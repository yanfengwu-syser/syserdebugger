/////////////////////////////////////////////////////////////////////////
// $Id: mult32.cc,v 1.6 2001/10/03 13:10:37 bdenney Exp $
/////////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "x86cpu.h"


//-----------------------------------------------------

#if (HOST_CPU_IS_I80386==0)

void MultiplyBit64(X86_CPU_INT64 *result,Bit32u src,Bit32u dst)
{
	Bit32u temp0_l,temp0_h;
	Bit32u temp1_l,temp1_h;
	Bit32u temp2_l,temp2_h;

	temp1_l = src;
	temp2_l = dst;
	
	temp0_l=temp0_h=temp1_h=temp2_h=0;
	
	while(temp2_l!=0)
	{
		if (temp2_l&0x1) 
		{
			if ((Bit32u)(temp0_l+temp1_l)<temp0_l) 
			{
				temp0_l=temp0_l+temp1_l;
				temp0_h=temp0_h+temp1_h+0x1;
			}
			else 
			{
				temp0_l=temp0_l+temp1_l;
				temp0_h=temp0_h+temp1_h;
			}
		}
		temp1_h=(temp1_h<<1)+(temp1_l>>0x1f);
		temp1_l =(temp1_l<<1);
		temp2_l =(temp2_l>>1);
	}
	
	result->l32 = temp0_l;
	result->h32 = temp0_h;
}

void DivideBit64(X86_CPU_INT64 *source,Bit32u dst,X86_CPU_INT64 *result)
{
	int i;
	Bit32u temp0_l,temp0_h;
	Bit32u temp1_l,temp1_h;
	Bit32u temp2_l,temp2_h;
	
	temp0_l = source->l32;
	temp0_h = source->h32;
	
	temp1_l = dst;
	
	temp1_h=temp1_l;	
	temp1_l=temp2_l=temp2_h=0;	
	
	for (i=0;temp1_h<0x80000000&&i<0x1f;i++)
		temp1_h=temp1_h<<1;
	
	for (i=i+0x20;i>=0;i--)
	{
		if (temp0_h>temp1_h)
		{
			if (temp0_l>=temp1_l)
			{
				temp0_l=temp0_l-temp1_l;
				temp0_h=temp0_h-temp1_h;
			}
			else
			{
				temp0_l=temp0_l-temp1_l;
				temp0_h=temp0_h-temp1_h-0x1;
			}
			temp2_l=temp2_l+0x1;
		}
		else if (temp0_h==temp1_h&&temp0_l>=temp1_l)
		{
			temp0_l=temp0_l-temp1_l;
			temp0_h=temp0_h-temp1_h;
			temp2_l=temp2_l+0x1;
		}
		
		if (i==0)
			break;
		
		temp1_l=(temp1_l>>1)+(temp1_h<<0x1f);
		temp1_h=temp1_h>>1;
		temp2_h=(temp2_h<<1)+(temp2_l>>0x1f);
		temp2_l=(temp2_l<<1);
	}
	
	source->l32 = temp0_l;
	source->h32 = temp0_h;
	
	result->l32 = temp2_l;
	result->h32 = temp2_h;
}

#endif //#if (HOST_CPU_IS_I80386==0)

#if (HOST_CPU_IS_I80386==1)

void MultiplyBit64(X86_CPU_INT64 *result,Bit32u src,Bit32u dst)
{
	__asm
	{
		mov eax,src
		mul dst
		mov ebx,result
		mov [ebx]X86_CPU_INT64.l32,eax
		mov [ebx]X86_CPU_INT64.h32,edx
	}
}

void DivideBit64(X86_CPU_INT64 *source,Bit32u dst,X86_CPU_INT64 *result)
{
	if (source->h32>=dst)
	{
		result->l32 = (Bit32u)(-1);
		result->h32 = (Bit32u)(-1);
		return ;
	}
	else
	{
		result->l32 = 0;
		result->h32 = 0;
	}

	__asm
	{
		mov ebx,source
		mov eax,[ebx]X86_CPU_INT64.l32
		mov edx,[ebx]X86_CPU_INT64.h32
		div dst
		mov [ebx]X86_CPU_INT64.l32,edx
		mov ebx,result
		mov [ebx]X86_CPU_INT64.l32,eax
	}
}

#endif //#if (HOST_CPU_IS_I80386==1)

