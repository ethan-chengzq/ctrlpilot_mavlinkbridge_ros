#pragma once
// MESSAGE DVL_DATA PACKING

#define MAVLINK_MSG_ID_DVL_DATA 18


typedef struct __mavlink_dvl_data_t {
 uint32_t timestamp_ms; /*< [ms] Timestamp from the sender clock.*/
 float BT_range[4]; /*< [m] Bottom-track range for four beams; 0 means bad bottom range detection.*/
 float BT_vel[4]; /*< [m/s] Bottom-track velocity for four beams. Beam meaning depends on DVL coordinate frame; common mapping is v1 east/Y, v2 north/X, v3 up/Z.*/
 float BT_max_depth; /*< [m] Maximum bottom-track depth, expected range 1-6553.5 m.*/
 float WP_Cell1_vel[4]; /*< [m/s] Water-profile cell 1 velocity for four beams.*/
 float WP_Cell2_vel[4]; /*< [m/s] Water-profile cell 2 velocity for four beams.*/
 float WP_Cell3_vel[4]; /*< [m/s] Water-profile cell 3 velocity for four beams.*/
 float WP_Cell4_vel[4]; /*< [m/s] Water-profile cell 4 velocity for four beams.*/
 float WP_Cell5_vel[4]; /*< [m/s] Water-profile cell 5 velocity for four beams.*/
 float WP_Cell6_vel[4]; /*< [m/s] Water-profile cell 6 velocity for four beams.*/
 float WP_Cell7_vel[4]; /*< [m/s] Water-profile cell 7 velocity for four beams.*/
 float WP_Cell8_vel[4]; /*< [m/s] Water-profile cell 8 velocity for four beams.*/
 float WP_Cell9_vel[4]; /*< [m/s] Water-profile cell 9 velocity for four beams.*/
 float WP_Cell10_vel[4]; /*< [m/s] Water-profile cell 10 velocity for four beams.*/
 uint8_t BT_percent_good[4]; /*< [%] Bottom-track percent-good for each beam.*/
 uint8_t WP_Cell1_percent_good[4]; /*< [%] Water-profile cell 1 percent-good for each beam.*/
 uint8_t WP_Cell2_percent_good[4]; /*< [%] Water-profile cell 2 percent-good for each beam.*/
 uint8_t WP_Cell3_percent_good[4]; /*< [%] Water-profile cell 3 percent-good for each beam.*/
 uint8_t WP_Cell4_percent_good[4]; /*< [%] Water-profile cell 4 percent-good for each beam.*/
 uint8_t WP_Cell5_percent_good[4]; /*< [%] Water-profile cell 5 percent-good for each beam.*/
 uint8_t WP_Cell6_percent_good[4]; /*< [%] Water-profile cell 6 percent-good for each beam.*/
 uint8_t WP_Cell7_percent_good[4]; /*< [%] Water-profile cell 7 percent-good for each beam.*/
 uint8_t WP_Cell8_percent_good[4]; /*< [%] Water-profile cell 8 percent-good for each beam.*/
 uint8_t WP_Cell9_percent_good[4]; /*< [%] Water-profile cell 9 percent-good for each beam.*/
 uint8_t WP_Cell10_percent_good[4]; /*< [%] Water-profile cell 10 percent-good for each beam.*/
} mavlink_dvl_data_t;

#define MAVLINK_MSG_ID_DVL_DATA_LEN 244
#define MAVLINK_MSG_ID_DVL_DATA_MIN_LEN 244
#define MAVLINK_MSG_ID_18_LEN 244
#define MAVLINK_MSG_ID_18_MIN_LEN 244

#define MAVLINK_MSG_ID_DVL_DATA_CRC 145
#define MAVLINK_MSG_ID_18_CRC 145

#define MAVLINK_MSG_DVL_DATA_FIELD_BT_RANGE_LEN 4
#define MAVLINK_MSG_DVL_DATA_FIELD_BT_VEL_LEN 4
#define MAVLINK_MSG_DVL_DATA_FIELD_WP_CELL1_VEL_LEN 4
#define MAVLINK_MSG_DVL_DATA_FIELD_WP_CELL2_VEL_LEN 4
#define MAVLINK_MSG_DVL_DATA_FIELD_WP_CELL3_VEL_LEN 4
#define MAVLINK_MSG_DVL_DATA_FIELD_WP_CELL4_VEL_LEN 4
#define MAVLINK_MSG_DVL_DATA_FIELD_WP_CELL5_VEL_LEN 4
#define MAVLINK_MSG_DVL_DATA_FIELD_WP_CELL6_VEL_LEN 4
#define MAVLINK_MSG_DVL_DATA_FIELD_WP_CELL7_VEL_LEN 4
#define MAVLINK_MSG_DVL_DATA_FIELD_WP_CELL8_VEL_LEN 4
#define MAVLINK_MSG_DVL_DATA_FIELD_WP_CELL9_VEL_LEN 4
#define MAVLINK_MSG_DVL_DATA_FIELD_WP_CELL10_VEL_LEN 4
#define MAVLINK_MSG_DVL_DATA_FIELD_BT_PERCENT_GOOD_LEN 4
#define MAVLINK_MSG_DVL_DATA_FIELD_WP_CELL1_PERCENT_GOOD_LEN 4
#define MAVLINK_MSG_DVL_DATA_FIELD_WP_CELL2_PERCENT_GOOD_LEN 4
#define MAVLINK_MSG_DVL_DATA_FIELD_WP_CELL3_PERCENT_GOOD_LEN 4
#define MAVLINK_MSG_DVL_DATA_FIELD_WP_CELL4_PERCENT_GOOD_LEN 4
#define MAVLINK_MSG_DVL_DATA_FIELD_WP_CELL5_PERCENT_GOOD_LEN 4
#define MAVLINK_MSG_DVL_DATA_FIELD_WP_CELL6_PERCENT_GOOD_LEN 4
#define MAVLINK_MSG_DVL_DATA_FIELD_WP_CELL7_PERCENT_GOOD_LEN 4
#define MAVLINK_MSG_DVL_DATA_FIELD_WP_CELL8_PERCENT_GOOD_LEN 4
#define MAVLINK_MSG_DVL_DATA_FIELD_WP_CELL9_PERCENT_GOOD_LEN 4
#define MAVLINK_MSG_DVL_DATA_FIELD_WP_CELL10_PERCENT_GOOD_LEN 4

#if MAVLINK_COMMAND_24BIT
#define MAVLINK_MESSAGE_INFO_DVL_DATA { \
    18, \
    "DVL_DATA", \
    25, \
    {  { "timestamp_ms", NULL, MAVLINK_TYPE_UINT32_T, 0, 0, offsetof(mavlink_dvl_data_t, timestamp_ms) }, \
         { "BT_range", NULL, MAVLINK_TYPE_FLOAT, 4, 4, offsetof(mavlink_dvl_data_t, BT_range) }, \
         { "BT_vel", NULL, MAVLINK_TYPE_FLOAT, 4, 20, offsetof(mavlink_dvl_data_t, BT_vel) }, \
         { "BT_percent_good", NULL, MAVLINK_TYPE_UINT8_T, 4, 200, offsetof(mavlink_dvl_data_t, BT_percent_good) }, \
         { "BT_max_depth", NULL, MAVLINK_TYPE_FLOAT, 0, 36, offsetof(mavlink_dvl_data_t, BT_max_depth) }, \
         { "WP_Cell1_vel", NULL, MAVLINK_TYPE_FLOAT, 4, 40, offsetof(mavlink_dvl_data_t, WP_Cell1_vel) }, \
         { "WP_Cell1_percent_good", NULL, MAVLINK_TYPE_UINT8_T, 4, 204, offsetof(mavlink_dvl_data_t, WP_Cell1_percent_good) }, \
         { "WP_Cell2_vel", NULL, MAVLINK_TYPE_FLOAT, 4, 56, offsetof(mavlink_dvl_data_t, WP_Cell2_vel) }, \
         { "WP_Cell2_percent_good", NULL, MAVLINK_TYPE_UINT8_T, 4, 208, offsetof(mavlink_dvl_data_t, WP_Cell2_percent_good) }, \
         { "WP_Cell3_vel", NULL, MAVLINK_TYPE_FLOAT, 4, 72, offsetof(mavlink_dvl_data_t, WP_Cell3_vel) }, \
         { "WP_Cell3_percent_good", NULL, MAVLINK_TYPE_UINT8_T, 4, 212, offsetof(mavlink_dvl_data_t, WP_Cell3_percent_good) }, \
         { "WP_Cell4_vel", NULL, MAVLINK_TYPE_FLOAT, 4, 88, offsetof(mavlink_dvl_data_t, WP_Cell4_vel) }, \
         { "WP_Cell4_percent_good", NULL, MAVLINK_TYPE_UINT8_T, 4, 216, offsetof(mavlink_dvl_data_t, WP_Cell4_percent_good) }, \
         { "WP_Cell5_vel", NULL, MAVLINK_TYPE_FLOAT, 4, 104, offsetof(mavlink_dvl_data_t, WP_Cell5_vel) }, \
         { "WP_Cell5_percent_good", NULL, MAVLINK_TYPE_UINT8_T, 4, 220, offsetof(mavlink_dvl_data_t, WP_Cell5_percent_good) }, \
         { "WP_Cell6_vel", NULL, MAVLINK_TYPE_FLOAT, 4, 120, offsetof(mavlink_dvl_data_t, WP_Cell6_vel) }, \
         { "WP_Cell6_percent_good", NULL, MAVLINK_TYPE_UINT8_T, 4, 224, offsetof(mavlink_dvl_data_t, WP_Cell6_percent_good) }, \
         { "WP_Cell7_vel", NULL, MAVLINK_TYPE_FLOAT, 4, 136, offsetof(mavlink_dvl_data_t, WP_Cell7_vel) }, \
         { "WP_Cell7_percent_good", NULL, MAVLINK_TYPE_UINT8_T, 4, 228, offsetof(mavlink_dvl_data_t, WP_Cell7_percent_good) }, \
         { "WP_Cell8_vel", NULL, MAVLINK_TYPE_FLOAT, 4, 152, offsetof(mavlink_dvl_data_t, WP_Cell8_vel) }, \
         { "WP_Cell8_percent_good", NULL, MAVLINK_TYPE_UINT8_T, 4, 232, offsetof(mavlink_dvl_data_t, WP_Cell8_percent_good) }, \
         { "WP_Cell9_vel", NULL, MAVLINK_TYPE_FLOAT, 4, 168, offsetof(mavlink_dvl_data_t, WP_Cell9_vel) }, \
         { "WP_Cell9_percent_good", NULL, MAVLINK_TYPE_UINT8_T, 4, 236, offsetof(mavlink_dvl_data_t, WP_Cell9_percent_good) }, \
         { "WP_Cell10_vel", NULL, MAVLINK_TYPE_FLOAT, 4, 184, offsetof(mavlink_dvl_data_t, WP_Cell10_vel) }, \
         { "WP_Cell10_percent_good", NULL, MAVLINK_TYPE_UINT8_T, 4, 240, offsetof(mavlink_dvl_data_t, WP_Cell10_percent_good) }, \
         } \
}
#else
#define MAVLINK_MESSAGE_INFO_DVL_DATA { \
    "DVL_DATA", \
    25, \
    {  { "timestamp_ms", NULL, MAVLINK_TYPE_UINT32_T, 0, 0, offsetof(mavlink_dvl_data_t, timestamp_ms) }, \
         { "BT_range", NULL, MAVLINK_TYPE_FLOAT, 4, 4, offsetof(mavlink_dvl_data_t, BT_range) }, \
         { "BT_vel", NULL, MAVLINK_TYPE_FLOAT, 4, 20, offsetof(mavlink_dvl_data_t, BT_vel) }, \
         { "BT_percent_good", NULL, MAVLINK_TYPE_UINT8_T, 4, 200, offsetof(mavlink_dvl_data_t, BT_percent_good) }, \
         { "BT_max_depth", NULL, MAVLINK_TYPE_FLOAT, 0, 36, offsetof(mavlink_dvl_data_t, BT_max_depth) }, \
         { "WP_Cell1_vel", NULL, MAVLINK_TYPE_FLOAT, 4, 40, offsetof(mavlink_dvl_data_t, WP_Cell1_vel) }, \
         { "WP_Cell1_percent_good", NULL, MAVLINK_TYPE_UINT8_T, 4, 204, offsetof(mavlink_dvl_data_t, WP_Cell1_percent_good) }, \
         { "WP_Cell2_vel", NULL, MAVLINK_TYPE_FLOAT, 4, 56, offsetof(mavlink_dvl_data_t, WP_Cell2_vel) }, \
         { "WP_Cell2_percent_good", NULL, MAVLINK_TYPE_UINT8_T, 4, 208, offsetof(mavlink_dvl_data_t, WP_Cell2_percent_good) }, \
         { "WP_Cell3_vel", NULL, MAVLINK_TYPE_FLOAT, 4, 72, offsetof(mavlink_dvl_data_t, WP_Cell3_vel) }, \
         { "WP_Cell3_percent_good", NULL, MAVLINK_TYPE_UINT8_T, 4, 212, offsetof(mavlink_dvl_data_t, WP_Cell3_percent_good) }, \
         { "WP_Cell4_vel", NULL, MAVLINK_TYPE_FLOAT, 4, 88, offsetof(mavlink_dvl_data_t, WP_Cell4_vel) }, \
         { "WP_Cell4_percent_good", NULL, MAVLINK_TYPE_UINT8_T, 4, 216, offsetof(mavlink_dvl_data_t, WP_Cell4_percent_good) }, \
         { "WP_Cell5_vel", NULL, MAVLINK_TYPE_FLOAT, 4, 104, offsetof(mavlink_dvl_data_t, WP_Cell5_vel) }, \
         { "WP_Cell5_percent_good", NULL, MAVLINK_TYPE_UINT8_T, 4, 220, offsetof(mavlink_dvl_data_t, WP_Cell5_percent_good) }, \
         { "WP_Cell6_vel", NULL, MAVLINK_TYPE_FLOAT, 4, 120, offsetof(mavlink_dvl_data_t, WP_Cell6_vel) }, \
         { "WP_Cell6_percent_good", NULL, MAVLINK_TYPE_UINT8_T, 4, 224, offsetof(mavlink_dvl_data_t, WP_Cell6_percent_good) }, \
         { "WP_Cell7_vel", NULL, MAVLINK_TYPE_FLOAT, 4, 136, offsetof(mavlink_dvl_data_t, WP_Cell7_vel) }, \
         { "WP_Cell7_percent_good", NULL, MAVLINK_TYPE_UINT8_T, 4, 228, offsetof(mavlink_dvl_data_t, WP_Cell7_percent_good) }, \
         { "WP_Cell8_vel", NULL, MAVLINK_TYPE_FLOAT, 4, 152, offsetof(mavlink_dvl_data_t, WP_Cell8_vel) }, \
         { "WP_Cell8_percent_good", NULL, MAVLINK_TYPE_UINT8_T, 4, 232, offsetof(mavlink_dvl_data_t, WP_Cell8_percent_good) }, \
         { "WP_Cell9_vel", NULL, MAVLINK_TYPE_FLOAT, 4, 168, offsetof(mavlink_dvl_data_t, WP_Cell9_vel) }, \
         { "WP_Cell9_percent_good", NULL, MAVLINK_TYPE_UINT8_T, 4, 236, offsetof(mavlink_dvl_data_t, WP_Cell9_percent_good) }, \
         { "WP_Cell10_vel", NULL, MAVLINK_TYPE_FLOAT, 4, 184, offsetof(mavlink_dvl_data_t, WP_Cell10_vel) }, \
         { "WP_Cell10_percent_good", NULL, MAVLINK_TYPE_UINT8_T, 4, 240, offsetof(mavlink_dvl_data_t, WP_Cell10_percent_good) }, \
         } \
}
#endif

/**
 * @brief Pack a dvl_data message
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param msg The MAVLink message to compress the data into
 *
 * @param timestamp_ms [ms] Timestamp from the sender clock.
 * @param BT_range [m] Bottom-track range for four beams; 0 means bad bottom range detection.
 * @param BT_vel [m/s] Bottom-track velocity for four beams. Beam meaning depends on DVL coordinate frame; common mapping is v1 east/Y, v2 north/X, v3 up/Z.
 * @param BT_percent_good [%] Bottom-track percent-good for each beam.
 * @param BT_max_depth [m] Maximum bottom-track depth, expected range 1-6553.5 m.
 * @param WP_Cell1_vel [m/s] Water-profile cell 1 velocity for four beams.
 * @param WP_Cell1_percent_good [%] Water-profile cell 1 percent-good for each beam.
 * @param WP_Cell2_vel [m/s] Water-profile cell 2 velocity for four beams.
 * @param WP_Cell2_percent_good [%] Water-profile cell 2 percent-good for each beam.
 * @param WP_Cell3_vel [m/s] Water-profile cell 3 velocity for four beams.
 * @param WP_Cell3_percent_good [%] Water-profile cell 3 percent-good for each beam.
 * @param WP_Cell4_vel [m/s] Water-profile cell 4 velocity for four beams.
 * @param WP_Cell4_percent_good [%] Water-profile cell 4 percent-good for each beam.
 * @param WP_Cell5_vel [m/s] Water-profile cell 5 velocity for four beams.
 * @param WP_Cell5_percent_good [%] Water-profile cell 5 percent-good for each beam.
 * @param WP_Cell6_vel [m/s] Water-profile cell 6 velocity for four beams.
 * @param WP_Cell6_percent_good [%] Water-profile cell 6 percent-good for each beam.
 * @param WP_Cell7_vel [m/s] Water-profile cell 7 velocity for four beams.
 * @param WP_Cell7_percent_good [%] Water-profile cell 7 percent-good for each beam.
 * @param WP_Cell8_vel [m/s] Water-profile cell 8 velocity for four beams.
 * @param WP_Cell8_percent_good [%] Water-profile cell 8 percent-good for each beam.
 * @param WP_Cell9_vel [m/s] Water-profile cell 9 velocity for four beams.
 * @param WP_Cell9_percent_good [%] Water-profile cell 9 percent-good for each beam.
 * @param WP_Cell10_vel [m/s] Water-profile cell 10 velocity for four beams.
 * @param WP_Cell10_percent_good [%] Water-profile cell 10 percent-good for each beam.
 * @return length of the message in bytes (excluding serial stream start sign)
 */
static inline uint16_t mavlink_msg_dvl_data_pack(uint8_t system_id, uint8_t component_id, mavlink_message_t* msg,
                               uint32_t timestamp_ms, const float *BT_range, const float *BT_vel, const uint8_t *BT_percent_good, float BT_max_depth, const float *WP_Cell1_vel, const uint8_t *WP_Cell1_percent_good, const float *WP_Cell2_vel, const uint8_t *WP_Cell2_percent_good, const float *WP_Cell3_vel, const uint8_t *WP_Cell3_percent_good, const float *WP_Cell4_vel, const uint8_t *WP_Cell4_percent_good, const float *WP_Cell5_vel, const uint8_t *WP_Cell5_percent_good, const float *WP_Cell6_vel, const uint8_t *WP_Cell6_percent_good, const float *WP_Cell7_vel, const uint8_t *WP_Cell7_percent_good, const float *WP_Cell8_vel, const uint8_t *WP_Cell8_percent_good, const float *WP_Cell9_vel, const uint8_t *WP_Cell9_percent_good, const float *WP_Cell10_vel, const uint8_t *WP_Cell10_percent_good)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    char buf[MAVLINK_MSG_ID_DVL_DATA_LEN];
    _mav_put_uint32_t(buf, 0, timestamp_ms);
    _mav_put_float(buf, 36, BT_max_depth);
    _mav_put_float_array(buf, 4, BT_range, 4);
    _mav_put_float_array(buf, 20, BT_vel, 4);
    _mav_put_float_array(buf, 40, WP_Cell1_vel, 4);
    _mav_put_float_array(buf, 56, WP_Cell2_vel, 4);
    _mav_put_float_array(buf, 72, WP_Cell3_vel, 4);
    _mav_put_float_array(buf, 88, WP_Cell4_vel, 4);
    _mav_put_float_array(buf, 104, WP_Cell5_vel, 4);
    _mav_put_float_array(buf, 120, WP_Cell6_vel, 4);
    _mav_put_float_array(buf, 136, WP_Cell7_vel, 4);
    _mav_put_float_array(buf, 152, WP_Cell8_vel, 4);
    _mav_put_float_array(buf, 168, WP_Cell9_vel, 4);
    _mav_put_float_array(buf, 184, WP_Cell10_vel, 4);
    _mav_put_uint8_t_array(buf, 200, BT_percent_good, 4);
    _mav_put_uint8_t_array(buf, 204, WP_Cell1_percent_good, 4);
    _mav_put_uint8_t_array(buf, 208, WP_Cell2_percent_good, 4);
    _mav_put_uint8_t_array(buf, 212, WP_Cell3_percent_good, 4);
    _mav_put_uint8_t_array(buf, 216, WP_Cell4_percent_good, 4);
    _mav_put_uint8_t_array(buf, 220, WP_Cell5_percent_good, 4);
    _mav_put_uint8_t_array(buf, 224, WP_Cell6_percent_good, 4);
    _mav_put_uint8_t_array(buf, 228, WP_Cell7_percent_good, 4);
    _mav_put_uint8_t_array(buf, 232, WP_Cell8_percent_good, 4);
    _mav_put_uint8_t_array(buf, 236, WP_Cell9_percent_good, 4);
    _mav_put_uint8_t_array(buf, 240, WP_Cell10_percent_good, 4);
        memcpy(_MAV_PAYLOAD_NON_CONST(msg), buf, MAVLINK_MSG_ID_DVL_DATA_LEN);
#else
    mavlink_dvl_data_t packet;
    packet.timestamp_ms = timestamp_ms;
    packet.BT_max_depth = BT_max_depth;
    mav_array_memcpy(packet.BT_range, BT_range, sizeof(float)*4);
    mav_array_memcpy(packet.BT_vel, BT_vel, sizeof(float)*4);
    mav_array_memcpy(packet.WP_Cell1_vel, WP_Cell1_vel, sizeof(float)*4);
    mav_array_memcpy(packet.WP_Cell2_vel, WP_Cell2_vel, sizeof(float)*4);
    mav_array_memcpy(packet.WP_Cell3_vel, WP_Cell3_vel, sizeof(float)*4);
    mav_array_memcpy(packet.WP_Cell4_vel, WP_Cell4_vel, sizeof(float)*4);
    mav_array_memcpy(packet.WP_Cell5_vel, WP_Cell5_vel, sizeof(float)*4);
    mav_array_memcpy(packet.WP_Cell6_vel, WP_Cell6_vel, sizeof(float)*4);
    mav_array_memcpy(packet.WP_Cell7_vel, WP_Cell7_vel, sizeof(float)*4);
    mav_array_memcpy(packet.WP_Cell8_vel, WP_Cell8_vel, sizeof(float)*4);
    mav_array_memcpy(packet.WP_Cell9_vel, WP_Cell9_vel, sizeof(float)*4);
    mav_array_memcpy(packet.WP_Cell10_vel, WP_Cell10_vel, sizeof(float)*4);
    mav_array_memcpy(packet.BT_percent_good, BT_percent_good, sizeof(uint8_t)*4);
    mav_array_memcpy(packet.WP_Cell1_percent_good, WP_Cell1_percent_good, sizeof(uint8_t)*4);
    mav_array_memcpy(packet.WP_Cell2_percent_good, WP_Cell2_percent_good, sizeof(uint8_t)*4);
    mav_array_memcpy(packet.WP_Cell3_percent_good, WP_Cell3_percent_good, sizeof(uint8_t)*4);
    mav_array_memcpy(packet.WP_Cell4_percent_good, WP_Cell4_percent_good, sizeof(uint8_t)*4);
    mav_array_memcpy(packet.WP_Cell5_percent_good, WP_Cell5_percent_good, sizeof(uint8_t)*4);
    mav_array_memcpy(packet.WP_Cell6_percent_good, WP_Cell6_percent_good, sizeof(uint8_t)*4);
    mav_array_memcpy(packet.WP_Cell7_percent_good, WP_Cell7_percent_good, sizeof(uint8_t)*4);
    mav_array_memcpy(packet.WP_Cell8_percent_good, WP_Cell8_percent_good, sizeof(uint8_t)*4);
    mav_array_memcpy(packet.WP_Cell9_percent_good, WP_Cell9_percent_good, sizeof(uint8_t)*4);
    mav_array_memcpy(packet.WP_Cell10_percent_good, WP_Cell10_percent_good, sizeof(uint8_t)*4);
        memcpy(_MAV_PAYLOAD_NON_CONST(msg), &packet, MAVLINK_MSG_ID_DVL_DATA_LEN);
#endif

    msg->msgid = MAVLINK_MSG_ID_DVL_DATA;
    return mavlink_finalize_message(msg, system_id, component_id, MAVLINK_MSG_ID_DVL_DATA_MIN_LEN, MAVLINK_MSG_ID_DVL_DATA_LEN, MAVLINK_MSG_ID_DVL_DATA_CRC);
}

/**
 * @brief Pack a dvl_data message
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param status MAVLink status structure
 * @param msg The MAVLink message to compress the data into
 *
 * @param timestamp_ms [ms] Timestamp from the sender clock.
 * @param BT_range [m] Bottom-track range for four beams; 0 means bad bottom range detection.
 * @param BT_vel [m/s] Bottom-track velocity for four beams. Beam meaning depends on DVL coordinate frame; common mapping is v1 east/Y, v2 north/X, v3 up/Z.
 * @param BT_percent_good [%] Bottom-track percent-good for each beam.
 * @param BT_max_depth [m] Maximum bottom-track depth, expected range 1-6553.5 m.
 * @param WP_Cell1_vel [m/s] Water-profile cell 1 velocity for four beams.
 * @param WP_Cell1_percent_good [%] Water-profile cell 1 percent-good for each beam.
 * @param WP_Cell2_vel [m/s] Water-profile cell 2 velocity for four beams.
 * @param WP_Cell2_percent_good [%] Water-profile cell 2 percent-good for each beam.
 * @param WP_Cell3_vel [m/s] Water-profile cell 3 velocity for four beams.
 * @param WP_Cell3_percent_good [%] Water-profile cell 3 percent-good for each beam.
 * @param WP_Cell4_vel [m/s] Water-profile cell 4 velocity for four beams.
 * @param WP_Cell4_percent_good [%] Water-profile cell 4 percent-good for each beam.
 * @param WP_Cell5_vel [m/s] Water-profile cell 5 velocity for four beams.
 * @param WP_Cell5_percent_good [%] Water-profile cell 5 percent-good for each beam.
 * @param WP_Cell6_vel [m/s] Water-profile cell 6 velocity for four beams.
 * @param WP_Cell6_percent_good [%] Water-profile cell 6 percent-good for each beam.
 * @param WP_Cell7_vel [m/s] Water-profile cell 7 velocity for four beams.
 * @param WP_Cell7_percent_good [%] Water-profile cell 7 percent-good for each beam.
 * @param WP_Cell8_vel [m/s] Water-profile cell 8 velocity for four beams.
 * @param WP_Cell8_percent_good [%] Water-profile cell 8 percent-good for each beam.
 * @param WP_Cell9_vel [m/s] Water-profile cell 9 velocity for four beams.
 * @param WP_Cell9_percent_good [%] Water-profile cell 9 percent-good for each beam.
 * @param WP_Cell10_vel [m/s] Water-profile cell 10 velocity for four beams.
 * @param WP_Cell10_percent_good [%] Water-profile cell 10 percent-good for each beam.
 * @return length of the message in bytes (excluding serial stream start sign)
 */
static inline uint16_t mavlink_msg_dvl_data_pack_status(uint8_t system_id, uint8_t component_id, mavlink_status_t *_status, mavlink_message_t* msg,
                               uint32_t timestamp_ms, const float *BT_range, const float *BT_vel, const uint8_t *BT_percent_good, float BT_max_depth, const float *WP_Cell1_vel, const uint8_t *WP_Cell1_percent_good, const float *WP_Cell2_vel, const uint8_t *WP_Cell2_percent_good, const float *WP_Cell3_vel, const uint8_t *WP_Cell3_percent_good, const float *WP_Cell4_vel, const uint8_t *WP_Cell4_percent_good, const float *WP_Cell5_vel, const uint8_t *WP_Cell5_percent_good, const float *WP_Cell6_vel, const uint8_t *WP_Cell6_percent_good, const float *WP_Cell7_vel, const uint8_t *WP_Cell7_percent_good, const float *WP_Cell8_vel, const uint8_t *WP_Cell8_percent_good, const float *WP_Cell9_vel, const uint8_t *WP_Cell9_percent_good, const float *WP_Cell10_vel, const uint8_t *WP_Cell10_percent_good)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    char buf[MAVLINK_MSG_ID_DVL_DATA_LEN];
    _mav_put_uint32_t(buf, 0, timestamp_ms);
    _mav_put_float(buf, 36, BT_max_depth);
    _mav_put_float_array(buf, 4, BT_range, 4);
    _mav_put_float_array(buf, 20, BT_vel, 4);
    _mav_put_float_array(buf, 40, WP_Cell1_vel, 4);
    _mav_put_float_array(buf, 56, WP_Cell2_vel, 4);
    _mav_put_float_array(buf, 72, WP_Cell3_vel, 4);
    _mav_put_float_array(buf, 88, WP_Cell4_vel, 4);
    _mav_put_float_array(buf, 104, WP_Cell5_vel, 4);
    _mav_put_float_array(buf, 120, WP_Cell6_vel, 4);
    _mav_put_float_array(buf, 136, WP_Cell7_vel, 4);
    _mav_put_float_array(buf, 152, WP_Cell8_vel, 4);
    _mav_put_float_array(buf, 168, WP_Cell9_vel, 4);
    _mav_put_float_array(buf, 184, WP_Cell10_vel, 4);
    _mav_put_uint8_t_array(buf, 200, BT_percent_good, 4);
    _mav_put_uint8_t_array(buf, 204, WP_Cell1_percent_good, 4);
    _mav_put_uint8_t_array(buf, 208, WP_Cell2_percent_good, 4);
    _mav_put_uint8_t_array(buf, 212, WP_Cell3_percent_good, 4);
    _mav_put_uint8_t_array(buf, 216, WP_Cell4_percent_good, 4);
    _mav_put_uint8_t_array(buf, 220, WP_Cell5_percent_good, 4);
    _mav_put_uint8_t_array(buf, 224, WP_Cell6_percent_good, 4);
    _mav_put_uint8_t_array(buf, 228, WP_Cell7_percent_good, 4);
    _mav_put_uint8_t_array(buf, 232, WP_Cell8_percent_good, 4);
    _mav_put_uint8_t_array(buf, 236, WP_Cell9_percent_good, 4);
    _mav_put_uint8_t_array(buf, 240, WP_Cell10_percent_good, 4);
        memcpy(_MAV_PAYLOAD_NON_CONST(msg), buf, MAVLINK_MSG_ID_DVL_DATA_LEN);
#else
    mavlink_dvl_data_t packet;
    packet.timestamp_ms = timestamp_ms;
    packet.BT_max_depth = BT_max_depth;
    mav_array_memcpy(packet.BT_range, BT_range, sizeof(float)*4);
    mav_array_memcpy(packet.BT_vel, BT_vel, sizeof(float)*4);
    mav_array_memcpy(packet.WP_Cell1_vel, WP_Cell1_vel, sizeof(float)*4);
    mav_array_memcpy(packet.WP_Cell2_vel, WP_Cell2_vel, sizeof(float)*4);
    mav_array_memcpy(packet.WP_Cell3_vel, WP_Cell3_vel, sizeof(float)*4);
    mav_array_memcpy(packet.WP_Cell4_vel, WP_Cell4_vel, sizeof(float)*4);
    mav_array_memcpy(packet.WP_Cell5_vel, WP_Cell5_vel, sizeof(float)*4);
    mav_array_memcpy(packet.WP_Cell6_vel, WP_Cell6_vel, sizeof(float)*4);
    mav_array_memcpy(packet.WP_Cell7_vel, WP_Cell7_vel, sizeof(float)*4);
    mav_array_memcpy(packet.WP_Cell8_vel, WP_Cell8_vel, sizeof(float)*4);
    mav_array_memcpy(packet.WP_Cell9_vel, WP_Cell9_vel, sizeof(float)*4);
    mav_array_memcpy(packet.WP_Cell10_vel, WP_Cell10_vel, sizeof(float)*4);
    mav_array_memcpy(packet.BT_percent_good, BT_percent_good, sizeof(uint8_t)*4);
    mav_array_memcpy(packet.WP_Cell1_percent_good, WP_Cell1_percent_good, sizeof(uint8_t)*4);
    mav_array_memcpy(packet.WP_Cell2_percent_good, WP_Cell2_percent_good, sizeof(uint8_t)*4);
    mav_array_memcpy(packet.WP_Cell3_percent_good, WP_Cell3_percent_good, sizeof(uint8_t)*4);
    mav_array_memcpy(packet.WP_Cell4_percent_good, WP_Cell4_percent_good, sizeof(uint8_t)*4);
    mav_array_memcpy(packet.WP_Cell5_percent_good, WP_Cell5_percent_good, sizeof(uint8_t)*4);
    mav_array_memcpy(packet.WP_Cell6_percent_good, WP_Cell6_percent_good, sizeof(uint8_t)*4);
    mav_array_memcpy(packet.WP_Cell7_percent_good, WP_Cell7_percent_good, sizeof(uint8_t)*4);
    mav_array_memcpy(packet.WP_Cell8_percent_good, WP_Cell8_percent_good, sizeof(uint8_t)*4);
    mav_array_memcpy(packet.WP_Cell9_percent_good, WP_Cell9_percent_good, sizeof(uint8_t)*4);
    mav_array_memcpy(packet.WP_Cell10_percent_good, WP_Cell10_percent_good, sizeof(uint8_t)*4);
        memcpy(_MAV_PAYLOAD_NON_CONST(msg), &packet, MAVLINK_MSG_ID_DVL_DATA_LEN);
#endif

    msg->msgid = MAVLINK_MSG_ID_DVL_DATA;
#if MAVLINK_CRC_EXTRA
    return mavlink_finalize_message_buffer(msg, system_id, component_id, _status, MAVLINK_MSG_ID_DVL_DATA_MIN_LEN, MAVLINK_MSG_ID_DVL_DATA_LEN, MAVLINK_MSG_ID_DVL_DATA_CRC);
#else
    return mavlink_finalize_message_buffer(msg, system_id, component_id, _status, MAVLINK_MSG_ID_DVL_DATA_MIN_LEN, MAVLINK_MSG_ID_DVL_DATA_LEN);
#endif
}

/**
 * @brief Pack a dvl_data message on a channel
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param chan The MAVLink channel this message will be sent over
 * @param msg The MAVLink message to compress the data into
 * @param timestamp_ms [ms] Timestamp from the sender clock.
 * @param BT_range [m] Bottom-track range for four beams; 0 means bad bottom range detection.
 * @param BT_vel [m/s] Bottom-track velocity for four beams. Beam meaning depends on DVL coordinate frame; common mapping is v1 east/Y, v2 north/X, v3 up/Z.
 * @param BT_percent_good [%] Bottom-track percent-good for each beam.
 * @param BT_max_depth [m] Maximum bottom-track depth, expected range 1-6553.5 m.
 * @param WP_Cell1_vel [m/s] Water-profile cell 1 velocity for four beams.
 * @param WP_Cell1_percent_good [%] Water-profile cell 1 percent-good for each beam.
 * @param WP_Cell2_vel [m/s] Water-profile cell 2 velocity for four beams.
 * @param WP_Cell2_percent_good [%] Water-profile cell 2 percent-good for each beam.
 * @param WP_Cell3_vel [m/s] Water-profile cell 3 velocity for four beams.
 * @param WP_Cell3_percent_good [%] Water-profile cell 3 percent-good for each beam.
 * @param WP_Cell4_vel [m/s] Water-profile cell 4 velocity for four beams.
 * @param WP_Cell4_percent_good [%] Water-profile cell 4 percent-good for each beam.
 * @param WP_Cell5_vel [m/s] Water-profile cell 5 velocity for four beams.
 * @param WP_Cell5_percent_good [%] Water-profile cell 5 percent-good for each beam.
 * @param WP_Cell6_vel [m/s] Water-profile cell 6 velocity for four beams.
 * @param WP_Cell6_percent_good [%] Water-profile cell 6 percent-good for each beam.
 * @param WP_Cell7_vel [m/s] Water-profile cell 7 velocity for four beams.
 * @param WP_Cell7_percent_good [%] Water-profile cell 7 percent-good for each beam.
 * @param WP_Cell8_vel [m/s] Water-profile cell 8 velocity for four beams.
 * @param WP_Cell8_percent_good [%] Water-profile cell 8 percent-good for each beam.
 * @param WP_Cell9_vel [m/s] Water-profile cell 9 velocity for four beams.
 * @param WP_Cell9_percent_good [%] Water-profile cell 9 percent-good for each beam.
 * @param WP_Cell10_vel [m/s] Water-profile cell 10 velocity for four beams.
 * @param WP_Cell10_percent_good [%] Water-profile cell 10 percent-good for each beam.
 * @return length of the message in bytes (excluding serial stream start sign)
 */
static inline uint16_t mavlink_msg_dvl_data_pack_chan(uint8_t system_id, uint8_t component_id, uint8_t chan,
                               mavlink_message_t* msg,
                                   uint32_t timestamp_ms,const float *BT_range,const float *BT_vel,const uint8_t *BT_percent_good,float BT_max_depth,const float *WP_Cell1_vel,const uint8_t *WP_Cell1_percent_good,const float *WP_Cell2_vel,const uint8_t *WP_Cell2_percent_good,const float *WP_Cell3_vel,const uint8_t *WP_Cell3_percent_good,const float *WP_Cell4_vel,const uint8_t *WP_Cell4_percent_good,const float *WP_Cell5_vel,const uint8_t *WP_Cell5_percent_good,const float *WP_Cell6_vel,const uint8_t *WP_Cell6_percent_good,const float *WP_Cell7_vel,const uint8_t *WP_Cell7_percent_good,const float *WP_Cell8_vel,const uint8_t *WP_Cell8_percent_good,const float *WP_Cell9_vel,const uint8_t *WP_Cell9_percent_good,const float *WP_Cell10_vel,const uint8_t *WP_Cell10_percent_good)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    char buf[MAVLINK_MSG_ID_DVL_DATA_LEN];
    _mav_put_uint32_t(buf, 0, timestamp_ms);
    _mav_put_float(buf, 36, BT_max_depth);
    _mav_put_float_array(buf, 4, BT_range, 4);
    _mav_put_float_array(buf, 20, BT_vel, 4);
    _mav_put_float_array(buf, 40, WP_Cell1_vel, 4);
    _mav_put_float_array(buf, 56, WP_Cell2_vel, 4);
    _mav_put_float_array(buf, 72, WP_Cell3_vel, 4);
    _mav_put_float_array(buf, 88, WP_Cell4_vel, 4);
    _mav_put_float_array(buf, 104, WP_Cell5_vel, 4);
    _mav_put_float_array(buf, 120, WP_Cell6_vel, 4);
    _mav_put_float_array(buf, 136, WP_Cell7_vel, 4);
    _mav_put_float_array(buf, 152, WP_Cell8_vel, 4);
    _mav_put_float_array(buf, 168, WP_Cell9_vel, 4);
    _mav_put_float_array(buf, 184, WP_Cell10_vel, 4);
    _mav_put_uint8_t_array(buf, 200, BT_percent_good, 4);
    _mav_put_uint8_t_array(buf, 204, WP_Cell1_percent_good, 4);
    _mav_put_uint8_t_array(buf, 208, WP_Cell2_percent_good, 4);
    _mav_put_uint8_t_array(buf, 212, WP_Cell3_percent_good, 4);
    _mav_put_uint8_t_array(buf, 216, WP_Cell4_percent_good, 4);
    _mav_put_uint8_t_array(buf, 220, WP_Cell5_percent_good, 4);
    _mav_put_uint8_t_array(buf, 224, WP_Cell6_percent_good, 4);
    _mav_put_uint8_t_array(buf, 228, WP_Cell7_percent_good, 4);
    _mav_put_uint8_t_array(buf, 232, WP_Cell8_percent_good, 4);
    _mav_put_uint8_t_array(buf, 236, WP_Cell9_percent_good, 4);
    _mav_put_uint8_t_array(buf, 240, WP_Cell10_percent_good, 4);
        memcpy(_MAV_PAYLOAD_NON_CONST(msg), buf, MAVLINK_MSG_ID_DVL_DATA_LEN);
#else
    mavlink_dvl_data_t packet;
    packet.timestamp_ms = timestamp_ms;
    packet.BT_max_depth = BT_max_depth;
    mav_array_memcpy(packet.BT_range, BT_range, sizeof(float)*4);
    mav_array_memcpy(packet.BT_vel, BT_vel, sizeof(float)*4);
    mav_array_memcpy(packet.WP_Cell1_vel, WP_Cell1_vel, sizeof(float)*4);
    mav_array_memcpy(packet.WP_Cell2_vel, WP_Cell2_vel, sizeof(float)*4);
    mav_array_memcpy(packet.WP_Cell3_vel, WP_Cell3_vel, sizeof(float)*4);
    mav_array_memcpy(packet.WP_Cell4_vel, WP_Cell4_vel, sizeof(float)*4);
    mav_array_memcpy(packet.WP_Cell5_vel, WP_Cell5_vel, sizeof(float)*4);
    mav_array_memcpy(packet.WP_Cell6_vel, WP_Cell6_vel, sizeof(float)*4);
    mav_array_memcpy(packet.WP_Cell7_vel, WP_Cell7_vel, sizeof(float)*4);
    mav_array_memcpy(packet.WP_Cell8_vel, WP_Cell8_vel, sizeof(float)*4);
    mav_array_memcpy(packet.WP_Cell9_vel, WP_Cell9_vel, sizeof(float)*4);
    mav_array_memcpy(packet.WP_Cell10_vel, WP_Cell10_vel, sizeof(float)*4);
    mav_array_memcpy(packet.BT_percent_good, BT_percent_good, sizeof(uint8_t)*4);
    mav_array_memcpy(packet.WP_Cell1_percent_good, WP_Cell1_percent_good, sizeof(uint8_t)*4);
    mav_array_memcpy(packet.WP_Cell2_percent_good, WP_Cell2_percent_good, sizeof(uint8_t)*4);
    mav_array_memcpy(packet.WP_Cell3_percent_good, WP_Cell3_percent_good, sizeof(uint8_t)*4);
    mav_array_memcpy(packet.WP_Cell4_percent_good, WP_Cell4_percent_good, sizeof(uint8_t)*4);
    mav_array_memcpy(packet.WP_Cell5_percent_good, WP_Cell5_percent_good, sizeof(uint8_t)*4);
    mav_array_memcpy(packet.WP_Cell6_percent_good, WP_Cell6_percent_good, sizeof(uint8_t)*4);
    mav_array_memcpy(packet.WP_Cell7_percent_good, WP_Cell7_percent_good, sizeof(uint8_t)*4);
    mav_array_memcpy(packet.WP_Cell8_percent_good, WP_Cell8_percent_good, sizeof(uint8_t)*4);
    mav_array_memcpy(packet.WP_Cell9_percent_good, WP_Cell9_percent_good, sizeof(uint8_t)*4);
    mav_array_memcpy(packet.WP_Cell10_percent_good, WP_Cell10_percent_good, sizeof(uint8_t)*4);
        memcpy(_MAV_PAYLOAD_NON_CONST(msg), &packet, MAVLINK_MSG_ID_DVL_DATA_LEN);
#endif

    msg->msgid = MAVLINK_MSG_ID_DVL_DATA;
    return mavlink_finalize_message_chan(msg, system_id, component_id, chan, MAVLINK_MSG_ID_DVL_DATA_MIN_LEN, MAVLINK_MSG_ID_DVL_DATA_LEN, MAVLINK_MSG_ID_DVL_DATA_CRC);
}

/**
 * @brief Encode a dvl_data struct
 *
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param msg The MAVLink message to compress the data into
 * @param dvl_data C-struct to read the message contents from
 */
static inline uint16_t mavlink_msg_dvl_data_encode(uint8_t system_id, uint8_t component_id, mavlink_message_t* msg, const mavlink_dvl_data_t* dvl_data)
{
    return mavlink_msg_dvl_data_pack(system_id, component_id, msg, dvl_data->timestamp_ms, dvl_data->BT_range, dvl_data->BT_vel, dvl_data->BT_percent_good, dvl_data->BT_max_depth, dvl_data->WP_Cell1_vel, dvl_data->WP_Cell1_percent_good, dvl_data->WP_Cell2_vel, dvl_data->WP_Cell2_percent_good, dvl_data->WP_Cell3_vel, dvl_data->WP_Cell3_percent_good, dvl_data->WP_Cell4_vel, dvl_data->WP_Cell4_percent_good, dvl_data->WP_Cell5_vel, dvl_data->WP_Cell5_percent_good, dvl_data->WP_Cell6_vel, dvl_data->WP_Cell6_percent_good, dvl_data->WP_Cell7_vel, dvl_data->WP_Cell7_percent_good, dvl_data->WP_Cell8_vel, dvl_data->WP_Cell8_percent_good, dvl_data->WP_Cell9_vel, dvl_data->WP_Cell9_percent_good, dvl_data->WP_Cell10_vel, dvl_data->WP_Cell10_percent_good);
}

/**
 * @brief Encode a dvl_data struct on a channel
 *
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param chan The MAVLink channel this message will be sent over
 * @param msg The MAVLink message to compress the data into
 * @param dvl_data C-struct to read the message contents from
 */
static inline uint16_t mavlink_msg_dvl_data_encode_chan(uint8_t system_id, uint8_t component_id, uint8_t chan, mavlink_message_t* msg, const mavlink_dvl_data_t* dvl_data)
{
    return mavlink_msg_dvl_data_pack_chan(system_id, component_id, chan, msg, dvl_data->timestamp_ms, dvl_data->BT_range, dvl_data->BT_vel, dvl_data->BT_percent_good, dvl_data->BT_max_depth, dvl_data->WP_Cell1_vel, dvl_data->WP_Cell1_percent_good, dvl_data->WP_Cell2_vel, dvl_data->WP_Cell2_percent_good, dvl_data->WP_Cell3_vel, dvl_data->WP_Cell3_percent_good, dvl_data->WP_Cell4_vel, dvl_data->WP_Cell4_percent_good, dvl_data->WP_Cell5_vel, dvl_data->WP_Cell5_percent_good, dvl_data->WP_Cell6_vel, dvl_data->WP_Cell6_percent_good, dvl_data->WP_Cell7_vel, dvl_data->WP_Cell7_percent_good, dvl_data->WP_Cell8_vel, dvl_data->WP_Cell8_percent_good, dvl_data->WP_Cell9_vel, dvl_data->WP_Cell9_percent_good, dvl_data->WP_Cell10_vel, dvl_data->WP_Cell10_percent_good);
}

/**
 * @brief Encode a dvl_data struct with provided status structure
 *
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param status MAVLink status structure
 * @param msg The MAVLink message to compress the data into
 * @param dvl_data C-struct to read the message contents from
 */
static inline uint16_t mavlink_msg_dvl_data_encode_status(uint8_t system_id, uint8_t component_id, mavlink_status_t* _status, mavlink_message_t* msg, const mavlink_dvl_data_t* dvl_data)
{
    return mavlink_msg_dvl_data_pack_status(system_id, component_id, _status, msg,  dvl_data->timestamp_ms, dvl_data->BT_range, dvl_data->BT_vel, dvl_data->BT_percent_good, dvl_data->BT_max_depth, dvl_data->WP_Cell1_vel, dvl_data->WP_Cell1_percent_good, dvl_data->WP_Cell2_vel, dvl_data->WP_Cell2_percent_good, dvl_data->WP_Cell3_vel, dvl_data->WP_Cell3_percent_good, dvl_data->WP_Cell4_vel, dvl_data->WP_Cell4_percent_good, dvl_data->WP_Cell5_vel, dvl_data->WP_Cell5_percent_good, dvl_data->WP_Cell6_vel, dvl_data->WP_Cell6_percent_good, dvl_data->WP_Cell7_vel, dvl_data->WP_Cell7_percent_good, dvl_data->WP_Cell8_vel, dvl_data->WP_Cell8_percent_good, dvl_data->WP_Cell9_vel, dvl_data->WP_Cell9_percent_good, dvl_data->WP_Cell10_vel, dvl_data->WP_Cell10_percent_good);
}

/**
 * @brief Send a dvl_data message
 * @param chan MAVLink channel to send the message
 *
 * @param timestamp_ms [ms] Timestamp from the sender clock.
 * @param BT_range [m] Bottom-track range for four beams; 0 means bad bottom range detection.
 * @param BT_vel [m/s] Bottom-track velocity for four beams. Beam meaning depends on DVL coordinate frame; common mapping is v1 east/Y, v2 north/X, v3 up/Z.
 * @param BT_percent_good [%] Bottom-track percent-good for each beam.
 * @param BT_max_depth [m] Maximum bottom-track depth, expected range 1-6553.5 m.
 * @param WP_Cell1_vel [m/s] Water-profile cell 1 velocity for four beams.
 * @param WP_Cell1_percent_good [%] Water-profile cell 1 percent-good for each beam.
 * @param WP_Cell2_vel [m/s] Water-profile cell 2 velocity for four beams.
 * @param WP_Cell2_percent_good [%] Water-profile cell 2 percent-good for each beam.
 * @param WP_Cell3_vel [m/s] Water-profile cell 3 velocity for four beams.
 * @param WP_Cell3_percent_good [%] Water-profile cell 3 percent-good for each beam.
 * @param WP_Cell4_vel [m/s] Water-profile cell 4 velocity for four beams.
 * @param WP_Cell4_percent_good [%] Water-profile cell 4 percent-good for each beam.
 * @param WP_Cell5_vel [m/s] Water-profile cell 5 velocity for four beams.
 * @param WP_Cell5_percent_good [%] Water-profile cell 5 percent-good for each beam.
 * @param WP_Cell6_vel [m/s] Water-profile cell 6 velocity for four beams.
 * @param WP_Cell6_percent_good [%] Water-profile cell 6 percent-good for each beam.
 * @param WP_Cell7_vel [m/s] Water-profile cell 7 velocity for four beams.
 * @param WP_Cell7_percent_good [%] Water-profile cell 7 percent-good for each beam.
 * @param WP_Cell8_vel [m/s] Water-profile cell 8 velocity for four beams.
 * @param WP_Cell8_percent_good [%] Water-profile cell 8 percent-good for each beam.
 * @param WP_Cell9_vel [m/s] Water-profile cell 9 velocity for four beams.
 * @param WP_Cell9_percent_good [%] Water-profile cell 9 percent-good for each beam.
 * @param WP_Cell10_vel [m/s] Water-profile cell 10 velocity for four beams.
 * @param WP_Cell10_percent_good [%] Water-profile cell 10 percent-good for each beam.
 */
#ifdef MAVLINK_USE_CONVENIENCE_FUNCTIONS

static inline void mavlink_msg_dvl_data_send(mavlink_channel_t chan, uint32_t timestamp_ms, const float *BT_range, const float *BT_vel, const uint8_t *BT_percent_good, float BT_max_depth, const float *WP_Cell1_vel, const uint8_t *WP_Cell1_percent_good, const float *WP_Cell2_vel, const uint8_t *WP_Cell2_percent_good, const float *WP_Cell3_vel, const uint8_t *WP_Cell3_percent_good, const float *WP_Cell4_vel, const uint8_t *WP_Cell4_percent_good, const float *WP_Cell5_vel, const uint8_t *WP_Cell5_percent_good, const float *WP_Cell6_vel, const uint8_t *WP_Cell6_percent_good, const float *WP_Cell7_vel, const uint8_t *WP_Cell7_percent_good, const float *WP_Cell8_vel, const uint8_t *WP_Cell8_percent_good, const float *WP_Cell9_vel, const uint8_t *WP_Cell9_percent_good, const float *WP_Cell10_vel, const uint8_t *WP_Cell10_percent_good)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    char buf[MAVLINK_MSG_ID_DVL_DATA_LEN];
    _mav_put_uint32_t(buf, 0, timestamp_ms);
    _mav_put_float(buf, 36, BT_max_depth);
    _mav_put_float_array(buf, 4, BT_range, 4);
    _mav_put_float_array(buf, 20, BT_vel, 4);
    _mav_put_float_array(buf, 40, WP_Cell1_vel, 4);
    _mav_put_float_array(buf, 56, WP_Cell2_vel, 4);
    _mav_put_float_array(buf, 72, WP_Cell3_vel, 4);
    _mav_put_float_array(buf, 88, WP_Cell4_vel, 4);
    _mav_put_float_array(buf, 104, WP_Cell5_vel, 4);
    _mav_put_float_array(buf, 120, WP_Cell6_vel, 4);
    _mav_put_float_array(buf, 136, WP_Cell7_vel, 4);
    _mav_put_float_array(buf, 152, WP_Cell8_vel, 4);
    _mav_put_float_array(buf, 168, WP_Cell9_vel, 4);
    _mav_put_float_array(buf, 184, WP_Cell10_vel, 4);
    _mav_put_uint8_t_array(buf, 200, BT_percent_good, 4);
    _mav_put_uint8_t_array(buf, 204, WP_Cell1_percent_good, 4);
    _mav_put_uint8_t_array(buf, 208, WP_Cell2_percent_good, 4);
    _mav_put_uint8_t_array(buf, 212, WP_Cell3_percent_good, 4);
    _mav_put_uint8_t_array(buf, 216, WP_Cell4_percent_good, 4);
    _mav_put_uint8_t_array(buf, 220, WP_Cell5_percent_good, 4);
    _mav_put_uint8_t_array(buf, 224, WP_Cell6_percent_good, 4);
    _mav_put_uint8_t_array(buf, 228, WP_Cell7_percent_good, 4);
    _mav_put_uint8_t_array(buf, 232, WP_Cell8_percent_good, 4);
    _mav_put_uint8_t_array(buf, 236, WP_Cell9_percent_good, 4);
    _mav_put_uint8_t_array(buf, 240, WP_Cell10_percent_good, 4);
    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_DVL_DATA, buf, MAVLINK_MSG_ID_DVL_DATA_MIN_LEN, MAVLINK_MSG_ID_DVL_DATA_LEN, MAVLINK_MSG_ID_DVL_DATA_CRC);
#else
    mavlink_dvl_data_t packet;
    packet.timestamp_ms = timestamp_ms;
    packet.BT_max_depth = BT_max_depth;
    mav_array_memcpy(packet.BT_range, BT_range, sizeof(float)*4);
    mav_array_memcpy(packet.BT_vel, BT_vel, sizeof(float)*4);
    mav_array_memcpy(packet.WP_Cell1_vel, WP_Cell1_vel, sizeof(float)*4);
    mav_array_memcpy(packet.WP_Cell2_vel, WP_Cell2_vel, sizeof(float)*4);
    mav_array_memcpy(packet.WP_Cell3_vel, WP_Cell3_vel, sizeof(float)*4);
    mav_array_memcpy(packet.WP_Cell4_vel, WP_Cell4_vel, sizeof(float)*4);
    mav_array_memcpy(packet.WP_Cell5_vel, WP_Cell5_vel, sizeof(float)*4);
    mav_array_memcpy(packet.WP_Cell6_vel, WP_Cell6_vel, sizeof(float)*4);
    mav_array_memcpy(packet.WP_Cell7_vel, WP_Cell7_vel, sizeof(float)*4);
    mav_array_memcpy(packet.WP_Cell8_vel, WP_Cell8_vel, sizeof(float)*4);
    mav_array_memcpy(packet.WP_Cell9_vel, WP_Cell9_vel, sizeof(float)*4);
    mav_array_memcpy(packet.WP_Cell10_vel, WP_Cell10_vel, sizeof(float)*4);
    mav_array_memcpy(packet.BT_percent_good, BT_percent_good, sizeof(uint8_t)*4);
    mav_array_memcpy(packet.WP_Cell1_percent_good, WP_Cell1_percent_good, sizeof(uint8_t)*4);
    mav_array_memcpy(packet.WP_Cell2_percent_good, WP_Cell2_percent_good, sizeof(uint8_t)*4);
    mav_array_memcpy(packet.WP_Cell3_percent_good, WP_Cell3_percent_good, sizeof(uint8_t)*4);
    mav_array_memcpy(packet.WP_Cell4_percent_good, WP_Cell4_percent_good, sizeof(uint8_t)*4);
    mav_array_memcpy(packet.WP_Cell5_percent_good, WP_Cell5_percent_good, sizeof(uint8_t)*4);
    mav_array_memcpy(packet.WP_Cell6_percent_good, WP_Cell6_percent_good, sizeof(uint8_t)*4);
    mav_array_memcpy(packet.WP_Cell7_percent_good, WP_Cell7_percent_good, sizeof(uint8_t)*4);
    mav_array_memcpy(packet.WP_Cell8_percent_good, WP_Cell8_percent_good, sizeof(uint8_t)*4);
    mav_array_memcpy(packet.WP_Cell9_percent_good, WP_Cell9_percent_good, sizeof(uint8_t)*4);
    mav_array_memcpy(packet.WP_Cell10_percent_good, WP_Cell10_percent_good, sizeof(uint8_t)*4);
    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_DVL_DATA, (const char *)&packet, MAVLINK_MSG_ID_DVL_DATA_MIN_LEN, MAVLINK_MSG_ID_DVL_DATA_LEN, MAVLINK_MSG_ID_DVL_DATA_CRC);
#endif
}

/**
 * @brief Send a dvl_data message
 * @param chan MAVLink channel to send the message
 * @param struct The MAVLink struct to serialize
 */
static inline void mavlink_msg_dvl_data_send_struct(mavlink_channel_t chan, const mavlink_dvl_data_t* dvl_data)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    mavlink_msg_dvl_data_send(chan, dvl_data->timestamp_ms, dvl_data->BT_range, dvl_data->BT_vel, dvl_data->BT_percent_good, dvl_data->BT_max_depth, dvl_data->WP_Cell1_vel, dvl_data->WP_Cell1_percent_good, dvl_data->WP_Cell2_vel, dvl_data->WP_Cell2_percent_good, dvl_data->WP_Cell3_vel, dvl_data->WP_Cell3_percent_good, dvl_data->WP_Cell4_vel, dvl_data->WP_Cell4_percent_good, dvl_data->WP_Cell5_vel, dvl_data->WP_Cell5_percent_good, dvl_data->WP_Cell6_vel, dvl_data->WP_Cell6_percent_good, dvl_data->WP_Cell7_vel, dvl_data->WP_Cell7_percent_good, dvl_data->WP_Cell8_vel, dvl_data->WP_Cell8_percent_good, dvl_data->WP_Cell9_vel, dvl_data->WP_Cell9_percent_good, dvl_data->WP_Cell10_vel, dvl_data->WP_Cell10_percent_good);
#else
    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_DVL_DATA, (const char *)dvl_data, MAVLINK_MSG_ID_DVL_DATA_MIN_LEN, MAVLINK_MSG_ID_DVL_DATA_LEN, MAVLINK_MSG_ID_DVL_DATA_CRC);
#endif
}

#if MAVLINK_MSG_ID_DVL_DATA_LEN <= MAVLINK_MAX_PAYLOAD_LEN
/*
  This variant of _send() can be used to save stack space by reusing
  memory from the receive buffer.  The caller provides a
  mavlink_message_t which is the size of a full mavlink message. This
  is usually the receive buffer for the channel, and allows a reply to an
  incoming message with minimum stack space usage.
 */
static inline void mavlink_msg_dvl_data_send_buf(mavlink_message_t *msgbuf, mavlink_channel_t chan,  uint32_t timestamp_ms, const float *BT_range, const float *BT_vel, const uint8_t *BT_percent_good, float BT_max_depth, const float *WP_Cell1_vel, const uint8_t *WP_Cell1_percent_good, const float *WP_Cell2_vel, const uint8_t *WP_Cell2_percent_good, const float *WP_Cell3_vel, const uint8_t *WP_Cell3_percent_good, const float *WP_Cell4_vel, const uint8_t *WP_Cell4_percent_good, const float *WP_Cell5_vel, const uint8_t *WP_Cell5_percent_good, const float *WP_Cell6_vel, const uint8_t *WP_Cell6_percent_good, const float *WP_Cell7_vel, const uint8_t *WP_Cell7_percent_good, const float *WP_Cell8_vel, const uint8_t *WP_Cell8_percent_good, const float *WP_Cell9_vel, const uint8_t *WP_Cell9_percent_good, const float *WP_Cell10_vel, const uint8_t *WP_Cell10_percent_good)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    char *buf = (char *)msgbuf;
    _mav_put_uint32_t(buf, 0, timestamp_ms);
    _mav_put_float(buf, 36, BT_max_depth);
    _mav_put_float_array(buf, 4, BT_range, 4);
    _mav_put_float_array(buf, 20, BT_vel, 4);
    _mav_put_float_array(buf, 40, WP_Cell1_vel, 4);
    _mav_put_float_array(buf, 56, WP_Cell2_vel, 4);
    _mav_put_float_array(buf, 72, WP_Cell3_vel, 4);
    _mav_put_float_array(buf, 88, WP_Cell4_vel, 4);
    _mav_put_float_array(buf, 104, WP_Cell5_vel, 4);
    _mav_put_float_array(buf, 120, WP_Cell6_vel, 4);
    _mav_put_float_array(buf, 136, WP_Cell7_vel, 4);
    _mav_put_float_array(buf, 152, WP_Cell8_vel, 4);
    _mav_put_float_array(buf, 168, WP_Cell9_vel, 4);
    _mav_put_float_array(buf, 184, WP_Cell10_vel, 4);
    _mav_put_uint8_t_array(buf, 200, BT_percent_good, 4);
    _mav_put_uint8_t_array(buf, 204, WP_Cell1_percent_good, 4);
    _mav_put_uint8_t_array(buf, 208, WP_Cell2_percent_good, 4);
    _mav_put_uint8_t_array(buf, 212, WP_Cell3_percent_good, 4);
    _mav_put_uint8_t_array(buf, 216, WP_Cell4_percent_good, 4);
    _mav_put_uint8_t_array(buf, 220, WP_Cell5_percent_good, 4);
    _mav_put_uint8_t_array(buf, 224, WP_Cell6_percent_good, 4);
    _mav_put_uint8_t_array(buf, 228, WP_Cell7_percent_good, 4);
    _mav_put_uint8_t_array(buf, 232, WP_Cell8_percent_good, 4);
    _mav_put_uint8_t_array(buf, 236, WP_Cell9_percent_good, 4);
    _mav_put_uint8_t_array(buf, 240, WP_Cell10_percent_good, 4);
    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_DVL_DATA, buf, MAVLINK_MSG_ID_DVL_DATA_MIN_LEN, MAVLINK_MSG_ID_DVL_DATA_LEN, MAVLINK_MSG_ID_DVL_DATA_CRC);
#else
    mavlink_dvl_data_t *packet = (mavlink_dvl_data_t *)msgbuf;
    packet->timestamp_ms = timestamp_ms;
    packet->BT_max_depth = BT_max_depth;
    mav_array_memcpy(packet->BT_range, BT_range, sizeof(float)*4);
    mav_array_memcpy(packet->BT_vel, BT_vel, sizeof(float)*4);
    mav_array_memcpy(packet->WP_Cell1_vel, WP_Cell1_vel, sizeof(float)*4);
    mav_array_memcpy(packet->WP_Cell2_vel, WP_Cell2_vel, sizeof(float)*4);
    mav_array_memcpy(packet->WP_Cell3_vel, WP_Cell3_vel, sizeof(float)*4);
    mav_array_memcpy(packet->WP_Cell4_vel, WP_Cell4_vel, sizeof(float)*4);
    mav_array_memcpy(packet->WP_Cell5_vel, WP_Cell5_vel, sizeof(float)*4);
    mav_array_memcpy(packet->WP_Cell6_vel, WP_Cell6_vel, sizeof(float)*4);
    mav_array_memcpy(packet->WP_Cell7_vel, WP_Cell7_vel, sizeof(float)*4);
    mav_array_memcpy(packet->WP_Cell8_vel, WP_Cell8_vel, sizeof(float)*4);
    mav_array_memcpy(packet->WP_Cell9_vel, WP_Cell9_vel, sizeof(float)*4);
    mav_array_memcpy(packet->WP_Cell10_vel, WP_Cell10_vel, sizeof(float)*4);
    mav_array_memcpy(packet->BT_percent_good, BT_percent_good, sizeof(uint8_t)*4);
    mav_array_memcpy(packet->WP_Cell1_percent_good, WP_Cell1_percent_good, sizeof(uint8_t)*4);
    mav_array_memcpy(packet->WP_Cell2_percent_good, WP_Cell2_percent_good, sizeof(uint8_t)*4);
    mav_array_memcpy(packet->WP_Cell3_percent_good, WP_Cell3_percent_good, sizeof(uint8_t)*4);
    mav_array_memcpy(packet->WP_Cell4_percent_good, WP_Cell4_percent_good, sizeof(uint8_t)*4);
    mav_array_memcpy(packet->WP_Cell5_percent_good, WP_Cell5_percent_good, sizeof(uint8_t)*4);
    mav_array_memcpy(packet->WP_Cell6_percent_good, WP_Cell6_percent_good, sizeof(uint8_t)*4);
    mav_array_memcpy(packet->WP_Cell7_percent_good, WP_Cell7_percent_good, sizeof(uint8_t)*4);
    mav_array_memcpy(packet->WP_Cell8_percent_good, WP_Cell8_percent_good, sizeof(uint8_t)*4);
    mav_array_memcpy(packet->WP_Cell9_percent_good, WP_Cell9_percent_good, sizeof(uint8_t)*4);
    mav_array_memcpy(packet->WP_Cell10_percent_good, WP_Cell10_percent_good, sizeof(uint8_t)*4);
    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_DVL_DATA, (const char *)packet, MAVLINK_MSG_ID_DVL_DATA_MIN_LEN, MAVLINK_MSG_ID_DVL_DATA_LEN, MAVLINK_MSG_ID_DVL_DATA_CRC);
#endif
}
#endif

#endif

// MESSAGE DVL_DATA UNPACKING


/**
 * @brief Get field timestamp_ms from dvl_data message
 *
 * @return [ms] Timestamp from the sender clock.
 */
static inline uint32_t mavlink_msg_dvl_data_get_timestamp_ms(const mavlink_message_t* msg)
{
    return _MAV_RETURN_uint32_t(msg,  0);
}

/**
 * @brief Get field BT_range from dvl_data message
 *
 * @return [m] Bottom-track range for four beams; 0 means bad bottom range detection.
 */
static inline uint16_t mavlink_msg_dvl_data_get_BT_range(const mavlink_message_t* msg, float *BT_range)
{
    return _MAV_RETURN_float_array(msg, BT_range, 4,  4);
}

/**
 * @brief Get field BT_vel from dvl_data message
 *
 * @return [m/s] Bottom-track velocity for four beams. Beam meaning depends on DVL coordinate frame; common mapping is v1 east/Y, v2 north/X, v3 up/Z.
 */
static inline uint16_t mavlink_msg_dvl_data_get_BT_vel(const mavlink_message_t* msg, float *BT_vel)
{
    return _MAV_RETURN_float_array(msg, BT_vel, 4,  20);
}

/**
 * @brief Get field BT_percent_good from dvl_data message
 *
 * @return [%] Bottom-track percent-good for each beam.
 */
static inline uint16_t mavlink_msg_dvl_data_get_BT_percent_good(const mavlink_message_t* msg, uint8_t *BT_percent_good)
{
    return _MAV_RETURN_uint8_t_array(msg, BT_percent_good, 4,  200);
}

/**
 * @brief Get field BT_max_depth from dvl_data message
 *
 * @return [m] Maximum bottom-track depth, expected range 1-6553.5 m.
 */
static inline float mavlink_msg_dvl_data_get_BT_max_depth(const mavlink_message_t* msg)
{
    return _MAV_RETURN_float(msg,  36);
}

/**
 * @brief Get field WP_Cell1_vel from dvl_data message
 *
 * @return [m/s] Water-profile cell 1 velocity for four beams.
 */
static inline uint16_t mavlink_msg_dvl_data_get_WP_Cell1_vel(const mavlink_message_t* msg, float *WP_Cell1_vel)
{
    return _MAV_RETURN_float_array(msg, WP_Cell1_vel, 4,  40);
}

/**
 * @brief Get field WP_Cell1_percent_good from dvl_data message
 *
 * @return [%] Water-profile cell 1 percent-good for each beam.
 */
static inline uint16_t mavlink_msg_dvl_data_get_WP_Cell1_percent_good(const mavlink_message_t* msg, uint8_t *WP_Cell1_percent_good)
{
    return _MAV_RETURN_uint8_t_array(msg, WP_Cell1_percent_good, 4,  204);
}

/**
 * @brief Get field WP_Cell2_vel from dvl_data message
 *
 * @return [m/s] Water-profile cell 2 velocity for four beams.
 */
static inline uint16_t mavlink_msg_dvl_data_get_WP_Cell2_vel(const mavlink_message_t* msg, float *WP_Cell2_vel)
{
    return _MAV_RETURN_float_array(msg, WP_Cell2_vel, 4,  56);
}

/**
 * @brief Get field WP_Cell2_percent_good from dvl_data message
 *
 * @return [%] Water-profile cell 2 percent-good for each beam.
 */
static inline uint16_t mavlink_msg_dvl_data_get_WP_Cell2_percent_good(const mavlink_message_t* msg, uint8_t *WP_Cell2_percent_good)
{
    return _MAV_RETURN_uint8_t_array(msg, WP_Cell2_percent_good, 4,  208);
}

/**
 * @brief Get field WP_Cell3_vel from dvl_data message
 *
 * @return [m/s] Water-profile cell 3 velocity for four beams.
 */
static inline uint16_t mavlink_msg_dvl_data_get_WP_Cell3_vel(const mavlink_message_t* msg, float *WP_Cell3_vel)
{
    return _MAV_RETURN_float_array(msg, WP_Cell3_vel, 4,  72);
}

/**
 * @brief Get field WP_Cell3_percent_good from dvl_data message
 *
 * @return [%] Water-profile cell 3 percent-good for each beam.
 */
static inline uint16_t mavlink_msg_dvl_data_get_WP_Cell3_percent_good(const mavlink_message_t* msg, uint8_t *WP_Cell3_percent_good)
{
    return _MAV_RETURN_uint8_t_array(msg, WP_Cell3_percent_good, 4,  212);
}

/**
 * @brief Get field WP_Cell4_vel from dvl_data message
 *
 * @return [m/s] Water-profile cell 4 velocity for four beams.
 */
static inline uint16_t mavlink_msg_dvl_data_get_WP_Cell4_vel(const mavlink_message_t* msg, float *WP_Cell4_vel)
{
    return _MAV_RETURN_float_array(msg, WP_Cell4_vel, 4,  88);
}

/**
 * @brief Get field WP_Cell4_percent_good from dvl_data message
 *
 * @return [%] Water-profile cell 4 percent-good for each beam.
 */
static inline uint16_t mavlink_msg_dvl_data_get_WP_Cell4_percent_good(const mavlink_message_t* msg, uint8_t *WP_Cell4_percent_good)
{
    return _MAV_RETURN_uint8_t_array(msg, WP_Cell4_percent_good, 4,  216);
}

/**
 * @brief Get field WP_Cell5_vel from dvl_data message
 *
 * @return [m/s] Water-profile cell 5 velocity for four beams.
 */
static inline uint16_t mavlink_msg_dvl_data_get_WP_Cell5_vel(const mavlink_message_t* msg, float *WP_Cell5_vel)
{
    return _MAV_RETURN_float_array(msg, WP_Cell5_vel, 4,  104);
}

/**
 * @brief Get field WP_Cell5_percent_good from dvl_data message
 *
 * @return [%] Water-profile cell 5 percent-good for each beam.
 */
static inline uint16_t mavlink_msg_dvl_data_get_WP_Cell5_percent_good(const mavlink_message_t* msg, uint8_t *WP_Cell5_percent_good)
{
    return _MAV_RETURN_uint8_t_array(msg, WP_Cell5_percent_good, 4,  220);
}

/**
 * @brief Get field WP_Cell6_vel from dvl_data message
 *
 * @return [m/s] Water-profile cell 6 velocity for four beams.
 */
static inline uint16_t mavlink_msg_dvl_data_get_WP_Cell6_vel(const mavlink_message_t* msg, float *WP_Cell6_vel)
{
    return _MAV_RETURN_float_array(msg, WP_Cell6_vel, 4,  120);
}

/**
 * @brief Get field WP_Cell6_percent_good from dvl_data message
 *
 * @return [%] Water-profile cell 6 percent-good for each beam.
 */
static inline uint16_t mavlink_msg_dvl_data_get_WP_Cell6_percent_good(const mavlink_message_t* msg, uint8_t *WP_Cell6_percent_good)
{
    return _MAV_RETURN_uint8_t_array(msg, WP_Cell6_percent_good, 4,  224);
}

/**
 * @brief Get field WP_Cell7_vel from dvl_data message
 *
 * @return [m/s] Water-profile cell 7 velocity for four beams.
 */
static inline uint16_t mavlink_msg_dvl_data_get_WP_Cell7_vel(const mavlink_message_t* msg, float *WP_Cell7_vel)
{
    return _MAV_RETURN_float_array(msg, WP_Cell7_vel, 4,  136);
}

/**
 * @brief Get field WP_Cell7_percent_good from dvl_data message
 *
 * @return [%] Water-profile cell 7 percent-good for each beam.
 */
static inline uint16_t mavlink_msg_dvl_data_get_WP_Cell7_percent_good(const mavlink_message_t* msg, uint8_t *WP_Cell7_percent_good)
{
    return _MAV_RETURN_uint8_t_array(msg, WP_Cell7_percent_good, 4,  228);
}

/**
 * @brief Get field WP_Cell8_vel from dvl_data message
 *
 * @return [m/s] Water-profile cell 8 velocity for four beams.
 */
static inline uint16_t mavlink_msg_dvl_data_get_WP_Cell8_vel(const mavlink_message_t* msg, float *WP_Cell8_vel)
{
    return _MAV_RETURN_float_array(msg, WP_Cell8_vel, 4,  152);
}

/**
 * @brief Get field WP_Cell8_percent_good from dvl_data message
 *
 * @return [%] Water-profile cell 8 percent-good for each beam.
 */
static inline uint16_t mavlink_msg_dvl_data_get_WP_Cell8_percent_good(const mavlink_message_t* msg, uint8_t *WP_Cell8_percent_good)
{
    return _MAV_RETURN_uint8_t_array(msg, WP_Cell8_percent_good, 4,  232);
}

/**
 * @brief Get field WP_Cell9_vel from dvl_data message
 *
 * @return [m/s] Water-profile cell 9 velocity for four beams.
 */
static inline uint16_t mavlink_msg_dvl_data_get_WP_Cell9_vel(const mavlink_message_t* msg, float *WP_Cell9_vel)
{
    return _MAV_RETURN_float_array(msg, WP_Cell9_vel, 4,  168);
}

/**
 * @brief Get field WP_Cell9_percent_good from dvl_data message
 *
 * @return [%] Water-profile cell 9 percent-good for each beam.
 */
static inline uint16_t mavlink_msg_dvl_data_get_WP_Cell9_percent_good(const mavlink_message_t* msg, uint8_t *WP_Cell9_percent_good)
{
    return _MAV_RETURN_uint8_t_array(msg, WP_Cell9_percent_good, 4,  236);
}

/**
 * @brief Get field WP_Cell10_vel from dvl_data message
 *
 * @return [m/s] Water-profile cell 10 velocity for four beams.
 */
static inline uint16_t mavlink_msg_dvl_data_get_WP_Cell10_vel(const mavlink_message_t* msg, float *WP_Cell10_vel)
{
    return _MAV_RETURN_float_array(msg, WP_Cell10_vel, 4,  184);
}

/**
 * @brief Get field WP_Cell10_percent_good from dvl_data message
 *
 * @return [%] Water-profile cell 10 percent-good for each beam.
 */
static inline uint16_t mavlink_msg_dvl_data_get_WP_Cell10_percent_good(const mavlink_message_t* msg, uint8_t *WP_Cell10_percent_good)
{
    return _MAV_RETURN_uint8_t_array(msg, WP_Cell10_percent_good, 4,  240);
}

/**
 * @brief Decode a dvl_data message into a struct
 *
 * @param msg The message to decode
 * @param dvl_data C-struct to decode the message contents into
 */
static inline void mavlink_msg_dvl_data_decode(const mavlink_message_t* msg, mavlink_dvl_data_t* dvl_data)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    dvl_data->timestamp_ms = mavlink_msg_dvl_data_get_timestamp_ms(msg);
    mavlink_msg_dvl_data_get_BT_range(msg, dvl_data->BT_range);
    mavlink_msg_dvl_data_get_BT_vel(msg, dvl_data->BT_vel);
    dvl_data->BT_max_depth = mavlink_msg_dvl_data_get_BT_max_depth(msg);
    mavlink_msg_dvl_data_get_WP_Cell1_vel(msg, dvl_data->WP_Cell1_vel);
    mavlink_msg_dvl_data_get_WP_Cell2_vel(msg, dvl_data->WP_Cell2_vel);
    mavlink_msg_dvl_data_get_WP_Cell3_vel(msg, dvl_data->WP_Cell3_vel);
    mavlink_msg_dvl_data_get_WP_Cell4_vel(msg, dvl_data->WP_Cell4_vel);
    mavlink_msg_dvl_data_get_WP_Cell5_vel(msg, dvl_data->WP_Cell5_vel);
    mavlink_msg_dvl_data_get_WP_Cell6_vel(msg, dvl_data->WP_Cell6_vel);
    mavlink_msg_dvl_data_get_WP_Cell7_vel(msg, dvl_data->WP_Cell7_vel);
    mavlink_msg_dvl_data_get_WP_Cell8_vel(msg, dvl_data->WP_Cell8_vel);
    mavlink_msg_dvl_data_get_WP_Cell9_vel(msg, dvl_data->WP_Cell9_vel);
    mavlink_msg_dvl_data_get_WP_Cell10_vel(msg, dvl_data->WP_Cell10_vel);
    mavlink_msg_dvl_data_get_BT_percent_good(msg, dvl_data->BT_percent_good);
    mavlink_msg_dvl_data_get_WP_Cell1_percent_good(msg, dvl_data->WP_Cell1_percent_good);
    mavlink_msg_dvl_data_get_WP_Cell2_percent_good(msg, dvl_data->WP_Cell2_percent_good);
    mavlink_msg_dvl_data_get_WP_Cell3_percent_good(msg, dvl_data->WP_Cell3_percent_good);
    mavlink_msg_dvl_data_get_WP_Cell4_percent_good(msg, dvl_data->WP_Cell4_percent_good);
    mavlink_msg_dvl_data_get_WP_Cell5_percent_good(msg, dvl_data->WP_Cell5_percent_good);
    mavlink_msg_dvl_data_get_WP_Cell6_percent_good(msg, dvl_data->WP_Cell6_percent_good);
    mavlink_msg_dvl_data_get_WP_Cell7_percent_good(msg, dvl_data->WP_Cell7_percent_good);
    mavlink_msg_dvl_data_get_WP_Cell8_percent_good(msg, dvl_data->WP_Cell8_percent_good);
    mavlink_msg_dvl_data_get_WP_Cell9_percent_good(msg, dvl_data->WP_Cell9_percent_good);
    mavlink_msg_dvl_data_get_WP_Cell10_percent_good(msg, dvl_data->WP_Cell10_percent_good);
#else
        uint8_t len = msg->len < MAVLINK_MSG_ID_DVL_DATA_LEN? msg->len : MAVLINK_MSG_ID_DVL_DATA_LEN;
        memset(dvl_data, 0, MAVLINK_MSG_ID_DVL_DATA_LEN);
    memcpy(dvl_data, _MAV_PAYLOAD(msg), len);
#endif
}
