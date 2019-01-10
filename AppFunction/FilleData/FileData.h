
/*======================================Include File============================================================*/
 	#include "..\..\APP\config.h"
	#include "stdlib.h"
	//#include "..\..\HardWare\Can\Can.H"
	#ifdef De_FileData_Compiler
		#include "..\..\File\rwFile.h"
		#include "..\..\miscellaneous\CodeTrans\AscNumber.h"
		#include "..\..\Control\Timer\Timer.h"
		#include "..\..\Control\Gps\GpsTask.h"
		#include "..\..\Control\Sleep\Sleep.h"
		#include "..\..\HardWare\RTC\RTC.h"
		#include "..\..\AppFunction\DataTrans\DataTrans.h"
		#include "..\..\Control\Gprs\GPRS.h"
	#endif
/*======================================Define Data============================================================*/
	/*++++++++++++++++++++++++++++++++++�������һ����++++++++++++++++++++++++++++++++++++++++++++++++++*/

	/*+++++++++++++++++++++++++++++++++++++�ļ�����+++++++++++++++++++++++++++++++++++++++++++++++++++++*/
	#define De_FileName_Basic						"Basic1"				//�����ͺš�����汾�š�Ӳ���汾�š����Ҵ��š��������
	#define	De_FileName_CanID						"CanID"			    //�ܹ����ܵ�CAN���ݵ�ID
	#define De_FileName_Parameter					"Parame"			//�ٶȡ�����ʱ�䡢������Ѳ��ʱ�䡢����״̬Ѳ��ʱ�䡢���ĺ���1�����ĺ���2��ʹ�ܷ����ַ���CanID��ACC���ء��Ƿ�ϵ����
	#define De_FileName_AccTimer					"AccTim"			//Accͳ��ʱ��
	#define De_FileName_TimerUpLoade				"UpLoad"			//��ʱ�ϴ�ʱ�䡢��ʱ�ϴ�����
	#define De_FileName_Message						"Message"			//�������ź�ʱ�ı���
	#define De_FileName_MessageSend					"MeSend"			//���ͱ�
	#define De_FileName_GpsMessage					"GpsMge"
	
	#define De_Suc_State							0

	#define De_State_Control							1
	#define De_State_NoControl							0
	#define De_IO_Control								0x01
	#define De_IO_Control_Remote_Out					FIO2DIR|=De_IO_Control
	#define De_IO_Control_Remote						FIO2SET|=De_IO_Control				//�ߵ�ƽ
	#define De_IO_NoControl_Remote						FIO2CLR|=De_IO_Control
	
	#define De_VoAlarm_No								0
	#define De_VoAlarm_Yes								1							

	#define De_IO_unLock								De_IO_Control_Remote_Out;De_IO_Control_Remote
	#define De_IO_Lock									De_IO_Control_Remote_Out;De_IO_NoControl_Remote
	

   	#define De_Can_Data_MaxID						10
/*=======================================Data Define===========================================================*/
	/*++++++++++++++++++++++++Ŀ��:������ά������ʱ�����ݿ��ļ�,��Ӧ�ó����Ϊ���¼����ļ�+++++++++++++++++++++*/
	typedef struct
	{	uint32 Speed;	   				//�ٶ�
		uint32 SleepTimer;				//����ʱ��
		uint32 SleepCheckTimer;		   	//������Ѳ��ʱ��
		uint32 WorkCheckTimer;			//gongzuo��Ѳ��ʱ��
		uint32 LowVolTimer;				//��ѹ��ʱ����ʱ�����ϴ���Ϣ
		uint32 HighVolTimer;			//��ѹ�ָ�����ʱ����ʱ�����ϴ���Ϣ	
		uint8 CenterPhone1[15];	  		//���ĺ���1
		uint8 CenterPhone2[15];   		// ���ĺ���2
		uint8 CheckPhone;				//Ѳ�����	 1��1������   2��2������
		uint8 TimePhone;				//׷�ٺ���	 1��1������   2��2������
		uint8 CenPhone[15];				//���ŷ������ĺ���
		uint8  EnableChar[3];			//ʹ�ܷ����ַ�
		uint8 VoAlarmState;
		uint16 CanId;	 				//CANID
			//st_Da_CanInfor	CN_st_Da_CanInfor[2];
		uint32 CanSendTimer;			//
		uint8  AccFun;					//acc���ܿ�
		uint8  ControlEnable; 			//�Ƿ����
		uint32 HighV;					//��ѹ���������
		uint32 HighL;					//��ѹ���ʱ����
	}st_File_Parameter;

	typedef struct
	{	uint8 SoftEdition[8];				//����汾
		uint8 HardEdition[8];				//Ӳ���汾
		uint8 MachID[16];					//�������
		uint8 MachType[2];					//��������
		uint8 MakeFactory[2];				//���Ҵ���
	}st_File_Basic;

	typedef struct
	{	uint16 CanID[De_Can_Data_MaxID];	//�ܹ����ܵ�CAN������
	
	}st_File_CanID;

	typedef struct
	{	uint32 Timer;					//��ʱ�ش���ʱ��
		uint32 Number;					//��ʱ�ش��Ĵ���
		uint32 NonceNumber;				//��ǰ�ش��Ĵ���
	}st_File_UpLoader;	
	typedef struct
	{	uint8 DateTime[7];
		uint8 Phone[15];
		uint8 Message[200];	
	}st_File_Message;

	typedef struct
	{	uint16 	Parameterfd;			//����ID
		uint16	Basicfd;				//��������ID
		uint16 	CanIDfd;				//CAN
		uint16 	UpLoaderfd;				//
	   	uint16	Messagefd;
		uint16	AccTimerfd;
		uint16	MessageSend;
		uint16	GpsMessagefd;
	}st_File_fd;



	/*+++++++++++++++++++++++++++++++++++++ϵͳ���й����е�״̬++++++++++++++++++++++++++++++++++++++++++++++++++*/
	typedef struct
	{	uint8 GpsState;						//GPS״̬
		uint8 GsmState;						//GSM״̬
		uint8 FlashState;					//FLASH״̬
		uint8 AccState;						//ACC״̬
		uint8 AccFunction;					//Acc����
		uint8 Sleep;						//�Ƿ�����
		uint8 voltage;						//��ѹ�Ƿ�����
		uint8 Speed;						//�����Ƿ�����
		uint8 Control;						//�Ƿ����								 
	}st_Sys_State;

	typedef struct
	{	uint8 Messagefd;					//���ܶ���Ϣ�¼�
		uint8 Phonefd;						//�绰�¼�
		uint8 Gpsfd;						//GPS�¼�
		uint8 Accfd;						//Acc�����¼�
		uint8 AccSleepfd;					//Acc�ر�����						
		uint8 VoDownfd;						//�͵�ѹ�����¼�
		uint8 VoUpfd;						//��ѹ�ָ�
		uint8 Sleepfd;						//�����¼�
		uint8 UpSleepfd;					//����״̬�¼�
		uint8 SleepCheckTimer;			//����״̬�µ�Ѳ���¼�
		uint8 CheckTimer;					//����״̬�µ�Ѳ���¼�
		uint8 Timerfd;						//��ʱ�ش��¼�
		uint8 Canfd;						//CAN�����¼�
		uint8 CanSendfd;					//CAN�����¼�
		uint8 HandfdGsm;						//�ֱ�ͨѶ�¼�
		uint8 HandfdGps;						//�ֱ�ͨѶ�¼�
		uint8 TraCheckDatafd;
		uint8 DellGpsfd;

	}st_Sys_Event;
	typedef struct
	{	uint32	FrameData[2];
	}st_CanData;

	typedef struct
	{	st_CanData 	CN_CanData[De_Can_Data_MaxID];
		uint16		CanID[De_Can_Data_MaxID];
		uint8 DateTime[7];
	}st_Data_Can;
	typedef struct
	{	uint8 Speed;				//�ٶ�
		uint32 Vol;					//��ѹ
		uint32 Timer;				//��ʱ�ش�
		uint32 CheckTimer;			//Ѳ��

	}st_Waring_Sys;




/*==========================================Static Function=====================================================*/	
	void CheckFile(void);
	void SendMessage(uint8 *Buf,uint8 *Phone);
	void Get_Gps_Data(uint8 *Buf);
	void GetPhone(uint8 *Phone,uint8 *CenterNum);
	void Get_Gps_DataHand(uint8 *Buf);
	void BackInit(void);
	void InitCenPhone(void);
	#ifdef De_FileData_Compiler
		static void Get_Sys_State(void);
		static void CheckFile_Basic(void);
		static void CheckFile_CanID(void);
		static void CheckFile_Parameter(void);
		static void CheckFile_Acc(void);
		static void CheckFile_UpLoader(void);
		static void CheckFile_Message(void);						//����Ϣ
		static void CheckFile_MessageState(void);
		static void CheckFile_GpsMessage(void);
		static void BackBasic(void);
		static void BackCan(void);
		static void BackPareameter(void);
		static void BackUpLoader(void);
		static void BackAccTimer(void);
/*============================================Public Ram=========================================================*/	
		st_Sys_State	CN_st_Sys_State;
		st_Sys_Event	CN_st_Sys_Event;
		st_Data_Can		CN_st_Data_Can;	
		st_Waring_Sys	CN_st_Waring_Sys;
		st_File_fd		CN_st_File_fd;
		uint16			MessageTail;
		uint16			MessageSendSpace;
		uint16 			MessageNumber;	
		uint8			CN_X_BUF[512];
		uint8			SleepCheck;
		uint8			TimeSend;
		OS_EVENT *FileDataSem;
	#else
		extern st_Sys_State	CN_st_Sys_State;
		extern st_Sys_Event	CN_st_Sys_Event;
		extern st_Waring_Sys	CN_st_Waring_Sys;
		extern st_Data_Can		CN_st_Data_Can;	
		extern uint8			CN_X_BUF[512];
		extern uint16			MessageTail;
		extern uint16			MessageSendSpace;
		extern uint16 			MessageNumber;
		extern st_File_fd		CN_st_File_fd;
		extern uint8			SleepCheck;
		extern uint8			TimeSend;
#endif






