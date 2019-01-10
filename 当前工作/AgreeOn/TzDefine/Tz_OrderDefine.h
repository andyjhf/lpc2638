/*===============================================中心命令协议====================================================*/	
/*----------------------------------------------基本协议--------------------------------------------------------*/	
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
/*---------------------------------------------功能扩展协议-----------------------------------------------------*/
	#define De_Centr_Order_LookJpg										0x0401			//查询指定类型的照片
	#define De_Centr_Order_JpgIng										0x0402			//查询实时照片
	#define De_Centr_Order_SetVidType									0x0403			//设置拍照类型
	#define De_Centr_Order_TabelList									0x0404			//设置表单
	#define De_Centr_Order_LookWorkPar									0x0405			//查询工作参数
	#define De_Centr_Order_WorkParTimer									0x0406			//按照固定时间上传工作参数	
	#define De_Centr_Order_WorkParSpace									0x0407		   	//按照间隔上传工作参数
	#define De_Centr_Order_LookLog										0x0408			//查询日志文件
	#define De_Centr_Order_SetWaringTerm								0x0409			//设置报警条件
	#define De_Centr_Order_LookWaringTerm								0x040A			//查询报警条件
/*-----------------------------------------------物流协议专用---------------------------------------------------*/
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
/*---------------------------------------------出租车协议-------------------------------------------------------*/ 
	#define	De_Centr_Order_AmendForm									0x0c01			//修改订单信息
	#define De_Centr_Order_UpLoaderForm									0x0c02			//下发订单抢答信息
	#define De_Centr_Order_UpLoaderFormSuc								0x0c03			//下发订单抢答成功信息
	#define De_Centr_Order_UpLoaderFormErro								0x0c04			//下发订单抢答失败信息
	#define De_Centr_Order_UpLoaderCan									0x0c05			//下发订单取消信息
/*==============================================终端命令协议===================================================*/
	/*----------------------------------------------基本协议-------------------------------------------------*/	
	#define De_Dev_Order_GetSeverComPar									0x0101			//获取服务器通讯参数
	#define De_Dev_Order_Login											0x0102			//定位终端登录
	#define De_Dev_Order_Sleep											0x0103			//定位终端休眠
	#define De_Dev_Order_CloseModerm									0x0104			//定位终端关机
	#define De_Dev_Order_Answer											0x0105			//定位终端命令应答
	#define De_Dev_Order_Orientation									0x0106			//上传位置信息
	#define De_Dev_Order_Menum											0x0107			//上传菜单信息
	#define De_Dev_Order_TxtMenum										0x0108			//上传带菜单的反馈信息
	#define De_Dev_Order_LookPar										0x0109			//上传定位终端参数
	#define De_Dev_Order_UpdateSoftWare									0x010a			//上传软件升级状态
	#define De_Dev_Order_Waring											0x010b			//上传报警状态
	/*---------------------------------------------功能扩展协议---------------------------------------------*/
	#define De_Dev_Order_UploaderJpg1									0x0501			//上传照片一
	#define De_Dev_Order_UploaderJpg2									0x0502			//上传照片二
	#define De_Dev_Order_TabelList										0x0503			//表单
	#define De_Dev_Order_UploaderPar									0x0504			//上传参数
	#define De_Dev_Order_UploaderLog									0x0505			//上传日志文件
	#define De_Dev_Order_UpLoaderWarning								0x0506			//上传报警参数
	/*--------------------------------------------物流协议专用----------------------------------------------*/
	#define De_Dev_Order_OutRoadMap										0x0901			//进出区域报警
	#define De_Dev_Order_UpLoaderReduce									0x0902			//上传压缩数据
	#define De_Dev_Order_UpLoaderDriver									0x0903			//上传驾驶员ID
	#define De_Dev_Order_UpLoaderHandMess								0x0904			//上传手机短信
	#define De_Dev_Order_NoSem											0x0905			//盲区补偿信息
	/*---------------------------------------------出租车协议----------------------------------------------*/
	#define De_Dev_UpLoaderFrom											0x0d02			//上传订单抢答信息
	#define De_Dev_OverFromErro											0x0d03			//上传订单未能完成原因
	#define De_Dev_PriceData											0x0d04			//上传计价器信息
