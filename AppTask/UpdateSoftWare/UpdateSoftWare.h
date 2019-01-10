/*=====================================Include File=========================================================*/
#include "..\..\APP\config.h"
#include "stdlib.h"

	#ifdef De_UpDateSoftWare_Compiler
		#include "..\..\miscellaneous\CodeTrans\AscNumber.h"				// ��������ת����Դ
//		#include "..\..\AgreeOn\AgreementCom.h"
		#include "..\..\Control\FTP\ftp.h"
	#endif
/*=======================================Define Data============================================================*/
	#define De_Suc_UpDateSoftWare							0
	
	/*+++++++++++++++++++++++++++++++++++�������һ����+++++++++++++++++++++++++++++++++++++*/
	#define De_Erro_UpDateSoftWare							1
	#define De_Erro_UpDateSoftWare_Init						De_Erro_UpDateSoftWare+1
	#define De_Erro_UpDateSoftWare_ReDown					De_Erro_UpDateSoftWare_Init+1	//��ֹ��ǰ���أ����¿�ʼ�µ�����
	/*+++++++++++++++++++++++++++++++++++�����йز���+++++++++++++++++++++++++++++++++*/
	#ifdef De_UpDateSoftWare_Compiler
		#define De_UpDateSoftWare_Stk										256							//�Ѵ�С
		#define De_UpDateSoftWare_TaskDly									30							//��ʱ����ʱ��
//		#define De_Affair_GpsAndMileage_MaxNumber							5 							//���20���¼�
		#define De_Task_Number												11
		#define MAX_MESSAGES												4
	#endif
/*========================================Data Define===========================================================*/
   typedef struct
	{	uint8 Device;			//���������豸��<De_Agree_AgreeOn_UpdateSoftWare_Host>��<De_Agree_AgreeOn_UpdateSoftWare_Display>
		uint32 IP;			   	//TFTP���ط�������IP��ַ
		uint16 Port;			//�˿ں�
		uint8 Use[40];			//�û���
		uint8 Pass[40];			//����
		uint8 FileName[200];	//�ļ�·��
		uint8 SaveFileName[32];	//�����ļ���
		void (*DownLoaderOver)(void);				//���ؽ����������Ӧ��
		void (*DownLoaderState)(st_FTP_WorkState	*ptst_FTP_WorkState);
	}st_Order_UpdateSoftWare;
   typedef struct
	{	st_Order_UpdateSoftWare	CN_st_Order_UpdateSoftWare;												//1: 160X128���� 2: 320X240���� 3: 640X480����
		uint16 Result;          										//����ִ�з��ؽ��
		OS_EVENT	*ReBox;    											//ͨ�������䷵��
	}st_BoxData_UpData;
   typedef struct
   { uint16 (*Init)(void);
   }st_Fun_UpdateSoftWare;
/*============================================Static Function================================================*/
   #ifdef De_UpDateSoftWare_Compiler
   		static uint16 Init(void);
		static void Task(void *pdata);
/*=============================================Public Ram=====================================================*/
		void *UpDataBox[MAX_MESSAGES];  	        					//���ؼ���Ϣ����
		st_BoxData_UpData	*ptst_BoxData_UpData;
		st_BoxData_UpData	*ptst_BoxData_UpData_Temp;
		st_FTP_WorkState CN_st_FTP_WorkState_Now;
		uint16 UpDataWaitTime;
//		st_AgreeOn_UpdateSoftWare	CN_st_AgreeOn_UpdateSoftWare;
		st_FTP_Data CN_st_FTP_Data;
		OS_STK UpDateSoftWare_Stk[De_UpDateSoftWare_Stk];
		st_Fun_UpdateSoftWare CN_st_Fun_UpdateSoftWare={Init};
		OS_EVENT	*UpDateSoftWare_Q;
		void (*DownLoaderOver)(void);				//���ؽ����������Ӧ��
		void (*DownLoaderState)(st_FTP_WorkState	*ptst_FTP_WorkState);
	#else
		extern OS_EVENT	*UpDateSoftWare_Q;
		extern st_Fun_UpdateSoftWare CN_st_Fun_UpdateSoftWare;
	#endif









