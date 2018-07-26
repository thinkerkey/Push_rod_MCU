#include "motor.h"
#include "tim2.h"
#include "encoder.h"
#include "delay.h"


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

//长度mm到脉冲数的转换  64个脉冲对应 6mm 
float LenAndPulseSwitch(int pulse)
{
    return  pulse * LenAndPulseSwitchPar;
}

void MotorSetZero(void)
{
    uint8_t cnt = 0;
    int pulse = 0;
    SetMotor(-1900);
    while(cnt < 3)
    {
        delay_ms(100);
        pulse = Read_Encoder();
        if((pulse < 5) && (pulse > -5))
        {
            cnt ++;
        }
        
    }
    SetMotor(0);
    delay_ms(200);
    TIM4->CNT = 0;
}


