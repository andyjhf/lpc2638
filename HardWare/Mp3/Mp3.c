static uint16 Init(void)					//初始化MP3
{				




}

static uint16 Open(uint8 *FileName)
{		





}


static uint16 Close(void)
{





}

#define De_Mp3_Command_FeedBack								1
#define De_Mp3_Command_NoFeedBack							0
#define De_Mp3_Use_Uart										1
static uint16 Command(uint8 CommWord,uint8 *Buf,uint8 SizeofBuf)
{	uint8 Head[4];
	uint8 ByteV;
	Head[0]='$';Head[1]=SizeofBuf+2;
	Head[2]=CommWord;Head[3]=De_Mp3_Command_FeedBack;
	CN_st_Fun_Uart.Write(De_Mp3_Use_Uart,Head,sizeof(Head));		//发送头信息
	CN_st_Fun_Uart.Write(De_Mp3_Use_Uart,Buf,SizeofBuf);			//发送参数		
	ByteV=CN_st_Fun_Arithmetic.CN_st_Fun_CheckAdd->CheckAdd(Head+1,sizeof(Head)-1,0);
	ByteV=CN_st_Fun_Arithmetic.CN_st_Fun_CheckAdd->CheckAdd(Buf,SizeofBuf,ByteV);
    CN_st_Fun_Uart.Write(De_Mp3_Use_Uart,&ByteV,1);				//发送校验和
	if(Head[3]==De_Mp3_Command_NoFeedBack)
		return De_Suc_Mp3;
	for(;;)
	{	






	}
}

static uint16 Command_Result(void)
{	uint16 Result;
	uint8 ByteV,DataLen,ResData,CheckV;
	for(DataLen=0,CheckV=0;;)
	{	Result=CN_st_Fun_Uart.Read(De_Mp3_Use_Uart,&ByteV,1);
		if(Result==0)	
			continue;
		if((Data==0)&&(ByteV=='$'))
		{	DataLen++;
			continue;
		}
		if(DataLen==1)
		{	ResData=ByteV+3;
			DataLen++;
			continue;
		}
		DataLen++;
		if(DataLen>=ResData)
			break;		
	}
}






