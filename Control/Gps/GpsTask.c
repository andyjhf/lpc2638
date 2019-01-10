#define De_GpsTask_Compiler
#include "GpsTask.h"


static uint16 Init(void)
{	const uint8 MainData[7]={0x20,0x50,0x06,0x05,0x10,0x00,0x00};
	uint16 Result;
	uint8 i;
		
	if((Result=CN_st_Fun_Gps.Init())!=De_Suc_Gps)
		return Result;
	if((Result=CN_st_Fun_RTC.Init())!=De_Suc_RTC)
		return Result;
	CN_st_Fun_AscNumber.ClsArray(&CN_st_Control_Gps,sizeof(st_Control_Gps));
	CN_st_Control_Gps.CN_st_Data_GpsControl.PoweState = De_Gps_PowerOff_Close;
//	CN_st_Fun_RTC.Read(CN_st_Control_Gps.CN_st_Data_GpsControl.CN_st_Data_Gps.CN_st_Gps_Data_GPRMC.DateTime);
//	if(CN_st_Fun_Date.Juge(CN_st_Control_Gps.CN_st_Data_GpsControl.CN_st_Data_Gps.CN_st_Gps_Data_GPRMC.DateTime,De_Type_Date_Second)!=De_Suc_Date)
	if(CN_st_Fun_RTC.Read(CN_st_Control_Gps.CN_st_Data_GpsControl.CN_st_Data_Gps.CN_st_Gps_Data_GPRMC.DateTime)!=De_Suc_RTC)
	{	CN_st_Fun_AscNumber.MoveByte(CN_st_Control_Gps.CN_st_Data_GpsControl.CN_st_Data_Gps.CN_st_Gps_Data_GPRMC.DateTime,(uint8 *)MainData,sizeof(MainData));	
		CN_st_Fun_RTC.Write(CN_st_Control_Gps.CN_st_Data_GpsControl.CN_st_Data_Gps.CN_st_Gps_Data_GPRMC.DateTime);
  	}

		
	for(i=0;i<De_Gps_MaxAffair;i++)
	{	CN_st_Control_Gps.CN_st_Affair_Gps[i].ptFunSemFun = NULL;
		CN_st_Control_Gps.CN_st_Affair_Gps[i].ptNoSemFun = NULL;
		CN_st_Control_Gps.CN_st_Affair_Gps[i].ptErroFun = NULL;
		CN_st_Control_Gps.State[i] = De_Affair_State_Close;
	}
	GpsCtrSem=OSSemCreate(1);
	if(GpsCtrSem==NULL)
		return	De_Erro_Control_Gps_Init;
	OSTaskCreate (GpsTask,(void *)0, &GpsTaskStk[De_Gps_Stk - 1], De_Gps_Task);	
	return De_Control_Suc_Gps;		
}
static uint16 Open(st_Affair_Gps *pst_Affair_Gps,uint8 *fd)
{
	uint8 err;
	uint16 Result;
	OSSemPend(GpsCtrSem, 0, &err);
	if((Result=SeekSpace(&CN_st_Control_Gps))==De_Gps_MaxAffair)
	{ 	OSSemPost(GpsCtrSem);
		return	De_Erro_Affair_Nofd;
	}
	CN_st_Control_Gps.State[Result] = De_Affair_State_Open;
	CN_st_Control_Gps.CN_st_Affair_Gps[Result].ptFunSemFun = pst_Affair_Gps->ptFunSemFun;
	CN_st_Control_Gps.CN_st_Affair_Gps[Result].ptNoSemFun = pst_Affair_Gps->ptNoSemFun;
	CN_st_Control_Gps.CN_st_Affair_Gps[Result].ptErroFun = pst_Affair_Gps->ptErroFun;
	*fd = Result;
	OSSemPost(GpsCtrSem);
	return De_Control_Suc_Gps;	
}
static uint16 Close(uint8   fd)
{
	uint8 err;
	OSSemPend(GpsCtrSem, 0, &err);
	CN_st_Control_Gps.CN_st_Affair_Gps[fd].ptFunSemFun = NULL;
	CN_st_Control_Gps.CN_st_Affair_Gps[fd].ptNoSemFun = NULL;
	CN_st_Control_Gps.CN_st_Affair_Gps[fd].ptErroFun = NULL;
	CN_st_Control_Gps.State[fd] = De_Affair_State_Close;
	OSSemPost(GpsCtrSem);
	return De_Control_Suc_Gps;	
}
static uint16 Read(st_Data_Gps   *ptst_Data_Gps)
{	uint8 err;
	OSSemPend(GpsCtrSem, 0, &err);
	CN_st_Fun_AscNumber.MoveByte(ptst_Data_Gps,&CN_st_Control_Gps.CN_st_Data_GpsControl.CN_st_Data_Gps,sizeof(st_Data_Gps));
	OSSemPost(GpsCtrSem);
	return De_Control_Suc_Gps;	
}


static uint16 PowerOpen(void)	  		//打开GPS电源
{	
	uint8	err;

	OSSemPend(GpsCtrSem, 0, &err);
	if(CN_st_Control_Gps.CN_st_Data_GpsControl.PoweState!=De_Gps_PowerOn_Open)
		CN_st_Fun_Gps.Open();				//开GPS电源
	CN_st_Fun_Uart.Write(0,"Gps Open Finish\r\n",17);
	CN_st_Control_Gps.CN_st_Data_GpsControl.PoweState = De_Gps_PowerOn_Open;
	OSSemPost(GpsCtrSem);
	return De_Control_Suc_Gps;
}

static uint16 PowerClose(void)
{	uint8 err;
	OSSemPend(GpsCtrSem, 0, &err);
	if(CN_st_Control_Gps.CN_st_Data_GpsControl.PoweState==De_Gps_PowerOn_Open)
	{	CN_st_Fun_Uart.Write(0,"Gps Close\r\n",11);
		if(CN_st_Fun_Gps.Close()!=De_Suc_Gps)
		{	OSSemPost(GpsCtrSem);
			return De_Erro_PowerOff_Gps;

		}
		CN_st_Control_Gps.CN_st_Data_GpsControl.CN_st_Data_Gps.CN_st_Gps_Data_GPRMC.LocationTrue=De_Gps_Location_Flase;
		CN_st_Control_Gps.CN_st_Data_GpsControl.PoweState = De_Gps_PowerOff_Close;
		CN_st_Fun_Uart.Write(0,"Gps close\r\n",11);
	}	
	OSSemPost(GpsCtrSem);
	return De_Control_Suc_Gps;
} 
static uint16 SeekSpace(st_Control_Gps    *pst_Control_Gps)	  //查找空闲的时间事件
{
	uint8 i;
	for(i=0;i<De_Gps_MaxAffair;i++)
	{
		if(pst_Control_Gps->State[i]==De_Affair_State_Close)
			break;

	}
	return i;
}

static void GpsTask(void *pdata)
{	uint16 Result;
	uint8	err;
	pdata = pdata;
	for(;;)
	{	WatchDog();
		if(CN_st_Control_Gps.CN_st_Data_GpsControl.PoweState == De_Gps_PowerOn_Open)
		{
			OSSemPend(GpsCtrSem, 0, &err);
			Result = CN_st_Fun_Gps.Read(&CN_st_Control_Gps.CN_st_Data_GpsControl.CN_st_Data_Gps);		
			JugeAffair(Result);
			OSSemPost(GpsCtrSem);
		}
		else
		{	
			CN_st_Fun_RTC.Read(CN_st_Control_Gps.CN_st_Data_GpsControl.CN_st_Data_Gps.CN_st_Gps_Data_GPRMC.DateTime);


		}
		
		OSTimeDly(De_Gps_TaskDly);
	}	
}
static void JugeAffair(uint16 Result)
{	uint8 i;
	uint8 DataTime[7];
	if(Result == De_Erro_Gps_TimeOut)
	{	CN_st_Fun_RTC.Read(DataTime);
		if(CN_st_Fun_AscNumber.CompareBuf(DataTime,
			CN_st_Control_Gps.CN_st_Data_GpsControl.CN_st_Data_Gps.CN_st_Gps_Data_GPRMC.DateTime,sizeof(DataTime))!=0)
			CN_st_Fun_RTC.Write(CN_st_Control_Gps.CN_st_Data_GpsControl.CN_st_Data_Gps.CN_st_Gps_Data_GPRMC.DateTime);
		CN_st_Fun_AscNumber.MoveByte(CN_st_Control_Gps.CN_st_Data_GpsControl.CN_st_Data_Gps.CN_st_Gps_Data_GPRMC.DateTime,
		DataTime,7);
		for(i=0;i<De_Gps_MaxAffair;i++)
		{	if(CN_st_Control_Gps.State[i]==De_Affair_State_Close)
				continue;
			if(CN_st_Control_Gps.CN_st_Affair_Gps[i].ptErroFun != NULL)
				CN_st_Control_Gps.CN_st_Affair_Gps[i].ptErroFun(&CN_st_Control_Gps.CN_st_Data_GpsControl.CN_st_Data_Gps,i);
		}
		
		CN_st_Control_Gps.CN_st_Data_GpsControl.CN_st_Data_Gps.CN_st_Gps_Data_GPRMC.LocationTrue=De_Gps_Location_Flase;
	}
	else if((Result == De_Suc_Gps)&&(CN_st_Control_Gps.CN_st_Data_GpsControl.CN_st_Data_Gps.CN_st_Gps_Data_GPRMC.LocationTrue==De_Gps_Location_True))
	{		
		if(RTC_First_Updata == 1)
		{	RTC_First_Updata = 0;
			CN_st_Fun_RTC.Write(CN_st_Control_Gps.CN_st_Data_GpsControl.CN_st_Data_Gps.CN_st_Gps_Data_GPRMC.DateTime);
		}
		for(i=0;i<De_Gps_MaxAffair;i++)
		{	if(CN_st_Control_Gps.State[i]==De_Affair_State_Close)
				continue;
			if(CN_st_Control_Gps.CN_st_Affair_Gps[i].ptFunSemFun != NULL)
				CN_st_Control_Gps.CN_st_Affair_Gps[i].ptFunSemFun(&CN_st_Control_Gps.CN_st_Data_GpsControl.CN_st_Data_Gps,i);
		}	
	}
	else if(Result == De_Erro_Gps_NoLocation)
	{	CN_st_Fun_RTC.Read(CN_st_Control_Gps.CN_st_Data_GpsControl.CN_st_Data_Gps.CN_st_Gps_Data_GPRMC.DateTime);	
		for(i=0;i<De_Gps_MaxAffair;i++)
		{	if(CN_st_Control_Gps.State[i]==De_Affair_State_Close)
				continue;
			if(CN_st_Control_Gps.CN_st_Affair_Gps[i].ptNoSemFun != NULL)
				CN_st_Control_Gps.CN_st_Affair_Gps[i].ptNoSemFun(&CN_st_Control_Gps.CN_st_Data_GpsControl.CN_st_Data_Gps,i);
		}
		
	}	
}
