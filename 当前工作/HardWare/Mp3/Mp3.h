#define MP3_H
#ifdef	MP3_H
/*===========================================include File=======================================================*/	
	#include "..\..\APP\config.h"
  	#include "stdlib.h"
	#include "..\UART\UART.h"
/*=============================================Define Data=====================================================*/
	/*++++++++++++++++++++++++++++++++++++++++错误代码一览表++++++++++++++++++++++++++++++++++++++++++++*/
	#define De_Suc_Mp3							0
	#define De_Erro_Mp3							1
	/*+++++++++++++++++++++++++++++++++++++++++程序状态字++++++++++++++++++++++++++++++++++++++++++++++*/
	#define De_Mp3_State_Play					1
	#define De_Mp3_State_Stop					0	
	
	/*++++++++++++++++++++++++++++++++++++++++HardWare+++++++++++++++++++++++++++++++++++++++++++++++++*/
	#define De_IO_Mp3_RstHigh										//Reset											
	#define De_IO_Mp3_RstLow
	#define De_IO_Mp3_State											//MP3状态							

/*=========================================Data Define=========================================================*/
	typedef struct
	{	uint8 FileName[12];						//MP3正在播放的文件名
		uint8 State;							//De_Mp3_State_Play.De_Mp3_State_Stop
	}st_Data_Mp3;

	/*++++++++++++++++++++++++++++++++++++Out Function+++++++++++++++++++++++++++++++++++++++++++++++++++*/
	typedef struct
	{	uint16 (*Init)(void);
		uint16 (*Open)(uint8 *FileName);
		uint16 (*Close)(void);
		uint16 (*Read)(st_Data_Mp3	*ptst_Data_Mp3);	
	};
/*==========================================Static Function====================================================*/
	static uint16 Init(void);
	static uint16 Open(uint8 *FileName);
	static uint16 Close(void);
	static uint16 Read(st_Data_Mp3	*ptst_Data_Mp3);

	/*++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/
	
	
	
	
	
				











#endif