/*
*文件名：滴答定时器延时配置文件
*功  能：源文件
*作  者：程晓强
*/
#include "delay.h"

static u8  fac_us=0;											//us延时倍乘数			   
static u16 fac_ms=0;											//ms延时倍乘数,在ucos下,代表每个节拍的ms数

/*
*函数名：延时初始化函数
*参	 数：无
*返回值：无
*作  者：程晓强
*/
void delay_Init(void)
{
	SysTick_CLKSourceConfig(SysTick_CLKSource_HCLK_Div8);		//选择外部时钟  HCLK/8
	fac_us=SystemCoreClock/8000000;								//为系统时钟的1/8  
	fac_ms=(u16)fac_us*1000;	
}
/*
*函数名：ms延时函数
*参	 数：u16 nms
*返回值：无
*作  者：程晓强
*/
void delay_ms(u16 nms)
{
	u32 temp;		   
	SysTick->LOAD=(u32)nms*fac_ms;								//时间加载(SysTick->LOAD为24bit)
	SysTick->VAL =0x00;											//清空计数器
	SysTick->CTRL|=SysTick_CTRL_ENABLE_Msk ;					//开始倒数  
	do
	{
		temp=SysTick->CTRL;
	}while((temp&0x01)&&!(temp&(1<<16)));						//等待时间到达   
	SysTick->CTRL&=~SysTick_CTRL_ENABLE_Msk;					//关闭计数器
	SysTick->VAL =0X00;     
}
/*
*函数名：ns延时函数
*参	 数：u16 nus
*返回值：无
*作  者：程晓强
*/
void delay_us(u32 nus)
{
	u32 temp;	    	 
	SysTick->LOAD=nus*fac_us; 									//时间加载	  		 
	SysTick->VAL=0x00;        									//清空计数器
	SysTick->CTRL|=SysTick_CTRL_ENABLE_Msk ;					//开始倒数	  
	do
	{
		temp=SysTick->CTRL;
	}while((temp&0x01)&&!(temp&(1<<16)));						//等待时间到达   
	SysTick->CTRL&=~SysTick_CTRL_ENABLE_Msk;					//关闭计数器
	SysTick->VAL =0X00;      		
}

