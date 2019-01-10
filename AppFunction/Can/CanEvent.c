#define De_CanEvent_Compiler
#include "CanEvent.h"
//#include "..\..\HardWare\UART\UART.h"

/*=============================================Can事件====================================================*/
void CanInit(void)
{	union
	{	st_File_Parameter	CN_st_File_Parameter;
		st_Affair_Timer		CN_st_Affair_Timer;
	}a;
	const st_Function_Can		CN_st_Function_Can={Can};
	
	CN_st_Fun_File.ReadRecoder(CN_st_File_fd.Parameterfd,0,&a.CN_st_File_Parameter);
	a.CN_st_Affair_Timer.CN_st_Property_Timer.TimerData=a.CN_st_File_Parameter.CanSendTimer;
	a.CN_st_Affair_Timer.CN_st_Function_Timer.ptFun=SenData;
	if(CN_st_Sys_Event.Canfd!=De_Event_No)
		CN_st_Fun_CanControl.Close(CN_st_Sys_Event.Canfd);	
	CN_st_Fun_CanControl.Open((st_Function_Can	*)&CN_st_Function_Can,&CN_st_Sys_Event.Canfd);
	
	if(CN_st_Sys_Event.CanSendfd!=De_Event_No)
		CN_st_Fun_Timer.Close(CN_st_Sys_Event.CanSendfd);
	CN_st_Fun_Timer.Open(&a.CN_st_Affair_Timer,&CN_st_Sys_Event.CanSendfd);
	CN_st_Fun_Timer.Enable(CN_st_Sys_Event.CanSendfd);				//关闭CAN定时发送
	Amount=0;
}
		 
static void Can(st_Da_CanInfor	*ptst_Da_CanInfor)	 					//CAN的接受
{	uint8 i;
	st_Data_Timer CN_st_Data_Timer;										//获取时间
//	CN_st_Fun_Uart.Write(0,"Receive Can Data\r\n",18);
	for(i=0;i<De_Can_Data_MaxID;i++)
	{	if(ptst_Da_CanInfor->FrameID==CN_st_Data_Can.CanID[i])
			break;
	}
	if(i!=De_Can_Data_MaxID)											//找到一样的ID
	{	//CN_st_Fun_Uart.Write(0,"Can Data Ok\r\n",13);
		CN_st_Fun_Timer.Read(&CN_st_Data_Timer);
		CN_st_Data_Can.CN_CanData[i].FrameData[0]=ptst_Da_CanInfor->FrameData[0];
		CN_st_Data_Can.CN_CanData[i].FrameData[1]=ptst_Da_CanInfor->FrameData[1];
		CN_st_Fun_AscNumber.MoveByte(CN_st_Data_Can.DateTime,CN_st_Data_Timer.DateTime,7);		
	}	
}

static void SenData(st_Data_Timer	*ptst_Data_Timer,uint8 fd)												//定时发送数据到CAN总线上
{	st_File_Parameter	CN_st_File_Parameter;
	st_Da_CanInfor	CN_st_Da_CanInfor;
	CN_st_Da_CanInfor.FrameData[0]=0x00000055;	
	if(Amount&0x01)
		CN_st_Da_CanInfor.FrameData[0]=0x000000AA;
//	if(CN_st_Da_CanInfor.FrameData[0]==0x00000055)
//		CN_st_Fun_Uart.Write(0,"Send 55\r\n",9);
//	else
//		CN_st_Fun_Uart.Write(0,"Send AA\r\n",9);
	CN_st_Da_CanInfor.FrameInfor=0x00080000;
	CN_st_Fun_File.ReadRecoder(CN_st_File_fd.Parameterfd,0,&CN_st_File_Parameter);
	CN_st_Fun_AscNumber.MoveByte(((uint8 *)CN_st_Da_CanInfor.FrameData)+1,CN_st_File_Parameter.EnableChar,3);
	CN_st_Da_CanInfor.FrameID=CN_st_File_Parameter.CanId;
	CN_st_Da_CanInfor.FrameData[1]=0;
	if(CN_st_Sys_State.GpsState==De_Erro_State_GpsBad)
		CN_st_Da_CanInfor.FrameData[1]=0x02000000;
	else if(CN_st_Sys_State.GsmState==De_Erro_State_GsmBad)			
		CN_st_Da_CanInfor.FrameData[1]=0x03000000;										//缺少信号
	else if(CN_st_Sys_State.GsmState==De_Erro_State_GpsNosem)
		CN_st_Da_CanInfor.FrameData[1]=0x04000000;
	CN_st_Fun_CanControl.Write(&CN_st_Da_CanInfor);
//	CN_st_Fun_Uart.Write(0,"Send Can Data\r\n",15);
	Amount++;		
}






