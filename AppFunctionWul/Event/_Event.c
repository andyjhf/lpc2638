/*=========================================控件层加载======================================================*/
typedef struct
{	uint16 Command;
	uint16 DataLen;
	uint8 *Buf;
	uint16 Result;
	OS_EVENT	*ResSem;
}st_Event_Box;													//邮箱的事件
typedef struct
{ 	uint16 Command;
	uint16 (*ptFun)(void);
}st_Contrl_Function;

const st_Contrl_Function	CN_st_Contrl_Function[]=
{	{De_EventBox_DownLoaderContr_Acc,CN_st_Fun_Acc.Init},		  		
	{De_EventBox_DownLoaderContr_Adc,CN_st_Fun_CheckVoltage.Init},
	{De_EventBox_DownLoaderContr_Can,CN_st_Fun_CanControl.Init},
	{De_EventBox_DownLoaderContr_Gprs,CN_st_Fun_Gprs.Init},
	{De_EventBox_DownLoaderContr_Gps,CN_st_Control_Fun_Gps.Init},
	{De_EventBox_DownLoaderContr_Sleep,CN_st_Fun_Sleep.Init},
	{De_EventBox_DownLoaderContr_Timer,CN_st_Fun_Timer.Init},
	{De_EventBox_DownLoaderContr_Hand,CN_st_Fun_Hand.Init}
};


#define De_Erro_Contrl_No							1000								//无此控件
/*===========================================控件层加载======================================================*/
static void DownLoaderContr(st_Event_Box	*ptst_Event_Box)					//加载控件						
{	uint16 i;
	for(i=0;i<De_EventBox_DownLoaderContr_Number;i++)
	{	if(ptst_Event_Box->Command==CN_st_Contrl_Function[i].Command)
		{	ptst_Event_Box->Result=CN_st_Contrl_Function[i].ptFun();
			break;
		}	
	}
	if(i==De_EventBox_DownLoaderContr_Number)									//无此控件
		ptst_Event_Box->Result=De_Erro_Contrl_No;			
	OSMboxPost(ptst_Event_Box->Result,(void *)1); 								//回复操作情况
}



/*============================================文件系统层加载=================================================*/
static void DownLoaderFile(st_Event_Box	*ptst_Event_Box)						//加载文件系统
{	ptst_Event_Box->Result=CN_st_Fun_Spi.Open();
	if(ptst_Event_Box->Result!=De_Suc_Spi)
	{ 	OSMboxPost(ptst_Event_Box->Result,(void *)1);
		return ;	
	}
	ptst_Event_Box->Result=CN_st_Fun_NorFlashPhy1.Init1();
	if(ptst_Event_Box->Result!=De_Suc_SpiFlash)
	{	OSMboxPost(ptst_Event_Box->Result,(void *)1);
		return ;
	}
	ptst_Event_Box->Result=CN_st_Fun_File.Init();
	OSMboxPost(ptst_Event_Box->Result,(void *)1);
	return ;
}
static void OpenFile(st_Event_Box	*ptst_Event_Box)							//打开需要使用的全局文件
{



}
static void BackFacTran(st_Event_Box	*ptst_Event_Box) 						//恢复出厂值
{




}
/*===========================================内部事件触发====================================================*/
typedef struct
		{	uint8 APN[32];				//ASC,以‘/0'作为结束
			uint8 Use[16];				//ASC,以‘/0'作为结束
			uint8 PassWord[8];			//ASC,以‘/0'作为结束	
		}st_Data_IPNet;
#define De_Event_Dev_APN_Number					3
static void Dev_APN(st_Event_Box	*ptst_Event_Box)
{	st_Data_IPNet	CN_st_Data_IPNet;									//APN的参数
	st_Gprs_ComPar	CN_st_Gprs_ComPar;
	uint8 i;
	CN_st_Fun_File.ReadRecoder(CN_st_File_fd.GprsParfd,0,&CN_st_Gprs_ComPar);
	CN_st_Fun_AscNumber.MoveByte(CN_st_Data_IPNet.APN,CN_st_Gprs_ComPar.CN_st_Gprs_IPNet.APN,32);
	CN_st_Fun_AscNumber.MoveByte(CN_st_Data_IPNet.Use,CN_st_Gprs_ComPar.CN_st_Gprs_IPNet.Use,16);
	CN_st_Fun_AscNumber.MoveByte(CN_st_Data_IPNet.PassWord,CN_st_Gprs_ComPar.CN_st_Gprs_IPNet.PassWord,8);
   	for(i=0;i<De_Event_Dev_APN_Number;i++)
	{	ptst_Event_Box->Result=InitTCPIP(st_Data_IPNet *ptst_Data_IPNet);
	 	if(ptst_Event_Box->Result==De_Suc_Moderm)
			break;				
	}
	OSMboxPost(ptst_Event_Box->Result,(void *)1);
}
#define De_Gprs_OpenLink_UDP								1				//UDP链路
#define De_Gprs_OpenLink_TCP								2				//TCP链路
#define De_Ucos_Tick										1000/OS_TICKS_PER_SEC
OS_EVENT	*UDPSendBox;
static void Dev_Login(st_Event_Box	*ptst_Event_Box) 							//定位终端首次登陆
{	union 
	{	st_Gprs_ComPar	CN_st_Gprs_ComPar;			
	 	uint8 Buf[40];
	}CN_st_Uion_Login;
	uint32 TimerOut;
	uint16 Result;
	uint8 fd;
	void *MessBuf;
	CN_st_Fun_File.ReadRecoder(CN_st_File_fd.GprsParfd,0,&CN_st_Gprs_ComPar);
	if(LoginUDP(&CN_st_Gprs_ComPar.CN_Mast_st_Gprs_IP,CN_st_Gprs_ComPar.CenPort,&fd)!=De_Event_Suc)
	{	Result=LoginUDP(&CN_st_Gprs_ComPar.CN_Reserve_st_Gprs_IP,CN_st_Gprs_ComPar.CenPort,&fd);
		if(Result!=De_Event_Suc)											//登录不成功
		{	ptst_Event_Box->Result=Result;	
			OSMboxPost(ptst_Event_Box->Result,(void *)1);
			return ;
		}
	}
	CN_st_Fun_AscNumber.ClsArray(CN_st_Uion_Login.Buf,40);					
	GetGps(CN_st_Uion_Login.Buf);
	MessBuf=SendDataUDP(fd,CN_st_Uion_Login.Buf,39,&Result);				//发送一个UDP命令
	if(Result!=De_Suc_DataTrans)											//登录不成功
	{	ptst_Event_Box->Result=Result;	
		OSMboxPost(ptst_Event_Box->Result,(void *)1);
		return ;
	}
	;												//登录一个服务器




	
		



	OSQPend(FileCommad,2,&err); 


		





	OpenUDPTCP(st_Data_UDPTCP *ptst_Data_UDPTCP,st_Affair_UDPTCP	*ptst_Affair_UDPTCP,uint8 *fd);

}


static void Dev_Sleep(st_Event_Box	*ptst_Event_Box)  					//定位终端休眠
{





}

static void Dev_ClosGprs(st_Event_Box	*ptst_Event_Box)				//关机
{





}

static void Dev_




























static uint16 LoginUDP(st_Gprs_IP	*ptst_Gprs_IP,uint16 Port,uint8 *fd)					//登录UDP链路
{	const st_Affair_UDPTCP	CN_st_Affair_UDPTCP={NULL};
	uint16 Result;
	st_Data_UDPTCP	CN_st_Data_UDPTCP;
 	CN_st_Fun_AscNumber.ClsArray(&CN_st_Data_UDPTCP,sizeof(st_Data_UDPTCP));
   	CN_st_Data_UDPTCP.LinkType=De_Gprs_OpenLink_UDP;				//打开UDP链路
	CN_st_Data_UDPTCP.Com=Port;		 								//端口号
	if(ptst_Gprs_IP->DomainName[0]!=0) 			//域名有效
	{	if(CN_st_Fun_Gprs.DNSRIP(ptst_Gprs_IP->DomainName,&CN_st_Data_UDPTCP.IP)==De_Suc_Moderm)
		{	if(CN_st_Fun_Gprs.OpenUDPTCP(&CN_st_Data_UDPTCP,(st_Affair_UDPTCP	*)&CN_st_Affair_UDPTCP,fd)==De_Suc_Moderm)			
		  		return De_Event_Suc;
		} 	
	}
	CN_st_Data_UDPTCP.IP=ptst_Gprs_IP->IP;
	return CN_st_Fun_Gprs.OpenUDPTCP(&CN_st_Data_UDPTCP,(st_Affair_UDPTCP	*)&CN_st_Affair_UDPTCP,fd);
}








static void 
















static void Dev_Sleep()