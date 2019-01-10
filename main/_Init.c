#include "..\APP\config.h"
#include "stdlib.h"
#include "..\File\rwFile.h"
#include "..\File\DownFile.h"
#include "..\FilleData\FileData.h"
#include "..\OpenSensor\OpenSensor.h"
#include "..\Control\Sensor\SensorContr.h"
#include "..\Control\Gprs\GPRS.h"
#include "..\Control\Timer\Timer.h"
#include "..\Dev\Sensor\Sensor.h"
#include "..\HardWare\RTC\RTC.h"
//#include "..\Control\Photo\Photo.h"
#include "..\Control\GpsAndMileage\GpsAndMileage.h"
#include "..\AgreeOn\TzV2.1.h"
#include "..\AppTask\LogOnServer\LogOnServer.h"
#include "..\Control\FTP\ftp.h"
#include "..\AppTask\UpdateSoftWare\UpdateSoftWare.h"
#include "..\AppOper\Space.h"
#include "..\AppOper\MessageAndPhone.h"
#include "..\AppSendAgreeOn\AppSendAgreeOn.H"
#include "..\AppOper\WarningUpate.h"
#include "..\AppTask\OpenClose\OpenAndClose.H"
#include "..\miscellaneous\CodeTrans\AscNumber.h"
//#include "..\Control\FTP\ftp.h"
//#include "..\AppTask\UpdateSoftWare\UpdateSoftWare.h"
static void Init(void *pdata);
#define TaskStkLengh		256
OS_STK		TaskStk[TaskStkLengh];
static void MODEM_Dly100ms(int num);
static void CheckLed(uint8 State);
void Build_INT_Vector_Table()
{	
	volatile uint32* pRAM;
	volatile uint32* pFlash;
	uint32 i = 0;	
	uint32 j = 0;  
	pRAM   = (uint32* )0x40000000;
	pFlash = (uint32* )0x10000;
	VICIntEnClr = 0xFFFFFFFF; //关中断 
	//Move interrupt vector from Flash to SRAM.
	for (i=0; i<16; i++)
	{	*pRAM = *pFlash;	  
		for(j=0;j<10000;j++);
	   	pRAM++;
	   	pFlash++;
	}	
	MEMMAP = 0x02;//map vector from SRAM.	
}					 

int main (void)
{//	Build_INT_Vector_Table();
	OSInit ();	
	TargetInit();																							
	OSTaskCreate (Init,(void *)0, &TaskStk[TaskStkLengh - 1],2);		
	OSStart();
	return 0;															
}




static void Init(void *pdata)
{	st_Gsm_Net_Information	CN_st_Gsm_Net_Information;
	st_File_Basic	CN_st_File_Basic;
	uint8 i;
	
	CN_st_Fun_RTC.Init();	
	CN_st_Fun_File.Init();
	for(i=0;i<De_Flash_Chip_Number;i++)
	{	if(CN_st_NorFlash.CN_st_Flash_Chip_Features[i]!=NULL)
			break;
	}
	if(i==De_Flash_Chip_Number)
		CheckLed(0);			  //故障
	else
		CheckLed(1);			  //正常
 	CN_st_Fun_DownFile.Init();
    FileData_CheckFile();								//检查文件系统
	//CN_st_Fun_Gprs.Init();								//GPRS控件开启
	//CN_st_Fun_Gprs.InitSys();
	//CN_st_Fun_Gprs.InitMessage();
	//CN_st_Fun_Gprs.InitPhone();
	CN_st_Fun_Timer.Init();	
	CN_st_Fun_MessageAndPhone.Init();
	CN_st_Fun_Sensor.Init();
	CN_st_Fun_SensorContr.Init();						//传感器控件开启	
	CN_st_Fun_OpenSensor.Init();					   	//打开传感器
	CN_st_Fun_RunLen.Init();							//里程统计任务开启
	CN_Ba_st_Fun_Space.Init();							//开启

	CN_st_Fun_Photo.Init();
	CN_st_Fun_Photo.Open();
	CN_st_Fun_Tzv21.Init();
	CN_st_Fun_LogOnServer.Init();
	CN_st_Fun_AppSendAgreeOn.Init();
	CN_st_Fun_WarningUpate.Init();
	CN_st_Fun_OpenAndClose.Init();
	
	CN_st_Fun_Gprs.GetSysState(&CN_st_Gsm_Net_Information);
//	CN_st_Fun_File.ReadRecoder(CN_st_File_fd.Basicfd,0,&CN_st_File_Basic);
//	if(CN_st_Fun_AscNumber.CompareBuf(CN_st_Gsm_Net_Information.IMEI,CN_st_File_Basic.IMEI,sizeof(CN_st_File_Basic.IMEI))!=0)
//	{	CN_st_Fun_AscNumber.MoveByte(CN_st_File_Basic.IMEI,CN_st_Gsm_Net_Information.IMEI,sizeof(CN_st_File_Basic.IMEI));
//		CN_st_Fun_File.WriteRecoder(CN_st_File_fd.Basicfd,0,&CN_st_File_Basic);
//	}
	CN_st_Fun_OpenAndClose.OpenGprs();			//登录系统
	CN_st_Fun_FTP.Init();
   	CN_st_Fun_UpdateSoftWare.Init();
	for(;;OSTimeDly(60000))
	{	
	
	
	
	}			 	
}											//硬件端口
#define GPSLED 26    	//  P0.26  LED     LED 指示灯
#define LED_ON        IODIR0  |= (1<<GPSLED);IOCLR0 |= (1<<GPSLED)
#define LED_OFF       IODIR0  |= (1<<GPSLED);IOSET0 |= (1<<GPSLED)	
static void CheckLed(uint8 State)
{	if(State==1)
	{	LED_OFF;
		MODEM_Dly100ms(10);
		LED_ON;
		MODEM_Dly100ms(10);
		LED_OFF;
	}
	else
	{	LED_OFF;
		MODEM_Dly100ms(10);
		LED_ON;
		MODEM_Dly100ms(10);
		LED_OFF;
		MODEM_Dly100ms(10);
		LED_ON;
		MODEM_Dly100ms(10);
		LED_OFF;
		MODEM_Dly100ms(10);
		LED_ON;
		MODEM_Dly100ms(10);
		LED_OFF;
	}
}
static void MODEM_Dly100ms(int num)
{	uint32  i,m;
    INT32U j;
	m = num*10;
   	for(i=0;i<m;i++)
    {	for(j=0;j<660;j++)
		{	IOCLR1 |= (1<<18);				  //延时中加喂狗
			IOSET1 |= (1<<18);
			IOSET1 |= (1<<18);
			IOCLR1 |= (1<<18);	
		}
    }
}


	
