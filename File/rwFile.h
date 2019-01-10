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
    #define OS_ADD																	//����ϵͳ����
	/*++++++++++++++++++++++++++++++++++�������һ����++++++++++++++++++++++++++++++++++++++++*/
	#define De_Suc_File							0
	#define De_Erro_File  						60
	#define De_Erro_File_NoSpace				De_Erro_File						//û�д洢�ռ�	
	#define De_Erro_File_FileAgin				De_Erro_File_NoSpace+1				//�ļ����ظ�
	#define De_Erro_File_RecoderSizeOut			De_Erro_File_FileAgin+1				//��¼���ȳ���
	#define De_Erro_File_NoFileSpaceOpen		De_Erro_File_RecoderSizeOut+1		//û�пռ���ļ�
	#define De_Erro_File_NoFile					De_Erro_File_NoFileSpaceOpen+1		//û������ļ�
	#define De_Erro_File_NoOpen					De_Erro_File_NoFile+1				//�ļ�δ��
	#define De_Erro_File_OutBinFile				De_Erro_File_NoOpen+1				//�������ļ�����
	#define De_Erro_File_NoBin					De_Erro_File_OutBinFile+1			//���Ƕ������ļ�
	#define De_Erro_File_NoRecoder				De_Erro_File_NoBin+1				//���Ǽ�¼�ļ�
	#define De_Erro_File_RecoderOut				De_Erro_File_NoRecoder+1			//���������ļ�¼��Χ
	#define De_Erro_File_Recoder				De_Erro_File_RecoderOut+1			//ECCУ�鲻�ܻش�
	#define De_Erro_File_RecoderFull			De_Erro_File_Recoder+1				//��¼����
	#define De_Erro_File_Opened					De_Erro_File_RecoderFull+1			//���ļ��Ѵ�
	#define De_Erro_File_Init					De_Erro_File_Opened+1				//��ʼ���ļ�ϵͳʧ��
	/*+++++++++++++++++++++++++++++++++++++�ļ�����+++++++++++++++++++++++++++++++++++++++++++*/
	#define De_File_Property_Bin							1					//�������ļ�
	#define De_File_Property_Recoder						2					//��¼�ļ�
	#define De_File_Property_Cycle 							3					//ѭ����¼�ļ�
	#define De_File_Open									40					//�ļ����Դ򿪵�����
	#define De_File_Number									80					//���ļ�ϵͳ֧�ֵ��ļ�����	

	/*+++++++++++++++++++++++++++++++++++++�����־+++++++++++++++++++++++++++++++++++++++++++*/
	#define De_File_State_Use								1					//����ʹ��
	#define De_File_State_NoUse								0					//δʹ��
	#define De_File_NoChip									255					//��������ȫ������	
	#define De_rwFile_Point_Head							1
	#define De_rwFile_Point_Tail							2
	#define De_Flash_Number									De_Flash_Chip_Number
/*========================================Data Define=========================================================*/	
	typedef struct 
	{	uint8 FileName[8]; 			//�ļ�����
		uint32 FileLen;				//�ļ���С
		uint8 FileNumber;			//�ļ�����
		uint8 Property;				//����									  
		uint16 RecoderSize;			//һ����¼��С
		uint16 RecoderNumber;		//��¼����
		uint32 StartAddree;			//��ʼ��ַ
		uint32 EndAddree;			//������ַ		
	}st_Data_File;

	typedef struct 
	{	uint8 FileName[8]; 			//�ļ�����
		uint32 FileLen;				//�ļ���С
		uint8 FileNumber;			//�ļ�����
		uint8 Property;				//����
		uint16 RecoderSize;			//һ����¼��С
		uint16 RecoderNumber;		//��¼����
		uint32 StartAddree;			//��ʼ��ַ
		uint32 EndAddree;			//������ַ
		uint16 HeadPoint;			//��¼ͷָ��
		uint16 EndPoint;			//��¼βָ��
		uint8 Chip;					//��ǰоƬ
		uint8 State;				//�Ƿ�����ʹ��
	}st_Data_FileUse;

	typedef struct
	{	st_Data_FileUse	CN_st_Data_FileUse[De_File_Open];							//���ļ�����	

	}st_Data_FileBuf;					//�����Դ�10���ļ���ÿ���ļ��Ļ�����Ϣ
	/*+++++++++++++++++++++++++++++++++++Out Function+++++++++++++++++++++++++++++++++++++++++*/
	typedef struct
	{	
		/*	�������ܣ���ʼ���ļ�ϵͳ���ϵ��ʹ��һ��
			����ֵ������������
		
		*/
		st_NorFlash	* (* Init)(void);
		/*	�������ܣ������������ļ�
			��ڲ������������	FileName	�������ļ�����
								FileLen		�������ļ���С
			����ֵ:	 0:�ɹ�			��0	<����������>		
		*/
		uint16 (*CreateBin)(uint8 *FileName,uint32 FileLen);						//����һ���ļ�
		
		/*	�������ܣ�������¼�ļ�
			��ڲ������������	FileName	�������ļ�����
								RecoderSize		һ����¼�Ĵ�С
								RecoderNumber	���ļ���¼������
								Property		��¼����   2��������¼�ļ�   3��ѭ����¼�ļ�
			����ֵ:	 0:�ɹ�			��0	<����������>		
		*/
		uint16 (*CreateRecoder)(uint8 *FileName,uint16 RecoderSize,uint16 RecoderNumber,uint8 Property); 					//������¼�ļ�
		/*	�������ܣ���һ���ļ�
			��ڲ������������	FileName	���ļ�������
					  �������	fd			�ɹ��򿪺󷵻ص��ļ����
			����ֵ:	 0:�ɹ�			��0	<����������>		
		*/
		uint16 (*Open)(uint8 *FileName,uint16 *fd);
		/*	�������ܣ��ر�һ���ļ�
			��ڲ������������	fd	���رյ��ļ����
			����ֵ:	 0:�ɹ�			��0	<����������>		
		*/
		uint16 (*Close)(uint16 fd);
		/*	�������ܣ����������ļ�
			��ڲ������������	fd	�����ļ��ľ��
								Addree	�����ļ�����ʼλ��
								SizeofBuf	���������Ĵ�С
					  �������	Buf		������ʵ������
			����ֵ:	 0:�ɹ�			��0	<����������>		
		*/
		uint16 (*ReadBin)(uint16 fd,uint32 Addree,uint16 SizeofBuf,void *Buf);
		/*	�������ܣ�д�������ļ�
			��ڲ������������	fd	��д�ļ��ľ��
								Addree	��д�ļ�����ʼλ��
								SizeofBuf	������д�Ĵ�С
					  			Buf		��д��ʵ������
			����ֵ:	 0:�ɹ�			��0	<����������>		
		*/
		uint16 (*WriteBin)(uint16 fd,uint32 Addree,uint16 SizeofBuf,void *Buf);
		/*	�������ܣ�����¼�ļ���һ����¼
			��ڲ������������	fd	�����ļ��ľ��
								Number	������¼�ļ�¼�ţ���¼�Ŵ�1��ʼ����Number==0�����Ƕ������һ����¼
					  �������	Buf		������ʵ������
			����ֵ:	 0:�ɹ�			��0	<����������>		
		*/
		uint16 (*ReadRecoder)(uint16 fd,uint16 Number,void *Buf);	 //����¼�ļ�����Ϊ0��ʱ���ʾ�������һ����¼
		/*	�������ܣ�д��¼�ļ���һ����¼
			��ڲ������������	fd	�����ļ��ľ��
								Number	��д��¼�ļ�¼�ţ���¼�Ŵ�1��ʼ����Number==0��������Ӽ�¼
					  			Buf		��д��ʵ������
			����ֵ:	 0:�ɹ�			��0	<����������>		
		*/
		uint16 (*WriteRecoder)(uint16 fd,uint16 Number,void *Buf); //д��¼�ļ�����Ϊ0��ʱ���ʾ��׷�Ӽ�¼
		/*	�������ܣ���ȡ��¼�ļ��ļ�¼����
			��ڲ���: 	fd	����ȡ���ļ��ľ��
			����ֵ:	 0:�ɹ�			��0	<����������>
		*/
		uint16 (*GetJlNum)(uint16 fd);
	
		uint16 (*Seek)(uint16 fd,uint16 StartRecoder,uint16 SizeofBuf,void *Buf);
		uint16 (*SeekSize)(uint16 fd,uint16 StartRecoder,uint16 SizeofBuf,uint8 *SmallBuf,uint8 *BigBuf,uint8 Flag,uint16 *Recoder,uint16 SizeofRecoder);
		uint16 (*ReadHeadTail)(uint16 fd,uint16 *Value,uint8 HeadOrTail);
		uint16 (*ReadPor)(uint16 fd,st_Data_FileUse	*ptst_Data_FileUse); 
		uint16 (*GetPointNum)(uint16 fd,uint16 Head);
	}st_Fun_File;


/*=========================================���ݵ�ַ����=================================================*/
	#define De_File_Addree_FileBasic			256	   				//�ļ�������Ϣ
	//�ļ�������Ϣ����
	#define De_File_Addree_FileBasicBack		De_File_Addree_FileBasic+De_File_Number*sizeof(st_Data_File);
	#define De_File_Addree_FileHeadTail			64*1024				//��¼�ļ�ͷβָ��	
	#define De_File_Addree_FileHeadTailBack		De_File_Addree_FileHeadTail+32*1024	 //��¼�ļ�ͷβָ�뱸��
	#define De_File_Addree_FileInforStart		De_File_Addree_FileHeadTailBack+32*1024	//�ļ����ݿ�ʼ��ַ
/*==============================Static Function========================================================*/
	#ifdef De_rwFile_Compiler	
		static st_NorFlash	* Init1(void);
		static uint16 CreateBin1(uint8 *FileName1,uint32 FileLen);						//����һ���ļ�
		static uint16 CreateRecoder1(uint8 *FileName1,uint16 RecoderSize,uint16 RecoderNumber,uint8 Property); 					//������¼�ļ�
		static uint16 Open1(uint8 *FileName1,uint16 *fd);
		static uint16 Close1(uint16 fd);
		static uint16 ReadBin1(uint16 fd,uint32 Addree,uint16 SizeofBuf,void *Buf);
		static uint16 WriteBin1(uint16 fd,uint32 Addree,uint16 SizeofBuf,void *Buf);
		static uint16 ReadRecoder2(uint16 fd,uint16 Number,void *Buf);	 //����¼�ļ�����Ϊ0��ʱ���ʾ�������һ����¼
		static uint16 WriteRecoder2(uint16 fd,uint16 Number,void *Buf); //д��¼�ļ�����Ϊ0��ʱ���ʾ��׷�Ӽ�¼
		static uint16 GetJlNum1(uint16 fd);
		static uint16 Seek1(uint16 fd,uint16 StartRecoder,uint16 SizeofBuf,void *Buf);
		static uint16 SeekSize1(uint16 fd,uint16 StartRecoder,uint16 SizeofBuf,uint8 *SmallBuf,uint8 *BigBuf,uint8 Flag,uint16 *Recoder,uint16 SizeofRecoder);
		static uint16 ReadHeadTail(uint16 fd,uint16 *Value,uint8 HeadOrTail);		
		static uint16 ReadPor(uint16 fd,st_Data_FileUse	*ptst_Data_FileUse);

		static st_NorFlash	* Init(void);
		static uint16 CreateBin(st_NorFlash	*ptst_NorFlash,uint8 *FileName1,uint32 FileLen);						//����һ���ļ�
		static uint16 CreateRecoder(st_NorFlash	*ptst_NorFlash,uint8 *FileName1,uint16 RecoderSize,uint16 RecoderNumber,uint8 Property); 					//������¼�ļ�
		static uint16 Open(st_NorFlash	*ptst_NorFlash,uint8 *FileName1,uint16 *fd);
		static uint16 Close(uint16 fd);
		static uint16 ReadBin(uint16 fd,uint32 Addree,uint16 SizeofBuf,void *Buf);
		static uint16 WriteBin(uint16 fd,uint32 Addree,uint16 SizeofBuf,void *Buf);
		static uint16 ReadRecoder1(uint16 fd,st_NorFlash	*ptst_NorFlash,uint16 Number,void *Buf);	 //����¼�ļ�����Ϊ0��ʱ���ʾ�������һ����¼
		static uint16 WriteRecoder1(uint16 fd,st_NorFlash	*ptst_NorFlash,uint16 Number,void *Buf); //д��¼�ļ�����Ϊ0��ʱ���ʾ��׷�Ӽ�¼
		static uint16 GetJlNum(uint16 fd);
		static uint16 Seek(uint16 fd,uint16 StartRecoder,uint16 SizeofBuf,void *Buf);
		static uint16 SeekSize(uint16 fd,uint16 StartRecoder,uint16 SizeofBuf,uint8 *SmallBuf,uint8 *BigBuf,uint8 Flag,uint16 *Recoder,uint16 SizeofRecoder);
		static uint16 GetPointNum(uint16 fd,uint16 Head);
		static uint16 UpdateHeadTailPoint(uint16 fd,st_NorFlash	*ptst_NorFlash);
		static uint16 fWriteHeadTail(uint16 fd,st_NorFlash	*ptst_NorFlash,uint16 Head,uint16 Tail);	//ʵ�ʸ���ͷβָ��
		static uint16 GetFileInfor(uint16 fd,uint8 Chip,st_Data_File	*ptst_Data_File);  										//��ȡ�ļ�������Ϣ
		static uint16 GetHeadTailPoint(uint8 Chip,uint8 FileNumber,uint8 fd);												//��ͷβָ��
		static uint16 LookHeadTailFF(uint8 Chip,uint8 FileNumber,uint16 *Erro);					//����FF��λ��
		static uint16 LookFileBufSpace(void);  					//���ҷ���λ�õĴ洢�ļ�
		static uint16 LookFileNameAgain(uint8 *FileName);
		static uint16 LookSpace(st_NorFlash	*ptst_NorFlash,uint8 *FileName,st_Data_File	*ptst_Data_File,uint8 Chip,uint8 *FileNumber);	//�����ļ���Ϣ��ŵ�λ��
		static uint8 LookChip(st_NorFlash	*ptst_NorFlash,uint8 Chip);
		static uint16 ReadRecode(uint8 Chip,uint32 Addree,uint32 AddreeBack,uint16 SizeofBuf,void *Buf); 			//��ȫ����FF��ʱ����ôУ��Ҳ��FFFF
		static uint16 WriteRecode(uint8 Chip,uint32 Addree,uint32 AddreeBack,uint16 SizeofBuf,void *Buf);
		static uint16 CompareBuf(uint8 *Buf1,uint8 *Buf2,uint32 SizeofBuf);
		static void MoveByte(uint8 *Fount,uint8 *Aim,uint16 SizeofBuf);
		static uint16 Crc(uint8 *s,uint16 len); 
		static void ClsArray(uint8 *Buf,uint16 SizeofBuf);
/*==============================Public Ram============================================================*/
		st_Data_FileBuf CN_st_Data_FileBuf;
		st_Data_FileBuf	*ptst_Data_FileBuf=(st_Data_FileBuf	*)&CN_st_Data_FileBuf;		//Ŀǰ���Դ�10���ļ�
		static uint8 *X_BUF=(uint8 *)(De_File_Ram);		
		#ifdef OS_ADD
			static OS_EVENT *FileSem=NULL;
		#endif
	    const st_Fun_File	CN_st_Fun_File={Init1,CreateBin1,CreateRecoder1,Open1,Close1,ReadBin1,WriteBin1,ReadRecoder2,WriteRecoder2,GetJlNum1,Seek1,SeekSize1,ReadHeadTail,ReadPor,GetPointNum};
	#else 
		extern const st_Fun_File	CN_st_Fun_File;
	#endif
	
#endif

