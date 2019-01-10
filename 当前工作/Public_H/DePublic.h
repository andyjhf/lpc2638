#define DePublic_h
#ifdef	DePublic_h
/*========================================编译选择======================================================*/
	/*++++++++++++++++++++++++++++++++miscellaneous++++++++++++++++++++++++++++++++++++++++++*/
	#define De_Compiler_miscellaneous_Date							//_Date.c编译
	#define De_Compiler_miscellaneous_AscNumber						//_AscNumber.c编译
	#define De_Compiler_miscellaneous_Arithmetic					//_Arithmetic.c编译	
	/*+++++++++++++++++++++++++++++++HardWare++++++++++++++++++++++++++++++++++++++++++++++++*/
	#define De_Compiler_HardWare_Can								//_Can.C编译
	#define De_Compiler_HardWare_UART								//_UART.C编译
	#define De_Compiler_HardWare_Spi								//_Spi.c编译
	#define De_Compiler_HardWare_SpiFlash							//_SpiFlash编译
	#define De_Compiler_HardWare_RTC								//_RTC.C编译 	
	#define De_Compiler_HardWare_Gps								//Gps.c编译
	/*+++++++++++++++++++++++++++++++++File+++++++++++++++++++++++++++++++++++++++++++++++++*/
	#define De_Compiler_File_rwflashlgc								//_rwflashlgc.c编译
	#define De_Compiler_File_rwFile									//rwFile.c编译
	/*+++++++++++++++++++++++++++++++++Control++++++++++++++++++++++++++++++++++++++++++++++*/
	#define De_Compiler_Control_adc									//adc.c编译
	#define De_Compiler_Control_GpsTask								//GpsTask.c编译
	#define De_Compiler_Control_GPRS								//GPRS.c编译
	#define De_Compiler_Control_Timer								//Timer.c编译
	/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/

/*=====================================错误代码分配表===========================================*/
	#define De_Erro_GPRS											1
	/*++++++++++++++++++++++++++++++Miscellaneous++++++++++++++++++++++++++++++++++++++++++++*/
	
	#define De_Erro_Date											De_Erro_GPRS+50
	#define De_Erro_AscNumber										De_Erro_Date+50
	#define De_Erro_Arithmetic										De_Erro_AscNumber+50
	/*++++++++++++++++++++++++++++++++HareWare++++++++++++++++++++++++++++++++++++++++++++++*/
	#define De_Erro_Can												De_Erro_Arithmetic+50
	#define De_Erro_UART											De_Erro_Can+50
	#define De_Erro_Spi												De_Erro_UART+50
	#define De_Erro_SpiFlash										De_Erro_Spi+50
	#define De_Erro_RTC												De_Erro_SpiFlash+50
	#define De_Erro_Gps												De_Erro_RTC+50
	/*+++++++++++++++++++++++++++++++File++++++++++++++++++++++++++++++++++++++++++++++++++*/
	#define De_Erro_rwflashlgc										De_Erro_Gps+50
	#define De_Erro_rwFile											De_Erro_rwflashlgc+50
	/*+++++++++++++++++++++++++++++++++adc++++++++++++++++++++++++++++++++++++++++++++++++*/
	#define De_Erro_adc												De_Erro_rwFile+50
	#define De_Erro_GpsTask											De_Erro_adc+50
	
	#define De_Erro_Timer											De_Erro_GpsTask+50	
/*============================利用以太网口的RAM================================================*/	
	#define De_Ram_Mac				0x7FE00000 						//LPC以太网口RAM起始地址
  	#define De_Uart_Ram 			De_Ram_Mac						//串口的开始地址
	#define De_Flash_Ram			De_Uart_Ram+5120				//Flash擦扇区时的RAM
	#define De_File_Ram				De_Flash_Ram+512				//FileRAM使用
	#define De_TzV21_Ram			De_File_Ram+1024				//天泽协议使用
	#define De_TzV21_STK			De_TzV21_Ram+3072				//协议堆栈使用
	#define De_IPData_Ram			De_TzV21_STK+3072
	#define De_Gprs_STK_Ram			De_IPData_Ram+2048				//协议
	//#define De_Data_Resu_Ram		De_Gprs_STK_Ram	

	
	
	
	
	
	
/*=====================================利用USB端口Ram================================================*/	
	#define De_GprsHard_Ram			0x7FD00000					//硬件接口使用3K
	#define De_Gprs_Ram				De_GprsHard_Ram+3050		//GPRS使用长度





#endif
