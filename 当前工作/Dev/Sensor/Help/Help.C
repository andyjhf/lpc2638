#define De_Help_Compiler
#include "Help.h"
static uint16 Init(void)
{	if(ACCSem!=NULL)
		return De_Suc_Sensor;
	if((ACCSem=OSSemCreate(1))==NULL)
		return De_Erro_Help_Init;
	CN_State=De_Acc_Fun_Close;
	return De_Suc_Sensor;
}
static uint16 Open(st_Sensor_DataPar	*ptst_Sensor_DataPar,uint8 *fd)
{	uint8 err;
	OSSemPend(ACCSem, 0, &err);
	if(CN_State==De_Acc_Fun_Open)
	{	OSSemPost(ACCSem);
		return De_Erro_Help_OverMaxNumber;
	}
	CN_State=De_Acc_Fun_Open;
	*fd=0;
	OSSemPost(ACCSem);
	return De_Suc_Sensor;
}
static uint16 Close(uint8 fd)
{	uint8 err;
	OSSemPend(ACCSem, 0, &err);
	if(fd!=0)
	{	OSSemPost(ACCSem);
		return De_Erro_Help_OverMaxNumber;
	}
	OSSemPost(ACCSem);
	CN_State=De_Acc_Fun_Close;
	return De_Suc_Sensor;
}
static uint16 Read(uint8 fd,void *SendBuf,void *AgreeBuf)
{	uint8 *BigTimer;
	uint8 *OnOrOff;
	uint32 AccTimer;
	uint8 err;
	
	OSSemPend(ACCSem, 0, &err);
	if(fd!=0)
	{	OSSemPost(ACCSem);
		return De_Erro_Help_OverMaxNumber;
	}
	if(CN_State!=De_Acc_Fun_Open)
	{	OSSemPost(ACCSem);
		return De_Erro_Help_OverMaxNumber;
	}
	OnOrOff=AgreeBuf;
	BigTimer=SendBuf;
	*OnOrOff=De_Sensor_ACC_Close;
	if(De_IO_Acc_In==0)
	{	AccTimer=GetTimeAdd(DateTime,BigTimer);
		if(AccTimer>=3)
			*OnOrOff=De_Sensor_ACC_Open;
	}
	else
	{	CN_st_Fun_AscNumber.MoveByte(DateTime,BigTimer,sizeof(DateTime));
	}
	OSSemPost(ACCSem);		
	return De_Suc_Sensor;
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
