#define De_Less_Compiler
#include "Less.h"
/*=========================================对外输出函数========================================================*/
static uint16 Init1(void)
{	return Init();
}

static uint16 Open1(st_Sensor_DataPar	*ptst_Sensor_DataPar,uint8 *fd)
{	uint16 Result;
	uint8 err;
	OSSemPend(LessSem, 0, &err);
	Result=Open(ptst_Sensor_DataPar,fd);
	OSSemPost(LessSem);
	return Result;
}
static uint16 Close1(uint8 fd)
{	uint16 Result;
	uint8 err;
	OSSemPend(LessSem, 0, &err);
	Result=Close(fd);
	OSSemPost(LessSem);
	return Result;
}
static uint16 Read1(uint8 fd,void *SendBuf,void *AgreeBuf)
{	uint16 Result;
	uint8 err;
	OSSemPend(LessSem, 0, &err);
	Result=Read(fd,SendBuf,AgreeBuf);
	OSSemPost(LessSem);
	return Result;
}

static uint16 GetState1(st_Sensor_State	*ptst_Less_State,uint8 fd)
{	uint16 Result;
	uint8 err;
	OSSemPend(LessSem, 0, &err);
	Result=GetState(ptst_Less_State,fd);
	OSSemPost(LessSem);
	return Result;
}

/*==========================================实际运行函数=====================================================*/
static uint16 Init(void)															//无线传感器初始化
{	const st_Da_Uart	CN_st_Da_Uart={9600,8,1,0};
	uint16 Result;
	if(LessSem!=NULL)
		return De_Suc_Sensor;
	if((Result=CN_st_Fun_Uart.Init(De_Wireless_Use_Uart))!=De_Suc_Uart)
		return Result;
	if((Result=CN_st_Fun_Uart.Open(De_Wireless_Use_Uart,(st_Da_Uart	*)&CN_st_Da_Uart))!=De_Suc_Uart)
		return Result;
	LessSem=OSSemCreate(1);
	if(LessSem==NULL)
		return De_Erro_Less_NoInit;
	for(Result=0;Result<De_Less_Max_Number;Result++)
	{	CN_st_Fun_AscNumber.MoveByte(&CN_st_Less_Par_Oper[Result],(st_Less_Par_Oper	*)&CN_Ba_st_Less_Par_Oper,
		sizeof(st_Less_Par_Oper));	
		CN_st_Fun_AscNumber.MoveByte(&CN_st_Less_Val[Result],(st_Less_Val	*)&CN_Ba_st_Less_Val,
		sizeof(st_Less_Val));
		CN_st_Fun_AscNumber.MoveByte(&CN_st_Less_State[Result],(st_Sensor_State	*)&CN_Ba_st_Less_State,
		sizeof(st_Sensor_State));
	}
	CN_st_Fun_AscNumber.ClsArray(DateTime,sizeof(DateTime));
	return De_Suc_Sensor;
}

static uint16 Open(st_Sensor_DataPar	*ptst_Sensor_DataPar,uint8 *fd)	   				//配置
{	uint16 Result;
	uint8 LessNumber;
	if((LessNumber=Lookfd())==De_Less_Max_Number)
		return De_Erro_Less_OverMaxNumber;
	*fd=LessNumber;
	for(Result=0;Result<sizeof(CN_st_Sensor_Par2Type)/sizeof(st_Sensor_Par2Type);Result++)
	{	if(CN_st_Sensor_Par2Type[Result].WorkPar==ptst_Sensor_DataPar->WorkPar)
			break;
	}
	if(Result==sizeof(CN_st_Sensor_Par2Type)/sizeof(st_Sensor_Par2Type))
		return De_Erro_Less_NoWorkPar;
	CN_st_Fun_AscNumber.MoveByte(&CN_st_Less_Par_Oper[LessNumber].CN_st_Less_DataPar,ptst_Sensor_DataPar,sizeof(st_Sensor_DataPar));			
	CN_st_Less_Par_Oper[LessNumber].Type=CN_st_Sensor_Par2Type[Result].Type;
	CN_st_Less_Par_Oper[LessNumber].State=De_Less_State_Open;
	if((Result=Configuration(CN_st_Less_Par_Oper))!=De_Suc_Less)
	{	CN_st_Less_Par_Oper[LessNumber].State=De_Less_State_Close;
	   	return Result;	
	}
	CN_st_Fun_AscNumber.MoveByte(&CN_st_Less_Val[LessNumber],(st_Less_Val	*)&CN_Ba_st_Less_Val,
	sizeof(st_Less_Val));
	CN_st_Fun_AscNumber.MoveByte(&CN_st_Less_State[LessNumber],(st_Sensor_State	*)&CN_Ba_st_Less_State,
	sizeof(st_Sensor_State));
	return De_Suc_Sensor;	
}

static uint16 Close(uint8 fd)
{	uint16 Result;
	if(fd>=De_Less_Max_Number)
		return De_Erro_Less_OverMaxNumber;
	if(CN_st_Less_Par_Oper[fd].State==De_Less_State_Open)
		return De_Suc_Sensor;
	CN_st_Less_Par_Oper[fd].State=De_Less_State_Close;
	if((Result=Configuration(CN_st_Less_Par_Oper))!=De_Suc_Less)
	{	CN_st_Less_Par_Oper[fd].State=De_Less_State_Open;
		return Result; 
	}
	return De_Suc_Sensor; 		
}

static uint16 Read(uint8 fd,void *SendBuf,void *AgreeBuf)
{	uint32 MaxDly;
	uint32 *Val;
	uint8 *AgrTimer;
	uint8 OrderID;
	if(fd>=De_Less_Max_Number)
		return De_Erro_Less_OverMaxNumber;
	AgrTimer=SendBuf;
	MaxDly=GetTimeAdd(DateTime,AgrTimer);
	for(OrderID=0;OrderID<De_Less_Max_Number;OrderID++)
	{	if(CN_st_Less_Par_Oper[OrderID].State==De_Less_State_Close)
			continue;
		CN_st_Less_Val[OrderID].MaxDly+=MaxDly;
		CN_st_Less_State[OrderID].Dly=De_Sensor_State_Suc;
		if(CN_st_Less_Val[OrderID].MaxDly>CN_st_Less_Par_Oper[OrderID].CN_st_Less_DataPar.MaxDly)
			CN_st_Less_State[OrderID].Dly=De_Sensor_MaxDly_State_Erro;
	}
	CN_st_Fun_AscNumber.MoveByte(DateTime,AgrTimer,sizeof(DateTime));
	if(AgreeData(Buf,&OrderID,sizeof(Buf))==De_Suc_Less)
	{	if(OrderID==De_Less_Sensors_state_ID)
			ExplainState(Buf,sizeof(Buf),CN_st_Less_Par_Oper);
		else
			ExplainData(Buf,sizeof(Buf),OrderID,CN_st_Less_Par_Oper);
		if(OrderID==De_Less_Switch_Date_ID)						//开关量
		{	SendData(De_Less_DoorDateAsk_ID,Buf,7);	
			ClsData();
		}
	}
	if(CN_st_Less_Par_Oper[fd].State==De_Less_State_Close)
		return De_Erro_Less_FunClose;
	if(CN_st_Less_Val[fd].State!=De_Less_Val_State_New)
		return De_Erro_Less_NoData;
	if(CN_st_Less_Par_Oper[fd].Type==De_Sensor_Par_Onoff)			//开关量
	{	AgrTimer=AgreeBuf;
		*AgrTimer=CN_st_Less_Val[fd].Val;
	}
	else 
	{	Val=AgreeBuf;
		*Val=CN_st_Less_Val[fd].Val;
	}
	CN_st_Less_Val[fd].State=De_Less_Val_State_Old;
	return De_Suc_Sensor;
}



static uint16 GetState(st_Sensor_State	*ptst_Less_State,uint8 fd)
{	if(fd>=De_Less_Max_Number)
		return De_Erro_Less_OverMaxNumber;
	if(CN_st_Less_Par_Oper[fd].State==De_Less_State_Close)
		return De_Erro_Less_FunClose;
	CN_st_Fun_AscNumber.MoveByte(ptst_Less_State,&CN_st_Less_State[fd],sizeof(st_Sensor_State));
	return De_Suc_Sensor;
}

/*=========================================服务函数===========================================================*/
static uint16 ExplainData(uint8 *Buf,uint16 SizeofBuf,uint8 OrderID,st_Less_Par_Oper	*ptst_Less_Par_Oper)
{	uint32 Addree,ParValue;
	uint16 WorkID;
	uint8 fd;
	Addree=Buf[0]*0x1000000+Buf[1]*0x10000+Buf[2]*0x100+Buf[3];
	WorkID=Buf[4]*0x100+Buf[5];

	if((fd=LookID(Addree,WorkID,ptst_Less_Par_Oper))==De_Less_MaxNumber)
		return De_Suc_Sensor;
	if(OrderID==De_Less_Switch_Date_ID)	
	{	ParValue=De_Sensor_Par_Onoff_Open;
		if(Buf[6]==De_Less_In_Onoff_Close)
			ParValue=De_Sensor_Par_Onoff_Close;
	}
	else
	{	ParValue=Buf[7]*100+Buf[8]*10;
		if(Buf[6]==De_Less_In_Temp_Negative)
			ParValue=0XFFFFFFFF-ParValue;
	}
	CN_st_Less_Val[fd].Val=ParValue;
	CN_st_Less_Val[fd].State=De_Less_Val_State_New;
	CN_st_Less_Val[fd].MaxDly=0;
	return De_Suc_Sensor;		
}

static uint16 ExplainState(uint8 *Buf,uint16 SizeofBuf,st_Less_Par_Oper	*ptst_Less_Par_Oper)
{	uint32 Addree;
	uint16 WorkID;
	uint16 i,j;
	uint8 fd;		
	for(i=0,j=1;i<Buf[0];i++,j+=2)
	{	Addree=Buf[j++]*0x1000000+Buf[j++]*0x10000+Buf[j++]*0x100+Buf[j++];
		WorkID=Buf[j++]*0x100+Buf[j++];
		if((fd=LookID(Addree,WorkID,ptst_Less_Par_Oper))==De_Less_MaxNumber)	
			continue;
		CN_st_Less_Val[fd].MaxDly=0;
		CN_st_Less_State[fd].Work=De_Sensor_State_Suc;
		if(Buf[j+1]==De_Less_Dev_Erro)
			CN_st_Less_State[fd].Work=De_Sensor_Par_State_Erro;
		CN_st_Less_State[fd].Battery=De_Sensor_State_Suc;
		if(Buf[j+2]==De_Less_DevBa_Erro)
			CN_st_Less_State[fd].Battery=De_Sensor_Battery_State_Erro;				
	}
	return De_Suc_Sensor;
}
static uint8 LookID(uint32 Addree,uint16 WorkID,st_Less_Par_Oper	*ptst_Less_Par_Oper)
{	uint8 i;
	for(i=0;i<De_Less_Max_Number;i++)
	{	if((CN_st_Less_Par_Oper[i].CN_st_Less_DataPar.Addree==Addree)&&
		(CN_st_Less_Par_Oper[i].CN_st_Less_DataPar.WorkPar==WorkID)&&(CN_st_Less_Par_Oper[i].State==De_Less_State_Open))
			break;
	}
	return i;
}
/*===========================================================================================================*/
static uint16 Configuration(st_Less_Par_Oper	*ptst_Less_DataParOut) 	  			//配置命令
{	uint8 Buf[1+De_Less_Max_Number*6];
	uint16 i,SizeofBuf;
	uint8 DataByte,OrderID;
	SizeofBuf=0;
	Buf[SizeofBuf++]=0;
	for(i=0;i<De_Less_Max_Number;i++)
	{	if(CN_st_Less_Par_Oper[i].State==De_Less_State_Close)	
			continue;	
		Buf[SizeofBuf++]=((CN_st_Less_Par_Oper[i].CN_st_Less_DataPar.Addree>>24)&0xff);
		Buf[SizeofBuf++]=((CN_st_Less_Par_Oper[i].CN_st_Less_DataPar.Addree>>16)&0xff);
		Buf[SizeofBuf++]=((CN_st_Less_Par_Oper[i].CN_st_Less_DataPar.Addree>>8)&0xff);
		Buf[SizeofBuf++]=((CN_st_Less_Par_Oper[i].CN_st_Less_DataPar.Addree)&0xff);
		Buf[SizeofBuf++]=((CN_st_Less_Par_Oper[i].CN_st_Less_DataPar.WorkPar>>8)&0xff);
		Buf[SizeofBuf++]=((CN_st_Less_Par_Oper[i].CN_st_Less_DataPar.WorkPar)&0xff);
		Buf[0]++;
	}
	if(Buf[0]==0)
		return De_Suc_Sensor;
	for(i=0;i<De_Less_Max_Number;i++)
	{	ClsData();
		SendData(De_Less_Configuration_Receive_ID,Buf,SizeofBuf);	
		OSTimeDly(De_Less_Dly_Order);
	 	if(AgreeData(&DataByte,&OrderID,sizeof(DataByte))!=De_Suc_Less)
			continue;		
		if(OrderID!=De_Less_Configuration_Ask_ID)
			continue;
	   	if(DataByte!=De_Less_Config_Suc)
			continue;		
		return De_Suc_Sensor;
	}
	return De_Erro_Less_Config;
}

static void SendData(uint8 ID,uint8 *Buf,uint16 SizeofBuf)		//发送数据
{	uint8 SendBuf[3];

	uint16 CrcVal;
	WriteData((uint8 *)Com_FlagHead,sizeof(Com_FlagHead));
	SendBuf[0]=(((SizeofBuf+3)>>8)&0xff);
	SendBuf[1]=((SizeofBuf+3)&0xff);
	SendBuf[2]=ID;
	CrcVal=CN_st_Fun_Arithmetic.ptst_Fun_Crc1021->Crc1021(SendBuf,3,0x0000);
	CrcVal=CN_st_Fun_Arithmetic.ptst_Fun_Crc1021->Crc1021(Buf,SizeofBuf,CrcVal);
	WriteData(SendBuf,sizeof(SendBuf));
	WriteData(Buf,SizeofBuf);
	SendBuf[0]=((CrcVal>>8)&0xff);
	SendBuf[1]=(CrcVal&0xff);
	WriteData(SendBuf,2);
	WriteData((uint8 *)Com_FlagEnd,sizeof(Com_FlagEnd));
}

static uint16 AgreeData(uint8 *Buf,uint8 *ID,uint16 SizeofBufLen) 			//接收数据
{	uint8 AgreeBuf[3];
	uint16 CrcVal,a;
	uint16 DataLen;
	CN_st_Fun_AscNumber.ClsArray(AgreeBuf,sizeof(AgreeBuf));
 	for(;(AgreeBuf[0]!='*');)
	{	if(ReadData(AgreeBuf,1)==0)
			return De_Erro_Less_NoData;
	}
	OSTimeDly(70);
	ReadData(AgreeBuf+1,2);
	if(CN_st_Fun_AscNumber.CompareBuf(AgreeBuf,(uint8 *)Com_FlagHead,sizeof(AgreeBuf))!=0) //包头错误
		return De_Erro_Less_Explain;
	if(ReadData(AgreeBuf,3)!=3)
		return De_Erro_Less_Explain;
	DataLen=AgreeBuf[0]*256+AgreeBuf[1];
	if(SizeofBufLen<DataLen-3)
		return De_Erro_Less_Explain;
	*ID=AgreeBuf[2];
	CrcVal=CN_st_Fun_Arithmetic.ptst_Fun_Crc1021->Crc1021(AgreeBuf,3,0x0000);
   	ReadData(Buf,DataLen-3);
	CrcVal=CN_st_Fun_Arithmetic.ptst_Fun_Crc1021->Crc1021(Buf,DataLen-3,CrcVal);
	ReadData(AgreeBuf,2);
	a=((uint16 )AgreeBuf[0]<<8)+(uint16 )AgreeBuf[1];
	   if(a!=CrcVal)
		return De_Erro_Less_Explain;
	ReadData(AgreeBuf,3);
	if(CN_st_Fun_AscNumber.CompareBuf(AgreeBuf,(uint8 *)Com_FlagEnd,sizeof(AgreeBuf))!=0) //包头错误
		return De_Erro_Less_Explain;
	return De_Suc_Sensor;
}
/*=====================================直接硬件操作===========================================================*/
static uint16 ReadData(uint8 *Buf,uint16 ReadLen)
{  	return CN_st_Fun_Uart.Read(De_Wireless_Use_Uart,Buf,ReadLen);	 
}			
static uint16 WriteData(uint8 *Buf,uint16 WriteLen)
{	return CN_st_Fun_Uart.Write(De_Wireless_Use_Uart,Buf,WriteLen);
}
static void ClsData(void)
{	uint8 Data;
	while(CN_st_Fun_Uart.Read(De_Wireless_Use_Uart,&Data,1)==1);
}
static uint16 Lookfd(void)
{	uint8 i;
	for(i=0;i<De_Less_Max_Number;i++)
	{	if(CN_st_Less_Par_Oper[i].State==De_Less_State_Close)
			break;
	}
	return i;
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
