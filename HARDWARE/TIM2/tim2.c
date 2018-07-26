/*
*文件名：定时器2配置文件
*功  能：源文件
*作  者：程晓强
*/
#include "tim2.h"


void SetPwmValu(u16 moto)
{
    TIM_SetCompare1(TIM2,moto);
}


void TIM2_Init(u16 arr,u16 psc)
{
/*----定义定时器所用到的结构体----*/
	TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
	NVIC_InitTypeDef NVIC_InitStructure;
/*----开启定时器时钟-------*/
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2, ENABLE);
/*----定时器寄存器配置，重装载值，向上计数，分频------*/
	TIM_TimeBaseStructure.TIM_Period = arr; 
	TIM_TimeBaseStructure.TIM_Prescaler =psc; 
	TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1; 
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;  
	TIM_TimeBaseInit(TIM2, &TIM_TimeBaseStructure); 

/*-----定时器中断初始化配置------*/
	TIM_ITConfig(TIM2,TIM_IT_Update,ENABLE ); 
/*-----定时器中断优先级------*/
	NVIC_InitStructure.NVIC_IRQChannel = TIM2_IRQn;  
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0; 
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;  
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE; 
	NVIC_Init(&NVIC_InitStructure); 

	TIM_Cmd(TIM2, ENABLE);  						 
}
void TIM2_PWM_Init(u16 arr,u16 psc)
{	 
	GPIO_InitTypeDef GPIO_InitStructure;							//定义GPIO初始化结构体
	TIM_OCInitTypeDef  TIM2_OCInitStructure;

	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2, ENABLE);			//使能TIM4时钟
 	RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO|RCC_APB2Periph_GPIOA, ENABLE);  			//使能GPIOB时钟
	
	GPIO_InitStructure.GPIO_Pin  = GPIO_Pin_0;							//B6,B7,B8,B9 清除之前设置  
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP; 								//复用推挽输出  
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA, &GPIO_InitStructure);
	GPIO_ResetBits(GPIOA,GPIO_Pin_0);

	
	TIM2_Init(arr,psc);
  
	//PWM初始化
	TIM2_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1;
	TIM2_OCInitStructure.TIM_OutputState =  TIM_OutputState_Enable;
	TIM2_OCInitStructure.TIM_Pulse = 0;
	TIM2_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High;
	
	TIM_OC1Init(TIM2,&TIM2_OCInitStructure);
	
	TIM_CtrlPWMOutputs(TIM2,ENABLE);
	
    TIM_OC1PreloadConfig(TIM2,TIM_OCPreload_Enable);

	
	TIM_ARRPreloadConfig(TIM2,ENABLE);
	
   	TIM_Cmd(TIM2,ENABLE ); 																	//使能定时器4
}




/*----定时器2中断服务函数-----*/
void TIM2_IRQHandler(void)
{
	if(TIM_GetITStatus(TIM2,TIM_IT_Update) != RESET)
	{
		TIM_ClearITPendingBit(TIM2,TIM_IT_Update);
	}
}
