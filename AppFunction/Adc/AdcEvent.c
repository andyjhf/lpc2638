#define De_AdcEvent_Compiler
#include "AdcEvent.h"
void AdcInit(void)											
{	st_File_Parameter		CN_st_File_Parameter;
	union
	{	st_Affair_Timer			CN_st_Affair_Timer;
		st_Affair_CheckVoltage	CN_st_Affair_CheckVoltage;
	}a;
	uint8 Fd;
	AdcLowCheckTime = 0;
	AdcHighCheckTime = 0;
	CN_st_Fun_File.ReadRecoder(CN_st_File_fd.Parameterfd,0,&CN_st_File_Parameter);

//	a.CN_st_Affair_Timer.CN_st_Property_Timer.TimerData=CN_st_File_Parameter.LowVolTimer;
//	a.CN_st_Affair_Timer.CN_st_Property_Timer.TimerNonce=0;
//	a.CN_st_Affair_Timer.CN_st_Function_Timer.ptFun=LowVolWaring;
//	if(CN_st_Sys_Event.VoDownfd!=De_Event_No)				
//	{	CN_st_Fun_Timer.Close(CN_st_Sys_Event.VoDownfd);	
//		CN_st_Sys_Event.VoDownfd=De_Event_No;	
//	}
//	CN_st_Fun_Timer.Open(&a.CN_st_Affair_Timer,&CN_st_Sys_Event.VoDownfd);
//	CN_st_Fun_Timer.DisEnable(CN_st_Sys_Event.VoDownfd); 			//低电压报警
//
//	a.CN_st_Affair_Timer.CN_st_Property_Timer.TimerData=CN_st_File_Parameter.HighVolTimer;
//	a.CN_st_Affair_Timer.CN_st_Property_Timer.TimerNonce=0;
//	a.CN_st_Affair_Timer.CN_st_Function_Timer.ptFun=HighVolBack;
//   	if(CN_st_Sys_Event.VoUpfd!=De_Event_No)				
//	{	CN_st_Fun_Timer.Close(CN_st_Sys_Event.VoUpfd);	
//		CN_st_Sys_Event.VoUpfd=De_Event_No;	
//	}
//   	CN_st_Fun_Timer.Open(&a.CN_st_Affair_Timer,&CN_st_Sys_Event.VoUpfd);
//	CN_st_Fun_Timer.DisEnable(CN_st_Sys_Event.VoUpfd); 				//高电压恢复

	a.CN_st_Affair_CheckVoltage.CN_st_Property_CheckVoltage.LowVoltage=CN_st_File_Parameter.HighL;
    a.CN_st_Affair_CheckVoltage.CN_st_Property_CheckVoltage.HighVoltage=CN_st_File_Parameter.HighV;
	a.CN_st_Affair_CheckVoltage.CN_st_Function_CheckVoltage.ptFunLowVoltage=LowAdc;
	a.CN_st_Affair_CheckVoltage.CN_st_Function_CheckVoltage.ptFunHighVoltage=HighAdc;
	CN_st_Fun_CheckVoltage.Open((st_Affair_CheckVoltage	*)&a.CN_st_Affair_CheckVoltage,&Fd);
	CN_st_Fun_CheckVoltage.Enable(Fd);						//开启adc功能

					
}
/*+++++++++++++++++++++++++++++++++++++执行函数+++++++++++++++++++++++++++++++++++++++++++++++++++*/
static void HighAdc(st_Data_CheckVoltage	*ptst_Data_CheckVoltage,uint8 fd)		//高电压恢复正常
{	st_File_Parameter		CN_st_File_Parameter;
	//CN_st_Fun_Timer.DisEnable(CN_st_Sys_Event.VoDownfd);
	
	if(CN_st_Sys_State.voltage!=De_Suc_State)		//恢复报警
	{	AdcLowCheckTime = 0;
		CN_st_Fun_File.ReadRecoder(CN_st_File_fd.Parameterfd,0,&CN_st_File_Parameter);
		if(CN_st_File_Parameter.VoAlarmState == De_VoAlarm_Yes)			//恢复报警
	 	{	AdcHighCheckTime++;
			if(AdcHighCheckTime>20)
			{	AdcHighCheckTime = 0;
				CN_st_Sys_State.voltage=De_Suc_State;
				//CN_st_Fun_Timer.Enable(CN_st_Sys_Event.VoUpfd);
				
				CN_st_File_Parameter.VoAlarmState = De_VoAlarm_No;
				CN_st_Fun_File.WriteRecoder(CN_st_File_fd.Parameterfd,0,&CN_st_File_Parameter);
				WatchDog();
				HighVolBack();
			}
		}
		else
			CN_st_Sys_State.voltage=De_Suc_State;
	}
}

static void LowAdc(st_Data_CheckVoltage	*ptst_Data_CheckVoltage,uint8 fd)
{	st_File_Parameter		CN_st_File_Parameter;
//	CN_st_Fun_Timer.DisEnable(CN_st_Sys_Event.VoUpfd);
	if(CN_st_Sys_State.voltage!=De_State_Voltage_Bad)
	{	AdcLowCheckTime++;
		AdcHighCheckTime = 0;
		if(AdcLowCheckTime>20)
		{	AdcLowCheckTime = 0;
			CN_st_Sys_State.voltage=De_State_Voltage_Bad;
//			CN_st_Fun_Timer.Enable(CN_st_Sys_Event.VoDownfd);
		 	CN_st_Fun_File.ReadRecoder(CN_st_File_fd.Parameterfd,0,&CN_st_File_Parameter);
			CN_st_File_Parameter.VoAlarmState = De_VoAlarm_Yes;
			CN_st_Fun_File.WriteRecoder(CN_st_File_fd.Parameterfd,0,&CN_st_File_Parameter);
			WatchDog();
			LowVolWaring();
		}
	}	
}

static void LowVolWaring(void)		//低电压报警
{	uint8 Phone[15];
	uint8 Buf[200],CenterNum = 1;
	st_File_Parameter		CN_st_File_Parameter;
	st_Data_CheckVoltage	CN_st_Data_CheckVoltage;

	CN_st_Fun_File.ReadRecoder(CN_st_File_fd.Parameterfd,0,&CN_st_File_Parameter);
	CN_st_Fun_CheckVoltage.Read(&CN_st_Data_CheckVoltage);
	if(CN_st_Data_CheckVoltage.Voltage>CN_st_File_Parameter.HighL)
		return;
	CN_st_Fun_AscNumber.ClsArray(Buf,sizeof(Buf));
	Buf[0]='*';Buf[1]='D';
	Get_Gps_Data(Buf+2);
	Buf[CN_st_Fun_AscNumber.Strsize(Buf)]='#';
	CN_st_Fun_AscNumber.ClsArray(Phone,sizeof(Phone));
	GetPhone(Phone,&CenterNum);
	SendMessage(Buf,Phone);	
//	CN_st_Fun_Timer.DisEnable(fd);
}

static void HighVolBack(void)		//电压恢复正常
{	uint8 Phone[15];
	uint8 Buf[200],CenterNum = 1;
	st_File_Parameter		CN_st_File_Parameter;
	st_Data_CheckVoltage	CN_st_Data_CheckVoltage;

	CN_st_Fun_File.ReadRecoder(CN_st_File_fd.Parameterfd,0,&CN_st_File_Parameter);
	CN_st_Fun_CheckVoltage.Read(&CN_st_Data_CheckVoltage);
	if(CN_st_Data_CheckVoltage.Voltage<CN_st_File_Parameter.HighV)
		return;
	//if(State==De_State_Voltage_Bad)
	CN_st_Fun_AscNumber.ClsArray(Buf,sizeof(Buf));
	Buf[0]='*';Buf[1]='Y';Buf[2]='J';Buf[3]='&';
	Get_Gps_Data(Buf+4);
	Buf[CN_st_Fun_AscNumber.Strsize(Buf)]='#';
	GetPhone(Phone,&CenterNum);
	SendMessage(Buf,Phone);

	
//	CN_st_Fun_Timer.DisEnable(fd);
}



