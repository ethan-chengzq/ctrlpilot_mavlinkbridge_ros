#!/usr/bin/env bash
set -Eeuo pipefail

PKG_NAME="sealien_ctrlpilot_mavlinkbridge"

CONFIG_FILE="${CONFIG_FILE:-}"
TOPIC_PREFIX="${TOPIC_PREFIX:-rov}"
TARGET_ENDPOINTS="${TARGET_ENDPOINTS:-}"
TX_PERIOD_MS="${TX_PERIOD_MS:-1000}"
QUALITY_REPORT_PERIOD_SEC="${QUALITY_REPORT_PERIOD_SEC:-5}"
QUALITY_LINK_TIMEOUT_MS="${QUALITY_LINK_TIMEOUT_MS:-3000}"
INCLUDE_HEARTBEAT_TX="${INCLUDE_HEARTBEAT_TX:-false}"
LOG_QUALITY_REPORT="${LOG_QUALITY_REPORT:-true}"
SAFE_MODE="${SAFE_MODE:-true}"
AUTO_RELOAD="${AUTO_RELOAD:-true}"

bridge_pid=""
test_pid=""

usage() {
  cat <<EOF
Usage:
  $0 [options]

Starts both ROS nodes required for ROV MAVLink integration testing:
  1) rov_mavlink_node       : ROS Topic <-> UDP MAVLink bridge
  2) rov_mavlink_test_node  : ROS-side test publisher/subscriber/quality monitor

Options:
  --config FILE             YAML config file. Default: installed/source sealien_mavlink_rov.yaml
  --prefix NAME             ROS topic prefix. Default: ${TOPIC_PREFIX}
  --endpoints LIST          Target endpoint list. Example: nav_sensor_mcu,actuator_mcu
  --tx-period-ms N          Test TX publish period. Default: ${TX_PERIOD_MS}
  --quality-period-sec N    Quality report period. Default: ${QUALITY_REPORT_PERIOD_SEC}
  --timeout-ms N            Link timeout for test quality monitor. Default: ${QUALITY_LINK_TIMEOUT_MS}
  --include-heartbeat-tx    Let test node publish heartbeat topics too. Default: false
  --no-quality-log          Disable test node terminal quality report. Default: enabled
  --unsafe                  Disable safe_mode test payloads. Default: safe_mode=true
  --no-auto-reload          Disable bridge YAML auto reload. Default: enabled
  -h, --help                Show this help

Environment overrides:
  CONFIG_FILE TOPIC_PREFIX TARGET_ENDPOINTS TX_PERIOD_MS QUALITY_REPORT_PERIOD_SEC
  QUALITY_LINK_TIMEOUT_MS INCLUDE_HEARTBEAT_TX LOG_QUALITY_REPORT SAFE_MODE AUTO_RELOAD

Examples:
  # Test all enabled endpoints in YAML.
  $0

  # Test only the 101 nav sensor board.
  $0 --endpoints nav_sensor_mcu

  # Use ros2 run after colcon build and source install/setup.bash.
  ros2 run ${PKG_NAME} start_rov_mavlink_test.sh -- --endpoints nav_sensor_mcu
EOF
}

die() {
  echo "ERROR: $*" >&2
  exit 1
}

cleanup() {
  trap - EXIT INT TERM
  if [[ -n "${test_pid}" ]] && kill -0 "${test_pid}" 2>/dev/null; then
    kill "${test_pid}" 2>/dev/null || true
  fi
  if [[ -n "${bridge_pid}" ]] && kill -0 "${bridge_pid}" 2>/dev/null; then
    kill "${bridge_pid}" 2>/dev/null || true
  fi
  if [[ -n "${test_pid}" ]]; then
    wait "${test_pid}" 2>/dev/null || true
  fi
  if [[ -n "${bridge_pid}" ]]; then
    wait "${bridge_pid}" 2>/dev/null || true
  fi
}

ros_array_from_csv() {
  local input="$1"
  local trimmed="${input//[[:space:]]/}"

  if [[ -z "${trimmed}" ]]; then
    echo ""
    return
  fi

  if [[ "${trimmed}" == \[* ]]; then
    echo "${trimmed}"
    return
  fi

  local output="["
  local first="true"
  local item
  IFS=',' read -ra items <<< "${trimmed}"
  for item in "${items[@]}"; do
    [[ -z "${item}" ]] && continue
    if [[ "${first}" == "true" ]]; then
      first="false"
    else
      output+=","
    fi
    output+="'${item}'"
  done
  output+="]"
  echo "${output}"
}

while [[ $# -gt 0 ]]; do
  case "$1" in
    --config)
      CONFIG_FILE="${2:-}"
      shift 2
      ;;
    --prefix)
      TOPIC_PREFIX="${2:-}"
      shift 2
      ;;
    --endpoints)
      TARGET_ENDPOINTS="${2:-}"
      shift 2
      ;;
    --tx-period-ms)
      TX_PERIOD_MS="${2:-}"
      shift 2
      ;;
    --quality-period-sec)
      QUALITY_REPORT_PERIOD_SEC="${2:-}"
      shift 2
      ;;
    --timeout-ms)
      QUALITY_LINK_TIMEOUT_MS="${2:-}"
      shift 2
      ;;
    --include-heartbeat-tx)
      INCLUDE_HEARTBEAT_TX="true"
      shift
      ;;
    --no-quality-log)
      LOG_QUALITY_REPORT="false"
      shift
      ;;
    --unsafe)
      SAFE_MODE="false"
      shift
      ;;
    --no-auto-reload)
      AUTO_RELOAD="false"
      shift
      ;;
    -h|--help)
      usage
      exit 0
      ;;
    *)
      die "unknown option: $1"
      ;;
  esac
done

command -v ros2 >/dev/null 2>&1 || die "ros2 not found. Run: source install/setup.bash"

if [[ -z "${CONFIG_FILE}" ]]; then
  if pkg_prefix="$(ros2 pkg prefix "${PKG_NAME}" 2>/dev/null)"; then
    CONFIG_FILE="${pkg_prefix}/share/${PKG_NAME}/config/sealien_mavlink_rov.yaml"
  else
    script_dir="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"
    CONFIG_FILE="${script_dir}/../config/sealien_mavlink_rov.yaml"
  fi
fi

[[ -f "${CONFIG_FILE}" ]] || die "config file not found: ${CONFIG_FILE}"

endpoint_param=()
if [[ -n "${TARGET_ENDPOINTS}" ]]; then
  endpoint_param=(-p "target_endpoints:=$(ros_array_from_csv "${TARGET_ENDPOINTS}")")
fi

bridge_cmd=(
  ros2 run "${PKG_NAME}" rov_mavlink_node --ros-args
  -p "config_file:=${CONFIG_FILE}"
  -p "topic_prefix:=${TOPIC_PREFIX}"
  -p "auto_reload:=${AUTO_RELOAD}"
)

test_cmd=(
  ros2 run "${PKG_NAME}" rov_mavlink_test_node --ros-args
  -p "config_file:=${CONFIG_FILE}"
  -p "topic_prefix:=${TOPIC_PREFIX}"
  "${endpoint_param[@]}"
  -p "tx_period_ms:=${TX_PERIOD_MS}"
  -p "quality_report_period_sec:=${QUALITY_REPORT_PERIOD_SEC}"
  -p "quality_link_timeout_ms:=${QUALITY_LINK_TIMEOUT_MS}"
  -p "include_heartbeat_tx:=${INCLUDE_HEARTBEAT_TX}"
  -p "log_quality_report:=${LOG_QUALITY_REPORT}"
  -p "safe_mode:=${SAFE_MODE}"
)

echo "ROV MAVLink integration test"
echo "  config=${CONFIG_FILE}"
echo "  prefix=${TOPIC_PREFIX}"
echo "  endpoints=${TARGET_ENDPOINTS:-all enabled endpoints}"
echo "  tx_period_ms=${TX_PERIOD_MS}"
echo "  quality_period_sec=${QUALITY_REPORT_PERIOD_SEC}"
echo "  timeout_ms=${QUALITY_LINK_TIMEOUT_MS}"
echo
echo "Starting bridge node..."
"${bridge_cmd[@]}" &
bridge_pid=$!

sleep 1

echo "Starting test node..."
"${test_cmd[@]}" &
test_pid=$!

trap cleanup EXIT INT TERM

set +e
wait -n "${bridge_pid}" "${test_pid}"
status=$?
set -e

exit "${status}"
