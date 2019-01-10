#define FTP_H
#ifdef  FTP_H
/*=========================================include File===========================================================*/	
	#include "..\..\APP\config.h"
	#include "stdlib.h"
	#ifdef De_FTP_Compiler
		#include "..\..\miscellaneous\CodeTrans\AscNumber.h"				// 引用码制转换资源
		#include "..\Gprs\GPRS.h"								// 引用GPRS控件
		#include "..\..\HardWare\UART\UART.h" 								// 引用串口
		#include "..\..\File\DownFile.h"										// 引用文件系统
		#include "..\..\File\rwFile.h"
		#include "..\..\miscellaneous\Arithmetic\Arithmetic.h" 				// 引用算法
	#endif
/*==============================Define Data==================================================*/	
	/*+++++++++++++++++++++++++++++++错误代码一栏表+++++++++++++++++++++++++++++++++++++++++*/
	#define De_Suc_FTP							 0
	#define De_Erro_FTP_Start                    1								 //此值由PUBLIC统一定义
	#define De_Erro_FTP_Init					 De_Erro_FTP_Start+1		     // FTP初始化错误
	#define De_Erro_FTP_InitTCPLink				 De_Erro_FTP_Init+1				 //	TCP链路初始化错误
	#define De_Erro_FTP_OpenCtrLink 			 De_Erro_FTP_InitTCPLink+1		 // 控制链路打开错误
	#define De_Erro_FTP_OpenDatLink           	 De_Erro_FTP_OpenCtrLink+1		 // 数据链路打开错误
	#define De_Erro_FTP_SendCommand				 De_Erro_FTP_OpenDatLink+1 		 // 发送FTP命令错误
	#define De_Erro_FTP_AskErro					 De_Erro_FTP_SendCommand+1		 // 服务器应答错误（并非所要的应答）
	#define De_Erro_FTP_TimeOut					 De_Erro_FTP_AskErro+1           // 数据接收超时  
	#define De_Erro_FTP_RevWrong				 De_Erro_FTP_TimeOut+1			 // 下载错误，长度不对等
	#define De_Erro_FTP_Finish					 De_Erro_FTP_RevWrong+1			 //数据下载完成
	/*+++++++++++++++++++++++++++++++程序状态字+++++++++++++++++++++++++++++++++++++++++++*/
	#define De_FTP_Operation_Work						1		//正在下载
	#define	De_FTP_Operation_Idle						0		//空闲
	#define De_FTP_Link_Close							0
	#define De_FTP_Link_Open							1
	#define De_FTP_Down_Nofinish       					0
	#define De_FTP_Down_Finish         					1
	#define De_FTP_StartCmd								1
	#define De_FTP_CtrLink     							2
	#define De_FTP_DataLink								3
	#define De_Max_Messages								10		//最大消息量
	#define De_Max_FileSize            					307200  //300K
	#define De_FileName_FTP								"FTP"
	/*++++++++++++++++++++++++++++++++操作系统有关++++++++++++++++++++++++++++++++++++++++*/
	#ifdef De_FTP_Compiler	
		#define De_Ftp_Task							    9//7//
		#define De_Ftp_Stk								356
	#endif
/*=======================================Data Define==========================================*/
	/*++++++++++++++++++++++++++++++++数据结构定义+++++++++++++++++++++++++++++++++++++++++++*/
	typedef struct
	{	uint32    CtrLinkIpAdd;       // 控制链路IP地址,4字节IP地址,如：221.223.224.225 0xdd de df e0
	    uint16    CtrLinkPort;        // 控制链路端口号 0~65535
	    uint8     LoginName[40];      // 登陆用户名	 ASC表示不足补零
	    uint8     LoginPassword[40];  // 登陆密码 		 ASC表示不足补零
	    uint8     FileDirName[200];   // 文件名，包括文件夹路径	ASC表示不足补零
		uint8     SaveFileName[32];	  // 保存本地文件的文件名
		uint8     UpFlag;			  //下载文件完整性
	}st_FTP_Recoder;
	typedef struct
	{	uint8     type;				  // 命令类型
		uint32    CtrLinkIpAdd;       // 控制链路IP地址,4字节IP地址,如：221.223.224.225 0xdd de df e0
	    uint16    CtrLinkPort;        // 控制链路端口号 0~65535
	    uint8     LoginName[40];      // 登陆用户名	 ASC表示不足补零
	    uint8     LoginPassword[40];  // 登陆密码 		 ASC表示不足补零
	    uint8     FileDirName[200];   // 文件名，包括文件夹路径	ASC表示不足补零
		uint8     SaveFileName[32];	  // 保存本地文件的文件名 				 	
		uint16    Result;	  
		OS_EVENT  *LocalBox;
	}st_FTP_Data;     // FTP下载参数
	typedef struct
	{	uint32 FileLen;					// 需要下载的文件的总长度
		uint32 DownLoaderLen;			// 当前已经下载的长度
		uint8 State;					// De_FTP_Operation_Work 正在下载; De_FTP_Operation_NoWork   程序空闲			
	}st_FTP_WorkState;
	typedef struct
	{	uint8 Buf[512];				//文件数据
		uint16 DataLength;			//文件长度
	}st_Buf_rwFlash;				//临时存储文件
	typedef struct
	{	uint8 Fd;
		uint8 State;
	}st_Ftp_Link;
	typedef struct
	{	uint8 *pUser_CMD;   // 输入登陆用户名
		uint8 *pPass_CMD;   // 输入登录密码
		uint8 *pPasv_CMD;   // 设置被动模式
		uint8 *pType_CMD;   // 设置文件类型
		uint8 *pList_CMD;   // 文件列表
		uint8 *pRest_CMD;   // 设置起始地址
		uint8 *pRetr_CMD;   // 开始下载文件
		uint8 *pQuit_CMD;   // 退出服务器
		uint8 *pCwd_CMD;    // 改变工作目录
	}st_Ftp_CMD;
	typedef struct
	{	uint8 DownState;
		uint8 DownFileState;
		st_Ftp_Link CN_st_Ftp_Link_Data;
		st_Ftp_Link CN_st_Ftp_Link_Ctrl;
		uint32 TimeOut;
	}st_Ftp_RunState;
	typedef struct
	{	uint16 (*Init)(void);											//初始化函数，上电后打开一次
		uint16 (*GetState)(st_FTP_WorkState	*ptst_FTP_WorkState);		//获取本任务的状态	   			
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
		void *MessegBox[De_Max_Messages]; 				//本控件消息队列							
		OS_EVENT    	*FtpQbox;		  // 启动FTP的邮箱 
		OS_EVENT 		*FtpCtrlSem;	   // 控制链路邮箱
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










