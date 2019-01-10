/*=========================================Include File=========================================================*/
#include "..\APP\config.h"
	#include "stdlib.h"
	#ifdef De_JugeOper_Compiler
		#include "..\File\rwFile.h"
		#include "..\miscellaneous\CodeTrans\AscNumber.h"
		#include "..\FilleData\FileData.h"
		#include "..\FilleData\TakeData.h"
		#include "..\AgreeOn\TzV2.1.h"
		#include "..\AppSendAgreeOn\AppSendAgreeOn.H"
	#endif
/*=========================================Define Data==========================================================*/
#ifdef De_JugeOper_Compiler	
	#define De_JugeOper_Warning_Yes									1
	#define De_JugeOper_Warning_No									0
	#define De_ParType_uint8					0
	#define De_ParType_uint16					1
	#define De_ParType_uint32					2
	#define De_ParType_int32					3
#endif
/*=========================================Data Define=========================================================*/
	typedef struct
	{	void (*Juge)(uint8 Number);
	}st_Fun_JugeOper;
#ifdef De_JugeOper_Compiler
	typedef struct
	{	void *State1;
		void *State2;
		void *State3;
	}st_Juge_void;
	typedef struct
	{	uint8 *State1;
		uint8 *State2;
		uint8 *State3;
	}st_Juge_uint8;
	typedef struct
	{	uint16 *State1;
		uint16 *State2;
		uint16 *State3;
	}st_Juge_uint16;
	typedef struct
	{	uint32 *State1;
		uint32 *State2;
		uint32 *State3;
	}st_Juge_uint32;
	typedef struct
	{	int16 *State1;
		int16 *State2;
		int16 *State3;
	}st_Juge_int32;
#endif
/*=========================================static Function=====================================================*/
	#ifdef De_JugeOper_Compiler	
		static void Juge(uint8 Number);
		static uint16 JugeAppair(uint8 Number,uint8 fd,uint16 Offset,uint8 Vid,uint16 ParWaring);
		static uint8 Warning(uint8 Number,void *Data);
	#endif
/*==========================================Public Ram=========================================================*/
	#ifdef De_JugeOper_Compiler
		const st_Fun_JugeOper	CN_st_Fun_JugeOper={Juge};
		static const uint8 CN_ParType[]=
		{	De_ParType_uint8,De_ParType_uint8,De_ParType_uint8,De_ParType_uint8,De_ParType_uint8,De_ParType_uint8,
			De_ParType_uint8,De_ParType_uint8,De_ParType_uint8,De_ParType_uint8,De_ParType_uint8,De_ParType_uint8,
			De_ParType_uint8,De_ParType_uint8,De_ParType_uint8,De_ParType_uint8,De_ParType_uint8,De_ParType_uint8,
			De_ParType_uint8,De_ParType_uint8,De_ParType_uint8,De_ParType_uint8,De_ParType_uint32,De_ParType_uint32,
			De_ParType_uint16,De_ParType_uint8,De_ParType_uint32,De_ParType_int32,De_ParType_uint16,De_ParType_uint32,
			De_ParType_uint16,De_ParType_uint8,De_ParType_int32,De_ParType_int32,De_ParType_int32,De_ParType_int32
		};
						
		static const st_Juge_void	CN_Ba_st_Juge_void[]=
		{	{&((st_AgreeOn_SetWaringTerm	*)(NULL))->CN_st_AgreeOn_SetVidType_Par[0].Switch1,
			&((st_AgreeOn_SetWaringTerm	*)(NULL))->CN_st_AgreeOn_SetVidType_Par[1].Switch1,
			&App_CN_st_WorkFlow_Table.CN_st_WorkVal_Tabel.CN_st_AgreeOn_SetVidType_Par.Switch1},
			{&((st_AgreeOn_SetWaringTerm*)(NULL))->CN_st_AgreeOn_SetVidType_Par[0].Switch2,&((st_AgreeOn_SetWaringTerm*)(NULL))->CN_st_AgreeOn_SetVidType_Par[1].Switch2,&App_CN_st_WorkFlow_Table.CN_st_WorkVal_Tabel.CN_st_AgreeOn_SetVidType_Par.Switch2},
			{&((st_AgreeOn_SetWaringTerm*)(NULL))->CN_st_AgreeOn_SetVidType_Par[0].Switch3,&((st_AgreeOn_SetWaringTerm*)(NULL))->CN_st_AgreeOn_SetVidType_Par[1].Switch3,&App_CN_st_WorkFlow_Table.CN_st_WorkVal_Tabel.CN_st_AgreeOn_SetVidType_Par.Switch3},
			{&((st_AgreeOn_SetWaringTerm*)(NULL))->CN_st_AgreeOn_SetVidType_Par[0].Switch4,&((st_AgreeOn_SetWaringTerm*)(NULL))->CN_st_AgreeOn_SetVidType_Par[1].Switch4,&App_CN_st_WorkFlow_Table.CN_st_WorkVal_Tabel.CN_st_AgreeOn_SetVidType_Par.Switch4},
			{&((st_AgreeOn_SetWaringTerm*)(NULL))->CN_st_AgreeOn_SetVidType_Par[0].Switch5,&((st_AgreeOn_SetWaringTerm*)(NULL))->CN_st_AgreeOn_SetVidType_Par[1].Switch5,&App_CN_st_WorkFlow_Table.CN_st_WorkVal_Tabel.CN_st_AgreeOn_SetVidType_Par.Switch5},
			{&((st_AgreeOn_SetWaringTerm*)(NULL))->CN_st_AgreeOn_SetVidType_Par[0].Switch6,&((st_AgreeOn_SetWaringTerm*)(NULL))->CN_st_AgreeOn_SetVidType_Par[1].Switch6,&App_CN_st_WorkFlow_Table.CN_st_WorkVal_Tabel.CN_st_AgreeOn_SetVidType_Par.Switch6},
			{&((st_AgreeOn_SetWaringTerm*)(NULL))->CN_st_AgreeOn_SetVidType_Par[0].Switch7,&((st_AgreeOn_SetWaringTerm*)(NULL))->CN_st_AgreeOn_SetVidType_Par[1].Switch7,&App_CN_st_WorkFlow_Table.CN_st_WorkVal_Tabel.CN_st_AgreeOn_SetVidType_Par.Switch7},
			{&((st_AgreeOn_SetWaringTerm*)(NULL))->CN_st_AgreeOn_SetVidType_Par[0].Switch8,&((st_AgreeOn_SetWaringTerm*)(NULL))->CN_st_AgreeOn_SetVidType_Par[1].Switch8,&App_CN_st_WorkFlow_Table.CN_st_WorkVal_Tabel.CN_st_AgreeOn_SetVidType_Par.Switch8},
			{&((st_AgreeOn_SetWaringTerm*)(NULL))->CN_st_AgreeOn_SetVidType_Par[0].Switch9,&((st_AgreeOn_SetWaringTerm*)(NULL))->CN_st_AgreeOn_SetVidType_Par[1].Switch9,&App_CN_st_WorkFlow_Table.CN_st_WorkVal_Tabel.CN_st_AgreeOn_SetVidType_Par.Switch9},
			{&((st_AgreeOn_SetWaringTerm*)(NULL))->CN_st_AgreeOn_SetVidType_Par[0].Switch10,&((st_AgreeOn_SetWaringTerm*)(NULL))->CN_st_AgreeOn_SetVidType_Par[1].Switch10,&App_CN_st_WorkFlow_Table.CN_st_WorkVal_Tabel.CN_st_AgreeOn_SetVidType_Par.Switch10},
			{&((st_AgreeOn_SetWaringTerm*)(NULL))->CN_st_AgreeOn_SetVidType_Par[0].Switch11,&((st_AgreeOn_SetWaringTerm*)(NULL))->CN_st_AgreeOn_SetVidType_Par[1].Switch11,&App_CN_st_WorkFlow_Table.CN_st_WorkVal_Tabel.CN_st_AgreeOn_SetVidType_Par.Switch11},
			{&((st_AgreeOn_SetWaringTerm*)(NULL))->CN_st_AgreeOn_SetVidType_Par[0].Switch12,&((st_AgreeOn_SetWaringTerm*)(NULL))->CN_st_AgreeOn_SetVidType_Par[1].Switch12,&App_CN_st_WorkFlow_Table.CN_st_WorkVal_Tabel.CN_st_AgreeOn_SetVidType_Par.Switch12},
			{&((st_AgreeOn_SetWaringTerm*)(NULL))->CN_st_AgreeOn_SetVidType_Par[0].Switch13,&((st_AgreeOn_SetWaringTerm*)(NULL))->CN_st_AgreeOn_SetVidType_Par[1].Switch13,&App_CN_st_WorkFlow_Table.CN_st_WorkVal_Tabel.CN_st_AgreeOn_SetVidType_Par.Switch13},
			{&((st_AgreeOn_SetWaringTerm*)(NULL))->CN_st_AgreeOn_SetVidType_Par[0].Switch14,&((st_AgreeOn_SetWaringTerm*)(NULL))->CN_st_AgreeOn_SetVidType_Par[1].Switch14,&App_CN_st_WorkFlow_Table.CN_st_WorkVal_Tabel.CN_st_AgreeOn_SetVidType_Par.Switch14},
			{&((st_AgreeOn_SetWaringTerm*)(NULL))->CN_st_AgreeOn_SetVidType_Par[0].Switch15,&((st_AgreeOn_SetWaringTerm*)(NULL))->CN_st_AgreeOn_SetVidType_Par[1].Switch15,&App_CN_st_WorkFlow_Table.CN_st_WorkVal_Tabel.CN_st_AgreeOn_SetVidType_Par.Switch15},
			{&((st_AgreeOn_SetWaringTerm*)(NULL))->CN_st_AgreeOn_SetVidType_Par[0].Switch16,&((st_AgreeOn_SetWaringTerm*)(NULL))->CN_st_AgreeOn_SetVidType_Par[1].Switch16,&App_CN_st_WorkFlow_Table.CN_st_WorkVal_Tabel.CN_st_AgreeOn_SetVidType_Par.Switch16},
			{&((st_AgreeOn_SetWaringTerm*)(NULL))->CN_st_AgreeOn_SetVidType_Par[0].CN_Less_Switch1.OpenOrClose,&((st_AgreeOn_SetWaringTerm*)(NULL))->CN_st_AgreeOn_SetVidType_Par[1].CN_Less_Switch1.OpenOrClose,&App_CN_st_WorkFlow_Table.CN_st_WorkVal_Tabel.CN_st_AgreeOn_SetVidType_Par.CN_Less_Switch1.OpenOrClose},
			{&((st_AgreeOn_SetWaringTerm*)(NULL))->CN_st_AgreeOn_SetVidType_Par[0].CN_Less_Switch2.OpenOrClose,&((st_AgreeOn_SetWaringTerm*)(NULL))->CN_st_AgreeOn_SetVidType_Par[1].CN_Less_Switch2.OpenOrClose,&App_CN_st_WorkFlow_Table.CN_st_WorkVal_Tabel.CN_st_AgreeOn_SetVidType_Par.CN_Less_Switch2.OpenOrClose},
			{&((st_AgreeOn_SetWaringTerm*)(NULL))->CN_st_AgreeOn_SetVidType_Par[0].CN_Less_Switch3.OpenOrClose,&((st_AgreeOn_SetWaringTerm*)(NULL))->CN_st_AgreeOn_SetVidType_Par[1].CN_Less_Switch3.OpenOrClose,&App_CN_st_WorkFlow_Table.CN_st_WorkVal_Tabel.CN_st_AgreeOn_SetVidType_Par.CN_Less_Switch3.OpenOrClose},
			{&((st_AgreeOn_SetWaringTerm*)(NULL))->CN_st_AgreeOn_SetVidType_Par[0].CN_Less_Switch4.OpenOrClose,&((st_AgreeOn_SetWaringTerm*)(NULL))->CN_st_AgreeOn_SetVidType_Par[1].CN_Less_Switch4.OpenOrClose,&App_CN_st_WorkFlow_Table.CN_st_WorkVal_Tabel.CN_st_AgreeOn_SetVidType_Par.CN_Less_Switch4.OpenOrClose},
			{&((st_AgreeOn_SetWaringTerm*)(NULL))->CN_st_AgreeOn_SetVidType_Par[0].CN_Less_Switch5.OpenOrClose,&((st_AgreeOn_SetWaringTerm*)(NULL))->CN_st_AgreeOn_SetVidType_Par[1].CN_Less_Switch5.OpenOrClose,&App_CN_st_WorkFlow_Table.CN_st_WorkVal_Tabel.CN_st_AgreeOn_SetVidType_Par.CN_Less_Switch5.OpenOrClose},
			{&((st_AgreeOn_SetWaringTerm*)(NULL))->CN_st_AgreeOn_SetVidType_Par[0].CN_Less_Switch6.OpenOrClose,&((st_AgreeOn_SetWaringTerm*)(NULL))->CN_st_AgreeOn_SetVidType_Par[1].CN_Less_Switch6.OpenOrClose,&App_CN_st_WorkFlow_Table.CN_st_WorkVal_Tabel.CN_st_AgreeOn_SetVidType_Par.CN_Less_Switch6.OpenOrClose},
			{&((st_AgreeOn_SetWaringTerm*)(NULL))->CN_st_AgreeOn_SetVidType_Par[0].AccTimer,&((st_AgreeOn_SetWaringTerm*)(NULL))->CN_st_AgreeOn_SetVidType_Par[1].AccTimer,&App_CN_st_WorkFlow_Table.CN_st_WorkVal_Tabel.CN_st_AgreeOn_SetVidType_Par.AccTimer},
			{&((st_AgreeOn_SetWaringTerm*)(NULL))->CN_st_AgreeOn_SetVidType_Par[0].Mileage,&((st_AgreeOn_SetWaringTerm*)(NULL))->CN_st_AgreeOn_SetVidType_Par[1].Mileage,&App_CN_st_WorkFlow_Table.CN_st_WorkVal_Tabel.CN_st_AgreeOn_SetVidType_Par.Mileage},
			{&((st_AgreeOn_SetWaringTerm*)(NULL))->CN_st_AgreeOn_SetVidType_Par[0].Oil1,&((st_AgreeOn_SetWaringTerm*)(NULL))->CN_st_AgreeOn_SetVidType_Par[1].Oil1,&App_CN_st_WorkFlow_Table.CN_st_WorkVal_Tabel.CN_st_AgreeOn_SetVidType_Par.Oil1},
			{&((st_AgreeOn_SetWaringTerm*)(NULL))->CN_st_AgreeOn_SetVidType_Par[0].Sem,&((st_AgreeOn_SetWaringTerm*)(NULL))->CN_st_AgreeOn_SetVidType_Par[1].Sem,&App_CN_st_WorkFlow_Table.CN_st_WorkVal_Tabel.CN_st_AgreeOn_SetVidType_Par.Sem},
			{&((st_AgreeOn_SetWaringTerm*)(NULL))->CN_st_AgreeOn_SetVidType_Par[0].SendOilTimer,&((st_AgreeOn_SetWaringTerm*)(NULL))->CN_st_AgreeOn_SetVidType_Par[1].SendOilTimer,&App_CN_st_WorkFlow_Table.CN_st_WorkVal_Tabel.CN_st_AgreeOn_SetVidType_Par.SendOilTimer},
			{&((st_AgreeOn_SetWaringTerm*)(NULL))->CN_st_AgreeOn_SetVidType_Par[0].Temp,&((st_AgreeOn_SetWaringTerm*)(NULL))->CN_st_AgreeOn_SetVidType_Par[1].Temp,&App_CN_st_WorkFlow_Table.CN_st_WorkVal_Tabel.CN_st_AgreeOn_SetVidType_Par.Temp},
			{&((st_AgreeOn_SetWaringTerm*)(NULL))->CN_st_AgreeOn_SetVidType_Par[0].Oil2,&((st_AgreeOn_SetWaringTerm*)(NULL))->CN_st_AgreeOn_SetVidType_Par[1].Oil2,&App_CN_st_WorkFlow_Table.CN_st_WorkVal_Tabel.CN_st_AgreeOn_SetVidType_Par.Oil2},
			{&((st_AgreeOn_SetWaringTerm*)(NULL))->CN_st_AgreeOn_SetVidType_Par[0].Pulse,&((st_AgreeOn_SetWaringTerm*)(NULL))->CN_st_AgreeOn_SetVidType_Par[1].Pulse,&App_CN_st_WorkFlow_Table.CN_st_WorkVal_Tabel.CN_st_AgreeOn_SetVidType_Par.Pulse},
			{&((st_AgreeOn_SetWaringTerm*)(NULL))->CN_st_AgreeOn_SetVidType_Par[0].Humidity,&((st_AgreeOn_SetWaringTerm*)(NULL))->CN_st_AgreeOn_SetVidType_Par[1].Humidity,&App_CN_st_WorkFlow_Table.CN_st_WorkVal_Tabel.CN_st_AgreeOn_SetVidType_Par.Humidity},
			{&((st_AgreeOn_SetWaringTerm*)(NULL))->CN_st_AgreeOn_SetVidType_Par[0].OilBaifen,&((st_AgreeOn_SetWaringTerm*)(NULL))->CN_st_AgreeOn_SetVidType_Par[1].OilBaifen,&App_CN_st_WorkFlow_Table.CN_st_WorkVal_Tabel.CN_st_AgreeOn_SetVidType_Par.OilBaifen},
			{&((st_AgreeOn_SetWaringTerm*)(NULL))->CN_st_AgreeOn_SetVidType_Par[0].CN_st_AgreeOn_Less_Temp1.Temp,&((st_AgreeOn_SetWaringTerm*)(NULL))->CN_st_AgreeOn_SetVidType_Par[1].CN_st_AgreeOn_Less_Temp1.Temp,&App_CN_st_WorkFlow_Table.CN_st_WorkVal_Tabel.CN_st_AgreeOn_SetVidType_Par.CN_st_AgreeOn_Less_Temp1.Temp},
			{&((st_AgreeOn_SetWaringTerm*)(NULL))->CN_st_AgreeOn_SetVidType_Par[0].CN_st_AgreeOn_Less_Temp2.Temp,&((st_AgreeOn_SetWaringTerm*)(NULL))->CN_st_AgreeOn_SetVidType_Par[1].CN_st_AgreeOn_Less_Temp2.Temp,&App_CN_st_WorkFlow_Table.CN_st_WorkVal_Tabel.CN_st_AgreeOn_SetVidType_Par.CN_st_AgreeOn_Less_Temp2.Temp},
			{&((st_AgreeOn_SetWaringTerm*)(NULL))->CN_st_AgreeOn_SetVidType_Par[0].CN_st_AgreeOn_Less_Temp3.Temp,&((st_AgreeOn_SetWaringTerm*)(NULL))->CN_st_AgreeOn_SetVidType_Par[1].CN_st_AgreeOn_Less_Temp3.Temp,&App_CN_st_WorkFlow_Table.CN_st_WorkVal_Tabel.CN_st_AgreeOn_SetVidType_Par.CN_st_AgreeOn_Less_Temp3.Temp},
			{&((st_AgreeOn_SetWaringTerm*)(NULL))->CN_st_AgreeOn_SetVidType_Par[0].CN_st_AgreeOn_Less_Temp4.Temp,&((st_AgreeOn_SetWaringTerm*)(NULL))->CN_st_AgreeOn_SetVidType_Par[1].CN_st_AgreeOn_Less_Temp4.Temp,&App_CN_st_WorkFlow_Table.CN_st_WorkVal_Tabel.CN_st_AgreeOn_SetVidType_Par.CN_st_AgreeOn_Less_Temp4.Temp}
		};

	#else
		extern const st_Fun_JugeOper	CN_st_Fun_JugeOper;
	#endif




