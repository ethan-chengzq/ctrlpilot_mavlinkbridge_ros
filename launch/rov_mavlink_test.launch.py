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

    bridge_params = {
        "config_file": config_file,
        "topic_prefix": topic_prefix,
        "auto_reload": _as_bool(LaunchConfiguration("auto_reload").perform(context)),
    }

    test_params = {
        "config_file": config_file,
        "topic_prefix": topic_prefix,
        "tx_period_ms": _as_int("tx_period_ms", LaunchConfiguration("tx_period_ms").perform(context)),
        "quality_report_period_sec": _as_int(
            "quality_report_period_sec",
            LaunchConfiguration("quality_report_period_sec").perform(context),
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
        "safe_mode": _as_bool(LaunchConfiguration("safe_mode").perform(context)),
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
                description="ROS-side test command publish period in milliseconds.",
            ),
            DeclareLaunchArgument(
                "quality_report_period_sec",
                default_value="5",
                description="Test node quality report period in seconds.",
            ),
            DeclareLaunchArgument(
                "quality_link_timeout_ms",
                default_value="3000",
                description="Test node RX timeout used for link state reporting.",
            ),
            DeclareLaunchArgument(
                "include_heartbeat_tx",
                default_value="false",
                description="Whether the test node also publishes HEARTBEAT topic messages.",
            ),
            DeclareLaunchArgument(
                "log_quality_report",
                default_value="true",
                description="Whether the test node prints terminal quality reports.",
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
