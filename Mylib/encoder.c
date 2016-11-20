#include "main.h"
#include "encoder.h"
#include "delay.h"

//encoder.INPUT_B---PB4(TIM3_CH1)
//encoder.INPUT_A---PB5(TIM3_CH2)

u8 angle1_last=90,angle2_last=90;   //�����ʼ���Ƕ�
u8 delay_step=13; 	//�����Ӧ��ʱ

/*
 * ��������TIM4_PWM_Init
 * ����  ��TIM4 PWM���ֳ�ʼ������
 * ����  ��arr���Զ���װֵ
		   psc��ʱ��Ԥ��Ƶ��
 * ���  ����
 */	
void TIM3_PWM_Init(u16 arr,u16 psc)
{  
	GPIO_InitTypeDef GPIO_InitStructure;
	TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure;
	TIM_OCInitTypeDef TIM_OCInitStructure;
	
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3,ENABLE);	//ʹ�ܶ�ʱ��4ʱ��
 	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB|RCC_APB2Periph_AFIO,ENABLE);  //ʹ��GPIO�����AFIO���ù���ģ��ʱ��
	    
   // GPIO_AFIODeInit();
	GPIO_PinRemapConfig(GPIO_Remap_SWJ_NoJTRST, ENABLE); 
	GPIO_PinRemapConfig(GPIO_Remap_SWJ_JTAGDisable, ENABLE); 
	GPIO_PinRemapConfig(GPIO_PartialRemap_TIM3  , ENABLE);
	//���ø�����Ϊ�����������,���TIM4 CH1��PWM���岨��	GPIOD.12
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_4 | GPIO_Pin_5; //TIM4_CH1
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;  //�����������
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOB, &GPIO_InitStructure);//��ʼ��GPIO
 
  //��ʼ��TIM4
	TIM_TimeBaseStructure.TIM_Period = arr; //��������һ�������¼�װ�����Զ���װ�ؼĴ������ڵ�ֵ
	TIM_TimeBaseStructure.TIM_Prescaler =psc; //����������ΪTIMxʱ��Ƶ�ʳ�����Ԥ��Ƶֵ 
	TIM_TimeBaseStructure.TIM_ClockDivision = 0; //����ʱ�ӷָ�:TDTS = Tck_tim
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;  //TIM���ϼ���ģʽ
	TIM_TimeBaseInit(TIM3, &TIM_TimeBaseStructure); //����TIM_TimeBaseInitStruct��ָ���Ĳ�����ʼ��TIMx��ʱ�������λ

	//��ʼ��TIM4 Channel2 PWMģʽ	 
	TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM2; //ѡ��ʱ��ģʽ:TIM�����ȵ���ģʽ2
 	TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable; //�Ƚ����ʹ��
	TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_Low ; //�������:TIM����Ƚϼ��Ը�
	
	TIM_OC1Init(TIM3, &TIM_OCInitStructure);  //����Tָ���Ĳ�����ʼ������TIM4 OC1
	TIM_OC1PreloadConfig(TIM3, TIM_OCPreload_Enable);  //ʹ��TIM4��CCR1�ϵ�Ԥװ�ؼĴ���
	
	TIM_OC2Init(TIM3, &TIM_OCInitStructure);  //����Tָ���Ĳ�����ʼ������TIM4 OC1
	TIM_OC2PreloadConfig(TIM3, TIM_OCPreload_Enable);  //ʹ��TIM4��CCR1�ϵ�Ԥװ�ؼĴ���
 
	TIM_Cmd(TIM3, ENABLE);  //ʹ��TIM4
	TIM_CtrlPWMOutputs(TIM3, ENABLE);
}
/*
 * ��������Serve
 * ����  �����PWM����
 * ����  ��angle1�����1��PWMֵ
		   angle2�����2��PWMֵ
 * ���  ����
 */	
void Serve(float angle1,float angle2)
{
	PWM_PB4=(float)(angle1*1.1111)+50;
	PWM_PB5=(float)(angle2*1.1111)+50;
}
/*
 * ��������Step_updata
 * ����  ������Ƕȿ���
 * ����  ��angle1�����1�ŽǶ�ֵ
		   angle2�����2�ŽǶ�ֵ
 * ���  ����
 */	

void Step_updata(u8 angle1,u8 angle2)
{	
	float dir_angle1,dir_angle2;
	u8 i;
	for(i=0;i<Aver_value;i++)
	{	
		dir_angle1=(float)(angle1_last+((angle1-angle1_last)*i)/Aver_value);
		dir_angle2=(float)(angle2_last+((angle2-angle2_last)*i)/Aver_value);
		
		Serve(dir_angle1,dir_angle2);
		delay_ms(delay_step);
		
	}
	angle1_last=angle1;
	angle2_last=angle2;
}
