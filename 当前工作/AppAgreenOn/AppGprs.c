#define De_AppGprs_Compiler
#include "AppGprs.h"
static void AgreeData(st_st_AgreeOn_Dev_Par	*ptst_st_AgreeOn_Dev_Par,uint8 fd)
{	uint16 i;
	for(i=0;i<sizeof(CN_Ba_st_AppGprs_Order_Set)/sizeof(st_AppGprs_Order_Set);i++)
	{	if(ptst_st_AgreeOn_Dev_Par->OrderID!=CN_Ba_st_AppGprs_Order_Set[i].ParID)
			continue;
		if(CN_Ba_st_AppGprs_Order_Set[i].Execute==NULL)
			break;
		CN_Ba_st_AppGprs_Order_Set[i].Execute(ptst_st_AgreeOn_Dev_Par,fd);
		break;
	}				
}
/*========================================����ִ�к���==========================================================*/
static void Orientation(st_st_AgreeOn_Dev_Par	*ptst_st_AgreeOn_Dev_Par,uint8 fd)		//���Ͷ�λָ��
{	st_st_AgreeOn_Dev_WritePar	CN_st_st_AgreeOn_Dev_WritePar;
	uint8 Oper;
	CN_st_st_AgreeOn_Dev_WritePar.OrderNumber=0;
	CN_st_st_AgreeOn_Dev_WritePar.OrderID=De_Dev_Order_Orientation;
	CN_st_st_AgreeOn_Dev_WritePar.Buf=&App_CN_st_WorkFlow_Table.CN_st_AgreeOn_Send_Basic;
	CN_st_st_AgreeOn_Dev_WritePar.ContrID=ptst_st_AgreeOn_Dev_Par->ContrID;
	CN_st_Fun_Tzv21.Write(fd,&CN_st_st_AgreeOn_Dev_WritePar,&Oper);			
}
static void Track(st_st_AgreeOn_Dev_Par	*ptst_st_AgreeOn_Dev_Par,uint8 fd)				//׷��ָ��
{	st_Parameter_Table		CN_st_Parameter_Table;
	CN_st_Fun_File.ReadRecoder(CN_st_File_fd.Parameterfd,0,&CN_st_Parameter_Table);
	CN_st_Fun_AscNumber.MoveByte(&CN_st_Parameter_Table.CN_st_AgreeOn_Agree_Track,ptst_st_AgreeOn_Dev_Par->Buf,
	sizeof(st_AgreeOn_Agree_Track));
	CN_st_Fun_File.WriteRecoder(CN_st_File_fd.Parameterfd,0,&CN_st_Parameter_Table);
 	CN_st_Fun_AppSendAgreeOn.Answer(ptst_st_AgreeOn_Dev_Par,fd,De_Suc_Oper);										//��������Ӧ�� �ɹ�
}
static void SetPar1(st_st_AgreeOn_Dev_Par	*ptst_st_AgreeOn_Dev_Par,uint8 fd)			//�趨����
{	st_AgreeOn_Agree_Par	*ptst_AgreeOn_Agree_Par;
	//void (*Fun)(void);
	uint16 i;
	ptst_AgreeOn_Agree_Par=ptst_st_AgreeOn_Dev_Par->Buf;
	for(i=0;i<De_AgreeOn_SetPar_Number;i++)
	{	if(ptst_AgreeOn_Agree_Par->ParSet[i]!=De_AgreeOn_SetPar_Yes)
			continue;
	   	SetPar(&ptst_AgreeOn_Agree_Par->CN_st_AgreeOn_Agree_Par_Cut,i);
	}
	CN_st_Fun_AppSendAgreeOn.Answer(ptst_st_AgreeOn_Dev_Par,fd,De_Suc_Oper);			//Ӧ��
	for(i=0;i<sizeof(CN_Ba_ChargLog);i++)
	{	if(ptst_AgreeOn_Agree_Par->ParSet[CN_Ba_ChargLog[i]]==De_AgreeOn_SetPar_Yes)
		{	CN_st_Fun_Timer.EditPro(LogTimerfd,1200);
			CN_st_Fun_Timer.Enable(LogTimerfd);
			break;
		}	
	}
	for(i=0;i<sizeof(CN_Ba_ResetDev);i++)
	{	if(ptst_AgreeOn_Agree_Par->ParSet[CN_Ba_ResetDev[i]]==De_AgreeOn_SetPar_Yes)
		{	CN_st_Fun_Timer.EditPro(UnLoaderTimerfd,1200);
			CN_st_Fun_Timer.Enable(UnLoaderTimerfd);
			break;
		}	
	}	




//	Fun=NULL;
//	Fun();														//�������¸�λ		
}
static void UnlockWaring(st_st_AgreeOn_Dev_Par	*ptst_st_AgreeOn_Dev_Par,uint8 fd)
{	st_Parameter_Table	CN_st_Parameter_Table;
	CN_st_Fun_File.ReadRecoder(CN_st_File_fd.Parameterfd,0,&CN_st_Parameter_Table);
	CN_st_Parameter_Table.HelpWaring=De_st_Parameter_Table_HelpWaring_No;
	CN_st_Fun_File.WriteRecoder(CN_st_File_fd.Parameterfd,0,&CN_st_Parameter_Table);
	CN_st_Fun_TakeData.ClearState(De_Access_Space_Help);							//������������״̬
	App_CN_st_WorkFlow_Table.CN_st_AgreeOn_Send_Basic.State[De_Orientation_State_Help]=De_AgreeOn_State_Suc;
	CN_st_Fun_AppSendAgreeOn.Answer(ptst_st_AgreeOn_Dev_Par,fd,De_Suc_Oper);									//Ӧ��ɹ�
} 
static void AmendMenum(st_st_AgreeOn_Dev_Par	*ptst_st_AgreeOn_Dev_Par,uint8 fd)	//�޸Ĺ̶��˵�
{	st_AgreeOn_AmendMenum	*ptst_AgreeOn_AmendMenum;
	st_File_Menum	CN_st_File_Menum;
	uint16 i,Cuit;
	ptst_AgreeOn_AmendMenum=ptst_st_AgreeOn_Dev_Par->Buf;
	Cuit=CN_st_Fun_File.GetJlNum(CN_st_File_fd.Menumfd);
	memset(&CN_st_File_Menum,0xff,sizeof(st_File_Menum));
	for(i=0;i<Cuit;i++)
		CN_st_Fun_File.WriteRecoder(CN_st_File_fd.Menumfd,i+1,&CN_st_File_Menum);			
	for(i=0;i<ptst_AgreeOn_AmendMenum->Number;i++)
	{	CN_st_File_Menum.BackID=ptst_AgreeOn_AmendMenum->CN_st_AgreeOn_Menum_Infor[i].BackID;
		CN_st_Fun_AscNumber.MoveByte(CN_st_File_Menum.Cut,
		ptst_AgreeOn_AmendMenum->CN_st_AgreeOn_Menum_Infor[i].Cut,sizeof(CN_st_File_Menum.Cut));
		CN_st_Fun_File.WriteRecoder(CN_st_File_fd.Menumfd,
		ptst_AgreeOn_AmendMenum->CN_st_AgreeOn_Menum_Infor[i].ID,&CN_st_File_Menum);
	}
	CN_st_Fun_AppSendAgreeOn.Answer(ptst_st_AgreeOn_Dev_Par,fd,De_Suc_Oper);							//Ӧ��ɹ�
}
static void LoaderTxt(st_st_AgreeOn_Dev_Par	*ptst_st_AgreeOn_Dev_Par,uint8 fd)
{	st_AgreeOn_LoaderTxt	*ptst_AgreeOn_LoaderTxt;
	uint16 Result;
	ptst_AgreeOn_LoaderTxt=ptst_st_AgreeOn_Dev_Par->Buf;
 	;																					//������Ϣ��������
	CN_st_Fun_AppSendAgreeOn.Answer(ptst_st_AgreeOn_Dev_Par,fd,Result);
}

static void LoaderTxtMenum(st_st_AgreeOn_Dev_Par	*ptst_st_AgreeOn_Dev_Par,uint8 fd)	//�·����ı��Ĳ˵�
{	st_AgreeOn_LoaderTxtMenum	*ptst_AgreeOn_LoaderTxtMenum;
	uint16 Result;
	ptst_AgreeOn_LoaderTxtMenum=ptst_st_AgreeOn_Dev_Par->Buf;
	;
	CN_st_Fun_AppSendAgreeOn.Answer(ptst_st_AgreeOn_Dev_Par,fd,Result);	
}
static void SetPhone(st_st_AgreeOn_Dev_Par	*ptst_st_AgreeOn_Dev_Par,uint8 fd)			//���ù̶��绰
{	st_AgreeOn_Phone	*ptst_AgreeOn_Phone;
	st_AgreeOn_Phone_Par		CN_st_AgreeOn_Phone_Par;
	uint16 i,Cuit;
	ptst_AgreeOn_Phone=ptst_st_AgreeOn_Dev_Par->Buf;
   	Cuit=CN_st_Fun_File.GetJlNum(CN_st_File_fd.Rootfd);
	memset(&CN_st_AgreeOn_Phone_Par,0xff,sizeof(st_AgreeOn_Phone_Par));
	for(i=0;i<Cuit;i++)
		CN_st_Fun_File.WriteRecoder(CN_st_File_fd.Rootfd,i+1,&CN_st_AgreeOn_Phone_Par);			
	for(i=0;i<ptst_AgreeOn_Phone->Number;i++)
	{	CN_st_Fun_AscNumber.MoveByte(&CN_st_AgreeOn_Phone_Par,
		&ptst_AgreeOn_Phone->CN_st_AgreeOn_Phone_Par[i],sizeof(st_AgreeOn_Phone_Par));
		CN_st_Fun_File.WriteRecoder(CN_st_File_fd.Menumfd,i+1,&CN_st_AgreeOn_Phone_Par);
	}
	CN_st_Fun_AppSendAgreeOn.Answer(ptst_st_AgreeOn_Dev_Par,fd,De_Suc_Oper);									//Ӧ��ɹ�
}
static void CallAnswer(st_st_AgreeOn_Dev_Par	*ptst_st_AgreeOn_Dev_Par,uint8 fd)	//ͨ������
{	st_AgreeOn_CallAnswer	*ptst_AgreeOn_CallAnswer;
	st_Data_Gprs_Call	CN_st_Data_Gprs_Call;
	uint8 Phone[16];
	uint16 Result;
	uint8 State;
	ptst_AgreeOn_CallAnswer=ptst_st_AgreeOn_Dev_Par->Buf;
	CN_st_Fun_AscNumber.ClsArray(Phone,sizeof(Phone));
	CN_st_Fun_AscNumber.MoveByte(Phone,ptst_AgreeOn_CallAnswer->Phone,sizeof(ptst_AgreeOn_CallAnswer->Phone));
	if(Result=CN_st_Fun_Gprs.GetPhoneState(&CN_st_Data_Gprs_Call))
	{	CN_st_Fun_AppSendAgreeOn.Answer(ptst_st_AgreeOn_Dev_Par,fd,Result);
		return ;
	}
	if(CN_st_Data_Gprs_Call.Mod!=De_GprsHard_CallType_NoCall)
	{	CN_st_Fun_AppSendAgreeOn.Answer(ptst_st_AgreeOn_Dev_Par,fd,De_Erro_Oper);
		return ;
	}	
	if((Result=CN_st_Fun_Gprs.SendPhone(Phone,&State))!=De_Suc_Gprs)
	{	CN_st_Fun_AppSendAgreeOn.Answer(ptst_st_AgreeOn_Dev_Par,fd,Result);
		return ;			
	}
	;				//���������͵绰����
	CN_st_Fun_AppSendAgreeOn.Answer(ptst_st_AgreeOn_Dev_Par,fd,De_Suc_Oper);
	
}
static void UpdateSoftWare(st_st_AgreeOn_Dev_Par	*ptst_st_AgreeOn_Dev_Par,uint8 fd)		//�������
{	; 				//���������������
 	CN_st_Fun_AppSendAgreeOn.Answer(ptst_st_AgreeOn_Dev_Par,fd,De_Suc_Oper);
}
static void LookPar(st_st_AgreeOn_Dev_Par	*ptst_st_AgreeOn_Dev_Par,uint8 fd)				//��ѯ����
{	CN_st_Fun_AppSendAgreeOn.WriteCommand(fd,De_Dev_Order_LookPar,ptst_st_AgreeOn_Dev_Par);
}
static void Contrl(st_st_AgreeOn_Dev_Par	*ptst_st_AgreeOn_Dev_Par,uint8 fd)				//Զ�̿���
{	;
	CN_st_Fun_AppSendAgreeOn.Answer(ptst_st_AgreeOn_Dev_Par,fd,De_Suc_Oper);
}
static void ConfineCall(st_st_AgreeOn_Dev_Par	*ptst_st_AgreeOn_Dev_Par,uint8 fd)			//ͨ������״̬
{ 	st_Parameter_Table	CN_st_Parameter_Table;
	CN_st_Fun_File.ReadRecoder(CN_st_File_fd.Parameterfd,0,&CN_st_Parameter_Table);
	CN_st_Fun_AscNumber.MoveByte(&CN_st_Parameter_Table.CN_st_AgreeOn_ConfineCall,
	ptst_st_AgreeOn_Dev_Par->Buf,sizeof(st_AgreeOn_ConfineCall));
	CN_st_Fun_File.WriteRecoder(CN_st_File_fd.Parameterfd,0,&CN_st_Parameter_Table);
	CN_st_Fun_AppSendAgreeOn.Answer(ptst_st_AgreeOn_Dev_Par,fd,De_Suc_Oper);
}
static void ConfigCentrSever(st_st_AgreeOn_Dev_Par	*ptst_st_AgreeOn_Dev_Par,uint8 fd)//�������ķ�����״̬
{	CN_st_Fun_AppSendAgreeOn.Answer(ptst_st_AgreeOn_Dev_Par,fd,De_Suc_Oper);
	;				//���µ�¼
}
static void Activation(st_st_AgreeOn_Dev_Par	*ptst_st_AgreeOn_Dev_Par,uint8 fd)//���λ�ն�
{	;	
}
/*---------------------------------------------������չЭ��-----------------------------------------------------*/
static void LookJpg(st_st_AgreeOn_Dev_Par	*ptst_st_AgreeOn_Dev_Par,uint8 fd)//��ѯָ�����͵���Ƭ
{	CN_st_Fun_AppSendAgreeOn.WriteCommand(fd,De_Dev_Order_UploaderJpg2,ptst_st_AgreeOn_Dev_Par);		
}

static void JpgIng(st_st_AgreeOn_Dev_Par	*ptst_st_AgreeOn_Dev_Par,uint8 fd)//��ѯʵʱ��Ƭ
{	;//CN_st_Fun_AppSendAgreeOn.WriteCommand(fd,De_Dev_Order_UploaderJpg1,ptst_st_AgreeOn_Dev_Par->Buf);;
}
static void SetVidType(st_st_AgreeOn_Dev_Par	*ptst_st_AgreeOn_Dev_Par,uint8 fd)//������������
{	uint16 i;
	for(i=0;i<De_CN_Ba_WordPar_Number;i++)
		CN_st_Fun_TakeData.ClearState(i+De_CN_Ba_WordPar_Number);
	CN_st_Fun_File.WriteRecoder(CN_st_File_fd.VidTermfd,0,ptst_st_AgreeOn_Dev_Par->Buf);
	CN_st_Fun_AppSendAgreeOn.Answer(ptst_st_AgreeOn_Dev_Par,fd,De_Suc_Oper);	

}
static void TabelList(st_st_AgreeOn_Dev_Par	*ptst_st_AgreeOn_Dev_Par,uint8 fd)		//���ñ�
{	

}
static void LookWorkPar(st_st_AgreeOn_Dev_Par	*ptst_st_AgreeOn_Dev_Par,uint8 fd)	//��ѯ��������
{	st_st_AgreeOn_Dev_WritePar	CN_st_st_AgreeOn_Dev_WritePar;
	st_AgreeOn_Send_UploaderPar	CN_st_AgreeOn_Send_UploaderPar;
	uint8 Oper;
	CN_st_Fun_AscNumber.MoveByte(&CN_st_AgreeOn_Send_UploaderPar.CN_st_AgreeOn_Send_Basic,
	&App_CN_st_WorkFlow_Table.CN_st_AgreeOn_Send_Basic,sizeof(st_AgreeOn_Send_Basic));

	CN_st_Fun_AscNumber.MoveByte(&CN_st_AgreeOn_Send_UploaderPar.CN_st_WorkVal_Tabel,
	&App_CN_st_WorkFlow_Table.CN_st_WorkVal_Tabel,sizeof(st_WorkVal_Tabel));

	CN_st_st_AgreeOn_Dev_WritePar.OrderNumber=0;
	CN_st_st_AgreeOn_Dev_WritePar.OrderID=De_Dev_Order_UploaderPar;
	CN_st_st_AgreeOn_Dev_WritePar.Buf=&CN_st_AgreeOn_Send_UploaderPar;
	CN_st_st_AgreeOn_Dev_WritePar.ContrID=ptst_st_AgreeOn_Dev_Par->ContrID;
	CN_st_Fun_Tzv21.Write(fd,&CN_st_st_AgreeOn_Dev_WritePar,&Oper);		
}
static void WorkParTimer(st_st_AgreeOn_Dev_Par	*ptst_st_AgreeOn_Dev_Par,uint8 fd)//���չ̶�ʱ���ϴ���������	
{	CN_st_Fun_File.WriteRecoder(CN_st_File_fd.WorkParTimerfd,0,ptst_st_AgreeOn_Dev_Par->Buf);	
	CN_st_Fun_AppSendAgreeOn.Answer(ptst_st_AgreeOn_Dev_Par,fd,De_Suc_Oper);
	;			//��������ʱ��	

}
static void WorkParSpace(st_st_AgreeOn_Dev_Par	*ptst_st_AgreeOn_Dev_Par,uint8 fd)//���ռ���ϴ���������
{	st_Parameter_Table	CN_st_Parameter_Table;
	CN_st_Fun_File.ReadRecoder(CN_st_File_fd.Parameterfd,0,&CN_st_Parameter_Table);
	CN_st_Fun_AscNumber.MoveByte(&CN_st_Parameter_Table.CN_Work_st_AgreeOn_Agree_Track,ptst_st_AgreeOn_Dev_Par->Buf,
	sizeof(st_AgreeOn_Agree_Track));
	CN_st_Fun_AppSendAgreeOn.Answer(ptst_st_AgreeOn_Dev_Par,fd,De_Suc_Oper);
}
static void LookLog(st_st_AgreeOn_Dev_Par	*ptst_st_AgreeOn_Dev_Par,uint8 fd)//��ѯ��־�ļ�
{	CN_st_Fun_AppSendAgreeOn.WriteCommand(fd,De_Dev_Order_UploaderLog,ptst_st_AgreeOn_Dev_Par);	

}
static void SetWaringTerm(st_st_AgreeOn_Dev_Par	*ptst_st_AgreeOn_Dev_Par,uint8 fd)//���ñ�������
{	CN_st_Fun_File.WriteRecoder(CN_st_File_fd.WaringStatefd,0,ptst_st_AgreeOn_Dev_Par->Buf);	
	CN_st_Fun_AppSendAgreeOn.Answer(ptst_st_AgreeOn_Dev_Par,fd,De_Suc_Oper);
}
static void LookWaringTerm(st_st_AgreeOn_Dev_Par	*ptst_st_AgreeOn_Dev_Par,uint8 fd)//��ѯ��������
{	CN_st_Fun_AppSendAgreeOn.WriteCommand(fd,De_Dev_Order_UpLoaderWarning,ptst_st_AgreeOn_Dev_Par);	


}
/*-----------------------------------------------����Э��ר��---------------------------------------------------*/
#define De_Type_Round										1
#define De_Type_Rectangle									2
static void SetRound(st_st_AgreeOn_Dev_Par	*ptst_st_AgreeOn_Dev_Par,uint8 fd)//����Բ��·��
{	st_AgreeOn_SetRound	*ptst_AgreeOn_SetRound;
	uint16 i;
	ptst_AgreeOn_SetRound=ptst_st_AgreeOn_Dev_Par->Buf;
	for(i=0;i<ptst_AgreeOn_SetRound->Number;i++)
	{	if(CN_st_Fun_TakeData.AccessAear(&ptst_AgreeOn_SetRound->CN_st_AgreeOn_SetRound_Par[i],De_Type_Round)!=De_Suc_AppGprs)
		{	CN_st_Fun_AppSendAgreeOn.Answer(ptst_st_AgreeOn_Dev_Par,fd,De_Erro_Oper);
		   	return ;
		}
	}
	CN_st_Fun_AppSendAgreeOn.Answer(ptst_st_AgreeOn_Dev_Par,fd,De_Suc_Oper);
}
static void DelRound(st_st_AgreeOn_Dev_Par	*ptst_st_AgreeOn_Dev_Par,uint8 fd)//ɾ��Բ��·��
{	st_AgreeOn_DelRound	*ptst_AgreeOn_DelRound;
	uint16 i;
	ptst_AgreeOn_DelRound=ptst_st_AgreeOn_Dev_Par->Buf;
	for(i=0;i<ptst_AgreeOn_DelRound->Number;i++)
		CN_st_Fun_TakeData.DelAear(ptst_AgreeOn_DelRound->ID[i]);
	CN_st_Fun_AppSendAgreeOn.Answer(ptst_st_AgreeOn_Dev_Par,fd,De_Suc_Oper);	
}
static void SetRectangle(st_st_AgreeOn_Dev_Par	*ptst_st_AgreeOn_Dev_Par,uint8 fd)//���þ���·��
{	st_AgreeOn_SetRectangle	*ptst_AgreeOn_SetRectangle;
	uint16 i;
	ptst_AgreeOn_SetRectangle=ptst_st_AgreeOn_Dev_Par->Buf;
	for(i=0;i<ptst_AgreeOn_SetRectangle->Number;i++)
	{	if(CN_st_Fun_TakeData.AccessAear(&ptst_AgreeOn_SetRectangle->CN_st_AgreeOn_SetRectangle_Par[i],De_Type_Rectangle)!=De_Suc_AppGprs)
		{	CN_st_Fun_AppSendAgreeOn.Answer(ptst_st_AgreeOn_Dev_Par,fd,De_Erro_Oper);
		   	return ;
		}
	}
	CN_st_Fun_AppSendAgreeOn.Answer(ptst_st_AgreeOn_Dev_Par,fd,De_Suc_Oper);

}
static void DelRectangle(st_st_AgreeOn_Dev_Par	*ptst_st_AgreeOn_Dev_Par,uint8 fd)//ɾ������·��
{	st_AgreeOn_DelRound	*ptst_AgreeOn_DelRound;
	uint16 i;
	ptst_AgreeOn_DelRound=ptst_st_AgreeOn_Dev_Par->Buf;
	for(i=0;i<ptst_AgreeOn_DelRound->Number;i++)
		CN_st_Fun_TakeData.DelAear(ptst_AgreeOn_DelRound->ID[i]);
	CN_st_Fun_AppSendAgreeOn.Answer(ptst_st_AgreeOn_Dev_Par,fd,De_Suc_Oper);
}
static void SetPolygon(st_st_AgreeOn_Dev_Par	*ptst_st_AgreeOn_Dev_Par,uint8 fd)//���ö����·��
{	CN_st_Fun_AppSendAgreeOn.Answer(ptst_st_AgreeOn_Dev_Par,fd,De_Erro_Oper);	

}
static void DelPolygon(st_st_AgreeOn_Dev_Par	*ptst_st_AgreeOn_Dev_Par,uint8 fd)//ɾ�������·��
{	st_AgreeOn_DelRound	*ptst_AgreeOn_DelRound;
	uint16 i;
	ptst_AgreeOn_DelRound=ptst_st_AgreeOn_Dev_Par->Buf;
	for(i=0;i<ptst_AgreeOn_DelRound->Number;i++)
		CN_st_Fun_TakeData.DelAear(ptst_AgreeOn_DelRound->ID[i]);
	CN_st_Fun_AppSendAgreeOn.Answer(ptst_st_AgreeOn_Dev_Par,fd,De_Suc_Oper);
}
static void SetRoadMap(st_st_AgreeOn_Dev_Par	*ptst_st_AgreeOn_Dev_Par,uint8 fd)											//����·������
{	CN_st_Fun_AppSendAgreeOn.Answer(ptst_st_AgreeOn_Dev_Par,fd,De_Suc_Oper);

}
static void DelRoadMap(st_st_AgreeOn_Dev_Par	*ptst_st_AgreeOn_Dev_Par,uint8 fd)											//ɾ��·������
{	CN_st_Fun_AppSendAgreeOn.Answer(ptst_st_AgreeOn_Dev_Par,fd,De_Suc_Oper);

}
static void Reduce(st_st_AgreeOn_Dev_Par	*ptst_st_AgreeOn_Dev_Par,uint8 fd)												//����ѹ���ش�
{ 	st_Reduce_Table	CN_st_Reduce_Table;
	CN_st_Fun_AscNumber.ClsArray(&CN_st_Reduce_Table,sizeof(st_Reduce_Table));
	CN_st_Fun_AscNumber.MoveByte(&CN_st_Reduce_Table.CN_st_AgreeOn_Reduce,ptst_st_AgreeOn_Dev_Par->Buf,sizeof(st_AgreeOn_Reduce));
	CN_st_Fun_File.WriteRecoder(CN_st_File_fd.Reducefd,0,&CN_st_Reduce_Table);
	CN_st_Fun_AppSendAgreeOn.Answer(ptst_st_AgreeOn_Dev_Par,fd,De_Suc_Oper);	
}
static void Driver(st_st_AgreeOn_Dev_Par	*ptst_st_AgreeOn_Dev_Par,uint8 fd)									//���ü�ʻԱID
{	CN_st_Fun_File.WriteRecoder(CN_st_File_fd.Driverfd,0,ptst_st_AgreeOn_Dev_Par->Buf);	
	CN_st_Fun_AppSendAgreeOn.Answer(ptst_st_AgreeOn_Dev_Par,fd,De_Suc_Oper);
}
static void Navigation(st_st_AgreeOn_Dev_Par	*ptst_st_AgreeOn_Dev_Par,uint8 fd)									//���ĵ���
{	CN_st_Fun_AppSendAgreeOn.Answer(ptst_st_AgreeOn_Dev_Par,fd,De_Erro_Oper);	

}
static void HandTxt(st_st_AgreeOn_Dev_Par	*ptst_st_AgreeOn_Dev_Par,uint8 fd)										//�ֻ��ı�����
{	st_AgreeOn_HandTxt	*ptst_AgreeOn_HandTxt;
	st_AgreeOn_Driver	CN_st_AgreeOn_Driver;
	uint8 i;
	ptst_AgreeOn_HandTxt=ptst_st_AgreeOn_Dev_Par->Buf;
	if(CN_st_Fun_File.ReadRecoder(CN_st_File_fd.Driverfd,0,&CN_st_AgreeOn_Driver)!=De_Suc_File)
	{	CN_st_Fun_AppSendAgreeOn.Answer(ptst_st_AgreeOn_Dev_Par,fd,De_Erro_Oper);
		return ;
	}	
	for(i=0;i<CN_st_AgreeOn_Driver.Number;i++)
	{	if(CN_st_Fun_AscNumber.CompareBuf(CN_st_AgreeOn_Driver.CN_st_AgreeOn_Driver_Par[i].ID,
			App_CN_st_WorkFlow_Table.DriverID,sizeof(App_CN_st_WorkFlow_Table.DriverID))==0)
			break;
	}
	if(i==CN_st_AgreeOn_Driver.Number)
	{	CN_st_Fun_AppSendAgreeOn.Answer(ptst_st_AgreeOn_Dev_Par,fd,De_Erro_Oper);
		return ;
	}
	if(CN_st_Fun_Gprs.SendMessage(CN_st_AgreeOn_Driver.CN_st_AgreeOn_Driver_Par[i].Phone,ptst_AgreeOn_HandTxt
	->Buf)!=De_Suc_Gprs)
	{ 	CN_st_Fun_AppSendAgreeOn.Answer(ptst_st_AgreeOn_Dev_Par,fd,De_Erro_Oper);
		return ;
	}
	CN_st_Fun_AppSendAgreeOn.Answer(ptst_st_AgreeOn_Dev_Par,fd,De_Suc_Oper);

}
static void HandAttemper(st_st_AgreeOn_Dev_Par	*ptst_st_AgreeOn_Dev_Par,uint8 fd)								//�ֻ�������Ϣ
{	st_AgreeOn_HandAttemper	*ptst_AgreeOn_HandAttemper;
	st_AgreeOn_Driver	CN_st_AgreeOn_Driver;
	uint8 Message[200];
	uint16 DataLen,StrDataLen;
	uint8 i;

	ptst_AgreeOn_HandAttemper=ptst_st_AgreeOn_Dev_Par->Buf;
	if(CN_st_Fun_File.ReadRecoder(CN_st_File_fd.Driverfd,0,&CN_st_AgreeOn_Driver)!=De_Suc_File)
	{	CN_st_Fun_AppSendAgreeOn.Answer(ptst_st_AgreeOn_Dev_Par,fd,De_Erro_Oper);
		return ;
	}	
	for(i=0;i<CN_st_AgreeOn_Driver.Number;i++)
	{	if(CN_st_Fun_AscNumber.CompareBuf(CN_st_AgreeOn_Driver.CN_st_AgreeOn_Driver_Par[i].ID,
			App_CN_st_WorkFlow_Table.DriverID,sizeof(App_CN_st_WorkFlow_Table.DriverID))==0)
			break;
	}
	if(i==CN_st_AgreeOn_Driver.Number)
	{	CN_st_Fun_AppSendAgreeOn.Answer(ptst_st_AgreeOn_Dev_Par,fd,De_Erro_Oper);
		return ;
	}
	CN_st_Fun_AscNumber.ClsArray(Message,sizeof(Message));
	DataLen=CN_st_Fun_AscNumber.Algorism2Asc((uint32) ptst_AgreeOn_HandAttemper->ID,Message);
	Message[DataLen++]=':';
	StrDataLen=CN_st_Fun_AscNumber.Strsize(ptst_AgreeOn_HandAttemper->Buf);
	if(StrDataLen+DataLen>sizeof(Message))
		StrDataLen=sizeof(Message)-DataLen;	
   	CN_st_Fun_AscNumber.MoveByte(Message+DataLen,ptst_AgreeOn_HandAttemper->Buf,StrDataLen);
	if(CN_st_Fun_Gprs.SendMessage(CN_st_AgreeOn_Driver.CN_st_AgreeOn_Driver_Par[i].Phone,Message)!=De_Suc_Gprs)
	{ 	CN_st_Fun_AppSendAgreeOn.Answer(ptst_st_AgreeOn_Dev_Par,fd,De_Erro_Oper);
		return ;
	}
	CN_st_Fun_AppSendAgreeOn.Answer(ptst_st_AgreeOn_Dev_Par,fd,De_Suc_Oper);
}	
/*---------------------------------------------���⳵Э��-------------------------------------------------------*/ 
static void AmendForm(st_st_AgreeOn_Dev_Par	*ptst_st_AgreeOn_Dev_Par,uint8 fd)									//�޸Ķ�����Ϣ
{	CN_st_Fun_AppSendAgreeOn.Answer(ptst_st_AgreeOn_Dev_Par,fd,De_Erro_Oper);
	

}
static void UpLoaderForm(st_st_AgreeOn_Dev_Par	*ptst_st_AgreeOn_Dev_Par,uint8 fd)								//�·�����������Ϣ
{	CN_st_Fun_AppSendAgreeOn.Answer(ptst_st_AgreeOn_Dev_Par,fd,De_Erro_Oper);

}
static void UpLoaderFormSuc(st_st_AgreeOn_Dev_Par	*ptst_st_AgreeOn_Dev_Par,uint8 fd)							//�·���������ɹ���Ϣ
{	CN_st_Fun_AppSendAgreeOn.Answer(ptst_st_AgreeOn_Dev_Par,fd,De_Erro_Oper);

}
static void UpLoaderFormErro(st_st_AgreeOn_Dev_Par	*ptst_st_AgreeOn_Dev_Par,uint8 fd)							//�·���������ʧ����Ϣ
{	CN_st_Fun_AppSendAgreeOn.Answer(ptst_st_AgreeOn_Dev_Par,fd,De_Erro_Oper);

}
static void UpLoaderCan(st_st_AgreeOn_Dev_Par	*ptst_st_AgreeOn_Dev_Par,uint8 fd)								//�·�����ȡ����Ϣ
{	CN_st_Fun_AppSendAgreeOn.Answer(ptst_st_AgreeOn_Dev_Par,fd,De_Erro_Oper);

}







