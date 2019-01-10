#define De_AppSendAgreeOn_Compiler
#include "AppSendAgreeOn.h"
//#define De_DeBug
/*=============================================对外接口=========================================================*/
static uint16 Init(void)									//初始化
{	if(AppSendAgreeOnSem!=NULL)
		return De_Suc_AgreeOn;
	if((AppSendAgreeOnSem=OSSemCreate(1))==NULL)
		return De_Erro_AppSendAgree_Init;
	return De_Suc_AppSendAgree;	
}

static void NoSemSend(void)		 							//盲区补偿
{	uint16 Result;
	uint8 err;
	OSSemPend(AppSendAgreeOnSem,0, &err);
	CN_Pu_st_st_AgreeOn_Dev_WritePar.OrderNumber=0;
	CN_Pu_st_st_AgreeOn_Dev_WritePar.OrderID=De_Dev_Order_NoSem;
	CN_Pu_st_st_AgreeOn_Dev_WritePar.ContrID=0;
	CN_Pu_st_st_AgreeOn_Dev_WritePar.Buf=X_BUF;
	Result=NoSemSend1();
	if(Result!=De_Suc_AppSendAgree)
		SendLogin();		
	OSSemPost(AppSendAgreeOnSem);
}
static uint16 WriteFlow(uint8 ID,st_WorkFlow_Table	*ptst_WorkFlow_Table,uint8 VidType)	 	//写流水表
{	uint16 Result;
	uint8 err;
	OSSemPend(AppSendAgreeOnSem,0, &err);
	CN_Pu_st_st_AgreeOn_Dev_WritePar.OrderNumber=0;
	CN_Pu_st_st_AgreeOn_Dev_WritePar.OrderID=De_Dev_Order_NoSem;
	CN_Pu_st_st_AgreeOn_Dev_WritePar.ContrID=0;
	CN_Pu_st_st_AgreeOn_Dev_WritePar.Buf=X_BUF;
	CN_Pu_st_st_AgreeOn_Dev_WritePar.ContrID=0;
	Result=WriteFlow2(ID,ptst_WorkFlow_Table,VidType);
	if(Result!=De_Suc_AppSendAgree)
		SendLogin();
	OSSemPost(AppSendAgreeOnSem);
	return Result;
}

static uint16 WriteCommand(uint8 fd,uint16 Par,st_st_AgreeOn_Dev_Par	*ptst_st_AgreeOn_Dev_Par) 									//发送命令
{	uint16 Result;
	uint8 err;
	OSSemPend(AppSendAgreeOnSem,0, &err);
	CN_Pu_st_st_AgreeOn_Dev_WritePar.OrderNumber=0;
	CN_Pu_st_st_AgreeOn_Dev_WritePar.OrderID=De_Dev_Order_NoSem;
	CN_Pu_st_st_AgreeOn_Dev_WritePar.Buf=X_BUF;
	CN_Pu_st_st_AgreeOn_Dev_WritePar.ContrID=ptst_st_AgreeOn_Dev_Par->ContrID;
   	Result=Send(fd,Par,ptst_st_AgreeOn_Dev_Par->Buf);
   	if(Result!=De_Suc_AppSendAgree)
		SendLogin();
	OSSemPost(AppSendAgreeOnSem);
	return Result;
}

static void Answer(st_st_AgreeOn_Dev_Par	*ptst_st_AgreeOn_Dev_Par,uint8 fd,uint16 Result)
{	st_st_AgreeOn_Dev_WritePar	CN_st_st_AgreeOn_Dev_WritePar;
	st_AgreeOn_Send_Answer	CN_st_AgreeOn_Send_Answer;
	uint8 Oper,err;
	OSSemPend(AppSendAgreeOnSem,0, &err);
	CN_st_AgreeOn_Send_Answer.Number=ptst_st_AgreeOn_Dev_Par->OrderNumber;
	CN_st_AgreeOn_Send_Answer.OrderID=ptst_st_AgreeOn_Dev_Par->OrderID;
	CN_st_st_AgreeOn_Dev_WritePar.ContrID=ptst_st_AgreeOn_Dev_Par->ContrID;
	if(Result==De_Suc_AppSendAgree)
		CN_st_AgreeOn_Send_Answer.Result=De_Suc_Oper;
	else
		CN_st_AgreeOn_Send_Answer.Result=De_Erro_Oper;
	CN_st_st_AgreeOn_Dev_WritePar.OrderNumber=0;
	CN_st_st_AgreeOn_Dev_WritePar.OrderID=De_Dev_Order_Answer;
	CN_st_st_AgreeOn_Dev_WritePar.Buf=&CN_st_AgreeOn_Send_Answer;
	CN_st_Fun_Tzv21.Write(fd,&CN_st_st_AgreeOn_Dev_WritePar,&Oper);
	OSSemPost(AppSendAgreeOnSem);
}

static uint16 NoSemSend1(void)																//盲区补偿
{	uint16 Result;
	
	if((Result=NoSemTrack())!=De_Suc_AppSendAgree)
		return Result;
	if((Result=NoSemWorkPar())!=De_Suc_AppSendAgree)
		return Result;
	if((Result=NoSemReduce())!=De_Suc_AppSendAgree)
		return Result;
	if((Result=NoSemJpgData())!=De_Suc_AppSendAgree)
		return Result;
	return NoSemDriver();														
}


static uint16 NoSemTrack(void)
{	st_Parameter_Table	CN_st_Parameter_Table;
	st_NoFlow_Table	CN_st_NoFlow_Table;
	st_AgreeOn_Send_LogAndNoSem	*ptst_AgreeOn_Send_LogAndNoSem;
	uint16 Cuit,i,Number,DataLen,ReDataLen,Result;
	uint8 fd,Oper;
	CN_st_Fun_File.ReadRecoder(CN_st_File_fd.Parameterfd,0,&CN_st_Parameter_Table);
	if(CN_st_Parameter_Table.CN_st_Data_Access.ScotomaLog[0]==1)
	{	CN_st_Fun_TakeData.AddSpace(De_ReadSpace_Track,De_Space_Set);
	   	return De_Suc_AppSendAgree;
	}
	Cuit=CN_st_Fun_TakeData.ReadSpace(De_ReadSpace_Track);
	i=CN_st_Fun_File.GetPointNum(CN_st_File_fd.NoFlowfd,Cuit);
	Cuit=CN_st_Fun_File.GetJlNum(CN_st_File_fd.NoFlowfd);
   	ptst_AgreeOn_Send_LogAndNoSem=CN_Pu_st_st_AgreeOn_Dev_WritePar.Buf;
	ptst_AgreeOn_Send_LogAndNoSem->ParID=De_Dev_Order_Orientation;
	for(Number=i,DataLen=0;i<=Cuit;i++)
	{	CN_st_Fun_File.ReadRecoder(CN_st_File_fd.NoFlowfd,i,&CN_st_NoFlow_Table);
		if(CN_st_NoFlow_Table.ID!=De_Access_Type_Track)
			continue;
		TrackDataExplain(i,ptst_AgreeOn_Send_LogAndNoSem->X_BUF+DataLen,&ReDataLen);
		if((DataLen+ReDataLen+(ptst_AgreeOn_Send_LogAndNoSem->Number+1)*2+42)>512)
		{	if(CN_st_Fun_Tzv21.GetPar2ID(De_Sensor_WordPar_UartTzxy_1,&fd)==De_Suc_AgreeOn)			//发送信息
				CN_st_Fun_Tzv21.Write(fd,&CN_Pu_st_st_AgreeOn_Dev_WritePar,&Oper);
			if((Result=CN_st_Fun_Tzv21.GetPar2ID(De_Sensor_WordPar_GprsTzxy_1,&fd))!=De_Suc_AgreeOn)
				return Result;
			if((Result=CN_st_Fun_Tzv21.Write(fd,&CN_Pu_st_st_AgreeOn_Dev_WritePar,&Oper))!=De_Suc_AgreeOn)
				return Result;
			i--;
			CN_st_Fun_TakeData.AddSpace(De_ReadSpace_Track,i-Number);
			Number=i;
			ptst_AgreeOn_Send_LogAndNoSem->Number=0;	
			CN_Pu_st_st_AgreeOn_Dev_WritePar.OrderNumber++;
		}
		DataLen+=ReDataLen;
		ptst_AgreeOn_Send_LogAndNoSem->DataLen[ptst_AgreeOn_Send_LogAndNoSem->Number++]=ReDataLen;
	}
	if(ptst_AgreeOn_Send_LogAndNoSem->Number!=0)
	{	if(CN_st_Fun_Tzv21.GetPar2ID(De_Sensor_WordPar_UartTzxy_1,&fd)==De_Suc_AgreeOn)			//发送信息
			CN_st_Fun_Tzv21.Write(fd,&CN_Pu_st_st_AgreeOn_Dev_WritePar,&Oper);
		if((Result=CN_st_Fun_Tzv21.GetPar2ID(De_Sensor_WordPar_GprsTzxy_1,&fd))!=De_Suc_AgreeOn)
			return Result;
		if((Result=CN_st_Fun_Tzv21.Write(fd,&CN_Pu_st_st_AgreeOn_Dev_WritePar,&Oper))!=De_Suc_AgreeOn)
			return Result;
		CN_Pu_st_st_AgreeOn_Dev_WritePar.OrderNumber++;
	}	
   	CN_st_Fun_TakeData.AddSpace(De_ReadSpace_Track,De_Space_Set);
	return De_Suc_AppSendAgree;
}

static uint16 NoSemWorkPar(void)
{	st_Parameter_Table	CN_st_Parameter_Table;
	st_AgreeOn_Send_LogAndNoSem	*ptst_AgreeOn_Send_LogAndNoSem;
	st_NoFlow_Table	CN_st_NoFlow_Table;
	uint16 Cuit,i,Number,DataLen,ReDataLen,Result;
	uint8 fd,Oper;
	CN_st_Fun_File.ReadRecoder(CN_st_File_fd.Parameterfd,0,&CN_st_Parameter_Table);
	if(CN_st_Parameter_Table.CN_st_Data_Access.ScotomaLog[1]==1)
	{	CN_st_Fun_TakeData.AddSpace(De_ReadSpace_WorkPar,De_Space_Set);
	   	return De_Suc_AppSendAgree;
	}
	Cuit=CN_st_Fun_TakeData.ReadSpace(De_ReadSpace_WorkPar);
	i=CN_st_Fun_File.GetPointNum(CN_st_File_fd.NoFlowfd,Cuit);
	Cuit=CN_st_Fun_File.GetJlNum(CN_st_File_fd.NoFlowfd);
   	ptst_AgreeOn_Send_LogAndNoSem=CN_Pu_st_st_AgreeOn_Dev_WritePar.Buf;
	ptst_AgreeOn_Send_LogAndNoSem->ParID=De_Dev_Order_UploaderPar;
	for(Number=i,DataLen=0;i<=Cuit;i++)
	{	CN_st_Fun_File.ReadRecoder(CN_st_File_fd.NoFlowfd,i,&CN_st_NoFlow_Table);
		if(CN_st_NoFlow_Table.ID!=De_Access_Type_WorkPar)
			continue;
		WorkParDataExpalin(i,ptst_AgreeOn_Send_LogAndNoSem->X_BUF+DataLen,&ReDataLen);
		if((DataLen+ReDataLen+(ptst_AgreeOn_Send_LogAndNoSem->Number+1)*2+42)>512)
		{	if(CN_st_Fun_Tzv21.GetPar2ID(De_Sensor_WordPar_UartTzxy_1,&fd)==De_Suc_AgreeOn)			//发送信息
				CN_st_Fun_Tzv21.Write(fd,&CN_Pu_st_st_AgreeOn_Dev_WritePar,&Oper);
			if((Result=CN_st_Fun_Tzv21.GetPar2ID(De_Sensor_WordPar_GprsTzxy_1,&fd))!=De_Suc_AgreeOn)
				return Result;
			if((Result=CN_st_Fun_Tzv21.Write(fd,&CN_Pu_st_st_AgreeOn_Dev_WritePar,&Oper))!=De_Suc_AgreeOn)
				return Result;
			i--;
			CN_st_Fun_TakeData.AddSpace(De_ReadSpace_WorkPar,i-Number);
			Number=i;
			ptst_AgreeOn_Send_LogAndNoSem->Number=0;	
		}
		DataLen+=ReDataLen;
		ptst_AgreeOn_Send_LogAndNoSem->DataLen[ptst_AgreeOn_Send_LogAndNoSem->Number++]=ReDataLen;
		CN_Pu_st_st_AgreeOn_Dev_WritePar.OrderNumber++;
	}
	if(ptst_AgreeOn_Send_LogAndNoSem->Number!=0)
	{	if(CN_st_Fun_Tzv21.GetPar2ID(De_Sensor_WordPar_UartTzxy_1,&fd)==De_Suc_AgreeOn)			//发送信息
			CN_st_Fun_Tzv21.Write(fd,&CN_Pu_st_st_AgreeOn_Dev_WritePar,&Oper);
		if((Result=CN_st_Fun_Tzv21.GetPar2ID(De_Sensor_WordPar_GprsTzxy_1,&fd))!=De_Suc_AgreeOn)
			return Result;
		if((Result=CN_st_Fun_Tzv21.Write(fd,&CN_Pu_st_st_AgreeOn_Dev_WritePar,&Oper))!=De_Suc_AgreeOn)
			return Result;
		CN_Pu_st_st_AgreeOn_Dev_WritePar.OrderNumber++;
	}	
   	CN_st_Fun_TakeData.AddSpace(De_ReadSpace_WorkPar,De_Space_Set);
	return De_Suc_AppSendAgree;
}

static uint16 NoSemReduce(void)
{	st_Parameter_Table	CN_st_Parameter_Table;
	st_NoFlow_Table	CN_st_NoFlow_Table;
	st_AgreeOn_Send_LogAndNoSem	*ptst_AgreeOn_Send_LogAndNoSem;
	uint16 Cuit,i,Number,DataLen,ReDataLen,Result;
	uint8 fd,Oper;
	CN_st_Fun_File.ReadRecoder(CN_st_File_fd.Parameterfd,0,&CN_st_Parameter_Table);
	if(CN_st_Parameter_Table.CN_st_Data_Access.ScotomaLog[3]==1)
	{	CN_st_Fun_TakeData.AddSpace(De_ReadSpace_Reduce,De_Space_Set);
	   	return De_Suc_AppSendAgree;
	}
	Cuit=CN_st_Fun_TakeData.ReadSpace(De_ReadSpace_Reduce);
	i=CN_st_Fun_File.GetPointNum(CN_st_File_fd.NoFlowfd,Cuit);
	Cuit=CN_st_Fun_File.GetJlNum(CN_st_File_fd.NoFlowfd);
   	ptst_AgreeOn_Send_LogAndNoSem=CN_Pu_st_st_AgreeOn_Dev_WritePar.Buf;
	ptst_AgreeOn_Send_LogAndNoSem->ParID=De_Dev_Order_UpLoaderReduce;
	for(Number=i,DataLen=0;i<=Cuit;i++)
	{	CN_st_Fun_File.ReadRecoder(CN_st_File_fd.NoFlowfd,i,&CN_st_NoFlow_Table);
		if((CN_st_NoFlow_Table.ID!=De_Access_Type_ReduceWork)&&(CN_st_NoFlow_Table.ID!=De_Access_Type_ReduceWork))
			continue;
		UpLoaderReduce(i,ptst_AgreeOn_Send_LogAndNoSem->X_BUF+DataLen,&ReDataLen);
		if((DataLen+ReDataLen+(ptst_AgreeOn_Send_LogAndNoSem->Number+1)*2+42)>512)
		{	if(CN_st_Fun_Tzv21.GetPar2ID(De_Sensor_WordPar_UartTzxy_1,&fd)==De_Suc_AgreeOn)			//发送信息
				CN_st_Fun_Tzv21.Write(fd,&CN_Pu_st_st_AgreeOn_Dev_WritePar,&Oper);
			if((Result=CN_st_Fun_Tzv21.GetPar2ID(De_Sensor_WordPar_GprsTzxy_1,&fd))!=De_Suc_AgreeOn)
				return Result;
			if((Result=CN_st_Fun_Tzv21.Write(fd,&CN_Pu_st_st_AgreeOn_Dev_WritePar,&Oper))!=De_Suc_AgreeOn)
				return Result;
			i--;
			CN_st_Fun_TakeData.AddSpace(De_ReadSpace_Reduce,i-Number);
			Number=i;
			ptst_AgreeOn_Send_LogAndNoSem->Number=0;	
		}
		DataLen+=ReDataLen;
		ptst_AgreeOn_Send_LogAndNoSem->DataLen[ptst_AgreeOn_Send_LogAndNoSem->Number++]=ReDataLen;
		CN_Pu_st_st_AgreeOn_Dev_WritePar.OrderNumber++;
	}
	if(ptst_AgreeOn_Send_LogAndNoSem->Number!=0)
	{	if(CN_st_Fun_Tzv21.GetPar2ID(De_Sensor_WordPar_UartTzxy_1,&fd)==De_Suc_AgreeOn)			//发送信息
			CN_st_Fun_Tzv21.Write(fd,&CN_Pu_st_st_AgreeOn_Dev_WritePar,&Oper);
		if((Result=CN_st_Fun_Tzv21.GetPar2ID(De_Sensor_WordPar_GprsTzxy_1,&fd))!=De_Suc_AgreeOn)
			return Result;
		if((Result=CN_st_Fun_Tzv21.Write(fd,&CN_Pu_st_st_AgreeOn_Dev_WritePar,&Oper))!=De_Suc_AgreeOn)
			return Result;
		CN_Pu_st_st_AgreeOn_Dev_WritePar.OrderNumber++;
	}	
   	CN_st_Fun_TakeData.AddSpace(De_ReadSpace_Reduce,De_Space_Set);
	return De_Suc_AppSendAgree;
}


static uint16 NoSemJpgData(void)
{ 	st_Parameter_Table	CN_st_Parameter_Table;
	st_NoFlow_Table	CN_st_NoFlow_Table;
	st_AgreeOn_Send_LogAndNoSem	*ptst_AgreeOn_Send_LogAndNoSem;
	uint16 Cuit,i,Number,Result;
	uint8 fd,Oper;
	CN_st_Fun_File.ReadRecoder(CN_st_File_fd.Parameterfd,0,&CN_st_Parameter_Table);
	if(CN_st_Parameter_Table.CN_st_Data_Access.ScotomaLog[2]==1)
	{	CN_st_Fun_TakeData.AddSpace(De_ReadSpace_Reduce,De_Space_Set);
	   	return De_Suc_AppSendAgree;
	}
	Cuit=CN_st_Fun_TakeData.ReadSpace(De_ReadSpace_Reduce);
	i=CN_st_Fun_File.GetPointNum(CN_st_File_fd.NoFlowfd,Cuit);
	Cuit=CN_st_Fun_File.GetJlNum(CN_st_File_fd.NoFlowfd);
   	ptst_AgreeOn_Send_LogAndNoSem=CN_Pu_st_st_AgreeOn_Dev_WritePar.Buf;
	ptst_AgreeOn_Send_LogAndNoSem->ParID=De_Dev_Order_UploaderJpg1;
	for(Number=i;i<=Cuit;i++)
	{	CN_st_Fun_File.ReadRecoder(CN_st_File_fd.NoFlowfd,i,&CN_st_NoFlow_Table);
		if((CN_st_NoFlow_Table.ID!=De_Access_Type_WaringParVid)&&(CN_st_NoFlow_Table.ID!=De_Access_Type_HelpVid))
			continue;
		if((Result=LoaderJpgData(i,fd))!=De_Suc_AgreeOn)
			return Result;	
		if(CN_st_Fun_Tzv21.GetPar2ID(De_Sensor_WordPar_UartTzxy_1,&fd)==De_Suc_AgreeOn)
			LoaderJpgData(i,fd);
		if((Result=CN_st_Fun_Tzv21.GetPar2ID(De_Sensor_WordPar_GprsTzxy_1,&fd))!=De_Suc_AgreeOn)
			return Result;
		if((Result=LoaderJpgData(i,fd))!=De_Suc_AgreeOn)
			return Result;	
		i--;
		CN_st_Fun_TakeData.AddSpace(De_ReadSpace_WorkPar,i-Number);
		Number=i;
		ptst_AgreeOn_Send_LogAndNoSem->Number=0;
	}
	if(ptst_AgreeOn_Send_LogAndNoSem->Number!=0)
	{	if(CN_st_Fun_Tzv21.GetPar2ID(De_Sensor_WordPar_UartTzxy_1,&fd)==De_Suc_AgreeOn)			//发送信息
			CN_st_Fun_Tzv21.Write(fd,&CN_Pu_st_st_AgreeOn_Dev_WritePar,&Oper);
		if((Result=CN_st_Fun_Tzv21.GetPar2ID(De_Sensor_WordPar_GprsTzxy_1,&fd))!=De_Suc_AgreeOn)
			return Result;
		if((Result=CN_st_Fun_Tzv21.Write(fd,&CN_Pu_st_st_AgreeOn_Dev_WritePar,&Oper))!=De_Suc_AgreeOn)
			return Result;
	}	
   	CN_st_Fun_TakeData.AddSpace(De_ReadSpace_Reduce,De_Space_Set);
	return De_Suc_AppSendAgree;
} 

static uint16 NoSemDriver(void)
{	st_Parameter_Table	CN_st_Parameter_Table;
	st_NoFlow_Table	CN_st_NoFlow_Table;
	st_AgreeOn_Send_LogAndNoSem	*ptst_AgreeOn_Send_LogAndNoSem;
	uint16 Cuit,i,Number,DataLen,ReDataLen,Result;
	uint8 fd,Oper;
	Cuit=CN_st_Fun_TakeData.ReadSpace(De_ReadSpace_DriverLog);
	i=CN_st_Fun_File.GetPointNum(CN_st_File_fd.NoFlowfd,Cuit);
	Cuit=CN_st_Fun_File.GetJlNum(CN_st_File_fd.NoFlowfd);
   	ptst_AgreeOn_Send_LogAndNoSem=CN_Pu_st_st_AgreeOn_Dev_WritePar.Buf;
	ptst_AgreeOn_Send_LogAndNoSem->ParID=De_Dev_Order_UpLoaderDriver;
	for(Number=i,DataLen=0;i<=Cuit;i++)
	{	CN_st_Fun_File.ReadRecoder(CN_st_File_fd.NoFlowfd,i,&CN_st_NoFlow_Table);
		if((CN_st_NoFlow_Table.ID!=De_Access_Type_JugeLog)&&(CN_st_NoFlow_Table.ID!=De_Access_Type_ExitLog)&&(CN_st_NoFlow_Table.ID!=De_Access_Type_LogErro))
			continue;
		UpLoaderDriverExplain(i,ptst_AgreeOn_Send_LogAndNoSem->X_BUF+DataLen,&ReDataLen);
		if((DataLen+ReDataLen+(ptst_AgreeOn_Send_LogAndNoSem->Number+1)*2+42)>512)
		{	if(CN_st_Fun_Tzv21.GetPar2ID(De_Sensor_WordPar_UartTzxy_1,&fd)==De_Suc_AgreeOn)			//发送信息
				CN_st_Fun_Tzv21.Write(fd,&CN_Pu_st_st_AgreeOn_Dev_WritePar,&Oper);
			if((Result=CN_st_Fun_Tzv21.GetPar2ID(De_Sensor_WordPar_GprsTzxy_1,&fd))!=De_Suc_AgreeOn)
				return Result;
			if((Result=CN_st_Fun_Tzv21.Write(fd,&CN_Pu_st_st_AgreeOn_Dev_WritePar,&Oper))!=De_Suc_AgreeOn)
				return Result;
			i--;
			CN_st_Fun_TakeData.AddSpace(De_ReadSpace_DriverLog,i-Number);
			Number=i;
			ptst_AgreeOn_Send_LogAndNoSem->Number=0;	
			CN_Pu_st_st_AgreeOn_Dev_WritePar.OrderNumber++;
		}
		DataLen+=ReDataLen;
		ptst_AgreeOn_Send_LogAndNoSem->DataLen[ptst_AgreeOn_Send_LogAndNoSem->Number++]=ReDataLen;
	}
	if(ptst_AgreeOn_Send_LogAndNoSem->Number!=0)
	{	if(CN_st_Fun_Tzv21.GetPar2ID(De_Sensor_WordPar_UartTzxy_1,&fd)==De_Suc_AgreeOn)			//发送信息
			CN_st_Fun_Tzv21.Write(fd,&CN_Pu_st_st_AgreeOn_Dev_WritePar,&Oper);
		if((Result=CN_st_Fun_Tzv21.GetPar2ID(De_Sensor_WordPar_GprsTzxy_1,&fd))!=De_Suc_AgreeOn)
			return Result;
		if((Result=CN_st_Fun_Tzv21.Write(fd,&CN_Pu_st_st_AgreeOn_Dev_WritePar,&Oper))!=De_Suc_AgreeOn)
			return Result;
		CN_Pu_st_st_AgreeOn_Dev_WritePar.OrderNumber++;
	}	
   	CN_st_Fun_TakeData.AddSpace(De_ReadSpace_DriverLog,De_Space_Set);
	return De_Suc_AppSendAgree;
}





/*==============================================写流水表=======================================================*/
static uint16 WriteFlow2(uint8 ID,st_WorkFlow_Table	*ptst_WorkFlow_Table,uint8 VidType) 	//写数据库然后发送
{	
	uint16 Result,Recoder;
	if((Result=WriteFlow1(ID,ptst_WorkFlow_Table,VidType))!=De_Suc_AccessBasic)
		return De_Suc_AppSendAgree;
	Recoder=CN_st_Fun_TakeData.ReadSpace(De_ReadSpace_Track);					//获取最后一条的地址
	if((Result=SendData(Recoder))==De_Suc_AppSendAgree)
	{	CN_st_Fun_TakeData.AddSpace(De_ReadSpace_Track,De_Space_Set);	
		CN_st_Fun_TakeData.AddSpace(De_ReadSpace_WorkPar,De_Space_Set);
		CN_st_Fun_TakeData.AddSpace(De_ReadSpace_Reduce,De_Space_Set);
		CN_st_Fun_TakeData.AddSpace(De_ReadSpace_Photo,De_Space_Set);
		CN_st_Fun_TakeData.AddSpace(De_ReadSpace_DriverLog,De_Space_Set);
		return De_Suc_AppSendAgree;
	}
	return Result;	
}
static uint16 SendData(uint16 Recoder)
{ 	
	uint8 Type,i,fd;
	CN_st_Fun_TakeData.GetFlowWaringType(Recoder,&Type);
   	for(i=0;i<sizeof(CN_Ba_VidType);i++)
	{	if(Type==CN_Ba_VidType[i])
			break;
	}
	if(i!=sizeof(CN_Ba_VidType))								//拍照
	{	return LoadJpg(Recoder);
	} 
	for(i=0;i<sizeof(CN_Ba_Type2Par)/sizeof(st_Type2Par_Data);i++)
	{	if(CN_Ba_Type2Par[i].Type==Type)	
			break;
	}
	if(i!=sizeof(CN_Ba_Type2Par)/sizeof(st_Type2Par_Data))
	{	if(CN_st_Fun_Tzv21.GetPar2ID(De_Sensor_WordPar_UartTzxy_1,&fd)==De_Suc_AgreeOn)			//发送信息
		{	Send(fd,CN_Ba_Type2Par[i].Par,&Recoder);			
			#ifdef De_DeBug
				return De_Suc_AppSendAgree;

			#endif
		}
		if(CN_st_Fun_Tzv21.GetPar2ID(De_Sensor_WordPar_GprsTzxy_1,&fd)!=De_Suc_AgreeOn)
			return De_Erro_AppSendAgreeOn_NoLink;
		return Send(fd,CN_Ba_Type2Par[i].Par,&Recoder);
	}
	return De_Suc_AppSendAgree; 												
}
static uint16 LoadJpg(uint16 Recoder)
{	st_Parameter_Table	CN_st_Parameter_Table;
	uint16 Result;
	uint8 fd;
	CN_st_Fun_File.ReadRecoder(CN_st_File_fd.Parameterfd,0,&CN_st_Parameter_Table);
	if((CN_st_Parameter_Table.CN_st_AgreeOn_JpgIng.Contrl==De_st_AgreeOn_JpgIng_Contrl_End)
	||(CN_st_Parameter_Table.CN_st_AgreeOn_JpgIng.LoadNumber==0)) 			//无需上传压缩数据
		return De_Suc_AppSendAgree;
	if(CN_st_Fun_Tzv21.GetPar2ID(De_Sensor_WordPar_UartTzxy_1,&fd)==De_Suc_AgreeOn)			//发送信息
		Send(fd,De_Dev_Order_UploaderJpg1,&Recoder); 
	#ifdef De_DeBug

	#else
		if(CN_st_Fun_Tzv21.GetPar2ID(De_Sensor_WordPar_GprsTzxy_1,&fd)!=De_Suc_AgreeOn)
			return De_Erro_AppSendAgreeOn_NoLink;
	#endif
	if((Result=Send(fd,De_Dev_Order_UploaderJpg2,&Recoder))==De_Suc_AgreeOn)
	{	if(CN_st_Parameter_Table.CN_st_AgreeOn_JpgIng.LoadNumber!=0xffff)
			CN_st_Parameter_Table.CN_st_AgreeOn_JpgIng.LoadNumber--;
		CN_st_Fun_File.WriteRecoder(CN_st_File_fd.Parameterfd,0,&CN_st_Parameter_Table);		
		return De_Suc_AppSendAgree;
	}
	return Result;		
}
static uint16 WriteFlow1(uint8 ID,st_WorkFlow_Table	*ptst_WorkFlow_Table,uint8 VidType) 	//写数据库数据上传
{	st_Parameter_Table	CN_st_Parameter_Table;
	uint16 Result,VidCuit=NULL;
	if(VidType!=NULL)																		//必须进行先拍照
	{	CN_st_Fun_File.ReadRecoder(CN_st_File_fd.Parameterfd,0,&CN_st_Parameter_Table);
		if(CN_st_Parameter_Table.DisVid==De_Agree_Par_TaskVid_No) 							//没有安装摄像头
			return De_Erro_AppSendAgreeOn_NoVid;
		if((Result=CN_st_Fun_TakeData.WritePhone(&VidCuit))==De_Suc_Photo)														//如果照片
		{	ptst_WorkFlow_Table->CN_st_AgreeOn_Send_Basic.State[De_Orientation_State_Vid]=
			De_AgreeOn_State_Suc;								//拍照状态置位
		}
		else 
		{	VidCuit=NULL;	
			ptst_WorkFlow_Table->CN_st_AgreeOn_Send_Basic.State[De_Orientation_State_Vid]=
			De_AgreeOn_State_Erro;								//拍照状态恢复
			return Result;
		}
	}
	ptst_WorkFlow_Table->PhotoAdree=VidCuit;
	return CN_st_Fun_TakeData.WriteFlow(ID,ptst_WorkFlow_Table);
}
/*============================================发送命令===========================================================*/
static uint16 Send(uint8 fd,uint16 Par,void *Buf)
{	uint8 i;
	CN_Pu_st_st_AgreeOn_Dev_WritePar.OrderID=Par;
	CN_Pu_st_st_AgreeOn_Dev_WritePar.OrderNumber=0;
	for(i=0;i<sizeof(CN_Ba_st_Par2Fun_Par)/sizeof(st_Par2Fun_Par);i++)
	{	if(CN_Ba_st_Par2Fun_Par[i].Par==Par)
		{	CN_Pu_st_st_AgreeOn_Dev_WritePar.OrderID=CN_Ba_st_Par2Fun_Par[i].Par;
			if(CN_Ba_st_Par2Fun_Par[i].ptFun!=NULL)
				return CN_Ba_st_Par2Fun_Par[i].ptFun(fd,Buf);
		}
	}
	return De_Suc_AppSendAgree;							
}
/*================================================登录信息========================================================*/
static uint16 LogInfor(uint8 fd,void *Buf)
{	uint8 Oper;	
	CN_Pu_st_st_AgreeOn_Dev_WritePar.Buf=&App_CN_st_WorkFlow_Table.CN_st_AgreeOn_Send_Basic;
	return CN_st_Fun_Tzv21.Write(fd,&CN_Pu_st_st_AgreeOn_Dev_WritePar,&Oper);
}


/*===========================================上传位置信息========================================================*/
static uint16 Orientation(uint8 fd,void *Buf)  					
{	st_WorkFlow_Table	CN_st_WorkFlow_Table;
	uint8 Oper;
	uint16 *RecoderSize;
	RecoderSize=Buf;
	CN_st_Fun_TakeData.ReadFlow(*RecoderSize,&CN_st_WorkFlow_Table);
	CN_st_Fun_AscNumber.MoveByte(CN_Pu_st_st_AgreeOn_Dev_WritePar.Buf,&CN_st_WorkFlow_Table.CN_st_AgreeOn_Send_Basic,
	sizeof(st_AgreeOn_Send_Basic));	
	return CN_st_Fun_Tzv21.Write(fd,&CN_Pu_st_st_AgreeOn_Dev_WritePar,&Oper);
}
/*=============================================上传菜单信息=====================================================*/
static uint16 Menum(uint8 fd,void *Buf)
{	uint8 Oper;
	CN_Pu_st_st_AgreeOn_Dev_WritePar.Buf=Buf;	
	return CN_st_Fun_Tzv21.Write(fd,&CN_Pu_st_st_AgreeOn_Dev_WritePar,&Oper);
}
/*==========================================上传带菜单的反馈信息=================================================*/
static uint16 TxtMenum(uint8 fd,void *Buf)
{	uint8 Oper;
	CN_Pu_st_st_AgreeOn_Dev_WritePar.Buf=Buf;	
	return CN_st_Fun_Tzv21.Write(fd,&CN_Pu_st_st_AgreeOn_Dev_WritePar,&Oper);
}
/*=============================================上传定位终端参数=================================================*/
static uint16 LookPar(uint8 fd,void *Buf)
{	uint16 i;
	st_AgreeOn_LookPar	*ptst_AgreeOn_LookPar;
	st_AgreeOn_Agree_Par	*ptst_AgreeOn_Agree_Par;
	uint8 Oper;
	ptst_AgreeOn_LookPar=Buf;
	ptst_AgreeOn_Agree_Par=CN_Pu_st_st_AgreeOn_Dev_WritePar.Buf;
	for(i=0;i<De_AgreeOn_SetPar_Number;i++)
	{	ptst_AgreeOn_Agree_Par->ParSet[i]=De_AgreeOn_LookPar_NoData;
		if(ptst_AgreeOn_LookPar->Par[i]!=De_AgreeOn_LookPar_Yes)
			continue;
		if(GetPar(&ptst_AgreeOn_Agree_Par->CN_st_AgreeOn_Agree_Par_Cut,i)!=De_Suc_AppSendAgreeOn)
			ptst_AgreeOn_Agree_Par->ParSet[i]=De_AgreeOn_LookPar_Erro;
		else
			ptst_AgreeOn_Agree_Par->ParSet[i]=De_AgreeOn_LookPar_YesData;
	}
	return CN_st_Fun_Tzv21.Write(fd,&CN_Pu_st_st_AgreeOn_Dev_WritePar,&Oper);		
}
/*============================================上传软件升级状态================================================*/
static uint16 UpdateSoftWare(uint8 fd,void *Buf)
{	uint8 Oper;
	CN_Pu_st_st_AgreeOn_Dev_WritePar.Buf=Buf;
	return CN_st_Fun_Tzv21.Write(fd,&CN_Pu_st_st_AgreeOn_Dev_WritePar,&Oper); 
}
/*============================================上传报警状态====================================================*/
static uint16 Waring(uint8 fd,void *Buf)
{	st_WorkFlow_Table	CN_st_WorkFlow_Table;
	st_AgreeOn_Send_Waring	*ptst_AgreeOn_Send_Waring;
	uint16 *RecoderSize;
	uint8 *State;
	uint16 i;	
	uint8 Oper;
   	RecoderSize=Buf;
	ptst_AgreeOn_Send_Waring=CN_Pu_st_st_AgreeOn_Dev_WritePar.Buf;
	CN_st_Fun_TakeData.ReadFlow(*RecoderSize,&CN_st_WorkFlow_Table);
	CN_st_Fun_TakeData.GetFlowWaringType(*RecoderSize,&ptst_AgreeOn_Send_Waring->Type);
	CN_st_Fun_AscNumber.MoveByte(&ptst_AgreeOn_Send_Waring->CN_st_AgreeOn_Send_Basic,
	&CN_st_WorkFlow_Table.CN_st_AgreeOn_Send_Basic,sizeof(st_AgreeOn_Send_Basic));

	CN_st_Fun_AscNumber.MoveByte(&ptst_AgreeOn_Send_Waring->CN_st_WorkVal_Tabel,
	&CN_st_WorkFlow_Table.CN_st_WorkVal_Tabel,sizeof(st_WorkVal_Tabel));
	for(i=0;i<sizeof(ptst_AgreeOn_Send_Waring->CN_st_Sensor_State)/sizeof(st_Sensor_State);i++)
	{	State=(uint8 *)((uint32 )JugePar[i]+(uint32 )&CN_st_WorkFlow_Table);
		ptst_AgreeOn_Send_Waring->CN_st_Sensor_State[i].Work=De_AgreeOn_Send_Less_State_Suc;
		ptst_AgreeOn_Send_Waring->CN_st_Sensor_State[i].Dly=De_AgreeOn_Send_Less_State_Suc;	
		ptst_AgreeOn_Send_Waring->CN_st_Sensor_State[i].Battery=De_AgreeOn_Send_Less_State_Suc;
		if(*State==De_Sensor_State_Suc)
			continue;
		else if(*State==De_Sensor_Battery_State_Erro)
			ptst_AgreeOn_Send_Waring->CN_st_Sensor_State[i].Battery=De_AgreeOn_Send_Less_State_Erro;
		else if(*State==De_Sensor_Par_State_Erro)
			ptst_AgreeOn_Send_Waring->CN_st_Sensor_State[i].Work=De_AgreeOn_Send_Less_State_Erro;
		else if(*State==De_Sensor_MaxDly_State_Erro)
			ptst_AgreeOn_Send_Waring->CN_st_Sensor_State[i].Dly=De_AgreeOn_Send_Less_State_Erro;												
	}
	return CN_st_Fun_Tzv21.Write(fd,&CN_Pu_st_st_AgreeOn_Dev_WritePar,&Oper);
}
/*===========================================上传照片一==========================================================*/
static uint16 UploaderJpg1(uint8 fd,void *Buf)	   				
{	st_WorkFlow_Table	CN_st_WorkFlow_Table;
	st_AgreeOn_Send_UploaderJpg1	*ptst_AgreeOn_Send_UploaderJpg1;
	uint32 iSize;
	uint16 *Recoder;
	uint16 Result,Len,i;
	uint8 Oper;
	Recoder=Buf;
	ptst_AgreeOn_Send_UploaderJpg1=CN_Pu_st_st_AgreeOn_Dev_WritePar.Buf;
	ptst_AgreeOn_Send_UploaderJpg1->Type=1;
	CN_st_Fun_TakeData.GetFlowWaringType(*Recoder,&ptst_AgreeOn_Send_UploaderJpg1->Type);
	CN_st_Fun_TakeData.ReadFlow(*Recoder,&CN_st_WorkFlow_Table);

	CN_st_Fun_AscNumber.MoveByte(&ptst_AgreeOn_Send_UploaderJpg1->CN_st_AgreeOn_Send_Basic,
	&CN_st_WorkFlow_Table.CN_st_AgreeOn_Send_Basic,sizeof(st_AgreeOn_Send_Basic));

	iSize=CN_st_Fun_TakeData.GetPhonesSize(CN_st_WorkFlow_Table.PhotoAdree);
	ptst_AgreeOn_Send_UploaderJpg1->SecSum=iSize/sizeof(ptst_AgreeOn_Send_UploaderJpg1->Buf);
	if(iSize%sizeof(ptst_AgreeOn_Send_UploaderJpg1->Buf))
		ptst_AgreeOn_Send_UploaderJpg1->SecSum++;
	for(i=0;i<ptst_AgreeOn_Send_UploaderJpg1->SecSum;i++)
	{	Len=sizeof(ptst_AgreeOn_Send_UploaderJpg1->Buf);
		if((i*sizeof(ptst_AgreeOn_Send_UploaderJpg1->Buf)+Len)>iSize)
			Len=iSize-i*sizeof(ptst_AgreeOn_Send_UploaderJpg1->Buf);
		CN_st_Fun_TakeData.GetPhoneCut(CN_st_WorkFlow_Table.PhotoAdree,i*sizeof(ptst_AgreeOn_Send_UploaderJpg1->Buf),
		Len,ptst_AgreeOn_Send_UploaderJpg1->Buf);	
			
		ptst_AgreeOn_Send_UploaderJpg1->SizeofBuf=Len;
		ptst_AgreeOn_Send_UploaderJpg1->SecNumber=i+1;
		if((Result=CN_st_Fun_Tzv21.Write(fd,&CN_Pu_st_st_AgreeOn_Dev_WritePar,&Oper))!=De_Suc_AgreeOn)
			return Result;
		CN_Pu_st_st_AgreeOn_Dev_WritePar.OrderNumber++;
	}
	return De_Suc_AppSendAgree;			
}
/*==========================================上传照片二==========================================================*/
static uint16 UploaderJpg2(uint8 fd,void *Buf)
{	st_NoFlow_Table	CN_st_NoFlow_Table;
	st_AgreeOn_LookJpg	*ptst_AgreeOn_LookJpg;
	uint16 i,Cuit,Number,j,Result;

	Cuit=CN_st_Fun_File.GetJlNum(CN_st_File_fd.NoFlowfd);
	ptst_AgreeOn_LookJpg=Buf;
	for(i=0,Number=0;i<Cuit;i++)
	{	CN_st_Fun_File.ReadRecoder(CN_st_File_fd.NoFlowfd,i+1,&CN_st_NoFlow_Table);	
		for(j=0;j<sizeof(CN_Ba_VidType)/sizeof(uint8);j++)
		{	if(CN_st_NoFlow_Table.ID==CN_Ba_VidType[i])
				break;
		}
		if(j==sizeof(CN_Ba_VidType)/sizeof(uint8))				//非照片
			continue;

		if(!(((ptst_AgreeOn_LookJpg->CN_st_VidType.HelpWarning==De_AgreeOn_Vid_Fun_Open)&&(CN_Ba_VidType[j]==De_Access_Type_HelpVid))		
		||((ptst_AgreeOn_LookJpg->CN_st_VidType.Oper==De_AgreeOn_Vid_Fun_Open)&&(CN_Ba_VidType[j]==De_Access_Type_CarPower))		
		||((ptst_AgreeOn_LookJpg->CN_st_VidType.AccOpen==De_AgreeOn_Vid_Fun_Open)&&(CN_Ba_VidType[j]==De_Access_Type_AccOpenVid))
		||((ptst_AgreeOn_LookJpg->CN_st_VidType.AccClose==De_AgreeOn_Vid_Fun_Open)&&(CN_Ba_VidType[j]==De_Access_Type_AccCloseVid))))
			continue;
		if(!((CN_st_Fun_AscNumber.CompareVa(CN_st_NoFlow_Table.DateTimer,ptst_AgreeOn_LookJpg->StartDate,4,De_AscNumber_Va_Big)!=De_AscNumber_Va_True)
		&&(CN_st_Fun_AscNumber.CompareVa(ptst_AgreeOn_LookJpg->EndDate,CN_st_NoFlow_Table.DateTimer,4,De_AscNumber_Va_Big)!=De_AscNumber_Va_True)))
			continue;
		if((Result=UploaderJpg2Sig(fd,CN_st_NoFlow_Table.AcceSpace,ptst_AgreeOn_LookJpg->WorkPar))!=De_Suc_AppSendAgreeOn)	
			return Result;
	   	Number++;
	}
	if(Number==0)
		;//Answer();				//应答错误
	return De_Suc_AppSendAgreeOn;		
}

/*=============================================上传工作参数=================================================*/
static uint16 UploaderPar(uint8 fd,void *Buf)
{	st_WorkFlow_Table	CN_st_WorkFlow_Table;
	st_AgreeOn_Send_UploaderPar	*ptst_AgreeOn_Send_UploaderPar;
	uint16 *RecoderSize;	
	uint8 Oper;			
	RecoderSize=Buf;
	ptst_AgreeOn_Send_UploaderPar=CN_Pu_st_st_AgreeOn_Dev_WritePar.Buf;
	CN_st_Fun_TakeData.ReadFlow(*RecoderSize,&CN_st_WorkFlow_Table);
	CN_st_Fun_AscNumber.MoveByte(&ptst_AgreeOn_Send_UploaderPar->CN_st_AgreeOn_Send_Basic,
	&CN_st_WorkFlow_Table.CN_st_AgreeOn_Send_Basic,sizeof(st_AgreeOn_Send_Basic));

	CN_st_Fun_AscNumber.MoveByte(&ptst_AgreeOn_Send_UploaderPar->CN_st_WorkVal_Tabel,
	&CN_st_WorkFlow_Table.CN_st_WorkVal_Tabel,sizeof(st_WorkVal_Tabel));
	return CN_st_Fun_Tzv21.Write(fd,&CN_Pu_st_st_AgreeOn_Dev_WritePar,&Oper);
}
/*================================================日志文件查找===================================================*/
static uint16 UploaderLog(uint8 fd,void *Buf)
{	st_AgreeOn_LookLog	*ptst_AgreeOn_LookLog;
	ptst_AgreeOn_LookLog=Buf;
	if(ptst_AgreeOn_LookLog->Type!=De_AgreeOn_LookLog_Type_Pone)
		return UpLoaderLog_Par(fd,ptst_AgreeOn_LookLog);
	else
		return UpLoaderJpHistory(fd,ptst_AgreeOn_LookLog);
}

static uint16 UpLoaderJpHistory(uint8 fd,st_AgreeOn_LookLog	*ptst_AgreeOn_LookLog)
{	st_NoFlow_Table	CN_st_NoFlow_Table;
	uint16 Cuit,i,Number,Result;
	Cuit=CN_st_Fun_File.GetJlNum(CN_st_File_fd.NoFlowfd);
	for(i=0,Number=0;i<Cuit;i++)
	{	CN_st_Fun_File.ReadRecoder(CN_st_File_fd.NoFlowfd,i+1,&CN_st_NoFlow_Table);
		if((CN_st_NoFlow_Table.ID!=De_Access_Type_HelpVid)&&(CN_st_NoFlow_Table.ID!=De_Access_Type_WaringParVid))
			continue;
	   	if((Result=LoaderJpgData(i+1,fd))!=De_Suc_AppSendAgreeOn)
			return Result;
	}
	if(Number==0)
		;				//应答失败
   	return De_Suc_AppSendAgreeOn; 
}

static uint16 LoaderJpgData(uint16 Recoder,uint8 fd)
{	st_AgreeOn_Send_LogAndNoSem	*ptst_st_AgreeOn_Send_LogAndNoSem;
	st_WorkFlow_Table	CN_st_WorkFlow_Table;
	st_AgreeOn_Send_UploaderJpg1	*ptst_AgreeOn_Send_UploaderJpg1;
	uint32 iSize;
	uint16 Result,Len,i,ReLen;
	uint8 Oper;
	ptst_st_AgreeOn_Send_LogAndNoSem=CN_Pu_st_st_AgreeOn_Dev_WritePar.Buf;
	ptst_AgreeOn_Send_UploaderJpg1=(st_AgreeOn_Send_UploaderJpg1	*)(X_BUF+512);
	ptst_AgreeOn_Send_UploaderJpg1->Type=2;									//历史照片
	CN_st_Fun_TakeData.GetFlowWaringType(Recoder,&ptst_AgreeOn_Send_UploaderJpg1->Type);
	CN_st_Fun_TakeData.ReadFlow(Recoder,&CN_st_WorkFlow_Table);
	CN_st_Fun_AscNumber.MoveByte(&ptst_AgreeOn_Send_UploaderJpg1->CN_st_AgreeOn_Send_Basic,
	&CN_st_WorkFlow_Table.CN_st_AgreeOn_Send_Basic,sizeof(st_AgreeOn_Send_Basic));

	iSize=CN_st_Fun_TakeData.GetPhonesSize(CN_st_WorkFlow_Table.PhotoAdree);
	ptst_AgreeOn_Send_UploaderJpg1->SecSum=iSize/(sizeof(ptst_AgreeOn_Send_UploaderJpg1->Buf)-27);
	if(iSize%(sizeof(ptst_AgreeOn_Send_UploaderJpg1->Buf)-27))
		ptst_AgreeOn_Send_UploaderJpg1->SecSum++;
	for(i=0;i<ptst_AgreeOn_Send_UploaderJpg1->SecSum;i++)
	{	Len=(sizeof(ptst_AgreeOn_Send_UploaderJpg1->Buf)-27);
		if((i*sizeof(ptst_AgreeOn_Send_UploaderJpg1->Buf)+Len)>iSize)
			Len=iSize-i*(sizeof(ptst_AgreeOn_Send_UploaderJpg1->Buf)-27);
		CN_st_Fun_TakeData.GetPhoneCut(Recoder,i*(sizeof(ptst_AgreeOn_Send_UploaderJpg1->Buf)-27),
		Len,ptst_AgreeOn_Send_UploaderJpg1->Buf);		
		ptst_AgreeOn_Send_UploaderJpg1->SizeofBuf=Len;
		ptst_AgreeOn_Send_UploaderJpg1->SecNumber=i+1;
		CN_st_Fun_Tz_Send.Write(ptst_st_AgreeOn_Send_LogAndNoSem->X_BUF,ptst_AgreeOn_Send_UploaderJpg1,&ReLen,
		De_Dev_Order_UploaderJpg1);
		ptst_st_AgreeOn_Send_LogAndNoSem->DataLen[ptst_st_AgreeOn_Send_LogAndNoSem->Number++]=ReLen;
		if((Result=CN_st_Fun_Tzv21.Write(fd,&CN_Pu_st_st_AgreeOn_Dev_WritePar,&Oper))!=De_Suc_AgreeOn)
			return Result;
		CN_Pu_st_st_AgreeOn_Dev_WritePar.OrderNumber++;
		ptst_st_AgreeOn_Send_LogAndNoSem->Number=0;
	}
	return De_Suc_AppSendAgree;		
}
/*==========================================上传报警参数=======================================================*/
static uint16 UpLoaderWarning(uint8 fd,void *Buf)
{	st_AgreeOn_SetVidType  *ptst_AgreeOn_SetVidType;
	uint8 Oper;
	ptst_AgreeOn_SetVidType=CN_Pu_st_st_AgreeOn_Dev_WritePar.Buf;
	if(CN_st_Fun_File.ReadRecoder(CN_st_File_fd.WaringTermfd,0,ptst_AgreeOn_SetVidType)!=De_Suc_File)
		;				//应答错误
	else
		return CN_st_Fun_Tzv21.Write(fd,&CN_Pu_st_st_AgreeOn_Dev_WritePar,&Oper);
	return De_Suc_AppSendAgreeOn;
}
/*============================================进出区域报警=====================================================*/
static uint16 OutRoadMap(uint8 fd,void *Buf)
{	st_Area_Infor_Table	CN_st_Area_Infor_Table;
	st_AgreeOn_Send_OutRoadMap	*ptst_AgreeOn_Send_OutRoadMap;
	st_OutRoadMap_Input			*ptst_OutRoadMap_Input;
	uint8 Oper;
	ptst_OutRoadMap_Input=Buf;
	ptst_AgreeOn_Send_OutRoadMap=CN_Pu_st_st_AgreeOn_Dev_WritePar.Buf;
	CN_st_Fun_File.ReadRecoder(CN_st_File_fd.Areafd,0,&CN_st_Area_Infor_Table);
	ptst_AgreeOn_Send_OutRoadMap->Type=CN_st_Area_Infor_Table.
	CN_st_Area_Infor_File[ptst_OutRoadMap_Input->Number].Type;
	ptst_AgreeOn_Send_OutRoadMap->ID=CN_st_Area_Infor_Table.
	CN_st_Area_Infor_File[ptst_OutRoadMap_Input->Number].ID;
	ptst_AgreeOn_Send_OutRoadMap->InputOrOut=ptst_OutRoadMap_Input->OutOrIn;
	CN_st_Fun_AscNumber.MoveByte(&ptst_AgreeOn_Send_OutRoadMap->CN_st_AgreeOn_Send_Basic,
	&App_CN_st_WorkFlow_Table.CN_st_AgreeOn_Send_Basic,sizeof(st_AgreeOn_Send_Basic));
	return CN_st_Fun_Tzv21.Write(fd,&CN_Pu_st_st_AgreeOn_Dev_WritePar,&Oper);
}
/*=========================================上传压缩数据回传数据============================================================*/
static uint16 UpLoaderReduce1(uint8 fd,void *Buf) 								//目前只解压定位数据
{	st_Reduce_Table	*ptst_Reduce_Table;
	uint8 Oper;
	uint16 *Recoder;
	Recoder=Buf;
	ptst_Reduce_Table=CN_Pu_st_st_AgreeOn_Dev_WritePar.Buf;
	CN_st_Fun_TakeData.ReadFlow(*Recoder,ptst_Reduce_Table);
	ptst_Reduce_Table->ReadParTable=CN_st_Fun_TakeData.ReadParTable;
	return CN_st_Fun_Tzv21.Write(fd,&CN_Pu_st_st_AgreeOn_Dev_WritePar,&Oper);					
}
/*==============================================上传驾驶员信息===========================================================*/
static uint16 UpLoaderDriver(uint8 fd,void *Buf)						//
{	union
	{	st_WorkFlow_Table	CN_st_WorkFlow_Table;
		st_AgreeOn_Driver	CN_st_AgreeOn_Driver;
	}un;
	st_AgreeOn_Send_UpLoaderDriver	*ptst_AgreeOn_Send_UpLoaderDriver;
	uint16 *Recoder;
	uint8 Oper,Type;
	Recoder=Buf;
	CN_st_Fun_TakeData.ReadFlow(*Recoder,&un.CN_st_WorkFlow_Table);
	CN_st_Fun_AscNumber.MoveByte(&ptst_AgreeOn_Send_UpLoaderDriver->CN_st_AgreeOn_Send_Basic,
	&un.CN_st_WorkFlow_Table.CN_st_AgreeOn_Send_Basic,sizeof(st_AgreeOn_Send_Basic));
	CN_st_Fun_TakeData.GetFlowWaringType(*Recoder,&Type);
	if(Type==De_Access_Type_JugeLog)  						//请求登录
	{	CN_st_Fun_AscNumber.MoveByte(ptst_AgreeOn_Send_UpLoaderDriver->ID,un.CN_st_WorkFlow_Table.DriverID,
		sizeof(un.CN_st_WorkFlow_Table.DriverID));	
		ptst_AgreeOn_Send_UpLoaderDriver->State=0;
	   	
	}
	else if(Type==De_Access_Type_ExitLog)					//退出登录
	{	CN_st_Fun_AscNumber.MoveByte(ptst_AgreeOn_Send_UpLoaderDriver->ID,un.CN_st_WorkFlow_Table.DriverID,
		sizeof(un.CN_st_WorkFlow_Table.DriverID));	
		ptst_AgreeOn_Send_UpLoaderDriver->State=1;
	}
	else 													//非法驾驶员登录
	{	Oper=un.CN_st_WorkFlow_Table.LogState-2;
		CN_st_Fun_File.ReadRecoder(CN_st_File_fd.Driverfd,0,&un.CN_st_AgreeOn_Driver);
		CN_st_Fun_AscNumber.MoveByte(ptst_AgreeOn_Send_UpLoaderDriver->ID,un.CN_st_AgreeOn_Driver.
		CN_st_AgreeOn_Driver_Par[Oper].ID,sizeof(un.CN_st_WorkFlow_Table.DriverID));	
		ptst_AgreeOn_Send_UpLoaderDriver->State=2;
	}
	return CN_st_Fun_Tzv21.Write(fd,&CN_Pu_st_st_AgreeOn_Dev_WritePar,&Oper);
}
/*==================================上传手机短信=============================================================*/
static uint16 UpLoaderHandMess(uint8 fd,void *Buf)						//手机短信
{	st_AgreeOn_Send_UpLoaderHandMess	*ptst_AgreeOn_Send_UpLoaderHandMess;
	st_UpLoaderHandMess_Input	*ptst_UpLoaderHandMess_Input;
	uint8 Oper;
	ptst_UpLoaderHandMess_Input=Buf;
	ptst_AgreeOn_Send_UpLoaderHandMess=CN_Pu_st_st_AgreeOn_Dev_WritePar.Buf;
	CN_st_Fun_AscNumber.MoveByte(&ptst_AgreeOn_Send_UpLoaderHandMess->CN_st_AgreeOn_Send_Basic,
	&App_CN_st_WorkFlow_Table.CN_st_AgreeOn_Send_Basic,sizeof(st_AgreeOn_Send_Basic));

	CN_st_Fun_AscNumber.MoveByte(ptst_AgreeOn_Send_UpLoaderHandMess->ID,
	ptst_UpLoaderHandMess_Input->ID,sizeof(ptst_AgreeOn_Send_UpLoaderHandMess->ID));
	
	CN_st_Fun_AscNumber.MoveByte(ptst_AgreeOn_Send_UpLoaderHandMess->Phone,
	ptst_UpLoaderHandMess_Input->Phone,sizeof(ptst_AgreeOn_Send_UpLoaderHandMess->Phone));
	
	CN_st_Fun_AscNumber.MoveByte(ptst_AgreeOn_Send_UpLoaderHandMess->Cut,
	&ptst_UpLoaderHandMess_Input->Cut,sizeof(ptst_AgreeOn_Send_UpLoaderHandMess->Cut));
	return CN_st_Fun_Tzv21.Write(fd,&CN_Pu_st_st_AgreeOn_Dev_WritePar,&Oper);	
}


/*============================================================================================================*/
static uint16 UploaderJpg2Sig(uint8 fd,uint16 Recoder,uint8 Number)
{	st_WorkFlow_Table	CN_st_WorkFlow_Table;
	st_AgreeOn_Send_UploaderJpg2	*ptst_AgreeOn_Send_UploaderJpg2;
	uint32 iSize;
	uint16 Result,i,Len;
	uint8 Oper;
	ptst_AgreeOn_Send_UploaderJpg2=CN_Pu_st_st_AgreeOn_Dev_WritePar.Buf;
	CN_st_Fun_TakeData.ReadFlow(Recoder,&CN_st_WorkFlow_Table);
	CN_st_Fun_AscNumber.MoveByte(&ptst_AgreeOn_Send_UploaderJpg2->CN_st_AgreeOn_Send_Basic,
	&CN_st_WorkFlow_Table.CN_st_AgreeOn_Send_Basic,sizeof(st_AgreeOn_Send_Basic));

	CN_st_Fun_AscNumber.MoveByte(&ptst_AgreeOn_Send_UploaderJpg2->CN_st_WorkVal_Tabel,
	&CN_st_WorkFlow_Table.CN_st_WorkVal_Tabel,sizeof(st_WorkVal_Tabel));

	memset(ptst_AgreeOn_Send_UploaderJpg2->CN_st_WorkVal_Tabel.Type,De_st_AgreeOn_Send_Waring_Type_No,
	sizeof(ptst_AgreeOn_Send_UploaderJpg2->CN_st_WorkVal_Tabel.Type));
	ptst_AgreeOn_Send_UploaderJpg2->CN_st_WorkVal_Tabel.Type[Number]=De_st_AgreeOn_Send_Waring_Type_Yes;

	iSize=CN_st_Fun_TakeData.GetPhonesSize(CN_st_WorkFlow_Table.PhotoAdree);
	ptst_AgreeOn_Send_UploaderJpg2->SecSum=iSize/sizeof(ptst_AgreeOn_Send_UploaderJpg2->Buf);
	if(iSize%sizeof(ptst_AgreeOn_Send_UploaderJpg2->Buf))
		ptst_AgreeOn_Send_UploaderJpg2->SecSum++;
	for(i=0;i<ptst_AgreeOn_Send_UploaderJpg2->SecSum;i++)
	{	Len=sizeof(ptst_AgreeOn_Send_UploaderJpg2->Buf);
		if((i*sizeof(ptst_AgreeOn_Send_UploaderJpg2->Buf)+Len)>iSize)
			Len=iSize-i*sizeof(ptst_AgreeOn_Send_UploaderJpg2->Buf);
		CN_st_Fun_TakeData.GetPhoneCut(Recoder,i*sizeof(ptst_AgreeOn_Send_UploaderJpg2->Buf),
		Len,ptst_AgreeOn_Send_UploaderJpg2->Buf);		
		ptst_AgreeOn_Send_UploaderJpg2->SizeofBuf=Len;
		ptst_AgreeOn_Send_UploaderJpg2->SecNumber=i+1;
		if((Result=CN_st_Fun_Tzv21.Write(fd,&CN_Pu_st_st_AgreeOn_Dev_WritePar,&Oper))!=De_Suc_AgreeOn)
			return Result;
		CN_Pu_st_st_AgreeOn_Dev_WritePar.OrderNumber++;
	}
	return De_Suc_AppSendAgree;		
}
static uint16 UpLoaderLog_Par(uint8 fd,st_AgreeOn_LookLog	*ptst_AgreeOn_LookLog)
{	st_AgreeOn_Send_LogAndNoSem	*ptst_st_AgreeOn_Send_LogAndNoSem;
	st_NoFlow_Table	CN_st_NoFlow_Table;
	st_st_AgreeOn_Dev_WritePar	CN_st_st_AgreeOn_Dev_WritePar;
	uint8 Oper;
	uint16 Cuit,DataLen,ReDataLen,Number,i,Result;
	ptst_st_AgreeOn_Send_LogAndNoSem=CN_Pu_st_st_AgreeOn_Dev_WritePar.Buf;			//发送结构体
	Cuit=CN_st_Fun_File.GetJlNum(CN_st_File_fd.NoFlowfd);				
	for(i=0,DataLen=0,Number=0;i<Cuit;i++)
	{	CN_st_Fun_File.ReadRecoder(CN_st_File_fd.NoFlowfd,i+1,&CN_st_NoFlow_Table);
		if(ptst_AgreeOn_LookLog->Type==De_AgreeOn_LookLog_Type_Track)
		{	if(CN_st_NoFlow_Table.ID!=De_Access_Type_Track)
				continue;
		}
		else if(ptst_AgreeOn_LookLog->Type==De_AgreeOn_LookLog_Type_WorkPar)
		{	if(CN_st_NoFlow_Table.ID!=De_Access_Type_WorkPar)
				continue;
		}
		else
		{	if((CN_st_NoFlow_Table.ID!=De_Access_Type_ReduceWork)&&(CN_st_NoFlow_Table.ID!=
			De_Access_Type_ReduceTrack))
				continue;
		}				
		if(!((CN_st_Fun_AscNumber.CompareVa(CN_st_NoFlow_Table.DateTimer,ptst_AgreeOn_LookLog->StartDateTimer,4,De_AscNumber_Va_Big)!=De_AscNumber_Va_True)
		&&(CN_st_Fun_AscNumber.CompareVa(ptst_AgreeOn_LookLog->EndDateTimer,CN_st_NoFlow_Table.DateTimer,4,De_AscNumber_Va_Big)!=De_AscNumber_Va_True)))
			continue;
		Number++;
		if(ptst_AgreeOn_LookLog->Type==De_AgreeOn_LookLog_Type_Track)
			TrackDataExplain(i+1,ptst_st_AgreeOn_Send_LogAndNoSem->X_BUF+DataLen,&ReDataLen);
		else if(ptst_AgreeOn_LookLog->Type==De_AgreeOn_LookLog_Type_WorkPar)
			WorkParDataExpalin(i+1,ptst_st_AgreeOn_Send_LogAndNoSem->X_BUF+DataLen,&ReDataLen);
		else
			UpLoaderReduce(i+1,ptst_st_AgreeOn_Send_LogAndNoSem->X_BUF+DataLen,&ReDataLen);
		if((DataLen+ReDataLen+(ptst_st_AgreeOn_Send_LogAndNoSem->Number+1)*2+42)>512)
		{	CN_st_Fun_AscNumber.MoveByte(&ptst_st_AgreeOn_Send_LogAndNoSem->CN_Ba_st_AgreeOn_Send_Basic,
			&App_CN_st_WorkFlow_Table.CN_st_AgreeOn_Send_Basic,sizeof(st_AgreeOn_Send_Basic));
			if((Result=CN_st_Fun_Tzv21.Write(fd,&CN_st_st_AgreeOn_Dev_WritePar,&Oper))!=De_Suc_AppSendAgreeOn)	
				return Result;
			CN_st_st_AgreeOn_Dev_WritePar.OrderNumber++;
			CN_st_Fun_AscNumber.ClsArray(ptst_st_AgreeOn_Send_LogAndNoSem,sizeof(st_AgreeOn_Send_LogAndNoSem));
			i--;
			DataLen=0;
			continue;
		}
		DataLen+=ReDataLen;
		ptst_st_AgreeOn_Send_LogAndNoSem->DataLen[ptst_st_AgreeOn_Send_LogAndNoSem->Number++]=ReDataLen;
	}
	if(ptst_st_AgreeOn_Send_LogAndNoSem->Number!=0)
	{	if((Result=CN_st_Fun_Tzv21.Write(fd,&CN_st_st_AgreeOn_Dev_WritePar,&Oper))!=De_Suc_AppSendAgreeOn)	
			return Result;
	}
	if(Number==0)			//无查找历史记录
	{	;	//应答错误
	}
	return De_Suc_AppSendAgreeOn;
}


static uint16 TrackDataExplain(uint16 Recoder,uint8 *Data,uint16 *ReLen)
{	st_WorkFlow_Table	CN_st_WorkFlow_Table;
   	CN_st_Fun_TakeData.ReadFlow(Recoder,&CN_st_WorkFlow_Table);
	CN_st_Fun_Tz_Send.Write(Data,&CN_st_WorkFlow_Table.CN_st_AgreeOn_Send_Basic,ReLen,De_Dev_Order_Orientation);
	return De_Suc_AppSendAgree;
}
static uint16 UpLoaderDriverExplain(uint16 Recoder,uint8 *Data,uint16 *ReLen)						//
{	union
	{	st_WorkFlow_Table	CN_st_WorkFlow_Table;
		st_AgreeOn_Driver	CN_st_AgreeOn_Driver;
	}un;
	st_AgreeOn_Send_UpLoaderDriver	CN_st_AgreeOn_Send_UpLoaderDriver;
	uint8 Oper,Type;
	CN_st_Fun_TakeData.ReadFlow(Recoder,&un.CN_st_WorkFlow_Table);
	CN_st_Fun_AscNumber.MoveByte(&CN_st_AgreeOn_Send_UpLoaderDriver.CN_st_AgreeOn_Send_Basic,
	&un.CN_st_WorkFlow_Table.CN_st_AgreeOn_Send_Basic,sizeof(st_AgreeOn_Send_Basic));
	CN_st_Fun_TakeData.GetFlowWaringType(Recoder,&Type);
	if(Type==De_Access_Type_JugeLog)  						//请求登录
	{	CN_st_Fun_AscNumber.MoveByte(CN_st_AgreeOn_Send_UpLoaderDriver.ID,un.CN_st_WorkFlow_Table.DriverID,
		sizeof(un.CN_st_WorkFlow_Table.DriverID));	
		CN_st_AgreeOn_Send_UpLoaderDriver.State=0;
	   	
	}
	else if(Type==De_Access_Type_ExitLog)					//退出登录
	{	CN_st_Fun_AscNumber.MoveByte(CN_st_AgreeOn_Send_UpLoaderDriver.ID,un.CN_st_WorkFlow_Table.DriverID,
		sizeof(un.CN_st_WorkFlow_Table.DriverID));	
		CN_st_AgreeOn_Send_UpLoaderDriver.State=1;
	}
	else 													//非法驾驶员登录
	{	Oper=un.CN_st_WorkFlow_Table.LogState-2;
		CN_st_Fun_File.ReadRecoder(CN_st_File_fd.Driverfd,0,&un.CN_st_AgreeOn_Driver);
		CN_st_Fun_AscNumber.MoveByte(CN_st_AgreeOn_Send_UpLoaderDriver.ID,un.CN_st_AgreeOn_Driver.
		CN_st_AgreeOn_Driver_Par[Oper].ID,sizeof(un.CN_st_WorkFlow_Table.DriverID));	
		CN_st_AgreeOn_Send_UpLoaderDriver.State=2;
	}
	return CN_st_Fun_Tz_Send.Write(Data,&CN_st_AgreeOn_Send_UpLoaderDriver,ReLen,De_Dev_Order_UpLoaderDriver);
	//return CN_st_Fun_Tzv21.Write(fd,&CN_Pu_st_st_AgreeOn_Dev_WritePar,&Oper);
}
static uint16 WorkParDataExpalin(uint16 Recoder,uint8 *Data,uint16 *ReLen)
{	st_WorkFlow_Table	CN_st_WorkFlow_Table;
	st_AgreeOn_Send_UploaderPar	CN_st_AgreeOn_Send_UploaderPar;
   	CN_st_Fun_TakeData.ReadFlow(Recoder,&CN_st_WorkFlow_Table);
	CN_st_Fun_AscNumber.MoveByte(&CN_st_AgreeOn_Send_UploaderPar.CN_st_AgreeOn_Send_Basic,
	&CN_st_WorkFlow_Table.CN_st_AgreeOn_Send_Basic,sizeof(st_AgreeOn_Send_Basic));
	CN_st_Fun_AscNumber.MoveByte(&CN_st_AgreeOn_Send_UploaderPar.CN_st_WorkVal_Tabel,
	&CN_st_WorkFlow_Table.CN_st_WorkVal_Tabel,sizeof(st_WorkVal_Tabel));
	CN_st_Fun_Tz_Send.Write(Data,&CN_st_AgreeOn_Send_UploaderPar,ReLen,De_Dev_Order_UploaderPar);
	return De_Suc_AppSendAgree;
}
static uint16 UpLoaderReduce(uint16 Recoder,uint8 *Data,uint16 *ReLen)	//目前只解压定位数据
{	st_Reduce_Table	CN_st_Reduce_Table;
	CN_st_Fun_TakeData.ReadFlow(Recoder,&CN_st_Reduce_Table);
	CN_st_Reduce_Table.ReadParTable=CN_st_Fun_TakeData.ReadParTable;
	CN_st_Fun_Tz_Send.Write(Data,&CN_st_Reduce_Table,ReLen,De_Dev_Order_UploaderPar);
	return De_Suc_AppSendAgree;				
}

static void SendLogin(void) 				//重新登录命令
{	CN_st_Fun_OpenAndClose.OpenGprsNo(1);
}
