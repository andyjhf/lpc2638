#include "..\APP\config.h"
#include "stdlib.h"
#include "..\File\rwFile.h"
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
static void Init(void *pdata);
#define TaskStkLengh		256
OS_STK		TaskStk[TaskStkLengh];
int main (void)
{	OSInit ();	
	TargetInit();																							
	OSTaskCreate (Init,(void *)0, &TaskStk[TaskStkLengh - 1],14);		
	OSStart();
	return 0;															
}




static void Init(void *pdata)
{	st_Gsm_Net_Information	CN_st_Gsm_Net_Information;
	st_File_Basic	CN_st_File_Basic;
	
	CN_st_Fun_RTC.Init();
	CN_st_Fun_Timer.Init();	
	CN_st_Fun_File.Init();
	FileData_CheckFile();								//检查文件系统
	//CN_st_Fun_Gprs.Init();								//GPRS控件开启
	//CN_st_Fun_Gprs.InitSys();
	//CN_st_Fun_Gprs.InitMessage();
	//CN_st_Fun_Gprs.InitPhone();
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
	CN_st_Fun_File.ReadRecoder(CN_st_File_fd.Basicfd,0,&CN_st_File_Basic);
	if(CN_st_Fun_AscNumber.CompareBuf(CN_st_Gsm_Net_Information.IMEI,CN_st_File_Basic.IMEI,sizeof(CN_st_File_Basic.IMEI))!=0)
	{	CN_st_Fun_AscNumber.MoveByte(CN_st_File_Basic.IMEI,CN_st_Gsm_Net_Information.IMEI,sizeof(CN_st_File_Basic.IMEI));
		CN_st_Fun_File.WriteRecoder(CN_st_File_fd.Basicfd,0,&CN_st_File_Basic);
	}
	CN_st_Fun_OpenAndClose.OpenGprs();			//登录系统
   	
	for(;;OSTimeDly(60000))
	{	
	
	
	
	}			 	
}											//硬件端口	
