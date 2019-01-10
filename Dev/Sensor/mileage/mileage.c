#define De_Mileage_Compiler
#include "mileage.h"


static uint16 Init(void)
{  	
	if(MileageSem != NULL)
		return De_Suc_Mileage;
	if((MileageSem=OSSemCreate(1))==NULL)
		return De_Erro_Mileage_NoInit; 
	CN_st_Mileage_Par_Oper.State = De_Mileage_State_Close;	 		
	CN_st_Fun_AscNumber.ClsArray(DateTime,sizeof(DateTime));
	CN_st_Fun_AscNumber.ClsArray(&CN_LctDat,sizeof(st_LctDat));
	CN_st_Fun_RTC.Read(DateTime);
	return De_Suc_Mileage;	
}
static uint16 Open(st_Sensor_DataPar	*ptst_Sensor_DataPar,uint8 *fd)
{
	uint8 i;
	OSSemPend(MileageSem,0,&i);
	if(CN_st_Mileage_Par_Oper.State == De_Mileage_State_Open)
		return De_Erro_Mileage_OverMaxNumber;
	CN_st_Mileage_Par_Oper.State = De_Mileage_State_Open;

	*fd = 0;   

	for(i=0;i<sizeof(CN_st_Sensor_Par2Type)/sizeof(st_Sensor_Par2Type);i++)
	{	if(CN_st_Sensor_Par2Type[i].WorkPar == ptst_Sensor_DataPar->WorkPar)
			break;
	}
	if(i == sizeof(CN_st_Sensor_Par2Type)/sizeof(st_Sensor_Par2Type))
	{
		OSSemPost(MileageSem);
		return De_Erro_Mileage_NoWorkPar;	 //工作参数错误
	}

	CN_st_Fun_AscNumber.MoveByte(&CN_st_Mileage_Par_Oper.CN_st_Mileage_DataPar,ptst_Sensor_DataPar,  \
								 sizeof(st_Sensor_DataPar));			
	CN_st_Mileage_Par_Oper.Type  = CN_st_Sensor_Par2Type[0].Type;
	CN_st_Mileage_Par_Oper.State = De_Mileage_State_Open;

	ReadFist = 0;

	OSSemPost(MileageSem);
	return De_Suc_Mileage;
}

static uint16 Close(uint8 fd)		//关闭
{
	uint8 i;
	OSSemPend(MileageSem, 0, &i);
	if(fd>0)
		return De_Erro_Mileage_OverMaxNumber;
	if(CN_st_Mileage_Par_Oper.State==De_Mileage_State_Close)
	{
		OSSemPost(MileageSem);
		return De_Suc_Mileage;
	}  	
	CN_st_Mileage_Par_Oper.State = De_Mileage_State_Close;
	OSSemPost(MileageSem); 	
	return De_Suc_Mileage;
}

static uint16 Read(uint8 fd,void *SendBuf,void *AgreeBuf)
{
	uint8 i,j; 
	uint32 *ReBuf;
	uint32 value;
	st_GpsPonit TempPoint;
	uint8 *CurTime;
	uint32 Dly;
	st_LctDat *pCurDat;	
	st_Data_Gps *pGpsData;
	
	OSSemPend(MileageSem, 0, &i);
	
	if(fd != 0)
	{
		OSSemPost(MileageSem);
		return De_Erro_Mileage_OverMaxNumber;
	}
	if(CN_st_Mileage_Par_Oper.State == De_Mileage_State_Close)
	{
		OSSemPost(MileageSem);
		return De_Erro_Mileage_Fun_NoOpen;	
	}  	 	
	
	pGpsData = (st_Data_Gps *)SendBuf;
	CurTime = pGpsData->CN_st_Gps_Data_GPRMC.DateTime; 
	Dly = GetTimeAdd(DateTime,CurTime);		 //计算两次读里程的时间差
	CN_st_Fun_AscNumber.MoveByte(DateTime,CurTime,sizeof(DateTime));  //更新时间

	ReBuf=AgreeBuf;
	if(pGpsData->CN_st_Gps_Data_GPRMC.LocationTrue == 'V')   //不定位
	{
		
		*ReBuf = 0;	
	   	OSSemPost(MileageSem);
		return De_Suc_Mileage;	  //定位无效时传入的里程不进行计算,同时不更新经纬度数据
	}
	if(pGpsData->CN_st_Gps_Data_GPRMC.Speed < 3)  
	{			
		*ReBuf = 0;	
	   	OSSemPost(MileageSem);
		return De_Suc_Mileage;	  //速度小于3km/h 里程不进行计算,同时不更新经纬度数据
	}

	pCurDat = (st_LctDat *)(&pGpsData->CN_st_Gps_Data_GPRMC.Latitude);
	value = CalcMil(&CN_LctDat,pCurDat);	

	if(ReadFist == 0)		  //前5个数据用来获取初始点
	{
		PointCount++;
		CN_st_Fun_AscNumber.MoveByte(&CN_GpsPoint[PointCount],pCurDat,8);	   	
		CN_GpsPoint[PointCount].Mileage = value;
		if(PointCount <5)
		{
			CN_st_Fun_AscNumber.MoveByte(&CN_LctDat,pCurDat,sizeof(st_LctDat));	   //更新当前经纬度信息	
		}
		else
		{
			for(i=1;i<6;i++) 	   //排序
			{ 
				for(j=5;j>=i;j--) 
				{ 
					if(CN_GpsPoint[j].Mileage<CN_GpsPoint[j-1].Mileage) 
					{ 
						CN_st_Fun_AscNumber.MoveByte(&TempPoint,&CN_GpsPoint[j-1],sizeof(st_GpsPonit));
						CN_st_Fun_AscNumber.MoveByte(&CN_GpsPoint[j-1],&CN_GpsPoint[j],sizeof(st_GpsPonit));
						CN_st_Fun_AscNumber.MoveByte(&CN_GpsPoint[j],&TempPoint,sizeof(st_GpsPonit));							
					} 
				} 
			}
			CN_st_Fun_AscNumber.MoveByte(&CN_LctDat,&CN_GpsPoint[3],8);	   //取排序后中间的数据为初始点					
			ReadFist = 1;				
		}	
		
		*ReBuf = 0;	 		
	   	OSSemPost(MileageSem);
		return De_Suc_Mileage;	  //认为是漂移很大的点里程不进行计算,同时不更新经纬度数据	
		
	}	
    
	if(value >= 50*Dly)  //按照最高时速 180km/h计算，每秒不超过50 m
	{
		*ReBuf = 0;	 		
	   	OSSemPost(MileageSem);
		return De_Suc_Mileage;	  //认为是漂移很大的点里程不进行计算,同时不更新经纬度数据		
	} 
	
	CN_st_Fun_AscNumber.MoveByte(&CN_LctDat,pCurDat,sizeof(st_LctDat));	   //更新当前经纬度信息
	
	ReBuf  = AgreeBuf;
	*ReBuf = value;

   	OSSemPost(MileageSem);
	return De_Suc_Mileage;	
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


//++++++++++++++++++++++++++++++++++++里程统计部分++++++++++++++++++++++++++++++++++++++++++


//利用经纬度差来计算距离  
static float CalcMil(st_LctDat *pStart,st_LctDat *pEnd)
{ 	
	uint32 x1,y1;
	uint32 x2,y2;
	float CurRadLong = 0;	//两点经纬度的弧度
	float CurRadLat = 0; 
	float PreRadLong = 0;
	float PreRadLat = 0;
	float a,b;              //经纬度弧度差
	float MilValue;	  

	x1 = pStart->Longitude;	   // 经度
	y1 = pStart->Latitude;	   // 维度
	x2 = pEnd  ->Longitude;
	y2 = pEnd  ->Latitude;

	//将经纬度换算成弧度
	CurRadLong = (float)(x1)/1000000.0;
	CurRadLong = CurRadLong*PI/180.0;    	

	PreRadLong = (float)(x2)/1000000.0 ;  		 
	PreRadLong = PreRadLong*PI/180.0; 	

	CurRadLat  = (float)(y1)/1000000.0;
	CurRadLat = CurRadLat*PI/180.0;   

	PreRadLat  = (float)(y2)/1000000.0 ;  		 
	PreRadLat  = PreRadLat*PI/180.0;	

    //计算经纬度差值
 	if(CurRadLat>PreRadLat)		    
	{
		a = CurRadLat - PreRadLat ;	
	}
	else
	{
		a = PreRadLat - CurRadLat;
	}  

	if(CurRadLong>PreRadLong)
	{
		b = CurRadLong -PreRadLong ;	
	}
	else
	{
		b = PreRadLong - CurRadLong;
	}  	

	MilValue = 2*(sqrt(sin(a/2.0)*sin(a/2.0)+cos(CurRadLat)*cos(PreRadLat)*sin(b/2.0)*sin(b/2.0)));
	MilValue = (float)EARTH_RADIUS*MilValue;
	return(MilValue);
} 


