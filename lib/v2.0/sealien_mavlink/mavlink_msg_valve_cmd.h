#pragma once
// MESSAGE VALVE_CMD PACKING

#define MAVLINK_MSG_ID_VALVE_CMD 21


typedef struct __mavlink_valve_cmd_t {
 uint32_t timestamp_ms; /*< [ms] Timestamp from the sender clock.*/
 uint32_t sensor_power_mask; /*<  32-channel 24 V sensor power bitmap, bit 0 maps to channel 1. 0xFFFFFFFF means do not update sensor power.*/
 int16_t current_ma[40]; /*< [mA] Target current for 40 valves. Valid range is 0-1500 mA; -1 skips that valve in sparse frames.*/
 uint16_t freq_hz[40]; /*< [Hz] Target frequency for 40 valves. Valid range is 110-2500 Hz; 0 skips that valve in sparse frames.*/
} mavlink_valve_cmd_t;

#define MAVLINK_MSG_ID_VALVE_CMD_LEN 168
#define MAVLINK_MSG_ID_VALVE_CMD_MIN_LEN 168
#define MAVLINK_MSG_ID_21_LEN 168
#define MAVLINK_MSG_ID_21_MIN_LEN 168

#define MAVLINK_MSG_ID_VALVE_CMD_CRC 228
#define MAVLINK_MSG_ID_21_CRC 228

#define MAVLINK_MSG_VALVE_CMD_FIELD_CURRENT_MA_LEN 40
#define MAVLINK_MSG_VALVE_CMD_FIELD_FREQ_HZ_LEN 40

#if MAVLINK_COMMAND_24BIT
#define MAVLINK_MESSAGE_INFO_VALVE_CMD { \
    21, \
    "VALVE_CMD", \
    4, \
    {  { "timestamp_ms", NULL, MAVLINK_TYPE_UINT32_T, 0, 0, offsetof(mavlink_valve_cmd_t, timestamp_ms) }, \
         { "sensor_power_mask", NULL, MAVLINK_TYPE_UINT32_T, 0, 4, offsetof(mavlink_valve_cmd_t, sensor_power_mask) }, \
         { "current_ma", NULL, MAVLINK_TYPE_INT16_T, 40, 8, offsetof(mavlink_valve_cmd_t, current_ma) }, \
         { "freq_hz", NULL, MAVLINK_TYPE_UINT16_T, 40, 88, offsetof(mavlink_valve_cmd_t, freq_hz) }, \
         } \
}
#else
#define MAVLINK_MESSAGE_INFO_VALVE_CMD { \
    "VALVE_CMD", \
    4, \
    {  { "timestamp_ms", NULL, MAVLINK_TYPE_UINT32_T, 0, 0, offsetof(mavlink_valve_cmd_t, timestamp_ms) }, \
         { "sensor_power_mask", NULL, MAVLINK_TYPE_UINT32_T, 0, 4, offsetof(mavlink_valve_cmd_t, sensor_power_mask) }, \
         { "current_ma", NULL, MAVLINK_TYPE_INT16_T, 40, 8, offsetof(mavlink_valve_cmd_t, current_ma) }, \
         { "freq_hz", NULL, MAVLINK_TYPE_UINT16_T, 40, 88, offsetof(mavlink_valve_cmd_t, freq_hz) }, \
         } \
}
#endif

/**
 * @brief Pack a valve_cmd message
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param msg The MAVLink message to compress the data into
 *
 * @param timestamp_ms [ms] Timestamp from the sender clock.
 * @param sensor_power_mask  32-channel 24 V sensor power bitmap, bit 0 maps to channel 1. 0xFFFFFFFF means do not update sensor power.
 * @param current_ma [mA] Target current for 40 valves. Valid range is 0-1500 mA; -1 skips that valve in sparse frames.
 * @param freq_hz [Hz] Target frequency for 40 valves. Valid range is 110-2500 Hz; 0 skips that valve in sparse frames.
 * @return length of the message in bytes (excluding serial stream start sign)
 */
static inline uint16_t mavlink_msg_valve_cmd_pack(uint8_t system_id, uint8_t component_id, mavlink_message_t* msg,
                               uint32_t timestamp_ms, uint32_t sensor_power_mask, const int16_t *current_ma, const uint16_t *freq_hz)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    char buf[MAVLINK_MSG_ID_VALVE_CMD_LEN];
    _mav_put_uint32_t(buf, 0, timestamp_ms);
    _mav_put_uint32_t(buf, 4, sensor_power_mask);
    _mav_put_int16_t_array(buf, 8, current_ma, 40);
    _mav_put_uint16_t_array(buf, 88, freq_hz, 40);
        memcpy(_MAV_PAYLOAD_NON_CONST(msg), buf, MAVLINK_MSG_ID_VALVE_CMD_LEN);
#else
    mavlink_valve_cmd_t packet;
    packet.timestamp_ms = timestamp_ms;
    packet.sensor_power_mask = sensor_power_mask;
    mav_array_memcpy(packet.current_ma, current_ma, sizeof(int16_t)*40);
    mav_array_memcpy(packet.freq_hz, freq_hz, sizeof(uint16_t)*40);
        memcpy(_MAV_PAYLOAD_NON_CONST(msg), &packet, MAVLINK_MSG_ID_VALVE_CMD_LEN);
#endif

    msg->msgid = MAVLINK_MSG_ID_VALVE_CMD;
    return mavlink_finalize_message(msg, system_id, component_id, MAVLINK_MSG_ID_VALVE_CMD_MIN_LEN, MAVLINK_MSG_ID_VALVE_CMD_LEN, MAVLINK_MSG_ID_VALVE_CMD_CRC);
}

/**
 * @brief Pack a valve_cmd message
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param status MAVLink status structure
 * @param msg The MAVLink message to compress the data into
 *
 * @param timestamp_ms [ms] Timestamp from the sender clock.
 * @param sensor_power_mask  32-channel 24 V sensor power bitmap, bit 0 maps to channel 1. 0xFFFFFFFF means do not update sensor power.
 * @param current_ma [mA] Target current for 40 valves. Valid range is 0-1500 mA; -1 skips that valve in sparse frames.
 * @param freq_hz [Hz] Target frequency for 40 valves. Valid range is 110-2500 Hz; 0 skips that valve in sparse frames.
 * @return length of the message in bytes (excluding serial stream start sign)
 */
static inline uint16_t mavlink_msg_valve_cmd_pack_status(uint8_t system_id, uint8_t component_id, mavlink_status_t *_status, mavlink_message_t* msg,
                               uint32_t timestamp_ms, uint32_t sensor_power_mask, const int16_t *current_ma, const uint16_t *freq_hz)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    char buf[MAVLINK_MSG_ID_VALVE_CMD_LEN];
    _mav_put_uint32_t(buf, 0, timestamp_ms);
    _mav_put_uint32_t(buf, 4, sensor_power_mask);
    _mav_put_int16_t_array(buf, 8, current_ma, 40);
    _mav_put_uint16_t_array(buf, 88, freq_hz, 40);
        memcpy(_MAV_PAYLOAD_NON_CONST(msg), buf, MAVLINK_MSG_ID_VALVE_CMD_LEN);
#else
    mavlink_valve_cmd_t packet;
    packet.timestamp_ms = timestamp_ms;
    packet.sensor_power_mask = sensor_power_mask;
    mav_array_memcpy(packet.current_ma, current_ma, sizeof(int16_t)*40);
    mav_array_memcpy(packet.freq_hz, freq_hz, sizeof(uint16_t)*40);
        memcpy(_MAV_PAYLOAD_NON_CONST(msg), &packet, MAVLINK_MSG_ID_VALVE_CMD_LEN);
#endif

    msg->msgid = MAVLINK_MSG_ID_VALVE_CMD;
#if MAVLINK_CRC_EXTRA
    return mavlink_finalize_message_buffer(msg, system_id, component_id, _status, MAVLINK_MSG_ID_VALVE_CMD_MIN_LEN, MAVLINK_MSG_ID_VALVE_CMD_LEN, MAVLINK_MSG_ID_VALVE_CMD_CRC);
#else
    return mavlink_finalize_message_buffer(msg, system_id, component_id, _status, MAVLINK_MSG_ID_VALVE_CMD_MIN_LEN, MAVLINK_MSG_ID_VALVE_CMD_LEN);
#endif
}

/**
 * @brief Pack a valve_cmd message on a channel
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param chan The MAVLink channel this message will be sent over
 * @param msg The MAVLink message to compress the data into
 * @param timestamp_ms [ms] Timestamp from the sender clock.
 * @param sensor_power_mask  32-channel 24 V sensor power bitmap, bit 0 maps to channel 1. 0xFFFFFFFF means do not update sensor power.
 * @param current_ma [mA] Target current for 40 valves. Valid range is 0-1500 mA; -1 skips that valve in sparse frames.
 * @param freq_hz [Hz] Target frequency for 40 valves. Valid range is 110-2500 Hz; 0 skips that valve in sparse frames.
 * @return length of the message in bytes (excluding serial stream start sign)
 */
static inline uint16_t mavlink_msg_valve_cmd_pack_chan(uint8_t system_id, uint8_t component_id, uint8_t chan,
                               mavlink_message_t* msg,
                                   uint32_t timestamp_ms,uint32_t sensor_power_mask,const int16_t *current_ma,const uint16_t *freq_hz)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    char buf[MAVLINK_MSG_ID_VALVE_CMD_LEN];
    _mav_put_uint32_t(buf, 0, timestamp_ms);
    _mav_put_uint32_t(buf, 4, sensor_power_mask);
    _mav_put_int16_t_array(buf, 8, current_ma, 40);
    _mav_put_uint16_t_array(buf, 88, freq_hz, 40);
        memcpy(_MAV_PAYLOAD_NON_CONST(msg), buf, MAVLINK_MSG_ID_VALVE_CMD_LEN);
#else
    mavlink_valve_cmd_t packet;
    packet.timestamp_ms = timestamp_ms;
    packet.sensor_power_mask = sensor_power_mask;
    mav_array_memcpy(packet.current_ma, current_ma, sizeof(int16_t)*40);
    mav_array_memcpy(packet.freq_hz, freq_hz, sizeof(uint16_t)*40);
        memcpy(_MAV_PAYLOAD_NON_CONST(msg), &packet, MAVLINK_MSG_ID_VALVE_CMD_LEN);
#endif

    msg->msgid = MAVLINK_MSG_ID_VALVE_CMD;
    return mavlink_finalize_message_chan(msg, system_id, component_id, chan, MAVLINK_MSG_ID_VALVE_CMD_MIN_LEN, MAVLINK_MSG_ID_VALVE_CMD_LEN, MAVLINK_MSG_ID_VALVE_CMD_CRC);
}

/**
 * @brief Encode a valve_cmd struct
 *
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param msg The MAVLink message to compress the data into
 * @param valve_cmd C-struct to read the message contents from
 */
static inline uint16_t mavlink_msg_valve_cmd_encode(uint8_t system_id, uint8_t component_id, mavlink_message_t* msg, const mavlink_valve_cmd_t* valve_cmd)
{
    return mavlink_msg_valve_cmd_pack(system_id, component_id, msg, valve_cmd->timestamp_ms, valve_cmd->sensor_power_mask, valve_cmd->current_ma, valve_cmd->freq_hz);
}

/**
 * @brief Encode a valve_cmd struct on a channel
 *
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param chan The MAVLink channel this message will be sent over
 * @param msg The MAVLink message to compress the data into
 * @param valve_cmd C-struct to read the message contents from
 */
static inline uint16_t mavlink_msg_valve_cmd_encode_chan(uint8_t system_id, uint8_t component_id, uint8_t chan, mavlink_message_t* msg, const mavlink_valve_cmd_t* valve_cmd)
{
    return mavlink_msg_valve_cmd_pack_chan(system_id, component_id, chan, msg, valve_cmd->timestamp_ms, valve_cmd->sensor_power_mask, valve_cmd->current_ma, valve_cmd->freq_hz);
}

/**
 * @brief Encode a valve_cmd struct with provided status structure
 *
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param status MAVLink status structure
 * @param msg The MAVLink message to compress the data into
 * @param valve_cmd C-struct to read the message contents from
 */
static inline uint16_t mavlink_msg_valve_cmd_encode_status(uint8_t system_id, uint8_t component_id, mavlink_status_t* _status, mavlink_message_t* msg, const mavlink_valve_cmd_t* valve_cmd)
{
    return mavlink_msg_valve_cmd_pack_status(system_id, component_id, _status, msg,  valve_cmd->timestamp_ms, valve_cmd->sensor_power_mask, valve_cmd->current_ma, valve_cmd->freq_hz);
}

/**
 * @brief Send a valve_cmd message
 * @param chan MAVLink channel to send the message
 *
 * @param timestamp_ms [ms] Timestamp from the sender clock.
 * @param sensor_power_mask  32-channel 24 V sensor power bitmap, bit 0 maps to channel 1. 0xFFFFFFFF means do not update sensor power.
 * @param current_ma [mA] Target current for 40 valves. Valid range is 0-1500 mA; -1 skips that valve in sparse frames.
 * @param freq_hz [Hz] Target frequency for 40 valves. Valid range is 110-2500 Hz; 0 skips that valve in sparse frames.
 */
#ifdef MAVLINK_USE_CONVENIENCE_FUNCTIONS

static inline void mavlink_msg_valve_cmd_send(mavlink_channel_t chan, uint32_t timestamp_ms, uint32_t sensor_power_mask, const int16_t *current_ma, const uint16_t *freq_hz)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    char buf[MAVLINK_MSG_ID_VALVE_CMD_LEN];
    _mav_put_uint32_t(buf, 0, timestamp_ms);
    _mav_put_uint32_t(buf, 4, sensor_power_mask);
    _mav_put_int16_t_array(buf, 8, current_ma, 40);
    _mav_put_uint16_t_array(buf, 88, freq_hz, 40);
    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_VALVE_CMD, buf, MAVLINK_MSG_ID_VALVE_CMD_MIN_LEN, MAVLINK_MSG_ID_VALVE_CMD_LEN, MAVLINK_MSG_ID_VALVE_CMD_CRC);
#else
    mavlink_valve_cmd_t packet;
    packet.timestamp_ms = timestamp_ms;
    packet.sensor_power_mask = sensor_power_mask;
    mav_array_memcpy(packet.current_ma, current_ma, sizeof(int16_t)*40);
    mav_array_memcpy(packet.freq_hz, freq_hz, sizeof(uint16_t)*40);
    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_VALVE_CMD, (const char *)&packet, MAVLINK_MSG_ID_VALVE_CMD_MIN_LEN, MAVLINK_MSG_ID_VALVE_CMD_LEN, MAVLINK_MSG_ID_VALVE_CMD_CRC);
#endif
}

/**
 * @brief Send a valve_cmd message
 * @param chan MAVLink channel to send the message
 * @param struct The MAVLink struct to serialize
 */
static inline void mavlink_msg_valve_cmd_send_struct(mavlink_channel_t chan, const mavlink_valve_cmd_t* valve_cmd)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    mavlink_msg_valve_cmd_send(chan, valve_cmd->timestamp_ms, valve_cmd->sensor_power_mask, valve_cmd->current_ma, valve_cmd->freq_hz);
#else
    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_VALVE_CMD, (const char *)valve_cmd, MAVLINK_MSG_ID_VALVE_CMD_MIN_LEN, MAVLINK_MSG_ID_VALVE_CMD_LEN, MAVLINK_MSG_ID_VALVE_CMD_CRC);
#endif
}

#if MAVLINK_MSG_ID_VALVE_CMD_LEN <= MAVLINK_MAX_PAYLOAD_LEN
/*
  This variant of _send() can be used to save stack space by reusing
  memory from the receive buffer.  The caller provides a
  mavlink_message_t which is the size of a full mavlink message. This
  is usually the receive buffer for the channel, and allows a reply to an
  incoming message with minimum stack space usage.
 */
static inline void mavlink_msg_valve_cmd_send_buf(mavlink_message_t *msgbuf, mavlink_channel_t chan,  uint32_t timestamp_ms, uint32_t sensor_power_mask, const int16_t *current_ma, const uint16_t *freq_hz)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    char *buf = (char *)msgbuf;
    _mav_put_uint32_t(buf, 0, timestamp_ms);
    _mav_put_uint32_t(buf, 4, sensor_power_mask);
    _mav_put_int16_t_array(buf, 8, current_ma, 40);
    _mav_put_uint16_t_array(buf, 88, freq_hz, 40);
    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_VALVE_CMD, buf, MAVLINK_MSG_ID_VALVE_CMD_MIN_LEN, MAVLINK_MSG_ID_VALVE_CMD_LEN, MAVLINK_MSG_ID_VALVE_CMD_CRC);
#else
    mavlink_valve_cmd_t *packet = (mavlink_valve_cmd_t *)msgbuf;
    packet->timestamp_ms = timestamp_ms;
    packet->sensor_power_mask = sensor_power_mask;
    mav_array_memcpy(packet->current_ma, current_ma, sizeof(int16_t)*40);
    mav_array_memcpy(packet->freq_hz, freq_hz, sizeof(uint16_t)*40);
    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_VALVE_CMD, (const char *)packet, MAVLINK_MSG_ID_VALVE_CMD_MIN_LEN, MAVLINK_MSG_ID_VALVE_CMD_LEN, MAVLINK_MSG_ID_VALVE_CMD_CRC);
#endif
}
#endif

#endif

// MESSAGE VALVE_CMD UNPACKING


/**
 * @brief Get field timestamp_ms from valve_cmd message
 *
 * @return [ms] Timestamp from the sender clock.
 */
static inline uint32_t mavlink_msg_valve_cmd_get_timestamp_ms(const mavlink_message_t* msg)
{
    return _MAV_RETURN_uint32_t(msg,  0);
}

/**
 * @brief Get field sensor_power_mask from valve_cmd message
 *
 * @return  32-channel 24 V sensor power bitmap, bit 0 maps to channel 1. 0xFFFFFFFF means do not update sensor power.
 */
static inline uint32_t mavlink_msg_valve_cmd_get_sensor_power_mask(const mavlink_message_t* msg)
{
    return _MAV_RETURN_uint32_t(msg,  4);
}

/**
 * @brief Get field current_ma from valve_cmd message
 *
 * @return [mA] Target current for 40 valves. Valid range is 0-1500 mA; -1 skips that valve in sparse frames.
 */
static inline uint16_t mavlink_msg_valve_cmd_get_current_ma(const mavlink_message_t* msg, int16_t *current_ma)
{
    return _MAV_RETURN_int16_t_array(msg, current_ma, 40,  8);
}

/**
 * @brief Get field freq_hz from valve_cmd message
 *
 * @return [Hz] Target frequency for 40 valves. Valid range is 110-2500 Hz; 0 skips that valve in sparse frames.
 */
static inline uint16_t mavlink_msg_valve_cmd_get_freq_hz(const mavlink_message_t* msg, uint16_t *freq_hz)
{
    return _MAV_RETURN_uint16_t_array(msg, freq_hz, 40,  88);
}

/**
 * @brief Decode a valve_cmd message into a struct
 *
 * @param msg The message to decode
 * @param valve_cmd C-struct to decode the message contents into
 */
static inline void mavlink_msg_valve_cmd_decode(const mavlink_message_t* msg, mavlink_valve_cmd_t* valve_cmd)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    valve_cmd->timestamp_ms = mavlink_msg_valve_cmd_get_timestamp_ms(msg);
    valve_cmd->sensor_power_mask = mavlink_msg_valve_cmd_get_sensor_power_mask(msg);
    mavlink_msg_valve_cmd_get_current_ma(msg, valve_cmd->current_ma);
    mavlink_msg_valve_cmd_get_freq_hz(msg, valve_cmd->freq_hz);
#else
        uint8_t len = msg->len < MAVLINK_MSG_ID_VALVE_CMD_LEN? msg->len : MAVLINK_MSG_ID_VALVE_CMD_LEN;
        memset(valve_cmd, 0, MAVLINK_MSG_ID_VALVE_CMD_LEN);
    memcpy(valve_cmd, _MAV_PAYLOAD(msg), len);
#endif
}
