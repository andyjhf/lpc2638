#define De_AccEvent_Compiler
#include "AccEvent.h"
void AccInit(void)						//初始化ACC
{	union
	{	st_File_Parameter	CN_st_File_Parameter;
		st_Affair_Timer		CN_st_Affair_Timer;
	}a;
	const st_Affair_Acc	CN_st_Affair_Acc={AccLow,AccHigh};	
	CN_st_Fun_File.ReadRecoder(CN_st_File_fd.Parameterfd,0,&a.CN_st_File_Parameter);

	a.CN_st_Affair_Timer.CN_st_Property_Timer.TimerData=a.CN_st_File_Parameter.SleepTimer;
	a.CN_st_Affair_Timer.CN_st_Property_Timer.TimerNonce=0;
	a.CN_st_Affair_Timer.CN_st_Function_Timer.ptFun=Sleep;
	if(CN_st_Sys_Event.AccSleepfd!=De_Event_No)
	{	CN_st_Fun_Timer.Close(CN_st_Sys_Event.AccSleepfd);
		CN_st_Sys_Event.AccSleepfd=De_Event_No;
	}
	CN_st_Fun_Timer.Open(&a.CN_st_Affair_Timer,&CN_st_Sys_Event.AccSleepfd); 		//ACC关闭休眠事件
	CN_st_Fun_Timer.DisEnable(CN_st_Sys_Event.AccSleepfd);				

	if(CN_st_Sys_Event.Accfd!=De_Event_No)
	{	CN_st_Fun_Acc.Close(CN_st_Sys_Event.Accfd);
		CN_st_Sys_Event.Accfd=De_Event_No;
	}
	CN_st_Fun_Acc.Open((st_Affair_Acc	*)&CN_st_Affair_Acc,&CN_st_Sys_Event.Accfd);
	//CN_st_Fun_Timer.Enable(CN_st_Sys_Event.Accfd);	
}
static void AccHigh(st_Data_Acc   *ptst_Data_Acc,uint8 fd)
{	uint8 State;
	CN_st_Fun_Timer.DisEnable(CN_st_Sys_Event.AccSleepfd);
	State=De_Suc_State;
	OSMboxPost (SleepBox,&State); 						//唤醒机器
	CN_st_Sys_State.Sleep=De_Suc_State;
	CN_st_Sys_State.AccState=De_Suc_State;
	CN_st_Fun_Uart.Write(0,"Up\r\n",4);
}
static void AccLow(st_Data_Acc   *ptst_Data_Acc,uint8 fd)	//Acc无效
{	st_File_Parameter	CN_st_File_Parameter;
	uint32 AccTime;
	CN_st_Fun_File.ReadRecoder(CN_st_File_fd.Parameterfd,0,&CN_st_File_Parameter);
	if(CN_st_File_Parameter.AccFun==0)						//ACC功能是否开
	{	CN_st_Fun_File.ReadRecoder(CN_st_File_fd.AccTimerfd,0,&AccTime);
		AccTime+=ptst_Data_Acc->BackStateTime;
		CN_st_Fun_File.WriteRecoder(CN_st_File_fd.AccTimerfd,0,&AccTime);
	}
	CN_st_Sys_State.AccState=De_Acc_State_Close;
	CN_st_Fun_Timer.Enable(CN_st_Sys_Event.AccSleepfd);	
	CN_st_Fun_Uart.Write(0,"Down\r\n",6);		
}
static void Sleep(st_Data_Timer	*ptst_Data_Timer,uint8 fd)
{	uint8 State,State2;
	CN_st_Fun_Timer.GetEnable(CN_st_Sys_Event.Timerfd,&State2);
	if(State2 == De_Timer_Affair_DisEnable)
	{	State=De_State_Sleep;
		OSMboxPost (SleepBox,&State);							//发送休眠消息
	}
	CN_st_Fun_Timer.DisEnable(CN_st_Sys_Event.AccSleepfd);
}

