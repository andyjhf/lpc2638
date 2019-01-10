/*=======================================include File=========================================================*/
#include "..\..\APP\config.h"											//LPC2368�Ĵ�������
#include "stdlib.h"
#include "GprsPublicDe.h"
#ifdef De_GprsHard_Compiler
	#include "..\..\HardWare\UART\UART.h" 								//���ô���
	#include "..\..\miscellaneous\CodeTrans\AscNumber.h"				//��������ת����Դ
	#include "..\..\miscellaneous\Date\Date.h"							//����������Դ
	#include "..\..\miscellaneous\Arithmetic\Arithmetic.h" 				//�����㷨
	#include "Huaiwei\_HuaiweiGprs.h"
#endif
/*======================================Define Data==========================================================*/
	/*++++++++++++++++++++++++++++++++++++++Ӳ��GPIO�ڲ���+++++++++++++++++++++++++++++++++++++++*/

	#define De_Fun_GprsHard_ModermPowerUp	IODIR0  |= (1<<7);IODIR0  |= (1<<9);IOSET0 |= (1<<9);IOCLR0 |= (1<<7);MODEM_Dly100ms(20);IOSET0 |= (1<<7);MODEM_Dly100ms(20);IOCLR0 |= (1<<7)
	#define De_Fun_GprsHard_ModermPowerRst	IODIR0  |= (1<<9);IOSET0 |= (1<<9);IOCLR0 |= (1<<9);OSTimeDly(OS_TICKS_PER_SEC*4);IOSET0 |= (1<<9);OSTimeDly(30*OS_TICKS_PER_SEC)
#ifdef De_GprsHard_Compiler
	#define De_GprsHard_Use_Uart										2				//ʹ�ô���2
	/*+++++++++++++++++++++++++++++++++++ͨ������������ʱʱ��+++++++++++++++++++++++++++++++++++*/
	#define De_GprsHard_Com_MaxDelay_AT						300								//����AT����
	#define De_GprsHard_Com_MaxDelay_ChipID					200								//��ȡ���Ҵ���
	#define De_GprsHard_Com_MaxDelay_ATE					300								//�رջ���
	#define De_GprsHard_Com_MaxDelay_BPS					300								//���ò����� 
	/*+++++++++++++++++++++++++++++++++++����ģ��ʹ��ʱ��RAM����++++++++++++++++++++++++++++++++++++++++++*/
	#define De_GprsHard_Use_Ram								De_GprsHard_Ram					//Ӳ����ʹ��USBRAM
	#define De_GprsHard_Use_Ram_Len							3050							//ʹ�õĳ���
#endif		
/*=========================================Data Define=======================================================*/	
	typedef struct
	{	uint16 (*Init)(void);				//��ʼ������
		uint16 (*Open)(void);			  	//��
		uint16 (*Close)(void); 			  	//�ر�
		uint16 (*Read)(uint16 Command,void *SendBuf,uint16 SizeofSendBuf,void *AgreeBuf,uint16 *SizeofAgreeBuf);
	}st_Fun_GprsHard;						//��������б�

/*========================================Function Define=====================================================*/
#ifdef De_GprsHard_Compiler	
	/*-------------------------------------�����������-------------------------------------------------*/
	static uint16 Init(void);				//��ʼ����ҳ
	static uint16 PowerUp(void);			//ģ�鿪��
	static uint16 PowerDown(void);			//ģ��ػ�
	static uint16 Read(uint16 Command,void *SendBuf,uint16 SizeofSendBuf,void *AgreeBuf,uint16 *SizeofAgreeBuf);//ִ������	 	
	/*----------------------------------------�м�֧��--------------------------------------------------*/
	static uint16 InitModerm(void);			//��ʼ��ģ��,������Ϊ115200
	static uint16 LookChipID(st_Fun_GprsHard_Fac	**ptst_Fun_GprsHard_Fac1);					//����������ַ
	static uint16 GetChipID(uint8 *Buf);	 													//��ȡ���Ҵ���	
	static uint16 GetBpsAT(void);
	static uint16 CloseShow(void);
	static uint16 SetBps(uint32 Bps);																//����ATָ��,���Բ���������	
	/*--------------------------------------��ModermͨѶ------------------------------------------------*/
	static uint16 ModermCom(uint8 *SendBuf,uint8 *AgreeBuf,uint16 SizeofAgreeBuf,st_GprsHard_Order_Cut	*ptst_GprsHard_Order_Cut);
	static uint16 ModermCom1(uint8 *SendBuf,uint8 *AgreeBuf,uint16 SizeofAgreeBuf,st_GprsHard_Order_Cut	*ptst_GprsHard_Order_Cut);//,uint16 *DataLength1);
	/*----------------------------------------ϵͳ����--------------------------------------------------*/
	static void MODEM_Dly100ms(int num);		 			
	static void ClearNoDisplay(uint8 *Buf);
#endif
/*========================================Public Ram==========================================================*/
	#ifdef De_GprsHard_Compiler
		/*+++++++++++++++++++++++++++++++++++��������+++++++++++++++++++++++++++++++++++++++++++++++++++++++*/
		const st_Fun_GprsHard	CN_st_Fun_GprsHard={Init,PowerUp,PowerDown,Read};					//�����������
		/*-----------------------------------����������---------------------------------------------*/
		const st_Fun_GprsHard_Fac	*ptCN_st_Fun_GprsHard_Fac[]=   							//����ģ��Ӳ���ӿ�
		{	&CN_Huawei_st_Fun_GprsHard_Fac						//��Ϊģ��
																//������
																//����			
		};
		const st_GprsHard_Order_Cut	CN_st_GprsHard_Order_Cut_AT={De_GprsHard_Com_MaxDelay_AT,"AT","\r\n","","\r\n","OK",""};
		const st_GprsHard_Order_Cut	CN_st_GprsHard_Order_Cut_ATE={De_GprsHard_Com_MaxDelay_ATE,"ATE0","\r\n","","\r\n","OK",""};
		const st_GprsHard_Order_Cut	CN_st_GprsHard_Order_Cut_ChipID={De_GprsHard_Com_MaxDelay_ChipID,"AT+GMI","\r\n","","\r\n","OK",""};
		const st_GprsHard_Order_Cut	CN_st_GprsHard_Order_Cut_BPS={De_GprsHard_Com_MaxDelay_BPS,"AT+IPR=","\r\n","","\r\n","OK","ERROR"};
		const st_Da_Uart	CN_Ba_st_Da_Uart_GprsHard[]= 					//�������б�
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
		/*++++++++++++++++++++++++++++++++++++RAM����++++++++++++++++++++++++++++++++++++++++++++++++++++++*/
		st_Fun_GprsHard_Fac	*ptst_Fun_GprsHard_Fac;
		uint8 *X_RAM=(uint8 *)De_GprsHard_Use_Ram;
	#else
		extern const st_Fun_GprsHard CN_st_Fun_GprsHard;	
	#endif	

