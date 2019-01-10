#define Photo_H
#ifdef	Photo_H
/*=============================include File==================================================*/
	#include "..\..\APP\config.h"
	#include "stdlib.h"
	#ifdef De_Photo_Compiler
		#include "..\..\File\rwFile.h"
		#include "..\..\HardWare\UART\UART.h"
		#include "..\..\miscellaneous\CodeTrans\AscNumber.h"		//��������ת����Դ
		#include "..\..\miscellaneous\Date\Date.h"					//����������Դ
		#include "..\..\miscellaneous\Arithmetic\Arithmetic.h" 		//�����㷨
	#endif
/*==============================Define Data==================================================*/	
	/*+++++++++++++++++++++++++++++++�������һ����+++++++++++++++++++++++++++++++++++++++++*/
	#define	De_Suc_Photo									0
	#define De_Erro_Photo									1
	#define De_Erro_Photo_CreateQ							De_Erro_Photo+1			//������Ϣ����ʧ��
	#define	De_Erro_Photo_Common							De_Erro_Photo_CreateQ+1	//����ʧ��
	#define De_Erro_Photo_Data								De_Erro_Photo_Common+1	//��ȡ��Ƭ����ʧ��
	/*+++++++++++++++++++++++++++++++����״̬��+++++++++++++++++++++++++++++++++++++++++++*/			
	#define De_Photo_Use_Uart								3			//����ͷʹ�ô���
	#define MAX_MESSAGES  									10			//ͬʱ�����Խ��յ���������
	#define De_BoxData_Vid_Command_Operation				1			//��������
	#define De_BoxData_Vid_Command_State					2			//��ѯ����ͷ״̬����
	#define De_Max_Bag_Length								508			//ÿ�����ݵ����ߴ�
	#define De_Max_Ram										De_Max_Bag_Length+20 //�������RAM��Դ
	#define De_PhotoType_160x128							'1'			//������Ƭ������160x128
	#define De_PhotoType_320x240							'2'			//������Ƭ������320x240
	#define De_PhotoType_640x480							'3'			//������Ƭ������640x480
	/*++++++++++++++++++++++++++++++++����ϵͳ�й�++++++++++++++++++++++++++++++++++++++++*/
	#ifdef De_Photo_Compiler
		#define De_Photo_Task								12
		#define De_Photo_Stk								256
		#define De_Photo_TaskDly							200								//��ʱ����ʱ��
	#endif
/*=======================================Data Define==========================================*/
	/*++++++++++++++++++++++++++++++++���ݽṹ����+++++++++++++++++++++++++++++++++++++++++++*/
	typedef struct
	{	uint8 Command;        											//��������
		//uint8 *Buf;             										//��������
		uint16 TailFd;													//λ�ñ�
		uint16 DataFd;													//���ݱ�
		uint8 PhotoType;												//1: 160X128���� 2: 320X240���� 3: 640X480����
		uint16 Result;          										//����ִ�з��ؽ��
		OS_EVENT	*ReBox;    											//ͨ�������䷵��
	}st_BoxData_Vid;	        										//���ؼ�����ṹ��
	
	typedef struct
	{	uint16 PhotoSize;												//��Ƭ���ܴ�С
		uint16 BagNum;													//�ְ�����
		uint16 PerBagLength;											//ÿ����С
	}st_Photo_Property;													//������Ƭ������
	typedef struct
	{	uint16 (*Init)(void);
		uint16 (*Open)(void);
		uint16 (*Close)(void);
	}st_Fun_Photo;
	typedef struct
	{	uint16 FrontTail; 												//ǰһ���ļ�βָ��
		uint16 CurrentTail;												//��ǰ�ļ�βָ��
	}st_File_Photo_Tail;
	typedef struct
	{	uint16 BagNumber;
		uint16 DataLength;
		uint8  Data[De_Max_Bag_Length];
	}st_File_Photo_Data;

/*============================================Static Function================================================*/
	#ifdef De_Photo_Compiler
		static uint16 Init(void);
		static uint16 Open(void);
		static uint16 Close(void);
		static void Task(void *pdata);
		static uint16 PhotoCommon(uint8 PhotoSize,st_Photo_Property *ptst_Photo_Property);
		static uint16 ReadPhoto(uint16 Num,uint8 *AgreeBuf,uint16 SizeofAgreeBuf,uint16 *DataLength);	
		static uint16 CheckSum(uint8 *s,uint16 len);
		static uint16 Photo(st_BoxData_Vid *ptst_BoxData_Vid,st_Photo_Property *ptst_Photo_Property,uint8 *AgreeBuf,uint16 SizeofAgreeBuf);
/*=============================================Public Ram=====================================================*/
		void *VidBox[MAX_MESSAGES];  	        					//���ؼ���Ϣ����
		OS_STK	PhotoTaskStk [De_Photo_Stk];						//���ؼ���ջ
		OS_EVENT *Photo_Q;											//��Ϣ�¼�
		st_BoxData_Vid *ptst_BoxData_Vid;							//��������ָ��
		st_Photo_Property CN_st_Photo_Property;						//��Ƭ����
		uint8 PhotoBuf[De_Max_Ram];									//�ռ�ʹ�û���
		const st_Fun_Photo	CN_st_Fun_Photo={Init,Open,Close};
	#else
		extern const st_Fun_Photo	CN_st_Fun_Photo;
		extern OS_EVENT *Photo_Q;
	#endif
#endif

