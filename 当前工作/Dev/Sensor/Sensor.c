#define De_Sensor_Compiler
#include "Sensor.h"
static uint16 Init(void)
{	uint8 i;
	for(i=0;i<De_Senor_Max_Number;i++)
		CN_st_Fun_AscNumber.MoveByte(&CN_st_Sensor_Oper[i],(void *)&CN_Ba_st_Sensor_Oper,sizeof(st_Sensor_Oper));
	return De_Suc_Sensor;
}
static uint16 Open(st_Sensor_DataPar	*ptst_Sensor_DataPar,uint8 *fd)			//打开对应的硬件
{	uint16 Result;
	uint8 i,j;
	for(i=0;i<De_Senor_Max_Number;i++)
	{	if(CN_st_Sensor_Oper[i].State==De_Senor_State_Close)
			break;
	}
	if(i==De_Senor_Max_Number)
		return De_Erro_Senor_OverMaxNumber;
	*fd=i;
	for(i=0;i<sizeof(CN_st_Sensor_ParList)/sizeof(CN_st_Sensor_ParList[0]);i++)		
	{	for(j=0;j<CN_st_Sensor_ParList[i]->SizeofPar;j++)		
		{	if(CN_st_Sensor_ParList[i]->ptst_Sensor_Par2Type[j].WorkPar==ptst_Sensor_DataPar->WorkPar)
				break;	 				
		}
		if(j!=CN_st_Sensor_ParList[i]->SizeofPar)								//已经找到对应的工作参数
			break;
	}
	if(i==sizeof(CN_st_Sensor_ParList)/sizeof(CN_st_Sensor_ParList[0]))			//工作参数
		return De_Erro_Senor_NoWorkPar;
	if(CN_st_Sensor_ParList[i]->ptst_Less_DataPar->Init!=NULL)
	{	if((Result=CN_st_Sensor_ParList[i]->ptst_Less_DataPar->Init())!=De_Suc_Sensor)
			return Result;
	}
	if(CN_st_Sensor_ParList[i]->ptst_Less_DataPar->Open!=NULL)
	{	if((Result=CN_st_Sensor_ParList[i]->ptst_Less_DataPar->Open(ptst_Sensor_DataPar,&j))!=De_Suc_Sensor)
			return Result;
   	}
	CN_st_Sensor_Oper[*fd].State=De_Senor_State_Open;
	CN_st_Fun_AscNumber.MoveByte(&CN_st_Sensor_Oper[*fd].CN_st_Sensor_DataPar,ptst_Sensor_DataPar,sizeof(st_Sensor_DataPar));
	CN_st_Sensor_Oper[*fd].fd=j;
	CN_st_Sensor_Oper[*fd].ptst_Fun_Les=(st_Fun_Sensor2Hard	*)CN_st_Sensor_ParList[i]->ptst_Less_DataPar;
	return De_Suc_Sensor;
}

static uint16 Close(uint8 fd)
{	uint16 Result;
	if(CN_st_Sensor_Oper[fd].State==De_Senor_State_Close)
		return De_Suc_Sensor;
	if(CN_st_Sensor_Oper[fd].ptst_Fun_Les->Close!=NULL)
	{	if((Result=CN_st_Sensor_Oper[fd].ptst_Fun_Les->Close(CN_st_Sensor_Oper[fd].fd))!=De_Suc_Sensor)
			return Result;
	}
	CN_st_Sensor_Oper[fd].State=De_Senor_State_Close;
	return De_Suc_Sensor;
}

static uint16 Read(uint8 fd,void *SendBuf,void *AgreeBuf)
{	uint16 Result;
	if(CN_st_Sensor_Oper[fd].State==De_Senor_State_Close)
		return De_Erro_Senor_NoOpen;
	if((Result=CN_st_Sensor_Oper[fd].ptst_Fun_Les->Read(CN_st_Sensor_Oper[fd].fd,SendBuf,AgreeBuf))!=De_Suc_Sensor)
		return Result;	
	return Result;
}
static uint16 GetState(st_Sensor_State	*ptst_Sensor_State,uint8 fd)
{	uint16 Result;
	if(CN_st_Sensor_Oper[fd].ptst_Fun_Les->GetState==NULL)
	{	ptst_Sensor_State->Work=De_Sensor_State_Suc;
		ptst_Sensor_State->Battery=De_Sensor_State_Suc;
		ptst_Sensor_State->Dly=De_Sensor_State_Suc;
	}
	if(CN_st_Sensor_Oper[fd].State==De_Senor_State_Close)
		return De_Erro_Senor_NoOpen;
	Result=De_Suc_Sensor;
	if(CN_st_Sensor_Oper[fd].ptst_Fun_Les->GetState!=NULL)
	{	if((Result=CN_st_Sensor_Oper[fd].ptst_Fun_Les->GetState(ptst_Sensor_State,fd))!=De_Suc_Sensor)
			return Result;
	}
	else
	{	ptst_Sensor_State->Work=De_Sensor_State_Suc;
		ptst_Sensor_State->Battery=De_Sensor_State_Suc;
		ptst_Sensor_State->Dly=De_Sensor_State_Suc;
	}
	return Result;
}

static uint16 GetSi(uint8 fd,st_Sensor_DataPar	*ptst_Sensor_DataPar)
{	CN_st_Fun_AscNumber.MoveByte(ptst_Sensor_DataPar,&CN_st_Sensor_Oper[fd].CN_st_Sensor_DataPar,
	sizeof(st_Sensor_DataPar));
	return De_Suc_Sensor;
}

static uint16 Get(st_Sensor_DataPar	**ptst_Sensor_DataPar,uint8 *Number)
{	uint8 i,j;
	for(i=0,j=0;i<De_Senor_Max_Number;i++)
	{	if(CN_st_Sensor_Oper[i].State==De_Senor_State_Close)
			continue;
		CN_st_Fun_AscNumber.MoveByte(ptst_Sensor_DataPar[j++],&CN_st_Sensor_Oper[i].CN_st_Sensor_DataPar,
		sizeof(st_Sensor_DataPar));	
	}
	return De_Suc_Sensor;
}

static uint16 GetPar2ID(uint16 Par,uint8 *fd)
{	uint8 i;
	for(i=0;i<De_Senor_Max_Number;i++)
	{	if(CN_st_Sensor_Oper[i].CN_st_Sensor_DataPar.WorkPar==Par)
		{	*fd=i;
			return De_Suc_Sensor;
		}	
	}
	return De_Erro_Senor_NoPar;
}

static uint16 GetID2Par(uint8 fd,uint16 *Par)
{	if(fd>=De_Senor_Max_Number)
		return De_Erro_Senor_NoID;
	if(CN_st_Sensor_Oper[fd].State==De_Senor_State_Close)
		return De_Erro_Senor_NoID;
   	*Par=CN_st_Sensor_Oper[fd].CN_st_Sensor_DataPar.WorkPar;
	return De_Suc_Sensor;
}
