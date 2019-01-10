/*==========================================Include File========================================================*/	
	#include "..\..\APP\config.h"
	#include "stdlib.h"
	//#include "..\..\File\rwFile.h"
	#ifdef De_DataTrans_Compiler
		#include "..\..\miscellaneous\CodeTrans\AscNumber.h"
		#include "..\..\HardWare\Gps\Gps.h"
		#include "..\FilleData\FileData.h"
		#include "..\..\miscellaneous\Date\Date.h"
	#endif

/*=========================================Define Data==========================================================*/
  	#define De_Acc_State_Close						1
	#define De_Suc_State							0
	
	#define De_Erro_State_GpsNosem						1
	#define De_Erro_State_GpsBad						2
	#define De_Erro_State_Speed							3	
	#define De_State_Voltage_Bad						4
	#define De_Erro_State_GsmBad						5
	#define De_Event_No									0xff




	/*++++++++++++++++++++++++++++++++++数据解析一览表+++++++++++++++++++++++++++++++++++++++++*/
	#ifdef	De_DataTrans_Compiler
		#define De_DataTrans_Gps_Timer							0				//hhmmss
		#define De_DataTrans_Gps_Latitude						De_DataTrans_Gps_Timer+6	//aaaaaaaa
		#define De_DataTrans_Gps_LongHem						De_DataTrans_Gps_Latitude+8
		#define De_DataTrans_Gps_Location						De_DataTrans_Gps_LongHem+9
		#define De_DataTrans_Gps_Speed							De_DataTrans_Gps_Location+1
		#define De_DataTrans_Gps_Angle							De_DataTrans_Gps_Speed+2
		#define De_DataTrans_Gps_Year							De_DataTrans_Gps_Angle+2
		#define De_DataTrans_Gps_State							De_DataTrans_Gps_Year+6
/*=======================================Static Function=======================================================*/
	
		static void Trans_Gps_Timer(st_Data_Gps	*ptst_Data_Gps,uint8 *OutBuf);				//时间转换
		static void Trans_Gps_Latitude(st_Data_Gps	*ptst_Data_Gps,uint8 *OutBuf);			//纬度转化
		static void Trans_Gps_LongHem(st_Data_Gps	*ptst_Data_Gps,uint8 *OutBuf);			//经度转换
		static uint8 Trans_Gps_Location(st_Data_Gps	*ptst_Data_Gps);							//定位状态
		static void Trans_Gps_Speed(st_Data_Gps	*ptst_Data_Gps,uint8 *OutBuf);						//速度
		static void Trans_Gps_Angle(st_Data_Gps	*ptst_Data_Gps,uint8 *OutBuf);						//角度 
		static void Trans_Gps_Year(st_Data_Gps	*ptst_Data_Gps,uint8 *OutBuf);					//年
		static void Trans_Gps_State(st_Sys_State	*ptst_Sys_State,uint8 *OutBuf);
		uint8 Trans_Gps(st_Data_Gps	*ptst_Data_Gps,st_Sys_State *ptst_Sys_State,uint8 *OutBuf);
		uint8 Trans_Gps_Hand(st_Data_Gps	*ptst_Data_Gps,st_Sys_State *ptst_Sys_State,uint8 *OutBuf);
	
	/*=========================================Public Function=====================================================*/
	
#endif


