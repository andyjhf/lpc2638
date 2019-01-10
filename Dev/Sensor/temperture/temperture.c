#define De_Temperture_Compiler
#include "Temperture.h"


static uint16 Init(void)
{	
	uint8 i;
	if(TempertureSem != NULL)
		return De_Suc_Temperture;
	if((TempertureSem=OSSemCreate(1))==NULL)
		return De_Erro_Temperture_NoInit; 
	for(i=0;i<De_Temperture_Max_Number;i++)
	{
		CN_st_Temperture_Par_Oper[i].State = De_Temperture_State_Close;	
		CN_st_Fun_AscNumber.MoveByte(&CN_st_Temperture_State[i],(st_Sensor_State*)&CN_Ba_st_Temperture_State,	\
									sizeof(st_Sensor_State));
	} 
	CN_st_Fun_AscNumber.ClsArray(DateTime,sizeof(DateTime));
	CN_st_Fun_RTC.Read(DateTime);	
	return De_Suc_Temperture;	
}

static uint16 Open(st_Sensor_DataPar	*ptst_Sensor_DataPar,uint8 *fd)
{
	uint8 i;
	uint16 result;
	uint8 TemperNumber;
	OSSemPend(TempertureSem, 0, &i);
	for(i=0;i<De_Temperture_Max_Number;i++)
	{
		if(CN_st_Temperture_Par_Oper[i].State == De_Temperture_State_Close)
			break;
	}	 
	if(i == De_Temperture_Max_Number)
	{
		OSSemPost(TempertureSem);
		return De_Erro_Temperture_OverMaxNumber;
	}
	TemperNumber = i;
	*fd = TemperNumber;

	for(i=0;i<sizeof(CN_st_Sensor_Par2Type)/sizeof(st_Sensor_Par2Type);i++)
	{	if(CN_st_Sensor_Par2Type[i].WorkPar == ptst_Sensor_DataPar->WorkPar)
			break;
	}
	if(i == sizeof(CN_st_Sensor_Par2Type)/sizeof(st_Sensor_Par2Type))
	{
		OSSemPost(TempertureSem);
		return De_Erro_Temperture_NoWorkPar;	
	}

	if((result = CN_st_Fun_18B20.Init())!= De_Suc_18B20)	//DS18B20初始化失败
	{
		OSSemPost(TempertureSem);
		return result;			
	}
	if((result = CN_st_Fun_18B20.Open(TemperNumber))!= De_Suc_18B20)   //DS18B20打开失败
	{
		OSSemPost(TempertureSem);
		return result;			
	}

	CN_st_Fun_AscNumber.MoveByte(&CN_st_Temperture_Par_Oper[TemperNumber].CN_st_Temperture_DataPar,ptst_Sensor_DataPar,  \
								 sizeof(st_Sensor_DataPar));			
	CN_st_Temperture_Par_Oper[TemperNumber].Type = CN_st_Sensor_Par2Type[i].Type;
	CN_st_Temperture_Par_Oper[TemperNumber].State = De_Temperture_State_Open;

	CN_st_Fun_18B20.Read(TemperNumber,&TemptureValue);
	CN_st_Fun_18B20.Read(TemperNumber,&TemptureValue);
	CN_st_Fun_18B20.Read(TemperNumber,&TemptureValue);
	OSSemPost(TempertureSem);
	return De_Suc_Temperture;		
}

static uint16 Close(uint8 fd)		//关闭
{
	uint8 i;
	OSSemPend(TempertureSem, 0, &i);
	if(fd>=De_Temperture_Max_Number)
		return De_Erro_Temperture_OverMaxNumber;
	if(CN_st_Temperture_Par_Oper[fd].State==De_Temperture_State_Close)
	{
		OSSemPost(TempertureSem);
		return De_Suc_Temperture;
	}
	CN_st_Fun_18B20.Close(fd);
	CN_st_Temperture_Par_Oper[fd].State = De_Temperture_State_Close;
	OSSemPost(TempertureSem);
	return De_Suc_Temperture;
}

static uint16 Read(uint8 fd,void *SendBuf,void *AgreeBuf)
{
	uint8 i;
	uint8 *CurTime;
	uint32 *ReBuf;
	uint32 Dly;	 	
	uint16 result;

	OSSemPend(TempertureSem, 0, &i);

	if(fd >= De_Temperture_Max_Number)
	{
		OSSemPost(TempertureSem);
		return De_Erro_Temperture_OverMaxNumber;
	 }
	if(CN_st_Temperture_Par_Oper[fd].State == De_Temperture_State_Close)
	{
		OSSemPost(TempertureSem);
		return De_Erro_Temperture_Fun_NoOpen;	
	}  
	CurTime = SendBuf;
	Dly = GetTimeAdd(DateTime,CurTime);
	if(Dly==0)
	{
		CN_st_Fun_AscNumber.MoveByte(DateTime,CurTime,sizeof(DateTime));  	
	 }
	else
	{
		if(Dly>=De_Temperture_Max_Dly)
		{
			CN_st_Fun_18B20.Read(fd,&TemptureValue);
			CN_st_Fun_AscNumber.MoveByte(DateTime,CurTime,sizeof(DateTime));			
		}
	}	
	ReBuf  = AgreeBuf;
	*ReBuf = TemptureValue;
	OSSemPost(TempertureSem);
	return result;
}

static uint16 GetState(st_Sensor_State	*ptst_Temperture_State,uint8 fd)	//获取状态
{
	if(fd >= De_Temperture_Max_Number)
		return De_Erro_Temperture_OverMaxNumber;
	if(CN_st_Temperture_Par_Oper[fd].State == De_Temperture_State_Close)
	{
		OSSemPost(TempertureSem);
		return De_Erro_Temperture_Fun_NoOpen;	
	}
	CN_st_Fun_AscNumber.MoveByte(ptst_Temperture_State,&CN_st_Temperture_State[fd],sizeof(st_Sensor_State));  
	return De_Suc_Temperture;
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

