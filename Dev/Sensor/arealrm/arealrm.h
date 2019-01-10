/*===========================================Include File=======================================================*/	
	#include "..\..\..\APP\config.h"
	#include "stdlib.h"
	
	#ifdef De_Arealrm_Compiler
		#include "..\..\..\miscellaneous\CodeTrans\AscNumber.h"
		#include "..\..\..\miscellaneous\Arithmetic\Arithmetic.h"	
		#include "..\..\..\HardWare\UART\UART.h"  
		#include "..\..\..\HardWare\RTC\RTC.h"  	
		#include "..\..\..\miscellaneous\Date\date.h"
		#include "..\_PuSensor.h"	  
		#include "math.h"
	#endif

	/*===========================================Define Data=======================================================*/
	#define De_Suc_Arealrm											0				//��ҳ�ɹ�

	#define De_Arealrm_State_Open									0				//�˹��ܴ�
	#define De_Arealrm_State_Close									1				//�˹��ܹر�
	
	#define De_Arealrm_Max_TypeNum									2				//���֧��2�б�����ʽ 
	#define De_Arealrm_Max_Dly									    1

	/*++++++++++++++++++++++++++++++++++++++++�������һ����++++++++++++++++++++++++++++++++++++++++++++++*/
	#define De_Erro_Arealrm_NoInit					          0xA0	              // ��ʼ��ʧ��
	#define De_Erro_Arealrm_OverMaxNumber					  De_Erro_Arealrm_NoInit+1
	#define De_Erro_Arealrm_NoWorkPar						  De_Erro_Arealrm_OverMaxNumber+1
	#define De_Erro_Arealrm_NoRead 							  De_Erro_Arealrm_NoWorkPar+1
	#define De_Erro_Arealrm_NoOpen							  De_Erro_Arealrm_NoRead+1 


	#ifdef De_Arealrm_Compiler

		#define PI         			3.1415926
		#define EARTH_RADIUS  		6378137      //����뾶 

		typedef struct
		{	st_Open_RunLen  CN_st_Arealrm_DataPar;//st_Sensor_DataPar	CN_st_Arealrm_DataPar;
			uint8 Type;
			uint8 State;
		}st_Arealrm_Par_Oper;

		typedef struct
		{	 
		    uint32 Latitude;						//γ��			����4λС��   
			uint32 Longitude;   			 		//����			����4λС��
			uint32 Speed;							//�ٶ� 			��λ�������һλС��
			uint32 Angle;							//����Ƕ�		�ȱ�  ����һλС��   
		}st_LctDat;     


		static OS_EVENT	*ArealrmSem = NULL;
		static uint8 DateTime[7];
		static st_LctDat CN_LctDat;

		static uint16 Init(void);
		static uint16 Open(st_Sensor_DataPar	*ptst_Sensor_DataPar,uint8 *fd);
		static uint16 Close(uint8 fd);
		static uint16 Read(uint8 fd,void *SendBuf,void *AgreeBuf); 		
		static uint32 GetTimeAdd(uint8 *Small,uint8 *Big);
		static float CalcMil(uint32 x1,uint32 y1,uint32 x2,uint32 y2);
		static uint8 JugeArearect(st_LctDat *pst_LctDat ,uint8 fd);
		static uint8 JugeAreacirc(st_LctDat *pst_LctDat ,uint8 fd);

		static const st_Sensor_Par2Type	CN_st_Sensor_Par2Type[]=
		{	
			{De_Sensor_WordPar_Arearect, De_Sensor_Par_Onoff},
			{De_Sensor_WordPar_AreaCirc, De_Sensor_Par_Onoff}		
		};
		static const st_Fun_Sensor2Hard	CN_st_Fun_Sensor2Hard={Init,Open,Close,Read,NULL};
			
		const st_Sensor_ParList		CN_Arealrm_st_Sensor_ParList=
		{	&CN_st_Fun_Sensor2Hard,CN_st_Sensor_Par2Type,sizeof(CN_st_Sensor_Par2Type)/sizeof(st_Sensor_Par2Type)
		};	   

		static st_Arealrm_Par_Oper	CN_st_Arealrm_Par_Oper[De_Arealrm_Max_TypeNum];
		un_OpenPar  CN_OpenPar;
	#else
		
		extern const st_Sensor_ParList	CN_Arealrm_st_Sensor_ParList;		
	#endif

