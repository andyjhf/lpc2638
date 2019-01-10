	#define De_Devi_ComMod_Gprs										0						//Ip通讯方式
	#define De_Devi_ComMod_Sms										1						//短信通讯方式
	#define De_AppGprs_TakeLcd_Yes									1						//安装调度屏
	#define De_AppGprs_TakeLcd_No									0						//不安装调度屏
	#define De_AppGprs_LogMess_Yes									1						//登录提示
	#define De_AppGprs_LogMess_No									0						//登录不提示
	#define De_AppGprs_TaskVid_Yes									1						//安装摄像头
	#define De_AppGprs_TaskVid_No									0						//不安装摄像头
	#define De_File_Phone_Pro_OutIn									0						//允许呼入允许呼出
	#define De_File_Phone_Pro_InNoOut								1						//允许呼入不允许呼出
	#define De_File_Phone_Pro_OutNoIn								2						//允许呼出不允许呼入
	#define De_File_Phone_Pro_NoOutNoIn								3						//不允许呼出不允许呼入
	#define De_WordPar_Open											0 		
	#define De_WordPar_Close										1
	#define De_WordPar_NoAdree										0xffffffff
#ifdef De_FileData_Compiler
/*============================================工作参数表==========================================================*/
		 
/*==========================================文件基本信息表======================================================*/
	static const st_File_Basic		CN_Ba_st_File_Basic=
	{ 	{'W','V','1','.','0','0',0X00,0X00},										//软件版本号
		{'V','2','.','3',0,0,0,0},													//硬件版本号
		{'8','8','8','8','8','8','8','8','8','8','8','8','8','8','8','8'},			//机器编号
		{0x88,0x88,0x88,0x88,0x88,0x88,0x88},										//卡号
		{0,3},																		//机器技术状态
		{0,2}																		//厂家代号
	};
/*==========================================文件基本信息表=====================================================*/
	static const st_Emplo_Basic	CN_Ba_st_Emplo_Basic={	0,"","","",""	};				//驾驶员ID
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
		{	{De_Devi_ComMod_Gprs,0,0,0},											//追踪参数
			{{255,255},{255,255},{255000,255}},										//报警值
			{0,0},																	//休眠值
			{	{0x02,0x00,0x00,0x00,0x00,0x00,0x00,0x00},							//数据查询日志
				{0x08,0x00,0x00,0x00,0x00,0x00,0x00,0x00}							//盲区补偿日志
			},												//数据查询类型
			{0xff,0xffff,30},								//车辆参数
			De_Devi_ComMod_Gprs,							//通讯方式
			1200,											//IP与SMS切换时间
			De_AppGprs_TakeLcd_No,							//是否安装调度屏
			De_AppGprs_LogMess_No,							//登录是否提示
			De_AppGprs_TaskVid_No,							//是否安装摄像头
			0xff,											//拍照类型
			10*60											//预约订单时间								
		};
	static const st_Gprs_ComPar	CN_Ba_st_Gprs_ComPar=
		{	{"CMNET","",""},								//APN参数
			{0,"v.cheguan.com"},							//主中心参数
			{0,""},											//副中心参数
			{120,40,2,8},									//GPRS基本参数
			2000											//中心端口号
		};//IP通讯参数表
   	static const st_Message_ComPar	CN_Ba_st_Message_ComPar=
		{	{2,60},											//短信参数
			{"+8613800250500","106380005668",""}			//短信号码
		};//Message方式下的通讯参数

	static const st_Phone_Basic	CN_Ba_st_Phone_Basic=
		{	"02586306763",""
		}; //电话类参数表
	static const st_Phone_Root		CN_Ba_st_Phone_Root=
		{	0xff,"",""};
	static const st_AccTimer	CN_Ba_st_AccTimer=
		{	0
		};//ACC里程
	static const st_File_Menum	CN_Ba_st_File_Menum=
		{	0xff,{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0}	
		};
#endif