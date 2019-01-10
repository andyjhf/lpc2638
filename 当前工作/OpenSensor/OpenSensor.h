/*=========================================Include File=========================================================*/	
	#include "..\APP\config.h"
	#include "stdlib.h"
	#ifdef De_OpenSensor_Compiler
		#include "..\File\rwFile.h"
		#include "..\miscellaneous\CodeTrans\AscNumber.h"
		#include "..\FilleData\FileData.h"
		#include "..\FilleData\TakeData.h"
		#include "..\Dev\Sensor\Sensor.h"
		#include "..\Control\Sensor\SensorContr.h"
		#include "..\AppSensor\AppAgreeDataSensor.h"
	#endif
/*=========================================static Function=====================================================*/
	#ifdef De_OpenSensor_Compiler	
	static void Init(void);
	#endif	
	typedef struct
	{	void (*Init)(void);
	}st_Fun_OpenSensor;



/*===========================================Public Ram========================================================*/
	#ifdef De_OpenSensor_Compiler
	/*static const st_AgreeOn_SetVidType_Par	CN_Ba_st_AgreeOn_SetVidType_Par=
	{	De_Sensor_Par_Onoff_Close,
		De_Sensor_Par_Onoff_Close,
		De_Sensor_Par_Onoff_Close,
		De_Sensor_Par_Onoff_Close,
		De_Sensor_Par_Onoff_Close,
		De_Sensor_Par_Onoff_Close,
		De_Sensor_Par_Onoff_Close,
		De_Sensor_Par_Onoff_Close,
		De_Sensor_Par_Onoff_Close,
		De_Sensor_Par_Onoff_Close,
		De_Sensor_Par_Onoff_Close,
		De_Sensor_Par_Onoff_Close,
		De_Sensor_Par_Onoff_Close,
		De_Sensor_Par_Onoff_Close,
		De_Sensor_Par_Onoff_Close,
		De_Sensor_Par_Onoff_Close,
		{De_WordPar_NoAdree,De_Sensor_Par_Onoff_Close,De_Sensor_State_Suc},
		{De_WordPar_NoAdree,De_Sensor_Par_Onoff_Close,De_Sensor_State_Suc},
		{De_WordPar_NoAdree,De_Sensor_Par_Onoff_Close,De_Sensor_State_Suc},
		{De_WordPar_NoAdree,De_Sensor_Par_Onoff_Close,De_Sensor_State_Suc},
		{De_WordPar_NoAdree,De_Sensor_Par_Onoff_Close,De_Sensor_State_Suc},
		{De_WordPar_NoAdree,De_Sensor_Par_Onoff_Close,De_Sensor_State_Suc},
		0,
		0,
		0,
		0,
		0,
		0,
		0,
		0,
		0,
		0,
		{De_WordPar_NoAdree,0,De_Sensor_State_Suc},
		{De_WordPar_NoAdree,0,De_Sensor_State_Suc},
		{De_WordPar_NoAdree,0,De_Sensor_State_Suc},
		{De_WordPar_NoAdree,0,De_Sensor_State_Suc}
	}; */
	static const uint16 CN_Ba_OutPar[]=
	{	De_Sensor_WordPar_Gps,De_Sensor_WordPar_Mileage,De_Sensor_WordPar_AreaCirc,
		De_Sensor_WordPar_Arearect,De_Sensor_WordPar_Help,De_Sensor_WordPar_VaCheck
	};
	
	static const st_WorkFlow_Table	CN_Ba_st_WorkFlow_Table=
	{	{0x20,0x01,0x01,0x01,0x00,0x00,0x00},
		{0,0,0,0,0,0,0,0,0,0},

		{	{	{	{0x20,0x01,0x01,0x01,0x00,0x00,0x00},'V','N','E',0,0,0,0
				},
				{0,0}
			},
			{De_AgreeOn_State_Erro,'N','E',De_AgreeOn_State_Suc,De_AgreeOn_State_Suc,
			De_AgreeOn_State_Suc,De_AgreeOn_State_Suc,De_AgreeOn_State_Suc,De_AgreeOn_State_Suc,De_AgreeOn_State_Suc,
			De_AgreeOn_State_Suc,De_AgreeOn_State_Suc,De_AgreeOn_State_Suc,De_AgreeOn_State_Suc,De_AgreeOn_State_Suc
			,De_AgreeOn_State_Suc,De_AgreeOn_State_Suc,De_AgreeOn_State_Suc,De_AgreeOn_State_Suc,De_AgreeOn_State_Suc,
			De_AgreeOn_State_Suc,De_AgreeOn_State_Suc,De_AgreeOn_State_Suc,De_AgreeOn_State_Suc,De_AgreeOn_State_Suc,
			De_AgreeOn_State_Suc,De_AgreeOn_State_Suc,De_AgreeOn_State_Suc,De_AgreeOn_State_Suc,De_AgreeOn_State_Suc,
			De_AgreeOn_State_Suc,De_AgreeOn_State_Suc},
		},
		{	{De_st_AgreeOn_Send_Waring_Type_No,De_st_AgreeOn_Send_Waring_Type_No,De_st_AgreeOn_Send_Waring_Type_No,
			De_st_AgreeOn_Send_Waring_Type_No,De_st_AgreeOn_Send_Waring_Type_No,De_st_AgreeOn_Send_Waring_Type_No,
			De_st_AgreeOn_Send_Waring_Type_No,De_st_AgreeOn_Send_Waring_Type_No,De_st_AgreeOn_Send_Waring_Type_No,
			De_st_AgreeOn_Send_Waring_Type_No,De_st_AgreeOn_Send_Waring_Type_No,De_st_AgreeOn_Send_Waring_Type_No,
			De_st_AgreeOn_Send_Waring_Type_No,De_st_AgreeOn_Send_Waring_Type_No,De_st_AgreeOn_Send_Waring_Type_No,
			De_st_AgreeOn_Send_Waring_Type_No,De_st_AgreeOn_Send_Waring_Type_No,De_st_AgreeOn_Send_Waring_Type_No,
			De_st_AgreeOn_Send_Waring_Type_No,De_st_AgreeOn_Send_Waring_Type_No,De_st_AgreeOn_Send_Waring_Type_No,
			De_st_AgreeOn_Send_Waring_Type_No,De_st_AgreeOn_Send_Waring_Type_No,De_st_AgreeOn_Send_Waring_Type_No,
			De_st_AgreeOn_Send_Waring_Type_No,De_st_AgreeOn_Send_Waring_Type_No,De_st_AgreeOn_Send_Waring_Type_No,
			De_st_AgreeOn_Send_Waring_Type_No,De_st_AgreeOn_Send_Waring_Type_No,De_st_AgreeOn_Send_Waring_Type_No,
			De_st_AgreeOn_Send_Waring_Type_No,De_st_AgreeOn_Send_Waring_Type_No,De_st_AgreeOn_Send_Waring_Type_No,
			De_st_AgreeOn_Send_Waring_Type_No,De_st_AgreeOn_Send_Waring_Type_No,De_st_AgreeOn_Send_Waring_Type_No,},
			{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,{0,0,0},{0,0,0},{0,0,0},{0,0,0},{0,0,0},{0,0,0},
			0,0,0,0,0,0,0,0,0,0,{0,0,0},{0,0,0},{0,0,0},{0,0,0}
			}
		}
	};
	
	
	const st_Fun_OpenSensor	CN_st_Fun_OpenSensor={Init};

	#else
	extern const st_Fun_OpenSensor CN_st_Fun_OpenSensor;	
	#endif
