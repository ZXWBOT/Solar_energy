#include "main.h"


/*********ZHOUXUEWEI add bluetooth menu progream*******/
/*************************
*'a' :���ҵ����״̬Ϊ�������ID��CAN_0GROUP_1NAMBER
*'b' :���ҵ����״̬Ϊ�أ����ID��CAN_0GROUP_1NAMBER
*'c' :���µ����״̬Ϊ�������ID��CAN_0GROUP_2NAMBER
*'d' :���µ����״̬Ϊ�أ����ID��CAN_0GROUP_2NAMBER
*'e' :ˢ�ӵ����״̬Ϊ�������ID��CAN_0GROUP_3NAMBER
*'f' :ˢ�ӵ����״̬Ϊ�أ����ID��CAN_0GROUP_3NAMBER
*'g' :��������״̬Ϊ����
*'h' :��������״̬Ϊ�أ�
**************************/
#define MOTO_1MAX_SPEED 500
#define MOTO_2MAX_SPEED 1300
void Menu_Bluetooth(const char value)
{
	switch(value)
	{
		case 'a': CAN_RoboModule_DRV_PWM_Mode(CAN_0GROUP_1NAMBER,MOTO_1MAX_SPEED);break;
		case 'b': CAN_RoboModule_DRV_PWM_Mode(CAN_0GROUP_1NAMBER,-MOTO_1MAX_SPEED);break;
		
		case 'c': CAN_RoboModule_DRV_PWM_Mode(CAN_0GROUP_2NAMBER,MOTO_2MAX_SPEED);break;
		case 'd': CAN_RoboModule_DRV_PWM_Mode(CAN_0GROUP_2NAMBER,-MOTO_2MAX_SPEED);break;
		
		case 'e': CAN_RoboModule_DRV_PWM_Mode(CAN_0GROUP_3NAMBER,3000);break;
		case 'f': CAN_RoboModule_DRV_PWM_Mode(CAN_0GROUP_3NAMBER,0);break;
		
		case 'g': Step_updata(120,95);break;
		case 'h': Step_updata(65,20);break;
		case 'i': CAN_RoboModule_DRV_PWM_Mode(CAN_0GROUP_1NAMBER,0);
				  CAN_RoboModule_DRV_PWM_Mode(CAN_0GROUP_2NAMBER,0);
			break;
		default :break;
	}
}
int main(void)
{
 	PWM_Configuration();
	ADC_Configuration();
	CAN_Configuration();
	LED_Configuration();
	
	uart_init(9600);
	TIM3_PWM_Init(1999,719);

////////1///2////65 20	
	Step_updata(65,20);
	
	CAN_RoboModule_DRV_Reset(DRV_ALL_RESET_ID);
    delay_ms(500);
    CAN_RoboModule_DRV_Mode_Choice(DRV_ALL_MODE_CHOICE_ID,ENTER_PWM_MODE);
    delay_ms(500);
	
    while(1)
	{
		Menu_Bluetooth(USART_ReceiveData(USART2));
	}
}
