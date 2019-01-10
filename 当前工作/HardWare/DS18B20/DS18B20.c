#define De_18B20_Compiler
#include "DS18B20.h"


static uint16 Init(void)
{	
	if(DS18B20Sem!=NULL)
		return De_Suc_18B20;
	if((DS18B20Sem=OSSemCreate(1))==NULL)
		return De_Erro_18B20_NoInit;  	
	return De_Suc_18B20;	
}


static uint16 Open(uint8 port)
{
	uint8 i;
	OSSemPend(DS18B20Sem, 0, &i);
	for(i=0;i<sizeof(CN_Ba_PinDe);i++)
	{	if(CN_Ba_PinDe[i]== port)
			break;
	}
	if(i==sizeof(CN_Ba_PinDe))
	{
		OSSemPost(DS18B20Sem);	
		return De_Erro_18B20_NoPort;	 // 找不到对应的端口
	}  
	if(port == DS18B20_PORT0)
	{
		DS18B20_FunOpen_PORT0;		     // 设置对应的引脚为GPIO功能
	}
	else if(port == DS18B20_PORT1)
	{
		DS18B20_FunOpen_PORT1;
	}
	CN_st_Data_18B20[i].state = De_18B20_Fun_Open;
	OSSemPost(DS18B20Sem);
	return De_Suc_18B20;		 	
}

static uint16 Read(uint8 port,uint32 *value)
{
	uint8 i;
	uint16 result;

	OSSemPend(DS18B20Sem, 0, &i);
	for(i=0;i<sizeof(CN_Ba_PinDe);i++)
	{	if(CN_Ba_PinDe[i]== port)
			break;
	}
	if(i == sizeof(CN_Ba_PinDe))
	{
		OSSemPost(DS18B20Sem);	
		return De_Erro_18B20_NoPort;
	}  
	if(CN_st_Data_18B20[i].state == De_18B20_Fun_Close)
	{
		OSSemPost(DS18B20Sem);	
		return De_Erro_18B20_NoOpen;	
	}
	if(port == DS18B20_PORT0)
	{
		result = DS18B20ReadTemp(value, DS18B20_PIN0) ;	 //读1路的温度值		
	}
	else if(port == DS18B20_PORT1)
	{
		result = DS18B20ReadTemp(value,DS18B20_PIN1);    //读2路的温度值 		
	}
	OSSemPost(DS18B20Sem);	
	return result;	
}
static uint16 Close(uint8 port)
{
	uint8 i;
	OSSemPend(DS18B20Sem, 0, &i);
	for(i=0;i<sizeof(CN_Ba_PinDe);i++)
	{	if(CN_Ba_PinDe[i]== port)
			break;
	}
	if(i==sizeof(CN_Ba_PinDe))
	{
		OSSemPost(DS18B20Sem);	
		return De_Erro_18B20_NoPort;
	}  
   	CN_st_Data_18B20[i].state = De_18B20_Fun_Close;
	OSSemPost(DS18B20Sem);
	return De_Suc_18B20;	
}


/*********************************底层硬件驱动*************************************/

static void delay_10us(uint32 time)    //10微秒延时
{
	uint32 i;
	for(;time>0;time--)
	{
	   for(i=84;i>0;i--);
	}
}

static void delay_1us(uint32 time)    //1微秒延时
{
	uint32 i;
	for(;time>0;time--)
	{
	   for(i=4;i>0;i--);  	  
	}
}	 


//DS18B20复位和存在脉冲
static uint16 DS18B20Reset(uint8 PinNum)
{  
	uint8 result;
	result = De_Suc_18B20;
	OS_ENTER_CRITICAL();   	
	DS18B20_Port_Out(PinNum);	// 输出高电平
	DS18B20_Out_High(PinNum);  
	delay_10us(5);	 
	DS18B20_Out_Low(PinNum);    //置低，初始化开始
	delay_10us(70);
	DS18B20_Out_High(PinNum);   //总线拉高
	delay_10us(2);
	DS18B20_Port_In(PinNum); 	//释放总线
	delay_10us(3);	 	
	if (DS18B20_Pin_Value(PinNum))		 //如果器件在位,该脚为高电平
		result = De_Erro_18B20_NOPRESENCE;	 	
	OS_EXIT_CRITICAL();	  	
	return result;
}


static  uint16 DS18B20ReadBit(uint8 PinNum)
{
	uint8 bit = 0;	 	
	DS18B20_Port_Out(PinNum);	// 输出高电平
	DS18B20_Out_High(PinNum); 
	delay_1us(20);
	DS18B20_Out_Low(PinNum);   	
	delay_1us(10);
	DS18B20_Port_In(PinNum);  	//设置为输入读取位状态
	delay_1us(9);		
	if (DS18B20_Pin_Value(PinNum))
		bit = 1;  
	DS18B20_Port_Out(PinNum);	// 上拉到高电平
	DS18B20_Out_High(PinNum); 
	DS18B20_Port_In(PinNum);  	
	return bit;
}

static void DS18B20WriteBit(uint8 bit,uint8 PinNum)
{
	DS18B20_Port_Out(PinNum);	// 上拉到高电平
	DS18B20_Out_High(PinNum); 
	delay_10us(12);
	DS18B20_Out_Low(PinNum);   	
	if (bit)				 //写高电平
		delay_1us(10);
	else					 //写低电平延时长点
		delay_1us(70);
	DS18B20_Out_High(PinNum); 	
	if (bit)
		delay_1us(64);
	else
		delay_1us(10);
	DS18B20_Port_In(PinNum);  
	delay_1us(10);
}

static uint16 DS18B20ReadByte(uint8 PinNum)
{
	uint8 i;
	uint8 byte = 0;	 
	OS_ENTER_CRITICAL();   	
	for(i=0;i<8;i++)
	{
		if (DS18B20ReadBit(PinNum))
			byte |= 0x01<<i;  
		delay_1us(1);
	}

	OS_EXIT_CRITICAL();   
	return byte;
} 

static void DS18B20WriteByte(uint8 byte,uint8 PinNum)
{
	uint8 i;	
	OS_ENTER_CRITICAL(); 	
	for(i=0;i<8;i++)
	{
		DS18B20WriteBit((byte>>i) & 0x01,PinNum);		
		delay_1us(1);
	}
	OS_EXIT_CRITICAL(); 
}
 

static uint8 DS18B20crc8(uint8 *s,uint16 len,uint8 value)
{
	uint16 i;
	uint8 crc;
	crc = value;		
	for(i=0;i<len;i++)
	{
		crc = crc8_table[crc^(*(s++))];		
	} 
	 return crc;
}

static uint16 DS18B20ReadTemp(uint32 *value,uint8 PinNum)
{
   	uint8 i;
	uint16 result;
	uint16 crc;
	uint32 tempv = 0;
	uint8 buf[9]; 

	result = DS18B20Reset(PinNum);	
	if(result != De_Suc_18B20)
	{
		return result;
	}

	DS18B20WriteByte(DS18B20_SKIP_ROM,PinNum); ;   //跳过读序列号的操作
	DS18B20WriteByte(DS18B20_CONVERT_TEMP,PinNum); //启动一次温度转换    
	delay_10us(60);	 
		
	result = DS18B20Reset(PinNum);	
	if(result != De_Suc_18B20)
	{
		return result;
	}	
	DS18B20WriteByte(DS18B20_SKIP_ROM,PinNum); ;   //跳过读序列号的操作
	DS18B20WriteByte(DS18B20_READ_SCRATCHPAD,PinNum); //读暂存寄存器的值
	for(i=0;i<9;i++)
	{
		buf[i] = DS18B20ReadByte(PinNum);	
	}  
	DS18B20Reset(PinNum);	   
	crc = DS18B20crc8(buf,8,0);
	if(crc != buf[8])
	{			
		 return De_Erro_18B20_CRC;
	}
	*value = 0;	 	
	if(!(buf[1]&0x80))	   // 温度为正数;高5位为符号位 00000 111 11010000 /07D0H	+125 
	{
		tempv = ((uint32)buf[1]<<8)+buf[0];   	
		tempv *= 100; // 保留两位小数
		tempv >>=4;   // 乘以0.0625
		*value = (uint32)tempv;
	}
	else			       // 温度为负数;高5位为符号位 11111 100 10010000 /FC90H	 -55
 
	{
		tempv = ((uint32)buf[1]<<8)+buf[0]; 	
		tempv = ((~tempv)& 0x0000ffff) + 1;			   
		tempv *= 100; 						// 保留两位小数
		tempv >>=4;   						// 乘以0.0625	
		tempv = ~(tempv-1)	;   			// 转换成 32bit补码
		*value = tempv;
	}
	return De_Suc_18B20;	
} 





