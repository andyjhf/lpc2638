#define  De_UART_Compiler
#include "Spi.h"
#ifdef De_Compiler_HardWare_Spi 
 /*	函数功能：打开SPI口，此函数在运行之前必须打开
			返回值:	0:成功			非0	<见错误代码表>
*/
static uint16 Open(void)								//初始化SPI总线
{
	if(SPISem!=NULL)
		return De_Suc_Spi;
	PCONP|=(1<<21);
	PINSEL3|=(0X03<<8)|(0X03<<10)|(0X03<<14)|(0X03<<16);
	SSP0CR0=0X000000C7;
	SSP0CPSR=0X20;
	//S0SPCCR=0X02;
			
	
	SSP0CR1|=0X02;
    #ifdef OS_ADD
	UseSPITaskPro = OS_PRIO_SELF;              
	SPISem=OSSemCreate(1); 					//避免SPI总线多任务互斥,保证SPI总线在操作时候，就一个任务在用
	if(SPISem == NULL)
		return De_Erro_Spi_Open;	
	#endif
	return De_Suc_Spi;
}
/*	函数功能：开始SPI总线，获取到SPI的使用权
			入口参数:	输入参数	ChipSelect	使能SPI/CE选通	      函数指针
									ChipSelectOver	使能SPI/CE关闭    函数指针
			返回值:	0:成功			非0	<见错误代码表>							
		*/
static uint16 Start(void (*ChipSelect)(void),void (*ChipSelectOver)(void))
{	uint8 err;
    #ifdef OS_ADD
	OSSemPend(SPISem, 0, &err);				//等待释放SPI总线,如果其他任务正在使用，该任务挂起，等待释放
	UseSPITaskPro=OSPrioCur;				//获取当前运行任务号
	#endif
	ChipSelectOver();
	DelaySpi();
	while(SSP0SR&0x0c)
	{ 	err=SSP0DR;


	}
	ChipSelect();
	
	return De_Suc_Spi;
}
/*	函数功能：SPI总新写的时候，同时接受
			入口参数:	输入参数	wBuf		所写的数据地址
									SizeofBuf	所写的数据量
						输出参数	rBuf		所读的数据地址，所读的数据量与所写的数据量一样
			返回值:	0:成功			非0	<见错误代码表>							
		*/
static uint16 RwSpi(uint8 *wBuf,uint8 *rBuf,uint16 SizeofBuf)
{	uint16 i;
	#ifdef OS_ADD
	if(UseSPITaskPro!=OSPrioCur)  //不是开始的任务在调用
		return	De_Erro_Spi_Task; 
	#endif
	while(SSP0SR&0x0c)
	{	i=SSP0DR;


	}
	for(i=0;i<SizeofBuf;i++)
	{	while((SSP0SR&0X12)==0X00);
		SSP0DR=wBuf[i];
		while((SSP0SR&0X17)!=0x07);
		//				  N
		rBuf[i]=SSP0DR;
	}
	return De_Suc_Spi;
}
/*	函数功能：向SPI总线上写数据
			入口参数:	输入参数	Buf			所写的数据地址
									SizeofBuf	所写的数据量
			返回值:	0:成功			非0	<见错误代码表>							
		*/
static uint16 Write(uint8 *Buf,uint16 SizeofBuf)
{	uint16 i;
	uint8 a;
	#ifdef OS_ADD
	if(UseSPITaskPro!=OSPrioCur)  //不是开始的任务在调用
		return	De_Erro_Spi_Task; 
	#endif
	for(i=0;i<SizeofBuf;i++)
	{	while((SSP0SR&0X12)==0X00);
		SSP0DR=Buf[i];
		while((SSP0SR&0X17)!=0x07);
		a=SSP0DR;
	}
	return De_Suc_Spi;
}
/*	函数功能：读取SPI总线的数据
			入口参数:	输入参数	Buf			所读的数据地址
									SizeofBuf	所读的数据量
			返回值:	0:成功			非0	<见错误代码表>							
		*/
static uint16 Read(uint8 *Buf,uint16 SizeofBuf)
{ 	uint16 i;
	#ifdef OS_ADD
	if(UseSPITaskPro!=OSPrioCur)  //不是开始的任务在调用
		return	De_Erro_Spi_Task; 
	#endif
	while(SSP0SR&0x0c)
	{	i=SSP0DR;


	}

	for(i=0;i<SizeofBuf;i++)
	{	while((SSP0SR&0X12)==0X00);
		SSP0DR=0xff;
		while((SSP0SR&0X17)!=0x07);
		//
		Buf[i]=SSP0DR;
	}
	return De_Suc_Spi;
}
	/*	函数功能：判断SPI总线上数据是否与BUF内容一致
			入口参数:	输入参数	Buf		所判断的数据
									SizeofBuf	所判断数据的数量
			返回值:	0:成功			非0	<见错误代码表>							
		*/
static uint16 JugeBuf(uint8 *Buf,uint16 SizeofBuf)
{ 	uint16 i;
	#ifdef OS_ADD
	if(UseSPITaskPro!=OSPrioCur)  //不是开始的任务在调用
		return	De_Erro_Spi_Task; 
	#endif
	while(SSP0SR&0x0c)
	{	i=SSP0DR;


	}
	for(i=0;i<SizeofBuf;i++)
	{	while((SSP0SR&0X12)==0X00);
		SSP0DR=0xff;
		while((SSP0SR&0X17)!=0x07);
		//
		if(Buf[i]!=SSP0DR)
			return De_Erro_Spi_Byte;
	}
	return De_Suc_Spi;
}

/*	函数功能：判断SPI总线上数据是否是同一个数据
			入口参数:	输入参数	ByteV		所判断的数据
									SizeofBuf	所判断数据的数量
			返回值:	0:成功			非0	<见错误代码表>							
		*/
static uint16 JugeByte(uint8 ByteV,uint32 SizeofBuf)
{	uint32 i;
	#ifdef OS_ADD
	if(UseSPITaskPro!=OSPrioCur)  //不是开始的任务在调用
		return	De_Erro_Spi_Task; 
	#endif
	while(SSP0SR&0x0c)
	{	i=SSP0DR;


	}
	for(i=0;i<SizeofBuf;i++)
	{	while((SSP0SR&0X12)==0X00);
		SSP0DR=0xff;
		while((SSP0SR&0X17)!=0x07);
		//
		if(ByteV!=SSP0DR)
			return De_Erro_Spi_Byte;
	}
	return De_Suc_Spi;
}





 /*	函数功能：结束SPI总线，释放到SPI的使用权
			入口参数:	输入参数	ChipSelect	使能SPI/CE关闭    函数指针	
			返回值:	0:成功			非0	<见错误代码表>							
		*/
static uint16 End(void (*ChipSelect)(void))
{	
	#ifdef OS_ADD
	if(UseSPITaskPro!=OSPrioCur)
		return 	De_Erro_Spi_Task;
	UseSPITaskPro = OS_PRIO_SELF;
	#endif
	ChipSelect();
	#ifdef OS_ADD
	OSSemPost(SPISem);				//通知其他任务我已经使用结束
	#endif
	return De_Suc_Spi;
}





 /*	函数功能：关闭SPI口，此函数一般不用
			返回值:	0:成功			非0	<见错误代码表>
		*/
static uint16 Close(void)							//关闭SPI总线
{	
	#ifdef OS_ADD
	if(UseSPITaskPro!=OS_PRIO_SELF)
		return De_Erro_Spi_Busy;
	#endif
	return De_Suc_Spi;
}



static void DelaySpi(void)
{	uint16 i;
	for(i=0;i<100;i++);


}
#endif
