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

// One STM32 lower-controller reachable from the ROS host.
// rx/tx are intentionally split so the bridge can enforce per-endpoint routing
// instead of broadcasting every MAVLink frame to every board.
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

// Runtime view of config/sealien_mavlink_*.yaml.
// The YAML file remains the single source of truth for endpoint identity,
// UDP address and allowed MSGID directions.
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

// Shared implementation used by both ROV and TMS executable nodes.
//
// Data flow:
//   STM32 UDP MAVLink -> rx_loop() -> route validation -> ROS topic publish
//   ROS topic subscribe -> MAVLink encode -> tx route validation -> STM32 UDP
//
// The two concrete nodes only choose a default YAML file and topic prefix.
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

  BridgeConfig load_config_file(const std::string & path) const;
  bool reload_config(std::string * message);
  void rebuild_ros_routes(const BridgeConfig & config);

  bool open_udp_socket(const BridgeConfig & config, std::string * error);
  void close_udp_socket();
  void rx_loop();
  void handle_mavlink_message(const mavlink_message_t & msg, const sockaddr_in & src_addr);

  void heartbeat_timer_callback();
  void config_reload_timer_callback();
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

  void create_rx_publisher(const EndpointConfig & endpoint, uint32_t msgid);
  void create_tx_subscription(const EndpointConfig & endpoint, uint32_t msgid);

  void publish_rx_message(const EndpointConfig & endpoint, const mavlink_message_t & msg);

  // Publishers are stored as PublisherBase because their concrete message type
  // depends on MSGID. The template recovers the concrete type at publish time.
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

  std::string default_config_file_;
  std::string config_file_;
  std::string topic_prefix_;
  bool auto_reload_{true};
  bool strict_remote_ip_{false};
  uint8_t heartbeat_type_{1};
  uint8_t heartbeat_system_status_{0};

  // Protects configuration and ROS communication handles while config reload
  // can rebuild routes concurrently with receive callbacks.
  mutable std::mutex state_mutex_;
  BridgeConfig config_;
  std::unordered_map<std::string, rclcpp::PublisherBase::SharedPtr> publishers_;
  std::vector<rclcpp::SubscriptionBase::SharedPtr> subscriptions_;

  // Protects the POSIX UDP socket shared by receive thread, send callbacks and
  // config reload. Keep this separate from state_mutex_ to avoid long lock chains.
  mutable std::mutex socket_mutex_;
  int socket_fd_{-1};

  // MAVLink parser state is used only by rx_thread_.
  std::atomic<bool> running_{false};
  std::thread rx_thread_;
  mavlink_status_t rx_status_{};
  mavlink_message_t rx_msg_{};

  rclcpp::TimerBase::SharedPtr heartbeat_timer_;
  rclcpp::TimerBase::SharedPtr config_reload_timer_;
  rclcpp::Service<ReloadService>::SharedPtr reload_service_;
  std::filesystem::file_time_type config_mtime_{};
  std::chrono::steady_clock::time_point last_heartbeat_tx_{};
};

}  // namespace sealien_ctrlpilot_mavlinkbridge
