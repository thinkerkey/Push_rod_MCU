/*
*文件名：串口一配置文件
*功  能：头文件
*作  者：程晓强
*/

#ifndef _USART1_H_
#define _USART1_H_

#include "sys.h"
#include "stm32f10x.h"
#include "stdio.h"

#define USART1_REC_LEN  			200  			//定义最大接收字节数 200
#define EN_USART1_RX 			1				//使能（1）/禁止（0）串口1接收

extern u8  USART1_RX_BUF[USART1_REC_LEN]; 		//接收缓冲,最大USART_REC_LEN个字节.末字节为换行符 
extern u16 USART1_RX_STA;         				//接收状态标记

void usart1_Init(u32 bound);
void u1_PrintfStr(char *string);
void u1_Enter(void);
void u32tostr(unsigned long dat,char *str);
unsigned long strtou32(char *str);
void u1_PrintfNum(unsigned long dat);
void u1_printf(char *string,u32 num);
#endif

