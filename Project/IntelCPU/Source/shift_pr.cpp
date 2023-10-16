/////////////////////////////////////////////////////////////////////////
// $Id: shift_pro.cc,v 1.0 2002/10/10 04:57:05 bdenney Exp $
/////////////////////////////////////////////////////////////////////////


#include "stdafx.h"
#include "x86cpu.h"
//---------------------------------------------------------
//–Èƒ‚÷¥––--÷∏¡ÓŒ¢∫Ø ˝  “∆Œª÷∏¡Ó
//---------------------------------------------------------


// shift dst(r/m), src(i8/1/cl)
// src <-- i8	| b1: 0xc0/0xc1
// src <-- 1    | b1: 0xd0/0xd1
// src <-- cl   | b1: 0xd2/0xd3
// shift double dst(r/m),src(r),  src(i8/cl)
// src <-- i8	| b1: 0x1a4
// src <-- cl   | b1: 0x1a5


	void
BX_CPU_C::ROL_EGb_0( BX_CPU_C *icpu,bxInstruction_c *i)
{
}

	void
BX_CPU_C::ROL_EGw_0( BX_CPU_C *icpu,bxInstruction_c *i)
{
}

	void
BX_CPU_C::ROL_EGd_0( BX_CPU_C *icpu,bxInstruction_c *i)
{
}

	void
BX_CPU_C::ROL_EEb_0( BX_CPU_C *icpu,bxInstruction_c *i)
{
	Bit8u op;
	READ_RMW_VIRTUAL_BYTE(MODRMSeg(i),RMAddr(i),&op);
}

	void
BX_CPU_C::ROL_EEw_0( BX_CPU_C *icpu,bxInstruction_c *i)
{
	Bit16u op;
	READ_RMW_VIRTUAL_WORD(MODRMSeg(i),RMAddr(i),&op);
}

	void
BX_CPU_C::ROL_EEd_0( BX_CPU_C *icpu,bxInstruction_c *i)
{
	Bit32u op;
	READ_RMW_VIRTUAL_DWORD(MODRMSeg(i),RMAddr(i),&op);
}

	void
BX_CPU_C::ROL_EGb_1(BX_CPU_C *icpu,bxInstruction_c *i)
{
	Bit8u count;
	Bit8u op1,result;
	count = i->Word.shift;
	op1 = READ_VIRTUAL_8BIT_REG(MODRMrm(i));

	result = (op1 << 1) | (op1 >> (8-1));
	WRITE_VIRTUAL_8BIT_REG(MODRMrm(i),result);
#if (HOST_CPU_IS_I80386==0)
	SET_FLAGS_OC_8(op1,i->Word.shift,result,BX_INSTR_ROL8)
#endif //#if (HOST_CPU_IS_I80386==0)
#if (HOST_CPU_IS_I80386==1)
	Bit32u x86_lf_flags = BX_CPU_CLASS_PTR eflags.x86.eax;
	count = IMMEDIATEIb(i);
	__asm
	{
		mov eax,x86_lf_flags
		cmp al,0x81
		sahf
		mov cl,count
		ROL op1,cl
		lahf
		seto al
		mov x86_lf_flags,eax
	}

	BX_CPU_CLASS_PTR eflags.x86.eax = x86_lf_flags;
#endif //#if (HOST_CPU_IS_I80386==1)
}

	void
BX_CPU_C::ROL_EGw_1(BX_CPU_C *icpu,bxInstruction_c *i)
{
	Bit8u count;
	Bit16u op1,result;
	count = i->Word.shift;
	op1 = READ_VIRTUAL_16BIT_REG(MODRMrm(i));

	result = (op1 << 1) | (op1 >> (16-1));
	WRITE_VIRTUAL_16BIT_REG(MODRMrm(i),result);
#if (HOST_CPU_IS_I80386==0)
	SET_FLAGS_OC_16(op1,i->Word.shift,result,BX_INSTR_ROL16)
#endif //#if (HOST_CPU_IS_I80386==0)
#if (HOST_CPU_IS_I80386==1)
	Bit32u x86_lf_flags = BX_CPU_CLASS_PTR eflags.x86.eax;
	count = IMMEDIATEIb(i);
	__asm
	{
		mov eax,x86_lf_flags
		cmp al,0x81
		sahf
		mov cl,count
		ROL op1,cl
		lahf
		seto al
		mov x86_lf_flags,eax
	}

	BX_CPU_CLASS_PTR eflags.x86.eax = x86_lf_flags;
#endif //#if (HOST_CPU_IS_I80386==1)
}

	void
BX_CPU_C::ROL_EGd_1(BX_CPU_C *icpu,bxInstruction_c *i)
{
	Bit8u count;
	Bit32u op1,result;
	count = i->Word.shift;
	op1 = READ_VIRTUAL_32BIT_REG(MODRMrm(i));

	result = (op1 << 1) | (op1 >> (32-1));
	WRITE_VIRTUAL_32BIT_REG(MODRMrm(i),result);
#if (HOST_CPU_IS_I80386==0)
	SET_FLAGS_OC_32(op1,i->Word.shift,result,BX_INSTR_ROL32)
#endif //#if (HOST_CPU_IS_I80386==0)
#if (HOST_CPU_IS_I80386==1)
	Bit32u x86_lf_flags = BX_CPU_CLASS_PTR eflags.x86.eax;
	count = IMMEDIATEIb(i);
	__asm
	{
		mov eax,x86_lf_flags
		cmp al,0x81
		sahf
		mov cl,count
		ROL op1,cl
		lahf
		seto al
		mov x86_lf_flags,eax
	}

	BX_CPU_CLASS_PTR eflags.x86.eax = x86_lf_flags;
#endif //#if (HOST_CPU_IS_I80386==1)
}

	void
BX_CPU_C::ROR_EGb_1(BX_CPU_C *icpu,bxInstruction_c *i)
{
	Bit8u count;
	Bit8u op1,result;
	count = i->Word.shift;
	op1 = READ_VIRTUAL_8BIT_REG(MODRMrm(i));

	result = (op1 >> 1) | (op1 << (8-1));
	WRITE_VIRTUAL_8BIT_REG(MODRMrm(i),result);
#if (HOST_CPU_IS_I80386==0)
	SET_FLAGS_OC_8(op1,i->Word.shift,result,BX_INSTR_ROR8)
#endif //#if (HOST_CPU_IS_I80386==0)
#if (HOST_CPU_IS_I80386==1)
	Bit32u x86_lf_flags = BX_CPU_CLASS_PTR eflags.x86.eax;
	count = IMMEDIATEIb(i);
	__asm
	{
		mov eax,x86_lf_flags
		cmp al,0x81
		sahf
		mov cl,count
		ROR op1,cl
		lahf
		seto al
		mov x86_lf_flags,eax
	}

	BX_CPU_CLASS_PTR eflags.x86.eax = x86_lf_flags;
#endif //#if (HOST_CPU_IS_I80386==1)
}

	void
BX_CPU_C::ROR_EGw_1(BX_CPU_C *icpu,bxInstruction_c *i)
{
	Bit8u count;
	Bit16u op1,result;
	count = i->Word.shift;
	op1 = READ_VIRTUAL_16BIT_REG(MODRMrm(i));

	result = (op1 >> 1) | (op1 << (16-1));
	WRITE_VIRTUAL_16BIT_REG(MODRMrm(i),result);
#if (HOST_CPU_IS_I80386==0)
	SET_FLAGS_OC_16(op1,i->Word.shift,result,BX_INSTR_ROR16)
#endif //#if (HOST_CPU_IS_I80386==0)
#if (HOST_CPU_IS_I80386==1)
	Bit32u x86_lf_flags = BX_CPU_CLASS_PTR eflags.x86.eax;
	count = IMMEDIATEIb(i);
	__asm
	{
		mov eax,x86_lf_flags
		cmp al,0x81
		sahf
		mov cl,count
		ROR op1,cl
		lahf
		seto al
		mov x86_lf_flags,eax
	}

	BX_CPU_CLASS_PTR eflags.x86.eax = x86_lf_flags;
#endif //#if (HOST_CPU_IS_I80386==1)
}

	void
BX_CPU_C::ROR_EGd_1(BX_CPU_C *icpu,bxInstruction_c *i)
{
	Bit8u count;
	Bit32u op1,result;
	count = i->Word.shift;
	op1 = READ_VIRTUAL_32BIT_REG(MODRMrm(i));

	result = (op1 >> 1) | (op1 << (32-1));
	WRITE_VIRTUAL_32BIT_REG(MODRMrm(i),result);
#if (HOST_CPU_IS_I80386==0)
	SET_FLAGS_OC_32(op1,i->Word.shift,result,BX_INSTR_ROR32)
#endif //#if (HOST_CPU_IS_I80386==0)
#if (HOST_CPU_IS_I80386==1)
	Bit32u x86_lf_flags = BX_CPU_CLASS_PTR eflags.x86.eax;
	count = IMMEDIATEIb(i);
	__asm
	{
		mov eax,x86_lf_flags
		cmp al,0x81
		sahf
		mov cl,count
		ROR op1,cl
		lahf
		seto al
		mov x86_lf_flags,eax
	}

	BX_CPU_CLASS_PTR eflags.x86.eax = x86_lf_flags;
#endif //#if (HOST_CPU_IS_I80386==1)
}

	void
BX_CPU_C::RCL_EGb_1(BX_CPU_C *icpu,bxInstruction_c *i)
{
	Bit8u count;
	Bit8u op1,result;
	count = i->Word.shift;
	op1 = READ_VIRTUAL_8BIT_REG(MODRMrm(i));

	result = (op1 << 1) | (BX_CPU_CLASS_PTR get_CF());
	WRITE_VIRTUAL_8BIT_REG(MODRMrm(i),result);
#if (HOST_CPU_IS_I80386==0)
	SET_FLAGS_OC_8(op1,i->Word.shift,result,BX_INSTR_RCL8)
#endif //#if (HOST_CPU_IS_I80386==0)
#if (HOST_CPU_IS_I80386==1)
	Bit32u x86_lf_flags = BX_CPU_CLASS_PTR eflags.x86.eax;
	count = IMMEDIATEIb(i);
	__asm
	{
		mov eax,x86_lf_flags
		cmp al,0x81
		sahf
		mov cl,count
		RCL op1,cl
		lahf
		seto al
		mov x86_lf_flags,eax
	}

	BX_CPU_CLASS_PTR eflags.x86.eax = x86_lf_flags;
#endif //#if (HOST_CPU_IS_I80386==1)
}

	void
BX_CPU_C::RCL_EGw_1(BX_CPU_C *icpu,bxInstruction_c *i)
{
	Bit8u count;
	Bit16u op1,result;
	count = i->Word.shift;
	op1 = READ_VIRTUAL_16BIT_REG(MODRMrm(i));

	result = (op1 << 1) | (BX_CPU_CLASS_PTR get_CF());
	WRITE_VIRTUAL_16BIT_REG(MODRMrm(i),result);
#if (HOST_CPU_IS_I80386==0)
	SET_FLAGS_OC_16(op1,i->Word.shift,result,BX_INSTR_RCL16)
#endif //#if (HOST_CPU_IS_I80386==0)
#if (HOST_CPU_IS_I80386==1)
	Bit32u x86_lf_flags = BX_CPU_CLASS_PTR eflags.x86.eax;
	count = IMMEDIATEIb(i);
	__asm
	{
		mov eax,x86_lf_flags
		cmp al,0x81
		sahf
		mov cl,count
		RCL op1,cl
		lahf
		seto al
		mov x86_lf_flags,eax
	}

	BX_CPU_CLASS_PTR eflags.x86.eax = x86_lf_flags;
#endif //#if (HOST_CPU_IS_I80386==1)
}

	void
BX_CPU_C::RCL_EGd_1(BX_CPU_C *icpu,bxInstruction_c *i)
{
	Bit8u count;
	Bit32u op1,result;
	count = i->Word.shift;
	op1 = READ_VIRTUAL_32BIT_REG(MODRMrm(i));

	result = (op1 << 1) | (BX_CPU_CLASS_PTR get_CF());
	WRITE_VIRTUAL_32BIT_REG(MODRMrm(i),result);
#if (HOST_CPU_IS_I80386==0)
	SET_FLAGS_OC_32(op1,i->Word.shift,result,BX_INSTR_RCL32)
#endif //#if (HOST_CPU_IS_I80386==0)
#if (HOST_CPU_IS_I80386==1)
	Bit32u x86_lf_flags = BX_CPU_CLASS_PTR eflags.x86.eax;
	count = IMMEDIATEIb(i);
	__asm
	{
		mov eax,x86_lf_flags
		cmp al,0x81
		sahf
		mov cl,count
		RCL op1,cl
		lahf
		seto al
		mov x86_lf_flags,eax
	}

	BX_CPU_CLASS_PTR eflags.x86.eax = x86_lf_flags;
#endif //#if (HOST_CPU_IS_I80386==1)
}

	void
BX_CPU_C::RCR_EGb_1(BX_CPU_C *icpu,bxInstruction_c *i)
{
	Bit8u count;
	Bit8u op1,result;
	count = i->Word.shift;
	op1 = READ_VIRTUAL_8BIT_REG(MODRMrm(i));

	result = (op1 >> 1) | (BX_CPU_CLASS_PTR get_CF() << (8 - 1));
	WRITE_VIRTUAL_8BIT_REG(MODRMrm(i),result);
#if (HOST_CPU_IS_I80386==0)
	SET_FLAGS_OC_8(op1,i->Word.shift,result,BX_INSTR_RCR8)
#endif //#if (HOST_CPU_IS_I80386==0)
#if (HOST_CPU_IS_I80386==1)
	Bit32u x86_lf_flags = BX_CPU_CLASS_PTR eflags.x86.eax;
	count = IMMEDIATEIb(i);
	__asm
	{
		mov eax,x86_lf_flags
		cmp al,0x81
		sahf
		mov cl,count
		RCR op1,cl
		lahf
		seto al
		mov x86_lf_flags,eax
	}

	BX_CPU_CLASS_PTR eflags.x86.eax = x86_lf_flags;
#endif //#if (HOST_CPU_IS_I80386==1)
}

	void
BX_CPU_C::RCR_EGw_1(BX_CPU_C *icpu,bxInstruction_c *i)
{
	Bit8u count;
	Bit16u op1,result;
	count = i->Word.shift;
	op1 = READ_VIRTUAL_16BIT_REG(MODRMrm(i));

	result = (op1 >> 1) | (BX_CPU_CLASS_PTR get_CF() << (16 - 1));
	WRITE_VIRTUAL_16BIT_REG(MODRMrm(i),result);
#if (HOST_CPU_IS_I80386==0)
	SET_FLAGS_OC_16(op1,i->Word.shift,result,BX_INSTR_RCR16)
#endif //#if (HOST_CPU_IS_I80386==0)
#if (HOST_CPU_IS_I80386==1)
	Bit32u x86_lf_flags = BX_CPU_CLASS_PTR eflags.x86.eax;
	count = IMMEDIATEIb(i);
	__asm
	{
		mov eax,x86_lf_flags
		cmp al,0x81
		sahf
		mov cl,count
		RCR op1,cl
		lahf
		seto al
		mov x86_lf_flags,eax
	}

	BX_CPU_CLASS_PTR eflags.x86.eax = x86_lf_flags;
#endif //#if (HOST_CPU_IS_I80386==1)
}

	void
BX_CPU_C::RCR_EGd_1(BX_CPU_C *icpu,bxInstruction_c *i)
{
	Bit8u count;
	Bit32u op1,result;
	count = i->Word.shift;
	op1 = READ_VIRTUAL_32BIT_REG(MODRMrm(i));

	result = (op1 >> 1) | (BX_CPU_CLASS_PTR get_CF() << (32 - 1));
	WRITE_VIRTUAL_32BIT_REG(MODRMrm(i),result);
#if (HOST_CPU_IS_I80386==0)
	SET_FLAGS_OC_32(op1,i->Word.shift,result,BX_INSTR_RCR32)
#endif //#if (HOST_CPU_IS_I80386==0)
#if (HOST_CPU_IS_I80386==1)
	Bit32u x86_lf_flags = BX_CPU_CLASS_PTR eflags.x86.eax;
	count = IMMEDIATEIb(i);
	__asm
	{
		mov eax,x86_lf_flags
		cmp al,0x81
		sahf
		mov cl,count
		RCR op1,cl
		lahf
		seto al
		mov x86_lf_flags,eax
	}

	BX_CPU_CLASS_PTR eflags.x86.eax = x86_lf_flags;
#endif //#if (HOST_CPU_IS_I80386==1)
}

	void
BX_CPU_C::SHL_EGb_1(BX_CPU_C *icpu,bxInstruction_c *i)
{
	Bit8u count;
	Bit8u op1,result;
	count = i->Word.shift;
	op1 = READ_VIRTUAL_8BIT_REG(MODRMrm(i));

	result = (op1 << 1);
	WRITE_VIRTUAL_8BIT_REG(MODRMrm(i),result);
#if (HOST_CPU_IS_I80386==0)
	SET_FLAGS_OSZPC_8(op1,IMMEDIATEIb(i),result,BX_INSTR_SHL8)
#endif //#if (HOST_CPU_IS_I80386==0)
#if (HOST_CPU_IS_I80386==1)
	Bit32u x86_lf_flags = BX_CPU_CLASS_PTR eflags.x86.eax;
	count = IMMEDIATEIb(i);
	__asm
	{
		mov eax,x86_lf_flags
		cmp al,0x81
		sahf
		mov cl,count
		SHL op1,cl
		lahf
		seto al
		mov x86_lf_flags,eax
	}

	BX_CPU_CLASS_PTR eflags.x86.eax = x86_lf_flags;
#endif //#if (HOST_CPU_IS_I80386==1)
}

	void
BX_CPU_C::SHL_EGw_1(BX_CPU_C *icpu,bxInstruction_c *i)
{
	Bit8u count;
	Bit16u op1,result;
	count = i->Word.shift;
	op1 = READ_VIRTUAL_16BIT_REG(MODRMrm(i));

	result = (op1 << 1);
	WRITE_VIRTUAL_16BIT_REG(MODRMrm(i),result);
#if (HOST_CPU_IS_I80386==0)
	SET_FLAGS_OSZPC_16(op1,IMMEDIATEIb(i),result,BX_INSTR_SHL16)
#endif //#if (HOST_CPU_IS_I80386==0)
#if (HOST_CPU_IS_I80386==1)
	Bit32u x86_lf_flags = BX_CPU_CLASS_PTR eflags.x86.eax;
	count = IMMEDIATEIb(i);
	__asm
	{
		mov eax,x86_lf_flags
		cmp al,0x81
		sahf
		mov cl,count
		SHL op1,cl
		lahf
		seto al
		mov x86_lf_flags,eax
	}

	BX_CPU_CLASS_PTR eflags.x86.eax = x86_lf_flags;
#endif //#if (HOST_CPU_IS_I80386==1)
}

	void
BX_CPU_C::SHL_EGd_1(BX_CPU_C *icpu,bxInstruction_c *i)
{
	Bit8u count;
	Bit32u op1,result;
	count = i->Word.shift;
	op1 = READ_VIRTUAL_32BIT_REG(MODRMrm(i));

	result = (op1 << 1);
	WRITE_VIRTUAL_32BIT_REG(MODRMrm(i),result);
#if (HOST_CPU_IS_I80386==0)
	SET_FLAGS_OSZPC_32(op1,IMMEDIATEIb(i),result,BX_INSTR_SHL32)
#endif //#if (HOST_CPU_IS_I80386==0)
#if (HOST_CPU_IS_I80386==1)
	Bit32u x86_lf_flags = BX_CPU_CLASS_PTR eflags.x86.eax;
	count = IMMEDIATEIb(i);
	__asm
	{
		mov eax,x86_lf_flags
		cmp al,0x81
		sahf
		mov cl,count
		SHL op1,cl
		lahf
		seto al
		mov x86_lf_flags,eax
	}

	BX_CPU_CLASS_PTR eflags.x86.eax = x86_lf_flags;
#endif //#if (HOST_CPU_IS_I80386==1)
}

	void
BX_CPU_C::SHR_EGb_1(BX_CPU_C *icpu,bxInstruction_c *i)
{
	Bit8u count;
	Bit8u op1,result;
	count = i->Word.shift;
	op1 = READ_VIRTUAL_8BIT_REG(MODRMrm(i));

	result = (op1 >> 1);
	WRITE_VIRTUAL_8BIT_REG(MODRMrm(i),result);
#if (HOST_CPU_IS_I80386==0)
	SET_FLAGS_OSZPC_8(op1,IMMEDIATEIb(i),result,BX_INSTR_SHR8)
#endif //#if (HOST_CPU_IS_I80386==0)
#if (HOST_CPU_IS_I80386==1)
	Bit32u x86_lf_flags = BX_CPU_CLASS_PTR eflags.x86.eax;
	count = IMMEDIATEIb(i);
	__asm
	{
		mov eax,x86_lf_flags
		cmp al,0x81
		sahf
		mov cl,count
		SHR op1,cl
		lahf
		seto al
		mov x86_lf_flags,eax
	}

	BX_CPU_CLASS_PTR eflags.x86.eax = x86_lf_flags;
#endif //#if (HOST_CPU_IS_I80386==1)
}

	void
BX_CPU_C::SHR_EGw_1(BX_CPU_C *icpu,bxInstruction_c *i)
{
	Bit8u count;
	Bit16u op1,result;
	count = i->Word.shift;
	op1 = READ_VIRTUAL_16BIT_REG(MODRMrm(i));

	result = (op1 >> 1);
	WRITE_VIRTUAL_16BIT_REG(MODRMrm(i),result);
#if (HOST_CPU_IS_I80386==0)
	SET_FLAGS_OSZPC_16(op1,IMMEDIATEIb(i),result,BX_INSTR_SHR16)
#endif //#if (HOST_CPU_IS_I80386==0)
#if (HOST_CPU_IS_I80386==1)
	Bit32u x86_lf_flags = BX_CPU_CLASS_PTR eflags.x86.eax;
	count = IMMEDIATEIb(i);
	__asm
	{
		mov eax,x86_lf_flags
		cmp al,0x81
		sahf
		mov cl,count
		SHR op1,cl
		lahf
		seto al
		mov x86_lf_flags,eax
	}

	BX_CPU_CLASS_PTR eflags.x86.eax = x86_lf_flags;
#endif //#if (HOST_CPU_IS_I80386==1)
}

	void
BX_CPU_C::SHR_EGd_1(BX_CPU_C *icpu,bxInstruction_c *i)
{
	Bit8u count;
	Bit32u op1,result;
	count = i->Word.shift;
	op1 = READ_VIRTUAL_32BIT_REG(MODRMrm(i));

	result = (op1 >> 1);
	WRITE_VIRTUAL_32BIT_REG(MODRMrm(i),result);
#if (HOST_CPU_IS_I80386==0)
	SET_FLAGS_OSZPC_32(op1,IMMEDIATEIb(i),result,BX_INSTR_SHR32)
#endif //#if (HOST_CPU_IS_I80386==0)
#if (HOST_CPU_IS_I80386==1)
	Bit32u x86_lf_flags = BX_CPU_CLASS_PTR eflags.x86.eax;
	count = IMMEDIATEIb(i);
	__asm
	{
		mov eax,x86_lf_flags
		cmp al,0x81
		sahf
		mov cl,count
		SHR op1,cl
		lahf
		seto al
		mov x86_lf_flags,eax
	}

	BX_CPU_CLASS_PTR eflags.x86.eax = x86_lf_flags;
#endif //#if (HOST_CPU_IS_I80386==1)
}

	void
BX_CPU_C::SAR_EGb_1(BX_CPU_C *icpu,bxInstruction_c *i)
{
	Bit8u count;
	Bit8u op1,result;
	count = i->Word.shift;
	op1 = READ_VIRTUAL_8BIT_REG(MODRMrm(i));

	result = (op1 >> 1) |
		((0-(op1>>(8-1))) << (8 - 1));
	WRITE_VIRTUAL_8BIT_REG(MODRMrm(i),result);
#if (HOST_CPU_IS_I80386==0)
	SET_FLAGS_OSZPC_8(op1,IMMEDIATEIb(i),result,BX_INSTR_SAR8)
#endif //#if (HOST_CPU_IS_I80386==0)
#if (HOST_CPU_IS_I80386==1)
	Bit32u x86_lf_flags = BX_CPU_CLASS_PTR eflags.x86.eax;
	count = IMMEDIATEIb(i);
	__asm
	{
		mov eax,x86_lf_flags
		cmp al,0x81
		sahf
		mov cl,count
		SAR op1,cl
		lahf
		seto al
		mov x86_lf_flags,eax
	}

	BX_CPU_CLASS_PTR eflags.x86.eax = x86_lf_flags;
#endif //#if (HOST_CPU_IS_I80386==1)
}

	void
BX_CPU_C::SAR_EGw_1(BX_CPU_C *icpu,bxInstruction_c *i)
{
	Bit8u count;
	Bit16u op1,result;
	count = i->Word.shift;
	op1 = READ_VIRTUAL_16BIT_REG(MODRMrm(i));

	result = (op1 >> 1) |
		((0-(op1>>(16-1))) << (16 - 1));
	WRITE_VIRTUAL_16BIT_REG(MODRMrm(i),result);
#if (HOST_CPU_IS_I80386==0)
	SET_FLAGS_OSZPC_16(op1,IMMEDIATEIb(i),result,BX_INSTR_SAR16)
#endif //#if (HOST_CPU_IS_I80386==0)
#if (HOST_CPU_IS_I80386==1)
	Bit32u x86_lf_flags = BX_CPU_CLASS_PTR eflags.x86.eax;
	count = IMMEDIATEIb(i);
	__asm
	{
		mov eax,x86_lf_flags
		cmp al,0x81
		sahf
		mov cl,count
		SAR op1,cl
		lahf
		seto al
		mov x86_lf_flags,eax
	}

	BX_CPU_CLASS_PTR eflags.x86.eax = x86_lf_flags;
#endif //#if (HOST_CPU_IS_I80386==1)
}

	void
BX_CPU_C::SAR_EGd_1(BX_CPU_C *icpu,bxInstruction_c *i)
{
	Bit8u count;
	Bit32u op1,result;
	count = i->Word.shift;
	op1 = READ_VIRTUAL_32BIT_REG(MODRMrm(i));

	result = (op1 >> 1) |
		((0-(op1>>(32-1))) << (32 - 1));
	WRITE_VIRTUAL_32BIT_REG(MODRMrm(i),result);
#if (HOST_CPU_IS_I80386==0)
	SET_FLAGS_OSZPC_32(op1,IMMEDIATEIb(i),result,BX_INSTR_SAR32)
#endif //#if (HOST_CPU_IS_I80386==0)
#if (HOST_CPU_IS_I80386==1)
	Bit32u x86_lf_flags = BX_CPU_CLASS_PTR eflags.x86.eax;
	count = IMMEDIATEIb(i);
	__asm
	{
		mov eax,x86_lf_flags
		cmp al,0x81
		sahf
		mov cl,count
		SAR op1,cl
		lahf
		seto al
		mov x86_lf_flags,eax
	}

	BX_CPU_CLASS_PTR eflags.x86.eax = x86_lf_flags;
#endif //#if (HOST_CPU_IS_I80386==1)
}

	void
BX_CPU_C::ROL_EGb_n(BX_CPU_C *icpu,bxInstruction_c *i)
{
	Bit8u count;
	Bit8u op1,result;
	count = i->Word.shift;
	op1 = READ_VIRTUAL_8BIT_REG(MODRMrm(i));

	result = (op1 << count) | (op1 >> (8-count));
	WRITE_VIRTUAL_8BIT_REG(MODRMrm(i),result);
#if (HOST_CPU_IS_I80386==0)
	SET_FLAGS_XC_8(op1,i->Word.shift,result,BX_INSTR_ROL8)
#endif //#if (HOST_CPU_IS_I80386==0)
#if (HOST_CPU_IS_I80386==1)
	Bit32u x86_lf_flags = BX_CPU_CLASS_PTR eflags.x86.eax;
	count = IMMEDIATEIb(i);
	__asm
	{
		mov eax,x86_lf_flags
		cmp al,0x81
		sahf
		mov cl,count
		ROL op1,cl
		lahf
		seto al
		mov x86_lf_flags,eax
	}

	BX_CPU_CLASS_PTR eflags.x86.eax = x86_lf_flags;
#endif //#if (HOST_CPU_IS_I80386==1)
}

	void
BX_CPU_C::ROL_EGw_n(BX_CPU_C *icpu,bxInstruction_c *i)
{
	Bit8u count;
	Bit16u op1,result;
	count = i->Word.shift;
	op1 = READ_VIRTUAL_16BIT_REG(MODRMrm(i));

	result = (op1 << count) | (op1 >> (16-count));
	WRITE_VIRTUAL_16BIT_REG(MODRMrm(i),result);
#if (HOST_CPU_IS_I80386==0)
	SET_FLAGS_XC_16(op1,i->Word.shift,result,BX_INSTR_ROL16)
#endif //#if (HOST_CPU_IS_I80386==0)
#if (HOST_CPU_IS_I80386==1)
	Bit32u x86_lf_flags = BX_CPU_CLASS_PTR eflags.x86.eax;
	count = IMMEDIATEIb(i);
	__asm
	{
		mov eax,x86_lf_flags
		cmp al,0x81
		sahf
		mov cl,count
		ROL op1,cl
		lahf
		seto al
		mov x86_lf_flags,eax
	}

	BX_CPU_CLASS_PTR eflags.x86.eax = x86_lf_flags;
#endif //#if (HOST_CPU_IS_I80386==1)
}

	void
BX_CPU_C::ROL_EGd_n(BX_CPU_C *icpu,bxInstruction_c *i)
{
	Bit8u count;
	Bit32u op1,result;
	count = i->Word.shift;
	op1 = READ_VIRTUAL_32BIT_REG(MODRMrm(i));

	result = (op1 << count) | (op1 >> (32-count));
	WRITE_VIRTUAL_32BIT_REG(MODRMrm(i),result);
#if (HOST_CPU_IS_I80386==0)
	SET_FLAGS_XC_32(op1,i->Word.shift,result,BX_INSTR_ROL32)
#endif //#if (HOST_CPU_IS_I80386==0)
#if (HOST_CPU_IS_I80386==1)
	Bit32u x86_lf_flags = BX_CPU_CLASS_PTR eflags.x86.eax;
	count = IMMEDIATEIb(i);
	__asm
	{
		mov eax,x86_lf_flags
		cmp al,0x81
		sahf
		mov cl,count
		ROL op1,cl
		lahf
		seto al
		mov x86_lf_flags,eax
	}

	BX_CPU_CLASS_PTR eflags.x86.eax = x86_lf_flags;
#endif //#if (HOST_CPU_IS_I80386==1)
}

	void
BX_CPU_C::ROR_EGb_n(BX_CPU_C *icpu,bxInstruction_c *i)
{
	Bit8u count;
	Bit8u op1,result;
	count = i->Word.shift;
	op1 = READ_VIRTUAL_8BIT_REG(MODRMrm(i));

	result = (op1 >> count) | (op1 << (8-count));
	WRITE_VIRTUAL_8BIT_REG(MODRMrm(i),result);
#if (HOST_CPU_IS_I80386==0)
	SET_FLAGS_XC_8(op1,i->Word.shift,result,BX_INSTR_ROR8)
#endif //#if (HOST_CPU_IS_I80386==0)
#if (HOST_CPU_IS_I80386==1)
	Bit32u x86_lf_flags = BX_CPU_CLASS_PTR eflags.x86.eax;
	count = IMMEDIATEIb(i);
	__asm
	{
		mov eax,x86_lf_flags
		cmp al,0x81
		sahf
		mov cl,count
		ROR op1,cl
		lahf
		seto al
		mov x86_lf_flags,eax
	}

	BX_CPU_CLASS_PTR eflags.x86.eax = x86_lf_flags;
#endif //#if (HOST_CPU_IS_I80386==1)
}

	void
BX_CPU_C::ROR_EGw_n(BX_CPU_C *icpu,bxInstruction_c *i)
{
	Bit8u count;
	Bit16u op1,result;
	count = i->Word.shift;
	op1 = READ_VIRTUAL_16BIT_REG(MODRMrm(i));

	result = (op1 >> count) | (op1 << (16-count));
	WRITE_VIRTUAL_16BIT_REG(MODRMrm(i),result);
#if (HOST_CPU_IS_I80386==0)
	SET_FLAGS_XC_16(op1,i->Word.shift,result,BX_INSTR_ROR16)
#endif //#if (HOST_CPU_IS_I80386==0)
#if (HOST_CPU_IS_I80386==1)
	Bit32u x86_lf_flags = BX_CPU_CLASS_PTR eflags.x86.eax;
	count = IMMEDIATEIb(i);
	__asm
	{
		mov eax,x86_lf_flags
		cmp al,0x81
		sahf
		mov cl,count
		ROR op1,cl
		lahf
		seto al
		mov x86_lf_flags,eax
	}

	BX_CPU_CLASS_PTR eflags.x86.eax = x86_lf_flags;
#endif //#if (HOST_CPU_IS_I80386==1)
}

	void
BX_CPU_C::ROR_EGd_n(BX_CPU_C *icpu,bxInstruction_c *i)
{
	Bit8u count;
	Bit32u op1,result;
	count = i->Word.shift;
	op1 = READ_VIRTUAL_32BIT_REG(MODRMrm(i));

	result = (op1 >> count) | (op1 << (32-count));
	WRITE_VIRTUAL_32BIT_REG(MODRMrm(i),result);
#if (HOST_CPU_IS_I80386==0)
	SET_FLAGS_XC_32(op1,i->Word.shift,result,BX_INSTR_ROR32)
#endif //#if (HOST_CPU_IS_I80386==0)
#if (HOST_CPU_IS_I80386==1)
	Bit32u x86_lf_flags = BX_CPU_CLASS_PTR eflags.x86.eax;
	count = IMMEDIATEIb(i);
	__asm
	{
		mov eax,x86_lf_flags
		cmp al,0x81
		sahf
		mov cl,count
		ROR op1,cl
		lahf
		seto al
		mov x86_lf_flags,eax
	}

	BX_CPU_CLASS_PTR eflags.x86.eax = x86_lf_flags;
#endif //#if (HOST_CPU_IS_I80386==1)
}

	void
BX_CPU_C::RCL_EGb_n(BX_CPU_C *icpu,bxInstruction_c *i)
{
	Bit8u count;
	Bit8u op1,result;
	count = i->Word.shift;
	op1 = READ_VIRTUAL_8BIT_REG(MODRMrm(i));

	result = (op1 << count) | (op1 >> ((8+1) - count)) |
		(BX_CPU_CLASS_PTR get_CF() << (count - 1));
	WRITE_VIRTUAL_8BIT_REG(MODRMrm(i),result);
#if (HOST_CPU_IS_I80386==0)
	SET_FLAGS_XC_8(op1,i->Word.shift,result,BX_INSTR_RCL8)
#endif //#if (HOST_CPU_IS_I80386==0)
#if (HOST_CPU_IS_I80386==1)
	Bit32u x86_lf_flags = BX_CPU_CLASS_PTR eflags.x86.eax;
	count = IMMEDIATEIb(i);
	__asm
	{
		mov eax,x86_lf_flags
		cmp al,0x81
		sahf
		mov cl,count
		RCL op1,cl
		lahf
		seto al
		mov x86_lf_flags,eax
	}

	BX_CPU_CLASS_PTR eflags.x86.eax = x86_lf_flags;
#endif //#if (HOST_CPU_IS_I80386==1)
}

	void
BX_CPU_C::RCL_EGw_n(BX_CPU_C *icpu,bxInstruction_c *i)
{
	Bit8u count;
	Bit16u op1,result;
	count = i->Word.shift;
	op1 = READ_VIRTUAL_16BIT_REG(MODRMrm(i));

	result = (op1 << count) | (op1 >> ((16+1) - count)) |
		(BX_CPU_CLASS_PTR get_CF() << (count - 1));
	WRITE_VIRTUAL_16BIT_REG(MODRMrm(i),result);
#if (HOST_CPU_IS_I80386==0)
	SET_FLAGS_XC_16(op1,i->Word.shift,result,BX_INSTR_RCL16)
#endif //#if (HOST_CPU_IS_I80386==0)
#if (HOST_CPU_IS_I80386==1)
	Bit32u x86_lf_flags = BX_CPU_CLASS_PTR eflags.x86.eax;
	count = IMMEDIATEIb(i);
	__asm
	{
		mov eax,x86_lf_flags
		cmp al,0x81
		sahf
		mov cl,count
		RCL op1,cl
		lahf
		seto al
		mov x86_lf_flags,eax
	}

	BX_CPU_CLASS_PTR eflags.x86.eax = x86_lf_flags;
#endif //#if (HOST_CPU_IS_I80386==1)
}

	void
BX_CPU_C::RCL_EGd_n(BX_CPU_C *icpu,bxInstruction_c *i)
{
	Bit8u count;
	Bit32u op1,result;
	count = i->Word.shift;
	op1 = READ_VIRTUAL_32BIT_REG(MODRMrm(i));

	result = (op1 << count) | (op1 >> ((32+1) - count)) |
		(BX_CPU_CLASS_PTR get_CF() << (count - 1));
	WRITE_VIRTUAL_32BIT_REG(MODRMrm(i),result);
#if (HOST_CPU_IS_I80386==0)
	SET_FLAGS_XC_32(op1,i->Word.shift,result,BX_INSTR_RCL32)
#endif //#if (HOST_CPU_IS_I80386==0)
#if (HOST_CPU_IS_I80386==1)
	Bit32u x86_lf_flags = BX_CPU_CLASS_PTR eflags.x86.eax;
	count = IMMEDIATEIb(i);
	__asm
	{
		mov eax,x86_lf_flags
		cmp al,0x81
		sahf
		mov cl,count
		RCL op1,cl
		lahf
		seto al
		mov x86_lf_flags,eax
	}

	BX_CPU_CLASS_PTR eflags.x86.eax = x86_lf_flags;
#endif //#if (HOST_CPU_IS_I80386==1)
}

	void
BX_CPU_C::RCR_EGb_n(BX_CPU_C *icpu,bxInstruction_c *i)
{
	Bit8u count;
	Bit8u op1,result;
	count = i->Word.shift;
	op1 = READ_VIRTUAL_8BIT_REG(MODRMrm(i));

	result = (op1 >> count) | (op1 << ((8+1) - count)) |
		(BX_CPU_CLASS_PTR get_CF() << (8 - count));
	WRITE_VIRTUAL_8BIT_REG(MODRMrm(i),result);
#if (HOST_CPU_IS_I80386==0)
	SET_FLAGS_XC_8(op1,i->Word.shift,result,BX_INSTR_RCR8)
#endif //#if (HOST_CPU_IS_I80386==0)
#if (HOST_CPU_IS_I80386==1)
	Bit32u x86_lf_flags = BX_CPU_CLASS_PTR eflags.x86.eax;
	count = IMMEDIATEIb(i);
	__asm
	{
		mov eax,x86_lf_flags
		cmp al,0x81
		sahf
		mov cl,count
		RCR op1,cl
		lahf
		seto al
		mov x86_lf_flags,eax
	}

	BX_CPU_CLASS_PTR eflags.x86.eax = x86_lf_flags;
#endif //#if (HOST_CPU_IS_I80386==1)
}

	void
BX_CPU_C::RCR_EGw_n(BX_CPU_C *icpu,bxInstruction_c *i)
{
	Bit8u count;
	Bit16u op1,result;
	count = i->Word.shift;
	op1 = READ_VIRTUAL_16BIT_REG(MODRMrm(i));

	result = (op1 >> count) | (op1 << ((16+1) - count)) |
		(BX_CPU_CLASS_PTR get_CF() << (16 - count));
	WRITE_VIRTUAL_16BIT_REG(MODRMrm(i),result);
#if (HOST_CPU_IS_I80386==0)
	SET_FLAGS_XC_16(op1,i->Word.shift,result,BX_INSTR_RCR16)
#endif //#if (HOST_CPU_IS_I80386==0)
#if (HOST_CPU_IS_I80386==1)
	Bit32u x86_lf_flags = BX_CPU_CLASS_PTR eflags.x86.eax;
	count = IMMEDIATEIb(i);
	__asm
	{
		mov eax,x86_lf_flags
		cmp al,0x81
		sahf
		mov cl,count
		RCR op1,cl
		lahf
		seto al
		mov x86_lf_flags,eax
	}

	BX_CPU_CLASS_PTR eflags.x86.eax = x86_lf_flags;
#endif //#if (HOST_CPU_IS_I80386==1)
}

	void
BX_CPU_C::RCR_EGd_n(BX_CPU_C *icpu,bxInstruction_c *i)
{
	Bit8u count;
	Bit32u op1,result;
	count = i->Word.shift;
	op1 = READ_VIRTUAL_32BIT_REG(MODRMrm(i));

	result = (op1 >> count) | (op1 << ((32+1) - count)) |
		(BX_CPU_CLASS_PTR get_CF() << (32 - count));
	WRITE_VIRTUAL_32BIT_REG(MODRMrm(i),result);
#if (HOST_CPU_IS_I80386==0)
	SET_FLAGS_XC_32(op1,i->Word.shift,result,BX_INSTR_RCR32)
#endif //#if (HOST_CPU_IS_I80386==0)
#if (HOST_CPU_IS_I80386==1)
	Bit32u x86_lf_flags = BX_CPU_CLASS_PTR eflags.x86.eax;
	count = IMMEDIATEIb(i);
	__asm
	{
		mov eax,x86_lf_flags
		cmp al,0x81
		sahf
		mov cl,count
		RCR op1,cl
		lahf
		seto al
		mov x86_lf_flags,eax
	}

	BX_CPU_CLASS_PTR eflags.x86.eax = x86_lf_flags;
#endif //#if (HOST_CPU_IS_I80386==1)
}

	void
BX_CPU_C::SHL_EGb_n(BX_CPU_C *icpu,bxInstruction_c *i)
{
	Bit8u count;
	Bit8u op1,result;
	count = i->Word.shift;
	op1 = READ_VIRTUAL_8BIT_REG(MODRMrm(i));

	result = (op1 << count);
	WRITE_VIRTUAL_8BIT_REG(MODRMrm(i),result);
#if (HOST_CPU_IS_I80386==0)
	SET_FLAGS_XSZPC_8(op1,IMMEDIATEIb(i),result,BX_INSTR_SHL8)
#endif //#if (HOST_CPU_IS_I80386==0)
#if (HOST_CPU_IS_I80386==1)
	Bit32u x86_lf_flags = BX_CPU_CLASS_PTR eflags.x86.eax;
	count = IMMEDIATEIb(i);
	__asm
	{
		mov eax,x86_lf_flags
		cmp al,0x81
		sahf
		mov cl,count
		SHL op1,cl
		lahf
		seto al
		mov x86_lf_flags,eax
	}

	BX_CPU_CLASS_PTR eflags.x86.eax = x86_lf_flags;
#endif //#if (HOST_CPU_IS_I80386==1)
}

	void
BX_CPU_C::SHL_EGw_n(BX_CPU_C *icpu,bxInstruction_c *i)
{
	Bit8u count;
	Bit16u op1,result;
	count = i->Word.shift;
	op1 = READ_VIRTUAL_16BIT_REG(MODRMrm(i));

	result = (op1 << count);
	WRITE_VIRTUAL_16BIT_REG(MODRMrm(i),result);
#if (HOST_CPU_IS_I80386==0)
	SET_FLAGS_XSZPC_16(op1,IMMEDIATEIb(i),result,BX_INSTR_SHL16)
#endif //#if (HOST_CPU_IS_I80386==0)
#if (HOST_CPU_IS_I80386==1)
	Bit32u x86_lf_flags = BX_CPU_CLASS_PTR eflags.x86.eax;
	count = IMMEDIATEIb(i);
	__asm
	{
		mov eax,x86_lf_flags
		cmp al,0x81
		sahf
		mov cl,count
		SHL op1,cl
		lahf
		seto al
		mov x86_lf_flags,eax
	}

	BX_CPU_CLASS_PTR eflags.x86.eax = x86_lf_flags;
#endif //#if (HOST_CPU_IS_I80386==1)
}

	void
BX_CPU_C::SHL_EGd_n(BX_CPU_C *icpu,bxInstruction_c *i)
{
	Bit8u count;
	Bit32u op1,result;
	count = i->Word.shift;
	op1 = READ_VIRTUAL_32BIT_REG(MODRMrm(i));

	result = (op1 << count);
	WRITE_VIRTUAL_32BIT_REG(MODRMrm(i),result);
#if (HOST_CPU_IS_I80386==0)
	SET_FLAGS_XSZPC_32(op1,IMMEDIATEIb(i),result,BX_INSTR_SHL32)
#endif //#if (HOST_CPU_IS_I80386==0)
#if (HOST_CPU_IS_I80386==1)
	Bit32u x86_lf_flags = BX_CPU_CLASS_PTR eflags.x86.eax;
	count = IMMEDIATEIb(i);
	__asm
	{
		mov eax,x86_lf_flags
		cmp al,0x81
		sahf
		mov cl,count
		SHL op1,cl
		lahf
		seto al
		mov x86_lf_flags,eax
	}

	BX_CPU_CLASS_PTR eflags.x86.eax = x86_lf_flags;
#endif //#if (HOST_CPU_IS_I80386==1)
}

	void
BX_CPU_C::SHR_EGb_n(BX_CPU_C *icpu,bxInstruction_c *i)
{
	Bit8u count;
	Bit8u op1,result;
	count = i->Word.shift;
	op1 = READ_VIRTUAL_8BIT_REG(MODRMrm(i));

	result = (op1 >> count);
	WRITE_VIRTUAL_8BIT_REG(MODRMrm(i),result);
#if (HOST_CPU_IS_I80386==0)
	SET_FLAGS_XSZPC_8(op1,IMMEDIATEIb(i),result,BX_INSTR_SHR8)
#endif //#if (HOST_CPU_IS_I80386==0)
#if (HOST_CPU_IS_I80386==1)
	Bit32u x86_lf_flags = BX_CPU_CLASS_PTR eflags.x86.eax;
	count = IMMEDIATEIb(i);
	__asm
	{
		mov eax,x86_lf_flags
		cmp al,0x81
		sahf
		mov cl,count
		SHR op1,cl
		lahf
		seto al
		mov x86_lf_flags,eax
	}

	BX_CPU_CLASS_PTR eflags.x86.eax = x86_lf_flags;
#endif //#if (HOST_CPU_IS_I80386==1)
}

	void
BX_CPU_C::SHR_EGw_n(BX_CPU_C *icpu,bxInstruction_c *i)
{
	Bit8u count;
	Bit16u op1,result;
	count = i->Word.shift;
	op1 = READ_VIRTUAL_16BIT_REG(MODRMrm(i));

	result = (op1 >> count);
	WRITE_VIRTUAL_16BIT_REG(MODRMrm(i),result);
#if (HOST_CPU_IS_I80386==0)
	SET_FLAGS_XSZPC_16(op1,IMMEDIATEIb(i),result,BX_INSTR_SHR16)
#endif //#if (HOST_CPU_IS_I80386==0)
#if (HOST_CPU_IS_I80386==1)
	Bit32u x86_lf_flags = BX_CPU_CLASS_PTR eflags.x86.eax;
	count = IMMEDIATEIb(i);
	__asm
	{
		mov eax,x86_lf_flags
		cmp al,0x81
		sahf
		mov cl,count
		SHR op1,cl
		lahf
		seto al
		mov x86_lf_flags,eax
	}

	BX_CPU_CLASS_PTR eflags.x86.eax = x86_lf_flags;
#endif //#if (HOST_CPU_IS_I80386==1)
}

	void
BX_CPU_C::SHR_EGd_n(BX_CPU_C *icpu,bxInstruction_c *i)
{
	Bit8u count;
	Bit32u op1,result;
	count = i->Word.shift;
	op1 = READ_VIRTUAL_32BIT_REG(MODRMrm(i));

	result = (op1 >> count);
	WRITE_VIRTUAL_32BIT_REG(MODRMrm(i),result);
#if (HOST_CPU_IS_I80386==0)
	SET_FLAGS_XSZPC_32(op1,IMMEDIATEIb(i),result,BX_INSTR_SHR32)
#endif //#if (HOST_CPU_IS_I80386==0)
#if (HOST_CPU_IS_I80386==1)
	Bit32u x86_lf_flags = BX_CPU_CLASS_PTR eflags.x86.eax;
	count = IMMEDIATEIb(i);
	__asm
	{
		mov eax,x86_lf_flags
		cmp al,0x81
		sahf
		mov cl,count
		SHR op1,cl
		lahf
		seto al
		mov x86_lf_flags,eax
	}

	BX_CPU_CLASS_PTR eflags.x86.eax = x86_lf_flags;
#endif //#if (HOST_CPU_IS_I80386==1)
}

	void
BX_CPU_C::SAR_EGb_n(BX_CPU_C *icpu,bxInstruction_c *i)
{
	Bit8u count;
	Bit8u op1,result;
	count = i->Word.shift;
	op1 = READ_VIRTUAL_8BIT_REG(MODRMrm(i));

	result = (op1 >> count) |
		((0-(op1>>(8-1))) << (8 - count));
	WRITE_VIRTUAL_8BIT_REG(MODRMrm(i),result);
#if (HOST_CPU_IS_I80386==0)
	SET_FLAGS_XSZPC_8(op1,IMMEDIATEIb(i),result,BX_INSTR_SAR8)
#endif //#if (HOST_CPU_IS_I80386==0)
#if (HOST_CPU_IS_I80386==1)
	Bit32u x86_lf_flags = BX_CPU_CLASS_PTR eflags.x86.eax;
	count = IMMEDIATEIb(i);
	__asm
	{
		mov eax,x86_lf_flags
		cmp al,0x81
		sahf
		mov cl,count
		SAR op1,cl
		lahf
		seto al
		mov x86_lf_flags,eax
	}

	BX_CPU_CLASS_PTR eflags.x86.eax = x86_lf_flags;
#endif //#if (HOST_CPU_IS_I80386==1)
}

	void
BX_CPU_C::SAR_EGw_n(BX_CPU_C *icpu,bxInstruction_c *i)
{
	Bit8u count;
	Bit16u op1,result;
	count = i->Word.shift;
	op1 = READ_VIRTUAL_16BIT_REG(MODRMrm(i));

	result = (op1 >> count) |
		((0-(op1>>(16-1))) << (16 - count));
	WRITE_VIRTUAL_16BIT_REG(MODRMrm(i),result);
#if (HOST_CPU_IS_I80386==0)
	SET_FLAGS_XSZPC_16(op1,IMMEDIATEIb(i),result,BX_INSTR_SAR16)
#endif //#if (HOST_CPU_IS_I80386==0)
#if (HOST_CPU_IS_I80386==1)
	Bit32u x86_lf_flags = BX_CPU_CLASS_PTR eflags.x86.eax;
	count = IMMEDIATEIb(i);
	__asm
	{
		mov eax,x86_lf_flags
		cmp al,0x81
		sahf
		mov cl,count
		SAR op1,cl
		lahf
		seto al
		mov x86_lf_flags,eax
	}

	BX_CPU_CLASS_PTR eflags.x86.eax = x86_lf_flags;
#endif //#if (HOST_CPU_IS_I80386==1)
}

	void
BX_CPU_C::SAR_EGd_n(BX_CPU_C *icpu,bxInstruction_c *i)
{
	Bit8u count;
	Bit32u op1,result;
	count = i->Word.shift;
	op1 = READ_VIRTUAL_32BIT_REG(MODRMrm(i));

	result = (op1 >> count) |
		((0-(op1>>(32-1))) << (32 - count));
	WRITE_VIRTUAL_32BIT_REG(MODRMrm(i),result);
#if (HOST_CPU_IS_I80386==0)
	SET_FLAGS_XSZPC_32(op1,IMMEDIATEIb(i),result,BX_INSTR_SAR32)
#endif //#if (HOST_CPU_IS_I80386==0)
#if (HOST_CPU_IS_I80386==1)
	Bit32u x86_lf_flags = BX_CPU_CLASS_PTR eflags.x86.eax;
	count = IMMEDIATEIb(i);
	__asm
	{
		mov eax,x86_lf_flags
		cmp al,0x81
		sahf
		mov cl,count
		SAR op1,cl
		lahf
		seto al
		mov x86_lf_flags,eax
	}

	BX_CPU_CLASS_PTR eflags.x86.eax = x86_lf_flags;
#endif //#if (HOST_CPU_IS_I80386==1)
}

	void
BX_CPU_C::SHLD_EGwGw_1(BX_CPU_C *icpu,bxInstruction_c *i)
{
	Bit8u count;
	Bit16u op1,op2,result;
	count = i->Word.shift;
	op1 = READ_VIRTUAL_16BIT_REG(MODRMrm(i));

	op2 = READ_VIRTUAL_16BIT_REG(MODRMnnn(i));

	result = (op1 << 1) | (op2 >> (16 - 1));
	WRITE_VIRTUAL_16BIT_REG(MODRMrm(i),result);
#if (HOST_CPU_IS_I80386==0)
	SET3_FLAGS_OSZPC_16(op1,op2,IMMEDIATEIb(i),result,BX_INSTR_SHLD16)
#endif //#if (HOST_CPU_IS_I80386==0)
#if (HOST_CPU_IS_I80386==1)
	Bit32u x86_lf_flags = BX_CPU_CLASS_PTR eflags.x86.eax;
	count = IMMEDIATEIb(i);
	__asm
	{
		mov eax,x86_lf_flags
		cmp al,0x81
		sahf
		mov cl,count
		mov dx,op2
		SHLD op1,dx,cl
		lahf
		seto al
		mov x86_lf_flags,eax
	}

	BX_CPU_CLASS_PTR eflags.x86.eax = x86_lf_flags;
#endif //#if (HOST_CPU_IS_I80386==1)
}

	void
BX_CPU_C::SHLD_EGdGd_1(BX_CPU_C *icpu,bxInstruction_c *i)
{
	Bit8u count;
	Bit32u op1,op2,result;
	count = i->Word.shift;
	op1 = READ_VIRTUAL_32BIT_REG(MODRMrm(i));

	op2 = READ_VIRTUAL_32BIT_REG(MODRMnnn(i));

	result = (op1 << 1) | (op2 >> (32 - 1));
	WRITE_VIRTUAL_32BIT_REG(MODRMrm(i),result);
#if (HOST_CPU_IS_I80386==0)
	SET3_FLAGS_OSZPC_32(op1,op2,IMMEDIATEIb(i),result,BX_INSTR_SHLD32)
#endif //#if (HOST_CPU_IS_I80386==0)
#if (HOST_CPU_IS_I80386==1)
	Bit32u x86_lf_flags = BX_CPU_CLASS_PTR eflags.x86.eax;
	count = IMMEDIATEIb(i);
	__asm
	{
		mov eax,x86_lf_flags
		cmp al,0x81
		sahf
		mov cl,count
		mov edx,op2
		SHLD op1,edx,cl
		lahf
		seto al
		mov x86_lf_flags,eax
	}

	BX_CPU_CLASS_PTR eflags.x86.eax = x86_lf_flags;
#endif //#if (HOST_CPU_IS_I80386==1)
}

	void
BX_CPU_C::SHRD_EGwGw_1(BX_CPU_C *icpu,bxInstruction_c *i)
{
	Bit8u count;
	Bit16u op1,op2,result;
	count = i->Word.shift;
	op1 = READ_VIRTUAL_16BIT_REG(MODRMrm(i));

	op2 = READ_VIRTUAL_16BIT_REG(MODRMnnn(i));

	result = (op1 >> 1) | (op2 << (16 - 1));
	WRITE_VIRTUAL_16BIT_REG(MODRMrm(i),result);
#if (HOST_CPU_IS_I80386==0)
	SET3_FLAGS_OSZPC_16(op1,op2,IMMEDIATEIb(i),result,BX_INSTR_SHRD16)
#endif //#if (HOST_CPU_IS_I80386==0)
#if (HOST_CPU_IS_I80386==1)
	Bit32u x86_lf_flags = BX_CPU_CLASS_PTR eflags.x86.eax;
	count = IMMEDIATEIb(i);
	__asm
	{
		mov eax,x86_lf_flags
		cmp al,0x81
		sahf
		mov cl,count
		mov dx,op2
		SHRD op1,dx,cl
		lahf
		seto al
		mov x86_lf_flags,eax
	}

	BX_CPU_CLASS_PTR eflags.x86.eax = x86_lf_flags;
#endif //#if (HOST_CPU_IS_I80386==1)
}

	void
BX_CPU_C::SHRD_EGdGd_1(BX_CPU_C *icpu,bxInstruction_c *i)
{
	Bit8u count;
	Bit32u op1,op2,result;
	count = i->Word.shift;
	op1 = READ_VIRTUAL_32BIT_REG(MODRMrm(i));

	op2 = READ_VIRTUAL_32BIT_REG(MODRMnnn(i));

	result = (op1 >> 1) | (op2 << (32 - 1));
	WRITE_VIRTUAL_32BIT_REG(MODRMrm(i),result);
#if (HOST_CPU_IS_I80386==0)
	SET3_FLAGS_OSZPC_32(op1,op2,IMMEDIATEIb(i),result,BX_INSTR_SHRD32)
#endif //#if (HOST_CPU_IS_I80386==0)
#if (HOST_CPU_IS_I80386==1)
	Bit32u x86_lf_flags = BX_CPU_CLASS_PTR eflags.x86.eax;
	count = IMMEDIATEIb(i);
	__asm
	{
		mov eax,x86_lf_flags
		cmp al,0x81
		sahf
		mov cl,count
		mov edx,op2
		SHRD op1,edx,cl
		lahf
		seto al
		mov x86_lf_flags,eax
	}

	BX_CPU_CLASS_PTR eflags.x86.eax = x86_lf_flags;
#endif //#if (HOST_CPU_IS_I80386==1)
}

	void
BX_CPU_C::SHLD_EGwGw_n(BX_CPU_C *icpu,bxInstruction_c *i)
{
	Bit8u count;
	Bit16u op1,op2,result;
	count = i->Word.shift;
	op1 = READ_VIRTUAL_16BIT_REG(MODRMrm(i));

	op2 = READ_VIRTUAL_16BIT_REG(MODRMnnn(i));

	result = (op1 << count) | (op2 >> (16 - count));
	WRITE_VIRTUAL_16BIT_REG(MODRMrm(i),result);
#if (HOST_CPU_IS_I80386==0)
	SET3_FLAGS_XSZPC_16(op1,op2,IMMEDIATEIb(i),result,BX_INSTR_SHLD16)
#endif //#if (HOST_CPU_IS_I80386==0)
#if (HOST_CPU_IS_I80386==1)
	Bit32u x86_lf_flags = BX_CPU_CLASS_PTR eflags.x86.eax;
	count = IMMEDIATEIb(i);
	__asm
	{
		mov eax,x86_lf_flags
		cmp al,0x81
		sahf
		mov cl,count
		mov dx,op2
		SHLD op1,dx,cl
		lahf
		seto al
		mov x86_lf_flags,eax
	}

	BX_CPU_CLASS_PTR eflags.x86.eax = x86_lf_flags;
#endif //#if (HOST_CPU_IS_I80386==1)
}

	void
BX_CPU_C::SHLD_EGdGd_n(BX_CPU_C *icpu,bxInstruction_c *i)
{
	Bit8u count;
	Bit32u op1,op2,result;
	count = i->Word.shift;
	op1 = READ_VIRTUAL_32BIT_REG(MODRMrm(i));

	op2 = READ_VIRTUAL_32BIT_REG(MODRMnnn(i));

	result = (op1 << count) | (op2 >> (32 - count));
	WRITE_VIRTUAL_32BIT_REG(MODRMrm(i),result);
#if (HOST_CPU_IS_I80386==0)
	SET3_FLAGS_XSZPC_32(op1,op2,IMMEDIATEIb(i),result,BX_INSTR_SHLD32)
#endif //#if (HOST_CPU_IS_I80386==0)
#if (HOST_CPU_IS_I80386==1)
	Bit32u x86_lf_flags = BX_CPU_CLASS_PTR eflags.x86.eax;
	count = IMMEDIATEIb(i);
	__asm
	{
		mov eax,x86_lf_flags
		cmp al,0x81
		sahf
		mov cl,count
		mov edx,op2
		SHLD op1,edx,cl
		lahf
		seto al
		mov x86_lf_flags,eax
	}

	BX_CPU_CLASS_PTR eflags.x86.eax = x86_lf_flags;
#endif //#if (HOST_CPU_IS_I80386==1)
}

	void
BX_CPU_C::SHRD_EGwGw_n(BX_CPU_C *icpu,bxInstruction_c *i)
{
	Bit8u count;
	Bit16u op1,op2,result;
	count = i->Word.shift;
	op1 = READ_VIRTUAL_16BIT_REG(MODRMrm(i));

	op2 = READ_VIRTUAL_16BIT_REG(MODRMnnn(i));

	result = (op1 >> count) | (op2 << (16 - count));
	WRITE_VIRTUAL_16BIT_REG(MODRMrm(i),result);
#if (HOST_CPU_IS_I80386==0)
	SET3_FLAGS_XSZPC_16(op1,op2,IMMEDIATEIb(i),result,BX_INSTR_SHRD16)
#endif //#if (HOST_CPU_IS_I80386==0)
#if (HOST_CPU_IS_I80386==1)
	Bit32u x86_lf_flags = BX_CPU_CLASS_PTR eflags.x86.eax;
	count = IMMEDIATEIb(i);
	__asm
	{
		mov eax,x86_lf_flags
		cmp al,0x81
		sahf
		mov cl,count
		mov dx,op2
		SHRD op1,dx,cl
		lahf
		seto al
		mov x86_lf_flags,eax
	}

	BX_CPU_CLASS_PTR eflags.x86.eax = x86_lf_flags;
#endif //#if (HOST_CPU_IS_I80386==1)
}

	void
BX_CPU_C::SHRD_EGdGd_n(BX_CPU_C *icpu,bxInstruction_c *i)
{
	Bit8u count;
	Bit32u op1,op2,result;
	count = i->Word.shift;
	op1 = READ_VIRTUAL_32BIT_REG(MODRMrm(i));

	op2 = READ_VIRTUAL_32BIT_REG(MODRMnnn(i));

	result = (op1 >> count) | (op2 << (32 - count));
	WRITE_VIRTUAL_32BIT_REG(MODRMrm(i),result);
#if (HOST_CPU_IS_I80386==0)
	SET3_FLAGS_XSZPC_32(op1,op2,IMMEDIATEIb(i),result,BX_INSTR_SHRD32)
#endif //#if (HOST_CPU_IS_I80386==0)
#if (HOST_CPU_IS_I80386==1)
	Bit32u x86_lf_flags = BX_CPU_CLASS_PTR eflags.x86.eax;
	count = IMMEDIATEIb(i);
	__asm
	{
		mov eax,x86_lf_flags
		cmp al,0x81
		sahf
		mov cl,count
		mov edx,op2
		SHRD op1,edx,cl
		lahf
		seto al
		mov x86_lf_flags,eax
	}

	BX_CPU_CLASS_PTR eflags.x86.eax = x86_lf_flags;
#endif //#if (HOST_CPU_IS_I80386==1)
}

	void
BX_CPU_C::ROL_EEb_1(BX_CPU_C *icpu,bxInstruction_c *i)
{
	Bit8u count;
	Bit8u op1,result;
	count = i->Word.shift;
	READ_RMW_VIRTUAL_BYTE(MODRMSeg(i),RMAddr(i),&op1);

	result = (op1 << 1) | (op1 >> (8-1));
	WRITE_RMW_VIRTUAL_BYTE(result);
#if (HOST_CPU_IS_I80386==0)
	SET_FLAGS_OC_8(op1,i->Word.shift,result,BX_INSTR_ROL8)
#endif //#if (HOST_CPU_IS_I80386==0)
#if (HOST_CPU_IS_I80386==1)
	Bit32u x86_lf_flags = BX_CPU_CLASS_PTR eflags.x86.eax;
	count = IMMEDIATEIb(i);
	__asm
	{
		mov eax,x86_lf_flags
		cmp al,0x81
		sahf
		mov cl,count
		ROL op1,cl
		lahf
		seto al
		mov x86_lf_flags,eax
	}

	BX_CPU_CLASS_PTR eflags.x86.eax = x86_lf_flags;
#endif //#if (HOST_CPU_IS_I80386==1)
}

	void
BX_CPU_C::ROL_EEw_1(BX_CPU_C *icpu,bxInstruction_c *i)
{
	Bit8u count;
	Bit16u op1,result;
	count = i->Word.shift;
	READ_RMW_VIRTUAL_WORD(MODRMSeg(i),RMAddr(i),&op1);

	result = (op1 << 1) | (op1 >> (16-1));
	WRITE_RMW_VIRTUAL_WORD(result);
#if (HOST_CPU_IS_I80386==0)
	SET_FLAGS_OC_16(op1,i->Word.shift,result,BX_INSTR_ROL16)
#endif //#if (HOST_CPU_IS_I80386==0)
#if (HOST_CPU_IS_I80386==1)
	Bit32u x86_lf_flags = BX_CPU_CLASS_PTR eflags.x86.eax;
	count = IMMEDIATEIb(i);
	__asm
	{
		mov eax,x86_lf_flags
		cmp al,0x81
		sahf
		mov cl,count
		ROL op1,cl
		lahf
		seto al
		mov x86_lf_flags,eax
	}

	BX_CPU_CLASS_PTR eflags.x86.eax = x86_lf_flags;
#endif //#if (HOST_CPU_IS_I80386==1)
}

	void
BX_CPU_C::ROL_EEd_1(BX_CPU_C *icpu,bxInstruction_c *i)
{
	Bit8u count;
	Bit32u op1,result;
	count = i->Word.shift;
	READ_RMW_VIRTUAL_DWORD(MODRMSeg(i),RMAddr(i),&op1);

	result = (op1 << 1) | (op1 >> (32-1));
	WRITE_RMW_VIRTUAL_DWORD(result);
#if (HOST_CPU_IS_I80386==0)
	SET_FLAGS_OC_32(op1,i->Word.shift,result,BX_INSTR_ROL32)
#endif //#if (HOST_CPU_IS_I80386==0)
#if (HOST_CPU_IS_I80386==1)
	Bit32u x86_lf_flags = BX_CPU_CLASS_PTR eflags.x86.eax;
	count = IMMEDIATEIb(i);
	__asm
	{
		mov eax,x86_lf_flags
		cmp al,0x81
		sahf
		mov cl,count
		ROL op1,cl
		lahf
		seto al
		mov x86_lf_flags,eax
	}

	BX_CPU_CLASS_PTR eflags.x86.eax = x86_lf_flags;
#endif //#if (HOST_CPU_IS_I80386==1)
}

	void
BX_CPU_C::ROR_EEb_1(BX_CPU_C *icpu,bxInstruction_c *i)
{
	Bit8u count;
	Bit8u op1,result;
	count = i->Word.shift;
	READ_RMW_VIRTUAL_BYTE(MODRMSeg(i),RMAddr(i),&op1);

	result = (op1 >> 1) | (op1 << (8-1));
	WRITE_RMW_VIRTUAL_BYTE(result);
#if (HOST_CPU_IS_I80386==0)
	SET_FLAGS_OC_8(op1,i->Word.shift,result,BX_INSTR_ROR8)
#endif //#if (HOST_CPU_IS_I80386==0)
#if (HOST_CPU_IS_I80386==1)
	Bit32u x86_lf_flags = BX_CPU_CLASS_PTR eflags.x86.eax;
	count = IMMEDIATEIb(i);
	__asm
	{
		mov eax,x86_lf_flags
		cmp al,0x81
		sahf
		mov cl,count
		ROR op1,cl
		lahf
		seto al
		mov x86_lf_flags,eax
	}

	BX_CPU_CLASS_PTR eflags.x86.eax = x86_lf_flags;
#endif //#if (HOST_CPU_IS_I80386==1)
}

	void
BX_CPU_C::ROR_EEw_1(BX_CPU_C *icpu,bxInstruction_c *i)
{
	Bit8u count;
	Bit16u op1,result;
	count = i->Word.shift;
	READ_RMW_VIRTUAL_WORD(MODRMSeg(i),RMAddr(i),&op1);

	result = (op1 >> 1) | (op1 << (16-1));
	WRITE_RMW_VIRTUAL_WORD(result);
#if (HOST_CPU_IS_I80386==0)
	SET_FLAGS_OC_16(op1,i->Word.shift,result,BX_INSTR_ROR16)
#endif //#if (HOST_CPU_IS_I80386==0)
#if (HOST_CPU_IS_I80386==1)
	Bit32u x86_lf_flags = BX_CPU_CLASS_PTR eflags.x86.eax;
	count = IMMEDIATEIb(i);
	__asm
	{
		mov eax,x86_lf_flags
		cmp al,0x81
		sahf
		mov cl,count
		ROR op1,cl
		lahf
		seto al
		mov x86_lf_flags,eax
	}

	BX_CPU_CLASS_PTR eflags.x86.eax = x86_lf_flags;
#endif //#if (HOST_CPU_IS_I80386==1)
}

	void
BX_CPU_C::ROR_EEd_1(BX_CPU_C *icpu,bxInstruction_c *i)
{
	Bit8u count;
	Bit32u op1,result;
	count = i->Word.shift;
	READ_RMW_VIRTUAL_DWORD(MODRMSeg(i),RMAddr(i),&op1);

	result = (op1 >> 1) | (op1 << (32-1));
	WRITE_RMW_VIRTUAL_DWORD(result);
#if (HOST_CPU_IS_I80386==0)
	SET_FLAGS_OC_32(op1,i->Word.shift,result,BX_INSTR_ROR32)
#endif //#if (HOST_CPU_IS_I80386==0)
#if (HOST_CPU_IS_I80386==1)
	Bit32u x86_lf_flags = BX_CPU_CLASS_PTR eflags.x86.eax;
	count = IMMEDIATEIb(i);
	__asm
	{
		mov eax,x86_lf_flags
		cmp al,0x81
		sahf
		mov cl,count
		ROR op1,cl
		lahf
		seto al
		mov x86_lf_flags,eax
	}

	BX_CPU_CLASS_PTR eflags.x86.eax = x86_lf_flags;
#endif //#if (HOST_CPU_IS_I80386==1)
}

	void
BX_CPU_C::RCL_EEb_1(BX_CPU_C *icpu,bxInstruction_c *i)
{
	Bit8u count;
	Bit8u op1,result;
	count = i->Word.shift;
	READ_RMW_VIRTUAL_BYTE(MODRMSeg(i),RMAddr(i),&op1);

	result = (op1 << 1) | (BX_CPU_CLASS_PTR get_CF());
	WRITE_RMW_VIRTUAL_BYTE(result);
#if (HOST_CPU_IS_I80386==0)
	SET_FLAGS_OC_8(op1,i->Word.shift,result,BX_INSTR_RCL8)
#endif //#if (HOST_CPU_IS_I80386==0)
#if (HOST_CPU_IS_I80386==1)
	Bit32u x86_lf_flags = BX_CPU_CLASS_PTR eflags.x86.eax;
	count = IMMEDIATEIb(i);
	__asm
	{
		mov eax,x86_lf_flags
		cmp al,0x81
		sahf
		mov cl,count
		RCL op1,cl
		lahf
		seto al
		mov x86_lf_flags,eax
	}

	BX_CPU_CLASS_PTR eflags.x86.eax = x86_lf_flags;
#endif //#if (HOST_CPU_IS_I80386==1)
}

	void
BX_CPU_C::RCL_EEw_1(BX_CPU_C *icpu,bxInstruction_c *i)
{
	Bit8u count;
	Bit16u op1,result;
	count = i->Word.shift;
	READ_RMW_VIRTUAL_WORD(MODRMSeg(i),RMAddr(i),&op1);

	result = (op1 << 1) | (BX_CPU_CLASS_PTR get_CF());
	WRITE_RMW_VIRTUAL_WORD(result);
#if (HOST_CPU_IS_I80386==0)
	SET_FLAGS_OC_16(op1,i->Word.shift,result,BX_INSTR_RCL16)
#endif //#if (HOST_CPU_IS_I80386==0)
#if (HOST_CPU_IS_I80386==1)
	Bit32u x86_lf_flags = BX_CPU_CLASS_PTR eflags.x86.eax;
	count = IMMEDIATEIb(i);
	__asm
	{
		mov eax,x86_lf_flags
		cmp al,0x81
		sahf
		mov cl,count
		RCL op1,cl
		lahf
		seto al
		mov x86_lf_flags,eax
	}

	BX_CPU_CLASS_PTR eflags.x86.eax = x86_lf_flags;
#endif //#if (HOST_CPU_IS_I80386==1)
}

	void
BX_CPU_C::RCL_EEd_1(BX_CPU_C *icpu,bxInstruction_c *i)
{
	Bit8u count;
	Bit32u op1,result;
	count = i->Word.shift;
	READ_RMW_VIRTUAL_DWORD(MODRMSeg(i),RMAddr(i),&op1);

	result = (op1 << 1) | (BX_CPU_CLASS_PTR get_CF());
	WRITE_RMW_VIRTUAL_DWORD(result);
#if (HOST_CPU_IS_I80386==0)
	SET_FLAGS_OC_32(op1,i->Word.shift,result,BX_INSTR_RCL32)
#endif //#if (HOST_CPU_IS_I80386==0)
#if (HOST_CPU_IS_I80386==1)
	Bit32u x86_lf_flags = BX_CPU_CLASS_PTR eflags.x86.eax;
	count = IMMEDIATEIb(i);
	__asm
	{
		mov eax,x86_lf_flags
		cmp al,0x81
		sahf
		mov cl,count
		RCL op1,cl
		lahf
		seto al
		mov x86_lf_flags,eax
	}

	BX_CPU_CLASS_PTR eflags.x86.eax = x86_lf_flags;
#endif //#if (HOST_CPU_IS_I80386==1)
}

	void
BX_CPU_C::RCR_EEb_1(BX_CPU_C *icpu,bxInstruction_c *i)
{
	Bit8u count;
	Bit8u op1,result;
	count = i->Word.shift;
	READ_RMW_VIRTUAL_BYTE(MODRMSeg(i),RMAddr(i),&op1);

	result = (op1 >> 1) | (BX_CPU_CLASS_PTR get_CF() << (8 - 1));
	WRITE_RMW_VIRTUAL_BYTE(result);
#if (HOST_CPU_IS_I80386==0)
	SET_FLAGS_OC_8(op1,i->Word.shift,result,BX_INSTR_RCR8)
#endif //#if (HOST_CPU_IS_I80386==0)
#if (HOST_CPU_IS_I80386==1)
	Bit32u x86_lf_flags = BX_CPU_CLASS_PTR eflags.x86.eax;
	count = IMMEDIATEIb(i);
	__asm
	{
		mov eax,x86_lf_flags
		cmp al,0x81
		sahf
		mov cl,count
		RCR op1,cl
		lahf
		seto al
		mov x86_lf_flags,eax
	}

	BX_CPU_CLASS_PTR eflags.x86.eax = x86_lf_flags;
#endif //#if (HOST_CPU_IS_I80386==1)
}

	void
BX_CPU_C::RCR_EEw_1(BX_CPU_C *icpu,bxInstruction_c *i)
{
	Bit8u count;
	Bit16u op1,result;
	count = i->Word.shift;
	READ_RMW_VIRTUAL_WORD(MODRMSeg(i),RMAddr(i),&op1);

	result = (op1 >> 1) | (BX_CPU_CLASS_PTR get_CF() << (16 - 1));
	WRITE_RMW_VIRTUAL_WORD(result);
#if (HOST_CPU_IS_I80386==0)
	SET_FLAGS_OC_16(op1,i->Word.shift,result,BX_INSTR_RCR16)
#endif //#if (HOST_CPU_IS_I80386==0)
#if (HOST_CPU_IS_I80386==1)
	Bit32u x86_lf_flags = BX_CPU_CLASS_PTR eflags.x86.eax;
	count = IMMEDIATEIb(i);
	__asm
	{
		mov eax,x86_lf_flags
		cmp al,0x81
		sahf
		mov cl,count
		RCR op1,cl
		lahf
		seto al
		mov x86_lf_flags,eax
	}

	BX_CPU_CLASS_PTR eflags.x86.eax = x86_lf_flags;
#endif //#if (HOST_CPU_IS_I80386==1)
}

	void
BX_CPU_C::RCR_EEd_1(BX_CPU_C *icpu,bxInstruction_c *i)
{
	Bit8u count;
	Bit32u op1,result;
	count = i->Word.shift;
	READ_RMW_VIRTUAL_DWORD(MODRMSeg(i),RMAddr(i),&op1);

	result = (op1 >> 1) | (BX_CPU_CLASS_PTR get_CF() << (32 - 1));
	WRITE_RMW_VIRTUAL_DWORD(result);
#if (HOST_CPU_IS_I80386==0)
	SET_FLAGS_OC_32(op1,i->Word.shift,result,BX_INSTR_RCR32)
#endif //#if (HOST_CPU_IS_I80386==0)
#if (HOST_CPU_IS_I80386==1)
	Bit32u x86_lf_flags = BX_CPU_CLASS_PTR eflags.x86.eax;
	count = IMMEDIATEIb(i);
	__asm
	{
		mov eax,x86_lf_flags
		cmp al,0x81
		sahf
		mov cl,count
		RCR op1,cl
		lahf
		seto al
		mov x86_lf_flags,eax
	}

	BX_CPU_CLASS_PTR eflags.x86.eax = x86_lf_flags;
#endif //#if (HOST_CPU_IS_I80386==1)
}

	void
BX_CPU_C::SHL_EEb_1(BX_CPU_C *icpu,bxInstruction_c *i)
{
	Bit8u count;
	Bit8u op1,result;
	count = i->Word.shift;
	READ_RMW_VIRTUAL_BYTE(MODRMSeg(i),RMAddr(i),&op1);

	result = (op1 << 1);
	WRITE_RMW_VIRTUAL_BYTE(result);
#if (HOST_CPU_IS_I80386==0)
	SET_FLAGS_OSZPC_8(op1,IMMEDIATEIb(i),result,BX_INSTR_SHL8)
#endif //#if (HOST_CPU_IS_I80386==0)
#if (HOST_CPU_IS_I80386==1)
	Bit32u x86_lf_flags = BX_CPU_CLASS_PTR eflags.x86.eax;
	count = IMMEDIATEIb(i);
	__asm
	{
		mov eax,x86_lf_flags
		cmp al,0x81
		sahf
		mov cl,count
		SHL op1,cl
		lahf
		seto al
		mov x86_lf_flags,eax
	}

	BX_CPU_CLASS_PTR eflags.x86.eax = x86_lf_flags;
#endif //#if (HOST_CPU_IS_I80386==1)
}

	void
BX_CPU_C::SHL_EEw_1(BX_CPU_C *icpu,bxInstruction_c *i)
{
	Bit8u count;
	Bit16u op1,result;
	count = i->Word.shift;
	READ_RMW_VIRTUAL_WORD(MODRMSeg(i),RMAddr(i),&op1);

	result = (op1 << 1);
	WRITE_RMW_VIRTUAL_WORD(result);
#if (HOST_CPU_IS_I80386==0)
	SET_FLAGS_OSZPC_16(op1,IMMEDIATEIb(i),result,BX_INSTR_SHL16)
#endif //#if (HOST_CPU_IS_I80386==0)
#if (HOST_CPU_IS_I80386==1)
	Bit32u x86_lf_flags = BX_CPU_CLASS_PTR eflags.x86.eax;
	count = IMMEDIATEIb(i);
	__asm
	{
		mov eax,x86_lf_flags
		cmp al,0x81
		sahf
		mov cl,count
		SHL op1,cl
		lahf
		seto al
		mov x86_lf_flags,eax
	}

	BX_CPU_CLASS_PTR eflags.x86.eax = x86_lf_flags;
#endif //#if (HOST_CPU_IS_I80386==1)
}

	void
BX_CPU_C::SHL_EEd_1(BX_CPU_C *icpu,bxInstruction_c *i)
{
	Bit8u count;
	Bit32u op1,result;
	count = i->Word.shift;
	READ_RMW_VIRTUAL_DWORD(MODRMSeg(i),RMAddr(i),&op1);

	result = (op1 << 1);
	WRITE_RMW_VIRTUAL_DWORD(result);
#if (HOST_CPU_IS_I80386==0)
	SET_FLAGS_OSZPC_32(op1,IMMEDIATEIb(i),result,BX_INSTR_SHL32)
#endif //#if (HOST_CPU_IS_I80386==0)
#if (HOST_CPU_IS_I80386==1)
	Bit32u x86_lf_flags = BX_CPU_CLASS_PTR eflags.x86.eax;
	count = IMMEDIATEIb(i);
	__asm
	{
		mov eax,x86_lf_flags
		cmp al,0x81
		sahf
		mov cl,count
		SHL op1,cl
		lahf
		seto al
		mov x86_lf_flags,eax
	}

	BX_CPU_CLASS_PTR eflags.x86.eax = x86_lf_flags;
#endif //#if (HOST_CPU_IS_I80386==1)
}

	void
BX_CPU_C::SHR_EEb_1(BX_CPU_C *icpu,bxInstruction_c *i)
{
	Bit8u count;
	Bit8u op1,result;
	count = i->Word.shift;
	READ_RMW_VIRTUAL_BYTE(MODRMSeg(i),RMAddr(i),&op1);

	result = (op1 >> 1);
	WRITE_RMW_VIRTUAL_BYTE(result);
#if (HOST_CPU_IS_I80386==0)
	SET_FLAGS_OSZPC_8(op1,IMMEDIATEIb(i),result,BX_INSTR_SHR8)
#endif //#if (HOST_CPU_IS_I80386==0)
#if (HOST_CPU_IS_I80386==1)
	Bit32u x86_lf_flags = BX_CPU_CLASS_PTR eflags.x86.eax;
	count = IMMEDIATEIb(i);
	__asm
	{
		mov eax,x86_lf_flags
		cmp al,0x81
		sahf
		mov cl,count
		SHR op1,cl
		lahf
		seto al
		mov x86_lf_flags,eax
	}

	BX_CPU_CLASS_PTR eflags.x86.eax = x86_lf_flags;
#endif //#if (HOST_CPU_IS_I80386==1)
}

	void
BX_CPU_C::SHR_EEw_1(BX_CPU_C *icpu,bxInstruction_c *i)
{
	Bit8u count;
	Bit16u op1,result;
	count = i->Word.shift;
	READ_RMW_VIRTUAL_WORD(MODRMSeg(i),RMAddr(i),&op1);

	result = (op1 >> 1);
	WRITE_RMW_VIRTUAL_WORD(result);
#if (HOST_CPU_IS_I80386==0)
	SET_FLAGS_OSZPC_16(op1,IMMEDIATEIb(i),result,BX_INSTR_SHR16)
#endif //#if (HOST_CPU_IS_I80386==0)
#if (HOST_CPU_IS_I80386==1)
	Bit32u x86_lf_flags = BX_CPU_CLASS_PTR eflags.x86.eax;
	count = IMMEDIATEIb(i);
	__asm
	{
		mov eax,x86_lf_flags
		cmp al,0x81
		sahf
		mov cl,count
		SHR op1,cl
		lahf
		seto al
		mov x86_lf_flags,eax
	}

	BX_CPU_CLASS_PTR eflags.x86.eax = x86_lf_flags;
#endif //#if (HOST_CPU_IS_I80386==1)
}

	void
BX_CPU_C::SHR_EEd_1(BX_CPU_C *icpu,bxInstruction_c *i)
{
	Bit8u count;
	Bit32u op1,result;
	count = i->Word.shift;
	READ_RMW_VIRTUAL_DWORD(MODRMSeg(i),RMAddr(i),&op1);

	result = (op1 >> 1);
	WRITE_RMW_VIRTUAL_DWORD(result);
#if (HOST_CPU_IS_I80386==0)
	SET_FLAGS_OSZPC_32(op1,IMMEDIATEIb(i),result,BX_INSTR_SHR32)
#endif //#if (HOST_CPU_IS_I80386==0)
#if (HOST_CPU_IS_I80386==1)
	Bit32u x86_lf_flags = BX_CPU_CLASS_PTR eflags.x86.eax;
	count = IMMEDIATEIb(i);
	__asm
	{
		mov eax,x86_lf_flags
		cmp al,0x81
		sahf
		mov cl,count
		SHR op1,cl
		lahf
		seto al
		mov x86_lf_flags,eax
	}

	BX_CPU_CLASS_PTR eflags.x86.eax = x86_lf_flags;
#endif //#if (HOST_CPU_IS_I80386==1)
}

	void
BX_CPU_C::SAR_EEb_1(BX_CPU_C *icpu,bxInstruction_c *i)
{
	Bit8u count;
	Bit8u op1,result;
	count = i->Word.shift;
	READ_RMW_VIRTUAL_BYTE(MODRMSeg(i),RMAddr(i),&op1);

	result = (op1 >> 1) |
		((0-(op1>>(8-1))) << (8 - 1));
	WRITE_RMW_VIRTUAL_BYTE(result);
#if (HOST_CPU_IS_I80386==0)
	SET_FLAGS_OSZPC_8(op1,IMMEDIATEIb(i),result,BX_INSTR_SAR8)
#endif //#if (HOST_CPU_IS_I80386==0)
#if (HOST_CPU_IS_I80386==1)
	Bit32u x86_lf_flags = BX_CPU_CLASS_PTR eflags.x86.eax;
	count = IMMEDIATEIb(i);
	__asm
	{
		mov eax,x86_lf_flags
		cmp al,0x81
		sahf
		mov cl,count
		SAR op1,cl
		lahf
		seto al
		mov x86_lf_flags,eax
	}

	BX_CPU_CLASS_PTR eflags.x86.eax = x86_lf_flags;
#endif //#if (HOST_CPU_IS_I80386==1)
}

	void
BX_CPU_C::SAR_EEw_1(BX_CPU_C *icpu,bxInstruction_c *i)
{
	Bit8u count;
	Bit16u op1,result;
	count = i->Word.shift;
	READ_RMW_VIRTUAL_WORD(MODRMSeg(i),RMAddr(i),&op1);

	result = (op1 >> 1) |
		((0-(op1>>(16-1))) << (16 - 1));
	WRITE_RMW_VIRTUAL_WORD(result);
#if (HOST_CPU_IS_I80386==0)
	SET_FLAGS_OSZPC_16(op1,IMMEDIATEIb(i),result,BX_INSTR_SAR16)
#endif //#if (HOST_CPU_IS_I80386==0)
#if (HOST_CPU_IS_I80386==1)
	Bit32u x86_lf_flags = BX_CPU_CLASS_PTR eflags.x86.eax;
	count = IMMEDIATEIb(i);
	__asm
	{
		mov eax,x86_lf_flags
		cmp al,0x81
		sahf
		mov cl,count
		SAR op1,cl
		lahf
		seto al
		mov x86_lf_flags,eax
	}

	BX_CPU_CLASS_PTR eflags.x86.eax = x86_lf_flags;
#endif //#if (HOST_CPU_IS_I80386==1)
}

	void
BX_CPU_C::SAR_EEd_1(BX_CPU_C *icpu,bxInstruction_c *i)
{
	Bit8u count;
	Bit32u op1,result;
	count = i->Word.shift;
	READ_RMW_VIRTUAL_DWORD(MODRMSeg(i),RMAddr(i),&op1);

	result = (op1 >> 1) |
		((0-(op1>>(32-1))) << (32 - 1));
	WRITE_RMW_VIRTUAL_DWORD(result);
#if (HOST_CPU_IS_I80386==0)
	SET_FLAGS_OSZPC_32(op1,IMMEDIATEIb(i),result,BX_INSTR_SAR32)
#endif //#if (HOST_CPU_IS_I80386==0)
#if (HOST_CPU_IS_I80386==1)
	Bit32u x86_lf_flags = BX_CPU_CLASS_PTR eflags.x86.eax;
	count = IMMEDIATEIb(i);
	__asm
	{
		mov eax,x86_lf_flags
		cmp al,0x81
		sahf
		mov cl,count
		SAR op1,cl
		lahf
		seto al
		mov x86_lf_flags,eax
	}

	BX_CPU_CLASS_PTR eflags.x86.eax = x86_lf_flags;
#endif //#if (HOST_CPU_IS_I80386==1)
}

	void
BX_CPU_C::ROL_EEb_n(BX_CPU_C *icpu,bxInstruction_c *i)
{
	Bit8u count;
	Bit8u op1,result;
	count = i->Word.shift;
	READ_RMW_VIRTUAL_BYTE(MODRMSeg(i),RMAddr(i),&op1);

	result = (op1 << count) | (op1 >> (8-count));
	WRITE_RMW_VIRTUAL_BYTE(result);
#if (HOST_CPU_IS_I80386==0)
	SET_FLAGS_XC_8(op1,i->Word.shift,result,BX_INSTR_ROL8)
#endif //#if (HOST_CPU_IS_I80386==0)
#if (HOST_CPU_IS_I80386==1)
	Bit32u x86_lf_flags = BX_CPU_CLASS_PTR eflags.x86.eax;
	count = IMMEDIATEIb(i);
	__asm
	{
		mov eax,x86_lf_flags
		cmp al,0x81
		sahf
		mov cl,count
		ROL op1,cl
		lahf
		seto al
		mov x86_lf_flags,eax
	}

	BX_CPU_CLASS_PTR eflags.x86.eax = x86_lf_flags;
#endif //#if (HOST_CPU_IS_I80386==1)
}

	void
BX_CPU_C::ROL_EEw_n(BX_CPU_C *icpu,bxInstruction_c *i)
{
	Bit8u count;
	Bit16u op1,result;
	count = i->Word.shift;
	READ_RMW_VIRTUAL_WORD(MODRMSeg(i),RMAddr(i),&op1);

	result = (op1 << count) | (op1 >> (16-count));
	WRITE_RMW_VIRTUAL_WORD(result);
#if (HOST_CPU_IS_I80386==0)
	SET_FLAGS_XC_16(op1,i->Word.shift,result,BX_INSTR_ROL16)
#endif //#if (HOST_CPU_IS_I80386==0)
#if (HOST_CPU_IS_I80386==1)
	Bit32u x86_lf_flags = BX_CPU_CLASS_PTR eflags.x86.eax;
	count = IMMEDIATEIb(i);
	__asm
	{
		mov eax,x86_lf_flags
		cmp al,0x81
		sahf
		mov cl,count
		ROL op1,cl
		lahf
		seto al
		mov x86_lf_flags,eax
	}

	BX_CPU_CLASS_PTR eflags.x86.eax = x86_lf_flags;
#endif //#if (HOST_CPU_IS_I80386==1)
}

	void
BX_CPU_C::ROL_EEd_n(BX_CPU_C *icpu,bxInstruction_c *i)
{
	Bit8u count;
	Bit32u op1,result;
	count = i->Word.shift;
	READ_RMW_VIRTUAL_DWORD(MODRMSeg(i),RMAddr(i),&op1);

	result = (op1 << count) | (op1 >> (32-count));
	WRITE_RMW_VIRTUAL_DWORD(result);
#if (HOST_CPU_IS_I80386==0)
	SET_FLAGS_XC_32(op1,i->Word.shift,result,BX_INSTR_ROL32)
#endif //#if (HOST_CPU_IS_I80386==0)
#if (HOST_CPU_IS_I80386==1)
	Bit32u x86_lf_flags = BX_CPU_CLASS_PTR eflags.x86.eax;
	count = IMMEDIATEIb(i);
	__asm
	{
		mov eax,x86_lf_flags
		cmp al,0x81
		sahf
		mov cl,count
		ROL op1,cl
		lahf
		seto al
		mov x86_lf_flags,eax
	}

	BX_CPU_CLASS_PTR eflags.x86.eax = x86_lf_flags;
#endif //#if (HOST_CPU_IS_I80386==1)
}

	void
BX_CPU_C::ROR_EEb_n(BX_CPU_C *icpu,bxInstruction_c *i)
{
	Bit8u count;
	Bit8u op1,result;
	count = i->Word.shift;
	READ_RMW_VIRTUAL_BYTE(MODRMSeg(i),RMAddr(i),&op1);

	result = (op1 >> count) | (op1 << (8-count));
	WRITE_RMW_VIRTUAL_BYTE(result);
#if (HOST_CPU_IS_I80386==0)
	SET_FLAGS_XC_8(op1,i->Word.shift,result,BX_INSTR_ROR8)
#endif //#if (HOST_CPU_IS_I80386==0)
#if (HOST_CPU_IS_I80386==1)
	Bit32u x86_lf_flags = BX_CPU_CLASS_PTR eflags.x86.eax;
	count = IMMEDIATEIb(i);
	__asm
	{
		mov eax,x86_lf_flags
		cmp al,0x81
		sahf
		mov cl,count
		ROR op1,cl
		lahf
		seto al
		mov x86_lf_flags,eax
	}

	BX_CPU_CLASS_PTR eflags.x86.eax = x86_lf_flags;
#endif //#if (HOST_CPU_IS_I80386==1)
}

	void
BX_CPU_C::ROR_EEw_n(BX_CPU_C *icpu,bxInstruction_c *i)
{
	Bit8u count;
	Bit16u op1,result;
	count = i->Word.shift;
	READ_RMW_VIRTUAL_WORD(MODRMSeg(i),RMAddr(i),&op1);

	result = (op1 >> count) | (op1 << (16-count));
	WRITE_RMW_VIRTUAL_WORD(result);
#if (HOST_CPU_IS_I80386==0)
	SET_FLAGS_XC_16(op1,i->Word.shift,result,BX_INSTR_ROR16)
#endif //#if (HOST_CPU_IS_I80386==0)
#if (HOST_CPU_IS_I80386==1)
	Bit32u x86_lf_flags = BX_CPU_CLASS_PTR eflags.x86.eax;
	count = IMMEDIATEIb(i);
	__asm
	{
		mov eax,x86_lf_flags
		cmp al,0x81
		sahf
		mov cl,count
		ROR op1,cl
		lahf
		seto al
		mov x86_lf_flags,eax
	}

	BX_CPU_CLASS_PTR eflags.x86.eax = x86_lf_flags;
#endif //#if (HOST_CPU_IS_I80386==1)
}

	void
BX_CPU_C::ROR_EEd_n(BX_CPU_C *icpu,bxInstruction_c *i)
{
	Bit8u count;
	Bit32u op1,result;
	count = i->Word.shift;
	READ_RMW_VIRTUAL_DWORD(MODRMSeg(i),RMAddr(i),&op1);

	result = (op1 >> count) | (op1 << (32-count));
	WRITE_RMW_VIRTUAL_DWORD(result);
#if (HOST_CPU_IS_I80386==0)
	SET_FLAGS_XC_32(op1,i->Word.shift,result,BX_INSTR_ROR32)
#endif //#if (HOST_CPU_IS_I80386==0)
#if (HOST_CPU_IS_I80386==1)
	Bit32u x86_lf_flags = BX_CPU_CLASS_PTR eflags.x86.eax;
	count = IMMEDIATEIb(i);
	__asm
	{
		mov eax,x86_lf_flags
		cmp al,0x81
		sahf
		mov cl,count
		ROR op1,cl
		lahf
		seto al
		mov x86_lf_flags,eax
	}

	BX_CPU_CLASS_PTR eflags.x86.eax = x86_lf_flags;
#endif //#if (HOST_CPU_IS_I80386==1)
}

	void
BX_CPU_C::RCL_EEb_n(BX_CPU_C *icpu,bxInstruction_c *i)
{
	Bit8u count;
	Bit8u op1,result;
	count = i->Word.shift;
	READ_RMW_VIRTUAL_BYTE(MODRMSeg(i),RMAddr(i),&op1);

	result = (op1 << count) | (op1 >> ((8+1) - count)) |
		(BX_CPU_CLASS_PTR get_CF() << (count - 1));
	WRITE_RMW_VIRTUAL_BYTE(result);
#if (HOST_CPU_IS_I80386==0)
	SET_FLAGS_XC_8(op1,i->Word.shift,result,BX_INSTR_RCL8)
#endif //#if (HOST_CPU_IS_I80386==0)
#if (HOST_CPU_IS_I80386==1)
	Bit32u x86_lf_flags = BX_CPU_CLASS_PTR eflags.x86.eax;
	count = IMMEDIATEIb(i);
	__asm
	{
		mov eax,x86_lf_flags
		cmp al,0x81
		sahf
		mov cl,count
		RCL op1,cl
		lahf
		seto al
		mov x86_lf_flags,eax
	}

	BX_CPU_CLASS_PTR eflags.x86.eax = x86_lf_flags;
#endif //#if (HOST_CPU_IS_I80386==1)
}

	void
BX_CPU_C::RCL_EEw_n(BX_CPU_C *icpu,bxInstruction_c *i)
{
	Bit8u count;
	Bit16u op1,result;
	count = i->Word.shift;
	READ_RMW_VIRTUAL_WORD(MODRMSeg(i),RMAddr(i),&op1);

	result = (op1 << count) | (op1 >> ((16+1) - count)) |
		(BX_CPU_CLASS_PTR get_CF() << (count - 1));
	WRITE_RMW_VIRTUAL_WORD(result);
#if (HOST_CPU_IS_I80386==0)
	SET_FLAGS_XC_16(op1,i->Word.shift,result,BX_INSTR_RCL16)
#endif //#if (HOST_CPU_IS_I80386==0)
#if (HOST_CPU_IS_I80386==1)
	Bit32u x86_lf_flags = BX_CPU_CLASS_PTR eflags.x86.eax;
	count = IMMEDIATEIb(i);
	__asm
	{
		mov eax,x86_lf_flags
		cmp al,0x81
		sahf
		mov cl,count
		RCL op1,cl
		lahf
		seto al
		mov x86_lf_flags,eax
	}

	BX_CPU_CLASS_PTR eflags.x86.eax = x86_lf_flags;
#endif //#if (HOST_CPU_IS_I80386==1)
}

	void
BX_CPU_C::RCL_EEd_n(BX_CPU_C *icpu,bxInstruction_c *i)
{
	Bit8u count;
	Bit32u op1,result;
	count = i->Word.shift;
	READ_RMW_VIRTUAL_DWORD(MODRMSeg(i),RMAddr(i),&op1);

	result = (op1 << count) | (op1 >> ((32+1) - count)) |
		(BX_CPU_CLASS_PTR get_CF() << (count - 1));
	WRITE_RMW_VIRTUAL_DWORD(result);
#if (HOST_CPU_IS_I80386==0)
	SET_FLAGS_XC_32(op1,i->Word.shift,result,BX_INSTR_RCL32)
#endif //#if (HOST_CPU_IS_I80386==0)
#if (HOST_CPU_IS_I80386==1)
	Bit32u x86_lf_flags = BX_CPU_CLASS_PTR eflags.x86.eax;
	count = IMMEDIATEIb(i);
	__asm
	{
		mov eax,x86_lf_flags
		cmp al,0x81
		sahf
		mov cl,count
		RCL op1,cl
		lahf
		seto al
		mov x86_lf_flags,eax
	}

	BX_CPU_CLASS_PTR eflags.x86.eax = x86_lf_flags;
#endif //#if (HOST_CPU_IS_I80386==1)
}

	void
BX_CPU_C::RCR_EEb_n(BX_CPU_C *icpu,bxInstruction_c *i)
{
	Bit8u count;
	Bit8u op1,result;
	count = i->Word.shift;
	READ_RMW_VIRTUAL_BYTE(MODRMSeg(i),RMAddr(i),&op1);

	result = (op1 >> count) | (op1 << ((8+1) - count)) |
		(BX_CPU_CLASS_PTR get_CF() << (8 - count));
	WRITE_RMW_VIRTUAL_BYTE(result);
#if (HOST_CPU_IS_I80386==0)
	SET_FLAGS_XC_8(op1,i->Word.shift,result,BX_INSTR_RCR8)
#endif //#if (HOST_CPU_IS_I80386==0)
#if (HOST_CPU_IS_I80386==1)
	Bit32u x86_lf_flags = BX_CPU_CLASS_PTR eflags.x86.eax;
	count = IMMEDIATEIb(i);
	__asm
	{
		mov eax,x86_lf_flags
		cmp al,0x81
		sahf
		mov cl,count
		RCR op1,cl
		lahf
		seto al
		mov x86_lf_flags,eax
	}

	BX_CPU_CLASS_PTR eflags.x86.eax = x86_lf_flags;
#endif //#if (HOST_CPU_IS_I80386==1)
}

	void
BX_CPU_C::RCR_EEw_n(BX_CPU_C *icpu,bxInstruction_c *i)
{
	Bit8u count;
	Bit16u op1,result;
	count = i->Word.shift;
	READ_RMW_VIRTUAL_WORD(MODRMSeg(i),RMAddr(i),&op1);

	result = (op1 >> count) | (op1 << ((16+1) - count)) |
		(BX_CPU_CLASS_PTR get_CF() << (16 - count));
	WRITE_RMW_VIRTUAL_WORD(result);
#if (HOST_CPU_IS_I80386==0)
	SET_FLAGS_XC_16(op1,i->Word.shift,result,BX_INSTR_RCR16)
#endif //#if (HOST_CPU_IS_I80386==0)
#if (HOST_CPU_IS_I80386==1)
	Bit32u x86_lf_flags = BX_CPU_CLASS_PTR eflags.x86.eax;
	count = IMMEDIATEIb(i);
	__asm
	{
		mov eax,x86_lf_flags
		cmp al,0x81
		sahf
		mov cl,count
		RCR op1,cl
		lahf
		seto al
		mov x86_lf_flags,eax
	}

	BX_CPU_CLASS_PTR eflags.x86.eax = x86_lf_flags;
#endif //#if (HOST_CPU_IS_I80386==1)
}

	void
BX_CPU_C::RCR_EEd_n(BX_CPU_C *icpu,bxInstruction_c *i)
{
	Bit8u count;
	Bit32u op1,result;
	count = i->Word.shift;
	READ_RMW_VIRTUAL_DWORD(MODRMSeg(i),RMAddr(i),&op1);

	result = (op1 >> count) | (op1 << ((32+1) - count)) |
		(BX_CPU_CLASS_PTR get_CF() << (32 - count));
	WRITE_RMW_VIRTUAL_DWORD(result);
#if (HOST_CPU_IS_I80386==0)
	SET_FLAGS_XC_32(op1,i->Word.shift,result,BX_INSTR_RCR32)
#endif //#if (HOST_CPU_IS_I80386==0)
#if (HOST_CPU_IS_I80386==1)
	Bit32u x86_lf_flags = BX_CPU_CLASS_PTR eflags.x86.eax;
	count = IMMEDIATEIb(i);
	__asm
	{
		mov eax,x86_lf_flags
		cmp al,0x81
		sahf
		mov cl,count
		RCR op1,cl
		lahf
		seto al
		mov x86_lf_flags,eax
	}

	BX_CPU_CLASS_PTR eflags.x86.eax = x86_lf_flags;
#endif //#if (HOST_CPU_IS_I80386==1)
}

	void
BX_CPU_C::SHL_EEb_n(BX_CPU_C *icpu,bxInstruction_c *i)
{
	Bit8u count;
	Bit8u op1,result;
	count = i->Word.shift;
	READ_RMW_VIRTUAL_BYTE(MODRMSeg(i),RMAddr(i),&op1);

	result = (op1 << count);
	WRITE_RMW_VIRTUAL_BYTE(result);
#if (HOST_CPU_IS_I80386==0)
	SET_FLAGS_XSZPC_8(op1,IMMEDIATEIb(i),result,BX_INSTR_SHL8)
#endif //#if (HOST_CPU_IS_I80386==0)
#if (HOST_CPU_IS_I80386==1)
	Bit32u x86_lf_flags = BX_CPU_CLASS_PTR eflags.x86.eax;
	count = IMMEDIATEIb(i);
	__asm
	{
		mov eax,x86_lf_flags
		cmp al,0x81
		sahf
		mov cl,count
		SHL op1,cl
		lahf
		seto al
		mov x86_lf_flags,eax
	}

	BX_CPU_CLASS_PTR eflags.x86.eax = x86_lf_flags;
#endif //#if (HOST_CPU_IS_I80386==1)
}

	void
BX_CPU_C::SHL_EEw_n(BX_CPU_C *icpu,bxInstruction_c *i)
{
	Bit8u count;
	Bit16u op1,result;
	count = i->Word.shift;
	READ_RMW_VIRTUAL_WORD(MODRMSeg(i),RMAddr(i),&op1);

	result = (op1 << count);
	WRITE_RMW_VIRTUAL_WORD(result);
#if (HOST_CPU_IS_I80386==0)
	SET_FLAGS_XSZPC_16(op1,IMMEDIATEIb(i),result,BX_INSTR_SHL16)
#endif //#if (HOST_CPU_IS_I80386==0)
#if (HOST_CPU_IS_I80386==1)
	Bit32u x86_lf_flags = BX_CPU_CLASS_PTR eflags.x86.eax;
	count = IMMEDIATEIb(i);
	__asm
	{
		mov eax,x86_lf_flags
		cmp al,0x81
		sahf
		mov cl,count
		SHL op1,cl
		lahf
		seto al
		mov x86_lf_flags,eax
	}

	BX_CPU_CLASS_PTR eflags.x86.eax = x86_lf_flags;
#endif //#if (HOST_CPU_IS_I80386==1)
}

	void
BX_CPU_C::SHL_EEd_n(BX_CPU_C *icpu,bxInstruction_c *i)
{
	Bit8u count;
	Bit32u op1,result;
	count = i->Word.shift;
	READ_RMW_VIRTUAL_DWORD(MODRMSeg(i),RMAddr(i),&op1);

	result = (op1 << count);
	WRITE_RMW_VIRTUAL_DWORD(result);
#if (HOST_CPU_IS_I80386==0)
	SET_FLAGS_XSZPC_32(op1,IMMEDIATEIb(i),result,BX_INSTR_SHL32)
#endif //#if (HOST_CPU_IS_I80386==0)
#if (HOST_CPU_IS_I80386==1)
	Bit32u x86_lf_flags = BX_CPU_CLASS_PTR eflags.x86.eax;
	count = IMMEDIATEIb(i);
	__asm
	{
		mov eax,x86_lf_flags
		cmp al,0x81
		sahf
		mov cl,count
		SHL op1,cl
		lahf
		seto al
		mov x86_lf_flags,eax
	}

	BX_CPU_CLASS_PTR eflags.x86.eax = x86_lf_flags;
#endif //#if (HOST_CPU_IS_I80386==1)
}

	void
BX_CPU_C::SHR_EEb_n(BX_CPU_C *icpu,bxInstruction_c *i)
{
	Bit8u count;
	Bit8u op1,result;
	count = i->Word.shift;
	READ_RMW_VIRTUAL_BYTE(MODRMSeg(i),RMAddr(i),&op1);

	result = (op1 >> count);
	WRITE_RMW_VIRTUAL_BYTE(result);
#if (HOST_CPU_IS_I80386==0)
	SET_FLAGS_XSZPC_8(op1,IMMEDIATEIb(i),result,BX_INSTR_SHR8)
#endif //#if (HOST_CPU_IS_I80386==0)
#if (HOST_CPU_IS_I80386==1)
	Bit32u x86_lf_flags = BX_CPU_CLASS_PTR eflags.x86.eax;
	count = IMMEDIATEIb(i);
	__asm
	{
		mov eax,x86_lf_flags
		cmp al,0x81
		sahf
		mov cl,count
		SHR op1,cl
		lahf
		seto al
		mov x86_lf_flags,eax
	}

	BX_CPU_CLASS_PTR eflags.x86.eax = x86_lf_flags;
#endif //#if (HOST_CPU_IS_I80386==1)
}

	void
BX_CPU_C::SHR_EEw_n(BX_CPU_C *icpu,bxInstruction_c *i)
{
	Bit8u count;
	Bit16u op1,result;
	count = i->Word.shift;
	READ_RMW_VIRTUAL_WORD(MODRMSeg(i),RMAddr(i),&op1);

	result = (op1 >> count);
	WRITE_RMW_VIRTUAL_WORD(result);
#if (HOST_CPU_IS_I80386==0)
	SET_FLAGS_XSZPC_16(op1,IMMEDIATEIb(i),result,BX_INSTR_SHR16)
#endif //#if (HOST_CPU_IS_I80386==0)
#if (HOST_CPU_IS_I80386==1)
	Bit32u x86_lf_flags = BX_CPU_CLASS_PTR eflags.x86.eax;
	count = IMMEDIATEIb(i);
	__asm
	{
		mov eax,x86_lf_flags
		cmp al,0x81
		sahf
		mov cl,count
		SHR op1,cl
		lahf
		seto al
		mov x86_lf_flags,eax
	}

	BX_CPU_CLASS_PTR eflags.x86.eax = x86_lf_flags;
#endif //#if (HOST_CPU_IS_I80386==1)
}

	void
BX_CPU_C::SHR_EEd_n(BX_CPU_C *icpu,bxInstruction_c *i)
{
	Bit8u count;
	Bit32u op1,result;
	count = i->Word.shift;
	READ_RMW_VIRTUAL_DWORD(MODRMSeg(i),RMAddr(i),&op1);

	result = (op1 >> count);
	WRITE_RMW_VIRTUAL_DWORD(result);
#if (HOST_CPU_IS_I80386==0)
	SET_FLAGS_XSZPC_32(op1,IMMEDIATEIb(i),result,BX_INSTR_SHR32)
#endif //#if (HOST_CPU_IS_I80386==0)
#if (HOST_CPU_IS_I80386==1)
	Bit32u x86_lf_flags = BX_CPU_CLASS_PTR eflags.x86.eax;
	count = IMMEDIATEIb(i);
	__asm
	{
		mov eax,x86_lf_flags
		cmp al,0x81
		sahf
		mov cl,count
		SHR op1,cl
		lahf
		seto al
		mov x86_lf_flags,eax
	}

	BX_CPU_CLASS_PTR eflags.x86.eax = x86_lf_flags;
#endif //#if (HOST_CPU_IS_I80386==1)
}

	void
BX_CPU_C::SAR_EEb_n(BX_CPU_C *icpu,bxInstruction_c *i)
{
	Bit8u count;
	Bit8u op1,result;
	count = i->Word.shift;
	READ_RMW_VIRTUAL_BYTE(MODRMSeg(i),RMAddr(i),&op1);

	result = (op1 >> count) |
		((0-(op1>>(8-1))) << (8 - count));
	WRITE_RMW_VIRTUAL_BYTE(result);
#if (HOST_CPU_IS_I80386==0)
	SET_FLAGS_XSZPC_8(op1,IMMEDIATEIb(i),result,BX_INSTR_SAR8)
#endif //#if (HOST_CPU_IS_I80386==0)
#if (HOST_CPU_IS_I80386==1)
	Bit32u x86_lf_flags = BX_CPU_CLASS_PTR eflags.x86.eax;
	count = IMMEDIATEIb(i);
	__asm
	{
		mov eax,x86_lf_flags
		cmp al,0x81
		sahf
		mov cl,count
		SAR op1,cl
		lahf
		seto al
		mov x86_lf_flags,eax
	}

	BX_CPU_CLASS_PTR eflags.x86.eax = x86_lf_flags;
#endif //#if (HOST_CPU_IS_I80386==1)
}

	void
BX_CPU_C::SAR_EEw_n(BX_CPU_C *icpu,bxInstruction_c *i)
{
	Bit8u count;
	Bit16u op1,result;
	count = i->Word.shift;
	READ_RMW_VIRTUAL_WORD(MODRMSeg(i),RMAddr(i),&op1);

	result = (op1 >> count) |
		((0-(op1>>(16-1))) << (16 - count));
	WRITE_RMW_VIRTUAL_WORD(result);
#if (HOST_CPU_IS_I80386==0)
	SET_FLAGS_XSZPC_16(op1,IMMEDIATEIb(i),result,BX_INSTR_SAR16)
#endif //#if (HOST_CPU_IS_I80386==0)
#if (HOST_CPU_IS_I80386==1)
	Bit32u x86_lf_flags = BX_CPU_CLASS_PTR eflags.x86.eax;
	count = IMMEDIATEIb(i);
	__asm
	{
		mov eax,x86_lf_flags
		cmp al,0x81
		sahf
		mov cl,count
		SAR op1,cl
		lahf
		seto al
		mov x86_lf_flags,eax
	}

	BX_CPU_CLASS_PTR eflags.x86.eax = x86_lf_flags;
#endif //#if (HOST_CPU_IS_I80386==1)
}

	void
BX_CPU_C::SAR_EEd_n(BX_CPU_C *icpu,bxInstruction_c *i)
{
	Bit8u count;
	Bit32u op1,result;
	count = i->Word.shift;
	READ_RMW_VIRTUAL_DWORD(MODRMSeg(i),RMAddr(i),&op1);

	result = (op1 >> count) |
		((0-(op1>>(32-1))) << (32 - count));
	WRITE_RMW_VIRTUAL_DWORD(result);
#if (HOST_CPU_IS_I80386==0)
	SET_FLAGS_XSZPC_32(op1,IMMEDIATEIb(i),result,BX_INSTR_SAR32)
#endif //#if (HOST_CPU_IS_I80386==0)
#if (HOST_CPU_IS_I80386==1)
	Bit32u x86_lf_flags = BX_CPU_CLASS_PTR eflags.x86.eax;
	count = IMMEDIATEIb(i);
	__asm
	{
		mov eax,x86_lf_flags
		cmp al,0x81
		sahf
		mov cl,count
		SAR op1,cl
		lahf
		seto al
		mov x86_lf_flags,eax
	}

	BX_CPU_CLASS_PTR eflags.x86.eax = x86_lf_flags;
#endif //#if (HOST_CPU_IS_I80386==1)
}

	void
BX_CPU_C::SHLD_EEwGw_1(BX_CPU_C *icpu,bxInstruction_c *i)
{
	Bit8u count;
	Bit16u op1,op2,result;
	count = i->Word.shift;
	READ_RMW_VIRTUAL_WORD(MODRMSeg(i),RMAddr(i),&op1);

	op2 = READ_VIRTUAL_16BIT_REG(MODRMnnn(i));

	result = (op1 << 1) | (op2 >> (16 - 1));
	WRITE_RMW_VIRTUAL_WORD(result);
#if (HOST_CPU_IS_I80386==0)
	SET3_FLAGS_OSZPC_16(op1,op2,IMMEDIATEIb(i),result,BX_INSTR_SHLD16)
#endif //#if (HOST_CPU_IS_I80386==0)
#if (HOST_CPU_IS_I80386==1)
	Bit32u x86_lf_flags = BX_CPU_CLASS_PTR eflags.x86.eax;
	count = IMMEDIATEIb(i);
	__asm
	{
		mov eax,x86_lf_flags
		cmp al,0x81
		sahf
		mov cl,count
		mov dx,op2
		SHLD op1,dx,cl
		lahf
		seto al
		mov x86_lf_flags,eax
	}

	BX_CPU_CLASS_PTR eflags.x86.eax = x86_lf_flags;
#endif //#if (HOST_CPU_IS_I80386==1)
}

	void
BX_CPU_C::SHLD_EEdGd_1(BX_CPU_C *icpu,bxInstruction_c *i)
{
	Bit8u count;
	Bit32u op1,op2,result;
	count = i->Word.shift;
	READ_RMW_VIRTUAL_DWORD(MODRMSeg(i),RMAddr(i),&op1);

	op2 = READ_VIRTUAL_32BIT_REG(MODRMnnn(i));

	result = (op1 << 1) | (op2 >> (32 - 1));
	WRITE_RMW_VIRTUAL_DWORD(result);
#if (HOST_CPU_IS_I80386==0)
	SET3_FLAGS_OSZPC_32(op1,op2,IMMEDIATEIb(i),result,BX_INSTR_SHLD32)
#endif //#if (HOST_CPU_IS_I80386==0)
#if (HOST_CPU_IS_I80386==1)
	Bit32u x86_lf_flags = BX_CPU_CLASS_PTR eflags.x86.eax;
	count = IMMEDIATEIb(i);
	__asm
	{
		mov eax,x86_lf_flags
		cmp al,0x81
		sahf
		mov cl,count
		mov edx,op2
		SHLD op1,edx,cl
		lahf
		seto al
		mov x86_lf_flags,eax
	}

	BX_CPU_CLASS_PTR eflags.x86.eax = x86_lf_flags;
#endif //#if (HOST_CPU_IS_I80386==1)
}

	void
BX_CPU_C::SHRD_EEwGw_1(BX_CPU_C *icpu,bxInstruction_c *i)
{
	Bit8u count;
	Bit16u op1,op2,result;
	count = i->Word.shift;
	READ_RMW_VIRTUAL_WORD(MODRMSeg(i),RMAddr(i),&op1);

	op2 = READ_VIRTUAL_16BIT_REG(MODRMnnn(i));

	result = (op1 >> 1) | (op2 << (16 - 1));
	WRITE_RMW_VIRTUAL_WORD(result);
#if (HOST_CPU_IS_I80386==0)
	SET3_FLAGS_OSZPC_16(op1,op2,IMMEDIATEIb(i),result,BX_INSTR_SHRD16)
#endif //#if (HOST_CPU_IS_I80386==0)
#if (HOST_CPU_IS_I80386==1)
	Bit32u x86_lf_flags = BX_CPU_CLASS_PTR eflags.x86.eax;
	count = IMMEDIATEIb(i);
	__asm
	{
		mov eax,x86_lf_flags
		cmp al,0x81
		sahf
		mov cl,count
		mov dx,op2
		SHRD op1,dx,cl
		lahf
		seto al
		mov x86_lf_flags,eax
	}

	BX_CPU_CLASS_PTR eflags.x86.eax = x86_lf_flags;
#endif //#if (HOST_CPU_IS_I80386==1)
}

	void
BX_CPU_C::SHRD_EEdGd_1(BX_CPU_C *icpu,bxInstruction_c *i)
{
	Bit8u count;
	Bit32u op1,op2,result;
	count = i->Word.shift;
	READ_RMW_VIRTUAL_DWORD(MODRMSeg(i),RMAddr(i),&op1);

	op2 = READ_VIRTUAL_32BIT_REG(MODRMnnn(i));

	result = (op1 >> 1) | (op2 << (32 - 1));
	WRITE_RMW_VIRTUAL_DWORD(result);
#if (HOST_CPU_IS_I80386==0)
	SET3_FLAGS_OSZPC_32(op1,op2,IMMEDIATEIb(i),result,BX_INSTR_SHRD32)
#endif //#if (HOST_CPU_IS_I80386==0)
#if (HOST_CPU_IS_I80386==1)
	Bit32u x86_lf_flags = BX_CPU_CLASS_PTR eflags.x86.eax;
	count = IMMEDIATEIb(i);
	__asm
	{
		mov eax,x86_lf_flags
		cmp al,0x81
		sahf
		mov cl,count
		mov edx,op2
		SHRD op1,edx,cl
		lahf
		seto al
		mov x86_lf_flags,eax
	}

	BX_CPU_CLASS_PTR eflags.x86.eax = x86_lf_flags;
#endif //#if (HOST_CPU_IS_I80386==1)
}

	void
BX_CPU_C::SHLD_EEwGw_n(BX_CPU_C *icpu,bxInstruction_c *i)
{
	Bit8u count;
	Bit16u op1,op2,result;
	count = i->Word.shift;
	READ_RMW_VIRTUAL_WORD(MODRMSeg(i),RMAddr(i),&op1);

	op2 = READ_VIRTUAL_16BIT_REG(MODRMnnn(i));

	result = (op1 << count) | (op2 >> (16 - count));
	WRITE_RMW_VIRTUAL_WORD(result);
#if (HOST_CPU_IS_I80386==0)
	SET3_FLAGS_XSZPC_16(op1,op2,IMMEDIATEIb(i),result,BX_INSTR_SHLD16)
#endif //#if (HOST_CPU_IS_I80386==0)
#if (HOST_CPU_IS_I80386==1)
	Bit32u x86_lf_flags = BX_CPU_CLASS_PTR eflags.x86.eax;
	count = IMMEDIATEIb(i);
	__asm
	{
		mov eax,x86_lf_flags
		cmp al,0x81
		sahf
		mov cl,count
		mov dx,op2
		SHLD op1,dx,cl
		lahf
		seto al
		mov x86_lf_flags,eax
	}

	BX_CPU_CLASS_PTR eflags.x86.eax = x86_lf_flags;
#endif //#if (HOST_CPU_IS_I80386==1)
}

	void
BX_CPU_C::SHLD_EEdGd_n(BX_CPU_C *icpu,bxInstruction_c *i)
{
	Bit8u count;
	Bit32u op1,op2,result;
	count = i->Word.shift;
	READ_RMW_VIRTUAL_DWORD(MODRMSeg(i),RMAddr(i),&op1);

	op2 = READ_VIRTUAL_32BIT_REG(MODRMnnn(i));

	result = (op1 << count) | (op2 >> (32 - count));
	WRITE_RMW_VIRTUAL_DWORD(result);
#if (HOST_CPU_IS_I80386==0)
	SET3_FLAGS_XSZPC_32(op1,op2,IMMEDIATEIb(i),result,BX_INSTR_SHLD32)
#endif //#if (HOST_CPU_IS_I80386==0)
#if (HOST_CPU_IS_I80386==1)
	Bit32u x86_lf_flags = BX_CPU_CLASS_PTR eflags.x86.eax;
	count = IMMEDIATEIb(i);
	__asm
	{
		mov eax,x86_lf_flags
		cmp al,0x81
		sahf
		mov cl,count
		mov edx,op2
		SHLD op1,edx,cl
		lahf
		seto al
		mov x86_lf_flags,eax
	}

	BX_CPU_CLASS_PTR eflags.x86.eax = x86_lf_flags;
#endif //#if (HOST_CPU_IS_I80386==1)
}

	void
BX_CPU_C::SHRD_EEwGw_n(BX_CPU_C *icpu,bxInstruction_c *i)
{
	Bit8u count;
	Bit16u op1,op2,result;
	count = i->Word.shift;
	READ_RMW_VIRTUAL_WORD(MODRMSeg(i),RMAddr(i),&op1);

	op2 = READ_VIRTUAL_16BIT_REG(MODRMnnn(i));

	result = (op1 >> count) | (op2 << (16 - count));
	WRITE_RMW_VIRTUAL_WORD(result);
#if (HOST_CPU_IS_I80386==0)
	SET3_FLAGS_XSZPC_16(op1,op2,IMMEDIATEIb(i),result,BX_INSTR_SHRD16)
#endif //#if (HOST_CPU_IS_I80386==0)
#if (HOST_CPU_IS_I80386==1)
	Bit32u x86_lf_flags = BX_CPU_CLASS_PTR eflags.x86.eax;
	count = IMMEDIATEIb(i);
	__asm
	{
		mov eax,x86_lf_flags
		cmp al,0x81
		sahf
		mov cl,count
		mov dx,op2
		SHRD op1,dx,cl
		lahf
		seto al
		mov x86_lf_flags,eax
	}

	BX_CPU_CLASS_PTR eflags.x86.eax = x86_lf_flags;
#endif //#if (HOST_CPU_IS_I80386==1)
}

	void
BX_CPU_C::SHRD_EEdGd_n(BX_CPU_C *icpu,bxInstruction_c *i)
{
	Bit8u count;
	Bit32u op1,op2,result;
	count = i->Word.shift;
	READ_RMW_VIRTUAL_DWORD(MODRMSeg(i),RMAddr(i),&op1);

	op2 = READ_VIRTUAL_32BIT_REG(MODRMnnn(i));

	result = (op1 >> count) | (op2 << (32 - count));
	WRITE_RMW_VIRTUAL_DWORD(result);
#if (HOST_CPU_IS_I80386==0)
	SET3_FLAGS_XSZPC_32(op1,op2,IMMEDIATEIb(i),result,BX_INSTR_SHRD32)
#endif //#if (HOST_CPU_IS_I80386==0)
#if (HOST_CPU_IS_I80386==1)
	Bit32u x86_lf_flags = BX_CPU_CLASS_PTR eflags.x86.eax;
	count = IMMEDIATEIb(i);
	__asm
	{
		mov eax,x86_lf_flags
		cmp al,0x81
		sahf
		mov cl,count
		mov edx,op2
		SHRD op1,edx,cl
		lahf
		seto al
		mov x86_lf_flags,eax
	}

	BX_CPU_CLASS_PTR eflags.x86.eax = x86_lf_flags;
#endif //#if (HOST_CPU_IS_I80386==1)
}

const BxOpcodeShiftFun_t BxOpcodeShiftFunG_RO__Eb[4] =
{
	/*  0 */  {&BX_CPU_C::ROL_EGb_0,	&BX_CPU_C::ROL_EGb_0,	&BX_CPU_C::ROL_EEb_0,	&BX_CPU_C::ROL_EEb_0 },
	/*  1 */ {&BX_CPU_C::ROL_EGb_1,	&BX_CPU_C::ROR_EGb_1, &BX_CPU_C::ROL_EEb_1,	&BX_CPU_C::ROR_EEb_1 },
	/*  2 */ {&BX_CPU_C::ROL_EGb_n,	&BX_CPU_C::ROR_EGb_n, &BX_CPU_C::ROL_EEb_n,	&BX_CPU_C::ROR_EEb_n },
	/*  3 */ {&BX_CPU_C::ROL_EGb_n,	&BX_CPU_C::ROR_EGb_n, &BX_CPU_C::ROL_EEb_n,	&BX_CPU_C::ROR_EEb_n },
};

const BxOpcodeShiftTable_t BxOpcodeShiftTableG_RO__Eb[32] =
{
	/*  0 */  {  0, &BxOpcodeShiftFunG_RO__Eb[ 0] },
	/*  1 */  {  1, &BxOpcodeShiftFunG_RO__Eb[ 1] },
	/*  2 */  {  2, &BxOpcodeShiftFunG_RO__Eb[ 2] },
	/*  3 */  {  3, &BxOpcodeShiftFunG_RO__Eb[ 3] },
	/*  4 */  {  4, &BxOpcodeShiftFunG_RO__Eb[ 3] },
	/*  5 */  {  5, &BxOpcodeShiftFunG_RO__Eb[ 3] },
	/*  6 */  {  6, &BxOpcodeShiftFunG_RO__Eb[ 3] },
	/*  7 */  {  7, &BxOpcodeShiftFunG_RO__Eb[ 3] },
	/*  8 */  {  0, &BxOpcodeShiftFunG_RO__Eb[ 3] },
	/*  9 */  {  1, &BxOpcodeShiftFunG_RO__Eb[ 3] },
	/*  a */  {  2, &BxOpcodeShiftFunG_RO__Eb[ 3] },
	/*  b */  {  3, &BxOpcodeShiftFunG_RO__Eb[ 3] },
	/*  c */  {  4, &BxOpcodeShiftFunG_RO__Eb[ 3] },
	/*  d */  {  5, &BxOpcodeShiftFunG_RO__Eb[ 3] },
	/*  e */  {  6, &BxOpcodeShiftFunG_RO__Eb[ 3] },
	/*  f */  {  7, &BxOpcodeShiftFunG_RO__Eb[ 3] },
	/* 10 */  {  0, &BxOpcodeShiftFunG_RO__Eb[ 3] },
	/* 11 */  {  1, &BxOpcodeShiftFunG_RO__Eb[ 3] },
	/* 12 */  {  2, &BxOpcodeShiftFunG_RO__Eb[ 3] },
	/* 13 */  {  3, &BxOpcodeShiftFunG_RO__Eb[ 3] },
	/* 14 */  {  4, &BxOpcodeShiftFunG_RO__Eb[ 3] },
	/* 15 */  {  5, &BxOpcodeShiftFunG_RO__Eb[ 3] },
	/* 16 */  {  6, &BxOpcodeShiftFunG_RO__Eb[ 3] },
	/* 17 */  {  7, &BxOpcodeShiftFunG_RO__Eb[ 3] },
	/* 18 */  {  0, &BxOpcodeShiftFunG_RO__Eb[ 3] },
	/* 19 */  {  1, &BxOpcodeShiftFunG_RO__Eb[ 3] },
	/* 1a */  {  2, &BxOpcodeShiftFunG_RO__Eb[ 3] },
	/* 1b */  {  3, &BxOpcodeShiftFunG_RO__Eb[ 3] },
	/* 1c */  {  4, &BxOpcodeShiftFunG_RO__Eb[ 3] },
	/* 1d */  {  5, &BxOpcodeShiftFunG_RO__Eb[ 3] },
	/* 1e */  {  6, &BxOpcodeShiftFunG_RO__Eb[ 3] },
	/* 1f */  {  7, &BxOpcodeShiftFunG_RO__Eb[ 3] } 
};

const BxOpcodeShiftFun_t BxOpcodeShiftFunG_RO__Ew[4] =
{
	/*  0 */  {&BX_CPU_C::ROL_EGw_0,	&BX_CPU_C::ROL_EGw_0,	&BX_CPU_C::ROL_EEw_0,	&BX_CPU_C::ROL_EEw_0 },
	/*  1 */ {&BX_CPU_C::ROL_EGw_1,	&BX_CPU_C::ROR_EGw_1, &BX_CPU_C::ROL_EEw_1,	&BX_CPU_C::ROR_EEw_1 },
	/*  2 */ {&BX_CPU_C::ROL_EGw_n,	&BX_CPU_C::ROR_EGw_n, &BX_CPU_C::ROL_EEw_n,	&BX_CPU_C::ROR_EEw_n },
	/*  3 */ {&BX_CPU_C::ROL_EGw_n,	&BX_CPU_C::ROR_EGw_n, &BX_CPU_C::ROL_EEw_n,	&BX_CPU_C::ROR_EEw_n },
};

const BxOpcodeShiftTable_t BxOpcodeShiftTableG_RO__Ew[32] =
{
	/*  0 */  {  0, &BxOpcodeShiftFunG_RO__Ew[ 0] },
	/*  1 */  {  1, &BxOpcodeShiftFunG_RO__Ew[ 1] },
	/*  2 */  {  2, &BxOpcodeShiftFunG_RO__Ew[ 2] },
	/*  3 */  {  3, &BxOpcodeShiftFunG_RO__Ew[ 3] },
	/*  4 */  {  4, &BxOpcodeShiftFunG_RO__Ew[ 3] },
	/*  5 */  {  5, &BxOpcodeShiftFunG_RO__Ew[ 3] },
	/*  6 */  {  6, &BxOpcodeShiftFunG_RO__Ew[ 3] },
	/*  7 */  {  7, &BxOpcodeShiftFunG_RO__Ew[ 3] },
	/*  8 */  {  8, &BxOpcodeShiftFunG_RO__Ew[ 3] },
	/*  9 */  {  9, &BxOpcodeShiftFunG_RO__Ew[ 3] },
	/*  a */  { 10, &BxOpcodeShiftFunG_RO__Ew[ 3] },
	/*  b */  { 11, &BxOpcodeShiftFunG_RO__Ew[ 3] },
	/*  c */  { 12, &BxOpcodeShiftFunG_RO__Ew[ 3] },
	/*  d */  { 13, &BxOpcodeShiftFunG_RO__Ew[ 3] },
	/*  e */  { 14, &BxOpcodeShiftFunG_RO__Ew[ 3] },
	/*  f */  { 15, &BxOpcodeShiftFunG_RO__Ew[ 3] },
	/* 10 */  {  0, &BxOpcodeShiftFunG_RO__Ew[ 3] },
	/* 11 */  {  1, &BxOpcodeShiftFunG_RO__Ew[ 3] },
	/* 12 */  {  2, &BxOpcodeShiftFunG_RO__Ew[ 3] },
	/* 13 */  {  3, &BxOpcodeShiftFunG_RO__Ew[ 3] },
	/* 14 */  {  4, &BxOpcodeShiftFunG_RO__Ew[ 3] },
	/* 15 */  {  5, &BxOpcodeShiftFunG_RO__Ew[ 3] },
	/* 16 */  {  6, &BxOpcodeShiftFunG_RO__Ew[ 3] },
	/* 17 */  {  7, &BxOpcodeShiftFunG_RO__Ew[ 3] },
	/* 18 */  {  8, &BxOpcodeShiftFunG_RO__Ew[ 3] },
	/* 19 */  {  9, &BxOpcodeShiftFunG_RO__Ew[ 3] },
	/* 1a */  { 10, &BxOpcodeShiftFunG_RO__Ew[ 3] },
	/* 1b */  { 11, &BxOpcodeShiftFunG_RO__Ew[ 3] },
	/* 1c */  { 12, &BxOpcodeShiftFunG_RO__Ew[ 3] },
	/* 1d */  { 13, &BxOpcodeShiftFunG_RO__Ew[ 3] },
	/* 1e */  { 14, &BxOpcodeShiftFunG_RO__Ew[ 3] },
	/* 1f */  { 15, &BxOpcodeShiftFunG_RO__Ew[ 3] } 
};

const BxOpcodeShiftFun_t BxOpcodeShiftFunG_RO__Ed[4] =
{
	/*  0 */  {&BX_CPU_C::ROL_EGd_0,	&BX_CPU_C::ROL_EGd_0,	&BX_CPU_C::ROL_EEd_0,	&BX_CPU_C::ROL_EEd_0 },
	/*  1 */ {&BX_CPU_C::ROL_EGd_1,	&BX_CPU_C::ROR_EGd_1, &BX_CPU_C::ROL_EEd_1,	&BX_CPU_C::ROR_EEd_1 },
	/*  2 */ {&BX_CPU_C::ROL_EGd_n,	&BX_CPU_C::ROR_EGd_n, &BX_CPU_C::ROL_EEd_n,	&BX_CPU_C::ROR_EEd_n },
	/*  3 */ {&BX_CPU_C::ROL_EGd_n,	&BX_CPU_C::ROR_EGd_n, &BX_CPU_C::ROL_EEd_n,	&BX_CPU_C::ROR_EEd_n },
};

const BxOpcodeShiftTable_t BxOpcodeShiftTableG_RO__Ed[32] =
{
	/*  0 */  {  0, &BxOpcodeShiftFunG_RO__Ed[ 0] },
	/*  1 */  {  1, &BxOpcodeShiftFunG_RO__Ed[ 1] },
	/*  2 */  {  2, &BxOpcodeShiftFunG_RO__Ed[ 2] },
	/*  3 */  {  3, &BxOpcodeShiftFunG_RO__Ed[ 3] },
	/*  4 */  {  4, &BxOpcodeShiftFunG_RO__Ed[ 3] },
	/*  5 */  {  5, &BxOpcodeShiftFunG_RO__Ed[ 3] },
	/*  6 */  {  6, &BxOpcodeShiftFunG_RO__Ed[ 3] },
	/*  7 */  {  7, &BxOpcodeShiftFunG_RO__Ed[ 3] },
	/*  8 */  {  8, &BxOpcodeShiftFunG_RO__Ed[ 3] },
	/*  9 */  {  9, &BxOpcodeShiftFunG_RO__Ed[ 3] },
	/*  a */  { 10, &BxOpcodeShiftFunG_RO__Ed[ 3] },
	/*  b */  { 11, &BxOpcodeShiftFunG_RO__Ed[ 3] },
	/*  c */  { 12, &BxOpcodeShiftFunG_RO__Ed[ 3] },
	/*  d */  { 13, &BxOpcodeShiftFunG_RO__Ed[ 3] },
	/*  e */  { 14, &BxOpcodeShiftFunG_RO__Ed[ 3] },
	/*  f */  { 15, &BxOpcodeShiftFunG_RO__Ed[ 3] },
	/* 10 */  { 16, &BxOpcodeShiftFunG_RO__Ed[ 3] },
	/* 11 */  { 17, &BxOpcodeShiftFunG_RO__Ed[ 3] },
	/* 12 */  { 18, &BxOpcodeShiftFunG_RO__Ed[ 3] },
	/* 13 */  { 19, &BxOpcodeShiftFunG_RO__Ed[ 3] },
	/* 14 */  { 20, &BxOpcodeShiftFunG_RO__Ed[ 3] },
	/* 15 */  { 21, &BxOpcodeShiftFunG_RO__Ed[ 3] },
	/* 16 */  { 22, &BxOpcodeShiftFunG_RO__Ed[ 3] },
	/* 17 */  { 23, &BxOpcodeShiftFunG_RO__Ed[ 3] },
	/* 18 */  { 24, &BxOpcodeShiftFunG_RO__Ed[ 3] },
	/* 19 */  { 25, &BxOpcodeShiftFunG_RO__Ed[ 3] },
	/* 1a */  { 26, &BxOpcodeShiftFunG_RO__Ed[ 3] },
	/* 1b */  { 27, &BxOpcodeShiftFunG_RO__Ed[ 3] },
	/* 1c */  { 28, &BxOpcodeShiftFunG_RO__Ed[ 3] },
	/* 1d */  { 29, &BxOpcodeShiftFunG_RO__Ed[ 3] },
	/* 1e */  { 30, &BxOpcodeShiftFunG_RO__Ed[ 3] },
	/* 1f */  { 31, &BxOpcodeShiftFunG_RO__Ed[ 3] } 
};

const BxOpcodeShiftFun_t BxOpcodeShiftFunG_RC__Eb[4] =
{
	/*  0 */  {&BX_CPU_C::ROL_EGb_0,	&BX_CPU_C::ROL_EGb_0,	&BX_CPU_C::ROL_EEb_0,	&BX_CPU_C::ROL_EEb_0 },
	/*  1 */ {&BX_CPU_C::RCL_EGb_1,	&BX_CPU_C::RCR_EGb_1, &BX_CPU_C::RCL_EEb_1,	&BX_CPU_C::RCR_EEb_1 },
	/*  2 */ {&BX_CPU_C::RCL_EGb_n,	&BX_CPU_C::RCR_EGb_n, &BX_CPU_C::RCL_EEb_n,	&BX_CPU_C::RCR_EEb_n },
	/*  3 */ {&BX_CPU_C::RCL_EGb_n,	&BX_CPU_C::RCR_EGb_n, &BX_CPU_C::RCL_EEb_n,	&BX_CPU_C::RCR_EEb_n },
};

const BxOpcodeShiftTable_t BxOpcodeShiftTableG_RC__Eb[32] =
{
	/*  0 */  {  0, &BxOpcodeShiftFunG_RC__Eb[ 0] },
	/*  1 */  {  1, &BxOpcodeShiftFunG_RC__Eb[ 1] },
	/*  2 */  {  2, &BxOpcodeShiftFunG_RC__Eb[ 2] },
	/*  3 */  {  3, &BxOpcodeShiftFunG_RC__Eb[ 3] },
	/*  4 */  {  4, &BxOpcodeShiftFunG_RC__Eb[ 3] },
	/*  5 */  {  5, &BxOpcodeShiftFunG_RC__Eb[ 3] },
	/*  6 */  {  6, &BxOpcodeShiftFunG_RC__Eb[ 3] },
	/*  7 */  {  7, &BxOpcodeShiftFunG_RC__Eb[ 3] },
	/*  8 */  {  8, &BxOpcodeShiftFunG_RC__Eb[ 3] },
	/*  9 */  {  0, &BxOpcodeShiftFunG_RC__Eb[ 3] },
	/*  a */  {  1, &BxOpcodeShiftFunG_RC__Eb[ 3] },
	/*  b */  {  2, &BxOpcodeShiftFunG_RC__Eb[ 3] },
	/*  c */  {  3, &BxOpcodeShiftFunG_RC__Eb[ 3] },
	/*  d */  {  4, &BxOpcodeShiftFunG_RC__Eb[ 3] },
	/*  e */  {  5, &BxOpcodeShiftFunG_RC__Eb[ 3] },
	/*  f */  {  6, &BxOpcodeShiftFunG_RC__Eb[ 3] },
	/* 10 */  {  7, &BxOpcodeShiftFunG_RC__Eb[ 3] },
	/* 11 */  {  8, &BxOpcodeShiftFunG_RC__Eb[ 3] },
	/* 12 */  {  0, &BxOpcodeShiftFunG_RC__Eb[ 3] },
	/* 13 */  {  1, &BxOpcodeShiftFunG_RC__Eb[ 3] },
	/* 14 */  {  2, &BxOpcodeShiftFunG_RC__Eb[ 3] },
	/* 15 */  {  3, &BxOpcodeShiftFunG_RC__Eb[ 3] },
	/* 16 */  {  4, &BxOpcodeShiftFunG_RC__Eb[ 3] },
	/* 17 */  {  5, &BxOpcodeShiftFunG_RC__Eb[ 3] },
	/* 18 */  {  6, &BxOpcodeShiftFunG_RC__Eb[ 3] },
	/* 19 */  {  7, &BxOpcodeShiftFunG_RC__Eb[ 3] },
	/* 1a */  {  8, &BxOpcodeShiftFunG_RC__Eb[ 3] },
	/* 1b */  {  0, &BxOpcodeShiftFunG_RC__Eb[ 3] },
	/* 1c */  {  1, &BxOpcodeShiftFunG_RC__Eb[ 3] },
	/* 1d */  {  2, &BxOpcodeShiftFunG_RC__Eb[ 3] },
	/* 1e */  {  3, &BxOpcodeShiftFunG_RC__Eb[ 3] },
	/* 1f */  {  4, &BxOpcodeShiftFunG_RC__Eb[ 3] } 
};

const BxOpcodeShiftFun_t BxOpcodeShiftFunG_RC__Ew[4] =
{
	/*  0 */  {&BX_CPU_C::ROL_EGw_0,	&BX_CPU_C::ROL_EGw_0,	&BX_CPU_C::ROL_EEw_0,	&BX_CPU_C::ROL_EEw_0 },
	/*  1 */ {&BX_CPU_C::RCL_EGw_1,	&BX_CPU_C::RCR_EGw_1, &BX_CPU_C::RCL_EEw_1,	&BX_CPU_C::RCR_EEw_1 },
	/*  2 */ {&BX_CPU_C::RCL_EGw_n,	&BX_CPU_C::RCR_EGw_n, &BX_CPU_C::RCL_EEw_n,	&BX_CPU_C::RCR_EEw_n },
	/*  3 */ {&BX_CPU_C::RCL_EGw_n,	&BX_CPU_C::RCR_EGw_n, &BX_CPU_C::RCL_EEw_n,	&BX_CPU_C::RCR_EEw_n },
};

const BxOpcodeShiftTable_t BxOpcodeShiftTableG_RC__Ew[32] =
{
	/*  0 */  {  0, &BxOpcodeShiftFunG_RC__Ew[ 0] },
	/*  1 */  {  1, &BxOpcodeShiftFunG_RC__Ew[ 1] },
	/*  2 */  {  2, &BxOpcodeShiftFunG_RC__Ew[ 2] },
	/*  3 */  {  3, &BxOpcodeShiftFunG_RC__Ew[ 3] },
	/*  4 */  {  4, &BxOpcodeShiftFunG_RC__Ew[ 3] },
	/*  5 */  {  5, &BxOpcodeShiftFunG_RC__Ew[ 3] },
	/*  6 */  {  6, &BxOpcodeShiftFunG_RC__Ew[ 3] },
	/*  7 */  {  7, &BxOpcodeShiftFunG_RC__Ew[ 3] },
	/*  8 */  {  8, &BxOpcodeShiftFunG_RC__Ew[ 3] },
	/*  9 */  {  9, &BxOpcodeShiftFunG_RC__Ew[ 3] },
	/*  a */  { 10, &BxOpcodeShiftFunG_RC__Ew[ 3] },
	/*  b */  { 11, &BxOpcodeShiftFunG_RC__Ew[ 3] },
	/*  c */  { 12, &BxOpcodeShiftFunG_RC__Ew[ 3] },
	/*  d */  { 13, &BxOpcodeShiftFunG_RC__Ew[ 3] },
	/*  e */  { 14, &BxOpcodeShiftFunG_RC__Ew[ 3] },
	/*  f */  { 15, &BxOpcodeShiftFunG_RC__Ew[ 3] },
	/* 10 */  { 16, &BxOpcodeShiftFunG_RC__Ew[ 3] },
	/* 11 */  {  0, &BxOpcodeShiftFunG_RC__Ew[ 3] },
	/* 12 */  {  1, &BxOpcodeShiftFunG_RC__Ew[ 3] },
	/* 13 */  {  2, &BxOpcodeShiftFunG_RC__Ew[ 3] },
	/* 14 */  {  3, &BxOpcodeShiftFunG_RC__Ew[ 3] },
	/* 15 */  {  4, &BxOpcodeShiftFunG_RC__Ew[ 3] },
	/* 16 */  {  5, &BxOpcodeShiftFunG_RC__Ew[ 3] },
	/* 17 */  {  6, &BxOpcodeShiftFunG_RC__Ew[ 3] },
	/* 18 */  {  7, &BxOpcodeShiftFunG_RC__Ew[ 3] },
	/* 19 */  {  8, &BxOpcodeShiftFunG_RC__Ew[ 3] },
	/* 1a */  {  9, &BxOpcodeShiftFunG_RC__Ew[ 3] },
	/* 1b */  { 10, &BxOpcodeShiftFunG_RC__Ew[ 3] },
	/* 1c */  { 11, &BxOpcodeShiftFunG_RC__Ew[ 3] },
	/* 1d */  { 12, &BxOpcodeShiftFunG_RC__Ew[ 3] },
	/* 1e */  { 13, &BxOpcodeShiftFunG_RC__Ew[ 3] },
	/* 1f */  { 14, &BxOpcodeShiftFunG_RC__Ew[ 3] } 
};

const BxOpcodeShiftFun_t BxOpcodeShiftFunG_RC__Ed[4] =
{
	/*  0 */  {&BX_CPU_C::ROL_EGd_0,	&BX_CPU_C::ROL_EGd_0,	&BX_CPU_C::ROL_EEd_0,	&BX_CPU_C::ROL_EEd_0 },
	/*  1 */ {&BX_CPU_C::RCL_EGd_1,	&BX_CPU_C::RCR_EGd_1, &BX_CPU_C::RCL_EEd_1,	&BX_CPU_C::RCR_EEd_1 },
	/*  2 */ {&BX_CPU_C::RCL_EGd_n,	&BX_CPU_C::RCR_EGd_n, &BX_CPU_C::RCL_EEd_n,	&BX_CPU_C::RCR_EEd_n },
	/*  3 */ {&BX_CPU_C::RCL_EGd_n,	&BX_CPU_C::RCR_EGd_n, &BX_CPU_C::RCL_EEd_n,	&BX_CPU_C::RCR_EEd_n },
};

const BxOpcodeShiftTable_t BxOpcodeShiftTableG_RC__Ed[32] =
{
	/*  0 */  {  0, &BxOpcodeShiftFunG_RC__Ed[ 0] },
	/*  1 */  {  1, &BxOpcodeShiftFunG_RC__Ed[ 1] },
	/*  2 */  {  2, &BxOpcodeShiftFunG_RC__Ed[ 2] },
	/*  3 */  {  3, &BxOpcodeShiftFunG_RC__Ed[ 3] },
	/*  4 */  {  4, &BxOpcodeShiftFunG_RC__Ed[ 3] },
	/*  5 */  {  5, &BxOpcodeShiftFunG_RC__Ed[ 3] },
	/*  6 */  {  6, &BxOpcodeShiftFunG_RC__Ed[ 3] },
	/*  7 */  {  7, &BxOpcodeShiftFunG_RC__Ed[ 3] },
	/*  8 */  {  8, &BxOpcodeShiftFunG_RC__Ed[ 3] },
	/*  9 */  {  9, &BxOpcodeShiftFunG_RC__Ed[ 3] },
	/*  a */  { 10, &BxOpcodeShiftFunG_RC__Ed[ 3] },
	/*  b */  { 11, &BxOpcodeShiftFunG_RC__Ed[ 3] },
	/*  c */  { 12, &BxOpcodeShiftFunG_RC__Ed[ 3] },
	/*  d */  { 13, &BxOpcodeShiftFunG_RC__Ed[ 3] },
	/*  e */  { 14, &BxOpcodeShiftFunG_RC__Ed[ 3] },
	/*  f */  { 15, &BxOpcodeShiftFunG_RC__Ed[ 3] },
	/* 10 */  { 16, &BxOpcodeShiftFunG_RC__Ed[ 3] },
	/* 11 */  { 17, &BxOpcodeShiftFunG_RC__Ed[ 3] },
	/* 12 */  { 18, &BxOpcodeShiftFunG_RC__Ed[ 3] },
	/* 13 */  { 19, &BxOpcodeShiftFunG_RC__Ed[ 3] },
	/* 14 */  { 20, &BxOpcodeShiftFunG_RC__Ed[ 3] },
	/* 15 */  { 21, &BxOpcodeShiftFunG_RC__Ed[ 3] },
	/* 16 */  { 22, &BxOpcodeShiftFunG_RC__Ed[ 3] },
	/* 17 */  { 23, &BxOpcodeShiftFunG_RC__Ed[ 3] },
	/* 18 */  { 24, &BxOpcodeShiftFunG_RC__Ed[ 3] },
	/* 19 */  { 25, &BxOpcodeShiftFunG_RC__Ed[ 3] },
	/* 1a */  { 26, &BxOpcodeShiftFunG_RC__Ed[ 3] },
	/* 1b */  { 27, &BxOpcodeShiftFunG_RC__Ed[ 3] },
	/* 1c */  { 28, &BxOpcodeShiftFunG_RC__Ed[ 3] },
	/* 1d */  { 29, &BxOpcodeShiftFunG_RC__Ed[ 3] },
	/* 1e */  { 30, &BxOpcodeShiftFunG_RC__Ed[ 3] },
	/* 1f */  { 31, &BxOpcodeShiftFunG_RC__Ed[ 3] } 
};

const BxOpcodeShiftFun_t BxOpcodeShiftFunG_SH__Eb[4] =
{
	/*  0 */  {&BX_CPU_C::ROL_EGb_0,	&BX_CPU_C::ROL_EGb_0,	&BX_CPU_C::ROL_EEb_0,	&BX_CPU_C::ROL_EEb_0 },
	/*  1 */ {&BX_CPU_C::SHL_EGb_1,	&BX_CPU_C::SHR_EGb_1, &BX_CPU_C::SHL_EEb_1,	&BX_CPU_C::SHR_EEb_1 },
	/*  2 */ {&BX_CPU_C::SHL_EGb_n,	&BX_CPU_C::SHR_EGb_n, &BX_CPU_C::SHL_EEb_n,	&BX_CPU_C::SHR_EEb_n },
	/*  3 */ {&BX_CPU_C::SHL_EGb_n,	&BX_CPU_C::SHR_EGb_n, &BX_CPU_C::SHL_EEb_n,	&BX_CPU_C::SHR_EEb_n },
};

const BxOpcodeShiftTable_t BxOpcodeShiftTableG_SH__Eb[32] =
{
	/*  0 */  {  0, &BxOpcodeShiftFunG_SH__Eb[ 0] },
	/*  1 */  {  1, &BxOpcodeShiftFunG_SH__Eb[ 1] },
	/*  2 */  {  2, &BxOpcodeShiftFunG_SH__Eb[ 2] },
	/*  3 */  {  3, &BxOpcodeShiftFunG_SH__Eb[ 3] },
	/*  4 */  {  4, &BxOpcodeShiftFunG_SH__Eb[ 3] },
	/*  5 */  {  5, &BxOpcodeShiftFunG_SH__Eb[ 3] },
	/*  6 */  {  6, &BxOpcodeShiftFunG_SH__Eb[ 3] },
	/*  7 */  {  7, &BxOpcodeShiftFunG_SH__Eb[ 3] },
	/*  8 */  {  8, &BxOpcodeShiftFunG_SH__Eb[ 3] },
	/*  9 */  {  8, &BxOpcodeShiftFunG_SH__Eb[ 3] },
	/*  a */  {  8, &BxOpcodeShiftFunG_SH__Eb[ 3] },
	/*  b */  {  8, &BxOpcodeShiftFunG_SH__Eb[ 3] },
	/*  c */  {  8, &BxOpcodeShiftFunG_SH__Eb[ 3] },
	/*  d */  {  8, &BxOpcodeShiftFunG_SH__Eb[ 3] },
	/*  e */  {  8, &BxOpcodeShiftFunG_SH__Eb[ 3] },
	/*  f */  {  8, &BxOpcodeShiftFunG_SH__Eb[ 3] },
	/* 10 */  {  8, &BxOpcodeShiftFunG_SH__Eb[ 3] },
	/* 11 */  {  8, &BxOpcodeShiftFunG_SH__Eb[ 3] },
	/* 12 */  {  8, &BxOpcodeShiftFunG_SH__Eb[ 3] },
	/* 13 */  {  8, &BxOpcodeShiftFunG_SH__Eb[ 3] },
	/* 14 */  {  8, &BxOpcodeShiftFunG_SH__Eb[ 3] },
	/* 15 */  {  8, &BxOpcodeShiftFunG_SH__Eb[ 3] },
	/* 16 */  {  8, &BxOpcodeShiftFunG_SH__Eb[ 3] },
	/* 17 */  {  8, &BxOpcodeShiftFunG_SH__Eb[ 3] },
	/* 18 */  {  8, &BxOpcodeShiftFunG_SH__Eb[ 3] },
	/* 19 */  {  8, &BxOpcodeShiftFunG_SH__Eb[ 3] },
	/* 1a */  {  8, &BxOpcodeShiftFunG_SH__Eb[ 3] },
	/* 1b */  {  8, &BxOpcodeShiftFunG_SH__Eb[ 3] },
	/* 1c */  {  8, &BxOpcodeShiftFunG_SH__Eb[ 3] },
	/* 1d */  {  8, &BxOpcodeShiftFunG_SH__Eb[ 3] },
	/* 1e */  {  8, &BxOpcodeShiftFunG_SH__Eb[ 3] },
	/* 1f */  {  8, &BxOpcodeShiftFunG_SH__Eb[ 3] } 
};

const BxOpcodeShiftFun_t BxOpcodeShiftFunG_SH__Ew[4] =
{
	/*  0 */  {&BX_CPU_C::ROL_EGw_0,	&BX_CPU_C::ROL_EGw_0,	&BX_CPU_C::ROL_EEw_0,	&BX_CPU_C::ROL_EEw_0 },
	/*  1 */ {&BX_CPU_C::SHL_EGw_1,	&BX_CPU_C::SHR_EGw_1, &BX_CPU_C::SHL_EEw_1,	&BX_CPU_C::SHR_EEw_1 },
	/*  2 */ {&BX_CPU_C::SHL_EGw_n,	&BX_CPU_C::SHR_EGw_n, &BX_CPU_C::SHL_EEw_n,	&BX_CPU_C::SHR_EEw_n },
	/*  3 */ {&BX_CPU_C::SHL_EGw_n,	&BX_CPU_C::SHR_EGw_n, &BX_CPU_C::SHL_EEw_n,	&BX_CPU_C::SHR_EEw_n },
};

const BxOpcodeShiftTable_t BxOpcodeShiftTableG_SH__Ew[32] =
{
	/*  0 */  {  0, &BxOpcodeShiftFunG_SH__Ew[ 0] },
	/*  1 */  {  1, &BxOpcodeShiftFunG_SH__Ew[ 1] },
	/*  2 */  {  2, &BxOpcodeShiftFunG_SH__Ew[ 2] },
	/*  3 */  {  3, &BxOpcodeShiftFunG_SH__Ew[ 3] },
	/*  4 */  {  4, &BxOpcodeShiftFunG_SH__Ew[ 3] },
	/*  5 */  {  5, &BxOpcodeShiftFunG_SH__Ew[ 3] },
	/*  6 */  {  6, &BxOpcodeShiftFunG_SH__Ew[ 3] },
	/*  7 */  {  7, &BxOpcodeShiftFunG_SH__Ew[ 3] },
	/*  8 */  {  8, &BxOpcodeShiftFunG_SH__Ew[ 3] },
	/*  9 */  {  9, &BxOpcodeShiftFunG_SH__Ew[ 3] },
	/*  a */  { 10, &BxOpcodeShiftFunG_SH__Ew[ 3] },
	/*  b */  { 11, &BxOpcodeShiftFunG_SH__Ew[ 3] },
	/*  c */  { 12, &BxOpcodeShiftFunG_SH__Ew[ 3] },
	/*  d */  { 13, &BxOpcodeShiftFunG_SH__Ew[ 3] },
	/*  e */  { 14, &BxOpcodeShiftFunG_SH__Ew[ 3] },
	/*  f */  { 15, &BxOpcodeShiftFunG_SH__Ew[ 3] },
	/* 10 */  { 16, &BxOpcodeShiftFunG_SH__Ew[ 3] },
	/* 11 */  { 16, &BxOpcodeShiftFunG_SH__Ew[ 3] },
	/* 12 */  { 16, &BxOpcodeShiftFunG_SH__Ew[ 3] },
	/* 13 */  { 16, &BxOpcodeShiftFunG_SH__Ew[ 3] },
	/* 14 */  { 16, &BxOpcodeShiftFunG_SH__Ew[ 3] },
	/* 15 */  { 16, &BxOpcodeShiftFunG_SH__Ew[ 3] },
	/* 16 */  { 16, &BxOpcodeShiftFunG_SH__Ew[ 3] },
	/* 17 */  { 16, &BxOpcodeShiftFunG_SH__Ew[ 3] },
	/* 18 */  { 16, &BxOpcodeShiftFunG_SH__Ew[ 3] },
	/* 19 */  { 16, &BxOpcodeShiftFunG_SH__Ew[ 3] },
	/* 1a */  { 16, &BxOpcodeShiftFunG_SH__Ew[ 3] },
	/* 1b */  { 16, &BxOpcodeShiftFunG_SH__Ew[ 3] },
	/* 1c */  { 16, &BxOpcodeShiftFunG_SH__Ew[ 3] },
	/* 1d */  { 16, &BxOpcodeShiftFunG_SH__Ew[ 3] },
	/* 1e */  { 16, &BxOpcodeShiftFunG_SH__Ew[ 3] },
	/* 1f */  { 16, &BxOpcodeShiftFunG_SH__Ew[ 3] } 
};

const BxOpcodeShiftFun_t BxOpcodeShiftFunG_SH__Ed[4] =
{
	/*  0 */  {&BX_CPU_C::ROL_EGd_0,	&BX_CPU_C::ROL_EGd_0,	&BX_CPU_C::ROL_EEd_0,	&BX_CPU_C::ROL_EEd_0 },
	/*  1 */ {&BX_CPU_C::SHL_EGd_1,	&BX_CPU_C::SHR_EGd_1, &BX_CPU_C::SHL_EEd_1,	&BX_CPU_C::SHR_EEd_1 },
	/*  2 */ {&BX_CPU_C::SHL_EGd_n,	&BX_CPU_C::SHR_EGd_n, &BX_CPU_C::SHL_EEd_n,	&BX_CPU_C::SHR_EEd_n },
	/*  3 */ {&BX_CPU_C::SHL_EGd_n,	&BX_CPU_C::SHR_EGd_n, &BX_CPU_C::SHL_EEd_n,	&BX_CPU_C::SHR_EEd_n },
};

const BxOpcodeShiftTable_t BxOpcodeShiftTableG_SH__Ed[32] =
{
	/*  0 */  {  0, &BxOpcodeShiftFunG_SH__Ed[ 0] },
	/*  1 */  {  1, &BxOpcodeShiftFunG_SH__Ed[ 1] },
	/*  2 */  {  2, &BxOpcodeShiftFunG_SH__Ed[ 2] },
	/*  3 */  {  3, &BxOpcodeShiftFunG_SH__Ed[ 3] },
	/*  4 */  {  4, &BxOpcodeShiftFunG_SH__Ed[ 3] },
	/*  5 */  {  5, &BxOpcodeShiftFunG_SH__Ed[ 3] },
	/*  6 */  {  6, &BxOpcodeShiftFunG_SH__Ed[ 3] },
	/*  7 */  {  7, &BxOpcodeShiftFunG_SH__Ed[ 3] },
	/*  8 */  {  8, &BxOpcodeShiftFunG_SH__Ed[ 3] },
	/*  9 */  {  9, &BxOpcodeShiftFunG_SH__Ed[ 3] },
	/*  a */  { 10, &BxOpcodeShiftFunG_SH__Ed[ 3] },
	/*  b */  { 11, &BxOpcodeShiftFunG_SH__Ed[ 3] },
	/*  c */  { 12, &BxOpcodeShiftFunG_SH__Ed[ 3] },
	/*  d */  { 13, &BxOpcodeShiftFunG_SH__Ed[ 3] },
	/*  e */  { 14, &BxOpcodeShiftFunG_SH__Ed[ 3] },
	/*  f */  { 15, &BxOpcodeShiftFunG_SH__Ed[ 3] },
	/* 10 */  { 16, &BxOpcodeShiftFunG_SH__Ed[ 3] },
	/* 11 */  { 17, &BxOpcodeShiftFunG_SH__Ed[ 3] },
	/* 12 */  { 18, &BxOpcodeShiftFunG_SH__Ed[ 3] },
	/* 13 */  { 19, &BxOpcodeShiftFunG_SH__Ed[ 3] },
	/* 14 */  { 20, &BxOpcodeShiftFunG_SH__Ed[ 3] },
	/* 15 */  { 21, &BxOpcodeShiftFunG_SH__Ed[ 3] },
	/* 16 */  { 22, &BxOpcodeShiftFunG_SH__Ed[ 3] },
	/* 17 */  { 23, &BxOpcodeShiftFunG_SH__Ed[ 3] },
	/* 18 */  { 24, &BxOpcodeShiftFunG_SH__Ed[ 3] },
	/* 19 */  { 25, &BxOpcodeShiftFunG_SH__Ed[ 3] },
	/* 1a */  { 26, &BxOpcodeShiftFunG_SH__Ed[ 3] },
	/* 1b */  { 27, &BxOpcodeShiftFunG_SH__Ed[ 3] },
	/* 1c */  { 28, &BxOpcodeShiftFunG_SH__Ed[ 3] },
	/* 1d */  { 29, &BxOpcodeShiftFunG_SH__Ed[ 3] },
	/* 1e */  { 30, &BxOpcodeShiftFunG_SH__Ed[ 3] },
	/* 1f */  { 31, &BxOpcodeShiftFunG_SH__Ed[ 3] } 
};

const BxOpcodeShiftFun_t BxOpcodeShiftFunG_SA__Eb[4] =
{
	/*  0 */  {&BX_CPU_C::ROL_EGb_0,	&BX_CPU_C::ROL_EGb_0,	&BX_CPU_C::ROL_EEb_0,	&BX_CPU_C::ROL_EEb_0 },
	/*  1 */ {&BX_CPU_C::SHL_EGb_1,	&BX_CPU_C::SAR_EGb_1, &BX_CPU_C::SHL_EEb_1,	&BX_CPU_C::SAR_EEb_1 },
	/*  2 */ {&BX_CPU_C::SHL_EGb_n,	&BX_CPU_C::SAR_EGb_n, &BX_CPU_C::SHL_EEb_n,	&BX_CPU_C::SAR_EEb_n },
	/*  3 */ {&BX_CPU_C::SHL_EGb_n,	&BX_CPU_C::SAR_EGb_n, &BX_CPU_C::SHL_EEb_n,	&BX_CPU_C::SAR_EEb_n },
};

const BxOpcodeShiftTable_t BxOpcodeShiftTableG_SA__Eb[32] =
{
	/*  0 */  {  0, &BxOpcodeShiftFunG_SA__Eb[ 0] },
	/*  1 */  {  1, &BxOpcodeShiftFunG_SA__Eb[ 1] },
	/*  2 */  {  2, &BxOpcodeShiftFunG_SA__Eb[ 2] },
	/*  3 */  {  3, &BxOpcodeShiftFunG_SA__Eb[ 3] },
	/*  4 */  {  4, &BxOpcodeShiftFunG_SA__Eb[ 3] },
	/*  5 */  {  5, &BxOpcodeShiftFunG_SA__Eb[ 3] },
	/*  6 */  {  6, &BxOpcodeShiftFunG_SA__Eb[ 3] },
	/*  7 */  {  7, &BxOpcodeShiftFunG_SA__Eb[ 3] },
	/*  8 */  {  8, &BxOpcodeShiftFunG_SA__Eb[ 3] },
	/*  9 */  {  8, &BxOpcodeShiftFunG_SA__Eb[ 3] },
	/*  a */  {  8, &BxOpcodeShiftFunG_SA__Eb[ 3] },
	/*  b */  {  8, &BxOpcodeShiftFunG_SA__Eb[ 3] },
	/*  c */  {  8, &BxOpcodeShiftFunG_SA__Eb[ 3] },
	/*  d */  {  8, &BxOpcodeShiftFunG_SA__Eb[ 3] },
	/*  e */  {  8, &BxOpcodeShiftFunG_SA__Eb[ 3] },
	/*  f */  {  8, &BxOpcodeShiftFunG_SA__Eb[ 3] },
	/* 10 */  {  8, &BxOpcodeShiftFunG_SA__Eb[ 3] },
	/* 11 */  {  8, &BxOpcodeShiftFunG_SA__Eb[ 3] },
	/* 12 */  {  8, &BxOpcodeShiftFunG_SA__Eb[ 3] },
	/* 13 */  {  8, &BxOpcodeShiftFunG_SA__Eb[ 3] },
	/* 14 */  {  8, &BxOpcodeShiftFunG_SA__Eb[ 3] },
	/* 15 */  {  8, &BxOpcodeShiftFunG_SA__Eb[ 3] },
	/* 16 */  {  8, &BxOpcodeShiftFunG_SA__Eb[ 3] },
	/* 17 */  {  8, &BxOpcodeShiftFunG_SA__Eb[ 3] },
	/* 18 */  {  8, &BxOpcodeShiftFunG_SA__Eb[ 3] },
	/* 19 */  {  8, &BxOpcodeShiftFunG_SA__Eb[ 3] },
	/* 1a */  {  8, &BxOpcodeShiftFunG_SA__Eb[ 3] },
	/* 1b */  {  8, &BxOpcodeShiftFunG_SA__Eb[ 3] },
	/* 1c */  {  8, &BxOpcodeShiftFunG_SA__Eb[ 3] },
	/* 1d */  {  8, &BxOpcodeShiftFunG_SA__Eb[ 3] },
	/* 1e */  {  8, &BxOpcodeShiftFunG_SA__Eb[ 3] },
	/* 1f */  {  8, &BxOpcodeShiftFunG_SA__Eb[ 3] } 
};

const BxOpcodeShiftFun_t BxOpcodeShiftFunG_SA__Ew[4] =
{
	/*  0 */  {&BX_CPU_C::ROL_EGw_0,	&BX_CPU_C::ROL_EGw_0,	&BX_CPU_C::ROL_EEw_0,	&BX_CPU_C::ROL_EEw_0 },
	/*  1 */ {&BX_CPU_C::SHL_EGw_1,	&BX_CPU_C::SAR_EGw_1, &BX_CPU_C::SHL_EEw_1,	&BX_CPU_C::SAR_EEw_1 },
	/*  2 */ {&BX_CPU_C::SHL_EGw_n,	&BX_CPU_C::SAR_EGw_n, &BX_CPU_C::SHL_EEw_n,	&BX_CPU_C::SAR_EEw_n },
	/*  3 */ {&BX_CPU_C::SHL_EGw_n,	&BX_CPU_C::SAR_EGw_n, &BX_CPU_C::SHL_EEw_n,	&BX_CPU_C::SAR_EEw_n },
};

const BxOpcodeShiftTable_t BxOpcodeShiftTableG_SA__Ew[32] =
{
	/*  0 */  {  0, &BxOpcodeShiftFunG_SA__Ew[ 0] },
	/*  1 */  {  1, &BxOpcodeShiftFunG_SA__Ew[ 1] },
	/*  2 */  {  2, &BxOpcodeShiftFunG_SA__Ew[ 2] },
	/*  3 */  {  3, &BxOpcodeShiftFunG_SA__Ew[ 3] },
	/*  4 */  {  4, &BxOpcodeShiftFunG_SA__Ew[ 3] },
	/*  5 */  {  5, &BxOpcodeShiftFunG_SA__Ew[ 3] },
	/*  6 */  {  6, &BxOpcodeShiftFunG_SA__Ew[ 3] },
	/*  7 */  {  7, &BxOpcodeShiftFunG_SA__Ew[ 3] },
	/*  8 */  {  8, &BxOpcodeShiftFunG_SA__Ew[ 3] },
	/*  9 */  {  9, &BxOpcodeShiftFunG_SA__Ew[ 3] },
	/*  a */  { 10, &BxOpcodeShiftFunG_SA__Ew[ 3] },
	/*  b */  { 11, &BxOpcodeShiftFunG_SA__Ew[ 3] },
	/*  c */  { 12, &BxOpcodeShiftFunG_SA__Ew[ 3] },
	/*  d */  { 13, &BxOpcodeShiftFunG_SA__Ew[ 3] },
	/*  e */  { 14, &BxOpcodeShiftFunG_SA__Ew[ 3] },
	/*  f */  { 15, &BxOpcodeShiftFunG_SA__Ew[ 3] },
	/* 10 */  { 16, &BxOpcodeShiftFunG_SA__Ew[ 3] },
	/* 11 */  { 16, &BxOpcodeShiftFunG_SA__Ew[ 3] },
	/* 12 */  { 16, &BxOpcodeShiftFunG_SA__Ew[ 3] },
	/* 13 */  { 16, &BxOpcodeShiftFunG_SA__Ew[ 3] },
	/* 14 */  { 16, &BxOpcodeShiftFunG_SA__Ew[ 3] },
	/* 15 */  { 16, &BxOpcodeShiftFunG_SA__Ew[ 3] },
	/* 16 */  { 16, &BxOpcodeShiftFunG_SA__Ew[ 3] },
	/* 17 */  { 16, &BxOpcodeShiftFunG_SA__Ew[ 3] },
	/* 18 */  { 16, &BxOpcodeShiftFunG_SA__Ew[ 3] },
	/* 19 */  { 16, &BxOpcodeShiftFunG_SA__Ew[ 3] },
	/* 1a */  { 16, &BxOpcodeShiftFunG_SA__Ew[ 3] },
	/* 1b */  { 16, &BxOpcodeShiftFunG_SA__Ew[ 3] },
	/* 1c */  { 16, &BxOpcodeShiftFunG_SA__Ew[ 3] },
	/* 1d */  { 16, &BxOpcodeShiftFunG_SA__Ew[ 3] },
	/* 1e */  { 16, &BxOpcodeShiftFunG_SA__Ew[ 3] },
	/* 1f */  { 16, &BxOpcodeShiftFunG_SA__Ew[ 3] } 
};

const BxOpcodeShiftFun_t BxOpcodeShiftFunG_SA__Ed[4] =
{
	/*  0 */  {&BX_CPU_C::ROL_EGd_0,	&BX_CPU_C::ROL_EGd_0,	&BX_CPU_C::ROL_EEd_0,	&BX_CPU_C::ROL_EEd_0 },
	/*  1 */ {&BX_CPU_C::SHL_EGd_1,	&BX_CPU_C::SAR_EGd_1, &BX_CPU_C::SHL_EEd_1,	&BX_CPU_C::SAR_EEd_1 },
	/*  2 */ {&BX_CPU_C::SHL_EGd_n,	&BX_CPU_C::SAR_EGd_n, &BX_CPU_C::SHL_EEd_n,	&BX_CPU_C::SAR_EEd_n },
	/*  3 */ {&BX_CPU_C::SHL_EGd_n,	&BX_CPU_C::SAR_EGd_n, &BX_CPU_C::SHL_EEd_n,	&BX_CPU_C::SAR_EEd_n },
};

const BxOpcodeShiftTable_t BxOpcodeShiftTableG_SA__Ed[32] =
{
	/*  0 */  {  0, &BxOpcodeShiftFunG_SA__Ed[ 0] },
	/*  1 */  {  1, &BxOpcodeShiftFunG_SA__Ed[ 1] },
	/*  2 */  {  2, &BxOpcodeShiftFunG_SA__Ed[ 2] },
	/*  3 */  {  3, &BxOpcodeShiftFunG_SA__Ed[ 3] },
	/*  4 */  {  4, &BxOpcodeShiftFunG_SA__Ed[ 3] },
	/*  5 */  {  5, &BxOpcodeShiftFunG_SA__Ed[ 3] },
	/*  6 */  {  6, &BxOpcodeShiftFunG_SA__Ed[ 3] },
	/*  7 */  {  7, &BxOpcodeShiftFunG_SA__Ed[ 3] },
	/*  8 */  {  8, &BxOpcodeShiftFunG_SA__Ed[ 3] },
	/*  9 */  {  9, &BxOpcodeShiftFunG_SA__Ed[ 3] },
	/*  a */  { 10, &BxOpcodeShiftFunG_SA__Ed[ 3] },
	/*  b */  { 11, &BxOpcodeShiftFunG_SA__Ed[ 3] },
	/*  c */  { 12, &BxOpcodeShiftFunG_SA__Ed[ 3] },
	/*  d */  { 13, &BxOpcodeShiftFunG_SA__Ed[ 3] },
	/*  e */  { 14, &BxOpcodeShiftFunG_SA__Ed[ 3] },
	/*  f */  { 15, &BxOpcodeShiftFunG_SA__Ed[ 3] },
	/* 10 */  { 16, &BxOpcodeShiftFunG_SA__Ed[ 3] },
	/* 11 */  { 17, &BxOpcodeShiftFunG_SA__Ed[ 3] },
	/* 12 */  { 18, &BxOpcodeShiftFunG_SA__Ed[ 3] },
	/* 13 */  { 19, &BxOpcodeShiftFunG_SA__Ed[ 3] },
	/* 14 */  { 20, &BxOpcodeShiftFunG_SA__Ed[ 3] },
	/* 15 */  { 21, &BxOpcodeShiftFunG_SA__Ed[ 3] },
	/* 16 */  { 22, &BxOpcodeShiftFunG_SA__Ed[ 3] },
	/* 17 */  { 23, &BxOpcodeShiftFunG_SA__Ed[ 3] },
	/* 18 */  { 24, &BxOpcodeShiftFunG_SA__Ed[ 3] },
	/* 19 */  { 25, &BxOpcodeShiftFunG_SA__Ed[ 3] },
	/* 1a */  { 26, &BxOpcodeShiftFunG_SA__Ed[ 3] },
	/* 1b */  { 27, &BxOpcodeShiftFunG_SA__Ed[ 3] },
	/* 1c */  { 28, &BxOpcodeShiftFunG_SA__Ed[ 3] },
	/* 1d */  { 29, &BxOpcodeShiftFunG_SA__Ed[ 3] },
	/* 1e */  { 30, &BxOpcodeShiftFunG_SA__Ed[ 3] },
	/* 1f */  { 31, &BxOpcodeShiftFunG_SA__Ed[ 3] } 
};

const BxOpcodeShiftFun_t BxOpcodeShiftFunG_SH_D_EwGw[4] =
{
	/*  0 */  {&BX_CPU_C::ROL_EGw_0,	&BX_CPU_C::ROL_EGw_0,	&BX_CPU_C::ROL_EEw_0,	&BX_CPU_C::ROL_EEw_0 },
	/*  1 */ {&BX_CPU_C::SHLD_EGwGw_1,	&BX_CPU_C::SHRD_EGwGw_1, &BX_CPU_C::SHLD_EEwGw_1,	&BX_CPU_C::SHRD_EEwGw_1 },
	/*  2 */ {&BX_CPU_C::SHLD_EGwGw_n,	&BX_CPU_C::SHRD_EGwGw_n, &BX_CPU_C::SHLD_EEwGw_n,	&BX_CPU_C::SHRD_EEwGw_n },
	/*  3 */ {&BX_CPU_C::SHLD_EGwGw_n,	&BX_CPU_C::SHRD_EGwGw_n, &BX_CPU_C::SHLD_EEwGw_n,	&BX_CPU_C::SHRD_EEwGw_n },
};

const BxOpcodeShiftTable_t BxOpcodeShiftTableG_SH_D_EwGw[32] =
{
	/*  0 */  {  0, &BxOpcodeShiftFunG_SH_D_EwGw[ 0] },
	/*  1 */  {  1, &BxOpcodeShiftFunG_SH_D_EwGw[ 1] },
	/*  2 */  {  2, &BxOpcodeShiftFunG_SH_D_EwGw[ 2] },
	/*  3 */  {  3, &BxOpcodeShiftFunG_SH_D_EwGw[ 3] },
	/*  4 */  {  4, &BxOpcodeShiftFunG_SH_D_EwGw[ 3] },
	/*  5 */  {  5, &BxOpcodeShiftFunG_SH_D_EwGw[ 3] },
	/*  6 */  {  6, &BxOpcodeShiftFunG_SH_D_EwGw[ 3] },
	/*  7 */  {  7, &BxOpcodeShiftFunG_SH_D_EwGw[ 3] },
	/*  8 */  {  8, &BxOpcodeShiftFunG_SH_D_EwGw[ 3] },
	/*  9 */  {  9, &BxOpcodeShiftFunG_SH_D_EwGw[ 3] },
	/*  a */  { 10, &BxOpcodeShiftFunG_SH_D_EwGw[ 3] },
	/*  b */  { 11, &BxOpcodeShiftFunG_SH_D_EwGw[ 3] },
	/*  c */  { 12, &BxOpcodeShiftFunG_SH_D_EwGw[ 3] },
	/*  d */  { 13, &BxOpcodeShiftFunG_SH_D_EwGw[ 3] },
	/*  e */  { 14, &BxOpcodeShiftFunG_SH_D_EwGw[ 3] },
	/*  f */  { 15, &BxOpcodeShiftFunG_SH_D_EwGw[ 3] },
	/* 10 */  { 16, &BxOpcodeShiftFunG_SH_D_EwGw[ 3] },
	/* 11 */  { 17, &BxOpcodeShiftFunG_SH_D_EwGw[ 3] },
	/* 12 */  { 18, &BxOpcodeShiftFunG_SH_D_EwGw[ 3] },
	/* 13 */  { 19, &BxOpcodeShiftFunG_SH_D_EwGw[ 3] },
	/* 14 */  { 20, &BxOpcodeShiftFunG_SH_D_EwGw[ 3] },
	/* 15 */  { 21, &BxOpcodeShiftFunG_SH_D_EwGw[ 3] },
	/* 16 */  { 22, &BxOpcodeShiftFunG_SH_D_EwGw[ 3] },
	/* 17 */  { 23, &BxOpcodeShiftFunG_SH_D_EwGw[ 3] },
	/* 18 */  { 24, &BxOpcodeShiftFunG_SH_D_EwGw[ 3] },
	/* 19 */  { 25, &BxOpcodeShiftFunG_SH_D_EwGw[ 3] },
	/* 1a */  { 26, &BxOpcodeShiftFunG_SH_D_EwGw[ 3] },
	/* 1b */  { 27, &BxOpcodeShiftFunG_SH_D_EwGw[ 3] },
	/* 1c */  { 28, &BxOpcodeShiftFunG_SH_D_EwGw[ 3] },
	/* 1d */  { 29, &BxOpcodeShiftFunG_SH_D_EwGw[ 3] },
	/* 1e */  { 30, &BxOpcodeShiftFunG_SH_D_EwGw[ 3] },
	/* 1f */  { 31, &BxOpcodeShiftFunG_SH_D_EwGw[ 3] } 
};

const BxOpcodeShiftFun_t BxOpcodeShiftFunG_SH_D_EdGd[4] =
{
	/*  0 */  {&BX_CPU_C::ROL_EGd_0,	&BX_CPU_C::ROL_EGd_0,	&BX_CPU_C::ROL_EEd_0,	&BX_CPU_C::ROL_EEd_0 },
	/*  1 */ {&BX_CPU_C::SHLD_EGdGd_1,	&BX_CPU_C::SHRD_EGdGd_1, &BX_CPU_C::SHLD_EEdGd_1,	&BX_CPU_C::SHRD_EEdGd_1 },
	/*  2 */ {&BX_CPU_C::SHLD_EGdGd_n,	&BX_CPU_C::SHRD_EGdGd_n, &BX_CPU_C::SHLD_EEdGd_n,	&BX_CPU_C::SHRD_EEdGd_n },
	/*  3 */ {&BX_CPU_C::SHLD_EGdGd_n,	&BX_CPU_C::SHRD_EGdGd_n, &BX_CPU_C::SHLD_EEdGd_n,	&BX_CPU_C::SHRD_EEdGd_n },
};

const BxOpcodeShiftTable_t BxOpcodeShiftTableG_SH_D_EdGd[32] =
{
	/*  0 */  {  0, &BxOpcodeShiftFunG_SH_D_EdGd[ 0] },
	/*  1 */  {  1, &BxOpcodeShiftFunG_SH_D_EdGd[ 1] },
	/*  2 */  {  2, &BxOpcodeShiftFunG_SH_D_EdGd[ 2] },
	/*  3 */  {  3, &BxOpcodeShiftFunG_SH_D_EdGd[ 3] },
	/*  4 */  {  4, &BxOpcodeShiftFunG_SH_D_EdGd[ 3] },
	/*  5 */  {  5, &BxOpcodeShiftFunG_SH_D_EdGd[ 3] },
	/*  6 */  {  6, &BxOpcodeShiftFunG_SH_D_EdGd[ 3] },
	/*  7 */  {  7, &BxOpcodeShiftFunG_SH_D_EdGd[ 3] },
	/*  8 */  {  8, &BxOpcodeShiftFunG_SH_D_EdGd[ 3] },
	/*  9 */  {  9, &BxOpcodeShiftFunG_SH_D_EdGd[ 3] },
	/*  a */  { 10, &BxOpcodeShiftFunG_SH_D_EdGd[ 3] },
	/*  b */  { 11, &BxOpcodeShiftFunG_SH_D_EdGd[ 3] },
	/*  c */  { 12, &BxOpcodeShiftFunG_SH_D_EdGd[ 3] },
	/*  d */  { 13, &BxOpcodeShiftFunG_SH_D_EdGd[ 3] },
	/*  e */  { 14, &BxOpcodeShiftFunG_SH_D_EdGd[ 3] },
	/*  f */  { 15, &BxOpcodeShiftFunG_SH_D_EdGd[ 3] },
	/* 10 */  { 16, &BxOpcodeShiftFunG_SH_D_EdGd[ 3] },
	/* 11 */  { 17, &BxOpcodeShiftFunG_SH_D_EdGd[ 3] },
	/* 12 */  { 18, &BxOpcodeShiftFunG_SH_D_EdGd[ 3] },
	/* 13 */  { 19, &BxOpcodeShiftFunG_SH_D_EdGd[ 3] },
	/* 14 */  { 20, &BxOpcodeShiftFunG_SH_D_EdGd[ 3] },
	/* 15 */  { 21, &BxOpcodeShiftFunG_SH_D_EdGd[ 3] },
	/* 16 */  { 22, &BxOpcodeShiftFunG_SH_D_EdGd[ 3] },
	/* 17 */  { 23, &BxOpcodeShiftFunG_SH_D_EdGd[ 3] },
	/* 18 */  { 24, &BxOpcodeShiftFunG_SH_D_EdGd[ 3] },
	/* 19 */  { 25, &BxOpcodeShiftFunG_SH_D_EdGd[ 3] },
	/* 1a */  { 26, &BxOpcodeShiftFunG_SH_D_EdGd[ 3] },
	/* 1b */  { 27, &BxOpcodeShiftFunG_SH_D_EdGd[ 3] },
	/* 1c */  { 28, &BxOpcodeShiftFunG_SH_D_EdGd[ 3] },
	/* 1d */  { 29, &BxOpcodeShiftFunG_SH_D_EdGd[ 3] },
	/* 1e */  { 30, &BxOpcodeShiftFunG_SH_D_EdGd[ 3] },
	/* 1f */  { 31, &BxOpcodeShiftFunG_SH_D_EdGd[ 3] } 
};

