#include "..\..\Public_H\DePublic.h"
#ifdef	De_Compiler_HardWare_UART

/*===============================Include File==========================================================*/
	#include "..\..\APP\config.h"
	#include "..\..\Public_H\DePublic.h"
	#include "stdlib.h"

/*===================================Define Data=======================================================*/
    #define  OS_ADD  	//此变量如定义，则在操作系统下使用，如果不定义则在前后台系统上使用
	
 	#ifdef OS_ADD
		#define  OS_Message_Uart0					//开启串口0消息模式
		#define  OS_Message_Uart1					//开启串口1消息模式
		#define  OS_Message_Uart2					//开启串口2消息模式
		#define  OS_Message_Uart3					//开启串口3消息模式
	#endif


	/*+++++++++++++++++++++++++++++++++错误代码一览表++++++++++++++++++++++++++++++++++++++++++++*/
	#define De_Suc_Uart							0
	#define De_Erro_Uart								20					
	#define De_Erro_Uart_Init_0					De_Erro_Uart+1 					//初始化串口0失败
	#define De_Erro_Uart_Init_1					De_Erro_Uart_Init_0+1			//初始化串口1失败
	#define De_Erro_Uart_Init_2					De_Erro_Uart_Init_1+1			//初始化串口2失败
	#define De_Erro_Uart_Init_3					De_Erro_Uart_Init_2+1			//初始化串口3失败
	#define De_Erro_Uart_NoPort					De_Erro_Uart_Init_3+1			//无此端口
	#define De_Erro_Uart_BaudRate				De_Erro_Uart_NoPort+1			//波特率不对
	#define De_Erro_Uart_DataBit				De_Erro_Uart_BaudRate+1			//数据位不对
	#define De_Erro_Uart_StopBit				De_Erro_Uart_DataBit+1			//停止位不对
	#define De_Erro_Uart_Parity					De_Erro_Uart_StopBit+1			//奇偶校验不对
	#define De_Erro_Uart0_NoData				De_Erro_Uart_Parity+1			//串口0无数据
	#define De_Erro_Uart1_NoData				De_Erro_Uart0_NoData+1			//串口1无数据
	#define De_Erro_Uart2_NoData				De_Erro_Uart1_NoData+1			//串口2无数据
	#define De_Erro_Uart3_NoData				De_Erro_Uart2_NoData+1			//串口3无数据
	
	/*+++++++++++++++++++++++++++++++++++++端口定义+++++++++++++++++++++++++++++++++++++++++*/
	#define De_Uart_Port_0							0 				//串口0
	#define De_Uart_Port_1							1				//串口1
	#define De_Uart_Port_2							2				//串口2
	#define De_Uart_Port_3							3				//串口3

	/*+++++++++++++++++++++++++++++++++++++Ram地址分配++++++++++++++++++++++++++++++++++++++++++*/
	#define De_Uart_RecMaxSize					2048	 						//uart最大接受的字节数量
	#define De_UartRam							De_Uart_Ram	  					//串口接受缓冲的首地址
	#define De_Uart0Ram							De_UartRam						//串口0接受缓冲首地址
	#define De_Uart1Ram							De_Uart0Ram+De_Uart_RecMaxSize	//串口1接受缓冲首地址
	#define De_Uart2Ram							De_Uart1Ram+De_Uart_RecMaxSize	//串口2接受缓冲首地址
	#define De_Uart3Ram							De_Uart2Ram+De_Uart_RecMaxSize	//串口3接受缓冲首地址

	/*++++++++++++++++++++++++++++++++++++HardWareI/O+++++++++++++++++++++++++++++++++++++++++++*/
	#ifdef De_UART_Compiler	
		#define  De_Uart_Port0_Power_up					PCONP=(PCONP|0X00000008)   //串口0功率寄存器开启
		#define  De_Uart_Port1_Power_up					PCONP=(PCONP|0X00000010)   //串口1功率寄存器开启
		#define  De_Uart_Port2_Power_up					PCONP=(PCONP|0X01000000)   //串口2功率寄存器开启
		#define  De_Uart_Port3_Power_up					PCONP=(PCONP|0X02000000)   //串口3功率寄存器开启
		
		
		#define De_Uart_Port0_Power_Down				PCONP=(PCONP&0xfffffff7)   //串口0功率寄存器关闭
		#define De_Uart_Port1_Power_Down				PCONP=(PCONP&0xffffff7f)   //串口1功率寄存器关闭
		#define De_Uart_Port2_Power_Down				PCONP=(PCONP&0xfeffffff)   //串口2功率寄存器关闭
		#define De_Uart_Port3_Power_Down				PCONP=(PCONP&0xfdfffff7)   //串口3功率寄存器关闭
		
		#define De_Uart_OpenIO_0				PINSEL0 = (PINSEL0 & 0xffffff0f) | 0x50	//串口0开启特殊功能寄存器
		#define De_Uart_OpenIO_1				PINSEL0 = (PINSEL0&0X3FFFFFFF)|0X40000000;PINSEL1=((PINSEL0&0XFFFFFFFC)|0X00000001);//串口1开启特殊功能寄存器
		#define De_Uart_OpenIO_2				PINSEL0 = (PINSEL0&0XFF0FFFFF)|0X00500000; //串口2开启特殊功能寄存器
		#define De_Uart_OpenIO_3				PINSEL0 = (PINSEL0&0XFFFFFFF0)|0X0000000A; //串口3开启特殊功能寄存器
		
  	#endif


/*==============================Data Define============================================================*/
	/*+++++++++++++++++++++++++++++数据结构体++++++++++++++++++++++++++++++++++++++++*/
	typedef struct
	{	uint32  BaudRate;				//波特率
		uint8  DataBit;					//串口数据位5/6/7/8代表位数
		uint8  StopBit;					//停止位.1/2位数
		uint8  Parity;					//奇偶校验位,0:无奇偶校验；1:奇校验;2：偶校验
	}st_Da_Uart;

	/*+++++++++++++++++++++++++++++Function Out++++++++++++++++++++++++++++++++++++++++*/
	typedef struct
	{	/*	函数功能:初始化串口,上电后使用一次以后,不使用
			入口参数:	ComNumber		0~3之间,代表了4个串口
			返回值:	 0:成功			非0	<见错误代码表>	
	
		*/
		uint16 (*Init)(uint8 ComNumber);
		/*	函数功能:打开一个指定的串口,获取串口的使用权
			入口参数:	输入参数	ComNumber	0~3之间,代表了4个串口
									ptst_Da_Uart	详见<st_Da_Uart>定义
			返回值:	 0:成功			非0	<见错误代码表>
		
		*/
		uint16 (*Open)(uint8 ComNumber,st_Da_Uart	*ptst_Da_Uart);
		/*	函数功能:	关闭一个指定的串口
			入口参数:	输入参数	ComNumber	0~3之间,代表了4个串口
			返回值:	 0:成功			非0	<见错误代码表>
		
		*/
		uint16 (*Close)(uint8 ComNumber);
		/*	函数功能:	读取指定串口的数据
			入口参数:	输入参数	ComNumber	0~3之间,代表了4个串口
									DataLen		所读的串口数据量
						输出参数	Data		所读的数据
			返回值:实际所读的字节数量						
		*/
		uint16 (*Read)(uint8 ComNumber,uint8 *Data,uint16 DataLen);

		/*	函数功能:	写指定串口的数据
			入口参数:	输入参数	ComNumber	0~3之间,代表了4个串口
									DataLen		所写的串口字节数据量
									Data		所写的数据
			返回值:实际所读的字节数量						
		*/
		uint16 (*Write)(uint8 ComNumber,uint8 *Data,uint16 DataLen);
	}st_Fun_Uart;				//Uart.c输

/*======================================static Function======================================================*/
	#ifdef De_UART_Compiler
		static uint16 Init(uint8 ComNumber);
		static uint16 Open(uint8 ComNumber,st_Da_Uart	*ptst_Da_Uart);
		static uint16 Close(uint8 ComNumber);
		static uint16 Read(uint8 ComNumber,uint8 *Data,uint16 DataLen);
		static uint16 Write(uint8 ComNumber,uint8 *Data,uint16 DataLen);
		
		
		
		static uint16 Open0(st_Da_Uart	*ptst_Da_Uart);
		static uint16 Close0(void);
		static uint16 Read0(uint8 *Data,uint16 DataLen);
		static uint16 Write0(uint8 *Data,uint16 DataLen);
		static uint16 Receive0Byte(uint8 *ByteV); 	
		
		
		static uint16 Open1(st_Da_Uart	*ptst_Da_Uart);
		static uint16 Close1(void);
		static uint16 Read1(uint8 *Data,uint16 DataLen);
		static uint16 Write1(uint8 *Data,uint16 DataLen);
		static uint16 Receive1Byte(uint8 *ByteV);
		
		static uint16 Open2(st_Da_Uart	*ptst_Da_Uart);
		static uint16 Close2(void);
		static uint16 Read2(uint8 *Data,uint16 DataLen);
		static uint16 Write2(uint8 *Data,uint16 DataLen);
		static uint16 Receive2Byte(uint8 *ByteV);
		
		static uint16 Open3(st_Da_Uart	*ptst_Da_Uart);
		static uint16 Close3(void);
		static uint16 Read3(uint8 *Data,uint16 DataLen);
		static uint16 Write3(uint8 *Data,uint16 DataLen);
		static uint16 Receive3Byte(uint8 *ByteV);
		static uint16 ClearSem(OS_EVENT	*UartSem);

/*======================================Public Ram============================================================*/
		#ifdef OS_ADD
			OS_EVENT 		*Uart0UseSem;						//获取串口使用权
			OS_EVENT 		*Uart1UseSem;						//获取串口使用权
			OS_EVENT 		*Uart2UseSem;						//获取串口使用权
			OS_EVENT 		*Uart3UseSem;						//获取串口使用权
		#endif	
		#ifdef OS_Message_Uart0
			OS_EVENT 		*Uart0RxSem;						//获取接收送使用权
		#endif
		
		#ifdef OS_Message_Uart1
			OS_EVENT 		*Uart1RxSem;						//获取接收送使用权
		#endif
		
		#ifdef OS_Message_Uart2	
			OS_EVENT 		*Uart2RxSem;						//获取接收送使用权
		#endif
		#ifdef OS_Message_Uart3
			OS_EVENT 		*Uart3RxSem;						//获取接收送使用权
		#endif
		//接受缓冲区
		uint8 *ptUart0ReBuf=(uint8 *)De_Uart0Ram;
		uint8 *ptUart1ReBuf=(uint8 *)De_Uart1Ram;
		uint8 *ptUart2ReBuf=(uint8 *)De_Uart2Ram;
		uint8 *ptUart3ReBuf=(uint8 *)De_Uart3Ram;
		//队列所用变量
		uint16 UART0_RxHead,UART0_RxTail,UART1_RxHead,UART1_RxTail,UART2_RxHead,UART2_RxTail,UART3_RxHead,UART3_RxTail;
		const st_Fun_Uart	CN_st_Fun_Uart={Init,Open,Close,Read,Write};  //函数输出定义
	#else
		extern const st_Fun_Uart CN_st_Fun_Uart;	 			//对外输出函数

	#endif
#endif

/*--------------------------------------End Uart.h---------------------------------------------------------------*/
