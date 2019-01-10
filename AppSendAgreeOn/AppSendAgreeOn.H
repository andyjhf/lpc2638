/*===========================================Include File========================================================*/
	#include "..\APP\config.h"
	#include "stdlib.h"
	#ifdef De_AppSendAgreeOn_Compiler
		#include "..\File\rwFile.h"
		#include "..\miscellaneous\CodeTrans\AscNumber.h"
		#include "..\FilleData\FileData.h"
		#include "..\FilleData\TakeData.h"
		#include "..\Dev\Sensor\Sensor.h"
		#include "..\AgreeOn\TzV2.1.h"
		#include "..\AgreeOn\TzV2.1\Send\Tz_Send.h"
		#include "..\AppTask\OpenClose\OpenAndClose.H"
		#include "SeeAbout.c"
		
	#endif
/*===========================================Define Data=========================================================*/		
	#define De_Suc_AppSendAgree														0
	#define De_Erro_AppSendAgreeOn_NoLink											1
	#define De_Erro_AppSendAgreeOn_NoVid 											De_Erro_AppSendAgreeOn_NoLink+1

	#define De_Suc_Oper																0
	#define De_Erro_Oper															1
	#define De_WriteFlow_VidType_Yes												1			//拍照
	#define De_WriteFlow_VidType_No													NULL		//不拍照
   	#ifdef De_AppSendAgreeOn_Compiler
		#define De_SendCm_NoSemSend					0
		#define De_SendCm_WriteFlow					1	
		#define De_SendCm_WriteCommand				2
		#define De_SendCm_Answer					3
		#define De_Stk_Size							640
		#define De_Task_Number						4
	#endif
/*===========================================Data Define=========================================================*/
	typedef struct
	{	uint8 Number;
		uint8 OutOrIn;
	}st_OutRoadMap_Input;
	typedef struct
	{	uint8 Type;
		uint8 ID[10];
	}st_UpLoaderDriver_Input;
	typedef struct
	{	uint8 ID[10];
		uint8 Phone[15];
		uint8 Cut[160];
	}st_UpLoaderHandMess_Input;
	typedef struct
	{	uint16 (*Init)(void);
		void (*NoSemSend)(void);
		uint16 (*WriteFlow)(uint8 ID,st_WorkFlow_Table	*ptst_WorkFlow_Table,uint8 VidType);
		uint16 (*WriteCommand)(uint8 fd,uint16 Par,st_st_AgreeOn_Dev_Par	*ptst_st_AgreeOn_Dev_Par);
		void (*Answer)(st_st_AgreeOn_Dev_Par	*ptst_st_AgreeOn_Dev_Par,uint8 fd,uint16 Result);
	}st_Fun_AppSendAgreeOn;

	#ifdef De_AppSendAgreeOn_Compiler
		typedef struct
		{	uint8 Type;
			uint16 Par;
		}st_Type2Par_Data;
	
	   	typedef struct
		{	uint16 Par;
			uint16 (*ptFun)(uint8 fd,void *Buf);
		}st_Par2Fun_Par;
		typedef struct
		{	uint8 Command;
			uint16 Result;
			void *Buf;
		}st_AppSendAgreeOn_Cm;
		typedef struct
		{	uint8 fd;
			uint16 Par;
			st_st_AgreeOn_Dev_Par	*ptst_st_AgreeOn_Dev_Par;
		}st_AppSendAgreeOn_Cm_WriteCommand;
		typedef struct
		{	uint8 ID;
			st_WorkFlow_Table	*ptst_WorkFlow_Table;
			uint8 VidType;
		}st_AppSendAgreeOn_Cm_WriteFlow;
	#endif
/*=======================================static Function=========================================================*/
#ifdef De_AppSendAgreeOn_Compiler	
	static uint16 Init(void);
	static void NoSemSend(void);
	static uint16 WriteFlow(uint8 ID,st_WorkFlow_Table	*ptst_WorkFlow_Table,uint8 VidType);
	static uint16 WriteCommand(uint8 fd,uint16 Par,st_st_AgreeOn_Dev_Par	*ptst_st_AgreeOn_Dev_Par); 
	static void Answer(st_st_AgreeOn_Dev_Par	*ptst_st_AgreeOn_Dev_Par,uint8 fd,uint16 Result);
	/*====================================================================================================*/
	static uint16 NoSemSend1(void); 		
	static uint16 NoSemTrack(void);
	static uint16 NoSemWorkPar(void);
	static uint16 NoSemReduce(void);
	static uint16 NoSemJpgData(void);
	static uint16 WriteFlow2(uint8 ID,st_WorkFlow_Table	*ptst_WorkFlow_Table,uint8 VidType);
	static uint16 SendData(uint16 Recoder);
	static uint16 LoadJpg(uint16 Recoder);
	static uint16 WriteFlow1(uint8 ID,st_WorkFlow_Table	*ptst_WorkFlow_Table,uint8 VidType);
	
	static uint16 Send(uint8 fd,uint16 Par,void *Buf);
	static uint16 LogInfor(uint8 fd,void *Buf);				//定位终端登录信息
	static uint16 Orientation(uint8 fd,void *Buf); 			//上传位置信息
	static uint16 Menum(uint8 fd,void *Buf);				//上传菜单信息
	static uint16 TxtMenum(uint8 fd,void *Buf);				//上传带菜单的反馈信息	
	static uint16 LookPar(uint8 fd,void *Buf);				//上传定位终端参数
	static uint16 UpdateSoftWare(uint8 fd,void *Buf);		//上传软件升级状态
	static uint16 Waring(uint8 fd,void *Buf);				//上传报警状态
	static uint16 UploaderJpg1(uint8 fd,void *Buf);			//上传照片一
	static uint16 UploaderJpg2(uint8 fd,void *Buf);			//上传照片二
	static uint16 UploaderPar(uint8 fd,void *Buf);		//上传工作参数
	static uint16 UploaderLog(uint8 fd,void *Buf);
	static uint16 UpLoaderWarning(uint8 fd,void *Buf);
	static uint16 OutRoadMap(uint8 fd,void *Buf);
	static uint16 UpLoaderReduce1(uint8 fd,void *Buf);
	static uint16 UpLoaderDriver(uint8 fd,void *Buf);
	static uint16 UpLoaderHandMess(uint8 fd,void *Buf);
	static uint16 UploaderJpg2Sig(uint8 fd,uint16 Recoder,uint8 Number);
	static uint16 UpLoaderLog_Par(uint8 fd,st_AgreeOn_LookLog	*ptst_AgreeOn_LookLog);
	static uint16 TrackDataExplain(uint16 Recoder,uint8 *Data,uint16 *ReLen);
	static uint16 UpLoaderJpHistory(uint8 fd,st_AgreeOn_LookLog	*ptst_AgreeOn_LookLog);
	static uint16 LoaderJpgData(uint16 Recoder,uint8 fd);
	static uint16 WorkParDataExpalin(uint16 Recoder,uint8 *Data,uint16 *ReLen);
	static uint16 UpLoaderReduce(uint16 Recoder,uint8 *Data,uint16 *ReLen);
	static void SendLogin(void); 
	static uint16 PhotoOper(void);
	static uint16 UpLoaderDriverExplain(uint16 Recoder,uint8 *Data,uint16 *ReLen);
	static uint16 NoSemDriver(void);
	static void Task(void *pData);
#endif
/*========================================Public Ram===============================================================*/
#ifdef De_AppSendAgreeOn_Compiler	
	static OS_EVENT	*AppSendAgreeOnSem=NULL;
	static OS_EVENT	*AppSendAgreeOnSem1=NULL;
	static OS_EVENT	*CN_Box_AppSend=NULL;
	static uint8 X_BUF[2048];
	st_st_AgreeOn_Dev_WritePar	CN_Pu_st_st_AgreeOn_Dev_WritePar;
	static const uint8 CN_Ba_VidType[]=
	{ 	De_Access_Type_AccOpenVid,De_Access_Type_AccCloseVid,De_Access_Type_HelpVid,
		De_Access_Type_EngineVid,De_Access_Type_WaringParVid,De_Access_Type_CarPower
	};
	static const st_Type2Par_Data CN_Ba_Type2Par[]=
	{	{	De_Access_Type_Help,De_Dev_Order_Waring	},																//求助报警
		{	De_Access_Type_HighSpeed,De_Dev_Order_Waring	},	//超速报警
		{	De_Access_Type_LowSpeed,De_Dev_Order_Waring	},		//低速报警
		{	De_Access_Type_LowVo,De_Dev_Order_Waring	},		//低电压报警
		{	De_Access_Type_ClosePower,De_Dev_Order_Waring	},	//断电报警
		{	De_Access_Type_LCD,De_Dev_Order_Waring	},			//LCD故障
		{	De_Access_Type_VidClose,De_Dev_Order_Waring	},		//视频拆除
		{	De_Access_Type_GpsErro,De_Dev_Order_Waring	},		//GPS模块故障
		{	De_Access_Type_GpsLessOpen,De_Dev_Order_Waring	},			//GPS开路
		{	De_Access_Type_GpsLessClose,De_Dev_Order_Waring	},			//Gps天线短路
		{	De_Access_Type_WorkParWaring,De_Dev_Order_Waring },		//工作参数报警
		{	De_Access_Type_LessState,De_Dev_Order_Waring	},			//无线传感器状态报警
		{	De_Access_Type_Track,De_Dev_Order_Orientation	},			//追踪
		{	De_Access_Type_WorkPar,De_Dev_Order_UploaderPar	},			//工作参数
		{	De_Access_Type_CarPower,De_Dev_Order_UploaderJpg2},			//发动机运转时拍照
		{	De_Access_Type_ReduceWork,De_Dev_Order_UpLoaderReduce},		//工作参数
		{	De_Access_Type_ReduceTrack,De_Dev_Order_UpLoaderReduce},	//追踪参数
		{	De_Access_Type_WorkParWaringVid,De_Dev_Order_UploaderJpg2},	//工作参数拍照
		{	De_Access_Type_AccOpenVid,De_Dev_Order_UploaderJpg2},	//ACC打开拍照
		{	De_Access_Type_AccCloseVid,De_Dev_Order_UploaderJpg2},	//ACC关闭
		{	De_Access_Type_HelpVid,De_Dev_Order_UploaderJpg2},		//求助
		{	De_Access_Type_EngineVid,De_Dev_Order_UploaderJpg2},	//发动机
		{	De_Access_Type_WaringParVid,De_Dev_Order_UploaderJpg2},	//报警参数
		{	De_Access_Type_PowerClose,De_Dev_Order_Orientation},	//关闭电源
		{	De_Access_Type_GprsClose,De_Dev_Order_Orientation},		//关闭GPRS
		{	De_Access_Type_JugeLog,De_Dev_Order_UpLoaderDriver},
		{	De_Access_Type_ExitLog,De_Dev_Order_UpLoaderDriver},
		{	De_Access_Type_LogErro,De_Dev_Order_UpLoaderDriver}
	};
	static const uint8 CN_Ba_NoData[]=
	{	De_Access_Type_Help,De_Access_Type_HighSpeed,De_Access_Type_LowSpeed,De_Access_Type_LowVo,
		De_Access_Type_ClosePower,De_Access_Type_LCD,De_Access_Type_VidClose,De_Access_Type_GpsLessOpen,
	   	De_Access_Type_GpsLessClose,De_Access_Type_WorkParWaring,De_Access_Type_LessState,De_Access_Type_PowerClose,
		De_Access_Type_GprsClose
	};
	static const st_Par2Fun_Par	CN_Ba_st_Par2Fun_Par[]=
	{	{	De_Dev_Order_Login,LogInfor},								//定位终端登录
		{	De_Dev_Order_Sleep,Orientation	},							//定位终端休眠
		{	De_Dev_Order_CloseModerm,Orientation	},					//定位终端关机
		{	De_Dev_Order_Orientation,Orientation	}, 					//上传位置信息
		{	De_Dev_Order_Menum,Menum},									//上传菜单信息
		{	De_Dev_Order_TxtMenum,TxtMenum},							//上传带菜单的反馈信息
		{	De_Dev_Order_LookPar,LookPar},
		{	De_Dev_Order_UpdateSoftWare,UpdateSoftWare},
		{	De_Dev_Order_Waring,Waring},
		{	De_Dev_Order_UploaderJpg1,UploaderJpg1},
		{	De_Dev_Order_UploaderJpg2,UploaderJpg2},
		{	De_Dev_Order_UploaderPar,UploaderPar},
		{	De_Dev_Order_UploaderLog,UploaderLog},
		{	De_Dev_Order_UpLoaderWarning,UpLoaderWarning},
		{	De_Dev_Order_OutRoadMap,OutRoadMap},
		{	De_Dev_Order_UpLoaderReduce,UpLoaderReduce1},
		{	De_Dev_Order_UpLoaderDriver,UpLoaderDriver},
		{	De_Dev_Order_UpLoaderHandMess,UpLoaderHandMess},	
	};
	static const uint8 *JugePar[]=
	{	&(((st_WorkFlow_Table	*)(NULL))->CN_st_WorkVal_Tabel.CN_st_AgreeOn_SetVidType_Par.CN_Less_Switch1.State),
		&(((st_WorkFlow_Table	*)(NULL))->CN_st_WorkVal_Tabel.CN_st_AgreeOn_SetVidType_Par.CN_Less_Switch2.State),
		&(((st_WorkFlow_Table	*)(NULL))->CN_st_WorkVal_Tabel.CN_st_AgreeOn_SetVidType_Par.CN_Less_Switch3.State),
		&(((st_WorkFlow_Table	*)(NULL))->CN_st_WorkVal_Tabel.CN_st_AgreeOn_SetVidType_Par.CN_Less_Switch4.State),
		&(((st_WorkFlow_Table	*)(NULL))->CN_st_WorkVal_Tabel.CN_st_AgreeOn_SetVidType_Par.CN_Less_Switch5.State),
		&(((st_WorkFlow_Table	*)(NULL))->CN_st_WorkVal_Tabel.CN_st_AgreeOn_SetVidType_Par.CN_Less_Switch6.State),
		&(((st_WorkFlow_Table	*)(NULL))->CN_st_WorkVal_Tabel.CN_st_AgreeOn_SetVidType_Par.CN_st_AgreeOn_Less_Temp1.State),
		&(((st_WorkFlow_Table	*)(NULL))->CN_st_WorkVal_Tabel.CN_st_AgreeOn_SetVidType_Par.CN_st_AgreeOn_Less_Temp2.State),
		&(((st_WorkFlow_Table	*)(NULL))->CN_st_WorkVal_Tabel.CN_st_AgreeOn_SetVidType_Par.CN_st_AgreeOn_Less_Temp3.State),
		&(((st_WorkFlow_Table	*)(NULL))->CN_st_WorkVal_Tabel.CN_st_AgreeOn_SetVidType_Par.CN_st_AgreeOn_Less_Temp4.State)
	};
	const st_Fun_AppSendAgreeOn	CN_st_Fun_AppSendAgreeOn={Init,NoSemSend,WriteFlow,WriteCommand,Answer};
	static OS_STK	STK[De_Stk_Size];
#else
	extern const st_Fun_AppSendAgreeOn	CN_st_Fun_AppSendAgreeOn;
#endif

















