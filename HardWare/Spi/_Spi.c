#define  De_UART_Compiler
#include "Spi.h"
#ifdef De_Compiler_HardWare_Spi 
 /*	�������ܣ���SPI�ڣ��˺���������֮ǰ�����
			����ֵ:	0:�ɹ�			��0	<����������>
*/
static uint16 Open(void)								//��ʼ��SPI����
{
	if(SPISem!=NULL)
		return De_Suc_Spi;
	PCONP|=(1<<21);
	PINSEL3|=(0X03<<8)|(0X03<<10)|(0X03<<14)|(0X03<<16);
	SSP0CR0=0X000000C7;
	SSP0CPSR=0X20;
	//S0SPCCR=0X02;
			
	
	SSP0CR1|=0X02;
    #ifdef OS_ADD
	UseSPITaskPro = OS_PRIO_SELF;              
	SPISem=OSSemCreate(1); 					//����SPI���߶����񻥳�,��֤SPI�����ڲ���ʱ�򣬾�һ����������
	if(SPISem == NULL)
		return De_Erro_Spi_Open;	
	#endif
	return De_Suc_Spi;
}
/*	�������ܣ���ʼSPI���ߣ���ȡ��SPI��ʹ��Ȩ
			��ڲ���:	�������	ChipSelect	ʹ��SPI/CEѡͨ	      ����ָ��
									ChipSelectOver	ʹ��SPI/CE�ر�    ����ָ��
			����ֵ:	0:�ɹ�			��0	<����������>							
		*/
static uint16 Start(void (*ChipSelect)(void),void (*ChipSelectOver)(void))
{	uint8 err;
    #ifdef OS_ADD
	OSSemPend(SPISem, 0, &err);				//�ȴ��ͷ�SPI����,���������������ʹ�ã���������𣬵ȴ��ͷ�
	UseSPITaskPro=OSPrioCur;				//��ȡ��ǰ���������
	#endif
	ChipSelectOver();
	DelaySpi();
	while(SSP0SR&0x0c)
	{ 	err=SSP0DR;


	}
	ChipSelect();
	
	return De_Suc_Spi;
}
/*	�������ܣ�SPI����д��ʱ��ͬʱ����
			��ڲ���:	�������	wBuf		��д�����ݵ�ַ
									SizeofBuf	��д��������
						�������	rBuf		���������ݵ�ַ������������������д��������һ��
			����ֵ:	0:�ɹ�			��0	<����������>							
		*/
static uint16 RwSpi(uint8 *wBuf,uint8 *rBuf,uint16 SizeofBuf)
{	uint16 i;
	#ifdef OS_ADD
	if(UseSPITaskPro!=OSPrioCur)  //���ǿ�ʼ�������ڵ���
		return	De_Erro_Spi_Task; 
	#endif
	while(SSP0SR&0x0c)
	{	i=SSP0DR;


	}
	for(i=0;i<SizeofBuf;i++)
	{	while((SSP0SR&0X12)==0X00);
		SSP0DR=wBuf[i];
		while((SSP0SR&0X17)!=0x07);
		//				  N
		rBuf[i]=SSP0DR;
	}
	return De_Suc_Spi;
}
/*	�������ܣ���SPI������д����
			��ڲ���:	�������	Buf			��д�����ݵ�ַ
									SizeofBuf	��д��������
			����ֵ:	0:�ɹ�			��0	<����������>							
		*/
static uint16 Write(uint8 *Buf,uint16 SizeofBuf)
{	uint16 i;
	uint8 a;
	#ifdef OS_ADD
	if(UseSPITaskPro!=OSPrioCur)  //���ǿ�ʼ�������ڵ���
		return	De_Erro_Spi_Task; 
	#endif
	for(i=0;i<SizeofBuf;i++)
	{	while((SSP0SR&0X12)==0X00);
		SSP0DR=Buf[i];
		while((SSP0SR&0X17)!=0x07);
		a=SSP0DR;
	}
	return De_Suc_Spi;
}
/*	�������ܣ���ȡSPI���ߵ�����
			��ڲ���:	�������	Buf			���������ݵ�ַ
									SizeofBuf	������������
			����ֵ:	0:�ɹ�			��0	<����������>							
		*/
static uint16 Read(uint8 *Buf,uint16 SizeofBuf)
{ 	uint16 i;
	#ifdef OS_ADD
	if(UseSPITaskPro!=OSPrioCur)  //���ǿ�ʼ�������ڵ���
		return	De_Erro_Spi_Task; 
	#endif
	while(SSP0SR&0x0c)
	{	i=SSP0DR;


	}

	for(i=0;i<SizeofBuf;i++)
	{	while((SSP0SR&0X12)==0X00);
		SSP0DR=0xff;
		while((SSP0SR&0X17)!=0x07);
		//
		Buf[i]=SSP0DR;
	}
	return De_Suc_Spi;
}
	/*	�������ܣ��ж�SPI�����������Ƿ���BUF����һ��
			��ڲ���:	�������	Buf		���жϵ�����
									SizeofBuf	���ж����ݵ�����
			����ֵ:	0:�ɹ�			��0	<����������>							
		*/
static uint16 JugeBuf(uint8 *Buf,uint16 SizeofBuf)
{ 	uint16 i;
	#ifdef OS_ADD
	if(UseSPITaskPro!=OSPrioCur)  //���ǿ�ʼ�������ڵ���
		return	De_Erro_Spi_Task; 
	#endif
	while(SSP0SR&0x0c)
	{	i=SSP0DR;


	}
	for(i=0;i<SizeofBuf;i++)
	{	while((SSP0SR&0X12)==0X00);
		SSP0DR=0xff;
		while((SSP0SR&0X17)!=0x07);
		//
		if(Buf[i]!=SSP0DR)
			return De_Erro_Spi_Byte;
	}
	return De_Suc_Spi;
}

/*	�������ܣ��ж�SPI�����������Ƿ���ͬһ������
			��ڲ���:	�������	ByteV		���жϵ�����
									SizeofBuf	���ж����ݵ�����
			����ֵ:	0:�ɹ�			��0	<����������>							
		*/
static uint16 JugeByte(uint8 ByteV,uint32 SizeofBuf)
{	uint32 i;
	#ifdef OS_ADD
	if(UseSPITaskPro!=OSPrioCur)  //���ǿ�ʼ�������ڵ���
		return	De_Erro_Spi_Task; 
	#endif
	while(SSP0SR&0x0c)
	{	i=SSP0DR;


	}
	for(i=0;i<SizeofBuf;i++)
	{	while((SSP0SR&0X12)==0X00);
		SSP0DR=0xff;
		while((SSP0SR&0X17)!=0x07);
		//
		if(ByteV!=SSP0DR)
			return De_Erro_Spi_Byte;
	}
	return De_Suc_Spi;
}





 /*	�������ܣ�����SPI���ߣ��ͷŵ�SPI��ʹ��Ȩ
			��ڲ���:	�������	ChipSelect	ʹ��SPI/CE�ر�    ����ָ��	
			����ֵ:	0:�ɹ�			��0	<����������>							
		*/
static uint16 End(void (*ChipSelect)(void))
{	
	#ifdef OS_ADD
	if(UseSPITaskPro!=OSPrioCur)
		return 	De_Erro_Spi_Task;
	UseSPITaskPro = OS_PRIO_SELF;
	#endif
	ChipSelect();
	#ifdef OS_ADD
	OSSemPost(SPISem);				//֪ͨ�����������Ѿ�ʹ�ý���
	#endif
	return De_Suc_Spi;
}





 /*	�������ܣ��ر�SPI�ڣ��˺���һ�㲻��
			����ֵ:	0:�ɹ�			��0	<����������>
		*/
static uint16 Close(void)							//�ر�SPI����
{	
	#ifdef OS_ADD
	if(UseSPITaskPro!=OS_PRIO_SELF)
		return De_Erro_Spi_Busy;
	#endif
	return De_Suc_Spi;
}



static void DelaySpi(void)
{	uint16 i;
	for(i=0;i<100;i++);


}
#endif
