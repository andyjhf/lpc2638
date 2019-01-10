





/*==============================================Adc ���ܺ���===========================================================*/
static void HighAdc(st_Data_CheckVoltage	*ptst_Data_CheckVoltage,uint8 fd)		//�ߵ�ѹ�ָ�����
{	if(CN_st_Sys_State.voltage!=De_Suc_State)			//�ָ�����
		InitAdcHighTimer();
}

static void LowAdc(st_Data_CheckVoltage	*ptst_Data_CheckVoltage,uint8 fd)
{	if(CN_st_Sys_State.voltage!=De_State_Voltage_Bad)
		InitAdcLowTimer();								//�͵�ѹ����		
}


static void InitAdcLowTimer(void)
{	union
	{	st_File_Parameter	CN_st_File_Parameter;
		st_Affair_Timer		CN_st_Affair_Timer;
	}a;
	uint16 fd;
	CN_st_Fun_File.Open(De_FileName_Parameter,&fd);
	CN_st_Fun_File.ReadRecoder(fd,0,&a.CN_st_File_Parameter);
	CN_st_Fun_File.Close(fd);
	
	if(CN_st_Sys_State.VoDownfd!=De_Event_No)				
	{	CN_st_Fun_Timer.Close(CN_st_Sys_Event.VoDownfd);	
		CN_st_Sys_Event.VoDownfd=De_Event_No;	
	}
	a.CN_st_Affair_Timer.CN_st_Property_Timer.TimerData=a.CN_st_File_Parameter.LowVolTimer;
	a.CN_st_Affair_Timer.CN_st_Property_Timer.TimerNonce=0;
	a.CN_st_Affair_Timer.CN_st_Function_Timer.ptFun=LowVolWaring;
	CN_st_Fun_Timer.Open(&CN_st_Affair_Timer,&CN_st_Sys_Event.VoDownfd);
}

static void InitAdcHighTimer(void)
{	union
	{	st_File_Parameter	CN_st_File_Parameter;
		st_Affair_Timer		CN_st_Affair_Timer;
	}a;
	uint16 fd;
	CN_st_Fun_File.Open(De_FileName_Parameter,&fd);
	CN_st_Fun_File.ReadRecoder(fd,0,&a.CN_st_File_Parameter);
	CN_st_Fun_File.Close(fd);
	
	if(CN_st_Sys_State.VoUpfd!=De_Event_No)				
	{	CN_st_Fun_Timer.Close(CN_st_Sys_Event.VoUpfd);	
		CN_st_Sys_Event.VoUpfd=De_Event_No;	
	}
	a.CN_st_Affair_Timer.CN_st_Property_Timer.TimerData=a.CN_st_File_Parameter.HighVolTimer;
	a.CN_st_Affair_Timer.CN_st_Property_Timer.TimerNonce=0;
	a.CN_st_Affair_Timer.CN_st_Function_Timer.ptFun=HighVolBack;
	CN_st_Fun_Timer.Open(&CN_st_Affair_Timer,&CN_st_Sys_Event.VoUpfd);
}
/*=============================================Sleep ��ʼ��=============================================================*/
static void SleepInit(void)					//���ߵĳ�ʼ���¼�
{	const st_Affair_Sleep	CN_st_Affair_Sleep={InitTimerSleep,InitTimerWork};
	if(CN_st_Sys_Event.Sleepfd!=De_Event_No)
	{	CN_st_Fun_Sleep.Close(CN_st_Sys_Event.Sleepfd);
		CN_st_Sys_Event.Sleepfd=De_Event_No;	
	}
	CN_st_Sys_Event.Open(&CN_st_Affair_Sleep,&CN_st_Sys_Event.Sleepfd);
}

/*==============================================Acc ��ʼ������=========================================================*/
static void AccInit(void)						//��ʼ��ACC
{	const st_Affair_Acc	CN_st_Affair_Acc={AccLow,AccHigh};
	if(CN_st_Sys_Event.Accfd!=De_Event_No)
	{	CN_st_Fun_Acc.Close(CN_st_Sys_Event.Accfd);
		CN_st_Sys_Event.Accfd=De_Event_No;
	}
	CN_st_Fun_Acc.Open(&CN_st_Affair_Acc,&CN_st_Sys_Event.Accfd);
}
/*=============================================Acc ���ܺ���===========================================================*/
static void AccHigh(st_Data_Acc   *ptst_Data_Acc,uint8 fd)
{	;				//��������������Ϣ




}



static void AccLow(st_Data_Acc   *ptst_Data_Acc,uint8 fd)		//Acc��Ч
{	st_File_Parameter	CN_st_File_Parameter;
	uint32 AccTime;
	uint16 fd;
	InitTimerAcc();										//ϵͳ��������״̬
	CN_st_Fun_File.Open(De_FileName_Parameter,&fd);
	CN_st_Fun_File.ReadRecoder(fd,0,&CN_st_File_Parameter);
	
	if(CN_st_File_Parameter.AccFun==0)						//ACC�����Ƿ�
	{	CN_st_Fun_File.Open(De_FileName_AccTimer,&fd);
		CN_st_Fun_File.ReadRecoder(fd,0,&AccTime);
		AccTime+=ptst_Data_Acc->BackStateTime;
		CN_st_Fun_File.WriteRecoder(fd,0,&AccTime);
	}	
	CN_st_Fun_File.Close(fd);		
}

/*=================================================��ʱ����ʼ��=======================================================*/
static void InitTimerWork(void)											//����״̬�µĳ�ʼ��
{	union
	{	st_File_Parameter	CN_st_File_Parameter;
		st_Affair_Timer		CN_st_Affair_Timer;
		st_File_UpLoader	CN_st_File_UpLoader;
	}a;
	uint16 fd;
	CN_st_Fun_File.Open(De_FileName_Parameter,&fd);
	CN_st_Fun_File.ReadRecoder(fd,0,&a.CN_st_File_Parameter);
	CN_st_Fun_File.Close(fd);
	if(CN_st_Sys_Event.CheckTimer!=De_Event_No)
	{	CN_st_Fun_Timer.Close(CN_st_Sys_Event.CheckTimer);	
		CN_st_Sys_Event.CheckTimer=De_Event_No;							//�ر�T
	}	
	if(a.CN_st_File_Parameter.WorkCheckTimer!=0)						//ϵͳ��ҪѲ��
	{	a.CN_st_Affair_Timer.CN_st_Property_Timer.TimerData=a.CN_st_File_Parameter->WorkCheckTimer;
		a.CN_st_Affair_Timer.CN_st_Property_Timer.TimerNonce=0;
		a.CN_st_Affair_Timer.CN_st_Function_Timer.ptFun=CheckData;
		CN_st_Fun_Timer.Open(&CN_st_Affair_Timer,&CN_st_Sys_Event.CheckTimer);								
	}
	CN_st_Fun_File.Open(De_FileName_TimerUpLoade,&fd);
	CN_st_Fun_File.ReadRecoder(fd,0,&a.CN_st_File_UpLoader);
	CN_st_Fun_File.Close(fd);
	if(CN_st_Sys_Event.Timerfd!=De_Event_No)
	{	CN_st_Fun_Timer.Close(CN_st_Sys_Event.Timerfd);
		CN_st_Sys_Event.Timerfd=De_Event_No;
	}
	if((a.CN_st_File_UpLoader.Timer!=0)&&(a.CN_st_File_UpLoader.Number!=a.CN_st_File_UpLoader.NonceNumber))
	{	a.CN_st_Affair_Timer.CN_st_Property_Timer.TimerData=a.CN_st_File_UpLoader.Timer;
		a.CN_st_Affair_Timer.CN_st_Property_Timer.TimerNonce=0;
		a.CN_st_Affair_Timer.CN_st_Function_Timer.ptFun=SendData;
		CN_st_Fun_Timer.Open(&CN_st_Affair_Timer,&CN_st_Sys_Event.Timerfd);	
	}
	CN_st_Sys_State.Sleep=De_Suc_State;
}

static void InitTimerSleep(void)					//����ʱ��ĳ�ʼ��
{	union
	{	st_File_Parameter	CN_st_File_Parameter;
		st_Affair_Timer		CN_st_Affair_Timer;
	}a;	
	uint16 fd;
	if(CN_st_Sys_Event.Timerfd!=De_Event_No)					//�رն�ʱ����
	{	CN_st_Fun_Timer.Close(CN_st_Sys_Event.Timerfd);
		CN_st_Sys_Event.Timerfd=De_Event_No;
	}
	CN_st_Fun_File.Open(De_FileName_Parameter,&fd);
	CN_st_Fun_File.ReadRecoder(fd,0,&a.CN_st_File_Parameter);
	CN_st_Fun_File.Close(fd);
	if(CN_st_Sys_Event.CheckTimer!=De_Event_No)
	{	CN_st_Fun_Timer.Close(CN_st_Sys_Event.CheckTimer);	
		CN_st_Sys_Event.CheckTimer=De_Event_No;				//�ر�T
	}
	if(a.CN_st_File_Parameter.WorkCheckTimer!=0)			//ϵͳ��ҪѲ��
	{	a.CN_st_Affair_Timer.CN_st_Property_Timer.TimerData=a.CN_st_File_Parameter.SleepCheckTimer;
		a.CN_st_Affair_Timer.CN_st_Property_Timer.TimerNonce=0;
		a.CN_st_Affair_Timer.CN_st_Function_Timer.ptFun=CheckData;
		CN_st_Fun_Timer.Open(&CN_st_Affair_Timer,&CN_st_Sys_Event.CheckTimer);								
	}
	CN_st_Sys_State.Sleep=De_State_Sleep;
}

static void InitTimerAcc(void)					//acc�رպ������¼�
{	union
	{	st_File_Parameter	CN_st_File_Parameter;
		st_Affair_Timer		CN_st_Affair_Timer;
	}a;
	uint16 fd;
	if(CN_st_Sys_Event.AccSleepfd!=De_Event_No)
	{	CN_st_Fun_Timer.Close(CN_st_Sys_Event.AccSleepfd);
		CN_st_Sys_Event.AccSleepfd=De_Event_No;
	}
	CN_st_Fun_File.Open(De_FileName_Parameter,&fd);		
	CN_st_Fun_File.ReadRecoder(fd,0,&a.CN_st_File_Parameter);
	CN_st_Fun_File.Close(fd);
	a.CN_st_Affair_Timer.CN_st_Property_Timer.TimerData=a.CN_st_File_Parameter.SleepTimer;
	a.CN_st_Affair_Timer.CN_st_Property_Timer.TimerNonce=0;
	a.CN_st_Affair_Timer.CN_st_Function_Timer.ptFun=Sleep;
	CN_st_Fun_Timer.Open(&CN_st_Affair_Timer,&CN_st_Sys_Event.AccSleepfd);
}

/*===================================��ʱ����===========================================================*/
static void SendData(st_Data_Timer	*ptst_Data_Timer,uint8 fd)				//��ʱ����
{	st_File_UpLoader	CN_st_File_UpLoader;
	CN_st_Fun_File.Open(De_FileName_TimerUpLoade,&fd);
	CN_st_Fun_File.ReadRecoder(fd,0,&CN_st_File_UpLoader);
	if((a.CN_st_File_UpLoader.Timer==0)||(a.CN_st_File_UpLoader.Number!=a.CN_st_File_UpLoader.NonceNumber))//û�ж�ʱ�¼�
	{	CN_st_Fun_Timer.Close(fd);
		CN_st_Sys_Event.Timerfd=De_Event_No;	
	}
	else
	{	;					//��������
		CN_st_File_UpLoader.NonceNumber++;
		CN_st_Fun_File.WriteRecoder(fd,0,&CN_st_File_UpLoader);
	}
	CN_st_Fun_File.Close(fd);					
}

static void CheckData(st_Data_Timer	*ptst_Data_Timer,uint8 fd)			//Ѳ��
{	uint8 State;
	State=CN_st_Sys_State.Sleep;
	if(State==De_State_Sleep)
	{	;						//���ͻ���Ҫ��
	
	}
	;							//����Ѳ�������
	if(State==De_State_Sleep)
		;						//�������ߵ�Ҫ��
}

static void Sleep(st_Data_Timer	*ptst_Data_Timer,uint8 fd)
{	;							//����������Ϣ
	CN_st_Fun_Timer.Close(fd);	
	CN_st_Sys_Event.AccSleepfd=De_Event_No;

}

static void LowVolWaring(st_Data_Timer	*ptst_Data_Timer,uint8 fd)		//�͵�ѹ����
{	CN_st_Sys_State.voltage=De_State_Voltage_Bad;
	;	//���ͱ������ݳ�ȥ	
	CN_st_Fun_Timer.Close(fd);
	CN_st_Sys_Event.VoDownfd=De_Event_No;
}

static void HighVolBack(st_Data_Timer	*ptst_Data_Timer,uint8 fd)		//��ѹ�ָ�����
{	uint8 State;
	State=CN_st_Sys_State.voltage;
	if(State==De_State_Voltage_Bad)
	{	;//�ָ�����
	}
	CN_st_Sys_State.voltage=De_Suc_State;	
	CN_st_Fun_Timer.Close(fd);
	CN_st_Sys_Event.VoUpfd=De_Event_No;

}


