#define _rwflashphy_h
#ifdef	_rwflashphy_h


/*===============================Include File==========================================================*/
      #include "..\APP\config.h"
      #include "stdlib.h"

/*===================================Define Data=======================================================*/

/*==============================Data Define============================================================*/
typedef struct																											  typedef struct
{	unsigned char MaID[16];					//Ğ¾Æ¬µÄIDºÅ,±íÊ¾Ğ¾Æ¬µÄ³§¼Ò,ÈİÁ¿µÈ
	unsigned short BlockSize;				//Ã¿¿éµÄ´óĞ¡,µ¥Î»ÊÇ×Ö½Ú
	unsigned short BlockNumber;				//´ËĞ¾Æ¬¿éµÄÊıÁ¿
	unsigned short SectionSize;				//Ã¿Ò³µÄ´óĞ¡
	unsigned short SectionNumber; 				//Ò»¿éÀïÃæÒ³µÄÊıÁ
	unsigned short BlockNumberUse;
	unsigned short BadBlock[24];				//»µ¿é,²éÕÒµ½0×÷Îª½áÊø
}st_Da_FlashL;
typedef struct 
{	/*	º¯Êı¹¦ÄÜ:³õÊ¼»¯FLASH£¬·µ»ØÒ»Ğ©³§¼ÒĞ¾Æ¬ĞÅÏ¢¡£Èç¹û´ËFLASHÃ»ÓĞ½øĞĞ³õÊ¼»¯£¬
			ÄÇÃ´¾ÍÒª¶ÔFLASH½øĞĞ³õÊ¼»¯£¬½¨Á¢ºÃ»µÉÈÇø¶ÔÕÕ±í
		Èë¿Ú²ÎÊı:
			ptst_Da_Flash:·µ»ØĞ¾Æ¬µÄĞÅÏ¢¡£
		·µ»ØÖµ:
			0:³É¹¦
			·Ç0:¼û´íÎó´úÂë±í	
	*/
	unsigned short (*	Open)(st_Da_Flash	*ptst_Da_Flash);
	/*	º¯Êı¹¦ÄÜ:¹Ø±ÕFLASH
		Èë¿Ú²ÎÊı:
			ÎŞ
		·µ»ØÖµ:
			0:³É¹¦	
			·Ç0:¼û´íÎó´úÂë±í
	*/
	unsigned short (*	Close)(void);
	
	/*	º¯Êı¹¦ÄÜ:µ½Ö¸¶¨Î»ÖÃ¶ÁÈ¡Ö¸¶¨µÄÊıÁ¿µÄ×Ö½Ú
		Èë¿Ú²ÎÊı:
			ptst_Da_Flash:±¾Ğ¾Æ¬µÄĞÅÏ¢,ÓÉÉÏ²ã´«µİ
			Addree:Ëù¶ÁÈ¡FLASHµÄÆğÊ¼µØÖ·
			SizeofBuf:Ëù¶ÁÈ¡µÄ×Ö½ÚÊıÁ¿
			Buf:¶ÁÈ¡ºóËù·ÅµÄ»º³åÇø,RAM
		·µ»ØÖµ:
			0:³É¹¦
			·Ç0:¼û´íÎó´úÂë±í
	*/
	unsigned short (*	Read)(const st_Da_Flash	*ptst_Da_Flash,const unsigned long Addree,
								  const unsigned short SizeofBuf,unsigned char *Buf);
	
	/*	º¯Êı¹¦ÄÜ:µ½Ö¸¶¨Î»ÖÃĞ´Ö¸¶¨µÄÊıÁ¿µÄ×Ö½Ú
		Èë¿Ú²ÎÊı:
			ptst_Da_Flash:±¾Ğ¾Æ¬µÄĞÅÏ¢,ÓÉÉÏ²ã´«µİ
			Addree:ËùĞ´FLASHµÄÆğÊ¼µØÖ·
			SizeofBuf:ËùĞ´µÄ×Ö½ÚÊıÁ¿
			Buf:ËùĞ´FLASHµÄ»º³åÇø
		·µ»ØÖµ:
			0:³É¹¦
			·Ç0:¼û´íÎó´úÂë±í
	*/
	unsigned short (*	Write)(const st_Da_Flash	*ptst_Da_Flash,const unsigned long Addree,
								 const unsigned short SizeofBuf,const unsigned char *Buf);
	/*	º¯Êı¹¦ÄÜ:²Á³ıÖ¸¶¨µÄ¿é
		Èë¿Ú²ÎÊı:
			ptst_Da_Flash:±¾Ğ¾Æ¬µÄĞÅÏ¢,ÓÉÉÏ²ã´«µİ
			Block:Ëù²Á³ıµÄÖ¸¶¨¿éºÅ
		·µ»ØÖµ:
			0:³É¹¦
			·Ç0:¼û´íÎó´úÂë±í
	*/
	unsigned short (*	Ease)(const st_Da_Flash	*ptst_Da_Flash,const unsigned short Block);
	
	unsigned short (*	Juge)(const st_Da_Flash	*ptst_Da_Flash,const unsigned long Addree,
								 const unsigned short SizeofBuf,const unsigned char Byte);
}st_Fun_NorFlashPhy;
/*==============================Static Function========================================================*/
static unsigned short Open(st_Da_Flash	*ptst_Da_Flash);
static unsigned short Read(const st_Da_Flash	*ptst_Da_Flash,unsigned long Addree,unsigned short SizeofBuf,
unsigned char *Buf);
static unsigned short Write(const st_Da_Flash	*ptst_Da_Flash,unsigned long Addree,unsigned short SizeofBuf,
unsigned char *Buf);
static unsigned short Juge(const st_Da_Flash	*ptst_Da_Flash,unsigned long Addree,unsigned short SizeofBuf,
unsigned char Byte);
static unsigned short Ease(const st_Da_Flash	*ptst_Da_Flash,unsigned short Block);
static unsigned short Close(void);
#endif