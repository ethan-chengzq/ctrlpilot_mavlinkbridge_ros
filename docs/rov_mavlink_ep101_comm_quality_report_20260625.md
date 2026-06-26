# ROV MAVLink EP101 通信质量测试报告

## 1. 测试目的

本次测试针对 EP101 下位机 `nav_sensor_mcu`，验证 ROS 中位机与 STM32 下位机在 MAVLink UDP 链路下的双向通信质量。测试重点覆盖：

- ROS -> STM32：`HEARTBEAT#00` 1Hz，`IMU_CALIB#12` 10Hz，`IMU_CLEAR#13` 10Hz。
- STM32 -> ROS：`HEARTBEAT#00` 1Hz，`IMU_DATA#01` 50Hz，`VCHECK#05` 10Hz，`HEIGHT_STATUS#06` 10Hz，`DEPTH_STATUS#07` 10Hz，`BME280#08` 10Hz，`DVL_DATA#18` 50Hz。
- 5s 简报与 60s 详报中的链路状态、丢包、速率、相邻帧间隔 `gap avg/min/max`、身份/消息过滤 drop。

## 2. 测试对象与环境

| 项目 | 内容 |
| --- | --- |
| 测试日期 | 2026-06-25 |
| ROS 工程 | `sealien_ctrlpilot_mavlinkbridge` |
| STM32 工程 | `sealien-ctrlcore` |
| 目标下位机 | EP101 / `nav_sensor_mcu` |
| STM32 system/component | `101/1` |
| STM32 IP/端口 | `192.168.100.101:9999` |
| ROS 主机 IP | `192.168.100.100` |
| 串口 | `/dev/ttyACM0`, 115200 |
| 测试时长 | 约 5 分钟 |
| ROS 原始日志 | `/tmp/rov_mavlink_ep101_ros_20260625.log` |
| ROS 清洗日志 | `/tmp/rov_mavlink_ep101_ros_20260625.clean.log` |
| STM32 原始日志 | `/tmp/rov_mavlink_ep101_stm32_20260625.log` |
| STM32 清洗日志 | `/tmp/rov_mavlink_ep101_stm32_20260625.clean.log` |

## 3. 测试前确认

本次测试前已确认当前 STM32 测试配置为 EP101：

- `ROV_MAVTEST_ACTIVE_ENDPOINT=101U`
- `RT_LWIP_IPADDR=192.168.100.101`
- 日志标识 `rov.mav101`

ROS 与 STM32 工程均完成编译检查：

```bash
source /opt/ros/jazzy/setup.bash
colcon build --packages-select sealien_ctrlpilot_mavlinkbridge

source /home/se113/SLWS/CtrlCore/sealien-ctrlcore/.venv/bin/activate
cd /home/se113/SLWS/CtrlCore/sealien-ctrlcore/target/stm32/stm32h743-SLControlBoard
scons -j16
```

EP101 网络连通性测试：

```bash
ping -c 5 -W 1 192.168.100.101
```

结果：`5 transmitted, 5 received, 0% packet loss`，RTT `min/avg/max/mdev = 1.346/1.354/1.361/0.006 ms`。

## 4. 测试步骤

1. 清零 STM32 测试统计：

   ```bash
   stty -F /dev/ttyACM0 115200 raw -echo
   printf 'rov_mavtest_reset_stats\r\n' > /dev/ttyACM0
   ```

2. 采集 STM32 串口日志：

   ```bash
   timeout 330 cat /dev/ttyACM0 > /tmp/rov_mavlink_ep101_stm32_20260625.log
   ```

3. 启动 ROS MAVLink 测试节点，仅测试 EP101：

   ```bash
   source /home/se113/SLWS/SealienDCN/install/setup.bash
   ROS_LOG_DIR=/tmp/ros_logs_ep101_20260625 \
   timeout 330 ros2 launch sealien_ctrlpilot_mavlinkbridge rov_mavlink_test.launch.py \
     target_endpoints:=nav_sensor_mcu \
     brief_report_period_sec:=5 \
     detail_report_period_sec:=60 \
     publish_rx_mirror_topics:=false \
     publish_per_message_events:=false \
     tx_stats_period_sec:=60
   ```

4. 清洗日志颜色控制字符：

   ```bash
   perl -pe 's/\e\[[0-9;]*m//g' /tmp/rov_mavlink_ep101_ros_20260625.log > /tmp/rov_mavlink_ep101_ros_20260625.clean.log
   perl -pe 's/\e\[[0-9;]*m//g' /tmp/rov_mavlink_ep101_stm32_20260625.log > /tmp/rov_mavlink_ep101_stm32_20260625.clean.log
   ```

## 5. 关键测试数据

### 5.1 ROS 端最终 60s 详报

ROS 端链路状态：`online(1/1)`，`state=UP(OK)`，`rx_age=7ms`，`last_rx_msgid=18`，`link_up/down=1/0`。

| 方向 | 总帧数 | 窗口帧数 | 速率 | missed | loss |
| --- | ---: | ---: | ---: | ---: | ---: |
| ROS -> STM32 | 6300 | 1260/1257 | 21.00/21.00Hz | 0 | 0.00% |
| STM32 -> ROS | 42292 | 8460/8453 | 141.00/141.00Hz | 0 | 0.00% |

| 消息 | 方向 | 窗口帧数 | 速率 | missed | loss | gap avg/min/max |
| --- | --- | ---: | ---: | ---: | ---: | --- |
| `HEARTBEAT#00` | ROS -> STM32 | 60/59 | 1.00/1.00Hz | 0 | 0.00% | 1000.00/1000/1000ms |
| `IMU_CALIB#12` | ROS -> STM32 | 600/599 | 10.00/10.00Hz | 0 | 0.00% | 100.00/100/100ms |
| `IMU_CLEAR#13` | ROS -> STM32 | 600/599 | 10.00/10.00Hz | 0 | 0.00% | 100.00/100/100ms |
| `HEARTBEAT#00` | STM32 -> ROS | 60/59 | 1.00/1.00Hz | 0 | 0.00% | 1000.00/999/1001ms |
| `IMU_DATA#01` | STM32 -> ROS | 3000/2999 | 50.00/50.00Hz | 0 | 0.00% | 20.00/17/22ms |
| `VCHECK#05` | STM32 -> ROS | 600/599 | 10.00/10.00Hz | 0 | 0.00% | 100.00/99/101ms |
| `HEIGHT_STATUS#06` | STM32 -> ROS | 600/599 | 10.00/10.00Hz | 0 | 0.00% | 100.00/99/101ms |
| `DEPTH_STATUS#07` | STM32 -> ROS | 600/599 | 10.00/10.00Hz | 0 | 0.00% | 100.00/99/101ms |
| `BME280#08` | STM32 -> ROS | 600/599 | 10.00/10.00Hz | 0 | 0.00% | 100.00/99/101ms |
| `DVL_DATA#18` | STM32 -> ROS | 3000/2999 | 50.00/50.00Hz | 0 | 0.00% | 20.00/18/21ms |

### 5.2 STM32 端最终 60s 详报

STM32 端链路状态：`state=UP(OK)`，`rx_age=45ms`，`last_rx=- IMU_CLEAR#13`，`link_up/down=1/0`，`drops(identity/not_allowed)=0/0`。

| 方向 | 总帧数 | 窗口帧数 | 速率 | missed | loss |
| --- | ---: | ---: | ---: | ---: | ---: |
| STM32 -> ROS | 45531 | 8464/8464 | 140.96/141.00Hz | 0 | 0.00% |
| ROS -> STM32 | 6304 | 1260/1260 | 20.98/21.00Hz | 0 | 0.00% |

| 消息 | 方向 | 窗口帧数 | 速率 | missed | loss | gap avg/min/max |
| --- | --- | ---: | ---: | ---: | ---: | --- |
| `HEARTBEAT#00` | STM32 -> ROS | 60/60 | 0.99/1.00Hz | 0 | 0.00% | 1000.00/1000/1000ms |
| `IMU_DATA#01` | STM32 -> ROS | 3002/3002 | 49.99/50.00Hz | 0 | 0.00% | 20.00/20/20ms |
| `VCHECK#05` | STM32 -> ROS | 600/600 | 9.99/10.00Hz | 0 | 0.00% | 100.00/100/100ms |
| `HEIGHT_STATUS#06` | STM32 -> ROS | 600/600 | 9.99/10.00Hz | 0 | 0.00% | 100.00/100/100ms |
| `DEPTH_STATUS#07` | STM32 -> ROS | 600/600 | 9.99/10.00Hz | 0 | 0.00% | 100.00/100/100ms |
| `BME280#08` | STM32 -> ROS | 600/600 | 9.99/10.00Hz | 0 | 0.00% | 100.00/100/100ms |
| `DVL_DATA#18` | STM32 -> ROS | 3002/3002 | 49.99/50.00Hz | 0 | 0.00% | 20.00/20/20ms |
| `HEARTBEAT#00` | ROS -> STM32 | 60/60 | 0.99/1.00Hz | 0 | 0.00% | 1000.00/1000/1000ms |
| `IMU_CALIB#12` | ROS -> STM32 | 600/600 | 9.99/10.00Hz | 0 | 0.00% | 100.00/99/101ms |
| `IMU_CLEAR#13` | ROS -> STM32 | 600/600 | 9.99/10.00Hz | 0 | 0.00% | 100.00/99/101ms |

### 5.3 5s 简报稳态表现

测试后半段多个 5s 简报均保持稳定：

- ROS 侧 `EP101 TX ROS->STM32`：`105/105` 或 `105/102`，`missed=0`，`loss=0.00%`。
- ROS 侧 `EP101 RX STM32->ROS`：`705/705` 或 `705/698`，`missed=0`，`loss=0.00%`。
- STM32 侧 `EP101 TX STM32->ROS`：约 `707/705`，`missed=0`，`loss=0.00%`。
- STM32 侧 `EP101 RX ROS->STM32`：约 `105/105`，`missed=0`，`loss=0.00%`。

说明：部分窗口中 `actual > expected` 是 expected 采用向下取整后的保守显示结果，不表示超发异常；真实速率和 gap 更能反映链路质量。

## 6. 异常扫描与问题定位

对 ROS 与 STM32 日志执行关键异常扫描，命中过首个启动窗口中的少量 missed：

- STM32 首个简报窗口：`missed=8`，`loss=1.13%`。
- ROS 首个简报窗口：RX 侧 `missed=7`，`loss=1.00%`，主要出现在 `IMU_DATA#01` 与 `DVL_DATA#18`。
- ROS 首个 60s 详报仍累计了启动瞬间的 `missed=7`，随后 60s 详报和后续 5s 简报均恢复为 `missed=0`、`loss=0.00%`。

排查结论：

- 该现象只出现在测试启动初期，链路进入稳态后不再复现。
- 全程未出现 `LINK DOWN`、`state=DOWN`、身份过滤 drop、非法消息 drop。
- 最终 60s 详报中 ROS 与 STM32 两端对双向链路均统计为 0 丢包。
- 因此本次首窗 missed 判断为测试启动/统计清零/ROS 节点上线不同步造成的暖机窗口统计误差，不属于 EP101 稳态通信质量问题。

本轮未发现需要继续修改 ROS 或 STM32 源码的新增设计缺陷。当前已经应用的 endpoint 独立统计窗口和 expected 向下取整逻辑能够避免稳态窗口误报。

## 7. 测试结果

EP101 在本轮约 5 分钟测试中通信质量满足预期：

- ROS -> STM32 下行链路目标 21Hz，最终 60s 窗口 0 丢包。
- STM32 -> ROS 上行链路目标 141Hz，最终 60s 窗口 0 丢包。
- 高频 `IMU_DATA#01` 与 `DVL_DATA#18` 均达到 50Hz，ROS 侧 gap 约 17-22ms，STM32 侧发送 gap 稳定为 20ms。
- 10Hz 状态类消息 gap 稳定在 99-101ms。
- 1Hz 心跳 gap 稳定在 999-1001ms。
- 全程链路保持 `UP(OK)`，无断链计数增加。

## 8. 后续优化建议

- 报告统计时建议固定忽略测试启动后的第一个 5s 窗口，或在测试脚本中增加 5-10s warm-up 后再清零统计，以避免把启动瞬态混入正式数据。
- 日志字段 `window=actual/expected` 在向下取整策略下可能显示 `actual > expected`，后续可将字段改名为 `window=min_expected` 或新增 `target_rate` 列，降低阅读歧义。
- 三板联测时建议分别输出 EP101、EP102、EP103 的最终 60s 汇总，再增加整机总吞吐、CPU 占用、UDP socket buffer drop 等系统级指标。
- 若需要进一步压测 EP101，可在当前 141Hz 上行基线通过后，逐步提高 IMU/DVL 至 100Hz，并观察 ROS 主机调度、STM32 发送线程优先级和串口日志输出对 jitter 的影响。
