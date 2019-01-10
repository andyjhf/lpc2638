/*=============================include File==================================================*/
	#include "..\..\APP\config.h"
	#include "stdlib.h"
	#ifdef De_OpenAndClose_Compiler
		#include "..\..\File\rwFile.h"
		#include "..\..\FilleData\FileData.h"
		#include "..\..\FilleData\TakeData.h"
		#include "..\..\AgreeOn\TzV2.1.h"
		#include "..\..\Control\Timer\Timer.h"
		#include "..\LogOnServer\LogOnServer.h"
		#include "..\..\AppAgreenOn\AppGprs.h"
		#include "..\..\Dev\Sensor\Sensor.h"
		#include "..\..\AppSendAgreeOn\AppSendAgreeOn.H"
		#include "..\..\OpenSensor\OpenSensor.h"
		#include "..\..\miscellaneous\CodeTrans\AscNumber.h"	
		
	#endif
/*==============================Define Data==================================================*/	
	#define De_No_Log													0		//没有登录
	#define De_LogInt													1		//正在登录中
	#define De_LogSuc													2		//登录成功
//	#define De_Link_State_Open											1
//	#define De_Link_State_Close											0

/*=======================================Data Define==========================================*/
	/*++++++++++++++++++++++++++++++++数据结构定义+++++++++++++++++++++++++++++++++++++++++++*/
/*	typedef struct
	{	uint8	OpenOrClose;
		uint8	SensorFd;
		uint8	Tzxy21Fd;
	}st_SmsLink_State;	 */
	typedef struct
	{	void (*Init)(void);
		void (*OpenGps)(void);
		void (*CloseGps)(void);
		void (*OpenGprs)(void);
		void (*CloseGprs)(void);
		void (*OpenGprsNo)(uint8 fd);
		void (*OpenUart)(void);
//		void (*OpenSms)(void);
//		void (*CloseSms)(void);
	}st_Fun_OpenAndClose;

/*============================================Static Function================================================*/
	#ifdef De_OpenAndClose_Compiler
		static void Init(void);
		static void OpenGps(void);
		static void CloseGps(void);
		static void OpenGprs(void);
		static void OpenGprsNo(uint8 fd);
		static void CloseGprs(void);
		static void ClearTimer(st_Data_Timer	*ptst_Data_Timer,uint8 fd);
		static void ClearSem(void);
		static void OpenUart(void);
//		static void OpenSms(void);
//		static void CloseSms(void);
		static void LogSucOper(void);
		static void ChargeLoadDev(st_Data_Timer	*ptst_Data_Timer,uint8 fd);
		static void ChargeLogin(st_Data_Timer	*ptst_Data_Timer,uint8 fd);
		static void LCDRef(st_Data_Timer	*ptst_Data_Timer,uint8 fd);
	#endif		
/*=============================================Public Ram=====================================================*/
		
	#ifdef De_OpenAndClose_Compiler
//		static st_SmsLink_State CN_st_SmsLink_State={De_Link_State_Close,0,0};
		static uint8 CloseTimer=De_AgreeOn_State_Suc;
		static uint8 Timerfd=0xff;
		uint8 LogFlag=De_No_Log;
		static st_BoxData_LogOnServer	CN_st_BoxData_LogOnServer;
		static const uint8 *CloseGpsTerm[]=
		{	&CloseTimer,
			App_CN_st_WorkFlow_Table.CN_st_AgreeOn_Send_Basic.State+De_Orientation_State_Help,
			App_CN_st_WorkFlow_Table.CN_st_AgreeOn_Send_Basic.State+De_Orientation_State_HighSpeed,
			App_CN_st_WorkFlow_Table.CN_st_AgreeOn_Send_Basic.State+De_Orientation_State_CloseVal,
			App_CN_st_WorkFlow_Table.CN_st_AgreeOn_Send_Basic.State+De_Orientation_State_LowSpeed

		};
		static const uint8 *CloseGprsTerm[]=
		{	&CloseTimer,App_CN_st_WorkFlow_Table.CN_st_AgreeOn_Send_Basic.State+De_Orientation_State_Help,
			App_CN_st_WorkFlow_Table.CN_st_AgreeOn_Send_Basic.State+De_Orientation_State_HighSpeed,
			App_CN_st_WorkFlow_Table.CN_st_AgreeOn_Send_Basic.State+De_Orientation_State_CloseVal,
			App_CN_st_WorkFlow_Table.CN_st_AgreeOn_Send_Basic.State+De_Orientation_State_LowSpeed

		};	
		static const st_Affair_Timer	CN_Ba_st_Affair_Timer=
		{	{120,0,{0,0,0,0,0,0,0}},
			{ClearTimer}
		};
		static const st_Affair_Timer	CN_Ba_st_Login=
		{ 	{120,0,{0,0,0,0,0,0,0}},
			{ChargeLogin}
		};
		static const st_Affair_Timer	CN_Ba_st_Dev=
		{ 	{120,0,{0,0,0,0,0,0,0}},
			{ChargeLoadDev}
		};
		const st_Fun_OpenAndClose	CN_st_Fun_OpenAndClose={Init,OpenGps,CloseGps,OpenGprs,CloseGprs,OpenGprsNo,OpenUart};				//,OpenSms,CloseSms
		uint8 LogTimerfd;
		uint8 UnLoaderTimerfd;													
	#else
		extern const st_Fun_OpenAndClose	CN_st_Fun_OpenAndClose;
		extern uint8 LogTimerfd;
		extern uint8 UnLoaderTimerfd;
		extern uint8 LogFlag;
	#endif
