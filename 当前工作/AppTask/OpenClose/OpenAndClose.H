/*=============================include File==================================================*/
	#include "..\..\APP\config.h"
	#include "stdlib.h"
	#ifdef De_OpenAndClose_Compiler
		#include "..\..\FilleData\FileData.h"
		#include "..\..\FilleData\TakeData.h"
		#include "..\..\AgreeOn\TzV2.1.h"
		#include "..\..\Control\Timer\Timer.h"
		#include "..\LogOnServer\LogOnServer.h"
		#include "..\..\AppAgreenOn\AppGprs.h"
		#include "..\..\Dev\Sensor\Sensor.h"
		#include "..\..\AppSendAgreeOn\AppSendAgreeOn.H"
		#include "..\..\OpenSensor\OpenSensor.h"	
		
	#endif
/*==============================Define Data==================================================*/	
	#define De_No_Log													0		//没有登录
	#define De_LogInt													1		//正在登录中
	#define De_LogSuc													2		//登录成功
/*=======================================Data Define==========================================*/
	/*++++++++++++++++++++++++++++++++数据结构定义+++++++++++++++++++++++++++++++++++++++++++*/
	typedef struct
	{	void (*Init)(void);
		void (*OpenGps)(void);
		void (*CloseGps)(void);
		void (*OpenGprs)(void);
		void (*CloseGprs)(void);
		void (*OpenGprsNo)(uint8 fd);
		void (*OpenUart)(void);
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
		static void LogSucOper(void);
		static void ChargeLoadDev(st_Data_Timer	*ptst_Data_Timer,uint8 fd);
		static void ChargeLogin(st_Data_Timer	*ptst_Data_Timer,uint8 fd);
		static void LCDRef(st_Data_Timer	*ptst_Data_Timer,uint8 fd);
	#endif		
/*=============================================Public Ram=====================================================*/
		
	#ifdef De_OpenAndClose_Compiler
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
		{	{1200,0,{0,0,0,0,0,0,0}},
			{ClearTimer}
		};
		static const st_Affair_Timer	CN_Ba_st_Login=
		{ 	{1200,0,{0,0,0,0,0,0,0}},
			{ChargeLogin}
		};
		static const st_Affair_Timer	CN_Ba_st_Dev=
		{ 	{1200,0,{0,0,0,0,0,0,0}},
			{ChargeLoadDev}
		};
		const st_Fun_OpenAndClose	CN_st_Fun_OpenAndClose={Init,OpenGps,CloseGps,OpenGprs,CloseGprs,OpenGprsNo,OpenUart};
		uint8 LogTimerfd;
		uint8 UnLoaderTimerfd;													
	#else
		extern const st_Fun_OpenAndClose	CN_st_Fun_OpenAndClose;
		extern uint8 LogTimerfd;
		extern uint8 UnLoaderTimerfd;
		extern uint8 LogFlag;
	#endif
