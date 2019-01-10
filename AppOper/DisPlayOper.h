/*=======================================Include Define=====================================================*/
#include "..\APP\config.h"
	#include "stdlib.h"
	#ifdef De_DisPlayOper_Compiler
		#include "..\File\rwFile.h"
		#include "..\miscellaneous\CodeTrans\AscNumber.h"
		#include "..\FilleData\FileData.h"
		#include "..\FilleData\TakeData.h"
		#include "..\Control\Sensor\SensorContr.h"
		#include "..\Dev\Sensor\Sensor.h"
		#include "..\HardWare\RTC\RTC.h"
		#include "..\miscellaneous\Date\Date.h"
		#include "..\AgreeOn\TzV2.1.h"
		#include "..\AppSendAgreeOn\AppSendAgreeOn.H"
		#include "..\AppOper\AccOper.H"
		#include "..\AppOper\JugeOper.h"
		#include "..\AppTask\OpenClose\OpenAndClose.H"
		#include "..\Control\Timer\Timer.h"
		#include "..\Control\Gprs\Gprs.h"
		#include "..\Dev\Sensor\Display\Display.h"
	#endif	
/*=========================================Define Data=====================================================*/
 	#define De_Suc_DisplayOpe													0
	#define De_Erro_DisPlayOpe_Nofd												1
	#define De_Suc_Display														0
	#define De_Erro_Display														2
	#define De_st_Display_Order_SysInfor_Gps_Erro1							 	1
	#define De_st_Display_Order_SysInfor_Gps_Erro2								0
	#define De_st_Display_Order_SysInfor_Gps_Suc								2



/*==========================================Data Define========================================================*/
	typedef struct
	{	void (*Init)(void);
		void (*GetData)(void *Data,uint8 *DateTimer);
	
	}st_Fun_DisPlayOper;	
#ifdef De_DisPlayOper_Compiler
	typedef struct
	{	uint8 ID;
		void (*ptFun)(void *Data,uint8 ID);
	}st_DispLay_Oper_Fun;
	typedef struct
	{	void *Dev;
		uint16 *fd;
	}st_SeePar_Data;
#endif	
/*========================================static Function=====================================================*/
#ifdef De_DisPlayOper_Compiler
	static void Init(void);
	static void GetData(void *Data,uint8 *DateTimer);
	static void Order_Phone(void *Data,uint8 ID);
	static void SeePar(void *Data,uint8 ID);
	static void SetPar(void *Data,uint8 ID);
	static void Log(void *Data,uint8 ID);
	static void Voic(void *Data,uint8 ID);
	static void Answer(uint8 ID,uint16 Result);
	static void LCDRef(st_Data_Timer	*ptst_Data_Timer,uint8 fd) ;
	static uint16 GetCentrIP(uint32 *IP);
#endif
/*========================================Public Ram==========================================================*/
#ifdef De_DisPlayOper_Compiler	
	static const st_SeePar_Data	CN_Ba_st_SeePar_Data[]=
	{	{&((st_File_GreenPar *)(NULL))->Integral,&CN_st_File_fd.GreenParfd},
		{((st_Phone_Basic *)(NULL))->WatchPhone,&CN_st_File_fd.Phonefd},
		{((st_Phone_Basic *)(NULL))->RestPhone,&CN_st_File_fd.Phonefd},
		{((st_Message_ComPar *)(NULL))->CN_st_Message_Phone.CentrMessPhone1,&CN_st_File_fd.MessageParfd},
		{(void *)(0xffffffff),NULL},
		{((st_Gprs_ComPar *)(NULL))->CN_st_Gprs_IPNet.APN,&CN_st_File_fd.GprsParfd},
		{&((st_Gprs_ComPar *)(NULL))->CN_Mast_st_Gprs_IP.IP,&CN_st_File_fd.GprsParfd},
		{((st_Gprs_ComPar *)(NULL))->CN_Mast_st_Gprs_IP.DomainName,&CN_st_File_fd.GprsParfd},
		{&((st_Gprs_ComPar *)(NULL))->CN_Reserve_st_Gprs_IP.IP,&CN_st_File_fd.GprsParfd},
		{((st_Gprs_ComPar *)(NULL))->CN_Reserve_st_Gprs_IP.DomainName,&CN_st_File_fd.GprsParfd},
		{&((st_Gprs_ComPar *)(NULL))->CenPort,&CN_st_File_fd.GprsParfd},
		{&((st_Gprs_ComPar *)(NULL))->CN_st_Gprs_BasicPar.CentrHeart,&CN_st_File_fd.GprsParfd},
		{(void *)(0xffffffff),NULL},	  
		{((st_File_Basic	*)NULL)->MachID,&CN_st_File_fd.Basicfd},
		{&((st_File_GreenPar	*)NULL)->PassWord,&CN_st_File_fd.GreenParfd},
		{((st_File_Basic	*)NULL)->SoftEdition,&CN_st_File_fd.Basicfd},
		{(void *)(0xffffffff),NULL},
		{(void *)(0xffffffff),NULL},
		{(void *)(0xffffffff),NULL},		  
		{&((st_Parameter_Table	*)NULL)->CN_st_AgreeOn_Agree_Track.AccOpenTimer,&CN_st_File_fd.Parameterfd},
	};
	const uint16  CN_Ba_Log[]=
	{De_Display_Par_APN,De_Display_Par_MastIP,De_Display_Par_MastDomain,De_Display_Par_ReserveIP,
	 De_Display_Par_ReserveDomain,De_Display_Par_CenPort
	};
	static const st_DispLay_Oper_Fun	CN_Ba_st_DispLay_Oper_Fun[]=
	{ 	{De_Display_Device_Order_Phone,Order_Phone},
		{De_Display_Device_Order_SeePar,SeePar},
		{De_Display_Device_Order_SetPar,SetPar},
		{De_Display_Device_Order_Log,Log},
		{De_Display_Device_Order_Voic,Voic}
	};
	static const st_Affair_Timer	CN_Ba_Display=
	{ 	{5,0,{0,0,0,0,0,0,0}},
			{LCDRef}
	};
	static uint8 DisTimerfd;
	const st_Fun_DisPlayOper CN_st_Fun_DisPlayOper={Init,GetData};
#else
	extern const st_Fun_DisPlayOper CN_st_Fun_DisPlayOper;
#endif

