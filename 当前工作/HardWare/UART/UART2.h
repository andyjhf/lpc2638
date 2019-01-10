#include "..\..\Public_H\DePublic.h"
#ifdef	De_Compiler_HardWare_UART

/*===============================Include File==========================================================*/
	#include "..\..\APP\config.h"
	#include "..\..\Public_H\DePublic.h"
	#include "stdlib.h"

/*===================================Define Data=======================================================*/
    #define  OS_ADD  	//�˱����綨�壬���ڲ���ϵͳ��ʹ�ã��������������ǰ��̨ϵͳ��ʹ��
	
 	#ifdef OS_ADD
		#define  OS_Message_Uart0					//��������0��Ϣģʽ
		#define  OS_Message_Uart1					//��������1��Ϣģʽ
		#define  OS_Message_Uart2					//��������2��Ϣģʽ
		#define  OS_Message_Uart3					//��������3��Ϣģʽ
	#endif


	/*+++++++++++++++++++++++++++++++++�������һ����++++++++++++++++++++++++++++++++++++++++++++*/
	#define De_Suc_Uart							0
	#define De_Erro_Uart								20					
	#define De_Erro_Uart_Init_0					De_Erro_Uart+1 					//��ʼ������0ʧ��
	#define De_Erro_Uart_Init_1					De_Erro_Uart_Init_0+1			//��ʼ������1ʧ��
	#define De_Erro_Uart_Init_2					De_Erro_Uart_Init_1+1			//��ʼ������2ʧ��
	#define De_Erro_Uart_Init_3					De_Erro_Uart_Init_2+1			//��ʼ������3ʧ��
	#define De_Erro_Uart_NoPort					De_Erro_Uart_Init_3+1			//�޴˶˿�
	#define De_Erro_Uart_BaudRate				De_Erro_Uart_NoPort+1			//�����ʲ���
	#define De_Erro_Uart_DataBit				De_Erro_Uart_BaudRate+1			//����λ����
	#define De_Erro_Uart_StopBit				De_Erro_Uart_DataBit+1			//ֹͣλ����
	#define De_Erro_Uart_Parity					De_Erro_Uart_StopBit+1			//��żУ�鲻��
	#define De_Erro_Uart0_NoData				De_Erro_Uart_Parity+1			//����0������
	#define De_Erro_Uart1_NoData				De_Erro_Uart0_NoData+1			//����1������
	#define De_Erro_Uart2_NoData				De_Erro_Uart1_NoData+1			//����2������
	#define De_Erro_Uart3_NoData				De_Erro_Uart2_NoData+1			//����3������
	
	/*+++++++++++++++++++++++++++++++++++++�˿ڶ���+++++++++++++++++++++++++++++++++++++++++*/
	#define De_Uart_Port_0							0 				//����0
	#define De_Uart_Port_1							1				//����1
	#define De_Uart_Port_2							2				//����2
	#define De_Uart_Port_3							3				//����3

	/*+++++++++++++++++++++++++++++++++++++Ram��ַ����++++++++++++++++++++++++++++++++++++++++++*/
	#define De_Uart_RecMaxSize					2048	 						//uart�����ܵ��ֽ�����
	#define De_UartRam							De_Uart_Ram	  					//���ڽ��ܻ�����׵�ַ
	#define De_Uart0Ram							De_UartRam						//����0���ܻ����׵�ַ
	#define De_Uart1Ram							De_Uart0Ram+De_Uart_RecMaxSize	//����1���ܻ����׵�ַ
	#define De_Uart2Ram							De_Uart1Ram+De_Uart_RecMaxSize	//����2���ܻ����׵�ַ
	#define De_Uart3Ram							De_Uart2Ram+De_Uart_RecMaxSize	//����3���ܻ����׵�ַ

	/*++++++++++++++++++++++++++++++++++++HardWareI/O+++++++++++++++++++++++++++++++++++++++++++*/
	#ifdef De_UART_Compiler	
		#define  De_Uart_Port0_Power_up					PCONP=(PCONP|0X00000008)   //����0���ʼĴ�������
		#define  De_Uart_Port1_Power_up					PCONP=(PCONP|0X00000010)   //����1���ʼĴ�������
		#define  De_Uart_Port2_Power_up					PCONP=(PCONP|0X01000000)   //����2���ʼĴ�������
		#define  De_Uart_Port3_Power_up					PCONP=(PCONP|0X02000000)   //����3���ʼĴ�������
		
		
		#define De_Uart_Port0_Power_Down				PCONP=(PCONP&0xfffffff7)   //����0���ʼĴ����ر�
		#define De_Uart_Port1_Power_Down				PCONP=(PCONP&0xffffff7f)   //����1���ʼĴ����ر�
		#define De_Uart_Port2_Power_Down				PCONP=(PCONP&0xfeffffff)   //����2���ʼĴ����ر�
		#define De_Uart_Port3_Power_Down				PCONP=(PCONP&0xfdfffff7)   //����3���ʼĴ����ر�
		
		#define De_Uart_OpenIO_0				PINSEL0 = (PINSEL0 & 0xffffff0f) | 0x50	//����0�������⹦�ܼĴ���
		#define De_Uart_OpenIO_1				PINSEL0 = (PINSEL0&0X3FFFFFFF)|0X40000000;PINSEL1=((PINSEL0&0XFFFFFFFC)|0X00000001);//����1�������⹦�ܼĴ���
		#define De_Uart_OpenIO_2				PINSEL0 = (PINSEL0&0XFF0FFFFF)|0X00500000; //����2�������⹦�ܼĴ���
		#define De_Uart_OpenIO_3				PINSEL0 = (PINSEL0&0XFFFFFFF0)|0X0000000A; //����3�������⹦�ܼĴ���
		
  	#endif


/*==============================Data Define============================================================*/
	/*+++++++++++++++++++++++++++++���ݽṹ��++++++++++++++++++++++++++++++++++++++++*/
	typedef struct
	{	uint32  BaudRate;				//������
		uint8  DataBit;					//��������λ5/6/7/8����λ��
		uint8  StopBit;					//ֹͣλ.1/2λ��
		uint8  Parity;					//��żУ��λ,0:����żУ�飻1:��У��;2��żУ��
	}st_Da_Uart;

	/*+++++++++++++++++++++++++++++Function Out++++++++++++++++++++++++++++++++++++++++*/
	typedef struct
	{	/*	��������:��ʼ������,�ϵ��ʹ��һ���Ժ�,��ʹ��
			��ڲ���:	ComNumber		0~3֮��,������4������
			����ֵ:	 0:�ɹ�			��0	<����������>	
	
		*/
		uint16 (*Init)(uint8 ComNumber);
		/*	��������:��һ��ָ���Ĵ���,��ȡ���ڵ�ʹ��Ȩ
			��ڲ���:	�������	ComNumber	0~3֮��,������4������
									ptst_Da_Uart	���<st_Da_Uart>����
			����ֵ:	 0:�ɹ�			��0	<����������>
		
		*/
		uint16 (*Open)(uint8 ComNumber,st_Da_Uart	*ptst_Da_Uart);
		/*	��������:	�ر�һ��ָ���Ĵ���
			��ڲ���:	�������	ComNumber	0~3֮��,������4������
			����ֵ:	 0:�ɹ�			��0	<����������>
		
		*/
		uint16 (*Close)(uint8 ComNumber);
		/*	��������:	��ȡָ�����ڵ�����
			��ڲ���:	�������	ComNumber	0~3֮��,������4������
									DataLen		�����Ĵ���������
						�������	Data		����������
			����ֵ:ʵ���������ֽ�����						
		*/
		uint16 (*Read)(uint8 ComNumber,uint8 *Data,uint16 DataLen);

		/*	��������:	дָ�����ڵ�����
			��ڲ���:	�������	ComNumber	0~3֮��,������4������
									DataLen		��д�Ĵ����ֽ�������
									Data		��д������
			����ֵ:ʵ���������ֽ�����						
		*/
		uint16 (*Write)(uint8 ComNumber,uint8 *Data,uint16 DataLen);
	}st_Fun_Uart;				//Uart.c��

/*======================================static Function======================================================*/
	#ifdef De_UART_Compiler
		static uint16 Init(uint8 ComNumber);
		static uint16 Open(uint8 ComNumber,st_Da_Uart	*ptst_Da_Uart);
		static uint16 Close(uint8 ComNumber);
		static uint16 Read(uint8 ComNumber,uint8 *Data,uint16 DataLen);
		static uint16 Write(uint8 ComNumber,uint8 *Data,uint16 DataLen);
		
		
		
		static uint16 Open0(st_Da_Uart	*ptst_Da_Uart);
		static uint16 Close0(void);
		static uint16 Read0(uint8 *Data,uint16 DataLen);
		static uint16 Write0(uint8 *Data,uint16 DataLen);
		static uint16 Receive0Byte(uint8 *ByteV); 	
		
		
		static uint16 Open1(st_Da_Uart	*ptst_Da_Uart);
		static uint16 Close1(void);
		static uint16 Read1(uint8 *Data,uint16 DataLen);
		static uint16 Write1(uint8 *Data,uint16 DataLen);
		static uint16 Receive1Byte(uint8 *ByteV);
		
		static uint16 Open2(st_Da_Uart	*ptst_Da_Uart);
		static uint16 Close2(void);
		static uint16 Read2(uint8 *Data,uint16 DataLen);
		static uint16 Write2(uint8 *Data,uint16 DataLen);
		static uint16 Receive2Byte(uint8 *ByteV);
		
		static uint16 Open3(st_Da_Uart	*ptst_Da_Uart);
		static uint16 Close3(void);
		static uint16 Read3(uint8 *Data,uint16 DataLen);
		static uint16 Write3(uint8 *Data,uint16 DataLen);
		static uint16 Receive3Byte(uint8 *ByteV);
		static uint16 ClearSem(OS_EVENT	*UartSem);

/*======================================Public Ram============================================================*/
		#ifdef OS_ADD
			OS_EVENT 		*Uart0UseSem;						//��ȡ����ʹ��Ȩ
			OS_EVENT 		*Uart1UseSem;						//��ȡ����ʹ��Ȩ
			OS_EVENT 		*Uart2UseSem;						//��ȡ����ʹ��Ȩ
			OS_EVENT 		*Uart3UseSem;						//��ȡ����ʹ��Ȩ
		#endif	
		#ifdef OS_Message_Uart0
			OS_EVENT 		*Uart0RxSem;						//��ȡ������ʹ��Ȩ
		#endif
		
		#ifdef OS_Message_Uart1
			OS_EVENT 		*Uart1RxSem;						//��ȡ������ʹ��Ȩ
		#endif
		
		#ifdef OS_Message_Uart2	
			OS_EVENT 		*Uart2RxSem;						//��ȡ������ʹ��Ȩ
		#endif
		#ifdef OS_Message_Uart3
			OS_EVENT 		*Uart3RxSem;						//��ȡ������ʹ��Ȩ
		#endif
		//���ܻ�����
		uint8 *ptUart0ReBuf=(uint8 *)De_Uart0Ram;
		uint8 *ptUart1ReBuf=(uint8 *)De_Uart1Ram;
		uint8 *ptUart2ReBuf=(uint8 *)De_Uart2Ram;
		uint8 *ptUart3ReBuf=(uint8 *)De_Uart3Ram;
		//�������ñ���
		uint16 UART0_RxHead,UART0_RxTail,UART1_RxHead,UART1_RxTail,UART2_RxHead,UART2_RxTail,UART3_RxHead,UART3_RxTail;
		const st_Fun_Uart	CN_st_Fun_Uart={Init,Open,Close,Read,Write};  //�����������
	#else
		extern const st_Fun_Uart CN_st_Fun_Uart;	 			//�����������

	#endif
#endif

/*--------------------------------------End Uart.h---------------------------------------------------------------*/
