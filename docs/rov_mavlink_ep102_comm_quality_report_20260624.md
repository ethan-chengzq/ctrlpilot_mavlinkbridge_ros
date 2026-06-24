# ROV MAVLink EP102 通信质量测试报告（2026-06-24）

## 1. 测试目的

本次测试针对 EP102 `actuator_mcu`，验证 ROS 中位机 `sealien_ctrlpilot_mavlinkbridge` 与 STM32 下位机在 UDP/IP 链路上的 MAVLink 通信质量，重点覆盖推进器命令 50 Hz、执行器状态/开关命令 10 Hz、心跳 1 Hz 的上下行压力通信。

本报告记录 EP102 本轮问题定位、ROS 测试节点修复和修复后短测验证结果。由于当前会话提权执行额度耗尽，无法继续访问 `/dev/ttyACM0` 完成 5 分钟正式复测；5 分钟标准测试数据需后续补采。

## 2. 测试对象

| 项目 | 内容 |
| --- | --- |
| 终端 | EP102 |
| endpoint | `actuator_mcu` |
| sysid / compid | `102 / 1` |
| UDP 地址 | `192.168.100.102:9999` |
| ROS launch | `ros2 launch sealien_ctrlpilot_mavlinkbridge rov_mavlink_test.launch.py target_endpoints:=actuator_mcu brief_report_period_sec:=5 detail_report_period_sec:=60 publish_rx_mirror_topics:=false publish_per_message_events:=false` |
| STM32 串口 | `/dev/ttyACM0`, 115200 baud |
| ROS 构建 | `colcon build --packages-select sealien_ctrlpilot_mavlinkbridge` 通过 |

## 3. 消息压力配置

| 方向 | 消息 | 目标频率 | 说明 |
| --- | --- | ---: | --- |
| ROS -> STM32 | `HEARTBEAT#00` | 1 Hz | bridge 内部心跳 |
| ROS -> STM32 | `THRUSTER_CMD#10` | 50 Hz | 高频推进器命令 |
| ROS -> STM32 | `THRUSTER_LOCK#11` | 10 Hz | 推进器锁定命令 |
| ROS -> STM32 | `LED_CMD#14` | 10 Hz | 灯光命令 |
| ROS -> STM32 | `GS_CMD#15` | 10 Hz | 云台命令 |
| ROS -> STM32 | `GS_CFG#16` | 10 Hz | 云台配置 |
| ROS -> STM32 | `SWITCH_CMD#17` | 10 Hz | 开关命令 |
| STM32 -> ROS | `HEARTBEAT#00` | 1 Hz | 下位机心跳 |
| STM32 -> ROS | `THRUSTER_STATUS#02` | 10 Hz | 推进器状态 |
| STM32 -> ROS | `GS_STATUS#03` | 10 Hz | 云台状态 |
| STM32 -> ROS | `LED_STATUS#04` | 10 Hz | 灯光状态 |
| STM32 -> ROS | `SWITCH_STATUS#09` | 10 Hz | 开关状态 |

## 4. 问题定位

修复前 5 分钟采集显示，ROS 测试节点侧 `TX ROS->STM32` 为 `30000/30000`、0.00% loss，STM32 侧 `TX STM32->ROS` 也稳定为 41 Hz 左右。但 STM32 侧 `RX ROS->STM32` 出现严重低频命令丢失，最后一个 60 s detail 窗口如下：

| 消息 | window | rate/target | missed | loss |
| --- | ---: | ---: | ---: | ---: |
| `HEARTBEAT#00` | 60/60 | 0.99/0.99 Hz | 0 | 0.00% |
| `THRUSTER_CMD#10` | 3002/3002 | 49.99/49.99 Hz | 0 | 0.00% |
| `THRUSTER_LOCK#11` | 81/600 | 1.34/9.99 Hz | 519 | 86.50% |
| `LED_CMD#14` | 82/600 | 1.36/9.99 Hz | 518 | 86.33% |
| `GS_CMD#15` | 75/600 | 1.24/9.99 Hz | 525 | 87.50% |
| `GS_CFG#16` | 77/600 | 1.28/9.99 Hz | 523 | 87.16% |
| `SWITCH_CMD#17` | 81/600 | 1.34/9.99 Hz | 519 | 86.50% |

进一步将 `tx_route_stagger_ms` 临时改为 10 ms 后，`THRUSTER_LOCK#11`、`GS_CMD#15`、`SWITCH_CMD#17` 恢复到 10 Hz，而 `LED_CMD#14`、`GS_CFG#16` 仍接近 100% loss。结合调度相位计算可定位为：这些 10 Hz 消息与 50 Hz `THRUSTER_CMD#10` 同 tick 发布，形成同一毫秒内连续 UDP MAVLink 帧，EP102 STM32 接收路径对该突发模式敏感，低频消息被高频命令压制。

结论：本轮主要问题不是正式桥接能力缺失，也不是 EP102 消息白名单错误，而是 ROS 测试节点压测调度相位设计不合理，制造了不符合目标频率含义的同 tick burst。

## 5. 修复内容

已修改 ROS 端 `src/rov_mavlink_test_node.cpp`：

- 新增 endpoint 级 TX phase slot 记录。
- 为每个 TX route 分配不会与同 endpoint 已有周期同相位重叠的发送相位。
- 对 50 Hz 与 10 Hz 混合压力场景，优先把 10 Hz 消息放在 50 Hz 周期间隔的中点。
- 保持 `mavlink_bridge_core` 正式通信逻辑不变，仅优化测试节点压测发布节奏。

该修复不改变 EP101/EP103 的 endpoint 配置，不改变 STM32 固件，不改变正式 MAVLink bridge 的收发能力。

## 6. 修复后验证数据

修复后使用默认 launch 参数短测约 70 s，EP102 各下行命令恢复到目标频率。

### 6.1 ROS 侧 60 s 窗口

| 方向 | window | rate/target | missed | loss |
| --- | ---: | ---: | ---: | ---: |
| TX ROS -> STM32 | 6000/6000 | 100.00/100.00 Hz | 0 | 0.00% |
| RX STM32 -> ROS | 2455/2460 | 40.92/41.00 Hz | 5 | 0.20% |

| 方向 | 消息 | window | rate/target | missed | loss | gap avg/min/max |
| --- | --- | ---: | ---: | ---: | ---: | --- |
| TX | `THRUSTER_CMD#10` | 3000/3000 | 50.00/50.00 Hz | 0 | 0.00% | 20.00/15/20 ms |
| TX | `THRUSTER_LOCK#11` | 600/600 | 10.00/10.00 Hz | 0 | 0.00% | 100.00/100/100 ms |
| TX | `LED_CMD#14` | 600/600 | 10.00/10.00 Hz | 0 | 0.00% | 100.00/100/100 ms |
| TX | `GS_CMD#15` | 600/600 | 10.00/10.00 Hz | 0 | 0.00% | 100.00/100/100 ms |
| TX | `GS_CFG#16` | 600/600 | 10.00/10.00 Hz | 0 | 0.00% | 100.00/99/101 ms |
| TX | `SWITCH_CMD#17` | 600/600 | 10.00/10.00 Hz | 0 | 0.00% | 100.00/100/100 ms |
| RX | `HEARTBEAT#00` | 60/60 | 1.00/1.00 Hz | 0 | 0.00% | 999.98/999/1001 ms |
| RX | `THRUSTER_STATUS#02` | 599/600 | 9.98/10.00 Hz | 1 | 0.17% | 100.00/79/122 ms |
| RX | `GS_STATUS#03` | 599/600 | 9.98/10.00 Hz | 1 | 0.17% | 100.00/79/121 ms |
| RX | `LED_STATUS#04` | 599/600 | 9.98/10.00 Hz | 1 | 0.17% | 100.00/80/119 ms |
| RX | `SWITCH_STATUS#09` | 598/600 | 9.97/10.00 Hz | 2 | 0.33% | 100.00/99/101 ms |

### 6.2 STM32 侧 60 s 窗口

| 方向 | window | rate/target | missed | loss |
| --- | ---: | ---: | ---: | ---: |
| TX STM32 -> ROS | 2460/2464 | 40.96/41.03 Hz | 4 | 0.16% |
| RX ROS -> STM32 | 6055/6068 | 100.83/101.04 Hz | 13 | 0.21% |

| 方向 | 消息 | window | rate/target | missed | loss | gap avg/min/max |
| --- | --- | ---: | ---: | ---: | ---: | --- |
| TX | `HEARTBEAT#00` | 60/60 | 0.99/0.99 Hz | 0 | 0.00% | 1000.00/1000/1000 ms |
| TX | `THRUSTER_STATUS#02` | 600/601 | 9.99/10.00 Hz | 1 | 0.16% | 99.96/78/100 ms |
| TX | `GS_STATUS#03` | 600/601 | 9.99/10.00 Hz | 1 | 0.16% | 99.96/79/100 ms |
| TX | `LED_STATUS#04` | 600/601 | 9.99/10.00 Hz | 1 | 0.16% | 99.96/80/100 ms |
| TX | `SWITCH_STATUS#09` | 600/601 | 9.99/10.00 Hz | 1 | 0.16% | 100.00/100/100 ms |
| RX | `HEARTBEAT#00` | 60/60 | 0.99/0.99 Hz | 0 | 0.00% | 999.69/900/1100 ms |
| RX | `THRUSTER_CMD#10` | 2998/3003 | 49.92/50.00 Hz | 5 | 0.16% | 19.99/1/21 ms |
| RX | `THRUSTER_LOCK#11` | 599/601 | 9.97/10.00 Hz | 2 | 0.33% | 100.00/100/100 ms |
| RX | `LED_CMD#14` | 600/601 | 9.99/10.00 Hz | 1 | 0.16% | 100.00/100/100 ms |
| RX | `GS_CMD#15` | 600/601 | 9.99/10.00 Hz | 1 | 0.16% | 100.00/100/100 ms |
| RX | `GS_CFG#16` | 599/601 | 9.97/10.00 Hz | 2 | 0.33% | 100.00/100/100 ms |
| RX | `SWITCH_CMD#17` | 599/601 | 9.97/10.00 Hz | 2 | 0.33% | 100.00/99/101 ms |

## 7. 当前问题与分析

1. 修复前 EP102 低频下行命令严重丢失，根因是 ROS 测试节点将 10 Hz 命令与 50 Hz 推进器命令分配到了相同发送相位，形成 UDP burst。

2. 修复后所有 EP102 下行测试消息均达到目标频率，60 s 窗口总损失降至 0.21%，已从“持续性大面积丢失”恢复为“启动/窗口边界级轻微损失”。

3. STM32 侧 `THRUSTER_CMD#10` gap 出现 `min=1 ms`，但窗口频率仍为 49.92/50.00 Hz，未造成持续丢包。该现象更像 ROS executor/bridge 在个别 tick 中补发相邻帧造成的短瞬态间隔，后续可通过 bridge 侧 UDP 实发统计进一步确认。

4. STM32 侧 `link_up/down=4/3` 包含历史测试和 ROS launch 停止后的状态变化，不适合作为本轮短测有效窗口的连接波动结论。后续正式 5 分钟测试建议先重启或提供统计清零命令。

## 8. 后续优化建议

1. 补做 EP102 5 分钟正式复测，采集 5 个连续 60 s detail 窗口，确认修复后的长期稳定性。

2. 在 ROS bridge 中增加可选 UDP 实发计数器，区分“测试节点发布成功”和“bridge 实际 sendto 成功”，后续定位会更直接。

3. STM32 测试固件建议增加 session reset 命令，清空累计 total、link_up/down、gap 统计，避免多轮测试历史计数混入报告。

4. 保留当前测试节点相位避让逻辑。多端点并发测试时，建议继续检查不同 endpoint 的主机侧 UDP 调度是否会在同一系统时刻形成跨端点突发。

## 9. 测试结论

EP102 本轮暴露的问题已定位并在 ROS 测试节点中修复。修复后短测显示，EP102 上行 STM32->ROS 保持稳定，ROS->STM32 下行从修复前约 43%-47% 总窗口损失、低频命令 86%-97% 丢失，恢复到 60 s 窗口总损失 0.21%，各命令消息均接近目标频率。

当前结论为“修复有效，需补做 5 分钟正式复测”。正式报告定稿前，应补采完整 5 分钟数据并替换本报告中的短测验证数据。
