# sealien_ctrlpilot_mavlinkbridge 源码说明

本功能包提供 ROV 和 TMS 两个 ROS 2 MAVLink 网口通信节点，用于中位机 ROS 与 STM32 下位机之间进行 UDP MAVLink 2.0 通信。两个节点共用同一套核心实现，区别只在默认配置文件和 ROS Topic 前缀。

## 文件结构

- `src/rov_mavlink_node.cpp`
  ROV 节点入口，默认加载 `config/sealien_mavlink_rov.yaml`，Topic 前缀为 `rov`。
- `src/tms_mavlink_node.cpp`
  TMS 节点入口，默认加载 `config/sealien_mavlink_tms.yaml`，Topic 前缀为 `tms`。
- `src/rov_mavlink_test_node.cpp`
  ROV 通信联调测试节点，读取 `config/sealien_mavlink_rov.yaml`，按配置中的 `messages.tx/rx` 自动创建测试发布和接收镜像。
- `docs/rov_mavlink_comm_test_case.md`
  ROV MAVLink 通信测试用例，说明 ROS 与 STM32 联调步骤、预期现象、节点切换和扩展方法。
- `include/sealien_ctrlpilot_mavlinkbridge/mavlink_bridge_core.hpp`
  桥接核心类声明，包括配置结构、线程状态、ROS publisher/subscriber 和 UDP socket 成员。
- `src/mavlink_bridge_core.cpp`
  桥接核心实现，包含 YAML 解析、UDP 收发、MAVLink 编解码、ROS Topic 路由、心跳发送和配置热重载。
- `config/sealien_mavlink_rov.yaml`
  ROV 中位机和多个 STM32 endpoint 的通信配置。
- `config/sealien_mavlink_tms.yaml`
  TMS 中位机和 STM32 endpoint 的通信配置。
- `lib/v2.0/sealien_mavlink`
  由 `tools/sealien_mavlink.xml` 生成的 MAVLink C 头文件。

## 运行方式

```bash
source install/setup.bash
ros2 run sealien_ctrlpilot_mavlinkbridge rov_mavlink_node
ros2 run sealien_ctrlpilot_mavlinkbridge tms_mavlink_node
```

可通过参数覆盖默认配置：

```bash
ros2 run sealien_ctrlpilot_mavlinkbridge rov_mavlink_node --ros-args \
  -p config_file:=/path/to/sealien_mavlink_rov.yaml \
  -p topic_prefix:=rov
```

ROV 三板联调测试节点需要和 `rov_mavlink_node` 同时运行。测试节点不直接打开 UDP 端口，而是通过桥接节点的 ROS Topic 触发 MAVLink 下发并接收桥接后的上发消息：

```bash
source install/setup.bash
ros2 launch sealien_ctrlpilot_mavlinkbridge rov_mavlink_test.launch.py
```

只测试 101 节点：

```bash
ros2 launch sealien_ctrlpilot_mavlinkbridge rov_mavlink_test.launch.py \
  target_endpoints:="['nav_sensor_mcu']"
```

也可以用脚本快捷入口：

```bash
ros2 run sealien_ctrlpilot_mavlinkbridge start_rov_mavlink_test.sh -- \
  --endpoints nav_sensor_mcu
```

常用参数：

```bash
ros2 run sealien_ctrlpilot_mavlinkbridge rov_mavlink_test_node --ros-args \
  -p tx_period_ms:=1000 \
  -p safe_mode:=true \
  -p include_heartbeat_tx:=false \
  -p target_endpoints:="['nav_sensor_mcu','actuator_mcu','io_valve_mcu']"
```

测试节点输出：

```text
rov/test/tx_events                         # 每次测试下发事件
rov/test/rx_events                         # 每次收到下位机上发事件
rov/test/rx_summary                        # 1 Hz 接收计数汇总
rov/test/from_mcu/<endpoint>/<message>     # 下位机上发消息的测试镜像 Topic
```

`safe_mode=true` 时，推进器、继电器、阀控、混合 IO 等测试载荷使用锁定、关闭或零输出值，适合先验证链路。需要硬件动作测试时再显式关闭 `safe_mode`，并确认现场条件允许。

## Topic 约定

节点根据 YAML 中每个 endpoint 的 `messages.rx` 和 `messages.tx` 自动创建 Topic。

下位机上发到 ROS：

```text
<prefix>/from_mcu/<endpoint>/<message_name>
```

ROS 下发到下位机：

```text
<prefix>/to_mcu/<endpoint>/<message_name>
```

示例：

```text
rov/from_mcu/nav_sensor_mcu/imu_data
rov/to_mcu/actuator_mcu/thruster_cmd
tms/from_mcu/tms_mcu/switch_status
tms/to_mcu/tms_mcu/switch_cmd
```

这种 Topic 设计的核心目的，是避免广播语义。一个 ROS Topic 明确对应一个 endpoint 和一个 MSGID，便于调试、录包和权限限制。

## 配置如何生效

YAML 中的每个 endpoint 有独立的 MAVLink 身份、UDP 地址和消息方向：

```yaml
endpoints:
  - name: "actuator_mcu"
    enabled: true
    system_id: 102
    component_id: 1
    remote_ip: "192.168.100.102"
    remote_port: 9999
    messages:
      rx: [0, 2, 3, 4, 9]
      tx: [0, 10, 11, 14, 15, 16, 17]
```

含义：

- 只接受 `sysid=102`、`compid=1` 且 MSGID 在 `rx` 列表中的 MAVLink 帧。
- 只允许向该 endpoint 发送 `tx` 列表中的 MSGID。
- `0 HEARTBEAT` 也在 `rx/tx` 中管理，因此可以动态决定是否监听或发送心跳。
- 同一 MSGID 可以同时出现在 `rx` 和 `tx` 中，代码支持双向使用同一消息 ID。

## 核心运行流程

### 启动

1. `rov_mavlink_node.cpp` 或 `tms_mavlink_node.cpp` 创建 `MavlinkBridgeCore`。
2. 构造函数声明和读取 ROS 参数：`config_file`、`topic_prefix`、`auto_reload` 等。
3. `reload_config()` 读取 YAML，校验 endpoint 名称、MAVLink 身份和 MSGID 范围。
4. `open_udp_socket()` 创建并绑定 UDP socket。
5. `rebuild_ros_routes()` 根据 `rx/tx` 创建 ROS publisher/subscriber。
6. 启动接收线程 `rx_loop()`，并启动心跳和配置重载定时器。

### 下位机上发

1. `rx_loop()` 使用 POSIX `recvfrom()` 从 UDP socket 读原始字节。
2. 每个字节交给 `mavlink_parse_char()`，MAVLink 库负责帧同步、长度和 CRC 校验。
3. 得到完整 `mavlink_message_t` 后调用 `handle_mavlink_message()`。
4. 先按 `sysid/component_id` 找 endpoint，再检查 MSGID 是否在该 endpoint 的 `rx` 中。
5. 通过后进入 `publish_rx_message()`，按 MSGID 解码 MAVLink payload 并发布 ROS msg。

### ROS 下发

1. `create_tx_subscription()` 根据 endpoint 的 `tx` 列表创建订阅器。
2. ROS callback 收到强类型 msg 后，填充对应的 `mavlink_*_t` 结构体。
3. 调用 `mavlink_msg_*_encode()` 生成 `mavlink_message_t`。
4. `send_message_to_endpoint()` 再次检查该 endpoint 是否允许发送该 MSGID。
5. `mavlink_msg_to_send_buffer()` 打包成字节流，`sendto()` 发往该 endpoint 的 IP/端口。

## 动态配置

节点支持两种重载方式：

- 自动重载：`auto_reload=true` 时，定时检查 `config_file` 修改时间。
- 手动重载：调用节点私有服务。

服务名：

```text
/rov_mavlink_node/reload_config
/tms_mavlink_node/reload_config
```

设计注意点：

- 新配置会先尝试打开并绑定新的 UDP socket。
- 只有 socket 成功后才替换当前配置和 ROS 路由。
- 如果新配置端口冲突或格式错误，旧运行状态不会被破坏。

ROS 端测试节点需要和桥接节点一起启动。
先启动 ROV MAVLink 桥接节点：
source install/setup.bash

ros2 run sealien_ctrlpilot_mavlinkbridge rov_mavlink_node --ros-args \
  -p config_file:=/home/se113/SLWS/SealienDCN/src/sealien_ctrlpilot_mavlinkbridge/config/sealien_mavlink_rov.yaml \
  -p topic_prefix:=rov \
  -p auto_reload:=true
再启动 ROS 端测试节点：
source install/setup.bash

ros2 run sealien_ctrlpilot_mavlinkbridge rov_mavlink_test_node --ros-args \
  -p config_file:=/home/se113/SLWS/SealienDCN/src/sealien_ctrlpilot_mavlinkbridge/config/sealien_mavlink_rov.yaml \
  -p topic_prefix:=rov \
  -p tx_period_ms:=1000 \
  -p quality_report_period_sec:=5 \
  -p quality_link_timeout_ms:=3000 \
  -p include_heartbeat_tx:=false \
  -p log_quality_report:=true \
  -p safe_mode:=true

## C/C++ 维护要点

### RAII 和 shared_ptr

ROS publisher/subscriber 由 `shared_ptr` 持有。配置重载时清空 `publishers_` 和 `subscriptions_`，旧 Topic 句柄会自动析构并注销。这是 C++ RAII 思想：资源生命周期由对象生命周期管理。

### mutex 和线程安全

本包有两把锁：

- `state_mutex_`：保护 YAML 配置、publisher/subscriber 路由表。
- `socket_mutex_`：保护 UDP socket fd。

分开两把锁可以避免网络 IO 和配置操作互相长时间阻塞。维护时不要随意在持有一把锁时再调用可能拿另一把锁的长流程函数。

### std::optional

`find_incoming_endpoint_locked()` 和 `find_endpoint_for_tx_locked()` 返回 `std::optional<EndpointConfig>`。这比返回空指针或特殊值更明确：可能找到 endpoint，也可能没有合法路由。

### lambda 捕获

发送侧 subscriber 使用 lambda callback：

```cpp
[this, endpoint_name = endpoint.name](Msg::SharedPtr msg) { ... }
```

只捕获 `endpoint.name`，不捕获完整 `EndpointConfig`。这样配置热重载后，callback 会通过 endpoint 名称重新查最新配置，避免继续使用旧 IP、旧端口或旧 `tx` 列表。

### MAVLink C API 和 C++ 混用

MAVLink 生成的是 C 头文件，因此头文件中使用：

```cpp
extern "C" {
#include "mavlink.h"
}
```

这告诉 C++ 编译器按 C ABI 处理 MAVLink 符号，避免名称修饰问题。

### 显式字段映射

`publish_rx_message()` 和发送 callback 中没有使用内存拷贝直接转换 ROS msg 和 MAVLink struct，而是逐字段赋值。这样做更啰嗦，但更安全：

- ROS 字段名可以更贴近业务语义。
- MAVLink 字段名可以严格跟随协议 XML。
- 后续协议字段变更时，编译器更容易暴露遗漏。

## 增加新 MSGID 的维护步骤

1. 更新 `tools/sealien_mavlink.xml`，并运行 `tools/generate_mavlink.sh`。
2. 在 `sealien_ctrlpilot_msgmanagement/msg` 中新增或更新 ROS msg。
3. 将新 msg 加入 `sealien_ctrlpilot_msgmanagement/CMakeLists.txt`。
4. 在 `mavlink_bridge_core.hpp` include 新 msg 头文件。
5. 在 `create_rx_publisher()` 添加接收 publisher 映射。
6. 在 `publish_rx_message()` 添加 MAVLink 到 ROS 的解码映射。
7. 如果该 MSGID 需要 ROS 下发，在 `create_tx_subscription()` 添加 ROS 到 MAVLink 的编码映射。
8. 更新 ROV/TMS YAML 的 endpoint `messages.rx/tx`。
9. 重新编译并做节点启动测试。

## 当前自测命令

```bash
source /opt/ros/jazzy/setup.bash
colcon build --packages-select sealien_ctrlpilot_msgmanagement sealien_ctrlpilot_mavlinkbridge

source install/setup.bash
ros2 run sealien_ctrlpilot_mavlinkbridge rov_mavlink_node
ros2 run sealien_ctrlpilot_mavlinkbridge tms_mavlink_node
```
