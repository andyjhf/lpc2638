/****************************************Copyright (c)**************************************************
**                               Guangzou ZLG-MCU Development Co.,LTD.
**                                      graduate school
**                                 http://www.zlgmcu.com
**
**--------------File Info-------------------------------------------------------------------------------
** File name:			target.c
** Last modified Date:	2004-09-17
** Last Version:		1.0
** Descriptions:		header file of the specific codes for LPC2100 target boards
**						Every project should include a copy of this file, user may modify it as needed
**------------------------------------------------------------------------------------------------------
** Created by:			Chenmingji
** Created date:		2004-02-02
** Version:				1.0
** Descriptions:		The original version
**
**------------------------------------------------------------------------------------------------------
** Modified by:			Chenmingji
** Modified date:		2004-09-17
** Version:				1.01
** Descriptions:		Renewed the template, added more compiler supports 
**
**------------------------------------------------------------------------------------------------------
** Modified by: silentdawn
** Modified date:2007-8-4
** Version:	
** Descriptions: 根据LPC2368的特点和NXP提供的target.c文件进行修改
**
********************************************************************************************************/

#define IN_TARGET

#include "config.h"



/******************************************************************************
** Function name:		ConfigurePLL
**
** Descriptions:		Configure PLL switching to main OSC instead of IRC
**						at power up and wake up from power down. 
**						This routine is used in TargetResetInit() and those
**						examples using power down and wake up such as
**						USB suspend to resume, ethernet WOL, and power management
**						example
** parameters:			None
** Returned value:		None
** 
******************************************************************************/
void ConfigurePLL ( void )
{
	uint32 MValue, NValue;

	if ( PLLSTAT & (1 << 25) )
    {
		PLLCON = 1;			/* Enable PLL, disconnected */
		PLLFEED = 0xaa;
		PLLFEED = 0x55;
    }

    PLLCON = 0;				/* Disable PLL, disconnected */
    PLLFEED = 0xaa;
    PLLFEED = 0x55;
    
		SCS |= 0x20;			/* Enable main OSC */
    while( !(SCS & 0x40) );	/* Wait until main OSC is usable */

    CLKSRCSEL = 0x1;		/* select main OSC, 12MHz, as the PLL clock source */

    PLLCFG = PLL_MValue | (PLL_NValue << 16);
    PLLFEED = 0xaa;
    PLLFEED = 0x55;
      
    PLLCON = 1;				/* Enable PLL, disconnected */
    PLLFEED = 0xaa;
    PLLFEED = 0x55;

    CCLKCFG = CCLKDivValue;	/* Set clock divider */
#if USE_USB
    USBCLKCFG = USBCLKDivValue;		/* usbclk = 288 MHz/6 = 48 MHz */
#endif

    while ( ((PLLSTAT & (1 << 26)) == 0) );	/* Check lock bit status */
    
    MValue = PLLSTAT & 0x00007FFF;
    NValue = (PLLSTAT & 0x00FF0000) >> 16;
    while ((MValue != PLL_MValue) && ( NValue != PLL_NValue) );

    PLLCON = 3;				/* enable and connect */
    PLLFEED = 0xaa;
    PLLFEED = 0x55;
	while ( ((PLLSTAT & (1 << 25)) == 0) );	/* Check connect bit status */
	return;
}

/******************************************************************************
** Function name:		GPIOResetInit
**
** Descriptions:		Initialize the target board before running the main() 
**				function; User may change it as needed, but may not 
**				deleted it.
**
** parameters:			None
** Returned value:		None
** 
******************************************************************************/
void GPIOResetInit( void )
{
	/* Reset all GPIO pins to default: primary function */
    PINSEL0 = 0x00000000;
    PINSEL1 = 0x00000000;
    PINSEL2 = 0x00000000;
    PINSEL3 = 0x00000000;
    PINSEL4 = 0x00000000;
    PINSEL5 = 0x00000000;
    PINSEL6 = 0x00000000;
    PINSEL7 = 0x00000000;
    PINSEL8 = 0x00000000;
    PINSEL9 = 0x00000000;
    PINSEL10 = 0x00000000;
    
    IODIR0 = 0x00000000;
    IODIR1 = 0x00000000;
		IOSET0 = 0x00000000;
    IOSET1 = 0x00000000;
    
    FIO0DIR = 0x00000000;
    FIO1DIR = 0x00000000;
    FIO2DIR = 0x00000000;
    FIO3DIR = 0x00000000;
    FIO4DIR = 0x00000000;
    
    FIO0SET = 0x00000000;
    FIO1SET = 0x00000000;
    FIO2SET = 0x00000000;
    FIO3SET = 0x00000000;
    FIO4SET = 0x00000000;
    return;        
}

/* Initialize the interrupt controller */
/******************************************************************************
** Function name:		init_VIC
**
** Descriptions:		Initialize VIC interrupt controller.
** parameters:			None
** Returned value:		None
** 
******************************************************************************/
void init_VIC(void) 
{
    uint32 i = 0;
    uint32 *vect_addr, *vect_cntl;
   	
    /* initialize VIC*/
    VICIntEnClr = 0xffffffff;
    VICVectAddr = 0;
    VICIntSelect = 0;

    /* set all the vector and vector control register to 0 */
    for ( i = 0; i < VIC_SIZE; i++ )
    {
		vect_addr = (uint32 *)(VIC_BASE_ADDR + VECT_ADDR_INDEX + i*4);
		vect_cntl = (uint32 *)(VIC_BASE_ADDR + VECT_CNTL_INDEX + i*4);
		*vect_addr = 0x0;	
		*vect_cntl = 0xF;
    }
    return;
}
/*********************************************************************************************************
** Function name:			TargetResetInit
**
** Descriptions:			Initialize the target 
**
** input parameters:		None
** Returned value:			None
**         
** Used global variables:	None
** Calling modules:			None
**
** Created by:				Chenmingji
** Created Date:			2004/02/02
**-------------------------------------------------------------------------------------------------------
** Modified by:
** Modified date:
**------------------------------------------------------------------------------------------------------
********************************************************************************************************/
void TargetResetInit(void)
{
#ifdef __DEBUG_RAM    
    MEMMAP = 0x2;			/* remap to internal RAM */
#endif

#ifdef __DEBUG_FLASH    
    MEMMAP = 0x1;			/* remap to internal flash */
#endif

#if USE_USB
	PCONP |= 0x80000000;		/* Turn On USB PCLK */
#endif
	/* Configure PLL, switch from IRC to Main OSC */
	ConfigurePLL();

  /* Set system timers for each component */
#if (Fpclk / (Fcclk / 4)) == 1
    PCLKSEL0 = 0x00000000;	/* PCLK is 1/4 CCLK */
    PCLKSEL1 = 0x00000000;
#endif
#if (Fpclk / (Fcclk / 4)) == 2
    PCLKSEL0 = 0xAAAAAAAA;	/* PCLK is 1/2 CCLK */
    PCLKSEL1 = 0xAAAAAAAA;	 
#endif
#if (Fpclk / (Fcclk / 4)) == 4
    PCLKSEL0 = 0x55555555;	/* PCLK is the same as CCLK */
    PCLKSEL1 = 0x55555555;	
#endif

    /* Set memory accelerater module*/
    MAMCR = 0;
#if Fcclk < 20000000
    MAMTIM = 1;
#else
#if Fcclk < 40000000
    MAMTIM = 2;
#else
    MAMTIM = 3;
#endif
#endif
    MAMCR = 2;

    GPIOResetInit();

	init_VIC();
    return;
}

/******************************************************************************
** Function name:		install_irq
**
** Descriptions:		Install interrupt handler
** parameters:			Interrupt number, interrupt handler address, 
**						interrupt priority
** Returned value:		true or false, return false if IntNum is out of range
** 
** Used global variables:	None
** Calling modules:			None
**
** Added by:silentdawn	
**
******************************************************************************/
uint32 Install_IRQ( uint32 IntNumber, void *HandlerAddr, uint32 Priority )
{
    uint32 *vect_addr;
    uint32 *vect_cntl;
      
    VICIntEnClr = 1 << IntNumber;	/* Disable Interrupt */
    if ( IntNumber >= VIC_SIZE )
    {
		return ( FALSE );
    }
    else
    {
		/* find first un-assigned VIC address for the handler */
		vect_addr = (uint32 *)(VIC_BASE_ADDR + VECT_ADDR_INDEX + IntNumber*4);
		vect_cntl = (uint32 *)(VIC_BASE_ADDR + VECT_CNTL_INDEX + IntNumber*4);
		*vect_addr = (uint32)HandlerAddr;	/* set interrupt vector */
		*vect_cntl = Priority;
		VICIntEnable = 1 << IntNumber;	/* Enable Interrupt */
		return( TRUE );
    }
}


void init_port(void)
 {

//LPC2368开发板的LED是采用P2.0~P2.7
 //port initialized
// FIO2DIR=0x000000FF;

   	IODIR1  |= ((uint32 )1<<31);IOSET1 |= ((uint32 )1<<31);
//	IODIR0  |= (1<<21);IOSET0 |= (1<<21);
	IODIR0  |= ((uint32 )1<<26);IOSET0 |= ((uint32 )1<<26);	
// FIO2SET=0x000000FF; //ALL LED OFF

 }

/*********************************************************************************************************
** Function name:			IRQ_Exception
**
** Descriptions:			interrupt exceptional handler , change it as needed
**
** input parameters:		None
** Returned value:			None
**         
** Used global variables:	None
** Calling modules:			None
**
** Created by:				Chenmingji
** Created Date:			2004/02/02
**-------------------------------------------------------------------------------------------------------
** Modified by:
** Modified date:
**------------------------------------------------------------------------------------------------------
********************************************************************************************************/
void IRQ_Exception(void)
{
    while(1);                   // change it to your code  这一句替换为自己的代码
}

/*********************************************************************************************************
** Function name:			FIQ_Exception
**
** Descriptions:			Fast interrupt exceptional handler , change it as needed
**
** input parameters:		None
** Returned value:			None
**         
** Used global variables:	None
** Calling modules:			None
**
** Created by:				Chenmingji
** Created Date:			2004/02/02
**-------------------------------------------------------------------------------------------------------
** Modified by:
** Modified date:
**------------------------------------------------------------------------------------------------------
********************************************************************************************************/
void FIQ_Exception(void)
{
    while(1);                   // change it to your code  这一句替换为自己的代码
}
/*********************************************************************************************************
** Function name:			Timer0_Exception
**
** Descriptions:			Timer0 interrupt service function
**
** input parameters:		None
** Returned value:			None
**         
** Used global variables:	None
** Calling modules:			None
**
** Created by:				Chenmingji
** Created Date:			2004/02/02
**-------------------------------------------------------------------------------------------------------
** Modified by:
** Modified date:
**------------------------------------------------------------------------------------------------------
********************************************************************************************************/
void Timer0_Exception(void)
{
    T0IR = 0x01;
    VICVectAddr = 0;            //interrupt close 通知中断控制器中断结束
    OSTimeTick();
}

/*********************************************************************************************************
** Function name:			Timer0Init
**
** Descriptions:			Initialize the Time0
**
** input parameters:		None
** Returned value:			None
**         
** Used global variables:	None
** Calling modules:			None
**
** Created by:				Chenmingji
** Created Date:			2004/02/02
**-------------------------------------------------------------------------------------------------------
** Modified by:
** Modified date:
**------------------------------------------------------------------------------------------------------
********************************************************************************************************/
void Timer0Init(void)
{
    T0IR = 0xffffffff;
    T0TC = 0;
    T0TCR = 0x01;
    T0MCR = 0x03;
    T0MR0 = (Fpclk / OS_TICKS_PER_SEC);
	
 }
/*********************************************************************************************************
** Function name:			VIC_Setup
**
** Descriptions:			distribute VIC
**
** input parameters:		None
** Returned value:			None
**         
** Used global variables:	None
** Calling modules:			None
**
** Created by:				silentdawn
** Created Date:			2004/02/02
**-------------------------------------------------------------------------------------------------------
** Modified by:
** Modified date:
**------------------------------------------------------------------------------------------------------
********************************************************************************************************/
void VIC_Setup(void)
{
//	extern void IRQ_Handler(void);
	extern void Timer0_Handler(void);
	extern void Uart0_Handler(void);
	extern void Uart1_Handler(void);
	extern void Uart2_Handler(void);
	extern void Uart3_Handler(void);
	extern void CAN_Handler(void);
	extern void Timer1_Handler(void);
	extern void Timer2_Handler(void);
	extern void EINT2_Handler(void);
  //分配给定时器0优先级为0

  Install_IRQ(EINT2_INT,(void *)EINT2_Handler,0);
  Install_IRQ(TIMER1_INT,(void *)Timer1_Handler,1);
  Install_IRQ(TIMER2_INT,(void *)Timer2_Handler,2);
  Install_IRQ(TIMER0_INT,(void *)Timer0_Handler,3);
  Install_IRQ(UART0_INT,(void *)Uart0_Handler,4);
  Install_IRQ(UART1_INT,(void *)Uart1_Handler,5);
  Install_IRQ(UART2_INT,(void *)Uart2_Handler,6);
  Install_IRQ(UART3_INT,(void *)Uart3_Handler,7);
  Install_IRQ(CAN_INT,(void *)CAN_Handler,8);  
  
}

/*********************************************************************************************************
** Function name:			TargetInit
**
** Descriptions:			Initialize the target board; it is called in a necessary place, change it as 
**							needed
**
** input parameters:		None
** Returned value:			None
**         
** Used global variables:	None
** Calling modules:			None
**
** Created by:				Chenmingji
** Created Date:			2004/02/02
**-------------------------------------------------------------------------------------------------------
** Modified by:
** Modified date:
**------------------------------------------------------------------------------------------------------
********************************************************************************************************/
void TargetInit(void)
{
    OS_ENTER_CRITICAL();
    srand((uint32) TargetInit);
    VIC_Setup();
	InitWTD();
    Timer0Init();
		init_port();
    OS_EXIT_CRITICAL();
}

// 看门狗喂狗
void WatchDog(void) 
{
	ClrWDI;	
	SetWDI;
	SetWDI;		
	ClrWDI;	 	
}

static void InitWTD(void)
{
	IODIR1 |= (1<<WDI);  //看门狗喂狗脚	
}

/*********************************************************************************************************
**                  以下为一些与系统相关的库函数的实现
**                  具体作用请ads的参考编译器与库函数手册
**                  用户可以根据自己的要求修改        
********************************************************************************************************/
/*********************************************************************************************************
**                  The implementations for some library functions
**                  For more details, please refer to the ADS compiler handbook and The library 
**					function manual
**                  User could change it as needed       
********************************************************************************************************/

/*
这段程序，，去除掉。。。
by mcu123
在startup.s 中添加了
*/
/*
#include "rt_sys.h"
#include "stdio.h"

#pragma import(__use_no_semihosting_swi)

        int __rt_div0(int a)
{
    a = a;
    return 0;
}

        int fputc(int ch,FILE *f)
{
    ch = ch;
    f = f;
    return 0;
}

    int fgetc(FILE *f)
{
    f = f;
    return 0;
}


        int _sys_close(FILEHANDLE fh)
{
    fh = fh;
    return 0;
}

        int _sys_write(FILEHANDLE fh, const unsigned char * buf,
                      unsigned len, int mode)
{
    fh = fh;
    buf = buf;
    len =len;
    mode = mode;
    return 0;
}
        int _sys_read(FILEHANDLE fh, unsigned char * buf,
                     unsigned len, int mode)
{
    fh = fh;
    buf = buf;
    len =len;
    mode = mode;
    
    return 0;
}

       void _ttywrch(int ch)
{
    ch = ch;
}

        int _sys_istty(FILEHANDLE fh)
{
    fh = fh;
    return 0;
}
        int _sys_seek(FILEHANDLE fh, long pos)
{
    fh = fh;
    return 0;
}
        int _sys_ensure(FILEHANDLE fh)
{
    fh = fh;
    return 0;
}

        long _sys_flen(FILEHANDLE fh)
{
    fh = fh;
    return 0;
}
       int _sys_tmpnam(char * name, int sig, unsigned maxlen)
{
    name = name;
    sig = sig;
    maxlen = maxlen;
    return 0;
}

        void _sys_exit(int returncode)
{
    returncode = returncode;
}

        char *_sys_command_string(char * cmd, int len)
{
    cmd = cmd;
    len = len;
    return 0;
}
*/

/*********************************************************************************************************
**                            End Of File
********************************************************************************************************/
