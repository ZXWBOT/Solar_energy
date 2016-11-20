#ifndef __ENCODER_H__
#define __ENCODER_H__
#include "stm32f10x.h"

#define PWM_PB4 TIM3->CCR1
#define PWM_PB5 TIM3->CCR2

void TIM3_PWM_Init(u16 arr,u16 psc);
void Serve(float angle1,float angle2);
void Step_updata(u8 angle1,u8 angle2);

#define Aver_value  30//动作分解次数   

#endif
