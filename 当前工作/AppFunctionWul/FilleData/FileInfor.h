#include "stdlib.h"	
#include "..\..\Dev\Sensor\_PuSensor.h"
/*=======================================�ļ�������Ϣ��===========================================================*/
	typedef struct
	{	uint8 SoftEdition[8];					//����汾
		uint8 HardEdition[8];					//Ӳ���汾
		uint8 MachID[16];						//�������
		uint8 IMEI[7];							//�����
		uint8 MachType[2];						//��������
		uint8 MakeFactory[2];					//���Ҵ���
	}st_File_Basic;								//�ļ�������Ϣ��
/*=====================================��ʻԱ������Ϣ��===========================================================*/	
	typedef struct
	{	uint8 ID;								//��ʻԱID
		uint8 Phone[15];						//��ʻԱ�ֻ�����
		uint8 Name[10];							//��ʻԱ����
		uint8 PassWord[10];						//��ʻԱ��¼����
		uint8 UseID[10];						//��ʻԱ����
	}st_Emplo_Basic;
/*==========================================����������===========================================================*/
	typedef struct
	{	uint8 GreenWord[128]; 					//��������
		int16 Integral;   						//��ǰ�������
		uint32 PassWord;						//����
	}st_File_GreenPar;
/*=========================================����������===========================================================*/
	typedef struct
	{	uint32	Adree;							//��ַ
		uint8 YesOnON;							//�Ƿ����ô�
	}st_File_WorkPar;
/*=========================================�����������ñ�=======================================================*/		
   /*---------------------------------------׷�������--------------------------------------------------*/
   	typedef struct
	{	uint8 ComMod;							//ͨѶ��ʽ
		uint16 AccOpenTimer;					//Acc�����ʱ�䴫�ͼ��
		uint16 AccCloseTimer;					//Acc�رպ��ʱ�䴫�ͼ��
		uint16 Space;							//�ƶ�����ı仯���
	}st_Track_Par; 								//׷�ٲ���
   /*---------------------------------------���������-------------------------------------------------*/
	typedef struct 
	{	uint32 WartingVl;					//����ֵ	
		uint32 WartingTimer;				//������ֵ��ʱ��
	}st_Waring_Par;		
   	typedef struct
	{	st_Waring_Par	HighSpeed;				//���ٶ�	 
		st_Waring_Par	LowSpeed;				//���ٶ�
		st_Waring_Par	Voltage;				//�͵�ѹ����
	}st_Sum_Waring;								//��������һ����
   /*-------------------------------------------���߱�-------------------------------------------------*/
   	typedef struct
	{	uint16 GpsTimer;						//Gps�رյ�ʱ��
		uint16 GprsTimer;						//Gprs�رյ�ʱ��	
	}st_Sleep_Par;								//���߲���
   /*-----------------------------------------����-----------------------------------------------------*/
	typedef struct
	{	uint8 DataLog[8];						//������־��ѯ
		uint8 ScotomaLog[8];					//ä��������־
	}st_Data_Access;							//���ݲ�ѯ����
   /*-------------------------------------������������-------------------------------------------------*/
   	typedef struct
	{	uint8 PerPuse;							//���ٴ�����ÿ��������
		uint16 Feature;							//��������ϵ��
		uint8 OilFrequency;						//��λ����������Ƶ��
	}st_File_Car_Par;  //���ڳ����Ĳ���
	typedef struct
	{	st_Track_Par	CN_st_Track_Par;		//׷�ٲ�����
		st_Sum_Waring	CN_st_Sum_Waring;		//����������
		st_Sleep_Par	CN_st_Sleep_Par;		//���߲�����			
		st_Data_Access	CN_st_Data_Access;		//���ݲ�ѯ����
		st_File_Car_Par	CN_st_File_Car_Par;		//�����Ĳ���	
		uint8 ComMod;							//ͨѶ��ʽ
		uint16 IPTransMessage;					//IP�л�MESSAGEʱ��
		uint8 DisLCD;							//�Ƿ�װ������
		uint8 DisLogin;							//�Ƿ��е�¼��ʾ
		uint8 DisVid;							//�Ƿ�װ����ͷ
		uint8 VidType;							//��������
		uint32 FrmTimer;						//ԤԼ����ʱ��	
	}st_Parameter_Table;			   			//������
/*======================================IPͨѶ������===========================================================*/
		typedef struct
		{	uint8 APN[32];						//��'/0'��Ϊ����	
	   		uint8 Use[32];						//�����û���
			uint8 PassWord[32];					//��������
		}st_Gprs_IPNet;
		typedef struct
		{	uint32 IP;			  				//IP��ַ
			uint8 DomainName[128];				//������ַ
		}st_Gprs_IP;
	
		typedef struct
		{	uint8 CentrHeart;					//�����������
	   		uint8 DeviceHeart;					//�豸�������
		  	uint8 Repeat;						//Ip�ؼ�ָ���ط�����
			uint8 RepeatTime;					//Ip�ؼ�ָ���ط����
		}st_Gprs_BasicPar;
   	
	typedef struct
	{	st_Gprs_IPNet	CN_st_Gprs_IPNet;			//APN ����
		st_Gprs_IP		CN_Mast_st_Gprs_IP;			//��IP���ų���
		st_Gprs_IP		CN_Reserve_st_Gprs_IP;		//��IP���ų���
		st_Gprs_BasicPar	CN_st_Gprs_BasicPar;	//GPRS��������
		uint16 			CenPort;					//���Ķ˿ں�	
	}st_Gprs_ComPar;								//IP��ʽ�µ�ͨѶ����
/*========================================Message��ʽ�µ�ͨѶ����==============================================*/
		typedef struct
		{	uint8 Repeat;							//�ط�����	
			uint8 RepeatTime;						//�ط����
		}st_Message_BasicPar;						//���Ų���	
		
		typedef struct
		{	uint8 CenMessageSev[15];				//�������ĺ���	
			uint8 CentrMessPhone1[128];				//���ŷ������ĺ���1
			uint8 CentrPhone2[128];					
		}st_Message_Phone;							//����Ϣ����������
	typedef struct
	{	st_Message_BasicPar	CN_st_Message_BasicPar;			//���ŵĻ���������
		st_Message_Phone	CN_st_Message_Phone;			//���ź���
	}st_Message_ComPar;										//�����µ�ͨѶ����
/*=============================================�绰�������===================================================*/
	typedef struct
	{	uint8 WatchPhone[15];									//��ص绰����
		uint8 RestPhone[15];									//��λ�绰����
	}st_Phone_Basic;
/*=============================================�̶��绰����===================================================*/
	typedef struct
	{	uint8 Type;											    //�绰����
		uint8 PhoneName[10];									//�õ绰��Ա����
		uint8 Phone[15];										//�绰����
	}st_Phone_Root;												//�̶��绰����

/*==============================================ACC===========================================================*/
	typedef struct
	{	uint32 AccTimer;										//Acc
	}st_AccTimer;	 											//Acc

/*==============================================Gps�����=====================================================*/
	typedef struct
	{	st_Data_Gps	CN_st_Data_Gps;								//
		uint32 Milage;
	}st_File_Gps;
/*==============================================�˵���Ϣ======================================================*/
	typedef struct
	{	uint8 BackID;
		uint8 Cut[40];
	}st_File_Menum;

/*==============================================�̶��绰======================================================*/
	typedef struct
	{	uint8 Name[8];				//����
		uint8 Phone[15];			//�绰
		uint8 Pro;					//����		
	}st_File_Phone;
/**************************************������ˮ*******************************************************/	
	typedef struct
	{	uint8 OnOffValue[16];									//�������ĸ���ֵ
		uint8 WireLess[6];										//���߿�������ֵ
		uint32 AccTimer;										//Acc�ۼ�ͳ��ʱ��
		uint32 Mileage;											//�ۼ����
		uint16 OilV1;											//������λ1
		uint16 OilV2;											//������λ2
		uint8 OilV1Scale;										//��λ1�ٷֱ�
		uint8 GsmCsq;											//GSM�ź�ǿ��	
		uint32 SupplyOilTimer;									//����ʱ��
		uint32 Temper;											//�¶�ֵ
		uint32 PulseNumber;										//�������
		uint16 Humidity_Par;									//ʪ��ֵ
		uint32 WireLessTemp[4];									//���ߴ������¶�ֵ
	}st_Work_ParFlow;
	
	typedef struct
	{	st_Data_Gps	CN_st_Data_Gps;				//GPS״̬λ
		uint8	AceWhy;							//�洢ԭ��
		uint32 DevState[4];						//�豸״̬
		st_Work_ParFlow	CN_st_Work_ParFlow;		//���������в���
	}st_WorkFlow_Table;							//������ˮ��
