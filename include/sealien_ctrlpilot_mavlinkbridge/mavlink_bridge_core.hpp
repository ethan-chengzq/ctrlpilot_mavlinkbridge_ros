#pragma once

#include <atomic>
#include <chrono>
#include <cstdint>
#include <filesystem>
#include <memory>
#include <mutex>
#include <optional>
#include <set>
#include <string>
#include <thread>
#include <unordered_map>
#include <vector>

#include <netinet/in.h>

#include "rclcpp/rclcpp.hpp"
#include "std_msgs/msg/string.hpp"

#include "sealien_ctrlpilot_msgmanagement/msg/bme280_status.hpp"
#include "sealien_ctrlpilot_msgmanagement/msg/depth_status.hpp"
#include "sealien_ctrlpilot_msgmanagement/msg/dvl_data.hpp"
#include "sealien_ctrlpilot_msgmanagement/msg/gs_cfg.hpp"
#include "sealien_ctrlpilot_msgmanagement/msg/gs_cmd.hpp"
#include "sealien_ctrlpilot_msgmanagement/msg/gs_status.hpp"
#include "sealien_ctrlpilot_msgmanagement/msg/heartbeat_status.hpp"
#include "sealien_ctrlpilot_msgmanagement/msg/imu_calib.hpp"
#include "sealien_ctrlpilot_msgmanagement/msg/imu_clear.hpp"
#include "sealien_ctrlpilot_msgmanagement/msg/imu_nav_status.hpp"
#include "sealien_ctrlpilot_msgmanagement/msg/led_cmd.hpp"
#include "sealien_ctrlpilot_msgmanagement/msg/led_status.hpp"
#include "sealien_ctrlpilot_msgmanagement/msg/mixed_io_cmd.hpp"
#include "sealien_ctrlpilot_msgmanagement/msg/mixed_io_data.hpp"
#include "sealien_ctrlpilot_msgmanagement/msg/sonar_altimeter_status.hpp"
#include "sealien_ctrlpilot_msgmanagement/msg/switch_cmd.hpp"
#include "sealien_ctrlpilot_msgmanagement/msg/switch_status.hpp"
#include "sealien_ctrlpilot_msgmanagement/msg/thruster_cmd.hpp"
#include "sealien_ctrlpilot_msgmanagement/msg/thruster_lock.hpp"
#include "sealien_ctrlpilot_msgmanagement/msg/thruster_status.hpp"
#include "sealien_ctrlpilot_msgmanagement/msg/valve_cmd.hpp"
#include "sealien_ctrlpilot_msgmanagement/msg/valve_status.hpp"
#include "sealien_ctrlpilot_msgmanagement/msg/vcheck_status.hpp"
#include "sealien_ctrlpilot_msgmanagement/srv/reload_mavlink_config.hpp"

extern "C" {
#include "mavlink.h"
}

namespace sealien_ctrlpilot_mavlinkbridge
{

// 单块 STM32 下位机的静态配置。
//
// 这里的 rx/tx 是站在 ROS bridge 视角定义的：
// - rx: ROS 从该 endpoint 接收的 MAVLink MSGID，bridge 会发布到 rov/from_mcu/*
// - tx: ROS 允许发往该 endpoint 的 MAVLink MSGID，bridge 会订阅 rov/to_mcu/*
//
// rx/tx 分开配置是为了让 bridge 做“按板卡、按消息”的白名单路由，避免把所有
// MAVLink 帧广播给所有 STM32。
struct EndpointConfig
{
  std::string name;
  bool enabled{true};
  uint8_t system_id{0};
  uint8_t component_id{0};
  std::string remote_ip;
  uint16_t remote_port{0};
  std::set<uint32_t> rx;
  std::set<uint32_t> tx;
};

// YAML 配置在运行期的内存视图。
//
// config/sealien_mavlink_*.yaml 是 endpoint 身份、UDP 地址和消息方向白名单
// 的唯一配置源。业务节点不应在代码里硬编码下位机 IP 或 MSGID 路由。
struct BridgeConfig
{
  std::string dialect;
  uint8_t host_system_id{1};
  uint8_t host_component_id{1};
  std::string bind_ip{"0.0.0.0"};
  uint16_t bind_port{9999};
  double heartbeat_host_tx_hz{1.0};
  double heartbeat_endpoint_expected_hz{1.0};
  int endpoint_timeout_ms{3000};
  std::vector<EndpointConfig> endpoints;
};

// MAVLink bridge 的共享实现。
//
// 数据流：
//   STM32 UDP MAVLink -> rx_loop() -> 身份/MSGID 校验 -> ROS topic 发布
//   ROS topic 订阅 -> MAVLink encode -> tx 白名单校验 -> UDP sendto STM32
//
// 具体可执行节点只负责选择默认 YAML 和 topic_prefix。新增产品线时优先复用
// MavlinkBridgeCore，不建议复制一份 bridge 逻辑再改。
class MavlinkBridgeCore : public rclcpp::Node
{
public:
  MavlinkBridgeCore(
    const std::string & node_name,
    const std::string & default_config_file,
    const std::string & default_topic_prefix);
  ~MavlinkBridgeCore() override;

private:
  using ReloadService = sealien_ctrlpilot_msgmanagement::srv::ReloadMavlinkConfig;

  struct EndpointRuntimeState
  {
    bool connected{false};
    std::chrono::steady_clock::time_point last_rx{};
  };

  struct TxCounter
  {
    uint64_t success{0};
    uint64_t failure{0};
    uint64_t bytes{0};
    uint64_t window_success{0};
    uint64_t window_failure{0};
    uint64_t window_bytes{0};
  };

  BridgeConfig load_config_file(const std::string & path) const;
  bool reload_config(std::string * message);
  void rebuild_ros_routes(const BridgeConfig & config);

  bool open_udp_socket(const BridgeConfig & config, std::string * error);
  void close_udp_socket();
  void rx_loop();
  void handle_mavlink_message(const mavlink_message_t & msg, const sockaddr_in & src_addr);
  void record_rx_message(
    const EndpointConfig & endpoint,
    const mavlink_message_t & msg,
    const sockaddr_in & src_addr);
  void check_endpoint_timeouts();

  void heartbeat_timer_callback();
  void config_reload_timer_callback();
  void tx_stats_timer_callback();
  void reload_service_callback(
    const std::shared_ptr<ReloadService::Request> request,
    std::shared_ptr<ReloadService::Response> response);

  std::optional<EndpointConfig> find_incoming_endpoint_locked(
    const mavlink_message_t & msg) const;
  std::optional<EndpointConfig> find_endpoint_for_tx_locked(
    const std::string & endpoint_name,
    uint32_t msgid) const;

  bool send_message_to_endpoint(
    const std::string & endpoint_name,
    uint32_t msgid,
    const mavlink_message_t & msg);
  bool send_message_to_endpoint_unchecked(
    const EndpointConfig & endpoint,
    const mavlink_message_t & msg);
  void record_tx_result(
    const EndpointConfig & endpoint,
    uint32_t msgid,
    bool success,
    uint16_t bytes_written);

  void create_rx_publisher(const EndpointConfig & endpoint, uint32_t msgid);
  void create_tx_subscription(const EndpointConfig & endpoint, uint32_t msgid);

  void publish_rx_message(const EndpointConfig & endpoint, const mavlink_message_t & msg);

  // 不同 MSGID 对应不同 ROS message 类型，因此 publisher 只能统一保存为
  // PublisherBase；真正 publish 前再 dynamic_cast 回具体类型。
  template<typename MessageT>
  void publish_typed(const std::string & key, const MessageT & message)
  {
    rclcpp::PublisherBase::SharedPtr base;
    {
      std::lock_guard<std::mutex> lock(state_mutex_);
      const auto it = publishers_.find(key);
      if (it == publishers_.end()) {
        return;
      }
      base = it->second;
    }

    auto pub = std::dynamic_pointer_cast<rclcpp::Publisher<MessageT>>(base);
    if (pub) {
      pub->publish(message);
    }
  }

  std::string topic_for(const EndpointConfig & endpoint, uint32_t msgid, bool rx) const;
  std::string publisher_key(const EndpointConfig & endpoint, uint32_t msgid) const;

  static std::string msgid_name(uint32_t msgid);
  static std::string msgid_topic_name(uint32_t msgid);
  static bool is_supported_msgid(uint32_t msgid);
  static std::string msgid_set_to_string(const std::set<uint32_t> & ids);

  std::string default_config_file_;
  std::string config_file_;
  std::string topic_prefix_;
  bool auto_reload_{true};
  bool strict_remote_ip_{false};
  uint8_t heartbeat_type_{1};
  uint8_t heartbeat_system_status_{0};
  double heartbeat_host_tx_hz_override_{-1.0};
  std::size_t ros_queue_depth_{100};
  int udp_recv_buffer_bytes_{262144};
  int udp_send_buffer_bytes_{262144};
  int rx_idle_sleep_ms_{1};
  bool enable_tx_stats_{true};
  int tx_stats_period_sec_{60};

  // 保护配置和 ROS 路由句柄。自动重载 YAML 时会重建 publisher/subscription，
  // 同时 rx_thread 和 ROS 回调仍可能读配置，因此必须统一走这把锁。
  mutable std::mutex state_mutex_;
  BridgeConfig config_;
  std::unordered_map<std::string, rclcpp::PublisherBase::SharedPtr> publishers_;
  std::vector<rclcpp::SubscriptionBase::SharedPtr> subscriptions_;

  mutable std::mutex endpoint_state_mutex_;
  std::unordered_map<std::string, EndpointRuntimeState> endpoint_states_;

  // 保护 POSIX UDP socket。socket 同时被接收线程、发送回调和配置重载使用。
  // 这把锁独立于 state_mutex_，避免 socket IO 与配置锁形成过长锁链。
  mutable std::mutex socket_mutex_;
  int socket_fd_{-1};

  mutable std::mutex tx_stats_mutex_;
  std::unordered_map<std::string, TxCounter> tx_counters_;

  // MAVLink C parser 状态只在 rx_thread_ 中使用，不跨线程共享。
  std::atomic<bool> running_{false};
  std::thread rx_thread_;
  mavlink_status_t rx_status_{};
  mavlink_message_t rx_msg_{};

  rclcpp::TimerBase::SharedPtr heartbeat_timer_;
  rclcpp::TimerBase::SharedPtr config_reload_timer_;
  rclcpp::TimerBase::SharedPtr tx_stats_timer_;
  rclcpp::Service<ReloadService>::SharedPtr reload_service_;
  rclcpp::Publisher<std_msgs::msg::String>::SharedPtr tx_stats_pub_;
  std::filesystem::file_time_type config_mtime_{};
  std::chrono::steady_clock::time_point next_heartbeat_tx_{};
};

}  // namespace sealien_ctrlpilot_mavlinkbridge
