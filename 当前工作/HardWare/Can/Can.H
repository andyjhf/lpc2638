#include "..\..\Public_H\DePublic.h"
#define Can_h
#ifdef	Can_h
/*===============================Include File==========================================================*/
	#include "..\..\APP\config.h"
	#include "stdlib.h"
	
/*===================================Define Data=======================================================*/
	/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/
	
	#define  OS_ADD  	//此变量如定义，则在操作系统下使用，如果不定义则在前后台系统上使用	
	/*++++++++++++++++++++++++++++++++端口定义+++++++++++++++++++++++++++++++++++++++++++++*/
	#define De_Can_Port_0							0
	#define De_Can_Port_1							1
	#define De_Can_Port_2							2
	#define De_Can_Port_3							3

	#define De_Can_Data_Read						0
	#define De_Can_Data_UnRead						1
	/*+++++++++++++++++++++++++++++++错误代码一览表++++++++++++++++++++++++++++++++++++++++*/
	#define De_Suc_Can								0
	#define De_Erro_Can_Init_0					De_Erro_Can+1
	#define De_Erro_Can_Init_1					De_Erro_Can_Init_0+1
	#define De_Erro_Can_NoPort					De_Erro_Can_Init_1+1
		
/*==============================Data Define================================================*/
	/*+++++++++++++++++++++++++++++++Can Data Type++++++++++++++++++++++++++++++++++++++++*/
	
	typedef struct
	{	uint32 FrameData[2];			//CAN数据
		uint32 FrameInfor;
		uint32 FrameID;
	}st_Da_CanInfor;  					//CAN的参数
	/*++++++++++++++++++++++++++++++Function Data+++++++++++++++++++++++++++++++++++++++++*/
	typedef struct
	{
		/*	函数功能:初始化CAN总线,上电后使用一次,以后不使用
			入口参数:	CanNumber		0~1之间,代表了2个CAN
			返回值:	 0:成功			非0	<见错误代码表>	
	
		*/
		uint16 (*Init)(uint8 CanNumber);
		/*	函数功能:打开CAN总线
			入口参数:	输入参数	CanNumber		0~1之间,代表了2个CAN
									Baud			CAN通讯波特率
			返回值:	 0:成功			非0	<见错误代码表>	
		*/
		uint16 (*Open)(uint8 CanNumber,uint32 Baud);
		/*	函数功能:关闭CAN总线
			入口参数:	输入参数	CanNumber		0~1之间,代表了2个CAN
			返回值:	 0:成功			非0	<见错误代码表>	
		*/
		uint16 (*Close)(uint8 CanNumber);
		/*	函数功能:向CAN总线发送一帧数据
			入口参数:	输入参数	CanNumber		0~1之间,代表了2个CAN
									ptst_Da_CanInfor	所要发送的数据
			返回值:	 0:成功			非0	<见错误代码表>	
		*/
		uint16 (*Write)(uint8 CanNumber,st_Da_CanInfor	*ptst_Da_CanInfor);
		/*	函数功能:读取CAN总线一帧数据
			入口参数:	输入参数	CanNumber		0~1之间,代表了2个CAN
						输出参数	ptst_Da_CanInfor	所读取的数据
			返回值:	 0:成功			非0	没有数据	
		*/
		uint16 (*Read)(uint8 CanNumber,st_Da_CanInfor	*ptst_Da_CanInfor);
	
	}st_Fun_Can;   				//Can.C输出
/*=====================================Ram定义=============================================*/
	
	#define De_CanRam							De_Flash_Ram
	#define De_Can1Ram							De_CanRam
	#define De_Can2Ram							De_CanRam+sizeof(st_Da_CanInforBuf)
	#define De_Can_RecMaxSize											10	
	
	
/*==================================静态函数定义===========================================*/
	#ifdef	De_Can_Compiler		 
		 static uint16 Init(uint8 CanNumber);
		 static uint16 Open(uint8 CanNumber,uint32 Baud);
		 static uint16 Close(uint8 CanNumber);
		 static uint16 Write(uint8 CanNumber,st_Da_CanInfor	*ptst_Da_CanInfor);
		 static uint16 Read(uint8 CanNumber,st_Da_CanInfor	*ptst_Da_CanInfor);
		
		
		 
		 static uint16 Open0(uint32 Baud);
		 static uint16 Close0(void);
		 static uint16 Write0(st_Da_CanInfor	*ptst_Da_CanInfor);
		 static uint16 Read0(st_Da_CanInfor	*ptst_Da_CanInfor);
		
		 static uint16 Open1(uint32 Baud);
		 static uint16 Close1(void);
		 static uint16 Write1(st_Da_CanInfor	*ptst_Da_CanInfor);
		 static uint16 Read1(st_Da_CanInfor	*ptst_Da_CanInfor);
		
		
		 static uint16 ClearSem(OS_EVENT	*CanSem);

		// static void CAN_Exception (void);

		 st_Da_CanInfor	CN_st_Da_CanInfor[De_Can_RecMaxSize],CN_st_Da_CanInfor1[De_Can_RecMaxSize];
		 uint16 Can0_RxHead,Can0_RxTail,Can1_RxHead,Can1_RxTail;
		 #ifdef OS_ADD
			OS_EVENT 		*Can0UseSem=NULL;						//获取CAN使用权
			OS_EVENT 		*Can1UseSem=NULL;						//获取CAN使用权
			
			OS_EVENT 		*Can0RxSem=NULL;						//获取CAN送使用权
			OS_EVENT 		*Can1RxSem=NULL;						//获取CAN送使用权
		 #endif
		 st_Fun_Can	CN_st_Fun_Can={Init,Open,Close,Write,Read};
	#else
		extern st_Da_CanInfor	CN_st_Da_CanInfor[De_Can_RecMaxSize],CN_st_Da_CanInfor1[De_Can_RecMaxSize];
		extern uint16 Can0_RxHead,Can0_RxTail,Can1_RxHead,Can1_RxTail;
		#ifdef OS_ADD
			extern OS_EVENT 		*Can0UseSem;						//获取CAN使用权
			extern OS_EVENT 		*Can1UseSem;						//获取CAN使用权
			
			extern OS_EVENT 		*Can0RxSem;							//获取CAN送使用权
			extern OS_EVENT 		*Can1RxSem;							//获取CAN送使用权
		#endif
		extern st_Fun_Can	CN_st_Fun_Can;
	#endif
#endif
