#define GpsEvent_h
#ifdef GpsEvent_h
/*=========================================include File===========================================================*/	
	#include "..\..\APP\config.h"
	#include "stdlib.h"
	#ifdef De_GpsEvent_Compiler
		//#include "..\..\Control\Timer\Timer.h"
		//#include "..\..\miscellaneous\CodeTrans\AscNumber.h"		//��������ת����Դ
		//#include "..\..\Control\Adc\Adc.h"
		//#include "..\..\Control\Adc\adc.h"
		//#include "..\..\Control\Can\CanTask.h"
		//#include "..\..\Control\Gprs\GPRS.h"
		#include "..\..\Control\Gps\GpsTask.h"
		//#include "..\..\Control\Sleep\Sleep.h"
		#include "..\..\AppFunction\FilleData\FileData.h"
		#include "..\..\AppFunction\DataTrans\DataTrans.h"
		#include "..\..\File\rwFile.h"
		#include "..\..\HardWare\RTC\RTC.h"
		// 
	#endif
/*========================================Define Data=============================================================*/
	/*+++++++++++++++++++++++++++++++++++++�������һ����++++++++++++++++++++++++++++++++++++++++++++++++++*/ 
	

	/*+++++++++++++++++++++++++++++++++++++����״̬��+++++++++++++++++++++++++++++++++++++++++++++++++++++*/
	
/*=========================================Data Define=+==========================================================*/
	/*+++++++++++++++++++++++++++++++++++++++���ݽṹ��+++++++++++++++++++++++++++++++++++++++++++++++++++*/

/*==========================================static Function==================+++================================*/
  	void GpsInit(void);

	#ifdef De_GpsEvent_Compiler
		static void GpsSem(st_Data_Gps  *ptst_Data_Gps,uint8 fd);
		static void GpsNoSem(st_Data_Gps  *ptst_Data_Gps,uint8 fd);
		static void GpsErro(st_Data_Gps  *ptst_Data_Gps,uint8 fd);
	
	#endif
	

#endif	 


