typedef struct
{	uint16 ID;				//命令ID
	uint16 ContrID;			//中心ID
	uint16 OrderNumber;		//命令序号
	void *Buf;				//命令内容，详细见以下说明
}st_AgreeOn_Agree;
/*==============================================基本协议========================================================*/
/*----------------------------------------------定位指令--------------------------------------------------------*/
	#define De_Agree_Answer_Result_Suc					0				//成功
	#define De_Agree_Answer_Result_Erro					1				//失败
	typedef struct
	{	uint16 Number; 				//应答命令序号
		uint16 ID;					//处理命令ID
		uint8 Result;				//应答结果
	}st_AgreeOn_Agree_Answer;	   	//
/*------------------------------------------------追踪指令------------------------------------------------------*/
	#define De_Agree_Track_ComMod_IP						0			//IP方式通讯
	#define De_Agree_Track_ComMod_Sms						1			//SMS方式通讯
	typedef struct
	{	uint8 ComMod;				//通讯方式
		uint16 AccOpenTimer;		//ACC开时间间隔	s
		uint16 AccCloseTimer;		//ACC关时间间隔	s
		uint16 Space;				//位移		   m
	}st_AgreeOn_Agree_Track;		//
/*------------------------------------------------设定参数------------------------------------------------------*/
	#define De_Agree_Par_Cut_ComMod_IP						0 				//IP方式通讯
	#define De_Agree_Par_Cut_ComMod_Sms						1		   		//SMS方式通讯
	#define De_Agree_Par_Cut_ComMod_NoIpSms					2		   		//IP链路不正常时采用SMS通讯
	#define De_WordPar_Close								0				//对应的工作参数不上传
	#define De_WordPar_Open									1				//对应的工作参数上传
	#define De_WordPar_NoAdree								0xffffffff		//无线传感器无地址
	#define De_Agree_Par_TakeLCD_Yes						1				//安装调度屏
	#define De_Agree_Par_TakeLCD_No							0				//不安装调度屏
	#define De_Agree_Par_LogMess_Yes						1				//回复驾驶员登录
	#define De_Agree_Par_LogMess_No							0				//不回复驾驶员登录
	#define De_Agree_Par_TaskVid_Yes						1 				//安装摄像头
	#define De_Agree_Par_TaskVid_No			 				0				//不安装摄像头
	#define De_AgreeOn_SetPar_Yes							1	   			//本参数本次设置
	#define De_AgreeOn_SetPar_No							0				//本参数本次不设置
	#define De_AgreeOn_Vid_Fun_Close						0
	#define De_AgreeOn_Vid_Fun_Open							1
	/*++++++++++++++++++++++++++++++++++++++修改固定菜单+++++++++++++++++++++++++++++++++++++++++++++++*/
	typedef struct
	{	uint8 ID;				//本菜单ID
		uint8 BackID;			//上一级ID	 当前为根目录时，只填写0
		uint8 Cut[40];			//内容
	}st_AgreeOn_Menum_Infor;	
	typedef struct
	{	uint8 Number;			//本次修改菜单的数量
		st_AgreeOn_Menum_Infor	CN_st_AgreeOn_Menum_Infor[10];
	}st_AgreeOn_AmendMenum;	//

	/*++++++++++++++++++++++++++++++++++++++设置固定电话++++++++++++++++++++++++++++++++++++++++++++++*/
	#define De_Agree_AgreeOn_Phone_State_0		0				//允许呼入，允许呼出
	#define De_Agree_AgreeOn_Phone_State_1		1				//允许呼入,禁止呼出
	#define De_Agree_AgreeOn_Phone_State_2		2				//允许呼出，禁止呼入
	#define De_Agree_AgreeOn_Phone_State_3		3				//禁止呼出，禁止呼入
	typedef struct
	{	uint8 State;   		//电话限制状态
		uint8 Name[10];		//电话名字
		uint8 Phone[15];	//电话号码
	}st_AgreeOn_Phone_Par;
	typedef struct
	{	uint8 Number;	  //电话数量
		st_AgreeOn_Phone_Par	CN_st_AgreeOn_Phone_Par[10];	
	}st_AgreeOn_Phone;		//电话
	/*++++++++++++++++++++++++++++++++++++++设置驾驶员ID+++++++++++++++++++++++++++++++++++++++++++++++++*/
	typedef struct
	{	uint8 ID[10];
		uint8 Phone[15];
	}st_AgreeOn_Driver_Par;
	
	typedef struct
	{	uint8 Number;
	   	st_AgreeOn_Driver_Par	CN_st_AgreeOn_Driver_Par[10];
	}st_AgreeOn_Driver;
	/*+++++++++++++++++++++++++++++++++++++报警值定义+++++++++++++++++++++++++++++++++++++++++++++++++*/
	typedef struct 
	{	uint32 WartingVl;					//报警值	
		uint32 WartingTimer;				//超过此值的时间
	}st_Waring_Par;	
	/*++++++++++++++++++++++++++++++++++++++摄像定义+++++++++++++++++++++++++++++++++++++++++++++++++++*/
	typedef struct
	{	uint8 HelpWarning;		//紧急报警
		uint8 Oper;				//发动机运转
		uint8 TurnOver;			//侧翻
		uint8 AccOpen;			//ACC打开
		uint8 AccClose;			//ACC关闭
	}st_VidType;
	/*--------------------------------------------通话限制状态----------------------------------------------------*/
	typedef struct
	{	uint8 State;
		uint8 Phone[15];
	}st_AgreeOn_ConfineCall;
	/*++++++++++++++++++++++++++++++++++++++各个参数详细定义++++++++++++++++++++++++++++++++++++++++++++*/
	typedef struct
	{	uint16 GreenPar;				//定位终端当前积分  					
		uint8 GreenWord[128];		   	//界面文字
		uint8 ListePhone[15];		   	//监听电话
		uint8 ResetPhone[15];			//电话复位号码
		uint8 CerSevPhone[15];			//短信息服务中心号码
		uint8 CenPhone[128];			//短信中心号码
		uint8 APN[32];					//APN
		uint32 MastIP;					//主IP地址
		uint8 MastDomainName[128];		//主域名
		uint32 ReserveIP;				//副IP地址
		uint8 ReserveDomainName[128];	//副域名
		uint16 CenPort;					//中心端口
		uint8 CentHeart;				//中心下发心跳间隔
		uint8 UseName[32];				//拨号用户名
		uint8 UsePass[32];				//拨号密码
		uint8 DevHeart;					//终端心跳
		uint8 ComMod;					//通信方式见<De_Agree_Par_Cut_ComMod_IP>~<De_Agree_Par_Cut_ComMod_NoIpSms>
		uint8 IPRepeat;					//Ip指令重发次数
		uint8 IPRepeatTime;				//IP指令重发间隔
		uint8 MessageRepeat;			//短信重发次数
		uint8 MessageRepeatTimer;		//短信指令重发间隔
		uint16 IPTransSms;				//IP方式与SMS方式切换间隔
		uint8 DataLog[8];				//数据日志记录设置
		uint8 DataScotomaLog[8];		//盲区补尝数据
		uint8 ParLoad[sizeof(CN_Ba_WordPar)/sizeof(uint16)]; //工作参数上传
		uint32 WireLessPar[sizeof(CN_Ba_LessPar)/sizeof(uint16)]; //无线传感器地址
		uint32 DePassWord; 				//定位终端密码
		uint32 AccTimer;				//ACC累计时间
		uint32 RunLen;					//行驶里程
		uint8 PerPuse;					//车速传感器每周脉冲数量
		uint16 CarFeature;				//车辆特征系数
		uint8 TakeLCD;					//是否安装调度屏
		uint8 OilFrequency;				//油位传感器采样频率
		uint16 SleepTimer;				//ACC关后休眠
		uint16 CloseTimer;				//ACC关后关机
		uint8 LogMess;					//登陆是否提示给驾驶员
		uint8 TaskVid;					//是否安装摄像头
		st_Waring_Par	CN_High_st_Waring_Par;	//超速报警参数
		st_Waring_Par	CN_Low_st_Waring_Par;	//低速报警参数
		st_Waring_Par	CN_Vo_st_Waring_Par;	//低电压报警参数
		st_VidType		CN_st_VidType;			//拍照类型
		uint32 OrderFrmTimer;					//预约订单，精确至秒
		uint8 HardWareEdit[8];					//硬件版本
		uint8 SoftWareEdit[8];					//软件版本
		uint8 MachID[8];						//本机ID
		st_AgreeOn_AmendMenum	CN_st_AgreeOn_AmendMenum; //修改固定菜单
		st_AgreeOn_Phone	CN_st_AgreeOn_Phone;		 //固定电话号码
	    st_AgreeOn_ConfineCall  CN_st_AgreeOn_ConfineCall;//设置通话限制状态
		st_AgreeOn_Driver	CN_st_AgreeOn_Driver;		 //驾驶员
		uint8 DriverID[10];								 //当前驾驶员信息
	}st_AgreeOn_Agree_Par_Cut;	

	/**************************************设定参数输出*********************************************************/

	typedef struct
	{	uint8 ParSet[De_AgreeOn_SetPar_Number];	 			//本参数是否已经设置见<De_AgreeOn_SetPar_Yes>
		st_AgreeOn_Agree_Par_Cut	CN_st_AgreeOn_Agree_Par_Cut;
	}st_AgreeOn_Agree_Par;
/*-----------------------------------------解除报警------------------------------------------------------------*/
	//<内容为空>
/*---------------------------------------------修改固定菜单----------------------------------------------------*/
	//内容见    [设定参数]->[修改固定菜单]
/*-------------------------------------------下发文本调度------------------------------------------------------*/
	typedef struct
	{	uint8 Text[200];
	}st_AgreeOn_LoaderTxt;
	
/*----------------------------------------下发带文本的菜单-----------------------------------------------------*/
	typedef struct
	{	uint8 ID;					//候选答案
		uint8 Cut[40];				//候选内容
	}st_AgreeOn_LoaderTxtMenum_Par;
	typedef struct
	{	uint16 ID;					 //信息ID
		uint8 AnswerNumber;
		uint8 Infor[200];			 //信息内容
		st_AgreeOn_LoaderTxtMenum_Par	CN_st_AgreeOn_LoaderTxtMenum_Par[10];
	}st_AgreeOn_LoaderTxtMenum;
	
/*------------------------------------------设置固定电话------------------------------------------------------*/
	//内容见    [设定参数]->[设置固定电话]	
	
/*--------------------------------------------通话请求--------------------------------------------------------*/
	typedef struct
	{	uint8 Phone[15];
	}st_AgreeOn_CallAnswer;
/*--------------------------------------------软件升级--------------------------------------------------------*/
	#define De_Agree_AgreeOn_UpdateSoftWare_Host					0  			//主机
	#define De_Agree_AgreeOn_UpdateSoftWare_Display					1			//调度屏
	typedef struct
	{	uint8 Device;			//所升级的设备见<De_Agree_AgreeOn_UpdateSoftWare_Host>与<De_Agree_AgreeOn_UpdateSoftWare_Display>
		uint32 IP;			   	//TFTP下载服务器的IP地址
		uint16 Port;			//端口号
		uint8 Use[40];			//用户名
		uint8 Pass[40];			//密码
		uint8 FileName[200];	//文件路径
	}st_AgreeOn_UpdateSoftWare;
/*--------------------------------------------查询参数-------------------------------------------------------*/
	#define De_AgreeOn_LookPar_Yes							1
	#define De_AgreeOn_LookPar_NO							0
	typedef struct
	{	uint8 Par[De_AgreeOn_SetPar_Number];
	}st_AgreeOn_LookPar;
	
/*---------------------------------------------远程控制------------------------------------------------------*/
	#define De_AgreeOn_Contrl_Open							1		//控制
	#define De_AgreeOn_Contrl_Close							3		//解除控制
	typedef struct
	{	uint8 Contr0;
		uint8 Contr1;
		uint8 Contr2;
	}st_AgreeOn_Contrl;
	

/*--------------------------------------------配置中心服务器--------------------------------------------------*/	
	typedef struct
	{	uint8 APN[32];					
		uint32 IP;
		uint16 Port;
	}st_AgreeOn_ConfigCentrSever;
/*--------------------------------------------激活定位终端----------------------------------------------------*/
	typedef struct
	{	uint32 PassWord;
	}st_AgreeOn_Activation;


/*====================================================扩展协议==================================================*/
	
/*---------------------------------------------查询指定类型的照片---------------------------------------------*/
	typedef struct
	{	st_VidType	CN_st_VidType;			//查询拍照类型
		uint8 WorkPar;						//拍照时的工作参数
		uint8 StartDate[4];					//开始日期
		uint8 EndDate[4];					//结束日期
	}st_AgreeOn_LookJpg;				   	//
/*------------------------------------------------查询实时照片------------------------------------------------*/
	#define De_st_AgreeOn_JpgIng_Contrl_End					1
	#define De_st_AgreeOn_JpgIng_Contrl_Start				0					
	typedef struct
	{	uint8 Contrl;						//开始上传
		uint8 VidTimer;						//拍摄间隔
		uint16 LoadNumber;					//上传张数
	}st_AgreeOn_JpgIng;						//
	/*------------------------------------------设置拍照类型--------------------------------------------------*/
	#define De_AgreeOn_SetVidType_Type_Stop						0 			//停止拍照
	#define De_AgreeOn_SetVidType_Type_Number					1			//数值拍照
	#define De_AgreeOn_SetVidType_Type_NumberCut				2			//数值范围内拍照
	#define De_AgreeOn_SetVidType_Type_No						3			//内容无效
	typedef struct
	{	uint32 Addree;
		uint8 OpenOrClose;
		uint8 State;
	}st_AgreeOn_Less_Switch;
	typedef struct
	{	uint32 Addree;
		int32 Temp;
		uint8 State;
	}st_AgreeOn_Less_Temp;
	typedef struct
	{	uint8 Switch1;
		uint8 Switch2;
		uint8 Switch3;
		uint8 Switch4;
		uint8 Switch5;
		uint8 Switch6;
		uint8 Switch7;
		uint8 Switch8;
		uint8 Switch9;
		uint8 Switch10;
		uint8 Switch11;
		uint8 Switch12;
		uint8 Switch13;
		uint8 Switch14;
		uint8 Switch15;
		uint8 Switch16;
		st_AgreeOn_Less_Switch CN_Less_Switch1;
		st_AgreeOn_Less_Switch CN_Less_Switch2;
		st_AgreeOn_Less_Switch CN_Less_Switch3;
		st_AgreeOn_Less_Switch CN_Less_Switch4;
		st_AgreeOn_Less_Switch CN_Less_Switch5;
		st_AgreeOn_Less_Switch CN_Less_Switch6;
		uint32 AccTimer;
		uint32 Mileage;
		uint16 Oil1;
		uint8 Sem;
		uint32 SendOilTimer;
		int32 Temp;
		uint16 Oil2;
		uint32 Pulse;
		uint16 Humidity;
		uint8 OilBaifen;
		st_AgreeOn_Less_Temp CN_st_AgreeOn_Less_Temp1;
		st_AgreeOn_Less_Temp CN_st_AgreeOn_Less_Temp2;
		st_AgreeOn_Less_Temp CN_st_AgreeOn_Less_Temp3;
		st_AgreeOn_Less_Temp CN_st_AgreeOn_Less_Temp4;
	}st_AgreeOn_SetVidType_Par;
	
	
	typedef struct
	{	uint8 Type[sizeof(CN_Ba_WordPar)/sizeof(uint16)];
		st_AgreeOn_SetVidType_Par	CN_st_AgreeOn_SetVidType_Par[2]; 	
	}st_AgreeOn_SetVidType;

/*------------------------------------------------表单设置------------------------------------------------------*/
	typedef struct
	{	uint8 ID;					//输入项ID
		uint8 Type;					//输入项类型
		uint8 Select;				//输入选择
		uint8 Name[40];				//输入项名称
		uint8 InputID[10];			//输入项的ID
		uint8 SelectName[10][40];	//输入项各项命令
	}st_AgreeOn_Tabel_Input;
	
	typedef struct
	{ 	uint8 DateTime[7];
		uint8 SumNumber;  			//总段数
		uint8 Number;				//本次段数
		uint32 TabelID;
		uint32 BackID;
		uint8 Name[40];
		st_AgreeOn_Tabel_Input	CN_st_AgreeOn_Tabel_Input[3];
	}st_AgreeOn_TabelList;
/*--------------------------------------------查询工作参数------------------------------------------------------*/
	//<内容为空>	
/*---------------------------------按照固定时间上传工作参数------------------------------------------------------*/
	typedef struct
	{	uint8 Com;
		uint8 Number;
		uint8 Timer[10][3];	
	}st_AgreeOn_WorkParTimer;
	
/*-------------------------------------按照间隔上传工作参数-----------------------------------------------------*/
	typedef struct
	{	uint8 Com;
		uint32 AccOpenTimer;
		uint32 AccCloseTimer;
		uint32 Space;
	}st_AgreeOn_WorkParSpace;
/*----------------------------------------查询日志文件---------------------------------------------------------*/
	#define De_AgreeOn_LookLog_Type_Track							1			//追踪采纳数存储间隔
	#define De_AgreeOn_LookLog_Type_WorkPar							2			//工作参数上传间隔
	#define De_AgreeOn_LookLog_Type_Pone							3			//存储照片
	#define De_AgreeOn_LookLog_Type_Reduce							4			//压缩数据
	typedef struct
	{	uint8 Type;
		uint8 StartDateTimer[7];
		uint8 EndDateTimer[7];
	}st_AgreeOn_LookLog;
/*--------------------------------------------设置报警条件----------------------------------------------------*/
	#define De_AgreeOn_SetWaringTerm_Type_Stop						0 			//停止报警
	#define De_AgreeOn_SetWaringTerm_Type_Number					1			//数值报警
	#define De_AgreeOn_SetWaringTerm_Type_NumberCut					2			//数值范围内报警
	#define De_AgreeOn_SetWaringTerm_Type_No						3			//无报警
	typedef struct
	{ 	uint8 Type[sizeof(CN_Ba_WordPar)/sizeof(uint16)];
		st_AgreeOn_SetVidType_Par	CN_st_AgreeOn_SetVidType_Par[2];
	}st_AgreeOn_SetWaringTerm;	
/*---------------------------------------------查询报警条件--------------------------------------------------*/
	//<内容为空>	


/*=================================================物流协议专用==============================================*/
/*---------------------------------------------设置圆形路线--------------------------------------------------*/	
	typedef struct
	{	uint16 ID;
		uint16 Pro;
		uint32 Latitude;	//维度
		uint32 Longitude;
		uint32 PI;
		uint8 StartTimer[3];
		uint8 EndTimer[4];
		uint8 HighSpeed;
		uint16 HighSpeedTimer;
	}st_AgreeOn_SetRound_Par;
	
	
	typedef struct
	{	uint16 Number;
		st_AgreeOn_SetRound_Par	CN_st_AgreeOn_SetRound_Par[5];
	}st_AgreeOn_SetRound;
/*--------------------------------------删除圆形路线-----------------------------------------------------------*/
	typedef struct
	{	uint16 Number;
		uint16 ID[100];
	}st_AgreeOn_DelRound;
	
/*---------------------------------------------------设置矩形路线----------------------------------------------*/
	typedef struct
	{	uint16 ID;
		uint8 Pro;
		uint32 Latitude[2];
		uint32 Longitude[2];
		uint8 StartTimer[3];
		uint8 EndTimer[3];
		uint8 HighSpeed;
		uint16 HighSpeedTimer;
	}st_AgreeOn_SetRectangle_Par;
	
	typedef struct
	{	uint16 Number;
		st_AgreeOn_SetRectangle_Par	CN_st_AgreeOn_SetRectangle_Par[5];
	}st_AgreeOn_SetRectangle;
/*--------------------------------------删除圆形路线-----------------------------------------------------------*/
	typedef struct
	{	uint16 Number;
		uint16 ID[100];
	}st_AgreeOn_DelRectangle;
	
/*------------------------------------------设置多边形路线----------------------------------------------------*/
	typedef struct
	{	uint16 ID;
	   	uint16 Pro;
		uint16 Number;
		uint32 Latitude[100];
		uint32 Longitude[100];
		uint8 StartTimer[3];
		uint8 EndTimer[4];
		uint8 HighSpeed;
		uint16 HighSpeedTimer;
	}st_AgreeOn_SetPolygon;
	
/*--------------------------------------删除多边形路线-----------------------------------------------------------*/
	typedef struct
	{	uint16 Number;
		uint16 ID[100];
	}st_AgreeOn_DelPolygon;
	
/*--------------------------------------设置路线区域-----------------------------------------------------------*/
	typedef struct
	{	uint16 ID;
		uint16 Pro;
		uint8 StartTimer[3];
		uint8 EndTimer[3]; 
		uint8 HighSpeed;
		uint16 HighSpeedTimer;
		uint16 Height;
		uint16 Number;
		uint8 SumSec;
		uint8 NonSec;
		uint32 Latitude[100];
		uint32 Longitude[100];
	}st_AgreeOn_SetRoadMap;
	
/*-----------------------------------------删除路线区域----------------------------------------------------------*/
	typedef struct
	{	uint16 Number;
		uint16 ID[100];
	}st_AgreeOn_DelRoadMap;
	
/*---------------------------------------设置压缩回传-----------------------------------------------------------*/
	#define De_AgreeOn_Reduce_Data_Space					0x00				//定位数据
	#define De_AgreeOn_Reduce_Data_WordSpace				0x01				//带工作参数定位数据	
	typedef struct
	{	uint8 Data;
		uint8 AccOpenTimer;
		uint8 AccCloseTimer;
		uint8 Space;
		uint16 Number;
	}st_AgreeOn_Reduce;
	
/*---------------------------------------设置驾驶员ID-----------------------------------------------------------*/
	//内容见    [设定参数]->[设置驾驶员ID]	
	
/*---------------------------------------中心导航--------------------------------------------------------------*/
	typedef struct
	{	uint32 Latitude;
		uint32 Longitude;
		uint32 State;
	}st_AgreeOn_Navigation_Par;
	typedef struct
	{	uint8 DateTimer[7];
		uint8 Number;
		uint8 Text[256];
		st_AgreeOn_Navigation_Par	CN_st_AgreeOn_Navigation_Par[100]; 
	}st_AgreeOn_Navigation;
	
/*--------------------------------------------手机文本调度---------------------------------------------------*/
	typedef struct
	{	uint8 Buf[200];
	}st_AgreeOn_HandTxt;
	
/*------------------------------------------手机调度信息---------------------------------------------------*/
	typedef struct
	{	uint16 ID;
		uint8 Buf[200];
	}st_AgreeOn_HandAttemper;
	
	
/*============================================出租车辆专用协议==================================================*/
	/*------------------------------------------修改订单信息---------------------------------------------------*/
	typedef struct
	{	uint8 ID;	
		uint8 Cut[40];
	}st_AgreeOn_AmendForm_Par;
	typedef struct
	{ 	uint8 Number;
		st_AgreeOn_AmendForm_Par	CN_st_AgreeOn_AmendForm_Par[30];
	}st_AgreeOn_AmendForm;
	/*------------------------------------------下发订单抢答信息------------------------------------------*/
	typedef struct
	{	uint8 Type;
		uint16 ID;
		uint8 DateTimer[7];
		uint8 Cut[200];	
	}st_AgreeOn_UpLoaderForm;
	
	/*---------------------------------------下发订单抢答成功信息------------------------------------------------*/
	typedef struct
	{	uint16 ID;
		uint8 Phone[15];
		uint8 Cut[200];
	}st_AgreeOn_UpLoaderFormSuc;
	
	/*--------------------------------------------下发订单抢答失败信息-------------------------------------------*/
	typedef struct
	{	uint16 ID;
	}st_AgreeOn_UpLoaderFormErro;
	
	/*--------------------------------------------下发订单取消信息--------------------------------------------*/
	typedef struct
	{	uint16 ID;
	}st_AgreeOn_UpLoaderCan;
	
/*=========================================发送部分数据结构类型==================================================*/	

	
						
			
						
	
	
