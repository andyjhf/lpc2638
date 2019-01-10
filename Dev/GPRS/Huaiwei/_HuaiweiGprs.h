/*========================================include File===========================================================*/
	#include "..\..\..\APP\config.h"													//LPC2368�Ĵ�������
	#include "stdlib.h"		 															//����C���Կ⺯��														//����GPRS����ӿ�
#ifdef	De_HuaweiGprs_Compiler
	#include "..\GprsPublicDe.h"
	#include "..\..\..\miscellaneous\CodeTrans\AscNumber.h"	
#endif								//��������ת����Դ
/*========================================Define Data============================================================*/
	/*++++++++++++++++++++++++++++++++++++++++���ȴ�ʱ��+++++++++++++++++++++++++++++++++++++++++++++++++*/
#ifdef	De_HuaweiGprs_Compiler 
	#define De_MaxDelay_Huawei_CloseShow				200								//�رջ���
	#define De_MaxDelay_Huawei_GetChipID				200								//��ȡ��������
	#define De_MaxDelay_Huawei_GetModermState			200								//��ȡ��������״̬
	#define De_MaxDelay_Huawei_GetModermCard			200								//����λ��ѯ
	#define De_MaxDelay_Huawei_GetCenterNumber			200								//�������ĺ���
	#define De_MaxDelay_Huawei_GetMessage				400								//������Ϣ
	#define De_MaxDelay_Huawei_SetTxtOrPdu				200								//�����ı�ģʽ
	#define De_MaxDelay_Huawei_SeeTxtOrPdu				200								//��ѯ���ַ�ʽ
	#define De_MaxDelay_Huawei_MsgSend					200								//���Ͷ���Ϣ
	#define De_MaxDelay_Huawei_MsgSendData				12000							//���Ͷ���Ϣ����
	#define De_MaxDelay_Huawei_SeeCarrier				200								//�鿴��Ӫ��
	#define De_MaxDelay_Huawei_SQ 						200								//�鿴�ź�ǿ��
	#define De_MaxDelay_Huawei_DelMsg					400								//ɾ������Ϣ
	#define De_MaxDelay_Huawei_Set_Mem					200								//����MEM
	#define De_MaxDelay_Huawei_MessSet					200								//���ö���Ϣ
	#define De_MaxDelay_Huawei_Upadate					200								//��������
	#define De_MaxDelay_Huawei_Reg						200								//�鿴����ע�����	
	#define De_MaxDelay_Huawei_IMEI						200								//��ȡIMEI��
	#define De_MaxDelay_Huawei_Chup						200								//�һ�
	#define De_MaxDelay_Huawei_Sync						200								//����ʹ�ܵ�
	#define De_MaxDelay_Huawei_CGDCONT					600								//���總��
	#define De_MaxDelay_Huawei_Etcpip					12000							//����TCP/IP
	#define De_MaxDelay_Huawei_IOMODE					400								//����TCP/IPģʽ
	#define De_MaxDelay_Huawei_IPOPENX					8000							//����·
	#define De_MaxDelay_Huawei_IPSENDX					1000							//����TCP/IP���ݰ�
	#define De_MaxDelay_Huawei_SeeDataRead				200								//��ѯλ�����ݰ�
	#define De_MaxDelay_Huawei_LogOnTCPIP				2000								//ע��GPRS
	#define De_MaxDelay_Huawei_IPDR						400								//��ȡTCP/IP����
	#define De_MaxDelay_Huawei_IPCLOSE					3000							//�ر�TCP/IP��·
	#define De_MaxDelay_Huawei_CLIP						200								//����������ʾ
	#define De_MaxDelay_Huawei_ATD						2000							//��绰
	#define De_MaxDelay_Huawei_ATA						1000							//�ӵ绰
	#define De_MaxDelay_Huawei_JugeETCPIP				1000							//�鿴TCP/IP�Ƿ�����
	#define De_MaxDelay_Huawei_DNSR						2000							//��������
	#define De_MaxDelay_Huawei_IPR						200								//���ò����� 	
	#define De_MaxDelay_Huawei_CLCC						200								//��ȡͨ��״̬
	#define De_MaxDelay_Huawei_SEEIPCLOSE				1000							//�鿴��·�Ƿ�ر�
	#define De_MaxDelay_Huawei_PowerDown				10								//�ػ�
	#define De_MaxDelay_Huawei_SeeCGDCONT 				1000							//�鿴���總��
	#define De_MaxDelay_Huawei_SendExtension			2000							//�鿴���總��
	#define De_MaxDelay_Huawei_SetVolume				200								//��������
#endif
	/*++++++++++++++++++++++++++++++++++++++++Data Define++++++++++++++++++++++++++++++++++++++++++++++++*/
#ifdef	De_HuaweiGprs_Compiler 	
	typedef struct
	{	uint16 Command;										//����
		st_GprsHard_Order_Cut	CN_st_GprsHard_Order_Cut; 	//�������
		uint16 (*Operation )(void *SendBuf,uint16 SizeofSendBuf,void *AgreeBuf,uint16 *SizeofAgreeBuf,st_GprsHard_Order_Cut	*ptst_GprsHard_Order_Cut);
													//����������к���	
	}st_GprsHard_Order;	  							//�����
	typedef struct
	{	uint8 ResultV;			
		uint8 ContrV;
	}st_GprsHead_Result;
	typedef struct
	{	uint8 *Cut;
		uint8 Value;
	}st_GprsHead_Explain;
	typedef struct
	{ 	uint8 Start;
		uint8 End;
		uint8 ByteV;
	}st_Asc_GetData;
	

#endif
/*==========================================Function Define====================================================*/
#ifdef	De_HuaweiGprs_Compiler  	
	/*---------------------------------------�����������---------------------------------------------------*/
	static uint16 Init(void *pFunc,void *Buf,uint16 SizeofBuf);
	static uint16 Read(uint16 Command,void *SendBuf,uint16 SizeofSendBuf,void *AgreeBuf,uint16 *SizeofAgreeBuf);
	/*---------------------------------------���������Ӧ��ִ�к���-----------------------------------------*/
   	static uint16 Huawei_CloseShow(void *SendBuf,uint16 SizeofSendBuf,void *AgreeBuf,uint16 *SizeofAgreeBuf,st_GprsHard_Order_Cut	*ptst_GprsHard_Order_Cut);//�رջ���
	static uint16 GetChipID(void *SendBuf,uint16 SizeofSendBuf,void *AgreeBuf,uint16 *SizeofAgreeBuf,st_GprsHard_Order_Cut	*ptst_GprsHard_Order_Cut);//��ȡ��������
	static uint16 Huawei_GetModermState(void *SendBuf,uint16 SizeofSendBuf,void *AgreeBuf,uint16 *SizeofAgreeBuf,st_GprsHard_Order_Cut	*ptst_GprsHard_Order_Cut);//��ȡ��������״̬
	static uint16 Huawei_GetModermCard(void *SendBuf,uint16 SizeofSendBuf,void *AgreeBuf,uint16 *SizeofAgreeBuf,st_GprsHard_Order_Cut	*ptst_GprsHard_Order_Cut);//����λ��ѯ
	static uint16 Huawei_GetCenterNumber(void *SendBuf,uint16 SizeofSendBuf,void *AgreeBuf,uint16 *SizeofAgreeBuf,st_GprsHard_Order_Cut	*ptst_GprsHard_Order_Cut);//�������ĺ���
	static uint16 Huawei_GetMessage(void *SendBuf,uint16 SizeofSendBuf,void *AgreeBuf,uint16 *SizeofAgreeBuf,st_GprsHard_Order_Cut	*ptst_GprsHard_Order_Cut);//������Ϣ
	static uint16 Huawei_SetTxtOrPdu(void *SendBuf,uint16 SizeofSendBuf,void *AgreeBuf,uint16 *SizeofAgreeBuf,st_GprsHard_Order_Cut	*ptst_GprsHard_Order_Cut);//�����ı�ģʽ
	static uint16 Huawei_SeeTxtOrPdu(void *SendBuf,uint16 SizeofSendBuf,void *AgreeBuf,uint16 *SizeofAgreeBuf,st_GprsHard_Order_Cut	*ptst_GprsHard_Order_Cut);//��ѯ���ַ�ʽ
	static uint16 Huawei_MsgSend(void *SendBuf,uint16 SizeofSendBuf,void *AgreeBuf,uint16 *SizeofAgreeBuf,st_GprsHard_Order_Cut	*ptst_GprsHard_Order_Cut);//���Ͷ���Ϣ
	static uint16 Huawei_MsgSendData(void *SendBuf,uint16 SizeofSendBuf,void *AgreeBuf,uint16 *SizeofAgreeBuf,st_GprsHard_Order_Cut	*ptst_GprsHard_Order_Cut);//���Ͷ���Ϣ����
	static uint16 Huawei_SeeCarrier(void *SendBuf,uint16 SizeofSendBuf,void *AgreeBuf,uint16 *SizeofAgreeBuf,st_GprsHard_Order_Cut	*ptst_GprsHard_Order_Cut);//�鿴��Ӫ��
	static uint16 Huawei_SQ(void *SendBuf,uint16 SizeofSendBuf,void *AgreeBuf,uint16 *SizeofAgreeBuf,st_GprsHard_Order_Cut	*ptst_GprsHard_Order_Cut);//�鿴�ź�ǿ��
	static uint16 Huawei_DelMsg(void *SendBuf,uint16 SizeofSendBuf,void *AgreeBuf,uint16 *SizeofAgreeBuf,st_GprsHard_Order_Cut	*ptst_GprsHard_Order_Cut);//ɾ������Ϣ
	static uint16 Huawei_Set_Mem(void *SendBuf,uint16 SizeofSendBuf,void *AgreeBuf,uint16 *SizeofAgreeBuf,st_GprsHard_Order_Cut	*ptst_GprsHard_Order_Cut);//����MEM
	static uint16 Huawei_MessSet(void *SendBuf,uint16 SizeofSendBuf,void *AgreeBuf,uint16 *SizeofAgreeBuf,st_GprsHard_Order_Cut	*ptst_GprsHard_Order_Cut);//���ö���Ϣ
	static uint16 Huawei_Upadate(void *SendBuf,uint16 SizeofSendBuf,void *AgreeBuf,uint16 *SizeofAgreeBuf,st_GprsHard_Order_Cut	*ptst_GprsHard_Order_Cut);//��������
	static uint16 Huawei_Reg(void *SendBuf,uint16 SizeofSendBuf,void *AgreeBuf,uint16 *SizeofAgreeBuf,st_GprsHard_Order_Cut	*ptst_GprsHard_Order_Cut);//�鿴����ע�����	
	static uint16 Huawei_IMEI(void *SendBuf,uint16 SizeofSendBuf,void *AgreeBuf,uint16 *SizeofAgreeBuf,st_GprsHard_Order_Cut	*ptst_GprsHard_Order_Cut);//��ȡIMEI��
	static uint16 Huawei_Chup(void *SendBuf,uint16 SizeofSendBuf,void *AgreeBuf,uint16 *SizeofAgreeBuf,st_GprsHard_Order_Cut	*ptst_GprsHard_Order_Cut);//�һ�
	static uint16 Huawei_Sync(void *SendBuf,uint16 SizeofSendBuf,void *AgreeBuf,uint16 *SizeofAgreeBuf,st_GprsHard_Order_Cut	*ptst_GprsHard_Order_Cut);//����ʹ�ܵ�
	static uint16 Huawei_CGDCONT(void *SendBuf,uint16 SizeofSendBuf,void *AgreeBuf,uint16 *SizeofAgreeBuf,st_GprsHard_Order_Cut	*ptst_GprsHard_Order_Cut);//���總��
	static uint16 Huawei_Etcpip(void *SendBuf,uint16 SizeofSendBuf,void *AgreeBuf,uint16 *SizeofAgreeBuf,st_GprsHard_Order_Cut	*ptst_GprsHard_Order_Cut);//����TCP/IP
	static uint16 Huawei_IOMODE(void *SendBuf,uint16 SizeofSendBuf,void *AgreeBuf,uint16 *SizeofAgreeBuf,st_GprsHard_Order_Cut	*ptst_GprsHard_Order_Cut);//����TCP/IPģʽ
	static uint16 Huawei_IPOPENX(void *SendBuf,uint16 SizeofSendBuf,void *AgreeBuf,uint16 *SizeofAgreeBuf,st_GprsHard_Order_Cut	*ptst_GprsHard_Order_Cut);//����·
	static uint16 Huawei_IPSENDX(void *SendBuf,uint16 SizeofSendBuf,void *AgreeBuf,uint16 *SizeofAgreeBuf,st_GprsHard_Order_Cut	*ptst_GprsHard_Order_Cut);//����TCP/IP���ݰ�
	static uint16 Huawei_SeeDataRead(void *SendBuf,uint16 SizeofSendBuf,void *AgreeBuf,uint16 *SizeofAgreeBuf,st_GprsHard_Order_Cut	*ptst_GprsHard_Order_Cut);//��ѯλ�����ݰ�
	static uint16 Huawei_LogOnTCPIP(void *SendBuf,uint16 SizeofSendBuf,void *AgreeBuf,uint16 *SizeofAgreeBuf,st_GprsHard_Order_Cut	*ptst_GprsHard_Order_Cut);//ע��GPRS
	static uint16 Huawei_IPDR(void *SendBuf,uint16 SizeofSendBuf,void *AgreeBuf,uint16 *SizeofAgreeBuf,st_GprsHard_Order_Cut	*ptst_GprsHard_Order_Cut);//��ȡTCP/IP����
	static uint16 Huawei_IPCLOSE(void *SendBuf,uint16 SizeofSendBuf,void *AgreeBuf,uint16 *SizeofAgreeBuf,st_GprsHard_Order_Cut	*ptst_GprsHard_Order_Cut);//�ر�TCP/IP��·
	static uint16 Huawei_CLIP(void *SendBuf,uint16 SizeofSendBuf,void *AgreeBuf,uint16 *SizeofAgreeBuf,st_GprsHard_Order_Cut	*ptst_GprsHard_Order_Cut);//����������ʾ
	static uint16 Huawei_ATD(void *SendBuf,uint16 SizeofSendBuf,void *AgreeBuf,uint16 *SizeofAgreeBuf,st_GprsHard_Order_Cut	*ptst_GprsHard_Order_Cut);//��绰
	static uint16 Huawei_ATA(void *SendBuf,uint16 SizeofSendBuf,void *AgreeBuf,uint16 *SizeofAgreeBuf,st_GprsHard_Order_Cut	*ptst_GprsHard_Order_Cut);//�ӵ绰
	static uint16 Huawei_JugeETCPIP(void *SendBuf,uint16 SizeofSendBuf,void *AgreeBuf,uint16 *SizeofAgreeBuf,st_GprsHard_Order_Cut	*ptst_GprsHard_Order_Cut);//�鿴TCP/IP�Ƿ�����
	static uint16 Huawei_DNSR(void *SendBuf,uint16 SizeofSendBuf,void *AgreeBuf,uint16 *SizeofAgreeBuf,st_GprsHard_Order_Cut	*ptst_GprsHard_Order_Cut);//��������
	static uint16 Huawei_IPR(void *SendBuf,uint16 SizeofSendBuf,void *AgreeBuf,uint16 *SizeofAgreeBuf,st_GprsHard_Order_Cut	*ptst_GprsHard_Order_Cut);//���ò����� 	
	static uint16 Huawei_CLCC(void *SendBuf,uint16 SizeofSendBuf,void *AgreeBuf,uint16 *SizeofAgreeBuf,st_GprsHard_Order_Cut	*ptst_GprsHard_Order_Cut);//��ȡͨ��״̬
	static uint16 Huawei_SEEIPCLOSE(void *SendBuf,uint16 SizeofSendBuf,void *AgreeBuf,uint16 *SizeofAgreeBuf,st_GprsHard_Order_Cut	*ptst_GprsHard_Order_Cut);//�鿴��·�Ƿ�ر�
	static uint16 Huawei_PowerDown(void *SendBuf,uint16 SizeofSendBuf,void *AgreeBuf,uint16 *SizeofAgreeBuf,st_GprsHard_Order_Cut	*ptst_GprsHard_Order_Cut);
	static uint16 Huawei_SeeCGDCONT(void *SendBuf,uint16 SizeofSendBuf,void *AgreeBuf,uint16 *SizeofAgreeBuf,st_GprsHard_Order_Cut	*ptst_GprsHard_Order_Cut);
	static uint16 Huawei_SendExtension(void *SendBuf,uint16 SizeofSendBuf,void *AgreeBuf,uint16 *SizeofAgreeBuf,st_GprsHard_Order_Cut	*ptst_GprsHard_Order_Cut);
	static uint16 Huawei_SetVolume(void *SendBuf,uint16 SizeofSendBuf,void *AgreeBuf,uint16 *SizeofAgreeBuf,st_GprsHard_Order_Cut	*ptst_GprsHard_Order_Cut);
	/*-----------------------------------------------------------------------------------------------------*/
	static void ClearNoDisplay(uint8 *Buf);
	static	uint8 *SeekChar(uint8 *Buf,uint8 CharV,uint16 SizeofBuf,uint8 Number);
#endif 
/*============================================Public Ram=======================================================*/
#ifdef	De_HuaweiGprs_Compiler	
	/*===========================================�������===================================================*/
	const st_Fun_GprsHard_Fac	CN_Huawei_st_Fun_GprsHard_Fac={Init,Read,"HUAWEI"};
	/*==========================================��Ϊ����ṹ��==============================================*/
	const st_GprsHard_Order	CN_HuaWei_st_GprsHard_Order[]=					//��Ϊ����ļ���
	{	{	De_GprsHard_Com_CloseShow,{De_MaxDelay_Huawei_CloseShow,"ATE0","\r\n","","\r\n","OK",""},Huawei_CloseShow}, //�رջ���
		{	De_GprsHard_Com_GetChipID,{De_MaxDelay_Huawei_GetChipID,"AT+GMI","\r\n","","\r\n","OK",""},GetChipID},		 //��ȡ��������
		{	De_GprsHard_Com_GetModermState,{De_MaxDelay_Huawei_GetModermState,"AT+CPAS","\r\n","+CPAS:","\r\n","OK","ERROR"},Huawei_GetModermState},//��ȡ��������״̬
		{	De_GprsHard_Com_GetModermCard,{De_MaxDelay_Huawei_GetModermCard,"AT%TSIM","\r\n","%TSIM","\r\n","OK","ERROR"},Huawei_GetModermCard}, //����λ��ѯ
		{	De_GprsHard_Com_GetCenterNumber,{De_MaxDelay_Huawei_GetCenterNumber,"AT+CSCA?","\r\n","+CSCA:","\r\n","OK","ERROR"},Huawei_GetCenterNumber},	//�������ĺ���
		{	De_GprsHard_Com_GetMessage,{De_MaxDelay_Huawei_GetMessage,"AT+CMGR=","\r\n","+CMGR:","\r\n","OK","ERROR"},Huawei_GetMessage},	//������Ϣ					
	  	{	De_GprsHard_Com_SetTxtOrPdu,{De_MaxDelay_Huawei_SetTxtOrPdu,"AT+CMGF=","\r\n","","\r\n","OK",""},Huawei_SetTxtOrPdu},				//�����ı�ģʽ
		{	De_GprsHard_Com_SeeTxtOrPdu,{De_MaxDelay_Huawei_SeeTxtOrPdu,"AT+CMGF?","\r\n","+CMGF:","\r\n","OK",""},Huawei_SeeTxtOrPdu},			//��ѯ�����ı�
		{	De_GprsHard_Com_MsgSend,{De_MaxDelay_Huawei_MsgSend,"AT+CMGS=","\r\n","","",">",""},Huawei_MsgSend},							//���Ͷ���Ϣ
		{	De_GprsHard_Com_MsgSendData,{De_MaxDelay_Huawei_MsgSendData,"","","+CMGS:","\r\n","OK","ERROR"},Huawei_MsgSendData},				//���Ͷ���Ϣ����	
		{	De_GprsHard_Com_SeeCarrier,{De_MaxDelay_Huawei_SeeCarrier,"AT+CIMI","\r\n","","\r\n","OK","ERROR"},Huawei_SeeCarrier},//�鿴��Ӫ��
		{	De_GprsHard_Com_SQ,{De_MaxDelay_Huawei_SQ,"AT+CSQ","\r\n","+CSQ:","\r\n","OK","ERROR"},Huawei_SQ},		//�鿴�ź�ǿ��
		{	De_GprsHard_Com_DelMsg,{De_MaxDelay_Huawei_DelMsg,"AT+CMGD=","\r\n","","\r\n","OK","ERROR"},Huawei_DelMsg},	//ɾ������Ϣ
		{	De_GprsHard_Com_Set_Mem,{De_MaxDelay_Huawei_Set_Mem,"AT+CPMS=","\r\n","+CPMS:","\r\n","OK","ERROR"},Huawei_Set_Mem},//����MEM
		{	De_GprsHard_Com_MessSet,{De_MaxDelay_Huawei_MessSet,"at+cnmi=","\r\n","","\r\n","OK","ERROR"},Huawei_MessSet},//���ö���Ϣ
		{	De_GprsHard_Com_Upadate,{De_MaxDelay_Huawei_Upadate,"AT&W","\r\n","","\r\n","OK","ERROR"},Huawei_Upadate},//��������
		{	De_GprsHard_Com_Reg,{De_MaxDelay_Huawei_Reg,"AT+CREG?","\r\n","+CREG:","\r\n","OK","ERROR"},Huawei_Reg},//�鿴����ע�����
		{	De_GprsHard_Com_CLIP,{De_MaxDelay_Huawei_CLIP,"AT+CLIP=1","\r\n","","\r\n","OK",""},Huawei_CLIP},//����������ʾ
		{	De_GprsHard_Com_ATD,{De_MaxDelay_Huawei_ATD,"ATD","\r\n","","\r\n","",""},Huawei_ATD},//ATD����
		{	De_GprsHard_Com_Chup,{De_MaxDelay_Huawei_Chup,"ATH0","\r\n","","\r\n","OK","ERROR"},Huawei_Chup},//�һ�
		{	De_GprsHard_Com_ATA,{De_MaxDelay_Huawei_ATA,"ATA","\r\n","","\r\n","","ERROR"},Huawei_ATA},	//�ӵ绰
		{	De_GprsHard_Com_IMEI,{De_MaxDelay_Huawei_IMEI,"ATD*#06#","\r\n","","\r\n","OK",""},Huawei_IMEI},	//�ӵ绰
		{	De_GprsHard_Com_Sync,{De_MaxDelay_Huawei_Sync,"","","","","",""},NULL},//����ʹ�ܵ�
		{	De_GprsHard_Com_CGDCONT,{De_MaxDelay_Huawei_CGDCONT,"AT+CGDCONT=1,\"IP\",","\r\n","","\r\n","OK","ERROR"},Huawei_CGDCONT},//���總��		
		{	De_GprsHard_Com_Etcpip,{De_MaxDelay_Huawei_Etcpip,"at%etcpip=","\r\n","","\r\n","OK","ERROR"},Huawei_Etcpip},//����TCP/IP
	 	{	De_GprsHard_Com_IOMODE,{De_MaxDelay_Huawei_IOMODE,"AT%IOMODE=1,2,0","\r\n","","\r\n","OK","ERROR"},Huawei_IOMODE},//����TCP/IPģʽ
	  	{	De_GprsHard_Com_IPOPENX,{De_MaxDelay_Huawei_IPOPENX,"AT%IPOPENX=","\r\n","","\r\n","CONNECT","ERROR"},Huawei_IPOPENX},//����·
	 	{	De_GprsHard_Com_IPSENDX,{De_MaxDelay_Huawei_IPSENDX,"AT%IPSENDX=","\r\n","","\r\n","OK","ERROR"},Huawei_IPSENDX},//����TCP/IP���ݰ�
	   	{	De_GprsHard_Com_SeeDataRead,{De_MaxDelay_Huawei_SeeDataRead,"AT%IPDQ","\r\n","%IPDQ:","\r\n","OK","ERROR"},Huawei_SeeDataRead},//��ѯ���ݰ�
		{	De_GprsHard_Com_IPDR,{De_MaxDelay_Huawei_IPDR,"AT%IPDR","\r\n","%IPDR:","\r\n","OK","ERROR"},Huawei_IPDR},	 //��ȡTCP/IP����
	 	{	De_GprsHard_Com_IPCLOSE,{De_MaxDelay_Huawei_IPCLOSE,"AT%IPCLOSE=","\r\n","%IPCLOSE:","\r\n","OK","ERROR"},Huawei_IPCLOSE},//�ر�TCP/IP��·
		{	De_GprsHard_Com_LogOnTCPIP,{De_MaxDelay_Huawei_LogOnTCPIP,"AT%IPCLOSE=5","\r\n","%IPCLOSE:","\r\n","OK","ERROR"},Huawei_LogOnTCPIP},//GPRS����ע��
		{	De_GprsHard_Com_JugeETCPIP,{De_MaxDelay_Huawei_JugeETCPIP,"AT%ETCPIP?","\r\n","%ETCPIP:","\r\n","OK",""},Huawei_JugeETCPIP},//��ѯTCP/IP
		{	De_GprsHard_Com_DNSR,{De_MaxDelay_Huawei_DNSR,"AT%DNSR=","\r\n","%DNSR:","\r\n","OK","ERROR"},Huawei_DNSR},		//��������
		{	De_GprsHard_Com_IPR,{De_MaxDelay_Huawei_IPR,"AT+IPR=","\r\n","","\r\n","OK","ERROR"},Huawei_IPR},			//���ò�����
		{	De_GprsHard_Com_CLCC,{De_MaxDelay_Huawei_CLCC,"AT+CLCC","\r\n","+CLCC:","\r\n","OK","ERROR"},Huawei_CLCC},//��ȡͨ��״̬
		{	De_GprsHard_Com_SEEIPCLOSE,{De_MaxDelay_Huawei_SEEIPCLOSE,"AT%IPCLOSE?","\r\n","%IPCLOSE:","\r\n","OK","ERROR"},Huawei_SEEIPCLOSE},//�鿴��·�Ƿ�ر�	
		{	De_GprsHard_Com_PowerDown,{De_MaxDelay_Huawei_PowerDown,"AT%MSO","\r\n","","","OK","ERROR"},Huawei_PowerDown}, 						//�ػ�
		{	De_GprsHard_Com_SeeCGDCONT,{De_MaxDelay_Huawei_SeeCGDCONT,"AT+CGDCONT?","\r\n","+CGDCONT:","\r\n","OK","ERROR"},Huawei_SeeCGDCONT}, //�鿴�����Ƿ���
		{	De_GprsHard_Com_SendExtension,{De_MaxDelay_Huawei_SendExtension,"AT+VTS=","\r\n","","\r\n","",""},Huawei_SendExtension},		//����ֻ�
		{	De_GprsHard_Com_SetVolume,{De_MaxDelay_Huawei_SetVolume,"AT%NFV=","\r\n","","\r\n","OK","ERROR"},Huawei_SetVolume}						 //��������
	};
	const st_GprsHead_Result	CN_Huawei_st_GprsHead_Result[]=	 	//	
	{	{'0',De_GprsHard_State_0},
		{'1',De_GprsHard_State_1},
		{'2',De_GprsHard_State_2},
		{'3',De_GprsHard_State_3},
		{'4',De_GprsHard_State_4},
		{'5',De_GprsHard_State_5}
	};
	const st_GprsHead_Result	CN_Huawei_ReadMessage[]=				//����Ϣ״̬	
	{	{'0',De_GprsHard_New},
		{'1',De_GprsHard_Old},
		{'2',De_GprsHard_Old},
		{'3',De_GprsHard_Ide}
	};
	const st_GprsHead_Result	CN_Huawei_SetMessage[]=				//PDU������TXT�����
	{	{'0',De_GprsHard_Txt_Pdu},
		{'1',De_GprsHard_Txt_Text}
	};
	const st_GprsHead_Explain	CN_Huawei_Carrier[]= 					//��Ӫ��
	{ 	{"46002",De_GprsHard_ChinaMobile},
		{"46000",De_GprsHard_ChinaMobile}
	};
	const st_GprsHead_Result	CN_Reg_State[]=	  						//ע��״̬
	{	{'0',De_GprsHard_Reg_State_NoReg},	   							//û��ע��
		{'1',De_GprsHard_Reg_State_Reged},	   							//�Ѿ�ע��
		{'2',De_GprsHard_Reg_State_NoRegIng},							//û��ע�ᣬ������ҵ��
		{'3',De_GprsHard_Reg_State_NoRegJuge},							//ע�ᱻ�ܾ�
		{'4',De_GprsHard_Reg_State_Unknown},   							//δ֪����
		{'5',De_GprsHard_Reg_State_RegedRove}  							//�Ѿ�ע�ᣬ������
	};
	const st_GprsHead_Explain	CN_Ba_CallRes[]=
	{	{"CONNECT",De_GprsHard_Connect_NoSound},						//������ҵ��
		{"BUSY",De_GprsHard_Connect_Busy},								//���з�æ
		{"NO CARRIER",De_GprsHard_Connect_NoCarrier},	    			//�޷���������
		{"OK",De_GprsHard_Connect_OK}					  				//���سɹ�
	};
	const st_GprsHead_Explain	CN_Ba_AgreePhone[]=
	{	{"CONNECT",De_GprsHard_AgreePhone_Connect},						//������������
		{"CONNECT",De_GprsHard_AgreePhone_ConnectTxt},					//�����������Ӳ������ı�
		{"NO CARRIER",De_GprsHard_AgreePhone_NoCarrier},				//�޷���������
		{"OK",De_GprsHard_Connect_OK}									//���ӳɹ�
	};
	const st_GprsHead_Explain	CN_Ba_UDPTCP[]=							//��·������
	{	{"\"TCP\"",De_GprsHard_UDPTCP_TCP},								//TCP��·
		{"\"UDP\"",De_GprsHard_UDPTCP_UDP}								//UDP��·
	};
	const st_GprsHead_Result	CN_Huawei_Link[]=	 			//��·����
	{ 	{De_GprsHard_Link0,'1'},							   	//1����·
		{De_GprsHard_Link1,'2'},								//2����·
		{De_GprsHard_Link2,'3'}								//3����·
	};
	const st_GprsHead_Result	CN_Huawei_TCPInitState[]=  		//TCP��ʼ�����
	{	{De_GprsHard_InitTcp_NoOver,'0'},						//û�г�ʼ��
		{De_GprsHard_InitTcp_Over,'1'}							//�Ѿ���ʼ��
	};

	const st_GprsHead_Result	CN_Huawei_CallTyte[]=  			//�绰�������		
	{	{De_GprsHard_CallType_Initiative,'0'},					//����ģʽ����
		{De_GprsHard_CallType_Passive,'1'}						//����ģʽ����
	};
	const st_GprsHead_Result	CN_Huawei_CallState[]= 			//�绰����״̬
	{ 	{De_GprsHard_Phone_State_Active,'0'},
		{De_GprsHard_Phone_State_Held,'1'},
		{De_GprsHard_Phone_State_MeDialing,'2'},
		{De_GprsHard_Phone_State_MeAlerting,'3'},
		{De_GprsHard_Phone_State_Incoming,'4'},
		{De_GprsHard_Phone_State_Suc,'5'}
	};



	const st_GprsHead_Result	CN_Huawei_Mod[]=				//ͨ����ʽ
	{	{De_GprsHard_Mod_Sound,'0'},						   	//����
		{De_GprsHard_Mod_Data,'1'},								//����
		{De_GprsHard_Mod_Faxes,'2'},							//����
		{De_GprsHard_Mod_DataAndSound,'3'},						//���ݸ�������������ģʽ
		{De_GprsHard_Mod_SoundAndData,'4'},						//�������ݽ��棬����ģʽ
		{De_GprsHard_Mod_SoundFaxes,'5'},						//�������洫�棬����ģʽ
		{De_GprsHard_Mod_DataBySound,'6'},						//���ݸ�������������ģʽ
		{De_GprsHard_Mod_SoundByData,'7'},						//�������ݽ��棬����ģʽ
		{De_GprsHard_Mod_SoundByFaxes,'8'},						//�������洫�棬����ģʽ
		{De_GprsHard_Mod_Unkown,'9'}							//δ֪
	};						//��������ģʽ//ͨ������

	const st_GprsHead_Result	CN_Huawei_PeperNumber[]=
	{	{De_GprsHard_Call_Peper,'0'},  							//����ͨ��
		{De_GprsHard_Call_SumPeper,'1'}						   	//����ͨ��
	};

	const st_Asc_GetData	CN_Ba_st_Asc_GetData[]=		  		//�ź�ǿ�Ƚ���
	{ 	{0,0,De_GpsHard_Sem_Size_0},   							//
		{1,6,De_GpsHard_Sem_Size_1},
		{7,20,De_GpsHard_Sem_Size_2},
		{21,25,De_GpsHard_Sem_Size_3},
		{26,30,De_GpsHard_Sem_Size_4},
		{31,31,De_GpsHard_Sem_Size_5}
	};
	const uint8 CN_LinkNum[]= 									//�����ӵ���·��
	{	'1','2','3'
	};
	const st_GprsHead_Result	CN_Huawei_LinkOper[]=
	{	{De_GprsHard_Link_Open,'1'},				//��·����
		{De_GprsHard_Link_Close,'0'}				//��·�ر�
	};
	/*------------------------------------------��̬RAM����----------------------------------------------------*/
	uint8 *X_BUF;
//	uint8 X_BUF[1536];
	uint16 SizeofX_BUF;
	uint16 (*ModermCom)(uint8 *SendBuf,uint8 *AgreeBuf,uint16 SizeofAgreeBuf,st_GprsHard_Order_Cut	*ptst_GprsHard_Order_Cut);		
#else
	extern const st_Fun_GprsHard_Fac	CN_Huawei_st_Fun_GprsHard_Fac;
#endif





