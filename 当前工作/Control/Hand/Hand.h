#define Hand_H
#ifdef Hand_H
/*=========================================include File===========================================================*/	
	#include "..\..\APP\config.h"
	#include "stdlib.h"
	#ifdef De_Hand_Compiler
		#include "..\..\miscellaneous\CodeTrans\AscNumber.h"		//引用码制转换资源
		#include "..\..\miscellaneous\Arithmetic\Arithmetic.h"
		#include "..\..\HardWare\UART\UART.h" 
	#endif
/*========================================Define Data=============================================================*/
	/*+++++++++++++++++++++++++++++++++++++错误代码一览表++++++++++++++++++++++++++++++++++++++++++++++++++*/ 
	#define De_Suc_Hand							0
	#define De_Erro_Hand						1
	#define De_Hand_Use_Uart					3
	/*+++++++++++++++++++++++++++++++++++++程序状态字+++++++++++++++++++++++++++++++++++++++++++++++++++++*/
	#define De_Hand_Affair_State_Open		1						//代表事件启动
	#define De_Hand_Affair_State_Close		0
	#define De_Hand_Affair_Enable			0
	#define De_Hand_Affair_DisEnable			1	
   	
	#define De_Hand_TaskDly				      50
  	#define De_Stk_Hand							768
	#define De_Task_Hand						11
	#define	De_Hand_MaxAgreeBuf					100
	/*++++++++++++++++++++++++++++++++++++++++HardWare+需要江华峰对照实际硬件电路进行更改++++++++++++++++++++++++++++++++++++++++++++++++++*/
	#define De_Hand_HardWareIO_CTS_Input  				FIO2DIR&=0xffffDfff				
	#define De_Hand_HardWareIO_CTS_OutPut		   		FIO2DIR|=0x00002000
	#define De_Hand_HardWareIO_CTS_OutPut_Low			FIO2CLR|=0x00002000
	#define De_Hand_HardWareIO_CTS_OutPut_HIGH			FIO2SET|=0x00002000			
	#define De_Hand_HardWareIO_CTS_Data	  				(FIO2PIN&0x00002000)
	#define De_Hand_CTS_High  							0x00002000
	#define De_Hand_CTS_Low				  				0

/*=========================================Data Define============================================================*/
	/*+++++++++++++++++++++++++++++++++++++++数据结构体+++++++++++++++++++++++++++++++++++++++++++++++++++*/
	typedef struct
	{   void (* ptFun)(uint8 *Buf,uint8 DataLen);
	}st_Affair_Hand;
	typedef struct
	{	st_Affair_Hand	CN_st_Affair_Hand;
		uint8 State;
		uint8 Enable;
	}st_Control_Hand;
	/*++++++++++++++++++++++++++++++++++++Out Function++++++++++++++++++++++++++++++++++++++++++++++++++++*/
	typedef struct
	{   uint16 (*   Init)(void);
	    uint16 (*   Open)(st_Affair_Hand   *ptst_Affair_Hand);
	    uint16 (*   Close)(void);
		uint16 (*	GetEnable)(uint8 *State);
		uint16 (*	Enable)(void);
		uint16 (*	DisEnable)(void);
		uint16 (*	LCDputLine)(uint8 *Dat);
		uint16 (*	RegLine)(uint8 *Dat,uint8 DataLen);
		uint16 (*	GsmLine)(uint8 *Dat,uint8 DataLen);
		uint16 (*	GpsLine)(uint8 *Dat,uint8 DataLen);
	}st_Fun_Hand;
/*==========================================static Function==================+++================================*/
  	#ifdef De_Hand_Compiler	 		
		static	uint16 Init(void);
	    static	uint16 Open(st_Affair_Hand   *ptst_Affair_Hand);
	    static	uint16 Close(void);
		static	uint16 GetEnable(uint8 *State);
		static	uint16 Enable(void);
		static	uint16 DisEnable(void);	
		static	uint8 *SeekChar(uint8 *Buf,uint8 CharV,uint8 SizeofBuf,uint8 Number);
		static void Task(void *pData);
		static uint16 LCDputLine(uint8 *Dat);
		static uint16 RegLine(uint8 *Dat,uint8 DataLen);
		static uint16 GsmLine(uint8 *Dat,uint8 DataLen);
		static uint16 GpsLine(uint8 *Dat,uint8 DataLen);
		static uint16 ReadData(uint8 *Buf,uint16 ReadLen);
		static uint16 WriteData(uint8 *Buf,uint16 WriteLen);
 /*========================+==================Public Ram=========================================================*/
	OS_STK	Hand_Stk[De_Stk_Hand];
	st_Control_Hand		CN_st_Control_Hand;
	OS_EVENT	*HandSem; 
		const st_Fun_Hand CN_st_Fun_Hand = {Init,Open,Close,GetEnable,Enable,DisEnable,LCDputLine,
											RegLine,GsmLine,GpsLine};
    #else
		extern const st_Fun_Hand CN_st_Fun_Hand;
    #endif
	

#endif	 


