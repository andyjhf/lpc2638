/*=========================================Include File=========================================================*/
	#include "..\APP\config.h"
	#include "stdlib.h"
	#ifdef De_WarningUpate_Compiler
		#include "..\File\rwFile.h"
		#include "..\miscellaneous\CodeTrans\AscNumber.h"
		#include "..\FilleData\FileData.h"
		#include "..\Control\GpsAndMileage\GpsAndMileage.h"
		#include "..\FilleData\TakeData.h"
		#include "..\miscellaneous\Date\Date.h"
		#include "..\AgreeOn\TzV2.1.h"
		#include "..\AppSendAgreeOn\AppSendAgreeOn.H"
		#include "..\Dev\Sensor\Sensor.h"
		#include "..\Control\Gprs\GPRS.h"
		#include "..\AppOper\JugeOper.h"
	#endif
/*==========================================Define Data======================================================*/
#ifdef De_WarningUpate_Compiler	
	#define De_Warning_Task													12
	#define De_Warning_Stk													256
	#define De_Warning_TaskDly												100				//延时调度时间
#endif

/*===========================================Data Define=========================================================*/
	typedef struct
	{	void (*Init)(void);	


	}st_Fun_WarningUpate;
	#ifdef De_WarningUpate_Compiler	
		typedef struct
		{	uint8 *State;
			uint16 Number;
		}st_Data_Number2Point;
	#endif
/*===========================================static Function=====================================================*/
#ifdef De_WarningUpate_Compiler		
	static void Init(void);
	static void Task(void *pData);
	static void JugeGpsState(void);
	static void JugeWorkPar(void);
	static void LoadWaringJugeWorkPar(uint16 Number,uint8 ErroOrOk);
	static void LoadWaringJugeWorkParState(uint16 Number,st_Sensor_State	*ptst_Sensor_State);
	static void SendWarning(uint16 Number);
#endif	 
/*=============================================Public Ram========================================================*/
#ifdef De_WarningUpate_Compiler
	static OS_STK		*Stk=(OS_STK		*)(De_FTP_STK_Ram);
	static const st_Data_Number2Point CN_Ba_st_Data_Number2Point[]=
	{	{&App_CN_st_WorkFlow_Table.CN_st_WorkVal_Tabel.CN_st_AgreeOn_SetVidType_Par.CN_Less_Switch1.State,16},
		{&App_CN_st_WorkFlow_Table.CN_st_WorkVal_Tabel.CN_st_AgreeOn_SetVidType_Par.CN_Less_Switch2.State,17},
		{&App_CN_st_WorkFlow_Table.CN_st_WorkVal_Tabel.CN_st_AgreeOn_SetVidType_Par.CN_Less_Switch3.State,18},
		{&App_CN_st_WorkFlow_Table.CN_st_WorkVal_Tabel.CN_st_AgreeOn_SetVidType_Par.CN_Less_Switch4.State,19},
		{&App_CN_st_WorkFlow_Table.CN_st_WorkVal_Tabel.CN_st_AgreeOn_SetVidType_Par.CN_Less_Switch5.State,20},
		{&App_CN_st_WorkFlow_Table.CN_st_WorkVal_Tabel.CN_st_AgreeOn_SetVidType_Par.CN_Less_Switch6.State,21},
		{&App_CN_st_WorkFlow_Table.CN_st_WorkVal_Tabel.CN_st_AgreeOn_SetVidType_Par.CN_Less_Switch1.State,16},
		{&App_CN_st_WorkFlow_Table.CN_st_WorkVal_Tabel.CN_st_AgreeOn_SetVidType_Par.CN_st_AgreeOn_Less_Temp1.State,32},
		{&App_CN_st_WorkFlow_Table.CN_st_WorkVal_Tabel.CN_st_AgreeOn_SetVidType_Par.CN_st_AgreeOn_Less_Temp2.State,33},
		{&App_CN_st_WorkFlow_Table.CN_st_WorkVal_Tabel.CN_st_AgreeOn_SetVidType_Par.CN_st_AgreeOn_Less_Temp3.State,34},
		{&App_CN_st_WorkFlow_Table.CN_st_WorkVal_Tabel.CN_st_AgreeOn_SetVidType_Par.CN_st_AgreeOn_Less_Temp4.State,35},
	};
	const st_Fun_WarningUpate	CN_st_Fun_WarningUpate={Init};
#else
	extern const st_Fun_WarningUpate	CN_st_Fun_WarningUpate;
#endif



