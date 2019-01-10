#include "..\..\Public_H\DePublic.h"
#ifdef De_Compiler_miscellaneous_Date
/*===============================Include File==========================================*/
	#include "..\..\APP\config.h"
	#include "stdlib.h"
	#ifdef De_Date_Compiler
		#include "..\..\miscellaneous\CodeTrans\AscNumber.h"
	#endif
/*==============================Function Data==========================================*/
	typedef struct
	{   uint16 (* Juge)(uint8 *Buf,uint8 Type);  				//�жϺ���
	    uint16 (* Next)(uint8 *Buf,uint8 Type);  				//��һ��ʱ��
	    uint16 (* Back)(uint8 *Buf,uint8 Type);					//��һ��ʱ��
		uint16 (*GetWeek)(uint8 *NonceDate);
	}st_Fun_Date;
/*==============================Define	Data===========================================*/
	
	
	#define De_Suc_Date                             0							//��ҳ�ɹ�����
	/*++++++++++++++++++++++++++++++++�������һ����++++++++++++++++++++++++++++*/
	                             													//��,H����ʼ
	#define De_Erro_Date_Hex2BCD                    De_Erro_Date                  //ʮ������תBCD����
	#define De_Erro_Date_JugeDate                   De_Erro_Date_Hex2BCD+1       //���ڴ���
	#define De_Erro_Date_JugeHour                   De_Erro_Date_JugeDate+1      //Сʱ����
	#define De_Erro_Date_JugeMinute                 De_Erro_Date_JugeHour+1      //�ִ��� 
	#define De_Erro_Date_JugeSecond                 De_Erro_Date_JugeMinute+1    //����� 
	
	
	/*++++++++++++++++++++++++++++++��������+++++++++++++++++++++++++++++++++++*/
	
	#define De_Type_Date_Date                       1                             //����Ϊ����
	#define De_Type_Date_Hour                       De_Type_Date_Date+1           //����Ϊ��ȷ��Сʱ
	#define De_Type_Date_Minute                     De_Type_Date_Hour+1           //���;�ȷ����
	#define De_Type_Date_Second                     De_Type_Date_Minute+1         //���;�ȷ����

	       
/*==============================Static Function========================================================*/
	#ifdef	De_Date_Compiler      
		  
		static uint16 Juge(uint8 *Buf,uint8 Type);      //ʱ���жϺ���
		static uint16 Next(uint8 *Buf,uint8 Type);      //��һ��ʱ��
		static uint16 Back(uint8 *Buf,uint8 Type);      //��һ��ʱ��
		static uint16 GetWeek(uint8 *NonceDate);
		
		static uint16 JugeDate(uint8 *Buf);
		static uint16 JugeHour(uint8 Byte);
		static uint16 JugeMinute(uint8 Byte);
		static uint16 JugeSecond(uint8 Byte);
		
		static void NextDate(uint8 *Buf);
		static void NextHour(uint8 *Buf);
		static void NextMinute(uint8 *Buf);
		static void NextSecond(uint8 *Buf);
		
		static void BackDate(uint8 *Buf);
		static void BackHour(uint8 *Buf);
		static void BackMinute(uint8 *Buf);
		static void BackSecond(uint8 *Buf);
		
		static void Bcd2Hex(uint8 *BcdBuf,uint8 *HexBuf,uint8 SizeofBcdBuf );
		static uint8 Hex2Bcd(uint8 *HexBuf,uint8 *BcdBuf,uint8 SizeofHexBuf);
		
		
/*===============================================�������=======================================*/
		const st_Fun_Date       CN_st_Fun_Date={Juge,Next,Back,GetWeek};
	#else
		extern st_Fun_Date	CN_st_Fun_Date;	
	#endif
#endif

/*                        End Date.h											*/

