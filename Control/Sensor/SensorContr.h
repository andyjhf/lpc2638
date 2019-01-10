/*=======================================Include File===========================================================*/
   	#include "..\..\APP\config.h"
	#include "stdlib.h"
	#ifdef De_SensorContr_Compiler
		#include "..\..\miscellaneous\CodeTrans\AscNumber.h"
		#include "..\..\Dev\Sensor\_PuSensor.h"
		#include "..\..\Dev\Sensor\Sensor.h"
		#include "..\..\HardWare\RTC\RTC.h"
		#include "..\Gprs\Gprs.h"
	#endif
/*=======================================Define Data============================================================*/
	#define De_Suc_SensorContr											0
	/*+++++++++++++++++++++++++++++++++++错误代码一览表+++++++++++++++++++++++++++++++++++++*/
	#define De_Erro_SensorContr_Init  										1
	#define De_Erro_SensorContr_OverMaxNumber								De_Erro_SensorContr_Init+1	
	#define De_Erro_SensorContr_NoPar										De_Erro_SensorContr_OverMaxNumber+1	
	#define De_Affair_Sensor_MaxNumber										20 							//最大20个事件

#ifdef De_SensorContr_Compiler 	
	#define De_Affair_Sensor_Fun_Open									1							//功能打开
	#define De_Affair_Sensor_Fun_Close									2							//功能关闭
	/*+++++++++++++++++++++++++++++++++++任务有关参数+++++++++++++++++++++++++++++++++*/
	#define De_Stk_Size													630							//堆大小
	#define De_SensorContr_TaskDly										100							//延时调度时间
	
	#define De_Task_Number												6
#endif		
/*========================================Data Define===========================================================*/
	typedef struct
	{	void (*	ptFunc)(uint16 Par,void *Data,uint8 *DateTimer); 							//获取到参数的函数
		void (*	GetState)(uint16 Par,st_Sensor_State	*ptst_Sensor_State);				//当传感器状态异常的函数
	}st_Affair_Sensor;
	typedef struct
	{	uint8 (*Init)(void);
		uint8 (*Open)(uint16 Par,st_Affair_Sensor	*ptst_Affair_Sensor,uint8 *fd);
		uint8 (*Close)(uint8 fd);
	}st_Fun_SensorContr;


#ifdef De_SensorContr_Compiler
	typedef struct
	{	uint16 Par[De_Affair_Sensor_MaxNumber];											//事件ID
		uint8 State[De_Affair_Sensor_MaxNumber];										//各个传感器状态
	}st_Affair_Sensor_OperData;
#endif
/*========================================static Function=======================================================*/
#ifdef De_SensorContr_Compiler	
	static uint8 Init(void);
	static uint8 Open(uint16 Par,st_Affair_Sensor	*ptst_Affair_Sensor,uint8 *fd);
	static uint8 Close(uint8 fd);
	static void Task(void *pData);
#endif		
/*============================================Pubic Ram=========================================================*/	
#ifdef De_SensorContr_Compiler	
	static const st_Affair_Sensor	CN_Ba_st_Affair_Sensor={NULL,NULL};
	static st_Affair_Sensor	CN_st_Affair_Sensor[De_Affair_Sensor_MaxNumber];
	static st_Affair_Sensor_OperData	CN_st_Affair_Sensor_OperData;
	static uint8 X_BUF[sizeof(st_Display_Par)];
	static st_Sensor_State	CN_st_Sensor_State;
	static OS_EVENT	*SensorContrSem=NULL;
	static OS_STK	STK[De_Stk_Size];
	static st_Display_Send	CN_st_Display_Send;
	static st_Data_Gprs_Call CN_st_Data_Gprs_Call;
	static const uint16 CN_Ba_OpenTermPar[]=
	{ 		De_Sensor_WordPar_Switch1,					//开关量1
			De_Sensor_WordPar_Switch2,				//开关量2
			De_Sensor_WordPar_Switch3,					//开关量3
			De_Sensor_WordPar_Switch4,					//开关量4
			De_Sensor_WordPar_Switch5,					//开关量5
			De_Sensor_WordPar_Switch6,					//开关量6
			De_Sensor_WordPar_Switch7,					//开关量7
			De_Sensor_WordPar_Switch8,					//开关量8
			De_Sensor_WordPar_Switch9,					//开关量9
			De_Sensor_WordPar_Switch10,					//开关量10
			De_Sensor_WordPar_Switch11,					//开关量11
			De_Sensor_WordPar_Switch12,					//开关量12
			De_Sensor_WordPar_Switch13,					//开关量13
			De_Sensor_WordPar_Switch14,					//开关量14
			De_Sensor_WordPar_Switch15,					//开关量15
			De_Sensor_WordPar_Switch16,					//开关量16

			De_Sensor_WordPar_Less_Switch1,				   	//无线开关量1
			De_Sensor_WordPar_Less_Switch2,					//无线开关量2
			De_Sensor_WordPar_Less_Switch3,					//无线开关量3
			De_Sensor_WordPar_Less_Switch4,					//无线开关量4
			De_Sensor_WordPar_Less_Switch5,					//无线开关量5
			De_Sensor_WordPar_Less_Switch6,					//无线开关量6

			De_Sensor_WordPar_AccTimer,				//ACC累计时间					//里程统计
			De_Sensor_WordPar_Oil1,					//油箱油位1
			De_Sensor_WordPar_SendOilTimer,					//喷油累计时间
			De_Sensor_WordPar_Temp,					//温度
			De_Sensor_WordPar_Oil2,					//油箱油位2
			De_Sensor_WordPar_Pulse,					//脉冲个数
			De_Sensor_WordPar_Humidity,					//湿度
			De_Sensor_WordPar_OilBaifen,					//油箱油位百分比
			De_Sensor_WordPar_Less_Temp1,					//无线传感器温度1      
			De_Sensor_WordPar_Less_Temp2,					//无线传感器温度2   
			De_Sensor_WordPar_Less_Temp3,					//无线传感器温度3   
			De_Sensor_WordPar_Less_Temp4,					//无线传感器温度4
			De_Sensor_WordPar_VaCheck,					//电压检测				
			//GPS参数
	
			De_Sensor_WordPar_Temperture_1, 				//温度1路
			De_Sensor_WordPar_Temperture_2,  				//温度2路					//圆形区域
			De_Sensor_WordPar_Help,
			De_Sensor_WordPar_Display						
	};
	const st_Fun_SensorContr	CN_st_Fun_SensorContr={Init,Open,Close};
#else
	extern const st_Fun_SensorContr	CN_st_Fun_SensorContr;
#endif









