/*========================================include File===========================================================*/
	#include "..\..\..\APP\config.h"													//LPC2368寄存器引用
	#include "stdlib.h"		 															//引用C语言库函数														//引用GPRS输入接口
#ifdef	De_HuaweiGprs_Compiler
	#include "..\GprsPublicDe.h"
	#include "..\..\..\miscellaneous\CodeTrans\AscNumber.h"	
#endif								//引用码制转换资源
/*========================================Define Data============================================================*/
	/*++++++++++++++++++++++++++++++++++++++++最大等待时间+++++++++++++++++++++++++++++++++++++++++++++++++*/
#ifdef	De_HuaweiGprs_Compiler 
	#define De_MaxDelay_Huawei_CloseShow				200								//关闭回显
	#define De_MaxDelay_Huawei_GetChipID				200								//获取厂家名称
	#define De_MaxDelay_Huawei_GetModermState			200								//获取机器工作状态
	#define De_MaxDelay_Huawei_GetModermCard			200								//卡在位查询
	#define De_MaxDelay_Huawei_GetCenterNumber			200								//短信中心号码
	#define De_MaxDelay_Huawei_GetMessage				400								//读短消息
	#define De_MaxDelay_Huawei_SetTxtOrPdu				200								//设置文本模式
	#define De_MaxDelay_Huawei_SeeTxtOrPdu				200								//查询何种方式
	#define De_MaxDelay_Huawei_MsgSend					200								//发送短消息
	#define De_MaxDelay_Huawei_MsgSendData				12000							//发送短消息数据
	#define De_MaxDelay_Huawei_SeeCarrier				200								//查看运营商
	#define De_MaxDelay_Huawei_SQ 						200								//查看信号强度
	#define De_MaxDelay_Huawei_DelMsg					400								//删除短信息
	#define De_MaxDelay_Huawei_Set_Mem					200								//设置MEM
	#define De_MaxDelay_Huawei_MessSet					200								//设置短消息
	#define De_MaxDelay_Huawei_Upadate					200								//保存设置
	#define De_MaxDelay_Huawei_Reg						200								//查看网络注册情况	
	#define De_MaxDelay_Huawei_IMEI						200								//获取IMEI码
	#define De_MaxDelay_Huawei_Chup						200								//挂机
	#define De_MaxDelay_Huawei_Sync						200								//开启使能灯
	#define De_MaxDelay_Huawei_CGDCONT					600								//网络附着
	#define De_MaxDelay_Huawei_Etcpip					12000							//开启TCP/IP
	#define De_MaxDelay_Huawei_IOMODE					400								//设置TCP/IP模式
	#define De_MaxDelay_Huawei_IPOPENX					8000							//打开链路
	#define De_MaxDelay_Huawei_IPSENDX					1000							//发送TCP/IP数据包
	#define De_MaxDelay_Huawei_SeeDataRead				200								//查询位读数据包
	#define De_MaxDelay_Huawei_LogOnTCPIP				2000								//注销GPRS
	#define De_MaxDelay_Huawei_IPDR						400								//读取TCP/IP缓存
	#define De_MaxDelay_Huawei_IPCLOSE					3000							//关闭TCP/IP链路
	#define De_MaxDelay_Huawei_CLIP						200								//设置来电显示
	#define De_MaxDelay_Huawei_ATD						2000							//打电话
	#define De_MaxDelay_Huawei_ATA						1000							//接电话
	#define De_MaxDelay_Huawei_JugeETCPIP				1000							//查看TCP/IP是否启用
	#define De_MaxDelay_Huawei_DNSR						2000							//域名解析
	#define De_MaxDelay_Huawei_IPR						200								//设置波特率 	
	#define De_MaxDelay_Huawei_CLCC						200								//获取通话状态
	#define De_MaxDelay_Huawei_SEEIPCLOSE				1000							//查看链路是否关闭
	#define De_MaxDelay_Huawei_PowerDown				10								//关机
	#define De_MaxDelay_Huawei_SeeCGDCONT 				1000							//查看网络附着
	#define De_MaxDelay_Huawei_SendExtension			2000							//查看网络附着
	#define De_MaxDelay_Huawei_SetVolume				200								//调节音量
#endif
	/*++++++++++++++++++++++++++++++++++++++++Data Define++++++++++++++++++++++++++++++++++++++++++++++++*/
#ifdef	De_HuaweiGprs_Compiler 	
	typedef struct
	{	uint16 Command;										//命令
		st_GprsHard_Order_Cut	CN_st_GprsHard_Order_Cut; 	//命令解析
		uint16 (*Operation )(void *SendBuf,uint16 SizeofSendBuf,void *AgreeBuf,uint16 *SizeofAgreeBuf,st_GprsHard_Order_Cut	*ptst_GprsHard_Order_Cut);
													//命令解析运行函数	
	}st_GprsHard_Order;	  							//命令函数
	typedef struct
	{	uint8 ResultV;			
		uint8 ContrV;
	}st_GprsHead_Result;
	typedef struct
	{	uint8 *Cut;
		uint8 Value;
	}st_GprsHead_Explain;
	typedef struct
	{ 	uint8 Start;
		uint8 End;
		uint8 ByteV;
	}st_Asc_GetData;
	

#endif
/*==========================================Function Define====================================================*/
#ifdef	De_HuaweiGprs_Compiler  	
	/*---------------------------------------对外输出函数---------------------------------------------------*/
	static uint16 Init(void *pFunc,void *Buf,uint16 SizeofBuf);
	static uint16 Read(uint16 Command,void *SendBuf,uint16 SizeofSendBuf,void *AgreeBuf,uint16 *SizeofAgreeBuf);
	/*---------------------------------------各个命令对应的执行函数-----------------------------------------*/
   	static uint16 Huawei_CloseShow(void *SendBuf,uint16 SizeofSendBuf,void *AgreeBuf,uint16 *SizeofAgreeBuf,st_GprsHard_Order_Cut	*ptst_GprsHard_Order_Cut);//关闭回显
	static uint16 GetChipID(void *SendBuf,uint16 SizeofSendBuf,void *AgreeBuf,uint16 *SizeofAgreeBuf,st_GprsHard_Order_Cut	*ptst_GprsHard_Order_Cut);//获取厂家名称
	static uint16 Huawei_GetModermState(void *SendBuf,uint16 SizeofSendBuf,void *AgreeBuf,uint16 *SizeofAgreeBuf,st_GprsHard_Order_Cut	*ptst_GprsHard_Order_Cut);//获取机器工作状态
	static uint16 Huawei_GetModermCard(void *SendBuf,uint16 SizeofSendBuf,void *AgreeBuf,uint16 *SizeofAgreeBuf,st_GprsHard_Order_Cut	*ptst_GprsHard_Order_Cut);//卡在位查询
	static uint16 Huawei_GetCenterNumber(void *SendBuf,uint16 SizeofSendBuf,void *AgreeBuf,uint16 *SizeofAgreeBuf,st_GprsHard_Order_Cut	*ptst_GprsHard_Order_Cut);//短信中心号码
	static uint16 Huawei_GetMessage(void *SendBuf,uint16 SizeofSendBuf,void *AgreeBuf,uint16 *SizeofAgreeBuf,st_GprsHard_Order_Cut	*ptst_GprsHard_Order_Cut);//读短消息
	static uint16 Huawei_SetTxtOrPdu(void *SendBuf,uint16 SizeofSendBuf,void *AgreeBuf,uint16 *SizeofAgreeBuf,st_GprsHard_Order_Cut	*ptst_GprsHard_Order_Cut);//设置文本模式
	static uint16 Huawei_SeeTxtOrPdu(void *SendBuf,uint16 SizeofSendBuf,void *AgreeBuf,uint16 *SizeofAgreeBuf,st_GprsHard_Order_Cut	*ptst_GprsHard_Order_Cut);//查询何种方式
	static uint16 Huawei_MsgSend(void *SendBuf,uint16 SizeofSendBuf,void *AgreeBuf,uint16 *SizeofAgreeBuf,st_GprsHard_Order_Cut	*ptst_GprsHard_Order_Cut);//发送短消息
	static uint16 Huawei_MsgSendData(void *SendBuf,uint16 SizeofSendBuf,void *AgreeBuf,uint16 *SizeofAgreeBuf,st_GprsHard_Order_Cut	*ptst_GprsHard_Order_Cut);//发送短消息数据
	static uint16 Huawei_SeeCarrier(void *SendBuf,uint16 SizeofSendBuf,void *AgreeBuf,uint16 *SizeofAgreeBuf,st_GprsHard_Order_Cut	*ptst_GprsHard_Order_Cut);//查看运营商
	static uint16 Huawei_SQ(void *SendBuf,uint16 SizeofSendBuf,void *AgreeBuf,uint16 *SizeofAgreeBuf,st_GprsHard_Order_Cut	*ptst_GprsHard_Order_Cut);//查看信号强度
	static uint16 Huawei_DelMsg(void *SendBuf,uint16 SizeofSendBuf,void *AgreeBuf,uint16 *SizeofAgreeBuf,st_GprsHard_Order_Cut	*ptst_GprsHard_Order_Cut);//删除短信息
	static uint16 Huawei_Set_Mem(void *SendBuf,uint16 SizeofSendBuf,void *AgreeBuf,uint16 *SizeofAgreeBuf,st_GprsHard_Order_Cut	*ptst_GprsHard_Order_Cut);//设置MEM
	static uint16 Huawei_MessSet(void *SendBuf,uint16 SizeofSendBuf,void *AgreeBuf,uint16 *SizeofAgreeBuf,st_GprsHard_Order_Cut	*ptst_GprsHard_Order_Cut);//设置短消息
	static uint16 Huawei_Upadate(void *SendBuf,uint16 SizeofSendBuf,void *AgreeBuf,uint16 *SizeofAgreeBuf,st_GprsHard_Order_Cut	*ptst_GprsHard_Order_Cut);//保存设置
	static uint16 Huawei_Reg(void *SendBuf,uint16 SizeofSendBuf,void *AgreeBuf,uint16 *SizeofAgreeBuf,st_GprsHard_Order_Cut	*ptst_GprsHard_Order_Cut);//查看网络注册情况	
	static uint16 Huawei_IMEI(void *SendBuf,uint16 SizeofSendBuf,void *AgreeBuf,uint16 *SizeofAgreeBuf,st_GprsHard_Order_Cut	*ptst_GprsHard_Order_Cut);//获取IMEI码
	static uint16 Huawei_Chup(void *SendBuf,uint16 SizeofSendBuf,void *AgreeBuf,uint16 *SizeofAgreeBuf,st_GprsHard_Order_Cut	*ptst_GprsHard_Order_Cut);//挂机
	static uint16 Huawei_Sync(void *SendBuf,uint16 SizeofSendBuf,void *AgreeBuf,uint16 *SizeofAgreeBuf,st_GprsHard_Order_Cut	*ptst_GprsHard_Order_Cut);//开启使能灯
	static uint16 Huawei_CGDCONT(void *SendBuf,uint16 SizeofSendBuf,void *AgreeBuf,uint16 *SizeofAgreeBuf,st_GprsHard_Order_Cut	*ptst_GprsHard_Order_Cut);//网络附着
	static uint16 Huawei_Etcpip(void *SendBuf,uint16 SizeofSendBuf,void *AgreeBuf,uint16 *SizeofAgreeBuf,st_GprsHard_Order_Cut	*ptst_GprsHard_Order_Cut);//开启TCP/IP
	static uint16 Huawei_IOMODE(void *SendBuf,uint16 SizeofSendBuf,void *AgreeBuf,uint16 *SizeofAgreeBuf,st_GprsHard_Order_Cut	*ptst_GprsHard_Order_Cut);//设置TCP/IP模式
	static uint16 Huawei_IPOPENX(void *SendBuf,uint16 SizeofSendBuf,void *AgreeBuf,uint16 *SizeofAgreeBuf,st_GprsHard_Order_Cut	*ptst_GprsHard_Order_Cut);//打开链路
	static uint16 Huawei_IPSENDX(void *SendBuf,uint16 SizeofSendBuf,void *AgreeBuf,uint16 *SizeofAgreeBuf,st_GprsHard_Order_Cut	*ptst_GprsHard_Order_Cut);//发送TCP/IP数据包
	static uint16 Huawei_SeeDataRead(void *SendBuf,uint16 SizeofSendBuf,void *AgreeBuf,uint16 *SizeofAgreeBuf,st_GprsHard_Order_Cut	*ptst_GprsHard_Order_Cut);//查询位读数据包
	static uint16 Huawei_LogOnTCPIP(void *SendBuf,uint16 SizeofSendBuf,void *AgreeBuf,uint16 *SizeofAgreeBuf,st_GprsHard_Order_Cut	*ptst_GprsHard_Order_Cut);//注销GPRS
	static uint16 Huawei_IPDR(void *SendBuf,uint16 SizeofSendBuf,void *AgreeBuf,uint16 *SizeofAgreeBuf,st_GprsHard_Order_Cut	*ptst_GprsHard_Order_Cut);//读取TCP/IP缓存
	static uint16 Huawei_IPCLOSE(void *SendBuf,uint16 SizeofSendBuf,void *AgreeBuf,uint16 *SizeofAgreeBuf,st_GprsHard_Order_Cut	*ptst_GprsHard_Order_Cut);//关闭TCP/IP链路
	static uint16 Huawei_CLIP(void *SendBuf,uint16 SizeofSendBuf,void *AgreeBuf,uint16 *SizeofAgreeBuf,st_GprsHard_Order_Cut	*ptst_GprsHard_Order_Cut);//设置来电显示
	static uint16 Huawei_ATD(void *SendBuf,uint16 SizeofSendBuf,void *AgreeBuf,uint16 *SizeofAgreeBuf,st_GprsHard_Order_Cut	*ptst_GprsHard_Order_Cut);//打电话
	static uint16 Huawei_ATA(void *SendBuf,uint16 SizeofSendBuf,void *AgreeBuf,uint16 *SizeofAgreeBuf,st_GprsHard_Order_Cut	*ptst_GprsHard_Order_Cut);//接电话
	static uint16 Huawei_JugeETCPIP(void *SendBuf,uint16 SizeofSendBuf,void *AgreeBuf,uint16 *SizeofAgreeBuf,st_GprsHard_Order_Cut	*ptst_GprsHard_Order_Cut);//查看TCP/IP是否启用
	static uint16 Huawei_DNSR(void *SendBuf,uint16 SizeofSendBuf,void *AgreeBuf,uint16 *SizeofAgreeBuf,st_GprsHard_Order_Cut	*ptst_GprsHard_Order_Cut);//域名解析
	static uint16 Huawei_IPR(void *SendBuf,uint16 SizeofSendBuf,void *AgreeBuf,uint16 *SizeofAgreeBuf,st_GprsHard_Order_Cut	*ptst_GprsHard_Order_Cut);//设置波特率 	
	static uint16 Huawei_CLCC(void *SendBuf,uint16 SizeofSendBuf,void *AgreeBuf,uint16 *SizeofAgreeBuf,st_GprsHard_Order_Cut	*ptst_GprsHard_Order_Cut);//获取通话状态
	static uint16 Huawei_SEEIPCLOSE(void *SendBuf,uint16 SizeofSendBuf,void *AgreeBuf,uint16 *SizeofAgreeBuf,st_GprsHard_Order_Cut	*ptst_GprsHard_Order_Cut);//查看链路是否关闭
	static uint16 Huawei_PowerDown(void *SendBuf,uint16 SizeofSendBuf,void *AgreeBuf,uint16 *SizeofAgreeBuf,st_GprsHard_Order_Cut	*ptst_GprsHard_Order_Cut);
	static uint16 Huawei_SeeCGDCONT(void *SendBuf,uint16 SizeofSendBuf,void *AgreeBuf,uint16 *SizeofAgreeBuf,st_GprsHard_Order_Cut	*ptst_GprsHard_Order_Cut);
	static uint16 Huawei_SendExtension(void *SendBuf,uint16 SizeofSendBuf,void *AgreeBuf,uint16 *SizeofAgreeBuf,st_GprsHard_Order_Cut	*ptst_GprsHard_Order_Cut);
	static uint16 Huawei_SetVolume(void *SendBuf,uint16 SizeofSendBuf,void *AgreeBuf,uint16 *SizeofAgreeBuf,st_GprsHard_Order_Cut	*ptst_GprsHard_Order_Cut);
	/*-----------------------------------------------------------------------------------------------------*/
	static void ClearNoDisplay(uint8 *Buf);
	static	uint8 *SeekChar(uint8 *Buf,uint8 CharV,uint16 SizeofBuf,uint8 Number);
#endif 
/*============================================Public Ram=======================================================*/
#ifdef	De_HuaweiGprs_Compiler	
	/*===========================================函数输出===================================================*/
	const st_Fun_GprsHard_Fac	CN_Huawei_st_Fun_GprsHard_Fac={Init,Read,"HUAWEI"};
	/*==========================================华为命令结构体==============================================*/
	const st_GprsHard_Order	CN_HuaWei_st_GprsHard_Order[]=					//华为命令的集合
	{	{	De_GprsHard_Com_CloseShow,{De_MaxDelay_Huawei_CloseShow,"ATE0","\r\n","","\r\n","OK",""},Huawei_CloseShow}, //关闭回显
		{	De_GprsHard_Com_GetChipID,{De_MaxDelay_Huawei_GetChipID,"AT+GMI","\r\n","","\r\n","OK",""},GetChipID},		 //获取厂家名称
		{	De_GprsHard_Com_GetModermState,{De_MaxDelay_Huawei_GetModermState,"AT+CPAS","\r\n","+CPAS:","\r\n","OK","ERROR"},Huawei_GetModermState},//获取机器工作状态
		{	De_GprsHard_Com_GetModermCard,{De_MaxDelay_Huawei_GetModermCard,"AT%TSIM","\r\n","%TSIM","\r\n","OK","ERROR"},Huawei_GetModermCard}, //卡在位查询
		{	De_GprsHard_Com_GetCenterNumber,{De_MaxDelay_Huawei_GetCenterNumber,"AT+CSCA?","\r\n","+CSCA:","\r\n","OK","ERROR"},Huawei_GetCenterNumber},	//短信中心号码
		{	De_GprsHard_Com_GetMessage,{De_MaxDelay_Huawei_GetMessage,"AT+CMGR=","\r\n","+CMGR:","\r\n","OK","ERROR"},Huawei_GetMessage},	//读短消息					
	  	{	De_GprsHard_Com_SetTxtOrPdu,{De_MaxDelay_Huawei_SetTxtOrPdu,"AT+CMGF=","\r\n","","\r\n","OK",""},Huawei_SetTxtOrPdu},				//设置文本模式
		{	De_GprsHard_Com_SeeTxtOrPdu,{De_MaxDelay_Huawei_SeeTxtOrPdu,"AT+CMGF?","\r\n","+CMGF:","\r\n","OK",""},Huawei_SeeTxtOrPdu},			//查询何种文本
		{	De_GprsHard_Com_MsgSend,{De_MaxDelay_Huawei_MsgSend,"AT+CMGS=","\r\n","","",">",""},Huawei_MsgSend},							//发送短消息
		{	De_GprsHard_Com_MsgSendData,{De_MaxDelay_Huawei_MsgSendData,"","","+CMGS:","\r\n","OK","ERROR"},Huawei_MsgSendData},				//发送短消息数据	
		{	De_GprsHard_Com_SeeCarrier,{De_MaxDelay_Huawei_SeeCarrier,"AT+CIMI","\r\n","","\r\n","OK","ERROR"},Huawei_SeeCarrier},//查看运营商
		{	De_GprsHard_Com_SQ,{De_MaxDelay_Huawei_SQ,"AT+CSQ","\r\n","+CSQ:","\r\n","OK","ERROR"},Huawei_SQ},		//查看信号强度
		{	De_GprsHard_Com_DelMsg,{De_MaxDelay_Huawei_DelMsg,"AT+CMGD=","\r\n","","\r\n","OK","ERROR"},Huawei_DelMsg},	//删除短信息
		{	De_GprsHard_Com_Set_Mem,{De_MaxDelay_Huawei_Set_Mem,"AT+CPMS=","\r\n","+CPMS:","\r\n","OK","ERROR"},Huawei_Set_Mem},//设置MEM
		{	De_GprsHard_Com_MessSet,{De_MaxDelay_Huawei_MessSet,"at+cnmi=","\r\n","","\r\n","OK","ERROR"},Huawei_MessSet},//设置短消息
		{	De_GprsHard_Com_Upadate,{De_MaxDelay_Huawei_Upadate,"AT&W","\r\n","","\r\n","OK","ERROR"},Huawei_Upadate},//保存设置
		{	De_GprsHard_Com_Reg,{De_MaxDelay_Huawei_Reg,"AT+CREG?","\r\n","+CREG:","\r\n","OK","ERROR"},Huawei_Reg},//查看网络注册情况
		{	De_GprsHard_Com_CLIP,{De_MaxDelay_Huawei_CLIP,"AT+CLIP=1","\r\n","","\r\n","OK",""},Huawei_CLIP},//设置来电显示
		{	De_GprsHard_Com_ATD,{De_MaxDelay_Huawei_ATD,"ATD","\r\n","","\r\n","",""},Huawei_ATD},//ATD拨号
		{	De_GprsHard_Com_Chup,{De_MaxDelay_Huawei_Chup,"ATH0","\r\n","","\r\n","OK","ERROR"},Huawei_Chup},//挂机
		{	De_GprsHard_Com_ATA,{De_MaxDelay_Huawei_ATA,"ATA","\r\n","","\r\n","","ERROR"},Huawei_ATA},	//接电话
		{	De_GprsHard_Com_IMEI,{De_MaxDelay_Huawei_IMEI,"ATD*#06#","\r\n","","\r\n","OK",""},Huawei_IMEI},	//接电话
		{	De_GprsHard_Com_Sync,{De_MaxDelay_Huawei_Sync,"","","","","",""},NULL},//开启使能灯
		{	De_GprsHard_Com_CGDCONT,{De_MaxDelay_Huawei_CGDCONT,"AT+CGDCONT=1,\"IP\",","\r\n","","\r\n","OK","ERROR"},Huawei_CGDCONT},//网络附着		
		{	De_GprsHard_Com_Etcpip,{De_MaxDelay_Huawei_Etcpip,"at%etcpip=","\r\n","","\r\n","OK","ERROR"},Huawei_Etcpip},//开启TCP/IP
	 	{	De_GprsHard_Com_IOMODE,{De_MaxDelay_Huawei_IOMODE,"AT%IOMODE=1,2,0","\r\n","","\r\n","OK","ERROR"},Huawei_IOMODE},//设置TCP/IP模式
	  	{	De_GprsHard_Com_IPOPENX,{De_MaxDelay_Huawei_IPOPENX,"AT%IPOPENX=","\r\n","","\r\n","CONNECT","ERROR"},Huawei_IPOPENX},//打开链路
	 	{	De_GprsHard_Com_IPSENDX,{De_MaxDelay_Huawei_IPSENDX,"AT%IPSENDX=","\r\n","","\r\n","OK","ERROR"},Huawei_IPSENDX},//发送TCP/IP数据包
	   	{	De_GprsHard_Com_SeeDataRead,{De_MaxDelay_Huawei_SeeDataRead,"AT%IPDQ","\r\n","%IPDQ:","\r\n","OK","ERROR"},Huawei_SeeDataRead},//查询数据包
		{	De_GprsHard_Com_IPDR,{De_MaxDelay_Huawei_IPDR,"AT%IPDR","\r\n","%IPDR:","\r\n","OK","ERROR"},Huawei_IPDR},	 //读取TCP/IP缓存
	 	{	De_GprsHard_Com_IPCLOSE,{De_MaxDelay_Huawei_IPCLOSE,"AT%IPCLOSE=","\r\n","%IPCLOSE:","\r\n","OK","ERROR"},Huawei_IPCLOSE},//关闭TCP/IP链路
		{	De_GprsHard_Com_LogOnTCPIP,{De_MaxDelay_Huawei_LogOnTCPIP,"AT%IPCLOSE=5","\r\n","%IPCLOSE:","\r\n","OK","ERROR"},Huawei_LogOnTCPIP},//GPRS网络注销
		{	De_GprsHard_Com_JugeETCPIP,{De_MaxDelay_Huawei_JugeETCPIP,"AT%ETCPIP?","\r\n","%ETCPIP:","\r\n","OK",""},Huawei_JugeETCPIP},//查询TCP/IP
		{	De_GprsHard_Com_DNSR,{De_MaxDelay_Huawei_DNSR,"AT%DNSR=","\r\n","%DNSR:","\r\n","OK","ERROR"},Huawei_DNSR},		//域名解析
		{	De_GprsHard_Com_IPR,{De_MaxDelay_Huawei_IPR,"AT+IPR=","\r\n","","\r\n","OK","ERROR"},Huawei_IPR},			//设置波特率
		{	De_GprsHard_Com_CLCC,{De_MaxDelay_Huawei_CLCC,"AT+CLCC","\r\n","+CLCC:","\r\n","OK","ERROR"},Huawei_CLCC},//获取通话状态
		{	De_GprsHard_Com_SEEIPCLOSE,{De_MaxDelay_Huawei_SEEIPCLOSE,"AT%IPCLOSE?","\r\n","%IPCLOSE:","\r\n","OK","ERROR"},Huawei_SEEIPCLOSE},//查看链路是否关闭	
		{	De_GprsHard_Com_PowerDown,{De_MaxDelay_Huawei_PowerDown,"AT%MSO","\r\n","","","OK","ERROR"},Huawei_PowerDown}, 						//关机
		{	De_GprsHard_Com_SeeCGDCONT,{De_MaxDelay_Huawei_SeeCGDCONT,"AT+CGDCONT?","\r\n","+CGDCONT:","\r\n","OK","ERROR"},Huawei_SeeCGDCONT}, //查看网络是否附着
		{	De_GprsHard_Com_SendExtension,{De_MaxDelay_Huawei_SendExtension,"AT+VTS=","\r\n","","\r\n","",""},Huawei_SendExtension},		//拨打分机
		{	De_GprsHard_Com_SetVolume,{De_MaxDelay_Huawei_SetVolume,"AT%NFV=","\r\n","","\r\n","OK","ERROR"},Huawei_SetVolume}						 //调节音量
	};
	const st_GprsHead_Result	CN_Huawei_st_GprsHead_Result[]=	 	//	
	{	{'0',De_GprsHard_State_0},
		{'1',De_GprsHard_State_1},
		{'2',De_GprsHard_State_2},
		{'3',De_GprsHard_State_3},
		{'4',De_GprsHard_State_4},
		{'5',De_GprsHard_State_5}
	};
	const st_GprsHead_Result	CN_Huawei_ReadMessage[]=				//短消息状态	
	{	{'0',De_GprsHard_New},
		{'1',De_GprsHard_Old},
		{'2',De_GprsHard_Old},
		{'3',De_GprsHard_Ide}
	};
	const st_GprsHead_Result	CN_Huawei_SetMessage[]=				//PDU或者是TXT的情况
	{	{'0',De_GprsHard_Txt_Pdu},
		{'1',De_GprsHard_Txt_Text}
	};
	const st_GprsHead_Explain	CN_Huawei_Carrier[]= 					//运营商
	{ 	{"46002",De_GprsHard_ChinaMobile},
		{"46000",De_GprsHard_ChinaMobile}
	};
	const st_GprsHead_Result	CN_Reg_State[]=	  						//注册状态
	{	{'0',De_GprsHard_Reg_State_NoReg},	   							//没有注册
		{'1',De_GprsHard_Reg_State_Reged},	   							//已经注册
		{'2',De_GprsHard_Reg_State_NoRegIng},							//没有注册，查找新业务
		{'3',De_GprsHard_Reg_State_NoRegJuge},							//注册被拒绝
		{'4',De_GprsHard_Reg_State_Unknown},   							//未知错误
		{'5',De_GprsHard_Reg_State_RegedRove}  							//已经注册，在漫游
	};
	const st_GprsHead_Explain	CN_Ba_CallRes[]=
	{	{"CONNECT",De_GprsHard_Connect_NoSound},						//非语音业务
		{"BUSY",De_GprsHard_Connect_Busy},								//被叫方忙
		{"NO CARRIER",De_GprsHard_Connect_NoCarrier},	    			//无法建立连接
		{"OK",De_GprsHard_Connect_OK}					  				//返回成功
	};
	const st_GprsHead_Explain	CN_Ba_AgreePhone[]=
	{	{"CONNECT",De_GprsHard_AgreePhone_Connect},						//建立数据连接
		{"CONNECT",De_GprsHard_AgreePhone_ConnectTxt},					//建立数据连接并且有文本
		{"NO CARRIER",De_GprsHard_AgreePhone_NoCarrier},				//无法建立连接
		{"OK",De_GprsHard_Connect_OK}									//连接成功
	};
	const st_GprsHead_Explain	CN_Ba_UDPTCP[]=							//链路常数表
	{	{"\"TCP\"",De_GprsHard_UDPTCP_TCP},								//TCP链路
		{"\"UDP\"",De_GprsHard_UDPTCP_UDP}								//UDP链路
	};
	const st_GprsHead_Result	CN_Huawei_Link[]=	 			//链路定义
	{ 	{De_GprsHard_Link0,'1'},							   	//1号链路
		{De_GprsHard_Link1,'2'},								//2号链路
		{De_GprsHard_Link2,'3'}								//3号链路
	};
	const st_GprsHead_Result	CN_Huawei_TCPInitState[]=  		//TCP初始化情况
	{	{De_GprsHard_InitTcp_NoOver,'0'},						//没有初始化
		{De_GprsHard_InitTcp_Over,'1'}							//已经初始化
	};

	const st_GprsHead_Result	CN_Huawei_CallTyte[]=  			//电话呼入情况		
	{	{De_GprsHard_CallType_Initiative,'0'},					//主动模式呼叫
		{De_GprsHard_CallType_Passive,'1'}						//被动模式呼叫
	};
	const st_GprsHead_Result	CN_Huawei_CallState[]= 			//电话连接状态
	{ 	{De_GprsHard_Phone_State_Active,'0'},
		{De_GprsHard_Phone_State_Held,'1'},
		{De_GprsHard_Phone_State_MeDialing,'2'},
		{De_GprsHard_Phone_State_MeAlerting,'3'},
		{De_GprsHard_Phone_State_Incoming,'4'},
		{De_GprsHard_Phone_State_Suc,'5'}
	};



	const st_GprsHead_Result	CN_Huawei_Mod[]=				//通话方式
	{	{De_GprsHard_Mod_Sound,'0'},						   	//语音
		{De_GprsHard_Mod_Data,'1'},								//数据
		{De_GprsHard_Mod_Faxes,'2'},							//传真
		{De_GprsHard_Mod_DataAndSound,'3'},						//数据跟随语音，语音模式
		{De_GprsHard_Mod_SoundAndData,'4'},						//语音数据交替，语音模式
		{De_GprsHard_Mod_SoundFaxes,'5'},						//语音伴随传真，语音模式
		{De_GprsHard_Mod_DataBySound,'6'},						//数据跟随语音，数据模式
		{De_GprsHard_Mod_SoundByData,'7'},						//语音数据交替，数据模式
		{De_GprsHard_Mod_SoundByFaxes,'8'},						//语音伴随传真，传真模式
		{De_GprsHard_Mod_Unkown,'9'}							//未知
	};						//语音呼叫模式//通话人数

	const st_GprsHead_Result	CN_Huawei_PeperNumber[]=
	{	{De_GprsHard_Call_Peper,'0'},  							//单人通话
		{De_GprsHard_Call_SumPeper,'1'}						   	//多人通话
	};

	const st_Asc_GetData	CN_Ba_st_Asc_GetData[]=		  		//信号强度解析
	{ 	{0,0,De_GpsHard_Sem_Size_0},   							//
		{1,6,De_GpsHard_Sem_Size_1},
		{7,20,De_GpsHard_Sem_Size_2},
		{21,25,De_GpsHard_Sem_Size_3},
		{26,30,De_GpsHard_Sem_Size_4},
		{31,31,De_GpsHard_Sem_Size_5}
	};
	const uint8 CN_LinkNum[]= 									//所连接的链路号
	{	'1','2','3'
	};
	const st_GprsHead_Result	CN_Huawei_LinkOper[]=
	{	{De_GprsHard_Link_Open,'1'},				//链路开启
		{De_GprsHard_Link_Close,'0'}				//链路关闭
	};
	/*------------------------------------------动态RAM定义----------------------------------------------------*/
	uint8 *X_BUF;
//	uint8 X_BUF[1536];
	uint16 SizeofX_BUF;
	uint16 (*ModermCom)(uint8 *SendBuf,uint8 *AgreeBuf,uint16 SizeofAgreeBuf,st_GprsHard_Order_Cut	*ptst_GprsHard_Order_Cut);		
#else
	extern const st_Fun_GprsHard_Fac	CN_Huawei_st_Fun_GprsHard_Fac;
#endif





