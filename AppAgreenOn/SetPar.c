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
		;				//���ͽ������
	}
	else if(Space==De_AgreeOn_SetPar_State_SetGreenWord)
	{	CN_st_Fun_File.ReadRecoder(CN_st_File_fd.GreenParfd,0,&un_Par.CN_st_File_GreenPar);
		CN_st_Fun_AscNumber.MoveByte(un_Par.CN_st_File_GreenPar.GreenWord,ptst_AgreeOn_Agree_Par->GreenWord,
		sizeof(ptst_AgreeOn_Agree_Par->GreenWord));
		CN_st_Fun_File.WriteRecoder(CN_st_File_fd.GreenParfd,0,&un_Par.CN_st_File_GreenPar);
		;				//���ͽ�������
	}
	else if(Space==De_AgreeOn_SetPar_State_SetListePhone)	//���ü�������
	{	CN_st_Fun_File.ReadRecoder(CN_st_File_fd.Phonefd,0,&un_Par.CN_st_Phone_Basic);
		CN_st_Fun_AscNumber.MoveByte(un_Par.CN_st_Phone_Basic.WatchPhone,ptst_AgreeOn_Agree_Par->ListePhone,
		sizeof(ptst_AgreeOn_Agree_Par->ListePhone));
		CN_st_Fun_File.WriteRecoder(CN_st_File_fd.Phonefd,0,&un_Par.CN_st_Phone_Basic);	
	}
	else if(Space==De_AgreeOn_SetPar_State_SetResetPhone)		//���õ绰��λ
	{	CN_st_Fun_File.ReadRecoder(CN_st_File_fd.Phonefd,0,&un_Par.CN_st_Phone_Basic);
		CN_st_Fun_AscNumber.MoveByte(un_Par.CN_st_Phone_Basic.RestPhone,ptst_AgreeOn_Agree_Par->ResetPhone,
		sizeof(ptst_AgreeOn_Agree_Par->ResetPhone));
		CN_st_Fun_File.WriteRecoder(CN_st_File_fd.Phonefd,0,&un_Par.CN_st_Phone_Basic);
	}
	else if(Space==De_AgreeOn_SetPar_State_SetCerSevPhone)			//���ö������ķ������
	{	CN_st_Fun_File.ReadRecoder(CN_st_File_fd.MessageParfd,0,&un_Par.CN_st_Message_ComPar);
		CN_st_Fun_AscNumber.MoveByte(un_Par.CN_st_Message_ComPar.CN_st_Message_Phone.CenMessageSev,
		ptst_AgreeOn_Agree_Par->CerSevPhone,
		sizeof(ptst_AgreeOn_Agree_Par->CerSevPhone));
		CN_st_Fun_File.WriteRecoder(CN_st_File_fd.MessageParfd,0,&un_Par.CN_st_Message_ComPar);
	}
	else if(Space==De_AgreeOn_SetPar_State_SetCenPhone)				//���ö������ķ������
	{	CN_st_Fun_File.ReadRecoder(CN_st_File_fd.MessageParfd,0,&un_Par.CN_st_Message_ComPar);
		CN_st_Fun_AscNumber.MoveByte(un_Par.CN_st_Message_ComPar.CN_st_Message_Phone.CentrMessPhone1,
		ptst_AgreeOn_Agree_Par->CenPhone,
		sizeof(un_Par.CN_st_Message_ComPar.CN_st_Message_Phone.CentrMessPhone1));
		CN_st_Fun_File.WriteRecoder(CN_st_File_fd.MessageParfd,0,&un_Par.CN_st_Message_ComPar);
	}
	else if(Space==De_AgreeOn_SetPar_State_SetAPN)					//����APN����
	{	CN_st_Fun_File.ReadRecoder(CN_st_File_fd.GprsParfd,0,&un_Par.CN_st_Gprs_ComPar);
		CN_st_Fun_AscNumber.MoveByte(un_Par.CN_st_Gprs_ComPar.CN_st_Gprs_IPNet.APN,ptst_AgreeOn_Agree_Par->APN,
		sizeof(ptst_AgreeOn_Agree_Par->APN));
		CN_st_Fun_File.WriteRecoder(CN_st_File_fd.GprsParfd,0,&un_Par.CN_st_Gprs_ComPar);
	}
	else if(Space==De_AgreeOn_SetPar_State_SetMastIP)				//����������IP
	{	CN_st_Fun_File.ReadRecoder(CN_st_File_fd.GprsParfd,0,&un_Par.CN_st_Gprs_ComPar);
		un_Par.CN_st_Gprs_ComPar.CN_Mast_st_Gprs_IP.IP=ptst_AgreeOn_Agree_Par->MastIP;
		CN_st_Fun_File.WriteRecoder(CN_st_File_fd.GprsParfd,0,&un_Par.CN_st_Gprs_ComPar);
	}
	else if(Space==De_AgreeOn_SetPar_State_SetMastDomainName)		//����������
	{	CN_st_Fun_File.ReadRecoder(CN_st_File_fd.GprsParfd,0,&un_Par.CN_st_Gprs_ComPar);
		CN_st_Fun_AscNumber.MoveByte(un_Par.CN_st_Gprs_ComPar.CN_Mast_st_Gprs_IP.DomainName,
		ptst_AgreeOn_Agree_Par->MastDomainName,sizeof(ptst_AgreeOn_Agree_Par->MastDomainName));
		CN_st_Fun_File.WriteRecoder(CN_st_File_fd.GprsParfd,0,&un_Par.CN_st_Gprs_ComPar);
	}
	else if(Space==De_AgreeOn_SetPar_State_SetReserveIP)			//���ø�����IP
	{	CN_st_Fun_File.ReadRecoder(CN_st_File_fd.GprsParfd,0,&un_Par.CN_st_Gprs_ComPar);
		un_Par.CN_st_Gprs_ComPar.CN_Reserve_st_Gprs_IP.IP=ptst_AgreeOn_Agree_Par->ReserveIP;
		CN_st_Fun_File.WriteRecoder(CN_st_File_fd.GprsParfd,0,&un_Par.CN_st_Gprs_ComPar);
	}
	else if(Space==De_AgreeOn_SetPar_State_SetReserveDomainName)	//�������ø�����
	{	CN_st_Fun_File.ReadRecoder(CN_st_File_fd.GprsParfd,0,&un_Par.CN_st_Gprs_ComPar);
		CN_st_Fun_AscNumber.MoveByte(un_Par.CN_st_Gprs_ComPar.CN_Reserve_st_Gprs_IP.DomainName,
		ptst_AgreeOn_Agree_Par->ReserveDomainName,sizeof(ptst_AgreeOn_Agree_Par->ReserveDomainName));
		CN_st_Fun_File.WriteRecoder(CN_st_File_fd.GprsParfd,0,&un_Par.CN_st_Gprs_ComPar);
	}
	else if(Space==De_AgreeOn_SetPar_State_SetCenPort)				//�������Ķ˿ں�
	{	CN_st_Fun_File.ReadRecoder(CN_st_File_fd.GprsParfd,0,&un_Par.CN_st_Gprs_ComPar);
		un_Par.CN_st_Gprs_ComPar.CenPort=ptst_AgreeOn_Agree_Par->CenPort;
		CN_st_Fun_File.WriteRecoder(CN_st_File_fd.GprsParfd,0,&un_Par.CN_st_Gprs_ComPar);
	}
	else if(Space==De_AgreeOn_SetPar_State_SetUseName)				//�����û���
	{ 	CN_st_Fun_File.ReadRecoder(CN_st_File_fd.GprsParfd,0,&un_Par.CN_st_Gprs_ComPar);
		CN_st_Fun_AscNumber.MoveByte(un_Par.CN_st_Gprs_ComPar.CN_st_Gprs_IPNet.Use,
		ptst_AgreeOn_Agree_Par->UseName,sizeof(ptst_AgreeOn_Agree_Par->UseName));
		CN_st_Fun_File.WriteRecoder(CN_st_File_fd.GprsParfd,0,&un_Par.CN_st_Gprs_ComPar);
	}
	else if(Space==De_AgreeOn_SetPar_State_SetUsePass)				//���ò�������
	{ 	CN_st_Fun_File.ReadRecoder(CN_st_File_fd.GprsParfd,0,&un_Par.CN_st_Gprs_ComPar);
		CN_st_Fun_AscNumber.MoveByte(un_Par.CN_st_Gprs_ComPar.CN_st_Gprs_IPNet.PassWord,
		ptst_AgreeOn_Agree_Par->UsePass,sizeof(ptst_AgreeOn_Agree_Par->UsePass));
		CN_st_Fun_File.WriteRecoder(CN_st_File_fd.GprsParfd,0,&un_Par.CN_st_Gprs_ComPar);
	}
	else if(Space==De_AgreeOn_SetPar_State_SetDevHeart)		 		//�ն��Ϸ��������
	{	CN_st_Fun_File.ReadRecoder(CN_st_File_fd.GprsParfd,0,&un_Par.CN_st_Gprs_ComPar);
		un_Par.CN_st_Gprs_ComPar.CN_st_Gprs_BasicPar.DeviceHeart=ptst_AgreeOn_Agree_Par->DevHeart;
		CN_st_Fun_File.WriteRecoder(CN_st_File_fd.GprsParfd,0,&un_Par.CN_st_Gprs_ComPar);
	}	
	else if(Space==De_AgreeOn_SetPar_State_SetCentHeart)			//�����·��������
	{	CN_st_Fun_File.ReadRecoder(CN_st_File_fd.GprsParfd,0,&un_Par.CN_st_Gprs_ComPar);
		un_Par.CN_st_Gprs_ComPar.CN_st_Gprs_BasicPar.CentrHeart=ptst_AgreeOn_Agree_Par->CentHeart;
	 	CN_st_Fun_File.WriteRecoder(CN_st_File_fd.GprsParfd,0,&un_Par.CN_st_Gprs_ComPar);			
	}
	else if(Space==De_AgreeOn_SetPar_State_SetComMod)				//����ͨѶ��ʽ
	{	CN_st_Fun_File.ReadRecoder(CN_st_File_fd.Parameterfd,0,&un_Par.CN_st_Parameter_Table);
		un_Par.CN_st_Parameter_Table.ComMod=ptst_AgreeOn_Agree_Par->ComMod;
		CN_st_Fun_File.WriteRecoder(CN_st_File_fd.Parameterfd,0,&un_Par.CN_st_Parameter_Table);
	}
	else if(Space==De_AgreeOn_SetPar_State_SetIPRepeat)				//Ip�ؼ�ָ���ط�����
	{	CN_st_Fun_File.ReadRecoder(CN_st_File_fd.GprsParfd,0,&un_Par.CN_st_Gprs_ComPar);
	   	un_Par.CN_st_Gprs_ComPar.CN_st_Gprs_BasicPar.Repeat=ptst_AgreeOn_Agree_Par->IPRepeat;
	   	CN_st_Fun_File.WriteRecoder(CN_st_File_fd.GprsParfd,0,&un_Par.CN_st_Gprs_ComPar);
	}
	else if(Space==De_AgreeOn_SetPar_State_SetIPRepeatTime)		   //IP�ؼ�ָ���ط����ʱ��
	{	CN_st_Fun_File.ReadRecoder(CN_st_File_fd.GprsParfd,0,&un_Par.CN_st_Gprs_ComPar);
	   	un_Par.CN_st_Gprs_ComPar.CN_st_Gprs_BasicPar.RepeatTime=ptst_AgreeOn_Agree_Par->IPRepeatTime;
	   	CN_st_Fun_File.WriteRecoder(CN_st_File_fd.GprsParfd,0,&un_Par.CN_st_Gprs_ComPar);
	}
	else if(Space==De_AgreeOn_SetPar_State_SetMessageRepeat)		//Message�ؼ�ָ���ط�����
	{	CN_st_Fun_File.ReadRecoder(CN_st_File_fd.MessageParfd,0,&un_Par.CN_st_Message_ComPar);
	   	un_Par.CN_st_Message_ComPar.CN_st_Message_BasicPar.Repeat=
		ptst_AgreeOn_Agree_Par->MessageRepeat;
	   	CN_st_Fun_File.WriteRecoder(CN_st_File_fd.MessageParfd,0,&un_Par.CN_st_Message_ComPar);
	}
	else if(Space==De_AgreeOn_SetPar_State_SetMessageRepeatTimer)	//Message Timer �ط�ʱ��
	{	CN_st_Fun_File.ReadRecoder(CN_st_File_fd.MessageParfd,0,&un_Par.CN_st_Message_ComPar);
	   	un_Par.CN_st_Message_ComPar.CN_st_Message_BasicPar.
		RepeatTime=ptst_AgreeOn_Agree_Par->MessageRepeatTimer;
	   	CN_st_Fun_File.WriteRecoder(CN_st_File_fd.MessageParfd,0,&un_Par.CN_st_Message_ComPar);
	}
	else if(Space==De_AgreeOn_SetPar_State_SetIPTransSms)			//Message��IP֮���л�ʱ��
	{	CN_st_Fun_File.ReadRecoder(CN_st_File_fd.Parameterfd,0,&un_Par.CN_st_Parameter_Table);
	   	un_Par.CN_st_Parameter_Table.IPTransMessage=ptst_AgreeOn_Agree_Par->IPTransSms;
	   	CN_st_Fun_File.WriteRecoder(CN_st_File_fd.Parameterfd,0,&un_Par.CN_st_Parameter_Table);
	}
	else if(Space==De_AgreeOn_SetPar_State_SetDataLog)				//������־�洢
	{	CN_st_Fun_File.ReadRecoder(CN_st_File_fd.Parameterfd,0,&un_Par.CN_st_Parameter_Table);
		CN_st_Fun_AscNumber.MoveByte(un_Par.CN_st_Parameter_Table.CN_st_Data_Access.DataLog,
		ptst_AgreeOn_Agree_Par->DataLog,sizeof(ptst_AgreeOn_Agree_Par->DataLog));
		CN_st_Fun_File.WriteRecoder(CN_st_File_fd.Parameterfd,0,&un_Par.CN_st_Parameter_Table);	
	}
	else if(Space==De_AgreeOn_SetPar_State_SetDataScotomaLog)		//ä����������
	{	CN_st_Fun_File.ReadRecoder(CN_st_File_fd.Parameterfd,0,&un_Par.CN_st_Parameter_Table);
		CN_st_Fun_AscNumber.MoveByte(un_Par.CN_st_Parameter_Table.CN_st_Data_Access.ScotomaLog,
		ptst_AgreeOn_Agree_Par->DataScotomaLog,sizeof(ptst_AgreeOn_Agree_Par->DataScotomaLog));	
		CN_st_Fun_File.WriteRecoder(CN_st_File_fd.Parameterfd,0,&un_Par.CN_st_Parameter_Table);
	}
	else if(Space==De_AgreeOn_SetPar_State_SetParLoad)				//�ϴ���������
	{	CN_st_Fun_File.ReadRecoder(CN_st_File_fd.WorkParfd,0,&un_Par.CN_st_File_WorkPar);
		for(i=0;i<De_CN_Ba_WordPar_Number;i++)
		{	un_Par.CN_st_File_WorkPar.CN_st_File_WorkParVal[i].YesOnON=De_WordPar_Close;
			if(ptst_AgreeOn_Agree_Par->ParLoad[i]==De_WordPar_Open)
				un_Par.CN_st_File_WorkPar.CN_st_File_WorkParVal[i].YesOnON=De_WordPar_Open;	
		}
		CN_st_Fun_File.WriteRecoder(CN_st_File_fd.WorkParfd,0,&un_Par.CN_st_File_WorkPar);
	}
	else if(Space==De_AgreeOn_SetPar_State_SetWireLessPar)			//�������߲���
	{	CN_st_Fun_File.ReadRecoder(CN_st_File_fd.WorkParfd,0,&un_Par.CN_st_File_WorkPar);
		for(i=0;i<sizeof(CN_LessPar)/sizeof(uint32 );i++)
		{ 	Val=(uint32 *)((uint32 )&un_Par+(uint32 )CN_LessPar[i]);
			*Val=ptst_AgreeOn_Agree_Par->WireLessPar[i];
			un_Par.CN_st_File_WorkPar.CN_st_File_WorkParVal[i].Adree=*Val;
		}	
		CN_st_Fun_File.WriteRecoder(CN_st_File_fd.WorkParfd,0,&un_Par.CN_st_File_WorkPar);	
	}
	else if(Space==De_AgreeOn_SetPar_State_SetDePassWord)  			//�����ն�����
	{	CN_st_Fun_File.ReadRecoder(CN_st_File_fd.GreenParfd,0,&un_Par.CN_st_File_GreenPar);
		un_Par.CN_st_File_GreenPar.PassWord=ptst_AgreeOn_Agree_Par->DePassWord;		
		CN_st_Fun_File.WriteRecoder(CN_st_File_fd.GreenParfd,0,&un_Par.CN_st_File_GreenPar);
	}
	else if(Space==De_AgreeOn_SetPar_State_SetAccTimer)				//����ACC�ۼ�ʱ��
	{	CN_st_Fun_File.ReadRecoder(CN_st_File_fd.AccTimerfd,0,&un_Par.CN_st_AccTimer);
		un_Par.CN_st_AccTimer.AccTimer=ptst_AgreeOn_Agree_Par->AccTimer;		
		CN_st_Fun_File.WriteRecoder(CN_st_File_fd.AccTimerfd,0,&un_Par.CN_st_AccTimer);
	}
	else if(Space==De_AgreeOn_SetPar_State_SetRunLen) 				//�����������
	{	CN_st_Fun_File.ReadRecoder(CN_st_File_fd.Gpsfd,0,&un_Par.CN_st_File_Gps);
		un_Par.CN_st_File_Gps.Milage=ptst_AgreeOn_Agree_Par->RunLen;		
		CN_st_Fun_File.WriteRecoder(CN_st_File_fd.Gpsfd,0,&un_Par.CN_st_File_Gps);
	}
	else if(Space==De_AgreeOn_SetPar_State_SetPerPuse)				//����ÿ�ܵ�������
	{	CN_st_Fun_File.ReadRecoder(CN_st_File_fd.Parameterfd,0,&un_Par.CN_st_Parameter_Table);
		un_Par.CN_st_Parameter_Table.CN_st_File_Car_Par.PerPuse=ptst_AgreeOn_Agree_Par->PerPuse; 	
		CN_st_Fun_File.WriteRecoder(CN_st_File_fd.Parameterfd,0,&un_Par.CN_st_Parameter_Table);

	}
	else if(Space==De_AgreeOn_SetPar_State_SetCarFeature)			//���ó�������
	{	CN_st_Fun_File.ReadRecoder(CN_st_File_fd.Parameterfd,0,&un_Par.CN_st_Parameter_Table);
		un_Par.CN_st_Parameter_Table.CN_st_File_Car_Par.Feature=ptst_AgreeOn_Agree_Par->CarFeature; 	
		CN_st_Fun_File.WriteRecoder(CN_st_File_fd.Parameterfd,0,&un_Par.CN_st_Parameter_Table);
	}
	else if(Space==De_AgreeOn_SetPar_State_SetTakeLCD)				//���ó����Ƿ�װ����
	{	CN_st_Fun_File.ReadRecoder(CN_st_File_fd.Parameterfd,0,&un_Par.CN_st_Parameter_Table);
		un_Par.CN_st_Parameter_Table.DisLCD=ptst_AgreeOn_Agree_Par->TakeLCD; 	
		CN_st_Fun_File.WriteRecoder(CN_st_File_fd.Parameterfd,0,&un_Par.CN_st_Parameter_Table);
	}
	else if(Space==De_AgreeOn_SetPar_State_SetOilFrequency)			////������������Ƶ��
   	{	CN_st_Fun_File.ReadRecoder(CN_st_File_fd.Parameterfd,0,&un_Par.CN_st_Parameter_Table);
		un_Par.CN_st_Parameter_Table.CN_st_File_Car_Par.OilFrequency=ptst_AgreeOn_Agree_Par->OilFrequency; 	
		CN_st_Fun_File.WriteRecoder(CN_st_File_fd.Parameterfd,0,&un_Par.CN_st_Parameter_Table);
	}
	else if(Space==De_AgreeOn_SetPar_State_SetSleepTimer) 			//��������ʱ��
	{	CN_st_Fun_File.ReadRecoder(CN_st_File_fd.Parameterfd,0,&un_Par.CN_st_Parameter_Table);
		un_Par.CN_st_Parameter_Table.CN_st_Sleep_Par.GpsTimer=ptst_AgreeOn_Agree_Par->SleepTimer; 	
		CN_st_Fun_File.WriteRecoder(CN_st_File_fd.Parameterfd,0,&un_Par.CN_st_Parameter_Table);
	}
	else if(Space==De_AgreeOn_SetPar_State_SetCloseTimer)		   //���ùػ�ʱ��
	{	CN_st_Fun_File.ReadRecoder(CN_st_File_fd.Parameterfd,0,&un_Par.CN_st_Parameter_Table);
		un_Par.CN_st_Parameter_Table.CN_st_Sleep_Par.GprsTimer=ptst_AgreeOn_Agree_Par->CloseTimer; 	
		CN_st_Fun_File.WriteRecoder(CN_st_File_fd.Parameterfd,0,&un_Par.CN_st_Parameter_Table);
	}
	else if(Space==De_AgreeOn_SetPar_State_SetLogMess)		   		//���õ�¼��ʾ
	{	CN_st_Fun_File.ReadRecoder(CN_st_File_fd.Parameterfd,0,&un_Par.CN_st_Parameter_Table);
		un_Par.CN_st_Parameter_Table.DisLogin=ptst_AgreeOn_Agree_Par->LogMess; 	
		CN_st_Fun_File.WriteRecoder(CN_st_File_fd.Parameterfd,0,&un_Par.CN_st_Parameter_Table);
	}
	else if(Space==De_AgreeOn_SetPar_State_SetTaskVid)		   		//���õ�¼��ʾ
	{	CN_st_Fun_File.ReadRecoder(CN_st_File_fd.Parameterfd,0,&un_Par.CN_st_Parameter_Table);
		un_Par.CN_st_Parameter_Table.DisVid=ptst_AgreeOn_Agree_Par->TaskVid; 	
		CN_st_Fun_File.WriteRecoder(CN_st_File_fd.Parameterfd,0,&un_Par.CN_st_Parameter_Table);
	}
	else if(Space==De_AgreeOn_SetPar_State_SetHighSpeed)			//���ó��ٱ���
	{	CN_st_Fun_File.ReadRecoder(CN_st_File_fd.Parameterfd,0,&un_Par.CN_st_Parameter_Table);
		CN_st_Fun_AscNumber.MoveByte(&un_Par.CN_st_Parameter_Table.CN_st_Sum_Waring.HighSpeed,
		&ptst_AgreeOn_Agree_Par->CN_High_st_Waring_Par,sizeof(st_Waring_Par));
		CN_st_Fun_File.WriteRecoder(CN_st_File_fd.Parameterfd,0,&un_Par.CN_st_Parameter_Table);
	}
	else if(Space==De_AgreeOn_SetPar_State_SetLowSpeed)				//���õ��ٱ���
	{	CN_st_Fun_File.ReadRecoder(CN_st_File_fd.Parameterfd,0,&un_Par.CN_st_Parameter_Table);
		CN_st_Fun_AscNumber.MoveByte(&un_Par.CN_st_Parameter_Table.CN_st_Sum_Waring.LowSpeed,
		&ptst_AgreeOn_Agree_Par->CN_Low_st_Waring_Par,sizeof(st_Waring_Par));
		CN_st_Fun_File.WriteRecoder(CN_st_File_fd.Parameterfd,0,&un_Par.CN_st_Parameter_Table);
	}
	else if(Space==De_AgreeOn_SetPar_State_SetLowVlt)				//���õ͵�ѹ����
	{	CN_st_Fun_File.ReadRecoder(CN_st_File_fd.Parameterfd,0,&un_Par.CN_st_Parameter_Table);
		CN_st_Fun_AscNumber.MoveByte(&un_Par.CN_st_Parameter_Table.CN_st_Sum_Waring.Voltage,
		&ptst_AgreeOn_Agree_Par->CN_Vo_st_Waring_Par,sizeof(st_Waring_Par));
		CN_st_Fun_File.WriteRecoder(CN_st_File_fd.Parameterfd,0,&un_Par.CN_st_Parameter_Table);
	}
	else if(Space==De_AgreeOn_SetPar_State_SetVidType)				//������������
	{	CN_st_Fun_File.ReadRecoder(CN_st_File_fd.Parameterfd,0,&un_Par.CN_st_Parameter_Table);
		CN_st_Fun_AscNumber.MoveByte(&un_Par.CN_st_Parameter_Table.CN_st_VidType,
		&ptst_AgreeOn_Agree_Par->CN_st_VidType,sizeof(st_VidType));
		CN_st_Fun_File.WriteRecoder(CN_st_File_fd.Parameterfd,0,&un_Par.CN_st_Parameter_Table);
	}
	else if(Space==De_AgreeOn_SetPar_State_SetOrderFrmTimer)		//����ԤԼ����ʱ��
	{	CN_st_Fun_File.ReadRecoder(CN_st_File_fd.Parameterfd,0,&un_Par.CN_st_Parameter_Table);
		un_Par.CN_st_Parameter_Table.FrmTimer=ptst_AgreeOn_Agree_Par->OrderFrmTimer;
		CN_st_Fun_File.WriteRecoder(CN_st_File_fd.Parameterfd,0,&un_Par.CN_st_Parameter_Table);
	}
}



