#define _RWFILE_H
#ifdef	_RWFILE_H

/*===============================Include File==========================================================*/
  	#include "..\APP\config.h"
  	#include "stdlib.h"
	#include "..\Dev\Flash\FlashPu.h"
	#include "..\Dev\Flash\_Flash.h"
	#include "..\Dev\Flash\rwflashlgc.h"
	#include "..\Public_H\DePublic.h"
	
	#ifdef De_rwFile_Compiler
		#include "..\miscellaneous\Arithmetic\Arithmetic.h"
	#endif
/*===================================Define Data=======================================================*/
    #define OS_ADD																	//操作系统函数
	/*++++++++++++++++++++++++++++++++++错误代码一览表++++++++++++++++++++++++++++++++++++++++*/
	#define De_Suc_File							0
	#define De_Erro_File  						60
	#define De_Erro_File_NoSpace				De_Erro_File						//没有存储空间	
	#define De_Erro_File_FileAgin				De_Erro_File_NoSpace+1				//文件名重复
	#define De_Erro_File_RecoderSizeOut			De_Erro_File_FileAgin+1				//记录长度超出
	#define De_Erro_File_NoFileSpaceOpen		De_Erro_File_RecoderSizeOut+1		//没有空间打开文件
	#define De_Erro_File_NoFile					De_Erro_File_NoFileSpaceOpen+1		//没有这个文件
	#define De_Erro_File_NoOpen					De_Erro_File_NoFile+1				//文件未打开
	#define De_Erro_File_OutBinFile				De_Erro_File_NoOpen+1				//二进制文件超长
	#define De_Erro_File_NoBin					De_Erro_File_OutBinFile+1			//不是二进制文件
	#define De_Erro_File_NoRecoder				De_Erro_File_NoBin+1				//不是记录文件
	#define De_Erro_File_RecoderOut				De_Erro_File_NoRecoder+1			//超过所读的记录范围
	#define De_Erro_File_Recoder				De_Erro_File_RecoderOut+1			//ECC校验不能回传
	#define De_Erro_File_RecoderFull			De_Erro_File_Recoder+1				//记录已满
	#define De_Erro_File_Opened					De_Erro_File_RecoderFull+1			//此文件已打开
	#define De_Erro_File_Init					De_Erro_File_Opened+1				//初始化文件系统失败
	/*+++++++++++++++++++++++++++++++++++++文件属性+++++++++++++++++++++++++++++++++++++++++++*/
	#define De_File_Property_Bin							1					//二进制文件
	#define De_File_Property_Recoder						2					//记录文件
	#define De_File_Property_Cycle 							3					//循环记录文件
	#define De_File_Open									40					//文件可以打开的数量
	#define De_File_Number									80					//本文件系统支持的文件数量	

	/*+++++++++++++++++++++++++++++++++++++程序标志+++++++++++++++++++++++++++++++++++++++++++*/
	#define De_File_State_Use								1					//正在使用
	#define De_File_State_NoUse								0					//未使用
	#define De_File_NoChip									255					//代表器件全部找完	
	#define De_rwFile_Point_Head							1
	#define De_rwFile_Point_Tail							2
	#define De_Flash_Number									De_Flash_Chip_Number
/*========================================Data Define=========================================================*/	
	typedef struct 
	{	uint8 FileName[8]; 			//文件名称
		uint32 FileLen;				//文件大小
		uint8 FileNumber;			//文件号码
		uint8 Property;				//属性									  
		uint16 RecoderSize;			//一条记录大小
		uint16 RecoderNumber;		//记录数量
		uint32 StartAddree;			//开始地址
		uint32 EndAddree;			//结束地址		
	}st_Data_File;

	typedef struct 
	{	uint8 FileName[8]; 			//文件名称
		uint32 FileLen;				//文件大小
		uint8 FileNumber;			//文件号码
		uint8 Property;				//属性
		uint16 RecoderSize;			//一条记录大小
		uint16 RecoderNumber;		//记录数量
		uint32 StartAddree;			//开始地址
		uint32 EndAddree;			//结束地址
		uint16 HeadPoint;			//记录头指针
		uint16 EndPoint;			//记录尾指针
		uint8 Chip;					//当前芯片
		uint8 State;				//是否正在使用
	}st_Data_FileUse;

	typedef struct
	{	st_Data_FileUse	CN_st_Data_FileUse[De_File_Open];							//打开文件缓冲	

	}st_Data_FileBuf;					//最多可以打开10个文件，每个文件的基本信息
	/*+++++++++++++++++++++++++++++++++++Out Function+++++++++++++++++++++++++++++++++++++++++*/
	typedef struct
	{	
		/*	函数功能：初始化文件系统，上电后使用一次
			返回值：返回驱动库
		
		*/
		st_NorFlash	* (* Init)(void);
		/*	函数功能：创建二进制文件
			入口参数：输入参数	FileName	创建的文件名称
								FileLen		创建的文件大小
			返回值:	 0:成功			非0	<见错误代码表>		
		*/
		uint16 (*CreateBin)(uint8 *FileName,uint32 FileLen);						//创建一个文件
		
		/*	函数功能：创建记录文件
			入口参数：输入参数	FileName	创建的文件名称
								RecoderSize		一条记录的大小
								RecoderNumber	本文件记录的数量
								Property		记录属性   2：定长记录文件   3：循环记录文件
			返回值:	 0:成功			非0	<见错误代码表>		
		*/
		uint16 (*CreateRecoder)(uint8 *FileName,uint16 RecoderSize,uint16 RecoderNumber,uint8 Property); 					//建立记录文件
		/*	函数功能：打开一个文件
			入口参数：输入参数	FileName	打开文件的名称
					  输出参数	fd			成功打开后返回的文件句柄
			返回值:	 0:成功			非0	<见错误代码表>		
		*/
		uint16 (*Open)(uint8 *FileName,uint16 *fd);
		/*	函数功能：关闭一个文件
			入口参数：输入参数	fd	所关闭的文件句柄
			返回值:	 0:成功			非0	<见错误代码表>		
		*/
		uint16 (*Close)(uint16 fd);
		/*	函数功能：读二进制文件
			入口参数：输入参数	fd	所读文件的句柄
								Addree	所读文件的起始位置
								SizeofBuf	本次所读的大小
					  输出参数	Buf		所读的实际数据
			返回值:	 0:成功			非0	<见错误代码表>		
		*/
		uint16 (*ReadBin)(uint16 fd,uint32 Addree,uint16 SizeofBuf,void *Buf);
		/*	函数功能：写二进制文件
			入口参数：输入参数	fd	所写文件的句柄
								Addree	所写文件的起始位置
								SizeofBuf	本次所写的大小
					  			Buf		所写的实际数据
			返回值:	 0:成功			非0	<见错误代码表>		
		*/
		uint16 (*WriteBin)(uint16 fd,uint32 Addree,uint16 SizeofBuf,void *Buf);
		/*	函数功能：读记录文件的一条记录
			入口参数：输入参数	fd	所读文件的句柄
								Number	所读记录的记录号，记录号从1开始，当Number==0代表是读的最后一条记录
					  输出参数	Buf		所读的实际数据
			返回值:	 0:成功			非0	<见错误代码表>		
		*/
		uint16 (*ReadRecoder)(uint16 fd,uint16 Number,void *Buf);	 //读记录文件，当为0的时候表示读的最后一条记录
		/*	函数功能：写记录文件的一条记录
			入口参数：输入参数	fd	所读文件的句柄
								Number	所写记录的记录号，记录号从1开始，当Number==0代表是添加记录
					  			Buf		所写的实际数据
			返回值:	 0:成功			非0	<见错误代码表>		
		*/
		uint16 (*WriteRecoder)(uint16 fd,uint16 Number,void *Buf); //写记录文件，当为0的时候表示是追加记录
		/*	函数功能：获取记录文件的记录数量
			入口参数: 	fd	所获取的文件的句柄
			返回值:	 0:成功			非0	<见错误代码表>
		*/
		uint16 (*GetJlNum)(uint16 fd);
	
		uint16 (*Seek)(uint16 fd,uint16 StartRecoder,uint16 SizeofBuf,void *Buf);
		uint16 (*SeekSize)(uint16 fd,uint16 StartRecoder,uint16 SizeofBuf,uint8 *SmallBuf,uint8 *BigBuf,uint8 Flag,uint16 *Recoder,uint16 SizeofRecoder);
		uint16 (*ReadHeadTail)(uint16 fd,uint16 *Value,uint8 HeadOrTail);
		uint16 (*ReadPor)(uint16 fd,st_Data_FileUse	*ptst_Data_FileUse); 
		uint16 (*GetPointNum)(uint16 fd,uint16 Head);
	}st_Fun_File;


/*=========================================数据地址定义=================================================*/
	#define De_File_Addree_FileBasic			256	   				//文件基本信息
	//文件基本信息备份
	#define De_File_Addree_FileBasicBack		De_File_Addree_FileBasic+De_File_Number*sizeof(st_Data_File);
	#define De_File_Addree_FileHeadTail			64*1024				//记录文件头尾指针	
	#define De_File_Addree_FileHeadTailBack		De_File_Addree_FileHeadTail+32*1024	 //记录文件头尾指针备份
	#define De_File_Addree_FileInforStart		De_File_Addree_FileHeadTailBack+32*1024	//文件内容开始地址
/*==============================Static Function========================================================*/
	#ifdef De_rwFile_Compiler	
		static st_NorFlash	* Init1(void);
		static uint16 CreateBin1(uint8 *FileName1,uint32 FileLen);						//创建一个文件
		static uint16 CreateRecoder1(uint8 *FileName1,uint16 RecoderSize,uint16 RecoderNumber,uint8 Property); 					//建立记录文件
		static uint16 Open1(uint8 *FileName1,uint16 *fd);
		static uint16 Close1(uint16 fd);
		static uint16 ReadBin1(uint16 fd,uint32 Addree,uint16 SizeofBuf,void *Buf);
		static uint16 WriteBin1(uint16 fd,uint32 Addree,uint16 SizeofBuf,void *Buf);
		static uint16 ReadRecoder2(uint16 fd,uint16 Number,void *Buf);	 //读记录文件，当为0的时候表示读的最后一条记录
		static uint16 WriteRecoder2(uint16 fd,uint16 Number,void *Buf); //写记录文件，当为0的时候表示是追加记录
		static uint16 GetJlNum1(uint16 fd);
		static uint16 Seek1(uint16 fd,uint16 StartRecoder,uint16 SizeofBuf,void *Buf);
		static uint16 SeekSize1(uint16 fd,uint16 StartRecoder,uint16 SizeofBuf,uint8 *SmallBuf,uint8 *BigBuf,uint8 Flag,uint16 *Recoder,uint16 SizeofRecoder);
		static uint16 ReadHeadTail(uint16 fd,uint16 *Value,uint8 HeadOrTail);		
		static uint16 ReadPor(uint16 fd,st_Data_FileUse	*ptst_Data_FileUse);

		static st_NorFlash	* Init(void);
		static uint16 CreateBin(st_NorFlash	*ptst_NorFlash,uint8 *FileName1,uint32 FileLen);						//创建一个文件
		static uint16 CreateRecoder(st_NorFlash	*ptst_NorFlash,uint8 *FileName1,uint16 RecoderSize,uint16 RecoderNumber,uint8 Property); 					//建立记录文件
		static uint16 Open(st_NorFlash	*ptst_NorFlash,uint8 *FileName1,uint16 *fd);
		static uint16 Close(uint16 fd);
		static uint16 ReadBin(uint16 fd,uint32 Addree,uint16 SizeofBuf,void *Buf);
		static uint16 WriteBin(uint16 fd,uint32 Addree,uint16 SizeofBuf,void *Buf);
		static uint16 ReadRecoder1(uint16 fd,st_NorFlash	*ptst_NorFlash,uint16 Number,void *Buf);	 //读记录文件，当为0的时候表示读的最后一条记录
		static uint16 WriteRecoder1(uint16 fd,st_NorFlash	*ptst_NorFlash,uint16 Number,void *Buf); //写记录文件，当为0的时候表示是追加记录
		static uint16 GetJlNum(uint16 fd);
		static uint16 Seek(uint16 fd,uint16 StartRecoder,uint16 SizeofBuf,void *Buf);
		static uint16 SeekSize(uint16 fd,uint16 StartRecoder,uint16 SizeofBuf,uint8 *SmallBuf,uint8 *BigBuf,uint8 Flag,uint16 *Recoder,uint16 SizeofRecoder);
		static uint16 GetPointNum(uint16 fd,uint16 Head);
		static uint16 UpdateHeadTailPoint(uint16 fd,st_NorFlash	*ptst_NorFlash);
		static uint16 fWriteHeadTail(uint16 fd,st_NorFlash	*ptst_NorFlash,uint16 Head,uint16 Tail);	//实际更新头尾指针
		static uint16 GetFileInfor(uint16 fd,uint8 Chip,st_Data_File	*ptst_Data_File);  										//获取文件基本信息
		static uint16 GetHeadTailPoint(uint8 Chip,uint8 FileNumber,uint8 fd);												//读头尾指针
		static uint16 LookHeadTailFF(uint8 Chip,uint8 FileNumber,uint16 *Erro);					//查找FF的位置
		static uint16 LookFileBufSpace(void);  					//查找符合位置的存储文件
		static uint16 LookFileNameAgain(uint8 *FileName);
		static uint16 LookSpace(st_NorFlash	*ptst_NorFlash,uint8 *FileName,st_Data_File	*ptst_Data_File,uint8 Chip,uint8 *FileNumber);	//查找文件信息存放的位置
		static uint8 LookChip(st_NorFlash	*ptst_NorFlash,uint8 Chip);
		static uint16 ReadRecode(uint8 Chip,uint32 Addree,uint32 AddreeBack,uint16 SizeofBuf,void *Buf); 			//当全部是FF的时候，那么校验也是FFFF
		static uint16 WriteRecode(uint8 Chip,uint32 Addree,uint32 AddreeBack,uint16 SizeofBuf,void *Buf);
		static uint16 CompareBuf(uint8 *Buf1,uint8 *Buf2,uint32 SizeofBuf);
		static void MoveByte(uint8 *Fount,uint8 *Aim,uint16 SizeofBuf);
		static uint16 Crc(uint8 *s,uint16 len); 
		static void ClsArray(uint8 *Buf,uint16 SizeofBuf);
/*==============================Public Ram============================================================*/
		st_Data_FileBuf CN_st_Data_FileBuf;
		st_Data_FileBuf	*ptst_Data_FileBuf=(st_Data_FileBuf	*)&CN_st_Data_FileBuf;		//目前可以打开10个文件
		static uint8 *X_BUF=(uint8 *)(De_File_Ram);		
		#ifdef OS_ADD
			static OS_EVENT *FileSem=NULL;
		#endif
	    const st_Fun_File	CN_st_Fun_File={Init1,CreateBin1,CreateRecoder1,Open1,Close1,ReadBin1,WriteBin1,ReadRecoder2,WriteRecoder2,GetJlNum1,Seek1,SeekSize1,ReadHeadTail,ReadPor,GetPointNum};
	#else 
		extern const st_Fun_File	CN_st_Fun_File;
	#endif
	
#endif

