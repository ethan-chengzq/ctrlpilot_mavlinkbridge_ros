# ROV MAVLink Bridge 使用手册

## 1. 文档目的

本文面向维护者、联调人员和后续复用该功能包的开发者，说明 `sealien_ctrlpilot_mavlinkbridge` 的设计原理、运行方式、配置方法、endpoint 增减流程、消息扩展方法以及生产场景注意事项。

通信质量压测流程和测试报告模板见：

- `docs/rov_mavlink_comm_test_case.md`
- `docs/rov_mavlink_comm_quality_report_*.md`
- `docs/rov_mavlink_ep*_comm_quality_report_*.md`

## 2. 功能定位

`sealien_ctrlpilot_mavlinkbridge` 是 ROS 2 中位机与多块 STM32 下位机之间的 MAVLink/UDP 桥接层。

它负责：

- 监听 STM32 通过 UDP 上报的 MAVLink 帧。
- 校验 MAVLink `system_id/component_id` 和 MSGID 白名单。
- 将合法 MAVLink 消息解码为强类型 ROS topic。
- 订阅 ROS 下发 topic，将 ROS message 编码为 MAVLink 并通过 UDP 发给指定 STM32。
- 管理 endpoint 心跳、在线/离线状态和 UDP 发送统计。
- 支持 YAML 配置热重载，便于联调期间调整 endpoint 和路由。

它不负责：

- 业务控制决策。
- 安全载荷控制策略。
- STM32 固件内部任务调度。
- 端到端可靠传输重发。当前通信基于 UDP，质量监测依赖统计和上下行交叉验证。

## 3. 架构概览

### 3.1 核心节点

正式通信节点：

```text
rov_mavlink_node
```

默认配置：

```text
config/sealien_mavlink_rov.yaml
```

默认 topic 前缀：

```text
rov
```

核心实现：

```text
include/sealien_ctrlpilot_mavlinkbridge/mavlink_bridge_core.hpp
src/mavlink_bridge_core.cpp
src/rov_mavlink_node.cpp
```

测试节点：

```text
rov_mavlink_test_node
```

该节点只用于通信质量压测，会主动向 `rov/to_mcu/*` 发布测试激励。生产控制场景不要与正式控制节点混跑，除非测试 topic、硬件动作和安全策略已明确隔离。

### 3.2 数据流

STM32 到 ROS：

```text
STM32 UDP MAVLink
  -> rov_mavlink_node rx_loop()
  -> system_id/component_id 校验
  -> endpoint.messages.rx 白名单校验
  -> MAVLink decode
  -> rov/from_mcu/<endpoint>/<message>
```

ROS 到 STM32：

```text
业务节点 publish ROS message
  -> rov/to_mcu/<endpoint>/<message>
  -> rov_mavlink_node subscription callback
  -> endpoint.messages.tx 白名单校验
  -> MAVLink encode
  -> UDP sendto(remote_ip:remote_port)
```

心跳：

```text
MSGID 0 HEARTBEAT
```

心跳仍按普通路由管理：

- `endpoint.messages.rx` 包含 `0`：bridge 接收该 endpoint 上报心跳。
- `endpoint.messages.tx` 包含 `0`：bridge 向该 endpoint 发送主机心跳。

## 4. Topic 命名规则

配置项：

```yaml
topic_prefix: rov
```

上行 topic：

```text
/<topic_prefix>/from_mcu/<endpoint>/<message>
```

下行 topic：

```text
/<topic_prefix>/to_mcu/<endpoint>/<message>
```

示例：

```text
/rov/from_mcu/nav_sensor_mcu/imu_data
/rov/from_mcu/actuator_mcu/thruster_status
/rov/to_mcu/actuator_mcu/thruster_cmd
/rov/to_mcu/io_valve_mcu/valve_cmd
```

测试统计 topic：

```text
/rov/test/quality_summary
/rov/test/quality_report
/rov/test/rx_summary
/rov/test/rx_events
/rov/test/tx_events
```

bridge UDP 发送统计：

```text
/rov_mavlink_node/tx_stats
```

`tx_stats` 记录的是 `sendto` 层成功/失败，不代表 STM32 已完成业务处理。下行端到端质量需要与 STM32 RX 日志交叉判断。

## 5. YAML 配置说明

配置文件：

```text
src/sealien_ctrlpilot_mavlinkbridge/config/sealien_mavlink_rov.yaml
```

核心结构：

```yaml
sealien_mavlink_bridge:
  dialect: "tools/sealien_mavlink.xml"

  host:
    system_id: 1
    component_id: 1
    bind_ip: "0.0.0.0"
    bind_port: 9999

  heartbeat:
    host_tx_hz: 1.0
    endpoint_expected_hz: 1.0
    endpoint_timeout_ms: 3000

  endpoints:
    - name: "nav_sensor_mcu"
      enabled: true
      system_id: 101
      component_id: 1
      remote_ip: "192.168.100.101"
      remote_port: 9999
      messages:
        rx: [0, 1, 5, 6, 7, 8, 18]
        tx: [0, 12, 13]
```

字段说明：

| 字段 | 含义 |
| --- | --- |
| `dialect` | MAVLink XML 方言路径，用于说明协议来源。当前 C++ 编译依赖已生成的 `mavlink.h`。 |
| `host.system_id` | ROS 主机 MAVLink system id。STM32 端应以此识别 ROS 主机。 |
| `host.component_id` | ROS 主机 MAVLink component id。 |
| `host.bind_ip` | ROS UDP 监听地址。`0.0.0.0` 表示监听所有本机网卡。 |
| `host.bind_port` | ROS UDP 监听端口。 |
| `heartbeat.host_tx_hz` | bridge 主机心跳发送频率。小于等于 0 时不发送主机心跳，但仍检查 endpoint 超时。 |
| `heartbeat.endpoint_timeout_ms` | 超过该时间未收到 endpoint 合法 MAVLink 帧则判定 link down。 |
| `endpoint.name` | endpoint 名称，会进入 ROS topic，必须唯一。 |
| `endpoint.enabled` | 是否启用该 endpoint。 |
| `endpoint.system_id/component_id` | STM32 MAVLink 身份，必须与固件一致，且在所有 endpoint 中唯一。 |
| `endpoint.remote_ip/remote_port` | ROS 向该 STM32 下发 UDP 的目的地址。 |
| `messages.rx` | ROS 允许从该 endpoint 接收的 MSGID。 |
| `messages.tx` | ROS 允许发往该 endpoint 的 MSGID。 |

## 6. 启动方法

### 6.1 编译

```bash
cd /home/se113/SLWS/SealienDCN
colcon build --packages-select sealien_ctrlpilot_mavlinkbridge
source install/setup.bash
```

### 6.2 启动正式 bridge

```bash
ros2 run sealien_ctrlpilot_mavlinkbridge rov_mavlink_node --ros-args \
  -p config_file:=/home/se113/SLWS/SealienDCN/src/sealien_ctrlpilot_mavlinkbridge/config/sealien_mavlink_rov.yaml \
  -p topic_prefix:=rov
```

常用参数：

| 参数 | 默认值 | 说明 |
| --- | --- | --- |
| `config_file` | package share 下的 `sealien_mavlink_rov.yaml` | bridge YAML 配置。 |
| `topic_prefix` | `rov` | ROS topic 前缀。 |
| `auto_reload` | `true` | YAML 文件 mtime 变化后自动重载。 |
| `strict_remote_ip` | `false` | 是否要求入站 UDP 源 IP 与 YAML `remote_ip` 完全一致。生产部署建议评估开启。 |
| `ros_queue_depth` | `100` | ROS topic queue depth。 |
| `udp_recv_buffer_bytes` | `262144` | UDP 接收缓冲区大小。 |
| `udp_send_buffer_bytes` | `262144` | UDP 发送缓冲区大小。 |
| `rx_idle_sleep_ms` | `1` | 非阻塞 UDP 无数据时接收线程休眠时间。 |
| `enable_tx_stats` | `true` | 是否发布 bridge UDP 发送统计。 |
| `tx_stats_period_sec` | `60` | UDP 发送统计输出周期。 |
| `heartbeat_host_tx_hz_override` | `-1.0` | 小于 0 使用 YAML；大于等于 0 覆盖 YAML 心跳频率。 |

### 6.3 启动标准压测

```bash
ros2 launch sealien_ctrlpilot_mavlinkbridge rov_mavlink_test.launch.py
```

仅测试指定 endpoint：

```bash
ros2 launch sealien_ctrlpilot_mavlinkbridge rov_mavlink_test.launch.py \
  target_endpoints:="nav_sensor_mcu"
```

三块板同时压测：

```bash
ros2 launch sealien_ctrlpilot_mavlinkbridge rov_mavlink_test.launch.py \
  target_endpoints:="[]"
```

注意：压测 launch 会同时启动正式 bridge 和测试节点。测试节点会主动发布下行测试消息，只用于联调/压测。

## 7. 增加 endpoint

### 7.1 修改 YAML

新增一块 STM32，例如 `power_mcu`：

```yaml
    - name: "power_mcu"
      enabled: true
      system_id: 104
      component_id: 1
      remote_ip: "192.168.100.104"
      remote_port: 9999
      messages:
        rx: [0, 5]
        tx: [0]
```

检查项：

- `name` 不与现有 endpoint 重复。
- `system_id/component_id` 不与现有 endpoint 重复。
- `remote_ip` 与 STM32 固件网络配置一致。
- STM32 固件中的 MAVLink system id/component id 与 YAML 一致。
- `messages.rx/tx` 只填写 bridge 已支持的 MSGID。

### 7.2 修改 STM32 固件

固件侧需要同步：

- IP 地址。
- MAVLink `system_id/component_id`。
- 上行消息集合，对应 YAML `messages.rx`。
- 下行消息 allowlist，对应 YAML `messages.tx`。
- 需要时更新测试固件 `ROV_MAVTEST_ACTIVE_ENDPOINT` 或新增 endpoint 配置。

### 7.3 验证

启动 bridge 后观察：

```bash
ros2 topic list | grep /rov/from_mcu/power_mcu
ros2 topic list | grep /rov/to_mcu/power_mcu
```

观察 link 日志：

```text
MAVLink link up: endpoint=power_mcu ...
```

若没有 link up：

- 检查 STM32 是否在发送 MAVLink。
- 检查 IP、端口、网线、路由。
- 检查 `system_id/component_id`。
- 检查 `messages.rx` 是否包含 STM32 正在上发的 MSGID。

## 8. 删除或临时禁用 endpoint

临时禁用：

```yaml
enabled: false
```

删除 endpoint 时需要确认：

- 没有业务节点继续订阅或发布该 endpoint 的 topic。
- 测试 launch 的 `target_endpoints` 不再包含该 endpoint。
- STM32 固件或网络中不再使用相同 `system_id/component_id` 造成误判。

## 9. 新增 MAVLink MSGID

新增协议消息不是只改 YAML。完整流程如下：

1. 修改 MAVLink XML 方言，新增 message 定义。
2. 重新生成 `mavlink.h`，并确认 ROS/STM32 使用同一版协议头。
3. 在 `sealien_ctrlpilot_msgmanagement` 中新增或更新对应 ROS msg。
4. 在 `mavlink_bridge_core.hpp/.cpp` 中增加映射：
   - `msgid_name()`
   - `msgid_topic_name()`
   - `is_supported_msgid()`
   - `create_rx_publisher()`
   - `create_tx_subscription()`
   - `publish_rx_message()`
5. 在 YAML `messages.rx/tx` 中按 endpoint 增加该 MSGID。
6. 在 STM32 固件中增加 pack/decode/allowlist。
7. 编译 ROS 和 STM32 固件。
8. 使用 `rov_mavlink_test_node` 或业务节点做单消息验证。

建议顺序：

```text
协议 XML -> MAVLink header -> ROS msg -> bridge 映射 -> YAML -> STM32 固件 -> 联调测试
```

## 10. 迁移和复用注意事项

### 10.1 复用到其它产品线

优先复用 `MavlinkBridgeCore`，新建一个很薄的可执行节点，只指定：

- node name
- 默认 YAML 路径
- 默认 topic prefix

参考：

```cpp
auto node = std::make_shared<sealien_ctrlpilot_mavlinkbridge::MavlinkBridgeCore>(
  "rov_mavlink_node",
  share_dir + "/config/sealien_mavlink_rov.yaml",
  "rov");
```

不要复制 `mavlink_bridge_core.cpp` 后手改一份。重复实现会让协议映射、路由校验和统计逻辑长期分叉。

### 10.2 topic_prefix 规划

多套系统在同一 ROS graph 中运行时，必须使用不同 `topic_prefix`，例如：

```text
rov_a
rov_b
```

否则多个 bridge 会发布/订阅同名 topic，业务节点无法区分数据来源。

### 10.3 IP 和 MAVLink 身份

生产环境建议形成固定表：

| endpoint | IP | system_id | component_id | 说明 |
| --- | --- | --- | --- | --- |
| nav_sensor_mcu | 192.168.100.101 | 101 | 1 | 导航/传感器 |
| actuator_mcu | 192.168.100.102 | 102 | 1 | 执行机构 |
| io_valve_mcu | 192.168.100.103 | 103 | 1 | IO/阀控 |

严禁两块 STM32 使用相同 `system_id/component_id`。bridge 入站路由首先按 MAVLink 身份匹配，身份冲突会导致数据归属错误。

### 10.4 strict_remote_ip

`strict_remote_ip=false` 便于早期联调，因为只要 MAVLink 身份正确即可接收。

生产环境可考虑：

```bash
-p strict_remote_ip:=true
```

开启后，入站 UDP 源 IP 必须等于 YAML 中的 `remote_ip`。这能减少身份配置错误或网络串包造成的误接收，但前提是网络地址稳定。

## 11. 生产场景建议

- 正式控制只启动 `rov_mavlink_node`，不要启动 `rov_mavlink_test_node`。
- 测试节点的 `safe_mode=true` 只能降低测试载荷风险，不能替代系统安全策略。
- 生产控制节点应发布到明确 endpoint 的 `rov/to_mcu/<endpoint>/<msg>`，不要依赖广播。
- 对关键控制链路保留 `enable_tx_stats=true`，便于定位 UDP sendto 层故障。
- 对业务关键 topic 使用独立监控，例如 `ros2 topic hz`、控制节点内部 watchdog、STM32 端心跳超时。
- 若联调阶段频繁修改 YAML，可以开启 `auto_reload=true`；生产发布后建议有明确配置管理流程。

## 12. 常见问题

### 12.1 bridge 启动失败

重点检查：

- YAML 路径是否存在。
- `sealien_mavlink_bridge` 根 key 是否存在。
- `bind_ip/bind_port` 是否可用。
- endpoint 是否存在重复 `name` 或重复 `system_id/component_id`。
- YAML 中是否配置了 C++ 尚不支持的 MSGID。

### 12.2 没有收到 STM32 上行 topic

排查顺序：

1. STM32 是否实际上电并接入网络。
2. ROS 主机是否能 ping 通 STM32 IP。
3. STM32 是否向 ROS `bind_port` 发送 MAVLink。
4. `system_id/component_id` 是否与 YAML 一致。
5. YAML `messages.rx` 是否包含该 MSGID。
6. 若开启 `strict_remote_ip`，检查 UDP 源 IP 是否等于 YAML `remote_ip`。

### 12.3 ROS 下发后 STM32 没反应

排查顺序：

1. ROS topic 名称是否为 `rov/to_mcu/<endpoint>/<message>`。
2. YAML `messages.tx` 是否包含该 MSGID。
3. `/rov_mavlink_node/tx_stats` 是否显示 `win_fail`。
4. STM32 日志 `RX ROS->STM32` 是否收到对应 MSGID。
5. STM32 业务层是否消费该消息。

### 12.4 测试数据过于理想

需要区分统计层级：

- `TX TestNode->BridgeTopic`：测试节点 publish 计数，只代表 ROS topic 层激励。
- `Bridge UDP sendto`：bridge 调用 `sendto` 的成功/失败计数。
- STM32 `RX ROS->STM32`：STM32 实际解码收到的下行帧。
- ROS `RX BridgeTopic->TestNode`：ROS 实际收到的 STM32 上行帧。

端到端质量必须交叉对比，不应只看单侧 TX。

## 13. 推荐维护流程

修改配置：

```text
改 YAML -> 启动 bridge -> 检查 link up -> 检查 topic list -> 做单 endpoint 测试
```

新增消息：

```text
改协议 -> 生成 header -> 改 ROS msg -> 改 bridge 映射 -> 改 YAML/STM32 -> 编译 -> 压测
```

发布前检查：

```bash
colcon build --packages-select sealien_ctrlpilot_mavlinkbridge
ros2 launch sealien_ctrlpilot_mavlinkbridge rov_mavlink_test.launch.py target_endpoints:="[]"
```

测试报告应记录：

- 测试日期、固件版本、ROS commit。
- endpoint/IP/system_id/component_id。
- ROS RX、STM32 RX、Bridge UDP sendto 三类关键数据。
- 丢包率、帧间隔、link up/down 次数。
- 已知问题和后续优化建议。
