/*=========================================Include File=========================================================*/
	#include "..\APP\config.h"
	#include "stdlib.h"
	#ifdef De_Space_Compiler
		#include "..\File\rwFile.h"
		#include "..\miscellaneous\CodeTrans\AscNumber.h"
		#include "..\FilleData\FileData.h"
		#include "..\Control\GpsAndMileage\GpsAndMileage.h"
		#include "..\FilleData\TakeData.h"
		#include "..\miscellaneous\Date\Date.h"
		#include "..\AgreeOn\TzV2.1.h"
		#include "..\AppSendAgreeOn\AppSendAgreeOn.H"
		#include "..\AppOper\JugeOper.h"
		#include "..\HardWare\RTC\RTC.h"
		#include "..\AppTask\OpenClose\OpenAndClose.H"
	#endif
/*=========================================Define Data=========================================================*/
	#define De_Affairfd_Nofd														0xff
	#define De_State_Gps															0
	#define De_Speed_No																0xffffffff	
/*=========================================Data Define=========================================================*/		
	typedef struct
	{	void (*Init)(void);
	}st_Fun_Space;
	#ifdef De_Space_Compiler
		typedef struct
		{	uint8 GetGpsfd;
			uint8 GetTrackfd;
			uint8 WorkParSpacefd;
		}st_RunLen_Affair_fd;
	#endif
/*=========================================static Function=====================================================*/
#ifdef De_Space_Compiler	
	static void InitSpace(void);
	static void GetGps(st_File_Gps	*ptst_File_Gps,uint8 fd);
	static void Space_Track(st_File_Gps	*ptst_File_Gps,uint8 fd);
	static void Space_WorkParSpace(st_File_Gps	*ptst_File_Gps,uint8 fd);
	static void JugeSpeed(uint32 AddTim,uint8 Speed);
	static uint32 GetTimeAdd(uint8 *Small,uint8 *Big);
#endif
/*===========================================Public Ram========================================================*/
#ifdef De_Space_Compiler	
	st_RunLen_Affair_fd	CN_st_RunLen_Affair_fd={De_Affairfd_Nofd,De_Affairfd_Nofd,De_Affairfd_Nofd};
	const st_Fun_Space	CN_Ba_st_Fun_Space={InitSpace};	
	static uint8 BackDate[7];
	static uint32 AddTimeHigh=0,AddTimeLow=0;
#else
	extern const st_Fun_Space	CN_Ba_st_Fun_Space;
#endif
