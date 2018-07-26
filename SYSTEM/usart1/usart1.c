/*
*文件名：串口1配置文件
*功  能：源文件
*作  者：程晓强
*/
#include "sys.h"
#include "usart1.h"
#include "tim3.h"

u8 USART1_RX_BUF[USART1_REC_LEN];     //接收缓冲数组
u16 USART1_RX_STA=0;					//接收状态标记

/***********支持printf（）函数*************/
struct __FILE 
{ 
	int handle; 

}; 

FILE __stdout;       
//定义_sys_exit()以避免使用半主机模式    
_sys_exit(int x) 
{ 
	x = x; 
} 
//重定义fputc函数 
int fputc(int ch, FILE *f)
{      
	while((USART1->SR&0X40)==0);//循环发送,直到发送完毕   
    USART1->DR = (u8) ch;      
	return ch;
}
/***********支持printf（）函数*************/

/*
*文件名：串口1初始化函数
*参	 数：u32 bound
*返回值：无
*作  者：程晓强
*/
void usart1_Init(u32 bound)
{
	GPIO_InitTypeDef USART1_GPIO;
	USART_InitTypeDef USART1_USART;
	NVIC_InitTypeDef USART1_NVIC;
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1|RCC_APB2Periph_GPIOA,ENABLE);   // 使能串口1和GPIOA的时钟
	
/****GPIO模式配置****/	
	USART1_GPIO.GPIO_Pin = GPIO_Pin_9;                                           //GPIOA.9	TX
	USART1_GPIO.GPIO_Mode = GPIO_Mode_AF_PP;									 //复用推挽输出
	USART1_GPIO.GPIO_Speed = GPIO_Speed_50MHz;
 	GPIO_Init(GPIOA,&USART1_GPIO);
	
	USART1_GPIO.GPIO_Pin = GPIO_Pin_10;											 //GPIOA.10  RX 
	USART1_GPIO.GPIO_Mode = GPIO_Mode_IN_FLOATING;								 //浮空输入
	GPIO_Init(GPIOA,&USART1_GPIO);
	
/***串口1配置***/
	USART1_USART.USART_BaudRate = bound;										//串口波特率
	USART1_USART.USART_HardwareFlowControl = USART_HardwareFlowControl_None;	//无硬件数据流控制
	USART1_USART.USART_Mode = USART_Mode_Rx|USART_Mode_Tx;						//收发模式
	USART1_USART.USART_Parity = USART_Parity_No;								//无奇偶校验位
	USART1_USART.USART_StopBits = USART_StopBits_1;								//一个停止位
	USART1_USART.USART_WordLength = USART_WordLength_8b;						//8位数据格式
	
	USART_Init(USART1,&USART1_USART);											//串口1初始化
	USART_ITConfig(USART1,USART_IT_RXNE,ENABLE);								//开启串口接收中断
	USART_Cmd(USART1,ENABLE);													//使能串口1
/***串口中断配置***/
	USART1_NVIC.NVIC_IRQChannel = USART1_IRQn;									//串口1中断通道
	USART1_NVIC.NVIC_IRQChannelCmd =ENABLE;										//中断使能
	USART1_NVIC.NVIC_IRQChannelPreemptionPriority=3 ;							//抢占优先级3
	USART1_NVIC.NVIC_IRQChannelSubPriority = 3;									//子优先级3
	NVIC_Init(&USART1_NVIC);
/***串口1初始化配置结束***/

}

/*
*文件名：串口1接收中断
*参	 数：无
*返回值：无
*作  者：程晓强
*/
uint8_t CmdReciveFromPc[2];
uint8_t ReciveOkFlag = 0;
void USART1_IRQHandler(void)
{
    static uint8_t cnt = 0;
	u8 Res;
	if(USART_GetITStatus(USART1, USART_IT_RXNE) != RESET)						//接收中断(接收到的数据必须是0x0d 0x0a结尾)
	{
		Res =USART_ReceiveData(USART1);											//读取接收到的数据
		if(Res == 0XAA)
        {
            cnt = 0;
            CmdReciveFromPc[cnt] = Res;
            cnt ++;
        }else{
            if(cnt == 1)
            {
                CmdReciveFromPc[cnt] = Res;
                cnt = 0;
                ReciveOkFlag = 1;
            }
        }
	} 
}
/*
*文件名：串口1打印函数
*参	 数：无
*返回值：无
*作  者：程晓强
*/
void u1_printf(char *string,u32 num)
{
	u1_PrintfStr(string);
	u1_PrintfNum(num);
	u1_Enter();
}

/*
*文件名：串口1打印字符函数
*参	 数：无
*返回值：无
*作  者：程晓强
*/
void u1_PrintfStr(char *string)
{
	while(*string){
		USART_SendData(USART1,*string++);
		while(USART_GetFlagStatus(USART1,USART_FLAG_TC)!=SET);
	}
}
/*
*文件名：串口1打印数字
*参	 数：无
*返回值：无
*作  者：程晓强
*/
void u1_PrintfNum(unsigned long dat)
{

	char temp[20];
	u32tostr(dat,temp);
	u1_PrintfStr(temp);
}

/**********************************************************
** 函数名:UART_Send_Enter
** 功能描述: 串口1发送一换行符
** 输入参数: 无
** 输出参数: 无
***********************************************************/
void u1_Enter(void)
{
	u1_PrintfStr("\r\n");
}

/**********************************************************
** 函数名:u32tostr
** 功能描述: 将一个32位的变量dat转为字符串，比如把1234转为"1234"
** 输入参数: dat:带转的long型的变量
             str:指向字符数组的指针，转换后的字节串放在其中 
** 输出参数: 无
***********************************************************/
void u32tostr(unsigned long dat,char *str) 
{
	char temp[20];
	unsigned char i=0,j=0;
	i=0;
	while(dat)
	{
		temp[i]=dat%10+0x30;
		i++;
		dat/=10;
	}
	j=i;
	for(i=0;i<j;i++)
	{
	  	str[i]=temp[j-i-1];
	}
	if(!i) {str[i++]='0';}
	str[i]=0;
}
/**********************************************************
** 函数名: strtou32
** 功能描述: 将一个字符串转为32位的变量，比如"1234"转为1234
** 输入参数: str:指向待转换的字符串     
** 输出参数: 无
** 返回：转换后的数值  
***********************************************************/
unsigned long strtou32(char *str) 
{
	unsigned long temp=0;
	unsigned long fact=1;
	unsigned char len=sizeof(str);
	unsigned char i;
	for(i=len;i>0;i--)
	{
		temp+=((str[i-1]-0x30)*fact);
		fact*=10;
	}
	return temp;
}

