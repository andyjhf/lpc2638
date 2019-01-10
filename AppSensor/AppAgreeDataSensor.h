/*=========================================Include File=========================================================*/	
	#include "..\APP\config.h"
	#include "stdlib.h"
	#ifdef De_AppAgreeDataSensor_Compiler
		#include "..\File\rwFile.h"
		#include "..\miscellaneous\CodeTrans\AscNumber.h"
		#include "..\FilleData\FileData.h"
		#include "..\FilleData\TakeData.h"
		#include "..\Control\Sensor\SensorContr.h"
		#include "..\Dev\Sensor\Sensor.h"
		#include "..\HardWare\RTC\RTC.h"
		#include "..\miscellaneous\Date\Date.h"
		#include "..\AgreeOn\TzV2.1.h"
		#include "..\AppSendAgreeOn\AppSendAgreeOn.H"
		#include "..\AppOper\AccOper.H"
		#include "..\AppOper\JugeOper.h"
		#include "..\AppTask\OpenClose\OpenAndClose.H"
		#include "..\Control\Timer\Timer.h"
		#include "..\Control\Gprs\Gprs.h"
		#include "..\AppOper\DisPlayOper.h"
	#endif
/*=========================================Define Data=========================================================*/
	#define De_Suc_AppAgreeDataSensor										0
	#define De_Erro_NoData													1
	#ifdef De_AppAgreeDataSensor_Compiler
		static void Init(uint16 *ParID,uint16 SizeofParID);
		static void GetData(uint16 Par,void *Data,uint8 *DateTimer);			
		static uint16 Jugeuint8(uint16 Par,uint8 *Data);
		static uint16 Jugeint32(uint16 Par,int32 *Data);
		static uint16 Jugeuint16(uint16 Par,uint16 *Data);
		static void VoCheck(void *Data);
		static void JugeVo(uint32 AddTim,uint32 Speed);
		static uint32 GetTimeAdd(uint8 *Small,uint8 *Big);
		static void HelpWaring(void *Data);
	#endif
		
/*=========================================Data Define=========================================================*/	
	typedef struct
	{	void (*Init)(uint16 *ParID,uint16 SizeofParID);
	
	}st_Fun_AppAgreeDataSensor;
	#ifdef De_AppAgreeDataSensor_Compiler
		typedef struct
		{	uint16 Par;
			void (*ptFun)(void *Data,st_AgreeOn_SetVidType_Par	*ptst_AgreeOn_SetVidType_Par);
		}st_Data_AppAgreeData;
		typedef struct
		{	int32 *Val;
			uint16 Par;
		}st_DataType_int32;
		typedef struct				
		{	uint8 *Val;
			uint16 Par;
		}st_DataType_uint8;
		typedef struct
		{	uint16 *Val;
			uint16 Par;
		}st_DataType_uint16;
	#endif
/*=========================================Public Ram=========================================================*/
	#ifdef De_AppAgreeDataSensor_Compiler
		static uint8 BackDateTimer[7]={0,0,0,0,0,0,0};
		static const st_DataType_uint8	CN_Ba_st_DataType_uint8[]=
		{{&App_CN_st_WorkFlow_Table.CN_st_WorkVal_Tabel.CN_st_AgreeOn_SetVidType_Par.Switch1,De_Sensor_WordPar_Switch1},
		 {&App_CN_st_WorkFlow_Table.CN_st_WorkVal_Tabel.CN_st_AgreeOn_SetVidType_Par.Switch2,De_Sensor_WordPar_Switch2},
		 {&App_CN_st_WorkFlow_Table.CN_st_WorkVal_Tabel.CN_st_AgreeOn_SetVidType_Par.Switch3,De_Sensor_WordPar_Switch3},
		 {&App_CN_st_WorkFlow_Table.CN_st_WorkVal_Tabel.CN_st_AgreeOn_SetVidType_Par.Switch4,De_Sensor_WordPar_Switch4},
		 {&App_CN_st_WorkFlow_Table.CN_st_WorkVal_Tabel.CN_st_AgreeOn_SetVidType_Par.Switch5,De_Sensor_WordPar_Switch5},
		 {&App_CN_st_WorkFlow_Table.CN_st_WorkVal_Tabel.CN_st_AgreeOn_SetVidType_Par.Switch6,De_Sensor_WordPar_Switch6},
		 {&App_CN_st_WorkFlow_Table.CN_st_WorkVal_Tabel.CN_st_AgreeOn_SetVidType_Par.Switch7,De_Sensor_WordPar_Switch7},
		 {&App_CN_st_WorkFlow_Table.CN_st_WorkVal_Tabel.CN_st_AgreeOn_SetVidType_Par.Switch8,De_Sensor_WordPar_Switch8},
		 {&App_CN_st_WorkFlow_Table.CN_st_WorkVal_Tabel.CN_st_AgreeOn_SetVidType_Par.Switch9,De_Sensor_WordPar_Switch9},
		 {&App_CN_st_WorkFlow_Table.CN_st_WorkVal_Tabel.CN_st_AgreeOn_SetVidType_Par.Switch10,De_Sensor_WordPar_Switch10},
		 {&App_CN_st_WorkFlow_Table.CN_st_WorkVal_Tabel.CN_st_AgreeOn_SetVidType_Par.Switch11,De_Sensor_WordPar_Switch11},
		 {&App_CN_st_WorkFlow_Table.CN_st_WorkVal_Tabel.CN_st_AgreeOn_SetVidType_Par.Switch12,De_Sensor_WordPar_Switch12},
		 {&App_CN_st_WorkFlow_Table.CN_st_WorkVal_Tabel.CN_st_AgreeOn_SetVidType_Par.Switch13,De_Sensor_WordPar_Switch13},
		 {&App_CN_st_WorkFlow_Table.CN_st_WorkVal_Tabel.CN_st_AgreeOn_SetVidType_Par.Switch14,De_Sensor_WordPar_Switch14},
		 {&App_CN_st_WorkFlow_Table.CN_st_WorkVal_Tabel.CN_st_AgreeOn_SetVidType_Par.Switch15,De_Sensor_WordPar_Switch15},
		 {&App_CN_st_WorkFlow_Table.CN_st_WorkVal_Tabel.CN_st_AgreeOn_SetVidType_Par.Switch16,De_Sensor_WordPar_Switch16},
		 {&App_CN_st_WorkFlow_Table.CN_st_WorkVal_Tabel.CN_st_AgreeOn_SetVidType_Par.CN_Less_Switch1.OpenOrClose,De_Sensor_WordPar_Less_Switch1},
		 {&App_CN_st_WorkFlow_Table.CN_st_WorkVal_Tabel.CN_st_AgreeOn_SetVidType_Par.CN_Less_Switch2.OpenOrClose,De_Sensor_WordPar_Less_Switch2},
		 {&App_CN_st_WorkFlow_Table.CN_st_WorkVal_Tabel.CN_st_AgreeOn_SetVidType_Par.CN_Less_Switch3.OpenOrClose,De_Sensor_WordPar_Less_Switch3},
		 {&App_CN_st_WorkFlow_Table.CN_st_WorkVal_Tabel.CN_st_AgreeOn_SetVidType_Par.CN_Less_Switch4.OpenOrClose,De_Sensor_WordPar_Less_Switch4},
		 {&App_CN_st_WorkFlow_Table.CN_st_WorkVal_Tabel.CN_st_AgreeOn_SetVidType_Par.CN_Less_Switch5.OpenOrClose,De_Sensor_WordPar_Less_Switch5},
		 {&App_CN_st_WorkFlow_Table.CN_st_WorkVal_Tabel.CN_st_AgreeOn_SetVidType_Par.CN_Less_Switch6.OpenOrClose,De_Sensor_WordPar_Less_Switch6},
		 {&App_CN_st_WorkFlow_Table.CN_st_WorkVal_Tabel.CN_st_AgreeOn_SetVidType_Par.Sem,De_Sensor_WordPar_Sem},
		 {&App_CN_st_WorkFlow_Table.CN_st_WorkVal_Tabel.CN_st_AgreeOn_SetVidType_Par.OilBaifen,De_Sensor_WordPar_OilBaifen}
		};
		static const st_DataType_int32	CN_Ba_st_DataType_int32[]=
		{	{&App_CN_st_WorkFlow_Table.CN_st_WorkVal_Tabel.CN_st_AgreeOn_SetVidType_Par.Temp,De_Sensor_WordPar_Temp},
			{&App_CN_st_WorkFlow_Table.CN_st_WorkVal_Tabel.CN_st_AgreeOn_SetVidType_Par.CN_st_AgreeOn_Less_Temp1.Temp,De_Sensor_WordPar_Less_Temp1},
			{&App_CN_st_WorkFlow_Table.CN_st_WorkVal_Tabel.CN_st_AgreeOn_SetVidType_Par.CN_st_AgreeOn_Less_Temp2.Temp,De_Sensor_WordPar_Less_Temp2},
			{&App_CN_st_WorkFlow_Table.CN_st_WorkVal_Tabel.CN_st_AgreeOn_SetVidType_Par.CN_st_AgreeOn_Less_Temp3.Temp,De_Sensor_WordPar_Less_Temp3},
			{&App_CN_st_WorkFlow_Table.CN_st_WorkVal_Tabel.CN_st_AgreeOn_SetVidType_Par.CN_st_AgreeOn_Less_Temp4.Temp,De_Sensor_WordPar_Less_Temp4},
		};
		static const st_DataType_uint16	CN_st_DataType_uint16[]=
		{	{&App_CN_st_WorkFlow_Table.CN_st_WorkVal_Tabel.CN_st_AgreeOn_SetVidType_Par.Oil1,De_Sensor_WordPar_Oil1},
		 	{&App_CN_st_WorkFlow_Table.CN_st_WorkVal_Tabel.CN_st_AgreeOn_SetVidType_Par.Oil2,De_Sensor_WordPar_Oil2}
		};
		static uint32 AddTimeHigh=0;
		const st_Fun_AppAgreeDataSensor	CN_st_Fun_AppAgreeDataSensor={Init};
	#else
		extern const st_Fun_AppAgreeDataSensor	CN_st_Fun_AppAgreeDataSensor;



	#endif
