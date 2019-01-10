#define De_SmsTzxy_Compiler
#include "SmsTzxy.h"
static uint16 Init(void)
{	uint8 i;
	if(SmsSem!=NULL)
		return De_Suc_Sensor;
	for(i=0;i<De_GprsTzxy_Dev_Number;i++)
	{	CN_State[i]=De_GprsTzxy_Fun_Close;
	 	CN_Gprsfd[i]=De_GprsTzxy_Nofd;
	}			
	if((SmsSem=OSSemCreate(1))==NULL)
		return De_Erro_SmsTzxy_Init;
	return De_Suc_Sensor;
}
static uint16 Open(st_Sensor_DataPar	*ptst_Sensor_DataPar,uint8 *fd)
{	//st_Affair_Message CN_st_Affair_Message={NULL};
	st_Sensor_Sms_DataPar *ptst_Sensor_Sms_DataPar;
	uint8 err;
	OSSemPend(SmsSem, 0, &err);
	for(err=0;err<De_GprsTzxy_Dev_Number;err++)
	{	if(CN_State[err]==De_GprsTzxy_Fun_Close)
			break;
	}
	if(err==De_GprsTzxy_Dev_Number)
	{	OSSemPost(SmsSem);
		return De_Erro_SmsTzxy_OverMaxNumber;
	}
	CN_State[err]=De_GprsTzxy_Fun_Open; 
	*fd=err;
	CN_Gprsfd[err]=ptst_Sensor_DataPar->Addree;
	//CN_st_Fun_Gprs.OpenMessage(&CN_st_Affair_Message);
	ptst_Sensor_Sms_DataPar=(st_Sensor_Sms_DataPar *)ptst_Sensor_DataPar;
	CN_st_Fun_AscNumber.MoveByte(CN_st_Sms_Order_Data.Phone,ptst_Sensor_Sms_DataPar->Phone,CN_st_Fun_AscNumber.Strsize16(ptst_Sensor_Sms_DataPar->Phone));
	OSSemPost(SmsSem);
	return De_Suc_Sensor;
}
static uint16 Close(uint8 fd)
{	uint8 err;
	OSSemPend(SmsSem, 0, &err);
	if(fd>=De_GprsTzxy_Dev_Number)
	{	OSSemPost(SmsSem);
		return De_Erro_SmsTzxy_OverMaxNumber;
	}
	OSSemPost(SmsSem);
	CN_State[fd]=De_GprsTzxy_Fun_Close;
	return De_Suc_Sensor;
}
static uint16 Read(uint8 fd,void *SendBuf,void *AgreeBuf)
{	st_Dev_Tzxy_Send	*ptst_Dev_Tzxy_Send;
	st_Dev_Tzxy_Agree	*ptst_Dev_Tzxy_Agree;
	uint16 Result;
	uint8 err;
	if((fd>=De_GprsTzxy_Dev_Number)||(CN_State[fd]!=De_GprsTzxy_Fun_Open))
		return De_Erro_SmsTzxy_OverMaxNumber;
	OSSemPend(SmsSem, 0, &err);
	ptst_Dev_Tzxy_Send=SendBuf;
	if(ptst_Dev_Tzxy_Send->ResultOrSend==De_Tzxy_SendBuf_Send)
	{	Result=Send(CN_Gprsfd[fd],ptst_Dev_Tzxy_Send->Buf,ptst_Dev_Tzxy_Send->SizeofBuf);
		OSSemPost(SmsSem);
		return Result;
	}
	ptst_Dev_Tzxy_Agree=AgreeBuf;
	Result=Agree(CN_Gprsfd[fd],ptst_Dev_Tzxy_Agree->Buf,&ptst_Dev_Tzxy_Agree->SizeofBuf);
	OSSemPost(SmsSem);
	return Result;
}

static uint16 Agree(uint8 fd,uint8 *Buf,uint16 *ReLen)
{	
	uint8 BagSum,BagNumber;
	uint16 OrderNumber;
	uint16 DataLen,Result;
	uint32 OverTimer;
	CN_st_Fun_AscNumber.ClsArray(AgreeBuf,sizeof(AgreeBuf));
	CN_st_Fun_AscNumber.ClsArray(Phone,sizeof(Phone));
	Result=CN_st_Fun_Gprs.ReadMessage(Phone,AgreeBuf);
	if(Result!=De_Suc_Sensor)
		return Result;
	if(CN_st_Fun_AscNumber.CompareBuf(Phone,CN_st_Sms_Order_Data.Phone,CN_st_Fun_AscNumber.Strsize16(CN_st_Sms_Order_Data.Phone))!=0)
		return De_Erro_AgreeOn_Dev_Sms_NoData;
	DataLen=CN_st_Fun_AscNumber.Strsize16(AgreeBuf);
	CN_st_Fun_AscNumber.Asc2HexBuf(AgreeBuf,AgreeBuf,DataLen);
	
	OrderNumber=((uint16)AgreeBuf[0]<<8)+AgreeBuf[1];
	BagSum=AgreeBuf[2];
	BagNumber=AgreeBuf[3];
	if(BagSum>De_Sms_MaxBagNum)
		return De_Erro_AgreeOn_Dev_Sms_MuchBag;
	if(CN_st_Sms_Order_Data.OrderNumber!=OrderNumber)
	{	CN_st_Sms_Order_Data.OrderNumber=OrderNumber;
		CN_st_Sms_Order_Data.BagNumber=1;
		CN_st_Sms_Order_Data.BagSum=BagSum;
		CN_st_Fun_AscNumber.ClsArray(&CN_st_Sms_Data,sizeof(CN_st_Sms_Data));
		CN_st_Sms_Data[BagNumber-1].Len=DataLen/2-4;
		CN_st_Fun_AscNumber.MoveByte(CN_st_Sms_Data[BagNumber-1].Data,AgreeBuf+4,CN_st_Sms_Data[BagNumber-1].Len);
	}
	else
	{	CN_st_Sms_Order_Data.BagNumber++;
		CN_st_Sms_Data[BagNumber-1].Len=DataLen/2-4;
		CN_st_Fun_AscNumber.MoveByte(CN_st_Sms_Data[BagNumber-1].Data,AgreeBuf+4,CN_st_Sms_Data[BagNumber-1].Len);	
	}
	if(CN_st_Sms_Order_Data.BagSum==CN_st_Sms_Order_Data.BagNumber)
	{	for(DataLen=0,BagNumber=0;BagNumber<CN_st_Sms_Order_Data.BagSum;BagNumber++)
		{	CN_st_Fun_AscNumber.MoveByte(Buf+DataLen,CN_st_Sms_Data[BagNumber].Data,CN_st_Sms_Data[BagNumber].Len);
			DataLen+=CN_st_Sms_Data[BagNumber].Len;	
		}
		*ReLen=DataLen;
		SendOrderNumber=CN_st_Sms_Order_Data.OrderNumber;
		return De_Suc_Sensor; 
	}
	return De_Erro_AgreeOn_Dev_Sms_NoData;
}

static uint16 Send(uint8 fd,uint8 *Buf,uint16 DataLen)
{	uint8 SendBuf[4],SendCount;
	uint8 BagNumber,BagSum;
	uint16 SmsDataLen,SendDataLen,Result;
//	SmsDataLen=(DataLen<<1);
	BagNumber=DataLen/66;
	if(DataLen%66)
		BagNumber++;
	BagSum=BagNumber;	
	for(BagNumber=1,SendDataLen=0;BagNumber<=BagSum;BagNumber++)
	{	SendBuf[0]=(uint8)(SendOrderNumber>>8);
		SendBuf[1]=(uint8)SendOrderNumber;
		SendBuf[2]=BagSum;
		SendBuf[3]=BagNumber;
		CN_st_Fun_AscNumber.ClsArray(AgreeBuf,sizeof(AgreeBuf));
		CN_st_Fun_AscNumber.HexBuf2Asc(SendBuf,AgreeBuf,4);
		if(BagNumber==BagSum)
			CN_st_Fun_AscNumber.HexBuf2Asc(Buf+SendDataLen,AgreeBuf+8,DataLen%66);
		else	
		{	CN_st_Fun_AscNumber.HexBuf2Asc(Buf+SendDataLen,AgreeBuf+8,66);
			SendDataLen+=66;		
		}
		for(SendCount=0;SendCount<3;SendCount++,OSTimeDly(2000))
		{	if((Result=CN_st_Fun_Gprs.SendMessage(CN_st_Sms_Order_Data.Phone,AgreeBuf))!=De_Suc_Gprs)
				continue;
			break;
		}
		if(SendCount==3)
			return De_Erro_AgreeOn_Dev_Sms_Send;	
	}
	SendOrderNumber++;	
 	return 	De_Suc_Sensor;
}


