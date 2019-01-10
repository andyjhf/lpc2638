#define De_FileData_Compiler
#include "FileData.h"
void FileData_BackSet(void)											//恢复出厂值
{	uint16 i,Cuit;
	Cuit=sizeof(CN_Ba_st_File_fd_Tabel)/sizeof(st_File_fd_Tabel);
	for(i=0;i<Cuit;i++)
	{	if(CN_Ba_st_File_fd_Tabel[i].SelectFac==De_File_BackFac_No)
			continue;
		if(CN_Ba_st_File_fd_Tabel[i].BackFaData==NULL)
			continue;
		BackFacFile((st_File_fd_Tabel	*)(CN_Ba_st_File_fd_Tabel+i));	
	}
}

void FileData_CheckFile(void)									  //检查文件系统
{	uint16 i,Result;
	uint16 FileSumNumber;
	FileSumNumber=sizeof(CN_Ba_st_File_fd_Tabel)/sizeof(st_File_fd_Tabel);			//获取文件的数量
	for(i=0;i<FileSumNumber;i++)
	{	Result=CN_st_Fun_File.Open(CN_Ba_st_File_fd_Tabel[i].CN_st_File_Property.FileName,CN_Ba_st_File_fd_Tabel[i].fd);
		if((Result!=De_Erro_File_NoFile)&&(Result!=De_Suc_File))
			continue;
		if(Result==De_Erro_File_NoFile)							//没有这个文件
		{	if(CN_Ba_st_File_fd_Tabel[i].CN_st_File_Property.Property==De_File_Property_Bin)
				CN_st_Fun_File.CreateBin(CN_Ba_st_File_fd_Tabel[i].CN_st_File_Property.FileName,CN_Ba_st_File_fd_Tabel[i].CN_st_File_Property.FileSize);	
			else 
				CN_st_Fun_File.CreateRecoder(CN_Ba_st_File_fd_Tabel[i].CN_st_File_Property.FileName,CN_Ba_st_File_fd_Tabel[i].CN_st_File_Property.RecoderSize,
				CN_Ba_st_File_fd_Tabel[i].CN_st_File_Property.RecoderNumber,CN_Ba_st_File_fd_Tabel[i].CN_st_File_Property.Property);	
			CN_st_Fun_File.Open(CN_Ba_st_File_fd_Tabel[i].CN_st_File_Property.FileName,CN_Ba_st_File_fd_Tabel[i].fd);
		}
		if(CN_Ba_st_File_fd_Tabel[i].CN_st_File_Property.Property==De_File_Property_Bin)
			continue;
		if(CN_Ba_st_File_fd_Tabel[i].BackFaData==NULL)
			continue;
		if(CN_st_Fun_File.GetJlNum(*CN_Ba_st_File_fd_Tabel[i].fd)!=0)
			continue;
		if(Result==0)										//如果这个文件没有记录，恢复记录
			BackFacFile((st_File_fd_Tabel	*)(CN_Ba_st_File_fd_Tabel+i));								
	}		
}

static void BackFacFile(st_File_fd_Tabel	*ptst_File_fd_Tabel)
{	uint16 i;
	if(ptst_File_fd_Tabel->CN_st_File_Property.Property==De_File_Property_Cycle)
	{	CN_st_Fun_File.WriteRecoder(*ptst_File_fd_Tabel->fd,0,(void	*)ptst_File_fd_Tabel->BackFaData);
		return ;		
	}
	for(i=0;i<ptst_File_fd_Tabel->CN_st_File_Property.RecoderNumber;i++)
		CN_st_Fun_File.WriteRecoder(*ptst_File_fd_Tabel->fd,i+1,(void	*)ptst_File_fd_Tabel->BackFaData);	
}
