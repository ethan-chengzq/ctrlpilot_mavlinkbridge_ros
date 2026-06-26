# ROV MAVLink EP103 通信质量测试报告

## 1. 测试目的

本次测试针对 EP103 下位机 `io_valve_mcu`，验证 ROS 中位机与 STM32 下位机在 MAVLink UDP 链路下的双向通信质量。测试覆盖：

- ROS -> STM32：`HEARTBEAT#00` 1Hz，`MIXED_IO_CMD#19` 10Hz，`VALVE_CMD#21` 10Hz。
- STM32 -> ROS：`HEARTBEAT#00` 1Hz，`MIXED_IO_DATA#20` 10Hz，`VALVE_STATUS#22` 10Hz。
- 5s 简报和 60s 详报中的丢包、速率、link up/down、drop、相邻帧间隔 `gap avg/min/max`。

## 2. 测试对象与环境

| 项目 | 内容 |
| --- | --- |
| 测试日期 | 2026-06-25 |
| ROS 工程 | `sealien_ctrlpilot_mavlinkbridge` |
| STM32 工程 | `sealien-ctrlcore` |
| 目标下位机 | EP103 / `io_valve_mcu` |
| STM32 system/component | `103/1` |
| STM32 IP/端口 | `192.168.100.103:9999` |
| ROS 主机 IP | `192.168.100.100` |
| 串口 | `/dev/ttyACM0`, 115200 |
| 测试时长 | 约 5 分钟 |
| ROS 日志 | `/tmp/rov_mavlink_ep103_ros_20260625_final_floor.log` |
| STM32 日志 | `/tmp/rov_mavlink_ep103_stm32_20260625_final_floor.log` |

## 3. 测试前修复

本次复测前完成以下修复：

- ROS 测试节点的通信质量窗口改为按 endpoint 独立维护，避免多 STM32 联测时后上线端点被全局窗口误算。
- STM32 测试固件通过 `config/task.py` 显式注入 `ROV_MAVTEST_ACTIVE_ENDPOINT=103U`，并将 `RT_LWIP_IPADDR` 对齐为 `192.168.100.103`。
- ROS 与 STM32 两端 expected 帧数从四舍五入改为保守向下取整，避免 5.03s、60.01s 等非整数窗口误报丢包。

说明：修复后日志中的 `window=actual/expected` 可能出现 actual 略大于 expected，这是非整数窗口下的保守统计口径，不表示超发异常；实际速率和 `gap` 仍按真实采样计算。

## 4. 测试步骤

1. 编译 ROS 测试节点：

   ```bash
   source /opt/ros/jazzy/setup.bash
   colcon build --packages-select sealien_ctrlpilot_mavlinkbridge
   ```

2. 编译并烧录 EP103 STM32 固件：

   ```bash
   source /home/se113/SLWS/CtrlCore/sealien-ctrlcore/.venv/bin/activate
   cd /home/se113/SLWS/CtrlCore/sealien-ctrlcore/target/stm32/stm32h743-SLControlBoard
   scons -j16
   pyocd flash --target stm32h743xx --base-address 0x08020000 Sealien-CtrlCore_SLControlBoard.bin
   pyocd reset --target stm32h743xx --method hw
   ```

3. 验证 EP103 网络连通性：

   ```bash
   ping -c 5 -W 1 192.168.100.103
   ```

   结果：`5 transmitted, 5 received, 0% packet loss`，RTT 平均约 `1.387ms`。

4. 清零 STM32 测试统计并采集串口日志：

   ```bash
   stty -F /dev/ttyACM0 115200 raw -echo
   printf 'rov_mavtest_reset_stats\r\n' > /dev/ttyACM0
   timeout 330 cat /dev/ttyACM0 > /tmp/rov_mavlink_ep103_stm32_20260625_final_floor.log
   ```

5. 启动 ROS MAVLink 测试：

   ```bash
   source /home/se113/SLWS/SealienDCN/install/setup.bash
   ROS_LOG_DIR=/tmp/ros_logs_ep103_20260625_final_floor \
   timeout 330 ros2 launch sealien_ctrlpilot_mavlinkbridge rov_mavlink_test.launch.py \
     target_endpoints:=io_valve_mcu \
     brief_report_period_sec:=5 \
     detail_report_period_sec:=60 \
     publish_rx_mirror_topics:=false \
     publish_per_message_events:=false \
     tx_stats_period_sec:=60
   ```

## 5. 关键测试数据

### 5.1 ROS 端最终 60s 详报

| 方向 | 总帧数 | 窗口帧数 | 速率 | missed | loss |
| --- | ---: | ---: | ---: | ---: | ---: |
| ROS -> STM32 | 6300 | 1260/1257 | 21.00/21.00Hz | 0 | 0.00% |
| STM32 -> ROS | 6300 | 1260/1257 | 21.00/21.00Hz | 0 | 0.00% |

| 消息 | 方向 | 窗口帧数 | 速率 | missed | loss | gap avg/min/max |
| --- | --- | ---: | ---: | ---: | ---: | --- |
| `HEARTBEAT#00` | ROS -> STM32 | 60/59 | 1.00/1.00Hz | 0 | 0.00% | 1000.00/1000/1000ms |
| `MIXED_IO_CMD#19` | ROS -> STM32 | 600/599 | 10.00/10.00Hz | 0 | 0.00% | 100.00/100/100ms |
| `VALVE_CMD#21` | ROS -> STM32 | 600/599 | 10.00/10.00Hz | 0 | 0.00% | 100.00/100/100ms |
| `HEARTBEAT#00` | STM32 -> ROS | 60/59 | 1.00/1.00Hz | 0 | 0.00% | 999.98/999/1001ms |
| `MIXED_IO_DATA#20` | STM32 -> ROS | 600/599 | 10.00/10.00Hz | 0 | 0.00% | 100.00/99/101ms |
| `VALVE_STATUS#22` | STM32 -> ROS | 600/599 | 10.00/10.00Hz | 0 | 0.00% | 100.00/99/101ms |

ROS 端链路状态：`online(1/1)`，`state=UP(OK)`，`link_up/down=1/0`。

### 5.2 STM32 端最终 60s 详报

| 方向 | 总帧数 | 窗口帧数 | 速率 | missed | loss |
| --- | ---: | ---: | ---: | ---: | ---: |
| STM32 -> ROS | 6732 | 1260/1260 | 20.99/21.00Hz | 0 | 0.00% |
| ROS -> STM32 | 6303 | 1260/1260 | 20.99/21.00Hz | 0 | 0.00% |

| 消息 | 方向 | 窗口帧数 | 速率 | missed | loss | gap avg/min/max |
| --- | --- | ---: | ---: | ---: | ---: | --- |
| `HEARTBEAT#00` | STM32 -> ROS | 60/60 | 0.99/1.00Hz | 0 | 0.00% | 1000.00/1000/1000ms |
| `MIXED_IO_DATA#20` | STM32 -> ROS | 600/600 | 9.99/10.00Hz | 0 | 0.00% | 100.00/100/100ms |
| `VALVE_STATUS#22` | STM32 -> ROS | 600/600 | 9.99/10.00Hz | 0 | 0.00% | 100.00/100/100ms |
| `HEARTBEAT#00` | ROS -> STM32 | 60/60 | 0.99/1.00Hz | 0 | 0.00% | 1000.01/1000/1001ms |
| `MIXED_IO_CMD#19` | ROS -> STM32 | 600/600 | 9.99/10.00Hz | 0 | 0.00% | 100.00/99/101ms |
| `VALVE_CMD#21` | ROS -> STM32 | 600/600 | 9.99/10.00Hz | 0 | 0.00% | 100.00/99/101ms |

STM32 端链路状态：`state=UP(OK)`，`link_up/down=1/0`，`drops(identity/not_allowed)=0/0`。

### 5.3 全程异常扫描

对 ROS 与 STM32 清洗后的日志执行异常扫描：

- 未发现 `LINK DOWN`。
- 未发现 `state=DOWN`。
- 未发现非零 `missed`。
- 未发现非零 `loss`。
- 未发现 `drops(identity/not_allowed)` 非零。

## 6. 结果分析

EP103 在本轮 5 分钟测试中表现稳定。ROS 和 STM32 两端对同一链路的观测结果一致：

- 双向总目标速率均为 21Hz，包含 1Hz 心跳和两路 10Hz 业务消息。
- 最终 60s 窗口中两端均未统计到丢包。
- 10Hz 消息相邻帧间隔集中在 99-101ms，心跳集中在 999-1001ms。
- 整个测试期间无断链、无非法源身份 drop、无不允许 MSGID drop。

ROS 侧最终 60s 详报中 `window=1260/1257` 是保守 expected 口径造成的显示差异：该窗口实际时长略小于 60s 时，expected 采用向下取整以避免假丢包；实际速率仍为 21.00/21.00Hz，且 missed/loss 为 0。

## 7. 问题汇总

本轮最终测试未发现 EP103 通信质量问题。

已在测试前修复的问题：

- 修复多端点统计窗口全局共享导致后上线端点误报丢包的问题。
- 修复 expected 帧数四舍五入导致非整数窗口误报丢包的问题。
- 修复 STM32 EP103 固件构建身份/IP 配置不显式、容易烧错角色的问题。

## 8. 后续优化建议

- 将 `window=actual/expected` 的 expected 字段命名优化为 `min_expected` 或新增 `target_rate` 单独列，避免保守 expected 显示成 actual 大于 expected 时产生阅读歧义。
- 后续三板联测时建议保持本次按 endpoint 独立窗口的统计逻辑，并在报告中分别列出 EP101、EP102、EP103 的独立 60s 详报。
- 若需要验证极限负载，可在当前 EP103 21Hz 基线通过后，再叠加 EP101/EP102 同时在线压力测试，观察 ROS 主机 CPU、UDP socket buffer、STM32 RX 线程优先级对 jitter 的影响。
