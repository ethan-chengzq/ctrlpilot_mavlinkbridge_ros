#include <algorithm>
#include <chrono>
#include <cctype>
#include <cmath>
#include <cstdint>
#include <functional>
#include <iomanip>
#include <memory>
#include <mutex>
#include <numeric>
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

struct GapStats
{
  uint64_t samples{0};
  double sum_ms{0.0};
  double min_ms{0.0};
  double max_ms{0.0};
};

struct StreamQuality
{
  uint64_t total{0};
  uint64_t window_count{0};
  bool have_local{false};
  uint64_t last_local_ms{0};
  bool have_remote{false};
  uint32_t last_remote_ms{0};
  GapStats local_gap;
  GapStats remote_gap;
  GapStats jitter;
  uint64_t remote_out_of_order_total{0};
  uint64_t remote_out_of_order_window{0};
};

struct MessageRateSummary
{
  uint32_t msgid{0};
  uint64_t total{0};
  uint64_t delta{0};
  uint64_t expected{0};
  uint64_t missed{0};
  double rate_hz{0.0};
  double target_rate_hz{0.0};
  double loss_pct{0.0};
  StreamQuality quality;
};

struct RateSummary
{
  uint64_t total{0};
  uint64_t delta{0};
  uint64_t expected{0};
  uint64_t missed{0};
  double rate_hz{0.0};
  double target_rate_hz{0.0};
  double loss_pct{0.0};
  std::string messages{"none"};
  std::vector<MessageRateSummary> message_details;
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

std::string msgid_label(uint32_t msgid)
{
  std::ostringstream oss;
  oss << msgid_name(msgid) << "#" << std::setw(2) << std::setfill('0') << msgid;
  return oss.str();
}

std::string msgid_topic_name(uint32_t msgid)
{
  auto name = msgid_name(msgid);
  std::transform(name.begin(), name.end(), name.begin(), [](unsigned char c) {
    return static_cast<char>(std::tolower(c));
  });
  return name;
}

double stress_rate_hz(uint32_t msgid)
{
  switch (msgid) {
    case 0:
      return 1.0;
    case 1:
    case 10:
    case 18:
      return 50.0;
    default:
      return 10.0;
  }
}

uint64_t expected_frames(double rate_hz, double elapsed_sec)
{
  if (rate_hz <= 0.0 || elapsed_sec <= 0.0) {
    return 0;
  }
  return static_cast<uint64_t>(std::llround(rate_hz * elapsed_sec));
}

void add_gap_sample(GapStats & stats, double value_ms)
{
  if (stats.samples == 0) {
    stats.min_ms = value_ms;
    stats.max_ms = value_ms;
  } else {
    stats.min_ms = std::min(stats.min_ms, value_ms);
    stats.max_ms = std::max(stats.max_ms, value_ms);
  }
  stats.sum_ms += value_ms;
  ++stats.samples;
}

std::string gap_stats_to_string(const GapStats & stats)
{
  if (stats.samples == 0) {
    return "avg/min/max=n/a";
  }

  std::ostringstream oss;
  oss << std::fixed << std::setprecision(2)
      << "avg/min/max=" << (stats.sum_ms / static_cast<double>(stats.samples))
      << "/" << std::llround(stats.min_ms)
      << "/" << std::llround(stats.max_ms) << "ms";
  return oss.str();
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
    declare_parameter<int>("tx_scheduler_period_ms", 5);
    declare_parameter<int>("tx_route_stagger_ms", 5);
    declare_parameter<int>("quality_report_period_sec", 60);
    declare_parameter<int>("brief_report_period_sec", 5);
    declare_parameter<int>("detail_report_period_sec", get_parameter("quality_report_period_sec").as_int());
    declare_parameter<int>("quality_link_timeout_ms", 3000);
    declare_parameter<bool>("use_stress_rates", true);
    declare_parameter<bool>("include_heartbeat_tx", false);
    declare_parameter<bool>("log_quality_report", true);
    declare_parameter<bool>("publish_per_message_events", false);
    declare_parameter<bool>("publish_rx_mirror_topics", false);
    declare_parameter<bool>("safe_mode", true);

    config_file_ = get_parameter("config_file").as_string();
    topic_prefix_ = trim_slashes(get_parameter("topic_prefix").as_string());
    target_endpoints_ = get_parameter("target_endpoints").as_string_array();
    use_stress_rates_ = get_parameter("use_stress_rates").as_bool();
    include_heartbeat_tx_ = get_parameter("include_heartbeat_tx").as_bool();
    log_quality_report_ = get_parameter("log_quality_report").as_bool();
    publish_per_message_events_ = get_parameter("publish_per_message_events").as_bool();
    publish_rx_mirror_topics_ = get_parameter("publish_rx_mirror_topics").as_bool();
    tx_route_stagger_ms_ =
      static_cast<uint32_t>(std::max<int64_t>(0, get_parameter("tx_route_stagger_ms").as_int()));
    quality_link_timeout_ms_ =
      static_cast<uint32_t>(std::max<int64_t>(100, get_parameter("quality_link_timeout_ms").as_int()));
    safe_mode_ = get_parameter("safe_mode").as_bool();

    rx_event_pub_ = create_publisher<std_msgs::msg::String>(test_topic("rx_events"), 100);
    tx_event_pub_ = create_publisher<std_msgs::msg::String>(test_topic("tx_events"), 100);
    quality_summary_pub_ = create_publisher<std_msgs::msg::String>(test_topic("quality_summary"), 10);
    quality_report_pub_ = create_publisher<std_msgs::msg::String>(test_topic("quality_report"), 10);
    legacy_rx_summary_pub_ = create_publisher<std_msgs::msg::String>(test_topic("rx_summary"), 10);

    const auto endpoints = load_endpoints(config_file_);
    build_routes(endpoints);

    tx_period_ms_ = static_cast<uint32_t>(
      std::max<int64_t>(1, get_parameter("tx_period_ms").as_int()));
    tx_scheduler_period_ms_ = static_cast<uint32_t>(
      std::max<int64_t>(1, get_parameter("tx_scheduler_period_ms").as_int()));
    const auto brief_report_period_sec =
      std::max<int64_t>(1, get_parameter("brief_report_period_sec").as_int());
    const auto detail_report_period_sec =
      std::max<int64_t>(brief_report_period_sec, get_parameter("detail_report_period_sec").as_int());
    tx_timer_ = create_wall_timer(
      std::chrono::milliseconds(use_stress_rates_ ? tx_scheduler_period_ms_ : tx_period_ms_),
      std::bind(&RovMavlinkTestNode::tx_timer_callback, this));
    brief_timer_ = create_wall_timer(
      std::chrono::seconds(brief_report_period_sec),
      std::bind(&RovMavlinkTestNode::brief_timer_callback, this));
    detail_timer_ = create_wall_timer(
      std::chrono::seconds(detail_report_period_sec),
      std::bind(&RovMavlinkTestNode::detail_timer_callback, this));
    last_brief_time_ = std::chrono::steady_clock::now();
    last_detail_time_ = last_brief_time_;

    RCLCPP_INFO(
      get_logger(),
      "ROV MAVLink test node loaded %zu endpoints, %zu tx routes and %zu rx routes from %s",
      selected_endpoints_.size(),
      tx_routes_.size(),
      rx_subscriptions_.size(),
      config_file_.c_str());
    RCLCPP_INFO(
      get_logger(),
      "ROV MAVLink quality monitor enabled: brief=%lds detail=%lds link_timeout=%ums stress_rates=%s scheduler=%ums route_stagger=%ums legacy_tx_period=%ums",
      static_cast<long>(brief_report_period_sec),
      static_cast<long>(detail_report_period_sec),
      quality_link_timeout_ms_,
      use_stress_rates_ ? "true" : "false",
      tx_scheduler_period_ms_,
      tx_route_stagger_ms_,
      tx_period_ms_);
    RCLCPP_INFO(
      get_logger(),
      "Stress frequency map: HEARTBEAT=1Hz, IMU_DATA/DVL_DATA/THRUSTER_CMD=50Hz, other status/cmd=10Hz");
    RCLCPP_INFO(
      get_logger(),
      "Quality topics: brief %s, detail %s and legacy brief %s",
      test_topic("quality_summary").c_str(),
      test_topic("quality_report").c_str(),
      test_topic("rx_summary").c_str());
    RCLCPP_INFO(
      get_logger(),
      "Run this node together with rov_mavlink_node; this test node observes ROS topics and does not open a MAVLink UDP socket itself");
    if (!include_heartbeat_tx_) {
      RCLCPP_INFO(
        get_logger(),
        "include_heartbeat_tx=false: bridge-owned heartbeat is not counted in test TX statistics");
    }
    if (!publish_per_message_events_) {
      RCLCPP_INFO(
        get_logger(),
        "publish_per_message_events=false: per-frame String events are suppressed during stress testing");
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
    double target_rate_hz{0.0};
    std::chrono::steady_clock::time_point next_due{};
    std::function<void(uint64_t)> publish;
  };

  struct TxPhaseSlot
  {
    uint32_t period_ms{0};
    uint32_t offset_ms{0};
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

  static std::string repeat_char(char value, std::size_t count)
  {
    return std::string(count, value);
  }

  static std::string banner_line(const std::string & title, char fill = '*')
  {
    constexpr std::size_t width = 132U;
    const std::string text = " " + title + " ";
    if (text.size() >= width) {
      return text;
    }
    const auto left = (width - text.size()) / 2U;
    const auto right = width - text.size() - left;
    return repeat_char(fill, left) + text + repeat_char(fill, right);
  }

  static std::string window_text(uint64_t actual, uint64_t expected)
  {
    return std::to_string(actual) + "/" + std::to_string(expected);
  }

  static std::string seconds_text(double seconds)
  {
    std::ostringstream oss;
    oss << std::fixed << std::setprecision(2) << seconds << "s";
    return oss.str();
  }

  static std::string endpoint_peer_text(const TestEndpoint & endpoint)
  {
    std::ostringstream oss;
    oss << endpoint.name << "(" << endpoint.remote_ip << ":" << endpoint.remote_port << ")";
    return oss.str();
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

  static uint64_t steady_now_ms()
  {
    const auto now = std::chrono::steady_clock::now().time_since_epoch();
    return static_cast<uint64_t>(
      std::chrono::duration_cast<std::chrono::milliseconds>(now).count());
  }

  std::chrono::steady_clock::duration next_tx_route_phase(
    const std::string & endpoint,
    double target_rate_hz)
  {
    if (tx_route_stagger_ms_ == 0U || target_rate_hz <= 0.0) {
      return std::chrono::steady_clock::duration::zero();
    }

    const auto period_ms =
      std::max<uint32_t>(1U, static_cast<uint32_t>(std::llround(1000.0 / target_rate_hz)));
    auto & slots = tx_phase_slots_[endpoint];

    auto phases_collide = [](const TxPhaseSlot & slot, uint32_t period, uint32_t offset) {
      const auto common_period = std::gcd(slot.period_ms, period);
      return common_period != 0U &&
             (slot.offset_ms % common_period) == (offset % common_period);
    };
    auto is_free = [&](uint32_t offset) {
      return std::none_of(slots.begin(), slots.end(), [&](const auto & slot) {
        return phases_collide(slot, period_ms, offset);
      });
    };

    std::vector<uint32_t> candidates;
    auto add_candidate = [&](uint32_t offset) {
      offset %= period_ms;
      if (std::find(candidates.begin(), candidates.end(), offset) == candidates.end()) {
        candidates.push_back(offset);
      }
    };

    // Prefer midpoint slots between existing faster routes. EP102 has one 50 Hz
    // command stream and several 10 Hz streams; same-tick UDP bursts can be
    // dropped by the embedded receive path, so exact phase collisions are avoided.
    for (const auto & slot : slots) {
      if (slot.period_ms > 0U && period_ms > slot.period_ms &&
        (period_ms % slot.period_ms) == 0U)
      {
        const auto half_period = std::max<uint32_t>(1U, slot.period_ms / 2U);
        for (uint32_t offset = 0U; offset < period_ms; offset += slot.period_ms) {
          add_candidate(slot.offset_ms + half_period + offset);
        }
      }
    }

    const auto step_ms = std::max<uint32_t>(1U, tx_scheduler_period_ms_);
    const auto stagger_start =
      static_cast<uint32_t>(((slots.size() + 1ULL) * tx_route_stagger_ms_) % period_ms);
    for (uint32_t offset = 0U; offset < period_ms; offset += step_ms) {
      add_candidate(stagger_start + offset);
    }
    for (uint32_t offset = 0U; offset < period_ms; offset += step_ms) {
      add_candidate(offset);
    }

    uint32_t offset_ms = stagger_start;
    for (const auto candidate : candidates) {
      if (is_free(candidate)) {
        offset_ms = candidate;
        break;
      }
    }
    slots.push_back(TxPhaseSlot{period_ms, offset_ms});

    return std::chrono::duration_cast<std::chrono::steady_clock::duration>(
      std::chrono::milliseconds(offset_ms));
  }

  void record_stream_sample_locked(
    std::unordered_map<std::string, StreamQuality> & streams,
    const std::string & endpoint,
    uint32_t msgid,
    uint64_t local_ms,
    bool has_remote_timestamp,
    uint32_t remote_timestamp_ms)
  {
    auto & stream = streams[stats_key(endpoint, msgid)];
    double local_gap_ms = 0.0;
    bool have_local_gap = false;
    double remote_gap_ms = 0.0;
    bool have_remote_gap = false;

    ++stream.total;
    ++stream.window_count;

    if (stream.have_local && local_ms > stream.last_local_ms) {
      local_gap_ms = static_cast<double>(local_ms - stream.last_local_ms);
      add_gap_sample(stream.local_gap, local_gap_ms);
      have_local_gap = true;
    }
    stream.last_local_ms = local_ms;
    stream.have_local = true;

    if (has_remote_timestamp) {
      if (stream.have_remote) {
        if (remote_timestamp_ms < stream.last_remote_ms) {
          ++stream.remote_out_of_order_total;
          ++stream.remote_out_of_order_window;
        } else if (remote_timestamp_ms > stream.last_remote_ms) {
          remote_gap_ms = static_cast<double>(remote_timestamp_ms - stream.last_remote_ms);
          add_gap_sample(stream.remote_gap, remote_gap_ms);
          have_remote_gap = true;
        }
      }
      stream.last_remote_ms = remote_timestamp_ms;
      stream.have_remote = true;
    }

    if (have_local_gap && have_remote_gap) {
      add_gap_sample(stream.jitter, std::fabs(local_gap_ms - remote_gap_ms));
    }
  }

  void reset_stream_windows_locked(
    std::unordered_map<std::string, StreamQuality> & tx_streams,
    std::unordered_map<std::string, StreamQuality> & rx_streams)
  {
    auto reset_one = [](auto & streams) {
      for (auto & item : streams) {
        item.second.window_count = 0;
        item.second.have_local = false;
        item.second.last_local_ms = 0;
        item.second.have_remote = false;
        item.second.last_remote_ms = 0;
        item.second.local_gap = GapStats{};
        item.second.remote_gap = GapStats{};
        item.second.jitter = GapStats{};
        item.second.remote_out_of_order_window = 0;
      }
    };

    reset_one(tx_streams);
    reset_one(rx_streams);
  }

  void publish_event(
    const rclcpp::Publisher<std_msgs::msg::String>::SharedPtr & pub,
    const std::string & direction,
    const std::string & endpoint,
    uint32_t msgid,
    const std::string & topic,
    uint64_t count)
  {
    if (!publish_per_message_events_ || !pub) {
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
    const auto target_rate_hz = stress_rate_hz(msgid);
    const auto first_due =
      std::chrono::steady_clock::now() + next_tx_route_phase(endpoint.name, target_rate_hz);
    auto pub = create_publisher<MessageT>(topic, 100);
    tx_publishers_.push_back(pub);
    tx_routes_.push_back(TxRoute{
      endpoint.name,
      msgid,
      topic,
      target_rate_hz,
      first_due,
      [this, pub, fill, endpoint_name = endpoint.name, msgid, topic](uint64_t seq) {
        MessageT msg;
        fill(msg, seq);
        pub->publish(msg);
        uint64_t count = 0;
        {
          std::lock_guard<std::mutex> lock(stats_mutex_);
          const auto sample_ms = steady_now_ms();
          count = ++tx_counts_[stats_key(endpoint_name, msgid)];
          record_stream_sample_locked(
            tx_stream_quality_, endpoint_name, msgid, sample_ms, false, 0U);
          record_stream_sample_locked(
            brief_tx_stream_quality_, endpoint_name, msgid, sample_ms, false, 0U);
        }
        publish_event(tx_event_pub_, "TX ROS->STM32", endpoint_name, msgid, topic, count);
      }});
  }

  template<typename MessageT>
  void add_rx_probe(const TestEndpoint & endpoint, uint32_t msgid)
  {
    const auto source_topic = bridge_topic(endpoint, msgid, true);
    const auto out_topic = mirror_topic(endpoint, msgid);
    std::shared_ptr<rclcpp::Publisher<MessageT>> mirror_pub;
    if (publish_rx_mirror_topics_) {
      mirror_pub = create_publisher<MessageT>(out_topic, 100);
      rx_mirror_publishers_.push_back(mirror_pub);
    }

    auto sub = create_subscription<MessageT>(
      source_topic,
      100,
      [this, mirror_pub, endpoint_name = endpoint.name, msgid, out_topic](
        typename MessageT::SharedPtr msg) {
        if (mirror_pub) {
          mirror_pub->publish(*msg);
        }
        uint64_t count = 0;
        {
          std::lock_guard<std::mutex> lock(stats_mutex_);
          const auto sample_ms = steady_now_ms();
          count = ++rx_counts_[stats_key(endpoint_name, msgid)];
          record_stream_sample_locked(
            rx_stream_quality_,
            endpoint_name,
            msgid,
            sample_ms,
            true,
            static_cast<uint32_t>(msg->timestamp_ms));
          record_stream_sample_locked(
            brief_rx_stream_quality_,
            endpoint_name,
            msgid,
            sample_ms,
            true,
            static_cast<uint32_t>(msg->timestamp_ms));
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
    const auto now = std::chrono::steady_clock::now();
    for (auto & route : tx_routes_) {
      if (!use_stress_rates_) {
        route.publish(++tx_sequence_);
        continue;
      }

      if (route.target_rate_hz <= 0.0) {
        continue;
      }
      if (route.next_due.time_since_epoch().count() == 0) {
        route.next_due = now;
      }
      if (now < route.next_due) {
        continue;
      }

      route.publish(++tx_sequence_);
      const auto period =
        std::chrono::duration_cast<std::chrono::steady_clock::duration>(
          std::chrono::duration<double>(1.0 / route.target_rate_hz));
      if (period <= std::chrono::steady_clock::duration::zero()) {
        route.next_due = now;
        continue;
      }
      do {
        route.next_due += period;
      } while (route.next_due <= now);
    }
  }

  void brief_timer_callback()
  {
    const auto now = std::chrono::steady_clock::now();
    const auto elapsed = std::chrono::duration<double>(now - last_brief_time_).count();
    if (elapsed <= 0.0) {
      return;
    }
    if (skip_next_brief_report_) {
      std::lock_guard<std::mutex> lock(stats_mutex_);
      last_brief_tx_counts_ = tx_counts_;
      last_brief_rx_counts_ = rx_counts_;
      reset_stream_windows_locked(brief_tx_stream_quality_, brief_rx_stream_quality_);
      last_brief_time_ = now;
      skip_next_brief_report_ = false;
      return;
    }

    std_msgs::msg::String summary;
    std::ostringstream oss;
    oss << std::fixed << std::setprecision(2);
    oss << "mavlink_quality_brief window=" << elapsed << "s";
    {
      std::lock_guard<std::mutex> lock(stats_mutex_);
      update_link_states_locked(now);
      std::ostringstream log_oss;
      std::size_t online_count = 0U;
      if (log_quality_report_) {
        log_oss << "\n" << kLogCyan
                << banner_line("ROV MAVLink COMM BRIEF (win=" + seconds_text(elapsed) + ")")
                << kLogReset << "\n"
                << format_link_status_block_locked(now) << "\n>>>\n";
      }
      for (const auto & endpoint : selected_endpoints_) {
        auto & quality = endpoint_quality_[endpoint.name];
        const auto rx_age_ms = rx_age_ms_locked(quality, now);
        const auto state = link_state_locked(quality, now);
        if (state != "UP") {
          continue;
        }

        const auto tx_summary =
          build_rate_summary_locked(
            endpoint,
            endpoint.tx,
            tx_counts_,
            last_brief_tx_counts_,
            brief_tx_stream_quality_,
            elapsed,
            false,
            true);
        const auto rx_summary =
          build_rate_summary_locked(
            endpoint,
            endpoint.rx,
            rx_counts_,
            last_brief_rx_counts_,
            brief_rx_stream_quality_,
            elapsed,
            true,
            true);
        ++online_count;

        oss << " endpoint=" << endpoint.name
            << " state=" << state
            << " rx_age_ms=" << rx_age_ms
            << " tx_ros_to_stm32=(total=" << tx_summary.total
            << " rate=" << tx_summary.rate_hz
            << "Hz missed=" << tx_summary.missed
            << " loss=" << tx_summary.loss_pct << "% msg=(" << tx_summary.messages << "))"
            << " rx_stm32_to_ros=(total=" << rx_summary.total
            << " rate=" << rx_summary.rate_hz
            << "Hz missed=" << rx_summary.missed
            << " loss=" << rx_summary.loss_pct << "% msg=(" << rx_summary.messages << "))";

        if (log_quality_report_) {
          log_oss << format_quality_brief_block(
            endpoint,
            state,
            rx_age_ms,
            elapsed,
            quality,
            tx_summary,
            rx_summary);
          log_oss << repeat_char('-', 132U) << "\n";
        }
      }
      if (log_quality_report_) {
        if (online_count == 0U) {
          log_oss << "[endpoint] no online STM32 endpoint in this window\n";
        }
        log_oss << "<<<";
        RCLCPP_INFO(get_logger(), "%s", log_oss.str().c_str());
      }
      last_brief_tx_counts_ = tx_counts_;
      last_brief_rx_counts_ = rx_counts_;
      reset_stream_windows_locked(brief_tx_stream_quality_, brief_rx_stream_quality_);
    }
    summary.data = oss.str();
    quality_summary_pub_->publish(summary);
    legacy_rx_summary_pub_->publish(summary);
    last_brief_time_ = now;
  }

  void detail_timer_callback()
  {
    const auto now = std::chrono::steady_clock::now();
    const auto elapsed = std::chrono::duration<double>(now - last_detail_time_).count();
    if (elapsed <= 0.0) {
      return;
    }

    std_msgs::msg::String report;
    std::ostringstream oss;
    oss << std::fixed << std::setprecision(2);
    oss << "mavlink_quality_detail window=" << elapsed << "s";
    {
      std::lock_guard<std::mutex> lock(stats_mutex_);
      update_link_states_locked(now);
      std::ostringstream log_oss;
      std::size_t online_count = 0U;
      if (log_quality_report_) {
        log_oss << "\n" << kLogCyan
                << banner_line("ROV MAVLink Test Quality (win=" + seconds_text(elapsed) + ")")
                << kLogReset << "\n"
                << format_link_status_block_locked(now) << "\n>>>\n";
      }
      for (const auto & endpoint : selected_endpoints_) {
        auto & quality = endpoint_quality_[endpoint.name];
        const auto rx_age_ms = rx_age_ms_locked(quality, now);
        const auto state = link_state_locked(quality, now);
        if (state != "UP") {
          continue;
        }

        const auto tx_summary =
          build_rate_summary_locked(
            endpoint,
            endpoint.tx,
            tx_counts_,
            last_tx_counts_,
            tx_stream_quality_,
            elapsed,
            false,
            true);
        const auto rx_summary =
          build_rate_summary_locked(
            endpoint,
            endpoint.rx,
            rx_counts_,
            last_rx_counts_,
            rx_stream_quality_,
            elapsed,
            true,
            true);
        ++online_count;

        oss << " endpoint=" << endpoint.name
            << " state=" << state
            << " rx_age_ms=" << rx_age_ms
            << " tx_ros_to_stm32=(total=" << tx_summary.total
            << " rate=" << tx_summary.rate_hz
            << "Hz missed=" << tx_summary.missed
            << " loss=" << tx_summary.loss_pct << "% msg=(" << tx_summary.messages << "))"
            << " rx_stm32_to_ros=(total=" << rx_summary.total
            << " rate=" << rx_summary.rate_hz
            << "Hz missed=" << rx_summary.missed
            << " loss=" << rx_summary.loss_pct << "% msg=(" << rx_summary.messages << "))";

        if (log_quality_report_) {
          log_oss << format_quality_detail_block(
            endpoint,
            state,
            rx_age_ms,
            elapsed,
            quality,
            tx_summary,
            rx_summary);
          log_oss << repeat_char('-', 132U) << "\n";
        }
      }
      if (log_quality_report_) {
        if (online_count == 0U) {
          log_oss << "[endpoint] no online STM32 endpoint in this window\n";
        }
        log_oss << "<<<";
        RCLCPP_INFO(get_logger(), "%s", log_oss.str().c_str());
      }
      last_tx_counts_ = tx_counts_;
      last_rx_counts_ = rx_counts_;
      reset_stream_windows_locked(tx_stream_quality_, rx_stream_quality_);
      skip_next_brief_report_ = true;
    }
    report.data = oss.str();
    quality_report_pub_->publish(report);
    last_detail_time_ = now;
  }

  RateSummary build_rate_summary_locked(
    const TestEndpoint & endpoint,
    const std::set<uint32_t> & ids,
    const std::unordered_map<std::string, uint64_t> & counts,
    const std::unordered_map<std::string, uint64_t> & last_counts,
    const std::unordered_map<std::string, StreamQuality> & stream_quality,
    double elapsed,
    bool rx_direction,
    bool include_gap_detail) const
  {
    RateSummary summary;
    std::ostringstream oss;
    bool first = true;
    oss << std::fixed << std::setprecision(2);
    for (const auto msgid : ids) {
      if (!rx_direction && msgid == 0U && !include_heartbeat_tx_) {
        continue;
      }
      const auto key = stats_key(endpoint.name, msgid);
      const auto count_it = counts.find(key);
      const auto last_it = last_counts.find(key);
      const auto quality_it = stream_quality.find(key);
      const auto total = (count_it == counts.end()) ? 0ULL : count_it->second;
      const auto last = (last_it == last_counts.end()) ? 0ULL : last_it->second;
      const auto delta = total - last;
      const auto rate_hz = static_cast<double>(delta) / elapsed;
      const auto target_rate_hz = stress_rate_hz(msgid);
      const auto expected = expected_frames(target_rate_hz, elapsed);
      const auto missed = expected > delta ? expected - delta : 0ULL;
      const auto loss_pct =
        expected == 0ULL ? 0.0 :
        (static_cast<double>(missed) * 100.0 / static_cast<double>(expected));
      const auto quality =
        (quality_it == stream_quality.end()) ? StreamQuality{} : quality_it->second;
      summary.message_details.push_back(MessageRateSummary{
        msgid,
        total,
        delta,
        expected,
        missed,
        rate_hz,
        target_rate_hz,
        loss_pct,
        quality});
      summary.total += total;
      summary.delta += delta;
      summary.expected += expected;
      summary.missed += missed;
      summary.target_rate_hz += target_rate_hz;
      if (!first) {
        oss << ", ";
      }
      first = false;
      oss << "- " << msgid_label(msgid)
          << " total=" << total
          << " win=" << delta << "/" << expected
          << " rate=" << rate_hz << "/" << target_rate_hz << "Hz"
          << " missed=" << missed
          << " loss=" << loss_pct << "%";
      if (include_gap_detail) {
        oss << " gap " << gap_stats_to_string(quality.local_gap);
      }
    }
    if (first) {
      oss << "none";
    }
    summary.rate_hz = static_cast<double>(summary.delta) / elapsed;
    summary.loss_pct =
      summary.expected == 0ULL ? 0.0 :
      (static_cast<double>(summary.missed) * 100.0 / static_cast<double>(summary.expected));
    summary.messages = oss.str();
    return summary;
  }

  bool endpoint_online_locked(
    const TestEndpoint & endpoint,
    std::chrono::steady_clock::time_point now) const
  {
    const auto it = endpoint_quality_.find(endpoint.name);
    if (it == endpoint_quality_.end()) {
      return false;
    }
    return link_state_locked(it->second, now) == "UP";
  }

  std::string format_link_status_block_locked(std::chrono::steady_clock::time_point now) const
  {
    std::vector<std::string> online;

    for (const auto & endpoint : selected_endpoints_) {
      const auto peer = endpoint_peer_text(endpoint);
      if (endpoint_online_locked(endpoint, now)) {
        online.push_back(peer);
      }
    }

    auto join = [](const std::vector<std::string> & values) {
      std::ostringstream oss;
      for (std::size_t i = 0U; i < values.size(); ++i) {
        if (i > 0U) {
          oss << ", ";
        }
        oss << values[i];
      }
      return values.empty() ? std::string("none") : oss.str();
    };

    std::ostringstream oss;
    oss << "[LinkStatus] online(" << online.size() << "/" << selected_endpoints_.size()
        << "): " << join(online);
    return oss.str();
  }

  static std::string stream_summary_line(const RateSummary & summary, double elapsed)
  {
    (void)elapsed;
    std::ostringstream oss;
    oss << std::fixed << std::setprecision(2)
        << "total=" << std::setw(8) << summary.total
        << " window=" << std::setw(9) << window_text(summary.delta, summary.expected)
        << " rate=" << std::setw(7) << summary.rate_hz
        << "/" << std::setw(6) << summary.target_rate_hz << "Hz"
        << " missed=" << std::setw(6) << summary.missed
        << " loss=" << std::setw(6) << summary.loss_pct << "%";
    return oss.str();
  }

  static std::string message_summary_line(const MessageRateSummary & msg)
  {
    std::ostringstream oss;
    oss << std::fixed << std::setprecision(2)
        << std::left << std::setw(20) << msgid_label(msg.msgid)
        << std::right
        << " total=" << std::setw(8) << msg.total
        << " win=" << std::setw(9) << window_text(msg.delta, msg.expected)
        << " rate=" << std::setw(7) << msg.rate_hz
        << "/" << std::setw(6) << msg.target_rate_hz << "Hz"
        << " missed=" << std::setw(6) << msg.missed
        << " loss=" << std::setw(6) << msg.loss_pct << "%";
    return oss.str();
  }

  static std::string gap_line(const GapStats & stats)
  {
    std::ostringstream oss;
    oss << "gap " << gap_stats_to_string(stats);
    return oss.str();
  }

  std::string format_stream_block(
    const TestEndpoint & endpoint,
    const std::string & direction,
    const RateSummary & summary,
    double elapsed,
    bool detail) const
  {
    std::ostringstream oss;
    const auto is_tx = direction.find("TX ") == 0U;
    oss << (is_tx ? kLogMagenta : kLogGreen)
        << "EP" << endpoint.system_id << " " << direction << ": "
        << kLogReset << stream_summary_line(summary, elapsed) << "\n";
    if (summary.message_details.empty()) {
      oss << "      - none\n";
      return oss.str();
    }

    for (std::size_t i = 0U; i < summary.message_details.size(); ++i) {
      const auto & msg = summary.message_details[i];
      oss << "      - " << message_summary_line(msg);
      if (detail) {
        oss << " " << gap_line(msg.quality.local_gap);
      }
      oss << "\n";
    }
    return oss.str();
  }

  std::string format_quality_brief_block(
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
    oss << "[endpoint] " << endpoint.name
        << ": peer=" << endpoint.remote_ip << ":" << endpoint.remote_port
        << " sysid=" << endpoint.system_id
        << " compid=" << endpoint.component_id
        << " state=" << state << "(" << state_label(state) << ")"
        << " window=" << elapsed << "s"
        << " rx_age=" << rx_age_ms << "ms"
        << " last_rx_msgid=" << quality.last_rx_msgid
        << " link_up/down=" << quality.link_up_count << "/" << quality.link_down_count << "\n"
        << format_stream_block(endpoint, "TX ROS->STM32", tx_summary, elapsed, true)
        << format_stream_block(endpoint, "RX STM32->ROS", rx_summary, elapsed, true);
    return oss.str();
  }

  std::string format_quality_detail_block(
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
    oss << "[endpoint] " << endpoint.name
        << ": peer=" << endpoint.remote_ip << ":" << endpoint.remote_port
        << " sysid=" << endpoint.system_id
        << " compid=" << endpoint.component_id
        << " state=" << state << "(" << state_label(state) << ")"
        << " rx_age=" << rx_age_ms << "ms"
        << " last_rx_msgid=" << quality.last_rx_msgid
        << " link_up/down=" << quality.link_up_count << "/" << quality.link_down_count << "\n"
        << format_stream_block(endpoint, "TX ROS->STM32", tx_summary, elapsed, true)
        << format_stream_block(endpoint, "RX STM32->ROS", rx_summary, elapsed, true);
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
  bool use_stress_rates_{true};
  bool include_heartbeat_tx_{false};
  bool log_quality_report_{true};
  bool publish_per_message_events_{false};
  bool publish_rx_mirror_topics_{false};
  bool skip_next_brief_report_{false};
  bool safe_mode_{true};
  uint32_t tx_period_ms_{1000};
  uint32_t tx_scheduler_period_ms_{5};
  uint32_t tx_route_stagger_ms_{5};
  uint32_t quality_link_timeout_ms_{3000};
  uint64_t tx_sequence_{0};

  std::vector<TestEndpoint> selected_endpoints_;
  std::vector<rclcpp::PublisherBase::SharedPtr> tx_publishers_;
  std::vector<rclcpp::PublisherBase::SharedPtr> rx_mirror_publishers_;
  std::vector<rclcpp::SubscriptionBase::SharedPtr> rx_subscriptions_;
  std::vector<TxRoute> tx_routes_;
  std::unordered_map<std::string, std::vector<TxPhaseSlot>> tx_phase_slots_;

  std::mutex stats_mutex_;
  std::unordered_map<std::string, uint64_t> tx_counts_;
  std::unordered_map<std::string, uint64_t> rx_counts_;
  std::unordered_map<std::string, uint64_t> last_brief_tx_counts_;
  std::unordered_map<std::string, uint64_t> last_brief_rx_counts_;
  std::unordered_map<std::string, uint64_t> last_tx_counts_;
  std::unordered_map<std::string, uint64_t> last_rx_counts_;
  std::unordered_map<std::string, StreamQuality> brief_tx_stream_quality_;
  std::unordered_map<std::string, StreamQuality> brief_rx_stream_quality_;
  std::unordered_map<std::string, StreamQuality> tx_stream_quality_;
  std::unordered_map<std::string, StreamQuality> rx_stream_quality_;
  std::unordered_map<std::string, EndpointQuality> endpoint_quality_;
  std::chrono::steady_clock::time_point last_brief_time_{};
  std::chrono::steady_clock::time_point last_detail_time_{};

  rclcpp::Publisher<std_msgs::msg::String>::SharedPtr rx_event_pub_;
  rclcpp::Publisher<std_msgs::msg::String>::SharedPtr tx_event_pub_;
  rclcpp::Publisher<std_msgs::msg::String>::SharedPtr quality_summary_pub_;
  rclcpp::Publisher<std_msgs::msg::String>::SharedPtr quality_report_pub_;
  rclcpp::Publisher<std_msgs::msg::String>::SharedPtr legacy_rx_summary_pub_;
  rclcpp::TimerBase::SharedPtr tx_timer_;
  rclcpp::TimerBase::SharedPtr brief_timer_;
  rclcpp::TimerBase::SharedPtr detail_timer_;
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
