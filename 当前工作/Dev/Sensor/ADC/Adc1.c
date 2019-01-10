#define De_Adc1_Compiler
#include "Adc1.h"
static uint16 Init(void)
{	if(OilSem!=NULL)
		return De_Suc_Sensor;
	if((OilSem=OSSemCreate(1))==NULL)
		return De_Erro_Adc1_Init;
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
	OSSemPost(OilSem);
	return De_Suc_Sensor;

}
static uint16 Close(uint8 fd)
{	uint8 err;
	OSSemPend(OilSem, 0, &err);
	if(fd!=0)
	{	OSSemPost(OilSem);
		return De_Erro_Adc1_OverMaxNumber;
	}
	CN_State=De_Oil_Fun_Close;
	OSSemPost(OilSem);
	return De_Suc_Sensor;

}
static uint16 Read(uint8 fd,void *SendBuf,void *AgreeBuf)
{ 	uint32 *ReBuf;
	uint32 Vol;
	uint16 Result;
	uint8 err;
	OSSemPend(OilSem, 0, &err);
	if(fd!=0)
	{	OSSemPost(OilSem);
		return De_Erro_Adc1_OverMaxNumber;
	}
	if(CN_State!=De_Oil_Fun_Open)
	{	OSSemPost(OilSem);
		return De_Erro_Adc1_Fun_NoOpen;
	}
	if((Result=CN_st_Fun_Adc.Read(De_Oil_Use_Port,&Vol))!=De_Suc_Adc)
	{	OSSemPost(OilSem);
		return Result;
	}		
	*ReBuf=Vol;
	OSSemPost(OilSem);	
	return De_Suc_Sensor;
}

