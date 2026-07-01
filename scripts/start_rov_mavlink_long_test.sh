#!/usr/bin/env bash
set -Eeuo pipefail

PKG_NAME="sealien_ctrlpilot_mavlinkbridge"
WORKSPACE_DIR="${WORKSPACE_DIR:-/home/se113/SLWS/SealienDCN}"
PACKAGE_DIR="${PACKAGE_DIR:-${WORKSPACE_DIR}/src/${PKG_NAME}}"
LOG_ROOT="${LOG_ROOT:-${PACKAGE_DIR}/logs/mavlink_long_test}"
RUN_ID="${RUN_ID:-$(date +%Y%m%d_%H%M%S)}"
LOG_DIR="${LOG_DIR:-${LOG_ROOT}/${RUN_ID}}"

EP101_DEV="${EP101_DEV:-/dev/ttyACM1}"
EP102_DEV="${EP102_DEV:-/dev/ttyACM2}"
EP103_DEV="${EP103_DEV:-/dev/ttyACM3}"
SERIAL_BAUD="${SERIAL_BAUD:-115200}"

CONFIG_FILE="${CONFIG_FILE:-${WORKSPACE_DIR}/src/${PKG_NAME}/config/sealien_mavlink_rov.yaml}"
TOPIC_PREFIX="${TOPIC_PREFIX:-rov}"
TARGET_ENDPOINTS="${TARGET_ENDPOINTS:-[]}"
BRIEF_REPORT_PERIOD_SEC="${BRIEF_REPORT_PERIOD_SEC:-5}"
DETAIL_REPORT_PERIOD_SEC="${DETAIL_REPORT_PERIOD_SEC:-60}"
TX_STATS_PERIOD_SEC="${TX_STATS_PERIOD_SEC:-60}"
REBOOT_STM32_ON_START="${REBOOT_STM32_ON_START:-true}"
ROS_START_DELAY_SEC="${ROS_START_DELAY_SEC:-20}"
CLEANUP_ONLY="false"

usage() {
  cat <<EOF
Usage:
  $0
  $0 --cleanup-only

Start a long-running MAVLink stress test with two Terminator windows:
  1) ROS test node log -> ${LOG_DIR}/ros_all_ep.log
  2) EP101/EP102/EP103 merged STM32 serial log -> ${LOG_DIR}/stm32_all_serial.log

The test has no timeout. Stop it manually from the ROS and STM32 windows.

Options:
  --cleanup-only       Release EP101/EP102/EP103 serial devices and lock files, then exit.
  -h, --help           Show this help.

Defaults:
  workspace=${WORKSPACE_DIR}
  package_dir=${PACKAGE_DIR}
  ep101=${EP101_DEV}
  ep102=${EP102_DEV}
  ep103=${EP103_DEV}
  baud=${SERIAL_BAUD}
  log_root=${LOG_ROOT}
  reboot_stm32_on_start=${REBOOT_STM32_ON_START}
  ros_start_delay_sec=${ROS_START_DELAY_SEC}
EOF
}

die() {
  echo "ERROR: $*" >&2
  exit 1
}

shell_quote() {
  printf '%q' "$1"
}

clean_log_tee() {
  local log_file="$1"
  python3 -u -c '
import re
import sys

log_file = sys.argv[1]
ansi_re = re.compile(r"\x1B(?:[@-Z\\-_]|\[[0-?]*[ -/]*[@-~]|\][^\x07]*(?:\x07|\x1B\\))")
sys.stdin.reconfigure(errors="replace")
sys.stdout.reconfigure(errors="replace")

def clean_for_log(text):
    text = ansi_re.sub("", text)
    text = text.replace("\r", "")
    return "".join(ch for ch in text if ch == "\n" or ch == "\t" or ord(ch) >= 32)

with open(log_file, "a", encoding="utf-8", errors="replace", buffering=1) as log:
    for chunk in sys.stdin:
        sys.stdout.write(chunk)
        sys.stdout.flush()
        log.write(clean_for_log(chunk))
        log.flush()
' "${log_file}"
}

write_run_info() {
  mkdir -p "${LOG_DIR}"
  cat > "${LOG_DIR}/run_info.txt" <<EOF
run_id=${RUN_ID}
start_time=$(date --iso-8601=seconds)
workspace=${WORKSPACE_DIR}
package_dir=${PACKAGE_DIR}
config_file=${CONFIG_FILE}
topic_prefix=${TOPIC_PREFIX}
target_endpoints=${TARGET_ENDPOINTS}
brief_report_period_sec=${BRIEF_REPORT_PERIOD_SEC}
detail_report_period_sec=${DETAIL_REPORT_PERIOD_SEC}
tx_stats_period_sec=${TX_STATS_PERIOD_SEC}
ep101_dev=${EP101_DEV}
ep102_dev=${EP102_DEV}
ep103_dev=${EP103_DEV}
serial_baud=${SERIAL_BAUD}
reboot_stm32_on_start=${REBOOT_STM32_ON_START}
ros_start_delay_sec=${ROS_START_DELAY_SEC}
ros_log=${LOG_DIR}/ros_all_ep.log
stm32_log=${LOG_DIR}/stm32_all_serial.log
EOF
}

collect_existing_serial_devices() {
  serial_devices=()
  local dev
  for dev in "${EP101_DEV}" "${EP102_DEV}" "${EP103_DEV}"; do
    if [[ -e "${dev}" ]]; then
      serial_devices+=("${dev}")
    else
      echo "WARN: ${dev} does not exist."
    fi
  done
}

release_serial_devices() {
  local occupied=()
  local still_busy=()
  local dev

  collect_existing_serial_devices
  if [[ ${#serial_devices[@]} -eq 0 ]]; then
    return
  fi

  if ! command -v fuser >/dev/null 2>&1; then
    echo "WARN: fuser not found; close serial tools manually if devices are busy."
    return
  fi

  for dev in "${serial_devices[@]}"; do
    if sudo fuser "${dev}" >/dev/null 2>&1; then
      occupied+=("${dev}")
    fi
  done

  if [[ ${#occupied[@]} -eq 0 ]]; then
    echo "Serial devices are free."
    return
  fi

  echo "Serial devices are in use; terminating holders:"
  for dev in "${occupied[@]}"; do
    echo "  ${dev}:"
    sudo fuser -v "${dev}" 2>&1 || true
  done

  sudo fuser -k -TERM "${occupied[@]}" >/dev/null 2>&1 || true
  sleep 1

  for dev in "${occupied[@]}"; do
    if sudo fuser "${dev}" >/dev/null 2>&1; then
      still_busy+=("${dev}")
    fi
  done

  if [[ ${#still_busy[@]} -gt 0 ]]; then
    echo "Still busy after SIGTERM; forcing close:"
    sudo fuser -k -KILL "${still_busy[@]}" >/dev/null 2>&1 || true
    sleep 1
  fi
}

cleanup_stale_serial_locks() {
  local dev base lock

  collect_existing_serial_devices
  for dev in "${serial_devices[@]:-}"; do
    base="$(basename "${dev}")"
    for lock in "/var/lock/LCK..${base}" "/run/lock/LCK..${base}"; do
      if [[ -e "${lock}" ]]; then
        echo "Removing stale serial lock: ${lock}"
        sudo rm -f "${lock}"
      fi
    done
  done
}

prepare_serial_devices() {
  collect_existing_serial_devices
  if [[ ${#serial_devices[@]} -gt 0 ]]; then
    sudo chmod a+rw "${serial_devices[@]}"
  fi
}

cleanup_serial_resources() {
  sudo -v
  release_serial_devices
  cleanup_stale_serial_locks
}

run_ros_window() {
  local log_file="${LOG_DIR}/ros_all_ep.log"
  mkdir -p "${LOG_DIR}"
  printf '\033]0;ROS MAVLink all endpoints\007'

  {
    echo "============================================================"
    echo "ROS MAVLink all-endpoint long stress test"
    echo "start_time=$(date --iso-8601=seconds)"
    echo "log_file=${log_file}"
    echo "workspace=${WORKSPACE_DIR}"
    echo "config_file=${CONFIG_FILE}"
    echo "target_endpoints=${TARGET_ENDPOINTS}"
    echo "Stop manually with Ctrl-C."
    echo "============================================================"
  } | clean_log_tee "${log_file}"

  cd "${WORKSPACE_DIR}"
  set +u
  # shellcheck disable=SC1091
  source install/setup.bash
  set -u

  stdbuf -oL -eL ros2 launch "${PKG_NAME}" rov_mavlink_test.launch.py \
    config_file:="${CONFIG_FILE}" \
    topic_prefix:="${TOPIC_PREFIX}" \
    target_endpoints:="${TARGET_ENDPOINTS}" \
    brief_report_period_sec:="${BRIEF_REPORT_PERIOD_SEC}" \
    detail_report_period_sec:="${DETAIL_REPORT_PERIOD_SEC}" \
    tx_stats_period_sec:="${TX_STATS_PERIOD_SEC}" \
    auto_reload:=false \
    publish_per_message_events:=false \
    publish_rx_mirror_topics:=false \
    log_quality_report:=true \
    safe_mode:=true \
    2>&1 | clean_log_tee "${log_file}"
}

run_stm32_window() {
  local log_file="${LOG_DIR}/stm32_all_serial.log"

  mkdir -p "${LOG_DIR}"
  printf '\033]0;STM32 merged serial logs\007'

  python3 -u - "${log_file}" "${SERIAL_BAUD}" "${REBOOT_STM32_ON_START}" \
    "EP101=${EP101_DEV}" "EP102=${EP102_DEV}" "EP103=${EP103_DEV}" <<'PY'
import errno
import fcntl
import os
import re
import select
import signal
import sys
import termios
import time

log_file = sys.argv[1]
baud_text = sys.argv[2]
reboot_on_start = sys.argv[3].lower() in ("1", "true", "yes", "on")
ports = []
for item in sys.argv[4:]:
    name, device = item.split("=", 1)
    ports.append({
        "name": name,
        "device": device,
        "fd": None,
        "buf": bytearray(),
        "old": None,
        "next_retry": 0.0,
        "pending_lines": [],
        "last_line_ts": 0.0,
        "reboot_sent": False,
    })

BAUD_MAP = {
    "9600": termios.B9600,
    "19200": termios.B19200,
    "38400": termios.B38400,
    "57600": termios.B57600,
    "115200": termios.B115200,
    "230400": getattr(termios, "B230400", termios.B115200),
    "460800": getattr(termios, "B460800", termios.B115200),
    "921600": getattr(termios, "B921600", termios.B115200),
}
baud = BAUD_MAP.get(baud_text)
if baud is None:
    print(f"ERROR: unsupported baud rate: {baud_text}", file=sys.stderr)
    sys.exit(2)

running = True
ansi_re = re.compile(r"\x1B(?:[@-Z\\-_]|\[[0-?]*[ -/]*[@-~]|\][^\x07]*(?:\x07|\x1B\\))")
BLOCK_FLUSH_IDLE_SEC = 0.25
MAX_PENDING_LINES = 240

def handle_stop(signum, frame):
    global running
    running = False

signal.signal(signal.SIGINT, handle_stop)
signal.signal(signal.SIGTERM, handle_stop)
signal.signal(signal.SIGHUP, handle_stop)

def clean_for_log(text):
    text = ansi_re.sub("", text)
    text = text.replace("\r", "")
    return "".join(ch for ch in text if ch == "\n" or ch == "\t" or ord(ch) >= 32)

def emit(log, text):
    sys.stdout.write(text + "\n")
    sys.stdout.flush()
    log.write(clean_for_log(text) + "\n")
    log.flush()

def emit_lines(log, lines):
    if not lines:
        return
    text = "\n".join(lines) + "\n"
    sys.stdout.write(text)
    sys.stdout.flush()
    log.write(clean_for_log(text))
    log.flush()

def flush_port_block(port, log):
    pending = port.get("pending_lines") or []
    if not pending:
        return
    emit_lines(log, pending)
    pending.clear()
    port["last_line_ts"] = 0.0

def flush_due_blocks(log):
    now = time.monotonic()
    for port in ports:
        pending = port.get("pending_lines") or []
        if pending and now - port.get("last_line_ts", 0.0) >= BLOCK_FLUSH_IDLE_SEC:
            flush_port_block(port, log)

def buffer_serial_line(port, log, text):
    pending = port["pending_lines"]
    pending.append(f"[{port['name']}] {text}")
    port["last_line_ts"] = time.monotonic()
    if len(pending) >= MAX_PENDING_LINES:
        flush_port_block(port, log)

def configure_serial(fd):
    old = termios.tcgetattr(fd)
    attrs = termios.tcgetattr(fd)
    attrs[0] &= ~(termios.IGNBRK | termios.BRKINT | termios.PARMRK |
                  termios.ISTRIP | termios.INLCR | termios.IGNCR |
                  termios.ICRNL | termios.IXON | termios.IXOFF)
    attrs[1] &= ~termios.OPOST
    attrs[2] &= ~(termios.CSIZE | termios.PARENB)
    attrs[2] |= termios.CS8 | termios.CREAD | termios.CLOCAL
    attrs[3] &= ~(termios.ECHO | termios.ECHONL | termios.ICANON |
                  termios.ISIG | termios.IEXTEN)
    attrs[4] = baud
    attrs[5] = baud
    attrs[6][termios.VMIN] = 0
    attrs[6][termios.VTIME] = 1
    termios.tcsetattr(fd, termios.TCSANOW, attrs)
    return old

def make_serial_exclusive(fd):
    request = getattr(termios, "TIOCEXCL", None)
    if request is not None:
        fcntl.ioctl(fd, request)

def close_port(port):
    fd = port.get("fd")
    if fd is not None:
        try:
            if port.get("old") is not None:
                termios.tcsetattr(fd, termios.TCSANOW, port["old"])
        except OSError:
            pass
        try:
            os.close(fd)
        except OSError:
            pass
    port["fd"] = None
    port["old"] = None
    port["buf"].clear()
    port["pending_lines"].clear()
    port["last_line_ts"] = 0.0
    port["next_retry"] = time.monotonic() + 2.0

def reboot_port_if_needed(port, log):
    if not reboot_on_start or port.get("reboot_sent"):
        return
    fd = port.get("fd")
    if fd is None:
        return
    try:
        os.write(fd, b"\r\nreboot\r\n")
        port["reboot_sent"] = True
        emit(log, f"[{port['name']}] reboot command sent; waiting for STM32 restart and clean counters.")
    except OSError as exc:
        emit(log, f"[{port['name']}] WARN: failed to send reboot command: {exc}")

def try_open(port, log):
    now = time.monotonic()
    if port["fd"] is not None or now < port["next_retry"]:
        return
    device = port["device"]
    if not os.path.exists(device):
        if port.get("missing_reported") != device:
            emit(log, f"[{port['name']}] ERROR: {device} does not exist.")
            port["missing_reported"] = device
        port["next_retry"] = now + 5.0
        return
    try:
        fd = os.open(device, os.O_RDWR | os.O_NOCTTY | os.O_NONBLOCK)
        make_serial_exclusive(fd)
        old = configure_serial(fd)
    except OSError as exc:
        emit(log, f"[{port['name']}] ERROR: failed to open/configure {device}: {exc}")
        try:
            os.close(fd)  # type: ignore[name-defined]
        except Exception:
            pass
        port["next_retry"] = now + 5.0
        return
    port["fd"] = fd
    port["old"] = old
    port["missing_reported"] = None
    emit(log, f"[{port['name']}] serial reader started device={device} baud={baud_text}")
    reboot_port_if_needed(port, log)

with open(log_file, "a", encoding="utf-8", errors="replace", buffering=1) as log:
    emit(log, "============================================================")
    emit(log, "STM32 merged serial log")
    emit(log, f"start_time={time.strftime('%Y-%m-%dT%H:%M:%S%z')}")
    for port in ports:
        emit(log, f"{port['name'].lower()}={port['device']}")
    emit(log, f"baud={baud_text}")
    emit(log, f"reboot_stm32_on_start={str(reboot_on_start).lower()}")
    emit(log, f"log_file={log_file}")
    emit(log, "Each line is prefixed by [EP101]/[EP102]/[EP103].")
    emit(log, "Serial ports are read by one select() loop to avoid FIFO writer buffering.")
    emit(log, f"Serial lines are grouped per endpoint after {int(BLOCK_FLUSH_IDLE_SEC * 1000)}ms idle.")
    emit(log, "Stop manually with Ctrl-C.")
    emit(log, "============================================================")

    while running:
        for port in ports:
            try_open(port, log)
        flush_due_blocks(log)

        fd_to_port = {port["fd"]: port for port in ports if port["fd"] is not None}
        if not fd_to_port:
            time.sleep(0.5)
            continue

        try:
            readable, _, _ = select.select(list(fd_to_port.keys()), [], [], 0.05)
        except OSError as exc:
            emit(log, f"[STM32] ERROR: select failed: {exc}")
            time.sleep(1.0)
            continue

        for fd in readable:
            port = fd_to_port.get(fd)
            if port is None:
                continue
            try:
                data = os.read(fd, 4096)
            except BlockingIOError:
                continue
            except OSError as exc:
                flush_port_block(port, log)
                if exc.errno not in (errno.EIO, errno.ENODEV):
                    emit(log, f"[{port['name']}] ERROR: read failed: {exc}")
                else:
                    emit(log, f"[{port['name']}] WARN: serial disconnected: {exc}")
                close_port(port)
                continue

            if not data:
                continue
            port["buf"].extend(data)
            while True:
                cr_pos = port["buf"].find(b"\r")
                lf_pos = port["buf"].find(b"\n")
                positions = [pos for pos in (cr_pos, lf_pos) if pos >= 0]
                if not positions:
                    break
                split_pos = min(positions)
                line = bytes(port["buf"][:split_pos])
                del port["buf"][:split_pos + 1]
                while port["buf"][:1] in (b"\r", b"\n"):
                    del port["buf"][:1]
                if not line:
                    continue
                text = line.decode("utf-8", errors="replace")
                buffer_serial_line(port, log, text)

    for port in ports:
        flush_port_block(port, log)

for port in ports:
    close_port(port)
PY
}

terminator_exec_arg() {
  local command="$1"
  local quoted
  quoted="$(shell_quote "${command}")"
  printf 'bash -lc %s' "${quoted}"
}

launch_windows() {
  local self="$1"
  local q_self q_log_dir q_workspace q_config q_target q_prefix q_ep101 q_ep102 q_ep103

  q_self="$(shell_quote "${self}")"
  q_log_dir="$(shell_quote "${LOG_DIR}")"
  q_workspace="$(shell_quote "${WORKSPACE_DIR}")"
  q_config="$(shell_quote "${CONFIG_FILE}")"
  q_target="$(shell_quote "${TARGET_ENDPOINTS}")"
  q_prefix="$(shell_quote "${TOPIC_PREFIX}")"
  q_ep101="$(shell_quote "${EP101_DEV}")"
  q_ep102="$(shell_quote "${EP102_DEV}")"
  q_ep103="$(shell_quote "${EP103_DEV}")"

  local env_args
  env_args="LOG_DIR=${q_log_dir} WORKSPACE_DIR=${q_workspace} CONFIG_FILE=${q_config} TARGET_ENDPOINTS=${q_target} TOPIC_PREFIX=${q_prefix} BRIEF_REPORT_PERIOD_SEC=${BRIEF_REPORT_PERIOD_SEC} DETAIL_REPORT_PERIOD_SEC=${DETAIL_REPORT_PERIOD_SEC} TX_STATS_PERIOD_SEC=${TX_STATS_PERIOD_SEC} REBOOT_STM32_ON_START=${REBOOT_STM32_ON_START} ROS_START_DELAY_SEC=${ROS_START_DELAY_SEC} SERIAL_BAUD=${SERIAL_BAUD} EP101_DEV=${q_ep101} EP102_DEV=${q_ep102} EP103_DEV=${q_ep103}"

  terminator -T "STM32 merged serial logs" \
    -e "$(terminator_exec_arg "${env_args} ${q_self} --pane stm32; exec bash")" &

  echo "STM32 serial window started. Waiting ${ROS_START_DELAY_SEC}s before starting ROS..."
  sleep "${ROS_START_DELAY_SEC}"

  terminator -T "ROS MAVLink all endpoints" \
    -e "$(terminator_exec_arg "${env_args} ${q_self} --pane ros; exec bash")" &
}

pane_mode=""

while [[ $# -gt 0 ]]; do
  case "$1" in
    --pane)
      pane_mode="${2:-}"
      shift 2
      ;;
    --cleanup-only)
      CLEANUP_ONLY="true"
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

case "${pane_mode}" in
  ros)
    run_ros_window
    exit 0
    ;;
  stm32)
    run_stm32_window
    exit 0
    ;;
  "")
    ;;
  *)
    die "unknown pane mode: ${pane_mode}"
    ;;
esac

mkdir -p "${LOG_DIR}"
write_run_info

if [[ "${CLEANUP_ONLY}" == "true" ]]; then
  echo "Cleanup-only mode: releasing serial devices and stale lock files."
  cleanup_serial_resources
  echo "Cleanup complete."
  exit 0
fi

command -v terminator >/dev/null 2>&1 || die "terminator not found. Install it first."
[[ -f "${WORKSPACE_DIR}/install/setup.bash" ]] ||
  die "missing ${WORKSPACE_DIR}/install/setup.bash. Build the workspace before starting the long test."

echo "Preparing serial devices. You may be prompted for sudo once..."
cleanup_serial_resources
prepare_serial_devices

self_path="$(readlink -f "$0")"

echo "Starting long MAVLink test."
echo "Log directory: ${LOG_DIR}"
echo "ROS log: ${LOG_DIR}/ros_all_ep.log"
echo "STM32 log: ${LOG_DIR}/stm32_all_serial.log"
echo "STM32 reboot on start: ${REBOOT_STM32_ON_START}"
echo "ROS start delay after STM32 window: ${ROS_START_DELAY_SEC}s"
echo "Stop manually from the ROS and STM32 windows."

launch_windows "${self_path}"
