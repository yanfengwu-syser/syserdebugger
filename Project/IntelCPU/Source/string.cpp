/////////////////////////////////////////////////////////////////////////
// $Id: string.cc,v 1.0 2002/10/10 04:57:05 bdenney Exp $
/////////////////////////////////////////////////////////////////////////


#include "stdafx.h"
#include "x86cpu.h"
//---------------------------------------------------------
//虚拟执行--指令微函数  串操作指令
//---------------------------------------------------------


/* MOVSB ES:[EDI], DS:[ESI] DS may be overridden
 *  mov string from DS:[ESI] into ES:[EDI]
 */
	void
BX_CPU_C::MOVSB_XbYb_E16_rep__(BX_CPU_C *icpu,bxInstruction_c *i)
{
	unsigned seg;
	Bit8u op1;
	seg = MODRMSeg(i);

	Bit32u esi,edi;
	esi = RW_SI;
	edi = RW_DI;
	READ_VIRTUAL_BYTE(seg, esi, &op1);
	WRITE_VIRTUAL_BYTE(BX_SEG_REG_ES, edi, &op1);
	if (BX_CPU_CLASS_PTR get_DF())
	{
		esi -= 1;
		edi -= 1;
	}
	else
	{
		esi += 1;
		edi += 1;
	}
	RW_SI = esi;
	RW_DI = edi;
}

	void
BX_CPU_C::MOVSB_XbYb_E16_repf2(BX_CPU_C *icpu,bxInstruction_c *i)
{
	unsigned seg;
	Bit8u op1;
	seg = MODRMSeg(i);

	//++++++++++++++++++++++++++++++++
	//ECX等于零时退出,否则执行
	if (RW_CX==0)
		return;

RepeatRun:

	Bit32u esi,edi;
	esi = RW_SI;
	edi = RW_DI;
	READ_VIRTUAL_BYTE(seg, esi, &op1);
	WRITE_VIRTUAL_BYTE(BX_SEG_REG_ES, edi, &op1);
	if (BX_CPU_CLASS_PTR get_DF())
	{
		esi -= 1;
		edi -= 1;
	}
	else
	{
		esi += 1;
		edi += 1;
	}
	RW_SI = esi;
	RW_DI = edi;
	RW_CX--;
	if (RW_CX==0)
		return;

	if (BX_CPU_CLASS_PTR async_event)
	{
		BX_CPU_CLASS_PTR invalidate_prefetch_q();
		RW_EIP	= BX_CPU_CLASS_PTR prev_eip; // commit old EIP
		return;
	}

	goto RepeatRun;
}

	void
BX_CPU_C::MOVSB_XbYb_E16_repf3(BX_CPU_C *icpu,bxInstruction_c *i)
{
	unsigned seg;
	Bit8u op1;
	seg = MODRMSeg(i);

	//++++++++++++++++++++++++++++++++
	//ECX等于零时退出,否则执行
	if (RW_CX==0)
		return;

RepeatRun:

	Bit32u esi,edi;
	esi = RW_SI;
	edi = RW_DI;
	READ_VIRTUAL_BYTE(seg, esi, &op1);
	WRITE_VIRTUAL_BYTE(BX_SEG_REG_ES, edi, &op1);
	if (BX_CPU_CLASS_PTR get_DF())
	{
		esi -= 1;
		edi -= 1;
	}
	else
	{
		esi += 1;
		edi += 1;
	}
	RW_SI = esi;
	RW_DI = edi;
	RW_CX--;
	if (RW_CX==0)
		return;

	if (BX_CPU_CLASS_PTR async_event)
	{
		BX_CPU_CLASS_PTR invalidate_prefetch_q();
		RW_EIP	= BX_CPU_CLASS_PTR prev_eip; // commit old EIP
		return;
	}

	goto RepeatRun;
}

	void
BX_CPU_C::MOVSB_XbYb_E32_rep__(BX_CPU_C *icpu,bxInstruction_c *i)
{
	unsigned seg;
	Bit8u op1;
	seg = MODRMSeg(i);

	Bit32u esi,edi;
	esi = RW_ESI;
	edi = RW_EDI;
	READ_VIRTUAL_BYTE(seg, esi, &op1);
	WRITE_VIRTUAL_BYTE(BX_SEG_REG_ES, edi, &op1);
	if (BX_CPU_CLASS_PTR get_DF())
	{
		esi -= 1;
		edi -= 1;
	}
	else
	{
		esi += 1;
		edi += 1;
	}
	RW_ESI = esi;
	RW_EDI = edi;
}

	void
BX_CPU_C::MOVSB_XbYb_E32_repf2(BX_CPU_C *icpu,bxInstruction_c *i)
{
	unsigned seg;
	Bit8u op1;
	seg = MODRMSeg(i);

	//++++++++++++++++++++++++++++++++
	//ECX等于零时退出,否则执行
	if (RW_ECX==0)
		return;

RepeatRun:

	Bit32u esi,edi;
	esi = RW_ESI;
	edi = RW_EDI;
	READ_VIRTUAL_BYTE(seg, esi, &op1);
	WRITE_VIRTUAL_BYTE(BX_SEG_REG_ES, edi, &op1);
	if (BX_CPU_CLASS_PTR get_DF())
	{
		esi -= 1;
		edi -= 1;
	}
	else
	{
		esi += 1;
		edi += 1;
	}
	RW_ESI = esi;
	RW_EDI = edi;
	RW_ECX--;
	if (RW_ECX==0)
		return;

	if (BX_CPU_CLASS_PTR async_event)
	{
		BX_CPU_CLASS_PTR invalidate_prefetch_q();
		RW_EIP	= BX_CPU_CLASS_PTR prev_eip; // commit old EIP
		return;
	}

	goto RepeatRun;
}

	void
BX_CPU_C::MOVSB_XbYb_E32_repf3(BX_CPU_C *icpu,bxInstruction_c *i)
{
	unsigned seg;
	Bit8u op1;
	seg = MODRMSeg(i);

	//++++++++++++++++++++++++++++++++
	//ECX等于零时退出,否则执行
	if (RW_ECX==0)
		return;

RepeatRun:

	Bit32u esi,edi;
	esi = RW_ESI;
	edi = RW_EDI;
	READ_VIRTUAL_BYTE(seg, esi, &op1);
	WRITE_VIRTUAL_BYTE(BX_SEG_REG_ES, edi, &op1);
	if (BX_CPU_CLASS_PTR get_DF())
	{
		esi -= 1;
		edi -= 1;
	}
	else
	{
		esi += 1;
		edi += 1;
	}
	RW_ESI = esi;
	RW_EDI = edi;
	RW_ECX--;
	if (RW_ECX==0)
		return;

	if (BX_CPU_CLASS_PTR async_event)
	{
		BX_CPU_CLASS_PTR invalidate_prefetch_q();
		RW_EIP	= BX_CPU_CLASS_PTR prev_eip; // commit old EIP
		return;
	}

	goto RepeatRun;
}

	void
BX_CPU_C::MOVSW_XvYv_E16_rep__(BX_CPU_C *icpu,bxInstruction_c *i)
{
	unsigned seg;
	Bit16u op1;
	seg = MODRMSeg(i);

	Bit32u esi,edi;
	esi = RW_SI;
	edi = RW_DI;
	READ_VIRTUAL_WORD(seg, esi, &op1);
	WRITE_VIRTUAL_WORD(BX_SEG_REG_ES, edi, &op1);
	if (BX_CPU_CLASS_PTR get_DF())
	{
		esi -= 2;
		edi -= 2;
	}
	else
	{
		esi += 2;
		edi += 2;
	}
	RW_SI = esi;
	RW_DI = edi;
}

	void
BX_CPU_C::MOVSW_XvYv_E16_repf2(BX_CPU_C *icpu,bxInstruction_c *i)
{
	unsigned seg;
	Bit16u op1;
	seg = MODRMSeg(i);

	//++++++++++++++++++++++++++++++++
	//ECX等于零时退出,否则执行
	if (RW_CX==0)
		return;

RepeatRun:

	Bit32u esi,edi;
	esi = RW_SI;
	edi = RW_DI;
	READ_VIRTUAL_WORD(seg, esi, &op1);
	WRITE_VIRTUAL_WORD(BX_SEG_REG_ES, edi, &op1);
	if (BX_CPU_CLASS_PTR get_DF())
	{
		esi -= 2;
		edi -= 2;
	}
	else
	{
		esi += 2;
		edi += 2;
	}
	RW_SI = esi;
	RW_DI = edi;
	RW_CX--;
	if (RW_CX==0)
		return;

	if (BX_CPU_CLASS_PTR async_event)
	{
		BX_CPU_CLASS_PTR invalidate_prefetch_q();
		RW_EIP	= BX_CPU_CLASS_PTR prev_eip; // commit old EIP
		return;
	}

	goto RepeatRun;
}

	void
BX_CPU_C::MOVSW_XvYv_E16_repf3(BX_CPU_C *icpu,bxInstruction_c *i)
{
	unsigned seg;
	Bit16u op1;
	seg = MODRMSeg(i);

	//++++++++++++++++++++++++++++++++
	//ECX等于零时退出,否则执行
	if (RW_CX==0)
		return;

RepeatRun:

	Bit32u esi,edi;
	esi = RW_SI;
	edi = RW_DI;
	READ_VIRTUAL_WORD(seg, esi, &op1);
	WRITE_VIRTUAL_WORD(BX_SEG_REG_ES, edi, &op1);
	if (BX_CPU_CLASS_PTR get_DF())
	{
		esi -= 2;
		edi -= 2;
	}
	else
	{
		esi += 2;
		edi += 2;
	}
	RW_SI = esi;
	RW_DI = edi;
	RW_CX--;
	if (RW_CX==0)
		return;

	if (BX_CPU_CLASS_PTR async_event)
	{
		BX_CPU_CLASS_PTR invalidate_prefetch_q();
		RW_EIP	= BX_CPU_CLASS_PTR prev_eip; // commit old EIP
		return;
	}

	goto RepeatRun;
}

	void
BX_CPU_C::MOVSW_XvYv_E32_rep__(BX_CPU_C *icpu,bxInstruction_c *i)
{
	unsigned seg;
	Bit16u op1;
	seg = MODRMSeg(i);

	Bit32u esi,edi;
	esi = RW_ESI;
	edi = RW_EDI;
	READ_VIRTUAL_WORD(seg, esi, &op1);
	WRITE_VIRTUAL_WORD(BX_SEG_REG_ES, edi, &op1);
	if (BX_CPU_CLASS_PTR get_DF())
	{
		esi -= 2;
		edi -= 2;
	}
	else
	{
		esi += 2;
		edi += 2;
	}
	RW_ESI = esi;
	RW_EDI = edi;
}

	void
BX_CPU_C::MOVSW_XvYv_E32_repf2(BX_CPU_C *icpu,bxInstruction_c *i)
{
	unsigned seg;
	Bit16u op1;
	seg = MODRMSeg(i);

	//++++++++++++++++++++++++++++++++
	//ECX等于零时退出,否则执行
	if (RW_ECX==0)
		return;

RepeatRun:

	Bit32u esi,edi;
	esi = RW_ESI;
	edi = RW_EDI;
	READ_VIRTUAL_WORD(seg, esi, &op1);
	WRITE_VIRTUAL_WORD(BX_SEG_REG_ES, edi, &op1);
	if (BX_CPU_CLASS_PTR get_DF())
	{
		esi -= 2;
		edi -= 2;
	}
	else
	{
		esi += 2;
		edi += 2;
	}
	RW_ESI = esi;
	RW_EDI = edi;
	RW_ECX--;
	if (RW_ECX==0)
		return;

	if (BX_CPU_CLASS_PTR async_event)
	{
		BX_CPU_CLASS_PTR invalidate_prefetch_q();
		RW_EIP	= BX_CPU_CLASS_PTR prev_eip; // commit old EIP
		return;
	}

	goto RepeatRun;
}

	void
BX_CPU_C::MOVSW_XvYv_E32_repf3(BX_CPU_C *icpu,bxInstruction_c *i)
{
	unsigned seg;
	Bit16u op1;
	seg = MODRMSeg(i);

	//++++++++++++++++++++++++++++++++
	//ECX等于零时退出,否则执行
	if (RW_ECX==0)
		return;

RepeatRun:

	Bit32u esi,edi;
	esi = RW_ESI;
	edi = RW_EDI;
	READ_VIRTUAL_WORD(seg, esi, &op1);
	WRITE_VIRTUAL_WORD(BX_SEG_REG_ES, edi, &op1);
	if (BX_CPU_CLASS_PTR get_DF())
	{
		esi -= 2;
		edi -= 2;
	}
	else
	{
		esi += 2;
		edi += 2;
	}
	RW_ESI = esi;
	RW_EDI = edi;
	RW_ECX--;
	if (RW_ECX==0)
		return;

	if (BX_CPU_CLASS_PTR async_event)
	{
		BX_CPU_CLASS_PTR invalidate_prefetch_q();
		RW_EIP	= BX_CPU_CLASS_PTR prev_eip; // commit old EIP
		return;
	}

	goto RepeatRun;
}

	void
BX_CPU_C::MOVSD_XvYv_E16_rep__(BX_CPU_C *icpu,bxInstruction_c *i)
{
	unsigned seg;
	Bit32u op1;
	seg = MODRMSeg(i);

	Bit32u esi,edi;
	esi = RW_SI;
	edi = RW_DI;
	READ_VIRTUAL_DWORD(seg, esi, &op1);
	WRITE_VIRTUAL_DWORD(BX_SEG_REG_ES, edi, &op1);
	if (BX_CPU_CLASS_PTR get_DF())
	{
		esi -= 4;
		edi -= 4;
	}
	else
	{
		esi += 4;
		edi += 4;
	}
	RW_SI = esi;
	RW_DI = edi;
}

	void
BX_CPU_C::MOVSD_XvYv_E16_repf2(BX_CPU_C *icpu,bxInstruction_c *i)
{
	unsigned seg;
	Bit32u op1;
	seg = MODRMSeg(i);

	//++++++++++++++++++++++++++++++++
	//ECX等于零时退出,否则执行
	if (RW_CX==0)
		return;

RepeatRun:

	Bit32u esi,edi;
	esi = RW_SI;
	edi = RW_DI;
	READ_VIRTUAL_DWORD(seg, esi, &op1);
	WRITE_VIRTUAL_DWORD(BX_SEG_REG_ES, edi, &op1);
	if (BX_CPU_CLASS_PTR get_DF())
	{
		esi -= 4;
		edi -= 4;
	}
	else
	{
		esi += 4;
		edi += 4;
	}
	RW_SI = esi;
	RW_DI = edi;
	RW_CX--;
	if (RW_CX==0)
		return;

	if (BX_CPU_CLASS_PTR async_event)
	{
		BX_CPU_CLASS_PTR invalidate_prefetch_q();
		RW_EIP	= BX_CPU_CLASS_PTR prev_eip; // commit old EIP
		return;
	}

	goto RepeatRun;
}

	void
BX_CPU_C::MOVSD_XvYv_E16_repf3(BX_CPU_C *icpu,bxInstruction_c *i)
{
	unsigned seg;
	Bit32u op1;
	seg = MODRMSeg(i);

	//++++++++++++++++++++++++++++++++
	//ECX等于零时退出,否则执行
	if (RW_CX==0)
		return;

RepeatRun:

	Bit32u esi,edi;
	esi = RW_SI;
	edi = RW_DI;
	READ_VIRTUAL_DWORD(seg, esi, &op1);
	WRITE_VIRTUAL_DWORD(BX_SEG_REG_ES, edi, &op1);
	if (BX_CPU_CLASS_PTR get_DF())
	{
		esi -= 4;
		edi -= 4;
	}
	else
	{
		esi += 4;
		edi += 4;
	}
	RW_SI = esi;
	RW_DI = edi;
	RW_CX--;
	if (RW_CX==0)
		return;

	if (BX_CPU_CLASS_PTR async_event)
	{
		BX_CPU_CLASS_PTR invalidate_prefetch_q();
		RW_EIP	= BX_CPU_CLASS_PTR prev_eip; // commit old EIP
		return;
	}

	goto RepeatRun;
}

	void
BX_CPU_C::MOVSD_XvYv_E32_rep__(BX_CPU_C *icpu,bxInstruction_c *i)
{
	unsigned seg;
	Bit32u op1;
	seg = MODRMSeg(i);

	Bit32u esi,edi;
	esi = RW_ESI;
	edi = RW_EDI;
	READ_VIRTUAL_DWORD(seg, esi, &op1);
	WRITE_VIRTUAL_DWORD(BX_SEG_REG_ES, edi, &op1);
	if (BX_CPU_CLASS_PTR get_DF())
	{
		esi -= 4;
		edi -= 4;
	}
	else
	{
		esi += 4;
		edi += 4;
	}
	RW_ESI = esi;
	RW_EDI = edi;
}

	void
BX_CPU_C::MOVSD_XvYv_E32_repf2(BX_CPU_C *icpu,bxInstruction_c *i)
{
	unsigned seg;
	Bit32u op1;
	seg = MODRMSeg(i);

	//++++++++++++++++++++++++++++++++
	//ECX等于零时退出,否则执行
	if (RW_ECX==0)
		return;

RepeatRun:

	Bit32u esi,edi;
	esi = RW_ESI;
	edi = RW_EDI;
	READ_VIRTUAL_DWORD(seg, esi, &op1);
	WRITE_VIRTUAL_DWORD(BX_SEG_REG_ES, edi, &op1);
	if (BX_CPU_CLASS_PTR get_DF())
	{
		esi -= 4;
		edi -= 4;
	}
	else
	{
		esi += 4;
		edi += 4;
	}
	RW_ESI = esi;
	RW_EDI = edi;
	RW_ECX--;
	if (RW_ECX==0)
		return;

	if (BX_CPU_CLASS_PTR async_event)
	{
		BX_CPU_CLASS_PTR invalidate_prefetch_q();
		RW_EIP	= BX_CPU_CLASS_PTR prev_eip; // commit old EIP
		return;
	}

	goto RepeatRun;
}

	void
BX_CPU_C::MOVSD_XvYv_E32_repf3(BX_CPU_C *icpu,bxInstruction_c *i)
{
	unsigned seg;
	Bit32u op1;
	seg = MODRMSeg(i);

	//++++++++++++++++++++++++++++++++
	//ECX等于零时退出,否则执行
	if (RW_ECX==0)
		return;

RepeatRun:

	Bit32u esi,edi;
	esi = RW_ESI;
	edi = RW_EDI;
	READ_VIRTUAL_DWORD(seg, esi, &op1);
	WRITE_VIRTUAL_DWORD(BX_SEG_REG_ES, edi, &op1);
	if (BX_CPU_CLASS_PTR get_DF())
	{
		esi -= 4;
		edi -= 4;
	}
	else
	{
		esi += 4;
		edi += 4;
	}
	RW_ESI = esi;
	RW_EDI = edi;
	RW_ECX--;
	if (RW_ECX==0)
		return;

	if (BX_CPU_CLASS_PTR async_event)
	{
		BX_CPU_CLASS_PTR invalidate_prefetch_q();
		RW_EIP	= BX_CPU_CLASS_PTR prev_eip; // commit old EIP
		return;
	}

	goto RepeatRun;
}

	void
BX_CPU_C::CMPSB_XbYb_E16_rep__(BX_CPU_C *icpu,bxInstruction_c *i)
{
	unsigned seg;
	Bit8u op1,op2,diff;
	seg = MODRMSeg(i);

	Bit32u esi,edi;
	esi = RW_SI;
	edi = RW_DI;
	READ_VIRTUAL_BYTE(seg, esi, &op1);
	READ_VIRTUAL_BYTE(BX_SEG_REG_ES, edi, &op2);
	diff = op1 - op2;
	if (BX_CPU_CLASS_PTR get_DF())
	{
		esi -= 1;
		edi -= 1;
	}
	else
	{
		esi += 1;
		edi += 1;
	}
	RW_SI = esi;
	RW_DI = edi;
#if (HOST_CPU_IS_I80386==0)
	SET_FLAGS_OSZAPC_8(op1,op2,diff,BX_INSTR_CMPS8);
#endif //#if (HOST_CPU_IS_I80386==0)
#if (HOST_CPU_IS_I80386==1)
	Bit32u x86_lf_flags;
	__asm
	{
		mov dl,op2
		cmp op1,dl
		lahf
		seto al
		mov x86_lf_flags,eax
	}
	BX_CPU_CLASS_PTR eflags.x86.eax = x86_lf_flags;
#endif //#if (HOST_CPU_IS_I80386==1)
}

	void
BX_CPU_C::CMPSB_XbYb_E16_repf2(BX_CPU_C *icpu,bxInstruction_c *i)
{
	unsigned seg;
	Bit8u op1,op2,diff;
	seg = MODRMSeg(i);

	//++++++++++++++++++++++++++++++++
	//ECX等于零时退出,否则执行
	if (RW_CX==0)
		return;

RepeatRun:

	Bit32u esi,edi;
	esi = RW_SI;
	edi = RW_DI;
	READ_VIRTUAL_BYTE(seg, esi, &op1);
	READ_VIRTUAL_BYTE(BX_SEG_REG_ES, edi, &op2);
	diff = op1 - op2;
	if (BX_CPU_CLASS_PTR get_DF())
	{
		esi -= 1;
		edi -= 1;
	}
	else
	{
		esi += 1;
		edi += 1;
	}
	RW_SI = esi;
	RW_DI = edi;
	RW_CX--;
	//原与目标相等||ECX==0 时退出,否则重复执行
	if (diff==0||RW_CX==0)
	{
#if (HOST_CPU_IS_I80386==0)
	SET_FLAGS_OSZAPC_8(op1,op2,diff,BX_INSTR_CMPS8);
#endif //#if (HOST_CPU_IS_I80386==0)
#if (HOST_CPU_IS_I80386==1)
	Bit32u x86_lf_flags;
	__asm
	{
		mov dl,op2
		cmp op1,dl
		lahf
		seto al
		mov x86_lf_flags,eax
	}
	BX_CPU_CLASS_PTR eflags.x86.eax = x86_lf_flags;
#endif //#if (HOST_CPU_IS_I80386==1)
		return;
	}

	if (BX_CPU_CLASS_PTR async_event)
	{
		BX_CPU_CLASS_PTR invalidate_prefetch_q();
		RW_EIP	= BX_CPU_CLASS_PTR prev_eip; // commit old EIP
		return;
	}

	goto RepeatRun;
}

	void
BX_CPU_C::CMPSB_XbYb_E16_repf3(BX_CPU_C *icpu,bxInstruction_c *i)
{
	unsigned seg;
	Bit8u op1,op2,diff;
	seg = MODRMSeg(i);

	//++++++++++++++++++++++++++++++++
	//ECX等于零时退出,否则执行
	if (RW_CX==0)
		return;

RepeatRun:

	Bit32u esi,edi;
	esi = RW_SI;
	edi = RW_DI;
	READ_VIRTUAL_BYTE(seg, esi, &op1);
	READ_VIRTUAL_BYTE(BX_SEG_REG_ES, edi, &op2);
	diff = op1 - op2;
	if (BX_CPU_CLASS_PTR get_DF())
	{
		esi -= 1;
		edi -= 1;
	}
	else
	{
		esi += 1;
		edi += 1;
	}
	RW_SI = esi;
	RW_DI = edi;
	RW_CX--;
	//原与目标不相等||ECX==0 时退出,否则重复执行
	if (diff!=0||RW_CX==0)
	{
#if (HOST_CPU_IS_I80386==0)
	SET_FLAGS_OSZAPC_8(op1,op2,diff,BX_INSTR_CMPS8);
#endif //#if (HOST_CPU_IS_I80386==0)
#if (HOST_CPU_IS_I80386==1)
	Bit32u x86_lf_flags;
	__asm
	{
		mov dl,op2
		cmp op1,dl
		lahf
		seto al
		mov x86_lf_flags,eax
	}
	BX_CPU_CLASS_PTR eflags.x86.eax = x86_lf_flags;
#endif //#if (HOST_CPU_IS_I80386==1)
		return;
	}

	if (BX_CPU_CLASS_PTR async_event)
	{
		BX_CPU_CLASS_PTR invalidate_prefetch_q();
		RW_EIP	= BX_CPU_CLASS_PTR prev_eip; // commit old EIP
		return;
	}

	goto RepeatRun;
}

	void
BX_CPU_C::CMPSB_XbYb_E32_rep__(BX_CPU_C *icpu,bxInstruction_c *i)
{
	unsigned seg;
	Bit8u op1,op2,diff;
	seg = MODRMSeg(i);

	Bit32u esi,edi;
	esi = RW_ESI;
	edi = RW_EDI;
	READ_VIRTUAL_BYTE(seg, esi, &op1);
	READ_VIRTUAL_BYTE(BX_SEG_REG_ES, edi, &op2);
	diff = op1 - op2;
	if (BX_CPU_CLASS_PTR get_DF())
	{
		esi -= 1;
		edi -= 1;
	}
	else
	{
		esi += 1;
		edi += 1;
	}
	RW_ESI = esi;
	RW_EDI = edi;
#if (HOST_CPU_IS_I80386==0)
	SET_FLAGS_OSZAPC_8(op1,op2,diff,BX_INSTR_CMPS8);
#endif //#if (HOST_CPU_IS_I80386==0)
#if (HOST_CPU_IS_I80386==1)
	Bit32u x86_lf_flags;
	__asm
	{
		mov dl,op2
		cmp op1,dl
		lahf
		seto al
		mov x86_lf_flags,eax
	}
	BX_CPU_CLASS_PTR eflags.x86.eax = x86_lf_flags;
#endif //#if (HOST_CPU_IS_I80386==1)
}

	void
BX_CPU_C::CMPSB_XbYb_E32_repf2(BX_CPU_C *icpu,bxInstruction_c *i)
{
	unsigned seg;
	Bit8u op1,op2,diff;
	seg = MODRMSeg(i);

	//++++++++++++++++++++++++++++++++
	//ECX等于零时退出,否则执行
	if (RW_ECX==0)
		return;

RepeatRun:

	Bit32u esi,edi;
	esi = RW_ESI;
	edi = RW_EDI;
	READ_VIRTUAL_BYTE(seg, esi, &op1);
	READ_VIRTUAL_BYTE(BX_SEG_REG_ES, edi, &op2);
	diff = op1 - op2;
	if (BX_CPU_CLASS_PTR get_DF())
	{
		esi -= 1;
		edi -= 1;
	}
	else
	{
		esi += 1;
		edi += 1;
	}
	RW_ESI = esi;
	RW_EDI = edi;
	RW_ECX--;
	//原与目标相等||ECX==0 时退出,否则重复执行
	if (diff==0||RW_ECX==0)
	{
#if (HOST_CPU_IS_I80386==0)
	SET_FLAGS_OSZAPC_8(op1,op2,diff,BX_INSTR_CMPS8);
#endif //#if (HOST_CPU_IS_I80386==0)
#if (HOST_CPU_IS_I80386==1)
	Bit32u x86_lf_flags;
	__asm
	{
		mov dl,op2
		cmp op1,dl
		lahf
		seto al
		mov x86_lf_flags,eax
	}
	BX_CPU_CLASS_PTR eflags.x86.eax = x86_lf_flags;
#endif //#if (HOST_CPU_IS_I80386==1)
		return;
	}

	if (BX_CPU_CLASS_PTR async_event)
	{
		BX_CPU_CLASS_PTR invalidate_prefetch_q();
		RW_EIP	= BX_CPU_CLASS_PTR prev_eip; // commit old EIP
		return;
	}

	goto RepeatRun;
}

	void
BX_CPU_C::CMPSB_XbYb_E32_repf3(BX_CPU_C *icpu,bxInstruction_c *i)
{
	unsigned seg;
	Bit8u op1,op2,diff;
	seg = MODRMSeg(i);

	//++++++++++++++++++++++++++++++++
	//ECX等于零时退出,否则执行
	if (RW_ECX==0)
		return;

RepeatRun:

	Bit32u esi,edi;
	esi = RW_ESI;
	edi = RW_EDI;
	READ_VIRTUAL_BYTE(seg, esi, &op1);
	READ_VIRTUAL_BYTE(BX_SEG_REG_ES, edi, &op2);
	diff = op1 - op2;
	if (BX_CPU_CLASS_PTR get_DF())
	{
		esi -= 1;
		edi -= 1;
	}
	else
	{
		esi += 1;
		edi += 1;
	}
	RW_ESI = esi;
	RW_EDI = edi;
	RW_ECX--;
	//原与目标不相等||ECX==0 时退出,否则重复执行
	if (diff!=0||RW_ECX==0)
	{
#if (HOST_CPU_IS_I80386==0)
	SET_FLAGS_OSZAPC_8(op1,op2,diff,BX_INSTR_CMPS8);
#endif //#if (HOST_CPU_IS_I80386==0)
#if (HOST_CPU_IS_I80386==1)
	Bit32u x86_lf_flags;
	__asm
	{
		mov dl,op2
		cmp op1,dl
		lahf
		seto al
		mov x86_lf_flags,eax
	}
	BX_CPU_CLASS_PTR eflags.x86.eax = x86_lf_flags;
#endif //#if (HOST_CPU_IS_I80386==1)
		return;
	}

	if (BX_CPU_CLASS_PTR async_event)
	{
		BX_CPU_CLASS_PTR invalidate_prefetch_q();
		RW_EIP	= BX_CPU_CLASS_PTR prev_eip; // commit old EIP
		return;
	}

	goto RepeatRun;
}

	void
BX_CPU_C::CMPSW_XvYv_E16_rep__(BX_CPU_C *icpu,bxInstruction_c *i)
{
	unsigned seg;
	Bit16u op1,op2,diff;
	seg = MODRMSeg(i);

	Bit32u esi,edi;
	esi = RW_SI;
	edi = RW_DI;
	READ_VIRTUAL_WORD(seg, esi, &op1);
	READ_VIRTUAL_WORD(BX_SEG_REG_ES, edi, &op2);
	diff = op1 - op2;
	if (BX_CPU_CLASS_PTR get_DF())
	{
		esi -= 2;
		edi -= 2;
	}
	else
	{
		esi += 2;
		edi += 2;
	}
	RW_SI = esi;
	RW_DI = edi;
#if (HOST_CPU_IS_I80386==0)
	SET_FLAGS_OSZAPC_16(op1,op2,diff,BX_INSTR_CMPS16);
#endif //#if (HOST_CPU_IS_I80386==0)
#if (HOST_CPU_IS_I80386==1)
	Bit32u x86_lf_flags;
	__asm
	{
		mov dx,op2
		cmp op1,dx
		lahf
		seto al
		mov x86_lf_flags,eax
	}
	BX_CPU_CLASS_PTR eflags.x86.eax = x86_lf_flags;
#endif //#if (HOST_CPU_IS_I80386==1)
}

	void
BX_CPU_C::CMPSW_XvYv_E16_repf2(BX_CPU_C *icpu,bxInstruction_c *i)
{
	unsigned seg;
	Bit16u op1,op2,diff;
	seg = MODRMSeg(i);

	//++++++++++++++++++++++++++++++++
	//ECX等于零时退出,否则执行
	if (RW_CX==0)
		return;

RepeatRun:

	Bit32u esi,edi;
	esi = RW_SI;
	edi = RW_DI;
	READ_VIRTUAL_WORD(seg, esi, &op1);
	READ_VIRTUAL_WORD(BX_SEG_REG_ES, edi, &op2);
	diff = op1 - op2;
	if (BX_CPU_CLASS_PTR get_DF())
	{
		esi -= 2;
		edi -= 2;
	}
	else
	{
		esi += 2;
		edi += 2;
	}
	RW_SI = esi;
	RW_DI = edi;
	RW_CX--;
	//原与目标相等||ECX==0 时退出,否则重复执行
	if (diff==0||RW_CX==0)
	{
#if (HOST_CPU_IS_I80386==0)
	SET_FLAGS_OSZAPC_16(op1,op2,diff,BX_INSTR_CMPS16);
#endif //#if (HOST_CPU_IS_I80386==0)
#if (HOST_CPU_IS_I80386==1)
	Bit32u x86_lf_flags;
	__asm
	{
		mov dx,op2
		cmp op1,dx
		lahf
		seto al
		mov x86_lf_flags,eax
	}
	BX_CPU_CLASS_PTR eflags.x86.eax = x86_lf_flags;
#endif //#if (HOST_CPU_IS_I80386==1)
		return;
	}

	if (BX_CPU_CLASS_PTR async_event)
	{
		BX_CPU_CLASS_PTR invalidate_prefetch_q();
		RW_EIP	= BX_CPU_CLASS_PTR prev_eip; // commit old EIP
		return;
	}

	goto RepeatRun;
}

	void
BX_CPU_C::CMPSW_XvYv_E16_repf3(BX_CPU_C *icpu,bxInstruction_c *i)
{
	unsigned seg;
	Bit16u op1,op2,diff;
	seg = MODRMSeg(i);

	//++++++++++++++++++++++++++++++++
	//ECX等于零时退出,否则执行
	if (RW_CX==0)
		return;

RepeatRun:

	Bit32u esi,edi;
	esi = RW_SI;
	edi = RW_DI;
	READ_VIRTUAL_WORD(seg, esi, &op1);
	READ_VIRTUAL_WORD(BX_SEG_REG_ES, edi, &op2);
	diff = op1 - op2;
	if (BX_CPU_CLASS_PTR get_DF())
	{
		esi -= 2;
		edi -= 2;
	}
	else
	{
		esi += 2;
		edi += 2;
	}
	RW_SI = esi;
	RW_DI = edi;
	RW_CX--;
	//原与目标不相等||ECX==0 时退出,否则重复执行
	if (diff!=0||RW_CX==0)
	{
#if (HOST_CPU_IS_I80386==0)
	SET_FLAGS_OSZAPC_16(op1,op2,diff,BX_INSTR_CMPS16);
#endif //#if (HOST_CPU_IS_I80386==0)
#if (HOST_CPU_IS_I80386==1)
	Bit32u x86_lf_flags;
	__asm
	{
		mov dx,op2
		cmp op1,dx
		lahf
		seto al
		mov x86_lf_flags,eax
	}
	BX_CPU_CLASS_PTR eflags.x86.eax = x86_lf_flags;
#endif //#if (HOST_CPU_IS_I80386==1)
		return;
	}

	if (BX_CPU_CLASS_PTR async_event)
	{
		BX_CPU_CLASS_PTR invalidate_prefetch_q();
		RW_EIP	= BX_CPU_CLASS_PTR prev_eip; // commit old EIP
		return;
	}

	goto RepeatRun;
}

	void
BX_CPU_C::CMPSW_XvYv_E32_rep__(BX_CPU_C *icpu,bxInstruction_c *i)
{
	unsigned seg;
	Bit16u op1,op2,diff;
	seg = MODRMSeg(i);

	Bit32u esi,edi;
	esi = RW_ESI;
	edi = RW_EDI;
	READ_VIRTUAL_WORD(seg, esi, &op1);
	READ_VIRTUAL_WORD(BX_SEG_REG_ES, edi, &op2);
	diff = op1 - op2;
	if (BX_CPU_CLASS_PTR get_DF())
	{
		esi -= 2;
		edi -= 2;
	}
	else
	{
		esi += 2;
		edi += 2;
	}
	RW_ESI = esi;
	RW_EDI = edi;
#if (HOST_CPU_IS_I80386==0)
	SET_FLAGS_OSZAPC_16(op1,op2,diff,BX_INSTR_CMPS16);
#endif //#if (HOST_CPU_IS_I80386==0)
#if (HOST_CPU_IS_I80386==1)
	Bit32u x86_lf_flags;
	__asm
	{
		mov dx,op2
		cmp op1,dx
		lahf
		seto al
		mov x86_lf_flags,eax
	}
	BX_CPU_CLASS_PTR eflags.x86.eax = x86_lf_flags;
#endif //#if (HOST_CPU_IS_I80386==1)
}

	void
BX_CPU_C::CMPSW_XvYv_E32_repf2(BX_CPU_C *icpu,bxInstruction_c *i)
{
	unsigned seg;
	Bit16u op1,op2,diff;
	seg = MODRMSeg(i);

	//++++++++++++++++++++++++++++++++
	//ECX等于零时退出,否则执行
	if (RW_ECX==0)
		return;

RepeatRun:

	Bit32u esi,edi;
	esi = RW_ESI;
	edi = RW_EDI;
	READ_VIRTUAL_WORD(seg, esi, &op1);
	READ_VIRTUAL_WORD(BX_SEG_REG_ES, edi, &op2);
	diff = op1 - op2;
	if (BX_CPU_CLASS_PTR get_DF())
	{
		esi -= 2;
		edi -= 2;
	}
	else
	{
		esi += 2;
		edi += 2;
	}
	RW_ESI = esi;
	RW_EDI = edi;
	RW_ECX--;
	//原与目标相等||ECX==0 时退出,否则重复执行
	if (diff==0||RW_ECX==0)
	{
#if (HOST_CPU_IS_I80386==0)
	SET_FLAGS_OSZAPC_16(op1,op2,diff,BX_INSTR_CMPS16);
#endif //#if (HOST_CPU_IS_I80386==0)
#if (HOST_CPU_IS_I80386==1)
	Bit32u x86_lf_flags;
	__asm
	{
		mov dx,op2
		cmp op1,dx
		lahf
		seto al
		mov x86_lf_flags,eax
	}
	BX_CPU_CLASS_PTR eflags.x86.eax = x86_lf_flags;
#endif //#if (HOST_CPU_IS_I80386==1)
		return;
	}

	if (BX_CPU_CLASS_PTR async_event)
	{
		BX_CPU_CLASS_PTR invalidate_prefetch_q();
		RW_EIP	= BX_CPU_CLASS_PTR prev_eip; // commit old EIP
		return;
	}

	goto RepeatRun;
}

	void
BX_CPU_C::CMPSW_XvYv_E32_repf3(BX_CPU_C *icpu,bxInstruction_c *i)
{
	unsigned seg;
	Bit16u op1,op2,diff;
	seg = MODRMSeg(i);

	//++++++++++++++++++++++++++++++++
	//ECX等于零时退出,否则执行
	if (RW_ECX==0)
		return;

RepeatRun:

	Bit32u esi,edi;
	esi = RW_ESI;
	edi = RW_EDI;
	READ_VIRTUAL_WORD(seg, esi, &op1);
	READ_VIRTUAL_WORD(BX_SEG_REG_ES, edi, &op2);
	diff = op1 - op2;
	if (BX_CPU_CLASS_PTR get_DF())
	{
		esi -= 2;
		edi -= 2;
	}
	else
	{
		esi += 2;
		edi += 2;
	}
	RW_ESI = esi;
	RW_EDI = edi;
	RW_ECX--;
	//原与目标不相等||ECX==0 时退出,否则重复执行
	if (diff!=0||RW_ECX==0)
	{
#if (HOST_CPU_IS_I80386==0)
	SET_FLAGS_OSZAPC_16(op1,op2,diff,BX_INSTR_CMPS16);
#endif //#if (HOST_CPU_IS_I80386==0)
#if (HOST_CPU_IS_I80386==1)
	Bit32u x86_lf_flags;
	__asm
	{
		mov dx,op2
		cmp op1,dx
		lahf
		seto al
		mov x86_lf_flags,eax
	}
	BX_CPU_CLASS_PTR eflags.x86.eax = x86_lf_flags;
#endif //#if (HOST_CPU_IS_I80386==1)
		return;
	}

	if (BX_CPU_CLASS_PTR async_event)
	{
		BX_CPU_CLASS_PTR invalidate_prefetch_q();
		RW_EIP	= BX_CPU_CLASS_PTR prev_eip; // commit old EIP
		return;
	}

	goto RepeatRun;
}

	void
BX_CPU_C::CMPSD_XvYv_E16_rep__(BX_CPU_C *icpu,bxInstruction_c *i)
{
	unsigned seg;
	Bit32u op1,op2,diff;
	seg = MODRMSeg(i);

	Bit32u esi,edi;
	esi = RW_SI;
	edi = RW_DI;
	READ_VIRTUAL_DWORD(seg, esi, &op1);
	READ_VIRTUAL_DWORD(BX_SEG_REG_ES, edi, &op2);
	diff = op1 - op2;
	if (BX_CPU_CLASS_PTR get_DF())
	{
		esi -= 4;
		edi -= 4;
	}
	else
	{
		esi += 4;
		edi += 4;
	}
	RW_SI = esi;
	RW_DI = edi;
#if (HOST_CPU_IS_I80386==0)
	SET_FLAGS_OSZAPC_32(op1,op2,diff,BX_INSTR_CMPS32);
#endif //#if (HOST_CPU_IS_I80386==0)
#if (HOST_CPU_IS_I80386==1)
	Bit32u x86_lf_flags;
	__asm
	{
		mov edx,op2
		cmp op1,edx
		lahf
		seto al
		mov x86_lf_flags,eax
	}
	BX_CPU_CLASS_PTR eflags.x86.eax = x86_lf_flags;
#endif //#if (HOST_CPU_IS_I80386==1)
}

	void
BX_CPU_C::CMPSD_XvYv_E16_repf2(BX_CPU_C *icpu,bxInstruction_c *i)
{
	unsigned seg;
	Bit32u op1,op2,diff;
	seg = MODRMSeg(i);

	//++++++++++++++++++++++++++++++++
	//ECX等于零时退出,否则执行
	if (RW_CX==0)
		return;

RepeatRun:

	Bit32u esi,edi;
	esi = RW_SI;
	edi = RW_DI;
	READ_VIRTUAL_DWORD(seg, esi, &op1);
	READ_VIRTUAL_DWORD(BX_SEG_REG_ES, edi, &op2);
	diff = op1 - op2;
	if (BX_CPU_CLASS_PTR get_DF())
	{
		esi -= 4;
		edi -= 4;
	}
	else
	{
		esi += 4;
		edi += 4;
	}
	RW_SI = esi;
	RW_DI = edi;
	RW_CX--;
	//原与目标相等||ECX==0 时退出,否则重复执行
	if (diff==0||RW_CX==0)
	{
#if (HOST_CPU_IS_I80386==0)
	SET_FLAGS_OSZAPC_32(op1,op2,diff,BX_INSTR_CMPS32);
#endif //#if (HOST_CPU_IS_I80386==0)
#if (HOST_CPU_IS_I80386==1)
	Bit32u x86_lf_flags;
	__asm
	{
		mov edx,op2
		cmp op1,edx
		lahf
		seto al
		mov x86_lf_flags,eax
	}
	BX_CPU_CLASS_PTR eflags.x86.eax = x86_lf_flags;
#endif //#if (HOST_CPU_IS_I80386==1)
		return;
	}

	if (BX_CPU_CLASS_PTR async_event)
	{
		BX_CPU_CLASS_PTR invalidate_prefetch_q();
		RW_EIP	= BX_CPU_CLASS_PTR prev_eip; // commit old EIP
		return;
	}

	goto RepeatRun;
}

	void
BX_CPU_C::CMPSD_XvYv_E16_repf3(BX_CPU_C *icpu,bxInstruction_c *i)
{
	unsigned seg;
	Bit32u op1,op2,diff;
	seg = MODRMSeg(i);

	//++++++++++++++++++++++++++++++++
	//ECX等于零时退出,否则执行
	if (RW_CX==0)
		return;

RepeatRun:

	Bit32u esi,edi;
	esi = RW_SI;
	edi = RW_DI;
	READ_VIRTUAL_DWORD(seg, esi, &op1);
	READ_VIRTUAL_DWORD(BX_SEG_REG_ES, edi, &op2);
	diff = op1 - op2;
	if (BX_CPU_CLASS_PTR get_DF())
	{
		esi -= 4;
		edi -= 4;
	}
	else
	{
		esi += 4;
		edi += 4;
	}
	RW_SI = esi;
	RW_DI = edi;
	RW_CX--;
	//原与目标不相等||ECX==0 时退出,否则重复执行
	if (diff!=0||RW_CX==0)
	{
#if (HOST_CPU_IS_I80386==0)
	SET_FLAGS_OSZAPC_32(op1,op2,diff,BX_INSTR_CMPS32);
#endif //#if (HOST_CPU_IS_I80386==0)
#if (HOST_CPU_IS_I80386==1)
	Bit32u x86_lf_flags;
	__asm
	{
		mov edx,op2
		cmp op1,edx
		lahf
		seto al
		mov x86_lf_flags,eax
	}
	BX_CPU_CLASS_PTR eflags.x86.eax = x86_lf_flags;
#endif //#if (HOST_CPU_IS_I80386==1)
		return;
	}

	if (BX_CPU_CLASS_PTR async_event)
	{
		BX_CPU_CLASS_PTR invalidate_prefetch_q();
		RW_EIP	= BX_CPU_CLASS_PTR prev_eip; // commit old EIP
		return;
	}

	goto RepeatRun;
}

	void
BX_CPU_C::CMPSD_XvYv_E32_rep__(BX_CPU_C *icpu,bxInstruction_c *i)
{
	unsigned seg;
	Bit32u op1,op2,diff;
	seg = MODRMSeg(i);

	Bit32u esi,edi;
	esi = RW_ESI;
	edi = RW_EDI;
	READ_VIRTUAL_DWORD(seg, esi, &op1);
	READ_VIRTUAL_DWORD(BX_SEG_REG_ES, edi, &op2);
	diff = op1 - op2;
	if (BX_CPU_CLASS_PTR get_DF())
	{
		esi -= 4;
		edi -= 4;
	}
	else
	{
		esi += 4;
		edi += 4;
	}
	RW_ESI = esi;
	RW_EDI = edi;
#if (HOST_CPU_IS_I80386==0)
	SET_FLAGS_OSZAPC_32(op1,op2,diff,BX_INSTR_CMPS32);
#endif //#if (HOST_CPU_IS_I80386==0)
#if (HOST_CPU_IS_I80386==1)
	Bit32u x86_lf_flags;
	__asm
	{
		mov edx,op2
		cmp op1,edx
		lahf
		seto al
		mov x86_lf_flags,eax
	}
	BX_CPU_CLASS_PTR eflags.x86.eax = x86_lf_flags;
#endif //#if (HOST_CPU_IS_I80386==1)
}

	void
BX_CPU_C::CMPSD_XvYv_E32_repf2(BX_CPU_C *icpu,bxInstruction_c *i)
{
	unsigned seg;
	Bit32u op1,op2,diff;
	seg = MODRMSeg(i);

	//++++++++++++++++++++++++++++++++
	//ECX等于零时退出,否则执行
	if (RW_ECX==0)
		return;

RepeatRun:

	Bit32u esi,edi;
	esi = RW_ESI;
	edi = RW_EDI;
	READ_VIRTUAL_DWORD(seg, esi, &op1);
	READ_VIRTUAL_DWORD(BX_SEG_REG_ES, edi, &op2);
	diff = op1 - op2;
	if (BX_CPU_CLASS_PTR get_DF())
	{
		esi -= 4;
		edi -= 4;
	}
	else
	{
		esi += 4;
		edi += 4;
	}
	RW_ESI = esi;
	RW_EDI = edi;
	RW_ECX--;
	//原与目标相等||ECX==0 时退出,否则重复执行
	if (diff==0||RW_ECX==0)
	{
#if (HOST_CPU_IS_I80386==0)
	SET_FLAGS_OSZAPC_32(op1,op2,diff,BX_INSTR_CMPS32);
#endif //#if (HOST_CPU_IS_I80386==0)
#if (HOST_CPU_IS_I80386==1)
	Bit32u x86_lf_flags;
	__asm
	{
		mov edx,op2
		cmp op1,edx
		lahf
		seto al
		mov x86_lf_flags,eax
	}
	BX_CPU_CLASS_PTR eflags.x86.eax = x86_lf_flags;
#endif //#if (HOST_CPU_IS_I80386==1)
		return;
	}

	if (BX_CPU_CLASS_PTR async_event)
	{
		BX_CPU_CLASS_PTR invalidate_prefetch_q();
		RW_EIP	= BX_CPU_CLASS_PTR prev_eip; // commit old EIP
		return;
	}

	goto RepeatRun;
}

	void
BX_CPU_C::CMPSD_XvYv_E32_repf3(BX_CPU_C *icpu,bxInstruction_c *i)
{
	unsigned seg;
	Bit32u op1,op2,diff;
	seg = MODRMSeg(i);

	//++++++++++++++++++++++++++++++++
	//ECX等于零时退出,否则执行
	if (RW_ECX==0)
		return;

RepeatRun:

	Bit32u esi,edi;
	esi = RW_ESI;
	edi = RW_EDI;
	READ_VIRTUAL_DWORD(seg, esi, &op1);
	READ_VIRTUAL_DWORD(BX_SEG_REG_ES, edi, &op2);
	diff = op1 - op2;
	if (BX_CPU_CLASS_PTR get_DF())
	{
		esi -= 4;
		edi -= 4;
	}
	else
	{
		esi += 4;
		edi += 4;
	}
	RW_ESI = esi;
	RW_EDI = edi;
	RW_ECX--;
	//原与目标不相等||ECX==0 时退出,否则重复执行
	if (diff!=0||RW_ECX==0)
	{
#if (HOST_CPU_IS_I80386==0)
	SET_FLAGS_OSZAPC_32(op1,op2,diff,BX_INSTR_CMPS32);
#endif //#if (HOST_CPU_IS_I80386==0)
#if (HOST_CPU_IS_I80386==1)
	Bit32u x86_lf_flags;
	__asm
	{
		mov edx,op2
		cmp op1,edx
		lahf
		seto al
		mov x86_lf_flags,eax
	}
	BX_CPU_CLASS_PTR eflags.x86.eax = x86_lf_flags;
#endif //#if (HOST_CPU_IS_I80386==1)
		return;
	}

	if (BX_CPU_CLASS_PTR async_event)
	{
		BX_CPU_CLASS_PTR invalidate_prefetch_q();
		RW_EIP	= BX_CPU_CLASS_PTR prev_eip; // commit old EIP
		return;
	}

	goto RepeatRun;
}

	void
BX_CPU_C::SCASB_ALYb_E16_rep__ (BX_CPU_C *icpu,bxInstruction_c *i)
{
	Bit8u op1,op2,diff;
	Bit32u edi;
	edi = RW_DI;
	op1 = READ_VIRTUAL_8BIT_REG(0);
	READ_VIRTUAL_BYTE(BX_SEG_REG_ES, edi, &op2);
	diff = op1 - op2;
	if (BX_CPU_CLASS_PTR get_DF())
	{
		edi -= 1;
	}
	else
	{
		edi += 1;
	}
	RW_DI = edi;
#if (HOST_CPU_IS_I80386==0)
	SET_FLAGS_OSZAPC_8(op1,op2,diff,BX_INSTR_SCAS8);
#endif //#if (HOST_CPU_IS_I80386==0)
#if (HOST_CPU_IS_I80386==1)
	Bit32u x86_lf_flags;
	__asm
	{
		mov dl,op2
		cmp op1,dl
		lahf
		seto al
		mov x86_lf_flags,eax
	}
	BX_CPU_CLASS_PTR eflags.x86.eax = x86_lf_flags;
#endif //#if (HOST_CPU_IS_I80386==1)
}

	void
BX_CPU_C::SCASB_ALYb_E16_repf2 (BX_CPU_C *icpu,bxInstruction_c *i)
{
	Bit8u op1,op2,diff;
	//++++++++++++++++++++++++++++++++
	//ECX等于零时退出,否则执行
	if (RW_CX==0)
		return;

RepeatRun:

	Bit32u edi;
	edi = RW_DI;
	op1 = READ_VIRTUAL_8BIT_REG(0);
	READ_VIRTUAL_BYTE(BX_SEG_REG_ES, edi, &op2);
	diff = op1 - op2;
	if (BX_CPU_CLASS_PTR get_DF())
	{
		edi -= 1;
	}
	else
	{
		edi += 1;
	}
	RW_DI = edi;
	RW_CX--;
	//原与目标相等||ECX==0 时退出,否则重复执行
	if (diff==0||RW_CX==0)
	{
#if (HOST_CPU_IS_I80386==0)
	SET_FLAGS_OSZAPC_8(op1,op2,diff,BX_INSTR_SCAS8);
#endif //#if (HOST_CPU_IS_I80386==0)
#if (HOST_CPU_IS_I80386==1)
	Bit32u x86_lf_flags;
	__asm
	{
		mov dl,op2
		cmp op1,dl
		lahf
		seto al
		mov x86_lf_flags,eax
	}
	BX_CPU_CLASS_PTR eflags.x86.eax = x86_lf_flags;
#endif //#if (HOST_CPU_IS_I80386==1)
		return;
	}

	if (BX_CPU_CLASS_PTR async_event)
	{
		BX_CPU_CLASS_PTR invalidate_prefetch_q();
		RW_EIP	= BX_CPU_CLASS_PTR prev_eip; // commit old EIP
		return;
	}

	goto RepeatRun;
}

	void
BX_CPU_C::SCASB_ALYb_E16_repf3 (BX_CPU_C *icpu,bxInstruction_c *i)
{
	Bit8u op1,op2,diff;
	//++++++++++++++++++++++++++++++++
	//ECX等于零时退出,否则执行
	if (RW_CX==0)
		return;

RepeatRun:

	Bit32u edi;
	edi = RW_DI;
	op1 = READ_VIRTUAL_8BIT_REG(0);
	READ_VIRTUAL_BYTE(BX_SEG_REG_ES, edi, &op2);
	diff = op1 - op2;
	if (BX_CPU_CLASS_PTR get_DF())
	{
		edi -= 1;
	}
	else
	{
		edi += 1;
	}
	RW_DI = edi;
	RW_CX--;
	//原与目标不相等||ECX==0 时退出,否则重复执行
	if (diff!=0||RW_CX==0)
	{
#if (HOST_CPU_IS_I80386==0)
	SET_FLAGS_OSZAPC_8(op1,op2,diff,BX_INSTR_SCAS8);
#endif //#if (HOST_CPU_IS_I80386==0)
#if (HOST_CPU_IS_I80386==1)
	Bit32u x86_lf_flags;
	__asm
	{
		mov dl,op2
		cmp op1,dl
		lahf
		seto al
		mov x86_lf_flags,eax
	}
	BX_CPU_CLASS_PTR eflags.x86.eax = x86_lf_flags;
#endif //#if (HOST_CPU_IS_I80386==1)
		return;
	}

	if (BX_CPU_CLASS_PTR async_event)
	{
		BX_CPU_CLASS_PTR invalidate_prefetch_q();
		RW_EIP	= BX_CPU_CLASS_PTR prev_eip; // commit old EIP
		return;
	}

	goto RepeatRun;
}

	void
BX_CPU_C::SCASB_ALYb_E32_rep__ (BX_CPU_C *icpu,bxInstruction_c *i)
{
	Bit8u op1,op2,diff;
	Bit32u edi;
	edi = RW_EDI;
	op1 = READ_VIRTUAL_8BIT_REG(0);
	READ_VIRTUAL_BYTE(BX_SEG_REG_ES, edi, &op2);
	diff = op1 - op2;
	if (BX_CPU_CLASS_PTR get_DF())
	{
		edi -= 1;
	}
	else
	{
		edi += 1;
	}
	RW_EDI = edi;
#if (HOST_CPU_IS_I80386==0)
	SET_FLAGS_OSZAPC_8(op1,op2,diff,BX_INSTR_SCAS8);
#endif //#if (HOST_CPU_IS_I80386==0)
#if (HOST_CPU_IS_I80386==1)
	Bit32u x86_lf_flags;
	__asm
	{
		mov dl,op2
		cmp op1,dl
		lahf
		seto al
		mov x86_lf_flags,eax
	}
	BX_CPU_CLASS_PTR eflags.x86.eax = x86_lf_flags;
#endif //#if (HOST_CPU_IS_I80386==1)
}

	void
BX_CPU_C::SCASB_ALYb_E32_repf2 (BX_CPU_C *icpu,bxInstruction_c *i)
{
	Bit8u op1,op2,diff;
	//++++++++++++++++++++++++++++++++
	//ECX等于零时退出,否则执行
	if (RW_ECX==0)
		return;

RepeatRun:

	Bit32u edi;
	edi = RW_EDI;
	op1 = READ_VIRTUAL_8BIT_REG(0);
	READ_VIRTUAL_BYTE(BX_SEG_REG_ES, edi, &op2);
	diff = op1 - op2;
	if (BX_CPU_CLASS_PTR get_DF())
	{
		edi -= 1;
	}
	else
	{
		edi += 1;
	}
	RW_EDI = edi;
	RW_ECX--;
	//原与目标相等||ECX==0 时退出,否则重复执行
	if (diff==0||RW_ECX==0)
	{
#if (HOST_CPU_IS_I80386==0)
	SET_FLAGS_OSZAPC_8(op1,op2,diff,BX_INSTR_SCAS8);
#endif //#if (HOST_CPU_IS_I80386==0)
#if (HOST_CPU_IS_I80386==1)
	Bit32u x86_lf_flags;
	__asm
	{
		mov dl,op2
		cmp op1,dl
		lahf
		seto al
		mov x86_lf_flags,eax
	}
	BX_CPU_CLASS_PTR eflags.x86.eax = x86_lf_flags;
#endif //#if (HOST_CPU_IS_I80386==1)
		return;
	}

	if (BX_CPU_CLASS_PTR async_event)
	{
		BX_CPU_CLASS_PTR invalidate_prefetch_q();
		RW_EIP	= BX_CPU_CLASS_PTR prev_eip; // commit old EIP
		return;
	}

	goto RepeatRun;
}

	void
BX_CPU_C::SCASB_ALYb_E32_repf3 (BX_CPU_C *icpu,bxInstruction_c *i)
{
	Bit8u op1,op2,diff;
	//++++++++++++++++++++++++++++++++
	//ECX等于零时退出,否则执行
	if (RW_ECX==0)
		return;

RepeatRun:

	Bit32u edi;
	edi = RW_EDI;
	op1 = READ_VIRTUAL_8BIT_REG(0);
	READ_VIRTUAL_BYTE(BX_SEG_REG_ES, edi, &op2);
	diff = op1 - op2;
	if (BX_CPU_CLASS_PTR get_DF())
	{
		edi -= 1;
	}
	else
	{
		edi += 1;
	}
	RW_EDI = edi;
	RW_ECX--;
	//原与目标不相等||ECX==0 时退出,否则重复执行
	if (diff!=0||RW_ECX==0)
	{
#if (HOST_CPU_IS_I80386==0)
	SET_FLAGS_OSZAPC_8(op1,op2,diff,BX_INSTR_SCAS8);
#endif //#if (HOST_CPU_IS_I80386==0)
#if (HOST_CPU_IS_I80386==1)
	Bit32u x86_lf_flags;
	__asm
	{
		mov dl,op2
		cmp op1,dl
		lahf
		seto al
		mov x86_lf_flags,eax
	}
	BX_CPU_CLASS_PTR eflags.x86.eax = x86_lf_flags;
#endif //#if (HOST_CPU_IS_I80386==1)
		return;
	}

	if (BX_CPU_CLASS_PTR async_event)
	{
		BX_CPU_CLASS_PTR invalidate_prefetch_q();
		RW_EIP	= BX_CPU_CLASS_PTR prev_eip; // commit old EIP
		return;
	}

	goto RepeatRun;
}

	void
BX_CPU_C::SCASW_eAXYv_E16_rep__(BX_CPU_C *icpu,bxInstruction_c *i)
{
	Bit16u op1,op2,diff;
	Bit32u edi;
	edi = RW_DI;
	op1 = READ_VIRTUAL_16BIT_REG(0);
	READ_VIRTUAL_WORD(BX_SEG_REG_ES, edi, &op2);
	diff = op1 - op2;
	if (BX_CPU_CLASS_PTR get_DF())
	{
		edi -= 2;
	}
	else
	{
		edi += 2;
	}
	RW_DI = edi;
#if (HOST_CPU_IS_I80386==0)
	SET_FLAGS_OSZAPC_16(op1,op2,diff,BX_INSTR_SCAS16);
#endif //#if (HOST_CPU_IS_I80386==0)
#if (HOST_CPU_IS_I80386==1)
	Bit32u x86_lf_flags;
	__asm
	{
		mov dx,op2
		cmp op1,dx
		lahf
		seto al
		mov x86_lf_flags,eax
	}
	BX_CPU_CLASS_PTR eflags.x86.eax = x86_lf_flags;
#endif //#if (HOST_CPU_IS_I80386==1)
}

	void
BX_CPU_C::SCASW_eAXYv_E16_repf2(BX_CPU_C *icpu,bxInstruction_c *i)
{
	Bit16u op1,op2,diff;
	//++++++++++++++++++++++++++++++++
	//ECX等于零时退出,否则执行
	if (RW_CX==0)
		return;

RepeatRun:

	Bit32u edi;
	edi = RW_DI;
	op1 = READ_VIRTUAL_16BIT_REG(0);
	READ_VIRTUAL_WORD(BX_SEG_REG_ES, edi, &op2);
	diff = op1 - op2;
	if (BX_CPU_CLASS_PTR get_DF())
	{
		edi -= 2;
	}
	else
	{
		edi += 2;
	}
	RW_DI = edi;
	RW_CX--;
	//原与目标相等||ECX==0 时退出,否则重复执行
	if (diff==0||RW_CX==0)
	{
#if (HOST_CPU_IS_I80386==0)
	SET_FLAGS_OSZAPC_16(op1,op2,diff,BX_INSTR_SCAS16);
#endif //#if (HOST_CPU_IS_I80386==0)
#if (HOST_CPU_IS_I80386==1)
	Bit32u x86_lf_flags;
	__asm
	{
		mov dx,op2
		cmp op1,dx
		lahf
		seto al
		mov x86_lf_flags,eax
	}
	BX_CPU_CLASS_PTR eflags.x86.eax = x86_lf_flags;
#endif //#if (HOST_CPU_IS_I80386==1)
		return;
	}

	if (BX_CPU_CLASS_PTR async_event)
	{
		BX_CPU_CLASS_PTR invalidate_prefetch_q();
		RW_EIP	= BX_CPU_CLASS_PTR prev_eip; // commit old EIP
		return;
	}

	goto RepeatRun;
}

	void
BX_CPU_C::SCASW_eAXYv_E16_repf3(BX_CPU_C *icpu,bxInstruction_c *i)
{
	Bit16u op1,op2,diff;
	//++++++++++++++++++++++++++++++++
	//ECX等于零时退出,否则执行
	if (RW_CX==0)
		return;

RepeatRun:

	Bit32u edi;
	edi = RW_DI;
	op1 = READ_VIRTUAL_16BIT_REG(0);
	READ_VIRTUAL_WORD(BX_SEG_REG_ES, edi, &op2);
	diff = op1 - op2;
	if (BX_CPU_CLASS_PTR get_DF())
	{
		edi -= 2;
	}
	else
	{
		edi += 2;
	}
	RW_DI = edi;
	RW_CX--;
	//原与目标不相等||ECX==0 时退出,否则重复执行
	if (diff!=0||RW_CX==0)
	{
#if (HOST_CPU_IS_I80386==0)
	SET_FLAGS_OSZAPC_16(op1,op2,diff,BX_INSTR_SCAS16);
#endif //#if (HOST_CPU_IS_I80386==0)
#if (HOST_CPU_IS_I80386==1)
	Bit32u x86_lf_flags;
	__asm
	{
		mov dx,op2
		cmp op1,dx
		lahf
		seto al
		mov x86_lf_flags,eax
	}
	BX_CPU_CLASS_PTR eflags.x86.eax = x86_lf_flags;
#endif //#if (HOST_CPU_IS_I80386==1)
		return;
	}

	if (BX_CPU_CLASS_PTR async_event)
	{
		BX_CPU_CLASS_PTR invalidate_prefetch_q();
		RW_EIP	= BX_CPU_CLASS_PTR prev_eip; // commit old EIP
		return;
	}

	goto RepeatRun;
}

	void
BX_CPU_C::SCASW_eAXYv_E32_rep__(BX_CPU_C *icpu,bxInstruction_c *i)
{
	Bit16u op1,op2,diff;
	Bit32u edi;
	edi = RW_EDI;
	op1 = READ_VIRTUAL_16BIT_REG(0);
	READ_VIRTUAL_WORD(BX_SEG_REG_ES, edi, &op2);
	diff = op1 - op2;
	if (BX_CPU_CLASS_PTR get_DF())
	{
		edi -= 2;
	}
	else
	{
		edi += 2;
	}
	RW_EDI = edi;
#if (HOST_CPU_IS_I80386==0)
	SET_FLAGS_OSZAPC_16(op1,op2,diff,BX_INSTR_SCAS16);
#endif //#if (HOST_CPU_IS_I80386==0)
#if (HOST_CPU_IS_I80386==1)
	Bit32u x86_lf_flags;
	__asm
	{
		mov dx,op2
		cmp op1,dx
		lahf
		seto al
		mov x86_lf_flags,eax
	}
	BX_CPU_CLASS_PTR eflags.x86.eax = x86_lf_flags;
#endif //#if (HOST_CPU_IS_I80386==1)
}

	void
BX_CPU_C::SCASW_eAXYv_E32_repf2(BX_CPU_C *icpu,bxInstruction_c *i)
{
	Bit16u op1,op2,diff;
	//++++++++++++++++++++++++++++++++
	//ECX等于零时退出,否则执行
	if (RW_ECX==0)
		return;

RepeatRun:

	Bit32u edi;
	edi = RW_EDI;
	op1 = READ_VIRTUAL_16BIT_REG(0);
	READ_VIRTUAL_WORD(BX_SEG_REG_ES, edi, &op2);
	diff = op1 - op2;
	if (BX_CPU_CLASS_PTR get_DF())
	{
		edi -= 2;
	}
	else
	{
		edi += 2;
	}
	RW_EDI = edi;
	RW_ECX--;
	//原与目标相等||ECX==0 时退出,否则重复执行
	if (diff==0||RW_ECX==0)
	{
#if (HOST_CPU_IS_I80386==0)
	SET_FLAGS_OSZAPC_16(op1,op2,diff,BX_INSTR_SCAS16);
#endif //#if (HOST_CPU_IS_I80386==0)
#if (HOST_CPU_IS_I80386==1)
	Bit32u x86_lf_flags;
	__asm
	{
		mov dx,op2
		cmp op1,dx
		lahf
		seto al
		mov x86_lf_flags,eax
	}
	BX_CPU_CLASS_PTR eflags.x86.eax = x86_lf_flags;
#endif //#if (HOST_CPU_IS_I80386==1)
		return;
	}

	if (BX_CPU_CLASS_PTR async_event)
	{
		BX_CPU_CLASS_PTR invalidate_prefetch_q();
		RW_EIP	= BX_CPU_CLASS_PTR prev_eip; // commit old EIP
		return;
	}

	goto RepeatRun;
}

	void
BX_CPU_C::SCASW_eAXYv_E32_repf3(BX_CPU_C *icpu,bxInstruction_c *i)
{
	Bit16u op1,op2,diff;
	//++++++++++++++++++++++++++++++++
	//ECX等于零时退出,否则执行
	if (RW_ECX==0)
		return;

RepeatRun:

	Bit32u edi;
	edi = RW_EDI;
	op1 = READ_VIRTUAL_16BIT_REG(0);
	READ_VIRTUAL_WORD(BX_SEG_REG_ES, edi, &op2);
	diff = op1 - op2;
	if (BX_CPU_CLASS_PTR get_DF())
	{
		edi -= 2;
	}
	else
	{
		edi += 2;
	}
	RW_EDI = edi;
	RW_ECX--;
	//原与目标不相等||ECX==0 时退出,否则重复执行
	if (diff!=0||RW_ECX==0)
	{
#if (HOST_CPU_IS_I80386==0)
	SET_FLAGS_OSZAPC_16(op1,op2,diff,BX_INSTR_SCAS16);
#endif //#if (HOST_CPU_IS_I80386==0)
#if (HOST_CPU_IS_I80386==1)
	Bit32u x86_lf_flags;
	__asm
	{
		mov dx,op2
		cmp op1,dx
		lahf
		seto al
		mov x86_lf_flags,eax
	}
	BX_CPU_CLASS_PTR eflags.x86.eax = x86_lf_flags;
#endif //#if (HOST_CPU_IS_I80386==1)
		return;
	}

	if (BX_CPU_CLASS_PTR async_event)
	{
		BX_CPU_CLASS_PTR invalidate_prefetch_q();
		RW_EIP	= BX_CPU_CLASS_PTR prev_eip; // commit old EIP
		return;
	}

	goto RepeatRun;
}

	void
BX_CPU_C::SCASD_eAXYv_E16_rep__(BX_CPU_C *icpu,bxInstruction_c *i)
{
	Bit32u op1,op2,diff;
	Bit32u edi;
	edi = RW_DI;
	op1 = READ_VIRTUAL_32BIT_REG(0);
	READ_VIRTUAL_DWORD(BX_SEG_REG_ES, edi, &op2);
	diff = op1 - op2;
	if (BX_CPU_CLASS_PTR get_DF())
	{
		edi -= 4;
	}
	else
	{
		edi += 4;
	}
	RW_DI = edi;
#if (HOST_CPU_IS_I80386==0)
	SET_FLAGS_OSZAPC_32(op1,op2,diff,BX_INSTR_SCAS32);
#endif //#if (HOST_CPU_IS_I80386==0)
#if (HOST_CPU_IS_I80386==1)
	Bit32u x86_lf_flags;
	__asm
	{
		mov edx,op2
		cmp op1,edx
		lahf
		seto al
		mov x86_lf_flags,eax
	}
	BX_CPU_CLASS_PTR eflags.x86.eax = x86_lf_flags;
#endif //#if (HOST_CPU_IS_I80386==1)
}

	void
BX_CPU_C::SCASD_eAXYv_E16_repf2(BX_CPU_C *icpu,bxInstruction_c *i)
{
	Bit32u op1,op2,diff;
	//++++++++++++++++++++++++++++++++
	//ECX等于零时退出,否则执行
	if (RW_CX==0)
		return;

RepeatRun:

	Bit32u edi;
	edi = RW_DI;
	op1 = READ_VIRTUAL_32BIT_REG(0);
	READ_VIRTUAL_DWORD(BX_SEG_REG_ES, edi, &op2);
	diff = op1 - op2;
	if (BX_CPU_CLASS_PTR get_DF())
	{
		edi -= 4;
	}
	else
	{
		edi += 4;
	}
	RW_DI = edi;
	RW_CX--;
	//原与目标相等||ECX==0 时退出,否则重复执行
	if (diff==0||RW_CX==0)
	{
#if (HOST_CPU_IS_I80386==0)
	SET_FLAGS_OSZAPC_32(op1,op2,diff,BX_INSTR_SCAS32);
#endif //#if (HOST_CPU_IS_I80386==0)
#if (HOST_CPU_IS_I80386==1)
	Bit32u x86_lf_flags;
	__asm
	{
		mov edx,op2
		cmp op1,edx
		lahf
		seto al
		mov x86_lf_flags,eax
	}
	BX_CPU_CLASS_PTR eflags.x86.eax = x86_lf_flags;
#endif //#if (HOST_CPU_IS_I80386==1)
		return;
	}

	if (BX_CPU_CLASS_PTR async_event)
	{
		BX_CPU_CLASS_PTR invalidate_prefetch_q();
		RW_EIP	= BX_CPU_CLASS_PTR prev_eip; // commit old EIP
		return;
	}

	goto RepeatRun;
}

	void
BX_CPU_C::SCASD_eAXYv_E16_repf3(BX_CPU_C *icpu,bxInstruction_c *i)
{
	Bit32u op1,op2,diff;
	//++++++++++++++++++++++++++++++++
	//ECX等于零时退出,否则执行
	if (RW_CX==0)
		return;

RepeatRun:

	Bit32u edi;
	edi = RW_DI;
	op1 = READ_VIRTUAL_32BIT_REG(0);
	READ_VIRTUAL_DWORD(BX_SEG_REG_ES, edi, &op2);
	diff = op1 - op2;
	if (BX_CPU_CLASS_PTR get_DF())
	{
		edi -= 4;
	}
	else
	{
		edi += 4;
	}
	RW_DI = edi;
	RW_CX--;
	//原与目标不相等||ECX==0 时退出,否则重复执行
	if (diff!=0||RW_CX==0)
	{
#if (HOST_CPU_IS_I80386==0)
	SET_FLAGS_OSZAPC_32(op1,op2,diff,BX_INSTR_SCAS32);
#endif //#if (HOST_CPU_IS_I80386==0)
#if (HOST_CPU_IS_I80386==1)
	Bit32u x86_lf_flags;
	__asm
	{
		mov edx,op2
		cmp op1,edx
		lahf
		seto al
		mov x86_lf_flags,eax
	}
	BX_CPU_CLASS_PTR eflags.x86.eax = x86_lf_flags;
#endif //#if (HOST_CPU_IS_I80386==1)
		return;
	}

	if (BX_CPU_CLASS_PTR async_event)
	{
		BX_CPU_CLASS_PTR invalidate_prefetch_q();
		RW_EIP	= BX_CPU_CLASS_PTR prev_eip; // commit old EIP
		return;
	}

	goto RepeatRun;
}

	void
BX_CPU_C::SCASD_eAXYv_E32_rep__(BX_CPU_C *icpu,bxInstruction_c *i)
{
	Bit32u op1,op2,diff;
	Bit32u edi;
	edi = RW_EDI;
	op1 = READ_VIRTUAL_32BIT_REG(0);
	READ_VIRTUAL_DWORD(BX_SEG_REG_ES, edi, &op2);
	diff = op1 - op2;
	if (BX_CPU_CLASS_PTR get_DF())
	{
		edi -= 4;
	}
	else
	{
		edi += 4;
	}
	RW_EDI = edi;
#if (HOST_CPU_IS_I80386==0)
	SET_FLAGS_OSZAPC_32(op1,op2,diff,BX_INSTR_SCAS32);
#endif //#if (HOST_CPU_IS_I80386==0)
#if (HOST_CPU_IS_I80386==1)
	Bit32u x86_lf_flags;
	__asm
	{
		mov edx,op2
		cmp op1,edx
		lahf
		seto al
		mov x86_lf_flags,eax
	}
	BX_CPU_CLASS_PTR eflags.x86.eax = x86_lf_flags;
#endif //#if (HOST_CPU_IS_I80386==1)
}

	void
BX_CPU_C::SCASD_eAXYv_E32_repf2(BX_CPU_C *icpu,bxInstruction_c *i)
{
	Bit32u op1,op2,diff;
	//++++++++++++++++++++++++++++++++
	//ECX等于零时退出,否则执行
	if (RW_ECX==0)
		return;

RepeatRun:

	Bit32u edi;
	edi = RW_EDI;
	op1 = READ_VIRTUAL_32BIT_REG(0);
	READ_VIRTUAL_DWORD(BX_SEG_REG_ES, edi, &op2);
	diff = op1 - op2;
	if (BX_CPU_CLASS_PTR get_DF())
	{
		edi -= 4;
	}
	else
	{
		edi += 4;
	}
	RW_EDI = edi;
	RW_ECX--;
	//原与目标相等||ECX==0 时退出,否则重复执行
	if (diff==0||RW_ECX==0)
	{
#if (HOST_CPU_IS_I80386==0)
	SET_FLAGS_OSZAPC_32(op1,op2,diff,BX_INSTR_SCAS32);
#endif //#if (HOST_CPU_IS_I80386==0)
#if (HOST_CPU_IS_I80386==1)
	Bit32u x86_lf_flags;
	__asm
	{
		mov edx,op2
		cmp op1,edx
		lahf
		seto al
		mov x86_lf_flags,eax
	}
	BX_CPU_CLASS_PTR eflags.x86.eax = x86_lf_flags;
#endif //#if (HOST_CPU_IS_I80386==1)
		return;
	}

	if (BX_CPU_CLASS_PTR async_event)
	{
		BX_CPU_CLASS_PTR invalidate_prefetch_q();
		RW_EIP	= BX_CPU_CLASS_PTR prev_eip; // commit old EIP
		return;
	}

	goto RepeatRun;
}

	void
BX_CPU_C::SCASD_eAXYv_E32_repf3(BX_CPU_C *icpu,bxInstruction_c *i)
{
	Bit32u op1,op2,diff;
	//++++++++++++++++++++++++++++++++
	//ECX等于零时退出,否则执行
	if (RW_ECX==0)
		return;

RepeatRun:

	Bit32u edi;
	edi = RW_EDI;
	op1 = READ_VIRTUAL_32BIT_REG(0);
	READ_VIRTUAL_DWORD(BX_SEG_REG_ES, edi, &op2);
	diff = op1 - op2;
	if (BX_CPU_CLASS_PTR get_DF())
	{
		edi -= 4;
	}
	else
	{
		edi += 4;
	}
	RW_EDI = edi;
	RW_ECX--;
	//原与目标不相等||ECX==0 时退出,否则重复执行
	if (diff!=0||RW_ECX==0)
	{
#if (HOST_CPU_IS_I80386==0)
	SET_FLAGS_OSZAPC_32(op1,op2,diff,BX_INSTR_SCAS32);
#endif //#if (HOST_CPU_IS_I80386==0)
#if (HOST_CPU_IS_I80386==1)
	Bit32u x86_lf_flags;
	__asm
	{
		mov edx,op2
		cmp op1,edx
		lahf
		seto al
		mov x86_lf_flags,eax
	}
	BX_CPU_CLASS_PTR eflags.x86.eax = x86_lf_flags;
#endif //#if (HOST_CPU_IS_I80386==1)
		return;
	}

	if (BX_CPU_CLASS_PTR async_event)
	{
		BX_CPU_CLASS_PTR invalidate_prefetch_q();
		RW_EIP	= BX_CPU_CLASS_PTR prev_eip; // commit old EIP
		return;
	}

	goto RepeatRun;
}

	void
BX_CPU_C::STOSB_ALYb_E16_rep__ (BX_CPU_C *icpu,bxInstruction_c *i)
{
	Bit8u op1;
	Bit32u edi;
	edi = RW_DI;
	op1 = READ_VIRTUAL_8BIT_REG(0);
	WRITE_VIRTUAL_BYTE(BX_SEG_REG_ES, edi, &op1);
	if (BX_CPU_CLASS_PTR get_DF())
	{
		edi -= 1;
	}
	else
	{
		edi += 1;
	}
	RW_DI = edi;
}

	void
BX_CPU_C::STOSB_ALYb_E16_repf2 (BX_CPU_C *icpu,bxInstruction_c *i)
{
	Bit8u op1;
	//++++++++++++++++++++++++++++++++
	//ECX等于零时退出,否则执行
	if (RW_CX==0)
		return;

RepeatRun:

	Bit32u edi;
	edi = RW_DI;
	op1 = READ_VIRTUAL_8BIT_REG(0);
	WRITE_VIRTUAL_BYTE(BX_SEG_REG_ES, edi, &op1);
	if (BX_CPU_CLASS_PTR get_DF())
	{
		edi -= 1;
	}
	else
	{
		edi += 1;
	}
	RW_DI = edi;
	RW_CX--;
	if (RW_CX==0)
		return;

	if (BX_CPU_CLASS_PTR async_event)
	{
		BX_CPU_CLASS_PTR invalidate_prefetch_q();
		RW_EIP	= BX_CPU_CLASS_PTR prev_eip; // commit old EIP
		return;
	}

	goto RepeatRun;
}

	void
BX_CPU_C::STOSB_ALYb_E16_repf3 (BX_CPU_C *icpu,bxInstruction_c *i)
{
	Bit8u op1;
	//++++++++++++++++++++++++++++++++
	//ECX等于零时退出,否则执行
	if (RW_CX==0)
		return;

RepeatRun:

	Bit32u edi;
	edi = RW_DI;
	op1 = READ_VIRTUAL_8BIT_REG(0);
	WRITE_VIRTUAL_BYTE(BX_SEG_REG_ES, edi, &op1);
	if (BX_CPU_CLASS_PTR get_DF())
	{
		edi -= 1;
	}
	else
	{
		edi += 1;
	}
	RW_DI = edi;
	RW_CX--;
	if (RW_CX==0)
		return;

	if (BX_CPU_CLASS_PTR async_event)
	{
		BX_CPU_CLASS_PTR invalidate_prefetch_q();
		RW_EIP	= BX_CPU_CLASS_PTR prev_eip; // commit old EIP
		return;
	}

	goto RepeatRun;
}

	void
BX_CPU_C::STOSB_ALYb_E32_rep__ (BX_CPU_C *icpu,bxInstruction_c *i)
{
	Bit8u op1;
	Bit32u edi;
	edi = RW_EDI;
	op1 = READ_VIRTUAL_8BIT_REG(0);
	WRITE_VIRTUAL_BYTE(BX_SEG_REG_ES, edi, &op1);
	if (BX_CPU_CLASS_PTR get_DF())
	{
		edi -= 1;
	}
	else
	{
		edi += 1;
	}
	RW_EDI = edi;
}

	void
BX_CPU_C::STOSB_ALYb_E32_repf2 (BX_CPU_C *icpu,bxInstruction_c *i)
{
	Bit8u op1;
	//++++++++++++++++++++++++++++++++
	//ECX等于零时退出,否则执行
	if (RW_ECX==0)
		return;

RepeatRun:

	Bit32u edi;
	edi = RW_EDI;
	op1 = READ_VIRTUAL_8BIT_REG(0);
	WRITE_VIRTUAL_BYTE(BX_SEG_REG_ES, edi, &op1);
	if (BX_CPU_CLASS_PTR get_DF())
	{
		edi -= 1;
	}
	else
	{
		edi += 1;
	}
	RW_EDI = edi;
	RW_ECX--;
	if (RW_ECX==0)
		return;

	if (BX_CPU_CLASS_PTR async_event)
	{
		BX_CPU_CLASS_PTR invalidate_prefetch_q();
		RW_EIP	= BX_CPU_CLASS_PTR prev_eip; // commit old EIP
		return;
	}

	goto RepeatRun;
}

	void
BX_CPU_C::STOSB_ALYb_E32_repf3 (BX_CPU_C *icpu,bxInstruction_c *i)
{
	Bit8u op1;
	//++++++++++++++++++++++++++++++++
	//ECX等于零时退出,否则执行
	if (RW_ECX==0)
		return;

RepeatRun:

	Bit32u edi;
	edi = RW_EDI;
	op1 = READ_VIRTUAL_8BIT_REG(0);
	WRITE_VIRTUAL_BYTE(BX_SEG_REG_ES, edi, &op1);
	if (BX_CPU_CLASS_PTR get_DF())
	{
		edi -= 1;
	}
	else
	{
		edi += 1;
	}
	RW_EDI = edi;
	RW_ECX--;
	if (RW_ECX==0)
		return;

	if (BX_CPU_CLASS_PTR async_event)
	{
		BX_CPU_CLASS_PTR invalidate_prefetch_q();
		RW_EIP	= BX_CPU_CLASS_PTR prev_eip; // commit old EIP
		return;
	}

	goto RepeatRun;
}

	void
BX_CPU_C::STOSW_eAXYv_E16_rep__(BX_CPU_C *icpu,bxInstruction_c *i)
{
	Bit16u op1;
	Bit32u edi;
	edi = RW_DI;
	op1 = READ_VIRTUAL_16BIT_REG(0);
	WRITE_VIRTUAL_WORD(BX_SEG_REG_ES, edi, &op1);
	if (BX_CPU_CLASS_PTR get_DF())
	{
		edi -= 2;
	}
	else
	{
		edi += 2;
	}
	RW_DI = edi;
}

	void
BX_CPU_C::STOSW_eAXYv_E16_repf2(BX_CPU_C *icpu,bxInstruction_c *i)
{
	Bit16u op1;
	//++++++++++++++++++++++++++++++++
	//ECX等于零时退出,否则执行
	if (RW_CX==0)
		return;

RepeatRun:

	Bit32u edi;
	edi = RW_DI;
	op1 = READ_VIRTUAL_16BIT_REG(0);
	WRITE_VIRTUAL_WORD(BX_SEG_REG_ES, edi, &op1);
	if (BX_CPU_CLASS_PTR get_DF())
	{
		edi -= 2;
	}
	else
	{
		edi += 2;
	}
	RW_DI = edi;
	RW_CX--;
	if (RW_CX==0)
		return;

	if (BX_CPU_CLASS_PTR async_event)
	{
		BX_CPU_CLASS_PTR invalidate_prefetch_q();
		RW_EIP	= BX_CPU_CLASS_PTR prev_eip; // commit old EIP
		return;
	}

	goto RepeatRun;
}

	void
BX_CPU_C::STOSW_eAXYv_E16_repf3(BX_CPU_C *icpu,bxInstruction_c *i)
{
	Bit16u op1;
	//++++++++++++++++++++++++++++++++
	//ECX等于零时退出,否则执行
	if (RW_CX==0)
		return;

RepeatRun:

	Bit32u edi;
	edi = RW_DI;
	op1 = READ_VIRTUAL_16BIT_REG(0);
	WRITE_VIRTUAL_WORD(BX_SEG_REG_ES, edi, &op1);
	if (BX_CPU_CLASS_PTR get_DF())
	{
		edi -= 2;
	}
	else
	{
		edi += 2;
	}
	RW_DI = edi;
	RW_CX--;
	if (RW_CX==0)
		return;

	if (BX_CPU_CLASS_PTR async_event)
	{
		BX_CPU_CLASS_PTR invalidate_prefetch_q();
		RW_EIP	= BX_CPU_CLASS_PTR prev_eip; // commit old EIP
		return;
	}

	goto RepeatRun;
}

	void
BX_CPU_C::STOSW_eAXYv_E32_rep__(BX_CPU_C *icpu,bxInstruction_c *i)
{
	Bit16u op1;
	Bit32u edi;
	edi = RW_EDI;
	op1 = READ_VIRTUAL_16BIT_REG(0);
	WRITE_VIRTUAL_WORD(BX_SEG_REG_ES, edi, &op1);
	if (BX_CPU_CLASS_PTR get_DF())
	{
		edi -= 2;
	}
	else
	{
		edi += 2;
	}
	RW_EDI = edi;
}

	void
BX_CPU_C::STOSW_eAXYv_E32_repf2(BX_CPU_C *icpu,bxInstruction_c *i)
{
	Bit16u op1;
	//++++++++++++++++++++++++++++++++
	//ECX等于零时退出,否则执行
	if (RW_ECX==0)
		return;

RepeatRun:

	Bit32u edi;
	edi = RW_EDI;
	op1 = READ_VIRTUAL_16BIT_REG(0);
	WRITE_VIRTUAL_WORD(BX_SEG_REG_ES, edi, &op1);
	if (BX_CPU_CLASS_PTR get_DF())
	{
		edi -= 2;
	}
	else
	{
		edi += 2;
	}
	RW_EDI = edi;
	RW_ECX--;
	if (RW_ECX==0)
		return;

	if (BX_CPU_CLASS_PTR async_event)
	{
		BX_CPU_CLASS_PTR invalidate_prefetch_q();
		RW_EIP	= BX_CPU_CLASS_PTR prev_eip; // commit old EIP
		return;
	}

	goto RepeatRun;
}

	void
BX_CPU_C::STOSW_eAXYv_E32_repf3(BX_CPU_C *icpu,bxInstruction_c *i)
{
	Bit16u op1;
	//++++++++++++++++++++++++++++++++
	//ECX等于零时退出,否则执行
	if (RW_ECX==0)
		return;

RepeatRun:

	Bit32u edi;
	edi = RW_EDI;
	op1 = READ_VIRTUAL_16BIT_REG(0);
	WRITE_VIRTUAL_WORD(BX_SEG_REG_ES, edi, &op1);
	if (BX_CPU_CLASS_PTR get_DF())
	{
		edi -= 2;
	}
	else
	{
		edi += 2;
	}
	RW_EDI = edi;
	RW_ECX--;
	if (RW_ECX==0)
		return;

	if (BX_CPU_CLASS_PTR async_event)
	{
		BX_CPU_CLASS_PTR invalidate_prefetch_q();
		RW_EIP	= BX_CPU_CLASS_PTR prev_eip; // commit old EIP
		return;
	}

	goto RepeatRun;
}

	void
BX_CPU_C::STOSD_eAXYv_E16_rep__(BX_CPU_C *icpu,bxInstruction_c *i)
{
	Bit32u op1;
	Bit32u edi;
	edi = RW_DI;
	op1 = READ_VIRTUAL_32BIT_REG(0);
	WRITE_VIRTUAL_DWORD(BX_SEG_REG_ES, edi, &op1);
	if (BX_CPU_CLASS_PTR get_DF())
	{
		edi -= 4;
	}
	else
	{
		edi += 4;
	}
	RW_DI = edi;
}

	void
BX_CPU_C::STOSD_eAXYv_E16_repf2(BX_CPU_C *icpu,bxInstruction_c *i)
{
	Bit32u op1;
	//++++++++++++++++++++++++++++++++
	//ECX等于零时退出,否则执行
	if (RW_CX==0)
		return;

RepeatRun:

	Bit32u edi;
	edi = RW_DI;
	op1 = READ_VIRTUAL_32BIT_REG(0);
	WRITE_VIRTUAL_DWORD(BX_SEG_REG_ES, edi, &op1);
	if (BX_CPU_CLASS_PTR get_DF())
	{
		edi -= 4;
	}
	else
	{
		edi += 4;
	}
	RW_DI = edi;
	RW_CX--;
	if (RW_CX==0)
		return;

	if (BX_CPU_CLASS_PTR async_event)
	{
		BX_CPU_CLASS_PTR invalidate_prefetch_q();
		RW_EIP	= BX_CPU_CLASS_PTR prev_eip; // commit old EIP
		return;
	}

	goto RepeatRun;
}

	void
BX_CPU_C::STOSD_eAXYv_E16_repf3(BX_CPU_C *icpu,bxInstruction_c *i)
{
	Bit32u op1;
	//++++++++++++++++++++++++++++++++
	//ECX等于零时退出,否则执行
	if (RW_CX==0)
		return;

RepeatRun:

	Bit32u edi;
	edi = RW_DI;
	op1 = READ_VIRTUAL_32BIT_REG(0);
	WRITE_VIRTUAL_DWORD(BX_SEG_REG_ES, edi, &op1);
	if (BX_CPU_CLASS_PTR get_DF())
	{
		edi -= 4;
	}
	else
	{
		edi += 4;
	}
	RW_DI = edi;
	RW_CX--;
	if (RW_CX==0)
		return;

	if (BX_CPU_CLASS_PTR async_event)
	{
		BX_CPU_CLASS_PTR invalidate_prefetch_q();
		RW_EIP	= BX_CPU_CLASS_PTR prev_eip; // commit old EIP
		return;
	}

	goto RepeatRun;
}

	void
BX_CPU_C::STOSD_eAXYv_E32_rep__(BX_CPU_C *icpu,bxInstruction_c *i)
{
	Bit32u op1;
	Bit32u edi;
	edi = RW_EDI;
	op1 = READ_VIRTUAL_32BIT_REG(0);
	WRITE_VIRTUAL_DWORD(BX_SEG_REG_ES, edi, &op1);
	if (BX_CPU_CLASS_PTR get_DF())
	{
		edi -= 4;
	}
	else
	{
		edi += 4;
	}
	RW_EDI = edi;
}

	void
BX_CPU_C::STOSD_eAXYv_E32_repf2(BX_CPU_C *icpu,bxInstruction_c *i)
{
	Bit32u op1;
	//++++++++++++++++++++++++++++++++
	//ECX等于零时退出,否则执行
	if (RW_ECX==0)
		return;

RepeatRun:

	Bit32u edi;
	edi = RW_EDI;
	op1 = READ_VIRTUAL_32BIT_REG(0);
	WRITE_VIRTUAL_DWORD(BX_SEG_REG_ES, edi, &op1);
	if (BX_CPU_CLASS_PTR get_DF())
	{
		edi -= 4;
	}
	else
	{
		edi += 4;
	}
	RW_EDI = edi;
	RW_ECX--;
	if (RW_ECX==0)
		return;

	if (BX_CPU_CLASS_PTR async_event)
	{
		BX_CPU_CLASS_PTR invalidate_prefetch_q();
		RW_EIP	= BX_CPU_CLASS_PTR prev_eip; // commit old EIP
		return;
	}

	goto RepeatRun;
}

	void
BX_CPU_C::STOSD_eAXYv_E32_repf3(BX_CPU_C *icpu,bxInstruction_c *i)
{
	Bit32u op1;
	//++++++++++++++++++++++++++++++++
	//ECX等于零时退出,否则执行
	if (RW_ECX==0)
		return;

RepeatRun:

	Bit32u edi;
	edi = RW_EDI;
	op1 = READ_VIRTUAL_32BIT_REG(0);
	WRITE_VIRTUAL_DWORD(BX_SEG_REG_ES, edi, &op1);
	if (BX_CPU_CLASS_PTR get_DF())
	{
		edi -= 4;
	}
	else
	{
		edi += 4;
	}
	RW_EDI = edi;
	RW_ECX--;
	if (RW_ECX==0)
		return;

	if (BX_CPU_CLASS_PTR async_event)
	{
		BX_CPU_CLASS_PTR invalidate_prefetch_q();
		RW_EIP	= BX_CPU_CLASS_PTR prev_eip; // commit old EIP
		return;
	}

	goto RepeatRun;
}

	void
BX_CPU_C::LODSB_ALXb_E16_rep__ (BX_CPU_C *icpu,bxInstruction_c *i)
{
	unsigned seg;
	Bit8u op1;
	seg = MODRMSeg(i);

	Bit32u esi;
	esi = RW_SI;
	READ_VIRTUAL_BYTE(seg, esi, &op1);
	WRITE_VIRTUAL_8BIT_REG(0,op1);
	if (BX_CPU_CLASS_PTR get_DF())
	{
		esi -= 1;
	}
	else
	{
		esi += 1;
	}
	RW_SI = esi;
}

	void
BX_CPU_C::LODSB_ALXb_E16_repf2 (BX_CPU_C *icpu,bxInstruction_c *i)
{
	unsigned seg;
	Bit8u op1;
	seg = MODRMSeg(i);

	//++++++++++++++++++++++++++++++++
	//ECX等于零时退出,否则执行
	if (RW_CX==0)
		return;

RepeatRun:

	Bit32u esi;
	esi = RW_SI;
	READ_VIRTUAL_BYTE(seg, esi, &op1);
	WRITE_VIRTUAL_8BIT_REG(0,op1);
	if (BX_CPU_CLASS_PTR get_DF())
	{
		esi -= 1;
	}
	else
	{
		esi += 1;
	}
	RW_SI = esi;
	RW_CX--;
	if (RW_CX==0)
		return;

	if (BX_CPU_CLASS_PTR async_event)
	{
		BX_CPU_CLASS_PTR invalidate_prefetch_q();
		RW_EIP	= BX_CPU_CLASS_PTR prev_eip; // commit old EIP
		return;
	}

	goto RepeatRun;
}

	void
BX_CPU_C::LODSB_ALXb_E16_repf3 (BX_CPU_C *icpu,bxInstruction_c *i)
{
	unsigned seg;
	Bit8u op1;
	seg = MODRMSeg(i);

	//++++++++++++++++++++++++++++++++
	//ECX等于零时退出,否则执行
	if (RW_CX==0)
		return;

RepeatRun:

	Bit32u esi;
	esi = RW_SI;
	READ_VIRTUAL_BYTE(seg, esi, &op1);
	WRITE_VIRTUAL_8BIT_REG(0,op1);
	if (BX_CPU_CLASS_PTR get_DF())
	{
		esi -= 1;
	}
	else
	{
		esi += 1;
	}
	RW_SI = esi;
	RW_CX--;
	if (RW_CX==0)
		return;

	if (BX_CPU_CLASS_PTR async_event)
	{
		BX_CPU_CLASS_PTR invalidate_prefetch_q();
		RW_EIP	= BX_CPU_CLASS_PTR prev_eip; // commit old EIP
		return;
	}

	goto RepeatRun;
}

	void
BX_CPU_C::LODSB_ALXb_E32_rep__ (BX_CPU_C *icpu,bxInstruction_c *i)
{
	unsigned seg;
	Bit8u op1;
	seg = MODRMSeg(i);

	Bit32u esi;
	esi = RW_ESI;
	READ_VIRTUAL_BYTE(seg, esi, &op1);
	WRITE_VIRTUAL_8BIT_REG(0,op1);
	if (BX_CPU_CLASS_PTR get_DF())
	{
		esi -= 1;
	}
	else
	{
		esi += 1;
	}
	RW_ESI = esi;
}

	void
BX_CPU_C::LODSB_ALXb_E32_repf2 (BX_CPU_C *icpu,bxInstruction_c *i)
{
	unsigned seg;
	Bit8u op1;
	seg = MODRMSeg(i);

	//++++++++++++++++++++++++++++++++
	//ECX等于零时退出,否则执行
	if (RW_ECX==0)
		return;

RepeatRun:

	Bit32u esi;
	esi = RW_ESI;
	READ_VIRTUAL_BYTE(seg, esi, &op1);
	WRITE_VIRTUAL_8BIT_REG(0,op1);
	if (BX_CPU_CLASS_PTR get_DF())
	{
		esi -= 1;
	}
	else
	{
		esi += 1;
	}
	RW_ESI = esi;
	RW_ECX--;
	if (RW_ECX==0)
		return;

	if (BX_CPU_CLASS_PTR async_event)
	{
		BX_CPU_CLASS_PTR invalidate_prefetch_q();
		RW_EIP	= BX_CPU_CLASS_PTR prev_eip; // commit old EIP
		return;
	}

	goto RepeatRun;
}

	void
BX_CPU_C::LODSB_ALXb_E32_repf3 (BX_CPU_C *icpu,bxInstruction_c *i)
{
	unsigned seg;
	Bit8u op1;
	seg = MODRMSeg(i);

	//++++++++++++++++++++++++++++++++
	//ECX等于零时退出,否则执行
	if (RW_ECX==0)
		return;

RepeatRun:

	Bit32u esi;
	esi = RW_ESI;
	READ_VIRTUAL_BYTE(seg, esi, &op1);
	WRITE_VIRTUAL_8BIT_REG(0,op1);
	if (BX_CPU_CLASS_PTR get_DF())
	{
		esi -= 1;
	}
	else
	{
		esi += 1;
	}
	RW_ESI = esi;
	RW_ECX--;
	if (RW_ECX==0)
		return;

	if (BX_CPU_CLASS_PTR async_event)
	{
		BX_CPU_CLASS_PTR invalidate_prefetch_q();
		RW_EIP	= BX_CPU_CLASS_PTR prev_eip; // commit old EIP
		return;
	}

	goto RepeatRun;
}

	void
BX_CPU_C::LODSW_eAXXv_E16_rep__(BX_CPU_C *icpu,bxInstruction_c *i)
{
	unsigned seg;
	Bit16u op1;
	seg = MODRMSeg(i);

	Bit32u esi;
	esi = RW_SI;
	READ_VIRTUAL_WORD(seg, esi, &op1);
	WRITE_VIRTUAL_16BIT_REG(0,op1);
	if (BX_CPU_CLASS_PTR get_DF())
	{
		esi -= 2;
	}
	else
	{
		esi += 2;
	}
	RW_SI = esi;
}

	void
BX_CPU_C::LODSW_eAXXv_E16_repf2(BX_CPU_C *icpu,bxInstruction_c *i)
{
	unsigned seg;
	Bit16u op1;
	seg = MODRMSeg(i);

	//++++++++++++++++++++++++++++++++
	//ECX等于零时退出,否则执行
	if (RW_CX==0)
		return;

RepeatRun:

	Bit32u esi;
	esi = RW_SI;
	READ_VIRTUAL_WORD(seg, esi, &op1);
	WRITE_VIRTUAL_16BIT_REG(0,op1);
	if (BX_CPU_CLASS_PTR get_DF())
	{
		esi -= 2;
	}
	else
	{
		esi += 2;
	}
	RW_SI = esi;
	RW_CX--;
	if (RW_CX==0)
		return;

	if (BX_CPU_CLASS_PTR async_event)
	{
		BX_CPU_CLASS_PTR invalidate_prefetch_q();
		RW_EIP	= BX_CPU_CLASS_PTR prev_eip; // commit old EIP
		return;
	}

	goto RepeatRun;
}

	void
BX_CPU_C::LODSW_eAXXv_E16_repf3(BX_CPU_C *icpu,bxInstruction_c *i)
{
	unsigned seg;
	Bit16u op1;
	seg = MODRMSeg(i);

	//++++++++++++++++++++++++++++++++
	//ECX等于零时退出,否则执行
	if (RW_CX==0)
		return;

RepeatRun:

	Bit32u esi;
	esi = RW_SI;
	READ_VIRTUAL_WORD(seg, esi, &op1);
	WRITE_VIRTUAL_16BIT_REG(0,op1);
	if (BX_CPU_CLASS_PTR get_DF())
	{
		esi -= 2;
	}
	else
	{
		esi += 2;
	}
	RW_SI = esi;
	RW_CX--;
	if (RW_CX==0)
		return;

	if (BX_CPU_CLASS_PTR async_event)
	{
		BX_CPU_CLASS_PTR invalidate_prefetch_q();
		RW_EIP	= BX_CPU_CLASS_PTR prev_eip; // commit old EIP
		return;
	}

	goto RepeatRun;
}

	void
BX_CPU_C::LODSW_eAXXv_E32_rep__(BX_CPU_C *icpu,bxInstruction_c *i)
{
	unsigned seg;
	Bit16u op1;
	seg = MODRMSeg(i);

	Bit32u esi;
	esi = RW_ESI;
	READ_VIRTUAL_WORD(seg, esi, &op1);
	WRITE_VIRTUAL_16BIT_REG(0,op1);
	if (BX_CPU_CLASS_PTR get_DF())
	{
		esi -= 2;
	}
	else
	{
		esi += 2;
	}
	RW_ESI = esi;
}

	void
BX_CPU_C::LODSW_eAXXv_E32_repf2(BX_CPU_C *icpu,bxInstruction_c *i)
{
	unsigned seg;
	Bit16u op1;
	seg = MODRMSeg(i);

	//++++++++++++++++++++++++++++++++
	//ECX等于零时退出,否则执行
	if (RW_ECX==0)
		return;

RepeatRun:

	Bit32u esi;
	esi = RW_ESI;
	READ_VIRTUAL_WORD(seg, esi, &op1);
	WRITE_VIRTUAL_16BIT_REG(0,op1);
	if (BX_CPU_CLASS_PTR get_DF())
	{
		esi -= 2;
	}
	else
	{
		esi += 2;
	}
	RW_ESI = esi;
	RW_ECX--;
	if (RW_ECX==0)
		return;

	if (BX_CPU_CLASS_PTR async_event)
	{
		BX_CPU_CLASS_PTR invalidate_prefetch_q();
		RW_EIP	= BX_CPU_CLASS_PTR prev_eip; // commit old EIP
		return;
	}

	goto RepeatRun;
}

	void
BX_CPU_C::LODSW_eAXXv_E32_repf3(BX_CPU_C *icpu,bxInstruction_c *i)
{
	unsigned seg;
	Bit16u op1;
	seg = MODRMSeg(i);

	//++++++++++++++++++++++++++++++++
	//ECX等于零时退出,否则执行
	if (RW_ECX==0)
		return;

RepeatRun:

	Bit32u esi;
	esi = RW_ESI;
	READ_VIRTUAL_WORD(seg, esi, &op1);
	WRITE_VIRTUAL_16BIT_REG(0,op1);
	if (BX_CPU_CLASS_PTR get_DF())
	{
		esi -= 2;
	}
	else
	{
		esi += 2;
	}
	RW_ESI = esi;
	RW_ECX--;
	if (RW_ECX==0)
		return;

	if (BX_CPU_CLASS_PTR async_event)
	{
		BX_CPU_CLASS_PTR invalidate_prefetch_q();
		RW_EIP	= BX_CPU_CLASS_PTR prev_eip; // commit old EIP
		return;
	}

	goto RepeatRun;
}

	void
BX_CPU_C::LODSD_eAXXv_E16_rep__(BX_CPU_C *icpu,bxInstruction_c *i)
{
	unsigned seg;
	Bit32u op1;
	seg = MODRMSeg(i);

	Bit32u esi;
	esi = RW_SI;
	READ_VIRTUAL_DWORD(seg, esi, &op1);
	WRITE_VIRTUAL_32BIT_REG(0,op1);
	if (BX_CPU_CLASS_PTR get_DF())
	{
		esi -= 4;
	}
	else
	{
		esi += 4;
	}
	RW_SI = esi;
}

	void
BX_CPU_C::LODSD_eAXXv_E16_repf2(BX_CPU_C *icpu,bxInstruction_c *i)
{
	unsigned seg;
	Bit32u op1;
	seg = MODRMSeg(i);

	//++++++++++++++++++++++++++++++++
	//ECX等于零时退出,否则执行
	if (RW_CX==0)
		return;

RepeatRun:

	Bit32u esi;
	esi = RW_SI;
	READ_VIRTUAL_DWORD(seg, esi, &op1);
	WRITE_VIRTUAL_32BIT_REG(0,op1);
	if (BX_CPU_CLASS_PTR get_DF())
	{
		esi -= 4;
	}
	else
	{
		esi += 4;
	}
	RW_SI = esi;
	RW_CX--;
	if (RW_CX==0)
		return;

	if (BX_CPU_CLASS_PTR async_event)
	{
		BX_CPU_CLASS_PTR invalidate_prefetch_q();
		RW_EIP	= BX_CPU_CLASS_PTR prev_eip; // commit old EIP
		return;
	}

	goto RepeatRun;
}

	void
BX_CPU_C::LODSD_eAXXv_E16_repf3(BX_CPU_C *icpu,bxInstruction_c *i)
{
	unsigned seg;
	Bit32u op1;
	seg = MODRMSeg(i);

	//++++++++++++++++++++++++++++++++
	//ECX等于零时退出,否则执行
	if (RW_CX==0)
		return;

RepeatRun:

	Bit32u esi;
	esi = RW_SI;
	READ_VIRTUAL_DWORD(seg, esi, &op1);
	WRITE_VIRTUAL_32BIT_REG(0,op1);
	if (BX_CPU_CLASS_PTR get_DF())
	{
		esi -= 4;
	}
	else
	{
		esi += 4;
	}
	RW_SI = esi;
	RW_CX--;
	if (RW_CX==0)
		return;

	if (BX_CPU_CLASS_PTR async_event)
	{
		BX_CPU_CLASS_PTR invalidate_prefetch_q();
		RW_EIP	= BX_CPU_CLASS_PTR prev_eip; // commit old EIP
		return;
	}

	goto RepeatRun;
}

	void
BX_CPU_C::LODSD_eAXXv_E32_rep__(BX_CPU_C *icpu,bxInstruction_c *i)
{
	unsigned seg;
	Bit32u op1;
	seg = MODRMSeg(i);

	Bit32u esi;
	esi = RW_ESI;
	READ_VIRTUAL_DWORD(seg, esi, &op1);
	WRITE_VIRTUAL_32BIT_REG(0,op1);
	if (BX_CPU_CLASS_PTR get_DF())
	{
		esi -= 4;
	}
	else
	{
		esi += 4;
	}
	RW_ESI = esi;
}

	void
BX_CPU_C::LODSD_eAXXv_E32_repf2(BX_CPU_C *icpu,bxInstruction_c *i)
{
	unsigned seg;
	Bit32u op1;
	seg = MODRMSeg(i);

	//++++++++++++++++++++++++++++++++
	//ECX等于零时退出,否则执行
	if (RW_ECX==0)
		return;

RepeatRun:

	Bit32u esi;
	esi = RW_ESI;
	READ_VIRTUAL_DWORD(seg, esi, &op1);
	WRITE_VIRTUAL_32BIT_REG(0,op1);
	if (BX_CPU_CLASS_PTR get_DF())
	{
		esi -= 4;
	}
	else
	{
		esi += 4;
	}
	RW_ESI = esi;
	RW_ECX--;
	if (RW_ECX==0)
		return;

	if (BX_CPU_CLASS_PTR async_event)
	{
		BX_CPU_CLASS_PTR invalidate_prefetch_q();
		RW_EIP	= BX_CPU_CLASS_PTR prev_eip; // commit old EIP
		return;
	}

	goto RepeatRun;
}

	void
BX_CPU_C::LODSD_eAXXv_E32_repf3(BX_CPU_C *icpu,bxInstruction_c *i)
{
	unsigned seg;
	Bit32u op1;
	seg = MODRMSeg(i);

	//++++++++++++++++++++++++++++++++
	//ECX等于零时退出,否则执行
	if (RW_ECX==0)
		return;

RepeatRun:

	Bit32u esi;
	esi = RW_ESI;
	READ_VIRTUAL_DWORD(seg, esi, &op1);
	WRITE_VIRTUAL_32BIT_REG(0,op1);
	if (BX_CPU_CLASS_PTR get_DF())
	{
		esi -= 4;
	}
	else
	{
		esi += 4;
	}
	RW_ESI = esi;
	RW_ECX--;
	if (RW_ECX==0)
		return;

	if (BX_CPU_CLASS_PTR async_event)
	{
		BX_CPU_CLASS_PTR invalidate_prefetch_q();
		RW_EIP	= BX_CPU_CLASS_PTR prev_eip; // commit old EIP
		return;
	}

	goto RepeatRun;
}

	void
BX_CPU_C::OUTSB_DXXb_E16_rep__(BX_CPU_C *icpu,bxInstruction_c *i)
{
	unsigned seg;
	Bit8u op1;
	seg = MODRMSeg(i);

	if (BX_CPU_CLASS_PTR cr0.pe && (BX_CPU_CLASS_PTR get_VM() || (RW_CPL>BX_CPU_CLASS_PTR get_IOPL())))
	{
		if ( !BX_CPU_CLASS_PTR allow_io(RW_DX, 1) )
		{
			BX_CPU_CLASS_PTR exception(BX_GP_EXCEPTION, 0, 0);
		}
	}

	Bit32u esi;
	esi = RW_SI;
	READ_VIRTUAL_BYTE(seg, esi, &op1);
	BX_CPU_CLASS_PTR BX_OUTP(RW_DX, op1, 1);
	if (BX_CPU_CLASS_PTR get_DF())
	{
		esi -= 1;
	}
	else
	{
		esi += 1;
	}
	RW_SI = esi;
}

	void
BX_CPU_C::OUTSB_DXXb_E16_repf2(BX_CPU_C *icpu,bxInstruction_c *i)
{
	unsigned seg;
	Bit8u op1;
	seg = MODRMSeg(i);

	//++++++++++++++++++++++++++++++++
	//ECX等于零时退出,否则执行
	if (RW_CX==0)
		return;

	if (BX_CPU_CLASS_PTR cr0.pe && (BX_CPU_CLASS_PTR get_VM() || (RW_CPL>BX_CPU_CLASS_PTR get_IOPL())))
	{
		if ( !BX_CPU_CLASS_PTR allow_io(RW_DX, 1) )
		{
			BX_CPU_CLASS_PTR exception(BX_GP_EXCEPTION, 0, 0);
		}
	}

RepeatRun:

	Bit32u esi;
	esi = RW_SI;
	READ_VIRTUAL_BYTE(seg, esi, &op1);
	BX_CPU_CLASS_PTR BX_OUTP(RW_DX, op1, 1);
	if (BX_CPU_CLASS_PTR get_DF())
	{
		esi -= 1;
	}
	else
	{
		esi += 1;
	}
	RW_SI = esi;
	RW_CX--;
	if (RW_CX==0)
		return;

	if (BX_CPU_CLASS_PTR async_event)
	{
		BX_CPU_CLASS_PTR invalidate_prefetch_q();
		RW_EIP	= BX_CPU_CLASS_PTR prev_eip; // commit old EIP
		return;
	}

	goto RepeatRun;
}

	void
BX_CPU_C::OUTSB_DXXb_E16_repf3(BX_CPU_C *icpu,bxInstruction_c *i)
{
	unsigned seg;
	Bit8u op1;
	seg = MODRMSeg(i);

	//++++++++++++++++++++++++++++++++
	//ECX等于零时退出,否则执行
	if (RW_CX==0)
		return;

	if (BX_CPU_CLASS_PTR cr0.pe && (BX_CPU_CLASS_PTR get_VM() || (RW_CPL>BX_CPU_CLASS_PTR get_IOPL())))
	{
		if ( !BX_CPU_CLASS_PTR allow_io(RW_DX, 1) )
		{
			BX_CPU_CLASS_PTR exception(BX_GP_EXCEPTION, 0, 0);
		}
	}

RepeatRun:

	Bit32u esi;
	esi = RW_SI;
	READ_VIRTUAL_BYTE(seg, esi, &op1);
	BX_CPU_CLASS_PTR BX_OUTP(RW_DX, op1, 1);
	if (BX_CPU_CLASS_PTR get_DF())
	{
		esi -= 1;
	}
	else
	{
		esi += 1;
	}
	RW_SI = esi;
	RW_CX--;
	if (RW_CX==0)
		return;

	if (BX_CPU_CLASS_PTR async_event)
	{
		BX_CPU_CLASS_PTR invalidate_prefetch_q();
		RW_EIP	= BX_CPU_CLASS_PTR prev_eip; // commit old EIP
		return;
	}

	goto RepeatRun;
}

	void
BX_CPU_C::OUTSB_DXXb_E32_rep__(BX_CPU_C *icpu,bxInstruction_c *i)
{
	unsigned seg;
	Bit8u op1;
	seg = MODRMSeg(i);

	if (BX_CPU_CLASS_PTR cr0.pe && (BX_CPU_CLASS_PTR get_VM() || (RW_CPL>BX_CPU_CLASS_PTR get_IOPL())))
	{
		if ( !BX_CPU_CLASS_PTR allow_io(RW_DX, 1) )
		{
			BX_CPU_CLASS_PTR exception(BX_GP_EXCEPTION, 0, 0);
		}
	}

	Bit32u esi;
	esi = RW_ESI;
	READ_VIRTUAL_BYTE(seg, esi, &op1);
	BX_CPU_CLASS_PTR BX_OUTP(RW_DX, op1, 1);
	if (BX_CPU_CLASS_PTR get_DF())
	{
		esi -= 1;
	}
	else
	{
		esi += 1;
	}
	RW_ESI = esi;
}

	void
BX_CPU_C::OUTSB_DXXb_E32_repf2(BX_CPU_C *icpu,bxInstruction_c *i)
{
	unsigned seg;
	Bit8u op1;
	seg = MODRMSeg(i);

	//++++++++++++++++++++++++++++++++
	//ECX等于零时退出,否则执行
	if (RW_ECX==0)
		return;

	if (BX_CPU_CLASS_PTR cr0.pe && (BX_CPU_CLASS_PTR get_VM() || (RW_CPL>BX_CPU_CLASS_PTR get_IOPL())))
	{
		if ( !BX_CPU_CLASS_PTR allow_io(RW_DX, 1) )
		{
			BX_CPU_CLASS_PTR exception(BX_GP_EXCEPTION, 0, 0);
		}
	}

RepeatRun:

	Bit32u esi;
	esi = RW_ESI;
	READ_VIRTUAL_BYTE(seg, esi, &op1);
	BX_CPU_CLASS_PTR BX_OUTP(RW_DX, op1, 1);
	if (BX_CPU_CLASS_PTR get_DF())
	{
		esi -= 1;
	}
	else
	{
		esi += 1;
	}
	RW_ESI = esi;
	RW_ECX--;
	if (RW_ECX==0)
		return;

	if (BX_CPU_CLASS_PTR async_event)
	{
		BX_CPU_CLASS_PTR invalidate_prefetch_q();
		RW_EIP	= BX_CPU_CLASS_PTR prev_eip; // commit old EIP
		return;
	}

	goto RepeatRun;
}

	void
BX_CPU_C::OUTSB_DXXb_E32_repf3(BX_CPU_C *icpu,bxInstruction_c *i)
{
	unsigned seg;
	Bit8u op1;
	seg = MODRMSeg(i);

	//++++++++++++++++++++++++++++++++
	//ECX等于零时退出,否则执行
	if (RW_ECX==0)
		return;

	if (BX_CPU_CLASS_PTR cr0.pe && (BX_CPU_CLASS_PTR get_VM() || (RW_CPL>BX_CPU_CLASS_PTR get_IOPL())))
	{
		if ( !BX_CPU_CLASS_PTR allow_io(RW_DX, 1) )
		{
			BX_CPU_CLASS_PTR exception(BX_GP_EXCEPTION, 0, 0);
		}
	}

RepeatRun:

	Bit32u esi;
	esi = RW_ESI;
	READ_VIRTUAL_BYTE(seg, esi, &op1);
	BX_CPU_CLASS_PTR BX_OUTP(RW_DX, op1, 1);
	if (BX_CPU_CLASS_PTR get_DF())
	{
		esi -= 1;
	}
	else
	{
		esi += 1;
	}
	RW_ESI = esi;
	RW_ECX--;
	if (RW_ECX==0)
		return;

	if (BX_CPU_CLASS_PTR async_event)
	{
		BX_CPU_CLASS_PTR invalidate_prefetch_q();
		RW_EIP	= BX_CPU_CLASS_PTR prev_eip; // commit old EIP
		return;
	}

	goto RepeatRun;
}

	void
BX_CPU_C::OUTSW_DXXv_E16_rep__(BX_CPU_C *icpu,bxInstruction_c *i)
{
	unsigned seg;
	Bit16u op1;
	seg = MODRMSeg(i);

	if (BX_CPU_CLASS_PTR cr0.pe && (BX_CPU_CLASS_PTR get_VM() || (RW_CPL>BX_CPU_CLASS_PTR get_IOPL())))
	{
		if ( !BX_CPU_CLASS_PTR allow_io(RW_DX, 2) )
		{
			BX_CPU_CLASS_PTR exception(BX_GP_EXCEPTION, 0, 0);
		}
	}

	Bit32u esi;
	esi = RW_SI;
	READ_VIRTUAL_WORD(seg, esi, &op1);
	BX_CPU_CLASS_PTR BX_OUTP(RW_DX, op1, 2);
	if (BX_CPU_CLASS_PTR get_DF())
	{
		esi -= 2;
	}
	else
	{
		esi += 2;
	}
	RW_SI = esi;
}

	void
BX_CPU_C::OUTSW_DXXv_E16_repf2(BX_CPU_C *icpu,bxInstruction_c *i)
{
	unsigned seg;
	Bit16u op1;
	seg = MODRMSeg(i);

	//++++++++++++++++++++++++++++++++
	//ECX等于零时退出,否则执行
	if (RW_CX==0)
		return;

	if (BX_CPU_CLASS_PTR cr0.pe && (BX_CPU_CLASS_PTR get_VM() || (RW_CPL>BX_CPU_CLASS_PTR get_IOPL())))
	{
		if ( !BX_CPU_CLASS_PTR allow_io(RW_DX, 2) )
		{
			BX_CPU_CLASS_PTR exception(BX_GP_EXCEPTION, 0, 0);
		}
	}

RepeatRun:

	Bit32u esi;
	esi = RW_SI;
	READ_VIRTUAL_WORD(seg, esi, &op1);
	BX_CPU_CLASS_PTR BX_OUTP(RW_DX, op1, 2);
	if (BX_CPU_CLASS_PTR get_DF())
	{
		esi -= 2;
	}
	else
	{
		esi += 2;
	}
	RW_SI = esi;
	RW_CX--;
	if (RW_CX==0)
		return;

	if (BX_CPU_CLASS_PTR async_event)
	{
		BX_CPU_CLASS_PTR invalidate_prefetch_q();
		RW_EIP	= BX_CPU_CLASS_PTR prev_eip; // commit old EIP
		return;
	}

	goto RepeatRun;
}

	void
BX_CPU_C::OUTSW_DXXv_E16_repf3(BX_CPU_C *icpu,bxInstruction_c *i)
{
	unsigned seg;
	Bit16u op1;
	seg = MODRMSeg(i);

	//++++++++++++++++++++++++++++++++
	//ECX等于零时退出,否则执行
	if (RW_CX==0)
		return;

	if (BX_CPU_CLASS_PTR cr0.pe && (BX_CPU_CLASS_PTR get_VM() || (RW_CPL>BX_CPU_CLASS_PTR get_IOPL())))
	{
		if ( !BX_CPU_CLASS_PTR allow_io(RW_DX, 2) )
		{
			BX_CPU_CLASS_PTR exception(BX_GP_EXCEPTION, 0, 0);
		}
	}

RepeatRun:

	Bit32u esi;
	esi = RW_SI;
	READ_VIRTUAL_WORD(seg, esi, &op1);
	BX_CPU_CLASS_PTR BX_OUTP(RW_DX, op1, 2);
	if (BX_CPU_CLASS_PTR get_DF())
	{
		esi -= 2;
	}
	else
	{
		esi += 2;
	}
	RW_SI = esi;
	RW_CX--;
	if (RW_CX==0)
		return;

	if (BX_CPU_CLASS_PTR async_event)
	{
		BX_CPU_CLASS_PTR invalidate_prefetch_q();
		RW_EIP	= BX_CPU_CLASS_PTR prev_eip; // commit old EIP
		return;
	}

	goto RepeatRun;
}

	void
BX_CPU_C::OUTSW_DXXv_E32_rep__(BX_CPU_C *icpu,bxInstruction_c *i)
{
	unsigned seg;
	Bit16u op1;
	seg = MODRMSeg(i);

	if (BX_CPU_CLASS_PTR cr0.pe && (BX_CPU_CLASS_PTR get_VM() || (RW_CPL>BX_CPU_CLASS_PTR get_IOPL())))
	{
		if ( !BX_CPU_CLASS_PTR allow_io(RW_DX, 2) )
		{
			BX_CPU_CLASS_PTR exception(BX_GP_EXCEPTION, 0, 0);
		}
	}

	Bit32u esi;
	esi = RW_ESI;
	READ_VIRTUAL_WORD(seg, esi, &op1);
	BX_CPU_CLASS_PTR BX_OUTP(RW_DX, op1, 2);
	if (BX_CPU_CLASS_PTR get_DF())
	{
		esi -= 2;
	}
	else
	{
		esi += 2;
	}
	RW_ESI = esi;
}

	void
BX_CPU_C::OUTSW_DXXv_E32_repf2(BX_CPU_C *icpu,bxInstruction_c *i)
{
	unsigned seg;
	Bit16u op1;
	seg = MODRMSeg(i);

	//++++++++++++++++++++++++++++++++
	//ECX等于零时退出,否则执行
	if (RW_ECX==0)
		return;

	if (BX_CPU_CLASS_PTR cr0.pe && (BX_CPU_CLASS_PTR get_VM() || (RW_CPL>BX_CPU_CLASS_PTR get_IOPL())))
	{
		if ( !BX_CPU_CLASS_PTR allow_io(RW_DX, 2) )
		{
			BX_CPU_CLASS_PTR exception(BX_GP_EXCEPTION, 0, 0);
		}
	}

RepeatRun:

	Bit32u esi;
	esi = RW_ESI;
	READ_VIRTUAL_WORD(seg, esi, &op1);
	BX_CPU_CLASS_PTR BX_OUTP(RW_DX, op1, 2);
	if (BX_CPU_CLASS_PTR get_DF())
	{
		esi -= 2;
	}
	else
	{
		esi += 2;
	}
	RW_ESI = esi;
	RW_ECX--;
	if (RW_ECX==0)
		return;

	if (BX_CPU_CLASS_PTR async_event)
	{
		BX_CPU_CLASS_PTR invalidate_prefetch_q();
		RW_EIP	= BX_CPU_CLASS_PTR prev_eip; // commit old EIP
		return;
	}

	goto RepeatRun;
}

	void
BX_CPU_C::OUTSW_DXXv_E32_repf3(BX_CPU_C *icpu,bxInstruction_c *i)
{
	unsigned seg;
	Bit16u op1;
	seg = MODRMSeg(i);

	//++++++++++++++++++++++++++++++++
	//ECX等于零时退出,否则执行
	if (RW_ECX==0)
		return;

	if (BX_CPU_CLASS_PTR cr0.pe && (BX_CPU_CLASS_PTR get_VM() || (RW_CPL>BX_CPU_CLASS_PTR get_IOPL())))
	{
		if ( !BX_CPU_CLASS_PTR allow_io(RW_DX, 2) )
		{
			BX_CPU_CLASS_PTR exception(BX_GP_EXCEPTION, 0, 0);
		}
	}

RepeatRun:

	Bit32u esi;
	esi = RW_ESI;
	READ_VIRTUAL_WORD(seg, esi, &op1);
	BX_CPU_CLASS_PTR BX_OUTP(RW_DX, op1, 2);
	if (BX_CPU_CLASS_PTR get_DF())
	{
		esi -= 2;
	}
	else
	{
		esi += 2;
	}
	RW_ESI = esi;
	RW_ECX--;
	if (RW_ECX==0)
		return;

	if (BX_CPU_CLASS_PTR async_event)
	{
		BX_CPU_CLASS_PTR invalidate_prefetch_q();
		RW_EIP	= BX_CPU_CLASS_PTR prev_eip; // commit old EIP
		return;
	}

	goto RepeatRun;
}

	void
BX_CPU_C::OUTSD_DXXv_E16_rep__(BX_CPU_C *icpu,bxInstruction_c *i)
{
	unsigned seg;
	Bit32u op1;
	seg = MODRMSeg(i);

	if (BX_CPU_CLASS_PTR cr0.pe && (BX_CPU_CLASS_PTR get_VM() || (RW_CPL>BX_CPU_CLASS_PTR get_IOPL())))
	{
		if ( !BX_CPU_CLASS_PTR allow_io(RW_DX, 4) )
		{
			BX_CPU_CLASS_PTR exception(BX_GP_EXCEPTION, 0, 0);
		}
	}

	Bit32u esi;
	esi = RW_SI;
	READ_VIRTUAL_DWORD(seg, esi, &op1);
	BX_CPU_CLASS_PTR BX_OUTP(RW_DX, op1, 4);
	if (BX_CPU_CLASS_PTR get_DF())
	{
		esi -= 4;
	}
	else
	{
		esi += 4;
	}
	RW_SI = esi;
}

	void
BX_CPU_C::OUTSD_DXXv_E16_repf2(BX_CPU_C *icpu,bxInstruction_c *i)
{
	unsigned seg;
	Bit32u op1;
	seg = MODRMSeg(i);

	//++++++++++++++++++++++++++++++++
	//ECX等于零时退出,否则执行
	if (RW_CX==0)
		return;

	if (BX_CPU_CLASS_PTR cr0.pe && (BX_CPU_CLASS_PTR get_VM() || (RW_CPL>BX_CPU_CLASS_PTR get_IOPL())))
	{
		if ( !BX_CPU_CLASS_PTR allow_io(RW_DX, 4) )
		{
			BX_CPU_CLASS_PTR exception(BX_GP_EXCEPTION, 0, 0);
		}
	}

RepeatRun:

	Bit32u esi;
	esi = RW_SI;
	READ_VIRTUAL_DWORD(seg, esi, &op1);
	BX_CPU_CLASS_PTR BX_OUTP(RW_DX, op1, 4);
	if (BX_CPU_CLASS_PTR get_DF())
	{
		esi -= 4;
	}
	else
	{
		esi += 4;
	}
	RW_SI = esi;
	RW_CX--;
	if (RW_CX==0)
		return;

	if (BX_CPU_CLASS_PTR async_event)
	{
		BX_CPU_CLASS_PTR invalidate_prefetch_q();
		RW_EIP	= BX_CPU_CLASS_PTR prev_eip; // commit old EIP
		return;
	}

	goto RepeatRun;
}

	void
BX_CPU_C::OUTSD_DXXv_E16_repf3(BX_CPU_C *icpu,bxInstruction_c *i)
{
	unsigned seg;
	Bit32u op1;
	seg = MODRMSeg(i);

	//++++++++++++++++++++++++++++++++
	//ECX等于零时退出,否则执行
	if (RW_CX==0)
		return;

	if (BX_CPU_CLASS_PTR cr0.pe && (BX_CPU_CLASS_PTR get_VM() || (RW_CPL>BX_CPU_CLASS_PTR get_IOPL())))
	{
		if ( !BX_CPU_CLASS_PTR allow_io(RW_DX, 4) )
		{
			BX_CPU_CLASS_PTR exception(BX_GP_EXCEPTION, 0, 0);
		}
	}

RepeatRun:

	Bit32u esi;
	esi = RW_SI;
	READ_VIRTUAL_DWORD(seg, esi, &op1);
	BX_CPU_CLASS_PTR BX_OUTP(RW_DX, op1, 4);
	if (BX_CPU_CLASS_PTR get_DF())
	{
		esi -= 4;
	}
	else
	{
		esi += 4;
	}
	RW_SI = esi;
	RW_CX--;
	if (RW_CX==0)
		return;

	if (BX_CPU_CLASS_PTR async_event)
	{
		BX_CPU_CLASS_PTR invalidate_prefetch_q();
		RW_EIP	= BX_CPU_CLASS_PTR prev_eip; // commit old EIP
		return;
	}

	goto RepeatRun;
}

	void
BX_CPU_C::OUTSD_DXXv_E32_rep__(BX_CPU_C *icpu,bxInstruction_c *i)
{
	unsigned seg;
	Bit32u op1;
	seg = MODRMSeg(i);

	if (BX_CPU_CLASS_PTR cr0.pe && (BX_CPU_CLASS_PTR get_VM() || (RW_CPL>BX_CPU_CLASS_PTR get_IOPL())))
	{
		if ( !BX_CPU_CLASS_PTR allow_io(RW_DX, 4) )
		{
			BX_CPU_CLASS_PTR exception(BX_GP_EXCEPTION, 0, 0);
		}
	}

	Bit32u esi;
	esi = RW_ESI;
	READ_VIRTUAL_DWORD(seg, esi, &op1);
	BX_CPU_CLASS_PTR BX_OUTP(RW_DX, op1, 4);
	if (BX_CPU_CLASS_PTR get_DF())
	{
		esi -= 4;
	}
	else
	{
		esi += 4;
	}
	RW_ESI = esi;
}

	void
BX_CPU_C::OUTSD_DXXv_E32_repf2(BX_CPU_C *icpu,bxInstruction_c *i)
{
	unsigned seg;
	Bit32u op1;
	seg = MODRMSeg(i);

	//++++++++++++++++++++++++++++++++
	//ECX等于零时退出,否则执行
	if (RW_ECX==0)
		return;

	if (BX_CPU_CLASS_PTR cr0.pe && (BX_CPU_CLASS_PTR get_VM() || (RW_CPL>BX_CPU_CLASS_PTR get_IOPL())))
	{
		if ( !BX_CPU_CLASS_PTR allow_io(RW_DX, 4) )
		{
			BX_CPU_CLASS_PTR exception(BX_GP_EXCEPTION, 0, 0);
		}
	}

RepeatRun:

	Bit32u esi;
	esi = RW_ESI;
	READ_VIRTUAL_DWORD(seg, esi, &op1);
	BX_CPU_CLASS_PTR BX_OUTP(RW_DX, op1, 4);
	if (BX_CPU_CLASS_PTR get_DF())
	{
		esi -= 4;
	}
	else
	{
		esi += 4;
	}
	RW_ESI = esi;
	RW_ECX--;
	if (RW_ECX==0)
		return;

	if (BX_CPU_CLASS_PTR async_event)
	{
		BX_CPU_CLASS_PTR invalidate_prefetch_q();
		RW_EIP	= BX_CPU_CLASS_PTR prev_eip; // commit old EIP
		return;
	}

	goto RepeatRun;
}

	void
BX_CPU_C::OUTSD_DXXv_E32_repf3(BX_CPU_C *icpu,bxInstruction_c *i)
{
	unsigned seg;
	Bit32u op1;
	seg = MODRMSeg(i);

	//++++++++++++++++++++++++++++++++
	//ECX等于零时退出,否则执行
	if (RW_ECX==0)
		return;

	if (BX_CPU_CLASS_PTR cr0.pe && (BX_CPU_CLASS_PTR get_VM() || (RW_CPL>BX_CPU_CLASS_PTR get_IOPL())))
	{
		if ( !BX_CPU_CLASS_PTR allow_io(RW_DX, 4) )
		{
			BX_CPU_CLASS_PTR exception(BX_GP_EXCEPTION, 0, 0);
		}
	}

RepeatRun:

	Bit32u esi;
	esi = RW_ESI;
	READ_VIRTUAL_DWORD(seg, esi, &op1);
	BX_CPU_CLASS_PTR BX_OUTP(RW_DX, op1, 4);
	if (BX_CPU_CLASS_PTR get_DF())
	{
		esi -= 4;
	}
	else
	{
		esi += 4;
	}
	RW_ESI = esi;
	RW_ECX--;
	if (RW_ECX==0)
		return;

	if (BX_CPU_CLASS_PTR async_event)
	{
		BX_CPU_CLASS_PTR invalidate_prefetch_q();
		RW_EIP	= BX_CPU_CLASS_PTR prev_eip; // commit old EIP
		return;
	}

	goto RepeatRun;
}

	void
BX_CPU_C::INSB_YbDX_E16_rep__(BX_CPU_C *icpu,bxInstruction_c *i)
{
	Bit8u op1;
	if (BX_CPU_CLASS_PTR cr0.pe && (BX_CPU_CLASS_PTR get_VM() || (RW_CPL>BX_CPU_CLASS_PTR get_IOPL())))
	{
		if ( !BX_CPU_CLASS_PTR allow_io(RW_DX, 1) )
		{
			BX_CPU_CLASS_PTR exception(BX_GP_EXCEPTION, 0, 0);
		}
	}

	Bit32u edi;
	edi = RW_DI;
	op1 = 0;
	WRITE_VIRTUAL_BYTE(BX_SEG_REG_ES, edi, &op1);
	op1 = BX_CPU_CLASS_PTR BX_INP(RW_DX, 1);
	WRITE_VIRTUAL_BYTE(BX_SEG_REG_ES, edi, &op1);
	if (BX_CPU_CLASS_PTR get_DF())
	{
		edi -= 1;
	}
	else
	{
		edi += 1;
	}
	RW_DI = edi;
}

	void
BX_CPU_C::INSB_YbDX_E16_repf2(BX_CPU_C *icpu,bxInstruction_c *i)
{
	Bit8u op1;
	//++++++++++++++++++++++++++++++++
	//ECX等于零时退出,否则执行
	if (RW_CX==0)
		return;

	if (BX_CPU_CLASS_PTR cr0.pe && (BX_CPU_CLASS_PTR get_VM() || (RW_CPL>BX_CPU_CLASS_PTR get_IOPL())))
	{
		if ( !BX_CPU_CLASS_PTR allow_io(RW_DX, 1) )
		{
			BX_CPU_CLASS_PTR exception(BX_GP_EXCEPTION, 0, 0);
		}
	}

RepeatRun:

	Bit32u edi;
	edi = RW_DI;
	op1 = 0;
	WRITE_VIRTUAL_BYTE(BX_SEG_REG_ES, edi, &op1);
	op1 = BX_CPU_CLASS_PTR BX_INP(RW_DX, 1);
	WRITE_VIRTUAL_BYTE(BX_SEG_REG_ES, edi, &op1);
	if (BX_CPU_CLASS_PTR get_DF())
	{
		edi -= 1;
	}
	else
	{
		edi += 1;
	}
	RW_DI = edi;
	RW_CX--;
	if (RW_CX==0)
		return;

	if (BX_CPU_CLASS_PTR async_event)
	{
		BX_CPU_CLASS_PTR invalidate_prefetch_q();
		RW_EIP	= BX_CPU_CLASS_PTR prev_eip; // commit old EIP
		return;
	}

	goto RepeatRun;
}

	void
BX_CPU_C::INSB_YbDX_E16_repf3(BX_CPU_C *icpu,bxInstruction_c *i)
{
	Bit8u op1;
	//++++++++++++++++++++++++++++++++
	//ECX等于零时退出,否则执行
	if (RW_CX==0)
		return;

	if (BX_CPU_CLASS_PTR cr0.pe && (BX_CPU_CLASS_PTR get_VM() || (RW_CPL>BX_CPU_CLASS_PTR get_IOPL())))
	{
		if ( !BX_CPU_CLASS_PTR allow_io(RW_DX, 1) )
		{
			BX_CPU_CLASS_PTR exception(BX_GP_EXCEPTION, 0, 0);
		}
	}

RepeatRun:

	Bit32u edi;
	edi = RW_DI;
	op1 = 0;
	WRITE_VIRTUAL_BYTE(BX_SEG_REG_ES, edi, &op1);
	op1 = BX_CPU_CLASS_PTR BX_INP(RW_DX, 1);
	WRITE_VIRTUAL_BYTE(BX_SEG_REG_ES, edi, &op1);
	if (BX_CPU_CLASS_PTR get_DF())
	{
		edi -= 1;
	}
	else
	{
		edi += 1;
	}
	RW_DI = edi;
	RW_CX--;
	if (RW_CX==0)
		return;

	if (BX_CPU_CLASS_PTR async_event)
	{
		BX_CPU_CLASS_PTR invalidate_prefetch_q();
		RW_EIP	= BX_CPU_CLASS_PTR prev_eip; // commit old EIP
		return;
	}

	goto RepeatRun;
}

	void
BX_CPU_C::INSB_YbDX_E32_rep__(BX_CPU_C *icpu,bxInstruction_c *i)
{
	Bit8u op1;
	if (BX_CPU_CLASS_PTR cr0.pe && (BX_CPU_CLASS_PTR get_VM() || (RW_CPL>BX_CPU_CLASS_PTR get_IOPL())))
	{
		if ( !BX_CPU_CLASS_PTR allow_io(RW_DX, 1) )
		{
			BX_CPU_CLASS_PTR exception(BX_GP_EXCEPTION, 0, 0);
		}
	}

	Bit32u edi;
	edi = RW_EDI;
	op1 = 0;
	WRITE_VIRTUAL_BYTE(BX_SEG_REG_ES, edi, &op1);
	op1 = BX_CPU_CLASS_PTR BX_INP(RW_DX, 1);
	WRITE_VIRTUAL_BYTE(BX_SEG_REG_ES, edi, &op1);
	if (BX_CPU_CLASS_PTR get_DF())
	{
		edi -= 1;
	}
	else
	{
		edi += 1;
	}
	RW_EDI = edi;
}

	void
BX_CPU_C::INSB_YbDX_E32_repf2(BX_CPU_C *icpu,bxInstruction_c *i)
{
	Bit8u op1;
	//++++++++++++++++++++++++++++++++
	//ECX等于零时退出,否则执行
	if (RW_ECX==0)
		return;

	if (BX_CPU_CLASS_PTR cr0.pe && (BX_CPU_CLASS_PTR get_VM() || (RW_CPL>BX_CPU_CLASS_PTR get_IOPL())))
	{
		if ( !BX_CPU_CLASS_PTR allow_io(RW_DX, 1) )
		{
			BX_CPU_CLASS_PTR exception(BX_GP_EXCEPTION, 0, 0);
		}
	}

RepeatRun:

	Bit32u edi;
	edi = RW_EDI;
	op1 = 0;
	WRITE_VIRTUAL_BYTE(BX_SEG_REG_ES, edi, &op1);
	op1 = BX_CPU_CLASS_PTR BX_INP(RW_DX, 1);
	WRITE_VIRTUAL_BYTE(BX_SEG_REG_ES, edi, &op1);
	if (BX_CPU_CLASS_PTR get_DF())
	{
		edi -= 1;
	}
	else
	{
		edi += 1;
	}
	RW_EDI = edi;
	RW_ECX--;
	if (RW_ECX==0)
		return;

	if (BX_CPU_CLASS_PTR async_event)
	{
		BX_CPU_CLASS_PTR invalidate_prefetch_q();
		RW_EIP	= BX_CPU_CLASS_PTR prev_eip; // commit old EIP
		return;
	}

	goto RepeatRun;
}

	void
BX_CPU_C::INSB_YbDX_E32_repf3(BX_CPU_C *icpu,bxInstruction_c *i)
{
	Bit8u op1;
	//++++++++++++++++++++++++++++++++
	//ECX等于零时退出,否则执行
	if (RW_ECX==0)
		return;

	if (BX_CPU_CLASS_PTR cr0.pe && (BX_CPU_CLASS_PTR get_VM() || (RW_CPL>BX_CPU_CLASS_PTR get_IOPL())))
	{
		if ( !BX_CPU_CLASS_PTR allow_io(RW_DX, 1) )
		{
			BX_CPU_CLASS_PTR exception(BX_GP_EXCEPTION, 0, 0);
		}
	}

RepeatRun:

	Bit32u edi;
	edi = RW_EDI;
	op1 = 0;
	WRITE_VIRTUAL_BYTE(BX_SEG_REG_ES, edi, &op1);
	op1 = BX_CPU_CLASS_PTR BX_INP(RW_DX, 1);
	WRITE_VIRTUAL_BYTE(BX_SEG_REG_ES, edi, &op1);
	if (BX_CPU_CLASS_PTR get_DF())
	{
		edi -= 1;
	}
	else
	{
		edi += 1;
	}
	RW_EDI = edi;
	RW_ECX--;
	if (RW_ECX==0)
		return;

	if (BX_CPU_CLASS_PTR async_event)
	{
		BX_CPU_CLASS_PTR invalidate_prefetch_q();
		RW_EIP	= BX_CPU_CLASS_PTR prev_eip; // commit old EIP
		return;
	}

	goto RepeatRun;
}

	void
BX_CPU_C::INSW_YvDX_E16_rep__(BX_CPU_C *icpu,bxInstruction_c *i)
{
	Bit16u op1;
	if (BX_CPU_CLASS_PTR cr0.pe && (BX_CPU_CLASS_PTR get_VM() || (RW_CPL>BX_CPU_CLASS_PTR get_IOPL())))
	{
		if ( !BX_CPU_CLASS_PTR allow_io(RW_DX, 2) )
		{
			BX_CPU_CLASS_PTR exception(BX_GP_EXCEPTION, 0, 0);
		}
	}

	Bit32u edi;
	edi = RW_DI;
	op1 = 0;
	WRITE_VIRTUAL_WORD(BX_SEG_REG_ES, edi, &op1);
	op1 = BX_CPU_CLASS_PTR BX_INP(RW_DX, 2);
	WRITE_VIRTUAL_WORD(BX_SEG_REG_ES, edi, &op1);
	if (BX_CPU_CLASS_PTR get_DF())
	{
		edi -= 2;
	}
	else
	{
		edi += 2;
	}
	RW_DI = edi;
}

	void
BX_CPU_C::INSW_YvDX_E16_repf2(BX_CPU_C *icpu,bxInstruction_c *i)
{
	Bit16u op1;
	//++++++++++++++++++++++++++++++++
	//ECX等于零时退出,否则执行
	if (RW_CX==0)
		return;

	if (BX_CPU_CLASS_PTR cr0.pe && (BX_CPU_CLASS_PTR get_VM() || (RW_CPL>BX_CPU_CLASS_PTR get_IOPL())))
	{
		if ( !BX_CPU_CLASS_PTR allow_io(RW_DX, 2) )
		{
			BX_CPU_CLASS_PTR exception(BX_GP_EXCEPTION, 0, 0);
		}
	}

RepeatRun:

	Bit32u edi;
	edi = RW_DI;
	op1 = 0;
	WRITE_VIRTUAL_WORD(BX_SEG_REG_ES, edi, &op1);
	op1 = BX_CPU_CLASS_PTR BX_INP(RW_DX, 2);
	WRITE_VIRTUAL_WORD(BX_SEG_REG_ES, edi, &op1);
	if (BX_CPU_CLASS_PTR get_DF())
	{
		edi -= 2;
	}
	else
	{
		edi += 2;
	}
	RW_DI = edi;
	RW_CX--;
	if (RW_CX==0)
		return;

	if (BX_CPU_CLASS_PTR async_event)
	{
		BX_CPU_CLASS_PTR invalidate_prefetch_q();
		RW_EIP	= BX_CPU_CLASS_PTR prev_eip; // commit old EIP
		return;
	}

	goto RepeatRun;
}

	void
BX_CPU_C::INSW_YvDX_E16_repf3(BX_CPU_C *icpu,bxInstruction_c *i)
{
	Bit16u op1;
	//++++++++++++++++++++++++++++++++
	//ECX等于零时退出,否则执行
	if (RW_CX==0)
		return;

	if (BX_CPU_CLASS_PTR cr0.pe && (BX_CPU_CLASS_PTR get_VM() || (RW_CPL>BX_CPU_CLASS_PTR get_IOPL())))
	{
		if ( !BX_CPU_CLASS_PTR allow_io(RW_DX, 2) )
		{
			BX_CPU_CLASS_PTR exception(BX_GP_EXCEPTION, 0, 0);
		}
	}

RepeatRun:

	Bit32u edi;
	edi = RW_DI;
	op1 = 0;
	WRITE_VIRTUAL_WORD(BX_SEG_REG_ES, edi, &op1);
	op1 = BX_CPU_CLASS_PTR BX_INP(RW_DX, 2);
	WRITE_VIRTUAL_WORD(BX_SEG_REG_ES, edi, &op1);
	if (BX_CPU_CLASS_PTR get_DF())
	{
		edi -= 2;
	}
	else
	{
		edi += 2;
	}
	RW_DI = edi;
	RW_CX--;
	if (RW_CX==0)
		return;

	if (BX_CPU_CLASS_PTR async_event)
	{
		BX_CPU_CLASS_PTR invalidate_prefetch_q();
		RW_EIP	= BX_CPU_CLASS_PTR prev_eip; // commit old EIP
		return;
	}

	goto RepeatRun;
}

	void
BX_CPU_C::INSW_YvDX_E32_rep__(BX_CPU_C *icpu,bxInstruction_c *i)
{
	Bit16u op1;
	if (BX_CPU_CLASS_PTR cr0.pe && (BX_CPU_CLASS_PTR get_VM() || (RW_CPL>BX_CPU_CLASS_PTR get_IOPL())))
	{
		if ( !BX_CPU_CLASS_PTR allow_io(RW_DX, 2) )
		{
			BX_CPU_CLASS_PTR exception(BX_GP_EXCEPTION, 0, 0);
		}
	}

	Bit32u edi;
	edi = RW_EDI;
	op1 = 0;
	WRITE_VIRTUAL_WORD(BX_SEG_REG_ES, edi, &op1);
	op1 = BX_CPU_CLASS_PTR BX_INP(RW_DX, 2);
	WRITE_VIRTUAL_WORD(BX_SEG_REG_ES, edi, &op1);
	if (BX_CPU_CLASS_PTR get_DF())
	{
		edi -= 2;
	}
	else
	{
		edi += 2;
	}
	RW_EDI = edi;
}

	void
BX_CPU_C::INSW_YvDX_E32_repf2(BX_CPU_C *icpu,bxInstruction_c *i)
{
	Bit16u op1;
	//++++++++++++++++++++++++++++++++
	//ECX等于零时退出,否则执行
	if (RW_ECX==0)
		return;

	if (BX_CPU_CLASS_PTR cr0.pe && (BX_CPU_CLASS_PTR get_VM() || (RW_CPL>BX_CPU_CLASS_PTR get_IOPL())))
	{
		if ( !BX_CPU_CLASS_PTR allow_io(RW_DX, 2) )
		{
			BX_CPU_CLASS_PTR exception(BX_GP_EXCEPTION, 0, 0);
		}
	}

RepeatRun:

	Bit32u edi;
	edi = RW_EDI;
	op1 = 0;
	WRITE_VIRTUAL_WORD(BX_SEG_REG_ES, edi, &op1);
	op1 = BX_CPU_CLASS_PTR BX_INP(RW_DX, 2);
	WRITE_VIRTUAL_WORD(BX_SEG_REG_ES, edi, &op1);
	if (BX_CPU_CLASS_PTR get_DF())
	{
		edi -= 2;
	}
	else
	{
		edi += 2;
	}
	RW_EDI = edi;
	RW_ECX--;
	if (RW_ECX==0)
		return;

	if (BX_CPU_CLASS_PTR async_event)
	{
		BX_CPU_CLASS_PTR invalidate_prefetch_q();
		RW_EIP	= BX_CPU_CLASS_PTR prev_eip; // commit old EIP
		return;
	}

	goto RepeatRun;
}

	void
BX_CPU_C::INSW_YvDX_E32_repf3(BX_CPU_C *icpu,bxInstruction_c *i)
{
	Bit16u op1;
	//++++++++++++++++++++++++++++++++
	//ECX等于零时退出,否则执行
	if (RW_ECX==0)
		return;

	if (BX_CPU_CLASS_PTR cr0.pe && (BX_CPU_CLASS_PTR get_VM() || (RW_CPL>BX_CPU_CLASS_PTR get_IOPL())))
	{
		if ( !BX_CPU_CLASS_PTR allow_io(RW_DX, 2) )
		{
			BX_CPU_CLASS_PTR exception(BX_GP_EXCEPTION, 0, 0);
		}
	}

RepeatRun:

	Bit32u edi;
	edi = RW_EDI;
	op1 = 0;
	WRITE_VIRTUAL_WORD(BX_SEG_REG_ES, edi, &op1);
	op1 = BX_CPU_CLASS_PTR BX_INP(RW_DX, 2);
	WRITE_VIRTUAL_WORD(BX_SEG_REG_ES, edi, &op1);
	if (BX_CPU_CLASS_PTR get_DF())
	{
		edi -= 2;
	}
	else
	{
		edi += 2;
	}
	RW_EDI = edi;
	RW_ECX--;
	if (RW_ECX==0)
		return;

	if (BX_CPU_CLASS_PTR async_event)
	{
		BX_CPU_CLASS_PTR invalidate_prefetch_q();
		RW_EIP	= BX_CPU_CLASS_PTR prev_eip; // commit old EIP
		return;
	}

	goto RepeatRun;
}

	void
BX_CPU_C::INSD_YvDX_E16_rep__(BX_CPU_C *icpu,bxInstruction_c *i)
{
	Bit32u op1;
	if (BX_CPU_CLASS_PTR cr0.pe && (BX_CPU_CLASS_PTR get_VM() || (RW_CPL>BX_CPU_CLASS_PTR get_IOPL())))
	{
		if ( !BX_CPU_CLASS_PTR allow_io(RW_DX, 4) )
		{
			BX_CPU_CLASS_PTR exception(BX_GP_EXCEPTION, 0, 0);
		}
	}

	Bit32u edi;
	edi = RW_DI;
	op1 = 0;
	WRITE_VIRTUAL_DWORD(BX_SEG_REG_ES, edi, &op1);
	op1 = BX_CPU_CLASS_PTR BX_INP(RW_DX, 4);
	WRITE_VIRTUAL_DWORD(BX_SEG_REG_ES, edi, &op1);
	if (BX_CPU_CLASS_PTR get_DF())
	{
		edi -= 4;
	}
	else
	{
		edi += 4;
	}
	RW_DI = edi;
}

	void
BX_CPU_C::INSD_YvDX_E16_repf2(BX_CPU_C *icpu,bxInstruction_c *i)
{
	Bit32u op1;
	//++++++++++++++++++++++++++++++++
	//ECX等于零时退出,否则执行
	if (RW_CX==0)
		return;

	if (BX_CPU_CLASS_PTR cr0.pe && (BX_CPU_CLASS_PTR get_VM() || (RW_CPL>BX_CPU_CLASS_PTR get_IOPL())))
	{
		if ( !BX_CPU_CLASS_PTR allow_io(RW_DX, 4) )
		{
			BX_CPU_CLASS_PTR exception(BX_GP_EXCEPTION, 0, 0);
		}
	}

RepeatRun:

	Bit32u edi;
	edi = RW_DI;
	op1 = 0;
	WRITE_VIRTUAL_DWORD(BX_SEG_REG_ES, edi, &op1);
	op1 = BX_CPU_CLASS_PTR BX_INP(RW_DX, 4);
	WRITE_VIRTUAL_DWORD(BX_SEG_REG_ES, edi, &op1);
	if (BX_CPU_CLASS_PTR get_DF())
	{
		edi -= 4;
	}
	else
	{
		edi += 4;
	}
	RW_DI = edi;
	RW_CX--;
	if (RW_CX==0)
		return;

	if (BX_CPU_CLASS_PTR async_event)
	{
		BX_CPU_CLASS_PTR invalidate_prefetch_q();
		RW_EIP	= BX_CPU_CLASS_PTR prev_eip; // commit old EIP
		return;
	}

	goto RepeatRun;
}

	void
BX_CPU_C::INSD_YvDX_E16_repf3(BX_CPU_C *icpu,bxInstruction_c *i)
{
	Bit32u op1;
	//++++++++++++++++++++++++++++++++
	//ECX等于零时退出,否则执行
	if (RW_CX==0)
		return;

	if (BX_CPU_CLASS_PTR cr0.pe && (BX_CPU_CLASS_PTR get_VM() || (RW_CPL>BX_CPU_CLASS_PTR get_IOPL())))
	{
		if ( !BX_CPU_CLASS_PTR allow_io(RW_DX, 4) )
		{
			BX_CPU_CLASS_PTR exception(BX_GP_EXCEPTION, 0, 0);
		}
	}

RepeatRun:

	Bit32u edi;
	edi = RW_DI;
	op1 = 0;
	WRITE_VIRTUAL_DWORD(BX_SEG_REG_ES, edi, &op1);
	op1 = BX_CPU_CLASS_PTR BX_INP(RW_DX, 4);
	WRITE_VIRTUAL_DWORD(BX_SEG_REG_ES, edi, &op1);
	if (BX_CPU_CLASS_PTR get_DF())
	{
		edi -= 4;
	}
	else
	{
		edi += 4;
	}
	RW_DI = edi;
	RW_CX--;
	if (RW_CX==0)
		return;

	if (BX_CPU_CLASS_PTR async_event)
	{
		BX_CPU_CLASS_PTR invalidate_prefetch_q();
		RW_EIP	= BX_CPU_CLASS_PTR prev_eip; // commit old EIP
		return;
	}

	goto RepeatRun;
}

	void
BX_CPU_C::INSD_YvDX_E32_rep__(BX_CPU_C *icpu,bxInstruction_c *i)
{
	Bit32u op1;
	if (BX_CPU_CLASS_PTR cr0.pe && (BX_CPU_CLASS_PTR get_VM() || (RW_CPL>BX_CPU_CLASS_PTR get_IOPL())))
	{
		if ( !BX_CPU_CLASS_PTR allow_io(RW_DX, 4) )
		{
			BX_CPU_CLASS_PTR exception(BX_GP_EXCEPTION, 0, 0);
		}
	}

	Bit32u edi;
	edi = RW_EDI;
	op1 = 0;
	WRITE_VIRTUAL_DWORD(BX_SEG_REG_ES, edi, &op1);
	op1 = BX_CPU_CLASS_PTR BX_INP(RW_DX, 4);
	WRITE_VIRTUAL_DWORD(BX_SEG_REG_ES, edi, &op1);
	if (BX_CPU_CLASS_PTR get_DF())
	{
		edi -= 4;
	}
	else
	{
		edi += 4;
	}
	RW_EDI = edi;
}

	void
BX_CPU_C::INSD_YvDX_E32_repf2(BX_CPU_C *icpu,bxInstruction_c *i)
{
	Bit32u op1;
	//++++++++++++++++++++++++++++++++
	//ECX等于零时退出,否则执行
	if (RW_ECX==0)
		return;

	if (BX_CPU_CLASS_PTR cr0.pe && (BX_CPU_CLASS_PTR get_VM() || (RW_CPL>BX_CPU_CLASS_PTR get_IOPL())))
	{
		if ( !BX_CPU_CLASS_PTR allow_io(RW_DX, 4) )
		{
			BX_CPU_CLASS_PTR exception(BX_GP_EXCEPTION, 0, 0);
		}
	}

RepeatRun:

	Bit32u edi;
	edi = RW_EDI;
	op1 = 0;
	WRITE_VIRTUAL_DWORD(BX_SEG_REG_ES, edi, &op1);
	op1 = BX_CPU_CLASS_PTR BX_INP(RW_DX, 4);
	WRITE_VIRTUAL_DWORD(BX_SEG_REG_ES, edi, &op1);
	if (BX_CPU_CLASS_PTR get_DF())
	{
		edi -= 4;
	}
	else
	{
		edi += 4;
	}
	RW_EDI = edi;
	RW_ECX--;
	if (RW_ECX==0)
		return;

	if (BX_CPU_CLASS_PTR async_event)
	{
		BX_CPU_CLASS_PTR invalidate_prefetch_q();
		RW_EIP	= BX_CPU_CLASS_PTR prev_eip; // commit old EIP
		return;
	}

	goto RepeatRun;
}

	void
BX_CPU_C::INSD_YvDX_E32_repf3(BX_CPU_C *icpu,bxInstruction_c *i)
{
	Bit32u op1;
	//++++++++++++++++++++++++++++++++
	//ECX等于零时退出,否则执行
	if (RW_ECX==0)
		return;

	if (BX_CPU_CLASS_PTR cr0.pe && (BX_CPU_CLASS_PTR get_VM() || (RW_CPL>BX_CPU_CLASS_PTR get_IOPL())))
	{
		if ( !BX_CPU_CLASS_PTR allow_io(RW_DX, 4) )
		{
			BX_CPU_CLASS_PTR exception(BX_GP_EXCEPTION, 0, 0);
		}
	}

RepeatRun:

	Bit32u edi;
	edi = RW_EDI;
	op1 = 0;
	WRITE_VIRTUAL_DWORD(BX_SEG_REG_ES, edi, &op1);
	op1 = BX_CPU_CLASS_PTR BX_INP(RW_DX, 4);
	WRITE_VIRTUAL_DWORD(BX_SEG_REG_ES, edi, &op1);
	if (BX_CPU_CLASS_PTR get_DF())
	{
		edi -= 4;
	}
	else
	{
		edi += 4;
	}
	RW_EDI = edi;
	RW_ECX--;
	if (RW_ECX==0)
		return;

	if (BX_CPU_CLASS_PTR async_event)
	{
		BX_CPU_CLASS_PTR invalidate_prefetch_q();
		RW_EIP	= BX_CPU_CLASS_PTR prev_eip; // commit old EIP
		return;
	}

	goto RepeatRun;
}

