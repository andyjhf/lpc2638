#define De_UpDateSoftWare_Compiler
#include "UpDateSoftWare.h"

static uint16 Init(void)
{	//UpDateSoftWare_Q=OSMboxCreate(NULL);
	UpDateSoftWare_Q = OSQCreate(&UpDataBox[0],MAX_MESSAGES);
	if(UpDateSoftWare_Q==NULL)
		return De_Erro_UpDateSoftWare_Init;
	UpDataWaitTime=0;
	CN_st_FTP_Data.Result=0xffff;
	OSTaskCreate(Task,(void *)0, &UpDateSoftWare_Stk[De_UpDateSoftWare_Stk - 1],De_Task_Number);
	return De_Suc_UpDateSoftWare;
}
static void Task(void *pdata)
{	uint8 err;
	uint16 Result,DataLength;
	pdata=pdata;
	for(;;)
	{	
		ptst_BoxData_UpData = OSQPend(UpDateSoftWare_Q,UpDataWaitTime,&err);
		
		if(err!=OS_NO_ERR)
		{	CN_st_Fun_FTP.GetState(&CN_st_FTP_WorkState);
		}
		else	
		{	if((CN_st_FTP_Data.Result!=0xffff)&&(CN_st_FTP_Data.Result!=De_Suc_FTP))
			{	CN_st_FTP_Data.Result=0xffff;
				OSQPost(FtpQbox,&CN_st_FTP_Data);
				continue;
			}
			else if(CN_st_FTP_Data.Result==De_Suc_FTP)
			{	ptst_BoxData_UpData_Temp->Result=0;
				UpDataWaitTime=0;							  //下载完成清除延时时间，处在等待下载命令
				CN_st_FTP_Data.Result=0xffff;
				OSMboxPost(ptst_BoxData_UpData_Temp->ReBox,&ptst_BoxData_UpData_Temp->Result);
			}
			else if(CN_st_FTP_Data.Result==0xffff)
			{	if(UpDataWaitTime!=0)
				{	ptst_BoxData_UpData_Temp->Result=De_Erro_UpDateSoftWare_ReDown;
					OSMboxPost(ptst_BoxData_UpData_Temp->ReBox,&ptst_BoxData_UpData_Temp->Result);
					;				//停止下载
					;//等待停止下载
				}	
				UpDataWaitTime=100;							  //下载开始，定时查询下载进度
				ptst_BoxData_UpData_Temp=ptst_BoxData_UpData;
				CN_st_FTP_Data.Result=0xffff;
				CN_st_FTP_Data.type=De_FTP_StartCmd;
				CN_st_FTP_Data.CtrLinkIpAdd=ptst_BoxData_UpData->CN_st_Order_UpdateSoftWare.IP;
				CN_st_FTP_Data.CtrLinkPort=ptst_BoxData_UpData->CN_st_Order_UpdateSoftWare.Port;
				DataLength=CN_st_Fun_AscNumber.Strsize16(ptst_BoxData_UpData->CN_st_Order_UpdateSoftWare.Use);
				CN_st_Fun_AscNumber.MoveByte(CN_st_FTP_Data.LoginName,ptst_BoxData_UpData->CN_st_Order_UpdateSoftWare.Use,DataLength);
				DataLength=CN_st_Fun_AscNumber.Strsize16(ptst_BoxData_UpData->CN_st_Order_UpdateSoftWare.Pass);
				CN_st_Fun_AscNumber.MoveByte(CN_st_FTP_Data.LoginPassword,ptst_BoxData_UpData->CN_st_Order_UpdateSoftWare.Pass,DataLength);
				DataLength=CN_st_Fun_AscNumber.Strsize16(ptst_BoxData_UpData->CN_st_Order_UpdateSoftWare.FileName);
				CN_st_Fun_AscNumber.MoveByte(CN_st_FTP_Data.FileDirName,ptst_BoxData_UpData->CN_st_Order_UpdateSoftWare.FileName,DataLength);
				DataLength=CN_st_Fun_AscNumber.Strsize16(ptst_BoxData_UpData->CN_st_Order_UpdateSoftWare.SaveFileName);
				CN_st_Fun_AscNumber.MoveByte(CN_st_FTP_Data.SaveFileName,ptst_BoxData_UpData->CN_st_Order_UpdateSoftWare.SaveFileName,4);
				CN_st_FTP_Data.LocalBox=UpDateSoftWare_Q;//OSMboxCreate(NULL);
				OSQPost(FtpQbox,&CN_st_FTP_Data);
			}	
		}	
	}
}



