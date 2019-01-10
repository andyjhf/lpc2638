/*===========================================Include File=======================================================*/	
	#include "..\..\APP\config.h"
	#include "stdlib.h"
	#ifdef De_18B20_Compiler
		#include "..\..\miscellaneous\CodeTrans\AscNumber.h"
		#include "..\..\miscellaneous\Arithmetic\Arithmetic.h"	
		#include "..\..\HardWare\UART\UART.h"
		#include "..\..\miscellaneous\Date\date.h"			
	#endif
    /*===========================================Define Data=======================================================*/
	#define De_Suc_18B20												0				//本页成功
	#define De_18B20_Fun_Open											0				//此功能打开
	#define De_18B20_Fun_Close											1				//此功能关闭
	/*++++++++++++++++++++++++++++++++++++++++错误代码一览表++++++++++++++++++++++++++++++++++++++++++++++*/
	#define De_Erro_18B20_NoInit							0x88	    // 初始化失败
	#define De_Erro_18B20_NOPRESENCE						De_Erro_18B20_NoInit+1   // 传感器不在位
	#define De_Erro_18B20_ADDRESS						    De_Erro_18B20_NOPRESENCE+1  //传感器地址错误 
	#define De_Erro_18B20_CRC								De_Erro_18B20_ADDRESS+1       //CRC校验错误
	#define De_Erro_18B20_BUS							    De_Erro_18B20_CRC+1       //总线错误
	#define De_Erro_18B20_NoPort						    De_Erro_18B20_BUS+1 
	#define De_Erro_18B20_NoOpen					        De_Erro_18B20_NoPort+1 

	typedef struct
	{	
		uint16 (*Init)(void);
		uint16 (*Open)(uint8 port);
		uint16 (*Read)(uint8 port,uint32 *value);
		uint16 (*Close)(uint8 port);
	}st_Fun_18B20;

    
    #ifdef De_18B20_Compiler	
        
        /*++++++++++++++++++++++++++++++++++++++++ROM操作指令 ++++++++++++++++++++++++++++++++++++++++++++++*/               
        #define DS18B20_READ_ROM		    0x33    // 读ROM
        #define DS18B20_MATCH_ROM		    0x55    // 匹配ROM
        #define DS18B20_SKIP_ROM		    0xCC    // 不提供编码访问ROM
        #define DS18B20_SEARCH_ROM		    0xF0    // 搜索ROM
        #define DS18B20_ALARM_SEARCH	    0xEC    // 报警搜索 

		#define DS18B20_CONVERT_TEMP		0x44	// 启动一次温度转换
		#define DS18B20_WRITE_SCRATCHPAD	0x4E	// 写暂存寄存器
		#define DS18B20_READ_SCRATCHPAD		0xBE    // 读取暂存寄存器
		#define DS18B20_COPY_SCRATCHPAD		0x48	// 将暂存寄存器的数据拷贝到EEPROM
		#define DS18B20_RECALL_EEPROM		0xB8    // 将报警寄存器的值拷贝到暂存寄存器
		#define DS18B20_READ_POWER			0xB4    // 读取电源模式

		/*++++++++++++++++++++++++++++++++++++++++硬件端口操作 ++++++++++++++++++++++++++++++++++++++++++++++*/  
		#define DS18B20_PIN0                22	   // P0.22	为温度1路 
		#define DS18B20_PIN1 	         	20     // P0.20 为温度2路 
		#define DS18B20_PORT0               0
		#define DS18B20_PORT1               1		

		#define DS18B20_FunOpen_PORT0       {PINSEL1 &=~ (1<<13);PINSEL1 &= ~(1<<12);}  // P0.22选择为GPIO     
	   	#define DS18B20_FunOpen_PORT1       {PINSEL1 &=~ (1<<9) ;PINSEL1 &= ~(1<<8);} 	// P0.20选择为GPIO 

		#define DS18B20_Port_Out(x)     IODIR0 |=  (1<<x)
		#define DS18B20_Port_In(x)      IODIR0 &= ~(1<<x)                  
		#define DS18B20_Out_High(x)	    IOSET0 |=  (1<<x) 
		#define DS18B20_Out_Low(x)     	IOCLR0 |=  (1<<x)
		#define DS18B20_Pin_Value(x)    IOPIN0 &   (1<<x)
		
		
		/*++++++++++++++++++++++++++++++++++++8位CRC++++++++++++++++++++++++++++*/
		static const uint8 crc8_table[] =		// dallas crc lookup table
		{
			0, 94,188,226, 97, 63,221,131,194,156,126, 32,163,253, 31, 65,
			157,195, 33,127,252,162, 64, 30, 95, 1,227,189, 62, 96,130,220,
			35,125,159,193, 66, 28,254,160,225,191, 93, 3,128,222, 60, 98,
			190,224, 2, 92,223,129, 99, 61,124, 34,192,158, 29, 67,161,255,
			70, 24,250,164, 39,121,155,197,132,218, 56,102,229,187, 89, 7,
			219,133,103, 57,186,228, 6, 88, 25, 71,165,251,120, 38,196,154,
			101, 59,217,135, 4, 90,184,230,167,249, 27, 69,198,152,122, 36,
			248,166, 68, 26,153,199, 37,123, 58,100,134,216, 91, 5,231,185,
			140,210, 48,110,237,179, 81, 15, 78, 16,242,172, 47,113,147,205,
			17, 79,173,243,112, 46,204,146,211,141,111, 49,178,236, 14, 80,
			175,241, 19, 77,206,144,114, 44,109, 51,209,143, 12, 82,176,238,
			50,108,142,208, 83, 13,239,177,240,174, 76, 18,145,207, 45,115,
			202,148,118, 40,171,245, 23, 73, 8, 86,180,234,105, 55,213,139,
			87, 9,235,181, 54,104,138,212,149,203, 41,119,244,170, 72, 22,
			233,183, 85, 11,136,214, 52,106, 43,117,151,201, 74, 20,246,168,
			116, 42,200,150, 21, 75,169,247,182,232, 10, 84,215,137,107, 53
		};     

    #endif
    
    /*===========================================Data Define=======================================================*/
	/*++++++++++++++++++++++++++++++++++++++++私有结构体数据++++++++++++++++++++++++++++++++++++++++++++++*/  	

	#ifdef De_18B20_Compiler  
	
		
		typedef struct
		{	
			uint8 state; 				//当前状态，打开/关闭		
		}st_Data_18B20_Oper;
		
				
	
		static uint32 intrup;	   		
		static OS_EVENT *DS18B20Sem = NULL;
		static uint16 Init(void);
		static uint16 Open(uint8 pin);
		static uint16 Read(uint8 pin,uint32 *value);
		static uint16 Close(uint8 pin);
		static uint16 DS18B20ReadTemp(uint32 *value,uint8 PinNum);

		/*======================================Public Ram=========================================================*/

		const uint8 CN_Ba_PinDe[]=
		{	
			DS18B20_PORT0,
			DS18B20_PORT1
		};				    //有效引脚定义 		

		st_Data_18B20_Oper	CN_st_Data_18B20[sizeof(CN_Ba_PinDe)];

		const st_Fun_18B20  CN_st_Fun_18B20 = {Init,Open,Read,Close};

	
	#else
		extern const st_Fun_18B20  CN_st_Fun_18B20;
	#endif


