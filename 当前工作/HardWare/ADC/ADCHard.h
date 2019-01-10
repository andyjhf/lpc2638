/*==========================================包含文件========================================================*/	
	#include "..\..\APP\config.h"
	#include "stdlib.h"
	#ifdef De_ADCHard_Compiler
		#include "..\..\miscellaneous\CodeTrans\AscNumber.h"
	#endif
/*==========================================Define Data=======================================================*/
	#define De_Suc_Adc													0			//成功
	/*++++++++++++++++++++++++++++++++++++错误代码一览表++++++++++++++++++++++++++++++++++++++++++++++++*/
	#define De_Erro_Adc_Init  											1			//初始化错误
	#define De_Erro_Adc_NoPort											2			//无此端口
	/*++++++++++++++++++++++++++++++++++++++对外参数输出++++++++++++++++++++++++++++++++++++++++++++++++*/
		/*------------------------------------端口定义--------------------------------------*/
	#define De_Adc_Port_0												0						//ADC0~ADC7
	#define De_Adc_Port_1												1					  	
	#define De_Adc_Port_2												2
	#define De_Adc_Port_3												3
	#define De_Adc_Port_4												4
	#define De_Adc_Port_5												5
	#define De_Adc_Port_6												6
	#define De_Adc_Port_7												7
	  	/*------------------------------------精度定义---------------------------------------*/
	#define De_Adc_Trans_Precision0										0x00			//11时钟/10位
	#define De_Adc_Trans_Precision1										0x01			//10时钟/9位
	#define De_Adc_Trans_Precision2										0x02			//9时钟/8位
	#define De_Adc_Trans_Precision3										0x03			//8时钟/7位
	#define De_Adc_Trans_Precision4										0x04			//7时钟/6位
	#define De_Adc_Trans_Precision5										0x05			//6时钟/5位
	#define De_Adc_Trans_Precision6										0x06			//5时钟/4位
	#define De_Adc_Trans_Precision7										0x07			//4时钟/3位
		/*-----------------------------------其他参数定义----------------------------------------*/
	#define De_Adc_Max_Clk												4500000			//最大的频率
	#define De_Adc_Fun_Open												0				//此功能打开
	#define De_Adc_Fun_Close											1				//此功能关闭
	/*++++++++++++++++++++++++++++++++++++++私有参数定义+++++++++++++++++++++++++++++++++++++++++++++++*/
#ifdef De_ADCHard_Compiler
  		/*------------------------------通道在寄存器中所在位置---------------------------------------*/
	#define De_Adc_Port_Space_0											0
	#define De_Adc_Port_Space_1											1
	#define De_Adc_Port_Space_2											2
	#define De_Adc_Port_Space_3											3
	#define De_Adc_Port_Space_4											4
	#define De_Adc_Port_Space_5											5
	#define De_Adc_Port_Space_6											6
	#define De_Adc_Port_Space_7											7
		/*--------------------------------硬件端口定义--------------------------------------------*/
	#define De_HardWare_FunOpen_ADC0							{	PINSEL1|=(0x00000001<<14);PINSEL1&=(~(0x00000001<<15));}
	#define De_HardWare_FunOpen_ADC1							{	PINSEL1|=(0x00000001<<16);PINSEL1&=(~(0x00000001<<17));}
	#define De_HardWare_FunOpen_ADC2							{	PINSEL1|=(0x00000001<<18);PINSEL1&=(~(0x00000001<<19));}
	#define De_HardWare_FunOpen_ADC3							{	PINSEL1|=(0x00000001<<20);PINSEL1&=(~(0x00000001<<21));}
	#define De_HardWare_FunOpen_ADC4							{	PINSEL3|=(0x00000001<<28);PINSEL3|=((0x00000001<<29));}
	#define De_HardWare_FunOpen_ADC5							{	PINSEL3|=0x40000000;PINSEL3|=0x80000000;}
	#define De_HardWare_FunOpen_ADC6							{	PINSEL0|=(0x00000001<<24);PINSEL0|=((0x00000001<<25));}
	#define De_HardWare_FunOpen_ADC7							{	PINSEL0|=(0x00000001<<26);PINSEL0|=((0x00000001<<27));}
	#define De_HardWare_Open_Power								PCONP|= (1 << 12)
#endif
/*===============================================Data Define====================================================*/
	/*++++++++++++++++++++++++++++++++++++对外数据结构体++++++++++++++++++++++++++++++++++++++++++++++*/	
	typedef struct
	{	uint32 CLK;		 				//A/D转换所采用的时钟,最大不得高于De_Adc_Max_Clk
		uint8 Precision;				//转换的精度，见<De_Adc_Trans_PrecisionX>定义
		uint32 Modulus;	   				//参考电压以及转化参数
	}st_Data_Adc;
	/*++++++++++++++++++++++++++++++++++++++对外输出函数结构体+++++++++++++++++++++++++++++++++++++++++*/
	typedef struct
	{	uint16 (*Init)(void);
		uint16 (*Open)(uint8 Port,st_Data_Adc	*ptst_Data_Adc);
		uint16 (*Read)(uint8 Port,uint32 *Vol);
		uint16 (*Close)(uint8 Port);
	}st_Fun_Adc;
	/*++++++++++++++++++++++++++++++++++++++私有结构体++++++++++++++++++++++++++++++++++++++++++++++++*/
#ifdef De_ADCHard_Compiler	
	typedef struct
	{	uint8 OpenOrClose; 				//见<De_Adc_Fun_Open>与<De_Adc_Fun_Close>
		uint8 Precision;				//转换的精度，见<De_Adc_Trans_PrecisionX>定义
		uint32 CLK;		 				//A/D转换所采用的时钟,最大不得高于De_Adc_Max_Clk
		uint32 Modulus;	   				//参考电压以及转化参
	}st_Data_Adc_Oper;
#endif
/*========================================static Function===================================================*/
#ifdef De_ADCHard_Compiler
	static uint16 Init(void);
	static uint16 Open(uint8 Port,st_Data_Adc	*ptst_Data_Adc);
	static uint16 Read(uint8 Port,uint32 *Vol);
	static uint16 Close(uint8 Port);
#endif
/*======================================Public Ram=========================================================*/
#ifdef De_ADCHard_Compiler
	const uint8 CN_Ba_PortDe[]=
	{	De_Adc_Port_0,De_Adc_Port_1,De_Adc_Port_2,De_Adc_Port_3,
		De_Adc_Port_4,De_Adc_Port_5,De_Adc_Port_6,De_Adc_Port_7	
	};				//有效端口定义
	const uint8 CN_Ba_PortSpace[]=
	{ 	De_Adc_Port_Space_0,De_Adc_Port_Space_1,De_Adc_Port_Space_2,De_Adc_Port_Space_3,
		De_Adc_Port_Space_4,De_Adc_Port_Space_5,De_Adc_Port_Space_6,De_Adc_Port_Space_7
	};				//各个有效端口所处的位置
	const uint8 CN_Ba_Precision[]=
	{	De_Adc_Trans_Precision0,De_Adc_Trans_Precision1,De_Adc_Trans_Precision2,De_Adc_Trans_Precision3,
		De_Adc_Trans_Precision4,De_Adc_Trans_Precision5,De_Adc_Trans_Precision6,De_Adc_Trans_Precision7
	}; 				//电压的精度
	const st_Data_Adc_Oper	CN_Ba_st_Data_Adc_Oper=
	{	De_Adc_Fun_Close,0x00,0x00000000,0x00000000	
	};
	const st_Fun_Adc	CN_st_Fun_Adc={Init,Open,Read,Close};
	st_Data_Adc_Oper	CN_st_Data_Adc[sizeof(CN_Ba_PortDe)];
	static OS_EVENT *AdcSem=NULL;
#else
	extern const st_Fun_Adc	CN_st_Fun_Adc;
#endif	






