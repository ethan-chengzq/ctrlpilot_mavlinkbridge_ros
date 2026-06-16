#pragma once
// MESSAGE BEM280 PACKING

#define MAVLINK_MSG_ID_BEM280 8


typedef struct __mavlink_bem280_t {
 uint32_t timestamp_ms; /*< [ms] Timestamp from the sender clock.*/
 float temp; /*< [degC] Temperature.*/
 float humi; /*< [%] Relative humidity.*/
 float press; /*< [hPa] Pressure.*/
} mavlink_bem280_t;

#define MAVLINK_MSG_ID_BEM280_LEN 16
#define MAVLINK_MSG_ID_BEM280_MIN_LEN 16
#define MAVLINK_MSG_ID_8_LEN 16
#define MAVLINK_MSG_ID_8_MIN_LEN 16

#define MAVLINK_MSG_ID_BEM280_CRC 151
#define MAVLINK_MSG_ID_8_CRC 151



#if MAVLINK_COMMAND_24BIT
#define MAVLINK_MESSAGE_INFO_BEM280 { \
    8, \
    "BEM280", \
    4, \
    {  { "timestamp_ms", NULL, MAVLINK_TYPE_UINT32_T, 0, 0, offsetof(mavlink_bem280_t, timestamp_ms) }, \
         { "temp", NULL, MAVLINK_TYPE_FLOAT, 0, 4, offsetof(mavlink_bem280_t, temp) }, \
         { "humi", NULL, MAVLINK_TYPE_FLOAT, 0, 8, offsetof(mavlink_bem280_t, humi) }, \
         { "press", NULL, MAVLINK_TYPE_FLOAT, 0, 12, offsetof(mavlink_bem280_t, press) }, \
         } \
}
#else
#define MAVLINK_MESSAGE_INFO_BEM280 { \
    "BEM280", \
    4, \
    {  { "timestamp_ms", NULL, MAVLINK_TYPE_UINT32_T, 0, 0, offsetof(mavlink_bem280_t, timestamp_ms) }, \
         { "temp", NULL, MAVLINK_TYPE_FLOAT, 0, 4, offsetof(mavlink_bem280_t, temp) }, \
         { "humi", NULL, MAVLINK_TYPE_FLOAT, 0, 8, offsetof(mavlink_bem280_t, humi) }, \
         { "press", NULL, MAVLINK_TYPE_FLOAT, 0, 12, offsetof(mavlink_bem280_t, press) }, \
         } \
}
#endif

/**
 * @brief Pack a bem280 message
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param msg The MAVLink message to compress the data into
 *
 * @param timestamp_ms [ms] Timestamp from the sender clock.
 * @param temp [degC] Temperature.
 * @param humi [%] Relative humidity.
 * @param press [hPa] Pressure.
 * @return length of the message in bytes (excluding serial stream start sign)
 */
static inline uint16_t mavlink_msg_bem280_pack(uint8_t system_id, uint8_t component_id, mavlink_message_t* msg,
                               uint32_t timestamp_ms, float temp, float humi, float press)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    char buf[MAVLINK_MSG_ID_BEM280_LEN];
    _mav_put_uint32_t(buf, 0, timestamp_ms);
    _mav_put_float(buf, 4, temp);
    _mav_put_float(buf, 8, humi);
    _mav_put_float(buf, 12, press);

        memcpy(_MAV_PAYLOAD_NON_CONST(msg), buf, MAVLINK_MSG_ID_BEM280_LEN);
#else
    mavlink_bem280_t packet;
    packet.timestamp_ms = timestamp_ms;
    packet.temp = temp;
    packet.humi = humi;
    packet.press = press;

        memcpy(_MAV_PAYLOAD_NON_CONST(msg), &packet, MAVLINK_MSG_ID_BEM280_LEN);
#endif

    msg->msgid = MAVLINK_MSG_ID_BEM280;
    return mavlink_finalize_message(msg, system_id, component_id, MAVLINK_MSG_ID_BEM280_MIN_LEN, MAVLINK_MSG_ID_BEM280_LEN, MAVLINK_MSG_ID_BEM280_CRC);
}

/**
 * @brief Pack a bem280 message
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param status MAVLink status structure
 * @param msg The MAVLink message to compress the data into
 *
 * @param timestamp_ms [ms] Timestamp from the sender clock.
 * @param temp [degC] Temperature.
 * @param humi [%] Relative humidity.
 * @param press [hPa] Pressure.
 * @return length of the message in bytes (excluding serial stream start sign)
 */
static inline uint16_t mavlink_msg_bem280_pack_status(uint8_t system_id, uint8_t component_id, mavlink_status_t *_status, mavlink_message_t* msg,
                               uint32_t timestamp_ms, float temp, float humi, float press)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    char buf[MAVLINK_MSG_ID_BEM280_LEN];
    _mav_put_uint32_t(buf, 0, timestamp_ms);
    _mav_put_float(buf, 4, temp);
    _mav_put_float(buf, 8, humi);
    _mav_put_float(buf, 12, press);

        memcpy(_MAV_PAYLOAD_NON_CONST(msg), buf, MAVLINK_MSG_ID_BEM280_LEN);
#else
    mavlink_bem280_t packet;
    packet.timestamp_ms = timestamp_ms;
    packet.temp = temp;
    packet.humi = humi;
    packet.press = press;

        memcpy(_MAV_PAYLOAD_NON_CONST(msg), &packet, MAVLINK_MSG_ID_BEM280_LEN);
#endif

    msg->msgid = MAVLINK_MSG_ID_BEM280;
#if MAVLINK_CRC_EXTRA
    return mavlink_finalize_message_buffer(msg, system_id, component_id, _status, MAVLINK_MSG_ID_BEM280_MIN_LEN, MAVLINK_MSG_ID_BEM280_LEN, MAVLINK_MSG_ID_BEM280_CRC);
#else
    return mavlink_finalize_message_buffer(msg, system_id, component_id, _status, MAVLINK_MSG_ID_BEM280_MIN_LEN, MAVLINK_MSG_ID_BEM280_LEN);
#endif
}

/**
 * @brief Pack a bem280 message on a channel
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param chan The MAVLink channel this message will be sent over
 * @param msg The MAVLink message to compress the data into
 * @param timestamp_ms [ms] Timestamp from the sender clock.
 * @param temp [degC] Temperature.
 * @param humi [%] Relative humidity.
 * @param press [hPa] Pressure.
 * @return length of the message in bytes (excluding serial stream start sign)
 */
static inline uint16_t mavlink_msg_bem280_pack_chan(uint8_t system_id, uint8_t component_id, uint8_t chan,
                               mavlink_message_t* msg,
                                   uint32_t timestamp_ms,float temp,float humi,float press)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    char buf[MAVLINK_MSG_ID_BEM280_LEN];
    _mav_put_uint32_t(buf, 0, timestamp_ms);
    _mav_put_float(buf, 4, temp);
    _mav_put_float(buf, 8, humi);
    _mav_put_float(buf, 12, press);

        memcpy(_MAV_PAYLOAD_NON_CONST(msg), buf, MAVLINK_MSG_ID_BEM280_LEN);
#else
    mavlink_bem280_t packet;
    packet.timestamp_ms = timestamp_ms;
    packet.temp = temp;
    packet.humi = humi;
    packet.press = press;

        memcpy(_MAV_PAYLOAD_NON_CONST(msg), &packet, MAVLINK_MSG_ID_BEM280_LEN);
#endif

    msg->msgid = MAVLINK_MSG_ID_BEM280;
    return mavlink_finalize_message_chan(msg, system_id, component_id, chan, MAVLINK_MSG_ID_BEM280_MIN_LEN, MAVLINK_MSG_ID_BEM280_LEN, MAVLINK_MSG_ID_BEM280_CRC);
}

/**
 * @brief Encode a bem280 struct
 *
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param msg The MAVLink message to compress the data into
 * @param bem280 C-struct to read the message contents from
 */
static inline uint16_t mavlink_msg_bem280_encode(uint8_t system_id, uint8_t component_id, mavlink_message_t* msg, const mavlink_bem280_t* bem280)
{
    return mavlink_msg_bem280_pack(system_id, component_id, msg, bem280->timestamp_ms, bem280->temp, bem280->humi, bem280->press);
}

/**
 * @brief Encode a bem280 struct on a channel
 *
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param chan The MAVLink channel this message will be sent over
 * @param msg The MAVLink message to compress the data into
 * @param bem280 C-struct to read the message contents from
 */
static inline uint16_t mavlink_msg_bem280_encode_chan(uint8_t system_id, uint8_t component_id, uint8_t chan, mavlink_message_t* msg, const mavlink_bem280_t* bem280)
{
    return mavlink_msg_bem280_pack_chan(system_id, component_id, chan, msg, bem280->timestamp_ms, bem280->temp, bem280->humi, bem280->press);
}

/**
 * @brief Encode a bem280 struct with provided status structure
 *
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param status MAVLink status structure
 * @param msg The MAVLink message to compress the data into
 * @param bem280 C-struct to read the message contents from
 */
static inline uint16_t mavlink_msg_bem280_encode_status(uint8_t system_id, uint8_t component_id, mavlink_status_t* _status, mavlink_message_t* msg, const mavlink_bem280_t* bem280)
{
    return mavlink_msg_bem280_pack_status(system_id, component_id, _status, msg,  bem280->timestamp_ms, bem280->temp, bem280->humi, bem280->press);
}

/**
 * @brief Send a bem280 message
 * @param chan MAVLink channel to send the message
 *
 * @param timestamp_ms [ms] Timestamp from the sender clock.
 * @param temp [degC] Temperature.
 * @param humi [%] Relative humidity.
 * @param press [hPa] Pressure.
 */
#ifdef MAVLINK_USE_CONVENIENCE_FUNCTIONS

static inline void mavlink_msg_bem280_send(mavlink_channel_t chan, uint32_t timestamp_ms, float temp, float humi, float press)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    char buf[MAVLINK_MSG_ID_BEM280_LEN];
    _mav_put_uint32_t(buf, 0, timestamp_ms);
    _mav_put_float(buf, 4, temp);
    _mav_put_float(buf, 8, humi);
    _mav_put_float(buf, 12, press);

    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_BEM280, buf, MAVLINK_MSG_ID_BEM280_MIN_LEN, MAVLINK_MSG_ID_BEM280_LEN, MAVLINK_MSG_ID_BEM280_CRC);
#else
    mavlink_bem280_t packet;
    packet.timestamp_ms = timestamp_ms;
    packet.temp = temp;
    packet.humi = humi;
    packet.press = press;

    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_BEM280, (const char *)&packet, MAVLINK_MSG_ID_BEM280_MIN_LEN, MAVLINK_MSG_ID_BEM280_LEN, MAVLINK_MSG_ID_BEM280_CRC);
#endif
}

/**
 * @brief Send a bem280 message
 * @param chan MAVLink channel to send the message
 * @param struct The MAVLink struct to serialize
 */
static inline void mavlink_msg_bem280_send_struct(mavlink_channel_t chan, const mavlink_bem280_t* bem280)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    mavlink_msg_bem280_send(chan, bem280->timestamp_ms, bem280->temp, bem280->humi, bem280->press);
#else
    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_BEM280, (const char *)bem280, MAVLINK_MSG_ID_BEM280_MIN_LEN, MAVLINK_MSG_ID_BEM280_LEN, MAVLINK_MSG_ID_BEM280_CRC);
#endif
}

#if MAVLINK_MSG_ID_BEM280_LEN <= MAVLINK_MAX_PAYLOAD_LEN
/*
  This variant of _send() can be used to save stack space by reusing
  memory from the receive buffer.  The caller provides a
  mavlink_message_t which is the size of a full mavlink message. This
  is usually the receive buffer for the channel, and allows a reply to an
  incoming message with minimum stack space usage.
 */
static inline void mavlink_msg_bem280_send_buf(mavlink_message_t *msgbuf, mavlink_channel_t chan,  uint32_t timestamp_ms, float temp, float humi, float press)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    char *buf = (char *)msgbuf;
    _mav_put_uint32_t(buf, 0, timestamp_ms);
    _mav_put_float(buf, 4, temp);
    _mav_put_float(buf, 8, humi);
    _mav_put_float(buf, 12, press);

    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_BEM280, buf, MAVLINK_MSG_ID_BEM280_MIN_LEN, MAVLINK_MSG_ID_BEM280_LEN, MAVLINK_MSG_ID_BEM280_CRC);
#else
    mavlink_bem280_t *packet = (mavlink_bem280_t *)msgbuf;
    packet->timestamp_ms = timestamp_ms;
    packet->temp = temp;
    packet->humi = humi;
    packet->press = press;

    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_BEM280, (const char *)packet, MAVLINK_MSG_ID_BEM280_MIN_LEN, MAVLINK_MSG_ID_BEM280_LEN, MAVLINK_MSG_ID_BEM280_CRC);
#endif
}
#endif

#endif

// MESSAGE BEM280 UNPACKING


/**
 * @brief Get field timestamp_ms from bem280 message
 *
 * @return [ms] Timestamp from the sender clock.
 */
static inline uint32_t mavlink_msg_bem280_get_timestamp_ms(const mavlink_message_t* msg)
{
    return _MAV_RETURN_uint32_t(msg,  0);
}

/**
 * @brief Get field temp from bem280 message
 *
 * @return [degC] Temperature.
 */
static inline float mavlink_msg_bem280_get_temp(const mavlink_message_t* msg)
{
    return _MAV_RETURN_float(msg,  4);
}

/**
 * @brief Get field humi from bem280 message
 *
 * @return [%] Relative humidity.
 */
static inline float mavlink_msg_bem280_get_humi(const mavlink_message_t* msg)
{
    return _MAV_RETURN_float(msg,  8);
}

/**
 * @brief Get field press from bem280 message
 *
 * @return [hPa] Pressure.
 */
static inline float mavlink_msg_bem280_get_press(const mavlink_message_t* msg)
{
    return _MAV_RETURN_float(msg,  12);
}

/**
 * @brief Decode a bem280 message into a struct
 *
 * @param msg The message to decode
 * @param bem280 C-struct to decode the message contents into
 */
static inline void mavlink_msg_bem280_decode(const mavlink_message_t* msg, mavlink_bem280_t* bem280)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    bem280->timestamp_ms = mavlink_msg_bem280_get_timestamp_ms(msg);
    bem280->temp = mavlink_msg_bem280_get_temp(msg);
    bem280->humi = mavlink_msg_bem280_get_humi(msg);
    bem280->press = mavlink_msg_bem280_get_press(msg);
#else
        uint8_t len = msg->len < MAVLINK_MSG_ID_BEM280_LEN? msg->len : MAVLINK_MSG_ID_BEM280_LEN;
        memset(bem280, 0, MAVLINK_MSG_ID_BEM280_LEN);
    memcpy(bem280, _MAV_PAYLOAD(msg), len);
#endif
}
