/*========================================Include File===========================================================*/	
	#include "..\..\..\APP\config.h"
	#include "stdlib.h"
	#ifdef De_GPRSAgreeOn_Compiler
		#include "..\..\..\miscellaneous\CodeTrans\AscNumber.h"	
		#include "..\..\..\Control\Gprs\GPRS.h"
	#endif
/*===========================================Define Data========================================================*/
	/*-------------------------------------错误代码一览表---------------------------------------------*/
	#define De_Suc_AgreeOn_Dev_Gprs								0						//成功执行
	#define De_Erro_AgreeOn_Dev_Gprs_NoOpen						1
	#define De_Erro_AgreeOn_Dev_Gprs_NoData						De_Erro_AgreeOn_Dev_Gprs_NoOpen+1
	#define De_Erro_AgreeOn_Dev_Gprs_Explain					De_Erro_AgreeOn_Dev_Gprs_NoData+1
	#define De_Erro_AgreeOn_Dev_Gprs_Legality 					De_Erro_AgreeOn_Dev_Gprs_Explain+1
	#define De_Erro_AgreeOn_Dev_Gprs_NoInit						De_Erro_AgreeOn_Dev_Gprs_Legality+1
	/*--------------------------------------程序状态控制----------------------------------------------*/
	#define De_AgreeOn_Dev_Gprs_Open							0						//本功能打开
	#define De_AgreeOn_Dev_Gprs_Close							1						//本功能关闭
/*===========================================Data Define========================================================*/
	typedef struct
	{	uint8 IMEI[7];
	}st_AgreeOn_Dev_Gprs_OpenPar;								//调用打开函数时的入口参数

	
	
	typedef struct
	{	uint16 OrderNumber;
		uint16 OrderID;
		uint16 SizeofBuf;
		uint8 AnswerFlag;
		uint8 *Buf;
	}st_st_AgreeOn_Dev_Gprs_Par;		  						//调用读函数时的函数
	typedef struct
	{	uint16 (*Init)(void);
		uint16 (*Open)(st_AgreeOn_Dev_Gprs_OpenPar	*ptst_AgreeOn_Dev_Gprs_OpenPar,uint8 fd);
		uint16 (*Close)(void);
		uint16 (*Read)(st_st_AgreeOn_Dev_Gprs_Par	*ptst_st_AgreeOn_Dev_Gprs_Par);
		uint16 (*Write)(st_st_AgreeOn_Dev_Gprs_Par	*ptst_st_AgreeOn_Dev_Gprs_Par,uint8 *Buf);
	}st_Fun_GPRSAgreeOn;
/*=========================================static Function=======================================================*/
#ifdef De_GPRSAgreeOn_Compiler	
	static uint16 Init(void);
	static uint16 Open(st_AgreeOn_Dev_Gprs_OpenPar	*ptst_AgreeOn_Dev_Gprs_OpenPar,uint8 fd);
	static uint16 Close(void);
	static uint16 Read(st_st_AgreeOn_Dev_Gprs_Par	*ptst_st_AgreeOn_Dev_Gprs_Par);
	static uint16 Write(st_st_AgreeOn_Dev_Gprs_Par	*ptst_st_AgreeOn_Dev_Gprs_Par,uint8 *Buf);

	static uint16 Read1(st_st_AgreeOn_Dev_Gprs_Par	*ptst_st_AgreeOn_Dev_Gprs_Par);
	static uint16 Write1(st_st_AgreeOn_Dev_Gprs_Par	*ptst_st_AgreeOn_Dev_Gprs_Par,uint8 *Buf);
#endif
/*===========================================Public Ram=========================================================*/
 #ifdef De_GPRSAgreeOn_Compiler	

	static st_AgreeOn_Dev_Gprs_OpenPar	CN_st_AgreeOn_Dev_Gprs_OpenPar;
	static uint16 State;
	static uint8 Gprsfd;
	static OS_EVENT	*GPRSAgreeOnSem=NULL;
	const st_Fun_GPRSAgreeOn	CN_st_Fun_GPRSAgreeOn={Init,Open,Close,Read,Write};
 #else
 	extern const st_Fun_GPRSAgreeOn	CN_st_Fun_GPRSAgreeOn;
 #endif






