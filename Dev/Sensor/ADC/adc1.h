/*==========================================Include Define=====================================================*/	
	#include "..\..\..\APP\config.h"
	#include "stdlib.h"
	#ifdef De_Adc1_Compiler
		#include "..\..\..\miscellaneous\CodeTrans\AscNumber.h"
		#include "..\..\..\miscellaneous\Date\date.h"	
		#include "..\..\..\HardWare\ADC\ADCHard.h"
		#include "..\_PuSensor.h"
	#endif
/*==========================================Define Data========================================================*/
	#define De_Erro_Adc1_Init							1
	#define De_Erro_Adc1_OverMaxNumber					De_Erro_Adc1_Init+1
	#define De_Erro_Adc1_Fun_NoOpen						De_Erro_Adc1_OverMaxNumber+1
	/*+++++++++++++++++++++++++++++++++++++HardWare Define+++++++++++++++++++++++++++++++++++++++++++++++*/
#ifdef De_Adc1_Compiler	
	#define De_Oil_Use_Port								De_Adc_Port_2								
	#define De_Oil_Fun_Open								1
	#define De_Oil_Fun_Close							2
	#define De_Oil_Max_Dly								3	
#endif

/*==========================================Static Function====================================================*/
#ifdef De_Adc1_Compiler	
	static uint16 Init(void);
	static uint16 Open(st_Sensor_DataPar	*ptst_Sensor_DataPar,uint8 *fd);
	static uint16 Close(uint8 fd);
	static uint16 Read(uint8 fd,void *SendBuf,void *AgreeBuf);
	static uint32 GetTimeAdd(uint8 *Small,uint8 *Big);
#endif
/*==========================================Public Ram=========================================================*/
#ifdef De_Adc1_Compiler	
	static OS_EVENT	*OilSem=NULL;	
	static uint8 CN_State;	
	static const st_Fun_Sensor2Hard	CN_st_Fun_Sensor2Hard={Init,Open,Close,Read,NULL};
	static const st_Sensor_Par2Type	CN_st_Sensor_Par2Type=
	{	De_Sensor_WordPar_VaCheck,De_Sensor_Par_ADC
	};
	const st_Sensor_ParList		CN_Adc1_st_Sensor_ParList=
	{	&CN_st_Fun_Sensor2Hard,&CN_st_Sensor_Par2Type,sizeof(CN_st_Sensor_Par2Type)/sizeof(st_Sensor_Par2Type)
	};
#else
  	extern st_Sensor_ParList	CN_Adc1_st_Sensor_ParList;	
#endif


