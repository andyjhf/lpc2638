#define De_UartTzxy_Compiler
#include "UartTzxy.h"
static uint16 Init(void)
{	uint8 i;
	if(GprsSem!=NULL)
		return De_Suc_Sensor;
	for(i=0;i<De_GprsTzxy_Dev_Number;i++)
	{	CN_State[i]=De_GprsTzxy_Fun_Close;
	 	CN_Gprsfd[i]=De_GprsTzxy_Nofd;
	}			
	if((GprsSem=OSSemCreate(1))==NULL)
		return De_Erro_UartTzxy_Init;
	return De_Suc_Sensor;
}
static uint16 Open(st_Sensor_DataPar	*ptst_Sensor_DataPar,uint8 *fd)
{	const st_Da_Uart	CN_Ba_st_Da_Uart={9600,8,1,0};
	uint8 err;
	OSSemPend(GprsSem, 0, &err);
	for(err=0;err<De_GprsTzxy_Dev_Number;err++)
	{	if(CN_State[err]==De_GprsTzxy_Fun_Close)
			break;
	}

	if(err==De_GprsTzxy_Dev_Number)
	{	OSSemPost(GprsSem);
		return De_Erro_UartTzxy_OverMaxNumber;
	}
	CN_State[err]=De_GprsTzxy_Fun_Open;
	*fd=err;
	CN_Gprsfd[err]=ptst_Sensor_DataPar->Addree;
	CN_st_Fun_Uart.Init(CN_Gprsfd[err]);
	CN_st_Fun_Uart.Open(CN_Gprsfd[err],(st_Da_Uart	*)&CN_Ba_st_Da_Uart);
	OSSemPost(GprsSem);
	return De_Suc_Sensor;
}
static uint16 Close(uint8 fd)
{	uint8 err;
	OSSemPend(GprsSem, 0, &err);
	if(fd>=De_GprsTzxy_Dev_Number)
	{	OSSemPost(GprsSem);
		return De_Erro_UartTzxy_OverMaxNumber;
	}
	OSSemPost(GprsSem);
	CN_State[fd]=De_GprsTzxy_Fun_Close;
	return De_Suc_Sensor;
}
static uint16 Read(uint8 fd,void *SendBuf,void *AgreeBuf)
{	st_Dev_Tzxy_Send	*ptst_Dev_Tzxy_Send;
	st_Dev_Tzxy_Agree	*ptst_Dev_Tzxy_Agree;
	uint16 Result;
	uint8 err;
	if((fd>=De_GprsTzxy_Dev_Number)||(CN_State[fd]!=De_GprsTzxy_Fun_Open))
		return De_Erro_UartTzxy_OverMaxNumber;
	OSSemPend(GprsSem, 0, &err);
	ptst_Dev_Tzxy_Send=SendBuf;
	if(ptst_Dev_Tzxy_Send->ResultOrSend==De_Tzxy_SendBuf_Send)
	{	Result=Send(CN_Gprsfd[fd],ptst_Dev_Tzxy_Send->Buf,ptst_Dev_Tzxy_Send->SizeofBuf);
		OSSemPost(GprsSem);
		return Result;
	}
	ptst_Dev_Tzxy_Agree=AgreeBuf;
	Result=Agree(CN_Gprsfd[fd],ptst_Dev_Tzxy_Agree->Buf,&ptst_Dev_Tzxy_Agree->SizeofBuf);
	OSSemPost(GprsSem);
	return Result;
}

static uint16 Agree(uint8 fd,uint8 *Buf,uint16 *ReLen)
{	uint16 DataLen;
	uint32 OverTimer;
	if(CN_st_Fun_Uart.Read(fd,Buf+1,1)!=1)
		return De_Erro_AgreeOn_Dev_Uart_NoData;
	for(DataLen=2,OverTimer=0;OverTimer<0xfff;WatchDog())
	{	if(CN_st_Fun_Uart.Read(fd,Buf+DataLen,1)==0)
			continue;
		DataLen++;
		OverTimer=0;
		if((Buf[DataLen-1]==0x0a)&&(Buf[DataLen-2]==0x0d))
		{	CN_st_Fun_AscNumber.Asc2HexBuf(Buf+1,Buf,DataLen-3);
			*ReLen=(DataLen-3)/2;	
			return De_Suc_Sensor;	
		}			
	}
	return De_Erro_AgreeOn_Dev_Uart_NoData;
}

static uint16 Send(uint8 fd,uint8 *Buf,uint16 DataLen)
{	uint8 SendBuf[2];
	uint16 i;
	for(i=0;i<DataLen;i++,WatchDog())
	{	CN_st_Fun_AscNumber.HexBuf2Asc(&Buf[i],SendBuf,1);
		CN_st_Fun_Uart.Write(fd,SendBuf,2);
	}

	CN_st_Fun_Uart.Write(fd,"\r\n",2);	
 	return 	De_Suc_Sensor;
}


