/*==============================================================================================================
	����ֵ����Ϊ���ࣺ1.��Ҫ�򿪵��豸����;	2.����������������ֵ�������䷶Χ֮��
	����Э���д��ڵģ�ֻ�е����ߴ�������������ʱ�Ų������ϱ���,����˾��Ʒ�����κδ�������������ҲҪ��������
	�����ݿ�����������Э�飬�����з��͡�
*/
#define De_WarningUpate_Compiler
#include "WarningUpate.h"
static void Init(void)
{	OSTaskCreate (Task,(void *)0, &Stk[De_Warning_Stk - 1],De_Warning_Task);	
}



static void Task(void *pData)					//���б���״̬������ж�
{	for(;;OSTimeDly(De_Warning_TaskDly),WatchDog())
	{	JugeWorkPar();			
		JugeGpsState();
	}	
}

static void JugeGpsState(void)					//�ж�GPS����
{	st_Sensor_State	CN_st_Sensor_State;
	uint8 fd;
	if(CN_st_Fun_Sensor.GetPar2ID(De_Sensor_WordPar_Gps,&fd)!=De_Suc_Sensor) 			//�ж�GPS�Ƿ��
	{	App_CN_st_WorkFlow_Table.CN_st_AgreeOn_Send_Basic.State[De_Orientation_State_Gps]=
		De_AgreeOn_State_Suc;
		return ;
	}
	if(CN_st_Fun_Sensor.GetState(&CN_st_Sensor_State,fd)!=De_Suc_Sensor)		//��ȡ������״̬
	{	App_CN_st_WorkFlow_Table.CN_st_AgreeOn_Send_Basic.State[De_Orientation_State_Gps]=
		De_AgreeOn_State_Suc;
		return ;		
	}
	if((CN_st_Sensor_State.Work!=De_Suc_Sensor)||(CN_st_Sensor_State.Battery!=De_Suc_Sensor)
	 ||(CN_st_Sensor_State.Dly!=De_Suc_Sensor))
	{	App_CN_st_WorkFlow_Table.CN_st_AgreeOn_Send_Basic.State[De_Orientation_State_Gps]=
		De_AgreeOn_State_Suc;
		return ;
	}
	App_CN_st_WorkFlow_Table.CN_st_AgreeOn_Send_Basic.State[De_Orientation_State_Gps]=De_AgreeOn_State_Erro;
}

																						  





static void JugeWorkPar(void) 					//�жϹ�������
{	st_File_WorkPar	CN_st_File_WorkPar;
	st_Sensor_State	CN_st_Sensor_State;
	st_Gsm_Net_Information	CN_st_Gsm_Net_Information;
	uint8 fd,i;
	CN_st_Fun_File.ReadRecoder(CN_st_File_fd.WorkParfd,0,&CN_st_File_WorkPar);
	for(i=0;i<De_CN_Ba_WordPar_Number;i++,SendWarning(i))
	{	if(CN_st_File_WorkPar.CN_st_File_WorkParVal[i].YesOnON==De_WordPar_Close)	//�����Ѿ���
			continue;	
		if(CN_st_Fun_Sensor.GetPar2ID(CN_Ba_WordPar[i],&fd)!=De_Suc_Sensor)			//���豸ʱ��������
		{	LoadWaringJugeWorkPar(i,De_Sensor_Par_State_Erro);
		 	continue;
		}
		if(CN_st_Fun_Sensor.GetState(&CN_st_Sensor_State,fd)!=De_Suc_Sensor)		//��ȡ������״̬
		{	LoadWaringJugeWorkPar(i,De_Sensor_Par_State_Erro);
			continue;		
		}
		LoadWaringJugeWorkParState(i,&CN_st_Sensor_State);												
	}
	if(CN_st_File_WorkPar.CN_st_File_WorkParVal[25].YesOnON==De_WordPar_Open) 				//�źŵ����⴦��
	{	CN_st_Fun_Gprs.GetSysState(&CN_st_Gsm_Net_Information);
		App_CN_st_WorkFlow_Table.CN_st_WorkVal_Tabel.CN_st_AgreeOn_SetVidType_Par.Sem
		=CN_st_Gsm_Net_Information.Csq;			
		App_CN_st_WorkFlow_Table.CN_st_WorkVal_Tabel.Type[25]=De_st_AgreeOn_Send_Waring_Type_Yes;
		CN_st_Fun_JugeOper.Juge(25);

	}					
}

static void LoadWaringJugeWorkPar(uint16 Number,uint8 ErroOrOk)
{	uint8 *State;
	uint8 i;
	for(i=0,State==NULL;i<sizeof(CN_Ba_st_Data_Number2Point)/sizeof(st_Data_Number2Point);i++)
	{	if(CN_Ba_st_Data_Number2Point[i].Number==Number)
		{	State=CN_Ba_st_Data_Number2Point[i].State;
			break;
		}
	}
	if(i!=sizeof(CN_Ba_st_Data_Number2Point)/sizeof(st_Data_Number2Point))
		*State=ErroOrOk;			
}

static void LoadWaringJugeWorkParState(uint16 Number,st_Sensor_State	*ptst_Sensor_State)
{	uint8 *State;
	uint8 i;
	for(i=0,State==NULL;i<sizeof(CN_Ba_st_Data_Number2Point)/sizeof(st_Data_Number2Point);i++)
	{	if(CN_Ba_st_Data_Number2Point[i].Number==Number)
		{	State=CN_Ba_st_Data_Number2Point[i].State;
			break;
		}
	}
	if(i!=sizeof(CN_Ba_st_Data_Number2Point)/sizeof(st_Data_Number2Point))
	{	*State=De_Sensor_State_Suc;
		if(ptst_Sensor_State->Work!=De_Sensor_State_Suc)
			*State=De_Sensor_Par_State_Erro;
		if(ptst_Sensor_State->Battery!=De_Sensor_State_Suc)
			*State=De_Sensor_Battery_State_Erro;		
	   	if(ptst_Sensor_State->Dly!=De_Sensor_State_Suc)
			*State=De_Sensor_MaxDly_State_Erro;
	}			
}

static void SendWarning(uint16 Number)
{	uint8 i,Type;
	for(i=0;i<sizeof(CN_Ba_st_Data_Number2Point)/sizeof(st_Data_Number2Point);i++)
	{	if(CN_Ba_st_Data_Number2Point[i].Number==Number)
			break;
	}

	if(i!=sizeof(CN_Ba_st_Data_Number2Point)/sizeof(st_Data_Number2Point))
	{	Type=CN_st_Fun_TakeData.GetState(i+De_Access_Space_LessState);
		if(*CN_Ba_st_Data_Number2Point[i].State!=De_Suc_Sensor)
		{	if(Type==De_Waring_State_Yes)				//�Ѿ���������
				return ;
			if(CN_st_Fun_AppSendAgreeOn.
			WriteFlow(De_Access_Type_LessState,&App_CN_st_WorkFlow_Table,NULL)==De_Suc_AppSendAgree)
			{	CN_st_Fun_TakeData.SetState(i+De_Access_Space_LessState);
				return ;
			}
			return ;	
		}
		if(Type!=De_Waring_State_No)
			CN_st_Fun_TakeData.ClearState(i+De_Access_Space_LessState);		
	}	
}


