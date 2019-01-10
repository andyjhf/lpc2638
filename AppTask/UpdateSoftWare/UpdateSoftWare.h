/*=====================================Include File=========================================================*/
#include "..\..\APP\config.h"
#include "stdlib.h"

	#ifdef De_UpDateSoftWare_Compiler
		#include "..\..\miscellaneous\CodeTrans\AscNumber.h"				// 引用码制转换资源
//		#include "..\..\AgreeOn\AgreementCom.h"
		#include "..\..\Control\FTP\ftp.h"
	#endif
/*=======================================Define Data============================================================*/
	#define De_Suc_UpDateSoftWare							0
	
	/*+++++++++++++++++++++++++++++++++++错误代码一览表+++++++++++++++++++++++++++++++++++++*/
	#define De_Erro_UpDateSoftWare							1
	#define De_Erro_UpDateSoftWare_Init						De_Erro_UpDateSoftWare+1
	#define De_Erro_UpDateSoftWare_ReDown					De_Erro_UpDateSoftWare_Init+1	//终止当前下载，重新开始新的下载
	/*+++++++++++++++++++++++++++++++++++任务有关参数+++++++++++++++++++++++++++++++++*/
	#ifdef De_UpDateSoftWare_Compiler
		#define De_UpDateSoftWare_Stk										256							//堆大小
		#define De_UpDateSoftWare_TaskDly									30							//延时调度时间
//		#define De_Affair_GpsAndMileage_MaxNumber							5 							//最大20个事件
		#define De_Task_Number												11
		#define MAX_MESSAGES												4
	#endif
/*========================================Data Define===========================================================*/
   typedef struct
	{	uint8 Device;			//所升级的设备见<De_Agree_AgreeOn_UpdateSoftWare_Host>与<De_Agree_AgreeOn_UpdateSoftWare_Display>
		uint32 IP;			   	//TFTP下载服务器的IP地址
		uint16 Port;			//端口号
		uint8 Use[40];			//用户名
		uint8 Pass[40];			//密码
		uint8 FileName[200];	//文件路径
		uint8 SaveFileName[32];	//保存文件名
		void (*DownLoaderOver)(void);				//下载结束后的命令应答
		void (*DownLoaderState)(st_FTP_WorkState	*ptst_FTP_WorkState);
	}st_Order_UpdateSoftWare;
   typedef struct
	{	st_Order_UpdateSoftWare	CN_st_Order_UpdateSoftWare;												//1: 160X128象素 2: 320X240象素 3: 640X480象素
		uint16 Result;          										//本次执行返回结果
		OS_EVENT	*ReBox;    											//通过此邮箱返回
	}st_BoxData_UpData;
   typedef struct
   { uint16 (*Init)(void);
   }st_Fun_UpdateSoftWare;
/*============================================Static Function================================================*/
   #ifdef De_UpDateSoftWare_Compiler
   		static uint16 Init(void);
		static void Task(void *pdata);
/*=============================================Public Ram=====================================================*/
		void *UpDataBox[MAX_MESSAGES];  	        					//本控件消息队列
		st_BoxData_UpData	*ptst_BoxData_UpData;
		st_BoxData_UpData	*ptst_BoxData_UpData_Temp;
		st_FTP_WorkState CN_st_FTP_WorkState_Now;
		uint16 UpDataWaitTime;
//		st_AgreeOn_UpdateSoftWare	CN_st_AgreeOn_UpdateSoftWare;
		st_FTP_Data CN_st_FTP_Data;
		OS_STK UpDateSoftWare_Stk[De_UpDateSoftWare_Stk];
		st_Fun_UpdateSoftWare CN_st_Fun_UpdateSoftWare={Init};
		OS_EVENT	*UpDateSoftWare_Q;
		void (*DownLoaderOver)(void);				//下载结束后的命令应答
		void (*DownLoaderState)(st_FTP_WorkState	*ptst_FTP_WorkState);
	#else
		extern OS_EVENT	*UpDateSoftWare_Q;
		extern st_Fun_UpdateSoftWare CN_st_Fun_UpdateSoftWare;
	#endif









