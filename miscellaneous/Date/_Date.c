#define De_Date_Compiler						//编译函数体   

#include "Date.h"


static uint16 Juge(uint8 *Buf,uint8 Type)    	//时间判断函数                          
{     uint16 Erro;
      if(CN_st_Fun_AscNumber.JugeHexBcd(Buf,3+Type)!=0)
	  		return De_Erro_Date_JugeDate;
	  if((Erro=JugeDate(Buf))!=De_Suc_Date)
            return Erro;
      if(Type==De_Type_Date_Date)
            return De_Suc_Date;
      if((Erro=JugeHour(Buf[4]))!=De_Suc_Date)
            return Erro;
      if(Type==De_Type_Date_Hour)
            return De_Suc_Date;
      if((Erro=JugeMinute(Buf[5]))!=De_Suc_Date)
            return Erro;
      if(Type==De_Type_Date_Minute)
            return De_Suc_Date;    
      if((Erro=JugeSecond(Buf[6]))!=De_Suc_Date)
            return Erro;
      return De_Suc_Date;           
}

static uint16 Next(uint8 *Buf,uint8 Type) //下一个时间
{     uint16 Erro;
      if((Erro=Juge(Buf,Type))!=De_Suc_Date)
            return Erro;
      if(Type==De_Type_Date_Date)
            NextDate(Buf);
      else if(Type==De_Type_Date_Hour)
            NextHour(Buf);      
      else if(Type==De_Type_Date_Minute)
            NextMinute(Buf);   
      else
            NextSecond(Buf);           
      return De_Suc_Date;
}

static uint16 Back(uint8 *Buf,uint8 Type) //上一个时间
{     uint16 Erro;
      if((Erro=Juge(Buf,Type))!=De_Suc_Date)
            return Erro;
      if(Type==De_Type_Date_Date)
            BackDate(Buf);
      else if(Type==De_Type_Date_Hour)
            BackHour(Buf);      
      else if(Type==De_Type_Date_Minute)
            BackMinute(Buf);   
      else
            BackSecond(Buf);           
      return De_Suc_Date;
}

static uint16 GetWeek(uint8 *NonceDate)
{	uint8 InitDate[4];
    uint16 i; 
    uint8 j;
	if(JugeDate(NonceDate)!=De_Suc_Date)
 		return 0;
	InitDate[0]=0x20;InitDate[1]=0x06;InitDate[2]=0x01;InitDate[3]=0x01; 
   	if(CN_st_Fun_AscNumber.CompareVa(InitDate,NonceDate,4,De_AscNumber_Va_Big)!=De_AscNumber_Va_Flase)
   	{	for(i=0;;i++)
        {	if(CN_st_Fun_AscNumber.CompareBuf(InitDate,NonceDate,4)==0)
             	break;    
              NextDate(NonceDate);
        }
   	} 
   else
   {    for(i=0;;i++)
        {     if(CN_st_Fun_AscNumber.CompareBuf(InitDate,NonceDate,4)==0)
                  break;    
              NextDate(InitDate);
        }
   } 
   j=(i%7);
   if(j==0)
        j=7; 
   return j; 
}

/*=======================================以下为静态函数==================================================*/
static uint16 JugeDate(uint8 *Buf)
{     uint8 BufHex[4];
      uint16 Year;
      Bcd2Hex(Buf,BufHex,sizeof(BufHex));
      Year=BufHex[0]*100+BufHex[1];
      if(Year&0x03)
            Year=1;
      else
            Year=0;        
      if((BufHex[3]>31)||(BufHex[0]!=20)||(BufHex[2]>12)||(BufHex[2]==0)||(BufHex[3]==0))    //不符合习惯
              return De_Erro_Date_JugeDate;        
      if(((BufHex[2]==4)||(BufHex[2]==6)||(BufHex[2]==9)||(BufHex[2]==11))&&(BufHex[3]>30))
              return De_Erro_Date_JugeDate;
      if(((BufHex[2]==1)||(BufHex[2]==3)||(BufHex[2]==5)||(BufHex[2]==7)||(BufHex[2]==8)||
      		(BufHex[2]==12)||(BufHex[2]==10))&&(BufHex[3]>31))
              return De_Erro_Date_JugeDate;
      if((BufHex[2]==2)&&(BufHex[3]>28)&&(Year==1))
              return De_Erro_Date_JugeDate; 
      if((BufHex[2]==2)&&(BufHex[3]>29)&&(Year==0))
              return De_Erro_Date_JugeDate;     
      return De_Suc_Date; 
}


static uint16 JugeHour(uint8 Byte)
{     
      if(Byte>0x23)
            return De_Erro_Date_JugeHour;
      return De_Suc_Date;      
}

static uint16 JugeMinute(uint8 Byte)
{     
      if(Byte>0x59)
            return De_Erro_Date_JugeMinute;
      return De_Suc_Date;
}

static uint16 JugeSecond(uint8 Byte)
{     
      if(Byte>0x59)
            return De_Erro_Date_JugeSecond;
      return De_Suc_Date;
}





static void NextDate(uint8 *Buf)
{     uint8 BufHex[4];
      uint16 Year;
      Bcd2Hex(Buf,BufHex,sizeof(BufHex));
      BufHex[3]+=1;//day+1;
      if((BufHex[3]==31)&&((BufHex[2]==4)||(BufHex[2]==6)||(BufHex[2]==9)||(BufHex[2]==11)))
      {	    BufHex[2]+=1;
            BufHex[3]=1;
      }                                                                 //上次是月底
      else if((BufHex[3]==32)&&((BufHex[2]==1)||(BufHex[2]==3)||(BufHex[2]==5)||(BufHex[2]==7)
      ||(BufHex[2]==8)||(BufHex[2]==12)||(BufHex[2]==10)))	
      {     BufHex[2]+=1;
	    if(BufHex[2]==13)                                        //超过12月
	    {	  BufHex[2]=1;                                     //month
		  BufHex[1]+=1;                                    //year			
	    }
	    BufHex[3]=1;
      }
      else if((BufHex[3]==29)&&(BufHex[2]==2))
      {     Year=BufHex[0]*100+BufHex[1];
	    if((Year&0x03)!=0)                                        /*判断是不是闰年,不是闰年*/
	    {	  BufHex[2]=3;
		  BufHex[3]=1;		
	    }	
	}
      else if((BufHex[3]==30)&&(BufHex[2]==2))
      {	    BufHex[2]=3;
	    BufHex[3]=1;			
      }
      Hex2Bcd(BufHex,Buf,sizeof(BufHex));
}

static void NextHour(uint8 *Buf)
{     uint8 ByteV;
      Bcd2Hex(Buf+4,&ByteV,sizeof(ByteV));
      ByteV++;
      if(ByteV>23)
      {     NextDate(Buf);     
            Buf[4]=0x00;
      }
      else
      {     Hex2Bcd(&ByteV,Buf+4,sizeof(ByteV));
      }
}

static void NextMinute(uint8 *Buf)
{     uint8 ByteV;
      Bcd2Hex(Buf+5,&ByteV,sizeof(ByteV));
      ByteV++;    
      if(ByteV>59)
      {     NextHour(Buf);
            Buf[5]=00;
      }
      else
      {     Hex2Bcd(&ByteV,Buf+5,sizeof(ByteV));
      }
}

static void NextSecond(uint8 *Buf)
{     uint8 ByteV;
      Bcd2Hex(Buf+6,&ByteV,sizeof(ByteV));
      ByteV++;
      if(ByteV>59)
      {     NextMinute(Buf);
            Buf[6]=00;
      }
      else
      {     Hex2Bcd(&ByteV,Buf+6,sizeof(ByteV));
      }
}


static void BackDate(uint8 *Buf)
{     uint8 BufHex[4];
      uint16 Year;
      Bcd2Hex(Buf,BufHex,sizeof(BufHex));
      BufHex[3]--;
      if(BufHex[3]==0x00)
      {     BufHex[2]--;  
            if(BufHex[2]==0)
            {     if(BufHex[1]==0)
                  {     BufHex[0]--;    
                        BufHex[1]=0x99;
                  }
                  else
                        BufHex[1]--;                 
                  BufHex[2]=12;
                  BufHex[3]=31;
            }
            else
            {     if((BufHex[2]==4)||(BufHex[2]==6)||(BufHex[2]==9)||(BufHex[2]==11))       
                        BufHex[3]=30;
                  else if((BufHex[2]==1)||(BufHex[2]==3)||(BufHex[2]==5)||(BufHex[2]==7)
                  ||(BufHex[2]==8)||(BufHex[2]==12)||(BufHex[2]==10))	                              
                        BufHex[3]=31;
                  else if(BufHex[2]==2)
                  {     Year=BufHex[0]*100+BufHex[1];
                        if((Year&0x03)!=0)
                              BufHex[3]=28;
                        else 
                              BufHex[3]=29;              
                  }      
            }         
      }
      Hex2Bcd(BufHex,Buf,sizeof(BufHex));
}

static void BackHour(uint8 *Buf)
{     uint8 ByteV;
      Bcd2Hex(Buf+4,&ByteV,sizeof(ByteV));
      if(ByteV==0)
      {     BackDate(Buf);
            Buf[4]=0x23;
      }
      else
      {     ByteV--;
            Hex2Bcd(&ByteV,Buf+4,sizeof(ByteV));
      }      
}

static void BackMinute(uint8 *Buf)
{     uint8 ByteV;
      Bcd2Hex(Buf+5,&ByteV,sizeof(ByteV));
      if(ByteV==0)
      {     BackHour(Buf);
            Buf[5]=0x59;
      }
      else
      {     ByteV--;
            Hex2Bcd(&ByteV,Buf+5,sizeof(ByteV));
      }  
}

static void BackSecond(uint8 *Buf)
{     uint8 ByteV;
      Bcd2Hex(Buf+6,&ByteV,sizeof(ByteV));
      if(ByteV==0)
      {     BackMinute(Buf);
            Buf[6]=0x59;
      }
      else
      {     ByteV--;
            Hex2Bcd(&ByteV,Buf+6,sizeof(ByteV));
      } 
} 

static void Bcd2Hex(uint8 *BcdBuf,uint8 *HexBuf,uint8 SizeofBcdBuf)
{     uint8 i,Byte;
      for(i=0;i<SizeofBcdBuf;i++)
      {     Byte=(BcdBuf[i]>>4)*10+(BcdBuf[i]&0x0f);
            HexBuf[i]=Byte;
      }       
}

static uint8 Hex2Bcd(uint8 *HexBuf,uint8 *BcdBuf,uint8 SizeofHexBuf)
{     uint8 i;
      for(i=0;i<SizeofHexBuf;i++)
      {     if(HexBuf[i]>99)
                  return De_Erro_Date_Hex2BCD;
            BcdBuf[i]=(HexBuf[i]%10)+((HexBuf[i]/10)<<4);  
      }
      return De_Suc_Date;
}





