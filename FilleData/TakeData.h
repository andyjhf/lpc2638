/*========================================include File===========================================================*/
	#include "..\APP\config.h"
	#include "stdlib.h"
	#ifdef De_TakeData_Compiler
		#include "..\File\rwFile.h"
		#include "..\miscellaneous\CodeTrans\AscNumber.h"
		#include "FileData.h"
		#include "..\AgreeOn\TzV2.1\Send\Tz_Send.h"
		#include "..\HardWare\RTC\RTC.h"
	#endif
/*=========================================Define Data===========================================================*/
	#define De_Suc_AccessBasic									0
	#define De_Erro_NoSend										100
	#define De_Erro_PhoneCut_No									De_Erro_NoSend+1
	#define De_Erro_AppSendAgree_Init							De_Erro_PhoneCut_No+1;
	#define De_Erro_Ara_NoData									De_Erro_AppSendAgree_Init+1


	#define De_Access_Space_WorkParWaring1						0
	#define De_Access_Space_VidWaring							De_CN_Ba_WordPar_Number
	#define De_Access_Space_Help								2*De_CN_Ba_WordPar_Number			//��������
	#define De_Access_Space_HighSpeed							De_Access_Space_Help+1				//���ٱ���
	#define De_Access_Space_LowSpeed							De_Access_Space_HighSpeed+1			//���ٱ���
	#define De_Access_Space_LowVo								De_Access_Space_LowSpeed+1			//�͵�ѹ����
	#define De_Access_Space_ClosePower							De_Access_Space_LowVo+1				//�ϵ籨��
	#define De_Access_Space_LCD									De_Access_Space_ClosePower+1		//LCD����
	#define De_Access_Space_VidClose							De_Access_Space_LCD+1				//��Ƶ���
	#define De_Access_Space_GpsErro								De_Access_Space_VidClose+1			//GPSģ�����
	#define De_Access_Space_GpsLessOpen							De_Access_Space_GpsErro+1			//GPS��·
	#define De_Access_Space_GpsLessClose						De_Access_Space_GpsLessOpen+1		//Gps���߶�·
	#define De_Access_Space_WorkParWaring						De_Access_Space_GpsLessClose+1		//������������
	#define De_Access_Space_LessState							De_Access_Space_WorkParWaring+1		//���ߴ�����״̬����

	
	
	#define De_Access_Type_Help													1			//��������
	#define De_Access_Type_HighSpeed											2			//���ٱ���
	#define De_Access_Type_LowSpeed												3			//���ٱ���
	#define De_Access_Type_LowVo												4			//�͵�ѹ����
	#define De_Access_Type_ClosePower											5 			//�ϵ籨��
	#define De_Access_Type_LCD													6			//LCD����
	#define De_Access_Type_VidClose												7			//��Ƶ���
	#define De_Access_Type_GpsErro												8			//GPSģ�����
	#define De_Access_Type_GpsLessOpen											9			//GPS��·
	#define De_Access_Type_GpsLessClose											10			//Gps���߶�·
	#define De_Access_Type_WorkParWaring										11		   	//������������
	#define De_Access_Type_LessState											12			//���ߴ�����״̬����


	#define De_Access_Type_Track												13			//׷��
	#define De_Access_Type_WorkPar												14			//��������
	#define De_Access_Type_CarPower												15			//��������תʱ����
	#define De_Access_Type_ReduceWork											16			//��������
	#define De_Access_Type_ReduceTrack											17			//׷�ٲ���
	#define De_Access_Type_WorkParWaringVid										18			//������������
	#define De_Access_Type_AccOpenVid											19			//ACC������
	#define De_Access_Type_AccCloseVid											20			//ACC�ر�
	#define De_Access_Type_HelpVid												21			//����
	#define De_Access_Type_EngineVid											22  		//������
	#define De_Access_Type_WaringParVid											23			//��������
	#define De_Access_Type_ReduceOver											24			//ѹ���ش�����
	#define De_Access_Type_PowerClose											25	   		//�ػ�
	#define De_Access_Type_GprsClose											26			//����
	#define De_Access_Type_JugeLog												27			//��ʻԱ��¼
	#define De_Access_Type_ExitLog												28			//��ʻԱ�˳���¼
	#define De_Access_Type_LogErro												29			//��ʻԱ��¼ʧ��




	#define De_Orientation_State_Gps											0 			//GPS��λ
	#define De_Orientation_State_GpsLatitude									1			//γ��
	#define De_Orientation_State_GpsLongitude									2			//����
	#define De_Orientation_State_Contro											7			//Զ�̿���
	#define De_Orientation_State_ACC											8			//ACC
	#define De_Orientation_State_Car											9			//�ճ����س�
	#define De_Orientation_State_Oper											10			//��Ӫ
	#define De_Orientation_State_CarPower										11			//����������
	#define De_Orientation_State_Help											16			//��������
	#define De_Orientation_State_HighSpeed										17			//���ٱ���
	#define De_Orientation_State_Vid											18			//��Ƶ�źŲ������
	#define De_Orientation_State_Low											19			//��ѹ����
	#define De_Orientation_State_CloseVal										20			//�ϵ籨��
	#define De_Orientation_State_LowSpeed										21			//���ٱ���
	#define De_Orientation_State_Gps1											25			//GPSģ�鷢������
	#define De_Orientation_State_LCD											28			//LCDͨѶ����


	#define De_Space_Set														0xffff 		//������ȵ�λ��
	#define De_ReadSpace_Track								0					//׷�������͵�λ��
	#define De_ReadSpace_WorkPar							1  					//�������������͵�λ��
	#define De_ReadSpace_Reduce								2					//ѹ�����ݻش������͵�λ��
	#define De_ReadSpace_Photo								3					//��Ƭ�����͵�λ��
	#define De_ReadSpace_DriverLog							4					//��ʻԱ��¼��Ϣ
	
	#define De_Waring_State_Yes													1
	#define De_Waring_State_No													0

	#define De_Type_Round											1
	#define De_Type_Rectangle										2
/*========================================Data Define ==========================================================*/
	typedef struct
	{ 	uint16 (*ReadFlow)(uint16 Recoder,void *Buf);
		uint16 (*WriteFlow)(uint16 ID,st_WorkFlow_Table	*ptst_WorkFlow_Table);
		uint16 (*ReadDataFlow)(uint16 Recoder,st_WorkFlow_Table	*ptst_WorkFlow_Table);
		uint16 (*GetFlowWaringType)(uint16 Recoder,uint8 *Type);
		uint32 (*GetPhonesSize)(uint16 Recoder);
		uint16 (*GetPhoneCut)(uint16 Recoder,uint32 StartSize,uint16 DataLen,uint8 *Buf);
		uint16 (*WritePhone)(uint16 *Recoder);
		void (*ClearState)(uint8 Number);
		uint8 (*GetState)(uint8 Number);
		void (*SetState)(uint8 Number);	
		void (* AddSpace)(uint16 Space,uint16 Number);
		uint16 (*ReadSpace)(uint16 Space); 
		uint16 (*ReadParTable)(uint16 Recoder,st_AgreeOn_Send_UploaderPar	*ptst_AgreeOn_Send_UploaderPar);
		uint16 (*GetAreaData)(void *Data,uint16 Number,uint8 *Type);
		uint16 (*AccessAear)(void *Buf,uint8 Type);
		void (*DelAear)(uint16 ID);
	}st_Fun_TakeData;

/*=======================================Static Function========================================================*/
 #ifdef De_TakeData_Compiler
 	static uint16 ReadParTable(uint16 Recoder,st_AgreeOn_Send_UploaderPar	*ptst_AgreeOn_Send_UploaderPar);	
	static uint16 ReadFlow(uint16 Recoder,void *Buf);
	static uint16 WriteFlow(uint16 ID,st_WorkFlow_Table	*ptst_WorkFlow_Table);
	static uint16 ReadDataFlow(uint16 Recoder,st_WorkFlow_Table	*ptst_WorkFlow_Table);
	static uint16 GetFlowWaringType(uint16 Recoder,uint8 *Type);
	static uint32 GetPhonesSize(uint16 Recoder);
	static uint16 GetPhoneCut(uint16 Recoder,uint32 StartSize,uint16 DataLen,uint8 *Buf);
	static uint16 WritePhone(uint16 *Recoder);
	static void ClearState(uint8 Number);
	static uint8 GetState(uint8 Number);
	static void SetState(uint8 Number);
	static void AddSpace(uint16 Space,uint16 Number);
	static uint16 ReadSpace(uint16 Space);
	static uint16 JugeReduceData(void);
	static uint16 JugeReduceData(void);
	static uint16 JugeReduceLen(void);
	static uint16 SendReduceData(void);
	static uint16 GetAreaData(void *Data,uint16 Number,uint8 *Type);
	static uint16 AccessAear(void *Buf,uint8 Type);
	static void DelAear(uint16 ID);
	static uint16 JugeID(uint16 ID,st_Area_Infor_Table	*ptst_Area_Infor_Table);
 #endif
/*=========================================Public Ram=========================================================*/ 			 
#ifdef De_TakeData_Compiler	
	const st_Fun_TakeData	CN_st_Fun_TakeData={ReadFlow,WriteFlow,ReadDataFlow,GetFlowWaringType,GetPhonesSize,
	GetPhoneCut,WritePhone,ClearState,GetState,SetState,AddSpace,ReadSpace,ReadParTable,GetAreaData,AccessAear,
	DelAear};	
#else
	extern const st_Fun_TakeData	CN_st_Fun_TakeData;
#endif
