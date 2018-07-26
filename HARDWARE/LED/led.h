#ifndef _LED_H_
#define _LED_H_
#include "sys.h"

#define LED0_Port   GPIOA
#define LED0_RCC    RCC_APB2Periph_GPIOA
#define LED0_Pin    GPIO_Pin_8

#define LED1_Port   GPIOD
#define LED1_RCC	RCC_APB2Periph_GPIOD
#define LED1_Pin    GPIO_Pin_2

#define LED0 PAout(8)
#define LED1 PDout(2)

void LED_Init(void);


#endif

