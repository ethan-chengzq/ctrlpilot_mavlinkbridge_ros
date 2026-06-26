"""Launch ROV MAVLink bridge and ROS-side integration test node."""

import ast
import os

from ament_index_python.packages import get_package_share_directory
from launch import LaunchDescription
from launch.actions import DeclareLaunchArgument, OpaqueFunction
from launch.substitutions import LaunchConfiguration
from launch_ros.actions import Node


PKG_NAME = "sealien_ctrlpilot_mavlinkbridge"


def _as_bool(value: str) -> bool:
    return value.strip().lower() in ("1", "true", "yes", "on")


def _as_int(name: str, value: str) -> int:
    try:
        return int(value)
    except ValueError as exc:
        raise RuntimeError(f"launch argument {name} must be an integer: {value}") from exc


def _as_float(name: str, value: str) -> float:
    try:
        return float(value)
    except ValueError as exc:
        raise RuntimeError(f"launch argument {name} must be a number: {value}") from exc


def _parse_target_endpoints(value: str) -> list[str]:
    text = value.strip()
    if not text or text == "[]":
        return []

    if text.startswith("["):
        try:
            parsed = ast.literal_eval(text)
        except (SyntaxError, ValueError) as exc:
            raise RuntimeError(
                "target_endpoints must be a Python-style list or comma-separated string"
            ) from exc
        if not isinstance(parsed, (list, tuple)):
            raise RuntimeError("target_endpoints list value must contain endpoint names")
        return [str(item) for item in parsed]

    return [item.strip() for item in text.split(",") if item.strip()]


def _launch_setup(context, *_, **__):
    config_file = LaunchConfiguration("config_file").perform(context)
    topic_prefix = LaunchConfiguration("topic_prefix").perform(context)
    target_endpoints = _parse_target_endpoints(
        LaunchConfiguration("target_endpoints").perform(context)
    )
    detail_report_period_sec = LaunchConfiguration("detail_report_period_sec").perform(context).strip()
    if not detail_report_period_sec:
        detail_report_period_sec = LaunchConfiguration("quality_report_period_sec").perform(context)

    bridge_params = {
        "config_file": config_file,
        "topic_prefix": topic_prefix,
        "auto_reload": _as_bool(LaunchConfiguration("auto_reload").perform(context)),
        "ros_queue_depth": _as_int(
            "ros_queue_depth",
            LaunchConfiguration("ros_queue_depth").perform(context),
        ),
        "udp_recv_buffer_bytes": _as_int(
            "udp_recv_buffer_bytes",
            LaunchConfiguration("udp_recv_buffer_bytes").perform(context),
        ),
        "udp_send_buffer_bytes": _as_int(
            "udp_send_buffer_bytes",
            LaunchConfiguration("udp_send_buffer_bytes").perform(context),
        ),
        "rx_idle_sleep_ms": _as_int(
            "rx_idle_sleep_ms",
            LaunchConfiguration("rx_idle_sleep_ms").perform(context),
        ),
        "enable_tx_stats": _as_bool(
            LaunchConfiguration("enable_tx_stats").perform(context)
        ),
        "tx_stats_period_sec": _as_int(
            "tx_stats_period_sec",
            LaunchConfiguration("tx_stats_period_sec").perform(context),
        ),
        "heartbeat_host_tx_hz_override": _as_float(
            "bridge_heartbeat_host_tx_hz",
            LaunchConfiguration("bridge_heartbeat_host_tx_hz").perform(context),
        ),
    }

    test_params = {
        "config_file": config_file,
        "topic_prefix": topic_prefix,
        "tx_period_ms": _as_int("tx_period_ms", LaunchConfiguration("tx_period_ms").perform(context)),
        "tx_scheduler_period_ms": _as_int(
            "tx_scheduler_period_ms",
            LaunchConfiguration("tx_scheduler_period_ms").perform(context),
        ),
        "tx_route_stagger_ms": _as_int(
            "tx_route_stagger_ms",
            LaunchConfiguration("tx_route_stagger_ms").perform(context),
        ),
        "use_stress_rates": _as_bool(LaunchConfiguration("use_stress_rates").perform(context)),
        "brief_report_period_sec": _as_int(
            "brief_report_period_sec",
            LaunchConfiguration("brief_report_period_sec").perform(context),
        ),
        "detail_report_period_sec": _as_int(
            "detail_report_period_sec",
            detail_report_period_sec,
        ),
        "quality_link_timeout_ms": _as_int(
            "quality_link_timeout_ms",
            LaunchConfiguration("quality_link_timeout_ms").perform(context),
        ),
        "include_heartbeat_tx": _as_bool(
            LaunchConfiguration("include_heartbeat_tx").perform(context)
        ),
        "log_quality_report": _as_bool(
            LaunchConfiguration("log_quality_report").perform(context)
        ),
        "publish_per_message_events": _as_bool(
            LaunchConfiguration("publish_per_message_events").perform(context)
        ),
        "publish_rx_mirror_topics": _as_bool(
            LaunchConfiguration("publish_rx_mirror_topics").perform(context)
        ),
        "safe_mode": _as_bool(LaunchConfiguration("safe_mode").perform(context)),
        "subscribe_bridge_tx_stats": _as_bool(
            LaunchConfiguration("subscribe_bridge_tx_stats").perform(context)
        ),
        "bridge_tx_stats_topic": LaunchConfiguration("bridge_tx_stats_topic").perform(context),
    }
    # launch_ros cannot normalize an empty array parameter reliably across ROS 2
    # distributions. Omit it when empty so the C++ node keeps its declared default.
    if target_endpoints:
        test_params["target_endpoints"] = target_endpoints

    bridge_node = Node(
        package=PKG_NAME,
        executable="rov_mavlink_node",
        name="rov_mavlink_node",
        output="screen",
        emulate_tty=True,
        parameters=[bridge_params],
    )

    test_node = Node(
        package=PKG_NAME,
        executable="rov_mavlink_test_node",
        name="rov_mavlink_test_node",
        output="screen",
        emulate_tty=True,
        parameters=[test_params],
    )

    return [bridge_node, test_node]


def generate_launch_description():
    share_dir = get_package_share_directory(PKG_NAME)
    default_config = os.path.join(share_dir, "config", "sealien_mavlink_rov.yaml")

    return LaunchDescription(
        [
            DeclareLaunchArgument(
                "config_file",
                default_value=default_config,
                description="ROV MAVLink YAML config file.",
            ),
            DeclareLaunchArgument(
                "topic_prefix",
                default_value="rov",
                description="ROS topic prefix used by bridge and test nodes.",
            ),
            DeclareLaunchArgument(
                "target_endpoints",
                default_value="[]",
                description=(
                    "Endpoint names to test. Use [] for all enabled endpoints, "
                    "or e.g. \"['nav_sensor_mcu']\" / nav_sensor_mcu,actuator_mcu."
                ),
            ),
            DeclareLaunchArgument(
                "tx_period_ms",
                default_value="1000",
                description="Legacy ROS-side test command publish period when stress rates are disabled.",
            ),
            DeclareLaunchArgument(
                "tx_scheduler_period_ms",
                default_value="5",
                description="Scheduler tick in milliseconds when stress rates are enabled.",
            ),
            DeclareLaunchArgument(
                "tx_route_stagger_ms",
                default_value="20",
                description="Per-route phase offset in milliseconds for stress TX topics.",
            ),
            DeclareLaunchArgument(
                "use_stress_rates",
                default_value="true",
                description="Publish test messages by MSGID stress frequency map.",
            ),
            DeclareLaunchArgument(
                "brief_report_period_sec",
                default_value="5",
                description="Test node brief quality report period in seconds.",
            ),
            DeclareLaunchArgument(
                "quality_report_period_sec",
                default_value="60",
                description="Legacy alias for detail_report_period_sec.",
            ),
            DeclareLaunchArgument(
                "detail_report_period_sec",
                default_value="",
                description="Test node detailed quality report period in seconds.",
            ),
            DeclareLaunchArgument(
                "quality_link_timeout_ms",
                default_value="3000",
                description="Test node RX timeout used for link state reporting.",
            ),
            DeclareLaunchArgument(
                "include_heartbeat_tx",
                default_value="true",
                description="Whether the test node publishes and counts HEARTBEAT topic messages.",
            ),
            DeclareLaunchArgument(
                "log_quality_report",
                default_value="true",
                description="Whether the test node prints terminal quality reports.",
            ),
            DeclareLaunchArgument(
                "publish_per_message_events",
                default_value="false",
                description="Whether the test node publishes per-frame String event topics.",
            ),
            DeclareLaunchArgument(
                "publish_rx_mirror_topics",
                default_value="false",
                description="Whether the test node republishes RX messages to rov/test/from_mcu/* topics.",
            ),
            DeclareLaunchArgument(
                "subscribe_bridge_tx_stats",
                default_value="true",
                description="Whether the test node subscribes to bridge UDP sendto statistics.",
            ),
            DeclareLaunchArgument(
                "bridge_tx_stats_topic",
                default_value="/rov_mavlink_node/tx_stats",
                description="Topic published by rov_mavlink_node for actual UDP sendto statistics.",
            ),
            DeclareLaunchArgument(
                "ros_queue_depth",
                default_value="100",
                description="Bridge ROS publisher/subscription queue depth for MAVLink topic routes.",
            ),
            DeclareLaunchArgument(
                "udp_recv_buffer_bytes",
                default_value="262144",
                description="Bridge UDP receive socket buffer size in bytes; 0 keeps OS default.",
            ),
            DeclareLaunchArgument(
                "udp_send_buffer_bytes",
                default_value="262144",
                description="Bridge UDP send socket buffer size in bytes; 0 keeps OS default.",
            ),
            DeclareLaunchArgument(
                "rx_idle_sleep_ms",
                default_value="1",
                description="Bridge nonblocking UDP RX idle sleep in milliseconds; 0 yields.",
            ),
            DeclareLaunchArgument(
                "enable_tx_stats",
                default_value="true",
                description="Whether the bridge publishes/logs actual UDP sendto success counters.",
            ),
            DeclareLaunchArgument(
                "tx_stats_period_sec",
                default_value="60",
                description="Bridge actual UDP TX stats report period in seconds; 0 disables timer.",
            ),
            DeclareLaunchArgument(
                "bridge_heartbeat_host_tx_hz",
                default_value="0.0",
                description=(
                    "Override bridge-owned heartbeat rate. Use 0.0 in stress tests "
                    "so the test node owns HEARTBEAT timing/statistics; use -1.0 to keep YAML."
                ),
            ),
            DeclareLaunchArgument(
                "safe_mode",
                default_value="true",
                description="Use non-actuating command payloads for hardware-safe tests.",
            ),
            DeclareLaunchArgument(
                "auto_reload",
                default_value="true",
                description="Enable bridge YAML auto reload.",
            ),
            OpaqueFunction(function=_launch_setup),
        ]
    )
