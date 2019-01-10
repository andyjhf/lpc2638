#define 	De_AscNumber_Compiler
#include 	"AscNumber.h"
#ifdef De_Compiler_miscellaneous_AscNumber
/*======================================码制转换函数===================================================*/		

static void Asc2Bcd(uint8 *Asc,uint8 *BCD,uint8 SizeofAsc)	 //ASC
{	uint8 i;
	for(i=0;i<SizeofAsc;i+=2)
		BCD[i/2]=((Asc[i]-'0')<<4)+((Asc[i+1]-'0')&0x0f);
}

static void Bcd2Asc(uint8 *Bcd,uint8 *Asc,uint8 SizeofBcd)
{	uint8 i;
	for(i=0;i<SizeofBcd;i++)
	{	Asc[i*2]=((Bcd[i]>>4)&0x0f)+'0';
		Asc[i*2+1]=(Bcd[i]&0x0f)+'0';
	}
}

static uint32 Asc2Algorism(uint8 *Asc,uint8 SizeofAsc)
{	uint32 AlgorismValue,Hex;
	uint8 i,j,k;
	for(i=1,AlgorismValue=0,Hex=1;i<=SizeofAsc;i++)
	{	k=Asc[SizeofAsc-i]-'0';
		for(j=0;j<k;j++)
			AlgorismValue+=Hex;
		Hex=(Hex<<3)+(Hex<<1);
	}
	return AlgorismValue;
}

static uint8 Algorism2Asc(uint32 Algorism,uint8 *Asc)
{	uint8 i,j,flag,h;
	uint32 Hex=1000000000;
	if(Algorism==0)
	{	Asc[0]='0';
		return 1;
	}
	for(i=0,flag=0,h=0;i<10;i++)
	{	j=Algorism/Hex;
		if(!((j==0)&&(flag==0))) 
		{	Asc[h++]=j+'0';
			flag=1;
			if(Algorism>=Hex)
         		Algorism=Algorism-Hex*j;
		} 
	   	Hex=Hex/10;
	}
	return h;
}

static void Asc2HexBuf(uint8 *Asc,uint8 *Hex,uint16 SizeofAsc)
{	uint16 i;
	for(i=0;i<SizeofAsc;i+=2)
	{	Hex[i/2]=((Asc2HexSig(Asc[i])<<4)&0xf0);
		Hex[i/2]+=(Asc2HexSig(Asc[i+1])&0x0f);	
	}
}

static void HexBuf2Asc(uint8 *Hex,uint8 *Asc,uint8 SizeofHex)
{	uint8 i;
	for(i=0;i<SizeofHex;i++)
	{	Asc[(uint16 )i*2]=Hex2AscSig((Hex[i]>>4)&0x0f);
		Asc[(uint16 )i*2+1]=Hex2AscSig(Hex[i]&0x0f);	
	}
}

static uint32 Asc2Hex(uint8 *Asc,uint8 SizeofAsc)
{	uint8 Hex[8];
	uint32 HexV,Hexj;
	uint8 i;
	Asc2HexBuf(Asc,Hex,SizeofAsc);
	for(i=SizeofAsc/2,HexV=0,Hexj=1;i>0;i--)
	{ 	HexV+=Hex[i-1]*Hexj;
		Hexj=(Hexj<<8);
	}
   	return HexV;
}

static uint8 Hex2Asc(uint32 Hex,uint8 *Asc)
{	uint8 i,flag,Byte,j;
	if(Hex==0)
	{	Asc[0]='0';
		Asc[1]='0';
		return 2;
	}
	for(i=0,flag=0,j=0;i<4;i++)
	{	Byte=((Hex>>((3-i)*8))&0xff);
		if((Byte==0)&&(flag!=0))
		{	Asc[j++]='0';
			Asc[j++]='0';	
		}
		else if(Byte!=0)
		{	Asc[j++]=Hex2AscSig((Byte>>4)&0x0f);
			Asc[j++]=Hex2AscSig(Byte&0x0f);
			flag=1;
		}
	}
	return j;
}

static void Bcd2Hex(uint8 *BcdBuf,uint8 *HexBuf,uint8 SizeofBcdBuf)
{     uint8 i,Byte;
      for(i=0;i<SizeofBcdBuf;i++)
      {     Byte=(BcdBuf[i]>>4)*10+(BcdBuf[i]&0x0f);
            HexBuf[i]=Byte;
      }       
}

static uint8 Hex2Bcd(uint8 *HexBuf,uint8 *BcdBuf,uint8 SizeofHexBuf)
{     uint8 i;
      for(i=0;i<SizeofHexBuf;i++)
      {     if(HexBuf[i]>99)
                  return 1;
            BcdBuf[i]=(HexBuf[i]%10)+((HexBuf[i]/10)<<4);  
      }
      return 0;
}


/*=========================================判断函数=========================================================*/
static uint16 JugeAscBcd(uint8 *Asc,uint8 SizeofAsc)
{	uint8 i;
	for(i=0;i<SizeofAsc;i++)
	{	if((Asc[i]<'0')||(Asc[i]>'9'))
			return 1;
	}
	return 0;
}

static uint16 JugeHexBcd(uint8 *Hex,uint8 SizeofHex)
{	uint8 i;
	for(i=0;i<SizeofHex;i++)
	{	if(((Hex[i]&0x0f)>0x09)||(((Hex[i]>>4)&0x0f)>0x09))
			return 1;
	}
	return 0;



}



static uint16 JugeAscHex(uint8 *Asc,uint8 SizeofAsc)
{	uint8 i;
	for(i=0;i<SizeofAsc;i++)
	{	if((Asc[i]>='0')&&(Asc[i]<='9'))
			continue;
		if((Asc[i]>='a')&&(Asc[i]<='f'))
			continue;
		if((Asc[i]>='A')&&(Asc[i]<='F'))
			continue;			
		return 1;
	}
	return 0;
}



static uint8 Asc2HexSig(uint8 Asc)
{ 	if((Asc>='0')&&(Asc<='9'))
		return 	Asc-'0';
	else if((Asc>='A')&&(Asc<='F'))
		return Asc-'A'+0x0a;
	else if((Asc>='a')&&(Asc<='f'))
		return Asc-'a'+0x0a;
	return 0;
}



static uint8 Hex2AscSig(uint8 Hex)
{	if(Hex<0x0a)
		return Hex+'0';
	else if(Hex<0x10)
		return Hex-0x0a+'A';
	else
		return '0';
}


static uint32 Asc2Float(uint8 *Asc,uint8 FixPoint,uint8 SizeofAsc)	//ASC到定点浮点数
{	uint32 IntValue,PointValue;
	uint8 IntNumber,PointNumber;
	uint8 *AmountBuf;
	AmountBuf=memchr(Asc,'.',SizeofAsc);
	if(AmountBuf==NULL)
	{	IntNumber=SizeofAsc;
	 	PointNumber=0;
	}
	else
	{	IntNumber=AmountBuf-Asc;
		PointNumber=SizeofAsc-IntNumber-1;		
	}
	if(PointNumber>FixPoint)
		PointNumber=FixPoint;
	IntValue=Asc2Algorism(Asc,IntNumber);
	PointValue=0;
	if(PointNumber!=0)
		PointValue=Asc2Algorism(Asc+IntNumber+1,PointNumber);
	IntValue=IntValue*FixPointValue[FixPoint];
	return IntValue+PointValue;
}

static uint16 JugeAscFloat(uint8 *Asc,uint8 SizeofAsc)
{	uint8 i,PointNumber;
	for(i=0,PointNumber=0;i<SizeofAsc;i++)
	{	if(Asc[i]=='.')
		{	PointNumber++;	
			continue;
		}
		if((Asc[i]>'9')||(Asc[i]<'0'))
			return 1;
	}
	if(PointNumber>1)
		return 2;
	return 0;
}







/*=========================================内存函数====================================================*/
static void ClsArray(void *Buf,uint16 SizeofBuf)
{	uint8 *pData;
	uint16 i;
	pData=Buf;
	for(i=0;i<SizeofBuf;i++)
		pData[i]=0;
}

static void MoveByte(void *Aim,void *Fountain,uint16 SizeofBuf)
{	uint8 *AimByte,*FountainByte;
	uint16 i;
	AimByte=Aim;FountainByte=Fountain;
	for(i=0;i<SizeofBuf;i++)
		AimByte[i]=FountainByte[i];
}

static uint16 CompareBuf(void *Buf1,void *Buf2,uint32 SizeofBuf)
{	uint8 *Buf1Byte,*Buf2Byte;
	uint16 i;
	Buf1Byte=Buf1;Buf2Byte=Buf2;
	for(i=0;i<SizeofBuf;i++)
	{	if(Buf1Byte[i]!=Buf2Byte[i])
			return 1;
	}
	return 0;
}

static uint16 CompareVa(uint8 *Big,uint8 *Small,uint8 SizeofBuf,uint8 Type)
{	uint8 i;
	if(Type==De_AscNumber_Va_Big)
	{	for(i=0;i<SizeofBuf;i++)
		{	if(Big[i]==Small[i])
				continue;	
			if(Big[i]>Small[i])	  
				return	De_AscNumber_Va_True;
			else
				return  De_AscNumber_Va_Flase;	 
		}
		return De_AscNumber_Va_Equality;
	}
	for(i=SizeofBuf;i>0;i--)
	{	if(Big[i-1]==Small[i-1])
			continue;
		if(Big[i]>Small[i])	  
			return	De_AscNumber_Va_True;
		else
			return  De_AscNumber_Va_Flase;
	}
	return De_AscNumber_Va_Equality;
}

static uint8 StrATChar(uint8 *Buf)						//查找以0D0A作为结束的字符
{	uint16 i,DataLen;
	DataLen=Strsize(Buf);
	for(i=0;i<DataLen;i++)
	{	if((Buf[i]==0x0d)&&(Buf[i+1]==0x0a))
			break;
	}
	return i;
}

static uint8 Strsize(uint8 *Buf)
{	uint8 i;
	for(i=0;i<200;i++)
	{	if(Buf[i]==0)
			break;
	}
	return i;
}

static uint16 Strsize16(uint8 *Buf)
{	uint16 i;
	for(i=0;i<6000;i++)
	{	if(Buf[i]==0)
			break;
	}
	return i;



}

static uint8 *LookStr(uint8 *LookString,uint8 *Buf)
{	uint16 i,DataLen,DataLen1,j;
	DataLen=Strsize16(Buf);
	DataLen1=Strsize16(LookString);
	if(DataLen1==0)
		return NULL;
	for(i=0;i<DataLen;i++)
	{	for(j=0;j<DataLen1;j++)
		{	if(Buf[i+j]!=LookString[j])
				break;
		}
		if(j==DataLen1)
			return Buf+i;
	}
	return NULL;
}
static uint8 *LookStrInLength(uint8 *LookString,uint8 *Buf,uint16 DataLength)
{	uint16 i,DataLen1,j;
//	DataLen=Strsize(Buf);
	DataLen1=Strsize(LookString);
	if(DataLength==0)
		return NULL;
	for(i=0;i<DataLength;i++)
	{	for(j=0;j<DataLen1;j++)
		{	if(Buf[i+j]!=LookString[j])
				break;
		}
		if(j==DataLen1)
			return Buf+i;
	}
	return NULL;
}

static uint8 *LookStrDown(uint8 *LookString,uint8 *Buf)
{	uint16 i,DataLen,DataLen1,a,j;
	DataLen=Strsize(Buf);
	DataLen1=Strsize(LookString);
	if(DataLen1==NULL)
		return NULL;
	for(i=0;i<DataLen;i++)
	{	if((DataLen-i)<DataLen1)
			return NULL;
		a=DataLen-i-DataLen1;
		for(j=0;j<DataLen1;j++)
		{	if(Buf[j+a]!=LookString[j])
		   		break;
		}
		if(j==DataLen1)
			return Buf+a;
	}
	return NULL;	
}




static uint8 *LookEnable(uint8 *Buf,uint8 *EnableBuf,uint8 Number)		//查找有效字符的顶端
{	uint8 *pTemp;
	uint16 i,DataLen,Number1;
	DataLen=Buf-EnableBuf;
	for(i=0,Number1=0;i<DataLen;i++)
	{	pTemp=Buf-i;
		if((*pTemp==0x0a)&&(*(pTemp-1)==0x0d))
		{	Number1++;
		 	if(Number1>Number)
				return pTemp++;
		}		
	}
	if(Number1<Number)
		return NULL;
	return EnableBuf;
}

static uint8 *LookShowChar(uint8 *CharBuf,uint8 *Buf) 				//从后往前找，找到第一个可见字符
{	if(CharBuf<Buf)
		return NULL;
	for(;CharBuf>=Buf;CharBuf--)
	{	if(*CharBuf>' ')
		 	return CharBuf;
	}
	return CharBuf;
}
static uint8 *SeekChar(uint8 *Buf,uint8 CharV,uint16 SizeofBuf,uint8 Number) 	   
{	uint16 i,j;
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
static uint8 *SeekStr(uint8 *Buf,uint8 *CharV,uint16 SizeofBuf,uint8 Number) 	   
{	uint16 j;
	uint8 *Temp;
	Temp=Buf;
	for(j=0;;)
	{	Temp=LookStr(CharV,Temp);
		if(Temp==NULL)
			return NULL;
		j++;
		if(j<Number)
		{	Temp++;	
			continue;
		}
		return Temp;
	}
}

static uint8 MemSpace(uint8 *Buf)
{	uint8 DataLen,i,j;
	DataLen=Strsize(Buf);
	for(i=0,j=0;i<DataLen;i++)
	{	if(Buf[i]>0x20)
		{	Buf[j]=Buf[i];
		 	j++;
		}
	}
	ClsArray(Buf+j,DataLen-j);
	return j;
}
static void IPAsc2INT32(uint8 *Buf,uint32 *Hex)
{	uint8 *temp,*temp1,DataLength,Data;
	*Hex=0;
	temp=LookStr(".",Buf);
	DataLength=temp-Buf;
	Data=Asc2Algorism(Buf,DataLength);
	*Hex=Data<<24;
	temp++;
	temp1=LookStr(".",temp);
	DataLength=temp1-temp;
	Data=Asc2Algorism(temp,DataLength);
	*Hex=*Hex+(Data<<16);
	temp1++;	
	temp=LookStr(".",temp1);
	DataLength=temp-temp1;
	Data=Asc2Algorism(temp1,DataLength);
	*Hex=*Hex+(Data<<8);
	temp++;
	DataLength=Strsize(temp);
	Data=Asc2Algorism(temp,DataLength);
	*Hex=*Hex+Data;
}
static uint16 INT322IPAsc(uint32 Hex,uint8 *Buf)
{	uint32 Data,DataLength,DataLength1;
	Data=(Hex>>24)&0xff;
	DataLength=Algorism2Asc(Data,Buf);
	DataLength1=DataLength;
	Buf[DataLength1]='.';
	DataLength1+=1;
	Data=(Hex>>16)&0xff;
	DataLength=Algorism2Asc(Data,Buf+DataLength1);
	DataLength1=DataLength1+DataLength;
	Buf[DataLength1]='.';
	DataLength1+=1;
	Data=(Hex>>8)&0xff;
	DataLength=Algorism2Asc(Data,Buf+DataLength1);
	DataLength1=DataLength1+DataLength;
	Buf[DataLength1]='.';
	DataLength1+=1;
	Data=Hex&0xff;
	DataLength=Algorism2Asc(Data,Buf+DataLength1);
	DataLength1=DataLength1+DataLength;	
	return DataLength1;		
}
static uint16 JugeBufType(uint8 *Buf)
{	uint8 DataLen,i,Flag;
	DataLen=Strsize(Buf);
	for(i=0,Flag=1;i<DataLen;i++)
	{	if(Buf[i]<0x80)			//ASC字符
			continue;
		if((i+1)==DataLen)
			break;//return 0;
		i++;					//不合法
//		if(!(Buf[i]>=0xa0)&&(Buf[i+1]>=0xa0))
//			return 0;				//不合法
		Flag=2;
	}
	return Flag;			//	1:ASC,2:汉字
}

static uint16 PhoPdu(uint8 *Dat,uint8 *Message,uint8 *Phone,uint8 *Centr)		//
{	uint8 Len,Buf[162];
	uint8 Flag;
	Flag=JugeBufType(Message);
	if(Flag==0)					//含有非法字符
		return 1;
	Len=Strsize(Centr)+2;					//中心号码
	if(Len&0x01)
		Len++;
	Len=(Len>>1);
	Len++;	
	HexBuf2Asc(&Len,Dat,1);					//短信号码长度
	Dat+=2;
	Dat[0]='9';Dat[1]='1'; 					//前面默认'+'
	Dat+=2;
	Dat[0]='6';Dat[1]='8';					//强制在中国
	Dat+=2;
	PduNumber(Centr,Dat,Strsize(Centr));	//中心号码打包
	Dat+=Strsize(Dat);
	Dat[0]='1';Dat[1]='1';					//基本参数
	Dat+=2;
	Dat[0]='0';Dat[1]='0';					//消息基准值
	Dat+=2;

	Len=Strsize(Phone);//+2;					//对方电话号码长度
	HexBuf2Asc(&Len,Dat,1);					
	Dat+=2;
	Dat[0]='8';Dat[1]='1'; 					//前面默认'+'
	Dat+=2;
//	Dat[0]='6';Dat[1]='8';					//强制在中国
//	Dat+=2;
	PduNumber(Phone,Dat,Strsize(Phone));	//电话号码打包
	Dat+=Strsize(Dat);

	Dat[0]='0';Dat[1]='0';					//协议类型，普通GSM
	Dat+=2;
	if(Flag==1)								//普通ASC字符
	{	Dat[0]='0';Dat[1]='0';
		Dat+=2;
		Dat[0]='F';Dat[1]='F';				//有效时间
		Dat+=2;
		Len = Strsize16(Message);
		HexBuf2Asc(&Len,Dat,1);
		Dat+=2;
		Len=gsmEncode7bit(Message,Buf,Strsize16(Message));	 //Len=GSM_AscllToPdu(Message,Dat+2);//
//		MoveByte(Dat+Len+Len,Dat,Len);
		HexBuf2Asc(Buf,Dat,Len);				//转换结束		
//		Dat[2*Len]=0;
	}
	else	 										//汉字编码
	{ 	Dat[0]='0';Dat[1]='8';
		Dat+=2;
		Dat[0]='F';Dat[1]='F';				//有效时间
		Dat+=2;											//江华峰要添加的代码
		Len = Strsize16(Message);
		Len=StrToUni(Message,Buf,Len);
		HexBuf2Asc(&Len,Dat,1);
		Dat+=2;
		HexBuf2Asc(Buf,Dat,Len);											//江华峰要添加的代码
	}
	return 0;
}

static uint16 gsmEncode7bit(const uint8* pSrc, uint8* pDst, uint16 nSrcLength)
{
    uint16 nSrc;        // 源字符串的计数值
    uint16 nDst;        // 目标编码串的计数值
    uint16 nChar;       // 当前正在处理的组内字符字节的序号，范围是0-7
    uint8 nLeft;    // 上一字节残余的数据
    
    // 计数值初始化
    nSrc = 0;
    nDst = 0;
    
    // 将源串每8个字节分为一组，压缩成7个字节
    // 循环该处理过程，直至源串被处理完
    // 如果分组不到8字节，也能正确处理
    while(nSrc<nSrcLength)
    {
        // 取源字符串的计数值的最低3位
        nChar = nSrc & 7;
    
        // 处理源串的每个字节
        if(nChar == 0)
        {
            // 组内第一个字节，只是保存起来，待处理下一个字节时使用
            nLeft = *pSrc;
        }
        else
        {
            // 组内其它字节，将其右边部分与残余数据相加，得到一个目标编码字节
            *pDst = (*pSrc << (8-nChar)) | nLeft;
    
            // 将该字节剩下的左边部分，作为残余数据保存起来
            nLeft = *pSrc >> nChar;
            // 修改目标串的指针和计数值 
			pDst++;
            nDst++; 
        } 
        
        // 修改源串的指针和计数值
        pSrc++; nSrc++;
    }
    if(nSrcLength%8!=0)
	{
		*pDst = nLeft;
		nDst++;	
	}
    // 返回目标串长度
    return nDst; 
}

static void PduNumber(uint8 *Dat,uint8 *PduNum,uint16 SizeofDat)
{ 	uint16 i;
	for(i=0;i<SizeofDat;)
	{	if(i+1<SizeofDat)
			PduNum[i] = Dat[i+1];
		else
			PduNum[i] = 'F';
		PduNum[i+1] = Dat[i];
		i += 2;
	}
}





static uint16 ExpPdu(uint8 *Dat,uint8 *Message,uint8 *Phone,uint8 *Centr)  	//解析PDU数据,只能支持
{	uint8 Len,Len1,i;
	uint8 *pTemp;
	uint8 Flag;
	Asc2HexBuf(Dat,&Len,2);
	pTemp=Dat+Len*2+2;													//短信中心号码
	pTemp+=2;															//基本参数
	Asc2HexBuf(pTemp,&Len,2);						//转换获取本次所接受的电话号码
	pTemp+=2;															//国际中心转化
	Asc2HexBuf(pTemp,&Len1,2);
	Flag=0;
	if(Len1==0x91)										//国际电话方式	  //6.17
	{	Flag=1;	
		pTemp+=2;
	}
	for(i=0;i<Len;i+=2,pTemp+=2)													//获取本次所发电话号码
	{	Phone[i]=pTemp[1];
		if(i==(Len-1))
		{	pTemp+=2;
			break;
		}
		Phone[i+1]=pTemp[0];	
	}
	if(Flag==1)
	{	MoveByte(Phone,Phone+2,Len-2);	
	   	ClsArray(Phone+Len-2,2);
	}
	pTemp+=2;														//发送方式
	Asc2HexBuf(pTemp,&Len1,2);
	if(Len1==0x08)					//本函数不支持汉字模式，需要江华峰添加代码
	{	pTemp+=2;
		pTemp+=14;
		Asc2HexBuf(pTemp,&Len1,2);
		pTemp+=2;
		Asc2HexBuf(pTemp,Dat,Len1*2);
		Len = UniToStr(Dat,Message,Len1);
		Message[Len]=0;
		return 0;
	}
	else if(Len1==0x00)
	{	pTemp+=2;
		pTemp+=14;						//时间戳
		Asc2HexBuf(pTemp,&Len1,2);
		Len = Len1/8;
		Len = Len1-Len;
		pTemp+=2;						//实际的7BIT编码
		Asc2HexBuf(pTemp,Dat,Len*2);
		Len=Bit72Bit8(Dat,Message,Len1);
		Message[Len]=0;
		return 0;
	}
	else
		return 0;
}

static uint16 Bit72Bit8(uint8 *Bit7,uint8 *Bit8,uint16 Bit7Len)
{	uint16 nLenTemp;
	uint16 nOrigin = 0;
    uint16 nCode = 0;
    nLenTemp = Bit7Len;           
    
    for(;;)
    {
    	if(nOrigin >= Bit7Len) 
			break;
    	Bit8[nCode] = (uint8 )(Bit7[nOrigin] & 0x7f);
    	
    	if((nOrigin + 1) >= Bit7Len) 
			break;
    	Bit8[nCode + 1] = (uint8 )((Bit7[nOrigin + 1] & 0x3f) << 1);
    	Bit8[nCode + 1] += (uint8 )((Bit7[nOrigin] & 0x80) >> 7);
    	
    	if((nOrigin + 2) >= Bit7Len) 
			break;
    	Bit8[nCode + 2] = (uint8 )((Bit7[nOrigin + 2] & 0x1f) << 2);
    	Bit8[nCode + 2] += (uint8 )((Bit7[nOrigin + 1] & 0xc0) >> 6);
    	
    	if((nOrigin + 3) >= Bit7Len)
			 break;
    	Bit8[nCode + 3] = (uint8 )((Bit7[nOrigin + 3] & 0x0f) << 3);
    	Bit8[nCode + 3] += (uint8 )((Bit7[nOrigin + 2] & 0xe0) >> 5);
    	
    	if((nOrigin + 4) >= Bit7Len) 
			break;
    	Bit8[nCode + 4] = (uint8 )((Bit7[nOrigin + 4] & 0x07) << 4);
    	Bit8[nCode + 4] += (uint8 )((Bit7[nOrigin + 3] & 0xf0) >> 4);
    	
    	if((nOrigin + 5) >= Bit7Len) 
			break;
    	Bit8[nCode + 5] = (uint8 )((Bit7[nOrigin + 5] & 0x03) << 5);
    	Bit8[nCode + 5] += (uint8 )((Bit7[nOrigin + 4] & 0xf8) >> 3);
    	
    	if((nOrigin + 6) >= Bit7Len) 
			break;
    	Bit8[nCode + 6] = (uint8 )((Bit7[nOrigin + 6] & 0x01) << 6);
    	Bit8[nCode + 6] += (uint8 )((Bit7[nOrigin + 5] & 0xfc) >> 2);
    	            	            	
    	Bit8[nCode + 7] = (uint8 )((Bit7[nOrigin + 6] & 0xfe) >> 1);
    	
    	nCode += 8;
    	nOrigin += 7;
    }
    return nLenTemp;
}			

static uint8 GetCsq(uint8 Csq)
{	uint8 i;
	for(i=0;i<De_Asc_MaxV;i++)
	{	if((Csq>=CN_st_Asc_GetData[i].Start)&&(Csq<=CN_st_Asc_GetData[i].End))
			return CN_st_Asc_GetData[i].ByteV;
	}
	return 0;	
}
static uint16 UniToStr(const uint8 *uni,uint8 *str,uint8 Length)
{
	uint16 gb,DataLen,unicode;
	char len;
	DataLen=0;
	len = Length;
	while( len>0 )
	{
		if((uni[0] == 0)&&(uni[1]<0xa4)) //ASCII
		{	uni++;
			*str = (*uni & 0xff);
			str++;
			uni++;
			DataLen++;
			len-=2;
		}
		else	//汉字GB
		{	unicode=(*uni<<8);
			uni++;
			unicode=unicode+*uni;
			uni++;
			if(BinarySearchUni(unicode,&gb)==0)
				return 0;
			*str = (gb >> 8) & 0xff;
			str++;
			*str = gb & 0xff;
			str++;
			DataLen+=2;
			len-=2;
		}
	}
	return DataLen;
}
static uint16 StrToUni(const uint8 *str,uint8 *uni,uint8 Length)
{	char len;
	uint16 gb,unicode,DataLen;
	DataLen = 0;
	len = Length;
	while( len>0 )
	{
		if(*str < 0x81) //ASCII
		{	
			*uni = 0x00;
			uni++;
			*uni = *str;
			uni++;
			str++;
			DataLen+=2;
			len--;
		}
		else	//汉字GB
		{	gb=(*str<<8);
			str++;
 			gb=gb+*str;
			str++;
			if(BinarySearchStr(gb,&unicode)==0)
				return 0;
			*uni = (unicode >> 8) & 0xff;
			uni++;
			*uni = unicode & 0xff;
			uni++;
			DataLen+=2;
			len-=2;
		}

	}
	return DataLen;
}			   
//二分查找
static uint16 BinarySearchUni(uint16 uni,uint16 *gb)
{ 	uint8 Buf[4];
	uint16 Temp;
	int left = 0;
	int middle;
	int right = MAX_UNI_INDEX - 1;
	
	while(left <= right)
	{
		middle = (left+right)/2;
		middle = middle*4;
		CN_st_Fun_File.ReadBin(CN_st_File_GBK.Uni2GBKfd,middle,4,Buf);
		Temp = Buf[2]*256+Buf[3];
		if (uni == Temp)
		{	*gb = Buf[0]*256+Buf[1]; 
			return 1;
		}
		if (uni > Temp) 
			left = middle/4 + 1;
		else 
			right = middle/4 - 1;
	}
	return 0;
}
static uint16 BinarySearchStr(uint16 gb,uint16 *uni)
{ 	uint8 Buf[4];
	uint16 Temp;
	int middle;
	int left = 0;
	int right = MAX_UNI_INDEX - 1;
	
	while(left <= right)
	{
		middle = (left+right)/2;
		middle = middle*4;
		CN_st_Fun_File.ReadBin(CN_st_File_GBK.GBK2Unifd,middle,4,Buf);
		Temp = Buf[0]*256+Buf[1];
		if (gb == Temp) 
		{	*uni = Buf[2]*256+Buf[3]; 
			return 1;
		}
		if (gb > Temp) 
			left = middle/4 + 1;
		else 
			right = middle/4 - 1;
	}
	return 0;
}

static uint16 IP2Char(uint32 IP,uint8 *Buf,uint8 Fix)
{	uint16 DataLen;
	uint8 i,ByteV;
	for(i=0,DataLen=0;i<4;i++)
	{	ByteV=((IP>>((3-i)*8))&0xff);	
	 	DataLen=Algorism2Asc(ByteV,Buf+DataLen)+DataLen;
		Buf[DataLen++]=Fix;
	}
	return DataLen;	
}

static uint16 Char2IP(uint8 *Buf,uint32 *IP,uint8 Fix)				//字符型IP转化成整型IP
{	uint8 *pTemp,*pTemp1;
	uint32 IpHex;
	uint16 DataLen;
	uint8 i;
	for(i=0,pTemp=pTemp1=Buf,*IP=0;i<3;i++)			
	{	DataLen=Strsize16(pTemp);
		pTemp=SeekChar(pTemp,Fix,DataLen,1); 
		*pTemp=0;
		IpHex=Asc2Algorism(pTemp1,Strsize16(pTemp1));
		if(IpHex>0xff)
			return De_Erro_AscNumber_Char2IP;
		*IP|=((IpHex&0XFF)<<((3-i)*8));
		pTemp++;
		pTemp1=pTemp;
	}
	IpHex=Asc2Algorism(pTemp1,Strsize16(pTemp1));
	if(IpHex>0xff)
		return De_Erro_AscNumber_Char2IP;
	*IP|=(IpHex&0XFF);
  	return De_Suc_AscNumber;
}
static uint8 *LookBufInLength(uint8 *LookString,uint16 DataLen1,uint8 *Buf,uint16 DataLength)
{	uint16 i,j;
//	DataLen=Strsize(Buf);
//	DataLen1=Strsize(LookString);
	if(DataLength==0)
		return NULL;
	for(i=0;i<DataLength;i++)
	{	for(j=0;j<DataLen1;j++)
		{	if(Buf[i+j]!=LookString[j])
				break;
		}
		if(j==DataLen1)
			return Buf+i;
	}
	return NULL;
}
static void Value32(uint8 *Buf,uint32 *Hex32,uint16 Len)
{	uint32 i,k;
	if(Len>4)
		Len=0x0004;
	*Hex32=0;
	for(i=1,k=0;Len>0;Len--)
	{	k=Buf[Len-1]*i;
	  	(*Hex32)+=k;
	   	i=i*0x100 ;
	}
}

#endif 







