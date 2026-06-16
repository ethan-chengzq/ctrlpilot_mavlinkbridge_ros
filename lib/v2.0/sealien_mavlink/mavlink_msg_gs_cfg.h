#pragma once
// MESSAGE GS_CFG PACKING

#define MAVLINK_MSG_ID_GS_CFG 16


typedef struct __mavlink_gs_cfg_t {
 float max_angle[2]; /*< [deg] Servo maximum angle: index 0 horizontal, index 1 pitch.*/
 float min_angle[2]; /*< [deg] Servo minimum angle: index 0 horizontal, index 1 pitch.*/
 uint16_t step[2]; /*<  Servo step: index 0 horizontal, index 1 pitch.*/
} mavlink_gs_cfg_t;

#define MAVLINK_MSG_ID_GS_CFG_LEN 20
#define MAVLINK_MSG_ID_GS_CFG_MIN_LEN 20
#define MAVLINK_MSG_ID_16_LEN 20
#define MAVLINK_MSG_ID_16_MIN_LEN 20

#define MAVLINK_MSG_ID_GS_CFG_CRC 1
#define MAVLINK_MSG_ID_16_CRC 1

#define MAVLINK_MSG_GS_CFG_FIELD_MAX_ANGLE_LEN 2
#define MAVLINK_MSG_GS_CFG_FIELD_MIN_ANGLE_LEN 2
#define MAVLINK_MSG_GS_CFG_FIELD_STEP_LEN 2

#if MAVLINK_COMMAND_24BIT
#define MAVLINK_MESSAGE_INFO_GS_CFG { \
    16, \
    "GS_CFG", \
    3, \
    {  { "max_angle", NULL, MAVLINK_TYPE_FLOAT, 2, 0, offsetof(mavlink_gs_cfg_t, max_angle) }, \
         { "min_angle", NULL, MAVLINK_TYPE_FLOAT, 2, 8, offsetof(mavlink_gs_cfg_t, min_angle) }, \
         { "step", NULL, MAVLINK_TYPE_UINT16_T, 2, 16, offsetof(mavlink_gs_cfg_t, step) }, \
         } \
}
#else
#define MAVLINK_MESSAGE_INFO_GS_CFG { \
    "GS_CFG", \
    3, \
    {  { "max_angle", NULL, MAVLINK_TYPE_FLOAT, 2, 0, offsetof(mavlink_gs_cfg_t, max_angle) }, \
         { "min_angle", NULL, MAVLINK_TYPE_FLOAT, 2, 8, offsetof(mavlink_gs_cfg_t, min_angle) }, \
         { "step", NULL, MAVLINK_TYPE_UINT16_T, 2, 16, offsetof(mavlink_gs_cfg_t, step) }, \
         } \
}
#endif

/**
 * @brief Pack a gs_cfg message
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param msg The MAVLink message to compress the data into
 *
 * @param max_angle [deg] Servo maximum angle: index 0 horizontal, index 1 pitch.
 * @param min_angle [deg] Servo minimum angle: index 0 horizontal, index 1 pitch.
 * @param step  Servo step: index 0 horizontal, index 1 pitch.
 * @return length of the message in bytes (excluding serial stream start sign)
 */
static inline uint16_t mavlink_msg_gs_cfg_pack(uint8_t system_id, uint8_t component_id, mavlink_message_t* msg,
                               const float *max_angle, const float *min_angle, const uint16_t *step)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    char buf[MAVLINK_MSG_ID_GS_CFG_LEN];

    _mav_put_float_array(buf, 0, max_angle, 2);
    _mav_put_float_array(buf, 8, min_angle, 2);
    _mav_put_uint16_t_array(buf, 16, step, 2);
        memcpy(_MAV_PAYLOAD_NON_CONST(msg), buf, MAVLINK_MSG_ID_GS_CFG_LEN);
#else
    mavlink_gs_cfg_t packet;

    mav_array_memcpy(packet.max_angle, max_angle, sizeof(float)*2);
    mav_array_memcpy(packet.min_angle, min_angle, sizeof(float)*2);
    mav_array_memcpy(packet.step, step, sizeof(uint16_t)*2);
        memcpy(_MAV_PAYLOAD_NON_CONST(msg), &packet, MAVLINK_MSG_ID_GS_CFG_LEN);
#endif

    msg->msgid = MAVLINK_MSG_ID_GS_CFG;
    return mavlink_finalize_message(msg, system_id, component_id, MAVLINK_MSG_ID_GS_CFG_MIN_LEN, MAVLINK_MSG_ID_GS_CFG_LEN, MAVLINK_MSG_ID_GS_CFG_CRC);
}

/**
 * @brief Pack a gs_cfg message
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param status MAVLink status structure
 * @param msg The MAVLink message to compress the data into
 *
 * @param max_angle [deg] Servo maximum angle: index 0 horizontal, index 1 pitch.
 * @param min_angle [deg] Servo minimum angle: index 0 horizontal, index 1 pitch.
 * @param step  Servo step: index 0 horizontal, index 1 pitch.
 * @return length of the message in bytes (excluding serial stream start sign)
 */
static inline uint16_t mavlink_msg_gs_cfg_pack_status(uint8_t system_id, uint8_t component_id, mavlink_status_t *_status, mavlink_message_t* msg,
                               const float *max_angle, const float *min_angle, const uint16_t *step)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    char buf[MAVLINK_MSG_ID_GS_CFG_LEN];

    _mav_put_float_array(buf, 0, max_angle, 2);
    _mav_put_float_array(buf, 8, min_angle, 2);
    _mav_put_uint16_t_array(buf, 16, step, 2);
        memcpy(_MAV_PAYLOAD_NON_CONST(msg), buf, MAVLINK_MSG_ID_GS_CFG_LEN);
#else
    mavlink_gs_cfg_t packet;

    mav_array_memcpy(packet.max_angle, max_angle, sizeof(float)*2);
    mav_array_memcpy(packet.min_angle, min_angle, sizeof(float)*2);
    mav_array_memcpy(packet.step, step, sizeof(uint16_t)*2);
        memcpy(_MAV_PAYLOAD_NON_CONST(msg), &packet, MAVLINK_MSG_ID_GS_CFG_LEN);
#endif

    msg->msgid = MAVLINK_MSG_ID_GS_CFG;
#if MAVLINK_CRC_EXTRA
    return mavlink_finalize_message_buffer(msg, system_id, component_id, _status, MAVLINK_MSG_ID_GS_CFG_MIN_LEN, MAVLINK_MSG_ID_GS_CFG_LEN, MAVLINK_MSG_ID_GS_CFG_CRC);
#else
    return mavlink_finalize_message_buffer(msg, system_id, component_id, _status, MAVLINK_MSG_ID_GS_CFG_MIN_LEN, MAVLINK_MSG_ID_GS_CFG_LEN);
#endif
}

/**
 * @brief Pack a gs_cfg message on a channel
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param chan The MAVLink channel this message will be sent over
 * @param msg The MAVLink message to compress the data into
 * @param max_angle [deg] Servo maximum angle: index 0 horizontal, index 1 pitch.
 * @param min_angle [deg] Servo minimum angle: index 0 horizontal, index 1 pitch.
 * @param step  Servo step: index 0 horizontal, index 1 pitch.
 * @return length of the message in bytes (excluding serial stream start sign)
 */
static inline uint16_t mavlink_msg_gs_cfg_pack_chan(uint8_t system_id, uint8_t component_id, uint8_t chan,
                               mavlink_message_t* msg,
                                   const float *max_angle,const float *min_angle,const uint16_t *step)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    char buf[MAVLINK_MSG_ID_GS_CFG_LEN];

    _mav_put_float_array(buf, 0, max_angle, 2);
    _mav_put_float_array(buf, 8, min_angle, 2);
    _mav_put_uint16_t_array(buf, 16, step, 2);
        memcpy(_MAV_PAYLOAD_NON_CONST(msg), buf, MAVLINK_MSG_ID_GS_CFG_LEN);
#else
    mavlink_gs_cfg_t packet;

    mav_array_memcpy(packet.max_angle, max_angle, sizeof(float)*2);
    mav_array_memcpy(packet.min_angle, min_angle, sizeof(float)*2);
    mav_array_memcpy(packet.step, step, sizeof(uint16_t)*2);
        memcpy(_MAV_PAYLOAD_NON_CONST(msg), &packet, MAVLINK_MSG_ID_GS_CFG_LEN);
#endif

    msg->msgid = MAVLINK_MSG_ID_GS_CFG;
    return mavlink_finalize_message_chan(msg, system_id, component_id, chan, MAVLINK_MSG_ID_GS_CFG_MIN_LEN, MAVLINK_MSG_ID_GS_CFG_LEN, MAVLINK_MSG_ID_GS_CFG_CRC);
}

/**
 * @brief Encode a gs_cfg struct
 *
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param msg The MAVLink message to compress the data into
 * @param gs_cfg C-struct to read the message contents from
 */
static inline uint16_t mavlink_msg_gs_cfg_encode(uint8_t system_id, uint8_t component_id, mavlink_message_t* msg, const mavlink_gs_cfg_t* gs_cfg)
{
    return mavlink_msg_gs_cfg_pack(system_id, component_id, msg, gs_cfg->max_angle, gs_cfg->min_angle, gs_cfg->step);
}

/**
 * @brief Encode a gs_cfg struct on a channel
 *
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param chan The MAVLink channel this message will be sent over
 * @param msg The MAVLink message to compress the data into
 * @param gs_cfg C-struct to read the message contents from
 */
static inline uint16_t mavlink_msg_gs_cfg_encode_chan(uint8_t system_id, uint8_t component_id, uint8_t chan, mavlink_message_t* msg, const mavlink_gs_cfg_t* gs_cfg)
{
    return mavlink_msg_gs_cfg_pack_chan(system_id, component_id, chan, msg, gs_cfg->max_angle, gs_cfg->min_angle, gs_cfg->step);
}

/**
 * @brief Encode a gs_cfg struct with provided status structure
 *
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param status MAVLink status structure
 * @param msg The MAVLink message to compress the data into
 * @param gs_cfg C-struct to read the message contents from
 */
static inline uint16_t mavlink_msg_gs_cfg_encode_status(uint8_t system_id, uint8_t component_id, mavlink_status_t* _status, mavlink_message_t* msg, const mavlink_gs_cfg_t* gs_cfg)
{
    return mavlink_msg_gs_cfg_pack_status(system_id, component_id, _status, msg,  gs_cfg->max_angle, gs_cfg->min_angle, gs_cfg->step);
}

/**
 * @brief Send a gs_cfg message
 * @param chan MAVLink channel to send the message
 *
 * @param max_angle [deg] Servo maximum angle: index 0 horizontal, index 1 pitch.
 * @param min_angle [deg] Servo minimum angle: index 0 horizontal, index 1 pitch.
 * @param step  Servo step: index 0 horizontal, index 1 pitch.
 */
#ifdef MAVLINK_USE_CONVENIENCE_FUNCTIONS

static inline void mavlink_msg_gs_cfg_send(mavlink_channel_t chan, const float *max_angle, const float *min_angle, const uint16_t *step)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    char buf[MAVLINK_MSG_ID_GS_CFG_LEN];

    _mav_put_float_array(buf, 0, max_angle, 2);
    _mav_put_float_array(buf, 8, min_angle, 2);
    _mav_put_uint16_t_array(buf, 16, step, 2);
    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_GS_CFG, buf, MAVLINK_MSG_ID_GS_CFG_MIN_LEN, MAVLINK_MSG_ID_GS_CFG_LEN, MAVLINK_MSG_ID_GS_CFG_CRC);
#else
    mavlink_gs_cfg_t packet;

    mav_array_memcpy(packet.max_angle, max_angle, sizeof(float)*2);
    mav_array_memcpy(packet.min_angle, min_angle, sizeof(float)*2);
    mav_array_memcpy(packet.step, step, sizeof(uint16_t)*2);
    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_GS_CFG, (const char *)&packet, MAVLINK_MSG_ID_GS_CFG_MIN_LEN, MAVLINK_MSG_ID_GS_CFG_LEN, MAVLINK_MSG_ID_GS_CFG_CRC);
#endif
}

/**
 * @brief Send a gs_cfg message
 * @param chan MAVLink channel to send the message
 * @param struct The MAVLink struct to serialize
 */
static inline void mavlink_msg_gs_cfg_send_struct(mavlink_channel_t chan, const mavlink_gs_cfg_t* gs_cfg)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    mavlink_msg_gs_cfg_send(chan, gs_cfg->max_angle, gs_cfg->min_angle, gs_cfg->step);
#else
    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_GS_CFG, (const char *)gs_cfg, MAVLINK_MSG_ID_GS_CFG_MIN_LEN, MAVLINK_MSG_ID_GS_CFG_LEN, MAVLINK_MSG_ID_GS_CFG_CRC);
#endif
}

#if MAVLINK_MSG_ID_GS_CFG_LEN <= MAVLINK_MAX_PAYLOAD_LEN
/*
  This variant of _send() can be used to save stack space by reusing
  memory from the receive buffer.  The caller provides a
  mavlink_message_t which is the size of a full mavlink message. This
  is usually the receive buffer for the channel, and allows a reply to an
  incoming message with minimum stack space usage.
 */
static inline void mavlink_msg_gs_cfg_send_buf(mavlink_message_t *msgbuf, mavlink_channel_t chan,  const float *max_angle, const float *min_angle, const uint16_t *step)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    char *buf = (char *)msgbuf;

    _mav_put_float_array(buf, 0, max_angle, 2);
    _mav_put_float_array(buf, 8, min_angle, 2);
    _mav_put_uint16_t_array(buf, 16, step, 2);
    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_GS_CFG, buf, MAVLINK_MSG_ID_GS_CFG_MIN_LEN, MAVLINK_MSG_ID_GS_CFG_LEN, MAVLINK_MSG_ID_GS_CFG_CRC);
#else
    mavlink_gs_cfg_t *packet = (mavlink_gs_cfg_t *)msgbuf;

    mav_array_memcpy(packet->max_angle, max_angle, sizeof(float)*2);
    mav_array_memcpy(packet->min_angle, min_angle, sizeof(float)*2);
    mav_array_memcpy(packet->step, step, sizeof(uint16_t)*2);
    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_GS_CFG, (const char *)packet, MAVLINK_MSG_ID_GS_CFG_MIN_LEN, MAVLINK_MSG_ID_GS_CFG_LEN, MAVLINK_MSG_ID_GS_CFG_CRC);
#endif
}
#endif

#endif

// MESSAGE GS_CFG UNPACKING


/**
 * @brief Get field max_angle from gs_cfg message
 *
 * @return [deg] Servo maximum angle: index 0 horizontal, index 1 pitch.
 */
static inline uint16_t mavlink_msg_gs_cfg_get_max_angle(const mavlink_message_t* msg, float *max_angle)
{
    return _MAV_RETURN_float_array(msg, max_angle, 2,  0);
}

/**
 * @brief Get field min_angle from gs_cfg message
 *
 * @return [deg] Servo minimum angle: index 0 horizontal, index 1 pitch.
 */
static inline uint16_t mavlink_msg_gs_cfg_get_min_angle(const mavlink_message_t* msg, float *min_angle)
{
    return _MAV_RETURN_float_array(msg, min_angle, 2,  8);
}

/**
 * @brief Get field step from gs_cfg message
 *
 * @return  Servo step: index 0 horizontal, index 1 pitch.
 */
static inline uint16_t mavlink_msg_gs_cfg_get_step(const mavlink_message_t* msg, uint16_t *step)
{
    return _MAV_RETURN_uint16_t_array(msg, step, 2,  16);
}

/**
 * @brief Decode a gs_cfg message into a struct
 *
 * @param msg The message to decode
 * @param gs_cfg C-struct to decode the message contents into
 */
static inline void mavlink_msg_gs_cfg_decode(const mavlink_message_t* msg, mavlink_gs_cfg_t* gs_cfg)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    mavlink_msg_gs_cfg_get_max_angle(msg, gs_cfg->max_angle);
    mavlink_msg_gs_cfg_get_min_angle(msg, gs_cfg->min_angle);
    mavlink_msg_gs_cfg_get_step(msg, gs_cfg->step);
#else
        uint8_t len = msg->len < MAVLINK_MSG_ID_GS_CFG_LEN? msg->len : MAVLINK_MSG_ID_GS_CFG_LEN;
        memset(gs_cfg, 0, MAVLINK_MSG_ID_GS_CFG_LEN);
    memcpy(gs_cfg, _MAV_PAYLOAD(msg), len);
#endif
}
