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
 	#define OS_ADD							//定义采用操作系统的模式
	/*++++++++++++++++++++++++++++++++++错误代码一览表+++++++++++++++++++++++++++++++++++++++++++++*/
	#define De_Suc_RTC						0								//成功返回
	#define De_Erro_RTC_Write				De_Erro_RTC						//写时钟失败
	#define De_Erro_RTC_Init				De_Erro_RTC_Write+1				//时钟初始化失败
	/*+++++++++++++++++++++++++++++++++++寄存器定义+++++++++++++++++++++++++++++++++++++++++++++++*/	
  	#define PREINT_RTC	Fpclk / 32768 - 1   /* Prescaler value, integer portion, PCLK = 15Mhz */
	#define PREFRAC_RTC	Fpclk % 32768       /* Prescaler value, fraction portion, PCLK = 15Mhz */

	#define ILR_RTCCIF	0x01
	#define ILR_RTCALF	0x02

	#define CCR_CLKEN	0x01
	#define CCR_CTCRST	0x02
	#define CCR_CLKSRC	0x10
/*========================================数据结构体定义==================================================*/
	typedef struct
	{	uint16 (*	Init)(void);
		/*	函数功能:读时钟
			入口参数:	输出参数：Buf		压缩BCD码		格式为：YYYYMMDD HHMM SS
			返回值:		De_Suc_RTC		成功读取
						非De_Suc_RTC	失败，见<错误代码一览表>
		*/	 				
		uint16 (*	Read)(uint8	*Buf);
		/*	函数功能：写时钟
			入口参数：	输入参数：Buf		压缩BCD码		格式为: YYYYMMDD HHMM SS
			返回值：	De_Suc_RTC		成功写入
						非De_Suc_RTC	失败  见<错误代码一览表>
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




