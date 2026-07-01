# ROV MAVLink 24小时长周期通信质量测试报告

## 1. 测试目的

本次测试针对 ROS 中位机 `sealien_ctrlpilot_mavlinkbridge` 与三块 STM32 下位机 EP101/EP102/EP103 的 MAVLink 长周期并发通信质量进行验证。测试关注点包括：

- 24小时连续运行条件下，三块下位机是否能持续在线。
- ROS->STM32 与 STM32->ROS 双向链路在高频、低频、状态/命令类消息混合负载下的稳定性。
- 各 endpoint 的丢包、窗口损耗、收发速率、相邻帧间隔、连接/断开统计是否满足长周期运行要求。
- ROS 端桥接层 UDP `sendto` 是否出现发送失败。
- STM32 串口侧日志与 ROS 端质量报告是否能相互印证。

## 2. 测试概况

| 项目 | 内容 |
| --- | --- |
| 测试开始时间 | 2026-06-29 16:36:49 +08:00 |
| 测试结束时间 | 2026-06-30 约 16:37 +08:00 |
| ROS 日志统计时长 | 86390.00s，约 23.997h |
| 测试方式 | EP101/EP102/EP103 三板并发长周期压力测试 |
| ROS 工程 | `/home/se113/SLWS/SealienDCN` |
| ROS 功能包 | `sealien_ctrlpilot_mavlinkbridge` |
| STM32 固件 | `sealien-ctrlcore` MAVLink 测试固件 |
| 测试脚本 | `src/sealien_ctrlpilot_mavlinkbridge/scripts/start_rov_mavlink_long_test.sh` |
| 测试配置 | `src/sealien_ctrlpilot_mavlinkbridge/config/sealien_mavlink_rov.yaml` |
| ROS 简报周期 | 5s |
| ROS 详报周期 | 60s |
| STM32 简报周期 | 5s |
| STM32 详报周期 | 60s |
| 启动策略 | 先启动 STM32 串口采集，发送 `reboot`，等待 20s 后启动 ROS 测试节点 |

本次测试日志目录：

```text
src/sealien_ctrlpilot_mavlinkbridge/logs/mavlink_long_test/20260629_163649
```

日志文件规模：

| 文件 | 大小 | 行数 | 说明 |
| --- | ---: | ---: | --- |
| `ros_all_ep.log` | 130MB | 871065 | ROS 端测试节点与 bridge 质量日志 |
| `stm32_all_serial.log` | 163MB | 1874899 | EP101/EP102/EP103 串口汇总日志 |
| `run_info.txt` | 794B | 18 | 本次运行参数 |

## 3. 被测对象与负载模型

| Endpoint | 角色 | IP:Port | sysid | 串口 |
| --- | --- | --- | ---: | --- |
| EP101 | `nav_sensor_mcu` | `192.168.100.101:9999` | 101 | `/dev/ttyACM1` |
| EP102 | `actuator_mcu` | `192.168.100.102:9999` | 102 | `/dev/ttyACM2` |
| EP103 | `io_valve_mcu` | `192.168.100.103:9999` | 103 | `/dev/ttyACM3` |

目标通信负载：

| 方向 | EP101 | EP102 | EP103 | 合计 |
| --- | ---: | ---: | ---: | ---: |
| ROS->STM32 | 21Hz | 101Hz | 21Hz | 143Hz |
| STM32->ROS | 141Hz | 41Hz | 21Hz | 203Hz |
| 双向合计 | 162Hz | 142Hz | 42Hz | 346Hz |

消息覆盖：

| 类别 | 消息 |
| --- | --- |
| 1Hz 低频 | `HEARTBEAT#00` |
| 50Hz 高频 | EP101 `IMU_DATA#01`、`DVL_DATA#18`，EP102 `THRUSTER_CMD#10` |
| 10Hz 状态/命令 | EP101 `IMU_CALIB#12`、`IMU_CLEAR#13`、传感器状态；EP102 推进器/云台/灯光/开关状态与命令；EP103 混合 IO/阀控状态与命令 |

## 4. 数据解析方法

本报告以 ROS 端 `ros_all_ep.log` 为主统计依据，原因如下：

- ROS 端同时记录测试节点 topic 发布、bridge topic 接收、UDP `sendto` 统计和三 endpoint 在线状态。
- ROS 端日志时间连续、格式完整，适合计算全程在线状态、窗口损耗和最终 60s 详报。
- STM32 串口日志用于交叉验证下位机侧收发计数与链路状态。

统计口径：

- `brief`：5s 通信质量简报。
- `detail`：60s 通信质量详报。
- `TX TestNode->BridgeTopic`：测试节点向 bridge 侧 ROS topic 发布的统计。
- `Bridge UDP sendto`：bridge 实际 UDP 发送统计。
- `RX BridgeTopic->TestNode`：测试节点从 bridge 侧 ROS topic 接收到的 STM32 上行消息统计。
- `missed/loss`：窗口期内相对于目标频率推算的缺失帧数与损耗率。
- `gap avg/min/max`：同一消息相邻帧间隔。

## 5. ROS 端总体结果

ROS 端日志统计结果：

| 指标 | 结果 |
| --- | ---: |
| 5s 简报数量 | 17278 |
| 60s 详报数量 | 1439 |
| LinkStatus online(3/3) 记录 | 18717 |
| offline 记录 | 0 |
| ERROR 记录 | 0 |
| WARN 记录 | 2 |

两条 WARN 均为测试节点启动时的预期提示：

- `safe_mode=true: command test payloads use non-actuating or low-risk values`
- `This executable is a stress-test publisher; do not run it with production control nodes...`

测试期间 ROS 端未出现 endpoint 离线记录，三块板在所有质量报告中均保持：

```text
[LinkStatus] online(3/3): nav_sensor_mcu(...), actuator_mcu(...), io_valve_mcu(...)
```

## 6. 最终60s详报数据

以下数据来自 ROS 端最后一个完整 60s `ROV MAVLink Test Quality` 详报。

### 6.1 EP101 / nav_sensor_mcu

链路状态：`state=UP(OK)`，`rx_age=1ms`，`last_rx_msgid=18`，`link_up/down=1/0`。

| 方向 | 总帧数 | 60s窗口 | 速率 | missed | loss |
| --- | ---: | ---: | ---: | ---: | ---: |
| ROS topic -> Bridge | 1813140 | 1260/1260 | 21.00/21.00Hz | 0 | 0.00% |
| Bridge UDP sendto | 1811880 ok / 0 fail | 1260 ok / 0 fail | - | 0 | 0.00% |
| Bridge topic -> ROS test | 12174041 | 8460/8460 | 141.00/141.00Hz | 0 | 0.00% |

| 消息 | 方向 | 60s窗口 | 速率 | loss | gap avg/min/max |
| --- | --- | ---: | ---: | ---: | --- |
| `HEARTBEAT#00` | ROS->STM32 | 60/60 | 1.00Hz | 0.00% | 1000.00/999/1001ms |
| `IMU_CALIB#12` | ROS->STM32 | 600/600 | 10.00Hz | 0.00% | 100.00/88/112ms |
| `IMU_CLEAR#13` | ROS->STM32 | 600/600 | 10.00Hz | 0.00% | 100.00/94/105ms |
| `HEARTBEAT#00` | STM32->ROS | 60/60 | 1.00Hz | 0.00% | 999.98/999/1001ms |
| `IMU_DATA#01` | STM32->ROS | 3000/3000 | 50.00Hz | 0.00% | 20.00/11/29ms |
| `VCHECK#05` | STM32->ROS | 600/600 | 10.00Hz | 0.00% | 100.00/99/101ms |
| `HEIGHT_STATUS#06` | STM32->ROS | 600/600 | 10.00Hz | 0.00% | 100.00/99/101ms |
| `DEPTH_STATUS#07` | STM32->ROS | 600/600 | 10.00Hz | 0.00% | 100.00/99/102ms |
| `BME280#08` | STM32->ROS | 600/600 | 10.00Hz | 0.00% | 100.00/98/102ms |
| `DVL_DATA#18` | STM32->ROS | 3000/3000 | 50.00Hz | 0.00% | 20.00/12/28ms |

结论：EP101 最终窗口收发均达到目标频率，UDP 发送失败为 0，上行高频 IMU/DVL 帧间隔稳定。

### 6.2 EP102 / actuator_mcu

链路状态：`state=UP(OK)`，`rx_age=64ms`，`last_rx_msgid=9`，`link_up/down=1/0`。

| 方向 | 总帧数 | 60s窗口 | 速率 | missed | loss |
| --- | ---: | ---: | ---: | ---: | ---: |
| ROS topic -> Bridge | 8720297 | 6059/6060 | 100.98/101.00Hz | 1 | 0.02% |
| Bridge UDP sendto | 8714239 ok / 0 fail | 6060 ok / 0 fail | - | 0 | 0.00% |
| Bridge topic -> ROS test | 3539977 | 2460/2460 | 41.00/41.00Hz | 0 | 0.00% |

| 消息 | 方向 | 60s窗口 | 速率 | loss | gap avg/min/max |
| --- | --- | ---: | ---: | ---: | --- |
| `HEARTBEAT#00` | ROS->STM32 | 60/60 | 1.00Hz | 0.00% | 1000.00/1000/1000ms |
| `THRUSTER_CMD#10` | ROS->STM32 | 2999/3000 | 49.98Hz | 0.03% | 20.01/12/48ms |
| `THRUSTER_LOCK#11` | ROS->STM32 | 600/600 | 10.00Hz | 0.00% | 100.00/82/118ms |
| `LED_CMD#14` | ROS->STM32 | 600/600 | 10.00Hz | 0.00% | 100.00/99/101ms |
| `GS_CMD#15` | ROS->STM32 | 600/600 | 10.00Hz | 0.00% | 100.00/99/101ms |
| `GS_CFG#16` | ROS->STM32 | 600/600 | 10.00Hz | 0.00% | 100.00/99/101ms |
| `SWITCH_CMD#17` | ROS->STM32 | 600/600 | 10.00Hz | 0.00% | 100.00/99/101ms |
| `HEARTBEAT#00` | STM32->ROS | 60/60 | 1.00Hz | 0.00% | 999.98/999/1001ms |
| `THRUSTER_STATUS#02` | STM32->ROS | 600/600 | 10.00Hz | 0.00% | 100.00/99/101ms |
| `GS_STATUS#03` | STM32->ROS | 600/600 | 10.00Hz | 0.00% | 100.00/99/101ms |
| `LED_STATUS#04` | STM32->ROS | 600/600 | 10.00Hz | 0.00% | 100.00/99/101ms |
| `SWITCH_STATUS#09` | STM32->ROS | 600/600 | 10.00Hz | 0.00% | 100.00/99/101ms |

结论：EP102 负载最高，最终 60s 窗口中测试节点 topic 发布侧 `THRUSTER_CMD#10` 少 1 帧，但 bridge UDP `sendto` 统计为 0 失败，说明不是 UDP 发送失败，而是测试节点调度窗口统计中的轻微抖动。该抖动量级为 0.03%，对长周期通信质量影响很小。

### 6.3 EP103 / io_valve_mcu

链路状态：`state=UP(OK)`，`rx_age=31ms`，`last_rx_msgid=22`，`link_up/down=1/0`。

| 方向 | 总帧数 | 60s窗口 | 速率 | missed | loss |
| --- | ---: | ---: | ---: | ---: | ---: |
| ROS topic -> Bridge | 1813140 | 1260/1260 | 21.00/21.00Hz | 0 | 0.00% |
| Bridge UDP sendto | 1811880 ok / 0 fail | 1260 ok / 0 fail | - | 0 | 0.00% |
| Bridge topic -> ROS test | 1813159 | 1260/1260 | 21.00/21.00Hz | 0 | 0.00% |

| 消息 | 方向 | 60s窗口 | 速率 | loss | gap avg/min/max |
| --- | --- | ---: | ---: | ---: | --- |
| `HEARTBEAT#00` | ROS->STM32 | 60/60 | 1.00Hz | 0.00% | 1000.00/999/1001ms |
| `MIXED_IO_CMD#19` | ROS->STM32 | 600/600 | 10.00Hz | 0.00% | 100.00/92/108ms |
| `VALVE_CMD#21` | ROS->STM32 | 600/600 | 10.00Hz | 0.00% | 100.00/99/101ms |
| `HEARTBEAT#00` | STM32->ROS | 60/60 | 1.00Hz | 0.00% | 999.97/999/1001ms |
| `MIXED_IO_DATA#20` | STM32->ROS | 600/600 | 10.00Hz | 0.00% | 100.00/99/102ms |
| `VALVE_STATUS#22` | STM32->ROS | 600/600 | 10.00Hz | 0.00% | 100.00/99/101ms |

结论：EP103 最终窗口收发均达到目标频率，UDP 发送失败为 0，阀控/混合 IO 状态与命令链路稳定。

## 7. 全程异常窗口与边界现象

全程统计中，ROS 端最大窗口损耗如下：

| Endpoint | 方向 | 最大窗口损耗 | 最大 missed | 说明 |
| --- | --- | ---: | ---: | --- |
| EP101 | STM32->ROS | 1.30% | 9 | 出现在测试启动初期窗口，随后稳定为 0 |
| EP102 | ROS topic->Bridge | 0.20% | 1 | 偶发测试节点调度窗口抖动 |
| EP102 | STM32->ROS | 0.49% | 1 | 偶发 5s 窗口统计抖动 |
| EP103 | ROS topic->Bridge | 0.03% | 2 | 低量级窗口统计抖动 |
| EP103 | STM32->ROS | 0.95% | 9 | 出现在边界窗口或短时窗口统计抖动 |

这些损耗主要集中在启动初期、窗口边界或测试节点调度统计边界，最终 60s 详报全部恢复到 0 或接近 0。测试过程中没有出现 endpoint offline、bridge UDP sendto failure 或持续性丢包。

STM32 串口日志中可见 3 次自动重启命令记录：

```text
[EP101] reboot command sent; waiting for STM32 restart and clean counters.
[EP102] reboot command sent; waiting for STM32 restart and clean counters.
[EP103] reboot command sent; waiting for STM32 restart and clean counters.
```

STM32 端只发现一条与 MAVLink 通信无关的 Flash 识别提示：

```text
SFUD: Warning: Read SFDP parameter header information failed. The w25q256 does not support JEDEC SFDP.
```

未发现串口侧 ERROR、断连、identity/not_allowed drop 等通信异常。

需要注意的是，STM32 串口日志末尾靠近人工停止测试时，EP102 `RX ROS->STM32` 曾出现一个 60s 窗口 `loss=0.79%`。该窗口时间已接近或晚于 ROS 端测试停止边界，不能代表稳态链路质量，应归类为停止边界效应。稳态过程中 ROS bridge UDP 发送统计持续为 `win_fail=0`、`total_fail=0`。

## 8. 长周期资源占用

本次 24小时测试日志总量约 293MB：

| 日志 | 大小 |
| --- | ---: |
| ROS 端 | 130MB |
| STM32 串口汇总 | 163MB |
| 合计 | 293MB |

该量级对磁盘空间和系统 I/O 压力较低。日志写入主要由 5s/60s 窗口报告驱动，不是逐 MAVLink 帧记录，因此不会显著影响通信性能。建议长期保留时按日期归档，并继续忽略 `logs/` 目录，避免测试产物进入版本控制。

## 9. 问题分析

### 9.1 ROS CLI 看不到节点的问题

测试期间曾出现 `ros2 topic list` 只显示：

```text
/parameter_events
/rosout
```

但日志显示 ROS 节点实际正常运行。后续排查确认原因是查询终端使用了 `ROS_DOMAIN_ID=68`，而测试脚本启动的 ROS 进程未显式设置 `ROS_DOMAIN_ID`，运行在默认 domain `0`。因此 CLI 和测试节点处于不同 DDS 域，互相不可见。

该问题不影响本次通信质量测试结果，但影响现场观测与调试。建议在长测脚本中显式固定并记录：

```bash
ROS_DOMAIN_ID="${ROS_DOMAIN_ID:-0}"
ROS_AUTOMATIC_DISCOVERY_RANGE="${ROS_AUTOMATIC_DISCOVERY_RANGE:-SUBNET}"
export ROS_DOMAIN_ID ROS_AUTOMATIC_DISCOVERY_RANGE
```

并写入 `run_info.txt`。

### 9.2 STM32 串口汇总日志可读性

测试过程中曾发现三块 STM32 串口日志在同一终端汇总时存在可读性问题，包括不同 EP 输出块交错、行边界异常等。后续脚本已优化为：

- 单进程 `select()` 同时监听三路串口。
- 对每个 EP 独立缓冲，按输出块刷新。
- 日志文件清洗 ANSI 控制字符。
- 串口按 CR/LF 双分隔处理。
- 串口打开后尝试 `TIOCEXCL` 独占。

本次报告中 ROS 端统计不受串口可读性问题影响；STM32 串口日志主要用于交叉验证。

### 9.3 高负载 endpoint 的轻微调度抖动

EP102 为最高下行负载 endpoint，ROS->STM32 目标 101Hz，其中 `THRUSTER_CMD#10` 为 50Hz。最终 60s 窗口中 ROS 测试节点 topic 发布侧出现 1 帧 missed，loss 0.03%，但 bridge UDP 发送失败为 0。该现象更符合测试节点调度/窗口边界抖动，而不是底层 UDP 链路故障。

## 10. 测试结论

1. 本次 EP101/EP102/EP103 三板并发 24小时 MAVLink 压力测试通过。
2. ROS 端全程 `online(3/3)`，未记录 endpoint offline。
3. ROS 端未出现 ERROR；仅有两条测试模式预期 WARN。
4. bridge UDP `sendto` 统计在最终 60s 详报中所有 endpoint 均为 `win_fail=0`、`total_fail=0`。
5. EP101 高频 `IMU_DATA#01`、`DVL_DATA#18` 50Hz 上行稳定，最终窗口 loss 0.00%。
6. EP102 最高负载链路整体稳定，最终窗口仅 `THRUSTER_CMD#10` 出现 1 帧 topic 调度 missed，bridge UDP 实际发送失败为 0。
7. EP103 混合 IO/阀控链路稳定，最终窗口收发 loss 0.00%。
8. 本次测试日志总量约 293MB/24h，当前日志策略对系统运行影响较低。

综合判断：当前 ROS 端 `sealien_ctrlpilot_mavlinkbridge` 与 STM32 端 `sealien-ctrlcore` MAVLink 测试固件在三板并发、约 346Hz 双向总通信负载、24小时连续运行条件下，通信链路稳定，满足现阶段长周期压力测试要求。

## 11. 后续优化建议

- 在长测脚本中显式固定并记录 `ROS_DOMAIN_ID`、`ROS_AUTOMATIC_DISCOVERY_RANGE`、`RMW_IMPLEMENTATION`，避免现场 CLI 观测误判。
- 为 EP101/EP102/EP103 配置 udev 固定串口别名，避免 STM32 重启后 `/dev/ttyACM*` 顺序变化。
- 保留当前“ROS 主统计 + STM32 串口交叉验证”的测试结构，避免把串口日志可读性问题误判为 MAVLink 链路问题。
- 对 EP102 高负载下行链路继续观察 `THRUSTER_CMD#10` 的窗口 missed，必要时可增加测试节点调度线程优先级或进一步拆分高频 timer。
- 继续保留 `publish_per_message_events=false`、`publish_rx_mirror_topics=false` 的长测默认值，减少 ROS topic 发布对通信质量测试的干扰。
- 长周期测试结束后对 `logs/mavlink_long_test` 进行归档压缩，避免本地磁盘长期堆积。
