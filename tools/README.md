# Sealien MAVLink Toolchain

This directory contains the local MAVLink generation toolchain for
`sealien_ctrlpilot_mavlinkbridge`.

## Layout

- `mavlink/`: official `mavlink/mavlink` repository cloned with submodules.
- `.venv/`: local Python virtual environment for `pymavlink` generator dependencies.
- `sealien_mavlink.xml`: Sealien private MAVLink dialect generated from the
  `mavlink` worksheet of `doc/数据采集板通信协议1.5.xlsx`.
- `generate_mavlink.sh`: regenerates C headers into `../lib/v2.0`.
- `../config/sealien_mavlink_rov.yaml`: ROV host and STM32 endpoint unicast
  routing configuration.
- `../config/sealien_mavlink_tms.yaml`: TMS host and STM32 endpoint unicast
  routing configuration.

## Regenerate Headers

Run from this directory or from the package root:

```bash
./tools/generate_mavlink.sh
```

The script validates `sealien_mavlink.xml`, removes the old
`../lib/v2.0/sealien_mavlink` generated dialect directory, then regenerates the
C headers with MAVLink 2.0 wire protocol.

The dialect intentionally does not include `common.xml`: the project defines a
private `HEARTBEAT` at message ID 0, which would collide with the MAVLink
standard `HEARTBEAT`.

## Endpoint Routing

`../config/sealien_mavlink_rov.yaml` and `../config/sealien_mavlink_tms.yaml`
use the same schema. Each endpoint has a unique `system_id`, UDP address, and
explicit `messages.rx` / `messages.tx` MSGID lists. These lists must reference
only MSGIDs defined in `sealien_mavlink.xml`.

Runtime code should send only to the endpoint whose `messages.tx` contains the
outgoing MSGID. Incoming frames should be accepted only when their MSGID is in
that endpoint's `messages.rx` list and the configured source identity matches.
Unknown or unrouted messages should be dropped.

When updating the workbook protocol, update `sealien_mavlink.xml` first, then
regenerate headers and check the changed message lengths/CRC values on both the
ROS host and STM32 firmware side.
