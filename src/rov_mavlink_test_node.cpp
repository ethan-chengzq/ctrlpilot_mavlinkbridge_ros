#include <algorithm>
#include <chrono>
#include <cctype>
#include <cstdint>
#include <functional>
#include <iomanip>
#include <memory>
#include <mutex>
#include <set>
#include <sstream>
#include <stdexcept>
#include <string>
#include <unordered_map>
#include <vector>

#include "ament_index_cpp/get_package_share_directory.hpp"
#include "rclcpp/rclcpp.hpp"
#include "std_msgs/msg/string.hpp"
#include "yaml-cpp/yaml.h"

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

#ifndef ROV_MAVLINK_TEST_ENABLE_ANSI_LOG
#define ROV_MAVLINK_TEST_ENABLE_ANSI_LOG 1
#endif

namespace
{

#if ROV_MAVLINK_TEST_ENABLE_ANSI_LOG
constexpr const char * kLogReset = "\033[0m";
constexpr const char * kLogCyan = "\033[36m";
constexpr const char * kLogGreen = "\033[32m";
constexpr const char * kLogYellow = "\033[33m";
constexpr const char * kLogMagenta = "\033[35m";
#else
constexpr const char * kLogReset = "";
constexpr const char * kLogCyan = "";
constexpr const char * kLogGreen = "";
constexpr const char * kLogYellow = "";
constexpr const char * kLogMagenta = "";
#endif

constexpr const char * kLogSeparator = "--------------------------------------------------";

struct TestEndpoint
{
  std::string name;
  bool enabled{true};
  uint32_t system_id{0};
  uint32_t component_id{0};
  std::string remote_ip;
  uint32_t remote_port{0};
  std::set<uint32_t> rx;
  std::set<uint32_t> tx;
};

struct EndpointQuality
{
  bool linked{false};
  std::chrono::steady_clock::time_point last_rx{};
  uint64_t link_up_count{0};
  uint64_t link_down_count{0};
  uint32_t last_rx_msgid{0};
};

struct RateSummary
{
  uint64_t total{0};
  uint64_t delta{0};
  double rate_hz{0.0};
  std::string messages{"none"};
};

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

std::string msgid_name(uint32_t msgid)
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

std::string msgid_topic_name(uint32_t msgid)
{
  auto name = msgid_name(msgid);
  std::transform(name.begin(), name.end(), name.begin(), [](unsigned char c) {
    return static_cast<char>(std::tolower(c));
  });
  return name;
}

}  // namespace

class RovMavlinkTestNode : public rclcpp::Node
{
public:
  explicit RovMavlinkTestNode(const std::string & default_config_file)
  : Node("rov_mavlink_test_node")
  {
    declare_parameter<std::string>("config_file", default_config_file);
    declare_parameter<std::string>("topic_prefix", "rov");
    declare_parameter<std::vector<std::string>>("target_endpoints", std::vector<std::string>{});
    declare_parameter<int>("tx_period_ms", 1000);
    declare_parameter<int>("quality_report_period_sec", 5);
    declare_parameter<int>("quality_link_timeout_ms", 3000);
    declare_parameter<bool>("include_heartbeat_tx", false);
    declare_parameter<bool>("log_quality_report", true);
    declare_parameter<bool>("safe_mode", true);

    config_file_ = get_parameter("config_file").as_string();
    topic_prefix_ = trim_slashes(get_parameter("topic_prefix").as_string());
    target_endpoints_ = get_parameter("target_endpoints").as_string_array();
    include_heartbeat_tx_ = get_parameter("include_heartbeat_tx").as_bool();
    log_quality_report_ = get_parameter("log_quality_report").as_bool();
    quality_link_timeout_ms_ =
      static_cast<uint32_t>(std::max<int64_t>(100, get_parameter("quality_link_timeout_ms").as_int()));
    safe_mode_ = get_parameter("safe_mode").as_bool();

    rx_event_pub_ = create_publisher<std_msgs::msg::String>(test_topic("rx_events"), 50);
    tx_event_pub_ = create_publisher<std_msgs::msg::String>(test_topic("tx_events"), 50);
    quality_summary_pub_ = create_publisher<std_msgs::msg::String>(test_topic("quality_summary"), 10);
    legacy_rx_summary_pub_ = create_publisher<std_msgs::msg::String>(test_topic("rx_summary"), 10);

    const auto endpoints = load_endpoints(config_file_);
    build_routes(endpoints);

    tx_period_ms_ = static_cast<uint32_t>(
      std::max<int64_t>(100, get_parameter("tx_period_ms").as_int()));
    const auto quality_report_period_sec =
      std::max<int64_t>(1, get_parameter("quality_report_period_sec").as_int());
    tx_timer_ = create_wall_timer(
      std::chrono::milliseconds(tx_period_ms_),
      std::bind(&RovMavlinkTestNode::tx_timer_callback, this));
    summary_timer_ = create_wall_timer(
      std::chrono::seconds(quality_report_period_sec),
      std::bind(&RovMavlinkTestNode::summary_timer_callback, this));
    last_summary_time_ = std::chrono::steady_clock::now();

    RCLCPP_INFO(
      get_logger(),
      "ROV MAVLink test node loaded %zu endpoints, %zu tx routes and %zu rx routes from %s",
      selected_endpoints_.size(),
      tx_routes_.size(),
      rx_subscriptions_.size(),
      config_file_.c_str());
    RCLCPP_INFO(
      get_logger(),
      "ROV MAVLink quality monitor enabled: period=%lds link_timeout=%ums tx_period=%ums",
      static_cast<long>(quality_report_period_sec),
      quality_link_timeout_ms_,
      tx_period_ms_);
    RCLCPP_INFO(
      get_logger(),
      "Quality summary topics: %s and legacy %s",
      test_topic("quality_summary").c_str(),
      test_topic("rx_summary").c_str());
    RCLCPP_INFO(
      get_logger(),
      "Run this node together with rov_mavlink_node; this test node observes ROS topics and does not open a MAVLink UDP socket itself");
    if (!include_heartbeat_tx_) {
      RCLCPP_INFO(
        get_logger(),
        "include_heartbeat_tx=false: bridge-owned heartbeat is not counted in test TX statistics");
    }
    if (tx_routes_.empty()) {
      RCLCPP_WARN(
        get_logger(),
        "No TX test routes were created; check endpoint messages.tx and include_heartbeat_tx");
    }
    if (safe_mode_) {
      RCLCPP_WARN(
        get_logger(),
        "safe_mode=true: command test payloads use non-actuating or low-risk values");
    }
  }

private:
  struct TxRoute
  {
    std::string endpoint;
    uint32_t msgid{0};
    std::string topic;
    std::function<void(uint64_t)> publish;
  };

  std::vector<TestEndpoint> load_endpoints(const std::string & path) const
  {
    const auto root = YAML::LoadFile(path);
    const auto bridge = root["sealien_mavlink_bridge"];
    if (!bridge) {
      throw std::runtime_error("missing root key: sealien_mavlink_bridge");
    }

    const auto endpoint_nodes = bridge["endpoints"];
    if (!endpoint_nodes || !endpoint_nodes.IsSequence()) {
      throw std::runtime_error("endpoints must be a sequence");
    }

    std::vector<TestEndpoint> endpoints;
    for (const auto & item : endpoint_nodes) {
      TestEndpoint endpoint;
      endpoint.name = item["name"].as<std::string>();
      endpoint.enabled = item["enabled"].as<bool>(true);
      endpoint.system_id = static_cast<uint32_t>(item["system_id"].as<int>(0));
      endpoint.component_id = static_cast<uint32_t>(item["component_id"].as<int>(0));
      endpoint.remote_ip = item["remote_ip"].as<std::string>("");
      endpoint.remote_port = static_cast<uint32_t>(item["remote_port"].as<int>(0));
      const auto messages = item["messages"];
      if (!messages) {
        throw std::runtime_error("endpoint " + endpoint.name + " missing messages");
      }
      endpoint.rx = read_msgids(messages["rx"]);
      endpoint.tx = read_msgids(messages["tx"]);
      endpoints.push_back(endpoint);
    }
    return endpoints;
  }

  bool endpoint_selected(const std::string & name) const
  {
    return target_endpoints_.empty() ||
           std::find(target_endpoints_.begin(), target_endpoints_.end(), name) !=
             target_endpoints_.end();
  }

  void build_routes(const std::vector<TestEndpoint> & endpoints)
  {
    std::size_t enabled_selected = 0;
    for (const auto & endpoint : endpoints) {
      if (!endpoint.enabled || !endpoint_selected(endpoint.name)) {
        continue;
      }
      ++enabled_selected;
      selected_endpoints_.push_back(endpoint);
      endpoint_quality_.emplace(endpoint.name, EndpointQuality{});

      for (const auto msgid : endpoint.tx) {
        if (msgid == 0U && !include_heartbeat_tx_) {
          continue;
        }
        create_tx_publisher(endpoint, msgid);
      }

      for (const auto msgid : endpoint.rx) {
        create_rx_probe(endpoint, msgid);
      }

      RCLCPP_INFO(
        get_logger(),
        "Test endpoint=%s peer=%s:%u sysid=%u compid=%u routes TX ROS->STM32=%s RX STM32->ROS=%s",
        endpoint.name.c_str(),
        endpoint.remote_ip.c_str(),
        endpoint.remote_port,
        endpoint.system_id,
        endpoint.component_id,
        msgid_set_to_string(endpoint.tx).c_str(),
        msgid_set_to_string(endpoint.rx).c_str());
    }

    if (enabled_selected != 3U) {
      RCLCPP_WARN(
        get_logger(),
        "selected %zu enabled endpoints; ROV three-board test normally expects 3",
        enabled_selected);
    }
  }

  std::string bridge_topic(const TestEndpoint & endpoint, uint32_t msgid, bool rx) const
  {
    const auto direction = rx ? "from_mcu" : "to_mcu";
    const auto suffix = direction + std::string("/") + endpoint.name + "/" + msgid_topic_name(msgid);
    return topic_prefix_.empty() ? suffix : topic_prefix_ + "/" + suffix;
  }

  std::string test_topic(const std::string & suffix) const
  {
    return topic_prefix_.empty() ? "test/" + suffix : topic_prefix_ + "/test/" + suffix;
  }

  std::string mirror_topic(const TestEndpoint & endpoint, uint32_t msgid) const
  {
    return test_topic("from_mcu/" + endpoint.name + "/" + msgid_topic_name(msgid));
  }

  static std::string stats_key(const std::string & endpoint, uint32_t msgid)
  {
    return endpoint + ":" + std::to_string(msgid);
  }

  static std::string msgid_set_to_string(const std::set<uint32_t> & ids)
  {
    std::ostringstream oss;
    bool first = true;
    for (const auto msgid : ids) {
      if (!first) {
        oss << ",";
      }
      first = false;
      oss << msgid;
    }
    return first ? "none" : oss.str();
  }

  static const char * state_label(const std::string & state)
  {
    if (state == "UP") {
      return "OK";
    }
    if (state == "DOWN") {
      return "LOST";
    }
    return "WAIT";
  }

  uint32_t now_ms() const
  {
    const auto ns = now().nanoseconds();
    return static_cast<uint32_t>(static_cast<uint64_t>(ns) / 1000000ULL);
  }

  void publish_event(
    const rclcpp::Publisher<std_msgs::msg::String>::SharedPtr & pub,
    const std::string & direction,
    const std::string & endpoint,
    uint32_t msgid,
    const std::string & topic,
    uint64_t count)
  {
    if (!pub) {
      return;
    }
    std_msgs::msg::String event;
    std::ostringstream oss;
    oss << direction << " endpoint=" << endpoint
        << " msgid=" << msgid
        << " name=" << msgid_name(msgid)
        << " count=" << count
        << " topic=" << topic;
    event.data = oss.str();
    pub->publish(event);
  }

  template<typename MessageT, typename FillT>
  void add_tx_route(const TestEndpoint & endpoint, uint32_t msgid, FillT fill)
  {
    const auto topic = bridge_topic(endpoint, msgid, false);
    auto pub = create_publisher<MessageT>(topic, 10);
    tx_publishers_.push_back(pub);
    tx_routes_.push_back(TxRoute{
      endpoint.name,
      msgid,
      topic,
      [this, pub, fill, endpoint_name = endpoint.name, msgid, topic](uint64_t seq) {
        MessageT msg;
        fill(msg, seq);
        pub->publish(msg);
        uint64_t count = 0;
        {
          std::lock_guard<std::mutex> lock(stats_mutex_);
          count = ++tx_counts_[stats_key(endpoint_name, msgid)];
        }
        publish_event(tx_event_pub_, "TX ROS->STM32", endpoint_name, msgid, topic, count);
      }});
  }

  template<typename MessageT>
  void add_rx_probe(const TestEndpoint & endpoint, uint32_t msgid)
  {
    const auto source_topic = bridge_topic(endpoint, msgid, true);
    const auto out_topic = mirror_topic(endpoint, msgid);
    auto mirror_pub = create_publisher<MessageT>(out_topic, 10);
    rx_mirror_publishers_.push_back(mirror_pub);

    auto sub = create_subscription<MessageT>(
      source_topic,
      10,
      [this, mirror_pub, endpoint_name = endpoint.name, msgid, out_topic](
        typename MessageT::SharedPtr msg) {
        mirror_pub->publish(*msg);
        uint64_t count = 0;
        {
          std::lock_guard<std::mutex> lock(stats_mutex_);
          count = ++rx_counts_[stats_key(endpoint_name, msgid)];
          auto & quality = endpoint_quality_[endpoint_name];
          quality.last_rx = std::chrono::steady_clock::now();
          quality.last_rx_msgid = msgid;
          if (!quality.linked) {
            quality.linked = true;
            ++quality.link_up_count;
            RCLCPP_INFO(
              get_logger(),
              "%sMAVLink test LINK UP endpoint=%s first_rx_msgid=%u%s",
              kLogGreen,
              endpoint_name.c_str(),
              msgid,
              kLogReset);
          }
        }
        publish_event(rx_event_pub_, "RX STM32->ROS", endpoint_name, msgid, out_topic, count);
      });
    rx_subscriptions_.push_back(sub);
  }

  void create_tx_publisher(const TestEndpoint & endpoint, uint32_t msgid)
  {
    switch (msgid) {
      case 0:
        add_tx_route<sealien_ctrlpilot_msgmanagement::msg::HeartbeatStatus>(
          endpoint, msgid, [this, endpoint_name = endpoint.name](
            auto & msg, uint64_t seq) {
            msg.header.stamp = now();
            msg.header.frame_id = endpoint_name;
            msg.timestamp_ms = now_ms();
            msg.type = 1;
            msg.system_status = static_cast<uint8_t>(seq % 4U);
            msg.mavlink_version = 2;
          });
        break;
      case 10:
        add_tx_route<sealien_ctrlpilot_msgmanagement::msg::ThrusterCmd>(
          endpoint, msgid, [](auto & msg, uint64_t) {
            msg.thru1 = 0;
            msg.thru2 = 0;
            msg.thru3 = 0;
            msg.thru4 = 0;
            msg.thru5 = 0;
            msg.thru6 = 0;
            msg.thru7 = 0;
            msg.thru8 = 0;
            msg.thru9 = 0;
            msg.thru10 = 0;
            msg.thru11 = 0;
            msg.thru12 = 0;
          });
        break;
      case 11:
        add_tx_route<sealien_ctrlpilot_msgmanagement::msg::ThrusterLock>(
          endpoint, msgid, [](auto & msg, uint64_t) {
            msg.lock = 1;
          });
        break;
      case 12:
        add_tx_route<sealien_ctrlpilot_msgmanagement::msg::ImuCalib>(
          endpoint, msgid, [this](auto & msg, uint64_t seq) {
            if (safe_mode_) {
              msg.lon = 0.0;
              msg.lat = 0.0;
              msg.alt = 0.0F;
            } else {
              msg.lon = 120.0 + static_cast<double>(seq % 100U) * 0.000001;
              msg.lat = 30.0 + static_cast<double>(seq % 100U) * 0.000001;
              msg.alt = 0.0F;
            }
          });
        break;
      case 13:
        add_tx_route<sealien_ctrlpilot_msgmanagement::msg::ImuClear>(
          endpoint, msgid, [this](auto & msg, uint64_t) {
            msg.clear = safe_mode_ ? 0 : 1;
          });
        break;
      case 14:
        add_tx_route<sealien_ctrlpilot_msgmanagement::msg::LedCmd>(
          endpoint, msgid, [this](auto & msg, uint64_t seq) {
            msg.index = static_cast<uint8_t>((seq % 10U) + 1U);
            msg.pwm = safe_mode_ ? 0 : static_cast<uint8_t>((seq * 10U) % 100U);
          });
        break;
      case 15:
        add_tx_route<sealien_ctrlpilot_msgmanagement::msg::GsCmd>(
          endpoint, msgid, [](auto & msg, uint64_t seq) {
            msg.index = static_cast<uint8_t>(seq % 2U);
            msg.angle_deg = 0.0F;
          });
        break;
      case 16:
        add_tx_route<sealien_ctrlpilot_msgmanagement::msg::GsCfg>(
          endpoint, msgid, [](auto & msg, uint64_t) {
            msg.max_angle_deg = {45.0F, 45.0F};
            msg.min_angle_deg = {-45.0F, -45.0F};
            msg.step = {1, 1};
          });
        break;
      case 17:
        add_tx_route<sealien_ctrlpilot_msgmanagement::msg::SwitchCmd>(
          endpoint, msgid, [](auto & msg, uint64_t seq) {
            msg.index = static_cast<uint8_t>((seq % 8U) + 1U);
            msg.value = 0;
          });
        break;
      case 19:
        add_tx_route<sealien_ctrlpilot_msgmanagement::msg::MixedIoCmd>(
          endpoint, msgid, [](auto & msg, uint64_t) {
            msg.gpio_1_32_output = 0;
            msg.gpio_33_64_output = 0;
            msg.dac_dev1_vout.fill(0.0F);
            msg.dac_dev2_vout.fill(0.0F);
            msg.dac_dev3_vout.fill(0.0F);
          });
        break;
      case 21:
        add_tx_route<sealien_ctrlpilot_msgmanagement::msg::ValveCmd>(
          endpoint, msgid, [this, endpoint_name = endpoint.name](auto & msg, uint64_t) {
            msg.header.stamp = now();
            msg.header.frame_id = endpoint_name;
            msg.timestamp_ms = now_ms();
            msg.sensor_power_mask = 0;
            msg.current_ma.fill(0);
            msg.freq_hz.fill(0);
          });
        break;
      default:
        RCLCPP_WARN(
          get_logger(),
          "No tx test payload mapping for endpoint=%s msgid=%u",
          endpoint.name.c_str(),
          msgid);
        break;
    }
  }

  void create_rx_probe(const TestEndpoint & endpoint, uint32_t msgid)
  {
    switch (msgid) {
      case 0:
        add_rx_probe<sealien_ctrlpilot_msgmanagement::msg::HeartbeatStatus>(endpoint, msgid);
        break;
      case 1:
        add_rx_probe<sealien_ctrlpilot_msgmanagement::msg::ImuNavStatus>(endpoint, msgid);
        break;
      case 2:
        add_rx_probe<sealien_ctrlpilot_msgmanagement::msg::ThrusterStatus>(endpoint, msgid);
        break;
      case 3:
        add_rx_probe<sealien_ctrlpilot_msgmanagement::msg::GsStatus>(endpoint, msgid);
        break;
      case 4:
        add_rx_probe<sealien_ctrlpilot_msgmanagement::msg::LedStatus>(endpoint, msgid);
        break;
      case 5:
        add_rx_probe<sealien_ctrlpilot_msgmanagement::msg::VcheckStatus>(endpoint, msgid);
        break;
      case 6:
        add_rx_probe<sealien_ctrlpilot_msgmanagement::msg::SonarAltimeterStatus>(endpoint, msgid);
        break;
      case 7:
        add_rx_probe<sealien_ctrlpilot_msgmanagement::msg::DepthStatus>(endpoint, msgid);
        break;
      case 8:
        add_rx_probe<sealien_ctrlpilot_msgmanagement::msg::Bme280Status>(endpoint, msgid);
        break;
      case 9:
        add_rx_probe<sealien_ctrlpilot_msgmanagement::msg::SwitchStatus>(endpoint, msgid);
        break;
      case 18:
        add_rx_probe<sealien_ctrlpilot_msgmanagement::msg::DvlData>(endpoint, msgid);
        break;
      case 20:
        add_rx_probe<sealien_ctrlpilot_msgmanagement::msg::MixedIoData>(endpoint, msgid);
        break;
      case 22:
        add_rx_probe<sealien_ctrlpilot_msgmanagement::msg::ValveStatus>(endpoint, msgid);
        break;
      default:
        RCLCPP_WARN(
          get_logger(),
          "No rx test mirror mapping for endpoint=%s msgid=%u",
          endpoint.name.c_str(),
          msgid);
        break;
    }
  }

  void tx_timer_callback()
  {
    ++tx_sequence_;
    for (const auto & route : tx_routes_) {
      route.publish(tx_sequence_);
    }
  }

  void summary_timer_callback()
  {
    const auto now = std::chrono::steady_clock::now();
    const auto elapsed = std::chrono::duration<double>(now - last_summary_time_).count();
    if (elapsed <= 0.0) {
      return;
    }

    std_msgs::msg::String summary;
    std::ostringstream oss;
    oss << std::fixed << std::setprecision(2);
    oss << "mavlink_quality window=" << elapsed << "s";
    {
      std::lock_guard<std::mutex> lock(stats_mutex_);
      update_link_states_locked(now);
      for (const auto & endpoint : selected_endpoints_) {
        const auto tx_summary =
          build_rate_summary_locked(endpoint, endpoint.tx, tx_counts_, last_tx_counts_, elapsed);
        const auto rx_summary =
          build_rate_summary_locked(endpoint, endpoint.rx, rx_counts_, last_rx_counts_, elapsed);
        auto & quality = endpoint_quality_[endpoint.name];
        const auto rx_age_ms = rx_age_ms_locked(quality, now);
        const auto state = link_state_locked(quality, now);

        oss << " endpoint=" << endpoint.name
            << " state=" << state
            << " rx_age_ms=" << rx_age_ms
            << " tx_ros_to_stm32=(total=" << tx_summary.total
            << " rate=" << tx_summary.rate_hz << "Hz msg=(" << tx_summary.messages << "))"
            << " rx_stm32_to_ros=(total=" << rx_summary.total
            << " rate=" << rx_summary.rate_hz << "Hz msg=(" << rx_summary.messages << "))";

        if (log_quality_report_) {
          const auto block = format_quality_report_block(
            endpoint,
            state,
            rx_age_ms,
            elapsed,
            quality,
            tx_summary,
            rx_summary);
          RCLCPP_INFO(get_logger(), "%s", block.c_str());
        }
      }
      last_tx_counts_ = tx_counts_;
      last_rx_counts_ = rx_counts_;
    }
    summary.data = oss.str();
    quality_summary_pub_->publish(summary);
    legacy_rx_summary_pub_->publish(summary);
    last_summary_time_ = now;
  }

  RateSummary build_rate_summary_locked(
    const TestEndpoint & endpoint,
    const std::set<uint32_t> & ids,
    const std::unordered_map<std::string, uint64_t> & counts,
    const std::unordered_map<std::string, uint64_t> & last_counts,
    double elapsed) const
  {
    RateSummary summary;
    std::ostringstream oss;
    bool first = true;
    oss << std::fixed << std::setprecision(2);
    for (const auto msgid : ids) {
      const auto key = stats_key(endpoint.name, msgid);
      const auto count_it = counts.find(key);
      const auto last_it = last_counts.find(key);
      const auto total = (count_it == counts.end()) ? 0ULL : count_it->second;
      const auto last = (last_it == last_counts.end()) ? 0ULL : last_it->second;
      const auto delta = total - last;
      const auto rate_hz = static_cast<double>(delta) / elapsed;
      summary.total += total;
      summary.delta += delta;
      if (!first) {
        oss << ", ";
      }
      first = false;
      oss << msgid << ":" << total << "@" << rate_hz << "Hz";
    }
    if (first) {
      oss << "none";
    }
    summary.rate_hz = static_cast<double>(summary.delta) / elapsed;
    summary.messages = oss.str();
    return summary;
  }

  std::string format_quality_report_block(
    const TestEndpoint & endpoint,
    const std::string & state,
    int64_t rx_age_ms,
    double elapsed,
    const EndpointQuality & quality,
    const RateSummary & tx_summary,
    const RateSummary & rx_summary) const
  {
    std::ostringstream oss;
    oss << std::fixed << std::setprecision(2);
    oss << "\n" << kLogCyan << kLogSeparator
        << " ROV MAVLink Test Quality " << kLogSeparator << kLogReset << "\n"
        << "endpoint=" << endpoint.name
        << " peer=" << endpoint.remote_ip << ":" << endpoint.remote_port
        << " sysid=" << endpoint.system_id
        << " compid=" << endpoint.component_id
        << " state=" << state << "(" << state_label(state) << ")"
        << " window=" << elapsed << "s"
        << " rx_age=" << rx_age_ms << "ms"
        << " last_rx_msgid=" << quality.last_rx_msgid
        << " link_up=" << quality.link_up_count
        << " link_down=" << quality.link_down_count << "\n"
        << kLogMagenta << "TX ROS->STM32" << kLogReset << "\n"
        << kLogMagenta << "total=" << tx_summary.total
        << " rate=" << tx_summary.rate_hz
        << "Hz msg=(" << tx_summary.messages << ")" << kLogReset << "\n"
        << kLogGreen << "RX STM32->ROS" << kLogReset << "\n"
        << kLogGreen << "total=" << rx_summary.total
        << " rate=" << rx_summary.rate_hz
        << "Hz msg=(" << rx_summary.messages << ")" << kLogReset;
    if (state == "WAIT") {
      oss << "\nhint=no RX topic data yet; check rov_mavlink_node, topic_prefix, YAML endpoint, and STM32 network";
    } else if (state == "DOWN") {
      oss << "\nhint=RX timeout; check STM32 power/network/IP and MAVLink sysid/compid";
    }
    if (!include_heartbeat_tx_) {
      oss << "\nnote=bridge heartbeat is not included in TX test counters";
    }
    return oss.str();
  }

  int64_t rx_age_ms_locked(
    const EndpointQuality & quality,
    std::chrono::steady_clock::time_point now) const
  {
    if (quality.last_rx.time_since_epoch().count() == 0) {
      return -1;
    }
    return std::chrono::duration_cast<std::chrono::milliseconds>(now - quality.last_rx).count();
  }

  std::string link_state_locked(
    const EndpointQuality & quality,
    std::chrono::steady_clock::time_point now) const
  {
    if (quality.last_rx.time_since_epoch().count() == 0) {
      return "WAIT";
    }
    const auto age_ms = rx_age_ms_locked(quality, now);
    return age_ms >= 0 && static_cast<uint32_t>(age_ms) <= quality_link_timeout_ms_ ? "UP" : "DOWN";
  }

  void update_link_states_locked(std::chrono::steady_clock::time_point now)
  {
    for (const auto & endpoint : selected_endpoints_) {
      auto & quality = endpoint_quality_[endpoint.name];
      const auto should_be_up = link_state_locked(quality, now) == "UP";
      if (quality.linked && !should_be_up) {
        quality.linked = false;
        ++quality.link_down_count;
        RCLCPP_WARN(
          get_logger(),
          "%sMAVLink test LINK DOWN endpoint=%s rx_age_ms=%lld%s",
          kLogYellow,
          endpoint.name.c_str(),
          static_cast<long long>(rx_age_ms_locked(quality, now)),
          kLogReset);
      }
    }
  }

  std::string config_file_;
  std::string topic_prefix_;
  std::vector<std::string> target_endpoints_;
  bool include_heartbeat_tx_{false};
  bool log_quality_report_{true};
  bool safe_mode_{true};
  uint32_t tx_period_ms_{1000};
  uint32_t quality_link_timeout_ms_{3000};
  uint64_t tx_sequence_{0};

  std::vector<TestEndpoint> selected_endpoints_;
  std::vector<rclcpp::PublisherBase::SharedPtr> tx_publishers_;
  std::vector<rclcpp::PublisherBase::SharedPtr> rx_mirror_publishers_;
  std::vector<rclcpp::SubscriptionBase::SharedPtr> rx_subscriptions_;
  std::vector<TxRoute> tx_routes_;

  std::mutex stats_mutex_;
  std::unordered_map<std::string, uint64_t> tx_counts_;
  std::unordered_map<std::string, uint64_t> rx_counts_;
  std::unordered_map<std::string, uint64_t> last_tx_counts_;
  std::unordered_map<std::string, uint64_t> last_rx_counts_;
  std::unordered_map<std::string, EndpointQuality> endpoint_quality_;
  std::chrono::steady_clock::time_point last_summary_time_{};

  rclcpp::Publisher<std_msgs::msg::String>::SharedPtr rx_event_pub_;
  rclcpp::Publisher<std_msgs::msg::String>::SharedPtr tx_event_pub_;
  rclcpp::Publisher<std_msgs::msg::String>::SharedPtr quality_summary_pub_;
  rclcpp::Publisher<std_msgs::msg::String>::SharedPtr legacy_rx_summary_pub_;
  rclcpp::TimerBase::SharedPtr tx_timer_;
  rclcpp::TimerBase::SharedPtr summary_timer_;
};

int main(int argc, char ** argv)
{
  rclcpp::init(argc, argv);
  const auto share_dir =
    ament_index_cpp::get_package_share_directory("sealien_ctrlpilot_mavlinkbridge");
  auto node = std::make_shared<RovMavlinkTestNode>(
    share_dir + "/config/sealien_mavlink_rov.yaml");
  rclcpp::spin(node);
  rclcpp::shutdown();
  return 0;
}
