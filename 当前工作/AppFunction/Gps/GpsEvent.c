#define De_GpsEvent_Compiler
#include "GpsEvent.h"
void GpsInit(void)
{	const st_Affair_Gps	CN_st_Affair_Gps={GpsSem,GpsNoSem,GpsErro};	
	uint8 fd;
	CN_st_Control_Fun_Gps.Open((st_Affair_Gps	*)&CN_st_Affair_Gps,&fd);			
}
/*++++++++++++++++++++++++++++++++++++++++ִ�к���+++++++++++++++++++++++++++++++++++++++++++++++++*/	
static void GpsSem(st_Data_Gps  *ptst_Data_Gps,uint8 fd)				//
{	//if(CN_st_Sys_State.GpsState==De_Erro_State_GpsNosem)
	//{	
		//CN_st_Fun_RTC.Write(ptst_Data_Gps->CN_st_Gps_Data_GPRMC.DateTime);	
	//}
	if(CN_st_Sys_State.GpsState != De_Suc_State)
		CN_st_Fun_File.WriteRecoder(CN_st_File_fd.GpsMessagefd,0,ptst_Data_Gps);
	CN_st_Sys_State.GpsState=De_Suc_State;				//״̬����
	CN_st_Sys_State.Speed=De_Suc_State;

//	if(ptst_Data_Gps->CN_st_Gps_Data_GPRMC.Speed>CN_st_Waring_Sys.Speed)//ϵͳ����
//	{	De_Erro_State_Speed;						//����	
//	 	;						/*�Ƿ�Ҫ����ϵͳ������Ϣ*/
//	}
//	else
//	{	CN_st_Sys_State.Speed=;
//	 	;						/*�����������Ժ��Ƿ�Ҫ����*/
	
//	}															
}
static void GpsNoSem(st_Data_Gps  *ptst_Data_Gps,uint8 fd)				//Gpsû���ź�
{	if(CN_st_Sys_State.GpsState == De_Suc_State)
		CN_st_Fun_File.WriteRecoder(CN_st_File_fd.GpsMessagefd,0,ptst_Data_Gps);
	CN_st_Sys_State.GpsState=De_Erro_State_GpsNosem;	
}

static void GpsErro(st_Data_Gps  *ptst_Data_Gps,uint8 fd)
{	CN_st_Sys_State.GpsState=De_Erro_State_GpsBad;
}




