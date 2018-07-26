#ifndef _ENCODE_H
#define _ENCODE_H

#include "sys.h"

extern float MotorAngle;

void Encoder_Init_TIM4(void);
int Read_Encoder(void);
float Read_MotorAngle(void);
int Read_Site(void);


#endif

