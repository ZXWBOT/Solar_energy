#include "main.h"

//HVD232---CAN_TX---PA12
//HVD232---CAN_RX---PA11

void CAN_Configuration1(void)
{
	CAN_InitTypeDef        can;
	CAN_FilterInitTypeDef  can_filter;
	GPIO_InitTypeDef 	   gpio;
	NVIC_InitTypeDef   	   nvic;

	RCC_APB1PeriphClockCmd(RCC_APB1Periph_CAN1,  ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
    
	gpio.GPIO_Pin = GPIO_Pin_11;
	gpio.GPIO_Mode = GPIO_Mode_IPU;
    gpio.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA, &gpio);	//CAN_RX
	
	gpio.GPIO_Pin = GPIO_Pin_12;	   
    gpio.GPIO_Mode = GPIO_Mode_AF_PP;
	gpio.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA, &gpio);    //CAN_TX

    nvic.NVIC_IRQChannel = USB_HP_CAN1_TX_IRQn;
    nvic.NVIC_IRQChannelPreemptionPriority = 1;
    nvic.NVIC_IRQChannelSubPriority = 0;
    nvic.NVIC_IRQChannelCmd = ENABLE;
    NVIC_Init(&nvic);
    
    nvic.NVIC_IRQChannel = USB_LP_CAN1_RX0_IRQn;  
    nvic.NVIC_IRQChannelPreemptionPriority = 0;
    nvic.NVIC_IRQChannelSubPriority = 0;
    nvic.NVIC_IRQChannelCmd = ENABLE;
    NVIC_Init(&nvic);

	CAN_DeInit(CAN1);

	can.CAN_TTCM = DISABLE;
	can.CAN_ABOM = DISABLE;
	can.CAN_AWUM = DISABLE;
	can.CAN_NART = DISABLE;	  
	can.CAN_RFLM = DISABLE;																
	can.CAN_TXFP = ENABLE;		
 	can.CAN_Mode = CAN_Mode_Normal;
	can.CAN_SJW = CAN_SJW_1tq;
	can.CAN_BS1 = CAN_BS1_5tq;
	can.CAN_BS2 = CAN_BS2_3tq;
	can.CAN_Prescaler = 4;     //CAN BaudRate 36/(1+5+3)/4=1Mbps
	CAN_Init(CAN1, &can);
    
	can_filter.CAN_FilterNumber = 0;
	can_filter.CAN_FilterMode = CAN_FilterMode_IdMask;
	can_filter.CAN_FilterScale = CAN_FilterScale_32bit;
	can_filter.CAN_FilterIdHigh = 0x0000;
	can_filter.CAN_FilterIdLow = 0x0000;
	can_filter.CAN_FilterMaskIdHigh = 0x0000;
	can_filter.CAN_FilterMaskIdLow = 0x0000;
	can_filter.CAN_FilterFIFOAssignment = 0;
	can_filter.CAN_FilterActivation = ENABLE;
	CAN_FilterInit(&can_filter);

    CAN_ITConfig(CAN1,CAN_IT_FMP0,ENABLE);
    CAN_ITConfig(CAN1,CAN_IT_TME,ENABLE);
}

void CAN_Configuration(void)
{
	CAN_InitTypeDef        can;
	CAN_FilterInitTypeDef  can_filter;
	GPIO_InitTypeDef 	   gpio;
	NVIC_InitTypeDef   	   nvic;

	RCC_APB1PeriphClockCmd(RCC_APB1Periph_CAN1,  ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB |
                           RCC_APB2Periph_AFIO , ENABLE);
    
    GPIO_PinRemapConfig(GPIO_Remap1_CAN1,ENABLE);
    
	gpio.GPIO_Pin = GPIO_Pin_8;
	gpio.GPIO_Mode = GPIO_Mode_IPU;
    gpio.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOB, &gpio);	//CAN_RX
	
	gpio.GPIO_Pin = GPIO_Pin_9;	   
    gpio.GPIO_Mode = GPIO_Mode_AF_PP;
	gpio.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOB, &gpio);    //CAN_TX

    nvic.NVIC_IRQChannel = USB_HP_CAN1_TX_IRQn;
    nvic.NVIC_IRQChannelPreemptionPriority = 1;
    nvic.NVIC_IRQChannelSubPriority = 0;
    nvic.NVIC_IRQChannelCmd = ENABLE;
    NVIC_Init(&nvic);
    
    nvic.NVIC_IRQChannel = USB_LP_CAN1_RX0_IRQn;  
    nvic.NVIC_IRQChannelPreemptionPriority = 0;
    nvic.NVIC_IRQChannelSubPriority = 0;
    nvic.NVIC_IRQChannelCmd = ENABLE;
    NVIC_Init(&nvic);

	CAN_DeInit(CAN1);

	can.CAN_TTCM = DISABLE;
	can.CAN_ABOM = DISABLE;
	can.CAN_AWUM = DISABLE;
	can.CAN_NART = DISABLE;	  
	can.CAN_RFLM = DISABLE;																
	can.CAN_TXFP = ENABLE;		
 	can.CAN_Mode = CAN_Mode_Normal;

	can.CAN_SJW = CAN_SJW_1tq;
	can.CAN_BS1 = CAN_BS1_5tq;
	can.CAN_BS2 = CAN_BS2_3tq;
	can.CAN_Prescaler = 4;     //CAN BaudRate 36/(1+5+3)/4=1Mbps  1532-2.2

	CAN_Init(CAN1, &can);	
	
	can_filter.CAN_FilterNumber = 0; 
	can_filter.CAN_FilterMode = CAN_FilterMode_IdMask;
	can_filter.CAN_FilterScale = CAN_FilterScale_32bit;
	can_filter.CAN_FilterIdHigh = 0;
	can_filter.CAN_FilterIdLow = 0;
	can_filter.CAN_FilterMaskIdHigh = 0;
	can_filter.CAN_FilterMaskIdLow = 0;
	can_filter.CAN_FilterFIFOAssignment = 0;
	can_filter.CAN_FilterActivation = ENABLE;
	
	CAN_FilterInit(&can_filter);
    
    CAN_ITConfig(CAN1,CAN_IT_FMP0,ENABLE);
    CAN_ITConfig(CAN1,CAN_IT_TME,ENABLE);
}


void USB_LP_CAN1_RX0_IRQHandler(void) //CAN RX
{
    CanRxMsg rx_message;
    
    if (CAN_GetITStatus(CAN1,CAN_IT_FMP0)!= RESET) 
	{
        CAN_ClearITPendingBit(CAN1, CAN_IT_FF0);
        CAN_Receive(CAN1, CAN_FIFO0, &rx_message);
        
    }
}

unsigned char can_tx_success_flag=0;
void USB_HP_CAN1_TX_IRQHandler(void) //CAN TX
{
    if (CAN_GetITStatus(CAN1,CAN_IT_TME)!= RESET)
	{
	   CAN_ClearITPendingBit(CAN1,CAN_IT_TME);
       can_tx_success_flag=1;
    }
}


/****************************************************************************************
                                       复位指令
CAN_ID的取值范围如下：
DRV_ALL_RESET_ID
DRV01_RESET_ID    DRV02_RESET_ID    DRV03_RESET_ID    DRV04_RESET_ID    DRV05_RESET_ID
DRV06_RESET_ID    DRV07_RESET_ID    DRV08_RESET_ID    DRV09_RESET_ID    DRV10_RESET_ID
DRV11_RESET_ID    DRV12_RESET_ID    DRV13_RESET_ID    DRV14_RESET_ID    DRV15_RESET_ID
*****************************************************************************************/
void CAN_RoboModule_DRV_Reset(unsigned char CAN_ID)
{
    CanTxMsg tx_message;
    
    tx_message.IDE = CAN_ID_STD;    //标准帧
    tx_message.RTR = CAN_RTR_DATA;  //数据帧
    tx_message.DLC = 0x08;          //帧长度为8
    tx_message.StdId = CAN_ID;      //帧ID为传入参数的CAN_ID
    
    tx_message.Data[0] = 0x55;
    tx_message.Data[1] = 0x55;
    tx_message.Data[2] = 0x55;
    tx_message.Data[3] = 0x55;
    tx_message.Data[4] = 0x55;
    tx_message.Data[5] = 0x55;
    tx_message.Data[6] = 0x55;
    tx_message.Data[7] = 0x55;
    
    can_tx_success_flag = 0;
    CAN_Transmit(CAN1,&tx_message);
    while(can_tx_success_flag == 0);
}


/****************************************************************************************
                                     模式选择指令
CAN_ID的取值范围如下：
DRV_ALL_MODE_CHOICE_ID
DRV01_MODE_CHOICE_ID    DRV02_MODE_CHOICE_ID    DRV03_MODE_CHOICE_ID    DRV04_MODE_CHOICE_ID    DRV05_MODE_CHOICE_ID    
DRV06_MODE_CHOICE_ID    DRV07_MODE_CHOICE_ID    DRV08_MODE_CHOICE_ID    DRV09_MODE_CHOICE_ID    DRV10_MODE_CHOICE_ID    
DRV11_MODE_CHOICE_ID    DRV12_MODE_CHOICE_ID    DRV13_MODE_CHOICE_ID    DRV14_MODE_CHOICE_ID    DRV15_MODE_CHOICE_ID

mode的取值范围如下：
ENTER_PWM_MODE
ENTER_PWM_CURRENT_MODE
ENTER_PWM_VELOCITY_MODE
ENTER_PWM_POSITION_MODE
ENTER_PWM_VELOCITY_POSITION_MODE
ENTER_CURRENT_VELOCITY_MODE
ENTER_CURRENT_POSITION_MODE
ENTER_CURRENT_VELOCITY_POSITION_MODE
*****************************************************************************************/
void CAN_RoboModule_DRV_Mode_Choice(unsigned char CAN_ID,unsigned char mode)
{
    CanTxMsg tx_message;
    
    tx_message.IDE = CAN_ID_STD;    //标准帧
    tx_message.RTR = CAN_RTR_DATA;  //数据帧
    tx_message.DLC = 0x08;          //帧长度为8
    tx_message.StdId = CAN_ID;      //帧ID为传入参数的CAN_ID
    
    tx_message.Data[0] = mode;
    tx_message.Data[1] = 0x55;
    tx_message.Data[2] = 0x55;
    tx_message.Data[3] = 0x55;
    tx_message.Data[4] = 0x55;
    tx_message.Data[5] = 0x55;
    tx_message.Data[6] = 0x55;
    tx_message.Data[7] = 0x55;
    
    can_tx_success_flag = 0;
    CAN_Transmit(CAN1,&tx_message);
    while(can_tx_success_flag == 0);
}


/****************************************************************************************
                                  PWM模式下的数据指令
CAN_ID的取值范围如下：
DRV_ALL_PWM_MODE_ID
DRV01_PWM_MODE_ID    DRV02_PWM_MODE_ID    DRV03_PWM_MODE_ID    DRV04_PWM_MODE_ID    DRV05_PWM_MODE_ID
DRV06_PWM_MODE_ID    DRV07_PWM_MODE_ID    DRV08_PWM_MODE_ID    DRV09_PWM_MODE_ID    DRV10_PWM_MODE_ID
DRV11_PWM_MODE_ID    DRV12_PWM_MODE_ID    DRV13_PWM_MODE_ID    DRV14_PWM_MODE_ID    DRV15_PWM_MODE_ID

temp_pwm的取值范围如下：
-5000 ~ +5000
*****************************************************************************************/
void CAN_RoboModule_DRV_PWM_Mode(unsigned char CAN_ID,short temp_pwm)
{
    CanTxMsg tx_message;
    
    tx_message.IDE = CAN_ID_STD;    //标准帧
    tx_message.RTR = CAN_RTR_DATA;  //数据帧
    tx_message.DLC = 0x08;          //帧长度为8
    tx_message.StdId = CAN_ID;      //帧ID为传入参数的CAN_ID
    
    if(temp_pwm > 5000)
    {
        temp_pwm = 5000;
    }
    else if(temp_pwm < -5000)
    {
        temp_pwm = -5000;
    }
    
    tx_message.Data[0] = (unsigned char)((temp_pwm>>8)&0xff);
    tx_message.Data[1] = (unsigned char)(temp_pwm&0xff);
    tx_message.Data[2] = 0x55;
    tx_message.Data[3] = 0x55;
    tx_message.Data[4] = 0x55;
    tx_message.Data[5] = 0x55;
    tx_message.Data[6] = 0x55;
    tx_message.Data[7] = 0x55;
    
    can_tx_success_flag = 0;
    CAN_Transmit(CAN1,&tx_message);
    while(can_tx_success_flag == 0);
}


/****************************************************************************************
                                  PWM电流模式下的数据指令
CAN_ID的取值范围如下：
DRV_ALL_PWM_CURRENT_MODE_ID
DRV01_PWM_CURRENT_MODE_ID    DRV02_PWM_CURRENT_MODE_ID    DRV03_PWM_CURRENT_MODE_ID    DRV04_PWM_CURRENT_MODE_ID    DRV05_PWM_CURRENT_MODE_ID
DRV06_PWM_CURRENT_MODE_ID    DRV07_PWM_CURRENT_MODE_ID    DRV08_PWM_CURRENT_MODE_ID    DRV09_PWM_CURRENT_MODE_ID    DRV10_PWM_CURRENT_MODE_ID
DRV11_PWM_CURRENT_MODE_ID    DRV12_PWM_CURRENT_MODE_ID    DRV13_PWM_CURRENT_MODE_ID    DRV14_PWM_CURRENT_MODE_ID    DRV15_PWM_CURRENT_MODE_ID

temp_pwm的取值范围如下：
0 ~ +5000

temp_current的取值范围如下：
-1600 ~ +1600
*****************************************************************************************/
void CAN_RoboModule_DRV_PWM_Current_Mode(unsigned char CAN_ID,short temp_pwm,short temp_current)
{
    CanTxMsg tx_message;
    
    tx_message.IDE = CAN_ID_STD;    //标准帧
    tx_message.RTR = CAN_RTR_DATA;  //数据帧
    tx_message.DLC = 0x08;          //帧长度为8
    tx_message.StdId = CAN_ID;      //帧ID为传入参数的CAN_ID
    
    if(temp_pwm > 5000)
    {
        temp_pwm = 5000;
    }
    else if(temp_pwm < -5000)
    {
        temp_pwm = -5000;
    }
    
    if(temp_pwm < 0)
    {
        temp_pwm = abs(temp_pwm);
    }
    
    if(temp_current > 1600)
    {
        temp_current = 1600;
    }
    else if(temp_current < -1600)
    {
        temp_current = -1600;
    }
    
    tx_message.Data[0] = (unsigned char)((temp_pwm>>8)&0xff);
    tx_message.Data[1] = (unsigned char)(temp_pwm&0xff);
    tx_message.Data[2] = (unsigned char)((temp_current>>8)&0xff);
    tx_message.Data[3] = (unsigned char)(temp_current&0xff);
    tx_message.Data[4] = 0x55;
    tx_message.Data[5] = 0x55;
    tx_message.Data[6] = 0x55;
    tx_message.Data[7] = 0x55;
    
    can_tx_success_flag = 0;
    CAN_Transmit(CAN1,&tx_message);
    while(can_tx_success_flag == 0);
}


/****************************************************************************************
                                  PWM速度模式下的数据指令
CAN_ID的取值范围如下：
DRV_ALL_PWM_VELOCITY_MODE_ID
DRV01_PWM_VELOCITY_MODE_ID    DRV02_PWM_VELOCITY_MODE_ID    DRV03_PWM_VELOCITY_MODE_ID    DRV04_PWM_VELOCITY_MODE_ID    DRV05_PWM_VELOCITY_MODE_ID
DRV06_PWM_VELOCITY_MODE_ID    DRV07_PWM_VELOCITY_MODE_ID    DRV08_PWM_VELOCITY_MODE_ID    DRV09_PWM_VELOCITY_MODE_ID    DRV10_PWM_VELOCITY_MODE_ID
DRV11_PWM_VELOCITY_MODE_ID    DRV12_PWM_VELOCITY_MODE_ID    DRV13_PWM_VELOCITY_MODE_ID    DRV14_PWM_VELOCITY_MODE_ID    DRV15_PWM_VELOCITY_MODE_ID

temp_pwm的取值范围如下：
0 ~ +5000

temp_velocity的取值范围如下：
-2000 ~ +2000
*****************************************************************************************/
void CAN_RoboModule_DRV_PWM_Velocity_Mode(unsigned char CAN_ID,short temp_pwm,short temp_velocity)
{
    CanTxMsg tx_message;
    
    tx_message.IDE = CAN_ID_STD;    //标准帧
    tx_message.RTR = CAN_RTR_DATA;  //数据帧
    tx_message.DLC = 0x08;          //帧长度为8
    tx_message.StdId = CAN_ID;      //帧ID为传入参数的CAN_ID
    
    if(temp_pwm > 5000)
    {
        temp_pwm = 5000;
    }
    else if(temp_pwm < -5000)
    {
        temp_pwm = -5000;
    }
    
    if(temp_pwm < 0)
    {
        temp_pwm = abs(temp_pwm);
    }
    
    if(temp_velocity > 2000)
    {
        temp_velocity = 2000;
    }
    else if(temp_velocity < -2000)
    {
        temp_velocity = -2000;
    }
    
    tx_message.Data[0] = (unsigned char)((temp_pwm>>8)&0xff);
    tx_message.Data[1] = (unsigned char)(temp_pwm&0xff);
    tx_message.Data[2] = (unsigned char)((temp_velocity>>8)&0xff);
    tx_message.Data[3] = (unsigned char)(temp_velocity&0xff);
    tx_message.Data[4] = 0x55;
    tx_message.Data[5] = 0x55;
    tx_message.Data[6] = 0x55;
    tx_message.Data[7] = 0x55;
    
    can_tx_success_flag = 0;
    CAN_Transmit(CAN1,&tx_message);
    while(can_tx_success_flag == 0);
}


/****************************************************************************************
                                  PWM位置模式下的数据指令
CAN_ID的取值范围如下：
DRV_ALL_PWM_POSITION_MODE_ID
DRV01_PWM_POSITION_MODE_ID    DRV02_PWM_POSITION_MODE_ID    DRV03_PWM_POSITION_MODE_ID    DRV04_PWM_POSITION_MODE_ID    DRV05_PWM_POSITION_MODE_ID
DRV06_PWM_POSITION_MODE_ID    DRV07_PWM_POSITION_MODE_ID    DRV08_PWM_POSITION_MODE_ID    DRV09_PWM_POSITION_MODE_ID    DRV10_PWM_POSITION_MODE_ID
DRV11_PWM_POSITION_MODE_ID    DRV12_PWM_POSITION_MODE_ID    DRV13_PWM_POSITION_MODE_ID    DRV14_PWM_POSITION_MODE_ID    DRV15_PWM_POSITION_MODE_ID

temp_pwm的取值范围如下：
0 ~ +5000

temp_position的取值范围如下：
32位有符号整型
*****************************************************************************************/
void CAN_RoboModule_DRV_PWM_Position_Mode(unsigned char CAN_ID,short temp_pwm,long temp_position)
{
    CanTxMsg tx_message;
    
    tx_message.IDE = CAN_ID_STD;    //标准帧
    tx_message.RTR = CAN_RTR_DATA;  //数据帧
    tx_message.DLC = 0x08;          //帧长度为8
    tx_message.StdId = CAN_ID;      //帧ID为传入参数的CAN_ID
    
    if(temp_pwm > 5000)
    {
        temp_pwm = 5000;
    }
    else if(temp_pwm < -5000)
    {
        temp_pwm = -5000;
    }
    
    if(temp_pwm < 0)
    {
        temp_pwm = abs(temp_pwm);
    }
    
    tx_message.Data[0] = (unsigned char)((temp_pwm>>8)&0xff);
    tx_message.Data[1] = (unsigned char)(temp_pwm&0xff);
    tx_message.Data[2] = 0x55;
    tx_message.Data[3] = 0x55;
    tx_message.Data[4] = (unsigned char)((temp_position>>24)&0xff);
    tx_message.Data[5] = (unsigned char)((temp_position>>16)&0xff);
    tx_message.Data[6] = (unsigned char)((temp_position>>8)&0xff);
    tx_message.Data[7] = (unsigned char)(temp_position&0xff);
    
    can_tx_success_flag = 0;
    CAN_Transmit(CAN1,&tx_message);
    while(can_tx_success_flag == 0);
}


/****************************************************************************************
                                  PWM速度位置模式下的数据指令
CAN_ID的取值范围如下：
DRV_ALL_PWM_VELOCITY_POSITION_MODE_ID
DRV01_PWM_VELOCITY_POSITION_MODE_ID    DRV02_PWM_VELOCITY_POSITION_MODE_ID    DRV03_PWM_VELOCITY_POSITION_MODE_ID    DRV04_PWM_VELOCITY_POSITION_MODE_ID    DRV05_PWM_VELOCITY_POSITION_MODE_ID
DRV06_PWM_VELOCITY_POSITION_MODE_ID    DRV07_PWM_VELOCITY_POSITION_MODE_ID    DRV08_PWM_VELOCITY_POSITION_MODE_ID    DRV09_PWM_VELOCITY_POSITION_MODE_ID    DRV10_PWM_VELOCITY_POSITION_MODE_ID
DRV11_PWM_VELOCITY_POSITION_MODE_ID    DRV12_PWM_VELOCITY_POSITION_MODE_ID    DRV13_PWM_VELOCITY_POSITION_MODE_ID    DRV14_PWM_VELOCITY_POSITION_MODE_ID    DRV15_PWM_VELOCITY_POSITION_MODE_ID

temp_pwm的取值范围如下：
0 ~ +5000

temp_velocity的取值范围如下：
0 ~ +2000

temp_position的取值范围如下：
32位有符号整型
*****************************************************************************************/
void CAN_RoboModule_DRV_PWM_Velocity_Position_Mode(unsigned char CAN_ID,short temp_pwm,short temp_velocity,long temp_position)
{
    CanTxMsg tx_message;
    
    tx_message.IDE = CAN_ID_STD;    //标准帧
    tx_message.RTR = CAN_RTR_DATA;  //数据帧
    tx_message.DLC = 0x08;          //帧长度为8
    tx_message.StdId = CAN_ID;      //帧ID为传入参数的CAN_ID
    
    if(temp_pwm > 5000)
    {
        temp_pwm = 5000;
    }
    else if(temp_pwm < -5000)
    {
        temp_pwm = -5000;
    }
    
    if(temp_pwm < 0)
    {
        temp_pwm = abs(temp_pwm);
    }
    
    if(temp_velocity > 2000)
    {
        temp_velocity = 2000;
    }
    else if(temp_velocity < -2000)
    {
        temp_velocity = -2000;
    }
    
    if(temp_velocity < 0)
    {
        temp_velocity = abs(temp_velocity);
    }
    
    tx_message.Data[0] = (unsigned char)((temp_pwm>>8)&0xff);
    tx_message.Data[1] = (unsigned char)(temp_pwm&0xff);
    tx_message.Data[2] = (unsigned char)((temp_velocity>>8)&0xff);
    tx_message.Data[3] = (unsigned char)(temp_velocity&0xff);
    tx_message.Data[4] = (unsigned char)((temp_position>>24)&0xff);
    tx_message.Data[5] = (unsigned char)((temp_position>>16)&0xff);
    tx_message.Data[6] = (unsigned char)((temp_position>>8)&0xff);
    tx_message.Data[7] = (unsigned char)(temp_position&0xff);
    
    can_tx_success_flag = 0;
    CAN_Transmit(CAN1,&tx_message);
    while(can_tx_success_flag == 0);
}


/****************************************************************************************
                                  电流速度模式下的数据指令
CAN_ID的取值范围如下：
DRV_ALL_CURRENT_VELOCITY_MODE_ID
DRV01_CURRENT_VELOCITY_MODE_ID    DRV02_CURRENT_VELOCITY_MODE_ID    DRV03_CURRENT_VELOCITY_MODE_ID    DRV04_CURRENT_VELOCITY_MODE_ID    DRV05_CURRENT_VELOCITY_MODE_ID
DRV06_CURRENT_VELOCITY_MODE_ID    DRV07_CURRENT_VELOCITY_MODE_ID    DRV08_CURRENT_VELOCITY_MODE_ID    DRV09_CURRENT_VELOCITY_MODE_ID    DRV10_CURRENT_VELOCITY_MODE_ID
DRV11_CURRENT_VELOCITY_MODE_ID    DRV12_CURRENT_VELOCITY_MODE_ID    DRV13_CURRENT_VELOCITY_MODE_ID    DRV14_CURRENT_VELOCITY_MODE_ID    DRV15_CURRENT_VELOCITY_MODE_ID

temp_current的取值范围如下：
0 ~ +1600

temp_velocity的取值范围如下：
-2000 ~ +2000
*****************************************************************************************/
void CAN_RoboModule_DRV_Current_Velocity_Mode(unsigned char CAN_ID,short temp_current,short temp_velocity)
{
    CanTxMsg tx_message;
    
    tx_message.IDE = CAN_ID_STD;    //标准帧
    tx_message.RTR = CAN_RTR_DATA;  //数据帧
    tx_message.DLC = 0x08;          //帧长度为8
    tx_message.StdId = CAN_ID;      //帧ID为传入参数的CAN_ID
    
    if(temp_current > 1600)
    {
        temp_current = 1600;
    }
    else if(temp_current < -1600)
    {
        temp_current = -1600;
    }
    
    if(temp_current < 0)
    {
        temp_current = abs(temp_current);
    }
    
    if(temp_velocity > 2000)
    {
        temp_velocity = 2000;
    }
    else if(temp_velocity < -2000)
    {
        temp_velocity = -2000;
    }
    
    tx_message.Data[0] = (unsigned char)((temp_current>>8)&0xff);
    tx_message.Data[1] = (unsigned char)(temp_current&0xff);
    tx_message.Data[2] = (unsigned char)((temp_velocity>>8)&0xff);
    tx_message.Data[3] = (unsigned char)(temp_velocity&0xff);
    tx_message.Data[4] = 0x55;
    tx_message.Data[5] = 0x55;
    tx_message.Data[6] = 0x55;
    tx_message.Data[7] = 0x55;
    
    can_tx_success_flag = 0;
    CAN_Transmit(CAN1,&tx_message);
    while(can_tx_success_flag == 0);
}


/****************************************************************************************
                                  电流位置模式下的数据指令
CAN_ID的取值范围如下：
DRV_ALL_CURRENT_POSITION_MODE_ID
DRV01_CURRENT_POSITION_MODE_ID    DRV02_CURRENT_POSITION_MODE_ID    DRV03_CURRENT_POSITION_MODE_ID    DRV04_CURRENT_POSITION_MODE_ID    DRV05_CURRENT_POSITION_MODE_ID
DRV06_CURRENT_POSITION_MODE_ID    DRV07_CURRENT_POSITION_MODE_ID    DRV08_CURRENT_POSITION_MODE_ID    DRV09_CURRENT_POSITION_MODE_ID    DRV10_CURRENT_POSITION_MODE_ID
DRV11_CURRENT_POSITION_MODE_ID    DRV12_CURRENT_POSITION_MODE_ID    DRV13_CURRENT_POSITION_MODE_ID    DRV14_CURRENT_POSITION_MODE_ID    DRV15_CURRENT_POSITION_MODE_ID

temp_current的取值范围如下：
0 ~ +1600

temp_position的取值范围如下：
32位有符号整型
*****************************************************************************************/
void CAN_RoboModule_DRV_Current_Position_Mode(unsigned char CAN_ID,short temp_current,long temp_position)
{
    CanTxMsg tx_message;
    
    tx_message.IDE = CAN_ID_STD;    //标准帧
    tx_message.RTR = CAN_RTR_DATA;  //数据帧
    tx_message.DLC = 0x08;          //帧长度为8
    tx_message.StdId = CAN_ID;      //帧ID为传入参数的CAN_ID
    
    if(temp_current > 1600)
    {
        temp_current = 1600;
    }
    else if(temp_current < -1600)
    {
        temp_current = -1600;
    }
    
    if(temp_current < 0)
    {
        temp_current = abs(temp_current);
    }
    
    tx_message.Data[0] = (unsigned char)((temp_current>>8)&0xff);
    tx_message.Data[1] = (unsigned char)(temp_current&0xff);
    tx_message.Data[2] = 0x55;
    tx_message.Data[3] = 0x55;
    tx_message.Data[4] = (unsigned char)((temp_position>>24)&0xff);
    tx_message.Data[5] = (unsigned char)((temp_position>>16)&0xff);
    tx_message.Data[6] = (unsigned char)((temp_position>>8)&0xff);
    tx_message.Data[7] = (unsigned char)(temp_position&0xff);
    
    can_tx_success_flag = 0;
    CAN_Transmit(CAN1,&tx_message);
    while(can_tx_success_flag == 0);
}


/****************************************************************************************
                                  电流速度位置模式下的数据指令
CAN_ID的取值范围如下：
DRV_ALL_CURRENT_VELOCITY_POSITION_MODE_ID
DRV01_CURRENT_VELOCITY_POSITION_MODE_ID    DRV02_CURRENT_VELOCITY_POSITION_MODE_ID    DRV03_CURRENT_VELOCITY_POSITION_MODE_ID    
DRV04_CURRENT_VELOCITY_POSITION_MODE_ID    DRV05_CURRENT_VELOCITY_POSITION_MODE_ID    DRV06_CURRENT_VELOCITY_POSITION_MODE_ID    
DRV07_CURRENT_VELOCITY_POSITION_MODE_ID    DRV08_CURRENT_VELOCITY_POSITION_MODE_ID    DRV09_CURRENT_VELOCITY_POSITION_MODE_ID    
DRV10_CURRENT_VELOCITY_POSITION_MODE_ID    DRV11_CURRENT_VELOCITY_POSITION_MODE_ID    DRV12_CURRENT_VELOCITY_POSITION_MODE_ID    
DRV13_CURRENT_VELOCITY_POSITION_MODE_ID    DRV14_CURRENT_VELOCITY_POSITION_MODE_ID    DRV15_CURRENT_VELOCITY_POSITION_MODE_ID

temp_current的取值范围如下：
0 ~ +1600

temp_velocity的取值范围如下：
0 ~ +2000

temp_position的取值范围如下：
32位有符号整型
*****************************************************************************************/
void CAN_RoboModule_DRV_Current_Velocity_Position_Mode(unsigned char CAN_ID,short temp_current,short temp_velocity,long temp_position)
{
    CanTxMsg tx_message;
    
    tx_message.IDE = CAN_ID_STD;    //标准帧
    tx_message.RTR = CAN_RTR_DATA;  //数据帧
    tx_message.DLC = 0x08;          //帧长度为8
    tx_message.StdId = CAN_ID;      //帧ID为传入参数的CAN_ID
    
    if(temp_current > 1600)
    {
        temp_current = 1600;
    }
    else if(temp_current < -1600)
    {
        temp_current = -1600;
    }
    
    if(temp_current < 0)
    {
        temp_current = abs(temp_current);
    }
    
    if(temp_velocity > 2000)
    {
        temp_velocity = 2000;
    }
    else if(temp_velocity < -2000)
    {
        temp_velocity = -2000;
    }
    
    if(temp_velocity < 0)
    {
        temp_velocity = abs(temp_velocity);
    }
    
    tx_message.Data[0] = (unsigned char)((temp_current>>8)&0xff);
    tx_message.Data[1] = (unsigned char)(temp_current&0xff);
    tx_message.Data[2] = (unsigned char)((temp_velocity>>8)&0xff);
    tx_message.Data[3] = (unsigned char)(temp_velocity&0xff);
    tx_message.Data[4] = (unsigned char)((temp_position>>24)&0xff);
    tx_message.Data[5] = (unsigned char)((temp_position>>16)&0xff);
    tx_message.Data[6] = (unsigned char)((temp_position>>8)&0xff);
    tx_message.Data[7] = (unsigned char)(temp_position&0xff);
    
    can_tx_success_flag = 0;
    CAN_Transmit(CAN1,&tx_message);
    while(can_tx_success_flag == 0);
}


/****************************************************************************************
                                      配置指令
CAN_ID的取值范围如下：
DRV_ALL_CONFIG_ID
DRV01_CONFIG_ID    DRV02_CONFIG_ID    DRV03_CONFIG_ID    DRV04_CONFIG_ID    DRV05_CONFIG_ID
DRV06_CONFIG_ID    DRV07_CONFIG_ID    DRV08_CONFIG_ID    DRV09_CONFIG_ID    DRV10_CONFIG_ID
DRV11_CONFIG_ID    DRV12_CONFIG_ID    DRV13_CONFIG_ID    DRV14_CONFIG_ID    DRV15_CONFIG_ID

temp_time的取值范围如下：
0 ~ 255
*****************************************************************************************/
void CAN_RoboModule_DRV_Config(unsigned char CAN_ID,unsigned char temp_time)
{
    CanTxMsg tx_message;
    
    tx_message.IDE = CAN_ID_STD;    //标准帧
    tx_message.RTR = CAN_RTR_DATA;  //数据帧
    tx_message.DLC = 0x08;          //帧长度为8
    tx_message.StdId = CAN_ID;      //帧ID为传入参数的CAN_ID
    
    tx_message.Data[0] = temp_time;
    tx_message.Data[1] = 0x55;
    tx_message.Data[2] = 0x55;
    tx_message.Data[3] = 0x55;
    tx_message.Data[4] = 0x55;
    tx_message.Data[5] = 0x55;
    tx_message.Data[6] = 0x55;
    tx_message.Data[7] = 0x55;
    
    can_tx_success_flag = 0;
    CAN_Transmit(CAN1,&tx_message);
    while(can_tx_success_flag == 0);
}
