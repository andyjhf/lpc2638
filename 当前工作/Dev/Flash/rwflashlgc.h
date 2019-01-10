#include "..\..\Public_H\DePublic.h"
#ifdef	De_Compiler_File_rwflashlgc

/*===============================Include File==========================================================*/
	#include "..\..\APP\config.h"
	#include "stdlib.h"
#ifdef De_rwflashlgc_Compiler	
	#include "FlashPu.h"
	#include "_Flash.h"
#endif
/*===================================Define Data=======================================================*/
	/*++++++++++++++++++++++++++++++错误代码一览表+++++++++++++++++++++++++++++++++++++*/
	#define De_Suc_FlashL                                 			0

	#define De_Erro_Flash_AddreeOut									De_Erro_rwflashlgc
	#define De_Erro_Flash_NoOpen									De_Erro_Flash_AddreeOut+1

	#define De_Flash_X_BUF_Size					512
/*==================================Data Define========================================================*/
	typedef struct
	{	st_Flash_Chip_Features	*CN_st_Flash_Chip_Features[De_Flash_Chip_Number];
	}st_NorFlash;								//返回给文件系统的数据

	typedef struct
	{	/*	函数功能:打开器件逻辑层
			入口参数:	无
			返回值:	 各个器件的驱动以及基本参数，详见<st_NorFlash>定义	
		
		*/
		st_NorFlash	* (* Open)(void);
		/*	函数功能:读取指定器件数据，逻辑层
				入口参数:	输入参数	Chip	器件号码
										Addree	所读取的逻辑地址
										SizeofBuf	所读取的字节数量
	
							输出参数	Buf		所读取的数据
				返回值:	 0:成功			非0	<见错误代码表>	
		*/
		uint16 (*	Read)(uint8 Chip,uint32 Addree,uint16 SizeofBuf,uint8 *Buf);
		/*	函数功能:写指定器件数据，上层不需要查看是否要擦除，自己会判断逻辑层
				入口参数:	输入参数	Chip	器件号码
										Addree	所写的逻辑地址
										SizeofBuf	所写的字节数量
	
										Buf		所写的数据
				返回值:	 0:成功			非0	<见错误代码表>	
		*/
		uint16 (*	Write)(uint8 Chip,uint32 Addree,uint16 SizeofBuf,uint8 *Buf);
		/*	函数功能:擦除指定器件的逻辑块
				入口参数:	输入参数	Chip	器件号码
										Addree	所擦除的逻辑地址
				返回值:	 0:成功			非0	<见错误代码表>	
		*/
		uint16 (*	Ease)(uint8 Chip,uint32 Addree);
	}st_Fun_NorFlash;					//_rwflashlgc.c
/*==================================Static Function========================================================*/
	#ifdef De_rwflashlgc_Compiler
		static st_NorFlash	* Open(void);
		static uint16 Read(uint8 Chip,uint32 Addree,uint16 SizeofBuf,uint8 *Buf);
		static uint16 Write(uint8 Chip,uint32 Addree,uint16 SizeofBuf,uint8 *Buf);
		static uint16 Ease(uint8 Chip,uint32 Addree);
		
		static uint16 Lgc2Phy(st_Flash_Chip_Features	*ptst_Flash_Chip_Features,uint16 LogicBlk,uint16 *PhyBlk);
		static uint16 WriteBlock(uint8 Chip,uint32 Addree,uint16 SizeofBuf,uint8 *Buf);
		static void MoveByte(uint8 *Fount,uint8 *Aim,uint16 SizeofBuf);
		static uint16 CopyBlock(uint8 Chip,uint16 FoBlock,uint16 AimBlock,uint8 *Buf,uint16 Offset,uint16 SizeofBuf);
/*======================================Public Ram========================================================*/
		st_NorFlash			CN_st_NorFlash;
		static uint8 *X_BUF=(uint8 *)De_Flash_Ram;				//用于操作改写内容
		const st_Fun_NorFlash CN_st_Fun_NorFlash={Open,Read,Write,Ease};
	#else
		extern st_Fun_NorFlash	CN_st_Fun_NorFlash;
		extern st_NorFlash			CN_st_NorFlash;
	#endif	 	
#endif

