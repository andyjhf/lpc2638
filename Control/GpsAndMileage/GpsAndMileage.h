/*=======================================Include File===========================================================*/
   	#include "..\..\APP\config.h"
	#include "stdlib.h"
	#ifdef De_GpsAndMileage_Compiler
		#include "..\..\Public_H\DePublic.h"
		#include "..\..\miscellaneous\CodeTrans\AscNumber.h"
		#include "..\..\Dev\Sensor\_PuSensor.h"
		#include "..\..\Dev\Sensor\Sensor.h"
		#include "..\..\HardWare\RTC\RTC.h"
		#include "..\..\Dev\Sensor\Gps\Gps.h"
		#include "..\..\Dev\Sensor\mileage\mileage.h"
	#endif
/*=======================================Define Data============================================================*/
	#define De_Suc_GpsAndMileage											0
	#define De_GpsState_Close												3		 //设备关闭
	#define De_GpsState_NoWork												2		 //设备故障
	#define De_GpsState_FlaseData										    1		 //不定位
	#define De_GpsState_OK													0		 //正常

	#define De_GpsAndMileage_State_Open										1				//状态打开
	#define De_GpsAndMileage_State_Close									0				//状态关闭
	/*+++++++++++++++++++++++++++++++++++错误代码一览表+++++++++++++++++++++++++++++++++++++*/
	#define De_Erro_GpsAndMileage											1
	#define De_Erro_GpsAndMileage_Init										De_Erro_GpsAndMileage
	#define De_Erro_GpsAndMileage_OverMaxNumber								De_Erro_GpsAndMileage_Init+1
	#define De_Erro_GpsAndMileage_Close										De_Erro_GpsAndMileage_OverMaxNumber+1
	/*+++++++++++++++++++++++++++++++++++任务有关参数+++++++++++++++++++++++++++++++++*/
	#ifdef De_GpsAndMileage_Compiler
		#define De_Stk_Size													256							//堆大小
		#define De_GpsAndMileage_TaskDly									100							//延时调度时间
		#define De_Affair_GpsAndMileage_MaxNumber							5 							//最大20个事件
		#define De_Task_Number												8
	#endif
/*========================================Data Define===========================================================*/
	typedef struct
	{	st_Data_Gps	CN_st_Data_Gps;			//
		uint32 Milage;						//统计
	}st_File_Gps;

	typedef struct
	{	uint32 Len;	
	}st_Affair_Data;
	
	typedef struct
	{	uint8 GpsState;
	}st_State_RunLen;

	typedef struct
	{	void (*Fun_SumLen)(st_File_Gps	*ptst_File_Gps,uint8 fd);
	}st_Affair_RunLen;

	typedef struct
	{	uint16 (*Init)(void);
		uint16 (*Open)(st_Affair_Data	*ptst_Affair_Data,st_Affair_RunLen	*ptst_Affair_RunLen,uint8 *fd);
		uint16 (*Close)(uint8 fd);
		uint16 (*Get)(st_State_RunLen	*ptst_State_RunLen);
	}st_Fun_RunLen;
	#ifdef De_GpsAndMileage_Compiler
		typedef struct
		{	st_Affair_Data CN_st_Affair_Data;
			st_Affair_RunLen CN_st_Affair_RunLen;
			uint32 Milage;
		}st_Affair_GpsAndMileage;
		typedef struct
		{	uint8 State[De_Affair_GpsAndMileage_MaxNumber];										//各事件状态
			st_File_Gps CN_st_File_Gps;
			st_Affair_GpsAndMileage CN_st_Affair_GpsAndMileage[De_Affair_GpsAndMileage_MaxNumber];
			st_State_RunLen CN_st_State_RunLen;
		}st_GpsAndMileage_OperData;
	#endif
/*========================================static Function=======================================================*/
	#ifdef De_GpsAndMileage_Compiler	
		static uint16 Init(void);
		static uint16 Open(st_Affair_Data	*ptst_Affair_Data,st_Affair_RunLen	*ptst_Affair_RunLen,uint8 *fd);
		static uint16 Close(uint8 fd);
		static uint16 Get(st_State_RunLen	*ptst_State_RunLen);
		static void Task(void *pData);
		static uint16 ReadGpsData(uint8 fd,uint8 *state,st_Data_Gps *ptst_Data_Gps);
		static uint16 CountMileage(uint8 fd,st_Data_Gps *ptst_Data_Gps,uint32 *Length);
		static uint16 JugeEvent(st_File_Gps *ptst_File_Gps);
	#endif
/*============================================Pubic Ram=========================================================*/	
	#ifdef De_GpsAndMileage_Compiler
		OS_EVENT	*GpsAndMileageUseSem=NULL;
		static OS_STK	*STK =(OS_STK	*)(De_GpsAndMi);
		st_GpsAndMileage_OperData CN_st_GpsAndMileage_OperData;

		const st_Fun_RunLen CN_st_Fun_RunLen = {Init,Open,Close,Get};
	#else
		extern st_Fun_RunLen CN_st_Fun_RunLen;
	#endif






