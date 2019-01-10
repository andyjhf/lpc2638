/*===========================================DisPlay Agreen===================================================*/
#define De_DisPlayOper_Compiler
#include "DisPlayOper.h"
static void Init(void)
{	CN_st_Fun_Timer.Open((st_Affair_Timer	*)&CN_Ba_Display,&DisTimerfd);
   	CN_st_Fun_Timer.DisEnable(DisTimerfd);
}
static void GetData(void *Data,uint8 *DateTimer)	
{	st_Display_Agree	*ptst_Display_Agree;
	uint8 i;
	ptst_Display_Agree=Data;
	for(i=0;i<sizeof(CN_Ba_st_DispLay_Oper_Fun)/sizeof(st_DispLay_Oper_Fun);i++)
	{ 	if(ptst_Display_Agree->ID!=CN_Ba_st_DispLay_Oper_Fun[i].ID)
			continue;
		CN_Ba_st_DispLay_Oper_Fun[i].ptFun(ptst_Display_Agree->AgreeData,ptst_Display_Agree->ID);
	}
}

static void Order_Phone(void *Data,uint8 ID)
{	st_Display_Agree_Phone	*ptst_Display_Agree_Phone;
	st_Data_Gprs_Call	CN_st_Data_Gprs_Call;
	uint8 PhoneState;
	ptst_Display_Agree_Phone=Data;
	if(ptst_Display_Agree_Phone->Type==0)				//拨打电话
	{	CN_st_Fun_Gprs.GetPhoneState(&CN_st_Data_Gprs_Call);
		if(CN_st_Data_Gprs_Call.Mod!=De_GprsHard_CallType_NoCall)
		{	Answer(ID,De_Erro_Display);			//应答失败
			return ;
		}
		if(CN_st_Fun_Gprs.SendPhone(ptst_Display_Agree_Phone->Phone,&PhoneState)!=De_Suc_Gprs)
		{	Answer(ID,De_Erro_Display);			//应答失败
			return ;
		}
		Answer(ID,De_Suc_Display);				//应答成功							
	}
	else if(ptst_Display_Agree_Phone->Type==2)	 		//接听电话
	{	CN_st_Fun_Gprs.GetPhoneState(&CN_st_Data_Gprs_Call);
		if(CN_st_Data_Gprs_Call.Mod!=De_GprsHard_CallType_Passive)
		{	Answer(ID,De_Erro_Display);			//应答失败
			return ;
		}
		if(CN_st_Fun_Gprs.AgreePhone()!=De_Suc_Gprs)
		{	Answer(ID,De_Erro_Display);			//应答失败
			return ;
		}
		Answer(De_Display_Device_Order_Phone,De_Suc_Display);				//应答成功
	}
	else if(ptst_Display_Agree_Phone->Type==4)	   		//拨打分机号码
	{	CN_st_Fun_Gprs.GetPhoneState(&CN_st_Data_Gprs_Call);
		if(CN_st_Data_Gprs_Call.Mod!=De_GprsHard_CallType_Initiative)
		{	Answer(ID,De_Erro_Display);			//应答失败
			return ;
		}			//应答失败
		if(CN_st_Fun_Gprs.SendPhone(ptst_Display_Agree_Phone->Phone,&PhoneState)!=De_Suc_Gprs)
		{	Answer(ID,De_Erro_Display);			//应答失败
			return ;
		}			
		Answer(ID,De_Suc_Display);				//应答成功
	
	}
	else if(ptst_Display_Agree_Phone->Type==3)			//挂断电话
	{	CN_st_Fun_Gprs.CloseCall();
		Answer(ID,De_Suc_Display);				//应答成功
	}	
}
static void SeePar(void *Data,uint8 ID)
{	union
	{	uint8 *Vauint8;
		uint16 *Vauint16;
		int16 *Vaint16;
		uint32 *Vauint32;
		void *Buf;
	}CN_st_VaTran;
	union
	{	uint8 *Vauint8;
		uint16 *Vauint16;
		int16 *Vaint16;
		uint32 *Vauint32;
		void *Buf;
	}CN_st_VaTran1;
	st_Display_Par	CN_st_Display_Par;
	st_Display_Send		CN_st_Display_Send;
	uint8 fd;
	union 
	{	st_Parameter_Table CN_st_Parameter_Table;
		st_HardWare_SeeTCPData	CN_st_HardWare_SeeTCPData;
	}un;
	uint8 *SeePar;
	uint8 i;
	SeePar=Data;
	CN_st_Display_Send.SendOrAgree=De_Sensor_Display_Send;
	CN_st_Display_Send.ID=ID;
	CN_st_Display_Send.SendData=&CN_st_Display_Par;
	for(i=0;i<sizeof(((st_Display_Par	*)(NULL))->Set);i++)
	{	CN_st_Display_Par.Set[i]=0;
		if(SeePar[i]==0)
			continue;
		CN_st_Display_Par.Set[i]=1;
		CN_st_VaTran.Buf=(void *)((uint32 )&CN_st_Display_Par.CN_st_Display_Par_Cut+
		(uint32 )CN_st_Display_Par_Set[i].Point);				
		if(CN_Ba_st_SeePar_Data[i].fd==NULL) 				//当不能从数据库中取数据时
		{	if(i==11)
			{	if(CN_st_Fun_Gprs.GetIPState(NULL,&un.CN_st_HardWare_SeeTCPData)!=De_Suc_Gprs)
				{	SeePar[i]=2;
					continue;
				}
				if(un.CN_st_HardWare_SeeTCPData.State!=De_GprsHard_InitTcp_Over)
				{ 	SeePar[i]=2;
					continue;
				}	
			   	*CN_st_VaTran.Vauint32=un.CN_st_HardWare_SeeTCPData.FristDNS;
			}
			else if(i==15)			
			{	if(CN_st_Fun_Gprs.GetIPState(NULL,&un.CN_st_HardWare_SeeTCPData)!=De_Suc_Gprs)
				{	SeePar[i]=2;
					continue;
				}
				if(un.CN_st_HardWare_SeeTCPData.State!=De_GprsHard_InitTcp_Over)
				{ 	SeePar[i]=2;
					continue;
				}	
				*CN_st_VaTran.Vauint32=un.CN_st_HardWare_SeeTCPData.IP;
			}
			else if(i==16)
			{	if(GetCentrIP(CN_st_VaTran.Vauint32)!=De_Suc_DisplayOpe)
				{ 	SeePar[i]=2;
					continue;
				}		
			}
			else if(i==17)
				*CN_st_VaTran.Vauint8=2;
			continue;
		}
		CN_st_VaTran1.Buf=(void *)((uint32 )&un.CN_st_Parameter_Table+(uint32 )CN_Ba_st_SeePar_Data[i].Dev);
		CN_st_Fun_File.ReadRecoder(*CN_Ba_st_SeePar_Data[i].fd,0,&un.CN_st_Parameter_Table);
		if(CN_st_Display_Par_Set[i].Type==De_Display_Par_Type_Asc)
			CN_st_Fun_AscNumber.MoveByte(CN_st_VaTran.Buf,CN_st_VaTran1.Buf,CN_st_Display_Par_Set[i].SizeofPoint);
		else if((CN_st_Display_Par_Set[i].Type==De_Display_Par_Type_IP)||(CN_st_Display_Par_Set[i].Type==De_Display_Par_Type_uint32))
			*CN_st_VaTran.Vauint32=*CN_st_VaTran.Vauint32;
		else if(CN_st_Display_Par_Set[i].Type==De_Display_Par_Type_uint8)
			*CN_st_VaTran.Vauint8=*CN_st_VaTran.Vauint8;
		else if(CN_st_Display_Par_Set[i].Type==De_Display_Par_Type_uint16)
			*CN_st_VaTran.Vauint16=*CN_st_VaTran.Vauint16;
		else if(CN_st_Display_Par_Set[i].Type==De_Display_Par_Type_int16)
			*CN_st_VaTran.Vaint16=*CN_st_VaTran.Vaint16;
	}
	if(CN_st_Fun_Sensor.GetPar2ID(De_Sensor_WordPar_Display,&fd)!=De_Suc_Sensor)
		return ;
	CN_st_Fun_Sensor.Read(fd,&CN_st_Display_Send,NULL);					
}

static void SetPar(void *Data,uint8 ID)
{	union
	{	uint8 *Vauint8;
		uint16 *Vauint16;
		int16 *Vaint16;
		uint32 *Vauint32;
		void *Buf;
	}CN_st_VaTran;
	union
	{	uint8 *Vauint8;
		uint16 *Vauint16;
		int16 *Vaint16;
		uint32 *Vauint32;
		void *Buf;
	}CN_st_VaTran1;
	st_Display_Par	CN_st_Display_Par;
	union 
	{	st_Parameter_Table CN_st_Parameter_Table;
		st_HardWare_SeeTCPData	CN_st_HardWare_SeeTCPData;
	}un;
	uint8 *SeePar;
	uint8 i;
	SeePar=Data;
	for(i=0;i<sizeof(((st_Display_Par	*)(NULL))->Set);i++)
	{	CN_st_Display_Par.Set[i]=0;
		if(SeePar[i]==0)
			continue;
		if(CN_Ba_st_SeePar_Data[i].fd==NULL) 
			continue;
		CN_st_Display_Par.Set[i]=1;
		CN_st_VaTran.Buf=(void *)((uint32 )&CN_st_Display_Par.CN_st_Display_Par_Cut+
			(uint32 )CN_st_Display_Par_Set[i].Point);				
		CN_st_VaTran1.Buf=(void *)((uint32 )&un.CN_st_Parameter_Table+
		(uint32 )CN_Ba_st_SeePar_Data[i].Dev);
		CN_st_Fun_File.ReadRecoder(*CN_Ba_st_SeePar_Data[i].fd,0,&un.CN_st_Parameter_Table);
		if(CN_st_Display_Par_Set[i].Type==De_Display_Par_Type_Asc)
			CN_st_Fun_AscNumber.MoveByte(CN_st_VaTran.Buf,CN_st_VaTran1.Buf,CN_st_Display_Par_Set[i].SizeofPoint);
		else if((CN_st_Display_Par_Set[i].Type==De_Display_Par_Type_IP)||(CN_st_Display_Par_Set[i].Type==De_Display_Par_Type_uint32))
			*CN_st_VaTran.Vauint32=*CN_st_VaTran.Vauint32;
		else if(CN_st_Display_Par_Set[i].Type==De_Display_Par_Type_uint8)
			*CN_st_VaTran.Vauint8=*CN_st_VaTran.Vauint8;
		else if(CN_st_Display_Par_Set[i].Type==De_Display_Par_Type_uint16)
			*CN_st_VaTran.Vauint16=*CN_st_VaTran.Vauint16;
		else if(CN_st_Display_Par_Set[i].Type==De_Display_Par_Type_int16)
			*CN_st_VaTran.Vaint16=*CN_st_VaTran.Vaint16;
		CN_st_Fun_File.WriteRecoder(*CN_Ba_st_SeePar_Data[i].fd,0,&un.CN_st_Parameter_Table);
	}
	Answer(ID,De_Suc_Display);		
}
static void Log(void *Data,uint8 ID)	 				//登录
{	st_Display_Send		CN_st_Display_Send;
	uint8 fd;
	//Answer(ID,De_Suc_Display);
	CN_st_Display_Send.SendOrAgree=De_Sensor_Display_Send;	
	CN_st_Display_Send.ID=De_Display_Host_Order_InitStart;
	if(CN_st_Fun_Sensor.GetPar2ID(De_Sensor_WordPar_Display,&fd)!=De_Suc_Sensor)
		return ;
	while(CN_st_Fun_Sensor.Read(fd,&CN_st_Display_Send,NULL)!=De_Suc_Sensor);
	CN_st_Display_Send.SendOrAgree=De_Sensor_Display_Send;	
	CN_st_Display_Send.ID=De_Display_Host_Order_InitOver;
	while(CN_st_Fun_Sensor.Read(fd,&CN_st_Display_Send,NULL)!=De_Suc_Sensor);

	CN_st_Fun_Timer.Enable(DisTimerfd);		
}

static void Voic(void *Data,uint8 ID)
{	st_Display_Agree_Voic	*ptst_Display_Agree_Voic;
	ptst_Display_Agree_Voic=Data;
	if(CN_st_Fun_Gprs.SetVolume(ptst_Display_Agree_Voic->VolSize)==De_Suc_Gprs)	
		Answer(ID,De_Suc_Display);
	else
		Answer(ID,De_Erro_Display);						
}

static void Answer(uint8 ID,uint16 Result)
{	st_Display_Send		CN_st_Display_Send;
	uint8 fd;
	st_Display_Order_Answer	CN_st_Display_Order_Answer;
	CN_st_Display_Send.SendOrAgree=De_Sensor_Display_Send;	
	CN_st_Display_Send.ID=De_Display_Host_Order_Answer;
   	CN_st_Display_Send.SendData=&CN_st_Display_Order_Answer;
	CN_st_Display_Order_Answer.Result=Result;
	CN_st_Display_Order_Answer.AnswerID=ID;
	if(CN_st_Fun_Sensor.GetPar2ID(De_Sensor_WordPar_Display,&fd)!=De_Suc_Sensor)
		return ;
	CN_st_Fun_Sensor.Read(fd,&CN_st_Display_Send,NULL);
}

static void LCDRef(st_Data_Timer	*ptst_Data_Timer,uint8 fd) 			//5秒钟刷新界面
{	st_Display_Order_SysInfor	CN_st_Display_Order_SysInfor;
	st_File_GreenPar	CN_st_File_GreenPar;
	st_Sensor_State		CN_st_Sensor_State;
	st_Display_Send		CN_st_Display_Send;
	st_Gsm_Net_Information	CN_st_Gsm_Net_Information;
	//uint8 fd;	
	CN_st_Fun_File.ReadRecoder(CN_st_File_fd.GreenParfd,0,&CN_st_File_GreenPar);
	CN_st_Display_Order_SysInfor.Integral=CN_st_File_GreenPar.Integral;
	CN_st_Fun_AscNumber.MoveByte(CN_st_Display_Order_SysInfor.DateTime,ptst_Data_Timer->DateTime,
	sizeof(CN_st_Display_Order_SysInfor.DateTime));
	if(CN_st_Fun_Sensor.GetPar2ID(De_Sensor_WordPar_Display,&fd)!=De_Suc_Sensor)
		CN_st_Display_Order_SysInfor.GpsState=De_st_Display_Order_SysInfor_Gps_Erro1;
	else
	{	CN_st_Fun_Sensor.GetState(&CN_st_Sensor_State,fd);
		if(CN_st_Sensor_State.Work!=De_Suc_Sensor)
			CN_st_Display_Order_SysInfor.GpsState=De_st_Display_Order_SysInfor_Gps_Erro1;
		else if(CN_st_Sensor_State.Dly!=De_Suc_Sensor)
			CN_st_Display_Order_SysInfor.GpsState=De_st_Display_Order_SysInfor_Gps_Erro2;			
		else
			CN_st_Display_Order_SysInfor.GpsState=De_st_Display_Order_SysInfor_Gps_Suc;
	}
	CN_st_Display_Order_SysInfor.VidState=1;
	if(LogFlag==De_No_Log)
		CN_st_Display_Order_SysInfor.ContrState=0;
	else if(LogFlag==De_LogInt)
		CN_st_Display_Order_SysInfor.ContrState=1;
	else
		CN_st_Display_Order_SysInfor.ContrState=2;
	CN_st_Fun_Gprs.GetSysState(&CN_st_Gsm_Net_Information);
	CN_st_Display_Order_SysInfor.GprsSem=CN_st_Gsm_Net_Information.Csq;
	CN_st_Display_Order_SysInfor.Carrier=CN_st_Gsm_Net_Information.Yys;
	CN_st_Display_Order_SysInfor.CarState=0;
	CN_st_Display_Order_SysInfor.ExigenceState=App_CN_st_WorkFlow_Table.CN_st_AgreeOn_Send_Basic.State[De_Orientation_State_Help];
	CN_st_Display_Order_SysInfor.WaringPci=0;
	CN_st_Display_Order_SysInfor.CarSpeed=App_CN_st_WorkFlow_Table.CN_st_AgreeOn_Send_Basic.CN_st_Data_Gps
	.CN_st_Gps_Data_GPRMC.Speed;
	CN_st_Display_Order_SysInfor.StarNumber=App_CN_st_WorkFlow_Table.CN_st_AgreeOn_Send_Basic.CN_st_Data_Gps
	.CN_st_Gps_Data_GPGGA.StarNumber;
	CN_st_Display_Order_SysInfor.TallyState=1;
	if(App_CN_st_WorkFlow_Table.CN_st_AgreeOn_Send_Basic.State[De_Orientation_State_Low]!=De_AgreeOn_State_Erro)
		CN_st_Display_Order_SysInfor.VolState=0;
	else
		CN_st_Display_Order_SysInfor.VolState=1;
	if(CN_st_Fun_Sensor.GetPar2ID(De_Sensor_WordPar_Display,&fd)!=De_Suc_Sensor)
	{	App_CN_st_WorkFlow_Table.CN_st_AgreeOn_Send_Basic.State[De_Orientation_State_LCD]=De_AgreeOn_State_Erro;
		return ;
	}
	CN_st_Display_Send.SendOrAgree=De_Sensor_Display_Send;
	CN_st_Display_Send.ID=De_Display_Host_Order_SysInfor;
	CN_st_Display_Send.SendData=&CN_st_Display_Order_SysInfor;
	if(CN_st_Fun_Sensor.Read(fd,&CN_st_Display_Send,NULL)!=De_Suc_Sensor)
	{	App_CN_st_WorkFlow_Table.CN_st_AgreeOn_Send_Basic.State[De_Orientation_State_LCD]=De_AgreeOn_State_Erro;
		return ;
	}
	App_CN_st_WorkFlow_Table.CN_st_AgreeOn_Send_Basic.State[De_Orientation_State_LCD]=De_AgreeOn_State_Suc;			
}

static uint16 GetCentrIP(uint32 *IP) 			//获取当前IP
{	st_Sensor_DataPar	CN_st_Sensor_DataPar;
	st_Data_UDPTCP	CN_st_Data_UDPTCP;
	uint8 fd;
	if(CN_st_Fun_Sensor.GetPar2ID(De_Sensor_WordPar_GprsTzxy_1,&fd)!=De_Suc_Sensor)
		return De_Erro_DisPlayOpe_Nofd;
	CN_st_Fun_Sensor.GetSi(fd,&CN_st_Sensor_DataPar);
	if(CN_st_Fun_Gprs.GetIpPro((uint8 )CN_st_Sensor_DataPar.Addree,&CN_st_Data_UDPTCP)!=De_Suc_Gprs)
		return De_Erro_DisPlayOpe_Nofd;
	*IP=CN_st_Data_UDPTCP.IP;
	return De_Suc_DisplayOpe;
}





