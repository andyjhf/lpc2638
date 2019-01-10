/*==========================================Include Define=====================================================*/	
	#include "..\..\..\APP\config.h"
	#include "stdlib.h"
	#ifdef De_UartTzxy_Compiler
		#include "..\..\..\miscellaneous\CodeTrans\AscNumber.h"
		#include "..\..\..\miscellaneous\Date\date.h"
		#include "..\..\..\HardWare\UART\UART.h"
		#include "..\_PuSensor.h"
	#endif
/*==========================================Define Data========================================================*/
	#define De_Erro_UartTzxy_Init									1
	#define De_Erro_UartTzxy_OverMaxNumber							De_Erro_UartTzxy_Init+1
	#define De_Erro_AgreeOn_Dev_Uart_NoData							De_Erro_UartTzxy_OverMaxNumber+1						
	/*+++++++++++++++++++++++++++++++++++++HardWare Define+++++++++++++++++++++++++++++++++++++++++++++++*/
#ifdef De_UartTzxy_Compiler	
	#define De_GprsTzxy_Fun_Open									1
	#define De_GprsTzxy_Fun_Close									2
	#define De_GprsTzxy_Dev_Number									2
	#define De_GprsTzxy_Nofd										0xff
#endif

/*==========================================Static Function====================================================*/
#ifdef De_UartTzxy_Compiler	
	static uint16 Init(void);
	static uint16 Open(st_Sensor_DataPar	*ptst_Sensor_DataPar,uint8 *fd);
	static uint16 Close(uint8 fd);
	static uint16 Read(uint8 fd,void *SendBuf,void *AgreeBuf);
	static uint16 Send(uint8 fd,uint8 *Buf,uint16 DataLen);
	static uint16 Agree(uint8 fd,uint8 *Buf,uint16 *ReLen);
#endif
/*==========================================Public Ram=========================================================*/
#ifdef De_UartTzxy_Compiler	
	static OS_EVENT	*GprsSem=NULL;	
	static uint8 CN_State[De_GprsTzxy_Dev_Number];
	static uint8 CN_Gprsfd[De_GprsTzxy_Dev_Number];	
	static const st_Fun_Sensor2Hard	CN_st_Fun_Sensor2Hard={Init,Open,Close,Read,NULL};
	static const st_Sensor_Par2Type	CN_st_Sensor_Par2Type[]=
	{	{	De_Sensor_WordPar_UartTzxy_1,De_Sensor_Par_Tzxy},
		{	De_Sensor_WordPar_UartTzxy_2,De_Sensor_Par_Tzxy}
	};
	const st_Sensor_ParList		CN_UartTzxy_st_Sensor_ParList=
	{	&CN_st_Fun_Sensor2Hard,CN_st_Sensor_Par2Type,sizeof(CN_st_Sensor_Par2Type)/sizeof(st_Sensor_Par2Type)
	};
#else
  	extern st_Sensor_ParList	CN_UartTzxy_st_Sensor_ParList;	
#endif


