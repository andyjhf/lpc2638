#define De_Gps_Compiler
#include "Gps.h"
#ifdef De_Compiler_HardWare_Gps
/*======================================================����===================================================*/
static uint16 Init(void)
{	const st_Da_Uart	CN_st_Da_Uart={4800,8,1,0};
	if(GpsSem!=NULL)
		return De_Suc_Gps;	
	CN_PowerState=De_Gps_State_Power_Down;
	De_Gps_Powe_OFF;
	CN_st_Fun_Uart.Init(De_Gps_Use_Uart);
	CN_st_Fun_Uart.Open(De_Gps_Use_Uart,(st_Da_Uart	*)&CN_st_Da_Uart);
	CN_st_Fun_AscNumber.MoveByte(&CN_st_Sensor_State,(void *)&CN_Ba_st_Sensor_State,sizeof(st_Sensor_State));
	#ifdef OS_ADD
	GpsSem=OSSemCreate(1);
	if(GpsSem==NULL)
		return	De_Erro_Gps_Init; 
	#endif
	return De_Suc_Gps;
}

static uint16 Open(st_Sensor_DataPar	*ptst_Sensor_DataPar,uint8 *fd)			//�򿪵�Դ
{	uint8 err;
	#ifdef	OS_ADD
	OSSemPend(GpsSem, 0, &err);
	#endif
	ptst_Sensor_DataPar=ptst_Sensor_DataPar;
	De_Gps_Power_ON;
	CN_PowerState=De_Gps_State_Power_Up;
	CN_st_Sensor_State.Battery=De_Sensor_State_Suc;
	#ifdef	OS_ADD
	OSSemPost(GpsSem);
	#endif 
	return De_Suc_Gps;
}
static uint16 Close(uint8 fd)														//�رյ�Դ
{	uint8 err;
	#ifdef	OS_ADD
	OSSemPend(GpsSem, 0, &err);
	#endif
	De_Gps_Powe_OFF;
	LED_OFF;
	CN_PowerState=De_Gps_State_Power_Down;
	#ifdef  OS_ADD
	OSSemPost(GpsSem);
	#endif
	return De_Suc_Gps;	
}
static uint16 Read(uint8 fd,void *SendBuf,void *AgreeBuf)
{	st_Data_Gps	*ptst_Data_Gps;
	uint8 err;
	uint16 Result;
	#ifdef	OS_ADD
	OSSemPend(GpsSem, 0, &err);
	#endif
	ptst_Data_Gps=AgreeBuf;
	Result=De_Erro_Gps_NoPower;
	if(CN_PowerState==De_Gps_State_Power_Up)
		Result=GpsCommInput(ptst_Data_Gps);
	CN_st_Sensor_State.Dly=De_Sensor_State_Suc;	CN_st_Sensor_State.Battery=De_Sensor_State_Suc;
   	CN_st_Sensor_State.Work=De_Sensor_State_Suc;
   	if(Result==De_Erro_Gps_TimeOut)
		CN_st_Sensor_State.Dly=De_Sensor_MaxDly_State_Erro;
	else if(Result!=De_Suc_Gps)
		CN_st_Sensor_State.Work=De_Sensor_Par_State_Erro;
    #ifdef  OS_ADD
	OSSemPost(GpsSem);
	#endif
	return Result;
}
static uint16 GetState(st_Sensor_State	*ptst_Sensor_State,uint8 fd)
{	uint8 err;
	#ifdef	OS_ADD
	OSSemPend(GpsSem, 0, &err);
	#endif
	CN_st_Fun_AscNumber.MoveByte(ptst_Sensor_State,&CN_st_Sensor_State,sizeof(st_Sensor_State));			
	#ifdef  OS_ADD
	OSSemPost(GpsSem);
	#endif
	return De_Suc_Gps;
}

/*===========================================================���ݽ��ղ�=============================================================*/
static uint16 GpsCommInput(st_Data_Gps *ptst_Data_Gps)							//GPSͨѶ�������
{	uint16 Result;
	uint8 Order,DataLen,Flag[2]={De_Gps_Flag_Close,De_Gps_Flag_Close};
	for(;;)
	{	if((Result=JugeOrder(&Order,&DataLen))!=De_Suc_Gps)							//��������
			return Result;
		if(Order==De_Gps_Order_GPRMC)
		{	Flag[0]=De_Gps_Flag_Open;
			if((Result=Parse_GPRMC(&ptst_Data_Gps->CN_st_Gps_Data_GPRMC,CN_Gps_Buf,DataLen))!=De_Suc_Gps)
				return Result;
		}
		else if(Order==De_Gps_Order_GPGGA)
		{	Flag[1]=De_Gps_Flag_Open;
			if((Result=Parse_GPGGA(&ptst_Data_Gps->CN_st_Gps_Data_GPGGA,CN_Gps_Buf,DataLen))!=De_Suc_Gps)
		   		return Result;
		}
		if((Flag[0]==De_Gps_Flag_Open)&&(Flag[1]==De_Gps_Flag_Open))
			return De_Suc_Gps;	
	}

}

/*++++++++++++++++++++++++++++++++++++++++++++++++++++++++��Э��Ľ���++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/
/*	ͨѶ����:Ĭ��Ϊ4800bps,8λ����λ��1λֹͣλ������żУ��.
	������:GPSģ��
	������:������	
	������ֻ�ܽ���
	NMEA 0183  ͨѶЭ��,����ͨѶ��ʽ����:
	'$'+��ַ��(5,ǰ������ʶ��λ,����λ�������)+','+����+'*'+У���+<CR>+<LF>
	ע��:У���:$��*֮�������ַ������У��ͣ����ֽ���������㣬�õ�У��ͺ���ת��16���Ƹ�ʽ��ASCII�ַ�)
*/
static uint16 JugeOrder(uint8 *Order,uint8 *AgreeLen)
{	uint8 *CheckEnd;
	uint8 ByteV,CheckValue[2];
	uint16 Result;
	uint16 DataLen;
	uint32 timeout=0; 
	for(DataLen=0;;)
	{	Result=CN_st_Fun_Uart.Read(De_Gps_Use_Uart,&ByteV,1);
		if(Result==0)
		{	WatchDog();					   //ʱ����ӳ�100-200ms
			timeout ++; 
			if(timeout == 200000)		   //540ms		  100000 ->  260ms
			{
				timeout = 0;
				return De_Erro_Gps_TimeOut;
			}
			continue;
		}
		timeout = 0;
		if((DataLen==0)&&(ByteV!='$'))
			continue;
		if(DataLen>De_Gps_MaxAgreeBuf)
		{	DataLen=0;
		 	continue;
		}				
		CN_Gps_Buf[DataLen++]=ByteV;
		if(ByteV==0x0a)
			break;	 							//һ֡���ݽ������
	}
	if(!((CN_Gps_Buf[DataLen-1]==0x0a)&&(CN_Gps_Buf[DataLen-2]==0x0d)))
		return De_Erro_Gps_Data;
   	CheckEnd=memchr(CN_Gps_Buf,'*',DataLen);
	if(CheckEnd==NULL)
		return De_Erro_Gps_Data;		 
	ByteV=CN_st_Fun_Arithmetic.ptst_Fun_CheckSum->CheckSum(CN_Gps_Buf+1,CheckEnd-1-CN_Gps_Buf);
	CN_st_Fun_AscNumber.HexBuf2Asc(&ByteV,CheckValue,1);
	if(CN_st_Fun_AscNumber.CompareBuf(CheckEnd+1,CheckValue,2)==1)
		return De_Erro_Gps_Data;
//	CN_st_Fun_Uart.Write(0,CN_Gps_Buf,DataLen);
	for(Result=0;Result<De_Gps_Order_MaxNumber;Result++)
	{	if(CN_st_Fun_AscNumber.CompareBuf((uint8 *)(CN_st_Gps_Order[Result].Gut),(uint8 *)CN_Gps_Buf,strlen((char*)CN_st_Gps_Order[Result].Gut))==0)
		{	*AgreeLen=DataLen;
			*Order=CN_st_Gps_Order[Result].OrderNumber;
			return De_Suc_Gps;
		}	
	}
	return De_Erro_Gps_Order;			
}

/*=================================================���ݽ�������==================================================================*/

/*+++++++++++++++++++++++++++++++++++++++++++++++GPRMC����++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/
	/*	���������ʽΪ
		$GPRMC+UTC(ʱ��)+��λ״̬+γ��+γ�Ȱ���+����+���Ȱ���+��������+���溽��+UTC����+��ƫ��+��ƫ�Ƿ���+ģʽָʾ
				 1		   2	   3	  4		 5		6		 7		 8		   9	  10	 11		   12
	*/
static uint16 Parse_GPRMC(st_Gps_Data_GPRMC	*ptst_Gps_Data_GPRMC,uint8 *GpsBuf,uint8 SizeofGpsBuf)
{	if(Parse_GPRMC_LocationTrue(&ptst_Gps_Data_GPRMC->LocationTrue,GpsBuf,SizeofGpsBuf)!=De_Suc_Gps)
		return	De_Erro_Gps_Data;
	if(ptst_Gps_Data_GPRMC->LocationTrue!=De_Gps_Location_True)	 			//��λ�� //����λ���ݲ���Ҫ�������·���
	{	LED_OFF;
		return De_Erro_Gps_NoLocation;
	}
	LED_ON;
	if(Parse_GPRMC_GetTime(ptst_Gps_Data_GPRMC->DateTime,GpsBuf,SizeofGpsBuf)!=De_Suc_Gps)
		return	De_Erro_Gps_Data;													
	if(Parse_GPRMC_Lat(&ptst_Gps_Data_GPRMC->LatHem,&ptst_Gps_Data_GPRMC->Latitude,GpsBuf,SizeofGpsBuf)!=De_Suc_Gps)
		return De_Erro_Gps_Data;
	if(Parse_GPRMC_Long(&ptst_Gps_Data_GPRMC->LongHem,&ptst_Gps_Data_GPRMC->Longitude,GpsBuf,SizeofGpsBuf)!=De_Suc_Gps)
		return De_Erro_Gps_Data;
	if(Parse_GPRMC_Speed(&ptst_Gps_Data_GPRMC->Speed,GpsBuf,SizeofGpsBuf)!=De_Suc_Gps)
		return De_Erro_Gps_Data;	
	if(Parse_GPRMC_Angle(&ptst_Gps_Data_GPRMC->Angle,GpsBuf,SizeofGpsBuf)!=De_Suc_Gps)
		return De_Erro_Gps_Data;
	return De_Suc_Gps;			 					
} 
/*----------------------------------------------GPRMC��������ʵ��----------------------------------------------------------------*/


/* 	UTC(ʱ��)+UTC(����)       ��������ʱ��     ����ɱ���ʱ�䣬��ȱ���ʱ����8Сʱ
	(HHMMSS.MS)

*/

static uint16 Parse_GPRMC_GetTime(uint8 *DateTime,uint8 *GpsBuf,uint8 SizeofGpsBuf)						//��ȡʱ��
{	uint8 *AmountBuf;	 
	uint8 CurTime[7],i;
	
	AmountBuf=SeekChar(GpsBuf,',',SizeofGpsBuf,De_Gps_Parse_Space_Time);
	if(AmountBuf==NULL)
		return De_Erro_Gps_Data;
	CN_st_Fun_AscNumber.MoveByte(CurTime,AmountBuf+1,6);
	CN_st_Fun_AscNumber.Asc2Bcd(CurTime,DateTime+4,6); 								//��ȡʱ��
	
	AmountBuf=SeekChar(GpsBuf,',',SizeofGpsBuf,De_Gps_Parse_Space_Date);	
	CN_st_Fun_AscNumber.MoveByte(CurTime,AmountBuf+1,6);
	CN_st_Fun_AscNumber.Asc2Bcd(CurTime+4,DateTime+1,2);							//��
	CN_st_Fun_AscNumber.Asc2Bcd(CurTime+2,DateTime+2,2);							//��
	CN_st_Fun_AscNumber.Asc2Bcd(CurTime,DateTime+3,2);								//��
	DateTime[0]=0x20;
	if(CN_st_Fun_Date.Juge(DateTime,De_Type_Date_Second)!=De_Suc_Date)				//�ж�ʱ���������Ƿ�Ϸ�
   		return De_Erro_Gps_Data;
	/*-----------------------------------����ʱ�任��------------------------------*/
    for(i=0;i<8;i++)
		CN_st_Fun_Date.Next(DateTime,De_Type_Date_Hour);
	return De_Suc_Gps;
}
																   	
static uint16 Parse_GPRMC_LocationTrue(uint8 *ByteV,uint8 *GpsBuf,uint8 SizeofGpsBuf) 					//��λ״̬
{	uint8 *AmountBuf;
	AmountBuf=SeekChar(GpsBuf,',',SizeofGpsBuf,De_Gps_Parse_Space_Location);
	if(AmountBuf==NULL)
		return De_Erro_Gps_Data;
	if((AmountBuf[1]==De_Gps_Location_True)||(AmountBuf[1]==De_Gps_Location_Flase))
		*ByteV=AmountBuf[1];	
	else
		return De_Erro_Gps_Data;
	return De_Suc_Gps; 		 				
}

static uint16 Parse_GPRMC_Lat(uint8 *LatHem,uint32 *Latitude,uint8 *GpsBuf,uint8 SizeofGpsBuf)			//γ�Ȱ����Լ�γ��ֵ
{	uint8 LatitudeLen;
	uint8 *AmountBuf,*AmountBuf1;
	uint32 Val,Val1;
	AmountBuf=SeekChar(GpsBuf,',',SizeofGpsBuf,De_Gps_Parse_Space_LatHem);
	if(AmountBuf==NULL)
		return De_Erro_Gps_Data;
	if((AmountBuf[1]==De_Gps_LatHem_N)||(AmountBuf[1]==De_Gps_LatHem_S)) 								//γ�ȱ������ϰ���
		*LatHem=AmountBuf[1];
	else
		return De_Erro_Gps_Data;
	AmountBuf=SeekChar(GpsBuf,',',SizeofGpsBuf,De_Gps_Parse_Space_Latitude);
	if(AmountBuf==NULL)
		return De_Erro_Gps_Data;
	AmountBuf++;
	AmountBuf1=SeekChar(GpsBuf,',',SizeofGpsBuf,De_Gps_Parse_Space_Latitude+1);
	if(AmountBuf==NULL)
		return De_Erro_Gps_Data; 
	LatitudeLen=AmountBuf1-AmountBuf;
	if(CN_st_Fun_AscNumber.JugeAscFloat(AmountBuf,LatitudeLen)!=0)
		return De_Erro_Gps_Data;
	*Latitude=CN_st_Fun_AscNumber.Asc2Float(AmountBuf,4,LatitudeLen);
	Val=(*Latitude/1000000)*1000000;
	Val1=*Latitude%1000000;
	Val1=Val1*100/60;
   	*Latitude=Val+Val1;
  	return De_Suc_Gps;
}

static uint16 Parse_GPRMC_Long(uint8 *LongHem,uint32 *Longitude,uint8 *GpsBuf,uint8 SizeofGpsBuf)		//���Ȱ����Լ�����ֵ
{	uint8 LongitudeLen;
	uint8 *AmountBuf,*AmountBuf1;
	uint32 Val,Val1;
	AmountBuf=SeekChar(GpsBuf,',',SizeofGpsBuf,De_Gps_Parse_Space_LongHem);
	if(AmountBuf==NULL)
		return De_Erro_Gps_Data;	
	if(AmountBuf==NULL)
		return De_Erro_Gps_Data;
	if((AmountBuf[1]==De_Gps_LongHem_E)||(AmountBuf[1]==De_Gps_LongHem_W)) 								//γ�ȱ������ϰ���
		*LongHem=AmountBuf[1];
	else
		return De_Erro_Gps_Data;

	AmountBuf=SeekChar(GpsBuf,',',SizeofGpsBuf,De_Gps_Parse_Space_Longitude);
	if(AmountBuf==NULL)
		return De_Erro_Gps_Data;
	AmountBuf++;
	AmountBuf1=SeekChar(GpsBuf,',',SizeofGpsBuf,De_Gps_Parse_Space_Longitude+1);
	if(AmountBuf==NULL)
		return De_Erro_Gps_Data; 
	LongitudeLen=AmountBuf1-AmountBuf;
	if(CN_st_Fun_AscNumber.JugeAscFloat(AmountBuf,LongitudeLen)!=0)
		return De_Erro_Gps_Data;
	*Longitude=CN_st_Fun_AscNumber.Asc2Float(AmountBuf,4,LongitudeLen);
	Val=(*Longitude/1000000)*1000000;
	Val1=*Longitude%1000000;
	Val1=Val1*100/60;
   	*Longitude=Val+Val1;
  	return De_Suc_Gps;
}

static uint16 Parse_GPRMC_Speed(uint32 *Speed,uint8 *GpsBuf,uint8 SizeofGpsBuf)						//�ٶ�
{ 	uint8 SpeedLen;
	uint8 *AmountBuf,*AmountBuf1;
	AmountBuf=SeekChar(GpsBuf,',',SizeofGpsBuf,De_Gps_Parse_Space_Speed);
	if(AmountBuf==NULL)
		return De_Erro_Gps_Data;
	AmountBuf++;
	AmountBuf1=SeekChar(GpsBuf,',',SizeofGpsBuf,De_Gps_Parse_Space_Speed+1);
	if(AmountBuf==NULL)
		return De_Erro_Gps_Data;
	SpeedLen=AmountBuf1-AmountBuf;
	if(CN_st_Fun_AscNumber.JugeAscFloat(AmountBuf,SpeedLen)!=0)
		return De_Erro_Gps_Data;
	*Speed=CN_st_Fun_AscNumber.Asc2Float(AmountBuf,1,SpeedLen);
	*Speed = (uint32)(*Speed*1825/1000);
  	return De_Suc_Gps;
}

static uint16 Parse_GPRMC_Angle(uint32 *Angle,uint8 *GpsBuf,uint8 SizeofGpsBuf)						//�ٶ�
{ 	uint8 AngleLen;
	uint8 *AmountBuf,*AmountBuf1;
	AmountBuf=SeekChar(GpsBuf,',',SizeofGpsBuf,De_Gps_Parse_Space_Angle);
	if(AmountBuf==NULL)
		return De_Erro_Gps_Data;
	AmountBuf++;
	AmountBuf1=SeekChar(GpsBuf,',',SizeofGpsBuf,De_Gps_Parse_Space_Angle+1);
	if(AmountBuf==NULL)
		return De_Erro_Gps_Data;
	AngleLen=AmountBuf1-AmountBuf;
	if(CN_st_Fun_AscNumber.JugeAscFloat(AmountBuf,AngleLen)!=0)
		return De_Erro_Gps_Data;
	*Angle=CN_st_Fun_AscNumber.Asc2Float(AmountBuf,1,AngleLen);
  	return De_Suc_Gps;
}


/*+++++++++++++++++++++++++++++++++++++++++++++++++++++GPGGA����+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/
/*������ʽ:	
		  $GPGGA+UTC(ʱ��)+γ��+γ�Ȱ���+����+���Ȱ���+GPS״̬+���Ǹ���+HDOPˮƽ��������+���θ߶�+������������Դ��ˮ׼��ĸ߶�+���ʱ��+���վID

*/


static uint16 Parse_GPGGA(st_Gps_Data_GPGGA	*ptst_Gps_Data_GPGGA,uint8 *GpsBuf,uint8 SizeofGpsBuf)	
{	if(Parse_GPGGA_StarNumber(&ptst_Gps_Data_GPGGA->StarNumber,GpsBuf,SizeofGpsBuf)!=De_Suc_Gps)
		return De_Erro_Gps_Data;
	if(Parse_GPGGA_Height(&ptst_Gps_Data_GPGGA->Height,GpsBuf,SizeofGpsBuf)!=De_Suc_Gps)
		return De_Erro_Gps_Data;
	return De_Suc_Gps;
}

//
static uint16 Parse_GPGGA_StarNumber(uint8 *StarNumber,uint8 *GpsBuf,uint8 SizeofGpsBuf)					//��ȡ���ǵ�����
{	uint8 StarNumberLen;
	uint8 *AmountBuf,*AmountBuf1;
	uint32 HexValue;
	AmountBuf=SeekChar(GpsBuf,',',SizeofGpsBuf,De_Gps_Parse_Space_StarNumber);
	if(AmountBuf==NULL)
		return De_Erro_Gps_Data;
	AmountBuf++;
	AmountBuf1=SeekChar(GpsBuf,',',SizeofGpsBuf,De_Gps_Parse_Space_StarNumber+1);
	if(AmountBuf==NULL)
		return De_Erro_Gps_Data;
	StarNumberLen=AmountBuf1-AmountBuf;
	if(CN_st_Fun_AscNumber.JugeAscFloat(AmountBuf,StarNumberLen)!=0)
		return De_Erro_Gps_Data;
	HexValue=CN_st_Fun_AscNumber.Asc2Float(AmountBuf,0,StarNumberLen);
	*StarNumber=HexValue;
  	return De_Suc_Gps;	
}
static uint16 Parse_GPGGA_Height(int32 *Height,uint8 *GpsBuf,uint8 SizeofGpsBuf)			//��ȡ���θ߶�
{	int8 Flag;
	uint8 StarNumberLen;
	uint8 *AmountBuf,*AmountBuf1;
	uint32 HexValue;
	AmountBuf=SeekChar(GpsBuf,',',SizeofGpsBuf,De_Gps_Parse_Space_Height);
	if(AmountBuf==NULL)
		return De_Erro_Gps_Data;
	AmountBuf++;
	AmountBuf1=SeekChar(GpsBuf,',',SizeofGpsBuf,De_Gps_Parse_Space_Height+1);
	if(AmountBuf==NULL)
		return De_Erro_Gps_Data;
	StarNumberLen=AmountBuf1-AmountBuf;
	Flag=1;
	if(AmountBuf[0]=='-')						//������Ϊ����
	{	Flag=-1;
		StarNumberLen-=1;
		AmountBuf++;		
	}
	if(CN_st_Fun_AscNumber.JugeAscFloat(AmountBuf,StarNumberLen)!=0)
		return De_Erro_Gps_Data;
	HexValue=CN_st_Fun_AscNumber.Asc2Float(AmountBuf,1,StarNumberLen);
	*Height=Flag*HexValue;				
	return De_Suc_Gps;
} 
static	uint8 *SeekChar(uint8 *Buf,uint8 CharV,uint8 SizeofBuf,uint8 Number) 	   
{	uint8 i,j;
	for(i=0,j=0;i<SizeofBuf;i++)
	{	if(Buf[i]!=CharV)
			continue;
		j++;
		if(j<Number)		
			continue;
		return Buf+i;
	}
	return NULL;
}

#endif


	 































