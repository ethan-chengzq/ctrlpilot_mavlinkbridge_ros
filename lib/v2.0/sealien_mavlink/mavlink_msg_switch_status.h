#pragma once
// MESSAGE SWITCH_STATUS PACKING

#define MAVLINK_MSG_ID_SWITCH_STATUS 9


typedef struct __mavlink_switch_status_t {
 uint32_t timestamp_ms; /*< [ms] Timestamp from the sender clock.*/
 uint8_t switchs[8]; /*<  Relay states: 0 no power, 1 powered.*/
} mavlink_switch_status_t;

#define MAVLINK_MSG_ID_SWITCH_STATUS_LEN 12
#define MAVLINK_MSG_ID_SWITCH_STATUS_MIN_LEN 12
#define MAVLINK_MSG_ID_9_LEN 12
#define MAVLINK_MSG_ID_9_MIN_LEN 12

#define MAVLINK_MSG_ID_SWITCH_STATUS_CRC 142
#define MAVLINK_MSG_ID_9_CRC 142

#define MAVLINK_MSG_SWITCH_STATUS_FIELD_SWITCHS_LEN 8

#if MAVLINK_COMMAND_24BIT
#define MAVLINK_MESSAGE_INFO_SWITCH_STATUS { \
    9, \
    "SWITCH_STATUS", \
    2, \
    {  { "timestamp_ms", NULL, MAVLINK_TYPE_UINT32_T, 0, 0, offsetof(mavlink_switch_status_t, timestamp_ms) }, \
         { "switchs", NULL, MAVLINK_TYPE_UINT8_T, 8, 4, offsetof(mavlink_switch_status_t, switchs) }, \
         } \
}
#else
#define MAVLINK_MESSAGE_INFO_SWITCH_STATUS { \
    "SWITCH_STATUS", \
    2, \
    {  { "timestamp_ms", NULL, MAVLINK_TYPE_UINT32_T, 0, 0, offsetof(mavlink_switch_status_t, timestamp_ms) }, \
         { "switchs", NULL, MAVLINK_TYPE_UINT8_T, 8, 4, offsetof(mavlink_switch_status_t, switchs) }, \
         } \
}
#endif

/**
 * @brief Pack a switch_status message
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param msg The MAVLink message to compress the data into
 *
 * @param timestamp_ms [ms] Timestamp from the sender clock.
 * @param switchs  Relay states: 0 no power, 1 powered.
 * @return length of the message in bytes (excluding serial stream start sign)
 */
static inline uint16_t mavlink_msg_switch_status_pack(uint8_t system_id, uint8_t component_id, mavlink_message_t* msg,
                               uint32_t timestamp_ms, const uint8_t *switchs)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    char buf[MAVLINK_MSG_ID_SWITCH_STATUS_LEN];
    _mav_put_uint32_t(buf, 0, timestamp_ms);
    _mav_put_uint8_t_array(buf, 4, switchs, 8);
        memcpy(_MAV_PAYLOAD_NON_CONST(msg), buf, MAVLINK_MSG_ID_SWITCH_STATUS_LEN);
#else
    mavlink_switch_status_t packet;
    packet.timestamp_ms = timestamp_ms;
    mav_array_memcpy(packet.switchs, switchs, sizeof(uint8_t)*8);
        memcpy(_MAV_PAYLOAD_NON_CONST(msg), &packet, MAVLINK_MSG_ID_SWITCH_STATUS_LEN);
#endif

    msg->msgid = MAVLINK_MSG_ID_SWITCH_STATUS;
    return mavlink_finalize_message(msg, system_id, component_id, MAVLINK_MSG_ID_SWITCH_STATUS_MIN_LEN, MAVLINK_MSG_ID_SWITCH_STATUS_LEN, MAVLINK_MSG_ID_SWITCH_STATUS_CRC);
}

/**
 * @brief Pack a switch_status message
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param status MAVLink status structure
 * @param msg The MAVLink message to compress the data into
 *
 * @param timestamp_ms [ms] Timestamp from the sender clock.
 * @param switchs  Relay states: 0 no power, 1 powered.
 * @return length of the message in bytes (excluding serial stream start sign)
 */
static inline uint16_t mavlink_msg_switch_status_pack_status(uint8_t system_id, uint8_t component_id, mavlink_status_t *_status, mavlink_message_t* msg,
                               uint32_t timestamp_ms, const uint8_t *switchs)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    char buf[MAVLINK_MSG_ID_SWITCH_STATUS_LEN];
    _mav_put_uint32_t(buf, 0, timestamp_ms);
    _mav_put_uint8_t_array(buf, 4, switchs, 8);
        memcpy(_MAV_PAYLOAD_NON_CONST(msg), buf, MAVLINK_MSG_ID_SWITCH_STATUS_LEN);
#else
    mavlink_switch_status_t packet;
    packet.timestamp_ms = timestamp_ms;
    mav_array_memcpy(packet.switchs, switchs, sizeof(uint8_t)*8);
        memcpy(_MAV_PAYLOAD_NON_CONST(msg), &packet, MAVLINK_MSG_ID_SWITCH_STATUS_LEN);
#endif

    msg->msgid = MAVLINK_MSG_ID_SWITCH_STATUS;
#if MAVLINK_CRC_EXTRA
    return mavlink_finalize_message_buffer(msg, system_id, component_id, _status, MAVLINK_MSG_ID_SWITCH_STATUS_MIN_LEN, MAVLINK_MSG_ID_SWITCH_STATUS_LEN, MAVLINK_MSG_ID_SWITCH_STATUS_CRC);
#else
    return mavlink_finalize_message_buffer(msg, system_id, component_id, _status, MAVLINK_MSG_ID_SWITCH_STATUS_MIN_LEN, MAVLINK_MSG_ID_SWITCH_STATUS_LEN);
#endif
}

/**
 * @brief Pack a switch_status message on a channel
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param chan The MAVLink channel this message will be sent over
 * @param msg The MAVLink message to compress the data into
 * @param timestamp_ms [ms] Timestamp from the sender clock.
 * @param switchs  Relay states: 0 no power, 1 powered.
 * @return length of the message in bytes (excluding serial stream start sign)
 */
static inline uint16_t mavlink_msg_switch_status_pack_chan(uint8_t system_id, uint8_t component_id, uint8_t chan,
                               mavlink_message_t* msg,
                                   uint32_t timestamp_ms,const uint8_t *switchs)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    char buf[MAVLINK_MSG_ID_SWITCH_STATUS_LEN];
    _mav_put_uint32_t(buf, 0, timestamp_ms);
    _mav_put_uint8_t_array(buf, 4, switchs, 8);
        memcpy(_MAV_PAYLOAD_NON_CONST(msg), buf, MAVLINK_MSG_ID_SWITCH_STATUS_LEN);
#else
    mavlink_switch_status_t packet;
    packet.timestamp_ms = timestamp_ms;
    mav_array_memcpy(packet.switchs, switchs, sizeof(uint8_t)*8);
        memcpy(_MAV_PAYLOAD_NON_CONST(msg), &packet, MAVLINK_MSG_ID_SWITCH_STATUS_LEN);
#endif

    msg->msgid = MAVLINK_MSG_ID_SWITCH_STATUS;
    return mavlink_finalize_message_chan(msg, system_id, component_id, chan, MAVLINK_MSG_ID_SWITCH_STATUS_MIN_LEN, MAVLINK_MSG_ID_SWITCH_STATUS_LEN, MAVLINK_MSG_ID_SWITCH_STATUS_CRC);
}

/**
 * @brief Encode a switch_status struct
 *
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param msg The MAVLink message to compress the data into
 * @param switch_status C-struct to read the message contents from
 */
static inline uint16_t mavlink_msg_switch_status_encode(uint8_t system_id, uint8_t component_id, mavlink_message_t* msg, const mavlink_switch_status_t* switch_status)
{
    return mavlink_msg_switch_status_pack(system_id, component_id, msg, switch_status->timestamp_ms, switch_status->switchs);
}

/**
 * @brief Encode a switch_status struct on a channel
 *
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param chan The MAVLink channel this message will be sent over
 * @param msg The MAVLink message to compress the data into
 * @param switch_status C-struct to read the message contents from
 */
static inline uint16_t mavlink_msg_switch_status_encode_chan(uint8_t system_id, uint8_t component_id, uint8_t chan, mavlink_message_t* msg, const mavlink_switch_status_t* switch_status)
{
    return mavlink_msg_switch_status_pack_chan(system_id, component_id, chan, msg, switch_status->timestamp_ms, switch_status->switchs);
}

/**
 * @brief Encode a switch_status struct with provided status structure
 *
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param status MAVLink status structure
 * @param msg The MAVLink message to compress the data into
 * @param switch_status C-struct to read the message contents from
 */
static inline uint16_t mavlink_msg_switch_status_encode_status(uint8_t system_id, uint8_t component_id, mavlink_status_t* _status, mavlink_message_t* msg, const mavlink_switch_status_t* switch_status)
{
    return mavlink_msg_switch_status_pack_status(system_id, component_id, _status, msg,  switch_status->timestamp_ms, switch_status->switchs);
}

/**
 * @brief Send a switch_status message
 * @param chan MAVLink channel to send the message
 *
 * @param timestamp_ms [ms] Timestamp from the sender clock.
 * @param switchs  Relay states: 0 no power, 1 powered.
 */
#ifdef MAVLINK_USE_CONVENIENCE_FUNCTIONS

static inline void mavlink_msg_switch_status_send(mavlink_channel_t chan, uint32_t timestamp_ms, const uint8_t *switchs)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    char buf[MAVLINK_MSG_ID_SWITCH_STATUS_LEN];
    _mav_put_uint32_t(buf, 0, timestamp_ms);
    _mav_put_uint8_t_array(buf, 4, switchs, 8);
    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_SWITCH_STATUS, buf, MAVLINK_MSG_ID_SWITCH_STATUS_MIN_LEN, MAVLINK_MSG_ID_SWITCH_STATUS_LEN, MAVLINK_MSG_ID_SWITCH_STATUS_CRC);
#else
    mavlink_switch_status_t packet;
    packet.timestamp_ms = timestamp_ms;
    mav_array_memcpy(packet.switchs, switchs, sizeof(uint8_t)*8);
    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_SWITCH_STATUS, (const char *)&packet, MAVLINK_MSG_ID_SWITCH_STATUS_MIN_LEN, MAVLINK_MSG_ID_SWITCH_STATUS_LEN, MAVLINK_MSG_ID_SWITCH_STATUS_CRC);
#endif
}

/**
 * @brief Send a switch_status message
 * @param chan MAVLink channel to send the message
 * @param struct The MAVLink struct to serialize
 */
static inline void mavlink_msg_switch_status_send_struct(mavlink_channel_t chan, const mavlink_switch_status_t* switch_status)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    mavlink_msg_switch_status_send(chan, switch_status->timestamp_ms, switch_status->switchs);
#else
    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_SWITCH_STATUS, (const char *)switch_status, MAVLINK_MSG_ID_SWITCH_STATUS_MIN_LEN, MAVLINK_MSG_ID_SWITCH_STATUS_LEN, MAVLINK_MSG_ID_SWITCH_STATUS_CRC);
#endif
}

#if MAVLINK_MSG_ID_SWITCH_STATUS_LEN <= MAVLINK_MAX_PAYLOAD_LEN
/*
  This variant of _send() can be used to save stack space by reusing
  memory from the receive buffer.  The caller provides a
  mavlink_message_t which is the size of a full mavlink message. This
  is usually the receive buffer for the channel, and allows a reply to an
  incoming message with minimum stack space usage.
 */
static inline void mavlink_msg_switch_status_send_buf(mavlink_message_t *msgbuf, mavlink_channel_t chan,  uint32_t timestamp_ms, const uint8_t *switchs)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    char *buf = (char *)msgbuf;
    _mav_put_uint32_t(buf, 0, timestamp_ms);
    _mav_put_uint8_t_array(buf, 4, switchs, 8);
    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_SWITCH_STATUS, buf, MAVLINK_MSG_ID_SWITCH_STATUS_MIN_LEN, MAVLINK_MSG_ID_SWITCH_STATUS_LEN, MAVLINK_MSG_ID_SWITCH_STATUS_CRC);
#else
    mavlink_switch_status_t *packet = (mavlink_switch_status_t *)msgbuf;
    packet->timestamp_ms = timestamp_ms;
    mav_array_memcpy(packet->switchs, switchs, sizeof(uint8_t)*8);
    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_SWITCH_STATUS, (const char *)packet, MAVLINK_MSG_ID_SWITCH_STATUS_MIN_LEN, MAVLINK_MSG_ID_SWITCH_STATUS_LEN, MAVLINK_MSG_ID_SWITCH_STATUS_CRC);
#endif
}
#endif

#endif

// MESSAGE SWITCH_STATUS UNPACKING


/**
 * @brief Get field timestamp_ms from switch_status message
 *
 * @return [ms] Timestamp from the sender clock.
 */
static inline uint32_t mavlink_msg_switch_status_get_timestamp_ms(const mavlink_message_t* msg)
{
    return _MAV_RETURN_uint32_t(msg,  0);
}

/**
 * @brief Get field switchs from switch_status message
 *
 * @return  Relay states: 0 no power, 1 powered.
 */
static inline uint16_t mavlink_msg_switch_status_get_switchs(const mavlink_message_t* msg, uint8_t *switchs)
{
    return _MAV_RETURN_uint8_t_array(msg, switchs, 8,  4);
}

/**
 * @brief Decode a switch_status message into a struct
 *
 * @param msg The message to decode
 * @param switch_status C-struct to decode the message contents into
 */
static inline void mavlink_msg_switch_status_decode(const mavlink_message_t* msg, mavlink_switch_status_t* switch_status)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    switch_status->timestamp_ms = mavlink_msg_switch_status_get_timestamp_ms(msg);
    mavlink_msg_switch_status_get_switchs(msg, switch_status->switchs);
#else
        uint8_t len = msg->len < MAVLINK_MSG_ID_SWITCH_STATUS_LEN? msg->len : MAVLINK_MSG_ID_SWITCH_STATUS_LEN;
        memset(switch_status, 0, MAVLINK_MSG_ID_SWITCH_STATUS_LEN);
    memcpy(switch_status, _MAV_PAYLOAD(msg), len);
#endif
}
