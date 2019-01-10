#define De_AccOper_Compiler
#include "AccOper.h"
/*========================================ACC运行===============================================================*/
static void AccOper(void *Data)
{	st_Sensor_Data_Acc	*ptst_Sensor_Data_Acc;
	ptst_Sensor_Data_Acc=Data;
	if(AccUse==NULL)	  												//ACC没有使用
	{	AccState=ptst_Sensor_Data_Acc->NonState;
		CN_st_Fun_AscNumber.ClsArray(AddTimerNumber,sizeof(AddTimerNumber));
		AccUse=1;
		GetData();
	}
	if(ptst_Sensor_Data_Acc->NonState==De_Sensor_ACC_Open)
		App_CN_st_WorkFlow_Table.CN_st_AgreeOn_Send_Basic.State[De_Orientation_State_ACC]=De_AgreeOn_State_Erro;
	else
		App_CN_st_WorkFlow_Table.CN_st_AgreeOn_Send_Basic.State[De_Orientation_State_ACC]=De_AgreeOn_State_Suc;	
	if(AccState!=ptst_Sensor_Data_Acc->NonState)						//如果状态发生改变
	{	AccState=ptst_Sensor_Data_Acc->NonState;
		AccStateChange(AccState);
		return ;	
	}
	if(AccState==De_Sensor_ACC_Open)
		AccOpen(ptst_Sensor_Data_Acc);
	else
		AccClose(ptst_Sensor_Data_Acc);
	JugeTimerPar(ptst_Sensor_Data_Acc);
	GetData();
				
}
/*==========================================各个状态运行=======================================================*/

static void AccStateChange(uint8 State)													//当ACC状态发生改变时
{	st_Parameter_Table	CN_st_Parameter_Table;
	uint8 fd;
	CN_st_Fun_File.ReadRecoder(CN_st_File_fd.Parameterfd,0,&CN_st_Parameter_Table);
	if(State==De_Sensor_ACC_Open)										//ACC打开
	{	CN_st_Fun_OpenAndClose.OpenGps();
		CN_st_Fun_OpenAndClose.OpenGprs();
		if(CN_st_Parameter_Table.CN_st_VidType.AccOpen==De_AgreeOn_Vid_Fun_Open)		//拍照功能打开
			CN_st_Fun_AppSendAgreeOn.WriteFlow(De_Access_Type_AccOpenVid,&App_CN_st_WorkFlow_Table,1);	
		for(fd=0;fd<sizeof(CN_Ba_AccClose_st_Affair_Term)/sizeof(st_Affair_Term);fd++)
			*CN_Ba_AccClose_st_Affair_Term[fd].Val2=0;
		for(fd=0;fd<sizeof(CN_Ba_st_Affair_TermClose)/sizeof(st_Affair_TermClose);fd++)
			*CN_Ba_st_Affair_TermClose[fd].Val2=0;				
	}
	else
	{	if(CN_st_Parameter_Table.CN_st_VidType.AccClose==De_AgreeOn_Vid_Fun_Open)		//拍照功能打开
			CN_st_Fun_AppSendAgreeOn.WriteFlow(De_Access_Type_AccCloseVid,&App_CN_st_WorkFlow_Table,1);	
		for(fd=0;fd<sizeof(CN_Ba_AccOpen_st_Affair_Term)/sizeof(st_Affair_Term);fd++)
			*CN_Ba_AccOpen_st_Affair_Term[fd].Val2=0;
	}	
}

static void AccOpen(st_Sensor_Data_Acc	*ptst_Sensor_Data_Acc)							//acc开时的任务
{	uint8 i;
	for(i=0;i<sizeof(CN_Ba_AccOpen_st_Affair_Term)/sizeof(st_Affair_Term);i++)
	{	if(*CN_Ba_AccOpen_st_Affair_Term[i].Val1==De_No_Data_Send)
			continue;
		*CN_Ba_AccOpen_st_Affair_Term[i].Val2+=ptst_Sensor_Data_Acc->AccTimer;
		if(*CN_Ba_AccOpen_st_Affair_Term[i].Val2<*CN_Ba_AccOpen_st_Affair_Term[i].Val1)		 	
			continue;
		CN_st_Fun_AppSendAgreeOn.WriteFlow(CN_Ba_AccOpen_st_Affair_Term[i].Par,&App_CN_st_WorkFlow_Table,NULL);
		*CN_Ba_AccOpen_st_Affair_Term[i].Val2=0;
	}
	AccTimer(ptst_Sensor_Data_Acc);
}

static void AccClose(st_Sensor_Data_Acc	*ptst_Sensor_Data_Acc)
{	uint8 i;
	for(i=0;i<sizeof(CN_Ba_AccClose_st_Affair_Term)/sizeof(st_Affair_Term);i++)
	{	if(*CN_Ba_AccClose_st_Affair_Term[i].Val1==De_No_Data_Send)
			continue;
		*CN_Ba_AccClose_st_Affair_Term[i].Val2+=ptst_Sensor_Data_Acc->AccTimer;
		if(*CN_Ba_AccClose_st_Affair_Term[i].Val2<*CN_Ba_AccClose_st_Affair_Term[i].Val1)		 	
			continue;
		CN_st_Fun_AppSendAgreeOn.WriteFlow(CN_Ba_AccClose_st_Affair_Term[i].Par,&App_CN_st_WorkFlow_Table,NULL);
		*CN_Ba_AccClose_st_Affair_Term[i].Val2=0;
	}
	for(i=0;i<sizeof(CN_Ba_OpenMachi_Term)/sizeof(st_GpsJuge_Term);i++)
	{	if(*CN_Ba_OpenMachi_Term[i].Val1==De_No_Data_Send)
			continue;	
		if(*CN_Ba_OpenMachi_Term[i].Val2>*CN_Ba_OpenMachi_Term[i].Val1)
		{	CN_Ba_OpenMachi_Term[i].ptFun();
			continue;
		}
		if((*CN_Ba_OpenMachi_Term[i].Val1-*CN_Ba_OpenMachi_Term[i].Val2)>CN_Ba_OpenMachi_Term[i].Val)
			continue;
		CN_Ba_OpenMachi_Term[i].ptFun();
	}
	for(i=0;i<sizeof(CN_Ba_st_Affair_TermClose)/sizeof(st_Affair_TermClose);i++)
	{	if(*CN_Ba_st_Affair_TermClose[i].Val1==De_No_Data_Send)
			continue;
		*CN_Ba_st_Affair_TermClose[i].Val2+=ptst_Sensor_Data_Acc->AccTimer;
		if(*CN_Ba_st_Affair_TermClose[i].Val2<*CN_Ba_st_Affair_TermClose[i].Val1)		 	
			continue;
		CN_Ba_st_Affair_TermClose[i].ptFun();
	}	
}
static void JugeTimerPar(st_Sensor_Data_Acc	*ptst_Sensor_Data_Acc)
{	uint8 i;
	for(i=0;i<sizeof(CN_Ba_TimerPar_Term)/sizeof(st_GpsJuge_Term);i++)
	{	if(*CN_Ba_TimerPar_Term[i].Val1==De_No_Data_Send)
			continue;
		*CN_Ba_TimerPar_Term[i].Val2+=ptst_Sensor_Data_Acc->AccTimer;
		if(*CN_Ba_TimerPar_Term[i].Val2<*CN_Ba_TimerPar_Term[i].Val1)
			continue;
		CN_st_Fun_AppSendAgreeOn.WriteFlow(De_Access_Type_WorkPar,&App_CN_st_WorkFlow_Table,NULL);
	}	
}

static uint32 GetTimeAdd(uint8 *Small,uint8 *Big)
{	uint8 Curtimer[7];
	uint32 i;
	if(CN_st_Fun_AscNumber.CompareVa(Big,Small,7,De_AscNumber_Va_Big)!=De_AscNumber_Va_True)
		return 0;
	if((CN_st_Fun_Date.Juge(Small,De_Type_Date_Second)!=De_Suc_Date)||(CN_st_Fun_Date.Juge(Big,De_Type_Date_Second)!=De_Suc_Date))
		return 0;
	CN_st_Fun_AscNumber.MoveByte(Curtimer,Small,7);
	for(i=0;CN_st_Fun_AscNumber.CompareBuf(Curtimer,Big,7)!=0;i++)
		CN_st_Fun_Date.Next(Curtimer,De_Type_Date_Second);	
	return i;				
}

static void GetData(void)											//获取数据
{	st_Parameter_Table	CN_st_Parameter_Table;
	st_AgreeOn_WorkParTimer	CN_st_AgreeOn_WorkParTimer;
	st_Reduce_Table		CN_st_Reduce_Table;	
	uint8 i;
	uint8 DateTime[7],NonceTimer[7];
	CN_st_Fun_RTC.Read(NonceTimer);
	
	for(i=0;i<sizeof(AddTimerNumber)/sizeof(uint32);i++)
		EndTimerNumber[i]=De_No_Data_Send;		
   	if(CN_st_Fun_File.ReadRecoder(CN_st_File_fd.Parameterfd,0,&CN_st_Parameter_Table)==De_Suc_File)	//追踪类参数
	{	if(CN_st_Parameter_Table.CN_st_AgreeOn_Agree_Track.AccOpenTimer!=0)
			EndTimerNumber[0]=CN_st_Parameter_Table.CN_st_AgreeOn_Agree_Track.AccOpenTimer;
		if(CN_st_Parameter_Table.CN_Work_st_AgreeOn_Agree_Track.AccOpenTimer!=0)
			EndTimerNumber[1]=CN_st_Parameter_Table.CN_Work_st_AgreeOn_Agree_Track.AccOpenTimer;			
		if(CN_st_Parameter_Table.CN_st_AgreeOn_Agree_Track.AccCloseTimer!=0)
			EndTimerNumber[3]=CN_st_Parameter_Table.CN_st_AgreeOn_Agree_Track.AccCloseTimer;
		if(CN_st_Parameter_Table.CN_Work_st_AgreeOn_Agree_Track.AccCloseTimer!=0)
			EndTimerNumber[4]=CN_st_Parameter_Table.CN_Work_st_AgreeOn_Agree_Track.AccCloseTimer;
		if(CN_st_Parameter_Table.CN_st_Sleep_Par.GpsTimer!=0)
			EndTimerNumber[6]=CN_st_Parameter_Table.CN_st_Sleep_Par.GpsTimer;
		if(CN_st_Parameter_Table.CN_st_Sleep_Par.GprsTimer!=0)
			EndTimerNumber[7]=CN_st_Parameter_Table.CN_st_Sleep_Par.GprsTimer;
	}
	if(CN_st_Fun_File.ReadRecoder(CN_st_File_fd.Reducefd,0,&CN_st_Reduce_Table)==De_Suc_File)
	{	if((CN_st_Reduce_Table.CN_st_AgreeOn_Reduce.AccOpenTimer!=0)&&(CN_st_Reduce_Table.CN_st_AgreeOn_Reduce.Number!=0))
			EndTimerNumber[2]=CN_st_Reduce_Table.CN_st_AgreeOn_Reduce.AccOpenTimer;
		if((CN_st_Reduce_Table.CN_st_AgreeOn_Reduce.AccOpenTimer!=0)&&(CN_st_Reduce_Table.CN_st_AgreeOn_Reduce.Number!=0))
			EndTimerNumber[5]=CN_st_Reduce_Table.CN_st_AgreeOn_Reduce.AccCloseTimer;
	}
	if(CN_st_Fun_File.ReadRecoder(CN_st_File_fd.WorkParTimerfd,0,&CN_st_AgreeOn_WorkParTimer)!=De_Suc_File)
		return ;
	for(i=8;i<sizeof(EndTimerNumber)/sizeof(uint32);i++)
	{	CN_st_Fun_AscNumber.MoveByte(DateTime,NonceTimer,4);
		CN_st_Fun_AscNumber.MoveByte(DateTime+4,CN_st_AgreeOn_WorkParTimer.Timer[i-8],3);
		if(CN_st_Fun_AscNumber.CompareVa(DateTime,NonceTimer,7,De_AscNumber_Va_Big)==De_AscNumber_Va_Flase)
			EndTimerNumber[i]=86400-GetTimeAdd(DateTime,NonceTimer);
		else
			EndTimerNumber[i]=GetTimeAdd(DateTime,NonceTimer);		
	}				
}
/*=========================================ACC时间类============================================================*/
static void AccTimer(st_Sensor_Data_Acc	*ptst_Sensor_Data_Acc)					//统计ACC时间
{	st_AccTimer	CN_st_AccTimer;
	st_File_WorkPar	CN_st_File_WorkPar;
	CN_st_Fun_File.ReadRecoder(CN_st_File_fd.AccTimerfd,0,&CN_st_AccTimer);
	if(ptst_Sensor_Data_Acc->AccTimer!=0)
	{	CN_st_AccTimer.AccTimer+=ptst_Sensor_Data_Acc->AccTimer;
		CN_st_Fun_File.WriteRecoder(CN_st_File_fd.AccTimerfd,0,&CN_st_AccTimer);
	}
	App_CN_st_WorkFlow_Table.CN_st_WorkVal_Tabel.CN_st_AgreeOn_SetVidType_Par.AccTimer=
	CN_st_AccTimer.AccTimer;	
	//CN_st_Fun_File.ReadRecoder(CN_st_File_fd.WorkParfd,0,&CN_st_File_WorkPar);
	//if(CN_st_File_WorkPar[])

}

static void OpenGps(void)
{	CN_st_Fun_OpenAndClose.OpenGps();
}
static void OpenGprs(void)
{	CN_st_Fun_OpenAndClose.OpenGprs();
}
static void CloseGps(void)
{	CN_st_Fun_OpenAndClose.CloseGps();
}
static void CloseGprs(void)
{	CN_st_Fun_OpenAndClose.CloseGprs();
}


