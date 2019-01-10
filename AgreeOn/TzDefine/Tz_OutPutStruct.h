typedef struct
{	uint16 ID;				//����ID
	uint16 ContrID;			//����ID
	uint16 OrderNumber;		//�������
	void *Buf;				//�������ݣ���ϸ������˵��
}st_AgreeOn_Agree;
/*==============================================����Э��========================================================*/
/*----------------------------------------------��λָ��--------------------------------------------------------*/
	#define De_Agree_Answer_Result_Suc					0				//�ɹ�
	#define De_Agree_Answer_Result_Erro					1				//ʧ��
	typedef struct
	{	uint16 Number; 				//Ӧ���������
		uint16 ID;					//��������ID
		uint8 Result;				//Ӧ����
	}st_AgreeOn_Agree_Answer;	   	//
/*------------------------------------------------׷��ָ��------------------------------------------------------*/
	#define De_Agree_Track_ComMod_IP						0			//IP��ʽͨѶ
	#define De_Agree_Track_ComMod_Sms						1			//SMS��ʽͨѶ
	typedef struct
	{	uint8 ComMod;				//ͨѶ��ʽ
		uint16 AccOpenTimer;		//ACC��ʱ����	s
		uint16 AccCloseTimer;		//ACC��ʱ����	s
		uint16 Space;				//λ��		   m
	}st_AgreeOn_Agree_Track;		//
/*------------------------------------------------�趨����------------------------------------------------------*/
	#define De_Agree_Par_Cut_ComMod_IP						0 				//IP��ʽͨѶ
	#define De_Agree_Par_Cut_ComMod_Sms						1		   		//SMS��ʽͨѶ
	#define De_Agree_Par_Cut_ComMod_NoIpSms					2		   		//IP��·������ʱ����SMSͨѶ
	#define De_WordPar_Close								0				//��Ӧ�Ĺ����������ϴ�
	#define De_WordPar_Open									1				//��Ӧ�Ĺ��������ϴ�
	#define De_WordPar_NoAdree								0xffffffff		//���ߴ������޵�ַ
	#define De_Agree_Par_TakeLCD_Yes						1				//��װ������
	#define De_Agree_Par_TakeLCD_No							0				//����װ������
	#define De_Agree_Par_LogMess_Yes						1				//�ظ���ʻԱ��¼
	#define De_Agree_Par_LogMess_No							0				//���ظ���ʻԱ��¼
	#define De_Agree_Par_TaskVid_Yes						1 				//��װ����ͷ
	#define De_Agree_Par_TaskVid_No			 				0				//����װ����ͷ
	#define De_AgreeOn_SetPar_Yes							1	   			//��������������
	#define De_AgreeOn_SetPar_No							0				//���������β�����
	#define De_AgreeOn_Vid_Fun_Close						0
	#define De_AgreeOn_Vid_Fun_Open							1
	/*++++++++++++++++++++++++++++++++++++++�޸Ĺ̶��˵�+++++++++++++++++++++++++++++++++++++++++++++++*/
	typedef struct
	{	uint8 ID;				//���˵�ID
		uint8 BackID;			//��һ��ID	 ��ǰΪ��Ŀ¼ʱ��ֻ��д0
		uint8 Cut[40];			//����
	}st_AgreeOn_Menum_Infor;	
	typedef struct
	{	uint8 Number;			//�����޸Ĳ˵�������
		st_AgreeOn_Menum_Infor	CN_st_AgreeOn_Menum_Infor[10];
	}st_AgreeOn_AmendMenum;	//

	/*++++++++++++++++++++++++++++++++++++++���ù̶��绰++++++++++++++++++++++++++++++++++++++++++++++*/
	#define De_Agree_AgreeOn_Phone_State_0		0				//������룬�������
	#define De_Agree_AgreeOn_Phone_State_1		1				//�������,��ֹ����
	#define De_Agree_AgreeOn_Phone_State_2		2				//�����������ֹ����
	#define De_Agree_AgreeOn_Phone_State_3		3				//��ֹ��������ֹ����
	typedef struct
	{	uint8 State;   		//�绰����״̬
		uint8 Name[10];		//�绰����
		uint8 Phone[15];	//�绰����
	}st_AgreeOn_Phone_Par;
	typedef struct
	{	uint8 Number;	  //�绰����
		st_AgreeOn_Phone_Par	CN_st_AgreeOn_Phone_Par[10];	
	}st_AgreeOn_Phone;		//�绰
	/*++++++++++++++++++++++++++++++++++++++���ü�ʻԱID+++++++++++++++++++++++++++++++++++++++++++++++++*/
	typedef struct
	{	uint8 ID[10];
		uint8 Phone[15];
	}st_AgreeOn_Driver_Par;
	
	typedef struct
	{	uint8 Number;
	   	st_AgreeOn_Driver_Par	CN_st_AgreeOn_Driver_Par[10];
	}st_AgreeOn_Driver;
	/*+++++++++++++++++++++++++++++++++++++����ֵ����+++++++++++++++++++++++++++++++++++++++++++++++++*/
	typedef struct 
	{	uint32 WartingVl;					//����ֵ	
		uint32 WartingTimer;				//������ֵ��ʱ��
	}st_Waring_Par;	
	/*++++++++++++++++++++++++++++++++++++++������+++++++++++++++++++++++++++++++++++++++++++++++++++*/
	typedef struct
	{	uint8 HelpWarning;		//��������
		uint8 Oper;				//��������ת
		uint8 TurnOver;			//�෭
		uint8 AccOpen;			//ACC��
		uint8 AccClose;			//ACC�ر�
	}st_VidType;
	/*--------------------------------------------ͨ������״̬----------------------------------------------------*/
	typedef struct
	{	uint8 State;
		uint8 Phone[15];
	}st_AgreeOn_ConfineCall;
	/*++++++++++++++++++++++++++++++++++++++����������ϸ����++++++++++++++++++++++++++++++++++++++++++++*/
	typedef struct
	{	uint16 GreenPar;				//��λ�ն˵�ǰ����  					
		uint8 GreenWord[128];		   	//��������
		uint8 ListePhone[15];		   	//�����绰
		uint8 ResetPhone[15];			//�绰��λ����
		uint8 CerSevPhone[15];			//����Ϣ�������ĺ���
		uint8 CenPhone[128];			//�������ĺ���
		uint8 APN[32];					//APN
		uint32 MastIP;					//��IP��ַ
		uint8 MastDomainName[128];		//������
		uint32 ReserveIP;				//��IP��ַ
		uint8 ReserveDomainName[128];	//������
		uint16 CenPort;					//���Ķ˿�
		uint8 CentHeart;				//�����·��������
		uint8 UseName[32];				//�����û���
		uint8 UsePass[32];				//��������
		uint8 DevHeart;					//�ն�����
		uint8 ComMod;					//ͨ�ŷ�ʽ��<De_Agree_Par_Cut_ComMod_IP>~<De_Agree_Par_Cut_ComMod_NoIpSms>
		uint8 IPRepeat;					//Ipָ���ط�����
		uint8 IPRepeatTime;				//IPָ���ط����
		uint8 MessageRepeat;			//�����ط�����
		uint8 MessageRepeatTimer;		//����ָ���ط����
		uint16 IPTransSms;				//IP��ʽ��SMS��ʽ�л����
		uint8 DataLog[8];				//������־��¼����
		uint8 DataScotomaLog[8];		//ä����������
		uint8 ParLoad[sizeof(CN_Ba_WordPar)/sizeof(uint16)]; //���������ϴ�
		uint32 WireLessPar[sizeof(CN_Ba_LessPar)/sizeof(uint16)]; //���ߴ�������ַ
		uint32 DePassWord; 				//��λ�ն�����
		uint32 AccTimer;				//ACC�ۼ�ʱ��
		uint32 RunLen;					//��ʻ���
		uint8 PerPuse;					//���ٴ�����ÿ����������
		uint16 CarFeature;				//��������ϵ��
		uint8 TakeLCD;					//�Ƿ�װ������
		uint8 OilFrequency;				//��λ����������Ƶ��
		uint16 SleepTimer;				//ACC�غ�����
		uint16 CloseTimer;				//ACC�غ�ػ�
		uint8 LogMess;					//��½�Ƿ���ʾ����ʻԱ
		uint8 TaskVid;					//�Ƿ�װ����ͷ
		st_Waring_Par	CN_High_st_Waring_Par;	//���ٱ�������
		st_Waring_Par	CN_Low_st_Waring_Par;	//���ٱ�������
		st_Waring_Par	CN_Vo_st_Waring_Par;	//�͵�ѹ��������
		st_VidType		CN_st_VidType;			//��������
		uint32 OrderFrmTimer;					//ԤԼ��������ȷ����
		uint8 HardWareEdit[8];					//Ӳ���汾
		uint8 SoftWareEdit[8];					//����汾
		uint8 MachID[8];						//����ID
		st_AgreeOn_AmendMenum	CN_st_AgreeOn_AmendMenum; //�޸Ĺ̶��˵�
		st_AgreeOn_Phone	CN_st_AgreeOn_Phone;		 //�̶��绰����
	    st_AgreeOn_ConfineCall  CN_st_AgreeOn_ConfineCall;//����ͨ������״̬
		st_AgreeOn_Driver	CN_st_AgreeOn_Driver;		 //��ʻԱ
		uint8 DriverID[10];								 //��ǰ��ʻԱ��Ϣ
	}st_AgreeOn_Agree_Par_Cut;	

	/**************************************�趨�������*********************************************************/

	typedef struct
	{	uint8 ParSet[De_AgreeOn_SetPar_Number];	 			//�������Ƿ��Ѿ����ü�<De_AgreeOn_SetPar_Yes>
		st_AgreeOn_Agree_Par_Cut	CN_st_AgreeOn_Agree_Par_Cut;
	}st_AgreeOn_Agree_Par;
/*-----------------------------------------�������------------------------------------------------------------*/
	//<����Ϊ��>
/*---------------------------------------------�޸Ĺ̶��˵�----------------------------------------------------*/
	//���ݼ�    [�趨����]->[�޸Ĺ̶��˵�]
/*-------------------------------------------�·��ı�����------------------------------------------------------*/
	typedef struct
	{	uint8 Text[200];
	}st_AgreeOn_LoaderTxt;
	
/*----------------------------------------�·����ı��Ĳ˵�-----------------------------------------------------*/
	typedef struct
	{	uint8 ID;					//��ѡ��
		uint8 Cut[40];				//��ѡ����
	}st_AgreeOn_LoaderTxtMenum_Par;
	typedef struct
	{	uint16 ID;					 //��ϢID
		uint8 AnswerNumber;
		uint8 Infor[200];			 //��Ϣ����
		st_AgreeOn_LoaderTxtMenum_Par	CN_st_AgreeOn_LoaderTxtMenum_Par[10];
	}st_AgreeOn_LoaderTxtMenum;
	
/*------------------------------------------���ù̶��绰------------------------------------------------------*/
	//���ݼ�    [�趨����]->[���ù̶��绰]	
	
/*--------------------------------------------ͨ������--------------------------------------------------------*/
	typedef struct
	{	uint8 Phone[15];
	}st_AgreeOn_CallAnswer;
/*--------------------------------------------�������--------------------------------------------------------*/
	#define De_Agree_AgreeOn_UpdateSoftWare_Host					0  			//����
	#define De_Agree_AgreeOn_UpdateSoftWare_Display					1			//������
	typedef struct
	{	uint8 Device;			//���������豸��<De_Agree_AgreeOn_UpdateSoftWare_Host>��<De_Agree_AgreeOn_UpdateSoftWare_Display>
		uint32 IP;			   	//TFTP���ط�������IP��ַ
		uint16 Port;			//�˿ں�
		uint8 Use[40];			//�û���
		uint8 Pass[40];			//����
		uint8 FileName[200];	//�ļ�·��
	}st_AgreeOn_UpdateSoftWare;
/*--------------------------------------------��ѯ����-------------------------------------------------------*/
	#define De_AgreeOn_LookPar_Yes							1
	#define De_AgreeOn_LookPar_NO							0
	typedef struct
	{	uint8 Par[De_AgreeOn_SetPar_Number];
	}st_AgreeOn_LookPar;
	
/*---------------------------------------------Զ�̿���------------------------------------------------------*/
	#define De_AgreeOn_Contrl_Open							1		//����
	#define De_AgreeOn_Contrl_Close							3		//�������
	typedef struct
	{	uint8 Contr0;
		uint8 Contr1;
		uint8 Contr2;
	}st_AgreeOn_Contrl;
	

/*--------------------------------------------�������ķ�����--------------------------------------------------*/	
	typedef struct
	{	uint8 APN[32];					
		uint32 IP;
		uint16 Port;
	}st_AgreeOn_ConfigCentrSever;
/*--------------------------------------------���λ�ն�----------------------------------------------------*/
	typedef struct
	{	uint32 PassWord;
	}st_AgreeOn_Activation;


/*====================================================��չЭ��==================================================*/
	
/*---------------------------------------------��ѯָ�����͵���Ƭ---------------------------------------------*/
	typedef struct
	{	st_VidType	CN_st_VidType;			//��ѯ��������
		uint8 WorkPar;						//����ʱ�Ĺ�������
		uint8 StartDate[4];					//��ʼ����
		uint8 EndDate[4];					//��������
	}st_AgreeOn_LookJpg;				   	//
/*------------------------------------------------��ѯʵʱ��Ƭ------------------------------------------------*/
	#define De_st_AgreeOn_JpgIng_Contrl_End					1
	#define De_st_AgreeOn_JpgIng_Contrl_Start				0					
	typedef struct
	{	uint8 Contrl;						//��ʼ�ϴ�
		uint8 VidTimer;						//������
		uint16 LoadNumber;					//�ϴ�����
	}st_AgreeOn_JpgIng;						//
	/*------------------------------------------������������--------------------------------------------------*/
	#define De_AgreeOn_SetVidType_Type_Stop						0 			//ֹͣ����
	#define De_AgreeOn_SetVidType_Type_Number					1			//��ֵ����
	#define De_AgreeOn_SetVidType_Type_NumberCut				2			//��ֵ��Χ������
	#define De_AgreeOn_SetVidType_Type_No						3			//������Ч
	typedef struct
	{	uint32 Addree;
		uint8 OpenOrClose;
		uint8 State;
	}st_AgreeOn_Less_Switch;
	typedef struct
	{	uint32 Addree;
		int32 Temp;
		uint8 State;
	}st_AgreeOn_Less_Temp;
	typedef struct
	{	uint8 Switch1;
		uint8 Switch2;
		uint8 Switch3;
		uint8 Switch4;
		uint8 Switch5;
		uint8 Switch6;
		uint8 Switch7;
		uint8 Switch8;
		uint8 Switch9;
		uint8 Switch10;
		uint8 Switch11;
		uint8 Switch12;
		uint8 Switch13;
		uint8 Switch14;
		uint8 Switch15;
		uint8 Switch16;
		st_AgreeOn_Less_Switch CN_Less_Switch1;
		st_AgreeOn_Less_Switch CN_Less_Switch2;
		st_AgreeOn_Less_Switch CN_Less_Switch3;
		st_AgreeOn_Less_Switch CN_Less_Switch4;
		st_AgreeOn_Less_Switch CN_Less_Switch5;
		st_AgreeOn_Less_Switch CN_Less_Switch6;
		uint32 AccTimer;
		uint32 Mileage;
		uint16 Oil1;
		uint8 Sem;
		uint32 SendOilTimer;
		int32 Temp;
		uint16 Oil2;
		uint32 Pulse;
		uint16 Humidity;
		uint8 OilBaifen;
		st_AgreeOn_Less_Temp CN_st_AgreeOn_Less_Temp1;
		st_AgreeOn_Less_Temp CN_st_AgreeOn_Less_Temp2;
		st_AgreeOn_Less_Temp CN_st_AgreeOn_Less_Temp3;
		st_AgreeOn_Less_Temp CN_st_AgreeOn_Less_Temp4;
	}st_AgreeOn_SetVidType_Par;
	
	
	typedef struct
	{	uint8 Type[sizeof(CN_Ba_WordPar)/sizeof(uint16)];
		st_AgreeOn_SetVidType_Par	CN_st_AgreeOn_SetVidType_Par[2]; 	
	}st_AgreeOn_SetVidType;

/*------------------------------------------------������------------------------------------------------------*/
	typedef struct
	{	uint8 ID;					//������ID
		uint8 Type;					//����������
		uint8 Select;				//����ѡ��
		uint8 Name[40];				//����������
		uint8 InputID[10];			//�������ID
		uint8 SelectName[10][40];	//�������������
	}st_AgreeOn_Tabel_Input;
	
	typedef struct
	{ 	uint8 DateTime[7];
		uint8 SumNumber;  			//�ܶ���
		uint8 Number;				//���ζ���
		uint32 TabelID;
		uint32 BackID;
		uint8 Name[40];
		st_AgreeOn_Tabel_Input	CN_st_AgreeOn_Tabel_Input[3];
	}st_AgreeOn_TabelList;
/*--------------------------------------------��ѯ��������------------------------------------------------------*/
	//<����Ϊ��>	
/*---------------------------------���չ̶�ʱ���ϴ���������------------------------------------------------------*/
	typedef struct
	{	uint8 Com;
		uint8 Number;
		uint8 Timer[10][3];	
	}st_AgreeOn_WorkParTimer;
	
/*-------------------------------------���ռ���ϴ���������-----------------------------------------------------*/
	typedef struct
	{	uint8 Com;
		uint32 AccOpenTimer;
		uint32 AccCloseTimer;
		uint32 Space;
	}st_AgreeOn_WorkParSpace;
/*----------------------------------------��ѯ��־�ļ�---------------------------------------------------------*/
	#define De_AgreeOn_LookLog_Type_Track							1			//׷�ٲ������洢���
	#define De_AgreeOn_LookLog_Type_WorkPar							2			//���������ϴ����
	#define De_AgreeOn_LookLog_Type_Pone							3			//�洢��Ƭ
	#define De_AgreeOn_LookLog_Type_Reduce							4			//ѹ������
	typedef struct
	{	uint8 Type;
		uint8 StartDateTimer[7];
		uint8 EndDateTimer[7];
	}st_AgreeOn_LookLog;
/*--------------------------------------------���ñ�������----------------------------------------------------*/
	#define De_AgreeOn_SetWaringTerm_Type_Stop						0 			//ֹͣ����
	#define De_AgreeOn_SetWaringTerm_Type_Number					1			//��ֵ����
	#define De_AgreeOn_SetWaringTerm_Type_NumberCut					2			//��ֵ��Χ�ڱ���
	#define De_AgreeOn_SetWaringTerm_Type_No						3			//�ޱ���
	typedef struct
	{ 	uint8 Type[sizeof(CN_Ba_WordPar)/sizeof(uint16)];
		st_AgreeOn_SetVidType_Par	CN_st_AgreeOn_SetVidType_Par[2];
	}st_AgreeOn_SetWaringTerm;	
/*---------------------------------------------��ѯ��������--------------------------------------------------*/
	//<����Ϊ��>	


/*=================================================����Э��ר��==============================================*/
/*---------------------------------------------����Բ��·��--------------------------------------------------*/	
	typedef struct
	{	uint16 ID;
		uint16 Pro;
		uint32 Latitude;	//ά��
		uint32 Longitude;
		uint32 PI;
		uint8 StartTimer[3];
		uint8 EndTimer[4];
		uint8 HighSpeed;
		uint16 HighSpeedTimer;
	}st_AgreeOn_SetRound_Par;
	
	
	typedef struct
	{	uint16 Number;
		st_AgreeOn_SetRound_Par	CN_st_AgreeOn_SetRound_Par[5];
	}st_AgreeOn_SetRound;
/*--------------------------------------ɾ��Բ��·��-----------------------------------------------------------*/
	typedef struct
	{	uint16 Number;
		uint16 ID[100];
	}st_AgreeOn_DelRound;
	
/*---------------------------------------------------���þ���·��----------------------------------------------*/
	typedef struct
	{	uint16 ID;
		uint8 Pro;
		uint32 Latitude[2];
		uint32 Longitude[2];
		uint8 StartTimer[3];
		uint8 EndTimer[3];
		uint8 HighSpeed;
		uint16 HighSpeedTimer;
	}st_AgreeOn_SetRectangle_Par;
	
	typedef struct
	{	uint16 Number;
		st_AgreeOn_SetRectangle_Par	CN_st_AgreeOn_SetRectangle_Par[5];
	}st_AgreeOn_SetRectangle;
/*--------------------------------------ɾ��Բ��·��-----------------------------------------------------------*/
	typedef struct
	{	uint16 Number;
		uint16 ID[100];
	}st_AgreeOn_DelRectangle;
	
/*------------------------------------------���ö����·��----------------------------------------------------*/
	typedef struct
	{	uint16 ID;
	   	uint16 Pro;
		uint16 Number;
		uint32 Latitude[100];
		uint32 Longitude[100];
		uint8 StartTimer[3];
		uint8 EndTimer[4];
		uint8 HighSpeed;
		uint16 HighSpeedTimer;
	}st_AgreeOn_SetPolygon;
	
/*--------------------------------------ɾ�������·��-----------------------------------------------------------*/
	typedef struct
	{	uint16 Number;
		uint16 ID[100];
	}st_AgreeOn_DelPolygon;
	
/*--------------------------------------����·������-----------------------------------------------------------*/
	typedef struct
	{	uint16 ID;
		uint16 Pro;
		uint8 StartTimer[3];
		uint8 EndTimer[3]; 
		uint8 HighSpeed;
		uint16 HighSpeedTimer;
		uint16 Height;
		uint16 Number;
		uint8 SumSec;
		uint8 NonSec;
		uint32 Latitude[100];
		uint32 Longitude[100];
	}st_AgreeOn_SetRoadMap;
	
/*-----------------------------------------ɾ��·������----------------------------------------------------------*/
	typedef struct
	{	uint16 Number;
		uint16 ID[100];
	}st_AgreeOn_DelRoadMap;
	
/*---------------------------------------����ѹ���ش�-----------------------------------------------------------*/
	#define De_AgreeOn_Reduce_Data_Space					0x00				//��λ����
	#define De_AgreeOn_Reduce_Data_WordSpace				0x01				//������������λ����	
	typedef struct
	{	uint8 Data;
		uint8 AccOpenTimer;
		uint8 AccCloseTimer;
		uint8 Space;
		uint16 Number;
	}st_AgreeOn_Reduce;
	
/*---------------------------------------���ü�ʻԱID-----------------------------------------------------------*/
	//���ݼ�    [�趨����]->[���ü�ʻԱID]	
	
/*---------------------------------------���ĵ���--------------------------------------------------------------*/
	typedef struct
	{	uint32 Latitude;
		uint32 Longitude;
		uint32 State;
	}st_AgreeOn_Navigation_Par;
	typedef struct
	{	uint8 DateTimer[7];
		uint8 Number;
		uint8 Text[256];
		st_AgreeOn_Navigation_Par	CN_st_AgreeOn_Navigation_Par[100]; 
	}st_AgreeOn_Navigation;
	
/*--------------------------------------------�ֻ��ı�����---------------------------------------------------*/
	typedef struct
	{	uint8 Buf[200];
	}st_AgreeOn_HandTxt;
	
/*------------------------------------------�ֻ�������Ϣ---------------------------------------------------*/
	typedef struct
	{	uint16 ID;
		uint8 Buf[200];
	}st_AgreeOn_HandAttemper;
	
	
/*============================================���⳵��ר��Э��==================================================*/
	/*------------------------------------------�޸Ķ�����Ϣ---------------------------------------------------*/
	typedef struct
	{	uint8 ID;	
		uint8 Cut[40];
	}st_AgreeOn_AmendForm_Par;
	typedef struct
	{ 	uint8 Number;
		st_AgreeOn_AmendForm_Par	CN_st_AgreeOn_AmendForm_Par[30];
	}st_AgreeOn_AmendForm;
	/*------------------------------------------�·�����������Ϣ------------------------------------------*/
	typedef struct
	{	uint8 Type;
		uint16 ID;
		uint8 DateTimer[7];
		uint8 Cut[200];	
	}st_AgreeOn_UpLoaderForm;
	
	/*---------------------------------------�·���������ɹ���Ϣ------------------------------------------------*/
	typedef struct
	{	uint16 ID;
		uint8 Phone[15];
		uint8 Cut[200];
	}st_AgreeOn_UpLoaderFormSuc;
	
	/*--------------------------------------------�·���������ʧ����Ϣ-------------------------------------------*/
	typedef struct
	{	uint16 ID;
	}st_AgreeOn_UpLoaderFormErro;
	
	/*--------------------------------------------�·�����ȡ����Ϣ--------------------------------------------*/
	typedef struct
	{	uint16 ID;
	}st_AgreeOn_UpLoaderCan;
	
/*=========================================���Ͳ������ݽṹ����==================================================*/	

	
						
			
						
	
	
