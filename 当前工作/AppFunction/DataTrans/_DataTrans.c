#define De_DataTrans_Compiler
#include "DataTrans.h"
uint8 Trans_Gps(st_Data_Gps	*ptst_Data_Gps,st_Sys_State *ptst_Sys_State,uint8 *OutBuf)
{	Trans_Gps_Timer(ptst_Data_Gps,OutBuf+De_DataTrans_Gps_Timer);					//获取时间,	
	Trans_Gps_Latitude(ptst_Data_Gps,OutBuf+De_DataTrans_Gps_Latitude);
	Trans_Gps_LongHem(ptst_Data_Gps,OutBuf+De_DataTrans_Gps_LongHem);
	OutBuf[De_DataTrans_Gps_Location]=Trans_Gps_Location(ptst_Data_Gps);
	Trans_Gps_Speed(ptst_Data_Gps,OutBuf+De_DataTrans_Gps_Speed);
	Trans_Gps_Angle(ptst_Data_Gps,OutBuf+De_DataTrans_Gps_Angle);
	Trans_Gps_Year(ptst_Data_Gps,OutBuf+De_DataTrans_Gps_Year);
	Trans_Gps_State(ptst_Sys_State,OutBuf+De_DataTrans_Gps_State);
	return CN_st_Fun_AscNumber.Strsize(OutBuf);
}


uint8 Trans_Gps_Hand(st_Data_Gps	*ptst_Data_Gps,st_Sys_State *ptst_Sys_State,uint8 *OutBuf)
{	Trans_Gps_Timer(ptst_Data_Gps,OutBuf+De_DataTrans_Gps_Timer);					//获取时间,	
	Trans_Gps_Latitude(ptst_Data_Gps,OutBuf+De_DataTrans_Gps_Latitude);
	Trans_Gps_LongHem(ptst_Data_Gps,OutBuf+De_DataTrans_Gps_LongHem);
	OutBuf[De_DataTrans_Gps_Location]=Trans_Gps_Location(ptst_Data_Gps)-0x30;
	OutBuf[De_DataTrans_Gps_Location]|=(CN_st_Fun_Date.GetWeek(ptst_Data_Gps->CN_st_Gps_Data_GPRMC.DateTime)<<4);
	Trans_Gps_Speed(ptst_Data_Gps,OutBuf+De_DataTrans_Gps_Speed);
	Trans_Gps_Angle(ptst_Data_Gps,OutBuf+De_DataTrans_Gps_Angle);
	Trans_Gps_Year(ptst_Data_Gps,OutBuf+De_DataTrans_Gps_Year);
	Trans_Gps_State(ptst_Sys_State,OutBuf+De_DataTrans_Gps_State);
	return CN_st_Fun_AscNumber.Strsize(OutBuf);
}


static void Trans_Gps_Timer(st_Data_Gps	*ptst_Data_Gps,uint8 *OutBuf)				//时间转换
{	CN_st_Fun_AscNumber.Bcd2Asc(ptst_Data_Gps->CN_st_Gps_Data_GPRMC.DateTime+4,OutBuf,3);			
}


static void Trans_Gps_Latitude(st_Data_Gps	*ptst_Data_Gps,uint8 *OutBuf)			//纬度转化
{	uint8 Buf[11];
	uint8 DataLen;	
	memset(OutBuf,'0',8);
	CN_st_Fun_AscNumber.ClsArray(Buf,sizeof(Buf));
	CN_st_Fun_AscNumber.Algorism2Asc(ptst_Data_Gps->CN_st_Gps_Data_GPRMC.Latitude,Buf);
	DataLen=strlen((char *)Buf);
	if(DataLen>8)
		DataLen=8;
	CN_st_Fun_AscNumber.MoveByte(OutBuf+8-DataLen,Buf,DataLen);
}
static void Trans_Gps_LongHem(st_Data_Gps	*ptst_Data_Gps,uint8 *OutBuf)			//经度转换
{	uint8 Buf[11];
	uint8 DataLen;
	memset(OutBuf,'0',9);
	CN_st_Fun_AscNumber.ClsArray(Buf,sizeof(Buf));
	CN_st_Fun_AscNumber.Algorism2Asc(ptst_Data_Gps->CN_st_Gps_Data_GPRMC.Longitude,Buf);
	DataLen=strlen((char *)Buf);
	if(DataLen>9)
		DataLen=9;
    CN_st_Fun_AscNumber.MoveByte(OutBuf+9-DataLen,Buf,DataLen);
}

static uint8 Trans_Gps_Location(st_Data_Gps	*ptst_Data_Gps)							//定位状态
{	uint8 Result;
	if(ptst_Data_Gps->CN_st_Gps_Data_GPRMC.LocationTrue==De_Gps_Location_True)	//有效定位
	{	if((ptst_Data_Gps->CN_st_Gps_Data_GPRMC.LatHem==De_Gps_LatHem_S)&&(ptst_Data_Gps->CN_st_Gps_Data_GPRMC.LongHem==De_Gps_LongHem_W))
			Result='0';
		else if((ptst_Data_Gps->CN_st_Gps_Data_GPRMC.LatHem==De_Gps_LatHem_N)&&(ptst_Data_Gps->CN_st_Gps_Data_GPRMC.LongHem==De_Gps_LongHem_W))
			Result='2';
		else if((ptst_Data_Gps->CN_st_Gps_Data_GPRMC.LatHem==De_Gps_LatHem_S)&&(ptst_Data_Gps->CN_st_Gps_Data_GPRMC.LongHem==De_Gps_LongHem_E))
			Result='4';			
		else if((ptst_Data_Gps->CN_st_Gps_Data_GPRMC.LatHem==De_Gps_LatHem_N)&&(ptst_Data_Gps->CN_st_Gps_Data_GPRMC.LongHem==De_Gps_LongHem_E))
			Result='6';
		else
			Result='8';
	}
	else
	{ 	if((ptst_Data_Gps->CN_st_Gps_Data_GPRMC.LatHem==De_Gps_LatHem_S)&&(ptst_Data_Gps->CN_st_Gps_Data_GPRMC.LongHem==De_Gps_LongHem_W))
			Result='1';
		else if((ptst_Data_Gps->CN_st_Gps_Data_GPRMC.LatHem==De_Gps_LatHem_N)&&(ptst_Data_Gps->CN_st_Gps_Data_GPRMC.LongHem==De_Gps_LongHem_W))
			Result='3';
		else if((ptst_Data_Gps->CN_st_Gps_Data_GPRMC.LatHem==De_Gps_LatHem_S)&&(ptst_Data_Gps->CN_st_Gps_Data_GPRMC.LongHem==De_Gps_LongHem_E))
			Result='5';			
		else if((ptst_Data_Gps->CN_st_Gps_Data_GPRMC.LatHem==De_Gps_LatHem_N)&&(ptst_Data_Gps->CN_st_Gps_Data_GPRMC.LongHem==De_Gps_LongHem_E))
			Result='7';
		else
			Result='8';
	}
	return Result;
}

static void Trans_Gps_Speed(st_Data_Gps	*ptst_Data_Gps,uint8 *OutBuf)						//速度
{ 	uint8 Buf[11];
	uint8 DataLen;
	memset(OutBuf,'0',2);
	CN_st_Fun_AscNumber.ClsArray(Buf,sizeof(Buf));
	CN_st_Fun_AscNumber.Algorism2Asc(ptst_Data_Gps->CN_st_Gps_Data_GPRMC.Speed/2,Buf);
	DataLen=strlen((char *)Buf);
	if(DataLen>2)
		DataLen=2;
	CN_st_Fun_AscNumber.MoveByte(OutBuf+2-DataLen,Buf,DataLen);
}

static void Trans_Gps_Angle(st_Data_Gps	*ptst_Data_Gps,uint8 *OutBuf)						//角度 
{	uint8 Buf[11];
	uint8 DataLen;
	memset(OutBuf,'0',2);
	CN_st_Fun_AscNumber.ClsArray(Buf,sizeof(Buf));
	CN_st_Fun_AscNumber.Algorism2Asc(ptst_Data_Gps->CN_st_Gps_Data_GPRMC.Angle/100,Buf);
	DataLen=strlen((char *)Buf);
	if(DataLen>2)
		DataLen=2;
	CN_st_Fun_AscNumber.MoveByte(OutBuf+2-DataLen,Buf,DataLen);
}

static void Trans_Gps_Year(st_Data_Gps	*ptst_Data_Gps,uint8 *OutBuf)					//年
{	CN_st_Fun_AscNumber.Bcd2Asc(ptst_Data_Gps->CN_st_Gps_Data_GPRMC.DateTime+3,OutBuf,1);
	CN_st_Fun_AscNumber.Bcd2Asc(ptst_Data_Gps->CN_st_Gps_Data_GPRMC.DateTime+2,OutBuf+2,1);
	CN_st_Fun_AscNumber.Bcd2Asc(ptst_Data_Gps->CN_st_Gps_Data_GPRMC.DateTime+1,OutBuf+4,1);	
}

static void Trans_Gps_State(st_Sys_State	*ptst_Sys_State,uint8 *OutBuf)
{	uint8 S[3];
	S[0]=S[1]=S[2]=0;
	if(ptst_Sys_State->AccState==De_Acc_State_Close)
		S[0]|=0x40;
	if(ptst_Sys_State->GpsState==De_Erro_State_GpsBad)
		S[1]|=0x10;
	if(ptst_Sys_State->voltage!=De_Suc_State)
		S[1]|=0x01;
	if(ptst_Sys_State->Control!=De_Suc_State)
		S[2]|=0X08;								
	CN_st_Fun_AscNumber.HexBuf2Asc(S,OutBuf,sizeof(S));
}





/*	当GPS正常时才能跳出这个函数		



*/
/*
static void Get_Gps_Data(uint8 *Buf)						//获取GPS数据
{	st_Data_Gps		CN_st_Data_Gps;
	uint8 State;
	State=CN_st_Sys_State.Sleep;
	if(State!=De_Suc_State)							//系统处于休眠状态
	{	;											//发送唤醒系统
	}
	CN_st_Control_Fun_Gps.Read(&CN_st_Data_Gps);
	Trans_Gps(&CN_st_Data_Gps,&CN_st_Sys_State,Buf);	
}


static void SendMessage(uint8 *Buf,uint8 *Phone)						//发送短信息
{	uint16 Result=1;
	if(CN_st_Sys_State.GsmState==De_Suc_State)							//正常
 		Result=SendMessage(uint8 *Message,uint8 *Phone);
	if(Result!=De_Suc_Gprs)												//不成功
	{	;						//写数据表	
		;
	}				
} */





