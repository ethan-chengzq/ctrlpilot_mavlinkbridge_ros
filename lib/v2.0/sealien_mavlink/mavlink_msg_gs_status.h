#pragma once
// MESSAGE GS_STATUS PACKING

#define MAVLINK_MSG_ID_GS_STATUS 3


typedef struct __mavlink_gs_status_t {
 uint32_t timestamp_ms; /*< [ms] Timestamp from the sender clock.*/
 float angle[2]; /*< [deg] Servo angle feedback: index 0 horizontal, index 1 pitch.*/
 int16_t step[2]; /*<  Servo step feedback: index 0 horizontal, index 1 pitch.*/
 int16_t res[2]; /*<  Reserved fields for future servo status expansion.*/
} mavlink_gs_status_t;

#define MAVLINK_MSG_ID_GS_STATUS_LEN 20
#define MAVLINK_MSG_ID_GS_STATUS_MIN_LEN 20
#define MAVLINK_MSG_ID_3_LEN 20
#define MAVLINK_MSG_ID_3_MIN_LEN 20

#define MAVLINK_MSG_ID_GS_STATUS_CRC 16
#define MAVLINK_MSG_ID_3_CRC 16

#define MAVLINK_MSG_GS_STATUS_FIELD_ANGLE_LEN 2
#define MAVLINK_MSG_GS_STATUS_FIELD_STEP_LEN 2
#define MAVLINK_MSG_GS_STATUS_FIELD_RES_LEN 2

#if MAVLINK_COMMAND_24BIT
#define MAVLINK_MESSAGE_INFO_GS_STATUS { \
    3, \
    "GS_STATUS", \
    4, \
    {  { "timestamp_ms", NULL, MAVLINK_TYPE_UINT32_T, 0, 0, offsetof(mavlink_gs_status_t, timestamp_ms) }, \
         { "angle", NULL, MAVLINK_TYPE_FLOAT, 2, 4, offsetof(mavlink_gs_status_t, angle) }, \
         { "step", NULL, MAVLINK_TYPE_INT16_T, 2, 12, offsetof(mavlink_gs_status_t, step) }, \
         { "res", NULL, MAVLINK_TYPE_INT16_T, 2, 16, offsetof(mavlink_gs_status_t, res) }, \
         } \
}
#else
#define MAVLINK_MESSAGE_INFO_GS_STATUS { \
    "GS_STATUS", \
    4, \
    {  { "timestamp_ms", NULL, MAVLINK_TYPE_UINT32_T, 0, 0, offsetof(mavlink_gs_status_t, timestamp_ms) }, \
         { "angle", NULL, MAVLINK_TYPE_FLOAT, 2, 4, offsetof(mavlink_gs_status_t, angle) }, \
         { "step", NULL, MAVLINK_TYPE_INT16_T, 2, 12, offsetof(mavlink_gs_status_t, step) }, \
         { "res", NULL, MAVLINK_TYPE_INT16_T, 2, 16, offsetof(mavlink_gs_status_t, res) }, \
         } \
}
#endif

/**
 * @brief Pack a gs_status message
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param msg The MAVLink message to compress the data into
 *
 * @param timestamp_ms [ms] Timestamp from the sender clock.
 * @param angle [deg] Servo angle feedback: index 0 horizontal, index 1 pitch.
 * @param step  Servo step feedback: index 0 horizontal, index 1 pitch.
 * @param res  Reserved fields for future servo status expansion.
 * @return length of the message in bytes (excluding serial stream start sign)
 */
static inline uint16_t mavlink_msg_gs_status_pack(uint8_t system_id, uint8_t component_id, mavlink_message_t* msg,
                               uint32_t timestamp_ms, const float *angle, const int16_t *step, const int16_t *res)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    char buf[MAVLINK_MSG_ID_GS_STATUS_LEN];
    _mav_put_uint32_t(buf, 0, timestamp_ms);
    _mav_put_float_array(buf, 4, angle, 2);
    _mav_put_int16_t_array(buf, 12, step, 2);
    _mav_put_int16_t_array(buf, 16, res, 2);
        memcpy(_MAV_PAYLOAD_NON_CONST(msg), buf, MAVLINK_MSG_ID_GS_STATUS_LEN);
#else
    mavlink_gs_status_t packet;
    packet.timestamp_ms = timestamp_ms;
    mav_array_memcpy(packet.angle, angle, sizeof(float)*2);
    mav_array_memcpy(packet.step, step, sizeof(int16_t)*2);
    mav_array_memcpy(packet.res, res, sizeof(int16_t)*2);
        memcpy(_MAV_PAYLOAD_NON_CONST(msg), &packet, MAVLINK_MSG_ID_GS_STATUS_LEN);
#endif

    msg->msgid = MAVLINK_MSG_ID_GS_STATUS;
    return mavlink_finalize_message(msg, system_id, component_id, MAVLINK_MSG_ID_GS_STATUS_MIN_LEN, MAVLINK_MSG_ID_GS_STATUS_LEN, MAVLINK_MSG_ID_GS_STATUS_CRC);
}

/**
 * @brief Pack a gs_status message
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param status MAVLink status structure
 * @param msg The MAVLink message to compress the data into
 *
 * @param timestamp_ms [ms] Timestamp from the sender clock.
 * @param angle [deg] Servo angle feedback: index 0 horizontal, index 1 pitch.
 * @param step  Servo step feedback: index 0 horizontal, index 1 pitch.
 * @param res  Reserved fields for future servo status expansion.
 * @return length of the message in bytes (excluding serial stream start sign)
 */
static inline uint16_t mavlink_msg_gs_status_pack_status(uint8_t system_id, uint8_t component_id, mavlink_status_t *_status, mavlink_message_t* msg,
                               uint32_t timestamp_ms, const float *angle, const int16_t *step, const int16_t *res)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    char buf[MAVLINK_MSG_ID_GS_STATUS_LEN];
    _mav_put_uint32_t(buf, 0, timestamp_ms);
    _mav_put_float_array(buf, 4, angle, 2);
    _mav_put_int16_t_array(buf, 12, step, 2);
    _mav_put_int16_t_array(buf, 16, res, 2);
        memcpy(_MAV_PAYLOAD_NON_CONST(msg), buf, MAVLINK_MSG_ID_GS_STATUS_LEN);
#else
    mavlink_gs_status_t packet;
    packet.timestamp_ms = timestamp_ms;
    mav_array_memcpy(packet.angle, angle, sizeof(float)*2);
    mav_array_memcpy(packet.step, step, sizeof(int16_t)*2);
    mav_array_memcpy(packet.res, res, sizeof(int16_t)*2);
        memcpy(_MAV_PAYLOAD_NON_CONST(msg), &packet, MAVLINK_MSG_ID_GS_STATUS_LEN);
#endif

    msg->msgid = MAVLINK_MSG_ID_GS_STATUS;
#if MAVLINK_CRC_EXTRA
    return mavlink_finalize_message_buffer(msg, system_id, component_id, _status, MAVLINK_MSG_ID_GS_STATUS_MIN_LEN, MAVLINK_MSG_ID_GS_STATUS_LEN, MAVLINK_MSG_ID_GS_STATUS_CRC);
#else
    return mavlink_finalize_message_buffer(msg, system_id, component_id, _status, MAVLINK_MSG_ID_GS_STATUS_MIN_LEN, MAVLINK_MSG_ID_GS_STATUS_LEN);
#endif
}

/**
 * @brief Pack a gs_status message on a channel
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param chan The MAVLink channel this message will be sent over
 * @param msg The MAVLink message to compress the data into
 * @param timestamp_ms [ms] Timestamp from the sender clock.
 * @param angle [deg] Servo angle feedback: index 0 horizontal, index 1 pitch.
 * @param step  Servo step feedback: index 0 horizontal, index 1 pitch.
 * @param res  Reserved fields for future servo status expansion.
 * @return length of the message in bytes (excluding serial stream start sign)
 */
static inline uint16_t mavlink_msg_gs_status_pack_chan(uint8_t system_id, uint8_t component_id, uint8_t chan,
                               mavlink_message_t* msg,
                                   uint32_t timestamp_ms,const float *angle,const int16_t *step,const int16_t *res)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    char buf[MAVLINK_MSG_ID_GS_STATUS_LEN];
    _mav_put_uint32_t(buf, 0, timestamp_ms);
    _mav_put_float_array(buf, 4, angle, 2);
    _mav_put_int16_t_array(buf, 12, step, 2);
    _mav_put_int16_t_array(buf, 16, res, 2);
        memcpy(_MAV_PAYLOAD_NON_CONST(msg), buf, MAVLINK_MSG_ID_GS_STATUS_LEN);
#else
    mavlink_gs_status_t packet;
    packet.timestamp_ms = timestamp_ms;
    mav_array_memcpy(packet.angle, angle, sizeof(float)*2);
    mav_array_memcpy(packet.step, step, sizeof(int16_t)*2);
    mav_array_memcpy(packet.res, res, sizeof(int16_t)*2);
        memcpy(_MAV_PAYLOAD_NON_CONST(msg), &packet, MAVLINK_MSG_ID_GS_STATUS_LEN);
#endif

    msg->msgid = MAVLINK_MSG_ID_GS_STATUS;
    return mavlink_finalize_message_chan(msg, system_id, component_id, chan, MAVLINK_MSG_ID_GS_STATUS_MIN_LEN, MAVLINK_MSG_ID_GS_STATUS_LEN, MAVLINK_MSG_ID_GS_STATUS_CRC);
}

/**
 * @brief Encode a gs_status struct
 *
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param msg The MAVLink message to compress the data into
 * @param gs_status C-struct to read the message contents from
 */
static inline uint16_t mavlink_msg_gs_status_encode(uint8_t system_id, uint8_t component_id, mavlink_message_t* msg, const mavlink_gs_status_t* gs_status)
{
    return mavlink_msg_gs_status_pack(system_id, component_id, msg, gs_status->timestamp_ms, gs_status->angle, gs_status->step, gs_status->res);
}

/**
 * @brief Encode a gs_status struct on a channel
 *
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param chan The MAVLink channel this message will be sent over
 * @param msg The MAVLink message to compress the data into
 * @param gs_status C-struct to read the message contents from
 */
static inline uint16_t mavlink_msg_gs_status_encode_chan(uint8_t system_id, uint8_t component_id, uint8_t chan, mavlink_message_t* msg, const mavlink_gs_status_t* gs_status)
{
    return mavlink_msg_gs_status_pack_chan(system_id, component_id, chan, msg, gs_status->timestamp_ms, gs_status->angle, gs_status->step, gs_status->res);
}

/**
 * @brief Encode a gs_status struct with provided status structure
 *
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param status MAVLink status structure
 * @param msg The MAVLink message to compress the data into
 * @param gs_status C-struct to read the message contents from
 */
static inline uint16_t mavlink_msg_gs_status_encode_status(uint8_t system_id, uint8_t component_id, mavlink_status_t* _status, mavlink_message_t* msg, const mavlink_gs_status_t* gs_status)
{
    return mavlink_msg_gs_status_pack_status(system_id, component_id, _status, msg,  gs_status->timestamp_ms, gs_status->angle, gs_status->step, gs_status->res);
}

/**
 * @brief Send a gs_status message
 * @param chan MAVLink channel to send the message
 *
 * @param timestamp_ms [ms] Timestamp from the sender clock.
 * @param angle [deg] Servo angle feedback: index 0 horizontal, index 1 pitch.
 * @param step  Servo step feedback: index 0 horizontal, index 1 pitch.
 * @param res  Reserved fields for future servo status expansion.
 */
#ifdef MAVLINK_USE_CONVENIENCE_FUNCTIONS

static inline void mavlink_msg_gs_status_send(mavlink_channel_t chan, uint32_t timestamp_ms, const float *angle, const int16_t *step, const int16_t *res)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    char buf[MAVLINK_MSG_ID_GS_STATUS_LEN];
    _mav_put_uint32_t(buf, 0, timestamp_ms);
    _mav_put_float_array(buf, 4, angle, 2);
    _mav_put_int16_t_array(buf, 12, step, 2);
    _mav_put_int16_t_array(buf, 16, res, 2);
    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_GS_STATUS, buf, MAVLINK_MSG_ID_GS_STATUS_MIN_LEN, MAVLINK_MSG_ID_GS_STATUS_LEN, MAVLINK_MSG_ID_GS_STATUS_CRC);
#else
    mavlink_gs_status_t packet;
    packet.timestamp_ms = timestamp_ms;
    mav_array_memcpy(packet.angle, angle, sizeof(float)*2);
    mav_array_memcpy(packet.step, step, sizeof(int16_t)*2);
    mav_array_memcpy(packet.res, res, sizeof(int16_t)*2);
    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_GS_STATUS, (const char *)&packet, MAVLINK_MSG_ID_GS_STATUS_MIN_LEN, MAVLINK_MSG_ID_GS_STATUS_LEN, MAVLINK_MSG_ID_GS_STATUS_CRC);
#endif
}

/**
 * @brief Send a gs_status message
 * @param chan MAVLink channel to send the message
 * @param struct The MAVLink struct to serialize
 */
static inline void mavlink_msg_gs_status_send_struct(mavlink_channel_t chan, const mavlink_gs_status_t* gs_status)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    mavlink_msg_gs_status_send(chan, gs_status->timestamp_ms, gs_status->angle, gs_status->step, gs_status->res);
#else
    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_GS_STATUS, (const char *)gs_status, MAVLINK_MSG_ID_GS_STATUS_MIN_LEN, MAVLINK_MSG_ID_GS_STATUS_LEN, MAVLINK_MSG_ID_GS_STATUS_CRC);
#endif
}

#if MAVLINK_MSG_ID_GS_STATUS_LEN <= MAVLINK_MAX_PAYLOAD_LEN
/*
  This variant of _send() can be used to save stack space by reusing
  memory from the receive buffer.  The caller provides a
  mavlink_message_t which is the size of a full mavlink message. This
  is usually the receive buffer for the channel, and allows a reply to an
  incoming message with minimum stack space usage.
 */
static inline void mavlink_msg_gs_status_send_buf(mavlink_message_t *msgbuf, mavlink_channel_t chan,  uint32_t timestamp_ms, const float *angle, const int16_t *step, const int16_t *res)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    char *buf = (char *)msgbuf;
    _mav_put_uint32_t(buf, 0, timestamp_ms);
    _mav_put_float_array(buf, 4, angle, 2);
    _mav_put_int16_t_array(buf, 12, step, 2);
    _mav_put_int16_t_array(buf, 16, res, 2);
    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_GS_STATUS, buf, MAVLINK_MSG_ID_GS_STATUS_MIN_LEN, MAVLINK_MSG_ID_GS_STATUS_LEN, MAVLINK_MSG_ID_GS_STATUS_CRC);
#else
    mavlink_gs_status_t *packet = (mavlink_gs_status_t *)msgbuf;
    packet->timestamp_ms = timestamp_ms;
    mav_array_memcpy(packet->angle, angle, sizeof(float)*2);
    mav_array_memcpy(packet->step, step, sizeof(int16_t)*2);
    mav_array_memcpy(packet->res, res, sizeof(int16_t)*2);
    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_GS_STATUS, (const char *)packet, MAVLINK_MSG_ID_GS_STATUS_MIN_LEN, MAVLINK_MSG_ID_GS_STATUS_LEN, MAVLINK_MSG_ID_GS_STATUS_CRC);
#endif
}
#endif

#endif

// MESSAGE GS_STATUS UNPACKING


/**
 * @brief Get field timestamp_ms from gs_status message
 *
 * @return [ms] Timestamp from the sender clock.
 */
static inline uint32_t mavlink_msg_gs_status_get_timestamp_ms(const mavlink_message_t* msg)
{
    return _MAV_RETURN_uint32_t(msg,  0);
}

/**
 * @brief Get field angle from gs_status message
 *
 * @return [deg] Servo angle feedback: index 0 horizontal, index 1 pitch.
 */
static inline uint16_t mavlink_msg_gs_status_get_angle(const mavlink_message_t* msg, float *angle)
{
    return _MAV_RETURN_float_array(msg, angle, 2,  4);
}

/**
 * @brief Get field step from gs_status message
 *
 * @return  Servo step feedback: index 0 horizontal, index 1 pitch.
 */
static inline uint16_t mavlink_msg_gs_status_get_step(const mavlink_message_t* msg, int16_t *step)
{
    return _MAV_RETURN_int16_t_array(msg, step, 2,  12);
}

/**
 * @brief Get field res from gs_status message
 *
 * @return  Reserved fields for future servo status expansion.
 */
static inline uint16_t mavlink_msg_gs_status_get_res(const mavlink_message_t* msg, int16_t *res)
{
    return _MAV_RETURN_int16_t_array(msg, res, 2,  16);
}

/**
 * @brief Decode a gs_status message into a struct
 *
 * @param msg The message to decode
 * @param gs_status C-struct to decode the message contents into
 */
static inline void mavlink_msg_gs_status_decode(const mavlink_message_t* msg, mavlink_gs_status_t* gs_status)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    gs_status->timestamp_ms = mavlink_msg_gs_status_get_timestamp_ms(msg);
    mavlink_msg_gs_status_get_angle(msg, gs_status->angle);
    mavlink_msg_gs_status_get_step(msg, gs_status->step);
    mavlink_msg_gs_status_get_res(msg, gs_status->res);
#else
        uint8_t len = msg->len < MAVLINK_MSG_ID_GS_STATUS_LEN? msg->len : MAVLINK_MSG_ID_GS_STATUS_LEN;
        memset(gs_status, 0, MAVLINK_MSG_ID_GS_STATUS_LEN);
    memcpy(gs_status, _MAV_PAYLOAD(msg), len);
#endif
}
