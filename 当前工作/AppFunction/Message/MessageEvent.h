#define MessageEvent_h
#ifdef MessageEvent_h
/*=========================================include File===========================================================*/	
	#include "..\..\APP\config.h"
	#include "stdlib.h"
	#ifdef De_MessageEvent_Compiler
		#include "..\..\Control\Gprs\GPRS.h"
		#include "..\..\miscellaneous\CodeTrans\AscNumber.h"
		#include "..\..\Control\Gps\GpsTask.h"
		#include "..\..\Control\Sleep\Sleep.h"
		#include "..\..\Control\Timer\Timer.h"
		#include "..\..\miscellaneous\Date\Date.h"
		#include "..\..\AppFunction\FilleData\FileData.h"
		#include "..\..\AppFunction\DataTrans\DataTrans.h"
		#include "..\..\Control\Hand\Hand.h"
		#include "..\..\File\rwFile.h"
		// 
	#endif
/*========================================Define Data=============================================================*/
	/*+++++++++++++++++++++++++++++++++++++错误代码一览表++++++++++++++++++++++++++++++++++++++++++++++++++*/ 
	#define De_Erro_App												0

	#define De_Erro_App_MessOrderiLegal								De_Erro_App	

	/*+++++++++++++++++++++++++++++++++++++程序状态字+++++++++++++++++++++++++++++++++++++++++++++++++++++*/
	#define De_App_MessOrder_No										0					//没有此命令

	#define De_App_MessOrder_vWaring								1					//
	#define De_App_MessOrder_SeeParameter							2
	#define De_App_MessOrder_AccInit								3
	#define De_App_MessOrder_Lock									4
	#define De_App_MessOrder_unLock									5
	#define De_App_MessOrder_TimerSend								6
	#define De_App_MessOrder_EditParameter							7
	#define De_App_MessOrder_ComeInit								8 
	#define De_App_MessOrderNumber									De_App_MessOrder_ComeInit 	//命令数量

	
	#define De_App_MessOrder_BagHead								'*'
	#define De_App_MessOrder_BagEnd									'#'	

/*=========================================Data Define=+==========================================================*/
	/*+++++++++++++++++++++++++++++++++++++++数据结构体+++++++++++++++++++++++++++++++++++++++++++++++++++*/
	typedef struct
	{	uint8 *Gut;
		uint16 App_MessOrder;
	}st_App_MessOrder;

/*==========================================static Function==================+++================================*/
	#ifdef De_MessageEvent_Compiler
		static void MessageNoWork(st_Data_Gprs   *ptst_Data_Gprs);
		static void MessageNoSem(st_Data_Gprs   *ptst_Data_Gprs);
		static void MessageSem(st_Data_Gprs   *ptst_Data_Gprs);
		static void AgreenMessage(st_Data_Gprs   *ptst_Data_Gprs);
		static void NewPhone(st_Data_Gprs   *ptst_Data_Gprs);
		
		static void Edit_CV(st_Data_Gprs	*ptst_Data_Gprs);
		static void SeeAbout_Machi(st_Data_Gprs	*ptst_Data_Gprs);
		static void Edit_Ce(st_Data_Gprs	*ptst_Data_Gprs);
		static void Lock(st_Data_Gprs	*ptst_Data_Gprs);
		static void unLock(st_Data_Gprs	*ptst_Data_Gprs);
		static void ComeInit(st_Data_Gprs	*ptst_Data_Gprs);
		static void TimerSend(st_Data_Gprs	*ptst_Data_Gprs);
		static void Edit_Parameter(st_Data_Gprs	*ptst_Data_Gprs);
		static void Edit_C1(st_Data_Gprs	*ptst_Data_Gprs);
		static void Edit_C2(st_Data_Gprs	*ptst_Data_Gprs);
		static void Edit_Cc(st_Data_Gprs	*ptst_Data_Gprs);
		static void Edit_Cm(st_Data_Gprs	*ptst_Data_Gprs);
		static void Edit_CE(st_Data_Gprs	*ptst_Data_Gprs);
		static void Edit_CS(st_Data_Gprs	*ptst_Data_Gprs);
		static void Edit_Ct(st_Data_Gprs	*ptst_Data_Gprs);
		static void Edit_Cp(st_Data_Gprs	*ptst_Data_Gprs);
		static uint16 JugeOrder(uint8 *Message);
		static uint16 JugeLegal(uint8 *Message);
		static uint16 JugePhone(uint8 *Phone,uint8 *CenterNum);
//		static void NewTCPIPData(uint8 *Data,uint8 *fd,uint16 DataLength);

		static void CheckData(void);			//巡检
		
		uint8 UDPFD;
		uint8 TCPFD;
		uint8 SendNumber = 0;
		const	st_App_MessOrder	Cn_st_App_MessOrder[De_App_MessOrderNumber]=
		{	{	"*CV",De_App_MessOrder_vWaring},						//设置报警数值
			{	"*kq",De_App_MessOrder_SeeParameter},					//查询车机参数
			{	"*Ce",De_App_MessOrder_AccInit},						//ACC时间
			{	"*L",De_App_MessOrder_Lock},  							//远程控制
			{	"*J",De_App_MessOrder_unLock},							//解除锁车	
			{	"*D",De_App_MessOrder_TimerSend},						//定时回传
			{	"*C",De_App_MessOrder_EditParameter},					//按指令更改
			{	"*U",De_App_MessOrder_ComeInit}							//恢复出厂值
		};
	#endif
	

#endif	 


