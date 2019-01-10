#include "..\..\Public_H\DePublic.h"
#ifdef	De_Compiler_HardWare_RTC
/*=======================================Include File======================================================*/
	#include "..\..\APP\config.h"
	#include "stdlib.h"	
	#ifdef De_RTC_Compiler
		#include "..\..\miscellaneous\CodeTrans\AscNumber.h"
		#include "..\..\miscellaneous\Date\Date.h"
	#endif
/*=======================================Define	Data=======================================================*/
 	#define OS_ADD							//������ò���ϵͳ��ģʽ
	/*++++++++++++++++++++++++++++++++++�������һ����+++++++++++++++++++++++++++++++++++++++++++++*/
	#define De_Suc_RTC						0								//�ɹ�����
	#define De_Erro_RTC_Write				De_Erro_RTC						//дʱ��ʧ��
	#define De_Erro_RTC_Init				De_Erro_RTC_Write+1				//ʱ�ӳ�ʼ��ʧ��
	/*+++++++++++++++++++++++++++++++++++�Ĵ�������+++++++++++++++++++++++++++++++++++++++++++++++*/	
  	#define PREINT_RTC	Fpclk / 32768 - 1   /* Prescaler value, integer portion, PCLK = 15Mhz */
	#define PREFRAC_RTC	Fpclk % 32768       /* Prescaler value, fraction portion, PCLK = 15Mhz */

	#define ILR_RTCCIF	0x01
	#define ILR_RTCALF	0x02

	#define CCR_CLKEN	0x01
	#define CCR_CTCRST	0x02
	#define CCR_CLKSRC	0x10
/*========================================���ݽṹ�嶨��==================================================*/
	typedef struct
	{	uint16 (*	Init)(void);
		/*	��������:��ʱ��
			��ڲ���:	���������Buf		ѹ��BCD��		��ʽΪ��YYYYMMDD HHMM SS
			����ֵ:		De_Suc_RTC		�ɹ���ȡ
						��De_Suc_RTC	ʧ�ܣ���<�������һ����>
		*/	 				
		uint16 (*	Read)(uint8	*Buf);
		/*	�������ܣ�дʱ��
			��ڲ�����	���������Buf		ѹ��BCD��		��ʽΪ: YYYYMMDD HHMM SS
			����ֵ��	De_Suc_RTC		�ɹ�д��
						��De_Suc_RTC	ʧ��  ��<�������һ����>
		*/
		uint16 (*	Write)(uint8 *Buf);
	}st_Fun_RTC;

/*========================================staic Function===================================================*/
	#ifdef De_RTC_Compiler
		static uint16 Init(void);
		static uint16 Read(uint8 *Buf);
		static uint16 Write(uint8 *Buf);

		static uint16 Init1(void);
		static uint16 Read1(uint8 *Buf);
		static uint16 Write1(uint8 *Buf);
		
		
		static void RTCInit( void );
		static void RTCStop( void );
		static void RTC_CTCReset( void );
		static void RTCStart( void );
/*==========================================Public Ram====================================================*/
		#ifdef	OS_ADD
			static OS_EVENT	*RTCSem=NULL;
		#endif
		const st_Fun_RTC	CN_st_Fun_RTC={Init,Read,Write};
	#else
		extern st_Fun_RTC	CN_st_Fun_RTC;
	#endif
#endif




