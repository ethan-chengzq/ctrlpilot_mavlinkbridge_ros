#pragma once
// MESSAGE MIXED_IO_DATA PACKING

#define MAVLINK_MSG_ID_MIXED_IO_DATA 20


typedef struct __mavlink_mixed_io_data_t {
 uint32_t timestamp_ms; /*< [ms] Timestamp from the sender clock.*/
 uint32_t gpio_1_32_output; /*<  GPIO outputs 1-32 state bitmap. Bit 0 maps to GPIO 1; bit value 0 is low and 1 is high.*/
 uint32_t gpio_33_64_output; /*<  GPIO outputs 33-64 state bitmap. Bit 0 maps to GPIO 33; bit value 0 is low and 1 is high.*/
 uint32_t gpio_1_32_input; /*<  GPIO inputs 1-32 state bitmap. Bit 0 maps to GPIO 1; bit value 0 is low and 1 is high.*/
 uint32_t gpio_33_64_input; /*<  GPIO inputs 33-64 state bitmap. Bit 0 maps to GPIO 33; bit value 0 is low and 1 is high.*/
 float dac_dev1_Vout[4]; /*< [V] DAC device 1 current output voltage: indexes 0-3 map to Vout_A through Vout_D.*/
 float dac_dev2_Vout[4]; /*< [V] DAC device 2 current output voltage: indexes 0-3 map to Vout_A through Vout_D.*/
 float dac_dev3_Vout[4]; /*< [V] DAC device 3 current output voltage: indexes 0-3 map to Vout_A through Vout_D.*/
 float adc_dev1_Vin[8]; /*< [V] ADC device 1 input voltage: indexes 0-7 map to AI1 through AI8.*/
 float adc_dev2_Vin[8]; /*< [V] ADC device 2 input voltage: indexes 0-7 map to AI1 through AI8.*/
 float adc_dev3_Vin[8]; /*< [V] ADC device 3 input voltage: indexes 0-7 map to AI1 through AI8.*/
} mavlink_mixed_io_data_t;

#define MAVLINK_MSG_ID_MIXED_IO_DATA_LEN 164
#define MAVLINK_MSG_ID_MIXED_IO_DATA_MIN_LEN 164
#define MAVLINK_MSG_ID_20_LEN 164
#define MAVLINK_MSG_ID_20_MIN_LEN 164

#define MAVLINK_MSG_ID_MIXED_IO_DATA_CRC 76
#define MAVLINK_MSG_ID_20_CRC 76

#define MAVLINK_MSG_MIXED_IO_DATA_FIELD_DAC_DEV1_VOUT_LEN 4
#define MAVLINK_MSG_MIXED_IO_DATA_FIELD_DAC_DEV2_VOUT_LEN 4
#define MAVLINK_MSG_MIXED_IO_DATA_FIELD_DAC_DEV3_VOUT_LEN 4
#define MAVLINK_MSG_MIXED_IO_DATA_FIELD_ADC_DEV1_VIN_LEN 8
#define MAVLINK_MSG_MIXED_IO_DATA_FIELD_ADC_DEV2_VIN_LEN 8
#define MAVLINK_MSG_MIXED_IO_DATA_FIELD_ADC_DEV3_VIN_LEN 8

#if MAVLINK_COMMAND_24BIT
#define MAVLINK_MESSAGE_INFO_MIXED_IO_DATA { \
    20, \
    "MIXED_IO_DATA", \
    11, \
    {  { "timestamp_ms", NULL, MAVLINK_TYPE_UINT32_T, 0, 0, offsetof(mavlink_mixed_io_data_t, timestamp_ms) }, \
         { "gpio_1_32_output", NULL, MAVLINK_TYPE_UINT32_T, 0, 4, offsetof(mavlink_mixed_io_data_t, gpio_1_32_output) }, \
         { "gpio_33_64_output", NULL, MAVLINK_TYPE_UINT32_T, 0, 8, offsetof(mavlink_mixed_io_data_t, gpio_33_64_output) }, \
         { "gpio_1_32_input", NULL, MAVLINK_TYPE_UINT32_T, 0, 12, offsetof(mavlink_mixed_io_data_t, gpio_1_32_input) }, \
         { "gpio_33_64_input", NULL, MAVLINK_TYPE_UINT32_T, 0, 16, offsetof(mavlink_mixed_io_data_t, gpio_33_64_input) }, \
         { "dac_dev1_Vout", NULL, MAVLINK_TYPE_FLOAT, 4, 20, offsetof(mavlink_mixed_io_data_t, dac_dev1_Vout) }, \
         { "dac_dev2_Vout", NULL, MAVLINK_TYPE_FLOAT, 4, 36, offsetof(mavlink_mixed_io_data_t, dac_dev2_Vout) }, \
         { "dac_dev3_Vout", NULL, MAVLINK_TYPE_FLOAT, 4, 52, offsetof(mavlink_mixed_io_data_t, dac_dev3_Vout) }, \
         { "adc_dev1_Vin", NULL, MAVLINK_TYPE_FLOAT, 8, 68, offsetof(mavlink_mixed_io_data_t, adc_dev1_Vin) }, \
         { "adc_dev2_Vin", NULL, MAVLINK_TYPE_FLOAT, 8, 100, offsetof(mavlink_mixed_io_data_t, adc_dev2_Vin) }, \
         { "adc_dev3_Vin", NULL, MAVLINK_TYPE_FLOAT, 8, 132, offsetof(mavlink_mixed_io_data_t, adc_dev3_Vin) }, \
         } \
}
#else
#define MAVLINK_MESSAGE_INFO_MIXED_IO_DATA { \
    "MIXED_IO_DATA", \
    11, \
    {  { "timestamp_ms", NULL, MAVLINK_TYPE_UINT32_T, 0, 0, offsetof(mavlink_mixed_io_data_t, timestamp_ms) }, \
         { "gpio_1_32_output", NULL, MAVLINK_TYPE_UINT32_T, 0, 4, offsetof(mavlink_mixed_io_data_t, gpio_1_32_output) }, \
         { "gpio_33_64_output", NULL, MAVLINK_TYPE_UINT32_T, 0, 8, offsetof(mavlink_mixed_io_data_t, gpio_33_64_output) }, \
         { "gpio_1_32_input", NULL, MAVLINK_TYPE_UINT32_T, 0, 12, offsetof(mavlink_mixed_io_data_t, gpio_1_32_input) }, \
         { "gpio_33_64_input", NULL, MAVLINK_TYPE_UINT32_T, 0, 16, offsetof(mavlink_mixed_io_data_t, gpio_33_64_input) }, \
         { "dac_dev1_Vout", NULL, MAVLINK_TYPE_FLOAT, 4, 20, offsetof(mavlink_mixed_io_data_t, dac_dev1_Vout) }, \
         { "dac_dev2_Vout", NULL, MAVLINK_TYPE_FLOAT, 4, 36, offsetof(mavlink_mixed_io_data_t, dac_dev2_Vout) }, \
         { "dac_dev3_Vout", NULL, MAVLINK_TYPE_FLOAT, 4, 52, offsetof(mavlink_mixed_io_data_t, dac_dev3_Vout) }, \
         { "adc_dev1_Vin", NULL, MAVLINK_TYPE_FLOAT, 8, 68, offsetof(mavlink_mixed_io_data_t, adc_dev1_Vin) }, \
         { "adc_dev2_Vin", NULL, MAVLINK_TYPE_FLOAT, 8, 100, offsetof(mavlink_mixed_io_data_t, adc_dev2_Vin) }, \
         { "adc_dev3_Vin", NULL, MAVLINK_TYPE_FLOAT, 8, 132, offsetof(mavlink_mixed_io_data_t, adc_dev3_Vin) }, \
         } \
}
#endif

/**
 * @brief Pack a mixed_io_data message
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param msg The MAVLink message to compress the data into
 *
 * @param timestamp_ms [ms] Timestamp from the sender clock.
 * @param gpio_1_32_output  GPIO outputs 1-32 state bitmap. Bit 0 maps to GPIO 1; bit value 0 is low and 1 is high.
 * @param gpio_33_64_output  GPIO outputs 33-64 state bitmap. Bit 0 maps to GPIO 33; bit value 0 is low and 1 is high.
 * @param gpio_1_32_input  GPIO inputs 1-32 state bitmap. Bit 0 maps to GPIO 1; bit value 0 is low and 1 is high.
 * @param gpio_33_64_input  GPIO inputs 33-64 state bitmap. Bit 0 maps to GPIO 33; bit value 0 is low and 1 is high.
 * @param dac_dev1_Vout [V] DAC device 1 current output voltage: indexes 0-3 map to Vout_A through Vout_D.
 * @param dac_dev2_Vout [V] DAC device 2 current output voltage: indexes 0-3 map to Vout_A through Vout_D.
 * @param dac_dev3_Vout [V] DAC device 3 current output voltage: indexes 0-3 map to Vout_A through Vout_D.
 * @param adc_dev1_Vin [V] ADC device 1 input voltage: indexes 0-7 map to AI1 through AI8.
 * @param adc_dev2_Vin [V] ADC device 2 input voltage: indexes 0-7 map to AI1 through AI8.
 * @param adc_dev3_Vin [V] ADC device 3 input voltage: indexes 0-7 map to AI1 through AI8.
 * @return length of the message in bytes (excluding serial stream start sign)
 */
static inline uint16_t mavlink_msg_mixed_io_data_pack(uint8_t system_id, uint8_t component_id, mavlink_message_t* msg,
                               uint32_t timestamp_ms, uint32_t gpio_1_32_output, uint32_t gpio_33_64_output, uint32_t gpio_1_32_input, uint32_t gpio_33_64_input, const float *dac_dev1_Vout, const float *dac_dev2_Vout, const float *dac_dev3_Vout, const float *adc_dev1_Vin, const float *adc_dev2_Vin, const float *adc_dev3_Vin)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    char buf[MAVLINK_MSG_ID_MIXED_IO_DATA_LEN];
    _mav_put_uint32_t(buf, 0, timestamp_ms);
    _mav_put_uint32_t(buf, 4, gpio_1_32_output);
    _mav_put_uint32_t(buf, 8, gpio_33_64_output);
    _mav_put_uint32_t(buf, 12, gpio_1_32_input);
    _mav_put_uint32_t(buf, 16, gpio_33_64_input);
    _mav_put_float_array(buf, 20, dac_dev1_Vout, 4);
    _mav_put_float_array(buf, 36, dac_dev2_Vout, 4);
    _mav_put_float_array(buf, 52, dac_dev3_Vout, 4);
    _mav_put_float_array(buf, 68, adc_dev1_Vin, 8);
    _mav_put_float_array(buf, 100, adc_dev2_Vin, 8);
    _mav_put_float_array(buf, 132, adc_dev3_Vin, 8);
        memcpy(_MAV_PAYLOAD_NON_CONST(msg), buf, MAVLINK_MSG_ID_MIXED_IO_DATA_LEN);
#else
    mavlink_mixed_io_data_t packet;
    packet.timestamp_ms = timestamp_ms;
    packet.gpio_1_32_output = gpio_1_32_output;
    packet.gpio_33_64_output = gpio_33_64_output;
    packet.gpio_1_32_input = gpio_1_32_input;
    packet.gpio_33_64_input = gpio_33_64_input;
    mav_array_memcpy(packet.dac_dev1_Vout, dac_dev1_Vout, sizeof(float)*4);
    mav_array_memcpy(packet.dac_dev2_Vout, dac_dev2_Vout, sizeof(float)*4);
    mav_array_memcpy(packet.dac_dev3_Vout, dac_dev3_Vout, sizeof(float)*4);
    mav_array_memcpy(packet.adc_dev1_Vin, adc_dev1_Vin, sizeof(float)*8);
    mav_array_memcpy(packet.adc_dev2_Vin, adc_dev2_Vin, sizeof(float)*8);
    mav_array_memcpy(packet.adc_dev3_Vin, adc_dev3_Vin, sizeof(float)*8);
        memcpy(_MAV_PAYLOAD_NON_CONST(msg), &packet, MAVLINK_MSG_ID_MIXED_IO_DATA_LEN);
#endif

    msg->msgid = MAVLINK_MSG_ID_MIXED_IO_DATA;
    return mavlink_finalize_message(msg, system_id, component_id, MAVLINK_MSG_ID_MIXED_IO_DATA_MIN_LEN, MAVLINK_MSG_ID_MIXED_IO_DATA_LEN, MAVLINK_MSG_ID_MIXED_IO_DATA_CRC);
}

/**
 * @brief Pack a mixed_io_data message
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param status MAVLink status structure
 * @param msg The MAVLink message to compress the data into
 *
 * @param timestamp_ms [ms] Timestamp from the sender clock.
 * @param gpio_1_32_output  GPIO outputs 1-32 state bitmap. Bit 0 maps to GPIO 1; bit value 0 is low and 1 is high.
 * @param gpio_33_64_output  GPIO outputs 33-64 state bitmap. Bit 0 maps to GPIO 33; bit value 0 is low and 1 is high.
 * @param gpio_1_32_input  GPIO inputs 1-32 state bitmap. Bit 0 maps to GPIO 1; bit value 0 is low and 1 is high.
 * @param gpio_33_64_input  GPIO inputs 33-64 state bitmap. Bit 0 maps to GPIO 33; bit value 0 is low and 1 is high.
 * @param dac_dev1_Vout [V] DAC device 1 current output voltage: indexes 0-3 map to Vout_A through Vout_D.
 * @param dac_dev2_Vout [V] DAC device 2 current output voltage: indexes 0-3 map to Vout_A through Vout_D.
 * @param dac_dev3_Vout [V] DAC device 3 current output voltage: indexes 0-3 map to Vout_A through Vout_D.
 * @param adc_dev1_Vin [V] ADC device 1 input voltage: indexes 0-7 map to AI1 through AI8.
 * @param adc_dev2_Vin [V] ADC device 2 input voltage: indexes 0-7 map to AI1 through AI8.
 * @param adc_dev3_Vin [V] ADC device 3 input voltage: indexes 0-7 map to AI1 through AI8.
 * @return length of the message in bytes (excluding serial stream start sign)
 */
static inline uint16_t mavlink_msg_mixed_io_data_pack_status(uint8_t system_id, uint8_t component_id, mavlink_status_t *_status, mavlink_message_t* msg,
                               uint32_t timestamp_ms, uint32_t gpio_1_32_output, uint32_t gpio_33_64_output, uint32_t gpio_1_32_input, uint32_t gpio_33_64_input, const float *dac_dev1_Vout, const float *dac_dev2_Vout, const float *dac_dev3_Vout, const float *adc_dev1_Vin, const float *adc_dev2_Vin, const float *adc_dev3_Vin)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    char buf[MAVLINK_MSG_ID_MIXED_IO_DATA_LEN];
    _mav_put_uint32_t(buf, 0, timestamp_ms);
    _mav_put_uint32_t(buf, 4, gpio_1_32_output);
    _mav_put_uint32_t(buf, 8, gpio_33_64_output);
    _mav_put_uint32_t(buf, 12, gpio_1_32_input);
    _mav_put_uint32_t(buf, 16, gpio_33_64_input);
    _mav_put_float_array(buf, 20, dac_dev1_Vout, 4);
    _mav_put_float_array(buf, 36, dac_dev2_Vout, 4);
    _mav_put_float_array(buf, 52, dac_dev3_Vout, 4);
    _mav_put_float_array(buf, 68, adc_dev1_Vin, 8);
    _mav_put_float_array(buf, 100, adc_dev2_Vin, 8);
    _mav_put_float_array(buf, 132, adc_dev3_Vin, 8);
        memcpy(_MAV_PAYLOAD_NON_CONST(msg), buf, MAVLINK_MSG_ID_MIXED_IO_DATA_LEN);
#else
    mavlink_mixed_io_data_t packet;
    packet.timestamp_ms = timestamp_ms;
    packet.gpio_1_32_output = gpio_1_32_output;
    packet.gpio_33_64_output = gpio_33_64_output;
    packet.gpio_1_32_input = gpio_1_32_input;
    packet.gpio_33_64_input = gpio_33_64_input;
    mav_array_memcpy(packet.dac_dev1_Vout, dac_dev1_Vout, sizeof(float)*4);
    mav_array_memcpy(packet.dac_dev2_Vout, dac_dev2_Vout, sizeof(float)*4);
    mav_array_memcpy(packet.dac_dev3_Vout, dac_dev3_Vout, sizeof(float)*4);
    mav_array_memcpy(packet.adc_dev1_Vin, adc_dev1_Vin, sizeof(float)*8);
    mav_array_memcpy(packet.adc_dev2_Vin, adc_dev2_Vin, sizeof(float)*8);
    mav_array_memcpy(packet.adc_dev3_Vin, adc_dev3_Vin, sizeof(float)*8);
        memcpy(_MAV_PAYLOAD_NON_CONST(msg), &packet, MAVLINK_MSG_ID_MIXED_IO_DATA_LEN);
#endif

    msg->msgid = MAVLINK_MSG_ID_MIXED_IO_DATA;
#if MAVLINK_CRC_EXTRA
    return mavlink_finalize_message_buffer(msg, system_id, component_id, _status, MAVLINK_MSG_ID_MIXED_IO_DATA_MIN_LEN, MAVLINK_MSG_ID_MIXED_IO_DATA_LEN, MAVLINK_MSG_ID_MIXED_IO_DATA_CRC);
#else
    return mavlink_finalize_message_buffer(msg, system_id, component_id, _status, MAVLINK_MSG_ID_MIXED_IO_DATA_MIN_LEN, MAVLINK_MSG_ID_MIXED_IO_DATA_LEN);
#endif
}

/**
 * @brief Pack a mixed_io_data message on a channel
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param chan The MAVLink channel this message will be sent over
 * @param msg The MAVLink message to compress the data into
 * @param timestamp_ms [ms] Timestamp from the sender clock.
 * @param gpio_1_32_output  GPIO outputs 1-32 state bitmap. Bit 0 maps to GPIO 1; bit value 0 is low and 1 is high.
 * @param gpio_33_64_output  GPIO outputs 33-64 state bitmap. Bit 0 maps to GPIO 33; bit value 0 is low and 1 is high.
 * @param gpio_1_32_input  GPIO inputs 1-32 state bitmap. Bit 0 maps to GPIO 1; bit value 0 is low and 1 is high.
 * @param gpio_33_64_input  GPIO inputs 33-64 state bitmap. Bit 0 maps to GPIO 33; bit value 0 is low and 1 is high.
 * @param dac_dev1_Vout [V] DAC device 1 current output voltage: indexes 0-3 map to Vout_A through Vout_D.
 * @param dac_dev2_Vout [V] DAC device 2 current output voltage: indexes 0-3 map to Vout_A through Vout_D.
 * @param dac_dev3_Vout [V] DAC device 3 current output voltage: indexes 0-3 map to Vout_A through Vout_D.
 * @param adc_dev1_Vin [V] ADC device 1 input voltage: indexes 0-7 map to AI1 through AI8.
 * @param adc_dev2_Vin [V] ADC device 2 input voltage: indexes 0-7 map to AI1 through AI8.
 * @param adc_dev3_Vin [V] ADC device 3 input voltage: indexes 0-7 map to AI1 through AI8.
 * @return length of the message in bytes (excluding serial stream start sign)
 */
static inline uint16_t mavlink_msg_mixed_io_data_pack_chan(uint8_t system_id, uint8_t component_id, uint8_t chan,
                               mavlink_message_t* msg,
                                   uint32_t timestamp_ms,uint32_t gpio_1_32_output,uint32_t gpio_33_64_output,uint32_t gpio_1_32_input,uint32_t gpio_33_64_input,const float *dac_dev1_Vout,const float *dac_dev2_Vout,const float *dac_dev3_Vout,const float *adc_dev1_Vin,const float *adc_dev2_Vin,const float *adc_dev3_Vin)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    char buf[MAVLINK_MSG_ID_MIXED_IO_DATA_LEN];
    _mav_put_uint32_t(buf, 0, timestamp_ms);
    _mav_put_uint32_t(buf, 4, gpio_1_32_output);
    _mav_put_uint32_t(buf, 8, gpio_33_64_output);
    _mav_put_uint32_t(buf, 12, gpio_1_32_input);
    _mav_put_uint32_t(buf, 16, gpio_33_64_input);
    _mav_put_float_array(buf, 20, dac_dev1_Vout, 4);
    _mav_put_float_array(buf, 36, dac_dev2_Vout, 4);
    _mav_put_float_array(buf, 52, dac_dev3_Vout, 4);
    _mav_put_float_array(buf, 68, adc_dev1_Vin, 8);
    _mav_put_float_array(buf, 100, adc_dev2_Vin, 8);
    _mav_put_float_array(buf, 132, adc_dev3_Vin, 8);
        memcpy(_MAV_PAYLOAD_NON_CONST(msg), buf, MAVLINK_MSG_ID_MIXED_IO_DATA_LEN);
#else
    mavlink_mixed_io_data_t packet;
    packet.timestamp_ms = timestamp_ms;
    packet.gpio_1_32_output = gpio_1_32_output;
    packet.gpio_33_64_output = gpio_33_64_output;
    packet.gpio_1_32_input = gpio_1_32_input;
    packet.gpio_33_64_input = gpio_33_64_input;
    mav_array_memcpy(packet.dac_dev1_Vout, dac_dev1_Vout, sizeof(float)*4);
    mav_array_memcpy(packet.dac_dev2_Vout, dac_dev2_Vout, sizeof(float)*4);
    mav_array_memcpy(packet.dac_dev3_Vout, dac_dev3_Vout, sizeof(float)*4);
    mav_array_memcpy(packet.adc_dev1_Vin, adc_dev1_Vin, sizeof(float)*8);
    mav_array_memcpy(packet.adc_dev2_Vin, adc_dev2_Vin, sizeof(float)*8);
    mav_array_memcpy(packet.adc_dev3_Vin, adc_dev3_Vin, sizeof(float)*8);
        memcpy(_MAV_PAYLOAD_NON_CONST(msg), &packet, MAVLINK_MSG_ID_MIXED_IO_DATA_LEN);
#endif

    msg->msgid = MAVLINK_MSG_ID_MIXED_IO_DATA;
    return mavlink_finalize_message_chan(msg, system_id, component_id, chan, MAVLINK_MSG_ID_MIXED_IO_DATA_MIN_LEN, MAVLINK_MSG_ID_MIXED_IO_DATA_LEN, MAVLINK_MSG_ID_MIXED_IO_DATA_CRC);
}

/**
 * @brief Encode a mixed_io_data struct
 *
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param msg The MAVLink message to compress the data into
 * @param mixed_io_data C-struct to read the message contents from
 */
static inline uint16_t mavlink_msg_mixed_io_data_encode(uint8_t system_id, uint8_t component_id, mavlink_message_t* msg, const mavlink_mixed_io_data_t* mixed_io_data)
{
    return mavlink_msg_mixed_io_data_pack(system_id, component_id, msg, mixed_io_data->timestamp_ms, mixed_io_data->gpio_1_32_output, mixed_io_data->gpio_33_64_output, mixed_io_data->gpio_1_32_input, mixed_io_data->gpio_33_64_input, mixed_io_data->dac_dev1_Vout, mixed_io_data->dac_dev2_Vout, mixed_io_data->dac_dev3_Vout, mixed_io_data->adc_dev1_Vin, mixed_io_data->adc_dev2_Vin, mixed_io_data->adc_dev3_Vin);
}

/**
 * @brief Encode a mixed_io_data struct on a channel
 *
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param chan The MAVLink channel this message will be sent over
 * @param msg The MAVLink message to compress the data into
 * @param mixed_io_data C-struct to read the message contents from
 */
static inline uint16_t mavlink_msg_mixed_io_data_encode_chan(uint8_t system_id, uint8_t component_id, uint8_t chan, mavlink_message_t* msg, const mavlink_mixed_io_data_t* mixed_io_data)
{
    return mavlink_msg_mixed_io_data_pack_chan(system_id, component_id, chan, msg, mixed_io_data->timestamp_ms, mixed_io_data->gpio_1_32_output, mixed_io_data->gpio_33_64_output, mixed_io_data->gpio_1_32_input, mixed_io_data->gpio_33_64_input, mixed_io_data->dac_dev1_Vout, mixed_io_data->dac_dev2_Vout, mixed_io_data->dac_dev3_Vout, mixed_io_data->adc_dev1_Vin, mixed_io_data->adc_dev2_Vin, mixed_io_data->adc_dev3_Vin);
}

/**
 * @brief Encode a mixed_io_data struct with provided status structure
 *
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param status MAVLink status structure
 * @param msg The MAVLink message to compress the data into
 * @param mixed_io_data C-struct to read the message contents from
 */
static inline uint16_t mavlink_msg_mixed_io_data_encode_status(uint8_t system_id, uint8_t component_id, mavlink_status_t* _status, mavlink_message_t* msg, const mavlink_mixed_io_data_t* mixed_io_data)
{
    return mavlink_msg_mixed_io_data_pack_status(system_id, component_id, _status, msg,  mixed_io_data->timestamp_ms, mixed_io_data->gpio_1_32_output, mixed_io_data->gpio_33_64_output, mixed_io_data->gpio_1_32_input, mixed_io_data->gpio_33_64_input, mixed_io_data->dac_dev1_Vout, mixed_io_data->dac_dev2_Vout, mixed_io_data->dac_dev3_Vout, mixed_io_data->adc_dev1_Vin, mixed_io_data->adc_dev2_Vin, mixed_io_data->adc_dev3_Vin);
}

/**
 * @brief Send a mixed_io_data message
 * @param chan MAVLink channel to send the message
 *
 * @param timestamp_ms [ms] Timestamp from the sender clock.
 * @param gpio_1_32_output  GPIO outputs 1-32 state bitmap. Bit 0 maps to GPIO 1; bit value 0 is low and 1 is high.
 * @param gpio_33_64_output  GPIO outputs 33-64 state bitmap. Bit 0 maps to GPIO 33; bit value 0 is low and 1 is high.
 * @param gpio_1_32_input  GPIO inputs 1-32 state bitmap. Bit 0 maps to GPIO 1; bit value 0 is low and 1 is high.
 * @param gpio_33_64_input  GPIO inputs 33-64 state bitmap. Bit 0 maps to GPIO 33; bit value 0 is low and 1 is high.
 * @param dac_dev1_Vout [V] DAC device 1 current output voltage: indexes 0-3 map to Vout_A through Vout_D.
 * @param dac_dev2_Vout [V] DAC device 2 current output voltage: indexes 0-3 map to Vout_A through Vout_D.
 * @param dac_dev3_Vout [V] DAC device 3 current output voltage: indexes 0-3 map to Vout_A through Vout_D.
 * @param adc_dev1_Vin [V] ADC device 1 input voltage: indexes 0-7 map to AI1 through AI8.
 * @param adc_dev2_Vin [V] ADC device 2 input voltage: indexes 0-7 map to AI1 through AI8.
 * @param adc_dev3_Vin [V] ADC device 3 input voltage: indexes 0-7 map to AI1 through AI8.
 */
#ifdef MAVLINK_USE_CONVENIENCE_FUNCTIONS

static inline void mavlink_msg_mixed_io_data_send(mavlink_channel_t chan, uint32_t timestamp_ms, uint32_t gpio_1_32_output, uint32_t gpio_33_64_output, uint32_t gpio_1_32_input, uint32_t gpio_33_64_input, const float *dac_dev1_Vout, const float *dac_dev2_Vout, const float *dac_dev3_Vout, const float *adc_dev1_Vin, const float *adc_dev2_Vin, const float *adc_dev3_Vin)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    char buf[MAVLINK_MSG_ID_MIXED_IO_DATA_LEN];
    _mav_put_uint32_t(buf, 0, timestamp_ms);
    _mav_put_uint32_t(buf, 4, gpio_1_32_output);
    _mav_put_uint32_t(buf, 8, gpio_33_64_output);
    _mav_put_uint32_t(buf, 12, gpio_1_32_input);
    _mav_put_uint32_t(buf, 16, gpio_33_64_input);
    _mav_put_float_array(buf, 20, dac_dev1_Vout, 4);
    _mav_put_float_array(buf, 36, dac_dev2_Vout, 4);
    _mav_put_float_array(buf, 52, dac_dev3_Vout, 4);
    _mav_put_float_array(buf, 68, adc_dev1_Vin, 8);
    _mav_put_float_array(buf, 100, adc_dev2_Vin, 8);
    _mav_put_float_array(buf, 132, adc_dev3_Vin, 8);
    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_MIXED_IO_DATA, buf, MAVLINK_MSG_ID_MIXED_IO_DATA_MIN_LEN, MAVLINK_MSG_ID_MIXED_IO_DATA_LEN, MAVLINK_MSG_ID_MIXED_IO_DATA_CRC);
#else
    mavlink_mixed_io_data_t packet;
    packet.timestamp_ms = timestamp_ms;
    packet.gpio_1_32_output = gpio_1_32_output;
    packet.gpio_33_64_output = gpio_33_64_output;
    packet.gpio_1_32_input = gpio_1_32_input;
    packet.gpio_33_64_input = gpio_33_64_input;
    mav_array_memcpy(packet.dac_dev1_Vout, dac_dev1_Vout, sizeof(float)*4);
    mav_array_memcpy(packet.dac_dev2_Vout, dac_dev2_Vout, sizeof(float)*4);
    mav_array_memcpy(packet.dac_dev3_Vout, dac_dev3_Vout, sizeof(float)*4);
    mav_array_memcpy(packet.adc_dev1_Vin, adc_dev1_Vin, sizeof(float)*8);
    mav_array_memcpy(packet.adc_dev2_Vin, adc_dev2_Vin, sizeof(float)*8);
    mav_array_memcpy(packet.adc_dev3_Vin, adc_dev3_Vin, sizeof(float)*8);
    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_MIXED_IO_DATA, (const char *)&packet, MAVLINK_MSG_ID_MIXED_IO_DATA_MIN_LEN, MAVLINK_MSG_ID_MIXED_IO_DATA_LEN, MAVLINK_MSG_ID_MIXED_IO_DATA_CRC);
#endif
}

/**
 * @brief Send a mixed_io_data message
 * @param chan MAVLink channel to send the message
 * @param struct The MAVLink struct to serialize
 */
static inline void mavlink_msg_mixed_io_data_send_struct(mavlink_channel_t chan, const mavlink_mixed_io_data_t* mixed_io_data)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    mavlink_msg_mixed_io_data_send(chan, mixed_io_data->timestamp_ms, mixed_io_data->gpio_1_32_output, mixed_io_data->gpio_33_64_output, mixed_io_data->gpio_1_32_input, mixed_io_data->gpio_33_64_input, mixed_io_data->dac_dev1_Vout, mixed_io_data->dac_dev2_Vout, mixed_io_data->dac_dev3_Vout, mixed_io_data->adc_dev1_Vin, mixed_io_data->adc_dev2_Vin, mixed_io_data->adc_dev3_Vin);
#else
    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_MIXED_IO_DATA, (const char *)mixed_io_data, MAVLINK_MSG_ID_MIXED_IO_DATA_MIN_LEN, MAVLINK_MSG_ID_MIXED_IO_DATA_LEN, MAVLINK_MSG_ID_MIXED_IO_DATA_CRC);
#endif
}

#if MAVLINK_MSG_ID_MIXED_IO_DATA_LEN <= MAVLINK_MAX_PAYLOAD_LEN
/*
  This variant of _send() can be used to save stack space by reusing
  memory from the receive buffer.  The caller provides a
  mavlink_message_t which is the size of a full mavlink message. This
  is usually the receive buffer for the channel, and allows a reply to an
  incoming message with minimum stack space usage.
 */
static inline void mavlink_msg_mixed_io_data_send_buf(mavlink_message_t *msgbuf, mavlink_channel_t chan,  uint32_t timestamp_ms, uint32_t gpio_1_32_output, uint32_t gpio_33_64_output, uint32_t gpio_1_32_input, uint32_t gpio_33_64_input, const float *dac_dev1_Vout, const float *dac_dev2_Vout, const float *dac_dev3_Vout, const float *adc_dev1_Vin, const float *adc_dev2_Vin, const float *adc_dev3_Vin)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    char *buf = (char *)msgbuf;
    _mav_put_uint32_t(buf, 0, timestamp_ms);
    _mav_put_uint32_t(buf, 4, gpio_1_32_output);
    _mav_put_uint32_t(buf, 8, gpio_33_64_output);
    _mav_put_uint32_t(buf, 12, gpio_1_32_input);
    _mav_put_uint32_t(buf, 16, gpio_33_64_input);
    _mav_put_float_array(buf, 20, dac_dev1_Vout, 4);
    _mav_put_float_array(buf, 36, dac_dev2_Vout, 4);
    _mav_put_float_array(buf, 52, dac_dev3_Vout, 4);
    _mav_put_float_array(buf, 68, adc_dev1_Vin, 8);
    _mav_put_float_array(buf, 100, adc_dev2_Vin, 8);
    _mav_put_float_array(buf, 132, adc_dev3_Vin, 8);
    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_MIXED_IO_DATA, buf, MAVLINK_MSG_ID_MIXED_IO_DATA_MIN_LEN, MAVLINK_MSG_ID_MIXED_IO_DATA_LEN, MAVLINK_MSG_ID_MIXED_IO_DATA_CRC);
#else
    mavlink_mixed_io_data_t *packet = (mavlink_mixed_io_data_t *)msgbuf;
    packet->timestamp_ms = timestamp_ms;
    packet->gpio_1_32_output = gpio_1_32_output;
    packet->gpio_33_64_output = gpio_33_64_output;
    packet->gpio_1_32_input = gpio_1_32_input;
    packet->gpio_33_64_input = gpio_33_64_input;
    mav_array_memcpy(packet->dac_dev1_Vout, dac_dev1_Vout, sizeof(float)*4);
    mav_array_memcpy(packet->dac_dev2_Vout, dac_dev2_Vout, sizeof(float)*4);
    mav_array_memcpy(packet->dac_dev3_Vout, dac_dev3_Vout, sizeof(float)*4);
    mav_array_memcpy(packet->adc_dev1_Vin, adc_dev1_Vin, sizeof(float)*8);
    mav_array_memcpy(packet->adc_dev2_Vin, adc_dev2_Vin, sizeof(float)*8);
    mav_array_memcpy(packet->adc_dev3_Vin, adc_dev3_Vin, sizeof(float)*8);
    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_MIXED_IO_DATA, (const char *)packet, MAVLINK_MSG_ID_MIXED_IO_DATA_MIN_LEN, MAVLINK_MSG_ID_MIXED_IO_DATA_LEN, MAVLINK_MSG_ID_MIXED_IO_DATA_CRC);
#endif
}
#endif

#endif

// MESSAGE MIXED_IO_DATA UNPACKING


/**
 * @brief Get field timestamp_ms from mixed_io_data message
 *
 * @return [ms] Timestamp from the sender clock.
 */
static inline uint32_t mavlink_msg_mixed_io_data_get_timestamp_ms(const mavlink_message_t* msg)
{
    return _MAV_RETURN_uint32_t(msg,  0);
}

/**
 * @brief Get field gpio_1_32_output from mixed_io_data message
 *
 * @return  GPIO outputs 1-32 state bitmap. Bit 0 maps to GPIO 1; bit value 0 is low and 1 is high.
 */
static inline uint32_t mavlink_msg_mixed_io_data_get_gpio_1_32_output(const mavlink_message_t* msg)
{
    return _MAV_RETURN_uint32_t(msg,  4);
}

/**
 * @brief Get field gpio_33_64_output from mixed_io_data message
 *
 * @return  GPIO outputs 33-64 state bitmap. Bit 0 maps to GPIO 33; bit value 0 is low and 1 is high.
 */
static inline uint32_t mavlink_msg_mixed_io_data_get_gpio_33_64_output(const mavlink_message_t* msg)
{
    return _MAV_RETURN_uint32_t(msg,  8);
}

/**
 * @brief Get field gpio_1_32_input from mixed_io_data message
 *
 * @return  GPIO inputs 1-32 state bitmap. Bit 0 maps to GPIO 1; bit value 0 is low and 1 is high.
 */
static inline uint32_t mavlink_msg_mixed_io_data_get_gpio_1_32_input(const mavlink_message_t* msg)
{
    return _MAV_RETURN_uint32_t(msg,  12);
}

/**
 * @brief Get field gpio_33_64_input from mixed_io_data message
 *
 * @return  GPIO inputs 33-64 state bitmap. Bit 0 maps to GPIO 33; bit value 0 is low and 1 is high.
 */
static inline uint32_t mavlink_msg_mixed_io_data_get_gpio_33_64_input(const mavlink_message_t* msg)
{
    return _MAV_RETURN_uint32_t(msg,  16);
}

/**
 * @brief Get field dac_dev1_Vout from mixed_io_data message
 *
 * @return [V] DAC device 1 current output voltage: indexes 0-3 map to Vout_A through Vout_D.
 */
static inline uint16_t mavlink_msg_mixed_io_data_get_dac_dev1_Vout(const mavlink_message_t* msg, float *dac_dev1_Vout)
{
    return _MAV_RETURN_float_array(msg, dac_dev1_Vout, 4,  20);
}

/**
 * @brief Get field dac_dev2_Vout from mixed_io_data message
 *
 * @return [V] DAC device 2 current output voltage: indexes 0-3 map to Vout_A through Vout_D.
 */
static inline uint16_t mavlink_msg_mixed_io_data_get_dac_dev2_Vout(const mavlink_message_t* msg, float *dac_dev2_Vout)
{
    return _MAV_RETURN_float_array(msg, dac_dev2_Vout, 4,  36);
}

/**
 * @brief Get field dac_dev3_Vout from mixed_io_data message
 *
 * @return [V] DAC device 3 current output voltage: indexes 0-3 map to Vout_A through Vout_D.
 */
static inline uint16_t mavlink_msg_mixed_io_data_get_dac_dev3_Vout(const mavlink_message_t* msg, float *dac_dev3_Vout)
{
    return _MAV_RETURN_float_array(msg, dac_dev3_Vout, 4,  52);
}

/**
 * @brief Get field adc_dev1_Vin from mixed_io_data message
 *
 * @return [V] ADC device 1 input voltage: indexes 0-7 map to AI1 through AI8.
 */
static inline uint16_t mavlink_msg_mixed_io_data_get_adc_dev1_Vin(const mavlink_message_t* msg, float *adc_dev1_Vin)
{
    return _MAV_RETURN_float_array(msg, adc_dev1_Vin, 8,  68);
}

/**
 * @brief Get field adc_dev2_Vin from mixed_io_data message
 *
 * @return [V] ADC device 2 input voltage: indexes 0-7 map to AI1 through AI8.
 */
static inline uint16_t mavlink_msg_mixed_io_data_get_adc_dev2_Vin(const mavlink_message_t* msg, float *adc_dev2_Vin)
{
    return _MAV_RETURN_float_array(msg, adc_dev2_Vin, 8,  100);
}

/**
 * @brief Get field adc_dev3_Vin from mixed_io_data message
 *
 * @return [V] ADC device 3 input voltage: indexes 0-7 map to AI1 through AI8.
 */
static inline uint16_t mavlink_msg_mixed_io_data_get_adc_dev3_Vin(const mavlink_message_t* msg, float *adc_dev3_Vin)
{
    return _MAV_RETURN_float_array(msg, adc_dev3_Vin, 8,  132);
}

/**
 * @brief Decode a mixed_io_data message into a struct
 *
 * @param msg The message to decode
 * @param mixed_io_data C-struct to decode the message contents into
 */
static inline void mavlink_msg_mixed_io_data_decode(const mavlink_message_t* msg, mavlink_mixed_io_data_t* mixed_io_data)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    mixed_io_data->timestamp_ms = mavlink_msg_mixed_io_data_get_timestamp_ms(msg);
    mixed_io_data->gpio_1_32_output = mavlink_msg_mixed_io_data_get_gpio_1_32_output(msg);
    mixed_io_data->gpio_33_64_output = mavlink_msg_mixed_io_data_get_gpio_33_64_output(msg);
    mixed_io_data->gpio_1_32_input = mavlink_msg_mixed_io_data_get_gpio_1_32_input(msg);
    mixed_io_data->gpio_33_64_input = mavlink_msg_mixed_io_data_get_gpio_33_64_input(msg);
    mavlink_msg_mixed_io_data_get_dac_dev1_Vout(msg, mixed_io_data->dac_dev1_Vout);
    mavlink_msg_mixed_io_data_get_dac_dev2_Vout(msg, mixed_io_data->dac_dev2_Vout);
    mavlink_msg_mixed_io_data_get_dac_dev3_Vout(msg, mixed_io_data->dac_dev3_Vout);
    mavlink_msg_mixed_io_data_get_adc_dev1_Vin(msg, mixed_io_data->adc_dev1_Vin);
    mavlink_msg_mixed_io_data_get_adc_dev2_Vin(msg, mixed_io_data->adc_dev2_Vin);
    mavlink_msg_mixed_io_data_get_adc_dev3_Vin(msg, mixed_io_data->adc_dev3_Vin);
#else
        uint8_t len = msg->len < MAVLINK_MSG_ID_MIXED_IO_DATA_LEN? msg->len : MAVLINK_MSG_ID_MIXED_IO_DATA_LEN;
        memset(mixed_io_data, 0, MAVLINK_MSG_ID_MIXED_IO_DATA_LEN);
    memcpy(mixed_io_data, _MAV_PAYLOAD(msg), len);
#endif
}
