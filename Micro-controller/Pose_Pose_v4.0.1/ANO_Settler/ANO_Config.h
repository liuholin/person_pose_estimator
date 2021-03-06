#ifndef _config_H
#define _config_H

#include "stm32f10x.h"

//#define ANO_DT_USE_USB_HID
//#define ANO_DT_USE_NRF24l01
//#define ANO_DT_USE_WIFI
#define POSE_DT_USE_USART1   1
#define DL_DT_USE_USART3     1

#define ACC_CAL_EN

#define OFFSET_AV_NUM 50
#define ACC_ADJ_EN //允许校准加速度计

#define MOTOR_NUM 6

/*----------------模块定义---------------------*/
#define MPU6050      0
#define MPU9250      1
#define ANO_IMU      0
#define POSE_IMU     1
#define DL_LN3X      1
#define VL15310x     0
#define MOTOR_PWM    0
#define PID_Module   0
#define CTRL_Module  0
#define RC_Module    0
#define ADC_Module   0
#define Bara_Module  0

#endif
