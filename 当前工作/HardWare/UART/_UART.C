#define De_UART_Compiler
#include "UART.h"
#ifdef	De_Compiler_HardWare_UART
/*=====================================================================================*/	
//程序里面未加入，在读串口与写串口是获取当前任务号与OPEN时获取到的任务号进行对比
/*====================================================================================*/		
static uint16 Init(uint8 ComNumber)						//初始化串口
{	if(ComNumber==De_Uart_Port_0)
	{	
		#ifdef OS_ADD              
		if(Uart0UseSem==NULL)
		{	
			Uart0UseSem=OSSemCreate(1); 		//申请一个信号量					
			if(Uart0UseSem == NULL)
				return De_Erro_Uart_Init_0;
		}
		#endif
		#ifdef OS_Message_Uart0			
		if(Uart0RxSem==NULL)
		{	Uart0RxSem=OSSemCreate(0); 					
			if(Uart0RxSem == NULL)
				return De_Erro_Uart_Init_0;
		}
		#endif		
				
	}
	else if(ComNumber==De_Uart_Port_1)
	{	
		#ifdef OS_ADD              
		if(Uart1UseSem==NULL)
		{	Uart1UseSem=OSSemCreate(1); 					
			if(Uart1UseSem == NULL)
				return De_Erro_Uart_Init_1;	
		}
		#endif
		#ifdef OS_Message_Uart1	
		if(Uart1RxSem==NULL)		
		{	Uart1RxSem=OSSemCreate(0); 					
			if(Uart1RxSem == NULL)
				return De_Erro_Uart_Init_1;	
		}
		#endif		
	}
	else if(ComNumber==De_Uart_Port_2)
	{	
		#ifdef OS_ADD              
		if(Uart2UseSem==NULL)
		{	Uart2UseSem=OSSemCreate(1); 					
			if(Uart2UseSem == NULL)
				return De_Erro_Uart_Init_2;
		}
		#endif
		#ifdef OS_Message_Uart2	
		if(Uart2RxSem==NULL)	
		{	Uart2RxSem=OSSemCreate(0); 					
			if(Uart2RxSem == NULL)
				return De_Erro_Uart_Init_2;	
		}
		#endif		
	}
	else if(ComNumber==De_Uart_Port_3)
	{	
		#ifdef OS_ADD              
		if(Uart3UseSem==NULL)
		{	Uart3UseSem=OSSemCreate(1); 					
			if(Uart3UseSem == NULL)
				return De_Erro_Uart_Init_3;	
		}
		#endif
		#ifdef OS_Message_Uart3
		if(Uart3RxSem==NULL)
		{	Uart3RxSem=OSMboxCreate(0); 					
			if(Uart3RxSem == NULL)
				return De_Erro_Uart_Init_3;	
		}
		#endif		
	}
	else if(ComNumber==De_Uart_Port_4)
	{	
		#ifdef OS_ADD              
		if(Uart4UseSem==NULL)
		{	Uart4UseSem=OSSemCreate(1); 					
			if(Uart4UseSem == NULL)
				return De_Erro_Uart_Init_4;	
		}
		#endif
		#ifdef OS_Message_Uart4
		if(Uart4RxSem==NULL)
		{	Uart4RxSem=OSMboxCreate(0); 					
			if(Uart4RxSem == NULL)
				return De_Erro_Uart_Init_4;	
		}
		#endif		
	}
	else 
	{	return 	De_Erro_Uart_NoPort;
	}
	return De_Suc_Uart;
}

static uint16 Open(uint8 ComNumber,st_Da_Uart	*ptst_Da_Uart)
{	if(ComNumber==De_Uart_Port_0)
		return Open0(ptst_Da_Uart);
	else if(ComNumber==De_Uart_Port_1)
		return Open1(ptst_Da_Uart);
	else if(ComNumber==De_Uart_Port_2)
		return Open2(ptst_Da_Uart);
	else if(ComNumber==De_Uart_Port_3)
		return Open3(ptst_Da_Uart);
	else if(ComNumber==De_Uart_Port_4)
		return Open4(ptst_Da_Uart);
	else
		return De_Erro_Uart_NoPort;
}

static uint16 Close(uint8 ComNumber)
{	if(ComNumber==De_Uart_Port_0)
		return Close0();
	else if(ComNumber==De_Uart_Port_1)
		return Close1();
	else if(ComNumber==De_Uart_Port_2)
		return Close2();
	else if(ComNumber==De_Uart_Port_3)
		return Close3();
	else if(ComNumber==De_Uart_Port_4)
		return Close4();
	else
		return De_Erro_Uart_NoPort;
}

static uint16 Read(uint8 ComNumber,uint8 *Data,uint16 DataLen)
{	if(ComNumber==De_Uart_Port_0)
		return Read0(Data,DataLen);	
	else if(ComNumber==De_Uart_Port_1)
		return Read1(Data,DataLen);
	else if(ComNumber==De_Uart_Port_2)
		return Read2(Data,DataLen);
	else if(ComNumber==De_Uart_Port_3)
		return Read3(Data,DataLen);
	else if(ComNumber==De_Uart_Port_4)
		return Read4(Data,DataLen);
	else
		return De_Erro_Uart_NoPort;
}

static uint16 Write(uint8 ComNumber,uint8 *Data,uint16 DataLen)
{	if(ComNumber==De_Uart_Port_0)
		return Write0(Data,DataLen);
	else if(ComNumber==De_Uart_Port_1)
		return Write1(Data,DataLen);		
	else if(ComNumber==De_Uart_Port_2)
		return Write2(Data,DataLen);		
	else if(ComNumber==De_Uart_Port_3)
		return Write3(Data,DataLen);
	else if(ComNumber==De_Uart_Port_4)
		return Write4(Data,DataLen);		
	else
		return De_Erro_Uart_NoPort;
}

/*=====================================串口0==========================================*/

static uint16 Open0(st_Da_Uart	*ptst_Da_Uart)					//打开一个串口
{	uint16 Fdiv;
	uint8 err;
	uint8 a;
	if((ptst_Da_Uart->BaudRate<300)||(ptst_Da_Uart->BaudRate>115200))
		return De_Erro_Uart_BaudRate;			//波特率不适合
	if((ptst_Da_Uart->DataBit<4)||(ptst_Da_Uart->DataBit>8))
		return De_Erro_Uart_BaudRate;			//数据位不适合
	if((ptst_Da_Uart->StopBit==0)||(ptst_Da_Uart->StopBit>2))	 //停止位选择
		return De_Erro_Uart_StopBit;
	if(ptst_Da_Uart->Parity>2)	   							//奇偶校验
		return De_Erro_Uart_Parity;	
	U0IER =0x00;
	#ifdef OS_ADD
	OSSemPend(Uart0UseSem, 0, &err);
	#endif
	#ifdef OS_Message_Uart0
	ClearSem(Uart0RxSem);					//清空信号量
	#endif
	UART0_RxHead=UART0_RxTail=0;
	UART4_RxHead=UART4_RxTail=0;
	De_Uart_Port0_Power_up;
   	De_Uart_OpenIO_0;
    PINSEL0 = (PINSEL0 & 0xffffff0f) | 0x50;    /* 选择管脚为UART0 */

	// 选择管脚为UART0 //                             
	U0LCR = 0x83;                               // 允许访问分频因子寄存器 //
	Fdiv = (Fpclk / 16) /(ptst_Da_Uart->BaudRate);                  // 设置波特率 //
    U0DLM = Fdiv / 256;       
 	U0DLL = Fdiv % 256;                         // 禁止访问分频因子寄存器 //
	U0LCR = 0x03;
	a=ptst_Da_Uart->DataBit-5;
	U0LCR=((U0LCR&0xfc)|a);	  					//数据位
	a=((ptst_Da_Uart->StopBit-1)<<2);		
    U0LCR=((U0LCR&0xfb)|a);	  					//停止位
	U0LCR&=0xf7;
	if(ptst_Da_Uart->Parity>0)
	{	U0LCR|=0x08;
		a=((ptst_Da_Uart->Parity-1)<<4);
		U0LCR=((U0LCR&0xcf)|a);
	}                                            
	U0FCR = 0x07;                         // 使能FIFO，并设置触发点为8字节
	U0LCR = 0x03;
	ptUart0ReBuf=(uint8 *)De_Uart0Ram;
	
	//install_irq(UART0_INT,(void *)IRQ_UART0,1);	
	U0IER = 0x01;                     // 允许RBR中断，即接收中断 
	return De_Suc_Uart;  
}

static uint16 Close0(void)
{	U0IER=0x00;
	#ifdef OS_ADD
	ClearSem(Uart0UseSem);
	#endif

	UART0_RxHead=UART0_RxTail=0;	
	De_Uart_Port0_Power_Down;
	#ifdef OS_ADD
	OSSemPost(Uart0UseSem);			//交出使用权
	#endif
	return De_Suc_Uart;
}

static uint16 Read0(uint8 *Data,uint16 DataLen)
{	uint16 i;
	uint8 ByteV;
	for(i=0;i<DataLen;i++)
	{	if(Receive0Byte(&ByteV)!=De_Suc_Uart)
			break;
		Data[i]=ByteV;
	}
    return i;
}
static uint16 Write0(uint8 *Data,uint16 DataLen)
{	uint16 i;
	for(i=0;i<DataLen;i++)
	{	U0THR = Data[i];
		while( (U0LSR&0x40)==0); 
	}
	return De_Suc_Uart;
}

												                                                                                                                                                                
static uint16 Receive0Byte(uint8 *ByteV)
{	if(UART0_RxHead==UART0_RxTail)				//缓冲区没有数据
		return De_Erro_Uart0_NoData;
	*ByteV=ptUart0ReBuf[UART0_RxHead];
	UART0_RxHead++;
	if(UART0_RxHead==De_Uart_RecMaxSize)
		UART0_RxHead=0;
	return De_Suc_Uart;				
}  

/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++串口2++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/
static uint16 Open1(st_Da_Uart	*ptst_Da_Uart)					//打开一个串口
{	uint16 Fdiv;
	uint8 err;
	uint8 a;
	if((ptst_Da_Uart->BaudRate<300)||(ptst_Da_Uart->BaudRate>115200))
		return De_Erro_Uart_BaudRate;			//波特率不适合
	if((ptst_Da_Uart->DataBit<4)||(ptst_Da_Uart->DataBit>8))
		return De_Erro_Uart_BaudRate;			//数据位不适合
	if((ptst_Da_Uart->StopBit==0)||(ptst_Da_Uart->StopBit>2))	 //停止位选择
		return De_Erro_Uart_StopBit;
	if(ptst_Da_Uart->Parity>2)	   							//奇偶校验
		return De_Erro_Uart_Parity;	
	U1IER =0x00;
	#ifdef OS_ADD
	OSSemPend(Uart1UseSem, 0, &err);
	#endif
	#ifdef OS_Message_Uart1
	ClearSem(Uart1RxSem);					//清空信号量
	#endif
	UART1_RxHead=UART1_RxTail=0;
	De_Uart_Port1_Power_up;
   	De_Uart_OpenIO_1;


	
	    // 选择管脚为UART0 //                             
	U1LCR = 0x83;                               // 允许访问分频因子寄存器 //
	Fdiv = (Fpclk / 16) /(ptst_Da_Uart->BaudRate);                  // 设置波特率 //
    U1DLM = Fdiv / 256;       
 	U1DLL = Fdiv % 256;                         // 禁止访问分频因子寄存器 //
	U1LCR = 0x03;
	a=ptst_Da_Uart->DataBit-5;
	U1LCR=((U1LCR&0xfc)|a);	  					//数据位
	a=((ptst_Da_Uart->StopBit-1)<<2);		
    U1LCR=((U1LCR&0xfb)|a);	  					//停止位
	U1LCR&=0xf7;
	if(ptst_Da_Uart->Parity>0)
	{	U1LCR|=0x08;
		a=((ptst_Da_Uart->Parity-1)<<4);
		U1LCR=((U1LCR&0xcf)|a);
	}                                            
	U1FCR = 0x07;                         // 使能FIFO，并设置触发点为8字节
	//U0LCR = 0x03;
	ptUart1ReBuf=(uint8 *)De_Uart1Ram;
	//install_irq(UART0_INT,(void *)IRQ_UART0,1);	
	U1IER = 0x01;                     // 允许RBR中断，即接收中断 
	return De_Suc_Uart;  
}

static uint16 Close1(void)
{	U1IER = 0x00;
	#ifdef OS_ADD
	ClearSem(Uart1UseSem);
	#endif
	//U0IER |= (~0x01);
	UART1_RxHead=UART1_RxTail=0;	
	De_Uart_Port1_Power_Down;
	#ifdef OS_ADD
	OSSemPost(Uart1UseSem);			//交出使用权
	#endif
	return De_Suc_Uart;
}

static uint16 Read1(uint8 *Data,uint16 DataLen)
{	uint16 i;
	uint8 ByteV;
	for(i=0;i<DataLen;i++)
	{	if(Receive1Byte(&ByteV)!=De_Suc_Uart)
			break;
		Data[i]=ByteV;
	}
    return i;
}
static uint16 Write1(uint8 *Data,uint16 DataLen)
{	uint16 i;
	for(i=0;i<DataLen;i++)
	{	U1THR = Data[i];
		while( (U1LSR&0x40)==0); 
	}
	return De_Suc_Uart;
}

												                                                                                                                                                                
static uint16 Receive1Byte(uint8 *ByteV)
{	if(UART1_RxHead==UART1_RxTail)				//缓冲区没有数据
		return De_Erro_Uart1_NoData;
	*ByteV=ptUart1ReBuf[UART1_RxHead];
	UART1_RxHead++;
	if(UART1_RxHead==De_Uart_RecMaxSize)
		UART1_RxHead=0;
	return De_Suc_Uart;				
}  


/*=============================================================串口2==============================================================================*/
static uint16 Open2(st_Da_Uart	*ptst_Da_Uart)					//打开一个串口
{	uint16 Fdiv;
	uint8 err;
	uint8 a;
	if((ptst_Da_Uart->BaudRate<300)||(ptst_Da_Uart->BaudRate>115200))
		return De_Erro_Uart_BaudRate;			//波特率不适合
	if((ptst_Da_Uart->DataBit<4)||(ptst_Da_Uart->DataBit>8))
		return De_Erro_Uart_BaudRate;			//数据位不适合
	if((ptst_Da_Uart->StopBit==0)||(ptst_Da_Uart->StopBit>2))	 //停止位选择
		return De_Erro_Uart_StopBit;
	if(ptst_Da_Uart->Parity>2)	   							//奇偶校验
		return De_Erro_Uart_Parity;	
	U2IER =0x00;
	#ifdef OS_ADD
	OSSemPend(Uart2UseSem, 0, &err);
	#endif
	#ifdef OS_Message_Uart2
	ClearSem(Uart2RxSem);					//清空信号量
	#endif
	UART2_RxHead=UART2_RxTail=0;
	De_Uart_Port2_Power_up;
   	De_Uart_OpenIO_2;


	
	    // 选择管脚为UART0 //                             
	U2LCR = 0x83;                               // 允许访问分频因子寄存器 //
	Fdiv = (Fpclk / 16) /(ptst_Da_Uart->BaudRate);                  // 设置波特率 //
    U2DLM = Fdiv / 256;       
 	U2DLL = Fdiv % 256;                         // 禁止访问分频因子寄存器 //
	U2LCR = 0x03;
	a=ptst_Da_Uart->DataBit-5;
	U2LCR=((U2LCR&0xfc)|a);	  					//数据位
	a=((ptst_Da_Uart->StopBit-1)<<2);		
    U2LCR=((U2LCR&0xfb)|a);	  					//停止位
	U2LCR&=0xf7;
	if(ptst_Da_Uart->Parity>0)
	{	U2LCR|=0x08;
		a=((ptst_Da_Uart->Parity-1)<<4);
		U2LCR=((U2LCR&0xcf)|a);
	}                                            
	U2FCR = 0x07;                         // 使能FIFO，并设置触发点为8字节
	U2LCR = 0x03;
	ptUart2ReBuf=(uint8 *)De_Uart2Ram;
	//Install_IRQ(UART2_INT,(void *)IRQ_UART2,1);
	//install_irq(UART0_INT,(void *)IRQ_UART0,1);	
	U2IER = 0x01;                     // 允许RBR中断，即接收中断 
	return De_Suc_Uart;  
}

static uint16 Close2(void)
{	U2IER=0x00;
	#ifdef OS_ADD
	ClearSem(Uart2UseSem);
	#endif
	UART2_RxHead=UART2_RxTail=0;	
	De_Uart_Port2_Power_Down;
	#ifdef OS_ADD
	OSSemPost(Uart2UseSem);			//交出使用权
	#endif
	return De_Suc_Uart;
}

static uint16 Read2(uint8 *Data,uint16 DataLen)
{	uint16 i;
	uint8 ByteV;
	for(i=0;i<DataLen;i++)
	{	if(Receive2Byte(&ByteV)!=De_Suc_Uart)
			break;
		Data[i]=ByteV;
	}
    return i;
}
static uint16 Write2(uint8 *Data,uint16 DataLen)
{	uint16 i;
	for(i=0;i<DataLen;i++)
	{	U2THR = Data[i];
		while( (U2LSR&0x40)==0); 
	}
	return De_Suc_Uart;
}

												                                                                                                                                                                
static uint16 Receive2Byte(uint8 *ByteV)
{	if(UART2_RxHead==UART2_RxTail)				//缓冲区没有数据
		return De_Erro_Uart2_NoData;
	*ByteV=ptUart2ReBuf[UART2_RxHead];
	UART2_RxHead++;
	if(UART2_RxHead==De_Uart_RecMaxSize)
		UART2_RxHead=0;
	return De_Suc_Uart;				
}

/*============================================================串口3=========================================================================*/
static uint16 Open3(st_Da_Uart	*ptst_Da_Uart)					//打开一个串口
{	uint16 Fdiv;
	uint8 err;
	uint8 a;
	if((ptst_Da_Uart->BaudRate<300)||(ptst_Da_Uart->BaudRate>115200))
		return De_Erro_Uart_BaudRate;			//波特率不适合
	if((ptst_Da_Uart->DataBit<4)||(ptst_Da_Uart->DataBit>8))
		return De_Erro_Uart_BaudRate;			//数据位不适合
	if((ptst_Da_Uart->StopBit==0)||(ptst_Da_Uart->StopBit>2))	 //停止位选择
		return De_Erro_Uart_StopBit;
	if(ptst_Da_Uart->Parity>2)	   							//奇偶校验
		return De_Erro_Uart_Parity;	
	U3IER =0x00;
	#ifdef OS_ADD
	OSSemPend(Uart3UseSem, 0, &err);
	#endif
	#ifdef OS_Message_Uart3
	ClearSem(Uart3RxSem);					//清空信号量
	#endif
	UART3_RxHead=UART3_RxTail=0;
	De_Uart_Port3_Power_up;
   	De_Uart_OpenIO_3;
    //PINSEL0 = (PINSEL0 & 0xffffff0f) | 0x50;    /* 选择管脚为UART0 */


	
	    // 选择管脚为UART0 //                             
	U3LCR = 0x83;                               // 允许访问分频因子寄存器 //
	Fdiv = (Fpclk / 16) /(ptst_Da_Uart->BaudRate);                  // 设置波特率 //
    U3DLM = Fdiv / 256;       
 	U3DLL = Fdiv % 256;                         // 禁止访问分频因子寄存器 //
	U3LCR = 0x03;
	a=ptst_Da_Uart->DataBit-5;
	U3LCR=((U3LCR&0xfc)|a);	  					//数据位
	a=((ptst_Da_Uart->StopBit-1)<<2);		
    U3LCR=((U3LCR&0xfb)|a);	  					//停止位
	U3LCR&=0xf7;
	if(ptst_Da_Uart->Parity>0)
	{	U3LCR|=0x08;
		a=((ptst_Da_Uart->Parity-1)<<4);
		U3LCR=((U3LCR&0xcf)|a);
	}                                            
	U3FCR = 0x07;                         // 使能FIFO，并设置触发点为8字节
	U3LCR = 0x0B;
	ptUart3ReBuf=(uint8 *)De_Uart3Ram;
	
	//install_irq(UART0_INT,(void *)IRQ_UART0,1);	
	U3IER = 0x01;                     // 允许RBR中断，即接收中断 
	return De_Suc_Uart;  
}

static uint16 Close3(void)
{	U3IER=0x00;
	#ifdef OS_ADD
	ClearSem(Uart3UseSem);
	#endif
	UART3_RxHead=UART3_RxTail=0;	
	De_Uart_Port3_Power_Down;
	#ifdef OS_ADD
	OSSemPost(Uart3UseSem);			//交出使用权
	#endif
	return De_Suc_Uart;
}

static uint16 Read3(uint8 *Data,uint16 DataLen)
{	uint16 i;
	uint8 ByteV;
	for(i=0;i<DataLen;i++)
	{	if(Receive3Byte(&ByteV)!=De_Suc_Uart)
			break;
		Data[i]=ByteV;
	}
    return i;
}
static uint16 Write3(uint8 *Data,uint16 DataLen)
{	uint16 i;
	for(i=0;i<DataLen;i++)
	{	U3THR = Data[i];
		while( (U3LSR&0x40)==0); 
	}
	return De_Suc_Uart;
}

												                                                                                                                                                                
static uint16 Receive3Byte(uint8 *ByteV)
{	if(UART3_RxHead==UART3_RxTail)				//缓冲区没有数据
		return De_Erro_Uart3_NoData;
	*ByteV=ptUart3ReBuf[UART3_RxHead];
	UART3_RxHead++;
	if(UART3_RxHead==De_Uart_RecMaxSize)
		UART3_RxHead=0;
	return De_Suc_Uart;				
}

/*============================================================串口4=========================================================================*/
static uint16 Open4(st_Da_Uart	*ptst_Da_Uart)					//打开一个串口
{	uint8 err;
	if((ptst_Da_Uart->BaudRate<300)||(ptst_Da_Uart->BaudRate>115200))
		return De_Erro_Uart_BaudRate;			//波特率不适合
	if((ptst_Da_Uart->DataBit<4)||(ptst_Da_Uart->DataBit>8))
		return De_Erro_Uart_BaudRate;			//数据位不适合
	if((ptst_Da_Uart->StopBit==0)||(ptst_Da_Uart->StopBit>2))	 //停止位选择
		return De_Erro_Uart_StopBit;
	if(ptst_Da_Uart->Parity>2)	   							//奇偶校验
		return De_Erro_Uart_Parity;
	switch(ptst_Da_Uart->BaudRate)
    {	case 2400:
			Uart4BaudRate=De_Uart_Br_2400;
		break;
		case 4800:
			Uart4BaudRate=De_Uart_Br_4800;
		break;
		case 9600:
			Uart4BaudRate=De_Uart_Br_9600;
		break;
		case 19200:
			Uart4BaudRate=De_Uart_Br_19200;
		break;
		case 38400:
			Uart4BaudRate=De_Uart_Br_38400;
		break;
		case 43000:
			Uart4BaudRate=De_Uart_Br_43000;
		break;
		case 56000:
			Uart4BaudRate=De_Uart_Br_56000;
		break;
		case 57600:
			Uart4BaudRate=De_Uart_Br_57600;
		break;
		case 115200:
			Uart4BaudRate=De_Uart_Br_115200;
		break;
	}
	
	#ifdef OS_ADD
	OSSemPend(Uart4UseSem, 0, &err);
	#endif
	#ifdef OS_Message_Uart3
	ClearSem(Uart4RxSem);					//清空信号量
	#endif
	UART4_RxHead=UART4_RxTail=0;
	De_Uart_Send_Up;
	PCONP=(PCONP|0X00000004);
	T1IR = 0xffffffff;
    T1TC = 0;
    T1TCR = 0x00;
    T1MCR = 0x03;
    T1MR0 = Uart4BaudRate;

	PCONP=(PCONP|0X00400000);
	T2IR = 0xffffffff;
    T2TC = 0;
    T2TCR = 0x00;
    T2MCR = 0x03;
    T2MR0 = Uart4BaudRate;

	PINSEL4 |= 0x01000000;	/* set P2.12 as EINT0 andP2.0~7 GPIO output */
	IO2_INT_EN_F |= 0x1000;	/* Port2.10 is falling edge. */
    EXTMODE = 0x00000004;	/* INT0 edge trigger */
    EXTPOLAR = 0;

	return De_Suc_Uart; 
}
static uint16 Close4(void)
{
	T1TCR = 0;
	T2TCR = 0;
	IO2_INT_EN_F &= (~0x1000);
	return De_Suc_Uart;	
}
static uint16 Read4(uint8 *Data,uint16 DataLen)
{	uint16 i;
	uint8 ByteV;
	for(i=0;i<DataLen;i++)
	{	if(Receive4Byte(&ByteV)!=De_Suc_Uart)
			break;
		Data[i]=ByteV;
	}
    return i;
}
static uint16 Write4(uint8 *Data,uint16 DataLen)
{	uint16 i;
	for(i=0;i<DataLen;i++)
	{	ByteSend = Data[i];
		De_Uart_Send_Down;
		BitCountSend=1;
		T2TCR = 0x01;
		while( BitCountSend!=0);
	}
	return De_Suc_Uart;
}
static uint16 Receive4Byte(uint8 *ByteV)
{	if(UART4_RxHead==UART4_RxTail)				//缓冲区没有数据
		return De_Erro_Uart4_NoData;
	*ByteV=ptUart4ReBuf[UART4_RxHead];
	UART4_RxHead++;
	if(UART4_RxHead==De_Uart_RecMaxSize)
		UART4_RxHead=0;
	return De_Suc_Uart;				
}



static uint16 ClearSem(OS_EVENT	*UartSem)
{	
	OS_SEM_DATA 	SemData;
	uint8 err;
	for(;;)
	{	if(OSSemQuery(UartSem, &SemData)!=OS_NO_ERR)
			return 1;
		if(SemData.OSCnt == 0)		//有信号要接受
			return De_Suc_Uart;	
		OSSemPend(UartSem, 1, &err);
	}
}


/*---------------------------------------中断处理函数-----------------------------------------------------*/
void Eint_Exception(void)
{	EXTINT = 0x00000004;
	if(FIO2PIN1&0x10)
	{	VICVectAddr = 0;
		return;
	}
	IO2_INT_EN_F &= (~0x1000);//VICIntEnClr = (1 << EINT2_INT);
	T1TC = 0;
	BitCount=0;
	AgreeByte=0;
	T1MR0 = Uart4BaudRate+(Uart4BaudRate>>4);	
	T1TCR = 1;	
	PINSEL4 &= 0xfcffffff;
		
    VICVectAddr = 0;            //interrupt close 通知中断控制器中断结束

}
void Timer1_Exception(void)
{	T1IR = 0x01;
	T1TC = 0; 
	BitCount++;
	

	T1MR0 = Uart4BaudRate;
	AgreeByte|=(((FIO2PIN1>>4)&0x01)<<(BitCount-1));
	if(BitCount<9)
	{	
		VICVectAddr = 0;
		return ;
	}
	PINSEL4 |= 0x01000000;
	EXTINT = 0x00000004;
	IO2_INT_EN_F |= 0x1000;//VICIntEnable = (1 << EINT2_INT);
	VICVectAddr = 0;
	T1TCR |= 0x02;
	T1TCR = 0;
	ptUart4ReBuf[UART4_RxTail++]=AgreeByte;
	if(UART4_RxTail==De_Uart_RecMaxSize)
		UART4_RxTail=0;         //interrupt close 通知中断控制器中断结束

}
void Timer2_Exception(void)
{	
	T2IR = 0x01;
//	set_timer2(Uart4BaudRate);
	BitCountSend++;
	if(BitCountSend>9)
	{
		De_Uart_Send_Up;
		if(BitCountSend>=13)
		{	BitCountSend=0;
			T2TCR = 0;	
		}
	}
	else
	{
		if(ByteSend&(1<<(BitCountSend-2)))
		{	De_Uart_Send_Up;  }
		else
		{	De_Uart_Send_Down;}	
	}
	T2TC = 0;
	VICVectAddr = 0;            //interrupt close 通知中断控制器中断结束
}


void UART0_Exception(void)
{
	INT8U iir;
	INT8U rdat;
	//static INT8U  counter = 0;		
	iir = U0IIR;   //清中断
	switch(iir & 0x0f)
	{
	  case 0x06://线状态中断
		break;
	  case 0x02://发送中断
		break;
	  case 0x04://接收中断
	  case 0x0c://字符超时中断
	  	   //U0IER = 0x00;
		   while((U0LSR&0X01)==1)
		   {		rdat = U0RBR; 
		   		ptUart0ReBuf[UART0_RxTail++]=rdat;
					if(UART0_RxTail==De_Uart_RecMaxSize)
					UART0_RxTail=0;				   	    
			}
		break;
	  default:
		break;
	}
	#ifdef OS_Message_Uart0
	OSSemPost(Uart0RxSem);
	#endif
	

	U0IER = 0x01; 
	VICVectAddr = 0x00;   //中断处理结束	
}	 

void UART1_Exception(void)
{
	INT8U iir;
	INT8U rdat;
	//static INT8U  counter = 0;		
	iir = U1IIR;   //清中断
	switch(iir & 0x0f)
	{
	  case 0x06://线状态中断
		break;
	  case 0x02://发送中断
		break;
	  case 0x04://接收中断
	  case 0x0c://字符超时中断
	  	   //U0IER = 0x00;
		   while((U1LSR&0X01)==1)
		   {		rdat = U1RBR; 
		   		ptUart1ReBuf[UART1_RxTail++]=rdat;
					if(UART1_RxTail==De_Uart_RecMaxSize)
					UART1_RxTail=0;				   	    
			}
		break;
	  default:
		break;
	}
	#ifdef OS_Message_Uart1
	OSSemPost(Uart1RxSem);
	#endif	
	 U1IER = 0x01; 
	 VICVectAddr = 0x00;   //中断处理结束
	 	
	
}

void UART2_Exception(void)
{
	INT8U iir;
	INT8U rdat;
	//static INT8U  counter = 0;		
	iir = U2IIR;   //清中断
	switch(iir & 0x0f)
	{
	  case 0x06://线状态中断
		break;
	  case 0x02://发送中断
		break;
	  case 0x04://接收中断
	  case 0x0c://字符超时中断
	  	   //U0IER = 0x00;
		   while((U2LSR&0X01)==1)
		   {		rdat = U2RBR; 
		   		ptUart2ReBuf[UART2_RxTail++]=rdat;
					if(UART2_RxTail==De_Uart_RecMaxSize)
					UART2_RxTail=0;				   	    
			}
		break;
	  default:
		break;
	}
	#ifdef OS_Message_Uart2
	OSSemPost(Uart2RxSem);
	#endif	
	 U2IER = 0x01; 
	 VICVectAddr = 0x00;
	 	
}

void UART3_Exception(void)
{
	INT8U iir;
	INT8U rdat;
	//static INT8U  counter = 0;		
	iir = U3IIR;   //清中断
	switch(iir & 0x0f)
	{
	  case 0x06://线状态中断
		break;
	  case 0x02://发送中断
		break;
	  case 0x04://接收中断
	  case 0x0c://字符超时中断
	  	   //U0IER = 0x00;
		   while((U3LSR&0X01)==1)
		   {		rdat = U3RBR; 
		   		ptUart3ReBuf[UART3_RxTail++]=rdat;
					if(UART3_RxTail==De_Uart_RecMaxSize)
					UART3_RxTail=0;				   	    
			}
		break;
	  default:
		break;
	}
	#ifdef OS_Message_Uart3
	OSSemPost(Uart3RxSem);
	#endif	
	 U3IER = 0x01;
	 VICVectAddr = 0x00; 
	 	
	   //中断处理结束
}
#endif


