/*============================================底层支持==========================================================*/
#define De_Flash_Compiler
#include "_Flash.h"
static uint16 Open(st_Flash_Chip_Features	*ptst_Flash_Chip_Features)
{	uint8 Buf[3];

	uint16 Result;
	uint16 FlagCut;
	if((Result=ptst_Flash_Chip_Features->ptst_Fun_PhyFlash->Init())!=De_Suc_PhyFlash)
		return Result;
	if((Result=ptst_Flash_Chip_Features->ptst_Fun_PhyFlash->ReadID(Buf))!=De_Suc_PhyFlash)
		return Result;	
	if(CompareBuf(ptst_Flash_Chip_Features->ID,Buf,sizeof(Buf))!=0)
		return De_Erro_PhyFlash_ID;
	if((Result=ptst_Flash_Chip_Features->ptst_Fun_PhyFlash->Read(De_Flash_FlashInitFlagAddree/ptst_Flash_Chip_Features->SectionSize,
	De_Flash_FlashInitFlagAddree%ptst_Flash_Chip_Features->SectionSize,2,ptst_Flash_Chip_Features->SectionSize,(uint8 *)&FlagCut))!=De_Suc_PhyFlash)
		return Result;		
	if(FlagCut==De_Flash_Format_Flag) 								//此芯片已经初始化
		return De_Suc_PhyFlash;	
	return FormatFlash(ptst_Flash_Chip_Features);
}

static uint16 FormatFlash(st_Flash_Chip_Features	*ptst_Flash_Chip_Features)
{	uint16 i,Result,j;
	uint8 BadFlag;
	if((Result=ptst_Flash_Chip_Features->ptst_Fun_PhyFlash->Ease(0,ptst_Flash_Chip_Features->SectionSize))!=De_Suc_PhyFlash)
		return Result;
	for(i=1;i<ptst_Flash_Chip_Features->BlockNumber;i++)
	{	if(ptst_Flash_Chip_Features->ptst_Fun_PhyFlash->LookBad!=NULL)
		{	if((Result=ptst_Flash_Chip_Features->ptst_Fun_PhyFlash->LookBad(i*ptst_Flash_Chip_Features->SectionNumber,&BadFlag))!=De_Suc_PhyFlash)
				return Result;
			if(BadFlag==De_Flash_Bad_Flag) 			//此块出厂前有坏块标志
			{	if((Result=CreatBad(i,ptst_Flash_Chip_Features))!=De_Suc_PhyFlash)				//坏块标志
					return Result;
				continue;
			}
		}
		if((Result=ptst_Flash_Chip_Features->ptst_Fun_PhyFlash->Ease(i*ptst_Flash_Chip_Features->SectionNumber,ptst_Flash_Chip_Features->SectionSize))!=De_Suc_PhyFlash)
		{	if((Result=CreatBad(i,ptst_Flash_Chip_Features))!=De_Suc_PhyFlash)				//坏块标志
				return Result;
			continue;
		}
		for(j=0;j<ptst_Flash_Chip_Features->SectionNumber;j++)
		{	if((Result=ptst_Flash_Chip_Features->ptst_Fun_PhyFlash->JugeByte(i*ptst_Flash_Chip_Features->SectionNumber+j,0,ptst_Flash_Chip_Features->SectionSize,
			ptst_Flash_Chip_Features->SectionSize,0xff))!=De_Suc_PhyFlash)
				break;
		}
		if(j!=ptst_Flash_Chip_Features->SectionNumber)
		{	if((Result=CreatBad(i,ptst_Flash_Chip_Features))!=De_Suc_PhyFlash)				//坏块标志
				return Result;;
			continue;
		}
	}
	Result=De_Flash_Format_Flag;
	return ptst_Flash_Chip_Features->ptst_Fun_PhyFlash->Write(De_Flash_FlashInitFlagAddree/ptst_Flash_Chip_Features->SectionSize,
	De_Flash_FlashInitFlagAddree%ptst_Flash_Chip_Features->SectionSize,2,ptst_Flash_Chip_Features->SectionSize,
	(uint8 *)&Result);
}
static uint16 CreatBad(uint16 BlockNumber,st_Flash_Chip_Features	*ptst_Flash_Chip_Features)
{	uint32 Addree,Page;
	uint16 i,Col;
	uint16 Result;
	uint8 Buf[2];
	for(i=0;i<De_Flash_Bad_Number;i++)
	{	Addree=De_Flash_BadBlock_Start+(i*2);
		Page=Addree/ptst_Flash_Chip_Features->SectionSize;
		Col=Addree%ptst_Flash_Chip_Features->SectionSize;
		if((Result=ptst_Flash_Chip_Features->ptst_Fun_PhyFlash->JugeByte(Page,Col,2,ptst_Flash_Chip_Features->SectionSize,0xff))==De_Suc_PhyFlash)
			break;
   	}
	if(i==De_Flash_Bad_Number)
		return De_Erro_Flash_Bad_Over;
	Buf[0]=((BlockNumber>>8)&0xff);Buf[1]=(BlockNumber&0xff);
	return  ptst_Flash_Chip_Features->ptst_Fun_PhyFlash->Write(Page,Col,sizeof(Buf),ptst_Flash_Chip_Features->SectionSize,
	Buf);
}

static uint16 JugeFlash(uint32 Addree,uint16 SizeofBuf,uint8 Byte,st_Flash_Chip_Features	*ptst_Flash_Chip_Features) 	//判断FLASH
{	uint32 Page;
	uint16 Result,Col,Size,i;
	for(i=0;i<SizeofBuf;i+=Size)
	{	Page=(Addree+i)/ptst_Flash_Chip_Features->SectionSize;
		Col=(Addree+i)%ptst_Flash_Chip_Features->SectionSize;	
		Size=ptst_Flash_Chip_Features->SectionSize-Col;
		if(Size>(SizeofBuf-i)) 			
			Size=(SizeofBuf-i);
		if((Result=ptst_Flash_Chip_Features->ptst_Fun_PhyFlash->JugeByte(Page,Col,Size,ptst_Flash_Chip_Features->SectionSize,Byte))!=De_Suc_PhyFlash)
			return Result;
	}
	return De_Suc_PhyFlash;	
}

static uint16 WriteFlash(uint32 Addree,uint16 SizeofBuf,uint8 *Buf,st_Flash_Chip_Features	*ptst_Flash_Chip_Features) //写FLASH
{	uint32 Page;
	uint16 Result,Col,Size,i;
	for(i=0;i<SizeofBuf;i+=Size)
	{	Page=(Addree+i)/ptst_Flash_Chip_Features->SectionSize;
		Col=(Addree+i)%ptst_Flash_Chip_Features->SectionSize;	
		Size=ptst_Flash_Chip_Features->SectionSize-Col;
		if(Size>(SizeofBuf-i)) 			
			Size=(SizeofBuf-i);
		if((Result=ptst_Flash_Chip_Features->ptst_Fun_PhyFlash->Write(Page,Col,Size,
		ptst_Flash_Chip_Features->SectionSize,Buf+i))!=De_Suc_PhyFlash)
			return Result;
		if((Result=ptst_Flash_Chip_Features->ptst_Fun_PhyFlash->JugeBuf(Page,Col,Size,
		ptst_Flash_Chip_Features->SectionSize,Buf+i))!=De_Suc_PhyFlash)
			return Result;
	}
	return De_Suc_PhyFlash;
}

static uint16 ReadFlash(uint32 Addree,uint16 SizeofBuf,uint8 *Buf,st_Flash_Chip_Features	*ptst_Flash_Chip_Features) 		//读FLASH
{	uint32 Page;
	uint16 Result,Col,Size,i;	
	for(i=0;i<SizeofBuf;i+=Size)
	{	Page=(Addree+i)/ptst_Flash_Chip_Features->SectionSize;
		Col=(Addree+i)%ptst_Flash_Chip_Features->SectionSize;	
		Size=ptst_Flash_Chip_Features->SectionSize-Col;
		if(Size>(SizeofBuf-i)) 				//
			Size=(SizeofBuf-i);
		if((Result=ptst_Flash_Chip_Features->ptst_Fun_PhyFlash->Read(Page,Col,Size,
		ptst_Flash_Chip_Features->SectionSize,Buf+i))!=De_Suc_PhyFlash)
			return Result;
	}
	return De_Suc_PhyFlash;	
}
static uint16 EaseFlash(uint32 Addree,st_Flash_Chip_Features	*ptst_Flash_Chip_Features)
{	uint32 Page;
	Page=Addree/ptst_Flash_Chip_Features->SectionSize;
	return ptst_Flash_Chip_Features->ptst_Fun_PhyFlash->Ease(Page,ptst_Flash_Chip_Features->SectionSize);
}

static uint16 CompareBuf(uint8 *Buf1,uint8 *Buf2,uint32 SizeofBuf)					//避免编译器不一样造成问题
{	uint32 i;
	for(i=0;i<SizeofBuf;i++)
	{	if(Buf1[i]!=Buf2[i])
			return 1;
	}
	return 0;
}
