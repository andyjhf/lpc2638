#define De_AppEvent_Compiler
#include "AppEvent.h"
/*==============================================Can ���ܺ���==========================================*/
	/*+++++++++++++++++++++++++++++++++++++��ʼ������+++++++++++++++++++++++++++++++++++++++++*/
	



/*===========================================Gps ���ܺ���========================================================*/
	/*++++++++++++++++++++++++++++++++++++++++��ʼ������++++++++++++++++++++++++++++++++++++++++++++++++*/
	
/*==============================================Adc ���ܺ���====================================================*/
	/*+++++++++++++++++++++++++++++++++++++��ʼ������+++++++++++++++++++++++++++++++++++++++++++++++++*/
	
	/*-----------------------------------���ͱ�������--------------------------------------------------------*/
	
/*===========================================Sleep���ܺ���=====================================================*/
 	/*+++++++++++++++++++++++++++++++++++++��ʼ������+++++++++++++++++++++++++++++++++++++++++++++++++*/
	

/*===============================================ACC���ܺ���=====================================================*/

	

/*=========================================���Ź���=========================================================*/
	/*++++++++++++++++++++++++++++++++++++++��ʼ������+++++++++++++++++++++++++++++++++++++++++++++++*/
	void GprsInit(void)
	{ 	const st_Affair_Gprs	CN_st_Affair_Gprs={NULL,NULL,NULL,NULL,MessageSem};
		CN_st_Fun_Gprs.Open((st_Affair_Gprs	*)&CN_st_Affair_Gprs);



	}
	
	
	
	
	
/*+++++++++++++++++++++++++++++++++++++++����ʵ�ֺ���+++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/
	static void MessageSem(st_Data_Gprs   *ptst_Data_Gprs)						//���������ź�ʱ
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
	
	
	
	
	
	
	
	/*void AgreenMessage(st_Data_Gprs   *ptst_Data_Gprs)						//GSM���ܶ�������	
	{	uint16 Result;
		if(JugePhone(ptst_Data_Gprs->Phone)!=0)								//�жϵ绰�����Ƿ�Ϸ�
			goto EndAgreenMessage;		
		Result=JugeOrder(ptst_Data_Gprs->Message);
		if(Result==De_App_MessOrder_No)										//��ϵͳ��֧�ִ�����
			goto EndAgreenMessage;
		else if(Result==De_App_MessOrder_vWaring)							//���ñ�������
			Edit_CV(ptst_Data_Gprs);
		else if(Result==De_App_MessOrder_SeeParameter)						//��ѯ��������
			SeeAbout_Machi(ptst_Data_Gprs);	
		else if(Result==De_App_MessOrder_AccInit)							//ACCʱ��
			Edit_Ce(ptst_Data_Gprs);
		else if(Result==De_App_MessOrder_Lock)								//Զ�̿���
			Lock(ptst_Data_Gprs);
		else if(Result==De_App_MessOrder_unLock)							//Զ�̽���								
			unLock(ptst_Data_Gprs);
		else if(Result==De_App_MessOrder_TimerSend)							//��ʱ�ش�
			TimerSend(ptst_Data_Gprs);
		else if(Result==De_App_MessOrder_EditParameter)						//��ָ�����
				
		EndAgreenMessage:
	
	}*/	
	
	



	


