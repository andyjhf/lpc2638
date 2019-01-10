/*=========================================控件层加载======================================================*/



static uint16 Login(void *ptFun,void *AgreeOnFun,uint8 *AgreeOnfd)
{	st_Sensor_DataPar	CN_st_Sensor_DataPar;
	st_AgreeOn_ConfigCentrSever	CN_st_AgreeOn_ConfigCentrSever;
	uint16 Result;
	uint8 fd,Sensorfd;
	if((Result=Dev_APN())!=De_Suc_Login) 										//APN拨号
		return Result;
	if((Result=Dev_Login(&fd))!=De_Suc_Login)									//首次登录
		return Result;
	if((Result=GetSevPar(&CN_st_AgreeOn_ConfigCentrSever,fd))!=De_Suc_Login)	//获取服务器参数
		return Result;	
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
	return De_Suc_Login;
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
	CN_st_Fun_File.ReadRecoder(CN_st_File_fd.Basicfd,0,&CN_st_File_Basic);
	for(i=0;i<3;i++)
	{	CN_st_Fun_RTC.Read(DateTimer);
		if(GetSevParSigle(CN_st_File_Basic.IMEI,ptst_AgreeOn_ConfigCentrSever,8,fd)==De_Suc_Login)	
			return De_Suc_Login;
		for(;;WatchDog())
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
	CN_st_Fun_AscNumber.ClsArray(&CN_st_Data_UDPTCP,sizeof(st_Data_UDPTCP));
	CN_st_Data_UDPTCP.IP=ptst_AgreeOn_ConfigCentrSever->IP;
	CN_st_Data_UDPTCP.LinkType=De_Gprs_OpenLink_UDP;
	CN_st_Data_UDPTCP.Com=ptst_AgreeOn_ConfigCentrSever->Port;
	CN_st_Fun_File.ReadRecoder(CN_st_File_fd.GprsParfd,0,&CN_st_Gprs_ComPar);
	CN_st_Data_UDPTCP.SelfHeartTimer=CN_st_Gprs_ComPar.CN_st_Gprs_BasicPar.SelfHeartTimer;
	CN_st_Data_UDPTCP.CentrHeartTimer=CN_st_Gprs_ComPar.CN_st_Gprs_BasicPar.CentrHeartTimer;
	CN_st_Data_UDPTCP.SelfHeartData[0]=0X00;
	CN_st_Data_UDPTCP.SelfHeartData[1]=0X02;
	CN_st_Data_UDPTCP.HeartDataLength=2;
	CN_st_Data_UDPTCP.CentrHeartData[0]=0X00;
	CN_st_Data_UDPTCP.CentrHeartData[1]=0X09;
	CN_st_Fun_File.ReadRecoder(CN_st_File_fd.Basicfd,0,&CN_st_File_Basic);
	CN_st_Fun_AscNumber.MoveByte(CN_st_Data_UDPTCP.CentrHeartData+2,CN_st_File_Basic.IMEI,7);
	CN_st_Data_UDPTCP.CentrHeartLength=0x09;
	CN_st_Affair_UDPTCP.ptFunLinkClose=ptFun;
	return CN_st_Fun_Gprs.OpenUDPTCP(&CN_st_Data_UDPTCP,&CN_st_Affair_UDPTCP,fd);
}

static uint16 CreatDev(uint8 fd)									//创建协议
{	st_Sensor_DataPar	CN_st_Sensor_DataPar;
	uint8 Parfd;
	if((CN_st_Fun_Sensor.GetPar2ID(De_Sensor_WordPar_GprsTzxy_1,&Parfd))==De_Suc_Sensor) 	
		CN_st_Fun_Sensor.Close(Parfd);
   	CN_st_Fun_AscNumber.ClsArray(&CN_st_Sensor_DataPar,sizeof(st_Sensor_DataPar));
	CN_st_Sensor_DataPar.Addree=fd;
	CN_st_Sensor_DataPar.WorkPar=De_Sensor_WordPar_GprsTzxy_1;
	return CN_st_Fun_Sensor.Open(&CN_st_Sensor_DataPar,&Parfd);		
}

static uint16 CreartAgreeOn(uint8 *fd,void *AgreeOnFun) 						//创建协议
{	st_Gprs_ComPar	CN_st_Gprs_ComPar;
	st_File_Basic	CN_st_File_Basic;
	st_AgreeOn_OpenPar	CN_st_AgreeOn_OpenPar;
	st_Appair_Tzv2	CN_st_Appair_Tzv2={AgreeOnFun};
	if(CN_st_Fun_Tzv21.GetPar2ID(De_Sensor_WordPar_GprsTzxy_1,fd)==De_Suc_AgreeOn)
		CN_st_Fun_Tzv21.Close(*fd);	
	CN_st_Fun_File.ReadRecoder(CN_st_File_fd.Basicfd,0,&CN_st_File_Basic);
	CN_st_Fun_AscNumber.MoveByte(CN_st_AgreeOn_OpenPar.IMEI,CentrHeartData+2,CN_st_File_Basic.IMEI,7);
   	CN_st_AgreeOn_OpenPar.WorkPar=De_Sensor_WordPar_GprsTzxy_1;
	CN_st_Fun_File.ReadRecoder(CN_st_File_fd.GprsParfd,0,&CN_st_Gprs_ComPar);
	CN_st_AgreeOn_OpenPar.MaxDelay=20;
	CN_st_AgreeOn_OpenPar.IPRepeat=CN_st_Gprs_ComPar.CN_CN_st_Gprs_BasicPar.IPRepeat;
	CN_st_AgreeOn_OpenPar.IPRepeatTime=CN_st_Gprs_ComPar.CN_CN_st_Gprs_BasicPar.IPRepeatTime;
	return CN_st_Fun_Tzv21.Open(&CN_st_AgreeOn_OpenPar,&CN_st_Appair_Tzv2);
}

static uint16 GetSevParSigle(uint8 *IMEI,st_AgreeOn_ConfigCentrSever	*ptst_AgreeOn_ConfigCentrSever,uint32 MaxDelay,uint8 fd)
{	st_Dev_Tzxy_Send	CN_st_Dev_Tzxy_Send;
	st_Dev_Tzxy_Agree	CN_st_Dev_Tzxy_Agree;
	uint8 DateTimer[7];
	uint8 DateTimer1[7],Byte;	
	uint16 Result,DataLen,OrderID,ReDataLen;
	uint8 i,Parfd;
	if((Result=CN_st_Fun_Tz_Send.Write(X_BUF+17,&App_CN_st_WorkFlow_Table.CN_st_AgreeOn_Send_Basic,&DataLen,
	De_Dev_Order_GetSeverComPar))!=De_Suc_AgreeOn)
		return Result;
	X_BUF[0]=((DataLen+17)>>8);
	X_BUF[1]=((DataLen+17)&0xff);
	X_BUF[2]=2;
	X_BUF[3]=De_AgreeOn_SendOrder_Answer_Yes;
	CN_st_Fun_AscNumber.MoveByte(X_BUF+4,IMEI,7);
	X_BUF[11]=0;
	X_BUF[12]=0;
	X_BUF[13]=0;
	X_BUF[14]=0;
	X_BUF[15]=((De_Dev_Order_GetSeverComPar->OrderID>>8)&0xff);
	X_BUF[16]=((De_Dev_Order_GetSeverComPar)&0xff);
	CN_st_Dev_Tzxy_Send.ResultOrSend=De_Tzxy_SendBuf_Send;
	CN_st_Dev_Tzxy_Send.SizeofBuf=DataLen+17;
   	CN_st_Dev_Tzxy_Send.Buf=X_BUF;
	if((Result=CN_st_Fun_Gprs.SendIP(fd,X_BUF,DataLen))!=De_Suc_Gprs)
		return Result;
	CN_st_Fun_RTC.Read(DateTimer);
	for(;;WatchDog())
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
{	const st_Affair_UDPTCP	CN_st_Affair_UDPTCP={NULL};
	uint16 Result;
	st_Data_UDPTCP	CN_st_Data_UDPTCP;
 	CN_st_Fun_AscNumber.ClsArray(&CN_st_Data_UDPTCP,sizeof(st_Data_UDPTCP));
   	CN_st_Data_UDPTCP.LinkType=De_Gprs_OpenLink_UDP;				//打开UDP链路
	CN_st_Data_UDPTCP.Com=Port;		 								//端口号
	if(ptst_Gprs_IP->DomainName[0]!=0) 			//域名有效
	{	if(CN_st_Fun_Gprs.DNSRIP(ptst_Gprs_IP->DomainName,&CN_st_Data_UDPTCP.IP)==De_Suc_Moderm)
		{	if(CN_st_Fun_Gprs.OpenUDPTCP(&CN_st_Data_UDPTCP,(st_Affair_UDPTCP	*)&CN_st_Affair_UDPTCP,fd)==De_Suc_Moderm)			
		  		return De_Suc_Login;
		} 	
	}
	if(ptst_Gprs_IP->IP==0)
		return De_Erro_Login_NoIP;
	CN_st_Data_UDPTCP.IP=ptst_Gprs_IP->IP;
	return CN_st_Fun_Gprs.OpenUDPTCP(&CN_st_Data_UDPTCP,(st_Affair_UDPTCP	*)&CN_st_Affair_UDPTCP,fd);
}

