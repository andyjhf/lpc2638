#define _rwflashphy_h
#ifdef	_rwflashphy_h


/*===============================Include File==========================================================*/
      #include "..\APP\config.h"
      #include "stdlib.h"

/*===================================Define Data=======================================================*/

/*==============================Data Define============================================================*/
typedef struct																											  typedef struct
{	unsigned char MaID[16];					//芯片的ID号,表示芯片的厂家,容量等
	unsigned short BlockSize;				//每块的大小,单位是字节
	unsigned short BlockNumber;				//此芯片块的数量
	unsigned short SectionSize;				//每页的大小
	unsigned short SectionNumber; 				//一块里面页的数�
	unsigned short BlockNumberUse;
	unsigned short BadBlock[24];				//坏块,查找到0作为结束
}st_Da_FlashL;
typedef struct 
{	/*	函数功能:初始化FLASH，返回一些厂家芯片信息。如果此FLASH没有进行初始化，
			那么就要对FLASH进行初始化，建立好坏扇区对照表
		入口参数:
			ptst_Da_Flash:返回芯片的信息。
		返回值:
			0:成功
			非0:见错误代码表	
	*/
	unsigned short (*	Open)(st_Da_Flash	*ptst_Da_Flash);
	/*	函数功能:关闭FLASH
		入口参数:
			无
		返回值:
			0:成功	
			非0:见错误代码表
	*/
	unsigned short (*	Close)(void);
	
	/*	函数功能:到指定位置读取指定的数量的字节
		入口参数:
			ptst_Da_Flash:本芯片的信息,由上层传递
			Addree:所读取FLASH的起始地址
			SizeofBuf:所读取的字节数量
			Buf:读取后所放的缓冲区,RAM
		返回值:
			0:成功
			非0:见错误代码表
	*/
	unsigned short (*	Read)(const st_Da_Flash	*ptst_Da_Flash,const unsigned long Addree,
								  const unsigned short SizeofBuf,unsigned char *Buf);
	
	/*	函数功能:到指定位置写指定的数量的字节
		入口参数:
			ptst_Da_Flash:本芯片的信息,由上层传递
			Addree:所写FLASH的起始地址
			SizeofBuf:所写的字节数量
			Buf:所写FLASH的缓冲区
		返回值:
			0:成功
			非0:见错误代码表
	*/
	unsigned short (*	Write)(const st_Da_Flash	*ptst_Da_Flash,const unsigned long Addree,
								 const unsigned short SizeofBuf,const unsigned char *Buf);
	/*	函数功能:擦除指定的块
		入口参数:
			ptst_Da_Flash:本芯片的信息,由上层传递
			Block:所擦除的指定块号
		返回值:
			0:成功
			非0:见错误代码表
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