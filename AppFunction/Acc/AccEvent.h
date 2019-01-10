#define AccEvent_H
#ifdef AccEvent_H
/*=========================================include File===========================================================*/	
	#include "..\..\APP\config.h"
	#include "stdlib.h"
	#ifdef De_AccEvent_Compiler
		#include "..\..\Control\Timer\Timer.h"
		#include "..\..\miscellaneous\CodeTrans\AscNumber.h"		//��������ת����Դ
		#include "..\..\Control\Acc\Acc.h"
		//#include "..\..\Control\Adc\adc.h"
		//#include "..\..\Control\Can\CanTask.h"
		//#include "..\..\Control\Gprs\GPRS.h"
		//#include "..\..\Control\Gps\GpsTask.h"
		#include "..\..\Control\Sleep\Sleep.h"
		#include "..\..\AppFunction\FilleData\FileData.h"
		#include "..\..\AppFunction\DataTrans\DataTrans.h"
		#include "..\..\File\rwFile.h"
		#include "..\..\HardWare\UART\UART.h"
		// 
	#endif
/*========================================Define Data=============================================================*/
	/*+++++++++++++++++++++++++++++++++++++�������һ����++++++++++++++++++++++++++++++++++++++++++++++++++*/ 
	

	/*+++++++++++++++++++++++++++++++++++++����״̬��+++++++++++++++++++++++++++++++++++++++++++++++++++++*/
	
/*=========================================Data Define=+==========================================================*/
	/*+++++++++++++++++++++++++++++++++++++++���ݽṹ��+++++++++++++++++++++++++++++++++++++++++++++++++++*/

/*==========================================static Function==================+++================================*/
  	void AccInit(void);

	#ifdef De_AccEvent_Compiler
		static void AccHigh(st_Data_Acc   *ptst_Data_Acc,uint8 fd);
		static void AccLow(st_Data_Acc   *ptst_Data_Acc,uint8 fd);
		static void Sleep(st_Data_Timer	*ptst_Data_Timer,uint8 fd);
	
	#endif
	

#endif	 


