/*++++++++++++++++++++++++++++++++++++++++�ؼ������+++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/
#define De_EventBox_DownLoaderContr_Start					1
#define De_EventBox_DownLoaderContr_Acc						De_EventBox_DownLoaderContr_Start 	//����Acc�ؼ�
#define De_EventBox_DownLoaderContr_Adc						De_EventBox_DownLoaderContr_Acc+1 	//���ص�ѹ���ؼ�
#define De_EventBox_DownLoaderContr_Can						De_EventBox_DownLoaderContr_Adc+1 	//����Can�ؼ�
#define De_EventBox_DownLoaderContr_Gprs					De_EventBox_DownLoaderContr_Can+1  	//����GPRS�ؼ�
#define De_EventBox_DownLoaderContr_Gps						De_EventBox_DownLoaderContr_Gprs+1	//����GPS�ؼ�
#define De_EventBox_DownLoaderContr_Sleep					De_EventBox_DownLoaderContr_Gps+1	//�������߿ؼ�
#define De_EventBox_DownLoaderContr_Timer					De_EventBox_DownLoaderContr_Sleep+1	//���ض�ʱ���ؼ�
#define De_EventBox_DownLoaderContr_Hand					De_EventBox_DownLoaderContr_Timer+1	//�����ֱ��ؼ�
#define De_EventBox_DownLoaderContr_Oil						De_EventBox_DownLoaderContr_Hand+1	//���������ؼ�
#define De_EventBox_DownLoaderContr_LCD						De_EventBox_DownLoaderContr_Oil+1	//����LCD�ؼ�
#define De_EventBox_DownLoaderContr_Number					De_EventBox_DownLoaderContr_LCD-De_EventBox_DownLoaderContr_Acc+1	//�ؼ�������
/*+++++++++++++++++++++++++++++++++++++++++++�ļ�ϵͳ����++++++++++++++++++++++++++++++++++++++++++++++++++++*/
#define De_EventBox_DownLoaderFile_Start					20
#define De_EventBox_DownLoaderFile_File						De_EventBox_DownLoaderFile_Start	//�����ļ�ϵͳ
/*+++++++++++++++++++++++++++++++++++++++++�ļ�������++++++++++++++++++++++++++++++++++++++++++++++++++++++*/
#define De_EventBox_Par_Amend_Start							30
#define De_EventBox_Par_Amend_BackFac						De_EventBox_Par_Amend_Start			//���ػָ�����ֵ
/*+++++++++++++++++++++++++++++++++++++++++�ڲ��¼�����++++++++++++++++++++++++++++++++++++++++++++++++++++++*/
#define De_EventBox_Inside_Start							40
#define De_EventBox_Inside_APN								De_EventBox_Inside_Start			//APN����
#define De_EventBox_Inside_Login							De_EventBox_Inside_APN+1			//��¼
#define De_EventBox_Inside_AccTimer							De_EventBox_Inside_Login+1			//ACCʱ��ͳ��
#define De_EventBox_Inside_MileageSum						De_EventBox_Inside_AccTimer+1		//���ͳ��
#define De_EventBox_Inside_CloseGps							De_EventBox_Inside_MileageSum+1		//�ر�GPS
#define De_EventBox_Inside_OpenGps							De_EventBox_Inside_CloseGps+1		//��GPS
#define De_EventBox_Inside_CloseGprs						De_EventBox_Inside_OpenGps+1		//�ر�GPRS
#define De_EventBox_Inside_OpenGprs							De_EventBox_Inside_CloseGprs+1		//����
																							