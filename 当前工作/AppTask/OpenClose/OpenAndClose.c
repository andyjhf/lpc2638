#define De_OpenAndClose_Compiler
#include "OpenAndClose.h"
static void Init(void)
{	
	CN_st_Fun_Timer.Open((st_Affair_Timer	*)&CN_Ba_st_Affair_Timer,&Timerfd);//关机指令
	CN_st_Fun_Timer.Open((st_Affair_Timer	*)&CN_Ba_st_Login,&LogTimerfd);
	CN_st_Fun_Timer.Open((st_Affair_Timer	*)&CN_Ba_st_Dev,&UnLoaderTimerfd);
	CN_st_Fun_Timer.DisEnable(LogTimerfd);
	CN_st_Fun_Timer.DisEnable(UnLoaderTimerfd);
	CN_st_Fun_Timer.Enable(Timerfd);
	if(CN_st_BoxData_LogOnServer.ReBox!=NULL)
		CN_st_BoxData_LogOnServer.ReBox=OSMboxCreate(NULL);

}
static void OpenGps(void)
{	st_Sensor_DataPar	CN_st_Sensor_DataPar;
	uint8 fd;
	CN_st_Fun_Timer.EditPro(Timerfd,1200);
	CloseTimer=De_AgreeOn_State_Erro;
	if(CN_st_Fun_Sensor.GetPar2ID(De_Sensor_WordPar_Gps,&fd)!=De_Suc_Sensor)
	{	CN_st_Sensor_DataPar.WorkPar=De_Sensor_WordPar_Gps;
		CN_st_Fun_Sensor.Open(&CN_st_Sensor_DataPar,&fd);
	}
}
static void CloseGps(void)
{	uint8 i;
	for(i=0;i<sizeof(CloseGpsTerm)/sizeof(uint8 *);i++)
	{	if(*CloseGpsTerm[i]!=De_AgreeOn_State_Suc)
			return ;
	}
	if(CN_st_Fun_Sensor.GetPar2ID(De_Sensor_WordPar_Gps,&i)!=De_Suc_Sensor)
		return ;
	CN_st_Fun_Sensor.Close(i);
}
static void OpenGprs(void)							//接受
{	uint8 err;
	CN_st_Fun_Timer.EditPro(Timerfd,1200);
	if(LogFlag==De_No_Log) 			//登录并标志
	{	ClearSem();
		CN_st_BoxData_LogOnServer.Command=De_LogOnServer_Order_Link_Open;
		CN_st_BoxData_LogOnServer.ptLinkCloseFun=OpenGprsNo;
		CN_st_BoxData_LogOnServer.ptSuc=LogSucOper;
		CN_st_BoxData_LogOnServer.AgreeOnNewDataFun=CN_st_Fun_AppGprs.Read;
		LogFlag=De_LogInt;
		OSMboxPost(LogOnServerBox,&CN_st_BoxData_LogOnServer);		
	}
	else if(LogFlag==De_LogInt)
	{	OSMboxPend(LogOnServerBox,2,&err);
		if(err==OS_NO_ERR)
			LogFlag=De_LogSuc;
	}	
}
static void OpenGprsNo(uint8 fd)  					//当发送不成功时
{	if((LogFlag==De_LogSuc)||(LogFlag==De_No_Log))
	{	LogFlag=De_No_Log;
		OpenGprs();
	}	
}
static void CloseGprs(void)
{	uint8 i;
	for(i=0;i<sizeof(CloseGprsTerm)/sizeof(uint8 *);i++)
	{	if(*CloseGprsTerm[i]!=De_AgreeOn_State_Suc)
			return ;
	}
	if(LogFlag==De_No_Log)
		return ;
	CN_st_BoxData_LogOnServer.Command=De_LogOnServer_Order_Link_Close;
	ClearSem();
	OSMboxPost(LogOnServerBox,&CN_st_BoxData_LogOnServer);
	LogFlag=De_No_Log;
}
static void ClearTimer(st_Data_Timer	*ptst_Data_Timer,uint8 fd)
{	ptst_Data_Timer=ptst_Data_Timer;
	CloseTimer=De_AgreeOn_State_Suc;
}
static void ClearSem(void)
{	OS_SEM_DATA 	SemData;
	uint8 err;
	for(;;)
	{	if(OSSemQuery(CN_st_BoxData_LogOnServer.ReBox,&SemData)!=OS_NO_ERR)
			break;
		if(SemData.OSCnt == 0)		//有信号要接受
			break;	
		OSMboxPend(LogOnServerBox,2,&err);
	}
}

static void LogSucOper(void)
{	uint8 fd;
	if(CN_st_Fun_Tzv21.GetPar2ID(De_Sensor_WordPar_GprsTzxy_1,&fd)!=De_Suc_AgreeOn)
		return ;
	CN_st_Fun_AppSendAgreeOn.WriteCommand(fd,De_Dev_Order_Login,NULL);
	//	return ;
	//if(CN_st_Fun_AppSendAgreeOn.) 				//暂时先封闭盲区补偿
	
}
#define De_OpenUart_Use_Port						0
const  st_Sensor_DataPar	CN_Ba_OpenUart_CN_st_Sensor_DataPar=
{	De_OpenUart_Use_Port,De_Sensor_WordPar_UartTzxy_1,0xffffff	
};

static void OpenUart(void)					//打开串口协议
{	uint8 fd;
	st_Appair_Tzv2	CN_st_Appair_Tzv2;
	st_AgreeOn_OpenPar	CN_st_AgreeOn_OpenPar=
	{	{0x01,0x45,0x4C,0xC5,0xF2,0x12,0xF6},0,De_Sensor_WordPar_UartTzxy_1,60,2,8
	};
	CN_st_Fun_Sensor.Open((st_Sensor_DataPar	*)&CN_Ba_OpenUart_CN_st_Sensor_DataPar,
	&fd);
	CN_st_Appair_Tzv2.ptFunction=CN_st_Fun_AppGprs.Read;
	CN_st_AgreeOn_OpenPar.fd=fd;
	CN_st_Fun_Tzv21.Open(&CN_st_AgreeOn_OpenPar,&CN_st_Appair_Tzv2,&fd);
}

static void ChargeLogin(st_Data_Timer	*ptst_Data_Timer,uint8 fd)
{	OpenGprsNo(1);
	CN_st_Fun_Timer.DisEnable(fd);	
}
static void ChargeLoadDev(st_Data_Timer	*ptst_Data_Timer,uint8 fd)		//重新加载传感器
{	CN_st_Fun_OpenSensor.Init();
	CN_st_Fun_Timer.DisEnable(fd);
}
