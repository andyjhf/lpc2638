#define De_SpiFlash512_Compiler
#include "_SpiFlash512.h"
/*========================================================================SPI Flash===============================================================================================================*/
static uint16 Init(void)
{	return CN_st_Fun_Spi.Open();
}


static uint16 ReadID(uint8 *Buf)
{	uint8 Buf1[1];
	CN_st_Fun_Spi.Start(CE_Low,CE_High);
	Buf1[0]=De_NorFlash_Comand_JedecID;	
	CN_st_Fun_Spi.Write(Buf1,sizeof(Buf1));
	CN_st_Fun_Spi.Read(Buf,3);
	CN_st_Fun_Spi.End(CE_High);
	return De_Suc_SpiFlash;
}
static uint16 JugeByte(uint32 Page,uint16 Col,uint16 iSize,uint16 PageSize,uint8 Byte)
{	uint8 Buf[5];
	uint32 Addree;
	uint16 Erro;
	Addree=Page*PageSize+Col;
	CN_st_Fun_Spi.Start(CE_Low,CE_High);
	Buf[0]=De_NorFlash_Comand_FastRead;
	Buf[1]=((Addree&0xffffff)>>16);
	Buf[2]=((Addree&0xffff)>>8);
	Buf[3]=(Addree&0xff);
	Buf[4]=0xff;
	CN_st_Fun_Spi.Write(Buf,sizeof(Buf));		
	Erro=CN_st_Fun_Spi.JugeByte(Byte,iSize);
	CN_st_Fun_Spi.End(CE_High);
	return Erro;
}
static uint16 JugeBuf(uint32 Page,uint16 Col,uint16 iSize,uint16 PageSize,uint8 *Buf)
{	uint8 Buf1[5];
	uint32 Addree;
	uint16 Erro;
	Addree=Page*PageSize+Col;
	CN_st_Fun_Spi.Start(CE_Low,CE_High);
	Buf1[0]=De_NorFlash_Comand_FastRead;
	Buf1[1]=((Addree&0xffffff)>>16);
	Buf1[2]=((Addree&0xffff)>>8);
	Buf1[3]=(Addree&0xff);
	Buf1[4]=0xff;
	CN_st_Fun_Spi.Write(Buf1,sizeof(Buf1));		
	Erro=CN_st_Fun_Spi.JugeBuf(Buf,iSize);
	CN_st_Fun_Spi.End(CE_High);
	return Erro;
}
static uint16 Ease(uint32 Page,uint16 PageSize)
{	uint8 Buf[4];
	uint32 Addree;
	uint16 Erro;
	Erro=WriteOpen();
	if(Erro!=De_Suc_SpiFlash)
		return Erro;
	Addree=Page*PageSize;
	CN_st_Fun_Spi.Start(CE_Low,CE_High);
	Buf[0]=De_NorFlash_Comand_Erase;
	Buf[1]=((Addree&0xffffff)>>16);
	Buf[2]=((Addree&0xffff)>>8);
	Buf[3]=(Addree&0xff);
	CN_st_Fun_Spi.Write(Buf,sizeof(Buf));
	CN_st_Fun_Spi.End(CE_High);
	return WriteClose();
}
static uint16 Write(uint32 Page,uint16 Col,uint16 iSize,uint16 PageSize,uint8 *Buf)
{	uint8 Buf1[4];
	uint32 Addree;
	uint16 Erro;			
   	Erro=WriteOpen();
	if(Erro!=De_Suc_SpiFlash)
		return Erro;
	Addree=Page*PageSize+Col;
	CN_st_Fun_Spi.Start(CE_Low,CE_High);
	Buf1[0]=De_NorFlash_Comand_Program;
	Buf1[1]=((Addree&0xffffff)>>16);
	Buf1[2]=((Addree&0xffff)>>8);
	Buf1[3]=(Addree&0xff);
	CN_st_Fun_Spi.Write(Buf1,sizeof(Buf1));
	CN_st_Fun_Spi.Write(Buf,iSize);
	CN_st_Fun_Spi.End(CE_High);
	return WriteClose();	
}
static uint16 Read(uint32 Page,uint16 Col,uint16 SizeofBuf,uint16 PageSize,uint8 *Buf)
{	uint8 Buf1[5];	
	uint32 Addree;
	Addree=Page*PageSize+Col;
	CN_st_Fun_Spi.Start(CE_Low,CE_High);
	Buf1[0]=De_NorFlash_Comand_FastRead;
	Buf1[1]=((Addree&0xffffff)>>16);
	Buf1[2]=((Addree&0xffff)>>8);
	Buf1[3]=(Addree&0xff);
	Buf1[4]=0xff;
	CN_st_Fun_Spi.Write(Buf1,5);		
	CN_st_Fun_Spi.Read(Buf,SizeofBuf);
	CN_st_Fun_Spi.End(CE_High);
	return De_Suc_SpiFlash;
}
/*=======================================================================================为Flash服务================================================================================================*/
static uint16 WriteClose(void)
{	uint16 Erro;
	uint8 Status;
	Erro=ReadStatusOutTime(&Status);
	if(Erro!=De_Suc_SpiFlash)
		return Erro;
	if(Status&De_NorFlash_Sta_Wel)
	{ 	Erro=WriteDisable();
		if(Erro!=De_Suc_SpiFlash)
			return Erro;
	}		
	return De_Suc_SpiFlash;
}



static uint16 WriteOpen(void)											//写打开
{	uint8 Status;
	uint16 Erro;
	Erro=ReadStatusOutTime(&Status);
	if(Erro!=De_Suc_SpiFlash)
		return Erro;
	if((Status&De_NorFlash_Sta_Wel)==0)
	{ 	Erro=WriteEnable();
		if(Erro!=De_Suc_SpiFlash)
			return Erro;
	}
	Status|=De_NorFlash_Sta_Wel;
	if(!((Status&De_NorFlash_Sta_Bp0)||(Status&De_NorFlash_Sta_Bp1)||(Status&De_NorFlash_Sta_Bp2)))
		return De_Suc_SpiFlash;
	Status=(Status&(~De_NorFlash_Sta_Bp0)&(~De_NorFlash_Sta_Bp1)&(~De_NorFlash_Sta_Bp2));
	Erro=WriteStatus(Status);
	return Erro;
}
static uint16 WriteStatus(uint8 ByteV)
{	uint16 Erro;
	uint8 Buf[2];
	uint8 i,Status;
	for(i=0;i<De_NorFlash_SoftErro_Number;i++)
	{	Buf[0]=De_NorFlash_Comand_WriteStatus;
		Buf[1]=ByteV;
		CN_st_Fun_Spi.Start(CE_Low,CE_High);
	    CN_st_Fun_Spi.Write(Buf,sizeof(Buf));
		CN_st_Fun_Spi.End(CE_High);
		Erro=ReadStatusOutTime(&Status);
		if(Erro!=De_Suc_SpiFlash)
			return Erro;
		if(Status==ByteV)
			return De_Suc_SpiFlash;
	}
	return De_Erro_SpiFlash_WriteStatus;
}
static uint16 WriteEnable(void)
{	uint16 Erro;
	uint8 i,Status;
	uint8 Buf[1];
	for(i=0;i<De_NorFlash_SoftErro_Number;i++)
	{	CN_st_Fun_Spi.Start(CE_Low,CE_High);	
		Buf[0]=De_NorFlash_Comand_Enable;
	    CN_st_Fun_Spi.Write(Buf,1);
		CN_st_Fun_Spi.End(CE_High);
		Erro=ReadStatusOutTime(&Status);
		if(Erro!=De_Suc_SpiFlash)
			return Erro;
		if(Status&De_NorFlash_Sta_Wel)
			return De_Suc_SpiFlash;
	}
	return De_Erro_SpiFlash_WriteEnable;
}


static uint16 WriteDisable(void)
{	uint16 Erro;
	uint8 i,Status;
	uint8 Buf[1];
	for(i=0;i<De_NorFlash_SoftErro_Number;i++)
	{	CN_st_Fun_Spi.Start(CE_Low,CE_High);	
		Buf[0]=De_NorFlash_Comand_Disable;
	    CN_st_Fun_Spi.Write(Buf,1);
		CN_st_Fun_Spi.End(CE_High);
		Erro=ReadStatusOutTime(&Status);
		if(Erro!=De_Suc_SpiFlash)
			return Erro;
		if((Status&De_NorFlash_Sta_Wel)==0)
			return De_Suc_SpiFlash;
	}
	return De_Erro_SpiFlash_WriteDisable;
}
 

static uint16 ReadStatusOutTime(uint8 *Status)
{	uint32 i;
	for(i=0;i<De_SpiFlash_OutTime;i++)
	{	*Status=ReadStatus();
		if((*Status&De_NorFlash_Sta_Busy)==0x00)	
			return	De_Suc_SpiFlash; 
	}
	return De_Erro_SpiFlash_TimeOut;
}





static uint8 ReadStatus(void)
{	uint8 Buf[1];
	Buf[0]=De_NorFlash_Comand_ReadStatus;
	CN_st_Fun_Spi.Start(CE_Low,CE_High);	
	CN_st_Fun_Spi.Write(Buf,sizeof(Buf));
	CN_st_Fun_Spi.Read(Buf,sizeof(Buf));
	CN_st_Fun_Spi.End(CE_High);
	return Buf[0];
}
static void CE_High(void)
{	De_IO_NorFlash_CE_High;
}

static void CE_Low(void)
{	De_IO_NorFlash_CE_Low;	
}
