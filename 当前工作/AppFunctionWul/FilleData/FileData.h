/*======================================Include File============================================================*/
 	#include "..\..\APP\config.h"
	#include "stdlib.h"
	#ifdef De_FileData_Compiler
		#include "..\..\File\rwFile.h"
		#include "..\..\miscellaneous\CodeTrans\AscNumber.h"
		#include "FileInfor.h"
		#include "FileBasInfor.h"
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
	{	uint16 Basicfd;					//基本信息
		uint16 Parameterfd; 			//参数
	  	uint16 Phonefd;					//电话参数
		uint16 MessageParfd;			//信息参数
		uint16 GprsParfd;				//GPRS参数
		uint16 GreenParfd;				//界面类参数
		uint16 Accfd;					//设置ACC与里程统计
		uint16 Driverfd;				//驾驶员基本信息
		uint16 AccTimerfd;			   	//ACC里程统计
		uint16 Rootfd;					//固定电话信息
		uint16 Gpsfd;					//GPS信息保存
		uint16 Workfd;					//工作参数
		uint16 Menumfd;					//菜单
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
			{&CN_st_File_fd.Driverfd,&CN_Ba_st_Emplo_Basic,{"Driver",sizeof(st_Emplo_Basic),100,0,De_File_Property_Recoder},De_File_BackFac_Yes},//驾驶员基本信息表
		   	{&CN_st_File_fd.GreenParfd,&CN_Ba_st_File_GreenPar,{"GrePar",sizeof(st_File_GreenPar),1,0,De_File_Property_Cycle},De_File_BackFac_Yes},//界面类文字
		 	{&CN_st_File_fd.Parameterfd,&CN_Ba_st_Parameter_Table,{"parame",sizeof(st_Parameter_Table),1,0,De_File_Property_Cycle},De_File_BackFac_Yes},//参数表
			{&CN_st_File_fd.GprsParfd,&CN_Ba_st_Gprs_ComPar,{"IPPar",sizeof(st_Gprs_ComPar),1,0,De_File_Property_Cycle},De_File_BackFac_Yes},	 //IP通讯方式下参数
			{&CN_st_File_fd.MessageParfd,&CN_Ba_st_Message_ComPar,{"MesPar",sizeof(st_Message_ComPar),1,0,De_File_Property_Cycle},De_File_BackFac_Yes},//Message方式下的通讯参数
			{&CN_st_File_fd.Phonefd,&CN_Ba_st_Phone_Basic,{"Phone",sizeof(st_Phone_Basic),1,0,De_File_Property_Cycle},De_File_BackFac_Yes},	//电话类参数表
			{&CN_st_File_fd.Rootfd,&CN_Ba_st_Phone_Root,{"RoPhone",sizeof(st_Phone_Root),1,0,De_File_Property_Cycle},De_File_BackFac_Yes}, //固定电话号码
			{&CN_st_File_fd.AccTimerfd,&CN_Ba_st_AccTimer,{"AccTimer",sizeof(st_AccTimer),1,0,De_File_Property_Cycle},De_File_BackFac_Yes},//ACC时间统计
			{&CN_st_File_fd.Gpsfd,NULL,{"Gps",sizeof(st_File_Gps),1,0,De_File_Property_Cycle},De_File_BackFac_No},				//GPS数据保存
			{&CN_st_File_fd.Menumfd,&CN_Ba_st_File_Menum,{"Menum",sizeof(st_File_Menum),128,0,De_File_Property_Recoder}},
			{&CN_st_File_fd.Workfd,NULL,{"Flow",sizeof(st_WorkFlow_Table),10000,0,De_File_Property_Cycle},De_File_BackFac_No}		//工作参数保存		
		};							//本应用程序所用文件表
	/*------------------------------------系统状态-------------------------------------------------------*/
	#else
		extern st_File_fd	CN_st_File_fd;
	#endif