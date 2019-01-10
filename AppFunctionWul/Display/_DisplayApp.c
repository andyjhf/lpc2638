/*===================================================================================================================================================================*/
static void Oper(uint8 fd,void *Data,uint8 *DateTimer)					//调度屏接受函数
{	union
	{	st_Display_Agree_Phone	*ptst_Display_Agree_Phone;
		st_Display_Agree_SeePar	*ptst_Display_Agree_SeePar;
		st_Display_Agree_SetPar	*ptst_Display_Agree_SetPar;
		st_Display_Agree_Log	*ptst_Display_Agree_Log;
		st_Display_Agree_OnCen	*ptst_Display_Agree_OnCen;
		st_Display_Agree_Voic	*ptst_Display_Agree_Voic;
	}CN_st_
	st_Display_Agree_Answer	*ptst_Display_Agree_Answer;
	ptst_Display_Agree_Answer=Data;
}

static void Oper_Phone(uint8 Order,void *Data,uint8 *DateTimer)			//拨打电话 		
{	st_Data_Gprs_Call	CN_st_Data_Gprs_Call;
	st_Display_Agree_Phone	*ptst_Display_Agree_Phone;
	uint8 PhoneState;
	if(CN_st_Fun_Gprs.GetPhoneState(&CN_st_Data_Gprs_Call)!=De_Suc_Gprs)
	{	SendData(Order,De_Display_Answer_Erro);							//发送错误
		return ;
	}
	ptst_Display_Agree_Phone=Data;
	if(ptst_Display_Agree_Phone->Type==De_Display_Agree_CallPhone)		//拨打电话
	{	if(CN_st_Data_Gprs_Call.Mod!=De_GprsHard_CallType_NoCall)
		{	SendData(Order,De_Display_Answer_Erro);						//发送错误
			return ;
		}
		if(CN_st_Fun_Gprs.SendPhone(ptst_Display_Agree_Phone->Phone,&PhoneState)!=De_Suc_Gprs)
		{	SendData(Order,De_Display_Answer_Erro);		//发送错误
			return ;
		}
		if(PhoneState!=De_GprsHard_Connect_OK)
		{	SendData(Order,De_Display_Answer_Erro);
			return ;
		}
		SendData(Order,De_Display_Answer_Suc);			
	}
	else if(ptst_Display_Agree_Phone->Type==De_Display_Agree_ClosePhone)	  //挂机
	{	CN_st_Fun_Gprs.CloseCall();
		SendData(Order,De_Display_Answer_Suc);
	}
	else if(ptst_Display_Agree_Phone->Type==De_Display_Agree_AnswerPhone)	 //应答电话
	{	if(CN_st_Data_Gprs_Call.Mod!=De_GprsHard_CallType_Passive)
		{	SendData(Order,De_Display_Answer_Erro);		//发送错误
			return ;
		}
	   	SendData(Order,De_Display_Answer_Suc);
	}
	else if(ptst_Display_Agree_Phone->Type==De_Display_Agree_CallPhone1)	//拨打分机号码
	{
		;		//需要软件进行添加

	}
}

static void Oper_SeePar(uint8 Order,void *Data,uint8 *DateTimer)  		//参数查询	
{	uint8 ListerPhone[15],RestPhone[15],MessSever[15],WaringPhone[15],APN[32],MastDomain[128],
		  ReserveDomain[128],MachiID[5],SoftWare
	uint32 MastIP,ReserveIP,DsnSever,PassWord,SelfIP,NonceIP,
	uint16 CenPort,CentHeart,Tracks
	uint8 CommEdit		
	st_Display_Agree_SeePar	*ptst_Display_Agree_SeePar;
	uint8 i;
	ptst_Display_Agree_SeePar=Data;
	for(i=0;i<ptst_Display_Agree_SeePar->ParNumber;i++)
	{
	
	
	
	}	



}

static void Oper_SetPar(uint8 Order,void *Data,uint8 *DateTimer)		//设置参数
{


}

static void Oper_Log(uint8 Order,void *Data,uint8 *DateTimer)			//登录信息
{


}

static void Oper_OnCen(uint8 Order,void *Data,uint8 *DateTimer)			//上传中心指令
{



}
static void Oper_Voic(uint8 Order,void *Data,uint8 *DateTimer)	  		//调节音量
{



}

static void SendData(uint8 ID,uint8 Result)			   //发送数据
{	st_Display_Send	CN_st_Display_Send;
	st_Display_Order_Answer	CN_st_Display_Order_Answer;
	uint8 fd;
	CN_st_Display_Send.SendData=&CN_st_Display_Order_Answer;
	CN_st_Display_Send.SendOrAgree=De_Sensor_Display_Send;
	CN_st_Display_Send.ID=De_Display_Host_Order_Answer;
	CN_st_Display_Order_Answer.AnswerID=ID;
	CN_st_Display_Order_Answer.Result=Result;
	CN_st_Fun_Sensor.GetPar2ID(De_Sensor_WordPar_Display,&fd);
	CN_st_Fun_Sensor.Read(fd,&CN_st_Display_Send,NULL);
}




	