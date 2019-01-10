#define De_Can_Compiler
#include "Can.h"


static uint16 Init(uint8 CanNumber)
{	if(CanNumber==De_Can_Port_0)
	{	
		#ifdef OS_ADD 
		if(Can0UseSem==NULL)             
		{	Can0UseSem=OSSemCreate(1); 					
			if(Can0UseSem == NULL)
				return De_Erro_Can_Init_0;		
		}
		if(Can0RxSem==NULL)
		{	Can0RxSem=OSMboxCreate(0); 					
			if(Can0RxSem == NULL)
				return De_Erro_Can_Init_0;	
		}
		#endif		
	}
	else if(CanNumber==De_Can_Port_1)
	{	
		#ifdef OS_ADD 
		if(Can1UseSem==NULL)             
		{	Can1UseSem=OSSemCreate(1); 					
			if(Can1UseSem == NULL)
				return De_Erro_Can_Init_1;	
		}
		if(Can1RxSem==NULL)			
		{	Can1RxSem=OSMboxCreate(0); 					
			if(Can1RxSem == NULL)
				return De_Erro_Can_Init_1;	
		}
		#endif		
	}
	else 
		return De_Erro_Can_NoPort;
	return De_Suc_Can;
}

static uint16 Open(uint8 CanNumber,uint32 Baud)
{	if(CanNumber==De_Can_Port_0)
		return Open0(Baud);
	else if(CanNumber==De_Can_Port_1)
		return Open1(Baud);
	else 
		return De_Erro_Can_NoPort;
}

static uint16 Close(uint8 CanNumber)
{ 	if(CanNumber==De_Can_Port_0)
		return Close0();
	else if(CanNumber==De_Can_Port_1)
		return Close1();
	else 
		return De_Erro_Can_NoPort;
}
static uint16 Read(uint8 CanNumber,st_Da_CanInfor	*ptst_Da_CanInfor)
{	if(CanNumber==De_Can_Port_0)
		return Read0(ptst_Da_CanInfor);
	else if(CanNumber==De_Can_Port_1)
		return Read1(ptst_Da_CanInfor);
	else 
		return De_Erro_Can_NoPort;
}

static uint16 Write(uint8 CanNumber,st_Da_CanInfor	*ptst_Da_CanInfor)
{	if(CanNumber==De_Can_Port_0)
		return Write0(ptst_Da_CanInfor);
	else if(CanNumber==De_Can_Port_1)
		return Write1(ptst_Da_CanInfor);
	else 
		return De_Erro_Can_NoPort;
}






/*=======================================================Can0==============================================================================*/
static uint16 Open0(uint32 Baud)						//初始化CAN
{	uint8 err;
	CAN1IER =0x00;
	#ifdef OS_ADD
	OSSemPend(Can0UseSem, 0, &err);
	ClearSem(Can0RxSem);					//清空信号量
	#endif
	Can0_RxHead=Can0_RxTail=0;
	PCONP |= 0X00002000;
	PINSEL0	&= ~0X0000000F;
	PINSEL0 |= 0X00000005;
	CAN1MOD = 1;
	CAN_AFMR = 0x02;
	CAN1BTR = Baud;
	CAN1MOD = 0;
	CAN1IER = 1;
	return De_Suc_Can;	
}
static uint16 Close0(void)
{	CAN1IER =0x00;
	#ifdef OS_ADD
	ClearSem(Can0RxSem);					//清空信号量
	#endif
	CAN1IER =0x00;
	PCONP &= ~0X00002000;
	#ifdef OS_ADD
	OSSemPost(Can0UseSem);			//交出使用权
	#endif
	return De_Suc_Can;
}

static uint16 Write0(st_Da_CanInfor	*ptst_Da_CanInfor)
{	uint32 timeout = 0;
	while (!(CAN1SR&0x00000004))				//表示可以发送
	{	timeout ++;
		WatchDog(); 					//时间会延长100-200ms
		if(timeout == 200000)		   //540ms		  100000 ->  260ms
		{	timeout = 0;
			return 1;
		}
	}
	timeout = 0;
	CAN1TFI1 = ptst_Da_CanInfor->FrameInfor;
	CAN1TID1 = ptst_Da_CanInfor->FrameID;
	CAN1TDA1 = ptst_Da_CanInfor->FrameData[0];
	CAN1TDB1 = ptst_Da_CanInfor->FrameData[1];
	CAN1CMR = 0X00000021;
	return 	De_Suc_Can;

}

static uint16 Read0(st_Da_CanInfor	*ptst_Da_CanInfor)
{	if(Can0_RxHead==Can0_RxTail)				//缓冲区没有数据
		return 0;
	ptst_Da_CanInfor->FrameData[0]=CN_st_Da_CanInfor[Can0_RxHead].FrameData[0];
	ptst_Da_CanInfor->FrameData[1]=CN_st_Da_CanInfor[Can0_RxHead].FrameData[1];
	ptst_Da_CanInfor->FrameInfor=CN_st_Da_CanInfor[Can0_RxHead].FrameInfor;
	ptst_Da_CanInfor->FrameID=CN_st_Da_CanInfor[Can0_RxHead].FrameID;
	Can0_RxHead++;
	if(Can0_RxHead==De_Can_RecMaxSize)
		Can0_RxHead=0;
	return 1;	
}

/*=======================================================Can0==============================================================================*/
static uint16 Open1(uint32 Baud)						//初始化CAN
{	uint8 err;
	CAN2IER =0x00;
	#ifdef OS_ADD
	OSSemPend(Can1UseSem, 0, &err);
	ClearSem(Can1RxSem);					//清空信号量
	#endif
	Can1_RxHead=Can1_RxTail=0;
	PCONP |= 0X00004000;
	PINSEL0	&= ~0X00000F00;
	PINSEL0 |= 0X00000A00;
	
	CAN2MOD = 1;
	CAN_AFMR = 0x02;
	CAN2BTR = Baud;
	CAN2MOD = 0;
	
	CAN2IER = 1;
	return De_Suc_Can;	
}
static uint16 Close1(void)
{	CAN1IER =0x00;
	#ifdef OS_ADD
	ClearSem(Can1RxSem);					//清空信号量
	#endif
	CAN2IER =0x00;
	PCONP &= ~0X00004000;
	#ifdef OS_ADD
	OSSemPost(Can1UseSem);			//交出使用权
	#endif
	return De_Suc_Can;
}

static uint16 Write1(st_Da_CanInfor	*ptst_Da_CanInfor)
{	uint32 timeout = 0;
	while (!(CAN2SR&0x00000004))				//表示可以发送
	{	timeout ++; 
		if(timeout == 200000)		   //540ms		  100000 ->  260ms
		{	timeout = 0;
			return 1;
		}
	}
	timeout = 0;
	CAN2TFI1 = ptst_Da_CanInfor->FrameInfor;
	CAN2TID1 = ptst_Da_CanInfor->FrameID;
	CAN2TDA1 = ptst_Da_CanInfor->FrameData[0];
	CAN2TDB1 = ptst_Da_CanInfor->FrameData[1];
	CAN2CMR = 0X00000021;
	return 	De_Suc_Can;
}

static uint16 Read1(st_Da_CanInfor	*ptst_Da_CanInfor)
{	if(Can1_RxHead==Can1_RxTail)				//缓冲区没有数据
		return 0;
	ptst_Da_CanInfor->FrameData[0]=CN_st_Da_CanInfor1[Can1_RxHead].FrameData[0];
	ptst_Da_CanInfor->FrameData[1]=CN_st_Da_CanInfor1[Can1_RxHead].FrameData[1];
	ptst_Da_CanInfor->FrameInfor=CN_st_Da_CanInfor1[Can1_RxHead].FrameInfor;
	ptst_Da_CanInfor->FrameID=CN_st_Da_CanInfor1[Can1_RxHead].FrameID;
	Can1_RxHead++;
	if(Can1_RxHead==De_Can_RecMaxSize)
		Can1_RxHead=0;
	return 1;	
}

static uint16 ClearSem(OS_EVENT	*CanSem)
{	OS_SEM_DATA 	SemData;
	uint8 err;
	for(;;)
	{	if(OSSemQuery(CanSem, &SemData)!=OS_NO_ERR)
			return 1;
		if(SemData.OSCnt == 0)		//有信号要接受
			return De_Suc_Can;	
		OSSemPend(CanSem, 1, &err);
	}
}
/*===============================中断接受函数===============================================*/
void CAN_Exception (void)
{	uint32 CANSTATUS;
	CANSTATUS = CAN_RX_SR;
	
	if (CANSTATUS&0X00000100) 						//CAN1接受中断
	{	CN_st_Da_CanInfor[Can0_RxTail].FrameInfor = CAN1RFS;
		CN_st_Da_CanInfor[Can0_RxTail].FrameID = CAN1RID;
		CN_st_Da_CanInfor[Can0_RxTail].FrameData[0] = CAN1RDA;
		CN_st_Da_CanInfor[Can0_RxTail].FrameData[1] = CAN1RDB;	
		Can0_RxTail++;
		if(Can0_RxTail==De_Can_RecMaxSize)
			Can0_RxTail=0;
		OSSemPost(Can0RxSem);
	}
	if (CANSTATUS&0X00000200)					   //CAN2接受中断
	{	CN_st_Da_CanInfor1[Can1_RxTail].FrameInfor = CAN2RFS;
		CN_st_Da_CanInfor1[Can1_RxTail].FrameID = CAN2RID;
		CN_st_Da_CanInfor1[Can1_RxTail].FrameData[0] = CAN2RDA;
		CN_st_Da_CanInfor1[Can1_RxTail].FrameData[1] = CAN2RDB;	
		Can1_RxTail++;
		if(Can1_RxTail==De_Can_RecMaxSize)
			Can1_RxTail=0;
		OSSemPost(Can1RxSem);
	}
	CAN2CMR |= (1<<2);
	VICVectAddr = 0x00;	
}



