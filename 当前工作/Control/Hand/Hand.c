#define De_Hand_Compiler
#include "Hand.h"
static uint16 Init(void)						//初始化
{	st_Da_Uart	CN_st_Da_Uart1={9600,8,1,0};
	CN_st_Fun_Uart.Init(De_Hand_Use_Uart);
	CN_st_Fun_Uart.Open(De_Hand_Use_Uart,&CN_st_Da_Uart1);
	CN_st_Fun_AscNumber.ClsArray(&CN_st_Control_Hand,sizeof(st_Control_Hand));
	HandSem=OSSemCreate(1);							//创建一个信号量
	OSTaskCreate (Task,(void *)0, &Hand_Stk[De_Stk_Hand - 1],De_Task_Hand);
	return De_Suc_Hand;
}


static uint16 Open(st_Affair_Hand	*ptst_Affair_Hand)
{	uint8 err;
	OSSemPend(HandSem, 0, &err);
	CN_st_Control_Hand.CN_st_Affair_Hand.ptFun=ptst_Affair_Hand->ptFun;
	CN_st_Control_Hand.State=De_Hand_Affair_State_Open;
	OSSemPost(HandSem);
	return De_Suc_Hand;
}
static uint16 Close(void)
{	uint8 err;
	OSSemPend(HandSem, 0, &err);
	CN_st_Control_Hand.State=De_Hand_Affair_State_Close;
	OSSemPost(HandSem);
	return De_Suc_Hand;
}

static void Task(void *pData)  					//任务调度
{	uint8 Buf[100];
	uint16 Result;
	uint8 DataLen,*pTemp1,err;
	
	pData=pData;

	for(DataLen=0;;OSSemPost(HandSem),OSTimeDly(De_Hand_TaskDly))
	{	//CN_st_Fun_Uart.Write(0,"hand",4);
		WatchDog();
		OSSemPend(HandSem, 0, &err);
		De_Hand_HardWareIO_CTS_Input;
		if(De_Hand_HardWareIO_CTS_Data==De_Hand_CTS_High)
			continue;
		                                                                           
		//De_Hand_CTS_High;
		Result=ReadData(Buf+DataLen,sizeof(Buf)-DataLen);
		if(Result==0)
			continue;
		//if(De_Hand_HardWareIO_CTS_Data==De_Hand_CTS_Low)
		//	continue;
			//De_Hand_HardWareIO_CTS_OutPut;
			//De_Hand_HardWareIO_CTS_OutPut_Low;

		//CN_st_Fun_Uart.Write(0,"start\r\n",7);
		//CN_st_Fun_Uart.Write(0,Buf,Result);
		//CN_st_Fun_Uart.Write(0,"\r\n",2);
		DataLen+=Result;
	   	for(pTemp1=Buf;pTemp1!=NULL;pTemp1++)
		{	if((pTemp1=SeekChar(pTemp1,0x01,DataLen,1))==NULL)
				break;
		 	pTemp1++;
			if(*pTemp1!=0x04)
				continue;
			break;
		}
		if(pTemp1==NULL)
		{	DataLen=0;
			continue;
		}
		pTemp1++;
		DataLen=*pTemp1;
		pTemp1++;
		if((DataLen<2)||(pTemp1[DataLen-1]!=0x0a))
		{	DataLen=0;
			continue;
		}
     //	pTemp1 = [DataLen+3];
		CN_st_Fun_AscNumber.ClsArray(&Buf[DataLen+3] ,97-DataLen);
			//DataLen--;
		if(CN_st_Fun_Arithmetic.ptst_Fun_CheckSum->CheckSum(pTemp1-3,DataLen+1)!=pTemp1[DataLen-2])		//校验不正确
		{	DataLen=0;
			continue;
		}
		DataLen-=2;
		De_Hand_HardWareIO_CTS_OutPut;
		De_Hand_HardWareIO_CTS_OutPut_Low;
		err=0x00;
		U3LCR=0x3b;
		WriteData(&err,sizeof(err));
		De_Hand_HardWareIO_CTS_OutPut;
		De_Hand_HardWareIO_CTS_OutPut_HIGH;
		//while(De_Hand_HardWareIO_CTS_Data==De_Hand_CTS_High);
			
		//De_Hand_HardWareIO_CTS_OutPut;
		//De_Hand_HardWareIO_CTS_OutPut_Low;
		//De_Hand_HardWareIO_CTS_OutPut;
		//De_Hand_HardWareIO_CTS_OutPut_HIGH;
		pTemp1[DataLen]=0;
		if((CN_st_Control_Hand.Enable==De_Hand_Affair_Enable)&&(CN_st_Control_Hand.State==De_Hand_Affair_State_Open)
			&&(CN_st_Control_Hand.CN_st_Affair_Hand.ptFun!=NULL))
		{	OSSemPost(HandSem);
			CN_st_Control_Hand.CN_st_Affair_Hand.ptFun(pTemp1,DataLen);
			OSSemPend(HandSem, 0, &err);
												//发生事件
		}
		DataLen=0;
		CN_st_Fun_AscNumber.ClsArray(Buf,sizeof(Buf));
		while(ReadData(&err,1)==1);
		De_Hand_HardWareIO_CTS_Input;
		
	}
}


static uint16 Enable(void)
{	uint8 err;	 
	OSSemPend(HandSem, 0, &err);
	CN_st_Control_Hand.Enable=De_Hand_Affair_Enable;	
	OSSemPost(HandSem);
	return De_Suc_Hand;
}

static uint16 DisEnable(void)
{	
	uint8 err;	 
	OSSemPend(HandSem, 0, &err);
	CN_st_Control_Hand.Enable=De_Hand_Affair_DisEnable;	
	OSSemPost(HandSem);
	return De_Suc_Hand;
}

static uint16 GetEnable(uint8 *State)
{	uint8 err;	 
	OSSemPend(HandSem, 0, &err);
	*State=CN_st_Control_Hand.Enable;
	OSSemPost(HandSem);
	return De_Suc_Hand;
}

static uint16 LCDputLine(uint8 *Dat)
{	uint8 Buf[200];
	uint8 DataLen;
	//OSSemPend(HandSem, 0, &err);
	//while(De_Hand_HardWareIO_CTS_Data==De_Hand_CTS_Low);
	De_Hand_HardWareIO_CTS_OutPut;
		De_Hand_HardWareIO_CTS_OutPut_Low;
	DataLen=CN_st_Fun_AscNumber.Strsize(Dat);
	Buf[0]=0x04;Buf[1]=0x01;
	Buf[2]=DataLen+3;Buf[3]=0x06;
	CN_st_Fun_AscNumber.MoveByte(Buf+4,Dat,DataLen);
	DataLen=DataLen+4;
	Buf[DataLen]=CN_st_Fun_Arithmetic.ptst_Fun_CheckSum->CheckSum(Buf,DataLen);
	DataLen++;
	Buf[DataLen]=0x0a;
   	DataLen++;
	U3LCR=0x2b;
	WriteData(Buf,1);
	U3LCR=0x3b;
	WriteData(Buf+1,DataLen-1);

	//OSSemPost(HandSem);
	
	return De_Suc_Hand;
}

static uint16 RegLine(uint8 *Dat,uint8 DataLen)			//发送登录命令
{	uint8 Buf[200];
//	uint8 err;
  // 	OSSemPend(HandSem, 0, &err);
  De_Hand_HardWareIO_CTS_OutPut;
		De_Hand_HardWareIO_CTS_OutPut_Low;
	Buf[0]=0x04;Buf[1]=0x01;
	Buf[2]=DataLen+3;Buf[3]=0x02;
	CN_st_Fun_AscNumber.MoveByte(Buf+4,Dat,DataLen);
	DataLen=DataLen+4;
	Buf[DataLen]=CN_st_Fun_Arithmetic.ptst_Fun_CheckSum->CheckSum(Buf,DataLen);
	DataLen++;
	Buf[DataLen]=0x0a;
   	DataLen++;
	U3LCR=0x2b;
	WriteData(Buf,1);
	U3LCR=0x3b;
	WriteData(Buf+1,DataLen-1);
	//OSSemPost(HandSem);
	
	return De_Suc_Hand;
}

static uint16 GsmLine(uint8 *Dat,uint8 DataLen)			//GSM数据
{ 	uint8 Buf[200];
//	uint8 err;
	De_Hand_HardWareIO_CTS_OutPut;
		De_Hand_HardWareIO_CTS_OutPut_Low;
   	//OSSemPend(HandSem, 0, &err);
	Buf[0]=0x02;Buf[1]=0x01;
	Buf[2]=DataLen+3;Buf[3]=0x01;
	CN_st_Fun_AscNumber.MoveByte(Buf+4,Dat,DataLen);
	DataLen=DataLen+4;
	Buf[DataLen]=CN_st_Fun_Arithmetic.ptst_Fun_CheckSum->CheckSum(Buf,DataLen);
	DataLen++;
	Buf[DataLen]=0x0a;
   	DataLen++;
	U3LCR=0x2b;
	WriteData(Buf,1);
	U3LCR=0x3b;
	WriteData(Buf+1,DataLen-1);
	//OSSemPost(HandSem);
	
	return De_Suc_Hand;
}

static uint16 GpsLine(uint8 *Dat,uint8 DataLen)			//Gps数据
{ 	uint8 Buf[200];
//	uint8 err;
   //	OSSemPend(HandSem, 0, &err);
   De_Hand_HardWareIO_CTS_OutPut;
		De_Hand_HardWareIO_CTS_OutPut_Low;
	Buf[0]=0x03;Buf[1]=0x01;
	Buf[2]=DataLen+3;Buf[3]=0x01;
	CN_st_Fun_AscNumber.MoveByte(Buf+4,Dat,DataLen);
	DataLen=DataLen+4;
	Buf[DataLen]=CN_st_Fun_Arithmetic.ptst_Fun_CheckSum->CheckSum(Buf,DataLen);
	DataLen++;
	Buf[DataLen]=0x0a;
   	DataLen++;
	U3LCR=0x2b;
	WriteData(Buf,1);
	U3LCR=0x3b;
	WriteData(Buf+1,DataLen-1);
	//OSSemPost(HandSem);
	
	return De_Suc_Hand;
}











/*==========================================底层支持函数======================================================*/

/*static uint16 ReadData(uint8 *Buf,uint16 ReadLen)
{	De_Hand_HardWareIO_CTS_Input;							//将
	if(De_Hand_HardWareIO_CTS_Data==De_Hand_CTS_Low)   			//如果当前状态为低代表还在发送字符
		return 0;
	return CN_st_Fun_Uart.Read(De_Hand_Use_Uart,Buf,ReadLen);
}  */
static uint16 ReadData(uint8 *Buf,uint16 ReadLen)
{  
   
   return CN_st_Fun_Uart.Read(De_Hand_Use_Uart,Buf,ReadLen);
    	//err=0x00;
		//U3LCR=0x3b;
		//WriteData(&err,sizeof(err)); 
}			


static uint16 WriteData(uint8 *Buf,uint16 WriteLen)
{	//De_Hand_HardWareIO_CTS_Input;
//	while(De_Hand_HardWareIO_CTS_Data==De_Hand_CTS_Low);			//等待低电平后发送数据
	//De_Hand_HardWareIO_CTS_OutPut;
	//De_Hand_HardWareIO_CTS_OutPut_Low;
	CN_st_Fun_Uart.Write(De_Hand_Use_Uart,Buf,WriteLen);
	//De_Hand_HardWareIO_CTS_Input;
	return De_Suc_Hand;
}


static	uint8 *SeekChar(uint8 *Buf,uint8 CharV,uint8 SizeofBuf,uint8 Number) 	   
{	uint8 i,j;
	for(i=0,j=0;i<SizeofBuf;i++)
	{	if(Buf[i]!=CharV)
			continue;
		j++;
		if(j<Number)		
			continue;
		return Buf+i;
	}
	return NULL;
}




