#define De_Timer_Compiler
#include "Timer.h"
#include "..\..\HardWare\UART\UART.h"
#ifdef	De_Compiler_Control_Timer
static uint16 Init(void)  								//
{	if(TimerSem!=NULL)
		return De_Suc_Timer;
	CN_st_Fun_AscNumber.ClsArray(&CN_st_Control_Timer,sizeof(st_Control_Timer));
	TimerSem=OSSemCreate(1);							//创建一个信号量
	OSTaskCreate (Task,(void *)0, &Timer_Stk[De_Stk_Timer - 1],De_Task_Timer);
	return De_Suc_Timer;
}

static uint16 Open(st_Affair_Timer	*ptst_Affair_Timer,uint8 *fd)
{//	uint8 Asc[11];
	uint16 Result;
	uint8	err;
	OSSemPend(TimerSem, 0, &err);
	if((Result=SeekSpace(&CN_st_Control_Timer))==De_Timer_MaxAffair)
	{	OSSemPost(TimerSem);
		return De_Erro_Timer_Nofd;
	}
	*fd=Result;
	
	CN_st_Control_Timer.CN_st_Affair_Timer[Result].CN_st_Property_Timer.TimerData=ptst_Affair_Timer->CN_st_Property_Timer.TimerData;
	CN_st_Control_Timer.CN_st_Affair_Timer[Result].CN_st_Property_Timer.TimerNonce=ptst_Affair_Timer->CN_st_Property_Timer.TimerNonce;
	CN_st_Control_Timer.CN_st_Affair_Timer[Result].CN_st_Function_Timer.ptFun=ptst_Affair_Timer->CN_st_Function_Timer.ptFun;
	CN_st_Control_Timer.State[Result]=De_Timer_Affair_State_Open;
	OSSemPost(TimerSem);
	return De_Suc_Timer;
}

static uint16 Close(uint8 fd)
{	uint8 err;
	if(fd>=De_Timer_MaxAffair)
		return De_Erro_Timer_Nofd;
	OSSemPend(TimerSem, 0, &err);
	CN_st_Control_Timer.State[fd]=De_Timer_Affair_State_Close;
	OSSemPost(TimerSem);
	return De_Suc_Timer;
}
static uint16 Read(st_Data_Timer	*ptst_Data_Timer)
{	uint8 err;
	OSSemPend(TimerSem, 0, &err);
	CN_st_Fun_AscNumber.MoveByte(ptst_Data_Timer,&CN_st_Control_Timer.CN_st_Data_Timer,sizeof(st_Data_Timer));	
	OSSemPost(TimerSem);
	return De_Suc_Timer;
}

static uint16 Enable(uint8 fd)
{	uint16 Result;
	uint8 err;	 
	Result=De_Suc_Timer;
	OSSemPend(TimerSem, 0, &err);
	if(fd>=De_Timer_MaxAffair)
		Result=De_Erro_Timer_Nofd;	
	else if(CN_st_Control_Timer.State[fd]==De_Timer_Affair_State_Open)
		CN_st_Control_Timer.Enable[fd]=De_Timer_Affair_Enable;
	else
		Result=De_Erro_Timer_Nofd;	
	OSSemPost(TimerSem);
	return Result;
}

static uint16 DisEnable(uint8 fd)
{	uint16 Result;
	uint8 err;	 
	Result=De_Suc_Timer;
	OSSemPend(TimerSem, 0, &err);
	if(fd>=De_Timer_MaxAffair)
		Result=De_Erro_Timer_Nofd;	
	else if(CN_st_Control_Timer.State[fd]==De_Timer_Affair_State_Open)
		CN_st_Control_Timer.Enable[fd]=De_Timer_Affair_DisEnable;
	else
		Result=De_Erro_Timer_Nofd;	
	OSSemPost(TimerSem);
	return Result;
}

static uint16 GetEnable(uint8 fd,uint8 *State)
{	uint16 Result;
	uint8 err;	 
	Result=De_Suc_Timer;
	OSSemPend(TimerSem, 0, &err);
	if(fd>=De_Timer_MaxAffair)
		Result=De_Erro_Timer_Nofd;	
	else if(CN_st_Control_Timer.State[fd]==De_Timer_Affair_State_Open)
		*State=CN_st_Control_Timer.Enable[fd];
	else
		Result=De_Erro_Timer_Nofd;	
	OSSemPost(TimerSem);
	return Result;
}

static uint16 GetPro(uint8 fd, uint32 *Va)
{	uint16 Result;
	uint8 err;	 
	Result=De_Suc_Timer;
	OSSemPend(TimerSem, 0, &err);
	if(fd>=De_Timer_MaxAffair)
		Result=De_Erro_Timer_Nofd;	
	else if(CN_st_Control_Timer.State[fd]==De_Timer_Affair_State_Open)
		*Va=CN_st_Control_Timer.CN_st_Affair_Timer[fd].CN_st_Property_Timer.TimerData;
	else
		Result=De_Erro_Timer_Nofd;	
	OSSemPost(TimerSem);
	return Result;
}

static uint16 EditPro(uint8 fd,uint32 Va)
{	uint16 Result;
	uint8 err;	 
	Result=De_Suc_Timer;
	OSSemPend(TimerSem, 0, &err);
	if(fd>=De_Timer_MaxAffair)
		Result=De_Erro_Timer_Nofd;	
	else if(CN_st_Control_Timer.State[fd]==De_Timer_Affair_State_Open)
	{	CN_st_Control_Timer.CN_st_Affair_Timer[fd].CN_st_Property_Timer.TimerData=Va;
		CN_st_Control_Timer.CN_st_Affair_Timer[fd].CN_st_Property_Timer.TimerNonce=0;
	}
	else
		Result=De_Erro_Timer_Nofd;	
	OSSemPost(TimerSem);
	return Result;
}


/*===============================================任务调度=======================================================*/
static void Task(void *pdata)
{	uint8 BackDateTime[7];
	uint32 add;
	uint8 GpsID;
	pdata=pdata;
	CN_st_Fun_AscNumber.ClsArray(BackDateTime,sizeof(BackDateTime));
	for(;;)
	{	WatchDog();
		CN_st_Fun_RTC.Read(CN_st_Control_Timer.CN_st_Data_Timer.DateTime);
		if(CN_st_Fun_Sensor.GetPar2ID(De_Sensor_WordPar_Gps,&GpsID)==De_Suc_Sensor)					//已经开启GPS功能
		{	if(CN_st_Fun_Sensor.Read(GpsID,NULL,&CN_st_Data_Gps)==De_Suc_Sensor)					//读GPS时间成功
			{ 	if(CN_st_Fun_AscNumber.CompareBuf(CN_st_Control_Timer.CN_st_Data_Timer.DateTime,CN_st_Data_Gps.CN_st_Gps_Data_GPRMC.DateTime,sizeof(DateTime))!=0)
				{	CN_st_Fun_AscNumber.MoveByte(CN_st_Control_Timer.CN_st_Data_Timer.DateTime,CN_st_Data_Gps.CN_st_Gps_Data_GPRMC.DateTime,sizeof(DateTime));
					CN_st_Fun_RTC.Write(CN_st_Control_Timer.CN_st_Data_Timer.DateTime);
				}
			}
		}
		add=GetTimeAdd(BackDateTime,CN_st_Control_Timer.CN_st_Data_Timer.DateTime);
		CN_st_Fun_AscNumber.MoveByte(BackDateTime,CN_st_Control_Timer.CN_st_Data_Timer.DateTime,sizeof(DateTime));	
		if(add!=0)			//时间发生变化		
			JugeEvent(&CN_st_Control_Timer,add);
		OSTimeDly(De_Timer_TaskDly);
	}
}

static void JugeEvent(st_Control_Timer	*ptst_Control_Timer,uint32 add)
{	uint16 Result;
	uint8 i,err;
	for(i=0;i<De_Timer_MaxAffair;i++,OSSemPost(TimerSem))
	{	OSSemPend(TimerSem, 0, &err);
		if(ptst_Control_Timer->State[i]==De_Timer_Affair_State_Close)
			continue;
		if(ptst_Control_Timer->CN_st_Affair_Timer[i].CN_st_Function_Timer.ptFun==NULL)
			continue;
		if(CN_st_Control_Timer.Enable[i]==De_Timer_Affair_DisEnable)
			continue;							//
		ptst_Control_Timer->CN_st_Affair_Timer[i].CN_st_Property_Timer.TimerNonce+=add;
		if(ptst_Control_Timer->CN_st_Affair_Timer[i].CN_st_Property_Timer.TimerData==0)					//代表是随着日期的变化发生事件
		{	Result=CN_st_Fun_AscNumber.CompareVa(ptst_Control_Timer->CN_st_Data_Timer.DateTime,ptst_Control_Timer->CN_st_Affair_Timer[i].CN_st_Property_Timer.DateTime,
			sizeof(ptst_Control_Timer->CN_st_Data_Timer.DateTime),De_AscNumber_Va_Big);
			if((Result==De_AscNumber_Va_True)||(Result==De_AscNumber_Va_Equality))
			{	if(ptst_Control_Timer->CN_st_Affair_Timer[i].CN_st_Function_Timer.ptFun!=NULL)
				{	OSSemPost(TimerSem);
					ptst_Control_Timer->CN_st_Affair_Timer[i].CN_st_Function_Timer.ptFun(&ptst_Control_Timer->CN_st_Data_Timer,i);
					OSSemPend(TimerSem, 0, &err);
					CN_st_Fun_Date.Next(ptst_Control_Timer->CN_st_Affair_Timer[i].CN_st_Property_Timer.DateTime,De_Type_Date_Date);
				}
			}
			continue;
		}
		if(ptst_Control_Timer->CN_st_Affair_Timer[i].CN_st_Property_Timer.TimerNonce>=ptst_Control_Timer->
		CN_st_Affair_Timer[i].CN_st_Property_Timer.TimerData)			//事件要发生
		{	OSSemPost(TimerSem);
			ptst_Control_Timer->CN_st_Affair_Timer[i].CN_st_Function_Timer.ptFun(&ptst_Control_Timer->CN_st_Data_Timer,i);
			OSSemPend(TimerSem, 0, &err);
			ptst_Control_Timer->CN_st_Affair_Timer[i].CN_st_Property_Timer.TimerNonce=0;				
		}
	}
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

static uint8 SeekSpace(st_Control_Timer	*ptst_Control_Timer)
{	uint16 i;
	for(i=0;i<De_Timer_MaxAffair;i++)
	{	if(ptst_Control_Timer->State[i]==De_Timer_Affair_State_Close)	
	  		break;
	}
	return i;
}
#endif






