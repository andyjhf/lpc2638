#define De_DataTrans_Compiler
#include "DataTrans.h"
/*=========================================�����������====================================================*/

/*++++++++++++++++++++++++++++++++++��ȡGPS�������Լ�ϵͳ�ĸ���״̬λ+++++++++++++++++++++++++++++++++++++++++*/
void GetGps(uint8 *Buf)
{	st_Data_Gps	CN_st_Data_Gps;
	CN_st_Control_Fun_Gps.Read(&CN_st_Data_Gps);
	Gps2CenGps(&CN_st_Data_Gps,Buf);			//��ȡGPS����
	State2CenState(Buf+18);		//Gps��״̬	 	
}
/*++++++++++++++++++++++++++++++++++++++��ʼ��ϵͳ��״̬����++++++++++++++++++++++++++++++++++++++++++++++++++++*/
void InitSytermState(void)							//��ʼ��ϵͳ״̬
{	uint16 i;
	for(i=0;i<sizeof(CN_Ba_st_Systerm_Init_State)/sizeof(st_Systerm_Init_State);i++)
		*CN_Ba_st_Systerm_Init_State[i].State=CN_Ba_st_Systerm_Init_State[i].StateVal;	
}

uint16 SendData2Gprs(uint8 fd,uint8 Answer,uint16 OrderNumber,uint16 OrderID,uint8 *Buf,uint16 SizeofBuf)  //����Ӧ��
{	st_File_Basic	CN_st_File_Basic;
	uint8 SendBuf[500];
	uint16 DataLen;
	DataLen=17+SizeofBuf;
	SendBuf[0]=(DataLen>>8);SendBuf[1]=(DataLen&0xff);					//��Ϣ����
	SendBuf[2]=De_IP_Com_AgreeOn;										//Э��汾��
	SendBuf[3]=Answer;													//Ӧ���־
	CN_st_Fun_File.ReadRecoder(CN_st_File_fd.Basicfd,0,&CN_st_File_Basic);
	CN_st_Fun_AscNumber.MoveByte(SendBuf+4,CN_st_File_Basic.IMEI,7);		//�������
	SendBuf[11]=0;SendBuf[12]=0;											//����ԴID
	SendBuf[13]=(OrderNumber>>8);SendBuf[14]=(OrderNumber&0XFF);			//�������
	SendBuf[15]=(OrderID>>8);	 SendBuf[16]=(OrderID&0xff);				//����ID
	CN_st_Fun_AscNumber.MoveByte(SendBuf+17,Buf,SizeofBuf);					//������Ϣ����
	return CN_st_Fun_Gprs.SendTCPUDP(fd,SendBuf,DataLen);							//�����ַ�
}

void  *OSMboxPend32 (OS_EVENT *pevent, uint32 timeout, uint8 *err)			//�ȴ�һ���ź��������¼����������ֽ�
{	void *Mess;
	uint16 Timer;
	for(;;)
	{	if(timeout>=0x8000)
			Timer=0x7fff;
		else
			Timer=timeout;
	   	Mess=OSMboxPend32 (pevent,timeout,err);
		if(*err==OS_NO_ERR)
			return Mess;
	}	
	return NULL;
} 
void *SendDataUDP(uint8 fd,void *Buf,uint16 SizeofBuf,uint16 *Err)			//����һ֡����ȴ�Ӧ��
{	;




}
/*========================================�ײ�֧�ֺ���==================================================*/

/*+++++++++++++++++++++++++++++++++++++++++��������Э���ȡ״̬+++++++++++++++++++++++++++++++++++++++++++++++*/
static void State2CenState(uint8 *Buf)							//ת�����ݵ�Э��
{	uint16 i;
	uint8 Point,Number;
	CN_st_Fun_AscNumber.ClsArray(Buf,4);
	for(i=0;i<sizeof(CN_Ba_st_Systerm_State)/sizeof(st_Systerm_State);i++)
	{	if(*CN_Ba_st_Systerm_State[i].State!=CN_Ba_st_Systerm_State[i].SateVal1)
			continue;
		Point=CN_Ba_st_Systerm_State[i].LocNumber/8;
		Number=(CN_Ba_st_Systerm_State[i].LocNumber&0x0007);
		Buf[Point]=((0X01)<<Number);
	}
}



 

	 