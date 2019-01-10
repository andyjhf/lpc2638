/*=======================================Include File==========================================================*/
	#include "..\APP\config.h"
	#include "stdlib.h"
	#ifdef De_AccOper_Compiler
		#include "..\File\rwFile.h"
		#include "..\miscellaneous\CodeTrans\AscNumber.h"
		#include "..\FilleData\FileData.h"
		#include "..\FilleData\TakeData.h"
		#include "..\Dev\Sensor\Sensor.h"
		#include "..\AgreeOn\TzV2.1.h"
		#include "..\AppSendAgreeOn\AppSendAgreeOn.H"
		#include "..\AppTask\OpenClose\OpenAndClose.H"
		#include "..\miscellaneous\Date\Date.h"
		#include "..\HardWare\RTC\RTC.h"
	#endif
/*=========================================Define Data=========================================================*/
	#ifdef De_AccOper_Compiler
		#define De_Gps_Open_Timer															300	 		//GPS启动时间
		#define De_Gprs_Open_Timer															120
		#define De_No_Data_Send													0xffffffff
	#endif				//Gprs打开时间
/*=========================================Data Define=========================================================*/ 
 	typedef struct
	{	void (*Write)(void *Data);
	}st_Fun_AccOper;	
	#ifdef De_AccOper_Compiler
	typedef struct
	{	uint32 *Val1;
		uint32 *Val2;
		uint32 Val;
		void (*ptFun)(void);
	}st_GpsJuge_Term;
	typedef struct
	{	uint32 *Val1;
		uint32 *Val2;
		uint8 Par;
	}st_Affair_Term;
	typedef struct
	{	uint32 *Val1;
		uint32 *Val2;	
		void (*	ptFun)(void);
	}st_Affair_TermClose;


	#endif			 
	
/*==========================================static Function====================================================*/	
#ifdef De_AccOper_Compiler	
	static void AccOper(void *Data);
	static void AccStateChange(uint8 State);
	static void AccOpen(st_Sensor_Data_Acc	*ptst_Sensor_Data_Acc);
	static void AccClose(st_Sensor_Data_Acc	*ptst_Sensor_Data_Acc);
	static void JugeTimerPar(st_Sensor_Data_Acc	*ptst_Sensor_Data_Acc);
	static uint32 GetTimeAdd(uint8 *Small,uint8 *Big);
	static void GetData(void);
	static void AccTimer(st_Sensor_Data_Acc	*ptst_Sensor_Data_Acc);
	static void OpenGps(void);
	static void OpenGprs(void);
	static void CloseGps(void);
	static void CloseGprs(void);

#endif
/*==========================================Public Ram=========================================================*/	
#ifdef De_AccOper_Compiler	
	static uint8 AccUse=NULL;
	static uint8 AccState;
	static uint32 AddTimerNumber[18]; 										//判断是否关机等
	static uint32 EndTimerNumber[18];										//判断是否关机等
	const st_Fun_AccOper	CN_st_Fun_AccOper={AccOper};
	const st_GpsJuge_Term		CN_Ba_OpenMachi_Term[]=
	{	{	&EndTimerNumber[3],&AddTimerNumber[3],De_Gps_Open_Timer,OpenGps},
		{	&EndTimerNumber[4],&AddTimerNumber[4],De_Gps_Open_Timer,OpenGps},
		{	&EndTimerNumber[5],&AddTimerNumber[5],De_Gps_Open_Timer,OpenGps},
		{	&EndTimerNumber[8],&AddTimerNumber[8],De_Gps_Open_Timer,OpenGps},
		{	&EndTimerNumber[9],&AddTimerNumber[9],De_Gps_Open_Timer,OpenGps},
		{	&EndTimerNumber[10],&AddTimerNumber[10],De_Gps_Open_Timer,OpenGps},
		{	&EndTimerNumber[11],&AddTimerNumber[11],De_Gps_Open_Timer,OpenGps},
		{	&EndTimerNumber[12],&AddTimerNumber[12],De_Gps_Open_Timer,OpenGps},
		{	&EndTimerNumber[13],&AddTimerNumber[13],De_Gps_Open_Timer,OpenGps},
		{	&EndTimerNumber[14],&AddTimerNumber[14],De_Gps_Open_Timer,OpenGps},
		{	&EndTimerNumber[15],&AddTimerNumber[15],De_Gps_Open_Timer,OpenGps},
		{	&EndTimerNumber[16],&AddTimerNumber[16],De_Gps_Open_Timer,OpenGps},
		{	&EndTimerNumber[17],&AddTimerNumber[17],De_Gps_Open_Timer,OpenGps},
		{	&EndTimerNumber[3],&AddTimerNumber[3],De_Gprs_Open_Timer,OpenGprs},
		{	&EndTimerNumber[4],&AddTimerNumber[4],De_Gprs_Open_Timer,OpenGprs},
		{	&EndTimerNumber[5],&AddTimerNumber[5],De_Gprs_Open_Timer,OpenGprs},
		{	&EndTimerNumber[8],&AddTimerNumber[8],De_Gprs_Open_Timer,OpenGprs},
		{	&EndTimerNumber[9],&AddTimerNumber[9],De_Gprs_Open_Timer,OpenGprs},
		{	&EndTimerNumber[10],&AddTimerNumber[10],De_Gprs_Open_Timer,OpenGprs},
		{	&EndTimerNumber[11],&AddTimerNumber[11],De_Gprs_Open_Timer,OpenGprs},
		{	&EndTimerNumber[12],&AddTimerNumber[12],De_Gprs_Open_Timer,OpenGprs},
		{	&EndTimerNumber[13],&AddTimerNumber[13],De_Gprs_Open_Timer,OpenGprs},
		{	&EndTimerNumber[14],&AddTimerNumber[14],De_Gprs_Open_Timer,OpenGprs},
		{	&EndTimerNumber[15],&AddTimerNumber[15],De_Gprs_Open_Timer,OpenGprs},
		{	&EndTimerNumber[16],&AddTimerNumber[16],De_Gprs_Open_Timer,OpenGprs},
		{	&EndTimerNumber[17],&AddTimerNumber[17],De_Gprs_Open_Timer,OpenGprs}
	};
	

	static const st_GpsJuge_Term		CN_Ba_TimerPar_Term[]=
	{	{	&EndTimerNumber[8],&AddTimerNumber[8]	},
		{	&EndTimerNumber[9],&AddTimerNumber[9]	},
		{	&EndTimerNumber[10],&AddTimerNumber[10]	},
		{	&EndTimerNumber[11],&AddTimerNumber[11]	},
		{	&EndTimerNumber[12],&AddTimerNumber[12]	},
		{	&EndTimerNumber[13],&AddTimerNumber[13]	},
		{	&EndTimerNumber[14],&AddTimerNumber[14]	},
		{	&EndTimerNumber[15],&AddTimerNumber[15]	},
		{	&EndTimerNumber[16],&AddTimerNumber[16]	},
		{	&EndTimerNumber[17],&AddTimerNumber[17]	}
	};
	static const st_Affair_Term			CN_Ba_AccOpen_st_Affair_Term[]=
	{	{	&EndTimerNumber[0],&AddTimerNumber[0],De_Access_Type_Track	},
		{	&EndTimerNumber[1],&AddTimerNumber[1],De_Access_Type_WorkPar	},
		{	&EndTimerNumber[2],&AddTimerNumber[2],De_Access_Type_ReduceWork	}
	};
	static const st_Affair_Term			CN_Ba_AccClose_st_Affair_Term[]=
	{	{	&EndTimerNumber[3],&AddTimerNumber[3],De_Access_Type_Track	},
		{	&EndTimerNumber[4],&AddTimerNumber[4],De_Access_Type_WorkPar	},
		{	&EndTimerNumber[5],&AddTimerNumber[5],De_Access_Type_ReduceWork	}
	};
	static const st_Affair_TermClose	CN_Ba_st_Affair_TermClose[]=
	{	{	&EndTimerNumber[6],&AddTimerNumber[6],CloseGps	},
		{	&EndTimerNumber[7],&AddTimerNumber[7],CloseGprs	},
	};
		
#else
	extern const st_Fun_AccOper	CN_st_Fun_AccOper;
#endif

