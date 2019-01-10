#define De_Tz_Agreen_Compiler
#include "Tz_Agreen.h"
static uint16 Explain(uint8 *Buf,void *OutBuf,uint16 DataLen,uint16 ID)
 {	uint16 i;
	for(i=0;i<sizeof(CN_Ba_st_Tz_Agreen_FunOper)/sizeof(st_Tz_Agreen_FunOper);i++)
	{	if(CN_Ba_st_Tz_Agreen_FunOper[i].ID==ID)
		{	if(CN_Ba_st_Tz_Agreen_FunOper[i].Read!=NULL)
				CN_Ba_st_Tz_Agreen_FunOper[i].Read(Buf,OutBuf,DataLen);
		 	return De_Suc_Tz_Agreen;
		}	
	}
	return De_Erro_Tz_Agreen_NoEdit;
}
/*===========================================基本协议==========================================================*/
/*----------------------------------------------定位指令-------------------------------------------------------*/
static void Explain_Answer(uint8 *Buf,void *OutBuf,uint16 DataLen)	  	//应答指令
{	st_AgreeOn_Agree_Answer	*ptst_AgreeOn_Agree_Answer;
	ptst_AgreeOn_Agree_Answer=OutBuf;
	ptst_AgreeOn_Agree_Answer->Number=Buf[0]*0x100+Buf[1];
	ptst_AgreeOn_Agree_Answer->ID=Buf[2]*0x100+Buf[3];
	ptst_AgreeOn_Agree_Answer->Result=Buf[4];		
}
/*------------------------------------------------追踪指令------------------------------------------------------*/
static void Explain_Track(uint8 *Buf,void *OutBuf,uint16 DataLen)		//追踪指令
{	st_AgreeOn_Agree_Track	*ptst_AgreeOn_Agree_Track;
	ptst_AgreeOn_Agree_Track=OutBuf;
	ptst_AgreeOn_Agree_Track->ComMod=Buf[0];
	ptst_AgreeOn_Agree_Track->AccOpenTimer=Buf[1]*0x100+Buf[2];
	ptst_AgreeOn_Agree_Track->AccCloseTimer=Buf[3]*0x100+Buf[4];	
	ptst_AgreeOn_Agree_Track->Space=Buf[5]*0x100+Buf[6];
}
/*------------------------------------------------设定参数------------------------------------------------------*/
static void Explain_SetPar(uint8 *Buf,void *OutBuf,uint16 DataLen)
{	st_AgreeOn_Agree_Par	*ptst_AgreeOn_Agree_Par;
	uint16 ParDataLen,WorkPar,j,i;
	ptst_AgreeOn_Agree_Par=OutBuf;
	for(i=0;i<DataLen;i+=(ParDataLen+3))
	{	WorkPar=Buf[i]*0x100+Buf[i+1];
		ParDataLen=Buf[i+2];
		for(j=0;j<sizeof(CN_Ba_st_AgreenOn_Par2Type)/sizeof(st_AgreenOn_Par2Type);j++)
		{	if(CN_Ba_st_AgreenOn_Par2Type[j].Par==WorkPar)
				break;
		}
		if(j==sizeof(CN_Ba_st_AgreenOn_Par2Type)/sizeof(st_AgreenOn_Par2Type))
			continue;
		Explain_Par(Buf+3+i,&ptst_AgreeOn_Agree_Par->CN_st_AgreeOn_Agree_Par_Cut,WorkPar,ParDataLen);
		ptst_AgreeOn_Agree_Par->ParSet[j]=De_AgreeOn_SetPar_Yes;
	}
}
/*-----------------------------------------解除报警------------------------------------------------------------*/
	//内容为空
/*---------------------------------------------修改固定菜单----------------------------------------------------*/
static void Explain_AmendMenum(uint8 *Buf,void *OutBuf,uint16 DataLen)	 //修改固定菜单
{	st_AgreeOn_AmendMenum	*ptst_AgreeOn_AmendMenum;
	uint16 ParDataLen,i;
	ptst_AgreeOn_AmendMenum=OutBuf;
	CN_st_Fun_AscNumber.ClsArray(ptst_AgreeOn_AmendMenum,sizeof(st_AgreeOn_AmendMenum));
	for(i=0,ptst_AgreeOn_AmendMenum->Number=0;i<DataLen;ptst_AgreeOn_AmendMenum->Number++)
	{	ptst_AgreeOn_AmendMenum->CN_st_AgreeOn_Menum_Infor[ptst_AgreeOn_AmendMenum->Number].ID=Buf[i];
		ptst_AgreeOn_AmendMenum->CN_st_AgreeOn_Menum_Infor[ptst_AgreeOn_AmendMenum->Number].BackID=Buf[i+1];
		ParDataLen=Buf[i+2];
		if(ParDataLen>40)
			ParDataLen=40;
	   	CN_st_Fun_AscNumber.MoveByte(ptst_AgreeOn_AmendMenum->CN_st_AgreeOn_Menum_Infor[ptst_AgreeOn_AmendMenum->Number]
		.Cut,Buf+(3+i),ParDataLen);
		ParDataLen=Buf[i+2];
		i=i+ParDataLen+3;
	}
}
/*-------------------------------------------下发文本调度------------------------------------------------------*/
static void Explain_LoaderTxt(uint8 *Buf,void *OutBuf,uint16 DataLen)		//下发文本调度
{  	st_AgreeOn_LoaderTxt	*ptst_AgreeOn_LoaderTxt;
	ptst_AgreeOn_LoaderTxt=OutBuf;
	CN_st_Fun_AscNumber.ClsArray(ptst_AgreeOn_LoaderTxt,sizeof(st_AgreeOn_LoaderTxt));
   	if(DataLen>sizeof(ptst_AgreeOn_LoaderTxt->Text))
		DataLen=sizeof(ptst_AgreeOn_LoaderTxt->Text);
	CN_st_Fun_AscNumber.MoveByte(ptst_AgreeOn_LoaderTxt->Text,Buf,DataLen);
}
/*----------------------------------------下发带文本的菜单-----------------------------------------------------*/
static void Explain_LoaderTxtMenum(uint8 *Buf,void *OutBuf,uint16 DataLen)	//下发带文本的菜单
{	st_AgreeOn_LoaderTxtMenum	*ptst_AgreeOn_LoaderTxtMenum;
	uint16 ParLen,i;
	ptst_AgreeOn_LoaderTxtMenum=OutBuf;
	CN_st_Fun_AscNumber.ClsArray(ptst_AgreeOn_LoaderTxtMenum,sizeof(st_AgreeOn_LoaderTxtMenum));
	ptst_AgreeOn_LoaderTxtMenum->ID=Buf[0]*0x100+Buf[1];
   	ParLen=Buf[2];
	if(ParLen>sizeof(ptst_AgreeOn_LoaderTxtMenum->Infor))
		ParLen=sizeof(ptst_AgreeOn_LoaderTxtMenum->Infor);
	CN_st_Fun_AscNumber.MoveByte(ptst_AgreeOn_LoaderTxtMenum->Infor,Buf+3,ParLen);
	ParLen=Buf[2]+3;
	for(i=ParLen,ptst_AgreeOn_LoaderTxtMenum->AnswerNumber=0;i<DataLen;ptst_AgreeOn_LoaderTxtMenum->AnswerNumber++)
	{	ptst_AgreeOn_LoaderTxtMenum->CN_st_AgreeOn_LoaderTxtMenum_Par[ptst_AgreeOn_LoaderTxtMenum->AnswerNumber].ID=Buf[i];
		ParLen=Buf[i+1];
		if(ParLen>sizeof(ptst_AgreeOn_LoaderTxtMenum->CN_st_AgreeOn_LoaderTxtMenum_Par[0].Cut))
			ParLen=sizeof(ptst_AgreeOn_LoaderTxtMenum->CN_st_AgreeOn_LoaderTxtMenum_Par[0].Cut);	
		CN_st_Fun_AscNumber.MoveByte(ptst_AgreeOn_LoaderTxtMenum->CN_st_AgreeOn_LoaderTxtMenum_Par[ptst_AgreeOn_LoaderTxtMenum->AnswerNumber].Cut,
		Buf+i+2,ParLen);
		ParLen=Buf[i+1]+2;
		i+=ParLen;
	}
}
/*------------------------------------------设置固定电话------------------------------------------------------*/
static void Explain_SetPhone(uint8 *Buf,void *OutBuf,uint16 DataLen)	//设置固定电话
{ 	st_AgreeOn_Phone	*ptst_AgreeOn_Phone;
	uint16 i;
	uint8 Len;
	ptst_AgreeOn_Phone=OutBuf;
	CN_st_Fun_AscNumber.ClsArray(ptst_AgreeOn_Phone,sizeof(st_AgreeOn_Phone));
	for(i=0,ptst_AgreeOn_Phone->Number=0;(i<DataLen)&&
	(ptst_AgreeOn_Phone->Number<(sizeof(ptst_AgreeOn_Phone->CN_st_AgreeOn_Phone_Par)/sizeof(st_AgreeOn_Phone_Par)));ptst_AgreeOn_Phone->Number++)
	{	ptst_AgreeOn_Phone->CN_st_AgreeOn_Phone_Par[ptst_AgreeOn_Phone->Number].State=Buf[i];
		CN_st_Fun_AscNumber.MoveByte(ptst_AgreeOn_Phone->CN_st_AgreeOn_Phone_Par[ptst_AgreeOn_Phone->Number].Name,
		Buf+i+1,8);
		Len=Buf[i+9];
		if(Len>sizeof(ptst_AgreeOn_Phone->CN_st_AgreeOn_Phone_Par[0].Phone))
			Len=sizeof(ptst_AgreeOn_Phone->CN_st_AgreeOn_Phone_Par[0].Phone);
		CN_st_Fun_AscNumber.MoveByte(ptst_AgreeOn_Phone->CN_st_AgreeOn_Phone_Par[ptst_AgreeOn_Phone->Number].Phone,
		Buf+i+10,Len);
		Len=10+Buf[i+9];
		i+=Len;		
	}	
}
/*--------------------------------------------通话请求--------------------------------------------------------*/
static void Explain_CallAnswer(uint8 *Buf,void *OutBuf,uint16 DataLen)			//通话请求
{	st_AgreeOn_CallAnswer	*ptst_AgreeOn_CallAnswer;
	ptst_AgreeOn_CallAnswer=OutBuf;
   	CN_st_Fun_AscNumber.ClsArray(ptst_AgreeOn_CallAnswer,sizeof(st_AgreeOn_CallAnswer));
	if(DataLen>sizeof(ptst_AgreeOn_CallAnswer->Phone))
		DataLen=sizeof(ptst_AgreeOn_CallAnswer->Phone);
   	CN_st_Fun_AscNumber.MoveByte(ptst_AgreeOn_CallAnswer->Phone,Buf,DataLen);
}
/*--------------------------------------------软件升级--------------------------------------------------------*/
static void Explain_UpdateSoftWare(uint8 *Buf,void *OutBuf,uint16 DataLen)		//软件升级
{	uint8 Asc[20];
	st_AgreeOn_UpdateSoftWare	*ptst_AgreeOn_UpdateSoftWare;
	uint16 Len,Point;
	CN_st_Fun_AscNumber.ClsArray(Asc,sizeof(Asc));
	ptst_AgreeOn_UpdateSoftWare=OutBuf;
   	ptst_AgreeOn_UpdateSoftWare->Device=Buf[0];
	Len=Buf[1];
	if(Len>=sizeof(Asc))
		Len=sizeof(Asc)-1;
	CN_st_Fun_AscNumber.MoveByte(Asc,Buf+2,Len);
	CN_st_Fun_AscNumber.Char2IP(Asc,&ptst_AgreeOn_UpdateSoftWare->IP,'.');
	Point=Buf[1]+2;
	ptst_AgreeOn_UpdateSoftWare->Port=Buf[Point]*0x100+Buf[Point+1];
	Point+=2;
	Len=Buf[Point];
	if(Len>sizeof(ptst_AgreeOn_UpdateSoftWare->Use))
		Len=sizeof(ptst_AgreeOn_UpdateSoftWare->Use);
   	CN_st_Fun_AscNumber.MoveByte(ptst_AgreeOn_UpdateSoftWare->Use,Buf+Point+1,Len);
	Len=Buf[Point];
	Point=Point+Len+1;

	Len=Buf[Point];
	if(Len>sizeof(ptst_AgreeOn_UpdateSoftWare->Pass))
		Len=sizeof(ptst_AgreeOn_UpdateSoftWare->Pass);
   	CN_st_Fun_AscNumber.MoveByte(ptst_AgreeOn_UpdateSoftWare->Pass,Buf+Point+1,Len);
	Len=Buf[Point];
	Point=Point+Len+1;

	Len=Buf[Point];
	if(Len>sizeof(ptst_AgreeOn_UpdateSoftWare->FileName))
		Len=sizeof(ptst_AgreeOn_UpdateSoftWare->FileName);
   	CN_st_Fun_AscNumber.MoveByte(ptst_AgreeOn_UpdateSoftWare->FileName,Buf+Point+1,Len);
}
/*--------------------------------------------查询参数-------------------------------------------------------*/
static void Explain_LookPar(uint8 *Buf,void *OutBuf,uint16 DataLen)
{	st_AgreeOn_LookPar	*ptst_AgreeOn_LookPar;
	uint16 ParWord,i,j;
	ptst_AgreeOn_LookPar=OutBuf;
	for(i=0;i<De_AgreeOn_SetPar_Number;i++)
		ptst_AgreeOn_LookPar->Par[i]=De_AgreeOn_LookPar_NO;	
	for(i=0;i<DataLen;i+=2)
	{	ParWord=Buf[i]*0x100+Buf[i+1];
		for(j=0;j<(sizeof(CN_Ba_st_AgreenOn_Par2Type)/sizeof(st_AgreenOn_Par2Type));j++)
		{	if(ParWord==CN_Ba_st_AgreenOn_Par2Type[j].Par)
				break;
		}
		if(j==sizeof(CN_Ba_st_AgreenOn_Par2Type)/sizeof(st_AgreenOn_Par2Type))
			continue;
		ptst_AgreeOn_LookPar->Par[CN_Ba_st_AgreenOn_Par2Type[j].Number]=De_AgreeOn_LookPar_Yes;
	}
}
/*---------------------------------------------远程控制------------------------------------------------------*/
static void Explain_Contrl(uint8 *Buf,void *OutBuf,uint16 DataLen)		 	//远程控制
{	st_AgreeOn_Contrl	*ptst_AgreeOn_Contrl;
	ptst_AgreeOn_Contrl=OutBuf;
	CN_st_Fun_AscNumber.ClsArray(ptst_AgreeOn_Contrl,sizeof(st_AgreeOn_Contrl));  	
	ptst_AgreeOn_Contrl->Contr0=Buf[0];
    ptst_AgreeOn_Contrl->Contr1=Buf[1];
	ptst_AgreeOn_Contrl->Contr2=Buf[2];
}
/*--------------------------------------------通话限制状态--------------------------------------------------*/
static void Explain_ConfineCall(uint8 *Buf,void *OutBuf,uint16 DataLen)		//通话限制状态
{	st_AgreeOn_ConfineCall	*ptst_AgreeOn_ConfineCall;
	uint8 Len;
	 ptst_AgreeOn_ConfineCall=OutBuf;
	CN_st_Fun_AscNumber.ClsArray(ptst_AgreeOn_ConfineCall,sizeof(st_AgreeOn_ConfineCall));
	ptst_AgreeOn_ConfineCall->State=Buf[0];
   	Len=Buf[1];
	if(Len>sizeof(ptst_AgreeOn_ConfineCall->Phone))
		Len=sizeof(ptst_AgreeOn_ConfineCall->Phone);
   	CN_st_Fun_AscNumber.MoveByte(ptst_AgreeOn_ConfineCall->Phone,Buf+2,Len);
}
/*--------------------------------------------配置中心服务器------------------------------------------------*/
static void Explain_ConfigCentrSever(uint8 *Buf,void *OutBuf,uint16 DataLen)//配置中心服务器状态
{	st_AgreeOn_ConfigCentrSever	*ptst_AgreeOn_ConfigCentrSever;
	uint8 Len;
	ptst_AgreeOn_ConfigCentrSever=OutBuf;
	CN_st_Fun_AscNumber.ClsArray(ptst_AgreeOn_ConfigCentrSever,sizeof(st_AgreeOn_ConfigCentrSever));
	Len=Buf[0];
	if(Len>sizeof(ptst_AgreeOn_ConfigCentrSever->APN))
		Len=sizeof(ptst_AgreeOn_ConfigCentrSever->APN);
	CN_st_Fun_AscNumber.MoveByte(ptst_AgreeOn_ConfigCentrSever->APN,Buf+1,Len);
	Len=1+Buf[0];
	ptst_AgreeOn_ConfigCentrSever->IP=Buf[Len]*0X1000000+Buf[Len+1]*0X10000+Buf[Len+2]*0X100+Buf[Len+3];
	Len+=4;
   	ptst_AgreeOn_ConfigCentrSever->Port=Buf[Len]*0X100+Buf[Len+1];
}
/*--------------------------------------------激活定位终端----------------------------------------------------*/
static void Explain_Activation(uint8 *Buf,void *OutBuf,uint16 DataLen)		//激活定位终端
{	st_AgreeOn_Activation	*ptst_AgreeOn_Activation;
	ptst_AgreeOn_Activation=OutBuf;
	ptst_AgreeOn_Activation->PassWord=Buf[0]*0x1000000+Buf[1]*0x10000+Buf[2]*0x100+Buf[3];
}

/*============================================功能扩展协议======================================================*/
/*---------------------------------------------查询指定类型的照片--------------------------------------------*/
static void Explain_LookJpg(uint8 *Buf,void *OutBuf,uint16 DataLen)	//查询指定类型的照片
{	st_AgreeOn_LookJpg	*ptst_AgreeOn_LookJpg;
	uint16 WorkID,i;
	ptst_AgreeOn_LookJpg=OutBuf;
	CN_st_Fun_AscNumber.ClsArray(ptst_AgreeOn_LookJpg,sizeof(st_AgreeOn_LookJpg));
   	ptst_AgreeOn_LookJpg->CN_st_VidType.HelpWarning=De_AgreeOn_Vid_Fun_Close;
	if(Buf[1]&0x01)	   //紧急报警
		ptst_AgreeOn_LookJpg->CN_st_VidType.HelpWarning=De_AgreeOn_Vid_Fun_Open;
	ptst_AgreeOn_LookJpg->CN_st_VidType.Oper=De_AgreeOn_Vid_Fun_Close;
	if(Buf[1]&0x02)	   //发动机运转
		ptst_AgreeOn_LookJpg->CN_st_VidType.Oper=De_AgreeOn_Vid_Fun_Open;		
	ptst_AgreeOn_LookJpg->CN_st_VidType.TurnOver=De_AgreeOn_Vid_Fun_Close;
	if(Buf[1]&0x04)	  //侧翻
		ptst_AgreeOn_LookJpg->CN_st_VidType.TurnOver=De_AgreeOn_Vid_Fun_Open;
	ptst_AgreeOn_LookJpg->CN_st_VidType.AccOpen=De_AgreeOn_Vid_Fun_Close;
	if(Buf[1]&0x08)	 //ACC打开
		ptst_AgreeOn_LookJpg->CN_st_VidType.AccOpen=De_AgreeOn_Vid_Fun_Open;
	ptst_AgreeOn_LookJpg->CN_st_VidType.AccClose=De_AgreeOn_Vid_Fun_Close;
	if(Buf[1]&0x10)	//ACC关闭
		ptst_AgreeOn_LookJpg->CN_st_VidType.AccClose=De_AgreeOn_Vid_Fun_Open;
   	WorkID=Buf[2]*0x100+Buf[3];
	for(i=0;i<(sizeof(CN_Ba_WordPar)/sizeof(uint16));i++)
	{	if(WorkID==CN_Ba_WordPar[i])
			break;
	}
	ptst_AgreeOn_LookJpg->WorkPar=i;
	ptst_AgreeOn_LookJpg->StartDate[0]=0X20;
	CN_st_Fun_AscNumber.Hex2Bcd(Buf+4,ptst_AgreeOn_LookJpg->StartDate+1,3);
	ptst_AgreeOn_LookJpg->EndDate[0]=0X20;
	CN_st_Fun_AscNumber.Hex2Bcd(Buf+7,ptst_AgreeOn_LookJpg->EndDate+1,3);
}
/*--------------------------------------------查询实时照片----------------------------------------------------*/
static void Explain_JpgIng(uint8 *Buf,void *OutBuf,uint16 DataLen)	//查询实时照片
{	st_AgreeOn_JpgIng	*ptst_AgreeOn_JpgIng;
	ptst_AgreeOn_JpgIng=OutBuf;
	ptst_AgreeOn_JpgIng->Contrl=Buf[0];
	ptst_AgreeOn_JpgIng->VidTimer=Buf[1];
	ptst_AgreeOn_JpgIng->LoadNumber=Buf[2]*0x100+Buf[3];
}
/*---------------------------------------------设置拍照类型---------------------------------------------------*/
static void Explain_SetVidType(uint8 *Buf,void *OutBuf,uint16 DataLen)	//设置拍照类型
{	uint16 i,WorkID,Len;
	uint8 j,k;
	st_AgreeOn_SetVidType	*ptst_AgreeOn_SetVidType;
	ptst_AgreeOn_SetVidType=(st_AgreeOn_SetVidType *)OutBuf;
	memset(ptst_AgreeOn_SetVidType->Type,De_AgreeOn_SetVidType_Type_No,sizeof(ptst_AgreeOn_SetVidType->Type));
	for(i=0;i<DataLen;)
	{	WorkID=Buf[i]*0x100+Buf[i+1];
		Len=Buf[i+3];
		for(j=0;j<(sizeof(CN_Ba_WordPar)/sizeof(uint16));j++)
		{	if(WorkID==CN_Ba_WordPar[j])
				break;
		}
		ptst_AgreeOn_SetVidType->Type[j]=Buf[i+2];
		k=ptst_AgreeOn_SetVidType->Type[j];
		Explain_WorkPar(Buf+4+i,(st_AgreeOn_SetVidType *)OutBuf,WorkID,Len,k);
		i+=Len+4;	
	}
}
/*------------------------------------------------表单设置------------------------------------------------------*/
static void Explain_TabelList(uint8 *Buf,void *OutBuf,uint16 DataLen)	//设置表单
{	st_AgreeOn_TabelList	*ptst_AgreeOn_TabelList;
	uint16 Len,j,Len1,k,Len2,m                               ;
	uint8 Len3;
	ptst_AgreeOn_TabelList=OutBuf;
	ptst_AgreeOn_TabelList->DateTime[0]=0x20;
	CN_st_Fun_AscNumber.Hex2Bcd(Buf,ptst_AgreeOn_TabelList->DateTime+1,6);
	ptst_AgreeOn_TabelList->SumNumber=Buf[6];
	ptst_AgreeOn_TabelList->Number=Buf[7];
	ptst_AgreeOn_TabelList->TabelID=Buf[8]*0x1000000+Buf[9]*0x10000+Buf[10]*0x100+Buf[11];
	ptst_AgreeOn_TabelList->BackID=Buf[12]*0x1000000+Buf[13]*0x10000+Buf[14]*0x100+Buf[15];
	Len=Buf[16];
	if(Len>sizeof(ptst_AgreeOn_TabelList->Name))
		Len=sizeof(ptst_AgreeOn_TabelList->Name);
	CN_st_Fun_AscNumber.MoveByte(ptst_AgreeOn_TabelList->Name,Buf+17,Len);
	Len=Buf[16];
	Len=17+Len;
	for(j=0;((Len<DataLen)&&(j<
		sizeof(ptst_AgreeOn_TabelList->CN_st_AgreeOn_Tabel_Input)/sizeof(st_AgreeOn_Tabel_Input)));Len=Len+Len2,j++)					//输入项解析
	{	Len2=Buf[Len]*0x100+Buf[Len+1];
		ptst_AgreeOn_TabelList->CN_st_AgreeOn_Tabel_Input[j].ID=Buf[Len+2];
		ptst_AgreeOn_TabelList->CN_st_AgreeOn_Tabel_Input[j].Type=Buf[Len+3];
		ptst_AgreeOn_TabelList->CN_st_AgreeOn_Tabel_Input[j].Select=Buf[Len+4];
		Len1=Buf[Len+5];
		if(Len1>sizeof(ptst_AgreeOn_TabelList->CN_st_AgreeOn_Tabel_Input[0].Name))
			Len1=sizeof(ptst_AgreeOn_TabelList->CN_st_AgreeOn_Tabel_Input[0].Name);
	   	CN_st_Fun_AscNumber.MoveByte(ptst_AgreeOn_TabelList->CN_st_AgreeOn_Tabel_Input[j].Name,Buf+Len+6,Len1);
		Len1=Buf[Len+5]+6;
		for(k=0,m=0;((k<(Len2-Len1))&&(m<10));k=k+Len3+2,m++)
		{	ptst_AgreeOn_TabelList->CN_st_AgreeOn_Tabel_Input[j].InputID[m]=Buf[Len1+Len+k];
			Len3=Buf[Len1+Len+k+1];
			if(Len3>40)
				Len3=40;
			CN_st_Fun_AscNumber.MoveByte(ptst_AgreeOn_TabelList->CN_st_AgreeOn_Tabel_Input[j].SelectName[m],
			Buf+Len1+Len+k+2,Len3);
			Len3=Buf[Len1+k+1+Len];
		}			
	}
}
/*--------------------------------------------查询工作参数------------------------------------------------------*/
	//<内容为空>
/*-------------------------------------按照间隔上传工作参数-----------------------------------------------------*/
static void Explain_WorkParTimer(uint8 *Buf,void *OutBuf,uint16 DataLen)	//按照固定时间上传工作参数
{	st_AgreeOn_WorkParTimer	*ptst_AgreeOn_WorkParTimer;
	uint16 i;
	uint8 j;
	ptst_AgreeOn_WorkParTimer=OutBuf;
	ptst_AgreeOn_WorkParTimer->Com=Buf[0];
	for(i=1,j=0;((i<DataLen)&&(j<10));i=i+2,j++)
	{	CN_st_Fun_AscNumber.Hex2Bcd(Buf+i,ptst_AgreeOn_WorkParTimer->Timer[j],2);
		ptst_AgreeOn_WorkParTimer->Timer[j][2]=0x00;
		ptst_AgreeOn_WorkParTimer->Number=j;
	}
}
/*-------------------------------------按照间隔上传工作参数-----------------------------------------------------*/
static void Explain_WorkParSpace(uint8 *Buf,void *OutBuf,uint16 DataLen)	//按照间隔上传工作参数
{	st_AgreeOn_WorkParSpace	*ptst_AgreeOn_WorkParSpace;
	ptst_AgreeOn_WorkParSpace=OutBuf;
   	ptst_AgreeOn_WorkParSpace->Com=Buf[0];
	ptst_AgreeOn_WorkParSpace->AccOpenTimer=Buf[1]*0x100+Buf[2];
	ptst_AgreeOn_WorkParSpace->AccCloseTimer=Buf[3]*0x100+Buf[4];
	ptst_AgreeOn_WorkParSpace->Space=Buf[5]*0x100+Buf[6];	
}
/*----------------------------------------查询日志文件---------------------------------------------------------*/
static void Explain_LookLog(uint8 *Buf,void *OutBuf,uint16 DataLen)		//查询日志文件
{	st_AgreeOn_LookLog	*ptst_AgreeOn_LookLog;
	ptst_AgreeOn_LookLog=OutBuf;
	ptst_AgreeOn_LookLog->Type=Buf[0];
	ptst_AgreeOn_LookLog->StartDateTimer[0]=0x20;
	CN_st_Fun_AscNumber.Hex2Bcd(Buf+1,ptst_AgreeOn_LookLog->StartDateTimer+1,6);
	ptst_AgreeOn_LookLog->EndDateTimer[0]=0x20;
	CN_st_Fun_AscNumber.Hex2Bcd(Buf+7,ptst_AgreeOn_LookLog->EndDateTimer+1,6);
}
/*--------------------------------------------设置报警条件----------------------------------------------------*/
static void Explain_SetWaringTerm(uint8 *Buf,void *OutBuf,uint16 DataLen)	//设置报警条件
{	uint16 i,WorkID,Len;
	uint8 j,k;
	st_AgreeOn_SetVidType	*ptst_AgreeOn_SetVidType;
	ptst_AgreeOn_SetVidType=(st_AgreeOn_SetVidType *)OutBuf;
	memset(ptst_AgreeOn_SetVidType->Type,De_AgreeOn_SetVidType_Type_No,sizeof(ptst_AgreeOn_SetVidType->Type));
	for(i=0;i<DataLen;)
	{	WorkID=Buf[i]*0x100+Buf[i+1];
		Len=Buf[i+3];
		for(j=0;j<(sizeof(CN_Ba_WordPar)/sizeof(uint16));j++)
		{	if(WorkID==CN_Ba_WordPar[j])
				break;
		}
		ptst_AgreeOn_SetVidType->Type[j]=Buf[i+2];
		k=ptst_AgreeOn_SetVidType->Type[j];
		Explain_WorkPar(Buf+4+i,(st_AgreeOn_SetVidType *)OutBuf,WorkID,Len,k);
		i+=Len+4;	
	}
}

/*---------------------------------------------查询报警条件--------------------------------------------------*/
	//<内容为空>
/*=================================================物流协议专用==============================================*/
/*---------------------------------------------设置圆形路线--------------------------------------------------*/
static void Explain_SetRound(uint8 *Buf,void *OutBuf,uint16 DataLen)//设置圆形路线
{	st_AgreeOn_SetRound	*ptst_AgreeOn_SetRound;
	uint16 Number,i,Len;
	ptst_AgreeOn_SetRound=OutBuf;
	Number=Buf[0]*0x100+Buf[1];
	for(i=0,Len=2;((i<Number)&&(i<sizeof(ptst_AgreeOn_SetRound->CN_st_AgreeOn_SetRound_Par)/sizeof(st_AgreeOn_SetRound_Par)));i++,Len=Len+25)
	{	ptst_AgreeOn_SetRound->CN_st_AgreeOn_SetRound_Par[i].ID=Buf[Len]*0x100+Buf[Len+1];
		ptst_AgreeOn_SetRound->CN_st_AgreeOn_SetRound_Par[i].Pro=Buf[Len+2]*0x100+Buf[Len+3];
	   	ptst_AgreeOn_SetRound->CN_st_AgreeOn_SetRound_Par[i].Latitude=Buf[Len+4]*0x1000000+
		Buf[Len+5]*0x10000+Buf[Len+6]*0x100+Buf[Len+7];
		ptst_AgreeOn_SetRound->CN_st_AgreeOn_SetRound_Par[i].Longitude=Buf[Len+8]*0x1000000+
		Buf[Len+9]*0x10000+Buf[Len+10]*0x100+Buf[Len+11];
		ptst_AgreeOn_SetRound->CN_st_AgreeOn_SetRound_Par[i].PI=Buf[Len+12]*0x1000000+
		Buf[Len+13]*0x10000+Buf[Len+14]*0x100+Buf[Len+15];
		CN_st_Fun_AscNumber.Hex2Bcd(Buf+Len+16,ptst_AgreeOn_SetRound->CN_st_AgreeOn_SetRound_Par[i].StartTimer,3);
	   	CN_st_Fun_AscNumber.Hex2Bcd(Buf+Len+19,ptst_AgreeOn_SetRound->CN_st_AgreeOn_SetRound_Par[i].EndTimer,3);
	   	ptst_AgreeOn_SetRound->CN_st_AgreeOn_SetRound_Par[i].HighSpeed=Buf[22+Len];
		ptst_AgreeOn_SetRound->CN_st_AgreeOn_SetRound_Par[i].HighSpeedTimer=Buf[23+Len]*0x100+Buf[Len+24];
	}
	ptst_AgreeOn_SetRound->Number=i;
}
/*--------------------------------------删除圆形路线-----------------------------------------------------------*/
static void Explain_DelRound(uint8 *Buf,void *OutBuf,uint16 DataLen) //删除圆形路线
{	st_AgreeOn_DelRound	*ptst_AgreeOn_DelRound;	  	
	uint16 Len;
	uint8 i,Number;
	ptst_AgreeOn_DelRound=OutBuf;
	Number=Buf[0];
	for(i=0,Len=1;(i<Number&&(i<(sizeof(ptst_AgreeOn_DelRound->ID)/sizeof(uint16))));i++,Len+=2)
		ptst_AgreeOn_DelRound->ID[i]=Buf[Len]*0x100+Buf[Len+1];
	ptst_AgreeOn_DelRound->Number=i;		
}
/*---------------------------------------------------设置矩形路线----------------------------------------------*/
static void Explain_SetRectangle(uint8 *Buf,void *OutBuf,uint16 DataLen) //设置矩形路线
{	st_AgreeOn_SetRectangle	*ptst_AgreeOn_SetRectangle;
	uint16 Number,i,Len;
	ptst_AgreeOn_SetRectangle=OutBuf;
	Number=Buf[0]*0x100+Buf[1];
	for(i=0,Len=2;((i<Number)&&(i<sizeof(ptst_AgreeOn_SetRectangle->CN_st_AgreeOn_SetRectangle_Par)/sizeof(st_AgreeOn_SetRectangle_Par)));i++,Len=Len+29)
	{	ptst_AgreeOn_SetRectangle->CN_st_AgreeOn_SetRectangle_Par[i].ID=Buf[Len]*0x100+Buf[Len+1];
		ptst_AgreeOn_SetRectangle->CN_st_AgreeOn_SetRectangle_Par[i].Pro=Buf[Len+2]*0x100+Buf[Len+3];
	   	ptst_AgreeOn_SetRectangle->CN_st_AgreeOn_SetRectangle_Par[i].Latitude[0]=Buf[Len+4]*0x1000000+
		Buf[Len+5]*0x10000+Buf[Len+6]*0x100+Buf[Len+7];
		ptst_AgreeOn_SetRectangle->CN_st_AgreeOn_SetRectangle_Par[i].Latitude[1]=Buf[Len+8]*0x1000000+
		Buf[Len+9]*0x10000+Buf[Len+10]*0x100+Buf[Len+11];
		ptst_AgreeOn_SetRectangle->CN_st_AgreeOn_SetRectangle_Par[i].Longitude[0]=Buf[Len+12]*0x1000000+
		Buf[Len+13]*0x10000+Buf[Len+14]*0x100+Buf[Len+15];
		ptst_AgreeOn_SetRectangle->CN_st_AgreeOn_SetRectangle_Par[i].Longitude[1]=Buf[Len+16]*0x1000000+
		Buf[Len+17]*0x10000+Buf[Len+18]*0x100+Buf[Len+19];
		CN_st_Fun_AscNumber.Hex2Bcd(Buf+Len+20,ptst_AgreeOn_SetRectangle->CN_st_AgreeOn_SetRectangle_Par[i].StartTimer,3);
	   	CN_st_Fun_AscNumber.Hex2Bcd(Buf+Len+23,ptst_AgreeOn_SetRectangle->CN_st_AgreeOn_SetRectangle_Par[i].EndTimer,3);
	   	ptst_AgreeOn_SetRectangle->CN_st_AgreeOn_SetRectangle_Par[i].HighSpeed=Buf[26+Len];
		ptst_AgreeOn_SetRectangle->CN_st_AgreeOn_SetRectangle_Par[i].HighSpeedTimer=Buf[27+Len]*0x100+Buf[Len+28];
	}
	ptst_AgreeOn_SetRectangle->Number=i;
}
/*--------------------------------------删除矩形路线-----------------------------------------------------------*/
static void Explain_DelRectangle(uint8 *Buf,void *OutBuf,uint16 DataLen) //删除矩形路线
{	st_AgreeOn_DelRectangle	*ptst_AgreeOn_DelRound;	  	
	uint16 Len;
	uint8 i,Number;
	ptst_AgreeOn_DelRound=OutBuf;
	Number=Buf[0];
	for(i=0,Len=1;(i<Number&&(i<(sizeof(ptst_AgreeOn_DelRound->ID)/sizeof(uint16))));i++,Len+=2)
		ptst_AgreeOn_DelRound->ID[i]=Buf[Len]*0x100+Buf[Len+1];
	ptst_AgreeOn_DelRound->Number=i;
}
/*------------------------------------------设置多边形路线----------------------------------------------------*/
static void Explain_SetPolygon(uint8 *Buf,void *OutBuf,uint16 DataLen)	//设置多边形路线
{	st_AgreeOn_SetPolygon	*ptst_AgreeOn_SetPolygon;
	uint16 Number,i,Len;
	ptst_AgreeOn_SetPolygon=OutBuf;
	ptst_AgreeOn_SetPolygon->ID=Buf[0]*0x100+Buf[1];
   	ptst_AgreeOn_SetPolygon->Pro=Buf[2]*0x100+Buf[3];
	CN_st_Fun_AscNumber.Hex2Bcd(Buf+4,ptst_AgreeOn_SetPolygon->StartTimer,3);
	CN_st_Fun_AscNumber.Hex2Bcd(Buf+7,ptst_AgreeOn_SetPolygon->EndTimer,3);
	ptst_AgreeOn_SetPolygon->HighSpeed=Buf[10];
	ptst_AgreeOn_SetPolygon->HighSpeedTimer=Buf[11]*0x100+Buf[12];
	Number=Buf[13]*0x100+Buf[14];
	ptst_AgreeOn_SetPolygon->Number=Number;
	for(i=0,Len=17;((i<Number)&&(i<sizeof(ptst_AgreeOn_SetPolygon->Latitude)/sizeof(uint32)));i++,Len+=8)
	{	ptst_AgreeOn_SetPolygon->Latitude[i]=Buf[Len]*0x1000000+Buf[Len+1]*0x10000+Buf[Len+2]*0x100+Buf[Len+3];
		ptst_AgreeOn_SetPolygon->Longitude[i]=Buf[Len+4]*0x1000000+Buf[Len+5]*0x10000+Buf[Len+6]*0x100+Buf[Len+7];
	}
}
/*--------------------------------------删除多边形路线-----------------------------------------------------------*/
static void Explain_DelPolygon(uint8 *Buf,void *OutBuf,uint16 DataLen)	//删除多边形路线
{ 	st_AgreeOn_DelRoadMap	*ptst_AgreeOn_DelRound;	  	
	uint16 Len;
	uint8 i,Number;
	ptst_AgreeOn_DelRound=OutBuf;
	Number=Buf[0];
	for(i=0,Len=1;(i<Number&&(i<(sizeof(ptst_AgreeOn_DelRound->ID)/sizeof(uint16))));i++,Len+=2)
		ptst_AgreeOn_DelRound->ID[i]=Buf[Len]*0x100+Buf[Len+1];
	ptst_AgreeOn_DelRound->Number=i;
}
/*--------------------------------------设置路线区域-----------------------------------------------------------*/
static void Explain_SetRoadMap(uint8 *Buf,void *OutBuf,uint16 DataLen)//设置路线区域
 {	st_AgreeOn_SetRoadMap	*ptst_AgreeOn_SetRoadMap;
	uint16 Number,i,Len;
	ptst_AgreeOn_SetRoadMap=OutBuf;
	ptst_AgreeOn_SetRoadMap->ID=Buf[0]*0x100+Buf[1];
   	ptst_AgreeOn_SetRoadMap->Pro=Buf[2]*0x100+Buf[3];
   	CN_st_Fun_AscNumber.Hex2Bcd(Buf+4,ptst_AgreeOn_SetRoadMap->StartTimer,3);
	CN_st_Fun_AscNumber.Hex2Bcd(Buf+7,ptst_AgreeOn_SetRoadMap->EndTimer,3);
	ptst_AgreeOn_SetRoadMap->HighSpeed=Buf[10];
	ptst_AgreeOn_SetRoadMap->HighSpeedTimer=Buf[11]*0x100+Buf[12];
	ptst_AgreeOn_SetRoadMap->Height=Buf[13]*0x100+Buf[14];
	Number=Buf[15]*0x100+Buf[16];
	ptst_AgreeOn_SetRoadMap->Number=Number;
    ptst_AgreeOn_SetRoadMap->SumSec=Buf[17];
	ptst_AgreeOn_SetRoadMap->NonSec=Buf[18];
	for(i=0,Len=19;((i<Number)&&(i<sizeof(ptst_AgreeOn_SetRoadMap->Latitude)/sizeof(uint32)));i++,Len+=8)
	{	ptst_AgreeOn_SetRoadMap->Latitude[i]=Buf[Len]*0x1000000+Buf[Len+1]*0x10000+Buf[Len+2]*0x100+Buf[Len+3];
		ptst_AgreeOn_SetRoadMap->Longitude[i]=Buf[Len+4]*0x1000000+Buf[Len+5]*0x10000+Buf[Len+6]*0x100+Buf[Len+7];
	}
}
/*-----------------------------------------删除路线区域----------------------------------------------------------*/
static void Explain_DelRoadMap(uint8 *Buf,void *OutBuf,uint16 DataLen)//删除路线区域
{ 	st_AgreeOn_DelRoadMap	*ptst_AgreeOn_DelRound;	  	
	uint16 Len;
	uint8 i,Number;
	ptst_AgreeOn_DelRound=OutBuf;
	Number=Buf[0];
	for(i=0,Len=1;(i<Number&&(i<(sizeof(ptst_AgreeOn_DelRound->ID)/sizeof(uint16))));i++,Len+=2)
		ptst_AgreeOn_DelRound->ID[i]=Buf[Len]*0x100+Buf[Len+1];
	ptst_AgreeOn_DelRound->Number=i;
}
/*---------------------------------------设置压缩回传-----------------------------------------------------------*/
static void Explain_Reduce(uint8 *Buf,void *OutBuf,uint16 DataLen) //设置压缩回传
{	st_AgreeOn_Reduce	*ptst_AgreeOn_Reduce;
	ptst_AgreeOn_Reduce=OutBuf;
	ptst_AgreeOn_Reduce->Data=Buf[0];
	ptst_AgreeOn_Reduce->AccOpenTimer=Buf[1];
	ptst_AgreeOn_Reduce->AccCloseTimer=Buf[2];
	ptst_AgreeOn_Reduce->Space=Buf[3];
	if((Buf[3]<10)||(Buf[3]>33))
	ptst_AgreeOn_Reduce->Space=33;
	ptst_AgreeOn_Reduce->Number=Buf[4]*0x100+Buf[5];
}
/*---------------------------------------设置驾驶员ID-----------------------------------------------------------*/
static void Explain_Driver(uint8 *Buf,void *OutBuf,uint16 DataLen) //设置驾驶员ID
{	st_AgreeOn_Driver	*ptst_AgreeOn_Driver;
	uint16 i;
	uint8 j,Len,Len1;
	ptst_AgreeOn_Driver=OutBuf;
	for(i=0,j=0;((i<DataLen)&&j<sizeof(ptst_AgreeOn_Driver->CN_st_AgreeOn_Driver_Par)/sizeof(st_AgreeOn_Driver_Par));i+=Len,j++)
	{	Len=Buf[i];
		if(Len>sizeof(ptst_AgreeOn_Driver->CN_st_AgreeOn_Driver_Par[0].ID))
			Len=sizeof(ptst_AgreeOn_Driver->CN_st_AgreeOn_Driver_Par[0].ID);	
		CN_st_Fun_AscNumber.MoveByte(ptst_AgreeOn_Driver->CN_st_AgreeOn_Driver_Par[j].ID,Buf+i+1,Len);
		Len=Buf[i]+1;
		Len1=Buf[Len+i];
		if(Len1>sizeof(ptst_AgreeOn_Driver->CN_st_AgreeOn_Driver_Par[0].Phone))
			Len1=sizeof(ptst_AgreeOn_Driver->CN_st_AgreeOn_Driver_Par[0].Phone);	
		CN_st_Fun_AscNumber.MoveByte(ptst_AgreeOn_Driver->CN_st_AgreeOn_Driver_Par[j].Phone,Buf+i+Len+1,Len1);
		Len1=Buf[Len+i]+1;
		Len=Len1+Len;
	}
	ptst_AgreeOn_Driver->Number=j;
}
/*---------------------------------------中心导航--------------------------------------------------------------*/
static void Explain_Navigation(uint8 *Buf,void *OutBuf,uint16 DataLen)//中心导航
{	st_AgreeOn_Navigation	*ptst_AgreeOn_Navigation;
	uint16 Number,Len,i;
	ptst_AgreeOn_Navigation=OutBuf;
   	ptst_AgreeOn_Navigation->DateTimer[0]=0x20;
   	CN_st_Fun_AscNumber.Hex2Bcd(Buf,ptst_AgreeOn_Navigation->DateTimer+1,6);
	Number=Buf[6];
	for(i=0,Len=7,ptst_AgreeOn_Navigation->Number=0;i<Number;i++,Len+=12)
	{	if(i>=sizeof(ptst_AgreeOn_Navigation->CN_st_AgreeOn_Navigation_Par)/sizeof(st_AgreeOn_Navigation_Par))
			continue;
		ptst_AgreeOn_Navigation->Number++;
		ptst_AgreeOn_Navigation->CN_st_AgreeOn_Navigation_Par[i].Latitude=Buf[Len]*0x1000000+Buf[Len+1]*0x10000+Buf[Len+2]*0x100+Buf[Len+3];	
		ptst_AgreeOn_Navigation->CN_st_AgreeOn_Navigation_Par[i].Longitude=
		Buf[Len+4]*0x1000000+Buf[Len+5]*0x10000+Buf[Len+6]*0x100+Buf[Len+7];
		ptst_AgreeOn_Navigation->CN_st_AgreeOn_Navigation_Par[i].State=
		Buf[Len+8]*0x1000000+Buf[Len+9]*0x10000+Buf[Len+10]*0x100+Buf[Len+11];
	}
	Number=DataLen-Len;
	if(Number>sizeof(ptst_AgreeOn_Navigation->Text))
		Number=sizeof(ptst_AgreeOn_Navigation->Text);
	CN_st_Fun_AscNumber.MoveByte(ptst_AgreeOn_Navigation->Text,Buf+Len,Number);
} 
/*--------------------------------------------手机文本调度---------------------------------------------------*/
static void Explain_HandTxt(uint8 *Buf,void *OutBuf,uint16 DataLen)//手机文本调度
{	st_AgreeOn_HandTxt	*ptst_AgreeOn_HandTxt;
	ptst_AgreeOn_HandTxt=OutBuf;
	CN_st_Fun_AscNumber.ClsArray(ptst_AgreeOn_HandTxt,sizeof(st_AgreeOn_HandTxt));
	CN_st_Fun_AscNumber.UniToStr(Buf,ptst_AgreeOn_HandTxt->Buf,DataLen);
}
/*------------------------------------------手机调度信息---------------------------------------------------*/
static void Explain_HandAttemper(uint8 *Buf,void *OutBuf,uint16 DataLen) //手机调度信息
{	st_AgreeOn_HandAttemper	*ptst_AgreeOn_HandAttemper;
	uint8 Len;
	uint8 *Temp;
	ptst_AgreeOn_HandAttemper=OutBuf;
	CN_st_Fun_AscNumber.UniToStr(Buf,ptst_AgreeOn_HandAttemper->Buf,DataLen);
   	if((Temp=CN_st_Fun_AscNumber.LookStr(":",ptst_AgreeOn_HandAttemper->Buf))==NULL)
		return ;
	*Temp=0;
	ptst_AgreeOn_HandAttemper->ID=CN_st_Fun_AscNumber.Asc2Hex(ptst_AgreeOn_HandAttemper->Buf,
	CN_st_Fun_AscNumber.Strsize(ptst_AgreeOn_HandAttemper->Buf));
	Len=CN_st_Fun_AscNumber.Strsize(Temp+1);
	CN_st_Fun_AscNumber.MoveByte(ptst_AgreeOn_HandAttemper->Buf,Temp+1,Len);
	CN_st_Fun_AscNumber.ClsArray(ptst_AgreeOn_HandAttemper->Buf+Len,sizeof(ptst_AgreeOn_HandAttemper->Buf)-Len);
}

/*============================================出租车辆专用协议==================================================*/
 /*------------------------------------------修改订单信息---------------------------------------------------*/
static void Explain_AmendForm(uint8 *Buf,void *OutBuf,uint16 DataLen)  //修改订单信息
{	st_AgreeOn_AmendForm	*ptst_AgreeOn_AmendForm;
	uint16 i,j;
	uint8 Len;
	ptst_AgreeOn_AmendForm=OutBuf;
	for(i=0,j=0;i<DataLen;j++,i+=Buf[i+1]+2)
	{	if(j>=sizeof(ptst_AgreeOn_AmendForm->CN_st_AgreeOn_AmendForm_Par)/sizeof(st_AgreeOn_AmendForm_Par))
			continue;
		ptst_AgreeOn_AmendForm->Number++;
		ptst_AgreeOn_AmendForm->CN_st_AgreeOn_AmendForm_Par[j].ID=Buf[i];
		Len=Buf[i+1];
		if(Len>sizeof(ptst_AgreeOn_AmendForm->CN_st_AgreeOn_AmendForm_Par[0].Cut))
			Len=sizeof(ptst_AgreeOn_AmendForm->CN_st_AgreeOn_AmendForm_Par[0].Cut);
		CN_st_Fun_AscNumber.MoveByte(ptst_AgreeOn_AmendForm->CN_st_AgreeOn_AmendForm_Par[j].Cut,
		Buf+i+2,Len);		
	}
}
/*------------------------------------------下发订单抢答信息------------------------------------------*/
static void Explain_UpLoaderForm(uint8 *Buf,void *OutBuf,uint16 DataLen)  //下发订单抢答信息
{	st_AgreeOn_UpLoaderForm	*ptst_AgreeOn_UpLoaderForm;
	ptst_AgreeOn_UpLoaderForm=OutBuf;
	CN_st_Fun_AscNumber.ClsArray(ptst_AgreeOn_UpLoaderForm,sizeof(st_AgreeOn_UpLoaderForm));
	ptst_AgreeOn_UpLoaderForm->Type=Buf[0];
	ptst_AgreeOn_UpLoaderForm->ID=Buf[1]*0x100+Buf[2];
	ptst_AgreeOn_UpLoaderForm->DateTimer[0]=0x20;
	CN_st_Fun_AscNumber.Hex2Bcd(Buf+3,ptst_AgreeOn_UpLoaderForm->DateTimer+1,5);
	DataLen=DataLen-8;
	if(DataLen>sizeof(ptst_AgreeOn_UpLoaderForm->Cut))
		DataLen=sizeof(ptst_AgreeOn_UpLoaderForm->Cut);	
	CN_st_Fun_AscNumber.MoveByte(ptst_AgreeOn_UpLoaderForm->Cut,Buf+8,DataLen);
}
/*---------------------------------------下发订单抢答成功信息------------------------------------------------*/
static void Explain_UpLoaderFormSuc(uint8 *Buf,void *OutBuf,uint16 DataLen)  //下发订单抢答成功信息
{	st_AgreeOn_UpLoaderFormSuc	*ptst_AgreeOn_UpLoaderFormSuc;
	uint8 Len;
	ptst_AgreeOn_UpLoaderFormSuc=OutBuf;
	CN_st_Fun_AscNumber.ClsArray(ptst_AgreeOn_UpLoaderFormSuc,sizeof(st_AgreeOn_UpLoaderFormSuc));
	ptst_AgreeOn_UpLoaderFormSuc->ID=Buf[0]*0X100+Buf[1];
	Len=Buf[2];
	if(Len>sizeof(ptst_AgreeOn_UpLoaderFormSuc->Phone))
		Len=sizeof(ptst_AgreeOn_UpLoaderFormSuc->Phone);
	CN_st_Fun_AscNumber.MoveByte(ptst_AgreeOn_UpLoaderFormSuc->Phone,Buf+3,Len);
	Len=Buf[2]+3;
	DataLen=DataLen-Len;
	if(DataLen>sizeof(ptst_AgreeOn_UpLoaderFormSuc->Cut))
		DataLen=sizeof(ptst_AgreeOn_UpLoaderFormSuc->Cut);
	CN_st_Fun_AscNumber.MoveByte(ptst_AgreeOn_UpLoaderFormSuc->Cut,Buf+Len,DataLen);				
}
/*--------------------------------------------下发订单抢答失败信息-------------------------------------------*/
static void Explain_UpLoaderFormErro(uint8 *Buf,void *OutBuf,uint16 DataLen)  //下发订单抢答失败信息
{	st_AgreeOn_UpLoaderFormErro	*ptst_AgreeOn_UpLoaderFormErro;
	ptst_AgreeOn_UpLoaderFormErro=OutBuf;
	ptst_AgreeOn_UpLoaderFormErro->ID=Buf[0]*0x100+Buf[1];
}
/*--------------------------------------------下发订单取消信息--------------------------------------------*/
static void Explain_UpLoaderCan(uint8 *Buf,void *OutBuf,uint16 DataLen)  //下发订单取消信息
{	st_AgreeOn_UpLoaderCan	*ptst_AgreeOn_UpLoaderCan;
	ptst_AgreeOn_UpLoaderCan=OutBuf;
	ptst_AgreeOn_UpLoaderCan->ID=Buf[0]*0x100+Buf[1];
}


