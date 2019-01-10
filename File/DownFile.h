#ifndef DownFile_H
#define DownFile_H

/*=========================================include File===========================================================*/	
	#include "..\APP\config.h"
	#include "stdlib.h"
	#ifdef De_DownFile_Compiler
		#include "..\miscellaneous\CodeTrans\AscNumber.h"				// 引用码制转换资源
		#include "..\File\rwFile.h"										// 引用文件系统
		#include "..\miscellaneous\Arithmetic\Arithmetic.h" 				// 引用算法
	#endif
/*===================================Define Data=======================================================*/
	#define OS_ADD
	/*++++++++++++++++++++++++++++++++++错误代码一览表++++++++++++++++++++++++++++++++++++++++*/
	#define De_Suc_DownFile							0
	#define De_Erro_DownFile  						1
	#define De_Erro_DownFile_TooMuch  				De_Erro_DownFile+1	//文件太大
	#define De_Erro_DownFile_NoFd					De_Erro_DownFile_TooMuch+1

	/*+++++++++++++++++++++++++++++++++++++程序标志+++++++++++++++++++++++++++++++++++++++++++*/
	#define Max_DownFile_Open						10			 //最多打开下载文件的数量
	#define De_DownFile_Open						1
	#define De_DownFile_Close						0
	/*+++++++++++++++++++++++++++++++++++Out Function+++++++++++++++++++++++++++++++++++++++++*/
/*========================================Data Define=========================================================*/
	typedef struct
	{ 	uint32  TotalFileLen;    				// 文件总长度
		uint32  RevFileLen;      				// 已经下载的文件长度
		uint8   UpFlag;          				// 文件完整性
		uint16  HeadRecoderNum;	 				//文件起始地址
		uint16  TailRecoderNum;	 				//文件结束地址
		uint8	FileName[200];
	}st_DownFile_Infor;		 					//下载文件信息
	typedef struct
	{	uint16 FileFd;									
	 	uint16 PropertyFd;
		uint8 State;
	}st_DownFile_UseFd;
	typedef struct
	{	st_DownFile_UseFd	CN_st_DownFile_UseFd[Max_DownFile_Open];
	}st_DownFile_BufFd;
	typedef struct
	{	uint16 (*Init)(void);
		uint16 (*Open)(uint8 *FileName,uint16 *fd);
		/*	函数功能：创建下载文件
			入口参数：输入参数	FileName	文件的名称
								FileLength	文件的大小
								FilePropertyLen	创建文件属性长度   当DataLength==0则读该文件属性非0则读内容
					  输出参数	Buf		所读的实际数据
			返回值:	 0:成功			非0	<见错误代码表>		
		*/
		uint16 (*CreateFile)(uint8 *FileName,uint32 FileLength);
		/*	函数功能：读下载文件
			入口参数：输入参数	fd	所读文件的句柄
								StartAddree	所读文件的起始位置
								DataLength	本次所读的大小   当DataLength==0则读该文件属性非0则读内容
					  输出参数	Buf		所读的实际数据
			返回值:	 0:成功			非0	<见错误代码表>		
		*/
		uint16 (*ReadFile)(uint16 fd,void *Buf,uint32 StartAddree,uint16 DataLength);
		/*	函数功能：写下载文件
			入口参数：输入参数	fd	所读文件的句柄
								DataLength	本次所读的大小   当DataLength==0则修改该文件属性非0则添加内容
					  输出参数	Buf		所写的实际数据
			返回值:	 0:成功			非0	<见错误代码表>		
		*/
		uint16 (*WriteFile)(uint16 fd,void *Buf,uint16 DataLength);
		uint16 (*Close)(uint16 fd);
		uint16 (*GetFileProperty)(uint16 fd,st_DownFile_Infor *ptst_DownFile_Infor);
		uint16 (*SetFileLength)(uint16 fd,uint32 FileLength);
		uint16 (*SetFileName)(uint16 fd,uint8 *FileName);
		uint16 (*CleanProperty)(uint16 fd);
	}st_Fun_DownFile;


/*==============================Static Function========================================================*/
	#ifdef	De_DownFile_Compiler
		static uint16 Init(void);
		static uint16 Open(uint8 *FileName,uint16 *fd);
		static uint16 CreateFile(uint8 *FileName,uint32 FileLength);
		static uint16 ReadFile(uint16 fd,void *Buf,uint32 StartAddree,uint16 DataLength);
		static uint16 WriteFile(uint16 fd,void *Buf,uint16 DataLength);
		static uint16 Close(uint16 fd);
		static uint16 GetFileProperty(uint16 fd,st_DownFile_Infor *ptst_DownFile_Infor);
		static uint16 SetFileLength(uint16 fd,uint32 FileLength);
		static uint16 SetFileName(uint16 fd,uint8 *FileName);
		static uint16 CleanProperty(uint16 fd);
		static uint16 Open1(uint8 *FileName,uint16 *fd);
		static uint16 CreateFile1(uint8 *FileName,uint32 FileLength);
		static uint16 ReadFile1(uint16 fd,void *Buf,uint32 StartAddree,uint16 DataLength);
		static uint16 WriteFile1(uint16 fd,void *Buf,uint16 DataLength);
		static uint16 Close1(uint16 fd);
		static uint16 GetFileProperty1(uint16 fd,st_DownFile_Infor *ptst_DownFile_Infor);
		static uint16 SetFileLength1(uint16 fd,uint32 FileLength);
		static uint16 SetFileName1(uint16 fd,uint8 *FileName);
		static uint16 CleanProperty1(uint16 fd);
		
		static void ClsArray(uint8 *Buf,uint16 SizeofBuf);
		static uint16 Strsize(uint8 *Buf);
		static void MoveByte(uint8 *Fount,uint8 *Aim,uint16 SizeofBuf);
	
	#endif
/*==============================Public Ram============================================================*/
	#ifdef	De_DownFile_Compiler
		OS_EVENT *DownFileSem=NULL;
		st_DownFile_BufFd CN_st_DownFile_BufFd;
		uint8 DownFile_BUF[512];
		const st_Fun_DownFile CN_st_Fun_DownFile={Init,Open,CreateFile,ReadFile,WriteFile,Close,GetFileProperty,SetFileLength,SetFileName,CleanProperty};
	#else
		extern const st_Fun_DownFile CN_st_Fun_DownFile; 
	#endif
#endif
