#define De_SleepEvent_Compiler
#include "SleepEvent.h"
#include "..\..\HardWare\UART\UART.h"
void SleepInit(void)					//���ߵĳ�ʼ���¼�
{	const st_Affair_Sleep	CN_st_Affair_Sleep={InitTimerSleep,InitTimerWork};
	if(CN_st_Sys_Event.Sleepfd!=De_Event_No)
	{	CN_st_Fun_Sleep.Close(CN_st_Sys_Event.Sleepfd);
		CN_st_Sys_Event.Sleepfd=De_Event_No;	
	}
	CN_st_Fun_Sleep.Open((st_Affair_Sleep	*)&CN_st_Affair_Sleep,&CN_st_Sys_Event.Sleepfd);
}
/*--------------------------------------------------����ʵ��---------------------------------------------------*/
static void InitTimerWork(uint8 Fd)											//����״̬�µĳ�ʼ��
{	st_File_Parameter	CN_st_File_Parameter;
	CN_st_Fun_File.ReadRecoder(CN_st_File_fd.Parameterfd,0,&CN_st_File_Parameter);
	CN_st_Fun_Timer.DisEnable(CN_st_Sys_Event.SleepCheckTimer);			//�ر������µ�Ѳ��
	CN_st_Fun_Timer.DisEnable(CN_st_Sys_Event.TraCheckDatafd);	
//	CN_st_Fun_Timer.Enable(CN_st_Sys_Event.Timerfd);					
	if(CN_st_File_Parameter.WorkCheckTimer!=0)			//ϵͳ��ҪѲ��
		CN_st_Fun_Timer.Enable(CN_st_Sys_Event.CheckTimer);							
	else
		CN_st_Fun_Timer.DisEnable(CN_st_Sys_Event.CheckTimer);
	CN_st_Fun_Uart.Write(0,"Sleepup\r\n",9);
	CN_st_Sys_State.Sleep=De_Suc_State;
}




	
static void InitTimerSleep(uint8 Fd)					//����ʱ��ĳ�ʼ��
{	st_File_Parameter	CN_st_File_Parameter;
//	CN_st_Fun_Timer.DisEnable(CN_st_Sys_Event.Timerfd);
	CN_st_Fun_Timer.DisEnable(CN_st_Sys_Event.CheckTimer);
	CN_st_Fun_File.ReadRecoder(CN_st_File_fd.Parameterfd,0,&CN_st_File_Parameter);
	if(CN_st_File_Parameter.SleepCheckTimer<300)
	{	CN_st_Fun_Timer.DisEnable(CN_st_Sys_Event.TraCheckDatafd);
		CN_st_Fun_Timer.EditPro(CN_st_Sys_Event.TraCheckDatafd,CN_st_File_Parameter.SleepCheckTimer);
		CN_st_Fun_Timer.EditPro(CN_st_Sys_Event.SleepCheckTimer,5);		   //��������ǰ5���ӻ���
	}
	else
	{	CN_st_Fun_Timer.DisEnable(CN_st_Sys_Event.TraCheckDatafd);
		CN_st_Fun_Timer.EditPro(CN_st_Sys_Event.TraCheckDatafd,300);
		CN_st_Fun_Timer.EditPro(CN_st_Sys_Event.SleepCheckTimer,CN_st_File_Parameter.SleepCheckTimer-300);		   //��������ǰ5���ӻ���
	}
	if(CN_st_File_Parameter.SleepCheckTimer!=0)			//ϵͳ��ҪѲ��
		CN_st_Fun_Timer.Enable(CN_st_Sys_Event.SleepCheckTimer);							
	else
		CN_st_Fun_Timer.DisEnable(CN_st_Sys_Event.SleepCheckTimer);
	CN_st_Fun_Uart.Write(0,"SleepDown\r\n",11);
	CN_st_Sys_State.Sleep=De_State_Sleep;
}
