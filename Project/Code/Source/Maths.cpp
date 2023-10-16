#include "StdAfx.h"
#include "Maths.h"

NAME_SPACE_BEGIN

DWORD Mul64(DWORD MulN1Low,DWORD MulN2Low,DWORD*ResHigh)
{
	DWORD MulResHigh,MulResLow,MulN1High;
	MulN1High = MulResHigh = MulResLow = 0;
	while(MulN2Low!=0)
	{
		if(MulN2Low&1)
		{
			if((DWORD)(MulResLow + MulN1Low) < MulResLow )
			{
				MulResLow += MulN1Low;
				MulResHigh += MulN1High+1;
			}
			else
			{
				MulResLow += MulN1Low;
				MulResHigh += MulN1High;
			}
		}
		MulN1High=(MulN1High<<1)+(MulN1Low>>0x1F);
		MulN1Low =(MulN1Low<<1);
		MulN2Low =(MulN2Low>>1);
	}
	*ResHigh=MulResHigh;
	return MulResLow;
}
DWORD Mul64(int Num1,int Num2,int*ResHigh)
{
	int MulResHigh,Sign;
	DWORD MulResLow;
	if(Num1 == 0 || Num2 == 0)
	{
		*ResHigh = 0;
		return 0;
	}
	if(Num1 < 0 && Num2<0)
	{
		Num1 = -Num1;
		Num2 = -Num2;
		Sign = 1;
	}
	else if(Num1 > 0 && Num2 > 0)
	{
		Sign = 1;
	}
	else if(Num1 < 0 && Num2 > 0)
	{
		Num1 = -Num1;
		Sign = -1;
	}
	else if(Num1 > 0 && Num2 < 0)
	{
		Num2 = -Num2;
		Sign = -1;
	}
	MulResLow  = Mul64((DWORD)Num1,(DWORD)Num2,(DWORD*)&MulResHigh);
	if(Sign==-1)
	{
		MulResLow = ~MulResLow;
		MulResHigh = ~MulResHigh;
		if(MulResLow+1<MulResLow)
		{
			MulResLow++;
			MulResHigh++;
		}
		else
		{
			MulResLow++;
		}
	}
	*ResHigh = MulResHigh;
	return MulResLow;
}
void Neg64(DWORD*NumLow,int*NumHigh)
{
	*NumLow = ~*NumLow;
	*NumHigh = ~*NumHigh;
	if(*NumLow+1<*NumLow)
	{
		*NumLow++;
		*NumHigh++;
	}
	else
	{
		*NumLow++;
	}
}

bool Div64(DWORD *NumLow,DWORD *NumHigh,DWORD DivisorLow,DWORD*ResLow,DWORD*ResHigh)
{
	DWORD DivResLow,DivResHigh,DivisorHigh, i;
	if(DivisorLow == 0)
		return false;
	DivisorHigh = DivisorLow;
	DivisorLow = DivResLow = DivResHigh = 0;
	
	for( i=0;DivisorHigh<0x80000000 && i<0x1F;i++)
		DivisorHigh<<=1;
	for(i+=0x20;i!=-1;i--)
	{
		if(*NumHigh>DivisorHigh)
		{
			if(*NumLow>=DivisorLow)
			{
				*NumLow-=DivisorLow;
				*NumHigh-=DivisorHigh;
			}
			else
			{
				*NumLow-=DivisorLow;
				*NumHigh-=DivisorHigh+1;
			}
			DivResLow++;
		}
		else if(*NumHigh==DivisorHigh&&*NumLow>=DivisorLow)
		{
			*NumLow-=DivisorLow;
			*NumHigh-=DivisorHigh;
			DivResLow++;
		}
		if(i==0)
			break;
		DivisorLow=(DivisorLow>>1)+(DivisorHigh<<0x1F);
		DivisorHigh>>=1;
		DivResHigh=(DivResHigh<<1)+(DivResLow>>0x1F);
		DivResLow<<=1;
	}
	*ResHigh = DivResHigh;
	*ResLow = DivResLow;
	if(DivResHigh>0)
		return false;
	return true;
}
bool Div64(DWORD*NumLow,int*NumHigh,int DivisorLow,DWORD*ResLow,int*ResHigh)
{
	int Sign;
	if(DivisorLow==0)
		return false;
	if(*NumHigh<=0 && DivisorLow<0)
	{
		Sign = 1;
		Neg64(NumLow,NumHigh);
		DivisorLow = -DivisorLow;
	}
	else if(*NumHigh>=0 && DivisorLow>0)
	{
		Sign = 1;
	}
	else if(*NumHigh>=0 && DivisorLow<0)
	{
		Sign = -1;
		DivisorLow = -DivisorLow;
	}
	else if(*NumHigh<=0 && DivisorLow>0)
	{
		Sign = -1;
		Neg64(NumLow,NumHigh);
	}
	if(Div64(NumLow,(DWORD*)NumHigh,DivisorLow,ResLow,(DWORD*)ResHigh)==false)
		return false;
	if(*ResLow & 0x80000000)
		return false;
	if(Sign==-1)
	{
		Neg64(ResLow,ResHigh);
	}
	return true;
}
LONG Pow(INT a,INT n)
{
	LONG Result;
	if(n==0)
		return 1;
	Result=n;
	do
	{		
		n--;
		Result*=n;
	}while(n);
	return Result;
}
NAME_SPACE_END
