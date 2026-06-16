#pragma once
// MESSAGE DEPTH_STATUS PACKING

#define MAVLINK_MSG_ID_DEPTH_STATUS 7


typedef struct __mavlink_depth_status_t {
 uint32_t timestamp_ms; /*< [ms] Timestamp from the sender clock.*/
 float depth[4]; /*< [m] Depth values.*/
 float temp[4]; /*< [degC] Temperature values.*/
} mavlink_depth_status_t;

#define MAVLINK_MSG_ID_DEPTH_STATUS_LEN 36
#define MAVLINK_MSG_ID_DEPTH_STATUS_MIN_LEN 36
#define MAVLINK_MSG_ID_7_LEN 36
#define MAVLINK_MSG_ID_7_MIN_LEN 36

#define MAVLINK_MSG_ID_DEPTH_STATUS_CRC 6
#define MAVLINK_MSG_ID_7_CRC 6

#define MAVLINK_MSG_DEPTH_STATUS_FIELD_DEPTH_LEN 4
#define MAVLINK_MSG_DEPTH_STATUS_FIELD_TEMP_LEN 4

#if MAVLINK_COMMAND_24BIT
#define MAVLINK_MESSAGE_INFO_DEPTH_STATUS { \
    7, \
    "DEPTH_STATUS", \
    3, \
    {  { "timestamp_ms", NULL, MAVLINK_TYPE_UINT32_T, 0, 0, offsetof(mavlink_depth_status_t, timestamp_ms) }, \
         { "depth", NULL, MAVLINK_TYPE_FLOAT, 4, 4, offsetof(mavlink_depth_status_t, depth) }, \
         { "temp", NULL, MAVLINK_TYPE_FLOAT, 4, 20, offsetof(mavlink_depth_status_t, temp) }, \
         } \
}
#else
#define MAVLINK_MESSAGE_INFO_DEPTH_STATUS { \
    "DEPTH_STATUS", \
    3, \
    {  { "timestamp_ms", NULL, MAVLINK_TYPE_UINT32_T, 0, 0, offsetof(mavlink_depth_status_t, timestamp_ms) }, \
         { "depth", NULL, MAVLINK_TYPE_FLOAT, 4, 4, offsetof(mavlink_depth_status_t, depth) }, \
         { "temp", NULL, MAVLINK_TYPE_FLOAT, 4, 20, offsetof(mavlink_depth_status_t, temp) }, \
         } \
}
#endif

/**
 * @brief Pack a depth_status message
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param msg The MAVLink message to compress the data into
 *
 * @param timestamp_ms [ms] Timestamp from the sender clock.
 * @param depth [m] Depth values.
 * @param temp [degC] Temperature values.
 * @return length of the message in bytes (excluding serial stream start sign)
 */
static inline uint16_t mavlink_msg_depth_status_pack(uint8_t system_id, uint8_t component_id, mavlink_message_t* msg,
                               uint32_t timestamp_ms, const float *depth, const float *temp)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    char buf[MAVLINK_MSG_ID_DEPTH_STATUS_LEN];
    _mav_put_uint32_t(buf, 0, timestamp_ms);
    _mav_put_float_array(buf, 4, depth, 4);
    _mav_put_float_array(buf, 20, temp, 4);
        memcpy(_MAV_PAYLOAD_NON_CONST(msg), buf, MAVLINK_MSG_ID_DEPTH_STATUS_LEN);
#else
    mavlink_depth_status_t packet;
    packet.timestamp_ms = timestamp_ms;
    mav_array_memcpy(packet.depth, depth, sizeof(float)*4);
    mav_array_memcpy(packet.temp, temp, sizeof(float)*4);
        memcpy(_MAV_PAYLOAD_NON_CONST(msg), &packet, MAVLINK_MSG_ID_DEPTH_STATUS_LEN);
#endif

    msg->msgid = MAVLINK_MSG_ID_DEPTH_STATUS;
    return mavlink_finalize_message(msg, system_id, component_id, MAVLINK_MSG_ID_DEPTH_STATUS_MIN_LEN, MAVLINK_MSG_ID_DEPTH_STATUS_LEN, MAVLINK_MSG_ID_DEPTH_STATUS_CRC);
}

/**
 * @brief Pack a depth_status message
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param status MAVLink status structure
 * @param msg The MAVLink message to compress the data into
 *
 * @param timestamp_ms [ms] Timestamp from the sender clock.
 * @param depth [m] Depth values.
 * @param temp [degC] Temperature values.
 * @return length of the message in bytes (excluding serial stream start sign)
 */
static inline uint16_t mavlink_msg_depth_status_pack_status(uint8_t system_id, uint8_t component_id, mavlink_status_t *_status, mavlink_message_t* msg,
                               uint32_t timestamp_ms, const float *depth, const float *temp)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    char buf[MAVLINK_MSG_ID_DEPTH_STATUS_LEN];
    _mav_put_uint32_t(buf, 0, timestamp_ms);
    _mav_put_float_array(buf, 4, depth, 4);
    _mav_put_float_array(buf, 20, temp, 4);
        memcpy(_MAV_PAYLOAD_NON_CONST(msg), buf, MAVLINK_MSG_ID_DEPTH_STATUS_LEN);
#else
    mavlink_depth_status_t packet;
    packet.timestamp_ms = timestamp_ms;
    mav_array_memcpy(packet.depth, depth, sizeof(float)*4);
    mav_array_memcpy(packet.temp, temp, sizeof(float)*4);
        memcpy(_MAV_PAYLOAD_NON_CONST(msg), &packet, MAVLINK_MSG_ID_DEPTH_STATUS_LEN);
#endif

    msg->msgid = MAVLINK_MSG_ID_DEPTH_STATUS;
#if MAVLINK_CRC_EXTRA
    return mavlink_finalize_message_buffer(msg, system_id, component_id, _status, MAVLINK_MSG_ID_DEPTH_STATUS_MIN_LEN, MAVLINK_MSG_ID_DEPTH_STATUS_LEN, MAVLINK_MSG_ID_DEPTH_STATUS_CRC);
#else
    return mavlink_finalize_message_buffer(msg, system_id, component_id, _status, MAVLINK_MSG_ID_DEPTH_STATUS_MIN_LEN, MAVLINK_MSG_ID_DEPTH_STATUS_LEN);
#endif
}

/**
 * @brief Pack a depth_status message on a channel
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param chan The MAVLink channel this message will be sent over
 * @param msg The MAVLink message to compress the data into
 * @param timestamp_ms [ms] Timestamp from the sender clock.
 * @param depth [m] Depth values.
 * @param temp [degC] Temperature values.
 * @return length of the message in bytes (excluding serial stream start sign)
 */
static inline uint16_t mavlink_msg_depth_status_pack_chan(uint8_t system_id, uint8_t component_id, uint8_t chan,
                               mavlink_message_t* msg,
                                   uint32_t timestamp_ms,const float *depth,const float *temp)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    char buf[MAVLINK_MSG_ID_DEPTH_STATUS_LEN];
    _mav_put_uint32_t(buf, 0, timestamp_ms);
    _mav_put_float_array(buf, 4, depth, 4);
    _mav_put_float_array(buf, 20, temp, 4);
        memcpy(_MAV_PAYLOAD_NON_CONST(msg), buf, MAVLINK_MSG_ID_DEPTH_STATUS_LEN);
#else
    mavlink_depth_status_t packet;
    packet.timestamp_ms = timestamp_ms;
    mav_array_memcpy(packet.depth, depth, sizeof(float)*4);
    mav_array_memcpy(packet.temp, temp, sizeof(float)*4);
        memcpy(_MAV_PAYLOAD_NON_CONST(msg), &packet, MAVLINK_MSG_ID_DEPTH_STATUS_LEN);
#endif

    msg->msgid = MAVLINK_MSG_ID_DEPTH_STATUS;
    return mavlink_finalize_message_chan(msg, system_id, component_id, chan, MAVLINK_MSG_ID_DEPTH_STATUS_MIN_LEN, MAVLINK_MSG_ID_DEPTH_STATUS_LEN, MAVLINK_MSG_ID_DEPTH_STATUS_CRC);
}

/**
 * @brief Encode a depth_status struct
 *
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param msg The MAVLink message to compress the data into
 * @param depth_status C-struct to read the message contents from
 */
static inline uint16_t mavlink_msg_depth_status_encode(uint8_t system_id, uint8_t component_id, mavlink_message_t* msg, const mavlink_depth_status_t* depth_status)
{
    return mavlink_msg_depth_status_pack(system_id, component_id, msg, depth_status->timestamp_ms, depth_status->depth, depth_status->temp);
}

/**
 * @brief Encode a depth_status struct on a channel
 *
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param chan The MAVLink channel this message will be sent over
 * @param msg The MAVLink message to compress the data into
 * @param depth_status C-struct to read the message contents from
 */
static inline uint16_t mavlink_msg_depth_status_encode_chan(uint8_t system_id, uint8_t component_id, uint8_t chan, mavlink_message_t* msg, const mavlink_depth_status_t* depth_status)
{
    return mavlink_msg_depth_status_pack_chan(system_id, component_id, chan, msg, depth_status->timestamp_ms, depth_status->depth, depth_status->temp);
}

/**
 * @brief Encode a depth_status struct with provided status structure
 *
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param status MAVLink status structure
 * @param msg The MAVLink message to compress the data into
 * @param depth_status C-struct to read the message contents from
 */
static inline uint16_t mavlink_msg_depth_status_encode_status(uint8_t system_id, uint8_t component_id, mavlink_status_t* _status, mavlink_message_t* msg, const mavlink_depth_status_t* depth_status)
{
    return mavlink_msg_depth_status_pack_status(system_id, component_id, _status, msg,  depth_status->timestamp_ms, depth_status->depth, depth_status->temp);
}

/**
 * @brief Send a depth_status message
 * @param chan MAVLink channel to send the message
 *
 * @param timestamp_ms [ms] Timestamp from the sender clock.
 * @param depth [m] Depth values.
 * @param temp [degC] Temperature values.
 */
#ifdef MAVLINK_USE_CONVENIENCE_FUNCTIONS

static inline void mavlink_msg_depth_status_send(mavlink_channel_t chan, uint32_t timestamp_ms, const float *depth, const float *temp)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    char buf[MAVLINK_MSG_ID_DEPTH_STATUS_LEN];
    _mav_put_uint32_t(buf, 0, timestamp_ms);
    _mav_put_float_array(buf, 4, depth, 4);
    _mav_put_float_array(buf, 20, temp, 4);
    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_DEPTH_STATUS, buf, MAVLINK_MSG_ID_DEPTH_STATUS_MIN_LEN, MAVLINK_MSG_ID_DEPTH_STATUS_LEN, MAVLINK_MSG_ID_DEPTH_STATUS_CRC);
#else
    mavlink_depth_status_t packet;
    packet.timestamp_ms = timestamp_ms;
    mav_array_memcpy(packet.depth, depth, sizeof(float)*4);
    mav_array_memcpy(packet.temp, temp, sizeof(float)*4);
    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_DEPTH_STATUS, (const char *)&packet, MAVLINK_MSG_ID_DEPTH_STATUS_MIN_LEN, MAVLINK_MSG_ID_DEPTH_STATUS_LEN, MAVLINK_MSG_ID_DEPTH_STATUS_CRC);
#endif
}

/**
 * @brief Send a depth_status message
 * @param chan MAVLink channel to send the message
 * @param struct The MAVLink struct to serialize
 */
static inline void mavlink_msg_depth_status_send_struct(mavlink_channel_t chan, const mavlink_depth_status_t* depth_status)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    mavlink_msg_depth_status_send(chan, depth_status->timestamp_ms, depth_status->depth, depth_status->temp);
#else
    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_DEPTH_STATUS, (const char *)depth_status, MAVLINK_MSG_ID_DEPTH_STATUS_MIN_LEN, MAVLINK_MSG_ID_DEPTH_STATUS_LEN, MAVLINK_MSG_ID_DEPTH_STATUS_CRC);
#endif
}

#if MAVLINK_MSG_ID_DEPTH_STATUS_LEN <= MAVLINK_MAX_PAYLOAD_LEN
/*
  This variant of _send() can be used to save stack space by reusing
  memory from the receive buffer.  The caller provides a
  mavlink_message_t which is the size of a full mavlink message. This
  is usually the receive buffer for the channel, and allows a reply to an
  incoming message with minimum stack space usage.
 */
static inline void mavlink_msg_depth_status_send_buf(mavlink_message_t *msgbuf, mavlink_channel_t chan,  uint32_t timestamp_ms, const float *depth, const float *temp)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    char *buf = (char *)msgbuf;
    _mav_put_uint32_t(buf, 0, timestamp_ms);
    _mav_put_float_array(buf, 4, depth, 4);
    _mav_put_float_array(buf, 20, temp, 4);
    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_DEPTH_STATUS, buf, MAVLINK_MSG_ID_DEPTH_STATUS_MIN_LEN, MAVLINK_MSG_ID_DEPTH_STATUS_LEN, MAVLINK_MSG_ID_DEPTH_STATUS_CRC);
#else
    mavlink_depth_status_t *packet = (mavlink_depth_status_t *)msgbuf;
    packet->timestamp_ms = timestamp_ms;
    mav_array_memcpy(packet->depth, depth, sizeof(float)*4);
    mav_array_memcpy(packet->temp, temp, sizeof(float)*4);
    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_DEPTH_STATUS, (const char *)packet, MAVLINK_MSG_ID_DEPTH_STATUS_MIN_LEN, MAVLINK_MSG_ID_DEPTH_STATUS_LEN, MAVLINK_MSG_ID_DEPTH_STATUS_CRC);
#endif
}
#endif

#endif

// MESSAGE DEPTH_STATUS UNPACKING


/**
 * @brief Get field timestamp_ms from depth_status message
 *
 * @return [ms] Timestamp from the sender clock.
 */
static inline uint32_t mavlink_msg_depth_status_get_timestamp_ms(const mavlink_message_t* msg)
{
    return _MAV_RETURN_uint32_t(msg,  0);
}

/**
 * @brief Get field depth from depth_status message
 *
 * @return [m] Depth values.
 */
static inline uint16_t mavlink_msg_depth_status_get_depth(const mavlink_message_t* msg, float *depth)
{
    return _MAV_RETURN_float_array(msg, depth, 4,  4);
}

/**
 * @brief Get field temp from depth_status message
 *
 * @return [degC] Temperature values.
 */
static inline uint16_t mavlink_msg_depth_status_get_temp(const mavlink_message_t* msg, float *temp)
{
    return _MAV_RETURN_float_array(msg, temp, 4,  20);
}

/**
 * @brief Decode a depth_status message into a struct
 *
 * @param msg The message to decode
 * @param depth_status C-struct to decode the message contents into
 */
static inline void mavlink_msg_depth_status_decode(const mavlink_message_t* msg, mavlink_depth_status_t* depth_status)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    depth_status->timestamp_ms = mavlink_msg_depth_status_get_timestamp_ms(msg);
    mavlink_msg_depth_status_get_depth(msg, depth_status->depth);
    mavlink_msg_depth_status_get_temp(msg, depth_status->temp);
#else
        uint8_t len = msg->len < MAVLINK_MSG_ID_DEPTH_STATUS_LEN? msg->len : MAVLINK_MSG_ID_DEPTH_STATUS_LEN;
        memset(depth_status, 0, MAVLINK_MSG_ID_DEPTH_STATUS_LEN);
    memcpy(depth_status, _MAV_PAYLOAD(msg), len);
#endif
}
