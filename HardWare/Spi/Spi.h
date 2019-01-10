#include "..\..\Public_H\DePublic.h"
#ifdef	De_Compiler_HardWare_Spi

/*===============================Include File==========================================================*/
      #include "..\..\APP\config.h"
      #include "stdlib.h"


/*===================================Define Data=======================================================*/
	#define  OS_ADD  	//�˱����綨�壬���ڲ���ϵͳ��ʹ�ã��������������ǰ��̨ϵͳ��ʹ��
	  /*++++++++++++++++++++++++++++++++++�������һ����++++++++++++++++++++++++++++++++++++++++++++*/
	#define De_Suc_Spi										0 				//�ɹ�
	
	#define De_Erro_Spi_Open									De_Erro_Spi				//��SPI����					
	#define De_Erro_Spi_Task									De_Erro_Spi_Open+1				//�Ǳ������ִ��
	#define De_Erro_Spi_Busy									De_Erro_Spi_Task+1				//Spi����æ
	#define De_Erro_Spi_Byte									De_Erro_Spi_Busy+1				//���ݲ�һ��
      

	/*+++++++++++++++++++++++++++++++++++HardWareI/O+++++++++++++++++++++++++++++++++++++++++++++++*/
	#define De_IO_Spi_SCK								0x00100000
	#define De_IO_Spi_Din								0XFF7fffff
	#define De_IO_Spi_Dou								0x01000000
	#define De_IO_Spi_SCK_OUT							IODIR1|=De_IO_Spi_SCK
	#define De_IO_Spi_Din_INT							IODIR1&=De_IO_Spi_Din
	#define De_IO_Spi_Dout_OUT							IODIR1|=De_IO_Spi_Dou

/*==============================Data Define============================================================*/
	
	/*++++++++++++++++++++++++++++++Function Out++++++++++++++++++++++++++++++++++++++++++++++++*/
	typedef struct
	{ 	/*	�������ܣ���SPI�ڣ��˺���������֮ǰ�����
			����ֵ:	0:�ɹ�			��0	<����������>
		*/
		uint16 (* Open)(void);
		/*	�������ܣ���ʼSPI���ߣ���ȡ��SPI��ʹ��Ȩ
			��ڲ���:	�������	ChipSelect	ʹ��SPI/CEѡͨ	      ����ָ��
									ChipSelectOver	ʹ��SPI/CE�ر�    ����ָ��
			����ֵ:	0:�ɹ�			��0	<����������>							
		*/
		uint16 (* Start)(void (*ChipSelect)(void),void (*ChipSelectOver)(void));
		/*	�������ܣ�SPI����д��ʱ��ͬʱ����
			��ڲ���:	�������	wBuf		��д�����ݵ�ַ
									SizeofBuf	��д��������
						�������	rBuf		���������ݵ�ַ������������������д��������һ��
			����ֵ:	0:�ɹ�			��0	<����������>							
		*/
		uint16 (* RwSpi)(uint8 *wBuf,uint8 *rBuf,uint16 SizeofBuf);
		/*	�������ܣ���SPI������д����
			��ڲ���:	�������	Buf			��д�����ݵ�ַ
									SizeofBuf	��д��������
			����ֵ:	0:�ɹ�			��0	<����������>							
		*/
		uint16 (* Write)(uint8 *Buf,uint16 SizeofBuf);
		/*	�������ܣ���ȡSPI���ߵ�����
			��ڲ���:	�������	Buf			���������ݵ�ַ
									SizeofBuf	������������
			����ֵ:	0:�ɹ�			��0	<����������>							
		*/
		uint16 (* Read)(uint8 *Buf,uint16 SizeofBuf);
		/*	�������ܣ��ж�SPI�����������Ƿ���ͬһ������
			��ڲ���:	�������	ByteV		���жϵ�����
									SizeofBuf	���ж����ݵ�����
			����ֵ:	0:�ɹ�			��0	<����������>							
		*/
		uint16 (* JugeByte)(uint8 ByteV,uint32 SizeofBuf);
		/*	�������ܣ��ж�SPI�����������Ƿ���BUF����һ��
			��ڲ���:	�������	Buf		���жϵ�����
									SizeofBuf	���ж����ݵ�����
			����ֵ:	0:�ɹ�			��0	<����������>							
		*/
		uint16 (* JugeBuf)(uint8 *Buf,uint16 SizeofBuf);
		/*	�������ܣ�����SPI���ߣ��ͷŵ�SPI��ʹ��Ȩ
			��ڲ���:	�������	ChipSelect	ʹ��SPI/CE�ر�    ����ָ��	
			����ֵ:	0:�ɹ�			��0	<����������>							
		*/
		uint16 (* End)(void (*ChipSelect)(void));
		/*	�������ܣ��ر�SPI�ڣ��˺���һ�㲻��
			����ֵ:	0:�ɹ�			��0	<����������>
		*/
		uint16 (* Close)(void);    
    }st_Fun_Spi;			//SPI.C���


	#ifdef De_UART_Compiler
/*======================================static Function=========================================================*/
		static uint16 Open(void);
		static uint16 Start(void (*ChipSelect)(void),void (*ChipSelectOver)(void));
		static uint16 Read(uint8 *Buf,uint16 SizeofBuf);
		static uint16 End(void (*ChipSelect)(void));
		static uint16 Close(void);
		static uint16 Read(uint8 *Buf,uint16 SizeofBuf);
		static uint16 Write(uint8 *Buf,uint16 SizeofBuf);
		static uint16 JugeByte(uint8 ByteV,uint32 SizeofBuf);
		static uint16 JugeBuf(uint8 *Buf,uint16 SizeofBuf);
		static uint16 RwSpi(uint8 *wBuf,uint8 *rBuf,uint16 SizeofBuf);
		static void DelaySpi(void);
/*======================================Public Ram==============================================================*/
		#ifdef OS_ADD
		static OS_EVENT *SPISem=NULL;
		static uint8 UseSPITaskPro;
		#endif
		const st_Fun_Spi  CN_st_Fun_Spi={Open,Start,RwSpi,Write,Read,JugeByte,JugeBuf,End,Close};
	#else
		extern st_Fun_Spi  CN_st_Fun_Spi;
	#endif    
#endif
