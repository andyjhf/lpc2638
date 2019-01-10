/*=====================================Include File=========================================================*/
#include "..\APP\config.h"
#include "stdlib.h"
#ifdef De_AppGprs_Compiler
	#include "..\File\rwFile.h"
	#include "..\miscellaneous\CodeTrans\AscNumber.h"
	#include "..\FilleData\FileData.h"
	#include "..\FilleData\TakeData.h"
	#include "..\Dev\Sensor\Sensor.h"
	#include "..\AgreeOn\TzV2.1.h"
	#include "..\AppSendAgreeOn\AppSendAgreeOn.H"
	#include "..\Control\Gprs\GPRS.h"
	#include "..\Control\Timer\Timer.h"
	#include "..\AppTask\OpenClose\OpenAndClose.H"
	#include "SetPar.c"
#endif
/*=====================================Define Data==========================================================*/
	/*+++++++++++++++++++++++++++++++++�������һ����+++++++++++++++++++++++++++++++++++++++++++*/
	#define De_AppGprs_Answer_Suc										0				//�ɹ�
	#define De_AppGprs_Answer_Erro										1				//����Ӧ��
	#define De_Suc_AppGprs												0				//ִ�гɹ�
	#define De_Erro_AppGprs_Over										1				//

	#define De_Erro_AgreeGprs_Start										1				//��ҳ��ʼ����
	#define De_Erro_AgreeGprs_DataLen									De_Erro_AgreeGprs_Start+1//���ȴ���
	#define De_Erro_AgreeGprs_ID										De_Erro_AgreeGprs_DataLen+1//������Ų�һ��
	#define De_Erro_AgreeGprs_AgreeOn									De_Erro_AgreeGprs_ID+1	//Э��汾����
	
/*========================================Data Define=============================================================*/
	typedef struct
	{ 	void (*Read)(st_st_AgreeOn_Dev_Par	*ptst_st_AgreeOn_Dev_Par,uint8 fd);
	}st_Fun_AppGprs;
#ifdef De_AppGprs_Compiler	
	typedef struct
	{	uint16 ParID;	 												//�趨����
		void (*	Execute)(st_st_AgreeOn_Dev_Par	*ptst_st_AgreeOn_Dev_Par,uint8 fd);	//ִ�в���
	}st_AppGprs_Order_Set;	 											//�趨�����ṹ��
#endif
/*=========================================Function=============================================================*/
#ifdef De_AppGprs_Compiler	
	static void AgreeData(st_st_AgreeOn_Dev_Par	*ptst_st_AgreeOn_Dev_Par,uint8 fd);
	//static void Answer(st_st_AgreeOn_Dev_Par	*ptst_st_AgreeOn_Dev_Par,uint8 fd,uint16 Result);  //��ȷ�����Ӧ��
	static void Orientation(st_st_AgreeOn_Dev_Par	*ptst_st_AgreeOn_Dev_Par,uint8 fd);	//���Ͷ�λָ��
	static void Track(st_st_AgreeOn_Dev_Par	*ptst_st_AgreeOn_Dev_Par,uint8 fd);			//׷��ָ��
	static void SetPar1(st_st_AgreeOn_Dev_Par	*ptst_st_AgreeOn_Dev_Par,uint8 fd);		//�趨����
	static void UnlockWaring(st_st_AgreeOn_Dev_Par	*ptst_st_AgreeOn_Dev_Par,uint8 fd);
	static void AmendMenum(st_st_AgreeOn_Dev_Par	*ptst_st_AgreeOn_Dev_Par,uint8 fd);
	static void LoaderTxt(st_st_AgreeOn_Dev_Par	*ptst_st_AgreeOn_Dev_Par,uint8 fd);
	static void LoaderTxtMenum(st_st_AgreeOn_Dev_Par	*ptst_st_AgreeOn_Dev_Par,uint8 fd);
	static void SetPhone(st_st_AgreeOn_Dev_Par	*ptst_st_AgreeOn_Dev_Par,uint8 fd);
	static void CallAnswer(st_st_AgreeOn_Dev_Par	*ptst_st_AgreeOn_Dev_Par,uint8 fd);
	static void UpdateSoftWare(st_st_AgreeOn_Dev_Par	*ptst_st_AgreeOn_Dev_Par,uint8 fd);
	static void LookPar(st_st_AgreeOn_Dev_Par	*ptst_st_AgreeOn_Dev_Par,uint8 fd);
	static void Contrl(st_st_AgreeOn_Dev_Par	*ptst_st_AgreeOn_Dev_Par,uint8 fd);
	static void ConfineCall(st_st_AgreeOn_Dev_Par	*ptst_st_AgreeOn_Dev_Par,uint8 fd);
	static void ConfigCentrSever(st_st_AgreeOn_Dev_Par	*ptst_st_AgreeOn_Dev_Par,uint8 fd);
	static void Activation(st_st_AgreeOn_Dev_Par	*ptst_st_AgreeOn_Dev_Par,uint8 fd);
	static void LookJpg(st_st_AgreeOn_Dev_Par	*ptst_st_AgreeOn_Dev_Par,uint8 fd);
	static void JpgIng(st_st_AgreeOn_Dev_Par	*ptst_st_AgreeOn_Dev_Par,uint8 fd);
	static void SetVidType(st_st_AgreeOn_Dev_Par	*ptst_st_AgreeOn_Dev_Par,uint8 fd);
	static void TabelList(st_st_AgreeOn_Dev_Par	*ptst_st_AgreeOn_Dev_Par,uint8 fd);
	static void LookWorkPar(st_st_AgreeOn_Dev_Par	*ptst_st_AgreeOn_Dev_Par,uint8 fd);
	static void WorkParTimer(st_st_AgreeOn_Dev_Par	*ptst_st_AgreeOn_Dev_Par,uint8 fd);
	static void WorkParSpace(st_st_AgreeOn_Dev_Par	*ptst_st_AgreeOn_Dev_Par,uint8 fd);
	static void LookLog(st_st_AgreeOn_Dev_Par	*ptst_st_AgreeOn_Dev_Par,uint8 fd);
	static void SetWaringTerm(st_st_AgreeOn_Dev_Par	*ptst_st_AgreeOn_Dev_Par,uint8 fd);
	static void LookWaringTerm(st_st_AgreeOn_Dev_Par	*ptst_st_AgreeOn_Dev_Par,uint8 fd);
	static void SetRound(st_st_AgreeOn_Dev_Par	*ptst_st_AgreeOn_Dev_Par,uint8 fd);
	static void DelRound(st_st_AgreeOn_Dev_Par	*ptst_st_AgreeOn_Dev_Par,uint8 fd);
	static void SetRectangle(st_st_AgreeOn_Dev_Par	*ptst_st_AgreeOn_Dev_Par,uint8 fd);
	static void DelRectangle(st_st_AgreeOn_Dev_Par	*ptst_st_AgreeOn_Dev_Par,uint8 fd);
	static void SetPolygon(st_st_AgreeOn_Dev_Par	*ptst_st_AgreeOn_Dev_Par,uint8 fd);
	static void DelPolygon(st_st_AgreeOn_Dev_Par	*ptst_st_AgreeOn_Dev_Par,uint8 fd);
	static void SetRoadMap(st_st_AgreeOn_Dev_Par	*ptst_st_AgreeOn_Dev_Par,uint8 fd);
	static void DelRoadMap(st_st_AgreeOn_Dev_Par	*ptst_st_AgreeOn_Dev_Par,uint8 fd);
	static void Reduce(st_st_AgreeOn_Dev_Par	*ptst_st_AgreeOn_Dev_Par,uint8 fd);
	static void Driver(st_st_AgreeOn_Dev_Par	*ptst_st_AgreeOn_Dev_Par,uint8 fd);
	static void Navigation(st_st_AgreeOn_Dev_Par	*ptst_st_AgreeOn_Dev_Par,uint8 fd);
	static void HandTxt(st_st_AgreeOn_Dev_Par	*ptst_st_AgreeOn_Dev_Par,uint8 fd);
	static void HandAttemper(st_st_AgreeOn_Dev_Par	*ptst_st_AgreeOn_Dev_Par,uint8 fd);
	static void AmendForm(st_st_AgreeOn_Dev_Par	*ptst_st_AgreeOn_Dev_Par,uint8 fd);
	static void UpLoaderForm(st_st_AgreeOn_Dev_Par	*ptst_st_AgreeOn_Dev_Par,uint8 fd);
	static void UpLoaderFormSuc(st_st_AgreeOn_Dev_Par	*ptst_st_AgreeOn_Dev_Par,uint8 fd);
	static void UpLoaderFormErro(st_st_AgreeOn_Dev_Par	*ptst_st_AgreeOn_Dev_Par,uint8 fd);
	static void UpLoaderCan(st_st_AgreeOn_Dev_Par	*ptst_st_AgreeOn_Dev_Par,uint8 fd);
#endif

/*==============================================ȫ�ֱ�������=====================================================*/							
#ifdef De_AppGprs_Compiler
	const st_Fun_AppGprs	CN_st_Fun_AppGprs={AgreeData};	
	static const st_AppGprs_Order_Set	CN_Ba_st_AppGprs_Order_Set[]=
	{ 	{	De_Centr_Order_Orientation,Orientation},//��λָ��
		{	De_Centr_Order_Track,Track},//׷��ָ��
		{	De_Centr_Order_SetPar,SetPar1},//�趨����
		{	De_Centr_Order_UnlockWaring,UnlockWaring},//�������
		{	De_Centr_Order_AmendMenum,AmendMenum},//�޸Ĺ̶��˵�
		{	De_Centr_Order_LoaderTxt,LoaderTxt},//�·��ı�����
		{	De_Centr_Order_LoaderTxtMenum,LoaderTxtMenum},//�·����ı��Ĳ˵�
		{	De_Centr_Order_SetPhone,SetPhone},//���ù̶��绰
		{	De_Centr_Order_CallAnswer,CallAnswer},//ͨ������
		{	De_Centr_Order_UpdateSoftWare,UpdateSoftWare},//�������
		{	De_Centr_Order_LookPar,LookPar},//��ѯ����
		{	De_Centr_Order_Contrl,Contrl},//Զ�̿���
		{	De_Centr_Order_ConfineCall,ConfineCall},//ͨ������״̬
		{	De_Centr_Order_ConfigCentrSever,ConfigCentrSever},//�������ķ�����״̬
		{	De_Centr_Order_Activation,Activation},//���λ�ն�
/*---------------------------------------------������չЭ��-----------------------------------------------------*/
		{	De_Centr_Order_LookJpg,LookJpg},//��ѯָ�����͵���Ƭ
		{	De_Centr_Order_JpgIng,JpgIng},//��ѯʵʱ��Ƭ
		{	De_Centr_Order_SetVidType,SetVidType},//������������
		{	De_Centr_Order_TabelList,TabelList},//���ñ�
		{	De_Centr_Order_LookWorkPar,LookWorkPar},//��ѯ��������
		{	De_Centr_Order_WorkParTimer,WorkParTimer},//���չ̶�ʱ���ϴ���������	
		{	De_Centr_Order_WorkParSpace,WorkParSpace},//���ռ���ϴ���������
		{	De_Centr_Order_LookLog,LookLog},//��ѯ��־�ļ�
		{	De_Centr_Order_SetWaringTerm,SetWaringTerm},//���ñ�������
		{	De_Centr_Order_LookWaringTerm,LookWaringTerm},//��ѯ��������
/*-----------------------------------------------����Э��ר��---------------------------------------------------*/
		{	 De_Centr_Order_SetRound,SetRound},//����Բ��·��
		{	 De_Centr_Order_DelRound,DelRound},//ɾ��Բ��·��
		{	 De_Centr_Order_SetRectangle,SetRectangle},//���þ���·��
		{	 De_Centr_Order_DelRectangle,DelRectangle},//ɾ������·��
		{	 De_Centr_Order_SetPolygon,SetPolygon},//���ö����·��
		{	 De_Centr_Order_DelPolygon,DelPolygon},//ɾ�������·��
		{	 De_Centr_Order_SetRoadMap,SetRoadMap},//����·������
		{	 De_Centr_Order_DelRoadMap,DelRoadMap},//ɾ��·������
		{	 De_Centr_Order_Reduce,Reduce},//����ѹ���ش�
		{	 De_Centr_Order_Driver,Driver},//���ü�ʻԱID
		{	 De_Centr_Order_Navigation,Navigation},//���ĵ���
		{	 De_Centr_Order_HandTxt,HandTxt},//�ֻ��ı�����
		{	 De_Centr_Order_HandAttemper,HandAttemper},//�ֻ�������Ϣ	
/*---------------------------------------------���⳵Э��-------------------------------------------------------*/ 
		{		De_Centr_Order_AmendForm,AmendForm},//�޸Ķ�����Ϣ
		{	 De_Centr_Order_UpLoaderForm,UpLoaderForm},//�·�����������Ϣ
		{	 De_Centr_Order_UpLoaderFormSuc,UpLoaderFormSuc},//�·���������ɹ���Ϣ
		{	 De_Centr_Order_UpLoaderFormErro,UpLoaderFormErro},//�·���������ʧ����Ϣ
		{	 De_Centr_Order_UpLoaderCan,UpLoaderCan}//�·�����ȡ����Ϣ
	};
	const uint8  CN_Ba_ChargLog[]=
	{	De_AgreeOn_SetPar_State_SetAPN,De_AgreeOn_SetPar_State_SetMastIP,De_AgreeOn_SetPar_State_SetMastDomainName,
		De_AgreeOn_SetPar_State_SetReserveIP,De_AgreeOn_SetPar_State_SetReserveDomainName,De_AgreeOn_SetPar_State_SetCenPort,
		De_AgreeOn_SetPar_State_SetUseName,De_AgreeOn_SetPar_State_SetUsePass,De_AgreeOn_SetPar_State_SetDevHeart,
		De_AgreeOn_SetPar_State_SetCentHeart,De_AgreeOn_SetPar_State_SetIPRepeat,De_AgreeOn_SetPar_State_SetIPRepeatTime		
	};
	const uint8 CN_Ba_ResetDev[]=
	{	De_AgreeOn_SetPar_State_SetParLoad,De_AgreeOn_SetPar_State_SetWireLessPar
	};		
#else
	extern const st_Fun_AppGprs	CN_st_Fun_AppGprs;
#endif
