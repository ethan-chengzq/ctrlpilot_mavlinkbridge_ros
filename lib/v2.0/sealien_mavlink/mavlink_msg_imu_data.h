#pragma once
// MESSAGE IMU_DATA PACKING

#define MAVLINK_MSG_ID_IMU_DATA 1


typedef struct __mavlink_imu_data_t {
 double lon; /*< [deg] Longitude.*/
 double lat; /*< [deg] Latitude.*/
 uint32_t timestamp_ms; /*< [ms] Timestamp from the sender clock.*/
 float alt; /*< [m] Altitude.*/
 float vel_n; /*< [m/s] North velocity.*/
 float vel_e; /*< [m/s] East velocity.*/
 float vel_u; /*< [m/s] Up or ground-referenced velocity, matching the STM32 protocol table.*/
 float acc_x; /*< [m/s/s] X-axis acceleration.*/
 float acc_y; /*< [m/s/s] Y-axis acceleration.*/
 float acc_z; /*< [m/s/s] Z-axis acceleration.*/
 float roll; /*< [deg] Roll angle.*/
 float pitch; /*< [deg] Pitch angle.*/
 float yaw; /*< [deg] Heading angle.*/
 float gyro_x; /*< [deg/s] Roll angular velocity.*/
 float gyro_y; /*< [deg/s] Pitch angular velocity.*/
 float gyro_z; /*< [deg/s] Heading angular velocity.*/
 float temp; /*< [degC] IMU temperature.*/
 float dvl_velx; /*< [m/s] DVL X-axis velocity.*/
 float dvl_vely; /*< [m/s] DVL Y-axis velocity.*/
 float dvl_velz; /*< [m/s] DVL Z-axis velocity.*/
 float dvl_height; /*< [m] DVL altitude above bottom.*/
 int16_t turns; /*<  IMU heading turn count; positive and negative values are valid.*/
 uint8_t imu_status; /*<  IMU status code.*/
 uint8_t fault; /*<  IMU fault code.*/
 uint8_t is_calibrating; /*<  IMU calibration flag: 0 not calibrating, 1 calibrating.*/
 uint8_t dvl_status; /*<  DVL status code.*/
} mavlink_imu_data_t;

#define MAVLINK_MSG_ID_IMU_DATA_LEN 98
#define MAVLINK_MSG_ID_IMU_DATA_MIN_LEN 98
#define MAVLINK_MSG_ID_1_LEN 98
#define MAVLINK_MSG_ID_1_MIN_LEN 98

#define MAVLINK_MSG_ID_IMU_DATA_CRC 64
#define MAVLINK_MSG_ID_1_CRC 64



#if MAVLINK_COMMAND_24BIT
#define MAVLINK_MESSAGE_INFO_IMU_DATA { \
    1, \
    "IMU_DATA", \
    26, \
    {  { "timestamp_ms", NULL, MAVLINK_TYPE_UINT32_T, 0, 16, offsetof(mavlink_imu_data_t, timestamp_ms) }, \
         { "lon", NULL, MAVLINK_TYPE_DOUBLE, 0, 0, offsetof(mavlink_imu_data_t, lon) }, \
         { "lat", NULL, MAVLINK_TYPE_DOUBLE, 0, 8, offsetof(mavlink_imu_data_t, lat) }, \
         { "alt", NULL, MAVLINK_TYPE_FLOAT, 0, 20, offsetof(mavlink_imu_data_t, alt) }, \
         { "vel_n", NULL, MAVLINK_TYPE_FLOAT, 0, 24, offsetof(mavlink_imu_data_t, vel_n) }, \
         { "vel_e", NULL, MAVLINK_TYPE_FLOAT, 0, 28, offsetof(mavlink_imu_data_t, vel_e) }, \
         { "vel_u", NULL, MAVLINK_TYPE_FLOAT, 0, 32, offsetof(mavlink_imu_data_t, vel_u) }, \
         { "acc_x", NULL, MAVLINK_TYPE_FLOAT, 0, 36, offsetof(mavlink_imu_data_t, acc_x) }, \
         { "acc_y", NULL, MAVLINK_TYPE_FLOAT, 0, 40, offsetof(mavlink_imu_data_t, acc_y) }, \
         { "acc_z", NULL, MAVLINK_TYPE_FLOAT, 0, 44, offsetof(mavlink_imu_data_t, acc_z) }, \
         { "roll", NULL, MAVLINK_TYPE_FLOAT, 0, 48, offsetof(mavlink_imu_data_t, roll) }, \
         { "pitch", NULL, MAVLINK_TYPE_FLOAT, 0, 52, offsetof(mavlink_imu_data_t, pitch) }, \
         { "yaw", NULL, MAVLINK_TYPE_FLOAT, 0, 56, offsetof(mavlink_imu_data_t, yaw) }, \
         { "gyro_x", NULL, MAVLINK_TYPE_FLOAT, 0, 60, offsetof(mavlink_imu_data_t, gyro_x) }, \
         { "gyro_y", NULL, MAVLINK_TYPE_FLOAT, 0, 64, offsetof(mavlink_imu_data_t, gyro_y) }, \
         { "gyro_z", NULL, MAVLINK_TYPE_FLOAT, 0, 68, offsetof(mavlink_imu_data_t, gyro_z) }, \
         { "temp", NULL, MAVLINK_TYPE_FLOAT, 0, 72, offsetof(mavlink_imu_data_t, temp) }, \
         { "turns", NULL, MAVLINK_TYPE_INT16_T, 0, 92, offsetof(mavlink_imu_data_t, turns) }, \
         { "imu_status", NULL, MAVLINK_TYPE_UINT8_T, 0, 94, offsetof(mavlink_imu_data_t, imu_status) }, \
         { "fault", NULL, MAVLINK_TYPE_UINT8_T, 0, 95, offsetof(mavlink_imu_data_t, fault) }, \
         { "is_calibrating", NULL, MAVLINK_TYPE_UINT8_T, 0, 96, offsetof(mavlink_imu_data_t, is_calibrating) }, \
         { "dvl_velx", NULL, MAVLINK_TYPE_FLOAT, 0, 76, offsetof(mavlink_imu_data_t, dvl_velx) }, \
         { "dvl_vely", NULL, MAVLINK_TYPE_FLOAT, 0, 80, offsetof(mavlink_imu_data_t, dvl_vely) }, \
         { "dvl_velz", NULL, MAVLINK_TYPE_FLOAT, 0, 84, offsetof(mavlink_imu_data_t, dvl_velz) }, \
         { "dvl_height", NULL, MAVLINK_TYPE_FLOAT, 0, 88, offsetof(mavlink_imu_data_t, dvl_height) }, \
         { "dvl_status", NULL, MAVLINK_TYPE_UINT8_T, 0, 97, offsetof(mavlink_imu_data_t, dvl_status) }, \
         } \
}
#else
#define MAVLINK_MESSAGE_INFO_IMU_DATA { \
    "IMU_DATA", \
    26, \
    {  { "timestamp_ms", NULL, MAVLINK_TYPE_UINT32_T, 0, 16, offsetof(mavlink_imu_data_t, timestamp_ms) }, \
         { "lon", NULL, MAVLINK_TYPE_DOUBLE, 0, 0, offsetof(mavlink_imu_data_t, lon) }, \
         { "lat", NULL, MAVLINK_TYPE_DOUBLE, 0, 8, offsetof(mavlink_imu_data_t, lat) }, \
         { "alt", NULL, MAVLINK_TYPE_FLOAT, 0, 20, offsetof(mavlink_imu_data_t, alt) }, \
         { "vel_n", NULL, MAVLINK_TYPE_FLOAT, 0, 24, offsetof(mavlink_imu_data_t, vel_n) }, \
         { "vel_e", NULL, MAVLINK_TYPE_FLOAT, 0, 28, offsetof(mavlink_imu_data_t, vel_e) }, \
         { "vel_u", NULL, MAVLINK_TYPE_FLOAT, 0, 32, offsetof(mavlink_imu_data_t, vel_u) }, \
         { "acc_x", NULL, MAVLINK_TYPE_FLOAT, 0, 36, offsetof(mavlink_imu_data_t, acc_x) }, \
         { "acc_y", NULL, MAVLINK_TYPE_FLOAT, 0, 40, offsetof(mavlink_imu_data_t, acc_y) }, \
         { "acc_z", NULL, MAVLINK_TYPE_FLOAT, 0, 44, offsetof(mavlink_imu_data_t, acc_z) }, \
         { "roll", NULL, MAVLINK_TYPE_FLOAT, 0, 48, offsetof(mavlink_imu_data_t, roll) }, \
         { "pitch", NULL, MAVLINK_TYPE_FLOAT, 0, 52, offsetof(mavlink_imu_data_t, pitch) }, \
         { "yaw", NULL, MAVLINK_TYPE_FLOAT, 0, 56, offsetof(mavlink_imu_data_t, yaw) }, \
         { "gyro_x", NULL, MAVLINK_TYPE_FLOAT, 0, 60, offsetof(mavlink_imu_data_t, gyro_x) }, \
         { "gyro_y", NULL, MAVLINK_TYPE_FLOAT, 0, 64, offsetof(mavlink_imu_data_t, gyro_y) }, \
         { "gyro_z", NULL, MAVLINK_TYPE_FLOAT, 0, 68, offsetof(mavlink_imu_data_t, gyro_z) }, \
         { "temp", NULL, MAVLINK_TYPE_FLOAT, 0, 72, offsetof(mavlink_imu_data_t, temp) }, \
         { "turns", NULL, MAVLINK_TYPE_INT16_T, 0, 92, offsetof(mavlink_imu_data_t, turns) }, \
         { "imu_status", NULL, MAVLINK_TYPE_UINT8_T, 0, 94, offsetof(mavlink_imu_data_t, imu_status) }, \
         { "fault", NULL, MAVLINK_TYPE_UINT8_T, 0, 95, offsetof(mavlink_imu_data_t, fault) }, \
         { "is_calibrating", NULL, MAVLINK_TYPE_UINT8_T, 0, 96, offsetof(mavlink_imu_data_t, is_calibrating) }, \
         { "dvl_velx", NULL, MAVLINK_TYPE_FLOAT, 0, 76, offsetof(mavlink_imu_data_t, dvl_velx) }, \
         { "dvl_vely", NULL, MAVLINK_TYPE_FLOAT, 0, 80, offsetof(mavlink_imu_data_t, dvl_vely) }, \
         { "dvl_velz", NULL, MAVLINK_TYPE_FLOAT, 0, 84, offsetof(mavlink_imu_data_t, dvl_velz) }, \
         { "dvl_height", NULL, MAVLINK_TYPE_FLOAT, 0, 88, offsetof(mavlink_imu_data_t, dvl_height) }, \
         { "dvl_status", NULL, MAVLINK_TYPE_UINT8_T, 0, 97, offsetof(mavlink_imu_data_t, dvl_status) }, \
         } \
}
#endif

/**
 * @brief Pack a imu_data message
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param msg The MAVLink message to compress the data into
 *
 * @param timestamp_ms [ms] Timestamp from the sender clock.
 * @param lon [deg] Longitude.
 * @param lat [deg] Latitude.
 * @param alt [m] Altitude.
 * @param vel_n [m/s] North velocity.
 * @param vel_e [m/s] East velocity.
 * @param vel_u [m/s] Up or ground-referenced velocity, matching the STM32 protocol table.
 * @param acc_x [m/s/s] X-axis acceleration.
 * @param acc_y [m/s/s] Y-axis acceleration.
 * @param acc_z [m/s/s] Z-axis acceleration.
 * @param roll [deg] Roll angle.
 * @param pitch [deg] Pitch angle.
 * @param yaw [deg] Heading angle.
 * @param gyro_x [deg/s] Roll angular velocity.
 * @param gyro_y [deg/s] Pitch angular velocity.
 * @param gyro_z [deg/s] Heading angular velocity.
 * @param temp [degC] IMU temperature.
 * @param turns  IMU heading turn count; positive and negative values are valid.
 * @param imu_status  IMU status code.
 * @param fault  IMU fault code.
 * @param is_calibrating  IMU calibration flag: 0 not calibrating, 1 calibrating.
 * @param dvl_velx [m/s] DVL X-axis velocity.
 * @param dvl_vely [m/s] DVL Y-axis velocity.
 * @param dvl_velz [m/s] DVL Z-axis velocity.
 * @param dvl_height [m] DVL altitude above bottom.
 * @param dvl_status  DVL status code.
 * @return length of the message in bytes (excluding serial stream start sign)
 */
static inline uint16_t mavlink_msg_imu_data_pack(uint8_t system_id, uint8_t component_id, mavlink_message_t* msg,
                               uint32_t timestamp_ms, double lon, double lat, float alt, float vel_n, float vel_e, float vel_u, float acc_x, float acc_y, float acc_z, float roll, float pitch, float yaw, float gyro_x, float gyro_y, float gyro_z, float temp, int16_t turns, uint8_t imu_status, uint8_t fault, uint8_t is_calibrating, float dvl_velx, float dvl_vely, float dvl_velz, float dvl_height, uint8_t dvl_status)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    char buf[MAVLINK_MSG_ID_IMU_DATA_LEN];
    _mav_put_double(buf, 0, lon);
    _mav_put_double(buf, 8, lat);
    _mav_put_uint32_t(buf, 16, timestamp_ms);
    _mav_put_float(buf, 20, alt);
    _mav_put_float(buf, 24, vel_n);
    _mav_put_float(buf, 28, vel_e);
    _mav_put_float(buf, 32, vel_u);
    _mav_put_float(buf, 36, acc_x);
    _mav_put_float(buf, 40, acc_y);
    _mav_put_float(buf, 44, acc_z);
    _mav_put_float(buf, 48, roll);
    _mav_put_float(buf, 52, pitch);
    _mav_put_float(buf, 56, yaw);
    _mav_put_float(buf, 60, gyro_x);
    _mav_put_float(buf, 64, gyro_y);
    _mav_put_float(buf, 68, gyro_z);
    _mav_put_float(buf, 72, temp);
    _mav_put_float(buf, 76, dvl_velx);
    _mav_put_float(buf, 80, dvl_vely);
    _mav_put_float(buf, 84, dvl_velz);
    _mav_put_float(buf, 88, dvl_height);
    _mav_put_int16_t(buf, 92, turns);
    _mav_put_uint8_t(buf, 94, imu_status);
    _mav_put_uint8_t(buf, 95, fault);
    _mav_put_uint8_t(buf, 96, is_calibrating);
    _mav_put_uint8_t(buf, 97, dvl_status);

        memcpy(_MAV_PAYLOAD_NON_CONST(msg), buf, MAVLINK_MSG_ID_IMU_DATA_LEN);
#else
    mavlink_imu_data_t packet;
    packet.lon = lon;
    packet.lat = lat;
    packet.timestamp_ms = timestamp_ms;
    packet.alt = alt;
    packet.vel_n = vel_n;
    packet.vel_e = vel_e;
    packet.vel_u = vel_u;
    packet.acc_x = acc_x;
    packet.acc_y = acc_y;
    packet.acc_z = acc_z;
    packet.roll = roll;
    packet.pitch = pitch;
    packet.yaw = yaw;
    packet.gyro_x = gyro_x;
    packet.gyro_y = gyro_y;
    packet.gyro_z = gyro_z;
    packet.temp = temp;
    packet.dvl_velx = dvl_velx;
    packet.dvl_vely = dvl_vely;
    packet.dvl_velz = dvl_velz;
    packet.dvl_height = dvl_height;
    packet.turns = turns;
    packet.imu_status = imu_status;
    packet.fault = fault;
    packet.is_calibrating = is_calibrating;
    packet.dvl_status = dvl_status;

        memcpy(_MAV_PAYLOAD_NON_CONST(msg), &packet, MAVLINK_MSG_ID_IMU_DATA_LEN);
#endif

    msg->msgid = MAVLINK_MSG_ID_IMU_DATA;
    return mavlink_finalize_message(msg, system_id, component_id, MAVLINK_MSG_ID_IMU_DATA_MIN_LEN, MAVLINK_MSG_ID_IMU_DATA_LEN, MAVLINK_MSG_ID_IMU_DATA_CRC);
}

/**
 * @brief Pack a imu_data message
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param status MAVLink status structure
 * @param msg The MAVLink message to compress the data into
 *
 * @param timestamp_ms [ms] Timestamp from the sender clock.
 * @param lon [deg] Longitude.
 * @param lat [deg] Latitude.
 * @param alt [m] Altitude.
 * @param vel_n [m/s] North velocity.
 * @param vel_e [m/s] East velocity.
 * @param vel_u [m/s] Up or ground-referenced velocity, matching the STM32 protocol table.
 * @param acc_x [m/s/s] X-axis acceleration.
 * @param acc_y [m/s/s] Y-axis acceleration.
 * @param acc_z [m/s/s] Z-axis acceleration.
 * @param roll [deg] Roll angle.
 * @param pitch [deg] Pitch angle.
 * @param yaw [deg] Heading angle.
 * @param gyro_x [deg/s] Roll angular velocity.
 * @param gyro_y [deg/s] Pitch angular velocity.
 * @param gyro_z [deg/s] Heading angular velocity.
 * @param temp [degC] IMU temperature.
 * @param turns  IMU heading turn count; positive and negative values are valid.
 * @param imu_status  IMU status code.
 * @param fault  IMU fault code.
 * @param is_calibrating  IMU calibration flag: 0 not calibrating, 1 calibrating.
 * @param dvl_velx [m/s] DVL X-axis velocity.
 * @param dvl_vely [m/s] DVL Y-axis velocity.
 * @param dvl_velz [m/s] DVL Z-axis velocity.
 * @param dvl_height [m] DVL altitude above bottom.
 * @param dvl_status  DVL status code.
 * @return length of the message in bytes (excluding serial stream start sign)
 */
static inline uint16_t mavlink_msg_imu_data_pack_status(uint8_t system_id, uint8_t component_id, mavlink_status_t *_status, mavlink_message_t* msg,
                               uint32_t timestamp_ms, double lon, double lat, float alt, float vel_n, float vel_e, float vel_u, float acc_x, float acc_y, float acc_z, float roll, float pitch, float yaw, float gyro_x, float gyro_y, float gyro_z, float temp, int16_t turns, uint8_t imu_status, uint8_t fault, uint8_t is_calibrating, float dvl_velx, float dvl_vely, float dvl_velz, float dvl_height, uint8_t dvl_status)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    char buf[MAVLINK_MSG_ID_IMU_DATA_LEN];
    _mav_put_double(buf, 0, lon);
    _mav_put_double(buf, 8, lat);
    _mav_put_uint32_t(buf, 16, timestamp_ms);
    _mav_put_float(buf, 20, alt);
    _mav_put_float(buf, 24, vel_n);
    _mav_put_float(buf, 28, vel_e);
    _mav_put_float(buf, 32, vel_u);
    _mav_put_float(buf, 36, acc_x);
    _mav_put_float(buf, 40, acc_y);
    _mav_put_float(buf, 44, acc_z);
    _mav_put_float(buf, 48, roll);
    _mav_put_float(buf, 52, pitch);
    _mav_put_float(buf, 56, yaw);
    _mav_put_float(buf, 60, gyro_x);
    _mav_put_float(buf, 64, gyro_y);
    _mav_put_float(buf, 68, gyro_z);
    _mav_put_float(buf, 72, temp);
    _mav_put_float(buf, 76, dvl_velx);
    _mav_put_float(buf, 80, dvl_vely);
    _mav_put_float(buf, 84, dvl_velz);
    _mav_put_float(buf, 88, dvl_height);
    _mav_put_int16_t(buf, 92, turns);
    _mav_put_uint8_t(buf, 94, imu_status);
    _mav_put_uint8_t(buf, 95, fault);
    _mav_put_uint8_t(buf, 96, is_calibrating);
    _mav_put_uint8_t(buf, 97, dvl_status);

        memcpy(_MAV_PAYLOAD_NON_CONST(msg), buf, MAVLINK_MSG_ID_IMU_DATA_LEN);
#else
    mavlink_imu_data_t packet;
    packet.lon = lon;
    packet.lat = lat;
    packet.timestamp_ms = timestamp_ms;
    packet.alt = alt;
    packet.vel_n = vel_n;
    packet.vel_e = vel_e;
    packet.vel_u = vel_u;
    packet.acc_x = acc_x;
    packet.acc_y = acc_y;
    packet.acc_z = acc_z;
    packet.roll = roll;
    packet.pitch = pitch;
    packet.yaw = yaw;
    packet.gyro_x = gyro_x;
    packet.gyro_y = gyro_y;
    packet.gyro_z = gyro_z;
    packet.temp = temp;
    packet.dvl_velx = dvl_velx;
    packet.dvl_vely = dvl_vely;
    packet.dvl_velz = dvl_velz;
    packet.dvl_height = dvl_height;
    packet.turns = turns;
    packet.imu_status = imu_status;
    packet.fault = fault;
    packet.is_calibrating = is_calibrating;
    packet.dvl_status = dvl_status;

        memcpy(_MAV_PAYLOAD_NON_CONST(msg), &packet, MAVLINK_MSG_ID_IMU_DATA_LEN);
#endif

    msg->msgid = MAVLINK_MSG_ID_IMU_DATA;
#if MAVLINK_CRC_EXTRA
    return mavlink_finalize_message_buffer(msg, system_id, component_id, _status, MAVLINK_MSG_ID_IMU_DATA_MIN_LEN, MAVLINK_MSG_ID_IMU_DATA_LEN, MAVLINK_MSG_ID_IMU_DATA_CRC);
#else
    return mavlink_finalize_message_buffer(msg, system_id, component_id, _status, MAVLINK_MSG_ID_IMU_DATA_MIN_LEN, MAVLINK_MSG_ID_IMU_DATA_LEN);
#endif
}

/**
 * @brief Pack a imu_data message on a channel
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param chan The MAVLink channel this message will be sent over
 * @param msg The MAVLink message to compress the data into
 * @param timestamp_ms [ms] Timestamp from the sender clock.
 * @param lon [deg] Longitude.
 * @param lat [deg] Latitude.
 * @param alt [m] Altitude.
 * @param vel_n [m/s] North velocity.
 * @param vel_e [m/s] East velocity.
 * @param vel_u [m/s] Up or ground-referenced velocity, matching the STM32 protocol table.
 * @param acc_x [m/s/s] X-axis acceleration.
 * @param acc_y [m/s/s] Y-axis acceleration.
 * @param acc_z [m/s/s] Z-axis acceleration.
 * @param roll [deg] Roll angle.
 * @param pitch [deg] Pitch angle.
 * @param yaw [deg] Heading angle.
 * @param gyro_x [deg/s] Roll angular velocity.
 * @param gyro_y [deg/s] Pitch angular velocity.
 * @param gyro_z [deg/s] Heading angular velocity.
 * @param temp [degC] IMU temperature.
 * @param turns  IMU heading turn count; positive and negative values are valid.
 * @param imu_status  IMU status code.
 * @param fault  IMU fault code.
 * @param is_calibrating  IMU calibration flag: 0 not calibrating, 1 calibrating.
 * @param dvl_velx [m/s] DVL X-axis velocity.
 * @param dvl_vely [m/s] DVL Y-axis velocity.
 * @param dvl_velz [m/s] DVL Z-axis velocity.
 * @param dvl_height [m] DVL altitude above bottom.
 * @param dvl_status  DVL status code.
 * @return length of the message in bytes (excluding serial stream start sign)
 */
static inline uint16_t mavlink_msg_imu_data_pack_chan(uint8_t system_id, uint8_t component_id, uint8_t chan,
                               mavlink_message_t* msg,
                                   uint32_t timestamp_ms,double lon,double lat,float alt,float vel_n,float vel_e,float vel_u,float acc_x,float acc_y,float acc_z,float roll,float pitch,float yaw,float gyro_x,float gyro_y,float gyro_z,float temp,int16_t turns,uint8_t imu_status,uint8_t fault,uint8_t is_calibrating,float dvl_velx,float dvl_vely,float dvl_velz,float dvl_height,uint8_t dvl_status)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    char buf[MAVLINK_MSG_ID_IMU_DATA_LEN];
    _mav_put_double(buf, 0, lon);
    _mav_put_double(buf, 8, lat);
    _mav_put_uint32_t(buf, 16, timestamp_ms);
    _mav_put_float(buf, 20, alt);
    _mav_put_float(buf, 24, vel_n);
    _mav_put_float(buf, 28, vel_e);
    _mav_put_float(buf, 32, vel_u);
    _mav_put_float(buf, 36, acc_x);
    _mav_put_float(buf, 40, acc_y);
    _mav_put_float(buf, 44, acc_z);
    _mav_put_float(buf, 48, roll);
    _mav_put_float(buf, 52, pitch);
    _mav_put_float(buf, 56, yaw);
    _mav_put_float(buf, 60, gyro_x);
    _mav_put_float(buf, 64, gyro_y);
    _mav_put_float(buf, 68, gyro_z);
    _mav_put_float(buf, 72, temp);
    _mav_put_float(buf, 76, dvl_velx);
    _mav_put_float(buf, 80, dvl_vely);
    _mav_put_float(buf, 84, dvl_velz);
    _mav_put_float(buf, 88, dvl_height);
    _mav_put_int16_t(buf, 92, turns);
    _mav_put_uint8_t(buf, 94, imu_status);
    _mav_put_uint8_t(buf, 95, fault);
    _mav_put_uint8_t(buf, 96, is_calibrating);
    _mav_put_uint8_t(buf, 97, dvl_status);

        memcpy(_MAV_PAYLOAD_NON_CONST(msg), buf, MAVLINK_MSG_ID_IMU_DATA_LEN);
#else
    mavlink_imu_data_t packet;
    packet.lon = lon;
    packet.lat = lat;
    packet.timestamp_ms = timestamp_ms;
    packet.alt = alt;
    packet.vel_n = vel_n;
    packet.vel_e = vel_e;
    packet.vel_u = vel_u;
    packet.acc_x = acc_x;
    packet.acc_y = acc_y;
    packet.acc_z = acc_z;
    packet.roll = roll;
    packet.pitch = pitch;
    packet.yaw = yaw;
    packet.gyro_x = gyro_x;
    packet.gyro_y = gyro_y;
    packet.gyro_z = gyro_z;
    packet.temp = temp;
    packet.dvl_velx = dvl_velx;
    packet.dvl_vely = dvl_vely;
    packet.dvl_velz = dvl_velz;
    packet.dvl_height = dvl_height;
    packet.turns = turns;
    packet.imu_status = imu_status;
    packet.fault = fault;
    packet.is_calibrating = is_calibrating;
    packet.dvl_status = dvl_status;

        memcpy(_MAV_PAYLOAD_NON_CONST(msg), &packet, MAVLINK_MSG_ID_IMU_DATA_LEN);
#endif

    msg->msgid = MAVLINK_MSG_ID_IMU_DATA;
    return mavlink_finalize_message_chan(msg, system_id, component_id, chan, MAVLINK_MSG_ID_IMU_DATA_MIN_LEN, MAVLINK_MSG_ID_IMU_DATA_LEN, MAVLINK_MSG_ID_IMU_DATA_CRC);
}

/**
 * @brief Encode a imu_data struct
 *
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param msg The MAVLink message to compress the data into
 * @param imu_data C-struct to read the message contents from
 */
static inline uint16_t mavlink_msg_imu_data_encode(uint8_t system_id, uint8_t component_id, mavlink_message_t* msg, const mavlink_imu_data_t* imu_data)
{
    return mavlink_msg_imu_data_pack(system_id, component_id, msg, imu_data->timestamp_ms, imu_data->lon, imu_data->lat, imu_data->alt, imu_data->vel_n, imu_data->vel_e, imu_data->vel_u, imu_data->acc_x, imu_data->acc_y, imu_data->acc_z, imu_data->roll, imu_data->pitch, imu_data->yaw, imu_data->gyro_x, imu_data->gyro_y, imu_data->gyro_z, imu_data->temp, imu_data->turns, imu_data->imu_status, imu_data->fault, imu_data->is_calibrating, imu_data->dvl_velx, imu_data->dvl_vely, imu_data->dvl_velz, imu_data->dvl_height, imu_data->dvl_status);
}

/**
 * @brief Encode a imu_data struct on a channel
 *
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param chan The MAVLink channel this message will be sent over
 * @param msg The MAVLink message to compress the data into
 * @param imu_data C-struct to read the message contents from
 */
static inline uint16_t mavlink_msg_imu_data_encode_chan(uint8_t system_id, uint8_t component_id, uint8_t chan, mavlink_message_t* msg, const mavlink_imu_data_t* imu_data)
{
    return mavlink_msg_imu_data_pack_chan(system_id, component_id, chan, msg, imu_data->timestamp_ms, imu_data->lon, imu_data->lat, imu_data->alt, imu_data->vel_n, imu_data->vel_e, imu_data->vel_u, imu_data->acc_x, imu_data->acc_y, imu_data->acc_z, imu_data->roll, imu_data->pitch, imu_data->yaw, imu_data->gyro_x, imu_data->gyro_y, imu_data->gyro_z, imu_data->temp, imu_data->turns, imu_data->imu_status, imu_data->fault, imu_data->is_calibrating, imu_data->dvl_velx, imu_data->dvl_vely, imu_data->dvl_velz, imu_data->dvl_height, imu_data->dvl_status);
}

/**
 * @brief Encode a imu_data struct with provided status structure
 *
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param status MAVLink status structure
 * @param msg The MAVLink message to compress the data into
 * @param imu_data C-struct to read the message contents from
 */
static inline uint16_t mavlink_msg_imu_data_encode_status(uint8_t system_id, uint8_t component_id, mavlink_status_t* _status, mavlink_message_t* msg, const mavlink_imu_data_t* imu_data)
{
    return mavlink_msg_imu_data_pack_status(system_id, component_id, _status, msg,  imu_data->timestamp_ms, imu_data->lon, imu_data->lat, imu_data->alt, imu_data->vel_n, imu_data->vel_e, imu_data->vel_u, imu_data->acc_x, imu_data->acc_y, imu_data->acc_z, imu_data->roll, imu_data->pitch, imu_data->yaw, imu_data->gyro_x, imu_data->gyro_y, imu_data->gyro_z, imu_data->temp, imu_data->turns, imu_data->imu_status, imu_data->fault, imu_data->is_calibrating, imu_data->dvl_velx, imu_data->dvl_vely, imu_data->dvl_velz, imu_data->dvl_height, imu_data->dvl_status);
}

/**
 * @brief Send a imu_data message
 * @param chan MAVLink channel to send the message
 *
 * @param timestamp_ms [ms] Timestamp from the sender clock.
 * @param lon [deg] Longitude.
 * @param lat [deg] Latitude.
 * @param alt [m] Altitude.
 * @param vel_n [m/s] North velocity.
 * @param vel_e [m/s] East velocity.
 * @param vel_u [m/s] Up or ground-referenced velocity, matching the STM32 protocol table.
 * @param acc_x [m/s/s] X-axis acceleration.
 * @param acc_y [m/s/s] Y-axis acceleration.
 * @param acc_z [m/s/s] Z-axis acceleration.
 * @param roll [deg] Roll angle.
 * @param pitch [deg] Pitch angle.
 * @param yaw [deg] Heading angle.
 * @param gyro_x [deg/s] Roll angular velocity.
 * @param gyro_y [deg/s] Pitch angular velocity.
 * @param gyro_z [deg/s] Heading angular velocity.
 * @param temp [degC] IMU temperature.
 * @param turns  IMU heading turn count; positive and negative values are valid.
 * @param imu_status  IMU status code.
 * @param fault  IMU fault code.
 * @param is_calibrating  IMU calibration flag: 0 not calibrating, 1 calibrating.
 * @param dvl_velx [m/s] DVL X-axis velocity.
 * @param dvl_vely [m/s] DVL Y-axis velocity.
 * @param dvl_velz [m/s] DVL Z-axis velocity.
 * @param dvl_height [m] DVL altitude above bottom.
 * @param dvl_status  DVL status code.
 */
#ifdef MAVLINK_USE_CONVENIENCE_FUNCTIONS

static inline void mavlink_msg_imu_data_send(mavlink_channel_t chan, uint32_t timestamp_ms, double lon, double lat, float alt, float vel_n, float vel_e, float vel_u, float acc_x, float acc_y, float acc_z, float roll, float pitch, float yaw, float gyro_x, float gyro_y, float gyro_z, float temp, int16_t turns, uint8_t imu_status, uint8_t fault, uint8_t is_calibrating, float dvl_velx, float dvl_vely, float dvl_velz, float dvl_height, uint8_t dvl_status)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    char buf[MAVLINK_MSG_ID_IMU_DATA_LEN];
    _mav_put_double(buf, 0, lon);
    _mav_put_double(buf, 8, lat);
    _mav_put_uint32_t(buf, 16, timestamp_ms);
    _mav_put_float(buf, 20, alt);
    _mav_put_float(buf, 24, vel_n);
    _mav_put_float(buf, 28, vel_e);
    _mav_put_float(buf, 32, vel_u);
    _mav_put_float(buf, 36, acc_x);
    _mav_put_float(buf, 40, acc_y);
    _mav_put_float(buf, 44, acc_z);
    _mav_put_float(buf, 48, roll);
    _mav_put_float(buf, 52, pitch);
    _mav_put_float(buf, 56, yaw);
    _mav_put_float(buf, 60, gyro_x);
    _mav_put_float(buf, 64, gyro_y);
    _mav_put_float(buf, 68, gyro_z);
    _mav_put_float(buf, 72, temp);
    _mav_put_float(buf, 76, dvl_velx);
    _mav_put_float(buf, 80, dvl_vely);
    _mav_put_float(buf, 84, dvl_velz);
    _mav_put_float(buf, 88, dvl_height);
    _mav_put_int16_t(buf, 92, turns);
    _mav_put_uint8_t(buf, 94, imu_status);
    _mav_put_uint8_t(buf, 95, fault);
    _mav_put_uint8_t(buf, 96, is_calibrating);
    _mav_put_uint8_t(buf, 97, dvl_status);

    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_IMU_DATA, buf, MAVLINK_MSG_ID_IMU_DATA_MIN_LEN, MAVLINK_MSG_ID_IMU_DATA_LEN, MAVLINK_MSG_ID_IMU_DATA_CRC);
#else
    mavlink_imu_data_t packet;
    packet.lon = lon;
    packet.lat = lat;
    packet.timestamp_ms = timestamp_ms;
    packet.alt = alt;
    packet.vel_n = vel_n;
    packet.vel_e = vel_e;
    packet.vel_u = vel_u;
    packet.acc_x = acc_x;
    packet.acc_y = acc_y;
    packet.acc_z = acc_z;
    packet.roll = roll;
    packet.pitch = pitch;
    packet.yaw = yaw;
    packet.gyro_x = gyro_x;
    packet.gyro_y = gyro_y;
    packet.gyro_z = gyro_z;
    packet.temp = temp;
    packet.dvl_velx = dvl_velx;
    packet.dvl_vely = dvl_vely;
    packet.dvl_velz = dvl_velz;
    packet.dvl_height = dvl_height;
    packet.turns = turns;
    packet.imu_status = imu_status;
    packet.fault = fault;
    packet.is_calibrating = is_calibrating;
    packet.dvl_status = dvl_status;

    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_IMU_DATA, (const char *)&packet, MAVLINK_MSG_ID_IMU_DATA_MIN_LEN, MAVLINK_MSG_ID_IMU_DATA_LEN, MAVLINK_MSG_ID_IMU_DATA_CRC);
#endif
}

/**
 * @brief Send a imu_data message
 * @param chan MAVLink channel to send the message
 * @param struct The MAVLink struct to serialize
 */
static inline void mavlink_msg_imu_data_send_struct(mavlink_channel_t chan, const mavlink_imu_data_t* imu_data)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    mavlink_msg_imu_data_send(chan, imu_data->timestamp_ms, imu_data->lon, imu_data->lat, imu_data->alt, imu_data->vel_n, imu_data->vel_e, imu_data->vel_u, imu_data->acc_x, imu_data->acc_y, imu_data->acc_z, imu_data->roll, imu_data->pitch, imu_data->yaw, imu_data->gyro_x, imu_data->gyro_y, imu_data->gyro_z, imu_data->temp, imu_data->turns, imu_data->imu_status, imu_data->fault, imu_data->is_calibrating, imu_data->dvl_velx, imu_data->dvl_vely, imu_data->dvl_velz, imu_data->dvl_height, imu_data->dvl_status);
#else
    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_IMU_DATA, (const char *)imu_data, MAVLINK_MSG_ID_IMU_DATA_MIN_LEN, MAVLINK_MSG_ID_IMU_DATA_LEN, MAVLINK_MSG_ID_IMU_DATA_CRC);
#endif
}

#if MAVLINK_MSG_ID_IMU_DATA_LEN <= MAVLINK_MAX_PAYLOAD_LEN
/*
  This variant of _send() can be used to save stack space by reusing
  memory from the receive buffer.  The caller provides a
  mavlink_message_t which is the size of a full mavlink message. This
  is usually the receive buffer for the channel, and allows a reply to an
  incoming message with minimum stack space usage.
 */
static inline void mavlink_msg_imu_data_send_buf(mavlink_message_t *msgbuf, mavlink_channel_t chan,  uint32_t timestamp_ms, double lon, double lat, float alt, float vel_n, float vel_e, float vel_u, float acc_x, float acc_y, float acc_z, float roll, float pitch, float yaw, float gyro_x, float gyro_y, float gyro_z, float temp, int16_t turns, uint8_t imu_status, uint8_t fault, uint8_t is_calibrating, float dvl_velx, float dvl_vely, float dvl_velz, float dvl_height, uint8_t dvl_status)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    char *buf = (char *)msgbuf;
    _mav_put_double(buf, 0, lon);
    _mav_put_double(buf, 8, lat);
    _mav_put_uint32_t(buf, 16, timestamp_ms);
    _mav_put_float(buf, 20, alt);
    _mav_put_float(buf, 24, vel_n);
    _mav_put_float(buf, 28, vel_e);
    _mav_put_float(buf, 32, vel_u);
    _mav_put_float(buf, 36, acc_x);
    _mav_put_float(buf, 40, acc_y);
    _mav_put_float(buf, 44, acc_z);
    _mav_put_float(buf, 48, roll);
    _mav_put_float(buf, 52, pitch);
    _mav_put_float(buf, 56, yaw);
    _mav_put_float(buf, 60, gyro_x);
    _mav_put_float(buf, 64, gyro_y);
    _mav_put_float(buf, 68, gyro_z);
    _mav_put_float(buf, 72, temp);
    _mav_put_float(buf, 76, dvl_velx);
    _mav_put_float(buf, 80, dvl_vely);
    _mav_put_float(buf, 84, dvl_velz);
    _mav_put_float(buf, 88, dvl_height);
    _mav_put_int16_t(buf, 92, turns);
    _mav_put_uint8_t(buf, 94, imu_status);
    _mav_put_uint8_t(buf, 95, fault);
    _mav_put_uint8_t(buf, 96, is_calibrating);
    _mav_put_uint8_t(buf, 97, dvl_status);

    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_IMU_DATA, buf, MAVLINK_MSG_ID_IMU_DATA_MIN_LEN, MAVLINK_MSG_ID_IMU_DATA_LEN, MAVLINK_MSG_ID_IMU_DATA_CRC);
#else
    mavlink_imu_data_t *packet = (mavlink_imu_data_t *)msgbuf;
    packet->lon = lon;
    packet->lat = lat;
    packet->timestamp_ms = timestamp_ms;
    packet->alt = alt;
    packet->vel_n = vel_n;
    packet->vel_e = vel_e;
    packet->vel_u = vel_u;
    packet->acc_x = acc_x;
    packet->acc_y = acc_y;
    packet->acc_z = acc_z;
    packet->roll = roll;
    packet->pitch = pitch;
    packet->yaw = yaw;
    packet->gyro_x = gyro_x;
    packet->gyro_y = gyro_y;
    packet->gyro_z = gyro_z;
    packet->temp = temp;
    packet->dvl_velx = dvl_velx;
    packet->dvl_vely = dvl_vely;
    packet->dvl_velz = dvl_velz;
    packet->dvl_height = dvl_height;
    packet->turns = turns;
    packet->imu_status = imu_status;
    packet->fault = fault;
    packet->is_calibrating = is_calibrating;
    packet->dvl_status = dvl_status;

    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_IMU_DATA, (const char *)packet, MAVLINK_MSG_ID_IMU_DATA_MIN_LEN, MAVLINK_MSG_ID_IMU_DATA_LEN, MAVLINK_MSG_ID_IMU_DATA_CRC);
#endif
}
#endif

#endif

// MESSAGE IMU_DATA UNPACKING


/**
 * @brief Get field timestamp_ms from imu_data message
 *
 * @return [ms] Timestamp from the sender clock.
 */
static inline uint32_t mavlink_msg_imu_data_get_timestamp_ms(const mavlink_message_t* msg)
{
    return _MAV_RETURN_uint32_t(msg,  16);
}

/**
 * @brief Get field lon from imu_data message
 *
 * @return [deg] Longitude.
 */
static inline double mavlink_msg_imu_data_get_lon(const mavlink_message_t* msg)
{
    return _MAV_RETURN_double(msg,  0);
}

/**
 * @brief Get field lat from imu_data message
 *
 * @return [deg] Latitude.
 */
static inline double mavlink_msg_imu_data_get_lat(const mavlink_message_t* msg)
{
    return _MAV_RETURN_double(msg,  8);
}

/**
 * @brief Get field alt from imu_data message
 *
 * @return [m] Altitude.
 */
static inline float mavlink_msg_imu_data_get_alt(const mavlink_message_t* msg)
{
    return _MAV_RETURN_float(msg,  20);
}

/**
 * @brief Get field vel_n from imu_data message
 *
 * @return [m/s] North velocity.
 */
static inline float mavlink_msg_imu_data_get_vel_n(const mavlink_message_t* msg)
{
    return _MAV_RETURN_float(msg,  24);
}

/**
 * @brief Get field vel_e from imu_data message
 *
 * @return [m/s] East velocity.
 */
static inline float mavlink_msg_imu_data_get_vel_e(const mavlink_message_t* msg)
{
    return _MAV_RETURN_float(msg,  28);
}

/**
 * @brief Get field vel_u from imu_data message
 *
 * @return [m/s] Up or ground-referenced velocity, matching the STM32 protocol table.
 */
static inline float mavlink_msg_imu_data_get_vel_u(const mavlink_message_t* msg)
{
    return _MAV_RETURN_float(msg,  32);
}

/**
 * @brief Get field acc_x from imu_data message
 *
 * @return [m/s/s] X-axis acceleration.
 */
static inline float mavlink_msg_imu_data_get_acc_x(const mavlink_message_t* msg)
{
    return _MAV_RETURN_float(msg,  36);
}

/**
 * @brief Get field acc_y from imu_data message
 *
 * @return [m/s/s] Y-axis acceleration.
 */
static inline float mavlink_msg_imu_data_get_acc_y(const mavlink_message_t* msg)
{
    return _MAV_RETURN_float(msg,  40);
}

/**
 * @brief Get field acc_z from imu_data message
 *
 * @return [m/s/s] Z-axis acceleration.
 */
static inline float mavlink_msg_imu_data_get_acc_z(const mavlink_message_t* msg)
{
    return _MAV_RETURN_float(msg,  44);
}

/**
 * @brief Get field roll from imu_data message
 *
 * @return [deg] Roll angle.
 */
static inline float mavlink_msg_imu_data_get_roll(const mavlink_message_t* msg)
{
    return _MAV_RETURN_float(msg,  48);
}

/**
 * @brief Get field pitch from imu_data message
 *
 * @return [deg] Pitch angle.
 */
static inline float mavlink_msg_imu_data_get_pitch(const mavlink_message_t* msg)
{
    return _MAV_RETURN_float(msg,  52);
}

/**
 * @brief Get field yaw from imu_data message
 *
 * @return [deg] Heading angle.
 */
static inline float mavlink_msg_imu_data_get_yaw(const mavlink_message_t* msg)
{
    return _MAV_RETURN_float(msg,  56);
}

/**
 * @brief Get field gyro_x from imu_data message
 *
 * @return [deg/s] Roll angular velocity.
 */
static inline float mavlink_msg_imu_data_get_gyro_x(const mavlink_message_t* msg)
{
    return _MAV_RETURN_float(msg,  60);
}

/**
 * @brief Get field gyro_y from imu_data message
 *
 * @return [deg/s] Pitch angular velocity.
 */
static inline float mavlink_msg_imu_data_get_gyro_y(const mavlink_message_t* msg)
{
    return _MAV_RETURN_float(msg,  64);
}

/**
 * @brief Get field gyro_z from imu_data message
 *
 * @return [deg/s] Heading angular velocity.
 */
static inline float mavlink_msg_imu_data_get_gyro_z(const mavlink_message_t* msg)
{
    return _MAV_RETURN_float(msg,  68);
}

/**
 * @brief Get field temp from imu_data message
 *
 * @return [degC] IMU temperature.
 */
static inline float mavlink_msg_imu_data_get_temp(const mavlink_message_t* msg)
{
    return _MAV_RETURN_float(msg,  72);
}

/**
 * @brief Get field turns from imu_data message
 *
 * @return  IMU heading turn count; positive and negative values are valid.
 */
static inline int16_t mavlink_msg_imu_data_get_turns(const mavlink_message_t* msg)
{
    return _MAV_RETURN_int16_t(msg,  92);
}

/**
 * @brief Get field imu_status from imu_data message
 *
 * @return  IMU status code.
 */
static inline uint8_t mavlink_msg_imu_data_get_imu_status(const mavlink_message_t* msg)
{
    return _MAV_RETURN_uint8_t(msg,  94);
}

/**
 * @brief Get field fault from imu_data message
 *
 * @return  IMU fault code.
 */
static inline uint8_t mavlink_msg_imu_data_get_fault(const mavlink_message_t* msg)
{
    return _MAV_RETURN_uint8_t(msg,  95);
}

/**
 * @brief Get field is_calibrating from imu_data message
 *
 * @return  IMU calibration flag: 0 not calibrating, 1 calibrating.
 */
static inline uint8_t mavlink_msg_imu_data_get_is_calibrating(const mavlink_message_t* msg)
{
    return _MAV_RETURN_uint8_t(msg,  96);
}

/**
 * @brief Get field dvl_velx from imu_data message
 *
 * @return [m/s] DVL X-axis velocity.
 */
static inline float mavlink_msg_imu_data_get_dvl_velx(const mavlink_message_t* msg)
{
    return _MAV_RETURN_float(msg,  76);
}

/**
 * @brief Get field dvl_vely from imu_data message
 *
 * @return [m/s] DVL Y-axis velocity.
 */
static inline float mavlink_msg_imu_data_get_dvl_vely(const mavlink_message_t* msg)
{
    return _MAV_RETURN_float(msg,  80);
}

/**
 * @brief Get field dvl_velz from imu_data message
 *
 * @return [m/s] DVL Z-axis velocity.
 */
static inline float mavlink_msg_imu_data_get_dvl_velz(const mavlink_message_t* msg)
{
    return _MAV_RETURN_float(msg,  84);
}

/**
 * @brief Get field dvl_height from imu_data message
 *
 * @return [m] DVL altitude above bottom.
 */
static inline float mavlink_msg_imu_data_get_dvl_height(const mavlink_message_t* msg)
{
    return _MAV_RETURN_float(msg,  88);
}

/**
 * @brief Get field dvl_status from imu_data message
 *
 * @return  DVL status code.
 */
static inline uint8_t mavlink_msg_imu_data_get_dvl_status(const mavlink_message_t* msg)
{
    return _MAV_RETURN_uint8_t(msg,  97);
}

/**
 * @brief Decode a imu_data message into a struct
 *
 * @param msg The message to decode
 * @param imu_data C-struct to decode the message contents into
 */
static inline void mavlink_msg_imu_data_decode(const mavlink_message_t* msg, mavlink_imu_data_t* imu_data)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    imu_data->lon = mavlink_msg_imu_data_get_lon(msg);
    imu_data->lat = mavlink_msg_imu_data_get_lat(msg);
    imu_data->timestamp_ms = mavlink_msg_imu_data_get_timestamp_ms(msg);
    imu_data->alt = mavlink_msg_imu_data_get_alt(msg);
    imu_data->vel_n = mavlink_msg_imu_data_get_vel_n(msg);
    imu_data->vel_e = mavlink_msg_imu_data_get_vel_e(msg);
    imu_data->vel_u = mavlink_msg_imu_data_get_vel_u(msg);
    imu_data->acc_x = mavlink_msg_imu_data_get_acc_x(msg);
    imu_data->acc_y = mavlink_msg_imu_data_get_acc_y(msg);
    imu_data->acc_z = mavlink_msg_imu_data_get_acc_z(msg);
    imu_data->roll = mavlink_msg_imu_data_get_roll(msg);
    imu_data->pitch = mavlink_msg_imu_data_get_pitch(msg);
    imu_data->yaw = mavlink_msg_imu_data_get_yaw(msg);
    imu_data->gyro_x = mavlink_msg_imu_data_get_gyro_x(msg);
    imu_data->gyro_y = mavlink_msg_imu_data_get_gyro_y(msg);
    imu_data->gyro_z = mavlink_msg_imu_data_get_gyro_z(msg);
    imu_data->temp = mavlink_msg_imu_data_get_temp(msg);
    imu_data->dvl_velx = mavlink_msg_imu_data_get_dvl_velx(msg);
    imu_data->dvl_vely = mavlink_msg_imu_data_get_dvl_vely(msg);
    imu_data->dvl_velz = mavlink_msg_imu_data_get_dvl_velz(msg);
    imu_data->dvl_height = mavlink_msg_imu_data_get_dvl_height(msg);
    imu_data->turns = mavlink_msg_imu_data_get_turns(msg);
    imu_data->imu_status = mavlink_msg_imu_data_get_imu_status(msg);
    imu_data->fault = mavlink_msg_imu_data_get_fault(msg);
    imu_data->is_calibrating = mavlink_msg_imu_data_get_is_calibrating(msg);
    imu_data->dvl_status = mavlink_msg_imu_data_get_dvl_status(msg);
#else
        uint8_t len = msg->len < MAVLINK_MSG_ID_IMU_DATA_LEN? msg->len : MAVLINK_MSG_ID_IMU_DATA_LEN;
        memset(imu_data, 0, MAVLINK_MSG_ID_IMU_DATA_LEN);
    memcpy(imu_data, _MAV_PAYLOAD(msg), len);
#endif
}
