/*=========================================Include File=========================================================*/
	#include "..\..\..\APP\config.h"												//LPC2368�Ĵ�������
 	#include "stdlib.h"		
	#ifdef De_Tz_Send_Compiler														//C��������
		#include "..\..\..\miscellaneous\CodeTrans\AscNumber.h"						//��������ת����Դ
		#include "..\..\..\miscellaneous\Date\Date.h"								//����������Դ
		#include "..\..\AgreementCom.h"												//Э������
		#include "Tz_Send_Pubi.c"
	#endif
/*==========================================Define Data=======================================================*/
	#define De_Erro_Tz_Send_NoID								1		//��֧�ִ�Э��
	#define De_Suc_Tz_Send										0		//�ɹ�
/*==========================================Data Define=======================================================*/
	typedef struct
	{	uint16 (*Write)(uint8 *Buf,void *InputBuf,uint16 *ReDataLen,uint16 ID);
	}st_Fun_Tz_Send;
#ifdef De_Tz_Send_Compiler
	typedef struct
	{	uint16 ID;
		void (*Read)(uint8 *OutBuf,void *InputBuf,uint16 *ReDataLen);
	}st_Tz_Send_FunOper;
#endif
/*=========================================static Function======================================================*/
#ifdef De_Tz_Send_Compiler	
	static uint16 Explain(uint8 *Buf,void *InputBuf,uint16 *ReDataLen,uint16 ID);
	
	/*----------------------------------------------����Э��----------------------------------------*/
	static void Explain_GetSeverComPar(uint8 *OutBuf,void *InputBuf,uint16 *ReDataLen);  //��ȡͨѶ����ָ��
	//��¼ָ��,���ȡͨѶ����ָ��һ��
	//����ָ��,���ȡͨѶ����ָ��һ��
	//�ػ�ָ��,���ȡͨѶ����ָ��һ��
	static void Explain_Answer(uint8 *OutBuf,void *InputBuf,uint16 *ReDataLen);			//��λ�ն�����Ӧ��
	//�ϴ�λ����Ϣ,���ȡͨѶ����ָ��һ��
	static void Explain_Menum(uint8 *OutBuf,void *InputBuf,uint16 *ReDataLen);	  //�ϴ��˵���Ϣ
	static void Explain_TxtMenum(uint8 *OutBuf,void *InputBuf,uint16 *ReDataLen);//�ϴ����˵��ķ�����Ϣ
	static void Explain_LookPar(uint8 *OutBuf,void *InputBuf,uint16 *ReDataLen);  //��ѯ��λ�ն˲���
	static void Explain_UpdateSoftWare(uint8 *OutBuf,void *InputBuf,uint16 *ReDataLen);//�ϴ��������״̬
	static void Explain_Waring(uint8 *OutBuf,void *InputBuf,uint16 *ReDataLen);//�ϴ�����״̬
	/*---------------------------------------------������չЭ��-----------------------------------------------------*/
	static void Explain_UploaderJpg1(uint8 *OutBuf,void *InputBuf,uint16 *ReDataLen);
	static void Explain_UploaderJpg2(uint8 *OutBuf,void *InputBuf,uint16 *ReDataLen);
	static void Explain_UploaderPar(uint8 *OutBuf,void *InputBuf,uint16 *ReDataLen);
	static void Explain_UploaderLog(uint8 *OutBuf,void *InputBuf,uint16 *ReDataLen);
	static void Explain_UpLoaderWarning(uint8 *OutBuf,void *InputBuf,uint16 *ReDataLen);

	/*-----------------------------------------------����Э��ר��---------------------------------------------------*/
	static void Explain_OutRoadMap(uint8 *OutBuf,void *InputBuf,uint16 *ReDataLen);
	static void Explain_UpLoaderReduce(uint8 *OutBuf,void *InputBuf,uint16 *ReDataLen);
	static void Explain_UpLoaderDriver(uint8 *OutBuf,void *InputBuf,uint16 *ReDataLen);
	static void Explain_UpLoaderHandMess(uint8 *OutBuf,void *InputBuf,uint16 *ReDataLen);
	static void Explain_NoSem(uint8 *OutBuf,void *InputBuf,uint16 *ReDataLen);
		
	/*---------------------------------------------���⳵Э��-------------------------------------------------------*/ 
	static void Explain_UpLoaderFrom(uint8 *OutBuf,void *InputBuf,uint16 *ReDataLen);
	static void Explain_OverFromErro(uint8 *OutBuf,void *InputBuf,uint16 *ReDataLen);
	static void Explain_PriceData(uint8 *OutBuf,void *InputBuf,uint16 *ReDataLen);
#endif


/*===========================================Public Ram========================================================*/
#ifdef De_Tz_Send_Compiler
	static const st_Tz_Send_FunOper	CN_Ba_st_Tz_Send_FunOper[]=
	{
	/*----------------------------------------------����Э��-------------------------------------------------*/	
		{	De_Dev_Order_GetSeverComPar,Explain_GetSeverComPar},//��ȡ������ͨѶ����
		{	De_Dev_Order_Login,Explain_GetSeverComPar},//��λ�ն˵�¼
		{	De_Dev_Order_Sleep,Explain_GetSeverComPar},//��λ�ն�����
		{ 	De_Dev_Order_CloseModerm,Explain_GetSeverComPar},//��λ�ն˹ػ�
		{ 	De_Dev_Order_Answer,Explain_Answer},//��λ�ն�����Ӧ��
		{	De_Dev_Order_Orientation,Explain_GetSeverComPar},//�ϴ�λ����Ϣ
		{ 	De_Dev_Order_Menum,Explain_Menum},//�ϴ��˵���Ϣ
		{ 	De_Dev_Order_TxtMenum,Explain_TxtMenum},//�ϴ����˵��ķ�����Ϣ
		{ 	De_Dev_Order_LookPar,Explain_LookPar},//�ϴ���λ�ն˲���
		{ 	De_Dev_Order_UpdateSoftWare,Explain_UpdateSoftWare},//�ϴ��������״̬
		{ 	De_Dev_Order_Waring,Explain_Waring},//�ϴ�����״̬
	/*---------------------------------------------������չЭ��---------------------------------------------*/
		{ 	De_Dev_Order_UploaderJpg1,Explain_UploaderJpg1},//�ϴ���Ƭһ
		{ 	De_Dev_Order_UploaderJpg2,Explain_UploaderJpg2},//�ϴ���Ƭ��
//		{ 	De_Dev_Order_TabelList,Explain_TabelList},//��
		{ 	De_Dev_Order_UploaderPar,Explain_UploaderPar},//�ϴ�����
		{ 	De_Dev_Order_UploaderLog,Explain_NoSem},//�ϴ���־�ļ�
		{ 	De_Dev_Order_UpLoaderWarning,Explain_UpLoaderWarning},//�ϴ���������
	/*--------------------------------------------����Э��ר��----------------------------------------------*/
		{ 	De_Dev_Order_OutRoadMap,Explain_OutRoadMap},//�������򱨾�
		{ 	De_Dev_Order_UpLoaderReduce,Explain_UpLoaderReduce},//�ϴ�ѹ������
		{ 	De_Dev_Order_UpLoaderDriver,Explain_UpLoaderDriver},//�ϴ���ʻԱID
		{ 	De_Dev_Order_UpLoaderHandMess,Explain_UpLoaderHandMess},//�ϴ��ֻ�����
		{ 	De_Dev_Order_NoSem,Explain_NoSem},//ä��������Ϣ
	/*---------------------------------------------���⳵Э��----------------------------------------------*/
		{ 	De_Dev_UpLoaderFrom,Explain_UpLoaderFrom},//�ϴ�����������Ϣ
		{ 	De_Dev_OverFromErro,Explain_OverFromErro},//�ϴ�����δ�����ԭ��
		{ 	De_Dev_PriceData,Explain_PriceData}//�ϴ��Ƽ�����Ϣ
	};
	const st_Fun_Tz_Send	CN_st_Fun_Tz_Send={Explain};
#else
	extern const st_Fun_Tz_Send	CN_st_Fun_Tz_Send;
#endif
