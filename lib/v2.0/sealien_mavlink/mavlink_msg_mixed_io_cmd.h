#pragma once
// MESSAGE MIXED_IO_CMD PACKING

#define MAVLINK_MSG_ID_MIXED_IO_CMD 19


typedef struct __mavlink_mixed_io_cmd_t {
 uint32_t gpio_1_32_output; /*<  GPIO outputs 1-32 bitmap. Bit 0 maps to GPIO 1; bit value 0 drives low and 1 drives high.*/
 uint32_t gpio_33_64_output; /*<  GPIO outputs 33-64 bitmap. Bit 0 maps to GPIO 33; bit value 0 drives low and 1 drives high.*/
 float dac_dev1_Vout[4]; /*< [V] DAC device 1 output voltage: indexes 0-3 map to Vout_A through Vout_D.*/
 float dac_dev2_Vout[4]; /*< [V] DAC device 2 output voltage: indexes 0-3 map to Vout_A through Vout_D.*/
 float dac_dev3_Vout[4]; /*< [V] DAC device 3 output voltage: indexes 0-3 map to Vout_A through Vout_D.*/
} mavlink_mixed_io_cmd_t;

#define MAVLINK_MSG_ID_MIXED_IO_CMD_LEN 56
#define MAVLINK_MSG_ID_MIXED_IO_CMD_MIN_LEN 56
#define MAVLINK_MSG_ID_19_LEN 56
#define MAVLINK_MSG_ID_19_MIN_LEN 56

#define MAVLINK_MSG_ID_MIXED_IO_CMD_CRC 173
#define MAVLINK_MSG_ID_19_CRC 173

#define MAVLINK_MSG_MIXED_IO_CMD_FIELD_DAC_DEV1_VOUT_LEN 4
#define MAVLINK_MSG_MIXED_IO_CMD_FIELD_DAC_DEV2_VOUT_LEN 4
#define MAVLINK_MSG_MIXED_IO_CMD_FIELD_DAC_DEV3_VOUT_LEN 4

#if MAVLINK_COMMAND_24BIT
#define MAVLINK_MESSAGE_INFO_MIXED_IO_CMD { \
    19, \
    "MIXED_IO_CMD", \
    5, \
    {  { "gpio_1_32_output", NULL, MAVLINK_TYPE_UINT32_T, 0, 0, offsetof(mavlink_mixed_io_cmd_t, gpio_1_32_output) }, \
         { "gpio_33_64_output", NULL, MAVLINK_TYPE_UINT32_T, 0, 4, offsetof(mavlink_mixed_io_cmd_t, gpio_33_64_output) }, \
         { "dac_dev1_Vout", NULL, MAVLINK_TYPE_FLOAT, 4, 8, offsetof(mavlink_mixed_io_cmd_t, dac_dev1_Vout) }, \
         { "dac_dev2_Vout", NULL, MAVLINK_TYPE_FLOAT, 4, 24, offsetof(mavlink_mixed_io_cmd_t, dac_dev2_Vout) }, \
         { "dac_dev3_Vout", NULL, MAVLINK_TYPE_FLOAT, 4, 40, offsetof(mavlink_mixed_io_cmd_t, dac_dev3_Vout) }, \
         } \
}
#else
#define MAVLINK_MESSAGE_INFO_MIXED_IO_CMD { \
    "MIXED_IO_CMD", \
    5, \
    {  { "gpio_1_32_output", NULL, MAVLINK_TYPE_UINT32_T, 0, 0, offsetof(mavlink_mixed_io_cmd_t, gpio_1_32_output) }, \
         { "gpio_33_64_output", NULL, MAVLINK_TYPE_UINT32_T, 0, 4, offsetof(mavlink_mixed_io_cmd_t, gpio_33_64_output) }, \
         { "dac_dev1_Vout", NULL, MAVLINK_TYPE_FLOAT, 4, 8, offsetof(mavlink_mixed_io_cmd_t, dac_dev1_Vout) }, \
         { "dac_dev2_Vout", NULL, MAVLINK_TYPE_FLOAT, 4, 24, offsetof(mavlink_mixed_io_cmd_t, dac_dev2_Vout) }, \
         { "dac_dev3_Vout", NULL, MAVLINK_TYPE_FLOAT, 4, 40, offsetof(mavlink_mixed_io_cmd_t, dac_dev3_Vout) }, \
         } \
}
#endif

/**
 * @brief Pack a mixed_io_cmd message
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param msg The MAVLink message to compress the data into
 *
 * @param gpio_1_32_output  GPIO outputs 1-32 bitmap. Bit 0 maps to GPIO 1; bit value 0 drives low and 1 drives high.
 * @param gpio_33_64_output  GPIO outputs 33-64 bitmap. Bit 0 maps to GPIO 33; bit value 0 drives low and 1 drives high.
 * @param dac_dev1_Vout [V] DAC device 1 output voltage: indexes 0-3 map to Vout_A through Vout_D.
 * @param dac_dev2_Vout [V] DAC device 2 output voltage: indexes 0-3 map to Vout_A through Vout_D.
 * @param dac_dev3_Vout [V] DAC device 3 output voltage: indexes 0-3 map to Vout_A through Vout_D.
 * @return length of the message in bytes (excluding serial stream start sign)
 */
static inline uint16_t mavlink_msg_mixed_io_cmd_pack(uint8_t system_id, uint8_t component_id, mavlink_message_t* msg,
                               uint32_t gpio_1_32_output, uint32_t gpio_33_64_output, const float *dac_dev1_Vout, const float *dac_dev2_Vout, const float *dac_dev3_Vout)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    char buf[MAVLINK_MSG_ID_MIXED_IO_CMD_LEN];
    _mav_put_uint32_t(buf, 0, gpio_1_32_output);
    _mav_put_uint32_t(buf, 4, gpio_33_64_output);
    _mav_put_float_array(buf, 8, dac_dev1_Vout, 4);
    _mav_put_float_array(buf, 24, dac_dev2_Vout, 4);
    _mav_put_float_array(buf, 40, dac_dev3_Vout, 4);
        memcpy(_MAV_PAYLOAD_NON_CONST(msg), buf, MAVLINK_MSG_ID_MIXED_IO_CMD_LEN);
#else
    mavlink_mixed_io_cmd_t packet;
    packet.gpio_1_32_output = gpio_1_32_output;
    packet.gpio_33_64_output = gpio_33_64_output;
    mav_array_memcpy(packet.dac_dev1_Vout, dac_dev1_Vout, sizeof(float)*4);
    mav_array_memcpy(packet.dac_dev2_Vout, dac_dev2_Vout, sizeof(float)*4);
    mav_array_memcpy(packet.dac_dev3_Vout, dac_dev3_Vout, sizeof(float)*4);
        memcpy(_MAV_PAYLOAD_NON_CONST(msg), &packet, MAVLINK_MSG_ID_MIXED_IO_CMD_LEN);
#endif

    msg->msgid = MAVLINK_MSG_ID_MIXED_IO_CMD;
    return mavlink_finalize_message(msg, system_id, component_id, MAVLINK_MSG_ID_MIXED_IO_CMD_MIN_LEN, MAVLINK_MSG_ID_MIXED_IO_CMD_LEN, MAVLINK_MSG_ID_MIXED_IO_CMD_CRC);
}

/**
 * @brief Pack a mixed_io_cmd message
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param status MAVLink status structure
 * @param msg The MAVLink message to compress the data into
 *
 * @param gpio_1_32_output  GPIO outputs 1-32 bitmap. Bit 0 maps to GPIO 1; bit value 0 drives low and 1 drives high.
 * @param gpio_33_64_output  GPIO outputs 33-64 bitmap. Bit 0 maps to GPIO 33; bit value 0 drives low and 1 drives high.
 * @param dac_dev1_Vout [V] DAC device 1 output voltage: indexes 0-3 map to Vout_A through Vout_D.
 * @param dac_dev2_Vout [V] DAC device 2 output voltage: indexes 0-3 map to Vout_A through Vout_D.
 * @param dac_dev3_Vout [V] DAC device 3 output voltage: indexes 0-3 map to Vout_A through Vout_D.
 * @return length of the message in bytes (excluding serial stream start sign)
 */
static inline uint16_t mavlink_msg_mixed_io_cmd_pack_status(uint8_t system_id, uint8_t component_id, mavlink_status_t *_status, mavlink_message_t* msg,
                               uint32_t gpio_1_32_output, uint32_t gpio_33_64_output, const float *dac_dev1_Vout, const float *dac_dev2_Vout, const float *dac_dev3_Vout)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    char buf[MAVLINK_MSG_ID_MIXED_IO_CMD_LEN];
    _mav_put_uint32_t(buf, 0, gpio_1_32_output);
    _mav_put_uint32_t(buf, 4, gpio_33_64_output);
    _mav_put_float_array(buf, 8, dac_dev1_Vout, 4);
    _mav_put_float_array(buf, 24, dac_dev2_Vout, 4);
    _mav_put_float_array(buf, 40, dac_dev3_Vout, 4);
        memcpy(_MAV_PAYLOAD_NON_CONST(msg), buf, MAVLINK_MSG_ID_MIXED_IO_CMD_LEN);
#else
    mavlink_mixed_io_cmd_t packet;
    packet.gpio_1_32_output = gpio_1_32_output;
    packet.gpio_33_64_output = gpio_33_64_output;
    mav_array_memcpy(packet.dac_dev1_Vout, dac_dev1_Vout, sizeof(float)*4);
    mav_array_memcpy(packet.dac_dev2_Vout, dac_dev2_Vout, sizeof(float)*4);
    mav_array_memcpy(packet.dac_dev3_Vout, dac_dev3_Vout, sizeof(float)*4);
        memcpy(_MAV_PAYLOAD_NON_CONST(msg), &packet, MAVLINK_MSG_ID_MIXED_IO_CMD_LEN);
#endif

    msg->msgid = MAVLINK_MSG_ID_MIXED_IO_CMD;
#if MAVLINK_CRC_EXTRA
    return mavlink_finalize_message_buffer(msg, system_id, component_id, _status, MAVLINK_MSG_ID_MIXED_IO_CMD_MIN_LEN, MAVLINK_MSG_ID_MIXED_IO_CMD_LEN, MAVLINK_MSG_ID_MIXED_IO_CMD_CRC);
#else
    return mavlink_finalize_message_buffer(msg, system_id, component_id, _status, MAVLINK_MSG_ID_MIXED_IO_CMD_MIN_LEN, MAVLINK_MSG_ID_MIXED_IO_CMD_LEN);
#endif
}

/**
 * @brief Pack a mixed_io_cmd message on a channel
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param chan The MAVLink channel this message will be sent over
 * @param msg The MAVLink message to compress the data into
 * @param gpio_1_32_output  GPIO outputs 1-32 bitmap. Bit 0 maps to GPIO 1; bit value 0 drives low and 1 drives high.
 * @param gpio_33_64_output  GPIO outputs 33-64 bitmap. Bit 0 maps to GPIO 33; bit value 0 drives low and 1 drives high.
 * @param dac_dev1_Vout [V] DAC device 1 output voltage: indexes 0-3 map to Vout_A through Vout_D.
 * @param dac_dev2_Vout [V] DAC device 2 output voltage: indexes 0-3 map to Vout_A through Vout_D.
 * @param dac_dev3_Vout [V] DAC device 3 output voltage: indexes 0-3 map to Vout_A through Vout_D.
 * @return length of the message in bytes (excluding serial stream start sign)
 */
static inline uint16_t mavlink_msg_mixed_io_cmd_pack_chan(uint8_t system_id, uint8_t component_id, uint8_t chan,
                               mavlink_message_t* msg,
                                   uint32_t gpio_1_32_output,uint32_t gpio_33_64_output,const float *dac_dev1_Vout,const float *dac_dev2_Vout,const float *dac_dev3_Vout)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    char buf[MAVLINK_MSG_ID_MIXED_IO_CMD_LEN];
    _mav_put_uint32_t(buf, 0, gpio_1_32_output);
    _mav_put_uint32_t(buf, 4, gpio_33_64_output);
    _mav_put_float_array(buf, 8, dac_dev1_Vout, 4);
    _mav_put_float_array(buf, 24, dac_dev2_Vout, 4);
    _mav_put_float_array(buf, 40, dac_dev3_Vout, 4);
        memcpy(_MAV_PAYLOAD_NON_CONST(msg), buf, MAVLINK_MSG_ID_MIXED_IO_CMD_LEN);
#else
    mavlink_mixed_io_cmd_t packet;
    packet.gpio_1_32_output = gpio_1_32_output;
    packet.gpio_33_64_output = gpio_33_64_output;
    mav_array_memcpy(packet.dac_dev1_Vout, dac_dev1_Vout, sizeof(float)*4);
    mav_array_memcpy(packet.dac_dev2_Vout, dac_dev2_Vout, sizeof(float)*4);
    mav_array_memcpy(packet.dac_dev3_Vout, dac_dev3_Vout, sizeof(float)*4);
        memcpy(_MAV_PAYLOAD_NON_CONST(msg), &packet, MAVLINK_MSG_ID_MIXED_IO_CMD_LEN);
#endif

    msg->msgid = MAVLINK_MSG_ID_MIXED_IO_CMD;
    return mavlink_finalize_message_chan(msg, system_id, component_id, chan, MAVLINK_MSG_ID_MIXED_IO_CMD_MIN_LEN, MAVLINK_MSG_ID_MIXED_IO_CMD_LEN, MAVLINK_MSG_ID_MIXED_IO_CMD_CRC);
}

/**
 * @brief Encode a mixed_io_cmd struct
 *
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param msg The MAVLink message to compress the data into
 * @param mixed_io_cmd C-struct to read the message contents from
 */
static inline uint16_t mavlink_msg_mixed_io_cmd_encode(uint8_t system_id, uint8_t component_id, mavlink_message_t* msg, const mavlink_mixed_io_cmd_t* mixed_io_cmd)
{
    return mavlink_msg_mixed_io_cmd_pack(system_id, component_id, msg, mixed_io_cmd->gpio_1_32_output, mixed_io_cmd->gpio_33_64_output, mixed_io_cmd->dac_dev1_Vout, mixed_io_cmd->dac_dev2_Vout, mixed_io_cmd->dac_dev3_Vout);
}

/**
 * @brief Encode a mixed_io_cmd struct on a channel
 *
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param chan The MAVLink channel this message will be sent over
 * @param msg The MAVLink message to compress the data into
 * @param mixed_io_cmd C-struct to read the message contents from
 */
static inline uint16_t mavlink_msg_mixed_io_cmd_encode_chan(uint8_t system_id, uint8_t component_id, uint8_t chan, mavlink_message_t* msg, const mavlink_mixed_io_cmd_t* mixed_io_cmd)
{
    return mavlink_msg_mixed_io_cmd_pack_chan(system_id, component_id, chan, msg, mixed_io_cmd->gpio_1_32_output, mixed_io_cmd->gpio_33_64_output, mixed_io_cmd->dac_dev1_Vout, mixed_io_cmd->dac_dev2_Vout, mixed_io_cmd->dac_dev3_Vout);
}

/**
 * @brief Encode a mixed_io_cmd struct with provided status structure
 *
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param status MAVLink status structure
 * @param msg The MAVLink message to compress the data into
 * @param mixed_io_cmd C-struct to read the message contents from
 */
static inline uint16_t mavlink_msg_mixed_io_cmd_encode_status(uint8_t system_id, uint8_t component_id, mavlink_status_t* _status, mavlink_message_t* msg, const mavlink_mixed_io_cmd_t* mixed_io_cmd)
{
    return mavlink_msg_mixed_io_cmd_pack_status(system_id, component_id, _status, msg,  mixed_io_cmd->gpio_1_32_output, mixed_io_cmd->gpio_33_64_output, mixed_io_cmd->dac_dev1_Vout, mixed_io_cmd->dac_dev2_Vout, mixed_io_cmd->dac_dev3_Vout);
}

/**
 * @brief Send a mixed_io_cmd message
 * @param chan MAVLink channel to send the message
 *
 * @param gpio_1_32_output  GPIO outputs 1-32 bitmap. Bit 0 maps to GPIO 1; bit value 0 drives low and 1 drives high.
 * @param gpio_33_64_output  GPIO outputs 33-64 bitmap. Bit 0 maps to GPIO 33; bit value 0 drives low and 1 drives high.
 * @param dac_dev1_Vout [V] DAC device 1 output voltage: indexes 0-3 map to Vout_A through Vout_D.
 * @param dac_dev2_Vout [V] DAC device 2 output voltage: indexes 0-3 map to Vout_A through Vout_D.
 * @param dac_dev3_Vout [V] DAC device 3 output voltage: indexes 0-3 map to Vout_A through Vout_D.
 */
#ifdef MAVLINK_USE_CONVENIENCE_FUNCTIONS

static inline void mavlink_msg_mixed_io_cmd_send(mavlink_channel_t chan, uint32_t gpio_1_32_output, uint32_t gpio_33_64_output, const float *dac_dev1_Vout, const float *dac_dev2_Vout, const float *dac_dev3_Vout)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    char buf[MAVLINK_MSG_ID_MIXED_IO_CMD_LEN];
    _mav_put_uint32_t(buf, 0, gpio_1_32_output);
    _mav_put_uint32_t(buf, 4, gpio_33_64_output);
    _mav_put_float_array(buf, 8, dac_dev1_Vout, 4);
    _mav_put_float_array(buf, 24, dac_dev2_Vout, 4);
    _mav_put_float_array(buf, 40, dac_dev3_Vout, 4);
    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_MIXED_IO_CMD, buf, MAVLINK_MSG_ID_MIXED_IO_CMD_MIN_LEN, MAVLINK_MSG_ID_MIXED_IO_CMD_LEN, MAVLINK_MSG_ID_MIXED_IO_CMD_CRC);
#else
    mavlink_mixed_io_cmd_t packet;
    packet.gpio_1_32_output = gpio_1_32_output;
    packet.gpio_33_64_output = gpio_33_64_output;
    mav_array_memcpy(packet.dac_dev1_Vout, dac_dev1_Vout, sizeof(float)*4);
    mav_array_memcpy(packet.dac_dev2_Vout, dac_dev2_Vout, sizeof(float)*4);
    mav_array_memcpy(packet.dac_dev3_Vout, dac_dev3_Vout, sizeof(float)*4);
    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_MIXED_IO_CMD, (const char *)&packet, MAVLINK_MSG_ID_MIXED_IO_CMD_MIN_LEN, MAVLINK_MSG_ID_MIXED_IO_CMD_LEN, MAVLINK_MSG_ID_MIXED_IO_CMD_CRC);
#endif
}

/**
 * @brief Send a mixed_io_cmd message
 * @param chan MAVLink channel to send the message
 * @param struct The MAVLink struct to serialize
 */
static inline void mavlink_msg_mixed_io_cmd_send_struct(mavlink_channel_t chan, const mavlink_mixed_io_cmd_t* mixed_io_cmd)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    mavlink_msg_mixed_io_cmd_send(chan, mixed_io_cmd->gpio_1_32_output, mixed_io_cmd->gpio_33_64_output, mixed_io_cmd->dac_dev1_Vout, mixed_io_cmd->dac_dev2_Vout, mixed_io_cmd->dac_dev3_Vout);
#else
    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_MIXED_IO_CMD, (const char *)mixed_io_cmd, MAVLINK_MSG_ID_MIXED_IO_CMD_MIN_LEN, MAVLINK_MSG_ID_MIXED_IO_CMD_LEN, MAVLINK_MSG_ID_MIXED_IO_CMD_CRC);
#endif
}

#if MAVLINK_MSG_ID_MIXED_IO_CMD_LEN <= MAVLINK_MAX_PAYLOAD_LEN
/*
  This variant of _send() can be used to save stack space by reusing
  memory from the receive buffer.  The caller provides a
  mavlink_message_t which is the size of a full mavlink message. This
  is usually the receive buffer for the channel, and allows a reply to an
  incoming message with minimum stack space usage.
 */
static inline void mavlink_msg_mixed_io_cmd_send_buf(mavlink_message_t *msgbuf, mavlink_channel_t chan,  uint32_t gpio_1_32_output, uint32_t gpio_33_64_output, const float *dac_dev1_Vout, const float *dac_dev2_Vout, const float *dac_dev3_Vout)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    char *buf = (char *)msgbuf;
    _mav_put_uint32_t(buf, 0, gpio_1_32_output);
    _mav_put_uint32_t(buf, 4, gpio_33_64_output);
    _mav_put_float_array(buf, 8, dac_dev1_Vout, 4);
    _mav_put_float_array(buf, 24, dac_dev2_Vout, 4);
    _mav_put_float_array(buf, 40, dac_dev3_Vout, 4);
    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_MIXED_IO_CMD, buf, MAVLINK_MSG_ID_MIXED_IO_CMD_MIN_LEN, MAVLINK_MSG_ID_MIXED_IO_CMD_LEN, MAVLINK_MSG_ID_MIXED_IO_CMD_CRC);
#else
    mavlink_mixed_io_cmd_t *packet = (mavlink_mixed_io_cmd_t *)msgbuf;
    packet->gpio_1_32_output = gpio_1_32_output;
    packet->gpio_33_64_output = gpio_33_64_output;
    mav_array_memcpy(packet->dac_dev1_Vout, dac_dev1_Vout, sizeof(float)*4);
    mav_array_memcpy(packet->dac_dev2_Vout, dac_dev2_Vout, sizeof(float)*4);
    mav_array_memcpy(packet->dac_dev3_Vout, dac_dev3_Vout, sizeof(float)*4);
    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_MIXED_IO_CMD, (const char *)packet, MAVLINK_MSG_ID_MIXED_IO_CMD_MIN_LEN, MAVLINK_MSG_ID_MIXED_IO_CMD_LEN, MAVLINK_MSG_ID_MIXED_IO_CMD_CRC);
#endif
}
#endif

#endif

// MESSAGE MIXED_IO_CMD UNPACKING


/**
 * @brief Get field gpio_1_32_output from mixed_io_cmd message
 *
 * @return  GPIO outputs 1-32 bitmap. Bit 0 maps to GPIO 1; bit value 0 drives low and 1 drives high.
 */
static inline uint32_t mavlink_msg_mixed_io_cmd_get_gpio_1_32_output(const mavlink_message_t* msg)
{
    return _MAV_RETURN_uint32_t(msg,  0);
}

/**
 * @brief Get field gpio_33_64_output from mixed_io_cmd message
 *
 * @return  GPIO outputs 33-64 bitmap. Bit 0 maps to GPIO 33; bit value 0 drives low and 1 drives high.
 */
static inline uint32_t mavlink_msg_mixed_io_cmd_get_gpio_33_64_output(const mavlink_message_t* msg)
{
    return _MAV_RETURN_uint32_t(msg,  4);
}

/**
 * @brief Get field dac_dev1_Vout from mixed_io_cmd message
 *
 * @return [V] DAC device 1 output voltage: indexes 0-3 map to Vout_A through Vout_D.
 */
static inline uint16_t mavlink_msg_mixed_io_cmd_get_dac_dev1_Vout(const mavlink_message_t* msg, float *dac_dev1_Vout)
{
    return _MAV_RETURN_float_array(msg, dac_dev1_Vout, 4,  8);
}

/**
 * @brief Get field dac_dev2_Vout from mixed_io_cmd message
 *
 * @return [V] DAC device 2 output voltage: indexes 0-3 map to Vout_A through Vout_D.
 */
static inline uint16_t mavlink_msg_mixed_io_cmd_get_dac_dev2_Vout(const mavlink_message_t* msg, float *dac_dev2_Vout)
{
    return _MAV_RETURN_float_array(msg, dac_dev2_Vout, 4,  24);
}

/**
 * @brief Get field dac_dev3_Vout from mixed_io_cmd message
 *
 * @return [V] DAC device 3 output voltage: indexes 0-3 map to Vout_A through Vout_D.
 */
static inline uint16_t mavlink_msg_mixed_io_cmd_get_dac_dev3_Vout(const mavlink_message_t* msg, float *dac_dev3_Vout)
{
    return _MAV_RETURN_float_array(msg, dac_dev3_Vout, 4,  40);
}

/**
 * @brief Decode a mixed_io_cmd message into a struct
 *
 * @param msg The message to decode
 * @param mixed_io_cmd C-struct to decode the message contents into
 */
static inline void mavlink_msg_mixed_io_cmd_decode(const mavlink_message_t* msg, mavlink_mixed_io_cmd_t* mixed_io_cmd)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    mixed_io_cmd->gpio_1_32_output = mavlink_msg_mixed_io_cmd_get_gpio_1_32_output(msg);
    mixed_io_cmd->gpio_33_64_output = mavlink_msg_mixed_io_cmd_get_gpio_33_64_output(msg);
    mavlink_msg_mixed_io_cmd_get_dac_dev1_Vout(msg, mixed_io_cmd->dac_dev1_Vout);
    mavlink_msg_mixed_io_cmd_get_dac_dev2_Vout(msg, mixed_io_cmd->dac_dev2_Vout);
    mavlink_msg_mixed_io_cmd_get_dac_dev3_Vout(msg, mixed_io_cmd->dac_dev3_Vout);
#else
        uint8_t len = msg->len < MAVLINK_MSG_ID_MIXED_IO_CMD_LEN? msg->len : MAVLINK_MSG_ID_MIXED_IO_CMD_LEN;
        memset(mixed_io_cmd, 0, MAVLINK_MSG_ID_MIXED_IO_CMD_LEN);
    memcpy(mixed_io_cmd, _MAV_PAYLOAD(msg), len);
#endif
}
