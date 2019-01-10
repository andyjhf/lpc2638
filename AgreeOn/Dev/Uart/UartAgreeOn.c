#define De_UartAgreeOn_Compiler
#include "UartAgreeOn.h"
static uint16 Init(void)
{	if(UartAgreeOnSem!=NULL)
		return De_Suc_AgreeOn_Dev_Uart;
	if((UartAgreeOnSem=OSSemCreate(1))==NULL)
		return De_Erro_AgreeOn_Dev_Uart_NoInit;
	return De_Suc_AgreeOn_Dev_Uart;		
}
static uint16 Open(st_AgreeOn_Dev_Gprs_OpenPar	*ptst_AgreeOn_Dev_Gprs_OpenPar,uint8 fd)
{	uint8 err;
	OSSemPend(UartAgreeOnSem, 0, &err);
	CN_st_Fun_AscNumber.MoveByte(&CN_st_AgreeOn_Dev_Gprs_OpenPar,ptst_AgreeOn_Dev_Gprs_OpenPar,sizeof(st_AgreeOn_Dev_Gprs_OpenPar));		
	State=De_AgreeOn_Dev_Uart_Open;
	Gprsfd=fd;
	OSSemPost(UartAgreeOnSem);
	return De_Suc_AgreeOn_Dev_Uart;
}
static uint16 Close(void)
{	uint8 err;
	OSSemPend(UartAgreeOnSem, 0, &err);
	State=De_AgreeOn_Dev_Uart_Close;
	OSSemPost(UartAgreeOnSem);
	return De_Suc_AgreeOn_Dev_Uart;
}
static uint16 Read(st_st_AgreeOn_Dev_Gprs_Par	*ptst_st_AgreeOn_Dev_Gprs_Par)
{	uint16 Result;
	uint8 err;
	OSSemPend(UartAgreeOnSem, 0, &err);
	Result=Read1(ptst_st_AgreeOn_Dev_Gprs_Par);
	OSSemPost(UartAgreeOnSem);
	return Result;
}
static uint16 Write(st_st_AgreeOn_Dev_Gprs_Par	*ptst_st_AgreeOn_Dev_Gprs_Par,uint8 *Buf)
{	uint16 Result;
	uint8 err;
	OSSemPend(UartAgreeOnSem, 0, &err);
	Result=Write1(ptst_st_AgreeOn_Dev_Gprs_Par,Buf);
	OSSemPost(UartAgreeOnSem);
	return Result;
}


static uint16 Read1(st_st_AgreeOn_Dev_Gprs_Par	*ptst_st_AgreeOn_Dev_Gprs_Par)		//获取数据
{	uint16 DataLen,ReDataLen;
	uint8 Byte;
	if(State!=De_AgreeOn_Dev_Uart_Open)
		return De_Erro_AgreeOn_Dev_Uart_NoOpen;
   	if(Agree(ptst_st_AgreeOn_Dev_Gprs_Par->Buf,&DataLen)!=De_Suc_AgreeOn_Dev_Uart)
		return De_Erro_AgreeOn_Dev_Uart_NoData;
	if(DataLen<17)			//解析错误
		return De_Erro_AgreeOn_Dev_Uart_Explain;
	if(CN_st_Fun_AscNumber.CompareBuf(ptst_st_AgreeOn_Dev_Gprs_Par->Buf,CN_st_AgreeOn_Dev_Gprs_OpenPar.IMEI,
	sizeof(CN_st_AgreeOn_Dev_Gprs_OpenPar.IMEI))!=0) 	//合法性判断
		return De_Erro_AgreeOn_Dev_Uart_Legality;
	Byte=ptst_st_AgreeOn_Dev_Gprs_Par->Buf[0];
	ReDataLen=Byte*0x100;
	Byte=ptst_st_AgreeOn_Dev_Gprs_Par->Buf[1];
	ReDataLen+=Byte;
	if(ReDataLen>DataLen)
		return De_Erro_AgreeOn_Dev_Uart_Explain;
	ptst_st_AgreeOn_Dev_Gprs_Par->AnswerFlag=ptst_st_AgreeOn_Dev_Gprs_Par->Buf[3];
	Byte=ptst_st_AgreeOn_Dev_Gprs_Par->Buf[11];
	ptst_st_AgreeOn_Dev_Gprs_Par->OrderNumber=Byte*0x100;
	Byte=ptst_st_AgreeOn_Dev_Gprs_Par->Buf[12];			
   	ptst_st_AgreeOn_Dev_Gprs_Par->OrderNumber+=Byte;
	Byte=ptst_st_AgreeOn_Dev_Gprs_Par->Buf[13];
	ptst_st_AgreeOn_Dev_Gprs_Par->OrderID=Byte*0x100;
	Byte=ptst_st_AgreeOn_Dev_Gprs_Par->Buf[14];			
   	ptst_st_AgreeOn_Dev_Gprs_Par->OrderID+=Byte;
	CN_st_Fun_AscNumber.MoveByte(ptst_st_AgreeOn_Dev_Gprs_Par->Buf,ptst_st_AgreeOn_Dev_Gprs_Par->Buf+17,ReDataLen-17);
	ptst_st_AgreeOn_Dev_Gprs_Par->SizeofBuf=ReDataLen-17;
	return De_Suc_AgreeOn_Dev_Uart;
}

static uint16 Write1(st_st_AgreeOn_Dev_Gprs_Par	*ptst_st_AgreeOn_Dev_Gprs_Par,uint8 *Buf)
{	uint16 DataLen;
	uint8 Byte;
	if(State!=De_AgreeOn_Dev_Uart_Open)
		return De_Erro_AgreeOn_Dev_Uart_NoOpen;
	DataLen=ptst_st_AgreeOn_Dev_Gprs_Par->SizeofBuf+17;
	Buf[0]=((DataLen>>8)&0xff);
	Buf[1]=((DataLen)&0xff);
	Buf[2]=2;
	Buf[3]=ptst_st_AgreeOn_Dev_Gprs_Par->AnswerFlag;
	CN_st_Fun_AscNumber.MoveByte(Buf+4,CN_st_AgreeOn_Dev_Gprs_OpenPar.IMEI,7);
	Buf[11]=0x00;
	Buf[12]=0x00;
	Buf[13]=((ptst_st_AgreeOn_Dev_Gprs_Par->OrderNumber>>8)&0xff);
	Buf[14]=((ptst_st_AgreeOn_Dev_Gprs_Par->OrderNumber)&0xff);
	Buf[15]=((ptst_st_AgreeOn_Dev_Gprs_Par->OrderID>>8)&0xff);
	Buf[16]=((ptst_st_AgreeOn_Dev_Gprs_Par->OrderID)&0xff);
	CN_st_Fun_AscNumber.MoveByte(Buf+17,ptst_st_AgreeOn_Dev_Gprs_Par->Buf,ptst_st_AgreeOn_Dev_Gprs_Par->SizeofBuf);
	return CN_st_Fun_Uart.Write(De_Use_UartAgreeOn_Port,Buf,DataLen);
}

static uint16 Agree(uint8 *Buf,uint16 *ReLen)
{	uint16 DataLen;
	uint32 OverTimer;
	if(CN_st_Fun_Uart.Read(De_Use_UartAgreeOn_Port,Buf+1,1)!=1)
		return De_Erro_AgreeOn_Dev_Uart_NoData;
	for(DataLen=2,OverTimer=0;OverTimer<0xfff;WatchDog())
	{	if(CN_st_Fun_Uart.Read(De_Use_UartAgreeOn_Port,Buf+DataLen,1)==0)
			continue;
		DataLen++;
		OverTimer=0;
		if((Buf[DataLen-1]==0x0a)&&(Buf[DataLen-2]==0x0a))
		{	CN_st_Fun_AscNumber.Asc2HexBuf(Buf+1,Buf,DataLen-3);
			*ReLen=(DataLen-3)/2;	
			return De_Suc_AgreeOn_Dev_Uart;	
		}			
	}
	return De_Erro_AgreeOn_Dev_Uart_NoData;
}






