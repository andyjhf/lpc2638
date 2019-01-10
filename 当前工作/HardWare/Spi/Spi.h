#include "..\..\Public_H\DePublic.h"
#ifdef	De_Compiler_HardWare_Spi

/*===============================Include File==========================================================*/
      #include "..\..\APP\config.h"
      #include "stdlib.h"


/*===================================Define Data=======================================================*/
	#define  OS_ADD  	//此变量如定义，则在操作系统下使用，如果不定义则在前后台系统上使用
	  /*++++++++++++++++++++++++++++++++++错误代码一览表++++++++++++++++++++++++++++++++++++++++++++*/
	#define De_Suc_Spi										0 				//成功
	
	#define De_Erro_Spi_Open									De_Erro_Spi				//打开SPI错误					
	#define De_Erro_Spi_Task									De_Erro_Spi_Open+1				//非本任务的执行
	#define De_Erro_Spi_Busy									De_Erro_Spi_Task+1				//Spi总线忙
	#define De_Erro_Spi_Byte									De_Erro_Spi_Busy+1				//数据不一样
      

	/*+++++++++++++++++++++++++++++++++++HardWareI/O+++++++++++++++++++++++++++++++++++++++++++++++*/
	#define De_IO_Spi_SCK								0x00100000
	#define De_IO_Spi_Din								0XFF7fffff
	#define De_IO_Spi_Dou								0x01000000
	#define De_IO_Spi_SCK_OUT							IODIR1|=De_IO_Spi_SCK
	#define De_IO_Spi_Din_INT							IODIR1&=De_IO_Spi_Din
	#define De_IO_Spi_Dout_OUT							IODIR1|=De_IO_Spi_Dou

/*==============================Data Define============================================================*/
	
	/*++++++++++++++++++++++++++++++Function Out++++++++++++++++++++++++++++++++++++++++++++++++*/
	typedef struct
	{ 	/*	函数功能：打开SPI口，此函数在运行之前必须打开
			返回值:	0:成功			非0	<见错误代码表>
		*/
		uint16 (* Open)(void);
		/*	函数功能：开始SPI总线，获取到SPI的使用权
			入口参数:	输入参数	ChipSelect	使能SPI/CE选通	      函数指针
									ChipSelectOver	使能SPI/CE关闭    函数指针
			返回值:	0:成功			非0	<见错误代码表>							
		*/
		uint16 (* Start)(void (*ChipSelect)(void),void (*ChipSelectOver)(void));
		/*	函数功能：SPI总新写的时候，同时接受
			入口参数:	输入参数	wBuf		所写的数据地址
									SizeofBuf	所写的数据量
						输出参数	rBuf		所读的数据地址，所读的数据量与所写的数据量一样
			返回值:	0:成功			非0	<见错误代码表>							
		*/
		uint16 (* RwSpi)(uint8 *wBuf,uint8 *rBuf,uint16 SizeofBuf);
		/*	函数功能：向SPI总线上写数据
			入口参数:	输入参数	Buf			所写的数据地址
									SizeofBuf	所写的数据量
			返回值:	0:成功			非0	<见错误代码表>							
		*/
		uint16 (* Write)(uint8 *Buf,uint16 SizeofBuf);
		/*	函数功能：读取SPI总线的数据
			入口参数:	输入参数	Buf			所读的数据地址
									SizeofBuf	所读的数据量
			返回值:	0:成功			非0	<见错误代码表>							
		*/
		uint16 (* Read)(uint8 *Buf,uint16 SizeofBuf);
		/*	函数功能：判断SPI总线上数据是否是同一个数据
			入口参数:	输入参数	ByteV		所判断的数据
									SizeofBuf	所判断数据的数量
			返回值:	0:成功			非0	<见错误代码表>							
		*/
		uint16 (* JugeByte)(uint8 ByteV,uint32 SizeofBuf);
		/*	函数功能：判断SPI总线上数据是否与BUF内容一致
			入口参数:	输入参数	Buf		所判断的数据
									SizeofBuf	所判断数据的数量
			返回值:	0:成功			非0	<见错误代码表>							
		*/
		uint16 (* JugeBuf)(uint8 *Buf,uint16 SizeofBuf);
		/*	函数功能：结束SPI总线，释放到SPI的使用权
			入口参数:	输入参数	ChipSelect	使能SPI/CE关闭    函数指针	
			返回值:	0:成功			非0	<见错误代码表>							
		*/
		uint16 (* End)(void (*ChipSelect)(void));
		/*	函数功能：关闭SPI口，此函数一般不用
			返回值:	0:成功			非0	<见错误代码表>
		*/
		uint16 (* Close)(void);    
    }st_Fun_Spi;			//SPI.C输出


	#ifdef De_UART_Compiler
/*======================================static Function=========================================================*/
		static uint16 Open(void);
		static uint16 Start(void (*ChipSelect)(void),void (*ChipSelectOver)(void));
		static uint16 Read(uint8 *Buf,uint16 SizeofBuf);
		static uint16 End(void (*ChipSelect)(void));
		static uint16 Close(void);
		static uint16 Read(uint8 *Buf,uint16 SizeofBuf);
		static uint16 Write(uint8 *Buf,uint16 SizeofBuf);
		static uint16 JugeByte(uint8 ByteV,uint32 SizeofBuf);
		static uint16 JugeBuf(uint8 *Buf,uint16 SizeofBuf);
		static uint16 RwSpi(uint8 *wBuf,uint8 *rBuf,uint16 SizeofBuf);
		static void DelaySpi(void);
/*======================================Public Ram==============================================================*/
		#ifdef OS_ADD
		static OS_EVENT *SPISem=NULL;
		static uint8 UseSPITaskPro;
		#endif
		const st_Fun_Spi  CN_st_Fun_Spi={Open,Start,RwSpi,Write,Read,JugeByte,JugeBuf,End,Close};
	#else
		extern st_Fun_Spi  CN_st_Fun_Spi;
	#endif    
#endif
