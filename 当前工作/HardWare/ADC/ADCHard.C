#define De_ADCHard_Compiler
#include "ADCHard.h"
/*==============================================================================================================*/
static uint16 Init(void)				 					//初始化本页
{	uint8 i;
	if(AdcSem!=NULL)
		return De_Suc_Adc;	
	for(i=0;i<sizeof(CN_Ba_PortDe);i++)
		CN_st_Fun_AscNumber.MoveByte(&CN_st_Data_Adc[i],(void *)&CN_Ba_st_Data_Adc_Oper,sizeof(st_Data_Adc_Oper));
	AdcSem=OSSemCreate(1);
	if(AdcSem==NULL)
		return De_Erro_Adc_Init;
	 De_HardWare_Open_Power;
	return De_Suc_Adc;
}
static uint16 Open(uint8 Port,st_Data_Adc	*ptst_Data_Adc)	//打开对应的ADC通道
{	uint8 i,j;
	OSSemPend(AdcSem, 0, &j);	 
	for(i=0;i<sizeof(CN_Ba_PortDe);i++)
	{	if(CN_Ba_PortDe[i]==Port)
			break;
	}
	for(j=0;j<sizeof(CN_Ba_PortDe);j++)
	{	if(CN_Ba_Precision[j]==ptst_Data_Adc->Precision)
			break;
	}
	if((i==sizeof(CN_Ba_PortDe))||(j==sizeof(CN_Ba_PortDe))||(ptst_Data_Adc->CLK>De_Adc_Max_Clk))
	{	OSSemPost(AdcSem);
		return De_Erro_Adc_NoPort;
	}
	if(Port==De_Adc_Port_0)
		De_HardWare_FunOpen_ADC0
	else if(Port==De_Adc_Port_1)
		De_HardWare_FunOpen_ADC1		
   	else if(Port==De_Adc_Port_2)
		De_HardWare_FunOpen_ADC2
	else if(Port==De_Adc_Port_3)
		De_HardWare_FunOpen_ADC3
	else if(Port==De_Adc_Port_4)
		De_HardWare_FunOpen_ADC4
   	else if(Port==De_Adc_Port_5)
		De_HardWare_FunOpen_ADC5
	else if(Port==De_Adc_Port_6)
		De_HardWare_FunOpen_ADC6
	else if(Port==De_Adc_Port_7)
		De_HardWare_FunOpen_ADC7
   	CN_st_Data_Adc[i].OpenOrClose=De_Adc_Fun_Open;
	CN_st_Data_Adc[i].Precision=ptst_Data_Adc->Precision;
	CN_st_Data_Adc[i].CLK=ptst_Data_Adc->CLK;
	CN_st_Data_Adc[i].Modulus=ptst_Data_Adc->Modulus;
	CN_st_Fun_AscNumber.MoveByte(&CN_st_Data_Adc[i],ptst_Data_Adc,sizeof(st_Data_Adc));
	OSSemPost(AdcSem);
	return De_Suc_Adc;
}

static uint16 Close(uint8 Port)				  //关闭对应的ADC通道
{	uint8 i;
	OSSemPend(AdcSem, 0, &i);
	for(i=0;i<sizeof(CN_Ba_PortDe);i++)
	{	if(CN_Ba_PortDe[i]==Port)	
	   		break;
	}
	if(i==sizeof(CN_Ba_PortDe))
	{	OSSemPost(AdcSem);
		return De_Erro_Adc_NoPort;
	}
	CN_st_Data_Adc[i].OpenOrClose=De_Adc_Fun_Close;
	OSSemPost(AdcSem);
	return De_Suc_Adc;	
}

static uint16 Read(uint8 Port,uint32 *Vol)			   //读取对应的ADC通道电压
{	uint32 AdcVal;
	uint8 i,err;
	OSSemPend(AdcSem, 0, &err);
	for(i=0;i<sizeof(CN_Ba_PortDe);i++)
	{	if(CN_Ba_PortDe[i]==Port)
			break;
	}
	if((i==sizeof(CN_Ba_PortDe))||(CN_st_Data_Adc[i].OpenOrClose==De_Adc_Fun_Close))
	{	OSSemPost(AdcSem);
		return De_Erro_Adc_NoPort;
	}
	
	AD0CR=(1<<CN_Ba_PortSpace[i])|	 						//哪个通道
		  ((Fpclk/CN_st_Data_Adc[i].Modulus-1)<<8)|					//频率
		   (0<<16)|											//软件控制
		  (CN_Ba_Precision[CN_st_Data_Adc[i].Precision]<<17)|	//控制精度
		  (1<<21)|											//正常工作
		  (0<<22)|											//正常模式
		  (1<<24);											//AD启动
 	if(Port==De_Adc_Port_0)
	{	while((AD0DR0&0x80000000) == 0)
			WatchDog();   		//等待转换结束
		AD0CR |= (1<<24);  				   //再次启动一次ADC转换
		while((AD0DR0&0x80000000) == 0)
			WatchDog();   //等待转换结束
		AdcVal=AD0DR0;
	}
	else if(Port==De_Adc_Port_1)
	{	while((AD0DR1&0x80000000) == 0)
			WatchDog();   		//等待转换结束
		AD0CR |= (1<<24);  				   //再次启动一次ADC转换
		while((AD0DR1&0x80000000) == 0)
			WatchDog();   //等待转换结束
		AdcVal=AD0DR1;
	}
	else if(Port==De_Adc_Port_2)
	{	while((AD0DR2&0x80000000) == 0)
			WatchDog();   		//等待转换结束
		AD0CR |= (1<<24);  				   //再次启动一次ADC转换
		while((AD0DR2&0x80000000) == 0)
			WatchDog();   //等待转换结束
		AdcVal=AD0DR2;
	}
	else if(Port==De_Adc_Port_3)
	{	while((AD0DR3&0x80000000) == 0)
			WatchDog();   		//等待转换结束
		AD0CR |= (1<<24);  				   //再次启动一次ADC转换
		while((AD0DR3&0x80000000) == 0)
			WatchDog();   //等待转换结束
		AdcVal=AD0DR3;
	}
	else if(Port==De_Adc_Port_4)
	{	while((AD0DR4&0x80000000) == 0)
			WatchDog();   		//等待转换结束
		AD0CR |= (1<<24);  				   //再次启动一次ADC转换
		while((AD0DR4&0x80000000) == 0)
			WatchDog();   //等待转换结束
		AdcVal=AD0DR4;
	}
	else if(Port==De_Adc_Port_5)
	{	while((AD0DR1&0x80000000) == 0)
			WatchDog();   		//等待转换结束
		AD0CR |= (1<<24);  				   //再次启动一次ADC转换
		while((AD0DR5&0x80000000) == 0)
			WatchDog();   //等待转换结束
		AdcVal=AD0DR5;
	}
	else if(Port==De_Adc_Port_6)
	{	while((AD0DR1&0x80000000) == 0)
			WatchDog();   		//等待转换结束
		AD0CR |= (1<<24);  				   //再次启动一次ADC转换
		while((AD0DR6&0x80000000) == 0)
			WatchDog();   //等待转换结束
		AdcVal=AD0DR6;
	}
	else if(Port==De_Adc_Port_7)
	{	while((AD0DR1&0x80000000) == 0)
			WatchDog();   		//等待转换结束
		AD0CR |= (1<<24);  				   //再次启动一次ADC转换
		while((AD0DR7&0x80000000) == 0)
			WatchDog();   //等待转换结束
		AdcVal=AD0DR7;
	}
   	AdcVal=((AdcVal>>6)&0x3fff);
	AdcVal=AdcVal*CN_st_Data_Adc[i].Modulus;
	AdcVal=AdcVal/1024;
	*Vol=AdcVal;
	 	OSSemPost(AdcSem);
	return De_Suc_Adc;
}

					
