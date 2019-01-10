#define De_AppEvent_Compiler
#include "AppEvent.h"
/*==============================================Can 功能函数==========================================*/
	/*+++++++++++++++++++++++++++++++++++++初始化函数+++++++++++++++++++++++++++++++++++++++++*/
	



/*===========================================Gps 功能函数========================================================*/
	/*++++++++++++++++++++++++++++++++++++++++初始化函数++++++++++++++++++++++++++++++++++++++++++++++++*/
	
/*==============================================Adc 功能函数====================================================*/
	/*+++++++++++++++++++++++++++++++++++++初始化函数+++++++++++++++++++++++++++++++++++++++++++++++++*/
	
	/*-----------------------------------发送报警数据--------------------------------------------------------*/
	
/*===========================================Sleep功能函数=====================================================*/
 	/*+++++++++++++++++++++++++++++++++++++初始化函数+++++++++++++++++++++++++++++++++++++++++++++++++*/
	

/*===============================================ACC功能函数=====================================================*/

	

/*=========================================短信功能=========================================================*/
	/*++++++++++++++++++++++++++++++++++++++初始化函数+++++++++++++++++++++++++++++++++++++++++++++++*/
	void GprsInit(void)
	{ 	const st_Affair_Gprs	CN_st_Affair_Gprs={NULL,NULL,NULL,NULL,MessageSem};
		CN_st_Fun_Gprs.Open((st_Affair_Gprs	*)&CN_st_Affair_Gprs);



	}
	
	
	
	
	
/*+++++++++++++++++++++++++++++++++++++++具体实现函数+++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/
	static void MessageSem(st_Data_Gprs   *ptst_Data_Gprs)						//当机器有信号时
	{	st_File_Message	CN_st_File_Message;
		uint16 Number,NumberAll;
		for(;;)
		{	if((MessageTail-1)==MessageSendSpace)
				break;
			else if((MessageTail-1)>MessageSendSpace)
				Number=MessageTail-1-MessageSendSpace;
			else
				Number=MessageTail+MessageNumber-1;
			NumberAll=CN_st_Fun_File.GetJlNum(MessageFileFd);
			Number=NumberAll+1-Number;
			CN_st_Fun_File.ReadRecoder(MessageFileFd,Number,&CN_st_File_Message);
			CN_st_Fun_Gprs.SendMessage(CN_st_File_Message.Message,CN_st_File_Message.Phone);				 	
			MessageSendSpace++;
			if(MessageSendSpace==MessageNumber)
				MessageSendSpace=0;
		    CN_st_Fun_File.WriteRecoder(MessageSendFileFd,0,&MessageSendSpace);
		}
	}	
	
	
	
	
	
	
	
	/*void AgreenMessage(st_Data_Gprs   *ptst_Data_Gprs)						//GSM接受短信命令	
	{	uint16 Result;
		if(JugePhone(ptst_Data_Gprs->Phone)!=0)								//判断电话号码是否合法
			goto EndAgreenMessage;		
		Result=JugeOrder(ptst_Data_Gprs->Message);
		if(Result==De_App_MessOrder_No)										//本系统不支持此命令
			goto EndAgreenMessage;
		else if(Result==De_App_MessOrder_vWaring)							//设置报警数据
			Edit_CV(ptst_Data_Gprs);
		else if(Result==De_App_MessOrder_SeeParameter)						//查询车机参数
			SeeAbout_Machi(ptst_Data_Gprs);	
		else if(Result==De_App_MessOrder_AccInit)							//ACC时间
			Edit_Ce(ptst_Data_Gprs);
		else if(Result==De_App_MessOrder_Lock)								//远程控制
			Lock(ptst_Data_Gprs);
		else if(Result==De_App_MessOrder_unLock)							//远程解锁								
			unLock(ptst_Data_Gprs);
		else if(Result==De_App_MessOrder_TimerSend)							//定时回传
			TimerSend(ptst_Data_Gprs);
		else if(Result==De_App_MessOrder_EditParameter)						//按指令更改
				
		EndAgreenMessage:
	
	}*/	
	
	



	


