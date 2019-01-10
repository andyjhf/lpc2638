#define DePublic_h
#ifdef	DePublic_h
/*========================================����ѡ��======================================================*/
	/*++++++++++++++++++++++++++++++++miscellaneous++++++++++++++++++++++++++++++++++++++++++*/
	#define De_Compiler_miscellaneous_Date							//_Date.c����
	#define De_Compiler_miscellaneous_AscNumber						//_AscNumber.c����
	#define De_Compiler_miscellaneous_Arithmetic					//_Arithmetic.c����	
	/*+++++++++++++++++++++++++++++++HardWare++++++++++++++++++++++++++++++++++++++++++++++++*/
	#define De_Compiler_HardWare_Can								//_Can.C����
	#define De_Compiler_HardWare_UART								//_UART.C����
	#define De_Compiler_HardWare_Spi								//_Spi.c����
	#define De_Compiler_HardWare_SpiFlash							//_SpiFlash����
	#define De_Compiler_HardWare_RTC								//_RTC.C���� 	
	#define De_Compiler_HardWare_Gps								//Gps.c����
	/*+++++++++++++++++++++++++++++++++File+++++++++++++++++++++++++++++++++++++++++++++++++*/
	#define De_Compiler_File_rwflashlgc								//_rwflashlgc.c����
	#define De_Compiler_File_rwFile									//rwFile.c����
	/*+++++++++++++++++++++++++++++++++Control++++++++++++++++++++++++++++++++++++++++++++++*/
	#define De_Compiler_Control_adc									//adc.c����
	#define De_Compiler_Control_GpsTask								//GpsTask.c����
	#define De_Compiler_Control_GPRS								//GPRS.c����
	#define De_Compiler_Control_Timer								//Timer.c����
	/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/

/*=====================================�����������===========================================*/
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
/*============================������̫���ڵ�RAM================================================*/	
	#define De_Ram_Mac				0x7FE00000 						//LPC��̫����RAM��ʼ��ַ
  	#define De_Uart_Ram 			De_Ram_Mac						//���ڵĿ�ʼ��ַ
	#define De_Flash_Ram			De_Uart_Ram+5120				//Flash������ʱ��RAM
	#define De_File_Ram				De_Flash_Ram+512				//FileRAMʹ��
	#define De_TzV21_Ram			De_File_Ram+1024				//����Э��ʹ��
	#define De_TzV21_STK			De_TzV21_Ram+3072				//Э���ջʹ��
	#define De_IPData_Ram			De_TzV21_STK+3072
	#define De_Gprs_STK_Ram			De_IPData_Ram+2048				//Э��
	//#define De_Data_Resu_Ram		De_Gprs_STK_Ram	

	
	
	
	
	
	
/*=====================================����USB�˿�Ram================================================*/	
	#define De_GprsHard_Ram			0x7FD00000					//Ӳ���ӿ�ʹ��3K
	#define De_Gprs_Ram				De_GprsHard_Ram+3050		//GPRSʹ�ó���





#endif
