#ifdef De_FileData_Compiler
/*=======================================�ļ�������Ϣ��=========================================================*/
	static const st_File_Basic		CN_Ba_st_File_Basic=
	{ 	{'W','V','1','.','0','0',0X00,0X00},										//����汾��
		{'V','2','.','3',0,0,0,0},													//Ӳ���汾��
		{'8','8','8','8','8','8','8','8','8','8','8','8','8','8','8','8'},			//�������
		{0x88,0x88,0x88,0x88,0x88,0x88,0x88},										//����
		{0,3},																		//��������״̬
		{0,2}																		//���Ҵ���
	};
/*=====================================��ʻԱ������Ϣ��===========================================================*/	
	static const st_Emplo_Basic	CN_Ba_st_Emplo_Basic={	0,"","","",""	};			//��ʻԱID
/*==========================================����������===========================================================*/
	static const st_File_GreenPar	 CN_Ba_st_File_GreenPar={"a",0,111111 };		
/*=========================================����������===========================================================*/
	static const st_File_WorkPar	CN_Ba_st_File_WorkPar=
	{	{	
			{De_WordPar_NoAdree,De_WordPar_Close},				//������1
			{De_WordPar_NoAdree,De_WordPar_Close},				//������2
			{De_WordPar_NoAdree,De_WordPar_Close},				//������3
			{De_WordPar_NoAdree,De_WordPar_Close},				//������4
			{De_WordPar_NoAdree,De_WordPar_Close},				//������5
			{De_WordPar_NoAdree,De_WordPar_Close},				//������6
			{De_WordPar_NoAdree,De_WordPar_Close},				//������7
			{De_WordPar_NoAdree,De_WordPar_Close},				//������8
			{De_WordPar_NoAdree,De_WordPar_Close},				//������9
			{De_WordPar_NoAdree,De_WordPar_Close},				//������10
			{De_WordPar_NoAdree,De_WordPar_Close},				//������11
			{De_WordPar_NoAdree,De_WordPar_Close},				//������12
			{De_WordPar_NoAdree,De_WordPar_Close},				//������13
			{De_WordPar_NoAdree,De_WordPar_Close},				//������14
			{De_WordPar_NoAdree,De_WordPar_Close},				//������15
			{De_WordPar_NoAdree,De_WordPar_Close},				//������16
			{0x33333333,De_WordPar_Close},				//���߿�����1
			{De_WordPar_NoAdree,De_WordPar_Close},				//���߿�����2
			{De_WordPar_NoAdree,De_WordPar_Close},				//���߿�����3
			{De_WordPar_NoAdree,De_WordPar_Close},				//���߿�����4
			{De_WordPar_NoAdree,De_WordPar_Close},				//���߿�����5
			{De_WordPar_NoAdree,De_WordPar_Close},				//���߿�����6
			{De_WordPar_NoAdree,De_WordPar_Open},				//ACC�ۼ�ʱ��
			{De_WordPar_NoAdree,De_WordPar_Close},				//���ͳ��
			{De_WordPar_NoAdree,De_WordPar_Open},				//������λ1
			{De_WordPar_NoAdree,De_WordPar_Open},				//GSM�ź�ǿ��
			{De_WordPar_NoAdree,De_WordPar_Close},				//�����ۼ�ʱ��
			{De_WordPar_NoAdree,De_WordPar_Close},				//�¶�
			{De_WordPar_NoAdree,De_WordPar_Close},				//������λ2
			{De_WordPar_NoAdree,De_WordPar_Close},				//�������
			{De_WordPar_NoAdree,De_WordPar_Close},				//ʪ��
			{De_WordPar_NoAdree,De_WordPar_Close},				//������λ�ٷֱ�
			{0x11111111,De_WordPar_Close},				//���ߴ������¶�1
			{De_WordPar_NoAdree,De_WordPar_Close},				//���ߴ������¶�2
			{De_WordPar_NoAdree,De_WordPar_Close},				//���ߴ������¶�3
			{De_WordPar_NoAdree,De_WordPar_Close}				//���ߴ������¶�4
		}
	}; 
/*=========================================�����������ñ�=======================================================*/
	static const st_Parameter_Table	CN_Ba_st_Parameter_Table=
	{	{De_Agree_Track_ComMod_IP,0,0,0},										//׷�ٲ���
		{De_Agree_Track_ComMod_IP,0,0,0},										//��������׷�ٲ���
		{{255,255},{255,255},{255000,255}},										//����ֵ
		{0,0},																	//����ֵ
		{	{0x02,0x00,0x00,0x00,0x00,0x00,0x00,0x00},							//���ݲ�ѯ��־
			{0x08,0x00,0x00,0x00,0x00,0x00,0x00,0x00}							//ä��������־
		},																		//���ݲ�ѯ����
		{0xff,0xffff,30},														//��������
		{De_Agree_AgreeOn_Phone_State_0,"*"}, 									//�κε绰
		{De_st_AgreeOn_JpgIng_Contrl_Start,0,10},
		De_Agree_Par_Cut_ComMod_IP,												//ͨѶ��ʽ
		1200,																	//IP��SMS�л�ʱ��
		De_Agree_Par_TakeLCD_No,												//�Ƿ�װ������
		De_Agree_Par_LogMess_No,												//��¼�Ƿ���ʾ
		De_Agree_Par_TaskVid_Yes,
		De_st_Parameter_Table_HelpWaring_No,
		De_st_Parameter_Table_Contrl_No,
		{De_AgreeOn_Vid_Fun_Close,De_AgreeOn_Vid_Fun_Close,De_AgreeOn_Vid_Fun_Close,De_AgreeOn_Vid_Fun_Open,De_AgreeOn_Vid_Fun_Open},	//�Ƿ�����																	//��������
		10*60																	//ԤԼ����ʱ��								
	};
/*======================================IPͨѶ������===========================================================*/
	static const st_Gprs_ComPar	CN_Ba_st_Gprs_ComPar=
	{	{"CMNET","",""},								//APN����
		{0,"v.cheguan.com"},							//�����Ĳ���
		{0,""},											//�����Ĳ���
		{120,40,2,8},									//GPRS��������
		2000											//���Ķ˿ں�
	};//IPͨѶ������
/*========================================Message��ʽ�µ�ͨѶ����==============================================*/
	static const st_Message_ComPar	CN_Ba_st_Message_ComPar=
	{	{2,60},											//���Ų���
		{"+8613800250500","106380005668",""}			//���ź���
	};//Message��ʽ�µ�ͨѶ����	
/*=============================================�绰�������===================================================*/
	static const st_Phone_Basic	CN_Ba_st_Phone_Basic=
	{	"02586306763",""
	}; //�绰�������	
/*=============================================�̶��绰����===================================================*/
	static const st_AgreeOn_Phone_Par		CN_Ba_st_Phone_Root=
	{	0xff,"",""};
/*==============================================ACC===========================================================*/
		static const st_AccTimer	CN_Ba_st_AccTimer=
		{	0
		};//ACC���
/*==============================================�˵���Ϣ======================================================*/
	static const st_File_Menum	CN_Ba_st_File_Menum=
		{	0xff,{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0}	
		};
#endif
