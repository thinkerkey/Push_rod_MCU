#ifndef _MOTOR_H_
#define _MOTOR_H_
#include "sys.h"

#define MotorIN1_RCC    RCC_APB2Periph_GPIOA
#define MotorIN1_PORT   GPIOA
#define MotorIN1_PIN    GPIO_Pin_2

#define MotorIN2_RCC    RCC_APB2Periph_GPIOA
#define MotorIN2_PORT   GPIOA
#define MotorIN2_PIN    GPIO_Pin_4

#define MotorIN1_OUT PAout(2)
#define MotorIN2_OUT PAout(4)

#define SetMotorForward {MotorIN1_OUT = 1;MotorIN2_OUT = 0;}
#define SetMotorReverse {MotorIN1_OUT = 0;MotorIN2_OUT = 1;}

#define LenAndPulseSwitchPar  0.09375f

void MotorIO_Init(void);
void SetMotor(int16_t moto);
//长度mm到脉冲数的转换  64个脉冲对应 6mm 
float LenAndPulseSwitch(int pulse);
void MotorSetZero(void);


#endif

