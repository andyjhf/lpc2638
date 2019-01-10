#define De_Space_Compiler
#include "Space.h"
/*===========================================位移发生变化========================================================*/	
static void InitSpace(void)
{	st_Parameter_Table	CN_st_Parameter_Table;
	st_Affair_Data	CN_st_Appair_Data;
	const st_Affair_RunLen	CN_Ba_GetGps={GetGps};
	const st_Affair_RunLen	CN_Ba_Space_Track={Space_Track};
	const st_Affair_RunLen	CN_Ba_Space_WorkParSpace={Space_WorkParSpace};
	uint8 fd;
	if(CN_st_RunLen_Affair_fd.GetGpsfd!=De_Affairfd_Nofd)
		CN_st_Fun_RunLen.Close(CN_st_RunLen_Affair_fd.GetGpsfd);
	if(CN_st_RunLen_Affair_fd.GetTrackfd!=De_Affairfd_Nofd)
		CN_st_Fun_RunLen.Close(CN_st_RunLen_Affair_fd.GetTrackfd);
	if(CN_st_RunLen_Affair_fd.WorkParSpacefd!=De_Affairfd_Nofd)
		CN_st_Fun_RunLen.Close(CN_st_RunLen_Affair_fd.WorkParSpacefd);
	CN_st_Appair_Data.Len=0;
	CN_st_Fun_RunLen.Open(&CN_st_Appair_Data,(st_Affair_RunLen	*)&CN_Ba_GetGps,&CN_st_RunLen_Affair_fd.GetGpsfd);
	CN_st_Fun_File.ReadRecoder(CN_st_File_fd.Parameterfd,0,&CN_st_Parameter_Table);
//	if(CN_st_Parameter_Table.CN_st_AgreeOn_Agree_Track.Space!=0)
//	{	CN_st_Appair_Data.Len=CN_st_Parameter_Table.CN_st_AgreeOn_Agree_Track.Space;
		CN_st_Fun_RunLen.Open(&CN_st_Appair_Data,(st_Affair_RunLen	*)&CN_Ba_Space_Track,&CN_st_RunLen_Affair_fd.GetTrackfd);	
//	}
//	if(CN_st_Parameter_Table.CN_Work_st_AgreeOn_Agree_Track.Space!=0)
//	{	CN_st_Appair_Data.Len=CN_st_Parameter_Table.CN_Work_st_AgreeOn_Agree_Track.Space;
		CN_st_Fun_RunLen.Open(&CN_st_Appair_Data,(st_Affair_RunLen	*)&CN_Ba_Space_WorkParSpace,&CN_st_RunLen_Affair_fd.WorkParSpacefd);	
//	}
	CN_st_Fun_AscNumber.ClsArray(BackDate,sizeof(BackDate));
	CN_st_Fun_RTC.Read(BackDate);
	App_CN_st_WorkFlow_Table.CN_st_WorkVal_Tabel.Type[23]=De_st_AgreeOn_Send_Waring_Type_Yes;				
}

static void GetGps(st_File_Gps	*ptst_File_Gps,uint8 fd)	 						//里程统计计算
{	st_File_Gps	CN_st_File_Gps;
	uint32 AddTim;
	uint8 DateTime[7];
	CN_st_Fun_AscNumber.ClsArray(&CN_st_File_Gps,sizeof(st_File_Gps));
	if(ptst_File_Gps->Milage!=0)
	{	if(CN_st_Fun_File.ReadRecoder(CN_st_File_fd.Gpsfd,0,&CN_st_File_Gps)!=De_Suc_File)
			CN_st_Fun_AscNumber.ClsArray(&CN_st_File_Gps,sizeof(st_File_Gps));
		CN_st_Fun_AscNumber.MoveByte(&CN_st_File_Gps.CN_st_Data_Gps,&ptst_File_Gps->CN_st_Data_Gps,
		sizeof(st_Data_Gps));
		CN_st_File_Gps.Milage+=ptst_File_Gps->Milage;
		CN_st_Fun_File.WriteRecoder(CN_st_File_fd.Gpsfd,0,&CN_st_File_Gps);
		App_CN_st_WorkFlow_Table.CN_st_WorkVal_Tabel.CN_st_AgreeOn_SetVidType_Par.Mileage=CN_st_File_Gps.Milage;
	}
	CN_st_Fun_AscNumber.MoveByte(&App_CN_st_WorkFlow_Table.CN_st_AgreeOn_Send_Basic.CN_st_Data_Gps,
	&ptst_File_Gps->CN_st_Data_Gps,sizeof(st_Data_Gps));
	App_CN_st_WorkFlow_Table.CN_st_AgreeOn_Send_Basic.State[De_Orientation_State_GpsLatitude]=De_AgreeOn_State_Suc;
	if(App_CN_st_WorkFlow_Table.CN_st_AgreeOn_Send_Basic.CN_st_Data_Gps.CN_st_Gps_Data_GPRMC.LatHem=='N')
		App_CN_st_WorkFlow_Table.CN_st_AgreeOn_Send_Basic.State[De_Orientation_State_GpsLatitude]=De_AgreeOn_State_Erro;
	App_CN_st_WorkFlow_Table.CN_st_AgreeOn_Send_Basic.State[De_Orientation_State_GpsLongitude]=De_AgreeOn_State_Suc;
	if(App_CN_st_WorkFlow_Table.CN_st_AgreeOn_Send_Basic.CN_st_Data_Gps.CN_st_Gps_Data_GPRMC.LongHem=='E')
		App_CN_st_WorkFlow_Table.CN_st_AgreeOn_Send_Basic.State[De_Orientation_State_GpsLongitude]=De_AgreeOn_State_Erro;	
	App_CN_st_WorkFlow_Table.CN_st_WorkVal_Tabel.Type[23]=De_st_AgreeOn_Send_Waring_Type_Yes;

	App_CN_st_WorkFlow_Table.CN_st_AgreeOn_Send_Basic.State[De_State_Gps]=De_AgreeOn_State_Erro;	
	AddTim=GetTimeAdd(BackDate,
	App_CN_st_WorkFlow_Table.CN_st_AgreeOn_Send_Basic.CN_st_Data_Gps.CN_st_Gps_Data_GPRMC.DateTime);
	JugeSpeed(AddTim,App_CN_st_WorkFlow_Table.CN_st_AgreeOn_Send_Basic.CN_st_Data_Gps.CN_st_Gps_Data_GPRMC.Speed);
	CN_st_Fun_AscNumber.MoveByte(BackDate,App_CN_st_WorkFlow_Table.CN_st_AgreeOn_Send_Basic.CN_st_Data_Gps.CN_st_Gps_Data_GPRMC.DateTime,
	sizeof(BackDate));
	
	CN_st_Fun_JugeOper.Juge(23);
	CN_st_Fun_RTC.Read(DateTime);
	if(CN_st_Fun_AscNumber.CompareBuf(DateTime,ptst_File_Gps->CN_st_Data_Gps.CN_st_Gps_Data_GPRMC.DateTime,sizeof(DateTime))!=0)
	{	CN_st_Fun_AscNumber.MoveByte(DateTime,ptst_File_Gps->CN_st_Data_Gps.CN_st_Gps_Data_GPRMC.DateTime,sizeof(DateTime));
		CN_st_Fun_RTC.Write(DateTime);
	}
				
}

static void Space_Track(st_File_Gps	*ptst_File_Gps,uint8 fd)						//位移变化以后,追踪命令
{	st_Parameter_Table CN_st_Parameter_Table;
	if(CN_st_Fun_File.ReadRecoder(CN_st_File_fd.Parameterfd,0,&CN_st_Parameter_Table)!=De_Suc_File)
		return;
	if(CN_st_Parameter_Table.CN_st_AgreeOn_Agree_Track.Space==0)
		return;
	CN_st_RunLen_Affair_fd.TrackSpace+=ptst_File_Gps->Milage;
	if(CN_st_RunLen_Affair_fd.TrackSpace<CN_st_Parameter_Table.CN_st_AgreeOn_Agree_Track.Space)
		return;
	ptst_File_Gps->Milage=0;
	CN_st_RunLen_Affair_fd.TrackSpace=0;
	GetGps(ptst_File_Gps,fd);
	CN_st_Fun_AppSendAgreeOn.WriteFlow(De_Access_Type_Track,&App_CN_st_WorkFlow_Table,NULL);				//发送追踪指令
}

static void Space_WorkParSpace(st_File_Gps	*ptst_File_Gps,uint8 fd)   				//位移发生变化以后,工作参数上传
{	st_Parameter_Table CN_st_Parameter_Table;
	if(CN_st_Fun_File.ReadRecoder(CN_st_File_fd.Parameterfd,0,&CN_st_Parameter_Table)!=De_Suc_File)
		return;
	if(CN_st_Parameter_Table.CN_Work_st_AgreeOn_Agree_Track.Space==0)
		return;
	CN_st_RunLen_Affair_fd.WorkParSpace+=ptst_File_Gps->Milage;
	if(CN_st_RunLen_Affair_fd.WorkParSpace<CN_st_Parameter_Table.CN_Work_st_AgreeOn_Agree_Track.Space)
		return;
	CN_st_RunLen_Affair_fd.WorkParSpace=0;
	ptst_File_Gps->Milage=0;
	GetGps(ptst_File_Gps,fd);
	CN_st_Fun_AppSendAgreeOn.WriteFlow(De_Access_Type_WorkPar,&App_CN_st_WorkFlow_Table,NULL);				//发送工作参数指令
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
static void JugeSpeed(uint32 AddTim,uint8 Speed)
{	st_Parameter_Table	CN_st_Parameter_Table;	
	CN_st_Fun_File.ReadRecoder(CN_st_File_fd.Parameterfd,0,&CN_st_Parameter_Table);
	if(!((CN_st_Parameter_Table.CN_st_Sum_Waring.HighSpeed.WartingVl==0xff)&&
	(CN_st_Parameter_Table.CN_st_Sum_Waring.HighSpeed.WartingTimer==0xff)))
	{	if(Speed>=CN_st_Parameter_Table.CN_st_Sum_Waring.HighSpeed.WartingVl)
		{	CN_st_Fun_OpenAndClose.OpenGps();
			CN_st_Fun_OpenAndClose.OpenGprs();
			AddTimeHigh+=AddTim;
			if(AddTimeHigh>=CN_st_Parameter_Table.CN_st_Sum_Waring.HighSpeed.WartingTimer)
			{	if(CN_st_Fun_TakeData.GetState(De_Access_Space_HighSpeed)!=De_Waring_State_Yes)
				{	App_CN_st_WorkFlow_Table.CN_st_AgreeOn_Send_Basic.State[De_Orientation_State_HighSpeed]=
					De_AgreeOn_State_Erro;
					if((CN_st_Fun_AppSendAgreeOn.WriteFlow(De_Orientation_State_HighSpeed,&App_CN_st_WorkFlow_Table,NULL))==De_Suc_AppSendAgree)
				   		CN_st_Fun_TakeData.SetState(De_Access_Space_HighSpeed);	
				}
			}
		}
		else
		{	App_CN_st_WorkFlow_Table.CN_st_AgreeOn_Send_Basic.State[De_Orientation_State_HighSpeed]=De_AgreeOn_State_Suc;
			if(CN_st_Fun_TakeData.GetState(De_Access_Space_HighSpeed)!=De_Waring_State_No)
			{	CN_st_Fun_TakeData.ClearState(De_Access_Space_HighSpeed);
			}
			AddTimeHigh=0;
		}
	}
	if(!((CN_st_Parameter_Table.CN_st_Sum_Waring.HighSpeed.WartingVl==0xff)&&
	(CN_st_Parameter_Table.CN_st_Sum_Waring.LowSpeed.WartingTimer==0xff)))
	{	if(CN_st_Parameter_Table.CN_st_Sum_Waring.LowSpeed.WartingVl>=Speed)
		{	AddTimeLow+=AddTim;
			CN_st_Fun_OpenAndClose.OpenGps();
			CN_st_Fun_OpenAndClose.OpenGprs();
			if(AddTimeLow>=CN_st_Parameter_Table.CN_st_Sum_Waring.LowSpeed.WartingTimer)
			{	if(CN_st_Fun_TakeData.GetState(De_Access_Space_LowSpeed)!=De_Waring_State_Yes)
				{	App_CN_st_WorkFlow_Table.CN_st_AgreeOn_Send_Basic.State[De_Orientation_State_LowSpeed]=
					De_AgreeOn_State_Erro;
					if((CN_st_Fun_AppSendAgreeOn.WriteFlow(De_Orientation_State_HighSpeed,&App_CN_st_WorkFlow_Table,NULL))==De_Suc_AppSendAgree)
				   		CN_st_Fun_TakeData.SetState(De_Access_Space_LowSpeed);	
				}
			}
		}
		else
		{	App_CN_st_WorkFlow_Table.CN_st_AgreeOn_Send_Basic.State[De_Orientation_State_LowSpeed]=De_AgreeOn_State_Suc;
			if(CN_st_Fun_TakeData.GetState(De_Access_Space_LowSpeed)!=De_Waring_State_No)
			{	CN_st_Fun_TakeData.ClearState(De_Access_Space_LowSpeed);
			}
			AddTimeLow=0;
		}
	}
}
/*
static void JugeArea(st_File_Gps	*ptst_File_Gps)					//判断是否区域报警
{	union
	{	st_AgreeOn_SetRound_Par	CN_st_AgreeOn_SetRound_Par;
		st_AgreeOn_SetRectangle_Par	CN_st_AgreeOn_SetRectangle_Par;
	}Un_Data;
	uint16 i;	
	uint8 Type;
	for(i=0;i<50;i++)
	{	if(CN_st_Fun_TakeData.GetAreaData(&Un_Data,i,&Type)!=De_Suc_AccessBasic)
			return ;	
	   	if(Type==De_Type_Round)
		{	




		}

	}

}*/			



