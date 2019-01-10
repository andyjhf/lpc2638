/*===========================================Include File=======================================================*/	
	#include "..\..\..\APP\config.h"
	#include "stdlib.h"
	
	#ifdef De_Mileage_Compiler
		#include "..\..\..\miscellaneous\CodeTrans\AscNumber.h"
		#include "..\..\..\miscellaneous\Arithmetic\Arithmetic.h"	
		#include "..\..\..\HardWare\UART\UART.h"   	
		#include "..\..\..\miscellaneous\Date\date.h"
		#include "..\_PuSensor.h"	  
		#include "math.h"
	#endif

	/*===========================================Define Data=======================================================*/
	#define De_Suc_Mileage											0				//本页成功

	#define De_Mileage_State_Open									0				//此功能打开
	#define De_Mileage_State_Close									1				//此功能关闭
	
	#define De_Mileage_Max_Dly									    1

	/*++++++++++++++++++++++++++++++++++++++++错误代码一览表++++++++++++++++++++++++++++++++++++++++++++++*/
	#define De_Erro_Mileage_NoInit					              0x99	              // 初始化失败
	#define De_Erro_Mileage_OverMaxNumber					  De_Erro_Mileage_NoInit+1
	#define De_Erro_Mileage_NoWorkPar						  De_Erro_Mileage_OverMaxNumber+1
	#define De_Erro_Mileage_NoRead 							  De_Erro_Mileage_NoWorkPar+1
	#define De_Erro_Mileage_Fun_NoOpen						  De_Erro_Mileage_NoRead+1

	#ifdef De_Mileage_Compiler

		#define PI         			3.1415926
		#define EARTH_RADIUS  		6378137      //地球半径 

		typedef struct
		{	st_Sensor_DataPar	CN_st_Mileage_DataPar;
			uint8 Type;
			uint8 State;
		}st_Mileage_Par_Oper;

		typedef struct
		{	 
		    uint32 Latitude;						//纬度			定点4位小数   
			uint32 Longitude;   			 		//经度			定点4位小数
			uint32 Speed;							//速度 			单位海里，定点一位小数
			uint32 Angle;							//方向角度		度表  定点一位小数   
		}st_LctDat;              

	   typedef struct
	   {
	   		uint32 Latitude;	// 纬度
			uint32 Longitude;   // 经度
			uint32 Mileage;     // 与上一个点的里程差值
	   }st_GpsPonit;

		static OS_EVENT	*MileageSem = NULL;
		static uint8 DateTime[7];
		static st_LctDat CN_LctDat;
		static st_GpsPonit CN_GpsPoint[6];
		static uint8 PointCount = 0;
	   	static uint8 ReadFist = 0;

		static uint16 Init(void);
		static uint16 Open(st_Sensor_DataPar	*ptst_Sensor_DataPar,uint8 *fd);
		static uint16 Close(uint8 fd);
		static uint16 Read(uint8 fd,void *SendBuf,void *AgreeBuf); 		
		static uint32 GetTimeAdd(uint8 *Small,uint8 *Big);
		static float CalcMil(st_LctDat *px,st_LctDat *py);
		

		static const st_Sensor_Par2Type	CN_st_Sensor_Par2Type[]=
		{	
			De_Sensor_WordPar_Mileage, De_Sensor_Par_Milleage		
		};
		static const st_Fun_Sensor2Hard	CN_st_Fun_Sensor2Hard={Init,Open,Close,Read,NULL};
			
		const st_Sensor_ParList		CN_Mileage_st_Sensor_ParList=
		{	&CN_st_Fun_Sensor2Hard,CN_st_Sensor_Par2Type,sizeof(CN_st_Sensor_Par2Type)/sizeof(st_Sensor_Par2Type)
		};	   

		static st_Mileage_Par_Oper	CN_st_Mileage_Par_Oper;
	
	#else

		extern const st_Sensor_ParList	CN_Mileage_st_Sensor_ParList;
	#endif

