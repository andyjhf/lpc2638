#define De_Photo_Compiler
#include "Photo.h"

static uint16 Init(void)
{	uint16 Result;
	Result=CN_st_Fun_Uart.Init(De_Photo_Use_Uart);
	if(Result!=De_Suc_Uart)
		return Result;
	CN_st_Fun_AscNumber.ClsArray(&CN_st_Photo_Property,sizeof(st_Photo_Property));
	CN_st_Photo_Property.PerBagLength = De_Max_Bag_Length;
	Photo_Q = OSQCreate(&VidBox[0],MAX_MESSAGES);
	if(Photo_Q==NULL)
		return De_Erro_Photo_CreateQ;
	OSTaskCreate(Task,(void *)0, &PhotoTaskStk[De_Photo_Stk - 1],De_Photo_Task);	
	return De_Suc_Photo;
}
static uint16 Open(void)
{	uint16 Result;
	const st_Da_Uart	CN_st_Da_Uart={115200,8,1,0};
	Result=CN_st_Fun_Uart.Open(De_Photo_Use_Uart,(st_Da_Uart	*)&CN_st_Da_Uart);
	if(Result!=De_Suc_Uart)
		return Result;
	return De_Suc_Photo;
}
static uint16 Close(void)
{	uint16 Result;
	Result=CN_st_Fun_Uart.Close(De_Photo_Use_Uart);
	if(Result!=De_Suc_Uart)
		return Result;
	return De_Suc_Photo;
}
static void Task(void *pdata)
{	uint8 err;
	uint16 Result;
	pdata=pdata;
	for(;;)
	{	WatchDog();
		ptst_BoxData_Vid = OSQPend(Photo_Q,0,&err);
		if(ptst_BoxData_Vid->Command == De_BoxData_Vid_Command_State)
			Result=De_Suc_Photo;
		else
		{	Result=Photo(ptst_BoxData_Vid,&CN_st_Photo_Property,PhotoBuf,De_Max_Ram);
		}
		ptst_BoxData_Vid->Result = Result;
		OSMboxPost(ptst_BoxData_Vid->ReBox,&ptst_BoxData_Vid->Result);
		OSTimeDly(De_Photo_TaskDly);
	}
	
}
static uint16 Photo(st_BoxData_Vid *ptst_BoxData_Vid,st_Photo_Property *ptst_Photo_Property,uint8 *AgreeBuf,uint16 SizeofAgreeBuf)
{	uint16 Result,ReLength1,ReLength=0;
	uint16 i;
	st_File_Photo_Tail CN_st_File_Photo_Tail;
	st_File_Photo_Data CN_st_File_Photo_Data;
	Result=PhotoCommon(ptst_BoxData_Vid->PhotoType,ptst_Photo_Property);
	if(Result!=De_Suc_Photo)
		return Result;
	CN_st_Fun_File.ReadHeadTail(ptst_BoxData_Vid->DataFd,&CN_st_File_Photo_Tail.FrontTail,De_rwFile_Point_Tail); //读上一文件的尾指针
	for(i=1;i<=ptst_Photo_Property->BagNum;i++)
	{	Result=ReadPhoto(i,AgreeBuf,SizeofAgreeBuf,&ReLength1);								   //获取照片数据包
		if(Result!=De_Suc_Photo)
			return Result;
		CN_st_File_Photo_Data.BagNumber=ptst_Photo_Property->BagNum-i;
		CN_st_File_Photo_Data.DataLength=ReLength1;
		CN_st_Fun_AscNumber.MoveByte(CN_st_File_Photo_Data.Data,AgreeBuf,ReLength1);
		CN_st_Fun_File.WriteRecoder(ptst_BoxData_Vid->DataFd,0,&CN_st_File_Photo_Data);		   //存储照片数据包
		ReLength+=ReLength1;		
	}
	if(ReLength!=ptst_Photo_Property->PhotoSize)
		return De_Erro_Photo_Data;
	CN_st_Fun_File.ReadHeadTail(ptst_BoxData_Vid->DataFd,&CN_st_File_Photo_Tail.CurrentTail,De_rwFile_Point_Tail);//读当前文件尾指针
	CN_st_Fun_File.WriteRecoder(ptst_BoxData_Vid->TailFd,0,&CN_st_File_Photo_Tail);				//存储照片指针
	return De_Suc_Photo;
}
static uint16 PhotoCommon(uint8 PhotoSize,st_Photo_Property *ptst_Photo_Property)
{	uint8 Buf[30],Buf1[10],*Temp;
	uint16 DataLength;
	CN_st_Fun_AscNumber.ClsArray(Buf,sizeof(Buf));
	CN_st_Fun_AscNumber.ClsArray(Buf1,sizeof(Buf1));
	Buf1[0] = 'U';Buf1[1] = 'H';Buf1[2] = PhotoSize;
	Buf1[3] = ptst_Photo_Property->PerBagLength%256;
	Buf1[4] = ptst_Photo_Property->PerBagLength/256;
	Buf1[5] = '#';
	CN_st_Fun_Uart.Write(De_Photo_Use_Uart,Buf1,6);
	OSTimeDly(600);
	DataLength = CN_st_Fun_Uart.Read(De_Photo_Use_Uart,Buf,30);
	if((Temp=CN_st_Fun_AscNumber.LookBufInLength("UH#",3,Buf,DataLength))==NULL)
		return De_Erro_Photo_Common;
	Temp+=3;
	if((Temp=CN_st_Fun_AscNumber.LookBufInLength("#",1,Temp,DataLength-3))==NULL)
		return De_Erro_Photo_Common;
	if((Temp=CN_st_Fun_AscNumber.LookBufInLength("UR",2,Buf,DataLength))==NULL)
		return De_Erro_Photo_Common;
	Temp+=2;
	ptst_Photo_Property->PhotoSize=*Temp+(*(Temp+1)<<8);
	Temp+=2;
	ptst_Photo_Property->BagNum=*Temp+(*(Temp+1)<<8);
	return De_Suc_Photo;

}
static uint16 ReadPhoto(uint16 Num,uint8 *AgreeBuf,uint16 SizeofAgreeBuf,uint16 *DataLength)
{	uint8 Buf[10],*Temp,*Temp1;
	uint16 ReLength,CrcTemp;

	CN_st_Fun_AscNumber.ClsArray(AgreeBuf,SizeofAgreeBuf);
	CN_st_Fun_AscNumber.ClsArray(Buf,sizeof(Buf));
	Buf[0]='U';Buf[1]='E';Buf[2]=Num%256;
	Buf[3]=Num/256;Buf[4]='#';
	CN_st_Fun_Uart.Write(De_Photo_Use_Uart,Buf,5);
	OSTimeDly(40);
	ReLength=CN_st_Fun_Uart.Read(De_Photo_Use_Uart,AgreeBuf,SizeofAgreeBuf);
	if((Temp=CN_st_Fun_AscNumber.LookBufInLength("UE#",3,AgreeBuf,ReLength))==NULL)
		return De_Erro_Photo_Data;
	Temp=Temp+3;
	if((Temp1=CN_st_Fun_AscNumber.LookBufInLength("UF",2,Temp,ReLength-3))==NULL)
		return De_Erro_Photo_Data;
	Temp=Temp1;
	Temp+=2;
	if((*Temp+(*(Temp+1)<<8))!=Num)
		return De_Erro_Photo_Data;
	Temp+=2;
	*DataLength=*Temp+(*(Temp+1)<<8);
	CrcTemp=CheckSum(Temp1,*DataLength+6);
	if(CrcTemp!=((*(Temp1+*DataLength+7)<<8)+*(Temp1+*DataLength+6)))
		return De_Erro_Photo_Data;	
	Temp+=2;
	CN_st_Fun_AscNumber.MoveByte(AgreeBuf,Temp,*DataLength);
	return De_Suc_Photo;
}
static uint16 CheckSum(uint8 *s,uint16 len)                                               //16位的CRC校验       
{	uint16 i,Result=0;   
	for(i=0;i<len;i++)
	{	Result = Result+s[i];
	}
	return Result;
			                  
}




