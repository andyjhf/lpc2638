/*=====================================Include define===========================================================*/
	#include "..\..\APP\config.h"
	#include "stdlib.h"
	#ifdef De_Sensor_Compiler
		#include "..\..\miscellaneous\CodeTrans\AscNumber.h"

		#include "_PuSensor.h"
		#include "Display\Display.h"
		#include "Less\Less.h"
		#include "ACC\ACC.h"
		#include "Oil\Oil.h"
		#include "Gps\Gps.h"
		#include "Display\Display.h"
		#include "temperture\temperture.h"
		#include "mileage\mileage.h"
		#include "arealrm\arealrm.h"
		#include "UartTzxy\UartTzxy.h"
		#include "GprsTzxy\GprsTzxy.h"
		#include "SmsTzxy\SmsTzxy.h"
		#include "Help\Help.h"
		#include "OnOff\OnOrOff.h"
		#include "ADC\adc1.h"
		
	#endif
/*==========================================Define Data========================================================*/
	/*+++++++++++++++++++++++++++++++++++++�������һ����++++++++++++++++++++++++++++++++++++++++++++++++*/
	#define De_Erro_Senor_Init									1  							
	#define De_Erro_Senor_OverMaxNumber							De_Erro_Senor_Init+1		//�������֧�ֳ���
	#define De_Erro_Senor_NoWorkPar								De_Erro_Senor_OverMaxNumber+1//�޴˹�������
	#define De_Erro_Senor_Initing								De_Erro_Senor_NoWorkPar+1
	#define De_Erro_Senor_NoOpen								De_Erro_Senor_Initing+1
	#define De_Erro_Senor_NoPar									De_Erro_Senor_NoOpen+1
	#define De_Erro_Senor_NoID									De_Erro_Senor_NoPar+1	
	
	#define De_Senor_Max_Number									26							//���֧�ִ���������
	/*+++++++++++++++++++++++++++++++++++Զ�̿���++++++++++++++++++++++++++++++++++++++++++++++++++*/
	#define De_IO_Control								0x01
	#define De_IO_Control_Function					    PINSEL7 &=0xffcfffff
	#define De_IO_Control_Remote_Out					De_IO_Control_Function;FIO3DIR	|=(1<<26)
	#define De_IO_Control_Remote						FIO3SET|=(1<<26)				//�ߵ�ƽ
	#define De_IO_NoControl_Remote						FIO3CLR|=(1<<26)													
	#define De_State_Control							1
	#define De_State_NoControl							0
	#define De_IO_unLock								De_IO_Control_Remote_Out;De_IO_Control_Remote
	#define De_IO_Lock									De_IO_Control_Remote_Out;De_IO_NoControl_Remote

	/*+++++++++++++++++++++++++++++++++++++����״̬++++++++++++++++++++++++++++++++++++++++++++++++++++*/
#ifdef De_Sensor_Compiler	
	#define De_Senor_State_Open									0							//��
	#define De_Senor_State_Close								1							//�ر�
#endif
/*==============================================================================================================*/
	typedef struct
	{	uint16 (*Init)(void);	   											//��ʼ��
		uint16 (*Open)(st_Sensor_DataPar	*ptst_Sensor_DataPar,uint8 *fd);		//��
		uint16 (*Close)(uint8 fd);											//�ر�
		uint16 (*Read)(uint8 fd,void *SendBuf,void *AgreeBuf);				//��
		uint16 (*GetState)(st_Sensor_State	*ptst_Sensor_State,uint8 fd);	//��ȡ״̬
		uint16 (*Get)(st_Sensor_DataPar	**ptst_Sensor_DataPar,uint8 *Number);
		uint16 (*GetID2Par)(uint8 fd,uint16 *Par);
		uint16 (*GetPar2ID)(uint16 Par,uint8 *fd);
		uint16 (*GetSi)(uint8 fd,st_Sensor_DataPar	*ptst_Sensor_DataPar);
	}st_Fun_Sensor;
	
#ifdef De_Sensor_Compiler	
	typedef struct
	{	st_Sensor_DataPar	CN_st_Sensor_DataPar;						//��������
		st_Fun_Sensor2Hard	*ptst_Fun_Les;							//ִ�к���
		uint8 State;											//״̬
		uint8 fd;												//ִ�к���FD
	}st_Sensor_Oper;
#endif

/*==============================================================================================================*/
#ifdef De_Sensor_Compiler
	static uint16 Init(void);	   											//��ʼ��
	static uint16 Open(st_Sensor_DataPar	*ptst_Sensor_DataPar,uint8 *fd);		//��
	static uint16 Close(uint8 fd);											//�ر�
	static uint16 Read(uint8 fd,void *SendBuf,void *AgreeBuf);				//��
	static uint16 GetState(st_Sensor_State	*ptst_Sensor_State,uint8 fd);	//��ȡ״̬
	static uint16 Get(st_Sensor_DataPar	**ptst_Sensor_DataPar,uint8 *Number);	
	static uint16 GetID2Par(uint8 fd,uint16 *Par);
	static uint16 GetPar2ID(uint16 Par,uint8 *fd);
	static uint16 GetSi(uint8 fd,st_Sensor_DataPar	*ptst_Sensor_DataPar);
#endif		
/*==============================================Public Ram======================================================*/
#ifdef De_Sensor_Compiler
	static OS_EVENT	*SensorSem=NULL;	
	const st_Sensor_ParList	*CN_st_Sensor_ParList[]=
	{&CN_Acc_st_Sensor_ParList,&CN_Oil_st_Sensor_ParList,&CN_Less_st_Sensor_ParList,&CN_Gps_st_Sensor_ParList,&CN_Display_st_Sensor_ParList,
	&CN_Temperture_st_Sensor_ParList,&CN_Mileage_st_Sensor_ParList,&CN_Arealrm_st_Sensor_ParList
	,&CN_UartTzxy_st_Sensor_ParList,&CN_GprsTzxy_st_Sensor_ParList,&CN_Help_st_Sensor_ParList,&CN_OnOrOff_st_Sensor_ParList,
	&CN_Adc1_st_Sensor_ParList,&CN_Display_st_Sensor_ParList,&CN_SmsTzxy_st_Sensor_ParList};

	const st_Sensor_Oper	CN_Ba_st_Sensor_Oper=
	{	{0xffffffff,De_WordPar_NoPar,0xffffffff},
		NULL,
		De_Senor_State_Close,
		De_Sensor_Nofd	
	};
	const st_Fun_Sensor	CN_st_Fun_Sensor={Init,Open,Close,Read,GetState,Get,GetID2Par,GetPar2ID,GetSi};
	static st_Sensor_Oper	CN_st_Sensor_Oper[De_Senor_Max_Number];
	
#else
   	extern const st_Fun_Sensor	CN_st_Fun_Sensor;
	extern un_OpenPar  CN_OpenPar;
#endif









