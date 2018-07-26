#include "main.h"


void All_Init(void);

int main()
{

	All_Init();
	while(1)    
    {
        if(ReciveOkFlag)
        {
            ReciveOkFlag = 0;
            if(CmdReciveFromPc[1] == 0xff)
            {
                PoleDoMode = ModeUp;
                SetMotor(800);
            }else if(CmdReciveFromPc[1] == 0xf3)
            {
                PoleDoMode = ModeDown;
                SetMotor(-800);
            }else if(CmdReciveFromPc[1] == 0xf0)
            {
                PoleDoMode = ModePause;
                SetMotor(0);
            }else if(CmdReciveFromPc[1] == 0xf1)
            {
                PoleDoMode = ModeReset;
                MotorSetZero();
            }else
            {
                PoleDoMode = ModeSend;
                SetLenthFromPC = CmdReciveFromPc[1];
                if(SetLenthFromPC > 45)
                {
                    SetLenthFromPC = 45;
                }
            }
        }
	}
}

void All_Init(void)
{
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
	usart1_Init(115200);
	delay_Init();
	LED_Init();
    Encoder_Init_TIM4();
    MotorIO_Init();
    TIM2_PWM_Init(1999,719);
    MotorSetZero();
    TIM3_Init(499,7199);    
}
