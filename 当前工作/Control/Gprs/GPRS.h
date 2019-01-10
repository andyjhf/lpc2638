#define GPRS_H
#ifdef 	GPRS_H
/*==========================================Include File====================================================*/	
	#include "..\..\APP\config.h"											//LPC2368寄存器引用
 	#include "stdlib.h"	
	
	#ifdef De_GPRS_Compiler													//C函数引用
		#include "..\..\Dev\Gprs\_GprsHard.h"
		#include "..\..\miscellaneous\CodeTrans\AscNumber.h"				//引用码制转换资源
		#include "..\..\miscellaneous\Date\Date.h"							//引用日期资源
		#include "..\..\miscellaneous\Arithmetic\Arithmetic.h" 				//引入算法
		#include "..\..\Control\Timer\Timer.h"								//引用时间计时
		#include "..\..\File\rwFile.h"
	#else
		#include "..\..\Dev\Gprs\GprsPublicDe.h"
	#endif
/*=========================================Define Data======================================================*/
	#define De_Suc_Gprs														0				//成功
	/*-------------------------------------错误代码一览表-------------------------------------------------*/
	#define De_Erro_GprsLink_Over											1				//无打开的链路
	#define De_Erro_Gprs_Explain											De_Erro_GprsLink_Over+1	//解析错误
	#define De_Erro_Gprs_LinkClose											De_Erro_Gprs_Explain+1	// 此链路关闭
	#define De_Erro_Gprs_Init												De_Erro_Gprs_LinkClose+1	//初始化失败
	#define De_Erro_Gprs_State_NoOpen										De_Erro_Gprs_Init+1			//功能没有打开	
	#define De_Erro_Gprs_NoMessageData										De_Erro_Gprs_State_NoOpen+1	//没有短信数据
	#define De_Erro_Gprs_NoPhone											De_Erro_Gprs_NoMessageData+1	//没有新来电
	#define De_Erro_Gprs_NoIPData											De_Erro_Gprs_NoPhone+1		//没有GPRS数据
	#define De_Erro_Gprs_CardNoReg											De_Erro_Gprs_NoIPData+1		//此卡未注册
	#define De_Erro_Gprs_MEErro												De_Erro_Gprs_CardNoReg+1	//状态未好
	#define De_Erro_Gprs_NoTCPIP											De_Erro_Gprs_MEErro+1	 	//没有TCPIP
	#define De_Erro_Gprs_NoCall												De_Erro_Gprs_NoTCPIP+1		//没有电话
	#define De_Erro_Gprs_FunctionNo											De_Erro_Gprs_NoCall+1		//此功能没有开
	#define	De_Erro_Gprs_NoCard												De_Erro_Gprs_FunctionNo+1
	#define De_Erro_Gprs_AnswerPhone										De_Erro_Gprs_NoCard+1
	#define De_Erro_Gprs_Volume												De_Erro_Gprs_AnswerPhone+1
	/*----------------------------------------系统状态-------------------------------------------------*/
	
		#define De_Gprs_Phone_Agree_New											0 				//新来电
		#define	De_Gprs_Phone_Agree_Old											1				//旧来电
		#define De_Gprs_Phone_Agree_Ide											2				//闲置
		#define De_Gprs_UDPTCP_Agree_New										0				//新的数据包
		#define De_Gprs_UDPTCP_Agree_Old										1				//旧数据包
		#define De_Gprs_UDPTCP_Agree_Ide										2				//闲置
		#define De_Gprs_UDPTCP_Agree_Close										3				//链路未打开
		#define De_Gprs_State_Open												0				//状态打开
		#define De_Gprs_State_Close												1				//状态关闭
		#define De_Gprs_Fd_All													0xff			//代表关闭GPRS		
	/*-------------------------------------程序中各个大小限制----------------------------------------------*/
		#define De_Gprs_Message_Size											160				//短消息的大小
		#define De_Gprs_PhoneNumber_Size										15				//电话号码大小
		#define De_Gprs_TCPUDP_Size												1536			//UDP或者TCP包大小
		#define De_Gprs_HeartFlag_Size											32				//心跳包的大小
		#define De_Gprs_APN_Size												32				//APN参数大小
		#define De_Gprs_Use_Size												16				//用户名参数大小
		#define De_Gprs_PassWord_Size											8				//密码大小
		#define De_Moderm_Message_Max											10				//读未短信息
		#define De_Moderm_Message_Max1											20				//短消息最大长度
	/*++++++++++++++++++++++++++++++++操作系统有关++++++++++++++++++++++++++++++++++++++++*/
	#ifdef De_GPRS_Compiler
		#define De_Gprs_Task												4
		#define De_Gprs_Stk													384//1536
		#define De_Gprs_TaskDly												40				//延时调度时间
	#endif
/*============================================Data Define=====================================================*/
	/*++++++++++++++++++++++++++++++++++++++++数据结构定义+++++++++++++++++++++++++++++++++++++++++++*/
		/*---------------------------------对外使用结构体----------------------------------------*/
		typedef struct
		{	uint8 LinkType;											//IP链路状态  UDP  TCP
			uint32 IP;												//hex
			uint16 Com;												//hex
			uint32 SelfHeartTimer;									//本机心跳时间
			uint32 CentrHeartTimer;									//中心心跳时间
			uint8 SelfHeartData[De_Gprs_HeartFlag_Size];			//ASC,以‘/0'作为结束,本机心跳所发送的数据
			uint8 HeartDataLength;									//心跳包长度
			uint8 CentrHeartData[De_Gprs_HeartFlag_Size];			//ASC,以‘/0'作为结束,中心心跳所发送的数据
			uint8 CentrHeartLength;									//心跳包长度
		}st_Data_UDPTCP;											//UDP参数

		typedef struct
		{	uint8 Yys;												//查看运营商
		   	uint8 IMEI[7];											//IMEI
		   	uint8 Csq;	   											//信号强度
		   	uint8 RegisterState;									//注册情况
			uint8 ModelState;										//模块状态
			uint8 SimCarkState;
		}st_Gsm_Net_Information;
		
		typedef struct
		{	uint8 CenterNum[15];									//短信中心号码
		}st_Gsm_Net_Message;

/*		typedef struct
		{	uint8 APN[De_Gprs_APN_Size+1];							//ASC,以‘/0'作为结束
			uint8 Use[De_Gprs_Use_Size+1];							//ASC,以‘/0'作为结束
			uint8 PassWord[De_Gprs_PassWord_Size+1];				//ASC,以‘/0'作为结束	
		}st_Data_IPNet;		*/										//TCP/IP参数
		/*------------------------------------对外使用事件结构体-------------------------------------------*/
		typedef struct
		{	void (* ptFunNoSem)(void); 								//系统没有信号
			void (*	ptFunSem)(void);								//系统有信号
			void (*	ptFunNoWork)(void);								//系统不工作
			void (*	ptGPRS)(void);									//GPRSTCP/IP断开
		}st_Affair_Sys;												//系统事件

		typedef struct
		{	void (*	ptFunNewMessage)(uint8 *Phone,uint8 *Message);	//新短信息
		}st_Affair_Message;											//系统短消息事件

		typedef struct
		{	void (* ptFunNewPhone)(uint8 *Phone);					//新电话事件
			void (* ptFunHupWork)(uint8 *Phone);					//挂机事件
		}st_Affair_Phone;											//电话事件

		typedef struct
		{	void (*	ptFunNewTCPUDP)(uint8 *Data,uint8 fd,uint16 DataLength);	//新数据包函数
			void (*	ptFunLinkClose)(uint8 *fd);						//链路关闭,无心跳包
		}st_Affair_UDPTCP;
		typedef struct
		{	uint8 Phone[De_Gprs_PhoneNumber_Size]; 				//电话号码	
			uint8 State;										//来电号码状态
			uint8 Mod;	  										//电话模式
			uint8 PhoneState;									//电话状态
		}st_Data_Gprs_Call;                                		//电话数据
		typedef struct
		{	uint16 (*	Init)(void);								//初始化本页
			uint16 (*	InitSys)(void);								//初始化GPRS模块
			uint16 (*	InitMessage)(void);							//初始化短信息
			uint16 (*	InitPhone)(void);							//初始化电话
			uint16 (*	InitGprs)(st_Data_IPNet	*ptst_Data_IPNet);	//初始化TCP/IP
			
			uint16 (*	OpenSys)(st_Affair_Sys	*ptst_Affair_Sys);	//打开系统事件
			uint16 (*	OpenMessage)(st_Affair_Message	*ptst_Affair_Message);	  //打开短信事件
			uint16 (*	OpenIP)(st_Data_UDPTCP	*ptst_Data_UDPTCP,st_Affair_UDPTCP	*ptst_Affair_UDPTCP,uint8 *fd);	//打开一条链路并且打开对应的事件
			uint16 (*	OpenPhone)(st_Affair_Phone	*ptst_Affair_Phone);  //打开电话事件
					

			uint16 (*	CloseSys)(void);	//关闭系统事件
			uint16 (*	CloseMessage)(void); //打开短信事件
			uint16 (*	CloseIP)(uint8 fd);	//关闭一条链路并且关闭对应的事件   
			uint16 (*	ClosePhone)(void); //关闭电话事件
		
			uint16 (*	ReadMessage)(uint8 *Phone,uint8 *Message); 			//读新短信息
			uint16 (*	ReadIP)(uint8 fd,uint8 *Data,uint16 *SizeofData);	//读新数据包
			uint16 (*	ReadPhone)(uint8 *Phone);	  //读新来电
			uint16 (*	AgreePhone)(void);			 //接电话
			uint16 (*	CloseCall)(void);			 //挂电话
		
		
			uint16 (*	SendMessage)(uint8 *Phone,uint8 *Message);	 	//发送短信息
			uint16 (*	SendIP)(uint8 fd,uint8 *Data,uint16 SizeofData);  //发送IP数据
			uint16 (*	SendPhone)(uint8 *Phone,uint8 *PhoneState);		  //打电话
			uint16 (*	SetVolume)(uint8 Volume);						//设置音量
		
			uint16 (*	GetSysState)(st_Gsm_Net_Information	*ptst_Gsm_Net_Information);//获取系统状态
			uint16 (*	GetMessageState)(st_Gsm_Net_Message	*ptst_Gsm_Net_Message);	   //获取短信状态
			uint16 (*	GetPhoneState)(st_Data_Gprs_Call	*ptst_Data_Gprs_Call);	   //获取电话状态
			uint16 (*	GetIPState)(st_Data_UDPTCP	*ptst_Data_UDPTCP,st_HardWare_SeeTCPData	*ptst_HardWare_SeeTCPData);//获取TCP/IP状态
		 	uint16 (*	DNSRIP)(uint8 *DomainName,uint32 *IP);
			uint16 (*	GetIpPro)(uint8 fd,st_Data_UDPTCP	*ptst_Data_UDPTCP);
		 
		 }st_Fun_Gprs;
		/*--------------------------------内部接受数据的定义-------------------------------------*/
	#ifdef De_GPRS_Compiler		
		typedef struct
		{	uint32 SelfHeartTimer;
			uint32 CentrHeartTimer;
		}st_Heart_Timer;
		typedef struct
		{	uint8 Message[De_Gprs_Message_Size+1];	 			//短消息保存
			uint8 Phone[De_Gprs_PhoneNumber_Size+1];		 	//短消息号码保存
			uint8 State;										//新短消息或者旧
		}st_Data_Gprs_Message;									//短信息保存
		typedef struct
		{	uint8 State;										//数据状态
			uint8 OpenOrClose;									//打开或者不打开
			uint16 DataLen;										//长度
			uint8 Data[De_Gprs_TCPUDP_Size];					//数据
			st_Data_UDPTCP	CN_st_Data_UDPTCP;					//参数数据
			st_Heart_Timer	CN_st_Heart_Timer;
		}st_Data_Gprs_TcpUdp;									//数据
		/*----------------------------------------事件汇总表-------------------------------------------------*/
		typedef struct
		{	uint8 SysState;								//系统打开状态
			uint8 MessageState;							//短信打开状态
			uint8 PhoneState;							//电话打开状态
			uint8 IPstate;								//IP打开状态
			st_Affair_Sys	CN_st_Affair_Sys;			//系统事件
		   	st_Affair_Message	CN_st_Affair_Message;	//短信事件
		  	st_Affair_Phone		CN_st_Affair_Phone;		//电话事件
			st_Affair_UDPTCP	CN_st_Affair_UDPTCP[De_GprsHard_MaxLink];//UDP事件
		}st_Affair_Gprs;
	#endif
/*===========================================static Functiion================================================*/
	#ifdef De_GPRS_Compiler	
		static uint16 Init(void);
		static uint16 InitSys1(void);
		static uint16 InitMessage1(void);
		static uint16 InitPhone1(void);
		static uint16 InitGprs1(st_Data_IPNet	*ptst_Data_IPNet);
		
		static uint16 OpenSys1(st_Affair_Sys	*ptst_Affair_Sys);
		static uint16 OpenMessage1(st_Affair_Message	*ptst_Affair_Message);
		static uint16 OpenIP1(st_Data_UDPTCP	*ptst_Data_UDPTCP,st_Affair_UDPTCP	*ptst_Affair_UDPTCP,uint8 *fd);
		static uint16 OpenPhone1(st_Affair_Phone	*ptst_Affair_Phone);
	
		static uint16 CloseSys1(void);
		static uint16 CloseIP1(uint8 fd);
		static uint16 CloseMessage1(void);
		static uint16 ClosePhone1(void);
	
		static uint16 ReadMessage1(uint8 *Phone,uint8 *Message);
		static uint16 ReadIP1(uint8 fd,uint8 *Data,uint16 *SizeofData);
		static uint16 ReadPhone1(uint8 *Phone);
		static uint16 AgreePhone1(void);
		static uint16 CloseCall1(void);
	
	
		static uint16 SendMessage1(uint8 *Phone,uint8 *Message);
		static uint16 SendIP1(uint8 fd,uint8 *Data,uint16 SizeofData);
		static uint16 SendPhone1(uint8 *Phone,uint8 *PhoneState);
		static uint16 SetVolume1(uint8 Volume);
	
		static uint16 GetSysState1(st_Gsm_Net_Information	*ptst_Gsm_Net_Information);
		static uint16 GetMessageState1(st_Gsm_Net_Message	*ptst_Gsm_Net_Message);
		static uint16 GetPhoneState1(st_Data_Gprs_Call	*ptst_Data_Gprs_Call);
		static uint16 GetIPState1(st_Data_UDPTCP	*ptst_Data_UDPTCP,st_HardWare_SeeTCPData	*ptst_HardWare_SeeTCPData);
		static uint16 DNSRIP1(uint8 *DomainName,uint32 *IP);
		static uint16 GetIpPro1(uint8 fd,st_Data_UDPTCP	*ptst_Data_UDPTCP);
	
		static uint16 InitSys(void);
		static uint16 InitMessage(void);
		static uint16 InitPhone(void);
		static uint16 InitGprs(st_Data_IPNet	*ptst_Data_IPNet);	
	
		static uint16 OpenSys(st_Affair_Sys	*ptst_Affair_Sys);
		static uint16 OpenMessage(st_Affair_Message	*ptst_Affair_Message);
		static uint16 OpenIP(st_Data_UDPTCP	*ptst_Data_UDPTCP,st_Affair_UDPTCP	*ptst_Affair_UDPTCP,uint8 *fd);
		static uint16 OpenPhone(st_Affair_Phone	*ptst_Affair_Phone);
	
		static uint16 CloseSys(void);
		static uint16 CloseIP(uint8 fd);
		static uint16 CloseMessage(void);
		static uint16 ClosePhone(void);
	
		static uint16 ReadMessage(uint8 *Phone,uint8 *Message);
		static uint16 ReadIP(uint8 fd,uint8 *Data,uint16 *SizeofData);
		static uint16 ReadPhone(uint8 *Phone);
		static uint16 AgreePhone(void);
		static uint16 CloseCall(void);
	
	
		static uint16 SendMessage(uint8 *Phone,uint8 *Message);
		static uint16 SendIP(uint8 fd,uint8 *Data,uint16 SizeofData);
		static uint16 SendPhone(uint8 *Phone,uint8 *PhoneState);
		static uint16 SetVolume(uint8 Volume);
	
		static uint16 GetSysState(st_Gsm_Net_Information	*ptst_Gsm_Net_Information);
		static uint16 GetMessageState(st_Gsm_Net_Message	*ptst_Gsm_Net_Message);
		static uint16 GetPhoneState(st_Data_Gprs_Call	*ptst_Data_Gprs_Call);
		static uint16 GetIPState(st_Data_UDPTCP	*ptst_Data_UDPTCP,st_HardWare_SeeTCPData	*ptst_HardWare_SeeTCPData);
		static uint16 DNSRIP(uint8 *DomainName,uint32 *IP);		
		static uint16 GetIpPro(uint8 fd,st_Data_UDPTCP	*ptst_Data_UDPTCP);
		static uint16 OperIPData(void); 					//运行GPRS
		static uint16 OperMessage(void);
		static uint16 OperPhone(void);
		static uint16 JugeSys(void);
		static uint16 JugeMessage(void);
		static uint16 JugeIPData(void);
		static uint16 BackUpSys(void);
		static uint16 BackUpIP(void);
		static uint32 GetTimeAdd(uint8 *Small,uint8 *Big);
		static void Task(void *pData);	
	#endif	


/*========================================全局变量定义=========================================================*/
	#ifdef De_GPRS_Compiler	
		OS_EVENT	*GprsUseSem=NULL;
		OS_STK		*GprsTaskStk=(OS_STK *)(De_Gprs_STK_Ram);//[De_Gprs_Stk];
		uint8 DateTimer[7];	 
		uint8 SMS_State[De_Moderm_Message_Max1];  																		//心跳维持包时间
		st_Affair_Gprs	CN_st_Affair_Gprs;															//事件表
		st_Gsm_Net_Information	CN_st_Gsm_Net_Information;
		st_Gsm_Net_Message	CN_st_Gsm_Net_Message;
		st_HardWare_SeeTCPData	CN_st_HardWare_SeeTCPData;
		const uint8 CN_LinkNumber[]={De_GprsHard_Link0,De_GprsHard_Link1,De_GprsHard_Link2};		//链路编号
		st_Data_Gprs_Message	 *ptst_Data_Gprs_Message=(st_Data_Gprs_Message	*)(De_Gprs_Ram);	//使用短信
		st_Data_Gprs_Call		 *ptst_Data_Gprs_Call=(st_Data_Gprs_Call	*)(De_Gprs_Ram+sizeof(st_Data_Gprs_Message));//电话号码
		st_Data_Gprs_TcpUdp 	 *ptst_Data_Gprs_TcpUdp[De_GprsHard_MaxLink]=	 					//UDP与TCP接受数据
		{	(st_Data_Gprs_TcpUdp	*)(De_Gprs_Ram+sizeof(st_Data_Gprs_Message)+sizeof(st_Data_Gprs_Call)),
			(st_Data_Gprs_TcpUdp	*)(De_Gprs_Ram+sizeof(st_Data_Gprs_Message)+sizeof(st_Data_Gprs_Call)+sizeof(st_Data_Gprs_TcpUdp)),
			(st_Data_Gprs_TcpUdp	*)(De_Gprs_Ram+sizeof(st_Data_Gprs_Message)+sizeof(st_Data_Gprs_Call)+sizeof(st_Data_Gprs_TcpUdp)*2)	
		};
		uint8 *CN_IPData =(uint8 *)(De_IPData_Ram);
	   	st_Data_IPNet	CN_st_Data_IPNet;
//		st_HardWare_SeeTCPData	CN_st_HardWare_SeeTCPData;
	 /*------------------------------------------变量初值定义------------------------------------------------------*/
	 	st_Affair_Gprs CN_Ba_st_Affair_Gprs=	   															//事件函数初始化
		{ 	De_Gprs_State_Close,
			De_Gprs_State_Close,
			De_Gprs_State_Close,
			De_Gprs_State_Close,
			{NULL,NULL,NULL,NULL},
			{NULL},
			{NULL,NULL},
			{	{NULL,NULL},
				{NULL,NULL},
				{NULL,NULL}
			}	
		};
		const st_Fun_Gprs	CN_st_Fun_Gprs=
		{Init,InitSys1,InitMessage1,InitPhone1,InitGprs1,OpenSys1,OpenMessage1,OpenIP1,OpenPhone1,CloseSys1,
		CloseMessage1,CloseIP1,ClosePhone1,ReadMessage1,ReadIP1,ReadPhone1,AgreePhone1,CloseCall1,SendMessage1,
		SendIP1,SendPhone1,SetVolume1,GetSysState1,GetMessageState1,GetPhoneState1,GetIPState1,DNSRIP1,GetIpPro1};
	#else
		extern st_Fun_Gprs	CN_st_Fun_Gprs;	
	#endif
#endif

