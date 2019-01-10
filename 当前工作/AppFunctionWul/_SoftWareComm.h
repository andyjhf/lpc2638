/*++++++++++++++++++++++++++++++++++++++++控件层加载+++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/
#define De_EventBox_DownLoaderContr_Start					1
#define De_EventBox_DownLoaderContr_Acc						De_EventBox_DownLoaderContr_Start 	//加载Acc控件
#define De_EventBox_DownLoaderContr_Adc						De_EventBox_DownLoaderContr_Acc+1 	//加载电压检测控件
#define De_EventBox_DownLoaderContr_Can						De_EventBox_DownLoaderContr_Adc+1 	//加载Can控件
#define De_EventBox_DownLoaderContr_Gprs					De_EventBox_DownLoaderContr_Can+1  	//加载GPRS控件
#define De_EventBox_DownLoaderContr_Gps						De_EventBox_DownLoaderContr_Gprs+1	//加载GPS控件
#define De_EventBox_DownLoaderContr_Sleep					De_EventBox_DownLoaderContr_Gps+1	//加载休眠控件
#define De_EventBox_DownLoaderContr_Timer					De_EventBox_DownLoaderContr_Sleep+1	//加载定时器控件
#define De_EventBox_DownLoaderContr_Hand					De_EventBox_DownLoaderContr_Timer+1	//加载手柄控件
#define De_EventBox_DownLoaderContr_Oil						De_EventBox_DownLoaderContr_Hand+1	//加载油量控件
#define De_EventBox_DownLoaderContr_LCD						De_EventBox_DownLoaderContr_Oil+1	//加载LCD控件
#define De_EventBox_DownLoaderContr_Number					De_EventBox_DownLoaderContr_LCD-De_EventBox_DownLoaderContr_Acc+1	//控件的数量
/*+++++++++++++++++++++++++++++++++++++++++++文件系统加载++++++++++++++++++++++++++++++++++++++++++++++++++++*/
#define De_EventBox_DownLoaderFile_Start					20
#define De_EventBox_DownLoaderFile_File						De_EventBox_DownLoaderFile_Start	//加载文件系统
/*+++++++++++++++++++++++++++++++++++++++++文件处理部分++++++++++++++++++++++++++++++++++++++++++++++++++++++*/
#define De_EventBox_Par_Amend_Start							30
#define De_EventBox_Par_Amend_BackFac						De_EventBox_Par_Amend_Start			//加载恢复出厂值
/*+++++++++++++++++++++++++++++++++++++++++内部事件触发++++++++++++++++++++++++++++++++++++++++++++++++++++++*/
#define De_EventBox_Inside_Start							40
#define De_EventBox_Inside_APN								De_EventBox_Inside_Start			//APN拨号
#define De_EventBox_Inside_Login							De_EventBox_Inside_APN+1			//登录
#define De_EventBox_Inside_AccTimer							De_EventBox_Inside_Login+1			//ACC时间统计
#define De_EventBox_Inside_MileageSum						De_EventBox_Inside_AccTimer+1		//里程统计
#define De_EventBox_Inside_CloseGps							De_EventBox_Inside_MileageSum+1		//关闭GPS
#define De_EventBox_Inside_OpenGps							De_EventBox_Inside_CloseGps+1		//开GPS
#define De_EventBox_Inside_CloseGprs						De_EventBox_Inside_OpenGps+1		//关闭GPRS
#define De_EventBox_Inside_OpenGprs							De_EventBox_Inside_CloseGprs+1		//开机
																							