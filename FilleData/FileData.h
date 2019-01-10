
/*======================================Include File============================================================*/
 	#include "..\APP\config.h"
	#include "stdlib.h"
	#include "FileInfor.h"
	#include "FileBasInfor.h"
	#ifdef De_FileData_Compiler
		#include "..\File\rwFile.h"
		#include "..\miscellaneous\CodeTrans\AscNumber.h"
		#include "..\Control\GpsAndMileage\GpsAndMileage.h"
		
	#endif
/*=======================================Define Data===========================================================*/
	#ifdef De_FileData_Compiler
		#define De_File_BackFac_Yes									1						//恢复出厂设置
		#define De_File_BackFac_No									0						//不恢复出厂设置	
	#endif
	#define De_File_Fd_Nofd											0xff					//没有这个文件
/*==========================================Data Define========================================================*/
/*-------------------------------------------输出处理结构------------------------------------------------------*/
	#ifdef De_FileData_Compiler
		typedef struct
		{	uint8 *FileName;				 //文件名称
			uint16 RecoderSize;				 //记录大小
			uint16 RecoderNumber;			 //文件记录数量
			uint32 FileSize;				 //文件大小
			uint8  Property;				 //属性		
		}st_File_Property;					//文件属性	

	 	typedef struct
		{	uint16 *fd;							   		//打开文件的ID
			const void *BackFaData;						//恢复出厂设置
			st_File_Property	CN_st_File_Property;
			uint8  SelectFac;							//是否恢复出厂设置
		}st_File_fd_Tabel;								//文件信息表
	#endif
	/*+++++++++++++++++++++++++++++++++++++++各个文件打开全局ID++++++++++++++++++++++++++++++++++++++++++++*/
	typedef struct
	{	uint16 Basicfd;					//文件基本信息表   1
		uint16 Driverfd;				//驾驶员基本信息   2
		uint16 GreenParfd;				//界面类参数	   3
		uint16 WorkParfd;				//工作参数		   4
		uint16 Parameterfd; 			//参数			   5
		uint16 GprsParfd;				//GPRS参数		   6
	  	uint16 MessageParfd;			//信息参数		   7
		uint16 Phonefd;					//电话参数		   8
		uint16 Rootfd;					//固定电话信息	   9
		uint16 AccTimerfd;			   	//统计			   10
		uint16 Gpsfd;					//GPS信息保存	   11
		uint16 Menumfd;					//菜单			   12
		uint16 Workfd;					//工作流水		   13
		uint16 Reducefd;				//压缩数据回传	   14
		uint16 NoFlowfd;			 	//盲区补偿		   15
		uint16 Sendfd;					//发送数据		   16
		uint16 Photofd;					//照片大小		   17
		uint16 PhotoDatafd;				//照片FD		   18
	   	uint16 WaringStatefd;			//工作参数报警状态 19
		uint16 WaringTermfd;			//报警参数		   20
		uint16 VidTermfd;				//拍照			   21
		uint16 Areafd;					//区域FD		   22
		uint16 Roundfd;	   				//圆形区域		   23
		uint16 Rectanglefd;				//矩形区域		   24
		uint16 WorkParTimerfd;			//固定时间点	   25
	}st_File_fd;						//各个文件	
/*==============================================函数定义======================================================*/
	void FileData_BackSet(void);
	void FileData_CheckFile(void);
	#ifdef De_FileData_Compiler
		static void BackFacFile(st_File_fd_Tabel	*ptst_File_fd_Tabel);
	#endif		
/*=======================================全局变量定义=========================================================*/
	#ifdef De_FileData_Compiler
		st_File_fd	CN_st_File_fd;
	/*-------------------------------------------文件系统结构体-------------------------------------------------------*/
		const st_File_fd_Tabel	CN_Ba_st_File_fd_Tabel[]=  				//本应用程序所创建的文件属性
		{	{&CN_st_File_fd.Basicfd,&CN_Ba_st_File_Basic,{"Basic",sizeof(st_File_Basic),1,0,De_File_Property_Cycle},De_File_BackFac_No},//文件基本信息表		
			{&CN_st_File_fd.Driverfd,NULL,{"Driver",sizeof(st_AgreeOn_Driver),1,0,De_File_Property_Cycle},De_File_BackFac_Yes},//驾驶员基本信息表
		   	{&CN_st_File_fd.GreenParfd,&CN_Ba_st_File_GreenPar,{"GrePar",sizeof(st_File_GreenPar),1,0,De_File_Property_Cycle},De_File_BackFac_Yes},//界面类文字
		 	{&CN_st_File_fd.WorkParfd,&CN_Ba_st_File_WorkPar,{"WorkPar",sizeof(st_File_WorkPar),1,0,De_File_Property_Cycle},De_File_BackFac_Yes},	//工作参数
			{&CN_st_File_fd.Parameterfd,&CN_Ba_st_Parameter_Table,{"parame",sizeof(st_Parameter_Table),1,0,De_File_Property_Cycle},De_File_BackFac_Yes},//参数表
			{&CN_st_File_fd.GprsParfd,&CN_Ba_st_Gprs_ComPar,{"IPPar",sizeof(st_Gprs_ComPar),1,0,De_File_Property_Cycle},De_File_BackFac_Yes},	 //IP通讯方式下参数
			{&CN_st_File_fd.MessageParfd,&CN_Ba_st_Message_ComPar,{"MesPar",sizeof(st_Message_ComPar),1,0,De_File_Property_Cycle},De_File_BackFac_Yes},//Message方式下的通讯参数
			{&CN_st_File_fd.Phonefd,&CN_Ba_st_Phone_Basic,{"Phone",sizeof(st_Phone_Basic),1,0,De_File_Property_Cycle},De_File_BackFac_Yes},	//电话类参数表
			{&CN_st_File_fd.Rootfd,&CN_Ba_st_Phone_Root,{"RoPhone",sizeof(st_AgreeOn_Phone_Par),10,0,De_File_Property_Recoder},De_File_BackFac_Yes}, //固定电话号码
			{&CN_st_File_fd.AccTimerfd,&CN_Ba_st_AccTimer,{"AccTimer",sizeof(st_AccTimer),1,0,De_File_Property_Cycle},De_File_BackFac_Yes},//ACC时间统计
			{&CN_st_File_fd.Gpsfd,NULL,{"Gps",sizeof(st_File_Gps),1,0,De_File_Property_Cycle},De_File_BackFac_No},				//GPS数据保存
			{&CN_st_File_fd.Menumfd,&CN_Ba_st_File_Menum,{"Menum",sizeof(st_File_Menum),128,0,De_File_Property_Recoder},De_File_BackFac_Yes},
			{&CN_st_File_fd.Workfd,NULL,{"Flow",sizeof(st_WorkFlow_Table),20000,0,De_File_Property_Cycle},De_File_BackFac_No},		//工作参数保存		
			{&CN_st_File_fd.Reducefd,NULL,{"Reduce",sizeof(st_Reduce_Table),1,0,De_File_Property_Cycle}, De_File_BackFac_No},
			{&CN_st_File_fd.NoFlowfd,NULL,{"Nosem",sizeof(st_NoFlow_Table),20000,0,De_File_Property_Cycle},De_File_BackFac_No},
			{&CN_st_File_fd.Sendfd,NULL,{"Send",sizeof(st_Send_Table),1,0,De_File_Property_Cycle},De_File_BackFac_No},
			{&CN_st_File_fd.Photofd,NULL,{"Photo",sizeof(st_File_Photo_Tail),1000,0,De_File_Property_Cycle},De_File_BackFac_No},
			{&CN_st_File_fd.PhotoDatafd,NULL,{"PhoDa",sizeof(st_File_Photo_Data),10000,0,De_File_Property_Cycle},De_File_BackFac_No},
			{&CN_st_File_fd.WaringStatefd,NULL,{"WarState",sizeof(st_Warning_State_Table),1,0,De_File_Property_Cycle},De_File_BackFac_No},
			{&CN_st_File_fd.WaringTermfd,NULL,{"WarPar",sizeof(st_AgreeOn_SetVidType),1,0,De_File_Property_Cycle},De_File_BackFac_No},
			{&CN_st_File_fd.VidTermfd,NULL,{"WarVid",sizeof(st_AgreeOn_SetVidType),1,0,De_File_Property_Cycle},De_File_BackFac_No},
			{&CN_st_File_fd.Areafd,NULL,{"Area",sizeof(st_Area_Infor_Table),1,0,De_File_Property_Cycle},De_File_BackFac_No},
			{&CN_st_File_fd.Roundfd,NULL,{"Round",sizeof(st_AgreeOn_SetRound_Par),50,0,De_File_Property_Cycle},De_File_BackFac_No},
			{&CN_st_File_fd.Rectanglefd,NULL,{"Rectang",sizeof(st_AgreeOn_SetRectangle_Par),50,0,De_File_Property_Cycle},De_File_BackFac_No},	
			{&CN_st_File_fd.WorkParTimerfd,NULL,{"ParTimer",sizeof(st_AgreeOn_WorkParTimer),1,0,De_File_Property_Cycle},De_File_BackFac_No}
			//{&CN_st_File_fd.DrivLogFd,NULL,{"DriLog",sizeof(st_Driver_Log_Table),1,0,De_File_Property_Cycle},De_File_BackFac_No}
			
			
		
		};	
		st_WorkFlow_Table	App_CN_st_WorkFlow_Table;	
	/*------------------------------------系统状态-------------------------------------------------------*/
	#else
		extern st_File_fd	CN_st_File_fd;
		extern st_WorkFlow_Table App_CN_st_WorkFlow_Table;	
	#endif

