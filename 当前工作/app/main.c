/****************************************Copyright (c)**************************************************
**                               Guangzou ZLG-MCU Development Co.,LTD.
**                                      graduate school
**                                 http://www.zlgmcu.com
**
**--------------File Info-------------------------------------------------------------------------------
** File name:			main.c
** Last modified Date:  2004-09-16
** Last Version:		1.0
** Descriptions:		The main() function example template
**
**------------------------------------------------------------------------------------------------------
** Created by:			Chenmingji
** Created date:		2004-09-16
** Version:				1.0
** Descriptions:		The original version
**
**------------------------------------------------------------------------------------------------------
** Modified by:
** Modified date:
** Version:
** Descriptions:
**
** mcu123.com add keil
********************************************************************************************************/
#include "config.h"
#include "stdlib.h"
#include "uart.h"
#include "usr_def.h"

#define	TaskStkLengh	1024			//Define the Task0 stack length 定义用户任务0的堆栈长度
 
OS_STK	TaskStk [TaskStkLengh];		//Define the Task0 stack 定义用户任务0的堆栈
OS_STK	TaskStk1 [TaskStkLengh];		//Define the Task1 stack 定义用户任务1的堆栈

void 	Task0(void *pdata);			//Task0 任务0
void 	Task1(void *pdata);			//Task1 任务1

void *GPSRxMsg[120];
RevGpsData GpsData;
OS_EVENT *GPSRxQ;
GPS *GPS_Cur;					 //当前处理GPS数据包
GPSRMC *RMC_Temp;				//RMC临时指针
GPSGGA *GGA_Temp;				//GGA临时指针
char *GPS_Temp;

uint16 GetGpsDat(RevGpsData *pDat)
{
	if(GpsData.GpsState & 0x01)
	{
		pDat = (void *)0;
		return De_Erro_GPS;
	}
	else
	{
		pDat = &GpsData;
		return 0;
	}
}
int main (void)
{
	TargetInit ();
	UARTInit(1, 4800);
	
	OSInit ();
	GPSRxQ=OSQCreate(&GPSRxMsg[0],120);																										
	OSTaskCreate (Task0,(void *)0, &TaskStk[TaskStkLengh - 1], 2);	
	OSTaskCreate (Task1,(void *)0, &TaskStk1[TaskStkLengh - 1], 3);		
	OSStart ();
	return 0;															
}
/*********************************************************************************************************
**                            Task0 任务0
********************************************************************************************************/

void Task0	(void *pdata)
{

	INT8U err,i;
	INT8U Time_Temp;
	INT8U vf_temp[7];
	float num;
	INT8U nn;
	pdata = pdata;
	while(1)
	{
		GPS_Temp = OSQPend(GPSRxQ,0,&err);
		GPS_Cur = (GPS *)GPS_Temp;
		if(GPS_Cur->Type == 1)								  //处理RMC包
		{
			RMC_Temp = (GPSRMC *)GPS_Cur->GPS_Buf;
			if(RMC_Temp->Availability == 'A')				  //定位有效
			{
//				GpsData.CurStat = 1;
				for(i=0;i<6;i++)							  //获取相关数据 //时间
				{
					GpsData.Time[i] = RMC_Temp->Time[i];
				}
				Time_Temp = (GpsData.Time[0]-0x30)*10+GpsData.Time[1]-0x30+8;
				if(Time_Temp>24)
					Time_Temp = Time_Temp - 24;
				GpsData.Time[0] = Time_Temp/10+0x30;
				GpsData.Time[1] = Time_Temp%10+0x30;
				for(i=0;i<3;i++)							   //速度
				{
					vf_temp[i] = RMC_Temp->v[i];
				}
				vf_temp[3] = '\0';
				num = atof(vf_temp);
        		nn = (INT8U)(num/2);
				nn = (INT8U)(nn * 1.852);
				GpsData.vv[0] = nn/10+0x30;					  //还原为可见字符
				GpsData.vv[1] = nn%10+0x30;

				for(i=0;i<5;i++)							  //方向
				{
					vf_temp[i] = RMC_Temp->f[i];
				}
				vf_temp[5] = '\0';
				num = atof(vf_temp);
        		nn = (INT8U)(num/10);
				GpsData.ff[0] = nn/10+0x30;					 //还原为可见字符
				GpsData.ff[1] = nn%10+0x30;

				for(i=0;i<4;i++)							 //	纬度
				{
					GpsData.Lat[i] = RMC_Temp->Lat[i];
				}
				for(i=4;i<8;i++)
				{
					GpsData.Lat[i] = RMC_Temp->Lat[i+1];
				}
				for(i=0;i<5;i++)							 //经度
				{
					GpsData.Long[i] = RMC_Temp->Long[i];
				}
				for(i=5;i<9;i++)
				{
					GpsData.Long[i] = RMC_Temp->Long[i+1];
				}
				for(i=0;i<6;i++)
				{
					GpsData.Date[i] = RMC_Temp->Date[i];		//日期
				}
				GpsData.GpsState &= 0x7e;						 //定位状态
				if(RMC_Temp->NS == 'N')							 //所在半球信息
				{
					GpsData.GpsState |= 0x02;
				}
				else if(RMC_Temp->NS == 'S')
				{
					GpsData.GpsState &= 0x7c;
				}
				if(RMC_Temp->EW == 'E')
				{
					GpsData.GpsState |= 0x04;
				}
				else if(RMC_Temp->EW == 'W')
				{
					GpsData.GpsState &= 0x7b;
				}
//				OSTimeDly(10);
			}	
			else												//定位无效
			{
				GpsData.GpsState |= 0x01;
//				OSTimeDly(10);	
			}
		}	
		else if(GPS_Cur->Type == 2)													//处理GGA包
		{
			GGA_Temp = (GPSGGA *)GPS_Cur->GPS_Buf;
			GpsData.StarNum = GGA_Temp->StarNum;				 //获取同步卫星数量
//			OSTimeDly(10);										 
		} 
		OSTimeDly(100);	
		
	}
	
//	while (1)
//	{
//		FIO2CLR|=0x000000FF;
//		OSTimeDly(100);
//	}
}
/*********************************************************************************************************
**                            Task1 任务1
********************************************************************************************************/

void Task1	(void *pdata)
{
	pdata = pdata;

	while (1)
	{
		FIO2SET|=0x000000FF;
		OSTimeDly(500);
	}
}   
/*********************************************************************************************************
**                            End Of File
********************************************************************************************************/
