/*----------------------------------------����Э��ͷ������-------------------------------------------------*/
	#define De_IP_Com_AgreeOn											2				//����ͨѶ��Э��汾
	#define De_Dev_SendCom_Mod_IP										0				//ͨѶ��ʽΪIP��ʽ
	#define De_Dev_SendCom_Mod_Sms										1				//ͨѶ��ʽΪSMS��ʽ
	#define De_Dev_SendCom_Mod_IPSms									2				//ͨѶ��ʽΪIP��SMS��ʽ
/*-----------------------------------------����������Э��--------------------------------------------------*/
	/*++++++++++++++++++++++++++++++++++��������Э��+++++++++++++++++++++++++++++++++++++++++++++*/	
	#define De_Centr_Order_Answer										0x0001			//��������Ӧ��
	#define De_Centr_Order_Orientation									0x0002			//��λָ��
	#define De_Centr_Order_Track										0x0003			//׷��ָ��
	#define De_Centr_Order_SetPar										0x0004			//�趨����
	#define De_Centr_Order_UnlockWaring									0x0005			//�������
	#define De_Centr_Order_AmendMenum									0x0006			//�޸Ĺ̶��˵�
	#define De_Centr_Order_LoaderTxt									0x0007			//�·��ı�����
	#define De_Centr_Order_LoaderTxtMenum								0x0008			//�·����ı��Ĳ˵�
	#define De_Centr_Order_SetPhone										0x0009			//���ù̶��绰
	#define De_Centr_Order_CallAnswer									0x000a			//ͨ������
	#define De_Centr_Order_UpdateSoftWare								0x000b			//�������
	#define De_Centr_Order_LookPar										0x000c			//��ѯ����
	#define De_Centr_Order_Contrl										0x000d			//Զ�̿���
	#define De_Centr_Order_ConfineCall									0x000e			//ͨ������״̬
	#define De_Centr_Order_ConfigCentrSever								0x000f			//�������ķ�����״̬
	#define De_Centr_Order_Activation									0x0010			//���λ�ն�
		/***************************************************************************************/
	#define De_Centr_Order_LookJpg										0x0401			//��ѯָ�����͵���Ƭ
	#define De_Centr_Order_JpgIng										0x0402			//��ѯʵʱ��Ƭ
	#define De_Centr_Order_SetVidType									0x0403			//������������
	#define De_Centr_Order_TabelList									0x0404			//���ñ�
	#define De_Centr_Order_LookWorkPar									0x0405			//��ѯ��������
	#define De_Centr_Order_WorkParTimer									0x0406			//���չ̶�ʱ���ϴ���������	
	#define De_Centr_Order_WorkParSpace									0x0407		   	//���ռ���ϴ���������
	#define De_Centr_Order_LookLog										0x0408			//��ѯ��־�ļ�
	#define De_Centr_Order_SetWaringTerm								0x0409			//���ñ�������
		/**********************************����Э��ר��****************************************/
	#define De_Centr_Order_SetRound										0X0801			//����Բ��·��
	#define De_Centr_Order_DelRound										0x0802			//ɾ��Բ��·��
	#define De_Centr_Order_SetRectangle									0X0803			//���þ���·��
	#define De_Centr_Order_DelRectangle									0x0804			//ɾ������·��
	#define De_Centr_Order_SetPolygon									0X0805			//���ö����·��
	#define De_Centr_Order_DelPolygon									0x0806			//ɾ�������·��
	#define De_Centr_Order_SetRoadMap									0x0807			//����·������
	#define De_Centr_Order_DelRoadMap									0x0808			//ɾ��·������
	#define De_Centr_Order_Reduce										0X0809			//����ѹ���ش�
	#define De_Centr_Order_Driver										0x080a			//���ü�ʻԱID
	#define De_Centr_Order_Navigation									0x080b			//���ĵ���
	#define De_Centr_Order_HandTxt										0x080c			//�ֻ��ı�����
	#define De_Centr_Order_HandAttemper									0X080D			//�ֻ�������Ϣ	
		/***********************************���⳵Э��****************************************/ 
	#define	De_Centr_Order_AmendForm									0x0c01			//�޸Ķ�����Ϣ
	#define De_Centr_Order_UpLoaderForm									0x0c02			//�·�����������Ϣ
	#define De_Centr_Order_UpLoaderFormSuc								0x0c03			//�·���������ɹ���Ϣ
	#define De_Centr_Order_UpLoaderFormErro								0x0c04			//�·���������ʧ����Ϣ
	#define De_Centr_Order_UpLoaderCan									0x0c05			//�·�����ȡ����Ϣ		   	  	   	 
	/*++++++++++++++++++++++++++++++++++++�����ն�Э��++++++++++++++++++++++++++++++++++++++++++++++*/
	#define De_Dev_Order_GetSeverComPar									0x0101			//��ȡ������ͨѶ����
	#define De_Dev_Order_Login											0x0102			//��λ�ն˵�¼
	#define De_Dev_Order_Sleep											0x0103			//��λ�ն�����
	#define De_Dev_Order_CloseModerm									0x0104			//��λ�ն˹ػ�
	#define De_Dev_Order_Answer											0x0105			//��λ�ն�����Ӧ��
	#define De_Dev_Order_Orientation									0x0106			//�ϴ�λ����Ϣ
	#define De_Dev_Order_Menum											0x0107			//�ϴ��˵���Ϣ
	#define De_Dev_Order_TxtMenum										0x0108			//�ϴ����˵��ķ�����Ϣ
	#define De_Dev_Order_LookPar										0x0109			//�ϴ���λ�ն������̼�״̬
	#define De_Dev_Order_UpdateSoftWare									0x010a			//�ϴ��������״̬
	#define De_Dev_Order_Waring											0x010b			//�ϴ�����״̬
		/****************************************************************************************/
	#define De_Dev_Order_UploaderJpg1									0x0501			//�ϴ���Ƭһ
	#define De_Dev_Order_UploaderJpg2									0x0502			//�ϴ���Ƭ��
	#define De_Dev_Order_TabelList										0x0503			//��
	#define De_Dev_Order_UploaderPar									0x0504			//�ϴ�����
	#define De_Dev_Order_UploaderLog									0x0505			//�ϴ���־�ļ�
		/**********************************����Э��ר��****************************************/
	#define De_Dev_Order_OutRoadMap										0x0901			//�������򱨾�
	#define De_Dev_Order_UpLoaderReduce									0x0902			//�ϴ�ѹ������
	#define De_Dev_Order_UpLoaderDriver									0x0903			//�ϴ���ʻԱID
	#define De_Dev_Order_UpLoaderHandMess								0x0904			//�ϴ��ֻ�����
	#define De_Dev_Order_NoSem											0x0905			//ä��������Ϣ
		/***********************************���⳵Э��*****************************************/
	#define De_Dev_UpLoaderFrom											0x0d02			//�ϴ�����������Ϣ
	#define De_Dev_OverFromErro											0x0d03			//�ϴ�����δ�����ԭ��
	#define De_Dev_PriceData											0x0d04			//�ϴ��Ƽ�����Ϣ

	/*++++++++++++++++++++++++++++++++++��������++++++++++++++++++++++++++++++++++++++++++++++++++++*/
	#define De_SetPar_SetGreenPar										0x0000			//����
	#define De_SetPar_SetGreenWord										0x0001			//���ý�������
	#define De_SetPar_SetListePhone										0x0100			//���ü�������							
	#define De_SetPar_SetResetPhone										0x0101			//���õ绰��λ
	#define De_SetPar_SetCerSevPhone 									0x0102			//���ö������ķ������
	#define De_SetPar_SetCenPhone										0x0103			//���ö�������
	#define De_SetPar_SetAPN											0x0200			//����APN����
	#define De_SetPar_SetMastIP											0x0201			//����������IP
	#define De_SetPar_SetMastDomainName									0x0202			//����������
	#define De_SetPar_SetReserveIP										0x0203			//���ø�����IP
	#define De_SetPar_SetReserveDomainName								0x0204			//����������
	#define De_SetPar_SetCenPort										0x0205			//�������Ķ˿ں�
	#define De_SetPar_SetCentHeart										0x0206			//�����·��������
	#define De_SetPar_SetUseName										0x0207			//�����û���
	#define De_SetPar_SetUsePass										0x0208			//�����û���
	#define De_SetPar_SetDevHeart										0x0209			//�ն��Ϸ��������
	#define De_SetPar_SetComMod											0x020a			//����ͨѶ��ʽ
	#define De_SetPar_SetIPRepeat										0x020b			//Ip�ؼ�ָ���ط�����
	#define De_SetPar_SetIPRepeatTime									0x020c			//IP�ؼ�ָ���ط����ʱ��
	#define De_SetPar_SetMessageRepeat									0x020d			//Message�ؼ�ָ���ط�����
	#define De_SetPar_SetMessageRepeatTimer								0x020e			//Message Timer �ط�ʱ��
	#define De_SetPar_SetIPTransSms										0x020f			//Message��IP֮���л�ʱ��
	#define De_SetPar_SetDataLog										0x0210			//������־�洢
	#define De_SetPar_SetDataScotomaLog									0x0211			//ä����������
	#define De_SetPar_SetParLoad										0x0212			//�����ϴ�����
	#define De_SetPar_SetWireLessPar									0x0213			//�������߲���
	#define De_SetPar_SetDePassWord										0x0301			//�����ն�����
	#define De_SetPar_ComFac											0x0302			//�ظ�����ֵ
	#define De_SetPar_SetAccTimer										0x0303			//����ACC�ۼ�ʱ��
	#define De_SetPar_SetRunLen											0x0304			//�����������
	#define De_SetPar_SetPerPuse										0x0305			//����ÿ�ܵ�������
	#define De_SetPar_SetCarFeature										0x0306			//���ó�������
	#define De_SetPar_SetTakeLCD										0x0307			//���ó����Ƿ�װ����
	#define De_SetPar_SetOilFrequency									0x0308			//������������Ƶ��
	#define De_SetPar_SetSleepTimer										0x0309			//��������ʱ��
	#define De_SetPar_SetCloseTimer										0x030a			//���ùػ�ʱ��
	#define De_SetPar_SetLogMess										0x030b			//���õ�¼��ʾ
	#define De_SetPar_SetTaskVid										0x030c			//�����Ƿ�װ����ͷ
	#define De_SetPar_SetHighSpeed										0x0400			//���ó��ٱ���
	#define De_SetPar_SetLowSpeed										0x0401			//���õ��ٱ���
	#define De_SetPar_SetLowVlt											0x0402			//���õ͵�ѹ����
	#define De_SetPar_SetVidType										0x0500			//������������
	#define De_SetPar_SetOrderFrmTimer									0x0600			//����ԤԼ����ʱ��
	#define De_SetPar_HardWareEdit										0x0700			//��ѯӲ���汾
	#define De_SetPar_SoftWareEdit										0x0701			//��ѯ����汾
	#define De_SetPar_MachID											0X0702			//��ѯ�������
	#define De_SetPar_Menum												0x0703			//��ѯ�˵���Ϣ
	#define De_SetPar_Phone												0x0704			//��ѯ�̶��绰��Ϣ
	#define De_SetPar_ConfineCall										0x0705			//��ѯͨ������״̬
	#define De_SetPar_DriverID											0X0706			//��ѯ��ʻԱ
	#define De_SetPar_DriverLogin										0x0707			//��ѯ�ѵ�¼�ļ�ʻԱ				
	
				