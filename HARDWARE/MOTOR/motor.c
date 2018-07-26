#include "motor.h"
#include "tim2.h"


void MotorIO_Init(void)
{
    GPIO_InitTypeDef GPIO_InitStructure;
	
	RCC_APB2PeriphClockCmd(MotorIN1_RCC|MotorIN2_RCC,ENABLE);
	
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_InitStructure.GPIO_Pin = MotorIN1_PIN;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	
	GPIO_Init(MotorIN1_PORT,&GPIO_InitStructure);
    
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_InitStructure.GPIO_Pin = MotorIN2_PIN;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	
	GPIO_Init(MotorIN2_PORT,&GPIO_InitStructure);
    
    MotorIN1_OUT = 1;
    MotorIN2_OUT = 1;
	
}


void SetMotor(int16_t moto)
{
    if(moto >= 0)
    {
        SetMotorForward;
    }else
    {
        SetMotorReverse;
        moto = -moto;
    }
    
    SetPwmValu(moto);
}

