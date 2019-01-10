/*==========================================Include Define=====================================================*/	
	#include "..\..\..\APP\config.h"
	#include "stdlib.h"
	#ifdef De_Oil_Compiler
		#include "..\..\..\miscellaneous\CodeTrans\AscNumber.h"
		#include "..\..\..\miscellaneous\Date\date.h"	
		#include "..\..\..\HardWare\ADC\ADCHard.h"
		#include "..\_PuSensor.h"
	#endif
/*==========================================Define Data========================================================*/
	#define De_Erro_Oil_Init							1
	#define De_Erro_Oil_OverMaxNumber					De_Erro_Oil_Init+1
	#define De_Erro_Oil_Fun_NoOpen						De_Erro_Oil_OverMaxNumber+1
	/*+++++++++++++++++++++++++++++++++++++HardWare Define+++++++++++++++++++++++++++++++++++++++++++++++*/
#ifdef De_Oil_Compiler	
	#define De_Oil_Use_Port								De_Adc_Port_1								
	#define De_Oil_Fun_Open								1
	#define De_Oil_Fun_Close							2
	#define De_Oil_Max_Dly								3	
#endif

/*==========================================Static Function====================================================*/
#ifdef De_Oil_Compiler	
	static uint16 Init(void);
	static uint16 Open(st_Sensor_DataPar	*ptst_Sensor_DataPar,uint8 *fd);
	static uint16 Close(uint8 fd);
	static uint16 Read(uint8 fd,void *SendBuf,void *AgreeBuf);
	static uint32 GetTimeAdd(uint8 *Small,uint8 *Big);
#endif
/*==========================================Public Ram=========================================================*/
#ifdef De_Oil_Compiler	
	static OS_EVENT	*OilSem=NULL;	
	static uint8 CN_State;	
	static const st_Fun_Sensor2Hard	CN_st_Fun_Sensor2Hard={Init,Open,Close,Read,NULL};
	static const st_Sensor_Par2Type	CN_st_Sensor_Par2Type=
	{	De_Sensor_WordPar_Oil1,De_Sensor_Par_Oil
	};
	const st_Sensor_ParList		CN_Oil_st_Sensor_ParList=
	{	&CN_st_Fun_Sensor2Hard,&CN_st_Sensor_Par2Type,sizeof(CN_st_Sensor_Par2Type)/sizeof(st_Sensor_Par2Type)
	};
	uint32 CN_VoVal[10];
	static uint8 DateTime[7];
	uint8 CN_Point;
#else
  	extern st_Sensor_ParList	CN_Oil_st_Sensor_ParList;	
#endif


