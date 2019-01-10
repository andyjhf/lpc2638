#define _rwflashphy_h
#ifdef	_rwflashphy_h


/*===============================Include File==========================================================*/
      #include "..\APP\config.h"
      #include "stdlib.h"

/*===================================Define Data=======================================================*/

/*==============================Data Define============================================================*/
typedef struct																											  typedef struct
{	unsigned char MaID[16];					//оƬ��ID��,��ʾоƬ�ĳ���,������
	unsigned short BlockSize;				//ÿ��Ĵ�С,��λ���ֽ�
	unsigned short BlockNumber;				//��оƬ�������
	unsigned short SectionSize;				//ÿҳ�Ĵ�С
	unsigned short SectionNumber; 				//һ������ҳ�����
	unsigned short BlockNumberUse;
	unsigned short BadBlock[24];				//����,���ҵ�0��Ϊ����
}st_Da_FlashL;
typedef struct 
{	/*	��������:��ʼ��FLASH������һЩ����оƬ��Ϣ�������FLASHû�н��г�ʼ����
			��ô��Ҫ��FLASH���г�ʼ���������û��������ձ�
		��ڲ���:
			ptst_Da_Flash:����оƬ����Ϣ��
		����ֵ:
			0:�ɹ�
			��0:����������	
	*/
	unsigned short (*	Open)(st_Da_Flash	*ptst_Da_Flash);
	/*	��������:�ر�FLASH
		��ڲ���:
			��
		����ֵ:
			0:�ɹ�	
			��0:����������
	*/
	unsigned short (*	Close)(void);
	
	/*	��������:��ָ��λ�ö�ȡָ�����������ֽ�
		��ڲ���:
			ptst_Da_Flash:��оƬ����Ϣ,���ϲ㴫��
			Addree:����ȡFLASH����ʼ��ַ
			SizeofBuf:����ȡ���ֽ�����
			Buf:��ȡ�����ŵĻ�����,RAM
		����ֵ:
			0:�ɹ�
			��0:����������
	*/
	unsigned short (*	Read)(const st_Da_Flash	*ptst_Da_Flash,const unsigned long Addree,
								  const unsigned short SizeofBuf,unsigned char *Buf);
	
	/*	��������:��ָ��λ��дָ�����������ֽ�
		��ڲ���:
			ptst_Da_Flash:��оƬ����Ϣ,���ϲ㴫��
			Addree:��дFLASH����ʼ��ַ
			SizeofBuf:��д���ֽ�����
			Buf:��дFLASH�Ļ�����
		����ֵ:
			0:�ɹ�
			��0:����������
	*/
	unsigned short (*	Write)(const st_Da_Flash	*ptst_Da_Flash,const unsigned long Addree,
								 const unsigned short SizeofBuf,const unsigned char *Buf);
	/*	��������:����ָ���Ŀ�
		��ڲ���:
			ptst_Da_Flash:��оƬ����Ϣ,���ϲ㴫��
			Block:��������ָ�����
		����ֵ:
			0:�ɹ�
			��0:����������
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