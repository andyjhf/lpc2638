/*=========================================Include File=========================================================*/
	#include "..\..\..\APP\config.h"											//LPC2368�Ĵ�������
 	#include "stdlib.h"		
	#ifdef De_Tz_Agreen_Compiler												//C��������
		#include "..\..\..\miscellaneous\CodeTrans\AscNumber.h"					//��������ת����Դ
		#include "..\..\..\miscellaneous\Date\Date.h"								//����������Դ
		#include "..\..\AgreementCom.h"												//Э������
		#include "Tz_Agreen_Pubi.c"
	#endif
/*==========================================Define Data=======================================================*/
	#define De_Erro_Tz_Agreen_NoEdit								1		//��֧�ִ�Э��
	#define De_Suc_Tz_Agreen										0		//�ɹ�
/*==========================================Data Define=======================================================*/
	typedef struct
	{	uint16 (*Read)(uint8 *Buf,void *OutBuf,uint16 DataLen,uint16 ID);
	}st_Fun_Tz_Agreen;


#ifdef De_Tz_Agreen_Compiler
	typedef struct
	{	uint16 ID;
		void (*Read)(uint8 *Buf,void *OutBuf,uint16 DataLen);
	}st_Tz_Agreen_FunOper;
#endif
/*=========================================static Function======================================================*/
#ifdef De_Tz_Agreen_Compiler	
	static uint16 Explain(uint8 *Buf,void *OutBuf,uint16 DataLen,uint16 ID);
	
	/*----------------------------------------------����Э��----------------------------------------*/
	static void Explain_Answer(uint8 *Buf,void *OutBuf,uint16 DataLen);					//��������Ӧ��
//	static void Explain_Orientation(uint8 *Buf,void *OutBuf,uint16 DataLen);			//��λָ��
	static void Explain_Track(uint8 *Buf,void *OutBuf,uint16 DataLen);					//׷��ָ��
	static void Explain_SetPar(uint8 *Buf,void *OutBuf,uint16 DataLen);					//�趨����
	static void Explain_UnlockWaring(uint8 *Buf,void *OutBuf,uint16 DataLen);			//�������
	static void Explain_AmendMenum(uint8 *Buf,void *OutBuf,uint16 DataLen);				//�޸Ĺ̶��˵�
	static void Explain_LoaderTxt(uint8 *Buf,void *OutBuf,uint16 DataLen);				//�·��ı�����
	static void Explain_LoaderTxtMenum(uint8 *Buf,void *OutBuf,uint16 DataLen);			//�·����ı��Ĳ˵�
	static void Explain_SetPhone(uint8 *Buf,void *OutBuf,uint16 DataLen);				//���ù̶��绰
	static void Explain_CallAnswer(uint8 *Buf,void *OutBuf,uint16 DataLen);				//ͨ������
	static void Explain_UpdateSoftWare(uint8 *Buf,void *OutBuf,uint16 DataLen);			//�������
	static void Explain_LookPar(uint8 *Buf,void *OutBuf,uint16 DataLen);				//��ѯ����
	static void Explain_Contrl(uint8 *Buf,void *OutBuf,uint16 DataLen);					//Զ�̿���
	static void Explain_ConfineCall(uint8 *Buf,void *OutBuf,uint16 DataLen);			//ͨ������״̬
	static void Explain_ConfigCentrSever(uint8 *Buf,void *OutBuf,uint16 DataLen);		//�������ķ�����״̬
//	static void Explain_Activation(uint8 *Buf,void *OutBuf,uint16 DataLen);				//���λ�ն�
/*---------------------------------------------������չЭ��-----------------------------------------------------*/
	static void Explain_LookJpg(uint8 *Buf,void *OutBuf,uint16 DataLen);				//��ѯָ�����͵���Ƭ
	static void Explain_JpgIng(uint8 *Buf,void *OutBuf,uint16 DataLen);					//��ѯʵʱ��Ƭ
	static void Explain_SetVidType(uint8 *Buf,void *OutBuf,uint16 DataLen);				//������������
	static void Explain_TabelList(uint8 *Buf,void *OutBuf,uint16 DataLen);				//���ñ�
//	static void Explain_LookWorkPar(uint8 *Buf,void *OutBuf,uint16 DataLen);			//��ѯ��������
	static void Explain_WorkParTimer(uint8 *Buf,void *OutBuf,uint16 DataLen);			//���չ̶�ʱ���ϴ���������	
	static void Explain_WorkParSpace(uint8 *Buf,void *OutBuf,uint16 DataLen);		   	//���ռ���ϴ���������
	static void Explain_LookLog(uint8 *Buf,void *OutBuf,uint16 DataLen);				//��ѯ��־�ļ�
	static void Explain_SetWaringTerm(uint8 *Buf,void *OutBuf,uint16 DataLen);			//���ñ�������
//	static void Explain_LookWaringTerm(uint8 *Buf,void *OutBuf,uint16 DataLen);			//��ѯ��������
/*-----------------------------------------------����Э��ר��---------------------------------------------------*/
	static void Explain_SetRound(uint8 *Buf,void *OutBuf,uint16 DataLen);				//����Բ��·��
	static void Explain_DelRound(uint8 *Buf,void *OutBuf,uint16 DataLen);				//ɾ��Բ��·��
	static void Explain_SetRectangle(uint8 *Buf,void *OutBuf,uint16 DataLen);			//���þ���·��
	static void Explain_DelRectangle(uint8 *Buf,void *OutBuf,uint16 DataLen);			//ɾ������·��
	static void Explain_SetPolygon(uint8 *Buf,void *OutBuf,uint16 DataLen);				//���ö����·��
	static void Explain_DelPolygon(uint8 *Buf,void *OutBuf,uint16 DataLen);				//ɾ�������·��
	static void Explain_SetRoadMap(uint8 *Buf,void *OutBuf,uint16 DataLen);				//����·������
	static void Explain_DelRoadMap(uint8 *Buf,void *OutBuf,uint16 DataLen);				//ɾ��·������
	static void Explain_Reduce(uint8 *Buf,void *OutBuf,uint16 DataLen);					//����ѹ���ش�
	static void Explain_Driver(uint8 *Buf,void *OutBuf,uint16 DataLen);					//���ü�ʻԱID
	static void Explain_Navigation(uint8 *Buf,void *OutBuf,uint16 DataLen);				//���ĵ���
	static void Explain_HandTxt(uint8 *Buf,void *OutBuf,uint16 DataLen);				//�ֻ��ı�����
	static void Explain_HandAttemper(uint8 *Buf,void *OutBuf,uint16 DataLen);			//�ֻ�������Ϣ	
/*---------------------------------------------���⳵Э��-------------------------------------------------------*/ 
	static void Explain_AmendForm(uint8 *Buf,void *OutBuf,uint16 DataLen);				//�޸Ķ�����Ϣ
	static void Explain_UpLoaderForm(uint8 *Buf,void *OutBuf,uint16 DataLen);			//�·�����������Ϣ
	static void Explain_UpLoaderFormSuc(uint8 *Buf,void *OutBuf,uint16 DataLen);		//�·���������ɹ���Ϣ
	static void Explain_UpLoaderFormErro(uint8 *Buf,void *OutBuf,uint16 DataLen);		//�·���������ʧ����Ϣ
	static void Explain_UpLoaderCan(uint8 *Buf,void *OutBuf,uint16 DataLen);			//�·�����ȡ����Ϣ
#endif


/*===========================================Public Ram========================================================*/
#ifdef De_Tz_Agreen_Compiler
	static const st_Tz_Agreen_FunOper	CN_Ba_st_Tz_Agreen_FunOper[]=
	{	{	De_Centr_Order_Answer,Explain_Answer},										//����Ӧ��									
		{	De_Centr_Order_Orientation,NULL},											//��λָ��
		{	De_Centr_Order_Track,Explain_Track},										//׷��ָ��
		{	De_Centr_Order_SetPar,Explain_SetPar},										//�趨����
		{	De_Centr_Order_UnlockWaring,NULL},											//�������
		{	De_Centr_Order_AmendMenum,Explain_AmendMenum},								//�޸Ĺ̶��˵�
		{	De_Centr_Order_LoaderTxt,Explain_LoaderTxt},								//�·��ı�����
		{	De_Centr_Order_LoaderTxtMenum,Explain_LoaderTxtMenum},						//�·����ı��Ĳ˵�
		{	De_Centr_Order_SetPhone,Explain_SetPhone},									//���ù̶��绰
		{	De_Centr_Order_CallAnswer,Explain_CallAnswer},								//ͨ������
		{	De_Centr_Order_UpdateSoftWare,Explain_UpdateSoftWare},						//�������
		{	De_Centr_Order_LookPar,Explain_LookPar},									//��ѯ����
		{	De_Centr_Order_Contrl,Explain_Contrl},										//Զ�̿���
		{	De_Centr_Order_ConfineCall,Explain_ConfineCall},							//ͨ������״̬
		{	De_Centr_Order_ConfigCentrSever,Explain_ConfigCentrSever},					//�������ķ�����״̬
		{	De_Centr_Order_Activation,NULL},					                    	//���λ�ն�
		{	De_Centr_Order_LookJpg,Explain_LookJpg},									//��ѯָ�����͵���Ƭ
		{	De_Centr_Order_JpgIng,Explain_JpgIng},										//��ѯʵʱ��Ƭ
		{	De_Centr_Order_SetVidType,Explain_SetVidType},								//������������
		{	De_Centr_Order_TabelList,Explain_TabelList},								//���ñ�
		{	De_Centr_Order_LookWorkPar,NULL},							                //��ѯ��������
		{	De_Centr_Order_WorkParTimer,Explain_WorkParTimer},							//���չ̶�ʱ���ϴ���������	
		{	De_Centr_Order_WorkParSpace,Explain_WorkParSpace},							//���ռ���ϴ���������
		{	De_Centr_Order_LookLog,Explain_LookLog},									//��ѯ��־�ļ�
		{	De_Centr_Order_SetWaringTerm,Explain_SetWaringTerm},						//���ñ�������
		{	De_Centr_Order_LookWaringTerm,NULL},						//��ѯ��������
	/*-----------------------------------------------����Э��ר��---------------------------------------------------*/
		{	De_Centr_Order_SetRound,Explain_SetRound},									//����Բ��·��
		{	De_Centr_Order_DelRound,Explain_DelRound},									//ɾ��Բ��·��
		{	De_Centr_Order_SetRectangle,Explain_SetRectangle},							//���þ���·��
		{	De_Centr_Order_DelRectangle,Explain_DelRectangle},							//ɾ������·��
		{	De_Centr_Order_SetPolygon,Explain_SetPolygon},								//���ö����·��
		{	De_Centr_Order_DelPolygon,Explain_DelPolygon},								//ɾ�������·��
		{	De_Centr_Order_SetRoadMap,Explain_SetRoadMap},								//����·������
		{	De_Centr_Order_DelRoadMap,Explain_DelRoadMap},								//ɾ��·������
		{	De_Centr_Order_Reduce,Explain_Reduce},										//����ѹ���ش�
		{	De_Centr_Order_Driver,Explain_Driver},										//���ü�ʻԱID
		{	De_Centr_Order_Navigation,Explain_Navigation},								//���ĵ���
		{	De_Centr_Order_HandTxt,Explain_HandTxt},									//�ֻ��ı�����
		{	De_Centr_Order_HandAttemper,Explain_HandAttemper},							//�ֻ�������Ϣ	
	/*---------------------------------------------���⳵Э��-------------------------------------------------------*/ 
		{	De_Centr_Order_AmendForm,Explain_AmendForm},								//�޸Ķ�����Ϣ
		{	De_Centr_Order_UpLoaderForm,Explain_UpLoaderForm},							//�·�����������Ϣ
		{	De_Centr_Order_UpLoaderFormSuc,Explain_UpLoaderFormSuc},					//�·���������ɹ���Ϣ
		{	De_Centr_Order_UpLoaderFormErro,Explain_UpLoaderFormErro},					//�·���������ʧ����Ϣ
		{	De_Centr_Order_UpLoaderCan,Explain_UpLoaderCan}								//�·�����ȡ����Ϣ
	};
	const st_Fun_Tz_Agreen	CN_st_Fun_Tz_Agreen={Explain};
#else
	extern const st_Fun_Tz_Agreen	CN_st_Fun_Tz_Agreen;
#endif
