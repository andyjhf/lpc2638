#include "..\..\Public_H\DePublic.h"
#ifdef	De_Compiler_miscellaneous_AscNumber

/*===============================Include File==========================================================*/
    #include "..\..\APP\config.h"
	#include "stdlib.h"
	#ifdef De_AscNumber_Compiler
		#include "..\..\File\rwFile.h"
	#endif
/*=====================================Define Data=====================================================*/
	/*++++++++++++++++++++++++++++++++++程序状态++++++++++++++++++++++++++++++++++++++++++++*/
	#define De_AscNumber_Va_True							0
    #define De_AscNumber_Va_Flase							1
    #define De_AscNumber_Va_Equality						2
	#define De_AscNumber_Va_Big								1
	#define De_AscNumber_Va_Small							0

	#define De_Erro_AscNumber_Char2IP						1
	#define De_Suc_AscNumber								0

	#define De_FileName_GBK2Uni								"GBK2UI.GJ"
	#define	De_FileName_Uni2GBK								"UI2GBK.GJ"
	#define MAX_UNI_INDEX									23940
/*==============================Function Data==========================================*/
	typedef struct
	{	void (*Asc2Bcd)(uint8 *Asc,uint8 *BCD,uint8 SizeofAsc);	 //ASC
		void (*Bcd2Asc)(uint8 *Bcd,uint8 *Asc,uint8 SizeofBcd);
		uint32 (*Asc2Algorism)(uint8 *Asc,uint8 SizeofAsc);
		uint8 (*Algorism2Asc)(uint32 Algorism,uint8 *Asc);
		void (*Asc2HexBuf)(uint8 *Asc,uint8 *Hex,uint16 SizeofAsc);
		void (*HexBuf2Asc)(uint8 *Hex,uint8 *Asc,uint8 SizeofHex);
		uint32 (*Asc2Hex)(uint8 *Asc,uint8 SizeofAsc);
		uint8 (*Hex2Asc)(uint32 Hex,uint8 *Asc);   
		uint32 (*Asc2Float)(uint8 *Asc,uint8 FixPoint,uint8 SizeofAsc);
		void (*Bcd2Hex)(uint8 *BcdBuf,uint8 *HexBuf,uint8 SizeofBcdBuf);
		uint8 (*Hex2Bcd)(uint8 *HexBuf,uint8 *BcdBuf,uint8 SizeofHexBuf);
		
		uint16 (*JugeAscBcd)(uint8 *Asc,uint8 SizeofAsc);
		uint16 (*JugeAscHex)(uint8 *Asc,uint8 SizeofAsc);
		uint16 (*JugeAscFloat)(uint8 *Asc,uint8 SizeofAsc);	
		uint16 (*JugeHexBcd)(uint8 *Hex,uint8 SizeofHex);
		void (*ClsArray)(void *Buf,uint16 SizeofBuf);
		void (*MoveByte)(void *Aim,void *Fountain,uint16 SizeofBuf);
		uint16 (*CompareBuf)(void *Buf1,void *Buf2,uint32 SizeofBuf);
		uint16 (*CompareVa)(uint8 *Big,uint8 *Small,uint8 SizeofBuf,uint8 Type);
		uint8 (*Strsize)(uint8 *Buf);
		uint16 (*Strsize16)(uint8 *Buf);
		uint8 (*StrATChar)(uint8 *Buf);
		uint8 *(*LookStr)(uint8 *LookString,uint8 *Buf);
		uint8 * (*LookEnable)(uint8 *Buf,uint8 *EnableBuf,uint8 Number);
		uint8 *(*LookStrInLength)(uint8 *LookString,uint8 *Buf,uint16 DataLength);
	   	uint8 *	(*LookStrDown)(uint8 *LookString,uint8 *Buf);
		uint8 *	(*LookShowChar)(uint8 *CharBuf,uint8 *Buf);
		uint8 * (*SeekStr)(uint8 *Buf,uint8 *CharV,uint16 SizeofBuf,uint8 Number);
		uint8 (*MemSpace)(uint8 *Buf);
		uint16 (*JugeBufType)(uint8 *Buf);
		uint16 (*PhoPdu)(uint8 *Dat,uint8 *Message,uint8 *Phone,uint8 *Centr);
		uint16 (*gsmEncode7bit)(const uint8* pSrc, uint8* pDst, uint16 nSrcLength);
		void (*PduNumber)(uint8 *Dat,uint8 *PduNum,uint16 SizeofDat);
		uint16 (*ExpPdu)(uint8 *Dat,uint8 *Message,uint8 *Phone,uint8 *Centr);
		uint16 (*Bit72Bit8)(uint8 *Bit7,uint8 *Bit8,uint16 Bit7Len);
		uint8 (*GetCsq)(uint8 Csq);
		uint16 (*StrToUni)(const uint8 *str,uint8 *uni,uint8 Length);
		uint16 (*UniToStr)(const uint8 *uni,uint8 *str,uint8 Length);
		uint16 (*INT322IPAsc)(uint32 Hex,uint8 *Buf);
		void (*IPAsc2INT32)(uint8 *Buf,uint32 *Hex);
		uint16 (*IP2Char)(uint32 IP,uint8 *Buf,uint8 Fix);
		uint16 (*Char2IP)(uint8 *Buf,uint32 *IP,uint8 Fix);				//字符型IP转化成整型IP
		uint8 *(*LookBufInLength)(uint8 *LookString,uint16 DataLen1,uint8 *Buf,uint16 DataLength);
		void (*Value32)(uint8 *Buf,uint32 *Hex32,uint16 Len);

	}st_Fun_AscNumber;
	#ifdef De_AscNumber_Compiler
   	typedef struct
	{ 	uint8 Start;
		uint8 End;
		uint8 ByteV;
	}st_Asc_GetData;
	#endif
	typedef struct
	{	int16	GBK2Unifd;
		uint16	Uni2GBKfd;
	}st_File_GBK;
/*==============================Static Function========================================================*/
	#ifdef De_AscNumber_Compiler						//编译函数体
	
		static void Asc2Bcd(uint8 *Asc,uint8 *BCD,uint8 SizeofAsc);	 //ASC
		static void Bcd2Asc(uint8 *Bcd,uint8 *Asc,uint8 SizeofBcd);
		static uint32 Asc2Algorism(uint8 *Asc,uint8 SizeofAsc);
		static uint8 Algorism2Asc(uint32 Algorism,uint8 *Asc);
		static void Asc2HexBuf(uint8 *Asc,uint8 *Hex,uint16 SizeofAsc);
		static void HexBuf2Asc(uint8 *Hex,uint8 *Asc,uint8 SizeofHex);
		static uint32 Asc2Hex(uint8 *Asc,uint8 SizeofAsc);
		static uint8 Hex2Asc(uint32 Hex,uint8 *Asc);
			
		static uint16 JugeAscBcd(uint8 *Asc,uint8 SizeofAsc);
		static uint16 JugeAscHex(uint8 *Asc,uint8 SizeofAsc);
		static uint32 Asc2Float(uint8 *Asc,uint8 FixPoint,uint8 SizeofAsc);
		static uint16 JugeAscFloat(uint8 *Asc,uint8 SizeofAsc);		
		static uint16 JugeHexBcd(uint8 *Hex,uint8 SizeofHex);


		static void ClsArray(void *Buf,uint16 SizeofBuf);
		static void MoveByte(void *Aim,void *Fountain,uint16 SizeofBuf);
		static uint16 CompareBuf(void *Buf1,void *Buf2,uint32 SizeofBuf);
		static uint16 CompareVa(uint8 *Big,uint8 *Small,uint8 SizeofBuf,uint8 Type);
		static uint8 Strsize(uint8 *Buf);
		static uint8 StrATChar(uint8 *Buf);
		static uint16 Strsize16(uint8 *Buf);
		
		static uint8 Asc2HexSig(uint8 Asc);
		static uint8 Hex2AscSig(uint8 Hex);
		static void Bcd2Hex(uint8 *BcdBuf,uint8 *HexBuf,uint8 SizeofBcdBuf);
		static uint8 Hex2Bcd(uint8 *HexBuf,uint8 *BcdBuf,uint8 SizeofHexBuf);
		static uint8 *LookStr(uint8 *LookString,uint8 *Buf);
		static uint8 *LookEnable(uint8 *Buf,uint8 *EnableBuf,uint8 Number);
		static uint8 *LookStrInLength(uint8 *LookString,uint8 *Buf,uint16 DataLength);
		static uint8 *LookStrDown(uint8 *LookString,uint8 *Buf);
		static uint8 *LookShowChar(uint8 *CharBuf,uint8 *Buf);
		static uint8 *SeekStr(uint8 *Buf,uint8 *CharV,uint16 SizeofBuf,uint8 Number);
		static uint8 MemSpace(uint8 *Buf);

		static uint16 JugeBufType(uint8 *Buf);
		static uint16 PhoPdu(uint8 *Dat,uint8 *Message,uint8 *Phone,uint8 *Centr);
		static uint16 gsmEncode7bit(const uint8* pSrc, uint8* pDst, uint16 nSrcLength);
		static void PduNumber(uint8 *Dat,uint8 *PduNum,uint16 SizeofDat);
		static uint16 ExpPdu(uint8 *Dat,uint8 *Message,uint8 *Phone,uint8 *Centr);
		static uint16 Bit72Bit8(uint8 *Bit7,uint8 *Bit8,uint16 Bit7Len);
		static uint8 GetCsq(uint8 Csq);
		static uint16 BinarySearchUni(uint16 uni,uint16 *gb);
		static uint16 BinarySearchStr(uint16 gb,uint16 *uni);
		static uint16 StrToUni(const uint8 *str,uint8 *uni,uint8 Length);
		static uint16 UniToStr(const uint8 *uni,uint8 *str,uint8 Length);
		static uint16 INT322IPAsc(uint32 Hex,uint8 *Buf);
		static void IPAsc2INT32(uint8 *Buf,uint32 *Hex);
		static uint16 IP2Char(uint32 IP,uint8 *Buf,uint8 Fix);
		static uint16 Char2IP(uint8 *Buf,uint32 *IP,uint8 Fix);
		static uint8 *LookBufInLength(uint8 *LookString,uint16 DataLen1,uint8 *Buf,uint16 DataLength);
		static void Value32(uint8 *Buf,uint32 *Hex32,uint16 Len);
/*==================================================函数输出====================================================*/		
		const st_Fun_AscNumber	CN_st_Fun_AscNumber=
		{	Asc2Bcd,Bcd2Asc,Asc2Algorism,Algorism2Asc,Asc2HexBuf,HexBuf2Asc,Asc2Hex,Hex2Asc,Asc2Float,Bcd2Hex,Hex2Bcd,JugeAscBcd,
			JugeAscHex,JugeAscFloat,JugeHexBcd,ClsArray,MoveByte,CompareBuf,CompareVa,Strsize,Strsize16,StrATChar,LookStr,LookEnable,LookStrInLength,LookStrDown,LookShowChar,SeekStr,
			MemSpace,JugeBufType,PhoPdu,gsmEncode7bit,PduNumber,ExpPdu,Bit72Bit8,GetCsq,StrToUni,UniToStr,INT322IPAsc,IPAsc2INT32,IP2Char,Char2IP,LookBufInLength
		
		};
		const uint32 FixPointValue[10]={1,10,100,1000,10000,100000,1000000,10000000,100000000,1000000000};
   		#define De_Asc_MaxV												6		
		const st_Asc_GetData	CN_st_Asc_GetData[De_Asc_MaxV]=
		{	{0,0,1},
			{1,6,2},
			{7,20,3},
			{21,25,4},
			{26,30,5},
			{31,31,6}
		};
		st_File_GBK CN_st_File_GBK;
   	#else
		extern const st_Fun_AscNumber CN_st_Fun_AscNumber;				
		extern st_File_GBK CN_st_File_GBK;
	#endif 	
#endif
