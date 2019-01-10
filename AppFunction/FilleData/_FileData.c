#define De_FileData_Compiler
#include "FileData.h"
#include "..\..\HardWare\UART\UART.h"
void CheckFile(void)												//������ݿ�
{	
	CheckFile_Basic();
//	CN_st_Fun_Uart.Write(0,"CheckFile Basic\r\n",17);	
	CheckFile_CanID();
//	CN_st_Fun_Uart.Write(0,"CheckFile CanID\r\n",17);				
	CheckFile_Parameter();
//	CN_st_Fun_Uart.Write(0,"CheckFile Parameter\r\n",21);
	CheckFile_Acc();
//	CN_st_Fun_Uart.Write(0,"CheckFile Acc\r\n",15);
    CheckFile_UpLoader();
//	CN_st_Fun_Uart.Write(0,"CheckFile UpLoader\r\n",20);
	CheckFile_MessageState();
//	CN_st_Fun_Uart.Write(0,"CheckFile MessageState\r\n",24);
 	CheckFile_Message();
//	CN_st_Fun_Uart.Write(0,"CheckFile Message\r\n",19);
	CheckFile_GpsMessage();
//	CN_st_Fun_Uart.Write(0,"CheckFile GpsMessage\r\n",22);
	CN_st_Fun_AscNumber.ClsArray(&CN_st_Sys_State,sizeof(st_Sys_State));
//	CN_st_Fun_Uart.Write(0,"Cls Get Sys State\r\n",19);
	Get_Sys_State();
//	CN_st_Fun_Uart.Write(0,"Get Sys State\r\n",15);
	memset((uint8 *)&CN_st_Sys_Event,0XFF,sizeof(st_Sys_Event));

	FileDataSem=OSSemCreate(1);			 //��ȡGPS������
}
void InitCenPhone(void)
{	st_Gsm_Net_Information	CN_st_Gsm_Net_Information;
	st_File_Parameter CN_st_File_Parameter;
	uint8 DataLen;
	CN_st_Fun_AscNumber.ClsArray(&CN_st_File_Parameter,sizeof(st_File_Parameter));
	CN_st_Fun_File.ReadRecoder(CN_st_File_fd.Parameterfd,0,&CN_st_File_Parameter);
	CN_st_Fun_Gprs.GetPro(&CN_st_Gsm_Net_Information);
	DataLen=CN_st_Fun_AscNumber.Strsize(CN_st_Gsm_Net_Information.CenterNum);
	if(DataLen == 0)
		return;
	CN_st_Fun_AscNumber.MoveByte(CN_st_File_Parameter.CenPhone,CN_st_Gsm_Net_Information.CenterNum,DataLen);
	CN_st_Fun_File.WriteRecoder(CN_st_File_fd.Parameterfd,0,&CN_st_File_Parameter);
}
void BackInit(void)
{ 	//BackBasic();			
	BackCan();		
	BackPareameter();
   	BackUpLoader();
   	BackAccTimer();
	Get_Sys_State();
	CN_st_Sys_State.voltage=De_Suc_State;
}

static void BackBasic(void)
{	st_File_Basic	CN_st_File_Basic;
	CN_st_Fun_AscNumber.ClsArray(&CN_st_File_Basic,sizeof(CN_st_File_Basic));
	CN_st_Fun_AscNumber.MoveByte(CN_st_File_Basic.SoftEdition,"YV1.0",5);
	CN_st_Fun_AscNumber.MoveByte(CN_st_File_Basic.HardEdition,"HV2.2",5);	
	CN_st_Fun_AscNumber.MoveByte(CN_st_File_Basic.MachID,"66666666",8);
	CN_st_Fun_AscNumber.MoveByte(CN_st_File_Basic.MachType,"02",2);
	CN_st_Fun_AscNumber.MoveByte(CN_st_File_Basic.MakeFactory,"02",2);
	CN_st_Fun_File.WriteRecoder(CN_st_File_fd.Basicfd,0,&CN_st_File_Basic);
}

static void BackCan(void)
{	st_File_CanID	CN_st_File_CanID;
	CN_st_Fun_AscNumber.ClsArray(&CN_st_File_CanID,sizeof(st_File_CanID));
	CN_st_File_CanID.CanID[0]=200;
	CN_st_File_CanID.CanID[1]=201;
	CN_st_File_CanID.CanID[2]=202;
	CN_st_File_CanID.CanID[3]=203;
	CN_st_File_CanID.CanID[4]=204;
	CN_st_Fun_File.WriteRecoder(CN_st_File_fd.CanIDfd,0,&CN_st_File_CanID);
}

static void BackPareameter(void)
{	st_File_Parameter CN_st_File_Parameter;
	CN_st_Fun_AscNumber.ClsArray(&CN_st_File_Parameter,sizeof(st_File_Parameter));
	CN_st_File_Parameter.Speed=0xff;												  //Ĭ��һ�����
	CN_st_File_Parameter.SleepTimer=1800;
	CN_st_File_Parameter.WorkCheckTimer=0;
	CN_st_File_Parameter.SleepCheckTimer=0;
	CN_st_File_Parameter.LowVolTimer=5;
	CN_st_File_Parameter.HighVolTimer=10;
	CN_st_File_Parameter.VoAlarmState = De_VoAlarm_No;
	CN_st_Fun_AscNumber.MoveByte(CN_st_File_Parameter.CenterPhone1,"106380005668",12);
	CN_st_Fun_AscNumber.MoveByte(CN_st_File_Parameter.CenterPhone2,"13675124434",11);
	CN_st_Fun_AscNumber.MoveByte(CN_st_File_Parameter.CenPhone,"13800250500",11);
	CN_st_File_Parameter.CheckPhone=1;
	CN_st_File_Parameter.TimePhone=1;
	CN_st_File_Parameter.EnableChar[0]=0x5a;CN_st_File_Parameter.EnableChar[1]=0x5b;
	CN_st_File_Parameter.EnableChar[2]=0x5c;
	CN_st_File_Parameter.CanId=205;
	CN_st_File_Parameter.CanSendTimer=1;
	CN_st_File_Parameter.AccFun=0;
	CN_st_File_Parameter.ControlEnable=0;
	CN_st_File_Parameter.HighV=9000;
	CN_st_File_Parameter.HighL=2000;
	CN_st_Fun_File.WriteRecoder(CN_st_File_fd.Parameterfd,0,&CN_st_File_Parameter);
}

static void BackUpLoader(void)
{  	st_File_UpLoader CN_st_File_UpLoader;
	CN_st_File_UpLoader.Timer=0;														//Ĭ�϶�ʱ�ش�����
	CN_st_File_UpLoader.Number=0;
	CN_st_File_UpLoader.NonceNumber=0;
	CN_st_Fun_File.WriteRecoder(CN_st_File_fd.UpLoaderfd,0,&CN_st_File_UpLoader);
}

static void BackAccTimer(void)
{ 	uint32 			AccTimer;
	AccTimer=0;
	CN_st_Fun_File.WriteRecoder(CN_st_File_fd.AccTimerfd,0,&AccTimer);
}




void Get_Gps_Data(uint8 *Buf)										//��ȡGPS����
{	uint8 i,State2,err;	
//	uint16 Result;
	st_Data_Gps		CN_st_Data_Gps;
	OSSemPend(FileDataSem, 0, &err);
	if(CN_st_Sys_State.Sleep!=De_Suc_State)
		CN_st_Control_Fun_Gps.PowerOpen();
	for(i=1;i<240;OSTimeDly(100),i++)
	{	CN_st_Control_Fun_Gps.Read(&CN_st_Data_Gps);
		if(CN_st_Data_Gps.CN_st_Gps_Data_GPRMC.LocationTrue==De_Gps_Location_True)
		{	CN_st_Fun_Uart.Write(0,"Gps Open\r\n",10);
			break;
		}
		else if((CN_st_Sys_State.Sleep==De_Suc_State)||(SleepCheck)||(TimeSend))
		{	i=240;
			break ;
		}
		else
			continue;	
	}
	SleepCheck = 0;			   //����Ѳ�첻�ȴ���λ		 ʱ�������ʱ������ʵ��
	TimeSend = 0;			   //��ʱ�ش����ȴ���λ
	if(i>=240)
	{	CN_st_Fun_AscNumber.ClsArray(&CN_st_Data_Gps,sizeof(CN_st_Data_Gps));
		CN_st_Fun_File.ReadRecoder(CN_st_File_fd.GpsMessagefd,0,&CN_st_Data_Gps);
		CN_st_Data_Gps.CN_st_Gps_Data_GPRMC.LocationTrue=De_Gps_Location_Flase;
		CN_st_Fun_RTC.Read(CN_st_Data_Gps.CN_st_Gps_Data_GPRMC.DateTime);
	}		
	CN_st_Fun_Uart.Write(0,"Gps finish\r\n",12);
//	CN_st_Control_Fun_Gps.Read(&CN_st_Data_Gps);
	Trans_Gps(&CN_st_Data_Gps,&CN_st_Sys_State,Buf);
	CN_st_Fun_Timer.GetEnable(CN_st_Sys_Event.Timerfd,&State2);
	if((State2 == De_Timer_Affair_DisEnable)&&(CN_st_Sys_State.Sleep!=De_Suc_State))
	{	CN_st_Fun_Timer.EditPro(CN_st_Sys_Event.DellGpsfd,120);
		CN_st_Fun_Timer.Enable(CN_st_Sys_Event.DellGpsfd);	
	}
	OSSemPost(FileDataSem);
}
void Get_Gps_DataHand(uint8 *Buf)
{ 	st_Data_Gps		CN_st_Data_Gps;
	CN_st_Control_Fun_Gps.Read(&CN_st_Data_Gps);
	Trans_Gps_Hand(&CN_st_Data_Gps,&CN_st_Sys_State,Buf);
}




void GetPhone(uint8 *Phone,uint8 *CenterNum)
{	st_File_Parameter	CN_st_File_Parameter;
	uint8 DataLen;
	CN_st_Fun_AscNumber.ClsArray(Phone,15);
	CN_st_Fun_File.ReadRecoder(CN_st_File_fd.Parameterfd,0,&CN_st_File_Parameter);
	if((CN_st_File_Parameter.CenterPhone1[0]==0)&&(CN_st_File_Parameter.CenterPhone2[0]==0))
		CN_st_Fun_AscNumber.MoveByte(Phone,"13305166710",11);
	else
	{	if(*CenterNum == 1)
		{
			DataLen=CN_st_Fun_AscNumber.Strsize(CN_st_File_Parameter.CenterPhone1);
			if(DataLen==0)
			{	DataLen=CN_st_Fun_AscNumber.Strsize(CN_st_File_Parameter.CenterPhone2);
				if(DataLen>15)
					DataLen=15;
				CN_st_Fun_AscNumber.MoveByte(Phone,CN_st_File_Parameter.CenterPhone2,DataLen);
			}
			else
			{	if(DataLen>15)
					DataLen=15;
				CN_st_Fun_AscNumber.MoveByte(Phone,CN_st_File_Parameter.CenterPhone1,DataLen);
			}
		}
		else if(*CenterNum == 2) 
		{	DataLen=CN_st_Fun_AscNumber.Strsize(CN_st_File_Parameter.CenterPhone2);
			if(DataLen==0)
			{	DataLen=CN_st_Fun_AscNumber.Strsize(CN_st_File_Parameter.CenterPhone1);
				if(DataLen>15)
					DataLen=15;
				CN_st_Fun_AscNumber.MoveByte(Phone,CN_st_File_Parameter.CenterPhone1,DataLen);
			}
			else
			{	if(DataLen>15)
					DataLen=15;
				CN_st_Fun_AscNumber.MoveByte(Phone,CN_st_File_Parameter.CenterPhone2,DataLen);
			}
		}
		else
			CN_st_Fun_AscNumber.MoveByte(Phone,"13305166710",11);		
	}		
}

void SendMessage(uint8 *Buf,uint8 *Phone)	 						//���Ͷ���Ϣ
{	st_File_Message	CN_st_File_Message;
	st_Data_Timer	CN_st_Data_Timer;
	uint8 DataLen;
	CN_st_Fun_AscNumber.ClsArray(&CN_st_File_Message,sizeof(st_File_Message));
	DataLen=CN_st_Fun_AscNumber.Strsize(Buf);
	if(DataLen>=200)
		DataLen=200;
	CN_st_Fun_AscNumber.MoveByte(CN_st_File_Message.Message,Buf,DataLen);
	CN_st_Fun_Uart.Write(0,Buf,DataLen);
	CN_st_Fun_Uart.Write(0,"\r\n",2);
   	DataLen=CN_st_Fun_AscNumber.Strsize(Phone);
	if(DataLen>15)	
		DataLen=15;
	CN_st_Fun_Uart.Write(0,Phone,DataLen);
	CN_st_Fun_Uart.Write(0,"\r\n",2);
	CN_st_Fun_AscNumber.MoveByte(CN_st_File_Message.Phone,Phone,DataLen);
	CN_st_Fun_Timer.Read(&CN_st_Data_Timer);
	CN_st_Fun_AscNumber.MoveByte(CN_st_File_Message.DateTime,CN_st_Data_Timer.DateTime,7);
	CN_st_Fun_File.WriteRecoder(CN_st_File_fd.Messagefd,0,&CN_st_File_Message);
	CN_st_Fun_File.ReadHeadTail(CN_st_File_fd.Messagefd,&MessageTail,De_rwFile_Point_Tail);
}


static void Get_Sys_State(void)
{	
	st_File_Parameter	*ptst_File_Parameter;
	st_File_CanID		*ptst_File_CanID;
	//st_Data_Gps			CN_st_Data_Gps;	
	ptst_File_Parameter=(st_File_Parameter	*)CN_X_BUF;
	ptst_File_CanID=(st_File_CanID	*)CN_X_BUF;
	CN_st_Fun_AscNumber.ClsArray(&CN_st_Sys_State,sizeof(st_Sys_State));
	CN_st_Fun_File.ReadRecoder(CN_st_File_fd.Parameterfd,0,ptst_File_Parameter);
//	CN_st_Fun_Uart.Write(0,"Read Parameter\r\n",16);
	CN_st_Sys_State.AccFunction=ptst_File_Parameter->AccFun;
	CN_st_Sys_State.Control=ptst_File_Parameter->ControlEnable;
	if(CN_st_Sys_State.Control==0)
	{	De_IO_unLock;

	}
	else 
	{	De_IO_Lock;
	
	}
//	CN_st_Fun_Uart.Write(0,"IO Lock\r\n",9);	
	CN_st_Fun_File.ReadRecoder(CN_st_File_fd.CanIDfd,0,ptst_File_CanID);
//	CN_st_Fun_Uart.Write(0,"Read CanID\r\n",12);
	CN_st_Fun_AscNumber.MoveByte(CN_st_Data_Can.CanID,ptst_File_CanID->CanID,sizeof(uint16)*De_Can_Data_MaxID);
//	CN_st_Fun_Uart.Write(0,"Move CanID\r\n",12);
	CN_st_Sys_State.voltage=De_State_Voltage_Bad;
	CN_st_Sys_State.GpsState=De_Erro_State_GpsNosem;
	CN_st_Fun_Uart.Write(0,"Get Sys State Finish\r\n",22);
}


static void CheckFile_GpsMessage(void)
{	uint16 Erro;
	Erro=CN_st_Fun_File.Open(De_FileName_GpsMessage,&CN_st_File_fd.GpsMessagefd);
	if(Erro==De_Erro_File_NoFile)										//û��CAN���ַ�
	{	CN_st_Fun_File.CreateRecoder(De_FileName_GpsMessage,sizeof(st_Data_Gps),500,De_File_Property_Cycle);
		CN_st_Fun_File.Open(De_FileName_GpsMessage,&CN_st_File_fd.GpsMessagefd);
	}	
	
}


/*++++++++++++++++++++++++++++++++++�ļ�������Ϣ��+++++++++++++++++++++++++++++++++++++++++++++++*/
/*	�ֶ�����			����				д�뷽ʽ				����	��ע			*/
		
/*	SoftEdition[8]:		����汾			����д��:YV1.0			ASC   ���㲹'\0'
	HardEdition[8]:		Ӳ���汾			����д��:HV1.0			ASC   ���㲹'\0'
	MachID[16]:			�������			12λ��������			ASC   ���㲹'\0'
	MachType[2]:		��������			����д��:02				ASC
	MakeFactory[2]:		��������			����д��:02				ASC			
*/
static void CheckFile_Basic(void)
{	uint16 Erro;
//	st_File_Basic	CN_st_File_Basic;
	Erro=CN_st_Fun_File.Open(De_FileName_Basic,&CN_st_File_fd.Basicfd);
	if(Erro==De_Erro_File_NoFile)									//��һ��ʹ��,Ҫ�����ļ�
	{	CN_st_Fun_File.CreateRecoder(De_FileName_Basic,sizeof(st_File_Basic),100,De_File_Property_Cycle);	
		CN_st_Fun_File.Open(De_FileName_Basic,&CN_st_File_fd.Basicfd);
		BackBasic();
	}
	if(CN_st_Fun_File.GetJlNum(CN_st_File_fd.Basicfd)==0)
		BackBasic();	
}

static void CheckFile_CanID(void)
{	uint16 Erro;
//	st_File_CanID	CN_st_File_CanID;
	Erro=CN_st_Fun_File.Open(De_FileName_CanID,&CN_st_File_fd.CanIDfd);
	if(Erro==De_Erro_File_NoFile)										//û��CAN���ַ�
	{	CN_st_Fun_File.CreateRecoder(De_FileName_CanID,sizeof(st_File_CanID),2,De_File_Property_Cycle);
		CN_st_Fun_File.Open(De_FileName_CanID,&CN_st_File_fd.CanIDfd);
		BackCan();
	}
	if(CN_st_Fun_File.GetJlNum(CN_st_File_fd.CanIDfd)==0)
		BackCan();	
	
}
/*++++++++++++++++++++++++++++++++++����������++++++++++++++++++++++++++++++++++++++++++++++++++*/
/*	�ֶ�����			����				д�뷽ʽ				����	��ע			*/
/*	Speed:				�ٶ�				Ĭ��Ϊ��50				HEX32	��λ:��
	SleepTimer��		����ʱ��			Ĭ��Ϊ��120				HEX32	��λ:S
	SleepCheckTimer:	���ߺ�Ѳ��ʱ��		Ĭ��Ϊ: 3600			HEX32	��λ:S
	WorkCheckTimer:		����Ѳ��ʱ��		Ĭ��Ϊ: 1200			HEX32	��λ:S
	CanId:				����CANID			Ĭ��Ϊ��205				HEX16			 			
	AccFun:				ACC����				Ĭ��Ϊ: 0				HEX8    0:�� 1:�ر�
	CenterPhone1[15]	����1�绰����		Ĭ��Ϊ��13305166710		ASC     ���㲹'\0'
    CenterPhone2[15]	����2�绰���� 		Ĭ��Ϊ����				ASC     ���㲹'\0'
	ControlEnable		�Ƿ����			Ĭ��Ϊ��������			HEX8		
*/
static void CheckFile_Parameter(void)
{//	st_File_Parameter	CN_st_File_Parameter;
//	uint8 asc[4];
	uint16 Erro;
	Erro=CN_st_Fun_File.Open(De_FileName_Parameter,&CN_st_File_fd.Parameterfd);
	if(Erro==De_Erro_File_NoFile)
	{	CN_st_Fun_File.CreateRecoder(De_FileName_Parameter,sizeof(st_File_Parameter),50,De_File_Property_Cycle);
		CN_st_Fun_File.Open(De_FileName_Parameter,&CN_st_File_fd.Parameterfd);	
		BackPareameter();
	}
	if(CN_st_Fun_File.GetJlNum(CN_st_File_fd.Parameterfd)==0)
		BackPareameter();		
}
/*+++++++++++++++++++++++++++++++++++Acc ʱ��ͳ��+++++++++++++++++++++++++++++++++++++++++++++++*/	
/*	AccTimer			���ۼƹ���ʱ��		Ĭ��Ϊ:0				HEX32	��λ:S
*/
static void CheckFile_Acc(void)
{//	uint32 AccTimer;
	uint16 Erro;
	Erro=CN_st_Fun_File.Open(De_FileName_AccTimer,&CN_st_File_fd.AccTimerfd);
	if(Erro==De_Erro_File_NoFile)
	{	CN_st_Fun_File.CreateRecoder(De_FileName_AccTimer,sizeof(uint32),50,De_File_Property_Cycle);
		CN_st_Fun_File.Open(De_FileName_AccTimer,&CN_st_File_fd.AccTimerfd);	
		BackAccTimer();
	}
	if(CN_st_Fun_File.GetJlNum(CN_st_File_fd.AccTimerfd)==0)  
		BackAccTimer();	
}


static void CheckFile_UpLoader(void)
{	//st_File_UpLoader	CN_st_File_UpLoader;
	uint16 Erro;
	Erro=CN_st_Fun_File.Open(De_FileName_TimerUpLoade,&CN_st_File_fd.UpLoaderfd);
	if(Erro==De_Erro_File_NoFile)
	{	CN_st_Fun_File.CreateRecoder(De_FileName_TimerUpLoade,sizeof(st_File_UpLoader),1000,De_File_Property_Cycle);
		CN_st_Fun_File.Open(De_FileName_TimerUpLoade,&CN_st_File_fd.UpLoaderfd);	
		BackUpLoader();
	}
   	if(CN_st_Fun_File.GetJlNum(CN_st_File_fd.UpLoaderfd)==0)  
		BackUpLoader();
}

static void CheckFile_Message(void)						//����Ϣ
{	st_Data_FileUse	CN_st_Data_FileUse;
	uint16 Erro;
	Erro=CN_st_Fun_File.Open(De_FileName_Message,&CN_st_File_fd.Messagefd);
	if(Erro==De_Erro_File_NoFile)
	{	CN_st_Fun_File.CreateRecoder(De_FileName_Message,sizeof(st_File_Message),2000,De_File_Property_Cycle);
		CN_st_Fun_File.Open(De_FileName_Message,&CN_st_File_fd.Messagefd);
	}
	CN_st_Fun_File.ReadHeadTail(CN_st_File_fd.Messagefd,&MessageTail,De_rwFile_Point_Tail);
	CN_st_Fun_File.ReadPor(CN_st_File_fd.Messagefd,&CN_st_Data_FileUse);
	MessageNumber=CN_st_Data_FileUse.RecoderNumber;
}

static void CheckFile_MessageState(void)
{	uint16 Erro;
	
	Erro=CN_st_Fun_File.Open(De_FileName_MessageSend,&CN_st_File_fd.MessageSend);
	if(Erro==De_Erro_File_NoFile)
	{	CN_st_Fun_File.CreateRecoder(De_FileName_MessageSend,2,1000,De_File_Property_Cycle);
		CN_st_Fun_File.Open(De_FileName_MessageSend,&CN_st_File_fd.MessageSend);
	}
	if(CN_st_Fun_File.GetJlNum(CN_st_File_fd.MessageSend)==0)
		MessageSendSpace=0;
	else
		CN_st_Fun_File.ReadRecoder(CN_st_File_fd.MessageSend,0,&MessageSendSpace);
						
}

















 

