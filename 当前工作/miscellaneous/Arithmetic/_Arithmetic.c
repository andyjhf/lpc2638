#define De_Arithmetic_Compiler
#include "Arithmetic.h"
#ifdef De_Compiler_miscellaneous_Arithmetic
//　Creates non-inverted ECC code from line parity
static void nand_trans_result(uint8 reg2, uint8 reg3,uint8 *ecc_code)
{
	uint8 a, b, i, tmp1, tmp2;

	/* Initialize variables */
	a = b = 0x80;
	tmp1 = tmp2 = 0;

	/* Calculate first ECC byte */
	for (i = 0; i < 4; i++)
	{
		if (reg3 & a) /* LP15,13,11,9 --> ecc_code[0] */
			tmp1 |= b;
		b >>= 1;
		if (reg2 & a) /* LP14,12,10,8 --> ecc_code[0] */
			tmp1 |= b;
		b >>= 1;
		a >>= 1;
	}

	/* Calculate second ECC byte */
	b = 0x80;
	for (i = 0; i < 4; i++)
	{
		if (reg3 & a) /* LP7,5,3,1 --> ecc_code[1] */
			tmp2 |= b;
		b >>= 1;
		if (reg2 & a) /* LP6,4,2,0 --> ecc_code[1] */
			tmp2 |= b;
		b >>= 1;
		a >>= 1;
	}

	/* Store two of the ECC bytes */
	ecc_code[0] = tmp1;
	ecc_code[1] = tmp2;
}

//　Calculate 3 byte ECC code for 256 byte block
static void nand_calculate_ecc (const uint8 *dat, uint8 *ecc_code)
{
	uint8 idx, reg1, reg2, reg3;
	uint16 j;

	/* Initialize variables */
	reg1 = reg2 = reg3 = 0;
	ecc_code[0] = ecc_code[1] = ecc_code[2] = 0;

	/* Build up column parity */
	for(j = 0; j < 256; j++)
	{

	/* Get CP0 - CP5 from table */
		idx = nand_ecc_precalc_table[dat[j]];
		reg1 ^= (idx & 0x3f);

		/* All bit XOR = 1 ? */
		if (idx & 0x40) {
			reg3 ^= (uint8) j;
			reg2 ^= ~((uint8) j);
		}
	}

	/* Create non-inverted ECC code from line parity */
	nand_trans_result(reg2, reg3, ecc_code);

	/* Calculate final ECC code */
	ecc_code[0] = ~ecc_code[0];
	ecc_code[1] = ~ecc_code[1];
	ecc_code[2] = ((~reg1) << 2) | 0x03;
}

//　Detect and correct a 1 bit error for 256 byte block
static uint16 nand_correct_data (uint8 *dat, uint8 *read_ecc, uint8 *calc_ecc)
{
	uint8 a, b, c, d1, d2, d3, add, bit, i;

	/* Do error detection */
	d1 = calc_ecc[0] ^ read_ecc[0];
	d2 = calc_ecc[1] ^ read_ecc[1];
	d3 = calc_ecc[2] ^ read_ecc[2];

	if ((d1 | d2 | d3) == 0)
	{
	/* No errors */
		return 3;
	}
	else
	{
		a = (d1 ^ (d1 >> 1)) & 0x55;
		b = (d2 ^ (d2 >> 1)) & 0x55;
		c = (d3 ^ (d3 >> 1)) & 0x54;

	/* Found and will correct single bit error in the data */
		if ((a == 0x55) && (b == 0x55) && (c == 0x54))
		{
			c = 0x80;
			add = 0;
			a = 0x80;
			for (i=0; i<4; i++)
			{
				if (d1 & c)
					add |= a;
				c >>= 2;
				a >>= 1;
			}
			c = 0x80;
			for (i=0; i<4; i++)
			{
				if (d2 & c)
					add |= a;
				c >>= 2;
				a >>= 1;
			}
			bit = 0;
			b = 0x04;
			c = 0x80;
			for (i=0; i<3; i++)
			{
				if (d3 & c)
					bit |= b;
				c >>= 2;
				b >>= 1;
			}
			b = 0x01;
			a = dat[add];
			a ^= (b << bit);
			dat[add] = a;
			return 1;
		}
		else
		{
			i = 0;
			while (d1)
			{
				if (d1 & 0x01)
						++i;
				d1 >>= 1;
			}
			while (d2)
			{
				if (d2 & 0x01)
					++i;
				d2 >>= 1;
			}
			while (d3)
			{
				if (d3 & 0x01)
					++i;
				d3 >>= 1;
			}
			if (i == 1)
			{
				/* ECC Code Error Correction */
				read_ecc[0] = calc_ecc[0];
				read_ecc[1] = calc_ecc[1];
				read_ecc[2] = calc_ecc[2];
				return 2;
			}
			else
			{
				/* Uncorrectable Error */
				return 0;
			}
		}
	}

	/* Should never happen */
	return 0;
}


static uint16 Crc(uint8 *s,uint16 len,uint16 Value)                                               //16位的CRC校验       
{   uint16 acc,i;
	acc=Value;   
      while (len--)                              
      {     acc = acc ^ (*s++ << 8);                
            for (i = 0; i++ < 8;)                   
            {     if (acc & 0x8000)                 
                          acc = (acc << 1) ^ 0x8005;     
                  else
                          acc <<= 1;                     
            }
       }
      return  acc;                   
}

static uint8 CheckSum(uint8 *Buf,uint16 SizeofBuf)       //异或校验
{	uint16 i;
	uint8 Sum;
	for(i=0,Sum=0;i<SizeofBuf;i++)
		Sum^=Buf[i];
	return Sum;		   
}
static uint8 CheckAdd(uint8 *Buf,uint16 SizeofBuf,uint8 Value)
{	uint16 i;
	for(i=0;i<SizeofBuf;i++)
		Value+=Buf[i];	
	return Value;
}
static uint16 Crc1021(uint8 *s,uint16 len,uint16 Value)
{   uint16 acc,i;
	acc=Value;   
      while (len--)                              
      {     acc = acc ^ (*s++ << 8);                
            for (i = 0; i++ < 8;)                   
            {     if (acc & 0x8000)                 
                          acc = (acc << 1) ^ 0x1021;     
                  else
                          acc <<= 1;                     
            }
       }
      return  acc;                   
}

#endif


