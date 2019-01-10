#define AdcEvent_h
#ifdef AdcEvent_h
/*=========================================include File===========================================================*/	
	#include "..\..\APP\config.h"
	#include "stdlib.h"
	#ifdef De_AdcEvent_Compiler
		#include "..\..\Control\Timer\Timer.h"
		#include "..\..\miscellaneous\CodeTrans\AscNumber.h"		//引用码制转换资源
		#include "..\..\Control\Adc\Adc.h"
		//#include "..\..\Control\Adc\adc.h"
		//#include "..\..\Control\Can\CanTask.h"
		//#include "..\..\Control\Gprs\GPRS.h"
		//#include "..\..\Control\Gps\GpsTask.h"
		//#include "..\..\Control\Sleep\Sleep.h"
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
  	void AdcInit(void);

	#ifdef De_AdcEvent_Compiler
		static void HighAdc(st_Data_CheckVoltage	*ptst_Data_CheckVoltage,uint8 fd);
		static void LowAdc(st_Data_CheckVoltage	*ptst_Data_CheckVoltage,uint8 fd);
		static void LowVolWaring(void);
		static void HighVolBack(void);
	
	#endif
	

#endif	 


