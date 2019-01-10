#define De_Tz_Send_Compiler
#include "Tz_Send.h"
static uint16 Explain(uint8 *Buf,void *InputBuf,uint16 *ReDataLen,uint16 ID)
{	uint16 i;
   	for(i=0;i<sizeof(CN_Ba_st_Tz_Send_FunOper)/sizeof(st_Tz_Send_FunOper);i++,WatchDog())
	{	if(CN_Ba_st_Tz_Send_FunOper[i].ID==ID)
		{	if(CN_Ba_st_Tz_Send_FunOper[i].Read!=NULL)
			{	CN_Ba_st_Tz_Send_FunOper[i].Read(Buf,InputBuf,ReDataLen);
			}
			break;
		}
	}
	if(i==sizeof(CN_Ba_st_Tz_Send_FunOper)/sizeof(st_Tz_Send_FunOper))
		return De_Erro_Tz_Send_NoID;
	return De_Suc_Tz_Send;		

}
/*==============================================基本协议=========================================================*/
/*--------------------------------------------获取服务器通讯参数-----------------------------------------------*/
static void Explain_GetSeverComPar(uint8 *OutBuf,void *InputBuf,uint16 *ReDataLen)  //获取通讯参数指令
{	uint8 *StateBuf,i;
	st_AgreeOn_Send_Basic	*ptst_AgreeOn_Send_Basic;
	uint8 Point,PointNumber;
	ptst_AgreeOn_Send_Basic=InputBuf;
	Gps2CenGps(&ptst_AgreeOn_Send_Basic->CN_st_Data_Gps,OutBuf);
	CN_st_Fun_AscNumber.ClsArray(OutBuf+18,4);
	StateBuf=OutBuf+18;
	for(i=0;i<sizeof(ptst_AgreeOn_Send_Basic->State);i++)
	{	Point=(3-i/8);
		PointNumber=i%8;
		if(ptst_AgreeOn_Send_Basic->State[i]!=De_AgreeOn_State_Suc)
			StateBuf[Point]|=((0x01)<<PointNumber);	
	}
	*ReDataLen=22;
}
/*-----------------------------------------------登录指令-----------------------------------------------------*/
//登录指令,与获取通讯参数指令一样
/*-----------------------------------------------休眠指令-----------------------------------------------------*/
//休眠指令,与获取通讯参数指令一样
/*-----------------------------------------------关机指令-----------------------------------------------------*/
//关机指令,与获取通讯参数指令一样
/*--------------------------------------------定位终端命令应答------------------------------------------------*/
static void Explain_Answer(uint8 *OutBuf,void *InputBuf,uint16 *ReDataLen)
{	st_AgreeOn_Send_Answer	*ptst_AgreeOn_Send_Answer;
	ptst_AgreeOn_Send_Answer=InputBuf;
	OutBuf[0]=(ptst_AgreeOn_Send_Answer->Number>>8);
	OutBuf[1]=(ptst_AgreeOn_Send_Answer->Number&0xff);
	OutBuf[2]=(ptst_AgreeOn_Send_Answer->OrderID>>8);
	OutBuf[3]=(ptst_AgreeOn_Send_Answer->OrderID&0xff);
	OutBuf[4]=ptst_AgreeOn_Send_Answer->Result;
	*ReDataLen=5;
}
/*--------------------------------------------上传位置信息----------------------------------------------------*/
//上传位置信息,与获取通讯参数指令一样
/*-------------------------------------------上传菜单信息-----------------------------------------------------*/
static void Explain_Menum(uint8 *OutBuf,void *InputBuf,uint16 *ReDataLen)
{	st_AgreeOn_Send_Menum	*ptst_AgreeOn_Send_Menum;
	uint8 DataLen;
	ptst_AgreeOn_Send_Menum=InputBuf;
	DataLen=CN_st_Fun_AscNumber.Strsize(ptst_AgreeOn_Send_Menum->Cut);
	if(DataLen>sizeof(ptst_AgreeOn_Send_Menum->Cut))
		DataLen=sizeof(ptst_AgreeOn_Send_Menum->Cut);
	OutBuf[0]=ptst_AgreeOn_Send_Menum->ID;
	OutBuf[1]=DataLen;
	CN_st_Fun_AscNumber.MoveByte(OutBuf+2,ptst_AgreeOn_Send_Menum->Cut,DataLen);
	*ReDataLen=2+DataLen;		
}

/*--------------------------------上传带菜单的调度信息的反馈信息----------------------------------------------*/
static void Explain_TxtMenum(uint8 *OutBuf,void *InputBuf,uint16 *ReDataLen)
{	st_AgreeOn_Send_TxtMenum	*ptst_AgreeOn_Send_TxtMenum;
	uint8 DataLen;		
	ptst_AgreeOn_Send_TxtMenum=InputBuf;
	DataLen=CN_st_Fun_AscNumber.Strsize(ptst_AgreeOn_Send_TxtMenum->Cut);
	if(DataLen>sizeof(ptst_AgreeOn_Send_TxtMenum->Cut))
		DataLen=sizeof(ptst_AgreeOn_Send_TxtMenum->Cut);
	OutBuf[0]=ptst_AgreeOn_Send_TxtMenum->ID>>8;
	OutBuf[1]=ptst_AgreeOn_Send_TxtMenum->ID;
	OutBuf[2]=ptst_AgreeOn_Send_TxtMenum->ResultID;
	OutBuf[3]=DataLen;
	CN_st_Fun_AscNumber.MoveByte(OutBuf+4,ptst_AgreeOn_Send_TxtMenum->Cut,DataLen);
	*ReDataLen=DataLen+4;
}

/*-------------------------------------------查询定位终端参数-------------------------------------------------*/
static void Explain_LookPar(uint8 *OutBuf,void *InputBuf,uint16 *ReDataLen)
{	st_AgreeOn_Agree_Par	*ptst_AgreeOn_Agree_Par;
	uint16 DataLen,Len;
	uint8 i;
	Len=0;
	ptst_AgreeOn_Agree_Par=InputBuf;	
	for(i=0,DataLen=0;i<De_AgreeOn_SetPar_Number;i++)
	{	if(ptst_AgreeOn_Agree_Par->ParSet[i]==De_AgreeOn_LookPar_NoData)
			continue;
		if(ptst_AgreeOn_Agree_Par->ParSet[i]==De_AgreeOn_LookPar_Erro)
		{	OutBuf[DataLen++]=1;
			continue;		
		}
		OutBuf[DataLen++]=0;
		OutBuf[DataLen++]=(CN_Ba_st_AgreenOn_Par2Type[i].Par>>8);
		OutBuf[DataLen++]=(CN_Ba_st_AgreenOn_Par2Type[i].Par&0xff);	
		Explain_Par(&ptst_AgreeOn_Agree_Par->CN_st_AgreeOn_Agree_Par_Cut,OutBuf+DataLen,&Len,CN_Ba_st_AgreenOn_Par2Type[i].Par);
		DataLen=DataLen+Len;
	}
	*ReDataLen=DataLen;			
}
/*-------------------------------------------上传软件升级状态-------------------------------------------------*/
static void Explain_UpdateSoftWare(uint8 *OutBuf,void *InputBuf,uint16 *ReDataLen)
{	st_AgreeOn_Send_UpdateSoftWare	*ptst_AgreeOn_Send_UpdateSoftWare;
	ptst_AgreeOn_Send_UpdateSoftWare=InputBuf;
	*OutBuf=ptst_AgreeOn_Send_UpdateSoftWare->Result;
	*ReDataLen=1;	
}
/*-------------------------------------------上传报警状态-----------------------------------------------------*/
static void Explain_Waring(uint8 *OutBuf,void *InputBuf,uint16 *ReDataLen)
{	st_AgreeOn_Send_Waring	*ptst_AgreeOn_Send_Waring;
	uint32 Addree;
	uint16 DataLen,i,Len;
	uint8 State;
	ptst_AgreeOn_Send_Waring=InputBuf;
	OutBuf[0]=ptst_AgreeOn_Send_Waring->Type;
   	Explain_GetSeverComPar(OutBuf+1,&ptst_AgreeOn_Send_Waring->CN_st_AgreeOn_Send_Basic,&DataLen);
	DataLen++;
	for(i=0;i<sizeof(ptst_AgreeOn_Send_Waring->CN_st_WorkVal_Tabel.Type);i++)
	{	if(ptst_AgreeOn_Send_Waring->CN_st_WorkVal_Tabel.Type[i]!=De_st_AgreeOn_Send_Waring_Type_Yes)
			continue;
		OutBuf[DataLen++]=(CN_Ba_WordPar[i]>>8);
		OutBuf[DataLen++]=(CN_Ba_WordPar[i]&0xff);
		Explain_WorkPar(&ptst_AgreeOn_Send_Waring->CN_st_WorkVal_Tabel.CN_st_AgreeOn_SetVidType_Par,OutBuf+DataLen,&Len,i);
		DataLen+=Len;
	}
	for(i=0;i<sizeof(ptst_AgreeOn_Send_Waring->CN_st_Sensor_State)/sizeof(st_Sensor_State);i++)
	{	if((ptst_AgreeOn_Send_Waring->CN_st_Sensor_State[i].Work==De_AgreeOn_Send_Less_State_Suc)&&(ptst_AgreeOn_Send_Waring->CN_st_Sensor_State[i].Battery==De_AgreeOn_Send_Less_State_Suc)
		&&(ptst_AgreeOn_Send_Waring->CN_st_Sensor_State[i].Dly==De_AgreeOn_Send_Less_State_Suc))
			continue;
		Addree=Expain_VidType2LessAddree(&ptst_AgreeOn_Send_Waring->CN_st_WorkVal_Tabel.CN_st_AgreeOn_SetVidType_Par,i);
		OutBuf[DataLen++]=((Addree>>24)&0xff);
		OutBuf[DataLen++]=((Addree>>16)&0xff);
		OutBuf[DataLen++]=((Addree>>8)&0xff);
		OutBuf[DataLen++]=((Addree>>0)&0xff);
		OutBuf[DataLen++]=((CN_Ba_LessPar[i]>>8)&0xff);
		OutBuf[DataLen++]=((CN_Ba_LessPar[i]>>0)&0xff);
		State=De_AgreeOn_Send_Less_State_Suc;
		if((ptst_AgreeOn_Send_Waring->CN_st_Sensor_State[i].Work!=De_AgreeOn_Send_Less_State_Suc)||(ptst_AgreeOn_Send_Waring->CN_st_Sensor_State[i].Dly!=De_AgreeOn_Send_Less_State_Suc))
			State=De_AgreeOn_Send_Less_State_Erro;
		OutBuf[DataLen++]=State;
		State=De_AgreeOn_Send_Less_State_Suc;
		if(ptst_AgreeOn_Send_Waring->CN_st_Sensor_State[i].Battery!=De_AgreeOn_Send_Less_State_Suc)
			State=De_AgreeOn_Send_Less_State_Erro;
		OutBuf[DataLen++]=State;
	}
		*ReDataLen=DataLen;	 
}

/*=========================================功能扩展协议==========================================================*/
/*-------------------------------------------上传照片1---------------------------------------------------*/
static void Explain_UploaderJpg1(uint8 *OutBuf,void *InputBuf,uint16 *ReDataLen)	 		//上传照片1
{	st_AgreeOn_Send_UploaderJpg1	*ptst_AgreeOn_Send_UploaderJpg1;
	uint16 DataLen;
	ptst_AgreeOn_Send_UploaderJpg1=InputBuf;
	Explain_GetSeverComPar(OutBuf,&ptst_AgreeOn_Send_UploaderJpg1->CN_st_AgreeOn_Send_Basic,&DataLen);
	OutBuf[DataLen++]=ptst_AgreeOn_Send_UploaderJpg1->Type;
	OutBuf[DataLen++]=ptst_AgreeOn_Send_UploaderJpg1->Pro;
	OutBuf[DataLen++]=ptst_AgreeOn_Send_UploaderJpg1->SecSum;
	OutBuf[DataLen++]=ptst_AgreeOn_Send_UploaderJpg1->SecNumber;
	CN_st_Fun_AscNumber.MoveByte(OutBuf+DataLen,ptst_AgreeOn_Send_UploaderJpg1->Buf,ptst_AgreeOn_Send_UploaderJpg1->SizeofBuf);	
   	DataLen+=ptst_AgreeOn_Send_UploaderJpg1->SizeofBuf;
	*ReDataLen=DataLen;
}
/*-------------------------------------------上传照片2---------------------------------------------------*/
static void Explain_UploaderJpg2(uint8 *OutBuf,void *InputBuf,uint16 *ReDataLen)		 	//上传照片2
{	st_AgreeOn_Send_UploaderJpg2	*ptst_AgreeOn_Send_UploaderJpg2;
	uint16 DataLen,Len;
	uint8 i;
	ptst_AgreeOn_Send_UploaderJpg2=InputBuf;
	Explain_GetSeverComPar(OutBuf,&ptst_AgreeOn_Send_UploaderJpg2->CN_st_AgreeOn_Send_Basic,&DataLen);
	for(i=0;i<sizeof(CN_Ba_WordPar)/sizeof(uint16);i++)
	{	if(ptst_AgreeOn_Send_UploaderJpg2->CN_st_WorkVal_Tabel.Type[i]==De_st_AgreeOn_Send_Waring_Type_Yes)
			break;
	}
	OutBuf[DataLen++]=((CN_Ba_WordPar[i]>>8)&0xff);
	OutBuf[DataLen++]=((CN_Ba_WordPar[i]>>0)&0xff);
	Explain_WorkPar(&ptst_AgreeOn_Send_UploaderJpg2->CN_st_WorkVal_Tabel.CN_st_AgreeOn_SetVidType_Par,
	OutBuf+DataLen,&Len,i);
	DataLen+=Len;
	OutBuf[DataLen++]=ptst_AgreeOn_Send_UploaderJpg2->SecSum;
	OutBuf[DataLen++]=ptst_AgreeOn_Send_UploaderJpg2->SecNumber;
	CN_st_Fun_AscNumber.MoveByte(OutBuf+DataLen,ptst_AgreeOn_Send_UploaderJpg2->Buf,ptst_AgreeOn_Send_UploaderJpg2->SizeofBuf);	
   	DataLen+=ptst_AgreeOn_Send_UploaderJpg2->SizeofBuf;
	*ReDataLen=DataLen;
}
/*----------------------------------------上传定位终端工作参数---------------------------------------------------*/
static void Explain_UploaderPar(uint8 *OutBuf,void *InputBuf,uint16 *ReDataLen)  //上传工作参数
{	st_AgreeOn_Send_UploaderPar	*ptst_AgreeOn_Send_UploaderPar;
	uint16 DataLen,i,Len;
	ptst_AgreeOn_Send_UploaderPar=InputBuf;
   	Explain_GetSeverComPar(OutBuf,&ptst_AgreeOn_Send_UploaderPar->CN_st_AgreeOn_Send_Basic,&DataLen);
	for(i=0;i<sizeof(ptst_AgreeOn_Send_UploaderPar->CN_st_WorkVal_Tabel.Type);i++)
	{	if(ptst_AgreeOn_Send_UploaderPar->CN_st_WorkVal_Tabel.Type[i]!=De_st_AgreeOn_Send_Waring_Type_Yes)
			continue;
		OutBuf[DataLen++]=(CN_Ba_WordPar[i]>>8);
		OutBuf[DataLen++]=(CN_Ba_WordPar[i]&0xff);
		Explain_WorkPar1(&ptst_AgreeOn_Send_UploaderPar->CN_st_WorkVal_Tabel.CN_st_AgreeOn_SetVidType_Par,OutBuf+DataLen,&Len,i);
		DataLen+=Len;
	}
		*ReDataLen=DataLen;	 
}
static void Explain_UploaderLog(uint8 *OutBuf,void *InputBuf,uint16 *ReDataLen)	//上传日志文件
{			



}
static void Explain_UpLoaderWarning(uint8 *OutBuf,void *InputBuf,uint16 *ReDataLen)	//上传报警参数
{	st_AgreeOn_SetVidType  *ptst_AgreeOn_SetVidType;
	uint16 DataLen,Len;
	uint8 i;
	ptst_AgreeOn_SetVidType=InputBuf;
	for(DataLen=0,i=0;i<sizeof(ptst_AgreeOn_SetVidType->Type);i++)
	{	if(ptst_AgreeOn_SetVidType->Type[i]==De_AgreeOn_SetVidType_Type_No)
			continue;
		OutBuf[DataLen++]=((CN_Ba_WordPar[i]>>8)&0xff);
		OutBuf[DataLen++]=((CN_Ba_WordPar[i]>>0)&0xff);
		OutBuf[DataLen++]=ptst_AgreeOn_SetVidType->Type[i];
		Explain_WorkPar2(ptst_AgreeOn_SetVidType,OutBuf+DataLen,&Len,i,ptst_AgreeOn_SetVidType->Type[i]);
		DataLen+=Len;
	}
	   *ReDataLen=DataLen;	 
}
/*=======================================交通物流专用协议=========================================================*/
static void Explain_OutRoadMap(uint8 *OutBuf,void *InputBuf,uint16 *ReDataLen)		//进出区域报警
{	st_AgreeOn_Send_OutRoadMap	*ptst_AgreeOn_Send_OutRoadMap;
	uint16 DataLen,Len;
	ptst_AgreeOn_Send_OutRoadMap=InputBuf;
	DataLen=0;
	OutBuf[DataLen++]=ptst_AgreeOn_Send_OutRoadMap->Type;
	OutBuf[DataLen++]=((ptst_AgreeOn_Send_OutRoadMap->ID>>8)&0xff);
	OutBuf[DataLen++]=((ptst_AgreeOn_Send_OutRoadMap->ID>>0)&0xff);
	OutBuf[DataLen++]=ptst_AgreeOn_Send_OutRoadMap->InputOrOut;
	Explain_GetSeverComPar(OutBuf+DataLen,&ptst_AgreeOn_Send_OutRoadMap->CN_st_AgreeOn_Send_Basic,&Len);
	*ReDataLen=DataLen+Len;
} 

static void Explain_UpLoaderReduce(uint8 *OutBuf,void *InputBuf,uint16 *ReDataLen) 	//上传压缩数据
{	st_AgreeOn_Send_UploaderPar	CN_st_AgreeOn_Send_UploaderPar;
    st_AgreeOn_Send_Basic	CN_st_AgreeOn_Send_Basic;
	st_Reduce_Table	*ptst_Reduce_Table;
    uint16 DataLen,Len,len1,i;
	DataLen=0;
	ptst_Reduce_Table=InputBuf;
	if(ptst_Reduce_Table->Number==0)
     	return ;
    if(ptst_Reduce_Table->CN_st_AgreeOn_Reduce.Data==0)
	{	OutBuf[DataLen++]=((De_Dev_Order_Orientation>>8)&0xff);
		OutBuf[DataLen++]=((De_Dev_Order_Orientation>>0)&0xff);
		OutBuf[DataLen++]=ptst_Reduce_Table->CN_st_AgreeOn_Reduce.AccOpenTimer;
		OutBuf[DataLen++]=ptst_Reduce_Table->CN_st_AgreeOn_Reduce.AccCloseTimer;
		for(i=0;i<ptst_Reduce_Table->Number;i++)
		{  	Len=DataLen;
			DataLen++	;
	    	ptst_Reduce_Table->ReadParTable(ptst_Reduce_Table->Data[i],&CN_st_AgreeOn_Send_UploaderPar);
	   		if(i==0)					//	
	  		{	Explain_GetSeverComPar(OutBuf+DataLen,&CN_st_AgreeOn_Send_UploaderPar.CN_st_AgreeOn_Send_Basic,&len1);
				OutBuf[Len]=len1;
			   	DataLen+=len1;
			   	CN_st_Fun_AscNumber.MoveByte(&CN_st_AgreeOn_Send_Basic,&CN_st_AgreeOn_Send_UploaderPar.CN_st_AgreeOn_Send_Basic,sizeof(st_AgreeOn_Send_Basic));
		       	continue;
			}	
			else
			{
			  	OutBuf[Len]=12;
			    if((len1=(CN_st_AgreeOn_Send_UploaderPar.CN_st_AgreeOn_Send_Basic.CN_st_Data_Gps.CN_st_Gps_Data_GPRMC.Latitude)-(CN_st_AgreeOn_Send_Basic.CN_st_Data_Gps.CN_st_Gps_Data_GPRMC.Latitude))>0x8000)
				{	len1=(CN_st_AgreeOn_Send_Basic.CN_st_Data_Gps.CN_st_Gps_Data_GPRMC.Latitude)-(CN_st_AgreeOn_Send_UploaderPar.CN_st_AgreeOn_Send_Basic.CN_st_Data_Gps.CN_st_Gps_Data_GPRMC.Latitude);
				   	len1+=0x8000;
				   	OutBuf[DataLen++]=((len1>>8)&0xff);
					OutBuf[DataLen++]=((len1>>0)&0xff); 
				}
				else
				{	len1=(CN_st_AgreeOn_Send_UploaderPar.CN_st_AgreeOn_Send_Basic.CN_st_Data_Gps.CN_st_Gps_Data_GPRMC.Latitude)-(CN_st_AgreeOn_Send_Basic.CN_st_Data_Gps.CN_st_Gps_Data_GPRMC.Latitude) ;
				    OutBuf[DataLen++]=((len1>>8)&0xff);
			        OutBuf[DataLen++]=((len1>>0)&0xff); 
				}
				if((len1=(CN_st_AgreeOn_Send_UploaderPar.CN_st_AgreeOn_Send_Basic.CN_st_Data_Gps.CN_st_Gps_Data_GPRMC.Longitude)-(CN_st_AgreeOn_Send_Basic.CN_st_Data_Gps.CN_st_Gps_Data_GPRMC.Longitude))>0x8000)
				{	len1=(CN_st_AgreeOn_Send_Basic.CN_st_Data_Gps.CN_st_Gps_Data_GPRMC.Longitude)-(CN_st_AgreeOn_Send_UploaderPar.CN_st_AgreeOn_Send_Basic.CN_st_Data_Gps.CN_st_Gps_Data_GPRMC.Longitude);
				    len1+=0x8000;
				    OutBuf[DataLen++]=((len1>>8)&0xff);
			        OutBuf[DataLen++]=((len1>>0)&0xff); 
				}
				else
				{	len1=(CN_st_AgreeOn_Send_UploaderPar.CN_st_AgreeOn_Send_Basic.CN_st_Data_Gps.CN_st_Gps_Data_GPRMC.Longitude)-(CN_st_AgreeOn_Send_Basic.CN_st_Data_Gps.CN_st_Gps_Data_GPRMC.Longitude) ;
				    OutBuf[DataLen++]=((len1>>8)&0xff);
			        OutBuf[DataLen++]=((len1>>0)&0xff); 
				}
			   OutBuf[DataLen++]=CN_st_AgreeOn_Send_UploaderPar.CN_st_AgreeOn_Send_Basic.CN_st_Data_Gps.CN_st_Gps_Data_GPRMC.Speed;
			   OutBuf[DataLen++]=CN_st_AgreeOn_Send_UploaderPar.CN_st_AgreeOn_Send_Basic.CN_st_Data_Gps.CN_st_Gps_Data_GPRMC.Angle/20;
			   Gps2ReduceGps_Height(&CN_st_AgreeOn_Send_UploaderPar.CN_st_AgreeOn_Send_Basic.CN_st_Data_Gps.CN_st_Gps_Data_GPGGA.Height,OutBuf+DataLen);
			   DataLen++;
			   DataLen++;
			   Explain_state(OutBuf+DataLen,&CN_st_AgreeOn_Send_UploaderPar,&len1);
			   DataLen+=len1;
			   CN_st_Fun_AscNumber.MoveByte(&CN_st_AgreeOn_Send_Basic,&CN_st_AgreeOn_Send_UploaderPar.CN_st_AgreeOn_Send_Basic,sizeof(st_AgreeOn_Send_Basic));	
   	 	    }
	 	}
	 }
	else
	{	OutBuf[DataLen++]=((De_Dev_Order_UploaderPar>>8)&0xff);
		OutBuf[DataLen++]=((De_Dev_Order_UploaderPar>>0)&0xff);
		OutBuf[DataLen++]=ptst_Reduce_Table->CN_st_AgreeOn_Reduce.AccOpenTimer;
		OutBuf[DataLen++]=ptst_Reduce_Table->CN_st_AgreeOn_Reduce.AccCloseTimer;
	  	for(i=0;i<ptst_Reduce_Table->Number;i++)
      	{   Len=DataLen;
		  	DataLen++	;
		  	ptst_Reduce_Table->ReadParTable(ptst_Reduce_Table->Data[i],&CN_st_AgreeOn_Send_UploaderPar);
          	if(i==0)					//	
          	{	Explain_UploaderPar(OutBuf+DataLen,&CN_st_AgreeOn_Send_UploaderPar,&len1);
		   		OutBuf[Len]=len1;
		   		DataLen+=len1;
		   		CN_st_Fun_AscNumber.MoveByte(&CN_st_AgreeOn_Send_Basic, &CN_st_AgreeOn_Send_UploaderPar.CN_st_AgreeOn_Send_Basic,len1);
          		continue;
		  	}	
		  	else 
		    {	if((len1=(CN_st_AgreeOn_Send_UploaderPar.CN_st_AgreeOn_Send_Basic.CN_st_Data_Gps.CN_st_Gps_Data_GPRMC.Latitude)-(CN_st_AgreeOn_Send_Basic.CN_st_Data_Gps.CN_st_Gps_Data_GPRMC.Latitude))>0x8000)
		        	{	len1=(CN_st_AgreeOn_Send_Basic.CN_st_Data_Gps.CN_st_Gps_Data_GPRMC.Latitude)-(CN_st_AgreeOn_Send_UploaderPar.CN_st_AgreeOn_Send_Basic.CN_st_Data_Gps.CN_st_Gps_Data_GPRMC.Latitude);
						len1+=0x8000;
						OutBuf[DataLen++]=((len1>>8)&0xff);
					    OutBuf[DataLen++]=((len1>>0)&0xff); 
		            }
			   else
			   {	len1=(CN_st_AgreeOn_Send_UploaderPar.CN_st_AgreeOn_Send_Basic.CN_st_Data_Gps.CN_st_Gps_Data_GPRMC.Latitude)-(CN_st_AgreeOn_Send_Basic.CN_st_Data_Gps.CN_st_Gps_Data_GPRMC.Latitude) ;
				    OutBuf[DataLen++]=((len1>>8)&0xff);
			        OutBuf[DataLen++]=((len1>>0)&0xff); 
			   }
			   if((len1=(CN_st_AgreeOn_Send_UploaderPar.CN_st_AgreeOn_Send_Basic.CN_st_Data_Gps.CN_st_Gps_Data_GPRMC.Longitude)-(CN_st_AgreeOn_Send_Basic.CN_st_Data_Gps.CN_st_Gps_Data_GPRMC.Longitude))>0x8000)
			   {	len1=(CN_st_AgreeOn_Send_Basic.CN_st_Data_Gps.CN_st_Gps_Data_GPRMC.Longitude)-(CN_st_AgreeOn_Send_UploaderPar.CN_st_AgreeOn_Send_Basic.CN_st_Data_Gps.CN_st_Gps_Data_GPRMC.Longitude);
				    len1+=0x8000;
				    OutBuf[DataLen++]=((len1>>8)&0xff);
			        OutBuf[DataLen++]=((len1>>0)&0xff); 
			   }
			   else
			   {	len1=(CN_st_AgreeOn_Send_UploaderPar.CN_st_AgreeOn_Send_Basic.CN_st_Data_Gps.CN_st_Gps_Data_GPRMC.Longitude)-(CN_st_AgreeOn_Send_Basic.CN_st_Data_Gps.CN_st_Gps_Data_GPRMC.Longitude) ;
				    OutBuf[DataLen++]=((len1>>8)&0xff);
			        OutBuf[DataLen++]=((len1>>0)&0xff); 
			   }
			  OutBuf[DataLen++]=CN_st_AgreeOn_Send_UploaderPar.CN_st_AgreeOn_Send_Basic.CN_st_Data_Gps.CN_st_Gps_Data_GPRMC.Speed;
			  OutBuf[DataLen++]=CN_st_AgreeOn_Send_UploaderPar.CN_st_AgreeOn_Send_Basic.CN_st_Data_Gps.CN_st_Gps_Data_GPRMC.Angle/20;
			  Gps2ReduceGps_Height(&CN_st_AgreeOn_Send_UploaderPar.CN_st_AgreeOn_Send_Basic.CN_st_Data_Gps.CN_st_Gps_Data_GPGGA.Height,OutBuf+DataLen);
			  DataLen++;
			  DataLen++;
			  Explain_state(OutBuf+DataLen,&CN_st_AgreeOn_Send_UploaderPar,&len1);
			  Explain_UpPar(OutBuf+DataLen+len1,&CN_st_AgreeOn_Send_UploaderPar,&len1);
			  OutBuf[Len]=len1+12;
			  DataLen+=(len1+4);
			  CN_st_Fun_AscNumber.MoveByte(&CN_st_AgreeOn_Send_Basic,&CN_st_AgreeOn_Send_UploaderPar.CN_st_AgreeOn_Send_Basic,len1);
	}		}
	} 
   	*ReDataLen=DataLen;	 
}

static void Explain_UpLoaderDriver(uint8 *OutBuf,void *InputBuf,uint16 *ReDataLen)	//上传驾驶员ID
{	st_AgreeOn_Send_UpLoaderDriver	*ptst_AgreeOn_Send_UpLoaderDriver;
	uint16 DataLen,Len;
	ptst_AgreeOn_Send_UpLoaderDriver=InputBuf;
	Explain_GetSeverComPar(OutBuf,&ptst_AgreeOn_Send_UpLoaderDriver->CN_st_AgreeOn_Send_Basic,&DataLen);
	Len=CN_st_Fun_AscNumber.Strsize(ptst_AgreeOn_Send_UpLoaderDriver->ID);
	if(Len>sizeof(ptst_AgreeOn_Send_UpLoaderDriver->ID))
		Len=sizeof(ptst_AgreeOn_Send_UpLoaderDriver->ID);
	OutBuf[DataLen++]=Len;
	CN_st_Fun_AscNumber.MoveByte(OutBuf+DataLen,ptst_AgreeOn_Send_UpLoaderDriver->ID,Len);
	DataLen+=Len;
	OutBuf[DataLen++]=ptst_AgreeOn_Send_UpLoaderDriver->State;
	*ReDataLen=DataLen;	 	
}

static void Explain_UpLoaderHandMess(uint8 *OutBuf,void *InputBuf,uint16 *ReDataLen) //上传手机短信
{	st_AgreeOn_Send_UpLoaderHandMess	*ptst_AgreeOn_Send_UpLoaderHandMess;
	uint16 DataLen,Len;	
	ptst_AgreeOn_Send_UpLoaderHandMess=InputBuf;
	Explain_GetSeverComPar(OutBuf,&ptst_AgreeOn_Send_UpLoaderHandMess->CN_st_AgreeOn_Send_Basic,&DataLen);
   	Len=CN_st_Fun_AscNumber.Strsize(ptst_AgreeOn_Send_UpLoaderHandMess->ID);
	if(Len>sizeof(ptst_AgreeOn_Send_UpLoaderHandMess->ID))
		Len=sizeof(ptst_AgreeOn_Send_UpLoaderHandMess->ID);
	OutBuf[DataLen++]=Len;
	CN_st_Fun_AscNumber.MoveByte(OutBuf+DataLen,ptst_AgreeOn_Send_UpLoaderHandMess->ID,Len);
	DataLen+=Len;
	Len=CN_st_Fun_AscNumber.Strsize(ptst_AgreeOn_Send_UpLoaderHandMess->Phone);
	if(Len>sizeof(ptst_AgreeOn_Send_UpLoaderHandMess->Phone))
		Len=sizeof(ptst_AgreeOn_Send_UpLoaderHandMess->Phone);
	OutBuf[DataLen++]=Len;
	CN_st_Fun_AscNumber.MoveByte(OutBuf+DataLen,ptst_AgreeOn_Send_UpLoaderHandMess->Phone,Len);
	DataLen+=Len;
	Len=CN_st_Fun_AscNumber.Strsize(ptst_AgreeOn_Send_UpLoaderHandMess->Cut);
	if(Len>sizeof(ptst_AgreeOn_Send_UpLoaderHandMess->Cut))
		Len=sizeof(ptst_AgreeOn_Send_UpLoaderHandMess->Cut);
//	OutBuf[DataLen++]=Len;
	Len=CN_st_Fun_AscNumber.StrToUni(ptst_AgreeOn_Send_UpLoaderHandMess->Cut,OutBuf+DataLen,Len);
//	OutBuf[DataLen++]=Len;
//	CN_st_Fun_AscNumber.MoveByte(OutBuf+DataLen,ptst_AgreeOn_Send_UpLoaderHandMess->Cut,Len);
	DataLen+=Len;
	*ReDataLen=DataLen;
}

static void Explain_NoSem(uint8 *OutBuf,void *InputBuf,uint16 *ReDataLen) 			//盲区补偿信息
{ st_AgreeOn_Send_LogAndNoSem *ptst_st_AgreeOn_Send_LogAndNoSem	;
  uint16 DataLen,Len,i;	
  ptst_st_AgreeOn_Send_LogAndNoSem=InputBuf;
  DataLen=0;
  OutBuf[DataLen++]=(ptst_st_AgreeOn_Send_LogAndNoSem->ParID>>8);
  OutBuf[DataLen++]=(ptst_st_AgreeOn_Send_LogAndNoSem->ParID&0XFF);
  Explain_GetSeverComPar(OutBuf+DataLen,&ptst_st_AgreeOn_Send_LogAndNoSem->CN_Ba_st_AgreeOn_Send_Basic,&Len);
  DataLen+=Len;
  OutBuf[DataLen++]=((ptst_st_AgreeOn_Send_LogAndNoSem->Number>>0)&0xff); 
  for(i=0,Len=0;i<ptst_st_AgreeOn_Send_LogAndNoSem->Number;i++)
      {OutBuf[DataLen++]=((ptst_st_AgreeOn_Send_LogAndNoSem->DataLen[i]>>8)&0xff); 
	   OutBuf[DataLen++]=((ptst_st_AgreeOn_Send_LogAndNoSem->DataLen[i]>>0)&0xff);
	   CN_st_Fun_AscNumber.MoveByte(OutBuf+DataLen,&ptst_st_AgreeOn_Send_LogAndNoSem->X_BUF[Len],ptst_st_AgreeOn_Send_LogAndNoSem->DataLen[i]);
	   Len+=ptst_st_AgreeOn_Send_LogAndNoSem->DataLen[i];
	   DataLen+=ptst_st_AgreeOn_Send_LogAndNoSem->DataLen[i];
	  }
	 *ReDataLen=DataLen;

}
/*===========================================出租车专用协议=====================================================*/
static void Explain_UpLoaderFrom(uint8 *OutBuf,void *InputBuf,uint16 *ReDataLen) //上传订单抢答信息
{	st_AgreeOn_Send_UpLoaderFrom	*ptst_AgreeOn_Send_UpLoaderFrom;
	ptst_AgreeOn_Send_UpLoaderFrom=InputBuf;
	OutBuf[0]=((ptst_AgreeOn_Send_UpLoaderFrom->ID>>8)&0xff);
	OutBuf[1]=((ptst_AgreeOn_Send_UpLoaderFrom->ID)&0xff);
	*ReDataLen=2;
}
static void Explain_OverFromErro(uint8 *OutBuf,void *InputBuf,uint16 *ReDataLen)//上传订单未能完成原因
{	st_AgreeOn_Send_OverFromErro	*ptst_AgreeOn_Send_OverFromErro;
	OutBuf[0]=((ptst_AgreeOn_Send_OverFromErro->ID>>8)&0xff);
	OutBuf[1]=((ptst_AgreeOn_Send_OverFromErro->ID)&0xff);	
	OutBuf[2]=((ptst_AgreeOn_Send_OverFromErro->CanceID>>8)&0xff);
	OutBuf[3]=((ptst_AgreeOn_Send_OverFromErro->CanceID)&0xff);
   	*ReDataLen=4;
}
static void Explain_PriceData(uint8 *OutBuf,void *InputBuf,uint16 *ReDataLen)//上传计价器信息
{


}
