#include "..\..\..\Public_H\DePublic.h"
#ifdef 	De_Compiler_HardWare_Gps
/*===========================================Include File====================================================*/
	#include "..\..\..\APP\config.h"								//LPC2368寄存器引用
 	#include "stdlib.h"											//C函数引用
	 						//引用串口
	#ifdef De_Gps_Compiler
		#include "..\..\..\HardWare\UART\UART.h" 
		#include "..\..\..\miscellaneous\CodeTrans\AscNumber.h"		//引用码制转换资源
		#include "..\..\..\miscellaneous\Date\Date.h"					//引用日期资源
		#include "..\..\..\miscellaneous\Arithmetic\Arithmetic.h" 		//引入算法
		#include "..\_PuSensor.h"
	#endif
/*===========================================Define Data====================================================*/
	/*++++++++++++++++++++++++++++++++++++++错误代码一览表+++++++++++++++++++++++++++++++++++++++++++++*/							
		
		#define De_Suc_Gps							0									//本页成功标志

		#define De_Erro_Gps_Data					De_Erro_Gps		  					//数据分析错误
		#define De_Erro_Gps_Order					De_Erro_Gps_Data+1					//没有此命令
		#define De_Erro_Gps_NoPower					De_Erro_Gps_Order+1
		#define De_Erro_Gps_Init					De_Erro_Gps_NoPower+1
		#define De_Erro_Gps_TimeOut					De_Erro_Gps_Init+1
		#define De_Erro_Gps_DataInval				De_Erro_Gps_TimeOut+1
		#define De_Erro_Gps_NoLocation				De_Erro_Gps_DataInval+1
	/*++++++++++++++++++++++++++++++++++++++程序标志状态++++++++++++++++++++++++++++++++++++++++++++++*/
		#define De_Gps_Use_Uart						4						//GPS使用的串口
		#define De_Gps_Location_True				'A'						//有效定位
		#define De_Gps_Location_Flase				'V'						//无效定位
		#define De_Gps_LatHem_N						'N'						//北半球
		#define De_Gps_LatHem_S						'S'						//南半球
		#define De_Gps_LongHem_E					'E'						//东半球
		#define De_Gps_LongHem_W					'W'						//西半球
		#define De_Gps_State_Power_Up				1						//
		#define De_Gps_State_Power_Down				0
		#define De_Gps_MaxAgreeBuf					100
		#define De_Gps_Flag_Open					0
		#define De_Gps_Flag_Close					1
	/*+++++++++++++++++++++++++++++++++++++GPS通讯命令++++++++++++++++++++++++++++++++++++++++++++++*/
	#ifdef De_Gps_Compiler
		#define De_Gps_Order_GPGSV								1						//可见卫星个数
		#define De_Gps_Order_GPGSA								2						//当前卫星信息
		#define De_Gps_Order_GPGGA								3						//定位信息
		#define De_Gps_Order_GPRMC								4						//推荐定位信息
		#define De_Gps_Order_GPVTG								5						//地面速度信息
		#define De_Gps_Order_GPGLL								6						//定位地理信息
		#define De_Gps_Order_GPZDA								7						//当前时间
		#define De_Gps_Order_GPDTM								8						//大地坐标系统
		#define De_Gps_Order_MaxNumber							De_Gps_Order_GPDTM 		//命令个数

	/*++++++++++++++++++++++++++++++++++++++数据解析有关+++++++++++++++++++++++++++++++++++++++++++*/
		/*----------------------------------GPRMC 数据位置------------------------------------*/
		#define De_Gps_Parse_Space_Time						1 										//时间
		#define De_Gps_Parse_Space_Location					2										//定位状态
		#define De_Gps_Parse_Space_Latitude					3										//纬度
		#define De_Gps_Parse_Space_LatHem					4										//纬度半球
		#define De_Gps_Parse_Space_Longitude				5										//经度
		#define De_Gps_Parse_Space_LongHem	  				6										//经度半球
		#define De_Gps_Parse_Space_Speed					7										//速度
		#define De_Gps_Parse_Space_Angle					8					   					//
		#define De_Gps_Parse_Space_Date						9										//日期
		/*-----------------------------------GPGGA 定位信息-----------------------------------*/
		#define De_Gps_Parse_Space_StarNumber				7										//卫星个数
		#define De_Gps_Parse_Space_Height					9
	/*++++++++++++++++++++++++++++++++++++++HardWare I/O+++++++++++++++++++++++++++++++++++++++++++++*/
		#define De_IO_Gps_Power								0x00020000 							//GPS电源
		#define De_IO_Gps_Powe_Function						PINSEL1&=0XFFFFFFF3					//选择GPIO输出
		#define De_IO_Gps_Power_Out							IODIR0|=De_IO_Gps_Power				//选择输出
		#define De_IO_Gps_Power_High						IOSET0|=De_IO_Gps_Power				//高电平
		#define De_IO_Gps_Power_Low							IOCLR0|=De_IO_Gps_Power				//低电平
	
		#define De_IO_Gps_LED								0X04000000							//GPS指示
		#define De_IO_Gps_LED_Function						PINSEL1&=0xffcfffff					//选择GPIO输出
		#define De_IO_Gps_LED_Out							IODIR0|=De_IO_Gps_LED				//
		#define De_IO_Gps_LED_High							IOSET0|=De_IO_Gps_LED				//
		#define De_IO_Gps_LED_Low							IOCLR0|=De_IO_Gps_LED				//
		
		#define GPSLED 26    	//  P0.26  LED     LED 指示灯
		#define LED_ON        IODIR0  |= (1<<GPSLED);IOCLR0 |= (1<<GPSLED)
		#define LED_OFF       IODIR0  |= (1<<GPSLED);IOSET0 |= (1<<GPSLED)		

		#define De_Gps_Power_ON								De_IO_Gps_Powe_Function;De_IO_Gps_Power_Out;De_IO_Gps_Power_High//;De_IO_Gps_LED_Function;De_IO_Gps_LED_Out;De_IO_Gps_LED_Low		
		#define De_Gps_Powe_OFF								De_IO_Gps_Powe_Function;De_IO_Gps_Power_Out;De_IO_Gps_Power_Low//;De_IO_Gps_LED_Function;De_IO_Gps_LED_Out;De_IO_Gps_LED_High																				
	#endif

/*============================================Data Define=====================================================*/
	/*++++++++++++++++++++++++++++++++++++++++数据结构定义+++++++++++++++++++++++++++++++++++++++++++*/
	#ifdef De_Gps_Compiler
		typedef struct
		{	uint8 *Gut;
			uint16 OrderNumber;
		}st_Gps_Order;											//GPS命令结构体
	#endif
	
/*============================================Static Function================================================*/
	#ifdef De_Gps_Compiler
		static uint16 Init(void);
		static uint16 Open(st_Sensor_DataPar	*ptst_Sensor_DataPar,uint8 *fd);
		static uint16 Close(uint8 fd);
		static uint16 Read(uint8 fd,void *SendBuf,void *AgreeBuf);
		static uint16 GetState(st_Sensor_State	*ptst_Sensor_State,uint8 fd);
		
		static uint16 GpsCommInput(st_Data_Gps *ptst_Data_Gps);							//GPS通讯函数入口
		static uint16 JugeOrder(uint8 *Order,uint8 *AgreeLen);
		
		static uint16 Parse_GPRMC(st_Gps_Data_GPRMC	*ptst_Gps_Data_GPRMC,uint8 *GpsBuf,uint8 SizeofGpsBuf);
		static uint16 Parse_GPRMC_GetTime(uint8 *DateTime,uint8 *GpsBuf,uint8 SizeofGpsBuf);						//获取时间
		static uint16 Parse_GPRMC_LocationTrue(uint8 *ByteV,uint8 *GpsBuf,uint8 SizeofGpsBuf); 					//定位状态
		static uint16 Parse_GPRMC_Lat(uint8 *LatHem,uint32 *Latitude,uint8 *GpsBuf,uint8 SizeofGpsBuf);			//纬度半球以及纬度值
		static uint16 Parse_GPRMC_Long(uint8 *LongHem,uint32 *Longitude,uint8 *GpsBuf,uint8 SizeofGspBuf);		//经度半球以及经度值
		static uint16 Parse_GPRMC_Speed(uint32 *Speed,uint8 *GpsBuf,uint8 SizeofGspBuf);						//速度
		static uint16 Parse_GPRMC_Angle(uint32 *Angle,uint8 *GpsBuf,uint8 SizeofGspBuf);						//速度
		
		static uint16 Parse_GPGGA(st_Gps_Data_GPGGA	*ptst_Gps_Data_GPGGA,uint8 *GpsBuf,uint8 SizeofGpsBuf);	//获取卫星的数量
		static uint16 Parse_GPGGA_StarNumber(uint8 *StarNumber,uint8 *GpsBuf,uint8 SizeofGpsBuf);
		static uint16 Parse_GPGGA_Height(int32 *Height,uint8 *GpsBuf,uint8 SizeofGpsBuf);			//获取海拔高度
					
		static uint8 *SeekChar(uint8 *Buf,uint8 CharV,uint8 SizeofBuf,uint8 Number); 
/*=============================================Public Ram=====================================================*/
		uint8 CN_Gps_Buf[De_Gps_MaxAgreeBuf];
		OS_EVENT	*GpsSem=NULL;
		uint8 CN_PowerState;
		st_Sensor_State	CN_st_Sensor_State;
		static const st_Sensor_State	CN_Ba_st_Sensor_State={De_Sensor_State_Suc,De_Sensor_Battery_State_Erro,
																De_Sensor_State_Suc};
		const st_Gps_Order	CN_st_Gps_Order[]=
		{	{"$GPGSV",De_Gps_Order_GPGSV}, 
			{"$GPGSA",De_Gps_Order_GPGSA},
			{"$GPGGA",De_Gps_Order_GPGGA}, 
			{"$GPRMC",De_Gps_Order_GPRMC}, 
			{"$GPVTG",De_Gps_Order_GPVTG}, 
			{"$GPGLL",De_Gps_Order_GPGLL},
			{"$GPZDA",De_Gps_Order_GPZDA},
			{"$GPDTM",De_Gps_Order_GPDTM}
		};//GPS命令汇总
		static const st_Fun_Sensor2Hard	CN_st_Fun_Sensor2Hard={Init,Open,Close,Read,GetState};
		static const st_Sensor_Par2Type	CN_st_Sensor_Par2Type={De_Sensor_WordPar_Gps,De_Sensor_Par_Gps};
		const st_Sensor_ParList	CN_Gps_st_Sensor_ParList=
		{	&CN_st_Fun_Sensor2Hard,&CN_st_Sensor_Par2Type,sizeof(CN_st_Sensor_Par2Type)/sizeof(st_Sensor_Par2Type)		
		};	
	#else
		extern const st_Sensor_ParList	CN_Gps_st_Sensor_ParList;
	#endif
#endif


