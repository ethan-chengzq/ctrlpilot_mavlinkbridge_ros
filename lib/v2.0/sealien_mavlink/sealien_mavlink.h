/** @file
 *  @brief MAVLink comm protocol generated from sealien_mavlink.xml
 *  @see http://mavlink.org
 */
#pragma once
#ifndef MAVLINK_SEALIEN_MAVLINK_H
#define MAVLINK_SEALIEN_MAVLINK_H

#ifndef MAVLINK_H
    #error Wrong include order: MAVLINK_SEALIEN_MAVLINK.H MUST NOT BE DIRECTLY USED. Include mavlink.h from the same directory instead or set ALL AND EVERY defines from MAVLINK.H manually accordingly, including the #define MAVLINK_H call.
#endif

#define MAVLINK_SEALIEN_MAVLINK_XML_HASH 1449854335120561911

#ifdef __cplusplus
extern "C" {
#endif

// MESSAGE LENGTHS AND CRCS

#ifndef MAVLINK_MESSAGE_LENGTHS
#define MAVLINK_MESSAGE_LENGTHS {}
#endif

#ifndef MAVLINK_MESSAGE_CRCS
#define MAVLINK_MESSAGE_CRCS {{0, 176, 7, 7, 0, 0, 0}, {1, 64, 98, 98, 0, 0, 0}, {2, 33, 101, 101, 0, 0, 0}, {3, 16, 20, 20, 0, 0, 0}, {4, 32, 14, 14, 0, 0, 0}, {5, 119, 16, 16, 0, 0, 0}, {6, 190, 64, 64, 0, 0, 0}, {7, 6, 36, 36, 0, 0, 0}, {8, 151, 16, 16, 0, 0, 0}, {9, 142, 12, 12, 0, 0, 0}, {10, 41, 24, 24, 0, 0, 0}, {11, 203, 1, 1, 0, 0, 0}, {12, 28, 20, 20, 0, 0, 0}, {13, 192, 1, 1, 0, 0, 0}, {14, 0, 2, 2, 0, 0, 0}, {15, 208, 5, 5, 0, 0, 0}, {16, 1, 20, 20, 0, 0, 0}, {17, 67, 2, 2, 0, 0, 0}, {18, 145, 244, 244, 0, 0, 0}, {19, 173, 56, 56, 0, 0, 0}, {20, 76, 164, 164, 0, 0, 0}, {21, 228, 168, 168, 0, 0, 0}, {22, 8, 190, 190, 0, 0, 0}}
#endif

#include "../protocol.h"

#define MAVLINK_ENABLED_SEALIEN_MAVLINK

// ENUM DEFINITIONS



// MAVLINK VERSION

#ifndef MAVLINK_VERSION
#define MAVLINK_VERSION 2
#endif

#if (MAVLINK_VERSION == 0)
#undef MAVLINK_VERSION
#define MAVLINK_VERSION 2
#endif

// MESSAGE DEFINITIONS
#include "./mavlink_msg_heartbeat.h"
#include "./mavlink_msg_imu_data.h"
#include "./mavlink_msg_thruster_status.h"
#include "./mavlink_msg_gs_status.h"
#include "./mavlink_msg_led_status.h"
#include "./mavlink_msg_vcheck.h"
#include "./mavlink_msg_height_status.h"
#include "./mavlink_msg_depth_status.h"
#include "./mavlink_msg_bem280.h"
#include "./mavlink_msg_switch_status.h"
#include "./mavlink_msg_thruster_cmd.h"
#include "./mavlink_msg_thruster_lock.h"
#include "./mavlink_msg_imu_calib.h"
#include "./mavlink_msg_imu_clear.h"
#include "./mavlink_msg_led_cmd.h"
#include "./mavlink_msg_gs_cmd.h"
#include "./mavlink_msg_gs_cfg.h"
#include "./mavlink_msg_switch_cmd.h"
#include "./mavlink_msg_dvl_data.h"
#include "./mavlink_msg_mixed_io_cmd.h"
#include "./mavlink_msg_mixed_io_data.h"
#include "./mavlink_msg_valve_cmd.h"
#include "./mavlink_msg_valve_status.h"

// base include



#if MAVLINK_SEALIEN_MAVLINK_XML_HASH == MAVLINK_PRIMARY_XML_HASH
# define MAVLINK_MESSAGE_INFO {MAVLINK_MESSAGE_INFO_HEARTBEAT, MAVLINK_MESSAGE_INFO_IMU_DATA, MAVLINK_MESSAGE_INFO_THRUSTER_STATUS, MAVLINK_MESSAGE_INFO_GS_STATUS, MAVLINK_MESSAGE_INFO_LED_STATUS, MAVLINK_MESSAGE_INFO_VCHECK, MAVLINK_MESSAGE_INFO_HEIGHT_STATUS, MAVLINK_MESSAGE_INFO_DEPTH_STATUS, MAVLINK_MESSAGE_INFO_BEM280, MAVLINK_MESSAGE_INFO_SWITCH_STATUS, MAVLINK_MESSAGE_INFO_THRUSTER_CMD, MAVLINK_MESSAGE_INFO_THRUSTER_LOCK, MAVLINK_MESSAGE_INFO_IMU_CALIB, MAVLINK_MESSAGE_INFO_IMU_CLEAR, MAVLINK_MESSAGE_INFO_LED_CMD, MAVLINK_MESSAGE_INFO_GS_CMD, MAVLINK_MESSAGE_INFO_GS_CFG, MAVLINK_MESSAGE_INFO_SWITCH_CMD, MAVLINK_MESSAGE_INFO_DVL_DATA, MAVLINK_MESSAGE_INFO_MIXED_IO_CMD, MAVLINK_MESSAGE_INFO_MIXED_IO_DATA, MAVLINK_MESSAGE_INFO_VALVE_CMD, MAVLINK_MESSAGE_INFO_VALVE_STATUS}
# define MAVLINK_MESSAGE_NAMES {{ "BEM280", 8 }, { "DEPTH_STATUS", 7 }, { "DVL_DATA", 18 }, { "GS_CFG", 16 }, { "GS_CMD", 15 }, { "GS_STATUS", 3 }, { "HEARTBEAT", 0 }, { "HEIGHT_STATUS", 6 }, { "IMU_CALIB", 12 }, { "IMU_CLEAR", 13 }, { "IMU_DATA", 1 }, { "LED_CMD", 14 }, { "LED_STATUS", 4 }, { "MIXED_IO_CMD", 19 }, { "MIXED_IO_DATA", 20 }, { "SWITCH_CMD", 17 }, { "SWITCH_STATUS", 9 }, { "THRUSTER_CMD", 10 }, { "THRUSTER_LOCK", 11 }, { "THRUSTER_STATUS", 2 }, { "VALVE_CMD", 21 }, { "VALVE_STATUS", 22 }, { "VCHECK", 5 }}
# if MAVLINK_COMMAND_24BIT
#  include "../mavlink_get_info.h"
# endif
#endif

#ifdef __cplusplus
}
#endif // __cplusplus
#endif // MAVLINK_SEALIEN_MAVLINK_H
