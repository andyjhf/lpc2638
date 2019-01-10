#define De_HandEvent_Compiler
#include "HandEvent.h"
#include "..\..\HardWare\UART\UART.h"
void HandEventInit(void)
{	const st_Affair_Hand	CN_st_Affair_Hand={HandAgree};
	const st_Affair_Timer	CN_Gsm_st_Affair_Timer=
		{		{5,0},									
				{SendGsmData}
		};
    const st_Affair_Timer	CN_Gps_st_Affair_Timer=
		{		{5,0},									
				{SendGpsData}
		};
//	const st_Affair_Timer	CN_Messege_st_Affair_Timer=
//		{		{15,0},									
//				{SendMessegeData}
//		};
   	CN_st_Fun_Hand.Open((st_Affair_Hand	*)&CN_st_Affair_Hand);
	if(CN_st_Sys_Event.HandfdGsm!=De_Event_No)
		CN_st_Fun_Timer.Close(CN_st_Sys_Event.HandfdGsm);
	if(CN_st_Sys_Event.HandfdGps!=De_Event_No)
		CN_st_Fun_Timer.Close(CN_st_Sys_Event.HandfdGps);
	CN_st_Fun_Timer.Open((st_Affair_Timer	*)&CN_Gsm_st_Affair_Timer,&CN_st_Sys_Event.HandfdGsm);
	CN_st_Fun_Timer.Enable(CN_st_Sys_Event.HandfdGsm);
	CN_st_Fun_Timer.Open((st_Affair_Timer	*)&CN_Gps_st_Affair_Timer,&CN_st_Sys_Event.HandfdGps);
	CN_st_Fun_Timer.Enable(CN_st_Sys_Event.HandfdGps);
//	CN_st_Fun_Timer.Open((st_Affair_Timer	*)&CN_Messege_st_Affair_Timer,&CN_st_Sys_Event.HandfdMessege);
//	CN_st_Fun_Timer.Enable(CN_st_Sys_Event.HandfdMessege);
}
//static void SendMessegeData(st_Data_Timer	*ptst_Data_Timer,uint8 fd)
//{	uint8 Messege[300],Phone[15];
//	uint16 DataLength,DataLength1;
//	CN_st_Fun_Timer.DisEnable(CN_st_Sys_Event.HandfdMessege);
//	CN_st_Fun_AscNumber.ClsArray(Messege,sizeof(Messege));
//	CN_st_Fun_AscNumber.ClsArray(Phone,sizeof(Phone));
//	CN_st_Fun_AscNumber.MoveByte(Messege,"新短信:",7);
//	if(CN_st_Fun_Gprs.ReadMessage(Messege+7,Phone)==De_Erro_MODEL_NoSms)
//	{	CN_st_Fun_Timer.Enable(CN_st_Sys_Event.HandfdMessege);
//		CN_st_Fun_Uart.Write(0,"NoSms\r\n",7);
//		return;
//	}
//	CN_st_Fun_Uart.Write(0,"Sms\r\n",5);
//	DataLength = CN_st_Fun_AscNumber.Strsize16(Messege);
//	DataLength1= CN_st_Fun_AscNumber.Strsize16(Phone);
//	CN_st_Fun_AscNumber.MoveByte(Messege+DataLength,"号码:",5);
//	CN_st_Fun_AscNumber.MoveByte(Messege+DataLength+5,Phone,DataLength1);
//
//	CN_st_Fun_Hand.LCDputLine(Messege);
//	CN_st_Fun_Timer.Enable(CN_st_Sys_Event.HandfdMessege);
//}
static void SendGsmData(st_Data_Timer	*ptst_Data_Timer,uint8 fd) 		//发送GSM
{	st_Gsm_Net_Information	CN_st_Gsm_Net_Information;
	uint8 Dat[3];							//
	CN_st_Fun_Gprs.GetPro(&CN_st_Gsm_Net_Information);
	Dat[0]=CN_st_Fun_AscNumber.GetCsq(CN_st_Gsm_Net_Information.Csq);
	Dat[1]=0x30;
	Dat[2]=0x31;					//猜测可能是新短消息提示，不知道是否是真的
  	CN_st_Fun_Hand.GsmLine(Dat,3);
}



static void SendGpsData(st_Data_Timer	*ptst_Data_Timer,uint8 fd)					//定时发送GPS数据
{	uint8 Buf[100];
	CN_st_Fun_AscNumber.ClsArray(Buf,sizeof(Buf));
	Get_Gps_DataHand(Buf);
	CN_st_Fun_Hand.GpsLine(Buf,CN_st_Fun_AscNumber.Strsize(Buf));
}



static void HandAgree(uint8 *Buf,uint8 DataLen)
{	uint8 ShowBuf[200];		
	st_Gsm_Net_Information	CN_st_Gsm_Net_Information;
//	st_Fun_Hand CN_st_Fun_Hand;
	uint8 i;
	//if((DataLen==0)||CN_st_Fun_Arithmetic.ptst_Fun_CheckSum->CheckSum(Buf,DataLen-1)!=Buf[DataLen-1])
	//CN_st_Fun_Hand.LCDputLine("校验错误");
      // else
	//CN_st_Fun_Uart.Write(3,0x00,1);	
		if(Buf[0]==0)						//登录命令
		{	CN_st_Fun_Gprs.GetPro(&CN_st_Gsm_Net_Information);
			
			if(CN_st_Gsm_Net_Information.Yys==De_Moderm_ChinaMobile)			//中国移动
				CN_st_Fun_Hand.RegLine((uint8 *)ChinaMobile,sizeof(ChinaMobile));	
			else	  															//中国联通
				CN_st_Fun_Hand.RegLine((uint8 *)Unicom,sizeof(Unicom));	
		}
		else if(Buf[0]==5)
		{	Buf++;
		    									  
			for(i=0;i<De_Hand_Order_MaxOrder;i++)	
			{	if(CN_st_Fun_AscNumber.CompareBuf(Buf,CN_st_Hand_Order[i].Gut,CN_st_Fun_AscNumber.Strsize(CN_st_Hand_Order[i].Gut))==0)
			 	{	CN_st_Fun_AscNumber.ClsArray(ShowBuf,sizeof(ShowBuf));
					CN_st_Hand_Order[i].ptFun(ShowBuf,Buf,i);
				//	CN_st_Fun_Hand.DisEnable();
					//CN_st_Fun_AscNumber.ClsArray(ptUart3ReBuf,1024);
				}	
			}
		}

				
}
/*=========================================底层运行函数=========================================================*/
static void HandSoftEdit(uint8 *Buf,uint8 *AmendBuf,uint8 Com)
{	st_File_Basic	CN_st_File_Basic;
	uint8 *pBuf;
	CN_st_Fun_File.ReadRecoder(CN_st_File_fd.Basicfd,0,&CN_st_File_Basic);
	pBuf=AddString(CN_st_Hand_Order[Com].DisDat,CN_st_File_Basic.SoftEdition,Buf,8,0);
	AddString(CN_st_Hand_Order[Com].DisDat,CN_st_File_Basic.HardEdition,pBuf,8,1);
	CN_st_Fun_Hand.LCDputLine(Buf);
}
static void CentrPhone(uint8 *Buf,uint8 *AmendBuf,uint8 Com)
{	st_File_Parameter	CN_st_File_Parameter;
	uint8 *pBuf;
	CN_st_Fun_File.ReadRecoder(CN_st_File_fd.Parameterfd,0,&CN_st_File_Parameter);
	pBuf=AddString(CN_st_Hand_Order[Com].DisDat,CN_st_File_Parameter.CenterPhone1,Buf,15,0);
	AddString(CN_st_Hand_Order[Com].DisDat,CN_st_File_Parameter.CenterPhone2,pBuf,15,1);
	CN_st_Fun_Hand.LCDputLine(Buf);
}
static void Control(uint8 *Buf,uint8 *AmendBuf,uint8 Com)
{	st_File_Parameter	CN_st_File_Parameter;
	CN_st_Fun_File.ReadRecoder(CN_st_File_fd.Parameterfd,0,&CN_st_File_Parameter);
	if(CN_st_File_Parameter.ControlEnable==0)
		AddString(CN_st_Hand_Order[Com].DisDat,(uint8 *)"非执行状态",Buf,10,0);
	else 
		AddString(CN_st_Hand_Order[Com].DisDat,(uint8 *)"执行状态",Buf,8,0);				
   	CN_st_Fun_Hand.LCDputLine(Buf);
}
static void Power(uint8 *Buf,uint8 *AmendBuf,uint8 Com)
{	if(CN_st_Sys_State.voltage==De_Suc_State)
		AddString(CN_st_Hand_Order[Com].DisDat,(uint8 *)"正常",Buf,4,0);
	else
		AddString(CN_st_Hand_Order[Com].DisDat,(uint8 *)"报警",Buf,4,0);
	CN_st_Fun_Hand.LCDputLine(Buf);				
}
static void ControlState(uint8 *Buf,uint8 *AmendBuf,uint8 Com)
{	st_File_Parameter	CN_st_File_Parameter;
	CN_st_Fun_File.ReadRecoder(CN_st_File_fd.Parameterfd,0,&CN_st_File_Parameter);
	if(CN_st_File_Parameter.ControlEnable==0)		//解除
	{
		CN_st_File_Parameter.ControlEnable=De_State_Control;
		CN_st_Fun_File.WriteRecoder(CN_st_File_fd.Parameterfd,0,&CN_st_File_Parameter);
		CN_st_Sys_State.Control=CN_st_File_Parameter.ControlEnable;	
		De_IO_Lock;	
		AddString(CN_st_Hand_Order[Com].DisDat,(uint8 *)"执行状态",Buf,10,0);
	}
	else 			//锁车
	{
		CN_st_File_Parameter.ControlEnable=De_State_NoControl;
		CN_st_Fun_File.WriteRecoder(CN_st_File_fd.Parameterfd,0,&CN_st_File_Parameter);
		CN_st_Sys_State.Control=CN_st_File_Parameter.ControlEnable;	
		De_IO_unLock;	
		AddString(CN_st_Hand_Order[Com].DisDat,(uint8 *)"非执行状态",Buf,8,0);				
	}
   	CN_st_Fun_Hand.LCDputLine(Buf);
} 

static void AccState(uint8 *Buf,uint8 *AmendBuf,uint8 Com)
{	st_File_Parameter	CN_st_File_Parameter;
  	st_Data_Acc			CN_st_Data_Acc;
	uint8 *pBuf;
	CN_st_Fun_File.ReadRecoder(CN_st_File_fd.Parameterfd,0,&CN_st_File_Parameter);
	CN_st_Fun_Acc.Read(&CN_st_Data_Acc);
	if(CN_st_Data_Acc.AccState==De_Acc_High)		//ACC状态打开
		pBuf=AddString(CN_st_Hand_Order[Com].DisDat,(uint8 *)"开",Buf,2,0);
	else 
		pBuf=AddString(CN_st_Hand_Order[Com].DisDat,(uint8 *)"关",Buf,2,0);
	if(CN_st_File_Parameter.AccFun==0)
		AddString(CN_st_Hand_Order[Com].DisDat,(uint8 *)"开",pBuf,2,1);					
	else 
		AddString(CN_st_Hand_Order[Com].DisDat,(uint8 *)"关",pBuf,2,1);
  	CN_st_Fun_Hand.LCDputLine(Buf);
}

static void AccTimer(uint8 *Buf,uint8 *AmendBuf,uint8 Com)
{				
  	CN_st_Fun_Hand.LCDputLine(Buf);
}

static void MaID(uint8 *Buf,uint8 *AmendBuf,uint8 Com)
{	st_File_Basic	CN_st_File_Basic;
	CN_st_Fun_File.ReadRecoder(CN_st_File_fd.Basicfd,0,&CN_st_File_Basic);
  	AddString(CN_st_Hand_Order[Com].DisDat,CN_st_File_Basic.MachID,Buf,16,0);
   	CN_st_Fun_Hand.LCDputLine(Buf);
}
static void MessageCentr(uint8 *Buf,uint8 *AmendBuf,uint8 Com)
{ 	st_File_Parameter	CN_st_File_Parameter;
//	uint8 *pBuf;
	CN_st_Fun_File.ReadRecoder(CN_st_File_fd.Parameterfd,0,&CN_st_File_Parameter);
//	AddString(CN_st_Hand_Order[Com].DisDat,CN_st_File_Parameter.CenterNum,pBuf,15,0);
//	CN_st_Fun_Hand.LCDputLine(Buf);
//	st_Gsm_Net_Information	CN_st_Gsm_Net_Information;
//	CN_st_Fun_Gprs.GetPro(&CN_st_Gsm_Net_Information);
	AddString(CN_st_Hand_Order[Com].DisDat,CN_st_File_Parameter.CenPhone,Buf,15,0);
 		CN_st_Fun_Hand.LCDputLine(Buf);
 }
static void Par(uint8 *Buf,uint8 *AmendBuf,uint8 Com)
{	st_File_Parameter	CN_st_File_Parameter;
	st_File_UpLoader	CN_st_File_UpLoader;
	uint8 Asc[10];
	uint8 Number=0;
	uint8 *pBuf;
	CN_st_Fun_File.ReadRecoder(CN_st_File_fd.Parameterfd,0,&CN_st_File_Parameter);
	CN_st_Fun_File.ReadRecoder(CN_st_File_fd.UpLoaderfd,0,&CN_st_File_UpLoader);
	CN_st_Fun_AscNumber.ClsArray(Asc,sizeof(Asc));
	CN_st_Fun_AscNumber.Algorism2Asc(CN_st_File_Parameter.SleepTimer,Asc);
	pBuf=AddString(CN_st_Hand_Order[Com].DisDat,Asc,Buf,sizeof(Asc),0);

	CN_st_Fun_AscNumber.ClsArray(Asc,sizeof(Asc));
	CN_st_File_Parameter.WorkCheckTimer = CN_st_File_Parameter.WorkCheckTimer/60;
	CN_st_Fun_AscNumber.Algorism2Asc(CN_st_File_Parameter.WorkCheckTimer,Asc);
	pBuf=AddString(CN_st_Hand_Order[Com].DisDat,Asc,pBuf,sizeof(Asc),1);

	CN_st_Fun_AscNumber.ClsArray(Asc,sizeof(Asc));
	CN_st_File_Parameter.SleepCheckTimer = CN_st_File_Parameter.SleepCheckTimer/60;
	CN_st_Fun_AscNumber.Algorism2Asc(CN_st_File_Parameter.SleepCheckTimer,Asc);
	pBuf=AddString(CN_st_Hand_Order[Com].DisDat,Asc,pBuf,sizeof(Asc),2);

	CN_st_Fun_AscNumber.ClsArray(Asc,sizeof(Asc));
	CN_st_Fun_AscNumber.Algorism2Asc(CN_st_File_UpLoader.Timer,Asc);
	pBuf=AddString(CN_st_Hand_Order[Com].DisDat,Asc,pBuf,sizeof(Asc),3);

	CN_st_Fun_AscNumber.ClsArray(Asc,sizeof(Asc));
	Number = CN_st_File_UpLoader.Number-CN_st_File_UpLoader.NonceNumber;
	CN_st_Fun_AscNumber.Algorism2Asc(Number,Asc);
	pBuf=AddString(CN_st_Hand_Order[Com].DisDat,Asc,pBuf,sizeof(Asc),4);

	CN_st_Fun_AscNumber.ClsArray(Asc,sizeof(Asc));
	CN_st_Fun_AscNumber.Algorism2Asc(CN_st_File_Parameter.Speed,Asc);
	pBuf=AddString(CN_st_Hand_Order[Com].DisDat,Asc,pBuf,sizeof(Asc),5);
	
	CN_st_Fun_AscNumber.ClsArray(Asc,sizeof(Asc));
	CN_st_Fun_AscNumber.Algorism2Asc(CN_st_File_Parameter.HighL,Asc);
	pBuf=AddString(CN_st_Hand_Order[Com].DisDat,Asc,pBuf,sizeof(Asc),6);
	CN_st_Fun_Hand.LCDputLine(Buf);
}

static void Can(uint8 *Buf,uint8 *AmendBuf,uint8 Com)
{	//st_Da_CanInfor CN_st_Da_CanInfor;
	//CN_st_Fun_CanControl.Read(&CN_st_Da_CanInfor);
	//CN_st_Fun_AscNumber.HexBuf2Asc((uint8 *)&CN_st_Da_CanInfor,Buf,sizeof((uint8 *)&CN_st_Da_CanInfor));
	//AddString(CN_st_Hand_Order[Com].DisDat,(uint8 *)&CN_st_Da_CanInfor,Buf,100,0);
	CN_st_Fun_Hand.LCDputLine((uint8 *)" ");
}


static void EditCentrPhone1(uint8 *Buf,uint8 *AmendBuf,uint8 Com)	//*#8000*13800000000#
{	st_File_Parameter	CN_st_File_Parameter;
	uint8 DataLen;
//	uint8 buf[30];
	uint8 *pt,*ps;
	uint8 len;
	DataLen=CN_st_Fun_AscNumber.Strsize(AmendBuf);
	if((DataLen==0)||(DataLen>30))
		CN_st_Fun_Hand.LCDputLine((uint8 *)"输入错误");	
	else
	{	CN_st_Fun_File.ReadRecoder(CN_st_File_fd.Parameterfd,0,&CN_st_File_Parameter);
		CN_st_Fun_AscNumber.ClsArray(CN_st_File_Parameter.CenterPhone1,15);	 	
		ps = AmendBuf+7;
		pt = CN_st_Fun_AscNumber.LookStr("#",ps);
		len = pt - ps;
        CN_st_Fun_AscNumber.MoveByte(Buf,AmendBuf+7,len);
		//CN_st_Fun_AscNumber.MoveByte(CN_st_File_Parameter.CenterPhone1,AmendBuf,DataLen);
		CN_st_Fun_AscNumber.MoveByte(CN_st_File_Parameter.CenterPhone1,Buf,len);
		CN_st_Fun_File.WriteRecoder(CN_st_File_fd.Parameterfd,0,&CN_st_File_Parameter);
		AddString(CN_st_Hand_Order[Com].DisDat,CN_st_File_Parameter.CenterPhone1,Buf,15,0);
		CN_st_Fun_Hand.LCDputLine(Buf);
	}	
}

static void EditCentrPhone2(uint8 *Buf,uint8 *AmendBuf,uint8 Com)
{	st_File_Parameter	CN_st_File_Parameter;
	uint8 DataLen;
//	uint8 buf[30];
	uint8 *pt,*ps;
	uint8 len;
	DataLen=CN_st_Fun_AscNumber.Strsize(AmendBuf);
	if((DataLen==0)||(DataLen>30))
		CN_st_Fun_Hand.LCDputLine((uint8 *)"输入错误");	
	else
	{	CN_st_Fun_File.ReadRecoder(CN_st_File_fd.Parameterfd,0,&CN_st_File_Parameter);
		CN_st_Fun_AscNumber.ClsArray(CN_st_File_Parameter.CenterPhone2,15);	 	
		ps = AmendBuf+7;
		pt = CN_st_Fun_AscNumber.LookStr("#",ps);
		len = pt - ps;
        CN_st_Fun_AscNumber.MoveByte(Buf,AmendBuf+7,len);
		//CN_st_Fun_AscNumber.MoveByte(CN_st_File_Parameter.CenterPhone1,AmendBuf,DataLen);
		CN_st_Fun_AscNumber.MoveByte(CN_st_File_Parameter.CenterPhone2,Buf,len);
		CN_st_Fun_File.WriteRecoder(CN_st_File_fd.Parameterfd,0,&CN_st_File_Parameter);
		AddString(CN_st_Hand_Order[Com].DisDat,CN_st_File_Parameter.CenterPhone2,Buf,15,0);
		CN_st_Fun_Hand.LCDputLine(Buf);
	}	
}

static void EditCentr(uint8 *Buf,uint8 *AmendBuf,uint8 Com)
{	st_File_Parameter	CN_st_File_Parameter;
	uint8 DataLen;
//	uint8 buf[30];
	uint8 *pt,*ps;
	uint8 len;
	DataLen=CN_st_Fun_AscNumber.Strsize(AmendBuf);
	if((DataLen==0)||(DataLen>30))
		CN_st_Fun_Hand.LCDputLine("输入错误");	
	else
	{	CN_st_Fun_File.ReadRecoder(CN_st_File_fd.Parameterfd,0,&CN_st_File_Parameter);
		CN_st_Fun_AscNumber.ClsArray(CN_st_File_Parameter.CenPhone,15);	 	
		ps = AmendBuf+7;
		pt = CN_st_Fun_AscNumber.LookStr("#",ps);
		len = pt - ps;
        CN_st_Fun_AscNumber.MoveByte(Buf,AmendBuf+7,len);
		//CN_st_Fun_AscNumber.MoveByte(CN_st_File_Parameter.CenterPhone1,AmendBuf,DataLen);
		CN_st_Fun_AscNumber.MoveByte(CN_st_File_Parameter.CenPhone,Buf,len);
		CN_st_Fun_File.WriteRecoder(CN_st_File_fd.Parameterfd,0,&CN_st_File_Parameter);
		AddString(CN_st_Hand_Order[Com].DisDat,CN_st_File_Parameter.CenPhone,Buf,15,0);
		CN_st_Fun_Hand.LCDputLine(Buf);
	}	
}
/*	DataLen=CN_st_Fun_AscNumber.Strsize(AmendBuf);
	if((DataLen==0)||(DataLen>15))
		CN_st_Fun_Hand.LCDputLine("输入错误");
	else
		CN_st_Fun_Hand.LCDputLine(CN_st_Hand_Order[Com].DisDat);
} */
static void Star(uint8 *Buf,uint8 *AmendBuf,uint8 Com)
{	st_Data_Gps	CN_st_Data_Gps;
	uint8 Asc[10];
	CN_st_Fun_AscNumber.ClsArray(Asc,sizeof(Asc));
	CN_st_Control_Fun_Gps.Read(&CN_st_Data_Gps);
	CN_st_Fun_AscNumber.Algorism2Asc((uint32 )CN_st_Data_Gps.CN_st_Gps_Data_GPGGA.StarNumber,Asc);
   	AddString(CN_st_Hand_Order[Com].DisDat,Asc,Buf,sizeof(Asc),0);
   	CN_st_Fun_Hand.LCDputLine(Buf);
}
static void EditMiMA(uint8 *Buf,uint8 *AmendBuf,uint8 Com)
{ 	//st_File_Parameter	CN_st_File_Parameter;
	uint8 DataLen;
//	uint8 buf[30];
	uint8 *pt,*ps;
	uint8 len;
	DataLen=CN_st_Fun_AscNumber.Strsize(AmendBuf);
	if((DataLen==0)||(DataLen>30))
		CN_st_Fun_Hand.LCDputLine("输入错误");	
	else
	{	//CN_st_Fun_File.ReadRecoder(CN_st_File_fd.Parameterfd,0,&CN_st_File_Parameter);
		//CN_st_Fun_AscNumber.ClsArray(CN_st_File_Parameter.MiMA,15);	 	
		ps = AmendBuf+9;
		pt = CN_st_Fun_AscNumber.LookStr("#",ps);
		len = pt - ps;
        CN_st_Fun_AscNumber.MoveByte(Buf,AmendBuf+9,len);
		//CN_st_Fun_AscNumber.MoveByte(CN_st_File_Parameter.CenterPhone1,AmendBuf,DataLen);
		//CN_st_Fun_AscNumber.MoveByte(CN_st_File_Parameter.MiMA,Buf,len);
		//CN_st_Fun_File.WriteRecoder(CN_st_File_fd.Parameterfd,0,&CN_st_File_Parameter);
		//AddString(CN_st_Hand_Order[Com].DisDat,CN_st_File_Parameter.MiMA,Buf,15,0);
		CN_st_Fun_Hand.LCDputLine(Buf);
	}	
}
static void EditMaID(uint8 *Buf,uint8 *AmendBuf,uint8 Com)
{ 	st_File_Basic	CN_st_File_Basic;
    uint8 DataLen;
//	uint8 buf[30];
	uint8 *pt,*ps;
	uint8 len;
	DataLen=CN_st_Fun_AscNumber.Strsize(AmendBuf);
	if((DataLen==0)||(DataLen>30))
		CN_st_Fun_Hand.LCDputLine("输入错误");	
	else
	{//	OSTimeDly(10);
		CN_st_Fun_File.ReadRecoder(CN_st_File_fd.Basicfd,0,&CN_st_File_Basic);
		CN_st_Fun_AscNumber.ClsArray(CN_st_File_Basic.MachID,16);	 	
		ps = AmendBuf+9;
		pt = CN_st_Fun_AscNumber.LookStr("#",ps);
		len = pt - ps;
        CN_st_Fun_AscNumber.MoveByte(Buf,AmendBuf+9,len);
		//CN_st_Fun_AscNumber.MoveByte(CN_st_File_Parameter.CenterPhone1,AmendBuf,DataLen);
		CN_st_Fun_AscNumber.MoveByte(CN_st_File_Basic.MachID,Buf,len);
		CN_st_Fun_File.WriteRecoder(CN_st_File_fd.Basicfd,0,&CN_st_File_Basic);
		AddString(CN_st_Hand_Order[Com].DisDat,CN_st_File_Basic.MachID,Buf,15,0);
		CN_st_Fun_Hand.LCDputLine(Buf);
	}	
}
/*	uint8 DataLen;
	DataLen=CN_st_Fun_AscNumber.Strsize(AmendBuf);
	if((DataLen==0)||(DataLen>16))	
		CN_st_Fun_Hand.LCDputLine("输入错误");
	else		
	{	CN_st_Fun_File.ReadRecoder(CN_st_File_fd.Basicfd,0,&CN_st_File_Basic);
		CN_st_Fun_AscNumber.ClsArray(CN_st_File_Basic.MachID,16);
	 	CN_st_Fun_AscNumber.MoveByte(CN_st_File_Basic.MachID,AmendBuf,DataLen);
		CN_st_Fun_File.WriteRecoder(CN_st_File_fd.Basicfd,0,&CN_st_File_Basic);
		AddString(CN_st_Hand_Order[Com].DisDat,CN_st_File_Basic.MachID,Buf,16,0);
	 	CN_st_Fun_Hand.LCDputLine(Buf);
	}
} */

static void BackMaID(uint8 *Buf,uint8 *AmendBuf,uint8 Com)
{	BackInit();
	CN_st_Fun_Hand.LCDputLine("正在恢复出厂值");
}
/*===============================================================================================================*/
static uint8 Strsizeoa(uint8 *Buf)
{	uint8 i;
	for(i=0;i<200;i++)
	{	if((Buf[i]==0x00)||(Buf[i]==0x0d))
			return i;
	}	
	return i;
}


static uint8 *AddString(uint8 *ConstBuf,uint8 *Buf,uint8 *ReBuf,uint8 SizeofBuf,uint8 Number)
{	uint8 *pTemp,*ps; 	
	uint8 DataLen,i;

	ps =  ConstBuf;
	for(i=0,pTemp=ps;i<Number;i++)
	{	pTemp=CN_st_Fun_AscNumber.LookStr("\r",ps);
		pTemp++;
		ps = pTemp;	
	}  
		
	DataLen=Strsizeoa(pTemp);

	CN_st_Fun_AscNumber.MoveByte(ReBuf,pTemp,DataLen); 
	ReBuf+=DataLen;				   
	DataLen=CN_st_Fun_AscNumber.Strsize(Buf);

	if(DataLen>SizeofBuf)
		DataLen=SizeofBuf;
	CN_st_Fun_AscNumber.MoveByte(ReBuf,Buf,DataLen);

	ReBuf+=DataLen;
	*ReBuf++=' ';
	return ReBuf;
}
