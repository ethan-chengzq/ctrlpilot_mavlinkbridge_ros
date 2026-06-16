#pragma once
// MESSAGE IMU_CALIB PACKING

#define MAVLINK_MSG_ID_IMU_CALIB 12


typedef struct __mavlink_imu_calib_t {
 double lon; /*< [deg] Longitude.*/
 double lat; /*< [deg] Latitude.*/
 float alt; /*< [m] Altitude.*/
} mavlink_imu_calib_t;

#define MAVLINK_MSG_ID_IMU_CALIB_LEN 20
#define MAVLINK_MSG_ID_IMU_CALIB_MIN_LEN 20
#define MAVLINK_MSG_ID_12_LEN 20
#define MAVLINK_MSG_ID_12_MIN_LEN 20

#define MAVLINK_MSG_ID_IMU_CALIB_CRC 28
#define MAVLINK_MSG_ID_12_CRC 28



#if MAVLINK_COMMAND_24BIT
#define MAVLINK_MESSAGE_INFO_IMU_CALIB { \
    12, \
    "IMU_CALIB", \
    3, \
    {  { "lon", NULL, MAVLINK_TYPE_DOUBLE, 0, 0, offsetof(mavlink_imu_calib_t, lon) }, \
         { "lat", NULL, MAVLINK_TYPE_DOUBLE, 0, 8, offsetof(mavlink_imu_calib_t, lat) }, \
         { "alt", NULL, MAVLINK_TYPE_FLOAT, 0, 16, offsetof(mavlink_imu_calib_t, alt) }, \
         } \
}
#else
#define MAVLINK_MESSAGE_INFO_IMU_CALIB { \
    "IMU_CALIB", \
    3, \
    {  { "lon", NULL, MAVLINK_TYPE_DOUBLE, 0, 0, offsetof(mavlink_imu_calib_t, lon) }, \
         { "lat", NULL, MAVLINK_TYPE_DOUBLE, 0, 8, offsetof(mavlink_imu_calib_t, lat) }, \
         { "alt", NULL, MAVLINK_TYPE_FLOAT, 0, 16, offsetof(mavlink_imu_calib_t, alt) }, \
         } \
}
#endif

/**
 * @brief Pack a imu_calib message
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param msg The MAVLink message to compress the data into
 *
 * @param lon [deg] Longitude.
 * @param lat [deg] Latitude.
 * @param alt [m] Altitude.
 * @return length of the message in bytes (excluding serial stream start sign)
 */
static inline uint16_t mavlink_msg_imu_calib_pack(uint8_t system_id, uint8_t component_id, mavlink_message_t* msg,
                               double lon, double lat, float alt)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    char buf[MAVLINK_MSG_ID_IMU_CALIB_LEN];
    _mav_put_double(buf, 0, lon);
    _mav_put_double(buf, 8, lat);
    _mav_put_float(buf, 16, alt);

        memcpy(_MAV_PAYLOAD_NON_CONST(msg), buf, MAVLINK_MSG_ID_IMU_CALIB_LEN);
#else
    mavlink_imu_calib_t packet;
    packet.lon = lon;
    packet.lat = lat;
    packet.alt = alt;

        memcpy(_MAV_PAYLOAD_NON_CONST(msg), &packet, MAVLINK_MSG_ID_IMU_CALIB_LEN);
#endif

    msg->msgid = MAVLINK_MSG_ID_IMU_CALIB;
    return mavlink_finalize_message(msg, system_id, component_id, MAVLINK_MSG_ID_IMU_CALIB_MIN_LEN, MAVLINK_MSG_ID_IMU_CALIB_LEN, MAVLINK_MSG_ID_IMU_CALIB_CRC);
}

/**
 * @brief Pack a imu_calib message
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param status MAVLink status structure
 * @param msg The MAVLink message to compress the data into
 *
 * @param lon [deg] Longitude.
 * @param lat [deg] Latitude.
 * @param alt [m] Altitude.
 * @return length of the message in bytes (excluding serial stream start sign)
 */
static inline uint16_t mavlink_msg_imu_calib_pack_status(uint8_t system_id, uint8_t component_id, mavlink_status_t *_status, mavlink_message_t* msg,
                               double lon, double lat, float alt)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    char buf[MAVLINK_MSG_ID_IMU_CALIB_LEN];
    _mav_put_double(buf, 0, lon);
    _mav_put_double(buf, 8, lat);
    _mav_put_float(buf, 16, alt);

        memcpy(_MAV_PAYLOAD_NON_CONST(msg), buf, MAVLINK_MSG_ID_IMU_CALIB_LEN);
#else
    mavlink_imu_calib_t packet;
    packet.lon = lon;
    packet.lat = lat;
    packet.alt = alt;

        memcpy(_MAV_PAYLOAD_NON_CONST(msg), &packet, MAVLINK_MSG_ID_IMU_CALIB_LEN);
#endif

    msg->msgid = MAVLINK_MSG_ID_IMU_CALIB;
#if MAVLINK_CRC_EXTRA
    return mavlink_finalize_message_buffer(msg, system_id, component_id, _status, MAVLINK_MSG_ID_IMU_CALIB_MIN_LEN, MAVLINK_MSG_ID_IMU_CALIB_LEN, MAVLINK_MSG_ID_IMU_CALIB_CRC);
#else
    return mavlink_finalize_message_buffer(msg, system_id, component_id, _status, MAVLINK_MSG_ID_IMU_CALIB_MIN_LEN, MAVLINK_MSG_ID_IMU_CALIB_LEN);
#endif
}

/**
 * @brief Pack a imu_calib message on a channel
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param chan The MAVLink channel this message will be sent over
 * @param msg The MAVLink message to compress the data into
 * @param lon [deg] Longitude.
 * @param lat [deg] Latitude.
 * @param alt [m] Altitude.
 * @return length of the message in bytes (excluding serial stream start sign)
 */
static inline uint16_t mavlink_msg_imu_calib_pack_chan(uint8_t system_id, uint8_t component_id, uint8_t chan,
                               mavlink_message_t* msg,
                                   double lon,double lat,float alt)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    char buf[MAVLINK_MSG_ID_IMU_CALIB_LEN];
    _mav_put_double(buf, 0, lon);
    _mav_put_double(buf, 8, lat);
    _mav_put_float(buf, 16, alt);

        memcpy(_MAV_PAYLOAD_NON_CONST(msg), buf, MAVLINK_MSG_ID_IMU_CALIB_LEN);
#else
    mavlink_imu_calib_t packet;
    packet.lon = lon;
    packet.lat = lat;
    packet.alt = alt;

        memcpy(_MAV_PAYLOAD_NON_CONST(msg), &packet, MAVLINK_MSG_ID_IMU_CALIB_LEN);
#endif

    msg->msgid = MAVLINK_MSG_ID_IMU_CALIB;
    return mavlink_finalize_message_chan(msg, system_id, component_id, chan, MAVLINK_MSG_ID_IMU_CALIB_MIN_LEN, MAVLINK_MSG_ID_IMU_CALIB_LEN, MAVLINK_MSG_ID_IMU_CALIB_CRC);
}

/**
 * @brief Encode a imu_calib struct
 *
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param msg The MAVLink message to compress the data into
 * @param imu_calib C-struct to read the message contents from
 */
static inline uint16_t mavlink_msg_imu_calib_encode(uint8_t system_id, uint8_t component_id, mavlink_message_t* msg, const mavlink_imu_calib_t* imu_calib)
{
    return mavlink_msg_imu_calib_pack(system_id, component_id, msg, imu_calib->lon, imu_calib->lat, imu_calib->alt);
}

/**
 * @brief Encode a imu_calib struct on a channel
 *
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param chan The MAVLink channel this message will be sent over
 * @param msg The MAVLink message to compress the data into
 * @param imu_calib C-struct to read the message contents from
 */
static inline uint16_t mavlink_msg_imu_calib_encode_chan(uint8_t system_id, uint8_t component_id, uint8_t chan, mavlink_message_t* msg, const mavlink_imu_calib_t* imu_calib)
{
    return mavlink_msg_imu_calib_pack_chan(system_id, component_id, chan, msg, imu_calib->lon, imu_calib->lat, imu_calib->alt);
}

/**
 * @brief Encode a imu_calib struct with provided status structure
 *
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param status MAVLink status structure
 * @param msg The MAVLink message to compress the data into
 * @param imu_calib C-struct to read the message contents from
 */
static inline uint16_t mavlink_msg_imu_calib_encode_status(uint8_t system_id, uint8_t component_id, mavlink_status_t* _status, mavlink_message_t* msg, const mavlink_imu_calib_t* imu_calib)
{
    return mavlink_msg_imu_calib_pack_status(system_id, component_id, _status, msg,  imu_calib->lon, imu_calib->lat, imu_calib->alt);
}

/**
 * @brief Send a imu_calib message
 * @param chan MAVLink channel to send the message
 *
 * @param lon [deg] Longitude.
 * @param lat [deg] Latitude.
 * @param alt [m] Altitude.
 */
#ifdef MAVLINK_USE_CONVENIENCE_FUNCTIONS

static inline void mavlink_msg_imu_calib_send(mavlink_channel_t chan, double lon, double lat, float alt)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    char buf[MAVLINK_MSG_ID_IMU_CALIB_LEN];
    _mav_put_double(buf, 0, lon);
    _mav_put_double(buf, 8, lat);
    _mav_put_float(buf, 16, alt);

    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_IMU_CALIB, buf, MAVLINK_MSG_ID_IMU_CALIB_MIN_LEN, MAVLINK_MSG_ID_IMU_CALIB_LEN, MAVLINK_MSG_ID_IMU_CALIB_CRC);
#else
    mavlink_imu_calib_t packet;
    packet.lon = lon;
    packet.lat = lat;
    packet.alt = alt;

    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_IMU_CALIB, (const char *)&packet, MAVLINK_MSG_ID_IMU_CALIB_MIN_LEN, MAVLINK_MSG_ID_IMU_CALIB_LEN, MAVLINK_MSG_ID_IMU_CALIB_CRC);
#endif
}

/**
 * @brief Send a imu_calib message
 * @param chan MAVLink channel to send the message
 * @param struct The MAVLink struct to serialize
 */
static inline void mavlink_msg_imu_calib_send_struct(mavlink_channel_t chan, const mavlink_imu_calib_t* imu_calib)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    mavlink_msg_imu_calib_send(chan, imu_calib->lon, imu_calib->lat, imu_calib->alt);
#else
    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_IMU_CALIB, (const char *)imu_calib, MAVLINK_MSG_ID_IMU_CALIB_MIN_LEN, MAVLINK_MSG_ID_IMU_CALIB_LEN, MAVLINK_MSG_ID_IMU_CALIB_CRC);
#endif
}

#if MAVLINK_MSG_ID_IMU_CALIB_LEN <= MAVLINK_MAX_PAYLOAD_LEN
/*
  This variant of _send() can be used to save stack space by reusing
  memory from the receive buffer.  The caller provides a
  mavlink_message_t which is the size of a full mavlink message. This
  is usually the receive buffer for the channel, and allows a reply to an
  incoming message with minimum stack space usage.
 */
static inline void mavlink_msg_imu_calib_send_buf(mavlink_message_t *msgbuf, mavlink_channel_t chan,  double lon, double lat, float alt)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    char *buf = (char *)msgbuf;
    _mav_put_double(buf, 0, lon);
    _mav_put_double(buf, 8, lat);
    _mav_put_float(buf, 16, alt);

    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_IMU_CALIB, buf, MAVLINK_MSG_ID_IMU_CALIB_MIN_LEN, MAVLINK_MSG_ID_IMU_CALIB_LEN, MAVLINK_MSG_ID_IMU_CALIB_CRC);
#else
    mavlink_imu_calib_t *packet = (mavlink_imu_calib_t *)msgbuf;
    packet->lon = lon;
    packet->lat = lat;
    packet->alt = alt;

    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_IMU_CALIB, (const char *)packet, MAVLINK_MSG_ID_IMU_CALIB_MIN_LEN, MAVLINK_MSG_ID_IMU_CALIB_LEN, MAVLINK_MSG_ID_IMU_CALIB_CRC);
#endif
}
#endif

#endif

// MESSAGE IMU_CALIB UNPACKING


/**
 * @brief Get field lon from imu_calib message
 *
 * @return [deg] Longitude.
 */
static inline double mavlink_msg_imu_calib_get_lon(const mavlink_message_t* msg)
{
    return _MAV_RETURN_double(msg,  0);
}

/**
 * @brief Get field lat from imu_calib message
 *
 * @return [deg] Latitude.
 */
static inline double mavlink_msg_imu_calib_get_lat(const mavlink_message_t* msg)
{
    return _MAV_RETURN_double(msg,  8);
}

/**
 * @brief Get field alt from imu_calib message
 *
 * @return [m] Altitude.
 */
static inline float mavlink_msg_imu_calib_get_alt(const mavlink_message_t* msg)
{
    return _MAV_RETURN_float(msg,  16);
}

/**
 * @brief Decode a imu_calib message into a struct
 *
 * @param msg The message to decode
 * @param imu_calib C-struct to decode the message contents into
 */
static inline void mavlink_msg_imu_calib_decode(const mavlink_message_t* msg, mavlink_imu_calib_t* imu_calib)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    imu_calib->lon = mavlink_msg_imu_calib_get_lon(msg);
    imu_calib->lat = mavlink_msg_imu_calib_get_lat(msg);
    imu_calib->alt = mavlink_msg_imu_calib_get_alt(msg);
#else
        uint8_t len = msg->len < MAVLINK_MSG_ID_IMU_CALIB_LEN? msg->len : MAVLINK_MSG_ID_IMU_CALIB_LEN;
        memset(imu_calib, 0, MAVLINK_MSG_ID_IMU_CALIB_LEN);
    memcpy(imu_calib, _MAV_PAYLOAD(msg), len);
#endif
}
