#include "..\..\Dev\Sensor\_PuSensor.h"
#define De_AgreeOn_LookPar_YesData						0x01
#define De_AgreeOn_LookPar_NoData						0x02
#define De_AgreeOn_LookPar_Erro							0x03
/*==============================================基本协议========================================================*/
/*--------------------------------------------获取服务器通讯参数---------------------------------------------*/
	#define De_AgreeOn_State_Suc							0					//状态正常
	#define De_AgreeOn_State_Erro							1
	typedef struct
	{	st_Data_Gps		CN_st_Data_Gps;
		uint8 State[32];
	}st_AgreeOn_Send_Basic;
/*-----------------------------------------------登录指令-----------------------------------------------------*/
//登录指令,与获取通讯参数指令一样
/*-----------------------------------------------休眠指令-----------------------------------------------------*/
//休眠指令,与获取通讯参数指令一样
/*-----------------------------------------------关机指令-----------------------------------------------------*/
//关机指令,与获取通讯参数指令一样
/*--------------------------------------------定位终端命令应答------------------------------------------------*/
	typedef struct
	{	uint16 Number;
		uint16 OrderID;	
		uint8 Result;
	}st_AgreeOn_Send_Answer;
/*--------------------------------------------上传位置信息----------------------------------------------------*/
	//上传位置信息,与获取通讯参数指令一样
/*-------------------------------------------上传菜单信息-----------------------------------------------------*/
	typedef struct
	{	uint8 ID;
		uint8 Cut[40];
	}st_AgreeOn_Send_Menum;
/*--------------------------------上传带菜单的调度信息的反馈信息----------------------------------------------*/
	typedef struct
	{	uint16 ID;
		uint8 ResultID;
		uint8 Cut[40];
	}st_AgreeOn_Send_TxtMenum;
	//内容见<上传菜单信息>
/*-------------------------------------------查询定位终端参数-------------------------------------------------*/
	//内容见接受结构体<st_AgreeOn_Agree_Par>
/*-------------------------------------------上传软件升级状态-------------------------------------------------*/
	typedef struct
	{
	  	uint8 Result;
	
	}st_AgreeOn_Send_UpdateSoftWare;
/*-------------------------------------------上传报警状态---------------------------------------------------*/	
	typedef struct
	{	uint8 Work;
		uint8 Battery;
	}st_st_AgreeOn_Send_State;
	#define De_st_AgreeOn_Send_Waring_Type_Yes				0
	#define De_st_AgreeOn_Send_Waring_Type_No				1
	#define De_AgreeOn_Send_Less_State_Suc					0x00  				//传感器正常
	#define De_AgreeOn_Send_Less_State_Erro					0x11				//传感器失败
	typedef struct
	{	uint8 Type[sizeof(CN_Ba_WordPar)/sizeof(uint16)];
		st_AgreeOn_SetVidType_Par	CN_st_AgreeOn_SetVidType_Par; 	
	}st_WorkVal_Tabel;
	typedef struct
	{ 	uint8 Type;
		st_AgreeOn_Send_Basic	CN_st_AgreeOn_Send_Basic;
		st_WorkVal_Tabel	CN_st_WorkVal_Tabel;
		st_Sensor_State	CN_st_Sensor_State[sizeof(CN_Ba_LessPar)/sizeof(uint16)];
	}st_AgreeOn_Send_Waring;
	
/*=========================================功能扩展协议==========================================================*/	
/*-------------------------------------------上传照片1---------------------------------------------------*/
	typedef struct
	{	uint8 Type;
		uint8 Pro;
		uint8 SecSum;
		uint8 SecNumber;
		st_AgreeOn_Send_Basic	CN_st_AgreeOn_Send_Basic;
		uint16 SizeofBuf;
		uint8 Buf[512-43];
	}st_AgreeOn_Send_UploaderJpg1;
/*-------------------------------------------上传照片2---------------------------------------------------*/
	typedef struct
	{	uint8 SecSum;
		uint8 SecNumber;
		st_AgreeOn_Send_Basic	CN_st_AgreeOn_Send_Basic;
		st_WorkVal_Tabel	CN_st_WorkVal_Tabel;
		uint16 SizeofBuf;
		uint8 Buf[512-50];
	}st_AgreeOn_Send_UploaderJpg2;
/*----------------------------------------上传定位终端工作参数------------------------------------------*/
	typedef struct
	{ 	uint8 Type;
		st_AgreeOn_Send_Basic	CN_st_AgreeOn_Send_Basic;
		st_WorkVal_Tabel	CN_st_WorkVal_Tabel;
	}st_AgreeOn_Send_UploaderPar;

	typedef struct
	{	uint8 Type;
		uint16 ID;
		uint8 InputOrOut;
		st_AgreeOn_Send_Basic	CN_st_AgreeOn_Send_Basic;
	}st_AgreeOn_Send_OutRoadMap;

	

	typedef struct
	{	st_AgreeOn_Send_Basic	CN_st_AgreeOn_Send_Basic;
		uint8 ID[10];
		uint8 State;
	}st_AgreeOn_Send_UpLoaderDriver;

	typedef struct
	{	st_AgreeOn_Send_Basic	CN_st_AgreeOn_Send_Basic;
		uint8 ID[10];
		uint8 Phone[15];
		uint8 Cut[160];
	}st_AgreeOn_Send_UpLoaderHandMess;

	typedef struct
	{	uint16 ID;
	}st_AgreeOn_Send_UpLoaderFrom;

	typedef struct
	{	uint16 ID;
		uint16 CanceID;
	}st_AgreeOn_Send_OverFromErro;
	typedef struct
	{	st_AgreeOn_Send_Basic	CN_st_AgreeOn_Send_Basic;
		uint8 TradeType;
		uint8 CarNumber[6];
		uint8 UpCarDateTime[7];
		uint32 WaintingTime;
		uint32 Space;
		uint32 Price;
		uint32 DownCarPrice;
		uint32 NonSpace;
		uint8 CardType;
		uint8 CardNumber[12];
		uint32 TradeFromPrice;
		uint32 TradePrice;
		uint16 Count;
		uint32 FlowNumber;
		uint32 TAC;
		uint8 DriverID[10];
		uint8 PSAM[6];
		uint8 POSNumber[4];
	}st_AgreeOn_Send_PriceData;
	typedef struct
	{	st_AgreeOn_Reduce	CN_st_AgreeOn_Reduce;
		uint16 Data[33]; 
		uint16 Number;
		uint16 (*ReadParTable)(uint16 Recoder,st_AgreeOn_Send_UploaderPar	*ptst_AgreeOn_Send_UploaderPar);
	}st_Reduce_Table;
	typedef struct
	{	st_AgreeOn_Send_Basic	CN_Ba_st_AgreeOn_Send_Basic;
	}st_Reduce_Basic;
  
 typedef struct
{	uint16 ParID;
	uint16 Number;
	uint8  X_BUF[512];
	uint16 DataLen[33];
	st_AgreeOn_Send_Basic	CN_Ba_st_AgreeOn_Send_Basic;
}st_AgreeOn_Send_LogAndNoSem;
	
			
