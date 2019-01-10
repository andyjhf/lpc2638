static void InitHardWare(void)
{	st_Display_Send	CN_st_Display_Send;
	st_Display_Agree	CN_st_Display_Agree;
	uint16 DisplayResult,Result;
	uint8 fd;
	st_Sensor_DataPar	CN_st_Sensor_DataPar;
	if(CN_st_Fun_Sensor.Init()!=De_Suc_Sensor)
		return ;
	DisplayResult=CN_st_Fun_Sensor.Open(&CN_st_Sensor_DataPar,&fd);	
	;									//读取
	;									//发送显示命令
	FileData_CheckFile();				//检查文件系统
	/*====================================加载各个硬件=================================================*/									
	CN_st_Display_Agree.WorkPar=De_Sensor_WordPar_Gps;
	CN_st_Fun_Sensor.Open(&CN_st_Display_Agree,fd);	 //加载GPS
	
	
		


	
}


static void DisplayTask(void *Task)
{	
	CN_st_Sensor_DataPar.WorkPar=De_Sensor_WordPar_Display;
		






}