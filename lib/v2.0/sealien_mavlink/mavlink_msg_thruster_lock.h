#pragma once
// MESSAGE THRUSTER_LOCK PACKING

#define MAVLINK_MSG_ID_THRUSTER_LOCK 11


typedef struct __mavlink_thruster_lock_t {
 uint8_t lock; /*<  Lock command: 0 unlock, 1 lock.*/
} mavlink_thruster_lock_t;

#define MAVLINK_MSG_ID_THRUSTER_LOCK_LEN 1
#define MAVLINK_MSG_ID_THRUSTER_LOCK_MIN_LEN 1
#define MAVLINK_MSG_ID_11_LEN 1
#define MAVLINK_MSG_ID_11_MIN_LEN 1

#define MAVLINK_MSG_ID_THRUSTER_LOCK_CRC 203
#define MAVLINK_MSG_ID_11_CRC 203



#if MAVLINK_COMMAND_24BIT
#define MAVLINK_MESSAGE_INFO_THRUSTER_LOCK { \
    11, \
    "THRUSTER_LOCK", \
    1, \
    {  { "lock", NULL, MAVLINK_TYPE_UINT8_T, 0, 0, offsetof(mavlink_thruster_lock_t, lock) }, \
         } \
}
#else
#define MAVLINK_MESSAGE_INFO_THRUSTER_LOCK { \
    "THRUSTER_LOCK", \
    1, \
    {  { "lock", NULL, MAVLINK_TYPE_UINT8_T, 0, 0, offsetof(mavlink_thruster_lock_t, lock) }, \
         } \
}
#endif

/**
 * @brief Pack a thruster_lock message
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param msg The MAVLink message to compress the data into
 *
 * @param lock  Lock command: 0 unlock, 1 lock.
 * @return length of the message in bytes (excluding serial stream start sign)
 */
static inline uint16_t mavlink_msg_thruster_lock_pack(uint8_t system_id, uint8_t component_id, mavlink_message_t* msg,
                               uint8_t lock)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    char buf[MAVLINK_MSG_ID_THRUSTER_LOCK_LEN];
    _mav_put_uint8_t(buf, 0, lock);

        memcpy(_MAV_PAYLOAD_NON_CONST(msg), buf, MAVLINK_MSG_ID_THRUSTER_LOCK_LEN);
#else
    mavlink_thruster_lock_t packet;
    packet.lock = lock;

        memcpy(_MAV_PAYLOAD_NON_CONST(msg), &packet, MAVLINK_MSG_ID_THRUSTER_LOCK_LEN);
#endif

    msg->msgid = MAVLINK_MSG_ID_THRUSTER_LOCK;
    return mavlink_finalize_message(msg, system_id, component_id, MAVLINK_MSG_ID_THRUSTER_LOCK_MIN_LEN, MAVLINK_MSG_ID_THRUSTER_LOCK_LEN, MAVLINK_MSG_ID_THRUSTER_LOCK_CRC);
}

/**
 * @brief Pack a thruster_lock message
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param status MAVLink status structure
 * @param msg The MAVLink message to compress the data into
 *
 * @param lock  Lock command: 0 unlock, 1 lock.
 * @return length of the message in bytes (excluding serial stream start sign)
 */
static inline uint16_t mavlink_msg_thruster_lock_pack_status(uint8_t system_id, uint8_t component_id, mavlink_status_t *_status, mavlink_message_t* msg,
                               uint8_t lock)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    char buf[MAVLINK_MSG_ID_THRUSTER_LOCK_LEN];
    _mav_put_uint8_t(buf, 0, lock);

        memcpy(_MAV_PAYLOAD_NON_CONST(msg), buf, MAVLINK_MSG_ID_THRUSTER_LOCK_LEN);
#else
    mavlink_thruster_lock_t packet;
    packet.lock = lock;

        memcpy(_MAV_PAYLOAD_NON_CONST(msg), &packet, MAVLINK_MSG_ID_THRUSTER_LOCK_LEN);
#endif

    msg->msgid = MAVLINK_MSG_ID_THRUSTER_LOCK;
#if MAVLINK_CRC_EXTRA
    return mavlink_finalize_message_buffer(msg, system_id, component_id, _status, MAVLINK_MSG_ID_THRUSTER_LOCK_MIN_LEN, MAVLINK_MSG_ID_THRUSTER_LOCK_LEN, MAVLINK_MSG_ID_THRUSTER_LOCK_CRC);
#else
    return mavlink_finalize_message_buffer(msg, system_id, component_id, _status, MAVLINK_MSG_ID_THRUSTER_LOCK_MIN_LEN, MAVLINK_MSG_ID_THRUSTER_LOCK_LEN);
#endif
}

/**
 * @brief Pack a thruster_lock message on a channel
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param chan The MAVLink channel this message will be sent over
 * @param msg The MAVLink message to compress the data into
 * @param lock  Lock command: 0 unlock, 1 lock.
 * @return length of the message in bytes (excluding serial stream start sign)
 */
static inline uint16_t mavlink_msg_thruster_lock_pack_chan(uint8_t system_id, uint8_t component_id, uint8_t chan,
                               mavlink_message_t* msg,
                                   uint8_t lock)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    char buf[MAVLINK_MSG_ID_THRUSTER_LOCK_LEN];
    _mav_put_uint8_t(buf, 0, lock);

        memcpy(_MAV_PAYLOAD_NON_CONST(msg), buf, MAVLINK_MSG_ID_THRUSTER_LOCK_LEN);
#else
    mavlink_thruster_lock_t packet;
    packet.lock = lock;

        memcpy(_MAV_PAYLOAD_NON_CONST(msg), &packet, MAVLINK_MSG_ID_THRUSTER_LOCK_LEN);
#endif

    msg->msgid = MAVLINK_MSG_ID_THRUSTER_LOCK;
    return mavlink_finalize_message_chan(msg, system_id, component_id, chan, MAVLINK_MSG_ID_THRUSTER_LOCK_MIN_LEN, MAVLINK_MSG_ID_THRUSTER_LOCK_LEN, MAVLINK_MSG_ID_THRUSTER_LOCK_CRC);
}

/**
 * @brief Encode a thruster_lock struct
 *
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param msg The MAVLink message to compress the data into
 * @param thruster_lock C-struct to read the message contents from
 */
static inline uint16_t mavlink_msg_thruster_lock_encode(uint8_t system_id, uint8_t component_id, mavlink_message_t* msg, const mavlink_thruster_lock_t* thruster_lock)
{
    return mavlink_msg_thruster_lock_pack(system_id, component_id, msg, thruster_lock->lock);
}

/**
 * @brief Encode a thruster_lock struct on a channel
 *
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param chan The MAVLink channel this message will be sent over
 * @param msg The MAVLink message to compress the data into
 * @param thruster_lock C-struct to read the message contents from
 */
static inline uint16_t mavlink_msg_thruster_lock_encode_chan(uint8_t system_id, uint8_t component_id, uint8_t chan, mavlink_message_t* msg, const mavlink_thruster_lock_t* thruster_lock)
{
    return mavlink_msg_thruster_lock_pack_chan(system_id, component_id, chan, msg, thruster_lock->lock);
}

/**
 * @brief Encode a thruster_lock struct with provided status structure
 *
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param status MAVLink status structure
 * @param msg The MAVLink message to compress the data into
 * @param thruster_lock C-struct to read the message contents from
 */
static inline uint16_t mavlink_msg_thruster_lock_encode_status(uint8_t system_id, uint8_t component_id, mavlink_status_t* _status, mavlink_message_t* msg, const mavlink_thruster_lock_t* thruster_lock)
{
    return mavlink_msg_thruster_lock_pack_status(system_id, component_id, _status, msg,  thruster_lock->lock);
}

/**
 * @brief Send a thruster_lock message
 * @param chan MAVLink channel to send the message
 *
 * @param lock  Lock command: 0 unlock, 1 lock.
 */
#ifdef MAVLINK_USE_CONVENIENCE_FUNCTIONS

static inline void mavlink_msg_thruster_lock_send(mavlink_channel_t chan, uint8_t lock)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    char buf[MAVLINK_MSG_ID_THRUSTER_LOCK_LEN];
    _mav_put_uint8_t(buf, 0, lock);

    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_THRUSTER_LOCK, buf, MAVLINK_MSG_ID_THRUSTER_LOCK_MIN_LEN, MAVLINK_MSG_ID_THRUSTER_LOCK_LEN, MAVLINK_MSG_ID_THRUSTER_LOCK_CRC);
#else
    mavlink_thruster_lock_t packet;
    packet.lock = lock;

    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_THRUSTER_LOCK, (const char *)&packet, MAVLINK_MSG_ID_THRUSTER_LOCK_MIN_LEN, MAVLINK_MSG_ID_THRUSTER_LOCK_LEN, MAVLINK_MSG_ID_THRUSTER_LOCK_CRC);
#endif
}

/**
 * @brief Send a thruster_lock message
 * @param chan MAVLink channel to send the message
 * @param struct The MAVLink struct to serialize
 */
static inline void mavlink_msg_thruster_lock_send_struct(mavlink_channel_t chan, const mavlink_thruster_lock_t* thruster_lock)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    mavlink_msg_thruster_lock_send(chan, thruster_lock->lock);
#else
    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_THRUSTER_LOCK, (const char *)thruster_lock, MAVLINK_MSG_ID_THRUSTER_LOCK_MIN_LEN, MAVLINK_MSG_ID_THRUSTER_LOCK_LEN, MAVLINK_MSG_ID_THRUSTER_LOCK_CRC);
#endif
}

#if MAVLINK_MSG_ID_THRUSTER_LOCK_LEN <= MAVLINK_MAX_PAYLOAD_LEN
/*
  This variant of _send() can be used to save stack space by reusing
  memory from the receive buffer.  The caller provides a
  mavlink_message_t which is the size of a full mavlink message. This
  is usually the receive buffer for the channel, and allows a reply to an
  incoming message with minimum stack space usage.
 */
static inline void mavlink_msg_thruster_lock_send_buf(mavlink_message_t *msgbuf, mavlink_channel_t chan,  uint8_t lock)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    char *buf = (char *)msgbuf;
    _mav_put_uint8_t(buf, 0, lock);

    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_THRUSTER_LOCK, buf, MAVLINK_MSG_ID_THRUSTER_LOCK_MIN_LEN, MAVLINK_MSG_ID_THRUSTER_LOCK_LEN, MAVLINK_MSG_ID_THRUSTER_LOCK_CRC);
#else
    mavlink_thruster_lock_t *packet = (mavlink_thruster_lock_t *)msgbuf;
    packet->lock = lock;

    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_THRUSTER_LOCK, (const char *)packet, MAVLINK_MSG_ID_THRUSTER_LOCK_MIN_LEN, MAVLINK_MSG_ID_THRUSTER_LOCK_LEN, MAVLINK_MSG_ID_THRUSTER_LOCK_CRC);
#endif
}
#endif

#endif

// MESSAGE THRUSTER_LOCK UNPACKING


/**
 * @brief Get field lock from thruster_lock message
 *
 * @return  Lock command: 0 unlock, 1 lock.
 */
static inline uint8_t mavlink_msg_thruster_lock_get_lock(const mavlink_message_t* msg)
{
    return _MAV_RETURN_uint8_t(msg,  0);
}

/**
 * @brief Decode a thruster_lock message into a struct
 *
 * @param msg The message to decode
 * @param thruster_lock C-struct to decode the message contents into
 */
static inline void mavlink_msg_thruster_lock_decode(const mavlink_message_t* msg, mavlink_thruster_lock_t* thruster_lock)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    thruster_lock->lock = mavlink_msg_thruster_lock_get_lock(msg);
#else
        uint8_t len = msg->len < MAVLINK_MSG_ID_THRUSTER_LOCK_LEN? msg->len : MAVLINK_MSG_ID_THRUSTER_LOCK_LEN;
        memset(thruster_lock, 0, MAVLINK_MSG_ID_THRUSTER_LOCK_LEN);
    memcpy(thruster_lock, _MAV_PAYLOAD(msg), len);
#endif
}
