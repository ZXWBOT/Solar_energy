#ifndef __MAIN_H__
#define __MAIN_H__

#include "stm32f10x.h"
#include <stdio.h>
#include <stdlib.h>

#include "encoder.h"
#include "led.h"
#include "pwm.h"
#include "tim2.h"
#include "delay.h"
#include "usart2.h"
#include "can.h"
#include "ad.h"
#include "flash.h"
#include "key.h"
#define abs(x) ((x)>0? (x):(-(x)))
extern unsigned char moto_start_flag;

/************周学伟添加CAN电机组别和编号************/
#define CAN_0GROUP_1NAMBER                   0X012
#define CAN_0GROUP_2NAMBER                   0X022
#define CAN_0GROUP_3NAMBER                   0X032

#define DRV_ALL_RESET_ID                              0x00
#define DRV_ALL_MODE_CHOICE_ID                        0x01
#define DRV_ALL_PWM_MODE_ID                           0x02
#define DRV_ALL_PWM_CURRENT_MODE_ID                   0x03
#define DRV_ALL_PWM_VELOCITY_MODE_ID                  0x04
#define DRV_ALL_PWM_POSITION_MODE_ID                  0x05
#define DRV_ALL_PWM_VELOCITY_POSITION_MODE_ID         0x06
#define DRV_ALL_CURRENT_VELOCITY_MODE_ID              0x07
#define DRV_ALL_CURRENT_POSITION_MODE_ID              0x08
#define DRV_ALL_CURRENT_VELOCITY_POSITION_MODE_ID     0x09
#define DRV_ALL_CONFIG_ID                             0x0a
#define DRV_ALL_RETURN_ID                             0x0b

#define ENTER_PWM_MODE                                0x01
#define ENTER_PWM_CURRENT_MODE                        0x02
#define ENTER_PWM_VELOCITY_MODE                       0x03
#define ENTER_PWM_POSITION_MODE                       0x04
#define ENTER_PWM_VELOCITY_POSITION_MODE              0x05
#define ENTER_CURRENT_VELOCITY_MODE                   0x06
#define ENTER_CURRENT_POSITION_MODE                   0x07
#define ENTER_CURRENT_VELOCITY_POSITION_MODE          0x08

#endif
