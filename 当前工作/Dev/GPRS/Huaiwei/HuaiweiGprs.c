#define De_HuaweiGprs_Compiler
#include "_HuaiweiGprs.h"
/*=======================================本页为华为模块命令输出页===========================================*/
/*===========================================华为输出函数======================================================*/
static uint16 Init(void *pFunc,void *Buf,uint16 SizeofBuf)
{	ModermCom=pFunc;													//获取底层的串口驱动
	X_BUF=Buf;
	SizeofX_BUF=SizeofBuf;
	return De_Suc_GprsHard;	
}
static uint16 Read(uint16 Command,void *SendBuf,uint16 SizeofSendBuf,void *AgreeBuf,uint16 *SizeofAgreeBuf)
{	uint16 i;
	if((ModermCom==NULL)||(X_BUF==NULL))
		return De_Erro_GprsHead_NoInit;
	for(i=0;i<sizeof(CN_HuaWei_st_GprsHard_Order)/sizeof(st_GprsHard_Order);i++)
	{	if(CN_HuaWei_st_GprsHard_Order[i].Command==Command)	
		{	if(CN_HuaWei_st_GprsHard_Order[i].Operation==NULL)
				return De_Suc_GprsHard;
			return CN_HuaWei_st_GprsHard_Order[i].Operation
			(SendBuf,SizeofSendBuf,AgreeBuf,SizeofAgreeBuf,(st_GprsHard_Order_Cut	*)&CN_HuaWei_st_GprsHard_Order[i].CN_st_GprsHard_Order_Cut);
		}
	}
	return De_Erro_GprsHard_NoOrder;	
}
/*=============================================命令集合=======================================================*/
//关闭回显
static uint16 Huawei_CloseShow(void *SendBuf,uint16 SizeofSendBuf,void *AgreeBuf,uint16 *SizeofAgreeBuf,st_GprsHard_Order_Cut	*ptst_GprsHard_Order_Cut)
{	uint16 Result;		
	SendBuf=SendBuf;AgreeBuf=AgreeBuf;SizeofSendBuf=SizeofSendBuf;
	if((Result=ModermCom(NULL,X_BUF,SizeofX_BUF,ptst_GprsHard_Order_Cut))!=De_Suc_GprsHard)
		return Result;
	return Result;
}
//获取器件ID
static uint16 GetChipID(void *SendBuf,uint16 SizeofSendBuf,void *AgreeBuf,uint16 *SizeofAgreeBuf,st_GprsHard_Order_Cut	*ptst_GprsHard_Order_Cut)
{	uint16 Result;
	SendBuf=SendBuf;SizeofSendBuf=SizeofSendBuf;
	if((Result=ModermCom(NULL,X_BUF,SizeofX_BUF,ptst_GprsHard_Order_Cut))!=De_Suc_GprsHard)
		return Result;
	ClearNoDisplay(X_BUF);
	*SizeofAgreeBuf=CN_st_Fun_AscNumber.Strsize16(X_BUF);
	CN_st_Fun_AscNumber.MoveByte(AgreeBuf,X_BUF,*SizeofAgreeBuf);
	return Result;
}
//获取模块状态
static uint16 Huawei_GetModermState(void *SendBuf,uint16 SizeofSendBuf,void *AgreeBuf,uint16 *SizeofAgreeBuf,st_GprsHard_Order_Cut	*ptst_GprsHard_Order_Cut)
{	uint8 *ByteAgree;
	uint16 Result;
	ByteAgree=AgreeBuf;SizeofSendBuf=SizeofSendBuf;
	if((Result=ModermCom(NULL,X_BUF,SizeofX_BUF,ptst_GprsHard_Order_Cut))!=De_Suc_GprsHard)
		return Result;
	ClearNoDisplay(X_BUF);
	Result=CN_st_Fun_AscNumber.Strsize16(X_BUF);
	if(Result!=1)
		return De_Erro_GprsHead_ReLen;			//长度错误
	for(Result=0;Result<sizeof(CN_Huawei_st_GprsHead_Result)/sizeof(st_GprsHead_Result);Result++)
	{	if(X_BUF[0]==CN_Huawei_st_GprsHead_Result[Result].ResultV)
		{	*ByteAgree=CN_Huawei_st_GprsHead_Result[Result].ContrV;
			return De_Suc_GprsHard;
		}
	}
	return De_Erro_GprsHead_NoReVa;
}
//查询卡在位情况
static uint16 Huawei_GetModermCard(void *SendBuf,uint16 SizeofSendBuf,void *AgreeBuf,uint16 *SizeofAgreeBuf,st_GprsHard_Order_Cut	*ptst_GprsHard_Order_Cut)
{	uint16 Result;
	uint8 *State;
	SendBuf=SendBuf;State=AgreeBuf;SizeofSendBuf=SizeofSendBuf;SizeofAgreeBuf=SizeofAgreeBuf;
	if((Result=ModermCom(NULL,X_BUF,SizeofX_BUF,ptst_GprsHard_Order_Cut))!=De_Suc_GprsHard)
		return Result;

	ClearNoDisplay(X_BUF);
	if(X_BUF[0]=='1')
		*State=De_GprsHard_SimState_Yes;	
	else
		*State=De_GprsHard_SimState_No;
	return De_Suc_GprsHard;		
}
//查询短信中心号码
static uint16 Huawei_GetCenterNumber(void *SendBuf,uint16 SizeofSendBuf,void *AgreeBuf,uint16 *SizeofAgreeBuf,st_GprsHard_Order_Cut	*ptst_GprsHard_Order_Cut)
{	uint16 Result;
	uint8 *pTemp,*pTempTail;
	SendBuf=SendBuf;SizeofSendBuf=SizeofSendBuf;
	if((Result=ModermCom(NULL,X_BUF,SizeofX_BUF,ptst_GprsHard_Order_Cut))!=De_Suc_GprsHard)
		return Result;
	ClearNoDisplay(X_BUF);
	Result=CN_st_Fun_AscNumber.Strsize16(X_BUF);
	if((pTemp=SeekChar(X_BUF,'"',Result,1))==NULL)
		return De_Erro_GprsHead_Explain;
	if((pTempTail=SeekChar(X_BUF,'"',Result,2))==NULL)
		return De_Erro_GprsHead_Explain;
	pTemp++;
	if(*pTemp=='+')
		pTemp++;
	if((*pTemp=='8')&&(pTemp[1]=='6'))
		pTemp+=2;
	*SizeofAgreeBuf=pTempTail-pTemp;
	CN_st_Fun_AscNumber.MoveByte(AgreeBuf,pTemp,*SizeofAgreeBuf);
	return De_Suc_GprsHard;
}

 //读短消息
static uint16 Huawei_GetMessage(void *SendBuf,uint16 SizeofSendBuf,void *AgreeBuf,uint16 *SizeofAgreeBuf,st_GprsHard_Order_Cut	*ptst_GprsHard_Order_Cut)
{	st_GprsHard_GetMessage	*ptst_GprsHard_GetMessage;
	uint8 *Buf,*pTemp;
	uint16 Result,DataLen;
	uint8 ReadId;
	SizeofSendBuf=SizeofSendBuf;
	ptst_GprsHard_GetMessage=AgreeBuf;
	Buf=SendBuf;
	ReadId=*Buf;
	X_BUF[CN_st_Fun_AscNumber.Algorism2Asc((uint32)ReadId,X_BUF)]=0;
	Result=ModermCom(X_BUF,X_BUF,SizeofX_BUF,ptst_GprsHard_Order_Cut);
	if(Result==De_Erro_GprsHead_ReErro)
	{	
		ptst_GprsHard_GetMessage->State=De_GprsHard_Ide;
		return De_Suc_GprsHard;	
	}
	if(Result!=De_Suc_GprsHard)
		return Result;
	DataLen=CN_st_Fun_AscNumber.Strsize16(X_BUF);
	if((pTemp=SeekChar(X_BUF,',',DataLen,1))==NULL)
		return De_Erro_GprsHead_Explain;				//解析错误
	*pTemp=0;	
	ClearNoDisplay(X_BUF);
	for(Result=0;Result<sizeof(CN_Huawei_ReadMessage)/sizeof(st_GprsHead_Result);Result++)
	{	if(CN_Huawei_ReadMessage[Result].ResultV==X_BUF[0])
		{	ptst_GprsHard_GetMessage->State=CN_Huawei_ReadMessage[Result].ContrV;	
		 	break;
		}
	}
	if(Result==sizeof(CN_Huawei_ReadMessage)/sizeof(st_GprsHead_Result))
		return De_Erro_GprsHead_Explain;			//解析错误
   	pTemp++;
	pTemp++;
	if((Buf=SeekChar(pTemp,0x0d,DataLen,1))==NULL)	//短信息长度
		return De_Erro_GprsHead_Explain;			//解析错误
	*Buf=0;
	ClearNoDisplay(pTemp);
	ReadId = CN_st_Fun_AscNumber.Asc2Algorism(pTemp,CN_st_Fun_AscNumber.Strsize16(pTemp));
	if(ReadId==0)
	{	*SizeofAgreeBuf=1;
		ptst_GprsHard_GetMessage->State=De_GprsHard_Ide;
		return De_Suc_GprsHard;	
	}
	Buf++;
	if((pTemp=SeekChar(Buf,0x0d,DataLen,1))==NULL)
		return De_Erro_GprsHead_Explain;
	*pTemp=0;
	ClearNoDisplay(Buf);
	*SizeofAgreeBuf=CN_st_Fun_AscNumber.Strsize16(Buf);
	CN_st_Fun_AscNumber.MoveByte(ptst_GprsHard_GetMessage->Buf,Buf,*SizeofAgreeBuf);
	ptst_GprsHard_GetMessage->Buf[*SizeofAgreeBuf]=0;
	return De_Suc_GprsHard;
}
//设置文本或者是PDU方式
static uint16 Huawei_SetTxtOrPdu(void *SendBuf,uint16 SizeofSendBuf,void *AgreeBuf,uint16 *SizeofAgreeBuf,st_GprsHard_Order_Cut	*ptst_GprsHard_Order_Cut)
{	uint8 *Buf;
	uint16 Result;
   	Buf=SendBuf;
	AgreeBuf=AgreeBuf;SizeofSendBuf=SizeofSendBuf;SizeofAgreeBuf=SizeofAgreeBuf;
	for(Result=0;Result<sizeof(CN_Huawei_SetMessage)/sizeof(st_GprsHead_Result);Result++)
	{	if(CN_Huawei_SetMessage[Result].ContrV==*Buf)
		{	X_BUF[0]=CN_Huawei_SetMessage[Result].ResultV;	
		 	break;
		}
	}
	if(Result==sizeof(CN_Huawei_SetMessage)/sizeof(st_GprsHead_Result))
		return De_Erro_GprsHard_NoOrder;
	X_BUF[1]=0;
	if((Result=ModermCom(X_BUF,X_BUF,SizeofX_BUF,ptst_GprsHard_Order_Cut))!=De_Suc_GprsHard)
		return Result;
	return Result;
}
//查看TEXT或者PDU的文本设置内容
static uint16 Huawei_SeeTxtOrPdu(void *SendBuf,uint16 SizeofSendBuf,void *AgreeBuf,uint16 *SizeofAgreeBuf,st_GprsHard_Order_Cut	*ptst_GprsHard_Order_Cut)
{	uint8 *Buf;
	uint16 Result;
	SendBuf=SendBuf;SizeofSendBuf=SizeofSendBuf;
	if((Result=ModermCom(NULL,X_BUF,SizeofX_BUF,ptst_GprsHard_Order_Cut))!=De_Suc_GprsHard)
		return Result;
	ClearNoDisplay(X_BUF);
	for(Result=0,Buf=AgreeBuf;Result<sizeof(CN_Huawei_SetMessage)/sizeof(st_GprsHead_Result);Result++)
	{	if(CN_Huawei_SetMessage[Result].ResultV==X_BUF[0])
		{	*Buf=CN_Huawei_SetMessage[Result].ContrV;	
		 	break;
		}
	}
	if(Result==sizeof(CN_Huawei_SetMessage)/sizeof(st_GprsHead_Result))
		return De_Erro_GprsHard_NoOrder;
	return De_Suc_GprsHard;
}
//发送短消息
static uint16 Huawei_MsgSend(void *SendBuf,uint16 SizeofSendBuf,void *AgreeBuf,uint16 *SizeofAgreeBuf,st_GprsHard_Order_Cut	*ptst_GprsHard_Order_Cut)
{	uint32 *HexBuf;
	uint16 Result;
	HexBuf=SendBuf;AgreeBuf=AgreeBuf;SizeofSendBuf=SizeofSendBuf;SizeofAgreeBuf=SizeofAgreeBuf;
	X_BUF[CN_st_Fun_AscNumber.Algorism2Asc((uint32	)*HexBuf,X_BUF)]=0;
	if((Result=ModermCom(X_BUF,X_BUF,SizeofX_BUF,ptst_GprsHard_Order_Cut))!=De_Suc_GprsHard)
		return Result;
	return Result;
}
//发送短消息数据
static uint16 Huawei_MsgSendData(void *SendBuf,uint16 SizeofSendBuf,void *AgreeBuf,uint16 *SizeofAgreeBuf,st_GprsHard_Order_Cut	*ptst_GprsHard_Order_Cut)
{	uint8 *Buf;
	uint16 Result;
	AgreeBuf=AgreeBuf;SizeofSendBuf=SizeofSendBuf; SizeofAgreeBuf=SizeofAgreeBuf;
	Buf=SendBuf;
//	CN_st_Fun_AscNumber.HexBuf2Asc(Buf,X_BUF,SizeofSendBuf);
//	X_BUF[SizeofSendBuf*2]=0;
	Result=CN_st_Fun_AscNumber.Strsize16(Buf);
	Buf[Result]=0x1a;
	Buf[Result+1]=0;
	if((Result=ModermCom(Buf,X_BUF,SizeofX_BUF,ptst_GprsHard_Order_Cut))!=De_Suc_GprsHard)
		return Result;
	return Result;	 
}
//查看运营商情况
static uint16 Huawei_SeeCarrier(void *SendBuf,uint16 SizeofSendBuf,void *AgreeBuf,uint16 *SizeofAgreeBuf,st_GprsHard_Order_Cut	*ptst_GprsHard_Order_Cut)
{	uint8 *Buf;
	uint16 Result;
	if((Result=ModermCom(NULL,X_BUF,SizeofX_BUF,ptst_GprsHard_Order_Cut))!=De_Suc_GprsHard)
		return Result;
	ClearNoDisplay(X_BUF);
	for(Result=0,Buf=AgreeBuf;Result<(sizeof(CN_Huawei_Carrier)/sizeof(st_GprsHead_Explain));Result++)
	{	if(CN_st_Fun_AscNumber.CompareBuf(CN_Huawei_Carrier[Result].Cut,X_BUF,
			CN_st_Fun_AscNumber.Strsize16(CN_Huawei_Carrier[Result].Cut))==0)
		{	*Buf=CN_Huawei_Carrier[Result].Value;
			break;
		}		
	}
	if(Result==sizeof(CN_Huawei_Carrier)/sizeof(st_GprsHead_Explain))
		*Buf=De_GprsHard_Unicom;	
	return De_Suc_GprsHard;
}
//查看信号强度
static uint16 Huawei_SQ(void *SendBuf,uint16 SizeofSendBuf,void *AgreeBuf,uint16 *SizeofAgreeBuf,st_GprsHard_Order_Cut	*ptst_GprsHard_Order_Cut)
{	uint8 *Buf;
	uint16 Result;
	uint8 ReadID;
	SizeofSendBuf=SizeofSendBuf;SendBuf=SendBuf;
	if((Result=ModermCom(NULL,X_BUF,SizeofX_BUF,ptst_GprsHard_Order_Cut))!=De_Suc_GprsHard)
		return Result;
    ClearNoDisplay(X_BUF);
	Result=CN_st_Fun_AscNumber.Strsize16(X_BUF);
	if((Buf=SeekChar(X_BUF,',',Result,1))==NULL)
		return De_Erro_GprsHead_Explain;
	Buf[0]=0;
//	ClearNoDisplay(Buf);
	ReadID=CN_st_Fun_AscNumber.Asc2Algorism(X_BUF,CN_st_Fun_AscNumber.Strsize(X_BUF));
	for(Result=0;Result<sizeof(CN_Ba_st_Asc_GetData)/sizeof(st_Asc_GetData);Result++)
	{	if((ReadID>=CN_Ba_st_Asc_GetData[Result].Start)&&(ReadID<=CN_Ba_st_Asc_GetData[Result].End))
			break;
	}
	if(Result==sizeof(CN_Ba_st_Asc_GetData)/sizeof(st_Asc_GetData))
		return De_Erro_GprsHead_Explain;
	Buf=AgreeBuf;
   	*Buf=CN_Ba_st_Asc_GetData[Result].ByteV;
	return De_Suc_GprsHard;
}
//删除短消息
static uint16 Huawei_DelMsg(void *SendBuf,uint16 SizeofSendBuf,void *AgreeBuf,uint16 *SizeofAgreeBuf,st_GprsHard_Order_Cut	*ptst_GprsHard_Order_Cut)
{ 	uint8 *ReadID;
	uint16 Result;
	ReadID=SendBuf;SizeofSendBuf=SizeofSendBuf;AgreeBuf=AgreeBuf;SizeofAgreeBuf=SizeofAgreeBuf;
	X_BUF[CN_st_Fun_AscNumber.Algorism2Asc((uint32	)*ReadID,X_BUF)]=0;
	Result=ModermCom(X_BUF,X_BUF,SizeofX_BUF,ptst_GprsHard_Order_Cut);
	if((Result==De_Suc_GprsHard)||(Result==De_Erro_GprsHead_ReErro))
		return De_Suc_GprsHard;
	return Result;
}
//SMS存储器设置
static uint16 Huawei_Set_Mem(void *SendBuf,uint16 SizeofSendBuf,void *AgreeBuf,uint16 *SizeofAgreeBuf,st_GprsHard_Order_Cut	*ptst_GprsHard_Order_Cut)
{	const uint8 MemSet[]="\"SM\",\"SM\",\"SM\"";
	uint16 Result;
	SizeofSendBuf=SizeofSendBuf;AgreeBuf=AgreeBuf;SendBuf=SendBuf;SizeofAgreeBuf=SizeofAgreeBuf;
	Result=ModermCom((uint8 *)MemSet,X_BUF,SizeofX_BUF,ptst_GprsHard_Order_Cut);
	if(Result!=De_Suc_GprsHard)
		return Result;
	return Result;			
}
//设置短消息
static uint16 Huawei_MessSet(void *SendBuf,uint16 SizeofSendBuf,void *AgreeBuf,uint16 *SizeofAgreeBuf,st_GprsHard_Order_Cut	*ptst_GprsHard_Order_Cut)
{	uint16 Result;
	const uint8 MemSet[]="2,1,0,0,1";
	SizeofSendBuf=SizeofSendBuf;AgreeBuf=AgreeBuf;SendBuf=SendBuf; SizeofAgreeBuf=SizeofAgreeBuf;
	Result=ModermCom((uint8 *)MemSet,X_BUF,SizeofX_BUF,ptst_GprsHard_Order_Cut);
	if(Result!=De_Suc_GprsHard)
		return Result;
	return Result;	
}
//保存设置
static uint16 Huawei_Upadate(void *SendBuf,uint16 SizeofSendBuf,void *AgreeBuf,uint16 *SizeofAgreeBuf,st_GprsHard_Order_Cut	*ptst_GprsHard_Order_Cut)
{	uint16 Result;
	SizeofSendBuf=SizeofSendBuf;AgreeBuf=AgreeBuf;SendBuf=SendBuf;SizeofAgreeBuf=SizeofAgreeBuf;
	Result=ModermCom(NULL,X_BUF,SizeofX_BUF,ptst_GprsHard_Order_Cut);
	if(Result!=De_Suc_GprsHard)
		return Result;
	return Result;	
}
//网络注册情况
static uint16 Huawei_Reg(void *SendBuf,uint16 SizeofSendBuf,void *AgreeBuf,uint16 *SizeofAgreeBuf,st_GprsHard_Order_Cut	*ptst_GprsHard_Order_Cut)
{	uint8 *ReBuf,*Buf;
	uint16 Result;
	Result=ModermCom(NULL,X_BUF,SizeofX_BUF,ptst_GprsHard_Order_Cut);
	if(Result!=De_Suc_GprsHard)
		return Result;
   	ClearNoDisplay(X_BUF);
	Result=CN_st_Fun_AscNumber.Strsize16(X_BUF);
	if((Buf=SeekChar(X_BUF,',',Result,1))==NULL)
		return De_Erro_GprsHead_Explain;
	Buf++;
	for(Result=0,ReBuf=AgreeBuf;Result<sizeof(CN_Reg_State)/sizeof(st_GprsHead_Result);Result++)
	{	if(CN_Reg_State[Result].ResultV==*Buf)
		{	*ReBuf=CN_Reg_State[Result].ContrV;	
			return De_Suc_GprsHard;
		}
	}
	return De_Erro_GprsHead_Explain;
}
//设置来电显示
static uint16 Huawei_CLIP(void *SendBuf,uint16 SizeofSendBuf,void *AgreeBuf,uint16 *SizeofAgreeBuf,st_GprsHard_Order_Cut	*ptst_GprsHard_Order_Cut)
{ 	uint16 Result;
	SendBuf=SendBuf;SizeofSendBuf=SizeofSendBuf;AgreeBuf=AgreeBuf;SizeofAgreeBuf=SizeofAgreeBuf;
	Result=ModermCom(NULL,X_BUF,SizeofX_BUF,ptst_GprsHard_Order_Cut);
	if(Result!=De_Suc_GprsHard)
		return Result;
	return Result;
}
//拨打电话
static uint16 Huawei_ATD(void *SendBuf,uint16 SizeofSendBuf,void *AgreeBuf,uint16 *SizeofAgreeBuf,st_GprsHard_Order_Cut	*ptst_GprsHard_Order_Cut)
{	uint16 Result;
 	uint8 *Buf;
	Buf=SendBuf; SizeofSendBuf=SizeofSendBuf;SizeofAgreeBuf=SizeofAgreeBuf;
   	CN_st_Fun_AscNumber.MoveByte(X_BUF,SendBuf,SizeofSendBuf);
	X_BUF[SizeofSendBuf++]=';';X_BUF[SizeofSendBuf++]=0;
	Result=ModermCom(X_BUF,X_BUF,SizeofX_BUF,ptst_GprsHard_Order_Cut);
	if(Result!=De_Suc_GprsHard)
		return Result;
	for(Result=0,Buf=AgreeBuf;Result<sizeof(CN_Ba_CallRes)/sizeof(st_GprsHead_Explain);Result++)
	{	if(CN_st_Fun_AscNumber.CompareBuf(CN_Ba_CallRes[Result].Cut,X_BUF,CN_st_Fun_AscNumber.Strsize16(CN_Ba_CallRes[Result].Cut))==0)	
	   	{	*Buf=CN_Ba_CallRes[Result].Value;
			return De_Suc_GprsHard;	
		}
	}
	return De_Erro_GprsHead_Explain;
}
//挂机
static uint16 Huawei_Chup(void *SendBuf,uint16 SizeofSendBuf,void *AgreeBuf,uint16 *SizeofAgreeBuf,st_GprsHard_Order_Cut	*ptst_GprsHard_Order_Cut)
{	uint16 Result;
	uint8 ReadID=0;
	SendBuf=SendBuf;SizeofSendBuf=SizeofSendBuf;AgreeBuf=AgreeBuf;
	Result=ModermCom(&ReadID,X_BUF,SizeofX_BUF,ptst_GprsHard_Order_Cut);
	if(Result!=De_Suc_GprsHard)
		return Result;
	return Result;
}
//接电话
static uint16 Huawei_ATA(void *SendBuf,uint16 SizeofSendBuf,void *AgreeBuf,uint16 *SizeofAgreeBuf,st_GprsHard_Order_Cut	*ptst_GprsHard_Order_Cut)
{	uint16 Result;
 	uint8 *Buf,ReadID=0;
	SendBuf=SendBuf;SizeofSendBuf=SizeofSendBuf;AgreeBuf=AgreeBuf;
	Result=ModermCom(&ReadID,X_BUF,SizeofX_BUF,ptst_GprsHard_Order_Cut);
	if(Result!=De_Suc_GprsHard)
		return Result;
	for(Result=0,Buf=AgreeBuf;Result<sizeof(CN_Ba_AgreePhone)/sizeof(st_GprsHead_Explain);Result++)
	{	if(CN_st_Fun_AscNumber.CompareBuf(CN_Ba_AgreePhone[Result].Cut,X_BUF,CN_st_Fun_AscNumber.Strsize16(CN_Ba_AgreePhone[Result].Cut))==0)	
	   	{	*Buf=CN_Ba_AgreePhone[Result].Value;
			return De_Suc_GprsHard;	
		}
	}
	return De_Erro_GprsHead_Explain;
}
//获取IMEI码
static uint16 Huawei_IMEI(void *SendBuf,uint16 SizeofSendBuf,void *AgreeBuf,uint16 *SizeofAgreeBuf,st_GprsHard_Order_Cut	*ptst_GprsHard_Order_Cut)
{	uint16 Result;
	uint8 *Buf;
	SendBuf=SendBuf;SizeofSendBuf=SizeofSendBuf;
	Result=ModermCom(NULL,X_BUF,SizeofX_BUF,ptst_GprsHard_Order_Cut);
	if(Result!=De_Suc_GprsHard)
		return Result;
	ClearNoDisplay(X_BUF);
	Buf=AgreeBuf;
	*SizeofAgreeBuf=CN_st_Fun_AscNumber.Strsize(X_BUF);
	CN_st_Fun_AscNumber.MoveByte(Buf,X_BUF,*SizeofAgreeBuf);
	return Result;
}
//定义PDP上下文
static uint16 Huawei_CGDCONT(void *SendBuf,uint16 SizeofSendBuf,void *AgreeBuf,uint16 *SizeofAgreeBuf,st_GprsHard_Order_Cut	*ptst_GprsHard_Order_Cut)
{	st_Data_IPNet *ptst_Data_IPNet;
	uint16 Result;
	SizeofSendBuf=SizeofSendBuf;AgreeBuf=AgreeBuf;
	ptst_Data_IPNet=SendBuf; 
	X_BUF[0]='"';
	Result=CN_st_Fun_AscNumber.Strsize16(ptst_Data_IPNet->APN);
	CN_st_Fun_AscNumber.MoveByte(X_BUF+1,ptst_Data_IPNet->APN,Result);
	Result++;
	X_BUF[Result++]='"'; X_BUF[Result]=0;
	Result=ModermCom(X_BUF,X_BUF,SizeofX_BUF,ptst_GprsHard_Order_Cut);
	if(Result!=De_Suc_GprsHard)
		return Result;
	return Result;
}
//PDP激活和TCP/IP初始化
static uint16 Huawei_Etcpip(void *SendBuf,uint16 SizeofSendBuf,void *AgreeBuf,uint16 *SizeofAgreeBuf,st_GprsHard_Order_Cut	*ptst_GprsHard_Order_Cut)
{	st_Data_IPNet *ptst_Data_IPNet;
	uint16 Result,DataLen;
	SizeofSendBuf=SizeofSendBuf;AgreeBuf=AgreeBuf;
	ptst_Data_IPNet=SendBuf;
	X_BUF[0]='"';
	DataLen=CN_st_Fun_AscNumber.Strsize16(ptst_Data_IPNet->Use);
	CN_st_Fun_AscNumber.MoveByte(X_BUF+1,ptst_Data_IPNet->Use,DataLen);
	DataLen++;
	X_BUF[DataLen++]='"';
	X_BUF[DataLen++]=',';
	X_BUF[DataLen++]='"';
	Result=CN_st_Fun_AscNumber.Strsize16(ptst_Data_IPNet->PassWord);
	CN_st_Fun_AscNumber.MoveByte(X_BUF+DataLen,ptst_Data_IPNet->PassWord,Result);
	DataLen+=Result;
	X_BUF[DataLen++]='"';
	X_BUF[DataLen]=0;
	Result=ModermCom(X_BUF,X_BUF,SizeofX_BUF,ptst_GprsHard_Order_Cut);
	if(Result!=De_Suc_GprsHard)
		return Result;
   	return Result;
}
//设置TCP/IP模式
static uint16 Huawei_IOMODE(void *SendBuf,uint16 SizeofSendBuf,void *AgreeBuf,uint16 *SizeofAgreeBuf,st_GprsHard_Order_Cut	*ptst_GprsHard_Order_Cut)
{	uint16 Result;
	SendBuf=SendBuf;SizeofSendBuf=SizeofSendBuf;AgreeBuf=AgreeBuf;
	Result=ModermCom(NULL,X_BUF,SizeofX_BUF,ptst_GprsHard_Order_Cut);
	if(Result!=De_Suc_GprsHard)
		return Result;
	return Result;
}


/* 链路号,"TCP或则UDP" , "XXX.XXX.XXX" , XXXXX*/
static uint16 Huawei_IPOPENX(void *SendBuf,uint16 SizeofSendBuf,void *AgreeBuf,uint16 *SizeofAgreeBuf,st_GprsHard_Order_Cut	*ptst_GprsHard_Order_Cut)
{	st_Data_OpenUDPTCP	*ptst_Data_OpenUDPTCP;
	uint16 Result,DataLen;
	uint8 ReadID;
	ptst_Data_OpenUDPTCP=SendBuf;
	for(Result=0;Result<sizeof(CN_Huawei_Link)/sizeof(st_GprsHead_Result);Result++)
	{	if(CN_Huawei_Link[Result].ResultV==ptst_Data_OpenUDPTCP->fd)		//
			break;	
	}
	if(Result==sizeof(CN_Huawei_Link)/sizeof(st_GprsHead_Result))
		return De_Erro_GprsHead_NoLink;
	X_BUF[0]=CN_Huawei_Link[Result].ContrV;
	DataLen=1;
	X_BUF[DataLen++]=',';   					//所连接的链路

	for(ReadID=0;ReadID<sizeof(CN_Ba_UDPTCP)/sizeof(st_GprsHead_Explain);ReadID++)
	{	if(CN_Ba_UDPTCP[ReadID].Value==ptst_Data_OpenUDPTCP->OpenType)
			break;
	}
	if(ReadID==sizeof(CN_Ba_UDPTCP)/sizeof(st_GprsHead_Explain))	 						//
		return De_Erro_GprsHead_NoCom;
	Result=CN_st_Fun_AscNumber.Strsize(CN_Ba_UDPTCP[ReadID].Cut);
	CN_st_Fun_AscNumber.MoveByte(X_BUF+DataLen,CN_Ba_UDPTCP[ReadID].Cut,Result);		//连接类型
	DataLen+=Result;

	X_BUF[DataLen++]=',';
	X_BUF[DataLen++]='"';
	DataLen=CN_st_Fun_AscNumber.IP2Char(ptst_Data_OpenUDPTCP->ptst_Data_IPPar->IP,X_BUF+DataLen,'.')+DataLen;
	DataLen-=1;
	X_BUF[DataLen++]='"';
	X_BUF[DataLen++]=',';					//UDP与TCP连接

	DataLen=CN_st_Fun_AscNumber.Algorism2Asc(ptst_Data_OpenUDPTCP->ptst_Data_IPPar->Com,X_BUF+DataLen)+DataLen;
	X_BUF[DataLen]=0;
	Result=ModermCom(X_BUF,X_BUF,SizeofX_BUF,ptst_GprsHard_Order_Cut);
	if(Result!=De_Suc_GprsHard)
		return Result;
	return De_Suc_GprsHard;
}
//多链路下发送UDP或者TCP数据
static uint16 Huawei_IPSENDX(void *SendBuf,uint16 SizeofSendBuf,void *AgreeBuf,uint16 *SizeofAgreeBuf,st_GprsHard_Order_Cut	*ptst_GprsHard_Order_Cut)
{	st_GprsHard_NetData	*ptst_GprsHard_NetData;
	uint16 Result;
	ptst_GprsHard_NetData=SendBuf; AgreeBuf=AgreeBuf;
	CN_st_Fun_AscNumber.ClsArray(X_BUF,SizeofX_BUF);
	for(Result=0;Result<sizeof(CN_Huawei_Link)/sizeof(st_GprsHead_Result);Result++)
	{	if(CN_Huawei_Link[Result].ResultV==ptst_GprsHard_NetData->fd)		//
			break;	
	}
	if(Result==sizeof(CN_Huawei_Link)/sizeof(st_GprsHead_Result))
		return De_Erro_GprsHead_NoLink;
	X_BUF[0]=CN_Huawei_Link[Result].ContrV;
	Result=1;
	X_BUF[Result++]=',';
	X_BUF[Result++]='"';
	CN_st_Fun_AscNumber.HexBuf2Asc(ptst_GprsHard_NetData->Data,X_BUF+Result,ptst_GprsHard_NetData->DataLen);
	Result=Result+ptst_GprsHard_NetData->DataLen*2;
	X_BUF[Result++]='"';
	X_BUF[Result++]=0;
	Result=ModermCom(X_BUF,X_BUF,SizeofX_BUF,ptst_GprsHard_Order_Cut);
	if(Result!=De_Suc_GprsHard)
		return Result;
	return De_Suc_GprsHard;
}



static uint16 Huawei_SeeDataRead(void *SendBuf,uint16 SizeofSendBuf,void *AgreeBuf,uint16 *SizeofAgreeBuf,st_GprsHard_Order_Cut	*ptst_GprsHard_Order_Cut)
{	st_GprsHard_UDPDataFlag		*ptst_GprsHard_UDPDataFlag;	
	uint8 *Buf;
	uint16 Result;
	uint8 ReadID=0;
 	ptst_GprsHard_UDPDataFlag=AgreeBuf;SizeofSendBuf=SizeofSendBuf;SendBuf=SendBuf;
	if((Result=ModermCom(&ReadID,X_BUF,SizeofX_BUF,ptst_GprsHard_Order_Cut))!=De_Suc_GprsHard)
		return Result;
   	ClearNoDisplay(X_BUF);
	if((Buf=SeekChar(X_BUF,',',100,1))==NULL)
		return De_Erro_GprsHead_Explain;
	*Buf=0;
	ptst_GprsHard_UDPDataFlag->NewDataNumber=CN_st_Fun_AscNumber.Asc2Algorism(X_BUF,Buf-X_BUF);
	Buf++;
	ptst_GprsHard_UDPDataFlag->SumDataNumber=CN_st_Fun_AscNumber.Asc2Algorism(Buf,CN_st_Fun_AscNumber.Strsize(Buf));
	return De_Suc_GprsHard;
}

/*------------%IPDR:<linkNum>,<data_index>,<data Len>,<data>------------------------------------------------*/
static uint16 Huawei_IPDR(void *SendBuf,uint16 SizeofSendBuf,void *AgreeBuf,uint16 *SizeofAgreeBuf,st_GprsHard_Order_Cut	*ptst_GprsHard_Order_Cut)
{	st_GprsHard_ReadData	*ptst_GprsHard_ReadData;
	uint8 *pTemp,*pTemp1;
	uint16 Result,Datalength;
	uint8 ReadID=0;
	ptst_GprsHard_ReadData=AgreeBuf;
	Result=ModermCom(NULL,X_BUF,SizeofX_BUF,ptst_GprsHard_Order_Cut);
	if(Result!=De_Suc_GprsHard)	 								//操作不成功
		return Result;

	ClearNoDisplay(X_BUF);
	Datalength=CN_st_Fun_AscNumber.Strsize16(X_BUF);
	pTemp=SeekChar(X_BUF,',',Datalength,1);
	if(pTemp==NULL)
		return De_Erro_GprsHead_Explain;
	*pTemp=0;
	ReadID = X_BUF[0];
//	ReadID=CN_st_Fun_AscNumber.Asc2Algorism(X_BUF,CN_st_Fun_AscNumber.Strsize16(X_BUF));
	for(Result=0;Result<sizeof(CN_Huawei_Link)/sizeof(st_GprsHead_Result);Result++)
	{	if(CN_Huawei_Link[Result].ContrV==ReadID)		//
			break;	
	}
	if(Result==sizeof(CN_Huawei_Link)/sizeof(st_GprsHead_Result))
		return De_Erro_GprsHead_NoLink;
	for(ReadID=0;ReadID<De_GprsHard_MaxLink;ReadID++)
	{	if(ptst_GprsHard_ReadData->fd[ReadID]==CN_Huawei_Link[Result].ResultV)
			break;
	}
	if(ReadID==De_GprsHard_MaxLink)						//此链路应用层未定义
		return De_Erro_GprsHead_SoftLinkNo;
	
	pTemp++;
	pTemp1=SeekChar(pTemp,',',Datalength,1);
	if(pTemp1==NULL)
		return De_Erro_GprsHead_Explain;
	*pTemp1=0;

	pTemp1++;
	pTemp=SeekChar(pTemp1,',',Datalength,1);
	if(pTemp==NULL)
		return De_Erro_GprsHead_Explain;
	*pTemp=0;

	Result=CN_st_Fun_AscNumber.Asc2Algorism(pTemp1,CN_st_Fun_AscNumber.Strsize16(pTemp1));
	
	pTemp++;
	pTemp1=SeekChar(pTemp,'"',Datalength,1);
	if(pTemp1==NULL)
		return De_Erro_GprsHead_Explain;
	*pTemp1=0;
	pTemp1++;
	pTemp=SeekChar(pTemp1,'"',Datalength,1);
	if(pTemp==NULL)
		return De_Erro_GprsHead_Explain;
	*pTemp=0;

	if(CN_st_Fun_AscNumber.Strsize16(pTemp1)!=2*Result)
		return De_Erro_GprsHead_Explain;
	ptst_GprsHard_ReadData->DataLen[ReadID]=Result;
	CN_st_Fun_AscNumber.Asc2HexBuf(pTemp1,ptst_GprsHard_ReadData->Data[ReadID],CN_st_Fun_AscNumber.Strsize16(pTemp1));		
	ptst_GprsHard_ReadData->NewLink=ReadID;
	return De_Suc_GprsHard;
}
//查看TCP/IP状态
static uint16 Huawei_JugeETCPIP(void *SendBuf,uint16 SizeofSendBuf,void *AgreeBuf,uint16 *SizeofAgreeBuf,st_GprsHard_Order_Cut	*ptst_GprsHard_Order_Cut)
{	st_HardWare_SeeTCPData	*ptst_HardWare_SeeTCPData;
	uint8 *pTemp,*pTemp1,*pTemp2;
	uint16 Result,DataLen;
	uint8 ReadID=0;
	ptst_HardWare_SeeTCPData=AgreeBuf; SendBuf=SendBuf;SizeofSendBuf=SizeofSendBuf;
	Result=ModermCom(NULL,X_BUF,SizeofX_BUF,ptst_GprsHard_Order_Cut);
	if(Result!=De_Suc_GprsHard)
		return Result;
	/*====================================TCP状态==================================================*/
	ClearNoDisplay(X_BUF);
	DataLen=CN_st_Fun_AscNumber.Strsize16(X_BUF);
	pTemp=SeekChar(X_BUF,',',DataLen,1);
	if(pTemp==NULL)
		return De_Erro_GprsHead_Explain;
	ReadID=X_BUF[0];
	for(Result=0;Result<sizeof(CN_Huawei_TCPInitState)/sizeof(st_GprsHead_Result);Result++)
	{	if(ReadID==CN_Huawei_TCPInitState[Result].ContrV)
			break;
	}
	if(Result==sizeof(CN_Huawei_TCPInitState)/sizeof(st_GprsHead_Result))
		return De_Erro_GprsHead_Explain;
	ptst_HardWare_SeeTCPData->State=CN_Huawei_TCPInitState[Result].ResultV;
	if(ptst_HardWare_SeeTCPData->State==De_GprsHard_InitTcp_NoOver)	  			//TCP初始化未完成
		return De_Suc_GprsHard;
	/*======================================IP地址================================================*/
	 pTemp++;
	 pTemp1=SeekChar(pTemp,',',DataLen,1);
	 if(pTemp1==NULL)
		return De_Erro_GprsHead_Explain;
	if((pTemp1-pTemp)>1)
	{	*pTemp1=0;
		pTemp++;
		pTemp2=SeekChar(pTemp,'"',DataLen,1);
		*pTemp2=0;		 
		 if(CN_st_Fun_AscNumber.Char2IP(pTemp,&ptst_HardWare_SeeTCPData->IP,'.')!=De_Suc_AscNumber)
		 	return De_Erro_GprsHead_Explain;
	}
	/*=======================================网关=================================================*/	
	pTemp1++;
	pTemp=SeekChar(pTemp1,',',DataLen,1);
	if(pTemp==NULL)
		return De_Erro_GprsHead_Explain;
	if((pTemp-pTemp1)>1)
	{	*pTemp=0;
		pTemp1++;
		pTemp2=SeekChar(pTemp1,'"',DataLen,1);
		*pTemp2=0;
		if(CN_st_Fun_AscNumber.Char2IP(pTemp1,&ptst_HardWare_SeeTCPData->GateWay,'.')!=De_Suc_AscNumber)
		 	return De_Erro_GprsHead_Explain;
	}
	/*======================================首选DSN================================================*/
	 pTemp++;
	 pTemp1=SeekChar(pTemp,',',DataLen,1);
	 if(pTemp1==NULL)
		return De_Erro_GprsHead_Explain;
	if((pTemp1-pTemp)>1)
	{	*pTemp1=0;
		pTemp++;
		pTemp2=SeekChar(pTemp,'"',DataLen,1);
		*pTemp2=0;
	 	if(CN_st_Fun_AscNumber.Char2IP(pTemp,&ptst_HardWare_SeeTCPData->FristDNS,'.')!=De_Suc_AscNumber)
	 		return De_Erro_GprsHead_Explain; 
	}
	/*=======================================备份DSN================================================*/	
	pTemp1++;
	pTemp1++;
	pTemp=SeekChar(pTemp1,'"',DataLen,1);
	if(pTemp==NULL)
		return De_Erro_GprsHead_Explain;
	if((pTemp-pTemp1)>1)
	{	*pTemp=0;
		if(CN_st_Fun_AscNumber.Char2IP(pTemp1,&ptst_HardWare_SeeTCPData->BackDNS,'.')!=De_Suc_AscNumber)
	 		return De_Erro_GprsHead_Explain;
	}
	return De_Suc_GprsHard;						
}
//域名解析
static uint16 Huawei_DNSR(void *SendBuf,uint16 SizeofSendBuf,void *AgreeBuf,uint16 *SizeofAgreeBuf,st_GprsHard_Order_Cut	*ptst_GprsHard_Order_Cut)
{	uint32 *IP;
	uint16 Result;
	X_BUF[0]='"';
	CN_st_Fun_AscNumber.MoveByte(X_BUF+1,SendBuf,SizeofSendBuf);
	X_BUF[SizeofSendBuf+1]='"';	X_BUF[SizeofSendBuf+2]=0;
	if((Result=ModermCom(X_BUF,X_BUF,SizeofX_BUF,ptst_GprsHard_Order_Cut))!=De_Suc_GprsHard)
		return Result;
	ClearNoDisplay(X_BUF);
	IP=AgreeBuf;
	if(CN_st_Fun_AscNumber.Char2IP(X_BUF,IP,'.')!=De_Suc_AscNumber)
	 	return De_Erro_GprsHead_Explain;
	return De_Suc_GprsHard;			
}
//设置波特率
static uint16 Huawei_IPR(void *SendBuf,uint16 SizeofSendBuf,void *AgreeBuf,uint16 *SizeofAgreeBuf,st_GprsHard_Order_Cut	*ptst_GprsHard_Order_Cut)
{	uint32 *Bps;
	uint16 Result;
	Bps=SendBuf;
	AgreeBuf=AgreeBuf;SizeofSendBuf=SizeofSendBuf;
	X_BUF[CN_st_Fun_AscNumber.Algorism2Asc(*Bps,X_BUF)]=0;
	if((Result=ModermCom(X_BUF,X_BUF,SizeofX_BUF,ptst_GprsHard_Order_Cut))!=De_Suc_GprsHard)
		return Result;
	*SizeofAgreeBuf=0;
	return De_Suc_GprsHard;
}

//获取通话状态
static uint16 Huawei_CLCC(void *SendBuf,uint16 SizeofSendBuf,void *AgreeBuf,uint16 *SizeofAgreeBuf,st_GprsHard_Order_Cut	*ptst_GprsHard_Order_Cut)
{	uint8 *pTemp,*pTemp1;
	st_GprsHard_CallState	*ptst_GprsHard_CallState;
	uint16 Result,DataLength;
	ptst_GprsHard_CallState=AgreeBuf;
	if((Result=ModermCom(NULL,X_BUF,SizeofX_BUF,ptst_GprsHard_Order_Cut))!=De_Suc_GprsHard)
		return Result;	
	ClearNoDisplay(X_BUF);
   	DataLength=CN_st_Fun_AscNumber.Strsize16(X_BUF);
	if(DataLength==0)					//没有接受到数据
	{	ptst_GprsHard_CallState->CallType=De_GprsHard_CallType_NoCall;	
		return De_Suc_GprsHard;
	}
//	if(CN_st_Fun_AscNumber.CompareBuf(X_BUF,"+CLCC:",6)!=0)
//		return De_Erro_GprsHead_Explain;
//	CN_st_Fun_AscNumber.MoveByte(X_BUF,X_BUF+6,Result-6);
//	CN_st_Fun_AscNumber.ClsArray(X_BUF+Result-6,6);
	/*+++++++++++++++++++++++++++++++++++语音通话方式+++++++++++++++++++++++++++++++++++*/				
	pTemp=SeekChar(X_BUF,',',DataLength,1);
	pTemp1=SeekChar(X_BUF,',',DataLength,2);
	if((pTemp==NULL)||(pTemp1==NULL))							//空指针
		return De_Erro_GprsHead_Explain;
   	pTemp++;
	*pTemp1=0;
	for(Result=0;Result<sizeof(CN_Huawei_CallTyte)/sizeof(st_GprsHead_Result);Result++)
	{	if(CN_Huawei_CallTyte[Result].ContrV==*pTemp)
			break;
	}
	if(Result==sizeof(CN_Huawei_CallTyte)/sizeof(st_GprsHead_Result))
		return De_Erro_GprsHead_Explain;
	ptst_GprsHard_CallState->CallType=CN_Huawei_CallTyte[Result].ResultV;
	/*++++++++++++++++++++++++++++++++++通话状态++++++++++++++++++++++++++++++++++++++++*/
	pTemp1++;
	pTemp=SeekChar(pTemp1,',',DataLength,1);
	if(pTemp==NULL)
		return De_Erro_GprsHead_Explain;
	*pTemp=0;
	for(Result=0;Result<sizeof(CN_Huawei_CallState)/sizeof(st_GprsHead_Result);Result++)
	{ 	if(CN_Huawei_CallState[Result].ContrV==*pTemp1)
			break;
	}
	if(Result==sizeof(CN_Huawei_CallState)/sizeof(st_GprsHead_Result))
		return De_Erro_GprsHead_Explain;
   	ptst_GprsHard_CallState->State=CN_Huawei_CallState[Result].ResultV;
	/*++++++++++++++++++++++++++++++++通话模式++++++++++++++++++++++++++++++++++++++++*/
	pTemp++;
	pTemp1=SeekChar(pTemp,',',DataLength,1);
	if(pTemp1==NULL)
		return De_Erro_GprsHead_Explain;
	*pTemp1=0;
	for(Result=0;Result<sizeof(CN_Huawei_Mod)/sizeof(st_GprsHead_Result);Result++)
	{ 	if(CN_Huawei_Mod[Result].ContrV==*pTemp)
			break;
	}
	if(Result==sizeof(CN_Huawei_Mod)/sizeof(st_GprsHead_Result))
		return De_Erro_GprsHead_Explain;
	ptst_GprsHard_CallState->Mod=CN_Huawei_Mod[Result].ResultV;
	/*++++++++++++++++++++++++++++++++++语音通话类型+++++++++++++++++++++++++++++++++*/
	pTemp1++;
	pTemp=SeekChar(pTemp1,',',DataLength,1);
	if(pTemp==NULL)
		return De_Erro_GprsHead_Explain;
	*pTemp=0;
	for(Result=0;Result<sizeof(CN_Huawei_PeperNumber)/sizeof(st_GprsHead_Result);Result++)
	{ 	if(CN_Huawei_PeperNumber[Result].ContrV==*pTemp)
			break;
	}
	if(Result==sizeof(CN_Huawei_CallState)/sizeof(st_GprsHead_Result))
		return De_Erro_GprsHead_Explain;
   	ptst_GprsHard_CallState->VoiceType=CN_Huawei_PeperNumber[Result].ResultV;
	/*++++++++++++++++++++++++++++++++++++++电话号码++++++++++++++++++++++++++++++++++++++++++++++*/
	pTemp++;
	pTemp1=SeekChar(pTemp,',',DataLength,1);
	if(pTemp1==NULL)
		return De_Erro_GprsHead_Explain;
	*pTemp1=0;
	 pTemp1-=2;
	 pTemp++;
	 if(pTemp>=pTemp1)
	 	return De_Erro_GprsHead_Explain;
	 if((pTemp[0]=='+')&&(pTemp[1]=='8')&&(pTemp[2]=='6'))
	 	pTemp+=3;
	 CN_st_Fun_AscNumber.MoveByte(ptst_GprsHard_CallState->Phone,pTemp,pTemp1-pTemp+1);
	 return De_Suc_GprsHard;


}
//关闭链路1-3
static uint16 Huawei_IPCLOSE(void *SendBuf,uint16 SizeofSendBuf,void *AgreeBuf,uint16 *SizeofAgreeBuf,st_GprsHard_Order_Cut	*ptst_GprsHard_Order_Cut)
{	uint8 *LinkNum;
	uint16 Result;
	LinkNum=SendBuf;
	for(Result=0;Result<sizeof(CN_Huawei_Link)/sizeof(st_GprsHead_Result);Result++)
	{	if(CN_Huawei_Link[Result].ResultV==*LinkNum)
			break;
	}
	if(Result==sizeof(CN_Huawei_Link)/sizeof(st_GprsHead_Result))
		return De_Erro_GprsHead_SoftLinkNo;
	X_BUF[0]=CN_Huawei_Link[Result].ContrV;
   	X_BUF[1]=0;
   	if((Result=ModermCom(X_BUF,X_BUF,SizeofX_BUF,ptst_GprsHard_Order_Cut))!=De_Suc_GprsHard)
		return Result;
	return Result;
}
//注销TCP
static uint16 Huawei_LogOnTCPIP(void *SendBuf,uint16 SizeofSendBuf,void *AgreeBuf,uint16 *SizeofAgreeBuf,st_GprsHard_Order_Cut	*ptst_GprsHard_Order_Cut)
{	uint16 Result;
	SendBuf=SendBuf;SizeofSendBuf=SizeofSendBuf;AgreeBuf=AgreeBuf;
	if((Result=ModermCom(NULL,X_BUF,SizeofX_BUF,ptst_GprsHard_Order_Cut))!=De_Suc_GprsHard)
		return Result;
	return Result;
}
//查看链路是否关闭
static uint16 Huawei_SEEIPCLOSE(void *SendBuf,uint16 SizeofSendBuf,void *AgreeBuf,uint16 *SizeofAgreeBuf,st_GprsHard_Order_Cut	*ptst_GprsHard_Order_Cut)
{	uint8 LinkNum,*temp;
	uint16 Result;
	uint8 LinkNumber;
	temp=SendBuf;
	for(Result=0;Result<sizeof(CN_Huawei_Link)/sizeof(st_GprsHead_Result);Result++)
	{	if(CN_Huawei_Link[Result].ResultV==*temp)
			break;
	}
	if(Result==sizeof(CN_Huawei_Link)/sizeof(st_GprsHead_Result))
		return De_Erro_GprsHead_SoftLinkNo;
	LinkNum=CN_Huawei_Link[Result].ContrV;
	for(LinkNumber=0;LinkNumber<De_GprsHard_MaxLink;LinkNumber++)
	{	if(CN_LinkNum[LinkNumber]==LinkNum)
			break;
	}
	if(LinkNumber==De_GprsHard_MaxLink)
		return De_Erro_GprsHead_SoftLinkNo;
	if((Result=ModermCom(NULL,X_BUF,SizeofX_BUF,ptst_GprsHard_Order_Cut))!=De_Suc_GprsHard)
		return Result;
	
	ClearNoDisplay(X_BUF);
	temp=X_BUF;
	if(LinkNumber!=0)
	{	temp=SeekChar(X_BUF,',',100,LinkNumber);
	 	if(temp==NULL)
			return De_Erro_GprsHead_Explain;
		temp++;
	}
	for(Result=0;Result<sizeof(CN_Huawei_LinkOper)/sizeof(st_GprsHead_Result);Result++)
	{	if(CN_Huawei_LinkOper[Result].ContrV==*temp)
			break;	
	}
	if(Result==sizeof(CN_Huawei_LinkOper)/sizeof(st_GprsHead_Result))
		return De_Erro_GprsHead_Explain;
	temp=AgreeBuf;
	*temp=CN_Huawei_LinkOper[Result].ResultV;
	return De_Suc_GprsHard;	
}
static uint16 Huawei_PowerDown(void *SendBuf,uint16 SizeofSendBuf,void *AgreeBuf,uint16 *SizeofAgreeBuf,st_GprsHard_Order_Cut	*ptst_GprsHard_Order_Cut)
{	return ModermCom(NULL,X_BUF,SizeofX_BUF,ptst_GprsHard_Order_Cut);
}

static uint16 Huawei_SeeCGDCONT(void *SendBuf,uint16 SizeofSendBuf,void *AgreeBuf,uint16 *SizeofAgreeBuf,st_GprsHard_Order_Cut	*ptst_GprsHard_Order_Cut)
{	st_Data_IPNet *ptst_Data_IPNet;
	uint8 *Buf,*Buf1;
	uint16 Result;

	Result=ModermCom(NULL,X_BUF,SizeofX_BUF,ptst_GprsHard_Order_Cut);
	if(!((Result==De_Erro_GprsHead_FlagHead)||(Result==De_Suc_GprsHard)))
		return Result;
	if(Result==De_Erro_GprsHead_FlagHead)
		return De_Erro_GprsHard_NoInitCONT;

	ClearNoDisplay(X_BUF);
	if(X_BUF[0]!='1') 						//#define De_Erro_GprsHard_NoInitCONT
		return De_Erro_GprsHard_NoInitCONT;
	Result=CN_st_Fun_AscNumber.Strsize(X_BUF);
	if((Buf=SeekChar(X_BUF,'\"',Result,1))==NULL) 	//解析错误
		return De_Erro_GprsHead_Explain;
   	Buf++;
	if((Buf1=SeekChar(Buf,'\"',Result,1))==NULL)  //解析错误
		return De_Erro_GprsHead_Explain;
	if((Buf[0]!='I')||(Buf[1]!='P'))
		return De_Erro_GprsHard_NoInitCONT;
	ptst_Data_IPNet=AgreeBuf;
	Buf1++;
	if((Buf=SeekChar(Buf1,'\"',Result,1))==NULL) 
		return De_Erro_GprsHead_Explain;
	Buf++;
	if((Buf1=SeekChar(Buf,'\"',Result,1))==NULL) 
		return De_Erro_GprsHead_Explain;
	CN_st_Fun_AscNumber.MoveByte(ptst_Data_IPNet->APN,Buf,Buf1-Buf);
	return De_Suc_GprsHard;			 
}
static uint16 Huawei_SendExtension(void *SendBuf,uint16 SizeofSendBuf,void *AgreeBuf,uint16 *SizeofAgreeBuf,st_GprsHard_Order_Cut	*ptst_GprsHard_Order_Cut)
{	uint8 *Buf;
	uint16 DataLen;
	Buf=SendBuf;AgreeBuf=AgreeBuf;
	DataLen=CN_st_Fun_AscNumber.Strsize16(Buf);
	CN_st_Fun_AscNumber.MoveByte(X_BUF,Buf,DataLen);
	X_BUF[DataLen]=0;
	return ModermCom(X_BUF,X_BUF,SizeofX_BUF,ptst_GprsHard_Order_Cut);
}
static uint16 Huawei_SetVolume(void *SendBuf,uint16 SizeofSendBuf,void *AgreeBuf,uint16 *SizeofAgreeBuf,st_GprsHard_Order_Cut	*ptst_GprsHard_Order_Cut)
{	uint8 *Buf;
	Buf=SendBuf;AgreeBuf=AgreeBuf;
	X_BUF[0]=*Buf;
	X_BUF[1]=0;
	return ModermCom(X_BUF,X_BUF,SizeofX_BUF,ptst_GprsHard_Order_Cut);
}
/*=======================================命令解析时所用函数=====================================================*/
static void ClearNoDisplay(uint8 *Buf)
{	uint16 DataLen,i;
	DataLen=CN_st_Fun_AscNumber.Strsize16(Buf);
	for(i=0;i<DataLen;)
	{	if(Buf[i]>0x20)
		{	i++;
			continue;
		}
		CN_st_Fun_AscNumber.MoveByte(Buf+i,Buf+i+1,DataLen-i-1);
		Buf[DataLen-1]=0;
		DataLen--;
	}
}
static	uint8 *SeekChar(uint8 *Buf,uint8 CharV,uint16 SizeofBuf,uint8 Number) 	   
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

