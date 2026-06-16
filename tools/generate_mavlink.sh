#!/usr/bin/env bash
set -euo pipefail

SCRIPT_DIR="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"
MAVLINK_DIR="${SCRIPT_DIR}/mavlink"
PYTHON="${SCRIPT_DIR}/.venv/bin/python"
XML_FILE="${SCRIPT_DIR}/sealien_mavlink.xml"
OUTPUT_DIR="${SCRIPT_DIR}/../lib/v2.0"
OUTPUT_DIALECT_DIR="${OUTPUT_DIR}/sealien_mavlink"

if [[ ! -x "${PYTHON}" ]]; then
  echo "Missing Python virtualenv: ${PYTHON}" >&2
  echo "Create it with: python3 -m venv ${SCRIPT_DIR}/.venv" >&2
  echo "Then install: ${SCRIPT_DIR}/.venv/bin/python -m pip install -r ${MAVLINK_DIR}/pymavlink/requirements.txt" >&2
  exit 1
fi

if [[ ! -d "${MAVLINK_DIR}/pymavlink" ]]; then
  echo "Missing MAVLink toolchain: ${MAVLINK_DIR}" >&2
  echo "Clone it with: git clone --recursive https://github.com/mavlink/mavlink.git ${MAVLINK_DIR}" >&2
  exit 1
fi

rm -rf "${OUTPUT_DIALECT_DIR}"
mkdir -p "${OUTPUT_DIR}"

cd "${MAVLINK_DIR}"
"${PYTHON}" -m pymavlink.tools.mavgen \
  --lang=C \
  --wire-protocol=2.0 \
  --output="${OUTPUT_DIR}" \
  "${XML_FILE}"
