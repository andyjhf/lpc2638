#include "stdlib.h"	
#include "..\..\Dev\Sensor\_PuSensor.h"
/*=======================================文件基本信息表===========================================================*/
	typedef struct
	{	uint8 SoftEdition[8];					//软件版本
		uint8 HardEdition[8];					//硬件版本
		uint8 MachID[16];						//机器编号
		uint8 IMEI[7];							//卡编号
		uint8 MachType[2];						//机器类型
		uint8 MakeFactory[2];					//厂家代号
	}st_File_Basic;								//文件基本信息表
/*=====================================驾驶员基本信息表===========================================================*/	
	typedef struct
	{	uint8 ID;								//驾驶员ID
		uint8 Phone[15];						//驾驶员手机号码
		uint8 Name[10];							//驾驶员姓名
		uint8 PassWord[10];						//驾驶员登录密码
		uint8 UseID[10];						//驾驶员工号
	}st_Emplo_Basic;
/*==========================================界面类文字===========================================================*/
	typedef struct
	{	uint8 GreenWord[128]; 					//界面文字
		int16 Integral;   						//当前界面积分
		uint32 PassWord;						//密码
	}st_File_GreenPar;
/*=========================================工作参数表===========================================================*/
	typedef struct
	{	uint32	Adree;							//地址
		uint8 YesOnON;							//是否配置打开
	}st_File_WorkPar;
/*=========================================基本参数配置表=======================================================*/		
   /*---------------------------------------追踪类参数--------------------------------------------------*/
   	typedef struct
	{	uint8 ComMod;							//通讯方式
		uint16 AccOpenTimer;					//Acc开后的时间传送间隔
		uint16 AccCloseTimer;					//Acc关闭后的时间传送间隔
		uint16 Space;							//移动距离的变化间隔
	}st_Track_Par; 								//追踪参数
   /*---------------------------------------报警类参数-------------------------------------------------*/
	typedef struct 
	{	uint32 WartingVl;					//报警值	
		uint32 WartingTimer;				//超过此值的时间
	}st_Waring_Par;		
   	typedef struct
	{	st_Waring_Par	HighSpeed;				//超速度	 
		st_Waring_Par	LowSpeed;				//低速度
		st_Waring_Par	Voltage;				//低电压报警
	}st_Sum_Waring;								//报警参数一览表
   /*-------------------------------------------休眠表-------------------------------------------------*/
   	typedef struct
	{	uint16 GpsTimer;						//Gps关闭的时间
		uint16 GprsTimer;						//Gprs关闭的时间	
	}st_Sleep_Par;								//休眠参数
   /*-----------------------------------------数据-----------------------------------------------------*/
	typedef struct
	{	uint8 DataLog[8];						//数据日志查询
		uint8 ScotomaLog[8];					//盲区补偿日志
	}st_Data_Access;							//数据查询参数
   /*-------------------------------------车辆特征参数-------------------------------------------------*/
   	typedef struct
	{	uint8 PerPuse;							//车速传感器每周脉冲数
		uint16 Feature;							//车辆特征系数
		uint8 OilFrequency;						//油位传感器采样频率
	}st_File_Car_Par;  //关于车辆的参数
	typedef struct
	{	st_Track_Par	CN_st_Track_Par;		//追踪参数表
		st_Sum_Waring	CN_st_Sum_Waring;		//报警参数表
		st_Sleep_Par	CN_st_Sleep_Par;		//休眠参数表			
		st_Data_Access	CN_st_Data_Access;		//数据查询类型
		st_File_Car_Par	CN_st_File_Car_Par;		//车辆的参数	
		uint8 ComMod;							//通讯方式
		uint16 IPTransMessage;					//IP切换MESSAGE时间
		uint8 DisLCD;							//是否安装调度屏
		uint8 DisLogin;							//是否有登录提示
		uint8 DisVid;							//是否安装摄像头
		uint8 VidType;							//拍照类型
		uint32 FrmTimer;						//预约订单时间	
	}st_Parameter_Table;			   			//参数表
/*======================================IP通讯参数表===========================================================*/
		typedef struct
		{	uint8 APN[32];						//以'/0'作为结束	
	   		uint8 Use[32];						//拨号用户名
			uint8 PassWord[32];					//拨号密码
		}st_Gprs_IPNet;
		typedef struct
		{	uint32 IP;			  				//IP地址
			uint8 DomainName[128];				//域名地址
		}st_Gprs_IP;
	
		typedef struct
		{	uint8 CentrHeart;					//中心心跳间隔
	   		uint8 DeviceHeart;					//设备心跳间隔
		  	uint8 Repeat;						//Ip关键指令重发次数
			uint8 RepeatTime;					//Ip关键指令重发间隔
		}st_Gprs_BasicPar;
   	
	typedef struct
	{	st_Gprs_IPNet	CN_st_Gprs_IPNet;			//APN 参数
		st_Gprs_IP		CN_Mast_st_Gprs_IP;			//主IP拨号程序
		st_Gprs_IP		CN_Reserve_st_Gprs_IP;		//副IP拨号程序
		st_Gprs_BasicPar	CN_st_Gprs_BasicPar;	//GPRS基本参数
		uint16 			CenPort;					//中心端口号	
	}st_Gprs_ComPar;								//IP方式下的通讯参数
/*========================================Message方式下的通讯参数==============================================*/
		typedef struct
		{	uint8 Repeat;							//重发次数	
			uint8 RepeatTime;						//重发间隔
		}st_Message_BasicPar;						//短信参数	
		
		typedef struct
		{	uint8 CenMessageSev[15];				//短信中心号码	
			uint8 CentrMessPhone1[128];				//短信服务中心号码1
			uint8 CentrPhone2[128];					
		}st_Message_Phone;							//短信息基本参数表
	typedef struct
	{	st_Message_BasicPar	CN_st_Message_BasicPar;			//短信的基本参数表
		st_Message_Phone	CN_st_Message_Phone;			//短信号码
	}st_Message_ComPar;										//短信下的通讯参数
/*=============================================电话类参数表===================================================*/
	typedef struct
	{	uint8 WatchPhone[15];									//监控电话号码
		uint8 RestPhone[15];									//复位电话号码
	}st_Phone_Basic;
/*=============================================固定电话号码===================================================*/
	typedef struct
	{	uint8 Type;											    //电话类型
		uint8 PhoneName[10];									//该电话人员姓名
		uint8 Phone[15];										//电话号码
	}st_Phone_Root;												//固定电话号码

/*==============================================ACC===========================================================*/
	typedef struct
	{	uint32 AccTimer;										//Acc
	}st_AccTimer;	 											//Acc

/*==============================================Gps保存表=====================================================*/
	typedef struct
	{	st_Data_Gps	CN_st_Data_Gps;								//
		uint32 Milage;
	}st_File_Gps;
/*==============================================菜单信息======================================================*/
	typedef struct
	{	uint8 BackID;
		uint8 Cut[40];
	}st_File_Menum;

/*==============================================固定电话======================================================*/
	typedef struct
	{	uint8 Name[8];				//姓名
		uint8 Phone[15];			//电话
		uint8 Pro;					//属性		
	}st_File_Phone;
/**************************************工作流水*******************************************************/	
	typedef struct
	{	uint8 OnOffValue[16];									//开关量的各个值
		uint8 WireLess[6];										//无线开关量的值
		uint32 AccTimer;										//Acc累计统计时间
		uint32 Mileage;											//累计里程
		uint16 OilV1;											//油量油位1
		uint16 OilV2;											//油量油位2
		uint8 OilV1Scale;										//油位1百分比
		uint8 GsmCsq;											//GSM信号强度	
		uint32 SupplyOilTimer;									//供油时间
		uint32 Temper;											//温度值
		uint32 PulseNumber;										//脉冲个数
		uint16 Humidity_Par;									//湿度值
		uint32 WireLessTemp[4];									//无线传感器温度值
	}st_Work_ParFlow;
	
	typedef struct
	{	st_Data_Gps	CN_st_Data_Gps;				//GPS状态位
		uint8	AceWhy;							//存储原因
		uint32 DevState[4];						//设备状态
		st_Work_ParFlow	CN_st_Work_ParFlow;		//工作过程中参数
	}st_WorkFlow_Table;							//工作流水表
