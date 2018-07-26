/*
*文件名：滴答定时器延时配置文件
*功  能：头文件
*作  者：程晓强
*/
#ifndef _DELAY_H_
#define _DELAY_H_
#include "delay.h"
#include "sys.h"

void delay_Init(void);
void delay_ms(u16 nms);
void delay_us(u32 nus);

#endif
