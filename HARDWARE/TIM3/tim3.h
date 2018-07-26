/*
*文件名：定时器3配置文件
*功  能：头文件
*作  者：程晓强
*之前要先进行中断优先级分组：NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
*初始化函数：TIM3_Init(9,7199);ms定时器
*/
#ifndef _TIM3_H_
#define _TIM3_H_
#include "sys.h"


void TIM3_Init(u16 arr,u16 psc);

#endif

