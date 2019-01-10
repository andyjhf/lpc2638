/*
//��FTP��Ϊһ���ؼ�����.ƽ��FTP���ڵȴ�״̬���ȴ�Ӧ�ó����һ������,�������ݼ�<st_FTP_Data>��ʾ,�����յ������
//�������ݱ����ڱ��ػ��棬Ȼ��ִ������.������ִ����ɺ�,�ٴ�ͨ������һ�����䷢�ͱ�������ʧ�ܻ����ǳɹ�������ɹ�
//����Ҫ���ݴ洢�ļ�������.��<st_FTP_ReData>;
//
*/

#define FTP_H
#ifdef  FTP_H

/*=========================================include File===========================================================*/	
	#include "..\..\APP\config.h"
	#include "stdlib.h"
	#ifdef De_FTP_Compiler

		#include "..\..\miscellaneous\CodeTrans\AscNumber.h"				// ��������ת����Դ
		#include "..\..\Control\Gprs\GPRS.h"								// ����GPRS�ؼ�
		#include "..\..\HardWare\UART\UART.h" 								// ���ô���
		#include "..\..\File\DownFile.h"										// �����ļ�ϵͳ
		#include "..\..\File\rwFile.h"
		#include "..\..\miscellaneous\Arithmetic\Arithmetic.h" 				// �����㷨
	#endif

/*=========================================��������б�========================================================*/
#define De_Erro_FTP_Start                    0xa0	//��ֵ��PUBLICͳһ����
#define De_Suc_FTP							 0
#define De_Erro_FTP_Init					 De_Erro_FTP_Start+1		     // FTP��ʼ������
#define De_Erro_FTP_InitTCPLink				 De_Erro_FTP_Init+1				 //	TCP��·��ʼ������
#define De_Erro_FTP_OpenCtrLink 			 De_Erro_FTP_InitTCPLink+1		 // ������·�򿪴���
#define De_Erro_FTP_OpenDatLink           	 De_Erro_FTP_OpenCtrLink+1		 // ������·�򿪴���
#define De_Erro_FTP_SendCommand				 De_Erro_FTP_OpenDatLink+1 		 // ����FTP�������
#define De_Erro_FTP_AskErro					 De_Erro_FTP_SendCommand+1		 // ������Ӧ����󣨲�����Ҫ��Ӧ��
#define De_Erro_FTP_TimeOut					 De_Erro_FTP_AskErro+1           // ���ݽ��ճ�ʱ  
#define De_Erro_FTP_RevWrong				 De_Erro_FTP_TimeOut+1			 // ���ش��󣬳��Ȳ��Ե�

/*===========================�����궨��=====================*/

#define De_FTP_Operation_NoWork    0		// FTP����״̬
#define De_FTP_Operation_Work      1		// FTP�������� 
#define De_Max_FileSize            256000  //250K
#define De_Max_Messages  			5			//ͬʱ�����Խ��յ�����

#define De_FTP_StartCmd			1
#define De_FTP_CtrLink     		2
#define De_FTP_DataLink			3

#define De_FTP_Link_Close          0
#define De_FTP_Link_Open           1

#define De_FTP_Down_Nofinish       0
#define De_FTP_Down_Finish         1

/*++++++++++++++++++++++++++++++++����ϵͳ�й�++++++++++++++++++++++++++++++++++++++++*/
		#define De_FTP_Task							    7
		#define De_FTP_Stk								1024
		#define De_FTP_TaskDly							50				 // ��ʱ����ʱ��
		#define OUTTIME                                 20               // ��ʱʱ�� 20s	  
	

/*=======================================Data Define=========================================================*/			
		/*++++++++++++++++++++++++++++++���ݽṹ�嶨��++++++++++++++++++++++++++++++++++++++*/
	

	typedef struct
	{	
		uint8     type;				  // ��������
		uint32    CtrLinkIpAdd;       // ������·IP��ַ,4�ֽ�IP��ַ,�磺221.223.224.225 0xdd de df e0
	    uint16    CtrLinkPort;        // ������·�˿ں� 0~65535
	    uint8     LoginName[40];      // ��½�û���	 ASC��ʾ���㲹��
	    uint8     LoginPassword[40];  // ��½���� 		 ASC��ʾ���㲹��
	    uint8     FileDirName[200];   // �ļ����������ļ���·��	ASC��ʾ���㲹��
		uint8     SaveFileName[32];	  // ���汾���ļ����ļ��� 				 	
		uint16    Result;	  
		OS_EVENT  *LocalBox;
	}st_FTP_Data;     // FTP���ز���


	typedef struct
	{	uint32 FileLen;					// ��Ҫ���ص��ļ����ܳ���
		uint32 DownLoaderLen;			// ��ǰ�Ѿ����صĳ���
		st_FTP_Data	cn_FTP_Data;	    // ��ǰ���صĲ���
		uint8 State;					// De_FTP_Operation_Work ��������; De_FTP_Operation_NoWork   �������			
	}st_FTP_WorkState;

   	typedef struct
	{
		st_FTP_Data  cn_FTP_Data; 	  
	    uint32       DataLinkIpAdd;        // ������·IP��ַ
	    uint16       DataLinkPort;         // ������·�˿ں�     
//	    uint32       FileLength;           // �ļ�����
//	    uint32       DownFileLen;          // �Ѿ����ص��ļ�����
//		uint32       FileOffset;           // �ļ��洢ƫ��
		uint16       CRC;                  // CRCУ��ֵ
	    uint8        state;                // De_FTP_Operation_Work ��������; De_FTP_Operation_NoWork   �������	
	}st_FtpDown_Data;         //FTP���ز���


	typedef union
	{
		struct 
		{
			uint8 buf[200];
		}DataBuf; 	
		struct
		{
			uint8 askcode[3];
			uint8 askmsg[180];
		}RevAsk;

	}un_FTP_Cmd;	 //FTP����ṹ

	typedef struct
	{
		uint8   fd;              // ftp������·��id
		uint8   state;           // ״̬
	} st_Ftp_Link;

	typedef struct
	{		
		uint16  FtpDownFd;              // �����ļ���id
	//	uint16  FTP_Info_Fd;              // ������Ϣ��id
	}st_FTP_ID;		//ID


	typedef struct
	{
		uint8  FileDes;       // �洢Ŀ�ĵأ�1����ʾ�洢���ڲ�flash��2��ʾ�洢���ⲿflash
		uint8  FileName[32];  // �ļ���
		uint32 StartAddr;	  // ��ʼ��ַ�����ڴ洢���ⲿflash���ļ����ֶ���Ч
		uint32 MaxFileSize;   // �ļ���ռ�õĿռ�����С
		uint16 fd;
	}st_FileInfor;

	typedef struct
	{ 	uint8  FileName[32];  // �ļ���
		uint32  TotalFileLen;    // �ļ��ܳ���
		uint32  RevFileLen;      // �Ѿ����յ��ļ�����
		uint8   UpFlag;          // ������־,0,δ������1���Ѿ����ص��ⲿflash,2,�Ѿ���д���
		uint16  HeadRecoderNum;
		uint16  TailRecoderNum;
	}st_UpFileInfor;		 //�����ļ���Ϣ
	typedef struct
	{	uint8 Buf[512];
		uint16 DataLength;
	}st_Buf_rwFlash;



/*======================================�������======================================================*/
		typedef struct
		{	uint16 (*Init)(void);											//��ʼ���������ϵ���һ��
			uint16 (*GetState)(st_FTP_WorkState	*ptst_FTP_WorkState);		//��ȡ�������״̬	   			
		}st_Fun_FTP;


/*=========================================�ڲ�����===========================================================*/	
	#ifdef De_FTP_Compiler

	    //FTP���� 
		const uint8 *pUser_CMD = "USER";   // �����½�û���
		const uint8 *pPass_CMD = "PASS";   // �����¼����
		const uint8 *pPasv_CMD = "PASV";   // ���ñ���ģʽ
		const uint8 *pType_CMD = "TYPE";   // �����ļ�����
		const uint8 *pList_CMD = "LIST";   // �ļ��б�
		const uint8 *pRest_CMD = "REST";   // ������ʼ��ַ
		const uint8 *pRetr_CMD = "RETR";   // ��ʼ�����ļ�
		const uint8 *pQuit_CMD = "QUIT";   // �˳�������
		const uint8 *pCwd_CMD  = "CWD";    // �ı乤��Ŀ¼   

		un_FTP_Cmd FTP_Cmd;

		static uint16 Init(void);
		static uint16 InitTCPLink(void);
		static uint16 FtpLinkOpen(uint32 ipaddress,uint16 port,st_Affair_UDPTCP	*ptst_Affair_UDPTCP,uint8 *fd);
		static uint16 GetState(st_FTP_WorkState	*ptst_FTP_WorkState);
		static uint16 Close(void);
		static uint16 FTP_SendCommand(const uint8 *pCmdName, uint8 *pCmdPara,uint8 *pAsk);
		static void FTP_Downloard_Task(void *pData);  
		static void FTP_Test_Task(void *pData); 
		static void FTP_CtrReceive(uint8 *Data,uint8 fd,uint16 DataLength);
		static void FTP_DataReceive(uint8 *Data,uint8 fd,uint16 DataLength);
		static uint16 FTP_Open_File(void); 
		static uint16 FTP_Close_File(void); 
		

		void *MessegBox[De_Max_Messages]; 				//���ؼ���Ϣ����							
		OS_EVENT    	*FtpQbox;		  // ����FTP������ 
		OS_EVENT 		*FtpCtrlSem;	   // ������·����	 		
		st_FTP_Data 	*pFtpBox;

		static OS_STK FTP_Stk[De_FTP_Stk];
		
		st_FTP_ID  		 CN_FTP_ID;   //���õ���id
		st_FtpDown_Data  CN_FtpDown_Data;	// �ڲ�ʹ�õ�ȫ�ֱ���
			
		st_Ftp_Link      CN_st_Link_Ctrl;
		st_Ftp_Link      CN_st_Link_Data;	

		const  st_Fun_FTP CN_st_Fun_FTP = {Init,GetState};
		const  st_Affair_UDPTCP CtrLink_Affair_TCP  = {FTP_CtrReceive,NULL};	  
		const  st_Affair_UDPTCP DataLink_Affair_TCP = {FTP_DataReceive,NULL};

		st_UpFileInfor  CN_st_UpFileInfor;
		st_FTP_Data     FtpDown;
		uint16 TimeCount;
		uint8  DownloadFile[32]; 	
		uint8  DownloadDir[150];
		uint8  FtpDownFlag;
		st_Buf_rwFlash CN_st_Buf_rwFlash;

	#else
		 extern st_Fun_FTP  CN_st_Fun_FTP;	 	
		 extern st_UpFileInfor CN_st_UpFileInfor;	 
		 extern OS_EVENT    *FtpQbox;					// ����FTP������ 		
		 
	#endif

#endif
