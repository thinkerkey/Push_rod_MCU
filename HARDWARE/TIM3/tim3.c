/*
*文件名：定时器3配置文件
*功  能：源文件
*作  者：程晓强
*/
#include "tim3.h"
#include "led.h"
#include "encoder.h"
#include "usart1.h"
#include "motor.h"
#include "pid.h"

/*----定时器3初始化函数-----*/
void TIM3_Init(u16 arr,u16 psc)
{
/*----定时器3寄存器结构体定义-------*/
	TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
	NVIC_InitTypeDef NVIC_InitStructure;
/*----使能定时器3时钟-------*/
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3, ENABLE);
/*----定时器3重装载值和分频系数-------*/
	TIM_TimeBaseStructure.TIM_Period = arr; 
	TIM_TimeBaseStructure.TIM_Prescaler =psc; 
	TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1; 
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;  
	TIM_TimeBaseInit(TIM3, &TIM_TimeBaseStructure); 
/*----开启定时器中断------*/
	TIM_ITConfig(TIM3,TIM_IT_Update,ENABLE ); 

	NVIC_InitStructure.NVIC_IRQChannel = TIM3_IRQn;  
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0; 
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 2;  
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE; 
	NVIC_Init(&NVIC_InitStructure); 

	TIM_Cmd(TIM3, ENABLE);  						 
}


uint8_t PoleDoMode;
uint8_t SetLenthFromPC;
/*-----定时器3中断服务函数-----*/
void TIM3_IRQHandler(void)
{
	static int pulse_cnt = 0;
    static float length = 0.0;
    static uint8_t DeadCnt = 0;
	if(TIM_GetITStatus(TIM3,TIM_IT_Update) != RESET)
	{
        pulse_cnt = Read_Site();
        length = LenAndPulseSwitch(pulse_cnt);
        
        if(PoleDoMode == ModeSend)
        {
             SetMotor(PIDController(&LengthCtrlPid,SetLenthFromPC,length));
        }    
        printf("A%d\r\nB%.2f\r\n",SetLenthFromPC,length);        
		LED0 = !LED0;
        LED1 = !LED1;
		TIM_ClearITPendingBit(TIM3,TIM_IT_Update);
	}
}

