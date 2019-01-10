#define De_TzV2_Compiler
#include "TzV2.1.h"
static uint16 Init(void) 																//天泽协议初始化
{	uint8 i;
	if(TzvSem!=NULL)
		return De_Suc_Sensor;
	for(i=0;i<sizeof(State);i++)
		State[i]=De_AgreeOn_Dev_Close;
	if((TzvSem=OSSemCreate(1))==NULL)
		return De_Erro_AgreeOn_Init;
	CN_st_st_AgreeOn_Dev_Par.Buf=BigBuf;
	STK=(OS_STK	*)(De_TzV21_STK);
	OSTaskCreate (Task,(void *)0, &STK[De_Stk_Tzv2_Size - 1],De_Task_Number);
	return De_Suc_AgreeOn;						
}
static uint16 Open(st_AgreeOn_OpenPar	*ptst_AgreeOn_OpenPar,st_Appair_Tzv2	*ptst_Appair_Tzv2,uint8 *fd)
{	uint16 Result;
	uint8 err;
	OSSemPend(TzvSem, 0, &err);
	Result=Open1(ptst_AgreeOn_OpenPar,ptst_Appair_Tzv2,fd);
	OSSemPost(TzvSem);
	return Result;
}

static uint16 Close(uint8 fd)
{	uint8 err;
	if(fd>=sizeof(State))
		return De_Erro_AgreeOn_Nofd;
	OSSemPend(TzvSem, 0, &err);
	State[fd]=De_AgreeOn_Dev_Close;	
	OSSemPost(TzvSem);
	return De_Suc_AgreeOn;	
}

static uint16 Read(uint8 fd,st_st_AgreeOn_Dev_Par	*ptst_st_AgreeOn_Dev_Par)
{	uint16 Result;
	uint8 err;
	OSSemPend(TzvSem, 0, &err);
	Result=Read1(fd,ptst_st_AgreeOn_Dev_Par);	
	OSSemPost(TzvSem);
	return Result;
}

static uint16 Write(uint8 fd,st_st_AgreeOn_Dev_WritePar	*ptst_st_AgreeOn_Dev_WritePar,uint8 *Oper)
{	uint16 Result;
	uint8 err;
	OSSemPend(TzvSem, 0, &err);
	Result=Write1(fd,ptst_st_AgreeOn_Dev_WritePar,Oper);
	FlagNumber[fd]++;	
	OSSemPost(TzvSem);
	return Result;
}
static uint16 GetPar2ID(uint16 WorkPar,uint8 *fd)
{	uint8 i,err;
	OSSemPend(TzvSem, 0, &err);
	for(i=0;i<sizeof(State);i++)
	{	if(State[i]==De_AgreeOn_Dev_Close)
			continue;
		if(CN_st_AgreeOn_OpenPar[i].WorkPar==WorkPar)
		{	*fd=i;
			OSSemPost(TzvSem);
			return De_Suc_AgreeOn;
		}
	}
	OSSemPost(TzvSem);
	return De_Erro_AgreeOn_Nofd;
}

static  void Task(void *pData)
{	uint8 i,err;
	pData=pData;
	for(;;OSTimeDly(De_Tzv2_TaskDly))
	{	OSSemPend(TzvSem, 0, &err);
		for(i=0;i<De_AgreeOn_Dev_Number;i++)
		{	if(State[i]!=De_AgreeOn_Dev_Open)
				continue;
			if(Read1(i,&CN_st_st_AgreeOn_Dev_Par)!=De_Suc_AgreeOn)
				continue;
			OSSemPost(TzvSem);
			CN_st_Appair_Tzv2[i].ptFunction(&CN_st_st_AgreeOn_Dev_Par,i);
			OSSemPend(TzvSem, 0, &err);
		}
		OSSemPost(TzvSem);		
	}
}




static uint16 Open1(st_AgreeOn_OpenPar	*ptst_AgreeOn_OpenPar,st_Appair_Tzv2	*ptst_Appair_Tzv2,uint8 *fd)				//打开天泽协议
{	uint8 i;
	for(i=0;i<sizeof(State);i++)
	{	if(State[i]==De_AgreeOn_Dev_Close)
			break;
	}
	if(i==sizeof(State))
		return De_Erro_AgreeOn_NoSpace;
	CN_st_Fun_AscNumber.MoveByte(&CN_st_AgreeOn_OpenPar[i],ptst_AgreeOn_OpenPar,sizeof(st_AgreeOn_OpenPar));
	CN_st_Fun_AscNumber.MoveByte(&CN_st_Appair_Tzv2[i],ptst_Appair_Tzv2,sizeof(st_Appair_Tzv2));
	State[i]=De_AgreeOn_Dev_Open;
	FlagNumber[i]=0;
	return De_Suc_AgreeOn;			
}


static uint16 Read1(uint8 fd,st_st_AgreeOn_Dev_Par	*ptst_st_AgreeOn_Dev_Par)			//读数据
{	st_Dev_Tzxy_Send	CN_st_Dev_Tzxy_Send;
	st_Dev_Tzxy_Agree	CN_st_Dev_Tzxy_Agree;
	uint16 Result;
	uint16 DataLen,ReDataLen;
	uint8 Byte,Parfd;
	if((fd>=sizeof(State))||(State[fd]!=De_AgreeOn_Dev_Open))	
		return De_Erro_AgreeOn_Nofd;
	CN_st_Dev_Tzxy_Send.ResultOrSend=De_Tzxy_AgreeBuf_Agree;
	CN_st_Dev_Tzxy_Agree.Buf=X_BUF;
	if((Result=CN_st_Fun_Sensor.GetPar2ID(CN_st_AgreeOn_OpenPar[fd].WorkPar,&Parfd))!=De_Suc_Sensor)
		return Result;
	if((Result=CN_st_Fun_Sensor.Read(Parfd,&CN_st_Dev_Tzxy_Send,&CN_st_Dev_Tzxy_Agree))!=De_Suc_Sensor)		
		return Result;
	DataLen=CN_st_Dev_Tzxy_Agree.SizeofBuf;
   	if(DataLen<17)																		//解析错误
		return De_Erro_AgreeOn_Explain;
	if(CN_st_Fun_AscNumber.CompareBuf(X_BUF+4,CN_st_AgreeOn_OpenPar[fd].IMEI,
	sizeof(CN_st_AgreeOn_OpenPar[0].IMEI))!=0) 											//合法性判断
		return De_Erro_AgreeOn_Legality;
	Byte=X_BUF[0];
	ReDataLen=Byte*0x100;
	Byte=X_BUF[1];
	ReDataLen+=Byte;
	if(ReDataLen>DataLen)
		return De_Erro_AgreeOn_Explain;
	ptst_st_AgreeOn_Dev_Par->AnswerFlag=X_BUF[3];
	Byte=X_BUF[11];
	ptst_st_AgreeOn_Dev_Par->ContrID=Byte*0X100;
	Byte=X_BUF[12];
	ptst_st_AgreeOn_Dev_Par->ContrID+=Byte;
	Byte=X_BUF[13];
	ptst_st_AgreeOn_Dev_Par->OrderNumber=Byte*0x100;
	Byte=X_BUF[14];			
   	ptst_st_AgreeOn_Dev_Par->OrderNumber+=Byte;
	Byte=X_BUF[15];
	ptst_st_AgreeOn_Dev_Par->OrderID=Byte*0x100;
	Byte=X_BUF[16];			
   	ptst_st_AgreeOn_Dev_Par->OrderID+=Byte;
	return CN_st_Fun_Tz_Agreen.Read(X_BUF+17,ptst_st_AgreeOn_Dev_Par->Buf,DataLen-17,ptst_st_AgreeOn_Dev_Par->OrderID);
}
static uint16 Write1(uint8 fd,st_st_AgreeOn_Dev_WritePar	*ptst_st_AgreeOn_Dev_WritePar,uint8 *Oper)
{	uint8 DateTimer[7];
	uint8 DateTimer1[7];
	uint16 Result,i;
	if((fd>=sizeof(State))||(State[fd]!=De_AgreeOn_Dev_Open))	
		return De_Erro_AgreeOn_Nofd;
	for(i=0;i<CN_st_AgreeOn_OpenPar[fd].IPRepeat;i++)
	{	CN_st_Fun_RTC.Read(DateTimer);
		Result=WriteSig(fd,ptst_st_AgreeOn_Dev_WritePar,Oper);
		if((Result==De_Suc_AgreeOn)||(Result==De_Erro_Tz_Send_NoID))
			return Result;


		for(;;WatchDog())
		{	CN_st_Fun_RTC.Read(DateTimer1);
			if(GetTimeAdd(DateTimer,DateTimer1)>=CN_st_AgreeOn_OpenPar[fd].IPRepeatTime)
				break;
		}			
	}
	
	return De_Erro_AgreeOn_Write;
}
		  					
static uint16 WriteSig(uint8 fd,st_st_AgreeOn_Dev_WritePar	*ptst_st_AgreeOn_Dev_WritePar,uint8 *Oper)	//调用读函数时的函数
{	st_Dev_Tzxy_Send	CN_st_Dev_Tzxy_Send;
	st_Dev_Tzxy_Agree	CN_st_Dev_Tzxy_Agree;
	uint8 DateTimer[7];
	uint8 DateTimer1[7],Byte;	
	uint16 Result,DataLen,OrderID,ReDataLen;
	uint8 i,Parfd;
	if((Result=CN_st_Fun_Tz_Send.Write(X_BUF+17,ptst_st_AgreeOn_Dev_WritePar->Buf,&DataLen,
	ptst_st_AgreeOn_Dev_WritePar->OrderID))!=De_Suc_AgreeOn)
		return Result;
	for(i=0;i<sizeof(CN_Ba_Order2Answer)/sizeof(st_AgreenOn_Par2Type);i++)
	{	if(CN_Ba_Order2Answer[i].Par==ptst_st_AgreeOn_Dev_WritePar->OrderID)
			break;
	}
	if(i==sizeof(CN_Ba_Order2Answer)/sizeof(st_AgreenOn_Par2Type))
		return De_Erro_AgreeOn_NoAgreeOn;
	X_BUF[0]=((DataLen+17)>>8);
	X_BUF[1]=((DataLen+17)&0xff);
	X_BUF[2]=2;
	X_BUF[3]=CN_Ba_Order2Answer[i].Number;
	CN_st_Fun_AscNumber.MoveByte(X_BUF+4,CN_st_AgreeOn_OpenPar[fd].IMEI,sizeof(CN_st_AgreeOn_OpenPar[0].IMEI));
	X_BUF[11]=((ptst_st_AgreeOn_Dev_WritePar->ContrID>>8)&0XFF);
	X_BUF[12]=((ptst_st_AgreeOn_Dev_WritePar->ContrID)&0XFF);
	X_BUF[13]=((FlagNumber[fd]>>8)&0xff);
	X_BUF[14]=((FlagNumber[fd])&0xff);
	X_BUF[15]=((ptst_st_AgreeOn_Dev_WritePar->OrderID>>8)&0xff);
	X_BUF[16]=((ptst_st_AgreeOn_Dev_WritePar->OrderID)&0xff);
	CN_st_Dev_Tzxy_Send.ResultOrSend=De_Tzxy_SendBuf_Send;
	CN_st_Dev_Tzxy_Send.SizeofBuf=DataLen+17;
   	CN_st_Dev_Tzxy_Send.Buf=X_BUF;
	
	if((Result=CN_st_Fun_Sensor.GetPar2ID(CN_st_AgreeOn_OpenPar[fd].WorkPar,&Parfd))!=De_Suc_Sensor)
		return Result;
	if((Result=CN_st_Fun_Sensor.Read(Parfd,&CN_st_Dev_Tzxy_Send,&CN_st_Dev_Tzxy_Agree))!=De_Suc_Sensor)		
		return Result;
	if(CN_Ba_Order2Answer[i].Number==De_AgreeOn_SendOrder_Answer_No)
		return Result;
	CN_st_Fun_RTC.Read(DateTimer);
	for(;;WatchDog())
	{	CN_st_Fun_RTC.Read(DateTimer1);
		if(GetTimeAdd(DateTimer,DateTimer1)>=CN_st_AgreeOn_OpenPar[fd].MaxDelay)
			return De_Erro_AgreeOn_TimerOver;
		if((Result=CN_st_Fun_Sensor.GetPar2ID(CN_st_AgreeOn_OpenPar[fd].WorkPar,&Parfd))!=De_Suc_Sensor)
			return Result;
		CN_st_Dev_Tzxy_Send.ResultOrSend=De_Tzxy_AgreeBuf_Agree;
		CN_st_Dev_Tzxy_Agree.Buf=X_BUF;
		if(CN_st_Fun_Sensor.Read(Parfd,&CN_st_Dev_Tzxy_Send,&CN_st_Dev_Tzxy_Agree)!=De_Suc_Sensor)		
			continue;
		DataLen=CN_st_Dev_Tzxy_Agree.SizeofBuf;
		if(DataLen<17)																		//解析错误
			continue;
		if(CN_st_Fun_AscNumber.CompareBuf(X_BUF+4,CN_st_AgreeOn_OpenPar[fd].IMEI,
		sizeof(CN_st_AgreeOn_OpenPar[0].IMEI))!=0) 											//合法性判断
			continue;
		Byte=X_BUF[0];
		ReDataLen=Byte*0x100;
		Byte=X_BUF[1];
		ReDataLen+=Byte;
		if(ReDataLen>DataLen)
			continue;
		OrderID=X_BUF[13]*0X100+X_BUF[14];
		if(OrderID!=De_Centr_Order_Answer)
			continue;
		OrderID=X_BUF[17]*0X100+X_BUF[18];
		if(OrderID!=ptst_st_AgreeOn_Dev_WritePar->OrderNumber)
			continue;
		OrderID=X_BUF[19]*0X100+X_BUF[20];
		if(OrderID!=ptst_st_AgreeOn_Dev_WritePar->OrderID)
			continue;
		*Oper=X_BUF[21];
		return De_Suc_AgreeOn;
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


