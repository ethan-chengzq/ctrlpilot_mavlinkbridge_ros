#pragma once
// MESSAGE THRUSTER_CMD PACKING

#define MAVLINK_MSG_ID_THRUSTER_CMD 10


typedef struct __mavlink_thruster_cmd_t {
 uint16_t speed[12]; /*<  Thruster speed command values.*/
} mavlink_thruster_cmd_t;

#define MAVLINK_MSG_ID_THRUSTER_CMD_LEN 24
#define MAVLINK_MSG_ID_THRUSTER_CMD_MIN_LEN 24
#define MAVLINK_MSG_ID_10_LEN 24
#define MAVLINK_MSG_ID_10_MIN_LEN 24

#define MAVLINK_MSG_ID_THRUSTER_CMD_CRC 41
#define MAVLINK_MSG_ID_10_CRC 41

#define MAVLINK_MSG_THRUSTER_CMD_FIELD_SPEED_LEN 12

#if MAVLINK_COMMAND_24BIT
#define MAVLINK_MESSAGE_INFO_THRUSTER_CMD { \
    10, \
    "THRUSTER_CMD", \
    1, \
    {  { "speed", NULL, MAVLINK_TYPE_UINT16_T, 12, 0, offsetof(mavlink_thruster_cmd_t, speed) }, \
         } \
}
#else
#define MAVLINK_MESSAGE_INFO_THRUSTER_CMD { \
    "THRUSTER_CMD", \
    1, \
    {  { "speed", NULL, MAVLINK_TYPE_UINT16_T, 12, 0, offsetof(mavlink_thruster_cmd_t, speed) }, \
         } \
}
#endif

/**
 * @brief Pack a thruster_cmd message
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param msg The MAVLink message to compress the data into
 *
 * @param speed  Thruster speed command values.
 * @return length of the message in bytes (excluding serial stream start sign)
 */
static inline uint16_t mavlink_msg_thruster_cmd_pack(uint8_t system_id, uint8_t component_id, mavlink_message_t* msg,
                               const uint16_t *speed)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    char buf[MAVLINK_MSG_ID_THRUSTER_CMD_LEN];

    _mav_put_uint16_t_array(buf, 0, speed, 12);
        memcpy(_MAV_PAYLOAD_NON_CONST(msg), buf, MAVLINK_MSG_ID_THRUSTER_CMD_LEN);
#else
    mavlink_thruster_cmd_t packet;

    mav_array_memcpy(packet.speed, speed, sizeof(uint16_t)*12);
        memcpy(_MAV_PAYLOAD_NON_CONST(msg), &packet, MAVLINK_MSG_ID_THRUSTER_CMD_LEN);
#endif

    msg->msgid = MAVLINK_MSG_ID_THRUSTER_CMD;
    return mavlink_finalize_message(msg, system_id, component_id, MAVLINK_MSG_ID_THRUSTER_CMD_MIN_LEN, MAVLINK_MSG_ID_THRUSTER_CMD_LEN, MAVLINK_MSG_ID_THRUSTER_CMD_CRC);
}

/**
 * @brief Pack a thruster_cmd message
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param status MAVLink status structure
 * @param msg The MAVLink message to compress the data into
 *
 * @param speed  Thruster speed command values.
 * @return length of the message in bytes (excluding serial stream start sign)
 */
static inline uint16_t mavlink_msg_thruster_cmd_pack_status(uint8_t system_id, uint8_t component_id, mavlink_status_t *_status, mavlink_message_t* msg,
                               const uint16_t *speed)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    char buf[MAVLINK_MSG_ID_THRUSTER_CMD_LEN];

    _mav_put_uint16_t_array(buf, 0, speed, 12);
        memcpy(_MAV_PAYLOAD_NON_CONST(msg), buf, MAVLINK_MSG_ID_THRUSTER_CMD_LEN);
#else
    mavlink_thruster_cmd_t packet;

    mav_array_memcpy(packet.speed, speed, sizeof(uint16_t)*12);
        memcpy(_MAV_PAYLOAD_NON_CONST(msg), &packet, MAVLINK_MSG_ID_THRUSTER_CMD_LEN);
#endif

    msg->msgid = MAVLINK_MSG_ID_THRUSTER_CMD;
#if MAVLINK_CRC_EXTRA
    return mavlink_finalize_message_buffer(msg, system_id, component_id, _status, MAVLINK_MSG_ID_THRUSTER_CMD_MIN_LEN, MAVLINK_MSG_ID_THRUSTER_CMD_LEN, MAVLINK_MSG_ID_THRUSTER_CMD_CRC);
#else
    return mavlink_finalize_message_buffer(msg, system_id, component_id, _status, MAVLINK_MSG_ID_THRUSTER_CMD_MIN_LEN, MAVLINK_MSG_ID_THRUSTER_CMD_LEN);
#endif
}

/**
 * @brief Pack a thruster_cmd message on a channel
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param chan The MAVLink channel this message will be sent over
 * @param msg The MAVLink message to compress the data into
 * @param speed  Thruster speed command values.
 * @return length of the message in bytes (excluding serial stream start sign)
 */
static inline uint16_t mavlink_msg_thruster_cmd_pack_chan(uint8_t system_id, uint8_t component_id, uint8_t chan,
                               mavlink_message_t* msg,
                                   const uint16_t *speed)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    char buf[MAVLINK_MSG_ID_THRUSTER_CMD_LEN];

    _mav_put_uint16_t_array(buf, 0, speed, 12);
        memcpy(_MAV_PAYLOAD_NON_CONST(msg), buf, MAVLINK_MSG_ID_THRUSTER_CMD_LEN);
#else
    mavlink_thruster_cmd_t packet;

    mav_array_memcpy(packet.speed, speed, sizeof(uint16_t)*12);
        memcpy(_MAV_PAYLOAD_NON_CONST(msg), &packet, MAVLINK_MSG_ID_THRUSTER_CMD_LEN);
#endif

    msg->msgid = MAVLINK_MSG_ID_THRUSTER_CMD;
    return mavlink_finalize_message_chan(msg, system_id, component_id, chan, MAVLINK_MSG_ID_THRUSTER_CMD_MIN_LEN, MAVLINK_MSG_ID_THRUSTER_CMD_LEN, MAVLINK_MSG_ID_THRUSTER_CMD_CRC);
}

/**
 * @brief Encode a thruster_cmd struct
 *
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param msg The MAVLink message to compress the data into
 * @param thruster_cmd C-struct to read the message contents from
 */
static inline uint16_t mavlink_msg_thruster_cmd_encode(uint8_t system_id, uint8_t component_id, mavlink_message_t* msg, const mavlink_thruster_cmd_t* thruster_cmd)
{
    return mavlink_msg_thruster_cmd_pack(system_id, component_id, msg, thruster_cmd->speed);
}

/**
 * @brief Encode a thruster_cmd struct on a channel
 *
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param chan The MAVLink channel this message will be sent over
 * @param msg The MAVLink message to compress the data into
 * @param thruster_cmd C-struct to read the message contents from
 */
static inline uint16_t mavlink_msg_thruster_cmd_encode_chan(uint8_t system_id, uint8_t component_id, uint8_t chan, mavlink_message_t* msg, const mavlink_thruster_cmd_t* thruster_cmd)
{
    return mavlink_msg_thruster_cmd_pack_chan(system_id, component_id, chan, msg, thruster_cmd->speed);
}

/**
 * @brief Encode a thruster_cmd struct with provided status structure
 *
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param status MAVLink status structure
 * @param msg The MAVLink message to compress the data into
 * @param thruster_cmd C-struct to read the message contents from
 */
static inline uint16_t mavlink_msg_thruster_cmd_encode_status(uint8_t system_id, uint8_t component_id, mavlink_status_t* _status, mavlink_message_t* msg, const mavlink_thruster_cmd_t* thruster_cmd)
{
    return mavlink_msg_thruster_cmd_pack_status(system_id, component_id, _status, msg,  thruster_cmd->speed);
}

/**
 * @brief Send a thruster_cmd message
 * @param chan MAVLink channel to send the message
 *
 * @param speed  Thruster speed command values.
 */
#ifdef MAVLINK_USE_CONVENIENCE_FUNCTIONS

static inline void mavlink_msg_thruster_cmd_send(mavlink_channel_t chan, const uint16_t *speed)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    char buf[MAVLINK_MSG_ID_THRUSTER_CMD_LEN];

    _mav_put_uint16_t_array(buf, 0, speed, 12);
    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_THRUSTER_CMD, buf, MAVLINK_MSG_ID_THRUSTER_CMD_MIN_LEN, MAVLINK_MSG_ID_THRUSTER_CMD_LEN, MAVLINK_MSG_ID_THRUSTER_CMD_CRC);
#else
    mavlink_thruster_cmd_t packet;

    mav_array_memcpy(packet.speed, speed, sizeof(uint16_t)*12);
    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_THRUSTER_CMD, (const char *)&packet, MAVLINK_MSG_ID_THRUSTER_CMD_MIN_LEN, MAVLINK_MSG_ID_THRUSTER_CMD_LEN, MAVLINK_MSG_ID_THRUSTER_CMD_CRC);
#endif
}

/**
 * @brief Send a thruster_cmd message
 * @param chan MAVLink channel to send the message
 * @param struct The MAVLink struct to serialize
 */
static inline void mavlink_msg_thruster_cmd_send_struct(mavlink_channel_t chan, const mavlink_thruster_cmd_t* thruster_cmd)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    mavlink_msg_thruster_cmd_send(chan, thruster_cmd->speed);
#else
    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_THRUSTER_CMD, (const char *)thruster_cmd, MAVLINK_MSG_ID_THRUSTER_CMD_MIN_LEN, MAVLINK_MSG_ID_THRUSTER_CMD_LEN, MAVLINK_MSG_ID_THRUSTER_CMD_CRC);
#endif
}

#if MAVLINK_MSG_ID_THRUSTER_CMD_LEN <= MAVLINK_MAX_PAYLOAD_LEN
/*
  This variant of _send() can be used to save stack space by reusing
  memory from the receive buffer.  The caller provides a
  mavlink_message_t which is the size of a full mavlink message. This
  is usually the receive buffer for the channel, and allows a reply to an
  incoming message with minimum stack space usage.
 */
static inline void mavlink_msg_thruster_cmd_send_buf(mavlink_message_t *msgbuf, mavlink_channel_t chan,  const uint16_t *speed)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    char *buf = (char *)msgbuf;

    _mav_put_uint16_t_array(buf, 0, speed, 12);
    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_THRUSTER_CMD, buf, MAVLINK_MSG_ID_THRUSTER_CMD_MIN_LEN, MAVLINK_MSG_ID_THRUSTER_CMD_LEN, MAVLINK_MSG_ID_THRUSTER_CMD_CRC);
#else
    mavlink_thruster_cmd_t *packet = (mavlink_thruster_cmd_t *)msgbuf;

    mav_array_memcpy(packet->speed, speed, sizeof(uint16_t)*12);
    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_THRUSTER_CMD, (const char *)packet, MAVLINK_MSG_ID_THRUSTER_CMD_MIN_LEN, MAVLINK_MSG_ID_THRUSTER_CMD_LEN, MAVLINK_MSG_ID_THRUSTER_CMD_CRC);
#endif
}
#endif

#endif

// MESSAGE THRUSTER_CMD UNPACKING


/**
 * @brief Get field speed from thruster_cmd message
 *
 * @return  Thruster speed command values.
 */
static inline uint16_t mavlink_msg_thruster_cmd_get_speed(const mavlink_message_t* msg, uint16_t *speed)
{
    return _MAV_RETURN_uint16_t_array(msg, speed, 12,  0);
}

/**
 * @brief Decode a thruster_cmd message into a struct
 *
 * @param msg The message to decode
 * @param thruster_cmd C-struct to decode the message contents into
 */
static inline void mavlink_msg_thruster_cmd_decode(const mavlink_message_t* msg, mavlink_thruster_cmd_t* thruster_cmd)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    mavlink_msg_thruster_cmd_get_speed(msg, thruster_cmd->speed);
#else
        uint8_t len = msg->len < MAVLINK_MSG_ID_THRUSTER_CMD_LEN? msg->len : MAVLINK_MSG_ID_THRUSTER_CMD_LEN;
        memset(thruster_cmd, 0, MAVLINK_MSG_ID_THRUSTER_CMD_LEN);
    memcpy(thruster_cmd, _MAV_PAYLOAD(msg), len);
#endif
}
