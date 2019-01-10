#include "..\Control\GpsAndMileage\GpsAndMileage.h"
static void SetPar(st_AgreeOn_Agree_Par_Cut	*ptst_AgreeOn_Agree_Par_Cut,uint8 Space);
const uint32 *CN_LessPar[]=
{	&(((st_File_WorkPar	*)(NULL))->CN_st_File_WorkParVal[16].Adree),
	&(((st_File_WorkPar	*)(NULL))->CN_st_File_WorkParVal[17].Adree),
	&(((st_File_WorkPar	*)(NULL))->CN_st_File_WorkParVal[18].Adree),
	&(((st_File_WorkPar	*)(NULL))->CN_st_File_WorkParVal[19].Adree),
	&(((st_File_WorkPar	*)(NULL))->CN_st_File_WorkParVal[20].Adree),
	&(((st_File_WorkPar	*)(NULL))->CN_st_File_WorkParVal[21].Adree),
	&(((st_File_WorkPar	*)(NULL))->CN_st_File_WorkParVal[32].Adree),
	&(((st_File_WorkPar	*)(NULL))->CN_st_File_WorkParVal[33].Adree),
	&(((st_File_WorkPar	*)(NULL))->CN_st_File_WorkParVal[34].Adree),
	&(((st_File_WorkPar	*)(NULL))->CN_st_File_WorkParVal[35].Adree)
};
static void SetPar(st_AgreeOn_Agree_Par_Cut	*ptst_AgreeOn_Agree_Par,uint8 Space)
{	union 
	{	st_File_GreenPar	CN_st_File_GreenPar;
		st_Phone_Basic		CN_st_Phone_Basic;
		st_Message_ComPar	CN_st_Message_ComPar;
		st_Gprs_ComPar		CN_st_Gprs_ComPar;
		st_Parameter_Table	CN_st_Parameter_Table;
		st_AccTimer			CN_st_AccTimer;
		st_File_Gps			CN_st_File_Gps;
		st_File_WorkPar		CN_st_File_WorkPar;
	}un_Par;
	uint32 *Val;
	uint8 i;

	if(Space==De_AgreeOn_SetPar_State_SetGreenPar)
	{	CN_st_Fun_File.ReadRecoder(CN_st_File_fd.GreenParfd,0,&un_Par.CN_st_File_GreenPar);
		un_Par.CN_st_File_GreenPar.Integral=ptst_AgreeOn_Agree_Par->GreenPar;		
		CN_st_Fun_File.WriteRecoder(CN_st_File_fd.GreenParfd,0,&un_Par.CN_st_File_GreenPar);
		;				//发送界面积分
	}
	else if(Space==De_AgreeOn_SetPar_State_SetGreenWord)
	{	CN_st_Fun_File.ReadRecoder(CN_st_File_fd.GreenParfd,0,&un_Par.CN_st_File_GreenPar);
		CN_st_Fun_AscNumber.MoveByte(un_Par.CN_st_File_GreenPar.GreenWord,ptst_AgreeOn_Agree_Par->GreenWord,
		sizeof(ptst_AgreeOn_Agree_Par->GreenWord));
		CN_st_Fun_File.WriteRecoder(CN_st_File_fd.GreenParfd,0,&un_Par.CN_st_File_GreenPar);
		;				//发送界面文字
	}
	else if(Space==De_AgreeOn_SetPar_State_SetListePhone)	//设置监听号码
	{	CN_st_Fun_File.ReadRecoder(CN_st_File_fd.Phonefd,0,&un_Par.CN_st_Phone_Basic);
		CN_st_Fun_AscNumber.MoveByte(un_Par.CN_st_Phone_Basic.WatchPhone,ptst_AgreeOn_Agree_Par->ListePhone,
		sizeof(ptst_AgreeOn_Agree_Par->ListePhone));
		CN_st_Fun_File.WriteRecoder(CN_st_File_fd.Phonefd,0,&un_Par.CN_st_Phone_Basic);	
	}
	else if(Space==De_AgreeOn_SetPar_State_SetResetPhone)		//设置电话复位
	{	CN_st_Fun_File.ReadRecoder(CN_st_File_fd.Phonefd,0,&un_Par.CN_st_Phone_Basic);
		CN_st_Fun_AscNumber.MoveByte(un_Par.CN_st_Phone_Basic.RestPhone,ptst_AgreeOn_Agree_Par->ResetPhone,
		sizeof(ptst_AgreeOn_Agree_Par->ResetPhone));
		CN_st_Fun_File.WriteRecoder(CN_st_File_fd.Phonefd,0,&un_Par.CN_st_Phone_Basic);
	}
	else if(Space==De_AgreeOn_SetPar_State_SetCerSevPhone)			//设置短信中心服务号码
	{	CN_st_Fun_File.ReadRecoder(CN_st_File_fd.MessageParfd,0,&un_Par.CN_st_Message_ComPar);
		CN_st_Fun_AscNumber.MoveByte(un_Par.CN_st_Message_ComPar.CN_st_Message_Phone.CenMessageSev,
		ptst_AgreeOn_Agree_Par->CerSevPhone,
		sizeof(ptst_AgreeOn_Agree_Par->CerSevPhone));
		CN_st_Fun_File.WriteRecoder(CN_st_File_fd.MessageParfd,0,&un_Par.CN_st_Message_ComPar);
	}
	else if(Space==De_AgreeOn_SetPar_State_SetCenPhone)				//设置短信中心服务号码
	{	CN_st_Fun_File.ReadRecoder(CN_st_File_fd.MessageParfd,0,&un_Par.CN_st_Message_ComPar);
		CN_st_Fun_AscNumber.MoveByte(un_Par.CN_st_Message_ComPar.CN_st_Message_Phone.CentrMessPhone1,
		ptst_AgreeOn_Agree_Par->CenPhone,
		sizeof(un_Par.CN_st_Message_ComPar.CN_st_Message_Phone.CentrMessPhone1));
		CN_st_Fun_File.WriteRecoder(CN_st_File_fd.MessageParfd,0,&un_Par.CN_st_Message_ComPar);
	}
	else if(Space==De_AgreeOn_SetPar_State_SetAPN)					//设置APN参数
	{	CN_st_Fun_File.ReadRecoder(CN_st_File_fd.GprsParfd,0,&un_Par.CN_st_Gprs_ComPar);
		CN_st_Fun_AscNumber.MoveByte(un_Par.CN_st_Gprs_ComPar.CN_st_Gprs_IPNet.APN,ptst_AgreeOn_Agree_Par->APN,
		sizeof(ptst_AgreeOn_Agree_Par->APN));
		CN_st_Fun_File.WriteRecoder(CN_st_File_fd.GprsParfd,0,&un_Par.CN_st_Gprs_ComPar);
	}
	else if(Space==De_AgreeOn_SetPar_State_SetMastIP)				//设置主中心IP
	{	CN_st_Fun_File.ReadRecoder(CN_st_File_fd.GprsParfd,0,&un_Par.CN_st_Gprs_ComPar);
		un_Par.CN_st_Gprs_ComPar.CN_Mast_st_Gprs_IP.IP=ptst_AgreeOn_Agree_Par->MastIP;
		CN_st_Fun_File.WriteRecoder(CN_st_File_fd.GprsParfd,0,&un_Par.CN_st_Gprs_ComPar);
	}
	else if(Space==De_AgreeOn_SetPar_State_SetMastDomainName)		//设置主域名
	{	CN_st_Fun_File.ReadRecoder(CN_st_File_fd.GprsParfd,0,&un_Par.CN_st_Gprs_ComPar);
		CN_st_Fun_AscNumber.MoveByte(un_Par.CN_st_Gprs_ComPar.CN_Mast_st_Gprs_IP.DomainName,
		ptst_AgreeOn_Agree_Par->MastDomainName,sizeof(ptst_AgreeOn_Agree_Par->MastDomainName));
		CN_st_Fun_File.WriteRecoder(CN_st_File_fd.GprsParfd,0,&un_Par.CN_st_Gprs_ComPar);
	}
	else if(Space==De_AgreeOn_SetPar_State_SetReserveIP)			//设置副中心IP
	{	CN_st_Fun_File.ReadRecoder(CN_st_File_fd.GprsParfd,0,&un_Par.CN_st_Gprs_ComPar);
		un_Par.CN_st_Gprs_ComPar.CN_Reserve_st_Gprs_IP.IP=ptst_AgreeOn_Agree_Par->ReserveIP;
		CN_st_Fun_File.WriteRecoder(CN_st_File_fd.GprsParfd,0,&un_Par.CN_st_Gprs_ComPar);
	}
	else if(Space==De_AgreeOn_SetPar_State_SetReserveDomainName)	//设置设置副域名
	{	CN_st_Fun_File.ReadRecoder(CN_st_File_fd.GprsParfd,0,&un_Par.CN_st_Gprs_ComPar);
		CN_st_Fun_AscNumber.MoveByte(un_Par.CN_st_Gprs_ComPar.CN_Reserve_st_Gprs_IP.DomainName,
		ptst_AgreeOn_Agree_Par->ReserveDomainName,sizeof(ptst_AgreeOn_Agree_Par->ReserveDomainName));
		CN_st_Fun_File.WriteRecoder(CN_st_File_fd.GprsParfd,0,&un_Par.CN_st_Gprs_ComPar);
	}
	else if(Space==De_AgreeOn_SetPar_State_SetCenPort)				//设置中心端口号
	{	CN_st_Fun_File.ReadRecoder(CN_st_File_fd.GprsParfd,0,&un_Par.CN_st_Gprs_ComPar);
		un_Par.CN_st_Gprs_ComPar.CenPort=ptst_AgreeOn_Agree_Par->CenPort;
		CN_st_Fun_File.WriteRecoder(CN_st_File_fd.GprsParfd,0,&un_Par.CN_st_Gprs_ComPar);
	}
	else if(Space==De_AgreeOn_SetPar_State_SetUseName)				//设置用户名
	{ 	CN_st_Fun_File.ReadRecoder(CN_st_File_fd.GprsParfd,0,&un_Par.CN_st_Gprs_ComPar);
		CN_st_Fun_AscNumber.MoveByte(un_Par.CN_st_Gprs_ComPar.CN_st_Gprs_IPNet.Use,
		ptst_AgreeOn_Agree_Par->UseName,sizeof(ptst_AgreeOn_Agree_Par->UseName));
		CN_st_Fun_File.WriteRecoder(CN_st_File_fd.GprsParfd,0,&un_Par.CN_st_Gprs_ComPar);
	}
	else if(Space==De_AgreeOn_SetPar_State_SetUsePass)				//设置拨号密码
	{ 	CN_st_Fun_File.ReadRecoder(CN_st_File_fd.GprsParfd,0,&un_Par.CN_st_Gprs_ComPar);
		CN_st_Fun_AscNumber.MoveByte(un_Par.CN_st_Gprs_ComPar.CN_st_Gprs_IPNet.PassWord,
		ptst_AgreeOn_Agree_Par->UsePass,sizeof(ptst_AgreeOn_Agree_Par->UsePass));
		CN_st_Fun_File.WriteRecoder(CN_st_File_fd.GprsParfd,0,&un_Par.CN_st_Gprs_ComPar);
	}
	else if(Space==De_AgreeOn_SetPar_State_SetDevHeart)		 		//终端上发心跳间隔
	{	CN_st_Fun_File.ReadRecoder(CN_st_File_fd.GprsParfd,0,&un_Par.CN_st_Gprs_ComPar);
		un_Par.CN_st_Gprs_ComPar.CN_st_Gprs_BasicPar.DeviceHeart=ptst_AgreeOn_Agree_Par->DevHeart;
		CN_st_Fun_File.WriteRecoder(CN_st_File_fd.GprsParfd,0,&un_Par.CN_st_Gprs_ComPar);
	}	
	else if(Space==De_AgreeOn_SetPar_State_SetCentHeart)			//中心下发心跳间隔
	{	CN_st_Fun_File.ReadRecoder(CN_st_File_fd.GprsParfd,0,&un_Par.CN_st_Gprs_ComPar);
		un_Par.CN_st_Gprs_ComPar.CN_st_Gprs_BasicPar.CentrHeart=ptst_AgreeOn_Agree_Par->CentHeart;
	 	CN_st_Fun_File.WriteRecoder(CN_st_File_fd.GprsParfd,0,&un_Par.CN_st_Gprs_ComPar);			
	}
	else if(Space==De_AgreeOn_SetPar_State_SetComMod)				//设置通讯方式
	{	CN_st_Fun_File.ReadRecoder(CN_st_File_fd.Parameterfd,0,&un_Par.CN_st_Parameter_Table);
		un_Par.CN_st_Parameter_Table.ComMod=ptst_AgreeOn_Agree_Par->ComMod;
		CN_st_Fun_File.WriteRecoder(CN_st_File_fd.Parameterfd,0,&un_Par.CN_st_Parameter_Table);
	}
	else if(Space==De_AgreeOn_SetPar_State_SetIPRepeat)				//Ip关键指令重发次数
	{	CN_st_Fun_File.ReadRecoder(CN_st_File_fd.GprsParfd,0,&un_Par.CN_st_Gprs_ComPar);
	   	un_Par.CN_st_Gprs_ComPar.CN_st_Gprs_BasicPar.Repeat=ptst_AgreeOn_Agree_Par->IPRepeat;
	   	CN_st_Fun_File.WriteRecoder(CN_st_File_fd.GprsParfd,0,&un_Par.CN_st_Gprs_ComPar);
	}
	else if(Space==De_AgreeOn_SetPar_State_SetIPRepeatTime)		   //IP关键指令重发间隔时间
	{	CN_st_Fun_File.ReadRecoder(CN_st_File_fd.GprsParfd,0,&un_Par.CN_st_Gprs_ComPar);
	   	un_Par.CN_st_Gprs_ComPar.CN_st_Gprs_BasicPar.RepeatTime=ptst_AgreeOn_Agree_Par->IPRepeatTime;
	   	CN_st_Fun_File.WriteRecoder(CN_st_File_fd.GprsParfd,0,&un_Par.CN_st_Gprs_ComPar);
	}
	else if(Space==De_AgreeOn_SetPar_State_SetMessageRepeat)		//Message关键指令重发次数
	{	CN_st_Fun_File.ReadRecoder(CN_st_File_fd.MessageParfd,0,&un_Par.CN_st_Message_ComPar);
	   	un_Par.CN_st_Message_ComPar.CN_st_Message_BasicPar.Repeat=
		ptst_AgreeOn_Agree_Par->MessageRepeat;
	   	CN_st_Fun_File.WriteRecoder(CN_st_File_fd.MessageParfd,0,&un_Par.CN_st_Message_ComPar);
	}
	else if(Space==De_AgreeOn_SetPar_State_SetMessageRepeatTimer)	//Message Timer 重发时间
	{	CN_st_Fun_File.ReadRecoder(CN_st_File_fd.MessageParfd,0,&un_Par.CN_st_Message_ComPar);
	   	un_Par.CN_st_Message_ComPar.CN_st_Message_BasicPar.
		RepeatTime=ptst_AgreeOn_Agree_Par->MessageRepeatTimer;
	   	CN_st_Fun_File.WriteRecoder(CN_st_File_fd.MessageParfd,0,&un_Par.CN_st_Message_ComPar);
	}
	else if(Space==De_AgreeOn_SetPar_State_SetIPTransSms)			//Message与IP之间切换时间
	{	CN_st_Fun_File.ReadRecoder(CN_st_File_fd.Parameterfd,0,&un_Par.CN_st_Parameter_Table);
	   	un_Par.CN_st_Parameter_Table.IPTransMessage=ptst_AgreeOn_Agree_Par->IPTransSms;
	   	CN_st_Fun_File.WriteRecoder(CN_st_File_fd.Parameterfd,0,&un_Par.CN_st_Parameter_Table);
	}
	else if(Space==De_AgreeOn_SetPar_State_SetDataLog)				//数据日志存储
	{	CN_st_Fun_File.ReadRecoder(CN_st_File_fd.Parameterfd,0,&un_Par.CN_st_Parameter_Table);
		CN_st_Fun_AscNumber.MoveByte(un_Par.CN_st_Parameter_Table.CN_st_Data_Access.DataLog,
		ptst_AgreeOn_Agree_Par->DataLog,sizeof(ptst_AgreeOn_Agree_Par->DataLog));
		CN_st_Fun_File.WriteRecoder(CN_st_File_fd.Parameterfd,0,&un_Par.CN_st_Parameter_Table);	
	}
	else if(Space==De_AgreeOn_SetPar_State_SetDataScotomaLog)		//盲区补偿数据
	{	CN_st_Fun_File.ReadRecoder(CN_st_File_fd.Parameterfd,0,&un_Par.CN_st_Parameter_Table);
		CN_st_Fun_AscNumber.MoveByte(un_Par.CN_st_Parameter_Table.CN_st_Data_Access.ScotomaLog,
		ptst_AgreeOn_Agree_Par->DataScotomaLog,sizeof(ptst_AgreeOn_Agree_Par->DataScotomaLog));	
		CN_st_Fun_File.WriteRecoder(CN_st_File_fd.Parameterfd,0,&un_Par.CN_st_Parameter_Table);
	}
	else if(Space==De_AgreeOn_SetPar_State_SetParLoad)				//上传工作参数
	{	CN_st_Fun_File.ReadRecoder(CN_st_File_fd.WorkParfd,0,&un_Par.CN_st_File_WorkPar);
		for(i=0;i<De_CN_Ba_WordPar_Number;i++)
		{	un_Par.CN_st_File_WorkPar.CN_st_File_WorkParVal[i].YesOnON=De_WordPar_Close;
			if(ptst_AgreeOn_Agree_Par->ParLoad[i]==De_WordPar_Open)
				un_Par.CN_st_File_WorkPar.CN_st_File_WorkParVal[i].YesOnON=De_WordPar_Open;	
		}
		CN_st_Fun_File.WriteRecoder(CN_st_File_fd.WorkParfd,0,&un_Par.CN_st_File_WorkPar);
	}
	else if(Space==De_AgreeOn_SetPar_State_SetWireLessPar)			//设置无线参数
	{	CN_st_Fun_File.ReadRecoder(CN_st_File_fd.WorkParfd,0,&un_Par.CN_st_File_WorkPar);
		for(i=0;i<sizeof(CN_LessPar)/sizeof(uint32 );i++)
		{ 	Val=(uint32 *)((uint32 )&un_Par+(uint32 )CN_LessPar[i]);
			*Val=ptst_AgreeOn_Agree_Par->WireLessPar[i];
			un_Par.CN_st_File_WorkPar.CN_st_File_WorkParVal[i].Adree=*Val;
		}	
		CN_st_Fun_File.WriteRecoder(CN_st_File_fd.WorkParfd,0,&un_Par.CN_st_File_WorkPar);	
	}
	else if(Space==De_AgreeOn_SetPar_State_SetDePassWord)  			//设置终端密码
	{	CN_st_Fun_File.ReadRecoder(CN_st_File_fd.GreenParfd,0,&un_Par.CN_st_File_GreenPar);
		un_Par.CN_st_File_GreenPar.PassWord=ptst_AgreeOn_Agree_Par->DePassWord;		
		CN_st_Fun_File.WriteRecoder(CN_st_File_fd.GreenParfd,0,&un_Par.CN_st_File_GreenPar);
	}
	else if(Space==De_AgreeOn_SetPar_State_SetAccTimer)				//设置ACC累计时间
	{	CN_st_Fun_File.ReadRecoder(CN_st_File_fd.AccTimerfd,0,&un_Par.CN_st_AccTimer);
		un_Par.CN_st_AccTimer.AccTimer=ptst_AgreeOn_Agree_Par->AccTimer;		
		CN_st_Fun_File.WriteRecoder(CN_st_File_fd.AccTimerfd,0,&un_Par.CN_st_AccTimer);
	}
	else if(Space==De_AgreeOn_SetPar_State_SetRunLen) 				//设置运行里程
	{	CN_st_Fun_File.ReadRecoder(CN_st_File_fd.Gpsfd,0,&un_Par.CN_st_File_Gps);
		un_Par.CN_st_File_Gps.Milage=ptst_AgreeOn_Agree_Par->RunLen;		
		CN_st_Fun_File.WriteRecoder(CN_st_File_fd.Gpsfd,0,&un_Par.CN_st_File_Gps);
	}
	else if(Space==De_AgreeOn_SetPar_State_SetPerPuse)				//设置每周的脉冲数
	{	CN_st_Fun_File.ReadRecoder(CN_st_File_fd.Parameterfd,0,&un_Par.CN_st_Parameter_Table);
		un_Par.CN_st_Parameter_Table.CN_st_File_Car_Par.PerPuse=ptst_AgreeOn_Agree_Par->PerPuse; 	
		CN_st_Fun_File.WriteRecoder(CN_st_File_fd.Parameterfd,0,&un_Par.CN_st_Parameter_Table);

	}
	else if(Space==De_AgreeOn_SetPar_State_SetCarFeature)			//设置车辆特征
	{	CN_st_Fun_File.ReadRecoder(CN_st_File_fd.Parameterfd,0,&un_Par.CN_st_Parameter_Table);
		un_Par.CN_st_Parameter_Table.CN_st_File_Car_Par.Feature=ptst_AgreeOn_Agree_Par->CarFeature; 	
		CN_st_Fun_File.WriteRecoder(CN_st_File_fd.Parameterfd,0,&un_Par.CN_st_Parameter_Table);
	}
	else if(Space==De_AgreeOn_SetPar_State_SetTakeLCD)				//设置车辆是否安装调度
	{	CN_st_Fun_File.ReadRecoder(CN_st_File_fd.Parameterfd,0,&un_Par.CN_st_Parameter_Table);
		un_Par.CN_st_Parameter_Table.DisLCD=ptst_AgreeOn_Agree_Par->TakeLCD; 	
		CN_st_Fun_File.WriteRecoder(CN_st_File_fd.Parameterfd,0,&un_Par.CN_st_Parameter_Table);
	}
	else if(Space==De_AgreeOn_SetPar_State_SetOilFrequency)			////设置油量采样频率
   	{	CN_st_Fun_File.ReadRecoder(CN_st_File_fd.Parameterfd,0,&un_Par.CN_st_Parameter_Table);
		un_Par.CN_st_Parameter_Table.CN_st_File_Car_Par.OilFrequency=ptst_AgreeOn_Agree_Par->OilFrequency; 	
		CN_st_Fun_File.WriteRecoder(CN_st_File_fd.Parameterfd,0,&un_Par.CN_st_Parameter_Table);
	}
	else if(Space==De_AgreeOn_SetPar_State_SetSleepTimer) 			//设置休眠时间
	{	CN_st_Fun_File.ReadRecoder(CN_st_File_fd.Parameterfd,0,&un_Par.CN_st_Parameter_Table);
		un_Par.CN_st_Parameter_Table.CN_st_Sleep_Par.GpsTimer=ptst_AgreeOn_Agree_Par->SleepTimer; 	
		CN_st_Fun_File.WriteRecoder(CN_st_File_fd.Parameterfd,0,&un_Par.CN_st_Parameter_Table);
	}
	else if(Space==De_AgreeOn_SetPar_State_SetCloseTimer)		   //设置关机时间
	{	CN_st_Fun_File.ReadRecoder(CN_st_File_fd.Parameterfd,0,&un_Par.CN_st_Parameter_Table);
		un_Par.CN_st_Parameter_Table.CN_st_Sleep_Par.GprsTimer=ptst_AgreeOn_Agree_Par->CloseTimer; 	
		CN_st_Fun_File.WriteRecoder(CN_st_File_fd.Parameterfd,0,&un_Par.CN_st_Parameter_Table);
	}
	else if(Space==De_AgreeOn_SetPar_State_SetLogMess)		   		//设置登录提示
	{	CN_st_Fun_File.ReadRecoder(CN_st_File_fd.Parameterfd,0,&un_Par.CN_st_Parameter_Table);
		un_Par.CN_st_Parameter_Table.DisLogin=ptst_AgreeOn_Agree_Par->LogMess; 	
		CN_st_Fun_File.WriteRecoder(CN_st_File_fd.Parameterfd,0,&un_Par.CN_st_Parameter_Table);
	}
	else if(Space==De_AgreeOn_SetPar_State_SetTaskVid)		   		//设置登录提示
	{	CN_st_Fun_File.ReadRecoder(CN_st_File_fd.Parameterfd,0,&un_Par.CN_st_Parameter_Table);
		un_Par.CN_st_Parameter_Table.DisVid=ptst_AgreeOn_Agree_Par->TaskVid; 	
		CN_st_Fun_File.WriteRecoder(CN_st_File_fd.Parameterfd,0,&un_Par.CN_st_Parameter_Table);
	}
	else if(Space==De_AgreeOn_SetPar_State_SetHighSpeed)			//设置超速报警
	{	CN_st_Fun_File.ReadRecoder(CN_st_File_fd.Parameterfd,0,&un_Par.CN_st_Parameter_Table);
		CN_st_Fun_AscNumber.MoveByte(&un_Par.CN_st_Parameter_Table.CN_st_Sum_Waring.HighSpeed,
		&ptst_AgreeOn_Agree_Par->CN_High_st_Waring_Par,sizeof(st_Waring_Par));
		CN_st_Fun_File.WriteRecoder(CN_st_File_fd.Parameterfd,0,&un_Par.CN_st_Parameter_Table);
	}
	else if(Space==De_AgreeOn_SetPar_State_SetLowSpeed)				//设置低速报警
	{	CN_st_Fun_File.ReadRecoder(CN_st_File_fd.Parameterfd,0,&un_Par.CN_st_Parameter_Table);
		CN_st_Fun_AscNumber.MoveByte(&un_Par.CN_st_Parameter_Table.CN_st_Sum_Waring.LowSpeed,
		&ptst_AgreeOn_Agree_Par->CN_Low_st_Waring_Par,sizeof(st_Waring_Par));
		CN_st_Fun_File.WriteRecoder(CN_st_File_fd.Parameterfd,0,&un_Par.CN_st_Parameter_Table);
	}
	else if(Space==De_AgreeOn_SetPar_State_SetLowVlt)				//设置低电压报警
	{	CN_st_Fun_File.ReadRecoder(CN_st_File_fd.Parameterfd,0,&un_Par.CN_st_Parameter_Table);
		CN_st_Fun_AscNumber.MoveByte(&un_Par.CN_st_Parameter_Table.CN_st_Sum_Waring.Voltage,
		&ptst_AgreeOn_Agree_Par->CN_Vo_st_Waring_Par,sizeof(st_Waring_Par));
		CN_st_Fun_File.WriteRecoder(CN_st_File_fd.Parameterfd,0,&un_Par.CN_st_Parameter_Table);
	}
	else if(Space==De_AgreeOn_SetPar_State_SetVidType)				//设置拍照类型
	{	CN_st_Fun_File.ReadRecoder(CN_st_File_fd.Parameterfd,0,&un_Par.CN_st_Parameter_Table);
		CN_st_Fun_AscNumber.MoveByte(&un_Par.CN_st_Parameter_Table.CN_st_VidType,
		&ptst_AgreeOn_Agree_Par->CN_st_VidType,sizeof(st_VidType));
		CN_st_Fun_File.WriteRecoder(CN_st_File_fd.Parameterfd,0,&un_Par.CN_st_Parameter_Table);
	}
	else if(Space==De_AgreeOn_SetPar_State_SetOrderFrmTimer)		//设置预约订单时间
	{	CN_st_Fun_File.ReadRecoder(CN_st_File_fd.Parameterfd,0,&un_Par.CN_st_Parameter_Table);
		un_Par.CN_st_Parameter_Table.FrmTimer=ptst_AgreeOn_Agree_Par->OrderFrmTimer;
		CN_st_Fun_File.WriteRecoder(CN_st_File_fd.Parameterfd,0,&un_Par.CN_st_Parameter_Table);
	}
}



