/*=======================================include File==========================================================*/
	#include "stdlib.h"																	//采用C编译器
/*=======================================Define Data===========================================================*/
	/*++++++++++++++++++++++++++++++++++++错误代码一览表++++++++++++++++++++++++++++++++++++++++++++++*/
	#define De_Suc_GprsHard								0 								//成功
	#define De_Erro_GprsHard_Start						1								//本页错误开始
	#define De_Erro_GprsHead_NoDriver					De_Erro_GprsHard_Start			//无此驱动		
	#define De_Erro_GprsHard_NoOrder					De_Erro_GprsHead_NoDriver+1		//不支持此命令
	#define De_Erro_GprsHead_ReLen						De_Erro_GprsHard_NoOrder+1		//长度返回错误
	#define De_Erro_GprsHead_NoReVa						De_Erro_GprsHead_ReLen+1		//返回值错误
	#define De_Erro_GprsHead_FlagHead					De_Erro_GprsHead_NoReVa+1		//包头信息错误
	#define De_Erro_GprsHead_Explain					De_Erro_GprsHead_FlagHead+1		//命令解析错误
	#define De_Erro_GprsHead_ReErro						De_Erro_GprsHead_Explain+1		//返回错误	
	#define De_Erro_GprsHead_NoLink						De_Erro_GprsHead_ReErro+1		//无此链路
	#define De_Erro_GprsHead_SoftLinkNo					De_Erro_GprsHead_NoLink+1		//此链路应用层未定义
	#define De_Erro_GprsHead_OpenPower					De_Erro_GprsHead_SoftLinkNo+1	//开机失败
	#define De_Erro_GprsHead_NoInit						De_Erro_GprsHead_OpenPower+1	//本驱动没有初始化
	#define De_Erro_GprsHead_NoCom						De_Erro_GprsHead_NoInit+1		//无此协议，只支持UDP/TCP
	#define De_Erro_GprsHead_OverTimer				   	De_Erro_GprsHead_NoCom+1		//通讯超时
	#define De_Erro_GprsHard_NoInitCONT					De_Erro_GprsHead_OverTimer+1	//没有初始化网络
	#define De_Erro_GprsHard_NoIpData					De_Erro_GprsHard_NoInitCONT+1	//没有IP数据包
	/*+++++++++++++++++++++++++++++++++++++命令接口++++++++++++++++++++++++++++++++++++++++++++++++++++*/
	#define De_GprsHard_Com_CloseShow					1									//关闭回显
	#define De_GprsHard_Com_GetChipID					De_GprsHard_Com_CloseShow+1			//获取厂家名称
	#define De_GprsHard_Com_GetModermState				De_GprsHard_Com_GetChipID+1			//获取机器工作状态
	#define De_GprsHard_Com_GetModermCard				De_GprsHard_Com_GetModermState+1	//卡在位查询
	#define De_GprsHard_Com_GetCenterNumber				De_GprsHard_Com_GetModermCard+1		//短信中心号码
	#define De_GprsHard_Com_GetMessage					De_GprsHard_Com_GetCenterNumber+1	//读短消息
	#define De_GprsHard_Com_SetTxtOrPdu					De_GprsHard_Com_GetMessage+1		//设置文本模式
	#define De_GprsHard_Com_SeeTxtOrPdu					De_GprsHard_Com_SetTxtOrPdu+1		//查询何种方式
	#define De_GprsHard_Com_MsgSend						De_GprsHard_Com_SeeTxtOrPdu+1		//发送短消息				 				//发送短消息
	#define De_GprsHard_Com_MsgSendData					De_GprsHard_Com_MsgSend+1			//发送短消息数据
	#define De_GprsHard_Com_SeeCarrier					De_GprsHard_Com_MsgSendData+1		//查看运营商
	#define	De_GprsHard_Com_SQ 							De_GprsHard_Com_SeeCarrier+1		//查看信号强度
	#define	De_GprsHard_Com_DelMsg						De_GprsHard_Com_SQ+1				//删除短信息
	#define De_GprsHard_Com_Set_Mem						De_GprsHard_Com_DelMsg+1			//设置MEM
	#define De_GprsHard_Com_MessSet						De_GprsHard_Com_Set_Mem+1			//设置短消息
	#define De_GprsHard_Com_Upadate						De_GprsHard_Com_MessSet+1			//保存设置
	#define De_GprsHard_Com_Reg							De_GprsHard_Com_Upadate+1			//查看网络注册情况	
	#define De_GprsHard_Com_IMEI						De_GprsHard_Com_Reg+1				//获取IMEI码
	#define De_GprsHard_Com_Chup						De_GprsHard_Com_IMEI+1				//挂机
	#define De_GprsHard_Com_Sync						De_GprsHard_Com_Chup+1				//开启使能灯
	#define De_GprsHard_Com_CGDCONT						De_GprsHard_Com_Sync+1				//网络附着
	#define De_GprsHard_Com_Etcpip						De_GprsHard_Com_CGDCONT+1			//开启TCP/IP
	#define De_GprsHard_Com_IOMODE						De_GprsHard_Com_Etcpip+1			//设置TCP/IP模式
	#define De_GprsHard_Com_IPOPENX						De_GprsHard_Com_IOMODE+1			//打开链路
	#define De_GprsHard_Com_IPSENDX						De_GprsHard_Com_IPOPENX+1			//发送TCP/IP数据包
	#define De_GprsHard_Com_SeeDataRead					De_GprsHard_Com_IPSENDX+1			//查询未读数据包
	#define De_GprsHard_Com_IPDR						De_GprsHard_Com_SeeDataRead+1		//读取TCP/IP缓存
	#define De_GprsHard_Com_IPCLOSE						De_GprsHard_Com_IPDR+1				//关闭TCP/IP链路
	#define De_GprsHard_Com_LogOnTCPIP					De_GprsHard_Com_IPCLOSE+1			//关闭GPRS功能
	#define De_GprsHard_Com_CLIP						De_GprsHard_Com_LogOnTCPIP+1		//设置来电显示
	#define De_GprsHard_Com_ATD							De_GprsHard_Com_CLIP+1				//打电话
	#define De_GprsHard_Com_ATA							De_GprsHard_Com_ATD+1				//接电话
	#define De_GprsHard_Com_JugeETCPIP					De_GprsHard_Com_ATA+1				//查看TCP/IP是否启用
	#define	De_GprsHard_Com_DNSR						De_GprsHard_Com_JugeETCPIP+1		//域名解析
	#define De_GprsHard_Com_IPR							De_GprsHard_Com_DNSR+1				//设置波特率 	
	#define De_GprsHard_Com_CLCC						De_GprsHard_Com_IPR+1				//获取通话状态
	#define De_GprsHard_Com_SEEIPCLOSE					De_GprsHard_Com_CLCC+1				//查看链路是否关闭
	#define De_GprsHard_Com_ATTestBps					De_GprsHard_Com_SEEIPCLOSE+1		//测试AT命令
	#define De_GprsHard_Com_PowerDown					De_GprsHard_Com_ATTestBps+1			//关机命令
	#define De_GprsHard_Com_SeeCGDCONT					De_GprsHard_Com_PowerDown+1			//查看附着	
	#define De_GprsHard_Com_SendExtension				De_GprsHard_Com_SeeCGDCONT+1		//拨打分机
	#define De_GprsHard_Com_SetVolume					De_GprsHard_Com_SendExtension+1
	/*+++++++++++++++++++++++++++++++++++++系统状态++++++++++++++++++++++++++++++++++++++++++++++++++++*/
		/*--------------------------------SIM卡状态------------------------------------*/
		#define	De_GprsHard_SimState_Yes			1					//卡在
		#define	De_GprsHard_SimState_No				0					//无卡
		/*------------------------------最大支持的链路号-------------------------------*/
		#define De_GprsHard_MaxLink					3					//本硬件最大支持的链路号
		/*---------------------------------通话人数------------------------------------*/
		#define De_GprsHard_Call_Peper				0  					//单人通话
		#define De_GprsHard_Call_SumPeper			1					//多人通话
		/*-------------------------------语音通话方式----------------------------------*/
		#define De_GprsHard_CallType_Initiative	 	0					//主动模式呼叫
		#define De_GprsHard_CallType_Passive		1					//被动模式呼叫
		#define De_GprsHard_CallType_NoCall			2					//正常模式	
		/*---------------------------------通话模式------------------------------------*/
		#define De_GprsHard_Mod_Sound				0 					//语音
		#define De_GprsHard_Mod_Data				1					//数据
		#define De_GprsHard_Mod_Faxes				2					//传真
		#define De_GprsHard_Mod_DataAndSound		3					//数据跟随语音，语音模式
		#define De_GprsHard_Mod_SoundAndData		4					//语音数据交替，语音模式
		#define De_GprsHard_Mod_SoundFaxes			5					//语音伴随传真，语音模式
		#define De_GprsHard_Mod_DataBySound			6					//数据跟随语音，数据模式
		#define De_GprsHard_Mod_SoundByData			7					//语音数据交替，数据模式
		#define De_GprsHard_Mod_SoundByFaxes		8					//语音伴随传真，传真模式
		#define De_GprsHard_Mod_Unkown				9					//未知
		/*-------------------------------TCP初始化状态---------------------------------*/
		#define De_GprsHard_InitTcp_Over			1					//完成
		#define De_GprsHard_InitTcp_NoOver			2					//未完成
		/*---------------------------------链路号--------------------------------------*/
		#define De_GprsHard_Link0					0					//1号链路
		#define De_GprsHard_Link1					1					//2号链路
		#define De_GprsHard_Link2					2					//3号链路
		#define De_GprsHard_Link3					3					//4号链路
		#define De_GprsHard_NoLink					0xff				//此链路关闭
		/*----------------------------------接受数据-----------------------------------*/
		#define De_GprsHard_AgreePhone_Connect		1					//建立数据连接		
		#define De_GprsHard_AgreePhone_ConnectTxt	2					//建立数据连接并且有文本
		#define De_GprsHard_AgreePhone_NoCarrier	3					//无法建立连接
		#define De_GprsHard_AgreePhone_OK			4					//连接成功
		/*-------------------------------链路定义--------------------------------------*/
		#define De_GprsHard_UDPTCP_UDP				1					//协议为UDP协议
		#define De_GprsHard_UDPTCP_TCP				2					//协议为TCP协议
		#define De_GprsHard_UDPTCP_NO				0xff				//无协议连接
		/*-------------------------------运营商名称------------------------------------*/
		#define De_GprsHard_ChinaMobile				0					//中国移动
		#define De_GprsHard_Unicom					1  					//中国联通
		#define De_GprsHard_Telecom					2					//中国电信
   		/*--------------------------------目前注册状态---------------------------------*/
		#define De_GprsHard_Reg_State_NoReg			'0'					//没有注册
		#define De_GprsHard_Reg_State_Reged			'1'					//已经注册
		#define De_GprsHard_Reg_State_NoRegIng		'2'					//没有注册，查找新业务
		#define De_GprsHard_Reg_State_NoRegJuge		'3'					//注册被拒绝
		#define De_GprsHard_Reg_State_Unknown		'4'					//未知错误
		#define De_GprsHard_Reg_State_RegedRove		'5'	   				//已经注册，在漫游
		/*-----------------------------呼叫电话返回状态--------------------------------*/
		#define De_GprsHard_Connect_NoSound			1					//非语音业务
		#define De_GprsHard_Connect_Busy			2					//被叫方忙
		#define De_GprsHard_Connect_NoCarrier		3					//无法建立连接
		#define De_GprsHard_Connect_OK				4					//返回成功
		/*------------------------------手机状态表-------------------------------------*/
		#define De_GprsHard_State_0					'0'					//ME准备就绪
		#define De_GprsHard_State_1					'1'					//ME不可用
		#define De_GprsHard_State_2					'2'					//未知ME没准备好
		#define De_GprsHard_State_3					'3'					//振铃
		#define De_GprsHard_State_4					'4'					//呼叫进行中
		#define De_GprsHard_State_5					'5'					//睡眠
		/*------------------------------短消息状态------------------------------------*/
		#define De_GprsHard_New						1					//新来短信息，未读
		#define De_GprsHard_Old 					2					//已读短信息
		#define De_GprsHard_Ide						3					//闲置短信息
		/*------------------------------短消息读取模式--------------------------------*/
		#define De_GprsHard_Txt_Pdu					1					//短消息为PDU方式进行读取
		#define De_GprsHard_Txt_Text				2					//短消息以TXT方式进行读取
		/*------------------------------手机信号强度---------------------------------*/
		#define De_GpsHard_Sem_Size_0				0 					//手机没有信号
		#define De_GpsHard_Sem_Size_1				1
		#define De_GpsHard_Sem_Size_2				2
		#define De_GpsHard_Sem_Size_3				3
		#define De_GpsHard_Sem_Size_4				4
		#define De_GpsHard_Sem_Size_5				5					//手机信号最强
		/*------------------------------手机音量强度---------------------------------*/
		#define De_GpsHard_Volume_Size_0			0					//静音
		#define De_GpsHard_Volume_Size_1			1
		#define De_GpsHard_Volume_Size_2			2
		#define De_GpsHard_Volume_Size_3			3
		#define De_GpsHard_Volume_Size_4			4
		#define De_GpsHard_Volume_Size_5			5
		/*------------------------------------链路情况-------------------------------------*/
		#define De_GprsHard_Link_Open				0					//链路开启
		#define De_GprsHard_Link_Close				1					//链路关闭
		/*---------------------------------电话状态----------------------------------------*/
		#define De_GprsHard_Phone_State_Active			0					//目前在用
		#define De_GprsHard_Phone_State_Held			1					//保持
		#define De_GprsHard_Phone_State_MeDialing		2					//拨号中
		#define De_GprsHard_Phone_State_MeAlerting		3					//拨号提示入局
		#define De_GprsHard_Phone_State_Incoming		4					//被呼叫
		#define De_GprsHard_Phone_State_Suc				5					//等待被呼叫	
		
		
			


/*==========================================Data Define==========================================================*/
	/*++++++++++++++++++++++++++++++++++++++各个厂家模块对外输出+++++++++++++++++++++++++++++++++++++++++++++*/
	typedef struct
	{	uint16 (*Init)(void *pFunc,void *Buf,uint16 SizeofBuf);									//初始化函数 
		uint16 (*Read)(uint16 Command,void *SendBuf,uint16 SizeofSendBuf,void *AgreeBuf,uint16 *SizeofAgreeBuf);
		uint8 *FacID;													//厂家标识代码
	}st_Fun_GprsHard_Fac;					
	/*++++++++++++++++++++++++++++++++++++++返回结果类型定义+++++++++++++++++++++++++++++++++++++++++++++++++*/
	typedef struct
	{	uint8 CallType;							//呼叫类型,主动或者被动
		uint8 State;							//目前状态
		uint8 Mod;								//模式
		uint8 VoiceType;						//语音类型
		uint8 *Phone;							//电话号码
	}st_GprsHard_CallState;
	typedef struct
	{	uint8 APN[32];				//ASC,以‘/0'作为结束
		uint8 Use[16];				//ASC,以‘/0'作为结束
		uint8 PassWord[8];			//ASC,以‘/0'作为结束	
	}st_Data_IPNet;					//TCP/IP参数
	typedef struct
	{	uint32 IP;					//Ip地址
		uint16 Com;					//端口号
	}st_Data_IPPar;					//UDP与TCP的参数

	typedef struct
	{	uint8 OpenType;				//打开类型,见<链路定义>
		uint8 fd;					//所打开的链路号,见<链路号>
		st_Data_IPPar	*ptst_Data_IPPar;	//UDP与TCP的参数 
	}st_Data_OpenUDPTCP;		 		//链路打开的输入
										
	typedef struct
	{	uint8 fd;														//GPRS链路号，见<链路号>
		uint16 DataLen;	  												//发送长度
		uint8 *Data;													//发送数据
	}st_GprsHard_NetData;
	//查询TCP/IP
	typedef struct
	{	uint8 State;													//状态							
		uint32 IP;														//本机IP地址
		uint32 GateWay;													//网关
		uint32 FristDNS;												//首选DSN
		uint32 BackDNS;													//备份DSN
	}st_HardWare_SeeTCPData; 											//数据
	typedef struct
	{	uint8 State;
		uint8 *Buf;
	}st_GprsHard_GetMessage;											//获取短信息
	//查看有无可读数据包
	typedef struct
	{	uint32 NewDataNumber;
		uint32 SumDataNumber;
	}st_GprsHard_UDPDataFlag;

	typedef struct
	{	uint8 fd[De_GprsHard_MaxLink];								//链路ID号
		uint16 DataLen[De_GprsHard_MaxLink];						//各个接受数据的长度
		uint8 *Data[De_GprsHard_MaxLink];							//链路
		uint8 NewLink;
	}st_GprsHard_ReadData;
	/*+++++++++++++++++++++++++++++++++++++++命令解析结果体++++++++++++++++++++++++++++++++++++++++++++++++++*/
	typedef struct
	{	uint32 MaxDelay;							//最大等待时间
		uint8 *OrderHead;							//头部发送
		uint8 *OrderTail;							//尾部发送
		uint8 *AgreeHead;							//头部接受
		uint8 *AgreeTail;							//尾部接受
		uint8 *AgreeTrueTail;						//尾部接受正确
		uint8 *AgreeErroTail;						//尾部接受错误
	}st_GprsHard_Order_Cut;							//命令解析

/*=============================================各个任务输入输出================================================
De_GprsHard_Com_CloseShow		关闭回显			
	SendBuf:NO	AgreeBuf:NO	
	SizeofSendBuf:0
	*SizeofAgreeBuf:0

De_GprsHard_GetChipID			获取厂家名称		
	SendBuf:NO	AgreeBuf:类型 uint8 内容:厂家代码 长度：以'/0'结束
	SizeofSendBuf:0
	*SizeofAgreeBuf:为AgreeBuf内容的长度

De_GprsHard_Com_GetModermState 获取机器工作状态	
	SendBuf:NO	AgreeBuf:类型 uint8 内容:手机状态，详见:<手机状态表> 长度:1个字节
	SizeofSendBuf:0
	*SizeofAgreeBuf:1

De_GprsHard_Com_GetModermCard	 卡在位查询	
	SendBuf:NO	AgreeBuf:NO	
	SizeofSendBuf:0 
	*SizeofAgreeBuf:0

De_GprsHard_Com_GetCenterNumber	查询短信中心号码
	SendBuf:NO	AgreeBuf:类型 uint8 内容:短信中心号码，应去除"+86" 长度：以'/0'结束
	SizeofSendBuf:0
	*SizeofAgreeBuf:AgreeBuf内容的长度

De_GprsHard_Com_GetGetMessage	   读短消息
	SendBuf:类型 uint8 内容:短消息记录号,以1开始  
	SizeofSendBuf:1	
	AgreeBuf:st_GprsHard_GetMessage 
	内容:st_GprsHard_GetMessage.State	<短消息状态>
		 st_GprsHard_GetMessage.Buf		短信息内容，编码规则为unicoder
	*SizeofAgreeBuf:Buf内容+1


De_GprsHard_Com_SetTxtOrPdu	   设置文本方式
	SendBuf:类型 uint8 内容:<短消息读取模式>,长度：1字节   
	AgreeBuf:NO
	SizeofSendBuf:1
	*SizeofAgreeBuf:0

De_GprsHard_Com_SeeTxtOrPdu	查看TEXT或者PDU的文本设置内容
	SendBuf:NO  AgreeBuf:类型 uint8 内容:短信息目前读的方式,表<短消息读取模式>.长度:1字节
	SizeofSendBuf:0
	*SizeofAgreeBuf:1 


De_GprsHard_Com_MsgSend		发送短消息
	SendBuf:类型 uint8 内容:本次所发短消息的长度,长度：1字节  HEX
	AgreeBuf:NO
	SizeofSendBuf:0

De_GprsHard_Com_MsgSendData	发送短消息数据
	SendBuf:类型 uint8 内容:所发送的短信内容,编码规则为unicoder
	SizeofSendBuf:所发送的大小
	*SizeofAgreeBuf:0

De_GprsHard_Com_SeeCarrier	运营商名称
	SendBuf:NO
    AgreeBuf:类型 uint8 内容:见<运营商名称> 长度:1字节
	SizeofSendBuf:0
	*SizeofAgreeBuf:1 
						
De_GprsHard_Com_SQ			信号强度
	SendBuf:NO
	AgreeBuf:类型 uint8 内容:见<手机信号强度> 长度:1字节
	SizeofSendBuf:0
	*SizeofAgreeBuf:1 

De_GprsHard_Com_DelMsg 		删除短信息
	SendBuf:类型 uint8 内容:短消息记录号，长度：1字节
	AgreeBuf:NO
	SizeofSendBuf:1
	*SizeofAgreeBuf:0

De_GprsHard_Com_Set_Mem		SMS存储器设置
	SendBuf:NO	AgreeBuf:NO	SizeofSendBuf:0 *SizeofAgreeBuf:0
	
De_GprsHard_Com_MessSet		设置短信息
	SendBuf:NO	AgreeBuf:NO	SizeofSendBuf:0 *SizeofAgreeBuf:0

De_GprsHard_Com_Upadate		保存设置
	SendBuf:NO	AgreeBuf:NO	SizeofSendBuf:0 *SizeofAgreeBuf:0

De_GprsHard_Com_Reg 			网络注册情况
	SendBuf:NO
	AgreeBuf:类型 uint8 内容:网络注册情况,参见<目前注册状态>
	SizeofSendBuf:0
	*SizeofAgreeBuf:1

De_GprsHard_Com_CLIP			设置来电显示
	SendBuf:NO	AgreeBuf:NO	SizeofSendBuf:0 *SizeofAgreeBuf:0

De_GprsHard_Com_ATD			拨打电话
	SendBuf:类型:uint8 内容：所要拨打的电话号码,长度：以'/0'结束
	AgreeBuf:NO	
	SizeofSendBuf:SendBuf的长度 
	*SizeofAgreeBuf:0

De_GprsHard_Com_Chup			挂电话
	SendBuf:NO
	AgreeBuf:NO	
	SizeofSendBuf:0
	*SizeofAgreeBuf:0

De_GprsHard_Com_ATA			接电话
	SendBuf:NO	AgreeBuf:类型：uint8 内容:见<接受数据>
	*SizeofAgreeBuf:1
	SizeofSendBuf:0

De_GprsHard_Com_IMEI			获取IMEI码
	SendBuf:NO SizeofSendBuf:0
	AgreeBuf:类型:uint8 内容:15位的Imei码 以'/0'结束
	*SizeofAgreeBuf: AgreeBuf的大小
		 			
De_GprsHard_Com_CGDCONT 		定义PDP上下文
	SendBuf:类型：<st_Data_IPNet>
	SizeofSendBuf:无效
	*SizeofAgreeBuf:0
	AgreeBuf:NO

De_GprsHard_Com_Etcpip		PDP激活和TCP/IP初始化
	SendBuf:类型：<st_Data_IPNet>
	SizeofSendBuf:无效
	*SizeofAgreeBuf:0
	AgreeBuf:NO	

De_GprsHard_Com_IOMODE		设置TCP/IP模式
	SendBuf:NO	AgreeBuf:NO	SizeofSendBuf:0 *SizeofAgreeBuf:0
	
De_GprsHard_Com_IPOPENX		打开TCP或者UDP的链路
	SendBuf:NO
	SizeofSendBuf:0
	*SizeofAgreeBuf:sizeof(st_GprsHard_UDPDataFlag)
	AgreeBuf:类型：st_GprsHard_UDPDataFlag  内容：详见<st_GprsHard_UDPDataFlag>定义

									


			
		












===============================================================================================================*/
















	
	
								


