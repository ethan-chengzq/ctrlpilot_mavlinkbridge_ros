# ROV MAVLink 通信测试用例

本文档用于验证 `sealien_ctrlpilot_mavlinkbridge` ROS 端与 `sealien-ctrlcore` STM32 端之间的 UDP MAVLink 通信。

单板测试示例默认以 `nav_sensor_mcu` 为例，即 `sysid=101`、`IP=192.168.100.101`。实际烧录前必须以 STM32 端 `ROV_MAVTEST_ACTIVE_ENDPOINT`、`.config` 和 `rtconfig.h` 为准；当前代码可能已经切换到 `102 actuator_mcu` 或 `103 io_valve_mcu`。

## 1. 测试目标

验证以下能力是否正常：

- ROS 中位机可通过 `rov_mavlink_node` 绑定 UDP `9999` 端口并加载 ROV 配置。
- STM32 端可按当前 endpoint 身份周期性上发 MAVLink 测试消息。
- ROS 端可按 YAML 中 `messages.rx` 限制接收并发布对应 ROS Topic。
- ROS 端可按 YAML 中 `messages.tx` 限制下发 MAVLink 测试消息到指定 STM32。
- 心跳包 `MSGID 0` 支持双向发送和接收。
- 后续可切换到 `102/103` 节点，或继续扩展更多 STM32 endpoint。

## 2. 当前拓扑

ROS 主机建议配置为：

| 角色 | MAVLink sysid | MAVLink compid | IP | UDP 端口 |
| --- | ---: | ---: | --- | ---: |
| ROS ROV bridge | 1 | 1 | 192.168.100.100 | 9999 |

ROV 侧当前配置文件：

```text
/home/se113/SLWS/SealienDCN/src/sealien_ctrlpilot_mavlinkbridge/config/sealien_mavlink_rov.yaml
```

ROV endpoint 规划：

| endpoint | sysid | compid | STM32 IP | STM32 -> ROS, YAML rx | ROS -> STM32, YAML tx |
| --- | ---: | ---: | --- | --- | --- |
| nav_sensor_mcu | 101 | 1 | 192.168.100.101 | 0, 1, 5, 6, 7, 8, 18 | 0, 12, 13 |
| actuator_mcu | 102 | 1 | 192.168.100.102 | 0, 2, 3, 4, 9 | 0, 10, 11, 14, 15, 16, 17 |
| io_valve_mcu | 103 | 1 | 192.168.100.103 | 0, 20, 22 | 0, 19, 21 |

方向说明：

- `messages.rx`: ROS bridge 允许接收的 MAVLink MSGID，即 STM32 上发。
- `messages.tx`: ROS bridge 允许发送的 MAVLink MSGID，即 ROS 下发到 STM32。
- `MSGID 0 HEARTBEAT` 也由 `messages.rx/tx` 管理。某 endpoint 的 `rx` 包含 `0` 时监听该下位机心跳，`tx` 包含 `0` 时 ROS bridge 向该下位机发送心跳。

## 3. 相关源码

ROS 侧：

```text
/home/se113/SLWS/SealienDCN/src/sealien_ctrlpilot_mavlinkbridge/src/rov_mavlink_node.cpp
/home/se113/SLWS/SealienDCN/src/sealien_ctrlpilot_mavlinkbridge/src/rov_mavlink_test_node.cpp
/home/se113/SLWS/SealienDCN/src/sealien_ctrlpilot_mavlinkbridge/src/mavlink_bridge_core.cpp
/home/se113/SLWS/SealienDCN/src/sealien_ctrlpilot_mavlinkbridge/config/sealien_mavlink_rov.yaml
```

STM32 侧：

```text
/home/se113/SLWS/CtrlCore/sealien-ctrlcore/src/task/mavlink_test/rov_mavlink_test.c
/home/se113/SLWS/CtrlCore/sealien-ctrlcore/src/se_def.h
/home/se113/SLWS/CtrlCore/sealien-ctrlcore/target/stm32/stm32h743-SLControlBoard/.config
/home/se113/SLWS/CtrlCore/sealien-ctrlcore/target/stm32/stm32h743-SLControlBoard/rtconfig.h
/home/se113/SLWS/CtrlCore/sealien-ctrlcore/target/stm32/stm32h743-SLControlBoard/board/default_config_test.h
/home/se113/SLWS/CtrlCore/sealien-ctrlcore/target/stm32/stm32h743-SLControlBoard/config/task.py
```

当前 STM32 侧 `task.py` 只编译：

```python
TASKS = [
    'mavlink_test/*.c',
]
```

因此旧 DCNTMS 业务任务不会参与当前 MAVLink 通信测试固件。

测试固件启用 `SE_ROV_MAVLINK_TEST_ENABLE` 时，`board.c` 会包含 `default_config_test.h`，并直接解析该文件中的内置 `default_conf`。这样可以避免文件系统中的旧 `default_conf.h` 覆盖 MAVLink 测试 IP 和端口。

## 4. 测试前检查

1. 确认 ROS 主机网口 IP 为 `192.168.100.100/24`。
2. 确认 STM32 当前固件身份与 IP 匹配：

| endpoint | `ROV_MAVTEST_ACTIVE_ENDPOINT` | STM32 IP | ROS YAML endpoint |
| --- | ---: | --- | --- |
| `nav_sensor_mcu` | `101U` | `192.168.100.101` | `remote_ip: "192.168.100.101"` |
| `actuator_mcu` | `102U` | `192.168.100.102` | `remote_ip: "192.168.100.102"` |
| `io_valve_mcu` | `103U` | `192.168.100.103` | `remote_ip: "192.168.100.103"` |

3. 确认 ROS 配置中目标 endpoint 的 `remote_ip` 与 STM32 本机 IP 一致。
4. 确认 STM32 `default_config_test.h` 中 `addr` 为 ROS 主机 IP：

```c
addr = "192.168.100.100"
port = 9999
```

5. 确认 ROS 与 STM32 两侧使用同一套 `sealien_mavlink` MAVLink C 头文件。
6. 若 ROS 主机防火墙启用，需允许 UDP `9999`。
7. 首次测试建议只连接一块 STM32，并在 ROS 测试节点中只指定对应 `target_endpoints`，避免多板 IP 或 sysid 配置混淆。
8. 若 STM32 端仍连接正式执行机构，先只运行 `rov_mavlink_node` 观察上发；确认安全后再启动 `rov_mavlink_test_node` 发送测试下行命令。

## 5. 编译

### 5.1 ROS 端

```bash
cd /home/se113/SLWS/SealienDCN
source /opt/ros/jazzy/setup.bash
colcon build --packages-select sealien_ctrlpilot_msgmanagement sealien_ctrlpilot_mavlinkbridge
source install/setup.bash
```

### 5.2 STM32 端

```bash
cd /home/se113/SLWS/CtrlCore/sealien-ctrlcore/target/stm32/stm32h743-SLControlBoard
scons -j16 --vehicle=DcnTmsRov --frame=1
```

预期结果：

- ROS 端两个包编译无错误。
- STM32 端生成 `Sealien-CtrlCore_SLControlBoard.elf` 和 `Sealien-CtrlCore_SLControlBoard.bin`。
- 当前测试工程可能仍有第三方库或原工程既有 warning，但不应有 error。

### 5.3 STM32 更换测试版固件

更换测试版固件前先确认三处配置：

```c
// src/se_def.h
#define SE_ROV_MAVLINK_TEST_ENABLE
```

```c
// src/task/mavlink_test/rov_mavlink_test.c
// 只打开一个 endpoint。下面以 102 actuator_mcu 为例。
#define ROV_MAVTEST_ACTIVE_ENDPOINT 102U
```

```text
# target/stm32/stm32h743-SLControlBoard/.config
CONFIG_RT_LWIP_IPADDR="192.168.100.102"
```

```c
// target/stm32/stm32h743-SLControlBoard/rtconfig.h
#define RT_LWIP_IPADDR "192.168.100.102"
```

测试固件编译产物位于：

```text
/home/se113/SLWS/CtrlCore/sealien-ctrlcore/target/stm32/stm32h743-SLControlBoard/Sealien-CtrlCore_SLControlBoard.elf
/home/se113/SLWS/CtrlCore/sealien-ctrlcore/target/stm32/stm32h743-SLControlBoard/Sealien-CtrlCore_SLControlBoard.bin
```

烧录流程建议：

1. 记录当前板卡原正式固件版本和当前 endpoint 身份。
2. 修改 `ROV_MAVTEST_ACTIVE_ENDPOINT` 和 STM32 本机 IP。
3. 编译生成 `.elf/.bin`。
4. 使用现有 STM32 烧录工具烧录 `Sealien-CtrlCore_SLControlBoard.bin`。
5. 复位后通过串口确认出现 `ROV MAVLink test endpoint=...` 日志。
6. 先 `ping` STM32，再启动 ROS bridge。

恢复正式固件时，去掉 `SE_ROV_MAVLINK_TEST_ENABLE` 或切回正式分支/配置，恢复正式 `task.py`、`default_config` 和 IP 配置后重新编译烧录。

## 6. 启动步骤

### 6.1 烧录 STM32

将当前测试固件烧录到目标 STM32 板。启动后串口日志应出现类似信息：

```text
ROV MAVLink test endpoint=nav_sensor_mcu sysid=101 compid=1 uplink=7 downlink=3
```

若烧录的是 102 或 103，对应日志应为：

```text
ROV MAVLink test endpoint=actuator_mcu sysid=102 compid=1 uplink=5 downlink=7
ROV MAVLink test endpoint=io_valve_mcu sysid=103 compid=1 uplink=3 downlink=3
```

### 6.2 网络连通性检查

在 ROS 主机执行：

```bash
# 按当前 STM32 IP 替换地址。
ping 192.168.100.101
```

预期结果：

- 可以稳定 ping 通。
- 若 ping 不通，先检查网线、交换机、ROS 主机网口 IP、STM32 IP、子网掩码和供电。

### 6.3 启动 ROS MAVLink bridge

开发调试时建议显式指定源码目录下的 YAML，便于修改配置后热重载：

```bash
cd /home/se113/SLWS/SealienDCN
source install/setup.bash

# 正式通信节点：负责 UDP MAVLink <-> ROS Topic，不包含测试激励逻辑。
ros2 run sealien_ctrlpilot_mavlinkbridge rov_mavlink_node --ros-args \
  -p config_file:=/home/se113/SLWS/SealienDCN/src/sealien_ctrlpilot_mavlinkbridge/config/sealien_mavlink_rov.yaml \
  -p topic_prefix:=rov \
  -p auto_reload:=true \
  -p strict_remote_ip:=true
```

预期结果：

- 节点名为 `rov_mavlink_node`。
- UDP 绑定 `0.0.0.0:9999`。
- 加载 `sealien_mavlink_rov.yaml` 中三个 endpoint。
- 根据每个 endpoint 的 `rx/tx` 创建 ROS Topic 路由。
- `strict_remote_ip=true` 时，来源 IP 不等于 YAML `remote_ip` 的 MAVLink 帧会被丢弃。

### 6.4 启动 ROS 测试激励节点

当前只测试 101 节点时执行：

```bash
cd /home/se113/SLWS/SealienDCN
source install/setup.bash

# 测试节点不打开 UDP socket，只通过 bridge 暴露的 ROS Topic 发送测试消息和统计接收质量。
ros2 run sealien_ctrlpilot_mavlinkbridge rov_mavlink_test_node --ros-args \
  -p config_file:=/home/se113/SLWS/SealienDCN/src/sealien_ctrlpilot_mavlinkbridge/config/sealien_mavlink_rov.yaml \
  -p target_endpoints:="['nav_sensor_mcu']" \
  -p tx_period_ms:=1000 \
  -p quality_report_period_sec:=5 \
  -p quality_link_timeout_ms:=3000 \
  -p log_quality_report:=true \
  -p safe_mode:=true \
  -p include_heartbeat_tx:=false
```

说明：

- `rov_mavlink_test_node` 不直接收发 UDP。
- 它向 `rov/to_mcu/<endpoint>/<message>` 发布测试 ROS 消息，由 `rov_mavlink_node` 转为 MAVLink UDP 下发。
- 它订阅 `rov/from_mcu/<endpoint>/<message>`，统计并镜像下位机上发消息。
- `include_heartbeat_tx=false` 时，测试节点不额外发布心跳；ROS bridge 自身会按 YAML `tx: [0]` 向 endpoint 定时发送心跳。

测试 102 节点：

```bash
ros2 run sealien_ctrlpilot_mavlinkbridge rov_mavlink_test_node --ros-args \
  -p config_file:=/home/se113/SLWS/SealienDCN/src/sealien_ctrlpilot_mavlinkbridge/config/sealien_mavlink_rov.yaml \
  -p target_endpoints:="['actuator_mcu']" \
  -p tx_period_ms:=1000 \
  -p safe_mode:=true \
  -p include_heartbeat_tx:=false
```

测试 103 节点：

```bash
ros2 run sealien_ctrlpilot_mavlinkbridge rov_mavlink_test_node --ros-args \
  -p config_file:=/home/se113/SLWS/SealienDCN/src/sealien_ctrlpilot_mavlinkbridge/config/sealien_mavlink_rov.yaml \
  -p target_endpoints:="['io_valve_mcu']" \
  -p tx_period_ms:=1000 \
  -p safe_mode:=true \
  -p include_heartbeat_tx:=false
```

三板同时测试：

```bash
ros2 run sealien_ctrlpilot_mavlinkbridge rov_mavlink_test_node --ros-args \
  -p config_file:=/home/se113/SLWS/SealienDCN/src/sealien_ctrlpilot_mavlinkbridge/config/sealien_mavlink_rov.yaml \
  -p target_endpoints:="['nav_sensor_mcu','actuator_mcu','io_valve_mcu']" \
  -p tx_period_ms:=1000 \
  -p safe_mode:=true \
  -p include_heartbeat_tx:=false
```

也可以一键启动 bridge 和测试节点：

```bash
cd /home/se113/SLWS/SealienDCN
source install/setup.bash

# launch 同时启动 rov_mavlink_node 和 rov_mavlink_test_node。
ros2 launch sealien_ctrlpilot_mavlinkbridge rov_mavlink_test.launch.py \
  config_file:=/home/se113/SLWS/SealienDCN/src/sealien_ctrlpilot_mavlinkbridge/config/sealien_mavlink_rov.yaml \
  topic_prefix:=rov \
  target_endpoints:="['nav_sensor_mcu']" \
  tx_period_ms:=1000 \
  safe_mode:=true \
  include_heartbeat_tx:=false
```

脚本启动方式：

```bash
cd /home/se113/SLWS/SealienDCN
source install/setup.bash

# --endpoints 支持单节点或逗号分隔多节点。
ros2 run sealien_ctrlpilot_mavlinkbridge start_rov_mavlink_test.sh -- \
  --config /home/se113/SLWS/SealienDCN/src/sealien_ctrlpilot_mavlinkbridge/config/sealien_mavlink_rov.yaml \
  --endpoints nav_sensor_mcu \
  --tx-period-ms 1000
```

安全说明：

- `safe_mode=true` 只代表测试节点尽量使用低风险载荷，不等同于正式执行机构安全锁。
- 若 STM32 端运行的是测试固件，当前下行命令只用于计数和解析，不会驱动真实 actuator。
- 若 STM32 端运行的是正式业务固件，启动 `rov_mavlink_test_node` 前必须确认现场允许发送对应 `messages.tx` 命令。

## 7. 观察命令

查看 topic：

```bash
ros2 topic list | grep rov
```

观察接收统计：

```bash
ros2 topic echo /rov/test/rx_summary
```

观察下位机上发事件：

```bash
ros2 topic echo /rov/test/rx_events
```

观察 ROS 下发事件：

```bash
ros2 topic echo /rov/test/tx_events
```

观察 101 节点上发的 IMU 测试数据：

```bash
ros2 topic echo /rov/from_mcu/nav_sensor_mcu/imu_data
```

观察测试节点镜像后的 IMU 测试数据：

```bash
ros2 topic echo /rov/test/from_mcu/nav_sensor_mcu/imu_data
```

查看频率：

```bash
ros2 topic hz /rov/from_mcu/nav_sensor_mcu/heartbeat
ros2 topic hz /rov/from_mcu/nav_sensor_mcu/imu_data
```

## 8. 测试日志含义

方向命名先统一说明：

- ROS 测试节点日志中的 `TX ROS->STM32` 表示测试节点发布 ROS topic，经 bridge 下发到 STM32。
- ROS 测试节点日志中的 `RX STM32->ROS` 表示 bridge 已经收到 STM32 MAVLink 帧并发布到 ROS topic。
- STM32 日志中的 `TX STM32->ROS` 表示 STM32 上发 MAVLink。
- STM32 日志中的 `RX ROS->STM32` 表示 STM32 收到 ROS bridge 下发的 MAVLink。

### 8.1 ROS bridge 日志

| 日志片段 | 含义 | 排查重点 |
| --- | --- | --- |
| `Loaded MAVLink config ... with N endpoints` | YAML 加载成功，bridge 已创建 socket 和路由。 | 若未出现，先检查 YAML 路径和格式。 |
| `Configured endpoint=... enabled=... ip=... sysid=... rx=... tx=...` | 当前 endpoint 的身份、IP 和允许 MSGID。 | 与 STM32 `ROV_MAVTEST_ACTIVE_ENDPOINT`、IP、sysid 对齐。 |
| `MAVLink link up: endpoint=... first_msgid=...` | 第一次收到该 endpoint 的合法 MAVLink 帧。 | 能看到这个日志说明 UDP、MAVLink CRC、sysid/compid、rx allowlist 均通过。 |
| `MAVLink link down: endpoint=... no_rx_ms=...` | 超过 `endpoint_timeout_ms` 没收到该 endpoint 消息。 | 查供电、网线、IP、STM32 任务、发送频率。 |
| `Drop MAVLink msgid=... from unknown sys=... comp=...` | 收到帧，但 sysid/compid 不属于任何 enabled endpoint。 | 查 STM32 active endpoint 或多板 sysid 冲突。 |
| `Drop MAVLink ... remote IP mismatch` | 开启 `strict_remote_ip` 后，来源 IP 与 YAML 不一致。 | 查 STM32 IP、YAML `remote_ip` 或网口地址。 |
| `Drop MAVLink msgid=... MSGID is not in rx route` | endpoint 身份正确，但该 MSGID 未列入 YAML `messages.rx`。 | 查 YAML rx 和 STM32 `uplink_ids` 是否一致。 |
| `Refuse sending MSGID ... route not configured` | ROS 有人发布了下发 topic，但该 MSGID 不在 YAML `messages.tx`。 | 查测试节点 target 或 YAML tx。 |

### 8.2 ROS 测试节点日志和 topic

| 日志或 topic | 含义 |
| --- | --- |
| `ROV MAVLink test node loaded X endpoints, Y tx routes and Z rx routes` | 测试节点按 YAML 和 `target_endpoints` 创建了多少测试发布/订阅路由。 |
| `MAVLink test LINK UP endpoint=... first_rx_msgid=...` | 测试节点第一次从该 endpoint 的 `from_mcu` topic 收到数据。 |
| `MAVLink test LINK DOWN endpoint=... rx_age_ms=...` | 测试节点超过 `quality_link_timeout_ms` 未收到该 endpoint 数据。 |
| `/rov/test/tx_events` | 每次测试节点发布下行测试 topic 时产生一条事件。 |
| `/rov/test/rx_events` | 每次测试节点收到 bridge 发布的上行 topic 时产生一条事件。 |
| `/rov/test/quality_summary` | 结构化字符串汇总，适合长期 echo 或记录日志。 |
| `/rov/test/from_mcu/<endpoint>/<msg>` | 测试节点镜像的上行数据，便于与正式 `from_mcu` topic 分开观察。 |

`quality_summary` 关键字段：

| 字段 | 含义 |
| --- | --- |
| `window` | 本次统计窗口长度。 |
| `endpoint` | 当前统计的 endpoint 名称。 |
| `state=WAIT` | 从启动后还未收到该 endpoint 的任何上行 topic。 |
| `state=UP` | 最近一次接收时间未超过超时阈值。 |
| `state=DOWN` | 曾经收到过数据，但现在超时。 |
| `rx_age_ms` | 距离最近一次上行 topic 的时间。 |
| `tx_ros_to_stm32` | ROS 测试节点已发布的下行消息总数和频率。 |
| `rx_stm32_to_ros` | ROS 测试节点已收到的上行消息总数和频率。 |

### 8.3 STM32 测试固件日志

| 日志片段 | 含义 | 排查重点 |
| --- | --- | --- |
| `ROV MAVLink test endpoint=... sysid=... compid=... uplink=... downlink=...` | 测试任务启动，显示当前固件身份和消息集合数量。 | 若 endpoint 与预期不一致，重新修改并编译 `ROV_MAVTEST_ACTIVE_ENDPOINT`。 |
| `MAVLink LINK UP` | STM32 收到 ROS 主机合法下行帧，host 链路置为 UP。 | 若 ROS 已启动但没有该日志，查 ROS 下发 topic、IP 和端口。 |
| `TX STM32->ROS tx msgid=... period=...Hz` | STM32 注册的周期上发消息及频率。 | 与 YAML `messages.rx` 对照。 |
| `RX ROS->STM32 rx msgid=...` | STM32 允许接收的下行 MSGID。 | 与 YAML `messages.tx` 对照。 |
| `MAVLink LINK QUALITY` | STM32 周期输出链路质量统计。 | 看 `Age`、总数和各 MSGID rate 是否持续增长。 |
| `heartbeat ts=... type=... status=... ver=...` | 最近一次收到 ROS bridge 心跳的内容。 | 若 heartbeat 计数不增长，查 YAML tx 是否包含 `0`。 |
| `MAVLink LINK DOWN` | STM32 超过 `ROV_MAVTEST_HOST_TIMEOUT_MS` 未收到 ROS 下行帧。 | 查 ROS bridge 是否仍在运行，或测试节点/bridge 心跳是否关闭。 |
| `drop msgid=... not allowed for endpoint ...` | STM32 收到 ROS 帧，但该 MSGID 不属于当前 endpoint 的 downlink allowlist。 | 查 ROS target endpoint 和 YAML tx。 |

## 9. 测试用例

### TC-01 编译检查

步骤：

1. 执行 ROS 端编译命令。
2. 执行 STM32 端编译命令。

预期结果：

- ROS 编译 `0 error`。
- STM32 编译 `0 error`。
- 生成 STM32 `.elf/.bin` 固件。

### TC-02 网络链路检查

步骤：

1. ROS 主机设置为 `192.168.100.100/24`。
2. 烧录并启动 101 节点 STM32。
3. ROS 主机执行 `ping 192.168.100.101`。

预期结果：

- ping 延迟稳定，无持续丢包。
- STM32 串口无网络初始化失败日志。

### TC-03 ROS bridge 启动检查

步骤：

1. 启动 `rov_mavlink_node`。
2. 执行 `ros2 node list`。
3. 执行 `ros2 topic list | grep rov/from_mcu/nav_sensor_mcu`。

预期结果：

- `/rov_mavlink_node` 存在。
- 出现 101 节点允许接收的 topic：

```text
/rov/from_mcu/nav_sensor_mcu/heartbeat
/rov/from_mcu/nav_sensor_mcu/imu_data
/rov/from_mcu/nav_sensor_mcu/vcheck
/rov/from_mcu/nav_sensor_mcu/height_status
/rov/from_mcu/nav_sensor_mcu/depth_status
/rov/from_mcu/nav_sensor_mcu/bem280
/rov/from_mcu/nav_sensor_mcu/dvl_data
```

- 出现 101 节点允许下发的 topic：

```text
/rov/to_mcu/nav_sensor_mcu/heartbeat
/rov/to_mcu/nav_sensor_mcu/imu_calib
/rov/to_mcu/nav_sensor_mcu/imu_clear
```

### TC-04 STM32 上发到 ROS

步骤：

1. 启动 `rov_mavlink_node`。
2. 启动 `rov_mavlink_test_node`，并指定 `target_endpoints=['nav_sensor_mcu']`。
3. 执行：

```bash
ros2 topic echo /rov/test/rx_summary
```

预期结果：

- `rx_summary` 中 `nav_sensor_mcu:0`、`nav_sensor_mcu:1`、`nav_sensor_mcu:5` 等计数持续增加。
- `/rov/from_mcu/nav_sensor_mcu/heartbeat` 约 `1 Hz`。
- `/rov/from_mcu/nav_sensor_mcu/imu_data` 约 `10 Hz`。
- `/rov/from_mcu/nav_sensor_mcu/vcheck`、`height_status`、`depth_status`、`bem280`、`dvl_data` 约 `2 Hz`。

### TC-05 ROS 下发到 STM32

步骤：

1. 保持 `rov_mavlink_node` 和 `rov_mavlink_test_node` 运行。
2. 执行：

```bash
ros2 topic echo /rov/test/tx_events
```

3. 查看 STM32 串口日志。

预期结果：

- `tx_events` 中周期性出现：

```text
tx endpoint=nav_sensor_mcu msgid=12 name=IMU_CALIB
tx endpoint=nav_sensor_mcu msgid=13 name=IMU_CLEAR
```

- STM32 串口出现：

```text
rx IMU_CALIB lon=0 lat=0 alt=0
rx IMU_CLEAR clear=0
```

- 若 `safe_mode=true`，`IMU_CLEAR clear` 应为 `0`，不会执行高风险动作。

### TC-06 双向心跳

步骤：

1. 保持 `rov_mavlink_node` 运行。
2. 执行：

```bash
ros2 topic hz /rov/from_mcu/nav_sensor_mcu/heartbeat
```

3. 查看 STM32 串口日志。

预期结果：

- ROS 端能看到 101 节点上发心跳，频率约 `1 Hz`。
- STM32 端能收到 ROS bridge 下发心跳，串口周期性出现类似日志：

```text
rx HEARTBEAT from host status=0
```

说明：

- 即使 `rov_mavlink_test_node` 的 `include_heartbeat_tx=false`，`rov_mavlink_node` 也会根据 YAML 中 `tx` 包含 `0` 自动发送心跳。
- 若要专门验证 ROS Topic 方式下发 `MSGID 0`，可将测试节点参数改为 `include_heartbeat_tx:=true`，但此时 bridge 心跳和测试心跳会同时存在。

### TC-07 路由限制检查

步骤：

1. 查看 101 节点 topic 列表：

```bash
ros2 topic list | grep /rov/to_mcu/nav_sensor_mcu
```

2. 检查是否存在未授权 topic，例如：

```text
/rov/to_mcu/nav_sensor_mcu/thruster_cmd
```

预期结果：

- 101 节点只出现 `heartbeat`、`imu_calib`、`imu_clear` 下发 topic。
- 不应出现 `thruster_cmd`、`led_cmd`、`mixed_io_cmd` 等不属于 101 节点 `messages.tx` 的 topic。
- 若下位机发送了不在 `messages.rx` 中的 MSGID，`rov_mavlink_node` 应丢弃该帧并输出 drop 日志。

### TC-08 三块 STM32 同时通信

前提：

- 三块 STM32 分别烧录为 101、102、103 对应固件。
- 三块 STM32 IP 分别为 `192.168.100.101`、`192.168.100.102`、`192.168.100.103`。
- ROS 主机可分别 ping 通三块板。

步骤：

1. 启动 `rov_mavlink_node`。
2. 启动测试节点：

```bash
ros2 run sealien_ctrlpilot_mavlinkbridge rov_mavlink_test_node --ros-args \
  -p config_file:=/home/se113/SLWS/SealienDCN/src/sealien_ctrlpilot_mavlinkbridge/config/sealien_mavlink_rov.yaml \
  -p target_endpoints:="['nav_sensor_mcu','actuator_mcu','io_valve_mcu']" \
  -p tx_period_ms:=1000 \
  -p safe_mode:=true \
  -p include_heartbeat_tx:=false
```

3. 观察：

```bash
ros2 topic echo /rov/test/rx_summary
```

预期结果：

- 101 节点计数持续增加：`0, 1, 5, 6, 7, 8, 18`。
- 102 节点计数持续增加：`0, 2, 3, 4, 9`。
- 103 节点计数持续增加：`0, 20, 22`。
- 三块板串口分别能看到本 endpoint 允许的下发 MSGID。
- 任意一块板掉线时，其对应计数停止增长，其它两块不受影响。

### TC-09 配置热重载

步骤：

1. 使用源码路径作为 `config_file` 启动 `rov_mavlink_node`。
2. 修改 `sealien_mavlink_rov.yaml`，例如临时将某个 endpoint 的 `enabled` 改为 `false`。
3. 等待 `auto_reload` 周期，或手动调用：

```bash
ros2 service call /rov_mavlink_node/reload_config \
  sealien_ctrlpilot_msgmanagement/srv/ReloadMavlinkConfig "{}"
```

预期结果：

- 配置格式正确时，bridge 输出 reload 成功日志。
- 被禁用 endpoint 的 ROS Topic 路由会被移除。
- 配置格式错误、端口冲突或 MSGID 不支持时，reload 失败，旧配置继续工作。

## 10. 当前测试固件配置说明

STM32 测试固件开关在 `src/se_def.h` 中定义：

```c
#define SE_ROV_MAVLINK_TEST_ENABLE
```

当前启用节点在 `src/task/mavlink_test/rov_mavlink_test.c` 中定义。烧录前以实际源码为准：

```c
// 示例：101 nav_sensor_mcu。实际值以当前要烧录的板卡身份为准。
#define ROV_MAVTEST_ACTIVE_ENDPOINT 101U
```

当前 IP 在以下文件中保持一致：

```text
target/stm32/stm32h743-SLControlBoard/.config
target/stm32/stm32h743-SLControlBoard/rtconfig.h
```

IP 示例：

```text
101 节点: 192.168.100.101
102 节点: 192.168.100.102
103 节点: 192.168.100.103
```

各节点测试程序行为：

- 101 `nav_sensor_mcu` 周期性上发 `HEARTBEAT`、`IMU_DATA`、`VCHECK`、`HEIGHT_STATUS`、`DEPTH_STATUS`、`BEM280`、`DVL_DATA`；只接收 `HEARTBEAT`、`IMU_CALIB`、`IMU_CLEAR`。
- 102 `actuator_mcu` 周期性上发 `HEARTBEAT`、`THRUSTER_STATUS`、`GS_STATUS`、`LED_STATUS`、`SWITCH_STATUS`；只接收 `HEARTBEAT`、`THRUSTER_CMD`、`THRUSTER_LOCK`、`LED_CMD`、`GS_CMD`、`GS_CFG`、`SWITCH_CMD`。
- 103 `io_valve_mcu` 周期性上发 `HEARTBEAT`、`MIXED_IO_DATA`、`VALVE_STATUS`；只接收 `HEARTBEAT`、`MIXED_IO_CMD`、`VALVE_CMD`。
- 丢弃来自非 ROS 主机 MAVLink 身份 `sysid=1, compid=1` 的下行帧。
- 丢弃不属于当前 endpoint `downlink_ids` 的 MSGID。

## 11. 切换为 102 或 103 节点

当前测试固件采用编译期选择 endpoint 的方式。每块 STM32 烧录前需要选择一个身份并设置对应 IP。

### 11.1 切换为 102 actuator_mcu

修改 `src/task/mavlink_test/rov_mavlink_test.c`：

```c
#define ROV_MAVTEST_ACTIVE_ENDPOINT 102U
```

修改 `.config`：

```text
CONFIG_RT_LWIP_IPADDR="192.168.100.102"
```

修改 `rtconfig.h`：

```c
#define RT_LWIP_IPADDR "192.168.100.102"
```

重新编译并烧录：

```bash
cd /home/se113/SLWS/CtrlCore/sealien-ctrlcore/target/stm32/stm32h743-SLControlBoard
scons -j16 --vehicle=DcnTmsRov --frame=1
```

ROS 测试节点改为：

```bash
ros2 run sealien_ctrlpilot_mavlinkbridge rov_mavlink_test_node --ros-args \
  -p config_file:=/home/se113/SLWS/SealienDCN/src/sealien_ctrlpilot_mavlinkbridge/config/sealien_mavlink_rov.yaml \
  -p target_endpoints:="['actuator_mcu']" \
  -p tx_period_ms:=1000 \
  -p safe_mode:=true
```

预期：

- ROS 收到 102 上发 `HEARTBEAT`、`THRUSTER_STATUS`、`GS_STATUS`、`LED_STATUS`、`SWITCH_STATUS`。
- STM32 串口收到 `THRUSTER_CMD`、`THRUSTER_LOCK`、`LED_CMD`、`GS_CMD`、`GS_CFG`、`SWITCH_CMD` 等允许下发消息。
- `safe_mode=true` 时推进器和开关类输出保持低风险测试值。

### 11.2 切换为 103 io_valve_mcu

修改 `src/task/mavlink_test/rov_mavlink_test.c`：

```c
#define ROV_MAVTEST_ACTIVE_ENDPOINT 103U
```

修改 `.config`：

```text
CONFIG_RT_LWIP_IPADDR="192.168.100.103"
```

修改 `rtconfig.h`：

```c
#define RT_LWIP_IPADDR "192.168.100.103"
```

重新编译并烧录。

ROS 测试节点改为：

```bash
ros2 run sealien_ctrlpilot_mavlinkbridge rov_mavlink_test_node --ros-args \
  -p config_file:=/home/se113/SLWS/SealienDCN/src/sealien_ctrlpilot_mavlinkbridge/config/sealien_mavlink_rov.yaml \
  -p target_endpoints:="['io_valve_mcu']" \
  -p tx_period_ms:=1000 \
  -p safe_mode:=true
```

预期：

- ROS 收到 103 上发 `HEARTBEAT`、`MIXED_IO_DATA`、`VALVE_STATUS`。
- STM32 串口收到 `MIXED_IO_CMD`、`VALVE_CMD`。
- `safe_mode=true` 时阀控、电流、频率和混合 IO 输出保持零值或关闭值。

### 11.3 切换注意事项

- `ROV_MAVTEST_ACTIVE_ENDPOINT`、STM32 本机 IP、ROS YAML 中该 endpoint 的 `remote_ip` 必须对应。
- `system_id/component_id` 不能与其它在线 STM32 重复。
- 每块 STM32 的 IP 不能重复。
- 如果 ROS 主机 IP 不是 `192.168.100.100`，需要修改 STM32 `default_config_test.h` 中 `addr`。
- 修改 `.config` 后若工程会自动生成 `rtconfig.h`，以生成结果为准；若手动维护，必须保证两个文件一致。

## 12. 添加更多 STM32 节点

### 12.1 ROS 配置扩展

在 `sealien_mavlink_rov.yaml` 的 `endpoints` 下新增节点：

```yaml
    - name: "extra_mcu"
      enabled: true
      system_id: 104
      component_id: 1
      remote_ip: "192.168.100.104"
      remote_port: 9999
      messages:
        rx: [0, 1]
        tx: [0, 12]
```

要求：

- `name` 全局唯一，用于 ROS Topic 路由。
- `system_id + component_id` 组合全局唯一，用于 MAVLink 入站识别。
- `remote_ip` 指向该 STM32 的静态 IP。
- `rx/tx` 只能填写当前 bridge 支持的 MSGID。若新增协议 MSGID，需要先扩展 MAVLink XML、ROS msg 和 bridge 映射。
- 不在线或暂不测试的 endpoint 建议设置 `enabled: false`。

新增后可通过自动热重载生效，也可手动调用：

```bash
ros2 service call /rov_mavlink_node/reload_config \
  sealien_ctrlpilot_msgmanagement/srv/ReloadMavlinkConfig "{}"
```

### 12.2 STM32 端扩展

若新增 `system_id=104` 的 STM32 测试节点，需要在 `rov_mavlink_test.c` 中增加一组配置：

1. 新增该节点允许上发的 `uplink_ids` 数组。
2. 新增该节点允许接收的 `downlink_ids` 数组。
3. 新增 `#elif ROV_MAVTEST_ACTIVE_ENDPOINT == 104U` 分支，填充 `active_endpoint`。
4. 若复用现有 MSGID，通常不需要新增 pack/decode 函数。
5. 若需要新的 MSGID，需要增加对应 `pack_by_msgid()`、`pack_callback_for_msgid()` 和 `decode_and_log_downlink()` 处理。
6. 在 `rov_mavlink_test.c` 增加可选节点注释，并在烧录该板前选择：

```c
#define ROV_MAVTEST_ACTIVE_ENDPOINT 104U
```

7. 修改 `.config` 和 `rtconfig.h`：

```text
192.168.100.104
```

8. 重新编译并烧录该 STM32。

### 12.3 多节点测试建议

- 每次新增一个节点后，先单独测试该节点，再加入多板联调。
- 多板联调时，先确认每块板可独立 ping 通。
- ROS 端使用 `target_endpoints` 控制测试激励范围，避免对未接线设备持续发送测试命令。
- 若要减少 bridge 对离线节点发送心跳，可临时将对应 endpoint `enabled` 改为 `false`。

## 13. 常见问题定位

### 13.1 ROS 收不到任何上发消息

检查项：

- `rov_mavlink_node` 是否启动并绑定 UDP `9999`。
- ROS 主机 IP 是否为 STM32 配置中的 `addr`。
- STM32 是否成功启动 `task:rov_mavtest`。
- STM32 本机 IP 是否与 ROS YAML `remote_ip` 一致。
- 两侧 MAVLink 头文件是否来自同一版 `sealien_mavlink.xml`。
- 防火墙是否拦截 UDP `9999`。

### 13.2 ROS 能收到心跳但收不到其它消息

检查项：

- `rov_mavlink_test.c` 中该 endpoint 的 `uplink_ids` 是否包含对应 MSGID。
- `sealien_mavlink_rov.yaml` 中该 endpoint 的 `messages.rx` 是否包含对应 MSGID。
- `mavlink_bridge_core.cpp` 是否支持该 MSGID 的 ROS publisher 和解码映射。

### 13.3 STM32 收不到 ROS 下发消息

检查项：

- `rov_mavlink_test_node` 是否运行。
- 测试节点 `target_endpoints` 是否包含当前 endpoint。
- YAML `messages.tx` 是否包含对应 MSGID。
- ROS 下发 topic 是否存在，例如 `/rov/to_mcu/nav_sensor_mcu/imu_calib`。
- STM32 UDP 是否绑定本地 `9999`，且 ROS YAML `remote_port` 是否为 `9999`。
- STM32 端 `handle_mavlink_message()` 是否因为 sysid/compid 或 allowlist 不匹配而丢弃。

### 13.4 三板同时测试时只有一块正常

检查项：

- 三块板是否烧录了不同的 `ROV_MAVTEST_ACTIVE_ENDPOINT`。
- 三块板 IP 是否分别为 `.101/.102/.103`。
- 三块板 sysid 是否分别为 `101/102/103`。
- 是否存在 IP 冲突。
- ROS 主机是否能分别 ping 通三块板。

## 14. 判定标准

单板通信测试通过条件：

- ROS 主机可 ping 通当前 STM32 IP。
- `rov_mavlink_node` 启动无异常。
- `rov_mavlink_test_node` 启动无异常。
- `/rov/test/rx_summary` 中当前 endpoint 允许上发的 MSGID 计数持续增加。
- 当前 endpoint 的 `/rov/from_mcu/<endpoint>/<msg>` 可持续 echo 到数据。
- STM32 串口能看到 ROS 下发的当前 endpoint 允许 MSGID。
- 双向心跳正常。
- 未配置给当前 endpoint 的下发 topic 不存在或不会被 bridge 发送。

三板联调通过条件：

- 三块 STM32 分别以 `101/102/103` 身份在线。
- 三块 STM32 均可被 ROS 主机 ping 通。
- `/rov/test/rx_summary` 中三组 endpoint 的 MSGID 计数均持续增加。
- 三块 STM32 只收到自己 `messages.tx` 允许的下发 MSGID。
- 任意单板掉线不影响其它 endpoint 的收发。
