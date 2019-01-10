#define De_MessageAndPhone_Compiler
#include "MessageAndPhone.h"
static void Init(void)
{	const st_Affair_Phone	CN_st_Affair_Phone={ptFunNewPhone,ptFunHupWork,ptFunMostPhone};
	const st_Affair_Message	CN_st_Affair_Message={NewMessage};
	const st_Affair_Timer	CN_st_Affair_Timer=
		{ 	{5,0,{0,0,0,0,0,0,0}},
			{CloseCall}
		};
	CN_st_Fun_Gprs.Init();	
	CN_st_Fun_Gprs.InitSys();
	CN_st_Fun_Gprs.InitMessage();
	CN_st_Fun_Gprs.InitPhone();
	CN_st_Fun_Gprs.OpenMessage((st_Affair_Message	*)&CN_st_Affair_Message);
	CN_st_Fun_Gprs.OpenPhone((st_Affair_Phone	*)&CN_st_Affair_Phone);
	CN_st_Fun_Timer.Open((st_Affair_Timer	*)&CN_st_Affair_Timer,&ClosePhTimerfd);
	CN_st_Fun_Timer.DisEnable(ClosePhTimerfd);
}
static void ptFunHupWork(uint8 *Phone)
{	AgreePhone(Phone,2);
}
static void NewMessage(uint8 *Phone,uint8 *Message)
{	st_AgreeOn_Driver	CN_st_AgreeOn_Driver;
	st_UpLoaderHandMess_Input	CN_st_UpLoaderHandMess_Input;
	st_st_AgreeOn_Dev_Par	CN_st_st_AgreeOn_Dev_Par;	
	uint16 DataLen,i,Result;
	uint8 fd;
	CN_st_Fun_OpenAndClose.OpenGps();
	CN_st_Fun_OpenAndClose.OpenGprs();
	if(CN_st_Fun_File.ReadRecoder(CN_st_File_fd.Driverfd,0,&CN_st_AgreeOn_Driver)!=De_Suc_File)
		return ;
	if(App_CN_st_WorkFlow_Table.LogState==0)
		return ;
	for(i=0;i<CN_st_AgreeOn_Driver.Number;i++)
	{	if(CN_st_Fun_AscNumber.CompareBuf(App_CN_st_WorkFlow_Table.DriverID,CN_st_AgreeOn_Driver.
		CN_st_AgreeOn_Driver_Par[i].ID,sizeof(CN_st_AgreeOn_Driver.CN_st_AgreeOn_Driver_Par[i].ID))!=0)
			continue;	
		break;
	}
	DataLen=CN_st_Fun_AscNumber.Strsize(Phone);
	if(DataLen>15)
		DataLen=15;
	if(CN_st_Fun_AscNumber.CompareBuf(CN_st_AgreeOn_Driver.CN_st_AgreeOn_Driver_Par[i].Phone,Phone,
	DataLen)!=0)   		//
		return ;
	CN_st_Fun_AscNumber.ClsArray(&CN_st_UpLoaderHandMess_Input,sizeof(st_UpLoaderHandMess_Input));
	CN_st_Fun_AscNumber.MoveByte(CN_st_UpLoaderHandMess_Input.Cut,Message,
	CN_st_Fun_AscNumber.Strsize(Message));
	CN_st_Fun_AscNumber.MoveByte(CN_st_UpLoaderHandMess_Input.Phone,Phone,DataLen);
	CN_st_Fun_AscNumber.MoveByte(CN_st_UpLoaderHandMess_Input.ID,App_CN_st_WorkFlow_Table.DriverID,10);
	CN_st_st_AgreeOn_Dev_Par.Buf=&CN_st_UpLoaderHandMess_Input;
	CN_st_st_AgreeOn_Dev_Par.ContrID=0;
	if((Result=CN_st_Fun_Tzv21.GetPar2ID(De_Sensor_WordPar_GprsTzxy_1,&fd))==De_Suc_AgreeOn)
		Result=CN_st_Fun_AppSendAgreeOn.WriteCommand(fd,De_Dev_Order_UpLoaderHandMess,&CN_st_st_AgreeOn_Dev_Par);
	if(Result==De_Suc_AgreeOn)
		CN_st_Fun_Gprs.SendMessage(Phone,"信息发送成功!");
	else
		CN_st_Fun_Gprs.SendMessage(Phone,"信息发送失败!");		
}

static void ptFunNewPhone(uint8 *Phone)								//新电话
{	uint16 Result;
	void (*ptFun)(void);
	CN_st_Fun_OpenAndClose.OpenGps();
	CN_st_Fun_OpenAndClose.OpenGprs();
	Result=BasicPhone(Phone);
	if(Result!=0)
	{	if(Result==1)
			CN_st_Fun_Gprs.AgreePhone();	
	   	else
		{	CN_st_Fun_Gprs.CloseCall();			//ClosePhone
			VICIntEnClr = 0xFFFFFFFF;
			MEMMAP = 0x01;
			ptFun=(void (*)())(0x0);//(void (*)())(0x40000000);												//接受电话
			ptFun();
		}
		return ;	
	}
	Result=ConsPhone(Phone);
	if((Result==2)||(Result==3))
	{	CN_st_Fun_Gprs.CloseCall();				//ClosePhone
		return ;
	}
	else if((Result==0)||(Result==1))
	{	if(AgreePhone(Phone,1)!=De_Suc_MessageAndPhone)				//接听
		{	CN_st_Fun_Gprs.CloseCall();			   //ClosePhone
		
		}	
		return ;
	}
	Result=JugeDriver(Phone);
	if(Result==De_Suc_MessageAndPhone)
	{	;			//s定时器
	   	return ;
	}
   	Result=JugePhone(Phone);
	if((Result==2)||(Result==3))
	{	CN_st_Fun_Gprs.CloseCall();				 //ClosePhone
		return ;
	}
	else if((Result==0)||(Result==1))
	{	if(AgreePhone(Phone,1)!=De_Suc_MessageAndPhone)					//接听
		{	CN_st_Fun_Gprs.CloseCall();			  //ClosePhone
		
		}	
		return ;
	}
	CN_st_Fun_Gprs.CloseCall();					//ClosePhone
	return ;
}
static void ptFunMostPhone(st_Data_Gprs_Call *ptst_Data_Gprs_Call)
{	if(ptst_Data_Gprs_Call->Mod==De_GprsHard_CallType_NoCall)
	{	AgreePhone(ptst_Data_Gprs_Call->Phone,2);
		return;	
	}
	if(ptst_Data_Gprs_Call->PhoneState==De_GprsHard_Phone_State_MeDialing)
	{	AgreePhone(ptst_Data_Gprs_Call->Phone,3);
		return;
	}
	if(ptst_Data_Gprs_Call->PhoneState==De_GprsHard_Phone_State_Active)
	{	AgreePhone(ptst_Data_Gprs_Call->Phone,5);
		return;
	}
	AgreePhone(ptst_Data_Gprs_Call->Phone,4);	
}



static uint16 BasicPhone(uint8 *Phone)				//基本电话
{	st_Phone_Basic	CN_st_Phone_Basic;
	uint16 DataLen;
	if(CN_st_Fun_File.ReadRecoder(CN_st_File_fd.Phonefd,0,&CN_st_Phone_Basic)==De_Suc_File)
	{	if((DataLen=CN_st_Fun_AscNumber.Strsize16(CN_st_Phone_Basic.WatchPhone))>sizeof(CN_st_Phone_Basic.WatchPhone))
			DataLen=sizeof(CN_st_Phone_Basic.WatchPhone);
		if(DataLen!=0)
		{	if(CN_st_Fun_AscNumber.CompareBuf(CN_st_Phone_Basic.WatchPhone,Phone,DataLen)==0)	//监控中心号码		
			   	return 1;
		}
		if((DataLen=CN_st_Fun_AscNumber.Strsize16(CN_st_Phone_Basic.RestPhone))>sizeof(CN_st_Phone_Basic.RestPhone))
			DataLen=sizeof(CN_st_Phone_Basic.RestPhone);
		if(DataLen!=0)
		{	if(CN_st_Fun_AscNumber.CompareBuf(CN_st_Phone_Basic.RestPhone,Phone,DataLen)==0)	//监控中心号码	
			   	return 2;
		}
	}
	return 0;
}

static uint16 ConsPhone(uint8 *Phone)
{	st_AgreeOn_Phone_Par	CN_st_AgreeOn_Phone_Par;
	st_Parameter_Table	CN_st_Parameter_Table;
	uint16 Cuit,DataLen;
	uint8 ByteV,i;
	Cuit=CN_st_Fun_File.GetJlNum(CN_st_File_fd.Rootfd);		
	for(i=0;i<Cuit;i++)
	{	CN_st_Fun_File.ReadRecoder(CN_st_File_fd.Rootfd,i+1,&CN_st_AgreeOn_Phone_Par);
		if(CN_st_Fun_AscNumber.CompareBuf(CN_st_AgreeOn_Phone_Par.Phone,Phone,15)!=0)
			continue;
		CN_st_Fun_File.ReadRecoder(CN_st_File_fd.Parameterfd,0,&CN_st_Parameter_Table);
		DataLen=CN_st_Fun_AscNumber.Strsize16(CN_st_Parameter_Table.CN_st_AgreeOn_ConfineCall.Phone);
		if(DataLen==0)
			return CN_st_AgreeOn_Phone_Par.State;
		if(DataLen>sizeof(CN_st_Parameter_Table.CN_st_AgreeOn_ConfineCall.Phone))
			DataLen=sizeof(CN_st_Parameter_Table.CN_st_AgreeOn_ConfineCall.Phone);
		if((CN_st_Parameter_Table.CN_st_AgreeOn_ConfineCall.Phone[DataLen-1]=='?')
		||(CN_st_Parameter_Table.CN_st_AgreeOn_ConfineCall.Phone[DataLen-1]=='*'))
			DataLen--;
		if(CN_st_Fun_AscNumber.CompareBuf(CN_st_Parameter_Table.CN_st_AgreeOn_ConfineCall.Phone,
		Phone,DataLen)!=0)
			return CN_st_AgreeOn_Phone_Par.State;
		ByteV=0x00;
		if((CN_st_Parameter_Table.CN_st_AgreeOn_ConfineCall.State==0x03)||
		(CN_st_Parameter_Table.CN_st_AgreeOn_ConfineCall.State==0x01)||
		(CN_st_AgreeOn_Phone_Par.State==0x03)||(CN_st_AgreeOn_Phone_Par.State==0x01))
			ByteV|=0x01;
		if((CN_st_Parameter_Table.CN_st_AgreeOn_ConfineCall.State==0x03)||
		(CN_st_Parameter_Table.CN_st_AgreeOn_ConfineCall.State==0x02)||
		(CN_st_AgreeOn_Phone_Par.State==0x03)||(CN_st_AgreeOn_Phone_Par.State==0x02))		
			ByteV|=0x02;
		return ByteV;			
	}
	return 0xffff;
}

static uint16 JugePhone(uint8 *Phone)
{	st_Parameter_Table	CN_st_Parameter_Table;
	uint16 DataLen;
	CN_st_Fun_File.ReadRecoder(CN_st_File_fd.Parameterfd,0,&CN_st_Parameter_Table);
	DataLen=CN_st_Fun_AscNumber.Strsize16(CN_st_Parameter_Table.CN_st_AgreeOn_ConfineCall.Phone);
	if(DataLen==0)
		return 0xffff;
	if(DataLen>sizeof(CN_st_Parameter_Table.CN_st_AgreeOn_ConfineCall.Phone))
		DataLen=sizeof(CN_st_Parameter_Table.CN_st_AgreeOn_ConfineCall.Phone);
	if((CN_st_Parameter_Table.CN_st_AgreeOn_ConfineCall.Phone[DataLen-1]=='?')
	||(CN_st_Parameter_Table.CN_st_AgreeOn_ConfineCall.Phone[DataLen-1]=='*'))
		DataLen--;
	if(CN_st_Fun_AscNumber.CompareBuf(CN_st_Parameter_Table.CN_st_AgreeOn_ConfineCall.Phone,
	Phone,DataLen)==0)
		return CN_st_Parameter_Table.CN_st_AgreeOn_ConfineCall.State;
	return 0xffff;
}


static uint16 JugeDriver(uint8 *Phone)						//判断是否是驾驶员登录
{	st_AgreeOn_Driver	CN_st_AgreeOn_Driver;
	uint16 DataLen,j;
	uint8 MessageCut[160],i;
	if(App_CN_st_WorkFlow_Table.LogState==0)							//当没有驾驶员时
	{	if(CN_st_Fun_File.ReadRecoder(CN_st_File_fd.Driverfd,0,&CN_st_AgreeOn_Driver)!=De_Suc_File)
			return De_Erro_MessageAndPhone_Nofd;
		for(i=0;i<CN_st_AgreeOn_Driver.Number;i++)
		{	DataLen=CN_st_Fun_AscNumber.Strsize(CN_st_AgreeOn_Driver.CN_st_AgreeOn_Driver_Par[i].Phone);
			if(DataLen>sizeof(CN_st_AgreeOn_Driver.CN_st_AgreeOn_Driver_Par[i].Phone))
				DataLen=sizeof(CN_st_AgreeOn_Driver.CN_st_AgreeOn_Driver_Par[i].Phone);
			if(CN_st_Fun_AscNumber.CompareBuf(Phone,CN_st_AgreeOn_Driver.CN_st_AgreeOn_Driver_Par[i].Phone,
			DataLen)!=0)
				continue;
			CN_st_Fun_AscNumber.ClsArray(MessageCut,sizeof(MessageCut));
		   	CN_st_Fun_AscNumber.MoveByte(App_CN_st_WorkFlow_Table.DriverID,CN_st_AgreeOn_Driver.CN_st_AgreeOn_Driver_Par[i].ID,10);
			CN_st_Fun_AscNumber.MoveByte(MessageCut,Phone,DataLen);
			App_CN_st_WorkFlow_Table.LogState=1;
			if(CN_st_Fun_AppSendAgreeOn.WriteFlow(De_Access_Type_JugeLog,&App_CN_st_WorkFlow_Table,
			NULL)!=De_Suc_AppSendAgree)
			{	CN_st_Fun_Gprs.SendMessage(Phone,"您的操作已接受,请稍后!");
				CN_st_Fun_Gprs.CloseCall();
				return De_Suc_MessageAndPhone;
			}
			else
			{	CN_st_Fun_Timer.Enable(ClosePhTimerfd);
				CN_st_Fun_AscNumber.MoveByte(MessageCut+DataLen,"登陆成功!",9);	
				CN_st_Fun_Gprs.SendMessage(Phone,MessageCut);
			   	return De_Suc_MessageAndPhone;
			}		
		}
		if(i==CN_st_AgreeOn_Driver.Number)
			return De_Erro_MessageAndPhone_Nofd;				
	}
	else
	{	if(CN_st_Fun_File.ReadRecoder(CN_st_File_fd.Driverfd,0,&CN_st_AgreeOn_Driver)!=De_Suc_File)
			return De_Erro_MessageAndPhone_Nofd;
		for(i=0;i<CN_st_AgreeOn_Driver.Number;i++)
		{	DataLen=CN_st_Fun_AscNumber.Strsize(CN_st_AgreeOn_Driver.CN_st_AgreeOn_Driver_Par[i].Phone);
			if(DataLen>sizeof(CN_st_AgreeOn_Driver.CN_st_AgreeOn_Driver_Par[i].Phone))
				DataLen=sizeof(CN_st_AgreeOn_Driver.CN_st_AgreeOn_Driver_Par[i].Phone);
			if(CN_st_Fun_AscNumber.CompareBuf(Phone,CN_st_AgreeOn_Driver.CN_st_AgreeOn_Driver_Par[i].Phone,
			DataLen)!=0)
				continue;
			CN_st_Fun_AscNumber.ClsArray(MessageCut,sizeof(MessageCut));
			if(CN_st_Fun_AscNumber.CompareBuf(App_CN_st_WorkFlow_Table.DriverID,CN_st_AgreeOn_Driver.CN_st_AgreeOn_Driver_Par[i].ID,
			sizeof(App_CN_st_WorkFlow_Table.DriverID))==0)			//推出登录
			{	App_CN_st_WorkFlow_Table.LogState=0;
				if(CN_st_Fun_AppSendAgreeOn.WriteFlow(De_Access_Type_ExitLog,&App_CN_st_WorkFlow_Table,
				NULL)!=De_Suc_AppSendAgree)
				{	CN_st_Fun_Gprs.SendMessage(Phone,"您的操作已接受，请稍后!");
					CN_st_Fun_Gprs.CloseCall();
					return De_Suc_MessageAndPhone;
				}
				CN_st_Fun_AscNumber.MoveByte(MessageCut,Phone,DataLen);
			   	CN_st_Fun_AscNumber.MoveByte(MessageCut+DataLen,"退出成功!",9);
				CN_st_Fun_Gprs.SendMessage(Phone,MessageCut);
				CN_st_Fun_Timer.Enable(ClosePhTimerfd);
				return De_Suc_MessageAndPhone;
			}
			else
			{	CN_st_Fun_AscNumber.MoveByte(MessageCut,"登陆失败!",9);
				for(j=0;j<CN_st_AgreeOn_Driver.Number;j++)
				{	if(CN_st_Fun_AscNumber.CompareBuf(App_CN_st_WorkFlow_Table.DriverID,
					CN_st_AgreeOn_Driver.CN_st_AgreeOn_Driver_Par[j].ID,sizeof(CN_st_AgreeOn_Driver.CN_st_AgreeOn_Driver_Par[j].ID))==0)
						break;
				}
				DataLen=CN_st_Fun_AscNumber.Strsize(CN_st_AgreeOn_Driver.CN_st_AgreeOn_Driver_Par[j].Phone);
				if(DataLen>15)
					DataLen=15;
				CN_st_Fun_AscNumber.MoveByte(MessageCut+9,CN_st_AgreeOn_Driver.CN_st_AgreeOn_Driver_Par[j].Phone,
				DataLen);
				DataLen+=9;
				CN_st_Fun_AscNumber.MoveByte(MessageCut+DataLen,"已登陆!",7);
				App_CN_st_WorkFlow_Table.LogState=2+i;
				CN_st_Fun_AppSendAgreeOn.WriteFlow(De_Access_Type_LogErro,&App_CN_st_WorkFlow_Table,
				NULL);	
				CN_st_Fun_Gprs.SendMessage(Phone,MessageCut);
				CN_st_Fun_Gprs.CloseCall();
				return De_Suc_MessageAndPhone;	
			}		
		}
		if(i==CN_st_AgreeOn_Driver.Number)
			return De_Erro_MessageAndPhone_Nofd;
	}			
}



static uint16 AgreePhone(uint8 *Phone,uint8 State)
{	st_Display_Order_Phone	CN_st_Display_Order_Phone;
	st_Display_Send	CN_st_Display_Send;
	uint8 fd;
	uint16 DataLen;
	CN_st_Display_Send.SendOrAgree=De_Sensor_Display_Send;
	CN_st_Display_Send.ID=De_Display_Host_Order_Phone;
	DataLen=CN_st_Fun_AscNumber.Strsize16(Phone);
	if(DataLen>15)
		DataLen=15;
	CN_st_Fun_AscNumber.ClsArray(&CN_st_Display_Order_Phone,sizeof(st_Display_Order_Phone));
	CN_st_Fun_AscNumber.MoveByte(CN_st_Display_Order_Phone.Phone,Phone,DataLen);
	CN_st_Display_Order_Phone.PhoneType=State;
	CN_st_Display_Send.SendData=&CN_st_Display_Order_Phone;  	
	if(CN_st_Fun_Sensor.GetPar2ID(De_Sensor_WordPar_Display,&fd)!=De_Suc_Sensor)
		return De_Erro_MessageAndPhone;
	CN_st_Fun_Sensor.Read(fd,&CN_st_Display_Send,NULL);
	return De_Suc_MessageAndPhone;
}


static void CloseCall(st_Data_Timer	*ptst_Data_Timer,uint8 fd)
{	CN_st_Fun_Gprs.CloseCall();
	CN_st_Fun_Timer.DisEnable(fd);
}
