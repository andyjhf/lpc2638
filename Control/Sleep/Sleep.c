#define De_Sleep_Compiler
#include "Sleep.h"				
//创建一个邮箱
static uint16 Init(void)													//休眠
{	SleepBox=OSMboxCreate(NULL); 			
	if(SleepBox==NULL)
		return De_Erro_Sleep_Init;
	SleepSem=OSSemCreate(1);
	if(SleepSem==NULL)
		return De_Erro_Sleep_Init;
	CN_st_Fun_AscNumber.ClsArray(&CN_st_Control_Sleep,sizeof(st_Control_Sleep));
	OSTaskCreate(Task,(void *)0, &Sleep_Stk[De_Stk_Sleep - 1],De_Task_Sleep);
	return De_Suc_Sleep;
}


static uint16 Open(st_Affair_Sleep	*ptst_Affair_Sleep,uint8 *fd)   		//创建休眠事件
{	uint16 Result;
	uint8	err;
	if((Result=SeekSpace(&CN_st_Control_Sleep))==De_Sleep_MaxAffair)
		return De_Erro_Sleep_Nofd;
	OSSemPend(SleepSem, 0, &err);
	CN_st_Control_Sleep.CN_st_Affair_Sleep[Result].ptFunSleep=ptst_Affair_Sleep->ptFunSleep;
	CN_st_Control_Sleep.CN_st_Affair_Sleep[Result].ptFunupSleep=ptst_Affair_Sleep->ptFunupSleep;
	CN_st_Control_Sleep.State[Result]=De_Sleep_Affair_State_Open;
	*fd=Result;
	OSSemPost(SleepSem);
	return De_Suc_Sleep;					
}

static uint16 SeekSpace(st_Control_Sleep	*ptst_Control_Sleep)
{	uint16 i;
	for(i=0;i<De_Sleep_MaxAffair;i++)
	{	if(ptst_Control_Sleep->State[i]==De_Sleep_Affair_State_Close)	
	  		break;
	}
	return i;
}

static uint16 Close(uint8 fd)												//关闭休眠事件
{	uint8 err;
	OSSemPend(SleepSem, 0, &err);
	CN_st_Control_Sleep.State[fd]=De_Sleep_Affair_State_Close;	
	OSSemPost(SleepSem);
	return De_Suc_Sleep;

}

static void Task(void *pdata)
{	uint8 *Sleep,err;
	pdata=pdata;
	for(;;)
	{	WatchDog();
		Sleep=OSMboxPend (SleepBox,0,&err);
		if(*Sleep==De_State_Sleep)
		{	//CN_st_Fun_Uart.Write(0,"Sleep\r\n",7);
			CN_st_Control_Fun_Gps.PowerClose();
			CN_st_Control_Sleep.Sleep=De_State_Sleep;
			JugeAffair(&CN_st_Control_Sleep);
			
		}
		else
		{	//CN_st_Fun_Uart.Write(0,"SleepSuc\r\n",10);
			CN_st_Control_Sleep.Sleep=0;
			//CN_st_Fun_Uart.Write(0,"Suc",3);
			CN_st_Control_Fun_Gps.PowerOpen();
			JugeAffair(&CN_st_Control_Sleep);
			
		}
		OSTimeDly(De_Sleep_TaskDly);
	}
}

static void JugeAffair(st_Control_Sleep	*ptst_Control_Sleep)
{	uint8 i;
	if(ptst_Control_Sleep->Sleep==De_State_Sleep)
	{	for(i=0;i<De_Sleep_MaxAffair;i++)
		{	if((ptst_Control_Sleep->State[i]==De_Sleep_Affair_State_Open)&&(ptst_Control_Sleep->CN_st_Affair_Sleep[i].ptFunSleep!=NULL))
			{	//CN_st_Fun_Uart.Write(0,"SleepLoad",9);
				ptst_Control_Sleep->CN_st_Affair_Sleep[i].ptFunSleep(i);
			
			}	
		}
	}
	else
	{	//CN_st_Fun_Uart.Write(0,"SleepSuc",8);
		for(i=0;i<De_Sleep_MaxAffair;i++)
		{	if((ptst_Control_Sleep->State[i]==De_Sleep_Affair_State_Open)&&(ptst_Control_Sleep->CN_st_Affair_Sleep[i].ptFunupSleep!=NULL))
			{	//CN_st_Fun_Uart.Write(0,"SleepSuc",8);
				ptst_Control_Sleep->CN_st_Affair_Sleep[i].ptFunupSleep(i);
			
			}	
		}	
	}
}
static uint16 Read(uint8 *Sleep)
{	*Sleep=CN_st_Control_Sleep.Sleep;
	return	De_Suc_Sleep; 
}

