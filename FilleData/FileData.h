
/*======================================Include File============================================================*/
 	#include "..\APP\config.h"
	#include "stdlib.h"
	#include "FileInfor.h"
	#include "FileBasInfor.h"
	#ifdef De_FileData_Compiler
		#include "..\File\rwFile.h"
		#include "..\miscellaneous\CodeTrans\AscNumber.h"
		#include "..\Control\GpsAndMileage\GpsAndMileage.h"
		
	#endif
/*=======================================Define Data===========================================================*/
	#ifdef De_FileData_Compiler
		#define De_File_BackFac_Yes									1						//�ָ���������
		#define De_File_BackFac_No									0						//���ָ���������	
	#endif
	#define De_File_Fd_Nofd											0xff					//û������ļ�
/*==========================================Data Define========================================================*/
/*-------------------------------------------�������ṹ------------------------------------------------------*/
	#ifdef De_FileData_Compiler
		typedef struct
		{	uint8 *FileName;				 //�ļ�����
			uint16 RecoderSize;				 //��¼��С
			uint16 RecoderNumber;			 //�ļ���¼����
			uint32 FileSize;				 //�ļ���С
			uint8  Property;				 //����		
		}st_File_Property;					//�ļ�����	

	 	typedef struct
		{	uint16 *fd;							   		//���ļ���ID
			const void *BackFaData;						//�ָ���������
			st_File_Property	CN_st_File_Property;
			uint8  SelectFac;							//�Ƿ�ָ���������
		}st_File_fd_Tabel;								//�ļ���Ϣ��
	#endif
	/*+++++++++++++++++++++++++++++++++++++++�����ļ���ȫ��ID++++++++++++++++++++++++++++++++++++++++++++*/
	typedef struct
	{	uint16 Basicfd;					//�ļ�������Ϣ��   1
		uint16 Driverfd;				//��ʻԱ������Ϣ   2
		uint16 GreenParfd;				//���������	   3
		uint16 WorkParfd;				//��������		   4
		uint16 Parameterfd; 			//����			   5
		uint16 GprsParfd;				//GPRS����		   6
	  	uint16 MessageParfd;			//��Ϣ����		   7
		uint16 Phonefd;					//�绰����		   8
		uint16 Rootfd;					//�̶��绰��Ϣ	   9
		uint16 AccTimerfd;			   	//ͳ��			   10
		uint16 Gpsfd;					//GPS��Ϣ����	   11
		uint16 Menumfd;					//�˵�			   12
		uint16 Workfd;					//������ˮ		   13
		uint16 Reducefd;				//ѹ�����ݻش�	   14
		uint16 NoFlowfd;			 	//ä������		   15
		uint16 Sendfd;					//��������		   16
		uint16 Photofd;					//��Ƭ��С		   17
		uint16 PhotoDatafd;				//��ƬFD		   18
	   	uint16 WaringStatefd;			//������������״̬ 19
		uint16 WaringTermfd;			//��������		   20
		uint16 VidTermfd;				//����			   21
		uint16 Areafd;					//����FD		   22
		uint16 Roundfd;	   				//Բ������		   23
		uint16 Rectanglefd;				//��������		   24
		uint16 WorkParTimerfd;			//�̶�ʱ���	   25
	}st_File_fd;						//�����ļ�	
/*==============================================��������======================================================*/
	void FileData_BackSet(void);
	void FileData_CheckFile(void);
	#ifdef De_FileData_Compiler
		static void BackFacFile(st_File_fd_Tabel	*ptst_File_fd_Tabel);
	#endif		
/*=======================================ȫ�ֱ�������=========================================================*/
	#ifdef De_FileData_Compiler
		st_File_fd	CN_st_File_fd;
	/*-------------------------------------------�ļ�ϵͳ�ṹ��-------------------------------------------------------*/
		const st_File_fd_Tabel	CN_Ba_st_File_fd_Tabel[]=  				//��Ӧ�ó������������ļ�����
		{	{&CN_st_File_fd.Basicfd,&CN_Ba_st_File_Basic,{"Basic",sizeof(st_File_Basic),1,0,De_File_Property_Cycle},De_File_BackFac_No},//�ļ�������Ϣ��		
			{&CN_st_File_fd.Driverfd,NULL,{"Driver",sizeof(st_AgreeOn_Driver),1,0,De_File_Property_Cycle},De_File_BackFac_Yes},//��ʻԱ������Ϣ��
		   	{&CN_st_File_fd.GreenParfd,&CN_Ba_st_File_GreenPar,{"GrePar",sizeof(st_File_GreenPar),1,0,De_File_Property_Cycle},De_File_BackFac_Yes},//����������
		 	{&CN_st_File_fd.WorkParfd,&CN_Ba_st_File_WorkPar,{"WorkPar",sizeof(st_File_WorkPar),1,0,De_File_Property_Cycle},De_File_BackFac_Yes},	//��������
			{&CN_st_File_fd.Parameterfd,&CN_Ba_st_Parameter_Table,{"parame",sizeof(st_Parameter_Table),1,0,De_File_Property_Cycle},De_File_BackFac_Yes},//������
			{&CN_st_File_fd.GprsParfd,&CN_Ba_st_Gprs_ComPar,{"IPPar",sizeof(st_Gprs_ComPar),1,0,De_File_Property_Cycle},De_File_BackFac_Yes},	 //IPͨѶ��ʽ�²���
			{&CN_st_File_fd.MessageParfd,&CN_Ba_st_Message_ComPar,{"MesPar",sizeof(st_Message_ComPar),1,0,De_File_Property_Cycle},De_File_BackFac_Yes},//Message��ʽ�µ�ͨѶ����
			{&CN_st_File_fd.Phonefd,&CN_Ba_st_Phone_Basic,{"Phone",sizeof(st_Phone_Basic),1,0,De_File_Property_Cycle},De_File_BackFac_Yes},	//�绰�������
			{&CN_st_File_fd.Rootfd,&CN_Ba_st_Phone_Root,{"RoPhone",sizeof(st_AgreeOn_Phone_Par),10,0,De_File_Property_Recoder},De_File_BackFac_Yes}, //�̶��绰����
			{&CN_st_File_fd.AccTimerfd,&CN_Ba_st_AccTimer,{"AccTimer",sizeof(st_AccTimer),1,0,De_File_Property_Cycle},De_File_BackFac_Yes},//ACCʱ��ͳ��
			{&CN_st_File_fd.Gpsfd,NULL,{"Gps",sizeof(st_File_Gps),1,0,De_File_Property_Cycle},De_File_BackFac_No},				//GPS���ݱ���
			{&CN_st_File_fd.Menumfd,&CN_Ba_st_File_Menum,{"Menum",sizeof(st_File_Menum),128,0,De_File_Property_Recoder},De_File_BackFac_Yes},
			{&CN_st_File_fd.Workfd,NULL,{"Flow",sizeof(st_WorkFlow_Table),20000,0,De_File_Property_Cycle},De_File_BackFac_No},		//������������		
			{&CN_st_File_fd.Reducefd,NULL,{"Reduce",sizeof(st_Reduce_Table),1,0,De_File_Property_Cycle}, De_File_BackFac_No},
			{&CN_st_File_fd.NoFlowfd,NULL,{"Nosem",sizeof(st_NoFlow_Table),20000,0,De_File_Property_Cycle},De_File_BackFac_No},
			{&CN_st_File_fd.Sendfd,NULL,{"Send",sizeof(st_Send_Table),1,0,De_File_Property_Cycle},De_File_BackFac_No},
			{&CN_st_File_fd.Photofd,NULL,{"Photo",sizeof(st_File_Photo_Tail),1000,0,De_File_Property_Cycle},De_File_BackFac_No},
			{&CN_st_File_fd.PhotoDatafd,NULL,{"PhoDa",sizeof(st_File_Photo_Data),10000,0,De_File_Property_Cycle},De_File_BackFac_No},
			{&CN_st_File_fd.WaringStatefd,NULL,{"WarState",sizeof(st_Warning_State_Table),1,0,De_File_Property_Cycle},De_File_BackFac_No},
			{&CN_st_File_fd.WaringTermfd,NULL,{"WarPar",sizeof(st_AgreeOn_SetVidType),1,0,De_File_Property_Cycle},De_File_BackFac_No},
			{&CN_st_File_fd.VidTermfd,NULL,{"WarVid",sizeof(st_AgreeOn_SetVidType),1,0,De_File_Property_Cycle},De_File_BackFac_No},
			{&CN_st_File_fd.Areafd,NULL,{"Area",sizeof(st_Area_Infor_Table),1,0,De_File_Property_Cycle},De_File_BackFac_No},
			{&CN_st_File_fd.Roundfd,NULL,{"Round",sizeof(st_AgreeOn_SetRound_Par),50,0,De_File_Property_Cycle},De_File_BackFac_No},
			{&CN_st_File_fd.Rectanglefd,NULL,{"Rectang",sizeof(st_AgreeOn_SetRectangle_Par),50,0,De_File_Property_Cycle},De_File_BackFac_No},	
			{&CN_st_File_fd.WorkParTimerfd,NULL,{"ParTimer",sizeof(st_AgreeOn_WorkParTimer),1,0,De_File_Property_Cycle},De_File_BackFac_No}
			//{&CN_st_File_fd.DrivLogFd,NULL,{"DriLog",sizeof(st_Driver_Log_Table),1,0,De_File_Property_Cycle},De_File_BackFac_No}
			
			
		
		};	
		st_WorkFlow_Table	App_CN_st_WorkFlow_Table;	
	/*------------------------------------ϵͳ״̬-------------------------------------------------------*/
	#else
		extern st_File_fd	CN_st_File_fd;
		extern st_WorkFlow_Table App_CN_st_WorkFlow_Table;	
	#endif

