/** @file
 *    @brief MAVLink comm protocol testsuite generated from sealien_mavlink.xml
 *    @see https://mavlink.io/en/
 */
#pragma once
#ifndef SEALIEN_MAVLINK_TESTSUITE_H
#define SEALIEN_MAVLINK_TESTSUITE_H

#ifdef __cplusplus
extern "C" {
#endif

#ifndef MAVLINK_TEST_ALL
#define MAVLINK_TEST_ALL

static void mavlink_test_sealien_mavlink(uint8_t, uint8_t, mavlink_message_t *last_msg);

static void mavlink_test_all(uint8_t system_id, uint8_t component_id, mavlink_message_t *last_msg)
{

    mavlink_test_sealien_mavlink(system_id, component_id, last_msg);
}
#endif




static void mavlink_test_heartbeat(uint8_t system_id, uint8_t component_id, mavlink_message_t *last_msg)
{
#ifdef MAVLINK_STATUS_FLAG_OUT_MAVLINK1
    mavlink_status_t *status = mavlink_get_channel_status(MAVLINK_COMM_0);
        if ((status->flags & MAVLINK_STATUS_FLAG_OUT_MAVLINK1) && MAVLINK_MSG_ID_HEARTBEAT >= 256) {
            return;
        }
#endif
    mavlink_message_t msg;
        uint8_t buffer[MAVLINK_MAX_PACKET_LEN];
        uint16_t i;
    mavlink_heartbeat_t packet_in = {
        963497464,17,84,2
    };
    mavlink_heartbeat_t packet1, packet2;
        memset(&packet1, 0, sizeof(packet1));
        packet1.timestamp_ms = packet_in.timestamp_ms;
        packet1.type = packet_in.type;
        packet1.system_status = packet_in.system_status;
        packet1.mavlink_version = packet_in.mavlink_version;
        
        
#ifdef MAVLINK_STATUS_FLAG_OUT_MAVLINK1
        if (status->flags & MAVLINK_STATUS_FLAG_OUT_MAVLINK1) {
           // cope with extensions
           memset(MAVLINK_MSG_ID_HEARTBEAT_MIN_LEN + (char *)&packet1, 0, sizeof(packet1)-MAVLINK_MSG_ID_HEARTBEAT_MIN_LEN);
        }
#endif
        memset(&packet2, 0, sizeof(packet2));
    mavlink_msg_heartbeat_encode(system_id, component_id, &msg, &packet1);
    mavlink_msg_heartbeat_decode(&msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);

        memset(&packet2, 0, sizeof(packet2));
    mavlink_msg_heartbeat_pack(system_id, component_id, &msg , packet1.timestamp_ms , packet1.type , packet1.system_status );
    mavlink_msg_heartbeat_decode(&msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);

        memset(&packet2, 0, sizeof(packet2));
    mavlink_msg_heartbeat_pack_chan(system_id, component_id, MAVLINK_COMM_0, &msg , packet1.timestamp_ms , packet1.type , packet1.system_status );
    mavlink_msg_heartbeat_decode(&msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);

        memset(&packet2, 0, sizeof(packet2));
        mavlink_msg_to_send_buffer(buffer, &msg);
        for (i=0; i<mavlink_msg_get_send_buffer_length(&msg); i++) {
            comm_send_ch(MAVLINK_COMM_0, buffer[i]);
        }
    mavlink_msg_heartbeat_decode(last_msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);
        
        memset(&packet2, 0, sizeof(packet2));
    mavlink_msg_heartbeat_send(MAVLINK_COMM_1 , packet1.timestamp_ms , packet1.type , packet1.system_status );
    mavlink_msg_heartbeat_decode(last_msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);

#ifdef MAVLINK_HAVE_GET_MESSAGE_INFO
    MAVLINK_ASSERT(mavlink_get_message_info_by_name("HEARTBEAT") != NULL);
    MAVLINK_ASSERT(mavlink_get_message_info_by_id(MAVLINK_MSG_ID_HEARTBEAT) != NULL);
#endif
}

static void mavlink_test_imu_data(uint8_t system_id, uint8_t component_id, mavlink_message_t *last_msg)
{
#ifdef MAVLINK_STATUS_FLAG_OUT_MAVLINK1
    mavlink_status_t *status = mavlink_get_channel_status(MAVLINK_COMM_0);
        if ((status->flags & MAVLINK_STATUS_FLAG_OUT_MAVLINK1) && MAVLINK_MSG_ID_IMU_DATA >= 256) {
            return;
        }
#endif
    mavlink_message_t msg;
        uint8_t buffer[MAVLINK_MAX_PACKET_LEN];
        uint16_t i;
    mavlink_imu_data_t packet_in = {
        123.0,179.0,963498296,157.0,185.0,213.0,241.0,269.0,297.0,325.0,353.0,381.0,409.0,437.0,465.0,493.0,521.0,549.0,577.0,605.0,633.0,22019,159,226,37,104
    };
    mavlink_imu_data_t packet1, packet2;
        memset(&packet1, 0, sizeof(packet1));
        packet1.lon = packet_in.lon;
        packet1.lat = packet_in.lat;
        packet1.timestamp_ms = packet_in.timestamp_ms;
        packet1.alt = packet_in.alt;
        packet1.vel_n = packet_in.vel_n;
        packet1.vel_e = packet_in.vel_e;
        packet1.vel_u = packet_in.vel_u;
        packet1.acc_x = packet_in.acc_x;
        packet1.acc_y = packet_in.acc_y;
        packet1.acc_z = packet_in.acc_z;
        packet1.roll = packet_in.roll;
        packet1.pitch = packet_in.pitch;
        packet1.yaw = packet_in.yaw;
        packet1.gyro_x = packet_in.gyro_x;
        packet1.gyro_y = packet_in.gyro_y;
        packet1.gyro_z = packet_in.gyro_z;
        packet1.temp = packet_in.temp;
        packet1.dvl_velx = packet_in.dvl_velx;
        packet1.dvl_vely = packet_in.dvl_vely;
        packet1.dvl_velz = packet_in.dvl_velz;
        packet1.dvl_height = packet_in.dvl_height;
        packet1.turns = packet_in.turns;
        packet1.imu_status = packet_in.imu_status;
        packet1.fault = packet_in.fault;
        packet1.is_calibrating = packet_in.is_calibrating;
        packet1.dvl_status = packet_in.dvl_status;
        
        
#ifdef MAVLINK_STATUS_FLAG_OUT_MAVLINK1
        if (status->flags & MAVLINK_STATUS_FLAG_OUT_MAVLINK1) {
           // cope with extensions
           memset(MAVLINK_MSG_ID_IMU_DATA_MIN_LEN + (char *)&packet1, 0, sizeof(packet1)-MAVLINK_MSG_ID_IMU_DATA_MIN_LEN);
        }
#endif
        memset(&packet2, 0, sizeof(packet2));
    mavlink_msg_imu_data_encode(system_id, component_id, &msg, &packet1);
    mavlink_msg_imu_data_decode(&msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);

        memset(&packet2, 0, sizeof(packet2));
    mavlink_msg_imu_data_pack(system_id, component_id, &msg , packet1.timestamp_ms , packet1.lon , packet1.lat , packet1.alt , packet1.vel_n , packet1.vel_e , packet1.vel_u , packet1.acc_x , packet1.acc_y , packet1.acc_z , packet1.roll , packet1.pitch , packet1.yaw , packet1.gyro_x , packet1.gyro_y , packet1.gyro_z , packet1.temp , packet1.turns , packet1.imu_status , packet1.fault , packet1.is_calibrating , packet1.dvl_velx , packet1.dvl_vely , packet1.dvl_velz , packet1.dvl_height , packet1.dvl_status );
    mavlink_msg_imu_data_decode(&msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);

        memset(&packet2, 0, sizeof(packet2));
    mavlink_msg_imu_data_pack_chan(system_id, component_id, MAVLINK_COMM_0, &msg , packet1.timestamp_ms , packet1.lon , packet1.lat , packet1.alt , packet1.vel_n , packet1.vel_e , packet1.vel_u , packet1.acc_x , packet1.acc_y , packet1.acc_z , packet1.roll , packet1.pitch , packet1.yaw , packet1.gyro_x , packet1.gyro_y , packet1.gyro_z , packet1.temp , packet1.turns , packet1.imu_status , packet1.fault , packet1.is_calibrating , packet1.dvl_velx , packet1.dvl_vely , packet1.dvl_velz , packet1.dvl_height , packet1.dvl_status );
    mavlink_msg_imu_data_decode(&msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);

        memset(&packet2, 0, sizeof(packet2));
        mavlink_msg_to_send_buffer(buffer, &msg);
        for (i=0; i<mavlink_msg_get_send_buffer_length(&msg); i++) {
            comm_send_ch(MAVLINK_COMM_0, buffer[i]);
        }
    mavlink_msg_imu_data_decode(last_msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);
        
        memset(&packet2, 0, sizeof(packet2));
    mavlink_msg_imu_data_send(MAVLINK_COMM_1 , packet1.timestamp_ms , packet1.lon , packet1.lat , packet1.alt , packet1.vel_n , packet1.vel_e , packet1.vel_u , packet1.acc_x , packet1.acc_y , packet1.acc_z , packet1.roll , packet1.pitch , packet1.yaw , packet1.gyro_x , packet1.gyro_y , packet1.gyro_z , packet1.temp , packet1.turns , packet1.imu_status , packet1.fault , packet1.is_calibrating , packet1.dvl_velx , packet1.dvl_vely , packet1.dvl_velz , packet1.dvl_height , packet1.dvl_status );
    mavlink_msg_imu_data_decode(last_msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);

#ifdef MAVLINK_HAVE_GET_MESSAGE_INFO
    MAVLINK_ASSERT(mavlink_get_message_info_by_name("IMU_DATA") != NULL);
    MAVLINK_ASSERT(mavlink_get_message_info_by_id(MAVLINK_MSG_ID_IMU_DATA) != NULL);
#endif
}

static void mavlink_test_thruster_status(uint8_t system_id, uint8_t component_id, mavlink_message_t *last_msg)
{
#ifdef MAVLINK_STATUS_FLAG_OUT_MAVLINK1
    mavlink_status_t *status = mavlink_get_channel_status(MAVLINK_COMM_0);
        if ((status->flags & MAVLINK_STATUS_FLAG_OUT_MAVLINK1) && MAVLINK_MSG_ID_THRUSTER_STATUS >= 256) {
            return;
        }
#endif
    mavlink_message_t msg;
        uint8_t buffer[MAVLINK_MAX_PACKET_LEN];
        uint16_t i;
    mavlink_thruster_status_t packet_in = {
        963497464,{ 17443, 17444, 17445, 17446, 17447, 17448, 17449, 17450, 17451, 17452, 17453, 17454 },{ 18691, 18692, 18693, 18694, 18695, 18696, 18697, 18698, 18699, 18700, 18701, 18702 },{ 19939, 19940, 19941, 19942, 19943, 19944, 19945, 19946, 19947, 19948, 19949, 19950 },{ 233, 234, 235, 236, 237, 238, 239, 240, 241, 242, 243, 244 },{ 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24 },49
    };
    mavlink_thruster_status_t packet1, packet2;
        memset(&packet1, 0, sizeof(packet1));
        packet1.timestamp_ms = packet_in.timestamp_ms;
        packet1.lock = packet_in.lock;
        
        mav_array_memcpy(packet1.speed, packet_in.speed, sizeof(int16_t)*12);
        mav_array_memcpy(packet1.power, packet_in.power, sizeof(int16_t)*12);
        mav_array_memcpy(packet1.temp, packet_in.temp, sizeof(int16_t)*12);
        mav_array_memcpy(packet1.status, packet_in.status, sizeof(uint8_t)*12);
        mav_array_memcpy(packet1.fault, packet_in.fault, sizeof(uint8_t)*12);
        
#ifdef MAVLINK_STATUS_FLAG_OUT_MAVLINK1
        if (status->flags & MAVLINK_STATUS_FLAG_OUT_MAVLINK1) {
           // cope with extensions
           memset(MAVLINK_MSG_ID_THRUSTER_STATUS_MIN_LEN + (char *)&packet1, 0, sizeof(packet1)-MAVLINK_MSG_ID_THRUSTER_STATUS_MIN_LEN);
        }
#endif
        memset(&packet2, 0, sizeof(packet2));
    mavlink_msg_thruster_status_encode(system_id, component_id, &msg, &packet1);
    mavlink_msg_thruster_status_decode(&msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);

        memset(&packet2, 0, sizeof(packet2));
    mavlink_msg_thruster_status_pack(system_id, component_id, &msg , packet1.timestamp_ms , packet1.speed , packet1.power , packet1.temp , packet1.status , packet1.fault , packet1.lock );
    mavlink_msg_thruster_status_decode(&msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);

        memset(&packet2, 0, sizeof(packet2));
    mavlink_msg_thruster_status_pack_chan(system_id, component_id, MAVLINK_COMM_0, &msg , packet1.timestamp_ms , packet1.speed , packet1.power , packet1.temp , packet1.status , packet1.fault , packet1.lock );
    mavlink_msg_thruster_status_decode(&msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);

        memset(&packet2, 0, sizeof(packet2));
        mavlink_msg_to_send_buffer(buffer, &msg);
        for (i=0; i<mavlink_msg_get_send_buffer_length(&msg); i++) {
            comm_send_ch(MAVLINK_COMM_0, buffer[i]);
        }
    mavlink_msg_thruster_status_decode(last_msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);
        
        memset(&packet2, 0, sizeof(packet2));
    mavlink_msg_thruster_status_send(MAVLINK_COMM_1 , packet1.timestamp_ms , packet1.speed , packet1.power , packet1.temp , packet1.status , packet1.fault , packet1.lock );
    mavlink_msg_thruster_status_decode(last_msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);

#ifdef MAVLINK_HAVE_GET_MESSAGE_INFO
    MAVLINK_ASSERT(mavlink_get_message_info_by_name("THRUSTER_STATUS") != NULL);
    MAVLINK_ASSERT(mavlink_get_message_info_by_id(MAVLINK_MSG_ID_THRUSTER_STATUS) != NULL);
#endif
}

static void mavlink_test_gs_status(uint8_t system_id, uint8_t component_id, mavlink_message_t *last_msg)
{
#ifdef MAVLINK_STATUS_FLAG_OUT_MAVLINK1
    mavlink_status_t *status = mavlink_get_channel_status(MAVLINK_COMM_0);
        if ((status->flags & MAVLINK_STATUS_FLAG_OUT_MAVLINK1) && MAVLINK_MSG_ID_GS_STATUS >= 256) {
            return;
        }
#endif
    mavlink_message_t msg;
        uint8_t buffer[MAVLINK_MAX_PACKET_LEN];
        uint16_t i;
    mavlink_gs_status_t packet_in = {
        963497464,{ 45.0, 46.0 },{ 17859, 17860 },{ 18067, 18068 }
    };
    mavlink_gs_status_t packet1, packet2;
        memset(&packet1, 0, sizeof(packet1));
        packet1.timestamp_ms = packet_in.timestamp_ms;
        
        mav_array_memcpy(packet1.angle, packet_in.angle, sizeof(float)*2);
        mav_array_memcpy(packet1.step, packet_in.step, sizeof(int16_t)*2);
        mav_array_memcpy(packet1.res, packet_in.res, sizeof(int16_t)*2);
        
#ifdef MAVLINK_STATUS_FLAG_OUT_MAVLINK1
        if (status->flags & MAVLINK_STATUS_FLAG_OUT_MAVLINK1) {
           // cope with extensions
           memset(MAVLINK_MSG_ID_GS_STATUS_MIN_LEN + (char *)&packet1, 0, sizeof(packet1)-MAVLINK_MSG_ID_GS_STATUS_MIN_LEN);
        }
#endif
        memset(&packet2, 0, sizeof(packet2));
    mavlink_msg_gs_status_encode(system_id, component_id, &msg, &packet1);
    mavlink_msg_gs_status_decode(&msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);

        memset(&packet2, 0, sizeof(packet2));
    mavlink_msg_gs_status_pack(system_id, component_id, &msg , packet1.timestamp_ms , packet1.angle , packet1.step , packet1.res );
    mavlink_msg_gs_status_decode(&msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);

        memset(&packet2, 0, sizeof(packet2));
    mavlink_msg_gs_status_pack_chan(system_id, component_id, MAVLINK_COMM_0, &msg , packet1.timestamp_ms , packet1.angle , packet1.step , packet1.res );
    mavlink_msg_gs_status_decode(&msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);

        memset(&packet2, 0, sizeof(packet2));
        mavlink_msg_to_send_buffer(buffer, &msg);
        for (i=0; i<mavlink_msg_get_send_buffer_length(&msg); i++) {
            comm_send_ch(MAVLINK_COMM_0, buffer[i]);
        }
    mavlink_msg_gs_status_decode(last_msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);
        
        memset(&packet2, 0, sizeof(packet2));
    mavlink_msg_gs_status_send(MAVLINK_COMM_1 , packet1.timestamp_ms , packet1.angle , packet1.step , packet1.res );
    mavlink_msg_gs_status_decode(last_msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);

#ifdef MAVLINK_HAVE_GET_MESSAGE_INFO
    MAVLINK_ASSERT(mavlink_get_message_info_by_name("GS_STATUS") != NULL);
    MAVLINK_ASSERT(mavlink_get_message_info_by_id(MAVLINK_MSG_ID_GS_STATUS) != NULL);
#endif
}

static void mavlink_test_led_status(uint8_t system_id, uint8_t component_id, mavlink_message_t *last_msg)
{
#ifdef MAVLINK_STATUS_FLAG_OUT_MAVLINK1
    mavlink_status_t *status = mavlink_get_channel_status(MAVLINK_COMM_0);
        if ((status->flags & MAVLINK_STATUS_FLAG_OUT_MAVLINK1) && MAVLINK_MSG_ID_LED_STATUS >= 256) {
            return;
        }
#endif
    mavlink_message_t msg;
        uint8_t buffer[MAVLINK_MAX_PACKET_LEN];
        uint16_t i;
    mavlink_led_status_t packet_in = {
        963497464,17,84,151,218,29,96,163,230,41,108
    };
    mavlink_led_status_t packet1, packet2;
        memset(&packet1, 0, sizeof(packet1));
        packet1.timestamp_ms = packet_in.timestamp_ms;
        packet1.ledpwm1 = packet_in.ledpwm1;
        packet1.ledpwm2 = packet_in.ledpwm2;
        packet1.ledpwm3 = packet_in.ledpwm3;
        packet1.ledpwm4 = packet_in.ledpwm4;
        packet1.ledpwm5 = packet_in.ledpwm5;
        packet1.ledpwm6 = packet_in.ledpwm6;
        packet1.ledpwm7 = packet_in.ledpwm7;
        packet1.ledpwm8 = packet_in.ledpwm8;
        packet1.ledpwm9 = packet_in.ledpwm9;
        packet1.ledpwm10 = packet_in.ledpwm10;
        
        
#ifdef MAVLINK_STATUS_FLAG_OUT_MAVLINK1
        if (status->flags & MAVLINK_STATUS_FLAG_OUT_MAVLINK1) {
           // cope with extensions
           memset(MAVLINK_MSG_ID_LED_STATUS_MIN_LEN + (char *)&packet1, 0, sizeof(packet1)-MAVLINK_MSG_ID_LED_STATUS_MIN_LEN);
        }
#endif
        memset(&packet2, 0, sizeof(packet2));
    mavlink_msg_led_status_encode(system_id, component_id, &msg, &packet1);
    mavlink_msg_led_status_decode(&msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);

        memset(&packet2, 0, sizeof(packet2));
    mavlink_msg_led_status_pack(system_id, component_id, &msg , packet1.timestamp_ms , packet1.ledpwm1 , packet1.ledpwm2 , packet1.ledpwm3 , packet1.ledpwm4 , packet1.ledpwm5 , packet1.ledpwm6 , packet1.ledpwm7 , packet1.ledpwm8 , packet1.ledpwm9 , packet1.ledpwm10 );
    mavlink_msg_led_status_decode(&msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);

        memset(&packet2, 0, sizeof(packet2));
    mavlink_msg_led_status_pack_chan(system_id, component_id, MAVLINK_COMM_0, &msg , packet1.timestamp_ms , packet1.ledpwm1 , packet1.ledpwm2 , packet1.ledpwm3 , packet1.ledpwm4 , packet1.ledpwm5 , packet1.ledpwm6 , packet1.ledpwm7 , packet1.ledpwm8 , packet1.ledpwm9 , packet1.ledpwm10 );
    mavlink_msg_led_status_decode(&msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);

        memset(&packet2, 0, sizeof(packet2));
        mavlink_msg_to_send_buffer(buffer, &msg);
        for (i=0; i<mavlink_msg_get_send_buffer_length(&msg); i++) {
            comm_send_ch(MAVLINK_COMM_0, buffer[i]);
        }
    mavlink_msg_led_status_decode(last_msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);
        
        memset(&packet2, 0, sizeof(packet2));
    mavlink_msg_led_status_send(MAVLINK_COMM_1 , packet1.timestamp_ms , packet1.ledpwm1 , packet1.ledpwm2 , packet1.ledpwm3 , packet1.ledpwm4 , packet1.ledpwm5 , packet1.ledpwm6 , packet1.ledpwm7 , packet1.ledpwm8 , packet1.ledpwm9 , packet1.ledpwm10 );
    mavlink_msg_led_status_decode(last_msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);

#ifdef MAVLINK_HAVE_GET_MESSAGE_INFO
    MAVLINK_ASSERT(mavlink_get_message_info_by_name("LED_STATUS") != NULL);
    MAVLINK_ASSERT(mavlink_get_message_info_by_id(MAVLINK_MSG_ID_LED_STATUS) != NULL);
#endif
}

static void mavlink_test_vcheck(uint8_t system_id, uint8_t component_id, mavlink_message_t *last_msg)
{
#ifdef MAVLINK_STATUS_FLAG_OUT_MAVLINK1
    mavlink_status_t *status = mavlink_get_channel_status(MAVLINK_COMM_0);
        if ((status->flags & MAVLINK_STATUS_FLAG_OUT_MAVLINK1) && MAVLINK_MSG_ID_VCHECK >= 256) {
            return;
        }
#endif
    mavlink_message_t msg;
        uint8_t buffer[MAVLINK_MAX_PACKET_LEN];
        uint16_t i;
    mavlink_vcheck_t packet_in = {
        963497464,{ 17443, 17444, 17445, 17446 },{ 41, 42, 43, 44 }
    };
    mavlink_vcheck_t packet1, packet2;
        memset(&packet1, 0, sizeof(packet1));
        packet1.timestamp_ms = packet_in.timestamp_ms;
        
        mav_array_memcpy(packet1.temp, packet_in.temp, sizeof(int16_t)*4);
        mav_array_memcpy(packet1.v_status, packet_in.v_status, sizeof(uint8_t)*4);
        
#ifdef MAVLINK_STATUS_FLAG_OUT_MAVLINK1
        if (status->flags & MAVLINK_STATUS_FLAG_OUT_MAVLINK1) {
           // cope with extensions
           memset(MAVLINK_MSG_ID_VCHECK_MIN_LEN + (char *)&packet1, 0, sizeof(packet1)-MAVLINK_MSG_ID_VCHECK_MIN_LEN);
        }
#endif
        memset(&packet2, 0, sizeof(packet2));
    mavlink_msg_vcheck_encode(system_id, component_id, &msg, &packet1);
    mavlink_msg_vcheck_decode(&msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);

        memset(&packet2, 0, sizeof(packet2));
    mavlink_msg_vcheck_pack(system_id, component_id, &msg , packet1.timestamp_ms , packet1.v_status , packet1.temp );
    mavlink_msg_vcheck_decode(&msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);

        memset(&packet2, 0, sizeof(packet2));
    mavlink_msg_vcheck_pack_chan(system_id, component_id, MAVLINK_COMM_0, &msg , packet1.timestamp_ms , packet1.v_status , packet1.temp );
    mavlink_msg_vcheck_decode(&msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);

        memset(&packet2, 0, sizeof(packet2));
        mavlink_msg_to_send_buffer(buffer, &msg);
        for (i=0; i<mavlink_msg_get_send_buffer_length(&msg); i++) {
            comm_send_ch(MAVLINK_COMM_0, buffer[i]);
        }
    mavlink_msg_vcheck_decode(last_msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);
        
        memset(&packet2, 0, sizeof(packet2));
    mavlink_msg_vcheck_send(MAVLINK_COMM_1 , packet1.timestamp_ms , packet1.v_status , packet1.temp );
    mavlink_msg_vcheck_decode(last_msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);

#ifdef MAVLINK_HAVE_GET_MESSAGE_INFO
    MAVLINK_ASSERT(mavlink_get_message_info_by_name("VCHECK") != NULL);
    MAVLINK_ASSERT(mavlink_get_message_info_by_id(MAVLINK_MSG_ID_VCHECK) != NULL);
#endif
}

static void mavlink_test_height_status(uint8_t system_id, uint8_t component_id, mavlink_message_t *last_msg)
{
#ifdef MAVLINK_STATUS_FLAG_OUT_MAVLINK1
    mavlink_status_t *status = mavlink_get_channel_status(MAVLINK_COMM_0);
        if ((status->flags & MAVLINK_STATUS_FLAG_OUT_MAVLINK1) && MAVLINK_MSG_ID_HEIGHT_STATUS >= 256) {
            return;
        }
#endif
    mavlink_message_t msg;
        uint8_t buffer[MAVLINK_MAX_PACKET_LEN];
        uint16_t i;
    mavlink_height_status_t packet_in = {
        963497464,{ 17443, 17444, 17445, 17446, 17447 },{ 17963, 17964, 17965, 17966, 17967 },{ 18483, 18484, 18485, 18486, 18487 },{ 19003, 19004, 19005, 19006, 19007 },{ 19523, 19524, 19525, 19526, 19527 },{ 20043, 20044, 20045, 20046, 20047 }
    };
    mavlink_height_status_t packet1, packet2;
        memset(&packet1, 0, sizeof(packet1));
        packet1.timestamp_ms = packet_in.timestamp_ms;
        
        mav_array_memcpy(packet1.near_dist, packet_in.near_dist, sizeof(uint16_t)*5);
        mav_array_memcpy(packet1.near_stren, packet_in.near_stren, sizeof(uint16_t)*5);
        mav_array_memcpy(packet1.far_dist, packet_in.far_dist, sizeof(uint16_t)*5);
        mav_array_memcpy(packet1.far_stren, packet_in.far_stren, sizeof(uint16_t)*5);
        mav_array_memcpy(packet1.most_dist, packet_in.most_dist, sizeof(uint16_t)*5);
        mav_array_memcpy(packet1.most_stren, packet_in.most_stren, sizeof(uint16_t)*5);
        
#ifdef MAVLINK_STATUS_FLAG_OUT_MAVLINK1
        if (status->flags & MAVLINK_STATUS_FLAG_OUT_MAVLINK1) {
           // cope with extensions
           memset(MAVLINK_MSG_ID_HEIGHT_STATUS_MIN_LEN + (char *)&packet1, 0, sizeof(packet1)-MAVLINK_MSG_ID_HEIGHT_STATUS_MIN_LEN);
        }
#endif
        memset(&packet2, 0, sizeof(packet2));
    mavlink_msg_height_status_encode(system_id, component_id, &msg, &packet1);
    mavlink_msg_height_status_decode(&msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);

        memset(&packet2, 0, sizeof(packet2));
    mavlink_msg_height_status_pack(system_id, component_id, &msg , packet1.timestamp_ms , packet1.near_dist , packet1.near_stren , packet1.far_dist , packet1.far_stren , packet1.most_dist , packet1.most_stren );
    mavlink_msg_height_status_decode(&msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);

        memset(&packet2, 0, sizeof(packet2));
    mavlink_msg_height_status_pack_chan(system_id, component_id, MAVLINK_COMM_0, &msg , packet1.timestamp_ms , packet1.near_dist , packet1.near_stren , packet1.far_dist , packet1.far_stren , packet1.most_dist , packet1.most_stren );
    mavlink_msg_height_status_decode(&msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);

        memset(&packet2, 0, sizeof(packet2));
        mavlink_msg_to_send_buffer(buffer, &msg);
        for (i=0; i<mavlink_msg_get_send_buffer_length(&msg); i++) {
            comm_send_ch(MAVLINK_COMM_0, buffer[i]);
        }
    mavlink_msg_height_status_decode(last_msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);
        
        memset(&packet2, 0, sizeof(packet2));
    mavlink_msg_height_status_send(MAVLINK_COMM_1 , packet1.timestamp_ms , packet1.near_dist , packet1.near_stren , packet1.far_dist , packet1.far_stren , packet1.most_dist , packet1.most_stren );
    mavlink_msg_height_status_decode(last_msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);

#ifdef MAVLINK_HAVE_GET_MESSAGE_INFO
    MAVLINK_ASSERT(mavlink_get_message_info_by_name("HEIGHT_STATUS") != NULL);
    MAVLINK_ASSERT(mavlink_get_message_info_by_id(MAVLINK_MSG_ID_HEIGHT_STATUS) != NULL);
#endif
}

static void mavlink_test_depth_status(uint8_t system_id, uint8_t component_id, mavlink_message_t *last_msg)
{
#ifdef MAVLINK_STATUS_FLAG_OUT_MAVLINK1
    mavlink_status_t *status = mavlink_get_channel_status(MAVLINK_COMM_0);
        if ((status->flags & MAVLINK_STATUS_FLAG_OUT_MAVLINK1) && MAVLINK_MSG_ID_DEPTH_STATUS >= 256) {
            return;
        }
#endif
    mavlink_message_t msg;
        uint8_t buffer[MAVLINK_MAX_PACKET_LEN];
        uint16_t i;
    mavlink_depth_status_t packet_in = {
        963497464,{ 45.0, 46.0, 47.0, 48.0 },{ 157.0, 158.0, 159.0, 160.0 }
    };
    mavlink_depth_status_t packet1, packet2;
        memset(&packet1, 0, sizeof(packet1));
        packet1.timestamp_ms = packet_in.timestamp_ms;
        
        mav_array_memcpy(packet1.depth, packet_in.depth, sizeof(float)*4);
        mav_array_memcpy(packet1.temp, packet_in.temp, sizeof(float)*4);
        
#ifdef MAVLINK_STATUS_FLAG_OUT_MAVLINK1
        if (status->flags & MAVLINK_STATUS_FLAG_OUT_MAVLINK1) {
           // cope with extensions
           memset(MAVLINK_MSG_ID_DEPTH_STATUS_MIN_LEN + (char *)&packet1, 0, sizeof(packet1)-MAVLINK_MSG_ID_DEPTH_STATUS_MIN_LEN);
        }
#endif
        memset(&packet2, 0, sizeof(packet2));
    mavlink_msg_depth_status_encode(system_id, component_id, &msg, &packet1);
    mavlink_msg_depth_status_decode(&msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);

        memset(&packet2, 0, sizeof(packet2));
    mavlink_msg_depth_status_pack(system_id, component_id, &msg , packet1.timestamp_ms , packet1.depth , packet1.temp );
    mavlink_msg_depth_status_decode(&msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);

        memset(&packet2, 0, sizeof(packet2));
    mavlink_msg_depth_status_pack_chan(system_id, component_id, MAVLINK_COMM_0, &msg , packet1.timestamp_ms , packet1.depth , packet1.temp );
    mavlink_msg_depth_status_decode(&msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);

        memset(&packet2, 0, sizeof(packet2));
        mavlink_msg_to_send_buffer(buffer, &msg);
        for (i=0; i<mavlink_msg_get_send_buffer_length(&msg); i++) {
            comm_send_ch(MAVLINK_COMM_0, buffer[i]);
        }
    mavlink_msg_depth_status_decode(last_msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);
        
        memset(&packet2, 0, sizeof(packet2));
    mavlink_msg_depth_status_send(MAVLINK_COMM_1 , packet1.timestamp_ms , packet1.depth , packet1.temp );
    mavlink_msg_depth_status_decode(last_msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);

#ifdef MAVLINK_HAVE_GET_MESSAGE_INFO
    MAVLINK_ASSERT(mavlink_get_message_info_by_name("DEPTH_STATUS") != NULL);
    MAVLINK_ASSERT(mavlink_get_message_info_by_id(MAVLINK_MSG_ID_DEPTH_STATUS) != NULL);
#endif
}

static void mavlink_test_bem280(uint8_t system_id, uint8_t component_id, mavlink_message_t *last_msg)
{
#ifdef MAVLINK_STATUS_FLAG_OUT_MAVLINK1
    mavlink_status_t *status = mavlink_get_channel_status(MAVLINK_COMM_0);
        if ((status->flags & MAVLINK_STATUS_FLAG_OUT_MAVLINK1) && MAVLINK_MSG_ID_BEM280 >= 256) {
            return;
        }
#endif
    mavlink_message_t msg;
        uint8_t buffer[MAVLINK_MAX_PACKET_LEN];
        uint16_t i;
    mavlink_bem280_t packet_in = {
        963497464,45.0,73.0,101.0
    };
    mavlink_bem280_t packet1, packet2;
        memset(&packet1, 0, sizeof(packet1));
        packet1.timestamp_ms = packet_in.timestamp_ms;
        packet1.temp = packet_in.temp;
        packet1.humi = packet_in.humi;
        packet1.press = packet_in.press;
        
        
#ifdef MAVLINK_STATUS_FLAG_OUT_MAVLINK1
        if (status->flags & MAVLINK_STATUS_FLAG_OUT_MAVLINK1) {
           // cope with extensions
           memset(MAVLINK_MSG_ID_BEM280_MIN_LEN + (char *)&packet1, 0, sizeof(packet1)-MAVLINK_MSG_ID_BEM280_MIN_LEN);
        }
#endif
        memset(&packet2, 0, sizeof(packet2));
    mavlink_msg_bem280_encode(system_id, component_id, &msg, &packet1);
    mavlink_msg_bem280_decode(&msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);

        memset(&packet2, 0, sizeof(packet2));
    mavlink_msg_bem280_pack(system_id, component_id, &msg , packet1.timestamp_ms , packet1.temp , packet1.humi , packet1.press );
    mavlink_msg_bem280_decode(&msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);

        memset(&packet2, 0, sizeof(packet2));
    mavlink_msg_bem280_pack_chan(system_id, component_id, MAVLINK_COMM_0, &msg , packet1.timestamp_ms , packet1.temp , packet1.humi , packet1.press );
    mavlink_msg_bem280_decode(&msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);

        memset(&packet2, 0, sizeof(packet2));
        mavlink_msg_to_send_buffer(buffer, &msg);
        for (i=0; i<mavlink_msg_get_send_buffer_length(&msg); i++) {
            comm_send_ch(MAVLINK_COMM_0, buffer[i]);
        }
    mavlink_msg_bem280_decode(last_msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);
        
        memset(&packet2, 0, sizeof(packet2));
    mavlink_msg_bem280_send(MAVLINK_COMM_1 , packet1.timestamp_ms , packet1.temp , packet1.humi , packet1.press );
    mavlink_msg_bem280_decode(last_msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);

#ifdef MAVLINK_HAVE_GET_MESSAGE_INFO
    MAVLINK_ASSERT(mavlink_get_message_info_by_name("BEM280") != NULL);
    MAVLINK_ASSERT(mavlink_get_message_info_by_id(MAVLINK_MSG_ID_BEM280) != NULL);
#endif
}

static void mavlink_test_switch_status(uint8_t system_id, uint8_t component_id, mavlink_message_t *last_msg)
{
#ifdef MAVLINK_STATUS_FLAG_OUT_MAVLINK1
    mavlink_status_t *status = mavlink_get_channel_status(MAVLINK_COMM_0);
        if ((status->flags & MAVLINK_STATUS_FLAG_OUT_MAVLINK1) && MAVLINK_MSG_ID_SWITCH_STATUS >= 256) {
            return;
        }
#endif
    mavlink_message_t msg;
        uint8_t buffer[MAVLINK_MAX_PACKET_LEN];
        uint16_t i;
    mavlink_switch_status_t packet_in = {
        963497464,{ 17, 18, 19, 20, 21, 22, 23, 24 }
    };
    mavlink_switch_status_t packet1, packet2;
        memset(&packet1, 0, sizeof(packet1));
        packet1.timestamp_ms = packet_in.timestamp_ms;
        
        mav_array_memcpy(packet1.switchs, packet_in.switchs, sizeof(uint8_t)*8);
        
#ifdef MAVLINK_STATUS_FLAG_OUT_MAVLINK1
        if (status->flags & MAVLINK_STATUS_FLAG_OUT_MAVLINK1) {
           // cope with extensions
           memset(MAVLINK_MSG_ID_SWITCH_STATUS_MIN_LEN + (char *)&packet1, 0, sizeof(packet1)-MAVLINK_MSG_ID_SWITCH_STATUS_MIN_LEN);
        }
#endif
        memset(&packet2, 0, sizeof(packet2));
    mavlink_msg_switch_status_encode(system_id, component_id, &msg, &packet1);
    mavlink_msg_switch_status_decode(&msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);

        memset(&packet2, 0, sizeof(packet2));
    mavlink_msg_switch_status_pack(system_id, component_id, &msg , packet1.timestamp_ms , packet1.switchs );
    mavlink_msg_switch_status_decode(&msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);

        memset(&packet2, 0, sizeof(packet2));
    mavlink_msg_switch_status_pack_chan(system_id, component_id, MAVLINK_COMM_0, &msg , packet1.timestamp_ms , packet1.switchs );
    mavlink_msg_switch_status_decode(&msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);

        memset(&packet2, 0, sizeof(packet2));
        mavlink_msg_to_send_buffer(buffer, &msg);
        for (i=0; i<mavlink_msg_get_send_buffer_length(&msg); i++) {
            comm_send_ch(MAVLINK_COMM_0, buffer[i]);
        }
    mavlink_msg_switch_status_decode(last_msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);
        
        memset(&packet2, 0, sizeof(packet2));
    mavlink_msg_switch_status_send(MAVLINK_COMM_1 , packet1.timestamp_ms , packet1.switchs );
    mavlink_msg_switch_status_decode(last_msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);

#ifdef MAVLINK_HAVE_GET_MESSAGE_INFO
    MAVLINK_ASSERT(mavlink_get_message_info_by_name("SWITCH_STATUS") != NULL);
    MAVLINK_ASSERT(mavlink_get_message_info_by_id(MAVLINK_MSG_ID_SWITCH_STATUS) != NULL);
#endif
}

static void mavlink_test_thruster_cmd(uint8_t system_id, uint8_t component_id, mavlink_message_t *last_msg)
{
#ifdef MAVLINK_STATUS_FLAG_OUT_MAVLINK1
    mavlink_status_t *status = mavlink_get_channel_status(MAVLINK_COMM_0);
        if ((status->flags & MAVLINK_STATUS_FLAG_OUT_MAVLINK1) && MAVLINK_MSG_ID_THRUSTER_CMD >= 256) {
            return;
        }
#endif
    mavlink_message_t msg;
        uint8_t buffer[MAVLINK_MAX_PACKET_LEN];
        uint16_t i;
    mavlink_thruster_cmd_t packet_in = {
        { 17235, 17236, 17237, 17238, 17239, 17240, 17241, 17242, 17243, 17244, 17245, 17246 }
    };
    mavlink_thruster_cmd_t packet1, packet2;
        memset(&packet1, 0, sizeof(packet1));
        
        mav_array_memcpy(packet1.speed, packet_in.speed, sizeof(uint16_t)*12);
        
#ifdef MAVLINK_STATUS_FLAG_OUT_MAVLINK1
        if (status->flags & MAVLINK_STATUS_FLAG_OUT_MAVLINK1) {
           // cope with extensions
           memset(MAVLINK_MSG_ID_THRUSTER_CMD_MIN_LEN + (char *)&packet1, 0, sizeof(packet1)-MAVLINK_MSG_ID_THRUSTER_CMD_MIN_LEN);
        }
#endif
        memset(&packet2, 0, sizeof(packet2));
    mavlink_msg_thruster_cmd_encode(system_id, component_id, &msg, &packet1);
    mavlink_msg_thruster_cmd_decode(&msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);

        memset(&packet2, 0, sizeof(packet2));
    mavlink_msg_thruster_cmd_pack(system_id, component_id, &msg , packet1.speed );
    mavlink_msg_thruster_cmd_decode(&msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);

        memset(&packet2, 0, sizeof(packet2));
    mavlink_msg_thruster_cmd_pack_chan(system_id, component_id, MAVLINK_COMM_0, &msg , packet1.speed );
    mavlink_msg_thruster_cmd_decode(&msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);

        memset(&packet2, 0, sizeof(packet2));
        mavlink_msg_to_send_buffer(buffer, &msg);
        for (i=0; i<mavlink_msg_get_send_buffer_length(&msg); i++) {
            comm_send_ch(MAVLINK_COMM_0, buffer[i]);
        }
    mavlink_msg_thruster_cmd_decode(last_msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);
        
        memset(&packet2, 0, sizeof(packet2));
    mavlink_msg_thruster_cmd_send(MAVLINK_COMM_1 , packet1.speed );
    mavlink_msg_thruster_cmd_decode(last_msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);

#ifdef MAVLINK_HAVE_GET_MESSAGE_INFO
    MAVLINK_ASSERT(mavlink_get_message_info_by_name("THRUSTER_CMD") != NULL);
    MAVLINK_ASSERT(mavlink_get_message_info_by_id(MAVLINK_MSG_ID_THRUSTER_CMD) != NULL);
#endif
}

static void mavlink_test_thruster_lock(uint8_t system_id, uint8_t component_id, mavlink_message_t *last_msg)
{
#ifdef MAVLINK_STATUS_FLAG_OUT_MAVLINK1
    mavlink_status_t *status = mavlink_get_channel_status(MAVLINK_COMM_0);
        if ((status->flags & MAVLINK_STATUS_FLAG_OUT_MAVLINK1) && MAVLINK_MSG_ID_THRUSTER_LOCK >= 256) {
            return;
        }
#endif
    mavlink_message_t msg;
        uint8_t buffer[MAVLINK_MAX_PACKET_LEN];
        uint16_t i;
    mavlink_thruster_lock_t packet_in = {
        5
    };
    mavlink_thruster_lock_t packet1, packet2;
        memset(&packet1, 0, sizeof(packet1));
        packet1.lock = packet_in.lock;
        
        
#ifdef MAVLINK_STATUS_FLAG_OUT_MAVLINK1
        if (status->flags & MAVLINK_STATUS_FLAG_OUT_MAVLINK1) {
           // cope with extensions
           memset(MAVLINK_MSG_ID_THRUSTER_LOCK_MIN_LEN + (char *)&packet1, 0, sizeof(packet1)-MAVLINK_MSG_ID_THRUSTER_LOCK_MIN_LEN);
        }
#endif
        memset(&packet2, 0, sizeof(packet2));
    mavlink_msg_thruster_lock_encode(system_id, component_id, &msg, &packet1);
    mavlink_msg_thruster_lock_decode(&msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);

        memset(&packet2, 0, sizeof(packet2));
    mavlink_msg_thruster_lock_pack(system_id, component_id, &msg , packet1.lock );
    mavlink_msg_thruster_lock_decode(&msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);

        memset(&packet2, 0, sizeof(packet2));
    mavlink_msg_thruster_lock_pack_chan(system_id, component_id, MAVLINK_COMM_0, &msg , packet1.lock );
    mavlink_msg_thruster_lock_decode(&msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);

        memset(&packet2, 0, sizeof(packet2));
        mavlink_msg_to_send_buffer(buffer, &msg);
        for (i=0; i<mavlink_msg_get_send_buffer_length(&msg); i++) {
            comm_send_ch(MAVLINK_COMM_0, buffer[i]);
        }
    mavlink_msg_thruster_lock_decode(last_msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);
        
        memset(&packet2, 0, sizeof(packet2));
    mavlink_msg_thruster_lock_send(MAVLINK_COMM_1 , packet1.lock );
    mavlink_msg_thruster_lock_decode(last_msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);

#ifdef MAVLINK_HAVE_GET_MESSAGE_INFO
    MAVLINK_ASSERT(mavlink_get_message_info_by_name("THRUSTER_LOCK") != NULL);
    MAVLINK_ASSERT(mavlink_get_message_info_by_id(MAVLINK_MSG_ID_THRUSTER_LOCK) != NULL);
#endif
}

static void mavlink_test_imu_calib(uint8_t system_id, uint8_t component_id, mavlink_message_t *last_msg)
{
#ifdef MAVLINK_STATUS_FLAG_OUT_MAVLINK1
    mavlink_status_t *status = mavlink_get_channel_status(MAVLINK_COMM_0);
        if ((status->flags & MAVLINK_STATUS_FLAG_OUT_MAVLINK1) && MAVLINK_MSG_ID_IMU_CALIB >= 256) {
            return;
        }
#endif
    mavlink_message_t msg;
        uint8_t buffer[MAVLINK_MAX_PACKET_LEN];
        uint16_t i;
    mavlink_imu_calib_t packet_in = {
        123.0,179.0,129.0
    };
    mavlink_imu_calib_t packet1, packet2;
        memset(&packet1, 0, sizeof(packet1));
        packet1.lon = packet_in.lon;
        packet1.lat = packet_in.lat;
        packet1.alt = packet_in.alt;
        
        
#ifdef MAVLINK_STATUS_FLAG_OUT_MAVLINK1
        if (status->flags & MAVLINK_STATUS_FLAG_OUT_MAVLINK1) {
           // cope with extensions
           memset(MAVLINK_MSG_ID_IMU_CALIB_MIN_LEN + (char *)&packet1, 0, sizeof(packet1)-MAVLINK_MSG_ID_IMU_CALIB_MIN_LEN);
        }
#endif
        memset(&packet2, 0, sizeof(packet2));
    mavlink_msg_imu_calib_encode(system_id, component_id, &msg, &packet1);
    mavlink_msg_imu_calib_decode(&msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);

        memset(&packet2, 0, sizeof(packet2));
    mavlink_msg_imu_calib_pack(system_id, component_id, &msg , packet1.lon , packet1.lat , packet1.alt );
    mavlink_msg_imu_calib_decode(&msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);

        memset(&packet2, 0, sizeof(packet2));
    mavlink_msg_imu_calib_pack_chan(system_id, component_id, MAVLINK_COMM_0, &msg , packet1.lon , packet1.lat , packet1.alt );
    mavlink_msg_imu_calib_decode(&msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);

        memset(&packet2, 0, sizeof(packet2));
        mavlink_msg_to_send_buffer(buffer, &msg);
        for (i=0; i<mavlink_msg_get_send_buffer_length(&msg); i++) {
            comm_send_ch(MAVLINK_COMM_0, buffer[i]);
        }
    mavlink_msg_imu_calib_decode(last_msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);
        
        memset(&packet2, 0, sizeof(packet2));
    mavlink_msg_imu_calib_send(MAVLINK_COMM_1 , packet1.lon , packet1.lat , packet1.alt );
    mavlink_msg_imu_calib_decode(last_msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);

#ifdef MAVLINK_HAVE_GET_MESSAGE_INFO
    MAVLINK_ASSERT(mavlink_get_message_info_by_name("IMU_CALIB") != NULL);
    MAVLINK_ASSERT(mavlink_get_message_info_by_id(MAVLINK_MSG_ID_IMU_CALIB) != NULL);
#endif
}

static void mavlink_test_imu_clear(uint8_t system_id, uint8_t component_id, mavlink_message_t *last_msg)
{
#ifdef MAVLINK_STATUS_FLAG_OUT_MAVLINK1
    mavlink_status_t *status = mavlink_get_channel_status(MAVLINK_COMM_0);
        if ((status->flags & MAVLINK_STATUS_FLAG_OUT_MAVLINK1) && MAVLINK_MSG_ID_IMU_CLEAR >= 256) {
            return;
        }
#endif
    mavlink_message_t msg;
        uint8_t buffer[MAVLINK_MAX_PACKET_LEN];
        uint16_t i;
    mavlink_imu_clear_t packet_in = {
        5
    };
    mavlink_imu_clear_t packet1, packet2;
        memset(&packet1, 0, sizeof(packet1));
        packet1.clear = packet_in.clear;
        
        
#ifdef MAVLINK_STATUS_FLAG_OUT_MAVLINK1
        if (status->flags & MAVLINK_STATUS_FLAG_OUT_MAVLINK1) {
           // cope with extensions
           memset(MAVLINK_MSG_ID_IMU_CLEAR_MIN_LEN + (char *)&packet1, 0, sizeof(packet1)-MAVLINK_MSG_ID_IMU_CLEAR_MIN_LEN);
        }
#endif
        memset(&packet2, 0, sizeof(packet2));
    mavlink_msg_imu_clear_encode(system_id, component_id, &msg, &packet1);
    mavlink_msg_imu_clear_decode(&msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);

        memset(&packet2, 0, sizeof(packet2));
    mavlink_msg_imu_clear_pack(system_id, component_id, &msg , packet1.clear );
    mavlink_msg_imu_clear_decode(&msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);

        memset(&packet2, 0, sizeof(packet2));
    mavlink_msg_imu_clear_pack_chan(system_id, component_id, MAVLINK_COMM_0, &msg , packet1.clear );
    mavlink_msg_imu_clear_decode(&msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);

        memset(&packet2, 0, sizeof(packet2));
        mavlink_msg_to_send_buffer(buffer, &msg);
        for (i=0; i<mavlink_msg_get_send_buffer_length(&msg); i++) {
            comm_send_ch(MAVLINK_COMM_0, buffer[i]);
        }
    mavlink_msg_imu_clear_decode(last_msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);
        
        memset(&packet2, 0, sizeof(packet2));
    mavlink_msg_imu_clear_send(MAVLINK_COMM_1 , packet1.clear );
    mavlink_msg_imu_clear_decode(last_msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);

#ifdef MAVLINK_HAVE_GET_MESSAGE_INFO
    MAVLINK_ASSERT(mavlink_get_message_info_by_name("IMU_CLEAR") != NULL);
    MAVLINK_ASSERT(mavlink_get_message_info_by_id(MAVLINK_MSG_ID_IMU_CLEAR) != NULL);
#endif
}

static void mavlink_test_led_cmd(uint8_t system_id, uint8_t component_id, mavlink_message_t *last_msg)
{
#ifdef MAVLINK_STATUS_FLAG_OUT_MAVLINK1
    mavlink_status_t *status = mavlink_get_channel_status(MAVLINK_COMM_0);
        if ((status->flags & MAVLINK_STATUS_FLAG_OUT_MAVLINK1) && MAVLINK_MSG_ID_LED_CMD >= 256) {
            return;
        }
#endif
    mavlink_message_t msg;
        uint8_t buffer[MAVLINK_MAX_PACKET_LEN];
        uint16_t i;
    mavlink_led_cmd_t packet_in = {
        5,72
    };
    mavlink_led_cmd_t packet1, packet2;
        memset(&packet1, 0, sizeof(packet1));
        packet1.index = packet_in.index;
        packet1.pwm = packet_in.pwm;
        
        
#ifdef MAVLINK_STATUS_FLAG_OUT_MAVLINK1
        if (status->flags & MAVLINK_STATUS_FLAG_OUT_MAVLINK1) {
           // cope with extensions
           memset(MAVLINK_MSG_ID_LED_CMD_MIN_LEN + (char *)&packet1, 0, sizeof(packet1)-MAVLINK_MSG_ID_LED_CMD_MIN_LEN);
        }
#endif
        memset(&packet2, 0, sizeof(packet2));
    mavlink_msg_led_cmd_encode(system_id, component_id, &msg, &packet1);
    mavlink_msg_led_cmd_decode(&msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);

        memset(&packet2, 0, sizeof(packet2));
    mavlink_msg_led_cmd_pack(system_id, component_id, &msg , packet1.index , packet1.pwm );
    mavlink_msg_led_cmd_decode(&msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);

        memset(&packet2, 0, sizeof(packet2));
    mavlink_msg_led_cmd_pack_chan(system_id, component_id, MAVLINK_COMM_0, &msg , packet1.index , packet1.pwm );
    mavlink_msg_led_cmd_decode(&msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);

        memset(&packet2, 0, sizeof(packet2));
        mavlink_msg_to_send_buffer(buffer, &msg);
        for (i=0; i<mavlink_msg_get_send_buffer_length(&msg); i++) {
            comm_send_ch(MAVLINK_COMM_0, buffer[i]);
        }
    mavlink_msg_led_cmd_decode(last_msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);
        
        memset(&packet2, 0, sizeof(packet2));
    mavlink_msg_led_cmd_send(MAVLINK_COMM_1 , packet1.index , packet1.pwm );
    mavlink_msg_led_cmd_decode(last_msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);

#ifdef MAVLINK_HAVE_GET_MESSAGE_INFO
    MAVLINK_ASSERT(mavlink_get_message_info_by_name("LED_CMD") != NULL);
    MAVLINK_ASSERT(mavlink_get_message_info_by_id(MAVLINK_MSG_ID_LED_CMD) != NULL);
#endif
}

static void mavlink_test_gs_cmd(uint8_t system_id, uint8_t component_id, mavlink_message_t *last_msg)
{
#ifdef MAVLINK_STATUS_FLAG_OUT_MAVLINK1
    mavlink_status_t *status = mavlink_get_channel_status(MAVLINK_COMM_0);
        if ((status->flags & MAVLINK_STATUS_FLAG_OUT_MAVLINK1) && MAVLINK_MSG_ID_GS_CMD >= 256) {
            return;
        }
#endif
    mavlink_message_t msg;
        uint8_t buffer[MAVLINK_MAX_PACKET_LEN];
        uint16_t i;
    mavlink_gs_cmd_t packet_in = {
        17.0,17
    };
    mavlink_gs_cmd_t packet1, packet2;
        memset(&packet1, 0, sizeof(packet1));
        packet1.angle = packet_in.angle;
        packet1.index = packet_in.index;
        
        
#ifdef MAVLINK_STATUS_FLAG_OUT_MAVLINK1
        if (status->flags & MAVLINK_STATUS_FLAG_OUT_MAVLINK1) {
           // cope with extensions
           memset(MAVLINK_MSG_ID_GS_CMD_MIN_LEN + (char *)&packet1, 0, sizeof(packet1)-MAVLINK_MSG_ID_GS_CMD_MIN_LEN);
        }
#endif
        memset(&packet2, 0, sizeof(packet2));
    mavlink_msg_gs_cmd_encode(system_id, component_id, &msg, &packet1);
    mavlink_msg_gs_cmd_decode(&msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);

        memset(&packet2, 0, sizeof(packet2));
    mavlink_msg_gs_cmd_pack(system_id, component_id, &msg , packet1.index , packet1.angle );
    mavlink_msg_gs_cmd_decode(&msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);

        memset(&packet2, 0, sizeof(packet2));
    mavlink_msg_gs_cmd_pack_chan(system_id, component_id, MAVLINK_COMM_0, &msg , packet1.index , packet1.angle );
    mavlink_msg_gs_cmd_decode(&msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);

        memset(&packet2, 0, sizeof(packet2));
        mavlink_msg_to_send_buffer(buffer, &msg);
        for (i=0; i<mavlink_msg_get_send_buffer_length(&msg); i++) {
            comm_send_ch(MAVLINK_COMM_0, buffer[i]);
        }
    mavlink_msg_gs_cmd_decode(last_msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);
        
        memset(&packet2, 0, sizeof(packet2));
    mavlink_msg_gs_cmd_send(MAVLINK_COMM_1 , packet1.index , packet1.angle );
    mavlink_msg_gs_cmd_decode(last_msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);

#ifdef MAVLINK_HAVE_GET_MESSAGE_INFO
    MAVLINK_ASSERT(mavlink_get_message_info_by_name("GS_CMD") != NULL);
    MAVLINK_ASSERT(mavlink_get_message_info_by_id(MAVLINK_MSG_ID_GS_CMD) != NULL);
#endif
}

static void mavlink_test_gs_cfg(uint8_t system_id, uint8_t component_id, mavlink_message_t *last_msg)
{
#ifdef MAVLINK_STATUS_FLAG_OUT_MAVLINK1
    mavlink_status_t *status = mavlink_get_channel_status(MAVLINK_COMM_0);
        if ((status->flags & MAVLINK_STATUS_FLAG_OUT_MAVLINK1) && MAVLINK_MSG_ID_GS_CFG >= 256) {
            return;
        }
#endif
    mavlink_message_t msg;
        uint8_t buffer[MAVLINK_MAX_PACKET_LEN];
        uint16_t i;
    mavlink_gs_cfg_t packet_in = {
        { 17.0, 18.0 },{ 73.0, 74.0 },{ 18067, 18068 }
    };
    mavlink_gs_cfg_t packet1, packet2;
        memset(&packet1, 0, sizeof(packet1));
        
        mav_array_memcpy(packet1.max_angle, packet_in.max_angle, sizeof(float)*2);
        mav_array_memcpy(packet1.min_angle, packet_in.min_angle, sizeof(float)*2);
        mav_array_memcpy(packet1.step, packet_in.step, sizeof(uint16_t)*2);
        
#ifdef MAVLINK_STATUS_FLAG_OUT_MAVLINK1
        if (status->flags & MAVLINK_STATUS_FLAG_OUT_MAVLINK1) {
           // cope with extensions
           memset(MAVLINK_MSG_ID_GS_CFG_MIN_LEN + (char *)&packet1, 0, sizeof(packet1)-MAVLINK_MSG_ID_GS_CFG_MIN_LEN);
        }
#endif
        memset(&packet2, 0, sizeof(packet2));
    mavlink_msg_gs_cfg_encode(system_id, component_id, &msg, &packet1);
    mavlink_msg_gs_cfg_decode(&msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);

        memset(&packet2, 0, sizeof(packet2));
    mavlink_msg_gs_cfg_pack(system_id, component_id, &msg , packet1.max_angle , packet1.min_angle , packet1.step );
    mavlink_msg_gs_cfg_decode(&msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);

        memset(&packet2, 0, sizeof(packet2));
    mavlink_msg_gs_cfg_pack_chan(system_id, component_id, MAVLINK_COMM_0, &msg , packet1.max_angle , packet1.min_angle , packet1.step );
    mavlink_msg_gs_cfg_decode(&msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);

        memset(&packet2, 0, sizeof(packet2));
        mavlink_msg_to_send_buffer(buffer, &msg);
        for (i=0; i<mavlink_msg_get_send_buffer_length(&msg); i++) {
            comm_send_ch(MAVLINK_COMM_0, buffer[i]);
        }
    mavlink_msg_gs_cfg_decode(last_msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);
        
        memset(&packet2, 0, sizeof(packet2));
    mavlink_msg_gs_cfg_send(MAVLINK_COMM_1 , packet1.max_angle , packet1.min_angle , packet1.step );
    mavlink_msg_gs_cfg_decode(last_msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);

#ifdef MAVLINK_HAVE_GET_MESSAGE_INFO
    MAVLINK_ASSERT(mavlink_get_message_info_by_name("GS_CFG") != NULL);
    MAVLINK_ASSERT(mavlink_get_message_info_by_id(MAVLINK_MSG_ID_GS_CFG) != NULL);
#endif
}

static void mavlink_test_switch_cmd(uint8_t system_id, uint8_t component_id, mavlink_message_t *last_msg)
{
#ifdef MAVLINK_STATUS_FLAG_OUT_MAVLINK1
    mavlink_status_t *status = mavlink_get_channel_status(MAVLINK_COMM_0);
        if ((status->flags & MAVLINK_STATUS_FLAG_OUT_MAVLINK1) && MAVLINK_MSG_ID_SWITCH_CMD >= 256) {
            return;
        }
#endif
    mavlink_message_t msg;
        uint8_t buffer[MAVLINK_MAX_PACKET_LEN];
        uint16_t i;
    mavlink_switch_cmd_t packet_in = {
        5,72
    };
    mavlink_switch_cmd_t packet1, packet2;
        memset(&packet1, 0, sizeof(packet1));
        packet1.index = packet_in.index;
        packet1.value = packet_in.value;
        
        
#ifdef MAVLINK_STATUS_FLAG_OUT_MAVLINK1
        if (status->flags & MAVLINK_STATUS_FLAG_OUT_MAVLINK1) {
           // cope with extensions
           memset(MAVLINK_MSG_ID_SWITCH_CMD_MIN_LEN + (char *)&packet1, 0, sizeof(packet1)-MAVLINK_MSG_ID_SWITCH_CMD_MIN_LEN);
        }
#endif
        memset(&packet2, 0, sizeof(packet2));
    mavlink_msg_switch_cmd_encode(system_id, component_id, &msg, &packet1);
    mavlink_msg_switch_cmd_decode(&msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);

        memset(&packet2, 0, sizeof(packet2));
    mavlink_msg_switch_cmd_pack(system_id, component_id, &msg , packet1.index , packet1.value );
    mavlink_msg_switch_cmd_decode(&msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);

        memset(&packet2, 0, sizeof(packet2));
    mavlink_msg_switch_cmd_pack_chan(system_id, component_id, MAVLINK_COMM_0, &msg , packet1.index , packet1.value );
    mavlink_msg_switch_cmd_decode(&msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);

        memset(&packet2, 0, sizeof(packet2));
        mavlink_msg_to_send_buffer(buffer, &msg);
        for (i=0; i<mavlink_msg_get_send_buffer_length(&msg); i++) {
            comm_send_ch(MAVLINK_COMM_0, buffer[i]);
        }
    mavlink_msg_switch_cmd_decode(last_msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);
        
        memset(&packet2, 0, sizeof(packet2));
    mavlink_msg_switch_cmd_send(MAVLINK_COMM_1 , packet1.index , packet1.value );
    mavlink_msg_switch_cmd_decode(last_msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);

#ifdef MAVLINK_HAVE_GET_MESSAGE_INFO
    MAVLINK_ASSERT(mavlink_get_message_info_by_name("SWITCH_CMD") != NULL);
    MAVLINK_ASSERT(mavlink_get_message_info_by_id(MAVLINK_MSG_ID_SWITCH_CMD) != NULL);
#endif
}

static void mavlink_test_dvl_data(uint8_t system_id, uint8_t component_id, mavlink_message_t *last_msg)
{
#ifdef MAVLINK_STATUS_FLAG_OUT_MAVLINK1
    mavlink_status_t *status = mavlink_get_channel_status(MAVLINK_COMM_0);
        if ((status->flags & MAVLINK_STATUS_FLAG_OUT_MAVLINK1) && MAVLINK_MSG_ID_DVL_DATA >= 256) {
            return;
        }
#endif
    mavlink_message_t msg;
        uint8_t buffer[MAVLINK_MAX_PACKET_LEN];
        uint16_t i;
    mavlink_dvl_data_t packet_in = {
        963497464,{ 45.0, 46.0, 47.0, 48.0 },{ 157.0, 158.0, 159.0, 160.0 },269.0,{ 297.0, 298.0, 299.0, 300.0 },{ 409.0, 410.0, 411.0, 412.0 },{ 521.0, 522.0, 523.0, 524.0 },{ 633.0, 634.0, 635.0, 636.0 },{ 745.0, 746.0, 747.0, 748.0 },{ 857.0, 858.0, 859.0, 860.0 },{ 969.0, 970.0, 971.0, 972.0 },{ 1081.0, 1082.0, 1083.0, 1084.0 },{ 1193.0, 1194.0, 1195.0, 1196.0 },{ 1305.0, 1306.0, 1307.0, 1308.0 },{ 93, 94, 95, 96 },{ 105, 106, 107, 108 },{ 117, 118, 119, 120 },{ 129, 130, 131, 132 },{ 141, 142, 143, 144 },{ 153, 154, 155, 156 },{ 165, 166, 167, 168 },{ 177, 178, 179, 180 },{ 189, 190, 191, 192 },{ 201, 202, 203, 204 },{ 213, 214, 215, 216 }
    };
    mavlink_dvl_data_t packet1, packet2;
        memset(&packet1, 0, sizeof(packet1));
        packet1.timestamp_ms = packet_in.timestamp_ms;
        packet1.BT_max_depth = packet_in.BT_max_depth;
        
        mav_array_memcpy(packet1.BT_range, packet_in.BT_range, sizeof(float)*4);
        mav_array_memcpy(packet1.BT_vel, packet_in.BT_vel, sizeof(float)*4);
        mav_array_memcpy(packet1.WP_Cell1_vel, packet_in.WP_Cell1_vel, sizeof(float)*4);
        mav_array_memcpy(packet1.WP_Cell2_vel, packet_in.WP_Cell2_vel, sizeof(float)*4);
        mav_array_memcpy(packet1.WP_Cell3_vel, packet_in.WP_Cell3_vel, sizeof(float)*4);
        mav_array_memcpy(packet1.WP_Cell4_vel, packet_in.WP_Cell4_vel, sizeof(float)*4);
        mav_array_memcpy(packet1.WP_Cell5_vel, packet_in.WP_Cell5_vel, sizeof(float)*4);
        mav_array_memcpy(packet1.WP_Cell6_vel, packet_in.WP_Cell6_vel, sizeof(float)*4);
        mav_array_memcpy(packet1.WP_Cell7_vel, packet_in.WP_Cell7_vel, sizeof(float)*4);
        mav_array_memcpy(packet1.WP_Cell8_vel, packet_in.WP_Cell8_vel, sizeof(float)*4);
        mav_array_memcpy(packet1.WP_Cell9_vel, packet_in.WP_Cell9_vel, sizeof(float)*4);
        mav_array_memcpy(packet1.WP_Cell10_vel, packet_in.WP_Cell10_vel, sizeof(float)*4);
        mav_array_memcpy(packet1.BT_percent_good, packet_in.BT_percent_good, sizeof(uint8_t)*4);
        mav_array_memcpy(packet1.WP_Cell1_percent_good, packet_in.WP_Cell1_percent_good, sizeof(uint8_t)*4);
        mav_array_memcpy(packet1.WP_Cell2_percent_good, packet_in.WP_Cell2_percent_good, sizeof(uint8_t)*4);
        mav_array_memcpy(packet1.WP_Cell3_percent_good, packet_in.WP_Cell3_percent_good, sizeof(uint8_t)*4);
        mav_array_memcpy(packet1.WP_Cell4_percent_good, packet_in.WP_Cell4_percent_good, sizeof(uint8_t)*4);
        mav_array_memcpy(packet1.WP_Cell5_percent_good, packet_in.WP_Cell5_percent_good, sizeof(uint8_t)*4);
        mav_array_memcpy(packet1.WP_Cell6_percent_good, packet_in.WP_Cell6_percent_good, sizeof(uint8_t)*4);
        mav_array_memcpy(packet1.WP_Cell7_percent_good, packet_in.WP_Cell7_percent_good, sizeof(uint8_t)*4);
        mav_array_memcpy(packet1.WP_Cell8_percent_good, packet_in.WP_Cell8_percent_good, sizeof(uint8_t)*4);
        mav_array_memcpy(packet1.WP_Cell9_percent_good, packet_in.WP_Cell9_percent_good, sizeof(uint8_t)*4);
        mav_array_memcpy(packet1.WP_Cell10_percent_good, packet_in.WP_Cell10_percent_good, sizeof(uint8_t)*4);
        
#ifdef MAVLINK_STATUS_FLAG_OUT_MAVLINK1
        if (status->flags & MAVLINK_STATUS_FLAG_OUT_MAVLINK1) {
           // cope with extensions
           memset(MAVLINK_MSG_ID_DVL_DATA_MIN_LEN + (char *)&packet1, 0, sizeof(packet1)-MAVLINK_MSG_ID_DVL_DATA_MIN_LEN);
        }
#endif
        memset(&packet2, 0, sizeof(packet2));
    mavlink_msg_dvl_data_encode(system_id, component_id, &msg, &packet1);
    mavlink_msg_dvl_data_decode(&msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);

        memset(&packet2, 0, sizeof(packet2));
    mavlink_msg_dvl_data_pack(system_id, component_id, &msg , packet1.timestamp_ms , packet1.BT_range , packet1.BT_vel , packet1.BT_percent_good , packet1.BT_max_depth , packet1.WP_Cell1_vel , packet1.WP_Cell1_percent_good , packet1.WP_Cell2_vel , packet1.WP_Cell2_percent_good , packet1.WP_Cell3_vel , packet1.WP_Cell3_percent_good , packet1.WP_Cell4_vel , packet1.WP_Cell4_percent_good , packet1.WP_Cell5_vel , packet1.WP_Cell5_percent_good , packet1.WP_Cell6_vel , packet1.WP_Cell6_percent_good , packet1.WP_Cell7_vel , packet1.WP_Cell7_percent_good , packet1.WP_Cell8_vel , packet1.WP_Cell8_percent_good , packet1.WP_Cell9_vel , packet1.WP_Cell9_percent_good , packet1.WP_Cell10_vel , packet1.WP_Cell10_percent_good );
    mavlink_msg_dvl_data_decode(&msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);

        memset(&packet2, 0, sizeof(packet2));
    mavlink_msg_dvl_data_pack_chan(system_id, component_id, MAVLINK_COMM_0, &msg , packet1.timestamp_ms , packet1.BT_range , packet1.BT_vel , packet1.BT_percent_good , packet1.BT_max_depth , packet1.WP_Cell1_vel , packet1.WP_Cell1_percent_good , packet1.WP_Cell2_vel , packet1.WP_Cell2_percent_good , packet1.WP_Cell3_vel , packet1.WP_Cell3_percent_good , packet1.WP_Cell4_vel , packet1.WP_Cell4_percent_good , packet1.WP_Cell5_vel , packet1.WP_Cell5_percent_good , packet1.WP_Cell6_vel , packet1.WP_Cell6_percent_good , packet1.WP_Cell7_vel , packet1.WP_Cell7_percent_good , packet1.WP_Cell8_vel , packet1.WP_Cell8_percent_good , packet1.WP_Cell9_vel , packet1.WP_Cell9_percent_good , packet1.WP_Cell10_vel , packet1.WP_Cell10_percent_good );
    mavlink_msg_dvl_data_decode(&msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);

        memset(&packet2, 0, sizeof(packet2));
        mavlink_msg_to_send_buffer(buffer, &msg);
        for (i=0; i<mavlink_msg_get_send_buffer_length(&msg); i++) {
            comm_send_ch(MAVLINK_COMM_0, buffer[i]);
        }
    mavlink_msg_dvl_data_decode(last_msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);
        
        memset(&packet2, 0, sizeof(packet2));
    mavlink_msg_dvl_data_send(MAVLINK_COMM_1 , packet1.timestamp_ms , packet1.BT_range , packet1.BT_vel , packet1.BT_percent_good , packet1.BT_max_depth , packet1.WP_Cell1_vel , packet1.WP_Cell1_percent_good , packet1.WP_Cell2_vel , packet1.WP_Cell2_percent_good , packet1.WP_Cell3_vel , packet1.WP_Cell3_percent_good , packet1.WP_Cell4_vel , packet1.WP_Cell4_percent_good , packet1.WP_Cell5_vel , packet1.WP_Cell5_percent_good , packet1.WP_Cell6_vel , packet1.WP_Cell6_percent_good , packet1.WP_Cell7_vel , packet1.WP_Cell7_percent_good , packet1.WP_Cell8_vel , packet1.WP_Cell8_percent_good , packet1.WP_Cell9_vel , packet1.WP_Cell9_percent_good , packet1.WP_Cell10_vel , packet1.WP_Cell10_percent_good );
    mavlink_msg_dvl_data_decode(last_msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);

#ifdef MAVLINK_HAVE_GET_MESSAGE_INFO
    MAVLINK_ASSERT(mavlink_get_message_info_by_name("DVL_DATA") != NULL);
    MAVLINK_ASSERT(mavlink_get_message_info_by_id(MAVLINK_MSG_ID_DVL_DATA) != NULL);
#endif
}

static void mavlink_test_mixed_io_cmd(uint8_t system_id, uint8_t component_id, mavlink_message_t *last_msg)
{
#ifdef MAVLINK_STATUS_FLAG_OUT_MAVLINK1
    mavlink_status_t *status = mavlink_get_channel_status(MAVLINK_COMM_0);
        if ((status->flags & MAVLINK_STATUS_FLAG_OUT_MAVLINK1) && MAVLINK_MSG_ID_MIXED_IO_CMD >= 256) {
            return;
        }
#endif
    mavlink_message_t msg;
        uint8_t buffer[MAVLINK_MAX_PACKET_LEN];
        uint16_t i;
    mavlink_mixed_io_cmd_t packet_in = {
        963497464,963497672,{ 73.0, 74.0, 75.0, 76.0 },{ 185.0, 186.0, 187.0, 188.0 },{ 297.0, 298.0, 299.0, 300.0 }
    };
    mavlink_mixed_io_cmd_t packet1, packet2;
        memset(&packet1, 0, sizeof(packet1));
        packet1.gpio_1_32_output = packet_in.gpio_1_32_output;
        packet1.gpio_33_64_output = packet_in.gpio_33_64_output;
        
        mav_array_memcpy(packet1.dac_dev1_Vout, packet_in.dac_dev1_Vout, sizeof(float)*4);
        mav_array_memcpy(packet1.dac_dev2_Vout, packet_in.dac_dev2_Vout, sizeof(float)*4);
        mav_array_memcpy(packet1.dac_dev3_Vout, packet_in.dac_dev3_Vout, sizeof(float)*4);
        
#ifdef MAVLINK_STATUS_FLAG_OUT_MAVLINK1
        if (status->flags & MAVLINK_STATUS_FLAG_OUT_MAVLINK1) {
           // cope with extensions
           memset(MAVLINK_MSG_ID_MIXED_IO_CMD_MIN_LEN + (char *)&packet1, 0, sizeof(packet1)-MAVLINK_MSG_ID_MIXED_IO_CMD_MIN_LEN);
        }
#endif
        memset(&packet2, 0, sizeof(packet2));
    mavlink_msg_mixed_io_cmd_encode(system_id, component_id, &msg, &packet1);
    mavlink_msg_mixed_io_cmd_decode(&msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);

        memset(&packet2, 0, sizeof(packet2));
    mavlink_msg_mixed_io_cmd_pack(system_id, component_id, &msg , packet1.gpio_1_32_output , packet1.gpio_33_64_output , packet1.dac_dev1_Vout , packet1.dac_dev2_Vout , packet1.dac_dev3_Vout );
    mavlink_msg_mixed_io_cmd_decode(&msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);

        memset(&packet2, 0, sizeof(packet2));
    mavlink_msg_mixed_io_cmd_pack_chan(system_id, component_id, MAVLINK_COMM_0, &msg , packet1.gpio_1_32_output , packet1.gpio_33_64_output , packet1.dac_dev1_Vout , packet1.dac_dev2_Vout , packet1.dac_dev3_Vout );
    mavlink_msg_mixed_io_cmd_decode(&msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);

        memset(&packet2, 0, sizeof(packet2));
        mavlink_msg_to_send_buffer(buffer, &msg);
        for (i=0; i<mavlink_msg_get_send_buffer_length(&msg); i++) {
            comm_send_ch(MAVLINK_COMM_0, buffer[i]);
        }
    mavlink_msg_mixed_io_cmd_decode(last_msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);
        
        memset(&packet2, 0, sizeof(packet2));
    mavlink_msg_mixed_io_cmd_send(MAVLINK_COMM_1 , packet1.gpio_1_32_output , packet1.gpio_33_64_output , packet1.dac_dev1_Vout , packet1.dac_dev2_Vout , packet1.dac_dev3_Vout );
    mavlink_msg_mixed_io_cmd_decode(last_msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);

#ifdef MAVLINK_HAVE_GET_MESSAGE_INFO
    MAVLINK_ASSERT(mavlink_get_message_info_by_name("MIXED_IO_CMD") != NULL);
    MAVLINK_ASSERT(mavlink_get_message_info_by_id(MAVLINK_MSG_ID_MIXED_IO_CMD) != NULL);
#endif
}

static void mavlink_test_mixed_io_data(uint8_t system_id, uint8_t component_id, mavlink_message_t *last_msg)
{
#ifdef MAVLINK_STATUS_FLAG_OUT_MAVLINK1
    mavlink_status_t *status = mavlink_get_channel_status(MAVLINK_COMM_0);
        if ((status->flags & MAVLINK_STATUS_FLAG_OUT_MAVLINK1) && MAVLINK_MSG_ID_MIXED_IO_DATA >= 256) {
            return;
        }
#endif
    mavlink_message_t msg;
        uint8_t buffer[MAVLINK_MAX_PACKET_LEN];
        uint16_t i;
    mavlink_mixed_io_data_t packet_in = {
        963497464,963497672,963497880,963498088,963498296,{ 157.0, 158.0, 159.0, 160.0 },{ 269.0, 270.0, 271.0, 272.0 },{ 381.0, 382.0, 383.0, 384.0 },{ 493.0, 494.0, 495.0, 496.0, 497.0, 498.0, 499.0, 500.0 },{ 717.0, 718.0, 719.0, 720.0, 721.0, 722.0, 723.0, 724.0 },{ 941.0, 942.0, 943.0, 944.0, 945.0, 946.0, 947.0, 948.0 }
    };
    mavlink_mixed_io_data_t packet1, packet2;
        memset(&packet1, 0, sizeof(packet1));
        packet1.timestamp_ms = packet_in.timestamp_ms;
        packet1.gpio_1_32_output = packet_in.gpio_1_32_output;
        packet1.gpio_33_64_output = packet_in.gpio_33_64_output;
        packet1.gpio_1_32_input = packet_in.gpio_1_32_input;
        packet1.gpio_33_64_input = packet_in.gpio_33_64_input;
        
        mav_array_memcpy(packet1.dac_dev1_Vout, packet_in.dac_dev1_Vout, sizeof(float)*4);
        mav_array_memcpy(packet1.dac_dev2_Vout, packet_in.dac_dev2_Vout, sizeof(float)*4);
        mav_array_memcpy(packet1.dac_dev3_Vout, packet_in.dac_dev3_Vout, sizeof(float)*4);
        mav_array_memcpy(packet1.adc_dev1_Vin, packet_in.adc_dev1_Vin, sizeof(float)*8);
        mav_array_memcpy(packet1.adc_dev2_Vin, packet_in.adc_dev2_Vin, sizeof(float)*8);
        mav_array_memcpy(packet1.adc_dev3_Vin, packet_in.adc_dev3_Vin, sizeof(float)*8);
        
#ifdef MAVLINK_STATUS_FLAG_OUT_MAVLINK1
        if (status->flags & MAVLINK_STATUS_FLAG_OUT_MAVLINK1) {
           // cope with extensions
           memset(MAVLINK_MSG_ID_MIXED_IO_DATA_MIN_LEN + (char *)&packet1, 0, sizeof(packet1)-MAVLINK_MSG_ID_MIXED_IO_DATA_MIN_LEN);
        }
#endif
        memset(&packet2, 0, sizeof(packet2));
    mavlink_msg_mixed_io_data_encode(system_id, component_id, &msg, &packet1);
    mavlink_msg_mixed_io_data_decode(&msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);

        memset(&packet2, 0, sizeof(packet2));
    mavlink_msg_mixed_io_data_pack(system_id, component_id, &msg , packet1.timestamp_ms , packet1.gpio_1_32_output , packet1.gpio_33_64_output , packet1.gpio_1_32_input , packet1.gpio_33_64_input , packet1.dac_dev1_Vout , packet1.dac_dev2_Vout , packet1.dac_dev3_Vout , packet1.adc_dev1_Vin , packet1.adc_dev2_Vin , packet1.adc_dev3_Vin );
    mavlink_msg_mixed_io_data_decode(&msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);

        memset(&packet2, 0, sizeof(packet2));
    mavlink_msg_mixed_io_data_pack_chan(system_id, component_id, MAVLINK_COMM_0, &msg , packet1.timestamp_ms , packet1.gpio_1_32_output , packet1.gpio_33_64_output , packet1.gpio_1_32_input , packet1.gpio_33_64_input , packet1.dac_dev1_Vout , packet1.dac_dev2_Vout , packet1.dac_dev3_Vout , packet1.adc_dev1_Vin , packet1.adc_dev2_Vin , packet1.adc_dev3_Vin );
    mavlink_msg_mixed_io_data_decode(&msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);

        memset(&packet2, 0, sizeof(packet2));
        mavlink_msg_to_send_buffer(buffer, &msg);
        for (i=0; i<mavlink_msg_get_send_buffer_length(&msg); i++) {
            comm_send_ch(MAVLINK_COMM_0, buffer[i]);
        }
    mavlink_msg_mixed_io_data_decode(last_msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);
        
        memset(&packet2, 0, sizeof(packet2));
    mavlink_msg_mixed_io_data_send(MAVLINK_COMM_1 , packet1.timestamp_ms , packet1.gpio_1_32_output , packet1.gpio_33_64_output , packet1.gpio_1_32_input , packet1.gpio_33_64_input , packet1.dac_dev1_Vout , packet1.dac_dev2_Vout , packet1.dac_dev3_Vout , packet1.adc_dev1_Vin , packet1.adc_dev2_Vin , packet1.adc_dev3_Vin );
    mavlink_msg_mixed_io_data_decode(last_msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);

#ifdef MAVLINK_HAVE_GET_MESSAGE_INFO
    MAVLINK_ASSERT(mavlink_get_message_info_by_name("MIXED_IO_DATA") != NULL);
    MAVLINK_ASSERT(mavlink_get_message_info_by_id(MAVLINK_MSG_ID_MIXED_IO_DATA) != NULL);
#endif
}

static void mavlink_test_valve_cmd(uint8_t system_id, uint8_t component_id, mavlink_message_t *last_msg)
{
#ifdef MAVLINK_STATUS_FLAG_OUT_MAVLINK1
    mavlink_status_t *status = mavlink_get_channel_status(MAVLINK_COMM_0);
        if ((status->flags & MAVLINK_STATUS_FLAG_OUT_MAVLINK1) && MAVLINK_MSG_ID_VALVE_CMD >= 256) {
            return;
        }
#endif
    mavlink_message_t msg;
        uint8_t buffer[MAVLINK_MAX_PACKET_LEN];
        uint16_t i;
    mavlink_valve_cmd_t packet_in = {
        963497464,963497672,{ 17651, 17652, 17653, 17654, 17655, 17656, 17657, 17658, 17659, 17660, 17661, 17662, 17663, 17664, 17665, 17666, 17667, 17668, 17669, 17670, 17671, 17672, 17673, 17674, 17675, 17676, 17677, 17678, 17679, 17680, 17681, 17682, 17683, 17684, 17685, 17686, 17687, 17688, 17689, 17690 },{ 21811, 21812, 21813, 21814, 21815, 21816, 21817, 21818, 21819, 21820, 21821, 21822, 21823, 21824, 21825, 21826, 21827, 21828, 21829, 21830, 21831, 21832, 21833, 21834, 21835, 21836, 21837, 21838, 21839, 21840, 21841, 21842, 21843, 21844, 21845, 21846, 21847, 21848, 21849, 21850 }
    };
    mavlink_valve_cmd_t packet1, packet2;
        memset(&packet1, 0, sizeof(packet1));
        packet1.timestamp_ms = packet_in.timestamp_ms;
        packet1.sensor_power_mask = packet_in.sensor_power_mask;
        
        mav_array_memcpy(packet1.current_ma, packet_in.current_ma, sizeof(int16_t)*40);
        mav_array_memcpy(packet1.freq_hz, packet_in.freq_hz, sizeof(uint16_t)*40);
        
#ifdef MAVLINK_STATUS_FLAG_OUT_MAVLINK1
        if (status->flags & MAVLINK_STATUS_FLAG_OUT_MAVLINK1) {
           // cope with extensions
           memset(MAVLINK_MSG_ID_VALVE_CMD_MIN_LEN + (char *)&packet1, 0, sizeof(packet1)-MAVLINK_MSG_ID_VALVE_CMD_MIN_LEN);
        }
#endif
        memset(&packet2, 0, sizeof(packet2));
    mavlink_msg_valve_cmd_encode(system_id, component_id, &msg, &packet1);
    mavlink_msg_valve_cmd_decode(&msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);

        memset(&packet2, 0, sizeof(packet2));
    mavlink_msg_valve_cmd_pack(system_id, component_id, &msg , packet1.timestamp_ms , packet1.sensor_power_mask , packet1.current_ma , packet1.freq_hz );
    mavlink_msg_valve_cmd_decode(&msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);

        memset(&packet2, 0, sizeof(packet2));
    mavlink_msg_valve_cmd_pack_chan(system_id, component_id, MAVLINK_COMM_0, &msg , packet1.timestamp_ms , packet1.sensor_power_mask , packet1.current_ma , packet1.freq_hz );
    mavlink_msg_valve_cmd_decode(&msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);

        memset(&packet2, 0, sizeof(packet2));
        mavlink_msg_to_send_buffer(buffer, &msg);
        for (i=0; i<mavlink_msg_get_send_buffer_length(&msg); i++) {
            comm_send_ch(MAVLINK_COMM_0, buffer[i]);
        }
    mavlink_msg_valve_cmd_decode(last_msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);
        
        memset(&packet2, 0, sizeof(packet2));
    mavlink_msg_valve_cmd_send(MAVLINK_COMM_1 , packet1.timestamp_ms , packet1.sensor_power_mask , packet1.current_ma , packet1.freq_hz );
    mavlink_msg_valve_cmd_decode(last_msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);

#ifdef MAVLINK_HAVE_GET_MESSAGE_INFO
    MAVLINK_ASSERT(mavlink_get_message_info_by_name("VALVE_CMD") != NULL);
    MAVLINK_ASSERT(mavlink_get_message_info_by_id(MAVLINK_MSG_ID_VALVE_CMD) != NULL);
#endif
}

static void mavlink_test_valve_status(uint8_t system_id, uint8_t component_id, mavlink_message_t *last_msg)
{
#ifdef MAVLINK_STATUS_FLAG_OUT_MAVLINK1
    mavlink_status_t *status = mavlink_get_channel_status(MAVLINK_COMM_0);
        if ((status->flags & MAVLINK_STATUS_FLAG_OUT_MAVLINK1) && MAVLINK_MSG_ID_VALVE_STATUS >= 256) {
            return;
        }
#endif
    mavlink_message_t msg;
        uint8_t buffer[MAVLINK_MAX_PACKET_LEN];
        uint16_t i;
    mavlink_valve_status_t packet_in = {
        963497464,{ 963497672, 963497673 },{ 17859, 17860, 17861, 17862, 17863, 17864, 17865, 17866, 17867, 17868, 17869, 17870, 17871, 17872, 17873, 17874, 17875, 17876, 17877, 17878, 17879, 17880, 17881, 17882, 17883, 17884, 17885, 17886, 17887, 17888, 17889, 17890, 17891, 17892, 17893, 17894, 17895, 17896, 17897, 17898 },{ 22019, 22020, 22021, 22022, 22023, 22024, 22025, 22026, 22027, 22028, 22029, 22030, 22031, 22032, 22033, 22034, 22035, 22036, 22037, 22038, 22039, 22040, 22041, 22042 },24515,24619,{ 24723, 24724, 24725 },{ 71, 72, 73, 74, 75, 76, 77, 78, 79, 80, 81, 82, 83, 84, 85, 86, 87, 88, 89, 90, 91, 92, 93, 94, 95, 96, 97, 98, 99, 100, 101, 102, 103, 104, 105, 106, 107, 108, 109, 110 }
    };
    mavlink_valve_status_t packet1, packet2;
        memset(&packet1, 0, sizeof(packet1));
        packet1.timestamp_ms = packet_in.timestamp_ms;
        packet1.water_in_mv = packet_in.water_in_mv;
        packet1.board_voltage_mv = packet_in.board_voltage_mv;
        
        mav_array_memcpy(packet1.encoder, packet_in.encoder, sizeof(int32_t)*2);
        mav_array_memcpy(packet1.valve_current_x10, packet_in.valve_current_x10, sizeof(uint16_t)*40);
        mav_array_memcpy(packet1.sensor_data, packet_in.sensor_data, sizeof(uint16_t)*24);
        mav_array_memcpy(packet1.temp_x10, packet_in.temp_x10, sizeof(int16_t)*3);
        mav_array_memcpy(packet1.valve_state, packet_in.valve_state, sizeof(uint8_t)*40);
        
#ifdef MAVLINK_STATUS_FLAG_OUT_MAVLINK1
        if (status->flags & MAVLINK_STATUS_FLAG_OUT_MAVLINK1) {
           // cope with extensions
           memset(MAVLINK_MSG_ID_VALVE_STATUS_MIN_LEN + (char *)&packet1, 0, sizeof(packet1)-MAVLINK_MSG_ID_VALVE_STATUS_MIN_LEN);
        }
#endif
        memset(&packet2, 0, sizeof(packet2));
    mavlink_msg_valve_status_encode(system_id, component_id, &msg, &packet1);
    mavlink_msg_valve_status_decode(&msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);

        memset(&packet2, 0, sizeof(packet2));
    mavlink_msg_valve_status_pack(system_id, component_id, &msg , packet1.timestamp_ms , packet1.valve_current_x10 , packet1.valve_state , packet1.encoder , packet1.sensor_data , packet1.water_in_mv , packet1.board_voltage_mv , packet1.temp_x10 );
    mavlink_msg_valve_status_decode(&msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);

        memset(&packet2, 0, sizeof(packet2));
    mavlink_msg_valve_status_pack_chan(system_id, component_id, MAVLINK_COMM_0, &msg , packet1.timestamp_ms , packet1.valve_current_x10 , packet1.valve_state , packet1.encoder , packet1.sensor_data , packet1.water_in_mv , packet1.board_voltage_mv , packet1.temp_x10 );
    mavlink_msg_valve_status_decode(&msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);

        memset(&packet2, 0, sizeof(packet2));
        mavlink_msg_to_send_buffer(buffer, &msg);
        for (i=0; i<mavlink_msg_get_send_buffer_length(&msg); i++) {
            comm_send_ch(MAVLINK_COMM_0, buffer[i]);
        }
    mavlink_msg_valve_status_decode(last_msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);
        
        memset(&packet2, 0, sizeof(packet2));
    mavlink_msg_valve_status_send(MAVLINK_COMM_1 , packet1.timestamp_ms , packet1.valve_current_x10 , packet1.valve_state , packet1.encoder , packet1.sensor_data , packet1.water_in_mv , packet1.board_voltage_mv , packet1.temp_x10 );
    mavlink_msg_valve_status_decode(last_msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);

#ifdef MAVLINK_HAVE_GET_MESSAGE_INFO
    MAVLINK_ASSERT(mavlink_get_message_info_by_name("VALVE_STATUS") != NULL);
    MAVLINK_ASSERT(mavlink_get_message_info_by_id(MAVLINK_MSG_ID_VALVE_STATUS) != NULL);
#endif
}

static void mavlink_test_sealien_mavlink(uint8_t system_id, uint8_t component_id, mavlink_message_t *last_msg)
{
    mavlink_test_heartbeat(system_id, component_id, last_msg);
    mavlink_test_imu_data(system_id, component_id, last_msg);
    mavlink_test_thruster_status(system_id, component_id, last_msg);
    mavlink_test_gs_status(system_id, component_id, last_msg);
    mavlink_test_led_status(system_id, component_id, last_msg);
    mavlink_test_vcheck(system_id, component_id, last_msg);
    mavlink_test_height_status(system_id, component_id, last_msg);
    mavlink_test_depth_status(system_id, component_id, last_msg);
    mavlink_test_bem280(system_id, component_id, last_msg);
    mavlink_test_switch_status(system_id, component_id, last_msg);
    mavlink_test_thruster_cmd(system_id, component_id, last_msg);
    mavlink_test_thruster_lock(system_id, component_id, last_msg);
    mavlink_test_imu_calib(system_id, component_id, last_msg);
    mavlink_test_imu_clear(system_id, component_id, last_msg);
    mavlink_test_led_cmd(system_id, component_id, last_msg);
    mavlink_test_gs_cmd(system_id, component_id, last_msg);
    mavlink_test_gs_cfg(system_id, component_id, last_msg);
    mavlink_test_switch_cmd(system_id, component_id, last_msg);
    mavlink_test_dvl_data(system_id, component_id, last_msg);
    mavlink_test_mixed_io_cmd(system_id, component_id, last_msg);
    mavlink_test_mixed_io_data(system_id, component_id, last_msg);
    mavlink_test_valve_cmd(system_id, component_id, last_msg);
    mavlink_test_valve_status(system_id, component_id, last_msg);
}

#ifdef __cplusplus
}
#endif // __cplusplus
#endif // SEALIEN_MAVLINK_TESTSUITE_H
