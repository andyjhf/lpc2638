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
	/*++++++++++++++++++++++++++++++�������һ����+++++++++++++++++++++++++++++++++++++*/
	#define De_Suc_FlashL                                 			0

	#define De_Erro_Flash_AddreeOut									De_Erro_rwflashlgc
	#define De_Erro_Flash_NoOpen									De_Erro_Flash_AddreeOut+1

	#define De_Flash_X_BUF_Size					512
/*==================================Data Define========================================================*/
	typedef struct
	{	st_Flash_Chip_Features	*CN_st_Flash_Chip_Features[De_Flash_Chip_Number];
	}st_NorFlash;								//���ظ��ļ�ϵͳ������

	typedef struct
	{	/*	��������:�������߼���
			��ڲ���:	��
			����ֵ:	 ���������������Լ��������������<st_NorFlash>����	
		
		*/
		st_NorFlash	* (* Open)(void);
		/*	��������:��ȡָ���������ݣ��߼���
				��ڲ���:	�������	Chip	��������
										Addree	����ȡ���߼���ַ
										SizeofBuf	����ȡ���ֽ�����
	
							�������	Buf		����ȡ������
				����ֵ:	 0:�ɹ�			��0	<����������>	
		*/
		uint16 (*	Read)(uint8 Chip,uint32 Addree,uint16 SizeofBuf,uint8 *Buf);
		/*	��������:дָ���������ݣ��ϲ㲻��Ҫ�鿴�Ƿ�Ҫ�������Լ����ж��߼���
				��ڲ���:	�������	Chip	��������
										Addree	��д���߼���ַ
										SizeofBuf	��д���ֽ�����
	
										Buf		��д������
				����ֵ:	 0:�ɹ�			��0	<����������>	
		*/
		uint16 (*	Write)(uint8 Chip,uint32 Addree,uint16 SizeofBuf,uint8 *Buf);
		/*	��������:����ָ���������߼���
				��ڲ���:	�������	Chip	��������
										Addree	���������߼���ַ
				����ֵ:	 0:�ɹ�			��0	<����������>	
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
		static uint8 *X_BUF=(uint8 *)De_Flash_Ram;				//���ڲ�����д����
		const st_Fun_NorFlash CN_st_Fun_NorFlash={Open,Read,Write,Ease};
	#else
		extern st_Fun_NorFlash	CN_st_Fun_NorFlash;
		extern st_NorFlash			CN_st_NorFlash;
	#endif	 	
#endif

