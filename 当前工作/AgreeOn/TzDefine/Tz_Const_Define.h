/*=======================================支持参数定义表==========================================================*/
#define De_Debug_h	
	typedef struct
	{	uint16 Par;
		uint8 Number;
	}st_AgreenOn_Par2Type; 
	#define De_CN_Ba_st_AgreenOn_Par2Type_Number   						51						//参数数量
	#define De_CN_Ba_WordPar_Number										36						//工作参数数量
	#define De_CN_Ba_LessPar_Number										10						//无线传感器数量

#ifdef De_TzV2_Compiler	
	const st_AgreenOn_Par2Type	CN_Ba_st_AgreenOn_Par2Type[De_CN_Ba_st_AgreenOn_Par2Type_Number]=
	{	{	De_SetPar_SetGreenPar,De_AgreeOn_SetPar_State_SetGreenPar},						//设置
		{	De_SetPar_SetGreenWord,De_AgreeOn_SetPar_State_SetGreenWord},					//设置界面文字
		{	De_SetPar_SetListePhone,De_AgreeOn_SetPar_State_SetListePhone},					//设置监听号码							
		{	De_SetPar_SetResetPhone,De_AgreeOn_SetPar_State_SetResetPhone},					//设置电话复位
		{	De_SetPar_SetCerSevPhone,De_AgreeOn_SetPar_State_SetCerSevPhone}, 				//设置短信中心服务号码
		{	De_SetPar_SetCenPhone,De_AgreeOn_SetPar_State_SetCenPhone},						//设置短信中心
		{	De_SetPar_SetAPN,De_AgreeOn_SetPar_State_SetAPN},								//设置APN参数
		{	De_SetPar_SetMastIP,De_AgreeOn_SetPar_State_SetMastIP},							//设置主中心IP
		{	De_SetPar_SetMastDomainName,De_AgreeOn_SetPar_State_SetMastDomainName},			//设置主域名
		{	De_SetPar_SetReserveIP,De_AgreeOn_SetPar_State_SetReserveIP},					//设置副中心IP
		{	De_SetPar_SetReserveDomainName,De_AgreeOn_SetPar_State_SetReserveDomainName},	//设置设置副域名
		{	De_SetPar_SetCenPort,De_AgreeOn_SetPar_State_SetCenPort},						//设置中心端口号
		{	De_SetPar_SetCentHeart,De_AgreeOn_SetPar_State_SetCentHeart},					//中心下发心跳间隔
		{	De_SetPar_SetUseName,De_AgreeOn_SetPar_State_SetUseName},						//设置用户名
		{	De_SetPar_SetUsePass,De_AgreeOn_SetPar_State_SetUsePass},						//设置拨号密码
		{	De_SetPar_SetDevHeart,De_AgreeOn_SetPar_State_SetDevHeart},						//终端上发心跳间隔
		{	De_SetPar_SetComMod,De_AgreeOn_SetPar_State_SetComMod},							//设置通讯方式
		{	De_SetPar_SetIPRepeat,De_AgreeOn_SetPar_State_SetIPRepeat},						//Ip关键指令重发次数
		{	De_SetPar_SetIPRepeatTime,De_AgreeOn_SetPar_State_SetIPRepeatTime},				//IP关键指令重发间隔时间
		{	De_SetPar_SetMessageRepeat,De_AgreeOn_SetPar_State_SetMessageRepeat},			//Message关键指令重发次数
		{	De_SetPar_SetMessageRepeatTimer,De_AgreeOn_SetPar_State_SetMessageRepeatTimer},	//Message Timer 重发时间
		{	De_SetPar_SetIPTransSms,De_AgreeOn_SetPar_State_SetIPTransSms},					//Message与IP之间切换时间
		{	De_SetPar_SetDataLog,De_AgreeOn_SetPar_State_SetDataLog},						//数据日志存储
		{	De_SetPar_SetDataScotomaLog,De_AgreeOn_SetPar_State_SetDataScotomaLog},			//盲区补偿数据
		{	De_SetPar_SetParLoad,De_AgreeOn_SetPar_State_SetParLoad},						//设置上传参数
		{	De_SetPar_SetWireLessPar,De_AgreeOn_SetPar_State_SetWireLessPar},				//设置无线参数
		{	De_SetPar_SetDePassWord,De_AgreeOn_SetPar_State_SetDePassWord},					//设置终端密码
		{	De_SetPar_ComFac,De_AgreeOn_SetPar_State_SetComFac},							//回复出厂值
		{	De_SetPar_SetAccTimer,De_AgreeOn_SetPar_State_SetAccTimer},						//设置ACC累计时间
		{	De_SetPar_SetRunLen,De_AgreeOn_SetPar_State_SetRunLen},							//设置运行里程
		{	De_SetPar_SetPerPuse,De_AgreeOn_SetPar_State_SetPerPuse},						//设置每周的脉冲数
		{	De_SetPar_SetCarFeature,De_AgreeOn_SetPar_State_SetCarFeature},					//设置车辆特征
		{	De_SetPar_SetTakeLCD,De_AgreeOn_SetPar_State_SetTakeLCD},						//设置车辆是否安装调度
		{	De_SetPar_SetOilFrequency,De_AgreeOn_SetPar_State_SetOilFrequency},				//设置油量采样频率
		{	De_SetPar_SetSleepTimer,De_AgreeOn_SetPar_State_SetSleepTimer},					//设置休眠时间
		{	De_SetPar_SetCloseTimer,De_AgreeOn_SetPar_State_SetCloseTimer},					//设置关机时间
		{	De_SetPar_SetLogMess,De_AgreeOn_SetPar_State_SetLogMess},						//设置登录提示	
		{	De_SetPar_SetTaskVid,De_AgreeOn_SetPar_State_SetTaskVid},						//设置是否安装摄像头
		{	De_SetPar_SetHighSpeed,De_AgreeOn_SetPar_State_SetHighSpeed},					//设置超速报警
		{	De_SetPar_SetLowSpeed,De_AgreeOn_SetPar_State_SetLowSpeed},						//设置低速报警
		{	De_SetPar_SetLowVlt,De_AgreeOn_SetPar_State_SetLowVlt},							//设置低电压报警
		{	De_SetPar_SetVidType,De_AgreeOn_SetPar_State_SetVidType},						//设置拍照类型
		{	De_SetPar_SetOrderFrmTimer,De_AgreeOn_SetPar_State_SetOrderFrmTimer},			//设置预约订单时间
		{	De_SetPar_HardWareEdit,De_AgreeOn_SetPar_State_SetHardWareEdit},				//查询硬件版本
		{	De_SetPar_SoftWareEdit,De_AgreeOn_SetPar_State_SetSoftWareEdit},				//查询软件版本
		{	De_SetPar_MachID,De_AgreeOn_SetPar_State_SetMachID},							//查询机器编号
		{	De_SetPar_Menum,De_AgreeOn_SetPar_State_SetMenum},								//查询菜单信息
		{	De_SetPar_Phone,De_AgreeOn_SetPar_State_SetPhone},								//查询固定电话信息
		{	De_SetPar_ConfineCall,De_AgreeOn_SetPar_State_SetConfineCall},					//查询通话限制状态
		{	De_SetPar_DriverID,De_AgreeOn_SetPar_State_SetDriverID},						//查询驾驶员
		{	De_SetPar_DriverLogin,De_AgreeOn_SetPar_State_SetDriverLogin}					//查询已登录的驾驶员
	};
	const uint16  CN_Ba_WordPar[De_CN_Ba_WordPar_Number]=
	{	De_Sensor_WordPar_Switch1,	  														//开关量1
		De_Sensor_WordPar_Switch2,															//开关量2
		De_Sensor_WordPar_Switch3,															//开关量3
		De_Sensor_WordPar_Switch4,															//开关量4
		De_Sensor_WordPar_Switch5,															//开关量5
		De_Sensor_WordPar_Switch6,															//开关量6
		De_Sensor_WordPar_Switch7,															//开关量7
		De_Sensor_WordPar_Switch8,															//开关量8
		De_Sensor_WordPar_Switch9,															//开关量9
		De_Sensor_WordPar_Switch10,															//开关量10
		De_Sensor_WordPar_Switch11,															//开关量11
		De_Sensor_WordPar_Switch12,															//开关量12
		De_Sensor_WordPar_Switch13,															//开关量13
		De_Sensor_WordPar_Switch14,															//开关量14
		De_Sensor_WordPar_Switch15,															//开关量15
		De_Sensor_WordPar_Switch16,															//开关量16
		De_Sensor_WordPar_Less_Switch1,														//无线开关量1
		De_Sensor_WordPar_Less_Switch2,														//无线开关量2
		De_Sensor_WordPar_Less_Switch3,														//无线开关量3
		De_Sensor_WordPar_Less_Switch4,														//无线开关量4
		De_Sensor_WordPar_Less_Switch5,														//无线开关量5
		De_Sensor_WordPar_Less_Switch6,														//无线开关量6
		De_Sensor_WordPar_AccTimer,															//ACC累计时间
		De_Sensor_WordPar_Mileage,														   	//里程统计
		De_Sensor_WordPar_Oil1,																//油箱油位1
		De_Sensor_WordPar_Sem,																//GSM信号强度
		De_Sensor_WordPar_SendOilTimer,														//喷油累计时间
		De_Sensor_WordPar_Temp,																//温度
		De_Sensor_WordPar_Oil2,																//油箱油位2
		De_Sensor_WordPar_Pulse,															//脉冲个数
		De_Sensor_WordPar_Humidity,															//湿度
		De_Sensor_WordPar_OilBaifen,														//油箱油位百分比
		De_Sensor_WordPar_Less_Temp1,														//无线传感器温度1
		De_Sensor_WordPar_Less_Temp2,														//无线传感器温度2
		De_Sensor_WordPar_Less_Temp3,														//无线传感器温度3
		De_Sensor_WordPar_Less_Temp4														//无线传感器温度4
	};
	const uint16 CN_Ba_LessPar[De_CN_Ba_LessPar_Number]=													//无线开关量1
	{	De_Sensor_WordPar_Less_Switch1,	 													//无线开关量2				
		De_Sensor_WordPar_Less_Switch2,														//无线开关量3
		De_Sensor_WordPar_Less_Switch3,														//无线开关量4
		De_Sensor_WordPar_Less_Switch4,														//无线开关量5
		De_Sensor_WordPar_Less_Switch5,													   	//无线开关量6
		De_Sensor_WordPar_Less_Switch6,														//无线传感器温度1
		De_Sensor_WordPar_Less_Temp1,														//无线传感器温度2
		De_Sensor_WordPar_Less_Temp2,														//无线传感器温度3
		De_Sensor_WordPar_Less_Temp3,														//无线传感器温度4
		De_Sensor_WordPar_Less_Temp4
	};
	#define De_AgreeOn_SendOrder_Answer_Yes									1
	#define De_AgreeOn_SendOrder_Answer_No									0
#ifdef  De_Debug_h
	static const st_AgreenOn_Par2Type	CN_Ba_Order2Answer[]=
	{	
		{	De_Dev_Order_GetSeverComPar,De_AgreeOn_SendOrder_Answer_No},		//获取服务器通讯参数
		{	De_Dev_Order_Login,De_AgreeOn_SendOrder_Answer_No},				//定位终端登录
		{	De_Dev_Order_Sleep,De_AgreeOn_SendOrder_Answer_No},				//定位终端休眠
		{	De_Dev_Order_CloseModerm,De_AgreeOn_SendOrder_Answer_No},			//定位终端关机
		{	De_Dev_Order_Answer,De_AgreeOn_SendOrder_Answer_No},				//定位终端命令应答
		{	De_Dev_Order_Orientation,De_AgreeOn_SendOrder_Answer_No},			//上传位置信息
		{	De_Dev_Order_Menum,De_AgreeOn_SendOrder_Answer_No},				//上传菜单信息
		{	De_Dev_Order_TxtMenum,De_AgreeOn_SendOrder_Answer_No},				//上传带菜单的反馈信息
		{	De_Dev_Order_LookPar,De_AgreeOn_SendOrder_Answer_No},				//上传定位终端升级固件状态
		{	De_Dev_Order_UpdateSoftWare,De_AgreeOn_SendOrder_Answer_No},		//上传软件升级状态
		{	De_Dev_Order_Waring,De_AgreeOn_SendOrder_Answer_No},				//上传报警状态

		{	De_Dev_Order_UploaderJpg1,De_AgreeOn_SendOrder_Answer_No},			//上传照片一
		{	De_Dev_Order_UploaderJpg2,De_AgreeOn_SendOrder_Answer_No},			//上传照片二
		{	De_Dev_Order_TabelList,De_AgreeOn_SendOrder_Answer_No},			//表单
		{	De_Dev_Order_UploaderPar,De_AgreeOn_SendOrder_Answer_No},			//上传参数
		{	De_Dev_Order_UploaderLog,De_AgreeOn_SendOrder_Answer_No},			//上传日志文件
		{	De_Dev_Order_UpLoaderWarning,De_AgreeOn_SendOrder_Answer_No},		//上传报警参数

		{	De_Dev_Order_OutRoadMap,De_AgreeOn_SendOrder_Answer_No},			//进出区域报警
		{	De_Dev_Order_UpLoaderReduce,De_AgreeOn_SendOrder_Answer_No},		//上传压缩数据
		{	De_Dev_Order_UpLoaderDriver,De_AgreeOn_SendOrder_Answer_No},		//上传驾驶员ID
		{	De_Dev_Order_UpLoaderHandMess,De_AgreeOn_SendOrder_Answer_No},		//上传手机短信
		{	De_Dev_Order_NoSem,De_AgreeOn_SendOrder_Answer_No},				//盲区补偿信息

		{	De_Dev_UpLoaderFrom,De_AgreeOn_SendOrder_Answer_No},				//上传订单抢答信息
		{	De_Dev_OverFromErro,De_AgreeOn_SendOrder_Answer_No},				//上传订单未能完成原因
		{	De_Dev_PriceData,De_AgreeOn_SendOrder_Answer_No},					//上传计价器信息
	};

#else
	static const st_AgreenOn_Par2Type	CN_Ba_Order2Answer[]=
	{	
		{	De_Dev_Order_GetSeverComPar,De_AgreeOn_SendOrder_Answer_Yes},		//获取服务器通讯参数
		{	De_Dev_Order_Login,De_AgreeOn_SendOrder_Answer_Yes},				//定位终端登录
		{	De_Dev_Order_Sleep,De_AgreeOn_SendOrder_Answer_Yes},				//定位终端休眠
		{	De_Dev_Order_CloseModerm,De_AgreeOn_SendOrder_Answer_Yes},			//定位终端关机
		{	De_Dev_Order_Answer,De_AgreeOn_SendOrder_Answer_No},				//定位终端命令应答
		{	De_Dev_Order_Orientation,De_AgreeOn_SendOrder_Answer_No},			//上传位置信息
		{	De_Dev_Order_Menum,De_AgreeOn_SendOrder_Answer_Yes},				//上传菜单信息
		{	De_Dev_Order_TxtMenum,De_AgreeOn_SendOrder_Answer_Yes},				//上传带菜单的反馈信息
		{	De_Dev_Order_LookPar,De_AgreeOn_SendOrder_Answer_Yes},				//上传定位终端升级固件状态
		{	De_Dev_Order_UpdateSoftWare,De_AgreeOn_SendOrder_Answer_Yes},		//上传软件升级状态
		{	De_Dev_Order_Waring,De_AgreeOn_SendOrder_Answer_Yes},				//上传报警状态

		{	De_Dev_Order_UploaderJpg1,De_AgreeOn_SendOrder_Answer_Yes},			//上传照片一
		{	De_Dev_Order_UploaderJpg2,De_AgreeOn_SendOrder_Answer_Yes},			//上传照片二
		{	De_Dev_Order_TabelList,De_AgreeOn_SendOrder_Answer_Yes},			//表单
		{	De_Dev_Order_UploaderPar,De_AgreeOn_SendOrder_Answer_No},			//上传参数
		{	De_Dev_Order_UploaderLog,De_AgreeOn_SendOrder_Answer_Yes},			//上传日志文件
		{	De_Dev_Order_UpLoaderWarning,De_AgreeOn_SendOrder_Answer_No},		//上传报警参数

		{	De_Dev_Order_OutRoadMap,De_AgreeOn_SendOrder_Answer_Yes},			//进出区域报警
		{	De_Dev_Order_UpLoaderReduce,De_AgreeOn_SendOrder_Answer_Yes},		//上传压缩数据
		{	De_Dev_Order_UpLoaderDriver,De_AgreeOn_SendOrder_Answer_Yes},		//上传驾驶员ID
		{	De_Dev_Order_UpLoaderHandMess,De_AgreeOn_SendOrder_Answer_Yes},		//上传手机短信
		{	De_Dev_Order_NoSem,De_AgreeOn_SendOrder_Answer_Yes},				//盲区补偿信息

		{	De_Dev_UpLoaderFrom,De_AgreeOn_SendOrder_Answer_Yes},				//上传订单抢答信息
		{	De_Dev_OverFromErro,De_AgreeOn_SendOrder_Answer_Yes},				//上传订单未能完成原因
		{	De_Dev_PriceData,De_AgreeOn_SendOrder_Answer_Yes},					//上传计价器信息
	};
#endif
#else
	extern const st_AgreenOn_Par2Type	CN_Ba_st_AgreenOn_Par2Type[De_CN_Ba_st_AgreenOn_Par2Type_Number];
	extern const uint16  CN_Ba_WordPar[De_CN_Ba_WordPar_Number];
	extern const uint16 CN_Ba_LessPar[De_CN_Ba_LessPar_Number];


#endif
