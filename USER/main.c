#include "main.h"


void All_Init(void);

int main()
{

	All_Init();
	while(1)    
    {
		//printf("working\r\n");
        delay_ms(100);
	}
}

void All_Init(void)
{
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
	usart1_Init(115200);
	delay_Init();
	LED_Init();
    Encoder_Init_TIM4();
    MotorIO_Init();
    TIM2_PWM_Init(1999,719);
    MotorSetZero();
    TIM3_Init(499,7199);    
}
