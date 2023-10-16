#ifndef  _MATH_H_
#define  _MATH_H_

NAME_SPACE_BEGIN

DWORD	Mul64(DWORD NulN1Low,DWORD NulN2Low,DWORD*ResHigh);//64位无符号乘
DWORD	Mul64(int Num1,int Num2,int *ResHigh);//64位有符号乘
bool	Div64(DWORD*NumLow,DWORD*NumHigh,DWORD DivisorLow,DWORD*ResLow,DWORD*ResHigh);//64位无符号除
bool	Div64(DWORD*NumLow,int*NumHigh,int DivisorLow,DWORD*ResLow,int*ResHigh);//64位有符号除
void	Neg64(DWORD*NumLow,int*NumHigh);//64位取负数
LONG	Pow(INT a,INT n);

NAME_SPACE_END

#endif

