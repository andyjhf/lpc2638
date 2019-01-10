//#include "..\..\AppFunction\Event\AppEvent.h"

#include "..\..\File\rwFile.h"
#include "..\..\HardWare\RTC\RTC.h"
#include "..\..\HardWare\UART\UART.h"
#include "..\..\miscellaneous\CodeTrans\AscNumber.h"
#include "..\..\miscellaneous\Date\Date.h"
#include "..\..\Dev\Sensor\_PuSensor.h"
//#include "..\..\Dev\Sensor\Sensor.h"
#include "..\..\Dev\Sensor\Sensor.h"

static void Init(void *pdata);
static void InitContrl(void);
static uint8 GetState(void);
	#define	De_Max_Dly_Time					5
 	#define De_Acc_High						1
	#define De_Acc_Low						0
	#define De_IO_Acc_Function					PINSEL4 &=0xfffffff3
	#define De_IO_Acc_Open						De_IO_Acc_Function;FIO2DIR	&= ~(1<<ACCIN)//打开ACC输入
	#define De_IO_Acc_In						(FIO2PIN &(1<<ACCIN))
#define TaskStkLengh			512	
OS_STK	TaskStk[TaskStkLengh];
const st_Da_Uart	CN_st_Da_Uart={9600,8,1,0};
const st_Sensor_DataPar	 CN_st_Sensor_DataPar1={0x22222222,0x0111,0x0002};
	const st_Sensor_DataPar	 CN_st_Sensor_DataPar2={0x33333333,0x0011,0x0001};
	const st_Sensor_DataPar	 CN_st_Sensor_DataPar3={0x44444444,0x0012,0x0001};
	const st_Sensor_DataPar  CN_st_Sensor_DataPar4={0x11111111,0x0112,0x0002};
    const st_Sensor_DataPar  CN_st_Sensor_DataPar5={0x55555555,De_Sensor_WordPar_Oil1,De_Max_Dly_Time} ;
	const st_Sensor_DataPar  CN_st_Sensor_DataPar6={0x66666666,De_Sensor_WordPar_AccTimer,De_Max_Dly_Time} ;   

int main (void)
{	OSInit ();	
	TargetInit();
																								
	OSTaskCreate (Init,(void *)0, &TaskStk[TaskStkLengh - 1],10);		
	OSStart();
	return 0;															
}

static void Init(void *pdata)
{  	st_Sensor_Data_Acc	CN_st_Sensor_Data_Acc;
	uint32 TempVa,OilVa;
	uint16 RecLen1,RecLen;
	uint8 Asc[30],i,fd1[6],Swith;
	uint16 Result;
	uint8 Buf[100]={0x20,0x09,0x01,0x01,0x00,0x00,0x00};
	pdata=pdata;
	CN_st_Fun_Uart.Init(0);
	CN_st_Fun_Uart.Open(0,(st_Da_Uart	*)&CN_st_Da_Uart);
	CN_st_Fun_Uart.Write(0,"Start\r\n",7);
    CN_st_Fun_Sensor.Init();          
    CN_st_Fun_Sensor.Open((st_Sensor_DataPar*)&CN_st_Sensor_DataPar1,&fd1[0]);		  
	CN_st_Fun_Sensor.Open((st_Sensor_DataPar*)&CN_st_Sensor_DataPar2,&fd1[2]);		
	CN_st_Fun_Sensor.Open((st_Sensor_DataPar*)&CN_st_Sensor_DataPar3,&fd1[3]);			
    CN_st_Fun_Sensor.Open((st_Sensor_DataPar*)&CN_st_Sensor_DataPar4,&fd1[1]);	 
	CN_st_Fun_Sensor.Open((st_Sensor_DataPar*)&CN_st_Sensor_DataPar5,&fd1[4]);			
    CN_st_Fun_Sensor.Open((st_Sensor_DataPar*)&CN_st_Sensor_DataPar6,&fd1[5]);	 
	for(;;OSTimeDly(400))
	{ 	for(i=0;i<4;i++)  
		{	if(i<2)
			{	if(CN_st_Fun_Sensor.Read(fd1[i],Buf,&TempVa)!=De_Suc_Sensor)	
	   			{	continue;
				}
				CN_st_Fun_Uart.Write(0,"canshu:",7);
				CN_st_Fun_AscNumber.ClsArray(Asc,sizeof(Asc));
				CN_st_Fun_AscNumber.Algorism2Asc(TempVa,Asc);
				CN_st_Fun_Uart.Write(0,Asc,CN_st_Fun_AscNumber.Strsize(Asc));
				CN_st_Fun_Uart.Write(0,"\r\n",2);	
			}
			else
			{ 	if(CN_st_Fun_Sensor.Read(fd1[i],Buf,&Swith)!=De_Suc_Sensor)	
	   			{	continue;
				}
			  	CN_st_Fun_Uart.Write(0,"OnOrOff:",8);
				CN_st_Fun_AscNumber.ClsArray(Asc,sizeof(Asc));
				CN_st_Fun_AscNumber.Algorism2Asc((uint32 )Swith,Asc);
				CN_st_Fun_Uart.Write(0,Asc,CN_st_Fun_AscNumber.Strsize(Asc));
				CN_st_Fun_Uart.Write(0,"\r\n",2);	
			} 	
	 	}
			  	if(CN_st_Fun_Sensor.Read(4,Buf,&OilVa)!=De_Suc_Sensor)	
	   			{	continue;
				}
			  	CN_st_Fun_Uart.Write(0,"oilva:",6);
				CN_st_Fun_AscNumber.ClsArray(Asc,sizeof(Asc));
				CN_st_Fun_AscNumber.Algorism2Asc((uint32 )OilVa,Asc);
				CN_st_Fun_Uart.Write(0,Asc,CN_st_Fun_AscNumber.Strsize(Asc));
				CN_st_Fun_Uart.Write(0,"\r\n",2);	
			  if(CN_st_Fun_Sensor.Read(5,Buf,&CN_st_Sensor_Data_Acc)!=De_Suc_Sensor)	
	   			{	continue;
				}
				CN_st_Fun_Uart.Write(0,"ACCState:",9);

				CN_st_Fun_AscNumber.ClsArray(Asc,sizeof(Asc));
				CN_st_Fun_AscNumber.Algorism2Asc((uint32 )CN_st_Sensor_Data_Acc.NonState,Asc);
				CN_st_Fun_Uart.Write(0,Asc,CN_st_Fun_AscNumber.Strsize(Asc));
				CN_st_Fun_Uart.Write(0,"\r\n",2);
				CN_st_Fun_Uart.Write(0,"ACCshijian:",11);
				CN_st_Fun_AscNumber.ClsArray(Asc,sizeof(Asc));
			   CN_st_Fun_AscNumber.Algorism2Asc((uint32 )CN_st_Sensor_Data_Acc.AccTimer,Asc);
				CN_st_Fun_Uart.Write(0,Asc,CN_st_Fun_AscNumber.Strsize(Asc));
				CN_st_Fun_Uart.Write(0,"\r\n",2); 
		CN_st_Fun_Date.Next(Buf,De_Type_Date_Second);
    }
}											//硬件端口	
	


static void InitContrl(void) 								//初始化控件
{	uint8 fd;


}
