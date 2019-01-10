/*============================================================================================*/
#define GpsTask_H
#ifdef	GpsTask_H
/*=============================include File==================================================*/
	#include "..\..\APP\config.h"
	#include "stdlib.h"
	#include "..\..\HardWare\Gps\Gps.h"
	#ifdef De_GpsTask_Compiler
		#include "..\..\HardWare\UART\UART.h"
		#include "..\..\miscellaneous\CodeTrans\AscNumber.h"		//��������ת����Դ
		#include "..\..\miscellaneous\Date\Date.h"					//����������Դ
		#include "..\..\miscellaneous\Arithmetic\Arithmetic.h" 		//�����㷨
		#include "..\..\HardWare\RTC\RTC.h"
	#endif
/*==============================Define Data==================================================*/	
	/*+++++++++++++++++++++++++++++++�������һ����+++++++++++++++++++++++++++++++++++++++++*/
	#define De_Control_Suc_Gps						0
	#define De_Erro_Control_Gps						1
	#define De_Erro_Control_Gps_Init				De_Erro_Control_Gps+1
	#define	De_Erro_Affair_Nofd						De_Erro_Control_Gps_Init+1		//û���¼��ռ�
	#define De_Erro_PowerOn_Gps						De_Erro_Affair_Nofd+1
	#define De_Erro_PowerOff_Gps					De_Erro_PowerOn_Gps+1
	/*+++++++++++++++++++++++++++++++����״̬��+++++++++++++++++++++++++++++++++++++++++++*/			
	#define De_Gps_MaxAffair						10
	#define De_Gps_PowerOff_Close              		0
	#define De_Gps_PowerOn_Open             		1
	#define De_Affair_State_Close              		0
	#define De_Affair_State_Open             		1

	/*++++++++++++++++++++++++++++++++����ϵͳ�й�++++++++++++++++++++++++++++++++++++++++*/
	#ifdef De_GpsTask_Compiler
		#define De_Gps_Task								5
		#define De_Gps_Stk								512
		#define De_Gps_Delay							180				//����ȴ�ʱ�� ��Ϊ��λ
		#define De_Gps_TaskDly							35								//��ʱ����ʱ��
	#endif
/*=======================================Data Define==========================================*/
	/*++++++++++++++++++++++++++++++++���ݽṹ����+++++++++++++++++++++++++++++++++++++++++++*/
	typedef struct
	{	void (* ptFunSemFun)(st_Data_Gps  *ptst_Data_Gps,uint8 fd);
		void (* ptNoSemFun)(st_Data_Gps	*ptst_Data_Gps,uint8 fd);
		void (*	ptErroFun)(st_Data_Gps	*ptst_Data_Gps,uint8 fd);	
	}st_Affair_Gps;
	
	typedef struct
	{	st_Data_Gps	CN_st_Data_Gps;	
		uint8 State;						//0����GPS�õģ�1����GPSû������
		uint8 PoweState;					//
	}st_Data_GpsControl;
	
	typedef struct
	{	st_Data_GpsControl	CN_st_Data_GpsControl;
		st_Affair_Gps		CN_st_Affair_Gps[De_Gps_MaxAffair];	
		uint8 State[De_Gps_MaxAffair];
	}st_Control_Gps;
	/*++++++++++++++++++++++++++++++++++Out Function+++++++++++++++++++++++++++++++++++++++*/
	typedef struct
	{   
		uint16 (*   Init)(void);
		uint16 (*   Open)(st_Affair_Gps *pst_Affair_Gps,uint8 *fd);
		uint16 (*   Close)(uint8   fd);
		uint16 (*   Read)(st_Data_Gps   *ptst_Data_Gps);
//		uint16 (*   Write)(st_Data_Gps   *ptst_Data_Gps);
		uint16 (* PowerOpen)(void);
		uint16 (* PowerClose)(void);  
	}st_Control_Fun_Gps;
/*=====================================static Function========================================*/
	#ifdef De_GpsTask_Compiler
		static uint16 Init(void);
		static uint16 Open(st_Affair_Gps *pst_Affair_Gps,uint8 *fd);
		static uint16 Close(uint8   fd);
		static uint16 Read(st_Data_Gps   *ptst_Data_Gps);
//		static uint16 Write(st_Data_Gps   *ptst_Data_Gps);
		static uint16 PowerOpen(void);
		static uint16 PowerClose(void);
	
		static void GpsTask(void *pdata);
		static uint16 SeekSpace(st_Control_Gps    *pst_Control_Gps);	  //���ҿ��е�ʱ���¼�
		static void JugeAffair(uint16 Result);						//�ж��¼�
/*====================================Public Ram==============================================*/
		OS_STK	GpsTaskStk [De_Gps_Stk];
		OS_EVENT 	*GpsCtrSem;
		uint8 RTC_First_Updata = 1; 
		st_Control_Gps CN_st_Control_Gps;
		const st_Control_Fun_Gps CN_st_Control_Fun_Gps = {Init,Open,Close,Read,PowerOpen,PowerClose};		//,Write
	#else
		extern const st_Control_Fun_Gps CN_st_Control_Fun_Gps;
	#endif
#endif		










