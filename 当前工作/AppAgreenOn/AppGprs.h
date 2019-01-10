/*=====================================Include File=========================================================*/
#include "..\APP\config.h"
#include "stdlib.h"
#ifdef De_AppGprs_Compiler
	#include "..\File\rwFile.h"
	#include "..\miscellaneous\CodeTrans\AscNumber.h"
	#include "..\FilleData\FileData.h"
	#include "..\FilleData\TakeData.h"
	#include "..\Dev\Sensor\Sensor.h"
	#include "..\AgreeOn\TzV2.1.h"
	#include "..\AppSendAgreeOn\AppSendAgreeOn.H"
	#include "..\Control\Gprs\GPRS.h"
	#include "..\Control\Timer\Timer.h"
	#include "..\AppTask\OpenClose\OpenAndClose.H"
	#include "SetPar.c"
#endif
/*=====================================Define Data==========================================================*/
	/*+++++++++++++++++++++++++++++++++错误代码一览表+++++++++++++++++++++++++++++++++++++++++++*/
	#define De_AppGprs_Answer_Suc										0				//成功
	#define De_AppGprs_Answer_Erro										1				//错误应答
	#define De_Suc_AppGprs												0				//执行成功
	#define De_Erro_AppGprs_Over										1				//

	#define De_Erro_AgreeGprs_Start										1				//本页开始错误
	#define De_Erro_AgreeGprs_DataLen									De_Erro_AgreeGprs_Start+1//长度错误
	#define De_Erro_AgreeGprs_ID										De_Erro_AgreeGprs_DataLen+1//机器编号不一致
	#define De_Erro_AgreeGprs_AgreeOn									De_Erro_AgreeGprs_ID+1	//协议版本不对
	
/*========================================Data Define=============================================================*/
	typedef struct
	{ 	void (*Read)(st_st_AgreeOn_Dev_Par	*ptst_st_AgreeOn_Dev_Par,uint8 fd);
	}st_Fun_AppGprs;
#ifdef De_AppGprs_Compiler	
	typedef struct
	{	uint16 ParID;	 												//设定参数
		void (*	Execute)(st_st_AgreeOn_Dev_Par	*ptst_st_AgreeOn_Dev_Par,uint8 fd);	//执行参数
	}st_AppGprs_Order_Set;	 											//设定参数结构体
#endif
/*=========================================Function=============================================================*/
#ifdef De_AppGprs_Compiler	
	static void AgreeData(st_st_AgreeOn_Dev_Par	*ptst_st_AgreeOn_Dev_Par,uint8 fd);
	//static void Answer(st_st_AgreeOn_Dev_Par	*ptst_st_AgreeOn_Dev_Par,uint8 fd,uint16 Result);  //正确或错误应答
	static void Orientation(st_st_AgreeOn_Dev_Par	*ptst_st_AgreeOn_Dev_Par,uint8 fd);	//发送定位指令
	static void Track(st_st_AgreeOn_Dev_Par	*ptst_st_AgreeOn_Dev_Par,uint8 fd);			//追踪指令
	static void SetPar1(st_st_AgreeOn_Dev_Par	*ptst_st_AgreeOn_Dev_Par,uint8 fd);		//设定参数
	static void UnlockWaring(st_st_AgreeOn_Dev_Par	*ptst_st_AgreeOn_Dev_Par,uint8 fd);
	static void AmendMenum(st_st_AgreeOn_Dev_Par	*ptst_st_AgreeOn_Dev_Par,uint8 fd);
	static void LoaderTxt(st_st_AgreeOn_Dev_Par	*ptst_st_AgreeOn_Dev_Par,uint8 fd);
	static void LoaderTxtMenum(st_st_AgreeOn_Dev_Par	*ptst_st_AgreeOn_Dev_Par,uint8 fd);
	static void SetPhone(st_st_AgreeOn_Dev_Par	*ptst_st_AgreeOn_Dev_Par,uint8 fd);
	static void CallAnswer(st_st_AgreeOn_Dev_Par	*ptst_st_AgreeOn_Dev_Par,uint8 fd);
	static void UpdateSoftWare(st_st_AgreeOn_Dev_Par	*ptst_st_AgreeOn_Dev_Par,uint8 fd);
	static void LookPar(st_st_AgreeOn_Dev_Par	*ptst_st_AgreeOn_Dev_Par,uint8 fd);
	static void Contrl(st_st_AgreeOn_Dev_Par	*ptst_st_AgreeOn_Dev_Par,uint8 fd);
	static void ConfineCall(st_st_AgreeOn_Dev_Par	*ptst_st_AgreeOn_Dev_Par,uint8 fd);
	static void ConfigCentrSever(st_st_AgreeOn_Dev_Par	*ptst_st_AgreeOn_Dev_Par,uint8 fd);
	static void Activation(st_st_AgreeOn_Dev_Par	*ptst_st_AgreeOn_Dev_Par,uint8 fd);
	static void LookJpg(st_st_AgreeOn_Dev_Par	*ptst_st_AgreeOn_Dev_Par,uint8 fd);
	static void JpgIng(st_st_AgreeOn_Dev_Par	*ptst_st_AgreeOn_Dev_Par,uint8 fd);
	static void SetVidType(st_st_AgreeOn_Dev_Par	*ptst_st_AgreeOn_Dev_Par,uint8 fd);
	static void TabelList(st_st_AgreeOn_Dev_Par	*ptst_st_AgreeOn_Dev_Par,uint8 fd);
	static void LookWorkPar(st_st_AgreeOn_Dev_Par	*ptst_st_AgreeOn_Dev_Par,uint8 fd);
	static void WorkParTimer(st_st_AgreeOn_Dev_Par	*ptst_st_AgreeOn_Dev_Par,uint8 fd);
	static void WorkParSpace(st_st_AgreeOn_Dev_Par	*ptst_st_AgreeOn_Dev_Par,uint8 fd);
	static void LookLog(st_st_AgreeOn_Dev_Par	*ptst_st_AgreeOn_Dev_Par,uint8 fd);
	static void SetWaringTerm(st_st_AgreeOn_Dev_Par	*ptst_st_AgreeOn_Dev_Par,uint8 fd);
	static void LookWaringTerm(st_st_AgreeOn_Dev_Par	*ptst_st_AgreeOn_Dev_Par,uint8 fd);
	static void SetRound(st_st_AgreeOn_Dev_Par	*ptst_st_AgreeOn_Dev_Par,uint8 fd);
	static void DelRound(st_st_AgreeOn_Dev_Par	*ptst_st_AgreeOn_Dev_Par,uint8 fd);
	static void SetRectangle(st_st_AgreeOn_Dev_Par	*ptst_st_AgreeOn_Dev_Par,uint8 fd);
	static void DelRectangle(st_st_AgreeOn_Dev_Par	*ptst_st_AgreeOn_Dev_Par,uint8 fd);
	static void SetPolygon(st_st_AgreeOn_Dev_Par	*ptst_st_AgreeOn_Dev_Par,uint8 fd);
	static void DelPolygon(st_st_AgreeOn_Dev_Par	*ptst_st_AgreeOn_Dev_Par,uint8 fd);
	static void SetRoadMap(st_st_AgreeOn_Dev_Par	*ptst_st_AgreeOn_Dev_Par,uint8 fd);
	static void DelRoadMap(st_st_AgreeOn_Dev_Par	*ptst_st_AgreeOn_Dev_Par,uint8 fd);
	static void Reduce(st_st_AgreeOn_Dev_Par	*ptst_st_AgreeOn_Dev_Par,uint8 fd);
	static void Driver(st_st_AgreeOn_Dev_Par	*ptst_st_AgreeOn_Dev_Par,uint8 fd);
	static void Navigation(st_st_AgreeOn_Dev_Par	*ptst_st_AgreeOn_Dev_Par,uint8 fd);
	static void HandTxt(st_st_AgreeOn_Dev_Par	*ptst_st_AgreeOn_Dev_Par,uint8 fd);
	static void HandAttemper(st_st_AgreeOn_Dev_Par	*ptst_st_AgreeOn_Dev_Par,uint8 fd);
	static void AmendForm(st_st_AgreeOn_Dev_Par	*ptst_st_AgreeOn_Dev_Par,uint8 fd);
	static void UpLoaderForm(st_st_AgreeOn_Dev_Par	*ptst_st_AgreeOn_Dev_Par,uint8 fd);
	static void UpLoaderFormSuc(st_st_AgreeOn_Dev_Par	*ptst_st_AgreeOn_Dev_Par,uint8 fd);
	static void UpLoaderFormErro(st_st_AgreeOn_Dev_Par	*ptst_st_AgreeOn_Dev_Par,uint8 fd);
	static void UpLoaderCan(st_st_AgreeOn_Dev_Par	*ptst_st_AgreeOn_Dev_Par,uint8 fd);
#endif

/*==============================================全局变量定义=====================================================*/							
#ifdef De_AppGprs_Compiler
	const st_Fun_AppGprs	CN_st_Fun_AppGprs={AgreeData};	
	static const st_AppGprs_Order_Set	CN_Ba_st_AppGprs_Order_Set[]=
	{ 	{	De_Centr_Order_Orientation,Orientation},//定位指令
		{	De_Centr_Order_Track,Track},//追踪指令
		{	De_Centr_Order_SetPar,SetPar1},//设定参数
		{	De_Centr_Order_UnlockWaring,UnlockWaring},//解除报警
		{	De_Centr_Order_AmendMenum,AmendMenum},//修改固定菜单
		{	De_Centr_Order_LoaderTxt,LoaderTxt},//下发文本调度
		{	De_Centr_Order_LoaderTxtMenum,LoaderTxtMenum},//下发带文本的菜单
		{	De_Centr_Order_SetPhone,SetPhone},//设置固定电话
		{	De_Centr_Order_CallAnswer,CallAnswer},//通话请求
		{	De_Centr_Order_UpdateSoftWare,UpdateSoftWare},//软件升级
		{	De_Centr_Order_LookPar,LookPar},//查询参数
		{	De_Centr_Order_Contrl,Contrl},//远程控制
		{	De_Centr_Order_ConfineCall,ConfineCall},//通话限制状态
		{	De_Centr_Order_ConfigCentrSever,ConfigCentrSever},//配置中心服务器状态
		{	De_Centr_Order_Activation,Activation},//激活定位终端
/*---------------------------------------------功能扩展协议-----------------------------------------------------*/
		{	De_Centr_Order_LookJpg,LookJpg},//查询指定类型的照片
		{	De_Centr_Order_JpgIng,JpgIng},//查询实时照片
		{	De_Centr_Order_SetVidType,SetVidType},//设置拍照类型
		{	De_Centr_Order_TabelList,TabelList},//设置表单
		{	De_Centr_Order_LookWorkPar,LookWorkPar},//查询工作参数
		{	De_Centr_Order_WorkParTimer,WorkParTimer},//按照固定时间上传工作参数	
		{	De_Centr_Order_WorkParSpace,WorkParSpace},//按照间隔上传工作参数
		{	De_Centr_Order_LookLog,LookLog},//查询日志文件
		{	De_Centr_Order_SetWaringTerm,SetWaringTerm},//设置报警条件
		{	De_Centr_Order_LookWaringTerm,LookWaringTerm},//查询报警条件
/*-----------------------------------------------物流协议专用---------------------------------------------------*/
		{	 De_Centr_Order_SetRound,SetRound},//设置圆形路线
		{	 De_Centr_Order_DelRound,DelRound},//删除圆形路线
		{	 De_Centr_Order_SetRectangle,SetRectangle},//设置矩形路线
		{	 De_Centr_Order_DelRectangle,DelRectangle},//删除矩形路线
		{	 De_Centr_Order_SetPolygon,SetPolygon},//设置多边形路线
		{	 De_Centr_Order_DelPolygon,DelPolygon},//删除多边形路线
		{	 De_Centr_Order_SetRoadMap,SetRoadMap},//设置路线区域
		{	 De_Centr_Order_DelRoadMap,DelRoadMap},//删除路线区域
		{	 De_Centr_Order_Reduce,Reduce},//设置压缩回传
		{	 De_Centr_Order_Driver,Driver},//设置驾驶员ID
		{	 De_Centr_Order_Navigation,Navigation},//中心导航
		{	 De_Centr_Order_HandTxt,HandTxt},//手机文本调度
		{	 De_Centr_Order_HandAttemper,HandAttemper},//手机调度信息	
/*---------------------------------------------出租车协议-------------------------------------------------------*/ 
		{		De_Centr_Order_AmendForm,AmendForm},//修改订单信息
		{	 De_Centr_Order_UpLoaderForm,UpLoaderForm},//下发订单抢答信息
		{	 De_Centr_Order_UpLoaderFormSuc,UpLoaderFormSuc},//下发订单抢答成功信息
		{	 De_Centr_Order_UpLoaderFormErro,UpLoaderFormErro},//下发订单抢答失败信息
		{	 De_Centr_Order_UpLoaderCan,UpLoaderCan}//下发订单取消信息
	};
	const uint8  CN_Ba_ChargLog[]=
	{	De_AgreeOn_SetPar_State_SetAPN,De_AgreeOn_SetPar_State_SetMastIP,De_AgreeOn_SetPar_State_SetMastDomainName,
		De_AgreeOn_SetPar_State_SetReserveIP,De_AgreeOn_SetPar_State_SetReserveDomainName,De_AgreeOn_SetPar_State_SetCenPort,
		De_AgreeOn_SetPar_State_SetUseName,De_AgreeOn_SetPar_State_SetUsePass,De_AgreeOn_SetPar_State_SetDevHeart,
		De_AgreeOn_SetPar_State_SetCentHeart,De_AgreeOn_SetPar_State_SetIPRepeat,De_AgreeOn_SetPar_State_SetIPRepeatTime		
	};
	const uint8 CN_Ba_ResetDev[]=
	{	De_AgreeOn_SetPar_State_SetParLoad,De_AgreeOn_SetPar_State_SetWireLessPar
	};		
#else
	extern const st_Fun_AppGprs	CN_st_Fun_AppGprs;
#endif
