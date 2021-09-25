#pragma once

#include "CANInterface.h"
#include "CANMsg.h"
#include "hw_bridge.h"

static void sendACK(HWBRIDGE::GIMBAL_ACK_VALUES ackValue);
static mbed_error_status_t gimbalSetControlMode(void);
static mbed_error_status_t gimbalSetJointPIDParams(void);
static mbed_error_status_t commonSwitchCANBus(void);

namespace CANConfig {

using namespace HWBRIDGE;

static CANMsgMap rxMsgMap = {
    // Streamed messages
    {CANID::GIMBAL_SET_JOINT_POSITION,
     {
         {CANSIGNAL::GIMBAL_SET_PAN_POSITION, 0},
         {CANSIGNAL::GIMBAL_SET_PITCH_POSITION, 0},
         {CANSIGNAL::GIMBAL_SET_ROLL_POSITION, 0},
     }},
    {CANID::GIMBAL_SET_JOINT_ANGULAR_VELOCITY,
     {
         {CANSIGNAL::GIMBAL_SET_PAN_ANGULAR_VELOCITY, 0},
     }},

    // One-shot messages
    {CANID::GIMBAL_SET_CONTROL_MODE,
     {
         {CANSIGNAL::GIMBAL_PAN_CONTROL_MODE, (CANSignalValue_t)GIMBAL_PAN_CONTROL_MODE_VALUES::SNA},
     }},
    {CANID::GIMBAL_SET_JOINT_PID_PARAMS,
     {
         {CANSIGNAL::GIMBAL_JOINT_PIDID, (CANSignalValue_t)GIMBAL_JOINT_PIDID_VALUES::SNA},
         {CANSIGNAL::GIMBAL_JOINT_PID_PROPORTIONAL_GAIN,
          (CANSignalValue_t)GIMBAL_JOINT_PID_PROPORTIONAL_GAIN_VALUES::SNA},
         {CANSIGNAL::GIMBAL_JOINT_PID_INTEGRAL_GAIN, (CANSignalValue_t)GIMBAL_JOINT_PID_INTEGRAL_GAIN_VALUES::SNA},
         {CANSIGNAL::GIMBAL_JOINT_PID_DERIVATIVE_GAIN, (CANSignalValue_t)GIMBAL_JOINT_PID_DERIVATIVE_GAIN_VALUES::SNA},
         {CANSIGNAL::GIMBAL_JOINT_PID_DEADZONE, (CANSignalValue_t)GIMBAL_JOINT_PID_DEADZONE_VALUES::SNA},
     }},
    {CANID::COMMON_SWITCH_CAN_BUS,
     {
         {CANSIGNAL::COMMON_CAN_BUS_ID, (CANSignalValue_t)COMMON_CAN_BUS_ID_VALUES::SNA},
     }},
};

static CANMsgMap txMsgMap = {
    {CANID::GIMBAL_REPORT_JOINT_DATA,
     {
         {CANSIGNAL::GIMBAL_REPORT_PAN_POSITION, 0},
         {CANSIGNAL::GIMBAL_REPORT_PAN_ANGULAR_VELOCITY, 0},
     }},
    {CANID::GIMBAL_REPORT_FAULTS,
     {
         {CANSIGNAL::GIMBAL_PAN_ENCODER_STATE, (CANSignalValue_t)GIMBAL_PAN_ENCODER_STATE_VALUES::SNA},
         {CANSIGNAL::GIMBAL_NUM_CANRX_FAULTS, 0},
         {CANSIGNAL::GIMBAL_NUM_CANTX_FAULTS, 0},
     }},
    {CANID::GIMBAL_REPORT_DIAGNOSTICS,
     {
         {CANSIGNAL::GIMBAL_REPORT_NUM_STREAMED_MSGS_RECEIVED, 0},
         {CANSIGNAL::GIMBAL_REPORT_NUM_ONE_SHOT_MSGS_RECEIVED, 0},
     }},
};

const static CANMsg::CANMsgHandlerMap rxOneShotMsgHandler = {
    {CANID::GIMBAL_SET_CONTROL_MODE, &gimbalSetControlMode},
    {CANID::GIMBAL_SET_JOINT_PID_PARAMS, &gimbalSetJointPIDParams},
    {CANID::COMMON_SWITCH_CAN_BUS, &commonSwitchCANBus},
};

CANInterface::Config config = {
    // CAN bus pins
    .can1_RX = CAN1_RX,
    .can1_TX = CAN1_TX,
    .can2_RX = CAN2_RX,
    .can2_TX = CAN2_TX,

    // Message maps and handlers
    .rxMsgMap            = &rxMsgMap,
    .txMsgMap            = &txMsgMap,
    .rxOneShotMsgHandler = &rxOneShotMsgHandler,
};

}  // namespace CANConfig
