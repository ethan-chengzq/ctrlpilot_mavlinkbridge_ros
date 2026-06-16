#pragma once
// MESSAGE HEIGHT_STATUS PACKING

#define MAVLINK_MSG_ID_HEIGHT_STATUS 6


typedef struct __mavlink_height_status_t {
 uint32_t timestamp_ms; /*< [ms] Timestamp from the sender clock.*/
 uint16_t near_dist[5]; /*< [cm] Nearest target distance.*/
 uint16_t near_stren[5]; /*<  Nearest target strength.*/
 uint16_t far_dist[5]; /*< [cm] Farthest target distance.*/
 uint16_t far_stren[5]; /*<  Farthest target strength.*/
 uint16_t most_dist[5]; /*< [cm] Strongest target distance.*/
 uint16_t most_stren[5]; /*<  Strongest target strength.*/
} mavlink_height_status_t;

#define MAVLINK_MSG_ID_HEIGHT_STATUS_LEN 64
#define MAVLINK_MSG_ID_HEIGHT_STATUS_MIN_LEN 64
#define MAVLINK_MSG_ID_6_LEN 64
#define MAVLINK_MSG_ID_6_MIN_LEN 64

#define MAVLINK_MSG_ID_HEIGHT_STATUS_CRC 190
#define MAVLINK_MSG_ID_6_CRC 190

#define MAVLINK_MSG_HEIGHT_STATUS_FIELD_NEAR_DIST_LEN 5
#define MAVLINK_MSG_HEIGHT_STATUS_FIELD_NEAR_STREN_LEN 5
#define MAVLINK_MSG_HEIGHT_STATUS_FIELD_FAR_DIST_LEN 5
#define MAVLINK_MSG_HEIGHT_STATUS_FIELD_FAR_STREN_LEN 5
#define MAVLINK_MSG_HEIGHT_STATUS_FIELD_MOST_DIST_LEN 5
#define MAVLINK_MSG_HEIGHT_STATUS_FIELD_MOST_STREN_LEN 5

#if MAVLINK_COMMAND_24BIT
#define MAVLINK_MESSAGE_INFO_HEIGHT_STATUS { \
    6, \
    "HEIGHT_STATUS", \
    7, \
    {  { "timestamp_ms", NULL, MAVLINK_TYPE_UINT32_T, 0, 0, offsetof(mavlink_height_status_t, timestamp_ms) }, \
         { "near_dist", NULL, MAVLINK_TYPE_UINT16_T, 5, 4, offsetof(mavlink_height_status_t, near_dist) }, \
         { "near_stren", NULL, MAVLINK_TYPE_UINT16_T, 5, 14, offsetof(mavlink_height_status_t, near_stren) }, \
         { "far_dist", NULL, MAVLINK_TYPE_UINT16_T, 5, 24, offsetof(mavlink_height_status_t, far_dist) }, \
         { "far_stren", NULL, MAVLINK_TYPE_UINT16_T, 5, 34, offsetof(mavlink_height_status_t, far_stren) }, \
         { "most_dist", NULL, MAVLINK_TYPE_UINT16_T, 5, 44, offsetof(mavlink_height_status_t, most_dist) }, \
         { "most_stren", NULL, MAVLINK_TYPE_UINT16_T, 5, 54, offsetof(mavlink_height_status_t, most_stren) }, \
         } \
}
#else
#define MAVLINK_MESSAGE_INFO_HEIGHT_STATUS { \
    "HEIGHT_STATUS", \
    7, \
    {  { "timestamp_ms", NULL, MAVLINK_TYPE_UINT32_T, 0, 0, offsetof(mavlink_height_status_t, timestamp_ms) }, \
         { "near_dist", NULL, MAVLINK_TYPE_UINT16_T, 5, 4, offsetof(mavlink_height_status_t, near_dist) }, \
         { "near_stren", NULL, MAVLINK_TYPE_UINT16_T, 5, 14, offsetof(mavlink_height_status_t, near_stren) }, \
         { "far_dist", NULL, MAVLINK_TYPE_UINT16_T, 5, 24, offsetof(mavlink_height_status_t, far_dist) }, \
         { "far_stren", NULL, MAVLINK_TYPE_UINT16_T, 5, 34, offsetof(mavlink_height_status_t, far_stren) }, \
         { "most_dist", NULL, MAVLINK_TYPE_UINT16_T, 5, 44, offsetof(mavlink_height_status_t, most_dist) }, \
         { "most_stren", NULL, MAVLINK_TYPE_UINT16_T, 5, 54, offsetof(mavlink_height_status_t, most_stren) }, \
         } \
}
#endif

/**
 * @brief Pack a height_status message
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param msg The MAVLink message to compress the data into
 *
 * @param timestamp_ms [ms] Timestamp from the sender clock.
 * @param near_dist [cm] Nearest target distance.
 * @param near_stren  Nearest target strength.
 * @param far_dist [cm] Farthest target distance.
 * @param far_stren  Farthest target strength.
 * @param most_dist [cm] Strongest target distance.
 * @param most_stren  Strongest target strength.
 * @return length of the message in bytes (excluding serial stream start sign)
 */
static inline uint16_t mavlink_msg_height_status_pack(uint8_t system_id, uint8_t component_id, mavlink_message_t* msg,
                               uint32_t timestamp_ms, const uint16_t *near_dist, const uint16_t *near_stren, const uint16_t *far_dist, const uint16_t *far_stren, const uint16_t *most_dist, const uint16_t *most_stren)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    char buf[MAVLINK_MSG_ID_HEIGHT_STATUS_LEN];
    _mav_put_uint32_t(buf, 0, timestamp_ms);
    _mav_put_uint16_t_array(buf, 4, near_dist, 5);
    _mav_put_uint16_t_array(buf, 14, near_stren, 5);
    _mav_put_uint16_t_array(buf, 24, far_dist, 5);
    _mav_put_uint16_t_array(buf, 34, far_stren, 5);
    _mav_put_uint16_t_array(buf, 44, most_dist, 5);
    _mav_put_uint16_t_array(buf, 54, most_stren, 5);
        memcpy(_MAV_PAYLOAD_NON_CONST(msg), buf, MAVLINK_MSG_ID_HEIGHT_STATUS_LEN);
#else
    mavlink_height_status_t packet;
    packet.timestamp_ms = timestamp_ms;
    mav_array_memcpy(packet.near_dist, near_dist, sizeof(uint16_t)*5);
    mav_array_memcpy(packet.near_stren, near_stren, sizeof(uint16_t)*5);
    mav_array_memcpy(packet.far_dist, far_dist, sizeof(uint16_t)*5);
    mav_array_memcpy(packet.far_stren, far_stren, sizeof(uint16_t)*5);
    mav_array_memcpy(packet.most_dist, most_dist, sizeof(uint16_t)*5);
    mav_array_memcpy(packet.most_stren, most_stren, sizeof(uint16_t)*5);
        memcpy(_MAV_PAYLOAD_NON_CONST(msg), &packet, MAVLINK_MSG_ID_HEIGHT_STATUS_LEN);
#endif

    msg->msgid = MAVLINK_MSG_ID_HEIGHT_STATUS;
    return mavlink_finalize_message(msg, system_id, component_id, MAVLINK_MSG_ID_HEIGHT_STATUS_MIN_LEN, MAVLINK_MSG_ID_HEIGHT_STATUS_LEN, MAVLINK_MSG_ID_HEIGHT_STATUS_CRC);
}

/**
 * @brief Pack a height_status message
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param status MAVLink status structure
 * @param msg The MAVLink message to compress the data into
 *
 * @param timestamp_ms [ms] Timestamp from the sender clock.
 * @param near_dist [cm] Nearest target distance.
 * @param near_stren  Nearest target strength.
 * @param far_dist [cm] Farthest target distance.
 * @param far_stren  Farthest target strength.
 * @param most_dist [cm] Strongest target distance.
 * @param most_stren  Strongest target strength.
 * @return length of the message in bytes (excluding serial stream start sign)
 */
static inline uint16_t mavlink_msg_height_status_pack_status(uint8_t system_id, uint8_t component_id, mavlink_status_t *_status, mavlink_message_t* msg,
                               uint32_t timestamp_ms, const uint16_t *near_dist, const uint16_t *near_stren, const uint16_t *far_dist, const uint16_t *far_stren, const uint16_t *most_dist, const uint16_t *most_stren)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    char buf[MAVLINK_MSG_ID_HEIGHT_STATUS_LEN];
    _mav_put_uint32_t(buf, 0, timestamp_ms);
    _mav_put_uint16_t_array(buf, 4, near_dist, 5);
    _mav_put_uint16_t_array(buf, 14, near_stren, 5);
    _mav_put_uint16_t_array(buf, 24, far_dist, 5);
    _mav_put_uint16_t_array(buf, 34, far_stren, 5);
    _mav_put_uint16_t_array(buf, 44, most_dist, 5);
    _mav_put_uint16_t_array(buf, 54, most_stren, 5);
        memcpy(_MAV_PAYLOAD_NON_CONST(msg), buf, MAVLINK_MSG_ID_HEIGHT_STATUS_LEN);
#else
    mavlink_height_status_t packet;
    packet.timestamp_ms = timestamp_ms;
    mav_array_memcpy(packet.near_dist, near_dist, sizeof(uint16_t)*5);
    mav_array_memcpy(packet.near_stren, near_stren, sizeof(uint16_t)*5);
    mav_array_memcpy(packet.far_dist, far_dist, sizeof(uint16_t)*5);
    mav_array_memcpy(packet.far_stren, far_stren, sizeof(uint16_t)*5);
    mav_array_memcpy(packet.most_dist, most_dist, sizeof(uint16_t)*5);
    mav_array_memcpy(packet.most_stren, most_stren, sizeof(uint16_t)*5);
        memcpy(_MAV_PAYLOAD_NON_CONST(msg), &packet, MAVLINK_MSG_ID_HEIGHT_STATUS_LEN);
#endif

    msg->msgid = MAVLINK_MSG_ID_HEIGHT_STATUS;
#if MAVLINK_CRC_EXTRA
    return mavlink_finalize_message_buffer(msg, system_id, component_id, _status, MAVLINK_MSG_ID_HEIGHT_STATUS_MIN_LEN, MAVLINK_MSG_ID_HEIGHT_STATUS_LEN, MAVLINK_MSG_ID_HEIGHT_STATUS_CRC);
#else
    return mavlink_finalize_message_buffer(msg, system_id, component_id, _status, MAVLINK_MSG_ID_HEIGHT_STATUS_MIN_LEN, MAVLINK_MSG_ID_HEIGHT_STATUS_LEN);
#endif
}

/**
 * @brief Pack a height_status message on a channel
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param chan The MAVLink channel this message will be sent over
 * @param msg The MAVLink message to compress the data into
 * @param timestamp_ms [ms] Timestamp from the sender clock.
 * @param near_dist [cm] Nearest target distance.
 * @param near_stren  Nearest target strength.
 * @param far_dist [cm] Farthest target distance.
 * @param far_stren  Farthest target strength.
 * @param most_dist [cm] Strongest target distance.
 * @param most_stren  Strongest target strength.
 * @return length of the message in bytes (excluding serial stream start sign)
 */
static inline uint16_t mavlink_msg_height_status_pack_chan(uint8_t system_id, uint8_t component_id, uint8_t chan,
                               mavlink_message_t* msg,
                                   uint32_t timestamp_ms,const uint16_t *near_dist,const uint16_t *near_stren,const uint16_t *far_dist,const uint16_t *far_stren,const uint16_t *most_dist,const uint16_t *most_stren)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    char buf[MAVLINK_MSG_ID_HEIGHT_STATUS_LEN];
    _mav_put_uint32_t(buf, 0, timestamp_ms);
    _mav_put_uint16_t_array(buf, 4, near_dist, 5);
    _mav_put_uint16_t_array(buf, 14, near_stren, 5);
    _mav_put_uint16_t_array(buf, 24, far_dist, 5);
    _mav_put_uint16_t_array(buf, 34, far_stren, 5);
    _mav_put_uint16_t_array(buf, 44, most_dist, 5);
    _mav_put_uint16_t_array(buf, 54, most_stren, 5);
        memcpy(_MAV_PAYLOAD_NON_CONST(msg), buf, MAVLINK_MSG_ID_HEIGHT_STATUS_LEN);
#else
    mavlink_height_status_t packet;
    packet.timestamp_ms = timestamp_ms;
    mav_array_memcpy(packet.near_dist, near_dist, sizeof(uint16_t)*5);
    mav_array_memcpy(packet.near_stren, near_stren, sizeof(uint16_t)*5);
    mav_array_memcpy(packet.far_dist, far_dist, sizeof(uint16_t)*5);
    mav_array_memcpy(packet.far_stren, far_stren, sizeof(uint16_t)*5);
    mav_array_memcpy(packet.most_dist, most_dist, sizeof(uint16_t)*5);
    mav_array_memcpy(packet.most_stren, most_stren, sizeof(uint16_t)*5);
        memcpy(_MAV_PAYLOAD_NON_CONST(msg), &packet, MAVLINK_MSG_ID_HEIGHT_STATUS_LEN);
#endif

    msg->msgid = MAVLINK_MSG_ID_HEIGHT_STATUS;
    return mavlink_finalize_message_chan(msg, system_id, component_id, chan, MAVLINK_MSG_ID_HEIGHT_STATUS_MIN_LEN, MAVLINK_MSG_ID_HEIGHT_STATUS_LEN, MAVLINK_MSG_ID_HEIGHT_STATUS_CRC);
}

/**
 * @brief Encode a height_status struct
 *
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param msg The MAVLink message to compress the data into
 * @param height_status C-struct to read the message contents from
 */
static inline uint16_t mavlink_msg_height_status_encode(uint8_t system_id, uint8_t component_id, mavlink_message_t* msg, const mavlink_height_status_t* height_status)
{
    return mavlink_msg_height_status_pack(system_id, component_id, msg, height_status->timestamp_ms, height_status->near_dist, height_status->near_stren, height_status->far_dist, height_status->far_stren, height_status->most_dist, height_status->most_stren);
}

/**
 * @brief Encode a height_status struct on a channel
 *
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param chan The MAVLink channel this message will be sent over
 * @param msg The MAVLink message to compress the data into
 * @param height_status C-struct to read the message contents from
 */
static inline uint16_t mavlink_msg_height_status_encode_chan(uint8_t system_id, uint8_t component_id, uint8_t chan, mavlink_message_t* msg, const mavlink_height_status_t* height_status)
{
    return mavlink_msg_height_status_pack_chan(system_id, component_id, chan, msg, height_status->timestamp_ms, height_status->near_dist, height_status->near_stren, height_status->far_dist, height_status->far_stren, height_status->most_dist, height_status->most_stren);
}

/**
 * @brief Encode a height_status struct with provided status structure
 *
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param status MAVLink status structure
 * @param msg The MAVLink message to compress the data into
 * @param height_status C-struct to read the message contents from
 */
static inline uint16_t mavlink_msg_height_status_encode_status(uint8_t system_id, uint8_t component_id, mavlink_status_t* _status, mavlink_message_t* msg, const mavlink_height_status_t* height_status)
{
    return mavlink_msg_height_status_pack_status(system_id, component_id, _status, msg,  height_status->timestamp_ms, height_status->near_dist, height_status->near_stren, height_status->far_dist, height_status->far_stren, height_status->most_dist, height_status->most_stren);
}

/**
 * @brief Send a height_status message
 * @param chan MAVLink channel to send the message
 *
 * @param timestamp_ms [ms] Timestamp from the sender clock.
 * @param near_dist [cm] Nearest target distance.
 * @param near_stren  Nearest target strength.
 * @param far_dist [cm] Farthest target distance.
 * @param far_stren  Farthest target strength.
 * @param most_dist [cm] Strongest target distance.
 * @param most_stren  Strongest target strength.
 */
#ifdef MAVLINK_USE_CONVENIENCE_FUNCTIONS

static inline void mavlink_msg_height_status_send(mavlink_channel_t chan, uint32_t timestamp_ms, const uint16_t *near_dist, const uint16_t *near_stren, const uint16_t *far_dist, const uint16_t *far_stren, const uint16_t *most_dist, const uint16_t *most_stren)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    char buf[MAVLINK_MSG_ID_HEIGHT_STATUS_LEN];
    _mav_put_uint32_t(buf, 0, timestamp_ms);
    _mav_put_uint16_t_array(buf, 4, near_dist, 5);
    _mav_put_uint16_t_array(buf, 14, near_stren, 5);
    _mav_put_uint16_t_array(buf, 24, far_dist, 5);
    _mav_put_uint16_t_array(buf, 34, far_stren, 5);
    _mav_put_uint16_t_array(buf, 44, most_dist, 5);
    _mav_put_uint16_t_array(buf, 54, most_stren, 5);
    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_HEIGHT_STATUS, buf, MAVLINK_MSG_ID_HEIGHT_STATUS_MIN_LEN, MAVLINK_MSG_ID_HEIGHT_STATUS_LEN, MAVLINK_MSG_ID_HEIGHT_STATUS_CRC);
#else
    mavlink_height_status_t packet;
    packet.timestamp_ms = timestamp_ms;
    mav_array_memcpy(packet.near_dist, near_dist, sizeof(uint16_t)*5);
    mav_array_memcpy(packet.near_stren, near_stren, sizeof(uint16_t)*5);
    mav_array_memcpy(packet.far_dist, far_dist, sizeof(uint16_t)*5);
    mav_array_memcpy(packet.far_stren, far_stren, sizeof(uint16_t)*5);
    mav_array_memcpy(packet.most_dist, most_dist, sizeof(uint16_t)*5);
    mav_array_memcpy(packet.most_stren, most_stren, sizeof(uint16_t)*5);
    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_HEIGHT_STATUS, (const char *)&packet, MAVLINK_MSG_ID_HEIGHT_STATUS_MIN_LEN, MAVLINK_MSG_ID_HEIGHT_STATUS_LEN, MAVLINK_MSG_ID_HEIGHT_STATUS_CRC);
#endif
}

/**
 * @brief Send a height_status message
 * @param chan MAVLink channel to send the message
 * @param struct The MAVLink struct to serialize
 */
static inline void mavlink_msg_height_status_send_struct(mavlink_channel_t chan, const mavlink_height_status_t* height_status)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    mavlink_msg_height_status_send(chan, height_status->timestamp_ms, height_status->near_dist, height_status->near_stren, height_status->far_dist, height_status->far_stren, height_status->most_dist, height_status->most_stren);
#else
    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_HEIGHT_STATUS, (const char *)height_status, MAVLINK_MSG_ID_HEIGHT_STATUS_MIN_LEN, MAVLINK_MSG_ID_HEIGHT_STATUS_LEN, MAVLINK_MSG_ID_HEIGHT_STATUS_CRC);
#endif
}

#if MAVLINK_MSG_ID_HEIGHT_STATUS_LEN <= MAVLINK_MAX_PAYLOAD_LEN
/*
  This variant of _send() can be used to save stack space by reusing
  memory from the receive buffer.  The caller provides a
  mavlink_message_t which is the size of a full mavlink message. This
  is usually the receive buffer for the channel, and allows a reply to an
  incoming message with minimum stack space usage.
 */
static inline void mavlink_msg_height_status_send_buf(mavlink_message_t *msgbuf, mavlink_channel_t chan,  uint32_t timestamp_ms, const uint16_t *near_dist, const uint16_t *near_stren, const uint16_t *far_dist, const uint16_t *far_stren, const uint16_t *most_dist, const uint16_t *most_stren)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    char *buf = (char *)msgbuf;
    _mav_put_uint32_t(buf, 0, timestamp_ms);
    _mav_put_uint16_t_array(buf, 4, near_dist, 5);
    _mav_put_uint16_t_array(buf, 14, near_stren, 5);
    _mav_put_uint16_t_array(buf, 24, far_dist, 5);
    _mav_put_uint16_t_array(buf, 34, far_stren, 5);
    _mav_put_uint16_t_array(buf, 44, most_dist, 5);
    _mav_put_uint16_t_array(buf, 54, most_stren, 5);
    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_HEIGHT_STATUS, buf, MAVLINK_MSG_ID_HEIGHT_STATUS_MIN_LEN, MAVLINK_MSG_ID_HEIGHT_STATUS_LEN, MAVLINK_MSG_ID_HEIGHT_STATUS_CRC);
#else
    mavlink_height_status_t *packet = (mavlink_height_status_t *)msgbuf;
    packet->timestamp_ms = timestamp_ms;
    mav_array_memcpy(packet->near_dist, near_dist, sizeof(uint16_t)*5);
    mav_array_memcpy(packet->near_stren, near_stren, sizeof(uint16_t)*5);
    mav_array_memcpy(packet->far_dist, far_dist, sizeof(uint16_t)*5);
    mav_array_memcpy(packet->far_stren, far_stren, sizeof(uint16_t)*5);
    mav_array_memcpy(packet->most_dist, most_dist, sizeof(uint16_t)*5);
    mav_array_memcpy(packet->most_stren, most_stren, sizeof(uint16_t)*5);
    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_HEIGHT_STATUS, (const char *)packet, MAVLINK_MSG_ID_HEIGHT_STATUS_MIN_LEN, MAVLINK_MSG_ID_HEIGHT_STATUS_LEN, MAVLINK_MSG_ID_HEIGHT_STATUS_CRC);
#endif
}
#endif

#endif

// MESSAGE HEIGHT_STATUS UNPACKING


/**
 * @brief Get field timestamp_ms from height_status message
 *
 * @return [ms] Timestamp from the sender clock.
 */
static inline uint32_t mavlink_msg_height_status_get_timestamp_ms(const mavlink_message_t* msg)
{
    return _MAV_RETURN_uint32_t(msg,  0);
}

/**
 * @brief Get field near_dist from height_status message
 *
 * @return [cm] Nearest target distance.
 */
static inline uint16_t mavlink_msg_height_status_get_near_dist(const mavlink_message_t* msg, uint16_t *near_dist)
{
    return _MAV_RETURN_uint16_t_array(msg, near_dist, 5,  4);
}

/**
 * @brief Get field near_stren from height_status message
 *
 * @return  Nearest target strength.
 */
static inline uint16_t mavlink_msg_height_status_get_near_stren(const mavlink_message_t* msg, uint16_t *near_stren)
{
    return _MAV_RETURN_uint16_t_array(msg, near_stren, 5,  14);
}

/**
 * @brief Get field far_dist from height_status message
 *
 * @return [cm] Farthest target distance.
 */
static inline uint16_t mavlink_msg_height_status_get_far_dist(const mavlink_message_t* msg, uint16_t *far_dist)
{
    return _MAV_RETURN_uint16_t_array(msg, far_dist, 5,  24);
}

/**
 * @brief Get field far_stren from height_status message
 *
 * @return  Farthest target strength.
 */
static inline uint16_t mavlink_msg_height_status_get_far_stren(const mavlink_message_t* msg, uint16_t *far_stren)
{
    return _MAV_RETURN_uint16_t_array(msg, far_stren, 5,  34);
}

/**
 * @brief Get field most_dist from height_status message
 *
 * @return [cm] Strongest target distance.
 */
static inline uint16_t mavlink_msg_height_status_get_most_dist(const mavlink_message_t* msg, uint16_t *most_dist)
{
    return _MAV_RETURN_uint16_t_array(msg, most_dist, 5,  44);
}

/**
 * @brief Get field most_stren from height_status message
 *
 * @return  Strongest target strength.
 */
static inline uint16_t mavlink_msg_height_status_get_most_stren(const mavlink_message_t* msg, uint16_t *most_stren)
{
    return _MAV_RETURN_uint16_t_array(msg, most_stren, 5,  54);
}

/**
 * @brief Decode a height_status message into a struct
 *
 * @param msg The message to decode
 * @param height_status C-struct to decode the message contents into
 */
static inline void mavlink_msg_height_status_decode(const mavlink_message_t* msg, mavlink_height_status_t* height_status)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    height_status->timestamp_ms = mavlink_msg_height_status_get_timestamp_ms(msg);
    mavlink_msg_height_status_get_near_dist(msg, height_status->near_dist);
    mavlink_msg_height_status_get_near_stren(msg, height_status->near_stren);
    mavlink_msg_height_status_get_far_dist(msg, height_status->far_dist);
    mavlink_msg_height_status_get_far_stren(msg, height_status->far_stren);
    mavlink_msg_height_status_get_most_dist(msg, height_status->most_dist);
    mavlink_msg_height_status_get_most_stren(msg, height_status->most_stren);
#else
        uint8_t len = msg->len < MAVLINK_MSG_ID_HEIGHT_STATUS_LEN? msg->len : MAVLINK_MSG_ID_HEIGHT_STATUS_LEN;
        memset(height_status, 0, MAVLINK_MSG_ID_HEIGHT_STATUS_LEN);
    memcpy(height_status, _MAV_PAYLOAD(msg), len);
#endif
}
