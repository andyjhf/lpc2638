#define De_End_Pusen
#ifdef 	De_End_Pusen
/*=========================================Include File========================================================*/
	#include "..\..\APP\config.h"
	#include "..\..\AgreeOn\TzDefine\Tz_WorkParDefine.h"	
/*==========================================Define Data========================================================*/
	#define De_Suc_Sensor											0						//成功
	/*++++++++++++++++++++++++++++++++++++++错误代码一览表++++++++++++++++++++++++++++++++++++++++++++++++*/	
	#define De_Erro_Sensor_Less										1
	/*++++++++++++++++++++++++++++++++++++++++工作参数++++++++++++++++++++++++++++++++++++++++++++++++++++*/
	
	/*++++++++++++++++++++++++++++++++++++++以下是扩展参数++++++++++++++++++++++++++++++++++++++++++++++++*/
	#define De_Sensor_WordPar_VaCheck								0x1000					//电压检测
	#define De_Sensor_WordPar_Gps									0x1001					//GPS参数

	#define De_Sensor_WordPar_Display								0x1002					//调度屏	
	
	#define De_Sensor_WordPar_Temperture_1                          0x1003    				//温度1路
	#define De_Sensor_WordPar_Temperture_2                          0x1004    				//温度2路
	#define De_Sensor_WordPar_GprsTzxy_1							0x1005					//GPRS设备参数1
	#define De_Sensor_WordPar_GprsTzxy_2							0x1006					//GPRS设备参数2
	#define De_Sensor_WordPar_UartTzxy_1							0x1007					//UART天泽协议
	#define De_Sensor_WordPar_UartTzxy_2							0x1008					//UART天泽协议
	#define De_Sensor_WordPar_MessagTzxy							0x1009					//短信天泽协议
	#define De_Sensor_WordPar_Arearect								0x100A					//矩形区域
	#define De_Sensor_WordPar_AreaCirc								0x100B					//圆形区域
	#define De_Sensor_WordPar_Help									0x100C					//求助开关

	#define De_WordPar_NoPar										0xffff					//此参数不可用
/*===========================================各个状态定义======================================================*/
	/*---------------------------------------传感器输入输出-----------------------------------------------*/
	#define De_Sensor_Par_Onoff										1		  			//表示为开关量
    #define De_Sensor_Par_Temp										2		  			//表示为温度
	#define De_Sensor_Par_Timer										3					//统计时间
	#define De_Sensor_Par_Milleage									4					//里程统计
	#define De_Sensor_Par_Oil										5					//油量
	#define De_Sensor_Par_Pulse										6					//脉冲
	#define De_Sensor_Par_Sem										7					//信号强度
	#define De_Sensor_Par_Humidity									8					//湿度
	#define De_Sensor_Par_ADC										9					//电压检测
	#define De_Sensor_Par_Baifen									10					//油量百分
	#define De_Sensor_Par_Gps										11					//GPS数据
	#define De_Sensor_Par_Display									12					//显示设备
	#define De_Sensor_Par_Tzxy										13					//天泽协议	
	#define De_Sensor_Par_No										0xff				//无参数
	
	
	
	#define De_Sensor_Par_Onoff_Open				     			0		  			//表示开关为打开状态
	#define De_Sensor_Par_Onoff_Close				    			1		  			//表示开关为关闭状态

	#define De_Sensor_Par_Onoff_In									0					//表示在区域内部
	#define De_Sensor_Par_Onoff_Out									1					//表示在区域外部
	/*-------------------------------------------传感器状态-----------------------------------------------*/
	#define De_Sensor_State_Suc										0	 				//传感器工作正常
	#define De_Sensor_Battery_State_Erro							1		  			//传感器电池工作不正常	
   	#define De_Sensor_Par_State_Erro								3					//传感器工作不正常
	#define De_Sensor_MaxDly_State_Erro								4					//超时	

	#define De_Sensor_ACC_Open										0					//ACC状态打开
	#define De_Sensor_ACC_Close										1					//ACC状态关闭

	#define De_Sensor_Nofd											0xff				//没有分配FD
	/*=====================================主机发送数据===================================================*/
	#define De_Display_Host_Order_Answer							0x00				//发送应答成功
	#define De_Display_Host_Order_DeliverCentr						0x09				//转发中心指令
	#define De_Display_Host_Order_SysInfor							0x02				//系统信息
	#define De_Display_Host_Order_Phone								0x03				//电话指令
	#define De_Display_Host_Order_InitStart							0x04				//初始化开始
	#define De_Display_Host_Order_InitOver							0x05				//初始化结束
	#define De_Display_Host_Order_HostSoft							0x06				//软件升级
	#define De_Display_Host_Order_ConInfor							0x07				//发送控制信息
	#define De_Display_Host_Order_ParAnswer							0x08				//参数应答
	
	/*=====================================调度屏发送数据=================================================*/
	#define De_Display_Device_Order_Answer							0x70				//调度屏应答
	#define De_Display_Device_Order_Phone							0x71				//电话指令
	#define De_Display_Device_Order_SeePar							0x72				//查看参数
	#define De_Display_Device_Order_SetPar							0x73				//设置参数
	#define De_Display_Device_Order_Log								0x74				//登录指令
	#define De_Display_Device_Order_OnCen							0x75				//上传中心指令
	#define De_Display_Device_Order_SeePci							0x76				//查看图片
	#define De_Display_Device_Order_Voic  							0x77				//设置音量


	#define De_Display_SeePar_Suc									0x00				//参数查询成功
	#define De_Display_SeePar_Erro									0x02				//参数查询失败
	#define De_Display_Oper_Suc										0x00				//执行成功

	#define De_Sensor_Display_Agree									0x00				//接受数据
	#define De_Sensor_Display_Send									0x01				//发送数据

	#define De_Display_Answer_Suc									0x00
	#define De_Display_Answer_Erro									0x02	

	/*=====================================调度屏数据类定义================================================*/
	 #define De_Display_Agree_CallPhone								0x00				//拨打电话
	 #define De_Display_Agree_ClosePhone							0x03				//挂电话
	 #define De_Display_Agree_AnswerPhone							0x02				//接电话
	 #define De_Display_Agree_CallPhone1							0X04				//拨打分机
	 #define De_Display_Par_Integral								0X0000				//当前积分			
	/*================================================================================================*/	
	#define De_Display_Par_ListenPhone								0X0100				//监听号码
	#define De_Display_Par_ResetPhone								0x0101				//复位号码
	#define De_Display_Par_CentrSevenPhone							0x0102				//短信服务号码
	#define De_Display_Par_WarningPhone								0x0103				//报警号码
	#define De_Display_Par_APN	   									0x200				//APN参数
	#define De_Display_Par_MastIP									0x201				//主中心服务IP
	#define De_Display_Par_MastDomain								0x202				//主域名
	#define De_Display_Par_ReserveIP								0x203				//副中心IP
	#define De_Display_Par_ReserveDomain							0x204				//副中心域名
	#define De_Display_Par_CenPort									0x205				//中心端口号
	#define De_Display_Par_CentHeart								0x206				//中心心跳间隔
	#define De_Display_Par_DsnSever								   	0x207				//DSN
	#define De_Display_Par_MachiID									0x300				//车机ID
	#define De_Display_Par_PassWord									0x301				//密码
	#define De_Display_Par_SoftWare									0xf04				//软件版本号
	#define De_Display_Par_SelfIP									0xf01				//本身IP
	#define De_Display_Par_NonceIP									0xf02				//当前中心IP
	#define De_Display_Par_CommEdit									0xf05				//协议版本号
	#define De_Display_Par_Tracks									0xf00				//追踪间隔


/*=============================================Data Define======================================================*/	
	#define De_Tzxy_SendBuf_Send						0
	#define De_Tzxy_AgreeBuf_Agree						1
	typedef struct
	{	uint8 ResultOrSend;
		uint16 SizeofBuf;
		uint8 *Buf;
	}st_Dev_Tzxy_Send;
	typedef struct
	{	uint16 SizeofBuf;
		uint8 *Buf;


	}st_Dev_Tzxy_Agree;
	
	/*+++++++++++++++++++++++++++++++++++++++++发送结构体++++++++++++++++++++++++++++++++++++++++++++++++++*/
	typedef struct
	{	uint8 SendOrAgree;	  //发送还是接受
		uint8 ID;
		void *SendData;		  //如果发送，则发送的数据
 	}st_Display_Send;

	typedef struct
	{	uint8 ID;
		void *AgreeData;

	}st_Display_Agree;

	/*+++++++++++++++++++++++++++++++++++++++++接受结构体+++++++++++++++++++++++++++++++++++++++++++++++++*/
	typedef struct
	{	uint8 Order;
		uint8 Result;
	}st_Display_Agree_Answer;

	typedef struct
	{	uint8 Type;
		uint8 Phone[15];
	}st_Display_Agree_Phone;

	typedef struct
	{	uint32 PassWord;
		uint8 ParNumber;
		uint8 YesOnNo[20];	
	}st_Display_Agree_SeePar;
	typedef struct
	{	uint32 PassWord;
		uint16 ParID;
		void *ParCut;

	}st_Display_Agree_SetPar;
	typedef struct
	{	uint8 SoftEdit[2];
	}st_Display_Agree_Log;
	typedef struct
	{	uint8 *Data;


	}st_Display_Agree_OnCen;
	typedef struct
	{	uint8 VolSize;


	}st_Display_Agree_Voic;

	typedef struct
	{	int16 Integral;				  //当前积分
		uint8 ListenPhone[15];		  //监听号码
		uint8 ResetPhone[15];	  			
		uint8 CentrSevenPhone[15];
		uint8 WarningPhone[15];
		uint8 APN[32];
		uint32 MastIP;
		uint8 MastDomain[128];
		uint32 ReserveIP;
		uint8 ReserveDomain[128];
		uint16 CenPort;
		uint8  CentHeart;
		uint32 DsnSever;
		uint8 MachiID[16];
		uint32 PassWord;
		uint8 SoftWare[8];
		uint32 SelfIP;
		uint32 NonceIP;
		uint8 CommEdit;
		uint32 Tracks;
	}st_Display_Par_Cut;

	typedef struct
	{	st_Display_Par_Cut	CN_st_Display_Par_Cut;
		uint8 Set[20];
		uint32 PassWord;
       	}st_Display_Par;
	 typedef struct
	{	uint16 Par;
		uint8 Type;
		void *Point;
		uint16 SizeofPoint;
	}st_Display_Par_Set;


	/*+++++++++++++++++++++++++++++++++++++++++发送结构体+++++++++++++++++++++++++++++++++++++++++++++++++*/
	typedef struct
	{	uint8 Result;
		uint8 AnswerID;
	}st_Display_Order_Answer;					//发送应答命令

	typedef struct
	{	uint16 SizeofBuf;
		uint8 *Buf;
	}st_Display_Order_DeliverCentr;		  		//转发中心指令

	typedef struct
	{	int16 Integral;	 						//当前屏幕积分
		uint8 DateTime[7];						//当
		uint8 GpsState;							//GPS状态
		uint8 VidState;							//摄像头状态
		uint8 ContrState;						//链接状态
		uint8 GprsSem;							//GPRS信号强度
		uint8 Carrier;							//运营商
		uint8 CarState;							//汽车状态
		uint8 ExigenceState;					//紧急状态
		uint8 WaringPci;						//报警图片存储
		uint8 CarSpeed;							//汽车速度
		uint8 StarNumber;						//卫星个数
		uint8 TallyState;						//计价器状态
		uint8 VolState;							//电压状态
	}st_Display_Order_SysInfor;				 	//系统信息
	typedef struct
	{	uint8 PhoneType;						//电话类型
		uint8 Phone[15];						//电话号码
	}st_Display_Order_Phone;					//电话指令
	typedef struct
	{	uint8 Value;							//升级进度表


	}st_Display_Order_HostSoft;			 		//软件升级

	typedef struct
	{	uint8 BeerLen;	 						//蜂鸣器长度
		uint8 BeerNumber;						//蜂鸣器次数
		uint8 VoiceReport;						//是否需要语音播报
		uint8 TextCut[128];						//播报内容
	}st_Display_Order_ConInfor;					//控制信息


	typedef struct
	{	uint8 Result;
		uint16 ParID;
		uint8 *ParCut;
	}st_Display_Order_ParAnswerCut;   				//参数查询

	typedef struct
	{	uint8 ParNumber;
		st_Display_Order_ParAnswerCut	*ptst_Display_Order_ParAnswerCut[];
	}st_Display_Order_ParAnswer;
	
/*=============================================Data Define======================================================*/	
	/*+++++++++++++++++++++++++++++++++++++++各个传感器输出表++++++++++++++++++++++++++++++++++++++++++++++*/
	
	typedef struct
	{	uint8 DateTime[7];						//YYYYMMDD HHMM SS,时间和年
		uint8 LocationTrue;						//定位是否有效，De_Gps_Location_True			有效
		uint8 LatHem;							//纬度半球		'N'  北半球	 'S'南半球  其他无效
		uint8 LongHem;							//经度半球		'E'	 东经	 'W'西经	其他无效
		uint32 Latitude;						//纬度			定点4位小数   
		uint32 Longitude;   			 		//经度			定点4位小数
		uint32 Speed;							//速度 			单位海里，定点一位小数
		uint32 Angle;							//方向角度		度表  定点一位小数    
	
	}st_Gps_Data_GPRMC;
	typedef struct
	{	uint8 	StarNumber;						//卫星个数
		int32 Height;							//海拔高度
	
	}st_Gps_Data_GPGGA;
	typedef struct
	{	st_Gps_Data_GPRMC	CN_st_Gps_Data_GPRMC;
		st_Gps_Data_GPGGA	CN_st_Gps_Data_GPGGA;	
	}st_Data_Gps;
	
	typedef struct
	{	uint8 NonState;
		uint32 AccTimer;
	}st_Sensor_Data_Acc; 						//ACC统计
	
	typedef struct
	{	uint32 Addree;				    		//传感器地址	 
		uint16 WorkPar;							//工作参数ID
		uint32 MaxDly;							//最大超时时间
	}st_Sensor_DataPar;							//传感器参数

	typedef struct
	{	uint8 Work;			  					//传感器工作状态
	 	uint8 Battery;		  					//传感器电池状态
		uint8 Dly;								//最大时间
 	}st_Sensor_State; 
	typedef struct
	{	st_Sensor_DataPar	CN_st_Sensor_DataPar;
		uint8 Phone[15];	
	}st_Sensor_Sms_DataPar;

	typedef struct
	{	uint16 WorkPar;
		uint8 Type;
	}st_Sensor_Par2Type;
	
	typedef struct
	{	uint16 (*Init)(void);	   											//初始化
		uint16 (*Open)(st_Sensor_DataPar	*ptst_Sensor_DataPar,uint8 *fd);		//打开
		uint16 (*Close)(uint8 fd);											//关闭
		uint16 (*Read)(uint8 fd,void *SendBuf,void *AgreeBuf);				//读
		uint16 (*GetState)(st_Sensor_State	*ptst_Sensor_State,uint8 fd);	//获取状态
	}st_Fun_Sensor2Hard;
						
	typedef struct
	{	const st_Fun_Sensor2Hard	*ptst_Less_DataPar;									//传感器函数
	  	const st_Sensor_Par2Type	*ptst_Sensor_Par2Type;
		uint16 SizeofPar;													//传感器所支持的参数多少
	}st_Sensor_ParList;	

	/****************************区域报警用数据结构******************************/	  
	typedef struct
	{	uint32 Latitude; 		//中心纬度
		uint32 Longitude;		//中心经度
		uint32 Radii;			//半径 
	}st_RoundPar_Data;


	typedef struct
	{	uint32 LeftLatitude; 	//左下角纬度
		uint32 LeftLongitude;	//左下角经度
		uint32 RightLatitude;	//右上角纬度
		uint32 RightLongitude;	//右上角经度
	}st_Rectangle_Data;  
	
	typedef struct
	{	st_Sensor_DataPar	CN_st_Sensor_DataPar; 		//打开时的参数
		union 
		{	
			st_Rectangle_Data	CN_st_Rectangle_Data;	//矩形参数  
			st_RoundPar_Data	CN_st_RoundPar_Data;	//圆形参数 			
		}CN_un_Par;
	}st_Open_RunLen;
	
	
	typedef union  
	{	st_Sensor_DataPar	CN_st_Sensor_DataPar; 		//参数
		st_Open_RunLen		CN_st_Open_RunLen;			//打开时的参数
	} un_OpenPar;
#endif
