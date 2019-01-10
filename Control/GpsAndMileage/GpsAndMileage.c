#define De_GpsAndMileage_Compiler
#include "GpsAndMileage.h"

static uint16 Init(void)
{	uint8 i;
	for(i=0;i<De_Affair_GpsAndMileage_MaxNumber;i++)
	{	CN_st_GpsAndMileage_OperData.State[i]=De_GpsAndMileage_State_Close;
		CN_st_GpsAndMileage_OperData.CN_st_Affair_GpsAndMileage[i].CN_st_Affair_RunLen.Fun_SumLen=NULL;
		CN_st_GpsAndMileage_OperData.CN_st_Affair_GpsAndMileage[i].Milage=0;
	}
	CN_st_GpsAndMileage_OperData.CN_st_State_RunLen.GpsState=De_GpsState_OK;
	
	if((GpsAndMileageUseSem=OSSemCreate(1))==NULL)
		return De_Erro_GpsAndMileage_Init;
	OSTaskCreate (Task,(void *)0, &STK[De_Stk_Size - 1],De_Task_Number);
	return De_Suc_GpsAndMileage;	
}
static uint16 Open(st_Affair_Data	*ptst_Affair_Data,st_Affair_RunLen	*ptst_Affair_RunLen,uint8 *fd)
{	uint8 i,err;
	for(i=0;i<De_Affair_GpsAndMileage_MaxNumber;i++)
	{	if(CN_st_GpsAndMileage_OperData.State[i]!=De_GpsAndMileage_State_Open)
			break;
	}
	if(i==De_Affair_GpsAndMileage_MaxNumber)
		return De_Erro_GpsAndMileage_OverMaxNumber;
	OSSemPend(GpsAndMileageUseSem, 0, &err);
	CN_st_Fun_AscNumber.MoveByte(&CN_st_GpsAndMileage_OperData.CN_st_Affair_GpsAndMileage[i].CN_st_Affair_Data,ptst_Affair_Data,sizeof(st_Affair_Data));
	CN_st_Fun_AscNumber.MoveByte(&CN_st_GpsAndMileage_OperData.CN_st_Affair_GpsAndMileage[i].CN_st_Affair_RunLen,ptst_Affair_RunLen,sizeof(st_Affair_RunLen));
	*fd=i;
	CN_st_GpsAndMileage_OperData.State[i]=De_GpsAndMileage_State_Open;
	OSSemPost(GpsAndMileageUseSem);
	return De_Suc_GpsAndMileage;
}
static uint16 Close(uint8 fd)
{	uint8 err;
	if(fd>=De_Affair_GpsAndMileage_MaxNumber)
		return De_Erro_GpsAndMileage_Close;
	OSSemPend(GpsAndMileageUseSem, 0, &err);
	CN_st_GpsAndMileage_OperData.State[fd]=De_GpsAndMileage_State_Close;
	OSSemPost(GpsAndMileageUseSem);
	return De_Suc_GpsAndMileage;
}
static uint16 Get(st_State_RunLen	*ptst_State_RunLen)
{	uint8 err;
	OSSemPend(GpsAndMileageUseSem, 0, &err);
	CN_st_Fun_AscNumber.MoveByte(ptst_State_RunLen,&CN_st_GpsAndMileage_OperData.CN_st_State_RunLen,sizeof(st_State_RunLen));
	OSSemPost(GpsAndMileageUseSem);
	return De_Suc_GpsAndMileage;		
}
static void Task(void *pData)
{	uint8 err,i,GpsId,MileageId;
	uint16 Result;
	pData=pData;
	for(;;OSSemPost(GpsAndMileageUseSem),OSTimeDly(De_GpsAndMileage_TaskDly),WatchDog())
	{	OSSemPend(GpsAndMileageUseSem, 0, &err);
		//CN_st_Fun_Uart.Write(0,"Mileage_Start\r\n",15);
		for(i=0;i<De_Affair_GpsAndMileage_MaxNumber;i++)
		{	if(CN_st_GpsAndMileage_OperData.State[i]==De_GpsAndMileage_State_Open)
				break;
		}
		if(i==De_Affair_GpsAndMileage_MaxNumber)
			continue;
		if(CN_st_Fun_Sensor.GetPar2ID(De_Sensor_WordPar_Gps,&GpsId)!=De_Suc_Sensor)
			continue;
		//CN_st_Fun_Uart.Write(0,"GPS OK\r\n",8);
		Result=ReadGpsData(GpsId,&CN_st_GpsAndMileage_OperData.CN_st_State_RunLen.GpsState,&CN_st_GpsAndMileage_OperData.CN_st_File_Gps.CN_st_Data_Gps);
		if(Result!=De_Suc_Gps)
			continue;
		if(CN_st_Fun_Sensor.GetPar2ID(De_Sensor_WordPar_Mileage,&MileageId)!=De_Suc_Sensor)
			continue;
		Result=CountMileage(MileageId,&CN_st_GpsAndMileage_OperData.CN_st_File_Gps.CN_st_Data_Gps,&CN_st_GpsAndMileage_OperData.CN_st_File_Gps.Milage);
		if(Result!=De_Suc_Mileage)
			continue;
	   	JugeEvent(&CN_st_GpsAndMileage_OperData.CN_st_File_Gps);
		//CN_st_Fun_Uart.Write(0,"Mileage_End\r\n",13);
	}	
}
static uint16 ReadGpsData(uint8 fd,uint8 *state,st_Data_Gps *ptst_Data_Gps)
{	uint16 Result;
	Result=CN_st_Fun_Sensor.Read(fd,NULL,ptst_Data_Gps);
	if(Result==De_Erro_Senor_NoOpen)
		*state=De_GpsState_Close;			
	else if(Result==De_Erro_Gps_NoLocation)
		*state=De_GpsState_FlaseData;
	else if(Result!=De_Suc_Gps)
		*state=De_GpsState_NoWork;
	else 
		*state=De_GpsState_OK;
	return Result;	
}
static uint16 CountMileage(uint8 fd,st_Data_Gps *ptst_Data_Gps,uint32 *Length)
{	return CN_st_Fun_Sensor.Read(fd,ptst_Data_Gps,Length);
} 
static uint16 JugeEvent(st_File_Gps *ptst_File_Gps)
{//	uint32 Milage;
	uint8 i,err;
	for(i=0;i<De_Affair_GpsAndMileage_MaxNumber;i++,WatchDog())						//Milage=ptst_File_Gps->Milage
	{	if(CN_st_GpsAndMileage_OperData.State[i]!=De_GpsAndMileage_State_Open)
			continue;
//		CN_st_GpsAndMileage_OperData.CN_st_Affair_GpsAndMileage[i].Milage+=ptst_File_Gps->Milage;
//		if((CN_st_GpsAndMileage_OperData.CN_st_Affair_GpsAndMileage[i].Milage<CN_st_GpsAndMileage_OperData.CN_st_Affair_GpsAndMileage[i].CN_st_Affair_Data.Len)||(CN_st_GpsAndMileage_OperData.CN_st_Affair_GpsAndMileage[i].CN_st_Affair_RunLen.Fun_SumLen==NULL))
//			continue;
		if(CN_st_GpsAndMileage_OperData.CN_st_Affair_GpsAndMileage[i].CN_st_Affair_RunLen.Fun_SumLen==NULL)
			continue;
		OSSemPost(GpsAndMileageUseSem);
//		ptst_File_Gps->Milage=CN_st_GpsAndMileage_OperData.CN_st_Affair_GpsAndMileage[i].Milage;
		CN_st_GpsAndMileage_OperData.CN_st_Affair_GpsAndMileage[i].CN_st_Affair_RunLen.Fun_SumLen(ptst_File_Gps,i);
		CN_st_GpsAndMileage_OperData.CN_st_Affair_GpsAndMileage[i].Milage=0;
//		ptst_File_Gps->Milage=Milage;
		OSSemPend(GpsAndMileageUseSem, 0, &err);
	}
	return De_Suc_GpsAndMileage;
}












