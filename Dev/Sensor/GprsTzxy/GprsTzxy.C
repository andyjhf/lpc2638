#define De_GprsTzxy_Compiler
#include "GprsTzxy.h"
static uint16 Init(void)
{	uint8 i;
	if(GprsSem!=NULL)
		return De_Suc_Sensor;
	for(i=0;i<De_GprsTzxy_Dev_Number;i++)
	{	CN_State[i]=De_GprsTzxy_Fun_Close;
	 	CN_Gprsfd[i]=De_GprsTzxy_Nofd;
	}			
	if((GprsSem=OSSemCreate(1))==NULL)
		return De_Erro_GprsTzxy_Init;
	return De_Suc_Sensor;
}
static uint16 Open(st_Sensor_DataPar	*ptst_Sensor_DataPar,uint8 *fd)
{	uint8 err;
	OSSemPend(GprsSem, 0, &err);
	for(err=0;err<De_GprsTzxy_Dev_Number;err++)
	{	if(CN_State[err]==De_GprsTzxy_Fun_Close)
			break;
	}

	if(err==De_GprsTzxy_Dev_Number)
	{	OSSemPost(GprsSem);
		return De_Erro_GprsTzxy_OverMaxNumber;
	}
	CN_State[err]=De_GprsTzxy_Fun_Open;
	*fd=err;
	CN_Gprsfd[err]=ptst_Sensor_DataPar->Addree;
	OSSemPost(GprsSem);
	return De_Suc_Sensor;
}
static uint16 Close(uint8 fd)
{	uint8 err;
	OSSemPend(GprsSem, 0, &err);
	if(fd>=De_GprsTzxy_Dev_Number)
	{	OSSemPost(GprsSem);
		return De_Erro_GprsTzxy_OverMaxNumber;
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
		return De_Erro_GprsTzxy_OverMaxNumber;
	OSSemPend(GprsSem, 0, &err);
	ptst_Dev_Tzxy_Send=SendBuf;
	if(ptst_Dev_Tzxy_Send->ResultOrSend==De_Tzxy_SendBuf_Send)
	{	Result=CN_st_Fun_Gprs.SendIP(CN_Gprsfd[fd],ptst_Dev_Tzxy_Send->Buf,ptst_Dev_Tzxy_Send->SizeofBuf);
		OSSemPost(GprsSem);
		return Result;
	}
	ptst_Dev_Tzxy_Agree=AgreeBuf;
	Result=CN_st_Fun_Gprs.ReadIP(CN_Gprsfd[fd],ptst_Dev_Tzxy_Agree->Buf,&ptst_Dev_Tzxy_Agree->SizeofBuf);
	OSSemPost(GprsSem);
	return Result;
}
