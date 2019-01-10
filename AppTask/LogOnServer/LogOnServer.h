/*=============================include File==================================================*/
	#include "..\..\APP\config.h"
	#include "stdlib.h"
	#ifdef De_LogOnServer_Compiler
		#include "..\..\File\rwFile.h"
		#include "..\..\Control\Gprs\Gprs.h"
		#include "..\..\FilleData\FileData.h"
		#include "..\..\AgreeOn\TzV2.1.h"
		#include "..\..\AgreeOn\TzV2.1\Send\Tz_Send.h"
		#include "..\..\AgreeOn\TzV2.1\Agree\Tz_Agreen.h"
		#include "..\..\AppAgreenOn\AppGprs.h"
		#include "..\..\HardWare\RTC\RTC.h"
		#include "..\..\Dev\Sensor\Sensor.h"
		#include "..\..\miscellaneous\CodeTrans\AscNumber.h"		//引用码制转换资源
		#include "..\..\miscellaneous\Date\Date.h"					//引用日期资源
		#include "..\..\miscellaneous\Arithmetic\Arithmetic.h" 		//引入算法
	#endif
/*==============================Define Data==================================================*/	
	/*+++++++++++++++++++++++++++++++错误代码一栏表+++++++++++++++++++++++++++++++++++++++++*/
	#define De_Suc_Login										0
	#define De_Erro_LogOnServer									1
	#define	De_Erro_Login										De_Erro_LogOnServer+1
	#define De_Erro_LogOnServer_Init							De_Erro_Login+1
	#define De_Erro_Login_NoIP									De_Erro_LogOnServer_Init+1
	/*+++++++++++++++++++++++++++++++程序状态字+++++++++++++++++++++++++++++++++++++++++++*/
	#define De_LogOnServer_Order_Link_Open						1
	#define De_LogOnServer_Order_Link_Close						0
	#define De_LogOnServer_Order_Link_Online					1
	#define De_LogOnServer_Order_Link_Idle						0
	#define De_Link_State_Open									1
	#define De_Link_State_Close									0

	/*++++++++++++++++++++++++++++++++操作系统有关++++++++++++++++++++++++++++++++++++++++*/
	#ifdef De_LogOnServer_Compiler
		#define De_LogOnServer_Task								3
		#define De_LogOnServer_Stk								384
		#define De_LogOnServer_TaskDly							12000								//延时调度时间
	#endif
/*=======================================Data Define==========================================*/
	/*++++++++++++++++++++++++++++++++数据结构定义+++++++++++++++++++++++++++++++++++++++++++*/
	typedef struct
	{	uint8 Command;        											//邮箱命令          																						
		uint8 Result;
		void (*ptLinkCloseFun)(uint8 *fd);
		void (*AgreeOnNewDataFun)(uint8 *Data,uint8 fd,uint16 DataLength); 
		void (*ptSuc)(void);        										
		OS_EVENT	*ReBox;    											
	}st_BoxData_LogOnServer;
	
	typedef struct
	{	uint16 (*Init)(void);
	}st_Fun_LogOnServer;
	typedef struct
	{	uint8	OpenOrClose;
		uint8	SensorFd;
		uint8	Tzxy21Fd;
	}st_SmsLink_State;
	#ifdef De_LogOnServer_Compiler
		typedef struct
		{	uint8 IPLinkFd;
			uint8 SensorFd;
			uint8 Tzv21Fd;
			uint8 IPLinkState;
			uint8 SensorState;
			uint8 Tzv21State;	
		}st_LogOnServer_OpenFd;
	#endif
/*============================================Static Function================================================*/
	#ifdef De_LogOnServer_Compiler
		static uint16 Init(void);
		static void Task(void *pdata);
		static uint16 Login(void *ptFun,void *AgreeOnFun,uint8 *AgreeOnfd);
		static uint16 Dev_APN(void);
		static uint16 Dev_Login(uint8 *fd);
		static uint16 GetSevPar(st_AgreeOn_ConfigCentrSever	*ptst_AgreeOn_ConfigCentrSever,uint8 fd);
		static uint16 OpenSev(st_AgreeOn_ConfigCentrSever	*ptst_AgreeOn_ConfigCentrSever,void *ptFun,uint8 *fd);
		static uint16 CreatDev(uint8 fd);
		static uint16 CreartAgreeOn(uint8 *fd,void *AgreeOnFun);
		static uint16 GetSevParSigle(uint8 *IMEI,st_AgreeOn_ConfigCentrSever	*ptst_AgreeOn_ConfigCentrSever,uint32 MaxDelay,uint8 fd);
		static uint16 LoginUDP(st_Gprs_IP	*ptst_Gprs_IP,uint16 Port,uint8 *fd);
		static uint32 GetTimeAdd(uint8 *Small,uint8 *Big);
		static void OpenSms(void);
		static void CloseSms(void);
/*=============================================Public Ram=====================================================*/
		OS_STK	LogOnServer_Stk [De_LogOnServer_Stk];
		OS_EVENT	*LogOnServerBox;
		st_BoxData_LogOnServer *ptst_BoxData_LogOnServer;
		st_BoxData_LogOnServer CN_st_BoxData_LogOnServer;
		st_LogOnServer_OpenFd CN_st_LogOnServer_OpenFd;
		static st_SmsLink_State CN_st_SmsLink_State={De_Link_State_Close,0,0};
		const st_Fun_LogOnServer CN_st_Fun_LogOnServer={Init};
	#else
		extern const st_Fun_LogOnServer CN_st_Fun_LogOnServer;
		extern OS_EVENT	*LogOnServerBox;
	#endif
