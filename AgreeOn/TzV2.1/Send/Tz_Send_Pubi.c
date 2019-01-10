/*===============================================共用解析部分====================================================*/
static void Explain_Par(st_AgreeOn_Agree_Par_Cut	*ptst_AgreeOn_Agree_Par,uint8 *OutBuf,uint16 *ReDataLen,uint16 ParID);
static void Explain_WorkPar(st_AgreeOn_SetVidType_Par	*ptst_AgreeOn_SetVidType_Par,uint8 *OutBuf,uint16 *ReDataLen,uint8 ID);
static void Explain_WorkPar1(st_AgreeOn_SetVidType_Par	*ptst_AgreeOn_SetVidType_Par,uint8 *OutBuf,uint16 *ReDataLen,uint8 ID);
static void Explain_WorkPar2(st_AgreeOn_SetVidType  *ptst_AgreeOn_SetVidType,uint8 *OutBuf,uint16 *ReDataLen,uint8 ID,uint8 type);
static void Gps2CenGps_Timer(st_Data_Gps	*ptst_Data_Gps,uint8 *OutBuf);
static uint32 Expain_VidType2LessAddree(st_AgreeOn_SetVidType_Par	*ptst_AgreeOn_SetVidType_Par,uint8 ID);
static void Gps2CenGps(st_Data_Gps	*ptst_Data_Gps,uint8 *OutBuf);
static void Gps2CenGps_Latitude(st_Data_Gps	*ptst_Data_Gps,uint8 *OutBuf);
static void Gps2CenGps_LongHem(st_Data_Gps	*ptst_Data_Gps,uint8 *OutBuf);
static void Gps2CenGps_Speed(st_Data_Gps	*ptst_Data_Gps,uint8 *OutBuf);
static void Gps2CenGps_Angle(st_Data_Gps	*ptst_Data_Gps,uint8 *OutBuf);
static void Gps2CenGps_Height(st_Data_Gps	*ptst_Data_Gps,uint8 *OutBuf);
static void Gps2CenGps_Timer(st_Data_Gps	*ptst_Data_Gps,uint8 *OutBuf);
static void Gps2ReduceGps_Height(int32 *Hex32,uint8 *OutBuf);	//海拔高度
static void Explain_state(uint8 *OutBuf,st_AgreeOn_Send_UploaderPar	*ptst_AgreeOn_Send_UploaderPar,uint16 *ReDataLen);
static void Explain_UpPar(uint8 *OutBuf,st_AgreeOn_Send_UploaderPar	*ptst_AgreeOn_Send_UploaderPar,uint16 *ReDataLen);  //工作参数
static void Explain_Par(st_AgreeOn_Agree_Par_Cut	*ptst_AgreeOn_Agree_Par,uint8 *OutBuf,uint16 *ReDataLen,uint16 ParID)
{	uint16 DataLen=0,j;
	uint8 Len,SmLen;
	if(ParID==De_SetPar_SetGreenPar)
	{	OutBuf[DataLen++]=2;
		OutBuf[DataLen++]=((ptst_AgreeOn_Agree_Par->GreenPar>>8)&0xff);
		OutBuf[DataLen++]=(ptst_AgreeOn_Agree_Par->GreenPar&0xff);
		*ReDataLen=3;
	}
	else if(ParID==De_SetPar_SetGreenWord)
	{	Len=CN_st_Fun_AscNumber.Strsize16(ptst_AgreeOn_Agree_Par->GreenWord);
		if(Len>sizeof(ptst_AgreeOn_Agree_Par->GreenWord))
			Len=sizeof(ptst_AgreeOn_Agree_Par->GreenWord);	
		OutBuf[DataLen++]=Len;
		CN_st_Fun_AscNumber.MoveByte(OutBuf+DataLen,ptst_AgreeOn_Agree_Par->GreenWord,Len);
		*ReDataLen=Len+1;
	}
	else if(ParID==De_SetPar_SetListePhone)	
	{	Len=CN_st_Fun_AscNumber.Strsize16(ptst_AgreeOn_Agree_Par->ListePhone);
		if(Len>sizeof(ptst_AgreeOn_Agree_Par->ListePhone))
			Len=sizeof(ptst_AgreeOn_Agree_Par->ListePhone);	
		OutBuf[DataLen++]=Len;
		CN_st_Fun_AscNumber.MoveByte(OutBuf+DataLen,ptst_AgreeOn_Agree_Par->ListePhone,Len);
		*ReDataLen=Len+1;
	}
	else if(ParID==De_SetPar_SetResetPhone)	
	{	Len=CN_st_Fun_AscNumber.Strsize16(ptst_AgreeOn_Agree_Par->ResetPhone);
		if(Len>sizeof(ptst_AgreeOn_Agree_Par->ResetPhone))
			Len=sizeof(ptst_AgreeOn_Agree_Par->ResetPhone);	
		OutBuf[DataLen++]=Len;
		CN_st_Fun_AscNumber.MoveByte(OutBuf+DataLen,ptst_AgreeOn_Agree_Par->ResetPhone,Len);
		*ReDataLen=Len+1;
	}
	else if(ParID==De_SetPar_SetCerSevPhone)	
	{	Len=CN_st_Fun_AscNumber.Strsize16(ptst_AgreeOn_Agree_Par->CerSevPhone);
		if(Len>sizeof(ptst_AgreeOn_Agree_Par->CerSevPhone))
			Len=sizeof(ptst_AgreeOn_Agree_Par->CerSevPhone);	
		OutBuf[DataLen++]=Len;
		CN_st_Fun_AscNumber.MoveByte(OutBuf+DataLen,ptst_AgreeOn_Agree_Par->CerSevPhone,Len);
		*ReDataLen=Len+1;
	}
	else if(ParID==De_SetPar_SetCenPhone)	
	{	Len=CN_st_Fun_AscNumber.Strsize16(ptst_AgreeOn_Agree_Par->CenPhone);
		if(Len>sizeof(ptst_AgreeOn_Agree_Par->CenPhone))
			Len=sizeof(ptst_AgreeOn_Agree_Par->CenPhone);	
		OutBuf[DataLen++]=Len;
		CN_st_Fun_AscNumber.MoveByte(OutBuf+DataLen,ptst_AgreeOn_Agree_Par->CenPhone,Len);
    	*ReDataLen=Len+1;
	}
	else if(ParID==De_SetPar_SetAPN)	
	{	Len=CN_st_Fun_AscNumber.Strsize16(ptst_AgreeOn_Agree_Par->APN);
		if(Len>sizeof(ptst_AgreeOn_Agree_Par->APN))
			Len=sizeof(ptst_AgreeOn_Agree_Par->APN);	
		OutBuf[DataLen++]=Len;
		CN_st_Fun_AscNumber.MoveByte(OutBuf+DataLen,ptst_AgreeOn_Agree_Par->APN,Len);
		*ReDataLen=Len+1;
	}
	else if(ParID==De_SetPar_SetMastIP)	
	{	OutBuf[DataLen++]=4;
		OutBuf[DataLen++]=((ptst_AgreeOn_Agree_Par->MastIP>>24)&0xff);
		OutBuf[DataLen++]=((ptst_AgreeOn_Agree_Par->MastIP>>16)&0xff);	
		OutBuf[DataLen++]=((ptst_AgreeOn_Agree_Par->MastIP>>8)&0xff);
		OutBuf[DataLen++]=(ptst_AgreeOn_Agree_Par->MastIP&0xff);
		*ReDataLen=5;
	}
	else if(ParID==De_SetPar_SetMastDomainName)	
	{	Len=CN_st_Fun_AscNumber.Strsize16(ptst_AgreeOn_Agree_Par->MastDomainName);
		if(Len>sizeof(ptst_AgreeOn_Agree_Par->MastDomainName))
			Len=sizeof(ptst_AgreeOn_Agree_Par->MastDomainName);	
		OutBuf[DataLen++]=Len;
		CN_st_Fun_AscNumber.MoveByte(OutBuf+DataLen,ptst_AgreeOn_Agree_Par->MastDomainName,Len);
		*ReDataLen=Len+1;
	}
	else if(ParID==De_SetPar_SetReserveIP)	
	{	OutBuf[DataLen++]=4;
		OutBuf[DataLen++]=((ptst_AgreeOn_Agree_Par->ReserveIP>>24)&0xff);
		OutBuf[DataLen++]=((ptst_AgreeOn_Agree_Par->ReserveIP>>16)&0xff);	
		OutBuf[DataLen++]=((ptst_AgreeOn_Agree_Par->ReserveIP>>8)&0xff);
		OutBuf[DataLen++]=(ptst_AgreeOn_Agree_Par->ReserveIP&0xff);
		*ReDataLen=5;
	}
	else if(ParID==De_SetPar_SetReserveDomainName)	
	{	Len=CN_st_Fun_AscNumber.Strsize16(ptst_AgreeOn_Agree_Par->ReserveDomainName);
		if(Len>sizeof(ptst_AgreeOn_Agree_Par->ReserveDomainName))
			Len=sizeof(ptst_AgreeOn_Agree_Par->ReserveDomainName);	
		OutBuf[DataLen++]=Len;
		CN_st_Fun_AscNumber.MoveByte(OutBuf+DataLen,ptst_AgreeOn_Agree_Par->ReserveDomainName,Len);
    	*ReDataLen=Len+1;
	}
	else if(ParID==De_SetPar_SetCenPort)	
	{	OutBuf[DataLen++]=2;
		OutBuf[DataLen++]=((ptst_AgreeOn_Agree_Par->CenPort>>8)&0xff);
		OutBuf[DataLen++]=(ptst_AgreeOn_Agree_Par->CenPort&0xff);
		*ReDataLen=3;	
	}
	else if(ParID==De_SetPar_SetCentHeart)	
	{	OutBuf[DataLen++]=1;
		OutBuf[DataLen++]=(ptst_AgreeOn_Agree_Par->CentHeart&0xff);	
		*ReDataLen=2;
	}
	else if(ParID==De_SetPar_SetUseName)	
	{	Len=CN_st_Fun_AscNumber.Strsize16(ptst_AgreeOn_Agree_Par->UseName);
		if(Len>sizeof(ptst_AgreeOn_Agree_Par->UseName))
			Len=sizeof(ptst_AgreeOn_Agree_Par->UseName);	
		OutBuf[DataLen++]=Len;
		CN_st_Fun_AscNumber.MoveByte(OutBuf+DataLen,ptst_AgreeOn_Agree_Par->UseName,Len);
	    *ReDataLen=Len+1;
	}
	else if(ParID==De_SetPar_SetUsePass)	
	{	Len=CN_st_Fun_AscNumber.Strsize16(ptst_AgreeOn_Agree_Par->UsePass);
		if(Len>sizeof(ptst_AgreeOn_Agree_Par->UsePass))
			Len=sizeof(ptst_AgreeOn_Agree_Par->UsePass);	
		OutBuf[DataLen++]=Len;
		CN_st_Fun_AscNumber.MoveByte(OutBuf+DataLen,ptst_AgreeOn_Agree_Par->UsePass,Len);
		*ReDataLen=Len+1;
	}
	else if(ParID==De_SetPar_SetDevHeart)	
	{	OutBuf[DataLen++]=1;
		OutBuf[DataLen++]=(ptst_AgreeOn_Agree_Par->DevHeart&0xff);	
		*ReDataLen=2;
	}
	else if(ParID==De_SetPar_SetComMod)	
	{	OutBuf[DataLen++]=1;
		OutBuf[DataLen++]=(ptst_AgreeOn_Agree_Par->ComMod&0xff);
		*ReDataLen=2;	
	}
	else if(ParID==De_SetPar_SetIPRepeat)	
	{	OutBuf[DataLen++]=1;
		OutBuf[DataLen++]=(ptst_AgreeOn_Agree_Par->IPRepeat&0xff);
		*ReDataLen=2;	
	}
	else if(ParID==De_SetPar_SetIPRepeatTime)	
	{	OutBuf[DataLen++]=1;
		OutBuf[DataLen++]=(ptst_AgreeOn_Agree_Par->IPRepeatTime&0xff);	
		*ReDataLen=2;
	}
	else if(ParID==De_SetPar_SetMessageRepeat)	
	{	OutBuf[DataLen++]=1;
		OutBuf[DataLen++]=(ptst_AgreeOn_Agree_Par->MessageRepeat&0xff);	
		*ReDataLen=2;
	}
	else if(ParID==De_SetPar_SetMessageRepeatTimer)	
	{	OutBuf[DataLen++]=1;
		OutBuf[DataLen++]=(ptst_AgreeOn_Agree_Par->MessageRepeatTimer&0xff);
		*ReDataLen=2;	
	}
	else if(ParID==De_SetPar_SetIPTransSms)	
	{	OutBuf[DataLen++]=2;
		OutBuf[DataLen++]=(ptst_AgreeOn_Agree_Par->IPTransSms>>8);	
		OutBuf[DataLen++]=(ptst_AgreeOn_Agree_Par->IPTransSms&0xff);
		*ReDataLen=3;
	}
	else if(ParID==De_SetPar_SetDataLog)	
	{	OutBuf[DataLen++]=8;
	    CN_st_Fun_AscNumber.ClsArray(OutBuf+DataLen,8);
		for(j=0,OutBuf[8]=0;j<8;j++)
		{	if(ptst_AgreeOn_Agree_Par->DataLog[j]==0)
				continue;
			OutBuf[8]|=(0x01<<j);
		}
		*ReDataLen=9;
	}
	else if(ParID==De_SetPar_SetDataScotomaLog)	
	{	OutBuf[DataLen++]=8;
	    CN_st_Fun_AscNumber.ClsArray(OutBuf+DataLen,8);
		for(j=0,OutBuf[8]=0;j<8;j++)
		{	if(ptst_AgreeOn_Agree_Par->DataScotomaLog[j]==0)
				continue;
			OutBuf[8]|=(0x01<<j);
		}
		*ReDataLen=9;
	}  
	else if(ParID==De_SetPar_SetParLoad)			//工作参数
	{	Len=DataLen;
		DataLen++;
		for(j=0;j<(sizeof(CN_Ba_WordPar)/sizeof(uint16));j++)
		{	if(ptst_AgreeOn_Agree_Par->ParLoad[j]!=De_WordPar_Open)
				continue;
			OutBuf[DataLen++]=((CN_Ba_WordPar[j]>>8)&0xff);
			OutBuf[DataLen++]=(CN_Ba_WordPar[j]&0xff);
		}
		OutBuf[Len]=DataLen-Len-1;
		*ReDataLen=DataLen;
	}
	else if(ParID==De_SetPar_SetWireLessPar)		//无线传感器
	{	Len=DataLen;
		DataLen++;
		DataLen++;
		for(j=0;j<(sizeof(CN_Ba_LessPar)/sizeof(uint16));j++)
		{	if(ptst_AgreeOn_Agree_Par->WireLessPar[j]==De_WordPar_NoAdree)
				continue;
			OutBuf[DataLen++]=((ptst_AgreeOn_Agree_Par->WireLessPar[j]>>24)&0xff);
			OutBuf[DataLen++]=((ptst_AgreeOn_Agree_Par->WireLessPar[j]>>16)&0xff);
			OutBuf[DataLen++]=((ptst_AgreeOn_Agree_Par->WireLessPar[j]>>8)&0xff);
			OutBuf[DataLen++]=((ptst_AgreeOn_Agree_Par->WireLessPar[j]>>0)&0xff);
			OutBuf[DataLen++]=((CN_Ba_LessPar[j]>>8)&0xff);
			OutBuf[DataLen++]=((CN_Ba_LessPar[j]>>0)&0xff);
		}
	   	OutBuf[Len]=DataLen-Len-1;
		OutBuf[Len+1]=((OutBuf[Len]-1)/6);
		*ReDataLen=DataLen;
	}
	else if(ParID==De_SetPar_SetDePassWord)
	{	OutBuf[DataLen++]=4;
		OutBuf[DataLen++]=((ptst_AgreeOn_Agree_Par->DePassWord>>24)&0xff);
		OutBuf[DataLen++]=((ptst_AgreeOn_Agree_Par->DePassWord>>16)&0xff);	
		OutBuf[DataLen++]=((ptst_AgreeOn_Agree_Par->DePassWord>>8)&0xff);
		OutBuf[DataLen++]=(ptst_AgreeOn_Agree_Par->DePassWord&0xff);
		*ReDataLen=5;
	}
	else if(ParID==De_SetPar_ComFac)
	{	;
	}
	else if(ParID==De_SetPar_SetAccTimer)
	{	OutBuf[DataLen++]=4;
		OutBuf[DataLen++]=((ptst_AgreeOn_Agree_Par->AccTimer>>24)&0xff);
		OutBuf[DataLen++]=((ptst_AgreeOn_Agree_Par->AccTimer>>16)&0xff);	
		OutBuf[DataLen++]=((ptst_AgreeOn_Agree_Par->AccTimer>>8)&0xff);
		OutBuf[DataLen++]=(ptst_AgreeOn_Agree_Par->AccTimer&0xff);
		*ReDataLen=5;	
	}
	else if(ParID==De_SetPar_SetRunLen)
	{	OutBuf[DataLen++]=4;
		OutBuf[DataLen++]=((ptst_AgreeOn_Agree_Par->RunLen>>24)&0xff);
		OutBuf[DataLen++]=((ptst_AgreeOn_Agree_Par->RunLen>>16)&0xff);	
		OutBuf[DataLen++]=((ptst_AgreeOn_Agree_Par->RunLen>>8)&0xff);
		OutBuf[DataLen++]=(ptst_AgreeOn_Agree_Par->RunLen&0xff);
		*ReDataLen=5;	
	}
	else if(ParID==De_SetPar_SetPerPuse)
	{	OutBuf[DataLen++]=1;
		OutBuf[DataLen++]=ptst_AgreeOn_Agree_Par->PerPuse;
		*ReDataLen=2;	
	}
	else if(ParID==De_SetPar_SetCarFeature)
	{	OutBuf[DataLen++]=2;
		OutBuf[DataLen++]=(ptst_AgreeOn_Agree_Par->CarFeature>>8);	
		OutBuf[DataLen++]=(ptst_AgreeOn_Agree_Par->CarFeature&0xff);
		*ReDataLen=3;
	}
	else if(ParID==De_SetPar_SetTakeLCD)
	{	OutBuf[DataLen++]=1;
		OutBuf[DataLen++]=(ptst_AgreeOn_Agree_Par->TakeLCD&0xff);
		*ReDataLen=2;	
	}
	else if(ParID==De_SetPar_SetOilFrequency)
	{	OutBuf[DataLen++]=1;
		OutBuf[DataLen++]=(ptst_AgreeOn_Agree_Par->OilFrequency&0xff);	
		*ReDataLen=2;
	}
	else if(ParID==De_SetPar_SetSleepTimer)
	{	OutBuf[DataLen++]=2;
		OutBuf[DataLen++]=(ptst_AgreeOn_Agree_Par->SleepTimer>>8);	
		OutBuf[DataLen++]=(ptst_AgreeOn_Agree_Par->SleepTimer&0xff);
		*ReDataLen=3;
	}
	else if(ParID==De_SetPar_SetCloseTimer)
	{	OutBuf[DataLen++]=2;
		OutBuf[DataLen++]=(ptst_AgreeOn_Agree_Par->CloseTimer>>8);	
		OutBuf[DataLen++]=(ptst_AgreeOn_Agree_Par->CloseTimer&0xff);
		*ReDataLen=3;
	}
	else if(ParID==De_SetPar_SetLogMess)
	{	OutBuf[DataLen++]=1;
		OutBuf[DataLen++]=(ptst_AgreeOn_Agree_Par->LogMess&0xff);
		*ReDataLen=2;	
	}
	else if(ParID==De_SetPar_SetTaskVid)
	{	OutBuf[DataLen++]=1;
		OutBuf[DataLen++]=(ptst_AgreeOn_Agree_Par->TaskVid&0xff);
		*ReDataLen=2;	
	}
	else if(ParID==De_SetPar_SetHighSpeed)
	{	OutBuf[DataLen++]=2;
		OutBuf[DataLen++]=ptst_AgreeOn_Agree_Par->CN_High_st_Waring_Par.WartingVl;
		OutBuf[DataLen++]=ptst_AgreeOn_Agree_Par->CN_High_st_Waring_Par.WartingTimer;
		*ReDataLen=3;	
	}
	else if(ParID==De_SetPar_SetLowSpeed)
	{	OutBuf[DataLen++]=2;
		OutBuf[DataLen++]=ptst_AgreeOn_Agree_Par->CN_Low_st_Waring_Par.WartingVl;
		OutBuf[DataLen++]=ptst_AgreeOn_Agree_Par->CN_Low_st_Waring_Par.WartingTimer;
		*ReDataLen=3;	
	}
	else if(ParID==De_SetPar_SetLowVlt)
	{	OutBuf[DataLen++]=2;
		OutBuf[DataLen++]=(ptst_AgreeOn_Agree_Par->CN_Vo_st_Waring_Par.WartingVl/1000);
		OutBuf[DataLen++]=ptst_AgreeOn_Agree_Par->CN_Vo_st_Waring_Par.WartingTimer;	
		*ReDataLen=3;
	}
	else if(ParID==De_SetPar_SetVidType)
	{	OutBuf[DataLen++]=2;
		OutBuf[DataLen++]=0;
		OutBuf[DataLen]=0;
		if(ptst_AgreeOn_Agree_Par->CN_st_VidType.HelpWarning==De_AgreeOn_Vid_Fun_Open)
			OutBuf[DataLen]=(OutBuf[DataLen]|0x01);	
		if(ptst_AgreeOn_Agree_Par->CN_st_VidType.Oper==De_AgreeOn_Vid_Fun_Open)
			OutBuf[DataLen]=(OutBuf[DataLen]|0x02);	
		if(ptst_AgreeOn_Agree_Par->CN_st_VidType.TurnOver==De_AgreeOn_Vid_Fun_Open)
			OutBuf[DataLen]=(OutBuf[DataLen]|0x04);	
		if(ptst_AgreeOn_Agree_Par->CN_st_VidType.AccOpen==De_AgreeOn_Vid_Fun_Open)
			OutBuf[DataLen]=(OutBuf[DataLen]|0x08);	
		if(ptst_AgreeOn_Agree_Par->CN_st_VidType.AccClose==De_AgreeOn_Vid_Fun_Open)
			OutBuf[DataLen]=(OutBuf[DataLen]|0x10);
			*ReDataLen=3;
	}
	else if(ParID==De_SetPar_SetOrderFrmTimer)
	{	OutBuf[DataLen++]=1;
		OutBuf[DataLen++]=(ptst_AgreeOn_Agree_Par->OrderFrmTimer/60);
		*ReDataLen=2;	
	}
	else if(ParID==De_SetPar_HardWareEdit)
	{	Len=CN_st_Fun_AscNumber.Strsize16(ptst_AgreeOn_Agree_Par->HardWareEdit);
		if(Len>sizeof(ptst_AgreeOn_Agree_Par->HardWareEdit))
			Len=sizeof(ptst_AgreeOn_Agree_Par->HardWareEdit);	
		OutBuf[DataLen++]=Len;
		CN_st_Fun_AscNumber.MoveByte(OutBuf+DataLen,ptst_AgreeOn_Agree_Par->HardWareEdit,Len);		
		*ReDataLen=Len+1;
	}
	else if(ParID==De_SetPar_SoftWareEdit)
	{	Len=CN_st_Fun_AscNumber.Strsize16(ptst_AgreeOn_Agree_Par->SoftWareEdit);
		if(Len>sizeof(ptst_AgreeOn_Agree_Par->SoftWareEdit))
			Len=sizeof(ptst_AgreeOn_Agree_Par->SoftWareEdit);	
		OutBuf[DataLen++]=Len;
		CN_st_Fun_AscNumber.MoveByte(OutBuf+DataLen,ptst_AgreeOn_Agree_Par->SoftWareEdit,Len);
		*ReDataLen=Len+1;
	}
	else if(ParID==De_SetPar_MachID)
	{	OutBuf[DataLen++]=12;
		OutBuf[DataLen++]='0';
		OutBuf[DataLen++]='1';
		CN_st_Fun_AscNumber.Bcd2Asc(ptst_AgreeOn_Agree_Par->MachID,OutBuf+DataLen,5);

		//CN_st_Fun_AscNumber.MoveByte(OutBuf+1,ptst_AgreeOn_Agree_Par->MachID,sizeof(ptst_AgreeOn_Agree_Par->MachID));
		//CN_st_Fun_AscNumber.Bcd2Asc(ptst_AgreeOn_Agree_Par->MachID,OutBuf+1,8);
		*ReDataLen=13;
	}
	else if(ParID==De_SetPar_Menum)
	{	Len=DataLen;
		DataLen++;	
		for(j=0;j<ptst_AgreeOn_Agree_Par->CN_st_AgreeOn_AmendMenum.Number;j++)
		{	OutBuf[DataLen++]=ptst_AgreeOn_Agree_Par->CN_st_AgreeOn_AmendMenum.CN_st_AgreeOn_Menum_Infor[j].ID;
			OutBuf[DataLen++]=ptst_AgreeOn_Agree_Par->CN_st_AgreeOn_AmendMenum.CN_st_AgreeOn_Menum_Infor[j].BackID;	
			SmLen=CN_st_Fun_AscNumber.Strsize(ptst_AgreeOn_Agree_Par->CN_st_AgreeOn_AmendMenum.CN_st_AgreeOn_Menum_Infor[j].Cut);
			if(SmLen>sizeof(ptst_AgreeOn_Agree_Par->CN_st_AgreeOn_AmendMenum.CN_st_AgreeOn_Menum_Infor[0].Cut))
				SmLen=sizeof(ptst_AgreeOn_Agree_Par->CN_st_AgreeOn_AmendMenum.CN_st_AgreeOn_Menum_Infor[0].Cut);
			OutBuf[DataLen++]=SmLen;
			CN_st_Fun_AscNumber.MoveByte(OutBuf+DataLen,ptst_AgreeOn_Agree_Par->CN_st_AgreeOn_AmendMenum.CN_st_AgreeOn_Menum_Infor[j].Cut,SmLen);		
		   	DataLen+=SmLen;
		}
		OutBuf[Len]=DataLen-Len-1;	
		*ReDataLen=DataLen;

	}
	else if(ParID==De_SetPar_Phone)	
	{	Len=DataLen;
		DataLen++;	
		for(j=0;j<ptst_AgreeOn_Agree_Par->CN_st_AgreeOn_Phone.Number;j++)
		{	OutBuf[DataLen++]=ptst_AgreeOn_Agree_Par->CN_st_AgreeOn_Phone.CN_st_AgreeOn_Phone_Par[j].State;
			SmLen=CN_st_Fun_AscNumber.Strsize(ptst_AgreeOn_Agree_Par->CN_st_AgreeOn_Phone.CN_st_AgreeOn_Phone_Par[j].Name);
			if(SmLen>8)
				SmLen=8;
			CN_st_Fun_AscNumber.MoveByte(OutBuf+DataLen,ptst_AgreeOn_Agree_Par->CN_st_AgreeOn_Phone.CN_st_AgreeOn_Phone_Par[j].Name,SmLen);	
			if(SmLen<8)
				memset(OutBuf+DataLen+SmLen,' ',8-SmLen);			
			DataLen+=8;
			SmLen=CN_st_Fun_AscNumber.Strsize(ptst_AgreeOn_Agree_Par->CN_st_AgreeOn_Phone.CN_st_AgreeOn_Phone_Par[j].Phone);
			if(SmLen>sizeof(ptst_AgreeOn_Agree_Par->CN_st_AgreeOn_Phone.CN_st_AgreeOn_Phone_Par[0].Phone))
				SmLen=sizeof(ptst_AgreeOn_Agree_Par->CN_st_AgreeOn_Phone.CN_st_AgreeOn_Phone_Par[0].Phone);
			OutBuf[DataLen++]=SmLen;
			CN_st_Fun_AscNumber.MoveByte(OutBuf+DataLen,ptst_AgreeOn_Agree_Par->CN_st_AgreeOn_Phone.CN_st_AgreeOn_Phone_Par[j].Phone,SmLen);	
			DataLen+=SmLen;		
		}
		OutBuf[Len]=DataLen-Len-1;
		*ReDataLen=DataLen;	
	}
	else if(ParID==De_SetPar_ConfineCall)	
	{	Len=DataLen;
		DataLen++;	
		OutBuf[DataLen++]=ptst_AgreeOn_Agree_Par->CN_st_AgreeOn_ConfineCall.State;
		SmLen=CN_st_Fun_AscNumber.Strsize16(ptst_AgreeOn_Agree_Par->CN_st_AgreeOn_ConfineCall.Phone);	   
		if(Len>sizeof(ptst_AgreeOn_Agree_Par->ListePhone))
			Len=sizeof(ptst_AgreeOn_Agree_Par->ListePhone);	
			CN_st_Fun_AscNumber.MoveByte(OutBuf+DataLen,ptst_AgreeOn_Agree_Par->ListePhone,SmLen);
		OutBuf[Len]=SmLen+1;
		*ReDataLen=SmLen+2;
	}
	else if(ParID==De_SetPar_DriverID)
	{	Len=DataLen;
		DataLen++;	
		for(j=0;j<ptst_AgreeOn_Agree_Par->CN_st_AgreeOn_Driver.Number;j++)
		{	SmLen=CN_st_Fun_AscNumber.Strsize(ptst_AgreeOn_Agree_Par->CN_st_AgreeOn_Driver.CN_st_AgreeOn_Driver_Par[j].ID);
			if(SmLen>sizeof(ptst_AgreeOn_Agree_Par->CN_st_AgreeOn_Driver.CN_st_AgreeOn_Driver_Par[0].ID))
				SmLen=sizeof(ptst_AgreeOn_Agree_Par->CN_st_AgreeOn_Driver.CN_st_AgreeOn_Driver_Par[0].ID);
			OutBuf[DataLen++]=SmLen;
			CN_st_Fun_AscNumber.MoveByte(OutBuf+DataLen,ptst_AgreeOn_Agree_Par->CN_st_AgreeOn_Driver.CN_st_AgreeOn_Driver_Par[j].ID,SmLen);	
			DataLen+=SmLen;
			SmLen=CN_st_Fun_AscNumber.Strsize(ptst_AgreeOn_Agree_Par->CN_st_AgreeOn_Driver.CN_st_AgreeOn_Driver_Par[j].Phone);
			if(SmLen>sizeof(ptst_AgreeOn_Agree_Par->CN_st_AgreeOn_Driver.CN_st_AgreeOn_Driver_Par[0].Phone))
				SmLen=sizeof(ptst_AgreeOn_Agree_Par->CN_st_AgreeOn_Driver.CN_st_AgreeOn_Driver_Par[0].Phone);
			OutBuf[DataLen++]=SmLen;
			CN_st_Fun_AscNumber.MoveByte(OutBuf+DataLen,ptst_AgreeOn_Agree_Par->CN_st_AgreeOn_Driver.CN_st_AgreeOn_Driver_Par[j].Phone,SmLen);	
			DataLen+=SmLen;
		}
		OutBuf[Len]=DataLen-Len-1;
		*ReDataLen=DataLen;	
	}
	else if(ParID==De_SetPar_DriverLogin)
	{	Len=DataLen;
		DataLen++;	
		SmLen=CN_st_Fun_AscNumber.Strsize(ptst_AgreeOn_Agree_Par->DriverID);
		if(SmLen>sizeof(ptst_AgreeOn_Agree_Par->DriverID))
			SmLen=sizeof(ptst_AgreeOn_Agree_Par->DriverID);
		if(SmLen==0)
			SmLen=1;
		CN_st_Fun_AscNumber.MoveByte(OutBuf+DataLen,ptst_AgreeOn_Agree_Par->DriverID,SmLen);
		OutBuf[Len]=SmLen;	
		*ReDataLen=SmLen+1;
	}
}



static void Explain_WorkPar(st_AgreeOn_SetVidType_Par	*ptst_AgreeOn_SetVidType_Par,uint8 *OutBuf,uint16 *ReDataLen,uint8 ID)
{	uint16 DataLen;
	DataLen=0;
	if(ID==0)
	{	OutBuf[DataLen++]=1;
		OutBuf[DataLen++]=ptst_AgreeOn_SetVidType_Par->Switch1;
	}
	else if(ID==1)
	{	OutBuf[DataLen++]=1;
		OutBuf[DataLen++]=ptst_AgreeOn_SetVidType_Par->Switch2;
	}
	else if(ID==2)
	{	OutBuf[DataLen++]=1;
		OutBuf[DataLen++]=ptst_AgreeOn_SetVidType_Par->Switch3;
	}
	else if(ID==3)
	{	OutBuf[DataLen++]=1;
		OutBuf[DataLen++]=ptst_AgreeOn_SetVidType_Par->Switch4;
	}
	else if(ID==4)
	{	OutBuf[DataLen++]=1;
		OutBuf[DataLen++]=ptst_AgreeOn_SetVidType_Par->Switch5;
	}
	else if(ID==5)
	{	OutBuf[DataLen++]=1;
		OutBuf[DataLen++]=ptst_AgreeOn_SetVidType_Par->Switch6;
	}
	else if(ID==6)
	{	OutBuf[DataLen++]=1;
		OutBuf[DataLen++]=ptst_AgreeOn_SetVidType_Par->Switch7;
	}
	else if(ID==7)
	{	OutBuf[DataLen++]=1;
		OutBuf[DataLen++]=ptst_AgreeOn_SetVidType_Par->Switch8;
	}
	else if(ID==8)
	{	OutBuf[DataLen++]=1;
		OutBuf[DataLen++]=ptst_AgreeOn_SetVidType_Par->Switch9;
	}
	else if(ID==9)
	{	OutBuf[DataLen++]=1;
		OutBuf[DataLen++]=ptst_AgreeOn_SetVidType_Par->Switch10;
	}
	
	else if(ID==10)
	{	OutBuf[DataLen++]=1;
		OutBuf[DataLen++]=ptst_AgreeOn_SetVidType_Par->Switch11;
	}
	else if(ID==11)
	{	OutBuf[DataLen++]=1;
		OutBuf[DataLen++]=ptst_AgreeOn_SetVidType_Par->Switch12;
	}
	else if(ID==12)
	{	OutBuf[DataLen++]=1;
		OutBuf[DataLen++]=ptst_AgreeOn_SetVidType_Par->Switch13;
	}
	else if(ID==13)
	{	OutBuf[DataLen++]=1;
		OutBuf[DataLen++]=ptst_AgreeOn_SetVidType_Par->Switch14;
	}
	else if(ID==14)
	{	OutBuf[DataLen++]=1;
		OutBuf[DataLen++]=ptst_AgreeOn_SetVidType_Par->Switch15;
	}
	else if(ID==15)
	{	OutBuf[DataLen++]=1;
		OutBuf[DataLen++]=ptst_AgreeOn_SetVidType_Par->Switch16;
	}
	else if(ID==16)
	{	OutBuf[DataLen++]=1;
		OutBuf[DataLen++]=(ptst_AgreeOn_SetVidType_Par->CN_Less_Switch1.OpenOrClose);
	}
	else if(ID==17)
	{	OutBuf[DataLen++]=1;
		OutBuf[DataLen++]=(ptst_AgreeOn_SetVidType_Par->CN_Less_Switch2.Addree);
		OutBuf[DataLen++]=(ptst_AgreeOn_SetVidType_Par->CN_Less_Switch2.OpenOrClose);
	}
	else if(ID==18)
	{	OutBuf[DataLen++]=1;
		OutBuf[DataLen++]=(ptst_AgreeOn_SetVidType_Par->CN_Less_Switch3.OpenOrClose);
	}
	else if(ID==19)
	{	OutBuf[DataLen++]=1;
		OutBuf[DataLen++]=(ptst_AgreeOn_SetVidType_Par->CN_Less_Switch4.OpenOrClose);
	}
	else if(ID==20)
	{	OutBuf[DataLen++]=1;
		OutBuf[DataLen++]=(ptst_AgreeOn_SetVidType_Par->CN_Less_Switch5.OpenOrClose);
	}
	else if(ID==21)
	{	OutBuf[DataLen++]=1;
		OutBuf[DataLen++]=(ptst_AgreeOn_SetVidType_Par->CN_Less_Switch6.OpenOrClose);
	}
	else if(ID==22)
	{	OutBuf[DataLen++]=4;
		OutBuf[DataLen++]=(ptst_AgreeOn_SetVidType_Par->AccTimer>>24);
		OutBuf[DataLen++]=(ptst_AgreeOn_SetVidType_Par->AccTimer>>16);
		OutBuf[DataLen++]=(ptst_AgreeOn_SetVidType_Par->AccTimer>>8);
		OutBuf[DataLen++]=(ptst_AgreeOn_SetVidType_Par->AccTimer);
	}
	else if(ID==23)
	{	OutBuf[DataLen++]=4;
		OutBuf[DataLen++]=(ptst_AgreeOn_SetVidType_Par->Mileage>>24);
		OutBuf[DataLen++]=(ptst_AgreeOn_SetVidType_Par->Mileage>>16);
		OutBuf[DataLen++]=(ptst_AgreeOn_SetVidType_Par->Mileage>>8);
		OutBuf[DataLen++]=(ptst_AgreeOn_SetVidType_Par->Mileage);
	}
	else if(ID==24)
	{	OutBuf[DataLen++]=2;
		OutBuf[DataLen++]=(ptst_AgreeOn_SetVidType_Par->Oil1>>8);
		OutBuf[DataLen++]=(ptst_AgreeOn_SetVidType_Par->Oil1);
	}
	else if(ID==25)
	{	OutBuf[DataLen++]=1;
		OutBuf[DataLen++]=(ptst_AgreeOn_SetVidType_Par->Sem);
	}
	else if(ID==26)
	{	OutBuf[DataLen++]=4;
		OutBuf[DataLen++]=(ptst_AgreeOn_SetVidType_Par->SendOilTimer>>24);
		OutBuf[DataLen++]=(ptst_AgreeOn_SetVidType_Par->SendOilTimer>>16);
		OutBuf[DataLen++]=(ptst_AgreeOn_SetVidType_Par->SendOilTimer>>8);
		OutBuf[DataLen++]=(ptst_AgreeOn_SetVidType_Par->SendOilTimer);
	}
	else if(ID==27)
	{	OutBuf[DataLen++]=3;
	    OutBuf[DataLen++]=0x00;
		if(ptst_AgreeOn_SetVidType_Par->Temp>0x80000000)
		{	OutBuf[DataLen-1]=0x11;
			ptst_AgreeOn_SetVidType_Par->Temp=0xffffffff-ptst_AgreeOn_SetVidType_Par->Temp+1;
		}
		OutBuf[DataLen++]=ptst_AgreeOn_SetVidType_Par->Temp/100;
		OutBuf[DataLen++]=((ptst_AgreeOn_SetVidType_Par->Temp/10)%100);
	}
	else if(ID==28)
	{ 	OutBuf[DataLen++]=2;
		OutBuf[DataLen++]=(ptst_AgreeOn_SetVidType_Par->Oil2>>8);
		OutBuf[DataLen++]=(ptst_AgreeOn_SetVidType_Par->Oil2);
	}
	else if(ID==29)
	{ 	OutBuf[DataLen++]=4;
		OutBuf[DataLen++]=(ptst_AgreeOn_SetVidType_Par->Pulse>>24);
		OutBuf[DataLen++]=(ptst_AgreeOn_SetVidType_Par->Pulse>>16);
		OutBuf[DataLen++]=(ptst_AgreeOn_SetVidType_Par->Pulse>>8);
		OutBuf[DataLen++]=(ptst_AgreeOn_SetVidType_Par->Pulse);
	}
	else if(ID==30)
	{ 	OutBuf[DataLen++]=2;
		OutBuf[DataLen++]=(ptst_AgreeOn_SetVidType_Par->Humidity/1000);
		OutBuf[DataLen++]=((ptst_AgreeOn_SetVidType_Par->Humidity/10)%100);
	}
	else if(ID==31)
	{ 	OutBuf[DataLen++]=1;
		OutBuf[DataLen++]=(ptst_AgreeOn_SetVidType_Par->OilBaifen/10);
	}
	else if(ID==32)
	{	OutBuf[DataLen++]=3;
	    OutBuf[DataLen++]=0x00;	
		if(ptst_AgreeOn_SetVidType_Par->CN_st_AgreeOn_Less_Temp1.Temp>0x80000000)
		{	OutBuf[DataLen-1]=0x11;
			ptst_AgreeOn_SetVidType_Par->CN_st_AgreeOn_Less_Temp1.Temp=0xffffffff-ptst_AgreeOn_SetVidType_Par->CN_st_AgreeOn_Less_Temp1.Temp+1;
		}
	   	OutBuf[DataLen++]=ptst_AgreeOn_SetVidType_Par->CN_st_AgreeOn_Less_Temp1.Temp/100;
		OutBuf[DataLen++]=((ptst_AgreeOn_SetVidType_Par->CN_st_AgreeOn_Less_Temp1.Temp/10)%100);
	}
	else if(ID==33)
	{	OutBuf[DataLen++]=3;
	    OutBuf[DataLen++]=0x00;	
		if(ptst_AgreeOn_SetVidType_Par->CN_st_AgreeOn_Less_Temp2.Temp>0x80000000)
		{	OutBuf[DataLen-1]=0x11;
			ptst_AgreeOn_SetVidType_Par->CN_st_AgreeOn_Less_Temp2.Temp=0xffffffff-ptst_AgreeOn_SetVidType_Par->CN_st_AgreeOn_Less_Temp2.Temp+1;
		}
	   	OutBuf[DataLen++]=ptst_AgreeOn_SetVidType_Par->CN_st_AgreeOn_Less_Temp2.Temp/100;
		OutBuf[DataLen++]=((ptst_AgreeOn_SetVidType_Par->CN_st_AgreeOn_Less_Temp2.Temp/10)%100);
		OutBuf[DataLen++]=ptst_AgreeOn_SetVidType_Par->CN_st_AgreeOn_Less_Temp2.State;
	}
	else if(ID==34)
	{	OutBuf[DataLen++]=3;	
		OutBuf[DataLen++]=0x00;
		if(ptst_AgreeOn_SetVidType_Par->CN_st_AgreeOn_Less_Temp3.Temp>0x80000000)
		{	OutBuf[DataLen-1]=0x11;
			ptst_AgreeOn_SetVidType_Par->CN_st_AgreeOn_Less_Temp3.Temp=0xffffffff-ptst_AgreeOn_SetVidType_Par->CN_st_AgreeOn_Less_Temp3.Temp+1;
		}
	   	OutBuf[DataLen++]=ptst_AgreeOn_SetVidType_Par->CN_st_AgreeOn_Less_Temp3.Temp/100;
		OutBuf[DataLen++]=((ptst_AgreeOn_SetVidType_Par->CN_st_AgreeOn_Less_Temp3.Temp/10)%100);
		}
	else if(ID==35)
	{	OutBuf[DataLen++]=3;
		OutBuf[DataLen++]=0x00;
		if(ptst_AgreeOn_SetVidType_Par->CN_st_AgreeOn_Less_Temp4.Temp>0x80000000)
		{	OutBuf[DataLen-1]=0x11;
			ptst_AgreeOn_SetVidType_Par->CN_st_AgreeOn_Less_Temp4.Temp=0xffffffff-ptst_AgreeOn_SetVidType_Par->CN_st_AgreeOn_Less_Temp4.Temp+1;
		}
	   	OutBuf[DataLen++]=ptst_AgreeOn_SetVidType_Par->CN_st_AgreeOn_Less_Temp4.Temp/100;
		OutBuf[DataLen++]=((ptst_AgreeOn_SetVidType_Par->CN_st_AgreeOn_Less_Temp4.Temp/10)%100);
		}
	*ReDataLen=DataLen;
}

static void Explain_WorkPar1(st_AgreeOn_SetVidType_Par	*ptst_AgreeOn_SetVidType_Par,uint8 *OutBuf,uint16 *ReDataLen,uint8 ID)
{	uint16 DataLen;
	DataLen=0;
	if(ID==0)
	{	OutBuf[DataLen++]=1;
		OutBuf[DataLen++]=ptst_AgreeOn_SetVidType_Par->Switch1;
	}
	else if(ID==1)
	{	OutBuf[DataLen++]=1;
		OutBuf[DataLen++]=ptst_AgreeOn_SetVidType_Par->Switch2;
	}
	else if(ID==2)
	{	OutBuf[DataLen++]=1;
		OutBuf[DataLen++]=ptst_AgreeOn_SetVidType_Par->Switch3;
	}
	else if(ID==3)
	{	OutBuf[DataLen++]=1;
		OutBuf[DataLen++]=ptst_AgreeOn_SetVidType_Par->Switch4;
	}
	else if(ID==4)
	{	OutBuf[DataLen++]=1;
		OutBuf[DataLen++]=ptst_AgreeOn_SetVidType_Par->Switch5;
	}
	else if(ID==5)
	{	OutBuf[DataLen++]=1;
		OutBuf[DataLen++]=ptst_AgreeOn_SetVidType_Par->Switch6;
	}
	else if(ID==6)
	{	OutBuf[DataLen++]=1;
		OutBuf[DataLen++]=ptst_AgreeOn_SetVidType_Par->Switch7;
	}
	else if(ID==7)
	{	OutBuf[DataLen++]=1;
		OutBuf[DataLen++]=ptst_AgreeOn_SetVidType_Par->Switch8;
	}
	else if(ID==8)
	{	OutBuf[DataLen++]=1;
		OutBuf[DataLen++]=ptst_AgreeOn_SetVidType_Par->Switch9;
	}
	else if(ID==9)
	{	OutBuf[DataLen++]=1;
		OutBuf[DataLen++]=ptst_AgreeOn_SetVidType_Par->Switch10;
	}
	
	else if(ID==10)
	{	OutBuf[DataLen++]=1;
		OutBuf[DataLen++]=ptst_AgreeOn_SetVidType_Par->Switch11;
	}
	else if(ID==11)
	{	OutBuf[DataLen++]=1;
		OutBuf[DataLen++]=ptst_AgreeOn_SetVidType_Par->Switch12;
	}
	else if(ID==12)
	{	OutBuf[DataLen++]=1;
		OutBuf[DataLen++]=ptst_AgreeOn_SetVidType_Par->Switch13;
	}
	else if(ID==13)
	{	OutBuf[DataLen++]=1;
		OutBuf[DataLen++]=ptst_AgreeOn_SetVidType_Par->Switch14;
	}
	else if(ID==14)
	{	OutBuf[DataLen++]=1;
		OutBuf[DataLen++]=ptst_AgreeOn_SetVidType_Par->Switch15;
	}
	else if(ID==15)
	{	OutBuf[DataLen++]=1;
		OutBuf[DataLen++]=ptst_AgreeOn_SetVidType_Par->Switch16;
	}
	else if(ID==16)
	{	OutBuf[DataLen++]=6;
		OutBuf[DataLen++]=(ptst_AgreeOn_SetVidType_Par->CN_Less_Switch1.Addree>>24);
		OutBuf[DataLen++]=(ptst_AgreeOn_SetVidType_Par->CN_Less_Switch1.Addree>>16);
		OutBuf[DataLen++]=(ptst_AgreeOn_SetVidType_Par->CN_Less_Switch1.Addree>>8);
		OutBuf[DataLen++]=(ptst_AgreeOn_SetVidType_Par->CN_Less_Switch1.Addree);
		OutBuf[DataLen++]=(ptst_AgreeOn_SetVidType_Par->CN_Less_Switch1.OpenOrClose);
		OutBuf[DataLen++]=(ptst_AgreeOn_SetVidType_Par->CN_Less_Switch1.State);
	}
	else if(ID==17)
	{	OutBuf[DataLen++]=6;
		OutBuf[DataLen++]=(ptst_AgreeOn_SetVidType_Par->CN_Less_Switch2.Addree>>24);
		OutBuf[DataLen++]=(ptst_AgreeOn_SetVidType_Par->CN_Less_Switch2.Addree>>16);
		OutBuf[DataLen++]=(ptst_AgreeOn_SetVidType_Par->CN_Less_Switch2.Addree>>8);
		OutBuf[DataLen++]=(ptst_AgreeOn_SetVidType_Par->CN_Less_Switch2.Addree);
		OutBuf[DataLen++]=(ptst_AgreeOn_SetVidType_Par->CN_Less_Switch2.OpenOrClose);
		OutBuf[DataLen++]=(ptst_AgreeOn_SetVidType_Par->CN_Less_Switch2.State);
	}
	else if(ID==18)
	{	OutBuf[DataLen++]=6;
		OutBuf[DataLen++]=(ptst_AgreeOn_SetVidType_Par->CN_Less_Switch3.Addree>>24);
		OutBuf[DataLen++]=(ptst_AgreeOn_SetVidType_Par->CN_Less_Switch3.Addree>>16);
		OutBuf[DataLen++]=(ptst_AgreeOn_SetVidType_Par->CN_Less_Switch3.Addree>>8);
		OutBuf[DataLen++]=(ptst_AgreeOn_SetVidType_Par->CN_Less_Switch3.Addree);
		OutBuf[DataLen++]=(ptst_AgreeOn_SetVidType_Par->CN_Less_Switch3.OpenOrClose);
		OutBuf[DataLen++]=(ptst_AgreeOn_SetVidType_Par->CN_Less_Switch3.State);
	}
	else if(ID==19)
	{	OutBuf[DataLen++]=6;
		OutBuf[DataLen++]=(ptst_AgreeOn_SetVidType_Par->CN_Less_Switch4.Addree>>24);
		OutBuf[DataLen++]=(ptst_AgreeOn_SetVidType_Par->CN_Less_Switch4.Addree>>16);
		OutBuf[DataLen++]=(ptst_AgreeOn_SetVidType_Par->CN_Less_Switch4.Addree>>8);
		OutBuf[DataLen++]=(ptst_AgreeOn_SetVidType_Par->CN_Less_Switch4.Addree);
		OutBuf[DataLen++]=(ptst_AgreeOn_SetVidType_Par->CN_Less_Switch4.OpenOrClose);
		OutBuf[DataLen++]=(ptst_AgreeOn_SetVidType_Par->CN_Less_Switch4.State);
	}
	else if(ID==20)
	{	OutBuf[DataLen++]=6;
		OutBuf[DataLen++]=(ptst_AgreeOn_SetVidType_Par->CN_Less_Switch5.Addree>>24);
		OutBuf[DataLen++]=(ptst_AgreeOn_SetVidType_Par->CN_Less_Switch5.Addree>>16);
		OutBuf[DataLen++]=(ptst_AgreeOn_SetVidType_Par->CN_Less_Switch5.Addree>>8);
		OutBuf[DataLen++]=(ptst_AgreeOn_SetVidType_Par->CN_Less_Switch5.Addree);
		OutBuf[DataLen++]=(ptst_AgreeOn_SetVidType_Par->CN_Less_Switch5.OpenOrClose);
		OutBuf[DataLen++]=(ptst_AgreeOn_SetVidType_Par->CN_Less_Switch5.State);
	}
	else if(ID==21)
	{	OutBuf[DataLen++]=6;
		OutBuf[DataLen++]=(ptst_AgreeOn_SetVidType_Par->CN_Less_Switch6.Addree>>24);
		OutBuf[DataLen++]=(ptst_AgreeOn_SetVidType_Par->CN_Less_Switch6.Addree>>16);
		OutBuf[DataLen++]=(ptst_AgreeOn_SetVidType_Par->CN_Less_Switch6.Addree>>8);
		OutBuf[DataLen++]=(ptst_AgreeOn_SetVidType_Par->CN_Less_Switch6.Addree);
		OutBuf[DataLen++]=(ptst_AgreeOn_SetVidType_Par->CN_Less_Switch6.OpenOrClose);
		OutBuf[DataLen++]=(ptst_AgreeOn_SetVidType_Par->CN_Less_Switch6.State);
	}
	else if(ID==22)
	{	OutBuf[DataLen++]=4;
		OutBuf[DataLen++]=(ptst_AgreeOn_SetVidType_Par->AccTimer>>24);
		OutBuf[DataLen++]=(ptst_AgreeOn_SetVidType_Par->AccTimer>>16);
		OutBuf[DataLen++]=(ptst_AgreeOn_SetVidType_Par->AccTimer>>8);
		OutBuf[DataLen++]=(ptst_AgreeOn_SetVidType_Par->AccTimer);
	}
	else if(ID==23)
	{	OutBuf[DataLen++]=4;
		OutBuf[DataLen++]=(ptst_AgreeOn_SetVidType_Par->Mileage>>24);
		OutBuf[DataLen++]=(ptst_AgreeOn_SetVidType_Par->Mileage>>16);
		OutBuf[DataLen++]=(ptst_AgreeOn_SetVidType_Par->Mileage>>8);
		OutBuf[DataLen++]=(ptst_AgreeOn_SetVidType_Par->Mileage);
	}
	else if(ID==24)
	{	OutBuf[DataLen++]=2;
		OutBuf[DataLen++]=(ptst_AgreeOn_SetVidType_Par->Oil1>>8);
		OutBuf[DataLen++]=(ptst_AgreeOn_SetVidType_Par->Oil1);
	}
	else if(ID==25)
	{	OutBuf[DataLen++]=1;
		OutBuf[DataLen++]=(ptst_AgreeOn_SetVidType_Par->Sem);
	}
	else if(ID==26)
	{	OutBuf[DataLen++]=4;
		OutBuf[DataLen++]=(ptst_AgreeOn_SetVidType_Par->SendOilTimer>>24);
		OutBuf[DataLen++]=(ptst_AgreeOn_SetVidType_Par->SendOilTimer>>16);
		OutBuf[DataLen++]=(ptst_AgreeOn_SetVidType_Par->SendOilTimer>>8);
		OutBuf[DataLen++]=(ptst_AgreeOn_SetVidType_Par->SendOilTimer);
	}
	else if(ID==27)
	{	OutBuf[DataLen++]=3;
	    OutBuf[DataLen++]=0x00;
		if(ptst_AgreeOn_SetVidType_Par->Temp>0x80000000)
		{	OutBuf[DataLen-1]=0x11;
			ptst_AgreeOn_SetVidType_Par->Temp=0xffffffff-ptst_AgreeOn_SetVidType_Par->Temp+1;
		}
		OutBuf[DataLen++]=ptst_AgreeOn_SetVidType_Par->Temp/100;
		OutBuf[DataLen++]=((ptst_AgreeOn_SetVidType_Par->Temp/10)%100);
	}
	else if(ID==28)
	{ 	OutBuf[DataLen++]=2;
		OutBuf[DataLen++]=(ptst_AgreeOn_SetVidType_Par->Oil2>>8);
		OutBuf[DataLen++]=(ptst_AgreeOn_SetVidType_Par->Oil2);
	}
	else if(ID==29)
	{ 	OutBuf[DataLen++]=4;
		OutBuf[DataLen++]=(ptst_AgreeOn_SetVidType_Par->Pulse>>24);
		OutBuf[DataLen++]=(ptst_AgreeOn_SetVidType_Par->Pulse>>16);
		OutBuf[DataLen++]=(ptst_AgreeOn_SetVidType_Par->Pulse>>8);
		OutBuf[DataLen++]=(ptst_AgreeOn_SetVidType_Par->Pulse);
	}
	else if(ID==30)
	{ 	OutBuf[DataLen++]=2;
		OutBuf[DataLen++]=(ptst_AgreeOn_SetVidType_Par->Humidity/1000);
		OutBuf[DataLen++]=((ptst_AgreeOn_SetVidType_Par->Humidity/10)%100);
	}
	else if(ID==31)
	{ 	OutBuf[DataLen++]=1;
		OutBuf[DataLen++]=(ptst_AgreeOn_SetVidType_Par->OilBaifen/10);
	}
	else if(ID==32)
	{	OutBuf[DataLen++]=8;	
		OutBuf[DataLen++]=(ptst_AgreeOn_SetVidType_Par->CN_st_AgreeOn_Less_Temp1.Addree>>24);
		OutBuf[DataLen++]=(ptst_AgreeOn_SetVidType_Par->CN_st_AgreeOn_Less_Temp1.Addree>>16);
		OutBuf[DataLen++]=(ptst_AgreeOn_SetVidType_Par->CN_st_AgreeOn_Less_Temp1.Addree>>8);
		OutBuf[DataLen++]=(ptst_AgreeOn_SetVidType_Par->CN_st_AgreeOn_Less_Temp1.Addree);
		OutBuf[DataLen++]=0x00;
		if(ptst_AgreeOn_SetVidType_Par->CN_st_AgreeOn_Less_Temp1.Temp>0x80000000)
		{	OutBuf[DataLen-1]=0x11;
			ptst_AgreeOn_SetVidType_Par->CN_st_AgreeOn_Less_Temp1.Temp=0xffffffff-ptst_AgreeOn_SetVidType_Par->CN_st_AgreeOn_Less_Temp1.Temp+1;
		}
	   	OutBuf[DataLen++]=ptst_AgreeOn_SetVidType_Par->CN_st_AgreeOn_Less_Temp1.Temp/100;
		OutBuf[DataLen++]=((ptst_AgreeOn_SetVidType_Par->CN_st_AgreeOn_Less_Temp1.Temp/10)%100);
		OutBuf[DataLen++]=ptst_AgreeOn_SetVidType_Par->CN_st_AgreeOn_Less_Temp1.State;
	}
	else if(ID==33)
	{	OutBuf[DataLen++]=8;	
		OutBuf[DataLen++]=(ptst_AgreeOn_SetVidType_Par->CN_st_AgreeOn_Less_Temp2.Addree>>24);
		OutBuf[DataLen++]=(ptst_AgreeOn_SetVidType_Par->CN_st_AgreeOn_Less_Temp2.Addree>>16);
		OutBuf[DataLen++]=(ptst_AgreeOn_SetVidType_Par->CN_st_AgreeOn_Less_Temp2.Addree>>8);
		OutBuf[DataLen++]=(ptst_AgreeOn_SetVidType_Par->CN_st_AgreeOn_Less_Temp2.Addree);
		OutBuf[DataLen++]=0x00;
		if(ptst_AgreeOn_SetVidType_Par->CN_st_AgreeOn_Less_Temp2.Temp>0x80000000)
		{	OutBuf[DataLen-1]=0x11;
			ptst_AgreeOn_SetVidType_Par->CN_st_AgreeOn_Less_Temp2.Temp=0xffffffff-ptst_AgreeOn_SetVidType_Par->CN_st_AgreeOn_Less_Temp2.Temp+1;
		}
	   	OutBuf[DataLen++]=ptst_AgreeOn_SetVidType_Par->CN_st_AgreeOn_Less_Temp2.Temp/100;
		OutBuf[DataLen++]=((ptst_AgreeOn_SetVidType_Par->CN_st_AgreeOn_Less_Temp2.Temp/10)%100);
		OutBuf[DataLen++]=ptst_AgreeOn_SetVidType_Par->CN_st_AgreeOn_Less_Temp2.State;
	}
	else if(ID==34)
	{	OutBuf[DataLen++]=8;	
		OutBuf[DataLen++]=(ptst_AgreeOn_SetVidType_Par->CN_st_AgreeOn_Less_Temp3.Addree>>24);
		OutBuf[DataLen++]=(ptst_AgreeOn_SetVidType_Par->CN_st_AgreeOn_Less_Temp3.Addree>>16);
		OutBuf[DataLen++]=(ptst_AgreeOn_SetVidType_Par->CN_st_AgreeOn_Less_Temp3.Addree>>8);
		OutBuf[DataLen++]=(ptst_AgreeOn_SetVidType_Par->CN_st_AgreeOn_Less_Temp3.Addree);
		OutBuf[DataLen++]=0x00;
		if(ptst_AgreeOn_SetVidType_Par->CN_st_AgreeOn_Less_Temp3.Temp>0x80000000)
		{	OutBuf[DataLen-1]=0x11;
			ptst_AgreeOn_SetVidType_Par->CN_st_AgreeOn_Less_Temp3.Temp=0xffffffff-ptst_AgreeOn_SetVidType_Par->CN_st_AgreeOn_Less_Temp3.Temp+1;
		}
	   	OutBuf[DataLen++]=ptst_AgreeOn_SetVidType_Par->CN_st_AgreeOn_Less_Temp3.Temp/100;
		OutBuf[DataLen++]=((ptst_AgreeOn_SetVidType_Par->CN_st_AgreeOn_Less_Temp3.Temp/10)%100);
		OutBuf[DataLen++]=ptst_AgreeOn_SetVidType_Par->CN_st_AgreeOn_Less_Temp3.State;
	}
	else if(ID==35)
	{	OutBuf[DataLen++]=8;	
		OutBuf[DataLen++]=(ptst_AgreeOn_SetVidType_Par->CN_st_AgreeOn_Less_Temp4.Addree>>24);
		OutBuf[DataLen++]=(ptst_AgreeOn_SetVidType_Par->CN_st_AgreeOn_Less_Temp4.Addree>>16);
		OutBuf[DataLen++]=(ptst_AgreeOn_SetVidType_Par->CN_st_AgreeOn_Less_Temp4.Addree>>8);
		OutBuf[DataLen++]=(ptst_AgreeOn_SetVidType_Par->CN_st_AgreeOn_Less_Temp4.Addree);
		OutBuf[DataLen++]=0x00;
		if(ptst_AgreeOn_SetVidType_Par->CN_st_AgreeOn_Less_Temp4.Temp>0x80000000)
		{	OutBuf[DataLen-1]=0x11;
			ptst_AgreeOn_SetVidType_Par->CN_st_AgreeOn_Less_Temp4.Temp=0xffffffff-ptst_AgreeOn_SetVidType_Par->CN_st_AgreeOn_Less_Temp4.Temp+1;
		}
	   	OutBuf[DataLen++]=ptst_AgreeOn_SetVidType_Par->CN_st_AgreeOn_Less_Temp4.Temp/100;
		OutBuf[DataLen++]=((ptst_AgreeOn_SetVidType_Par->CN_st_AgreeOn_Less_Temp4.Temp/10)%100);
		OutBuf[DataLen++]=ptst_AgreeOn_SetVidType_Par->CN_st_AgreeOn_Less_Temp4.State;
	}
	*ReDataLen=DataLen;
}


static void Explain_WorkPar2(st_AgreeOn_SetVidType  *ptst_AgreeOn_SetVidType,uint8 *OutBuf,uint16 *ReDataLen,uint8 ID,uint8 type)
{	uint16 DataLen;
	DataLen=0;
	if(ID==0)
	{	OutBuf[DataLen++]=1;
		OutBuf[DataLen++]=ptst_AgreeOn_SetVidType->CN_st_AgreeOn_SetVidType_Par[0].Switch1;
	    if(type==De_AgreeOn_SetVidType_Type_NumberCut)
	    { OutBuf[DataLen-2]=2;
	      OutBuf[DataLen-1]=ptst_AgreeOn_SetVidType->CN_st_AgreeOn_SetVidType_Par[0].Switch1;
	      OutBuf[DataLen++]=ptst_AgreeOn_SetVidType->CN_st_AgreeOn_SetVidType_Par[1].Switch1;
	    }				
	}
	else if(ID==1)
	{	OutBuf[DataLen++]=1;
		OutBuf[DataLen++]=ptst_AgreeOn_SetVidType->CN_st_AgreeOn_SetVidType_Par[0].Switch1;
	    if(type==De_AgreeOn_SetVidType_Type_NumberCut)
	    { OutBuf[DataLen-2]=2;
	      OutBuf[DataLen-1]=ptst_AgreeOn_SetVidType->CN_st_AgreeOn_SetVidType_Par[0].Switch1;
	      OutBuf[DataLen++]=ptst_AgreeOn_SetVidType->CN_st_AgreeOn_SetVidType_Par[1].Switch1;
	    }		
	}
	else if(ID==2)
	{	OutBuf[DataLen++]=1;
		OutBuf[DataLen++]=ptst_AgreeOn_SetVidType->CN_st_AgreeOn_SetVidType_Par[0].Switch1;
	    if(type==De_AgreeOn_SetVidType_Type_NumberCut)
	    { OutBuf[DataLen-2]=2;
	      OutBuf[DataLen-1]=ptst_AgreeOn_SetVidType->CN_st_AgreeOn_SetVidType_Par[0].Switch1;
	      OutBuf[DataLen++]=ptst_AgreeOn_SetVidType->CN_st_AgreeOn_SetVidType_Par[1].Switch1;
	    }		
	}
	else if(ID==3)
	{	OutBuf[DataLen++]=1;
		OutBuf[DataLen++]=ptst_AgreeOn_SetVidType->CN_st_AgreeOn_SetVidType_Par[0].Switch1;
	    if(type==De_AgreeOn_SetVidType_Type_NumberCut)
	    { OutBuf[DataLen-2]=2;
	      OutBuf[DataLen-1]=ptst_AgreeOn_SetVidType->CN_st_AgreeOn_SetVidType_Par[0].Switch1;
	      OutBuf[DataLen++]=ptst_AgreeOn_SetVidType->CN_st_AgreeOn_SetVidType_Par[1].Switch1;
	    }		
	}
	else if(ID==4)
	{	OutBuf[DataLen++]=1;
		OutBuf[DataLen++]=ptst_AgreeOn_SetVidType->CN_st_AgreeOn_SetVidType_Par[0].Switch1;
	    if(type==De_AgreeOn_SetVidType_Type_NumberCut)
	    { OutBuf[DataLen-2]=2;
	      OutBuf[DataLen-1]=ptst_AgreeOn_SetVidType->CN_st_AgreeOn_SetVidType_Par[0].Switch1;
	      OutBuf[DataLen++]=ptst_AgreeOn_SetVidType->CN_st_AgreeOn_SetVidType_Par[1].Switch1;
	    }		
	}
	else if(ID==5)
	{	OutBuf[DataLen++]=1;
		OutBuf[DataLen++]=ptst_AgreeOn_SetVidType->CN_st_AgreeOn_SetVidType_Par[0].Switch1;
	    if(type==De_AgreeOn_SetVidType_Type_NumberCut)
	    { OutBuf[DataLen-2]=2;
	      OutBuf[DataLen-1]=ptst_AgreeOn_SetVidType->CN_st_AgreeOn_SetVidType_Par[0].Switch1;
	      OutBuf[DataLen++]=ptst_AgreeOn_SetVidType->CN_st_AgreeOn_SetVidType_Par[1].Switch1;
	    }		
	}
	else if(ID==6)
	{	OutBuf[DataLen++]=1;
		OutBuf[DataLen++]=ptst_AgreeOn_SetVidType->CN_st_AgreeOn_SetVidType_Par[0].Switch1;
	    if(type==De_AgreeOn_SetVidType_Type_NumberCut)
	    { OutBuf[DataLen-2]=2;
	      OutBuf[DataLen-1]=ptst_AgreeOn_SetVidType->CN_st_AgreeOn_SetVidType_Par[0].Switch1;
	      OutBuf[DataLen++]=ptst_AgreeOn_SetVidType->CN_st_AgreeOn_SetVidType_Par[1].Switch1;
	    }		
	}
	else if(ID==7)
	{	OutBuf[DataLen++]=1;
		OutBuf[DataLen++]=ptst_AgreeOn_SetVidType->CN_st_AgreeOn_SetVidType_Par[0].Switch1;
	    if(type==De_AgreeOn_SetVidType_Type_NumberCut)
	    { OutBuf[DataLen-2]=2;
	      OutBuf[DataLen-1]=ptst_AgreeOn_SetVidType->CN_st_AgreeOn_SetVidType_Par[0].Switch1;
	      OutBuf[DataLen++]=ptst_AgreeOn_SetVidType->CN_st_AgreeOn_SetVidType_Par[1].Switch1;
	    }		
	}
	else if(ID==8)
	{	OutBuf[DataLen++]=1;
		OutBuf[DataLen++]=ptst_AgreeOn_SetVidType->CN_st_AgreeOn_SetVidType_Par[0].Switch1;
	    if(type==De_AgreeOn_SetVidType_Type_NumberCut)
	    { OutBuf[DataLen-2]=2;
	      OutBuf[DataLen-1]=ptst_AgreeOn_SetVidType->CN_st_AgreeOn_SetVidType_Par[0].Switch1;
	      OutBuf[DataLen++]=ptst_AgreeOn_SetVidType->CN_st_AgreeOn_SetVidType_Par[1].Switch1;
	    }		
	}
	else if(ID==9)
	{	OutBuf[DataLen++]=1;
		OutBuf[DataLen++]=ptst_AgreeOn_SetVidType->CN_st_AgreeOn_SetVidType_Par[0].Switch1;
	    if(type==De_AgreeOn_SetVidType_Type_NumberCut)
	    { OutBuf[DataLen-2]=2;
	      OutBuf[DataLen-1]=ptst_AgreeOn_SetVidType->CN_st_AgreeOn_SetVidType_Par[0].Switch1;
	      OutBuf[DataLen++]=ptst_AgreeOn_SetVidType->CN_st_AgreeOn_SetVidType_Par[1].Switch1;
	    }		
	}
	
	else if(ID==10)
	{	OutBuf[DataLen++]=1;
		OutBuf[DataLen++]=ptst_AgreeOn_SetVidType->CN_st_AgreeOn_SetVidType_Par[0].Switch1;
	    if(type==De_AgreeOn_SetVidType_Type_NumberCut)
	    { OutBuf[DataLen-2]=2;
	      OutBuf[DataLen-1]=ptst_AgreeOn_SetVidType->CN_st_AgreeOn_SetVidType_Par[0].Switch1;
	      OutBuf[DataLen++]=ptst_AgreeOn_SetVidType->CN_st_AgreeOn_SetVidType_Par[1].Switch1;
	    }		
	}
	else if(ID==11)
	{	OutBuf[DataLen++]=1;
		OutBuf[DataLen++]=ptst_AgreeOn_SetVidType->CN_st_AgreeOn_SetVidType_Par[0].Switch1;
	    if(type==De_AgreeOn_SetVidType_Type_NumberCut)
	    { OutBuf[DataLen-2]=2;
	      OutBuf[DataLen-1]=ptst_AgreeOn_SetVidType->CN_st_AgreeOn_SetVidType_Par[0].Switch1;
	      OutBuf[DataLen++]=ptst_AgreeOn_SetVidType->CN_st_AgreeOn_SetVidType_Par[1].Switch1;
	    }		
	}
	else if(ID==12)
	{	OutBuf[DataLen++]=1;
		OutBuf[DataLen++]=ptst_AgreeOn_SetVidType->CN_st_AgreeOn_SetVidType_Par[0].Switch1;
	    if(type==De_AgreeOn_SetVidType_Type_NumberCut)
	    { OutBuf[DataLen-2]=2;
	      OutBuf[DataLen-1]=ptst_AgreeOn_SetVidType->CN_st_AgreeOn_SetVidType_Par[0].Switch1;
	      OutBuf[DataLen++]=ptst_AgreeOn_SetVidType->CN_st_AgreeOn_SetVidType_Par[1].Switch1;
	    }		
	}
	else if(ID==13)
	{	OutBuf[DataLen++]=1;
		OutBuf[DataLen++]=ptst_AgreeOn_SetVidType->CN_st_AgreeOn_SetVidType_Par[0].Switch1;
	    if(type==De_AgreeOn_SetVidType_Type_NumberCut)
	    { OutBuf[DataLen-2]=2;
	      OutBuf[DataLen-1]=ptst_AgreeOn_SetVidType->CN_st_AgreeOn_SetVidType_Par[0].Switch1;
	      OutBuf[DataLen++]=ptst_AgreeOn_SetVidType->CN_st_AgreeOn_SetVidType_Par[1].Switch1;
	    }		
	}
	else if(ID==14)
	{	OutBuf[DataLen++]=1;
		OutBuf[DataLen++]=ptst_AgreeOn_SetVidType->CN_st_AgreeOn_SetVidType_Par[0].Switch1;
	    if(type==De_AgreeOn_SetVidType_Type_NumberCut)
	    { OutBuf[DataLen-2]=2;
	      OutBuf[DataLen-1]=ptst_AgreeOn_SetVidType->CN_st_AgreeOn_SetVidType_Par[0].Switch1;
	      OutBuf[DataLen++]=ptst_AgreeOn_SetVidType->CN_st_AgreeOn_SetVidType_Par[1].Switch1;
	    }		
	}
	else if(ID==15)
	{	OutBuf[DataLen++]=1;
		OutBuf[DataLen++]=ptst_AgreeOn_SetVidType->CN_st_AgreeOn_SetVidType_Par[0].Switch1;
	    if(type==De_AgreeOn_SetVidType_Type_NumberCut)
	    { OutBuf[DataLen-2]=2;
	      OutBuf[DataLen-1]=ptst_AgreeOn_SetVidType->CN_st_AgreeOn_SetVidType_Par[0].Switch1;
	      OutBuf[DataLen++]=ptst_AgreeOn_SetVidType->CN_st_AgreeOn_SetVidType_Par[1].Switch1;
	    }		
	}
	else if(ID==16)
	{    OutBuf[DataLen++]=1;		
	     OutBuf[DataLen++]=ptst_AgreeOn_SetVidType->CN_st_AgreeOn_SetVidType_Par[0].CN_Less_Switch1.OpenOrClose;
	     if(type==De_AgreeOn_SetVidType_Type_NumberCut)
	       {   OutBuf[DataLen-2]=2;
		       OutBuf[DataLen-1]=ptst_AgreeOn_SetVidType->CN_st_AgreeOn_SetVidType_Par[0].CN_Less_Switch1.OpenOrClose;
	           OutBuf[DataLen++]=ptst_AgreeOn_SetVidType->CN_st_AgreeOn_SetVidType_Par[1].CN_Less_Switch1.OpenOrClose;	
	        }	
	}
	else if(ID==17)
	{    OutBuf[DataLen++]=1;		
	     OutBuf[DataLen++]=ptst_AgreeOn_SetVidType->CN_st_AgreeOn_SetVidType_Par[0].CN_Less_Switch2.OpenOrClose;
	     if(type==De_AgreeOn_SetVidType_Type_NumberCut)
	     {   OutBuf[DataLen-2]=2;
		     OutBuf[DataLen-1]=ptst_AgreeOn_SetVidType->CN_st_AgreeOn_SetVidType_Par[0].CN_Less_Switch2.OpenOrClose;
	         OutBuf[DataLen++]=ptst_AgreeOn_SetVidType->CN_st_AgreeOn_SetVidType_Par[1].CN_Less_Switch2.OpenOrClose;	
	     }	
	}
	else if(ID==18)
	{    OutBuf[DataLen++]=1;		
	     OutBuf[DataLen++]=ptst_AgreeOn_SetVidType->CN_st_AgreeOn_SetVidType_Par[0].CN_Less_Switch3.OpenOrClose;
	     if(type==De_AgreeOn_SetVidType_Type_NumberCut)
	     {   OutBuf[DataLen-2]=2;
		     OutBuf[DataLen-1]=ptst_AgreeOn_SetVidType->CN_st_AgreeOn_SetVidType_Par[0].CN_Less_Switch3.OpenOrClose;
	         OutBuf[DataLen++]=ptst_AgreeOn_SetVidType->CN_st_AgreeOn_SetVidType_Par[1].CN_Less_Switch3.OpenOrClose;	
	     }	
	}
	else if(ID==19)
	{    OutBuf[DataLen++]=1;		
	     OutBuf[DataLen++]=ptst_AgreeOn_SetVidType->CN_st_AgreeOn_SetVidType_Par[0].CN_Less_Switch4.OpenOrClose;
	     if(type==De_AgreeOn_SetVidType_Type_NumberCut)
	     {   OutBuf[DataLen-2]=2;
		     OutBuf[DataLen-1]=ptst_AgreeOn_SetVidType->CN_st_AgreeOn_SetVidType_Par[0].CN_Less_Switch4.OpenOrClose;
	         OutBuf[DataLen++]=ptst_AgreeOn_SetVidType->CN_st_AgreeOn_SetVidType_Par[1].CN_Less_Switch4.OpenOrClose;	
	     }	
	}
	else if(ID==20)
	{    OutBuf[DataLen++]=1;		
	     OutBuf[DataLen++]=ptst_AgreeOn_SetVidType->CN_st_AgreeOn_SetVidType_Par[0].CN_Less_Switch5.OpenOrClose;
	     if(type==De_AgreeOn_SetVidType_Type_NumberCut)
		 {   OutBuf[DataLen-2]=2;
		     OutBuf[DataLen-1]=ptst_AgreeOn_SetVidType->CN_st_AgreeOn_SetVidType_Par[0].CN_Less_Switch5.OpenOrClose;
		     OutBuf[DataLen++]=ptst_AgreeOn_SetVidType->CN_st_AgreeOn_SetVidType_Par[1].CN_Less_Switch5.OpenOrClose;	
		 }	
	}
	else if(ID==21)
	{    OutBuf[DataLen++]=1;		
	     OutBuf[DataLen++]=ptst_AgreeOn_SetVidType->CN_st_AgreeOn_SetVidType_Par[0].CN_Less_Switch6.OpenOrClose;
	     if(type==De_AgreeOn_SetVidType_Type_NumberCut)
	     {   OutBuf[DataLen-2]=2;
		     OutBuf[DataLen-1]=ptst_AgreeOn_SetVidType->CN_st_AgreeOn_SetVidType_Par[0].CN_Less_Switch6.OpenOrClose;
	         OutBuf[DataLen++]=ptst_AgreeOn_SetVidType->CN_st_AgreeOn_SetVidType_Par[1].CN_Less_Switch6.OpenOrClose;	
	     }	
	}
	else if(ID==22)
	{	OutBuf[DataLen++]=4;
	    OutBuf[DataLen++]=(ptst_AgreeOn_SetVidType->CN_st_AgreeOn_SetVidType_Par[0].AccTimer>>24);
		OutBuf[DataLen++]=(ptst_AgreeOn_SetVidType->CN_st_AgreeOn_SetVidType_Par[0].AccTimer>>16);
		OutBuf[DataLen++]=(ptst_AgreeOn_SetVidType->CN_st_AgreeOn_SetVidType_Par[0].AccTimer>>8);
		OutBuf[DataLen++]=(ptst_AgreeOn_SetVidType->CN_st_AgreeOn_SetVidType_Par[0].AccTimer);
		 if(type==De_AgreeOn_SetVidType_Type_NumberCut)
	     {  OutBuf[DataLen-5]=8;
		    OutBuf[DataLen-4]=(ptst_AgreeOn_SetVidType->CN_st_AgreeOn_SetVidType_Par[0].AccTimer>>24);
			OutBuf[DataLen-3]=(ptst_AgreeOn_SetVidType->CN_st_AgreeOn_SetVidType_Par[0].AccTimer>>16);
			OutBuf[DataLen-2]=(ptst_AgreeOn_SetVidType->CN_st_AgreeOn_SetVidType_Par[0].AccTimer>>8);
			OutBuf[DataLen-1]=(ptst_AgreeOn_SetVidType->CN_st_AgreeOn_SetVidType_Par[0].AccTimer);
			OutBuf[DataLen++]=(ptst_AgreeOn_SetVidType->CN_st_AgreeOn_SetVidType_Par[1].AccTimer>>24);
			OutBuf[DataLen++]=(ptst_AgreeOn_SetVidType->CN_st_AgreeOn_SetVidType_Par[1].AccTimer>>16);
			OutBuf[DataLen++]=(ptst_AgreeOn_SetVidType->CN_st_AgreeOn_SetVidType_Par[1].AccTimer>>8);
			OutBuf[DataLen++]=(ptst_AgreeOn_SetVidType->CN_st_AgreeOn_SetVidType_Par[1].AccTimer);
	     }	
	}
	else if(ID==23)
	{	OutBuf[DataLen++]=4;
		OutBuf[DataLen++]=( ptst_AgreeOn_SetVidType->CN_st_AgreeOn_SetVidType_Par[0].Mileage>>24);
		OutBuf[DataLen++]=( ptst_AgreeOn_SetVidType->CN_st_AgreeOn_SetVidType_Par[0].Mileage>>16);
		OutBuf[DataLen++]=( ptst_AgreeOn_SetVidType->CN_st_AgreeOn_SetVidType_Par[0].Mileage>>8);
		OutBuf[DataLen++]=( ptst_AgreeOn_SetVidType->CN_st_AgreeOn_SetVidType_Par[0].Mileage);
		 if(type==De_AgreeOn_SetVidType_Type_NumberCut)
	     {  OutBuf[DataLen-5]=8;
		    OutBuf[DataLen-4]=( ptst_AgreeOn_SetVidType->CN_st_AgreeOn_SetVidType_Par[0].Mileage>>24);
		    OutBuf[DataLen-3]=( ptst_AgreeOn_SetVidType->CN_st_AgreeOn_SetVidType_Par[0].Mileage>>16);
		    OutBuf[DataLen-2]=( ptst_AgreeOn_SetVidType->CN_st_AgreeOn_SetVidType_Par[0].Mileage>>8);
		    OutBuf[DataLen-1]=( ptst_AgreeOn_SetVidType->CN_st_AgreeOn_SetVidType_Par[0].Mileage);
		    OutBuf[DataLen++]=( ptst_AgreeOn_SetVidType->CN_st_AgreeOn_SetVidType_Par[1].Mileage>>24);
		    OutBuf[DataLen++]=( ptst_AgreeOn_SetVidType->CN_st_AgreeOn_SetVidType_Par[1].Mileage>>16);
		    OutBuf[DataLen++]=( ptst_AgreeOn_SetVidType->CN_st_AgreeOn_SetVidType_Par[1].Mileage>>8);
	    	OutBuf[DataLen++]=( ptst_AgreeOn_SetVidType->CN_st_AgreeOn_SetVidType_Par[1].Mileage);
	     }	
	}
	else if(ID==24)
	{	OutBuf[DataLen++]=2;
		OutBuf[DataLen++]=(ptst_AgreeOn_SetVidType->CN_st_AgreeOn_SetVidType_Par[0].Oil1>>8);
		OutBuf[DataLen++]=(ptst_AgreeOn_SetVidType->CN_st_AgreeOn_SetVidType_Par[0].Oil1);
		if(type==De_AgreeOn_SetVidType_Type_NumberCut)
		{ OutBuf[DataLen-3]=4;
		  OutBuf[DataLen-2]=(ptst_AgreeOn_SetVidType->CN_st_AgreeOn_SetVidType_Par[0].Oil1>>8);
		  OutBuf[DataLen-1]=(ptst_AgreeOn_SetVidType->CN_st_AgreeOn_SetVidType_Par[0].Oil1);
		  OutBuf[DataLen++]=(ptst_AgreeOn_SetVidType->CN_st_AgreeOn_SetVidType_Par[1].Oil1>>8);
		  OutBuf[DataLen++]=(ptst_AgreeOn_SetVidType->CN_st_AgreeOn_SetVidType_Par[1].Oil1);
		}

	}
	else if(ID==25)
	{	OutBuf[DataLen++]=1;
		OutBuf[DataLen++]=(ptst_AgreeOn_SetVidType->CN_st_AgreeOn_SetVidType_Par[0].Sem);
	  	if(type==De_AgreeOn_SetVidType_Type_NumberCut)
		{ OutBuf[DataLen-2]=2;
		  OutBuf[DataLen-1]=(ptst_AgreeOn_SetVidType->CN_st_AgreeOn_SetVidType_Par[0].Sem);
		  OutBuf[DataLen++]=(ptst_AgreeOn_SetVidType->CN_st_AgreeOn_SetVidType_Par[1].Sem);
		}
	}
	else if(ID==26)
	{	OutBuf[DataLen++]=4;
		OutBuf[DataLen++]=(ptst_AgreeOn_SetVidType->CN_st_AgreeOn_SetVidType_Par[0].SendOilTimer>>24);
		OutBuf[DataLen++]=(ptst_AgreeOn_SetVidType->CN_st_AgreeOn_SetVidType_Par[0].SendOilTimer>>16);
		OutBuf[DataLen++]=(ptst_AgreeOn_SetVidType->CN_st_AgreeOn_SetVidType_Par[0].SendOilTimer>>8);
		OutBuf[DataLen++]=(ptst_AgreeOn_SetVidType->CN_st_AgreeOn_SetVidType_Par[0].SendOilTimer);
		if(type==De_AgreeOn_SetVidType_Type_NumberCut)
		{   OutBuf[DataLen-5]=8;
		    OutBuf[DataLen-4]=(ptst_AgreeOn_SetVidType->CN_st_AgreeOn_SetVidType_Par[0].SendOilTimer>>24);
			OutBuf[DataLen-3]=(ptst_AgreeOn_SetVidType->CN_st_AgreeOn_SetVidType_Par[0].SendOilTimer>>16);
			OutBuf[DataLen-2]=(ptst_AgreeOn_SetVidType->CN_st_AgreeOn_SetVidType_Par[0].SendOilTimer>>8);
			OutBuf[DataLen-1]=(ptst_AgreeOn_SetVidType->CN_st_AgreeOn_SetVidType_Par[0].SendOilTimer);
			OutBuf[DataLen++]=(ptst_AgreeOn_SetVidType->CN_st_AgreeOn_SetVidType_Par[1].SendOilTimer>>24);
			OutBuf[DataLen++]=(ptst_AgreeOn_SetVidType->CN_st_AgreeOn_SetVidType_Par[1].SendOilTimer>>16);
			OutBuf[DataLen++]=(ptst_AgreeOn_SetVidType->CN_st_AgreeOn_SetVidType_Par[1].SendOilTimer>>8);
			OutBuf[DataLen++]=(ptst_AgreeOn_SetVidType->CN_st_AgreeOn_SetVidType_Par[1].SendOilTimer);
		}
	}
	else if(ID==27)
	{	OutBuf[DataLen++]=3;
	    OutBuf[DataLen++]=0x00;
		if(ptst_AgreeOn_SetVidType->CN_st_AgreeOn_SetVidType_Par[0].Temp>0x80000000)
		{	OutBuf[DataLen-1]=0x11;
			ptst_AgreeOn_SetVidType->CN_st_AgreeOn_SetVidType_Par[0].Temp=0xffffffff-ptst_AgreeOn_SetVidType->CN_st_AgreeOn_SetVidType_Par[0].Temp+1;
		}
		OutBuf[DataLen++]=ptst_AgreeOn_SetVidType->CN_st_AgreeOn_SetVidType_Par[0].Temp/100;
		OutBuf[DataLen++]=((ptst_AgreeOn_SetVidType->CN_st_AgreeOn_SetVidType_Par[0].Temp/10)%100);
		if(type==De_AgreeOn_SetVidType_Type_NumberCut)
		{ OutBuf[DataLen-4]=6;
		  OutBuf[DataLen-3]=0x00;
		  if(ptst_AgreeOn_SetVidType->CN_st_AgreeOn_SetVidType_Par[0].Temp>0x80000000)
	      {  OutBuf[DataLen-3]=0x11;
			 ptst_AgreeOn_SetVidType->CN_st_AgreeOn_SetVidType_Par[0].Temp=0xffffffff-ptst_AgreeOn_SetVidType->CN_st_AgreeOn_SetVidType_Par[0].Temp+1;
		  }
		  OutBuf[DataLen-2]=ptst_AgreeOn_SetVidType->CN_st_AgreeOn_SetVidType_Par[0].Temp/100;
		  OutBuf[DataLen-1]=((ptst_AgreeOn_SetVidType->CN_st_AgreeOn_SetVidType_Par[0].Temp/10)%100);
		  OutBuf[DataLen++]=0x00;
		  if(ptst_AgreeOn_SetVidType->CN_st_AgreeOn_SetVidType_Par[1].Temp>0x80000000)
	      {  OutBuf[DataLen-1]=0x11;
			 ptst_AgreeOn_SetVidType->CN_st_AgreeOn_SetVidType_Par[1].Temp=0xffffffff-ptst_AgreeOn_SetVidType->CN_st_AgreeOn_SetVidType_Par[0].Temp+1;
		  }
	      OutBuf[DataLen++]=ptst_AgreeOn_SetVidType->CN_st_AgreeOn_SetVidType_Par[1].Temp/100;
		  OutBuf[DataLen++]=((ptst_AgreeOn_SetVidType->CN_st_AgreeOn_SetVidType_Par[1].Temp/10)%100);		
	   }
	}
	else if(ID==28)
	{ 	OutBuf[DataLen++]=2;
		OutBuf[DataLen++]=(ptst_AgreeOn_SetVidType->CN_st_AgreeOn_SetVidType_Par[0].Oil2>>8);
		OutBuf[DataLen++]=(ptst_AgreeOn_SetVidType->CN_st_AgreeOn_SetVidType_Par[0].Oil2);
		if(type==De_AgreeOn_SetVidType_Type_NumberCut)
		{  OutBuf[DataLen-3]=4;
		   OutBuf[DataLen-2]=(ptst_AgreeOn_SetVidType->CN_st_AgreeOn_SetVidType_Par[0].Oil2>>8);
		   OutBuf[DataLen-1]=(ptst_AgreeOn_SetVidType->CN_st_AgreeOn_SetVidType_Par[0].Oil2);
     	   OutBuf[DataLen++]=(ptst_AgreeOn_SetVidType->CN_st_AgreeOn_SetVidType_Par[1].Oil2>>8);
		   OutBuf[DataLen++]=(ptst_AgreeOn_SetVidType->CN_st_AgreeOn_SetVidType_Par[1].Oil2);
		}

	}
	else if(ID==29)
	{ 	OutBuf[DataLen++]=4;
		OutBuf[DataLen++]=(ptst_AgreeOn_SetVidType->CN_st_AgreeOn_SetVidType_Par[0].Pulse>>24);
		OutBuf[DataLen++]=(ptst_AgreeOn_SetVidType->CN_st_AgreeOn_SetVidType_Par[0].Pulse>>16);
		OutBuf[DataLen++]=(ptst_AgreeOn_SetVidType->CN_st_AgreeOn_SetVidType_Par[0].Pulse>>8);
		OutBuf[DataLen++]=(ptst_AgreeOn_SetVidType->CN_st_AgreeOn_SetVidType_Par[0].Pulse);
		if(type==De_AgreeOn_SetVidType_Type_NumberCut)
		{  OutBuf[DataLen-5]=8;
		   OutBuf[DataLen-4]=(ptst_AgreeOn_SetVidType->CN_st_AgreeOn_SetVidType_Par[0].Pulse>>24);
		   OutBuf[DataLen-3]=(ptst_AgreeOn_SetVidType->CN_st_AgreeOn_SetVidType_Par[0].Pulse>>16);
		   OutBuf[DataLen-2]=(ptst_AgreeOn_SetVidType->CN_st_AgreeOn_SetVidType_Par[0].Pulse>>8);
		   OutBuf[DataLen-1]=(ptst_AgreeOn_SetVidType->CN_st_AgreeOn_SetVidType_Par[0].Pulse);
		   OutBuf[DataLen++]=(ptst_AgreeOn_SetVidType->CN_st_AgreeOn_SetVidType_Par[1].Pulse>>24);
		   OutBuf[DataLen++]=(ptst_AgreeOn_SetVidType->CN_st_AgreeOn_SetVidType_Par[1].Pulse>>16);
     	   OutBuf[DataLen++]=(ptst_AgreeOn_SetVidType->CN_st_AgreeOn_SetVidType_Par[1].Pulse>>8);
		   OutBuf[DataLen++]=(ptst_AgreeOn_SetVidType->CN_st_AgreeOn_SetVidType_Par[1].Pulse);
		}
	}
	else if(ID==30)
	{ 	OutBuf[DataLen++]=2;
		OutBuf[DataLen++]=(ptst_AgreeOn_SetVidType->CN_st_AgreeOn_SetVidType_Par[0].Humidity/1000);
		OutBuf[DataLen++]=((ptst_AgreeOn_SetVidType->CN_st_AgreeOn_SetVidType_Par[0].Humidity/10)%100);
		if(type==De_AgreeOn_SetVidType_Type_NumberCut)
		{  OutBuf[DataLen-3]=4;
	       OutBuf[DataLen-2]=(ptst_AgreeOn_SetVidType->CN_st_AgreeOn_SetVidType_Par[0].Humidity/1000);
		   OutBuf[DataLen-1]=((ptst_AgreeOn_SetVidType->CN_st_AgreeOn_SetVidType_Par[0].Humidity/10)%100);
		   OutBuf[DataLen++]=(ptst_AgreeOn_SetVidType->CN_st_AgreeOn_SetVidType_Par[1].Humidity/1000);
		   OutBuf[DataLen++]=((ptst_AgreeOn_SetVidType->CN_st_AgreeOn_SetVidType_Par[1].Humidity/10)%100);
     	  
		}
	}
	else if(ID==31)
	{ 	OutBuf[DataLen++]=1;
		OutBuf[DataLen++]=(ptst_AgreeOn_SetVidType->CN_st_AgreeOn_SetVidType_Par[1].OilBaifen/10);
		if(type==De_AgreeOn_SetVidType_Type_NumberCut)
		{  OutBuf[DataLen-2]=2;
	       OutBuf[DataLen-1]=(ptst_AgreeOn_SetVidType->CN_st_AgreeOn_SetVidType_Par[0].OilBaifen/10);
		   OutBuf[DataLen++]=(ptst_AgreeOn_SetVidType->CN_st_AgreeOn_SetVidType_Par[1].OilBaifen/10);
		}

	}
	else if(ID==32)
	{	OutBuf[DataLen++]=3;
	    OutBuf[DataLen++]=0x00;
		if(ptst_AgreeOn_SetVidType->CN_st_AgreeOn_SetVidType_Par[0].CN_st_AgreeOn_Less_Temp1.Temp>0x80000000)
		{	OutBuf[DataLen-1]=0x11;
			ptst_AgreeOn_SetVidType->CN_st_AgreeOn_SetVidType_Par[0].CN_st_AgreeOn_Less_Temp1.Temp=0xffffffff-ptst_AgreeOn_SetVidType->CN_st_AgreeOn_SetVidType_Par[0].CN_st_AgreeOn_Less_Temp1.Temp+1;
		}
		OutBuf[DataLen++]=ptst_AgreeOn_SetVidType->CN_st_AgreeOn_SetVidType_Par[0].CN_st_AgreeOn_Less_Temp1.Temp/100;
		OutBuf[DataLen++]=((ptst_AgreeOn_SetVidType->CN_st_AgreeOn_SetVidType_Par[0].CN_st_AgreeOn_Less_Temp1.Temp/10)%100);
		if(type==De_AgreeOn_SetVidType_Type_NumberCut)
		{ OutBuf[DataLen-4]=6;
		  OutBuf[DataLen-3]=0x00;
		  if(ptst_AgreeOn_SetVidType->CN_st_AgreeOn_SetVidType_Par[0].CN_st_AgreeOn_Less_Temp1.Temp>0x80000000)
	      {  OutBuf[DataLen-3]=0x11;
			 ptst_AgreeOn_SetVidType->CN_st_AgreeOn_SetVidType_Par[0].CN_st_AgreeOn_Less_Temp1.Temp=0xffffffff-ptst_AgreeOn_SetVidType->CN_st_AgreeOn_SetVidType_Par[1].CN_st_AgreeOn_Less_Temp1.Temp+1;
		  }
		  OutBuf[DataLen-2]=ptst_AgreeOn_SetVidType->CN_st_AgreeOn_SetVidType_Par[0].CN_st_AgreeOn_Less_Temp1.Temp/100;
		  OutBuf[DataLen-1]=((ptst_AgreeOn_SetVidType->CN_st_AgreeOn_SetVidType_Par[0].CN_st_AgreeOn_Less_Temp1.Temp/10)%100);
		  OutBuf[DataLen++]=0x00;
		  if(ptst_AgreeOn_SetVidType->CN_st_AgreeOn_SetVidType_Par[1].CN_st_AgreeOn_Less_Temp1.Temp>0x80000000)
	      {  OutBuf[DataLen-1]=0x11;
			 ptst_AgreeOn_SetVidType->CN_st_AgreeOn_SetVidType_Par[1].CN_st_AgreeOn_Less_Temp1.Temp=0xffffffff-ptst_AgreeOn_SetVidType->CN_st_AgreeOn_SetVidType_Par[1].CN_st_AgreeOn_Less_Temp1.Temp+1;
		  }
	      OutBuf[DataLen++]=ptst_AgreeOn_SetVidType->CN_st_AgreeOn_SetVidType_Par[1].CN_st_AgreeOn_Less_Temp1.Temp/100;
		  OutBuf[DataLen++]=((ptst_AgreeOn_SetVidType->CN_st_AgreeOn_SetVidType_Par[1].CN_st_AgreeOn_Less_Temp1.Temp/10)%100);		
	   }
	}
	else if(ID==33)
	{	OutBuf[DataLen++]=3;
	    OutBuf[DataLen++]=0x00;
		if(ptst_AgreeOn_SetVidType->CN_st_AgreeOn_SetVidType_Par[0].CN_st_AgreeOn_Less_Temp2.Temp>0x80000000)
		{	OutBuf[DataLen-1]=0x11;
			ptst_AgreeOn_SetVidType->CN_st_AgreeOn_SetVidType_Par[0].CN_st_AgreeOn_Less_Temp2.Temp=0xffffffff-ptst_AgreeOn_SetVidType->CN_st_AgreeOn_SetVidType_Par[0].CN_st_AgreeOn_Less_Temp2.Temp+1;
		}
		OutBuf[DataLen++]=(ptst_AgreeOn_SetVidType->CN_st_AgreeOn_SetVidType_Par[0].CN_st_AgreeOn_Less_Temp2.Temp/100);
		OutBuf[DataLen++]=((ptst_AgreeOn_SetVidType->CN_st_AgreeOn_SetVidType_Par[0].CN_st_AgreeOn_Less_Temp2.Temp/10)%100);
		if(type==De_AgreeOn_SetVidType_Type_NumberCut)
		{ OutBuf[DataLen-4]=6;
		  OutBuf[DataLen-3]=0x00;
		  if(ptst_AgreeOn_SetVidType->CN_st_AgreeOn_SetVidType_Par[0].CN_st_AgreeOn_Less_Temp2.Temp>0x80000000)
	      {  OutBuf[DataLen-1]=0x11;
			 ptst_AgreeOn_SetVidType->CN_st_AgreeOn_SetVidType_Par[0].CN_st_AgreeOn_Less_Temp2.Temp=0xffffffff-ptst_AgreeOn_SetVidType->CN_st_AgreeOn_SetVidType_Par[1].CN_st_AgreeOn_Less_Temp2.Temp+1;
		  }
		  OutBuf[DataLen-2]=ptst_AgreeOn_SetVidType->CN_st_AgreeOn_SetVidType_Par[0].CN_st_AgreeOn_Less_Temp2.Temp/100;
		  OutBuf[DataLen-1]=((ptst_AgreeOn_SetVidType->CN_st_AgreeOn_SetVidType_Par[0].CN_st_AgreeOn_Less_Temp2.Temp/10)%100);
		  OutBuf[DataLen++]=0x00;
		  if(ptst_AgreeOn_SetVidType->CN_st_AgreeOn_SetVidType_Par[1].CN_st_AgreeOn_Less_Temp2.Temp>0x80000000)
	      {  OutBuf[DataLen-1]=0x11;
			 ptst_AgreeOn_SetVidType->CN_st_AgreeOn_SetVidType_Par[1].CN_st_AgreeOn_Less_Temp2.Temp=0xffffffff-ptst_AgreeOn_SetVidType->CN_st_AgreeOn_SetVidType_Par[1].CN_st_AgreeOn_Less_Temp2.Temp+1;
		  }
	      OutBuf[DataLen++]=ptst_AgreeOn_SetVidType->CN_st_AgreeOn_SetVidType_Par[1].CN_st_AgreeOn_Less_Temp2.Temp/100;
		  OutBuf[DataLen++]=((ptst_AgreeOn_SetVidType->CN_st_AgreeOn_SetVidType_Par[1].CN_st_AgreeOn_Less_Temp2.Temp/10)%100);		
	   }
	}
	else if(ID==34)
	{	OutBuf[DataLen++]=3;
	    OutBuf[DataLen++]=0x00;
		if(ptst_AgreeOn_SetVidType->CN_st_AgreeOn_SetVidType_Par[0].CN_st_AgreeOn_Less_Temp3.Temp>0x80000000)
		{	OutBuf[DataLen-1]=0x11;
			ptst_AgreeOn_SetVidType->CN_st_AgreeOn_SetVidType_Par[0].CN_st_AgreeOn_Less_Temp3.Temp=0xffffffff-ptst_AgreeOn_SetVidType->CN_st_AgreeOn_SetVidType_Par[0].CN_st_AgreeOn_Less_Temp3.Temp+1;
		}
		OutBuf[DataLen++]=ptst_AgreeOn_SetVidType->CN_st_AgreeOn_SetVidType_Par[0].CN_st_AgreeOn_Less_Temp3.Temp/100;
		OutBuf[DataLen++]=((ptst_AgreeOn_SetVidType->CN_st_AgreeOn_SetVidType_Par[0].CN_st_AgreeOn_Less_Temp3.Temp/10)%100);
		if(type==De_AgreeOn_SetVidType_Type_NumberCut)
		{ OutBuf[DataLen-4]=6;
		  OutBuf[DataLen-3]=0x00;
		  if(ptst_AgreeOn_SetVidType->CN_st_AgreeOn_SetVidType_Par[0].CN_st_AgreeOn_Less_Temp3.Temp>0x80000000)
	      {  OutBuf[DataLen-3]=0x11;
			 ptst_AgreeOn_SetVidType->CN_st_AgreeOn_SetVidType_Par[0].CN_st_AgreeOn_Less_Temp3.Temp=0xffffffff-ptst_AgreeOn_SetVidType->CN_st_AgreeOn_SetVidType_Par[1].CN_st_AgreeOn_Less_Temp3.Temp+1;
		  }
		  OutBuf[DataLen-2]=ptst_AgreeOn_SetVidType->CN_st_AgreeOn_SetVidType_Par[0].CN_st_AgreeOn_Less_Temp3.Temp/100;
		  OutBuf[DataLen-1]=((ptst_AgreeOn_SetVidType->CN_st_AgreeOn_SetVidType_Par[0].CN_st_AgreeOn_Less_Temp3.Temp/10)%100);
		  OutBuf[DataLen++]=0x00;
		  if(ptst_AgreeOn_SetVidType->CN_st_AgreeOn_SetVidType_Par[1].CN_st_AgreeOn_Less_Temp3.Temp>0x80000000)
	      {  OutBuf[DataLen-1]=0x11;
			 ptst_AgreeOn_SetVidType->CN_st_AgreeOn_SetVidType_Par[1].CN_st_AgreeOn_Less_Temp3.Temp=0xffffffff-ptst_AgreeOn_SetVidType->CN_st_AgreeOn_SetVidType_Par[1].CN_st_AgreeOn_Less_Temp3.Temp+1;
		  }
	      OutBuf[DataLen++]=ptst_AgreeOn_SetVidType->CN_st_AgreeOn_SetVidType_Par[1].CN_st_AgreeOn_Less_Temp3.Temp/100;
		  OutBuf[DataLen++]=((ptst_AgreeOn_SetVidType->CN_st_AgreeOn_SetVidType_Par[1].CN_st_AgreeOn_Less_Temp3.Temp/10)%100);		
	   }
	}
	else if(ID==35)
	{		OutBuf[DataLen++]=3;
	    OutBuf[DataLen++]=0x00;
		if(ptst_AgreeOn_SetVidType->CN_st_AgreeOn_SetVidType_Par[0].CN_st_AgreeOn_Less_Temp4.Temp>0x80000000)
		{	OutBuf[DataLen-1]=0x11;
			ptst_AgreeOn_SetVidType->CN_st_AgreeOn_SetVidType_Par[0].CN_st_AgreeOn_Less_Temp4.Temp=0xffffffff-ptst_AgreeOn_SetVidType->CN_st_AgreeOn_SetVidType_Par[0].CN_st_AgreeOn_Less_Temp4.Temp+1;
		}
		OutBuf[DataLen++]=ptst_AgreeOn_SetVidType->CN_st_AgreeOn_SetVidType_Par[0].CN_st_AgreeOn_Less_Temp4.Temp/100;
		OutBuf[DataLen++]=((ptst_AgreeOn_SetVidType->CN_st_AgreeOn_SetVidType_Par[0].CN_st_AgreeOn_Less_Temp4.Temp/10)%100);
		if(type==De_AgreeOn_SetVidType_Type_NumberCut)
		{ OutBuf[DataLen-4]=6;
		  OutBuf[DataLen-3]=0x00;
		  if(ptst_AgreeOn_SetVidType->CN_st_AgreeOn_SetVidType_Par[0].CN_st_AgreeOn_Less_Temp4.Temp>0x80000000)
	      {  OutBuf[DataLen-1]=0x11;
			 ptst_AgreeOn_SetVidType->CN_st_AgreeOn_SetVidType_Par[0].CN_st_AgreeOn_Less_Temp4.Temp=0xffffffff-ptst_AgreeOn_SetVidType->CN_st_AgreeOn_SetVidType_Par[1].CN_st_AgreeOn_Less_Temp4.Temp+1;
		  }
		  OutBuf[DataLen-2]=ptst_AgreeOn_SetVidType->CN_st_AgreeOn_SetVidType_Par[0].CN_st_AgreeOn_Less_Temp4.Temp/100;
		  OutBuf[DataLen-1]=((ptst_AgreeOn_SetVidType->CN_st_AgreeOn_SetVidType_Par[0].CN_st_AgreeOn_Less_Temp4.Temp/10)%100);
		  OutBuf[DataLen++]=0x00;
		  if(ptst_AgreeOn_SetVidType->CN_st_AgreeOn_SetVidType_Par[1].CN_st_AgreeOn_Less_Temp4.Temp>0x80000000)
	      {  OutBuf[DataLen-1]=0x11;
			 ptst_AgreeOn_SetVidType->CN_st_AgreeOn_SetVidType_Par[1].CN_st_AgreeOn_Less_Temp4.Temp=0xffffffff-ptst_AgreeOn_SetVidType->CN_st_AgreeOn_SetVidType_Par[1].CN_st_AgreeOn_Less_Temp4.Temp+1;
		  }
	      OutBuf[DataLen++]=ptst_AgreeOn_SetVidType->CN_st_AgreeOn_SetVidType_Par[1].CN_st_AgreeOn_Less_Temp4.Temp/100;
		  OutBuf[DataLen++]=((ptst_AgreeOn_SetVidType->CN_st_AgreeOn_SetVidType_Par[1].CN_st_AgreeOn_Less_Temp4.Temp/10)%100);		
	   }
	}
	*ReDataLen=DataLen;
}

 
static uint32 Expain_VidType2LessAddree(st_AgreeOn_SetVidType_Par	*ptst_AgreeOn_SetVidType_Par,uint8 ID)
{	
	if(ID==0)
		return ptst_AgreeOn_SetVidType_Par->CN_Less_Switch1.Addree;
	else if(ID==1)
		return ptst_AgreeOn_SetVidType_Par->CN_Less_Switch2.Addree;
	else if(ID==2)
		return ptst_AgreeOn_SetVidType_Par->CN_Less_Switch3.Addree;
	else if(ID==3)
		return ptst_AgreeOn_SetVidType_Par->CN_Less_Switch4.Addree;
	else if(ID==4)
		return ptst_AgreeOn_SetVidType_Par->CN_Less_Switch5.Addree;
	else if(ID==5)
		return ptst_AgreeOn_SetVidType_Par->CN_Less_Switch6.Addree;
   	else if(ID==6)
		return ptst_AgreeOn_SetVidType_Par->CN_st_AgreeOn_Less_Temp1.Addree;
	else if(ID==7)
		return ptst_AgreeOn_SetVidType_Par->CN_st_AgreeOn_Less_Temp2.Addree;
	else if(ID==8)
		return ptst_AgreeOn_SetVidType_Par->CN_st_AgreeOn_Less_Temp3.Addree;
	else if(ID==9)
		return ptst_AgreeOn_SetVidType_Par->CN_st_AgreeOn_Less_Temp4.Addree;
}

/*===========================================数据转化层=================================================*/
#define De_Gps2CenGps_Latitude				0 							//纬度
#define De_Gps2CenGps_LongHem				De_Gps2CenGps_Latitude+4	//经度
#define De_Gps2CenGps_Speed					De_Gps2CenGps_LongHem+4		//速度
#define De_Gps2CenGps_Angle					De_Gps2CenGps_Speed+1		//角度
#define De_Gps2CenGps_Height				De_Gps2CenGps_Angle+1		//海拔高度
#define De_Gps2CenGps_Timer					De_Gps2CenGps_Height+2		//时间
static void Gps2CenGps(st_Data_Gps	*ptst_Data_Gps,uint8 *OutBuf)
{	Gps2CenGps_Latitude(ptst_Data_Gps,OutBuf+De_Gps2CenGps_Latitude);
	Gps2CenGps_LongHem(ptst_Data_Gps,OutBuf+De_Gps2CenGps_LongHem);
	Gps2CenGps_Speed(ptst_Data_Gps,OutBuf+De_Gps2CenGps_Speed);
	Gps2CenGps_Angle(ptst_Data_Gps,OutBuf+De_Gps2CenGps_Angle);
	Gps2CenGps_Height(ptst_Data_Gps,OutBuf+De_Gps2CenGps_Height);
	Gps2CenGps_Timer(ptst_Data_Gps,OutBuf+De_Gps2CenGps_Timer);
}

static void Gps2CenGps_Latitude(st_Data_Gps	*ptst_Data_Gps,uint8 *OutBuf) //纬度转化
{	uint32 Hex32;
	Hex32=ptst_Data_Gps->CN_st_Gps_Data_GPRMC.Latitude;
	OutBuf[0]=(Hex32>>24);
	OutBuf[1]=(Hex32>>16);
	OutBuf[2]=(Hex32>>8);
	OutBuf[3]=(Hex32&0xff);
} 

static void Gps2CenGps_LongHem(st_Data_Gps	*ptst_Data_Gps,uint8 *OutBuf)	//经度转化
{	uint32 Hex32;
	Hex32=ptst_Data_Gps->CN_st_Gps_Data_GPRMC.Longitude;
	OutBuf[0]=(Hex32>>24);
	OutBuf[1]=(Hex32>>16);
	OutBuf[2]=(Hex32>>8);
	OutBuf[3]=(Hex32&0xff);
}

static void Gps2CenGps_Speed(st_Data_Gps	*ptst_Data_Gps,uint8 *OutBuf)	//速度转化
{	uint32 Hex32;
	Hex32=(ptst_Data_Gps->CN_st_Gps_Data_GPRMC.Speed);
	Hex32=Hex32;
   	OutBuf[0]=Hex32;
}


static void Gps2CenGps_Angle(st_Data_Gps	*ptst_Data_Gps,uint8 *OutBuf)	//方向转化
{	OutBuf[0]=(ptst_Data_Gps->CN_st_Gps_Data_GPRMC.Angle/20);
}

static void Gps2CenGps_Height(st_Data_Gps	*ptst_Data_Gps,uint8 *OutBuf)	//海拔高度
{	uint32 Hex32;
	if(ptst_Data_Gps->CN_st_Gps_Data_GPGGA.Height<0)						//当海拔为负数时
	{	Hex32=ptst_Data_Gps->CN_st_Gps_Data_GPGGA.Height;
		Hex32--;
		Hex32=~Hex32;
		Hex32=Hex32/10;
		OutBuf[0]=((Hex32>>8)&0xff);
		OutBuf[1]=(Hex32&0xff);				
	}
	else
	{	Hex32=ptst_Data_Gps->CN_st_Gps_Data_GPGGA.Height;
		OutBuf[0]=((Hex32>>8)&0xff);
		OutBuf[1]=(Hex32&0xff);		
	}	
}

static void Gps2CenGps_Timer(st_Data_Gps	*ptst_Data_Gps,uint8 *OutBuf) //时间	
{	CN_st_Fun_AscNumber.MoveByte(OutBuf,ptst_Data_Gps->CN_st_Gps_Data_GPRMC.DateTime+1,6);
	CN_st_Fun_AscNumber.Bcd2Hex(OutBuf,OutBuf,6);
}
static void Gps2ReduceGps_Height(int32 *Hex32,uint8 *OutBuf)	//海拔高度
{	if(*Hex32<0)						//当海拔为负数时
	{	*Hex32--;
		*Hex32=~(*Hex32);
		*Hex32=(*Hex32)/10;
		OutBuf[0]=((*Hex32>>8)&0xff);
		OutBuf[1]=(*Hex32&0xff);				
	}
	else
	{	OutBuf[0]=((*Hex32>>8)&0xff);
		OutBuf[1]=(*Hex32&0xff);		
	}	
}
static void Explain_state(uint8 *OutBuf,st_AgreeOn_Send_UploaderPar	*ptst_AgreeOn_Send_UploaderPar,uint16 *ReDataLen) 
{	uint8 Point,PointNumber,k,i,j;
	for(Point=(sizeof(ptst_AgreeOn_Send_UploaderPar->CN_st_AgreeOn_Send_Basic.State)/8)-1,i=0;i<sizeof(ptst_AgreeOn_Send_UploaderPar->CN_st_AgreeOn_Send_Basic.State)&&Point>=0;Point--)
	 {	 PointNumber=0;
	     for(j=0;j<8;j++,i++)
	 	 {	if(ptst_AgreeOn_Send_UploaderPar->CN_st_AgreeOn_Send_Basic.State[i]!=De_AgreeOn_State_Suc)
		     {	k=(1<<j);	
			  	PointNumber+=k;
		     }	
		 }	 
	 	 OutBuf[Point]=PointNumber;
	 }
	*ReDataLen=4;
}
static void Explain_UpPar(uint8 *OutBuf,st_AgreeOn_Send_UploaderPar	*ptst_AgreeOn_Send_UploaderPar,uint16 *ReDataLen)  //工作参数
{	uint16 DataLen,i,Len;
    DataLen=0;
	for(i=0;i<sizeof(ptst_AgreeOn_Send_UploaderPar->CN_st_WorkVal_Tabel.Type);i++)
	{	if(ptst_AgreeOn_Send_UploaderPar->CN_st_WorkVal_Tabel.Type[i]!=De_st_AgreeOn_Send_Waring_Type_Yes)
			continue;
		OutBuf[DataLen++]=(CN_Ba_WordPar[i]>>8);
		OutBuf[DataLen++]=(CN_Ba_WordPar[i]&0xff);
		Explain_WorkPar1(&ptst_AgreeOn_Send_UploaderPar->CN_st_WorkVal_Tabel.CN_st_AgreeOn_SetVidType_Par,OutBuf+DataLen,&Len,i);
		DataLen+=Len;
	}
   *ReDataLen=DataLen;
}
