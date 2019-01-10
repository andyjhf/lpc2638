#define De_DownFile_Compiler
#include "DownFile.h"
static uint16 Init(void)
{	
	if(DownFileSem==NULL)
		DownFileSem=OSSemCreate(1); 
	ClsArray((uint8 *)&CN_st_DownFile_BufFd,sizeof(CN_st_DownFile_BufFd));
	return De_Suc_DownFile;
}
static uint16 Open(uint8 *FileName,uint16 *fd)
{	uint8 err;
	uint16 Result;
	#ifdef OS_ADD
	OSSemPend(DownFileSem, 0, &err);				
	#endif
	Result=Open1(FileName,fd);
	#ifdef OS_ADD
	OSSemPost(DownFileSem);
	#endif
	return Result;
}
static uint16 CreateFile(uint8 *FileName,uint32 FileLength)
{	uint8 err;
	uint16 Result;
	#ifdef OS_ADD
	OSSemPend(DownFileSem, 0, &err);				
	#endif
	Result=CreateFile1(FileName,FileLength);
	#ifdef OS_ADD
	OSSemPost(DownFileSem);
	#endif
	return Result;
}
static uint16 ReadFile(uint16 fd,void *Buf,uint32 StartAddree,uint16 DataLength)
{	uint8 err;
	uint16 Result;
	#ifdef OS_ADD
	OSSemPend(DownFileSem, 0, &err);				
	#endif
	Result=ReadFile1(fd,Buf,StartAddree,DataLength);
	#ifdef OS_ADD
	OSSemPost(DownFileSem);
	#endif
	return Result;	
}
static uint16 WriteFile(uint16 fd,void *Buf,uint16 DataLength)
{	uint8 err;
	uint16 Result;
	#ifdef OS_ADD
	OSSemPend(DownFileSem, 0, &err);				
	#endif
	Result=WriteFile1(fd,Buf,DataLength);
	#ifdef OS_ADD
	OSSemPost(DownFileSem);
	#endif
	return Result;
}
static uint16 Close(uint16 fd)
{	uint8 err;
	uint16 Result;
	#ifdef OS_ADD
	OSSemPend(DownFileSem, 0, &err);				
	#endif
	Result=Close1(fd);
	#ifdef OS_ADD
	OSSemPost(DownFileSem);
	#endif
	return Result;
}
static uint16 GetFileProperty(uint16 fd,st_DownFile_Infor *ptst_DownFile_Infor)
{	uint8 err;
	uint16 Result;
	#ifdef OS_ADD
	OSSemPend(DownFileSem, 0, &err);				
	#endif
	Result=GetFileProperty1(fd,ptst_DownFile_Infor);
	#ifdef OS_ADD
	OSSemPost(DownFileSem);
	#endif
	return Result;
}
static uint16 SetFileLength(uint16 fd,uint32 FileLength)
{	uint8 err;
	uint16 Result;
	#ifdef OS_ADD
	OSSemPend(DownFileSem, 0, &err);				
	#endif
	Result=SetFileLength1(fd,FileLength);
	#ifdef OS_ADD
	OSSemPost(DownFileSem);
	#endif
	return Result;
}
static uint16 SetFileName(uint16 fd,uint8 *FileName)
{	uint8 err;
	uint16 Result;
	#ifdef OS_ADD
	OSSemPend(DownFileSem, 0, &err);				
	#endif
	Result=SetFileName1(fd,FileName);
	#ifdef OS_ADD
	OSSemPost(DownFileSem);
	#endif
	return Result;	
}
static uint16 CleanProperty(uint16 fd)
{	uint8 err;
	uint16 Result;
	#ifdef OS_ADD
	OSSemPend(DownFileSem, 0, &err);				
	#endif
	Result=CleanProperty1(fd);
	#ifdef OS_ADD
	OSSemPost(DownFileSem);
	#endif
	return Result;
}
static uint16 CreateFile1(uint8 *FileName,uint32 FileLength)
{	uint16 Result,fd;
	uint16 RecoderSum;
	uint16 DataLength;
	uint8 FileName1[9];
	st_DownFile_Infor CN_st_DownFile_Infor;
	ClsArray((uint8 *)&CN_st_DownFile_Infor,sizeof(st_DownFile_Infor));
	ClsArray(FileName1,sizeof(FileName1));
	RecoderSum=FileLength/512;
	if(FileLength%512)
		RecoderSum++;
	if(RecoderSum>65500)
		return De_Erro_DownFile_TooMuch;
	FileName1[0]='_';
	DataLength=Strsize(FileName);
	if(DataLength>7)
		MoveByte(&FileName1[1],FileName,7);
	else
		MoveByte(&FileName1[1],FileName,DataLength);
	if((Result=CN_st_Fun_File.CreateRecoder(FileName1,sizeof(st_DownFile_Infor),1,De_File_Property_Cycle))!=De_Suc_File)
		return Result;
	if((Result=CN_st_Fun_File.CreateRecoder(FileName,512,RecoderSum,De_File_Property_Cycle))!=De_Suc_File)	// 创建定长记录文件 ; 	
		return Result;
	if((Result=CN_st_Fun_File.Open(FileName1,&fd))!=De_Suc_File)
		return Result;
	CN_st_Fun_File.ReadHeadTail(fd,&CN_st_DownFile_Infor.HeadRecoderNum,De_rwFile_Point_Tail);
	CN_st_DownFile_Infor.TailRecoderNum=CN_st_DownFile_Infor.HeadRecoderNum;
	CN_st_Fun_File.WriteRecoder(fd,0,&CN_st_DownFile_Infor);
	CN_st_Fun_File.Close(fd);
	return De_Suc_DownFile;
}
static uint16 Open1(uint8 *FileName,uint16 *fd)
{	uint8 i;
	uint8 FileName1[9];
	uint16 Result,DataLength;
	
	for(i=0;i<Max_DownFile_Open;i++)
	{	if(CN_st_DownFile_BufFd.CN_st_DownFile_UseFd[i].State==De_DownFile_Close)
			break;
	}
	if(i==Max_DownFile_Open)
		return De_Erro_DownFile_NoFd;
	ClsArray(FileName1,sizeof(FileName1));
	FileName1[0]='_';
	DataLength=Strsize(FileName);
	if(DataLength>7)
		MoveByte(&FileName1[1],FileName,7);
	else
		MoveByte(&FileName1[1],FileName,DataLength);
	if((Result=CN_st_Fun_File.Open(FileName1,&CN_st_DownFile_BufFd.CN_st_DownFile_UseFd[i].PropertyFd))!=De_Suc_File)
		return Result;
	if((Result=CN_st_Fun_File.Open(FileName,&CN_st_DownFile_BufFd.CN_st_DownFile_UseFd[i].FileFd))!=De_Suc_File)	// 创建定长记录文件 ; 	
	{	CN_st_Fun_File.Close(CN_st_DownFile_BufFd.CN_st_DownFile_UseFd[i].PropertyFd);
		return Result;
	}
	*fd=i;
	CN_st_DownFile_BufFd.CN_st_DownFile_UseFd[i].State=De_DownFile_Open;
	return De_Suc_DownFile;
}

static uint16 ReadFile1(uint16 fd,void *Buf,uint32 StartAddree,uint16 DataLength)
{	uint16 Result,Offset,StartNum;
	uint16 RecoderNumber,i;
	st_DownFile_Infor CN_st_DownFile_Infor;
	uint8 *Buf1; 
//	if(DataLength==0)				  								//数据长度为0，则读该文件的属性
//		return CN_st_Fun_File.ReadRecoder(CN_st_DownFile_BufFd.CN_st_DownFile_UseFd[fd].PropertyFd,0,Buf);
	Buf1=Buf;
	CN_st_Fun_File.ReadRecoder(CN_st_DownFile_BufFd.CN_st_DownFile_UseFd[fd].PropertyFd,0,&CN_st_DownFile_Infor);
	StartNum=CN_st_Fun_File.GetPointNum(CN_st_DownFile_BufFd.CN_st_DownFile_UseFd[fd].FileFd,CN_st_DownFile_Infor.HeadRecoderNum);	
	for(i=0;i<DataLength;i+=Offset,StartAddree+=Offset)
	{	Offset=StartAddree%512;
	    Offset=512-Offset;
		if((Offset+i)>DataLength)
			Offset=DataLength-i;
		RecoderNumber=(StartAddree/512)+StartNum;	
		if((Result=CN_st_Fun_File.ReadRecoder(CN_st_DownFile_BufFd.CN_st_DownFile_UseFd[fd].FileFd,RecoderNumber,DownFile_BUF))!=De_Suc_File)
			return Result;
		MoveByte(Buf1,&DownFile_BUF[StartAddree%512],Offset);
		Buf1+=Offset;
	}
	return De_Suc_DownFile;	
}

static uint16 WriteFile1(uint16 fd,void *Buf,uint16 DataLength)
{	uint16 Result;
	st_DownFile_Infor CN_st_DownFile_Infor; 
//	if(DataLength==0)				  								//数据长度为0，则修改该文件的属性
//		return CN_st_Fun_File.WriteRecoder(CN_st_DownFile_BufFd.CN_st_DownFile_UseFd[fd].PropertyFd,0,Buf);
	CN_st_Fun_File.ReadRecoder(CN_st_DownFile_BufFd.CN_st_DownFile_UseFd[fd].PropertyFd,0,&CN_st_DownFile_Infor);
	if((Result=CN_st_Fun_File.WriteRecoder(CN_st_DownFile_BufFd.CN_st_DownFile_UseFd[fd].FileFd,0,Buf))!=De_Suc_File)
		return Result;
	CN_st_Fun_File.ReadHeadTail(CN_st_DownFile_BufFd.CN_st_DownFile_UseFd[fd].FileFd,&CN_st_DownFile_Infor.TailRecoderNum,De_rwFile_Point_Tail);
	CN_st_DownFile_Infor.RevFileLen+=DataLength;
	if((CN_st_DownFile_Infor.RevFileLen==CN_st_DownFile_Infor.TotalFileLen)&&(CN_st_DownFile_Infor.TotalFileLen!=0))
		CN_st_DownFile_Infor.UpFlag=1;	
	if((Result=CN_st_Fun_File.WriteRecoder(CN_st_DownFile_BufFd.CN_st_DownFile_UseFd[fd].PropertyFd,0,&CN_st_DownFile_Infor))!=De_Suc_File)
		return Result;
	return De_Suc_DownFile;
/*	for(i=0;i<DataLength;i+=Offset,StartAddree+=Offset)
	{	Offset=StartAddree%512;
	    Offset=512-Offset;
		if((Offset+i)>DataLength)
			Offset=DataLength-i;
		RecoderNumber=(StartAddree/512)+1;
		MoveByte(DownFile_BUF[StartAddree%512],Buf,Offset);	
		if((Result=CN_st_Fun_File.WriteRecoder(CN_st_BinFile_BufFd.CN_st_BinFile_UseFd[fd].FileFd,RecoderNumber,DownFile_BUF))!=De_Suc_File)
			return Result;	
	}	 	
	return De_Suc_BinFile; */
}

static uint16 Close1(uint16 fd)
{	if(CN_st_DownFile_BufFd.CN_st_DownFile_UseFd[fd].State!=De_DownFile_Open)
		return De_Erro_DownFile_NoFd;
	CN_st_Fun_File.Close(CN_st_DownFile_BufFd.CN_st_DownFile_UseFd[fd].PropertyFd);
	CN_st_Fun_File.Close(CN_st_DownFile_BufFd.CN_st_DownFile_UseFd[fd].FileFd);
	CN_st_DownFile_BufFd.CN_st_DownFile_UseFd[fd].State=De_DownFile_Close;
	return De_Suc_DownFile;
}
static uint16 GetFileProperty1(uint16 fd,st_DownFile_Infor *ptst_DownFile_Infor)
{	uint16 Result;
	st_DownFile_Infor CN_st_DownFile_Infor;
	if((Result=CN_st_Fun_File.ReadRecoder(CN_st_DownFile_BufFd.CN_st_DownFile_UseFd[fd].PropertyFd,0,&CN_st_DownFile_Infor))!=De_Suc_File)
		return Result;
	MoveByte((uint8 *)ptst_DownFile_Infor,(uint8 *)&CN_st_DownFile_Infor,sizeof(st_DownFile_Infor));
	return De_Suc_DownFile;		
}
static uint16 SetFileLength1(uint16 fd,uint32 FileLength)
{	uint16 Result;
	st_DownFile_Infor CN_st_DownFile_Infor;
	if((Result=CN_st_Fun_File.ReadRecoder(CN_st_DownFile_BufFd.CN_st_DownFile_UseFd[fd].PropertyFd,0,&CN_st_DownFile_Infor))!=De_Suc_File)
		return Result;
	CN_st_DownFile_Infor.TotalFileLen=FileLength;
	if((Result=CN_st_Fun_File.WriteRecoder(CN_st_DownFile_BufFd.CN_st_DownFile_UseFd[fd].PropertyFd,0,&CN_st_DownFile_Infor))!=De_Suc_File)
		return Result;
	return De_Suc_DownFile;	
}
static uint16 SetFileName1(uint16 fd,uint8 *FileName)
{	uint16 Result;
	st_DownFile_Infor CN_st_DownFile_Infor;
	if((Result=CN_st_Fun_File.ReadRecoder(CN_st_DownFile_BufFd.CN_st_DownFile_UseFd[fd].PropertyFd,0,&CN_st_DownFile_Infor))!=De_Suc_File)
		return Result;
	MoveByte(CN_st_DownFile_Infor.FileName,FileName,Strsize(FileName));
	CN_st_DownFile_Infor.FileName[Strsize(FileName)]=0;
	if((Result=CN_st_Fun_File.WriteRecoder(CN_st_DownFile_BufFd.CN_st_DownFile_UseFd[fd].PropertyFd,0,&CN_st_DownFile_Infor))!=De_Suc_File)
		return Result;
	return De_Suc_DownFile;	
}
static uint16 CleanProperty1(uint16 fd)
{	st_DownFile_Infor CN_st_DownFile_Infor;
	ClsArray((uint8 *)&CN_st_DownFile_Infor,sizeof(st_DownFile_Infor));
	CN_st_Fun_File.ReadHeadTail(CN_st_DownFile_BufFd.CN_st_DownFile_UseFd[fd].FileFd,&CN_st_DownFile_Infor.HeadRecoderNum,De_rwFile_Point_Tail);
	CN_st_DownFile_Infor.TailRecoderNum=CN_st_DownFile_Infor.HeadRecoderNum;
	CN_st_Fun_File.WriteRecoder(CN_st_DownFile_BufFd.CN_st_DownFile_UseFd[fd].PropertyFd,0,&CN_st_DownFile_Infor);
	return De_Suc_DownFile;	
}
static void MoveByte(uint8 *Fount,uint8 *Aim,uint16 SizeofBuf)
{	uint16 i;
	for(i=0;i<SizeofBuf;i++)
		Fount[i]=Aim[i];	
}

static uint16 Strsize(uint8 *Buf)
{	uint8 i;
	for(i=0;i<60000;i++)
	{	if(Buf[i]==0)
			break;
	}
	return i;
}

static void ClsArray(uint8 *Buf,uint16 SizeofBuf)
{	uint16 i;
	for(i=0;i<SizeofBuf;i++)
		Buf[i]=0;
}
