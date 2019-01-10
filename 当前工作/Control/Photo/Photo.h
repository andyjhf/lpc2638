#define Photo_H
#ifdef	Photo_H
/*=============================include File==================================================*/
	#include "..\..\APP\config.h"
	#include "stdlib.h"
	#ifdef De_Photo_Compiler
		#include "..\..\File\rwFile.h"
		#include "..\..\HardWare\UART\UART.h"
		#include "..\..\miscellaneous\CodeTrans\AscNumber.h"		//引用码制转换资源
		#include "..\..\miscellaneous\Date\Date.h"					//引用日期资源
		#include "..\..\miscellaneous\Arithmetic\Arithmetic.h" 		//引入算法
	#endif
/*==============================Define Data==================================================*/	
	/*+++++++++++++++++++++++++++++++错误代码一栏表+++++++++++++++++++++++++++++++++++++++++*/
	#define	De_Suc_Photo									0
	#define De_Erro_Photo									1
	#define De_Erro_Photo_CreateQ							De_Erro_Photo+1			//创建消息队列失败
	#define	De_Erro_Photo_Common							De_Erro_Photo_CreateQ+1	//拍照失败
	#define De_Erro_Photo_Data								De_Erro_Photo_Common+1	//获取照片数据失败
	/*+++++++++++++++++++++++++++++++程序状态字+++++++++++++++++++++++++++++++++++++++++++*/			
	#define De_Photo_Use_Uart								3			//摄像头使用串口
	#define MAX_MESSAGES  									10			//同时最多可以接收的拍照命令
	#define De_BoxData_Vid_Command_Operation				1			//拍照命令
	#define De_BoxData_Vid_Command_State					2			//查询摄像头状态命令
	#define De_Max_Bag_Length								508			//每包数据的最大尺寸
	#define De_Max_Ram										De_Max_Bag_Length+20 //最大申请RAM资源
	#define De_PhotoType_160x128							'1'			//所拍相片的像素160x128
	#define De_PhotoType_320x240							'2'			//所拍相片的像素320x240
	#define De_PhotoType_640x480							'3'			//所拍相片的像素640x480
	/*++++++++++++++++++++++++++++++++操作系统有关++++++++++++++++++++++++++++++++++++++++*/
	#ifdef De_Photo_Compiler
		#define De_Photo_Task								12
		#define De_Photo_Stk								256
		#define De_Photo_TaskDly							200								//延时调度时间
	#endif
/*=======================================Data Define==========================================*/
	/*++++++++++++++++++++++++++++++++数据结构定义+++++++++++++++++++++++++++++++++++++++++++*/
	typedef struct
	{	uint8 Command;        											//邮箱命令
		//uint8 *Buf;             										//传递内容
		uint16 TailFd;													//位置表
		uint16 DataFd;													//内容表
		uint8 PhotoType;												//1: 160X128象素 2: 320X240象素 3: 640X480象素
		uint16 Result;          										//本次执行返回结果
		OS_EVENT	*ReBox;    											//通过此邮箱返回
	}st_BoxData_Vid;	        										//本控件邮箱结构体
	
	typedef struct
	{	uint16 PhotoSize;												//相片的总大小
		uint16 BagNum;													//分包数量
		uint16 PerBagLength;											//每包大小
	}st_Photo_Property;													//所拍相片的属性
	typedef struct
	{	uint16 (*Init)(void);
		uint16 (*Open)(void);
		uint16 (*Close)(void);
	}st_Fun_Photo;
	typedef struct
	{	uint16 FrontTail; 												//前一条文件尾指针
		uint16 CurrentTail;												//当前文件尾指针
	}st_File_Photo_Tail;
	typedef struct
	{	uint16 BagNumber;
		uint16 DataLength;
		uint8  Data[De_Max_Bag_Length];
	}st_File_Photo_Data;

/*============================================Static Function================================================*/
	#ifdef De_Photo_Compiler
		static uint16 Init(void);
		static uint16 Open(void);
		static uint16 Close(void);
		static void Task(void *pdata);
		static uint16 PhotoCommon(uint8 PhotoSize,st_Photo_Property *ptst_Photo_Property);
		static uint16 ReadPhoto(uint16 Num,uint8 *AgreeBuf,uint16 SizeofAgreeBuf,uint16 *DataLength);	
		static uint16 CheckSum(uint8 *s,uint16 len);
		static uint16 Photo(st_BoxData_Vid *ptst_BoxData_Vid,st_Photo_Property *ptst_Photo_Property,uint8 *AgreeBuf,uint16 SizeofAgreeBuf);
/*=============================================Public Ram=====================================================*/
		void *VidBox[MAX_MESSAGES];  	        					//本控件消息队列
		OS_STK	PhotoTaskStk [De_Photo_Stk];						//本控件堆栈
		OS_EVENT *Photo_Q;											//消息事件
		st_BoxData_Vid *ptst_BoxData_Vid;							//拍照命令指针
		st_Photo_Property CN_st_Photo_Property;						//照片属性
		uint8 PhotoBuf[De_Max_Ram];									//空间使用缓存
		const st_Fun_Photo	CN_st_Fun_Photo={Init,Open,Close};
	#else
		extern const st_Fun_Photo	CN_st_Fun_Photo;
		extern OS_EVENT *Photo_Q;
	#endif
#endif

