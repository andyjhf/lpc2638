/*======================================Include File============================================================*/
 	#include "..\..\APP\config.h"
	#include "stdlib.h"
	#ifdef De_FileData_Compiler
		#include "..\..\File\rwFile.h"
		#include "..\..\miscellaneous\CodeTrans\AscNumber.h"
		#include "FileInfor.h"
		#include "FileBasInfor.h"
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
	{	uint16 Basicfd;					//������Ϣ
		uint16 Parameterfd; 			//����
	  	uint16 Phonefd;					//�绰����
		uint16 MessageParfd;			//��Ϣ����
		uint16 GprsParfd;				//GPRS����
		uint16 GreenParfd;				//���������
		uint16 Accfd;					//����ACC�����ͳ��
		uint16 Driverfd;				//��ʻԱ������Ϣ
		uint16 AccTimerfd;			   	//ACC���ͳ��
		uint16 Rootfd;					//�̶��绰��Ϣ
		uint16 Gpsfd;					//GPS��Ϣ����
		uint16 Workfd;					//��������
		uint16 Menumfd;					//�˵�
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
			{&CN_st_File_fd.Driverfd,&CN_Ba_st_Emplo_Basic,{"Driver",sizeof(st_Emplo_Basic),100,0,De_File_Property_Recoder},De_File_BackFac_Yes},//��ʻԱ������Ϣ��
		   	{&CN_st_File_fd.GreenParfd,&CN_Ba_st_File_GreenPar,{"GrePar",sizeof(st_File_GreenPar),1,0,De_File_Property_Cycle},De_File_BackFac_Yes},//����������
		 	{&CN_st_File_fd.Parameterfd,&CN_Ba_st_Parameter_Table,{"parame",sizeof(st_Parameter_Table),1,0,De_File_Property_Cycle},De_File_BackFac_Yes},//������
			{&CN_st_File_fd.GprsParfd,&CN_Ba_st_Gprs_ComPar,{"IPPar",sizeof(st_Gprs_ComPar),1,0,De_File_Property_Cycle},De_File_BackFac_Yes},	 //IPͨѶ��ʽ�²���
			{&CN_st_File_fd.MessageParfd,&CN_Ba_st_Message_ComPar,{"MesPar",sizeof(st_Message_ComPar),1,0,De_File_Property_Cycle},De_File_BackFac_Yes},//Message��ʽ�µ�ͨѶ����
			{&CN_st_File_fd.Phonefd,&CN_Ba_st_Phone_Basic,{"Phone",sizeof(st_Phone_Basic),1,0,De_File_Property_Cycle},De_File_BackFac_Yes},	//�绰�������
			{&CN_st_File_fd.Rootfd,&CN_Ba_st_Phone_Root,{"RoPhone",sizeof(st_Phone_Root),1,0,De_File_Property_Cycle},De_File_BackFac_Yes}, //�̶��绰����
			{&CN_st_File_fd.AccTimerfd,&CN_Ba_st_AccTimer,{"AccTimer",sizeof(st_AccTimer),1,0,De_File_Property_Cycle},De_File_BackFac_Yes},//ACCʱ��ͳ��
			{&CN_st_File_fd.Gpsfd,NULL,{"Gps",sizeof(st_File_Gps),1,0,De_File_Property_Cycle},De_File_BackFac_No},				//GPS���ݱ���
			{&CN_st_File_fd.Menumfd,&CN_Ba_st_File_Menum,{"Menum",sizeof(st_File_Menum),128,0,De_File_Property_Recoder}},
			{&CN_st_File_fd.Workfd,NULL,{"Flow",sizeof(st_WorkFlow_Table),10000,0,De_File_Property_Cycle},De_File_BackFac_No}		//������������		
		};							//��Ӧ�ó��������ļ���
	/*------------------------------------ϵͳ״̬-------------------------------------------------------*/
	#else
		extern st_File_fd	CN_st_File_fd;
	#endif