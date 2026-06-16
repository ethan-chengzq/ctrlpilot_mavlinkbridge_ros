#pragma once
// MESSAGE SWITCH_CMD PACKING

#define MAVLINK_MSG_ID_SWITCH_CMD 17


typedef struct __mavlink_switch_cmd_t {
 uint8_t index; /*<  Relay index, valid range 0-7.*/
 uint8_t value; /*<  Relay command value from protocol table: 0 ON, 1 OFF.*/
} mavlink_switch_cmd_t;

#define MAVLINK_MSG_ID_SWITCH_CMD_LEN 2
#define MAVLINK_MSG_ID_SWITCH_CMD_MIN_LEN 2
#define MAVLINK_MSG_ID_17_LEN 2
#define MAVLINK_MSG_ID_17_MIN_LEN 2

#define MAVLINK_MSG_ID_SWITCH_CMD_CRC 67
#define MAVLINK_MSG_ID_17_CRC 67



#if MAVLINK_COMMAND_24BIT
#define MAVLINK_MESSAGE_INFO_SWITCH_CMD { \
    17, \
    "SWITCH_CMD", \
    2, \
    {  { "index", NULL, MAVLINK_TYPE_UINT8_T, 0, 0, offsetof(mavlink_switch_cmd_t, index) }, \
         { "value", NULL, MAVLINK_TYPE_UINT8_T, 0, 1, offsetof(mavlink_switch_cmd_t, value) }, \
         } \
}
#else
#define MAVLINK_MESSAGE_INFO_SWITCH_CMD { \
    "SWITCH_CMD", \
    2, \
    {  { "index", NULL, MAVLINK_TYPE_UINT8_T, 0, 0, offsetof(mavlink_switch_cmd_t, index) }, \
         { "value", NULL, MAVLINK_TYPE_UINT8_T, 0, 1, offsetof(mavlink_switch_cmd_t, value) }, \
         } \
}
#endif

/**
 * @brief Pack a switch_cmd message
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param msg The MAVLink message to compress the data into
 *
 * @param index  Relay index, valid range 0-7.
 * @param value  Relay command value from protocol table: 0 ON, 1 OFF.
 * @return length of the message in bytes (excluding serial stream start sign)
 */
static inline uint16_t mavlink_msg_switch_cmd_pack(uint8_t system_id, uint8_t component_id, mavlink_message_t* msg,
                               uint8_t index, uint8_t value)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    char buf[MAVLINK_MSG_ID_SWITCH_CMD_LEN];
    _mav_put_uint8_t(buf, 0, index);
    _mav_put_uint8_t(buf, 1, value);

        memcpy(_MAV_PAYLOAD_NON_CONST(msg), buf, MAVLINK_MSG_ID_SWITCH_CMD_LEN);
#else
    mavlink_switch_cmd_t packet;
    packet.index = index;
    packet.value = value;

        memcpy(_MAV_PAYLOAD_NON_CONST(msg), &packet, MAVLINK_MSG_ID_SWITCH_CMD_LEN);
#endif

    msg->msgid = MAVLINK_MSG_ID_SWITCH_CMD;
    return mavlink_finalize_message(msg, system_id, component_id, MAVLINK_MSG_ID_SWITCH_CMD_MIN_LEN, MAVLINK_MSG_ID_SWITCH_CMD_LEN, MAVLINK_MSG_ID_SWITCH_CMD_CRC);
}

/**
 * @brief Pack a switch_cmd message
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param status MAVLink status structure
 * @param msg The MAVLink message to compress the data into
 *
 * @param index  Relay index, valid range 0-7.
 * @param value  Relay command value from protocol table: 0 ON, 1 OFF.
 * @return length of the message in bytes (excluding serial stream start sign)
 */
static inline uint16_t mavlink_msg_switch_cmd_pack_status(uint8_t system_id, uint8_t component_id, mavlink_status_t *_status, mavlink_message_t* msg,
                               uint8_t index, uint8_t value)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    char buf[MAVLINK_MSG_ID_SWITCH_CMD_LEN];
    _mav_put_uint8_t(buf, 0, index);
    _mav_put_uint8_t(buf, 1, value);

        memcpy(_MAV_PAYLOAD_NON_CONST(msg), buf, MAVLINK_MSG_ID_SWITCH_CMD_LEN);
#else
    mavlink_switch_cmd_t packet;
    packet.index = index;
    packet.value = value;

        memcpy(_MAV_PAYLOAD_NON_CONST(msg), &packet, MAVLINK_MSG_ID_SWITCH_CMD_LEN);
#endif

    msg->msgid = MAVLINK_MSG_ID_SWITCH_CMD;
#if MAVLINK_CRC_EXTRA
    return mavlink_finalize_message_buffer(msg, system_id, component_id, _status, MAVLINK_MSG_ID_SWITCH_CMD_MIN_LEN, MAVLINK_MSG_ID_SWITCH_CMD_LEN, MAVLINK_MSG_ID_SWITCH_CMD_CRC);
#else
    return mavlink_finalize_message_buffer(msg, system_id, component_id, _status, MAVLINK_MSG_ID_SWITCH_CMD_MIN_LEN, MAVLINK_MSG_ID_SWITCH_CMD_LEN);
#endif
}

/**
 * @brief Pack a switch_cmd message on a channel
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param chan The MAVLink channel this message will be sent over
 * @param msg The MAVLink message to compress the data into
 * @param index  Relay index, valid range 0-7.
 * @param value  Relay command value from protocol table: 0 ON, 1 OFF.
 * @return length of the message in bytes (excluding serial stream start sign)
 */
static inline uint16_t mavlink_msg_switch_cmd_pack_chan(uint8_t system_id, uint8_t component_id, uint8_t chan,
                               mavlink_message_t* msg,
                                   uint8_t index,uint8_t value)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    char buf[MAVLINK_MSG_ID_SWITCH_CMD_LEN];
    _mav_put_uint8_t(buf, 0, index);
    _mav_put_uint8_t(buf, 1, value);

        memcpy(_MAV_PAYLOAD_NON_CONST(msg), buf, MAVLINK_MSG_ID_SWITCH_CMD_LEN);
#else
    mavlink_switch_cmd_t packet;
    packet.index = index;
    packet.value = value;

        memcpy(_MAV_PAYLOAD_NON_CONST(msg), &packet, MAVLINK_MSG_ID_SWITCH_CMD_LEN);
#endif

    msg->msgid = MAVLINK_MSG_ID_SWITCH_CMD;
    return mavlink_finalize_message_chan(msg, system_id, component_id, chan, MAVLINK_MSG_ID_SWITCH_CMD_MIN_LEN, MAVLINK_MSG_ID_SWITCH_CMD_LEN, MAVLINK_MSG_ID_SWITCH_CMD_CRC);
}

/**
 * @brief Encode a switch_cmd struct
 *
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param msg The MAVLink message to compress the data into
 * @param switch_cmd C-struct to read the message contents from
 */
static inline uint16_t mavlink_msg_switch_cmd_encode(uint8_t system_id, uint8_t component_id, mavlink_message_t* msg, const mavlink_switch_cmd_t* switch_cmd)
{
    return mavlink_msg_switch_cmd_pack(system_id, component_id, msg, switch_cmd->index, switch_cmd->value);
}

/**
 * @brief Encode a switch_cmd struct on a channel
 *
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param chan The MAVLink channel this message will be sent over
 * @param msg The MAVLink message to compress the data into
 * @param switch_cmd C-struct to read the message contents from
 */
static inline uint16_t mavlink_msg_switch_cmd_encode_chan(uint8_t system_id, uint8_t component_id, uint8_t chan, mavlink_message_t* msg, const mavlink_switch_cmd_t* switch_cmd)
{
    return mavlink_msg_switch_cmd_pack_chan(system_id, component_id, chan, msg, switch_cmd->index, switch_cmd->value);
}

/**
 * @brief Encode a switch_cmd struct with provided status structure
 *
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param status MAVLink status structure
 * @param msg The MAVLink message to compress the data into
 * @param switch_cmd C-struct to read the message contents from
 */
static inline uint16_t mavlink_msg_switch_cmd_encode_status(uint8_t system_id, uint8_t component_id, mavlink_status_t* _status, mavlink_message_t* msg, const mavlink_switch_cmd_t* switch_cmd)
{
    return mavlink_msg_switch_cmd_pack_status(system_id, component_id, _status, msg,  switch_cmd->index, switch_cmd->value);
}

/**
 * @brief Send a switch_cmd message
 * @param chan MAVLink channel to send the message
 *
 * @param index  Relay index, valid range 0-7.
 * @param value  Relay command value from protocol table: 0 ON, 1 OFF.
 */
#ifdef MAVLINK_USE_CONVENIENCE_FUNCTIONS

static inline void mavlink_msg_switch_cmd_send(mavlink_channel_t chan, uint8_t index, uint8_t value)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    char buf[MAVLINK_MSG_ID_SWITCH_CMD_LEN];
    _mav_put_uint8_t(buf, 0, index);
    _mav_put_uint8_t(buf, 1, value);

    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_SWITCH_CMD, buf, MAVLINK_MSG_ID_SWITCH_CMD_MIN_LEN, MAVLINK_MSG_ID_SWITCH_CMD_LEN, MAVLINK_MSG_ID_SWITCH_CMD_CRC);
#else
    mavlink_switch_cmd_t packet;
    packet.index = index;
    packet.value = value;

    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_SWITCH_CMD, (const char *)&packet, MAVLINK_MSG_ID_SWITCH_CMD_MIN_LEN, MAVLINK_MSG_ID_SWITCH_CMD_LEN, MAVLINK_MSG_ID_SWITCH_CMD_CRC);
#endif
}

/**
 * @brief Send a switch_cmd message
 * @param chan MAVLink channel to send the message
 * @param struct The MAVLink struct to serialize
 */
static inline void mavlink_msg_switch_cmd_send_struct(mavlink_channel_t chan, const mavlink_switch_cmd_t* switch_cmd)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    mavlink_msg_switch_cmd_send(chan, switch_cmd->index, switch_cmd->value);
#else
    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_SWITCH_CMD, (const char *)switch_cmd, MAVLINK_MSG_ID_SWITCH_CMD_MIN_LEN, MAVLINK_MSG_ID_SWITCH_CMD_LEN, MAVLINK_MSG_ID_SWITCH_CMD_CRC);
#endif
}

#if MAVLINK_MSG_ID_SWITCH_CMD_LEN <= MAVLINK_MAX_PAYLOAD_LEN
/*
  This variant of _send() can be used to save stack space by reusing
  memory from the receive buffer.  The caller provides a
  mavlink_message_t which is the size of a full mavlink message. This
  is usually the receive buffer for the channel, and allows a reply to an
  incoming message with minimum stack space usage.
 */
static inline void mavlink_msg_switch_cmd_send_buf(mavlink_message_t *msgbuf, mavlink_channel_t chan,  uint8_t index, uint8_t value)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    char *buf = (char *)msgbuf;
    _mav_put_uint8_t(buf, 0, index);
    _mav_put_uint8_t(buf, 1, value);

    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_SWITCH_CMD, buf, MAVLINK_MSG_ID_SWITCH_CMD_MIN_LEN, MAVLINK_MSG_ID_SWITCH_CMD_LEN, MAVLINK_MSG_ID_SWITCH_CMD_CRC);
#else
    mavlink_switch_cmd_t *packet = (mavlink_switch_cmd_t *)msgbuf;
    packet->index = index;
    packet->value = value;

    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_SWITCH_CMD, (const char *)packet, MAVLINK_MSG_ID_SWITCH_CMD_MIN_LEN, MAVLINK_MSG_ID_SWITCH_CMD_LEN, MAVLINK_MSG_ID_SWITCH_CMD_CRC);
#endif
}
#endif

#endif

// MESSAGE SWITCH_CMD UNPACKING


/**
 * @brief Get field index from switch_cmd message
 *
 * @return  Relay index, valid range 0-7.
 */
static inline uint8_t mavlink_msg_switch_cmd_get_index(const mavlink_message_t* msg)
{
    return _MAV_RETURN_uint8_t(msg,  0);
}

/**
 * @brief Get field value from switch_cmd message
 *
 * @return  Relay command value from protocol table: 0 ON, 1 OFF.
 */
static inline uint8_t mavlink_msg_switch_cmd_get_value(const mavlink_message_t* msg)
{
    return _MAV_RETURN_uint8_t(msg,  1);
}

/**
 * @brief Decode a switch_cmd message into a struct
 *
 * @param msg The message to decode
 * @param switch_cmd C-struct to decode the message contents into
 */
static inline void mavlink_msg_switch_cmd_decode(const mavlink_message_t* msg, mavlink_switch_cmd_t* switch_cmd)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    switch_cmd->index = mavlink_msg_switch_cmd_get_index(msg);
    switch_cmd->value = mavlink_msg_switch_cmd_get_value(msg);
#else
        uint8_t len = msg->len < MAVLINK_MSG_ID_SWITCH_CMD_LEN? msg->len : MAVLINK_MSG_ID_SWITCH_CMD_LEN;
        memset(switch_cmd, 0, MAVLINK_MSG_ID_SWITCH_CMD_LEN);
    memcpy(switch_cmd, _MAV_PAYLOAD(msg), len);
#endif
}
