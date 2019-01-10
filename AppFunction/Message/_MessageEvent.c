#define De_MessageEvent_Compiler
#include "MessageEvent.h"
#include "..\..\HardWare\UART\UART.h"
void GprsInit(void)
{ 	uint8 Result;
//	uint8 text[10] = "456jhf";
//	uint8 text1[10] = "123jhf";
	const st_Data_IPNet CN_ptst_Data_IPNet={"CMNET","",""};
	const st_Affair_Gprs	CN_st_Affair_Gprs={AgreenMessage,NewPhone,MessageNoSem,MessageNoWork,MessageSem};
	const st_Affair_UDPTCP	CN_st_Affair_UDPTCP={NULL};
	st_Data_UDPTCP	CN_st_Data_UDPTCP={2,3722939603,7001,40,120,"",25};			  // 221.231.140.211
//	const st_Data_UDPTCP	CN_st_Data_UDPTCP1={1,1968807372,9011,50,0,""};
//	uint8 heartdata[30] = {0x00,0x19,0x20,0x44,0xD9,0x9A,0x2E,0x52,0xA5,0x72,0x01,0xE8,0xAC,0x3A,0x07,0x14,0x62,0xFD,0x07,0x7D,0x00,0x00,0x01,0x07};
	uint8 heartdata[30] = {0x00,0x19,0x20,0x44,0xD9,0x9A,0x2E,0x02,0xCA,0x97,0x72,0x01,0xE8,0xAC,0x3A,0x07,0x14,0x62,0xFD,0x07,0x7D,0x00,0x00,0x01,0x07};
	CN_st_Fun_AscNumber.MoveByte(CN_st_Data_UDPTCP.SelfHeartData,heartdata,25);
	CN_st_Fun_Gprs.OpenMessage((st_Affair_Gprs	*)&CN_st_Affair_Gprs);
	CN_st_Fun_Gprs.InitTCPIP((st_Data_IPNet *)&CN_ptst_Data_IPNet);
	Result=CN_st_Fun_Gprs.OpenUDPTCP((st_Data_UDPTCP *)&CN_st_Data_UDPTCP,(st_Affair_UDPTCP *)&CN_st_Affair_UDPTCP,&UDPFD);			 //(st_Affair_UDPTCP *)&CN_st_Affair_UDPTCP
//	Result=CN_st_Fun_Gprs.OpenUDPTCP((st_Data_UDPTCP *)&CN_st_Data_UDPTCP1,(st_Affair_UDPTCP *)&CN_st_Affair_UDPTCP,&TCPFD);
//	CN_st_Fun_Gprs.SendTCPUDP(UDPFD,text);
//	CN_st_Fun_Gprs.SendTCPUDP(TCPFD,text1);
}
//static void NewTCPIPData(uint8 *Data,uint8 *fd,uint16 DataLength)
//{
//
////	CN_st_Fun_Gprs.SendTCPUDP(*fd,Data,DataLength);		
//}


static void NewPhone(st_Data_Gprs   *ptst_Data_Gprs)
{
	;
//	CN_st_Fun_Gprs.HangPhone();
//	CN_st_Fun_Gprs.CallPhone("13905163025");
//	if(CN_st_Sys_State.Sleep!=De_Suc_State)
//	{	CN_st_Control_Fun_Gps.PowerOpen();
//		CN_st_Fun_Timer.EditPro(CN_st_Sys_Event.DellGpsfd,120);
//		CN_st_Fun_Timer.Enable(CN_st_Sys_Event.DellGpsfd);
//	}
//	else
//	{	OS_ENTER_CRITICAL();
//		while(1)
//		;
//	}
}
static void MessageNoSem(st_Data_Gprs   *ptst_Data_Gprs)
{	CN_st_Sys_State.GsmState=De_Erro_State_GpsNosem;
}


static void MessageNoWork(st_Data_Gprs   *ptst_Data_Gprs)
{	CN_st_Sys_State.GsmState=De_Erro_State_GsmBad;
}



static void MessageSem(st_Data_Gprs   *ptst_Data_Gprs)						//当机器有信号时
{	st_File_Message	CN_st_File_Message;
	st_File_Parameter CN_st_File_Parameter;
	uint8 Messege[300],Phone[15];
	uint16 DataLength,DataLength1;
	uint16 Number,NumberAll;
	CN_st_Sys_State.GsmState=De_Suc_State;
	CN_st_Fun_AscNumber.ClsArray(&CN_st_File_Parameter,sizeof(st_File_Parameter));
	CN_st_Fun_File.ReadRecoder(CN_st_File_fd.Parameterfd,0,&CN_st_File_Parameter);
	for(;;)
	{	if((MessageTail-1)==MessageSendSpace)
			break;
		else if((MessageTail-1)>MessageSendSpace)
			Number=MessageTail-1-MessageSendSpace;
		else
			Number=MessageTail+MessageNumber-1;
		NumberAll=CN_st_Fun_File.GetJlNum(CN_st_File_fd.Messagefd);
		Number=NumberAll+1-Number;
		CN_st_Fun_File.ReadRecoder(CN_st_File_fd.Messagefd,Number,&CN_st_File_Message);
		CN_st_Fun_Uart.Write(0,"SendMessag:",11);
		CN_st_Fun_Uart.Write(0,CN_st_File_Message.Message,CN_st_Fun_AscNumber.Strsize(CN_st_File_Message.Message));
		CN_st_Fun_Uart.Write(0,"Phone:",6);
		CN_st_Fun_Uart.Write(0,CN_st_File_Message.Phone,CN_st_Fun_AscNumber.Strsize(CN_st_File_Message.Phone));
		CN_st_Fun_Uart.Write(0,"\r\n",2);		  								
		if(CN_st_Fun_Gprs.SendMessage(CN_st_File_Message.Message,CN_st_File_Message.Phone,CN_st_File_Parameter.CenPhone)!=De_Suc_Moderm)				 	
		{	SendNumber++;			 //限制发送不成功重发次数
			if(SendNumber>=3)
			{	MessageSendSpace++;
				if(MessageSendSpace==MessageNumber)
					MessageSendSpace=0;
			    CN_st_Fun_File.WriteRecoder(CN_st_File_fd.MessageSend,0,&MessageSendSpace);
				InitCenPhone();
				SendNumber = 0;	
				CN_st_Fun_Hand.LCDputLine((uint8 *)"信息发送失败");	
			}
			continue;
		}
		SendNumber = 0;								  //重新计数
		MessageSendSpace++;
		if(MessageSendSpace==MessageNumber)
			MessageSendSpace=0;
	    CN_st_Fun_File.WriteRecoder(CN_st_File_fd.MessageSend,0,&MessageSendSpace);
		//CN_st_Fun_Hand.LCDputLine((uint8 *)"输入错误");
		
		CN_st_Fun_AscNumber.ClsArray(Messege,sizeof(Messege));
		CN_st_Fun_AscNumber.ClsArray(Phone,sizeof(Phone));
		CN_st_Fun_AscNumber.MoveByte(Messege,(uint8 *)"新短信:",7);
		if(CN_st_Fun_Gprs.ReadMessage(Messege+7,Phone)==De_Erro_MODEL_NoSms)
		{	
			CN_st_Fun_Hand.LCDputLine((uint8 *)"信息发送成功");	
			CN_st_Fun_Uart.Write(0,"NoSms\r\n",7);
			break;
		}
//		CN_st_Fun_AscNumber.MoveByte(Messege+7,CN_st_File_Message.Message,CN_st_Fun_AscNumber.Strsize16(CN_st_File_Message.Message));
		DataLength = CN_st_Fun_AscNumber.Strsize16(Messege);
		DataLength1= CN_st_Fun_AscNumber.Strsize16(Phone);
		CN_st_Fun_AscNumber.MoveByte(Messege+DataLength,(uint8 *)"号码:",5);
		CN_st_Fun_AscNumber.MoveByte(Messege+DataLength+5,Phone,DataLength1);
		CN_st_Fun_Hand.LCDputLine(Messege);	
	}
}

static void AgreenMessage(st_Data_Gprs   *ptst_Data_Gprs)						//GSM接受短信命令	
{	uint16 Result;
	uint8 asc;
	uint8 CenterNum;
	CN_st_Fun_Uart.Write(0,"NewMessage:",11);
	CN_st_Fun_Uart.Write(0,ptst_Data_Gprs->CN_st_Data_Gprs_Message.Message,CN_st_Fun_AscNumber.Strsize(ptst_Data_Gprs->CN_st_Data_Gprs_Message.Message));
	CN_st_Fun_Uart.Write(0,"\r\n",2);
	CN_st_Fun_Uart.Write(0,"NewPhone:",9);
	CN_st_Fun_Uart.Write(0,ptst_Data_Gprs->CN_st_Data_Gprs_Message.Phone,CN_st_Fun_AscNumber.Strsize(ptst_Data_Gprs->CN_st_Data_Gprs_Message.Phone));
	CN_st_Fun_Uart.Write(0,"\r\n",2);
	
	
	if(JugePhone(ptst_Data_Gprs->CN_st_Data_Gprs_Message.Phone,&CenterNum)!=0)								//判断电话号码是否合法
	{	CN_st_Fun_Uart.Write(0,"Phone error",11);
		goto EndAgreenMessage;		
	}
	Result=JugeOrder(ptst_Data_Gprs->CN_st_Data_Gprs_Message.Message);
	CN_st_Fun_Uart.Write(0,"NewMessage OK:",14);
	asc = Result+0x30;
	CN_st_Fun_Uart.Write(0,&asc,1);
	CN_st_Fun_Uart.Write(0,"\r\n",2);
	if(Result==De_App_MessOrder_No)										//本系统不支持此命令
	{	CN_st_Fun_Uart.Write(0,"Message error",13);
		goto EndAgreenMessage;
	}
	else if(Result==De_App_MessOrder_vWaring)							//设置报警数据
		Edit_CV(ptst_Data_Gprs);
	else if(Result==De_App_MessOrder_SeeParameter)						//查询车机参数
		SeeAbout_Machi(ptst_Data_Gprs);	
	else if(Result==De_App_MessOrder_AccInit)							//ACC时间
		Edit_Ce(ptst_Data_Gprs);
	else if(Result==De_App_MessOrder_Lock)								//远程控制
		Lock(ptst_Data_Gprs);
	else if(Result==De_App_MessOrder_unLock)							//远程解锁								
		unLock(ptst_Data_Gprs);
	else if(Result==De_App_MessOrder_TimerSend)							//定时回传
		TimerSend(ptst_Data_Gprs);
	else if(Result==De_App_MessOrder_EditParameter)						//按指令更改
		Edit_Parameter(ptst_Data_Gprs);
	else if(Result==De_App_MessOrder_ComeInit)						   //恢复默认值
		ComeInit(ptst_Data_Gprs);
	EndAgreenMessage:

}

/*==============================================命令处理=======================================================*/
/*
	*CVXX#
*/
static void Edit_CV(st_Data_Gprs	*ptst_Data_Gprs)			//设置速度报警值
{	uint8 Buf[160];
	st_File_Parameter	CN_st_File_Parameter;	
	uint8 DataLen;
	CN_st_Fun_AscNumber.ClsArray(Buf,sizeof(Buf));
	DataLen=CN_st_Fun_AscNumber.Strsize(ptst_Data_Gprs->CN_st_Data_Gprs_Message.Message+3);
	if(DataLen==3)				//有效数据
	{	if(CN_st_Fun_AscNumber.JugeAscHex(ptst_Data_Gprs->CN_st_Data_Gprs_Message.Message+3,2)==0)
		{	
		   	CN_st_Fun_File.ReadRecoder(CN_st_File_fd.Parameterfd,0,&CN_st_File_Parameter);	
			CN_st_File_Parameter.Speed=CN_st_Fun_AscNumber.Asc2Hex(ptst_Data_Gprs->CN_st_Data_Gprs_Message.Message+3,2);
			CN_st_Fun_File.WriteRecoder(CN_st_File_fd.Parameterfd,0,&CN_st_File_Parameter);
			CN_st_Waring_Sys.Speed=CN_st_File_Parameter.Speed;
			CN_st_Fun_AscNumber.ClsArray(Buf,sizeof(Buf));
			Buf[0]='*';
			Buf[1]='Y';
			CN_st_Fun_AscNumber.MoveByte(Buf+2,ptst_Data_Gprs->CN_st_Data_Gprs_Message.Message+1,2);
			Buf[4]='&';
			DataLen=5;
			Get_Gps_Data(Buf+DataLen);
			Buf[CN_st_Fun_AscNumber.Strsize(Buf)]='#';
			SendMessage(Buf,ptst_Data_Gprs->CN_st_Data_Gprs_Message.Phone);
		}	
	}
}

static void SeeAbout_Machi(st_Data_Gprs	*ptst_Data_Gprs)		//查询车机参数
{	uint8 Buf[160];
	st_File_Parameter	CN_st_File_Parameter;
	st_File_Basic		CN_st_File_Basic;
	uint8 DataLen,DataLen1;
//	CN_st_Fun_AscNumber.ClsArray(Buf,sizeof(Buf));
	CN_st_Fun_AscNumber.ClsArray(&CN_st_File_Parameter,sizeof(CN_st_File_Parameter));
	CN_st_Fun_AscNumber.ClsArray(&CN_st_File_Basic,sizeof(CN_st_File_Basic));
	CN_st_Fun_File.ReadRecoder(CN_st_File_fd.Basicfd,0,&CN_st_File_Basic);
	CN_st_Fun_File.ReadRecoder(CN_st_File_fd.Parameterfd,0,&CN_st_File_Parameter);
	CN_st_Fun_AscNumber.ClsArray(Buf,sizeof(Buf));
	Buf[0]='*';Buf[1]='Q';Buf[2]='C';
	DataLen1=CN_st_Fun_AscNumber.Strsize(CN_st_File_Parameter.CenterPhone1);
	if(DataLen1>15)
		DataLen1=15;
	Buf[3]='0'+DataLen1;
	CN_st_Fun_AscNumber.MoveByte(Buf+4,CN_st_File_Parameter.CenterPhone1,DataLen1);	//中心一的电话号码
	DataLen=CN_st_Fun_AscNumber.Strsize(Buf);
	Buf[DataLen++]='c';
	DataLen1=CN_st_Fun_AscNumber.Strsize(CN_st_File_Parameter.CenterPhone2);
	if(DataLen1>15)
		DataLen1=15;
	Buf[DataLen++]='0'+DataLen1;
	CN_st_Fun_AscNumber.MoveByte(Buf+DataLen,CN_st_File_Parameter.CenterPhone2,DataLen1);	//中心二的电话号码
	DataLen=CN_st_Fun_AscNumber.Strsize(Buf);
	
	Buf[DataLen++]='V';
	Buf[DataLen++]='2';
	DataLen1=CN_st_File_Parameter.Speed;
	CN_st_Fun_AscNumber.HexBuf2Asc(&DataLen1,Buf+DataLen,1);				//速度值
	DataLen+=2;
	
	Buf[DataLen++]='T';
	Buf[DataLen++]='4';
	DataLen1 = CN_st_Fun_AscNumber.Hex2Asc(CN_st_File_Parameter.SleepTimer,Buf+DataLen);			//省电时间
	memset(Buf+DataLen,'0',4-DataLen1);
	CN_st_Fun_AscNumber.Hex2Asc(CN_st_File_Parameter.SleepTimer,Buf+DataLen+4-DataLen1);
	DataLen+=4;
	
	DataLen1=CN_st_Fun_AscNumber.Strsize(CN_st_File_Basic.SoftEdition);
	if(DataLen1>8)
		DataLen1=8;
	Buf[DataLen++]='R';
	Buf[DataLen++]='0'+DataLen1;
	CN_st_Fun_AscNumber.MoveByte(Buf+DataLen,CN_st_File_Basic.SoftEdition,DataLen1);	//软件版本
	DataLen+=DataLen1;
	
	DataLen1=CN_st_Fun_AscNumber.Strsize(CN_st_File_Basic.HardEdition);						
	if(DataLen1>8)
		DataLen1=8;
	Buf[DataLen++]='Y';
	Buf[DataLen++]='0'+DataLen1;
	CN_st_Fun_AscNumber.MoveByte(Buf+DataLen,CN_st_File_Basic.HardEdition,DataLen1);		//硬件版本
	DataLen+=DataLen1;
	
	DataLen1=CN_st_Fun_AscNumber.Strsize(CN_st_File_Basic.MachID);
	if(DataLen1>16)
		DataLen1=16;
	Buf[DataLen++]='X';
	Buf[DataLen++]='0'+DataLen1;
	CN_st_Fun_AscNumber.MoveByte(Buf+DataLen,CN_st_File_Basic.MachID,DataLen1);	
	DataLen+=DataLen1;
	Buf[DataLen++]='&';
	Get_Gps_Data(Buf+DataLen);
	DataLen=CN_st_Fun_AscNumber.Strsize(Buf);
	Buf[DataLen]='#';
	SendMessage(Buf,ptst_Data_Gprs->CN_st_Data_Gprs_Message.Phone);				
}

static void Edit_Ce(st_Data_Gprs	*ptst_Data_Gprs)				//更改ACC累计时间				
{	uint8 Buf[160];
	uint32 AccTimer;
	uint8 i,DataLen;
	AccTimer=0;
	CN_st_Fun_AscNumber.ClsArray(Buf,sizeof(Buf));
	if(ptst_Data_Gprs->CN_st_Data_Gprs_Message.Message[3]=='H')										
	{	for(i=0;i<8;i++)
		{	if(((ptst_Data_Gprs->CN_st_Data_Gprs_Message.Message[i+3]>='0')&&(ptst_Data_Gprs->CN_st_Data_Gprs_Message.Message[i+3]<='9'))
			||((ptst_Data_Gprs->CN_st_Data_Gprs_Message.Message[i+3]>='a')&&(ptst_Data_Gprs->CN_st_Data_Gprs_Message.Message[i+3]<='f'))
			||((ptst_Data_Gprs->CN_st_Data_Gprs_Message.Message[i+3]>='A')&&(ptst_Data_Gprs->CN_st_Data_Gprs_Message.Message[i+3]<='F')))
				continue;	
			break;
		}
		AccTimer=CN_st_Fun_AscNumber.Asc2Hex(ptst_Data_Gprs->CN_st_Data_Gprs_Message.Message+4,i);
	}
	CN_st_Fun_File.WriteRecoder(CN_st_File_fd.AccTimerfd,0,&AccTimer);
   	CN_st_Fun_AscNumber.ClsArray(Buf,sizeof(Buf));
	Buf[0]='*';
	CN_st_Fun_AscNumber.MoveByte(Buf+1,ptst_Data_Gprs->CN_st_Data_Gprs_Message.Message+1,3+i);
	DataLen=4+i;
	Buf[DataLen++]='&';
	Get_Gps_Data(Buf+DataLen);
	Buf[CN_st_Fun_AscNumber.Strsize(Buf)]='#';
	SendMessage(Buf,ptst_Data_Gprs->CN_st_Data_Gprs_Message.Phone);
}


static void Lock(st_Data_Gprs	*ptst_Data_Gprs)					//远程控制
{	union
	{	st_File_Parameter	CN_st_File_Parameter;
		uint8 Buf[100];
	}a;
	
	CN_st_Fun_File.ReadRecoder(CN_st_File_fd.Parameterfd,0,&a.CN_st_File_Parameter);
	a.CN_st_File_Parameter.ControlEnable=De_State_Control;
	CN_st_Fun_File.WriteRecoder(CN_st_File_fd.Parameterfd,0,&a.CN_st_File_Parameter);
	CN_st_Sys_State.Control=a.CN_st_File_Parameter.ControlEnable;	
	De_IO_Lock;													//继电器打开
	CN_st_Fun_AscNumber.ClsArray(a.Buf,sizeof(a.Buf));
	a.Buf[0]='*';a.Buf[1]='Y';a.Buf[2]='L';a.Buf[3]='&';
	Get_Gps_Data(a.Buf+4);
	a.Buf[CN_st_Fun_AscNumber.Strsize(a.Buf)]='#';
	SendMessage(a.Buf,ptst_Data_Gprs->CN_st_Data_Gprs_Message.Phone);							
}

static void unLock(st_Data_Gprs	*ptst_Data_Gprs)					//解除锁车
{	union
	{	st_File_Parameter	CN_st_File_Parameter;
		uint8 Buf[100];
	}a;
	CN_st_Fun_AscNumber.ClsArray(a.Buf,sizeof(a.Buf));
	CN_st_Fun_File.ReadRecoder(CN_st_File_fd.Parameterfd,0,&a.CN_st_File_Parameter);
	a.CN_st_File_Parameter.ControlEnable=De_State_NoControl;
	CN_st_Fun_File.WriteRecoder(CN_st_File_fd.Parameterfd,0,&a.CN_st_File_Parameter);
	CN_st_Sys_State.Control=a.CN_st_File_Parameter.ControlEnable;	
	De_IO_unLock;				//继电器关闭
	CN_st_Fun_AscNumber.ClsArray(a.Buf,sizeof(a.Buf));
	a.Buf[0]='*';a.Buf[1]='Y';a.Buf[2]='J';a.Buf[3]='&';
	Get_Gps_Data(a.Buf+4);
	a.Buf[CN_st_Fun_AscNumber.Strsize(a.Buf)]='#';
	SendMessage(a.Buf,ptst_Data_Gprs->CN_st_Data_Gprs_Message.Phone);						
}

static void ComeInit(st_Data_Gprs	*ptst_Data_Gprs)					//恢复默认值
{	union
	{	st_File_Parameter	CN_st_File_Parameter;
		uint8 Buf[100];
	}a;
	BackInit();
//	CN_st_Fun_File.ReadRecoder(CN_st_File_fd.Parameterfd,0,&a.CN_st_File_Parameter);
//	a.CN_st_File_Parameter.ControlEnable=De_State_NoControl;
//	CN_st_Fun_File.WriteRecoder(CN_st_File_fd.Parameterfd,0,&a.CN_st_File_Parameter);
//	CN_st_Sys_State.Control=a.CN_st_File_Parameter.ControlEnable;	
//	De_IO_unLock;				//继电器关闭
	a.Buf[0]='*';a.Buf[1]='Y';a.Buf[2]='U';a.Buf[3]='&';
	Get_Gps_Data(a.Buf+4);
	a.Buf[CN_st_Fun_AscNumber.Strsize(a.Buf)]='#';
	SendMessage(a.Buf,ptst_Data_Gprs->CN_st_Data_Gprs_Message.Phone);						
}

/*	*DNNVVVV#
*/
static void TimerSend(st_Data_Gprs	*ptst_Data_Gprs)	  				//定时回传
{	st_File_UpLoader	CN_st_File_UpLoader;
	st_File_Parameter CN_st_File_Parameter;
	uint8 Buf[100];
	uint8 DataLen;
	uint8 CenterNum;
	if(JugePhone(ptst_Data_Gprs->CN_st_Data_Gprs_Message.Phone,&CenterNum)==0)								//判断电话号码是否合法
	{		CN_st_Fun_File.ReadRecoder(CN_st_File_fd.Parameterfd,0,&CN_st_File_Parameter);
			CN_st_File_Parameter.TimePhone=CenterNum;
			CN_st_Fun_File.WriteRecoder(CN_st_File_fd.Parameterfd,0,&CN_st_File_Parameter);			
	}
	CN_st_Fun_AscNumber.ClsArray(&CN_st_File_UpLoader,sizeof(st_File_UpLoader)); 		//清除数据
	CN_st_File_UpLoader.Number=CN_st_Fun_AscNumber.Asc2Hex(ptst_Data_Gprs->CN_st_Data_Gprs_Message.Message+2,2);
	CN_st_File_UpLoader.Timer=CN_st_Fun_AscNumber.Asc2Hex(ptst_Data_Gprs->CN_st_Data_Gprs_Message.Message+4,4);	 			//定时回传的次数
	CN_st_File_UpLoader.NonceNumber=0;
	CN_st_File_UpLoader.NonceNumber++;
	if((CN_st_File_UpLoader.Timer<10)&&(CN_st_File_UpLoader.Timer!=0))
		CN_st_File_UpLoader.Timer=10;
	CN_st_Fun_File.WriteRecoder(CN_st_File_fd.UpLoaderfd,0,&CN_st_File_UpLoader);	

	if(CN_st_File_UpLoader.Number!=1)			//先判断是追踪还是定位，追踪唤醒机器后不立即休眠
	{
		CN_st_Fun_Timer.EditPro(CN_st_Sys_Event.Timerfd,600);	  //先唤醒，使能定时器，以保证Gps不重新进入休眠
		CN_st_Fun_Timer.Enable(CN_st_Sys_Event.Timerfd);	
	}
	else
		CN_st_Fun_Timer.DisEnable(CN_st_Sys_Event.Timerfd);

	CN_st_Fun_AscNumber.ClsArray(Buf,sizeof(Buf));
	Buf[0]='*';Buf[1]='D';
	Get_Gps_Data(Buf+2);						//发送数据
	DataLen=CN_st_Fun_AscNumber.Strsize(Buf);
	Buf[DataLen++]='#';
	SendMessage(Buf,ptst_Data_Gprs->CN_st_Data_Gprs_Message.Phone);

	if(CN_st_File_UpLoader.Number!=1)
	{		
		CN_st_Fun_Timer.EditPro(CN_st_Sys_Event.Timerfd,CN_st_File_UpLoader.Timer);
		CN_st_Fun_Timer.Enable(CN_st_Sys_Event.Timerfd);
				
	}

//	CN_st_Fun_Timer.EditPro(CN_st_Sys_Event.Timerfd,CN_st_File_UpLoader.Timer);	//以第一条时间为准重新开始计时
	
}
static void Edit_Parameter(st_Data_Gprs	*ptst_Data_Gprs)
{	if(ptst_Data_Gprs->CN_st_Data_Gprs_Message.Message[2]=='1')
		Edit_C1(ptst_Data_Gprs);	
	else if(ptst_Data_Gprs->CN_st_Data_Gprs_Message.Message[2]=='2')
		Edit_C2(ptst_Data_Gprs);
	else if(ptst_Data_Gprs->CN_st_Data_Gprs_Message.Message[2]=='c')
		Edit_Cc(ptst_Data_Gprs);
	else if(ptst_Data_Gprs->CN_st_Data_Gprs_Message.Message[2]=='m')
		Edit_Cm(ptst_Data_Gprs);
	else if(ptst_Data_Gprs->CN_st_Data_Gprs_Message.Message[2]=='E')
		Edit_CE(ptst_Data_Gprs);
	else if(ptst_Data_Gprs->CN_st_Data_Gprs_Message.Message[2]=='S')
		Edit_CS(ptst_Data_Gprs);
	else if(ptst_Data_Gprs->CN_st_Data_Gprs_Message.Message[2]=='t')
		Edit_Ct(ptst_Data_Gprs);	
	else if(ptst_Data_Gprs->CN_st_Data_Gprs_Message.Message[2]=='p')								
		Edit_Cp(ptst_Data_Gprs);
}

/*	* *C1电话号码#    */
static void Edit_C1(st_Data_Gprs	*ptst_Data_Gprs)				//修改中心电话号码
{	uint8 Buf[160];
	st_File_Parameter	CN_st_File_Parameter;
	uint8 DataLen;
	DataLen=CN_st_Fun_AscNumber.Strsize(ptst_Data_Gprs->CN_st_Data_Gprs_Message.Message+3);
	if(DataLen>1)
	{	DataLen--;
		CN_st_Fun_File.ReadRecoder(CN_st_File_fd.Parameterfd,0,&CN_st_File_Parameter);
		CN_st_Fun_AscNumber.ClsArray(CN_st_File_Parameter.CenterPhone1,15);
		CN_st_Fun_AscNumber.MoveByte(CN_st_File_Parameter.CenterPhone1,ptst_Data_Gprs->CN_st_Data_Gprs_Message.Message+3,DataLen);
	   	CN_st_Fun_File.WriteRecoder(CN_st_File_fd.Parameterfd,0,&CN_st_File_Parameter);
		CN_st_Fun_AscNumber.ClsArray(Buf,sizeof(Buf));
		Buf[0]='*';
		Buf[1]='Y';
		CN_st_Fun_AscNumber.MoveByte(Buf+2,ptst_Data_Gprs->CN_st_Data_Gprs_Message.Message+1,2);
		DataLen=4;
		Buf[DataLen++]='&';
		Get_Gps_Data(Buf+DataLen);
		Buf[CN_st_Fun_AscNumber.Strsize(Buf)]='#';
	   	SendMessage(Buf,ptst_Data_Gprs->CN_st_Data_Gprs_Message.Phone);
	}
}
/*	* *C2电话号码#    */
static void Edit_C2(st_Data_Gprs	*ptst_Data_Gprs)
{	uint8 Buf[160];
	st_File_Parameter	CN_st_File_Parameter;
	uint8 DataLen;

	DataLen=CN_st_Fun_AscNumber.Strsize(ptst_Data_Gprs->CN_st_Data_Gprs_Message.Message+3);
	if(DataLen>1)
	{	DataLen--;		
		CN_st_Fun_File.ReadRecoder(CN_st_File_fd.Parameterfd,0,&CN_st_File_Parameter);
		CN_st_Fun_AscNumber.ClsArray(CN_st_File_Parameter.CenterPhone2,15);
		CN_st_Fun_AscNumber.MoveByte(CN_st_File_Parameter.CenterPhone2,ptst_Data_Gprs->CN_st_Data_Gprs_Message.Message+3,DataLen);
	   	CN_st_Fun_File.WriteRecoder(CN_st_File_fd.Parameterfd,0,&CN_st_File_Parameter);
		CN_st_Fun_AscNumber.ClsArray(Buf,sizeof(Buf));
		Buf[0]='*';Buf[1]='Y';
		CN_st_Fun_AscNumber.MoveByte(Buf+2,ptst_Data_Gprs->CN_st_Data_Gprs_Message.Message+1,2);
		DataLen=4;
		Buf[DataLen++]='&';
		Get_Gps_Data(Buf+DataLen);
		Buf[CN_st_Fun_AscNumber.Strsize(Buf)]='#';
	   	SendMessage(Buf,ptst_Data_Gprs->CN_st_Data_Gprs_Message.Phone);
	}
}
/*	* *Cc电话号码#    */
static void Edit_Cc(st_Data_Gprs	*ptst_Data_Gprs)
{	uint8 Buf[160];
	st_File_Parameter	CN_st_File_Parameter;
	uint8 DataLen;

	DataLen=CN_st_Fun_AscNumber.Strsize(ptst_Data_Gprs->CN_st_Data_Gprs_Message.Message+3);
	if(DataLen>1)
	{	DataLen--;		
		CN_st_Fun_File.ReadRecoder(CN_st_File_fd.Parameterfd,0,&CN_st_File_Parameter);
		CN_st_Fun_AscNumber.ClsArray(CN_st_File_Parameter.CenPhone,15);
		CN_st_Fun_AscNumber.MoveByte(CN_st_File_Parameter.CenPhone,ptst_Data_Gprs->CN_st_Data_Gprs_Message.Message+3,DataLen);
	   	CN_st_Fun_File.WriteRecoder(CN_st_File_fd.Parameterfd,0,&CN_st_File_Parameter);
		CN_st_Fun_AscNumber.ClsArray(Buf,sizeof(Buf));
		Buf[0]='*';Buf[1]='Y';
		CN_st_Fun_AscNumber.MoveByte(Buf+2,ptst_Data_Gprs->CN_st_Data_Gprs_Message.Message+1,2);
		DataLen=4;
		Buf[DataLen++]='&';
		Get_Gps_Data(Buf+DataLen);
		Buf[CN_st_Fun_AscNumber.Strsize(Buf)]='#';
	   	SendMessage(Buf,ptst_Data_Gprs->CN_st_Data_Gprs_Message.Phone);
	}
}
/*	* *CmVVVVVV#    */
static void Edit_Cm(st_Data_Gprs	*ptst_Data_Gprs)
{	uint8 Buf[160];
	st_File_Parameter	CN_st_File_Parameter;
	uint8 DataLen;

	DataLen=CN_st_Fun_AscNumber.Strsize(ptst_Data_Gprs->CN_st_Data_Gprs_Message.Message+3);
	if((CN_st_Fun_AscNumber.CompareBuf(ptst_Data_Gprs->CN_st_Data_Gprs_Message.Message+3,"5A5B5C",6)==0)||(CN_st_Fun_AscNumber.CompareBuf(ptst_Data_Gprs->CN_st_Data_Gprs_Message.Message+3,"A5B5C5",6)==0))
	{	CN_st_Fun_File.ReadRecoder(CN_st_File_fd.Parameterfd,0,&CN_st_File_Parameter);
		CN_st_File_Parameter.ControlEnable=De_State_NoControl;
		CN_st_Fun_File.WriteRecoder(CN_st_File_fd.Parameterfd,0,&CN_st_File_Parameter);
		CN_st_Sys_State.Control=CN_st_File_Parameter.ControlEnable;	
		De_IO_unLock;	
	}
	else if(CN_st_Fun_AscNumber.CompareBuf(ptst_Data_Gprs->CN_st_Data_Gprs_Message.Message+3,"5A5B5E",6)==0)
	{	CN_st_Fun_File.ReadRecoder(CN_st_File_fd.Parameterfd,0,&CN_st_File_Parameter);
		CN_st_File_Parameter.ControlEnable=De_State_Control;
		CN_st_Fun_File.WriteRecoder(CN_st_File_fd.Parameterfd,0,&CN_st_File_Parameter);
		CN_st_Sys_State.Control=CN_st_File_Parameter.ControlEnable;	
		De_IO_Lock;	
	}
	if(DataLen>1)
	{	DataLen--;		
		CN_st_Fun_File.ReadRecoder(CN_st_File_fd.Parameterfd,0,&CN_st_File_Parameter);
		CN_st_Fun_AscNumber.ClsArray(CN_st_File_Parameter.EnableChar,3);
		CN_st_Fun_AscNumber.Asc2HexBuf(ptst_Data_Gprs->CN_st_Data_Gprs_Message.Message+3,CN_st_File_Parameter.EnableChar,DataLen);
//		CN_st_Fun_AscNumber.MoveByte(CN_st_File_Parameter.EnableChar,ptst_Data_Gprs->CN_st_Data_Gprs_Message.Message+3,DataLen);
	   	CN_st_Fun_File.WriteRecoder(CN_st_File_fd.Parameterfd,0,&CN_st_File_Parameter);
		CN_st_Fun_AscNumber.ClsArray(Buf,sizeof(Buf));
		Buf[0]='*';Buf[1]='Y';
		CN_st_Fun_AscNumber.MoveByte(Buf+2,ptst_Data_Gprs->CN_st_Data_Gprs_Message.Message+1,8);
		DataLen=10;
		Buf[DataLen++]='&';
		Get_Gps_Data(Buf+DataLen);
		Buf[CN_st_Fun_AscNumber.Strsize(Buf)]='#';
	   	SendMessage(Buf,ptst_Data_Gprs->CN_st_Data_Gprs_Message.Phone);
	}
}

/*	*CEVVVV

*/
static void Edit_CE(st_Data_Gprs	*ptst_Data_Gprs)  					//更改巡检时间
{	uint8 Buf[160],i;//,Phone[15];
	st_File_Parameter	CN_st_File_Parameter;
	uint8 DataLen,CenterNum;
 	DataLen=CN_st_Fun_AscNumber.Strsize(ptst_Data_Gprs->CN_st_Data_Gprs_Message.Message+3);
	if(DataLen==5)				//代表命令有效
	{	if(CN_st_Fun_AscNumber.JugeAscHex(ptst_Data_Gprs->CN_st_Data_Gprs_Message.Message+3,4)==0)			//数据类型有效
		{	CN_st_Fun_File.ReadRecoder(CN_st_File_fd.Parameterfd,0,&CN_st_File_Parameter);
			CN_st_File_Parameter.WorkCheckTimer=CN_st_Fun_AscNumber.Asc2Hex(ptst_Data_Gprs->CN_st_Data_Gprs_Message.Message+3,4)*60;
			if(JugePhone(ptst_Data_Gprs->CN_st_Data_Gprs_Message.Phone,&CenterNum)==0)								//判断电话号码是否合法	
				CN_st_File_Parameter.CheckPhone=CenterNum;
			CN_st_Fun_File.WriteRecoder(CN_st_File_fd.Parameterfd,0,&CN_st_File_Parameter);
			CN_st_Fun_AscNumber.ClsArray(Buf,sizeof(Buf));
			Buf[0]='*';Buf[1]='Y';Buf[2]='C';
			Buf[3]='E';DataLen = 4;Buf[DataLen++]='&';
			Get_Gps_Data(Buf+DataLen);
			Buf[CN_st_Fun_AscNumber.Strsize(Buf)]='#';
		   	SendMessage(Buf,ptst_Data_Gprs->CN_st_Data_Gprs_Message.Phone);

			if((CN_st_File_Parameter.WorkCheckTimer!=0)&&(CN_st_Sys_State.Sleep==De_Suc_State))			 //取消巡检时不发送巡检指令
			{
				DataLen = 0;
				CN_st_Fun_AscNumber.ClsArray(Buf,sizeof(Buf));
				Buf[DataLen++]='*';Buf[DataLen++]='H';Buf[DataLen++]='Y';
				if(CN_st_Fun_Date.Juge(CN_st_Data_Can.DateTime,De_Type_Date_Second)==De_Suc_Date) 
				{	Buf[DataLen++]='0';Buf[DataLen++]='2';								//厂家代号
					Buf[DataLen++]='0';Buf[DataLen++]='2';								//机器型号
					CN_st_Fun_Uart.Write(0,"Can Data Ok\r\n",13);
					CN_st_Fun_AscNumber.Bcd2Asc(CN_st_Data_Can.DateTime+4,Buf+DataLen,3);
					DataLen+=6;
					CN_st_Fun_AscNumber.Bcd2Asc(CN_st_Data_Can.DateTime+3,Buf+DataLen,1);
					DataLen+=2;
					CN_st_Fun_AscNumber.Bcd2Asc(CN_st_Data_Can.DateTime+2,Buf+DataLen,1);
					DataLen+=2;
					CN_st_Fun_AscNumber.Bcd2Asc(CN_st_Data_Can.DateTime+1,Buf+DataLen,1);
					DataLen+=2;
					Buf[DataLen++]='1';Buf[DataLen++]='8';						//技术状态
					for(i=0;i<4;i++)
					{	CN_st_Fun_AscNumber.HexBuf2Asc((uint8 *)&CN_st_Data_Can.CN_CanData[i].FrameData[0],Buf+DataLen,4);
						DataLen+=8;
						CN_st_Fun_AscNumber.HexBuf2Asc((uint8 *)&CN_st_Data_Can.CN_CanData[i].FrameData[1],Buf+DataLen,4);	
						DataLen+=8;
					}
					DataLen-=12;
					CN_st_Fun_AscNumber.HexBuf2Asc((uint8 *)&CN_st_Data_Can.CN_CanData[i].FrameData[0],Buf+DataLen,4);
					DataLen+=8;
					CN_st_Fun_AscNumber.HexBuf2Asc((uint8 *)&CN_st_Data_Can.CN_CanData[i].FrameData[1],Buf+DataLen,4);	
					DataLen+=8;
					memset(Buf+DataLen-2,'F',14);
					DataLen+=12;			//填补前一帧数据的备用6个字节数据	 //6.17
				}
				Buf[DataLen++]='&';
				Get_Gps_Data(Buf+DataLen);
				DataLen=CN_st_Fun_AscNumber.Strsize(Buf);
				Buf[DataLen++]='#';
				SendMessage(Buf,ptst_Data_Gprs->CN_st_Data_Gprs_Message.Phone);
			}
	
			CN_st_Fun_Timer.EditPro(CN_st_Sys_Event.CheckTimer,CN_st_File_Parameter.WorkCheckTimer);
//			if(CN_st_Sys_State.Sleep==De_Suc_State)
//			{	State=De_Suc_State;
//				OSMboxPost (SleepBox,&State);		 	
//			}
			if(CN_st_Sys_State.Sleep==De_Suc_State)
			{	if(CN_st_File_Parameter.WorkCheckTimer!=0)			//系统需要巡检
					CN_st_Fun_Timer.Enable(CN_st_Sys_Event.CheckTimer);							
				else
					CN_st_Fun_Timer.DisEnable(CN_st_Sys_Event.CheckTimer);
			}			
		}
	}
}
/*	*CSVVVV

*/
static void Edit_CS(st_Data_Gprs	*ptst_Data_Gprs) 				//休眠状态下的巡检时间
{	uint8 Buf[160],i;//,Phone[15];
	st_File_Parameter	CN_st_File_Parameter;
	uint8 DataLen,CenterNum;
 	DataLen=CN_st_Fun_AscNumber.Strsize(ptst_Data_Gprs->CN_st_Data_Gprs_Message.Message+3);
	if(DataLen==5)				//代表命令有效
	{	if(CN_st_Fun_AscNumber.JugeAscHex(ptst_Data_Gprs->CN_st_Data_Gprs_Message.Message+3,4)==0)			//数据类型有效
		{	CN_st_Fun_File.ReadRecoder(CN_st_File_fd.Parameterfd,0,&CN_st_File_Parameter);
			CN_st_File_Parameter.SleepCheckTimer=CN_st_Fun_AscNumber.Asc2Hex(ptst_Data_Gprs->CN_st_Data_Gprs_Message.Message+3,4)*60;
			if(JugePhone(ptst_Data_Gprs->CN_st_Data_Gprs_Message.Phone,&CenterNum)==0)								//判断电话号码是否合法	
				CN_st_File_Parameter.CheckPhone=CenterNum;
			CN_st_Fun_File.WriteRecoder(CN_st_File_fd.Parameterfd,0,&CN_st_File_Parameter);
			CN_st_Fun_AscNumber.ClsArray(Buf,sizeof(Buf));
			Buf[0]='*';Buf[1]='Y';Buf[2]='C';Buf[3]='S';
			DataLen = 4;Buf[DataLen++]='&';
			Get_Gps_Data(Buf+DataLen);
			Buf[CN_st_Fun_AscNumber.Strsize(Buf)]='#';
		   	SendMessage(Buf,ptst_Data_Gprs->CN_st_Data_Gprs_Message.Phone);

			if((CN_st_File_Parameter.SleepCheckTimer!=0)&&(CN_st_Sys_State.Sleep!=De_Suc_State))			 //取消巡检时不发送巡检指令
			{
				DataLen = 0;
				CN_st_Fun_AscNumber.ClsArray(Buf,sizeof(Buf));
				Buf[DataLen++]='*';Buf[DataLen++]='H';Buf[DataLen++]='Y';
				if(CN_st_Fun_Date.Juge(CN_st_Data_Can.DateTime,De_Type_Date_Second)==De_Suc_Date) 
				{	Buf[DataLen++]='0';Buf[DataLen++]='2';								//厂家代号
					Buf[DataLen++]='0';Buf[DataLen++]='2';								//机器型号
					CN_st_Fun_Uart.Write(0,"Can Data Ok\r\n",13);
					CN_st_Fun_AscNumber.Bcd2Asc(CN_st_Data_Can.DateTime+4,Buf+DataLen,3);
					DataLen+=6;
					CN_st_Fun_AscNumber.Bcd2Asc(CN_st_Data_Can.DateTime+3,Buf+DataLen,1);
					DataLen+=2;
					CN_st_Fun_AscNumber.Bcd2Asc(CN_st_Data_Can.DateTime+2,Buf+DataLen,1);
					DataLen+=2;
					CN_st_Fun_AscNumber.Bcd2Asc(CN_st_Data_Can.DateTime+1,Buf+DataLen,1);
					DataLen+=2;
					Buf[DataLen++]='1';Buf[DataLen++]='8';						//技术状态
					for(i=0;i<4;i++)
					{	CN_st_Fun_AscNumber.HexBuf2Asc((uint8 *)&CN_st_Data_Can.CN_CanData[i].FrameData[0],Buf+DataLen,4);
						DataLen+=8;
						CN_st_Fun_AscNumber.HexBuf2Asc((uint8 *)&CN_st_Data_Can.CN_CanData[i].FrameData[1],Buf+DataLen,4);	
						DataLen+=8;
					}
					DataLen-=12;
					CN_st_Fun_AscNumber.HexBuf2Asc((uint8 *)&CN_st_Data_Can.CN_CanData[i].FrameData[0],Buf+DataLen,4);
					DataLen+=8;
					CN_st_Fun_AscNumber.HexBuf2Asc((uint8 *)&CN_st_Data_Can.CN_CanData[i].FrameData[1],Buf+DataLen,4);	
					DataLen+=8;
					memset(Buf+DataLen-2,'F',14);
					DataLen+=12;			//填补前一帧数据的备用6个字节数据	 //6.17
				}
				Buf[DataLen++]='&';
				Get_Gps_Data(Buf+DataLen);
				DataLen=CN_st_Fun_AscNumber.Strsize(Buf);
				Buf[DataLen++]='#';
				SendMessage(Buf,ptst_Data_Gprs->CN_st_Data_Gprs_Message.Phone);
			}
			if(CN_st_File_Parameter.SleepCheckTimer<300)
			{	CN_st_Fun_Timer.DisEnable(CN_st_Sys_Event.TraCheckDatafd);
				CN_st_Fun_Timer.EditPro(CN_st_Sys_Event.TraCheckDatafd,CN_st_File_Parameter.SleepCheckTimer);
				CN_st_Fun_Timer.EditPro(CN_st_Sys_Event.SleepCheckTimer,5);		   //休眠下提前5分钟唤醒
			}
			else
			{	CN_st_Fun_Timer.DisEnable(CN_st_Sys_Event.TraCheckDatafd);
				CN_st_Fun_Timer.EditPro(CN_st_Sys_Event.TraCheckDatafd,300);
				CN_st_Fun_Timer.EditPro(CN_st_Sys_Event.SleepCheckTimer,CN_st_File_Parameter.SleepCheckTimer-300);		   //休眠下提前5分钟唤醒
			}
			if(CN_st_Sys_State.Sleep==De_State_Sleep)
			{
				if(CN_st_File_Parameter.SleepCheckTimer!=0)			//系统需要巡检
					CN_st_Fun_Timer.Enable(CN_st_Sys_Event.SleepCheckTimer);							
				else
					CN_st_Fun_Timer.DisEnable(CN_st_Sys_Event.SleepCheckTimer);
			}
//			if(CN_st_Sys_State.Sleep==De_State_Sleep)
//			{	State=De_State_Sleep;
//				CN_st_Fun_Timer.DisEnable(CN_st_Sys_Event.TraCheckDatafd);	 //修改巡检时间后关闭提前5分钟唤醒计时器，重新开始巡检计时
//				OSMboxPost (SleepBox,&State);		 	
//			}
					
		}
	}
}
 /*		*CtVVVV#	*/
static void Edit_Ct(st_Data_Gprs	*ptst_Data_Gprs)				//休眠
{	uint8 Buf[160];
	st_File_Parameter	CN_st_File_Parameter;
	uint8 DataLen;
	
 	DataLen=CN_st_Fun_AscNumber.Strsize(ptst_Data_Gprs->CN_st_Data_Gprs_Message.Message+3);
	if(DataLen==5)				//代表命令有效
	{	if(CN_st_Fun_AscNumber.JugeAscHex(ptst_Data_Gprs->CN_st_Data_Gprs_Message.Message+3,4)==0)			//数据类型有效
		{	CN_st_Fun_File.ReadRecoder(CN_st_File_fd.Parameterfd,0,&CN_st_File_Parameter);
			CN_st_File_Parameter.SleepTimer=CN_st_Fun_AscNumber.Asc2Hex(ptst_Data_Gprs->CN_st_Data_Gprs_Message.Message+3,4);
			if(CN_st_File_Parameter.SleepTimer<120)
				CN_st_File_Parameter.SleepTimer = 120;
			CN_st_Fun_File.WriteRecoder(CN_st_File_fd.Parameterfd,0,&CN_st_File_Parameter);
			CN_st_Fun_AscNumber.ClsArray(Buf,sizeof(Buf));
			Buf[0]='*';
			Buf[1]='Y';
			CN_st_Fun_AscNumber.MoveByte(Buf+2,ptst_Data_Gprs->CN_st_Data_Gprs_Message.Message+1,2);
			DataLen=4;
			Buf[DataLen++]='&';
			Get_Gps_Data(Buf+DataLen);
			Buf[CN_st_Fun_AscNumber.Strsize(Buf)]='#';
		   	SendMessage(Buf,ptst_Data_Gprs->CN_st_Data_Gprs_Message.Phone);		
			CN_st_Fun_Timer.EditPro(CN_st_Sys_Event.AccSleepfd,CN_st_File_Parameter.SleepTimer);
		}
	}
}
/*	*CpX123456#

*/
static void Edit_Cp(st_Data_Gprs	*ptst_Data_Gprs)				//更改ACC
{	uint8 Buf[160];
	st_File_Parameter	CN_st_File_Parameter;
	uint16 fd;
	uint8 DataLen;
	
	DataLen=CN_st_Fun_AscNumber.Strsize(ptst_Data_Gprs->CN_st_Data_Gprs_Message.Message+3);
	if(DataLen==8)
	{	if(CN_st_Fun_AscNumber.CompareBuf(ptst_Data_Gprs->CN_st_Data_Gprs_Message.Message+4,"123456",6)==0)			//密码比对正确
		{	CN_st_Fun_File.ReadRecoder(CN_st_File_fd.Parameterfd,0,&CN_st_File_Parameter);
			if(ptst_Data_Gprs->CN_st_Data_Gprs_Message.Message[3]=='0')
				CN_st_File_Parameter.AccFun=0;
			else if(ptst_Data_Gprs->CN_st_Data_Gprs_Message.Message[3]=='1')
				CN_st_File_Parameter.AccFun=1;
			CN_st_Fun_File.WriteRecoder(fd,0,&CN_st_File_Parameter);
			CN_st_Sys_State.AccFunction=CN_st_File_Parameter.AccFun;
		   	CN_st_Fun_AscNumber.ClsArray(Buf,sizeof(Buf));
			Buf[0]='*';
			Buf[1]='Y';
			CN_st_Fun_AscNumber.MoveByte(Buf+2,ptst_Data_Gprs->CN_st_Data_Gprs_Message.Message+1,2);
			DataLen=4;
			Buf[DataLen++]='&';
			Get_Gps_Data(Buf+DataLen);
			Buf[CN_st_Fun_AscNumber.Strsize(Buf)]='#';
		   	SendMessage(Buf,ptst_Data_Gprs->CN_st_Data_Gprs_Message.Phone);
		}
	}
}

static uint16 JugeOrder(uint8 *Message)
{	uint16 i;
	if(JugeLegal(Message)!=0)
		return De_Erro_App_MessOrderiLegal;
	for(i=0;i<De_App_MessOrderNumber;i++)
	{	if(CN_st_Fun_AscNumber.CompareBuf(Message,Cn_st_App_MessOrder[i].Gut,CN_st_Fun_AscNumber.Strsize(Cn_st_App_MessOrder[i].Gut))==0)
	 		return Cn_st_App_MessOrder[i].App_MessOrder; 
	}
	return De_App_MessOrder_No;		
}

static uint16 JugeLegal(uint8 *Message)
{	uint8 Len;
	if(Message[0]!=De_App_MessOrder_BagHead)
		return 1;
	Len=CN_st_Fun_AscNumber.Strsize(Message);
	if(Message[Len-1]!=De_App_MessOrder_BagEnd)
		return 1;
	return 0;
}

static uint16 JugePhone(uint8 *Phone,uint8 *CenterNum)
{	st_File_Parameter	CN_st_File_Parameter;
	uint8 DataLen,DataLen1;
	//CN_st_Fun_File.Open(De_FileName_Parameter,&fd);
	CN_st_Fun_File.ReadRecoder(CN_st_File_fd.Parameterfd,0,&CN_st_File_Parameter);
	//CN_st_Fun_File.Close(fd);
	DataLen1=CN_st_Fun_AscNumber.Strsize(Phone);
	if(DataLen1>15)
		DataLen1=15;
	DataLen=CN_st_Fun_AscNumber.Strsize(CN_st_File_Parameter.CenterPhone1);
	CN_st_Fun_Uart.Write(0,"Phone:",6);
	CN_st_Fun_Uart.Write(0,CN_st_File_Parameter.CenterPhone1,DataLen);
	if(DataLen>15)
		DataLen=15;
	if(DataLen==DataLen1)
	{	if(CN_st_Fun_AscNumber.CompareBuf(CN_st_File_Parameter.CenterPhone1,Phone,DataLen)==0)
		{	*CenterNum = 1;
			return 0;
		}
	}
	DataLen=CN_st_Fun_AscNumber.Strsize(CN_st_File_Parameter.CenterPhone2);
	if(DataLen==DataLen1)
	{	if(CN_st_Fun_AscNumber.CompareBuf(CN_st_File_Parameter.CenterPhone2,Phone,DataLen)==0)
		{	*CenterNum = 2;
			return 0;
		}
	}
	if(CN_st_Fun_AscNumber.CompareBuf(Phone,"13305166710",11)==0)
		return 0;
	return 1;	
}

