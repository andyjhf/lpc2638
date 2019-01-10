#define De_AppGprs_Compiler
#include "AppGprs.h"
//#define De_SoftWareUpDate_Debug
static void AgreeData(st_st_AgreeOn_Dev_Par	*ptst_st_AgreeOn_Dev_Par,uint8 fd)
{	uint16 i;
	st_AgreeOn_UpdateSoftWare	*ptst_AgreeOn_UpdateSoftWare;
	for(i=0;i<sizeof(CN_Ba_st_AppGprs_Order_Set)/sizeof(st_AppGprs_Order_Set);i++,WatchDog())
	{	
		#ifdef De_SoftWareUpDate_Debug
		if(ptst_st_AgreeOn_Dev_Par->OrderID==De_Centr_Order_Orientation)					//定位指令模拟软件升级
		{	ptst_AgreeOn_UpdateSoftWare=ptst_st_AgreeOn_Dev_Par->Buf;
			ptst_AgreeOn_UpdateSoftWare->Device=0;
			ptst_AgreeOn_UpdateSoftWare->IP=0xdde78cd3;
			ptst_AgreeOn_UpdateSoftWare->Port=1596;
			CN_st_Fun_AscNumber.MoveByte(ptst_AgreeOn_UpdateSoftWare->Use,"machao",6);
			CN_st_Fun_AscNumber.MoveByte(ptst_AgreeOn_UpdateSoftWare->Pass,"machao1980",10);
			//CN_st_Fun_AscNumber.MoveByte(ptst_AgreeOn_UpdateSoftWare->FileName,"/123/APP.GJ",sizeof("/123/APP.GJ"));
			CN_st_Fun_AscNumber.MoveByte(ptst_AgreeOn_UpdateSoftWare->FileName,"/123/GPRS_OS.GJ",sizeof("/123/GPRS_OS.GJ"));
			ptst_st_AgreeOn_Dev_Par->OrderID=De_Centr_Order_UpdateSoftWare;				
		}
		#endif
		if(ptst_st_AgreeOn_Dev_Par->OrderID!=CN_Ba_st_AppGprs_Order_Set[i].ParID)
			continue;
		if(CN_Ba_st_AppGprs_Order_Set[i].Execute==NULL)
			break;

		CN_Ba_st_AppGprs_Order_Set[i].Execute(ptst_st_AgreeOn_Dev_Par,fd);
		break;
	}				
}
/*========================================命令执行函数==========================================================*/
static void Orientation(st_st_AgreeOn_Dev_Par	*ptst_st_AgreeOn_Dev_Par,uint8 fd)		//发送定位指令
{	st_st_AgreeOn_Dev_WritePar	CN_st_st_AgreeOn_Dev_WritePar;
	uint8 Oper;
	CN_st_st_AgreeOn_Dev_WritePar.OrderNumber=0;
	CN_st_st_AgreeOn_Dev_WritePar.OrderID=De_Dev_Order_Orientation;
	CN_st_st_AgreeOn_Dev_WritePar.Buf=&App_CN_st_WorkFlow_Table.CN_st_AgreeOn_Send_Basic;
	CN_st_st_AgreeOn_Dev_WritePar.ContrID=ptst_st_AgreeOn_Dev_Par->ContrID;
	CN_st_Fun_Tzv21.Write(fd,&CN_st_st_AgreeOn_Dev_WritePar,&Oper);			
}
static void Track(st_st_AgreeOn_Dev_Par	*ptst_st_AgreeOn_Dev_Par,uint8 fd)				//追踪指令
{	st_Parameter_Table		CN_st_Parameter_Table;
	CN_st_Fun_File.ReadRecoder(CN_st_File_fd.Parameterfd,0,&CN_st_Parameter_Table);
	CN_st_Fun_AscNumber.MoveByte(&CN_st_Parameter_Table.CN_st_AgreeOn_Agree_Track,ptst_st_AgreeOn_Dev_Par->Buf,
	sizeof(st_AgreeOn_Agree_Track));
	CN_st_Fun_File.WriteRecoder(CN_st_File_fd.Parameterfd,0,&CN_st_Parameter_Table);
 	CN_st_Fun_AppSendAgreeOn.Answer(ptst_st_AgreeOn_Dev_Par,fd,De_Suc_Oper);										//发送命令应答 成功
}
static void SetPar1(st_st_AgreeOn_Dev_Par	*ptst_st_AgreeOn_Dev_Par,uint8 fd)			//设定参数
{	st_AgreeOn_Agree_Par	*ptst_AgreeOn_Agree_Par;
//	st_File_WorkPar CN_st_File_WorkPar;
	//void (*Fun)(void);
	uint16 i,Tail;
	ptst_AgreeOn_Agree_Par=ptst_st_AgreeOn_Dev_Par->Buf;
	for(i=0;i<De_AgreeOn_SetPar_Number;i++)
	{	if(ptst_AgreeOn_Agree_Par->ParSet[i]!=De_AgreeOn_SetPar_Yes)
			continue;
	   	SetPar(&ptst_AgreeOn_Agree_Par->CN_st_AgreeOn_Agree_Par_Cut,i);
//		if(i==De_AgreeOn_SetPar_State_SetParLoad)
//		{	CN_st_Fun_File.ReadRecoder(CN_st_File_fd.WorkParfd,0,&CN_st_File_WorkPar);
//			for(Tail=0;Tail<De_CN_Ba_WordPar_Number;Tail++)
//			{	if(CN_st_File_WorkPar.CN_st_File_WorkParVal[Tail].YesOnON==De_WordPar_Open)
//				{	App_CN_st_WorkFlow_Table.CN_st_WorkVal_Tabel.Type[Tail]=De_st_AgreeOn_Send_Waring_Type_Yes;
//					continue;
//				}
//				App_CN_st_WorkFlow_Table.CN_st_WorkVal_Tabel.Type[Tail]=De_st_AgreeOn_Send_Waring_Type_No;
//			}
//		}
	}
	CN_st_Fun_AppSendAgreeOn.Answer(ptst_st_AgreeOn_Dev_Par,fd,De_Suc_Oper);			//应答
	for(i=0;i<sizeof(CN_Ba_ChargLog);i++)
	{	if(ptst_AgreeOn_Agree_Par->ParSet[CN_Ba_ChargLog[i]]==De_AgreeOn_SetPar_Yes)
		{	CN_st_Fun_Timer.EditPro(LogTimerfd,120);
			CN_st_Fun_Timer.Enable(LogTimerfd);
			break;
		}	
	}
	for(i=0;i<sizeof(CN_Ba_ResetDev);i++)
	{	if(ptst_AgreeOn_Agree_Par->ParSet[CN_Ba_ResetDev[i]]==De_AgreeOn_SetPar_Yes)
		{	CN_st_Fun_Timer.EditPro(UnLoaderTimerfd,120);
			CN_st_Fun_Timer.Enable(UnLoaderTimerfd);
			break;
		}	
	}		
}
static void UnlockWaring(st_st_AgreeOn_Dev_Par	*ptst_st_AgreeOn_Dev_Par,uint8 fd)
{	st_Parameter_Table	CN_st_Parameter_Table;
	CN_st_Fun_File.ReadRecoder(CN_st_File_fd.Parameterfd,0,&CN_st_Parameter_Table);
	CN_st_Parameter_Table.HelpWaring=De_st_Parameter_Table_HelpWaring_No;
	CN_st_Fun_File.WriteRecoder(CN_st_File_fd.Parameterfd,0,&CN_st_Parameter_Table);
	CN_st_Fun_TakeData.ClearState(De_Access_Space_Help);							//消除紧急报警状态
	App_CN_st_WorkFlow_Table.CN_st_AgreeOn_Send_Basic.State[De_Orientation_State_Help]=De_AgreeOn_State_Suc;
	CN_st_Fun_AppSendAgreeOn.Answer(ptst_st_AgreeOn_Dev_Par,fd,De_Suc_Oper);									//应答成功
} 
static void AmendMenum(st_st_AgreeOn_Dev_Par	*ptst_st_AgreeOn_Dev_Par,uint8 fd)	//修改固定菜单
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
	CN_st_Fun_AppSendAgreeOn.Answer(ptst_st_AgreeOn_Dev_Par,fd,De_Suc_Oper);							//应答成功
}
static void LoaderTxt(st_st_AgreeOn_Dev_Par	*ptst_st_AgreeOn_Dev_Par,uint8 fd)
{	st_AgreeOn_LoaderTxt	*ptst_AgreeOn_LoaderTxt;
	st_Display_Order_DeliverCentr	CN_st_Display_Order_DeliverCentr;
	st_Display_Send		CN_st_Display_Send;
	uint16 Result,DataLen,Len;
	uint8 Buf[201];
//	CN_st_Fun_AscNumber.ClsArray(ptst_AgreeOn_LoaderTxt,sizeof(st_AgreeOn_LoaderTxt));
	ptst_AgreeOn_LoaderTxt=ptst_st_AgreeOn_Dev_Par->Buf;
	CN_st_Fun_AppSendAgreeOn.Answer(ptst_st_AgreeOn_Dev_Par,fd,Result);

	DataLen=0;
	Buf[DataLen++]=0x09;
	Len=CN_st_Fun_AscNumber.Strsize(ptst_st_AgreeOn_Dev_Par->Buf);
	CN_st_Fun_AscNumber.MoveByte(Buf+DataLen,ptst_st_AgreeOn_Dev_Par->Buf,
	CN_st_Fun_AscNumber.Strsize(ptst_st_AgreeOn_Dev_Par->Buf));
	DataLen+=Len;
	CN_st_Display_Order_DeliverCentr.SizeofBuf=DataLen;
	CN_st_Display_Order_DeliverCentr.Buf=Buf;
	CN_st_Display_Send.SendOrAgree=De_Sensor_Display_Send;
	CN_st_Display_Send.ID=De_Display_Host_Order_DeliverCentr;
	CN_st_Display_Send.SendData=&CN_st_Display_Order_DeliverCentr;  
	if(CN_st_Fun_Sensor.GetPar2ID(De_Sensor_WordPar_Display,&fd)!=De_Suc_Sensor)
		return ;
	CN_st_Fun_Sensor.Read(fd,&CN_st_Display_Send,NULL);	
}

static void LoaderTxtMenum(st_st_AgreeOn_Dev_Par	*ptst_st_AgreeOn_Dev_Par,uint8 fd)	//下发带文本的菜单
{	st_AgreeOn_LoaderTxtMenum	*ptst_AgreeOn_LoaderTxtMenum;
	uint16 Result;
	ptst_AgreeOn_LoaderTxtMenum=ptst_st_AgreeOn_Dev_Par->Buf;
	;
	CN_st_Fun_AppSendAgreeOn.Answer(ptst_st_AgreeOn_Dev_Par,fd,Result);	
}
static void SetPhone(st_st_AgreeOn_Dev_Par	*ptst_st_AgreeOn_Dev_Par,uint8 fd)			//设置固定电话
{	st_AgreeOn_Phone	*ptst_AgreeOn_Phone;
	st_Display_Order_DeliverCentr	CN_st_Display_Order_DeliverCentr;
	st_Display_Send		CN_st_Display_Send;
	st_AgreeOn_Phone_Par		CN_st_AgreeOn_Phone_Par;
	uint8 *Buf;
	uint16 i,Cuit,DataLen,Len;
	ptst_AgreeOn_Phone=ptst_st_AgreeOn_Dev_Par->Buf;
	Buf=ptst_st_AgreeOn_Dev_Par->Buf;
   	Cuit=CN_st_Fun_File.GetJlNum(CN_st_File_fd.Rootfd);
	memset(&CN_st_AgreeOn_Phone_Par,0xff,sizeof(st_AgreeOn_Phone_Par));
	for(i=0;i<Cuit;i++)
		CN_st_Fun_File.WriteRecoder(CN_st_File_fd.Rootfd,i+1,&CN_st_AgreeOn_Phone_Par);			
	for(i=0;i<ptst_AgreeOn_Phone->Number;i++)
	{	CN_st_Fun_AscNumber.MoveByte(&CN_st_AgreeOn_Phone_Par,
		&ptst_AgreeOn_Phone->CN_st_AgreeOn_Phone_Par[i],sizeof(st_AgreeOn_Phone_Par));
		CN_st_Fun_File.WriteRecoder(CN_st_File_fd.Rootfd,i+1,&CN_st_AgreeOn_Phone_Par);
	}
	CN_st_Fun_AppSendAgreeOn.Answer(ptst_st_AgreeOn_Dev_Par,fd,De_Suc_Oper);  	//应答成功
	Cuit=ptst_AgreeOn_Phone->Number;
	DataLen=0;
	Buf[DataLen++]=0x0f;
	for(i=0;i<Cuit;i++)
	{ 	CN_st_Fun_File.ReadRecoder(CN_st_File_fd.Rootfd,i+1,&CN_st_AgreeOn_Phone_Par);
		Buf[DataLen++]=CN_st_AgreeOn_Phone_Par.State;									
		CN_st_Fun_AscNumber.MoveByte(Buf+DataLen,CN_st_AgreeOn_Phone_Par.Name,8);
		DataLen+=8;
		Buf[DataLen++]=CN_st_Fun_AscNumber.Strsize(CN_st_AgreeOn_Phone_Par.Phone);
		Len=CN_st_Fun_AscNumber.Strsize(CN_st_AgreeOn_Phone_Par.Phone);
		CN_st_Fun_AscNumber.MoveByte(Buf+DataLen,CN_st_AgreeOn_Phone_Par.Phone,
		CN_st_Fun_AscNumber.Strsize16(CN_st_AgreeOn_Phone_Par.Phone));
		DataLen+=Len;
	}											                                                                         
	CN_st_Display_Order_DeliverCentr.SizeofBuf=DataLen;
 	CN_st_Display_Order_DeliverCentr.Buf=Buf;
	CN_st_Display_Send.SendOrAgree=De_Sensor_Display_Send;
	CN_st_Display_Send.ID=De_Display_Host_Order_DeliverCentr;
	CN_st_Display_Send.SendData=&CN_st_Display_Order_DeliverCentr;  
	if(CN_st_Fun_Sensor.GetPar2ID(De_Sensor_WordPar_Display,&fd)!=De_Suc_Sensor)
		return ;
	CN_st_Fun_Sensor.Read(fd,&CN_st_Display_Send,NULL);		
}
static void CallAnswer(st_st_AgreeOn_Dev_Par	*ptst_st_AgreeOn_Dev_Par,uint8 fd)	//通话请求
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
	;				//调度屏发送电话接受
	CN_st_Fun_AppSendAgreeOn.Answer(ptst_st_AgreeOn_Dev_Par,fd,De_Suc_Oper);
	
}
static void UpdateSoftWare(st_st_AgreeOn_Dev_Par	*ptst_st_AgreeOn_Dev_Par,uint8 fd)		//软件升级
{	st_AgreeOn_UpdateSoftWare	*ptst_AgreeOn_UpdateSoftWare;
	
	ptst_AgreeOn_UpdateSoftWare=ptst_st_AgreeOn_Dev_Par->Buf;
	CN_st_Fun_AscNumber.ClsArray(&CN_st_BoxData_UpData,sizeof(st_BoxData_UpData));
   	CN_st_Fun_AscNumber.MoveByte(CN_st_BoxData_UpData.CN_st_Order_UpdateSoftWare.Use,ptst_AgreeOn_UpdateSoftWare->Use,
	sizeof(CN_st_BoxData_UpData.CN_st_Order_UpdateSoftWare.Use));
	CN_st_Fun_AscNumber.MoveByte(CN_st_BoxData_UpData.CN_st_Order_UpdateSoftWare.Pass,ptst_AgreeOn_UpdateSoftWare->Pass,
	sizeof(CN_st_BoxData_UpData.CN_st_Order_UpdateSoftWare.Pass));
	CN_st_Fun_AscNumber.MoveByte(CN_st_BoxData_UpData.CN_st_Order_UpdateSoftWare.FileName,ptst_AgreeOn_UpdateSoftWare->FileName,
	sizeof(CN_st_BoxData_UpData.CN_st_Order_UpdateSoftWare.FileName));
	CN_st_Fun_AscNumber.MoveByte(CN_st_BoxData_UpData.CN_st_Order_UpdateSoftWare.SaveFileName,"UpData",6);
	CN_st_BoxData_UpData.CN_st_Order_UpdateSoftWare.Port=ptst_AgreeOn_UpdateSoftWare->Port;
   	CN_st_BoxData_UpData.CN_st_Order_UpdateSoftWare.IP=ptst_AgreeOn_UpdateSoftWare->IP;
	CN_st_BoxData_UpData.CN_st_Order_UpdateSoftWare.Device=ptst_AgreeOn_UpdateSoftWare->Device;
	CN_st_BoxData_UpData.CN_st_Order_UpdateSoftWare.DownLoaderOver=DownLoaderOver;
	CN_st_BoxData_UpData.CN_st_Order_UpdateSoftWare.DownLoaderState=SoftWareState;
	OSQPost(UpDateSoftWare_Q,&CN_st_BoxData_UpData);							//发送软件升级命令
 	CN_st_Fun_AppSendAgreeOn.Answer(ptst_st_AgreeOn_Dev_Par,fd,De_Suc_Oper);
}
static void LookPar(st_st_AgreeOn_Dev_Par	*ptst_st_AgreeOn_Dev_Par,uint8 fd)				//查询参数
{	CN_st_Fun_AppSendAgreeOn.WriteCommand(fd,De_Dev_Order_LookPar,ptst_st_AgreeOn_Dev_Par);
}
static void Contrl(st_st_AgreeOn_Dev_Par	*ptst_st_AgreeOn_Dev_Par,uint8 fd)				//远程控制
{	st_Parameter_Table	CN_st_Parameter_Table;
    CN_st_Fun_File.ReadRecoder(CN_st_File_fd.Parameterfd,0,&CN_st_Parameter_Table);
	CN_st_Fun_AscNumber.MoveByte(&CN_st_Parameter_Table.Contr0,ptst_st_AgreeOn_Dev_Par->Buf,1);
	CN_st_Fun_File.WriteRecoder(CN_st_File_fd.Parameterfd,0,&CN_st_Parameter_Table);
	if(CN_st_Parameter_Table.Contr0==De_IO_Control)
	{	De_IO_Lock;
		App_CN_st_WorkFlow_Table.CN_st_AgreeOn_Send_Basic.State[De_Orientation_State_Contro]=1;
	}
	else 
	{	De_IO_unLock;
		App_CN_st_WorkFlow_Table.CN_st_AgreeOn_Send_Basic.State[De_Orientation_State_Contro]=0;
	}
	CN_st_Fun_AppSendAgreeOn.Answer(ptst_st_AgreeOn_Dev_Par,fd,De_Suc_Oper);
}
static void ConfineCall(st_st_AgreeOn_Dev_Par	*ptst_st_AgreeOn_Dev_Par,uint8 fd)			//通话限制状态
{ 	st_Parameter_Table	CN_st_Parameter_Table;
	CN_st_Fun_File.ReadRecoder(CN_st_File_fd.Parameterfd,0,&CN_st_Parameter_Table);
	CN_st_Fun_AscNumber.MoveByte(&CN_st_Parameter_Table.CN_st_AgreeOn_ConfineCall,
	ptst_st_AgreeOn_Dev_Par->Buf,sizeof(st_AgreeOn_ConfineCall));
	CN_st_Fun_File.WriteRecoder(CN_st_File_fd.Parameterfd,0,&CN_st_Parameter_Table);
	CN_st_Fun_AppSendAgreeOn.Answer(ptst_st_AgreeOn_Dev_Par,fd,De_Suc_Oper);
}
static void ConfigCentrSever(st_st_AgreeOn_Dev_Par	*ptst_st_AgreeOn_Dev_Par,uint8 fd)//配置中心服务器状态
{	CN_st_Fun_AppSendAgreeOn.Answer(ptst_st_AgreeOn_Dev_Par,fd,De_Suc_Oper);
	;				//重新登录
}
static void Activation(st_st_AgreeOn_Dev_Par	*ptst_st_AgreeOn_Dev_Par,uint8 fd)//激活定位终端
{	;	
}
/*---------------------------------------------功能扩展协议-----------------------------------------------------*/
static void LookJpg(st_st_AgreeOn_Dev_Par	*ptst_st_AgreeOn_Dev_Par,uint8 fd)//查询指定类型的照片
{	CN_st_Fun_AppSendAgreeOn.WriteCommand(fd,De_Dev_Order_UploaderJpg2,ptst_st_AgreeOn_Dev_Par);		
}

static void JpgIng(st_st_AgreeOn_Dev_Par	*ptst_st_AgreeOn_Dev_Par,uint8 fd)//查询实时照片
{	;//CN_st_Fun_AppSendAgreeOn.WriteCommand(fd,De_Dev_Order_UploaderJpg1,ptst_st_AgreeOn_Dev_Par->Buf);;
}
static void SetVidType(st_st_AgreeOn_Dev_Par	*ptst_st_AgreeOn_Dev_Par,uint8 fd)//设置拍照类型
{	uint16 i;
	for(i=0;i<De_CN_Ba_WordPar_Number;i++)
		CN_st_Fun_TakeData.ClearState(i+De_CN_Ba_WordPar_Number);
	CN_st_Fun_File.WriteRecoder(CN_st_File_fd.VidTermfd,0,ptst_st_AgreeOn_Dev_Par->Buf);
	CN_st_Fun_AppSendAgreeOn.Answer(ptst_st_AgreeOn_Dev_Par,fd,De_Suc_Oper);	

}
static void TabelList(st_st_AgreeOn_Dev_Par	*ptst_st_AgreeOn_Dev_Par,uint8 fd)		//设置表单
{	

}
static void LookWorkPar(st_st_AgreeOn_Dev_Par	*ptst_st_AgreeOn_Dev_Par,uint8 fd)	//查询工作参数
{	union
	{	st_File_WorkPar CN_st_File_WorkPar;
		st_AgreeOn_Send_UploaderPar	CN_st_AgreeOn_Send_UploaderPar;
	}un;
	st_st_AgreeOn_Dev_WritePar	CN_st_st_AgreeOn_Dev_WritePar;
	
	uint8 Oper,Tail;
	CN_st_Fun_File.ReadRecoder(CN_st_File_fd.WorkParfd,0,&un.CN_st_File_WorkPar);
	for(Tail=0;Tail<De_CN_Ba_WordPar_Number;Tail++)
	{	if((App_CN_st_WorkFlow_Table.CN_st_WorkVal_Tabel.Type[Tail]==De_st_AgreeOn_Send_Waring_Type_Yes)
		&&(un.CN_st_File_WorkPar.CN_st_File_WorkParVal[Tail].YesOnON==De_WordPar_Open))
		{   GetLessAdree(Tail);
			continue;
		}
		App_CN_st_WorkFlow_Table.CN_st_WorkVal_Tabel.Type[Tail]=De_st_AgreeOn_Send_Waring_Type_No;	
	}
	CN_st_Fun_AscNumber.MoveByte(&un.CN_st_AgreeOn_Send_UploaderPar.CN_st_AgreeOn_Send_Basic,
	&App_CN_st_WorkFlow_Table.CN_st_AgreeOn_Send_Basic,sizeof(st_AgreeOn_Send_Basic));

	CN_st_Fun_AscNumber.MoveByte(&un.CN_st_AgreeOn_Send_UploaderPar.CN_st_WorkVal_Tabel,
	&App_CN_st_WorkFlow_Table.CN_st_WorkVal_Tabel,sizeof(st_WorkVal_Tabel));

	CN_st_st_AgreeOn_Dev_WritePar.OrderNumber=0;
	CN_st_st_AgreeOn_Dev_WritePar.OrderID=De_Dev_Order_UploaderPar;
	CN_st_st_AgreeOn_Dev_WritePar.Buf=&un.CN_st_AgreeOn_Send_UploaderPar;
	CN_st_st_AgreeOn_Dev_WritePar.ContrID=ptst_st_AgreeOn_Dev_Par->ContrID;
	CN_st_Fun_Tzv21.Write(fd,&CN_st_st_AgreeOn_Dev_WritePar,&Oper);		
}
static void WorkParTimer(st_st_AgreeOn_Dev_Par	*ptst_st_AgreeOn_Dev_Par,uint8 fd)//按照固定时间上传工作参数	
{	CN_st_Fun_File.WriteRecoder(CN_st_File_fd.WorkParTimerfd,0,ptst_st_AgreeOn_Dev_Par->Buf);	
	CN_st_Fun_AppSendAgreeOn.Answer(ptst_st_AgreeOn_Dev_Par,fd,De_Suc_Oper);
	;			//重新启动时间	

}
static void WorkParSpace(st_st_AgreeOn_Dev_Par	*ptst_st_AgreeOn_Dev_Par,uint8 fd)//按照间隔上传工作参数
{	st_Parameter_Table	CN_st_Parameter_Table;
	CN_st_Fun_File.ReadRecoder(CN_st_File_fd.Parameterfd,0,&CN_st_Parameter_Table);
	CN_st_Fun_AscNumber.MoveByte(&CN_st_Parameter_Table.CN_Work_st_AgreeOn_Agree_Track,ptst_st_AgreeOn_Dev_Par->Buf,
	sizeof(st_AgreeOn_Agree_Track));
	CN_st_Fun_File.WriteRecoder(CN_st_File_fd.Parameterfd,0,&CN_st_Parameter_Table);
	CN_st_Fun_AppSendAgreeOn.Answer(ptst_st_AgreeOn_Dev_Par,fd,De_Suc_Oper);
}
static void LookLog(st_st_AgreeOn_Dev_Par	*ptst_st_AgreeOn_Dev_Par,uint8 fd)//查询日志文件
{	CN_st_Fun_AppSendAgreeOn.WriteCommand(fd,De_Dev_Order_UploaderLog,ptst_st_AgreeOn_Dev_Par);	

}
static void SetWaringTerm(st_st_AgreeOn_Dev_Par	*ptst_st_AgreeOn_Dev_Par,uint8 fd)//设置报警条件
{	CN_st_Fun_File.WriteRecoder(CN_st_File_fd.WaringTermfd,0,ptst_st_AgreeOn_Dev_Par->Buf);	
	CN_st_Fun_AppSendAgreeOn.Answer(ptst_st_AgreeOn_Dev_Par,fd,De_Suc_Oper);
}
static void LookWaringTerm(st_st_AgreeOn_Dev_Par	*ptst_st_AgreeOn_Dev_Par,uint8 fd)//查询报警条件
{	CN_st_Fun_AppSendAgreeOn.WriteCommand(fd,De_Dev_Order_UpLoaderWarning,ptst_st_AgreeOn_Dev_Par);	


}
/*-----------------------------------------------物流协议专用---------------------------------------------------*/
#define De_Type_Round										1
#define De_Type_Rectangle									2
static void SetRound(st_st_AgreeOn_Dev_Par	*ptst_st_AgreeOn_Dev_Par,uint8 fd)//设置圆形路线
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
static void DelRound(st_st_AgreeOn_Dev_Par	*ptst_st_AgreeOn_Dev_Par,uint8 fd)//删除圆形路线
{	st_AgreeOn_DelRound	*ptst_AgreeOn_DelRound;
	uint16 i;
	ptst_AgreeOn_DelRound=ptst_st_AgreeOn_Dev_Par->Buf;
	for(i=0;i<ptst_AgreeOn_DelRound->Number;i++)
		CN_st_Fun_TakeData.DelAear(ptst_AgreeOn_DelRound->ID[i]);
	CN_st_Fun_AppSendAgreeOn.Answer(ptst_st_AgreeOn_Dev_Par,fd,De_Suc_Oper);	
}
static void SetRectangle(st_st_AgreeOn_Dev_Par	*ptst_st_AgreeOn_Dev_Par,uint8 fd)//设置矩形路线
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
static void DelRectangle(st_st_AgreeOn_Dev_Par	*ptst_st_AgreeOn_Dev_Par,uint8 fd)//删除矩形路线
{	st_AgreeOn_DelRound	*ptst_AgreeOn_DelRound;
	uint16 i;
	ptst_AgreeOn_DelRound=ptst_st_AgreeOn_Dev_Par->Buf;
	for(i=0;i<ptst_AgreeOn_DelRound->Number;i++)
		CN_st_Fun_TakeData.DelAear(ptst_AgreeOn_DelRound->ID[i]);
	CN_st_Fun_AppSendAgreeOn.Answer(ptst_st_AgreeOn_Dev_Par,fd,De_Suc_Oper);
}
static void SetPolygon(st_st_AgreeOn_Dev_Par	*ptst_st_AgreeOn_Dev_Par,uint8 fd)//设置多边形路线
{	CN_st_Fun_AppSendAgreeOn.Answer(ptst_st_AgreeOn_Dev_Par,fd,De_Erro_Oper);	

}
static void DelPolygon(st_st_AgreeOn_Dev_Par	*ptst_st_AgreeOn_Dev_Par,uint8 fd)//删除多边形路线
{	st_AgreeOn_DelRound	*ptst_AgreeOn_DelRound;
	uint16 i;
	ptst_AgreeOn_DelRound=ptst_st_AgreeOn_Dev_Par->Buf;
	for(i=0;i<ptst_AgreeOn_DelRound->Number;i++)
		CN_st_Fun_TakeData.DelAear(ptst_AgreeOn_DelRound->ID[i]);
	CN_st_Fun_AppSendAgreeOn.Answer(ptst_st_AgreeOn_Dev_Par,fd,De_Suc_Oper);
}
static void SetRoadMap(st_st_AgreeOn_Dev_Par	*ptst_st_AgreeOn_Dev_Par,uint8 fd)											//设置路线区域
{	CN_st_Fun_AppSendAgreeOn.Answer(ptst_st_AgreeOn_Dev_Par,fd,De_Suc_Oper);

}
static void DelRoadMap(st_st_AgreeOn_Dev_Par	*ptst_st_AgreeOn_Dev_Par,uint8 fd)											//删除路线区域
{	CN_st_Fun_AppSendAgreeOn.Answer(ptst_st_AgreeOn_Dev_Par,fd,De_Suc_Oper);

}
static void Reduce(st_st_AgreeOn_Dev_Par	*ptst_st_AgreeOn_Dev_Par,uint8 fd)												//设置压缩回传
{ 	st_Reduce_Table	CN_st_Reduce_Table;
	CN_st_Fun_AscNumber.ClsArray(&CN_st_Reduce_Table,sizeof(st_Reduce_Table));
	CN_st_Fun_AscNumber.MoveByte(&CN_st_Reduce_Table.CN_st_AgreeOn_Reduce,ptst_st_AgreeOn_Dev_Par->Buf,sizeof(st_AgreeOn_Reduce));
	CN_st_Fun_File.WriteRecoder(CN_st_File_fd.Reducefd,0,&CN_st_Reduce_Table);
	CN_st_Fun_AppSendAgreeOn.Answer(ptst_st_AgreeOn_Dev_Par,fd,De_Suc_Oper);	
}
static void Driver(st_st_AgreeOn_Dev_Par	*ptst_st_AgreeOn_Dev_Par,uint8 fd)									//设置驾驶员ID
{   uint8 DataLen,DataLen1;
	uint8 Phone[15],i;
	uint8 Message[40];
	uint16 Result;
	st_AgreeOn_Driver *ptst_AgreeOn_Driver;
	ptst_AgreeOn_Driver=ptst_st_AgreeOn_Dev_Par->Buf;
	CN_st_Fun_AscNumber.ClsArray(Phone,sizeof(Phone));
	CN_st_Fun_AscNumber.ClsArray(Message,sizeof(Message));
	Result=GetDriver(Phone);
	CN_st_Fun_File.WriteRecoder(CN_st_File_fd.Driverfd,0,ptst_st_AgreeOn_Dev_Par->Buf);	
	CN_st_Fun_AppSendAgreeOn.Answer(ptst_st_AgreeOn_Dev_Par,fd,De_Suc_Oper);
	if((App_CN_st_WorkFlow_Table.LogState!=0)&&(Result==0))
	{	for(i=0;i<ptst_AgreeOn_Driver->Number;i++)
		{	DataLen=CN_st_Fun_AscNumber.Strsize(ptst_AgreeOn_Driver->CN_st_AgreeOn_Driver_Par[i].ID);
			DataLen1=CN_st_Fun_AscNumber.Strsize(App_CN_st_WorkFlow_Table.DriverID);
			if(DataLen>sizeof(ptst_AgreeOn_Driver->CN_st_AgreeOn_Driver_Par[i].ID))
				DataLen=sizeof(ptst_AgreeOn_Driver->CN_st_AgreeOn_Driver_Par[i].ID);
			if(DataLen!=DataLen1)
				continue;
			if(CN_st_Fun_AscNumber.CompareBuf(ptst_AgreeOn_Driver->CN_st_AgreeOn_Driver_Par[i].ID,App_CN_st_WorkFlow_Table.DriverID,
			DataLen)!=0)
				continue;
			break; 
		}	
		if(i==ptst_AgreeOn_Driver->Number)
		{	App_CN_st_WorkFlow_Table.LogState=0;
			CN_st_Fun_AscNumber.ClsArray(App_CN_st_WorkFlow_Table.DriverID,sizeof(App_CN_st_WorkFlow_Table.DriverID));
			CN_st_Fun_AppSendAgreeOn.WriteFlow(De_Access_Type_ExitLog,&App_CN_st_WorkFlow_Table,NULL);
			DataLen=CN_st_Fun_AscNumber.Strsize(Phone);
			CN_st_Fun_AscNumber.MoveByte(Message,Phone,DataLen);
			CN_st_Fun_AscNumber.MoveByte(Message+DataLen,(uint8 *)"已被中心删除!",13);	
			CN_st_Fun_Gprs.SendMessage(Phone,Message);	
		}
	}

}
static void Navigation(st_st_AgreeOn_Dev_Par	*ptst_st_AgreeOn_Dev_Par,uint8 fd)									//中心导航
{	CN_st_Fun_AppSendAgreeOn.Answer(ptst_st_AgreeOn_Dev_Par,fd,De_Erro_Oper);	

}
static void HandTxt(st_st_AgreeOn_Dev_Par	*ptst_st_AgreeOn_Dev_Par,uint8 fd)										//手机文本调度
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
static void HandAttemper(st_st_AgreeOn_Dev_Par	*ptst_st_AgreeOn_Dev_Par,uint8 fd)								//手机调度信息
{	st_AgreeOn_HandAttemper	*ptst_AgreeOn_HandAttemper;
	union 
	{	st_AgreeOn_Driver	CN_st_AgreeOn_Driver;
		uint8 Message[200];
	}un;
	uint8 Phone[15];
	uint16 DataLen,StrDataLen;
	uint8 i;

	ptst_AgreeOn_HandAttemper=ptst_st_AgreeOn_Dev_Par->Buf;
	if(CN_st_Fun_File.ReadRecoder(CN_st_File_fd.Driverfd,0,&un.CN_st_AgreeOn_Driver)!=De_Suc_File)
	{	CN_st_Fun_AppSendAgreeOn.Answer(ptst_st_AgreeOn_Dev_Par,fd,De_Erro_Oper);
		return ;
	}	
	for(i=0;i<un.CN_st_AgreeOn_Driver.Number;i++)
	{	if(CN_st_Fun_AscNumber.CompareBuf(un.CN_st_AgreeOn_Driver.CN_st_AgreeOn_Driver_Par[i].ID,
			App_CN_st_WorkFlow_Table.DriverID,sizeof(App_CN_st_WorkFlow_Table.DriverID))==0)
			break;
	}
	if(i==un.CN_st_AgreeOn_Driver.Number)
	{	CN_st_Fun_AppSendAgreeOn.Answer(ptst_st_AgreeOn_Dev_Par,fd,De_Erro_Oper);
		return ;
	}
	CN_st_Fun_AscNumber.ClsArray(Phone,sizeof(Phone));
	CN_st_Fun_AscNumber.MoveByte(Phone,un.CN_st_AgreeOn_Driver.CN_st_AgreeOn_Driver_Par[i].Phone,CN_st_Fun_AscNumber.Strsize(un.CN_st_AgreeOn_Driver.CN_st_AgreeOn_Driver_Par[i].Phone));
	CN_st_Fun_AscNumber.ClsArray(un.Message,sizeof(un.Message));
	DataLen=CN_st_Fun_AscNumber.Hex2Asc((uint32) ptst_AgreeOn_HandAttemper->ID,un.Message);
	un.Message[DataLen++]=':';
	StrDataLen=CN_st_Fun_AscNumber.Strsize(ptst_AgreeOn_HandAttemper->Buf);
	if(StrDataLen+DataLen>sizeof(un.Message))
		StrDataLen=sizeof(un.Message)-DataLen;	
   	CN_st_Fun_AscNumber.MoveByte(un.Message+DataLen,ptst_AgreeOn_HandAttemper->Buf,StrDataLen);
	if(CN_st_Fun_Gprs.SendMessage(Phone,un.Message)!=De_Suc_Gprs)
	{ 	CN_st_Fun_AppSendAgreeOn.Answer(ptst_st_AgreeOn_Dev_Par,fd,De_Erro_Oper);
		return ;
	}
	CN_st_Fun_AppSendAgreeOn.Answer(ptst_st_AgreeOn_Dev_Par,fd,De_Suc_Oper);
}	
/*---------------------------------------------出租车协议-------------------------------------------------------*/ 
static void AmendForm(st_st_AgreeOn_Dev_Par	*ptst_st_AgreeOn_Dev_Par,uint8 fd)									//修改订单信息
{	CN_st_Fun_AppSendAgreeOn.Answer(ptst_st_AgreeOn_Dev_Par,fd,De_Erro_Oper);
	

}
static void UpLoaderForm(st_st_AgreeOn_Dev_Par	*ptst_st_AgreeOn_Dev_Par,uint8 fd)								//下发订单抢答信息
{	CN_st_Fun_AppSendAgreeOn.Answer(ptst_st_AgreeOn_Dev_Par,fd,De_Erro_Oper);

}
static void UpLoaderFormSuc(st_st_AgreeOn_Dev_Par	*ptst_st_AgreeOn_Dev_Par,uint8 fd)							//下发订单抢答成功信息
{	CN_st_Fun_AppSendAgreeOn.Answer(ptst_st_AgreeOn_Dev_Par,fd,De_Erro_Oper);

}
static void UpLoaderFormErro(st_st_AgreeOn_Dev_Par	*ptst_st_AgreeOn_Dev_Par,uint8 fd)							//下发订单抢答失败信息
{	CN_st_Fun_AppSendAgreeOn.Answer(ptst_st_AgreeOn_Dev_Par,fd,De_Erro_Oper);

}
static void UpLoaderCan(st_st_AgreeOn_Dev_Par	*ptst_st_AgreeOn_Dev_Par,uint8 fd)								//下发订单取消信息
{	CN_st_Fun_AppSendAgreeOn.Answer(ptst_st_AgreeOn_Dev_Par,fd,De_Erro_Oper);

}



static void SoftWareState(st_FTP_WorkState	*ptst_FTP_WorkState)
{	st_Display_Order_HostSoft	CN_st_Display_Order_HostSoft;
	st_Display_Send		CN_st_Display_Send;
	uint8 fd;
	CN_st_Display_Order_HostSoft.Value=ptst_FTP_WorkState->DownLoaderLen*100/ptst_FTP_WorkState->FileLen;
	CN_st_Display_Send.SendOrAgree=De_Sensor_Display_Send;
	CN_st_Display_Send.ID=De_Display_Host_Order_HostSoft;
	CN_st_Display_Send.SendData=&CN_st_Display_Order_HostSoft;
	if(CN_st_Fun_Sensor.GetPar2ID(De_Sensor_WordPar_Display,&fd)!=De_Suc_Sensor)
		return ;
	CN_st_Fun_Sensor.Read(fd,&CN_st_Display_Send,NULL);	
}
	
static void DownLoaderOver(void)
{	st_AgreeOn_Send_UpdateSoftWare	CN_st_AgreeOn_Send_UpdateSoftWare;
	st_st_AgreeOn_Dev_WritePar	CN_st_st_AgreeOn_Dev_WritePar;
	uint16 Result;
	uint8 fd,Oper;
	void (*ptFun)(void);

	CN_st_AgreeOn_Send_UpdateSoftWare.Result=0;
	CN_st_st_AgreeOn_Dev_WritePar.OrderNumber=0;
	CN_st_st_AgreeOn_Dev_WritePar.OrderID=De_Dev_Order_UpdateSoftWare;
	CN_st_st_AgreeOn_Dev_WritePar.ContrID=0;
	CN_st_st_AgreeOn_Dev_WritePar.Buf=&CN_st_AgreeOn_Send_UpdateSoftWare;
	if((Result=CN_st_Fun_Tzv21.GetPar2ID(De_Sensor_WordPar_GprsTzxy_1,&fd))!=De_Suc_AgreeOn)
		return ;
	if((Result=CN_st_Fun_Tzv21.Write(fd,&CN_st_st_AgreeOn_Dev_WritePar,&Oper))!=De_Suc_AgreeOn)
		return ;
	VICIntEnClr = 0xFFFFFFFF;
	MEMMAP = 0x01;
	ptFun=(void (*)())(0x0);//(void (*)())(0x40000000);												//接受电话
	ptFun();	
		
					
}



static uint16 GetDriver(uint8 *Phone)
{	st_AgreeOn_Driver CN_st_AgreeOn_Driver;
	uint8 i;
	uint16 DataLen;
	if(App_CN_st_WorkFlow_Table.LogState!=0)							//当有驾驶员时
	{	if(CN_st_Fun_File.ReadRecoder(CN_st_File_fd.Driverfd,0,&CN_st_AgreeOn_Driver)!=De_Suc_File)
			return 1;
		for(i=0;i<CN_st_AgreeOn_Driver.Number;i++)
		{	DataLen=CN_st_Fun_AscNumber.Strsize(CN_st_AgreeOn_Driver.CN_st_AgreeOn_Driver_Par[i].ID);
			if(DataLen>sizeof(CN_st_AgreeOn_Driver.CN_st_AgreeOn_Driver_Par[i].ID))
				DataLen=sizeof(CN_st_AgreeOn_Driver.CN_st_AgreeOn_Driver_Par[i].ID);
			if(CN_st_Fun_AscNumber.CompareBuf(CN_st_AgreeOn_Driver.CN_st_AgreeOn_Driver_Par[i].ID,App_CN_st_WorkFlow_Table.DriverID,
			DataLen)!=0)
				continue;
			
		   	CN_st_Fun_AscNumber.MoveByte(Phone,CN_st_AgreeOn_Driver.CN_st_AgreeOn_Driver_Par[i].Phone,15);
			return 0;
		}
		if(i==CN_st_AgreeOn_Driver.Number)
			return 1;				
	}
	return 1;
}


static uint16 GetLessAdree(uint8 Tail)
{	st_File_WorkPar CN_st_File_WorkPar;
	st_st_AgreeOn_Dev_WritePar	CN_st_st_AgreeOn_Dev_WritePar;
	uint8 Oper;
	CN_st_Fun_File.ReadRecoder(CN_st_File_fd.WorkParfd,0,&CN_st_File_WorkPar);
	if(Tail==16)
		CN_st_Fun_AscNumber.MoveByte(&App_CN_st_WorkFlow_Table.CN_st_WorkVal_Tabel.CN_st_AgreeOn_SetVidType_Par.CN_Less_Switch1.Addree,
	    &CN_st_File_WorkPar.CN_st_File_WorkParVal[Tail].Adree,4);
	if(Tail==17)
		CN_st_Fun_AscNumber.MoveByte(&App_CN_st_WorkFlow_Table.CN_st_WorkVal_Tabel.CN_st_AgreeOn_SetVidType_Par.CN_Less_Switch2.Addree,
	    &CN_st_File_WorkPar.CN_st_File_WorkParVal[Tail].Adree,4);
	if(Tail==18)
		CN_st_Fun_AscNumber.MoveByte(&App_CN_st_WorkFlow_Table.CN_st_WorkVal_Tabel.CN_st_AgreeOn_SetVidType_Par.CN_Less_Switch3.Addree,
	    &CN_st_File_WorkPar.CN_st_File_WorkParVal[Tail].Adree,4);
	if(Tail==19)
		CN_st_Fun_AscNumber.MoveByte(&App_CN_st_WorkFlow_Table.CN_st_WorkVal_Tabel.CN_st_AgreeOn_SetVidType_Par.CN_Less_Switch4.Addree,
	    &CN_st_File_WorkPar.CN_st_File_WorkParVal[Tail].Adree,4);
	if(Tail==20)
		CN_st_Fun_AscNumber.MoveByte(&App_CN_st_WorkFlow_Table.CN_st_WorkVal_Tabel.CN_st_AgreeOn_SetVidType_Par.CN_Less_Switch5.Addree,
	    &CN_st_File_WorkPar.CN_st_File_WorkParVal[Tail].Adree,4);
	if(Tail==21)
		CN_st_Fun_AscNumber.MoveByte(&App_CN_st_WorkFlow_Table.CN_st_WorkVal_Tabel.CN_st_AgreeOn_SetVidType_Par.CN_Less_Switch6.Addree,
	    &CN_st_File_WorkPar.CN_st_File_WorkParVal[Tail].Adree,4);
	if(Tail==32)
		CN_st_Fun_AscNumber.MoveByte(&App_CN_st_WorkFlow_Table.CN_st_WorkVal_Tabel.CN_st_AgreeOn_SetVidType_Par.CN_st_AgreeOn_Less_Temp1.Addree,
	    &CN_st_File_WorkPar.CN_st_File_WorkParVal[Tail].Adree,4);
	if(Tail==33)
		CN_st_Fun_AscNumber.MoveByte(&App_CN_st_WorkFlow_Table.CN_st_WorkVal_Tabel.CN_st_AgreeOn_SetVidType_Par.CN_st_AgreeOn_Less_Temp2.Addree,
	    &CN_st_File_WorkPar.CN_st_File_WorkParVal[Tail].Adree,4);
	if(Tail==34)
		CN_st_Fun_AscNumber.MoveByte(&App_CN_st_WorkFlow_Table.CN_st_WorkVal_Tabel.CN_st_AgreeOn_SetVidType_Par.CN_st_AgreeOn_Less_Temp3.Addree,
	    &CN_st_File_WorkPar.CN_st_File_WorkParVal[Tail].Adree,4);
    if(Tail==35)
		CN_st_Fun_AscNumber.MoveByte(&App_CN_st_WorkFlow_Table.CN_st_WorkVal_Tabel.CN_st_AgreeOn_SetVidType_Par.CN_st_AgreeOn_Less_Temp4.Addree,
	    &CN_st_File_WorkPar.CN_st_File_WorkParVal[Tail].Adree,4);
	}



