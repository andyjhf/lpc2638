	#define De_Devi_ComMod_Gprs										0						//IpͨѶ��ʽ
	#define De_Devi_ComMod_Sms										1						//����ͨѶ��ʽ
	#define De_AppGprs_TakeLcd_Yes									1						//��װ������
	#define De_AppGprs_TakeLcd_No									0						//����װ������
	#define De_AppGprs_LogMess_Yes									1						//��¼��ʾ
	#define De_AppGprs_LogMess_No									0						//��¼����ʾ
	#define De_AppGprs_TaskVid_Yes									1						//��װ����ͷ
	#define De_AppGprs_TaskVid_No									0						//����װ����ͷ
	#define De_File_Phone_Pro_OutIn									0						//��������������
	#define De_File_Phone_Pro_InNoOut								1						//������벻�������
	#define De_File_Phone_Pro_OutNoIn								2						//����������������
	#define De_File_Phone_Pro_NoOutNoIn								3						//������������������
	#define De_WordPar_Open											0 		
	#define De_WordPar_Close										1
	#define De_WordPar_NoAdree										0xffffffff
#ifdef De_FileData_Compiler
/*============================================����������==========================================================*/
		 
/*==========================================�ļ�������Ϣ��======================================================*/
	static const st_File_Basic		CN_Ba_st_File_Basic=
	{ 	{'W','V','1','.','0','0',0X00,0X00},										//����汾��
		{'V','2','.','3',0,0,0,0},													//Ӳ���汾��
		{'8','8','8','8','8','8','8','8','8','8','8','8','8','8','8','8'},			//�������
		{0x88,0x88,0x88,0x88,0x88,0x88,0x88},										//����
		{0,3},																		//��������״̬
		{0,2}																		//���Ҵ���
	};
/*==========================================�ļ�������Ϣ��=====================================================*/
	static const st_Emplo_Basic	CN_Ba_st_Emplo_Basic={	0,"","","",""	};				//��ʻԱID
	static const st_File_GreenPar	 CN_Ba_st_File_GreenPar={"a",0,111111 };
	static const st_File_WorkPar	CN_Ba_st_File_WorkPar[sizeof(CN_Ba_WordPar)/sizeof(uint16)]=
	{	{De_WordPar_NoAdree,De_WordPar_Close},{De_WordPar_NoAdree,De_WordPar_Close},{De_WordPar_NoAdree,De_WordPar_Close},
		{De_WordPar_NoAdree,De_WordPar_Close},{De_WordPar_NoAdree,De_WordPar_Close},{De_WordPar_NoAdree,De_WordPar_Close},
		{De_WordPar_NoAdree,De_WordPar_Close},{De_WordPar_NoAdree,De_WordPar_Close},{De_WordPar_NoAdree,De_WordPar_Close},
		{De_WordPar_NoAdree,De_WordPar_Close},{De_WordPar_NoAdree,De_WordPar_Close},{De_WordPar_NoAdree,De_WordPar_Close},
		{De_WordPar_NoAdree,De_WordPar_Close},{De_WordPar_NoAdree,De_WordPar_Close},{De_WordPar_NoAdree,De_WordPar_Close},
		{De_WordPar_NoAdree,De_WordPar_Close},{De_WordPar_NoAdree,De_WordPar_Close},{De_WordPar_NoAdree,De_WordPar_Close},
		{De_WordPar_NoAdree,De_WordPar_Close},{De_WordPar_NoAdree,De_WordPar_Close},{De_WordPar_NoAdree,De_WordPar_Close},
		{De_WordPar_NoAdree,De_WordPar_Close},{De_WordPar_NoAdree,De_WordPar_Close},{De_WordPar_NoAdree,De_WordPar_Close},
		{De_WordPar_NoAdree,De_WordPar_Close},{De_WordPar_NoAdree,De_WordPar_Close},{De_WordPar_NoAdree,De_WordPar_Close},
		{De_WordPar_NoAdree,De_WordPar_Close},{De_WordPar_NoAdree,De_WordPar_Close},{De_WordPar_NoAdree,De_WordPar_Close},
		{De_WordPar_NoAdree,De_WordPar_Close},{De_WordPar_NoAdree,De_WordPar_Close},{De_WordPar_NoAdree,De_WordPar_Close},
		{De_WordPar_NoAdree,De_WordPar_Close}
	};
	static const st_Parameter_Table	CN_Ba_st_Parameter_Table=
		{	{De_Devi_ComMod_Gprs,0,0,0},											//׷�ٲ���
			{{255,255},{255,255},{255000,255}},										//����ֵ
			{0,0},																	//����ֵ
			{	{0x02,0x00,0x00,0x00,0x00,0x00,0x00,0x00},							//���ݲ�ѯ��־
				{0x08,0x00,0x00,0x00,0x00,0x00,0x00,0x00}							//ä��������־
			},												//���ݲ�ѯ����
			{0xff,0xffff,30},								//��������
			De_Devi_ComMod_Gprs,							//ͨѶ��ʽ
			1200,											//IP��SMS�л�ʱ��
			De_AppGprs_TakeLcd_No,							//�Ƿ�װ������
			De_AppGprs_LogMess_No,							//��¼�Ƿ���ʾ
			De_AppGprs_TaskVid_No,							//�Ƿ�װ����ͷ
			0xff,											//��������
			10*60											//ԤԼ����ʱ��								
		};
	static const st_Gprs_ComPar	CN_Ba_st_Gprs_ComPar=
		{	{"CMNET","",""},								//APN����
			{0,"v.cheguan.com"},							//�����Ĳ���
			{0,""},											//�����Ĳ���
			{120,40,2,8},									//GPRS��������
			2000											//���Ķ˿ں�
		};//IPͨѶ������
   	static const st_Message_ComPar	CN_Ba_st_Message_ComPar=
		{	{2,60},											//���Ų���
			{"+8613800250500","106380005668",""}			//���ź���
		};//Message��ʽ�µ�ͨѶ����

	static const st_Phone_Basic	CN_Ba_st_Phone_Basic=
		{	"02586306763",""
		}; //�绰�������
	static const st_Phone_Root		CN_Ba_st_Phone_Root=
		{	0xff,"",""};
	static const st_AccTimer	CN_Ba_st_AccTimer=
		{	0
		};//ACC���
	static const st_File_Menum	CN_Ba_st_File_Menum=
		{	0xff,{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0}	
		};
#endif