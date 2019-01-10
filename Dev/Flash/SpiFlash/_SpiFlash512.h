/*=============================================================Include File===================================================================================================*/
	#include "..\..\..\APP\config.h"
	#include "stdlib.h"
#ifdef De_SpiFlash512_Compiler
	#include "..\FlashPu.h"
	#include "..\..\..\HardWare\Spi\Spi.h"
#endif
/*============================================================Define Data=====================================================================================================*/
	#define De_Suc_SpiFlash															0
	/*++++++++++++++++++++++++++++++++++++++++++++++++++++++++错误代码定义+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/
	#define De_Erro_SpiFlash_WriteStatus												1
	#define De_Erro_SpiFlash_WriteEnable												De_Erro_SpiFlash_WriteStatus+1
	#define De_Erro_SpiFlash_WriteDisable 												De_Erro_SpiFlash_WriteEnable+1
	#define De_Erro_SpiFlash_TimeOut													De_Erro_SpiFlash_WriteDisable+1
	/*++++++++++++++++++++++++++++++++++++++++++++++++++++++++硬件端口定义+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/
#ifdef De_SpiFlash512_Compiler	
	/*+++++++++++++++++++++++++++++++HardWareI/O++++++++++++++++++++++++++++++++++++++*/
	#define De_IO_NorFlash_CE							0x04000000				
	#define De_IO_NorFlash_WP							0x00400000
	
	#define De_IO_NorFlash_CE_High						IODIR1|=De_IO_NorFlash_CE;IOSET1|=De_IO_NorFlash_CE
	#define De_IO_NorFlash_CE_Low						IODIR1|=De_IO_NorFlash_CE;IOCLR1|=De_IO_NorFlash_CE
	#define De_IO_NorFlash_WP_High						IODIR1|=De_IO_NorFlash_WP;IOSET1|=De_IO_NorFlash_WP
	#define De_IO_NorFlash_WP_Low 						IODIR1|=De_IO_NorFlash_WP;IOCLR1|=De_IO_NorFlash_WP

	/*++++++++++++++++++++++++++++++++SpiFlash命令+++++++++++++++++++++++++++++++++++*/
	#define De_NorFlash_Comand_JedecID					0x9F							//读芯片ID
	#define De_NorFlash_Comand_FastRead					0x0b							//快速读
	#define De_NorFlash_Comand_Program					0x02							//写命令
	#define De_NorFlash_Comand_Erase					0x20							//段擦除命令
	#define De_NorFlash_Comand_ReadStatus				0x05							//读状态
	#define De_NorFlash_Comand_WriteStatus				0x01							//写状态
	#define De_NorFlash_Comand_Enable					0x06							//操作时能
	#define De_NorFlash_Comand_Disable					0x04
   	/*++++++++++++++++++++++++++++++Spi状态+++++++++++++++++++++++++++++++++++++++++++*/
	#define De_NorFlash_Sta_Busy						0x01
	#define De_NorFlash_Sta_Wel							(0x01<<1)
	#define De_NorFlash_Sta_Bp0							(0x01<<2)
	#define De_NorFlash_Sta_Bp1							(0x01<<3)
	#define De_NorFlash_Sta_Bp2							(0x01<<4)
	#define De_NorFlash_Sta_TB							(0x01<<5)
	#define De_NorFlash_Sta_R							(0x01<<6)
	#define De_NorFlash_Sta_Srp							(0x01<<7)

	#define De_NorFlash_SoftErro_Number					3	//读写三次，如果不成功就认为失败

	#define De_SpiFlash_OutTime							0xffffff

#endif
/*============================================================static Function===========================================================================================================*/
#ifdef De_SpiFlash512_Compiler	 	
	static uint16 Init(void);
	static uint16 ReadID(uint8 *Buf);  
	static uint16 LookBad(uint16 Block,uint8 *BadFlag);
	static uint16 JugeByte(uint32 Page,uint16 Col,uint16 iSize,uint16 PageSize,uint8 Byte);
	static uint16 JugeBuf(uint32 Page,uint16 Col,uint16 iSize,uint16 PageSize,uint8 *Buf);
	static uint16 Ease(uint32 Page,uint16 PageSize);
	static uint16 Write(uint32 Page,uint16 Col,uint16 iSize,uint16 PageSize,uint8 *buf);
	static uint16 Read(uint32 Page,uint16 Col,uint16 SizeofBuf,uint16 PageSize,uint8 *Buf);

	static uint16 WriteClose(void);
	static uint16 WriteOpen(void);
	static uint16 WriteStatus(uint8 ByteV);
	static uint16 WriteEnable(void);
	static uint16 WriteDisable(void);
	static uint16 ReadStatusOutTime(uint8 *Status);
	static uint8 ReadStatus(void);
	static void CE_High(void);
	static void CE_Low(void);
	const st_Fun_PhyFlash	CN_Spi_st_Fun_PhyFlash={Init,ReadID,NULL,JugeByte,JugeBuf,Ease,Write,Read};  				//
#else
	extern const st_Fun_PhyFlash CN_Spi_st_Fun_PhyFlash;
#endif

