#define De_SensorContr_Compiler
#include "SensorContr.h"
static uint16 Init(void)
{	uint8 i;
	if(SensorContrSem!=NULL)
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

static uint16 Open(uint16 Par,st_Affair_Sensor	*ptst_Affair_Sensor,uint8 *fd)
{	uint8 i,err;
	for(i=0;i<sizeof(CN_Ba_OpenTermPar)/sizeof(uint16);i++)
	{	if(Par==CN_Ba_OpenTermPar[i])
			break;
	}
	if(i==sizeof(CN_Ba_OpenTermPar)/sizeof(uint16))
		return De_Erro_SensorContr_NoPar;
	for(i=0;i<De_Affair_Sensor_MaxNumber;i++)
	{	if(CN_st_Affair_Sensor_OperData.State[i]!=De_Affair_Sensor_Fun_Open)
			break;
	}
	if(i==De_Affair_Sensor_MaxNumber)
		return De_Erro_SensorContr_OverMaxNumber;
	OSSemPend(SensorContrSem, 0, &err);
	CN_st_Fun_AscNumber.MoveByte(&CN_st_Affair_Sensor[i],ptst_Affair_Sensor,sizeof(st_Affair_Sensor));
	CN_st_Affair_Sensor_OperData.Par[i]=Par;
	CN_st_Affair_Sensor_OperData.State[i]=De_Affair_Sensor_Fun_Open;
	OSSemPost(SensorContrSem);
	return De_Suc_SensorContr;				
}
static uint16 Write(uint8 fd,void *SendBuf,void *AgreeBuf)
{	uint8 err;
	uint16 Result;
	OSSemPend(SensorContrSem, 0, &err);
	Result=CN_st_Fun_Sensor.Read(fd,SendBuf,AgreeBuf);
	OSSemPost(SensorContrSem);
	return Result;
}
static uint16 Close(uint8 fd)
{	uint8 err;
	if(fd>De_Affair_Sensor_MaxNumber)
		return De_Erro_SensorContr_OverMaxNumber;
	OSSemPend(SensorContrSem, 0, &err);
	CN_st_Affair_Sensor_OperData.State[fd]=De_Affair_Sensor_Fun_Close;
	OSSemPost(SensorContrSem);
	return De_Suc_SensorContr;
}

static void Task(void *pData)
{	st_Display_Send	CN_st_Display_Send;
	st_Display_Agree	CN_st_Display_Agree;
	uint8 DateTime[7];
	uint16 Result;
	uint8 i,err;
	for(;;OSTimeDly(De_SensorContr_TaskDly),OSSemPost(SensorContrSem))
	{	OSSemPend(SensorContrSem, 0, &err);
		CN_st_Fun_RTC.Read(DateTime);
		for(i=0;i<De_Affair_Sensor_MaxNumber;i++)
		{	if(CN_st_Affair_Sensor_OperData.State[i]!=De_Affair_Sensor_Fun_Open)
				continue;
		   	if(CN_st_Fun_Sensor.GetPar2ID(CN_st_Affair_Sensor_OperData.Par[i],&err)!=De_Suc_Sensor)
				continue;
			if(CN_st_Affair_Sensor_OperData.Par[i]!=De_Sensor_WordPar_Display)
			{	Result=CN_st_Fun_Sensor.Read(err,DateTime,X_BUF);
				if(Result==De_Suc_Sensor)
				{	if(CN_st_Affair_Sensor[i].ptFunc!=NULL)
						CN_st_Affair_Sensor[i].ptFunc(CN_st_Affair_Sensor_OperData.Par[i],X_BUF,DateTime);	
				}
			}
			else
			{	CN_st_Display_Send.SendOrAgree=De_Sensor_Display_Agree;
				CN_st_Display_Agree.AgreeData=X_BUF;
				if((Result=CN_st_Fun_Sensor.Read(err,&CN_st_Display_Send,&CN_st_Display_Agree))==De_Suc_Sensor)	
				{	if(CN_st_Affair_Sensor[i].ptFunc!=NULL)
						CN_st_Affair_Sensor[i].ptFunc(CN_st_Affair_Sensor_OperData.Par[i],&CN_st_Display_Agree,DateTime);	
				}
			}
		}				
	}
}
