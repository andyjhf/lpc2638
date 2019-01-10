/****************************************Copyright (c)**************************************************
**                               Guangzou ZLG-MCU Development Co.,LTD.
**                                      graduate school
**                                 http://www.zlgmcu.com
**
**--------------File Info-------------------------------------------------------------------------------
** File Name: config.h
** Last modified Date:  2004-09-17
** Last Version: 1.0
** Descriptions: User Configurable File
**
**------------------------------------------------------------------------------------------------------
** Created By: Chenmingji
** Created date:   2004-09-17
** Version: 1.0
** Descriptions: First version
**
**------------------------------------------------------------------------------------------------------
** Modified by: silentdawn
** Modified date:2007-08-04
** Version:      
** Descriptions: ��ֲ��MB2300�������ϣ�оƬ����LPC2368��
**
********************************************************************************************************/
#ifndef __CONFIG_H 
#define __CONFIG_H
//��һ������Ķ�
//This segment should not be modified
#ifndef TRUE
#define TRUE  1
#endif

#ifndef FALSE
#define FALSE 0
#endif

typedef unsigned char  uint8;                   /* defined for unsigned 8-bits integer variable 	�޷���8λ���ͱ���  */
typedef signed   char  int8;                    /* defined for signed 8-bits integer variable		�з���8λ���ͱ���  */
typedef unsigned short uint16;                  /* defined for unsigned 16-bits integer variable 	�޷���16λ���ͱ��� */
typedef signed   short int16;                   /* defined for signed 16-bits integer variable 		�з���16λ���ͱ��� */
typedef unsigned int   uint32;                  /* defined for unsigned 32-bits integer variable 	�޷���32λ���ͱ��� */
typedef signed   int   int32;                   /* defined for signed 32-bits integer variable 		�з���32λ���ͱ��� */
typedef float          fp32;                    /* single precision floating point variable (32bits) �����ȸ�������32λ���ȣ� */
typedef double         fp64;                    /* double precision floating point variable (64bits) ˫���ȸ�������64λ���ȣ� */

/********************************/
/*      uC/OS-II specital code  */
/*      uC/OS-II���������      */
/********************************/

#define     USER_USING_MODE    0x10                    /*  User mode ,ARM 32BITS CODE �û�ģʽ,ARM����                  */
// 
                                                     /*  Chosen one from 0x10,0x30,0x1f,0x3f.ֻ����0x10,0x30,0x1f,0x3f֮һ       */
#include "Includes.h"


/********************************/
/*      ARM���������           */
/*      ARM specital code       */
/********************************/
//��һ������Ķ�
//This segment should not be modify

//��ΪLPC2368оƬ��ͷ�ļ�
#include    "LPC23xx.h"


/********************************/
/*     Ӧ�ó�������             */
/*Application Program Configurations*/
/********************************/
//���¸�����Ҫ�Ķ�
//This segment could be modified as needed.
#include    <stdio.h>
#include    <ctype.h>
#include    <stdlib.h>
#include    <setjmp.h>
#include    <rt_misc.h>


/********************************/
/*     �����ӵ�����             */
/*Configuration of the example */
/********************************/

//NXP �ṩ����������
/* If USB device is used, the CCLK setting needs to be 57.6Mhz, CCO will be 288Mhz
to get precise USB clock 48Mhz. If USB is not used, you set any clock you want
based on the table below. If you want to use USB, change "define USE_USB" from 0 to 1 */

#define	USE_USB					1

/* PLL Setting Table Matrix */
/* 	
	Main Osc.	CCLKCFG		Fcco		Fcclk 		M 	N
	12Mhz		29		300Mhz		10Mhz		24	1
	12Mhz		35		360Mhz		10Mhz		14	0					
	12Mhz		27		336Mhz		12Mhz		13	0
	12Mhz		14		300Mhz		20Mhz		24	1		
	12Mhz		17		360Mhz		20Mhz		14	0
	12Mhz		13		336Mhz		24Mhz		13	0
	12Mhz		11		300Mhz		25Mhz		24	1   
	12Mhz		9		300Mhz		30Mhz		24	1
	12Mhz		11		360Mhz		30Mhz		14	0
	12Mhz		9		320Mhz		32Mhz		39	2
	12Mhz		9		350Mhz		35Mhz		174	11
	12Mhz		7		312Mhz		39Mhz		12	0
 	12Mhz		8		360Mhz		40Mhz		14	0 
	12Mhz		7		360Mhz		45Mhz		14	0
	12Mhz		6		336Mhz		48Mhz		13	0  
	12Mhz		5		300Mhz		50Mhz		24	1
	12Mhz		5		312Mhz		52Mhz		12	0
	12Mhz		5		336Mhz		56Mhz		13	0		
 	12Mhz		4		300Mhz		60Mhz		24	1		
  	12Mhz		4		320Mhz		64Mhz		39	2
	12Mhz		4		350Mhz		70Mhz		174	11
	12Mhz		4		360Mhz		72Mhz		14	0		
	12Mhz		3		300Mhz		75Mhz		24	1
	12Mhz		3		312Mhz		78Mhz		12	0  
	12Mhz		3		320Mhz		80Mhz		39	2
	12Mhz		3		336Mhz		84Mhz		13	0 
*/

#define WDI      18		//  P1.18  WDI     ���Ź�ι���ź�
#define SetWDI   IOSET1 |= (1<<WDI)
#define ClrWDI   IOCLR1 |= (1<<WDI)
void WatchDog(void);
static void InitWTD(void);


#if USE_USB		/* 1 is USB, 0 is non-USB related */  
/* Fcck = 57.6Mhz, Fosc = 288Mhz, and USB 48Mhz */

#define PLL_MValue			23//11	//		  //��Pclk�ĳ�24MHz������CAN�����ʸ�׼ȷ
#define PLL_NValue			1//	 0	//
#define CCLKDivValue		5//	 4	//
#define USBCLKDivValue		5

/* System configuration: Fosc, Fcclk, Fcco, Fpclk must be defined */
/* PLL input Crystal frequence range 4KHz~20MHz. */
#define Fosc	12000000
/* System frequence,should be less than 80MHz. */
#define Fcclk	48000000//	  57600000	 //
#define Fcco	288000000

#else

/* Fcck = 50Mhz, Fosc = 300Mhz, and USB 48Mhz */
#define PLL_MValue			24
#define PLL_NValue			1
#define CCLKDivValue		5
#define USBCLKDivValue		6

/* System configuration: Fosc, Fcclk, Fcco, Fpclk must be defined */
/* PLL input Crystal frequence range 4KHz~20MHz. */
#define Fosc	12000000
/* System frequence,should be less than 80MHz. */
#define Fcclk	50000000
#define Fcco	300000000

#endif

/* APB clock frequence , must be 1/2/4 multiples of ( Fcclk/4 ). */
/* If USB is enabled, the minimum APB must be greater than 16Mhz */ 
#if USE_USB
#define Fpclk	(Fcclk / 2)
#else
#define Fpclk	(Fcclk / 4)
#endif


#include    "target.h"              //This line may not be deleted ��һ�䲻��ɾ��
//#include    "..\Arm_Pc\pc.h"

//����IRQ�жϵ�һЩ��������һЩͷ�ļ���������ӵ�����
#include "irq.h"

#endif
/*********************************************************************************************************
**                            End Of File
********************************************************************************************************/
