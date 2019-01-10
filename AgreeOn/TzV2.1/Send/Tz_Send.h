/*=========================================Include File=========================================================*/
	#include "..\..\..\APP\config.h"												//LPC2368寄存器引用
 	#include "stdlib.h"		
	#ifdef De_Tz_Send_Compiler														//C函数引用
		#include "..\..\..\miscellaneous\CodeTrans\AscNumber.h"						//引用码制转换资源
		#include "..\..\..\miscellaneous\Date\Date.h"								//引用日期资源
		#include "..\..\AgreementCom.h"												//协议数据
		#include "Tz_Send_Pubi.c"
	#endif
/*==========================================Define Data=======================================================*/
	#define De_Erro_Tz_Send_NoID								1		//不支持此协议
	#define De_Suc_Tz_Send										0		//成功
/*==========================================Data Define=======================================================*/
	typedef struct
	{	uint16 (*Write)(uint8 *Buf,void *InputBuf,uint16 *ReDataLen,uint16 ID);
	}st_Fun_Tz_Send;
#ifdef De_Tz_Send_Compiler
	typedef struct
	{	uint16 ID;
		void (*Read)(uint8 *OutBuf,void *InputBuf,uint16 *ReDataLen);
	}st_Tz_Send_FunOper;
#endif
/*=========================================static Function======================================================*/
#ifdef De_Tz_Send_Compiler	
	static uint16 Explain(uint8 *Buf,void *InputBuf,uint16 *ReDataLen,uint16 ID);
	
	/*----------------------------------------------基本协议----------------------------------------*/
	static void Explain_GetSeverComPar(uint8 *OutBuf,void *InputBuf,uint16 *ReDataLen);  //获取通讯参数指令
	//登录指令,与获取通讯参数指令一样
	//休眠指令,与获取通讯参数指令一样
	//关机指令,与获取通讯参数指令一样
	static void Explain_Answer(uint8 *OutBuf,void *InputBuf,uint16 *ReDataLen);			//定位终端命令应答
	//上传位置信息,与获取通讯参数指令一样
	static void Explain_Menum(uint8 *OutBuf,void *InputBuf,uint16 *ReDataLen);	  //上传菜单信息
	static void Explain_TxtMenum(uint8 *OutBuf,void *InputBuf,uint16 *ReDataLen);//上传带菜单的反馈信息
	static void Explain_LookPar(uint8 *OutBuf,void *InputBuf,uint16 *ReDataLen);  //查询定位终端参数
	static void Explain_UpdateSoftWare(uint8 *OutBuf,void *InputBuf,uint16 *ReDataLen);//上传软件升级状态
	static void Explain_Waring(uint8 *OutBuf,void *InputBuf,uint16 *ReDataLen);//上传报警状态
	/*---------------------------------------------功能扩展协议-----------------------------------------------------*/
	static void Explain_UploaderJpg1(uint8 *OutBuf,void *InputBuf,uint16 *ReDataLen);
	static void Explain_UploaderJpg2(uint8 *OutBuf,void *InputBuf,uint16 *ReDataLen);
	static void Explain_UploaderPar(uint8 *OutBuf,void *InputBuf,uint16 *ReDataLen);
	static void Explain_UploaderLog(uint8 *OutBuf,void *InputBuf,uint16 *ReDataLen);
	static void Explain_UpLoaderWarning(uint8 *OutBuf,void *InputBuf,uint16 *ReDataLen);

	/*-----------------------------------------------物流协议专用---------------------------------------------------*/
	static void Explain_OutRoadMap(uint8 *OutBuf,void *InputBuf,uint16 *ReDataLen);
	static void Explain_UpLoaderReduce(uint8 *OutBuf,void *InputBuf,uint16 *ReDataLen);
	static void Explain_UpLoaderDriver(uint8 *OutBuf,void *InputBuf,uint16 *ReDataLen);
	static void Explain_UpLoaderHandMess(uint8 *OutBuf,void *InputBuf,uint16 *ReDataLen);
	static void Explain_NoSem(uint8 *OutBuf,void *InputBuf,uint16 *ReDataLen);
		
	/*---------------------------------------------出租车协议-------------------------------------------------------*/ 
	static void Explain_UpLoaderFrom(uint8 *OutBuf,void *InputBuf,uint16 *ReDataLen);
	static void Explain_OverFromErro(uint8 *OutBuf,void *InputBuf,uint16 *ReDataLen);
	static void Explain_PriceData(uint8 *OutBuf,void *InputBuf,uint16 *ReDataLen);
#endif


/*===========================================Public Ram========================================================*/
#ifdef De_Tz_Send_Compiler
	static const st_Tz_Send_FunOper	CN_Ba_st_Tz_Send_FunOper[]=
	{
	/*----------------------------------------------基本协议-------------------------------------------------*/	
		{	De_Dev_Order_GetSeverComPar,Explain_GetSeverComPar},//获取服务器通讯参数
		{	De_Dev_Order_Login,Explain_GetSeverComPar},//定位终端登录
		{	De_Dev_Order_Sleep,Explain_GetSeverComPar},//定位终端休眠
		{ 	De_Dev_Order_CloseModerm,Explain_GetSeverComPar},//定位终端关机
		{ 	De_Dev_Order_Answer,Explain_Answer},//定位终端命令应答
		{	De_Dev_Order_Orientation,Explain_GetSeverComPar},//上传位置信息
		{ 	De_Dev_Order_Menum,Explain_Menum},//上传菜单信息
		{ 	De_Dev_Order_TxtMenum,Explain_TxtMenum},//上传带菜单的反馈信息
		{ 	De_Dev_Order_LookPar,Explain_LookPar},//上传定位终端参数
		{ 	De_Dev_Order_UpdateSoftWare,Explain_UpdateSoftWare},//上传软件升级状态
		{ 	De_Dev_Order_Waring,Explain_Waring},//上传报警状态
	/*---------------------------------------------功能扩展协议---------------------------------------------*/
		{ 	De_Dev_Order_UploaderJpg1,Explain_UploaderJpg1},//上传照片一
		{ 	De_Dev_Order_UploaderJpg2,Explain_UploaderJpg2},//上传照片二
//		{ 	De_Dev_Order_TabelList,Explain_TabelList},//表单
		{ 	De_Dev_Order_UploaderPar,Explain_UploaderPar},//上传参数
		{ 	De_Dev_Order_UploaderLog,Explain_NoSem},//上传日志文件
		{ 	De_Dev_Order_UpLoaderWarning,Explain_UpLoaderWarning},//上传报警参数
	/*--------------------------------------------物流协议专用----------------------------------------------*/
		{ 	De_Dev_Order_OutRoadMap,Explain_OutRoadMap},//进出区域报警
		{ 	De_Dev_Order_UpLoaderReduce,Explain_UpLoaderReduce},//上传压缩数据
		{ 	De_Dev_Order_UpLoaderDriver,Explain_UpLoaderDriver},//上传驾驶员ID
		{ 	De_Dev_Order_UpLoaderHandMess,Explain_UpLoaderHandMess},//上传手机短信
		{ 	De_Dev_Order_NoSem,Explain_NoSem},//盲区补偿信息
	/*---------------------------------------------出租车协议----------------------------------------------*/
		{ 	De_Dev_UpLoaderFrom,Explain_UpLoaderFrom},//上传订单抢答信息
		{ 	De_Dev_OverFromErro,Explain_OverFromErro},//上传订单未能完成原因
		{ 	De_Dev_PriceData,Explain_PriceData}//上传计价器信息
	};
	const st_Fun_Tz_Send	CN_st_Fun_Tz_Send={Explain};
#else
	extern const st_Fun_Tz_Send	CN_st_Fun_Tz_Send;
#endif
