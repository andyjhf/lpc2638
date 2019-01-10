#define De_End_Pusen
#ifdef 	De_End_Pusen
/*=========================================Include File========================================================*/
	#include "..\..\APP\config.h"
	#include "..\..\AgreeOn\TzDefine\Tz_WorkParDefine.h"	
/*==========================================Define Data========================================================*/
	#define De_Suc_Sensor											0						//�ɹ�
	/*++++++++++++++++++++++++++++++++++++++�������һ����++++++++++++++++++++++++++++++++++++++++++++++++*/	
	#define De_Erro_Sensor_Less										1
	/*++++++++++++++++++++++++++++++++++++++++��������++++++++++++++++++++++++++++++++++++++++++++++++++++*/
	
	/*++++++++++++++++++++++++++++++++++++++��������չ����++++++++++++++++++++++++++++++++++++++++++++++++*/
	#define De_Sensor_WordPar_VaCheck								0x1000					//��ѹ���
	#define De_Sensor_WordPar_Gps									0x1001					//GPS����

	#define De_Sensor_WordPar_Display								0x1002					//������	
	
	#define De_Sensor_WordPar_Temperture_1                          0x1003    				//�¶�1·
	#define De_Sensor_WordPar_Temperture_2                          0x1004    				//�¶�2·
	#define De_Sensor_WordPar_GprsTzxy_1							0x1005					//GPRS�豸����1
	#define De_Sensor_WordPar_GprsTzxy_2							0x1006					//GPRS�豸����2
	#define De_Sensor_WordPar_UartTzxy_1							0x1007					//UART����Э��
	#define De_Sensor_WordPar_UartTzxy_2							0x1008					//UART����Э��
	#define De_Sensor_WordPar_MessagTzxy							0x1009					//��������Э��
	#define De_Sensor_WordPar_Arearect								0x100A					//��������
	#define De_Sensor_WordPar_AreaCirc								0x100B					//Բ������
	#define De_Sensor_WordPar_Help									0x100C					//��������

	#define De_WordPar_NoPar										0xffff					//�˲���������
/*===========================================����״̬����======================================================*/
	/*---------------------------------------�������������-----------------------------------------------*/
	#define De_Sensor_Par_Onoff										1		  			//��ʾΪ������
    #define De_Sensor_Par_Temp										2		  			//��ʾΪ�¶�
	#define De_Sensor_Par_Timer										3					//ͳ��ʱ��
	#define De_Sensor_Par_Milleage									4					//���ͳ��
	#define De_Sensor_Par_Oil										5					//����
	#define De_Sensor_Par_Pulse										6					//����
	#define De_Sensor_Par_Sem										7					//�ź�ǿ��
	#define De_Sensor_Par_Humidity									8					//ʪ��
	#define De_Sensor_Par_ADC										9					//��ѹ���
	#define De_Sensor_Par_Baifen									10					//�����ٷ�
	#define De_Sensor_Par_Gps										11					//GPS����
	#define De_Sensor_Par_Display									12					//��ʾ�豸
	#define De_Sensor_Par_Tzxy										13					//����Э��	
	#define De_Sensor_Par_No										0xff				//�޲���
	
	
	
	#define De_Sensor_Par_Onoff_Open				     			0		  			//��ʾ����Ϊ��״̬
	#define De_Sensor_Par_Onoff_Close				    			1		  			//��ʾ����Ϊ�ر�״̬

	#define De_Sensor_Par_Onoff_In									0					//��ʾ�������ڲ�
	#define De_Sensor_Par_Onoff_Out									1					//��ʾ�������ⲿ
	/*-------------------------------------------������״̬-----------------------------------------------*/
	#define De_Sensor_State_Suc										0	 				//��������������
	#define De_Sensor_Battery_State_Erro							1		  			//��������ع���������	
   	#define De_Sensor_Par_State_Erro								3					//����������������
	#define De_Sensor_MaxDly_State_Erro								4					//��ʱ	

	#define De_Sensor_ACC_Open										0					//ACC״̬��
	#define De_Sensor_ACC_Close										1					//ACC״̬�ر�

	#define De_Sensor_Nofd											0xff				//û�з���FD
	/*=====================================������������===================================================*/
	#define De_Display_Host_Order_Answer							0x00				//����Ӧ��ɹ�
	#define De_Display_Host_Order_DeliverCentr						0x09				//ת������ָ��
	#define De_Display_Host_Order_SysInfor							0x02				//ϵͳ��Ϣ
	#define De_Display_Host_Order_Phone								0x03				//�绰ָ��
	#define De_Display_Host_Order_InitStart							0x04				//��ʼ����ʼ
	#define De_Display_Host_Order_InitOver							0x05				//��ʼ������
	#define De_Display_Host_Order_HostSoft							0x06				//�������
	#define De_Display_Host_Order_ConInfor							0x07				//���Ϳ�����Ϣ
	#define De_Display_Host_Order_ParAnswer							0x08				//����Ӧ��
	
	/*=====================================��������������=================================================*/
	#define De_Display_Device_Order_Answer							0x70				//������Ӧ��
	#define De_Display_Device_Order_Phone							0x71				//�绰ָ��
	#define De_Display_Device_Order_SeePar							0x72				//�鿴����
	#define De_Display_Device_Order_SetPar							0x73				//���ò���
	#define De_Display_Device_Order_Log								0x74				//��¼ָ��
	#define De_Display_Device_Order_OnCen							0x75				//�ϴ�����ָ��
	#define De_Display_Device_Order_SeePci							0x76				//�鿴ͼƬ
	#define De_Display_Device_Order_Voic  							0x77				//��������


	#define De_Display_SeePar_Suc									0x00				//������ѯ�ɹ�
	#define De_Display_SeePar_Erro									0x02				//������ѯʧ��
	#define De_Display_Oper_Suc										0x00				//ִ�гɹ�

	#define De_Sensor_Display_Agree									0x00				//��������
	#define De_Sensor_Display_Send									0x01				//��������

	#define De_Display_Answer_Suc									0x00
	#define De_Display_Answer_Erro									0x02	

	/*=====================================�����������ඨ��================================================*/
	 #define De_Display_Agree_CallPhone								0x00				//����绰
	 #define De_Display_Agree_ClosePhone							0x03				//�ҵ绰
	 #define De_Display_Agree_AnswerPhone							0x02				//�ӵ绰
	 #define De_Display_Agree_CallPhone1							0X04				//����ֻ�
	 #define De_Display_Par_Integral								0X0000				//��ǰ����			
	/*================================================================================================*/	
	#define De_Display_Par_ListenPhone								0X0100				//��������
	#define De_Display_Par_ResetPhone								0x0101				//��λ����
	#define De_Display_Par_CentrSevenPhone							0x0102				//���ŷ������
	#define De_Display_Par_WarningPhone								0x0103				//��������
	#define De_Display_Par_APN	   									0x200				//APN����
	#define De_Display_Par_MastIP									0x201				//�����ķ���IP
	#define De_Display_Par_MastDomain								0x202				//������
	#define De_Display_Par_ReserveIP								0x203				//������IP
	#define De_Display_Par_ReserveDomain							0x204				//����������
	#define De_Display_Par_CenPort									0x205				//���Ķ˿ں�
	#define De_Display_Par_CentHeart								0x206				//�����������
	#define De_Display_Par_DsnSever								   	0x207				//DSN
	#define De_Display_Par_MachiID									0x300				//����ID
	#define De_Display_Par_PassWord									0x301				//����
	#define De_Display_Par_SoftWare									0xf04				//����汾��
	#define De_Display_Par_SelfIP									0xf01				//����IP
	#define De_Display_Par_NonceIP									0xf02				//��ǰ����IP
	#define De_Display_Par_CommEdit									0xf05				//Э��汾��
	#define De_Display_Par_Tracks									0xf00				//׷�ټ��


/*=============================================Data Define======================================================*/	
	#define De_Tzxy_SendBuf_Send						0
	#define De_Tzxy_AgreeBuf_Agree						1
	typedef struct
	{	uint8 ResultOrSend;
		uint16 SizeofBuf;
		uint8 *Buf;
	}st_Dev_Tzxy_Send;
	typedef struct
	{	uint16 SizeofBuf;
		uint8 *Buf;


	}st_Dev_Tzxy_Agree;
	
	/*+++++++++++++++++++++++++++++++++++++++++���ͽṹ��++++++++++++++++++++++++++++++++++++++++++++++++++*/
	typedef struct
	{	uint8 SendOrAgree;	  //���ͻ��ǽ���
		uint8 ID;
		void *SendData;		  //������ͣ����͵�����
 	}st_Display_Send;

	typedef struct
	{	uint8 ID;
		void *AgreeData;

	}st_Display_Agree;

	/*+++++++++++++++++++++++++++++++++++++++++���ܽṹ��+++++++++++++++++++++++++++++++++++++++++++++++++*/
	typedef struct
	{	uint8 Order;
		uint8 Result;
	}st_Display_Agree_Answer;

	typedef struct
	{	uint8 Type;
		uint8 Phone[15];
	}st_Display_Agree_Phone;

	typedef struct
	{	uint32 PassWord;
		uint8 ParNumber;
		uint8 YesOnNo[20];	
	}st_Display_Agree_SeePar;
	typedef struct
	{	uint32 PassWord;
		uint16 ParID;
		void *ParCut;

	}st_Display_Agree_SetPar;
	typedef struct
	{	uint8 SoftEdit[2];
	}st_Display_Agree_Log;
	typedef struct
	{	uint8 *Data;


	}st_Display_Agree_OnCen;
	typedef struct
	{	uint8 VolSize;


	}st_Display_Agree_Voic;

	typedef struct
	{	int16 Integral;				  //��ǰ����
		uint8 ListenPhone[15];		  //��������
		uint8 ResetPhone[15];	  			
		uint8 CentrSevenPhone[15];
		uint8 WarningPhone[15];
		uint8 APN[32];
		uint32 MastIP;
		uint8 MastDomain[128];
		uint32 ReserveIP;
		uint8 ReserveDomain[128];
		uint16 CenPort;
		uint8  CentHeart;
		uint32 DsnSever;
		uint8 MachiID[16];
		uint32 PassWord;
		uint8 SoftWare[8];
		uint32 SelfIP;
		uint32 NonceIP;
		uint8 CommEdit;
		uint32 Tracks;
	}st_Display_Par_Cut;

	typedef struct
	{	st_Display_Par_Cut	CN_st_Display_Par_Cut;
		uint8 Set[20];
		uint32 PassWord;
       	}st_Display_Par;
	 typedef struct
	{	uint16 Par;
		uint8 Type;
		void *Point;
		uint16 SizeofPoint;
	}st_Display_Par_Set;


	/*+++++++++++++++++++++++++++++++++++++++++���ͽṹ��+++++++++++++++++++++++++++++++++++++++++++++++++*/
	typedef struct
	{	uint8 Result;
		uint8 AnswerID;
	}st_Display_Order_Answer;					//����Ӧ������

	typedef struct
	{	uint16 SizeofBuf;
		uint8 *Buf;
	}st_Display_Order_DeliverCentr;		  		//ת������ָ��

	typedef struct
	{	int16 Integral;	 						//��ǰ��Ļ����
		uint8 DateTime[7];						//��
		uint8 GpsState;							//GPS״̬
		uint8 VidState;							//����ͷ״̬
		uint8 ContrState;						//����״̬
		uint8 GprsSem;							//GPRS�ź�ǿ��
		uint8 Carrier;							//��Ӫ��
		uint8 CarState;							//����״̬
		uint8 ExigenceState;					//����״̬
		uint8 WaringPci;						//����ͼƬ�洢
		uint8 CarSpeed;							//�����ٶ�
		uint8 StarNumber;						//���Ǹ���
		uint8 TallyState;						//�Ƽ���״̬
		uint8 VolState;							//��ѹ״̬
	}st_Display_Order_SysInfor;				 	//ϵͳ��Ϣ
	typedef struct
	{	uint8 PhoneType;						//�绰����
		uint8 Phone[15];						//�绰����
	}st_Display_Order_Phone;					//�绰ָ��
	typedef struct
	{	uint8 Value;							//�������ȱ�


	}st_Display_Order_HostSoft;			 		//�������

	typedef struct
	{	uint8 BeerLen;	 						//����������
		uint8 BeerNumber;						//����������
		uint8 VoiceReport;						//�Ƿ���Ҫ��������
		uint8 TextCut[128];						//��������
	}st_Display_Order_ConInfor;					//������Ϣ


	typedef struct
	{	uint8 Result;
		uint16 ParID;
		uint8 *ParCut;
	}st_Display_Order_ParAnswerCut;   				//������ѯ

	typedef struct
	{	uint8 ParNumber;
		st_Display_Order_ParAnswerCut	*ptst_Display_Order_ParAnswerCut[];
	}st_Display_Order_ParAnswer;
	
/*=============================================Data Define======================================================*/	
	/*+++++++++++++++++++++++++++++++++++++++���������������++++++++++++++++++++++++++++++++++++++++++++++*/
	
	typedef struct
	{	uint8 DateTime[7];						//YYYYMMDD HHMM SS,ʱ�����
		uint8 LocationTrue;						//��λ�Ƿ���Ч��De_Gps_Location_True			��Ч
		uint8 LatHem;							//γ�Ȱ���		'N'  ������	 'S'�ϰ���  ������Ч
		uint8 LongHem;							//���Ȱ���		'E'	 ����	 'W'����	������Ч
		uint32 Latitude;						//γ��			����4λС��   
		uint32 Longitude;   			 		//����			����4λС��
		uint32 Speed;							//�ٶ� 			��λ�������һλС��
		uint32 Angle;							//����Ƕ�		�ȱ�  ����һλС��    
	
	}st_Gps_Data_GPRMC;
	typedef struct
	{	uint8 	StarNumber;						//���Ǹ���
		int32 Height;							//���θ߶�
	
	}st_Gps_Data_GPGGA;
	typedef struct
	{	st_Gps_Data_GPRMC	CN_st_Gps_Data_GPRMC;
		st_Gps_Data_GPGGA	CN_st_Gps_Data_GPGGA;	
	}st_Data_Gps;
	
	typedef struct
	{	uint8 NonState;
		uint32 AccTimer;
	}st_Sensor_Data_Acc; 						//ACCͳ��
	
	typedef struct
	{	uint32 Addree;				    		//��������ַ	 
		uint16 WorkPar;							//��������ID
		uint32 MaxDly;							//���ʱʱ��
	}st_Sensor_DataPar;							//����������

	typedef struct
	{	uint8 Work;			  					//����������״̬
	 	uint8 Battery;		  					//���������״̬
		uint8 Dly;								//���ʱ��
 	}st_Sensor_State; 
	typedef struct
	{	st_Sensor_DataPar	CN_st_Sensor_DataPar;
		uint8 Phone[15];	
	}st_Sensor_Sms_DataPar;

	typedef struct
	{	uint16 WorkPar;
		uint8 Type;
	}st_Sensor_Par2Type;
	
	typedef struct
	{	uint16 (*Init)(void);	   											//��ʼ��
		uint16 (*Open)(st_Sensor_DataPar	*ptst_Sensor_DataPar,uint8 *fd);		//��
		uint16 (*Close)(uint8 fd);											//�ر�
		uint16 (*Read)(uint8 fd,void *SendBuf,void *AgreeBuf);				//��
		uint16 (*GetState)(st_Sensor_State	*ptst_Sensor_State,uint8 fd);	//��ȡ״̬
	}st_Fun_Sensor2Hard;
						
	typedef struct
	{	const st_Fun_Sensor2Hard	*ptst_Less_DataPar;									//����������
	  	const st_Sensor_Par2Type	*ptst_Sensor_Par2Type;
		uint16 SizeofPar;													//��������֧�ֵĲ�������
	}st_Sensor_ParList;	

	/****************************���򱨾������ݽṹ******************************/	  
	typedef struct
	{	uint32 Latitude; 		//����γ��
		uint32 Longitude;		//���ľ���
		uint32 Radii;			//�뾶 
	}st_RoundPar_Data;


	typedef struct
	{	uint32 LeftLatitude; 	//���½�γ��
		uint32 LeftLongitude;	//���½Ǿ���
		uint32 RightLatitude;	//���Ͻ�γ��
		uint32 RightLongitude;	//���ϽǾ���
	}st_Rectangle_Data;  
	
	typedef struct
	{	st_Sensor_DataPar	CN_st_Sensor_DataPar; 		//��ʱ�Ĳ���
		union 
		{	
			st_Rectangle_Data	CN_st_Rectangle_Data;	//���β���  
			st_RoundPar_Data	CN_st_RoundPar_Data;	//Բ�β��� 			
		}CN_un_Par;
	}st_Open_RunLen;
	
	
	typedef union  
	{	st_Sensor_DataPar	CN_st_Sensor_DataPar; 		//����
		st_Open_RunLen		CN_st_Open_RunLen;			//��ʱ�Ĳ���
	} un_OpenPar;
#endif
