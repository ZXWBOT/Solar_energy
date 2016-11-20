#include "main.h"
#include "encoder.h"
#include "delay.h"

//encoder.INPUT_B---PB4(TIM3_CH1)
//encoder.INPUT_A---PB5(TIM3_CH2)

u8 angle1_last=90,angle2_last=90;   //舵机初始化角度
u8 delay_step=13; 	//舵机响应延时

/*
 * 函数名：TIM4_PWM_Init
 * 描述  ：TIM4 PWM部分初始化程序
 * 输入  ：arr：自动重装值
		   psc：时钟预分频数
 * 输出  ：无
 */	
void TIM3_PWM_Init(u16 arr,u16 psc)
{  
	GPIO_InitTypeDef GPIO_InitStructure;
	TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure;
	TIM_OCInitTypeDef TIM_OCInitStructure;
	
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3,ENABLE);	//使能定时器4时钟
 	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB|RCC_APB2Periph_AFIO,ENABLE);  //使能GPIO外设和AFIO复用功能模块时钟
	    
   // GPIO_AFIODeInit();
	GPIO_PinRemapConfig(GPIO_Remap_SWJ_NoJTRST, ENABLE); 
	GPIO_PinRemapConfig(GPIO_Remap_SWJ_JTAGDisable, ENABLE); 
	GPIO_PinRemapConfig(GPIO_PartialRemap_TIM3  , ENABLE);
	//设置该引脚为复用输出功能,输出TIM4 CH1的PWM脉冲波形	GPIOD.12
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_4 | GPIO_Pin_5; //TIM4_CH1
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;  //复用推挽输出
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOB, &GPIO_InitStructure);//初始化GPIO
 
  //初始化TIM4
	TIM_TimeBaseStructure.TIM_Period = arr; //设置在下一个更新事件装入活动的自动重装载寄存器周期的值
	TIM_TimeBaseStructure.TIM_Prescaler =psc; //设置用来作为TIMx时钟频率除数的预分频值 
	TIM_TimeBaseStructure.TIM_ClockDivision = 0; //设置时钟分割:TDTS = Tck_tim
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;  //TIM向上计数模式
	TIM_TimeBaseInit(TIM3, &TIM_TimeBaseStructure); //根据TIM_TimeBaseInitStruct中指定的参数初始化TIMx的时间基数单位

	//初始化TIM4 Channel2 PWM模式	 
	TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM2; //选择定时器模式:TIM脉冲宽度调制模式2
 	TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable; //比较输出使能
	TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_Low ; //输出极性:TIM输出比较极性高
	
	TIM_OC1Init(TIM3, &TIM_OCInitStructure);  //根据T指定的参数初始化外设TIM4 OC1
	TIM_OC1PreloadConfig(TIM3, TIM_OCPreload_Enable);  //使能TIM4在CCR1上的预装载寄存器
	
	TIM_OC2Init(TIM3, &TIM_OCInitStructure);  //根据T指定的参数初始化外设TIM4 OC1
	TIM_OC2PreloadConfig(TIM3, TIM_OCPreload_Enable);  //使能TIM4在CCR1上的预装载寄存器
 
	TIM_Cmd(TIM3, ENABLE);  //使能TIM4
	TIM_CtrlPWMOutputs(TIM3, ENABLE);
}
/*
 * 函数名：Serve
 * 描述  ：舵机PWM控制
 * 输入  ：angle1：舵机1号PWM值
		   angle2：舵机2号PWM值
 * 输出  ：无
 */	
void Serve(float angle1,float angle2)
{
	PWM_PB4=(float)(angle1*1.1111)+50;
	PWM_PB5=(float)(angle2*1.1111)+50;
}
/*
 * 函数名：Step_updata
 * 描述  ：舵机角度控制
 * 输入  ：angle1：舵机1号角度值
		   angle2：舵机2号角度值
 * 输出  ：无
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
