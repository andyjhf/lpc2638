#define De_Oil_Compiler
#include "Oil.h"
static uint16 Init(void)
{	if(OilSem!=NULL)
		return De_Suc_Sensor;
	if((OilSem=OSSemCreate(1))==NULL)
		return De_Erro_Oil_Init;
	CN_State=De_Oil_Fun_Close;
	return De_Suc_Sensor;	
}
static uint16 Open(st_Sensor_DataPar	*ptst_Sensor_DataPar,uint8 *fd)
{ 	const st_Data_Adc	CN_Ba_st_Data_Adc={1000000,De_Adc_Trans_Precision0,3300};
	uint16 Result;
	uint8 err;
	OSSemPend(OilSem, 0, &err);
	if((Result=CN_st_Fun_Adc.Init())!=De_Suc_Adc)
		return Result;
	if((Result=CN_st_Fun_Adc.Open(De_Oil_Use_Port,(st_Data_Adc	*)&CN_Ba_st_Data_Adc))!=De_Suc_Adc)
	{	OSSemPost(OilSem);
		return Result;
	}
	CN_State=De_Oil_Fun_Open;
	CN_st_Fun_Adc.Read(De_Oil_Use_Port,CN_VoVal);
	CN_Point=1;
	*fd=0;
	CN_st_Fun_AscNumber.ClsArray(DateTime,sizeof(DateTime));
	OSSemPost(OilSem);
	return De_Suc_Sensor;

}
static uint16 Close(uint8 fd)
{	uint8 err;
	OSSemPend(OilSem, 0, &err);
	if(fd!=0)
	{	OSSemPost(OilSem);
		return De_Erro_Oil_OverMaxNumber;
	}
	CN_State=De_Oil_Fun_Close;
	OSSemPost(OilSem);
	return De_Suc_Sensor;

}
static uint16 Read(uint8 fd,void *SendBuf,void *AgreeBuf)
{ 	uint16 *ReBuf;
	uint8 *BigTimer;
	uint32 Vol,Dly;
	uint16 Result;
	uint8 err;
	OSSemPend(OilSem, 0, &err);
	if(fd!=0)
	{	OSSemPost(OilSem);
		return De_Erro_Oil_OverMaxNumber;
	}
	if(CN_State!=De_Oil_Fun_Open)
	{	OSSemPost(OilSem);
		return De_Erro_Oil_Fun_NoOpen;
	}
	if((Result=CN_st_Fun_Adc.Read(De_Oil_Use_Port,&Vol))!=De_Suc_Adc)
	{	OSSemPost(OilSem);
		return Result;
	}
	BigTimer=SendBuf;
	Dly=GetTimeAdd(DateTime,BigTimer);
	if(Dly==0)
		CN_st_Fun_AscNumber.MoveByte(DateTime,BigTimer,sizeof(DateTime));
	else		
	{	if(Dly>=De_Oil_Max_Dly)
		{	CN_st_Fun_Adc.Read(De_Oil_Use_Port,&Vol);	
			if(CN_Point<(sizeof(CN_VoVal)/sizeof(uint32)))
				CN_VoVal[CN_Point++]=Vol;
			else	
			{	CN_st_Fun_AscNumber.MoveByte(CN_VoVal,&CN_VoVal[1],sizeof(CN_VoVal)-sizeof(uint32));
			 	CN_VoVal[sizeof(CN_VoVal)/sizeof(uint32)-1]=Vol;
			}
			CN_st_Fun_AscNumber.MoveByte(DateTime,BigTimer,sizeof(DateTime));
		}
	}
	ReBuf=AgreeBuf;
	for(fd=0,Vol=0;fd<CN_Point;fd++)
		Vol+=CN_VoVal[fd];		
	*ReBuf=Vol/CN_Point;
	OSSemPost(OilSem);	
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


