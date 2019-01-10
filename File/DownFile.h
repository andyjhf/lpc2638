#ifndef DownFile_H
#define DownFile_H

/*=========================================include File===========================================================*/	
	#include "..\APP\config.h"
	#include "stdlib.h"
	#ifdef De_DownFile_Compiler
		#include "..\miscellaneous\CodeTrans\AscNumber.h"				// ��������ת����Դ
		#include "..\File\rwFile.h"										// �����ļ�ϵͳ
		#include "..\miscellaneous\Arithmetic\Arithmetic.h" 				// �����㷨
	#endif
/*===================================Define Data=======================================================*/
	#define OS_ADD
	/*++++++++++++++++++++++++++++++++++�������һ����++++++++++++++++++++++++++++++++++++++++*/
	#define De_Suc_DownFile							0
	#define De_Erro_DownFile  						1
	#define De_Erro_DownFile_TooMuch  				De_Erro_DownFile+1	//�ļ�̫��
	#define De_Erro_DownFile_NoFd					De_Erro_DownFile_TooMuch+1

	/*+++++++++++++++++++++++++++++++++++++�����־+++++++++++++++++++++++++++++++++++++++++++*/
	#define Max_DownFile_Open						10			 //���������ļ�������
	#define De_DownFile_Open						1
	#define De_DownFile_Close						0
	/*+++++++++++++++++++++++++++++++++++Out Function+++++++++++++++++++++++++++++++++++++++++*/
/*========================================Data Define=========================================================*/
	typedef struct
	{ 	uint32  TotalFileLen;    				// �ļ��ܳ���
		uint32  RevFileLen;      				// �Ѿ����ص��ļ�����
		uint8   UpFlag;          				// �ļ�������
		uint16  HeadRecoderNum;	 				//�ļ���ʼ��ַ
		uint16  TailRecoderNum;	 				//�ļ�������ַ
		uint8	FileName[200];
	}st_DownFile_Infor;		 					//�����ļ���Ϣ
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
		/*	�������ܣ����������ļ�
			��ڲ������������	FileName	�ļ�������
								FileLength	�ļ��Ĵ�С
								FilePropertyLen	�����ļ����Գ���   ��DataLength==0������ļ����Է�0�������
					  �������	Buf		������ʵ������
			����ֵ:	 0:�ɹ�			��0	<����������>		
		*/
		uint16 (*CreateFile)(uint8 *FileName,uint32 FileLength);
		/*	�������ܣ��������ļ�
			��ڲ������������	fd	�����ļ��ľ��
								StartAddree	�����ļ�����ʼλ��
								DataLength	���������Ĵ�С   ��DataLength==0������ļ����Է�0�������
					  �������	Buf		������ʵ������
			����ֵ:	 0:�ɹ�			��0	<����������>		
		*/
		uint16 (*ReadFile)(uint16 fd,void *Buf,uint32 StartAddree,uint16 DataLength);
		/*	�������ܣ�д�����ļ�
			��ڲ������������	fd	�����ļ��ľ��
								DataLength	���������Ĵ�С   ��DataLength==0���޸ĸ��ļ����Է�0���������
					  �������	Buf		��д��ʵ������
			����ֵ:	 0:�ɹ�			��0	<����������>		
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
