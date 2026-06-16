#pragma once
// MESSAGE LED_STATUS PACKING

#define MAVLINK_MSG_ID_LED_STATUS 4


typedef struct __mavlink_led_status_t {
 uint32_t timestamp_ms; /*< [ms] Timestamp from the sender clock.*/
 uint8_t ledpwm1; /*< [%] LED channel 1 duty cycle.*/
 uint8_t ledpwm2; /*< [%] LED channel 2 duty cycle.*/
 uint8_t ledpwm3; /*< [%] LED channel 3 duty cycle.*/
 uint8_t ledpwm4; /*< [%] LED channel 4 duty cycle.*/
 uint8_t ledpwm5; /*< [%] LED channel 5 duty cycle.*/
 uint8_t ledpwm6; /*< [%] LED channel 6 duty cycle.*/
 uint8_t ledpwm7; /*< [%] LED channel 7 duty cycle.*/
 uint8_t ledpwm8; /*< [%] LED channel 8 duty cycle.*/
 uint8_t ledpwm9; /*< [%] LED channel 9 duty cycle.*/
 uint8_t ledpwm10; /*< [%] LED channel 10 duty cycle.*/
} mavlink_led_status_t;

#define MAVLINK_MSG_ID_LED_STATUS_LEN 14
#define MAVLINK_MSG_ID_LED_STATUS_MIN_LEN 14
#define MAVLINK_MSG_ID_4_LEN 14
#define MAVLINK_MSG_ID_4_MIN_LEN 14

#define MAVLINK_MSG_ID_LED_STATUS_CRC 32
#define MAVLINK_MSG_ID_4_CRC 32



#if MAVLINK_COMMAND_24BIT
#define MAVLINK_MESSAGE_INFO_LED_STATUS { \
    4, \
    "LED_STATUS", \
    11, \
    {  { "timestamp_ms", NULL, MAVLINK_TYPE_UINT32_T, 0, 0, offsetof(mavlink_led_status_t, timestamp_ms) }, \
         { "ledpwm1", NULL, MAVLINK_TYPE_UINT8_T, 0, 4, offsetof(mavlink_led_status_t, ledpwm1) }, \
         { "ledpwm2", NULL, MAVLINK_TYPE_UINT8_T, 0, 5, offsetof(mavlink_led_status_t, ledpwm2) }, \
         { "ledpwm3", NULL, MAVLINK_TYPE_UINT8_T, 0, 6, offsetof(mavlink_led_status_t, ledpwm3) }, \
         { "ledpwm4", NULL, MAVLINK_TYPE_UINT8_T, 0, 7, offsetof(mavlink_led_status_t, ledpwm4) }, \
         { "ledpwm5", NULL, MAVLINK_TYPE_UINT8_T, 0, 8, offsetof(mavlink_led_status_t, ledpwm5) }, \
         { "ledpwm6", NULL, MAVLINK_TYPE_UINT8_T, 0, 9, offsetof(mavlink_led_status_t, ledpwm6) }, \
         { "ledpwm7", NULL, MAVLINK_TYPE_UINT8_T, 0, 10, offsetof(mavlink_led_status_t, ledpwm7) }, \
         { "ledpwm8", NULL, MAVLINK_TYPE_UINT8_T, 0, 11, offsetof(mavlink_led_status_t, ledpwm8) }, \
         { "ledpwm9", NULL, MAVLINK_TYPE_UINT8_T, 0, 12, offsetof(mavlink_led_status_t, ledpwm9) }, \
         { "ledpwm10", NULL, MAVLINK_TYPE_UINT8_T, 0, 13, offsetof(mavlink_led_status_t, ledpwm10) }, \
         } \
}
#else
#define MAVLINK_MESSAGE_INFO_LED_STATUS { \
    "LED_STATUS", \
    11, \
    {  { "timestamp_ms", NULL, MAVLINK_TYPE_UINT32_T, 0, 0, offsetof(mavlink_led_status_t, timestamp_ms) }, \
         { "ledpwm1", NULL, MAVLINK_TYPE_UINT8_T, 0, 4, offsetof(mavlink_led_status_t, ledpwm1) }, \
         { "ledpwm2", NULL, MAVLINK_TYPE_UINT8_T, 0, 5, offsetof(mavlink_led_status_t, ledpwm2) }, \
         { "ledpwm3", NULL, MAVLINK_TYPE_UINT8_T, 0, 6, offsetof(mavlink_led_status_t, ledpwm3) }, \
         { "ledpwm4", NULL, MAVLINK_TYPE_UINT8_T, 0, 7, offsetof(mavlink_led_status_t, ledpwm4) }, \
         { "ledpwm5", NULL, MAVLINK_TYPE_UINT8_T, 0, 8, offsetof(mavlink_led_status_t, ledpwm5) }, \
         { "ledpwm6", NULL, MAVLINK_TYPE_UINT8_T, 0, 9, offsetof(mavlink_led_status_t, ledpwm6) }, \
         { "ledpwm7", NULL, MAVLINK_TYPE_UINT8_T, 0, 10, offsetof(mavlink_led_status_t, ledpwm7) }, \
         { "ledpwm8", NULL, MAVLINK_TYPE_UINT8_T, 0, 11, offsetof(mavlink_led_status_t, ledpwm8) }, \
         { "ledpwm9", NULL, MAVLINK_TYPE_UINT8_T, 0, 12, offsetof(mavlink_led_status_t, ledpwm9) }, \
         { "ledpwm10", NULL, MAVLINK_TYPE_UINT8_T, 0, 13, offsetof(mavlink_led_status_t, ledpwm10) }, \
         } \
}
#endif

/**
 * @brief Pack a led_status message
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param msg The MAVLink message to compress the data into
 *
 * @param timestamp_ms [ms] Timestamp from the sender clock.
 * @param ledpwm1 [%] LED channel 1 duty cycle.
 * @param ledpwm2 [%] LED channel 2 duty cycle.
 * @param ledpwm3 [%] LED channel 3 duty cycle.
 * @param ledpwm4 [%] LED channel 4 duty cycle.
 * @param ledpwm5 [%] LED channel 5 duty cycle.
 * @param ledpwm6 [%] LED channel 6 duty cycle.
 * @param ledpwm7 [%] LED channel 7 duty cycle.
 * @param ledpwm8 [%] LED channel 8 duty cycle.
 * @param ledpwm9 [%] LED channel 9 duty cycle.
 * @param ledpwm10 [%] LED channel 10 duty cycle.
 * @return length of the message in bytes (excluding serial stream start sign)
 */
static inline uint16_t mavlink_msg_led_status_pack(uint8_t system_id, uint8_t component_id, mavlink_message_t* msg,
                               uint32_t timestamp_ms, uint8_t ledpwm1, uint8_t ledpwm2, uint8_t ledpwm3, uint8_t ledpwm4, uint8_t ledpwm5, uint8_t ledpwm6, uint8_t ledpwm7, uint8_t ledpwm8, uint8_t ledpwm9, uint8_t ledpwm10)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    char buf[MAVLINK_MSG_ID_LED_STATUS_LEN];
    _mav_put_uint32_t(buf, 0, timestamp_ms);
    _mav_put_uint8_t(buf, 4, ledpwm1);
    _mav_put_uint8_t(buf, 5, ledpwm2);
    _mav_put_uint8_t(buf, 6, ledpwm3);
    _mav_put_uint8_t(buf, 7, ledpwm4);
    _mav_put_uint8_t(buf, 8, ledpwm5);
    _mav_put_uint8_t(buf, 9, ledpwm6);
    _mav_put_uint8_t(buf, 10, ledpwm7);
    _mav_put_uint8_t(buf, 11, ledpwm8);
    _mav_put_uint8_t(buf, 12, ledpwm9);
    _mav_put_uint8_t(buf, 13, ledpwm10);

        memcpy(_MAV_PAYLOAD_NON_CONST(msg), buf, MAVLINK_MSG_ID_LED_STATUS_LEN);
#else
    mavlink_led_status_t packet;
    packet.timestamp_ms = timestamp_ms;
    packet.ledpwm1 = ledpwm1;
    packet.ledpwm2 = ledpwm2;
    packet.ledpwm3 = ledpwm3;
    packet.ledpwm4 = ledpwm4;
    packet.ledpwm5 = ledpwm5;
    packet.ledpwm6 = ledpwm6;
    packet.ledpwm7 = ledpwm7;
    packet.ledpwm8 = ledpwm8;
    packet.ledpwm9 = ledpwm9;
    packet.ledpwm10 = ledpwm10;

        memcpy(_MAV_PAYLOAD_NON_CONST(msg), &packet, MAVLINK_MSG_ID_LED_STATUS_LEN);
#endif

    msg->msgid = MAVLINK_MSG_ID_LED_STATUS;
    return mavlink_finalize_message(msg, system_id, component_id, MAVLINK_MSG_ID_LED_STATUS_MIN_LEN, MAVLINK_MSG_ID_LED_STATUS_LEN, MAVLINK_MSG_ID_LED_STATUS_CRC);
}

/**
 * @brief Pack a led_status message
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param status MAVLink status structure
 * @param msg The MAVLink message to compress the data into
 *
 * @param timestamp_ms [ms] Timestamp from the sender clock.
 * @param ledpwm1 [%] LED channel 1 duty cycle.
 * @param ledpwm2 [%] LED channel 2 duty cycle.
 * @param ledpwm3 [%] LED channel 3 duty cycle.
 * @param ledpwm4 [%] LED channel 4 duty cycle.
 * @param ledpwm5 [%] LED channel 5 duty cycle.
 * @param ledpwm6 [%] LED channel 6 duty cycle.
 * @param ledpwm7 [%] LED channel 7 duty cycle.
 * @param ledpwm8 [%] LED channel 8 duty cycle.
 * @param ledpwm9 [%] LED channel 9 duty cycle.
 * @param ledpwm10 [%] LED channel 10 duty cycle.
 * @return length of the message in bytes (excluding serial stream start sign)
 */
static inline uint16_t mavlink_msg_led_status_pack_status(uint8_t system_id, uint8_t component_id, mavlink_status_t *_status, mavlink_message_t* msg,
                               uint32_t timestamp_ms, uint8_t ledpwm1, uint8_t ledpwm2, uint8_t ledpwm3, uint8_t ledpwm4, uint8_t ledpwm5, uint8_t ledpwm6, uint8_t ledpwm7, uint8_t ledpwm8, uint8_t ledpwm9, uint8_t ledpwm10)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    char buf[MAVLINK_MSG_ID_LED_STATUS_LEN];
    _mav_put_uint32_t(buf, 0, timestamp_ms);
    _mav_put_uint8_t(buf, 4, ledpwm1);
    _mav_put_uint8_t(buf, 5, ledpwm2);
    _mav_put_uint8_t(buf, 6, ledpwm3);
    _mav_put_uint8_t(buf, 7, ledpwm4);
    _mav_put_uint8_t(buf, 8, ledpwm5);
    _mav_put_uint8_t(buf, 9, ledpwm6);
    _mav_put_uint8_t(buf, 10, ledpwm7);
    _mav_put_uint8_t(buf, 11, ledpwm8);
    _mav_put_uint8_t(buf, 12, ledpwm9);
    _mav_put_uint8_t(buf, 13, ledpwm10);

        memcpy(_MAV_PAYLOAD_NON_CONST(msg), buf, MAVLINK_MSG_ID_LED_STATUS_LEN);
#else
    mavlink_led_status_t packet;
    packet.timestamp_ms = timestamp_ms;
    packet.ledpwm1 = ledpwm1;
    packet.ledpwm2 = ledpwm2;
    packet.ledpwm3 = ledpwm3;
    packet.ledpwm4 = ledpwm4;
    packet.ledpwm5 = ledpwm5;
    packet.ledpwm6 = ledpwm6;
    packet.ledpwm7 = ledpwm7;
    packet.ledpwm8 = ledpwm8;
    packet.ledpwm9 = ledpwm9;
    packet.ledpwm10 = ledpwm10;

        memcpy(_MAV_PAYLOAD_NON_CONST(msg), &packet, MAVLINK_MSG_ID_LED_STATUS_LEN);
#endif

    msg->msgid = MAVLINK_MSG_ID_LED_STATUS;
#if MAVLINK_CRC_EXTRA
    return mavlink_finalize_message_buffer(msg, system_id, component_id, _status, MAVLINK_MSG_ID_LED_STATUS_MIN_LEN, MAVLINK_MSG_ID_LED_STATUS_LEN, MAVLINK_MSG_ID_LED_STATUS_CRC);
#else
    return mavlink_finalize_message_buffer(msg, system_id, component_id, _status, MAVLINK_MSG_ID_LED_STATUS_MIN_LEN, MAVLINK_MSG_ID_LED_STATUS_LEN);
#endif
}

/**
 * @brief Pack a led_status message on a channel
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param chan The MAVLink channel this message will be sent over
 * @param msg The MAVLink message to compress the data into
 * @param timestamp_ms [ms] Timestamp from the sender clock.
 * @param ledpwm1 [%] LED channel 1 duty cycle.
 * @param ledpwm2 [%] LED channel 2 duty cycle.
 * @param ledpwm3 [%] LED channel 3 duty cycle.
 * @param ledpwm4 [%] LED channel 4 duty cycle.
 * @param ledpwm5 [%] LED channel 5 duty cycle.
 * @param ledpwm6 [%] LED channel 6 duty cycle.
 * @param ledpwm7 [%] LED channel 7 duty cycle.
 * @param ledpwm8 [%] LED channel 8 duty cycle.
 * @param ledpwm9 [%] LED channel 9 duty cycle.
 * @param ledpwm10 [%] LED channel 10 duty cycle.
 * @return length of the message in bytes (excluding serial stream start sign)
 */
static inline uint16_t mavlink_msg_led_status_pack_chan(uint8_t system_id, uint8_t component_id, uint8_t chan,
                               mavlink_message_t* msg,
                                   uint32_t timestamp_ms,uint8_t ledpwm1,uint8_t ledpwm2,uint8_t ledpwm3,uint8_t ledpwm4,uint8_t ledpwm5,uint8_t ledpwm6,uint8_t ledpwm7,uint8_t ledpwm8,uint8_t ledpwm9,uint8_t ledpwm10)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    char buf[MAVLINK_MSG_ID_LED_STATUS_LEN];
    _mav_put_uint32_t(buf, 0, timestamp_ms);
    _mav_put_uint8_t(buf, 4, ledpwm1);
    _mav_put_uint8_t(buf, 5, ledpwm2);
    _mav_put_uint8_t(buf, 6, ledpwm3);
    _mav_put_uint8_t(buf, 7, ledpwm4);
    _mav_put_uint8_t(buf, 8, ledpwm5);
    _mav_put_uint8_t(buf, 9, ledpwm6);
    _mav_put_uint8_t(buf, 10, ledpwm7);
    _mav_put_uint8_t(buf, 11, ledpwm8);
    _mav_put_uint8_t(buf, 12, ledpwm9);
    _mav_put_uint8_t(buf, 13, ledpwm10);

        memcpy(_MAV_PAYLOAD_NON_CONST(msg), buf, MAVLINK_MSG_ID_LED_STATUS_LEN);
#else
    mavlink_led_status_t packet;
    packet.timestamp_ms = timestamp_ms;
    packet.ledpwm1 = ledpwm1;
    packet.ledpwm2 = ledpwm2;
    packet.ledpwm3 = ledpwm3;
    packet.ledpwm4 = ledpwm4;
    packet.ledpwm5 = ledpwm5;
    packet.ledpwm6 = ledpwm6;
    packet.ledpwm7 = ledpwm7;
    packet.ledpwm8 = ledpwm8;
    packet.ledpwm9 = ledpwm9;
    packet.ledpwm10 = ledpwm10;

        memcpy(_MAV_PAYLOAD_NON_CONST(msg), &packet, MAVLINK_MSG_ID_LED_STATUS_LEN);
#endif

    msg->msgid = MAVLINK_MSG_ID_LED_STATUS;
    return mavlink_finalize_message_chan(msg, system_id, component_id, chan, MAVLINK_MSG_ID_LED_STATUS_MIN_LEN, MAVLINK_MSG_ID_LED_STATUS_LEN, MAVLINK_MSG_ID_LED_STATUS_CRC);
}

/**
 * @brief Encode a led_status struct
 *
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param msg The MAVLink message to compress the data into
 * @param led_status C-struct to read the message contents from
 */
static inline uint16_t mavlink_msg_led_status_encode(uint8_t system_id, uint8_t component_id, mavlink_message_t* msg, const mavlink_led_status_t* led_status)
{
    return mavlink_msg_led_status_pack(system_id, component_id, msg, led_status->timestamp_ms, led_status->ledpwm1, led_status->ledpwm2, led_status->ledpwm3, led_status->ledpwm4, led_status->ledpwm5, led_status->ledpwm6, led_status->ledpwm7, led_status->ledpwm8, led_status->ledpwm9, led_status->ledpwm10);
}

/**
 * @brief Encode a led_status struct on a channel
 *
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param chan The MAVLink channel this message will be sent over
 * @param msg The MAVLink message to compress the data into
 * @param led_status C-struct to read the message contents from
 */
static inline uint16_t mavlink_msg_led_status_encode_chan(uint8_t system_id, uint8_t component_id, uint8_t chan, mavlink_message_t* msg, const mavlink_led_status_t* led_status)
{
    return mavlink_msg_led_status_pack_chan(system_id, component_id, chan, msg, led_status->timestamp_ms, led_status->ledpwm1, led_status->ledpwm2, led_status->ledpwm3, led_status->ledpwm4, led_status->ledpwm5, led_status->ledpwm6, led_status->ledpwm7, led_status->ledpwm8, led_status->ledpwm9, led_status->ledpwm10);
}

/**
 * @brief Encode a led_status struct with provided status structure
 *
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param status MAVLink status structure
 * @param msg The MAVLink message to compress the data into
 * @param led_status C-struct to read the message contents from
 */
static inline uint16_t mavlink_msg_led_status_encode_status(uint8_t system_id, uint8_t component_id, mavlink_status_t* _status, mavlink_message_t* msg, const mavlink_led_status_t* led_status)
{
    return mavlink_msg_led_status_pack_status(system_id, component_id, _status, msg,  led_status->timestamp_ms, led_status->ledpwm1, led_status->ledpwm2, led_status->ledpwm3, led_status->ledpwm4, led_status->ledpwm5, led_status->ledpwm6, led_status->ledpwm7, led_status->ledpwm8, led_status->ledpwm9, led_status->ledpwm10);
}

/**
 * @brief Send a led_status message
 * @param chan MAVLink channel to send the message
 *
 * @param timestamp_ms [ms] Timestamp from the sender clock.
 * @param ledpwm1 [%] LED channel 1 duty cycle.
 * @param ledpwm2 [%] LED channel 2 duty cycle.
 * @param ledpwm3 [%] LED channel 3 duty cycle.
 * @param ledpwm4 [%] LED channel 4 duty cycle.
 * @param ledpwm5 [%] LED channel 5 duty cycle.
 * @param ledpwm6 [%] LED channel 6 duty cycle.
 * @param ledpwm7 [%] LED channel 7 duty cycle.
 * @param ledpwm8 [%] LED channel 8 duty cycle.
 * @param ledpwm9 [%] LED channel 9 duty cycle.
 * @param ledpwm10 [%] LED channel 10 duty cycle.
 */
#ifdef MAVLINK_USE_CONVENIENCE_FUNCTIONS

static inline void mavlink_msg_led_status_send(mavlink_channel_t chan, uint32_t timestamp_ms, uint8_t ledpwm1, uint8_t ledpwm2, uint8_t ledpwm3, uint8_t ledpwm4, uint8_t ledpwm5, uint8_t ledpwm6, uint8_t ledpwm7, uint8_t ledpwm8, uint8_t ledpwm9, uint8_t ledpwm10)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    char buf[MAVLINK_MSG_ID_LED_STATUS_LEN];
    _mav_put_uint32_t(buf, 0, timestamp_ms);
    _mav_put_uint8_t(buf, 4, ledpwm1);
    _mav_put_uint8_t(buf, 5, ledpwm2);
    _mav_put_uint8_t(buf, 6, ledpwm3);
    _mav_put_uint8_t(buf, 7, ledpwm4);
    _mav_put_uint8_t(buf, 8, ledpwm5);
    _mav_put_uint8_t(buf, 9, ledpwm6);
    _mav_put_uint8_t(buf, 10, ledpwm7);
    _mav_put_uint8_t(buf, 11, ledpwm8);
    _mav_put_uint8_t(buf, 12, ledpwm9);
    _mav_put_uint8_t(buf, 13, ledpwm10);

    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_LED_STATUS, buf, MAVLINK_MSG_ID_LED_STATUS_MIN_LEN, MAVLINK_MSG_ID_LED_STATUS_LEN, MAVLINK_MSG_ID_LED_STATUS_CRC);
#else
    mavlink_led_status_t packet;
    packet.timestamp_ms = timestamp_ms;
    packet.ledpwm1 = ledpwm1;
    packet.ledpwm2 = ledpwm2;
    packet.ledpwm3 = ledpwm3;
    packet.ledpwm4 = ledpwm4;
    packet.ledpwm5 = ledpwm5;
    packet.ledpwm6 = ledpwm6;
    packet.ledpwm7 = ledpwm7;
    packet.ledpwm8 = ledpwm8;
    packet.ledpwm9 = ledpwm9;
    packet.ledpwm10 = ledpwm10;

    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_LED_STATUS, (const char *)&packet, MAVLINK_MSG_ID_LED_STATUS_MIN_LEN, MAVLINK_MSG_ID_LED_STATUS_LEN, MAVLINK_MSG_ID_LED_STATUS_CRC);
#endif
}

/**
 * @brief Send a led_status message
 * @param chan MAVLink channel to send the message
 * @param struct The MAVLink struct to serialize
 */
static inline void mavlink_msg_led_status_send_struct(mavlink_channel_t chan, const mavlink_led_status_t* led_status)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    mavlink_msg_led_status_send(chan, led_status->timestamp_ms, led_status->ledpwm1, led_status->ledpwm2, led_status->ledpwm3, led_status->ledpwm4, led_status->ledpwm5, led_status->ledpwm6, led_status->ledpwm7, led_status->ledpwm8, led_status->ledpwm9, led_status->ledpwm10);
#else
    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_LED_STATUS, (const char *)led_status, MAVLINK_MSG_ID_LED_STATUS_MIN_LEN, MAVLINK_MSG_ID_LED_STATUS_LEN, MAVLINK_MSG_ID_LED_STATUS_CRC);
#endif
}

#if MAVLINK_MSG_ID_LED_STATUS_LEN <= MAVLINK_MAX_PAYLOAD_LEN
/*
  This variant of _send() can be used to save stack space by reusing
  memory from the receive buffer.  The caller provides a
  mavlink_message_t which is the size of a full mavlink message. This
  is usually the receive buffer for the channel, and allows a reply to an
  incoming message with minimum stack space usage.
 */
static inline void mavlink_msg_led_status_send_buf(mavlink_message_t *msgbuf, mavlink_channel_t chan,  uint32_t timestamp_ms, uint8_t ledpwm1, uint8_t ledpwm2, uint8_t ledpwm3, uint8_t ledpwm4, uint8_t ledpwm5, uint8_t ledpwm6, uint8_t ledpwm7, uint8_t ledpwm8, uint8_t ledpwm9, uint8_t ledpwm10)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    char *buf = (char *)msgbuf;
    _mav_put_uint32_t(buf, 0, timestamp_ms);
    _mav_put_uint8_t(buf, 4, ledpwm1);
    _mav_put_uint8_t(buf, 5, ledpwm2);
    _mav_put_uint8_t(buf, 6, ledpwm3);
    _mav_put_uint8_t(buf, 7, ledpwm4);
    _mav_put_uint8_t(buf, 8, ledpwm5);
    _mav_put_uint8_t(buf, 9, ledpwm6);
    _mav_put_uint8_t(buf, 10, ledpwm7);
    _mav_put_uint8_t(buf, 11, ledpwm8);
    _mav_put_uint8_t(buf, 12, ledpwm9);
    _mav_put_uint8_t(buf, 13, ledpwm10);

    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_LED_STATUS, buf, MAVLINK_MSG_ID_LED_STATUS_MIN_LEN, MAVLINK_MSG_ID_LED_STATUS_LEN, MAVLINK_MSG_ID_LED_STATUS_CRC);
#else
    mavlink_led_status_t *packet = (mavlink_led_status_t *)msgbuf;
    packet->timestamp_ms = timestamp_ms;
    packet->ledpwm1 = ledpwm1;
    packet->ledpwm2 = ledpwm2;
    packet->ledpwm3 = ledpwm3;
    packet->ledpwm4 = ledpwm4;
    packet->ledpwm5 = ledpwm5;
    packet->ledpwm6 = ledpwm6;
    packet->ledpwm7 = ledpwm7;
    packet->ledpwm8 = ledpwm8;
    packet->ledpwm9 = ledpwm9;
    packet->ledpwm10 = ledpwm10;

    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_LED_STATUS, (const char *)packet, MAVLINK_MSG_ID_LED_STATUS_MIN_LEN, MAVLINK_MSG_ID_LED_STATUS_LEN, MAVLINK_MSG_ID_LED_STATUS_CRC);
#endif
}
#endif

#endif

// MESSAGE LED_STATUS UNPACKING


/**
 * @brief Get field timestamp_ms from led_status message
 *
 * @return [ms] Timestamp from the sender clock.
 */
static inline uint32_t mavlink_msg_led_status_get_timestamp_ms(const mavlink_message_t* msg)
{
    return _MAV_RETURN_uint32_t(msg,  0);
}

/**
 * @brief Get field ledpwm1 from led_status message
 *
 * @return [%] LED channel 1 duty cycle.
 */
static inline uint8_t mavlink_msg_led_status_get_ledpwm1(const mavlink_message_t* msg)
{
    return _MAV_RETURN_uint8_t(msg,  4);
}

/**
 * @brief Get field ledpwm2 from led_status message
 *
 * @return [%] LED channel 2 duty cycle.
 */
static inline uint8_t mavlink_msg_led_status_get_ledpwm2(const mavlink_message_t* msg)
{
    return _MAV_RETURN_uint8_t(msg,  5);
}

/**
 * @brief Get field ledpwm3 from led_status message
 *
 * @return [%] LED channel 3 duty cycle.
 */
static inline uint8_t mavlink_msg_led_status_get_ledpwm3(const mavlink_message_t* msg)
{
    return _MAV_RETURN_uint8_t(msg,  6);
}

/**
 * @brief Get field ledpwm4 from led_status message
 *
 * @return [%] LED channel 4 duty cycle.
 */
static inline uint8_t mavlink_msg_led_status_get_ledpwm4(const mavlink_message_t* msg)
{
    return _MAV_RETURN_uint8_t(msg,  7);
}

/**
 * @brief Get field ledpwm5 from led_status message
 *
 * @return [%] LED channel 5 duty cycle.
 */
static inline uint8_t mavlink_msg_led_status_get_ledpwm5(const mavlink_message_t* msg)
{
    return _MAV_RETURN_uint8_t(msg,  8);
}

/**
 * @brief Get field ledpwm6 from led_status message
 *
 * @return [%] LED channel 6 duty cycle.
 */
static inline uint8_t mavlink_msg_led_status_get_ledpwm6(const mavlink_message_t* msg)
{
    return _MAV_RETURN_uint8_t(msg,  9);
}

/**
 * @brief Get field ledpwm7 from led_status message
 *
 * @return [%] LED channel 7 duty cycle.
 */
static inline uint8_t mavlink_msg_led_status_get_ledpwm7(const mavlink_message_t* msg)
{
    return _MAV_RETURN_uint8_t(msg,  10);
}

/**
 * @brief Get field ledpwm8 from led_status message
 *
 * @return [%] LED channel 8 duty cycle.
 */
static inline uint8_t mavlink_msg_led_status_get_ledpwm8(const mavlink_message_t* msg)
{
    return _MAV_RETURN_uint8_t(msg,  11);
}

/**
 * @brief Get field ledpwm9 from led_status message
 *
 * @return [%] LED channel 9 duty cycle.
 */
static inline uint8_t mavlink_msg_led_status_get_ledpwm9(const mavlink_message_t* msg)
{
    return _MAV_RETURN_uint8_t(msg,  12);
}

/**
 * @brief Get field ledpwm10 from led_status message
 *
 * @return [%] LED channel 10 duty cycle.
 */
static inline uint8_t mavlink_msg_led_status_get_ledpwm10(const mavlink_message_t* msg)
{
    return _MAV_RETURN_uint8_t(msg,  13);
}

/**
 * @brief Decode a led_status message into a struct
 *
 * @param msg The message to decode
 * @param led_status C-struct to decode the message contents into
 */
static inline void mavlink_msg_led_status_decode(const mavlink_message_t* msg, mavlink_led_status_t* led_status)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    led_status->timestamp_ms = mavlink_msg_led_status_get_timestamp_ms(msg);
    led_status->ledpwm1 = mavlink_msg_led_status_get_ledpwm1(msg);
    led_status->ledpwm2 = mavlink_msg_led_status_get_ledpwm2(msg);
    led_status->ledpwm3 = mavlink_msg_led_status_get_ledpwm3(msg);
    led_status->ledpwm4 = mavlink_msg_led_status_get_ledpwm4(msg);
    led_status->ledpwm5 = mavlink_msg_led_status_get_ledpwm5(msg);
    led_status->ledpwm6 = mavlink_msg_led_status_get_ledpwm6(msg);
    led_status->ledpwm7 = mavlink_msg_led_status_get_ledpwm7(msg);
    led_status->ledpwm8 = mavlink_msg_led_status_get_ledpwm8(msg);
    led_status->ledpwm9 = mavlink_msg_led_status_get_ledpwm9(msg);
    led_status->ledpwm10 = mavlink_msg_led_status_get_ledpwm10(msg);
#else
        uint8_t len = msg->len < MAVLINK_MSG_ID_LED_STATUS_LEN? msg->len : MAVLINK_MSG_ID_LED_STATUS_LEN;
        memset(led_status, 0, MAVLINK_MSG_ID_LED_STATUS_LEN);
    memcpy(led_status, _MAV_PAYLOAD(msg), len);
#endif
}
