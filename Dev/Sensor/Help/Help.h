/*==========================================Include Define=====================================================*/	
	#include "..\..\..\APP\config.h"
	#include "stdlib.h"
	#ifdef De_Help_Compiler
		#include "..\..\..\miscellaneous\CodeTrans\AscNumber.h"
		#include "..\..\..\miscellaneous\Date\date.h"
		#include "..\..\..\HardWare\RTC\RTC.h" 
		#include "..\_PuSensor.h"
	#endif
/*==========================================Define Data========================================================*/
	#define De_Erro_Help_Init							1
	#define De_Erro_Help_OverMaxNumber					De_Erro_Help_Init+1
	/*+++++++++++++++++++++++++++++++++++++HardWare Define+++++++++++++++++++++++++++++++++++++++++++++++*/
#ifdef De_Help_Compiler	
	#define De_IO_Acc_Function					PINSEL3 &=0xff3fffff
	#define De_IO_Acc_Open						De_IO_Acc_Function;IODIR1	&= ~(1<<27)//��ACC����
	#define De_IO_Acc_In						(IOPIN1 &(1<<27))
	/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/
	#define De_Acc_Fun_Open						1
	#define De_Acc_Fun_Close					2	
#endif

/*==========================================Static Function====================================================*/
#ifdef De_Help_Compiler	
	static uint16 Init(void);
	static uint16 Open(st_Sensor_DataPar	*ptst_Sensor_DataPar,uint8 *fd);
	static uint16 Close(uint8 fd);
	static uint16 Read(uint8 fd,void *SendBuf,void *AgreeBuf);
	static uint32 GetTimeAdd(uint8 *Small,uint8 *Big);
#endif
/*==========================================Public Ram=========================================================*/
#ifdef De_Help_Compiler	
	static OS_EVENT	*ACCSem=NULL;	
	static uint8 CN_State;	
	static uint8 DateTime[7];
	static const st_Fun_Sensor2Hard	CN_st_Fun_Sensor2Hard={Init,Open,Close,Read,NULL};
	static const st_Sensor_Par2Type	CN_st_Sensor_Par2Type=
	{	De_Sensor_WordPar_Help,De_Sensor_Par_Onoff
	};
	const st_Sensor_ParList		CN_Help_st_Sensor_ParList=
	{	&CN_st_Fun_Sensor2Hard,&CN_st_Sensor_Par2Type,sizeof(CN_st_Sensor_Par2Type)/sizeof(st_Sensor_Par2Type)
	};
#else
  	extern st_Sensor_ParList	CN_Help_st_Sensor_ParList;	
#endif


