# sealien_ctrlpilot_mavlinkbridge

`sealien_ctrlpilot_mavlinkbridge` 是 Sealien 控制系统中 ROS 2 中位机与 STM32 下位机之间的 MAVLink/UDP 桥接功能包。它把 STM32 上报的 MAVLink 帧转换为强类型 ROS topic，也把 ROS 控制/测试 topic 编码为 MAVLink 帧发送到指定 STM32 endpoint。

本包当前覆盖两类应用：

- ROV：多块 STM32 下位机并发通信，默认 topic 前缀为 `rov`。
- TMS：TMS 单板通信，默认 topic 前缀为 `tms`。

更完整的设计说明、迁移方法和维护细节见：

```text
src/sealien_ctrlpilot_mavlinkbridge/docs/rov_mavlink_bridge_user_manual.md
```

## 1. 功能定位

本功能包负责：

- 监听 STM32 通过 UDP 上报的 MAVLink 2.0 帧。
- 按 endpoint 校验 MAVLink `system_id/component_id`。
- 按 YAML 白名单过滤允许接收/发送的 MSGID。
- 将合法 MAVLink 消息发布为 ROS 强类型 topic。
- 订阅 ROS 下发 topic，编码并通过 UDP `sendto()` 发给指定 STM32。
- 管理 HEARTBEAT、在线/离线状态、配置热重载和 UDP 发送统计。
- 提供 ROV 通信质量压测节点和长周期测试脚本。

本功能包不负责：

- 业务控制决策。
- 推进器、阀控、继电器等载荷安全策略。
- 端到端可靠重传。当前通信基于 UDP，链路质量通过统计和双端日志验证。
- STM32 固件内部任务调度。

## 2. 目录结构

```text
sealien_ctrlpilot_mavlinkbridge/
├── config/
│   ├── sealien_mavlink_rov.yaml      # ROV 多 endpoint 配置
│   └── sealien_mavlink_tms.yaml      # TMS endpoint 配置
├── docs/
│   ├── rov_mavlink_bridge_user_manual.md
│   ├── rov_mavlink_comm_test_case.md
│   └── *_comm_quality_report_*.md
├── include/sealien_ctrlpilot_mavlinkbridge/
│   └── mavlink_bridge_core.hpp       # 桥接核心类声明
├── launch/
│   └── rov_mavlink_test.launch.py    # ROV 通信质量测试 launch
├── scripts/
│   ├── start_rov_mavlink_test.sh     # ROV 单次测试辅助脚本
│   └── start_rov_mavlink_long_test.sh # ROV 长周期测试辅助脚本
├── src/
│   ├── mavlink_bridge_core.cpp       # YAML、UDP、MAVLink、ROS topic 核心实现
│   ├── rov_mavlink_node.cpp          # ROV 正式 bridge 节点入口
│   ├── tms_mavlink_node.cpp          # TMS 正式 bridge 节点入口
│   └── rov_mavlink_test_node.cpp     # ROV 通信质量测试节点
├── tools/
│   └── sealien_mavlink.xml           # MAVLink 方言源文件
└── lib/v2.0/sealien_mavlink/         # 由 MAVLink XML 生成的 C 头文件
```

## 3. 节点说明

### 3.1 `rov_mavlink_node`

ROV 正式 MAVLink bridge 节点。

默认配置：

```text
config/sealien_mavlink_rov.yaml
```

默认 topic 前缀：

```text
rov
```

典型职责：

- 绑定 ROS 主机 UDP 端口 `9999`。
- 接收 EP101/EP102/EP103 上报的 MAVLink 消息。
- 发布 `/rov/from_mcu/<endpoint>/<message>`。
- 订阅 `/rov/to_mcu/<endpoint>/<message>` 并下发到对应 STM32。
- 发布 UDP 发送统计 `/rov_mavlink_node/tx_stats`。

### 3.2 `tms_mavlink_node`

TMS 正式 MAVLink bridge 节点。

默认配置：

```text
config/sealien_mavlink_tms.yaml
```

默认 topic 前缀：

```text
tms
```

典型职责：

- 面向 TMS 下位机 `tms_mcu` 建立 MAVLink/UDP 通信。
- 使用 `/tms/from_mcu/...` 和 `/tms/to_mcu/...` topic 命名空间。

### 3.3 `rov_mavlink_test_node`

ROV 通信质量测试节点，只用于联调和压测。

重要特性：

- 不直接打开 MAVLink UDP socket。
- 通过 `rov_mavlink_node` 提供的 ROS topic 发送测试消息和接收桥接后的上行消息。
- 可按 MSGID 压测频率发布测试激励。
- 输出 5s 简报和 60s 详报，统计速率、丢包、gap、在线状态等。
- 默认 `safe_mode=true`，测试载荷使用低风险/非动作值。

注意：生产控制场景不要与 `rov_mavlink_test_node` 混跑，除非测试 topic、硬件动作和安全策略已明确隔离。

## 4. Topic 命名规则

Topic 由 `topic_prefix`、endpoint 名称和消息名共同决定。

STM32 -> ROS：

```text
/<topic_prefix>/from_mcu/<endpoint>/<message>
```

ROS -> STM32：

```text
/<topic_prefix>/to_mcu/<endpoint>/<message>
```

示例：

```text
/rov/from_mcu/nav_sensor_mcu/imu_data
/rov/from_mcu/actuator_mcu/thruster_status
/rov/from_mcu/io_valve_mcu/valve_status
/rov/to_mcu/actuator_mcu/thruster_cmd
/rov/to_mcu/io_valve_mcu/valve_cmd
/tms/from_mcu/tms_mcu/switch_status
/tms/to_mcu/tms_mcu/switch_cmd
```

测试统计 topic：

```text
/rov/mavlink_test/quality_summary
/rov/mavlink_test/quality_report
/rov/mavlink_test/rx_summary
/rov/mavlink_test/rx_events
/rov/mavlink_test/tx_events
```

Bridge UDP 发送统计：

```text
/rov_mavlink_node/tx_stats
```

`tx_stats` 表示 ROS bridge 调用 UDP `sendto()` 的成功/失败，不等价于 STM32 已完成业务处理。端到端下行质量需结合 STM32 RX 统计判断。

## 5. ROV 配置文件

ROV 默认配置文件：

```text
config/sealien_mavlink_rov.yaml
```

当前 endpoint：

| Endpoint | 角色 | sysid/compid | IP:Port | ROS 前缀 |
| --- | --- | --- | --- | --- |
| `nav_sensor_mcu` | EP101 导航/传感器板 | `101/1` | `192.168.100.101:9999` | `rov` |
| `actuator_mcu` | EP102 推进器/云台/灯光/开关执行板 | `102/1` | `192.168.100.102:9999` | `rov` |
| `io_valve_mcu` | EP103 混合 IO/阀控板 | `103/1` | `192.168.100.103:9999` | `rov` |

ROV 主机配置：

```yaml
host:
  system_id: 1
  component_id: 1
  bind_ip: "0.0.0.0"
  bind_port: 9999
```

ROV 消息方向以 ROS bridge 为视角：

```yaml
messages:
  rx: [0, 1, 5, 6, 7, 8, 18]  # STM32 -> ROS
  tx: [0, 12, 13]              # ROS -> STM32
```

配置含义：

- `rx`：允许从该 endpoint 接收的 MSGID。
- `tx`：允许发往该 endpoint 的 MSGID。
- `system_id/component_id`：必须与 STM32 固件一致。
- `remote_ip/remote_port`：ROS 下发 UDP 的目标地址。
- `enabled=false` 可临时禁用 endpoint。

## 6. TMS 配置文件

TMS 默认配置文件：

```text
config/sealien_mavlink_tms.yaml
```

当前 endpoint：

| Endpoint | 角色 | sysid/compid | IP:Port | ROS 前缀 |
| --- | --- | --- | --- | --- |
| `tms_mcu` | TMS 下位机 | `200/0` | `192.168.100.200:49153` | `tms` |

TMS 主机配置：

```yaml
host:
  system_id: 15
  component_id: 0
  bind_ip: "0.0.0.0"
  bind_port: 9999
```

当前 TMS 消息配置：

```yaml
messages:
  rx: [0, 9]
  tx: [0, 17]
```

含义：

- 接收 TMS 心跳和开关状态。
- 向 TMS 下发心跳和开关命令。

## 7. 编译

```bash
cd /home/se113/SLWS/SealienDCN
colcon build --packages-select sealien_ctrlpilot_mavlinkbridge
source install/setup.bash
```

如果修改了消息定义或 MAVLink 生成头文件，通常需要连同依赖包一起重新编译。

## 8. 启动正式通信节点

### 8.1 启动 ROV bridge

```bash
cd /home/se113/SLWS/SealienDCN
source install/setup.bash
ros2 run sealien_ctrlpilot_mavlinkbridge rov_mavlink_node
```

覆盖配置路径和 topic 前缀：

```bash
ros2 run sealien_ctrlpilot_mavlinkbridge rov_mavlink_node --ros-args \
  -p config_file:=/home/se113/SLWS/SealienDCN/src/sealien_ctrlpilot_mavlinkbridge/config/sealien_mavlink_rov.yaml \
  -p topic_prefix:=rov \
  -p auto_reload:=true
```

### 8.2 启动 TMS bridge

```bash
cd /home/se113/SLWS/SealienDCN
source install/setup.bash
ros2 run sealien_ctrlpilot_mavlinkbridge tms_mavlink_node
```

覆盖配置路径和 topic 前缀：

```bash
ros2 run sealien_ctrlpilot_mavlinkbridge tms_mavlink_node --ros-args \
  -p config_file:=/home/se113/SLWS/SealienDCN/src/sealien_ctrlpilot_mavlinkbridge/config/sealien_mavlink_tms.yaml \
  -p topic_prefix:=tms \
  -p auto_reload:=true
```

### 8.3 常用 bridge 参数

| 参数 | 说明 |
| --- | --- |
| `config_file` | YAML 配置文件路径。 |
| `topic_prefix` | topic 前缀，例如 `rov` 或 `tms`。 |
| `auto_reload` | 是否根据 YAML 修改时间自动热重载。 |
| `strict_remote_ip` | 是否要求入站 UDP 源 IP 与 YAML `remote_ip` 完全一致。生产部署建议评估开启。 |
| `ros_queue_depth` | ROS publisher/subscriber queue depth。 |
| `udp_recv_buffer_bytes` | UDP 接收缓冲区大小。 |
| `udp_send_buffer_bytes` | UDP 发送缓冲区大小。 |
| `rx_idle_sleep_ms` | UDP 无数据时接收线程休眠时间。 |
| `enable_tx_stats` | 是否发布 UDP 发送统计。 |
| `tx_stats_period_sec` | UDP 发送统计周期。 |
| `heartbeat_host_tx_hz_override` | 覆盖 YAML 中的主机心跳频率；小于 0 表示使用 YAML。 |

## 9. ROV 通信质量测试

### 9.1 标准测试 launch

```bash
cd /home/se113/SLWS/SealienDCN
source install/setup.bash
ros2 launch sealien_ctrlpilot_mavlinkbridge rov_mavlink_test.launch.py
```

仅测试指定 endpoint：

```bash
ros2 launch sealien_ctrlpilot_mavlinkbridge rov_mavlink_test.launch.py \
  target_endpoints:="nav_sensor_mcu"
```

三块板全量测试：

```bash
ros2 launch sealien_ctrlpilot_mavlinkbridge rov_mavlink_test.launch.py \
  target_endpoints:="[]"
```

常用参数：

| 参数 | 说明 |
| --- | --- |
| `target_endpoints` | 指定参与测试的 endpoint；空列表表示全部启用 endpoint。 |
| `brief_report_period_sec` | 简报周期，常用 5s。 |
| `detail_report_period_sec` | 详报周期，常用 60s。 |
| `use_stress_rates` | 是否按压力测试频率发布。 |
| `safe_mode` | 是否使用低风险测试载荷。默认建议保持 true。 |
| `publish_per_message_events` | 是否发布每帧事件 topic。长周期测试建议 false。 |
| `publish_rx_mirror_topics` | 是否发布上行镜像 topic。长周期测试建议 false。 |
| `log_quality_report` | 是否向日志输出质量报告。 |

### 9.2 长周期测试脚本

脚本路径：

```text
scripts/start_rov_mavlink_long_test.sh
```

启动方式：

```bash
./src/sealien_ctrlpilot_mavlinkbridge/scripts/start_rov_mavlink_long_test.sh
```

脚本行为：

- 启动 STM32 串口汇总终端。
- 向 EP101/EP102/EP103 发送 `reboot`，清空 STM32 历史统计。
- 等待一段时间后启动 ROS 测试节点。
- ROS 日志和 STM32 串口日志分别保存到 `logs/mavlink_long_test/<时间戳>/`。
- STM32 串口日志写文件时会清洗颜色控制字符。

清理串口占用：

```bash
./src/sealien_ctrlpilot_mavlinkbridge/scripts/start_rov_mavlink_long_test.sh --cleanup-only
```

长周期测试建议：

- 固定 `ROS_DOMAIN_ID`，并在查询终端使用相同值。
- 使用 udev 规则固定 EP101/EP102/EP103 串口别名。
- 保持 `publish_per_message_events=false` 和 `publish_rx_mirror_topics=false`，减少测试节点对 ROS 通信环境的干扰。

## 10. ROS_DOMAIN_ID 注意事项

如果测试脚本正在运行，但另一个终端执行：

```bash
ros2 topic list
```

只看到：

```text
/parameter_events
/rosout
```

通常是查询终端与测试脚本所在 DDS domain 不一致。

排查：

```bash
echo $ROS_DOMAIN_ID
pgrep -af rov_mavlink_test_node
tr '\0' '\n' < /proc/<PID>/environ | grep -E 'ROS_DOMAIN_ID|RMW_IMPLEMENTATION|ROS_AUTOMATIC_DISCOVERY_RANGE'
```

临时修复：

```bash
cd /home/se113/SLWS/SealienDCN
source install/setup.bash
export ROS_DOMAIN_ID=0
ros2 daemon stop
ros2 daemon start
ros2 node list
ros2 topic list | grep -E 'mavlink|quality|summary'
```

建议在所有启动终端统一设置 `ROS_DOMAIN_ID`，避免“节点实际运行但 CLI 看不到”的误判。

## 11. 配置热重载

bridge 支持配置热重载：

- `auto_reload=true`：定时检查 `config_file` 修改时间并自动重载。
- 调用节点私有服务手动重载。

服务名示例：

```text
/rov_mavlink_node/reload_config
/tms_mavlink_node/reload_config
```

热重载策略：

- 新配置会先解析并尝试打开新 UDP socket。
- 只有新 socket 成功后才替换当前配置和 ROS 路由。
- 如果新配置格式错误或端口冲突，旧配置继续运行。

## 12. 增减 endpoint

新增 endpoint 的基本步骤：

1. 在 ROV 或 TMS YAML 的 `endpoints` 列表中新增配置。
2. 确保 `name` 唯一，且只包含适合 topic 的字符。
3. 确保 `system_id/component_id` 与 STM32 固件一致，并且不与其它 endpoint 重复。
4. 配置正确的 `remote_ip/remote_port`。
5. 在 `messages.rx/tx` 中只填写当前 bridge 已支持的 MSGID。
6. 同步修改 STM32 固件中的 IP、MAVLink 身份、上行/下行消息集合。
7. 启动 bridge，观察 link up 和 topic 是否生成。

临时禁用 endpoint：

```yaml
- name: "some_mcu"
  enabled: false
```

验证命令：

```bash
ros2 topic list | grep /rov/from_mcu/<endpoint>
ros2 topic list | grep /rov/to_mcu/<endpoint>
```

## 13. 新增 MSGID

新增 MAVLink 消息时通常需要同时改协议、ROS msg 和 bridge 映射。

推荐步骤：

1. 更新 `tools/sealien_mavlink.xml`。
2. 重新生成 `lib/v2.0/sealien_mavlink` 下的 MAVLink C 头文件。
3. 在 `sealien_ctrlpilot_msgmanagement/msg` 中新增或更新 ROS msg。
4. 更新 `sealien_ctrlpilot_msgmanagement/CMakeLists.txt`。
5. 在 `mavlink_bridge_core.hpp` include 新 ROS msg 头文件。
6. 在 `mavlink_bridge_core.cpp` 中维护 MSGID 到名称、publisher、subscriber、编码和解码逻辑。
7. 更新 ROV/TMS YAML 中的 `messages.rx/tx`。
8. 更新 STM32 固件中的 MAVLink 解析和打包逻辑。
9. 增加测试节点覆盖，确认新消息的收发、gap 和丢包统计。

维护原则：

- 不要用裸内存拷贝直接转换 ROS msg 和 MAVLink struct。
- 显式逐字段赋值，便于协议变更时被编译器暴露问题。
- 新 MSGID 必须同时明确方向和 endpoint 白名单。

## 14. 生产使用注意事项

- 正式控制场景只启动 `rov_mavlink_node` 或 `tms_mavlink_node`，不要同时启动压力测试节点。
- 测试节点会主动向 `/rov/to_mcu/...` 发布命令类消息，即使 `safe_mode=true`，也应确认硬件安全状态。
- `strict_remote_ip=false` 便于联调，但生产网络建议评估开启。
- `bind_ip=0.0.0.0` 会监听所有网卡；生产部署可收敛为指定网口 IP。
- UDP 不提供可靠重传，控制链路设计应能容忍短时丢包或通过上层状态闭环判断。
- 修改 YAML 后确认 endpoint 身份、MSGID 白名单和 STM32 固件保持一致。
- 长周期日志默认写入 `logs/`，该目录应保持 git ignore。
- 多板串口长测建议使用固定 udev 设备名，避免 `/dev/ttyACM*` 重枚举导致板卡映射错位。

## 15. 常用排查命令

查看节点：

```bash
ros2 node list | grep mavlink
```

查看 topic：

```bash
ros2 topic list | grep -E 'rov|tms|mavlink|quality|summary'
```

查看质量简报：

```bash
ros2 topic echo /rov/mavlink_test/quality_summary
```

查看 bridge UDP 发送统计：

```bash
ros2 topic echo /rov_mavlink_node/tx_stats
```

确认 UDP 端口：

```bash
ss -lunp | grep 9999
```

确认串口占用：

```bash
sudo fuser -v /dev/ttyACM1 /dev/ttyACM2 /dev/ttyACM3
```

清理长周期测试串口占用：

```bash
./src/sealien_ctrlpilot_mavlinkbridge/scripts/start_rov_mavlink_long_test.sh --cleanup-only
```
