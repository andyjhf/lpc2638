#define CanEvent_H
#ifdef CanEvent_H
/*=========================================include File===========================================================*/	
	#include "..\..\APP\config.h"
	#include "stdlib.h"
	#ifdef De_CanEvent_Compiler
		#include "..\..\Control\Timer\Timer.h"
		#include "..\..\miscellaneous\CodeTrans\AscNumber.h"		//��������ת����Դ
		#include "..\..\Control\Can\CanTask.h"
		#include "..\..\AppFunction\FilleData\FileData.h"
		#include "..\..\AppFunction\DataTrans\DataTrans.h"
		#include "..\..\File\rwFile.h"
		//#include "..\..\HardWare\Can\Can.H"
		// 
	#endif
/*========================================Define Data=============================================================*/
	/*+++++++++++++++++++++++++++++++++++++�������һ����++++++++++++++++++++++++++++++++++++++++++++++++++*/ 
	

	/*+++++++++++++++++++++++++++++++++++++����״̬��+++++++++++++++++++++++++++++++++++++++++++++++++++++*/
	
/*=========================================Data Define=+==========================================================*/
	/*+++++++++++++++++++++++++++++++++++++++���ݽṹ��+++++++++++++++++++++++++++++++++++++++++++++++++++*/

/*==========================================static Function==================+++================================*/
  	

	#ifdef De_CanEvent_Compiler
		void CanInit(void);
		static void Can(st_Da_CanInfor	*ptst_Da_CanInfor);
		static void SenData(st_Data_Timer	*ptst_Data_Timer,uint8 fd);
	  	uint8 Amount;
	#else
		extern uint8 Amount;
		extern void CanInit(void);	
	#endif
	

#endif	 


