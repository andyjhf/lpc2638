#define De_FTP_Compiler
#include "FTP.h"
static uint16 Init(void)
{	uint16 result;
	st_FTP_Recoder CN_st_FTP_Recoder;
	CN_st_Fun_AscNumber.ClsArray(&CN_st_Buf_rwFlash,sizeof(CN_st_Buf_rwFlash)); 
	FtpQbox = OSQCreate(&MessegBox[0],De_Max_Messages); 
	if(FtpQbox == NULL)
		return De_Erro_FTP_Init;	
	FtpCtrlSem = OSMboxCreate(NULL); 
	CN_st_Ftp_RunState.DownState=De_FTP_Operation_Idle;
	CN_st_Ftp_RunState.CN_st_Ftp_Link_Data.State = De_FTP_Link_Close;
    CN_st_Ftp_RunState.CN_st_Ftp_Link_Ctrl.State = De_FTP_Link_Close; 
	CN_st_Ftp_RunState.DownFileState=De_FTP_Down_Nofinish;	 
	CN_st_Buf_rwFlash.DataLength=0;
	CN_st_Ftp_RunState.TimeOut=0;
	result=CN_st_Fun_File.Open(De_FileName_FTP,&FTPRecoderFd);
	if(result == De_Erro_File_NoFile)
	{	CN_st_Fun_File.CreateRecoder(De_FileName_FTP,sizeof(st_FTP_Recoder),1,De_File_Property_Cycle);
		CN_st_Fun_File.Open(De_FileName_FTP,&FTPRecoderFd);
		CN_st_FTP_Recoder.UpFlag=1;
		CN_st_Fun_File.WriteRecoder(FTPRecoderFd,0,&CN_st_FTP_Recoder);	
	}
	OSTaskCreate (Task,(void *)0, &FTP_Stk[De_Ftp_Stk - 1], De_Ftp_Task);	//创建FTP下载任务	
	return De_Suc_FTP ;
}
static void Task(void *pdata)
{	uint8 err;
	uint16 Result;
	pdata=pdata;
	for(;;WatchDog())
	{	ptst_FTP_Data_Temp = OSQPend(FtpQbox,CN_st_Ftp_RunState.TimeOut,&err);
		if(err != OS_NO_ERR)
		{	FtpClose();
//			CN_st_Fun_Uart.Write(0,"DownTimeout\r\n",13);
			CN_st_Ftp_RunState.TimeOut=0;
			ptst_FTP_Data_Save->Result = De_Erro_FTP_TimeOut;
			CN_st_Ftp_RunState.DownState = De_FTP_Operation_Idle;				
			OSQPost(ptst_FTP_Data_Save->LocalBox,&ptst_FTP_Data_Save->Result);
			continue; 	
		}
		ptRecData_Type = (uint8 *)ptst_FTP_Data_Temp;
		if(*ptRecData_Type==De_FTP_StartCmd)
		{	ptst_FTP_Data_Save=ptst_FTP_Data_Temp;
			CN_st_Ftp_RunState.TimeOut=30*OS_TICKS_PER_SEC;	
			ClearSem(FtpCtrlSem);
			FtpClose();
			Result=FTP_File_Init();
			if(Result==De_Erro_FTP_Finish)
			{	CN_st_Ftp_RunState.TimeOut=0;
				FtpClose();
				ClearQ(FtpQbox);
				ptst_FTP_Data_Save->Result = 0;
//				CN_st_Fun_Uart.Write(0,"DownReOk\r\n",10);
				CN_st_Ftp_RunState.DownState = De_FTP_Operation_Idle;				
				OSQPost(ptst_FTP_Data_Save->LocalBox,&ptst_FTP_Data_Save->Result);
				continue;
			}
			CN_st_Ftp_RunState.DownState=De_FTP_Operation_Work;
			if((Result=LogOnFtpServer(&CN_st_Ftp_RunState,ptst_FTP_Data_Save,(st_Affair_Ftp *)&CN_st_Affair_Ftp,(st_Ftp_CMD *)&CN_st_Ftp_CMD))!=De_Suc_FTP)
			{	CN_st_Ftp_RunState.TimeOut=0;
				FtpClose();
				ClearQ(FtpQbox);
				ptst_FTP_Data_Save->Result = Result;
				CN_st_Ftp_RunState.DownState = De_FTP_Operation_Idle;				
				OSQPost(ptst_FTP_Data_Save->LocalBox,&ptst_FTP_Data_Save->Result);	
			}
		}
		else if(*ptRecData_Type==De_FTP_DataLink)
 		{	Result=RevFtpData();
			if(Result==De_Suc_FTP)
			{	CN_st_Ftp_RunState.TimeOut=0;
				FtpClose();
				ClearQ(FtpQbox);
//				CN_st_Fun_Uart.Write(0,"DownOk\r\n",8);
				ptst_FTP_Data_Save->Result = Result;				
				OSQPost(ptst_FTP_Data_Save->LocalBox,&ptst_FTP_Data_Save->Result);
				CN_st_Ftp_RunState.DownState = De_FTP_Operation_Idle;	
			}
			else if(Result==De_Erro_FTP_RevWrong)
			{	CN_st_Ftp_RunState.TimeOut=0;
				CN_st_Ftp_RunState.DownFileState=De_FTP_Down_Nofinish;
				FtpClose();
				ClearQ(FtpQbox);
				ptst_FTP_Data_Save->Result = Result;
				CN_st_Ftp_RunState.DownState = De_FTP_Operation_Idle;				
				OSQPost(ptst_FTP_Data_Save->LocalBox,&ptst_FTP_Data_Save->Result);	
			}
				
		}
	}
}
static uint16 FtpClose(void)
{	uint16 Result;
	if(CN_st_Ftp_RunState.CN_st_Ftp_Link_Ctrl.State==De_FTP_Link_Open)
    {  	CN_st_Fun_Gprs.CloseIP(CN_st_Ftp_RunState.CN_st_Ftp_Link_Ctrl.Fd);
		CN_st_Ftp_RunState.CN_st_Ftp_Link_Ctrl.State = De_FTP_Link_Close;
    }
	 if(CN_st_Ftp_RunState.CN_st_Ftp_Link_Data.State==De_FTP_Link_Open)
    {   CN_st_Fun_Gprs.CloseIP(CN_st_Ftp_RunState.CN_st_Ftp_Link_Data.Fd);	
		CN_st_Ftp_RunState.CN_st_Ftp_Link_Data.State = De_FTP_Link_Close;
    }								
	CN_st_Ftp_RunState.DownState = De_FTP_Operation_Idle;   //置FTP空闲状态
	CN_st_Fun_DownFile.Close(DownFileFd); 
	return De_Suc_FTP;
}
static uint16 FTP_File_Init(void)
{	uint16 DataLength,DataLength1,result;
	st_DownFile_Infor CN_st_DownFile_Infor;
	st_FTP_Recoder CN_st_FTP_Recoder;
	CN_st_Buf_rwFlash.DataLength=0;
	result=CN_st_Fun_DownFile.Open(ptst_FTP_Data_Save->SaveFileName,&DownFileFd);
	if(result == De_Erro_File_NoFile)
	{	CN_st_Fun_DownFile.CreateFile(ptst_FTP_Data_Save->SaveFileName,De_Max_FileSize);
		CN_st_Fun_DownFile.Open(ptst_FTP_Data_Save->SaveFileName,&DownFileFd);	
	}
	CN_st_Fun_DownFile.GetFileProperty(DownFileFd,&CN_st_DownFile_Infor);
	DataLength=CN_st_Fun_AscNumber.Strsize(CN_st_DownFile_Infor.FileName);
	DataLength1=CN_st_Fun_AscNumber.Strsize(ptst_FTP_Data_Save->FileDirName);
	if((DataLength!=DataLength1)||((result=CN_st_Fun_AscNumber.CompareBuf(CN_st_DownFile_Infor.FileName,ptst_FTP_Data_Save->FileDirName,DataLength1))!=0))
	{	CN_st_Fun_DownFile.CleanProperty(DownFileFd);
		CN_st_Fun_DownFile.SetFileName(DownFileFd,ptst_FTP_Data_Save->FileDirName);
		CN_st_Fun_DownFile.GetFileProperty(DownFileFd,&CN_st_DownFile_Infor);			
	}
	if((CN_st_DownFile_Infor.RevFileLen == CN_st_DownFile_Infor.TotalFileLen)&&(CN_st_DownFile_Infor.TotalFileLen!=0))
	{	
//		CN_st_Fun_Uart.Write(0,"Form update is complete1!\r\n",CN_st_Fun_AscNumber.Strsize("Form update is complete1!\r\n"));	 													
		CN_st_FTP_WorkState.FileLen = CN_st_DownFile_Infor.TotalFileLen;
		CN_st_FTP_WorkState.DownLoaderLen = CN_st_DownFile_Infor.RevFileLen;
		return De_Erro_FTP_Finish;
	}
	CN_st_Fun_AscNumber.ClsArray(&CN_st_FTP_Recoder,sizeof(st_FTP_Recoder));
	CN_st_FTP_Recoder.CtrLinkIpAdd=ptst_FTP_Data_Save->CtrLinkIpAdd;
	CN_st_FTP_Recoder.CtrLinkPort=ptst_FTP_Data_Save->CtrLinkPort;
	CN_st_Fun_AscNumber.MoveByte(CN_st_FTP_Recoder.LoginName,ptst_FTP_Data_Save->LoginName,CN_st_Fun_AscNumber.Strsize(ptst_FTP_Data_Save->LoginName));
	CN_st_Fun_AscNumber.MoveByte(CN_st_FTP_Recoder.LoginPassword,ptst_FTP_Data_Save->LoginPassword,CN_st_Fun_AscNumber.Strsize(ptst_FTP_Data_Save->LoginPassword));
	CN_st_Fun_AscNumber.MoveByte(CN_st_FTP_Recoder.FileDirName,ptst_FTP_Data_Save->FileDirName,CN_st_Fun_AscNumber.Strsize(ptst_FTP_Data_Save->FileDirName));
	CN_st_Fun_AscNumber.MoveByte(CN_st_FTP_Recoder.SaveFileName,ptst_FTP_Data_Save->SaveFileName,CN_st_Fun_AscNumber.Strsize(ptst_FTP_Data_Save->SaveFileName));
	CN_st_FTP_Recoder.UpFlag=0;
	CN_st_Fun_File.WriteRecoder(FTPRecoderFd,0,&CN_st_FTP_Recoder);	  
	CN_st_FTP_WorkState.FileLen = CN_st_DownFile_Infor.TotalFileLen;
	CN_st_FTP_WorkState.DownLoaderLen = CN_st_DownFile_Infor.RevFileLen;
	return De_Suc_FTP;
}
static uint16 LogOnFtpServer(st_Ftp_RunState *ptst_Ftp_RunState,st_FTP_Data *ptst_FTP_Data,st_Affair_Ftp *ptst_Affair_Ftp,st_Ftp_CMD *ptst_Ftp_CMD)
{	uint16 Result;
	uint32  RecCtrlData1;
	st_Data_UDPTCP CN_st_Data_UDPTCP;
	//const st_Data_IPNet CN_st_Data_IPNet={"CMNET","",""};
	//if((Result=CN_st_Fun_Gprs.InitGprs((st_Data_IPNet *)&CN_st_Data_IPNet))!=De_Suc_Gprs)
	//	return Result;
	CN_st_Fun_AscNumber.ClsArray(&CN_st_Data_UDPTCP,sizeof(st_Data_UDPTCP));
	CN_st_Data_UDPTCP.LinkType          = De_GprsHard_UDPTCP_TCP;     	      // 链路类型为TCP
	CN_st_Data_UDPTCP.IP                = ptst_FTP_Data->CtrLinkIpAdd;	  // 链路的IP地址
	CN_st_Data_UDPTCP.Com               = ptst_FTP_Data->CtrLinkPort;		  // 链路的端口号
	if((Result=CN_st_Fun_Gprs.OpenIP(&CN_st_Data_UDPTCP,(st_Affair_UDPTCP *)&ptst_Affair_Ftp->CN_st_Affair_UDPTCP_Ctrl,&ptst_Ftp_RunState->CN_st_Ftp_Link_Ctrl.Fd))!=De_Suc_Gprs)
		return Result;
	ptst_Ftp_RunState->CN_st_Ftp_Link_Ctrl.State = De_FTP_Link_Open; 
//	CN_st_Fun_DownFile.ReadFile(DownFileFd,&CN_st_Ftp_UpFileInfor,0,0,0);
	if((Result=JudgeFtpAsk("220",&RecCtrlData1))!= De_Suc_FTP)								//
		return Result;
	if((Result=FtpConfig(ptst_Affair_Ftp,ptst_Ftp_RunState,ptst_FTP_Data,ptst_Ftp_CMD))!= De_Suc_FTP)
		return Result;	
	return Result;
}
static uint16 FtpConfig(st_Affair_Ftp *ptst_Affair_Ftp,st_Ftp_RunState *ptst_Ftp_RunState,st_FTP_Data *ptst_FTP_Data,st_Ftp_CMD *ptst_Ftp_CMD)
{	uint16 Result;
	st_Data_UDPTCP CN_st_Data_UDPTCP;
	uint32 FileLength;
	uint8  DownloadFile[32]; 	
	uint8  DownloadDir[150];
	uint32  RecCtrlData;
	st_DownFile_Infor CN_st_DownFile_Infor;
	CN_st_Fun_AscNumber.ClsArray(DownloadFile,sizeof(DownloadFile));
	CN_st_Fun_AscNumber.ClsArray(DownloadDir,sizeof(DownloadDir));
	CN_st_Fun_AscNumber.ClsArray(&CN_st_Data_UDPTCP,sizeof(st_Data_UDPTCP));
	GetFileNameDir(DownloadFile,DownloadDir,ptst_FTP_Data);
	if((Result=FTP_SendCommand(ptst_Ftp_CMD->pUser_CMD,ptst_FTP_Data->LoginName,"331",&RecCtrlData))!=De_Suc_FTP)
		return Result;
	if((Result=FTP_SendCommand(ptst_Ftp_CMD->pPass_CMD,ptst_FTP_Data->LoginPassword,"230",&RecCtrlData))!=De_Suc_FTP)
		return Result;
	if((Result=FTP_SendCommand(ptst_Ftp_CMD->pCwd_CMD,DownloadDir,"250",&RecCtrlData))!=De_Suc_FTP)
		return Result;
	if((Result=FTP_SendCommand(ptst_Ftp_CMD->pPasv_CMD,"","227",&RecCtrlData))!=De_Suc_FTP)
		return Result;
	GetDataLinkPra((uint8 *)RecCtrlData,&CN_st_Data_UDPTCP);
	if((Result=FTP_SendCommand(ptst_Ftp_CMD->pType_CMD,"I","200",&RecCtrlData))!=De_Suc_FTP)
		return Result;
	if((Result=CN_st_Fun_Gprs.OpenIP(&CN_st_Data_UDPTCP,(st_Affair_UDPTCP *)&ptst_Affair_Ftp->CN_st_Affair_UDPTCP_Data,&ptst_Ftp_RunState->CN_st_Ftp_Link_Data.Fd))!=De_Suc_Gprs)
		return Result;
	ptst_Ftp_RunState->CN_st_Ftp_Link_Data.State = De_FTP_Link_Open;
	CN_st_Fun_AscNumber.ClsArray(DownloadDir,150);
	CN_st_Fun_DownFile.GetFileProperty(DownFileFd,&CN_st_DownFile_Infor); 	
    CN_st_Fun_AscNumber.Algorism2Asc(CN_st_DownFile_Infor.RevFileLen,DownloadDir);
	if((Result=FTP_SendCommand(ptst_Ftp_CMD->pRest_CMD,DownloadDir,"350",&RecCtrlData))!=De_Suc_FTP)
		return Result; 
	if((Result=FTP_SendCommand(ptst_Ftp_CMD->pRetr_CMD,DownloadFile,"150",&RecCtrlData))!=De_Suc_FTP)
		return Result;
	if(CN_st_DownFile_Infor.TotalFileLen==0)
	{	GetFileLength((uint8 *)RecCtrlData,&CN_st_DownFile_Infor.TotalFileLen);
		CN_st_Fun_DownFile.SetFileLength(DownFileFd,CN_st_DownFile_Infor.TotalFileLen);		
	}	
	return De_Suc_FTP; 
}
static uint16 GetFileNameDir(uint8 *FileName,uint8 *FileDir,st_FTP_Data *ptst_FTP_Data)
{	uint8 *ps,*pt;
	ps = ptst_FTP_Data->FileDirName;
	pt = CN_st_Fun_AscNumber.LookStrDown("/",ps);
	if(pt == NULL)   //当前根目录
	{	CN_st_Fun_AscNumber.MoveByte(FileDir,"/",1);
		CN_st_Fun_AscNumber.MoveByte(FileName,ptst_FTP_Data->FileDirName,CN_st_Fun_AscNumber.Strsize(pt));		
	}
	else		 //  "/123/APP.GJ"
	{	//*pt = 0;
		pt++;
		CN_st_Fun_AscNumber.MoveByte(FileName,pt,CN_st_Fun_AscNumber.Strsize(pt));		
		CN_st_Fun_AscNumber.MoveByte(FileDir,ps,pt-ps-1);		
	}
	return De_Suc_FTP;
}
//发送FTP命令，并等待服务器应答
static uint16 FTP_SendCommand(const uint8 *pCmdName, uint8 *pCmdPara,uint8 *pAsk,uint32 *AskData)
{	uint8 buf[50];
	uint8 len;
	uint16 result;
   	CN_st_Fun_AscNumber.MoveByte(buf, (uint8 *)pCmdName,CN_st_Fun_AscNumber.Strsize((void *)pCmdName));
	len = CN_st_Fun_AscNumber.Strsize((uint8 *)pCmdName);
	buf[len] = 0x20;   																					//空格
	len += 1;
	CN_st_Fun_AscNumber.MoveByte(buf+len,pCmdPara,CN_st_Fun_AscNumber.Strsize(pCmdPara));
	len += CN_st_Fun_AscNumber.Strsize(pCmdPara);
	buf[len++] = '\r';
	buf[len++] = '\n';
	buf[len]   = '\0';    																				//结束符	
	if(CN_st_Fun_Gprs.SendIP(CN_st_Ftp_RunState.CN_st_Ftp_Link_Ctrl.Fd,buf,len) != De_Suc_FTP) 
		return De_Erro_FTP_SendCommand; 	  															//发送命令失败 	
	result=JudgeFtpAsk(pAsk,AskData);	   																		//判断服务器应答
	return 	result;			
}
/*static uint16 JudgeFtpAsk(uint8 *pAsk,uint32 *AskData)
{	uint8  err;
	uint8 *temp;
	temp=OSMboxPend(FtpCtrlSem, 20*OS_TICKS_PER_SEC, &err);
	if(err == OS_NO_ERR)
	{	*AskData=(uint32)temp;
		if(CN_st_Fun_AscNumber.CompareBuf(temp,pAsk,CN_st_Fun_AscNumber.Strsize((void *)pAsk))== 0)
			return De_Suc_FTP;		
		return De_Erro_FTP_AskErro;	
	}
	else
	{	CN_st_Fun_Uart.Write(0,"Ctrl link receive time out\r\n",CN_st_Fun_AscNumber.Strsize("Ctrl link receive time out\r\n")); 					
		return De_Erro_FTP_TimeOut;		 															//数据接收超时	
	}
}		  */
static uint16 JudgeFtpAsk(uint8 *pAsk,uint32 *AskData)
{	uint8  err;
	uint8 **temp;
	temp=OSMboxPend(FtpCtrlSem, 20*OS_TICKS_PER_SEC, &err);
	if(err == OS_NO_ERR)
	{	*AskData=(uint32)(*temp);
		if(CN_st_Fun_AscNumber.CompareBuf(*temp,pAsk,CN_st_Fun_AscNumber.Strsize((void *)pAsk))== 0)
			return De_Suc_FTP;		
		return De_Erro_FTP_AskErro;	
	}
	else
	{	//CN_st_Fun_Uart.Write(0,"Ctrl link receive time out\r\n",CN_st_Fun_AscNumber.Strsize("Ctrl link receive time out\r\n")); 					
		return De_Erro_FTP_TimeOut;		 															//数据接收超时	
	}
}
static void GetDataLinkPra(uint8 *pdata,st_Data_UDPTCP *ptst_Data_UDPTCP)
{
	uint8 *ps;
	uint8 *pt;
	uint8 buf[10];
	uint8 len;
	uint8 temp;
	uint8 i;
	ptst_Data_UDPTCP->LinkType          = De_GprsHard_UDPTCP_TCP;     	      // 链路类型为TCP
	CN_st_Fun_AscNumber.ClsArray(buf,10);
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
		ptst_Data_UDPTCP->IP += ((uint32)temp)<<(8*(3-i));
		ps = pt+1;
	}
	//计算端口号
	pt = CN_st_Fun_AscNumber.LookStr(",",ps);
	len = pt - ps;		
	CN_st_Fun_AscNumber.MoveByte(buf,ps,len);
	buf[len] = '\0';
	temp = (uint8)CN_st_Fun_AscNumber.Asc2Algorism(buf,CN_st_Fun_AscNumber.Strsize(buf)); 
	ptst_Data_UDPTCP->Com += ((uint16)temp<<8);
	ps = pt+1;
	pt = CN_st_Fun_AscNumber.LookStr(")",ps);
	len = pt - ps;		
	CN_st_Fun_AscNumber.MoveByte(buf,ps,len);
	buf[len] = '\0';
	temp = (uint8)CN_st_Fun_AscNumber.Asc2Algorism(buf,CN_st_Fun_AscNumber.Strsize(buf)); 
	ptst_Data_UDPTCP->Com += (uint16)temp;	
}
// 获取需要下载文件的长度
// 应答 150 Opening BINARY mode data connection for boot.bin (10852 Bytes)
static void GetFileLength(uint8 *pdata,uint32 *FileLength)
{
	uint8 *ps;
	uint8 *pt;
	uint8 len;
	uint8 buf[10];
	CN_st_Fun_AscNumber.ClsArray(buf,10);
	ps = pdata;
	ps = CN_st_Fun_AscNumber.LookStr("(",ps) ; 
	ps++;
	pt = CN_st_Fun_AscNumber.LookStr(" ",ps);
	len = pt-ps;
    CN_st_Fun_AscNumber.MoveByte(buf,ps,len);
	buf[len] = '\0';
	*FileLength = CN_st_Fun_AscNumber.Asc2Algorism(buf,CN_st_Fun_AscNumber.Strsize(buf));  	
} 
static uint16 RevFtpData(void)
{ 	uint16 result;
	st_DownFile_Infor CN_st_DownFile_Infor;	 
	result = 1;
	CN_st_Fun_DownFile.GetFileProperty(DownFileFd,&CN_st_DownFile_Infor); 
	if(CN_st_DownFile_Infor.RevFileLen == CN_st_DownFile_Infor.TotalFileLen)
	{	
//		CN_st_Fun_Uart.Write(0,"Form update is complete!\r\n",CN_st_Fun_AscNumber.Strsize("Form update is complete!\r\n"));		
		result =  De_Suc_FTP;	 //下载完成
	}
	else if(CN_st_DownFile_Infor.RevFileLen > CN_st_DownFile_Infor.TotalFileLen) //下载的文件长度错误
	{	CN_st_Fun_DownFile.CleanProperty(DownFileFd);
//		CN_st_Fun_Uart.Write(0,"data length err\r\n",CN_st_Fun_AscNumber.Strsize("data length err\r\n")); 
		result =  De_Erro_FTP_RevWrong;	
	}
	return  result;		
		
}
//控制链路接收事情
static void FTP_CtrReceive(uint8 *Data,uint8 fd,uint16 DataLength)
{ 		
	fd = fd;  
	if(CN_st_Ftp_RunState.DownState == De_FTP_Operation_Work)   //FTP下载状态
	{	CN_Data=Data;
		Data[DataLength]=0;
//		CN_st_Fun_Uart.Write(0,Data,DataLength);
		OSMboxPost(FtpCtrlSem,&CN_Data);
	}				
}
//数据链路接收事情
static void FTP_DataReceive(uint8 *Data,uint8 fd,uint16 DataLength)
{	uint16 j,DataLen,Offset;
	uint32 i;
	uint8 Buf[20],LinkState;
	st_DownFile_Infor CN_st_DownFile_Infor;
	st_FTP_Recoder CN_st_FTP_Recoder;	 		
	fd = fd;
	if(CN_st_Ftp_RunState.DownState!=De_FTP_Operation_Work)
		return ;	
	if(CN_st_Fun_Gprs.GetCurIPState(fd,&LinkState)!=De_Suc_Gprs)
	{	CN_st_Ftp_RunState.DownState=De_FTP_Operation_Idle;
		return ; 
	}
	CN_st_Fun_DownFile.GetFileProperty(DownFileFd,&CN_st_DownFile_Infor);	
	if(LinkState!=De_GprsHard_Link_Open)
	{	if((CN_st_DownFile_Infor.RevFileLen+DataLength+CN_st_Buf_rwFlash.DataLength)
		!=CN_st_DownFile_Infor.TotalFileLen)
		{	CN_st_Ftp_RunState.DownState=De_FTP_Operation_Idle;
			return;
		}
	}
	for(j=0;;)
	{	DataLen=DataLength+CN_st_Buf_rwFlash.DataLength;
		if(DataLen>=512)
			DataLen=512;
		if((DataLen==512)||((CN_st_DownFile_Infor.RevFileLen+DataLen)==CN_st_DownFile_Infor.TotalFileLen))
		{	CN_st_Fun_AscNumber.MoveByte(CN_st_Buf_rwFlash.Buf+CN_st_Buf_rwFlash.DataLength,
			Data+j,DataLen-CN_st_Buf_rwFlash.DataLength);
			j=j+(DataLen-CN_st_Buf_rwFlash.DataLength);
			DataLength=DataLength-(DataLen-CN_st_Buf_rwFlash.DataLength);
			CN_st_Buf_rwFlash.DataLength=0;
//			CN_st_Fun_Uart.Write(3,CN_st_Buf_rwFlash.Buf,DataLen);
			CN_st_Fun_DownFile.WriteFile(DownFileFd,CN_st_Buf_rwFlash.Buf,DataLen);	

			CN_st_DownFile_Infor.RevFileLen+=DataLen;
			if(CN_st_DownFile_Infor.RevFileLen==CN_st_DownFile_Infor.TotalFileLen)	
			{	//CN_st_Fun_DownFile.GetFileProperty(DownFileFd,&CN_st_DownFile_Infor);
//				for(i=0;i<CN_st_DownFile_Infor.TotalFileLen;WatchDog())
//				{	Offset=512;
//					if((i+Offset)>CN_st_DownFile_Infor.TotalFileLen)
//						Offset=CN_st_DownFile_Infor.TotalFileLen-i;		
//					CN_st_Fun_DownFile.ReadFile(DownFileFd,CN_st_Buf_rwFlash.Buf,i,Offset);		
//					CN_st_Fun_Uart.Write(3,CN_st_Buf_rwFlash.Buf,Offset);
//					i+=Offset;	
//				}
				CN_st_FTP_Recoder.UpFlag=1;
				CN_st_Fun_File.WriteRecoder(FTPRecoderFd,0,&CN_st_FTP_Recoder);
				break;
			}
		}
		else
		{	CN_st_Fun_AscNumber.MoveByte(CN_st_Buf_rwFlash.Buf+CN_st_Buf_rwFlash.DataLength,Data+j,DataLength);
			CN_st_Buf_rwFlash.DataLength=CN_st_Buf_rwFlash.DataLength+DataLength;
			break;	
		}
	}
	CN_st_FTP_WorkState.FileLen = CN_st_DownFile_Infor.TotalFileLen;
	CN_st_FTP_WorkState.DownLoaderLen = CN_st_DownFile_Infor.RevFileLen;
	RecData_Type = De_FTP_DataLink;
	OSQPost(FtpQbox,(void*)&RecData_Type);  			
}

static uint16 GetState(st_FTP_WorkState	*ptst_FTP_WorkState)
{	ptst_FTP_WorkState->FileLen       = CN_st_FTP_WorkState.FileLen;   // 文件长度
    ptst_FTP_WorkState->DownLoaderLen = CN_st_FTP_WorkState.DownLoaderLen;  // 已经下载的文件长度
	ptst_FTP_WorkState->State         = CN_st_Ftp_RunState.DownState;		  // 当前状态
	return De_Suc_FTP;
}
static uint16 ClearSem(OS_EVENT	*FTPSem)
{	
	OS_MBOX_DATA 	SemData;
	uint8 err;
	for(;;)
	{	if(OSMboxQuery(FTPSem, &SemData)!=OS_NO_ERR)
			return 1;
		if(SemData.OSMsg == 0)		
			return De_Suc_FTP;	
		OSMboxPend(FTPSem, 1, &err);  
	}
}
static uint16 ClearQ(OS_EVENT	*FTPSem)
{	
	OS_Q_DATA 	SemData;
	uint8 err;
	for(;;)
	{	if(OSQQuery(FTPSem, &SemData)!=OS_NO_ERR)
			return 1;
		if(SemData.OSNMsgs == 0)		
			return De_Suc_FTP;	
		OSQPend(FTPSem, 1, &err);  
	}
}


