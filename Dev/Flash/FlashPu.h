/*=============================================================Define Data==============================================================================================================*/	
	#define De_Flash_Bad_Flag 																		0 							//坏块标志
	#define De_Flash_Bad_NoFlag																		1							//没有坏
/*==============================================================Data Define=============================================================================================================*/
	typedef struct
	{	uint16 (*Init)(void);
		uint16 (*ReadID)(uint8 *Buf);  
		uint16 (*LookBad)(uint32 Page,uint8 *BadFlag);
		uint16 (*JugeByte)(uint32 Page,uint16 Col,uint16 iSize,uint16 PageSize,uint8 Byte);
		uint16 (*JugeBuf)(uint32 Page,uint16 Col,uint16 iSize,uint16 PageSize,uint8 *Buf);
		uint16 (*Ease)(uint32 Page,uint16 PageSize);
		uint16 (*Write)(uint32 Page,uint16 Col,uint16 iSize,uint16 PageSize,uint8 *buf);
		uint16 (*Read)(uint32 Page,uint16 Col,uint16 SizeofBuf,uint16 PageSize,uint8 *Buf);
	}st_Fun_PhyFlash;

	typedef struct
	{	uint8 ID[3];
		uint16 BlockSize;
		uint16 BlockNumber;
		uint16 SectionSize;
		uint16 SectionNumber;
		uint16 BlockNumberUse;
		uint8 *Name;
		st_Fun_PhyFlash	*ptst_Fun_PhyFlash;
	}st_Flash_Chip_Features;

