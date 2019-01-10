#include "stdlib.h"	
#include "..\AgreeOn\AgreementCom.h"
#include "..\Control\Photo\Photo.h"
/*=======================================�ļ�������Ϣ��=========================================================*/
	typedef struct
	{	uint8 SoftEdition[8];					//����汾
		uint8 HardEdition[8];					//Ӳ���汾
		uint8 MachID[8];						//�������
		uint8 IMEI[7];							//�����
		uint8 MachType[2];						//��������
		uint8 MakeFactory[2];					//���Ҵ���
	}st_File_Basic;								//�ļ�������Ϣ��

/*=====================================��ʻԱ������Ϣ��=========================================================*/	
	typedef struct
	{	uint8 ID;								//��ʻԱID
		uint8 Phone[15];						//��ʻԱ�ֻ�����
		uint8 Name[10];							//��ʻԱ����
		uint8 PassWord[10];						//��ʻԱ��¼����
		uint8 UseID[10];						//��ʻԱ����
	}st_Emplo_Basic;
/*==========================================����������==========================================================*/
	typedef struct
	{	uint8 GreenWord[128]; 					//��������
		int16 Integral;   						//��ǰ�������
		uint32 PassWord;						//����
	}st_File_GreenPar;
/*=========================================����������===========================================================*/
	typedef struct
	{	uint32	Adree;							//��ַ
		uint8 YesOnON;							//�Ƿ����ô�
	}st_File_WorkParVal;
	typedef struct
	{	st_File_WorkParVal	CN_st_File_WorkParVal[De_CN_Ba_WordPar_Number];
	}st_File_WorkPar;

	
/*=========================================�����������ñ�=======================================================*/		
   /*---------------------------------------׷�������--------------------------------------------------*/
   	//<��׷�ٲ���>
   /*---------------------------------------���������-------------------------------------------------*/
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
	/*---------------------------------------�绰����-------------------------------------------------*/
	typedef struct
	{	uint8 Type;
		uint8 Phone[15];

	}st_Phone_State;
   /*-------------------------------------������������-------------------------------------------------*/
   	typedef struct
	{	uint8 PerPuse;							//���ٴ�����ÿ��������
		uint16 Feature;							//��������ϵ��
		uint8 OilFrequency;						//��λ����������Ƶ��
	}st_File_Car_Par;  //���ڳ����Ĳ���
	#define De_st_Parameter_Table_HelpWaring_Yes							0
	#define De_st_Parameter_Table_HelpWaring_No								1
	#define De_st_Parameter_Table_Contrl_Yes								0
	#define De_st_Parameter_Table_Contrl_No									1
	typedef struct
	{	st_AgreeOn_Agree_Track	CN_st_AgreeOn_Agree_Track;		//׷�ٲ�����
		st_AgreeOn_Agree_Track	CN_Work_st_AgreeOn_Agree_Track;	
		st_Sum_Waring	CN_st_Sum_Waring;		//����������
		st_Sleep_Par	CN_st_Sleep_Par;		//���߲�����			
		st_Data_Access	CN_st_Data_Access;		//���ݲ�ѯ����
		st_File_Car_Par	CN_st_File_Car_Par;		//�����Ĳ���
		st_AgreeOn_ConfineCall	CN_st_AgreeOn_ConfineCall;		//�绰����״̬
		st_AgreeOn_JpgIng	CN_st_AgreeOn_JpgIng;		
		uint8 ComMod;							//ͨѶ��ʽ
		uint16 IPTransMessage;					//IP�л�MESSAGEʱ��
		uint8 DisLCD;							//�Ƿ�װ������
		uint8 DisLogin;							//�Ƿ��е�¼��ʾ
		uint8 DisVid;							//�Ƿ�װ����ͷ
		uint8 HelpWaring;						//�Ƿ��������
		uint8 Contr0;							//Զ�̿���
		st_VidType	CN_st_VidType;				//��������
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
	{	st_Message_BasicPar	CN_st_Message_BasicPar;		//���ŵĻ���������
		st_Message_Phone	CN_st_Message_Phone;			//���ź���
	}st_Message_ComPar;										//�����µ�ͨѶ����
	
/*=============================================�绰�������===================================================*/
	typedef struct
	{	uint8 WatchPhone[15];									//��ص绰����
		uint8 RestPhone[15];									//��λ�绰����
	}st_Phone_Basic;
	
/*=============================================�̶��绰����===================================================*/
											//�̶��绰����
	//<st_AgreeOn_Phone_Par>
/*==============================================ACC===========================================================*/
	typedef struct
	{	uint32 AccTimer;										//Acc
	}st_AccTimer;	 											//Acc
/*==============================================Gps�����=====================================================*/
	/*typedef struct
	{	st_Data_Gps	CN_st_Data_Gps;								//
		uint32 Milage;
	}st_File_Gps; */
/*==============================================�˵���Ϣ======================================================*/
	typedef struct
	{	uint8 BackID;
		uint8 Cut[40];
	}st_File_Menum;
/**********************************************������ˮ*******************************************************/	
	typedef struct
	{	uint8 DateTimer[7];
		uint8 DriverID[10];
		st_AgreeOn_Send_Basic	CN_st_AgreeOn_Send_Basic;
		st_WorkVal_Tabel		CN_st_WorkVal_Tabel;
		uint16 PhotoAdree;
		uint8 LogState;	 								//0:��Ա���ڵ�¼��1���Ѿ���¼������������������Ա�����зǷ���¼
	}st_WorkFlow_Table;							//������ˮ��
/*========================================ѹ���ش�����========================================================*/
	/*typedef struct
	{	st_AgreeOn_Reduce	CN_st_AgreeOn_Reduce;
		uint16 Data[33]; 
		uint16 Number;
	}st_Reduce_Table; */
/*==========================================ä����������======================================================*/
	typedef struct
	{	uint8 DateTimer[7];
		uint16 ID;	 					//
		uint16 AcceSpace;
		uint8 AceWhy;					//�洢ԪӤ
	}st_NoFlow_Table;
/*=============================================���ݷ���======================================================*/
	typedef struct
	{	uint16 SendSpace[5];
	}st_Send_Table;
/*============================================��Ƭ�洢=======================================================*/


/*=============================================��������======================================================*/
	

/*===========================================================================================================*/
	typedef struct
	{	uint8 State[De_CN_Ba_WordPar_Number*2+10];
	}st_Warning_State_Table;
	typedef struct
	{	uint16 	ID;
	 	uint8 	Type;
		uint16	Space;
	}st_Area_Infor_File;
	
	typedef struct
	{	st_Area_Infor_File	CN_st_Area_Infor_File[50];
		uint16 Number;
	}st_Area_Infor_Table; 
/*======================================��ʻԱ��¼��Ϣ======================================================*/
	typedef struct
	{	uint8 Phone[15];
		uint8 State;
	}st_Driver_Log_Table;


