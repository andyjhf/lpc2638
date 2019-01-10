#define De_rwFile_Compiler

#include "rwFile.h"

/*	�������ܣ���ʼ���ļ�ϵͳ���ϵ��ʹ��һ��
		����ֵ������������
	
	*/
static 	st_NorFlash		*Init1(void)
{	st_NorFlash	*ptst_NorFlash;	
	ptst_NorFlash=Init();
	#ifdef OS_ADD
	if(FileSem==NULL)
		FileSem=OSSemCreate(1); 					
	#endif
	return ptst_NorFlash;
}
/*	�������ܣ������������ļ�
		��ڲ������������	FileName	�������ļ�����
							FileLen		�������ļ���С
		����ֵ:	 0:�ɹ�			��0	<����������>		
	*/																
static uint16 CreateBin1(uint8 *FileName1,uint32 FileLen)
{	uint8 err;
	uint16 Result;
	#ifdef OS_ADD
	OSSemPend(FileSem, 0, &err);				
	#endif
	Result=CreateBin(&CN_st_NorFlash,FileName1,FileLen);

	#ifdef OS_ADD
	OSSemPost(FileSem);
	#endif
	return Result;
}
/*	�������ܣ�������¼�ļ�
		��ڲ������������	FileName	�������ļ�����
							RecoderSize		һ����¼�Ĵ�С
							RecoderNumber	���ļ���¼������
							Property		��¼����   2��������¼�ļ�   3��ѭ����¼�ļ�
		����ֵ:	 0:�ɹ�			��0	<����������>		
	*/
static uint16 CreateRecoder1(uint8 *FileName1,uint16 RecoderSize,uint16 RecoderNumber,uint8 Property)
{	uint8 err;
	uint16 Result;
	#ifdef OS_ADD
	OSSemPend(FileSem, 0, &err);				
	#endif
	Result=CreateRecoder(&CN_st_NorFlash,FileName1,RecoderSize,RecoderNumber,Property);

	#ifdef OS_ADD
	OSSemPost(FileSem);
	#endif
	return Result;
}
/*	�������ܣ���һ���ļ�
		��ڲ������������	FileName	���ļ�������
				  �������	fd			�ɹ��򿪺󷵻ص��ļ����
		����ֵ:	 0:�ɹ�			��0	<����������>		
	*/
static uint16 Open1(uint8 *FileName1,uint16 *fd)
{	uint8 err;
	uint16 Result;
	#ifdef OS_ADD
	OSSemPend(FileSem, 0, &err);				
	#endif
	Result=Open(&CN_st_NorFlash,FileName1,fd);

	#ifdef OS_ADD
	OSSemPost(FileSem);
	#endif
	return Result;
}
/*	�������ܣ��ر�һ���ļ�
		��ڲ������������	fd	���رյ��ļ����
		����ֵ:	 0:�ɹ�			��0	<����������>		
	*/
static uint16 Close1(uint16 fd)
{	uint8 err;
	uint16 Result;
	#ifdef OS_ADD
	OSSemPend(FileSem, 0, &err);				
	#endif
	Result=Close(fd);

	#ifdef OS_ADD
	OSSemPost(FileSem);
	#endif
	return Result;
}

/*	�������ܣ����������ļ�
		��ڲ������������	fd	�����ļ��ľ��
							Addree	�����ļ�����ʼλ��
							SizeofBuf	���������Ĵ�С
				  �������	Buf		������ʵ������
		����ֵ:	 0:�ɹ�			��0	<����������>		
	*/
static uint16 ReadBin1(uint16 fd,uint32 Addree,uint16 SizeofBuf,void *Buf)
{	uint8 err;
	uint16 Result;
	#ifdef OS_ADD
	OSSemPend(FileSem, 0, &err);				
	#endif
	Result=ReadBin(fd,Addree,SizeofBuf,Buf);

	#ifdef OS_ADD
	OSSemPost(FileSem);
	#endif
	return Result;
}
	/*	�������ܣ�д�������ļ�
		��ڲ������������	fd	��д�ļ��ľ��
							Addree	��д�ļ�����ʼλ��
							SizeofBuf	������д�Ĵ�С
				  			Buf		��д��ʵ������
		����ֵ:	 0:�ɹ�			��0	<����������>		
	*/
static uint16 WriteBin1(uint16 fd,uint32 Addree,uint16 SizeofBuf,void *Buf)
{	uint8 err;
	uint16 Result;
	#ifdef OS_ADD
	OSSemPend(FileSem, 0, &err);				
	#endif
	Result=WriteBin(fd,Addree,SizeofBuf,Buf);

	#ifdef OS_ADD
	OSSemPost(FileSem);
	#endif
	return Result;
}
/*	�������ܣ�����¼�ļ���һ����¼
		��ڲ������������	fd	�����ļ��ľ��
							Number	������¼�ļ�¼�ţ���¼�Ŵ�1��ʼ����Number==0�����Ƕ������һ����¼
				  �������	Buf		������ʵ������
		����ֵ:	 0:�ɹ�			��0	<����������>		
	*/
static uint16 ReadRecoder2(uint16 fd,uint16 Number,void *Buf)
{	uint8 err;
	uint16 Result;
	#ifdef OS_ADD
	OSSemPend(FileSem, 0, &err);				
	#endif
	Result=ReadRecoder1(fd,&CN_st_NorFlash,Number,Buf);

	#ifdef OS_ADD
	OSSemPost(FileSem);
	#endif
	return Result;
}
 	/*	�������ܣ�д��¼�ļ���һ����¼
		��ڲ������������	fd	�����ļ��ľ��
							Number	��д��¼�ļ�¼�ţ���¼�Ŵ�1��ʼ����Number==0��������Ӽ�¼
				  			Buf		��д��ʵ������
		����ֵ:	 0:�ɹ�			��0	<����������>		
	*/
static uint16 WriteRecoder2(uint16 fd,uint16 Number,void *Buf)
{	uint8 err;
	uint16 Result;
	#ifdef OS_ADD
	OSSemPend(FileSem, 0, &err);				
	#endif
	Result=WriteRecoder1(fd,&CN_st_NorFlash,Number,Buf);

	#ifdef OS_ADD
	OSSemPost(FileSem);
	#endif
	return Result;
}
	/*	�������ܣ���ȡ��¼�ļ��ļ�¼����
		��ڲ���: 	fd	����ȡ���ļ��ľ��
		����ֵ:	 0:�ɹ�			��0	<����������>
	*/
static uint16 GetJlNum1(uint16 fd)
{	uint8 err;
	uint16 Result;
	#ifdef OS_ADD
	OSSemPend(FileSem, 0, &err);				
	#endif
	Result=GetJlNum(fd);

	#ifdef OS_ADD
	OSSemPost(FileSem);
	#endif
	return Result;
}

static uint16 Seek1(uint16 fd,uint16 StartRecoder,uint16 SizeofBuf,void *Buf)
{	uint8 err;
	uint16 Result;
	#ifdef OS_ADD
	OSSemPend(FileSem, 0, &err);			
	#endif
	Result=Seek(fd,StartRecoder,SizeofBuf,Buf);

	#ifdef OS_ADD
	OSSemPost(FileSem);
	#endif
	return Result;
}

static uint16 SeekSize1(uint16 fd,uint16 StartRecoder,uint16 SizeofBuf,uint8 *SmallBuf,uint8 *BigBuf,uint8 Flag,uint16 *Recoder,uint16 SizeofRecoder)
{	uint8 err;
	uint16 Result;
	#ifdef OS_ADD
	OSSemPend(FileSem, 0, &err);				
	#endif
	Result=SeekSize(fd,StartRecoder,SizeofBuf,SmallBuf,BigBuf,Flag,Recoder,SizeofRecoder);

	#ifdef OS_ADD
	OSSemPost(FileSem);
	#endif
	return Result;
}

static uint16 ReadHeadTail(uint16 fd,uint16 *Value,uint8 HeadOrTail)
{	uint8 err;
	#ifdef OS_ADD
	OSSemPend(FileSem, 0, &err);				
	#endif
	if(HeadOrTail==De_rwFile_Point_Head)
		*Value=ptst_Data_FileBuf->CN_st_Data_FileUse[fd].HeadPoint;
	else 
		*Value=ptst_Data_FileBuf->CN_st_Data_FileUse[fd].EndPoint;	
   	#ifdef OS_ADD
	OSSemPost(FileSem);
	#endif
	return De_Suc_File;
}

static uint16 ReadPor(uint16 fd,st_Data_FileUse	*ptst_Data_FileUse)
{	uint8 err;
	#ifdef OS_ADD
	OSSemPend(FileSem, 0, &err);				
	#endif
	MoveByte((uint8 *)ptst_Data_FileUse,(uint8 *)&ptst_Data_FileBuf->CN_st_Data_FileUse[fd],sizeof(st_Data_FileUse));
	#ifdef OS_ADD
	OSSemPost(FileSem);
	#endif
	return De_Suc_File;
}



/*=======================================================������֧�ֺ���====================================================================================*/











static st_NorFlash	* Init(void)	//��ʼ���ļ�ϵͳ
{	ClsArray((uint8 *)ptst_Data_FileBuf,sizeof(st_Data_FileBuf));
	return CN_st_Fun_NorFlash.Open();  	
}









static uint16 CreateBin(st_NorFlash	*ptst_NorFlash,uint8 *FileName1,uint32 FileLen)						//����һ���ļ�
 {	st_Data_File	CN_st_Data_File;
 	uint32 Addree,AddreeBack;
	uint16 Erro;
 	uint8 Chip,FileNumber,FileName[8];
	if((Erro=strlen((const char *)FileName1))>8)
		Erro=8;
	ClsArray(FileName,sizeof(FileName));
	MoveByte(FileName,FileName1,Erro);
	for(Chip=0;Chip<De_Flash_Number;Chip++)
	{ 	Chip=LookChip(ptst_NorFlash,Chip);
		if(Chip==De_File_NoChip)
			return 	De_Erro_File_NoSpace;
		Erro=LookSpace(ptst_NorFlash,FileName,&CN_st_Data_File,Chip,&FileNumber);
		if(Erro==De_Erro_File_NoSpace)
			continue;
		if(Erro!=De_Suc_File)					
			return Erro;
		Addree=ptst_NorFlash->CN_st_Flash_Chip_Features[Chip]->BlockSize*ptst_NorFlash->CN_st_Flash_Chip_Features[Chip]->BlockNumberUse;
		if((CN_st_Data_File.EndAddree+FileLen)>Addree) 	//�ļ����ܿ�оƬ
			continue;
		Addree=CN_st_Data_File.EndAddree;
		memset(&CN_st_Data_File,0,sizeof(st_Data_File));
		MoveByte(CN_st_Data_File.FileName,FileName,8);
		CN_st_Data_File.FileLen=FileLen;
		CN_st_Data_File.Property=De_File_Property_Bin;
		CN_st_Data_File.StartAddree=Addree;
	   	Addree+=FileLen;
		Erro=Addree%ptst_NorFlash->CN_st_Flash_Chip_Features[Chip]->BlockSize;
		Addree=(Addree/ptst_NorFlash->CN_st_Flash_Chip_Features[Chip]->BlockSize)*ptst_NorFlash->CN_st_Flash_Chip_Features[Chip]->BlockSize;
		if(Erro!=0)
			Addree+=ptst_NorFlash->CN_st_Flash_Chip_Features[Chip]->BlockSize;	
		CN_st_Data_File.EndAddree=Addree;
		Addree=De_File_Addree_FileBasic+FileNumber*(sizeof(st_Data_File)+2);
		AddreeBack=(uint32 )FileNumber*(sizeof(st_Data_File)+2)+(uint32 )De_File_Addree_FileBasicBack;
		return WriteRecode(Chip,Addree,AddreeBack,sizeof(st_Data_File),&CN_st_Data_File);
	}
	return De_Erro_File;																	
 }
static uint16 CreateRecoder(st_NorFlash	*ptst_NorFlash,uint8 *FileName1,uint16 RecoderSize,uint16 RecoderNumber,uint8 Property) 					//������¼�ļ�
{	st_Data_File	CN_st_Data_File;
 	uint32 Addree,FileLen;
	uint16 Erro;
 	uint8 Chip,Offset,FileNumber,FileName[8];
	uint16 BlockPerNumber;
	uint16 BlockNumber;
	if(RecoderSize>512)			//��¼���Ȳ��ܴ���512
		return De_Erro_File_RecoderSizeOut;
	Offset=3;
	if(RecoderSize>256)					//��¼�����������
		Offset=6;
	if((Erro=strlen((const char *)FileName1))>8)
		Erro=8;
	ClsArray(FileName,sizeof(FileName));
	MoveByte(FileName,FileName1,Erro);
	for(Chip=0;Chip<De_Flash_Number;Chip++)
	{	Chip=LookChip(ptst_NorFlash,Chip);
		if(Chip==De_File_NoChip)
			return 	De_Erro_File_NoSpace;
		Erro=LookSpace(ptst_NorFlash,FileName,&CN_st_Data_File,Chip,&FileNumber);
		if(Erro==De_Erro_File_NoSpace)
			continue;
		if(Erro!=De_Suc_File)					
			return Erro;
		BlockPerNumber=ptst_NorFlash->CN_st_Flash_Chip_Features[Chip]->BlockSize/(RecoderSize+Offset);
		BlockNumber=RecoderNumber/BlockPerNumber;
		if(RecoderNumber%BlockPerNumber)
			BlockNumber++;
		if(Property==De_File_Property_Cycle)	//ѭ����¼�ļ���֤ѭ������
			BlockNumber++;
		FileLen=BlockNumber*ptst_NorFlash->CN_st_Flash_Chip_Features[Chip]->BlockSize;
		if((FileLen+CN_st_Data_File.EndAddree)>(ptst_NorFlash->CN_st_Flash_Chip_Features[Chip]->BlockSize*
		ptst_NorFlash->CN_st_Flash_Chip_Features[Chip]->BlockNumberUse))
			continue;
		Addree=CN_st_Data_File.EndAddree;
		memset(&CN_st_Data_File,0,sizeof(st_Data_File));
		MoveByte(CN_st_Data_File.FileName,FileName,8);
		CN_st_Data_File.StartAddree=Addree;
		CN_st_Data_File.EndAddree=Addree+FileLen;
		CN_st_Data_File.RecoderSize=RecoderSize;
		CN_st_Data_File.FileNumber=FileNumber;
		CN_st_Data_File.Property=Property;
		CN_st_Data_File.RecoderNumber=BlockNumber*BlockPerNumber;
		Addree=De_File_Addree_FileBasic+FileNumber*(sizeof(st_Data_File)+2);
		FileLen=FileNumber*(sizeof(st_Data_File)+2)+De_File_Addree_FileBasicBack;
		return WriteRecode(Chip,Addree,FileLen,sizeof(st_Data_File),&CN_st_Data_File);
	}
	return De_Erro_File;	
}

static uint16 Open(st_NorFlash	*ptst_NorFlash,uint8 *FileName1,uint16 *fd)		//��һ���ļ�,�����ļ������ƴ��ݽ���,���ļ����������ó���10���ļ�������һ�����ID
{	st_Data_File	CN_st_Data_File;
	uint16 Erro;
	uint8 Chip,FileNumber,FileName[8];
	if((*fd=LookFileBufSpace())==0xffff)					//�Ƿ�������ļ�				
		return De_Erro_File_NoFileSpaceOpen;
	if((Erro=strlen((const char *)FileName1))>8)
		Erro=8;
	ClsArray(FileName,sizeof(FileName));
	MoveByte(FileName,FileName1,Erro);
	if((Erro=LookFileNameAgain(FileName))!=De_Suc_File)
		return Erro;
	for(Chip=0;Chip<De_Flash_Number;Chip++)
	{	Chip=LookChip(ptst_NorFlash,Chip);
		if(Chip==De_File_NoChip)
		{	Chip=De_Flash_Number;
			break;
		}
		Erro=LookSpace(ptst_NorFlash,FileName,&CN_st_Data_File,Chip,&FileNumber);
		if(Erro==De_Erro_File_FileAgin)			//������ļ�
			break;
	 	if((Erro!=De_Suc_File)&&(Erro!=De_Erro_File_NoSpace))
			return Erro;
	}
	if(Chip==De_Flash_Number)
		return De_Erro_File_NoFile;
	return GetFileInfor(*fd,Chip,&CN_st_Data_File);
}


static uint16 Close(uint16 fd)	//�ر�һ���ļ�����ʹ���ļ����ڴ��ͷŵ�												
{	ptst_Data_FileBuf->CN_st_Data_FileUse[fd].State=De_File_State_NoUse;
	
	
	return De_Suc_File;	
}					


static uint16 ReadBin(uint16 fd,uint32 Addree,uint16 SizeofBuf,void *Buf)	  //���������ļ�
{	if(ptst_Data_FileBuf->CN_st_Data_FileUse[fd].State==De_File_State_NoUse)			//�ļ�δ��
		return 	De_Erro_File_NoOpen;
	if(ptst_Data_FileBuf->CN_st_Data_FileUse[fd].Property!=De_File_Property_Bin)
		return De_Erro_File_NoBin;	
	if((Addree+SizeofBuf)>(ptst_Data_FileBuf->CN_st_Data_FileUse[fd].EndAddree-ptst_Data_FileBuf->CN_st_Data_FileUse[fd].StartAddree))//�жϵ�ַ�Ƿ���ȷ
		return De_Erro_File_OutBinFile;
	return CN_st_Fun_NorFlash.Read(ptst_Data_FileBuf->CN_st_Data_FileUse[fd].Chip,ptst_Data_FileBuf->CN_st_Data_FileUse[fd].StartAddree+Addree
			,SizeofBuf,Buf);
}

static uint16 WriteBin(uint16 fd,uint32 Addree,uint16 SizeofBuf,void *Buf)
{	if(ptst_Data_FileBuf->CN_st_Data_FileUse[fd].State==De_File_State_NoUse)			//�ļ�δ��
		return 	De_Erro_File_NoOpen;
	if(ptst_Data_FileBuf->CN_st_Data_FileUse[fd].Property!=De_File_Property_Bin) 		//�ж��Ƿ�������ļ�
		return De_Erro_File_NoBin;
	if((Addree+SizeofBuf)>(ptst_Data_FileBuf->CN_st_Data_FileUse[fd].EndAddree-ptst_Data_FileBuf->CN_st_Data_FileUse[fd].StartAddree))//
		return De_Erro_File_OutBinFile;
	Addree=ptst_Data_FileBuf->CN_st_Data_FileUse[fd].StartAddree+Addree;
	return CN_st_Fun_NorFlash.Write(ptst_Data_FileBuf->CN_st_Data_FileUse[fd].Chip,Addree,SizeofBuf,Buf);
}

static uint16 ReadRecoder1(uint16 fd,st_NorFlash	*ptst_NorFlash,uint16 Number,void *Buf)	 //����¼�ļ�����Ϊ0��ʱ���ʾ�������һ����¼
{	uint32 Addree,BlockNumber;
	uint8 ecc[3];
	uint16 RecoderNumber,Size,Erro;
	if(ptst_Data_FileBuf->CN_st_Data_FileUse[fd].State==De_File_State_NoUse)			//�ļ�δ��
		return 	De_Erro_File_NoOpen;
	if(ptst_Data_FileBuf->CN_st_Data_FileUse[fd].Property==De_File_Property_Bin) 		//�ж��Ƿ�������ļ�
		return De_Erro_File_NoRecoder;
	RecoderNumber=GetJlNum(fd);
	if(RecoderNumber==0)
		return De_Erro_File_RecoderOut;
	if(Number==0)
		Number=RecoderNumber;
	if(Number>RecoderNumber)
		return De_Erro_File_RecoderOut;
	Number=ptst_Data_FileBuf->CN_st_Data_FileUse[fd].HeadPoint+Number-2;
	if(Number>=ptst_Data_FileBuf->CN_st_Data_FileUse[fd].RecoderNumber)
		Number-=ptst_Data_FileBuf->CN_st_Data_FileUse[fd].RecoderNumber;
	Size=ptst_Data_FileBuf->CN_st_Data_FileUse[fd].RecoderSize;
	if(Size>256)  				//��¼�ļ�����ECCУ��
		Size+=6;
	else
		Size+=3;
	BlockNumber=ptst_NorFlash->CN_st_Flash_Chip_Features[ptst_Data_FileBuf->CN_st_Data_FileUse[fd].Chip]->BlockSize/Size;
	RecoderNumber=Number/BlockNumber;
	Number=Number%BlockNumber;
	Addree=RecoderNumber*ptst_NorFlash->CN_st_Flash_Chip_Features[ptst_Data_FileBuf->CN_st_Data_FileUse[fd].Chip]->BlockSize;
	Addree+=Number*Size;
	Addree+=ptst_Data_FileBuf->CN_st_Data_FileUse[fd].StartAddree;
	Erro=CN_st_Fun_NorFlash.Read(ptst_Data_FileBuf->CN_st_Data_FileUse[fd].Chip,Addree,Size,X_BUF);
	if(Erro!=De_Suc_File)  			//��ʧ��
		return Erro;
	if(ptst_Data_FileBuf->CN_st_Data_FileUse[fd].RecoderSize<=256)				//С��256���ֽڵ����
	{	MoveByte(X_BUF+256,X_BUF+ptst_Data_FileBuf->CN_st_Data_FileUse[fd].RecoderSize,3);
		ClsArray(X_BUF+ptst_Data_FileBuf->CN_st_Data_FileUse[fd].RecoderSize,256-ptst_Data_FileBuf->CN_st_Data_FileUse[fd].RecoderSize);
		CN_st_Fun_Arithmetic.ptst_Fun_Ecc->Calculate_ecc (X_BUF,ecc);
		if(CompareBuf(ecc,X_BUF+256,3)==0)				//У��ɹ�
		{	MoveByte(Buf,X_BUF,ptst_Data_FileBuf->CN_st_Data_FileUse[fd].RecoderSize);
			return De_Suc_File;
		}
		Erro=CN_st_Fun_Arithmetic.ptst_Fun_Ecc->Correct_data(X_BUF,X_BUF+256, ecc);
		if(Erro==0)
			return De_Erro_File_Recoder;
		ClsArray(X_BUF+ptst_Data_FileBuf->CN_st_Data_FileUse[fd].RecoderSize,256-ptst_Data_FileBuf->CN_st_Data_FileUse[fd].RecoderSize);
		CN_st_Fun_Arithmetic.ptst_Fun_Ecc->Calculate_ecc (X_BUF,ecc);
		MoveByte(X_BUF+ptst_Data_FileBuf->CN_st_Data_FileUse[fd].RecoderSize,ecc,3);
		Erro=CN_st_Fun_NorFlash.Write(ptst_Data_FileBuf->CN_st_Data_FileUse[fd].Chip,Addree,Size,X_BUF);
		if(Erro!=De_Suc_File)  			//��ʧ��
			return Erro;
		MoveByte(Buf,X_BUF,ptst_Data_FileBuf->CN_st_Data_FileUse[fd].RecoderSize);
		return De_Suc_File;
	}
	MoveByte(X_BUF+512,X_BUF+ptst_Data_FileBuf->CN_st_Data_FileUse[fd].RecoderSize,6);
	CN_st_Fun_Arithmetic.ptst_Fun_Ecc->Calculate_ecc(X_BUF,ecc);
	Erro=0;
	if(CompareBuf(ecc,X_BUF+512,3)!=0)				//У�鲻�ɹ�
	{	Erro=CN_st_Fun_Arithmetic.ptst_Fun_Ecc->Correct_data(X_BUF,X_BUF+512, ecc);
		if(Erro==0)						//������λ�޷��ָ�
			return De_Erro_File_Recoder;
		CN_st_Fun_Arithmetic.ptst_Fun_Ecc->Calculate_ecc(X_BUF,ecc);
		Erro=1;
		MoveByte(X_BUF+512,ecc,3);			
	}
	ClsArray(X_BUF+ptst_Data_FileBuf->CN_st_Data_FileUse[fd].RecoderSize,512-ptst_Data_FileBuf->CN_st_Data_FileUse[fd].RecoderSize);
	CN_st_Fun_Arithmetic.ptst_Fun_Ecc->Calculate_ecc (X_BUF+256,ecc);
	if(CompareBuf(ecc,X_BUF+515,3)!=0)			//У�鲻�ɹ�
	{	Erro=CN_st_Fun_Arithmetic.ptst_Fun_Ecc->Correct_data(X_BUF+256,X_BUF+515, ecc);	
		if(Erro==0)
			return De_Erro_File_Recoder;
		CN_st_Fun_Arithmetic.ptst_Fun_Ecc->Calculate_ecc(X_BUF+256,ecc);
		Erro=1;
		MoveByte(X_BUF+515,ecc,3);
	}
	if(Erro==1)					//��;�д�������
	{	MoveByte(X_BUF+ptst_Data_FileBuf->CN_st_Data_FileUse[fd].RecoderSize,X_BUF+512,6);
		Erro=CN_st_Fun_NorFlash.Write(ptst_Data_FileBuf->CN_st_Data_FileUse[fd].Chip,Addree,Size,X_BUF);
		if(Erro!=De_Suc_File)  			//��ʧ��
			return Erro;
	}
	MoveByte(Buf,X_BUF,ptst_Data_FileBuf->CN_st_Data_FileUse[fd].RecoderSize);
	return De_Suc_File;

}


static uint16 WriteRecoder1(uint16 fd,st_NorFlash	*ptst_NorFlash,uint16 Number,void *Buf) //д��¼�ļ�����Ϊ0��ʱ���ʾ��׷�Ӽ�¼
{	uint32 Addree,BlockNumber,OffsetNumber;
	uint8 ecc[3];
	uint16 RecoderNumber,Size,WriteNumber,Erro;
	if(ptst_Data_FileBuf->CN_st_Data_FileUse[fd].State==De_File_State_NoUse)			//�ļ�δ��
		return 	De_Erro_File_NoOpen;
	if(ptst_Data_FileBuf->CN_st_Data_FileUse[fd].Property==De_File_Property_Bin) 		//�ж��Ƿ�������ļ�
		return De_Erro_File_NoRecoder;	
	RecoderNumber=GetJlNum(fd);
	if(((RecoderNumber>=ptst_Data_FileBuf->CN_st_Data_FileUse[fd].RecoderNumber)&&(ptst_Data_FileBuf->CN_st_Data_FileUse[fd].Property==De_File_Property_Recoder))
		&&(Number==0))
		return 	De_Erro_File_RecoderFull;
	if(Number==0)					//��Ӽ�¼�����
		WriteNumber=ptst_Data_FileBuf->CN_st_Data_FileUse[fd].EndPoint-1;
	else 							//�޸ļ�¼
	{	WriteNumber=Number+ptst_Data_FileBuf->CN_st_Data_FileUse[fd].HeadPoint-2;
		if(WriteNumber>=ptst_Data_FileBuf->CN_st_Data_FileUse[fd].RecoderNumber)
			WriteNumber-=ptst_Data_FileBuf->CN_st_Data_FileUse[fd].RecoderNumber;
	}
	Size=ptst_Data_FileBuf->CN_st_Data_FileUse[fd].RecoderSize;
	if(Size>256)  				//��¼�ļ�����ECCУ��
		Size+=6;
	else
		Size+=3;
	BlockNumber=ptst_NorFlash->CN_st_Flash_Chip_Features[ptst_Data_FileBuf->CN_st_Data_FileUse[fd].Chip]->BlockSize/Size;
	RecoderNumber=WriteNumber/BlockNumber;
	OffsetNumber=WriteNumber%BlockNumber;
	Addree=RecoderNumber*ptst_NorFlash->CN_st_Flash_Chip_Features[ptst_Data_FileBuf->CN_st_Data_FileUse[fd].Chip]->BlockSize;
	Addree+=OffsetNumber*Size;
	Addree+=ptst_Data_FileBuf->CN_st_Data_FileUse[fd].StartAddree;
	if(ptst_Data_FileBuf->CN_st_Data_FileUse[fd].RecoderSize<=256)				//һ����¼С��256�����
	{	ClsArray(X_BUF,512);
		MoveByte(X_BUF,Buf,ptst_Data_FileBuf->CN_st_Data_FileUse[fd].RecoderSize);
		CN_st_Fun_Arithmetic.ptst_Fun_Ecc->Calculate_ecc(X_BUF,ecc);
		MoveByte(X_BUF+ptst_Data_FileBuf->CN_st_Data_FileUse[fd].RecoderSize,ecc,3);
		Erro=CN_st_Fun_NorFlash.Write(ptst_Data_FileBuf->CN_st_Data_FileUse[fd].Chip,Addree,Size,X_BUF);
		if(Erro!=De_Suc_File)
			return Erro;
	}
	else																		//����256�����
	{	ClsArray(X_BUF,512);
		MoveByte(X_BUF,Buf,ptst_Data_FileBuf->CN_st_Data_FileUse[fd].RecoderSize);
	   	CN_st_Fun_Arithmetic.ptst_Fun_Ecc->Calculate_ecc(X_BUF+256,ecc);
		MoveByte(X_BUF+ptst_Data_FileBuf->CN_st_Data_FileUse[fd].RecoderSize+3,ecc,3);
		CN_st_Fun_Arithmetic.ptst_Fun_Ecc->Calculate_ecc(X_BUF,ecc);
		MoveByte(X_BUF+ptst_Data_FileBuf->CN_st_Data_FileUse[fd].RecoderSize,ecc,3);
		Erro=CN_st_Fun_NorFlash.Write(ptst_Data_FileBuf->CN_st_Data_FileUse[fd].Chip,Addree,Size,X_BUF);
		if(Erro!=De_Suc_File)
			return Erro;
	}
	if(Number!=0)
		return De_Suc_File;
	Erro=UpdateHeadTailPoint(fd,ptst_NorFlash);
	if(Erro!=0)
		return Erro;
	if((((ptst_Data_FileBuf->CN_st_Data_FileUse[fd].EndPoint<ptst_Data_FileBuf->CN_st_Data_FileUse[fd].HeadPoint))&&
	((ptst_Data_FileBuf->CN_st_Data_FileUse[fd].EndPoint%BlockNumber)==1))) 					//��ѭ�� 
	{	OffsetNumber=ptst_Data_FileBuf->CN_st_Data_FileUse[fd].EndPoint/BlockNumber;
		Addree=ptst_Data_FileBuf->CN_st_Data_FileUse[fd].StartAddree+OffsetNumber*ptst_NorFlash->CN_st_Flash_Chip_Features[ptst_Data_FileBuf->CN_st_Data_FileUse[fd].Chip]->BlockSize;
		Erro=CN_st_Fun_NorFlash.Ease(ptst_Data_FileBuf->CN_st_Data_FileUse[fd].Chip,Addree);
		if(Erro!=De_Suc_File)
			return Erro;				
	}
	return De_Suc_File;
}

static uint16 GetJlNum(uint16 fd)							//��ȡ��¼��������
{	if(ptst_Data_FileBuf->CN_st_Data_FileUse[fd].EndPoint>=ptst_Data_FileBuf->CN_st_Data_FileUse[fd].HeadPoint)				//���������
		return 	ptst_Data_FileBuf->CN_st_Data_FileUse[fd].EndPoint-ptst_Data_FileBuf->CN_st_Data_FileUse[fd].HeadPoint;
	return ptst_Data_FileBuf->CN_st_Data_FileUse[fd].EndPoint+ptst_Data_FileBuf->CN_st_Data_FileUse[fd].RecoderNumber-
		ptst_Data_FileBuf->CN_st_Data_FileUse[fd].HeadPoint;		
}

static uint16 GetPointNum(uint16 fd,uint16 Head)
{	if(Head>=ptst_Data_FileBuf->CN_st_Data_FileUse[fd].HeadPoint)
		return Head-ptst_Data_FileBuf->CN_st_Data_FileUse[fd].HeadPoint+1; 
	return Head+ptst_Data_FileBuf->CN_st_Data_FileUse[fd].RecoderNumber+1-ptst_Data_FileBuf->CN_st_Data_FileUse[fd].HeadPoint;
}
static uint16 Seek(uint16 fd,uint16 StartRecoder,uint16 SizeofBuf,void *Buf) //����¼�ֶν��в���
{ 	return 0;




}

static uint16 SeekSize(uint16 fd,uint16 StartRecoder,uint16 SizeofBuf,uint8 *SmallBuf,uint8 *BigBuf,uint8 Flag,uint16 *Recoder,uint16 SizeofRecoder)			//��������ҷ��ϵļ�¼
{	return 0;




}











static uint16 UpdateHeadTailPoint(uint16 fd,st_NorFlash	*ptst_NorFlash)						//����ͷβ��ָ��
{	uint32 BlockNumber;
	uint16 Head,End,Size;
	Size=ptst_Data_FileBuf->CN_st_Data_FileUse[fd].RecoderSize;
	if(Size>256)  				//��¼�ļ�����ECCУ��
		Size+=6;
	else
		Size+=3;
	BlockNumber=ptst_NorFlash->CN_st_Flash_Chip_Features[ptst_Data_FileBuf->CN_st_Data_FileUse[fd].Chip]->BlockSize/Size;
	Head=ptst_Data_FileBuf->CN_st_Data_FileUse[fd].HeadPoint;
	End=ptst_Data_FileBuf->CN_st_Data_FileUse[fd].EndPoint;
	End++;
	if(End>ptst_Data_FileBuf->CN_st_Data_FileUse[fd].RecoderNumber)
	{	End=1;
	 	Head=End+BlockNumber;
	}
	else if((Head>=End)&&((End%BlockNumber)==1))
		Head+=BlockNumber;
	Size=fWriteHeadTail(fd,ptst_NorFlash,Head,End);
	if(Size!=De_Suc_File)
		return Size;
	ptst_Data_FileBuf->CN_st_Data_FileUse[fd].HeadPoint=Head;
	ptst_Data_FileBuf->CN_st_Data_FileUse[fd].EndPoint=End;
	return De_Suc_File;
}

static uint16 fWriteHeadTail(uint16 fd,st_NorFlash	*ptst_NorFlash,uint16 Head,uint16 Tail)	//ʵ�ʸ���ͷβָ��
{	uint16 Result,Erro;
	uint32 Addree;
	Result=LookHeadTailFF(ptst_Data_FileBuf->CN_st_Data_FileUse[fd].Chip,ptst_Data_FileBuf->CN_st_Data_FileUse[fd].FileNumber,&Erro);
	if(Erro!=0)
		return Erro;
	ClsArray(X_BUF,8);
	X_BUF[0]=(Head&0XFF); X_BUF[1]=(Head/256);
	X_BUF[2]=(Tail&0XFF); X_BUF[3]=(Tail/256);
	
	if(Result==256)
	{	memset(X_BUF+8,0XFF,248);
		Result=Crc(X_BUF,6);
		X_BUF[6]=(Result&0XFF);X_BUF[7]= Result/256;
		Addree=De_File_Addree_FileHeadTail+ptst_Data_FileBuf->CN_st_Data_FileUse[fd].FileNumber*256;
		Erro=CN_st_Fun_NorFlash.Write(ptst_Data_FileBuf->CN_st_Data_FileUse[fd].Chip,Addree,256,X_BUF);
		if(Erro!=De_Suc_File)
			return Erro;
		Addree=De_File_Addree_FileHeadTailBack+ptst_Data_FileBuf->CN_st_Data_FileUse[fd].FileNumber*256;
		Erro=CN_st_Fun_NorFlash.Write(ptst_Data_FileBuf->CN_st_Data_FileUse[fd].Chip,Addree,256,X_BUF);
		if(Erro!=De_Suc_File)
			return Erro;
		return De_Suc_File;
	}
	return WriteRecode(ptst_Data_FileBuf->CN_st_Data_FileUse[fd].Chip,
		De_File_Addree_FileHeadTail+ptst_Data_FileBuf->CN_st_Data_FileUse[fd].FileNumber*256+Result,
		De_File_Addree_FileHeadTailBack+ptst_Data_FileBuf->CN_st_Data_FileUse[fd].FileNumber*256+Result,6,X_BUF);
}















static uint16 GetFileInfor(uint16 fd,uint8 Chip,st_Data_File	*ptst_Data_File)  										//��ȡ�ļ�������Ϣ
{	MoveByte(ptst_Data_FileBuf->CN_st_Data_FileUse[fd].FileName,ptst_Data_File->FileName,8);
	ptst_Data_FileBuf->CN_st_Data_FileUse[fd].FileLen=ptst_Data_File->FileLen;
	ptst_Data_FileBuf->CN_st_Data_FileUse[fd].FileNumber=ptst_Data_File->FileNumber;
	ptst_Data_FileBuf->CN_st_Data_FileUse[fd].Property=ptst_Data_File->Property;
	ptst_Data_FileBuf->CN_st_Data_FileUse[fd].RecoderSize=ptst_Data_File->RecoderSize;	
	ptst_Data_FileBuf->CN_st_Data_FileUse[fd].RecoderNumber=ptst_Data_File->RecoderNumber;
	ptst_Data_FileBuf->CN_st_Data_FileUse[fd].StartAddree=ptst_Data_File->StartAddree;	
	ptst_Data_FileBuf->CN_st_Data_FileUse[fd].EndAddree=ptst_Data_File->EndAddree;	
	ptst_Data_FileBuf->CN_st_Data_FileUse[fd].Chip=Chip;
	ptst_Data_FileBuf->CN_st_Data_FileUse[fd].State=De_File_State_Use;
	return GetHeadTailPoint(Chip,ptst_Data_File->FileNumber,fd);

}


static uint16 GetHeadTailPoint(uint8 Chip,uint8 FileNumber,uint8 fd)												//��ͷβָ��
{	uint32 Addree,AddreeBack;
	uint16 i,Erro;
	i=LookHeadTailFF(Chip,FileNumber,&Erro);
	if(Erro!=De_Suc_File)
		return Erro;
	if(i!=0)
	{	Addree=De_File_Addree_FileHeadTail+FileNumber*256+i-8;
		AddreeBack=De_File_Addree_FileHeadTailBack+FileNumber*256+i-8;
		if((Erro=ReadRecode(Chip,Addree,AddreeBack,6,X_BUF))!=De_Suc_File)
			return Erro;
		ptst_Data_FileBuf->CN_st_Data_FileUse[fd].HeadPoint=X_BUF[0]+X_BUF[1]*256;
		ptst_Data_FileBuf->CN_st_Data_FileUse[fd].EndPoint=X_BUF[2]+X_BUF[3]*256;
	}
	else		 				//��¼�ļ���û����Ϣ
	{	ptst_Data_FileBuf->CN_st_Data_FileUse[fd].HeadPoint=ptst_Data_FileBuf->CN_st_Data_FileUse[fd].EndPoint=1;
	}
	return De_Suc_File;				

}


static uint16 LookHeadTailFF(uint8 Chip,uint8 FileNumber,uint16 *Erro)					//����FF��λ��
{	uint16 i;
	uint32 Addree;
	Addree=De_File_Addree_FileHeadTail+FileNumber*256;
	*Erro=CN_st_Fun_NorFlash.Read(Chip,Addree,256,X_BUF);
	if(*Erro!=De_Suc_File)
		return 0;
	for(i=0;i<256;i+=8)
	{	if((X_BUF[i]==0xff)&&(X_BUF[i+1]==0xff)&&(X_BUF[i+2]==0xff)&&(X_BUF[i+3]==0xff))
			break;
	}
	return i;				
}











static uint16 LookFileBufSpace(void)  					//���ҷ���λ�õĴ洢�ļ�
{	uint16 i;
	for(i=0;i<De_File_Open;i++)
	{	if(ptst_Data_FileBuf->CN_st_Data_FileUse[i].State==De_File_State_NoUse)
			return i;	
	}
	return 0xffff;
}
static uint16 LookFileNameAgain(uint8 *FileName)
{	uint8 FileName1[8];
	uint16 i,len;
	if((len=strlen((const char *)FileName))>8)
		len=8;
	ClsArray(FileName1,sizeof(FileName1));
	MoveByte(FileName1,FileName,len);
	for(i=0;i<De_File_Open;i++)				   
	{	if(ptst_Data_FileBuf->CN_st_Data_FileUse[i].State==De_File_State_NoUse)
			continue;
		if(CompareBuf(ptst_Data_FileBuf->CN_st_Data_FileUse[i].FileName,FileName1,8)==0)	
			return 	De_Erro_File_Opened;
	}
	return De_Suc_File;
}



static uint16 LookSpace(st_NorFlash	*ptst_NorFlash,uint8 *FileName,st_Data_File	*ptst_Data_File,uint8 Chip,uint8 *FileNumber)	//�����ļ���Ϣ��ŵ�λ��
 {	uint32 Addree,AddreeBack;
 	uint16 i,Erro;
 	for(i=0;i<De_File_Number;i++)
	{	Addree=De_File_Addree_FileBasic+i*(sizeof(st_Data_File)+2);
		AddreeBack=i*(sizeof(st_Data_File)+2)+De_File_Addree_FileBasicBack;
		Erro=ReadRecode(Chip,Addree,AddreeBack,sizeof(st_Data_File),ptst_Data_File); 	
		if(Erro!=De_Suc_File)
			return Erro;		
		if(ptst_Data_File->FileName[0]==0XFF)
			break;
		if(CompareBuf(FileName,ptst_Data_File->FileName,8)==0)
			return De_Erro_File_FileAgin;
	}
	if(i==De_File_Number)					//û��λ�ÿ��Դ�������
		return De_Erro_File_NoSpace;
	if(i==0)
		ptst_Data_File->EndAddree=De_File_Addree_FileInforStart;
	else
	{	i--;
		Addree=De_File_Addree_FileBasic+i*(sizeof(st_Data_File)+2);
		AddreeBack=i*(sizeof(st_Data_File)+2)+De_File_Addree_FileBasicBack;
		Erro=ReadRecode(Chip,Addree,AddreeBack,sizeof(st_Data_File),ptst_Data_File); 	
		if(Erro!=De_Suc_File)
			return Erro;
		i++;			
	}		
	*FileNumber=i;
	return De_Suc_File;
 }




static uint8 LookChip(st_NorFlash	*ptst_NorFlash,uint8 Chip)
{	uint8 i;
	for(i=Chip;i<De_Flash_Number;i++)
	{	if(ptst_NorFlash->CN_st_Flash_Chip_Features[i]!=NULL)	
		 	return i;	
	}
   	return De_File_NoChip;
}

static uint16 ReadRecode(uint8 Chip,uint32 Addree,uint32 AddreeBack,uint16 SizeofBuf,void *Buf) 			//��ȫ����FF��ʱ����ôУ��Ҳ��FFFF
 {	uint16 CrsV,Erro,CrsAV;
 	Erro=CN_st_Fun_NorFlash.Read(Chip,Addree,SizeofBuf,Buf);		
	if(Erro!=De_Suc_File)
		return Erro;
	Erro=CN_st_Fun_NorFlash.Read(Chip,Addree+SizeofBuf,2,(uint8 *)&CrsAV);
	if(Erro!=De_Suc_File)
		return Erro;
	CrsV=Crc(Buf,SizeofBuf);
	if(CrsAV==CrsV)
		return De_Suc_File;
	Erro=CN_st_Fun_NorFlash.Read(Chip,AddreeBack,SizeofBuf,Buf);		
	if(Erro!=De_Suc_File)
		return Erro;
	Erro=CN_st_Fun_NorFlash.Read(Chip,AddreeBack+SizeofBuf,2,(uint8 *)&CrsAV);
	if(Erro!=De_Suc_File)
		return Erro;
	CrsV=Crc(Buf,SizeofBuf);
	if(CrsV==CrsAV)	  				//��������ȷ��
	{	Erro=CN_st_Fun_NorFlash.Write(Chip,Addree,SizeofBuf,Buf);
		if(Erro!=De_Suc_File)
			return Erro;
		Erro=CN_st_Fun_NorFlash.Write(Chip,Addree+SizeofBuf,2,(uint8 *)&CrsAV);	
		if(Erro!=De_Suc_File)
			return Erro;
	}
	Erro=CN_st_Fun_NorFlash.Read(Chip,Addree,SizeofBuf,Buf);		
	if(Erro!=De_Suc_File)
		return Erro;
    return WriteRecode(Chip,Addree,AddreeBack,SizeofBuf,Buf);					//������ԭ���Ķ�����ȷ
 }

static uint16 WriteRecode(uint8 Chip,uint32 Addree,uint32 AddreeBack,uint16 SizeofBuf,void *Buf)
 {	uint16 CrsV,Erro;
 	CrsV=Crc(Buf,SizeofBuf);
	Erro=CN_st_Fun_NorFlash.Write(Chip,Addree,SizeofBuf,Buf);	
	if(Erro!=De_Suc_File)
		return Erro;
    Erro=CN_st_Fun_NorFlash.Write(Chip,Addree+SizeofBuf,2,(uint8 *)&CrsV);
	if(Erro!=De_Suc_File)
		return Erro;
	Erro=CN_st_Fun_NorFlash.Write(Chip,AddreeBack,SizeofBuf,Buf);	
	if(Erro!=De_Suc_File)
		return Erro;
    return CN_st_Fun_NorFlash.Write(Chip,AddreeBack+SizeofBuf,2,(uint8 *)&CrsV);
 }

static uint16 CompareBuf(uint8 *Buf1,uint8 *Buf2,uint32 SizeofBuf)					//�����������һ���������
{	uint32 i;
	for(i=0;i<SizeofBuf;i++)
	{	if(Buf1[i]!=Buf2[i])
			return 1;
	}
	return 0;
}

static void MoveByte(uint8 *Fount,uint8 *Aim,uint16 SizeofBuf)
{	uint16 i;
	for(i=0;i<SizeofBuf;i++)
		Fount[i]=Aim[i];	
}

static uint16 Crc(uint8 *s,uint16 len)                                               //16λ��CRCУ��       
{	uint16 i;   
	for(i=0;i<len;i++)
	{	if(s[i]!=0xff)
			break;
	}
	if(i==len)
		return 0xffff;
	return CN_st_Fun_Arithmetic.ptst_Fun_Crc->Crc(s,len,0);			                  
}

static void ClsArray(uint8 *Buf,uint16 SizeofBuf)
{	uint16 i;
	for(i=0;i<SizeofBuf;i++)
		Buf[i]=0;
}

