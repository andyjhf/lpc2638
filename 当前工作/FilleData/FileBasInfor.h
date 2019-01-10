#ifdef De_FileData_Compiler
/*=======================================文件基本信息表=========================================================*/
	static const st_File_Basic		CN_Ba_st_File_Basic=
	{ 	{'W','V','1','.','0','0',0X00,0X00},										//软件版本号
		{'V','2','.','3',0,0,0,0},													//硬件版本号
		{'8','8','8','8','8','8','8','8','8','8','8','8','8','8','8','8'},			//机器编号
		{0x88,0x88,0x88,0x88,0x88,0x88,0x88},										//卡号
		{0,3},																		//机器技术状态
		{0,2}																		//厂家代号
	};
/*=====================================驾驶员基本信息表===========================================================*/	
	static const st_Emplo_Basic	CN_Ba_st_Emplo_Basic={	0,"","","",""	};			//驾驶员ID
/*==========================================界面类文字===========================================================*/
	static const st_File_GreenPar	 CN_Ba_st_File_GreenPar={"a",0,111111 };		
/*=========================================工作参数表===========================================================*/
	static const st_File_WorkPar	CN_Ba_st_File_WorkPar=
	{	{	
			{De_WordPar_NoAdree,De_WordPar_Close},				//开关量1
			{De_WordPar_NoAdree,De_WordPar_Close},				//开关量2
			{De_WordPar_NoAdree,De_WordPar_Close},				//开关量3
			{De_WordPar_NoAdree,De_WordPar_Close},				//开关量4
			{De_WordPar_NoAdree,De_WordPar_Close},				//开关量5
			{De_WordPar_NoAdree,De_WordPar_Close},				//开关量6
			{De_WordPar_NoAdree,De_WordPar_Close},				//开关量7
			{De_WordPar_NoAdree,De_WordPar_Close},				//开关量8
			{De_WordPar_NoAdree,De_WordPar_Close},				//开关量9
			{De_WordPar_NoAdree,De_WordPar_Close},				//开关量10
			{De_WordPar_NoAdree,De_WordPar_Close},				//开关量11
			{De_WordPar_NoAdree,De_WordPar_Close},				//开关量12
			{De_WordPar_NoAdree,De_WordPar_Close},				//开关量13
			{De_WordPar_NoAdree,De_WordPar_Close},				//开关量14
			{De_WordPar_NoAdree,De_WordPar_Close},				//开关量15
			{De_WordPar_NoAdree,De_WordPar_Close},				//开关量16
			{0x33333333,De_WordPar_Close},				//无线开关量1
			{De_WordPar_NoAdree,De_WordPar_Close},				//无线开关量2
			{De_WordPar_NoAdree,De_WordPar_Close},				//无线开关量3
			{De_WordPar_NoAdree,De_WordPar_Close},				//无线开关量4
			{De_WordPar_NoAdree,De_WordPar_Close},				//无线开关量5
			{De_WordPar_NoAdree,De_WordPar_Close},				//无线开关量6
			{De_WordPar_NoAdree,De_WordPar_Open},				//ACC累计时间
			{De_WordPar_NoAdree,De_WordPar_Close},				//里程统计
			{De_WordPar_NoAdree,De_WordPar_Open},				//油箱油位1
			{De_WordPar_NoAdree,De_WordPar_Open},				//GSM信号强度
			{De_WordPar_NoAdree,De_WordPar_Close},				//喷油累计时间
			{De_WordPar_NoAdree,De_WordPar_Close},				//温度
			{De_WordPar_NoAdree,De_WordPar_Close},				//油箱油位2
			{De_WordPar_NoAdree,De_WordPar_Close},				//脉冲个数
			{De_WordPar_NoAdree,De_WordPar_Close},				//湿度
			{De_WordPar_NoAdree,De_WordPar_Close},				//油箱油位百分比
			{0x11111111,De_WordPar_Close},				//无线传感器温度1
			{De_WordPar_NoAdree,De_WordPar_Close},				//无线传感器温度2
			{De_WordPar_NoAdree,De_WordPar_Close},				//无线传感器温度3
			{De_WordPar_NoAdree,De_WordPar_Close}				//无线传感器温度4
		}
	}; 
/*=========================================基本参数配置表=======================================================*/
	static const st_Parameter_Table	CN_Ba_st_Parameter_Table=
	{	{De_Agree_Track_ComMod_IP,0,0,0},										//追踪参数
		{De_Agree_Track_ComMod_IP,0,0,0},										//工作参数追踪参数
		{{255,255},{255,255},{255000,255}},										//报警值
		{0,0},																	//休眠值
		{	{0x02,0x00,0x00,0x00,0x00,0x00,0x00,0x00},							//数据查询日志
			{0x08,0x00,0x00,0x00,0x00,0x00,0x00,0x00}							//盲区补偿日志
		},																		//数据查询类型
		{0xff,0xffff,30},														//车辆参数
		{De_Agree_AgreeOn_Phone_State_0,"*"}, 									//任何电话
		{De_st_AgreeOn_JpgIng_Contrl_Start,0,10},
		De_Agree_Par_Cut_ComMod_IP,												//通讯方式
		1200,																	//IP与SMS切换时间
		De_Agree_Par_TakeLCD_No,												//是否安装调度屏
		De_Agree_Par_LogMess_No,												//登录是否提示
		De_Agree_Par_TaskVid_Yes,
		De_st_Parameter_Table_HelpWaring_No,
		De_st_Parameter_Table_Contrl_No,
		{De_AgreeOn_Vid_Fun_Close,De_AgreeOn_Vid_Fun_Close,De_AgreeOn_Vid_Fun_Close,De_AgreeOn_Vid_Fun_Open,De_AgreeOn_Vid_Fun_Open},	//是否拍照																	//拍照类型
		10*60																	//预约订单时间								
	};
/*======================================IP通讯参数表===========================================================*/
	static const st_Gprs_ComPar	CN_Ba_st_Gprs_ComPar=
	{	{"CMNET","",""},								//APN参数
		{0,"v.cheguan.com"},							//主中心参数
		{0,""},											//副中心参数
		{120,40,2,8},									//GPRS基本参数
		2000											//中心端口号
	};//IP通讯参数表
/*========================================Message方式下的通讯参数==============================================*/
	static const st_Message_ComPar	CN_Ba_st_Message_ComPar=
	{	{2,60},											//短信参数
		{"+8613800250500","106380005668",""}			//短信号码
	};//Message方式下的通讯参数	
/*=============================================电话类参数表===================================================*/
	static const st_Phone_Basic	CN_Ba_st_Phone_Basic=
	{	"02586306763",""
	}; //电话类参数表	
/*=============================================固定电话号码===================================================*/
	static const st_AgreeOn_Phone_Par		CN_Ba_st_Phone_Root=
	{	0xff,"",""};
/*==============================================ACC===========================================================*/
		static const st_AccTimer	CN_Ba_st_AccTimer=
		{	0
		};//ACC里程
/*==============================================菜单信息======================================================*/
	static const st_File_Menum	CN_Ba_st_File_Menum=
		{	0xff,{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0}	
		};
#endif
