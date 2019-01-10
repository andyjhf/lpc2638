/*=======================================Include File===========================================================*/
   	#include "..\..\APP\config.h"
	#include "stdlib.h"
	#ifdef De_SensorContr_Compiler
		#include "..\..\miscellaneous\CodeTrans\AscNumber.h"
		#include "..\..\Dev\Sensor\_PuSensor.h"
		#include "..\..\Dev\Sensor\Sensor.h"
		#include "..\..\HardWare\RTC\RTC.h"
		#include "..\Gprs\Gprs.h"
	#endif
/*=======================================Define Data============================================================*/
	#define De_Suc_SensorContr											0
	/*+++++++++++++++++++++++++++++++++++�������һ����+++++++++++++++++++++++++++++++++++++*/
	#define De_Erro_SensorContr_Init  										1
	#define De_Erro_SensorContr_OverMaxNumber								De_Erro_SensorContr_Init+1	
	#define De_Erro_SensorContr_NoPar										De_Erro_SensorContr_OverMaxNumber+1	
	#define De_Affair_Sensor_MaxNumber										20 							//���20���¼�

#ifdef De_SensorContr_Compiler 	
	#define De_Affair_Sensor_Fun_Open									1							//���ܴ�
	#define De_Affair_Sensor_Fun_Close									2							//���ܹر�
	/*+++++++++++++++++++++++++++++++++++�����йز���+++++++++++++++++++++++++++++++++*/
	#define De_Stk_Size													630							//�Ѵ�С
	#define De_SensorContr_TaskDly										100							//��ʱ����ʱ��
	
	#define De_Task_Number												6
#endif		
/*========================================Data Define===========================================================*/
	typedef struct
	{	void (*	ptFunc)(uint16 Par,void *Data,uint8 *DateTimer); 							//��ȡ�������ĺ���
		void (*	GetState)(uint16 Par,st_Sensor_State	*ptst_Sensor_State);				//��������״̬�쳣�ĺ���
	}st_Affair_Sensor;
	typedef struct
	{	uint8 (*Init)(void);
		uint8 (*Open)(uint16 Par,st_Affair_Sensor	*ptst_Affair_Sensor,uint8 *fd);
		uint8 (*Close)(uint8 fd);
	}st_Fun_SensorContr;


#ifdef De_SensorContr_Compiler
	typedef struct
	{	uint16 Par[De_Affair_Sensor_MaxNumber];											//�¼�ID
		uint8 State[De_Affair_Sensor_MaxNumber];										//����������״̬
	}st_Affair_Sensor_OperData;
#endif
/*========================================static Function=======================================================*/
#ifdef De_SensorContr_Compiler	
	static uint8 Init(void);
	static uint8 Open(uint16 Par,st_Affair_Sensor	*ptst_Affair_Sensor,uint8 *fd);
	static uint8 Close(uint8 fd);
	static void Task(void *pData);
#endif		
/*============================================Pubic Ram=========================================================*/	
#ifdef De_SensorContr_Compiler	
	static const st_Affair_Sensor	CN_Ba_st_Affair_Sensor={NULL,NULL};
	static st_Affair_Sensor	CN_st_Affair_Sensor[De_Affair_Sensor_MaxNumber];
	static st_Affair_Sensor_OperData	CN_st_Affair_Sensor_OperData;
	static uint8 X_BUF[sizeof(st_Display_Par)];
	static st_Sensor_State	CN_st_Sensor_State;
	static OS_EVENT	*SensorContrSem=NULL;
	static OS_STK	STK[De_Stk_Size];
	static st_Display_Send	CN_st_Display_Send;
	static st_Data_Gprs_Call CN_st_Data_Gprs_Call;
	static const uint16 CN_Ba_OpenTermPar[]=
	{ 		De_Sensor_WordPar_Switch1,					//������1
			De_Sensor_WordPar_Switch2,				//������2
			De_Sensor_WordPar_Switch3,					//������3
			De_Sensor_WordPar_Switch4,					//������4
			De_Sensor_WordPar_Switch5,					//������5
			De_Sensor_WordPar_Switch6,					//������6
			De_Sensor_WordPar_Switch7,					//������7
			De_Sensor_WordPar_Switch8,					//������8
			De_Sensor_WordPar_Switch9,					//������9
			De_Sensor_WordPar_Switch10,					//������10
			De_Sensor_WordPar_Switch11,					//������11
			De_Sensor_WordPar_Switch12,					//������12
			De_Sensor_WordPar_Switch13,					//������13
			De_Sensor_WordPar_Switch14,					//������14
			De_Sensor_WordPar_Switch15,					//������15
			De_Sensor_WordPar_Switch16,					//������16

			De_Sensor_WordPar_Less_Switch1,				   	//���߿�����1
			De_Sensor_WordPar_Less_Switch2,					//���߿�����2
			De_Sensor_WordPar_Less_Switch3,					//���߿�����3
			De_Sensor_WordPar_Less_Switch4,					//���߿�����4
			De_Sensor_WordPar_Less_Switch5,					//���߿�����5
			De_Sensor_WordPar_Less_Switch6,					//���߿�����6

			De_Sensor_WordPar_AccTimer,				//ACC�ۼ�ʱ��					//���ͳ��
			De_Sensor_WordPar_Oil1,					//������λ1
			De_Sensor_WordPar_SendOilTimer,					//�����ۼ�ʱ��
			De_Sensor_WordPar_Temp,					//�¶�
			De_Sensor_WordPar_Oil2,					//������λ2
			De_Sensor_WordPar_Pulse,					//�������
			De_Sensor_WordPar_Humidity,					//ʪ��
			De_Sensor_WordPar_OilBaifen,					//������λ�ٷֱ�
			De_Sensor_WordPar_Less_Temp1,					//���ߴ������¶�1      
			De_Sensor_WordPar_Less_Temp2,					//���ߴ������¶�2   
			De_Sensor_WordPar_Less_Temp3,					//���ߴ������¶�3   
			De_Sensor_WordPar_Less_Temp4,					//���ߴ������¶�4
			De_Sensor_WordPar_VaCheck,					//��ѹ���				
			//GPS����
	
			De_Sensor_WordPar_Temperture_1, 				//�¶�1·
			De_Sensor_WordPar_Temperture_2,  				//�¶�2·					//Բ������
			De_Sensor_WordPar_Help,
			De_Sensor_WordPar_Display						
	};
	const st_Fun_SensorContr	CN_st_Fun_SensorContr={Init,Open,Close};
#else
	extern const st_Fun_SensorContr	CN_st_Fun_SensorContr;
#endif









