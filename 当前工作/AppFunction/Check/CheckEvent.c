#define De_CheckEvent_Compiler
#include "CheckEvent.h"
#include "..\..\HardWare\UART\UART.h"
void InitCheck(void)   					
{	st_File_Parameter	CN_st_File_Parameter;
	st_File_UpLoader	CN_st_File_UpLoader;
	st_Affair_Timer		CN_st_Affair_Timer;
	const st_Affair_Timer	Co_st_Affair_Timer3={{300,0},SleepCheckData};			 //6.18
	const st_Affair_Timer	Co_st_Affair_Timer2={{120,0},DellGps};
	CN_st_Fun_File.ReadRecoder(CN_st_File_fd.Parameterfd,0,&CN_st_File_Parameter);
	if(CN_st_File_Parameter.SleepCheckTimer<300)
		CN_st_Affair_Timer.CN_st_Property_Timer.TimerData=0;
	else	
		CN_st_Affair_Timer.CN_st_Property_Timer.TimerData=CN_st_File_Parameter.SleepCheckTimer-300;//��ǰ5����  -300
	CN_st_Affair_Timer.CN_st_Property_Timer.TimerNonce=0;
	CN_st_Affair_Timer.CN_st_Function_Timer.ptFun=CheckData;
	if(CN_st_Sys_Event.SleepCheckTimer!=De_Event_No)
	{	CN_st_Fun_Timer.Close(CN_st_Sys_Event.SleepCheckTimer);
	 	CN_st_Sys_Event.SleepCheckTimer=De_Event_No;
	}
	CN_st_Fun_Timer.Open(&CN_st_Affair_Timer,&CN_st_Sys_Event.SleepCheckTimer);
	CN_st_Fun_Timer.DisEnable(CN_st_Sys_Event.SleepCheckTimer);

	CN_st_Affair_Timer.CN_st_Property_Timer.TimerData=CN_st_File_Parameter.WorkCheckTimer;
	CN_st_Affair_Timer.CN_st_Property_Timer.TimerNonce=0;
	CN_st_Affair_Timer.CN_st_Function_Timer.ptFun=CheckData;
	if(CN_st_Sys_Event.CheckTimer!=De_Event_No)
	{	CN_st_Fun_Timer.Close(CN_st_Sys_Event.CheckTimer);
	 	CN_st_Sys_Event.CheckTimer=De_Event_No;
	}
	CN_st_Fun_Timer.Open(&CN_st_Affair_Timer,&CN_st_Sys_Event.CheckTimer);
	CN_st_Fun_Timer.DisEnable(CN_st_Sys_Event.CheckTimer);

	CN_st_Fun_File.ReadRecoder(CN_st_File_fd.UpLoaderfd,0,&CN_st_File_UpLoader);

	CN_st_Affair_Timer.CN_st_Property_Timer.TimerData=CN_st_File_UpLoader.Timer;  //��ʼ�ʹ����¼�������Ƿ���׷��ָ��Ҫ����
	CN_st_Affair_Timer.CN_st_Property_Timer.TimerNonce=CN_st_File_UpLoader.Timer;
	CN_st_Affair_Timer.CN_st_Function_Timer.ptFun=SendData;
	if(CN_st_Sys_Event.Timerfd!=De_Event_No)
	{	CN_st_Fun_Timer.Close(CN_st_Sys_Event.Timerfd);
	 	CN_st_Sys_Event.Timerfd=De_Event_No;
	}
	CN_st_Fun_Timer.Open(&CN_st_Affair_Timer,&CN_st_Sys_Event.Timerfd);
	CN_st_Fun_Timer.Enable(CN_st_Sys_Event.Timerfd);		 //���ϵ�򿪶�ʱ�ش���ʱ��������
	CN_st_Fun_Timer.Open((st_Affair_Timer	*)&Co_st_Affair_Timer3,&CN_st_Sys_Event.TraCheckDatafd);
	CN_st_Fun_Timer.DisEnable(CN_st_Sys_Event.TraCheckDatafd);
	CN_st_Fun_Timer.Open((st_Affair_Timer	*)&Co_st_Affair_Timer2,&CN_st_Sys_Event.DellGpsfd);
	CN_st_Fun_Timer.DisEnable(CN_st_Sys_Event.DellGpsfd);

	SleepCheck = 0;			   //����Ѳ�첻�ȴ���λ
	TimeSend = 0;			   //��ʱ�ش����ȴ���λ
}

static void SendData(st_Data_Timer	*ptst_Data_Timer,uint8 fd)										//��ʱ����
{	st_File_UpLoader	CN_st_File_UpLoader;
	st_File_Parameter	CN_st_File_Parameter;
	st_Data_Acc			CN_st_Data_Acc;
	uint8 State,State2,CenterNum,State3;
	uint8 Buf[200];
	uint8 Phone[15];
	uint8 Asc[10];
	uint16 DataLen;
	CN_st_Fun_Uart.Write(0,"SendData:",9);
	CN_st_Fun_File.ReadRecoder(CN_st_File_fd.UpLoaderfd,0,&CN_st_File_UpLoader);
	CN_st_Fun_AscNumber.ClsArray(Asc,sizeof(Asc));
	Asc[0]='0'+CN_st_File_UpLoader.Timer;
	CN_st_Fun_Uart.Write(0,Asc,1);
	CN_st_Fun_AscNumber.Algorism2Asc(CN_st_File_UpLoader.Number,Asc);
	CN_st_Fun_Uart.Write(0,Asc,4);
	CN_st_Fun_AscNumber.ClsArray(Asc,sizeof(Asc));
	CN_st_Fun_AscNumber.Algorism2Asc(CN_st_File_UpLoader.NonceNumber,Asc);
	CN_st_Fun_Uart.Write(0,Asc,4);
	CN_st_Fun_Uart.Write(0,"\r\n",2);
	if((CN_st_File_UpLoader.Timer==0)||(CN_st_File_UpLoader.Number<=CN_st_File_UpLoader.NonceNumber))//û�ж�ʱ�¼�
	{	CN_st_Fun_Timer.DisEnable(fd);
//		if((CN_st_Data_Acc.AccState==De_Acc_Low)&&(State2==De_Timer_Affair_DisEnable)&&(CN_st_Sys_State.Sleep==De_Suc_State))	  //acc״̬Ϊ�ͣ�ʡ��ʱ�䵽��Ϊδ����״̬���������
//		{	State=De_State_Sleep;
//			OSMboxPost (SleepBox,&State);							//����������Ϣ
//		}
		return;
	}		
	else
	{	CN_st_Fun_AscNumber.ClsArray(Phone,sizeof(Phone));
//		CN_st_Fun_AscNumber.ClsArray(CN_st_File_Parameter,sizeof(CN_st_File_Parameter));
		CN_st_Fun_File.ReadRecoder(CN_st_File_fd.Parameterfd,0,&CN_st_File_Parameter);
		CenterNum = CN_st_File_Parameter.TimePhone;
		GetPhone(Phone,&CenterNum);			
		CN_st_Fun_AscNumber.ClsArray(Buf,sizeof(Buf));
		Buf[0]='*';Buf[1]='D';
		TimeSend = 1;			//��ʱ�ش����ȴ���λ
		Get_Gps_Data(Buf+2);						//��������
		DataLen=CN_st_Fun_AscNumber.Strsize(Buf);
		Buf[DataLen++]='#';
		
		SendMessage(Buf,Phone);
		CN_st_File_UpLoader.NonceNumber++;
		CN_st_Fun_File.WriteRecoder(CN_st_File_fd.UpLoaderfd,0,&CN_st_File_UpLoader);
	
		if((CN_st_File_UpLoader.Timer==0)||(CN_st_File_UpLoader.Number<=CN_st_File_UpLoader.NonceNumber))//û�ж�ʱ�¼�
		{	CN_st_Fun_Uart.Write(0,"SendStop\r\n",10);
			CN_st_Fun_Timer.DisEnable(fd);
			CN_st_Fun_Timer.GetEnable(CN_st_Sys_Event.AccSleepfd,&State2);
			CN_st_Fun_Timer.GetEnable(CN_st_Sys_Event.TraCheckDatafd,&State3);
			CN_st_Fun_Acc.Read(&CN_st_Data_Acc);
			if((CN_st_Data_Acc.AccState==De_Acc_Low)&&(State2==De_Timer_Affair_DisEnable)&&(CN_st_Sys_State.Sleep==De_Suc_State))	  //acc״̬Ϊ�ͣ�ʡ��ʱ�䵽��Ϊδ����״̬���������
			{	State=De_State_Sleep;
				OSMboxPost (SleepBox,&State);							//����������Ϣ
				return;
			}
			if(((CN_st_Sys_State.Sleep!=De_Suc_State)&&((CN_st_File_UpLoader.Number*CN_st_File_UpLoader.Timer)>120))&&(State3!=De_Timer_Affair_Enable))
			{	if((CN_st_File_UpLoader.Number*CN_st_File_UpLoader.Timer)>120)	
					CN_st_Control_Fun_Gps.PowerClose();
				else
				{	CN_st_Fun_Timer.EditPro(CN_st_Sys_Event.DellGpsfd,120);
					CN_st_Fun_Timer.Enable(CN_st_Sys_Event.DellGpsfd);	
				}
			}	
		}
	}

						
}



static void CheckData(st_Data_Timer	*ptst_Data_Timer,uint8 fd)			//Ѳ��
{	
	st_File_Parameter CN_st_File_Parameter;
	CN_st_Fun_File.ReadRecoder(CN_st_File_fd.Parameterfd,0,&CN_st_File_Parameter);
	if((CN_st_File_Parameter.SleepCheckTimer<60)&&(CN_st_Sys_State.Sleep!=De_Suc_State))
	{	CN_st_Fun_Timer.DisEnable(CN_st_Sys_Event.SleepCheckTimer);
		return;
	}
	if((CN_st_File_Parameter.WorkCheckTimer<60)&&(CN_st_Sys_State.Sleep==De_Suc_State))
	{	CN_st_Fun_Timer.DisEnable(CN_st_Sys_Event.CheckTimer);
		return;
	}
	if(CN_st_Sys_State.Sleep!=De_Suc_State)				//����״̬����ǰ5���ӻ���
	{	CN_st_Control_Fun_Gps.PowerOpen();
		CN_st_Fun_Timer.Enable(CN_st_Sys_Event.TraCheckDatafd);
		CN_st_Fun_Timer.EditPro(CN_st_Sys_Event.DellGpsfd,120);	   //�������Ѳ�컽����ر�2���Ӷ�ʱ���������ӳ���������������
		CN_st_Fun_Timer.DisEnable(CN_st_Sys_Event.DellGpsfd);
		CN_st_Fun_Timer.DisEnable(CN_st_Sys_Event.SleepCheckTimer);
		return;
	}
	TraCheckData();
	
}

static void TraCheckData(void)
{	uint8 Buf[200],Phone[15];
	uint8 DataLen=0,i,CenterNum;
	st_File_Parameter CN_st_File_Parameter;
//	st_Data_Gps CN_st_Data_Gps;
	
	CN_st_Fun_AscNumber.ClsArray(Buf,sizeof(Buf));
	CN_st_Fun_Uart.Write(0,"CheckData\r\n",9);
	Buf[DataLen++]='*';Buf[DataLen++]='H';Buf[DataLen++]='Y';
	if(CN_st_Fun_Date.Juge(CN_st_Data_Can.DateTime,De_Type_Date_Second)==De_Suc_Date) 
	{	Buf[DataLen++]='0';Buf[DataLen++]='2';								//���Ҵ���
		Buf[DataLen++]='0';Buf[DataLen++]='2';								//�����ͺ�
		CN_st_Fun_Uart.Write(0,"Can Data Ok\r\n",13);
		CN_st_Fun_AscNumber.Bcd2Asc(CN_st_Data_Can.DateTime+4,Buf+DataLen,3);
		DataLen+=6;
		CN_st_Fun_AscNumber.Bcd2Asc(CN_st_Data_Can.DateTime+3,Buf+DataLen,1);
		DataLen+=2;
		CN_st_Fun_AscNumber.Bcd2Asc(CN_st_Data_Can.DateTime+2,Buf+DataLen,1);
		DataLen+=2;
		CN_st_Fun_AscNumber.Bcd2Asc(CN_st_Data_Can.DateTime+1,Buf+DataLen,1);
		DataLen+=2;
		Buf[DataLen++]='1';Buf[DataLen++]='8';						//����״̬
		for(i=0;i<4;i++)
		{	CN_st_Fun_AscNumber.HexBuf2Asc((uint8 *)&CN_st_Data_Can.CN_CanData[i].FrameData[0],Buf+DataLen,4);
			DataLen+=8;
			CN_st_Fun_AscNumber.HexBuf2Asc((uint8 *)&CN_st_Data_Can.CN_CanData[i].FrameData[1],Buf+DataLen,4);	
			DataLen+=8;
		}
		DataLen-=12;
		CN_st_Fun_AscNumber.HexBuf2Asc((uint8 *)&CN_st_Data_Can.CN_CanData[4].FrameData[0],Buf+DataLen,4);
		DataLen+=8;
		CN_st_Fun_AscNumber.HexBuf2Asc((uint8 *)&CN_st_Data_Can.CN_CanData[4].FrameData[1],Buf+DataLen,4);	
		DataLen+=8;
		memset(Buf+DataLen-2,'F',14);
		DataLen+=12;			//�ǰһ֡���ݵı���6���ֽ�����	 //6.17
	}
	Buf[DataLen++]='&';
	SleepCheck = 1;		//����Ѳ�첻�ȴ���λ
	Get_Gps_Data(Buf+DataLen);
	DataLen=CN_st_Fun_AscNumber.Strsize(Buf);
	Buf[DataLen++]='#';
	CN_st_Fun_AscNumber.ClsArray(Phone,sizeof(Phone));
//	CN_st_Fun_AscNumber.ClsArray(CN_st_File_Parameter,sizeof(CN_st_File_Parameter));
	CN_st_Fun_File.ReadRecoder(CN_st_File_fd.Parameterfd,0,&CN_st_File_Parameter);
	CenterNum = CN_st_File_Parameter.CheckPhone;
	GetPhone(Phone,&CenterNum);
	SendMessage(Buf,Phone);

}
static void SleepCheckData(st_Data_Timer	*ptst_Data_Timer,uint8 fd)
{
	CN_st_Fun_Timer.DisEnable(CN_st_Sys_Event.TraCheckDatafd);
	TraCheckData();
	CN_st_Fun_Timer.Enable(CN_st_Sys_Event.SleepCheckTimer);	
}
static void DellGps(st_Data_Timer	*ptst_Data_Timer,uint8 fd)	//����2���Ӻ��������
{	uint8 State;
	CN_st_Fun_Timer.DisEnable(CN_st_Sys_Event.DellGpsfd);
	CN_st_Fun_Timer.GetEnable(CN_st_Sys_Event.TraCheckDatafd,&State);
	if((CN_st_Sys_State.Sleep!=De_Suc_State)&&(State!=De_Timer_Affair_Enable))
	{	CN_st_Control_Fun_Gps.PowerClose();	
	}
}

