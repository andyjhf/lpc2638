#define FTP_H
#ifdef  FTP_H
/*=========================================include File===========================================================*/	
	#include "..\..\APP\config.h"
	#include "stdlib.h"
	#ifdef De_FTP_Compiler
		#include "..\..\miscellaneous\CodeTrans\AscNumber.h"				// ��������ת����Դ
		#include "..\Gprs\GPRS.h"								// ����GPRS�ؼ�
		#include "..\..\HardWare\UART\UART.h" 								// ���ô���
		#include "..\..\File\DownFile.h"										// �����ļ�ϵͳ
		#include "..\..\File\rwFile.h"
		#include "..\..\miscellaneous\Arithmetic\Arithmetic.h" 				// �����㷨
	#endif
/*==============================Define Data==================================================*/	
	/*+++++++++++++++++++++++++++++++�������һ����+++++++++++++++++++++++++++++++++++++++++*/
	#define De_Suc_FTP							 0
	#define De_Erro_FTP_Start                    1								 //��ֵ��PUBLICͳһ����
	#define De_Erro_FTP_Init					 De_Erro_FTP_Start+1		     // FTP��ʼ������
	#define De_Erro_FTP_InitTCPLink				 De_Erro_FTP_Init+1				 //	TCP��·��ʼ������
	#define De_Erro_FTP_OpenCtrLink 			 De_Erro_FTP_InitTCPLink+1		 // ������·�򿪴���
	#define De_Erro_FTP_OpenDatLink           	 De_Erro_FTP_OpenCtrLink+1		 // ������·�򿪴���
	#define De_Erro_FTP_SendCommand				 De_Erro_FTP_OpenDatLink+1 		 // ����FTP�������
	#define De_Erro_FTP_AskErro					 De_Erro_FTP_SendCommand+1		 // ������Ӧ����󣨲�����Ҫ��Ӧ��
	#define De_Erro_FTP_TimeOut					 De_Erro_FTP_AskErro+1           // ���ݽ��ճ�ʱ  
	#define De_Erro_FTP_RevWrong				 De_Erro_FTP_TimeOut+1			 // ���ش��󣬳��Ȳ��Ե�
	#define De_Erro_FTP_Finish					 De_Erro_FTP_RevWrong+1			 //�����������
	/*+++++++++++++++++++++++++++++++����״̬��+++++++++++++++++++++++++++++++++++++++++++*/
	#define De_FTP_Operation_Work						1		//��������
	#define	De_FTP_Operation_Idle						0		//����
	#define De_FTP_Link_Close							0
	#define De_FTP_Link_Open							1
	#define De_FTP_Down_Nofinish       					0
	#define De_FTP_Down_Finish         					1
	#define De_FTP_StartCmd								1
	#define De_FTP_CtrLink     							2
	#define De_FTP_DataLink								3
	#define De_Max_Messages								10		//�����Ϣ��
	#define De_Max_FileSize            					307200  //300K
	#define De_FileName_FTP								"FTP"
	/*++++++++++++++++++++++++++++++++����ϵͳ�й�++++++++++++++++++++++++++++++++++++++++*/
	#ifdef De_FTP_Compiler	
		#define De_Ftp_Task							    9//7//
		#define De_Ftp_Stk								356
	#endif
/*=======================================Data Define==========================================*/
	/*++++++++++++++++++++++++++++++++���ݽṹ����+++++++++++++++++++++++++++++++++++++++++++*/
	typedef struct
	{	uint32    CtrLinkIpAdd;       // ������·IP��ַ,4�ֽ�IP��ַ,�磺221.223.224.225 0xdd de df e0
	    uint16    CtrLinkPort;        // ������·�˿ں� 0~65535
	    uint8     LoginName[40];      // ��½�û���	 ASC��ʾ���㲹��
	    uint8     LoginPassword[40];  // ��½���� 		 ASC��ʾ���㲹��
	    uint8     FileDirName[200];   // �ļ����������ļ���·��	ASC��ʾ���㲹��
		uint8     SaveFileName[32];	  // ���汾���ļ����ļ���
		uint8     UpFlag;			  //�����ļ�������
	}st_FTP_Recoder;
	typedef struct
	{	uint8     type;				  // ��������
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
		uint8 State;					// De_FTP_Operation_Work ��������; De_FTP_Operation_NoWork   �������			
	}st_FTP_WorkState;
	typedef struct
	{	uint8 Buf[512];				//�ļ�����
		uint16 DataLength;			//�ļ�����
	}st_Buf_rwFlash;				//��ʱ�洢�ļ�
	typedef struct
	{	uint8 Fd;
		uint8 State;
	}st_Ftp_Link;
	typedef struct
	{	uint8 *pUser_CMD;   // �����½�û���
		uint8 *pPass_CMD;   // �����¼����
		uint8 *pPasv_CMD;   // ���ñ���ģʽ
		uint8 *pType_CMD;   // �����ļ�����
		uint8 *pList_CMD;   // �ļ��б�
		uint8 *pRest_CMD;   // ������ʼ��ַ
		uint8 *pRetr_CMD;   // ��ʼ�����ļ�
		uint8 *pQuit_CMD;   // �˳�������
		uint8 *pCwd_CMD;    // �ı乤��Ŀ¼
	}st_Ftp_CMD;
	typedef struct
	{	uint8 DownState;
		uint8 DownFileState;
		st_Ftp_Link CN_st_Ftp_Link_Data;
		st_Ftp_Link CN_st_Ftp_Link_Ctrl;
		uint32 TimeOut;
	}st_Ftp_RunState;
	typedef struct
	{	uint16 (*Init)(void);											//��ʼ���������ϵ���һ��
		uint16 (*GetState)(st_FTP_WorkState	*ptst_FTP_WorkState);		//��ȡ�������״̬	   			
	}st_Fun_FTP;
	#ifdef De_FTP_Compiler
		typedef struct
		{	st_Affair_UDPTCP CN_st_Affair_UDPTCP_Ctrl;
			st_Affair_UDPTCP CN_st_Affair_UDPTCP_Data;
		}st_Affair_Ftp;
	#endif
/*============================================Static Function================================================*/
	#ifdef De_FTP_Compiler
		static uint16 Init(void);
		static void Task(void *pdata);
		static uint16 FtpClose(void);
		static uint16 FTP_File_Init(void);
		static uint16 LogOnFtpServer(st_Ftp_RunState *ptst_Ftp_RunState,st_FTP_Data *ptst_FTP_Data,st_Affair_Ftp *ptst_Affair_Ftp,st_Ftp_CMD *ptst_Ftp_CMD);
		static uint16 FtpConfig(st_Affair_Ftp *ptst_Affair_Ftp,st_Ftp_RunState *ptst_Ftp_RunState,st_FTP_Data *ptst_FTP_Data,st_Ftp_CMD *ptst_Ftp_CMD);
		static uint16 GetFileNameDir(uint8 *FileName,uint8 *FileDir,st_FTP_Data *ptst_FTP_Data);
		static uint16 FTP_SendCommand(const uint8 *pCmdName, uint8 *pCmdPara,uint8 *pAsk,uint32 *AskData);
		static uint16 JudgeFtpAsk(uint8 *pAsk,uint32 *AskData);
		static void GetDataLinkPra(uint8 *pdata,st_Data_UDPTCP *ptst_Data_UDPTCP);
		static void GetFileLength(uint8 *pdata,uint32 *FileLength);
		static uint16 RevFtpData(void);
		static void FTP_CtrReceive(uint8 *Data,uint8 fd,uint16 DataLength);
		static void FTP_DataReceive(uint8 *Data,uint8 fd,uint16 DataLength);
		static uint16 GetState(st_FTP_WorkState	*ptst_FTP_WorkState);
		static uint16 ClearSem(OS_EVENT	*FTPSem);
		static uint16 ClearQ(OS_EVENT	*FTPSem);
/*=============================================Public Ram=====================================================*/
	
		st_FTP_Data *ptst_FTP_Data_Save,*ptst_FTP_Data_Temp;
		st_Buf_rwFlash CN_st_Buf_rwFlash;
		st_Ftp_RunState CN_st_Ftp_RunState;
		st_FTP_WorkState CN_st_FTP_WorkState;
		uint16 DownFileFd;
		OS_STK FTP_Stk[De_Ftp_Stk];
		void *MessegBox[De_Max_Messages]; 				//���ؼ���Ϣ����							
		OS_EVENT    	*FtpQbox;		  // ����FTP������ 
		OS_EVENT 		*FtpCtrlSem;	   // ������·����
		st_Buf_rwFlash CN_st_Buf_rwFlash;
		uint8 RecData_Type;	
		uint8 *ptRecData_Type;
		uint16 FTPRecoderFd;
		static uint8 *CN_Data;	
		const st_Affair_Ftp CN_st_Affair_Ftp = {{FTP_CtrReceive,NULL},{FTP_DataReceive,NULL}};
		const st_Ftp_CMD CN_st_Ftp_CMD={"USER","PASS","PASV","TYPE","LIST","REST","RETR","QUIT","CWD"};
		const st_Fun_FTP CN_st_Fun_FTP={Init,GetState};
   #else
		extern const st_Fun_FTP CN_st_Fun_FTP;
		extern OS_EVENT    	*FtpQbox;
		extern uint16 FTPRecoderFd;
//		extern uint16 DownFileFd;
   #endif
#endif










