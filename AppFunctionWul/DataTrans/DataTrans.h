/*==========================================Include File========================================================*/	
	#include "..\..\APP\config.h"
	#include "stdlib.h"
	#ifdef De_DataTrans_Compiler
		#include "..\..\miscellaneous\CodeTrans\AscNumber.h"
		//#include "..\..\HardWare\Gps\Gps.h"
		#include "..\..\Control\Gps\GpsTask.h"
		#include "..\FilleData\FileData.h"
		#include "..\..\miscellaneous\Date\Date.h"
		#include "..\..\File\rwFile.h"
		#include "..\..\Control\Gprs\GPRS.h"
	#endif

/*=========================================Define Data==========================================================*/
  	#define	De_AppGprs_Com_Answer_No									0					//不需要应答
	#define De_AppGprs_Com_Answer_Yes									1					//需要应答
	#define De_IP_Com_AgreeOn											2					//物流通讯协议版本号
	
	/*************************************Gps到物流协议解析一览表***************************************/
	#ifdef De_DataTrans_Compiler
		
		/*************************************状态位解析对应表*******************************************/
		#define De_FileData_GpsLoc_Number								0				//Gps定位有效
		#define De_FileData_LatHem_Number								1				//GPS南北
		#define De_FileData_LongHem_Number								2				//GPS东西
		#define De_FileData_Contr_Number								7				//车辆控制
		#define De_FileData_Acc_Number									8				//ACC状态	
		#define De_FileData_CarSpace_Number								9				//车辆状态位
		#define De_FileData_Work_Number									10				//车辆运营状态
		#define De_FileData_Operation_Number							11				//发动机状态
		#define De_FileData_Help_Number									16				//求助报警
		#define De_FileData_HighSpeed_Number							17				//超过速度
		#define De_FileData_Watch_Number								18				//视屏情况
		#define De_FileData_LowVlo_Number								19				//低电压报警
		#define De_FileData_CloseVlo_Number								20				//断电报警
		#define De_FileData_LowSpeed_Number								21				//低速度
		#define De_FileData_GpsBad_Number								25				//GPS模块故障
		#define De_FileData_GpsOpencircuit_Number						26				//GPS天线开路
		#define De_FileData_GpsShortCircuit_Number						27				//Gps天线短路
		#define De_FileData_LCD_Number									28				//LCD故障
	#endif
	
   	/*++++++++++++++++++++++++++++++++++++++系统各个状态位对应表+++++++++++++++++++++++++++++++++++++++++++++++*/
	#define De_FileData_CarSpace_State								0				//空车
	#define De_FileData_CarSpace_State_Full							1				//重车
	#define De_FileData_Contrl_Open									1				//车辆控制
	#define De_FileData_Contrl_Close								0				//车辆不控制
	#define De_FileData_Acc_Open									1				//ACC打开
	#define De_FileData_Acc_Close									0				//ACC关闭
	#define De_FileData_Work_Open									1				//车辆运营
	#define De_FileData_Work_Close									0				//车辆停止运营
	#define De_FileData_Operation_Open								1				//发动机运行
	#define De_FileData_Operation_Close								0				//发动机不运行
	#define De_FileData_Help_Open									1				//求助报警
	#define De_FileData_Help_Close									0				//不求租报警
	#define De_FileData_HighSpeed_Open								1				//超过速度
	#define De_FileData_HighSpeed_Close								0				//不超过速度
	#define De_FileData_Watch_Close									1				//视屏擦除
	#define De_FileData_Watch_Open									0				//视屏正常	
	#define De_FileData_LowVlo_Open									1				//低电压报警
	#define De_FileData_LowVlo_Close								0				//低电压报警解除
	#define De_FileData_CloseVlo_Open								1				//断电报警
	#define De_FileData_CloseVlo_Close								0				//断电报警解除
	#define De_FileData_LowSpeed_Open								1				//低速报警
	#define De_FileData_LowSpeed_Close								0				//低速报警解除
	#define De_FileData_NullSate									0xffff			// 本系统硬件无法检测的
	#define De_FileData_LCD_Bad										1				//LCD屏坏
	#define De_Suc_LCD												0				//LCD正常
	#define De_Erro_State_GpsNosem									1				//GPS无信息
	#define De_Erro_State_GpsBad									2				//GPS坏
/*=========================================Data Define=========================================================*/
   	/*++++++++++++++++++++++++++++++++++++++系统各个状态++++++++++++++++++++++++++++++++++++++++++++++++++++*/
	#ifdef De_DataTrans_Compiler
		typedef struct
		{	uint16 *State;
			uint16 SateVal1;
			uint16 LocNumber;
		}st_Systerm_State;
		typedef struct
		{	uint16 *State;
			uint16 StateVal;
		}st_Systerm_Init_State;
	#endif

	typedef struct
	{	uint16 CarSpace;					//空车或者是重车
		uint16 Gps;							//GPS的状态
		uint16 Acc;							//Acc的状态
		uint16 Work;						//车子运营状态
		uint16 Operation;					//发动机运行状态
		uint16 Help;						//求助报警
		uint16 HighSpeed;					//超速度报警
		uint16 Watch;						//视屏擦除
		uint16 LowVlo;						//低电压报警
		uint16 CloseVlo;					//断电报警
		uint16 LowSpeed;					//低速报警
		uint16 LCD;							//调度屏状态;
		uint16 LocationTrue;				//定位状态
		uint16 LatHem;						//南北
		uint16 LongHem;						//东西
		uint16 Contr;						//控制	 
	}st_FilData_Sys_State;					//系统状态
	
	
	
	
	
/*=======================================Function =============================================================*/
	void GetGps(uint8 *Buf);
	void InitSytermState(void);
	uint16 SendData2Gprs(uint8 fd,uint8 Answer,uint16 OrderNumber,uint16 OrderID,uint8 *Buf,uint16 SizeofBuf);
	void  *OSMboxPend32 (OS_EVENT *pevent, uint32 timeout, uint8 *err);
	void *SendDataUDP(uint8 fd,void *Buf,uint16 SizeofBuf,uint16 *Err);
	#ifdef De_DataTrans_Compiler
		static void State2CenState(uint8 *Buf);
		static void Gps2CenGps(st_Data_Gps	*ptst_Data_Gps,uint8 *OutBuf);
		static void Gps2CenGps_Latitude(st_Data_Gps	*ptst_Data_Gps,uint8 *OutBuf);
		static void Gps2CenGps_LongHem(st_Data_Gps	*ptst_Data_Gps,uint8 *OutBuf);
		static void Gps2CenGps_Speed(st_Data_Gps	*ptst_Data_Gps,uint8 *OutBuf);
		static void Gps2CenGps_Angle(st_Data_Gps	*ptst_Data_Gps,uint8 *OutBuf);
		static void Gps2CenGps_Height(st_Data_Gps	*ptst_Data_Gps,uint8 *OutBuf);
		static void Gps2CenGps_Timer(st_Data_Gps	*ptst_Data_Gps,uint8 *OutBuf); 
	#endif
/*==========================================全局变量定义=========================================================*/
	#ifdef De_DataTrans_Compiler	
		st_FilData_Sys_State	CN_st_FilData_Sys_State;
		/*********************************系统报警状态对应表***********************************************/
		const st_Systerm_State	CN_Ba_st_Systerm_State[]=
		{	{&CN_st_FilData_Sys_State.Gps,De_Erro_State_GpsNosem,De_FileData_GpsLoc_Number},		//GPS是否定位
			{&CN_st_FilData_Sys_State.LatHem,De_Gps_LatHem_N,De_FileData_LatHem_Number},			//南北定位
			{&CN_st_FilData_Sys_State.LatHem,De_Gps_LongHem_E,De_FileData_LongHem_Number},			//东西定位
			{&CN_st_FilData_Sys_State.Contr,De_FileData_Contrl_Open,De_FileData_Contr_Number},		//GPS控制
			{&CN_st_FilData_Sys_State.Acc,De_FileData_Acc_Open,De_FileData_Acc_Number},				//ACC状态
			{&CN_st_FilData_Sys_State.CarSpace,De_FileData_CarSpace_State_Full,De_FileData_CarSpace_Number},	//车辆状态位
			{&CN_st_FilData_Sys_State.Work,De_FileData_Work_Close,De_FileData_Work_Number},	//车辆状态位
			{&CN_st_FilData_Sys_State.Operation,De_FileData_Operation_Close,De_FileData_Operation_Number},//发动机状态
			{&CN_st_FilData_Sys_State.Help,De_FileData_Operation_Close,De_FileData_Help_Number},   //求助报警
			{&CN_st_FilData_Sys_State.HighSpeed,De_FileData_HighSpeed_Open,De_FileData_HighSpeed_Number}, //超速度报警
			{&CN_st_FilData_Sys_State.Watch,De_FileData_Watch_Close,De_FileData_Watch_Number},			//视屏线拆除
			{&CN_st_FilData_Sys_State.LowVlo,De_FileData_LowVlo_Open,De_FileData_LowVlo_Number},		//低电压
			{&CN_st_FilData_Sys_State.CloseVlo,De_FileData_CloseVlo_Open,De_FileData_CloseVlo_Number},	//断电
			{&CN_st_FilData_Sys_State.LowSpeed,De_FileData_LowSpeed_Open,De_FileData_LowSpeed_Number},	//低速度
			{&CN_st_FilData_Sys_State.Gps,De_Erro_State_GpsBad,De_FileData_GpsBad_Number},//GPS模块故障
			{&CN_st_FilData_Sys_State.Gps,De_FileData_NullSate,De_FileData_GpsOpencircuit_Number},//Gps天线开路
			{&CN_st_FilData_Sys_State.Gps,De_FileData_NullSate,De_FileData_GpsShortCircuit_Number},//GPS天心短路
			{&CN_st_FilData_Sys_State.LCD,De_FileData_LCD_Bad,De_FileData_LCD_Number},//GPS模块故障
		};
		/**********************************系统初始状态对应表**************************************************/
		const st_Systerm_Init_State	CN_Ba_st_Systerm_Init_State[]=
		{	{&CN_st_FilData_Sys_State.CarSpace,De_FileData_CarSpace_State},
			{&CN_st_FilData_Sys_State.Gps,De_Control_Suc_Gps},
			{&CN_st_FilData_Sys_State.Acc,De_FileData_Acc_Close},
			{&CN_st_FilData_Sys_State.Work,De_FileData_Work_Close},
			{&CN_st_FilData_Sys_State.Operation,De_FileData_Operation_Close},
			{&CN_st_FilData_Sys_State.Help,De_FileData_Help_Close},
			{&CN_st_FilData_Sys_State.HighSpeed,De_FileData_HighSpeed_Close},
			{&CN_st_FilData_Sys_State.Watch,De_FileData_Watch_Open},
			{&CN_st_FilData_Sys_State.LowVlo,De_FileData_LowVlo_Close},
			{&CN_st_FilData_Sys_State.CloseVlo,De_FileData_CloseVlo_Close},
			{&CN_st_FilData_Sys_State.LowSpeed,De_FileData_LowSpeed_Close},
			{&CN_st_FilData_Sys_State.LCD,De_Suc_LCD},
			{&CN_st_FilData_Sys_State.LocationTrue,De_Control_Suc_Gps},
			{&CN_st_FilData_Sys_State.LatHem,De_Gps_LatHem_N},
			{&CN_st_FilData_Sys_State.LongHem,De_Gps_LongHem_E},
			{&CN_st_FilData_Sys_State.LongHem,De_FileData_Contrl_Close}
		};
	#else
		extern st_FilData_Sys_State	CN_st_FilData_Sys_State;				
	#endif


