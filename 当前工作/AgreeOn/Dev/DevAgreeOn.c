static uint16 Init(void)
{	


}
typedef struct
{	uint16 (*Read)(uint8 fd,uint8 *Data,uint16 *DataLen);
	uint16 (*Write)(uint8 fd,uint8 *Data,uint16 *DataLen);
}st_Fun_HardWare_Dev;

typedef struct
{	uint8 IMEI[7];
	uint8 fd;
	st_Fun_HardWare_Dev	CN_st_Fun_HardWare_Dev;
}st_AgreeOn_OpenPar;								//调用打开函数时的入口参数
#define De_AgreeOn_Open_Port_Number					2
typedef struct
{	st_AgreeOn_OpenPar	CN_st_AgreeOn_OpenPar[De_AgreeOn_Open_Port_Number];



}st_AgreeOn_OperPar;

static uint16 Open(st_AgreeOn_OpenPar	*ptst_AgreeOn_OpenPar,uint8 *fd)
{	




}