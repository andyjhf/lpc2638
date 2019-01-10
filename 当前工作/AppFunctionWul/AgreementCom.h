/*----------------------------------------物流协议头部定义-------------------------------------------------*/
	#define De_IP_Com_AgreeOn											2				//本次通讯的协议版本
	#define De_Dev_SendCom_Mod_IP										0				//通讯方式为IP方式
	#define De_Dev_SendCom_Mod_Sms										1				//通讯方式为SMS方式
	#define De_Dev_SendCom_Mod_IPSms									2				//通讯方式为IP与SMS方式
/*-----------------------------------------上行与下行协议--------------------------------------------------*/
	/*++++++++++++++++++++++++++++++++++中心命令协议+++++++++++++++++++++++++++++++++++++++++++++*/	
	#define De_Centr_Order_Answer										0x0001			//中心命令应答
	#define De_Centr_Order_Orientation									0x0002			//定位指令
	#define De_Centr_Order_Track										0x0003			//追踪指令
	#define De_Centr_Order_SetPar										0x0004			//设定参数
	#define De_Centr_Order_UnlockWaring									0x0005			//解除报警
	#define De_Centr_Order_AmendMenum									0x0006			//修改固定菜单
	#define De_Centr_Order_LoaderTxt									0x0007			//下发文本调度
	#define De_Centr_Order_LoaderTxtMenum								0x0008			//下发带文本的菜单
	#define De_Centr_Order_SetPhone										0x0009			//设置固定电话
	#define De_Centr_Order_CallAnswer									0x000a			//通话请求
	#define De_Centr_Order_UpdateSoftWare								0x000b			//软件升级
	#define De_Centr_Order_LookPar										0x000c			//查询参数
	#define De_Centr_Order_Contrl										0x000d			//远程控制
	#define De_Centr_Order_ConfineCall									0x000e			//通话限制状态
	#define De_Centr_Order_ConfigCentrSever								0x000f			//配置中心服务器状态
	#define De_Centr_Order_Activation									0x0010			//激活定位终端
		/***************************************************************************************/
	#define De_Centr_Order_LookJpg										0x0401			//查询指定类型的照片
	#define De_Centr_Order_JpgIng										0x0402			//查询实时照片
	#define De_Centr_Order_SetVidType									0x0403			//设置拍照类型
	#define De_Centr_Order_TabelList									0x0404			//设置表单
	#define De_Centr_Order_LookWorkPar									0x0405			//查询工作参数
	#define De_Centr_Order_WorkParTimer									0x0406			//按照固定时间上传工作参数	
	#define De_Centr_Order_WorkParSpace									0x0407		   	//按照间隔上传工作参数
	#define De_Centr_Order_LookLog										0x0408			//查询日志文件
	#define De_Centr_Order_SetWaringTerm								0x0409			//设置报警条件
		/**********************************物流协议专用****************************************/
	#define De_Centr_Order_SetRound										0X0801			//设置圆形路线
	#define De_Centr_Order_DelRound										0x0802			//删除圆形路线
	#define De_Centr_Order_SetRectangle									0X0803			//设置矩形路线
	#define De_Centr_Order_DelRectangle									0x0804			//删除矩形路线
	#define De_Centr_Order_SetPolygon									0X0805			//设置多边形路线
	#define De_Centr_Order_DelPolygon									0x0806			//删除多边形路线
	#define De_Centr_Order_SetRoadMap									0x0807			//设置路线区域
	#define De_Centr_Order_DelRoadMap									0x0808			//删除路线区域
	#define De_Centr_Order_Reduce										0X0809			//设置压缩回传
	#define De_Centr_Order_Driver										0x080a			//设置驾驶员ID
	#define De_Centr_Order_Navigation									0x080b			//中心导航
	#define De_Centr_Order_HandTxt										0x080c			//手机文本调度
	#define De_Centr_Order_HandAttemper									0X080D			//手机调度信息	
		/***********************************出租车协议****************************************/ 
	#define	De_Centr_Order_AmendForm									0x0c01			//修改订单信息
	#define De_Centr_Order_UpLoaderForm									0x0c02			//下发订单抢答信息
	#define De_Centr_Order_UpLoaderFormSuc								0x0c03			//下发订单抢答成功信息
	#define De_Centr_Order_UpLoaderFormErro								0x0c04			//下发订单抢答失败信息
	#define De_Centr_Order_UpLoaderCan									0x0c05			//下发订单取消信息		   	  	   	 
	/*++++++++++++++++++++++++++++++++++++命令终端协议++++++++++++++++++++++++++++++++++++++++++++++*/
	#define De_Dev_Order_GetSeverComPar									0x0101			//获取服务器通讯参数
	#define De_Dev_Order_Login											0x0102			//定位终端登录
	#define De_Dev_Order_Sleep											0x0103			//定位终端休眠
	#define De_Dev_Order_CloseModerm									0x0104			//定位终端关机
	#define De_Dev_Order_Answer											0x0105			//定位终端命令应答
	#define De_Dev_Order_Orientation									0x0106			//上传位置信息
	#define De_Dev_Order_Menum											0x0107			//上传菜单信息
	#define De_Dev_Order_TxtMenum										0x0108			//上传带菜单的反馈信息
	#define De_Dev_Order_LookPar										0x0109			//上传定位终端升级固件状态
	#define De_Dev_Order_UpdateSoftWare									0x010a			//上传软件升级状态
	#define De_Dev_Order_Waring											0x010b			//上传报警状态
		/****************************************************************************************/
	#define De_Dev_Order_UploaderJpg1									0x0501			//上传照片一
	#define De_Dev_Order_UploaderJpg2									0x0502			//上传照片二
	#define De_Dev_Order_TabelList										0x0503			//表单
	#define De_Dev_Order_UploaderPar									0x0504			//上传参数
	#define De_Dev_Order_UploaderLog									0x0505			//上传日志文件
		/**********************************物流协议专用****************************************/
	#define De_Dev_Order_OutRoadMap										0x0901			//进出区域报警
	#define De_Dev_Order_UpLoaderReduce									0x0902			//上传压缩数据
	#define De_Dev_Order_UpLoaderDriver									0x0903			//上传驾驶员ID
	#define De_Dev_Order_UpLoaderHandMess								0x0904			//上传手机短信
	#define De_Dev_Order_NoSem											0x0905			//盲区补偿信息
		/***********************************出租车协议*****************************************/
	#define De_Dev_UpLoaderFrom											0x0d02			//上传订单抢答信息
	#define De_Dev_OverFromErro											0x0d03			//上传订单未能完成原因
	#define De_Dev_PriceData											0x0d04			//上传计价器信息

	/*++++++++++++++++++++++++++++++++++参数定义++++++++++++++++++++++++++++++++++++++++++++++++++++*/
	#define De_SetPar_SetGreenPar										0x0000			//设置
	#define De_SetPar_SetGreenWord										0x0001			//设置界面文字
	#define De_SetPar_SetListePhone										0x0100			//设置监听号码							
	#define De_SetPar_SetResetPhone										0x0101			//设置电话复位
	#define De_SetPar_SetCerSevPhone 									0x0102			//设置短信中心服务号码
	#define De_SetPar_SetCenPhone										0x0103			//设置短信中心
	#define De_SetPar_SetAPN											0x0200			//设置APN参数
	#define De_SetPar_SetMastIP											0x0201			//设置主中心IP
	#define De_SetPar_SetMastDomainName									0x0202			//设置主域名
	#define De_SetPar_SetReserveIP										0x0203			//设置副中心IP
	#define De_SetPar_SetReserveDomainName								0x0204			//设置主域名
	#define De_SetPar_SetCenPort										0x0205			//设置中心端口号
	#define De_SetPar_SetCentHeart										0x0206			//中心下发心跳间隔
	#define De_SetPar_SetUseName										0x0207			//设置用户名
	#define De_SetPar_SetUsePass										0x0208			//设置用户名
	#define De_SetPar_SetDevHeart										0x0209			//终端上发心跳间隔
	#define De_SetPar_SetComMod											0x020a			//设置通讯方式
	#define De_SetPar_SetIPRepeat										0x020b			//Ip关键指令重发次数
	#define De_SetPar_SetIPRepeatTime									0x020c			//IP关键指令重发间隔时间
	#define De_SetPar_SetMessageRepeat									0x020d			//Message关键指令重发次数
	#define De_SetPar_SetMessageRepeatTimer								0x020e			//Message Timer 重发时间
	#define De_SetPar_SetIPTransSms										0x020f			//Message与IP之间切换时间
	#define De_SetPar_SetDataLog										0x0210			//数据日志存储
	#define De_SetPar_SetDataScotomaLog									0x0211			//盲区补偿数据
	#define De_SetPar_SetParLoad										0x0212			//设置上传参数
	#define De_SetPar_SetWireLessPar									0x0213			//设置无线参数
	#define De_SetPar_SetDePassWord										0x0301			//设置终端密码
	#define De_SetPar_ComFac											0x0302			//回复出厂值
	#define De_SetPar_SetAccTimer										0x0303			//设置ACC累计时间
	#define De_SetPar_SetRunLen											0x0304			//设置运行里程
	#define De_SetPar_SetPerPuse										0x0305			//设置每周的脉冲数
	#define De_SetPar_SetCarFeature										0x0306			//设置车辆特征
	#define De_SetPar_SetTakeLCD										0x0307			//设置车辆是否安装调度
	#define De_SetPar_SetOilFrequency									0x0308			//设置油量采样频率
	#define De_SetPar_SetSleepTimer										0x0309			//设置休眠时间
	#define De_SetPar_SetCloseTimer										0x030a			//设置关机时间
	#define De_SetPar_SetLogMess										0x030b			//设置登录提示
	#define De_SetPar_SetTaskVid										0x030c			//设置是否安装摄像头
	#define De_SetPar_SetHighSpeed										0x0400			//设置超速报警
	#define De_SetPar_SetLowSpeed										0x0401			//设置低速报警
	#define De_SetPar_SetLowVlt											0x0402			//设置低电压报警
	#define De_SetPar_SetVidType										0x0500			//设置拍照类型
	#define De_SetPar_SetOrderFrmTimer									0x0600			//设置预约订单时间
	#define De_SetPar_HardWareEdit										0x0700			//查询硬件版本
	#define De_SetPar_SoftWareEdit										0x0701			//查询软件版本
	#define De_SetPar_MachID											0X0702			//查询机器编号
	#define De_SetPar_Menum												0x0703			//查询菜单信息
	#define De_SetPar_Phone												0x0704			//查询固定电话信息
	#define De_SetPar_ConfineCall										0x0705			//查询通话限制状态
	#define De_SetPar_DriverID											0X0706			//查询驾驶员
	#define De_SetPar_DriverLogin										0x0707			//查询已登录的驾驶员				
	
				