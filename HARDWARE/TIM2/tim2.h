/*
*文件名：PWM配置文件
*功  能：头文件
*作  者：程晓强
*之前要先进行中断优先级分组：NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
*初始化函数：TIM2_PWM_Init(199,7199);10MS方波
*/
#ifndef  _TIM2_H_
#define  _TIM2_H_
#include "sys.h"

void TIM2_Init(u16 arr,u16 psc);
void TIM2_PWM_Init(u16 arr,u16 psc);
void SetPwmValu(u16 moto);
#endif

