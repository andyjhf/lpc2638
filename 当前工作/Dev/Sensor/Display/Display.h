/*==========================================include Define========================================================*/
 	#include "..\..\..\APP\config.h"
	#include "stdlib.h"
	#ifdef De_Display_Compiler
		#include "..\..\..\miscellaneous\CodeTrans\AscNumber.h"	
		#include "..\..\..\HardWare\UART\UART.h"
		#include "..\..\..\miscellaneous\Date\date.h"
		#include "..\_PuSensor.h"
	#endif
/*==========================================Define Data==========================================================*/
	#define De_Suc_Display									De_Suc_Sensor
	/*++++++++++++++++++++++++++++++++错误代码一览表+++++++++++++++++++++++++++++++++++++++++++++++++*/
   	#define De_Erro_Display_Explain							1
	#define De_Erro_Display_Init							De_Erro_Display_Explain+1
	#define De_Erro_Display_OverMaxNumber  					De_Erro_Display_Init+1
	#define De_Erro_Display_NoOrder							De_Erro_Display_OverMaxNumber+1
	#define De_Erro_Display_NoData 							De_Erro_Display_NoOrder+1

	/*++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/
	
	#define De_Display_Par_Type_int16								0  					//INT变量
	#define De_Display_Par_Type_Asc									1					//ASC变量
	#define De_Display_Par_Type_IP									2					//IP变量
	#define De_Display_Par_Type_uint16								3					//UINT16变量
	#define De_Display_Par_Type_uint8 								4					//UIN8变量
	#define De_Display_Par_Type_uint32								5					//32变量
	#define De_Display_Par_Type_MacID								6					//MACHI变量


	#define De_Display_Use_Port										0	//使用情况

	#define De_Display_Answer_Yes									1					//要应答
	#define De_Display_Answer_No									0					//不要应答
	#define De_Display_MaxDly										0xfffff				//超时时间

	#define De_Display_Fun_Open										1					//开调度屏
	#define De_Display_Fun_Close									0					//关调度屏


/*===========================================Data Define========================================================*/
#ifdef De_Display_Compiler	
	typedef struct
	{	uint16 Par;	   					//c查询与设定的参数
		uint8 Type;						//参数类型
	}st_Display_Par2Type;

	typedef struct
	{	uint8 OrderID;					//命令
		uint8 Answer;					//是否需要应答
		uint16 (*ptFun)(void *Buf,uint8 ID);  //发送函数
	}st_Host_SendData;
#endif

/*=========================================static Function=======================================================*/
#ifdef De_Display_Compiler
	static uint16 Init(void);
	static uint16 Open(st_Sensor_DataPar	*ptst_Sensor_DataPar,uint8 *fd);
	static uint16 Read1(uint8 fd,void *SendBuf,void *AgreeBuf);
	static uint16 Close(uint8 fd);
	static uint16 Read(uint8 fd,void *SendBuf,void *AgreeBuf);
	
	static uint16 Host_Answer(void *Buf,uint8 ID);									//命令应答成功
	static uint16 Host_DeliverCentr(void *Buf,uint8 ID);
	static uint16 Host_SysInfor(void *Buf,uint8 ID);	  							//系统信息
	static uint16 Host_Phone(void *Buf,uint8 ID);  									//电话指令
	static uint16 Host_InitStart(void *Buf,uint8 ID);  								//初始化指令开始
	static uint16 Host_InitOver(void *Buf,uint8 ID);						  		//初始化指令结束
	static uint16 Host_HostSoft(void *Buf,uint8 ID);			   					//升级进度条
	static uint16 Host_ConInfor(void *Buf,uint8 ID);		   						//控制类信息
	static uint16 Host_ParAnswer(void *Buf,uint8 ID);								//参数查询应答
	
	static uint16 Agree(void *AgreeBuf);
	static uint16 AgreeData(uint8 *AgreeBuf,uint16 SizeofBuf,uint16 *AgreeBufSize);
	static void Send(uint8 ID,uint8 *Buf,uint16 SizeofBuf);	  					//发送数据
	
	static uint16 App2CommType(void *Buf,uint8 *AgreeBuf,uint8 i);
	static uint16 CommType2App(uint8 *Buf,st_Display_Par *ptst_Display_Par,uint16 Par,uint16 SizeofAgreeBuf);
	static uint16 Int162Asc(uint16 Val,uint8 *Asc);
	static uint16 Asc2Int16(uint8 *Asc,uint8 SizeofAsc);
#endif
/*===========================================================================================================*/
	
#ifdef De_Display_Compiler
	


	const st_Display_Par_Set	CN_st_Display_Par_Set[]=
	{	{De_Display_Par_Integral,De_Display_Par_Type_int16,&((st_Display_Par_Cut	*)NULL)->Integral,5},
		{De_Display_Par_ListenPhone,De_Display_Par_Type_Asc,((st_Display_Par_Cut	*)NULL)->ListenPhone,15},
	   	{De_Display_Par_ResetPhone,De_Display_Par_Type_Asc,((st_Display_Par_Cut	*)NULL)->ResetPhone,15},
	   	{De_Display_Par_CentrSevenPhone,De_Display_Par_Type_Asc,((st_Display_Par_Cut	*)NULL)->CentrSevenPhone,sizeof(((st_Display_Par_Cut	*)NULL)->CentrSevenPhone)},
	   	{De_Display_Par_APN,De_Display_Par_Type_Asc,((st_Display_Par_Cut	*)NULL)->APN,sizeof(((st_Display_Par_Cut	*)NULL)->APN)},
	   	{De_Display_Par_MastIP,De_Display_Par_Type_IP,&((st_Display_Par_Cut	*)NULL)->MastIP,sizeof(((st_Display_Par_Cut	*)NULL)->MastIP)},
	   	{De_Display_Par_MastDomain,De_Display_Par_Type_Asc,((st_Display_Par_Cut	*)NULL)->MastDomain,sizeof(((st_Display_Par_Cut	*)NULL)->MastDomain)},
	   	{De_Display_Par_ReserveIP,De_Display_Par_Type_IP,&((st_Display_Par_Cut	*)NULL)->ReserveIP,sizeof(((st_Display_Par_Cut	*)NULL)->ReserveIP)},
	   	{De_Display_Par_ReserveDomain,De_Display_Par_Type_Asc,((st_Display_Par_Cut	*)NULL)->ReserveDomain,sizeof(((st_Display_Par_Cut	*)NULL)->ReserveDomain)},
	   	{De_Display_Par_CenPort,De_Display_Par_Type_uint16,&((st_Display_Par_Cut	*)NULL)->CenPort,sizeof(((st_Display_Par_Cut	*)NULL)->CenPort)},
	   	{De_Display_Par_CentHeart,De_Display_Par_Type_uint8,&((st_Display_Par_Cut	*)NULL)->CentHeart,sizeof(((st_Display_Par_Cut	*)NULL)->CenPort)},
	   	{De_Display_Par_DsnSever,De_Display_Par_Type_IP,&((st_Display_Par_Cut	*)NULL)->DsnSever,sizeof(((st_Display_Par_Cut	*)NULL)->DsnSever)},
		{De_Display_Par_MachiID,De_Display_Par_Type_Asc,((st_Display_Par_Cut	*)NULL)->MachiID,sizeof(((st_Display_Par_Cut	*)NULL)->MachiID)},
	   	{De_Display_Par_PassWord,De_Display_Par_Type_uint32,&((st_Display_Par_Cut	*)NULL)->PassWord,sizeof(((st_Display_Par_Cut	*)NULL)->PassWord)},
	   	{De_Display_Par_SoftWare,De_Display_Par_Type_Asc,((st_Display_Par_Cut	*)NULL)->SoftWare,sizeof(((st_Display_Par_Cut	*)NULL)->SoftWare)},
	   	{De_Display_Par_SelfIP,De_Display_Par_Type_IP,&((st_Display_Par_Cut	*)NULL)->SelfIP,sizeof(((st_Display_Par_Cut	*)NULL)->SelfIP)},
	   	{De_Display_Par_NonceIP,De_Display_Par_Type_IP,&((st_Display_Par_Cut	*)NULL)->NonceIP,sizeof(((st_Display_Par_Cut	*)NULL)->NonceIP)},
	   	{De_Display_Par_CommEdit,De_Display_Par_Type_uint8,&((st_Display_Par_Cut	*)NULL)->CommEdit,sizeof(((st_Display_Par_Cut	*)NULL)->CommEdit)},
	   	{De_Display_Par_Tracks,De_Display_Par_Type_uint32,&((st_Display_Par_Cut	*)NULL)->Tracks,sizeof(((st_Display_Par_Cut	*)NULL)->Tracks)}
	};



	static const st_Display_Par2Type	CN_Ba_st_Display_Par2Type[]=
	{	{	De_Display_Par_Integral,De_Display_Par_Type_int16	},					//当前积分			
		{	De_Display_Par_ListenPhone,De_Display_Par_Type_Asc	},					//监听号码
		{	De_Display_Par_ResetPhone,De_Display_Par_Type_Asc	},					//复位号码
		{	De_Display_Par_CentrSevenPhone,De_Display_Par_Type_Asc},				//短信服务号码
		{	De_Display_Par_WarningPhone,De_Display_Par_Type_Asc	},					//报警号码
		{	De_Display_Par_APN,De_Display_Par_Type_Asc			},	   				//APN									//APN参数
		{	De_Display_Par_MastIP,De_Display_Par_Type_IP		},					//主中心服务IP
		{	De_Display_Par_MastDomain,De_Display_Par_Type_Asc	},					//主域名
		{	De_Display_Par_ReserveIP,De_Display_Par_Type_IP		},					//副中心IP
		{	De_Display_Par_ReserveDomain,De_Display_Par_Type_Asc},					//副中心域名
		{	De_Display_Par_CenPort,	De_Display_Par_Type_uint16	},					//中心端口号
		{	De_Display_Par_CentHeart,De_Display_Par_Type_uint8	},					//中心心跳间隔
		{	De_Display_Par_DsnSever,De_Display_Par_Type_IP		},					//DSN
		{	De_Display_Par_MachiID,	De_Display_Par_Type_MacID	},					//车机ID
		{	De_Display_Par_PassWord,De_Display_Par_Type_uint32	},					//密码
		{	De_Display_Par_SoftWare,De_Display_Par_Type_Asc		},					//软件版本号
		{	De_Display_Par_SelfIP,De_Display_Par_Type_IP		},					//本身IP
		{	De_Display_Par_NonceIP,De_Display_Par_Type_IP		},					//当前中心IP
		{	De_Display_Par_CommEdit,De_Display_Par_Type_uint8	},					//协议版本号
		{	De_Display_Par_Tracks,De_Display_Par_Type_uint32	}					//追踪间隔
	};

	static const st_Host_SendData	CN_Ba_st_Host_SendData[]=
	{	{	De_Display_Host_Order_Answer,De_Display_Answer_No,Host_Answer},
		{	De_Display_Host_Order_DeliverCentr,De_Display_Answer_Yes,Host_DeliverCentr},
		{	De_Display_Host_Order_SysInfor,De_Display_Answer_Yes,Host_SysInfor},
		{	De_Display_Host_Order_Phone,De_Display_Answer_Yes,Host_Phone},
		{	De_Display_Host_Order_InitStart,De_Display_Answer_Yes,Host_InitStart},
		{	De_Display_Host_Order_InitOver,De_Display_Answer_Yes,Host_InitOver},
		{	De_Display_Host_Order_HostSoft,De_Display_Answer_Yes,Host_HostSoft},
		{	De_Display_Host_Order_ConInfor,De_Display_Answer_Yes,Host_ConInfor},
		{	De_Display_Host_Order_ParAnswer,De_Display_Answer_No,Host_ParAnswer}
	};
	static OS_EVENT	*DisplaySem=NULL;
	static uint8 CN_State;
	static const st_Fun_Sensor2Hard	CN_st_Fun_Sensor2Hard={Init,Open,Close,Read1,NULL};
	static const st_Sensor_Par2Type	CN_st_Sensor_Par2Type=
	{	De_Sensor_WordPar_Display,De_Sensor_Par_Display
	};
	const st_Sensor_ParList		CN_Display_st_Sensor_ParList=
	{	&CN_st_Fun_Sensor2Hard,&CN_st_Sensor_Par2Type,sizeof(CN_st_Sensor_Par2Type)/sizeof(st_Sensor_Par2Type)
	};

#else
 	extern const st_Sensor_ParList		CN_Display_st_Sensor_ParList;
	extern const st_Display_Par_Set	CN_st_Display_Par_Set[];

#endif








   









