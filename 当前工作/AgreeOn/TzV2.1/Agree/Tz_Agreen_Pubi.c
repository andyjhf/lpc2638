static void Explain_Par(uint8 *Buf,st_AgreeOn_Agree_Par_Cut	*ptst_AgreeOn_Agree_Par_Cut,uint16 WordPar,uint16 ParDataLen);
static void Explain_WorkPar(uint8 *Buf,st_AgreeOn_SetVidType  *ptst_AgreeOn_SetVidType,uint16 WorkID,uint16 Len,uint8 type);
static void Explain_Par(uint8 *Buf,st_AgreeOn_Agree_Par_Cut	*ptst_AgreeOn_Agree_Par_Cut,uint16 WordPar,uint16 ParDataLen)
{	uint8 j,k;
	if(WordPar==De_SetPar_SetGreenPar) 				//�趨�������				
	{	ptst_AgreeOn_Agree_Par_Cut->GreenPar=Buf[0]*0x100+Buf[1];	
	}
	else if(WordPar==De_SetPar_SetGreenWord)		//���ý�������
	{ 	if(ParDataLen>sizeof(ptst_AgreeOn_Agree_Par_Cut->GreenWord))
			ParDataLen=sizeof(ptst_AgreeOn_Agree_Par_Cut->GreenWord);
		CN_st_Fun_AscNumber.MoveByte(ptst_AgreeOn_Agree_Par_Cut->GreenWord,Buf,ParDataLen);
	}
	else if(WordPar==De_SetPar_SetListePhone)		//���ü�������
	{	if(ParDataLen>sizeof(ptst_AgreeOn_Agree_Par_Cut->ListePhone))
			ParDataLen=sizeof(ptst_AgreeOn_Agree_Par_Cut->ListePhone);
		CN_st_Fun_AscNumber.MoveByte(ptst_AgreeOn_Agree_Par_Cut->ListePhone,Buf,ParDataLen);
	}
	else if(WordPar==De_SetPar_SetResetPhone)		//���õ绰��λ
	{	if(ParDataLen>sizeof(ptst_AgreeOn_Agree_Par_Cut->ResetPhone))
			ParDataLen=sizeof(ptst_AgreeOn_Agree_Par_Cut->ResetPhone);
		CN_st_Fun_AscNumber.MoveByte(ptst_AgreeOn_Agree_Par_Cut->ResetPhone,Buf,ParDataLen);
	}
	else if(WordPar==De_SetPar_SetCerSevPhone)		//���ö������ķ������
	{	if(ParDataLen>sizeof(ptst_AgreeOn_Agree_Par_Cut->CerSevPhone))
			ParDataLen=sizeof(ptst_AgreeOn_Agree_Par_Cut->CerSevPhone);
		CN_st_Fun_AscNumber.MoveByte(ptst_AgreeOn_Agree_Par_Cut->CerSevPhone,Buf,ParDataLen);
	}
	else if(WordPar==De_SetPar_SetCenPhone)		//�������ö�������
	{	if(ParDataLen>sizeof(ptst_AgreeOn_Agree_Par_Cut->CenPhone))
			ParDataLen=sizeof(ptst_AgreeOn_Agree_Par_Cut->CenPhone);
		CN_st_Fun_AscNumber.MoveByte(ptst_AgreeOn_Agree_Par_Cut->CenPhone,Buf,ParDataLen);
	}
	else if(WordPar==De_SetPar_SetAPN)			//����APN����
	{	if(ParDataLen>sizeof(ptst_AgreeOn_Agree_Par_Cut->APN))
			ParDataLen=sizeof(ptst_AgreeOn_Agree_Par_Cut->APN);
		CN_st_Fun_AscNumber.MoveByte(ptst_AgreeOn_Agree_Par_Cut->APN,Buf,ParDataLen);
	}
	else if(WordPar==De_SetPar_SetMastIP)		//������IP��ַ
	{	ptst_AgreeOn_Agree_Par_Cut->MastIP=Buf[0]*0x1000000+Buf[1]*0x10000+Buf[2]*0x100+Buf[3];
	}
	else if(WordPar==De_SetPar_SetMastDomainName)	//����������
	{	if(ParDataLen>sizeof(ptst_AgreeOn_Agree_Par_Cut->MastDomainName))
			ParDataLen=sizeof(ptst_AgreeOn_Agree_Par_Cut->MastDomainName);
		CN_st_Fun_AscNumber.MoveByte(ptst_AgreeOn_Agree_Par_Cut->MastDomainName,Buf,ParDataLen);
	}
	else if(WordPar==De_SetPar_SetReserveIP)			//���ø�����IP
	{	ptst_AgreeOn_Agree_Par_Cut->ReserveIP=Buf[0]*0x1000000+Buf[1]*0x10000+Buf[2]*0x100+Buf[3];
	}
	else if(WordPar==De_SetPar_SetReserveDomainName)		//���ø�����
	{	if(ParDataLen>sizeof(ptst_AgreeOn_Agree_Par_Cut->ReserveDomainName))
			ParDataLen=sizeof(ptst_AgreeOn_Agree_Par_Cut->ReserveDomainName);
		CN_st_Fun_AscNumber.MoveByte(ptst_AgreeOn_Agree_Par_Cut->ReserveDomainName,Buf,ParDataLen);
	}
	else if(WordPar==De_SetPar_SetCenPort)		 			//�������Ķ˿ں�
	{ 	ptst_AgreeOn_Agree_Par_Cut->CenPort=Buf[0]*0x100+Buf[1];
	}
	else if(WordPar==De_SetPar_SetCentHeart)		 		//�����·��������
	{ 	ptst_AgreeOn_Agree_Par_Cut->CentHeart=Buf[0];
	}
	else if(WordPar==De_SetPar_SetUseName)					//�����û���
	{	if(ParDataLen>sizeof(ptst_AgreeOn_Agree_Par_Cut->UseName))
			ParDataLen=sizeof(ptst_AgreeOn_Agree_Par_Cut->UseName);
		CN_st_Fun_AscNumber.MoveByte(ptst_AgreeOn_Agree_Par_Cut->UseName,Buf,ParDataLen);
	}
	else if(WordPar==De_SetPar_SetUsePass)					//���ò�������
	{	if(ParDataLen>sizeof(ptst_AgreeOn_Agree_Par_Cut->UsePass))
			ParDataLen=sizeof(ptst_AgreeOn_Agree_Par_Cut->UsePass);
		CN_st_Fun_AscNumber.MoveByte(ptst_AgreeOn_Agree_Par_Cut->UsePass,Buf,ParDataLen);
	}
	else if(WordPar==De_SetPar_SetDevHeart)		 			//�ն��Ϸ��������
	{ 	ptst_AgreeOn_Agree_Par_Cut->DevHeart=Buf[0];
	}
	else if(WordPar==De_SetPar_SetComMod)		 			//����ͨѶ��ʽ
	{ 	ptst_AgreeOn_Agree_Par_Cut->ComMod=Buf[0];
	}
	else if(WordPar==De_SetPar_SetIPRepeat)		 			//Ip�ؼ�ָ���ط�����
	{ 	ptst_AgreeOn_Agree_Par_Cut->IPRepeat=Buf[0];
	}
	else if(WordPar==De_SetPar_SetIPRepeatTime)		 		//IP�ؼ�ָ���ط����ʱ��
	{ 	ptst_AgreeOn_Agree_Par_Cut->IPRepeatTime=Buf[0];
	}
	else if(WordPar==De_SetPar_SetMessageRepeat)		 		//Message�ؼ�ָ���ط�����
	{ 	ptst_AgreeOn_Agree_Par_Cut->MessageRepeat=Buf[0];
	}
	else if(WordPar==De_SetPar_SetMessageRepeatTimer)		 	//Message Timer �ط�ʱ��
	{ 	ptst_AgreeOn_Agree_Par_Cut->MessageRepeatTimer=Buf[0];
	}
	else if(WordPar==De_SetPar_SetIPTransSms)		 			//Message��IP֮���л�ʱ��
	{ 	ptst_AgreeOn_Agree_Par_Cut->IPTransSms=Buf[0]*0x100+Buf[1];
	}
   	else if(WordPar==De_SetPar_SetDataLog)						//������־�洢
	{	if(ParDataLen>sizeof(ptst_AgreeOn_Agree_Par_Cut->DataLog))
			ParDataLen=sizeof(ptst_AgreeOn_Agree_Par_Cut->DataLog);
		CN_st_Fun_AscNumber.MoveByte(ptst_AgreeOn_Agree_Par_Cut->DataLog,Buf,ParDataLen);
	}
	else if(WordPar==De_SetPar_SetDataScotomaLog)						//ä����������
	{	if(ParDataLen>sizeof(ptst_AgreeOn_Agree_Par_Cut->DataScotomaLog))
			ParDataLen=sizeof(ptst_AgreeOn_Agree_Par_Cut->DataScotomaLog);
		CN_st_Fun_AscNumber.MoveByte(ptst_AgreeOn_Agree_Par_Cut->DataScotomaLog,Buf,ParDataLen);
	}
	else if(WordPar==De_SetPar_SetParLoad)								//���������ϴ�
	{	for(j=0;j<(sizeof(CN_Ba_WordPar)/sizeof(uint16));j++)
			ptst_AgreeOn_Agree_Par_Cut->ParLoad[j]=De_WordPar_Close;
		for(j=0;j<ParDataLen;j+=2)
		{	WordPar=Buf[j]*0x100+Buf[j+1];
			for(k=0;k<(sizeof(CN_Ba_WordPar)/sizeof(uint16));k++)
			{	if(WordPar==CN_Ba_WordPar[k])
					break;
			}
			if(k==(sizeof(CN_Ba_WordPar)/sizeof(uint16)))
				continue;
			ptst_AgreeOn_Agree_Par_Cut->ParLoad[k]=De_WordPar_Open;
		}	
	}
	else if(WordPar==De_SetPar_SetWireLessPar)							//�������߲���
	{ 	for(j=0;j<(sizeof(CN_Ba_LessPar)/sizeof(uint16));j++)
			ptst_AgreeOn_Agree_Par_Cut->WireLessPar[j]=De_WordPar_NoAdree;	
		for(j=0;j<(Buf[0]*6);j+=6)
		{	WordPar=Buf[5+j]*0x100+Buf[6+j];
			for(k=0;k<(sizeof(CN_Ba_LessPar)/sizeof(uint16));k++)
			{	if(WordPar==CN_Ba_LessPar[k])	
					break;
			}
			if(k==(sizeof(CN_Ba_LessPar)/sizeof(uint16)))
				continue;
			ptst_AgreeOn_Agree_Par_Cut->WireLessPar[k]=Buf[1+j]*0x1000000+Buf[2+j]*0x10000+Buf[3+j]*0x100+
																	+Buf[4+j];	
		}
	}
	else if(WordPar==De_SetPar_SetDePassWord)					//�����ն�����
	{ 	ptst_AgreeOn_Agree_Par_Cut->DePassWord=Buf[0]*0x1000000+Buf[1]*0x10000+Buf[2]*0x100+Buf[3];
	}
	else if(WordPar==De_SetPar_SetAccTimer)					//����ACC�ۼ�ʱ��
	{ 	ptst_AgreeOn_Agree_Par_Cut->AccTimer=Buf[0]*0x1000000+Buf[1]*0x10000+Buf[2]*0x100+Buf[3];
	}
	else if(WordPar==De_SetPar_SetRunLen)					//�����������
	{ 	ptst_AgreeOn_Agree_Par_Cut->RunLen=Buf[0]*0x1000000+Buf[1]*0x10000+Buf[2]*0x100+Buf[3];
	}
	else if(WordPar==De_SetPar_SetPerPuse)		 			//����ÿ�ܵ�������
	{ 	ptst_AgreeOn_Agree_Par_Cut->PerPuse=Buf[0];
	}
	else if(WordPar==De_SetPar_SetCarFeature)		 			//���ó�������
	{ 	ptst_AgreeOn_Agree_Par_Cut->CarFeature=Buf[0]*0x100+Buf[1];
	}
	else if(WordPar==De_SetPar_SetTakeLCD)		 				//���ó����Ƿ�װ����
	{ 	ptst_AgreeOn_Agree_Par_Cut->TakeLCD=Buf[0];
	}
	else if(WordPar==De_SetPar_SetOilFrequency)		 			//������������Ƶ��
	{ 	ptst_AgreeOn_Agree_Par_Cut->OilFrequency=Buf[0];
	}
	else if(WordPar==De_SetPar_SetSleepTimer)		 			//��������ʱ��
	{ 	ptst_AgreeOn_Agree_Par_Cut->SleepTimer=Buf[0]*0x100+Buf[1];
	}
	else if(WordPar==De_SetPar_SetCloseTimer)		 				//���ùػ�ʱ��
	{ 	ptst_AgreeOn_Agree_Par_Cut->CloseTimer=Buf[0]*0x100+Buf[1];
	}
	else if(WordPar==De_SetPar_SetLogMess)		 				//���õ�¼��ʾ
	{ 	ptst_AgreeOn_Agree_Par_Cut->LogMess=Buf[0];
	}
	else if(WordPar==De_SetPar_SetTaskVid)		 				//�����Ƿ�װ����ͷ
	{ 	ptst_AgreeOn_Agree_Par_Cut->TaskVid=Buf[0];
	}
	else if(WordPar==De_SetPar_SetHighSpeed)		 			//���ó��ٱ���
	{ 	ptst_AgreeOn_Agree_Par_Cut->CN_High_st_Waring_Par.WartingVl=Buf[0];
		ptst_AgreeOn_Agree_Par_Cut->CN_High_st_Waring_Par.WartingTimer=Buf[1];
	}
	else if(WordPar==De_SetPar_SetLowSpeed)		 			//���õ��ٱ���
	{ 	ptst_AgreeOn_Agree_Par_Cut->CN_Low_st_Waring_Par.WartingVl=Buf[0];
		ptst_AgreeOn_Agree_Par_Cut->CN_Low_st_Waring_Par.WartingTimer=Buf[1];
	}
	else if(WordPar==De_SetPar_SetLowVlt)		 			//���õ͵�ѹ����
	{ 	ptst_AgreeOn_Agree_Par_Cut->CN_Vo_st_Waring_Par.WartingVl=Buf[0];
		ptst_AgreeOn_Agree_Par_Cut->CN_Vo_st_Waring_Par.WartingTimer=Buf[1];
	}
	else if(WordPar==De_SetPar_SetVidType)
	{	ptst_AgreeOn_Agree_Par_Cut->CN_st_VidType.HelpWarning=De_AgreeOn_Vid_Fun_Close;
		if(Buf[1]&0x01)	   //��������
			ptst_AgreeOn_Agree_Par_Cut->CN_st_VidType.HelpWarning=De_AgreeOn_Vid_Fun_Open;
		ptst_AgreeOn_Agree_Par_Cut->CN_st_VidType.Oper=De_AgreeOn_Vid_Fun_Close;
		if(Buf[1]&0x02)	   //��������ת
			ptst_AgreeOn_Agree_Par_Cut->CN_st_VidType.Oper=De_AgreeOn_Vid_Fun_Open;		
		ptst_AgreeOn_Agree_Par_Cut->CN_st_VidType.TurnOver=De_AgreeOn_Vid_Fun_Close;
		if(Buf[1]&0x04)	  //�෭
			ptst_AgreeOn_Agree_Par_Cut->CN_st_VidType.TurnOver=De_AgreeOn_Vid_Fun_Open;
		ptst_AgreeOn_Agree_Par_Cut->CN_st_VidType.AccOpen=De_AgreeOn_Vid_Fun_Close;
		if(Buf[1]&0x08)	 //ACC��
			ptst_AgreeOn_Agree_Par_Cut->CN_st_VidType.AccOpen=De_AgreeOn_Vid_Fun_Open;
		ptst_AgreeOn_Agree_Par_Cut->CN_st_VidType.AccClose=De_AgreeOn_Vid_Fun_Close;
		if(Buf[1]&0x10)	//ACC�ر�
			ptst_AgreeOn_Agree_Par_Cut->CN_st_VidType.AccClose=De_AgreeOn_Vid_Fun_Open;
	}
	else if(WordPar==De_SetPar_SetOrderFrmTimer)		//����ԤԼ����ʱ��
	{	ptst_AgreeOn_Agree_Par_Cut->OrderFrmTimer=Buf[0]*60;
	}
}

static void Explain_WorkPar(uint8 *Buf,st_AgreeOn_SetVidType  *ptst_AgreeOn_SetVidType,uint16 WorkID,uint16 Len,uint8 type)
{   
    uint16 t;
	uint32 Value1;
	if(WorkID==De_Sensor_WordPar_Switch1)
	{  ptst_AgreeOn_SetVidType->CN_st_AgreeOn_SetVidType_Par[0].Switch1=Buf[0];
	   ptst_AgreeOn_SetVidType->CN_st_AgreeOn_SetVidType_Par[1].Switch1=Buf[0];
		if(type==De_AgreeOn_SetVidType_Type_NumberCut)
	   {ptst_AgreeOn_SetVidType->CN_st_AgreeOn_SetVidType_Par[0].Switch1=Buf[0];
	    ptst_AgreeOn_SetVidType->CN_st_AgreeOn_SetVidType_Par[1].Switch1=Buf[1];
	   }			
	}
	else if(WorkID==De_Sensor_WordPar_Switch2)
	{   ptst_AgreeOn_SetVidType->CN_st_AgreeOn_SetVidType_Par[0].Switch2=Buf[0];
		ptst_AgreeOn_SetVidType->CN_st_AgreeOn_SetVidType_Par[1].Switch2=Buf[0];
		if(type==De_AgreeOn_SetVidType_Type_NumberCut)
	   {ptst_AgreeOn_SetVidType->CN_st_AgreeOn_SetVidType_Par[0].Switch2=Buf[0];
	    ptst_AgreeOn_SetVidType->CN_st_AgreeOn_SetVidType_Par[1].Switch2=Buf[1];
	   }		
	}
	else if(WorkID==De_Sensor_WordPar_Switch3)
	{	ptst_AgreeOn_SetVidType->CN_st_AgreeOn_SetVidType_Par[0].Switch3=Buf[0];
		ptst_AgreeOn_SetVidType->CN_st_AgreeOn_SetVidType_Par[1].Switch3=Buf[0];
		if(type==De_AgreeOn_SetVidType_Type_NumberCut)
	   {ptst_AgreeOn_SetVidType->CN_st_AgreeOn_SetVidType_Par[0].Switch3=Buf[0];
	    ptst_AgreeOn_SetVidType->CN_st_AgreeOn_SetVidType_Par[1].Switch3=Buf[1];
	   }				 
	}
	else if(WorkID==De_Sensor_WordPar_Switch4)
	{	ptst_AgreeOn_SetVidType->CN_st_AgreeOn_SetVidType_Par[0].Switch4=Buf[0];
		ptst_AgreeOn_SetVidType->CN_st_AgreeOn_SetVidType_Par[1].Switch4=Buf[0];
		if(type==De_AgreeOn_SetVidType_Type_NumberCut)
	   {ptst_AgreeOn_SetVidType->CN_st_AgreeOn_SetVidType_Par[0].Switch4=Buf[0];
	    ptst_AgreeOn_SetVidType->CN_st_AgreeOn_SetVidType_Par[1].Switch4=Buf[1];
	   }		
	}
	else if(WorkID==De_Sensor_WordPar_Switch5)
	{	ptst_AgreeOn_SetVidType->CN_st_AgreeOn_SetVidType_Par[0].Switch5=Buf[0];
		ptst_AgreeOn_SetVidType->CN_st_AgreeOn_SetVidType_Par[1].Switch5=Buf[0];
		if(type==De_AgreeOn_SetVidType_Type_NumberCut)
	   {ptst_AgreeOn_SetVidType->CN_st_AgreeOn_SetVidType_Par[0].Switch5=Buf[0];
	    ptst_AgreeOn_SetVidType->CN_st_AgreeOn_SetVidType_Par[1].Switch5=Buf[1];
	   }		
	}
	else if(WorkID==De_Sensor_WordPar_Switch6)
	{	ptst_AgreeOn_SetVidType->CN_st_AgreeOn_SetVidType_Par[0].Switch6=Buf[0];
		ptst_AgreeOn_SetVidType->CN_st_AgreeOn_SetVidType_Par[1].Switch6=Buf[0];
		if(type==De_AgreeOn_SetVidType_Type_NumberCut)
	   {ptst_AgreeOn_SetVidType->CN_st_AgreeOn_SetVidType_Par[0].Switch6=Buf[0];
	    ptst_AgreeOn_SetVidType->CN_st_AgreeOn_SetVidType_Par[1].Switch6=Buf[1];
	   }		
	}
	else if(WorkID==De_Sensor_WordPar_Switch7)
	{	ptst_AgreeOn_SetVidType->CN_st_AgreeOn_SetVidType_Par[0].Switch7=Buf[0];
		ptst_AgreeOn_SetVidType->CN_st_AgreeOn_SetVidType_Par[1].Switch7=Buf[0];
		if(type==De_AgreeOn_SetVidType_Type_NumberCut)
	   {ptst_AgreeOn_SetVidType->CN_st_AgreeOn_SetVidType_Par[0].Switch7=Buf[0];
	    ptst_AgreeOn_SetVidType->CN_st_AgreeOn_SetVidType_Par[1].Switch7=Buf[1];
	   }		
	}
	else if(WorkID==De_Sensor_WordPar_Switch8)
	{   ptst_AgreeOn_SetVidType->CN_st_AgreeOn_SetVidType_Par[0].Switch8=Buf[0];
		ptst_AgreeOn_SetVidType->CN_st_AgreeOn_SetVidType_Par[1].Switch8=Buf[0];
		if(type==De_AgreeOn_SetVidType_Type_NumberCut)
	   {ptst_AgreeOn_SetVidType->CN_st_AgreeOn_SetVidType_Par[0].Switch8=Buf[0];
	    ptst_AgreeOn_SetVidType->CN_st_AgreeOn_SetVidType_Par[1].Switch8=Buf[1];
	   }		
	}
	else if(WorkID==De_Sensor_WordPar_Switch9)
	{	ptst_AgreeOn_SetVidType->CN_st_AgreeOn_SetVidType_Par[0].Switch9=Buf[0];
		 ptst_AgreeOn_SetVidType->CN_st_AgreeOn_SetVidType_Par[1].Switch9=Buf[0];
		if(type==De_AgreeOn_SetVidType_Type_NumberCut)
	   {ptst_AgreeOn_SetVidType->CN_st_AgreeOn_SetVidType_Par[0].Switch9=Buf[0];
	    ptst_AgreeOn_SetVidType->CN_st_AgreeOn_SetVidType_Par[1].Switch9=Buf[1];
	   }		
	}
	else if(WorkID==De_Sensor_WordPar_Switch10)
	{   ptst_AgreeOn_SetVidType->CN_st_AgreeOn_SetVidType_Par[0].Switch10=Buf[0];
		ptst_AgreeOn_SetVidType->CN_st_AgreeOn_SetVidType_Par[1].Switch10=Buf[0];
		if(type==De_AgreeOn_SetVidType_Type_NumberCut)
	   {ptst_AgreeOn_SetVidType->CN_st_AgreeOn_SetVidType_Par[0].Switch10=Buf[0];
	    ptst_AgreeOn_SetVidType->CN_st_AgreeOn_SetVidType_Par[1].Switch10=Buf[1];
	   }		
	}
	else if(WorkID==De_Sensor_WordPar_Switch11)
	{   ptst_AgreeOn_SetVidType->CN_st_AgreeOn_SetVidType_Par[0].Switch11=Buf[0];
		ptst_AgreeOn_SetVidType->CN_st_AgreeOn_SetVidType_Par[1].Switch11=Buf[0];
		if(type==De_AgreeOn_SetVidType_Type_NumberCut)
	   {ptst_AgreeOn_SetVidType->CN_st_AgreeOn_SetVidType_Par[0].Switch11=Buf[0];
	    ptst_AgreeOn_SetVidType->CN_st_AgreeOn_SetVidType_Par[1].Switch11=Buf[1];
	   }		
	}
	else if(WorkID==De_Sensor_WordPar_Switch12)
	{	ptst_AgreeOn_SetVidType->CN_st_AgreeOn_SetVidType_Par[0].Switch12=Buf[0];
		ptst_AgreeOn_SetVidType->CN_st_AgreeOn_SetVidType_Par[1].Switch12=Buf[0];
		if(type==De_AgreeOn_SetVidType_Type_NumberCut)
	   {ptst_AgreeOn_SetVidType->CN_st_AgreeOn_SetVidType_Par[0].Switch12=Buf[0];
	    ptst_AgreeOn_SetVidType->CN_st_AgreeOn_SetVidType_Par[1].Switch12=Buf[1];
	   }		
	}
	else if(WorkID==De_Sensor_WordPar_Switch13)
	{	ptst_AgreeOn_SetVidType->CN_st_AgreeOn_SetVidType_Par[0].Switch13=Buf[0];
	    ptst_AgreeOn_SetVidType->CN_st_AgreeOn_SetVidType_Par[1].Switch13=Buf[0];
		if(type==De_AgreeOn_SetVidType_Type_NumberCut)
	   {ptst_AgreeOn_SetVidType->CN_st_AgreeOn_SetVidType_Par[0].Switch13=Buf[0];
	    ptst_AgreeOn_SetVidType->CN_st_AgreeOn_SetVidType_Par[1].Switch13=Buf[1];
	   }		
	}
	else if(WorkID==De_Sensor_WordPar_Switch14)
	{	ptst_AgreeOn_SetVidType->CN_st_AgreeOn_SetVidType_Par[0].Switch14=Buf[0];
	    ptst_AgreeOn_SetVidType->CN_st_AgreeOn_SetVidType_Par[1].Switch14=Buf[0];
		if(type==De_AgreeOn_SetVidType_Type_NumberCut)
	   {ptst_AgreeOn_SetVidType->CN_st_AgreeOn_SetVidType_Par[0].Switch14=Buf[0];
	    ptst_AgreeOn_SetVidType->CN_st_AgreeOn_SetVidType_Par[1].Switch14=Buf[1];
	   }		
	}
	else if(WorkID==De_Sensor_WordPar_Switch15)
	{	ptst_AgreeOn_SetVidType->CN_st_AgreeOn_SetVidType_Par[0].Switch15=Buf[0];
	    ptst_AgreeOn_SetVidType->CN_st_AgreeOn_SetVidType_Par[1].Switch15=Buf[0];
		if(type==De_AgreeOn_SetVidType_Type_NumberCut)
	   {ptst_AgreeOn_SetVidType->CN_st_AgreeOn_SetVidType_Par[0].Switch15=Buf[0];
	    ptst_AgreeOn_SetVidType->CN_st_AgreeOn_SetVidType_Par[1].Switch15=Buf[1];
	   }			
	}
	else if(WorkID==De_Sensor_WordPar_Switch16)
	{  ptst_AgreeOn_SetVidType->CN_st_AgreeOn_SetVidType_Par[0].Switch16=Buf[0];
	   ptst_AgreeOn_SetVidType->CN_st_AgreeOn_SetVidType_Par[1].Switch16=Buf[0];
		if(type==De_AgreeOn_SetVidType_Type_NumberCut)
	   {ptst_AgreeOn_SetVidType->CN_st_AgreeOn_SetVidType_Par[0].Switch16=Buf[0];
	    ptst_AgreeOn_SetVidType->CN_st_AgreeOn_SetVidType_Par[1].Switch16=Buf[1];
	   }		
	}
	else if(WorkID==De_Sensor_WordPar_Less_Switch1)			//���߿�����
	{  ptst_AgreeOn_SetVidType->CN_st_AgreeOn_SetVidType_Par[0].CN_Less_Switch1.OpenOrClose=Buf[0];
	   ptst_AgreeOn_SetVidType->CN_st_AgreeOn_SetVidType_Par[1].CN_Less_Switch1.OpenOrClose=Buf[0];
			 if(type==De_AgreeOn_SetVidType_Type_NumberCut)
	        {ptst_AgreeOn_SetVidType->CN_st_AgreeOn_SetVidType_Par[0].CN_Less_Switch1.OpenOrClose=Buf[0];
	         ptst_AgreeOn_SetVidType->CN_st_AgreeOn_SetVidType_Par[1].CN_Less_Switch1.OpenOrClose=Buf[1];	
	        }	
	}
	else if(WorkID==De_Sensor_WordPar_Less_Switch2)			//���߿�����
	{      ptst_AgreeOn_SetVidType->CN_st_AgreeOn_SetVidType_Par[0].CN_Less_Switch2.OpenOrClose=Buf[0];
	       ptst_AgreeOn_SetVidType->CN_st_AgreeOn_SetVidType_Par[1].CN_Less_Switch2.OpenOrClose=Buf[0];
			 if(type==De_AgreeOn_SetVidType_Type_NumberCut)
	        {ptst_AgreeOn_SetVidType->CN_st_AgreeOn_SetVidType_Par[0].CN_Less_Switch2.OpenOrClose=Buf[0];
	         ptst_AgreeOn_SetVidType->CN_st_AgreeOn_SetVidType_Par[1].CN_Less_Switch2.OpenOrClose=Buf[1];	
	        }	
	}
	else if(WorkID==De_Sensor_WordPar_Less_Switch3)			//���߿�����
	{	  ptst_AgreeOn_SetVidType->CN_st_AgreeOn_SetVidType_Par[0].CN_Less_Switch3.OpenOrClose=Buf[0];
	      ptst_AgreeOn_SetVidType->CN_st_AgreeOn_SetVidType_Par[1].CN_Less_Switch3.OpenOrClose=Buf[0];
			 if(type==De_AgreeOn_SetVidType_Type_NumberCut)
	        {ptst_AgreeOn_SetVidType->CN_st_AgreeOn_SetVidType_Par[0].CN_Less_Switch3.OpenOrClose=Buf[0];
	         ptst_AgreeOn_SetVidType->CN_st_AgreeOn_SetVidType_Par[1].CN_Less_Switch3.OpenOrClose=Buf[1];	
	        }	
	}
	else if(WorkID==De_Sensor_WordPar_Less_Switch4)			//���߿�����
	{	   ptst_AgreeOn_SetVidType->CN_st_AgreeOn_SetVidType_Par[0].CN_Less_Switch4.OpenOrClose=Buf[0];
	       ptst_AgreeOn_SetVidType->CN_st_AgreeOn_SetVidType_Par[1].CN_Less_Switch4.OpenOrClose=Buf[0];
			 if(type==De_AgreeOn_SetVidType_Type_NumberCut)
	        {ptst_AgreeOn_SetVidType->CN_st_AgreeOn_SetVidType_Par[0].CN_Less_Switch4.OpenOrClose=Buf[0];
	         ptst_AgreeOn_SetVidType->CN_st_AgreeOn_SetVidType_Par[1].CN_Less_Switch4.OpenOrClose=Buf[1];	
	        }		
	}
	else if(WorkID==De_Sensor_WordPar_Less_Switch5)			//���߿�����
	{     ptst_AgreeOn_SetVidType->CN_st_AgreeOn_SetVidType_Par[0].CN_Less_Switch5.OpenOrClose=Buf[0];
	      ptst_AgreeOn_SetVidType->CN_st_AgreeOn_SetVidType_Par[1].CN_Less_Switch5.OpenOrClose=Buf[0];
			 if(type==De_AgreeOn_SetVidType_Type_NumberCut)
	        {ptst_AgreeOn_SetVidType->CN_st_AgreeOn_SetVidType_Par[0].CN_Less_Switch5.OpenOrClose=Buf[0];
	         ptst_AgreeOn_SetVidType->CN_st_AgreeOn_SetVidType_Par[1].CN_Less_Switch5.OpenOrClose=Buf[1];	
	        }		
	}
	else if(WorkID==De_Sensor_WordPar_Less_Switch6)			//���߿�����
	{    ptst_AgreeOn_SetVidType->CN_st_AgreeOn_SetVidType_Par[0].CN_Less_Switch6.OpenOrClose=Buf[0];
	     ptst_AgreeOn_SetVidType->CN_st_AgreeOn_SetVidType_Par[1].CN_Less_Switch6.OpenOrClose=Buf[0];
			 if(type==De_AgreeOn_SetVidType_Type_NumberCut)
	        {ptst_AgreeOn_SetVidType->CN_st_AgreeOn_SetVidType_Par[0].CN_Less_Switch6.OpenOrClose=Buf[0];
	         ptst_AgreeOn_SetVidType->CN_st_AgreeOn_SetVidType_Par[1].CN_Less_Switch6.OpenOrClose=Buf[1];	
	        }		
	}
	else if(WorkID==De_Sensor_WordPar_AccTimer)
	{  CN_st_Fun_AscNumber.Value32(Buf,&Value1,Len);
	     ptst_AgreeOn_SetVidType->CN_st_AgreeOn_SetVidType_Par[0].AccTimer=Value1;
		  ptst_AgreeOn_SetVidType->CN_st_AgreeOn_SetVidType_Par[1].AccTimer=Value1;
	   	 if(type==De_AgreeOn_SetVidType_Type_NumberCut)
	        {t=Len/2;
			CN_st_Fun_AscNumber.Value32(Buf,&Value1,t);			
			ptst_AgreeOn_SetVidType->CN_st_AgreeOn_SetVidType_Par[0].AccTimer=Value1;
			CN_st_Fun_AscNumber.Value32(Buf+t,&Value1,t);
	        ptst_AgreeOn_SetVidType->CN_st_AgreeOn_SetVidType_Par[1].AccTimer=Value1;	
	        }	
	}
	else if(WorkID==De_Sensor_WordPar_Mileage)
	{	CN_st_Fun_AscNumber.Value32(Buf,&Value1,Len);
	    ptst_AgreeOn_SetVidType->CN_st_AgreeOn_SetVidType_Par[0].Mileage=Value1;
		 ptst_AgreeOn_SetVidType->CN_st_AgreeOn_SetVidType_Par[1].Mileage=Value1;
	   	 if(type==De_AgreeOn_SetVidType_Type_NumberCut)
	        {t=Len/2;
			CN_st_Fun_AscNumber.Value32(Buf,&Value1,t);			
			ptst_AgreeOn_SetVidType->CN_st_AgreeOn_SetVidType_Par[0].Mileage=Value1;
			CN_st_Fun_AscNumber.Value32(Buf+t,&Value1,t);
	        ptst_AgreeOn_SetVidType->CN_st_AgreeOn_SetVidType_Par[1].Mileage=Value1;	
	        }	
	}
	else if(WorkID==De_Sensor_WordPar_Oil1)
	{ 	 CN_st_Fun_AscNumber.Value32(Buf,&Value1,Len);
	       ptst_AgreeOn_SetVidType->CN_st_AgreeOn_SetVidType_Par[0].Oil1=Value1;
		   ptst_AgreeOn_SetVidType->CN_st_AgreeOn_SetVidType_Par[1].Oil1=Value1;
	   	   if(type==De_AgreeOn_SetVidType_Type_NumberCut)
	        {t=Len/2;
			CN_st_Fun_AscNumber.Value32(Buf,&Value1,t);			
			ptst_AgreeOn_SetVidType->CN_st_AgreeOn_SetVidType_Par[0].Oil1=Value1;
			CN_st_Fun_AscNumber.Value32(Buf+t,&Value1,t);
	        ptst_AgreeOn_SetVidType->CN_st_AgreeOn_SetVidType_Par[0].Oil1=Value1;	
	        }	
	}
	else if(WorkID==De_Sensor_WordPar_Sem)
	{  CN_st_Fun_AscNumber.Value32(Buf,&Value1,Len);
	       ptst_AgreeOn_SetVidType->CN_st_AgreeOn_SetVidType_Par[0].Sem=Value1;
		    ptst_AgreeOn_SetVidType->CN_st_AgreeOn_SetVidType_Par[1].Sem=Value1;
	   	   if(type==De_AgreeOn_SetVidType_Type_NumberCut)
	        {t=Len/2;
			CN_st_Fun_AscNumber.Value32(Buf,&Value1,t);			
			ptst_AgreeOn_SetVidType->CN_st_AgreeOn_SetVidType_Par[0].Sem=Value1;
			CN_st_Fun_AscNumber.Value32(Buf+t,&Value1,t);
	        ptst_AgreeOn_SetVidType->CN_st_AgreeOn_SetVidType_Par[1].Sem=Value1;	
	        }		
	}
	else if(WorkID==De_Sensor_WordPar_SendOilTimer)
	{ 	 CN_st_Fun_AscNumber.Value32(Buf,&Value1,Len);
	       ptst_AgreeOn_SetVidType->CN_st_AgreeOn_SetVidType_Par[0].SendOilTimer=Value1;
		   ptst_AgreeOn_SetVidType->CN_st_AgreeOn_SetVidType_Par[1].SendOilTimer=Value1;
	   	   if(type==De_AgreeOn_SetVidType_Type_NumberCut)
	        {t=Len/2;
			CN_st_Fun_AscNumber.Value32(Buf,&Value1,t);			
			ptst_AgreeOn_SetVidType->CN_st_AgreeOn_SetVidType_Par[0].SendOilTimer=Value1;
			CN_st_Fun_AscNumber.Value32(Buf+t,&Value1,t);
	        ptst_AgreeOn_SetVidType->CN_st_AgreeOn_SetVidType_Par[1].SendOilTimer=Value1;	
	        }		
	}
	else if(WorkID==De_Sensor_WordPar_Temp)
	{		ptst_AgreeOn_SetVidType->CN_st_AgreeOn_SetVidType_Par[0].Temp=Buf[1]*100+Buf[2];
	   	    ptst_AgreeOn_SetVidType->CN_st_AgreeOn_SetVidType_Par[1].Temp=Buf[1]*100+Buf[2];
		if(Buf[0]==0x11)
		 	ptst_AgreeOn_SetVidType->CN_st_AgreeOn_SetVidType_Par[0].Temp=0xffffffff-ptst_AgreeOn_SetVidType->CN_st_AgreeOn_SetVidType_Par[0].Temp+1;
        if(type==De_AgreeOn_SetVidType_Type_NumberCut)
	        {
			ptst_AgreeOn_SetVidType->CN_st_AgreeOn_SetVidType_Par[0].Temp=Buf[1]*100+Buf[2];
	    	if(Buf[0]==0x11)
		 	ptst_AgreeOn_SetVidType->CN_st_AgreeOn_SetVidType_Par[0].Temp=0xffffffff-ptst_AgreeOn_SetVidType->CN_st_AgreeOn_SetVidType_Par[0].Temp+1;	
			ptst_AgreeOn_SetVidType->CN_st_AgreeOn_SetVidType_Par[1].Temp=Buf[4]*100+Buf[5];
	    	if(Buf[3]==0x11)
		 	ptst_AgreeOn_SetVidType->CN_st_AgreeOn_SetVidType_Par[1].Temp=0xffffffff-ptst_AgreeOn_SetVidType->CN_st_AgreeOn_SetVidType_Par[0].Temp+1;	
	        }		
	}
	else if(WorkID==De_Sensor_WordPar_Oil2)
	{	   CN_st_Fun_AscNumber.Value32(Buf,&Value1,Len);
	       ptst_AgreeOn_SetVidType->CN_st_AgreeOn_SetVidType_Par[0].Oil2=Value1;
		   ptst_AgreeOn_SetVidType->CN_st_AgreeOn_SetVidType_Par[1].Oil2=Value1;
	   	   if(type==De_AgreeOn_SetVidType_Type_NumberCut)
	        {t=Len/2;
			CN_st_Fun_AscNumber.Value32(Buf,&Value1,t);			
			ptst_AgreeOn_SetVidType->CN_st_AgreeOn_SetVidType_Par[0].Oil2=Value1;
			CN_st_Fun_AscNumber.Value32(Buf+t,&Value1,t);
	        ptst_AgreeOn_SetVidType->CN_st_AgreeOn_SetVidType_Par[1].Oil2=Value1;	
	        }	
	}
	else if(WorkID==De_Sensor_WordPar_Pulse)
	{	 CN_st_Fun_AscNumber.Value32(Buf,&Value1,Len);
	       ptst_AgreeOn_SetVidType->CN_st_AgreeOn_SetVidType_Par[0].Pulse=Value1;
		    ptst_AgreeOn_SetVidType->CN_st_AgreeOn_SetVidType_Par[1].Pulse=Value1;
	   	   if(type==De_AgreeOn_SetVidType_Type_NumberCut)
	        {t=Len/2;
			CN_st_Fun_AscNumber.Value32(Buf,&Value1,t);			
			ptst_AgreeOn_SetVidType->CN_st_AgreeOn_SetVidType_Par[0].Pulse=Value1;
			CN_st_Fun_AscNumber.Value32(Buf+t,&Value1,t);
	        ptst_AgreeOn_SetVidType->CN_st_AgreeOn_SetVidType_Par[1].Pulse=Value1;	
	        }	
	}
	else if(WorkID==De_Sensor_WordPar_Humidity)
	{   ptst_AgreeOn_SetVidType->CN_st_AgreeOn_SetVidType_Par[0].Humidity=Buf[0]*1000+Buf[1]*10;
	    ptst_AgreeOn_SetVidType->CN_st_AgreeOn_SetVidType_Par[1].Humidity=Buf[0]*1000+Buf[1]*10;
		if(type==De_AgreeOn_SetVidType_Type_NumberCut)
		{ptst_AgreeOn_SetVidType->CN_st_AgreeOn_SetVidType_Par[0].Humidity=Buf[0]*1000+Buf[1]*10;
		 ptst_AgreeOn_SetVidType->CN_st_AgreeOn_SetVidType_Par[0].Humidity=Buf[2]*1000+Buf[3]*10;
		 }
	}
	else if(WorkID==De_Sensor_WordPar_OilBaifen)
	{	ptst_AgreeOn_SetVidType->CN_st_AgreeOn_SetVidType_Par[0].OilBaifen=Buf[0]*10;
	    ptst_AgreeOn_SetVidType->CN_st_AgreeOn_SetVidType_Par[1].OilBaifen=Buf[0]*10;
	    if(type==De_AgreeOn_SetVidType_Type_NumberCut)
		{ptst_AgreeOn_SetVidType->CN_st_AgreeOn_SetVidType_Par[0].OilBaifen=Buf[0]*10;
		ptst_AgreeOn_SetVidType->CN_st_AgreeOn_SetVidType_Par[1].OilBaifen=Buf[1]*10;
		}
	}
	else if(WorkID==De_Sensor_WordPar_Less_Temp1)			//���߿�����
	{	ptst_AgreeOn_SetVidType->CN_st_AgreeOn_SetVidType_Par[0].CN_st_AgreeOn_Less_Temp1.Temp=Buf[1]*100+Buf[2];
		ptst_AgreeOn_SetVidType->CN_st_AgreeOn_SetVidType_Par[1].CN_st_AgreeOn_Less_Temp1.Temp=Buf[1]*100+Buf[2];
		if(Buf[0]==0x11)
		 {	ptst_AgreeOn_SetVidType->CN_st_AgreeOn_SetVidType_Par[0].CN_st_AgreeOn_Less_Temp1.Temp=0xffffffff-ptst_AgreeOn_SetVidType->CN_st_AgreeOn_SetVidType_Par[0].CN_st_AgreeOn_Less_Temp1.Temp+1;
			ptst_AgreeOn_SetVidType->CN_st_AgreeOn_SetVidType_Par[1].CN_st_AgreeOn_Less_Temp1.Temp=0xffffffff-ptst_AgreeOn_SetVidType->CN_st_AgreeOn_SetVidType_Par[0].CN_st_AgreeOn_Less_Temp1.Temp+1;
		 }
	     if(type==De_AgreeOn_SetVidType_Type_NumberCut)
	        {
			ptst_AgreeOn_SetVidType->CN_st_AgreeOn_SetVidType_Par[0].CN_st_AgreeOn_Less_Temp1.Temp=Buf[1]*100+Buf[2];
	    	if(Buf[0]==0x11)
		 	ptst_AgreeOn_SetVidType->CN_st_AgreeOn_SetVidType_Par[0].CN_st_AgreeOn_Less_Temp1.Temp=0xffffffff-ptst_AgreeOn_SetVidType->CN_st_AgreeOn_SetVidType_Par[0].CN_st_AgreeOn_Less_Temp1.Temp+1;	
			ptst_AgreeOn_SetVidType->CN_st_AgreeOn_SetVidType_Par[1].CN_st_AgreeOn_Less_Temp1.Temp=Buf[4]*100+Buf[5];
	    	if(Buf[3]==0x11)
		 	ptst_AgreeOn_SetVidType->CN_st_AgreeOn_SetVidType_Par[1].CN_st_AgreeOn_Less_Temp1.Temp=0xffffffff-ptst_AgreeOn_SetVidType->CN_st_AgreeOn_SetVidType_Par[1].CN_st_AgreeOn_Less_Temp1.Temp+1;	
	        }	
	}
	else if(WorkID==De_Sensor_WordPar_Less_Temp2)			//���߿�����
	{	ptst_AgreeOn_SetVidType->CN_st_AgreeOn_SetVidType_Par[0].CN_st_AgreeOn_Less_Temp2.Temp=Buf[1]*100+Buf[2];
		ptst_AgreeOn_SetVidType->CN_st_AgreeOn_SetVidType_Par[1].CN_st_AgreeOn_Less_Temp2.Temp=Buf[1]*100+Buf[2];
		if(Buf[0]==0x11)
		{ptst_AgreeOn_SetVidType->CN_st_AgreeOn_SetVidType_Par[0].CN_st_AgreeOn_Less_Temp2.Temp=0xffffffff-ptst_AgreeOn_SetVidType->CN_st_AgreeOn_SetVidType_Par[0].CN_st_AgreeOn_Less_Temp2.Temp+1;
         ptst_AgreeOn_SetVidType->CN_st_AgreeOn_SetVidType_Par[1].CN_st_AgreeOn_Less_Temp2.Temp=0xffffffff-ptst_AgreeOn_SetVidType->CN_st_AgreeOn_SetVidType_Par[0].CN_st_AgreeOn_Less_Temp2.Temp+1;
	    }
		if(type==De_AgreeOn_SetVidType_Type_NumberCut)
	    {
			ptst_AgreeOn_SetVidType->CN_st_AgreeOn_SetVidType_Par[0].CN_st_AgreeOn_Less_Temp2.Temp=Buf[1]*100+Buf[2];
	    	if(Buf[0]==0x11)
		 	{ptst_AgreeOn_SetVidType->CN_st_AgreeOn_SetVidType_Par[0].CN_st_AgreeOn_Less_Temp2.Temp=0xffffffff-	ptst_AgreeOn_SetVidType->CN_st_AgreeOn_SetVidType_Par[0].CN_st_AgreeOn_Less_Temp2.Temp+1;	
		     ptst_AgreeOn_SetVidType->CN_st_AgreeOn_SetVidType_Par[1].CN_st_AgreeOn_Less_Temp2.Temp=Buf[4]*100+Buf[5];
	    	 if(Buf[3]==0x11)
		 	 ptst_AgreeOn_SetVidType->CN_st_AgreeOn_SetVidType_Par[1].CN_st_AgreeOn_Less_Temp2.Temp=0xffffffff-	ptst_AgreeOn_SetVidType->CN_st_AgreeOn_SetVidType_Par[1].CN_st_AgreeOn_Less_Temp2.Temp+1;	
	   		 }
	    }	
	}
	else if(WorkID==De_Sensor_WordPar_Less_Temp3)			//���߿�����
	{	ptst_AgreeOn_SetVidType->CN_st_AgreeOn_SetVidType_Par[0].CN_st_AgreeOn_Less_Temp3.Temp=Buf[1]*100+Buf[2];
	   	ptst_AgreeOn_SetVidType->CN_st_AgreeOn_SetVidType_Par[1].CN_st_AgreeOn_Less_Temp3.Temp=Buf[1]*100+Buf[2];
		if(Buf[0]==0x11)
		 {	ptst_AgreeOn_SetVidType->CN_st_AgreeOn_SetVidType_Par[0].CN_st_AgreeOn_Less_Temp3.Temp=0xffffffff-ptst_AgreeOn_SetVidType->CN_st_AgreeOn_SetVidType_Par[0].CN_st_AgreeOn_Less_Temp3.Temp+1;
      		ptst_AgreeOn_SetVidType->CN_st_AgreeOn_SetVidType_Par[1].CN_st_AgreeOn_Less_Temp3.Temp=0xffffffff-ptst_AgreeOn_SetVidType->CN_st_AgreeOn_SetVidType_Par[0].CN_st_AgreeOn_Less_Temp3.Temp+1;
	     }
		if(type==De_AgreeOn_SetVidType_Type_NumberCut)
	     {
			ptst_AgreeOn_SetVidType->CN_st_AgreeOn_SetVidType_Par[0].CN_st_AgreeOn_Less_Temp3.Temp=Buf[1]*100+Buf[2];
	    	if(Buf[0]==0x11)
		 	{ptst_AgreeOn_SetVidType->CN_st_AgreeOn_SetVidType_Par[0].CN_st_AgreeOn_Less_Temp3.Temp=0xffffffff-	ptst_AgreeOn_SetVidType->CN_st_AgreeOn_SetVidType_Par[0].CN_st_AgreeOn_Less_Temp3.Temp+1;	
			 ptst_AgreeOn_SetVidType->CN_st_AgreeOn_SetVidType_Par[1].CN_st_AgreeOn_Less_Temp3.Temp=Buf[4]*100+Buf[5];
	    	 if(Buf[3]==0x11)
		 	 ptst_AgreeOn_SetVidType->CN_st_AgreeOn_SetVidType_Par[1].CN_st_AgreeOn_Less_Temp3.Temp=0xffffffff-	ptst_AgreeOn_SetVidType->CN_st_AgreeOn_SetVidType_Par[1].CN_st_AgreeOn_Less_Temp3.Temp+1;	
	   	    }
	    }	
	}
	else if(WorkID==De_Sensor_WordPar_Less_Temp4)			//���߿�����
	{ptst_AgreeOn_SetVidType->CN_st_AgreeOn_SetVidType_Par[0].CN_st_AgreeOn_Less_Temp4.Temp=Buf[1]*100+Buf[2];
	 ptst_AgreeOn_SetVidType->CN_st_AgreeOn_SetVidType_Par[1].CN_st_AgreeOn_Less_Temp4.Temp=Buf[1]*100+Buf[2];
		if(Buf[0]==0x11)
		 {	ptst_AgreeOn_SetVidType->CN_st_AgreeOn_SetVidType_Par[0].CN_st_AgreeOn_Less_Temp4.Temp=0xffffffff-ptst_AgreeOn_SetVidType->CN_st_AgreeOn_SetVidType_Par[0].CN_st_AgreeOn_Less_Temp4.Temp+1;
        	ptst_AgreeOn_SetVidType->CN_st_AgreeOn_SetVidType_Par[1].CN_st_AgreeOn_Less_Temp4.Temp=0xffffffff-ptst_AgreeOn_SetVidType->CN_st_AgreeOn_SetVidType_Par[0].CN_st_AgreeOn_Less_Temp4.Temp+1;
		 }
		if(type==De_AgreeOn_SetVidType_Type_NumberCut)
	    {
			ptst_AgreeOn_SetVidType->CN_st_AgreeOn_SetVidType_Par[0].CN_st_AgreeOn_Less_Temp4.Temp=Buf[1]*100+Buf[2];
	    	if(Buf[0]==0x11)
		 	{ptst_AgreeOn_SetVidType->CN_st_AgreeOn_SetVidType_Par[0].CN_st_AgreeOn_Less_Temp4.Temp=0xffffffff-	ptst_AgreeOn_SetVidType->CN_st_AgreeOn_SetVidType_Par[0].CN_st_AgreeOn_Less_Temp4.Temp+1;	
			ptst_AgreeOn_SetVidType->CN_st_AgreeOn_SetVidType_Par[1].CN_st_AgreeOn_Less_Temp4.Temp=Buf[4]*100+Buf[5];
	    	if(Buf[3]==0x11)
		 	ptst_AgreeOn_SetVidType->CN_st_AgreeOn_SetVidType_Par[1].CN_st_AgreeOn_Less_Temp4.Temp=0xffffffff-	ptst_AgreeOn_SetVidType->CN_st_AgreeOn_SetVidType_Par[1].CN_st_AgreeOn_Less_Temp4.Temp+1;	
	  	   }
	  }	
	}
}






