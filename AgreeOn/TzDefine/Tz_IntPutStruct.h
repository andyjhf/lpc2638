#include "..\..\Dev\Sensor\_PuSensor.h"
#define De_AgreeOn_LookPar_YesData						0x01
#define De_AgreeOn_LookPar_NoData						0x02
#define De_AgreeOn_LookPar_Erro							0x03
/*==============================================����Э��========================================================*/
/*--------------------------------------------��ȡ������ͨѶ����---------------------------------------------*/
	#define De_AgreeOn_State_Suc							0					//״̬����
	#define De_AgreeOn_State_Erro							1
	typedef struct
	{	st_Data_Gps		CN_st_Data_Gps;
		uint8 State[32];
	}st_AgreeOn_Send_Basic;
/*-----------------------------------------------��¼ָ��-----------------------------------------------------*/
//��¼ָ��,���ȡͨѶ����ָ��һ��
/*-----------------------------------------------����ָ��-----------------------------------------------------*/
//����ָ��,���ȡͨѶ����ָ��һ��
/*-----------------------------------------------�ػ�ָ��-----------------------------------------------------*/
//�ػ�ָ��,���ȡͨѶ����ָ��һ��
/*--------------------------------------------��λ�ն�����Ӧ��------------------------------------------------*/
	typedef struct
	{	uint16 Number;
		uint16 OrderID;	
		uint8 Result;
	}st_AgreeOn_Send_Answer;
/*--------------------------------------------�ϴ�λ����Ϣ----------------------------------------------------*/
	//�ϴ�λ����Ϣ,���ȡͨѶ����ָ��һ��
/*-------------------------------------------�ϴ��˵���Ϣ-----------------------------------------------------*/
	typedef struct
	{	uint8 ID;
		uint8 Cut[40];
	}st_AgreeOn_Send_Menum;
/*--------------------------------�ϴ����˵��ĵ�����Ϣ�ķ�����Ϣ----------------------------------------------*/
	typedef struct
	{	uint16 ID;
		uint8 ResultID;
		uint8 Cut[40];
	}st_AgreeOn_Send_TxtMenum;
	//���ݼ�<�ϴ��˵���Ϣ>
/*-------------------------------------------��ѯ��λ�ն˲���-------------------------------------------------*/
	//���ݼ����ܽṹ��<st_AgreeOn_Agree_Par>
/*-------------------------------------------�ϴ��������״̬-------------------------------------------------*/
	typedef struct
	{
	  	uint8 Result;
	
	}st_AgreeOn_Send_UpdateSoftWare;
/*-------------------------------------------�ϴ�����״̬---------------------------------------------------*/	
	typedef struct
	{	uint8 Work;
		uint8 Battery;
	}st_st_AgreeOn_Send_State;
	#define De_st_AgreeOn_Send_Waring_Type_Yes				0
	#define De_st_AgreeOn_Send_Waring_Type_No				1
	#define De_AgreeOn_Send_Less_State_Suc					0x00  				//����������
	#define De_AgreeOn_Send_Less_State_Erro					0x11				//������ʧ��
	typedef struct
	{	uint8 Type[sizeof(CN_Ba_WordPar)/sizeof(uint16)];
		st_AgreeOn_SetVidType_Par	CN_st_AgreeOn_SetVidType_Par; 	
	}st_WorkVal_Tabel;
	typedef struct
	{ 	uint8 Type;
		st_AgreeOn_Send_Basic	CN_st_AgreeOn_Send_Basic;
		st_WorkVal_Tabel	CN_st_WorkVal_Tabel;
		st_Sensor_State	CN_st_Sensor_State[sizeof(CN_Ba_LessPar)/sizeof(uint16)];
	}st_AgreeOn_Send_Waring;
	
/*=========================================������չЭ��==========================================================*/	
/*-------------------------------------------�ϴ���Ƭ1---------------------------------------------------*/
	typedef struct
	{	uint8 Type;
		uint8 Pro;
		uint8 SecSum;
		uint8 SecNumber;
		st_AgreeOn_Send_Basic	CN_st_AgreeOn_Send_Basic;
		uint16 SizeofBuf;
		uint8 Buf[512-43];
	}st_AgreeOn_Send_UploaderJpg1;
/*-------------------------------------------�ϴ���Ƭ2---------------------------------------------------*/
	typedef struct
	{	uint8 SecSum;
		uint8 SecNumber;
		st_AgreeOn_Send_Basic	CN_st_AgreeOn_Send_Basic;
		st_WorkVal_Tabel	CN_st_WorkVal_Tabel;
		uint16 SizeofBuf;
		uint8 Buf[512-50];
	}st_AgreeOn_Send_UploaderJpg2;
/*----------------------------------------�ϴ���λ�ն˹�������------------------------------------------*/
	typedef struct
	{ 	uint8 Type;
		st_AgreeOn_Send_Basic	CN_st_AgreeOn_Send_Basic;
		st_WorkVal_Tabel	CN_st_WorkVal_Tabel;
	}st_AgreeOn_Send_UploaderPar;

	typedef struct
	{	uint8 Type;
		uint16 ID;
		uint8 InputOrOut;
		st_AgreeOn_Send_Basic	CN_st_AgreeOn_Send_Basic;
	}st_AgreeOn_Send_OutRoadMap;

	

	typedef struct
	{	st_AgreeOn_Send_Basic	CN_st_AgreeOn_Send_Basic;
		uint8 ID[10];
		uint8 State;
	}st_AgreeOn_Send_UpLoaderDriver;

	typedef struct
	{	st_AgreeOn_Send_Basic	CN_st_AgreeOn_Send_Basic;
		uint8 ID[10];
		uint8 Phone[15];
		uint8 Cut[160];
	}st_AgreeOn_Send_UpLoaderHandMess;

	typedef struct
	{	uint16 ID;
	}st_AgreeOn_Send_UpLoaderFrom;

	typedef struct
	{	uint16 ID;
		uint16 CanceID;
	}st_AgreeOn_Send_OverFromErro;
	typedef struct
	{	st_AgreeOn_Send_Basic	CN_st_AgreeOn_Send_Basic;
		uint8 TradeType;
		uint8 CarNumber[6];
		uint8 UpCarDateTime[7];
		uint32 WaintingTime;
		uint32 Space;
		uint32 Price;
		uint32 DownCarPrice;
		uint32 NonSpace;
		uint8 CardType;
		uint8 CardNumber[12];
		uint32 TradeFromPrice;
		uint32 TradePrice;
		uint16 Count;
		uint32 FlowNumber;
		uint32 TAC;
		uint8 DriverID[10];
		uint8 PSAM[6];
		uint8 POSNumber[4];
	}st_AgreeOn_Send_PriceData;
	typedef struct
	{	st_AgreeOn_Reduce	CN_st_AgreeOn_Reduce;
		uint16 Data[33]; 
		uint16 Number;
		uint16 (*ReadParTable)(uint16 Recoder,st_AgreeOn_Send_UploaderPar	*ptst_AgreeOn_Send_UploaderPar);
	}st_Reduce_Table;
	typedef struct
	{	st_AgreeOn_Send_Basic	CN_Ba_st_AgreeOn_Send_Basic;
	}st_Reduce_Basic;
  
 typedef struct
{	uint16 ParID;
	uint16 Number;
	uint8  X_BUF[512];
	uint16 DataLen[33];
	st_AgreeOn_Send_Basic	CN_Ba_st_AgreeOn_Send_Basic;
}st_AgreeOn_Send_LogAndNoSem;
	
			
