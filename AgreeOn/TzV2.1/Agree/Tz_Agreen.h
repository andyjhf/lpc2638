/*=========================================Include File=========================================================*/
	#include "..\..\..\APP\config.h"											//LPC2368寄存器引用
 	#include "stdlib.h"		
	#ifdef De_Tz_Agreen_Compiler												//C函数引用
		#include "..\..\..\miscellaneous\CodeTrans\AscNumber.h"					//引用码制转换资源
		#include "..\..\..\miscellaneous\Date\Date.h"								//引用日期资源
		#include "..\..\AgreementCom.h"												//协议数据
		#include "Tz_Agreen_Pubi.c"
	#endif
/*==========================================Define Data=======================================================*/
	#define De_Erro_Tz_Agreen_NoEdit								1		//不支持此协议
	#define De_Suc_Tz_Agreen										0		//成功
/*==========================================Data Define=======================================================*/
	typedef struct
	{	uint16 (*Read)(uint8 *Buf,void *OutBuf,uint16 DataLen,uint16 ID);
	}st_Fun_Tz_Agreen;


#ifdef De_Tz_Agreen_Compiler
	typedef struct
	{	uint16 ID;
		void (*Read)(uint8 *Buf,void *OutBuf,uint16 DataLen);
	}st_Tz_Agreen_FunOper;
#endif
/*=========================================static Function======================================================*/
#ifdef De_Tz_Agreen_Compiler	
	static uint16 Explain(uint8 *Buf,void *OutBuf,uint16 DataLen,uint16 ID);
	
	/*----------------------------------------------基本协议----------------------------------------*/
	static void Explain_Answer(uint8 *Buf,void *OutBuf,uint16 DataLen);					//中心命令应答
//	static void Explain_Orientation(uint8 *Buf,void *OutBuf,uint16 DataLen);			//定位指令
	static void Explain_Track(uint8 *Buf,void *OutBuf,uint16 DataLen);					//追踪指令
	static void Explain_SetPar(uint8 *Buf,void *OutBuf,uint16 DataLen);					//设定参数
	static void Explain_UnlockWaring(uint8 *Buf,void *OutBuf,uint16 DataLen);			//解除报警
	static void Explain_AmendMenum(uint8 *Buf,void *OutBuf,uint16 DataLen);				//修改固定菜单
	static void Explain_LoaderTxt(uint8 *Buf,void *OutBuf,uint16 DataLen);				//下发文本调度
	static void Explain_LoaderTxtMenum(uint8 *Buf,void *OutBuf,uint16 DataLen);			//下发带文本的菜单
	static void Explain_SetPhone(uint8 *Buf,void *OutBuf,uint16 DataLen);				//设置固定电话
	static void Explain_CallAnswer(uint8 *Buf,void *OutBuf,uint16 DataLen);				//通话请求
	static void Explain_UpdateSoftWare(uint8 *Buf,void *OutBuf,uint16 DataLen);			//软件升级
	static void Explain_LookPar(uint8 *Buf,void *OutBuf,uint16 DataLen);				//查询参数
	static void Explain_Contrl(uint8 *Buf,void *OutBuf,uint16 DataLen);					//远程控制
	static void Explain_ConfineCall(uint8 *Buf,void *OutBuf,uint16 DataLen);			//通话限制状态
	static void Explain_ConfigCentrSever(uint8 *Buf,void *OutBuf,uint16 DataLen);		//配置中心服务器状态
//	static void Explain_Activation(uint8 *Buf,void *OutBuf,uint16 DataLen);				//激活定位终端
/*---------------------------------------------功能扩展协议-----------------------------------------------------*/
	static void Explain_LookJpg(uint8 *Buf,void *OutBuf,uint16 DataLen);				//查询指定类型的照片
	static void Explain_JpgIng(uint8 *Buf,void *OutBuf,uint16 DataLen);					//查询实时照片
	static void Explain_SetVidType(uint8 *Buf,void *OutBuf,uint16 DataLen);				//设置拍照类型
	static void Explain_TabelList(uint8 *Buf,void *OutBuf,uint16 DataLen);				//设置表单
//	static void Explain_LookWorkPar(uint8 *Buf,void *OutBuf,uint16 DataLen);			//查询工作参数
	static void Explain_WorkParTimer(uint8 *Buf,void *OutBuf,uint16 DataLen);			//按照固定时间上传工作参数	
	static void Explain_WorkParSpace(uint8 *Buf,void *OutBuf,uint16 DataLen);		   	//按照间隔上传工作参数
	static void Explain_LookLog(uint8 *Buf,void *OutBuf,uint16 DataLen);				//查询日志文件
	static void Explain_SetWaringTerm(uint8 *Buf,void *OutBuf,uint16 DataLen);			//设置报警条件
//	static void Explain_LookWaringTerm(uint8 *Buf,void *OutBuf,uint16 DataLen);			//查询报警条件
/*-----------------------------------------------物流协议专用---------------------------------------------------*/
	static void Explain_SetRound(uint8 *Buf,void *OutBuf,uint16 DataLen);				//设置圆形路线
	static void Explain_DelRound(uint8 *Buf,void *OutBuf,uint16 DataLen);				//删除圆形路线
	static void Explain_SetRectangle(uint8 *Buf,void *OutBuf,uint16 DataLen);			//设置矩形路线
	static void Explain_DelRectangle(uint8 *Buf,void *OutBuf,uint16 DataLen);			//删除矩形路线
	static void Explain_SetPolygon(uint8 *Buf,void *OutBuf,uint16 DataLen);				//设置多边形路线
	static void Explain_DelPolygon(uint8 *Buf,void *OutBuf,uint16 DataLen);				//删除多边形路线
	static void Explain_SetRoadMap(uint8 *Buf,void *OutBuf,uint16 DataLen);				//设置路线区域
	static void Explain_DelRoadMap(uint8 *Buf,void *OutBuf,uint16 DataLen);				//删除路线区域
	static void Explain_Reduce(uint8 *Buf,void *OutBuf,uint16 DataLen);					//设置压缩回传
	static void Explain_Driver(uint8 *Buf,void *OutBuf,uint16 DataLen);					//设置驾驶员ID
	static void Explain_Navigation(uint8 *Buf,void *OutBuf,uint16 DataLen);				//中心导航
	static void Explain_HandTxt(uint8 *Buf,void *OutBuf,uint16 DataLen);				//手机文本调度
	static void Explain_HandAttemper(uint8 *Buf,void *OutBuf,uint16 DataLen);			//手机调度信息	
/*---------------------------------------------出租车协议-------------------------------------------------------*/ 
	static void Explain_AmendForm(uint8 *Buf,void *OutBuf,uint16 DataLen);				//修改订单信息
	static void Explain_UpLoaderForm(uint8 *Buf,void *OutBuf,uint16 DataLen);			//下发订单抢答信息
	static void Explain_UpLoaderFormSuc(uint8 *Buf,void *OutBuf,uint16 DataLen);		//下发订单抢答成功信息
	static void Explain_UpLoaderFormErro(uint8 *Buf,void *OutBuf,uint16 DataLen);		//下发订单抢答失败信息
	static void Explain_UpLoaderCan(uint8 *Buf,void *OutBuf,uint16 DataLen);			//下发订单取消信息
#endif


/*===========================================Public Ram========================================================*/
#ifdef De_Tz_Agreen_Compiler
	static const st_Tz_Agreen_FunOper	CN_Ba_st_Tz_Agreen_FunOper[]=
	{	{	De_Centr_Order_Answer,Explain_Answer},										//命令应答									
		{	De_Centr_Order_Orientation,NULL},											//定位指令
		{	De_Centr_Order_Track,Explain_Track},										//追踪指令
		{	De_Centr_Order_SetPar,Explain_SetPar},										//设定参数
		{	De_Centr_Order_UnlockWaring,NULL},											//解除报警
		{	De_Centr_Order_AmendMenum,Explain_AmendMenum},								//修改固定菜单
		{	De_Centr_Order_LoaderTxt,Explain_LoaderTxt},								//下发文本调度
		{	De_Centr_Order_LoaderTxtMenum,Explain_LoaderTxtMenum},						//下发带文本的菜单
		{	De_Centr_Order_SetPhone,Explain_SetPhone},									//设置固定电话
		{	De_Centr_Order_CallAnswer,Explain_CallAnswer},								//通话请求
		{	De_Centr_Order_UpdateSoftWare,Explain_UpdateSoftWare},						//软件升级
		{	De_Centr_Order_LookPar,Explain_LookPar},									//查询参数
		{	De_Centr_Order_Contrl,Explain_Contrl},										//远程控制
		{	De_Centr_Order_ConfineCall,Explain_ConfineCall},							//通话限制状态
		{	De_Centr_Order_ConfigCentrSever,Explain_ConfigCentrSever},					//配置中心服务器状态
		{	De_Centr_Order_Activation,NULL},					                    	//激活定位终端
		{	De_Centr_Order_LookJpg,Explain_LookJpg},									//查询指定类型的照片
		{	De_Centr_Order_JpgIng,Explain_JpgIng},										//查询实时照片
		{	De_Centr_Order_SetVidType,Explain_SetVidType},								//设置拍照类型
		{	De_Centr_Order_TabelList,Explain_TabelList},								//设置表单
		{	De_Centr_Order_LookWorkPar,NULL},							                //查询工作参数
		{	De_Centr_Order_WorkParTimer,Explain_WorkParTimer},							//按照固定时间上传工作参数	
		{	De_Centr_Order_WorkParSpace,Explain_WorkParSpace},							//按照间隔上传工作参数
		{	De_Centr_Order_LookLog,Explain_LookLog},									//查询日志文件
		{	De_Centr_Order_SetWaringTerm,Explain_SetWaringTerm},						//设置报警条件
		{	De_Centr_Order_LookWaringTerm,NULL},						//查询报警条件
	/*-----------------------------------------------物流协议专用---------------------------------------------------*/
		{	De_Centr_Order_SetRound,Explain_SetRound},									//设置圆形路线
		{	De_Centr_Order_DelRound,Explain_DelRound},									//删除圆形路线
		{	De_Centr_Order_SetRectangle,Explain_SetRectangle},							//设置矩形路线
		{	De_Centr_Order_DelRectangle,Explain_DelRectangle},							//删除矩形路线
		{	De_Centr_Order_SetPolygon,Explain_SetPolygon},								//设置多边形路线
		{	De_Centr_Order_DelPolygon,Explain_DelPolygon},								//删除多边形路线
		{	De_Centr_Order_SetRoadMap,Explain_SetRoadMap},								//设置路线区域
		{	De_Centr_Order_DelRoadMap,Explain_DelRoadMap},								//删除路线区域
		{	De_Centr_Order_Reduce,Explain_Reduce},										//设置压缩回传
		{	De_Centr_Order_Driver,Explain_Driver},										//设置驾驶员ID
		{	De_Centr_Order_Navigation,Explain_Navigation},								//中心导航
		{	De_Centr_Order_HandTxt,Explain_HandTxt},									//手机文本调度
		{	De_Centr_Order_HandAttemper,Explain_HandAttemper},							//手机调度信息	
	/*---------------------------------------------出租车协议-------------------------------------------------------*/ 
		{	De_Centr_Order_AmendForm,Explain_AmendForm},								//修改订单信息
		{	De_Centr_Order_UpLoaderForm,Explain_UpLoaderForm},							//下发订单抢答信息
		{	De_Centr_Order_UpLoaderFormSuc,Explain_UpLoaderFormSuc},					//下发订单抢答成功信息
		{	De_Centr_Order_UpLoaderFormErro,Explain_UpLoaderFormErro},					//下发订单抢答失败信息
		{	De_Centr_Order_UpLoaderCan,Explain_UpLoaderCan}								//下发订单取消信息
	};
	const st_Fun_Tz_Agreen	CN_st_Fun_Tz_Agreen={Explain};
#else
	extern const st_Fun_Tz_Agreen	CN_st_Fun_Tz_Agreen;
#endif
