#define AppEvent_H
#ifdef AppEvent_H
/*=========================================include File===========================================================*/	
	#include "..\..\APP\config.h"
	#include "stdlib.h"
	#ifdef De_AppEvent_Compiler
		
		#include "..\..\miscellaneous\Date\date.h"
		#include "..\..\Control\Timer\Timer.h"
		#include "..\..\miscellaneous\CodeTrans\AscNumber.h"		//��������ת����Դ
		#include "..\..\Control\Acc\Acc.h"
		#include "..\..\Control\Adc\adc.h"
		#include "..\..\Control\Can\CanTask.h"
		#include "..\..\Control\Gprs\GPRS.h"
		#include "..\..\Control\Gps\GpsTask.h"
		#include "..\..\Control\Sleep\Sleep.h"
		#include "..\..\AppFunction\FilleData\FileData.h"
		#include "..\..\AppFunction\DataTrans\DataTrans.h"
		#include "..\..\File\rwFile.h"
		// 
	#endif
/*========================================Define Data=============================================================*/
	/*+++++++++++++++++++++++++++++++++++++�������һ����++++++++++++++++++++++++++++++++++++++++++++++++++*/ 
	

	/*+++++++++++++++++++++++++++++++++++++����״̬��+++++++++++++++++++++++++++++++++++++++++++++++++++++*/
	#define De_Erro_State_GpsNosem						1
	#define De_Erro_State_GpsBad						2
	#define De_Erro_State_Speed							3	
	#define De_State_Voltage_Bad						4

	#define De_Event_No									0xff

/*=========================================Data Define=+==========================================================*/
	/*+++++++++++++++++++++++++++++++++++++++���ݽṹ��+++++++++++++++++++++++++++++++++++++++++++++++++++*/

/*==========================================static Function==================+++================================*/
  	void GpsInit(void);
 	void AdcInit(void);
	void SleepInit(void);
	void AccInit(void);
	void CanInit(void);
	void GprsInit(void);
	#ifdef De_AppEvent_Compiler
		static void Can(st_Da_CanInfor	*ptst_Da_CanInfor);

		static void GpsSem(st_Data_Gps  *ptst_Data_Gps,uint8 fd);				//
		static void GpsNoSem(st_Data_Gps  *ptst_Data_Gps,uint8 fd);				//Gpsû���ź�
		static void GpsErro(uint8 fd);
		
		static void HighAdc(st_Data_CheckVoltage	*ptst_Data_CheckVoltage,uint8 fd);		//�ߵ�ѹ�ָ�����
		static void LowAdc(st_Data_CheckVoltage	*ptst_Data_CheckVoltage,uint8 fd);
		static void InitAdcLowTimer(void);
		static void InitAdcHighTimer(void);
		static void LowVolWaring(st_Data_Timer	*ptst_Data_Timer,uint8 fd);		//�͵�ѹ����
		static void HighVolBack(st_Data_Timer	*ptst_Data_Timer,uint8 fd);		//��ѹ�ָ�����
		
		static void InitTimerWork(uint8 fd);
		static void InitTimerSleep(uint8 fd);
	
		static void AccHigh(st_Data_Acc   *ptst_Data_Acc,uint8 fd);
		static void AccLow(st_Data_Acc   *ptst_Data_Acc,uint8 fd);		//Acc��Ч
		static void InitTimerAcc(void);					//acc�رպ������¼�
		static void Sleep(st_Data_Timer	*ptst_Data_Timer,uint8 fd);
		static void SendData(st_Data_Timer	*ptst_Data_Timer,uint8 fd);				//��ʱ����
		static void CheckData(st_Data_Timer	*ptst_Data_Timer,uint8 fd);			//Ѳ��
    	
		static void MessageSem(st_Data_Gprs   *ptst_Data_Gprs);
	
	#endif
	

#endif	 


