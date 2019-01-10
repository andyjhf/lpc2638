#define De_JugeOper_Compiler
#include "JugeOper.h"
static void Juge(uint8 Number)
{	uint8 i;
	JugeAppair(Number,CN_st_File_fd.WaringTermfd,De_Access_Space_WorkParWaring1,NULL,De_Access_Space_WorkParWaring1);
	JugeAppair(Number,CN_st_File_fd.VidTermfd,De_Access_Space_VidWaring,1,De_Access_Type_WaringParVid);
	for(i=0;i<De_CN_Ba_WordPar_Number;i++)
	{	if(CN_st_Fun_TakeData.GetState(De_Access_Space_WorkParWaring1+i)==De_Waring_State_Yes)
			break;	
	}
	if(i!=De_CN_Ba_WordPar_Number)
		App_CN_st_WorkFlow_Table.CN_st_AgreeOn_Send_Basic.State[De_Access_Space_WorkParWaring]=De_AgreeOn_State_Erro;
	else
		App_CN_st_WorkFlow_Table.CN_st_AgreeOn_Send_Basic.State[De_Access_Space_WorkParWaring]=De_AgreeOn_State_Suc;
}

static uint16 JugeAppair(uint8 Number,uint8 fd,uint16 Offset,uint8 Vid,uint16 ParWaring)
{	st_AgreeOn_SetWaringTerm	CN_st_AgreeOn_SetWaringTerm;
	uint8 State;
	if(CN_st_Fun_File.ReadRecoder(CN_st_File_fd.WaringTermfd,0,&CN_st_AgreeOn_SetWaringTerm)!=De_Suc_File)
		return ;
	if((CN_st_AgreeOn_SetWaringTerm.Type[Number]!=De_AgreeOn_SetWaringTerm_Type_Stop)&&(CN_st_AgreeOn_SetWaringTerm.Type[Number]!=De_AgreeOn_SetWaringTerm_Type_No))
	{	State=Warning(Number,&CN_st_AgreeOn_SetWaringTerm);
		if(State==De_JugeOper_Warning_Yes)
		{	App_CN_st_WorkFlow_Table.CN_st_AgreeOn_Send_Basic.State[De_Access_Space_WorkParWaring]=De_AgreeOn_State_Erro;		
			if(CN_st_Fun_TakeData.GetState(Number+Offset)!=De_Waring_State_Yes)
			{	if(CN_st_Fun_AppSendAgreeOn.WriteFlow(ParWaring,&App_CN_st_WorkFlow_Table,Vid)==De_Suc_AppSendAgree)
					CN_st_Fun_TakeData.SetState(Number+Offset);	
			}
			return ;
		}
	}
	if(CN_st_Fun_TakeData.GetState(Number+Offset)!=De_Waring_State_No)
		CN_st_Fun_TakeData.ClearState(Number+Offset);
	return ;
}

static uint8 Warning(uint8 Number,void *Data)
{	union
	{	st_Juge_void	CN_st_Juge_void;
		st_Juge_uint8	CN_st_Juge_uint8;
		st_Juge_uint16	CN_st_Juge_uint16;
		st_Juge_uint32	CN_st_Juge_uint32;
		st_Juge_int32	CN_st_Juge_int32;
	}Un_DataJuge;
	if(Number>=sizeof(CN_ParType)/sizeof(uint8))
		return De_AgreeOn_SetWaringTerm_Type_No;
	CN_st_Fun_AscNumber.MoveByte(&Un_DataJuge.CN_st_Juge_void,(void *)&CN_Ba_st_Juge_void[Number],sizeof(Un_DataJuge.CN_st_Juge_void));
	(uint32 )Un_DataJuge.CN_st_Juge_void.State1=(uint32 )Un_DataJuge.CN_st_Juge_void.State1+(uint32 )Data;
	(uint32 )Un_DataJuge.CN_st_Juge_void.State2=(uint32 )Un_DataJuge.CN_st_Juge_void.State2+(uint32 )Data;
	if(CN_ParType[Number]==De_ParType_uint8)
	{	if((*Un_DataJuge.CN_st_Juge_uint8.State3>=*Un_DataJuge.CN_st_Juge_uint8.State1)&&
		(*Un_DataJuge.CN_st_Juge_uint8.State3<=*Un_DataJuge.CN_st_Juge_uint8.State2))
			return De_JugeOper_Warning_Yes;
	}
	else if(CN_ParType[Number]==De_ParType_uint16)
	{	if((*Un_DataJuge.CN_st_Juge_uint16.State3>=*Un_DataJuge.CN_st_Juge_uint16.State1)&&
		(*Un_DataJuge.CN_st_Juge_uint16.State3<=*Un_DataJuge.CN_st_Juge_uint16.State2))
			return De_JugeOper_Warning_Yes;
	}
	else if(CN_ParType[Number]==De_ParType_uint32)
	{	if((*Un_DataJuge.CN_st_Juge_uint32.State3>=*Un_DataJuge.CN_st_Juge_uint32.State1)&&
		(*Un_DataJuge.CN_st_Juge_uint32.State3<=*Un_DataJuge.CN_st_Juge_uint32.State2))
			return De_JugeOper_Warning_Yes;
	}
	else if(CN_ParType[Number]==De_ParType_int32)
	{	if((*Un_DataJuge.CN_st_Juge_int32.State3>=*Un_DataJuge.CN_st_Juge_int32.State1)&&
		(*Un_DataJuge.CN_st_Juge_int32.State3<=*Un_DataJuge.CN_st_Juge_int32.State2))
			return De_JugeOper_Warning_Yes;
	}
   	return De_AgreeOn_SetWaringTerm_Type_No;
}
