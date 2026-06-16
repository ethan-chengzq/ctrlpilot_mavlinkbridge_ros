#pragma once
// MESSAGE VALVE_STATUS PACKING

#define MAVLINK_MSG_ID_VALVE_STATUS 22


typedef struct __mavlink_valve_status_t {
 uint32_t timestamp_ms; /*< [ms] Timestamp from the sender clock.*/
 int32_t encoder[2]; /*<  Encoder 1 and encoder 2 counts. Source: Modbus registers 46-49.*/
 uint16_t valve_current_x10[40]; /*<  Valve current readback in 10 mA units. Source: Modbus registers 2-21.*/
 uint16_t sensor_data[24]; /*<  Analog sensor 1-24 raw values. Source: Modbus registers 22-45.*/
 uint16_t water_in_mv; /*< [mV] Water ingress sensor voltage. Source: Modbus register 51.*/
 uint16_t board_voltage_mv; /*< [mV] Board supply voltage. Source: Modbus register 55.*/
 int16_t temp_x10[3]; /*<  Temperature channels 1, 2 and board temperature in 0.1 degC units. Source: Modbus registers 52-54.*/
 uint8_t valve_state[40]; /*<  Valve state for 40 valves: 0 normal, 2 alarm, 3 offline. Source: Modbus registers 56-60.*/
} mavlink_valve_status_t;

#define MAVLINK_MSG_ID_VALVE_STATUS_LEN 190
#define MAVLINK_MSG_ID_VALVE_STATUS_MIN_LEN 190
#define MAVLINK_MSG_ID_22_LEN 190
#define MAVLINK_MSG_ID_22_MIN_LEN 190

#define MAVLINK_MSG_ID_VALVE_STATUS_CRC 8
#define MAVLINK_MSG_ID_22_CRC 8

#define MAVLINK_MSG_VALVE_STATUS_FIELD_ENCODER_LEN 2
#define MAVLINK_MSG_VALVE_STATUS_FIELD_VALVE_CURRENT_X10_LEN 40
#define MAVLINK_MSG_VALVE_STATUS_FIELD_SENSOR_DATA_LEN 24
#define MAVLINK_MSG_VALVE_STATUS_FIELD_TEMP_X10_LEN 3
#define MAVLINK_MSG_VALVE_STATUS_FIELD_VALVE_STATE_LEN 40

#if MAVLINK_COMMAND_24BIT
#define MAVLINK_MESSAGE_INFO_VALVE_STATUS { \
    22, \
    "VALVE_STATUS", \
    8, \
    {  { "timestamp_ms", NULL, MAVLINK_TYPE_UINT32_T, 0, 0, offsetof(mavlink_valve_status_t, timestamp_ms) }, \
         { "valve_current_x10", NULL, MAVLINK_TYPE_UINT16_T, 40, 12, offsetof(mavlink_valve_status_t, valve_current_x10) }, \
         { "valve_state", NULL, MAVLINK_TYPE_UINT8_T, 40, 150, offsetof(mavlink_valve_status_t, valve_state) }, \
         { "encoder", NULL, MAVLINK_TYPE_INT32_T, 2, 4, offsetof(mavlink_valve_status_t, encoder) }, \
         { "sensor_data", NULL, MAVLINK_TYPE_UINT16_T, 24, 92, offsetof(mavlink_valve_status_t, sensor_data) }, \
         { "water_in_mv", NULL, MAVLINK_TYPE_UINT16_T, 0, 140, offsetof(mavlink_valve_status_t, water_in_mv) }, \
         { "board_voltage_mv", NULL, MAVLINK_TYPE_UINT16_T, 0, 142, offsetof(mavlink_valve_status_t, board_voltage_mv) }, \
         { "temp_x10", NULL, MAVLINK_TYPE_INT16_T, 3, 144, offsetof(mavlink_valve_status_t, temp_x10) }, \
         } \
}
#else
#define MAVLINK_MESSAGE_INFO_VALVE_STATUS { \
    "VALVE_STATUS", \
    8, \
    {  { "timestamp_ms", NULL, MAVLINK_TYPE_UINT32_T, 0, 0, offsetof(mavlink_valve_status_t, timestamp_ms) }, \
         { "valve_current_x10", NULL, MAVLINK_TYPE_UINT16_T, 40, 12, offsetof(mavlink_valve_status_t, valve_current_x10) }, \
         { "valve_state", NULL, MAVLINK_TYPE_UINT8_T, 40, 150, offsetof(mavlink_valve_status_t, valve_state) }, \
         { "encoder", NULL, MAVLINK_TYPE_INT32_T, 2, 4, offsetof(mavlink_valve_status_t, encoder) }, \
         { "sensor_data", NULL, MAVLINK_TYPE_UINT16_T, 24, 92, offsetof(mavlink_valve_status_t, sensor_data) }, \
         { "water_in_mv", NULL, MAVLINK_TYPE_UINT16_T, 0, 140, offsetof(mavlink_valve_status_t, water_in_mv) }, \
         { "board_voltage_mv", NULL, MAVLINK_TYPE_UINT16_T, 0, 142, offsetof(mavlink_valve_status_t, board_voltage_mv) }, \
         { "temp_x10", NULL, MAVLINK_TYPE_INT16_T, 3, 144, offsetof(mavlink_valve_status_t, temp_x10) }, \
         } \
}
#endif

/**
 * @brief Pack a valve_status message
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param msg The MAVLink message to compress the data into
 *
 * @param timestamp_ms [ms] Timestamp from the sender clock.
 * @param valve_current_x10  Valve current readback in 10 mA units. Source: Modbus registers 2-21.
 * @param valve_state  Valve state for 40 valves: 0 normal, 2 alarm, 3 offline. Source: Modbus registers 56-60.
 * @param encoder  Encoder 1 and encoder 2 counts. Source: Modbus registers 46-49.
 * @param sensor_data  Analog sensor 1-24 raw values. Source: Modbus registers 22-45.
 * @param water_in_mv [mV] Water ingress sensor voltage. Source: Modbus register 51.
 * @param board_voltage_mv [mV] Board supply voltage. Source: Modbus register 55.
 * @param temp_x10  Temperature channels 1, 2 and board temperature in 0.1 degC units. Source: Modbus registers 52-54.
 * @return length of the message in bytes (excluding serial stream start sign)
 */
static inline uint16_t mavlink_msg_valve_status_pack(uint8_t system_id, uint8_t component_id, mavlink_message_t* msg,
                               uint32_t timestamp_ms, const uint16_t *valve_current_x10, const uint8_t *valve_state, const int32_t *encoder, const uint16_t *sensor_data, uint16_t water_in_mv, uint16_t board_voltage_mv, const int16_t *temp_x10)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    char buf[MAVLINK_MSG_ID_VALVE_STATUS_LEN];
    _mav_put_uint32_t(buf, 0, timestamp_ms);
    _mav_put_uint16_t(buf, 140, water_in_mv);
    _mav_put_uint16_t(buf, 142, board_voltage_mv);
    _mav_put_int32_t_array(buf, 4, encoder, 2);
    _mav_put_uint16_t_array(buf, 12, valve_current_x10, 40);
    _mav_put_uint16_t_array(buf, 92, sensor_data, 24);
    _mav_put_int16_t_array(buf, 144, temp_x10, 3);
    _mav_put_uint8_t_array(buf, 150, valve_state, 40);
        memcpy(_MAV_PAYLOAD_NON_CONST(msg), buf, MAVLINK_MSG_ID_VALVE_STATUS_LEN);
#else
    mavlink_valve_status_t packet;
    packet.timestamp_ms = timestamp_ms;
    packet.water_in_mv = water_in_mv;
    packet.board_voltage_mv = board_voltage_mv;
    mav_array_memcpy(packet.encoder, encoder, sizeof(int32_t)*2);
    mav_array_memcpy(packet.valve_current_x10, valve_current_x10, sizeof(uint16_t)*40);
    mav_array_memcpy(packet.sensor_data, sensor_data, sizeof(uint16_t)*24);
    mav_array_memcpy(packet.temp_x10, temp_x10, sizeof(int16_t)*3);
    mav_array_memcpy(packet.valve_state, valve_state, sizeof(uint8_t)*40);
        memcpy(_MAV_PAYLOAD_NON_CONST(msg), &packet, MAVLINK_MSG_ID_VALVE_STATUS_LEN);
#endif

    msg->msgid = MAVLINK_MSG_ID_VALVE_STATUS;
    return mavlink_finalize_message(msg, system_id, component_id, MAVLINK_MSG_ID_VALVE_STATUS_MIN_LEN, MAVLINK_MSG_ID_VALVE_STATUS_LEN, MAVLINK_MSG_ID_VALVE_STATUS_CRC);
}

/**
 * @brief Pack a valve_status message
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param status MAVLink status structure
 * @param msg The MAVLink message to compress the data into
 *
 * @param timestamp_ms [ms] Timestamp from the sender clock.
 * @param valve_current_x10  Valve current readback in 10 mA units. Source: Modbus registers 2-21.
 * @param valve_state  Valve state for 40 valves: 0 normal, 2 alarm, 3 offline. Source: Modbus registers 56-60.
 * @param encoder  Encoder 1 and encoder 2 counts. Source: Modbus registers 46-49.
 * @param sensor_data  Analog sensor 1-24 raw values. Source: Modbus registers 22-45.
 * @param water_in_mv [mV] Water ingress sensor voltage. Source: Modbus register 51.
 * @param board_voltage_mv [mV] Board supply voltage. Source: Modbus register 55.
 * @param temp_x10  Temperature channels 1, 2 and board temperature in 0.1 degC units. Source: Modbus registers 52-54.
 * @return length of the message in bytes (excluding serial stream start sign)
 */
static inline uint16_t mavlink_msg_valve_status_pack_status(uint8_t system_id, uint8_t component_id, mavlink_status_t *_status, mavlink_message_t* msg,
                               uint32_t timestamp_ms, const uint16_t *valve_current_x10, const uint8_t *valve_state, const int32_t *encoder, const uint16_t *sensor_data, uint16_t water_in_mv, uint16_t board_voltage_mv, const int16_t *temp_x10)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    char buf[MAVLINK_MSG_ID_VALVE_STATUS_LEN];
    _mav_put_uint32_t(buf, 0, timestamp_ms);
    _mav_put_uint16_t(buf, 140, water_in_mv);
    _mav_put_uint16_t(buf, 142, board_voltage_mv);
    _mav_put_int32_t_array(buf, 4, encoder, 2);
    _mav_put_uint16_t_array(buf, 12, valve_current_x10, 40);
    _mav_put_uint16_t_array(buf, 92, sensor_data, 24);
    _mav_put_int16_t_array(buf, 144, temp_x10, 3);
    _mav_put_uint8_t_array(buf, 150, valve_state, 40);
        memcpy(_MAV_PAYLOAD_NON_CONST(msg), buf, MAVLINK_MSG_ID_VALVE_STATUS_LEN);
#else
    mavlink_valve_status_t packet;
    packet.timestamp_ms = timestamp_ms;
    packet.water_in_mv = water_in_mv;
    packet.board_voltage_mv = board_voltage_mv;
    mav_array_memcpy(packet.encoder, encoder, sizeof(int32_t)*2);
    mav_array_memcpy(packet.valve_current_x10, valve_current_x10, sizeof(uint16_t)*40);
    mav_array_memcpy(packet.sensor_data, sensor_data, sizeof(uint16_t)*24);
    mav_array_memcpy(packet.temp_x10, temp_x10, sizeof(int16_t)*3);
    mav_array_memcpy(packet.valve_state, valve_state, sizeof(uint8_t)*40);
        memcpy(_MAV_PAYLOAD_NON_CONST(msg), &packet, MAVLINK_MSG_ID_VALVE_STATUS_LEN);
#endif

    msg->msgid = MAVLINK_MSG_ID_VALVE_STATUS;
#if MAVLINK_CRC_EXTRA
    return mavlink_finalize_message_buffer(msg, system_id, component_id, _status, MAVLINK_MSG_ID_VALVE_STATUS_MIN_LEN, MAVLINK_MSG_ID_VALVE_STATUS_LEN, MAVLINK_MSG_ID_VALVE_STATUS_CRC);
#else
    return mavlink_finalize_message_buffer(msg, system_id, component_id, _status, MAVLINK_MSG_ID_VALVE_STATUS_MIN_LEN, MAVLINK_MSG_ID_VALVE_STATUS_LEN);
#endif
}

/**
 * @brief Pack a valve_status message on a channel
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param chan The MAVLink channel this message will be sent over
 * @param msg The MAVLink message to compress the data into
 * @param timestamp_ms [ms] Timestamp from the sender clock.
 * @param valve_current_x10  Valve current readback in 10 mA units. Source: Modbus registers 2-21.
 * @param valve_state  Valve state for 40 valves: 0 normal, 2 alarm, 3 offline. Source: Modbus registers 56-60.
 * @param encoder  Encoder 1 and encoder 2 counts. Source: Modbus registers 46-49.
 * @param sensor_data  Analog sensor 1-24 raw values. Source: Modbus registers 22-45.
 * @param water_in_mv [mV] Water ingress sensor voltage. Source: Modbus register 51.
 * @param board_voltage_mv [mV] Board supply voltage. Source: Modbus register 55.
 * @param temp_x10  Temperature channels 1, 2 and board temperature in 0.1 degC units. Source: Modbus registers 52-54.
 * @return length of the message in bytes (excluding serial stream start sign)
 */
static inline uint16_t mavlink_msg_valve_status_pack_chan(uint8_t system_id, uint8_t component_id, uint8_t chan,
                               mavlink_message_t* msg,
                                   uint32_t timestamp_ms,const uint16_t *valve_current_x10,const uint8_t *valve_state,const int32_t *encoder,const uint16_t *sensor_data,uint16_t water_in_mv,uint16_t board_voltage_mv,const int16_t *temp_x10)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    char buf[MAVLINK_MSG_ID_VALVE_STATUS_LEN];
    _mav_put_uint32_t(buf, 0, timestamp_ms);
    _mav_put_uint16_t(buf, 140, water_in_mv);
    _mav_put_uint16_t(buf, 142, board_voltage_mv);
    _mav_put_int32_t_array(buf, 4, encoder, 2);
    _mav_put_uint16_t_array(buf, 12, valve_current_x10, 40);
    _mav_put_uint16_t_array(buf, 92, sensor_data, 24);
    _mav_put_int16_t_array(buf, 144, temp_x10, 3);
    _mav_put_uint8_t_array(buf, 150, valve_state, 40);
        memcpy(_MAV_PAYLOAD_NON_CONST(msg), buf, MAVLINK_MSG_ID_VALVE_STATUS_LEN);
#else
    mavlink_valve_status_t packet;
    packet.timestamp_ms = timestamp_ms;
    packet.water_in_mv = water_in_mv;
    packet.board_voltage_mv = board_voltage_mv;
    mav_array_memcpy(packet.encoder, encoder, sizeof(int32_t)*2);
    mav_array_memcpy(packet.valve_current_x10, valve_current_x10, sizeof(uint16_t)*40);
    mav_array_memcpy(packet.sensor_data, sensor_data, sizeof(uint16_t)*24);
    mav_array_memcpy(packet.temp_x10, temp_x10, sizeof(int16_t)*3);
    mav_array_memcpy(packet.valve_state, valve_state, sizeof(uint8_t)*40);
        memcpy(_MAV_PAYLOAD_NON_CONST(msg), &packet, MAVLINK_MSG_ID_VALVE_STATUS_LEN);
#endif

    msg->msgid = MAVLINK_MSG_ID_VALVE_STATUS;
    return mavlink_finalize_message_chan(msg, system_id, component_id, chan, MAVLINK_MSG_ID_VALVE_STATUS_MIN_LEN, MAVLINK_MSG_ID_VALVE_STATUS_LEN, MAVLINK_MSG_ID_VALVE_STATUS_CRC);
}

/**
 * @brief Encode a valve_status struct
 *
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param msg The MAVLink message to compress the data into
 * @param valve_status C-struct to read the message contents from
 */
static inline uint16_t mavlink_msg_valve_status_encode(uint8_t system_id, uint8_t component_id, mavlink_message_t* msg, const mavlink_valve_status_t* valve_status)
{
    return mavlink_msg_valve_status_pack(system_id, component_id, msg, valve_status->timestamp_ms, valve_status->valve_current_x10, valve_status->valve_state, valve_status->encoder, valve_status->sensor_data, valve_status->water_in_mv, valve_status->board_voltage_mv, valve_status->temp_x10);
}

/**
 * @brief Encode a valve_status struct on a channel
 *
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param chan The MAVLink channel this message will be sent over
 * @param msg The MAVLink message to compress the data into
 * @param valve_status C-struct to read the message contents from
 */
static inline uint16_t mavlink_msg_valve_status_encode_chan(uint8_t system_id, uint8_t component_id, uint8_t chan, mavlink_message_t* msg, const mavlink_valve_status_t* valve_status)
{
    return mavlink_msg_valve_status_pack_chan(system_id, component_id, chan, msg, valve_status->timestamp_ms, valve_status->valve_current_x10, valve_status->valve_state, valve_status->encoder, valve_status->sensor_data, valve_status->water_in_mv, valve_status->board_voltage_mv, valve_status->temp_x10);
}

/**
 * @brief Encode a valve_status struct with provided status structure
 *
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param status MAVLink status structure
 * @param msg The MAVLink message to compress the data into
 * @param valve_status C-struct to read the message contents from
 */
static inline uint16_t mavlink_msg_valve_status_encode_status(uint8_t system_id, uint8_t component_id, mavlink_status_t* _status, mavlink_message_t* msg, const mavlink_valve_status_t* valve_status)
{
    return mavlink_msg_valve_status_pack_status(system_id, component_id, _status, msg,  valve_status->timestamp_ms, valve_status->valve_current_x10, valve_status->valve_state, valve_status->encoder, valve_status->sensor_data, valve_status->water_in_mv, valve_status->board_voltage_mv, valve_status->temp_x10);
}

/**
 * @brief Send a valve_status message
 * @param chan MAVLink channel to send the message
 *
 * @param timestamp_ms [ms] Timestamp from the sender clock.
 * @param valve_current_x10  Valve current readback in 10 mA units. Source: Modbus registers 2-21.
 * @param valve_state  Valve state for 40 valves: 0 normal, 2 alarm, 3 offline. Source: Modbus registers 56-60.
 * @param encoder  Encoder 1 and encoder 2 counts. Source: Modbus registers 46-49.
 * @param sensor_data  Analog sensor 1-24 raw values. Source: Modbus registers 22-45.
 * @param water_in_mv [mV] Water ingress sensor voltage. Source: Modbus register 51.
 * @param board_voltage_mv [mV] Board supply voltage. Source: Modbus register 55.
 * @param temp_x10  Temperature channels 1, 2 and board temperature in 0.1 degC units. Source: Modbus registers 52-54.
 */
#ifdef MAVLINK_USE_CONVENIENCE_FUNCTIONS

static inline void mavlink_msg_valve_status_send(mavlink_channel_t chan, uint32_t timestamp_ms, const uint16_t *valve_current_x10, const uint8_t *valve_state, const int32_t *encoder, const uint16_t *sensor_data, uint16_t water_in_mv, uint16_t board_voltage_mv, const int16_t *temp_x10)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    char buf[MAVLINK_MSG_ID_VALVE_STATUS_LEN];
    _mav_put_uint32_t(buf, 0, timestamp_ms);
    _mav_put_uint16_t(buf, 140, water_in_mv);
    _mav_put_uint16_t(buf, 142, board_voltage_mv);
    _mav_put_int32_t_array(buf, 4, encoder, 2);
    _mav_put_uint16_t_array(buf, 12, valve_current_x10, 40);
    _mav_put_uint16_t_array(buf, 92, sensor_data, 24);
    _mav_put_int16_t_array(buf, 144, temp_x10, 3);
    _mav_put_uint8_t_array(buf, 150, valve_state, 40);
    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_VALVE_STATUS, buf, MAVLINK_MSG_ID_VALVE_STATUS_MIN_LEN, MAVLINK_MSG_ID_VALVE_STATUS_LEN, MAVLINK_MSG_ID_VALVE_STATUS_CRC);
#else
    mavlink_valve_status_t packet;
    packet.timestamp_ms = timestamp_ms;
    packet.water_in_mv = water_in_mv;
    packet.board_voltage_mv = board_voltage_mv;
    mav_array_memcpy(packet.encoder, encoder, sizeof(int32_t)*2);
    mav_array_memcpy(packet.valve_current_x10, valve_current_x10, sizeof(uint16_t)*40);
    mav_array_memcpy(packet.sensor_data, sensor_data, sizeof(uint16_t)*24);
    mav_array_memcpy(packet.temp_x10, temp_x10, sizeof(int16_t)*3);
    mav_array_memcpy(packet.valve_state, valve_state, sizeof(uint8_t)*40);
    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_VALVE_STATUS, (const char *)&packet, MAVLINK_MSG_ID_VALVE_STATUS_MIN_LEN, MAVLINK_MSG_ID_VALVE_STATUS_LEN, MAVLINK_MSG_ID_VALVE_STATUS_CRC);
#endif
}

/**
 * @brief Send a valve_status message
 * @param chan MAVLink channel to send the message
 * @param struct The MAVLink struct to serialize
 */
static inline void mavlink_msg_valve_status_send_struct(mavlink_channel_t chan, const mavlink_valve_status_t* valve_status)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    mavlink_msg_valve_status_send(chan, valve_status->timestamp_ms, valve_status->valve_current_x10, valve_status->valve_state, valve_status->encoder, valve_status->sensor_data, valve_status->water_in_mv, valve_status->board_voltage_mv, valve_status->temp_x10);
#else
    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_VALVE_STATUS, (const char *)valve_status, MAVLINK_MSG_ID_VALVE_STATUS_MIN_LEN, MAVLINK_MSG_ID_VALVE_STATUS_LEN, MAVLINK_MSG_ID_VALVE_STATUS_CRC);
#endif
}

#if MAVLINK_MSG_ID_VALVE_STATUS_LEN <= MAVLINK_MAX_PAYLOAD_LEN
/*
  This variant of _send() can be used to save stack space by reusing
  memory from the receive buffer.  The caller provides a
  mavlink_message_t which is the size of a full mavlink message. This
  is usually the receive buffer for the channel, and allows a reply to an
  incoming message with minimum stack space usage.
 */
static inline void mavlink_msg_valve_status_send_buf(mavlink_message_t *msgbuf, mavlink_channel_t chan,  uint32_t timestamp_ms, const uint16_t *valve_current_x10, const uint8_t *valve_state, const int32_t *encoder, const uint16_t *sensor_data, uint16_t water_in_mv, uint16_t board_voltage_mv, const int16_t *temp_x10)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    char *buf = (char *)msgbuf;
    _mav_put_uint32_t(buf, 0, timestamp_ms);
    _mav_put_uint16_t(buf, 140, water_in_mv);
    _mav_put_uint16_t(buf, 142, board_voltage_mv);
    _mav_put_int32_t_array(buf, 4, encoder, 2);
    _mav_put_uint16_t_array(buf, 12, valve_current_x10, 40);
    _mav_put_uint16_t_array(buf, 92, sensor_data, 24);
    _mav_put_int16_t_array(buf, 144, temp_x10, 3);
    _mav_put_uint8_t_array(buf, 150, valve_state, 40);
    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_VALVE_STATUS, buf, MAVLINK_MSG_ID_VALVE_STATUS_MIN_LEN, MAVLINK_MSG_ID_VALVE_STATUS_LEN, MAVLINK_MSG_ID_VALVE_STATUS_CRC);
#else
    mavlink_valve_status_t *packet = (mavlink_valve_status_t *)msgbuf;
    packet->timestamp_ms = timestamp_ms;
    packet->water_in_mv = water_in_mv;
    packet->board_voltage_mv = board_voltage_mv;
    mav_array_memcpy(packet->encoder, encoder, sizeof(int32_t)*2);
    mav_array_memcpy(packet->valve_current_x10, valve_current_x10, sizeof(uint16_t)*40);
    mav_array_memcpy(packet->sensor_data, sensor_data, sizeof(uint16_t)*24);
    mav_array_memcpy(packet->temp_x10, temp_x10, sizeof(int16_t)*3);
    mav_array_memcpy(packet->valve_state, valve_state, sizeof(uint8_t)*40);
    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_VALVE_STATUS, (const char *)packet, MAVLINK_MSG_ID_VALVE_STATUS_MIN_LEN, MAVLINK_MSG_ID_VALVE_STATUS_LEN, MAVLINK_MSG_ID_VALVE_STATUS_CRC);
#endif
}
#endif

#endif

// MESSAGE VALVE_STATUS UNPACKING


/**
 * @brief Get field timestamp_ms from valve_status message
 *
 * @return [ms] Timestamp from the sender clock.
 */
static inline uint32_t mavlink_msg_valve_status_get_timestamp_ms(const mavlink_message_t* msg)
{
    return _MAV_RETURN_uint32_t(msg,  0);
}

/**
 * @brief Get field valve_current_x10 from valve_status message
 *
 * @return  Valve current readback in 10 mA units. Source: Modbus registers 2-21.
 */
static inline uint16_t mavlink_msg_valve_status_get_valve_current_x10(const mavlink_message_t* msg, uint16_t *valve_current_x10)
{
    return _MAV_RETURN_uint16_t_array(msg, valve_current_x10, 40,  12);
}

/**
 * @brief Get field valve_state from valve_status message
 *
 * @return  Valve state for 40 valves: 0 normal, 2 alarm, 3 offline. Source: Modbus registers 56-60.
 */
static inline uint16_t mavlink_msg_valve_status_get_valve_state(const mavlink_message_t* msg, uint8_t *valve_state)
{
    return _MAV_RETURN_uint8_t_array(msg, valve_state, 40,  150);
}

/**
 * @brief Get field encoder from valve_status message
 *
 * @return  Encoder 1 and encoder 2 counts. Source: Modbus registers 46-49.
 */
static inline uint16_t mavlink_msg_valve_status_get_encoder(const mavlink_message_t* msg, int32_t *encoder)
{
    return _MAV_RETURN_int32_t_array(msg, encoder, 2,  4);
}

/**
 * @brief Get field sensor_data from valve_status message
 *
 * @return  Analog sensor 1-24 raw values. Source: Modbus registers 22-45.
 */
static inline uint16_t mavlink_msg_valve_status_get_sensor_data(const mavlink_message_t* msg, uint16_t *sensor_data)
{
    return _MAV_RETURN_uint16_t_array(msg, sensor_data, 24,  92);
}

/**
 * @brief Get field water_in_mv from valve_status message
 *
 * @return [mV] Water ingress sensor voltage. Source: Modbus register 51.
 */
static inline uint16_t mavlink_msg_valve_status_get_water_in_mv(const mavlink_message_t* msg)
{
    return _MAV_RETURN_uint16_t(msg,  140);
}

/**
 * @brief Get field board_voltage_mv from valve_status message
 *
 * @return [mV] Board supply voltage. Source: Modbus register 55.
 */
static inline uint16_t mavlink_msg_valve_status_get_board_voltage_mv(const mavlink_message_t* msg)
{
    return _MAV_RETURN_uint16_t(msg,  142);
}

/**
 * @brief Get field temp_x10 from valve_status message
 *
 * @return  Temperature channels 1, 2 and board temperature in 0.1 degC units. Source: Modbus registers 52-54.
 */
static inline uint16_t mavlink_msg_valve_status_get_temp_x10(const mavlink_message_t* msg, int16_t *temp_x10)
{
    return _MAV_RETURN_int16_t_array(msg, temp_x10, 3,  144);
}

/**
 * @brief Decode a valve_status message into a struct
 *
 * @param msg The message to decode
 * @param valve_status C-struct to decode the message contents into
 */
static inline void mavlink_msg_valve_status_decode(const mavlink_message_t* msg, mavlink_valve_status_t* valve_status)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    valve_status->timestamp_ms = mavlink_msg_valve_status_get_timestamp_ms(msg);
    mavlink_msg_valve_status_get_encoder(msg, valve_status->encoder);
    mavlink_msg_valve_status_get_valve_current_x10(msg, valve_status->valve_current_x10);
    mavlink_msg_valve_status_get_sensor_data(msg, valve_status->sensor_data);
    valve_status->water_in_mv = mavlink_msg_valve_status_get_water_in_mv(msg);
    valve_status->board_voltage_mv = mavlink_msg_valve_status_get_board_voltage_mv(msg);
    mavlink_msg_valve_status_get_temp_x10(msg, valve_status->temp_x10);
    mavlink_msg_valve_status_get_valve_state(msg, valve_status->valve_state);
#else
        uint8_t len = msg->len < MAVLINK_MSG_ID_VALVE_STATUS_LEN? msg->len : MAVLINK_MSG_ID_VALVE_STATUS_LEN;
        memset(valve_status, 0, MAVLINK_MSG_ID_VALVE_STATUS_LEN);
    memcpy(valve_status, _MAV_PAYLOAD(msg), len);
#endif
}
