#define De_FTP_Compiler
#include "FTP.h"

//初始化FTP
static uint16 Init(void)
{
	CN_st_Fun_AscNumber.ClsArray(&CN_FtpDown_Data,sizeof(st_FtpDown_Data)); 
	CN_FtpDown_Data.state = De_FTP_Operation_NoWork;   //置FTP空闲状态
	FtpQbox = OSQCreate(&MessegBox[0],De_Max_Messages);; 
	if(FtpQbox == NULL)
	{
		return De_Erro_FTP_Init;
	}	
	FtpCtrlSem = OSSemCreate(0); 
	CN_st_Link_Data.state = De_FTP_Link_Close;
    CN_st_Link_Ctrl.state = De_FTP_Link_Close; 	 
	FtpDownFlag = De_FTP_Down_Nofinish	;
	OSTaskCreate (FTP_Downloard_Task,(void *)0, &FTP_Stk[De_FTP_Stk - 1], De_FTP_Task);	//创建FTP下载任务	
	return De_Suc_FTP ;
} 


//初始化TCP链路，进行附着，如果应用层已经附着过则不能够附着
static uint16 InitTCPLink(void)
{
	st_Data_IPNet    Temp_IPnet; 
	uint8 *pApn       = "CMNET";
	uint8 *pUser      = "";
	uint8 *pPassword  = "";

	static uint8 step = 0;	 
	uint16  result;
	CN_st_Fun_AscNumber.ClsArray(&Temp_IPnet,sizeof(st_Data_IPNet));
	CN_st_Fun_AscNumber.MoveByte(&Temp_IPnet.APN,pApn,CN_st_Fun_AscNumber.Strsize(pApn));
	CN_st_Fun_AscNumber.MoveByte(&Temp_IPnet.Use,pUser,CN_st_Fun_AscNumber.Strsize(pUser));
	CN_st_Fun_AscNumber.MoveByte(&Temp_IPnet.PassWord,pPassword,CN_st_Fun_AscNumber.Strsize(pPassword));
	
	while(1)
	{
		result = CN_st_Fun_Gprs.InitGprs(&Temp_IPnet);
		if(result == De_Suc_FTP)
			return result;		
		CN_st_Fun_Uart.Write(0,"Init GPRS erro\r\n",CN_st_Fun_AscNumber.Strsize("Init GPRS erro\r\n"));
		if(step++>2)			  //连续初始化3次，超过3次则退出
		{
			step = 0;
			return De_Erro_FTP_InitTCPLink;					 //控制链路初始化失败
		} 			 		
	}	
}

 //初始化FTP链路
static uint16 FtpLinkOpen(uint32 ipaddress,uint16 port,st_Affair_UDPTCP	*ptst_Affair_UDPTCP,uint8 *fd)
{	
	st_Data_UDPTCP   TempFtpData_TCP;
	
	static uint8 step = 0;	 
	uint16  result;	  	

	CN_st_Fun_AscNumber.ClsArray(&TempFtpData_TCP,sizeof(st_Data_UDPTCP));

	TempFtpData_TCP.LinkType          = De_GprsHard_UDPTCP_TCP;     	      // 链路类型为TCP
	TempFtpData_TCP.IP                = ipaddress;	  // 链路的IP地址
	TempFtpData_TCP.Com               = port;		  // 链路的端口号
	TempFtpData_TCP.SelfHeartTimer    = 0;			  // 主机心跳时间为 0
	TempFtpData_TCP.CentrHeartTimer   = 0;			  // 中心心跳时间为	0
	TempFtpData_TCP.SelfHeartData[0]  = 0;			  // 主机心跳数据为空
	TempFtpData_TCP.HeartDataLength   = 0;			  // 心跳数据长度为	0
	TempFtpData_TCP.CentrHeartData[0] = 0;			  // 中心心跳数据为空
	TempFtpData_TCP.CentrHeartLength  = 0;			  // 中心心跳长度为 0

	while(1)
	{  		
		result = CN_st_Fun_Gprs.OpenIP(&TempFtpData_TCP,ptst_Affair_UDPTCP,fd);	  	
		if(result == De_Suc_FTP)
			return result; 		
		CN_st_Fun_Uart.Write(0,"Open TCP link erro\r\n",CN_st_Fun_AscNumber.Strsize("Open TCP link erro\r\n"));
		if(step++>2)	 //连续初始化3次，超过3次则退出
		{
			step = 0;
			return De_Erro_FTP_OpenCtrLink;					 //打开控制链路失败
		}
	}	
}

//控制链路接收事情
static void FTP_CtrReceive(uint8 *Data,uint8 fd,uint16 DataLength)
{ 		
	fd = fd;  
	if(CN_FtpDown_Data.state == De_FTP_Operation_Work)   //FTP下载状态
	{	CN_st_Fun_AscNumber.ClsArray(FTP_Cmd.DataBuf.buf,sizeof(un_FTP_Cmd));
		CN_st_Fun_AscNumber.MoveByte(FTP_Cmd.DataBuf.buf, Data, DataLength);  //
		CN_st_Fun_Uart.Write(0,FTP_Cmd.DataBuf.buf,DataLength); 
		OSSemPost(FtpCtrlSem);
	}			
	
}
		  
//数据链路接收事情
static void FTP_DataReceive(uint8 *Data,uint8 fd,uint16 DataLength)
{
	uint8  asciilen;
	uint8  buf[20];	 		
	

	fd = fd;	 
	if(CN_FtpDown_Data.state == De_FTP_Operation_Work)   //FTP下载状态
	{
		CN_FtpDown_Data.FileOffset   = CN_FtpDown_Data.DownFileLen ; 

		CN_st_Fun_File.WriteBin(CN_FTP_ID.FTP_File_Fd,CN_FtpDown_Data.FileOffset,DataLength,Data);	 //写入文件系统	

		
		CN_FtpDown_Data.DownFileLen += DataLength; 	 
						
		asciilen = CN_st_Fun_AscNumber.Algorism2Asc(CN_FtpDown_Data.DownFileLen,buf);								
		CN_st_Fun_Uart.Write(0,buf,asciilen);					
		CN_st_Fun_Uart.Write(0,"\r\n",2); 

		//更新记录文件				
		CN_st_Fun_File.Open("FileInforRecord",&CN_FTP_ID.FTP_Info_Fd);	
		CN_st_Fun_File.ReadRecoder(CN_FTP_ID.FTP_Info_Fd,0,&CN_st_UpFileInfor);	  //读取状态	
		CN_st_UpFileInfor.RevFileLen = CN_FtpDown_Data.DownFileLen;
		CN_st_Fun_File.WriteRecoder(CN_FTP_ID.FTP_Info_Fd,0,&CN_st_UpFileInfor); //将FTP参数和状态写入文件系统
		CN_st_Fun_File.Close(CN_FTP_ID.FTP_Info_Fd);
			
		//OSSemPost(FtpDataSem);
		FtpDown.type = De_FTP_DataLink;
		OSQPost(FtpQbox,(void*)&FtpDown);
	}   			
}

//判断服务器的回码是否正确
static uint16 JudgeAsk(uint8 *pAsk,uint8 len)
{	
	uint8  err;

	OSSemPend(FtpCtrlSem, OUTTIME*OS_TICKS_PER_SEC, &err);
	if(err == OS_NO_ERR)
	{
		if(CN_st_Fun_AscNumber.CompareBuf(FTP_Cmd.RevAsk.askcode,pAsk,len)== 0)
		{
			return De_Suc_FTP;		
		}
		return De_Erro_FTP_AskErro;	
	}
	else
	{
		CN_st_Fun_Uart.Write(0,"Ctrl link receive time out\r\n",CN_st_Fun_AscNumber.Strsize("Ctrl link receive time out\r\n")); 					
		return De_Erro_FTP_TimeOut;		 //数据接收超时	
	}
}

//发送FTP命令，并等待服务器应答
static uint16 FTP_SendCommand(const uint8 *pCmdName, uint8 *pCmdPara,uint8 *pAsk)
{
	uint8 buf[50];
	uint8 len;
	uint16 result;

   	CN_st_Fun_AscNumber.MoveByte(buf, (uint8 *)pCmdName,CN_st_Fun_AscNumber.Strsize((void *)pCmdName));
	len = CN_st_Fun_AscNumber.Strsize((uint8 *)pCmdName);
	buf[len] = 0x20;   //空格
	len += 1;
	CN_st_Fun_AscNumber.MoveByte(buf+len,pCmdPara,CN_st_Fun_AscNumber.Strsize(pCmdPara));
	len += CN_st_Fun_AscNumber.Strsize(pCmdPara);
	buf[len++] = '\r';
	buf[len++] = '\n';
	buf[len]   = '\0';    //结束符	
	if(CN_st_Fun_Gprs.SendIP(CN_st_Link_Ctrl.fd,buf,len) != De_Suc_FTP) 
		return De_Erro_FTP_SendCommand; 	  							//发送命令失败 	
	result = JudgeAsk(pAsk,3);	   //判断服务器应答
	return 	result;			
}

// 获取需要下载文件的长度
// 应答 150 Opening BINARY mode data connection for boot.bin (10852 Bytes)
static void GetFileLength(uint8 *pdata)
{
	uint8 *ps;
	uint8 *pt;
	uint8 len;
	uint8 buf[10];
	CN_st_Fun_AscNumber.ClsArray(buf,10);
	CN_FtpDown_Data.FileLength = 0;
	ps = pdata;
	ps = CN_st_Fun_AscNumber.LookStr("(",ps) ; 
	ps++;
	pt = CN_st_Fun_AscNumber.LookStr(" ",ps);
	len = pt-ps;
    CN_st_Fun_AscNumber.MoveByte(buf,ps,len);
	buf[len] = '\0';
	CN_FtpDown_Data.FileLength = CN_st_Fun_AscNumber.Asc2Algorism(buf,CN_st_Fun_AscNumber.Strsize(buf));  	
}

// 获取数据链路的通信参数
// 应答 227 Entering Passive Mode (221,231,140,211,7,202)
static void GetDataLinkPra(uint8 *pdata)
{
	uint8 *ps;
	uint8 *pt;
	uint8 buf[10];
	uint8 len;
	uint8 temp;
	uint8 i;

	CN_st_Fun_AscNumber.ClsArray(buf,10);
	CN_FtpDown_Data.DataLinkIpAdd = 0x00000000;
	CN_FtpDown_Data.DataLinkPort  = 0x0000;
	ps = pdata;
	ps = CN_st_Fun_AscNumber.LookStr("(",ps) ; 
	ps++;
	for(i=0;i<4;i++)   //计算IP地址
	{ 					
		pt = CN_st_Fun_AscNumber.LookStr(",",ps);
		len = pt - ps;		
		CN_st_Fun_AscNumber.MoveByte(buf,ps,len);
		buf[len] = '\0';
		temp = (uint8)CN_st_Fun_AscNumber.Asc2Algorism(buf,CN_st_Fun_AscNumber.Strsize(buf));
		CN_FtpDown_Data.DataLinkIpAdd += ((uint32)temp)<<(8*(3-i));
		ps = pt+1;
	}
	//计算端口号
	pt = CN_st_Fun_AscNumber.LookStr(",",ps);
	len = pt - ps;		
	CN_st_Fun_AscNumber.MoveByte(buf,ps,len);
	buf[len] = '\0';
	temp = (uint8)CN_st_Fun_AscNumber.Asc2Algorism(buf,CN_st_Fun_AscNumber.Strsize(buf)); 
	CN_FtpDown_Data.DataLinkPort += ((uint16)temp<<8);

	ps = pt+1;
	pt = CN_st_Fun_AscNumber.LookStr(")",ps);
	len = pt - ps;		
	CN_st_Fun_AscNumber.MoveByte(buf,ps,len);
	buf[len] = '\0';
	temp = (uint8)CN_st_Fun_AscNumber.Asc2Algorism(buf,CN_st_Fun_AscNumber.Strsize(buf)); 
	CN_FtpDown_Data.DataLinkPort += (uint16)temp;	
}



//数据链路接收数据
static uint16 RevFtpData(void)
{ 	
	uint16 result;
		 
	result = 1;

	if(CN_FtpDown_Data.FileLength == CN_FtpDown_Data.DownFileLen)
	{	
		CN_st_Fun_Uart.Write(0,"Form update is complete!\r\n",CN_st_Fun_AscNumber.Strsize("Form update is complete!\r\n"));	
		 				
		CN_st_Fun_File.Open("FileInforRecord",&CN_FTP_ID.FTP_Info_Fd);							
		CN_st_UpFileInfor.UpFlag = 1;  
		CN_st_UpFileInfor.TotalFileLen = CN_FtpDown_Data.FileLength;
		CN_st_Fun_File.WriteRecoder(CN_FTP_ID.FTP_Info_Fd,0,&CN_st_UpFileInfor); //将FTP参数和状态写入文件系统
		CN_st_Fun_File.Close(CN_FTP_ID.FTP_Info_Fd);
		
										
		result =  De_Suc_FTP;	 //下载完成
	}
	else if(CN_FtpDown_Data.DownFileLen > CN_FtpDown_Data.FileLength) //下载的文件长度错误
	{
		CN_FtpDown_Data.DownFileLen = 0;				//重新下载

		
		CN_st_Fun_File.Open("FileInforRecord",&CN_FTP_ID.FTP_Info_Fd);							
		CN_st_UpFileInfor.UpFlag = 0;
		CN_st_UpFileInfor.RevFileLen = 0;
		CN_st_UpFileInfor.TotalFileLen = 0;
		CN_st_Fun_File.WriteRecoder(CN_FTP_ID.FTP_Info_Fd,0,&CN_st_UpFileInfor); //将FTP参数和状态写入文件系统
		CN_st_Fun_File.Close(CN_FTP_ID.FTP_Info_Fd);
		

		CN_st_Fun_Uart.Write(0,"data length err\r\n",CN_st_Fun_AscNumber.Strsize("data length err\r\n")); 
		result =  De_Erro_FTP_RevWrong;	
	}
	return  result;		
		
}
//清除信号量
static uint16 ClearSem(OS_EVENT	*FTPSem)
{	
	OS_SEM_DATA 	SemData;
	uint8 err;
	for(;;)
	{	if(OSSemQuery(FTPSem, &SemData)!=OS_NO_ERR)
			return 1;
		if(SemData.OSCnt == 0)		
			return De_Suc_FTP;	
		OSSemPend(FTPSem, 1, &err);  
	}
}



//打开本地升级的文件，如果文件不存在则创建
static uint16 FTP_Open_File(void)
{
	uint16 result;

	result = CN_st_Fun_File.Open("FileInforRecord",&CN_FTP_ID.FTP_Info_Fd);
	if(result == De_Erro_File_NoFile)
	{
		CN_st_Fun_File.CreateRecoder("FileInforRecord",sizeof(CN_st_UpFileInfor),1,De_File_Property_Cycle);	// 创建记录文件，大小30个字节 
		CN_st_Fun_File.Open("FileInforRecord",&CN_FTP_ID.FTP_Info_Fd);
	}      	

	result = CN_st_Fun_File.Open(CN_FtpDown_Data.cn_FTP_Data.SaveFileName, &CN_FTP_ID.FTP_File_Fd);
	if(result == De_Erro_File_NoFile)
	{
		CN_st_Fun_File.CreateBin(CN_FtpDown_Data.cn_FTP_Data.SaveFileName,De_Max_FileSize);        // 创建二进制文件，文件大小200K 
		CN_st_Fun_File.Open(CN_FtpDown_Data.cn_FTP_Data.SaveFileName, &CN_FTP_ID.FTP_File_Fd);
	}
	return result;	
}
//将下载的文件填充0XFF
static uint16 FullSaveFile(void)
{
	uint16 i;
	uint32 Offset = 0  ; 
	
	for(i=0;i<512;i++)
		FTP_Cmd.DataBuf.buf[i] = 0xff;	
	for(i=0;i<De_Max_FileSize/512;i++)
	{ 		
		CN_st_Fun_File.WriteBin(CN_FTP_ID.FTP_File_Fd,Offset,512,FTP_Cmd.DataBuf.buf);	 //写入文件系统
		Offset += 512;	
	}	 	
	return 0; 
}

void InitDownload(st_FTP_Data *pFtpData)
{
	uint16 result,result1; 
	//char dbgbuf[100];
	uint8 *ps;
	uint8 *pt;
//	uint8 buf[10]; 

	CN_st_Fun_AscNumber.MoveByte((st_FTP_Data *)&CN_FtpDown_Data.cn_FTP_Data,pFtpData,sizeof(st_FTP_Data));
	ClearSem(FtpCtrlSem);  	
	FTP_Open_File(); 	//打开文件	 
	
	CN_st_Fun_AscNumber.ClsArray(&CN_st_UpFileInfor,sizeof(st_UpFileInfor));
	result = CN_st_Fun_File.ReadRecoder(CN_FTP_ID.FTP_Info_Fd,0,&CN_st_UpFileInfor);	  //读取状态
	result1 = CN_st_Fun_AscNumber.CompareBuf( CN_st_UpFileInfor.FileInfor.FileName,        		\
											 CN_FtpDown_Data.cn_FTP_Data.SaveFileName ,   		\
											 sizeof(CN_st_UpFileInfor.FileInfor.FileName));

	if((result == De_Erro_File_RecoderOut)||(result1 == 1))	  //需要存储的文件名和之前的不同或者无记录	
	{					
		CN_st_Fun_Uart.Write(0,"It's a new file\r\n",CN_st_Fun_AscNumber.Strsize("It's a new file\r\n"));	
		CN_st_Fun_AscNumber.MoveByte(CN_st_UpFileInfor.FileInfor.FileName,            \
									 CN_FtpDown_Data.cn_FTP_Data.SaveFileName,        \
									 CN_st_Fun_AscNumber.Strsize(CN_FtpDown_Data.cn_FTP_Data.SaveFileName));

		CN_st_UpFileInfor.RevFileLen = 0;      //清除已经下载的文件
        CN_st_UpFileInfor.TotalFileLen = 0;
	  	CN_st_Fun_File.WriteRecoder(CN_FTP_ID.FTP_Info_Fd,0,&CN_st_UpFileInfor); //将FTP参数和状态写入记录
		FullSaveFile();	   		
	}

	CN_st_Fun_AscNumber.ClsArray(DownloadFile,sizeof(DownloadFile));
	CN_st_Fun_AscNumber.ClsArray(DownloadDir,sizeof(DownloadDir));

	ps = CN_FtpDown_Data.cn_FTP_Data.FileDirName;
	pt = CN_st_Fun_AscNumber.LookStrDown("/",ps);
	if(pt == NULL)   //当前根目录
	{
		CN_st_Fun_AscNumber.MoveByte(DownloadDir,"/",1);
		CN_st_Fun_AscNumber.MoveByte(DownloadFile,CN_FtpDown_Data.cn_FTP_Data.FileDirName,sizeof(DownloadFile));		
	}
	else		 //  "/123/APP.GJ"
	{	
		*pt = 0;
		pt++;		
		CN_st_Fun_AscNumber.MoveByte(DownloadDir,ps,CN_st_Fun_AscNumber.Strsize(ps));
		CN_st_Fun_AscNumber.MoveByte(DownloadFile,pt,CN_st_Fun_AscNumber.Strsize(pt));	
	}											 												 

    CN_st_Fun_File.Close(CN_FTP_ID.FTP_Info_Fd); //关闭文件	
	CN_FtpDown_Data.state = De_FTP_Operation_Work;   //置FTP下载状态
    

	//调试信息
	/*	
	sprintf(dbgbuf,"Have save fileName is: %s\r\n",CN_st_UpFileInfor.FileInfor.FileName);
	CN_st_Fun_Uart.Write(0,(uint8 *)dbgbuf,CN_st_Fun_AscNumber.Strsize((uint8 *)dbgbuf));	

	sprintf(dbgbuf,"Have save upFlag is: %d\r\n",CN_st_UpFileInfor.UpFlag);
	CN_st_Fun_Uart.Write(0,(uint8 *)dbgbuf,CN_st_Fun_AscNumber.Strsize((uint8 *)dbgbuf));
	
	sprintf(dbgbuf,"Have save revFileLen is: %ld\r\n",CN_st_UpFileInfor.RevFileLen);
	CN_st_Fun_Uart.Write(0,(uint8 *)dbgbuf,CN_st_Fun_AscNumber.Strsize((uint8 *)dbgbuf));	
	*/		
}


static uint16 SendCtrCmd(void)
{
    uint16 result;
    uint8  buf[20];	 	

    for(;;)
    {  				
        if((result =JudgeAsk("220",3))!= De_Suc_FTP)break; 

        result = FTP_SendCommand(pUser_CMD,CN_FtpDown_Data.cn_FTP_Data.LoginName,"331");		// 输入用户登录名 				
        if(result != De_Suc_FTP) break;	  
		                 
        result = FTP_SendCommand(pPass_CMD,CN_FtpDown_Data.cn_FTP_Data.LoginPassword,"230");	// 输入用户登录密码			
        if(result != De_Suc_FTP) break;	 
		
		result = FTP_SendCommand(pCwd_CMD,DownloadDir,"250");
		if(result != De_Suc_FTP) break;	 
		                                             
        result = FTP_SendCommand(pPasv_CMD,"","227");		  // 设置被动模式 			
        if(result != De_Suc_FTP) break;	

        GetDataLinkPra(FTP_Cmd.RevAsk.askmsg);		  // 从返回的消息中获取数据链路的IP地址和端口号
        FTP_SendCommand(pType_CMD,"I","230");	  	  // 设置文件类型 			
        if(result != De_Suc_FTP) break;	  
		                      
        result = FtpLinkOpen(CN_FtpDown_Data.DataLinkIpAdd, CN_FtpDown_Data.DataLinkPort,   \
                            (st_Affair_UDPTCP *)&DataLink_Affair_TCP,&CN_st_Link_Data.fd);	//打开数据链路
        if(result != De_Suc_FTP) break;	
        CN_st_Link_Data.state = De_FTP_Link_Open;
		                 
        CN_st_Fun_AscNumber.ClsArray(buf,20); 
        	
        CN_st_Fun_AscNumber.Algorism2Asc(CN_st_UpFileInfor.RevFileLen,buf);	
        result = FTP_SendCommand(pRest_CMD,buf,"350");	 		//打开数据链路,并设置续传地址 			
        if(result != De_Suc_FTP) break;	
			                   
        result = FTP_SendCommand(pRetr_CMD,DownloadFile,"150"); //开始下载文件				
        if(result != De_Suc_FTP) break;	 
		 						 
        GetFileLength(FTP_Cmd.RevAsk.askmsg); 
		break;
    }
    return result;    
}

static void QuitFtp(uint16 result)
{
	
	TimeCount = 0;	
	ClearSem(FtpCtrlSem); 
    if(CN_st_Link_Ctrl.state == De_FTP_Link_Open)
    {
        CN_st_Fun_Gprs.CloseIP(CN_st_Link_Ctrl.fd);
		CN_st_Link_Ctrl.state = De_FTP_Link_Close;
    }
	 if(CN_st_Link_Data.state == De_FTP_Link_Open)
    {
        CN_st_Fun_Gprs.CloseIP(CN_st_Link_Data.fd);
		CN_st_Link_Data.state = De_FTP_Link_Close;
    }								
	CN_FtpDown_Data.state = De_FTP_Operation_NoWork;   //置FTP空闲状态 
		 			
	CN_st_Fun_File.Close(CN_FTP_ID.FTP_File_Fd);					
	
	pFtpBox->Result = result;				
	OSQPost(pFtpBox->LocalBox,&pFtpBox->Result); 	
}


//FTP下载任务
static void FTP_Downloard_Task(void *pData)	 
{ 
	st_FTP_Data *pFtpData;	  	
	void  *pBox;	
	uint8  err;		
	uint16 result;

	pData = pData;
	TimeCount = 0;
	for(;;) 
	{ 	
		WatchDog();				
		pBox = OSQPend(FtpQbox,TimeCount,&err);	 		
		pFtpData = (st_FTP_Data *)pBox;	  
		if(err != OS_NO_ERR)	  //超时
		{
			CN_st_Fun_Uart.Write(0,"Datalink timeout\r\n",CN_st_Fun_AscNumber.Strsize("Datalink timeout\r\n")); 						
			
			QuitFtp(De_Erro_FTP_TimeOut);  
						 
			continue; 	
		}
		 
		if(pFtpData->type == De_FTP_StartCmd) 
		{	pFtpBox  = pFtpData;
            InitDownload(pFtpData);
			if(TimeCount != 0)
			{
				if(CN_st_Link_Ctrl.state == De_FTP_Link_Open)
			    {
			        CN_st_Fun_Gprs.CloseIP(CN_st_Link_Ctrl.fd);
					CN_st_Link_Ctrl.state = De_FTP_Link_Close;
			    }
				 if(CN_st_Link_Data.state == De_FTP_Link_Open)
			    {
			        CN_st_Fun_Gprs.CloseIP(CN_st_Link_Data.fd);
					CN_st_Link_Data.state = De_FTP_Link_Close;
			    }	
			}
			   		
			TimeCount = OUTTIME*OS_TICKS_PER_SEC;
		}
        else if(pFtpData->type == De_FTP_DataLink)
		{
		 	result = RevFtpData();
			if(result == De_Suc_FTP)
			{	 				
				if(FtpDownFlag == De_FTP_Down_Nofinish)
				{
					CN_st_Fun_Uart.Write(0,"Quit Ftp!\r\n",CN_st_Fun_AscNumber.Strsize("Quit Ftp!\r\n"));
					FtpDownFlag = De_FTP_Down_Finish;
					QuitFtp(result);		
				}
			}			
			continue;
		}
									
		result = InitTCPLink();	   
		result = FtpLinkOpen(CN_FtpDown_Data.cn_FTP_Data.CtrLinkIpAdd,                              \
							CN_FtpDown_Data.cn_FTP_Data.CtrLinkPort,  								\
				 			(st_Affair_UDPTCP *)&CtrLink_Affair_TCP,&CN_st_Link_Ctrl.fd);						//打开控制链路
		if(result == De_Suc_FTP)
		{ 	
            CN_st_Link_Ctrl.state = De_FTP_Link_Open;
            result = SendCtrCmd();	
            if(result == De_Suc_FTP)
			{
				if(CN_FtpDown_Data.FileLength > CN_st_UpFileInfor.RevFileLen) 
					continue;   	 					
			}
		}
		if(FtpDownFlag == De_FTP_Down_Nofinish)
		{	FtpDownFlag = De_FTP_Down_Finish;
			QuitFtp(result); 	
		} 		
	}		
}


 //获取当前的工作状态
static uint16 GetState(st_FTP_WorkState	*ptst_FTP_WorkState)
{
    ptst_FTP_WorkState->FileLen       = CN_FtpDown_Data.FileLength;   // 文件长度
    ptst_FTP_WorkState->DownLoaderLen = CN_FtpDown_Data.DownFileLen;  // 已经下载的文件长度
	ptst_FTP_WorkState->State         = CN_FtpDown_Data.state;		  // 当前状态
    CN_st_Fun_AscNumber.MoveByte((st_FTP_Data*)&ptst_FTP_WorkState->cn_FTP_Data,(st_FTP_Data*)&CN_FtpDown_Data.cn_FTP_Data,sizeof(st_FTP_Data));	
	return De_Suc_FTP;
}


