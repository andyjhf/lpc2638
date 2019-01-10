#define Sleep_H
#ifdef	Sleep_H
/*===============================Include File==========================================================*/
	#include "..\..\APP\config.h"
	#include "stdlib.h"
	#ifdef De_Sleep_Compiler
		#include "..\..\miscellaneous\CodeTrans\AscNumber.h"
		#include "..\..\Control\Gps\GpsTask.h"
	#endif
/*===================================Define Data=======================================================*/
	
	/*++++++++++++++++++++++++++++++++错误代码一览表++++++++++++++++++++++++++++ +++++*/
	#define De_Suc_Sleep						0
	#define De_Erro_Sleep_Start					1
	#define	De_Erro_Sleep_Nofd					De_Erro_Sleep_Start		//没有事件空间
	#define De_Erro_Sleep_Init					De_Erro_Sleep_Nofd+1

	/*++++++++++++++++++++++++++++++++++++系统标志++++++++++++++++++++++++++++++++++++*/
	#define De_Sleep_Affair_State_Open		1
	#define De_Sleep_Affair_State_Close		0
	#define De_State_Sleep					1							//休眠
	/*+++++++++++++++++++++++++++++++++++任务有关参数+++++++++++++++++++++++++++++++++*/
	#define De_Stk_Sleep							128							//堆大小
	#define De_Sleep_TaskDly						300								//延时调度时间
	#define	De_Sleep_MaxAffair						1								//最多10个事件
	#define De_Task_Sleep							3
/*=====================================Data Define=======================================================*/
	/*+++++++++++++++++++++++++++++++++数据结构体+++++++++++++++++++++++++++++++++++++*/ 
	typedef struct
	{	void (*ptFunSleep)(uint8 fd);
		void (*ptFunupSleep)(uint8 fd);
	}st_Affair_Sleep; 		  					//事件控件
	typedef struct
	{	uint8 Sleep;
		st_Affair_Sleep	CN_st_Affair_Sleep[De_Sleep_MaxAffair];
		uint8 State[De_Sleep_MaxAffair];	  //事件有无打开标志
	}st_Control_Sleep; 							//运行参数
	/*++++++++++++++++++++++++++++++++++++Out Function+++++++++++++++++++++++++++++++++++*/
	typedef struct
	{   uint16 (*   Init)(void);
	    uint16 (*   Open)(st_Affair_Sleep	*ptst_Affair_Sleep,uint8 *fd);
	    uint16 (*   Close)(uint8 fd);
	    uint16 (*	Read)(uint8 *Sleep);
	    
	}st_Fun_Sleep;

/*===================================================Static Function=======================================*/
	#ifdef De_Sleep_Compiler	
		static uint16 Init(void);
		static uint16 Open(st_Affair_Sleep	*ptst_Affair_Sleep,uint8 *fd);   		//创建休眠事件
		static uint16 SeekSpace(st_Control_Sleep	*ptst_Control_Sleep);
		static uint16 Close(uint8 fd);												//关闭休眠事件
		static uint16 Read(uint8 *Sleep);
		static void Task(void *pdata);
		static void JugeAffair(st_Control_Sleep	*ptst_Control_Sleep);


/*==================================================Public Ram============================================*/	
		OS_EVENT	*SleepBox; 
		static OS_EVENT	*SleepSem;
		st_Control_Sleep	 CN_st_Control_Sleep;
		static OS_STK Sleep_Stk[De_Stk_Sleep];
		const st_Fun_Sleep	CN_st_Fun_Sleep={Init,Open,Close,Read};
	#else
		extern const st_Fun_Sleep	CN_st_Fun_Sleep;
		extern 	OS_EVENT	*SleepBox; 	
	#endif


#endif



