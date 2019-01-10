/*========================================Include File==========================================================*/	
	#include "..\..\APP\config.h"
	#include "stdlib.h"
#ifdef De_Flash_Compiler
	#include "FlashPu.h"
	#include "NandFlash\512\_NandFlash512.h"
	#include "SpiFlash\_SpiFlash512.h"
#endif

/*========================================Define Data===========================================================*/
	#define De_Suc_PhyFlash											0
	/*+++++++++++++++++++++++++++++++++++++´íÎó´úÂëÒ»ÀÀ±í++++++++++++++++++++++++++++++++++++++++++++++++++*/
	#define De_Erro_PhyFlash_ID										1
	#define De_Erro_Flash_Bad_Over									De_Erro_PhyFlash_ID+1

	#define De_Flash_FlashInitFlagAddree							0
	#define De_Flash_BadBlock_Start									De_Flash_FlashInitFlagAddree+2
	#define De_Flash_Format_Flag									0xaa55
	#define De_Flash_Bad_Number										100
/*=========================================Data Define=========================================================*/
	typedef struct
	{	uint16 (*Open)(st_Flash_Chip_Features	*ptst_Flash_Chip_Features);
		uint16 (*Format)(st_Flash_Chip_Features	*ptst_Flash_Chip_Features);
		uint16 (*CreatBad)(uint16 BlockNumber,st_Flash_Chip_Features	*ptst_Flash_Chip_Features);
		uint16 (*Juge)(uint32 Addree,uint16 SizeofBuf,uint8 Byte,st_Flash_Chip_Features	*ptst_Flash_Chip_Features); 	//ÅÐ¶ÏFLASH
		uint16 (*Write)(uint32 Addree,uint16 SizeofBuf,uint8 *Buf,st_Flash_Chip_Features	*ptst_Flash_Chip_Features); //Ð´FLASH
		uint16 (*Read)(uint32 Addree,uint16 SizeofBuf,uint8 *Buf,st_Flash_Chip_Features	*ptst_Flash_Chip_Features); 		//¶ÁFLASH
		uint16 (*Ease)(uint32 Addree,st_Flash_Chip_Features	*ptst_Flash_Chip_Features);	
	}st_Fun_Flash;
/*==========================================Static Function=======================================================*/
#ifdef De_Flash_Compiler	
	static uint16 Open(st_Flash_Chip_Features	*ptst_Flash_Chip_Features);
	static uint16 FormatFlash(st_Flash_Chip_Features	*ptst_Flash_Chip_Features);
	static uint16 CreatBad(uint16 BlockNumber,st_Flash_Chip_Features	*ptst_Flash_Chip_Features);
	static uint16 JugeFlash(uint32 Addree,uint16 SizeofBuf,uint8 Byte,st_Flash_Chip_Features	*ptst_Flash_Chip_Features); 	//ÅÐ¶ÏFLASH
	static uint16 WriteFlash(uint32 Addree,uint16 SizeofBuf,uint8 *Buf,st_Flash_Chip_Features	*ptst_Flash_Chip_Features); //Ð´FLASH
	static uint16 ReadFlash(uint32 Addree,uint16 SizeofBuf,uint8 *Buf,st_Flash_Chip_Features	*ptst_Flash_Chip_Features); 		//¶ÁFLASH
	static uint16 EaseFlash(uint32 Addree,st_Flash_Chip_Features	*ptst_Flash_Chip_Features);
	static uint16 CompareBuf(uint8 *Buf1,uint8 *Buf2,uint32 SizeofBuf);
#endif
/*=========================================Public Ram===========================================================*/
	#define De_Flash_Chip_Number												6								
#ifdef De_Flash_Compiler	
	const st_Flash_Chip_Features	CN_st_Flash_Chip_Features[De_Flash_Chip_Number]=													//Ö§³ÖµÄFLASHµÄÆ÷¼þ
	{	{	{0xAD,0X76,0xff},16384,4096,512,32,4000,"H27U518S2C",(st_Fun_PhyFlash	*)&CN_NandFlash512_st_Fun_PhyFlash},					//H27U518S2C
		{	{0xEC,0X76,0xff},16384,4096,512,32,4000,"K9F1208X0C",(st_Fun_PhyFlash	*)&CN_NandFlash512_st_Fun_PhyFlash},					//K9F1208X0C
		{	{0XEF,0X30,0X15},4096,256,256,16,230,"W25X16",(st_Fun_PhyFlash	*)&CN_Spi_st_Fun_PhyFlash},									//W25X16
		{	{0XEF,0X30,0X16},4096,1024,256,16,980,"W25X32",(st_Fun_PhyFlash	*)&CN_Spi_st_Fun_PhyFlash}, 								//W25X32
		{	{0XEF,0X30,0X16},4096,2048,256,16,1960,"W25X64",(st_Fun_PhyFlash	*)&CN_Spi_st_Fun_PhyFlash}, 								//W25X64
		{	{0x20,0x71,0x16},4096,1024,256,16,980,"25PX32",(st_Fun_PhyFlash	*)&CN_Spi_st_Fun_PhyFlash} 								//25PX32
	};
	const st_Fun_Flash	CN_st_Fun_PhyFlash={Open,FormatFlash,CreatBad,JugeFlash,WriteFlash,ReadFlash,EaseFlash};
#else
	extern const st_Flash_Chip_Features	CN_st_Flash_Chip_Features[De_Flash_Chip_Number];
	extern const st_Fun_Flash	CN_st_Fun_PhyFlash;	 
#endif
