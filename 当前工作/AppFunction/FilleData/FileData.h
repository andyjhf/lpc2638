
/*======================================Include File============================================================*/
 	#include "..\..\APP\config.h"
	#include "stdlib.h"
	//#include "..\..\HardWare\Can\Can.H"
	#ifdef De_FileData_Compiler
		#include "..\..\File\rwFile.h"
		#include "..\..\miscellaneous\CodeTrans\AscNumber.h"
		#include "..\..\Control\Timer\Timer.h"
		#include "..\..\Control\Gps\GpsTask.h"
		#include "..\..\Control\Sleep\Sleep.h"
		#include "..\..\HardWare\RTC\RTC.h"
		#include "..\..\AppFunction\DataTrans\DataTrans.h"
		#include "..\..\Control\Gprs\GPRS.h"
	#endif
/*======================================Define Data============================================================*/
	/*++++++++++++++++++++++++++++++++++错误代码一览表++++++++++++++++++++++++++++++++++++++++++++++++++*/

	/*+++++++++++++++++++++++++++++++++++++文件名称+++++++++++++++++++++++++++++++++++++++++++++++++++++*/
	#define De_FileName_Basic						"Basic1"				//机器型号、软件版本号、硬件版本号、厂家代号、机器编号
	#define	De_FileName_CanID						"CanID"			    //能够接受的CAN数据的ID
	#define De_FileName_Parameter					"Parame"			//速度、休眠时间、休眠下巡检时间、工作状态巡检时间、中心号码1、中心号码2、使能防拆字符、CanID、ACC开关、是否断电断油
	#define De_FileName_AccTimer					"AccTim"			//Acc统计时间
	#define De_FileName_TimerUpLoade				"UpLoad"			//定时上传时间、定时上传次数
	#define De_FileName_Message						"Message"			//短信无信号时的保存
	#define De_FileName_MessageSend					"MeSend"			//发送表
	#define De_FileName_GpsMessage					"GpsMge"
	
	#define De_Suc_State							0

	#define De_State_Control							1
	#define De_State_NoControl							0
	#define De_IO_Control								0x01
	#define De_IO_Control_Remote_Out					FIO2DIR|=De_IO_Control
	#define De_IO_Control_Remote						FIO2SET|=De_IO_Control				//高电平
	#define De_IO_NoControl_Remote						FIO2CLR|=De_IO_Control
	
	#define De_VoAlarm_No								0
	#define De_VoAlarm_Yes								1							

	#define De_IO_unLock								De_IO_Control_Remote_Out;De_IO_Control_Remote
	#define De_IO_Lock									De_IO_Control_Remote_Out;De_IO_NoControl_Remote
	

   	#define De_Can_Data_MaxID						10
/*=======================================Data Define===========================================================*/
	/*++++++++++++++++++++++++目的:建立和维护运行时的数据库文件,本应用程序分为以下几个文件+++++++++++++++++++++*/
	typedef struct
	{	uint32 Speed;	   				//速度
		uint32 SleepTimer;				//休眠时间
		uint32 SleepCheckTimer;		   	//休眠下巡检时间
		uint32 WorkCheckTimer;			//gongzuo下巡检时间
		uint32 LowVolTimer;				//电压低时多少时间内上传信息
		uint32 HighVolTimer;			//电压恢复正常时多少时间内上传信息	
		uint8 CenterPhone1[15];	  		//中心号码1
		uint8 CenterPhone2[15];   		// 中心号码2
		uint8 CheckPhone;				//巡检号码	 1：1号中心   2：2号中心
		uint8 TimePhone;				//追踪号码	 1：1号中心   2：2号中心
		uint8 CenPhone[15];				//短信服务中心号码
		uint8  EnableChar[3];			//使能防拆字符
		uint8 VoAlarmState;
		uint16 CanId;	 				//CANID
			//st_Da_CanInfor	CN_st_Da_CanInfor[2];
		uint32 CanSendTimer;			//
		uint8  AccFun;					//acc空能开
		uint8  ControlEnable; 			//是否控制
		uint32 HighV;					//电压多高是正常
		uint32 HighL;					//电压多低时正常
	}st_File_Parameter;

	typedef struct
	{	uint8 SoftEdition[8];				//软件版本
		uint8 HardEdition[8];				//硬件版本
		uint8 MachID[16];					//机器编号
		uint8 MachType[2];					//机器类型
		uint8 MakeFactory[2];				//厂家代号
	}st_File_Basic;

	typedef struct
	{	uint16 CanID[De_Can_Data_MaxID];	//能够接受的CAN的数据
	
	}st_File_CanID;

	typedef struct
	{	uint32 Timer;					//定时回传的时间
		uint32 Number;					//定时回传的次数
		uint32 NonceNumber;				//当前回传的次数
	}st_File_UpLoader;	
	typedef struct
	{	uint8 DateTime[7];
		uint8 Phone[15];
		uint8 Message[200];	
	}st_File_Message;

	typedef struct
	{	uint16 	Parameterfd;			//参数ID
		uint16	Basicfd;				//基本参数ID
		uint16 	CanIDfd;				//CAN
		uint16 	UpLoaderfd;				//
	   	uint16	Messagefd;
		uint16	AccTimerfd;
		uint16	MessageSend;
		uint16	GpsMessagefd;
	}st_File_fd;



	/*+++++++++++++++++++++++++++++++++++++系统运行过程中的状态++++++++++++++++++++++++++++++++++++++++++++++++++*/
	typedef struct
	{	uint8 GpsState;						//GPS状态
		uint8 GsmState;						//GSM状态
		uint8 FlashState;					//FLASH状态
		uint8 AccState;						//ACC状态
		uint8 AccFunction;					//Acc功能
		uint8 Sleep;						//是否休眠
		uint8 voltage;						//电压是否正常
		uint8 Speed;						//车速是否正常
		uint8 Control;						//是否控制								 
	}st_Sys_State;

	typedef struct
	{	uint8 Messagefd;					//接受短信息事件
		uint8 Phonefd;						//电话事件
		uint8 Gpsfd;						//GPS事件
		uint8 Accfd;						//Acc开启事件
		uint8 AccSleepfd;					//Acc关闭休眠						
		uint8 VoDownfd;						//低电压报警事件
		uint8 VoUpfd;						//电压恢复
		uint8 Sleepfd;						//休眠事件
		uint8 UpSleepfd;					//正常状态事件
		uint8 SleepCheckTimer;			//休眠状态下的巡检事件
		uint8 CheckTimer;					//工作状态下的巡检事件
		uint8 Timerfd;						//定时回传事件
		uint8 Canfd;						//CAN接受事件
		uint8 CanSendfd;					//CAN发送事件
		uint8 HandfdGsm;						//手柄通讯事件
		uint8 HandfdGps;						//手柄通讯事件
		uint8 TraCheckDatafd;
		uint8 DellGpsfd;

	}st_Sys_Event;
	typedef struct
	{	uint32	FrameData[2];
	}st_CanData;

	typedef struct
	{	st_CanData 	CN_CanData[De_Can_Data_MaxID];
		uint16		CanID[De_Can_Data_MaxID];
		uint8 DateTime[7];
	}st_Data_Can;
	typedef struct
	{	uint8 Speed;				//速度
		uint32 Vol;					//电压
		uint32 Timer;				//定时回传
		uint32 CheckTimer;			//巡检

	}st_Waring_Sys;




/*==========================================Static Function=====================================================*/	
	void CheckFile(void);
	void SendMessage(uint8 *Buf,uint8 *Phone);
	void Get_Gps_Data(uint8 *Buf);
	void GetPhone(uint8 *Phone,uint8 *CenterNum);
	void Get_Gps_DataHand(uint8 *Buf);
	void BackInit(void);
	void InitCenPhone(void);
	#ifdef De_FileData_Compiler
		static void Get_Sys_State(void);
		static void CheckFile_Basic(void);
		static void CheckFile_CanID(void);
		static void CheckFile_Parameter(void);
		static void CheckFile_Acc(void);
		static void CheckFile_UpLoader(void);
		static void CheckFile_Message(void);						//短信息
		static void CheckFile_MessageState(void);
		static void CheckFile_GpsMessage(void);
		static void BackBasic(void);
		static void BackCan(void);
		static void BackPareameter(void);
		static void BackUpLoader(void);
		static void BackAccTimer(void);
/*============================================Public Ram=========================================================*/	
		st_Sys_State	CN_st_Sys_State;
		st_Sys_Event	CN_st_Sys_Event;
		st_Data_Can		CN_st_Data_Can;	
		st_Waring_Sys	CN_st_Waring_Sys;
		st_File_fd		CN_st_File_fd;
		uint16			MessageTail;
		uint16			MessageSendSpace;
		uint16 			MessageNumber;	
		uint8			CN_X_BUF[512];
		uint8			SleepCheck;
		uint8			TimeSend;
		OS_EVENT *FileDataSem;
	#else
		extern st_Sys_State	CN_st_Sys_State;
		extern st_Sys_Event	CN_st_Sys_Event;
		extern st_Waring_Sys	CN_st_Waring_Sys;
		extern st_Data_Can		CN_st_Data_Can;	
		extern uint8			CN_X_BUF[512];
		extern uint16			MessageTail;
		extern uint16			MessageSendSpace;
		extern uint16 			MessageNumber;
		extern st_File_fd		CN_st_File_fd;
		extern uint8			SleepCheck;
		extern uint8			TimeSend;
#endif






