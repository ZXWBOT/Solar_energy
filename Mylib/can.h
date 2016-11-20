#ifndef __CAN_H__
#define __CAN_H__
extern unsigned char can_get_flag; 

void CAN_Configuration(void);

void CAN_Configuration(void);
void CAN_RoboModule_DRV_Reset(unsigned char CAN_ID);
void CAN_RoboModule_DRV_Mode_Choice(unsigned char CAN_ID,unsigned char mode);
void CAN_RoboModule_DRV_PWM_Mode(unsigned char CAN_ID,short temp_pwm);
void CAN_RoboModule_DRV_PWM_Current_Mode(unsigned char CAN_ID,short temp_pwm,short temp_current);
void CAN_RoboModule_DRV_PWM_Velocity_Mode(unsigned char CAN_ID,short temp_pwm,short temp_velocity);
void CAN_RoboModule_DRV_PWM_Position_Mode(unsigned char CAN_ID,short temp_pwm,long temp_position);
void CAN_RoboModule_DRV_PWM_Velocity_Position_Mode(unsigned char CAN_ID,short temp_pwm,short temp_velocity,long temp_position);
void CAN_RoboModule_DRV_Current_Velocity_Mode(unsigned char CAN_ID,short temp_current,short temp_velocity);
void CAN_RoboModule_DRV_Current_Position_Mode(unsigned char CAN_ID,short temp_current,long temp_position);
void CAN_RoboModule_DRV_Current_Velocity_Position_Mode(unsigned char CAN_ID,short temp_current,short temp_velocity,long temp_position);



#endif 
