/*============================================================================*/
#define CanTask_H
#ifdef	CanTask_H
/*=============================include File===================================*/
	#include "..\..\APP\config.h"
	#include "stdlib.h"
	#include "..\..\HardWare\Can\Can.H"
	#ifdef De_CanTask_Compiler
		
		#include "..\..\miscellaneous\CodeTrans\AscNumber.h"		//引用码制转换资源
		#include "..\..\miscellaneous\Date\Date.h"					//引用日期资源
		#include "..\..\miscellaneous\Arithmetic\Arithmetic.h" 		//引入算法
	#endif
	/*==============================Define Data===================================*/	
	/*++++++++++++++++++++++++错误代码一栏表++++++++++++++++++++++++++++++*/
	#define De_Control_Suc_Can						0
	#define De_Erro_Control_Can						1
	#define De_Erro_Control_Can_Init				De_Erro_Control_Can+1
	#define De_Erro_Affair_Can_Nofd					De_Erro_Control_Can_Init+1
	#define De_Erro_Control_Can_Send				De_Erro_Affair_Can_Nofd+1
	#define De_Erro_Control_Can_Nodata				De_Erro_Control_Can_Send+1
	/*+++++++++++++++++++++++++++++++程序状态字+++++++++++++++++++++++++++++++++++++++++++*/			
	#define BITRATE100K28_8MHZ        				0x00090006//0x00090017	   //CAN使用波特率
	#define BITRATE100K24MHZ          				0x001C000E
	#define BITRATE125K24MHZ          				0x001C000B
	#define BITRATE250K24MHZ          				0x001C0005
	#define BITRATE500K24MHZ          				0x001C0002
	#define BITRATE1000K24MHZ         				0x00090001
	#define Can_Use_BitRate							BITRATE250K24MHZ
	#define De_Can_Use_Port							De_Can_Port_1
	#define De_Can_MaxAffair						10				//最大Can事件数
	#define De_Can_Affair_State_Close				0
	#define De_Can_Affair_State_Open				1
	
	#define De_Can_Affair_Enable					0
	#define De_Can_Affair_DisEnable					1	
	/*++++++++++++++++++++++++++++++++操作系统有关++++++++++++++++++++++++++++++*/
	#ifdef De_CanTask_Compiler
		#define De_Can_Task								9
		#define De_Can_Stk								512
		#define De_Can_TaskDly							80								//延时调度时间
	#endif
/*=======================================Data Define============================*/
	/*++++++++++++++++++++++++++++++++数据结构定义++++++++++++++++++++++++++++++*/
	typedef struct
	{	void (*ptFun)(st_Da_CanInfor	*ptst_Da_CanInfor);				//接受中断
			
	}st_Function_Can;

	typedef struct
	{	st_Da_CanInfor 	CN_st_Data_CanInfor;
		st_Function_Can CN_st_Function_Can[De_Can_MaxAffair];
		uint8 State[De_Can_MaxAffair];
		uint8 Enable[De_Can_MaxAffair];
		uint32 Bps;
		uint8 CanInfor_State;				//数据状态   是否已读
	}st_Control_Can;

	typedef struct
	{	uint16 (* Init)(void);
		uint16 (* Open)(st_Function_Can *ptst_Function_Can,uint8 *fd);
		uint16 (* Close)(uint8 fd);
		uint16 (* Read)(st_Da_CanInfor *ptst_Da_CanInfor);
		uint16 (* Write)(st_Da_CanInfor *ptst_Da_CanInfor);
		uint16 (* Enable)(uint8 fd);
		uint16 (* DisEnable)(uint8 fd);
		uint16 (* GetEnable)(uint8 fd,uint8 *State);
		uint16 (* GetPro)(uint32 *Bps);
		uint16 (* EditPro)(uint32 *Bps);
	}st_Fun_CanControl;
	/*=====================================static Function========================================*/
	#ifdef De_CanTask_Compiler
		static uint16 Init(void);
		static uint16 Open(st_Function_Can *ptst_Function_Can,uint8 *fd);
		static uint16 Close(uint8 fd);
		static uint16 Read(st_Da_CanInfor *ptst_Da_CanInfor);
		static uint16 Write(st_Da_CanInfor *ptst_Da_CanInfor);
		static uint16 Enable(uint8 fd);
		static uint16 DisEnable(uint8 fd);
		static uint16 GetEnable(uint8 fd,uint8 *State);
		static uint16 GetPro(uint32 *Bps);
		static uint16 EditPro(uint32 *Bps);


		static void CanTask(void *pdata);
		static uint16 SeekSpace(st_Control_Can    *pst_Control_Can);
		static void JugeAffair(void);
	#endif
	/*====================================Public Ram==============================================*/
	#ifdef De_CanTask_Compiler
		OS_EVENT 			*CanCtrSem;
		OS_STK				CanTaskStk [De_Can_Stk];
		st_Control_Can		CN_st_Control_Can;
	
		const st_Fun_CanControl CN_st_Fun_CanControl = {Init,Open,Close,Read,Write,Enable,DisEnable,GetEnable,GetPro,EditPro};
	#else
		extern const st_Fun_CanControl CN_st_Fun_CanControl;
	#endif
#endif
