#define De_GprsHard_Compiler
#include "_GprsHard.h"
/*=========================================GPRSӲ���㺯�����===================================================*/
static uint16 Init(void)																	//��ʼ������
{	CN_st_Fun_Uart.Init(De_GprsHard_Use_Uart);
	return De_Suc_GprsHard;			
}
static uint16 PowerUp(void)									   								//ģ���ϵ�
{	uint16 Result;
//	De_Fun_GprsHard_ModermPowerUp;															//ģ��Ӳ������
//	IODIR0  |= (1<<7);IODIR0  |= (1<<9);IOSET0 |= (1<<9);IOCLR0 |= (1<<7);MODEM_Dly100ms(20);IOSET0 |= (1<<7);MODEM_Dly100ms(20);IOCLR0 |= (1<<7);
	De_Fun_GprsHard_ModermPowerRst;				//��λģ��
	if((Result=LookChipID(&ptst_Fun_GprsHard_Fac))!=De_Suc_GprsHard)						//Ѱ������
		return Result;
	if((Result=ptst_Fun_GprsHard_Fac->Init((void *)ModermCom,(uint8 *)De_GprsHard_Use_Ram,De_GprsHard_Use_Ram_Len))!=De_Suc_GprsHard)
		return Result;
	return InitModerm();
}
static uint16 PowerDown(void)								   								//ģ���µ�
{	if(ptst_Fun_GprsHard_Fac==NULL)
		return De_Erro_GprsHead_NoDriver;
	ptst_Fun_GprsHard_Fac->Read(De_GprsHard_Com_PowerDown,NULL,NULL,NULL,NULL);	
	return De_Suc_GprsHard;
}
static uint16 Read(uint16 Command,void *SendBuf,uint16 SizeofSendBuf,void *AgreeBuf,uint16 *SizeofAgreeBuf)
{	return ptst_Fun_GprsHard_Fac->Read(Command,SendBuf,SizeofSendBuf,AgreeBuf,SizeofAgreeBuf);	
}
/*=================================================�м�֧��=====================================================*/
static uint16 InitModerm(void)																//��ʼ��MODERM
{	uint16 Result;
	if(ptCN_st_Fun_GprsHard_Fac==NULL)
		return De_Erro_GprsHead_NoDriver;
	if((Result=ptst_Fun_GprsHard_Fac->Read(De_GprsHard_Com_CloseShow,NULL,NULL,NULL,NULL))!=De_Suc_GprsHard)							//�رջ���
		return Result;
//	if((Result=ptst_Fun_GprsHard_Fac->Read(De_GprsHard_Com_IPR,NULL,NULL,NULL,NULL))!=De_Suc_GprsHard)							//���ò�����
//		return Result;
	return De_Suc_GprsHard;
}
static uint16 LookChipID(st_Fun_GprsHard_Fac	**ptst_Fun_GprsHard_Fac1)					//����������ַ
{	uint8 ChipID[20];
	uint16 Result;
	uint8 i;
	for(i=0;i<(sizeof(CN_Ba_st_Da_Uart_GprsHard))/(sizeof(st_Da_Uart));i++)					//Ѱ�Ҳ�����
	{	CN_st_Fun_Uart.Close(De_GprsHard_Use_Uart);
		CN_st_Fun_Uart.Open(De_GprsHard_Use_Uart,(st_Da_Uart	*)(CN_Ba_st_Da_Uart_GprsHard+i));
		if(GetBpsAT()==De_Suc_GprsHard)
			break;
//		if(GetBpsAT()==De_Suc_GprsHard)
//			break;
	}
	if(i==sizeof(CN_Ba_st_Da_Uart_GprsHard)/(sizeof(st_Da_Uart)))  							//�����ʶԱ��Ƿ�ɹ�					
		return De_Erro_GprsHead_OpenPower;
	if(i!=0)
	{	SetBps(CN_Ba_st_Da_Uart_GprsHard[0].BaudRate);
	 	CN_st_Fun_Uart.Close(De_GprsHard_Use_Uart);
		CN_st_Fun_Uart.Open(De_GprsHard_Use_Uart,(st_Da_Uart	*)CN_Ba_st_Da_Uart_GprsHard);
	}
	CloseShow();
	CN_st_Fun_AscNumber.ClsArray(ChipID,sizeof(ChipID));
	if((Result=GetChipID(ChipID))!=De_Suc_GprsHard)											//Ѱ��������
		return Result;
	for(i=0;i<sizeof(*ptCN_st_Fun_GprsHard_Fac)/sizeof(uint32);i++)
	{	if(CN_st_Fun_AscNumber.CompareBuf(ptCN_st_Fun_GprsHard_Fac[i]->FacID,ChipID,
		CN_st_Fun_AscNumber.Strsize16(ptCN_st_Fun_GprsHard_Fac[i]->FacID))==0)
	  		break;
	}
	if(i==sizeof(*ptCN_st_Fun_GprsHard_Fac)/sizeof(uint32))
		return De_Erro_GprsHead_NoDriver;
	*ptst_Fun_GprsHard_Fac1=(st_Fun_GprsHard_Fac	*)ptCN_st_Fun_GprsHard_Fac[i];
	return De_Suc_GprsHard;
}

/*==============================================ͨ������========================================================*/
static uint16 GetChipID(uint8 *Buf)	 									//��ȡ���Ҵ���
{	uint16 Result;
	if((Result=ModermCom(NULL,X_RAM,De_GprsHard_Use_Ram_Len,(st_GprsHard_Order_Cut	*)&CN_st_GprsHard_Order_Cut_ChipID))!=De_Suc_GprsHard)
		return Result;
	ClearNoDisplay(X_RAM);
	Result=CN_st_Fun_AscNumber.Strsize16(X_RAM);
	CN_st_Fun_AscNumber.MoveByte(Buf,X_RAM,Result);
	return De_Suc_GprsHard;
}
static uint16 GetBpsAT(void)											//����ATָ��,���Բ���������
{	
	return ModermCom(NULL,X_RAM,De_GprsHard_Use_Ram_Len,(st_GprsHard_Order_Cut	*)&CN_st_GprsHard_Order_Cut_AT);
}
static uint16 CloseShow(void)
{	return ModermCom(NULL,X_RAM,De_GprsHard_Use_Ram_Len,(st_GprsHard_Order_Cut	*)&CN_st_GprsHard_Order_Cut_ATE);
}
static uint16 SetBps(uint32 Bps)
{	uint8 Buf[10];
	CN_st_Fun_AscNumber.ClsArray(Buf,sizeof(Buf));
	CN_st_Fun_AscNumber.Algorism2Asc(Bps,Buf);
	return ModermCom(Buf,X_RAM,De_GprsHard_Use_Ram_Len,(st_GprsHard_Order_Cut	*)&CN_st_GprsHard_Order_Cut_BPS);
}
/*==============================================��MODERMͨѶ=====================================================*/
static uint16 ModermCom(uint8 *SendBuf,uint8 *AgreeBuf,uint16 SizeofAgreeBuf,st_GprsHard_Order_Cut	*ptst_GprsHard_Order_Cut)
{	uint16 Result,DataLength;
DataLength=0;
	Result = ModermCom1(SendBuf,AgreeBuf,SizeofAgreeBuf,ptst_GprsHard_Order_Cut);//,&DataLength);
	if((Result==De_Erro_GprsHead_OverTimer)&&(DataLength==0))
	{	OSTimeDly(100);
		return ModermCom1(SendBuf,AgreeBuf,SizeofAgreeBuf,ptst_GprsHard_Order_Cut);//,&DataLength);	
	}
	return Result;		
}

static uint16 ModermCom1(uint8 *SendBuf,uint8 *AgreeBuf,uint16 SizeofAgreeBuf,st_GprsHard_Order_Cut	*ptst_GprsHard_Order_Cut)//,uint16 *DataLength1)
{	uint16 DataLenOrderHead,DataLenSendBuf,DataLenOrderTail,RecLen,TrueDataLen,ErroDataLen,HeadDataLen;
	uint32 i,OverTime;
	uint8 ByteV,*Temp,*Temp1;
//	*DataLength1 = 0;
	TrueDataLen=CN_st_Fun_AscNumber.Strsize16(ptst_GprsHard_Order_Cut->AgreeTrueTail); 		//��ȷ����
	ErroDataLen=CN_st_Fun_AscNumber.Strsize16(ptst_GprsHard_Order_Cut->AgreeErroTail);		//�������
	HeadDataLen=CN_st_Fun_AscNumber.Strsize16(ptst_GprsHard_Order_Cut->AgreeHead);			//ͷ����Ϣ
	DataLenOrderHead=CN_st_Fun_AscNumber.Strsize16(ptst_GprsHard_Order_Cut->OrderHead);	
	DataLenSendBuf=CN_st_Fun_AscNumber.Strsize16(SendBuf);
	DataLenOrderTail=CN_st_Fun_AscNumber.Strsize16(ptst_GprsHard_Order_Cut->OrderTail);
	for(;CN_st_Fun_Uart.Read(De_GprsHard_Use_Uart,&ByteV,sizeof(ByteV))!=0;);					//��ջ���

	if(DataLenOrderHead!=0)		//����ͷ��Ϣ
	{	CN_st_Fun_Uart.Write(De_GprsHard_Use_Uart,ptst_GprsHard_Order_Cut->OrderHead,DataLenOrderHead);
//		CN_st_Fun_Uart.Write(0,ptst_GprsHard_Order_Cut->OrderHead,DataLen);
	}
	if((SendBuf!=NULL)&&(DataLenSendBuf!=0))																	//��������				 					
	{	CN_st_Fun_Uart.Write(De_GprsHard_Use_Uart,SendBuf,DataLenSendBuf);
//		CN_st_Fun_Uart.Write(0,SendBuf,DataLen);
	}
	if(DataLenOrderTail!=0)	   	//����β��Ϣ
	{	CN_st_Fun_Uart.Write(De_GprsHard_Use_Uart,ptst_GprsHard_Order_Cut->OrderTail,DataLenOrderTail);
//		CN_st_Fun_Uart.Write(0,ptst_GprsHard_Order_Cut->OrderTail,DataLen);
	}
	OverTime=ptst_GprsHard_Order_Cut->MaxDelay*700;
	for(i=0,RecLen=0;i<OverTime;WatchDog())
	{	if((DataLenOrderHead=CN_st_Fun_Uart.Read(De_GprsHard_Use_Uart,AgreeBuf+RecLen,SizeofAgreeBuf-RecLen))==0)
		{	i++;
		 	continue;
		}
		i=0;
		RecLen+=DataLenOrderHead;
		AgreeBuf[RecLen]=0;
//		*DataLength1 = RecLen;
		if(TrueDataLen!=0)																//��ȷ�жϲ�Ϊ��
		{	if((Temp=CN_st_Fun_AscNumber.LookStr(ptst_GprsHard_Order_Cut->AgreeTrueTail,AgreeBuf))!=NULL)	//����ȷ������
			{							//ͷ����Ϣ��Ҫ�ж�
				Temp1=AgreeBuf;
			//	CN_st_Fun_Uart.Write(0,AgreeBuf,RecLen);
				if(HeadDataLen!=0)
				{	if((Temp1=CN_st_Fun_AscNumber.LookStr(ptst_GprsHard_Order_Cut->AgreeHead,AgreeBuf))==NULL)//ͷ����Ϣ��һ��	 	
						return De_Erro_GprsHead_FlagHead;			//��ͷ��Ϣ����
				}
				Temp1+=HeadDataLen;
				if(Temp1>Temp)
					return De_Erro_GprsHead_FlagHead;
				DataLenOrderHead=Temp-Temp1;
				CN_st_Fun_AscNumber.MoveByte(AgreeBuf,Temp1,DataLenOrderHead);
			   	AgreeBuf[DataLenOrderHead]=0;
				return De_Suc_GprsHard;
			}
		}
		if(ErroDataLen!=0)
		{	if((Temp=CN_st_Fun_AscNumber.LookStr(ptst_GprsHard_Order_Cut->AgreeErroTail,AgreeBuf))!=NULL)	
			{//	CN_st_Fun_Uart.Write(0,AgreeBuf,RecLen);
				return De_Erro_GprsHead_ReErro;	
			}
		}
		if((ErroDataLen==0)&&(TrueDataLen==0))				//��������Ϊ0
		{//	if(HeadDataLen==0)
		 //	{	AgreeBuf[RecLen]=0;	
		 //	   	return De_Suc_GprsHard;
		 //	}
		 	Temp1=AgreeBuf;
		 	if((Temp=CN_st_Fun_AscNumber.LookStr(ptst_GprsHard_Order_Cut->AgreeTail,AgreeBuf))==NULL)
				continue;
			Temp++;
			if((Temp=CN_st_Fun_AscNumber.LookStr(ptst_GprsHard_Order_Cut->AgreeTail,Temp))==NULL)	
				continue;		
			if(HeadDataLen!=0)
			{	if((Temp1=CN_st_Fun_AscNumber.LookStr(ptst_GprsHard_Order_Cut->AgreeHead,AgreeBuf))==NULL)
					return 	De_Erro_GprsHead_FlagHead;
			}
			Temp1+=HeadDataLen;
			DataLenOrderHead=Temp1-AgreeBuf;
			DataLenOrderHead=RecLen-DataLenOrderHead;
			CN_st_Fun_AscNumber.MoveByte(AgreeBuf,Temp1,DataLenOrderHead);
			AgreeBuf[DataLenOrderHead]=0;
			return De_Suc_GprsHard;
		}
	}
	return De_Erro_GprsHead_OverTimer;					
}
/*----------------------------------------ϵͳ����----------------------------------------------------------*/
static void MODEM_Dly100ms(int num)
{	uint32  i,m;
    INT32U j;
	m = num*10;
   	for(i=0;i<m;i++)
    {	for(j=0;j<660;j++)
		{	IOCLR1 |= (1<<18);				  //��ʱ�м�ι��
			IOSET1 |= (1<<18);
			IOSET1 |= (1<<18);
			IOCLR1 |= (1<<18);	
		}
    }
}
static void ClearNoDisplay(uint8 *Buf)
{	uint16 DataLen,i;
	DataLen=CN_st_Fun_AscNumber.Strsize16(Buf);
	for(i=0;i<DataLen;)
	{	if(Buf[i]>0x20)
		{	i++;
			continue;
		}
		CN_st_Fun_AscNumber.MoveByte(Buf+i,Buf+i+1,DataLen-i-1);
		Buf[DataLen-1]=0;
		DataLen--;
	}
}




