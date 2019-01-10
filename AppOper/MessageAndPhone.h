/*=========================================Include File=========================================================*/
	#include "..\APP\config.h"
	#include "stdlib.h"
	#ifdef De_MessageAndPhone_Compiler
		#include "..\File\rwFile.h"
		#include "..\miscellaneous\CodeTrans\AscNumber.h"
		#include "..\FilleData\FileData.h"
		#include "..\FilleData\TakeData.h"
		#include "..\Control\Sensor\SensorContr.h"
		#include "..\Dev\Sensor\Sensor.h"
		#include "..\HardWare\RTC\RTC.h"
		#include "..\miscellaneous\Date\Date.h"
		#include "..\AgreeOn\TzV2.1.h"
		#include "..\AppSendAgreeOn\AppSendAgreeOn.H"
		#include "..\AppOper\AccOper.H"
		#include "..\AppOper\JugeOper.h"
		#include "..\AppTask\OpenClose\OpenAndClose.H"
		#include "..\Control\Timer\Timer.h"
		#include "..\Control\Gprs\Gprs.h"
		#include "..\Dev\Sensor\Display\Display.h"
	#endif
/*========================================Define Data=========================================================*/
	#define De_Suc_MessageAndPhone	0
	#define De_Erro_MessageAndPhone_Nofd		1
	#define De_Erro_MessageAndPhone				De_Erro_MessageAndPhone_Nofd+1


/*========================================Data Define========================================================*/
 	typedef struct
	{	void (*Init)(void);
	}st_Fun_MessageAndPhone;

/*========================================static Function====================================================*/
#ifdef De_MessageAndPhone_Compiler	
	static void Init(void);
	static void ptFunHupWork(uint8 *Phone);
	static void NewMessage(uint8 *Phone,uint8 *Message);
	static void ptFunNewPhone(uint8 *Phone);
	static void ptFunMostPhone(st_Data_Gprs_Call *ptst_Data_Gprs_Call);
	static uint16 BasicPhone(uint8 *Phone);
	static uint16 ConsPhone(uint8 *Phone);
	static uint16 JugePhone(uint8 *Phone);
	static uint16 JugeDriver(uint8 *Phone);
	static uint16 AgreePhone(uint8 *Phone,uint8 State);
	static void CloseCall(st_Data_Timer	*ptst_Data_Timer,uint8 fd);
	static  uint8 ClosePhTimerfd;
	const st_Fun_MessageAndPhone	CN_st_Fun_MessageAndPhone={Init};
#else 
	extern const st_Fun_MessageAndPhone	CN_st_Fun_MessageAndPhone;		
#endif






