#define De_SensorContr_Compiler
#include "SensorContr.h"
static uint8 Init(void)
{	uint8 i;
	if(SensorContrSem==NULL)
		return De_Suc_SensorContr;
	for(i=0;i<De_Affair_Sensor_MaxNumber;i++)	
	{	CN_st_Fun_AscNumber.MoveByte(&CN_st_Affair_Sensor,(void *)&CN_Ba_st_Affair_Sensor,sizeof(st_Affair_Sensor));
	  	CN_st_Affair_Sensor_OperData.State[i]=De_Affair_Sensor_Fun_Close;
	}
	if((SensorContrSem=OSSemCreate(1))==NULL)
		return De_Erro_SensorContr_Init;
	OSTaskCreate (Task,(void *)0, &STK[De_Stk_Size - 1],De_Task_Number);
	return De_Suc_SensorContr;
}

static uint8 Open(uint8 HardWareID,st_Affair_Sensor	*ptst_Affair_Sensor,uint8 *fd)
{	uint8 i,err;	
	for(i=0;i<De_Affair_Sensor_MaxNumber;i++)
	{	if(CN_st_Affair_Sensor_OperData.State[i]!=De_Affair_Sensor_Fun_Open)
			break;
	}
	if(i==De_Affair_Sensor_MaxNumber)
		return De_Erro_SensorContr_OverMaxNumber;
	OSSemPend(SensorContrSem, 0, &err);
	CN_st_Fun_AscNumber.MoveByte(&CN_st_Affair_Sensor[i],ptst_Affair_Sensor,sizeof(st_Affair_Sensor));
	CN_st_Affair_Sensor_OperData.fd[i]=HardWareID;
	CN_st_Affair_Sensor_OperData.State[i]=De_Affair_Sensor_Fun_Open;
	OSSemPost(SensorContrSem);
	return De_Suc_SensorContr;				
}

static uint8 Close(uint8 fd)
{	uint8 err;
	if(fd>De_Affair_Sensor_MaxNumber)
		return De_Erro_SensorContr_OverMaxNumber;
	OSSemPend(SensorContrSem, 0, &err);
	CN_st_Affair_Sensor_OperData.State[fd]=De_Affair_Sensor_Fun_Close;
	OSSemPost(SensorContrSem);
	return De_Suc_SensorContr;
}

static void Task(void *pData)
{	uint8 DateTime[7];
	uint16 Result;
	uint8 i,err;
	for(i=0;;OSSemPost(SensorContrSem))
	{	OSSemPend(SensorContrSem, 0, &err);
		if(CN_st_Affair_Sensor_OperData.State[i]!=De_Affair_Sensor_Fun_Open)
		{	i++;
			if(i==De_Affair_Sensor_MaxNumber)
				i=0;
			continue;
		}
		CN_st_Fun_RTC.Read(DateTime);
		Result=CN_st_Fun_Sensor.Read(CN_st_Affair_Sensor_OperData.fd[i],DateTime,X_BUF);
		if(Result==De_Suc_Sensor)
		{	if(CN_st_Affair_Sensor[i].ptFunc!=NULL)
				CN_st_Affair_Sensor[i].ptFunc(i,X_BUF,DateTime);	
		}
		CN_st_Fun_Sensor.GetState(&CN_st_Sensor_State,CN_st_Affair_Sensor_OperData.fd[i]);
		if(CN_st_Affair_Sensor[i].GetState!=NULL)
			CN_st_Affair_Sensor[i].GetState(i,&CN_st_Sensor_State);	
		i++;
		if(i==De_Affair_Sensor_MaxNumber)
			i=0;					
	}
}