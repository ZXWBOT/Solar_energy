#include "main.h"

int encoder_value=0;
float speed_moto=0;


void TIM2_Configuration(void)
{
    TIM_TimeBaseInitTypeDef  tim;
    NVIC_InitTypeDef         nvic;
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2,ENABLE);

    nvic.NVIC_IRQChannel = TIM2_IRQn;
    nvic.NVIC_IRQChannelPreemptionPriority = 1;
    nvic.NVIC_IRQChannelSubPriority = 1;
    nvic.NVIC_IRQChannelCmd = ENABLE;
    NVIC_Init(&nvic);

    tim.TIM_Prescaler = 36-1;    //APB1 is 36MHz
    tim.TIM_CounterMode = TIM_CounterMode_Up;
    tim.TIM_ClockDivision = TIM_CKD_DIV1;
    tim.TIM_Period = 250;      //2MS
    TIM_TimeBaseInit(TIM2,&tim);
}

void TIM2_Start(void)
{
    TIM_Cmd(TIM2, ENABLE);	 
    TIM_ITConfig(TIM2, TIM_IT_Update,ENABLE);
    TIM_ClearFlag(TIM2, TIM_FLAG_Update);	
}


void TIM2_IRQHandler(void)//2ms 
{
	
    if (TIM_GetITStatus(TIM2,TIM_IT_Update)!= RESET) 
	{
		printf("hello world data is %c\r\n",USART_ReceiveData(USART2));
    }
}
