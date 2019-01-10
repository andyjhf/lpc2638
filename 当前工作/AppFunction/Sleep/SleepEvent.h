#define SleepEvent_h
#ifdef SleepEvent_h
/*=========================================include File===========================================================*/	
	#include "..\..\APP\config.h"
	#include "stdlib.h"
	#ifdef De_SleepEvent_Compiler
		#include "..\..\Control\Timer\Timer.h"
		#include "..\..\miscellaneous\CodeTrans\AscNumber.h"		//��������ת����Դ
		//#include "..\..\Control\Adc\Adc.h"
		//#include "..\..\Control\Adc\adc.h"
		//#include "..\..\Control\Can\CanTask.h"
		//#include "..\..\Control\Gprs\GPRS.h"
		//#include "..\..\Control\Gps\GpsTask.h"
		#include "..\..\Control\Sleep\Sleep.h"
		#include "..\..\AppFunction\FilleData\FileData.h"
		#include "..\..\AppFunction\DataTrans\DataTrans.h"
		#include "..\..\File\rwFile.h"
		// 
	#endif
/*========================================Define Data=============================================================*/
	/*+++++++++++++++++++++++++++++++++++++�������һ����++++++++++++++++++++++++++++++++++++++++++++++++++*/ 
	

	/*+++++++++++++++++++++++++++++++++++++����״̬��+++++++++++++++++++++++++++++++++++++++++++++++++++++*/
	
/*=========================================Data Define=+==========================================================*/
	/*+++++++++++++++++++++++++++++++++++++++���ݽṹ��+++++++++++++++++++++++++++++++++++++++++++++++++++*/

/*==========================================static Function==================+++================================*/
  	void SleepInit(void);

	#ifdef De_SleepEvent_Compiler
		static void InitTimerWork(uint8 Fd);
		static void InitTimerSleep(uint8 Fd);
	
	#endif
	

#endif	 


