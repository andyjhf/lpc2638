#define De_GPRS_Compiler				
#include "GPRS.h"
#include "..\..\HardWare\UART\UART.h"
/*===============================================对外输出=====================================================*/
/*---------------------------------------------初始化层----------------------------------------------------*/
static uint16 Init(void)							
{	uint8 i;
	if(GprsUseSem!=NULL)
		return De_Suc_Gprs;
	CN_st_Fun_AscNumber.MoveByte(&CN_st_Affair_Gprs,&CN_Ba_st_Affair_Gprs,sizeof(st_Affair_Gprs));
	ptst_Data_Gprs_Message->State=De_GprsHard_Ide;
	ptst_Data_Gprs_Call->State=De_Gprs_Phone_Agree_Ide;
	ptst_Data_Gprs_Call->Mod=De_GprsHard_CallType_NoCall;
	for(i=0;i<De_GprsHard_MaxLink;i++)
	{	ptst_Data_Gprs_TcpUdp[i]->OpenOrClose=De_GprsHard_Link_Close;
		ptst_Data_Gprs_TcpUdp[i]->State=De_Gprs_UDPTCP_Agree_Ide;
		CN_st_Fun_AscNumber.ClsArray(&ptst_Data_Gprs_TcpUdp[i]->CN_st_Heart_Timer.SelfHeartTimer,4);
		CN_st_Fun_AscNumber.ClsArray(&ptst_Data_Gprs_TcpUdp[i]->CN_st_Heart_Timer.CentrHeartTimer,4);
	}
	for(i=0;i<sizeof(SMS_State);i++)
		SMS_State[i]=De_GprsHard_Ide;
	CN_st_Fun_AscNumber.ClsArray(DateTimer,sizeof(DateTimer));
	GprsUseSem=OSSemCreate(1);
	if(GprsUseSem==NULL)
		return De_Erro_Gprs_Init;
	CN_st_Fun_GprsHard.Init();
	OSTaskCreate (Task,(void *)0, &GprsTaskStk[De_Gprs_Stk - 1],De_Gprs_Task);
	return De_Suc_Gprs;
}
/*===========================================各个功能初始化对外=================================================*/
static uint16 InitSys1(void)
{	uint16 Result;	
	uint8 err;
	OSSemPend(GprsUseSem, 0, &err);
	Result=InitSys();
 	OSSemPost(GprsUseSem);
	return Result;
}
static uint16 InitMessage1(void)
{ 	uint16 Result;	
	uint8 err;
	OSSemPend(GprsUseSem, 0, &err);
	Result=InitMessage();
 	OSSemPost(GprsUseSem);
	return Result;
}
static uint16 InitPhone1(void)
{	uint16 Result;	
	uint8 err;
	OSSemPend(GprsUseSem, 0, &err);
	Result=InitPhone();
 	OSSemPost(GprsUseSem);
	return Result;
}
static uint16 InitGprs1(st_Data_IPNet	*ptst_Data_IPNet)
{ 	uint16 Result;	
	uint8 err;
	OSSemPend(GprsUseSem, 0, &err);
	Result=InitGprs(ptst_Data_IPNet);
 	OSSemPost(GprsUseSem);
	return Result;
}

/*============================================各个事件打开对外================================================*/
static uint16 OpenSys1(st_Affair_Sys	*ptst_Affair_Sys)
{	uint16 Result;	
	uint8 err;
	OSSemPend(GprsUseSem, 0, &err);
	Result=OpenSys(ptst_Affair_Sys);
 	OSSemPost(GprsUseSem);
	return Result;
}
static uint16 OpenMessage1(st_Affair_Message	*ptst_Affair_Message)
{	uint16 Result;	
	uint8 err;
	OSSemPend(GprsUseSem, 0, &err);
	Result=OpenMessage(ptst_Affair_Message);
 	OSSemPost(GprsUseSem);
	return Result;
}
static uint16 OpenIP1(st_Data_UDPTCP	*ptst_Data_UDPTCP,st_Affair_UDPTCP	*ptst_Affair_UDPTCP,uint8 *fd)
{	uint16 Result;	
	uint8 err;
	OSSemPend(GprsUseSem, 0, &err);
	Result=OpenIP(ptst_Data_UDPTCP,ptst_Affair_UDPTCP,fd);
 	OSSemPost(GprsUseSem);
	return Result;
}
static uint16 OpenPhone1(st_Affair_Phone	*ptst_Affair_Phone)
{	uint16 Result;	
	uint8 err;
	OSSemPend(GprsUseSem, 0, &err);
	Result=OpenPhone(ptst_Affair_Phone);
 	OSSemPost(GprsUseSem);
	return Result;
}

/*============================================各个事件关闭对外==================================================*/
static uint16 CloseSys1(void)
{	uint16 Result;	
	uint8 err;
	OSSemPend(GprsUseSem, 0, &err);
	Result=CloseSys();
 	OSSemPost(GprsUseSem);
	return Result;
}
static uint16 CloseIP1(uint8 fd)
{	uint16 Result;	
	uint8 err;
	OSSemPend(GprsUseSem, 0, &err);
	Result=CloseIP(fd);
 	OSSemPost(GprsUseSem);
	return Result;
}
static uint16 CloseMessage1(void)
{ 	uint16 Result;	
	uint8 err;
	OSSemPend(GprsUseSem, 0, &err);
	Result=CloseMessage();
 	OSSemPost(GprsUseSem);
	return Result;
}
static uint16 ClosePhone1(void)
{	uint16 Result;	
	uint8 err;
	OSSemPend(GprsUseSem, 0, &err);
	Result=ClosePhone();
 	OSSemPost(GprsUseSem);
	return Result;
}
/*==============================================获取状态对外====================================================*/
static uint16 GetSysState1(st_Gsm_Net_Information	*ptst_Gsm_Net_Information)
{	uint16 Result;	
	uint8 err;
	OSSemPend(GprsUseSem, 0, &err);
	Result=GetSysState(ptst_Gsm_Net_Information);
 	OSSemPost(GprsUseSem);
	return Result;

}
static uint16 GetMessageState1(st_Gsm_Net_Message	*ptst_Gsm_Net_Message)
{	uint16 Result;	
	uint8 err;
	OSSemPend(GprsUseSem, 0, &err);
	Result=GetMessageState(ptst_Gsm_Net_Message);
 	OSSemPost(GprsUseSem);
	return Result;

}
static uint16 GetPhoneState1(st_Data_Gprs_Call	*ptst_Data_Gprs_Call)
{	uint16 Result;	
	uint8 err;
	OSSemPend(GprsUseSem, 0, &err);
	Result=GetPhoneState(ptst_Data_Gprs_Call);
 	OSSemPost(GprsUseSem);
	return Result;

}
static uint16 GetIPState1(st_Data_UDPTCP	*ptst_Data_UDPTCP,st_HardWare_SeeTCPData	*ptst_HardWare_SeeTCPData)
{	uint16 Result;	
	uint8 err;
	OSSemPend(GprsUseSem, 0, &err);
	Result=GetIPState(ptst_Data_UDPTCP,ptst_HardWare_SeeTCPData);
 	OSSemPost(GprsUseSem);
	return Result;
}
static uint16 DNSRIP1(uint8 *DomainName,uint32 *IP)
{	uint16 Result;	
	uint8 err;
	OSSemPend(GprsUseSem, 0, &err);
	Result=DNSRIP(DomainName,IP);
 	OSSemPost(GprsUseSem);
	return Result;
}
/*===========================================获取数据对外=======================================================*/
static uint16 ReadMessage1(uint8 *Phone,uint8 *Message)
{	uint16 Result;	
	uint8 err;
	OSSemPend(GprsUseSem, 0, &err);
	Result=ReadMessage(Phone,Message);
 	OSSemPost(GprsUseSem);
	return Result;

}
static uint16 ReadIP1(uint8 fd,uint8 *Data,uint16 *SizeofData)
{	uint16 Result;	
	uint8 err;
	OSSemPend(GprsUseSem, 0, &err);
	Result=ReadIP(fd,Data,SizeofData);
 	OSSemPost(GprsUseSem);
	return Result;

}
static uint16 ReadPhone1(uint8 *Phone)
{	uint16 Result;	
	uint8 err;
	OSSemPend(GprsUseSem, 0, &err);
	Result=ReadPhone(Phone);
 	OSSemPost(GprsUseSem);
	return Result;

}
static uint16 AgreePhone1(void)
{	uint16 Result;	
	uint8 err;
	OSSemPend(GprsUseSem, 0, &err);
	Result=AgreePhone();
 	OSSemPost(GprsUseSem);
	return Result;

}
static uint16 CloseCall1(void)
{	uint16 Result;	
	uint8 err;
	OSSemPend(GprsUseSem, 0, &err);
	Result=CloseCall();
 	OSSemPost(GprsUseSem);
	return Result;
}

/*===========================================发送数据对外=======================================================*/
static uint16 SendMessage1(uint8 *Phone,uint8 *Message)
{	uint16 Result;	
	uint8 err;
	OSSemPend(GprsUseSem, 0, &err);
	Result=SendMessage(Phone,Message);
 	OSSemPost(GprsUseSem);
	return Result;
}
static uint16 SendIP1(uint8 fd,uint8 *Data,uint16 SizeofData)
{	uint16 Result;	
	uint8 err;
	OSSemPend(GprsUseSem, 0, &err);
	Result=SendIP(fd,Data,SizeofData);
 	OSSemPost(GprsUseSem);
	return Result;
}
static uint16 SendPhone1(uint8 *Phone,uint8 *PhoneState)
{	uint16 Result;	
	uint8 err;
	OSSemPend(GprsUseSem, 0, &err);
	Result=SendPhone(Phone,PhoneState);
 	OSSemPost(GprsUseSem);
	return Result;
}
static uint16 SetVolume1(uint8 Volume)
{	uint16 Result;	
	uint8 err;
	OSSemPend(GprsUseSem, 0, &err);
	Result=SetVolume(Volume);
 	OSSemPost(GprsUseSem);
	return Result;
}								  		 													//GSM网络信息
/*=============================================各个功能初始化==================================================*/
static uint16 InitSys(void)		  					//系统初始化
{	uint16 Result,ReSize;
	uint8 Imei[20],State;
	if((Result=CN_st_Fun_GprsHard.Open())!=De_Suc_GprsHard)
		return Result;
	CN_st_Fun_AscNumber.ClsArray(Imei,sizeof(Imei));
	if((Result=CN_st_Fun_GprsHard.Read(De_GprsHard_Com_IMEI,NULL,NULL,Imei,&ReSize))!=De_Suc_GprsHard)//机器编号
		return Result;
	CN_st_Fun_AscNumber.Asc2Bcd(Imei,CN_st_Gsm_Net_Information.IMEI,14);
	if((Result=CN_st_Fun_GprsHard.Read(De_GprsHard_Com_SeeCarrier,NULL,NULL,&State,NULL))!=De_Suc_GprsHard)	 //运营商
		return Result;
	CN_st_Gsm_Net_Information.Yys=State;
	CN_st_Affair_Gprs.SysState=De_Gprs_State_Open;
   	return De_Suc_Gprs;
}


static uint16 InitMessage(void)						//初始化短信																//初始化短消息							
{	uint16 Result;
	uint8 PduOrTxt;
//	if((Result=CN_st_Fun_File.Open(De_FileName_GBK2Uni,&CN_st_File_GBK.GBK2Unifd))!=De_Suc_File)
//		return Result;
//	if((Result=CN_st_Fun_File.Open(De_FileName_Uni2GBK,&CN_st_File_GBK.Uni2GBKfd))!=De_Suc_File)
//		return Result;
	if((Result=CN_st_Fun_GprsHard.Read(De_GprsHard_Com_Set_Mem,NULL,NULL,NULL,NULL))!=De_Suc_GprsHard)	//设置MEM
		return Result;
	if((Result=CN_st_Fun_GprsHard.Read(De_GprsHard_Com_MessSet,NULL,NULL,NULL,NULL))!=De_Suc_GprsHard)	//设置短信息
		return Result;
	PduOrTxt=De_GprsHard_Txt_Pdu;
	if((Result=CN_st_Fun_GprsHard.Read(De_GprsHard_Com_SetTxtOrPdu,&PduOrTxt,NULL,NULL,NULL))!=De_Suc_GprsHard)
		return Result;
	if((Result=CN_st_Fun_GprsHard.Read(De_GprsHard_Com_Upadate,NULL,NULL,NULL,NULL))!=De_Suc_GprsHard)	//设置短消息
		return Result;
	CN_st_Affair_Gprs.MessageState=De_Gprs_State_Open;
	return De_Suc_Gprs;
}

static uint16 InitPhone(void)																			//初始化电话																//初始化电话号码
{	uint16 Result;
	if((Result=CN_st_Fun_GprsHard.Read(De_GprsHard_Com_Upadate,NULL,NULL,NULL,NULL))!=De_Suc_GprsHard) 	//保存设置
		return Result;
	CN_st_Affair_Gprs.PhoneState=De_Gprs_State_Open;
	return De_Suc_Gprs;
}

static uint16 InitGprs(st_Data_IPNet	*ptst_Data_IPNet) 				//初始化GPRS
{	uint16 Result;
	Result=CN_st_Fun_GprsHard.Read(De_GprsHard_Com_SeeCGDCONT,NULL,NULL,&CN_st_Data_IPNet,NULL);
	if(!((Result==De_Suc_GprsHard)||(Result==De_Erro_GprsHard_NoInitCONT)))
		return Result;
	if((Result!=De_Suc_GprsHard)||(CN_st_Fun_AscNumber.CompareBuf(ptst_Data_IPNet->APN,CN_st_Data_IPNet.APN,sizeof(CN_st_Data_IPNet.APN))!=0))
	{	if((Result=CN_st_Fun_GprsHard.Read(De_GprsHard_Com_CGDCONT,ptst_Data_IPNet,sizeof(st_Data_IPNet),NULL,NULL))!=De_Suc_GprsHard)
			return Result;	
	}
	if((Result=CN_st_Fun_GprsHard.Read(De_GprsHard_Com_JugeETCPIP,NULL,NULL,&CN_st_HardWare_SeeTCPData,NULL))!=De_Suc_GprsHard)		
		return Result;
	if(CN_st_HardWare_SeeTCPData.State!=De_GprsHard_InitTcp_Over)		//没有初始化
	{	if((Result=CN_st_Fun_GprsHard.Read(De_GprsHard_Com_Etcpip,ptst_Data_IPNet,NULL,NULL,NULL))!=De_Suc_GprsHard)
			return Result;	
	}
	if((Result=CN_st_Fun_GprsHard.Read(De_GprsHard_Com_IOMODE,NULL,NULL,NULL,NULL))!=De_Suc_GprsHard)
		return Result;
	CN_st_Affair_Gprs.IPstate=De_Gprs_State_Open;
	CN_st_Fun_AscNumber.MoveByte(&CN_st_Data_IPNet,ptst_Data_IPNet,sizeof(st_Data_IPNet));
	return De_Suc_Gprs;
}
/*==============================================事件打开========================================================*/
static uint16 OpenSys(st_Affair_Sys	*ptst_Affair_Sys) 							//打开系统事件
{	if(CN_st_Affair_Gprs.SysState!=De_Gprs_State_Open)
		return De_Erro_Gprs_State_NoOpen;
	CN_st_Fun_AscNumber.MoveByte(&CN_st_Affair_Gprs.CN_st_Affair_Sys,ptst_Affair_Sys,sizeof(st_Affair_Sys));
	return De_Suc_Gprs;		
}
static uint16 OpenMessage(st_Affair_Message	*ptst_Affair_Message)	  			//打开信息事件
{	if(CN_st_Affair_Gprs.MessageState!=De_Gprs_State_Open)
		return De_Erro_Gprs_State_NoOpen;
	CN_st_Fun_AscNumber.MoveByte(&CN_st_Affair_Gprs.CN_st_Affair_Message,ptst_Affair_Message,sizeof(st_Affair_Message));	
	return De_Suc_Gprs;
}

static uint16 OpenIP(st_Data_UDPTCP	*ptst_Data_UDPTCP,st_Affair_UDPTCP	*ptst_Affair_UDPTCP,uint8 *fd)	//打开链路事件
{	st_Data_IPPar	CN_st_Data_IPPar;
	st_Data_OpenUDPTCP	CN_st_Data_OpenUDPTCP;
	uint16 Result;
	uint8 LinkNumber;
	uint8 LinekState;
	if(CN_st_Affair_Gprs.IPstate!=De_Gprs_State_Open)
		return De_Erro_Gprs_State_NoOpen;
	for(LinkNumber=0;LinkNumber<De_GprsHard_MaxLink;LinkNumber++)
	{	if(ptst_Data_Gprs_TcpUdp[LinkNumber]->OpenOrClose==De_GprsHard_Link_Close)
			break;
	}
	if(LinkNumber==De_GprsHard_MaxLink)
		return De_Erro_GprsLink_Over;
   	if((Result=CN_st_Fun_GprsHard.Read(De_GprsHard_Com_SEEIPCLOSE,(void *)&CN_LinkNumber[LinkNumber],NULL,&LinekState,NULL))!=De_Suc_GprsHard)
		return Result;
	if(LinekState==De_GprsHard_Link_Open)	 			//如果此链路打开
	{	if((Result=CN_st_Fun_GprsHard.Read(De_GprsHard_Com_IPCLOSE,(void *)&CN_LinkNumber[LinkNumber],NULL,NULL,NULL))!=De_Suc_GprsHard)	
	   		return Result;
	}
	CN_st_Data_OpenUDPTCP.OpenType=ptst_Data_UDPTCP->LinkType;
	CN_st_Data_OpenUDPTCP.fd=CN_LinkNumber[LinkNumber];
	CN_st_Data_OpenUDPTCP.ptst_Data_IPPar=&CN_st_Data_IPPar;
	CN_st_Data_IPPar.IP=ptst_Data_UDPTCP->IP;
	CN_st_Data_IPPar.Com=ptst_Data_UDPTCP->Com;
	if((Result=CN_st_Fun_GprsHard.Read(De_GprsHard_Com_IPOPENX,&CN_st_Data_OpenUDPTCP,NULL,NULL,NULL))!=De_Suc_GprsHard)
		return Result;
	CN_st_Fun_AscNumber.MoveByte(&ptst_Data_Gprs_TcpUdp[LinkNumber]->CN_st_Data_UDPTCP,ptst_Data_UDPTCP,sizeof(st_Data_UDPTCP));								
	ptst_Data_Gprs_TcpUdp[LinkNumber]->OpenOrClose=De_GprsHard_Link_Open;
	ptst_Data_Gprs_TcpUdp[LinkNumber]->DataLen=0;
	ptst_Data_Gprs_TcpUdp[LinkNumber]->State=De_Gprs_UDPTCP_Agree_Ide;
	*fd=LinkNumber;
	ptst_Data_Gprs_TcpUdp[LinkNumber]->CN_st_Heart_Timer.SelfHeartTimer=0;
	ptst_Data_Gprs_TcpUdp[LinkNumber]->CN_st_Heart_Timer.CentrHeartTimer=0;
	CN_st_Fun_AscNumber.MoveByte(&CN_st_Affair_Gprs.CN_st_Affair_UDPTCP[LinkNumber],ptst_Affair_UDPTCP,sizeof(st_Affair_UDPTCP));	
	return De_Suc_Gprs;
}
static uint16 OpenPhone(st_Affair_Phone	*ptst_Affair_Phone)	 //打开电话事件
{	if(CN_st_Affair_Gprs.PhoneState!=De_Gprs_State_Open)
		return De_Erro_Gprs_State_NoOpen;
	CN_st_Fun_AscNumber.MoveByte(&CN_st_Affair_Gprs.CN_st_Affair_Phone,ptst_Affair_Phone,sizeof(st_Affair_Phone));	
  	return De_Suc_Gprs;
}
/*==============================================事件关闭=======================================================*/
static uint16 CloseSys(void)								//关闭系统事件
{	CloseIP(De_Gprs_Fd_All);
	CloseMessage();
	ClosePhone();
	//De_Fun_GprsHard_ModermPowerRst;
	CN_st_Fun_GprsHard.Close();
	CN_st_Affair_Gprs.SysState=De_Gprs_State_Close;
	return De_Suc_Gprs;			
}
static uint16 CloseIP(uint8 fd)							  	//关闭IP电话事件
{	st_Data_IPNet	CN_st_Data_IPNet;
	uint16 Result;
	uint8 i,LinkState;
	CN_st_Fun_Uart.Write(0,"art\r\n",5);
	if(fd==De_Gprs_Fd_All)									//代表关闭整个GPRS
	{	if(CN_st_Affair_Gprs.IPstate==De_Gprs_State_Close)
			return De_Suc_Gprs;
		Result=CN_st_Fun_GprsHard.Read(De_GprsHard_Com_SeeCGDCONT,NULL,NULL,&CN_st_Data_IPNet,NULL);
		if(Result==De_Erro_GprsHard_NoInitCONT)
		{	CN_st_Affair_Gprs.IPstate=De_Gprs_State_Close;
		   	return De_Suc_Gprs;
		}
		if(Result!=De_Suc_Gprs)	
			return Result;
		for(i=0;i<De_GprsHard_MaxLink;ptst_Data_Gprs_TcpUdp[i]->OpenOrClose=De_GprsHard_Link_Close,i++)
		{	if(ptst_Data_Gprs_TcpUdp[i]->OpenOrClose!=De_GprsHard_Link_Open)
				continue;
			if((Result=CN_st_Fun_GprsHard.Read(De_GprsHard_Com_SEEIPCLOSE,(void *)&CN_LinkNumber[i],NULL,&LinkState,NULL))!=De_Suc_GprsHard)
				return Result;
			if(LinkState!=De_GprsHard_Link_Open)
				continue;
			if((Result=CN_st_Fun_GprsHard.Read(De_GprsHard_Com_SeeCGDCONT,NULL,NULL,&CN_st_Data_IPNet,NULL))!=De_Suc_GprsHard)
				return Result;
			if((Result=CN_st_Fun_GprsHard.Read(De_GprsHard_Com_IPCLOSE,(void *)&CN_LinkNumber[i],NULL,NULL,NULL))!=De_Suc_GprsHard)
		   		return Result;
			ptst_Data_Gprs_TcpUdp[i]->OpenOrClose=De_GprsHard_Link_Close;
		}
			
		if((Result=CN_st_Fun_GprsHard.Read(De_GprsHard_Com_LogOnTCPIP,NULL,NULL,NULL,NULL))!=De_Suc_GprsHard)
			return Result;
		CN_st_Affair_Gprs.IPstate=De_Gprs_State_Close;
		return De_Suc_Gprs;	
	}
	if(CN_st_Affair_Gprs.IPstate!=De_Gprs_State_Open)
		return De_Erro_Gprs_State_NoOpen;
	if(ptst_Data_Gprs_TcpUdp[fd]->OpenOrClose==De_GprsHard_Link_Close)
		return De_Suc_Gprs;
	if((Result=CN_st_Fun_GprsHard.Read(De_GprsHard_Com_SEEIPCLOSE,(void *)&CN_LinkNumber[fd],NULL,&LinkState,NULL))!=De_Suc_GprsHard)
		return Result;		
	if(LinkState==De_GprsHard_Link_Close)
	{	ptst_Data_Gprs_TcpUdp[fd]->OpenOrClose=De_GprsHard_Link_Close;
		return De_Suc_Gprs;
	}
	if((Result=CN_st_Fun_GprsHard.Read(De_GprsHard_Com_IPCLOSE,(void *)&CN_LinkNumber[fd],NULL,NULL,NULL))!=De_Suc_GprsHard)
		return Result;
	ptst_Data_Gprs_TcpUdp[fd]->OpenOrClose=De_GprsHard_Link_Close;
	return De_Suc_Gprs;
}
static uint16 CloseMessage(void)						   	//关闭短息事件
{	CN_st_Affair_Gprs.MessageState=De_Gprs_State_Close;
	CN_st_Fun_File.Close(CN_st_File_GBK.GBK2Unifd);
	CN_st_Fun_File.Close(CN_st_File_GBK.Uni2GBKfd);
	return De_Suc_Gprs;		
}
static uint16 ClosePhone(void)						 	//关闭电话事件
{ 	CN_st_Affair_Gprs.PhoneState=De_Gprs_State_Close;
	return De_Suc_Gprs;	
}
/*==========================================获取数据=====================================================*/
static uint16 ReadMessage(uint8 *Phone,uint8 *Message)						//读短信息
{	if(ptst_Data_Gprs_Message->State!=De_GprsHard_New)
		return De_Erro_Gprs_NoMessageData;
	CN_st_Fun_AscNumber.MoveByte(Message,ptst_Data_Gprs_Message->Message,CN_st_Fun_AscNumber.Strsize16(ptst_Data_Gprs_Message->Message));
	CN_st_Fun_AscNumber.MoveByte(Phone,ptst_Data_Gprs_Message->Phone,CN_st_Fun_AscNumber.Strsize16(ptst_Data_Gprs_Message->Phone));					
	ptst_Data_Gprs_Message->State=De_GprsHard_Old;
	return De_Suc_Gprs;
}
static uint16 ReadIP(uint8 fd,uint8 *Data,uint16 *SizeofData)		  		//读IP数据
{	if(ptst_Data_Gprs_TcpUdp[fd]->OpenOrClose!=De_GprsHard_Link_Open)
		return De_Erro_Gprs_NoIPData;
	if(ptst_Data_Gprs_TcpUdp[fd]->State!=De_Gprs_UDPTCP_Agree_New)
		return De_Erro_Gprs_NoIPData;
	*SizeofData=ptst_Data_Gprs_TcpUdp[fd]->DataLen;
	CN_st_Fun_AscNumber.MoveByte(Data,ptst_Data_Gprs_TcpUdp[fd]->Data,*SizeofData);
	ptst_Data_Gprs_TcpUdp[fd]->State=De_Gprs_UDPTCP_Agree_Old;
	return De_Suc_Gprs;			
}

static uint16 ReadPhone(uint8 *Phone)						  				//读电话号码
{	if(ptst_Data_Gprs_Call->State!=De_Gprs_Phone_Agree_New)
		return De_Erro_Gprs_NoPhone;
	CN_st_Fun_AscNumber.MoveByte(Phone,ptst_Data_Gprs_Call->Phone,CN_st_Fun_AscNumber.Strsize16(ptst_Data_Gprs_Call->Phone));																 	
	ptst_Data_Gprs_Call->State=De_Gprs_Phone_Agree_Old;
	return De_Suc_Gprs;
}
static uint16 AgreePhone(void)
{	if(ptst_Data_Gprs_Call->Mod!=De_GprsHard_CallType_Passive)
		return De_Erro_Gprs_NoCall;
	return CN_st_Fun_GprsHard.Read(De_GprsHard_Com_ATA,NULL,NULL,NULL,NULL);
}
static uint16 CloseCall(void)
{	return CN_st_Fun_GprsHard.Read(De_GprsHard_Com_Chup,NULL,NULL,NULL,NULL);
}

/*======================================发送数据==========================================================*/
static uint16 SendMessage(uint8 *Phone,uint8 *Message)				   		//发送短信息
{	uint8 UnMessage[De_Gprs_Message_Size*2+80];
	uint8 CentrPhone[De_Gprs_PhoneNumber_Size+1];
	uint32 SendSize;
	uint16 Result,ReSize;
	CN_st_Fun_AscNumber.ClsArray(CentrPhone,sizeof(CentrPhone));
	if((Result=CN_st_Fun_GprsHard.Read(De_GprsHard_Com_GetCenterNumber,NULL,NULL,CentrPhone,&ReSize))!=De_Suc_GprsHard)
		return Result;
	CN_st_Fun_AscNumber.ClsArray(UnMessage,sizeof(UnMessage));
	if(CN_st_Fun_AscNumber.PhoPdu(UnMessage,Message,Phone,CentrPhone)!=0)
		return De_Erro_Gprs_Explain;
	SendSize=CN_st_Fun_AscNumber.Strsize16(UnMessage);
	SendSize=(SendSize/2)-9;
	if((Result=CN_st_Fun_GprsHard.Read(De_GprsHard_Com_MsgSend,&SendSize,NULL,NULL,NULL))!=De_Suc_GprsHard)
		return Result;
	if((Result=CN_st_Fun_GprsHard.Read(De_GprsHard_Com_MsgSendData,UnMessage,NULL,NULL,NULL))!=De_Suc_GprsHard)
		return Result;
	return De_Suc_Gprs;
}

static uint16 SendIP(uint8 fd,uint8 *Data,uint16 SizeofData)				//发送UDP/TCP数据
{	st_GprsHard_NetData	CN_st_GprsHard_NetData;
	uint16 Result;
	uint8 LinkState;
	if((Result=CN_st_Fun_GprsHard.Read(De_GprsHard_Com_SEEIPCLOSE,(void *)&CN_LinkNumber[fd],NULL,&LinkState,NULL))!=De_Suc_GprsHard)
		return Result;
	if(LinkState!=De_GprsHard_Link_Open)
		return De_Erro_Gprs_LinkClose;
	CN_st_GprsHard_NetData.fd=CN_LinkNumber[fd];
	CN_st_GprsHard_NetData.DataLen=SizeofData;
	CN_st_GprsHard_NetData.Data=Data;
	if((Result=CN_st_Fun_GprsHard.Read(De_GprsHard_Com_IPSENDX,&CN_st_GprsHard_NetData,NULL,NULL,NULL))!=De_Suc_GprsHard)
	 	return Result;
	CN_st_Fun_AscNumber.ClsArray(&ptst_Data_Gprs_TcpUdp[fd]->CN_st_Heart_Timer.SelfHeartTimer,4);
	return De_Suc_Gprs;

}
static uint16 SendPhone(uint8 *Phone,uint8 *PhoneState)										//打电话
{	uint16 SizeofPhone;
	uint16 Result;
	if(ptst_Data_Gprs_Call->Mod==De_GprsHard_CallType_NoCall)
	{	SizeofPhone=CN_st_Fun_AscNumber.Strsize(Phone);
		if((Result=CN_st_Fun_GprsHard.Read(De_GprsHard_Com_ATD,Phone,SizeofPhone,PhoneState,NULL))!=De_Suc_GprsHard)
			return Result;
		return De_Suc_Gprs;
	}
	else if(ptst_Data_Gprs_Call->Mod==De_GprsHard_CallType_Initiative)
	{	SizeofPhone=CN_st_Fun_AscNumber.Strsize(Phone);
		if((Result=CN_st_Fun_GprsHard.Read(De_GprsHard_Com_SendExtension,Phone,SizeofPhone,PhoneState,NULL))!=De_Suc_GprsHard)
			return Result;
		return De_Suc_Gprs;	
	}
	else
		return De_Erro_Gprs_AnswerPhone;	 	
}
static uint16 SetVolume(uint8 Volume)
{	uint16 Result;
	if(Volume>De_GpsHard_Volume_Size_5)
		Volume=De_GpsHard_Volume_Size_5;
	Volume=Volume+0x30;	
	if((Result=CN_st_Fun_GprsHard.Read(De_GprsHard_Com_SetVolume,&Volume,NULL,NULL,NULL))!=De_Suc_GprsHard)
		return Result;
	if((Result=CN_st_Fun_GprsHard.Read(De_GprsHard_Com_Upadate,NULL,NULL,NULL,NULL))!=De_Suc_GprsHard)	//保存设置
		return Result;
	return De_Suc_Gprs;
}

/*==========================================获取状态=====================================================*/
static uint16 GetSysState(st_Gsm_Net_Information	*ptst_Gsm_Net_Information)
{	if(CN_st_Affair_Gprs.SysState!=De_Gprs_State_Open)
		return De_Erro_Gprs_FunctionNo;
	CN_st_Fun_AscNumber.MoveByte(ptst_Gsm_Net_Information,&CN_st_Gsm_Net_Information,sizeof(st_Gsm_Net_Information));
	return De_Suc_Gprs;
}

static uint16 GetMessageState(st_Gsm_Net_Message	*ptst_Gsm_Net_Message)
{	if(CN_st_Affair_Gprs.MessageState!=De_Gprs_State_Open)
		return De_Erro_Gprs_FunctionNo;
   	CN_st_Fun_AscNumber.MoveByte(ptst_Gsm_Net_Message,&CN_st_Gsm_Net_Message,sizeof(st_Gsm_Net_Message));
	return De_Suc_Gprs;
}

static uint16 GetPhoneState(st_Data_Gprs_Call	*ptst_Data_Gprs_Call)
{	if(CN_st_Affair_Gprs.PhoneState!=De_Gprs_State_Open)
		return De_Erro_Gprs_FunctionNo;
	CN_st_Fun_AscNumber.MoveByte(ptst_Data_Gprs_Call,ptst_Data_Gprs_Call,sizeof(st_Data_Gprs_Call));
	return De_Suc_Gprs;
}

static uint16 GetIPState(st_Data_UDPTCP	*ptst_Data_UDPTCP,st_HardWare_SeeTCPData	*ptst_HardWare_SeeTCPData)
{	uint8 i;
	CN_st_Fun_AscNumber.MoveByte(ptst_HardWare_SeeTCPData,&CN_st_HardWare_SeeTCPData,sizeof(st_HardWare_SeeTCPData));
	for(i=0;i<De_GprsHard_MaxLink;i++)
		CN_st_Fun_AscNumber.MoveByte(ptst_Data_UDPTCP,&ptst_Data_Gprs_TcpUdp[i]->CN_st_Data_UDPTCP,sizeof(st_Data_UDPTCP));
	return De_Suc_Gprs;
}
static uint16 DNSRIP(uint8 *DomainName,uint32 *IP)
{	uint16 Result,DataLength;
	DataLength=CN_st_Fun_AscNumber.Strsize(DomainName);
	if((Result=CN_st_Fun_GprsHard.Read(De_GprsHard_Com_DNSR,DomainName,DataLength,IP,NULL))!=De_Suc_GprsHard)
		return Result;
	return De_Suc_Gprs;
}


/*=========================================任务处理======================================================*/
static void Task(void *pData)
{	uint8 err;					
	pData=pData;
	for(;;OSSemPost(GprsUseSem),OSTimeDly(De_Gprs_TaskDly))
	{	OSSemPend(GprsUseSem, 0, &err);
		if(CN_st_Affair_Gprs.SysState!=De_Gprs_State_Open)					//系统电源没有开
			continue;
		CN_st_Fun_Uart.Write(0,"Sys_Start\r\n",11);
		if(JugeSys()!=De_Suc_Gprs)											//系统不正常
		{	if(CN_st_Affair_Gprs.CN_st_Affair_Sys.ptFunNoWork!=NULL)
			{	OSSemPost(GprsUseSem);
				CN_st_Affair_Gprs.CN_st_Affair_Sys.ptFunNoWork();
				OSSemPend(GprsUseSem, 0, &err);
			}
			BackUpSys();
			continue;

		}
		CN_st_Fun_Uart.Write(0,"Sys_End\r\n",9);
		if(CN_st_Gsm_Net_Information.Csq<De_GpsHard_Sem_Size_1)	   			//手机没有信号
		{	if(CN_st_Affair_Gprs.CN_st_Affair_Sys.ptFunNoSem!=NULL)
			{	OSSemPost(GprsUseSem);
				CN_st_Affair_Gprs.CN_st_Affair_Sys.ptFunNoSem();
				OSSemPend(GprsUseSem, 0, &err);
			}
			continue;
		}
		if(CN_st_Affair_Gprs.CN_st_Affair_Sys.ptFunSem!=NULL)
		{	OSSemPost(GprsUseSem);
			CN_st_Affair_Gprs.CN_st_Affair_Sys.ptFunSem();
			OSSemPend(GprsUseSem, 0, &err);
		}
		CN_st_Fun_Uart.Write(0,"OperIPData_Start\r\n",18);
		if(CN_st_Affair_Gprs.IPstate==De_Gprs_State_Open)					//IP通讯方式打开
		{	if(JugeIPData()!=De_Suc_Gprs)									//判断IP是否正常
			{	if(CN_st_Affair_Gprs.CN_st_Affair_Sys.ptGPRS!=NULL)
				{	OSSemPost(GprsUseSem);
					CN_st_Affair_Gprs.CN_st_Affair_Sys.ptGPRS();
					OSSemPend(GprsUseSem, 0, &err);
				}
				BackUpSys();	
				continue;
			}
			
			OperIPData();
					
		}
		CN_st_Fun_Uart.Write(0,"OperIPData_End\r\n",16);
		if(CN_st_Affair_Gprs.MessageState==De_Gprs_State_Open)				//短信方式打开
		{	if(JugeMessage()!=De_Suc_Gprs)
			{	BackUpSys();
		   		continue;
			}
		  	OperMessage();
		}
		if(CN_st_Affair_Gprs.PhoneState==De_Gprs_State_Open)				//电话方式
			OperPhone();			
	}
}


/*============================================运行系统========================================================*/
static uint16 OperIPData(void) 					//运行GPRS
{	st_Data_Timer	CN_st_Data_Timer;	
	st_GprsHard_ReadData	CN_st_GprsHard_ReadData;
	st_GprsHard_UDPDataFlag	CN_st_GprsHard_UDPDataFlag;
	uint32 TimerDly;
	uint32 TimerDly1;
	uint16 Result,i;
	uint8 fd,err,j;
	CN_st_Fun_Timer.Read(&CN_st_Data_Timer);
	TimerDly=GetTimeAdd(DateTimer,CN_st_Data_Timer.DateTime);
	CN_st_Fun_AscNumber.MoveByte(DateTimer,CN_st_Data_Timer.DateTime,7);
	for(i=0;i<De_GprsHard_MaxLink;i++)
	{	if(ptst_Data_Gprs_TcpUdp[i]->OpenOrClose==De_GprsHard_Link_Close)
		{	CN_st_GprsHard_ReadData.fd[i]=De_GprsHard_NoLink;
			continue;
		}
		CN_st_GprsHard_ReadData.fd[i]=CN_LinkNumber[i];
		CN_st_GprsHard_ReadData.DataLen[i]=ptst_Data_Gprs_TcpUdp[i]->DataLen;
		CN_st_GprsHard_ReadData.Data[i]=CN_IPData;
		CN_st_GprsHard_ReadData.NewLink=De_GprsHard_NoLink;
		if(ptst_Data_Gprs_TcpUdp[i]->CN_st_Data_UDPTCP.SelfHeartTimer==0)
			continue;
//		ptst_Data_Gprs_TcpUdp[i]->CN_st_Heart_Timer.SelfHeartTimer+=TimerDly;
//		ptst_Data_Gprs_TcpUdp[i]->CN_st_Heart_Timer.CentrHeartTimer+=TimerDly;
		CN_st_Fun_AscNumber.MoveByte(&TimerDly1,&ptst_Data_Gprs_TcpUdp[i]->CN_st_Heart_Timer.SelfHeartTimer,4);
		TimerDly1+=TimerDly;
		CN_st_Fun_AscNumber.MoveByte(&ptst_Data_Gprs_TcpUdp[i]->CN_st_Heart_Timer.SelfHeartTimer,&TimerDly1,4);
		
		if(ptst_Data_Gprs_TcpUdp[i]->CN_st_Heart_Timer.SelfHeartTimer>=
		ptst_Data_Gprs_TcpUdp[i]->CN_st_Data_UDPTCP.SelfHeartTimer)
		{	if(SendIP(i,ptst_Data_Gprs_TcpUdp[i]->CN_st_Data_UDPTCP.SelfHeartData,
			ptst_Data_Gprs_TcpUdp[i]->CN_st_Data_UDPTCP.HeartDataLength)!=De_Suc_GprsHard)
				continue;
			CN_st_Fun_AscNumber.ClsArray(&ptst_Data_Gprs_TcpUdp[i]->CN_st_Heart_Timer.SelfHeartTimer,4);
		}
	}
	for(j=0;j<De_GprsHard_MaxLink;j++)
	{	if(ptst_Data_Gprs_TcpUdp[i]->OpenOrClose==De_GprsHard_Link_Close)
			continue;
		if(ptst_Data_Gprs_TcpUdp[j]->CN_st_Data_UDPTCP.CentrHeartTimer==0)
			continue;
		CN_st_Fun_AscNumber.MoveByte(&TimerDly1,&ptst_Data_Gprs_TcpUdp[i]->CN_st_Heart_Timer.CentrHeartTimer,4);
		TimerDly1+=TimerDly;
		CN_st_Fun_AscNumber.MoveByte(&ptst_Data_Gprs_TcpUdp[i]->CN_st_Heart_Timer.CentrHeartTimer,&TimerDly1,4);
		if(ptst_Data_Gprs_TcpUdp[j]->CN_st_Heart_Timer.CentrHeartTimer>ptst_Data_Gprs_TcpUdp[j]->CN_st_Data_UDPTCP.CentrHeartTimer)	
	   	{	if(CN_st_Affair_Gprs.CN_st_Affair_UDPTCP[j].ptFunLinkClose!=NULL)
			{	OSSemPost(GprsUseSem);
				CN_st_Affair_Gprs.CN_st_Affair_UDPTCP[j].ptFunLinkClose(&j);			//中心收不到心跳
				OSSemPend(GprsUseSem, 0, &err);
			}
			CN_st_Fun_AscNumber.ClsArray(&ptst_Data_Gprs_TcpUdp[j]->CN_st_Heart_Timer.CentrHeartTimer,4);
		}
	}
	if((Result=CN_st_Fun_GprsHard.Read(De_GprsHard_Com_SeeDataRead,NULL,NULL,&CN_st_GprsHard_UDPDataFlag,NULL))!=De_Suc_GprsHard)
		return Result;
	if(CN_st_GprsHard_UDPDataFlag.NewDataNumber==0)
		return De_Suc_Gprs;
   	for(i=0;i<CN_st_GprsHard_UDPDataFlag.NewDataNumber;i++)
	{	if((Result=CN_st_Fun_GprsHard.Read(De_GprsHard_Com_IPDR,NULL,NULL,&CN_st_GprsHard_ReadData,NULL))!=De_Suc_GprsHard)
			return Result;			
	   	fd=CN_st_GprsHard_ReadData.NewLink;
		CN_st_Fun_AscNumber.ClsArray(&ptst_Data_Gprs_TcpUdp[fd]->CN_st_Heart_Timer.CentrHeartTimer,4);
		if((CN_st_Fun_AscNumber.CompareBuf(ptst_Data_Gprs_TcpUdp[fd]->CN_st_Data_UDPTCP.CentrHeartData,CN_IPData,
			ptst_Data_Gprs_TcpUdp[fd]->CN_st_Data_UDPTCP.CentrHeartLength)==0)&&(ptst_Data_Gprs_TcpUdp[fd]->CN_st_Data_UDPTCP.CentrHeartLength!=0))
			continue;
		ptst_Data_Gprs_TcpUdp[fd]->DataLen=CN_st_GprsHard_ReadData.DataLen[fd];
		ptst_Data_Gprs_TcpUdp[fd]->State=De_Gprs_UDPTCP_Agree_New;
		CN_st_Fun_AscNumber.MoveByte(ptst_Data_Gprs_TcpUdp[fd]->Data,CN_IPData,CN_st_GprsHard_ReadData.DataLen[fd]);
		if(CN_st_Affair_Gprs.CN_st_Affair_UDPTCP[fd].ptFunNewTCPUDP==NULL)
			continue;
		OSSemPost(GprsUseSem);
		CN_st_Affair_Gprs.CN_st_Affair_UDPTCP[fd].ptFunNewTCPUDP(ptst_Data_Gprs_TcpUdp[fd]->Data,fd,
		ptst_Data_Gprs_TcpUdp[fd]->DataLen);
		OSSemPend(GprsUseSem, 0, &err);
	}
	
	return De_Suc_Gprs;
}

static uint16 OperMessage(void)						//短信方式
{	st_GprsHard_GetMessage	CN_st_GprsHard_GetMessage;
	uint8 UnMessage[De_Gprs_Message_Size*2+80];
	uint16 Result,ReSize,MessMaxNumber;
	uint8 PduOrTxt,i,err;
	if((Result=CN_st_Fun_GprsHard.Read(De_GprsHard_Com_SeeTxtOrPdu,NULL,NULL,&PduOrTxt,NULL))!=De_Suc_GprsHard)
		return Result;
	if(PduOrTxt!=De_GprsHard_Txt_Pdu)
	{	PduOrTxt=De_GprsHard_Txt_Pdu;
		if((Result=CN_st_Fun_GprsHard.Read(De_GprsHard_Com_SetTxtOrPdu,&PduOrTxt,NULL,NULL,NULL))!=De_Suc_GprsHard)
			return Result;
		if((Result=CN_st_Fun_GprsHard.Read(De_GprsHard_Com_Upadate,NULL,NULL,NULL,NULL))!=De_Suc_GprsHard)
			return Result;
	}
	CN_st_GprsHard_GetMessage.Buf=UnMessage;
	MessMaxNumber=De_Moderm_Message_Max;
	for(i=1;i<=MessMaxNumber;i++)
	{	CN_st_Fun_AscNumber.ClsArray(UnMessage,sizeof(UnMessage));
		if(SMS_State[i-1]==De_GprsHard_Ide) 					//空闲状态
		{	if((Result=CN_st_Fun_GprsHard.Read(De_GprsHard_Com_GetMessage,&i,NULL,&CN_st_GprsHard_GetMessage,&ReSize))!=De_Suc_GprsHard)				
		   		return Result;
			if(CN_st_GprsHard_GetMessage.State==De_GprsHard_Ide)
				continue;
			SMS_State[i-1]=CN_st_GprsHard_GetMessage.State;
		}
		if(SMS_State[i-1]==De_GprsHard_New)	   				//新短信
		{	CN_st_Fun_AscNumber.ExpPdu(UnMessage,ptst_Data_Gprs_Message->Message,ptst_Data_Gprs_Message->Phone,NULL);
			ptst_Data_Gprs_Message->State=De_GprsHard_New;
			if(CN_st_Affair_Gprs.CN_st_Affair_Message.ptFunNewMessage!=NULL)
			{	OSSemPost(GprsUseSem);
				CN_st_Affair_Gprs.CN_st_Affair_Message.ptFunNewMessage(ptst_Data_Gprs_Message->Phone,
				ptst_Data_Gprs_Message->Message);
				OSSemPend(GprsUseSem, 0, &err);	
			}
			SMS_State[i-1]=De_GprsHard_Old;
			if(i==De_Moderm_Message_Max)
				MessMaxNumber=De_Moderm_Message_Max1;	
		}
		if(SMS_State[i-1]==De_GprsHard_Old)					//已读短信
		{	if((Result=CN_st_Fun_GprsHard.Read(De_GprsHard_Com_DelMsg,&i,NULL,NULL,NULL))!=De_Suc_GprsHard)
				return Result;
		}
	}
	return De_Suc_Gprs;
}

static uint16 OperPhone(void)	
{	st_GprsHard_CallState	CN_st_GprsHard_CallState;
	uint8 Phone[De_Gprs_PhoneNumber_Size],err;
	uint16 Result;
	CN_st_Fun_AscNumber.ClsArray(Phone,sizeof(Phone));
	CN_st_GprsHard_CallState.Phone=Phone;
	if((Result=CN_st_Fun_GprsHard.Read(De_GprsHard_Com_CLCC,NULL,NULL,&CN_st_GprsHard_CallState,NULL))!=De_Suc_GprsHard)
		return Result;
	if(ptst_Data_Gprs_Call->Mod==De_GprsHard_CallType_NoCall) 			//正常
	{	if(CN_st_GprsHard_CallState.CallType==De_GprsHard_CallType_NoCall)
			return De_Suc_Gprs;
		if(CN_st_GprsHard_CallState.CallType==De_GprsHard_CallType_Passive)		//来电
		{	ptst_Data_Gprs_Call->Mod=De_GprsHard_CallType_Passive;
			CN_st_Fun_AscNumber.MoveByte(ptst_Data_Gprs_Call->Phone,Phone,sizeof(Phone));
			ptst_Data_Gprs_Call->State=De_Gprs_Phone_Agree_New;				//新来电
			if(CN_st_Affair_Gprs.CN_st_Affair_Phone.ptFunNewPhone!=NULL)
			{	OSSemPost(GprsUseSem);
				CN_st_Affair_Gprs.CN_st_Affair_Phone.ptFunNewPhone(ptst_Data_Gprs_Call->Phone);		
		 		OSSemPend(GprsUseSem, 0, &err);
			}
		}
		else 												//主动拨号
			ptst_Data_Gprs_Call->Mod=CN_st_GprsHard_CallState.CallType;
		ptst_Data_Gprs_Call->PhoneState=CN_st_GprsHard_CallState.State;
		return De_Suc_Gprs;
	}
	else if(ptst_Data_Gprs_Call->Mod==De_GprsHard_CallType_Passive) 			//如果上次是来电
	{	if(CN_st_GprsHard_CallState.CallType==De_GprsHard_CallType_NoCall)		//恢复正常,说明机器挂机
		{	ptst_Data_Gprs_Call->Mod=De_GprsHard_CallType_NoCall;
			if(CN_st_Affair_Gprs.CN_st_Affair_Phone.ptFunHupWork!=NULL)			//如果为空
			{	OSSemPost(GprsUseSem);
				CN_st_Affair_Gprs.CN_st_Affair_Phone.ptFunHupWork(ptst_Data_Gprs_Call->Phone);	
				OSSemPend(GprsUseSem, 0, &err);
			}
			return De_Suc_Gprs;
		}
		ptst_Data_Gprs_Call->Mod=CN_st_GprsHard_CallState.CallType;
		ptst_Data_Gprs_Call->PhoneState=CN_st_GprsHard_CallState.State;
		return De_Suc_Gprs;
	}
	else					//主动打电话的状态
	{	ptst_Data_Gprs_Call->Mod=CN_st_GprsHard_CallState.CallType;
		ptst_Data_Gprs_Call->PhoneState=CN_st_GprsHard_CallState.State;
		return De_Suc_Gprs;
	}
}

/*==========================================判断系统状态====================================================*/
static uint16 JugeSys(void)	 								//判断系统
{	uint8 Imei[20];
	uint16 Result,ReSize;
	uint8 State;

	if((Result=CN_st_Fun_GprsHard.Read(De_GprsHard_Com_GetModermCard,NULL,NULL,&State,NULL))!=De_Suc_GprsHard)//获取模块状态
	{	CN_st_Gsm_Net_Information.SimCarkState=State;
		return Result;
	}
	CN_st_Gsm_Net_Information.SimCarkState=State;
	if(State!=De_GprsHard_SimState_Yes)
		return De_Erro_Gprs_NoCard;			
	if((Result=CN_st_Fun_GprsHard.Read(De_GprsHard_Com_GetModermState,NULL,NULL,&State,NULL))!=De_Suc_GprsHard)//获取模块状态
		return Result;
	CN_st_Gsm_Net_Information.ModelState=State;	
	if((State==De_GprsHard_State_1)||(State==De_GprsHard_State_2))
		return De_Erro_Gprs_MEErro;

	if((Result=CN_st_Fun_GprsHard.Read(De_GprsHard_Com_Reg,NULL,NULL,&State,NULL))!=De_Suc_GprsHard)  //注册情况
		return Result;
	CN_st_Gsm_Net_Information.RegisterState=State;
	if(!((State==De_GprsHard_Reg_State_RegedRove)||(State==De_GprsHard_Reg_State_Reged)))
		return De_Erro_Gprs_CardNoReg;
	
	
	if((Result=CN_st_Fun_GprsHard.Read(De_GprsHard_Com_SQ,NULL,NULL,&State,NULL))!=De_Suc_GprsHard)//信号强度
		return Result;
	CN_st_Fun_Uart.Write(0,"SQ_OK\r\n",7);
	CN_st_Gsm_Net_Information.Csq=State;
	return De_Suc_Gprs;
}

static uint16 JugeMessage(void)
{	uint8 Centr[De_Gprs_PhoneNumber_Size+1];
	uint16 Result,ReSize;
	CN_st_Fun_AscNumber.ClsArray(Centr,sizeof(Centr));
	if((Result=CN_st_Fun_GprsHard.Read(De_GprsHard_Com_GetCenterNumber,NULL,NULL,Centr,&ReSize))!=De_Suc_GprsHard)
		return Result;
	CN_st_Fun_AscNumber.MoveByte(CN_st_Gsm_Net_Message.CenterNum,Centr,ReSize);
	return De_Suc_Gprs;
}
static uint16 JugeIPData(void)
{ 	
	uint16 Result;
	uint8 i,LinkState;
	if((Result=CN_st_Fun_GprsHard.Read(De_GprsHard_Com_SeeCGDCONT,NULL,NULL,&CN_st_Data_IPNet,NULL))!=De_Suc_GprsHard)
   		return Result;
	if((Result=CN_st_Fun_GprsHard.Read(De_GprsHard_Com_JugeETCPIP,NULL,NULL,&CN_st_HardWare_SeeTCPData,NULL))!=De_Suc_GprsHard)	
		return Result;
	if(CN_st_HardWare_SeeTCPData.State!=De_GprsHard_InitTcp_Over)
		return De_Erro_Gprs_NoTCPIP;
	for(i=0;i<De_GprsHard_MaxLink;i++)
	{	if(ptst_Data_Gprs_TcpUdp[i]->OpenOrClose!=De_GprsHard_Link_Open)
			continue;
		if((Result=CN_st_Fun_GprsHard.Read(De_GprsHard_Com_SEEIPCLOSE,(void *)&CN_LinkNumber[i],NULL,&LinkState,NULL))!=De_Suc_GprsHard)
			return Result;
		if(LinkState!=De_GprsHard_Link_Open)
			return De_Erro_Gprs_LinkClose;
	}
	return De_Suc_Gprs;
}

/*============================================恢复系统状态=======================================================*/
static uint16 BackUpSys(void)											//恢复系统状态
{	uint8 State[3];
	uint16 Result;
	uint8 MessageState,PhoneState,IPState;
	uint8 i;
	CN_st_Fun_AscNumber.ClsArray(State,sizeof(State));
	MessageState=CN_st_Affair_Gprs.MessageState;
	PhoneState=CN_st_Affair_Gprs.PhoneState;
	IPState=CN_st_Affair_Gprs.IPstate;
	for(i=0;i<De_GprsHard_MaxLink;i++)
		State[i]=ptst_Data_Gprs_TcpUdp[i]->OpenOrClose;	
	CloseSys();
	InitSys();
	if(MessageState==De_Gprs_State_Open)
	{	if((Result=InitMessage())!=De_Suc_Gprs)
			return Result;
	}
	if(PhoneState==De_Gprs_State_Open)
	{	if((Result=InitPhone())!=De_Suc_Gprs)
			return Result;
	}
	if(IPState==De_Gprs_State_Open)
	{ 	for(i=0;i<De_GprsHard_MaxLink;i++)
			ptst_Data_Gprs_TcpUdp[i]->OpenOrClose=State[i];
		if((Result=BackUpIP())!=De_Suc_Gprs)
			return Result;
	}
	return De_Suc_Gprs; 
}

static uint16 BackUpIP(void)   											//恢复IP状态
{	st_Data_IPPar	CN_st_Data_IPPar;
	st_Data_OpenUDPTCP	CN_st_Data_OpenUDPTCP;
	uint8 State[De_GprsHard_MaxLink];
	uint16 Result;
	uint8 i;
	CN_st_Fun_AscNumber.ClsArray(State,sizeof(State));
	for(i=0;i<De_GprsHard_MaxLink;i++)
		State[i]=ptst_Data_Gprs_TcpUdp[i]->OpenOrClose;		
	CloseIP(De_Gprs_Fd_All);
	if((Result=InitGprs(&CN_st_Data_IPNet))!=De_Suc_Gprs)
		return Result;
	for(i=0;i<De_GprsHard_MaxLink;i++)
	{	if(State[i]==De_GprsHard_Link_Close)
			continue;
		CN_st_Data_OpenUDPTCP.OpenType=ptst_Data_Gprs_TcpUdp[i]->CN_st_Data_UDPTCP.LinkType;
		CN_st_Data_OpenUDPTCP.fd=CN_LinkNumber[i];
		CN_st_Data_OpenUDPTCP.ptst_Data_IPPar=&CN_st_Data_IPPar;
//		CN_st_Data_IPPar.IP=ptst_Data_Gprs_TcpUdp[i]->CN_st_Data_UDPTCP.IP;
		CN_st_Fun_AscNumber.MoveByte(&CN_st_Data_IPPar.IP,&ptst_Data_Gprs_TcpUdp[i]->CN_st_Data_UDPTCP.IP,4);
		CN_st_Data_IPPar.Com=ptst_Data_Gprs_TcpUdp[i]->CN_st_Data_UDPTCP.Com;
		if((Result=CN_st_Fun_GprsHard.Read(De_GprsHard_Com_IPOPENX,&CN_st_Data_OpenUDPTCP,NULL,NULL,NULL))!=De_Suc_GprsHard)
			return Result;
		ptst_Data_Gprs_TcpUdp[i]->OpenOrClose=De_GprsHard_Link_Open;
		ptst_Data_Gprs_TcpUdp[i]->DataLen=0;
		ptst_Data_Gprs_TcpUdp[i]->State=De_Gprs_UDPTCP_Agree_Ide;
	}
	return De_Suc_Gprs;
}

static uint32 GetTimeAdd(uint8 *Small,uint8 *Big)
{	uint8 Curtimer[7];
	uint32 i;
	CN_st_Fun_AscNumber.ClsArray(Curtimer,sizeof(Curtimer));
	if(CN_st_Fun_AscNumber.CompareVa(Big,Small,7,De_AscNumber_Va_Big)!=De_AscNumber_Va_True)
	{	return 0;

	}
	CN_st_Fun_AscNumber.MoveByte(Curtimer,Small,7);
	for(i=0;CN_st_Fun_AscNumber.CompareBuf(Curtimer,Big,7)!=0;i++)
	{	if(i>150)
			break;
		CN_st_Fun_Date.Next(Curtimer,De_Type_Date_Second);	
	}
	return i;				
}


