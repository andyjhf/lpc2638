/*=======================================include File=========================================================*/
#include "..\..\APP\config.h"											//LPC2368寄存器引用
#include "stdlib.h"
#include "GprsPublicDe.h"
#ifdef De_GprsHard_Compiler
	#include "..\..\HardWare\UART\UART.h" 								//引用串口
	#include "..\..\miscellaneous\CodeTrans\AscNumber.h"				//引用码制转换资源
	#include "..\..\miscellaneous\Date\Date.h"							//引用日期资源
	#include "..\..\miscellaneous\Arithmetic\Arithmetic.h" 				//引入算法
	#include "Huaiwei\_HuaiweiGprs.h"
#endif
/*======================================Define Data==========================================================*/
	/*++++++++++++++++++++++++++++++++++++++硬件GPIO口操作+++++++++++++++++++++++++++++++++++++++*/

	#define De_Fun_GprsHard_ModermPowerUp	IODIR0  |= (1<<7);IODIR0  |= (1<<9);IOSET0 |= (1<<9);IOCLR0 |= (1<<7);MODEM_Dly100ms(20);IOSET0 |= (1<<7);MODEM_Dly100ms(20);IOCLR0 |= (1<<7)
	#define De_Fun_GprsHard_ModermPowerRst	IODIR0  |= (1<<9);IOSET0 |= (1<<9);IOCLR0 |= (1<<9);OSTimeDly(OS_TICKS_PER_SEC*4);IOSET0 |= (1<<9);OSTimeDly(30*OS_TICKS_PER_SEC)
#ifdef De_GprsHard_Compiler
	#define De_GprsHard_Use_Uart										2				//使用串口2
	/*+++++++++++++++++++++++++++++++++++通用命令的最大延时时间+++++++++++++++++++++++++++++++++++*/
	#define De_GprsHard_Com_MaxDelay_AT						300								//测试AT命令
	#define De_GprsHard_Com_MaxDelay_ChipID					200								//获取厂家代码
	#define De_GprsHard_Com_MaxDelay_ATE					300								//关闭回显
	#define De_GprsHard_Com_MaxDelay_BPS					300								//设置波特率 
	/*+++++++++++++++++++++++++++++++++++各个模块使用时的RAM定义++++++++++++++++++++++++++++++++++++++++++*/
	#define De_GprsHard_Use_Ram								De_GprsHard_Ram					//硬件层使用USBRAM
	#define De_GprsHard_Use_Ram_Len							3050							//使用的长度
#endif		
/*=========================================Data Define=======================================================*/	
	typedef struct
	{	uint16 (*Init)(void);				//初始化命令
		uint16 (*Open)(void);			  	//打开
		uint16 (*Close)(void); 			  	//关闭
		uint16 (*Read)(uint16 Command,void *SendBuf,uint16 SizeofSendBuf,void *AgreeBuf,uint16 *SizeofAgreeBuf);
	}st_Fun_GprsHard;						//对外输出列表

/*========================================Function Define=====================================================*/
#ifdef De_GprsHard_Compiler	
	/*-------------------------------------对外输出函数-------------------------------------------------*/
	static uint16 Init(void);				//初始化本页
	static uint16 PowerUp(void);			//模块开机
	static uint16 PowerDown(void);			//模块关机
	static uint16 Read(uint16 Command,void *SendBuf,uint16 SizeofSendBuf,void *AgreeBuf,uint16 *SizeofAgreeBuf);//执行命令	 	
	/*----------------------------------------中间支撑--------------------------------------------------*/
	static uint16 InitModerm(void);			//初始化模块,波特率为115200
	static uint16 LookChipID(st_Fun_GprsHard_Fac	**ptst_Fun_GprsHard_Fac1);					//查找器件地址
	static uint16 GetChipID(uint8 *Buf);	 													//获取厂家代码	
	static uint16 GetBpsAT(void);
	static uint16 CloseShow(void);
	static uint16 SetBps(uint32 Bps);																//发送AT指令,测试波特率命令	
	/*--------------------------------------与Moderm通讯------------------------------------------------*/
	static uint16 ModermCom(uint8 *SendBuf,uint8 *AgreeBuf,uint16 SizeofAgreeBuf,st_GprsHard_Order_Cut	*ptst_GprsHard_Order_Cut);
	static uint16 ModermCom1(uint8 *SendBuf,uint8 *AgreeBuf,uint16 SizeofAgreeBuf,st_GprsHard_Order_Cut	*ptst_GprsHard_Order_Cut);//,uint16 *DataLength1);
	/*----------------------------------------系统函数--------------------------------------------------*/
	static void MODEM_Dly100ms(int num);		 			
	static void ClearNoDisplay(uint8 *Buf);
#endif
/*========================================Public Ram==========================================================*/
	#ifdef De_GprsHard_Compiler
		/*+++++++++++++++++++++++++++++++++++常数定义+++++++++++++++++++++++++++++++++++++++++++++++++++++++*/
		const st_Fun_GprsHard	CN_st_Fun_GprsHard={Init,PowerUp,PowerDown,Read};					//对外输出函数
		/*-----------------------------------各家驱动库---------------------------------------------*/
		const st_Fun_GprsHard_Fac	*ptCN_st_Fun_GprsHard_Fac[]=   							//各个模块硬件接口
		{	&CN_Huawei_st_Fun_GprsHard_Fac						//华为模块
																//西门子
																//明基			
		};
		const st_GprsHard_Order_Cut	CN_st_GprsHard_Order_Cut_AT={De_GprsHard_Com_MaxDelay_AT,"AT","\r\n","","\r\n","OK",""};
		const st_GprsHard_Order_Cut	CN_st_GprsHard_Order_Cut_ATE={De_GprsHard_Com_MaxDelay_ATE,"ATE0","\r\n","","\r\n","OK",""};
		const st_GprsHard_Order_Cut	CN_st_GprsHard_Order_Cut_ChipID={De_GprsHard_Com_MaxDelay_ChipID,"AT+GMI","\r\n","","\r\n","OK",""};
		const st_GprsHard_Order_Cut	CN_st_GprsHard_Order_Cut_BPS={De_GprsHard_Com_MaxDelay_BPS,"AT+IPR=","\r\n","","\r\n","OK","ERROR"};
		const st_Da_Uart	CN_Ba_st_Da_Uart_GprsHard[]= 					//波特率列表
		{	{115200,8,1,0},
			{300,8,1,0},
			{600,8,1,0},
			{1200,8,1,0},
			{4800,8,1,0},
			{9600,8,1,0},
			{14400,8,1,0},
			{19200,8,1,0},
			{38400,8,1,0},
			{57600,8,1,0},
		};
		/*++++++++++++++++++++++++++++++++++++RAM定义++++++++++++++++++++++++++++++++++++++++++++++++++++++*/
		st_Fun_GprsHard_Fac	*ptst_Fun_GprsHard_Fac;
		uint8 *X_RAM=(uint8 *)De_GprsHard_Use_Ram;
	#else
		extern const st_Fun_GprsHard CN_st_Fun_GprsHard;	
	#endif	

