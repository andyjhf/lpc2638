#define De_RTC_Compiler
#include "RTC.h"
#ifdef	De_Compiler_HardWare_RTC
/*=====================================================================================================*/

/*=====================================================================================================*/
static uint16 Init(void)
{	uint16 Result;
	if(RTCSem!=NULL)
		return De_Suc_RTC;
	Result=Init1();
	if(Result!=De_Suc_RTC)
		return Result;
	#ifdef OS_ADD
	RTCSem=OSSemCreate(1); 
	if(RTCSem==NULL)
		return De_Erro_RTC_Init;	
	#endif
	return De_Suc_RTC;
}

static uint16 Read(uint8 *Buf)
{	uint8 err;
	uint16 Result;
	#ifdef OS_ADD
	OSSemPend(RTCSem, 0, &err);				
	#endif
	Result=Read1(Buf);
	#ifdef OS_ADD
	OSSemPost(RTCSem);
	#endif
	return Result;
}

static uint16 Write(uint8 *Buf)
{	uint8 err;
	uint16 Result;
	#ifdef OS_ADD
	OSSemPend(RTCSem, 0, &err);				
	#endif
	Result=Write1(Buf);
	#ifdef OS_ADD
	OSSemPost(RTCSem);
	#endif
	return Result;
}

static uint16 Init1(void)
{	RTCInit();					
	return De_Suc_RTC;
}

static uint16 Read1(uint8 *Buf)
{	uint16 Result;
	uint8 Timer[7];
	Timer[0]=RTC_YEAR/100;		Timer[1]=RTC_YEAR%100;
	Timer[2]=RTC_MONTH;	Timer[3]=RTC_DOM;
	Timer[4]=RTC_HOUR;	Timer[5]=RTC_MIN;
	Timer[6]=RTC_SEC;
	CN_st_Fun_AscNumber.Hex2Bcd(Timer,Buf,sizeof(Timer));
	if((Result=CN_st_Fun_Date.Juge(Buf,De_Type_Date_Second))!=De_Suc_Date)
		return Result;
	//CN_st_Fun_AscNumber.MoveByte(Buf,Timer,sizeof(Timer));
//	RTCStart();	    
	return De_Suc_RTC;
}

static uint16 Write1(uint8 *Buf)
{	uint8 Timer[7];
	uint16 Result;
	if((Result=CN_st_Fun_Date.Juge(Buf,De_Type_Date_Second))!=De_Suc_Date)
		return Result;
	CN_st_Fun_AscNumber.Bcd2Hex(Buf,Timer,sizeof(Timer));
//	RTCStop();
	RTC_YEAR=Timer[0]*100+Timer[1];RTC_MONTH=Timer[2];RTC_DOM=Timer[3];
	RTC_HOUR=Timer[4];RTC_MIN=Timer[5];RTC_SEC=Timer[6];
//   	RTCStart();
	if(Read1(Timer)!=De_Suc_RTC)
		return De_Erro_RTC_Write;
	return De_Suc_RTC;
}
/*=====================================================支撑函数===============================================*/

/*****************************************************************************
** Function name:		RTCInit
**
** Descriptions:		Initialize RTC timer
**
** parameters:			None
** Returned value:		None
** 
*****************************************************************************/
static void RTCInit( void )
{
    /*--- Initialize registers ---*/    
//    RTC_AMR = 0;
//    RTC_CIIR = 0;
//    RTC_CCR = 0x01;
//    RTC_PREINT = PREINT_RTC;
//    RTC_PREFRAC = PREFRAC_RTC;
	
	RTC_CCR  = 0x00;
	RTC_CISS &= ~(1<<7);      //禁止次秒级中断
	RTC_AMR  |= 0xff;         //禁止报警	
	RTC_CCR  |= (1<<4);  //选择独立时钟
//	RTC_CIIR |= (1<<IMSEC);	  //设置秒中断
//	RTC_ILR  |= (1<<RTCCIF);  //清除中断标志
	RTC_CCR  |= (1<<0) ;  //使能定时器

    return;
}

/*****************************************************************************
** Function name:		RTCStart
**
** Descriptions:		Start RTC timer
**
** parameters:			None
** Returned value:		None
** 
*****************************************************************************/
static void RTCStart( void ) 
{
    /*--- Start RTC counters ---*/
    RTC_CCR |= CCR_CLKEN;
    RTC_ILR = 0;
    return;
}

/*****************************************************************************
** Function name:		RTCStop
**
** Descriptions:		Stop RTC timer
**
** parameters:			None
** Returned value:		None
** 
*****************************************************************************/
static void RTCStop( void )
{   
    /*--- Stop RTC counters ---*/
    RTC_CCR &= ~CCR_CLKEN;
    return;
} 

/*****************************************************************************
** Function name:		RTC_CTCReset
**
** Descriptions:		Reset RTC clock tick counter
**
** parameters:			None
** Returned value:		None
** 
*****************************************************************************/
static void RTC_CTCReset( void )
{   
    /*--- Reset CTC ---*/
    RTC_CCR |= CCR_CTCRST;
    return;
}
#endif
