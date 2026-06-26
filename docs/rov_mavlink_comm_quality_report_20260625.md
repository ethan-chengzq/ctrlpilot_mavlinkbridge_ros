# ROV MAVLink 三板并发通信质量测试总体报告

## 1. 测试目的

本次测试在 EP101、EP102、EP103 三块 STM32 下位机同时在线的条件下，验证 ROS 中位机 `sealien_ctrlpilot_mavlinkbridge` 与多块下位机之间的 MAVLink UDP 并发通信质量。

测试目标包括：

- 验证 ROS 端同时对三块板进行上行接收与下行发送时的链路稳定性。
- 覆盖高频、低频和状态类消息：
  - 高频 50Hz：EP101 `IMU_DATA#01`、`DVL_DATA#18`，EP102 `THRUSTER_CMD#10`。
  - 低频 1Hz：三块板 `HEARTBEAT#00`。
  - 10Hz 状态/命令类消息：EP101 传感状态、EP102 推进器/灯光/云台/开关命令与状态、EP103 混合 IO/阀控命令与状态。
- 基于 ROS 端总通信质量日志，统计 5s 简报和 60s 详报中的速率、丢包、相邻帧间隔、在线状态与发送失败情况。
- 结合单板测试报告，对三板并发压力下的通信质量进行总体评价。

## 2. 测试对象与环境

| 项目 | 内容 |
| --- | --- |
| 测试日期 | 2026-06-25 |
| ROS 工程 | `sealien_ctrlpilot_mavlinkbridge` |
| STM32 工程 | `sealien-ctrlcore` |
| ROS 主机 IP | `192.168.100.100` |
| EP101 | `nav_sensor_mcu`, sysid `101`, `192.168.100.101:9999` |
| EP102 | `actuator_mcu`, sysid `102`, `192.168.100.102:9999` |
| EP103 | `io_valve_mcu`, sysid `103`, `192.168.100.103:9999` |
| 测试时长 | 约 5 分钟 |
| ROS 原始日志 | `/tmp/rov_mavlink_all_ep_ros_20260625.log` |
| ROS 清洗日志 | `/tmp/rov_mavlink_all_ep_ros_20260625.clean.log` |

本报告参考的单板测试报告：

- `rov_mavlink_ep101_comm_quality_report_20260625.md`
- `rov_mavlink_ep102_comm_quality_report_20260625.md`
- `rov_mavlink_ep103_comm_quality_report_20260625.md`

## 3. 测试前连通性确认

三块板测试前均完成 ICMP 连通性检查：

| 终端 | IP | ping 结果 | RTT avg |
| --- | --- | --- | ---: |
| EP101 | `192.168.100.101` | `3 transmitted, 3 received, 0% packet loss` | 1.367ms |
| EP102 | `192.168.100.102` | `3 transmitted, 3 received, 0% packet loss` | 1.356ms |
| EP103 | `192.168.100.103` | `3 transmitted, 3 received, 0% packet loss` | 1.354ms |

## 4. 测试方法

启动 ROS 端三板并发测试节点：

```bash
source /home/se113/SLWS/SealienDCN/install/setup.bash
ROS_LOG_DIR=/tmp/ros_logs_all_ep_20260625 \
timeout 330 ros2 launch sealien_ctrlpilot_mavlinkbridge rov_mavlink_test.launch.py \
  target_endpoints:=nav_sensor_mcu,actuator_mcu,io_valve_mcu \
  brief_report_period_sec:=5 \
  detail_report_period_sec:=60 \
  publish_rx_mirror_topics:=false \
  publish_per_message_events:=false \
  tx_stats_period_sec:=60
```

清洗 ROS 日志颜色控制字符：

```bash
perl -pe 's/\e\[[0-9;]*m//g' \
  /tmp/rov_mavlink_all_ep_ros_20260625.log \
  > /tmp/rov_mavlink_all_ep_ros_20260625.clean.log
```

## 5. 总体负载概况

三板并发测试目标总频率：

| 方向 | EP101 | EP102 | EP103 | 合计 |
| --- | ---: | ---: | ---: | ---: |
| ROS -> STM32 | 21Hz | 101Hz | 21Hz | 143Hz |
| STM32 -> ROS | 141Hz | 41Hz | 21Hz | 203Hz |
| 双向合计 | 162Hz | 142Hz | 42Hz | 346Hz |

最终 60s 详报显示三块板均在线：

```text
[LinkStatus] online(3/3): nav_sensor_mcu(192.168.100.101:9999), actuator_mcu(192.168.100.102:9999), io_valve_mcu(192.168.100.103:9999)
```

桥接发送统计 `mavlink_bridge_tx_stats` 在最终 60s 窗口中全部为：

- `win_fail=0`
- `win_fail_pct=0.00`
- 各路由累计 `total_fail=0`

## 6. 最终 60s 详报数据

### 6.1 EP101 / `nav_sensor_mcu`

链路状态：`state=UP(OK)`，`rx_age=3ms`，`last_rx_msgid=18`，`link_up/down=1/0`。

| 方向 | 总帧数 | 窗口帧数 | 速率 | missed | loss |
| --- | ---: | ---: | ---: | ---: | ---: |
| ROS -> STM32 | 6300 | 1260/1260 | 21.00/21.00Hz | 0 | 0.00% |
| STM32 -> ROS | 42292 | 8460/8460 | 141.00/141.00Hz | 0 | 0.00% |

| 消息 | 方向 | 窗口帧数 | 速率 | missed | loss | gap avg/min/max |
| --- | --- | ---: | ---: | ---: | ---: | --- |
| `HEARTBEAT#00` | ROS -> STM32 | 60/60 | 1.00/1.00Hz | 0 | 0.00% | 1000.00/999/1001ms |
| `IMU_CALIB#12` | ROS -> STM32 | 600/600 | 10.00/10.00Hz | 0 | 0.00% | 100.00/99/101ms |
| `IMU_CLEAR#13` | ROS -> STM32 | 600/600 | 10.00/10.00Hz | 0 | 0.00% | 100.00/99/101ms |
| `HEARTBEAT#00` | STM32 -> ROS | 60/60 | 1.00/1.00Hz | 0 | 0.00% | 1000.00/999/1001ms |
| `IMU_DATA#01` | STM32 -> ROS | 3000/3000 | 50.00/50.00Hz | 0 | 0.00% | 20.00/18/22ms |
| `VCHECK#05` | STM32 -> ROS | 600/600 | 10.00/10.00Hz | 0 | 0.00% | 100.00/99/101ms |
| `HEIGHT_STATUS#06` | STM32 -> ROS | 600/600 | 10.00/10.00Hz | 0 | 0.00% | 100.00/99/102ms |
| `DEPTH_STATUS#07` | STM32 -> ROS | 600/600 | 10.00/10.00Hz | 0 | 0.00% | 100.00/99/101ms |
| `BME280#08` | STM32 -> ROS | 600/600 | 10.00/10.00Hz | 0 | 0.00% | 100.00/98/101ms |
| `DVL_DATA#18` | STM32 -> ROS | 3000/3000 | 50.00/50.00Hz | 0 | 0.00% | 20.00/19/22ms |

### 6.2 EP102 / `actuator_mcu`

链路状态：`state=UP(OK)`，`rx_age=76ms`，`last_rx_msgid=9`，`link_up/down=1/0`。

| 方向 | 总帧数 | 窗口帧数 | 速率 | missed | loss |
| --- | ---: | ---: | ---: | ---: | ---: |
| ROS -> STM32 | 30300 | 6060/6060 | 101.00/101.00Hz | 0 | 0.00% |
| STM32 -> ROS | 12299 | 2460/2460 | 41.00/41.00Hz | 0 | 0.00% |

| 消息 | 方向 | 窗口帧数 | 速率 | missed | loss | gap avg/min/max |
| --- | --- | ---: | ---: | ---: | ---: | --- |
| `HEARTBEAT#00` | ROS -> STM32 | 60/60 | 1.00/1.00Hz | 0 | 0.00% | 1000.00/999/1001ms |
| `THRUSTER_CMD#10` | ROS -> STM32 | 3000/3000 | 50.00/50.00Hz | 0 | 0.00% | 20.00/19/21ms |
| `THRUSTER_LOCK#11` | ROS -> STM32 | 600/600 | 10.00/10.00Hz | 0 | 0.00% | 100.00/99/101ms |
| `LED_CMD#14` | ROS -> STM32 | 600/600 | 10.00/10.00Hz | 0 | 0.00% | 100.00/99/101ms |
| `GS_CMD#15` | ROS -> STM32 | 600/600 | 10.00/10.00Hz | 0 | 0.00% | 100.00/99/101ms |
| `GS_CFG#16` | ROS -> STM32 | 600/600 | 10.00/10.00Hz | 0 | 0.00% | 100.00/99/101ms |
| `SWITCH_CMD#17` | ROS -> STM32 | 600/600 | 10.00/10.00Hz | 0 | 0.00% | 100.00/99/101ms |
| `HEARTBEAT#00` | STM32 -> ROS | 60/60 | 1.00/1.00Hz | 0 | 0.00% | 1000.00/999/1001ms |
| `THRUSTER_STATUS#02` | STM32 -> ROS | 600/600 | 10.00/10.00Hz | 0 | 0.00% | 100.00/98/101ms |
| `GS_STATUS#03` | STM32 -> ROS | 600/600 | 10.00/10.00Hz | 0 | 0.00% | 100.00/99/102ms |
| `LED_STATUS#04` | STM32 -> ROS | 600/600 | 10.00/10.00Hz | 0 | 0.00% | 100.00/99/101ms |
| `SWITCH_STATUS#09` | STM32 -> ROS | 600/600 | 10.00/10.00Hz | 0 | 0.00% | 100.00/99/101ms |

### 6.3 EP103 / `io_valve_mcu`

链路状态：`state=UP(OK)`，`rx_age=32ms`，`last_rx_msgid=22`，`link_up/down=1/0`。

| 方向 | 总帧数 | 窗口帧数 | 速率 | missed | loss |
| --- | ---: | ---: | ---: | ---: | ---: |
| ROS -> STM32 | 6300 | 1260/1260 | 21.00/21.00Hz | 0 | 0.00% |
| STM32 -> ROS | 6300 | 1260/1260 | 21.00/21.00Hz | 0 | 0.00% |

| 消息 | 方向 | 窗口帧数 | 速率 | missed | loss | gap avg/min/max |
| --- | --- | ---: | ---: | ---: | ---: | --- |
| `HEARTBEAT#00` | ROS -> STM32 | 60/60 | 1.00/1.00Hz | 0 | 0.00% | 1000.00/999/1001ms |
| `MIXED_IO_CMD#19` | ROS -> STM32 | 600/600 | 10.00/10.00Hz | 0 | 0.00% | 100.00/99/101ms |
| `VALVE_CMD#21` | ROS -> STM32 | 600/600 | 10.00/10.00Hz | 0 | 0.00% | 100.00/99/101ms |
| `HEARTBEAT#00` | STM32 -> ROS | 60/60 | 1.00/1.00Hz | 0 | 0.00% | 999.97/999/1001ms |
| `MIXED_IO_DATA#20` | STM32 -> ROS | 600/600 | 10.00/10.00Hz | 0 | 0.00% | 100.00/99/102ms |
| `VALVE_STATUS#22` | STM32 -> ROS | 600/600 | 10.00/10.00Hz | 0 | 0.00% | 100.00/98/101ms |

## 7. 单板测试结果对比

| 终端 | 单板测试结论 | 三板并发最终 60s 结论 |
| --- | --- | --- |
| EP101 | 最终 60s 双向 0 丢包，高频 IMU/DVL 50Hz 稳定 | 最终 60s 双向 0 丢包，141Hz 上行稳定 |
| EP102 | 最终 60s 双向 0 丢包，101Hz 下行稳定 | 最终 60s 双向 0 丢包，101Hz 下行稳定 |
| EP103 | 最终 60s 双向 0 丢包，21Hz 双向稳定 | 最终 60s 双向 0 丢包，21Hz 双向稳定 |

单板和三板并发测试结果一致：三块下位机在当前压力配置下均能保持稳定通信。

## 8. 问题分析

### 8.1 瞬时窗口 missed

全日志异常扫描中发现 EP101 在中段两个 5s 简报窗口出现过轻微 missed：

- `EP101 RX STM32->ROS`：`703/705`，`missed=2`，`loss=0.28%`。
- 对应消息为 `IMU_DATA#01` 和 `DVL_DATA#18`，各 `249/250`，各 `missed=1`，`loss=0.40%`。

该现象没有在最终 60s 详报中持续出现，后续窗口恢复为 0 丢包。结合 gap 仍保持在约 `18-22ms`，判断更可能是 ROS 端 5s 窗口边界、调度抖动或 UDP 接收处理短时抖动导致的瞬时统计损耗，而不是持续链路质量问题。

### 8.2 未发现的问题

本轮三板并发测试未发现以下问题：

- 未发现 `LINK DOWN`。
- 未发现 `state=DOWN`。
- 未发现 endpoint offline。
- 未发现桥接发送失败，最终 `mavlink_bridge_tx_stats` 各路由 `win_fail=0`。
- 未发现 EP102 或 EP103 稳态丢包。
- 未发现三板最终 60s 详报中的非零丢包。

### 8.3 统计显示口径说明

部分 5s 简报可能显示 `window=actual/expected` 中 actual 略大于 expected，这是 expected 采用保守向下取整后的结果，不表示超发异常。判断通信质量时应综合观察：

- `rate/target`
- `missed`
- `loss`
- `gap avg/min/max`
- `link_up/down`
- `mavlink_bridge_tx_stats win_fail`

## 9. 优化建议

- 后续三板长时间稳定性测试建议将测试时长扩展至 30 分钟或 1 小时，观察 EP101 高频上行在长时间窗口中的瞬时 missed 是否偶发。
- 增加 ROS 端系统资源记录，包括 CPU 占用、线程调度延迟、UDP socket receive buffer 使用情况和丢包计数，以便定位 5s 窗口偶发 missed 的真实来源。
- 对测试脚本增加 warm-up 阶段：先启动 ROS 测试并等待 `online(3/3)`，再开始正式统计，减少启动窗口误差。
- 将总体报告中的最终 60s 详报作为主要判据，5s 简报作为瞬时波动观察项，避免单个短窗口误判总体质量。
- 若进入更高压力测试，可优先提高 EP102 `THRUSTER_CMD#10` 至 100Hz，并同步提高 EP101 IMU/DVL 至 100Hz，逐级观察 ROS 主机调度和 STM32 接收能力边界。

## 10. 测试结论

本次 EP101、EP102、EP103 三板并发 MAVLink 通信压力测试通过。

在约 5 分钟三板同时通信条件下：

- 三块板全程保持在线，最终状态 `online(3/3)`。
- 三板最终 60s 详报全部为 `missed=0`、`loss=0.00%`。
- ROS 端桥接发送统计全部 `win_fail=0`。
- 当前并发负载约为 ROS 下行 143Hz、STM32 上行 203Hz、双向合计 346Hz。
- EP101 高频 IMU/DVL、EP102 高频推进器命令、EP103 IO/阀控消息均达到目标频率。

综合单板与三板并发测试结果，当前 ROS 端 `sealien_ctrlpilot_mavlinkbridge` 与 STM32 端 `sealien-ctrlcore` 的 MAVLink 测试通信链路在现有压力配置下具备稳定联调能力，可作为后续多下位机联合调试和更高压力测试的基础版本。
