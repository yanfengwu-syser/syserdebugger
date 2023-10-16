/////////////////////////////////////////////////////////////////////////
// $Id: mult.cc,v 1.0 2002/10/10 04:57:05 bdenney Exp $
/////////////////////////////////////////////////////////////////////////


#include "stdafx.h"
#include "x86cpu.h"
//---------------------------------------------------------
//ÐéÄâÖ´ÐÐ--Ö¸ÁîÎ¢º¯Êý  ³Ë³ýÔËËãÖ¸Áî
//---------------------------------------------------------


	void
BX_CPU_C::DIV_ALEGb(BX_CPU_C *icpu,bxInstruction_c *i)
{
	Bit8u op2;
	X86_CPU_INT64 source,result;
	Bit16u op1;
	op2 = READ_VIRTUAL_8BIT_REG(MODRMrm(i));
	op1 = RW_AX;
	source.h32 = 0;
	source.l32 = op1;
	
	DivideBit64(&source,op2,&result);
	if (result.l32>0x00ff)
	{
		BX_CPU_CLASS_PTR exception(BX_DE_EXCEPTION, 0, 0);
	}
	RW_AH = (Bit8u)(source.l32);
	RW_AL = (Bit8u)(result.l32);

	// DIV_ALEGb affects the following flags: O,S,Z,A,P,C are undefined 
}

	void
BX_CPU_C::DIV_ALEEb(BX_CPU_C *icpu,bxInstruction_c *i)
{
	Bit8u op2;
	X86_CPU_INT64 source,result;
	Bit16u op1;
	READ_VIRTUAL_BYTE(MODRMSeg(i),RMAddr(i),&op2);
	op1 = RW_AX;
	source.h32 = 0;
	source.l32 = op1;
	
	DivideBit64(&source,op2,&result);
	if (result.l32>0x00ff)
	{
		BX_CPU_CLASS_PTR exception(BX_DE_EXCEPTION, 0, 0);
	}
	RW_AH = (Bit8u)(source.l32);
	RW_AL = (Bit8u)(result.l32);

	// DIV_ALEEb affects the following flags: O,S,Z,A,P,C are undefined 
}

	void
BX_CPU_C::DIV_AXEGw(BX_CPU_C *icpu,bxInstruction_c *i)
{
	Bit16u op2;
	X86_CPU_INT64 source,result;
	Bit32u op1;
	op2 = READ_VIRTUAL_16BIT_REG(MODRMrm(i));
	op1 = ((RW_DX<<16) | RW_AX);
	source.h32 =0;
	source.l32 = op1;
	
	DivideBit64(&source,op2,&result);
	if (result.l32>0x0000ffff)
	{
		BX_CPU_CLASS_PTR exception(BX_DE_EXCEPTION, 0, 0);
	}
	RW_DX = (Bit16u)(source.l32);
	RW_AX = (Bit16u)(result.l32);

	// DIV_AXEGw affects the following flags: O,S,Z,A,P,C are undefined 
}

	void
BX_CPU_C::DIV_AXEEw(BX_CPU_C *icpu,bxInstruction_c *i)
{
	Bit16u op2;
	X86_CPU_INT64 source,result;
	Bit32u op1;
	READ_VIRTUAL_WORD(MODRMSeg(i),RMAddr(i),&op2);
	op1 = ((RW_DX<<16) | RW_AX);
	source.h32 =0;
	source.l32 = op1;
	
	DivideBit64(&source,op2,&result);
	if (result.l32>0x0000ffff)
	{
		BX_CPU_CLASS_PTR exception(BX_DE_EXCEPTION, 0, 0);
	}
	RW_DX = (Bit16u)(source.l32);
	RW_AX = (Bit16u)(result.l32);

	// DIV_AXEEw affects the following flags: O,S,Z,A,P,C are undefined 
}

	void
BX_CPU_C::DIV_EAXEGd(BX_CPU_C *icpu,bxInstruction_c *i)
{
	Bit32u op2;
	X86_CPU_INT64 source,result;
	op2 = READ_VIRTUAL_32BIT_REG(MODRMrm(i));
	source.h32 = RW_EDX;
	source.l32  = RW_EAX;
	
	DivideBit64(&source,op2,&result);
	if (result.h32>0)
	{
		BX_CPU_CLASS_PTR exception(BX_DE_EXCEPTION, 0, 0);
	}
	RW_EDX = source.l32;
	RW_EAX = result.l32;

	// DIV_EAXEGd affects the following flags: O,S,Z,A,P,C are undefined 
}

	void
BX_CPU_C::DIV_EAXEEd(BX_CPU_C *icpu,bxInstruction_c *i)
{
	Bit32u op2;
	X86_CPU_INT64 source,result;
	READ_VIRTUAL_DWORD(MODRMSeg(i),RMAddr(i),&op2);
	source.h32 = RW_EDX;
	source.l32  = RW_EAX;
	
	DivideBit64(&source,op2,&result);
	if (result.h32>0)
	{
		BX_CPU_CLASS_PTR exception(BX_DE_EXCEPTION, 0, 0);
	}
	RW_EDX = source.l32;
	RW_EAX = result.l32;

	// DIV_EAXEEd affects the following flags: O,S,Z,A,P,C are undefined 
}

	void
BX_CPU_C::IDIV_ALEGb(BX_CPU_C *icpu,bxInstruction_c *i)
{
	Bit8u op2;
	X86_CPU_INT64 source,result;
	Boolean s2,s1;
	Bit16u op1;
	op2 = READ_VIRTUAL_8BIT_REG(MODRMrm(i));
	op1 = RW_AX;
	s1 = op1>>15;
	s2 = op2>>7;
	if (s1)
	{
		op1 = 0 -op1;
	}
	if (s2)
	{
		op2 = 0 - op2;
	}
	source.h32 =0;
	source.l32 = op1;
	
	DivideBit64(&source,op2,&result);
	if (result.l32>0x0007f)
	{
		BX_CPU_CLASS_PTR exception(BX_DE_EXCEPTION, 0, 0);
	}
	if (s1)
	{
		source.l32 = 0 -source.l32;
	}
	if (s1!=s2)
	{
		result.l32 = 0 -result.l32;
	}
	RW_AH = (Bit8u)(source.l32);
	RW_AL = (Bit8u)(result.l32);

	// IDIV_ALEGb affects the following flags: O,S,Z,A,P,C are undefined 
}

	void
BX_CPU_C::IDIV_ALEEb(BX_CPU_C *icpu,bxInstruction_c *i)
{
	Bit8u op2;
	X86_CPU_INT64 source,result;
	Boolean s2,s1;
	Bit16u op1;
	READ_VIRTUAL_BYTE(MODRMSeg(i),RMAddr(i),&op2);
	op1 = RW_AX;
	s1 = op1>>15;
	s2 = op2>>7;
	if (s1)
	{
		op1 = 0 -op1;
	}
	if (s2)
	{
		op2 = 0 - op2;
	}
	source.h32 =0;
	source.l32 = op1;
	
	DivideBit64(&source,op2,&result);
	if (result.l32>0x0007f)
	{
		BX_CPU_CLASS_PTR exception(BX_DE_EXCEPTION, 0, 0);
	}
	if (s1)
	{
		source.l32 = 0 -source.l32;
	}
	if (s1!=s2)
	{
		result.l32 = 0 -result.l32;
	}
	RW_AH = (Bit8u)(source.l32);
	RW_AL = (Bit8u)(result.l32);

	// IDIV_ALEEb affects the following flags: O,S,Z,A,P,C are undefined 
}

	void
BX_CPU_C::IDIV_AXEGw(BX_CPU_C *icpu,bxInstruction_c *i)
{
	Bit16u op2;
	X86_CPU_INT64 source,result;
	Boolean s2,s1;
	Bit32u op1;
	op2 = READ_VIRTUAL_16BIT_REG(MODRMrm(i));
	op1 = ((RW_DX<<16) | RW_AX);
	s1 = op1>>31;
	s2 = op2>>15;
	if (s1)
	{
		op1 = 0 - op1;
	}
	if (s2)
	{
		op2 = 0 - op2;
	}
	source.h32 =0;
	source.l32 = op1;
	
	DivideBit64(&source,op2,&result);
	if (result.l32>0x0007fff)
	{
		BX_CPU_CLASS_PTR exception(BX_DE_EXCEPTION, 0, 0);
	}
	if (s1)
	{
		source.l32 = 0 -source.l32;
	}
	if (s1!=s2)
	{
		result.l32 = 0 -result.l32;
	}
	RW_DX = (Bit16u)(source.l32);
	RW_AX = (Bit16u)(result.l32);

	// IDIV_AXEGw affects the following flags: O,S,Z,A,P,C are undefined 
}

	void
BX_CPU_C::IDIV_AXEEw(BX_CPU_C *icpu,bxInstruction_c *i)
{
	Bit16u op2;
	X86_CPU_INT64 source,result;
	Boolean s2,s1;
	Bit32u op1;
	READ_VIRTUAL_WORD(MODRMSeg(i),RMAddr(i),&op2);
	op1 = ((RW_DX<<16) | RW_AX);
	s1 = op1>>31;
	s2 = op2>>15;
	if (s1)
	{
		op1 = 0 - op1;
	}
	if (s2)
	{
		op2 = 0 - op2;
	}
	source.h32 =0;
	source.l32 = op1;
	
	DivideBit64(&source,op2,&result);
	if (result.l32>0x0007fff)
	{
		BX_CPU_CLASS_PTR exception(BX_DE_EXCEPTION, 0, 0);
	}
	if (s1)
	{
		source.l32 = 0 -source.l32;
	}
	if (s1!=s2)
	{
		result.l32 = 0 -result.l32;
	}
	RW_DX = (Bit16u)(source.l32);
	RW_AX = (Bit16u)(result.l32);

	// IDIV_AXEEw affects the following flags: O,S,Z,A,P,C are undefined 
}

	void
BX_CPU_C::IDIV_EAXEGd(BX_CPU_C *icpu,bxInstruction_c *i)
{
	Bit32u op2;
	X86_CPU_INT64 source,result;
	Boolean s2,s1;
	op2 = READ_VIRTUAL_32BIT_REG(MODRMrm(i));
	source.h32 = RW_EDX;
	source.l32  = RW_EAX;
	s1 = source.h32>>31;
	s2 = op2>>31;
	if (s1)
	{
		source.l32 = 0 -source.l32;
		if (!source.l32)
		{
			source.h32 = 0 -source.h32 - 0;
		}
		else
		{
			source.h32 = 0 -source.h32 - 1;
		}
	}
	if (s2)
	{
		op2 = 0 - op2;
	}
	
	DivideBit64(&source,op2,&result);
	if (result.h32>0||result.l32>0x7fffffff)
	{
		BX_CPU_CLASS_PTR exception(BX_DE_EXCEPTION, 0, 0);
	}
	if (s1)
	{
		source.l32 = 0 -source.l32;
	}
	if (s1!=s2)
	{
		result.l32 = 0 -result.l32;
	}
	RW_EDX = source.l32;
	RW_EAX = result.l32;

	// IDIV_EAXEGd affects the following flags: O,S,Z,A,P,C are undefined 
}

	void
BX_CPU_C::IDIV_EAXEEd(BX_CPU_C *icpu,bxInstruction_c *i)
{
	Bit32u op2;
	X86_CPU_INT64 source,result;
	Boolean s2,s1;
	READ_VIRTUAL_DWORD(MODRMSeg(i),RMAddr(i),&op2);
	source.h32 = RW_EDX;
	source.l32  = RW_EAX;
	s1 = source.h32>>31;
	s2 = op2>>31;
	if (s1)
	{
		source.l32 = 0 -source.l32;
		if (!source.l32)
		{
			source.h32 = 0 -source.h32 - 0;
		}
		else
		{
			source.h32 = 0 -source.h32 - 1;
		}
	}
	if (s2)
	{
		op2 = 0 - op2;
	}
	
	DivideBit64(&source,op2,&result);
	if (result.h32>0||result.l32>0x7fffffff)
	{
		BX_CPU_CLASS_PTR exception(BX_DE_EXCEPTION, 0, 0);
	}
	if (s1)
	{
		source.l32 = 0 -source.l32;
	}
	if (s1!=s2)
	{
		result.l32 = 0 -result.l32;
	}
	RW_EDX = source.l32;
	RW_EAX = result.l32;

	// IDIV_EAXEEd affects the following flags: O,S,Z,A,P,C are undefined 
}

	void
BX_CPU_C::MUL_ALEGb(BX_CPU_C *icpu,bxInstruction_c *i)
{
	Bit8u op2, op1;
	Boolean temp_flag;
	Bit16u sum;
	op1 = READ_VIRTUAL_8BIT_REG(0);
	op2 = READ_VIRTUAL_8BIT_REG(MODRMrm(i));
	sum = op1 * op2;
	temp_flag = (sum>0x00ff);
	RW_AX  = sum;
	// MUL_ALEGb affects the following flags: C,O 
	SET_FLAGS_OxxxxC(temp_flag, temp_flag);
}

	void
BX_CPU_C::MUL_ALEEb(BX_CPU_C *icpu,bxInstruction_c *i)
{
	Bit8u op2, op1;
	Boolean temp_flag;
	Bit16u sum;
	op1 = READ_VIRTUAL_8BIT_REG(0);
	READ_VIRTUAL_BYTE(MODRMSeg(i),RMAddr(i),&op2);
	sum = op1 * op2;
	temp_flag = (sum>0x00ff);
	RW_AX  = sum;
	// MUL_ALEEb affects the following flags: C,O 
	SET_FLAGS_OxxxxC(temp_flag, temp_flag);
}

	void
BX_CPU_C::MUL_AXEGw(BX_CPU_C *icpu,bxInstruction_c *i)
{
	Bit16u op2, op1;
	Boolean temp_flag;
	Bit32u sum;
	op1 = READ_VIRTUAL_16BIT_REG(0);
	op2 = READ_VIRTUAL_16BIT_REG(MODRMrm(i));
	sum = op1 * op2;
	temp_flag = (sum>0x0000ffff);
	RW_AX  = (Bit16u)sum;
	RW_DX  = (Bit16u)(sum>>16);
	// MUL_AXEGw affects the following flags: C,O 
	SET_FLAGS_OxxxxC(temp_flag, temp_flag);
}

	void
BX_CPU_C::MUL_AXEEw(BX_CPU_C *icpu,bxInstruction_c *i)
{
	Bit16u op2, op1;
	Boolean temp_flag;
	Bit32u sum;
	op1 = READ_VIRTUAL_16BIT_REG(0);
	READ_VIRTUAL_WORD(MODRMSeg(i),RMAddr(i),&op2);
	sum = op1 * op2;
	temp_flag = (sum>0x0000ffff);
	RW_AX  = (Bit16u)sum;
	RW_DX  = (Bit16u)(sum>>16);
	// MUL_AXEEw affects the following flags: C,O 
	SET_FLAGS_OxxxxC(temp_flag, temp_flag);
}

	void
BX_CPU_C::MUL_EAXEGd(BX_CPU_C *icpu,bxInstruction_c *i)
{
	Bit32u op2, op1;
	Boolean temp_flag;
	X86_CPU_INT64 result;
	op1 = READ_VIRTUAL_32BIT_REG(0);
	op2 = READ_VIRTUAL_32BIT_REG(MODRMrm(i));
	
	MultiplyBit64(&result,op1,op2);
	temp_flag = (result.h32>0);
	RW_EAX  = result.l32;
	RW_EDX  = result.h32;
	// MUL_EAXEGd affects the following flags: C,O 
	SET_FLAGS_OxxxxC(temp_flag, temp_flag);
}

	void
BX_CPU_C::MUL_EAXEEd(BX_CPU_C *icpu,bxInstruction_c *i)
{
	Bit32u op2, op1;
	Boolean temp_flag;
	X86_CPU_INT64 result;
	op1 = READ_VIRTUAL_32BIT_REG(0);
	READ_VIRTUAL_DWORD(MODRMSeg(i),RMAddr(i),&op2);
	
	MultiplyBit64(&result,op1,op2);
	temp_flag = (result.h32>0);
	RW_EAX  = result.l32;
	RW_EDX  = result.h32;
	// MUL_EAXEEd affects the following flags: C,O 
	SET_FLAGS_OxxxxC(temp_flag, temp_flag);
}

	void
BX_CPU_C::IMUL_ALEGb(BX_CPU_C *icpu,bxInstruction_c *i)
{
	Bit8u op2, op1;
	Boolean s2,s1,temp_flag;
	Bit16u sum;
	op1 = READ_VIRTUAL_8BIT_REG(0);
	op2 = READ_VIRTUAL_8BIT_REG(MODRMrm(i));
	s1 = op1>>(8-1);
	s2 = op2>>(8-1);
	if (s1)
	{
		op1 = 0-op1;
	}
	if (s2)
	{
		op2 = 0-op2;
	}
	sum = op1 * op2;
	temp_flag = (sum>0x007f);
	if (s1!=s2)
	{
		sum = 0- sum;
	}
	RW_AX  = sum;
	// IMUL_ALEGb affects the following flags: C,O 
	SET_FLAGS_OxxxxC(temp_flag, temp_flag);
}

	void
BX_CPU_C::IMUL_ALEEb(BX_CPU_C *icpu,bxInstruction_c *i)
{
	Bit8u op2, op1;
	Boolean s2,s1,temp_flag;
	Bit16u sum;
	op1 = READ_VIRTUAL_8BIT_REG(0);
	READ_VIRTUAL_BYTE(MODRMSeg(i),RMAddr(i),&op2);
	s1 = op1>>(8-1);
	s2 = op2>>(8-1);
	if (s1)
	{
		op1 = 0-op1;
	}
	if (s2)
	{
		op2 = 0-op2;
	}
	sum = op1 * op2;
	temp_flag = (sum>0x007f);
	if (s1!=s2)
	{
		sum = 0- sum;
	}
	RW_AX  = sum;
	// IMUL_ALEEb affects the following flags: C,O 
	SET_FLAGS_OxxxxC(temp_flag, temp_flag);
}

	void
BX_CPU_C::IMUL_AXEGw(BX_CPU_C *icpu,bxInstruction_c *i)
{
	Bit16u op2, op1;
	Boolean s2,s1,temp_flag;
	Bit32u sum;
	op1 = READ_VIRTUAL_16BIT_REG(0);
	op2 = READ_VIRTUAL_16BIT_REG(MODRMrm(i));
	s1 = op1>>(16-1);
	s2 = op2>>(16-1);
	if (s1)
	{
		op1 = 0-op1;
	}
	if (s2)
	{
		op2 = 0-op2;
	}
	sum = op1 * op2;
	temp_flag = (sum>0x00007fff);
	if (s1!=s2)
	{
		sum = 0- sum;
	}
	RW_AX  = (Bit16u)sum;
	RW_DX  = (Bit16u)(sum>>16);
	// IMUL_AXEGw affects the following flags: C,O 
	SET_FLAGS_OxxxxC(temp_flag, temp_flag);
}

	void
BX_CPU_C::IMUL_AXEEw(BX_CPU_C *icpu,bxInstruction_c *i)
{
	Bit16u op2, op1;
	Boolean s2,s1,temp_flag;
	Bit32u sum;
	op1 = READ_VIRTUAL_16BIT_REG(0);
	READ_VIRTUAL_WORD(MODRMSeg(i),RMAddr(i),&op2);
	s1 = op1>>(16-1);
	s2 = op2>>(16-1);
	if (s1)
	{
		op1 = 0-op1;
	}
	if (s2)
	{
		op2 = 0-op2;
	}
	sum = op1 * op2;
	temp_flag = (sum>0x00007fff);
	if (s1!=s2)
	{
		sum = 0- sum;
	}
	RW_AX  = (Bit16u)sum;
	RW_DX  = (Bit16u)(sum>>16);
	// IMUL_AXEEw affects the following flags: C,O 
	SET_FLAGS_OxxxxC(temp_flag, temp_flag);
}

	void
BX_CPU_C::IMUL_EAXEGd(BX_CPU_C *icpu,bxInstruction_c *i)
{
	Bit32u op2, op1;
	Boolean s2,s1,temp_flag;
	X86_CPU_INT64 result;
	op1 = READ_VIRTUAL_32BIT_REG(0);
	op2 = READ_VIRTUAL_32BIT_REG(MODRMrm(i));
	s1 = op1>>(32-1);
	s2 = op2>>(32-1);
	if (s1)
	{
		op1 = 0-op1;
	}
	if (s2)
	{
		op2 = 0-op2;
	}
	
	MultiplyBit64(&result,op1,op2);
	temp_flag = (result.h32>0||result.l32>0x7fffffff);
	if (s1!=s2)
	{
		result.l32 = 0 - result.l32;
		if (!result.l32)
		{
			result.h32 = 0 - result.h32 -0;
		}
		else
		{
			result.h32 = 0 - result.h32 -1;
		}
	}
	RW_EAX  = result.l32;
	RW_EDX  = result.h32;
	// IMUL_EAXEGd affects the following flags: C,O 
	SET_FLAGS_OxxxxC(temp_flag, temp_flag);
}

	void
BX_CPU_C::IMUL_EAXEEd(BX_CPU_C *icpu,bxInstruction_c *i)
{
	Bit32u op2, op1;
	Boolean s2,s1,temp_flag;
	X86_CPU_INT64 result;
	op1 = READ_VIRTUAL_32BIT_REG(0);
	READ_VIRTUAL_DWORD(MODRMSeg(i),RMAddr(i),&op2);
	s1 = op1>>(32-1);
	s2 = op2>>(32-1);
	if (s1)
	{
		op1 = 0-op1;
	}
	if (s2)
	{
		op2 = 0-op2;
	}
	
	MultiplyBit64(&result,op1,op2);
	temp_flag = (result.h32>0||result.l32>0x7fffffff);
	if (s1!=s2)
	{
		result.l32 = 0 - result.l32;
		if (!result.l32)
		{
			result.h32 = 0 - result.h32 -0;
		}
		else
		{
			result.h32 = 0 - result.h32 -1;
		}
	}
	RW_EAX  = result.l32;
	RW_EDX  = result.h32;
	// IMUL_EAXEEd affects the following flags: C,O 
	SET_FLAGS_OxxxxC(temp_flag, temp_flag);
}

	void
BX_CPU_C::IMUL_GwEGw(BX_CPU_C *icpu,bxInstruction_c *i)
{
	Bit16u op2,op1;
	Boolean s2,s1,temp_flag;
	X86_CPU_INT64 result;
	op1 = READ_VIRTUAL_16BIT_REG(MODRMnnn(i));
	op2 = READ_VIRTUAL_16BIT_REG(MODRMrm(i));
	s1 = (op1>>(16-1));
	s2 = (op2>>(16-1));
	if (s1)
	{
		op1 = 0 - op1;
	}
	if (s2)
	{
		op2 = 0 - op2;
	}

	MultiplyBit64(&result,op1,op2);
	// Imul r,r/m;Imul r,r/m,immed :affects the following flags CF & OF:
	// result exactly fits within r

	temp_flag = (result.l32>0x00007fff);
	if (s1!=s2)
	{
		result.l32 = 0 - result.l32;
	}
	WRITE_VIRTUAL_16BIT_REG(MODRMnnn(i), ((Bit16u)result.l32));
	SET_FLAGS_OxxxxC(temp_flag, temp_flag);
}

	void
BX_CPU_C::IMUL_GwEEw(BX_CPU_C *icpu,bxInstruction_c *i)
{
	Bit16u op2,op1;
	Boolean s2,s1,temp_flag;
	X86_CPU_INT64 result;
	op1 = READ_VIRTUAL_16BIT_REG(MODRMnnn(i));
	READ_VIRTUAL_WORD(MODRMSeg(i),RMAddr(i),&op2);
	s1 = (op1>>(16-1));
	s2 = (op2>>(16-1));
	if (s1)
	{
		op1 = 0 - op1;
	}
	if (s2)
	{
		op2 = 0 - op2;
	}

	MultiplyBit64(&result,op1,op2);
	// Imul r,r/m;Imul r,r/m,immed :affects the following flags CF & OF:
	// result exactly fits within r

	temp_flag = (result.l32>0x00007fff);
	if (s1!=s2)
	{
		result.l32 = 0 - result.l32;
	}
	WRITE_VIRTUAL_16BIT_REG(MODRMnnn(i), ((Bit16u)result.l32));
	SET_FLAGS_OxxxxC(temp_flag, temp_flag);
}

	void
BX_CPU_C::IMUL_GdEGd(BX_CPU_C *icpu,bxInstruction_c *i)
{
	Bit32u op2,op1;
	Boolean s2,s1,temp_flag;
	X86_CPU_INT64 result;
	op1 = READ_VIRTUAL_32BIT_REG(MODRMnnn(i));
	op2 = READ_VIRTUAL_32BIT_REG(MODRMrm(i));
	s1 = (op1>>(32-1));
	s2 = (op2>>(32-1));
	if (s1)
	{
		op1 = 0 - op1;
	}
	if (s2)
	{
		op2 = 0 - op2;
	}

	MultiplyBit64(&result,op1,op2);
	// Imul r,r/m;Imul r,r/m,immed :affects the following flags CF & OF:
	// result exactly fits within r

	temp_flag = (result.h32 >0 || result.l32 >0x7fffffff);
	if (s1!=s2)
	{
		result.l32 = 0 - result.l32;
		if (!result.l32)
		{
			result.h32 = 0 - result.h32 -0;
		}
		else
		{
			result.h32 = 0 - result.h32 -1;
		}
	}
	WRITE_VIRTUAL_32BIT_REG(MODRMnnn(i),result.l32);
	SET_FLAGS_OxxxxC(temp_flag, temp_flag);
}

	void
BX_CPU_C::IMUL_GdEEd(BX_CPU_C *icpu,bxInstruction_c *i)
{
	Bit32u op2,op1;
	Boolean s2,s1,temp_flag;
	X86_CPU_INT64 result;
	op1 = READ_VIRTUAL_32BIT_REG(MODRMnnn(i));
	READ_VIRTUAL_DWORD(MODRMSeg(i),RMAddr(i),&op2);
	s1 = (op1>>(32-1));
	s2 = (op2>>(32-1));
	if (s1)
	{
		op1 = 0 - op1;
	}
	if (s2)
	{
		op2 = 0 - op2;
	}

	MultiplyBit64(&result,op1,op2);
	// Imul r,r/m;Imul r,r/m,immed :affects the following flags CF & OF:
	// result exactly fits within r

	temp_flag = (result.h32 >0 || result.l32 >0x7fffffff);
	if (s1!=s2)
	{
		result.l32 = 0 - result.l32;
		if (!result.l32)
		{
			result.h32 = 0 - result.h32 -0;
		}
		else
		{
			result.h32 = 0 - result.h32 -1;
		}
	}
	WRITE_VIRTUAL_32BIT_REG(MODRMnnn(i),result.l32);
	SET_FLAGS_OxxxxC(temp_flag, temp_flag);
}

	void
BX_CPU_C::IMUL_GwEGwIw(BX_CPU_C *icpu,bxInstruction_c *i)
{
	Bit16u op2,op1;
	Boolean s2,s1,temp_flag;
	X86_CPU_INT64 result;
	op1 = IMMEDIATEIw(i);
	op2 = READ_VIRTUAL_16BIT_REG(MODRMrm(i));
	s1 = (op1>>(16-1));
	s2 = (op2>>(16-1));
	if (s1)
	{
		op1 = 0 - op1;
	}
	if (s2)
	{
		op2 = 0 - op2;
	}

	MultiplyBit64(&result,op1,op2);
	// Imul r,r/m;Imul r,r/m,immed :affects the following flags CF & OF:
	// result exactly fits within r

	temp_flag = (result.l32>0x00007fff);
	if (s1!=s2)
	{
		result.l32 = 0 - result.l32;
	}
	WRITE_VIRTUAL_16BIT_REG(MODRMnnn(i), ((Bit16u)result.l32));
	SET_FLAGS_OxxxxC(temp_flag, temp_flag);
}

	void
BX_CPU_C::IMUL_GwEEwIw(BX_CPU_C *icpu,bxInstruction_c *i)
{
	Bit16u op2,op1;
	Boolean s2,s1,temp_flag;
	X86_CPU_INT64 result;
	op1 = IMMEDIATEIw(i);
	READ_VIRTUAL_WORD(MODRMSeg(i),RMAddr(i),&op2);
	s1 = (op1>>(16-1));
	s2 = (op2>>(16-1));
	if (s1)
	{
		op1 = 0 - op1;
	}
	if (s2)
	{
		op2 = 0 - op2;
	}

	MultiplyBit64(&result,op1,op2);
	// Imul r,r/m;Imul r,r/m,immed :affects the following flags CF & OF:
	// result exactly fits within r

	temp_flag = (result.l32>0x00007fff);
	if (s1!=s2)
	{
		result.l32 = 0 - result.l32;
	}
	WRITE_VIRTUAL_16BIT_REG(MODRMnnn(i), ((Bit16u)result.l32));
	SET_FLAGS_OxxxxC(temp_flag, temp_flag);
}

	void
BX_CPU_C::IMUL_GdEGdId(BX_CPU_C *icpu,bxInstruction_c *i)
{
	Bit32u op2,op1;
	Boolean s2,s1,temp_flag;
	X86_CPU_INT64 result;
	op1 = IMMEDIATEId(i);
	op2 = READ_VIRTUAL_32BIT_REG(MODRMrm(i));
	s1 = (op1>>(32-1));
	s2 = (op2>>(32-1));
	if (s1)
	{
		op1 = 0 - op1;
	}
	if (s2)
	{
		op2 = 0 - op2;
	}

	MultiplyBit64(&result,op1,op2);
	// Imul r,r/m;Imul r,r/m,immed :affects the following flags CF & OF:
	// result exactly fits within r

	temp_flag = (result.h32 >0 || result.l32 >0x7fffffff);
	if (s1!=s2)
	{
		result.l32 = 0 - result.l32;
		if (!result.l32)
		{
			result.h32 = 0 - result.h32 -0;
		}
		else
		{
			result.h32 = 0 - result.h32 -1;
		}
	}
	WRITE_VIRTUAL_32BIT_REG(MODRMnnn(i),result.l32);
	SET_FLAGS_OxxxxC(temp_flag, temp_flag);
}

	void
BX_CPU_C::IMUL_GdEEdId(BX_CPU_C *icpu,bxInstruction_c *i)
{
	Bit32u op2,op1;
	Boolean s2,s1,temp_flag;
	X86_CPU_INT64 result;
	op1 = IMMEDIATEId(i);
	READ_VIRTUAL_DWORD(MODRMSeg(i),RMAddr(i),&op2);
	s1 = (op1>>(32-1));
	s2 = (op2>>(32-1));
	if (s1)
	{
		op1 = 0 - op1;
	}
	if (s2)
	{
		op2 = 0 - op2;
	}

	MultiplyBit64(&result,op1,op2);
	// Imul r,r/m;Imul r,r/m,immed :affects the following flags CF & OF:
	// result exactly fits within r

	temp_flag = (result.h32 >0 || result.l32 >0x7fffffff);
	if (s1!=s2)
	{
		result.l32 = 0 - result.l32;
		if (!result.l32)
		{
			result.h32 = 0 - result.h32 -0;
		}
		else
		{
			result.h32 = 0 - result.h32 -1;
		}
	}
	WRITE_VIRTUAL_32BIT_REG(MODRMnnn(i),result.l32);
	SET_FLAGS_OxxxxC(temp_flag, temp_flag);
}

