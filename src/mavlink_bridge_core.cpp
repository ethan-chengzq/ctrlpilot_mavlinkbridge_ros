#include "sealien_ctrlpilot_mavlinkbridge/mavlink_bridge_core.hpp"

#include <algorithm>
#include <cerrno>
#include <cctype>
#include <cstddef>
#include <cstring>
#include <iomanip>
#include <sstream>
#include <stdexcept>

#include <arpa/inet.h>
#include <fcntl.h>
#include <sys/socket.h>
#include <unistd.h>

#include "yaml-cpp/yaml.h"

namespace sealien_ctrlpilot_mavlinkbridge
{
namespace
{

// MAVLink 生成的 C 数组和 ROS 2 固定数组类型不同，但都支持 size()/operator[]。
// 统一用这两个 helper 做数组字段拷贝，避免在每个 MSGID 映射里重复手写循环。
template<typename RosArrayT, typename MavArrayT>
void copy_to_ros_array(RosArrayT & dst, const MavArrayT & src)
{
  for (std::size_t i = 0; i < dst.size(); ++i) {
    dst[i] = src[i];
  }
}

template<typename MavArrayT, typename RosArrayT>
void copy_to_mav_array(MavArrayT & dst, const RosArrayT & src)
{
  for (std::size_t i = 0; i < src.size(); ++i) {
    dst[i] = src[i];
  }
}

// YAML 由人工维护，读取后先校验范围，再收窄到 MAVLink header 使用的
// uint8_t/uint16_t，避免非法配置在运行期静默截断。
uint8_t read_u8(const YAML::Node & node, const std::string & key)
{
  const auto value = node[key].as<int>();
  if (value < 0 || value > 255) {
    throw std::runtime_error(key + " must be in uint8 range");
  }
  return static_cast<uint8_t>(value);
}

uint16_t read_u16(const YAML::Node & node, const std::string & key)
{
  const auto value = node[key].as<int>();
  if (value < 0 || value > 65535) {
    throw std::runtime_error(key + " must be in uint16 range");
  }
  return static_cast<uint16_t>(value);
}

std::set<uint32_t> read_msgids(const YAML::Node & node)
{
  std::set<uint32_t> ids;
  if (!node) {
    return ids;
  }
  for (const auto & item : node) {
    const auto id = item.as<int>();
    if (id < 0) {
      throw std::runtime_error("MSGID must be non-negative");
    }
    ids.insert(static_cast<uint32_t>(id));
  }
  return ids;
}

std::string ip_to_string(const sockaddr_in & addr)
{
  char buf[INET_ADDRSTRLEN] = {};
  if (::inet_ntop(AF_INET, &addr.sin_addr, buf, sizeof(buf)) == nullptr) {
    return {};
  }
  return std::string(buf);
}

// topic_prefix 允许用户传 "rov" 或 "/rov"，内部统一去掉首尾斜杠。
// 这样 topic 拼接逻辑只需要维护一种格式。
std::string trim_slashes(std::string value)
{
  while (!value.empty() && value.front() == '/') {
    value.erase(value.begin());
  }
  while (!value.empty() && value.back() == '/') {
    value.pop_back();
  }
  return value;
}

}  // namespace

MavlinkBridgeCore::MavlinkBridgeCore(
  const std::string & node_name,
  const std::string & default_config_file,
  const std::string & default_topic_prefix)
: Node(node_name),
  default_config_file_(default_config_file)
{
  declare_parameter<std::string>("config_file", default_config_file_);
  declare_parameter<std::string>("topic_prefix", default_topic_prefix);
  declare_parameter<bool>("auto_reload", true);
  declare_parameter<int>("config_check_period_ms", 1000);
  declare_parameter<bool>("strict_remote_ip", false);
  declare_parameter<int>("heartbeat_type", 1);
  declare_parameter<int>("heartbeat_system_status", 0);
  declare_parameter<double>("heartbeat_host_tx_hz_override", -1.0);
  declare_parameter<int>("ros_queue_depth", 100);
  declare_parameter<int>("udp_recv_buffer_bytes", 262144);
  declare_parameter<int>("udp_send_buffer_bytes", 262144);
  declare_parameter<int>("rx_idle_sleep_ms", 1);
  declare_parameter<bool>("enable_tx_stats", true);
  declare_parameter<int>("tx_stats_period_sec", 60);

  config_file_ = get_parameter("config_file").as_string();
  topic_prefix_ = trim_slashes(get_parameter("topic_prefix").as_string());
  auto_reload_ = get_parameter("auto_reload").as_bool();
  strict_remote_ip_ = get_parameter("strict_remote_ip").as_bool();
  heartbeat_type_ = static_cast<uint8_t>(get_parameter("heartbeat_type").as_int());
  heartbeat_system_status_ =
    static_cast<uint8_t>(get_parameter("heartbeat_system_status").as_int());
  heartbeat_host_tx_hz_override_ = get_parameter("heartbeat_host_tx_hz_override").as_double();
  ros_queue_depth_ = static_cast<std::size_t>(
    std::max<int64_t>(10, get_parameter("ros_queue_depth").as_int()));
  udp_recv_buffer_bytes_ = static_cast<int>(
    std::max<int64_t>(0, get_parameter("udp_recv_buffer_bytes").as_int()));
  udp_send_buffer_bytes_ = static_cast<int>(
    std::max<int64_t>(0, get_parameter("udp_send_buffer_bytes").as_int()));
  rx_idle_sleep_ms_ = static_cast<int>(
    std::max<int64_t>(0, get_parameter("rx_idle_sleep_ms").as_int()));
  enable_tx_stats_ = get_parameter("enable_tx_stats").as_bool();
  tx_stats_period_sec_ = static_cast<int>(
    std::max<int64_t>(0, get_parameter("tx_stats_period_sec").as_int()));

  // 首次加载配置会创建 UDP socket 和 ROS 路由。若失败直接抛错退出，
  // 不允许节点在“没有有效路由”的状态下继续运行并静默丢数据。
  std::string error;
  if (!reload_config(&error)) {
    throw std::runtime_error("failed to load MAVLink bridge config: " + error);
  }

  running_ = true;
  rx_thread_ = std::thread(&MavlinkBridgeCore::rx_loop, this);

  heartbeat_timer_ = create_wall_timer(
    std::chrono::milliseconds(100),
    std::bind(&MavlinkBridgeCore::heartbeat_timer_callback, this));

  const auto config_check_period_ms = static_cast<int>(
    std::max<int64_t>(100, get_parameter("config_check_period_ms").as_int()));
  config_reload_timer_ = create_wall_timer(
    std::chrono::milliseconds(config_check_period_ms),
    std::bind(&MavlinkBridgeCore::config_reload_timer_callback, this));

  reload_service_ = create_service<ReloadService>(
    "~/reload_config",
    std::bind(
      &MavlinkBridgeCore::reload_service_callback,
      this,
      std::placeholders::_1,
      std::placeholders::_2));

  if (enable_tx_stats_ && tx_stats_period_sec_ > 0) {
    tx_stats_pub_ = create_publisher<std_msgs::msg::String>("~/tx_stats", 10);
    tx_stats_timer_ = create_wall_timer(
      std::chrono::seconds(tx_stats_period_sec_),
      std::bind(&MavlinkBridgeCore::tx_stats_timer_callback, this));
    RCLCPP_INFO(
      get_logger(),
      "MAVLink bridge UDP TX stats enabled: period=%ds topic=~/tx_stats",
      tx_stats_period_sec_);
  }
}

MavlinkBridgeCore::~MavlinkBridgeCore()
{
  running_ = false;
  if (rx_thread_.joinable()) {
    rx_thread_.join();
  }
  close_udp_socket();
}

BridgeConfig MavlinkBridgeCore::load_config_file(const std::string & path) const
{
  const auto root = YAML::LoadFile(path);
  const auto bridge = root["sealien_mavlink_bridge"];
  if (!bridge) {
    throw std::runtime_error("missing root key: sealien_mavlink_bridge");
  }

  BridgeConfig config;
  config.dialect = bridge["dialect"].as<std::string>("");

  const auto host = bridge["host"];
  if (!host) {
    throw std::runtime_error("missing host section");
  }
  config.host_system_id = read_u8(host, "system_id");
  config.host_component_id = read_u8(host, "component_id");
  config.bind_ip = host["bind_ip"].as<std::string>("0.0.0.0");
  config.bind_port = read_u16(host, "bind_port");

  const auto heartbeat = bridge["heartbeat"];
  if (heartbeat) {
    config.heartbeat_host_tx_hz = heartbeat["host_tx_hz"].as<double>(1.0);
    config.heartbeat_endpoint_expected_hz =
      heartbeat["endpoint_expected_hz"].as<double>(1.0);
    config.endpoint_timeout_ms = heartbeat["endpoint_timeout_ms"].as<int>(3000);
  }

  const auto endpoints = bridge["endpoints"];
  if (!endpoints || !endpoints.IsSequence()) {
    throw std::runtime_error("endpoints must be a sequence");
  }

  std::set<std::string> endpoint_names;
  std::set<std::pair<uint8_t, uint8_t>> endpoint_ids;
  for (const auto & item : endpoints) {
    EndpointConfig endpoint;
    endpoint.name = item["name"].as<std::string>();
    endpoint.enabled = item["enabled"].as<bool>(true);
    endpoint.system_id = read_u8(item, "system_id");
    endpoint.component_id = read_u8(item, "component_id");
    endpoint.remote_ip = item["remote_ip"].as<std::string>();
    endpoint.remote_port = read_u16(item, "remote_port");

    const auto messages = item["messages"];
    if (!messages) {
      throw std::runtime_error("endpoint " + endpoint.name + " missing messages");
    }
    endpoint.rx = read_msgids(messages["rx"]);
    endpoint.tx = read_msgids(messages["tx"]);

    // endpoint.name 参与 ROS topic 命名，system_id/component_id 参与入站 MAVLink
    // 身份匹配；两者都必须唯一，否则运行期无法可靠路由。
    if (!endpoint_names.insert(endpoint.name).second) {
      throw std::runtime_error("duplicate endpoint name: " + endpoint.name);
    }
    if (!endpoint_ids.insert({endpoint.system_id, endpoint.component_id}).second) {
      throw std::runtime_error("duplicate endpoint system/component id: " + endpoint.name);
    }
    for (const auto msgid : endpoint.rx) {
      if (!is_supported_msgid(msgid)) {
        throw std::runtime_error("unsupported rx MSGID " + std::to_string(msgid));
      }
    }
    for (const auto msgid : endpoint.tx) {
      if (!is_supported_msgid(msgid)) {
        throw std::runtime_error("unsupported tx MSGID " + std::to_string(msgid));
      }
    }
    config.endpoints.push_back(endpoint);
  }

  return config;
}

bool MavlinkBridgeCore::reload_config(std::string * message)
{
  try {
    auto next = load_config_file(config_file_);
    if (heartbeat_host_tx_hz_override_ >= 0.0) {
      next.heartbeat_host_tx_hz = heartbeat_host_tx_hz_override_;
    }
    std::string error;
    // 先用新配置创建并 bind 新 socket，成功后才替换运行期配置。
    // 这样 YAML 自动重载遇到错误时不会破坏当前正在工作的通信链路。
    if (!open_udp_socket(next, &error)) {
      if (message) {
        *message = error;
      }
      return false;
    }

    {
      std::lock_guard<std::mutex> lock(state_mutex_);
      config_ = next;
      next_heartbeat_tx_ = {};
      // 清空 shared_ptr 会注销旧 ROS 路由，随后按新 YAML 重建。
      // 注意：业务节点应通过 topic 名称感知路由变化，不应持有内部句柄。
      publishers_.clear();
      subscriptions_.clear();
    }
    {
      std::lock_guard<std::mutex> lock(endpoint_state_mutex_);
      endpoint_states_.clear();
      for (const auto & endpoint : next.endpoints) {
        if (endpoint.enabled) {
          endpoint_states_.emplace(endpoint.name, EndpointRuntimeState{});
        }
      }
    }
    {
      std::lock_guard<std::mutex> lock(tx_stats_mutex_);
      tx_counters_.clear();
    }
    rebuild_ros_routes(next);

    if (std::filesystem::exists(config_file_)) {
      config_mtime_ = std::filesystem::last_write_time(config_file_);
    }

    if (message) {
      *message = "loaded " + config_file_;
    }
    RCLCPP_INFO(
      get_logger(),
      "Loaded MAVLink config %s with %zu endpoints heartbeat_host_tx_hz=%.2f",
      config_file_.c_str(),
      next.endpoints.size(),
      next.heartbeat_host_tx_hz);
    for (const auto & endpoint : next.endpoints) {
      RCLCPP_INFO(
        get_logger(),
        "Configured endpoint=%s enabled=%s ip=%s:%u sysid=%u compid=%u rx=%s tx=%s",
        endpoint.name.c_str(),
        endpoint.enabled ? "true" : "false",
        endpoint.remote_ip.c_str(),
        endpoint.remote_port,
        endpoint.system_id,
        endpoint.component_id,
        msgid_set_to_string(endpoint.rx).c_str(),
        msgid_set_to_string(endpoint.tx).c_str());
    }
    return true;
  } catch (const std::exception & e) {
    if (message) {
      *message = e.what();
    }
    return false;
  }
}

void MavlinkBridgeCore::rebuild_ros_routes(const BridgeConfig & config)
{
  // ROS API 完全由 YAML endpoint.messages.rx/tx 生成。
  // 增减 endpoint 或 MSGID 时，优先改 YAML；只有新增协议字段时才需要改 C++ 映射。
  for (const auto & endpoint : config.endpoints) {
    if (!endpoint.enabled) {
      continue;
    }
    for (const auto msgid : endpoint.rx) {
      create_rx_publisher(endpoint, msgid);
    }
    for (const auto msgid : endpoint.tx) {
      create_tx_subscription(endpoint, msgid);
    }
  }
}

bool MavlinkBridgeCore::open_udp_socket(const BridgeConfig & config, std::string * error)
{
  // 先创建临时 fd，bind 成功后再替换共享 socket_fd_。
  // 这是为了保证配置热重载失败时旧 socket 仍然可用。
  const int fd = ::socket(AF_INET, SOCK_DGRAM, 0);
  if (fd < 0) {
    if (error) {
      *error = std::string("socket() failed: ") + std::strerror(errno);
    }
    return false;
  }

  int reuse = 1;
  (void)::setsockopt(fd, SOL_SOCKET, SO_REUSEADDR, &reuse, sizeof(reuse));
  if (udp_recv_buffer_bytes_ > 0 &&
    ::setsockopt(
      fd, SOL_SOCKET, SO_RCVBUF,
      &udp_recv_buffer_bytes_, sizeof(udp_recv_buffer_bytes_)) != 0)
  {
    RCLCPP_WARN(
      get_logger(),
      "setsockopt SO_RCVBUF=%d failed: %s",
      udp_recv_buffer_bytes_,
      std::strerror(errno));
  }
  if (udp_send_buffer_bytes_ > 0 &&
    ::setsockopt(
      fd, SOL_SOCKET, SO_SNDBUF,
      &udp_send_buffer_bytes_, sizeof(udp_send_buffer_bytes_)) != 0)
  {
    RCLCPP_WARN(
      get_logger(),
      "setsockopt SO_SNDBUF=%d failed: %s",
      udp_send_buffer_bytes_,
      std::strerror(errno));
  }

  const int flags = ::fcntl(fd, F_GETFL, 0);
  if (flags >= 0) {
    (void)::fcntl(fd, F_SETFL, flags | O_NONBLOCK);
  }

  sockaddr_in local_addr{};
  local_addr.sin_family = AF_INET;
  local_addr.sin_port = htons(config.bind_port);
  if (::inet_pton(AF_INET, config.bind_ip.c_str(), &local_addr.sin_addr) != 1) {
    if (config.bind_ip == "0.0.0.0") {
      local_addr.sin_addr.s_addr = INADDR_ANY;
    } else {
      if (error) {
        *error = "invalid bind_ip: " + config.bind_ip;
      }
      ::close(fd);
      return false;
    }
  }

  if (::bind(fd, reinterpret_cast<sockaddr *>(&local_addr), sizeof(local_addr)) < 0) {
    if (error) {
      *error = std::string("bind(") + config.bind_ip + ":" +
        std::to_string(config.bind_port) + ") failed: " + std::strerror(errno);
    }
    ::close(fd);
    return false;
  }

  {
    std::lock_guard<std::mutex> lock(socket_mutex_);
    if (socket_fd_ >= 0) {
      ::close(socket_fd_);
    }
    socket_fd_ = fd;
  }

  return true;
}

void MavlinkBridgeCore::close_udp_socket()
{
  std::lock_guard<std::mutex> lock(socket_mutex_);
  if (socket_fd_ >= 0) {
    ::close(socket_fd_);
    socket_fd_ = -1;
  }
}

void MavlinkBridgeCore::rx_loop()
{
  uint8_t buffer[2048];

  // POSIX UDP 收包不放在 ROS executor 中执行，而是由独立线程负责。
  // socket 设置为非阻塞，便于节点退出和配置重载时快速释放。
  while (rclcpp::ok() && running_) {
    sockaddr_in src_addr{};
    socklen_t src_len = sizeof(src_addr);
    ssize_t nbytes = -1;
    {
      std::lock_guard<std::mutex> lock(socket_mutex_);
      if (socket_fd_ >= 0) {
        nbytes = ::recvfrom(
          socket_fd_,
          buffer,
          sizeof(buffer),
          0,
          reinterpret_cast<sockaddr *>(&src_addr),
          &src_len);
      }
    }

    if (nbytes < 0) {
      const int err = errno;
      if (err != EAGAIN && err != EWOULDBLOCK && err != EINTR) {
        RCLCPP_WARN_THROTTLE(
          get_logger(), *get_clock(), 2000,
          "MAVLink UDP recvfrom failed: %s", std::strerror(err));
      }
      if (rx_idle_sleep_ms_ > 0) {
        std::this_thread::sleep_for(std::chrono::milliseconds(rx_idle_sleep_ms_));
      } else {
        std::this_thread::yield();
      }
      continue;
    }

    for (ssize_t i = 0; i < nbytes; ++i) {
      // MAVLink 按字节流解析。一个 UDP datagram 可能包含半帧、一帧或多帧，
      // 统一交给 mavlink_parse_char() 做帧同步和 CRC 校验。
      if (mavlink_parse_char(MAVLINK_COMM_0, buffer[i], &rx_msg_, &rx_status_)) {
        handle_mavlink_message(rx_msg_, src_addr);
      }
    }
  }
}

void MavlinkBridgeCore::record_rx_message(
  const EndpointConfig & endpoint,
  const mavlink_message_t & msg,
  const sockaddr_in & src_addr)
{
  const auto now = std::chrono::steady_clock::now();
  const auto src_ip = ip_to_string(src_addr);
  bool link_up = false;

  {
    std::lock_guard<std::mutex> lock(endpoint_state_mutex_);
    auto & state = endpoint_states_[endpoint.name];

    if (!state.connected) {
      state.connected = true;
      link_up = true;
    }

    state.last_rx = now;
  }

  if (link_up) {
    RCLCPP_INFO(
      get_logger(),
      "MAVLink link up: endpoint=%s peer=%s configured=%s:%u sysid=%u compid=%u first_msgid=%u tx=%s rx=%s",
      endpoint.name.c_str(),
      src_ip.c_str(),
      endpoint.remote_ip.c_str(),
      endpoint.remote_port,
      endpoint.system_id,
      endpoint.component_id,
      msg.msgid,
      msgid_set_to_string(endpoint.tx).c_str(),
      msgid_set_to_string(endpoint.rx).c_str());
  }
}

void MavlinkBridgeCore::check_endpoint_timeouts()
{
  BridgeConfig config;
  {
    std::lock_guard<std::mutex> lock(state_mutex_);
    config = config_;
  }

  const auto now = std::chrono::steady_clock::now();
  const auto timeout = std::chrono::milliseconds(config.endpoint_timeout_ms);

  std::lock_guard<std::mutex> lock(endpoint_state_mutex_);
  for (const auto & endpoint : config.endpoints) {
    if (!endpoint.enabled) {
      continue;
    }

    auto & state = endpoint_states_[endpoint.name];
    if (!state.connected) {
      continue;
    }

    const auto elapsed_since_rx = std::chrono::duration_cast<std::chrono::milliseconds>(
      now - state.last_rx);
    if (state.last_rx.time_since_epoch().count() != 0 && elapsed_since_rx > timeout) {
      RCLCPP_WARN(
        get_logger(),
        "MAVLink link down: endpoint=%s peer=%s:%u sysid=%u compid=%u no_rx_ms=%lld tx=%s rx=%s",
        endpoint.name.c_str(),
        endpoint.remote_ip.c_str(),
        endpoint.remote_port,
        endpoint.system_id,
        endpoint.component_id,
        static_cast<long long>(elapsed_since_rx.count()),
        msgid_set_to_string(endpoint.tx).c_str(),
        msgid_set_to_string(endpoint.rx).c_str());
      state.connected = false;
      continue;
    }
  }
}

void MavlinkBridgeCore::handle_mavlink_message(
  const mavlink_message_t & msg,
  const sockaddr_in & src_addr)
{
  std::optional<EndpointConfig> endpoint;
  {
    std::lock_guard<std::mutex> lock(state_mutex_);
    endpoint = find_incoming_endpoint_locked(msg);
  }

  // bridge 不是“谁发都收”的广播接收器。入站帧必须同时满足：
  // 1. system_id/component_id 匹配某个 enabled endpoint；
  // 2. MSGID 位于该 endpoint 的 rx 白名单。
  // 只有通过校验的数据才会进入 ROS topic。
  if (!endpoint) {
    RCLCPP_DEBUG(
      get_logger(),
      "Drop MAVLink msgid=%u from unknown sys=%u comp=%u",
      msg.msgid,
      msg.sysid,
      msg.compid);
    return;
  }

  if (strict_remote_ip_ && ip_to_string(src_addr) != endpoint->remote_ip) {
    RCLCPP_WARN_THROTTLE(
      get_logger(), *get_clock(), 2000,
      "Drop MAVLink msgid=%u from endpoint %s due to remote IP mismatch: got %s expected %s",
      msg.msgid,
      endpoint->name.c_str(),
      ip_to_string(src_addr).c_str(),
      endpoint->remote_ip.c_str());
    return;
  }

  if (endpoint->rx.count(msg.msgid) == 0U) {
    RCLCPP_WARN_THROTTLE(
      get_logger(), *get_clock(), 2000,
      "Drop MAVLink msgid=%u from endpoint %s: MSGID is not in rx route",
      msg.msgid,
      endpoint->name.c_str());
    return;
  }

  record_rx_message(*endpoint, msg, src_addr);
  publish_rx_message(*endpoint, msg);
}

void MavlinkBridgeCore::heartbeat_timer_callback()
{
  BridgeConfig config;
  {
    std::lock_guard<std::mutex> lock(state_mutex_);
    config = config_;
  }

  if (config.heartbeat_host_tx_hz <= 0.0) {
    check_endpoint_timeouts();
    return;
  }

  const auto now = std::chrono::steady_clock::now();
  const auto period = std::chrono::duration_cast<std::chrono::steady_clock::duration>(
    std::chrono::duration<double>(1.0 / config.heartbeat_host_tx_hz));
  if (next_heartbeat_tx_.time_since_epoch().count() == 0) {
    next_heartbeat_tx_ = now;
  }
  if (now < next_heartbeat_tx_) {
    return;
  }
  do {
    next_heartbeat_tx_ += period;
  } while (next_heartbeat_tx_ <= now);

  mavlink_heartbeat_t heartbeat{};
  heartbeat.timestamp_ms = static_cast<uint32_t>(
    this->now().nanoseconds() / 1000000ULL);
  heartbeat.type = heartbeat_type_;
  heartbeat.system_status = heartbeat_system_status_;
  heartbeat.mavlink_version = 2;

  for (const auto & endpoint : config.endpoints) {
    // HEARTBEAT 也按普通路由处理：
    // - endpoint.tx 包含 0，bridge 才会向该板发送主机心跳；
    // - endpoint.rx 包含 0，bridge 才会接收该板上报心跳。
    // 这样可以针对不同板卡独立开关心跳方向。
    if (!endpoint.enabled || endpoint.tx.count(MAVLINK_MSG_ID_HEARTBEAT) == 0U) {
      continue;
    }
    mavlink_message_t mav_msg{};
    mavlink_msg_heartbeat_encode(
      config.host_system_id,
      config.host_component_id,
      &mav_msg,
      &heartbeat);
    (void)send_message_to_endpoint_unchecked(endpoint, mav_msg);
  }

  check_endpoint_timeouts();
}

void MavlinkBridgeCore::config_reload_timer_callback()
{
  if (!auto_reload_ || config_file_.empty() || !std::filesystem::exists(config_file_)) {
    return;
  }

  const auto mtime = std::filesystem::last_write_time(config_file_);
  if (mtime == config_mtime_) {
    return;
  }

  // 通过文件 mtime 做自动重载，便于联调时快速调整 YAML。
  // 若生产场景需要确定性重载点，可关闭 auto_reload 并调用 ~/reload_config 服务。
  std::string message;
  if (!reload_config(&message)) {
    RCLCPP_ERROR(get_logger(), "Failed to auto-reload MAVLink config: %s", message.c_str());
  }
}

void MavlinkBridgeCore::tx_stats_timer_callback()
{
  if (!enable_tx_stats_) {
    return;
  }

  std_msgs::msg::String stats;
  {
    std::lock_guard<std::mutex> lock(tx_stats_mutex_);
    if (tx_counters_.empty()) {
      return;
    }

    std::ostringstream oss;
    oss << "mavlink_bridge_tx_stats";
    for (auto & item : tx_counters_) {
      auto & counter = item.second;
      const auto window_total = counter.window_success + counter.window_failure;
      const auto total = counter.success + counter.failure;
      const auto failure_pct = window_total == 0U ? 0.0 :
        (static_cast<double>(counter.window_failure) * 100.0 /
        static_cast<double>(window_total));

      oss << " route=" << item.first
          << " win_ok=" << counter.window_success
          << " win_fail=" << counter.window_failure
          << " win_bytes=" << counter.window_bytes
          << " win_fail_pct=" << std::fixed << std::setprecision(2) << failure_pct
          << " total_ok=" << counter.success
          << " total_fail=" << counter.failure
          << " total=" << total
          << " bytes=" << counter.bytes;

      counter.window_success = 0;
      counter.window_failure = 0;
      counter.window_bytes = 0;
    }
    stats.data = oss.str();
  }

  if (tx_stats_pub_) {
    tx_stats_pub_->publish(stats);
  }
  RCLCPP_INFO(get_logger(), "%s", stats.data.c_str());
}

void MavlinkBridgeCore::reload_service_callback(
  const std::shared_ptr<ReloadService::Request> /*request*/,
  std::shared_ptr<ReloadService::Response> response)
{
  response->success = reload_config(&response->message);
}

std::optional<EndpointConfig> MavlinkBridgeCore::find_incoming_endpoint_locked(
  const mavlink_message_t & msg) const
{
  for (const auto & endpoint : config_.endpoints) {
    if (!endpoint.enabled) {
      continue;
    }
    if (endpoint.system_id == msg.sysid && endpoint.component_id == msg.compid) {
      return endpoint;
    }
  }
  return std::nullopt;
}

std::optional<EndpointConfig> MavlinkBridgeCore::find_endpoint_for_tx_locked(
  const std::string & endpoint_name,
  uint32_t msgid) const
{
  for (const auto & endpoint : config_.endpoints) {
    if (!endpoint.enabled || endpoint.name != endpoint_name) {
      continue;
    }
    if (endpoint.tx.count(msgid) == 0U) {
      return std::nullopt;
    }
    return endpoint;
  }
  return std::nullopt;
}

bool MavlinkBridgeCore::send_message_to_endpoint(
  const std::string & endpoint_name,
  uint32_t msgid,
  const mavlink_message_t & msg)
{
  if (msg.msgid != msgid) {
    RCLCPP_WARN(
      get_logger(),
      "Refuse sending route MSGID %u to endpoint %s: encoded MAVLink msgid is %u",
      msgid,
      endpoint_name.c_str(),
      msg.msgid);
    return false;
  }

  std::optional<EndpointConfig> endpoint;
  {
    std::lock_guard<std::mutex> lock(state_mutex_);
    endpoint = find_endpoint_for_tx_locked(endpoint_name, msgid);
  }

  if (!endpoint) {
    RCLCPP_WARN(
      get_logger(),
      "Refuse sending MSGID %u to endpoint %s: route not configured",
      msgid,
      endpoint_name.c_str());
    return false;
  }

  // 所有普通 ROS->MAVLink 下发都必须经过这个白名单入口。
  // send_message_to_endpoint_unchecked() 只给内部已校验流程使用，例如 heartbeat。
  return send_message_to_endpoint_unchecked(*endpoint, msg);
}

bool MavlinkBridgeCore::send_message_to_endpoint_unchecked(
  const EndpointConfig & endpoint,
  const mavlink_message_t & msg)
{
  sockaddr_in remote_addr{};
  remote_addr.sin_family = AF_INET;
  remote_addr.sin_port = htons(endpoint.remote_port);
  if (::inet_pton(AF_INET, endpoint.remote_ip.c_str(), &remote_addr.sin_addr) != 1) {
    RCLCPP_ERROR(
      get_logger(),
      "Invalid remote_ip for endpoint %s: %s",
      endpoint.name.c_str(),
      endpoint.remote_ip.c_str());
    record_tx_result(endpoint, msg.msgid, false, 0U);
    return false;
  }

  uint8_t buffer[MAVLINK_MAX_PACKET_LEN];
  const uint16_t len = mavlink_msg_to_send_buffer(buffer, &msg);

  ssize_t written = -1;
  int err = 0;
  bool socket_ready = true;
  {
    std::lock_guard<std::mutex> lock(socket_mutex_);
    if (socket_fd_ < 0) {
      socket_ready = false;
    } else {
      written = ::sendto(
        socket_fd_,
        buffer,
        len,
        0,
        reinterpret_cast<const sockaddr *>(&remote_addr),
        sizeof(remote_addr));
      if (written < 0) {
        err = errno;
      }
    }
  }

  if (!socket_ready) {
    record_tx_result(endpoint, msg.msgid, false, 0U);
    return false;
  }

  if (written < 0 || static_cast<uint16_t>(written) != len) {
    record_tx_result(endpoint, msg.msgid, false, 0U);
    RCLCPP_WARN(
      get_logger(),
      "sendto endpoint %s msgid=%u failed: %s",
      endpoint.name.c_str(),
      msg.msgid,
      written < 0 ? std::strerror(err) : "short write");
    return false;
  }

  record_tx_result(endpoint, msg.msgid, true, static_cast<uint16_t>(written));
  return true;
}

void MavlinkBridgeCore::record_tx_result(
  const EndpointConfig & endpoint,
  uint32_t msgid,
  bool success,
  uint16_t bytes_written)
{
  if (!enable_tx_stats_) {
    return;
  }

  std::lock_guard<std::mutex> lock(tx_stats_mutex_);
  auto & counter = tx_counters_[endpoint.name + ":" + std::to_string(msgid)];
  if (success) {
    ++counter.success;
    ++counter.window_success;
    counter.bytes += bytes_written;
    counter.window_bytes += bytes_written;
  } else {
    ++counter.failure;
    ++counter.window_failure;
  }
}

void MavlinkBridgeCore::create_rx_publisher(const EndpointConfig & endpoint, uint32_t msgid)
{
  const auto topic = topic_for(endpoint, msgid, true);
  const auto key = publisher_key(endpoint, msgid);
  const auto qos = rclcpp::QoS(rclcpp::KeepLast(ros_queue_depth_));

  rclcpp::PublisherBase::SharedPtr pub;
  // 将线上的 MAVLink MSGID 映射为强类型 ROS publisher。
  // 新增上行 MSGID 时，需要同步修改：
  // 1. is_supported_msgid()
  // 2. msgid_name()/msgid_topic_name()
  // 3. create_rx_publisher()
  // 4. publish_rx_message()
  switch (msgid) {
    case MAVLINK_MSG_ID_HEARTBEAT:
      pub = create_publisher<sealien_ctrlpilot_msgmanagement::msg::HeartbeatStatus>(topic, qos);
      break;
    case MAVLINK_MSG_ID_IMU_DATA:
      pub = create_publisher<sealien_ctrlpilot_msgmanagement::msg::ImuNavStatus>(topic, qos);
      break;
    case MAVLINK_MSG_ID_THRUSTER_STATUS:
      pub = create_publisher<sealien_ctrlpilot_msgmanagement::msg::ThrusterStatus>(topic, qos);
      break;
    case MAVLINK_MSG_ID_GS_STATUS:
      pub = create_publisher<sealien_ctrlpilot_msgmanagement::msg::GsStatus>(topic, qos);
      break;
    case MAVLINK_MSG_ID_LED_STATUS:
      pub = create_publisher<sealien_ctrlpilot_msgmanagement::msg::LedStatus>(topic, qos);
      break;
    case MAVLINK_MSG_ID_VCHECK:
      pub = create_publisher<sealien_ctrlpilot_msgmanagement::msg::VcheckStatus>(topic, qos);
      break;
    case MAVLINK_MSG_ID_HEIGHT_STATUS:
      pub = create_publisher<sealien_ctrlpilot_msgmanagement::msg::SonarAltimeterStatus>(topic, qos);
      break;
    case MAVLINK_MSG_ID_DEPTH_STATUS:
      pub = create_publisher<sealien_ctrlpilot_msgmanagement::msg::DepthStatus>(topic, qos);
      break;
    case MAVLINK_MSG_ID_BEM280:
      pub = create_publisher<sealien_ctrlpilot_msgmanagement::msg::Bme280Status>(topic, qos);
      break;
    case MAVLINK_MSG_ID_SWITCH_STATUS:
      pub = create_publisher<sealien_ctrlpilot_msgmanagement::msg::SwitchStatus>(topic, qos);
      break;
    case MAVLINK_MSG_ID_DVL_DATA:
      pub = create_publisher<sealien_ctrlpilot_msgmanagement::msg::DvlData>(topic, qos);
      break;
    case MAVLINK_MSG_ID_MIXED_IO_DATA:
      pub = create_publisher<sealien_ctrlpilot_msgmanagement::msg::MixedIoData>(topic, qos);
      break;
    case MAVLINK_MSG_ID_VALVE_STATUS:
      pub = create_publisher<sealien_ctrlpilot_msgmanagement::msg::ValveStatus>(topic, qos);
      break;
    default:
      return;
  }

  std::lock_guard<std::mutex> lock(state_mutex_);
  publishers_[key] = pub;
}

void MavlinkBridgeCore::create_tx_subscription(const EndpointConfig & endpoint, uint32_t msgid)
{
  const auto topic = topic_for(endpoint, msgid, false);
  const auto qos = rclcpp::QoS(rclcpp::KeepLast(ros_queue_depth_));
  rclcpp::SubscriptionBase::SharedPtr sub;

  // 回调只捕获 endpoint.name，不捕获完整 EndpointConfig。
  // 这样 YAML 热重载修改 IP/端口/tx 白名单后，回调会在发送前重新查最新配置。
  switch (msgid) {
    case MAVLINK_MSG_ID_HEARTBEAT:
      sub = create_subscription<sealien_ctrlpilot_msgmanagement::msg::HeartbeatStatus>(
        topic, qos, [this, endpoint_name = endpoint.name](
          sealien_ctrlpilot_msgmanagement::msg::HeartbeatStatus::SharedPtr ros_msg) {
          BridgeConfig current;
          {
            std::lock_guard<std::mutex> lock(state_mutex_);
            current = config_;
          }
          mavlink_heartbeat_t mav{};
          mav.timestamp_ms = ros_msg->timestamp_ms;
          mav.type = ros_msg->type;
          mav.system_status = ros_msg->system_status;
          mav.mavlink_version = ros_msg->mavlink_version;
          mavlink_message_t out{};
          mavlink_msg_heartbeat_encode(
            current.host_system_id, current.host_component_id, &out, &mav);
          (void)send_message_to_endpoint(endpoint_name, MAVLINK_MSG_ID_HEARTBEAT, out);
        });
      break;
    case MAVLINK_MSG_ID_THRUSTER_CMD:
      sub = create_subscription<sealien_ctrlpilot_msgmanagement::msg::ThrusterCmd>(
        topic, qos, [this, endpoint_name = endpoint.name](
          sealien_ctrlpilot_msgmanagement::msg::ThrusterCmd::SharedPtr ros_msg) {
          BridgeConfig current;
          {
            std::lock_guard<std::mutex> lock(state_mutex_);
            current = config_;
          }
          mavlink_thruster_cmd_t mav{};
          mav.speed[0] = ros_msg->thru1;
          mav.speed[1] = ros_msg->thru2;
          mav.speed[2] = ros_msg->thru3;
          mav.speed[3] = ros_msg->thru4;
          mav.speed[4] = ros_msg->thru5;
          mav.speed[5] = ros_msg->thru6;
          mav.speed[6] = ros_msg->thru7;
          mav.speed[7] = ros_msg->thru8;
          mav.speed[8] = ros_msg->thru9;
          mav.speed[9] = ros_msg->thru10;
          mav.speed[10] = ros_msg->thru11;
          mav.speed[11] = ros_msg->thru12;
          mavlink_message_t out{};
          mavlink_msg_thruster_cmd_encode(
            current.host_system_id, current.host_component_id, &out, &mav);
          (void)send_message_to_endpoint(endpoint_name, MAVLINK_MSG_ID_THRUSTER_CMD, out);
        });
      break;
    case MAVLINK_MSG_ID_THRUSTER_LOCK:
      sub = create_subscription<sealien_ctrlpilot_msgmanagement::msg::ThrusterLock>(
        topic, qos, [this, endpoint_name = endpoint.name](
          sealien_ctrlpilot_msgmanagement::msg::ThrusterLock::SharedPtr ros_msg) {
          BridgeConfig current;
          {
            std::lock_guard<std::mutex> lock(state_mutex_);
            current = config_;
          }
          mavlink_thruster_lock_t mav{};
          mav.lock = ros_msg->lock;
          mavlink_message_t out{};
          mavlink_msg_thruster_lock_encode(
            current.host_system_id, current.host_component_id, &out, &mav);
          (void)send_message_to_endpoint(endpoint_name, MAVLINK_MSG_ID_THRUSTER_LOCK, out);
        });
      break;
    case MAVLINK_MSG_ID_IMU_CALIB:
      sub = create_subscription<sealien_ctrlpilot_msgmanagement::msg::ImuCalib>(
        topic, qos, [this, endpoint_name = endpoint.name](
          sealien_ctrlpilot_msgmanagement::msg::ImuCalib::SharedPtr ros_msg) {
          BridgeConfig current;
          {
            std::lock_guard<std::mutex> lock(state_mutex_);
            current = config_;
          }
          mavlink_imu_calib_t mav{};
          mav.lon = ros_msg->lon;
          mav.lat = ros_msg->lat;
          mav.alt = ros_msg->alt;
          mavlink_message_t out{};
          mavlink_msg_imu_calib_encode(
            current.host_system_id, current.host_component_id, &out, &mav);
          (void)send_message_to_endpoint(endpoint_name, MAVLINK_MSG_ID_IMU_CALIB, out);
        });
      break;
    case MAVLINK_MSG_ID_IMU_CLEAR:
      sub = create_subscription<sealien_ctrlpilot_msgmanagement::msg::ImuClear>(
        topic, qos, [this, endpoint_name = endpoint.name](
          sealien_ctrlpilot_msgmanagement::msg::ImuClear::SharedPtr ros_msg) {
          BridgeConfig current;
          {
            std::lock_guard<std::mutex> lock(state_mutex_);
            current = config_;
          }
          mavlink_imu_clear_t mav{};
          mav.clear = ros_msg->clear;
          mavlink_message_t out{};
          mavlink_msg_imu_clear_encode(
            current.host_system_id, current.host_component_id, &out, &mav);
          (void)send_message_to_endpoint(endpoint_name, MAVLINK_MSG_ID_IMU_CLEAR, out);
        });
      break;
    case MAVLINK_MSG_ID_LED_CMD:
      sub = create_subscription<sealien_ctrlpilot_msgmanagement::msg::LedCmd>(
        topic, qos, [this, endpoint_name = endpoint.name](
          sealien_ctrlpilot_msgmanagement::msg::LedCmd::SharedPtr ros_msg) {
          BridgeConfig current;
          {
            std::lock_guard<std::mutex> lock(state_mutex_);
            current = config_;
          }
          mavlink_led_cmd_t mav{};
          mav.index = ros_msg->index;
          mav.pwm = ros_msg->pwm;
          mavlink_message_t out{};
          mavlink_msg_led_cmd_encode(
            current.host_system_id, current.host_component_id, &out, &mav);
          (void)send_message_to_endpoint(endpoint_name, MAVLINK_MSG_ID_LED_CMD, out);
        });
      break;
    case MAVLINK_MSG_ID_GS_CMD:
      sub = create_subscription<sealien_ctrlpilot_msgmanagement::msg::GsCmd>(
        topic, qos, [this, endpoint_name = endpoint.name](
          sealien_ctrlpilot_msgmanagement::msg::GsCmd::SharedPtr ros_msg) {
          BridgeConfig current;
          {
            std::lock_guard<std::mutex> lock(state_mutex_);
            current = config_;
          }
          mavlink_gs_cmd_t mav{};
          mav.index = ros_msg->index;
          mav.angle = ros_msg->angle_deg;
          mavlink_message_t out{};
          mavlink_msg_gs_cmd_encode(
            current.host_system_id, current.host_component_id, &out, &mav);
          (void)send_message_to_endpoint(endpoint_name, MAVLINK_MSG_ID_GS_CMD, out);
        });
      break;
    case MAVLINK_MSG_ID_GS_CFG:
      sub = create_subscription<sealien_ctrlpilot_msgmanagement::msg::GsCfg>(
        topic, qos, [this, endpoint_name = endpoint.name](
          sealien_ctrlpilot_msgmanagement::msg::GsCfg::SharedPtr ros_msg) {
          BridgeConfig current;
          {
            std::lock_guard<std::mutex> lock(state_mutex_);
            current = config_;
          }
          mavlink_gs_cfg_t mav{};
          copy_to_mav_array(mav.max_angle, ros_msg->max_angle_deg);
          copy_to_mav_array(mav.min_angle, ros_msg->min_angle_deg);
          copy_to_mav_array(mav.step, ros_msg->step);
          mavlink_message_t out{};
          mavlink_msg_gs_cfg_encode(
            current.host_system_id, current.host_component_id, &out, &mav);
          (void)send_message_to_endpoint(endpoint_name, MAVLINK_MSG_ID_GS_CFG, out);
        });
      break;
    case MAVLINK_MSG_ID_SWITCH_CMD:
      sub = create_subscription<sealien_ctrlpilot_msgmanagement::msg::SwitchCmd>(
        topic, qos, [this, endpoint_name = endpoint.name](
          sealien_ctrlpilot_msgmanagement::msg::SwitchCmd::SharedPtr ros_msg) {
          BridgeConfig current;
          {
            std::lock_guard<std::mutex> lock(state_mutex_);
            current = config_;
          }
          mavlink_switch_cmd_t mav{};
          mav.index = ros_msg->index;
          mav.value = ros_msg->value;
          mavlink_message_t out{};
          mavlink_msg_switch_cmd_encode(
            current.host_system_id, current.host_component_id, &out, &mav);
          (void)send_message_to_endpoint(endpoint_name, MAVLINK_MSG_ID_SWITCH_CMD, out);
        });
      break;
    case MAVLINK_MSG_ID_MIXED_IO_CMD:
      sub = create_subscription<sealien_ctrlpilot_msgmanagement::msg::MixedIoCmd>(
        topic, qos, [this, endpoint_name = endpoint.name](
          sealien_ctrlpilot_msgmanagement::msg::MixedIoCmd::SharedPtr ros_msg) {
          BridgeConfig current;
          {
            std::lock_guard<std::mutex> lock(state_mutex_);
            current = config_;
          }
          mavlink_mixed_io_cmd_t mav{};
          mav.gpio_1_32_output = ros_msg->gpio_1_32_output;
          mav.gpio_33_64_output = ros_msg->gpio_33_64_output;
          copy_to_mav_array(mav.dac_dev1_Vout, ros_msg->dac_dev1_vout);
          copy_to_mav_array(mav.dac_dev2_Vout, ros_msg->dac_dev2_vout);
          copy_to_mav_array(mav.dac_dev3_Vout, ros_msg->dac_dev3_vout);
          mavlink_message_t out{};
          mavlink_msg_mixed_io_cmd_encode(
            current.host_system_id, current.host_component_id, &out, &mav);
          (void)send_message_to_endpoint(endpoint_name, MAVLINK_MSG_ID_MIXED_IO_CMD, out);
        });
      break;
    case MAVLINK_MSG_ID_VALVE_CMD:
      sub = create_subscription<sealien_ctrlpilot_msgmanagement::msg::ValveCmd>(
        topic, qos, [this, endpoint_name = endpoint.name](
          sealien_ctrlpilot_msgmanagement::msg::ValveCmd::SharedPtr ros_msg) {
          BridgeConfig current;
          {
            std::lock_guard<std::mutex> lock(state_mutex_);
            current = config_;
          }
          mavlink_valve_cmd_t mav{};
          mav.timestamp_ms = ros_msg->timestamp_ms;
          mav.sensor_power_mask = ros_msg->sensor_power_mask;
          copy_to_mav_array(mav.current_ma, ros_msg->current_ma);
          copy_to_mav_array(mav.freq_hz, ros_msg->freq_hz);
          mavlink_message_t out{};
          mavlink_msg_valve_cmd_encode(
            current.host_system_id, current.host_component_id, &out, &mav);
          (void)send_message_to_endpoint(endpoint_name, MAVLINK_MSG_ID_VALVE_CMD, out);
        });
      break;
    default:
      break;
  }

  if (sub) {
    std::lock_guard<std::mutex> lock(state_mutex_);
    subscriptions_.push_back(sub);
  }
}

void MavlinkBridgeCore::publish_rx_message(
  const EndpointConfig & endpoint,
  const mavlink_message_t & msg)
{
  const auto key = publisher_key(endpoint, msg.msgid);

  // 只有通过身份和 rx 白名单校验后才解码 payload。
  // 字段赋值保持显式展开，允许 MAVLink XML、工作表和 ROS msg 字段名不完全一致。
  switch (msg.msgid) {
    case MAVLINK_MSG_ID_HEARTBEAT: {
      mavlink_heartbeat_t mav{};
      mavlink_msg_heartbeat_decode(&msg, &mav);
      sealien_ctrlpilot_msgmanagement::msg::HeartbeatStatus ros_msg;
      ros_msg.header.stamp = now();
      ros_msg.header.frame_id = endpoint.name;
      ros_msg.timestamp_ms = mav.timestamp_ms;
      ros_msg.type = mav.type;
      ros_msg.system_status = mav.system_status;
      ros_msg.mavlink_version = mav.mavlink_version;
      publish_typed(key, ros_msg);
      break;
    }
    case MAVLINK_MSG_ID_IMU_DATA: {
      mavlink_imu_data_t mav{};
      mavlink_msg_imu_data_decode(&msg, &mav);
      sealien_ctrlpilot_msgmanagement::msg::ImuNavStatus ros_msg;
      ros_msg.header.stamp = now();
      ros_msg.header.frame_id = endpoint.name;
      ros_msg.timestamp_ms = mav.timestamp_ms;
      ros_msg.longitude_deg = mav.lon;
      ros_msg.latitude_deg = mav.lat;
      ros_msg.altitude_m = mav.alt;
      ros_msg.velocity_mps.x = mav.vel_n;
      ros_msg.velocity_mps.y = mav.vel_e;
      ros_msg.velocity_mps.z = mav.vel_u;
      ros_msg.linear_acceleration_mps2.x = mav.acc_x;
      ros_msg.linear_acceleration_mps2.y = mav.acc_y;
      ros_msg.linear_acceleration_mps2.z = mav.acc_z;
      ros_msg.roll_deg = mav.roll;
      ros_msg.pitch_deg = mav.pitch;
      ros_msg.yaw_deg = mav.yaw;
      ros_msg.angular_velocity_dps.x = mav.gyro_x;
      ros_msg.angular_velocity_dps.y = mav.gyro_y;
      ros_msg.angular_velocity_dps.z = mav.gyro_z;
      ros_msg.temperature_c = mav.temp;
      ros_msg.heading_turns = mav.turns;
      ros_msg.imu_status_code = mav.imu_status;
      ros_msg.imu_error_code = mav.fault;
      ros_msg.poweron_calibrating = static_cast<int8_t>(mav.is_calibrating);
      ros_msg.dvl_velocity_mps.x = mav.dvl_velx;
      ros_msg.dvl_velocity_mps.y = mav.dvl_vely;
      ros_msg.dvl_velocity_mps.z = mav.dvl_velz;
      ros_msg.dvl_height = mav.dvl_height;
      ros_msg.dvl_status = mav.dvl_status;
      publish_typed(key, ros_msg);
      break;
    }
    case MAVLINK_MSG_ID_THRUSTER_STATUS: {
      mavlink_thruster_status_t mav{};
      mavlink_msg_thruster_status_decode(&msg, &mav);
      sealien_ctrlpilot_msgmanagement::msg::ThrusterStatus ros_msg;
      ros_msg.header.stamp = now();
      ros_msg.header.frame_id = endpoint.name;
      ros_msg.timestamp_ms = mav.timestamp_ms;
      copy_to_ros_array(ros_msg.speed_rpm, mav.speed);
      copy_to_ros_array(ros_msg.power_w, mav.power);
      copy_to_ros_array(ros_msg.temperature_c, mav.temp);
      copy_to_ros_array(ros_msg.thruster_status_code, mav.status);
      copy_to_ros_array(ros_msg.thruster_error_code, mav.fault);
      ros_msg.power_lock = mav.lock;
      publish_typed(key, ros_msg);
      break;
    }
    case MAVLINK_MSG_ID_GS_STATUS: {
      mavlink_gs_status_t mav{};
      mavlink_msg_gs_status_decode(&msg, &mav);
      sealien_ctrlpilot_msgmanagement::msg::GsStatus ros_msg;
      ros_msg.header.stamp = now();
      ros_msg.header.frame_id = endpoint.name;
      ros_msg.timestamp_ms = mav.timestamp_ms;
      copy_to_ros_array(ros_msg.angle_deg, mav.angle);
      copy_to_ros_array(ros_msg.step, mav.step);
      copy_to_ros_array(ros_msg.res, mav.res);
      publish_typed(key, ros_msg);
      break;
    }
    case MAVLINK_MSG_ID_LED_STATUS: {
      mavlink_led_status_t mav{};
      mavlink_msg_led_status_decode(&msg, &mav);
      sealien_ctrlpilot_msgmanagement::msg::LedStatus ros_msg;
      ros_msg.header.stamp = now();
      ros_msg.header.frame_id = endpoint.name;
      ros_msg.timestamp_ms = mav.timestamp_ms;
      ros_msg.ledpwm1 = mav.ledpwm1;
      ros_msg.ledpwm2 = mav.ledpwm2;
      ros_msg.ledpwm3 = mav.ledpwm3;
      ros_msg.ledpwm4 = mav.ledpwm4;
      ros_msg.ledpwm5 = mav.ledpwm5;
      ros_msg.ledpwm6 = mav.ledpwm6;
      ros_msg.ledpwm7 = mav.ledpwm7;
      ros_msg.ledpwm8 = mav.ledpwm8;
      ros_msg.ledpwm9 = mav.ledpwm9;
      ros_msg.ledpwm10 = mav.ledpwm10;
      publish_typed(key, ros_msg);
      break;
    }
    case MAVLINK_MSG_ID_VCHECK: {
      mavlink_vcheck_t mav{};
      mavlink_msg_vcheck_decode(&msg, &mav);
      sealien_ctrlpilot_msgmanagement::msg::VcheckStatus ros_msg;
      ros_msg.header.stamp = now();
      ros_msg.header.frame_id = endpoint.name;
      ros_msg.timestamp_ms = mav.timestamp_ms;
      copy_to_ros_array(ros_msg.v_status, mav.v_status);
      copy_to_ros_array(ros_msg.temperature_c, mav.temp);
      publish_typed(key, ros_msg);
      break;
    }
    case MAVLINK_MSG_ID_HEIGHT_STATUS: {
      mavlink_height_status_t mav{};
      mavlink_msg_height_status_decode(&msg, &mav);
      sealien_ctrlpilot_msgmanagement::msg::SonarAltimeterStatus ros_msg;
      ros_msg.header.stamp = now();
      ros_msg.header.frame_id = endpoint.name;
      ros_msg.timestamp_ms = mav.timestamp_ms;
      copy_to_ros_array(ros_msg.near_dist_cm, mav.near_dist);
      copy_to_ros_array(ros_msg.near_stren, mav.near_stren);
      copy_to_ros_array(ros_msg.far_dist_cm, mav.far_dist);
      copy_to_ros_array(ros_msg.far_stren, mav.far_stren);
      copy_to_ros_array(ros_msg.most_dist_cm, mav.most_dist);
      copy_to_ros_array(ros_msg.most_stren, mav.most_stren);
      publish_typed(key, ros_msg);
      break;
    }
    case MAVLINK_MSG_ID_DEPTH_STATUS: {
      mavlink_depth_status_t mav{};
      mavlink_msg_depth_status_decode(&msg, &mav);
      sealien_ctrlpilot_msgmanagement::msg::DepthStatus ros_msg;
      ros_msg.header.stamp = now();
      ros_msg.header.frame_id = endpoint.name;
      ros_msg.timestamp_ms = mav.timestamp_ms;
      copy_to_ros_array(ros_msg.depth_m, mav.depth);
      copy_to_ros_array(ros_msg.temperature_c, mav.temp);
      publish_typed(key, ros_msg);
      break;
    }
    case MAVLINK_MSG_ID_BEM280: {
      mavlink_bem280_t mav{};
      mavlink_msg_bem280_decode(&msg, &mav);
      sealien_ctrlpilot_msgmanagement::msg::Bme280Status ros_msg;
      ros_msg.header.stamp = now();
      ros_msg.header.frame_id = endpoint.name;
      ros_msg.timestamp_ms = mav.timestamp_ms;
      ros_msg.temperature_c = mav.temp;
      ros_msg.humidity_rh = mav.humi;
      ros_msg.press_hpa = mav.press;
      publish_typed(key, ros_msg);
      break;
    }
    case MAVLINK_MSG_ID_SWITCH_STATUS: {
      mavlink_switch_status_t mav{};
      mavlink_msg_switch_status_decode(&msg, &mav);
      sealien_ctrlpilot_msgmanagement::msg::SwitchStatus ros_msg;
      ros_msg.header.stamp = now();
      ros_msg.header.frame_id = endpoint.name;
      ros_msg.timestamp_ms = mav.timestamp_ms;
      copy_to_ros_array(ros_msg.switch_status, mav.switchs);
      publish_typed(key, ros_msg);
      break;
    }
    case MAVLINK_MSG_ID_DVL_DATA: {
      mavlink_dvl_data_t mav{};
      mavlink_msg_dvl_data_decode(&msg, &mav);
      sealien_ctrlpilot_msgmanagement::msg::DvlData ros_msg;
      ros_msg.header.stamp = now();
      ros_msg.header.frame_id = endpoint.name;
      ros_msg.timestamp_ms = mav.timestamp_ms;
      copy_to_ros_array(ros_msg.bt_range_m, mav.BT_range);
      copy_to_ros_array(ros_msg.bt_velocity_mps, mav.BT_vel);
      copy_to_ros_array(ros_msg.bt_percent_good, mav.BT_percent_good);
      ros_msg.bt_max_depth_m = mav.BT_max_depth;
      copy_to_ros_array(ros_msg.wp_cell1_velocity_mps, mav.WP_Cell1_vel);
      copy_to_ros_array(ros_msg.wp_cell1_percent_good, mav.WP_Cell1_percent_good);
      copy_to_ros_array(ros_msg.wp_cell2_velocity_mps, mav.WP_Cell2_vel);
      copy_to_ros_array(ros_msg.wp_cell2_percent_good, mav.WP_Cell2_percent_good);
      copy_to_ros_array(ros_msg.wp_cell3_velocity_mps, mav.WP_Cell3_vel);
      copy_to_ros_array(ros_msg.wp_cell3_percent_good, mav.WP_Cell3_percent_good);
      copy_to_ros_array(ros_msg.wp_cell4_velocity_mps, mav.WP_Cell4_vel);
      copy_to_ros_array(ros_msg.wp_cell4_percent_good, mav.WP_Cell4_percent_good);
      copy_to_ros_array(ros_msg.wp_cell5_velocity_mps, mav.WP_Cell5_vel);
      copy_to_ros_array(ros_msg.wp_cell5_percent_good, mav.WP_Cell5_percent_good);
      copy_to_ros_array(ros_msg.wp_cell6_velocity_mps, mav.WP_Cell6_vel);
      copy_to_ros_array(ros_msg.wp_cell6_percent_good, mav.WP_Cell6_percent_good);
      copy_to_ros_array(ros_msg.wp_cell7_velocity_mps, mav.WP_Cell7_vel);
      copy_to_ros_array(ros_msg.wp_cell7_percent_good, mav.WP_Cell7_percent_good);
      copy_to_ros_array(ros_msg.wp_cell8_velocity_mps, mav.WP_Cell8_vel);
      copy_to_ros_array(ros_msg.wp_cell8_percent_good, mav.WP_Cell8_percent_good);
      copy_to_ros_array(ros_msg.wp_cell9_velocity_mps, mav.WP_Cell9_vel);
      copy_to_ros_array(ros_msg.wp_cell9_percent_good, mav.WP_Cell9_percent_good);
      copy_to_ros_array(ros_msg.wp_cell10_velocity_mps, mav.WP_Cell10_vel);
      copy_to_ros_array(ros_msg.wp_cell10_percent_good, mav.WP_Cell10_percent_good);
      publish_typed(key, ros_msg);
      break;
    }
    case MAVLINK_MSG_ID_MIXED_IO_DATA: {
      mavlink_mixed_io_data_t mav{};
      mavlink_msg_mixed_io_data_decode(&msg, &mav);
      sealien_ctrlpilot_msgmanagement::msg::MixedIoData ros_msg;
      ros_msg.header.stamp = now();
      ros_msg.header.frame_id = endpoint.name;
      ros_msg.timestamp_ms = mav.timestamp_ms;
      ros_msg.gpio_1_32_output = mav.gpio_1_32_output;
      ros_msg.gpio_33_64_output = mav.gpio_33_64_output;
      ros_msg.gpio_1_32_input = mav.gpio_1_32_input;
      ros_msg.gpio_33_64_input = mav.gpio_33_64_input;
      copy_to_ros_array(ros_msg.dac_dev1_vout, mav.dac_dev1_Vout);
      copy_to_ros_array(ros_msg.dac_dev2_vout, mav.dac_dev2_Vout);
      copy_to_ros_array(ros_msg.dac_dev3_vout, mav.dac_dev3_Vout);
      copy_to_ros_array(ros_msg.adc_dev1_vin, mav.adc_dev1_Vin);
      copy_to_ros_array(ros_msg.adc_dev2_vin, mav.adc_dev2_Vin);
      copy_to_ros_array(ros_msg.adc_dev3_vin, mav.adc_dev3_Vin);
      publish_typed(key, ros_msg);
      break;
    }
    case MAVLINK_MSG_ID_VALVE_STATUS: {
      mavlink_valve_status_t mav{};
      mavlink_msg_valve_status_decode(&msg, &mav);
      sealien_ctrlpilot_msgmanagement::msg::ValveStatus ros_msg;
      ros_msg.header.stamp = now();
      ros_msg.header.frame_id = endpoint.name;
      ros_msg.timestamp_ms = mav.timestamp_ms;
      copy_to_ros_array(ros_msg.valve_current_x10, mav.valve_current_x10);
      copy_to_ros_array(ros_msg.valve_state, mav.valve_state);
      copy_to_ros_array(ros_msg.encoder, mav.encoder);
      copy_to_ros_array(ros_msg.sensor_data, mav.sensor_data);
      ros_msg.water_in_mv = mav.water_in_mv;
      ros_msg.board_voltage_mv = mav.board_voltage_mv;
      copy_to_ros_array(ros_msg.temp_x10, mav.temp_x10);
      publish_typed(key, ros_msg);
      break;
    }
    default:
      RCLCPP_DEBUG(get_logger(), "No ROS publisher mapping for msgid=%u", msg.msgid);
      break;
  }
}

std::string MavlinkBridgeCore::topic_for(
  const EndpointConfig & endpoint,
  uint32_t msgid,
  bool rx) const
{
  const auto direction = rx ? "from_mcu" : "to_mcu";
  // Example: rov/from_mcu/nav_sensor_mcu/imu_data.
  // Keeping endpoint in the topic prevents topic-level broadcast semantics.
  if (topic_prefix_.empty()) {
    return direction + std::string("/") + endpoint.name + "/" + msgid_topic_name(msgid);
  }
  return topic_prefix_ + "/" + direction + "/" + endpoint.name + "/" + msgid_topic_name(msgid);
}

std::string MavlinkBridgeCore::publisher_key(
  const EndpointConfig & endpoint,
  uint32_t msgid) const
{
  return endpoint.name + ":" + std::to_string(msgid);
}

std::string MavlinkBridgeCore::msgid_name(uint32_t msgid)
{
  switch (msgid) {
    case 0: return "HEARTBEAT";
    case 1: return "IMU_DATA";
    case 2: return "THRUSTER_STATUS";
    case 3: return "GS_STATUS";
    case 4: return "LED_STATUS";
    case 5: return "VCHECK";
    case 6: return "HEIGHT_STATUS";
    case 7: return "DEPTH_STATUS";
    case 8: return "BEM280";
    case 9: return "SWITCH_STATUS";
    case 10: return "THRUSTER_CMD";
    case 11: return "THRUSTER_LOCK";
    case 12: return "IMU_CALIB";
    case 13: return "IMU_CLEAR";
    case 14: return "LED_CMD";
    case 15: return "GS_CMD";
    case 16: return "GS_CFG";
    case 17: return "SWITCH_CMD";
    case 18: return "DVL_DATA";
    case 19: return "MIXED_IO_CMD";
    case 20: return "MIXED_IO_DATA";
    case 21: return "VALVE_CMD";
    case 22: return "VALVE_STATUS";
    default: return "UNKNOWN";
  }
}

std::string MavlinkBridgeCore::msgid_topic_name(uint32_t msgid)
{
  std::string name = msgid_name(msgid);
  std::transform(name.begin(), name.end(), name.begin(), [](unsigned char c) {
    return static_cast<char>(std::tolower(c));
  });
  return name;
}

std::string MavlinkBridgeCore::msgid_set_to_string(const std::set<uint32_t> & ids)
{
  std::ostringstream oss;
  oss << "[";
  bool first = true;
  for (const auto msgid : ids) {
    if (!first) {
      oss << ",";
    }
    first = false;
    oss << msgid;
  }
  oss << "]";
  return oss.str();
}

bool MavlinkBridgeCore::is_supported_msgid(uint32_t msgid)
{
  // The generated MAVLink header exposes MAVLINK_MESSAGE_CRCS, and
  // mavlink_get_msg_entry() searches that table. This keeps YAML validation in
  // sync with sealien_mavlink.xml after regenerating the dialect, and avoids a
  // hand-maintained "max MSGID" constant that would also allow gaps by mistake.
  return mavlink_get_msg_entry(msgid) != nullptr;
}

}  // namespace sealien_ctrlpilot_mavlinkbridge
