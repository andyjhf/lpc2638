#define De_Display_Compiler
#include "Display.h"
static uint16 Init(void)
{	if(DisplaySem!=NULL)
		return De_Suc_Sensor;
	if((DisplaySem=OSSemCreate(1))==NULL)
		return De_Erro_Display_Init;
	CN_State=De_Display_Fun_Close;
	return De_Suc_Display;
}
static uint16 Open(st_Sensor_DataPar	*ptst_Sensor_DataPar,uint8 *fd)
{ 	const st_Da_Uart	CN_Ba_st_Da_Uart={9600,8,1,0};
	uint8 err;
	OSSemPend(DisplaySem, 0, &err);
	CN_st_Fun_Uart.Init(De_Display_Use_Port);
	CN_st_Fun_Uart.Close(De_Display_Use_Port);
	CN_st_Fun_Uart.Open(De_Display_Use_Port,(st_Da_Uart	*)&CN_Ba_st_Da_Uart);
	if(CN_State==De_Display_Fun_Open)
	{	OSSemPost(DisplaySem);
		return De_Erro_Display_OverMaxNumber;
	}
	CN_State=De_Display_Fun_Open;
	*fd=0;
	OSSemPost(DisplaySem);
	return De_Suc_Display;
}

static uint16 Read1(uint8 fd,void *SendBuf,void *AgreeBuf)
{	uint16 Result;
	uint8 err;
	OSSemPend(DisplaySem, 0, &err);
	Result=Read(fd,SendBuf,AgreeBuf);
	OSSemPost(DisplaySem);	
	return Result;
}

static uint16 Close(uint8 fd)
{	uint8 err;
	OSSemPend(DisplaySem, 0, &err);
	if(fd!=0)
	{	OSSemPost(DisplaySem);
		return De_Erro_Display_OverMaxNumber;
	}
	OSSemPost(DisplaySem);
	CN_State=De_Display_Fun_Close;
	return De_Suc_Display;
}

static uint16 Read(uint8 fd,void *SendBuf,void *AgreeBuf)
{	st_Display_Agree	CN_st_Display_Agree;
	st_Display_Agree_Answer	CN_st_Display_Agree_Answer;
	st_Display_Send	*ptst_Display_Send;
	uint16 Result;
	uint8 i,Data;
	if(fd!=0)
		return De_Erro_Display_OverMaxNumber;
	if(CN_State!=De_Display_Fun_Open)	
		return De_Erro_Display_OverMaxNumber;
	ptst_Display_Send=SendBuf;
	if(ptst_Display_Send->SendOrAgree==De_Sensor_Display_Agree)					//接受数据
		return Agree(AgreeBuf);	
	else
	{	//while(CN_st_Fun_Uart.Read(De_Display_Use_Port,&Data,1)==1);
		for(i=0;i<sizeof(CN_Ba_st_Host_SendData)/sizeof(st_Host_SendData);i++)	
		{	if(CN_Ba_st_Host_SendData[i].OrderID==ptst_Display_Send->ID)
			{	CN_Ba_st_Host_SendData[i].ptFun(ptst_Display_Send->SendData,ptst_Display_Send->ID);
				break;
			}
		}
		if(i==sizeof(CN_Ba_st_Host_SendData)/sizeof(st_Host_SendData))
			return De_Erro_Display_NoOrder;
		if(CN_Ba_st_Host_SendData[i].Answer==De_Display_Answer_No)
			return De_Suc_Display;
		OSTimeDly(30);
		CN_st_Display_Agree.AgreeData=&CN_st_Display_Agree_Answer;
		if((Result=Agree(&CN_st_Display_Agree))!=De_Suc_Display)
			return Result;
		if((CN_st_Display_Agree_Answer.Result==De_Display_Oper_Suc)&&(CN_st_Display_Agree_Answer.Order==CN_Ba_st_Host_SendData[i].OrderID))
			return De_Suc_Display;
		return De_Erro_Display_Explain;	
	}		
}

/*=============================================================================================================*/
static uint16 Host_Answer(void *Buf,uint8 ID)								//命令应答成功
{	st_Display_Order_Answer	*ptst_Display_Order_Answer;
	uint8 Cut[2];
	ptst_Display_Order_Answer=Buf;
	Cut[0]=ptst_Display_Order_Answer->AnswerID;
	Cut[1]=ptst_Display_Order_Answer->Result;
	Send(ID,Cut,sizeof(Cut));
	return De_Suc_Display;
}
static uint16 Host_DeliverCentr(void *Buf,uint8 ID)
{	st_Display_Order_DeliverCentr	*ptst_Display_Order_DeliverCentr;
	ptst_Display_Order_DeliverCentr=Buf;
	Send(ID,ptst_Display_Order_DeliverCentr->Buf,ptst_Display_Order_DeliverCentr->SizeofBuf);
	return De_Suc_Display;
}
static uint16 Host_SysInfor(void *Buf,uint8 ID)	  							//系统信息
{	uint8 Cut[21];
	st_Display_Order_SysInfor	*ptst_Display_Order_SysInfor;
	ptst_Display_Order_SysInfor=Buf;
	Cut[0]=((ptst_Display_Order_SysInfor->Integral>>8)&0xff);
	Cut[1]=(ptst_Display_Order_SysInfor->Integral&0xff);
	CN_st_Fun_AscNumber.Bcd2Hex(ptst_Display_Order_SysInfor->DateTime+1,Cut+2,1);
	CN_st_Fun_AscNumber.Bcd2Hex(ptst_Display_Order_SysInfor->DateTime+2,Cut+3,1);
	CN_st_Fun_AscNumber.Bcd2Hex(ptst_Display_Order_SysInfor->DateTime+3,Cut+4,1);
	Cut[5]=CN_st_Fun_Date.GetWeek(ptst_Display_Order_SysInfor->DateTime);
	CN_st_Fun_AscNumber.Bcd2Hex(ptst_Display_Order_SysInfor->DateTime+4,Cut+6,1);
	CN_st_Fun_AscNumber.Bcd2Hex(ptst_Display_Order_SysInfor->DateTime+5,Cut+7,1);
	CN_st_Fun_AscNumber.Bcd2Hex(ptst_Display_Order_SysInfor->DateTime+6,Cut+8,1);
	Cut[9]=ptst_Display_Order_SysInfor->GpsState;
	Cut[10]=ptst_Display_Order_SysInfor->VidState;
	Cut[11]=ptst_Display_Order_SysInfor->ContrState;
	Cut[12]=ptst_Display_Order_SysInfor->GprsSem;
	Cut[13]=ptst_Display_Order_SysInfor->Carrier;
	Cut[14]=ptst_Display_Order_SysInfor->CarState;
	Cut[15]=ptst_Display_Order_SysInfor->ExigenceState;
	Cut[16]=ptst_Display_Order_SysInfor->WaringPci;
	Cut[17]=ptst_Display_Order_SysInfor->CarSpeed;
	Cut[18]=ptst_Display_Order_SysInfor->StarNumber;
	Cut[19]=ptst_Display_Order_SysInfor->TallyState;
	Cut[20]=ptst_Display_Order_SysInfor->VolState;
	Send(ID,Cut,sizeof(Cut));
	return De_Suc_Display;
}

static uint16 Host_Phone(void *Buf,uint8 ID)  								//电话指令
{	uint8 Cut[21];
	uint8 DataLen;
	st_Display_Order_Phone	*ptst_Display_Order_Phone;
	ptst_Display_Order_Phone=Buf;
	Cut[0]=ptst_Display_Order_Phone->PhoneType;
	DataLen=CN_st_Fun_AscNumber.Strsize(ptst_Display_Order_Phone->Phone);
	if(DataLen>15)
		DataLen=15;
	CN_st_Fun_AscNumber.MoveByte(Cut+1,ptst_Display_Order_Phone->Phone,DataLen);
	DataLen++;
	Send(ID,Cut,DataLen);
	return De_Suc_Display;	
} 

static uint16 Host_InitStart(void *Buf,uint8 ID)  						//初始化指令开始
{	Send(ID,NULL,0);		
	return De_Suc_Display;
}
static uint16 Host_InitOver(void *Buf,uint8 ID)						  	//初始化指令结束
{	Send(ID,NULL,0);		
	return De_Suc_Display;
}

static uint16 Host_HostSoft(void *Buf,uint8 ID)			   				//升级进度条
{	st_Display_Order_HostSoft	*ptst_Display_Order_HostSoft;
	uint8 Cut;
	ptst_Display_Order_HostSoft=Buf;
	Cut=ptst_Display_Order_HostSoft->Value;
	Send(ID,&Cut,sizeof(Cut));
	return De_Suc_Display;
}

static uint16 Host_ConInfor(void *Buf,uint8 ID)		   						//控制类信息
{	uint8 Cut[100];
	st_Display_Order_ConInfor	*ptst_Display_Order_ConInfor;	
   	uint16 DataLen;
	ptst_Display_Order_ConInfor=Buf;
	Cut[0]=ptst_Display_Order_ConInfor->BeerLen;
   	Cut[1]=ptst_Display_Order_ConInfor->BeerNumber;
	Cut[2]=ptst_Display_Order_ConInfor->VoiceReport;
	DataLen=CN_st_Fun_AscNumber.Strsize(ptst_Display_Order_ConInfor->TextCut);
	if(DataLen>sizeof(Cut)-3)
		DataLen=sizeof(Cut)-3;
   	CN_st_Fun_AscNumber.MoveByte(Cut+3,ptst_Display_Order_ConInfor->TextCut,DataLen);
	DataLen+=3;
	Send(ID,Cut,DataLen);
	return De_Suc_Display;
}

static uint16 Host_ParAnswer(void *Buf,uint8 ID)							//参数查询应答
{	uint8 Cut[512];
	st_Display_Par *ptst_Display_Par;
	uint16 j,DataLen;
	uint8 i;
	ptst_Display_Par=Buf;
	for(i=0,j=0;i<sizeof(ptst_Display_Par->Set);i++)
	{	if(ptst_Display_Par->Set[i]==0)
			continue;
		Cut[j++]=0;
		Cut[j++]=(CN_st_Display_Par_Set[i].Par>>8);
		Cut[j++]=(CN_st_Display_Par_Set[i].Par&0xff);	
		DataLen=App2CommType((void *)((uint32 )CN_st_Display_Par_Set[i].Point+
		(uint32 )(&ptst_Display_Par->CN_st_Display_Par_Cut)),Cut+j+1,i);
		Cut[j]=DataLen;			
		j+=DataLen;
		j++;
	}
	return De_Suc_Display; 
}

static uint16 App2CommType(void *Buf,uint8 *AgreeBuf,uint8 i)
{	union
	{	uint8 *Vauint8;
		uint16 *Vauint16;
		int16 *Vaint16;
		uint32 *Vauint32;
		void *Buf;
	}CN_st_VaTran;
	uint16 DataLen;

	CN_st_VaTran.Buf=Buf;
	if(CN_Ba_st_Display_Par2Type[i].Type==De_Display_Par_Type_int16)
	{	DataLen=Int162Asc(*CN_st_VaTran.Vaint16,AgreeBuf);
	}
	else if(CN_Ba_st_Display_Par2Type[i].Type==De_Display_Par_Type_Asc)
	{	DataLen=CN_st_Fun_AscNumber.Strsize(CN_st_VaTran.Vauint8);
		if(DataLen>CN_st_Display_Par_Set[i].SizeofPoint)
			DataLen=CN_st_Display_Par_Set[i].SizeofPoint;
		CN_st_Fun_AscNumber.MoveByte(AgreeBuf,CN_st_VaTran.Vauint8,DataLen);	
	}
	else if(CN_Ba_st_Display_Par2Type[i].Type==De_Display_Par_Type_IP)
	{	DataLen=CN_st_Fun_AscNumber.IP2Char(*CN_st_VaTran.Vauint32,AgreeBuf,'.');
	}
	else if(CN_Ba_st_Display_Par2Type[i].Type==De_Display_Par_Type_uint16)
	{	DataLen=CN_st_Fun_AscNumber.Algorism2Asc((uint32 )*CN_st_VaTran.Vauint16,AgreeBuf);
	}
	else if(CN_Ba_st_Display_Par2Type[i].Type==De_Display_Par_Type_uint8)
	{	DataLen=CN_st_Fun_AscNumber.Algorism2Asc((uint32 )*CN_st_VaTran.Vauint8,AgreeBuf);	
	}
	else if(CN_Ba_st_Display_Par2Type[i].Type==De_Display_Par_Type_uint32)
	{	
		DataLen=CN_st_Fun_AscNumber.Algorism2Asc((uint32 )*CN_st_VaTran.Vauint32,AgreeBuf);
	}
	else
		DataLen=0;
	return DataLen;
}
static uint16 CommType2App(uint8 *Buf,st_Display_Par *ptst_Display_Par,uint16 Par,uint16 SizeofAgreeBuf)
{	union
	{	uint8 *Vauint8;
		uint16 *Vauint16;
		uint32 *Vauint32;
		void *Buf;
	}CN_st_VaTran;
	uint8 i,DataLen;
   	CN_st_Fun_AscNumber.ClsArray(ptst_Display_Par->Set,sizeof(ptst_Display_Par->Set));
	for(i=0;i<sizeof(CN_st_Display_Par_Set)/sizeof(st_Display_Par_Set);i++)
	{	if(Par==CN_st_Display_Par_Set[i].Par)
			break;
	}
	if(i==sizeof(CN_st_Display_Par_Set)/sizeof(st_Display_Par_Set))
		return ;
	CN_st_VaTran.Buf=(void *)((uint32 )CN_st_Display_Par_Set[i].Point+(uint32 )(&ptst_Display_Par->CN_st_Display_Par_Cut));
	if(CN_Ba_st_Display_Par2Type[i].Type==De_Display_Par_Type_int16)
		*CN_st_VaTran.Vauint16=Asc2Int16(Buf,SizeofAgreeBuf);
	else if(CN_Ba_st_Display_Par2Type[i].Type==De_Display_Par_Type_Asc)
	{	if(SizeofAgreeBuf>CN_st_Display_Par_Set[i].SizeofPoint)
			SizeofAgreeBuf=CN_st_Display_Par_Set[i].SizeofPoint;
		CN_st_Fun_AscNumber.MoveByte(CN_st_VaTran.Vauint8,Buf,DataLen);	
	}
	else if(CN_Ba_st_Display_Par2Type[i].Type==De_Display_Par_Type_IP)
	{	CN_st_Fun_AscNumber.Char2IP(Buf,CN_st_VaTran.Vauint32,'.');
	}
	else if(CN_Ba_st_Display_Par2Type[i].Type==De_Display_Par_Type_uint16)
		*CN_st_VaTran.Vauint16=CN_st_Fun_AscNumber.Asc2Algorism(Buf,SizeofAgreeBuf);
	else if(CN_Ba_st_Display_Par2Type[i].Type==De_Display_Par_Type_uint8)
		*CN_st_VaTran.Vauint8=CN_st_Fun_AscNumber.Asc2Algorism(Buf,SizeofAgreeBuf);	
	else if(CN_Ba_st_Display_Par2Type[i].Type==De_Display_Par_Type_uint32)
		*CN_st_VaTran.Vauint32=CN_st_Fun_AscNumber.Asc2Algorism(Buf,SizeofAgreeBuf);
	ptst_Display_Par->Set[i]=1;
	return De_Suc_Display;
}
/*==========================================底层硬件=========================================================*/
static uint16 Agree(void *AgreeBuf)
{	st_Display_Agree	*ptst_Display_Agree;
	union 
	{	st_Display_Agree_Answer	*ptst_Display_Agree_Answer;
		st_Display_Agree_Phone	*ptst_Display_Agree_Phone;
		st_Display_Agree_SeePar	*ptst_Display_Agree_SeePar;
		st_Display_Agree_SetPar	*ptst_Display_Agree_SetPar;
		st_Display_Agree_Log	*ptst_Display_Agree_Log;
		st_Display_Agree_OnCen	*ptst_Display_Agree_OnCen;
		st_Display_Agree_Voic	*ptst_Display_Agree_Voic;
		st_Display_Par *ptst_Display_Par;
	}CN_st_Un_Explain;
	uint16 DataLen,Result,i;
	uint8 X_BUF[512];
	if((Result=AgreeData(X_BUF,sizeof(X_BUF),&DataLen))!=De_Suc_Display)
		return Result;
	ptst_Display_Agree=AgreeBuf;
	ptst_Display_Agree->ID=X_BUF[3];
	CN_st_Un_Explain.ptst_Display_Agree_Answer=ptst_Display_Agree->AgreeData;
	if(X_BUF[3]==De_Display_Device_Order_Answer)  								//应答指令
	{	CN_st_Un_Explain.ptst_Display_Agree_Answer->Order=X_BUF[4];	
		CN_st_Un_Explain.ptst_Display_Agree_Answer->Result=X_BUF[5];
	}
	else if(X_BUF[3]==De_Display_Device_Order_Phone)							//电话指令
	{	CN_st_Un_Explain.ptst_Display_Agree_Phone->Type=X_BUF[4];
		CN_st_Fun_AscNumber.ClsArray(CN_st_Un_Explain.ptst_Display_Agree_Phone->Phone,15);
		if(DataLen>20)
			DataLen=20;
		CN_st_Fun_AscNumber.MoveByte(CN_st_Un_Explain.ptst_Display_Agree_Phone->Phone,X_BUF+5,DataLen-5);
	}
	else if(X_BUF[3]==De_Display_Device_Order_SeePar)	   		//查询参数命令
	{	CN_st_Un_Explain.ptst_Display_Agree_SeePar->PassWord=X_BUF[4]*0x1000000+X_BUF[5]*0x10000+X_BUF[6]*0x100+X_BUF[7];
	   	Result=DataLen-8;
		Result=Result/2;
		if(Result>20)
			Result=20;
		CN_st_Un_Explain.ptst_Display_Agree_SeePar->ParNumber=Result;
		for(i=0;i<Result;i++)
			CN_st_Un_Explain.ptst_Display_Agree_SeePar->Par[i]=X_BUF[8+i*2]*0x100+X_BUF[8+i*2+1];	
	}
	else if(X_BUF[3]==De_Display_Device_Order_SetPar)			//设置参数命令
	{	CN_st_Un_Explain.ptst_Display_Agree_SetPar->PassWord=X_BUF[4]*0x1000000+X_BUF[5]*0x10000+X_BUF[6]*0x100+X_BUF[7];
	  	CN_st_Un_Explain.ptst_Display_Agree_SetPar->ParID=X_BUF[8]*0x100+X_BUF[9];
	   	CommType2App(X_BUF+9,CN_st_Un_Explain.ptst_Display_Par,De_Display_Device_Order_SetPar,DataLen-9);
	}
	else if(X_BUF[3]==De_Display_Device_Order_Log)				//登录信息
	 	CN_st_Fun_AscNumber.MoveByte(CN_st_Un_Explain.ptst_Display_Agree_Log->SoftEdit,X_BUF+4,2);
	else if(X_BUF[3]==De_Display_Device_Order_OnCen)
		CN_st_Fun_AscNumber.MoveByte(CN_st_Un_Explain.ptst_Display_Agree_OnCen,X_BUF+4,DataLen-4);
	else if(X_BUF[3]==De_Display_Device_Order_Voic)				
	{	CN_st_Un_Explain.ptst_Display_Agree_Voic->VolSize=X_BUF[4];	
	}
	return De_Suc_Display;
}

static uint16 AgreeData(uint8 *AgreeBuf,uint16 SizeofBuf,uint16 *AgreeBufSize)
{	uint32 MaxDelay;
	uint16 DataLen,DataLen1;
	AgreeBuf[0]=0;
	for(;(AgreeBuf[0]!='*');)
	{	if(CN_st_Fun_Uart.Read(De_Display_Use_Port,AgreeBuf,1)==0)
			return De_Erro_Display_NoData;
	}
	DataLen=1;
	for(MaxDelay=0;(MaxDelay<De_Display_MaxDly&&DataLen<SizeofBuf);MaxDelay++,WatchDog())
	{	if(CN_st_Fun_Uart.Read(De_Display_Use_Port,AgreeBuf+DataLen,1)==0)
			continue;
		DataLen++;
		MaxDelay=0;
		if(DataLen<3)
			continue;
		DataLen1=AgreeBuf[1]*0x100+AgreeBuf[2];
		if(DataLen1==DataLen)
			return De_Suc_Display;
	}
	return De_Erro_Display_Explain;
}

static void Send(uint8 ID,uint8 *Buf,uint16 SizeofBuf)	  					//发送数据
{	uint8 Byte;
	uint16 DataLen;
	DataLen=SizeofBuf+5;
	CN_st_Fun_Uart.Write(De_Display_Use_Port,"*",1);
	Byte=((DataLen>>8)&0xff);
	CN_st_Fun_Uart.Write(De_Display_Use_Port,&Byte,1);
	Byte=(DataLen&0xff);
   	CN_st_Fun_Uart.Write(De_Display_Use_Port,&Byte,1);
	CN_st_Fun_Uart.Write(De_Display_Use_Port,&ID,sizeof(ID));
	CN_st_Fun_Uart.Write(De_Display_Use_Port,Buf,SizeofBuf);
   	CN_st_Fun_Uart.Write(De_Display_Use_Port,"#",1);
	while(CN_st_Fun_Uart.Read(De_Display_Use_Port,&Byte,1)==1);
}


static uint16 Int162Asc(uint16 Val,uint8 *Asc)
{	if(Val<0x8000)	
   		return CN_st_Fun_AscNumber.Algorism2Asc((uint32 )Val,Asc);
	else
	{	Asc[0]='-';
		Val=0xffff-Val+1;	
		return CN_st_Fun_AscNumber.Algorism2Asc((uint32 )Val,Asc+1)+1;
	}
} 

static uint16 Asc2Int16(uint8 *Asc,uint8 SizeofAsc)
{	uint16 Result;
	if(Asc[0]=='-')
	{ 	Result=CN_st_Fun_AscNumber.Asc2Algorism(Asc+1,SizeofAsc-1);
		Result=0xffff-Result+1;
	}
	else
		Result=CN_st_Fun_AscNumber.Asc2Algorism(Asc,SizeofAsc);
   	return Result;
}
