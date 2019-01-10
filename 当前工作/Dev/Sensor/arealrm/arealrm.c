#define De_Arealrm_Compiler
#include "arealrm.h"

static uint16 Init(void)
{
	uint8 i;
	if(ArealrmSem != NULL) 	
		return De_Suc_Arealrm;

	if((ArealrmSem = OSSemCreate(1)) == NULL)
		return De_Erro_Arealrm_NoInit;
	for(i=0;i<De_Arealrm_Max_TypeNum;i++)
	{
		CN_st_Arealrm_Par_Oper[i].State = De_Arealrm_State_Close;
	}
	return De_Suc_Arealrm;
}

static uint16 Open(st_Sensor_DataPar  *ptst_Sensor_DataPar,uint8 *fd)
{
	uint8 i;
	
	uint8 ArealrmType;
	un_OpenPar *ptun_OpenPar;
	
	OSSemPend(ArealrmSem, 0, &i);

	ptun_OpenPar = (un_OpenPar *)ptst_Sensor_DataPar;

	for(i=0;i<De_Arealrm_Max_TypeNum;i++)
	{
		if(CN_st_Arealrm_Par_Oper[i].State == De_Arealrm_State_Close)		
			break;	 		
	}
	if(i==De_Arealrm_Max_TypeNum)
	{
		OSSemPost(ArealrmSem);
		return De_Erro_Arealrm_OverMaxNumber;
	}
	ArealrmType = i;
	*fd = ArealrmType;

	for(i=0;i<sizeof(CN_st_Sensor_Par2Type)/sizeof(st_Sensor_Par2Type);i++)
	{	if(CN_st_Sensor_Par2Type[i].WorkPar == ptun_OpenPar->CN_st_Sensor_DataPar.WorkPar)
			break;
	}
	if(i == sizeof(CN_st_Sensor_Par2Type)/sizeof(st_Sensor_Par2Type))
	{
		OSSemPost(ArealrmSem);
		return De_Erro_Arealrm_NoWorkPar;	
	}

	CN_st_Fun_AscNumber.MoveByte(&CN_st_Arealrm_Par_Oper[ArealrmType].CN_st_Arealrm_DataPar,   \
								 &ptun_OpenPar->CN_st_Open_RunLen,  sizeof(st_Open_RunLen));	
								 		
	CN_st_Arealrm_Par_Oper[ArealrmType].Type = CN_st_Sensor_Par2Type[i].Type;
	CN_st_Arealrm_Par_Oper[ArealrmType].State = De_Arealrm_State_Open;

	OSSemPost(ArealrmSem);
	return De_Suc_Arealrm;
}

static uint16 Close(uint8 fd)		//关闭
{
	uint8 i;
	OSSemPend(ArealrmSem, 0, &i);
	if(fd>=De_Arealrm_Max_TypeNum)
		return De_Erro_Arealrm_OverMaxNumber;
	if(CN_st_Arealrm_Par_Oper[fd].State==De_Arealrm_State_Close)
	{
		OSSemPost(ArealrmSem);
		return De_Suc_Arealrm;
	}	
	CN_st_Arealrm_Par_Oper[fd].State = De_Arealrm_State_Close;
	OSSemPost(ArealrmSem); 
	return De_Suc_Arealrm;
}

static uint16 Read(uint8 fd,void *SendBuf,void *AgreeBuf)
{  
	uint8 i; 
	uint8 *ReBuf;


	uint8 *CurTime;
	st_LctDat *pCurDat;			
	st_Data_Gps *pGpsData;
	
	OSSemPend(ArealrmSem, 0, &i);
	if(fd >= De_Arealrm_Max_TypeNum)
	{
		OSSemPost(ArealrmSem);
		return De_Erro_Arealrm_OverMaxNumber;
	 }
	if(CN_st_Arealrm_Par_Oper[fd].State == De_Arealrm_State_Close)
	{
		OSSemPost(ArealrmSem);
		return De_Erro_Arealrm_NoOpen;	
	}  	
	pGpsData = (st_Data_Gps *)SendBuf;
	CurTime = pGpsData->CN_st_Gps_Data_GPRMC.DateTime; 
//	Dly = GetTimeAdd(DateTime,CurTime);		 						  // 计算两次时间差
	CN_st_Fun_AscNumber.MoveByte(DateTime,CurTime,sizeof(DateTime));  // 更新时间

	ReBuf = (uint8 *)AgreeBuf;
	pCurDat = (st_LctDat *)(&pGpsData->CN_st_Gps_Data_GPRMC.Latitude);	

	if(CN_st_Arealrm_Par_Oper[fd].CN_st_Arealrm_DataPar.CN_st_Sensor_DataPar.WorkPar == De_Sensor_WordPar_Arearect)				
		*ReBuf = JugeArearect(pCurDat,fd);		   	
	else if(CN_st_Arealrm_Par_Oper[fd].CN_st_Arealrm_DataPar.CN_st_Sensor_DataPar.WorkPar == De_Sensor_WordPar_AreaCirc) 	
		*ReBuf = JugeAreacirc(pCurDat,fd);	 
						 
   	OSSemPost(ArealrmSem);
	return De_Suc_Arealrm;
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

/**++++++++++++++++++++++++++++++++涉及到的算法+++++++++++++++++++++++++++++++++++++++**/

//利用经纬度差来计算距离 
//x，经度；y，维度 
static float CalcMil(uint32 x1,uint32 y1,uint32 x2,uint32 y2)
{ 
	float CurRadLong = 0;	//两点经纬度的弧度
	float CurRadLat = 0; 
	float PreRadLong = 0;
	float PreRadLat = 0;
	float a,b;              //经纬度弧度差
	float MilValue;	   

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

// 矩形区域判断
static uint8 JugeArearect(st_LctDat *pst_LctDat,uint8 fd)
{
	uint8 result;
	uint32 x1,y1;
	uint32 x2,y2;
	uint32 px,py;

	//CN_st_Fun_Uart.Write(0,"Rect area\r\n",CN_st_Fun_AscNumber.Strsize("Rect area\r\n"));

	x1 = CN_st_Arealrm_Par_Oper[fd].CN_st_Arealrm_DataPar.CN_un_Par.CN_st_Rectangle_Data.LeftLatitude;
	y1 = CN_st_Arealrm_Par_Oper[fd].CN_st_Arealrm_DataPar.CN_un_Par.CN_st_Rectangle_Data.LeftLongitude;
	x2 = CN_st_Arealrm_Par_Oper[fd].CN_st_Arealrm_DataPar.CN_un_Par.CN_st_Rectangle_Data.RightLatitude;
	y2 = CN_st_Arealrm_Par_Oper[fd].CN_st_Arealrm_DataPar.CN_un_Par.CN_st_Rectangle_Data.RightLongitude;
	px = pst_LctDat->Latitude;
	py = pst_LctDat->Longitude;

	if((px>x1)&&(px<x2)&&(py>y1)&&(py<y2))
		result = De_Sensor_Par_Onoff_In;
	else
		result =  De_Sensor_Par_Onoff_Out; 			
	return result;		
}

// 圆形区域判断
static uint8 JugeAreacirc(st_LctDat *pst_LctDat,uint8 fd)
{
	uint8 result;
	uint32 cx,cy;  
	uint32 r;
	uint32 dis;
	uint32 px,py;  
	
	//CN_st_Fun_Uart.Write(0,"Circ area\r\n",CN_st_Fun_AscNumber.Strsize("Circ area\r\n"));

	cx = CN_st_Arealrm_Par_Oper[fd].CN_st_Arealrm_DataPar.CN_un_Par.CN_st_RoundPar_Data.Latitude;
	cy = CN_st_Arealrm_Par_Oper[fd].CN_st_Arealrm_DataPar.CN_un_Par.CN_st_RoundPar_Data.Longitude;
	r =  CN_st_Arealrm_Par_Oper[fd].CN_st_Arealrm_DataPar.CN_un_Par.CN_st_RoundPar_Data.Radii;
	px = pst_LctDat->Latitude;
	py = pst_LctDat->Longitude;
	
	dis = (uint32)CalcMil(py,px,cy,cx);
	if(dis<r)
		result = De_Sensor_Par_Onoff_In;
	else
		result =  De_Sensor_Par_Onoff_Out; 		 		
	return result;		
}
