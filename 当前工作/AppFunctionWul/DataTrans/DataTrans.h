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
  	#define	De_AppGprs_Com_Answer_No									0					//����ҪӦ��
	#define De_AppGprs_Com_Answer_Yes									1					//��ҪӦ��
	#define De_IP_Com_AgreeOn											2					//����ͨѶЭ��汾��
	
	/*************************************Gps������Э�����һ����***************************************/
	#ifdef De_DataTrans_Compiler
		
		/*************************************״̬λ������Ӧ��*******************************************/
		#define De_FileData_GpsLoc_Number								0				//Gps��λ��Ч
		#define De_FileData_LatHem_Number								1				//GPS�ϱ�
		#define De_FileData_LongHem_Number								2				//GPS����
		#define De_FileData_Contr_Number								7				//��������
		#define De_FileData_Acc_Number									8				//ACC״̬	
		#define De_FileData_CarSpace_Number								9				//����״̬λ
		#define De_FileData_Work_Number									10				//������Ӫ״̬
		#define De_FileData_Operation_Number							11				//������״̬
		#define De_FileData_Help_Number									16				//��������
		#define De_FileData_HighSpeed_Number							17				//�����ٶ�
		#define De_FileData_Watch_Number								18				//�������
		#define De_FileData_LowVlo_Number								19				//�͵�ѹ����
		#define De_FileData_CloseVlo_Number								20				//�ϵ籨��
		#define De_FileData_LowSpeed_Number								21				//���ٶ�
		#define De_FileData_GpsBad_Number								25				//GPSģ�����
		#define De_FileData_GpsOpencircuit_Number						26				//GPS���߿�·
		#define De_FileData_GpsShortCircuit_Number						27				//Gps���߶�·
		#define De_FileData_LCD_Number									28				//LCD����
	#endif
	
   	/*++++++++++++++++++++++++++++++++++++++ϵͳ����״̬λ��Ӧ��+++++++++++++++++++++++++++++++++++++++++++++++*/
	#define De_FileData_CarSpace_State								0				//�ճ�
	#define De_FileData_CarSpace_State_Full							1				//�س�
	#define De_FileData_Contrl_Open									1				//��������
	#define De_FileData_Contrl_Close								0				//����������
	#define De_FileData_Acc_Open									1				//ACC��
	#define De_FileData_Acc_Close									0				//ACC�ر�
	#define De_FileData_Work_Open									1				//������Ӫ
	#define De_FileData_Work_Close									0				//����ֹͣ��Ӫ
	#define De_FileData_Operation_Open								1				//����������
	#define De_FileData_Operation_Close								0				//������������
	#define De_FileData_Help_Open									1				//��������
	#define De_FileData_Help_Close									0				//�����ⱨ��
	#define De_FileData_HighSpeed_Open								1				//�����ٶ�
	#define De_FileData_HighSpeed_Close								0				//�������ٶ�
	#define De_FileData_Watch_Close									1				//��������
	#define De_FileData_Watch_Open									0				//��������	
	#define De_FileData_LowVlo_Open									1				//�͵�ѹ����
	#define De_FileData_LowVlo_Close								0				//�͵�ѹ�������
	#define De_FileData_CloseVlo_Open								1				//�ϵ籨��
	#define De_FileData_CloseVlo_Close								0				//�ϵ籨�����
	#define De_FileData_LowSpeed_Open								1				//���ٱ���
	#define De_FileData_LowSpeed_Close								0				//���ٱ������
	#define De_FileData_NullSate									0xffff			// ��ϵͳӲ���޷�����
	#define De_FileData_LCD_Bad										1				//LCD����
	#define De_Suc_LCD												0				//LCD����
	#define De_Erro_State_GpsNosem									1				//GPS����Ϣ
	#define De_Erro_State_GpsBad									2				//GPS��
/*=========================================Data Define=========================================================*/
   	/*++++++++++++++++++++++++++++++++++++++ϵͳ����״̬++++++++++++++++++++++++++++++++++++++++++++++++++++*/
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
	{	uint16 CarSpace;					//�ճ��������س�
		uint16 Gps;							//GPS��״̬
		uint16 Acc;							//Acc��״̬
		uint16 Work;						//������Ӫ״̬
		uint16 Operation;					//����������״̬
		uint16 Help;						//��������
		uint16 HighSpeed;					//���ٶȱ���
		uint16 Watch;						//��������
		uint16 LowVlo;						//�͵�ѹ����
		uint16 CloseVlo;					//�ϵ籨��
		uint16 LowSpeed;					//���ٱ���
		uint16 LCD;							//������״̬;
		uint16 LocationTrue;				//��λ״̬
		uint16 LatHem;						//�ϱ�
		uint16 LongHem;						//����
		uint16 Contr;						//����	 
	}st_FilData_Sys_State;					//ϵͳ״̬
	
	
	
	
	
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
/*==========================================ȫ�ֱ�������=========================================================*/
	#ifdef De_DataTrans_Compiler	
		st_FilData_Sys_State	CN_st_FilData_Sys_State;
		/*********************************ϵͳ����״̬��Ӧ��***********************************************/
		const st_Systerm_State	CN_Ba_st_Systerm_State[]=
		{	{&CN_st_FilData_Sys_State.Gps,De_Erro_State_GpsNosem,De_FileData_GpsLoc_Number},		//GPS�Ƿ�λ
			{&CN_st_FilData_Sys_State.LatHem,De_Gps_LatHem_N,De_FileData_LatHem_Number},			//�ϱ���λ
			{&CN_st_FilData_Sys_State.LatHem,De_Gps_LongHem_E,De_FileData_LongHem_Number},			//������λ
			{&CN_st_FilData_Sys_State.Contr,De_FileData_Contrl_Open,De_FileData_Contr_Number},		//GPS����
			{&CN_st_FilData_Sys_State.Acc,De_FileData_Acc_Open,De_FileData_Acc_Number},				//ACC״̬
			{&CN_st_FilData_Sys_State.CarSpace,De_FileData_CarSpace_State_Full,De_FileData_CarSpace_Number},	//����״̬λ
			{&CN_st_FilData_Sys_State.Work,De_FileData_Work_Close,De_FileData_Work_Number},	//����״̬λ
			{&CN_st_FilData_Sys_State.Operation,De_FileData_Operation_Close,De_FileData_Operation_Number},//������״̬
			{&CN_st_FilData_Sys_State.Help,De_FileData_Operation_Close,De_FileData_Help_Number},   //��������
			{&CN_st_FilData_Sys_State.HighSpeed,De_FileData_HighSpeed_Open,De_FileData_HighSpeed_Number}, //���ٶȱ���
			{&CN_st_FilData_Sys_State.Watch,De_FileData_Watch_Close,De_FileData_Watch_Number},			//�����߲��
			{&CN_st_FilData_Sys_State.LowVlo,De_FileData_LowVlo_Open,De_FileData_LowVlo_Number},		//�͵�ѹ
			{&CN_st_FilData_Sys_State.CloseVlo,De_FileData_CloseVlo_Open,De_FileData_CloseVlo_Number},	//�ϵ�
			{&CN_st_FilData_Sys_State.LowSpeed,De_FileData_LowSpeed_Open,De_FileData_LowSpeed_Number},	//���ٶ�
			{&CN_st_FilData_Sys_State.Gps,De_Erro_State_GpsBad,De_FileData_GpsBad_Number},//GPSģ�����
			{&CN_st_FilData_Sys_State.Gps,De_FileData_NullSate,De_FileData_GpsOpencircuit_Number},//Gps���߿�·
			{&CN_st_FilData_Sys_State.Gps,De_FileData_NullSate,De_FileData_GpsShortCircuit_Number},//GPS���Ķ�·
			{&CN_st_FilData_Sys_State.LCD,De_FileData_LCD_Bad,De_FileData_LCD_Number},//GPSģ�����
		};
		/**********************************ϵͳ��ʼ״̬��Ӧ��**************************************************/
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


