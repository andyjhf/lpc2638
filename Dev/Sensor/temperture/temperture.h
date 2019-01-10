/*===========================================Include File=======================================================*/	
	#include "..\..\..\APP\config.h"
	#include "stdlib.h"
	#ifdef De_Temperture_Compiler
		#include "..\..\..\miscellaneous\CodeTrans\AscNumber.h"
		#include "..\..\..\miscellaneous\Arithmetic\Arithmetic.h"	
		#include "..\..\..\HardWare\UART\UART.h"
		#include "..\..\..\HardWare\RTC\RTC.h"
		#include "..\..\..\HardWare\DS18B20\DS18B20.h"
		#include "..\..\..\miscellaneous\Date\date.h"
		#include "..\_PuSensor.h"
	#endif


	/*===========================================Define Data=======================================================*/
	#define De_Suc_Temperture											0				//本页成功

	#define De_Temperture_State_Open									0				//此功能打开
	#define De_Temperture_State_Close									1				//此功能关闭

	/*++++++++++++++++++++++++++++++++++++++++错误代码一览表++++++++++++++++++++++++++++++++++++++++++++++*/
	#define De_Erro_Temperture_NoInit					              0x99	              // 初始化失败
	#define De_Erro_Temperture_OverMaxNumber						  De_Erro_Temperture_NoInit+1
	#define De_Erro_Temperture_NoWorkPar							  De_Erro_Temperture_OverMaxNumber+1
	#define De_Erro_Temperture_Fun_NoOpen							  De_Erro_Temperture_NoWorkPar+1
	#define De_Erro_Temperture_NoRead								  De_Erro_Temperture_Fun_NoOpen+1

	#ifdef De_Temperture_Compiler
	/*++++++++++++++++++++++++++++++++++++++++程序状态 ++++++++++++++++++++++++++++++++++++++++++++++*/          
        #define De_Temperture_Max_Number													2				//最大支持2路温度      
     	#define De_Temperture_Max_Dly														180 
        
	#endif
	#ifdef De_Temperture_Compiler	

		typedef struct
		{	st_Sensor_DataPar	CN_st_Temperture_DataPar;
			uint8 Type;
			uint8 State;
		}st_Temperture_Par_Oper;

		static OS_EVENT	*TempertureSem = NULL;

		static uint16 Init(void);
		static uint16 Open(st_Sensor_DataPar	*ptst_Sensor_DataPar,uint8 *fd);
		static uint16 Close(uint8 fd);
		static uint16 Read(uint8 fd,void *SendBuf,void *AgreeBuf);
		static uint16 GetState(st_Sensor_State	*ptst_Sensor_State,uint8 fd);  		
		static uint32 GetTimeAdd(uint8 *Small,uint8 *Big);
		static uint8 DateTime[7];
		static uint32 TemptureValue;

		/*======================================Public Ram=========================================================*/
		
		static const st_Sensor_Par2Type	CN_st_Sensor_Par2Type[]=
		{	
			{	De_Sensor_WordPar_Temperture_1, De_Sensor_Par_Temp},
			{	De_Sensor_WordPar_Temp, De_Sensor_Par_Temp}
		};
		static const st_Fun_Sensor2Hard	CN_st_Fun_Sensor2Hard={Init,Open,Close,Read,GetState};

		const st_Sensor_ParList		CN_Temperture_st_Sensor_ParList=
		{	&CN_st_Fun_Sensor2Hard,CN_st_Sensor_Par2Type,sizeof(CN_st_Sensor_Par2Type)/sizeof(st_Sensor_Par2Type)
		};	

		const st_Sensor_State		CN_Ba_st_Temperture_State=
		{	De_Sensor_State_Suc,De_Sensor_State_Suc,De_Sensor_State_Suc};

		static st_Temperture_Par_Oper	CN_st_Temperture_Par_Oper[De_Temperture_Max_Number];
		static st_Sensor_State   CN_st_Temperture_State[De_Temperture_Max_Number];

	#else

		extern const st_Sensor_ParList	CN_Temperture_st_Sensor_ParList;

	#endif


