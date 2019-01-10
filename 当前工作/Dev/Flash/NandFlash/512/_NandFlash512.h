/*=============================================================Include File===================================================================================================*/
	#include "..\..\..\..\APP\config.h"
	#include "stdlib.h"
#ifdef De_NandFlash512_Compiler
	#include "..\..\FlashPu.h"
#endif
/*============================================================Define Data=====================================================================================================*/
	#define De_Suc_NandFlash														0
	/*++++++++++++++++++++++++++++++++++++++++++++++++++++++++������붨��+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/
	#define De_Erro_NandFlash_NoEven												1
	#define De_Erro_NandFlash_Write													2

	/*++++++++++++++++++++++++++++++++++++++++++++++++++++++++Ӳ���˿ڶ���+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/
#ifdef De_NandFlash512_Compiler	
	#define De_NandFlash_HardWare_RB_Number							9			//æ�ź���
	#define De_NandFlash_HardWare_CE_Number							10		   	//ѡͨ�ź�
	#define De_NandFlash_HardWare_CLE_Number						14			//�����ź�			
	#define De_NandFlash_HardWare_ALE_Number						15			//��ַ��Ϣ
	#define De_NandFlash_HardWare_WE_Number							16			//д�ź�
	#define De_NandFlash_HardWare_RE_Number							17			//���ź�

	#define De_NandFlash_HardWare_ReSet 							PINSEL2 &= 0x0fc3ffff;PINSEL3 &= 0xfffffff0

	#define De_NandFlash_HardWare_WE_Up								IODIR1|=(0x00000001<<De_NandFlash_HardWare_WE_Number);IOSET1|=(0x00000001<<De_NandFlash_HardWare_WE_Number)																														
	#define De_NandFlash_HardWare_WE_Down							IODIR1|=(0x00000001<<De_NandFlash_HardWare_WE_Number);IOCLR1|=(0x00000001<<De_NandFlash_HardWare_WE_Number)
	#define De_NandFlash_HardWare_RE_Up								IODIR1|=(0x00000001<<De_NandFlash_HardWare_RE_Number);IOSET1|=(0x00000001<<De_NandFlash_HardWare_RE_Number)
	#define De_NandFlash_HardWare_RE_Down							IODIR1|=(0x00000001<<De_NandFlash_HardWare_RE_Number);IOCLR1|=(0x00000001<<De_NandFlash_HardWare_RE_Number)
	#define De_NandFlash_HardWare_CE_Up								IODIR1|=(0x00000001<<De_NandFlash_HardWare_CE_Number);IOSET1|=(0x00000001<<De_NandFlash_HardWare_CE_Number)
	#define De_NandFlash_HardWare_CE_Down							IODIR1|=(0x00000001<<De_NandFlash_HardWare_CE_Number);IOCLR1|=(0x00000001<<De_NandFlash_HardWare_CE_Number)
	#define De_NandFlash_HardWare_ALE_Up							IODIR1|=(0x00000001<<De_NandFlash_HardWare_ALE_Number);IOSET1|=(0x00000001<<De_NandFlash_HardWare_ALE_Number)
	#define De_NandFlash_HardWare_ALE_Down							IODIR1|=(0x00000001<<De_NandFlash_HardWare_ALE_Number);IOCLR1|=(0x00000001<<De_NandFlash_HardWare_ALE_Number)
	#define De_NandFlash_HardWare_CLE_Up							IODIR1|=(0x00000001<<De_NandFlash_HardWare_CLE_Number);IOSET1|=(0x00000001<<De_NandFlash_HardWare_CLE_Number)
	#define De_NandFlash_HardWare_CLE_Down							IODIR1|=(0x00000001<<De_NandFlash_HardWare_CLE_Number);IOCLR1|=(0x00000001<<De_NandFlash_HardWare_CLE_Number)
	#define De_NandFlash_HardWare_Data_Out							FIO2DIR|=0xff
	#define De_NandFlash_HardWare_Data_In							FIO2DIR&=0Xffffff00
	#define De_NandFlash_HardWare_Data_Output_High					FIO2SET
	#define De_NandFlash_HardWare_Data_Output_Low 					FIO2CLR
	#define De_NandFlash_HardWare_Data_Input						FIO2PIN
	#define De_NandFlash_HardWare_Data_RB_In						IODIR1&=(~(0x00000001<<De_NandFlash_HardWare_RB_Number))
	#define	De_NandFlash_HardWare_Data_RB_In_Data					(IOPIN1&(0x00000001<<De_NandFlash_HardWare_RB_Number))
	/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++NandFlash ����+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/
   	#define De_NandFlash_Order_ReadHead								0x00			//0~255
	#define De_NandFlash_Order_ReadMiddle							0x01			//256~511
	#define De_NandFlash_Order_ReadExcursion						0X50   			//511~526
	#define De_NandFlash_Order_ReadID								0X90			//��ID
	#define De_NandFlash_Order_Program								0x80			//д����
	#define De_NandFlash_Order_Latch								0x10			//��������
	#define De_NandFlash_Order_ProgramOver							0x70			//д��������
	#define De_NandFlash_Order_EaseStep								0x60			//������ʼ
	#define De_NandFlash_Order_Ease									0xd0			//��������
   	/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++����״̬+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/
	#define De_NandFlash_Write										0 				//дFLASH����
	#define De_NandFlash_Read										1 				//��FLASH����
#endif
/*============================================================static Function===========================================================================================================*/
#ifdef De_NandFlash512_Compiler	 	
	static uint16 Init(void);
	static uint16 ReadID(uint8 *Buf);  
	static uint16 LookBad(uint32 Page,uint8 *BadFlag);
	static uint16 JugeByte(uint32 Page,uint16 Col,uint16 iSize,uint16 PageSize,uint8 Byte);
	static uint16 JugeBuf(uint32 Page,uint16 Col,uint16 iSize,uint16 PageSize,uint8 *Buf);
	static uint16 Ease(uint32 Page,uint16 PageSize);
	static uint16 FMwrPg(uint32 Page,uint16 Col,uint16 iSize,uint16 PageSize,uint8 *buf);
	static uint16 FMrdPg517(uint32 Page,uint16 Col,uint16 SizeofBuf,uint16 PageSize,uint8 *Buf);
	static void dzflash(uint32 Page,uint16 Col,uint8 wtORrd); 
	static void WriteData(uint8 Data);
   	static uint8 ReadData(void);
	const st_Fun_PhyFlash	CN_NandFlash512_st_Fun_PhyFlash={Init,ReadID,LookBad,JugeByte,JugeBuf,Ease,FMwrPg,FMrdPg517};  				//
#else
	extern const st_Fun_PhyFlash CN_NandFlash512_st_Fun_PhyFlash;
#endif

