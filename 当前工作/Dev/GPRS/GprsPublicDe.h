/*=======================================include File==========================================================*/
	#include "stdlib.h"																	//����C������
/*=======================================Define Data===========================================================*/
	/*++++++++++++++++++++++++++++++++++++�������һ����++++++++++++++++++++++++++++++++++++++++++++++*/
	#define De_Suc_GprsHard								0 								//�ɹ�
	#define De_Erro_GprsHard_Start						1								//��ҳ����ʼ
	#define De_Erro_GprsHead_NoDriver					De_Erro_GprsHard_Start			//�޴�����		
	#define De_Erro_GprsHard_NoOrder					De_Erro_GprsHead_NoDriver+1		//��֧�ִ�����
	#define De_Erro_GprsHead_ReLen						De_Erro_GprsHard_NoOrder+1		//���ȷ��ش���
	#define De_Erro_GprsHead_NoReVa						De_Erro_GprsHead_ReLen+1		//����ֵ����
	#define De_Erro_GprsHead_FlagHead					De_Erro_GprsHead_NoReVa+1		//��ͷ��Ϣ����
	#define De_Erro_GprsHead_Explain					De_Erro_GprsHead_FlagHead+1		//�����������
	#define De_Erro_GprsHead_ReErro						De_Erro_GprsHead_Explain+1		//���ش���	
	#define De_Erro_GprsHead_NoLink						De_Erro_GprsHead_ReErro+1		//�޴���·
	#define De_Erro_GprsHead_SoftLinkNo					De_Erro_GprsHead_NoLink+1		//����·Ӧ�ò�δ����
	#define De_Erro_GprsHead_OpenPower					De_Erro_GprsHead_SoftLinkNo+1	//����ʧ��
	#define De_Erro_GprsHead_NoInit						De_Erro_GprsHead_OpenPower+1	//������û�г�ʼ��
	#define De_Erro_GprsHead_NoCom						De_Erro_GprsHead_NoInit+1		//�޴�Э�飬ֻ֧��UDP/TCP
	#define De_Erro_GprsHead_OverTimer				   	De_Erro_GprsHead_NoCom+1		//ͨѶ��ʱ
	#define De_Erro_GprsHard_NoInitCONT					De_Erro_GprsHead_OverTimer+1	//û�г�ʼ������
	#define De_Erro_GprsHard_NoIpData					De_Erro_GprsHard_NoInitCONT+1	//û��IP���ݰ�
	/*+++++++++++++++++++++++++++++++++++++����ӿ�++++++++++++++++++++++++++++++++++++++++++++++++++++*/
	#define De_GprsHard_Com_CloseShow					1									//�رջ���
	#define De_GprsHard_Com_GetChipID					De_GprsHard_Com_CloseShow+1			//��ȡ��������
	#define De_GprsHard_Com_GetModermState				De_GprsHard_Com_GetChipID+1			//��ȡ��������״̬
	#define De_GprsHard_Com_GetModermCard				De_GprsHard_Com_GetModermState+1	//����λ��ѯ
	#define De_GprsHard_Com_GetCenterNumber				De_GprsHard_Com_GetModermCard+1		//�������ĺ���
	#define De_GprsHard_Com_GetMessage					De_GprsHard_Com_GetCenterNumber+1	//������Ϣ
	#define De_GprsHard_Com_SetTxtOrPdu					De_GprsHard_Com_GetMessage+1		//�����ı�ģʽ
	#define De_GprsHard_Com_SeeTxtOrPdu					De_GprsHard_Com_SetTxtOrPdu+1		//��ѯ���ַ�ʽ
	#define De_GprsHard_Com_MsgSend						De_GprsHard_Com_SeeTxtOrPdu+1		//���Ͷ���Ϣ				 				//���Ͷ���Ϣ
	#define De_GprsHard_Com_MsgSendData					De_GprsHard_Com_MsgSend+1			//���Ͷ���Ϣ����
	#define De_GprsHard_Com_SeeCarrier					De_GprsHard_Com_MsgSendData+1		//�鿴��Ӫ��
	#define	De_GprsHard_Com_SQ 							De_GprsHard_Com_SeeCarrier+1		//�鿴�ź�ǿ��
	#define	De_GprsHard_Com_DelMsg						De_GprsHard_Com_SQ+1				//ɾ������Ϣ
	#define De_GprsHard_Com_Set_Mem						De_GprsHard_Com_DelMsg+1			//����MEM
	#define De_GprsHard_Com_MessSet						De_GprsHard_Com_Set_Mem+1			//���ö���Ϣ
	#define De_GprsHard_Com_Upadate						De_GprsHard_Com_MessSet+1			//��������
	#define De_GprsHard_Com_Reg							De_GprsHard_Com_Upadate+1			//�鿴����ע�����	
	#define De_GprsHard_Com_IMEI						De_GprsHard_Com_Reg+1				//��ȡIMEI��
	#define De_GprsHard_Com_Chup						De_GprsHard_Com_IMEI+1				//�һ�
	#define De_GprsHard_Com_Sync						De_GprsHard_Com_Chup+1				//����ʹ�ܵ�
	#define De_GprsHard_Com_CGDCONT						De_GprsHard_Com_Sync+1				//���總��
	#define De_GprsHard_Com_Etcpip						De_GprsHard_Com_CGDCONT+1			//����TCP/IP
	#define De_GprsHard_Com_IOMODE						De_GprsHard_Com_Etcpip+1			//����TCP/IPģʽ
	#define De_GprsHard_Com_IPOPENX						De_GprsHard_Com_IOMODE+1			//����·
	#define De_GprsHard_Com_IPSENDX						De_GprsHard_Com_IPOPENX+1			//����TCP/IP���ݰ�
	#define De_GprsHard_Com_SeeDataRead					De_GprsHard_Com_IPSENDX+1			//��ѯδ�����ݰ�
	#define De_GprsHard_Com_IPDR						De_GprsHard_Com_SeeDataRead+1		//��ȡTCP/IP����
	#define De_GprsHard_Com_IPCLOSE						De_GprsHard_Com_IPDR+1				//�ر�TCP/IP��·
	#define De_GprsHard_Com_LogOnTCPIP					De_GprsHard_Com_IPCLOSE+1			//�ر�GPRS����
	#define De_GprsHard_Com_CLIP						De_GprsHard_Com_LogOnTCPIP+1		//����������ʾ
	#define De_GprsHard_Com_ATD							De_GprsHard_Com_CLIP+1				//��绰
	#define De_GprsHard_Com_ATA							De_GprsHard_Com_ATD+1				//�ӵ绰
	#define De_GprsHard_Com_JugeETCPIP					De_GprsHard_Com_ATA+1				//�鿴TCP/IP�Ƿ�����
	#define	De_GprsHard_Com_DNSR						De_GprsHard_Com_JugeETCPIP+1		//��������
	#define De_GprsHard_Com_IPR							De_GprsHard_Com_DNSR+1				//���ò����� 	
	#define De_GprsHard_Com_CLCC						De_GprsHard_Com_IPR+1				//��ȡͨ��״̬
	#define De_GprsHard_Com_SEEIPCLOSE					De_GprsHard_Com_CLCC+1				//�鿴��·�Ƿ�ر�
	#define De_GprsHard_Com_ATTestBps					De_GprsHard_Com_SEEIPCLOSE+1		//����AT����
	#define De_GprsHard_Com_PowerDown					De_GprsHard_Com_ATTestBps+1			//�ػ�����
	#define De_GprsHard_Com_SeeCGDCONT					De_GprsHard_Com_PowerDown+1			//�鿴����	
	#define De_GprsHard_Com_SendExtension				De_GprsHard_Com_SeeCGDCONT+1		//����ֻ�
	#define De_GprsHard_Com_SetVolume					De_GprsHard_Com_SendExtension+1
	/*+++++++++++++++++++++++++++++++++++++ϵͳ״̬++++++++++++++++++++++++++++++++++++++++++++++++++++*/
		/*--------------------------------SIM��״̬------------------------------------*/
		#define	De_GprsHard_SimState_Yes			1					//����
		#define	De_GprsHard_SimState_No				0					//�޿�
		/*------------------------------���֧�ֵ���·��-------------------------------*/
		#define De_GprsHard_MaxLink					3					//��Ӳ�����֧�ֵ���·��
		/*---------------------------------ͨ������------------------------------------*/
		#define De_GprsHard_Call_Peper				0  					//����ͨ��
		#define De_GprsHard_Call_SumPeper			1					//����ͨ��
		/*-------------------------------����ͨ����ʽ----------------------------------*/
		#define De_GprsHard_CallType_Initiative	 	0					//����ģʽ����
		#define De_GprsHard_CallType_Passive		1					//����ģʽ����
		#define De_GprsHard_CallType_NoCall			2					//����ģʽ	
		/*---------------------------------ͨ��ģʽ------------------------------------*/
		#define De_GprsHard_Mod_Sound				0 					//����
		#define De_GprsHard_Mod_Data				1					//����
		#define De_GprsHard_Mod_Faxes				2					//����
		#define De_GprsHard_Mod_DataAndSound		3					//���ݸ�������������ģʽ
		#define De_GprsHard_Mod_SoundAndData		4					//�������ݽ��棬����ģʽ
		#define De_GprsHard_Mod_SoundFaxes			5					//�������洫�棬����ģʽ
		#define De_GprsHard_Mod_DataBySound			6					//���ݸ�������������ģʽ
		#define De_GprsHard_Mod_SoundByData			7					//�������ݽ��棬����ģʽ
		#define De_GprsHard_Mod_SoundByFaxes		8					//�������洫�棬����ģʽ
		#define De_GprsHard_Mod_Unkown				9					//δ֪
		/*-------------------------------TCP��ʼ��״̬---------------------------------*/
		#define De_GprsHard_InitTcp_Over			1					//���
		#define De_GprsHard_InitTcp_NoOver			2					//δ���
		/*---------------------------------��·��--------------------------------------*/
		#define De_GprsHard_Link0					0					//1����·
		#define De_GprsHard_Link1					1					//2����·
		#define De_GprsHard_Link2					2					//3����·
		#define De_GprsHard_Link3					3					//4����·
		#define De_GprsHard_NoLink					0xff				//����·�ر�
		/*----------------------------------��������-----------------------------------*/
		#define De_GprsHard_AgreePhone_Connect		1					//������������		
		#define De_GprsHard_AgreePhone_ConnectTxt	2					//�����������Ӳ������ı�
		#define De_GprsHard_AgreePhone_NoCarrier	3					//�޷���������
		#define De_GprsHard_AgreePhone_OK			4					//���ӳɹ�
		/*-------------------------------��·����--------------------------------------*/
		#define De_GprsHard_UDPTCP_UDP				1					//Э��ΪUDPЭ��
		#define De_GprsHard_UDPTCP_TCP				2					//Э��ΪTCPЭ��
		#define De_GprsHard_UDPTCP_NO				0xff				//��Э������
		/*-------------------------------��Ӫ������------------------------------------*/
		#define De_GprsHard_ChinaMobile				0					//�й��ƶ�
		#define De_GprsHard_Unicom					1  					//�й���ͨ
		#define De_GprsHard_Telecom					2					//�й�����
   		/*--------------------------------Ŀǰע��״̬---------------------------------*/
		#define De_GprsHard_Reg_State_NoReg			'0'					//û��ע��
		#define De_GprsHard_Reg_State_Reged			'1'					//�Ѿ�ע��
		#define De_GprsHard_Reg_State_NoRegIng		'2'					//û��ע�ᣬ������ҵ��
		#define De_GprsHard_Reg_State_NoRegJuge		'3'					//ע�ᱻ�ܾ�
		#define De_GprsHard_Reg_State_Unknown		'4'					//δ֪����
		#define De_GprsHard_Reg_State_RegedRove		'5'	   				//�Ѿ�ע�ᣬ������
		/*-----------------------------���е绰����״̬--------------------------------*/
		#define De_GprsHard_Connect_NoSound			1					//������ҵ��
		#define De_GprsHard_Connect_Busy			2					//���з�æ
		#define De_GprsHard_Connect_NoCarrier		3					//�޷���������
		#define De_GprsHard_Connect_OK				4					//���سɹ�
		/*------------------------------�ֻ�״̬��-------------------------------------*/
		#define De_GprsHard_State_0					'0'					//ME׼������
		#define De_GprsHard_State_1					'1'					//ME������
		#define De_GprsHard_State_2					'2'					//δ֪MEû׼����
		#define De_GprsHard_State_3					'3'					//����
		#define De_GprsHard_State_4					'4'					//���н�����
		#define De_GprsHard_State_5					'5'					//˯��
		/*------------------------------����Ϣ״̬------------------------------------*/
		#define De_GprsHard_New						1					//��������Ϣ��δ��
		#define De_GprsHard_Old 					2					//�Ѷ�����Ϣ
		#define De_GprsHard_Ide						3					//���ö���Ϣ
		/*------------------------------����Ϣ��ȡģʽ--------------------------------*/
		#define De_GprsHard_Txt_Pdu					1					//����ϢΪPDU��ʽ���ж�ȡ
		#define De_GprsHard_Txt_Text				2					//����Ϣ��TXT��ʽ���ж�ȡ
		/*------------------------------�ֻ��ź�ǿ��---------------------------------*/
		#define De_GpsHard_Sem_Size_0				0 					//�ֻ�û���ź�
		#define De_GpsHard_Sem_Size_1				1
		#define De_GpsHard_Sem_Size_2				2
		#define De_GpsHard_Sem_Size_3				3
		#define De_GpsHard_Sem_Size_4				4
		#define De_GpsHard_Sem_Size_5				5					//�ֻ��ź���ǿ
		/*------------------------------�ֻ�����ǿ��---------------------------------*/
		#define De_GpsHard_Volume_Size_0			0					//����
		#define De_GpsHard_Volume_Size_1			1
		#define De_GpsHard_Volume_Size_2			2
		#define De_GpsHard_Volume_Size_3			3
		#define De_GpsHard_Volume_Size_4			4
		#define De_GpsHard_Volume_Size_5			5
		/*------------------------------------��·���-------------------------------------*/
		#define De_GprsHard_Link_Open				0					//��·����
		#define De_GprsHard_Link_Close				1					//��·�ر�
		/*---------------------------------�绰״̬----------------------------------------*/
		#define De_GprsHard_Phone_State_Active			0					//Ŀǰ����
		#define De_GprsHard_Phone_State_Held			1					//����
		#define De_GprsHard_Phone_State_MeDialing		2					//������
		#define De_GprsHard_Phone_State_MeAlerting		3					//������ʾ���
		#define De_GprsHard_Phone_State_Incoming		4					//������
		#define De_GprsHard_Phone_State_Suc				5					//�ȴ�������	
		
		
			


/*==========================================Data Define==========================================================*/
	/*++++++++++++++++++++++++++++++++++++++��������ģ��������+++++++++++++++++++++++++++++++++++++++++++++*/
	typedef struct
	{	uint16 (*Init)(void *pFunc,void *Buf,uint16 SizeofBuf);									//��ʼ������ 
		uint16 (*Read)(uint16 Command,void *SendBuf,uint16 SizeofSendBuf,void *AgreeBuf,uint16 *SizeofAgreeBuf);
		uint8 *FacID;													//���ұ�ʶ����
	}st_Fun_GprsHard_Fac;					
	/*++++++++++++++++++++++++++++++++++++++���ؽ�����Ͷ���+++++++++++++++++++++++++++++++++++++++++++++++++*/
	typedef struct
	{	uint8 CallType;							//��������,�������߱���
		uint8 State;							//Ŀǰ״̬
		uint8 Mod;								//ģʽ
		uint8 VoiceType;						//��������
		uint8 *Phone;							//�绰����
	}st_GprsHard_CallState;
	typedef struct
	{	uint8 APN[32];				//ASC,�ԡ�/0'��Ϊ����
		uint8 Use[16];				//ASC,�ԡ�/0'��Ϊ����
		uint8 PassWord[8];			//ASC,�ԡ�/0'��Ϊ����	
	}st_Data_IPNet;					//TCP/IP����
	typedef struct
	{	uint32 IP;					//Ip��ַ
		uint16 Com;					//�˿ں�
	}st_Data_IPPar;					//UDP��TCP�Ĳ���

	typedef struct
	{	uint8 OpenType;				//������,��<��·����>
		uint8 fd;					//���򿪵���·��,��<��·��>
		st_Data_IPPar	*ptst_Data_IPPar;	//UDP��TCP�Ĳ��� 
	}st_Data_OpenUDPTCP;		 		//��·�򿪵�����
										
	typedef struct
	{	uint8 fd;														//GPRS��·�ţ���<��·��>
		uint16 DataLen;	  												//���ͳ���
		uint8 *Data;													//��������
	}st_GprsHard_NetData;
	//��ѯTCP/IP
	typedef struct
	{	uint8 State;													//״̬							
		uint32 IP;														//����IP��ַ
		uint32 GateWay;													//����
		uint32 FristDNS;												//��ѡDSN
		uint32 BackDNS;													//����DSN
	}st_HardWare_SeeTCPData; 											//����
	typedef struct
	{	uint8 State;
		uint8 *Buf;
	}st_GprsHard_GetMessage;											//��ȡ����Ϣ
	//�鿴���޿ɶ����ݰ�
	typedef struct
	{	uint32 NewDataNumber;
		uint32 SumDataNumber;
	}st_GprsHard_UDPDataFlag;

	typedef struct
	{	uint8 fd[De_GprsHard_MaxLink];								//��·ID��
		uint16 DataLen[De_GprsHard_MaxLink];						//�����������ݵĳ���
		uint8 *Data[De_GprsHard_MaxLink];							//��·
		uint8 NewLink;
	}st_GprsHard_ReadData;
	/*+++++++++++++++++++++++++++++++++++++++������������++++++++++++++++++++++++++++++++++++++++++++++++++*/
	typedef struct
	{	uint32 MaxDelay;							//���ȴ�ʱ��
		uint8 *OrderHead;							//ͷ������
		uint8 *OrderTail;							//β������
		uint8 *AgreeHead;							//ͷ������
		uint8 *AgreeTail;							//β������
		uint8 *AgreeTrueTail;						//β��������ȷ
		uint8 *AgreeErroTail;						//β�����ܴ���
	}st_GprsHard_Order_Cut;							//�������

/*=============================================���������������================================================
De_GprsHard_Com_CloseShow		�رջ���			
	SendBuf:NO	AgreeBuf:NO	
	SizeofSendBuf:0
	*SizeofAgreeBuf:0

De_GprsHard_GetChipID			��ȡ��������		
	SendBuf:NO	AgreeBuf:���� uint8 ����:���Ҵ��� ���ȣ���'/0'����
	SizeofSendBuf:0
	*SizeofAgreeBuf:ΪAgreeBuf���ݵĳ���

De_GprsHard_Com_GetModermState ��ȡ��������״̬	
	SendBuf:NO	AgreeBuf:���� uint8 ����:�ֻ�״̬�����:<�ֻ�״̬��> ����:1���ֽ�
	SizeofSendBuf:0
	*SizeofAgreeBuf:1

De_GprsHard_Com_GetModermCard	 ����λ��ѯ	
	SendBuf:NO	AgreeBuf:NO	
	SizeofSendBuf:0 
	*SizeofAgreeBuf:0

De_GprsHard_Com_GetCenterNumber	��ѯ�������ĺ���
	SendBuf:NO	AgreeBuf:���� uint8 ����:�������ĺ��룬Ӧȥ��"+86" ���ȣ���'/0'����
	SizeofSendBuf:0
	*SizeofAgreeBuf:AgreeBuf���ݵĳ���

De_GprsHard_Com_GetGetMessage	   ������Ϣ
	SendBuf:���� uint8 ����:����Ϣ��¼��,��1��ʼ  
	SizeofSendBuf:1	
	AgreeBuf:st_GprsHard_GetMessage 
	����:st_GprsHard_GetMessage.State	<����Ϣ״̬>
		 st_GprsHard_GetMessage.Buf		����Ϣ���ݣ��������Ϊunicoder
	*SizeofAgreeBuf:Buf����+1


De_GprsHard_Com_SetTxtOrPdu	   �����ı���ʽ
	SendBuf:���� uint8 ����:<����Ϣ��ȡģʽ>,���ȣ�1�ֽ�   
	AgreeBuf:NO
	SizeofSendBuf:1
	*SizeofAgreeBuf:0

De_GprsHard_Com_SeeTxtOrPdu	�鿴TEXT����PDU���ı���������
	SendBuf:NO  AgreeBuf:���� uint8 ����:����ϢĿǰ���ķ�ʽ,��<����Ϣ��ȡģʽ>.����:1�ֽ�
	SizeofSendBuf:0
	*SizeofAgreeBuf:1 


De_GprsHard_Com_MsgSend		���Ͷ���Ϣ
	SendBuf:���� uint8 ����:������������Ϣ�ĳ���,���ȣ�1�ֽ�  HEX
	AgreeBuf:NO
	SizeofSendBuf:0

De_GprsHard_Com_MsgSendData	���Ͷ���Ϣ����
	SendBuf:���� uint8 ����:�����͵Ķ�������,�������Ϊunicoder
	SizeofSendBuf:�����͵Ĵ�С
	*SizeofAgreeBuf:0

De_GprsHard_Com_SeeCarrier	��Ӫ������
	SendBuf:NO
    AgreeBuf:���� uint8 ����:��<��Ӫ������> ����:1�ֽ�
	SizeofSendBuf:0
	*SizeofAgreeBuf:1 
						
De_GprsHard_Com_SQ			�ź�ǿ��
	SendBuf:NO
	AgreeBuf:���� uint8 ����:��<�ֻ��ź�ǿ��> ����:1�ֽ�
	SizeofSendBuf:0
	*SizeofAgreeBuf:1 

De_GprsHard_Com_DelMsg 		ɾ������Ϣ
	SendBuf:���� uint8 ����:����Ϣ��¼�ţ����ȣ�1�ֽ�
	AgreeBuf:NO
	SizeofSendBuf:1
	*SizeofAgreeBuf:0

De_GprsHard_Com_Set_Mem		SMS�洢������
	SendBuf:NO	AgreeBuf:NO	SizeofSendBuf:0 *SizeofAgreeBuf:0
	
De_GprsHard_Com_MessSet		���ö���Ϣ
	SendBuf:NO	AgreeBuf:NO	SizeofSendBuf:0 *SizeofAgreeBuf:0

De_GprsHard_Com_Upadate		��������
	SendBuf:NO	AgreeBuf:NO	SizeofSendBuf:0 *SizeofAgreeBuf:0

De_GprsHard_Com_Reg 			����ע�����
	SendBuf:NO
	AgreeBuf:���� uint8 ����:����ע�����,�μ�<Ŀǰע��״̬>
	SizeofSendBuf:0
	*SizeofAgreeBuf:1

De_GprsHard_Com_CLIP			����������ʾ
	SendBuf:NO	AgreeBuf:NO	SizeofSendBuf:0 *SizeofAgreeBuf:0

De_GprsHard_Com_ATD			����绰
	SendBuf:����:uint8 ���ݣ���Ҫ����ĵ绰����,���ȣ���'/0'����
	AgreeBuf:NO	
	SizeofSendBuf:SendBuf�ĳ��� 
	*SizeofAgreeBuf:0

De_GprsHard_Com_Chup			�ҵ绰
	SendBuf:NO
	AgreeBuf:NO	
	SizeofSendBuf:0
	*SizeofAgreeBuf:0

De_GprsHard_Com_ATA			�ӵ绰
	SendBuf:NO	AgreeBuf:���ͣ�uint8 ����:��<��������>
	*SizeofAgreeBuf:1
	SizeofSendBuf:0

De_GprsHard_Com_IMEI			��ȡIMEI��
	SendBuf:NO SizeofSendBuf:0
	AgreeBuf:����:uint8 ����:15λ��Imei�� ��'/0'����
	*SizeofAgreeBuf: AgreeBuf�Ĵ�С
		 			
De_GprsHard_Com_CGDCONT 		����PDP������
	SendBuf:���ͣ�<st_Data_IPNet>
	SizeofSendBuf:��Ч
	*SizeofAgreeBuf:0
	AgreeBuf:NO

De_GprsHard_Com_Etcpip		PDP�����TCP/IP��ʼ��
	SendBuf:���ͣ�<st_Data_IPNet>
	SizeofSendBuf:��Ч
	*SizeofAgreeBuf:0
	AgreeBuf:NO	

De_GprsHard_Com_IOMODE		����TCP/IPģʽ
	SendBuf:NO	AgreeBuf:NO	SizeofSendBuf:0 *SizeofAgreeBuf:0
	
De_GprsHard_Com_IPOPENX		��TCP����UDP����·
	SendBuf:NO
	SizeofSendBuf:0
	*SizeofAgreeBuf:sizeof(st_GprsHard_UDPDataFlag)
	AgreeBuf:���ͣ�st_GprsHard_UDPDataFlag  ���ݣ����<st_GprsHard_UDPDataFlag>����

									


			
		












===============================================================================================================*/
















	
	
								


