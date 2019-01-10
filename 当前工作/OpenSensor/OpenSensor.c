#define De_OpenSensor_Compiler
#include "OpenSensor.h"
static void Init(void)
{	st_Sensor_DataPar	CN_st_Sensor_DataPar;
	st_File_WorkPar	CN_st_File_WorkPar;
	st_Parameter_Table	CN_st_Parameter_Table;
	uint16 ID[De_Affair_Sensor_MaxNumber];
	uint16 i,j;
	uint8 fd;
	CN_st_Fun_File.ReadRecoder(CN_st_File_fd.WorkParfd,0,&CN_st_File_WorkPar);
	for(i=0,j=0;i<sizeof(st_File_WorkPar)/sizeof(st_File_WorkParVal);i++)
	{	if(CN_st_File_WorkPar.CN_st_File_WorkParVal[i].YesOnON==De_WordPar_Close)
			continue;
		if(CN_st_Fun_Sensor.GetPar2ID(CN_Ba_WordPar[i],&fd)==De_Suc_Sensor)
			CN_st_Fun_Sensor.Close(fd);
		CN_st_Sensor_DataPar.Addree=CN_st_File_WorkPar.CN_st_File_WorkParVal[i].Adree;
		CN_st_Sensor_DataPar.WorkPar=CN_Ba_WordPar[i];
 		CN_st_Sensor_DataPar.MaxDly=1800;		
		if(CN_st_Fun_Sensor.Open(&CN_st_Sensor_DataPar,&fd)!=De_Suc_Sensor)
			continue;
		ID[j++]=CN_st_Sensor_DataPar.WorkPar;
	}
	for(i=0;i<sizeof(CN_Ba_OutPar)/sizeof(uint16);i++)
	{	if(CN_st_Fun_Sensor.GetPar2ID(CN_Ba_OutPar[i],&fd)==De_Suc_Sensor)
			CN_st_Fun_Sensor.Close(fd);
	   	CN_st_Sensor_DataPar.Addree=0xfffffff;
		CN_st_Sensor_DataPar.WorkPar=CN_Ba_OutPar[i];
 		CN_st_Sensor_DataPar.MaxDly=1800;	
		if(CN_st_Fun_Sensor.Open(&CN_st_Sensor_DataPar,&fd)!=De_Suc_Sensor)
			continue;
		ID[j++]=CN_Ba_OutPar[i];
	}
	if(CN_st_Fun_File.ReadRecoder(CN_st_File_fd.Workfd,0,&App_CN_st_WorkFlow_Table)!=De_Suc_File)
		CN_st_Fun_AscNumber.MoveByte(&App_CN_st_WorkFlow_Table,(void *)&CN_Ba_st_WorkFlow_Table,sizeof(st_WorkFlow_Table));	
	else
	{	CN_st_Fun_AscNumber.MoveByte(App_CN_st_WorkFlow_Table.CN_st_AgreeOn_Send_Basic.State,
		(void *)CN_Ba_st_WorkFlow_Table.CN_st_AgreeOn_Send_Basic.State,sizeof(CN_Ba_st_WorkFlow_Table.CN_st_AgreeOn_Send_Basic.State));
		CN_st_Fun_AscNumber.MoveByte(&App_CN_st_WorkFlow_Table.CN_st_WorkVal_Tabel,
		(void *)&CN_Ba_st_WorkFlow_Table.CN_st_WorkVal_Tabel,sizeof(CN_Ba_st_WorkFlow_Table.CN_st_WorkVal_Tabel));
	}
	CN_st_Fun_File.ReadRecoder(CN_st_File_fd.Parameterfd,0,&CN_st_Parameter_Table);
	if(CN_st_Parameter_Table.DisLCD==De_Agree_Par_TakeLCD_Yes)
	{	if(CN_st_Fun_Sensor.GetPar2ID(De_Sensor_WordPar_Display,&fd)==De_Suc_Sensor)
			CN_st_Fun_Sensor.Close(fd);
		CN_st_Sensor_DataPar.Addree=0xfffffff;
		CN_st_Sensor_DataPar.WorkPar=De_Sensor_WordPar_Display;
 		CN_st_Sensor_DataPar.MaxDly=1800;	
		if(CN_st_Fun_Sensor.Open(&CN_st_Sensor_DataPar,&fd)==De_Suc_Sensor)
			ID[j++]=De_Sensor_WordPar_Display;	
	}	

	CN_st_Fun_AppAgreeDataSensor.Init(ID,j);
}


