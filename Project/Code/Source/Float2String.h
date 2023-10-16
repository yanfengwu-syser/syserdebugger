#ifndef _FLOAT2STRING_H_
#define _FLOAT2STRING_H_

#define FLOAT_MANTISSA_MSBIT 22
#define DOUBLE_MANTISSA_MSBIT 51
#define LONG_DOUBLE_MANTISSA_MSBIT 62

#define FLOAT_MANTISSA_BITS 23
#define DOUBLE_MANTISSA_BITS 52
#define LONG_DOUBLE_MANTISSA_BITS 63

#define FLOAT_EXP_MAX 128
#define DOUBLE_EXP_MAX 1024
#define LONG_DOUBLE_EXP_MAX 16384

#define GET_FLOAT 1
#define GET_DOUBLE 2
#define GET_LONG_DOUBLE 3
void Hex2Float(char *str, unsigned long addr);
void Hex2Double(char *str, unsigned long addr);
void Hex2LongDouble(char *str, unsigned long addr);

enum{
	POSITIVE_ZERO,
	NEGATIVE_ZERO,   
	POSITIVE_INDEFINITE,
	NEGATIVE_INDEFINITE,
	SNAN,
	QNAN,
	QNAN_INDEFINITE,
	POSITIVE_NORMALS,
	NEGITIVE_NORMALS,
	POSITIVE_DENORMALS,
	NEGITIVE_DENORMALS,
	UNKNOW_FLOAT_NUMBER,
};

typedef union
{
	long double value;
	struct
	{
		unsigned int fractionl;
		unsigned int fractionh:31;
		unsigned int integer:1;
		unsigned int exponent:15;
		unsigned int sign:1;
		unsigned int empty:16;
	} ;
} myieee_long_double_shape_type;

int ftypef(myieee_long_double_shape_type fval);
int ftyped(double value);
int ftypeld(float value);
#endif //_FLOAT2STRING_H_