#define De_AppAgreeDataSensor_Compiler
#include "AppAgreeDataSensor.h"
static void Init(uint16 *ParID,uint16 SizeofParID)
{	uint16 i;
	uint8 fd;
	const st_Affair_Sensor CN_Ba_st_Affair_Sensor={GetData,NULL};
	CN_st_Fun_SensorContr.Init();
	for(i=0;i<De_Affair_Sensor_MaxNumber;i++)
		CN_st_Fun_SensorContr.Close(i);
	for(i=0;i<SizeofParID;i++)
	{	CN_st_Fun_SensorContr.Open(ParID[i],(st_Affair_Sensor	*)&CN_Ba_st_Affair_Sensor,&fd);
	 	if(ParID[i]==De_Sensor_WordPar_Display)
			CN_st_Fun_DisPlayOper.Init();
	}
}														
static void GetData(uint16 Par,void *Data,uint8 *DateTimer)			//传感器
{	uint16 i;
	Jugeuint8(Par,Data);
	Jugeint32(Par,Data);
	Jugeuint16(Par,Data);
	if(Par==De_Sensor_WordPar_AccTimer)					//ACC时间
		CN_st_Fun_AccOper.Write(Data);
	if(Par==De_Sensor_WordPar_VaCheck)
		VoCheck(Data);
	if(Par==De_Sensor_WordPar_Help)						//紧急报警
		HelpWaring(Data);
	if(Par==De_Sensor_WordPar_Display)
		CN_st_Fun_DisPlayOper.GetData(Data,DateTimer);			
	for(i=0;i<sizeof(CN_Ba_WordPar)/sizeof(uint16);i++)
	{	if(CN_Ba_WordPar[i]==Par)
		{	App_CN_st_WorkFlow_Table.CN_st_WorkVal_Tabel.Type[i]=De_st_AgreeOn_Send_Waring_Type_Yes;
			CN_st_Fun_JugeOper.Juge(i);
			break;
		}
	}		
}

static uint16 Jugeuint8(uint16 Par,uint8 *Data)
{	uint8 i;
	for(i=0;i<sizeof(CN_Ba_st_DataType_uint8)/sizeof(st_DataType_uint8);i++)
	{	if(CN_Ba_st_DataType_uint8[i].Par==Par)
		{	*CN_Ba_st_DataType_uint8[i].Val=*Data;
			return De_Suc_AppAgreeDataSensor;
		}
	}
	return De_Erro_NoData;
}

static uint16 Jugeint32(uint16 Par,int32 *Data)
{	uint8 i;
	for(i=0;i<sizeof(CN_Ba_st_DataType_int32)/sizeof(st_DataType_int32);i++)
	{	if(CN_Ba_st_DataType_int32[i].Par==Par)
		{	*CN_Ba_st_DataType_int32[i].Val=*Data;
			return De_Suc_AppAgreeDataSensor;
		}
	}
	return De_Erro_NoData;
}
static uint16 Jugeuint16(uint16 Par,uint16 *Data)
{	uint8 i;
	for(i=0;i<sizeof(CN_st_DataType_uint16)/sizeof(st_DataType_uint16);i++)
	{	if(CN_st_DataType_uint16[i].Par==Par)
		{	*CN_st_DataType_uint16[i].Val=*Data;
			return De_Suc_AppAgreeDataSensor;
		}
	}
	return De_Erro_NoData;
} 

/*==========================================内容解析============================================================*/
static void VoCheck(void *Data) //电压检测
{	uint32 *Vol,AddTim; 
	uint8 DateTime[7];
	Vol=Data;
	CN_st_Fun_RTC.Read(DateTime);
	AddTim=GetTimeAdd(BackDateTimer,DateTime);
	JugeVo(AddTim,*Vol);					
}

static void JugeVo(uint32 AddTim,uint32 Speed)
{	st_Parameter_Table	CN_st_Parameter_Table;	
	CN_st_Fun_File.ReadRecoder(CN_st_File_fd.Parameterfd,0,&CN_st_Parameter_Table);
	if(!((CN_st_Parameter_Table.CN_st_Sum_Waring.Voltage.WartingVl==0xff*10)&&
	(CN_st_Parameter_Table.CN_st_Sum_Waring.Voltage.WartingTimer==0xff*10)))
	{	if(CN_st_Parameter_Table.CN_st_Sum_Waring.HighSpeed.WartingVl>=Speed)
		{	AddTimeHigh+=AddTim;
			CN_st_Fun_OpenAndClose.OpenGps();
			CN_st_Fun_OpenAndClose.OpenGprs();
			if(AddTimeHigh>=CN_st_Parameter_Table.CN_st_Sum_Waring.Voltage.WartingTimer)
			{	if(CN_st_Fun_TakeData.GetState(De_Access_Space_LowVo)!=De_Waring_State_Yes)
				{	App_CN_st_WorkFlow_Table.CN_st_AgreeOn_Send_Basic.State[De_Access_Type_LowVo]=
					De_AgreeOn_State_Erro;
					if((CN_st_Fun_AppSendAgreeOn.WriteFlow(De_Access_Type_LowVo,&App_CN_st_WorkFlow_Table,NULL))==De_Suc_AppSendAgree)
				   		CN_st_Fun_TakeData.SetState(De_Access_Space_LowVo);	
				}
			}
		}
		else
		{	App_CN_st_WorkFlow_Table.CN_st_AgreeOn_Send_Basic.State[De_Orientation_State_Low]=De_AgreeOn_State_Suc;
			if(CN_st_Fun_TakeData.GetState(De_Access_Space_LowVo)!=De_Waring_State_No)
			{	CN_st_Fun_TakeData.ClearState(De_Access_Space_LowVo);
			}
			AddTimeHigh=0;
		}
	}
	if(Speed==0)
	{	CN_st_Fun_OpenAndClose.OpenGps();
		CN_st_Fun_OpenAndClose.OpenGprs();
		if(CN_st_Fun_TakeData.GetState(De_Access_Space_ClosePower)!=De_Waring_State_Yes)
		{	App_CN_st_WorkFlow_Table.CN_st_AgreeOn_Send_Basic.State[De_Orientation_State_CloseVal]=
			De_AgreeOn_State_Erro;
			if((CN_st_Fun_AppSendAgreeOn.WriteFlow(De_Access_Type_ClosePower,&App_CN_st_WorkFlow_Table,NULL))==De_Suc_AppSendAgree)
		   		CN_st_Fun_TakeData.SetState(De_Access_Space_ClosePower);	
		}
	}
	else
	{	App_CN_st_WorkFlow_Table.CN_st_AgreeOn_Send_Basic.State[De_Orientation_State_CloseVal]=De_AgreeOn_State_Suc;
		if(CN_st_Fun_TakeData.GetState(De_Access_Space_ClosePower)!=De_Waring_State_No)
		{	CN_st_Fun_TakeData.ClearState(De_Access_Space_ClosePower);
		}
	}
}

static void HelpWaring(void *Data)
{	uint8 *Val;
	st_Parameter_Table	CN_st_Parameter_Table;
	Val=Data;	
	if(*Val!=De_Sensor_ACC_Open) 	
		return ;
	CN_st_Fun_File.ReadRecoder(CN_st_File_fd.Parameterfd,0,&CN_st_Parameter_Table);
	if(CN_st_Parameter_Table.CN_st_VidType.HelpWarning==De_AgreeOn_Vid_Fun_Open)
	{	if(CN_st_Fun_TakeData.GetState(De_Access_Space_Help)!=De_Waring_State_Yes)
		{	App_CN_st_WorkFlow_Table.CN_st_AgreeOn_Send_Basic.State[De_Orientation_State_Help]=
			De_AgreeOn_State_Erro;
			if((CN_st_Fun_AppSendAgreeOn.WriteFlow(De_Access_Type_HelpVid,&App_CN_st_WorkFlow_Table,1))==De_Suc_AppSendAgree)
		   		CN_st_Fun_TakeData.SetState(De_Access_Space_Help);
		}
		return ;
	}
	if(CN_st_Fun_TakeData.GetState(De_Access_Space_Help)!=De_Waring_State_Yes)
	{	App_CN_st_WorkFlow_Table.CN_st_AgreeOn_Send_Basic.State[De_Orientation_State_Help]=
		De_AgreeOn_State_Erro;
		if((CN_st_Fun_AppSendAgreeOn.WriteFlow(De_Access_Type_Help,&App_CN_st_WorkFlow_Table,0))==De_Suc_AppSendAgree)
	   		CN_st_Fun_TakeData.SetState(De_Access_Space_Help);
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
