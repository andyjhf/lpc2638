/*=======================================================================NandFlash 页大小为256+256+16，块大小为16K===============================================================================*/
#define De_NandFlash512_Compiler
#include "_NandFlash512.h"
static uint16 Init(void)
{	De_NandFlash_HardWare_Data_RB_In;
	De_NandFlash_HardWare_RE_Up;
	De_NandFlash_HardWare_CE_Up;
   	De_NandFlash_HardWare_WE_Up;
	De_NandFlash_HardWare_ALE_Down;
	De_NandFlash_HardWare_CLE_Down;
	De_NandFlash_HardWare_Data_Out;
	De_NandFlash_HardWare_CE_Up;	
	return De_Suc_NandFlash;
}
static uint16 ReadID(uint8 *Buf)
{	uint8 i;
	De_NandFlash_HardWare_ReSet;
	De_NandFlash_HardWare_Data_RB_In;
	De_NandFlash_HardWare_RE_Up;
	De_NandFlash_HardWare_CE_Up;
   	De_NandFlash_HardWare_WE_Up;
	De_NandFlash_HardWare_ALE_Down;
	De_NandFlash_HardWare_CLE_Down;
	De_NandFlash_HardWare_Data_Out;
	De_NandFlash_HardWare_CE_Down;
	De_NandFlash_HardWare_CLE_Up;
	WriteData(De_NandFlash_Order_ReadID);
	De_NandFlash_HardWare_CLE_Down;

	De_NandFlash_HardWare_ALE_Up;
	WriteData(0);
	De_NandFlash_HardWare_Data_In;
	De_NandFlash_HardWare_ALE_Down;
	for(i=0;i<2;i++)
		*(Buf++)=ReadData();
	*(Buf++)=0xff;
	De_NandFlash_HardWare_CE_Up;
   	return De_Suc_NandFlash;
}

static uint16 LookBad(uint32 Page,uint8 *BadFlag)
{	uint16 Result;
	uint8 Byte;
	if((Result=FMrdPg517(Page,517,1,512,&Byte))!=De_Suc_NandFlash)
		return Result;
	if(Byte!=0xff)
	{	*BadFlag=De_Flash_Bad_Flag;
		return De_Suc_NandFlash;
	}
	if((Result=FMrdPg517(Page+1,517,1,512,&Byte))!=De_Suc_NandFlash)
		return Result;
	if(Byte!=0xff)
	{	*BadFlag=De_Flash_Bad_Flag;
		return De_Suc_NandFlash;
	}
	*BadFlag=De_Flash_Bad_NoFlag;
	return De_Suc_NandFlash;	
}
static uint16 JugeByte(uint32 Page,uint16 Col,uint16 iSize,uint16 PageSize,uint8 Byte)
{	uint16 i;
	PageSize=PageSize;
	dzflash(Page,Col,De_NandFlash_Read);
	while(De_NandFlash_HardWare_Data_RB_In_Data==0);
	for(i=0;i<iSize;i++)
	{	if(Byte!=ReadData())
		{	De_NandFlash_HardWare_ALE_Down;
			De_NandFlash_HardWare_CE_Up;
			return De_Erro_NandFlash_NoEven; 
		}
	}
	De_NandFlash_HardWare_ALE_Down;
	De_NandFlash_HardWare_CE_Up;
	return De_Suc_NandFlash;
}

static uint16 JugeBuf(uint32 Page,uint16 Col,uint16 iSize,uint16 PageSize,uint8 *Buf)
{	uint16 i;
	PageSize=PageSize;
	dzflash(Page,Col,De_NandFlash_Read);
	while(De_NandFlash_HardWare_Data_RB_In_Data==0);
	for(i=0;i<iSize;i++)
	{	if(Buf[i]!=ReadData())	
		{	De_NandFlash_HardWare_ALE_Down;
			De_NandFlash_HardWare_CE_Up;
			return De_Erro_NandFlash_NoEven; 
		}
	}
	De_NandFlash_HardWare_ALE_Down;
	De_NandFlash_HardWare_CE_Up;
	return De_Suc_NandFlash;
}
					
static uint16 Ease(uint32 Page,uint16 PageSize)
{	uint8 Byte2;
	PageSize=PageSize;
	De_NandFlash_HardWare_Data_RB_In;
	De_NandFlash_HardWare_RE_Up;
	De_NandFlash_HardWare_CE_Up;
   	De_NandFlash_HardWare_WE_Up;
	De_NandFlash_HardWare_ALE_Down;
	De_NandFlash_HardWare_CLE_Down;
	De_NandFlash_HardWare_Data_Out;
	De_NandFlash_HardWare_CE_Down;
	De_NandFlash_HardWare_CLE_Up;  
	WriteData(De_NandFlash_Order_EaseStep);	
	De_NandFlash_HardWare_CLE_Down;
	De_NandFlash_HardWare_ALE_Up;
	WriteData(Page&0xff);
	WriteData((Page>>8)&0xff);
	WriteData((Page>>16)&0xff);
	De_NandFlash_HardWare_ALE_Down;
	De_NandFlash_HardWare_CLE_Up;
	WriteData(De_NandFlash_Order_Ease);
	De_NandFlash_HardWare_CLE_Down;
	while(De_NandFlash_HardWare_Data_RB_In_Data==0);
	De_NandFlash_HardWare_CLE_Up;
	WriteData(De_NandFlash_Order_ProgramOver);
	De_NandFlash_HardWare_CLE_Down;
	Byte2=ReadData();
	De_NandFlash_HardWare_CE_Up;
	if(Byte2&0x01)
		return De_Erro_NandFlash_Write;
	return De_Suc_NandFlash;
}
static uint16 FMwrPg(uint32 Page,uint16 Col,uint16 iSize,uint16 PageSize,uint8 *buf)
{	uint8 Byte2;
	uint16 i;
	PageSize=PageSize;
	dzflash(Page,Col,De_NandFlash_Write);
	for(i=0;i<iSize;i++)
		WriteData(buf[i]);
	De_NandFlash_HardWare_CLE_Up;
	WriteData(De_NandFlash_Order_Latch);
	De_NandFlash_HardWare_CLE_Down;				
	while(De_NandFlash_HardWare_Data_RB_In_Data==0);
	De_NandFlash_HardWare_CLE_Up;
	WriteData(De_NandFlash_Order_ProgramOver);
	De_NandFlash_HardWare_CLE_Down;
	Byte2=ReadData();
	De_NandFlash_HardWare_CE_Up;
	if(Byte2&0x01)
		return De_Erro_NandFlash_Write;
	return De_Suc_NandFlash;
}
static uint16 FMrdPg517(uint32 Page,uint16 Col,uint16 SizeofBuf,uint16 PageSize,uint8 *Buf)
{	uint16 i;
	PageSize=PageSize;
	dzflash(Page,Col,De_NandFlash_Read);
	while(De_NandFlash_HardWare_Data_RB_In_Data==0);
	for(i=0;i<SizeofBuf;)
		Buf[i++]=ReadData();
	De_NandFlash_HardWare_ALE_Down;
	De_NandFlash_HardWare_CE_Up;
	return De_Suc_NandFlash;
}

/*===========================================================================底层支持函数=======================================================================================================*/
static void dzflash(uint32 Page,uint16 Col,uint8 wtORrd)
{	uint8 col0,comd;
 	if (Col>511)
  	{	comd=0x50;
	   	col0=Col-512;
   	}   
    else if(Col>255)
	{  	comd=0x01;
	    col0=Col-256;
	}
	else
	{	comd=0x00;
	    col0=Col;
	}
	De_NandFlash_HardWare_Data_RB_In;
	De_NandFlash_HardWare_RE_Up;
	De_NandFlash_HardWare_CE_Up;
   	De_NandFlash_HardWare_WE_Up;
	De_NandFlash_HardWare_ALE_Down;
	De_NandFlash_HardWare_CLE_Down;
	De_NandFlash_HardWare_Data_Out;
	De_NandFlash_HardWare_CE_Down;
	De_NandFlash_HardWare_CLE_Up;  
	WriteData(comd);
	De_NandFlash_HardWare_CLE_Down; 
	if(wtORrd==De_NandFlash_Write)
	{	De_NandFlash_HardWare_CLE_Up;
		WriteData(De_NandFlash_Order_Program);	
		De_NandFlash_HardWare_CLE_Down;
	}
	De_NandFlash_HardWare_ALE_Up;
	WriteData(col0);
	WriteData(Page&0xff);
	WriteData((Page>>8)&0xff);
	WriteData((Page>>16)&0xff);
	De_NandFlash_HardWare_Data_In;
	De_NandFlash_HardWare_ALE_Down;
}

static void WriteData(uint8 Data)
{	uint32 Data1;
	Data1=0x00000000+(~Data);
	De_NandFlash_HardWare_Data_Out;
	De_NandFlash_HardWare_Data_Output_High=Data;
	De_NandFlash_HardWare_Data_Output_Low=Data1;
	De_NandFlash_HardWare_WE_Down;
	De_NandFlash_HardWare_WE_Up;
}
static uint8 ReadData(void)
{	uint8 Byte;
	De_NandFlash_HardWare_Data_In;
	De_NandFlash_HardWare_RE_Down;
	Byte=(De_NandFlash_HardWare_Data_Input&0xff);
	De_NandFlash_HardWare_RE_Up;
   	return Byte;
}







