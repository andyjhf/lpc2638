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
	
	/*++++++++++++++++++++++++++++++++�������һ����++++++++++++++++++++++++++++ +++++*/
	#define De_Suc_Sleep						0
	#define De_Erro_Sleep_Start					1
	#define	De_Erro_Sleep_Nofd					De_Erro_Sleep_Start		//û���¼��ռ�
	#define De_Erro_Sleep_Init					De_Erro_Sleep_Nofd+1

	/*++++++++++++++++++++++++++++++++++++ϵͳ��־++++++++++++++++++++++++++++++++++++*/
	#define De_Sleep_Affair_State_Open		1
	#define De_Sleep_Affair_State_Close		0
	#define De_State_Sleep					1							//����
	/*+++++++++++++++++++++++++++++++++++�����йز���+++++++++++++++++++++++++++++++++*/
	#define De_Stk_Sleep							128							//�Ѵ�С
	#define De_Sleep_TaskDly						300								//��ʱ����ʱ��
	#define	De_Sleep_MaxAffair						1								//���10���¼�
	#define De_Task_Sleep							3
/*=====================================Data Define=======================================================*/
	/*+++++++++++++++++++++++++++++++++���ݽṹ��+++++++++++++++++++++++++++++++++++++*/ 
	typedef struct
	{	void (*ptFunSleep)(uint8 fd);
		void (*ptFunupSleep)(uint8 fd);
	}st_Affair_Sleep; 		  					//�¼��ؼ�
	typedef struct
	{	uint8 Sleep;
		st_Affair_Sleep	CN_st_Affair_Sleep[De_Sleep_MaxAffair];
		uint8 State[De_Sleep_MaxAffair];	  //�¼����޴򿪱�־
	}st_Control_Sleep; 							//���в���
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
		static uint16 Open(st_Affair_Sleep	*ptst_Affair_Sleep,uint8 *fd);   		//���������¼�
		static uint16 SeekSpace(st_Control_Sleep	*ptst_Control_Sleep);
		static uint16 Close(uint8 fd);												//�ر������¼�
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



