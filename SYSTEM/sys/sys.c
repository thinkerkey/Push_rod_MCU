/*
*文件名：系统文件 源文件
*功  能：宏定义IO
*作  者：程晓强
*/
#include "sys.h"

/***系统调用汇编相关函数***/

//采用如下方法实现执行汇编指令WFI 
void WFI_SET(void)
{
	__ASM volatile("wfi");		  
}

//关闭所有中断
void INTX_DISABLE(void)
{		  
	__ASM volatile("cpsid i");
}

//开启所有中断
void INTX_ENABLE(void)
{
	__ASM volatile("cpsie i");		  
}

//设置栈顶地址
//addr:栈顶地址
__asm void MSR_MSP(u32 addr) 
{
    MSR MSP, r0 			
    BX r14
}
