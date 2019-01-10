#define De_CanTask_Compiler
#include "CanTask.h"
#include "..\..\HardWare\UART\UART.h"

static uint16 Init(void)
{	uint8 i;
	if(CN_st_Fun_Can.Init(De_Can_Use_Port))
		return	De_Erro_Control_Can_Init;
	if(CN_st_Fun_Can.Open(De_Can_Use_Port,Can_Use_BitRate))
		return	De_Erro_Control_Can_Init;
	CanCtrSem=OSSemCreate(1);
	if(CanCtrSem==NULL)
		return	De_Erro_Control_Can_Init;
	for(i=0;i<De_Can_MaxAffair;i++)
	{
		CN_st_Control_Can.CN_st_Function_Can[i].ptFun = NULL;
		CN_st_Control_Can.State[i] = De_Can_Affair_State_Close;
	}
	CN_st_Control_Can.CanInfor_State = De_Can_Data_Read;
	CN_st_Control_Can.Bps=Can_Use_BitRate;
	OSTaskCreate (CanTask,(void *)0, &CanTaskStk[De_Can_Stk - 1], De_Can_Task);
	return De_Control_Suc_Can;	
}

uint16 Open(st_Function_Can *ptst_Function_Can,uint8 *fd)
{	uint8 err;
	uint16 Result;
	OSSemPend(CanCtrSem, 0, &err);
	if((Result=SeekSpace(&CN_st_Control_Can))==De_Can_MaxAffair)
	{ 
		OSSemPost(CanCtrSem);
		return	De_Erro_Affair_Can_Nofd;
	}
	CN_st_Control_Can.State[Result] = De_Can_Affair_State_Open;
	CN_st_Control_Can.CN_st_Function_Can[Result].ptFun = ptst_Function_Can->ptFun;
	*fd = Result;
	OSSemPost(CanCtrSem);
	return De_Control_Suc_Can;	
}

uint16 Close(uint8 fd)
{
	uint8 err;
	OSSemPend(CanCtrSem, 0, &err);
	CN_st_Control_Can.CN_st_Function_Can[fd].ptFun = NULL;
	CN_st_Control_Can.State[fd] = De_Can_Affair_State_Close;
	OSSemPost(CanCtrSem);
	return De_Control_Suc_Can;
}

uint16 Read(st_Da_CanInfor *ptst_Da_CanInfor)
{
	uint8 err;
	OSSemPend(CanCtrSem, 0, &err);
	if(CN_st_Control_Can.CanInfor_State==De_Can_Data_Read)
	{
		OSSemPost(CanCtrSem);
		return De_Erro_Control_Can_Nodata;	
	}
	CN_st_Fun_AscNumber.MoveByte(ptst_Da_CanInfor,&CN_st_Control_Can.CN_st_Data_CanInfor,sizeof(st_Da_CanInfor));
//	for(i=0;i<sizeof(st_Da_CanInfor);i++)
//		*(ptst_Da_CanInfor+i) = *(&CN_st_Control_Can.CN_st_Data_CanInfor+i);
	CN_st_Control_Can.CanInfor_State = De_Can_Data_Read;
	OSSemPost(CanCtrSem);
	return De_Control_Suc_Can;	
}

uint16 Write(st_Da_CanInfor *ptst_Da_CanInfor)
{	uint8 err;
	OSSemPend(CanCtrSem, 0, &err);
	if(CN_st_Fun_Can.Write(De_Can_Use_Port,ptst_Da_CanInfor)!=De_Suc_Can)
	{
		OSSemPost(CanCtrSem);
		return De_Erro_Control_Can_Send;
	}
	OSSemPost(CanCtrSem);
	return De_Control_Suc_Can;
}

static uint16 Enable(uint8 fd)
{	uint16 Result;
	uint8 err;	 
	Result=De_Control_Suc_Can;
	OSSemPend(CanCtrSem, 0, &err);
	if(fd>=De_Can_MaxAffair)
		Result=De_Erro_Affair_Can_Nofd;	
	else if(CN_st_Control_Can.State[fd]==De_Can_Affair_State_Open)
		CN_st_Control_Can.Enable[fd]=De_Can_Affair_Enable;
	else
		Result=De_Erro_Affair_Can_Nofd;	
	OSSemPost(CanCtrSem);
	return Result;
}

static uint16 DisEnable(uint8 fd)
{	uint16 Result;
	uint8 err;	 
	Result=De_Control_Suc_Can;
	OSSemPend(CanCtrSem, 0, &err);
	if(fd>=De_Can_MaxAffair)
		Result=De_Erro_Affair_Can_Nofd;	
	else if(CN_st_Control_Can.State[fd]==De_Can_Affair_State_Open)
		CN_st_Control_Can.Enable[fd]=De_Can_Affair_DisEnable;
	else
		Result=De_Erro_Affair_Can_Nofd;	
	OSSemPost(CanCtrSem);
	return Result;
}

static uint16 GetEnable(uint8 fd,uint8 *State)
{ 	uint16 Result;
	uint8 err;	 
	Result=De_Control_Suc_Can;
	OSSemPend(CanCtrSem, 0, &err);
	if(fd>=De_Can_MaxAffair)
		Result=De_Erro_Affair_Can_Nofd;
	else if(CN_st_Control_Can.State[fd]==De_Can_Affair_State_Open)
		*State=CN_st_Control_Can.Enable[fd];
	else
		Result=De_Erro_Affair_Can_Nofd;	
   	OSSemPost(CanCtrSem);
	return Result;

}
static uint16 GetPro(uint32 *Bps)
{	uint8 err;
	OSSemPend(CanCtrSem, 0, &err);
	*Bps=CN_st_Control_Can.Bps;
	OSSemPost(CanCtrSem);
	return De_Control_Suc_Can;
}

static uint16 EditPro(uint32 *Bps)
{	uint8 err;
	OSSemPend(CanCtrSem, 0, &err);
	CN_st_Fun_Can.Close(De_Can_Use_Port);
	CN_st_Fun_Can.Open(De_Can_Use_Port,*Bps);
	CN_st_Control_Can.Bps=*Bps;	
	OSSemPost(CanCtrSem);
	return De_Control_Suc_Can;
}




static uint16 SeekSpace(st_Control_Can    *pst_Control_Can)	  //查找空闲的时间事件
{
	uint8 i;
	for(i=0;i<De_Can_MaxAffair;i++)
	{
		if(pst_Control_Can->State[i]==De_Can_Affair_State_Close)
			break;

	}
	return i;
}
static void CanTask(void *pdata)
{
	uint16 Result;
	uint8	err;
	pdata=pdata;
	for(;;)
	{
		//CN_st_Fun_Uart.Write(0,"Can",3);
		WatchDog();
		OSSemPend(CanCtrSem, 0, &err);
		Result = CN_st_Fun_Can.Read(De_Can_Use_Port,&CN_st_Control_Can.CN_st_Data_CanInfor);
		OSSemPost(CanCtrSem);
		if(Result != 0)
		{	CN_st_Control_Can.CanInfor_State = De_Can_Data_UnRead;
			JugeAffair();
		}
		OSTimeDly(De_Can_TaskDly);			
	}
}
static void JugeAffair(void)
{	uint8 i;
	for(i=0;i<De_Can_MaxAffair;i++)
	{	if(CN_st_Control_Can.State[i]==De_Can_Affair_State_Close)
			continue;
		if(CN_st_Control_Can.Enable[i]==De_Can_Affair_DisEnable)
			continue;
		if(CN_st_Control_Can.CN_st_Function_Can[i].ptFun != NULL)
			CN_st_Control_Can.CN_st_Function_Can[i].ptFun(&CN_st_Control_Can.CN_st_Data_CanInfor);
	}	
}


