#define HandEvent_H
#ifdef HandEvent_H
/*=========================================include File===========================================================*/	
	#include "..\..\APP\config.h"
	#include "stdlib.h"
	#ifdef De_HandEvent_Compiler
		#include "..\..\Control\Hand\Hand.h"
		#include "..\..\Control\Acc\Acc.h"
		#include "..\..\Control\Gprs\GPRS.h"
		#include "..\..\Control\Gps\GpsTask.h"
		#include "..\..\miscellaneous\CodeTrans\AscNumber.h"		//引用码制转换资源
		#include "..\..\miscellaneous\Arithmetic\Arithmetic.h"
		#include "..\..\AppFunction\FilleData\FileData.h"
		#include "..\..\AppFunction\DataTrans\DataTrans.h"
		#include "..\..\File\rwFile.h"
		#include "..\..\Control\Timer\Timer.h"
		#include "..\..\Control\Can\CanTask.h"
	#endif
/*========================================Define Data=============================================================*/
	/*+++++++++++++++++++++++++++++++++++++错误代码一览表++++++++++++++++++++++++++++++++++++++++++++++++++*/ 
	

	/*+++++++++++++++++++++++++++++++++++++程序状态字+++++++++++++++++++++++++++++++++++++++++++++++++++++*/
	#define De_Hand_Order_MaxOrder					18				//命令数量
/*=========================================Data Define=+==========================================================*/
	/*+++++++++++++++++++++++++++++++++++++++数据结构体+++++++++++++++++++++++++++++++++++++++++++++++++++*/
	#ifdef De_HandEvent_Compiler
	typedef struct
	{	void (*ptFun)(uint8 *Buf,uint8 *AmendBuf,uint8 Com);
		uint8 *Gut;
		uint8 *DisDat;
	}st_Hand_Order;
	#endif
/*==========================================static Function==================================================*/
	void HandEventInit(void);
	#ifdef De_HandEvent_Compiler
//	static void SendMessegeData(st_Data_Timer	*ptst_Data_Timer,uint8 fd);
	static void SendGpsData(st_Data_Timer	*ptst_Data_Timer,uint8 fd);
	static void SendGsmData(st_Data_Timer	*ptst_Data_Timer,uint8 fd);
	static void HandAgree(uint8 *Buf,uint8 DataLen);	
	static void HandSoftEdit(uint8 *Buf,uint8 *AmendBuf,uint8 Com);
	static void CentrPhone(uint8 *Buf,uint8 *AmendBuf,uint8 Com);
	static void Control(uint8 *Buf,uint8 *AmendBuf,uint8 Com);	
	static void Power(uint8 *Buf,uint8 *AmendBuf,uint8 Com);	
	static void ControlState(uint8 *Buf,uint8 *AmendBuf,uint8 Com);
	static void AccState(uint8 *Buf,uint8 *AmendBuf,uint8 Com);	
	static void AccTimer(uint8 *Buf,uint8 *AmendBuf,uint8 Com);	
	static void MaID(uint8 *Buf,uint8 *AmendBuf,uint8 Com);
	static void MessageCentr(uint8 *Buf,uint8 *AmendBuf,uint8 Com);
	static void Par(uint8 *Buf,uint8 *AmendBuf,uint8 Com);	
	static void Can(uint8 *Buf,uint8 *AmendBuf,uint8 Com);
	static void EditCentrPhone1(uint8 *Buf,uint8 *AmendBuf,uint8 Com);
	static void EditCentrPhone2(uint8 *Buf,uint8 *AmendBuf,uint8 Com);
	static void EditCentr(uint8 *Buf,uint8 *AmendBuf,uint8 Com);
	static void Star(uint8 *Buf,uint8 *AmendBuf,uint8 Com);
	static void EditMiMA(uint8 *Buf,uint8 *AmendBuf,uint8 Com);
	static void EditMaID(uint8 *Buf,uint8 *AmendBuf,uint8 Com);
	//static void EditAccr(uint8 *Buf,uint8 *AmendBuf,uint8 Com);
	static void BackMaID(uint8 *Buf,uint8 *AmendBuf,uint8 Com);
	static uint8 Strsizeoa(uint8 *Buf);
	static uint8 *AddString(uint8 *ConstBuf,uint8 *Buf,uint8 *ReBuf,uint8 SizeofBuf,uint8 Number);

	const st_Hand_Order	CN_st_Hand_Order[De_Hand_Order_MaxOrder]=  					//命令执行
	{	
		{	HandSoftEdit,"*8000#","软件版本号:   \r        硬件版本号:   "},
		{	CentrPhone,"*8001#","一号中心:      \r二号中心:     "},
		{	Control,"*8002#","控制状态:    "},
		{	Power,"*8003#","主电源状态:   "},
		{	ControlState,"*8004#","远程控制:    "},
		{	AccState,"*8005#","Acc状态    \rAcc功能    "},
		{	AccTimer,"*8006#","Acc累计时间(s):"},
		{	MaID,"*8007#","机器编号:     "},
		{	MessageCentr,"*8008#","短信中心号码: "},
		{	Par,"*8009#","At:\rPt:\r SleepCT:\r  WtchT:\r    WN:\r Sp:"},
		{	Can,"*8010#",""},
		{	EditCentrPhone1,"*#8000*","中心1号码修改成功,号码为:"},
		{	EditCentrPhone2,"*#8001*","中心2号码修改成功,号码为:"},
		{	EditCentr,"*#8008*","短信中心号码修改成功,号码为:"},
		{	Star,"*63123456#","当前卫星个数:"},
		{	EditMiMA,"*66123456","修改密码"	},
    	{	EditMaID,"*67123456","机器编号设置成功"},
		//	{	EditAccr,"*68123456#","Acc软件状态"},
		{	BackMaID,"*69123456#","恢复出厂成功"}
	};
	const uint8 Unicom[] = 
	{
		0x28,0x63,0x31,0x29,0x28,0x56,0x34,0x29,0x28,0x50,0x31,0x31,
		0x31,0x31,0x31,0x29,0x28,0x70,0x32,0x32,0x32,0x32,0x32,0x29
	};
	const uint8 ChinaMobile[] = 
	{
		0x28,0x63,0x30,0x29,0x28,0x56,0x34,0x29,0x28,0x50,0x31,0x31,
		0x31,0x31,0x31,0x29,0x28,0x70,0x32,0x32,0x32,0x32,0x32,0x29
	};

	#endif
#endif
