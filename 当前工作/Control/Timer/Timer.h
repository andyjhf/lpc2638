#include "..\..\Public_H\DePublic.h"
#ifdef	De_Compiler_Control_Timer
/*======================================include File==========================================================*/
	#include "..\..\APP\config.h"
	#include "stdlib.h"
	
	#ifdef De_Timer_Compiler
		#include "..\..\miscellaneous\CodeTrans\AscNumber.h"						//��������ת����Դ
		#include "..\..\miscellaneous\Date\Date.h"									//����������Դ
		#include "..\..\Dev\Sensor\_PuSensor.h"
		#include "..\..\Dev\Sensor\Sensor.h"
		#include "..\..\HardWare\RTC\RTC.h"
	#endif
/*======================================Define Data==========================================================*/
	/*+++++++++++++++++++++++++++++++++++++++�������һ����++++++++++++++++++++++++++++++++++++++++++++++*/
	#define De_Suc_Timer							0
	#define De_Erro_Timer_Nofd						De_Erro_Timer
	/*++++++++++++++++++++++++++++++++++++++����״̬��־++++++++++++++++++++++++++++++++++++++++++++++++*/
//	#ifdef De_Timer_Compiler
		#define De_Timer_Affair_State_Close						0 					//��ʱ���Ѿ���ʹ��
		#define De_Timer_Affair_State_Open						1					//��ʱ��
		#define De_Timer_Affair_Enable							0					//��ʱ����
		#define De_Timer_Affair_DisEnable						1					//��ʱ����
   /*+++++++++++++++++++++++++++++++++++�����йز���+++++++++++++++++++++++++++++++++++++++++++++++++++*/
		#define De_Stk_Timer							128								//�Ѵ�С
		#define De_Timer_TaskDly						300	
//	#endif								//��ʱ����ʱ��
		#define De_Timer_MaxAffair						3
		#define De_Task_Timer							11
   

/*======================================Data Define=========================================================*/
	typedef struct
	{	uint8 DateTime[7];
	}st_Data_Timer;

	typedef struct
	{	uint32 TimerData;				//ϵͳ
		uint32 TimerNonce;
		uint8 DateTime[7];	 
	}st_Property_Timer;
	
	typedef struct
	{	void (*	ptFun)(st_Data_Timer	*ptst_Data_Timer,uint8 fd);
	}st_Function_Timer;
	
	typedef struct
	{	st_Property_Timer	CN_st_Property_Timer;
		st_Function_Timer	CN_st_Function_Timer;
	}st_Affair_Timer;
	
	typedef struct
	{	st_Data_Timer	CN_st_Data_Timer;		
		st_Affair_Timer	CN_st_Affair_Timer[De_Timer_MaxAffair];
		uint8 State[De_Timer_MaxAffair];	  //�¼����޴򿪱�־
		uint8 Enable[De_Timer_MaxAffair];
	}st_Control_Timer; 			//���в���
/*============================================Out Function=====================================================*/
	typedef struct
	{	uint16 (*	Init)(void);
		uint16 (*	Open)(st_Affair_Timer	*ptst_Affair_Timer,uint8 *fd);
		uint16 (*	Close)(uint8 fd);
		uint16 (*	Read)(st_Data_Timer	*ptst_Data_Timer);
		uint16 (*	Enable)(uint8 fd);
		uint16 (*	DisEnable)(uint8 fd);
		uint16 (*	GetEnable)(uint8 fd,uint8 *State);
		uint16 (*	GetPro)(uint8 fd, uint32 *Va);
		uint16 (*	EditPro)(uint8 fd,uint32 Va);
	}st_Fun_Timer;
/*============================================Static Function==================================================*/
	#ifdef De_Timer_Compiler
		static uint16 Init(void);
		static uint16 Open(st_Affair_Timer	*ptst_Affair_Timer,uint8 *fd);
		static uint16 Close(uint8 fd);
		static uint16 Read(st_Data_Timer	*ptst_Data_Timer);
		static uint16 Enable(uint8 fd);
		static uint16 DisEnable(uint8 fd);
		static uint16 GetEnable(uint8 fd,uint8 *State);
		static uint16 GetPro(uint8 fd, uint32 *Va);
		static uint16 EditPro(uint8 fd,uint32 Va);




		static void Task(void *pdata);
		static void JugeEvent(st_Control_Timer	*ptst_Control_Timer,uint32 add);
		static uint32 GetTimeAdd(uint8 *Small,uint8 *Big);
		static uint8 SeekSpace(st_Control_Timer	*ptst_Control_Timer);


/*=================================================Public Ram==================================================*/
		st_Control_Timer	CN_st_Control_Timer;
		st_Data_Gps	CN_st_Data_GpsControl;
		static OS_EVENT *TimerSem=NULL;
		static OS_STK Timer_Stk[De_Stk_Timer];
		const st_Fun_Timer	CN_st_Fun_Timer={Init,Open,Close,Read,Enable,DisEnable,GetEnable,GetPro,EditPro};
		static uint8 DateTime[7];
		static st_Data_Gps	CN_st_Data_Gps;

   #else
   		extern const st_Fun_Timer	CN_st_Fun_Timer;
   #endif

#endif
		


