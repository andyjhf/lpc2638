#define De_TakeData_Compiler
#include "TakeData.h"
/*==============================================维护流水表=====================================================*/
static uint16 ReadFlow(uint16 Recoder,void *Buf)  											//读取流水表
{	st_NoFlow_Table	CN_st_NoFlow_Table;	
	uint16 Cuit;				
	CN_st_Fun_File.ReadRecoder(CN_st_File_fd.NoFlowfd,Recoder,&CN_st_NoFlow_Table);
	Cuit=CN_st_Fun_File.GetPointNum(CN_st_File_fd.Workfd,CN_st_NoFlow_Table.AcceSpace)-1;
	if((CN_st_NoFlow_Table.ID==De_Access_Type_ReduceWork)||(CN_st_NoFlow_Table.ID==De_Access_Type_ReduceTrack))	//压缩回传
	{	CN_st_Fun_File.ReadRecoder(CN_st_File_fd.Reducefd,Cuit,Buf);
		return De_Suc_AccessBasic;	
	}
	else 
	{	CN_st_Fun_File.ReadRecoder(CN_st_File_fd.Workfd,Cuit,Buf);
		return De_Suc_AccessBasic;
	}
}
static uint16 WriteFlow(uint16 ID,st_WorkFlow_Table	*ptst_WorkFlow_Table)					//写流水表
{	st_NoFlow_Table	CN_st_NoFlow_Table;
	st_Reduce_Table	CN_st_AgreeOn_Reduce;
	uint16 Tail;
	CN_st_Fun_RTC.Read(ptst_WorkFlow_Table->DateTimer);
	CN_st_Fun_File.WriteRecoder(CN_st_File_fd.Workfd,0,ptst_WorkFlow_Table);
	CN_st_Fun_File.ReadHeadTail(CN_st_File_fd.Workfd,&Tail,De_rwFile_Point_Tail);
	if((ID==De_Access_Type_ReduceWork)||(ID==De_Access_Type_ReduceTrack)||(ID==De_Access_Type_ReduceOver))//压缩回传记录
	{	CN_st_Fun_File.ReadRecoder(CN_st_File_fd.Reducefd,0,&CN_st_AgreeOn_Reduce);
		if(CN_st_AgreeOn_Reduce.CN_st_AgreeOn_Reduce.Number==0)	 				//没有的话，就不发送
			return De_Erro_NoSend;
		if(ID==De_Access_Type_ReduceOver)  												//压缩回传计算
			return SendReduceData();				
		if(CN_st_AgreeOn_Reduce.Number>=CN_st_AgreeOn_Reduce.CN_st_AgreeOn_Reduce.Space)	//数量超过时
			SendReduceData();
		if(JugeReduceData()==De_Suc_AccessBasic)
			SendReduceData();
		if(JugeReduceLen()==De_Suc_AccessBasic)
			SendReduceData();
		CN_st_Fun_File.ReadRecoder(CN_st_File_fd.Reducefd,0,&CN_st_AgreeOn_Reduce);
		if(CN_st_AgreeOn_Reduce.CN_st_AgreeOn_Reduce.Number==0)	 				//没有的话，就不发送
			return De_Erro_NoSend;
		CN_st_AgreeOn_Reduce.Data[CN_st_AgreeOn_Reduce.Number]=Tail;
		CN_st_AgreeOn_Reduce.Number++;
		CN_st_Fun_File.WriteRecoder(CN_st_File_fd.Reducefd,0,&CN_st_AgreeOn_Reduce);
		if(CN_st_AgreeOn_Reduce.Number>=CN_st_AgreeOn_Reduce.CN_st_AgreeOn_Reduce.Space)	//数量超过时
			return SendReduceData();
		if(JugeReduceData()==De_Suc_AccessBasic)
			return SendReduceData();
		if(JugeReduceLen()==De_Suc_AccessBasic)
			return SendReduceData();
		return De_Erro_NoSend;	
	}
	else																					//非压缩回传数据
	{	CN_st_NoFlow_Table.ID=ID;
		CN_st_NoFlow_Table.AcceSpace=Tail;
		CN_st_Fun_File.WriteRecoder(CN_st_File_fd.NoFlowfd,0,&CN_st_NoFlow_Table);
		return De_Suc_AccessBasic;	   				//发送
	}
	return De_Erro_NoSend;	
}

static uint16 JugeReduceData(void)
{	st_Reduce_Table	CN_st_Reduce_Table;
	st_WorkFlow_Table	CN_st_WorkFlow_Table;
	uint16 Cuit;
	CN_st_Fun_File.ReadRecoder(CN_st_File_fd.Reducefd,0,&CN_st_Reduce_Table);
	if(CN_st_Reduce_Table.Number<1)
		return De_Erro_NoSend;
	Cuit=CN_st_Fun_File.GetPointNum(CN_st_File_fd.Workfd,CN_st_Reduce_Table.Data[CN_st_Reduce_Table.CN_st_AgreeOn_Reduce.Number-1])-1;
	CN_st_Fun_File.ReadRecoder(CN_st_File_fd.Workfd,Cuit,&CN_st_WorkFlow_Table);
	if(CN_st_Fun_AscNumber.CompareBuf(CN_st_WorkFlow_Table.CN_st_AgreeOn_Send_Basic.State,
	App_CN_st_WorkFlow_Table.CN_st_AgreeOn_Send_Basic.State,sizeof(CN_st_WorkFlow_Table.CN_st_AgreeOn_Send_Basic.State))!=0)
		return De_Suc_AccessBasic;
	if(CN_st_Fun_AscNumber.CompareBuf(CN_st_WorkFlow_Table.CN_st_AgreeOn_Send_Basic.CN_st_Data_Gps.CN_st_Gps_Data_GPRMC
	.DateTime,App_CN_st_WorkFlow_Table.CN_st_AgreeOn_Send_Basic.CN_st_Data_Gps.CN_st_Gps_Data_GPRMC.DateTime,
	4)!=0)
		return De_Suc_AccessBasic;
	return De_Erro_NoSend;						
}

static uint16 JugeReduceLen(void)
{	st_Reduce_Table	CN_st_Reduce_Table;
	uint16 DataLen;
	CN_st_Fun_File.ReadRecoder(CN_st_File_fd.Reducefd,0,&CN_st_Reduce_Table);
	if(CN_st_Reduce_Table.Number==0)
		return De_Erro_NoSend;	
	CN_st_Reduce_Table.ReadParTable=ReadParTable;
	CN_st_Fun_Tz_Send.Write(X_BUF,&CN_st_Reduce_Table,&DataLen,De_Dev_Order_UpLoaderReduce);
	if(((DataLen+17)+DataLen/CN_st_Reduce_Table.Number)>512)
		return De_Suc_AccessBasic; 
	return De_Erro_NoSend;	
}




static uint16 SendReduceData(void)
{	st_Reduce_Table	CN_st_Reduce_Table;
	st_NoFlow_Table	CN_st_NoFlow_Table;
	uint16 Tail;
	CN_st_Fun_File.ReadHeadTail(CN_st_File_fd.Reducefd,&Tail,De_rwFile_Point_Tail);
	CN_st_Fun_File.ReadRecoder(CN_st_File_fd.Reducefd,0,&CN_st_Reduce_Table);
	if(CN_st_Reduce_Table.Number==0)
		return De_Erro_NoSend;
	if(CN_st_Reduce_Table.CN_st_AgreeOn_Reduce.Data==De_AgreeOn_Reduce_Data_Space)
		CN_st_NoFlow_Table.ID=De_Access_Type_ReduceTrack;
	else
		CN_st_NoFlow_Table.ID=De_Access_Type_ReduceWork;
	CN_st_NoFlow_Table.AcceSpace=Tail;
	CN_st_Fun_AscNumber.MoveByte(CN_st_NoFlow_Table.DateTimer,App_CN_st_WorkFlow_Table.DateTimer,
	sizeof(CN_st_NoFlow_Table.DateTimer));
	CN_st_Fun_File.WriteRecoder(CN_st_File_fd.NoFlowfd,0,&CN_st_NoFlow_Table);
	CN_st_Reduce_Table.Number=0;
	if(CN_st_Reduce_Table.CN_st_AgreeOn_Reduce.Number!=0xffff)
		CN_st_Reduce_Table.CN_st_AgreeOn_Reduce.Number--;
	CN_st_Fun_File.WriteRecoder(CN_st_File_fd.NoFlowfd,0,&CN_st_NoFlow_Table);
   	return De_Suc_AccessBasic;	
}
static uint16 ReadDataFlow(uint16 Recoder,st_WorkFlow_Table	*ptst_WorkFlow_Table)			//读流水表内容
{	uint16 Cuit;
	Cuit=CN_st_Fun_File.GetPointNum(CN_st_File_fd.Workfd,Recoder)-1;
	return CN_st_Fun_File.ReadRecoder(CN_st_File_fd.Workfd,Cuit,ptst_WorkFlow_Table);
}

static uint16 GetFlowWaringType(uint16 Recoder,uint8 *Type)
{ 	st_NoFlow_Table	CN_st_NoFlow_Table;	
	uint16 Cuit;				
	Cuit=CN_st_Fun_File.GetPointNum(CN_st_File_fd.NoFlowfd,Recoder);
	CN_st_Fun_File.ReadRecoder(CN_st_File_fd.NoFlowfd,Cuit,&CN_st_NoFlow_Table);
	*Type=CN_st_NoFlow_Table.ID;
	return De_Suc_AccessBasic;
}
		
static uint16 ReadSpace(uint16 Space)
{	st_Send_Table	CN_st_Send_Table;
	CN_st_Fun_AscNumber.ClsArray(&CN_st_Send_Table,sizeof(st_Send_Table));
	CN_st_Fun_File.ReadRecoder(CN_st_File_fd.Sendfd,0,&CN_st_Send_Table);
	return CN_st_Send_Table.SendSpace[Space]+1;
}

static void AddSpace(uint16 Space,uint16 Number)
{	st_Data_FileUse	CN_st_Data_FileUse;
	st_Send_Table	CN_st_Send_Table;
	uint16 Tail;
	CN_st_Fun_File.ReadRecoder(CN_st_File_fd.Sendfd,0,&CN_st_Send_Table);
	if(Number==De_Space_Set)							//表示该位置置位
	{	CN_st_Fun_File.ReadHeadTail(CN_st_File_fd.NoFlowfd,&Tail,De_rwFile_Point_Tail);	
		CN_st_Send_Table.SendSpace[Space]=Tail-1;
		CN_st_Fun_File.WriteRecoder(CN_st_File_fd.Sendfd,0,&CN_st_Send_Table);
	}
	else
	{	CN_st_Fun_File.ReadPor(CN_st_File_fd.NoFlowfd,&CN_st_Data_FileUse);
		for(Tail=0;Tail<Number;Tail++)
		{	CN_st_Send_Table.SendSpace[Space]++;
			if(CN_st_Send_Table.SendSpace[Space]>=CN_st_Data_FileUse.RecoderNumber)
				CN_st_Send_Table.SendSpace[Space]=0;
		}	
	   	CN_st_Fun_File.WriteRecoder(CN_st_File_fd.Sendfd,0,&CN_st_Send_Table);
	}		
}
//读取压缩回传的参数
static uint16 ReadParTable(uint16 Recoder,st_AgreeOn_Send_UploaderPar	*ptst_AgreeOn_Send_UploaderPar)
{	st_WorkFlow_Table	CN_st_WorkFlow_Table;
	ReadDataFlow(Recoder,&CN_st_WorkFlow_Table);
	CN_st_Fun_AscNumber.MoveByte(&ptst_AgreeOn_Send_UploaderPar->CN_st_AgreeOn_Send_Basic,
	&CN_st_WorkFlow_Table.CN_st_AgreeOn_Send_Basic,sizeof(st_AgreeOn_Send_Basic));

	CN_st_Fun_AscNumber.MoveByte(&ptst_AgreeOn_Send_UploaderPar->CN_st_WorkVal_Tabel,
	&CN_st_WorkFlow_Table.CN_st_WorkVal_Tabel,sizeof(st_WorkVal_Tabel));
}

/*==========================================维护照片表==========================================================*/
static uint32 GetPhonesSize(uint16 Recoder)							   //获取照片文件大小
{	st_File_Photo_Tail	CN_st_File_Photo_Tail;
	st_File_Photo_Data	CN_st_File_Photo_Data;
	uint16 Cuit;
	uint32 DataLen;
	Cuit=CN_st_Fun_File.GetPointNum(CN_st_File_fd.Photofd,Recoder)-1;
	CN_st_Fun_File.ReadRecoder(CN_st_File_fd.Photofd,Cuit,&CN_st_File_Photo_Tail);
   	Cuit=CN_st_Fun_File.GetPointNum(CN_st_File_fd.PhotoDatafd,CN_st_File_Photo_Tail.FrontTail);
	Recoder=CN_st_Fun_File.GetPointNum(CN_st_File_fd.PhotoDatafd,CN_st_File_Photo_Tail.CurrentTail);
	Cuit=Recoder-Cuit;
	CN_st_Fun_File.ReadRecoder(CN_st_File_fd.PhotoDatafd,Recoder-1,&CN_st_File_Photo_Data);
	DataLen=Cuit*De_Max_Bag_Length;
	DataLen=DataLen-De_Max_Bag_Length+CN_st_File_Photo_Data.DataLength;
	return DataLen;
}
static uint16 GetPhoneCut(uint16 Recoder,uint32 StartSize,uint16 DataLen,uint8 *Buf)  //获取照片文件内容
{	st_File_Photo_Tail	CN_st_File_Photo_Tail;
	st_File_Photo_Data	CN_st_File_Photo_Data;
	uint16 Cuit,Number,Offset,Len;		
	Cuit=CN_st_Fun_File.GetPointNum(CN_st_File_fd.Photofd,Recoder)-1;
	CN_st_Fun_File.ReadRecoder(CN_st_File_fd.Photofd,Cuit,&CN_st_File_Photo_Tail);
	Cuit=CN_st_Fun_File.GetPointNum(CN_st_File_fd.PhotoDatafd,CN_st_File_Photo_Tail.FrontTail);
	Number=StartSize/De_Max_Bag_Length;
	CN_st_Fun_File.ReadRecoder(CN_st_File_fd.PhotoDatafd,Cuit+Number,&CN_st_File_Photo_Data);
	Offset=StartSize%De_Max_Bag_Length;
	Len=DataLen;
	if(Len>CN_st_File_Photo_Data.DataLength-Offset)
		Len=CN_st_File_Photo_Data.DataLength-Offset;
	CN_st_Fun_AscNumber.MoveByte(Buf,CN_st_File_Photo_Data.Data+Offset,Len);
	if(Len<DataLen)
	{	CN_st_Fun_File.ReadRecoder(CN_st_File_fd.PhotoDatafd,Cuit+Number+1,&CN_st_File_Photo_Data);
		CN_st_Fun_AscNumber.MoveByte(Buf+Len,CN_st_File_Photo_Data.Data,DataLen-Len);
	}			
	return De_Suc_AccessBasic;
}	 
static uint16 WritePhone(uint16 *Recoder)  												//拍照
{	st_BoxData_Vid	CN_st_BoxData_Vid;
	uint8 err;
	CN_st_Fun_AscNumber.ClsArray(&CN_st_BoxData_Vid,sizeof(st_BoxData_Vid));
	CN_st_BoxData_Vid.ReBox=OSMboxCreate(NULL);
	CN_st_BoxData_Vid.Command=De_BoxData_Vid_Command_Operation;
	CN_st_BoxData_Vid.TailFd=CN_st_File_fd.Photofd;
	CN_st_BoxData_Vid.DataFd=CN_st_File_fd.PhotoDatafd;
	CN_st_BoxData_Vid.PhotoType=De_PhotoType_320x240;
	OSQPost (Photo_Q,&CN_st_BoxData_Vid);												//拍照命令
	OSMboxPend (CN_st_BoxData_Vid.ReBox,0,&err);
	OSMboxDel(CN_st_BoxData_Vid.ReBox,OS_DEL_NO_PEND,&err);
	if(CN_st_BoxData_Vid.Result!=De_Suc_Photo)
		return CN_st_BoxData_Vid.Result;	
	CN_st_Fun_File.ReadHeadTail(CN_st_File_fd.Photofd,Recoder,De_rwFile_Point_Tail);
	return De_Suc_AccessBasic;
}
/*============================================维护状态表=======================================================*/
static void ClearState(uint8 Number)  		
{	st_Warning_State_Table	CN_st_Warning_State_Table;	
	uint8 Point,BitNumber;
	if(CN_st_Fun_File.ReadRecoder(CN_st_File_fd.WaringStatefd,0,&CN_st_Warning_State_Table)!=De_Suc_File)
		CN_st_Fun_AscNumber.ClsArray(&CN_st_Warning_State_Table,sizeof(st_Warning_State_Table));
	Point=Number/8;
	BitNumber=(Number&0x07);
	CN_st_Warning_State_Table.State[Point]=(CN_st_Warning_State_Table.State[Point]|(0x01<<BitNumber));		
	CN_st_Fun_File.WriteRecoder(CN_st_File_fd.WaringStatefd,0,&CN_st_Warning_State_Table);
}
static uint8 GetState(uint8 Number)
{	st_Warning_State_Table	CN_st_Warning_State_Table;
	uint16 Point,BitNumber;
	if(CN_st_Fun_File.ReadRecoder(CN_st_File_fd.WaringStatefd,0,&CN_st_Warning_State_Table)!=De_Suc_File)
		CN_st_Fun_AscNumber.ClsArray(&CN_st_Warning_State_Table,sizeof(st_Warning_State_Table));
	Point=Number/8;
	BitNumber=(Number&0x07);		
	if(CN_st_Warning_State_Table.State[Point]&(0x01<<BitNumber))
		return De_Waring_State_Yes;
	return De_Waring_State_No;
}
static void SetState(uint8 Number)
{	st_Warning_State_Table	CN_st_Warning_State_Table;	
	uint8 Point,BitNumber;
	if(CN_st_Fun_File.ReadRecoder(CN_st_File_fd.WaringStatefd,0,&CN_st_Warning_State_Table)!=De_Suc_File)
		CN_st_Fun_AscNumber.ClsArray(&CN_st_Warning_State_Table,sizeof(st_Warning_State_Table));
	Point=Number/8;
	BitNumber=(Number&0x07);
	CN_st_Warning_State_Table.State[Point]=(CN_st_Warning_State_Table.State[Point]&(~(0x01<<BitNumber)));	
	CN_st_Fun_File.WriteRecoder(CN_st_File_fd.WaringStatefd,0,&CN_st_Warning_State_Table);
}
/*=========================================维护区域数据=======================================================*/
static uint16 GetAreaData(void *Data,uint16 Number,uint8 *Type)
{	st_Area_Infor_Table	CN_st_Area_Infor_Table;
	uint16 Cuit;
	if(CN_st_Fun_File.ReadRecoder(CN_st_File_fd.Areafd,0,&CN_st_Area_Infor_Table)!=De_Suc_File)
		return De_Erro_Ara_NoData;
	if(Number>=CN_st_Area_Infor_Table.Number)
		return De_Erro_Ara_NoData;
	*Type=CN_st_Area_Infor_Table.CN_st_Area_Infor_File[Number].Type;
	if(CN_st_Area_Infor_Table.CN_st_Area_Infor_File[Number].Type==De_Type_Round)			
	{	Cuit=CN_st_Fun_File.GetPointNum(CN_st_File_fd.Roundfd,CN_st_Area_Infor_Table.
			CN_st_Area_Infor_File[Number].Space)-1;
		CN_st_Fun_File.ReadRecoder(CN_st_File_fd.Roundfd,Cuit,Data);
		return De_Suc_AccessBasic;
	}
	else if(CN_st_Area_Infor_Table.CN_st_Area_Infor_File[Number].Type==De_Type_Rectangle)
	{	Cuit=CN_st_Fun_File.GetPointNum(CN_st_File_fd.Rectanglefd,CN_st_Area_Infor_Table.
			CN_st_Area_Infor_File[Number].Space)-1;
		CN_st_Fun_File.ReadRecoder(CN_st_File_fd.Rectanglefd,Cuit,Data);
		return De_Suc_AccessBasic;
	}
	return De_Erro_Ara_NoData;
}
static uint16 AccessAear(void *Buf,uint8 Type)
{	st_Area_Infor_Table	CN_st_Area_Infor_Table;
	st_AgreeOn_SetRectangle_Par	*ptst_AgreeOn_SetRectangle_Par;
	st_AgreeOn_SetRound_Par		*ptst_AgreeOn_SetRound_Par;
	uint16 Number;
	if(CN_st_Fun_File.ReadRecoder(CN_st_File_fd.Areafd,0,&CN_st_Area_Infor_Table)!=De_Suc_File)
		CN_st_Fun_AscNumber.ClsArray(&CN_st_Area_Infor_Table,sizeof(st_Area_Infor_Table));	
	if(Type==De_Type_Round)
	{	ptst_AgreeOn_SetRound_Par=Buf;
		Number=JugeID(ptst_AgreeOn_SetRound_Par->ID,&CN_st_Area_Infor_Table);
		if(Number>=sizeof(CN_st_Area_Infor_Table.CN_st_Area_Infor_File)/sizeof(st_Area_Infor_File))	 //已经满了
			return De_Erro_Ara_NoData;
		CN_st_Fun_File.WriteRecoder(CN_st_File_fd.Roundfd,0,Buf);
		CN_st_Area_Infor_Table.CN_st_Area_Infor_File[Number].ID=ptst_AgreeOn_SetRound_Par->ID;
		CN_st_Area_Infor_Table.CN_st_Area_Infor_File[Number].Type=De_Type_Round;
		CN_st_Fun_File.ReadHeadTail(CN_st_File_fd.Roundfd,
		&CN_st_Area_Infor_Table.CN_st_Area_Infor_File[Number].Space,De_rwFile_Point_Tail);
		CN_st_Fun_File.WriteRecoder(CN_st_File_fd.Areafd,0,&CN_st_Area_Infor_Table);
	}
	else if(Type==De_Type_Rectangle)
	{	ptst_AgreeOn_SetRectangle_Par=Buf;
		Number=JugeID(ptst_AgreeOn_SetRectangle_Par->ID,&CN_st_Area_Infor_Table);
		if(Number>=sizeof(CN_st_Area_Infor_Table.CN_st_Area_Infor_File)/sizeof(st_Area_Infor_File))	 //已经满了
			return De_Erro_Ara_NoData;
		CN_st_Fun_File.WriteRecoder(CN_st_File_fd.Rectanglefd,0,Buf);
		CN_st_Area_Infor_Table.CN_st_Area_Infor_File[Number].ID=ptst_AgreeOn_SetRound_Par->ID;
		CN_st_Area_Infor_Table.CN_st_Area_Infor_File[Number].Type=De_Type_Rectangle;
		CN_st_Fun_File.ReadHeadTail(CN_st_File_fd.Rectanglefd,
		&CN_st_Area_Infor_Table.CN_st_Area_Infor_File[Number].Space,De_rwFile_Point_Tail);
		CN_st_Fun_File.WriteRecoder(CN_st_File_fd.Areafd,0,&CN_st_Area_Infor_Table);
	}
	return De_Suc_AccessBasic;
}

static void DelAear(uint16 ID)//删除圆形路线
{	st_Area_Infor_Table	CN_st_Area_Infor_Table;	
	uint16 j;
	if(CN_st_Fun_File.ReadRecoder(CN_st_File_fd.Parameterfd,0,&CN_st_Area_Infor_Table)!=De_Suc_File)
		CN_st_Fun_AscNumber.ClsArray(&CN_st_Area_Infor_Table,sizeof(st_Area_Infor_Table));
	if((j=JugeID(ID,&CN_st_Area_Infor_Table))==CN_st_Area_Infor_Table.Number)
		return ;
	if(j!=(CN_st_Area_Infor_Table.Number-1))
	{	CN_st_Fun_AscNumber.MoveByte(&CN_st_Area_Infor_Table.CN_st_Area_Infor_File[j],
		&CN_st_Area_Infor_Table.CN_st_Area_Infor_File[j+1],
		(CN_st_Area_Infor_Table.Number-(j+1))*sizeof(st_Area_Infor_File));
	}
	CN_st_Area_Infor_Table.Number--;
   	CN_st_Fun_File.WriteRecoder(CN_st_File_fd.Parameterfd,0,&CN_st_Area_Infor_Table);
}
static uint16 JugeID(uint16 ID,st_Area_Infor_Table	*ptst_Area_Infor_Table)
{	uint16 i;
	for(i=0;i<ptst_Area_Infor_Table->Number;i++)
	{	if(ptst_Area_Infor_Table->CN_st_Area_Infor_File[i].ID==ID)
			break;	
	}
	return i;
}
