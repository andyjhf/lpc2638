#define De_FileData_Compiler
#include "FileData.h"
#define De_DeBug
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
{	uint16 i,Result,Cuit;
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
			Result=CN_st_Fun_File.Open(CN_Ba_st_File_fd_Tabel[i].CN_st_File_Property.FileName,CN_Ba_st_File_fd_Tabel[i].fd);
		}
		if(CN_Ba_st_File_fd_Tabel[i].CN_st_File_Property.Property==De_File_Property_Bin)
			continue;
		if(CN_Ba_st_File_fd_Tabel[i].BackFaData==NULL)
			continue;
		Cuit=CN_st_Fun_File.GetJlNum(*CN_Ba_st_File_fd_Tabel[i].fd);
		if((CN_Ba_st_File_fd_Tabel[i].CN_st_File_Property.Property==De_File_Property_Recoder)
		&&(Cuit==CN_Ba_st_File_fd_Tabel[i].CN_st_File_Property.RecoderNumber))
			continue;
		if((Cuit!=0)&&(CN_Ba_st_File_fd_Tabel[i].CN_st_File_Property.Property==De_File_Property_Cycle))
			continue;
		if(Result==0)										//如果这个文件没有记录，恢复记录
			BackFacFile((st_File_fd_Tabel	*)(CN_Ba_st_File_fd_Tabel+i));								
	}
	#ifdef De_DeBug
		//CN_st_Fun_File.WriteRecoder(CN_st_File_fd.Parameterfd,0,(void *)&CN_Ba_st_Parameter_Table);
	
	#endif		
}
static void BackFacFile(st_File_fd_Tabel	*ptst_File_fd_Tabel)
{	uint16 i;
	if(ptst_File_fd_Tabel->CN_st_File_Property.Property==De_File_Property_Cycle)
	{	CN_st_Fun_File.WriteRecoder(*ptst_File_fd_Tabel->fd,0,(void	*)ptst_File_fd_Tabel->BackFaData);
		return ;		
	}
	for(i=0;i<ptst_File_fd_Tabel->CN_st_File_Property.RecoderNumber;i++)
	{	if(CN_st_Fun_File.GetJlNum(*ptst_File_fd_Tabel->fd)>i)
			CN_st_Fun_File.WriteRecoder(*ptst_File_fd_Tabel->fd,i+1,(void	*)ptst_File_fd_Tabel->BackFaData);
		else
			CN_st_Fun_File.WriteRecoder(*ptst_File_fd_Tabel->fd,0,(void	*)ptst_File_fd_Tabel->BackFaData);			
	}
}


