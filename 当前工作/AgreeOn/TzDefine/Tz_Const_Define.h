/*=======================================֧�ֲ��������==========================================================*/
#define De_Debug_h	
	typedef struct
	{	uint16 Par;
		uint8 Number;
	}st_AgreenOn_Par2Type; 
	#define De_CN_Ba_st_AgreenOn_Par2Type_Number   						51						//��������
	#define De_CN_Ba_WordPar_Number										36						//������������
	#define De_CN_Ba_LessPar_Number										10						//���ߴ���������

#ifdef De_TzV2_Compiler	
	const st_AgreenOn_Par2Type	CN_Ba_st_AgreenOn_Par2Type[De_CN_Ba_st_AgreenOn_Par2Type_Number]=
	{	{	De_SetPar_SetGreenPar,De_AgreeOn_SetPar_State_SetGreenPar},						//����
		{	De_SetPar_SetGreenWord,De_AgreeOn_SetPar_State_SetGreenWord},					//���ý�������
		{	De_SetPar_SetListePhone,De_AgreeOn_SetPar_State_SetListePhone},					//���ü�������							
		{	De_SetPar_SetResetPhone,De_AgreeOn_SetPar_State_SetResetPhone},					//���õ绰��λ
		{	De_SetPar_SetCerSevPhone,De_AgreeOn_SetPar_State_SetCerSevPhone}, 				//���ö������ķ������
		{	De_SetPar_SetCenPhone,De_AgreeOn_SetPar_State_SetCenPhone},						//���ö�������
		{	De_SetPar_SetAPN,De_AgreeOn_SetPar_State_SetAPN},								//����APN����
		{	De_SetPar_SetMastIP,De_AgreeOn_SetPar_State_SetMastIP},							//����������IP
		{	De_SetPar_SetMastDomainName,De_AgreeOn_SetPar_State_SetMastDomainName},			//����������
		{	De_SetPar_SetReserveIP,De_AgreeOn_SetPar_State_SetReserveIP},					//���ø�����IP
		{	De_SetPar_SetReserveDomainName,De_AgreeOn_SetPar_State_SetReserveDomainName},	//�������ø�����
		{	De_SetPar_SetCenPort,De_AgreeOn_SetPar_State_SetCenPort},						//�������Ķ˿ں�
		{	De_SetPar_SetCentHeart,De_AgreeOn_SetPar_State_SetCentHeart},					//�����·��������
		{	De_SetPar_SetUseName,De_AgreeOn_SetPar_State_SetUseName},						//�����û���
		{	De_SetPar_SetUsePass,De_AgreeOn_SetPar_State_SetUsePass},						//���ò�������
		{	De_SetPar_SetDevHeart,De_AgreeOn_SetPar_State_SetDevHeart},						//�ն��Ϸ��������
		{	De_SetPar_SetComMod,De_AgreeOn_SetPar_State_SetComMod},							//����ͨѶ��ʽ
		{	De_SetPar_SetIPRepeat,De_AgreeOn_SetPar_State_SetIPRepeat},						//Ip�ؼ�ָ���ط�����
		{	De_SetPar_SetIPRepeatTime,De_AgreeOn_SetPar_State_SetIPRepeatTime},				//IP�ؼ�ָ���ط����ʱ��
		{	De_SetPar_SetMessageRepeat,De_AgreeOn_SetPar_State_SetMessageRepeat},			//Message�ؼ�ָ���ط�����
		{	De_SetPar_SetMessageRepeatTimer,De_AgreeOn_SetPar_State_SetMessageRepeatTimer},	//Message Timer �ط�ʱ��
		{	De_SetPar_SetIPTransSms,De_AgreeOn_SetPar_State_SetIPTransSms},					//Message��IP֮���л�ʱ��
		{	De_SetPar_SetDataLog,De_AgreeOn_SetPar_State_SetDataLog},						//������־�洢
		{	De_SetPar_SetDataScotomaLog,De_AgreeOn_SetPar_State_SetDataScotomaLog},			//ä����������
		{	De_SetPar_SetParLoad,De_AgreeOn_SetPar_State_SetParLoad},						//�����ϴ�����
		{	De_SetPar_SetWireLessPar,De_AgreeOn_SetPar_State_SetWireLessPar},				//�������߲���
		{	De_SetPar_SetDePassWord,De_AgreeOn_SetPar_State_SetDePassWord},					//�����ն�����
		{	De_SetPar_ComFac,De_AgreeOn_SetPar_State_SetComFac},							//�ظ�����ֵ
		{	De_SetPar_SetAccTimer,De_AgreeOn_SetPar_State_SetAccTimer},						//����ACC�ۼ�ʱ��
		{	De_SetPar_SetRunLen,De_AgreeOn_SetPar_State_SetRunLen},							//�����������
		{	De_SetPar_SetPerPuse,De_AgreeOn_SetPar_State_SetPerPuse},						//����ÿ�ܵ�������
		{	De_SetPar_SetCarFeature,De_AgreeOn_SetPar_State_SetCarFeature},					//���ó�������
		{	De_SetPar_SetTakeLCD,De_AgreeOn_SetPar_State_SetTakeLCD},						//���ó����Ƿ�װ����
		{	De_SetPar_SetOilFrequency,De_AgreeOn_SetPar_State_SetOilFrequency},				//������������Ƶ��
		{	De_SetPar_SetSleepTimer,De_AgreeOn_SetPar_State_SetSleepTimer},					//��������ʱ��
		{	De_SetPar_SetCloseTimer,De_AgreeOn_SetPar_State_SetCloseTimer},					//���ùػ�ʱ��
		{	De_SetPar_SetLogMess,De_AgreeOn_SetPar_State_SetLogMess},						//���õ�¼��ʾ	
		{	De_SetPar_SetTaskVid,De_AgreeOn_SetPar_State_SetTaskVid},						//�����Ƿ�װ����ͷ
		{	De_SetPar_SetHighSpeed,De_AgreeOn_SetPar_State_SetHighSpeed},					//���ó��ٱ���
		{	De_SetPar_SetLowSpeed,De_AgreeOn_SetPar_State_SetLowSpeed},						//���õ��ٱ���
		{	De_SetPar_SetLowVlt,De_AgreeOn_SetPar_State_SetLowVlt},							//���õ͵�ѹ����
		{	De_SetPar_SetVidType,De_AgreeOn_SetPar_State_SetVidType},						//������������
		{	De_SetPar_SetOrderFrmTimer,De_AgreeOn_SetPar_State_SetOrderFrmTimer},			//����ԤԼ����ʱ��
		{	De_SetPar_HardWareEdit,De_AgreeOn_SetPar_State_SetHardWareEdit},				//��ѯӲ���汾
		{	De_SetPar_SoftWareEdit,De_AgreeOn_SetPar_State_SetSoftWareEdit},				//��ѯ����汾
		{	De_SetPar_MachID,De_AgreeOn_SetPar_State_SetMachID},							//��ѯ�������
		{	De_SetPar_Menum,De_AgreeOn_SetPar_State_SetMenum},								//��ѯ�˵���Ϣ
		{	De_SetPar_Phone,De_AgreeOn_SetPar_State_SetPhone},								//��ѯ�̶��绰��Ϣ
		{	De_SetPar_ConfineCall,De_AgreeOn_SetPar_State_SetConfineCall},					//��ѯͨ������״̬
		{	De_SetPar_DriverID,De_AgreeOn_SetPar_State_SetDriverID},						//��ѯ��ʻԱ
		{	De_SetPar_DriverLogin,De_AgreeOn_SetPar_State_SetDriverLogin}					//��ѯ�ѵ�¼�ļ�ʻԱ
	};
	const uint16  CN_Ba_WordPar[De_CN_Ba_WordPar_Number]=
	{	De_Sensor_WordPar_Switch1,	  														//������1
		De_Sensor_WordPar_Switch2,															//������2
		De_Sensor_WordPar_Switch3,															//������3
		De_Sensor_WordPar_Switch4,															//������4
		De_Sensor_WordPar_Switch5,															//������5
		De_Sensor_WordPar_Switch6,															//������6
		De_Sensor_WordPar_Switch7,															//������7
		De_Sensor_WordPar_Switch8,															//������8
		De_Sensor_WordPar_Switch9,															//������9
		De_Sensor_WordPar_Switch10,															//������10
		De_Sensor_WordPar_Switch11,															//������11
		De_Sensor_WordPar_Switch12,															//������12
		De_Sensor_WordPar_Switch13,															//������13
		De_Sensor_WordPar_Switch14,															//������14
		De_Sensor_WordPar_Switch15,															//������15
		De_Sensor_WordPar_Switch16,															//������16
		De_Sensor_WordPar_Less_Switch1,														//���߿�����1
		De_Sensor_WordPar_Less_Switch2,														//���߿�����2
		De_Sensor_WordPar_Less_Switch3,														//���߿�����3
		De_Sensor_WordPar_Less_Switch4,														//���߿�����4
		De_Sensor_WordPar_Less_Switch5,														//���߿�����5
		De_Sensor_WordPar_Less_Switch6,														//���߿�����6
		De_Sensor_WordPar_AccTimer,															//ACC�ۼ�ʱ��
		De_Sensor_WordPar_Mileage,														   	//���ͳ��
		De_Sensor_WordPar_Oil1,																//������λ1
		De_Sensor_WordPar_Sem,																//GSM�ź�ǿ��
		De_Sensor_WordPar_SendOilTimer,														//�����ۼ�ʱ��
		De_Sensor_WordPar_Temp,																//�¶�
		De_Sensor_WordPar_Oil2,																//������λ2
		De_Sensor_WordPar_Pulse,															//�������
		De_Sensor_WordPar_Humidity,															//ʪ��
		De_Sensor_WordPar_OilBaifen,														//������λ�ٷֱ�
		De_Sensor_WordPar_Less_Temp1,														//���ߴ������¶�1
		De_Sensor_WordPar_Less_Temp2,														//���ߴ������¶�2
		De_Sensor_WordPar_Less_Temp3,														//���ߴ������¶�3
		De_Sensor_WordPar_Less_Temp4														//���ߴ������¶�4
	};
	const uint16 CN_Ba_LessPar[De_CN_Ba_LessPar_Number]=													//���߿�����1
	{	De_Sensor_WordPar_Less_Switch1,	 													//���߿�����2				
		De_Sensor_WordPar_Less_Switch2,														//���߿�����3
		De_Sensor_WordPar_Less_Switch3,														//���߿�����4
		De_Sensor_WordPar_Less_Switch4,														//���߿�����5
		De_Sensor_WordPar_Less_Switch5,													   	//���߿�����6
		De_Sensor_WordPar_Less_Switch6,														//���ߴ������¶�1
		De_Sensor_WordPar_Less_Temp1,														//���ߴ������¶�2
		De_Sensor_WordPar_Less_Temp2,														//���ߴ������¶�3
		De_Sensor_WordPar_Less_Temp3,														//���ߴ������¶�4
		De_Sensor_WordPar_Less_Temp4
	};
	#define De_AgreeOn_SendOrder_Answer_Yes									1
	#define De_AgreeOn_SendOrder_Answer_No									0
#ifdef  De_Debug_h
	static const st_AgreenOn_Par2Type	CN_Ba_Order2Answer[]=
	{	
		{	De_Dev_Order_GetSeverComPar,De_AgreeOn_SendOrder_Answer_No},		//��ȡ������ͨѶ����
		{	De_Dev_Order_Login,De_AgreeOn_SendOrder_Answer_No},				//��λ�ն˵�¼
		{	De_Dev_Order_Sleep,De_AgreeOn_SendOrder_Answer_No},				//��λ�ն�����
		{	De_Dev_Order_CloseModerm,De_AgreeOn_SendOrder_Answer_No},			//��λ�ն˹ػ�
		{	De_Dev_Order_Answer,De_AgreeOn_SendOrder_Answer_No},				//��λ�ն�����Ӧ��
		{	De_Dev_Order_Orientation,De_AgreeOn_SendOrder_Answer_No},			//�ϴ�λ����Ϣ
		{	De_Dev_Order_Menum,De_AgreeOn_SendOrder_Answer_No},				//�ϴ��˵���Ϣ
		{	De_Dev_Order_TxtMenum,De_AgreeOn_SendOrder_Answer_No},				//�ϴ����˵��ķ�����Ϣ
		{	De_Dev_Order_LookPar,De_AgreeOn_SendOrder_Answer_No},				//�ϴ���λ�ն������̼�״̬
		{	De_Dev_Order_UpdateSoftWare,De_AgreeOn_SendOrder_Answer_No},		//�ϴ��������״̬
		{	De_Dev_Order_Waring,De_AgreeOn_SendOrder_Answer_No},				//�ϴ�����״̬

		{	De_Dev_Order_UploaderJpg1,De_AgreeOn_SendOrder_Answer_No},			//�ϴ���Ƭһ
		{	De_Dev_Order_UploaderJpg2,De_AgreeOn_SendOrder_Answer_No},			//�ϴ���Ƭ��
		{	De_Dev_Order_TabelList,De_AgreeOn_SendOrder_Answer_No},			//��
		{	De_Dev_Order_UploaderPar,De_AgreeOn_SendOrder_Answer_No},			//�ϴ�����
		{	De_Dev_Order_UploaderLog,De_AgreeOn_SendOrder_Answer_No},			//�ϴ���־�ļ�
		{	De_Dev_Order_UpLoaderWarning,De_AgreeOn_SendOrder_Answer_No},		//�ϴ���������

		{	De_Dev_Order_OutRoadMap,De_AgreeOn_SendOrder_Answer_No},			//�������򱨾�
		{	De_Dev_Order_UpLoaderReduce,De_AgreeOn_SendOrder_Answer_No},		//�ϴ�ѹ������
		{	De_Dev_Order_UpLoaderDriver,De_AgreeOn_SendOrder_Answer_No},		//�ϴ���ʻԱID
		{	De_Dev_Order_UpLoaderHandMess,De_AgreeOn_SendOrder_Answer_No},		//�ϴ��ֻ�����
		{	De_Dev_Order_NoSem,De_AgreeOn_SendOrder_Answer_No},				//ä��������Ϣ

		{	De_Dev_UpLoaderFrom,De_AgreeOn_SendOrder_Answer_No},				//�ϴ�����������Ϣ
		{	De_Dev_OverFromErro,De_AgreeOn_SendOrder_Answer_No},				//�ϴ�����δ�����ԭ��
		{	De_Dev_PriceData,De_AgreeOn_SendOrder_Answer_No},					//�ϴ��Ƽ�����Ϣ
	};

#else
	static const st_AgreenOn_Par2Type	CN_Ba_Order2Answer[]=
	{	
		{	De_Dev_Order_GetSeverComPar,De_AgreeOn_SendOrder_Answer_Yes},		//��ȡ������ͨѶ����
		{	De_Dev_Order_Login,De_AgreeOn_SendOrder_Answer_Yes},				//��λ�ն˵�¼
		{	De_Dev_Order_Sleep,De_AgreeOn_SendOrder_Answer_Yes},				//��λ�ն�����
		{	De_Dev_Order_CloseModerm,De_AgreeOn_SendOrder_Answer_Yes},			//��λ�ն˹ػ�
		{	De_Dev_Order_Answer,De_AgreeOn_SendOrder_Answer_No},				//��λ�ն�����Ӧ��
		{	De_Dev_Order_Orientation,De_AgreeOn_SendOrder_Answer_No},			//�ϴ�λ����Ϣ
		{	De_Dev_Order_Menum,De_AgreeOn_SendOrder_Answer_Yes},				//�ϴ��˵���Ϣ
		{	De_Dev_Order_TxtMenum,De_AgreeOn_SendOrder_Answer_Yes},				//�ϴ����˵��ķ�����Ϣ
		{	De_Dev_Order_LookPar,De_AgreeOn_SendOrder_Answer_Yes},				//�ϴ���λ�ն������̼�״̬
		{	De_Dev_Order_UpdateSoftWare,De_AgreeOn_SendOrder_Answer_Yes},		//�ϴ��������״̬
		{	De_Dev_Order_Waring,De_AgreeOn_SendOrder_Answer_Yes},				//�ϴ�����״̬

		{	De_Dev_Order_UploaderJpg1,De_AgreeOn_SendOrder_Answer_Yes},			//�ϴ���Ƭһ
		{	De_Dev_Order_UploaderJpg2,De_AgreeOn_SendOrder_Answer_Yes},			//�ϴ���Ƭ��
		{	De_Dev_Order_TabelList,De_AgreeOn_SendOrder_Answer_Yes},			//��
		{	De_Dev_Order_UploaderPar,De_AgreeOn_SendOrder_Answer_No},			//�ϴ�����
		{	De_Dev_Order_UploaderLog,De_AgreeOn_SendOrder_Answer_Yes},			//�ϴ���־�ļ�
		{	De_Dev_Order_UpLoaderWarning,De_AgreeOn_SendOrder_Answer_No},		//�ϴ���������

		{	De_Dev_Order_OutRoadMap,De_AgreeOn_SendOrder_Answer_Yes},			//�������򱨾�
		{	De_Dev_Order_UpLoaderReduce,De_AgreeOn_SendOrder_Answer_Yes},		//�ϴ�ѹ������
		{	De_Dev_Order_UpLoaderDriver,De_AgreeOn_SendOrder_Answer_Yes},		//�ϴ���ʻԱID
		{	De_Dev_Order_UpLoaderHandMess,De_AgreeOn_SendOrder_Answer_Yes},		//�ϴ��ֻ�����
		{	De_Dev_Order_NoSem,De_AgreeOn_SendOrder_Answer_Yes},				//ä��������Ϣ

		{	De_Dev_UpLoaderFrom,De_AgreeOn_SendOrder_Answer_Yes},				//�ϴ�����������Ϣ
		{	De_Dev_OverFromErro,De_AgreeOn_SendOrder_Answer_Yes},				//�ϴ�����δ�����ԭ��
		{	De_Dev_PriceData,De_AgreeOn_SendOrder_Answer_Yes},					//�ϴ��Ƽ�����Ϣ
	};
#endif
#else
	extern const st_AgreenOn_Par2Type	CN_Ba_st_AgreenOn_Par2Type[De_CN_Ba_st_AgreenOn_Par2Type_Number];
	extern const uint16  CN_Ba_WordPar[De_CN_Ba_WordPar_Number];
	extern const uint16 CN_Ba_LessPar[De_CN_Ba_LessPar_Number];


#endif
