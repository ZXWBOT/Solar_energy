#ifndef __PWM_H__
#define __PWM_H__

void PWM_Configuration(void);
void MOTO_foreward(unsigned short PWM_VAL);
void MOTO_inversion(unsigned short PWM_VAL);
float moto_Control_speed(float current_speed,float target_speed);
void moto_flag_perinter(void);
void control_PWM_OUTPUT(float output_PWM);
void speed_output(float last_speed,float terger_speed);

#define PWM1_PA8   TIM1->CCR1   //8
#define PWM2_PA9   TIM1->CCR2
#define PWM3_PA10  TIM1->CCR3
#define PWM4_PA11  TIM1->CCR4   //11

#define ESC_MAX 2000



#endif
