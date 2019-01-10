/*
//将FTP作为一个控件来做.平常FTP处于等待状态，等待应用程序给一个邮箱,邮箱内容见<st_FTP_Data>所示,任务收到邮箱后将
//邮箱内容保存在本地缓存，然后执行任务.当任务执行完成后,再次通过另外一个邮箱发送本次升级失败或者是成功。如果成功
//则需要传递存储文件的名称.见<st_FTP_ReData>;
//
*/

#define FTP_H
#ifdef  FTP_H

/*=========================================include File===========================================================*/	
	#include "..\..\APP\config.h"
	#include "stdlib.h"
	#ifdef De_FTP_Compiler

		#include "..\..\miscellaneous\CodeTrans\AscNumber.h"				// 引用码制转换资源
		#include "..\..\Control\Gprs\GPRS.h"								// 引用GPRS控件
		#include "..\..\HardWare\UART\UART.h" 								// 引用串口
		#include "..\..\File\DownFile.h"										// 引用文件系统
		#include "..\..\File\rwFile.h"
		#include "..\..\miscellaneous\Arithmetic\Arithmetic.h" 				// 引用算法
	#endif

/*=========================================错误代码列表========================================================*/
#define De_Erro_FTP_Start                    0xa0	//此值由PUBLIC统一定义
#define De_Suc_FTP							 0
#define De_Erro_FTP_Init					 De_Erro_FTP_Start+1		     // FTP初始化错误
#define De_Erro_FTP_InitTCPLink				 De_Erro_FTP_Init+1				 //	TCP链路初始化错误
#define De_Erro_FTP_OpenCtrLink 			 De_Erro_FTP_InitTCPLink+1		 // 控制链路打开错误
#define De_Erro_FTP_OpenDatLink           	 De_Erro_FTP_OpenCtrLink+1		 // 数据链路打开错误
#define De_Erro_FTP_SendCommand				 De_Erro_FTP_OpenDatLink+1 		 // 发送FTP命令错误
#define De_Erro_FTP_AskErro					 De_Erro_FTP_SendCommand+1		 // 服务器应答错误（并非所要的应答）
#define De_Erro_FTP_TimeOut					 De_Erro_FTP_AskErro+1           // 数据接收超时  
#define De_Erro_FTP_RevWrong				 De_Erro_FTP_TimeOut+1			 // 下载错误，长度不对等

/*===========================其他宏定义=====================*/

#define De_FTP_Operation_NoWork    0		// FTP空闲状态
#define De_FTP_Operation_Work      1		// FTP正在下载 
#define De_Max_FileSize            256000  //250K
#define De_Max_Messages  			5			//同时最多可以接收的命令

#define De_FTP_StartCmd			1
#define De_FTP_CtrLink     		2
#define De_FTP_DataLink			3

#define De_FTP_Link_Close          0
#define De_FTP_Link_Open           1

#define De_FTP_Down_Nofinish       0
#define De_FTP_Down_Finish         1

/*++++++++++++++++++++++++++++++++操作系统有关++++++++++++++++++++++++++++++++++++++++*/
		#define De_FTP_Task							    7
		#define De_FTP_Stk								1024
		#define De_FTP_TaskDly							50				 // 延时调度时间
		#define OUTTIME                                 20               // 超时时间 20s	  
	

/*=======================================Data Define=========================================================*/			
		/*++++++++++++++++++++++++++++++数据结构体定义++++++++++++++++++++++++++++++++++++++*/
	

	typedef struct
	{	
		uint8     type;				  // 命令类型
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
		st_FTP_Data	cn_FTP_Data;	    // 当前下载的参数
		uint8 State;					// De_FTP_Operation_Work 正在下载; De_FTP_Operation_NoWork   程序空闲			
	}st_FTP_WorkState;

   	typedef struct
	{
		st_FTP_Data  cn_FTP_Data; 	  
	    uint32       DataLinkIpAdd;        // 数据链路IP地址
	    uint16       DataLinkPort;         // 数据链路端口号     
//	    uint32       FileLength;           // 文件长度
//	    uint32       DownFileLen;          // 已经下载的文件长度
//		uint32       FileOffset;           // 文件存储偏移
		uint16       CRC;                  // CRC校验值
	    uint8        state;                // De_FTP_Operation_Work 正在下载; De_FTP_Operation_NoWork   程序空闲	
	}st_FtpDown_Data;         //FTP下载参数


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

	}un_FTP_Cmd;	 //FTP命令结构

	typedef struct
	{
		uint8   fd;              // ftp控制链路的id
		uint8   state;           // 状态
	} st_Ftp_Link;

	typedef struct
	{		
		uint16  FtpDownFd;              // 下载文件的id
	//	uint16  FTP_Info_Fd;              // 下载信息的id
	}st_FTP_ID;		//ID


	typedef struct
	{
		uint8  FileDes;       // 存储目的地，1，表示存储在内部flash，2表示存储在外部flash
		uint8  FileName[32];  // 文件名
		uint32 StartAddr;	  // 起始地址，对于存储于外部flash的文件该字段无效
		uint32 MaxFileSize;   // 文件所占用的空间最大大小
		uint16 fd;
	}st_FileInfor;

	typedef struct
	{ 	uint8  FileName[32];  // 文件名
		uint32  TotalFileLen;    // 文件总长度
		uint32  RevFileLen;      // 已经接收的文件长度
		uint8   UpFlag;          // 升级标志,0,未升级，1，已经下载到外部flash,2,已经烧写完成
		uint16  HeadRecoderNum;
		uint16  TailRecoderNum;
	}st_UpFileInfor;		 //升级文件信息
	typedef struct
	{	uint8 Buf[512];
		uint16 DataLength;
	}st_Buf_rwFlash;



/*======================================输出函数======================================================*/
		typedef struct
		{	uint16 (*Init)(void);											//初始化函数，上电后打开一次
			uint16 (*GetState)(st_FTP_WorkState	*ptst_FTP_WorkState);		//获取本任务的状态	   			
		}st_Fun_FTP;


/*=========================================内部函数===========================================================*/	
	#ifdef De_FTP_Compiler

	    //FTP命令 
		const uint8 *pUser_CMD = "USER";   // 输入登陆用户名
		const uint8 *pPass_CMD = "PASS";   // 输入登录密码
		const uint8 *pPasv_CMD = "PASV";   // 设置被动模式
		const uint8 *pType_CMD = "TYPE";   // 设置文件类型
		const uint8 *pList_CMD = "LIST";   // 文件列表
		const uint8 *pRest_CMD = "REST";   // 设置起始地址
		const uint8 *pRetr_CMD = "RETR";   // 开始下载文件
		const uint8 *pQuit_CMD = "QUIT";   // 退出服务器
		const uint8 *pCwd_CMD  = "CWD";    // 改变工作目录   

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
		

		void *MessegBox[De_Max_Messages]; 				//本控件消息队列							
		OS_EVENT    	*FtpQbox;		  // 启动FTP的邮箱 
		OS_EVENT 		*FtpCtrlSem;	   // 控制链路邮箱	 		
		st_FTP_Data 	*pFtpBox;

		static OS_STK FTP_Stk[De_FTP_Stk];
		
		st_FTP_ID  		 CN_FTP_ID;   //所用到的id
		st_FtpDown_Data  CN_FtpDown_Data;	// 内部使用的全局变量
			
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
		 extern OS_EVENT    *FtpQbox;					// 启动FTP的邮箱 		
		 
	#endif

#endif
