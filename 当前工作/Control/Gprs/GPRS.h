#define GPRS_H
#ifdef 	GPRS_H
/*==========================================Include File====================================================*/	
	#include "..\..\APP\config.h"											//LPC2368�Ĵ�������
 	#include "stdlib.h"	
	
	#ifdef De_GPRS_Compiler													//C��������
		#include "..\..\Dev\Gprs\_GprsHard.h"
		#include "..\..\miscellaneous\CodeTrans\AscNumber.h"				//��������ת����Դ
		#include "..\..\miscellaneous\Date\Date.h"							//����������Դ
		#include "..\..\miscellaneous\Arithmetic\Arithmetic.h" 				//�����㷨
		#include "..\..\Control\Timer\Timer.h"								//����ʱ���ʱ
		#include "..\..\File\rwFile.h"
	#else
		#include "..\..\Dev\Gprs\GprsPublicDe.h"
	#endif
/*=========================================Define Data======================================================*/
	#define De_Suc_Gprs														0				//�ɹ�
	/*-------------------------------------�������һ����-------------------------------------------------*/
	#define De_Erro_GprsLink_Over											1				//�޴򿪵���·
	#define De_Erro_Gprs_Explain											De_Erro_GprsLink_Over+1	//��������
	#define De_Erro_Gprs_LinkClose											De_Erro_Gprs_Explain+1	// ����·�ر�
	#define De_Erro_Gprs_Init												De_Erro_Gprs_LinkClose+1	//��ʼ��ʧ��
	#define De_Erro_Gprs_State_NoOpen										De_Erro_Gprs_Init+1			//����û�д�	
	#define De_Erro_Gprs_NoMessageData										De_Erro_Gprs_State_NoOpen+1	//û�ж�������
	#define De_Erro_Gprs_NoPhone											De_Erro_Gprs_NoMessageData+1	//û��������
	#define De_Erro_Gprs_NoIPData											De_Erro_Gprs_NoPhone+1		//û��GPRS����
	#define De_Erro_Gprs_CardNoReg											De_Erro_Gprs_NoIPData+1		//�˿�δע��
	#define De_Erro_Gprs_MEErro												De_Erro_Gprs_CardNoReg+1	//״̬δ��
	#define De_Erro_Gprs_NoTCPIP											De_Erro_Gprs_MEErro+1	 	//û��TCPIP
	#define De_Erro_Gprs_NoCall												De_Erro_Gprs_NoTCPIP+1		//û�е绰
	#define De_Erro_Gprs_FunctionNo											De_Erro_Gprs_NoCall+1		//�˹���û�п�
	#define	De_Erro_Gprs_NoCard												De_Erro_Gprs_FunctionNo+1
	#define De_Erro_Gprs_AnswerPhone										De_Erro_Gprs_NoCard+1
	#define De_Erro_Gprs_Volume												De_Erro_Gprs_AnswerPhone+1
	/*----------------------------------------ϵͳ״̬-------------------------------------------------*/
	
		#define De_Gprs_Phone_Agree_New											0 				//������
		#define	De_Gprs_Phone_Agree_Old											1				//������
		#define De_Gprs_Phone_Agree_Ide											2				//����
		#define De_Gprs_UDPTCP_Agree_New										0				//�µ����ݰ�
		#define De_Gprs_UDPTCP_Agree_Old										1				//�����ݰ�
		#define De_Gprs_UDPTCP_Agree_Ide										2				//����
		#define De_Gprs_UDPTCP_Agree_Close										3				//��·δ��
		#define De_Gprs_State_Open												0				//״̬��
		#define De_Gprs_State_Close												1				//״̬�ر�
		#define De_Gprs_Fd_All													0xff			//����ر�GPRS		
	/*-------------------------------------�����и�����С����----------------------------------------------*/
		#define De_Gprs_Message_Size											160				//����Ϣ�Ĵ�С
		#define De_Gprs_PhoneNumber_Size										15				//�绰�����С
		#define De_Gprs_TCPUDP_Size												1536			//UDP����TCP����С
		#define De_Gprs_HeartFlag_Size											32				//�������Ĵ�С
		#define De_Gprs_APN_Size												32				//APN������С
		#define De_Gprs_Use_Size												16				//�û���������С
		#define De_Gprs_PassWord_Size											8				//�����С
		#define De_Moderm_Message_Max											10				//��δ����Ϣ
		#define De_Moderm_Message_Max1											20				//����Ϣ��󳤶�
	/*++++++++++++++++++++++++++++++++����ϵͳ�й�++++++++++++++++++++++++++++++++++++++++*/
	#ifdef De_GPRS_Compiler
		#define De_Gprs_Task												4
		#define De_Gprs_Stk													384//1536
		#define De_Gprs_TaskDly												40				//��ʱ����ʱ��
	#endif
/*============================================Data Define=====================================================*/
	/*++++++++++++++++++++++++++++++++++++++++���ݽṹ����+++++++++++++++++++++++++++++++++++++++++++*/
		/*---------------------------------����ʹ�ýṹ��----------------------------------------*/
		typedef struct
		{	uint8 LinkType;											//IP��·״̬  UDP  TCP
			uint32 IP;												//hex
			uint16 Com;												//hex
			uint32 SelfHeartTimer;									//��������ʱ��
			uint32 CentrHeartTimer;									//��������ʱ��
			uint8 SelfHeartData[De_Gprs_HeartFlag_Size];			//ASC,�ԡ�/0'��Ϊ����,�������������͵�����
			uint8 HeartDataLength;									//����������
			uint8 CentrHeartData[De_Gprs_HeartFlag_Size];			//ASC,�ԡ�/0'��Ϊ����,�������������͵�����
			uint8 CentrHeartLength;									//����������
		}st_Data_UDPTCP;											//UDP����

		typedef struct
		{	uint8 Yys;												//�鿴��Ӫ��
		   	uint8 IMEI[7];											//IMEI
		   	uint8 Csq;	   											//�ź�ǿ��
		   	uint8 RegisterState;									//ע�����
			uint8 ModelState;										//ģ��״̬
			uint8 SimCarkState;
		}st_Gsm_Net_Information;
		
		typedef struct
		{	uint8 CenterNum[15];									//�������ĺ���
		}st_Gsm_Net_Message;

/*		typedef struct
		{	uint8 APN[De_Gprs_APN_Size+1];							//ASC,�ԡ�/0'��Ϊ����
			uint8 Use[De_Gprs_Use_Size+1];							//ASC,�ԡ�/0'��Ϊ����
			uint8 PassWord[De_Gprs_PassWord_Size+1];				//ASC,�ԡ�/0'��Ϊ����	
		}st_Data_IPNet;		*/										//TCP/IP����
		/*------------------------------------����ʹ���¼��ṹ��-------------------------------------------*/
		typedef struct
		{	void (* ptFunNoSem)(void); 								//ϵͳû���ź�
			void (*	ptFunSem)(void);								//ϵͳ���ź�
			void (*	ptFunNoWork)(void);								//ϵͳ������
			void (*	ptGPRS)(void);									//GPRSTCP/IP�Ͽ�
		}st_Affair_Sys;												//ϵͳ�¼�

		typedef struct
		{	void (*	ptFunNewMessage)(uint8 *Phone,uint8 *Message);	//�¶���Ϣ
		}st_Affair_Message;											//ϵͳ����Ϣ�¼�

		typedef struct
		{	void (* ptFunNewPhone)(uint8 *Phone);					//�µ绰�¼�
			void (* ptFunHupWork)(uint8 *Phone);					//�һ��¼�
		}st_Affair_Phone;											//�绰�¼�

		typedef struct
		{	void (*	ptFunNewTCPUDP)(uint8 *Data,uint8 fd,uint16 DataLength);	//�����ݰ�����
			void (*	ptFunLinkClose)(uint8 *fd);						//��·�ر�,��������
		}st_Affair_UDPTCP;
		typedef struct
		{	uint8 Phone[De_Gprs_PhoneNumber_Size]; 				//�绰����	
			uint8 State;										//�������״̬
			uint8 Mod;	  										//�绰ģʽ
			uint8 PhoneState;									//�绰״̬
		}st_Data_Gprs_Call;                                		//�绰����
		typedef struct
		{	uint16 (*	Init)(void);								//��ʼ����ҳ
			uint16 (*	InitSys)(void);								//��ʼ��GPRSģ��
			uint16 (*	InitMessage)(void);							//��ʼ������Ϣ
			uint16 (*	InitPhone)(void);							//��ʼ���绰
			uint16 (*	InitGprs)(st_Data_IPNet	*ptst_Data_IPNet);	//��ʼ��TCP/IP
			
			uint16 (*	OpenSys)(st_Affair_Sys	*ptst_Affair_Sys);	//��ϵͳ�¼�
			uint16 (*	OpenMessage)(st_Affair_Message	*ptst_Affair_Message);	  //�򿪶����¼�
			uint16 (*	OpenIP)(st_Data_UDPTCP	*ptst_Data_UDPTCP,st_Affair_UDPTCP	*ptst_Affair_UDPTCP,uint8 *fd);	//��һ����·���Ҵ򿪶�Ӧ���¼�
			uint16 (*	OpenPhone)(st_Affair_Phone	*ptst_Affair_Phone);  //�򿪵绰�¼�
					

			uint16 (*	CloseSys)(void);	//�ر�ϵͳ�¼�
			uint16 (*	CloseMessage)(void); //�򿪶����¼�
			uint16 (*	CloseIP)(uint8 fd);	//�ر�һ����·���ҹرն�Ӧ���¼�   
			uint16 (*	ClosePhone)(void); //�رյ绰�¼�
		
			uint16 (*	ReadMessage)(uint8 *Phone,uint8 *Message); 			//���¶���Ϣ
			uint16 (*	ReadIP)(uint8 fd,uint8 *Data,uint16 *SizeofData);	//�������ݰ�
			uint16 (*	ReadPhone)(uint8 *Phone);	  //��������
			uint16 (*	AgreePhone)(void);			 //�ӵ绰
			uint16 (*	CloseCall)(void);			 //�ҵ绰
		
		
			uint16 (*	SendMessage)(uint8 *Phone,uint8 *Message);	 	//���Ͷ���Ϣ
			uint16 (*	SendIP)(uint8 fd,uint8 *Data,uint16 SizeofData);  //����IP����
			uint16 (*	SendPhone)(uint8 *Phone,uint8 *PhoneState);		  //��绰
			uint16 (*	SetVolume)(uint8 Volume);						//��������
		
			uint16 (*	GetSysState)(st_Gsm_Net_Information	*ptst_Gsm_Net_Information);//��ȡϵͳ״̬
			uint16 (*	GetMessageState)(st_Gsm_Net_Message	*ptst_Gsm_Net_Message);	   //��ȡ����״̬
			uint16 (*	GetPhoneState)(st_Data_Gprs_Call	*ptst_Data_Gprs_Call);	   //��ȡ�绰״̬
			uint16 (*	GetIPState)(st_Data_UDPTCP	*ptst_Data_UDPTCP,st_HardWare_SeeTCPData	*ptst_HardWare_SeeTCPData);//��ȡTCP/IP״̬
		 	uint16 (*	DNSRIP)(uint8 *DomainName,uint32 *IP);
			uint16 (*	GetIpPro)(uint8 fd,st_Data_UDPTCP	*ptst_Data_UDPTCP);
		 
		 }st_Fun_Gprs;
		/*--------------------------------�ڲ��������ݵĶ���-------------------------------------*/
	#ifdef De_GPRS_Compiler		
		typedef struct
		{	uint32 SelfHeartTimer;
			uint32 CentrHeartTimer;
		}st_Heart_Timer;
		typedef struct
		{	uint8 Message[De_Gprs_Message_Size+1];	 			//����Ϣ����
			uint8 Phone[De_Gprs_PhoneNumber_Size+1];		 	//����Ϣ���뱣��
			uint8 State;										//�¶���Ϣ���߾�
		}st_Data_Gprs_Message;									//����Ϣ����
		typedef struct
		{	uint8 State;										//����״̬
			uint8 OpenOrClose;									//�򿪻��߲���
			uint16 DataLen;										//����
			uint8 Data[De_Gprs_TCPUDP_Size];					//����
			st_Data_UDPTCP	CN_st_Data_UDPTCP;					//��������
			st_Heart_Timer	CN_st_Heart_Timer;
		}st_Data_Gprs_TcpUdp;									//����
		/*----------------------------------------�¼����ܱ�-------------------------------------------------*/
		typedef struct
		{	uint8 SysState;								//ϵͳ��״̬
			uint8 MessageState;							//���Ŵ�״̬
			uint8 PhoneState;							//�绰��״̬
			uint8 IPstate;								//IP��״̬
			st_Affair_Sys	CN_st_Affair_Sys;			//ϵͳ�¼�
		   	st_Affair_Message	CN_st_Affair_Message;	//�����¼�
		  	st_Affair_Phone		CN_st_Affair_Phone;		//�绰�¼�
			st_Affair_UDPTCP	CN_st_Affair_UDPTCP[De_GprsHard_MaxLink];//UDP�¼�
		}st_Affair_Gprs;
	#endif
/*===========================================static Functiion================================================*/
	#ifdef De_GPRS_Compiler	
		static uint16 Init(void);
		static uint16 InitSys1(void);
		static uint16 InitMessage1(void);
		static uint16 InitPhone1(void);
		static uint16 InitGprs1(st_Data_IPNet	*ptst_Data_IPNet);
		
		static uint16 OpenSys1(st_Affair_Sys	*ptst_Affair_Sys);
		static uint16 OpenMessage1(st_Affair_Message	*ptst_Affair_Message);
		static uint16 OpenIP1(st_Data_UDPTCP	*ptst_Data_UDPTCP,st_Affair_UDPTCP	*ptst_Affair_UDPTCP,uint8 *fd);
		static uint16 OpenPhone1(st_Affair_Phone	*ptst_Affair_Phone);
	
		static uint16 CloseSys1(void);
		static uint16 CloseIP1(uint8 fd);
		static uint16 CloseMessage1(void);
		static uint16 ClosePhone1(void);
	
		static uint16 ReadMessage1(uint8 *Phone,uint8 *Message);
		static uint16 ReadIP1(uint8 fd,uint8 *Data,uint16 *SizeofData);
		static uint16 ReadPhone1(uint8 *Phone);
		static uint16 AgreePhone1(void);
		static uint16 CloseCall1(void);
	
	
		static uint16 SendMessage1(uint8 *Phone,uint8 *Message);
		static uint16 SendIP1(uint8 fd,uint8 *Data,uint16 SizeofData);
		static uint16 SendPhone1(uint8 *Phone,uint8 *PhoneState);
		static uint16 SetVolume1(uint8 Volume);
	
		static uint16 GetSysState1(st_Gsm_Net_Information	*ptst_Gsm_Net_Information);
		static uint16 GetMessageState1(st_Gsm_Net_Message	*ptst_Gsm_Net_Message);
		static uint16 GetPhoneState1(st_Data_Gprs_Call	*ptst_Data_Gprs_Call);
		static uint16 GetIPState1(st_Data_UDPTCP	*ptst_Data_UDPTCP,st_HardWare_SeeTCPData	*ptst_HardWare_SeeTCPData);
		static uint16 DNSRIP1(uint8 *DomainName,uint32 *IP);
		static uint16 GetIpPro1(uint8 fd,st_Data_UDPTCP	*ptst_Data_UDPTCP);
	
		static uint16 InitSys(void);
		static uint16 InitMessage(void);
		static uint16 InitPhone(void);
		static uint16 InitGprs(st_Data_IPNet	*ptst_Data_IPNet);	
	
		static uint16 OpenSys(st_Affair_Sys	*ptst_Affair_Sys);
		static uint16 OpenMessage(st_Affair_Message	*ptst_Affair_Message);
		static uint16 OpenIP(st_Data_UDPTCP	*ptst_Data_UDPTCP,st_Affair_UDPTCP	*ptst_Affair_UDPTCP,uint8 *fd);
		static uint16 OpenPhone(st_Affair_Phone	*ptst_Affair_Phone);
	
		static uint16 CloseSys(void);
		static uint16 CloseIP(uint8 fd);
		static uint16 CloseMessage(void);
		static uint16 ClosePhone(void);
	
		static uint16 ReadMessage(uint8 *Phone,uint8 *Message);
		static uint16 ReadIP(uint8 fd,uint8 *Data,uint16 *SizeofData);
		static uint16 ReadPhone(uint8 *Phone);
		static uint16 AgreePhone(void);
		static uint16 CloseCall(void);
	
	
		static uint16 SendMessage(uint8 *Phone,uint8 *Message);
		static uint16 SendIP(uint8 fd,uint8 *Data,uint16 SizeofData);
		static uint16 SendPhone(uint8 *Phone,uint8 *PhoneState);
		static uint16 SetVolume(uint8 Volume);
	
		static uint16 GetSysState(st_Gsm_Net_Information	*ptst_Gsm_Net_Information);
		static uint16 GetMessageState(st_Gsm_Net_Message	*ptst_Gsm_Net_Message);
		static uint16 GetPhoneState(st_Data_Gprs_Call	*ptst_Data_Gprs_Call);
		static uint16 GetIPState(st_Data_UDPTCP	*ptst_Data_UDPTCP,st_HardWare_SeeTCPData	*ptst_HardWare_SeeTCPData);
		static uint16 DNSRIP(uint8 *DomainName,uint32 *IP);		
		static uint16 GetIpPro(uint8 fd,st_Data_UDPTCP	*ptst_Data_UDPTCP);
		static uint16 OperIPData(void); 					//����GPRS
		static uint16 OperMessage(void);
		static uint16 OperPhone(void);
		static uint16 JugeSys(void);
		static uint16 JugeMessage(void);
		static uint16 JugeIPData(void);
		static uint16 BackUpSys(void);
		static uint16 BackUpIP(void);
		static uint32 GetTimeAdd(uint8 *Small,uint8 *Big);
		static void Task(void *pData);	
	#endif	


/*========================================ȫ�ֱ�������=========================================================*/
	#ifdef De_GPRS_Compiler	
		OS_EVENT	*GprsUseSem=NULL;
		OS_STK		*GprsTaskStk=(OS_STK *)(De_Gprs_STK_Ram);//[De_Gprs_Stk];
		uint8 DateTimer[7];	 
		uint8 SMS_State[De_Moderm_Message_Max1];  																		//����ά�ְ�ʱ��
		st_Affair_Gprs	CN_st_Affair_Gprs;															//�¼���
		st_Gsm_Net_Information	CN_st_Gsm_Net_Information;
		st_Gsm_Net_Message	CN_st_Gsm_Net_Message;
		st_HardWare_SeeTCPData	CN_st_HardWare_SeeTCPData;
		const uint8 CN_LinkNumber[]={De_GprsHard_Link0,De_GprsHard_Link1,De_GprsHard_Link2};		//��·���
		st_Data_Gprs_Message	 *ptst_Data_Gprs_Message=(st_Data_Gprs_Message	*)(De_Gprs_Ram);	//ʹ�ö���
		st_Data_Gprs_Call		 *ptst_Data_Gprs_Call=(st_Data_Gprs_Call	*)(De_Gprs_Ram+sizeof(st_Data_Gprs_Message));//�绰����
		st_Data_Gprs_TcpUdp 	 *ptst_Data_Gprs_TcpUdp[De_GprsHard_MaxLink]=	 					//UDP��TCP��������
		{	(st_Data_Gprs_TcpUdp	*)(De_Gprs_Ram+sizeof(st_Data_Gprs_Message)+sizeof(st_Data_Gprs_Call)),
			(st_Data_Gprs_TcpUdp	*)(De_Gprs_Ram+sizeof(st_Data_Gprs_Message)+sizeof(st_Data_Gprs_Call)+sizeof(st_Data_Gprs_TcpUdp)),
			(st_Data_Gprs_TcpUdp	*)(De_Gprs_Ram+sizeof(st_Data_Gprs_Message)+sizeof(st_Data_Gprs_Call)+sizeof(st_Data_Gprs_TcpUdp)*2)	
		};
		uint8 *CN_IPData =(uint8 *)(De_IPData_Ram);
	   	st_Data_IPNet	CN_st_Data_IPNet;
//		st_HardWare_SeeTCPData	CN_st_HardWare_SeeTCPData;
	 /*------------------------------------------������ֵ����------------------------------------------------------*/
	 	st_Affair_Gprs CN_Ba_st_Affair_Gprs=	   															//�¼�������ʼ��
		{ 	De_Gprs_State_Close,
			De_Gprs_State_Close,
			De_Gprs_State_Close,
			De_Gprs_State_Close,
			{NULL,NULL,NULL,NULL},
			{NULL},
			{NULL,NULL},
			{	{NULL,NULL},
				{NULL,NULL},
				{NULL,NULL}
			}	
		};
		const st_Fun_Gprs	CN_st_Fun_Gprs=
		{Init,InitSys1,InitMessage1,InitPhone1,InitGprs1,OpenSys1,OpenMessage1,OpenIP1,OpenPhone1,CloseSys1,
		CloseMessage1,CloseIP1,ClosePhone1,ReadMessage1,ReadIP1,ReadPhone1,AgreePhone1,CloseCall1,SendMessage1,
		SendIP1,SendPhone1,SetVolume1,GetSysState1,GetMessageState1,GetPhoneState1,GetIPState1,DNSRIP1,GetIpPro1};
	#else
		extern st_Fun_Gprs	CN_st_Fun_Gprs;	
	#endif
#endif

