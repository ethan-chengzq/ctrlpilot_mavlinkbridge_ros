#pragma once
// MESSAGE GS_CMD PACKING

#define MAVLINK_MSG_ID_GS_CMD 15


typedef struct __mavlink_gs_cmd_t {
 float angle; /*< [deg] Target servo angle.*/
 uint8_t index; /*<  Servo index: 0 horizontal, 1 pitch.*/
} mavlink_gs_cmd_t;

#define MAVLINK_MSG_ID_GS_CMD_LEN 5
#define MAVLINK_MSG_ID_GS_CMD_MIN_LEN 5
#define MAVLINK_MSG_ID_15_LEN 5
#define MAVLINK_MSG_ID_15_MIN_LEN 5

#define MAVLINK_MSG_ID_GS_CMD_CRC 208
#define MAVLINK_MSG_ID_15_CRC 208



#if MAVLINK_COMMAND_24BIT
#define MAVLINK_MESSAGE_INFO_GS_CMD { \
    15, \
    "GS_CMD", \
    2, \
    {  { "index", NULL, MAVLINK_TYPE_UINT8_T, 0, 4, offsetof(mavlink_gs_cmd_t, index) }, \
         { "angle", NULL, MAVLINK_TYPE_FLOAT, 0, 0, offsetof(mavlink_gs_cmd_t, angle) }, \
         } \
}
#else
#define MAVLINK_MESSAGE_INFO_GS_CMD { \
    "GS_CMD", \
    2, \
    {  { "index", NULL, MAVLINK_TYPE_UINT8_T, 0, 4, offsetof(mavlink_gs_cmd_t, index) }, \
         { "angle", NULL, MAVLINK_TYPE_FLOAT, 0, 0, offsetof(mavlink_gs_cmd_t, angle) }, \
         } \
}
#endif

/**
 * @brief Pack a gs_cmd message
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param msg The MAVLink message to compress the data into
 *
 * @param index  Servo index: 0 horizontal, 1 pitch.
 * @param angle [deg] Target servo angle.
 * @return length of the message in bytes (excluding serial stream start sign)
 */
static inline uint16_t mavlink_msg_gs_cmd_pack(uint8_t system_id, uint8_t component_id, mavlink_message_t* msg,
                               uint8_t index, float angle)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    char buf[MAVLINK_MSG_ID_GS_CMD_LEN];
    _mav_put_float(buf, 0, angle);
    _mav_put_uint8_t(buf, 4, index);

        memcpy(_MAV_PAYLOAD_NON_CONST(msg), buf, MAVLINK_MSG_ID_GS_CMD_LEN);
#else
    mavlink_gs_cmd_t packet;
    packet.angle = angle;
    packet.index = index;

        memcpy(_MAV_PAYLOAD_NON_CONST(msg), &packet, MAVLINK_MSG_ID_GS_CMD_LEN);
#endif

    msg->msgid = MAVLINK_MSG_ID_GS_CMD;
    return mavlink_finalize_message(msg, system_id, component_id, MAVLINK_MSG_ID_GS_CMD_MIN_LEN, MAVLINK_MSG_ID_GS_CMD_LEN, MAVLINK_MSG_ID_GS_CMD_CRC);
}

/**
 * @brief Pack a gs_cmd message
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param status MAVLink status structure
 * @param msg The MAVLink message to compress the data into
 *
 * @param index  Servo index: 0 horizontal, 1 pitch.
 * @param angle [deg] Target servo angle.
 * @return length of the message in bytes (excluding serial stream start sign)
 */
static inline uint16_t mavlink_msg_gs_cmd_pack_status(uint8_t system_id, uint8_t component_id, mavlink_status_t *_status, mavlink_message_t* msg,
                               uint8_t index, float angle)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    char buf[MAVLINK_MSG_ID_GS_CMD_LEN];
    _mav_put_float(buf, 0, angle);
    _mav_put_uint8_t(buf, 4, index);

        memcpy(_MAV_PAYLOAD_NON_CONST(msg), buf, MAVLINK_MSG_ID_GS_CMD_LEN);
#else
    mavlink_gs_cmd_t packet;
    packet.angle = angle;
    packet.index = index;

        memcpy(_MAV_PAYLOAD_NON_CONST(msg), &packet, MAVLINK_MSG_ID_GS_CMD_LEN);
#endif

    msg->msgid = MAVLINK_MSG_ID_GS_CMD;
#if MAVLINK_CRC_EXTRA
    return mavlink_finalize_message_buffer(msg, system_id, component_id, _status, MAVLINK_MSG_ID_GS_CMD_MIN_LEN, MAVLINK_MSG_ID_GS_CMD_LEN, MAVLINK_MSG_ID_GS_CMD_CRC);
#else
    return mavlink_finalize_message_buffer(msg, system_id, component_id, _status, MAVLINK_MSG_ID_GS_CMD_MIN_LEN, MAVLINK_MSG_ID_GS_CMD_LEN);
#endif
}

/**
 * @brief Pack a gs_cmd message on a channel
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param chan The MAVLink channel this message will be sent over
 * @param msg The MAVLink message to compress the data into
 * @param index  Servo index: 0 horizontal, 1 pitch.
 * @param angle [deg] Target servo angle.
 * @return length of the message in bytes (excluding serial stream start sign)
 */
static inline uint16_t mavlink_msg_gs_cmd_pack_chan(uint8_t system_id, uint8_t component_id, uint8_t chan,
                               mavlink_message_t* msg,
                                   uint8_t index,float angle)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    char buf[MAVLINK_MSG_ID_GS_CMD_LEN];
    _mav_put_float(buf, 0, angle);
    _mav_put_uint8_t(buf, 4, index);

        memcpy(_MAV_PAYLOAD_NON_CONST(msg), buf, MAVLINK_MSG_ID_GS_CMD_LEN);
#else
    mavlink_gs_cmd_t packet;
    packet.angle = angle;
    packet.index = index;

        memcpy(_MAV_PAYLOAD_NON_CONST(msg), &packet, MAVLINK_MSG_ID_GS_CMD_LEN);
#endif

    msg->msgid = MAVLINK_MSG_ID_GS_CMD;
    return mavlink_finalize_message_chan(msg, system_id, component_id, chan, MAVLINK_MSG_ID_GS_CMD_MIN_LEN, MAVLINK_MSG_ID_GS_CMD_LEN, MAVLINK_MSG_ID_GS_CMD_CRC);
}

/**
 * @brief Encode a gs_cmd struct
 *
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param msg The MAVLink message to compress the data into
 * @param gs_cmd C-struct to read the message contents from
 */
static inline uint16_t mavlink_msg_gs_cmd_encode(uint8_t system_id, uint8_t component_id, mavlink_message_t* msg, const mavlink_gs_cmd_t* gs_cmd)
{
    return mavlink_msg_gs_cmd_pack(system_id, component_id, msg, gs_cmd->index, gs_cmd->angle);
}

/**
 * @brief Encode a gs_cmd struct on a channel
 *
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param chan The MAVLink channel this message will be sent over
 * @param msg The MAVLink message to compress the data into
 * @param gs_cmd C-struct to read the message contents from
 */
static inline uint16_t mavlink_msg_gs_cmd_encode_chan(uint8_t system_id, uint8_t component_id, uint8_t chan, mavlink_message_t* msg, const mavlink_gs_cmd_t* gs_cmd)
{
    return mavlink_msg_gs_cmd_pack_chan(system_id, component_id, chan, msg, gs_cmd->index, gs_cmd->angle);
}

/**
 * @brief Encode a gs_cmd struct with provided status structure
 *
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param status MAVLink status structure
 * @param msg The MAVLink message to compress the data into
 * @param gs_cmd C-struct to read the message contents from
 */
static inline uint16_t mavlink_msg_gs_cmd_encode_status(uint8_t system_id, uint8_t component_id, mavlink_status_t* _status, mavlink_message_t* msg, const mavlink_gs_cmd_t* gs_cmd)
{
    return mavlink_msg_gs_cmd_pack_status(system_id, component_id, _status, msg,  gs_cmd->index, gs_cmd->angle);
}

/**
 * @brief Send a gs_cmd message
 * @param chan MAVLink channel to send the message
 *
 * @param index  Servo index: 0 horizontal, 1 pitch.
 * @param angle [deg] Target servo angle.
 */
#ifdef MAVLINK_USE_CONVENIENCE_FUNCTIONS

static inline void mavlink_msg_gs_cmd_send(mavlink_channel_t chan, uint8_t index, float angle)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    char buf[MAVLINK_MSG_ID_GS_CMD_LEN];
    _mav_put_float(buf, 0, angle);
    _mav_put_uint8_t(buf, 4, index);

    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_GS_CMD, buf, MAVLINK_MSG_ID_GS_CMD_MIN_LEN, MAVLINK_MSG_ID_GS_CMD_LEN, MAVLINK_MSG_ID_GS_CMD_CRC);
#else
    mavlink_gs_cmd_t packet;
    packet.angle = angle;
    packet.index = index;

    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_GS_CMD, (const char *)&packet, MAVLINK_MSG_ID_GS_CMD_MIN_LEN, MAVLINK_MSG_ID_GS_CMD_LEN, MAVLINK_MSG_ID_GS_CMD_CRC);
#endif
}

/**
 * @brief Send a gs_cmd message
 * @param chan MAVLink channel to send the message
 * @param struct The MAVLink struct to serialize
 */
static inline void mavlink_msg_gs_cmd_send_struct(mavlink_channel_t chan, const mavlink_gs_cmd_t* gs_cmd)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    mavlink_msg_gs_cmd_send(chan, gs_cmd->index, gs_cmd->angle);
#else
    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_GS_CMD, (const char *)gs_cmd, MAVLINK_MSG_ID_GS_CMD_MIN_LEN, MAVLINK_MSG_ID_GS_CMD_LEN, MAVLINK_MSG_ID_GS_CMD_CRC);
#endif
}

#if MAVLINK_MSG_ID_GS_CMD_LEN <= MAVLINK_MAX_PAYLOAD_LEN
/*
  This variant of _send() can be used to save stack space by reusing
  memory from the receive buffer.  The caller provides a
  mavlink_message_t which is the size of a full mavlink message. This
  is usually the receive buffer for the channel, and allows a reply to an
  incoming message with minimum stack space usage.
 */
static inline void mavlink_msg_gs_cmd_send_buf(mavlink_message_t *msgbuf, mavlink_channel_t chan,  uint8_t index, float angle)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    char *buf = (char *)msgbuf;
    _mav_put_float(buf, 0, angle);
    _mav_put_uint8_t(buf, 4, index);

    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_GS_CMD, buf, MAVLINK_MSG_ID_GS_CMD_MIN_LEN, MAVLINK_MSG_ID_GS_CMD_LEN, MAVLINK_MSG_ID_GS_CMD_CRC);
#else
    mavlink_gs_cmd_t *packet = (mavlink_gs_cmd_t *)msgbuf;
    packet->angle = angle;
    packet->index = index;

    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_GS_CMD, (const char *)packet, MAVLINK_MSG_ID_GS_CMD_MIN_LEN, MAVLINK_MSG_ID_GS_CMD_LEN, MAVLINK_MSG_ID_GS_CMD_CRC);
#endif
}
#endif

#endif

// MESSAGE GS_CMD UNPACKING


/**
 * @brief Get field index from gs_cmd message
 *
 * @return  Servo index: 0 horizontal, 1 pitch.
 */
static inline uint8_t mavlink_msg_gs_cmd_get_index(const mavlink_message_t* msg)
{
    return _MAV_RETURN_uint8_t(msg,  4);
}

/**
 * @brief Get field angle from gs_cmd message
 *
 * @return [deg] Target servo angle.
 */
static inline float mavlink_msg_gs_cmd_get_angle(const mavlink_message_t* msg)
{
    return _MAV_RETURN_float(msg,  0);
}

/**
 * @brief Decode a gs_cmd message into a struct
 *
 * @param msg The message to decode
 * @param gs_cmd C-struct to decode the message contents into
 */
static inline void mavlink_msg_gs_cmd_decode(const mavlink_message_t* msg, mavlink_gs_cmd_t* gs_cmd)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    gs_cmd->angle = mavlink_msg_gs_cmd_get_angle(msg);
    gs_cmd->index = mavlink_msg_gs_cmd_get_index(msg);
#else
        uint8_t len = msg->len < MAVLINK_MSG_ID_GS_CMD_LEN? msg->len : MAVLINK_MSG_ID_GS_CMD_LEN;
        memset(gs_cmd, 0, MAVLINK_MSG_ID_GS_CMD_LEN);
    memcpy(gs_cmd, _MAV_PAYLOAD(msg), len);
#endif
}
