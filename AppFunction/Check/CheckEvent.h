#define CheckEvent_h
#ifdef CheckEvent_h
/*=========================================include File===========================================================*/	
	#include "..\..\APP\config.h"
	#include "stdlib.h"
	#ifdef De_CheckEvent_Compiler
		#include "..\..\Control\Timer\Timer.h"
		#include "..\..\miscellaneous\CodeTrans\AscNumber.h"		//引用码制转换资源
		#include "..\..\miscellaneous\Date\Date.h"
		//#include "..\..\Control\Adc\Adc.h"
		//#include "..\..\Control\Adc\adc.h"
		//#include "..\..\Control\Can\CanTask.h"
		//#include "..\..\Control\Gprs\GPRS.h"
		#include "..\..\Control\Gps\GpsTask.h"
		#include "..\..\Control\Acc\Acc.h"
		#include "..\..\Control\Sleep\Sleep.h"
		#include "..\..\AppFunction\FilleData\FileData.h"
		#include "..\..\AppFunction\DataTrans\DataTrans.h"
		#include "..\..\File\rwFile.h"
		// 
	#endif
/*========================================Define Data=============================================================*/
	/*+++++++++++++++++++++++++++++++++++++错误代码一览表++++++++++++++++++++++++++++++++++++++++++++++++++*/ 
	

	/*+++++++++++++++++++++++++++++++++++++程序状态字+++++++++++++++++++++++++++++++++++++++++++++++++++++*/
	
/*=========================================Data Define=+==========================================================*/
	/*+++++++++++++++++++++++++++++++++++++++数据结构体+++++++++++++++++++++++++++++++++++++++++++++++++++*/

/*==========================================static Function==================+++================================*/
  	void InitCheck(void);

	#ifdef De_CheckEvent_Compiler
		static void SendData(st_Data_Timer	*ptst_Data_Timer,uint8 fd);
		static void CheckData(st_Data_Timer	*ptst_Data_Timer,uint8 fd);
		static void TraCheckData(void);
		static void SleepCheckData(st_Data_Timer	*ptst_Data_Timer,uint8 fd);
		static void DellGps(st_Data_Timer	*ptst_Data_Timer,uint8 fd);
	#endif
	

#endif	 


