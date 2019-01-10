#define De_LogOnServer_Compiler
#include "LogOnServer.h"
static uint16 Init(void)
{	LogOnServerBox=OSMboxCreate(NULL);
	if(LogOnServerBox==NULL)
		return De_Erro_LogOnServer_Init;
	CN_st_LogOnServer_OpenFd.Tzv21State=De_LogOnServer_Order_Link_Idle;
	CN_st_LogOnServer_OpenFd.SensorState=De_LogOnServer_Order_Link_Idle;
	CN_st_LogOnServer_OpenFd.IPLinkState=De_LogOnServer_Order_Link_Idle;
	OSTaskCreate(Task,(void *)0, &LogOnServer_Stk[De_LogOnServer_Stk - 1],De_LogOnServer_Task);
	return De_Suc_Login;
}

static void Task(void *pdata)
{	uint8 err;
	uint16 Result;
	pdata=pdata;
	for(;;OSTimeDly(De_LogOnServer_TaskDly),WatchDog())
	{	ptst_BoxData_LogOnServer = OSMboxPend(LogOnServerBox,0,&err);
		if(ptst_BoxData_LogOnServer->Command==De_LogOnServer_Order_Link_Open)
		{	CloseSms();
			CN_st_Fun_AscNumber.MoveByte(&CN_st_BoxData_LogOnServer,ptst_BoxData_LogOnServer,sizeof(st_BoxData_LogOnServer));	
			if(CN_st_LogOnServer_OpenFd.Tzv21State!=De_LogOnServer_Order_Link_Idle)
			{	CN_st_Fun_Tzv21.Close(CN_st_LogOnServer_OpenFd.Tzv21Fd);
				CN_st_LogOnServer_OpenFd.Tzv21State=De_LogOnServer_Order_Link_Idle;
 			}
			if(CN_st_LogOnServer_OpenFd.SensorState!=De_LogOnServer_Order_Link_Idle)
			{	CN_st_Fun_Sensor.Close(CN_st_LogOnServer_OpenFd.SensorFd);
				CN_st_LogOnServer_OpenFd.SensorState=De_LogOnServer_Order_Link_Idle;
			}
			if(CN_st_LogOnServer_OpenFd.IPLinkState!=De_LogOnServer_Order_Link_Idle)
			{	Result=CN_st_Fun_Gprs.CloseIP(CN_st_LogOnServer_OpenFd.IPLinkFd);
				if(Result!=De_Suc_Gprs)
				{	OSMboxPost(LogOnServerBox,&CN_st_BoxData_LogOnServer);
					continue;
				}	
				CN_st_LogOnServer_OpenFd.IPLinkState=De_LogOnServer_Order_Link_Idle;
				
			}
			Result=Login((void *)ptst_BoxData_LogOnServer->ptLinkCloseFun,(void *)ptst_BoxData_LogOnServer->AgreeOnNewDataFun,&ptst_BoxData_LogOnServer->Result);
			if(Result==De_Suc_Login)
			{	OSMboxPost(ptst_BoxData_LogOnServer->ReBox,&ptst_BoxData_LogOnServer->Result);
				if(ptst_BoxData_LogOnServer->ptSuc!=NULL)
					ptst_BoxData_LogOnServer->ptSuc();	
				OpenSms();

			}
			else
				OSMboxPost(LogOnServerBox,&CN_st_BoxData_LogOnServer); 
			
		}
		else if(ptst_BoxData_LogOnServer->Command==De_LogOnServer_Order_Link_Close)
		{	if(CN_st_LogOnServer_OpenFd.Tzv21State!=De_LogOnServer_Order_Link_Idle)
				CN_st_Fun_Tzv21.Close(CN_st_LogOnServer_OpenFd.Tzv21Fd);
			if(CN_st_LogOnServer_OpenFd.SensorState!=De_LogOnServer_Order_Link_Idle)
				CN_st_Fun_Sensor.Close(CN_st_LogOnServer_OpenFd.SensorFd);
			if(CN_st_LogOnServer_OpenFd.IPLinkState!=De_LogOnServer_Order_Link_Idle)
				CN_st_Fun_Gprs.CloseIP(CN_st_LogOnServer_OpenFd.IPLinkFd);
			CN_st_LogOnServer_OpenFd.Tzv21State=De_LogOnServer_Order_Link_Idle;
			CN_st_LogOnServer_OpenFd.SensorState=De_LogOnServer_Order_Link_Idle;
			CN_st_LogOnServer_OpenFd.IPLinkState=De_LogOnServer_Order_Link_Idle;
			ptst_BoxData_LogOnServer->Result=0;
			OSMboxPost(ptst_BoxData_LogOnServer->ReBox,&ptst_BoxData_LogOnServer->Result);
		}		
	}
}
static uint16 Login(void *ptFun,void *AgreeOnFun,uint8 *AgreeOnfd)
{//	st_Sensor_DataPar	CN_st_Sensor_DataPar;
	st_AgreeOn_ConfigCentrSever	CN_st_AgreeOn_ConfigCentrSever;
	uint16 Result;
	uint8 fd;//,Sensorfd;
	if((Result=Dev_APN())!=De_Suc_Login) 										//APN拨号
		return Result;
	if((Result=Dev_Login(&fd))!=De_Suc_Login)									//首次登录
		return Result;
	if((Result=GetSevPar(&CN_st_AgreeOn_ConfigCentrSever,fd))!=De_Suc_Login)	//获取服务器参数
	{	CN_st_Fun_Gprs.CloseIP(fd);
		return Result;	
	}
	CN_st_Fun_Gprs.CloseIP(fd);
	if((Result=OpenSev(&CN_st_AgreeOn_ConfigCentrSever,ptFun,&fd))!=De_Suc_Login) //重新根据新的登录
		return Result;
	if((Result=CreatDev(fd))!=De_Suc_Login)	  									  //加载GPRS设备
		return Result;
	return CreartAgreeOn(AgreeOnfd,AgreeOnFun);									  //加载天泽协议
}	

static uint16 Dev_APN(void)
{	st_Data_IPNet	CN_st_Data_IPNet;									//APN的参数
	st_Gprs_ComPar	CN_st_Gprs_ComPar;
	uint16 Result;
	CN_st_Fun_File.ReadRecoder(CN_st_File_fd.GprsParfd,0,&CN_st_Gprs_ComPar);
	CN_st_Fun_AscNumber.MoveByte(CN_st_Data_IPNet.APN,CN_st_Gprs_ComPar.CN_st_Gprs_IPNet.APN,32);
	CN_st_Fun_AscNumber.MoveByte(CN_st_Data_IPNet.Use,CN_st_Gprs_ComPar.CN_st_Gprs_IPNet.Use,16);
	CN_st_Fun_AscNumber.MoveByte(CN_st_Data_IPNet.PassWord,CN_st_Gprs_ComPar.CN_st_Gprs_IPNet.PassWord,8);
	Result=CN_st_Fun_Gprs.InitGprs(&CN_st_Data_IPNet);				
	return Result;
}
static uint16 Dev_Login(uint8 *fd) 							//定位终端首次登陆
{	st_Gprs_ComPar	CN_st_Gprs_ComPar;			
	CN_st_Fun_File.ReadRecoder(CN_st_File_fd.GprsParfd,0,&CN_st_Gprs_ComPar);
	if(LoginUDP(&CN_st_Gprs_ComPar.CN_Mast_st_Gprs_IP,CN_st_Gprs_ComPar.CenPort,fd)!=De_Suc_Login)
		return LoginUDP(&CN_st_Gprs_ComPar.CN_Reserve_st_Gprs_IP,CN_st_Gprs_ComPar.CenPort,fd);
	return De_Suc_Login;
}

static uint16 GetSevPar(st_AgreeOn_ConfigCentrSever	*ptst_AgreeOn_ConfigCentrSever,uint8 fd)
{	st_File_Basic	CN_st_File_Basic;
	uint8 DateTimer[7],DateTimer1[7],i;
	CN_st_Fun_File.ReadRecoder(CN_st_File_fd.Basicfd,0,&CN_st_File_Basic);
	for(i=0;i<3;i++)
	{	CN_st_Fun_RTC.Read(DateTimer);
		if(GetSevParSigle(CN_st_File_Basic.IMEI,ptst_AgreeOn_ConfigCentrSever,8,fd)==De_Suc_Login)	
			return De_Suc_Login;
		for(;;WatchDog(),OSTimeDly(100))
		{	CN_st_Fun_RTC.Read(DateTimer1);
			if(GetTimeAdd(DateTimer,DateTimer1)>=8)
				break;
		}		
	}
	return De_Erro_Login;	
}

static uint16 OpenSev(st_AgreeOn_ConfigCentrSever	*ptst_AgreeOn_ConfigCentrSever,void *ptFun,uint8 *fd)
{	st_Data_UDPTCP	CN_st_Data_UDPTCP;
	st_Gprs_ComPar	CN_st_Gprs_ComPar;
	st_File_Basic	CN_st_File_Basic;
	st_Affair_UDPTCP	CN_st_Affair_UDPTCP={NULL,NULL};
	uint16 Result;
	CN_st_Fun_AscNumber.ClsArray(&CN_st_Data_UDPTCP,sizeof(st_Data_UDPTCP));
	CN_st_Data_UDPTCP.IP=ptst_AgreeOn_ConfigCentrSever->IP;
	CN_st_Data_UDPTCP.LinkType=De_GprsHard_UDPTCP_UDP;
	CN_st_Data_UDPTCP.Com=ptst_AgreeOn_ConfigCentrSever->Port;
	CN_st_Fun_File.ReadRecoder(CN_st_File_fd.GprsParfd,0,&CN_st_Gprs_ComPar);
	CN_st_Data_UDPTCP.SelfHeartTimer=CN_st_Gprs_ComPar.CN_st_Gprs_BasicPar.DeviceHeart;
	CN_st_Data_UDPTCP.CentrHeartTimer=CN_st_Gprs_ComPar.CN_st_Gprs_BasicPar.CentrHeart;
	CN_st_Data_UDPTCP.CentrHeartData[0]=0X00;
	CN_st_Data_UDPTCP.CentrHeartData[1]=0X02;
	CN_st_Data_UDPTCP.CentrHeartLength=2;	  
	CN_st_Data_UDPTCP.SelfHeartData[0]=0X00;
	CN_st_Data_UDPTCP.SelfHeartData[1]=0X09;
	CN_st_Fun_File.ReadRecoder(CN_st_File_fd.Basicfd,0,&CN_st_File_Basic);
	CN_st_Fun_AscNumber.MoveByte(CN_st_Data_UDPTCP.SelfHeartData+2,CN_st_File_Basic.IMEI,7);
	CN_st_Data_UDPTCP.HeartDataLength=0x09;
	CN_st_Affair_UDPTCP.ptFunLinkClose=ptFun;
	Result=CN_st_Fun_Gprs.OpenIP(&CN_st_Data_UDPTCP,&CN_st_Affair_UDPTCP,fd);
	if(Result==De_Suc_Gprs)
	{	CN_st_LogOnServer_OpenFd.IPLinkFd=*fd;
		CN_st_LogOnServer_OpenFd.IPLinkState=De_LogOnServer_Order_Link_Online;
	}
	return Result;
}

static uint16 CreatDev(uint8 fd)									//创建协议
{	st_Sensor_DataPar	CN_st_Sensor_DataPar;
	uint8 Parfd;
	uint16 Result;
	if((CN_st_Fun_Sensor.GetPar2ID(De_Sensor_WordPar_GprsTzxy_1,&Parfd))==De_Suc_Sensor) 	
		CN_st_Fun_Sensor.Close(Parfd);
   	CN_st_Fun_AscNumber.ClsArray(&CN_st_Sensor_DataPar,sizeof(st_Sensor_DataPar));
	CN_st_Sensor_DataPar.Addree=fd;
	CN_st_Sensor_DataPar.WorkPar=De_Sensor_WordPar_GprsTzxy_1;
	Result=CN_st_Fun_Sensor.Open(&CN_st_Sensor_DataPar,&Parfd);
	if(Result==De_Suc_Login)
	{	CN_st_LogOnServer_OpenFd.SensorFd=Parfd;
		CN_st_LogOnServer_OpenFd.SensorState=De_LogOnServer_Order_Link_Online;
	}
	return Result;	
}

static uint16 CreartAgreeOn(uint8 *fd,void *AgreeOnFun) 						//创建协议
{	st_Gprs_ComPar	CN_st_Gprs_ComPar;
	st_File_Basic	CN_st_File_Basic;
	st_AgreeOn_OpenPar	CN_st_AgreeOn_OpenPar;
	st_Appair_Tzv2	CN_st_Appair_Tzv2;//={AgreeOnFun};
	uint16 Result;
	CN_st_Appair_Tzv2.ptFunction=AgreeOnFun;
	if(CN_st_Fun_Tzv21.GetPar2ID(De_Sensor_WordPar_GprsTzxy_1,fd)==De_Suc_AgreeOn)
		CN_st_Fun_Tzv21.Close(*fd);	
	CN_st_Fun_File.ReadRecoder(CN_st_File_fd.Basicfd,0,&CN_st_File_Basic);
	CN_st_Fun_AscNumber.MoveByte(CN_st_AgreeOn_OpenPar.IMEI,CN_st_File_Basic.IMEI,7);
   	CN_st_AgreeOn_OpenPar.WorkPar=De_Sensor_WordPar_GprsTzxy_1;
	CN_st_Fun_File.ReadRecoder(CN_st_File_fd.GprsParfd,0,&CN_st_Gprs_ComPar);
	CN_st_AgreeOn_OpenPar.MaxDelay=20;
	CN_st_AgreeOn_OpenPar.IPRepeat=CN_st_Gprs_ComPar.CN_st_Gprs_BasicPar.Repeat;
	CN_st_AgreeOn_OpenPar.IPRepeatTime=CN_st_Gprs_ComPar.CN_st_Gprs_BasicPar.RepeatTime;
	Result=CN_st_Fun_Tzv21.Open(&CN_st_AgreeOn_OpenPar,&CN_st_Appair_Tzv2,fd);
	if(Result==De_Suc_Login)
	{	CN_st_LogOnServer_OpenFd.Tzv21Fd=*fd;
		CN_st_LogOnServer_OpenFd.Tzv21State=De_LogOnServer_Order_Link_Online;
	}
	return Result;
}

static uint16 GetSevParSigle(uint8 *IMEI,st_AgreeOn_ConfigCentrSever	*ptst_AgreeOn_ConfigCentrSever,uint32 MaxDelay,uint8 fd)
{	st_Dev_Tzxy_Send	CN_st_Dev_Tzxy_Send;
//	st_Dev_Tzxy_Agree	CN_st_Dev_Tzxy_Agree;
	uint8 DateTimer[7];
	uint8 DateTimer1[7],Byte;
	uint8 X_BUF[100];	
	uint16 Result,DataLen,OrderID,ReDataLen;
//	uint8 Parfd;//i,
	if((Result=CN_st_Fun_Tz_Send.Write(X_BUF+17,&App_CN_st_WorkFlow_Table.CN_st_AgreeOn_Send_Basic,&DataLen,
	De_Dev_Order_GetSeverComPar))!=De_Suc_AgreeOn)
		return Result;
	X_BUF[0]=((DataLen+17)>>8);
	X_BUF[1]=((DataLen+17)&0xff);
	X_BUF[2]=2;
	X_BUF[3]=1;
	CN_st_Fun_AscNumber.MoveByte(X_BUF+4,IMEI,7);
	X_BUF[11]=0;
	X_BUF[12]=0;
	X_BUF[13]=0;
	X_BUF[14]=0;
	X_BUF[15]=((De_Dev_Order_GetSeverComPar>>8)&0xff);
	X_BUF[16]=((De_Dev_Order_GetSeverComPar)&0xff);
	CN_st_Dev_Tzxy_Send.ResultOrSend=De_Tzxy_SendBuf_Send;
	CN_st_Dev_Tzxy_Send.SizeofBuf=DataLen+17;
   	CN_st_Dev_Tzxy_Send.Buf=X_BUF;
	if((Result=CN_st_Fun_Gprs.SendIP(fd,X_BUF,DataLen))!=De_Suc_Gprs)
		return Result;
	CN_st_Fun_RTC.Read(DateTimer);
	for(;;OSTimeDly(200),WatchDog())
	{	CN_st_Fun_RTC.Read(DateTimer1);
		if(GetTimeAdd(DateTimer,DateTimer1)>=MaxDelay)
			return De_Erro_AgreeOn_TimerOver;
		if((Result=CN_st_Fun_Gprs.ReadIP(fd,X_BUF,&DataLen))!=De_Suc_Sensor)
			continue;
		if(DataLen<17)														//解析错误
			continue;
		if(CN_st_Fun_AscNumber.CompareBuf(X_BUF+4,IMEI,7)!=0) 				//合法性判断
			continue;
		Byte=X_BUF[0];
		ReDataLen=Byte*0x100;
		Byte=X_BUF[1];
		ReDataLen+=Byte;
		if(ReDataLen>DataLen)
			continue;
		OrderID=X_BUF[15]*0X100+X_BUF[16];
		if(OrderID!=De_Centr_Order_ConfigCentrSever)
			continue;
		CN_st_Fun_Tz_Agreen.Read(X_BUF+17,ptst_AgreeOn_ConfigCentrSever,ReDataLen-17,De_Centr_Order_ConfigCentrSever);
		return De_Suc_AgreeOn;
	}
}


static uint16 LoginUDP(st_Gprs_IP	*ptst_Gprs_IP,uint16 Port,uint8 *fd)					//登录UDP链路
{	const st_Affair_UDPTCP	CN_st_Affair_UDPTCP={NULL,NULL};
//	uint16 Result;
	st_Data_UDPTCP	CN_st_Data_UDPTCP;
 	CN_st_Fun_AscNumber.ClsArray(&CN_st_Data_UDPTCP,sizeof(st_Data_UDPTCP));
   	CN_st_Data_UDPTCP.LinkType=De_GprsHard_UDPTCP_UDP;				//打开UDP链路
	CN_st_Data_UDPTCP.Com=Port;		 								//端口号
	if(ptst_Gprs_IP->DomainName[0]!=0) 			//域名有效
	{	if(CN_st_Fun_Gprs.DNSRIP(ptst_Gprs_IP->DomainName,&CN_st_Data_UDPTCP.IP)==De_Suc_Gprs)
		{	if(CN_st_Fun_Gprs.OpenIP(&CN_st_Data_UDPTCP,(st_Affair_UDPTCP	*)&CN_st_Affair_UDPTCP,fd)==De_Suc_Gprs)			
		  		return De_Suc_Login;
		} 	
	}
	if(ptst_Gprs_IP->IP==0)
		return De_Erro_Login_NoIP;
	CN_st_Data_UDPTCP.IP=ptst_Gprs_IP->IP;
	return CN_st_Fun_Gprs.OpenIP(&CN_st_Data_UDPTCP,(st_Affair_UDPTCP	*)&CN_st_Affair_UDPTCP,fd);
}

static uint32 GetTimeAdd(uint8 *Small,uint8 *Big)
{	uint8 Curtimer[7];
	uint32 i;
	if(CN_st_Fun_AscNumber.CompareVa(Big,Small,7,De_AscNumber_Va_Big)!=De_AscNumber_Va_True)
		return 0;
	if((CN_st_Fun_Date.Juge(Small,De_Type_Date_Second)!=De_Suc_Date)||(CN_st_Fun_Date.Juge(Big,De_Type_Date_Second)!=De_Suc_Date))
		return 0;
	CN_st_Fun_AscNumber.MoveByte(Curtimer,Small,7);
	for(i=0;CN_st_Fun_AscNumber.CompareBuf(Curtimer,Big,7)!=0;i++)
		CN_st_Fun_Date.Next(Curtimer,De_Type_Date_Second);	
	return i;				
}

static void OpenSms(void)					//打开短信协议
{	uint8 Result;
	union
	{	st_File_Basic CN_st_File_Basic;
		st_Message_ComPar CN_st_Message_ComPar;
	}un;
	st_Appair_Tzv2	CN_st_Appair_Tzv2;
	st_Sensor_Sms_DataPar CN_st_Sensor_Sms_DataPar={{0,De_Sensor_WordPar_MessagTzxy,0xffffffff},{0}};
	st_AgreeOn_OpenPar	CN_st_AgreeOn_OpenPar=
	{	{0x01,0x45,0x4C,0xC5,0xF2,0x12,0xF6},0,De_Sensor_WordPar_MessagTzxy,60,2,8
	};
	CN_st_Fun_File.ReadRecoder(CN_st_File_fd.Basicfd,0,&un.CN_st_File_Basic);
	CN_st_Fun_AscNumber.MoveByte(CN_st_AgreeOn_OpenPar.IMEI,un.CN_st_File_Basic.IMEI,7);
	CN_st_Fun_File.ReadRecoder(CN_st_File_fd.MessageParfd,0,&un.CN_st_Message_ComPar);
	CN_st_Fun_AscNumber.MoveByte(CN_st_Sensor_Sms_DataPar.Phone,un.CN_st_Message_ComPar.CN_st_Message_Phone.CentrMessPhone1,CN_st_Fun_AscNumber.Strsize16(un.CN_st_Message_ComPar.CN_st_Message_Phone.CentrMessPhone1));
	CN_st_Fun_Sensor.Open((st_Sensor_DataPar	*)&CN_st_Sensor_Sms_DataPar,
	&CN_st_SmsLink_State.SensorFd);
	CN_st_Appair_Tzv2.ptFunction=CN_st_Fun_AppGprs.Read;
	CN_st_AgreeOn_OpenPar.fd=CN_st_SmsLink_State.SensorFd;
	if((Result=CN_st_Fun_Tzv21.Open(&CN_st_AgreeOn_OpenPar,&CN_st_Appair_Tzv2,&CN_st_SmsLink_State.Tzxy21Fd))==De_Suc_AgreeOn)
		CN_st_SmsLink_State.OpenOrClose=De_Link_State_Open;	
}
static void CloseSms(void)
{	if(CN_st_SmsLink_State.OpenOrClose!=De_Link_State_Close)
	{	CN_st_Fun_Tzv21.Close(CN_st_SmsLink_State.Tzxy21Fd);
		CN_st_Fun_Sensor.Close(CN_st_SmsLink_State.SensorFd);
		CN_st_SmsLink_State.OpenOrClose=De_Link_State_Close;	
	}
}





