/*========================================Include File===========================================================*/
	#include "..\APP\config.h"												//LPC2368寄存器引用
 	#include "stdlib.h"	
	#ifdef De_TzV2_Compiler
		#include "..\miscellaneous\CodeTrans\AscNumber.h"
		#include "..\HardWare\RTC\RTC.h"
		#include "..\miscellaneous\Date\date.h"
		#include "AgreementCom.h"
		#include "TzV2.1\Agree\Tz_Agreen.h"
		#include "TzV2.1\Send\Tz_Send.h"
		#include "..\Public_H\DePublic.h"
		#include "..\Dev\Sensor\Sensor.h"
	#endif
/*=========================================Define Data==========================================================*/
	#define De_Suc_AgreeOn										0
	#define De_Erro_AgreeOn_Init	 							1
	#define De_Erro_AgreeOn_Nofd								De_Erro_AgreeOn_Init+1
	#define De_Erro_AgreeOn_NoSpace	 							De_Erro_AgreeOn_Nofd+1
	#define De_Erro_AgreeOn_Explain								De_Erro_AgreeOn_NoSpace+1
	#define De_Erro_AgreeOn_Legality 							De_Erro_AgreeOn_Explain+1
	#define De_Erro_AgreeOn_Write 								De_Erro_AgreeOn_Legality+1
	#define De_Erro_AgreeOn_NoAgreeOn							De_Erro_AgreeOn_Write+1
	#define De_Erro_AgreeOn_TimerOver							De_Erro_AgreeOn_NoAgreeOn+1
	#ifdef De_TzV2_Compiler
		#define De_AgreeOn_Dev_Number							3
		#define De_AgreeOn_Dev_Open								1
		#define De_AgreeOn_Dev_Close							0
		#define De_Stk_Tzv2_Size								512							//堆大小
		#define De_Tzv2_TaskDly									100							//延时调度时间
		#define De_Task_Number									5
	#endif
/*=========================================Data Define=========================================================*/

	typedef struct
	{	uint8 IMEI[7];										//卡号
		uint8 fd;				   							//发送设备ID
		uint16 WorkPar;
		uint32 MaxDelay;
		uint32 IPRepeat;
		uint32 IPRepeatTime;
	}st_AgreeOn_OpenPar;						//调用打开函数时的入口参数

	



	typedef struct
	{	uint16 OrderNumber;
		uint16 OrderID;
		uint16 SizeofBuf;
		uint16 ContrID;
		uint8 AnswerFlag;
		void *Buf;
	}st_st_AgreeOn_Dev_Par;		  						//调用读函数时的函数

	typedef struct
	{	uint16 OrderNumber;
		uint16 OrderID;
		uint16 ContrID;
		void *Buf;
	}st_st_AgreeOn_Dev_WritePar;
   	typedef  struct
	{	void  (*ptFunction)	(st_st_AgreeOn_Dev_Par	*ptst_st_AgreeOn_Dev_Par,uint8 fd);

	}st_Appair_Tzv2;


	typedef struct
	{	uint16 (*Init)(void);
		uint16 (*Open)(st_AgreeOn_OpenPar	*ptst_AgreeOn_OpenPar,st_Appair_Tzv2	*ptst_Appair_Tzv2,uint8 *fd);
		uint16 (*Close)(uint8 fd);
		uint16 (*Read)(uint8 fd,st_st_AgreeOn_Dev_Par	*ptst_st_AgreeOn_Dev_Par);
		uint16 (*Write)(uint8 fd,st_st_AgreeOn_Dev_WritePar	*ptst_st_AgreeOn_Dev_WritePar,uint8 *Oper);	
		uint16 (*GetPar2ID)(uint16 WorkPar,uint8 *fd);
	}st_Fun_Tzv21;

/*=====================================static Function====================================================*/
#ifdef De_TzV2_Compiler	
	static uint16 Init(void);
	static uint16 Open(st_AgreeOn_OpenPar	*ptst_AgreeOn_OpenPar,st_Appair_Tzv2	*ptst_Appair_Tzv2,uint8 *fd);
	static uint16 Close(uint8 fd);
	static uint16 Read(uint8 fd,st_st_AgreeOn_Dev_Par	*ptst_st_AgreeOn_Dev_Par);
	static uint16 Write(uint8 fd,st_st_AgreeOn_Dev_WritePar	*ptst_st_AgreeOn_Dev_WritePar,uint8 *Oper);
	static uint16 Open1(st_AgreeOn_OpenPar	*ptst_AgreeOn_OpenPar,st_Appair_Tzv2	*ptst_Appair_Tzv2,uint8 *fd);
	static uint16 GetPar2ID(uint16 WorkPar,uint8 *fd);
	static uint16 Read1(uint8 fd,st_st_AgreeOn_Dev_Par	*ptst_st_AgreeOn_Dev_Par);
	static uint16 Write1(uint8 fd,st_st_AgreeOn_Dev_WritePar	*ptst_st_AgreeOn_Dev_WritePar,uint8 *Oper);
	static uint16 WriteSig(uint8 fd,st_st_AgreeOn_Dev_WritePar	*ptst_st_AgreeOn_Dev_WritePar,uint8 *Oper);
	static uint32 GetTimeAdd(uint8 *Small,uint8 *Big);
	static  void Task(void *pData);
#endif

/*======================================Public Ram========================================================*/
#ifdef De_TzV2_Compiler	
	static uint8 *X_BUF=(uint8 *)De_TzV21_Ram;
	static uint8 State[De_AgreeOn_Dev_Number];
	static st_AgreeOn_OpenPar	CN_st_AgreeOn_OpenPar[De_AgreeOn_Dev_Number];
	OS_EVENT	*TzvSem=NULL;
	const st_Fun_Tzv21	CN_st_Fun_Tzv21={Init,Open,Close,Read,Write,GetPar2ID};
	static  uint32 BigBuf[512] ;
	static st_st_AgreeOn_Dev_Par	CN_st_st_AgreeOn_Dev_Par;
	static st_Appair_Tzv2	CN_st_Appair_Tzv2[De_AgreeOn_Dev_Number];
	static OS_STK	*STK=(OS_STK	*)De_TzV21_STK;
	static uint16 FlagNumber[De_AgreeOn_Dev_Number];
#else
	extern const st_Fun_Tzv21	CN_st_Fun_Tzv21;
	
#endif


