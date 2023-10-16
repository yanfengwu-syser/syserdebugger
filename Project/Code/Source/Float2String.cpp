#include "StdAfx.h"
#include "Float2String.h"


LONGLONG pwr(int a, int b)
{
	LONGLONG i = 0, val = 1;

	for(i=0; i<b; i++)
	{
		val *= a;
	}

	return val;
}

void GetDisplayString(char *str, ULONGLONG frac, 
						int exp, char sign, char flag)
{
	int mantissa_bits = 0, i = 0;
	int exp_max = 0;
	ULONGLONG tmp = 100000000, tmp1, integral = 1, mantissa = 0; 
	ULONGLONG bit_mask = 0;


	//Initialize for calculating the integral value
	if(flag == GET_FLOAT)
	{
		exp_max = FLOAT_EXP_MAX;
		mantissa_bits = FLOAT_MANTISSA_BITS;
		bit_mask = pwr(2, FLOAT_MANTISSA_MSBIT);
	}
	else if(flag == GET_DOUBLE)
	{
		exp_max = DOUBLE_EXP_MAX;
		mantissa_bits = DOUBLE_MANTISSA_BITS;
		bit_mask = pwr(2, DOUBLE_MANTISSA_MSBIT);
	}
	else 
	{
		exp_max = LONG_DOUBLE_EXP_MAX;
		mantissa_bits = LONG_DOUBLE_MANTISSA_BITS;
		bit_mask = pwr(2, LONG_DOUBLE_MANTISSA_MSBIT);
	}

	if(exp == exp_max)
	{
		sprintf(str, " = %cInfiniti", (sign ? '-' : ' '));
		return;
	}
	else if(exp > 0)
	{
		if(exp > 31)
		{
			sprintf(str, " >= 2^31 !!");
			return;
		}
		else
			integral <<= exp;
	}
	else if(exp < 0)
	{
		if(flag == GET_FLOAT)
			frac |= (1 << FLOAT_MANTISSA_BITS);
		else if(flag == GET_DOUBLE)
			frac |= ((ULONGLONG)1 << DOUBLE_MANTISSA_BITS);
		else 
			frac |= ((ULONGLONG)1 << LONG_DOUBLE_MANTISSA_BITS);

		frac >>= (-exp);
	}
		
	for(i=1; i<=mantissa_bits; i++, bit_mask /= 2)
	{
		if(i > exp)
		{
			tmp = (tmp/2);
			mantissa += (((frac & bit_mask) >> (mantissa_bits -i)) * tmp);
		}
		else
		{
			if(exp <= mantissa_bits)
				tmp1 = ((frac & bit_mask) >> (mantissa_bits - exp));
			else
				tmp1 = ((frac & bit_mask) << (exp - mantissa_bits));

			integral |= tmp1;
		}
	}

	if((exp > 0) && (exp < exp_max))
		//integral part should be converted for long long type
		//sprintf(str, " = %c%llu.%08u", (sign ? '-' : ' '), 
		TSPrintf(str, " = %c%u.%08u", (sign ? '-' : ' '), 
						(unsigned long)integral, (unsigned long)mantissa);
	else if(exp == 0)
		TSPrintf(str, " = %c1.%08u", (sign ? '-' : ' '), mantissa);
	else if(exp < 0)
		TSPrintf(str, " = %c0.%08u", (sign ? '-' : ' '), mantissa);
}


void Hex2Float(char *str, unsigned long addr)
{
	ULONGLONG frac;
	unsigned char a, b;
	int exp;
	char sign;
	char* tmpptr=*(char**)&addr;
	a = *((tmpptr+3));
	b = *((tmpptr+2));

	//Get the sign , exponent, significand fraction
	sign = (a & 0x80) >> 7;

	exp = (a & 0x7F);
	exp <<= 1;
	exp |= ((b & 0x80) >> 7);
	exp -= (FLOAT_EXP_MAX-1);

	memcpy(&frac, (void *)tmpptr, 4);
	frac &= 0x7FFFFF;

	GetDisplayString(str, frac, exp, sign, GET_FLOAT);
}

void Hex2Double(char *str, unsigned long addr)
{
	int exp;
	unsigned char a, b;
	char sign;
	ULONGLONG frac;
char* tmpptr=*(char**)&addr;
	a = *((char *)(tmpptr+7));
	b = *((char *)(tmpptr+6));

	//Get the sign , exponent, significand fraction
	sign = (a & 0x80) >> 7;
	
	exp = (a & 0x7F);
	exp <<= 4;
	exp	|= ((b & 0xF0) >> 4);
	exp -= (DOUBLE_EXP_MAX-1);

	memcpy(&frac, (void *)tmpptr, 8);
	frac &= 0x000FFFFFFFFFFFFF;

	GetDisplayString(str, frac, exp, sign, GET_DOUBLE);
}

void Hex2LongDouble(char *str, unsigned long addr)
{
	int exp;
	unsigned char a, b;
	char sign;
	ULONGLONG frac;
char* tmpptr=*(char**)&addr;
	a = *((char *)(tmpptr+9));
	b = *((char *)(tmpptr+8));

	//Get the sign , exponent, significand fraction
	sign = (a & 0x80) >> 7;
	
	exp = (a & 0x7F);
	exp <<= 8;
	exp	|= b;
	exp -= (LONG_DOUBLE_EXP_MAX-1);

	memcpy(&frac, (void *)tmpptr, 8);

	GetDisplayString(str, frac, exp, sign, GET_LONG_DOUBLE);
}
typedef union
{
	float value;
	struct
	{
		unsigned int fraction:23;
		unsigned int exponent:8;
		unsigned int sign:1;
	} ;
	unsigned int val;
} myieee_float_shape_type;

int ftype(float value)
{
	myieee_float_shape_type fval;
	fval.value=value;
	if(fval.val==0)
		return POSITIVE_ZERO;
	if(fval.val==0x80000000)
		return NEGATIVE_ZERO;
	if(fval.fraction==0 && fval.exponent==255 && fval.sign==0)
		return POSITIVE_INDEFINITE;
	if(fval.fraction==0 && fval.exponent==255 && fval.sign==1)
		return NEGATIVE_INDEFINITE;
	if(fval.exponent==255 && (fval.fraction & 0x400000)==0)
		return SNAN;
	if(fval.exponent==255 && (fval.fraction & 0x400000)==1)
		return QNAN;
	if(fval.exponent==255 && fval.fraction==0x400000)
		return QNAN_INDEFINITE;
	if(fval.exponent>=1 && fval.exponent <=254 && fval.sign==0)
		return POSITIVE_NORMALS;
	if(fval.exponent>=1 && fval.exponent <=254 && fval.sign==1)
		return NEGITIVE_NORMALS;
	if(fval.exponent==0 && fval.fraction && fval.sign==0)
		return POSITIVE_DENORMALS;
	if(fval.exponent==0 && fval.fraction && fval.sign==1)
		return NEGITIVE_DENORMALS;
	return UNKNOW_FLOAT_NUMBER;
}
typedef union
{
	double value;
	struct
	{
		unsigned int fractionl;
		unsigned int fractionh:20;
		unsigned int exponent:11;
		unsigned int sign:1;
	} ;
	unsigned __int64 val;
} myieee_double_shape_type;

int ftype(double value)
{
	myieee_double_shape_type fval;
	fval.value=value;
	if(fval.val==0)
		return POSITIVE_ZERO;
	if(fval.val==0x8000000000000000I64)
		return NEGATIVE_ZERO;
	if(fval.fractionl==0 &&fval.fractionh==0 && fval.exponent==0x7ff && fval.sign==0)
		return POSITIVE_INDEFINITE;
	if(fval.fractionl==0 &&fval.fractionh==0 && fval.exponent==0x7ff && fval.sign==1)
		return NEGATIVE_INDEFINITE;
	if(fval.exponent==0x7ff && (fval.fractionh & 0x80000)==0)
		return SNAN;
	if(fval.exponent==0x7ff && (fval.fractionh & 0x80000)==1)
		return QNAN;
	if(fval.exponent==0x7ff && fval.fractionh ==0x80000 && fval.fractionl==0)
		return QNAN_INDEFINITE;
	if(fval.exponent>=1 && fval.exponent <0x7ff && fval.sign==0)
		return POSITIVE_NORMALS;
	if(fval.exponent>=1 && fval.exponent <0x7ff && fval.sign==1)
		return NEGITIVE_NORMALS;
	if(fval.exponent==0 && (fval.fractionh || fval.fractionl) && fval.sign==0)
		return POSITIVE_DENORMALS;
	if(fval.exponent==0 && (fval.fractionh || fval.fractionl) && fval.sign==1)
		return NEGITIVE_DENORMALS;
	return UNKNOW_FLOAT_NUMBER;
}



int ftype(myieee_long_double_shape_type fval)
{
	if(fval.fractionl==0 && fval.fractionh==0 && fval.sign==0 && fval.exponent==0 &&fval.integer==0)
		return POSITIVE_ZERO;
	if(fval.fractionl==0 && fval.fractionh==0 && fval.sign==1 && fval.exponent==0 &&fval.integer==0)
		return NEGATIVE_ZERO;
	if(fval.fractionl==0 &&fval.fractionh==0 && fval.exponent==0x7fff && fval.sign==0&&fval.integer==1)
		return POSITIVE_INDEFINITE;
	if(fval.fractionl==0 &&fval.fractionh==0 && fval.exponent==0x7fff && fval.sign==1 &&fval.integer==1)
		return NEGATIVE_INDEFINITE;
	if(fval.exponent==0x7fff && (fval.fractionh & 0x40000000)==0 &&fval.integer==1)
		return SNAN;
	if(fval.exponent==0x7fff && (fval.fractionh & 0x40000000)==1 &&fval.integer==1)
		return QNAN;
	if(fval.exponent==0x7fff && fval.fractionh==0x40000000 && fval.fractionl==0 &&fval.integer==1)
		return QNAN_INDEFINITE;
	if(fval.exponent>=1 && fval.exponent <0x7fff && fval.sign==0&&fval.integer==1)
		return POSITIVE_NORMALS;
	if(fval.exponent>=1 && fval.exponent <0x7fff && fval.sign==1&&fval.integer==1)
		return NEGITIVE_NORMALS;
	if(fval.exponent==0 && (fval.fractionh || fval.fractionl) && fval.sign==0&&fval.integer==0)
		return POSITIVE_DENORMALS;
	if(fval.exponent==0 && (fval.fractionh || fval.fractionl) && fval.sign==1&&fval.integer==0)
		return NEGITIVE_DENORMALS;
	return UNKNOW_FLOAT_NUMBER;
}