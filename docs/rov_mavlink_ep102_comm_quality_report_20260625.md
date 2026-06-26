# ROV MAVLink EP102 通信质量测试报告

## 1. 测试目的

本次测试针对 EP102 下位机 `actuator_mcu`，验证 ROS 中位机与 STM32 下位机在 MAVLink UDP 链路下的双向通信质量。

- ROS -> STM32：`HEARTBEAT#00` 1Hz，`THRUSTER_CMD#10` 50Hz，`THRUSTER_LOCK#11` 10Hz，`LED_CMD#14` 10Hz，`GS_CMD#15` 10Hz，`GS_CFG#16` 10Hz，`SWITCH_CMD#17` 10Hz。
- STM32 -> ROS：`HEARTBEAT#00` 1Hz，`THRUSTER_STATUS#02` 10Hz，`GS_STATUS#03` 10Hz，`LED_STATUS#04` 10Hz，`SWITCH_STATUS#09` 10Hz。
- 统计 5s 简报和 60s 详报中的链路状态、丢包、速率、相邻帧间隔 `gap avg/min/max`、身份/消息过滤 drop。

## 2. 测试对象与环境

| 项目 | 内容 |
| --- | --- |
| 测试日期 | 2026-06-25 |
| ROS 工程 | `sealien_ctrlpilot_mavlinkbridge` |
| STM32 工程 | `sealien-ctrlcore` |
| 目标下位机 | EP102 / `actuator_mcu` |
| STM32 system/component | `102/1` |
| STM32 IP/端口 | `192.168.100.102:9999` |
| ROS 主机 IP | `192.168.100.100` |
| 串口 | `/dev/ttyACM0`, 115200 |
| 测试时长 | 约 5 分钟 |
| ROS 原始日志 | `/tmp/rov_mavlink_ep102_ros_20260625_retest.log` |
| ROS 清洗日志 | `/tmp/rov_mavlink_ep102_ros_20260625_retest.clean.log` |
| STM32 原始日志 | `/tmp/rov_mavlink_ep102_stm32_20260625_retest.log` |
| STM32 清洗日志 | `/tmp/rov_mavlink_ep102_stm32_20260625_retest.clean.log` |

## 3. 测试前确认

ROS 工程完成编译检查：

```bash
source /opt/ros/jazzy/setup.bash
colcon build --packages-select sealien_ctrlpilot_mavlinkbridge
```

EP102 网络连通性测试：

```bash
ping -c 5 -W 1 192.168.100.102
```

结果：`5 transmitted, 5 received, 0% packet loss`，RTT `min/avg/max/mdev = 1.359/1.375/1.398/0.015 ms`。

## 4. 测试步骤

1. 清零 STM32 测试统计：

   ```bash
   stty -F /dev/ttyACM0 115200 raw -echo
   printf 'rov_mavtest_reset_stats\r\n' > /dev/ttyACM0
   ```

2. 采集 STM32 串口日志：

   ```bash
   timeout 330 cat /dev/ttyACM0 > /tmp/rov_mavlink_ep102_stm32_20260625_retest.log
   ```

3. 启动 ROS MAVLink 测试节点，仅测试 EP102：

   ```bash
   source /home/se113/SLWS/SealienDCN/install/setup.bash
   ROS_LOG_DIR=/tmp/ros_logs_ep102_20260625_retest \
   timeout 330 ros2 launch sealien_ctrlpilot_mavlinkbridge rov_mavlink_test.launch.py \
     target_endpoints:=actuator_mcu \
     brief_report_period_sec:=5 \
     detail_report_period_sec:=60 \
     publish_rx_mirror_topics:=false \
     publish_per_message_events:=false \
     tx_stats_period_sec:=60
   ```

## 5. 关键测试数据

### 5.1 ROS 端最终 60s 详报

ROS 端链路状态：`online(1/1)`，`state=UP(OK)`，`rx_age=78ms`，`last_rx_msgid=9`，`link_up/down=1/0`。

| 方向 | 总帧数 | 窗口帧数 | 速率 | missed | loss |
| --- | ---: | ---: | ---: | ---: | ---: |
| ROS -> STM32 | 30300 | 6060/6060 | 101.00/101.00Hz | 0 | 0.00% |
| STM32 -> ROS | 12296 | 2460/2460 | 41.00/41.00Hz | 0 | 0.00% |

| 消息 | 方向 | 窗口帧数 | 速率 | missed | loss | gap avg/min/max |
| --- | --- | ---: | ---: | ---: | ---: | --- |
| `HEARTBEAT#00` | ROS -> STM32 | 60/60 | 1.00/1.00Hz | 0 | 0.00% | 1000.00/1000/1000ms |
| `THRUSTER_CMD#10` | ROS -> STM32 | 3000/3000 | 50.00/50.00Hz | 0 | 0.00% | 20.00/20/20ms |
| `THRUSTER_LOCK#11` | ROS -> STM32 | 600/600 | 10.00/10.00Hz | 0 | 0.00% | 100.00/100/100ms |
| `LED_CMD#14` | ROS -> STM32 | 600/600 | 10.00/10.00Hz | 0 | 0.00% | 100.00/100/100ms |
| `GS_CMD#15` | ROS -> STM32 | 600/600 | 10.00/10.00Hz | 0 | 0.00% | 100.00/100/100ms |
| `GS_CFG#16` | ROS -> STM32 | 600/600 | 10.00/10.00Hz | 0 | 0.00% | 100.00/100/100ms |
| `SWITCH_CMD#17` | ROS -> STM32 | 600/600 | 10.00/10.00Hz | 0 | 0.00% | 100.00/100/100ms |
| `HEARTBEAT#00` | STM32 -> ROS | 60/60 | 1.00/1.00Hz | 0 | 0.00% | 1000.00/999/1001ms |
| `THRUSTER_STATUS#02` | STM32 -> ROS | 600/600 | 10.00/10.00Hz | 0 | 0.00% | 100.00/98/102ms |
| `GS_STATUS#03` | STM32 -> ROS | 600/600 | 10.00/10.00Hz | 0 | 0.00% | 100.00/99/101ms |
| `LED_STATUS#04` | STM32 -> ROS | 600/600 | 10.00/10.00Hz | 0 | 0.00% | 100.00/99/101ms |
| `SWITCH_STATUS#09` | STM32 -> ROS | 600/600 | 10.00/10.00Hz | 0 | 0.00% | 100.00/99/101ms |

### 5.2 STM32 端最终 60s 详报

STM32 端链路状态：`state=UP(OK)`，`rx_age=0ms`，`last_rx=- GS_CFG#16`，`link_up/down=1/0`，`drops(identity/not_allowed)=0/0`。

| 方向 | 总帧数 | 窗口帧数 | 速率 | missed | loss |
| --- | ---: | ---: | ---: | ---: | ---: |
| STM32 -> ROS | 13071 | 2464/2460 | 40.99/41.00Hz | 0 | 0.00% |
| ROS -> STM32 | 30313 | 6070/6064 | 101.00/101.00Hz | 0 | 0.00% |

| 消息 | 方向 | 窗口帧数 | 速率 | missed | loss | gap avg/min/max |
| --- | --- | ---: | ---: | ---: | ---: | --- |
| `HEARTBEAT#00` | STM32 -> ROS | 60/60 | 0.99/1.00Hz | 0 | 0.00% | 1000.00/1000/1000ms |
| `THRUSTER_STATUS#02` | STM32 -> ROS | 601/600 | 10.00/10.00Hz | 0 | 0.00% | 100.00/100/100ms |
| `GS_STATUS#03` | STM32 -> ROS | 601/600 | 10.00/10.00Hz | 0 | 0.00% | 100.00/100/100ms |
| `LED_STATUS#04` | STM32 -> ROS | 601/600 | 10.00/10.00Hz | 0 | 0.00% | 100.00/100/100ms |
| `SWITCH_STATUS#09` | STM32 -> ROS | 601/600 | 10.00/10.00Hz | 0 | 0.00% | 100.00/100/100ms |
| `HEARTBEAT#00` | ROS -> STM32 | 60/60 | 0.99/1.00Hz | 0 | 0.00% | 1000.01/999/1001ms |
| `THRUSTER_CMD#10` | ROS -> STM32 | 3005/3004 | 50.00/50.00Hz | 0 | 0.00% | 20.00/19/21ms |
| `THRUSTER_LOCK#11` | ROS -> STM32 | 601/600 | 10.00/10.00Hz | 0 | 0.00% | 100.00/99/101ms |
| `LED_CMD#14` | ROS -> STM32 | 601/600 | 10.00/10.00Hz | 0 | 0.00% | 100.00/99/101ms |
| `GS_CMD#15` | ROS -> STM32 | 601/600 | 10.00/10.00Hz | 0 | 0.00% | 100.00/99/101ms |
| `GS_CFG#16` | ROS -> STM32 | 601/600 | 10.00/10.00Hz | 0 | 0.00% | 100.00/99/101ms |
| `SWITCH_CMD#17` | ROS -> STM32 | 601/600 | 10.00/10.00Hz | 0 | 0.00% | 100.00/99/101ms |

## 6. 异常扫描与问题定位

对 ROS 与 STM32 日志执行关键异常扫描：

- 未发现 `LINK DOWN`。
- 未发现 `state=DOWN`。
- 未发现身份过滤或消息过滤 drop，`drops(identity/not_allowed)=0/0`。
- ROS 侧未发现非零 missed/loss。
- STM32 侧仅在测试早期命中两处非零 missed：
  - 首个 5s 简报：`EP102 RX ROS->STM32` 为 `499/505`，`missed=6`，`loss=1.18%`。
  - 首个 60s 详报：`EP102 RX ROS->STM32` 为 `6053/6060`，`missed=7`，`loss=0.11%`。

排查结论：

- 非零 missed 只出现在测试启动初期，后续最终 60s 详报及后半段 5s 简报均恢复为 `missed=0`、`loss=0.00%`。
- 本次流程中先通过串口清零 STM32 统计，再启动 ROS launch；STM32 的首个统计窗口会覆盖 ROS 节点加载、UDP socket 创建和链路上线前的短暂空窗，因此 expected 已开始累计但 ROS 尚未完整发送。
- 稳态阶段 ROS 与 STM32 双端统计一致，双向链路无丢包、无断链、无 drop。
- 因此早期 missed 判断为测试流程 warm-up 窗口误差，不属于 EP102 稳态通信质量问题。

本轮未发现需要继续修改 ROS 或 STM32 源码的新增设计缺陷。当前通信测试源码的 endpoint 独立窗口、expected 向下取整、gap 统计和日志格式在 EP102 稳态窗口下表现正常。

## 7. 测试结果

EP102 在本轮约 5 分钟测试中通信质量满足预期：

- ROS -> STM32 下行链路目标 101Hz，最终 60s 窗口 0 丢包。
- STM32 -> ROS 上行链路目标 41Hz，最终 60s 窗口 0 丢包。
- 高频 `THRUSTER_CMD#10` 达到 50Hz，ROS 侧 gap 稳定为 20ms，STM32 接收侧 gap 约 19-21ms。
- 10Hz 命令和状态类消息 gap 稳定在 99-101ms。
- 1Hz 心跳 gap 稳定在 999-1001ms。
- 全程链路保持 `UP(OK)`，无断链计数增加。

## 8. 后续优化建议

- 正式测试流程建议调整为：先启动 ROS 测试节点并等待 EP102 `UP(OK)`，再通过串口执行 `rov_mavtest_reset_stats`，随后开始计时采集正式 5 分钟数据。
- 若希望在程序层面进一步降低误读，可增加 `warmup_report_skip_sec` 参数，在测试节点和 STM32 测试固件中对启动后的第一个 5s 窗口只打印 `WARMUP` 标识，不纳入正式质量结论。
- 三板联测时建议重点观察 EP102 的 101Hz 下行负载叠加 EP101 高频上行后，ROS 主机 UDP socket buffer、CPU 调度和 STM32 RX 线程是否仍保持 0 丢包。
- 若要继续提高压力，可优先将 `THRUSTER_CMD#10` 从 50Hz 提升到 100Hz，观察 STM32 接收侧 `gap`、`missed` 和 UDP buffer drop 是否出现边界变化。
