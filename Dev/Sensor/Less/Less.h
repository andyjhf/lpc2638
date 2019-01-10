/*===========================================Include File=======================================================*/	
	#include "..\..\..\APP\config.h"
	#include "stdlib.h"
	#ifdef De_Less_Compiler
		#include "..\..\..\miscellaneous\CodeTrans\AscNumber.h"
		#include "..\..\..\miscellaneous\Arithmetic\Arithmetic.h"	
		#include "..\..\..\HardWare\UART\UART.h"
		#include "..\..\..\HardWare\RTC\RTC.h"
		#include "..\..\..\miscellaneous\Date\date.h"
		#include "..\_PuSensor.h"
	#endif
/*===========================================Define Data=======================================================*/
	#define De_Suc_Less															0				//本页成功
	/*++++++++++++++++++++++++++++++++++++++++错误代码一览表++++++++++++++++++++++++++++++++++++++++++++++*/
	#define De_Erro_Less_NoInit													De_Erro_Sensor_Less	//初始化失败
	#define De_Erro_Less_InitIng												De_Erro_Less_NoInit+1//已经初始化
	#define De_Erro_Less_OverMaxNumber											De_Erro_Less_InitIng+1
	#define De_Erro_Less_Config													De_Erro_Less_OverMaxNumber+1//传感器控件已满	
	#define De_Erro_Less_Explain												De_Erro_Less_Config+1
	#define De_Erro_Less_NoData													De_Erro_Less_Explain+1
	#define De_Erro_Less_FunClose												De_Erro_Less_NoData+1
	#define De_Erro_Less_NoWorkPar												De_Erro_Less_FunClose+1
/*++++++++++++++++++++++++++++++++++++++++++程序状态+++++++++++++++++++++++++++++++++++++++++++++++++*/
#ifdef De_Less_Compiler	
	#define De_Less_Max_Number													6				//最大支持6个传感器
	#define De_Less_State_Open													0				//打开
	#define De_Less_State_Close													1				//关闭
	#define De_Less_MaxNumber													6				//命令重发次数
	#define De_Less_Dly_Order						       						600				//接受最大等待时间
	#define De_Less_Val_State_New												0				//新数据
	#define De_Less_Val_State_Old												1				//旧数据
	#define De_Less_Val_State_Idl												2				//闲置数据	
/*++++++++++++++++++++++++++++++++++++++++++++硬件端口定义+++++++++++++++++++++++++++++++++++++++++++++++++++*/
	#define De_Wireless_Use_Uart 												1
		
	/*-----------------------------------------传感器协议有关------------------------------------------------*/		
		/*&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&传感器命令&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&*/
			/*^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^无线传感器端命令^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^*/
		#define De_Less_Search_Ask_ID		            	0xE3							//代表查询应答ID
		#define De_Less_Configuration_Ask_ID		       	0xE4	   						//代表配置应答ID
		#define De_Less_Temp_Date_ID	                    0xA0							//代表上传温度数据ID
		#define De_Less_Switch_Date_ID		                0xA2					    	//代表上传开关状态数据ID
		#define De_Less_Sensors_state_ID		           	0xCA							//代表上传传感器状态ID
			/*^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^GPRS端命令^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^*/		
		#define De_Less_Search_Receive_ID	            	0xD3							//代表查询接收端接收的传感器ID
		#define De_Less_Configuration_Receive_ID		    0xD4							//代表配置接收端接收的传感器ID
		#define De_Less_DoorDateAsk_ID		            	0xB2							//代表开关状态数据应答ID																					
		/*&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&传感器个数据状态&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&*/																					
		#define De_Less_In_Onoff_Open						0x11							//门状态为开
		#define De_Less_In_Onoff_Close						0x00							//门状态为关
		#define De_Less_In_Temp_Negative					0X11 							//温度为负
		#define De_Less_Config_Suc							0x11 							//配置无线传感器正确
		#define De_Less_DevBa_Erro							0x11 							//传感器电池馈电
		#define De_Less_Dev_Erro							0x11							//传感器工作不正常
#endif		
/*===========================================Data Define=======================================================*/
	/*++++++++++++++++++++++++++++++++++++++++私有结构体数据++++++++++++++++++++++++++++++++++++++++++++++*/
#ifdef De_Less_Compiler		
	typedef struct
	{	st_Sensor_DataPar	CN_st_Less_DataPar;
		uint8 Type;
		uint8 State;
	}st_Less_Par_Oper;
	typedef struct
	{	uint32 Val;
		uint8 State;
		uint32 MaxDly;
	}st_Less_Val;
#endif
/*==========================================static Function====================================================*/
#ifdef De_Less_Compiler		
	static uint16 Init1(void);
	static uint16 Open1(st_Sensor_DataPar	*ptst_Sensor_DataPar,uint8 *fd);
	static uint16 Close1(uint8 fd);
	static uint16 Read1(uint8 fd,void *SendBuf,void *AgreeBuf);
	static uint16 GetState1(st_Sensor_State	*ptst_Less_State,uint8 fd);	
	
	static uint16 Init(void);
	static uint16 Open(st_Sensor_DataPar	*ptst_Sensor_DataPar,uint8 *fd);
	static uint16 Close(uint8 fd);
	static uint16 Read(uint8 fd,void *SendBuf,void *AgreeBuf);
	static uint16 GetState(st_Sensor_State	*ptst_Less_State,uint8 fd);	
		
	static uint16 ExplainData(uint8 *Buf,uint16 SizeofBuf,uint8 OrderID,st_Less_Par_Oper	*ptst_Less_Par_Oper);
	static uint16 ExplainState(uint8 *Buf,uint16 SizeofBuf,st_Less_Par_Oper	*ptst_Less_Par_Oper);
	static uint8 LookID(uint32 Addree,uint16 WorkID,st_Less_Par_Oper	*ptst_Less_Par_Oper);
	static uint16 Configuration(st_Less_Par_Oper	*ptst_Less_DataParOut); 	  			//配置命令
	static void SendData(uint8 ID,uint8 *Buf,uint16 SizeofBuf);								//发送数据
	static uint16 AgreeData(uint8 *Buf,uint8 *ID,uint16 SizeofBufLen); 						//接收数据
	static uint16 ReadData(uint8 *Buf,uint16 ReadLen);
	static uint16 WriteData(uint8 *Buf,uint16 WriteLen);
	static void ClsData(void);
	static uint16 Lookfd(void);
	static uint32 GetTimeAdd(uint8 *Small,uint8 *Big);
#endif	 	   
/*=============================================================================================================*/
#ifdef De_Less_Compiler	
	static const st_Fun_Sensor2Hard	CN_st_Fun_Sensor2Hard={Init1,Open1,Close1,Read1,GetState1};
	static const st_Sensor_Par2Type	CN_st_Sensor_Par2Type[]=
	{	{	De_Sensor_WordPar_Less_Switch1,De_Sensor_Par_Onoff	},
		{	De_Sensor_WordPar_Less_Switch2,De_Sensor_Par_Onoff	},
		{	De_Sensor_WordPar_Less_Switch3,De_Sensor_Par_Onoff	},
		{	De_Sensor_WordPar_Less_Switch4,De_Sensor_Par_Onoff	},
		{	De_Sensor_WordPar_Less_Switch5,De_Sensor_Par_Onoff	},
		{	De_Sensor_WordPar_Less_Switch6,De_Sensor_Par_Onoff	},
		{	De_Sensor_WordPar_Less_Temp1,De_Sensor_Par_Temp},
		{	De_Sensor_WordPar_Less_Temp2,De_Sensor_Par_Temp},
		{	De_Sensor_WordPar_Less_Temp3,De_Sensor_Par_Temp},
		{	De_Sensor_WordPar_Less_Temp4,De_Sensor_Par_Temp}
	};	
	const st_Sensor_ParList		CN_Less_st_Sensor_ParList=
	{	&CN_st_Fun_Sensor2Hard,CN_st_Sensor_Par2Type,sizeof(CN_st_Sensor_Par2Type)/sizeof(st_Sensor_Par2Type)
	};

	const st_Less_Par_Oper	CN_Ba_st_Less_Par_Oper=
	{	{0xffffffff,0xffff,0xffffffff},De_Sensor_Par_No,De_Less_State_Close};
	
	const st_Sensor_State		CN_Ba_st_Less_State=
	{	De_Sensor_State_Suc,De_Sensor_State_Suc,De_Sensor_State_Suc};
	
	const st_Less_Val		CN_Ba_st_Less_Val=
	{	0,De_Less_Val_State_Idl,0};	
	
	const uint8 Com_FlagHead[]={'*','*','*'};							//包头信息
	
	const uint8 Com_FlagEnd[]={'#','#','#'};							//包尾信息
	st_Less_Par_Oper	CN_st_Less_Par_Oper[De_Less_Max_Number];
	st_Sensor_State	CN_st_Less_State[De_Less_Max_Number];
	st_Less_Val		CN_st_Less_Val[De_Less_Max_Number];
	static uint8 DateTime[7];
	static uint8 Buf[100];
	static OS_EVENT	*LessSem=NULL;
  #else
	extern const st_Sensor_ParList	CN_Less_st_Sensor_ParList;

   #endif



