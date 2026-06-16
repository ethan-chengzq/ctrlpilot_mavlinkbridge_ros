#pragma once
// MESSAGE VCHECK PACKING

#define MAVLINK_MSG_ID_VCHECK 5


typedef struct __mavlink_vcheck_t {
 uint32_t timestamp_ms; /*< [ms] Timestamp from the sender clock.*/
 int16_t temp[4]; /*< [degC] Temperature detection data for four channels.*/
 uint8_t v_status[4]; /*<  Water ingress detection state for four channels.*/
} mavlink_vcheck_t;

#define MAVLINK_MSG_ID_VCHECK_LEN 16
#define MAVLINK_MSG_ID_VCHECK_MIN_LEN 16
#define MAVLINK_MSG_ID_5_LEN 16
#define MAVLINK_MSG_ID_5_MIN_LEN 16

#define MAVLINK_MSG_ID_VCHECK_CRC 119
#define MAVLINK_MSG_ID_5_CRC 119

#define MAVLINK_MSG_VCHECK_FIELD_TEMP_LEN 4
#define MAVLINK_MSG_VCHECK_FIELD_V_STATUS_LEN 4

#if MAVLINK_COMMAND_24BIT
#define MAVLINK_MESSAGE_INFO_VCHECK { \
    5, \
    "VCHECK", \
    3, \
    {  { "timestamp_ms", NULL, MAVLINK_TYPE_UINT32_T, 0, 0, offsetof(mavlink_vcheck_t, timestamp_ms) }, \
         { "v_status", NULL, MAVLINK_TYPE_UINT8_T, 4, 12, offsetof(mavlink_vcheck_t, v_status) }, \
         { "temp", NULL, MAVLINK_TYPE_INT16_T, 4, 4, offsetof(mavlink_vcheck_t, temp) }, \
         } \
}
#else
#define MAVLINK_MESSAGE_INFO_VCHECK { \
    "VCHECK", \
    3, \
    {  { "timestamp_ms", NULL, MAVLINK_TYPE_UINT32_T, 0, 0, offsetof(mavlink_vcheck_t, timestamp_ms) }, \
         { "v_status", NULL, MAVLINK_TYPE_UINT8_T, 4, 12, offsetof(mavlink_vcheck_t, v_status) }, \
         { "temp", NULL, MAVLINK_TYPE_INT16_T, 4, 4, offsetof(mavlink_vcheck_t, temp) }, \
         } \
}
#endif

/**
 * @brief Pack a vcheck message
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param msg The MAVLink message to compress the data into
 *
 * @param timestamp_ms [ms] Timestamp from the sender clock.
 * @param v_status  Water ingress detection state for four channels.
 * @param temp [degC] Temperature detection data for four channels.
 * @return length of the message in bytes (excluding serial stream start sign)
 */
static inline uint16_t mavlink_msg_vcheck_pack(uint8_t system_id, uint8_t component_id, mavlink_message_t* msg,
                               uint32_t timestamp_ms, const uint8_t *v_status, const int16_t *temp)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    char buf[MAVLINK_MSG_ID_VCHECK_LEN];
    _mav_put_uint32_t(buf, 0, timestamp_ms);
    _mav_put_int16_t_array(buf, 4, temp, 4);
    _mav_put_uint8_t_array(buf, 12, v_status, 4);
        memcpy(_MAV_PAYLOAD_NON_CONST(msg), buf, MAVLINK_MSG_ID_VCHECK_LEN);
#else
    mavlink_vcheck_t packet;
    packet.timestamp_ms = timestamp_ms;
    mav_array_memcpy(packet.temp, temp, sizeof(int16_t)*4);
    mav_array_memcpy(packet.v_status, v_status, sizeof(uint8_t)*4);
        memcpy(_MAV_PAYLOAD_NON_CONST(msg), &packet, MAVLINK_MSG_ID_VCHECK_LEN);
#endif

    msg->msgid = MAVLINK_MSG_ID_VCHECK;
    return mavlink_finalize_message(msg, system_id, component_id, MAVLINK_MSG_ID_VCHECK_MIN_LEN, MAVLINK_MSG_ID_VCHECK_LEN, MAVLINK_MSG_ID_VCHECK_CRC);
}

/**
 * @brief Pack a vcheck message
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param status MAVLink status structure
 * @param msg The MAVLink message to compress the data into
 *
 * @param timestamp_ms [ms] Timestamp from the sender clock.
 * @param v_status  Water ingress detection state for four channels.
 * @param temp [degC] Temperature detection data for four channels.
 * @return length of the message in bytes (excluding serial stream start sign)
 */
static inline uint16_t mavlink_msg_vcheck_pack_status(uint8_t system_id, uint8_t component_id, mavlink_status_t *_status, mavlink_message_t* msg,
                               uint32_t timestamp_ms, const uint8_t *v_status, const int16_t *temp)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    char buf[MAVLINK_MSG_ID_VCHECK_LEN];
    _mav_put_uint32_t(buf, 0, timestamp_ms);
    _mav_put_int16_t_array(buf, 4, temp, 4);
    _mav_put_uint8_t_array(buf, 12, v_status, 4);
        memcpy(_MAV_PAYLOAD_NON_CONST(msg), buf, MAVLINK_MSG_ID_VCHECK_LEN);
#else
    mavlink_vcheck_t packet;
    packet.timestamp_ms = timestamp_ms;
    mav_array_memcpy(packet.temp, temp, sizeof(int16_t)*4);
    mav_array_memcpy(packet.v_status, v_status, sizeof(uint8_t)*4);
        memcpy(_MAV_PAYLOAD_NON_CONST(msg), &packet, MAVLINK_MSG_ID_VCHECK_LEN);
#endif

    msg->msgid = MAVLINK_MSG_ID_VCHECK;
#if MAVLINK_CRC_EXTRA
    return mavlink_finalize_message_buffer(msg, system_id, component_id, _status, MAVLINK_MSG_ID_VCHECK_MIN_LEN, MAVLINK_MSG_ID_VCHECK_LEN, MAVLINK_MSG_ID_VCHECK_CRC);
#else
    return mavlink_finalize_message_buffer(msg, system_id, component_id, _status, MAVLINK_MSG_ID_VCHECK_MIN_LEN, MAVLINK_MSG_ID_VCHECK_LEN);
#endif
}

/**
 * @brief Pack a vcheck message on a channel
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param chan The MAVLink channel this message will be sent over
 * @param msg The MAVLink message to compress the data into
 * @param timestamp_ms [ms] Timestamp from the sender clock.
 * @param v_status  Water ingress detection state for four channels.
 * @param temp [degC] Temperature detection data for four channels.
 * @return length of the message in bytes (excluding serial stream start sign)
 */
static inline uint16_t mavlink_msg_vcheck_pack_chan(uint8_t system_id, uint8_t component_id, uint8_t chan,
                               mavlink_message_t* msg,
                                   uint32_t timestamp_ms,const uint8_t *v_status,const int16_t *temp)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    char buf[MAVLINK_MSG_ID_VCHECK_LEN];
    _mav_put_uint32_t(buf, 0, timestamp_ms);
    _mav_put_int16_t_array(buf, 4, temp, 4);
    _mav_put_uint8_t_array(buf, 12, v_status, 4);
        memcpy(_MAV_PAYLOAD_NON_CONST(msg), buf, MAVLINK_MSG_ID_VCHECK_LEN);
#else
    mavlink_vcheck_t packet;
    packet.timestamp_ms = timestamp_ms;
    mav_array_memcpy(packet.temp, temp, sizeof(int16_t)*4);
    mav_array_memcpy(packet.v_status, v_status, sizeof(uint8_t)*4);
        memcpy(_MAV_PAYLOAD_NON_CONST(msg), &packet, MAVLINK_MSG_ID_VCHECK_LEN);
#endif

    msg->msgid = MAVLINK_MSG_ID_VCHECK;
    return mavlink_finalize_message_chan(msg, system_id, component_id, chan, MAVLINK_MSG_ID_VCHECK_MIN_LEN, MAVLINK_MSG_ID_VCHECK_LEN, MAVLINK_MSG_ID_VCHECK_CRC);
}

/**
 * @brief Encode a vcheck struct
 *
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param msg The MAVLink message to compress the data into
 * @param vcheck C-struct to read the message contents from
 */
static inline uint16_t mavlink_msg_vcheck_encode(uint8_t system_id, uint8_t component_id, mavlink_message_t* msg, const mavlink_vcheck_t* vcheck)
{
    return mavlink_msg_vcheck_pack(system_id, component_id, msg, vcheck->timestamp_ms, vcheck->v_status, vcheck->temp);
}

/**
 * @brief Encode a vcheck struct on a channel
 *
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param chan The MAVLink channel this message will be sent over
 * @param msg The MAVLink message to compress the data into
 * @param vcheck C-struct to read the message contents from
 */
static inline uint16_t mavlink_msg_vcheck_encode_chan(uint8_t system_id, uint8_t component_id, uint8_t chan, mavlink_message_t* msg, const mavlink_vcheck_t* vcheck)
{
    return mavlink_msg_vcheck_pack_chan(system_id, component_id, chan, msg, vcheck->timestamp_ms, vcheck->v_status, vcheck->temp);
}

/**
 * @brief Encode a vcheck struct with provided status structure
 *
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param status MAVLink status structure
 * @param msg The MAVLink message to compress the data into
 * @param vcheck C-struct to read the message contents from
 */
static inline uint16_t mavlink_msg_vcheck_encode_status(uint8_t system_id, uint8_t component_id, mavlink_status_t* _status, mavlink_message_t* msg, const mavlink_vcheck_t* vcheck)
{
    return mavlink_msg_vcheck_pack_status(system_id, component_id, _status, msg,  vcheck->timestamp_ms, vcheck->v_status, vcheck->temp);
}

/**
 * @brief Send a vcheck message
 * @param chan MAVLink channel to send the message
 *
 * @param timestamp_ms [ms] Timestamp from the sender clock.
 * @param v_status  Water ingress detection state for four channels.
 * @param temp [degC] Temperature detection data for four channels.
 */
#ifdef MAVLINK_USE_CONVENIENCE_FUNCTIONS

static inline void mavlink_msg_vcheck_send(mavlink_channel_t chan, uint32_t timestamp_ms, const uint8_t *v_status, const int16_t *temp)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    char buf[MAVLINK_MSG_ID_VCHECK_LEN];
    _mav_put_uint32_t(buf, 0, timestamp_ms);
    _mav_put_int16_t_array(buf, 4, temp, 4);
    _mav_put_uint8_t_array(buf, 12, v_status, 4);
    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_VCHECK, buf, MAVLINK_MSG_ID_VCHECK_MIN_LEN, MAVLINK_MSG_ID_VCHECK_LEN, MAVLINK_MSG_ID_VCHECK_CRC);
#else
    mavlink_vcheck_t packet;
    packet.timestamp_ms = timestamp_ms;
    mav_array_memcpy(packet.temp, temp, sizeof(int16_t)*4);
    mav_array_memcpy(packet.v_status, v_status, sizeof(uint8_t)*4);
    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_VCHECK, (const char *)&packet, MAVLINK_MSG_ID_VCHECK_MIN_LEN, MAVLINK_MSG_ID_VCHECK_LEN, MAVLINK_MSG_ID_VCHECK_CRC);
#endif
}

/**
 * @brief Send a vcheck message
 * @param chan MAVLink channel to send the message
 * @param struct The MAVLink struct to serialize
 */
static inline void mavlink_msg_vcheck_send_struct(mavlink_channel_t chan, const mavlink_vcheck_t* vcheck)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    mavlink_msg_vcheck_send(chan, vcheck->timestamp_ms, vcheck->v_status, vcheck->temp);
#else
    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_VCHECK, (const char *)vcheck, MAVLINK_MSG_ID_VCHECK_MIN_LEN, MAVLINK_MSG_ID_VCHECK_LEN, MAVLINK_MSG_ID_VCHECK_CRC);
#endif
}

#if MAVLINK_MSG_ID_VCHECK_LEN <= MAVLINK_MAX_PAYLOAD_LEN
/*
  This variant of _send() can be used to save stack space by reusing
  memory from the receive buffer.  The caller provides a
  mavlink_message_t which is the size of a full mavlink message. This
  is usually the receive buffer for the channel, and allows a reply to an
  incoming message with minimum stack space usage.
 */
static inline void mavlink_msg_vcheck_send_buf(mavlink_message_t *msgbuf, mavlink_channel_t chan,  uint32_t timestamp_ms, const uint8_t *v_status, const int16_t *temp)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    char *buf = (char *)msgbuf;
    _mav_put_uint32_t(buf, 0, timestamp_ms);
    _mav_put_int16_t_array(buf, 4, temp, 4);
    _mav_put_uint8_t_array(buf, 12, v_status, 4);
    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_VCHECK, buf, MAVLINK_MSG_ID_VCHECK_MIN_LEN, MAVLINK_MSG_ID_VCHECK_LEN, MAVLINK_MSG_ID_VCHECK_CRC);
#else
    mavlink_vcheck_t *packet = (mavlink_vcheck_t *)msgbuf;
    packet->timestamp_ms = timestamp_ms;
    mav_array_memcpy(packet->temp, temp, sizeof(int16_t)*4);
    mav_array_memcpy(packet->v_status, v_status, sizeof(uint8_t)*4);
    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_VCHECK, (const char *)packet, MAVLINK_MSG_ID_VCHECK_MIN_LEN, MAVLINK_MSG_ID_VCHECK_LEN, MAVLINK_MSG_ID_VCHECK_CRC);
#endif
}
#endif

#endif

// MESSAGE VCHECK UNPACKING


/**
 * @brief Get field timestamp_ms from vcheck message
 *
 * @return [ms] Timestamp from the sender clock.
 */
static inline uint32_t mavlink_msg_vcheck_get_timestamp_ms(const mavlink_message_t* msg)
{
    return _MAV_RETURN_uint32_t(msg,  0);
}

/**
 * @brief Get field v_status from vcheck message
 *
 * @return  Water ingress detection state for four channels.
 */
static inline uint16_t mavlink_msg_vcheck_get_v_status(const mavlink_message_t* msg, uint8_t *v_status)
{
    return _MAV_RETURN_uint8_t_array(msg, v_status, 4,  12);
}

/**
 * @brief Get field temp from vcheck message
 *
 * @return [degC] Temperature detection data for four channels.
 */
static inline uint16_t mavlink_msg_vcheck_get_temp(const mavlink_message_t* msg, int16_t *temp)
{
    return _MAV_RETURN_int16_t_array(msg, temp, 4,  4);
}

/**
 * @brief Decode a vcheck message into a struct
 *
 * @param msg The message to decode
 * @param vcheck C-struct to decode the message contents into
 */
static inline void mavlink_msg_vcheck_decode(const mavlink_message_t* msg, mavlink_vcheck_t* vcheck)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    vcheck->timestamp_ms = mavlink_msg_vcheck_get_timestamp_ms(msg);
    mavlink_msg_vcheck_get_temp(msg, vcheck->temp);
    mavlink_msg_vcheck_get_v_status(msg, vcheck->v_status);
#else
        uint8_t len = msg->len < MAVLINK_MSG_ID_VCHECK_LEN? msg->len : MAVLINK_MSG_ID_VCHECK_LEN;
        memset(vcheck, 0, MAVLINK_MSG_ID_VCHECK_LEN);
    memcpy(vcheck, _MAV_PAYLOAD(msg), len);
#endif
}
