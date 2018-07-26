#include "main.h"


void all_Init(void);

int main()
{

	all_Init();
	while(1)    
    {
		printf("working\r\n");
        delay_ms(100);
	}
}

void all_Init(void)
{
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
	usart1_Init(115200);
	delay_Init();
	LED_Init();
    Encoder_Init_TIM4();
    MotorIO_Init();
    TIM2_PWM_Init(1999,71);
    TIM3_Init(499,7199);
    
    SetMotor(1000);
}
