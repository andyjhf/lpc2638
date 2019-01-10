#define De_rwflashlgc_Compiler
#include "rwflashlgc.h"
#ifdef	De_Compiler_File_rwflashlgc
/*=========================================================底层支持======================================================================================*/
/*	函数功能:打开器件逻辑层
		入口参数:	无
		返回值:	 各个器件的驱动以及基本参数，详见<st_NorFlash>定义		
*/
static st_NorFlash	* Open(void)                   
{	uint16 i;                              
	for(i=0;i<sizeof(CN_st_Flash_Chip_Features)/sizeof(st_Flash_Chip_Features);i++)
	{	CN_st_NorFlash.CN_st_Flash_Chip_Features[i]=NULL;
		if(CN_st_Fun_PhyFlash.Open((st_Flash_Chip_Features	*)&CN_st_Flash_Chip_Features[i])!=De_Suc_PhyFlash)
			continue;
		CN_st_NorFlash.CN_st_Flash_Chip_Features[i]=(st_Flash_Chip_Features	*)&CN_st_Flash_Chip_Features[i];				
	}
	return &CN_st_NorFlash;	 										//返回句柄给文件系统用，包含所支持的所有器件
}
/*	函数功能:读取指定器件数据，逻辑层
			入口参数:	输入参数	Chip	器件号码
									Addree	所读取的逻辑地址
									SizeofBuf	所读取的字节数量

						输出参数	Buf		所读取的数据
			返回值:	 0:成功			非0	<见错误代码表>	
	*/
static uint16 Read(uint8 Chip,uint32 Addree,uint16 SizeofBuf,uint8 *Buf)	//文件不能跨器件
{   uint16 i,Block,Offset;
	uint32 AddreeL;
	if(CN_st_NorFlash.CN_st_Flash_Chip_Features[Chip]==NULL)
		return De_Erro_Flash_NoOpen;
	if((Addree+SizeofBuf)>(uint32 )(CN_st_Flash_Chip_Features[Chip].BlockSize*CN_st_Flash_Chip_Features[Chip].BlockNumberUse))
		return De_Erro_Flash_AddreeOut;    
	for(i=0;i<SizeofBuf;i+=Offset,Addree+=Offset)
	{  	AddreeL=Addree;
		Block=AddreeL/CN_st_Flash_Chip_Features[Chip].BlockSize;
		Offset=AddreeL%CN_st_Flash_Chip_Features[Chip].BlockSize;
		Lgc2Phy((st_Flash_Chip_Features	*)&CN_st_Flash_Chip_Features[Chip],Block,&Block);
		AddreeL=Block*CN_st_Flash_Chip_Features[Chip].BlockSize+Offset;
		Offset=CN_st_Flash_Chip_Features[Chip].BlockSize-Offset;
		if(Offset+i>SizeofBuf)
			Offset=SizeofBuf-i;
		CN_st_Fun_PhyFlash.Read(AddreeL,Offset,Buf+i,(st_Flash_Chip_Features	*)&CN_st_Flash_Chip_Features[Chip]);          
	}
	return De_Suc_FlashL;                                      
}
	/*	函数功能:写指定器件数据，上层不需要查看是否要擦除，自己会判断逻辑层
			入口参数:	输入参数	Chip	器件号码
									Addree	所写的逻辑地址
									SizeofBuf	所写的字节数量

									Buf		所写的数据
			返回值:	 0:成功			非0	<见错误代码表>	
	*/
static uint16 Write(uint8 Chip,uint32 Addree,uint16 SizeofBuf,uint8 *Buf) //写数据
{ 	uint16 i,Offset,Result;
	if(CN_st_NorFlash.CN_st_Flash_Chip_Features[Chip]==NULL)
		return De_Erro_Flash_NoOpen;
	if((Addree+SizeofBuf)>(uint32 )(CN_st_Flash_Chip_Features[Chip].BlockSize*CN_st_Flash_Chip_Features[Chip].BlockNumberUse))
		return De_Erro_Flash_AddreeOut; 
	for(i=0;i<SizeofBuf;i+=Offset,Addree+=Offset)
	{	Offset=Addree%CN_st_Flash_Chip_Features[Chip].BlockSize;
	    Offset=CN_st_Flash_Chip_Features[Chip].BlockSize-Offset;
		if((Offset+i)>SizeofBuf)
			Offset=SizeofBuf-i;	
		Result=WriteBlock(Chip,Addree,Offset,Buf+i);
		if(Result!=De_Suc_FlashL)
			return Result;
	} 
	return De_Suc_FlashL;          
}
/*	函数功能:擦除指定器件的逻辑块
			入口参数:	输入参数	Chip	器件号码
									Addree	所擦除的逻辑地址
			返回值:	 0:成功			非0	<见错误代码表>	
	*/
static uint16 Ease(uint8 Chip,uint32 Addree)
{	uint16 Block;
	if(CN_st_NorFlash.CN_st_Flash_Chip_Features[Chip]==NULL)
		return De_Erro_Flash_NoOpen;
	if(Addree>(uint32 )(CN_st_Flash_Chip_Features[Chip].BlockSize*CN_st_Flash_Chip_Features[Chip].BlockNumberUse))
		return De_Erro_Flash_AddreeOut; 
	Block=Addree/CN_st_Flash_Chip_Features[Chip].BlockSize;
	Lgc2Phy((st_Flash_Chip_Features	*)&CN_st_Flash_Chip_Features[Chip],Block,&Block);
	Addree=(uint32 )Block*CN_st_Flash_Chip_Features[Chip].BlockSize;
	return CN_st_Fun_PhyFlash.Ease(Addree,(st_Flash_Chip_Features	*)&CN_st_Flash_Chip_Features[Chip]);
}

/*================================================================================================================================*/
static uint16 Lgc2Phy(st_Flash_Chip_Features	*ptst_Flash_Chip_Features,uint16 LogicBlk,uint16 *PhyBlk)
{	uint16 Result,Block;
	if((Result=CN_st_Fun_PhyFlash.Read(De_Flash_BadBlock_Start,De_Flash_Bad_Number*2,X_BUF,ptst_Flash_Chip_Features))
		!=De_Suc_PhyFlash)
		return Result;
	for(Result=0;Result<De_Flash_Bad_Number;)
	{	Block=X_BUF[Result*2]*0x100+X_BUF[Result*2+1];
		if(Block==0xffff)
			break;
		if(LogicBlk==Block)
		{	LogicBlk=ptst_Flash_Chip_Features->BlockNumberUse+Result+1;
			Result=0;
			continue;
		}
		Result++;
	}			
	*PhyBlk=LogicBlk;
	return De_Suc_FlashL;
}

static uint16 WriteBlock(uint8 Chip,uint32 Addree,uint16 SizeofBuf,uint8 *Buf)												//写文件
{	uint16 Result,Offset,Block,AimBlock;
	Block=Addree/CN_st_Flash_Chip_Features[Chip].BlockSize;
	Offset=Addree%CN_st_Flash_Chip_Features[Chip].BlockSize;
	Lgc2Phy((st_Flash_Chip_Features	*)&CN_st_Flash_Chip_Features[Chip],Block,&Block);
	Addree=Block*CN_st_Flash_Chip_Features[Chip].BlockSize+Offset;
	Result=CN_st_Fun_PhyFlash.Juge(Addree,SizeofBuf,0xff,(st_Flash_Chip_Features	*)&CN_st_Flash_Chip_Features[Chip]);
	if(Result==De_Suc_PhyFlash) 			//是否是全0XFF
	{	Result=CN_st_Fun_PhyFlash.Write(Addree,SizeofBuf,Buf,(st_Flash_Chip_Features	*)&CN_st_Flash_Chip_Features[Chip]);	
	   	if(Result==De_Suc_PhyFlash)
			return De_Suc_PhyFlash;
	}
	for(;;)
	{	AimBlock=CN_st_Flash_Chip_Features[Chip].BlockNumberUse+1;
		Lgc2Phy((st_Flash_Chip_Features	*)&CN_st_Flash_Chip_Features[Chip],AimBlock,&AimBlock);		
		if(CopyBlock(Chip,Block,AimBlock,Buf,Offset,SizeofBuf)!=De_Suc_FlashL)
		{	if(CN_st_Fun_PhyFlash.CreatBad(AimBlock,(st_Flash_Chip_Features	*)&CN_st_Flash_Chip_Features[Chip])!=De_Suc_PhyFlash)
			{	for(;;);						//进入死循环
			}
		}
	 	break;
	}
	
	for(Result=Block;;)
	{	Block=Result;
		Lgc2Phy((st_Flash_Chip_Features	*)&CN_st_Flash_Chip_Features[Chip],Block,&Block);		
		if(CopyBlock(Chip,AimBlock,Block,NULL,Offset,SizeofBuf)!=De_Suc_FlashL)
		{	if(CN_st_Fun_PhyFlash.CreatBad(Block,(st_Flash_Chip_Features	*)&CN_st_Flash_Chip_Features[Chip])!=De_Suc_PhyFlash)
			{	for(;;);						//进入死循环
			}
		}
	 	break;
	}
	return De_Suc_FlashL;
}

static uint16 CopyBlock(uint8 Chip,uint16 FoBlock,uint16 AimBlock,uint8 *Buf,uint16 Offset,uint16 SizeofBuf)
{	uint32 Addree,Addree1;
	uint16 Result,i,Size,Len;
	Addree=AimBlock*CN_st_Flash_Chip_Features[Chip].BlockSize;
	if(CN_st_Fun_PhyFlash.Juge(Addree,CN_st_Flash_Chip_Features[Chip].BlockSize,0xff,(st_Flash_Chip_Features	*)&CN_st_Flash_Chip_Features[Chip])
		!=De_Suc_PhyFlash)
	{	if((Result=CN_st_Fun_PhyFlash.Ease(Addree,(st_Flash_Chip_Features	*)&CN_st_Flash_Chip_Features[Chip]))!=De_Suc_PhyFlash)
			return Result;	
	}
	Addree1=FoBlock*CN_st_Flash_Chip_Features[Chip].BlockSize;
	for(i=0;i<CN_st_Flash_Chip_Features[Chip].BlockSize;i+=Size)
	{	Size=De_Flash_X_BUF_Size;
		if((i+Size)>CN_st_Flash_Chip_Features[Chip].BlockSize)
			Size=CN_st_Flash_Chip_Features[Chip].BlockSize-i;
		CN_st_Fun_PhyFlash.Read(Addree1+i,Size,X_BUF,(st_Flash_Chip_Features	*)&CN_st_Flash_Chip_Features[Chip]);
		if(Buf!=NULL)
		{	if(!((i>(Offset+SizeofBuf))||(i+Size)<Offset))
			{	if(i<Offset)
				{	Len=SizeofBuf;
					if((Offset-i+Len)>Size)	
						Len=(Size-(Offset-i));
					MoveByte(X_BUF+(Offset-i),Buf,Len);
				}
				
			    else 
				{	Len=SizeofBuf-(i-Offset);
					if(Len>Size)
						Len=Size;
					MoveByte(X_BUF,Buf+(i-Offset),Len);
				}
			}
		}
		if((Result=CN_st_Fun_PhyFlash.Write(Addree+i,Size,X_BUF,(st_Flash_Chip_Features	*)&CN_st_Flash_Chip_Features[Chip]))!=De_Suc_PhyFlash)
			return Result;
	}
	return De_Suc_FlashL;		
}

static void MoveByte(uint8 *Fount,uint8 *Aim,uint16 SizeofBuf)
{	uint16 i;
	for(i=0;i<SizeofBuf;i++)
		Fount[i]=Aim[i];	
}
#endif
