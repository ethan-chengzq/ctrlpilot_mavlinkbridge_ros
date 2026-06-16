#pragma once
// MESSAGE THRUSTER_STATUS PACKING

#define MAVLINK_MSG_ID_THRUSTER_STATUS 2


typedef struct __mavlink_thruster_status_t {
 uint32_t timestamp_ms; /*< [ms] Timestamp from the sender clock.*/
 int16_t speed[12]; /*< [rpm] Thruster speed feedback.*/
 int16_t power[12]; /*< [W] Thruster power feedback.*/
 int16_t temp[12]; /*< [degC] Thruster temperature feedback.*/
 uint8_t status[12]; /*<  Thruster status code for each channel.*/
 uint8_t fault[12]; /*<  Thruster fault code for each channel.*/
 uint8_t lock; /*<  Thruster lock state: 0 unlocked, 1 locked.*/
} mavlink_thruster_status_t;

#define MAVLINK_MSG_ID_THRUSTER_STATUS_LEN 101
#define MAVLINK_MSG_ID_THRUSTER_STATUS_MIN_LEN 101
#define MAVLINK_MSG_ID_2_LEN 101
#define MAVLINK_MSG_ID_2_MIN_LEN 101

#define MAVLINK_MSG_ID_THRUSTER_STATUS_CRC 33
#define MAVLINK_MSG_ID_2_CRC 33

#define MAVLINK_MSG_THRUSTER_STATUS_FIELD_SPEED_LEN 12
#define MAVLINK_MSG_THRUSTER_STATUS_FIELD_POWER_LEN 12
#define MAVLINK_MSG_THRUSTER_STATUS_FIELD_TEMP_LEN 12
#define MAVLINK_MSG_THRUSTER_STATUS_FIELD_STATUS_LEN 12
#define MAVLINK_MSG_THRUSTER_STATUS_FIELD_FAULT_LEN 12

#if MAVLINK_COMMAND_24BIT
#define MAVLINK_MESSAGE_INFO_THRUSTER_STATUS { \
    2, \
    "THRUSTER_STATUS", \
    7, \
    {  { "timestamp_ms", NULL, MAVLINK_TYPE_UINT32_T, 0, 0, offsetof(mavlink_thruster_status_t, timestamp_ms) }, \
         { "speed", NULL, MAVLINK_TYPE_INT16_T, 12, 4, offsetof(mavlink_thruster_status_t, speed) }, \
         { "power", NULL, MAVLINK_TYPE_INT16_T, 12, 28, offsetof(mavlink_thruster_status_t, power) }, \
         { "temp", NULL, MAVLINK_TYPE_INT16_T, 12, 52, offsetof(mavlink_thruster_status_t, temp) }, \
         { "status", NULL, MAVLINK_TYPE_UINT8_T, 12, 76, offsetof(mavlink_thruster_status_t, status) }, \
         { "fault", NULL, MAVLINK_TYPE_UINT8_T, 12, 88, offsetof(mavlink_thruster_status_t, fault) }, \
         { "lock", NULL, MAVLINK_TYPE_UINT8_T, 0, 100, offsetof(mavlink_thruster_status_t, lock) }, \
         } \
}
#else
#define MAVLINK_MESSAGE_INFO_THRUSTER_STATUS { \
    "THRUSTER_STATUS", \
    7, \
    {  { "timestamp_ms", NULL, MAVLINK_TYPE_UINT32_T, 0, 0, offsetof(mavlink_thruster_status_t, timestamp_ms) }, \
         { "speed", NULL, MAVLINK_TYPE_INT16_T, 12, 4, offsetof(mavlink_thruster_status_t, speed) }, \
         { "power", NULL, MAVLINK_TYPE_INT16_T, 12, 28, offsetof(mavlink_thruster_status_t, power) }, \
         { "temp", NULL, MAVLINK_TYPE_INT16_T, 12, 52, offsetof(mavlink_thruster_status_t, temp) }, \
         { "status", NULL, MAVLINK_TYPE_UINT8_T, 12, 76, offsetof(mavlink_thruster_status_t, status) }, \
         { "fault", NULL, MAVLINK_TYPE_UINT8_T, 12, 88, offsetof(mavlink_thruster_status_t, fault) }, \
         { "lock", NULL, MAVLINK_TYPE_UINT8_T, 0, 100, offsetof(mavlink_thruster_status_t, lock) }, \
         } \
}
#endif

/**
 * @brief Pack a thruster_status message
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param msg The MAVLink message to compress the data into
 *
 * @param timestamp_ms [ms] Timestamp from the sender clock.
 * @param speed [rpm] Thruster speed feedback.
 * @param power [W] Thruster power feedback.
 * @param temp [degC] Thruster temperature feedback.
 * @param status  Thruster status code for each channel.
 * @param fault  Thruster fault code for each channel.
 * @param lock  Thruster lock state: 0 unlocked, 1 locked.
 * @return length of the message in bytes (excluding serial stream start sign)
 */
static inline uint16_t mavlink_msg_thruster_status_pack(uint8_t system_id, uint8_t component_id, mavlink_message_t* msg,
                               uint32_t timestamp_ms, const int16_t *speed, const int16_t *power, const int16_t *temp, const uint8_t *status, const uint8_t *fault, uint8_t lock)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    char buf[MAVLINK_MSG_ID_THRUSTER_STATUS_LEN];
    _mav_put_uint32_t(buf, 0, timestamp_ms);
    _mav_put_uint8_t(buf, 100, lock);
    _mav_put_int16_t_array(buf, 4, speed, 12);
    _mav_put_int16_t_array(buf, 28, power, 12);
    _mav_put_int16_t_array(buf, 52, temp, 12);
    _mav_put_uint8_t_array(buf, 76, status, 12);
    _mav_put_uint8_t_array(buf, 88, fault, 12);
        memcpy(_MAV_PAYLOAD_NON_CONST(msg), buf, MAVLINK_MSG_ID_THRUSTER_STATUS_LEN);
#else
    mavlink_thruster_status_t packet;
    packet.timestamp_ms = timestamp_ms;
    packet.lock = lock;
    mav_array_memcpy(packet.speed, speed, sizeof(int16_t)*12);
    mav_array_memcpy(packet.power, power, sizeof(int16_t)*12);
    mav_array_memcpy(packet.temp, temp, sizeof(int16_t)*12);
    mav_array_memcpy(packet.status, status, sizeof(uint8_t)*12);
    mav_array_memcpy(packet.fault, fault, sizeof(uint8_t)*12);
        memcpy(_MAV_PAYLOAD_NON_CONST(msg), &packet, MAVLINK_MSG_ID_THRUSTER_STATUS_LEN);
#endif

    msg->msgid = MAVLINK_MSG_ID_THRUSTER_STATUS;
    return mavlink_finalize_message(msg, system_id, component_id, MAVLINK_MSG_ID_THRUSTER_STATUS_MIN_LEN, MAVLINK_MSG_ID_THRUSTER_STATUS_LEN, MAVLINK_MSG_ID_THRUSTER_STATUS_CRC);
}

/**
 * @brief Pack a thruster_status message
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param status MAVLink status structure
 * @param msg The MAVLink message to compress the data into
 *
 * @param timestamp_ms [ms] Timestamp from the sender clock.
 * @param speed [rpm] Thruster speed feedback.
 * @param power [W] Thruster power feedback.
 * @param temp [degC] Thruster temperature feedback.
 * @param status  Thruster status code for each channel.
 * @param fault  Thruster fault code for each channel.
 * @param lock  Thruster lock state: 0 unlocked, 1 locked.
 * @return length of the message in bytes (excluding serial stream start sign)
 */
static inline uint16_t mavlink_msg_thruster_status_pack_status(uint8_t system_id, uint8_t component_id, mavlink_status_t *_status, mavlink_message_t* msg,
                               uint32_t timestamp_ms, const int16_t *speed, const int16_t *power, const int16_t *temp, const uint8_t *status, const uint8_t *fault, uint8_t lock)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    char buf[MAVLINK_MSG_ID_THRUSTER_STATUS_LEN];
    _mav_put_uint32_t(buf, 0, timestamp_ms);
    _mav_put_uint8_t(buf, 100, lock);
    _mav_put_int16_t_array(buf, 4, speed, 12);
    _mav_put_int16_t_array(buf, 28, power, 12);
    _mav_put_int16_t_array(buf, 52, temp, 12);
    _mav_put_uint8_t_array(buf, 76, status, 12);
    _mav_put_uint8_t_array(buf, 88, fault, 12);
        memcpy(_MAV_PAYLOAD_NON_CONST(msg), buf, MAVLINK_MSG_ID_THRUSTER_STATUS_LEN);
#else
    mavlink_thruster_status_t packet;
    packet.timestamp_ms = timestamp_ms;
    packet.lock = lock;
    mav_array_memcpy(packet.speed, speed, sizeof(int16_t)*12);
    mav_array_memcpy(packet.power, power, sizeof(int16_t)*12);
    mav_array_memcpy(packet.temp, temp, sizeof(int16_t)*12);
    mav_array_memcpy(packet.status, status, sizeof(uint8_t)*12);
    mav_array_memcpy(packet.fault, fault, sizeof(uint8_t)*12);
        memcpy(_MAV_PAYLOAD_NON_CONST(msg), &packet, MAVLINK_MSG_ID_THRUSTER_STATUS_LEN);
#endif

    msg->msgid = MAVLINK_MSG_ID_THRUSTER_STATUS;
#if MAVLINK_CRC_EXTRA
    return mavlink_finalize_message_buffer(msg, system_id, component_id, _status, MAVLINK_MSG_ID_THRUSTER_STATUS_MIN_LEN, MAVLINK_MSG_ID_THRUSTER_STATUS_LEN, MAVLINK_MSG_ID_THRUSTER_STATUS_CRC);
#else
    return mavlink_finalize_message_buffer(msg, system_id, component_id, _status, MAVLINK_MSG_ID_THRUSTER_STATUS_MIN_LEN, MAVLINK_MSG_ID_THRUSTER_STATUS_LEN);
#endif
}

/**
 * @brief Pack a thruster_status message on a channel
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param chan The MAVLink channel this message will be sent over
 * @param msg The MAVLink message to compress the data into
 * @param timestamp_ms [ms] Timestamp from the sender clock.
 * @param speed [rpm] Thruster speed feedback.
 * @param power [W] Thruster power feedback.
 * @param temp [degC] Thruster temperature feedback.
 * @param status  Thruster status code for each channel.
 * @param fault  Thruster fault code for each channel.
 * @param lock  Thruster lock state: 0 unlocked, 1 locked.
 * @return length of the message in bytes (excluding serial stream start sign)
 */
static inline uint16_t mavlink_msg_thruster_status_pack_chan(uint8_t system_id, uint8_t component_id, uint8_t chan,
                               mavlink_message_t* msg,
                                   uint32_t timestamp_ms,const int16_t *speed,const int16_t *power,const int16_t *temp,const uint8_t *status,const uint8_t *fault,uint8_t lock)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    char buf[MAVLINK_MSG_ID_THRUSTER_STATUS_LEN];
    _mav_put_uint32_t(buf, 0, timestamp_ms);
    _mav_put_uint8_t(buf, 100, lock);
    _mav_put_int16_t_array(buf, 4, speed, 12);
    _mav_put_int16_t_array(buf, 28, power, 12);
    _mav_put_int16_t_array(buf, 52, temp, 12);
    _mav_put_uint8_t_array(buf, 76, status, 12);
    _mav_put_uint8_t_array(buf, 88, fault, 12);
        memcpy(_MAV_PAYLOAD_NON_CONST(msg), buf, MAVLINK_MSG_ID_THRUSTER_STATUS_LEN);
#else
    mavlink_thruster_status_t packet;
    packet.timestamp_ms = timestamp_ms;
    packet.lock = lock;
    mav_array_memcpy(packet.speed, speed, sizeof(int16_t)*12);
    mav_array_memcpy(packet.power, power, sizeof(int16_t)*12);
    mav_array_memcpy(packet.temp, temp, sizeof(int16_t)*12);
    mav_array_memcpy(packet.status, status, sizeof(uint8_t)*12);
    mav_array_memcpy(packet.fault, fault, sizeof(uint8_t)*12);
        memcpy(_MAV_PAYLOAD_NON_CONST(msg), &packet, MAVLINK_MSG_ID_THRUSTER_STATUS_LEN);
#endif

    msg->msgid = MAVLINK_MSG_ID_THRUSTER_STATUS;
    return mavlink_finalize_message_chan(msg, system_id, component_id, chan, MAVLINK_MSG_ID_THRUSTER_STATUS_MIN_LEN, MAVLINK_MSG_ID_THRUSTER_STATUS_LEN, MAVLINK_MSG_ID_THRUSTER_STATUS_CRC);
}

/**
 * @brief Encode a thruster_status struct
 *
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param msg The MAVLink message to compress the data into
 * @param thruster_status C-struct to read the message contents from
 */
static inline uint16_t mavlink_msg_thruster_status_encode(uint8_t system_id, uint8_t component_id, mavlink_message_t* msg, const mavlink_thruster_status_t* thruster_status)
{
    return mavlink_msg_thruster_status_pack(system_id, component_id, msg, thruster_status->timestamp_ms, thruster_status->speed, thruster_status->power, thruster_status->temp, thruster_status->status, thruster_status->fault, thruster_status->lock);
}

/**
 * @brief Encode a thruster_status struct on a channel
 *
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param chan The MAVLink channel this message will be sent over
 * @param msg The MAVLink message to compress the data into
 * @param thruster_status C-struct to read the message contents from
 */
static inline uint16_t mavlink_msg_thruster_status_encode_chan(uint8_t system_id, uint8_t component_id, uint8_t chan, mavlink_message_t* msg, const mavlink_thruster_status_t* thruster_status)
{
    return mavlink_msg_thruster_status_pack_chan(system_id, component_id, chan, msg, thruster_status->timestamp_ms, thruster_status->speed, thruster_status->power, thruster_status->temp, thruster_status->status, thruster_status->fault, thruster_status->lock);
}

/**
 * @brief Encode a thruster_status struct with provided status structure
 *
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param status MAVLink status structure
 * @param msg The MAVLink message to compress the data into
 * @param thruster_status C-struct to read the message contents from
 */
static inline uint16_t mavlink_msg_thruster_status_encode_status(uint8_t system_id, uint8_t component_id, mavlink_status_t* _status, mavlink_message_t* msg, const mavlink_thruster_status_t* thruster_status)
{
    return mavlink_msg_thruster_status_pack_status(system_id, component_id, _status, msg,  thruster_status->timestamp_ms, thruster_status->speed, thruster_status->power, thruster_status->temp, thruster_status->status, thruster_status->fault, thruster_status->lock);
}

/**
 * @brief Send a thruster_status message
 * @param chan MAVLink channel to send the message
 *
 * @param timestamp_ms [ms] Timestamp from the sender clock.
 * @param speed [rpm] Thruster speed feedback.
 * @param power [W] Thruster power feedback.
 * @param temp [degC] Thruster temperature feedback.
 * @param status  Thruster status code for each channel.
 * @param fault  Thruster fault code for each channel.
 * @param lock  Thruster lock state: 0 unlocked, 1 locked.
 */
#ifdef MAVLINK_USE_CONVENIENCE_FUNCTIONS

static inline void mavlink_msg_thruster_status_send(mavlink_channel_t chan, uint32_t timestamp_ms, const int16_t *speed, const int16_t *power, const int16_t *temp, const uint8_t *status, const uint8_t *fault, uint8_t lock)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    char buf[MAVLINK_MSG_ID_THRUSTER_STATUS_LEN];
    _mav_put_uint32_t(buf, 0, timestamp_ms);
    _mav_put_uint8_t(buf, 100, lock);
    _mav_put_int16_t_array(buf, 4, speed, 12);
    _mav_put_int16_t_array(buf, 28, power, 12);
    _mav_put_int16_t_array(buf, 52, temp, 12);
    _mav_put_uint8_t_array(buf, 76, status, 12);
    _mav_put_uint8_t_array(buf, 88, fault, 12);
    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_THRUSTER_STATUS, buf, MAVLINK_MSG_ID_THRUSTER_STATUS_MIN_LEN, MAVLINK_MSG_ID_THRUSTER_STATUS_LEN, MAVLINK_MSG_ID_THRUSTER_STATUS_CRC);
#else
    mavlink_thruster_status_t packet;
    packet.timestamp_ms = timestamp_ms;
    packet.lock = lock;
    mav_array_memcpy(packet.speed, speed, sizeof(int16_t)*12);
    mav_array_memcpy(packet.power, power, sizeof(int16_t)*12);
    mav_array_memcpy(packet.temp, temp, sizeof(int16_t)*12);
    mav_array_memcpy(packet.status, status, sizeof(uint8_t)*12);
    mav_array_memcpy(packet.fault, fault, sizeof(uint8_t)*12);
    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_THRUSTER_STATUS, (const char *)&packet, MAVLINK_MSG_ID_THRUSTER_STATUS_MIN_LEN, MAVLINK_MSG_ID_THRUSTER_STATUS_LEN, MAVLINK_MSG_ID_THRUSTER_STATUS_CRC);
#endif
}

/**
 * @brief Send a thruster_status message
 * @param chan MAVLink channel to send the message
 * @param struct The MAVLink struct to serialize
 */
static inline void mavlink_msg_thruster_status_send_struct(mavlink_channel_t chan, const mavlink_thruster_status_t* thruster_status)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    mavlink_msg_thruster_status_send(chan, thruster_status->timestamp_ms, thruster_status->speed, thruster_status->power, thruster_status->temp, thruster_status->status, thruster_status->fault, thruster_status->lock);
#else
    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_THRUSTER_STATUS, (const char *)thruster_status, MAVLINK_MSG_ID_THRUSTER_STATUS_MIN_LEN, MAVLINK_MSG_ID_THRUSTER_STATUS_LEN, MAVLINK_MSG_ID_THRUSTER_STATUS_CRC);
#endif
}

#if MAVLINK_MSG_ID_THRUSTER_STATUS_LEN <= MAVLINK_MAX_PAYLOAD_LEN
/*
  This variant of _send() can be used to save stack space by reusing
  memory from the receive buffer.  The caller provides a
  mavlink_message_t which is the size of a full mavlink message. This
  is usually the receive buffer for the channel, and allows a reply to an
  incoming message with minimum stack space usage.
 */
static inline void mavlink_msg_thruster_status_send_buf(mavlink_message_t *msgbuf, mavlink_channel_t chan,  uint32_t timestamp_ms, const int16_t *speed, const int16_t *power, const int16_t *temp, const uint8_t *status, const uint8_t *fault, uint8_t lock)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    char *buf = (char *)msgbuf;
    _mav_put_uint32_t(buf, 0, timestamp_ms);
    _mav_put_uint8_t(buf, 100, lock);
    _mav_put_int16_t_array(buf, 4, speed, 12);
    _mav_put_int16_t_array(buf, 28, power, 12);
    _mav_put_int16_t_array(buf, 52, temp, 12);
    _mav_put_uint8_t_array(buf, 76, status, 12);
    _mav_put_uint8_t_array(buf, 88, fault, 12);
    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_THRUSTER_STATUS, buf, MAVLINK_MSG_ID_THRUSTER_STATUS_MIN_LEN, MAVLINK_MSG_ID_THRUSTER_STATUS_LEN, MAVLINK_MSG_ID_THRUSTER_STATUS_CRC);
#else
    mavlink_thruster_status_t *packet = (mavlink_thruster_status_t *)msgbuf;
    packet->timestamp_ms = timestamp_ms;
    packet->lock = lock;
    mav_array_memcpy(packet->speed, speed, sizeof(int16_t)*12);
    mav_array_memcpy(packet->power, power, sizeof(int16_t)*12);
    mav_array_memcpy(packet->temp, temp, sizeof(int16_t)*12);
    mav_array_memcpy(packet->status, status, sizeof(uint8_t)*12);
    mav_array_memcpy(packet->fault, fault, sizeof(uint8_t)*12);
    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_THRUSTER_STATUS, (const char *)packet, MAVLINK_MSG_ID_THRUSTER_STATUS_MIN_LEN, MAVLINK_MSG_ID_THRUSTER_STATUS_LEN, MAVLINK_MSG_ID_THRUSTER_STATUS_CRC);
#endif
}
#endif

#endif

// MESSAGE THRUSTER_STATUS UNPACKING


/**
 * @brief Get field timestamp_ms from thruster_status message
 *
 * @return [ms] Timestamp from the sender clock.
 */
static inline uint32_t mavlink_msg_thruster_status_get_timestamp_ms(const mavlink_message_t* msg)
{
    return _MAV_RETURN_uint32_t(msg,  0);
}

/**
 * @brief Get field speed from thruster_status message
 *
 * @return [rpm] Thruster speed feedback.
 */
static inline uint16_t mavlink_msg_thruster_status_get_speed(const mavlink_message_t* msg, int16_t *speed)
{
    return _MAV_RETURN_int16_t_array(msg, speed, 12,  4);
}

/**
 * @brief Get field power from thruster_status message
 *
 * @return [W] Thruster power feedback.
 */
static inline uint16_t mavlink_msg_thruster_status_get_power(const mavlink_message_t* msg, int16_t *power)
{
    return _MAV_RETURN_int16_t_array(msg, power, 12,  28);
}

/**
 * @brief Get field temp from thruster_status message
 *
 * @return [degC] Thruster temperature feedback.
 */
static inline uint16_t mavlink_msg_thruster_status_get_temp(const mavlink_message_t* msg, int16_t *temp)
{
    return _MAV_RETURN_int16_t_array(msg, temp, 12,  52);
}

/**
 * @brief Get field status from thruster_status message
 *
 * @return  Thruster status code for each channel.
 */
static inline uint16_t mavlink_msg_thruster_status_get_status(const mavlink_message_t* msg, uint8_t *status)
{
    return _MAV_RETURN_uint8_t_array(msg, status, 12,  76);
}

/**
 * @brief Get field fault from thruster_status message
 *
 * @return  Thruster fault code for each channel.
 */
static inline uint16_t mavlink_msg_thruster_status_get_fault(const mavlink_message_t* msg, uint8_t *fault)
{
    return _MAV_RETURN_uint8_t_array(msg, fault, 12,  88);
}

/**
 * @brief Get field lock from thruster_status message
 *
 * @return  Thruster lock state: 0 unlocked, 1 locked.
 */
static inline uint8_t mavlink_msg_thruster_status_get_lock(const mavlink_message_t* msg)
{
    return _MAV_RETURN_uint8_t(msg,  100);
}

/**
 * @brief Decode a thruster_status message into a struct
 *
 * @param msg The message to decode
 * @param thruster_status C-struct to decode the message contents into
 */
static inline void mavlink_msg_thruster_status_decode(const mavlink_message_t* msg, mavlink_thruster_status_t* thruster_status)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    thruster_status->timestamp_ms = mavlink_msg_thruster_status_get_timestamp_ms(msg);
    mavlink_msg_thruster_status_get_speed(msg, thruster_status->speed);
    mavlink_msg_thruster_status_get_power(msg, thruster_status->power);
    mavlink_msg_thruster_status_get_temp(msg, thruster_status->temp);
    mavlink_msg_thruster_status_get_status(msg, thruster_status->status);
    mavlink_msg_thruster_status_get_fault(msg, thruster_status->fault);
    thruster_status->lock = mavlink_msg_thruster_status_get_lock(msg);
#else
        uint8_t len = msg->len < MAVLINK_MSG_ID_THRUSTER_STATUS_LEN? msg->len : MAVLINK_MSG_ID_THRUSTER_STATUS_LEN;
        memset(thruster_status, 0, MAVLINK_MSG_ID_THRUSTER_STATUS_LEN);
    memcpy(thruster_status, _MAV_PAYLOAD(msg), len);
#endif
}
