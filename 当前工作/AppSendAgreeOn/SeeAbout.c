#include "..\Control\GpsAndMileage\GpsAndMileage.h"
#define De_Erro_AppSendAgreeOn_SeeAbout					1
#define De_Suc_AppSendAgreeOn							0
typedef struct
{	uint32 *Val;
	uint8 Space;
}st_Less_Space;
const st_Less_Space CN_st_Less_Space[]=
{	{&(((st_File_WorkPar	*)(NULL))->CN_st_File_WorkParVal[16].Adree),16},
	{&(((st_File_WorkPar	*)(NULL))->CN_st_File_WorkParVal[17].Adree),17},
	{&(((st_File_WorkPar	*)(NULL))->CN_st_File_WorkParVal[18].Adree),18},
	{&(((st_File_WorkPar	*)(NULL))->CN_st_File_WorkParVal[19].Adree),19},
	{&(((st_File_WorkPar	*)(NULL))->CN_st_File_WorkParVal[20].Adree),20},
	{&(((st_File_WorkPar	*)(NULL))->CN_st_File_WorkParVal[21].Adree),21},
	{&(((st_File_WorkPar	*)(NULL))->CN_st_File_WorkParVal[32].Adree),32},
	{&(((st_File_WorkPar	*)(NULL))->CN_st_File_WorkParVal[33].Adree),33},
	{&(((st_File_WorkPar	*)(NULL))->CN_st_File_WorkParVal[34].Adree),34},
	{&(((st_File_WorkPar	*)(NULL))->CN_st_File_WorkParVal[35].Adree),35}
};
static uint16 GetPar(st_AgreeOn_Agree_Par_Cut	*ptst_AgreeOn_Agree_Par_Cut,uint8 Space);

static uint16 GetPar(st_AgreeOn_Agree_Par_Cut	*ptst_AgreeOn_Agree_Par,uint8 Space)
{	union 
	{	st_File_GreenPar	CN_st_File_GreenPar;
		st_Phone_Basic		CN_st_Phone_Basic;
		st_Message_ComPar	CN_st_Message_ComPar;
		st_Gprs_ComPar		CN_st_Gprs_ComPar;
		st_Parameter_Table	CN_st_Parameter_Table;
		st_AccTimer			CN_st_AccTimer;
		st_File_Gps			CN_st_File_Gps;
		st_File_Basic		CN_st_File_Basic;
		st_File_Menum		CN_st_File_Menum;
		st_AgreeOn_Phone_Par	CN_st_AgreeOn_Phone_Par;
		st_AgreeOn_Driver	CN_st_AgreeOn_Driver;
		st_File_WorkPar		CN_st_File_WorkPar;	
	}un_Par;
	uint32 *Val;
	uint16 i,Cuit;
	if(Space==De_AgreeOn_SetPar_State_SetGreenPar)
	{	CN_st_Fun_File.ReadRecoder(CN_st_File_fd.GreenParfd,0,&un_Par.CN_st_File_GreenPar);
		ptst_AgreeOn_Agree_Par->GreenPar=un_Par.CN_st_File_GreenPar.Integral;		
	}
	else if(Space==De_AgreeOn_SetPar_State_SetGreenWord)
	{	CN_st_Fun_File.ReadRecoder(CN_st_File_fd.GreenParfd,0,&un_Par.CN_st_File_GreenPar);
		CN_st_Fun_AscNumber.MoveByte(ptst_AgreeOn_Agree_Par->GreenWord,un_Par.CN_st_File_GreenPar.GreenWord,
		sizeof(ptst_AgreeOn_Agree_Par->GreenWord));
	}
	else if(Space==De_AgreeOn_SetPar_State_SetListePhone)	//���ü�������
	{	CN_st_Fun_File.ReadRecoder(CN_st_File_fd.Phonefd,0,&un_Par.CN_st_Phone_Basic);
		CN_st_Fun_AscNumber.MoveByte(ptst_AgreeOn_Agree_Par->ListePhone,un_Par.CN_st_Phone_Basic.WatchPhone,
		sizeof(ptst_AgreeOn_Agree_Par->ListePhone));
	}
	else if(Space==De_AgreeOn_SetPar_State_SetResetPhone)		//���õ绰��λ
	{	CN_st_Fun_File.ReadRecoder(CN_st_File_fd.Phonefd,0,&un_Par.CN_st_Phone_Basic);
		CN_st_Fun_AscNumber.MoveByte(ptst_AgreeOn_Agree_Par->ResetPhone,un_Par.CN_st_Phone_Basic.RestPhone,
		sizeof(ptst_AgreeOn_Agree_Par->ResetPhone));
	}
	else if(Space==De_AgreeOn_SetPar_State_SetCerSevPhone)			//���ö������ķ������
	{	CN_st_Fun_File.ReadRecoder(CN_st_File_fd.MessageParfd,0,&un_Par.CN_st_Message_ComPar);
		CN_st_Fun_AscNumber.MoveByte(ptst_AgreeOn_Agree_Par->CenPhone,
		un_Par.CN_st_Message_ComPar.CN_st_Message_Phone.CenMessageSev,		  
		sizeof(ptst_AgreeOn_Agree_Par->CerSevPhone));
	}
	else if(Space==De_AgreeOn_SetPar_State_SetCenPhone)			//���ö������ķ������
	{	CN_st_Fun_File.ReadRecoder(CN_st_File_fd.MessageParfd,0,&un_Par.CN_st_Message_ComPar);
		CN_st_Fun_AscNumber.MoveByte(ptst_AgreeOn_Agree_Par->CenPhone,
		un_Par.CN_st_Message_ComPar.CN_st_Message_Phone.CentrMessPhone1,
		sizeof(ptst_AgreeOn_Agree_Par->CenPhone));
	}
	else if(Space==De_AgreeOn_SetPar_State_SetAPN)				//����APN����
	{	CN_st_Fun_File.ReadRecoder(CN_st_File_fd.GprsParfd,0,&un_Par.CN_st_Gprs_ComPar);
		CN_st_Fun_AscNumber.MoveByte(ptst_AgreeOn_Agree_Par->APN,un_Par.CN_st_Gprs_ComPar.CN_st_Gprs_IPNet.APN,
		sizeof(ptst_AgreeOn_Agree_Par->APN));
	}
	else if(Space==De_AgreeOn_SetPar_State_SetMastIP)			//����������IP
	{	CN_st_Fun_File.ReadRecoder(CN_st_File_fd.GprsParfd,0,&un_Par.CN_st_Gprs_ComPar);
		ptst_AgreeOn_Agree_Par->MastIP=un_Par.CN_st_Gprs_ComPar.CN_Mast_st_Gprs_IP.IP;
	}
	else if(Space==De_AgreeOn_SetPar_State_SetMastDomainName)		//����������
	{	CN_st_Fun_File.ReadRecoder(CN_st_File_fd.GprsParfd,0,&un_Par.CN_st_Gprs_ComPar);
		CN_st_Fun_AscNumber.MoveByte(ptst_AgreeOn_Agree_Par->MastDomainName,
		un_Par.CN_st_Gprs_ComPar.CN_Mast_st_Gprs_IP.DomainName,sizeof(ptst_AgreeOn_Agree_Par->MastDomainName));
	}
	else if(Space==De_AgreeOn_SetPar_State_SetReserveIP)			//���ø�����IP
	{	CN_st_Fun_File.ReadRecoder(CN_st_File_fd.GprsParfd,0,&un_Par.CN_st_Gprs_ComPar);
		ptst_AgreeOn_Agree_Par->ReserveIP=un_Par.CN_st_Gprs_ComPar.CN_Reserve_st_Gprs_IP.IP;
	}
	else if(Space==De_AgreeOn_SetPar_State_SetReserveDomainName)	//�������ø�����
	{	CN_st_Fun_File.ReadRecoder(CN_st_File_fd.GprsParfd,0,&un_Par.CN_st_Gprs_ComPar);
		CN_st_Fun_AscNumber.MoveByte(ptst_AgreeOn_Agree_Par->ReserveDomainName,
		un_Par.CN_st_Gprs_ComPar.CN_Reserve_st_Gprs_IP.DomainName,sizeof(ptst_AgreeOn_Agree_Par->ReserveDomainName));
	}
	else if(Space==De_AgreeOn_SetPar_State_SetCenPort)				//�������Ķ˿ں�
	{	CN_st_Fun_File.ReadRecoder(CN_st_File_fd.GprsParfd,0,&un_Par.CN_st_Gprs_ComPar);
		ptst_AgreeOn_Agree_Par->CenPort=un_Par.CN_st_Gprs_ComPar.CenPort;
	}
	else if(Space==De_AgreeOn_SetPar_State_SetUseName)				//�����û���
	{ 	CN_st_Fun_File.ReadRecoder(CN_st_File_fd.GprsParfd,0,&un_Par.CN_st_Gprs_ComPar);
		CN_st_Fun_AscNumber.MoveByte(ptst_AgreeOn_Agree_Par->UseName,
		un_Par.CN_st_Gprs_ComPar.CN_st_Gprs_IPNet.Use,sizeof(ptst_AgreeOn_Agree_Par->UseName));
	}
	else if(Space==De_AgreeOn_SetPar_State_SetUseName)				//�����û���
	{ 	CN_st_Fun_File.ReadRecoder(CN_st_File_fd.GprsParfd,0,&un_Par.CN_st_Gprs_ComPar);
		CN_st_Fun_AscNumber.MoveByte(un_Par.CN_st_Gprs_ComPar.CN_st_Gprs_IPNet.Use,
		ptst_AgreeOn_Agree_Par->UseName,sizeof(ptst_AgreeOn_Agree_Par->UseName));
		CN_st_Fun_File.WriteRecoder(CN_st_File_fd.GprsParfd,0,&un_Par.CN_st_Gprs_ComPar);
	}
	else if(Space==De_AgreeOn_SetPar_State_SetUsePass)				//���ò�������
	{ 	CN_st_Fun_File.ReadRecoder(CN_st_File_fd.GprsParfd,0,&un_Par.CN_st_Gprs_ComPar);
		CN_st_Fun_AscNumber.MoveByte(ptst_AgreeOn_Agree_Par->UsePass,
		un_Par.CN_st_Gprs_ComPar.CN_st_Gprs_IPNet.PassWord,sizeof(ptst_AgreeOn_Agree_Par->UsePass));
	}
	else if(Space==De_AgreeOn_SetPar_State_SetDevHeart)		 		//�ն��Ϸ��������
	{	CN_st_Fun_File.ReadRecoder(CN_st_File_fd.GprsParfd,0,&un_Par.CN_st_Gprs_ComPar);
		ptst_AgreeOn_Agree_Par->DevHeart=un_Par.CN_st_Gprs_ComPar.CN_st_Gprs_BasicPar.DeviceHeart;
	}	
	else if(Space==De_AgreeOn_SetPar_State_SetCentHeart)			//�����·��������
	{	CN_st_Fun_File.ReadRecoder(CN_st_File_fd.GprsParfd,0,&un_Par.CN_st_Gprs_ComPar);
		ptst_AgreeOn_Agree_Par->CentHeart=un_Par.CN_st_Gprs_ComPar.CN_st_Gprs_BasicPar.CentrHeart;			
	}
	else if(Space==De_AgreeOn_SetPar_State_SetComMod)				//����ͨѶ��ʽ
	{	CN_st_Fun_File.ReadRecoder(CN_st_File_fd.Parameterfd,0,&un_Par.CN_st_Parameter_Table);
		ptst_AgreeOn_Agree_Par->ComMod=un_Par.CN_st_Parameter_Table.ComMod;
	}
	else if(Space==De_AgreeOn_SetPar_State_SetIPRepeat)				//Ip�ؼ�ָ���ط�����
	{	CN_st_Fun_File.ReadRecoder(CN_st_File_fd.GprsParfd,0,&un_Par.CN_st_Gprs_ComPar);
	   	ptst_AgreeOn_Agree_Par->IPRepeat=un_Par.CN_st_Gprs_ComPar.CN_st_Gprs_BasicPar.Repeat;
	}
	else if(Space==De_AgreeOn_SetPar_State_SetIPRepeatTime)		   //IP�ؼ�ָ���ط����ʱ��
	{	CN_st_Fun_File.ReadRecoder(CN_st_File_fd.GprsParfd,0,&un_Par.CN_st_Gprs_ComPar);
	   	ptst_AgreeOn_Agree_Par->IPRepeatTime=un_Par.CN_st_Gprs_ComPar.CN_st_Gprs_BasicPar.RepeatTime;
	}
	else if(Space==De_AgreeOn_SetPar_State_SetMessageRepeat)		//Message�ؼ�ָ���ط�����
	{	CN_st_Fun_File.ReadRecoder(CN_st_File_fd.MessageParfd,0,&un_Par.CN_st_Message_ComPar);
	   	ptst_AgreeOn_Agree_Par->MessageRepeat=un_Par.CN_st_Message_ComPar.CN_st_Message_BasicPar.Repeat;
	}
	else if(Space==De_AgreeOn_SetPar_State_SetMessageRepeatTimer)	//Message Timer �ط�ʱ��
	{	CN_st_Fun_File.ReadRecoder(CN_st_File_fd.MessageParfd,0,&un_Par.CN_st_Message_ComPar);
	   	ptst_AgreeOn_Agree_Par->MessageRepeatTimer=un_Par.CN_st_Message_ComPar.CN_st_Message_BasicPar.RepeatTime;
	}
	else if(Space==De_AgreeOn_SetPar_State_SetIPTransSms)			//Message��IP֮���л�ʱ��
	{	CN_st_Fun_File.ReadRecoder(CN_st_File_fd.Parameterfd,0,&un_Par.CN_st_Parameter_Table);
	   	ptst_AgreeOn_Agree_Par->IPTransSms=un_Par.CN_st_Parameter_Table.IPTransMessage;
	}
	else if(Space==De_AgreeOn_SetPar_State_SetDataLog)				//������־�洢
	{	CN_st_Fun_File.ReadRecoder(CN_st_File_fd.Parameterfd,0,&un_Par.CN_st_Parameter_Table);
		CN_st_Fun_AscNumber.MoveByte(ptst_AgreeOn_Agree_Par->DataLog,
		un_Par.CN_st_Parameter_Table.CN_st_Data_Access.DataLog,sizeof(ptst_AgreeOn_Agree_Par->DataLog));
	}
	else if(Space==De_AgreeOn_SetPar_State_SetDataScotomaLog)		//ä����������
	{	CN_st_Fun_File.ReadRecoder(CN_st_File_fd.Parameterfd,0,&un_Par.CN_st_Parameter_Table);
		CN_st_Fun_AscNumber.MoveByte(ptst_AgreeOn_Agree_Par->DataScotomaLog,
		un_Par.CN_st_Parameter_Table.CN_st_Data_Access.ScotomaLog,sizeof(ptst_AgreeOn_Agree_Par->DataScotomaLog));	
	}
	else if(Space==De_AgreeOn_SetPar_State_SetParLoad)				//�ϴ���������
	{	CN_st_Fun_File.ReadRecoder(CN_st_File_fd.WorkParfd,0,&un_Par.CN_st_File_WorkPar);
		for(i=0;i<De_CN_Ba_WordPar_Number;i++)
		{	ptst_AgreeOn_Agree_Par->ParLoad[i]=De_WordPar_Close;
			if(un_Par.CN_st_File_WorkPar.CN_st_File_WorkParVal[i].YesOnON==De_WordPar_Open)
				ptst_AgreeOn_Agree_Par->ParLoad[i]=De_WordPar_Open;	
		}
	}
	else if(Space==De_AgreeOn_SetPar_State_SetWireLessPar)			//�������߲���
	{	CN_st_Fun_File.ReadRecoder(CN_st_File_fd.WorkParfd,0,&un_Par.CN_st_File_WorkPar);
		for(i=0;i<sizeof(CN_st_Less_Space)/sizeof(st_Less_Space);i++)
		{ 	Val=(uint32 *)((uint32 )&un_Par+(uint32 )CN_st_Less_Space[i].Val);
			ptst_AgreeOn_Agree_Par->WireLessPar[i]=De_WordPar_NoAdree;
			if(un_Par.CN_st_File_WorkPar.CN_st_File_WorkParVal[CN_st_Less_Space[i].Space].YesOnON==De_WordPar_Open)
			{	
				ptst_AgreeOn_Agree_Par->WireLessPar[i]=*Val;
			
			}	
		}	

	}
	else if(Space==De_AgreeOn_SetPar_State_SetDePassWord)  			//�����ն�����
	{	CN_st_Fun_File.ReadRecoder(CN_st_File_fd.GreenParfd,0,&un_Par.CN_st_File_GreenPar);
		ptst_AgreeOn_Agree_Par->DePassWord=un_Par.CN_st_File_GreenPar.PassWord;		
	}
	else if(Space==De_AgreeOn_SetPar_State_SetAccTimer)				//����ACC�ۼ�ʱ��
	{	CN_st_Fun_File.ReadRecoder(CN_st_File_fd.AccTimerfd,0,&un_Par.CN_st_AccTimer);
		ptst_AgreeOn_Agree_Par->AccTimer=un_Par.CN_st_AccTimer.AccTimer;		
	}
	else if(Space==De_AgreeOn_SetPar_State_SetRunLen) 				//�����������
	{	CN_st_Fun_File.ReadRecoder(CN_st_File_fd.Gpsfd,0,&un_Par.CN_st_File_Gps);
		ptst_AgreeOn_Agree_Par->RunLen=un_Par.CN_st_File_Gps.Milage;		
	}
	else if(Space==De_AgreeOn_SetPar_State_SetPerPuse)				//����ÿ�ܵ�������
	{	CN_st_Fun_File.ReadRecoder(CN_st_File_fd.Parameterfd,0,&un_Par.CN_st_Parameter_Table);
		ptst_AgreeOn_Agree_Par->PerPuse=un_Par.CN_st_Parameter_Table.CN_st_File_Car_Par.PerPuse; 	
	}
	else if(Space==De_AgreeOn_SetPar_State_SetCarFeature)			//���ó�������
	{	CN_st_Fun_File.ReadRecoder(CN_st_File_fd.Parameterfd,0,&un_Par.CN_st_Parameter_Table);
		ptst_AgreeOn_Agree_Par->CarFeature=un_Par.CN_st_Parameter_Table.CN_st_File_Car_Par.Feature; 	
	}
	else if(Space==De_AgreeOn_SetPar_State_SetTakeLCD)				//���ó����Ƿ�װ����
	{	CN_st_Fun_File.ReadRecoder(CN_st_File_fd.Parameterfd,0,&un_Par.CN_st_Parameter_Table);
		ptst_AgreeOn_Agree_Par->TakeLCD=un_Par.CN_st_Parameter_Table.DisLCD; 	
	}
	else if(Space==De_AgreeOn_SetPar_State_SetOilFrequency)			////������������Ƶ��
   	{	CN_st_Fun_File.ReadRecoder(CN_st_File_fd.Parameterfd,0,&un_Par.CN_st_Parameter_Table);
		ptst_AgreeOn_Agree_Par->OilFrequency=un_Par.CN_st_Parameter_Table.CN_st_File_Car_Par.OilFrequency; 	
	}
	else if(Space==De_AgreeOn_SetPar_State_SetSleepTimer) 			//��������ʱ��
	{	CN_st_Fun_File.ReadRecoder(CN_st_File_fd.Parameterfd,0,&un_Par.CN_st_Parameter_Table);
		ptst_AgreeOn_Agree_Par->SleepTimer=un_Par.CN_st_Parameter_Table.CN_st_Sleep_Par.GpsTimer; 	
	}
	else if(Space==De_AgreeOn_SetPar_State_SetCloseTimer)		   //���ùػ�ʱ��
	{	CN_st_Fun_File.ReadRecoder(CN_st_File_fd.Parameterfd,0,&un_Par.CN_st_Parameter_Table);
		ptst_AgreeOn_Agree_Par->CloseTimer=un_Par.CN_st_Parameter_Table.CN_st_Sleep_Par.GprsTimer; 	
	}
	else if(Space==De_AgreeOn_SetPar_State_SetLogMess)		   		//���õ�¼��ʾ
	{	CN_st_Fun_File.ReadRecoder(CN_st_File_fd.Parameterfd,0,&un_Par.CN_st_Parameter_Table);
		ptst_AgreeOn_Agree_Par->LogMess=un_Par.CN_st_Parameter_Table.DisLogin; 	
	}
	else if(Space==De_AgreeOn_SetPar_State_SetTaskVid)		   		//���õ�¼��ʾ
	{	CN_st_Fun_File.ReadRecoder(CN_st_File_fd.Parameterfd,0,&un_Par.CN_st_Parameter_Table);
		ptst_AgreeOn_Agree_Par->TaskVid=un_Par.CN_st_Parameter_Table.DisVid; 	
	}
	else if(Space==De_AgreeOn_SetPar_State_SetHighSpeed)			//���ó��ٱ���
	{	CN_st_Fun_File.ReadRecoder(CN_st_File_fd.Parameterfd,0,&un_Par.CN_st_Parameter_Table);
		CN_st_Fun_AscNumber.MoveByte(&ptst_AgreeOn_Agree_Par->CN_High_st_Waring_Par,
		&un_Par.CN_st_Parameter_Table.CN_st_Sum_Waring.HighSpeed,sizeof(st_Waring_Par));
	}
	else if(Space==De_AgreeOn_SetPar_State_SetLowSpeed)				//���õ��ٱ���
	{	CN_st_Fun_File.ReadRecoder(CN_st_File_fd.Parameterfd,0,&un_Par.CN_st_Parameter_Table);
		CN_st_Fun_AscNumber.MoveByte(&ptst_AgreeOn_Agree_Par->CN_Low_st_Waring_Par,
		&un_Par.CN_st_Parameter_Table.CN_st_Sum_Waring.LowSpeed,sizeof(st_Waring_Par));
	}
	else if(Space==De_AgreeOn_SetPar_State_SetLowVlt)				//���õ͵�ѹ����
	{	CN_st_Fun_File.ReadRecoder(CN_st_File_fd.Parameterfd,0,&un_Par.CN_st_Parameter_Table);
		CN_st_Fun_AscNumber.MoveByte(&ptst_AgreeOn_Agree_Par->CN_Vo_st_Waring_Par,
		&un_Par.CN_st_Parameter_Table.CN_st_Sum_Waring.Voltage,sizeof(st_Waring_Par));
	}
	else if(Space==De_AgreeOn_SetPar_State_SetVidType)				//������������
	{	CN_st_Fun_File.ReadRecoder(CN_st_File_fd.Parameterfd,0,&un_Par.CN_st_Parameter_Table);
		CN_st_Fun_AscNumber.MoveByte(&ptst_AgreeOn_Agree_Par->CN_st_VidType,
		&un_Par.CN_st_Parameter_Table.CN_st_VidType,sizeof(st_VidType));
	}
	else if(Space==De_AgreeOn_SetPar_State_SetOrderFrmTimer)		//����ԤԼ����ʱ��
	{	CN_st_Fun_File.ReadRecoder(CN_st_File_fd.Parameterfd,0,&un_Par.CN_st_Parameter_Table);
		ptst_AgreeOn_Agree_Par->OrderFrmTimer=un_Par.CN_st_Parameter_Table.FrmTimer;
	}
	else if(Space==De_AgreeOn_SetPar_State_SetHardWareEdit)			//Ӳ���汾
	{	CN_st_Fun_File.ReadRecoder(CN_st_File_fd.Basicfd,0,&un_Par.CN_st_File_Basic);
	   	CN_st_Fun_AscNumber.MoveByte(&ptst_AgreeOn_Agree_Par->HardWareEdit,
		&un_Par.CN_st_File_Basic.HardEdition,sizeof(un_Par.CN_st_File_Basic.HardEdition));
	}
	else if(Space==De_AgreeOn_SetPar_State_SetSoftWareEdit)			//����汾
	{	CN_st_Fun_File.ReadRecoder(CN_st_File_fd.Basicfd,0,&un_Par.CN_st_File_Basic);
	   	CN_st_Fun_AscNumber.MoveByte(&ptst_AgreeOn_Agree_Par->SoftWareEdit,
		&un_Par.CN_st_File_Basic.SoftEdition,sizeof(un_Par.CN_st_File_Basic.SoftEdition));
	}
	else if(Space==De_AgreeOn_SetPar_State_SetMachID) 				//�������к�
	{	CN_st_Fun_File.ReadRecoder(CN_st_File_fd.Basicfd,0,&un_Par.CN_st_File_Basic);
	   	CN_st_Fun_AscNumber.MoveByte(&ptst_AgreeOn_Agree_Par->MachID,
		&un_Par.CN_st_File_Basic.MachID,sizeof(un_Par.CN_st_File_Basic.MachID));
	}
	else if(Space==De_AgreeOn_SetPar_State_SetMenum)				//�̶��˵�
	{	Cuit=CN_st_Fun_File.GetJlNum(CN_st_File_fd.Menumfd);
		for(i=0,ptst_AgreeOn_Agree_Par->CN_st_AgreeOn_AmendMenum.Number=0;i<Cuit;i++)
		{	CN_st_Fun_File.ReadRecoder(CN_st_File_fd.Menumfd,i+1,&un_Par.CN_st_File_Menum);
			if(un_Par.CN_st_File_Menum.BackID==0XFF)	
				continue;
			CN_st_Fun_AscNumber.MoveByte(ptst_AgreeOn_Agree_Par->CN_st_AgreeOn_AmendMenum.
			CN_st_AgreeOn_Menum_Infor[ptst_AgreeOn_Agree_Par->CN_st_AgreeOn_AmendMenum.Number].Cut,
			un_Par.CN_st_File_Menum.Cut,sizeof(un_Par.CN_st_File_Menum.Cut));
			ptst_AgreeOn_Agree_Par->CN_st_AgreeOn_AmendMenum.CN_st_AgreeOn_Menum_Infor
			[ptst_AgreeOn_Agree_Par->CN_st_AgreeOn_AmendMenum.Number].BackID=un_Par.CN_st_File_Menum.BackID;
			ptst_AgreeOn_Agree_Par->CN_st_AgreeOn_AmendMenum.CN_st_AgreeOn_Menum_Infor
			[ptst_AgreeOn_Agree_Par->CN_st_AgreeOn_AmendMenum.Number].ID=i+1;
			ptst_AgreeOn_Agree_Par->CN_st_AgreeOn_AmendMenum.Number++;
		}	
	}
	else if(Space==De_AgreeOn_SetPar_State_SetPhone)  				//���õ绰��Ϣ
	{	Cuit=CN_st_Fun_File.GetJlNum(CN_st_File_fd.Menumfd);
		for(i=0,ptst_AgreeOn_Agree_Par->CN_st_AgreeOn_Phone.Number=0;i<Cuit;i++)
		{ 	CN_st_Fun_File.ReadRecoder(CN_st_File_fd.Menumfd,i+1,&un_Par.CN_st_AgreeOn_Phone_Par);
			if(un_Par.CN_st_AgreeOn_Phone_Par.State==0xff)
				continue;
			CN_st_Fun_AscNumber.MoveByte(&ptst_AgreeOn_Agree_Par->CN_st_AgreeOn_Phone.CN_st_AgreeOn_Phone_Par
			[ptst_AgreeOn_Agree_Par->CN_st_AgreeOn_Phone.Number],&un_Par.CN_st_AgreeOn_Phone_Par,
			sizeof(st_AgreeOn_Phone_Par));
			ptst_AgreeOn_Agree_Par->CN_st_AgreeOn_Phone.Number++;
		}				
	}
	else if(Space==De_AgreeOn_SetPar_State_SetConfineCall)										//ͨ������״̬
	{	CN_st_Fun_File.ReadRecoder(CN_st_File_fd.Parameterfd,0,&un_Par.CN_st_Parameter_Table);
		CN_st_Fun_AscNumber.MoveByte(&ptst_AgreeOn_Agree_Par->CN_st_AgreeOn_ConfineCall,
		&un_Par.CN_st_Parameter_Table.CN_st_AgreeOn_ConfineCall,sizeof(st_AgreeOn_ConfineCall));
	}
	else if(Space==De_AgreeOn_SetPar_State_SetDriverID)	 										//���ü�ʻԱ
	{	if(CN_st_Fun_File.ReadRecoder(CN_st_File_fd.Reducefd,0,&un_Par.CN_st_AgreeOn_Driver)!=De_Suc_File)
			return De_Erro_AppSendAgreeOn_SeeAbout;
		CN_st_Fun_AscNumber.MoveByte(&ptst_AgreeOn_Agree_Par->CN_st_AgreeOn_Driver,&un_Par.CN_st_AgreeOn_Driver
		,sizeof(st_AgreeOn_Driver));
	}
	else if(Space==De_AgreeOn_SetPar_State_SetDriverLogin)										//�Ѿ���¼��ʻԱ
	{	if((App_CN_st_WorkFlow_Table.DriverID[0]==0xff)||(App_CN_st_WorkFlow_Table.DriverID[0]==0x00))
			return De_Erro_AppSendAgreeOn_SeeAbout;
		CN_st_Fun_AscNumber.MoveByte(ptst_AgreeOn_Agree_Par->DriverID,App_CN_st_WorkFlow_Table.DriverID,
		sizeof(App_CN_st_WorkFlow_Table.DriverID));
	}
	return De_Suc_AppSendAgreeOn;
}
