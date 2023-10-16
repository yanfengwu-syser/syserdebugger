/////////////////////////////////////////////////////////////////////////
// $Id: segment_ctrl.cc,v 1.6 2001/10/03 13:10:37 bdenney Exp $
/////////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "x86cpu.h"

	void
BX_CPU_C::MOV_EwSw(BX_CPU_C *icpu,bxInstruction_c *i)
{
	Bit16u seg_reg;

#if BX_CPU_LEVEL < 3
	BX_PANIC(("MOV_EwSw: incomplete for CPU < 3"));
#endif

	if (MODRMnnn(i)>=0x06)
	{
		BX_PANIC(("MOV_EwSw: incomplete MODRMnnn(i) >= 6"));
		UndefinedOpcode(icpu,i);
	}

	seg_reg = BX_CPU_CLASS_PTR program_visible_sregs[MODRMnnn(i)].selector.value;

	if (i->modC0())
	{
		// ??? WRITE_VIRTUAL_16BIT_REG(mem_addr, seg_reg);
		if ( i->size_mode.os_32 )
		{
			// mov eax,ds
			WRITE_VIRTUAL_32BIT_REG(MODRMrm(i), seg_reg);
		}
		else
		{
			//mov ax,ds
			WRITE_VIRTUAL_16BIT_REG(MODRMrm(i), seg_reg);
		}
    }
	else
	{
		BX_CPU_CLASS_PTR write_virtual_word(MODRMSeg(i), RMAddr(i), &seg_reg);
    }
}

	void
BX_CPU_C::MOV_SwEw(BX_CPU_C *icpu,bxInstruction_c *i)
{
	Bit16u op2_16;

#if BX_CPU_LEVEL < 3
	BX_PANIC(("MOV_SwEw: incomplete for CPU < 3"));
#endif

	if (MODRMnnn(i)>=6||MODRMnnn(i)==1)
	{
		BX_PANIC(("MOV_EwSw: incomplete MODRMnnn(i) >= 6 or MODRMnnn(i) ==1"));
		UndefinedOpcode(icpu,i);
	}

	if (i->modC0())
	{
		op2_16 = READ_VIRTUAL_16BIT_REG(MODRMrm(i));
    }
	else
	{
		BX_CPU_CLASS_PTR read_virtual_word(MODRMSeg(i), RMAddr(i), &op2_16);
    }

	BX_CPU_CLASS_PTR load_seg_reg(&BX_CPU_CLASS_PTR program_visible_sregs[MODRMnnn(i)], op2_16);

	if (MODRMnnn(i) == BX_SEG_REG_SS)
	{
    // MOV SS inhibits interrupts, debug exceptions and single-step
    // trap exceptions until the execution boundary following the
    // next instruction is reached.
    // Same code as POP_SS()
		BX_CPU_CLASS_PTR inhibit_mask |=
			BX_INHIBIT_INTERRUPTS | BX_INHIBIT_DEBUG;
		BX_CPU_CLASS_PTR async_event = 1;
    }
}

	void
BX_CPU_C::PUSH_CS(BX_CPU_C *icpu,bxInstruction_c *i)
{
	if (i->size_mode.os_32)
		BX_CPU_CLASS_PTR push_32(BX_CPU_CLASS_PTR program_visible_sregs[BX_SEG_REG_CS].selector.value);
	else
		BX_CPU_CLASS_PTR push_16(BX_CPU_CLASS_PTR program_visible_sregs[BX_SEG_REG_CS].selector.value);
}
	void
BX_CPU_C::PUSH_DS(BX_CPU_C *icpu,bxInstruction_c *i)
{
	if (i->size_mode.os_32)
		BX_CPU_CLASS_PTR push_32(BX_CPU_CLASS_PTR program_visible_sregs[BX_SEG_REG_DS].selector.value);
	else
		BX_CPU_CLASS_PTR push_16(BX_CPU_CLASS_PTR program_visible_sregs[BX_SEG_REG_DS].selector.value);
}
	void
BX_CPU_C::PUSH_ES(BX_CPU_C *icpu,bxInstruction_c *i)
{
	if (i->size_mode.os_32)
		BX_CPU_CLASS_PTR push_32(BX_CPU_CLASS_PTR program_visible_sregs[BX_SEG_REG_ES].selector.value);
	else
		BX_CPU_CLASS_PTR push_16(BX_CPU_CLASS_PTR program_visible_sregs[BX_SEG_REG_ES].selector.value);
}
	void
BX_CPU_C::PUSH_FS(BX_CPU_C *icpu,bxInstruction_c *i)
{
	if (i->size_mode.os_32)
		BX_CPU_CLASS_PTR push_32(BX_CPU_CLASS_PTR program_visible_sregs[BX_SEG_REG_FS].selector.value);
	else
		BX_CPU_CLASS_PTR push_16(BX_CPU_CLASS_PTR program_visible_sregs[BX_SEG_REG_FS].selector.value);
}
	void
BX_CPU_C::PUSH_GS(BX_CPU_C *icpu,bxInstruction_c *i)
{
	if (i->size_mode.os_32)
		BX_CPU_CLASS_PTR push_32(BX_CPU_CLASS_PTR program_visible_sregs[BX_SEG_REG_GS].selector.value);
	else
		BX_CPU_CLASS_PTR push_16(BX_CPU_CLASS_PTR program_visible_sregs[BX_SEG_REG_GS].selector.value);
}
	void
BX_CPU_C::PUSH_SS(BX_CPU_C *icpu,bxInstruction_c *i)
{
	if (i->size_mode.os_32)
		BX_CPU_CLASS_PTR push_32(BX_CPU_CLASS_PTR program_visible_sregs[BX_SEG_REG_SS].selector.value);
	else
		BX_CPU_CLASS_PTR push_16(BX_CPU_CLASS_PTR program_visible_sregs[BX_SEG_REG_SS].selector.value);
}

	void
BX_CPU_C::POP_DS(BX_CPU_C *icpu,bxInstruction_c *i)
{
	if (i->size_mode.os_32)
	{	/* 32 bit operand size */
		Bit32u ds;
		BX_CPU_CLASS_PTR pop_32(&ds);
		BX_CPU_CLASS_PTR load_seg_reg(&BX_CPU_CLASS_PTR program_visible_sregs[BX_SEG_REG_DS], (Bit16u) ds);
    }
	else
	{	/* 16 bit operand size */
		Bit16u ds;
		BX_CPU_CLASS_PTR pop_16(&ds);
		BX_CPU_CLASS_PTR load_seg_reg(&BX_CPU_CLASS_PTR program_visible_sregs[BX_SEG_REG_DS], ds);
    }
}
	void
BX_CPU_C::POP_ES(BX_CPU_C *icpu,bxInstruction_c *i)
{
	if (i->size_mode.os_32)
	{	/* 32 bit operand size */
		Bit32u es;
		BX_CPU_CLASS_PTR pop_32(&es);
		BX_CPU_CLASS_PTR load_seg_reg(&BX_CPU_CLASS_PTR program_visible_sregs[BX_SEG_REG_ES], (Bit16u) es);
    }
	else
	{	/* 16 bit operand size */
		Bit16u es;
		BX_CPU_CLASS_PTR pop_16(&es);
		BX_CPU_CLASS_PTR load_seg_reg(&BX_CPU_CLASS_PTR program_visible_sregs[BX_SEG_REG_ES], es);
    }
}
	void
BX_CPU_C::POP_FS(BX_CPU_C *icpu,bxInstruction_c *i)
{
	if (i->size_mode.os_32)
	{	/* 32 bit operand size */
		Bit32u fs;
		BX_CPU_CLASS_PTR pop_32(&fs);
		BX_CPU_CLASS_PTR load_seg_reg(&BX_CPU_CLASS_PTR program_visible_sregs[BX_SEG_REG_FS], (Bit16u) fs);
    }
	else
	{	/* 16 bit operand size */
		Bit16u fs;
		BX_CPU_CLASS_PTR pop_16(&fs);
		BX_CPU_CLASS_PTR load_seg_reg(&BX_CPU_CLASS_PTR program_visible_sregs[BX_SEG_REG_FS], fs);
    }
}
	void
BX_CPU_C::POP_GS(BX_CPU_C *icpu,bxInstruction_c *i)
{
	if (i->size_mode.os_32)
	{	/* 32 bit operand size */
		Bit32u gs;
		BX_CPU_CLASS_PTR pop_32(&gs);
		BX_CPU_CLASS_PTR load_seg_reg(&BX_CPU_CLASS_PTR program_visible_sregs[BX_SEG_REG_GS], (Bit16u) gs);
    }
	else
	{	/* 16 bit operand size */
		Bit16u gs;
		BX_CPU_CLASS_PTR pop_16(&gs);
		BX_CPU_CLASS_PTR load_seg_reg(&BX_CPU_CLASS_PTR program_visible_sregs[BX_SEG_REG_GS], gs);
    }
}

	void
BX_CPU_C::POP_SS(BX_CPU_C *icpu,bxInstruction_c *i)
{
	if (i->size_mode.os_32)
	{	/* 32 bit operand size */
		Bit32u ss;
		BX_CPU_CLASS_PTR pop_32(&ss);
		BX_CPU_CLASS_PTR load_seg_reg(&BX_CPU_CLASS_PTR program_visible_sregs[BX_SEG_REG_SS], (Bit16u) ss);
    }
	else
	{	/* 16 bit operand size */
		Bit16u ss;
		BX_CPU_CLASS_PTR pop_16(&ss);
		BX_CPU_CLASS_PTR load_seg_reg(&BX_CPU_CLASS_PTR program_visible_sregs[BX_SEG_REG_SS], ss);
    }

	// POP SS inhibits interrupts, debug exceptions and single-step
	// trap exceptions until the execution boundary following the
	// next instruction is reached.
	// Same code as MOV_SwEw()
	BX_CPU_CLASS_PTR inhibit_mask |=
		BX_INHIBIT_INTERRUPTS | BX_INHIBIT_DEBUG;
	BX_CPU_CLASS_PTR async_event = 1;
}

	void
BX_CPU_C::LES_GvMp(BX_CPU_C *icpu,bxInstruction_c *i)
{
	if (i->modC0())
	{
		// (BW) NT seems to use this when booting.
		BX_INFO(("invalid use of LES, must use memory reference!"));
		UndefinedOpcode(icpu,i);
    }

#if BX_CPU_LEVEL > 2
	if (i->size_mode.os_32)
	{	/* 32 bit operand size */
		Bit16u es;
		Bit32u reg_32;

		BX_CPU_CLASS_PTR read_virtual_dword(MODRMSeg(i), RMAddr(i), &reg_32);
		BX_CPU_CLASS_PTR read_virtual_word(MODRMSeg(i), RMAddr(i) + 4, &es);

		BX_CPU_CLASS_PTR load_seg_reg(&BX_CPU_CLASS_PTR program_visible_sregs[BX_SEG_REG_ES], es);

	    WRITE_VIRTUAL_32BIT_REG(MODRMnnn(i), reg_32);
	}
	else
#endif /* BX_CPU_LEVEL > 2 */
    {	/* 16 bit mode */
		Bit16u reg_16, es;

		BX_CPU_CLASS_PTR read_virtual_word(MODRMSeg(i), RMAddr(i), &reg_16);
		BX_CPU_CLASS_PTR read_virtual_word(MODRMSeg(i), RMAddr(i) + 2, &es);

		BX_CPU_CLASS_PTR load_seg_reg(&BX_CPU_CLASS_PTR program_visible_sregs[BX_SEG_REG_ES], es);

		WRITE_VIRTUAL_16BIT_REG(MODRMnnn(i), reg_16);
    }
}

	void
BX_CPU_C::LDS_GvMp(BX_CPU_C *icpu,bxInstruction_c *i)
{
	if (i->modC0())
	{
		BX_PANIC(("invalid use of LDS, must use memory reference!"));
		UndefinedOpcode(icpu,i);
    }

#if BX_CPU_LEVEL > 2
	if (i->size_mode.os_32)
	{	/* 32 bit operand size */
		Bit16u ds;
		Bit32u reg_32;

		BX_CPU_CLASS_PTR read_virtual_dword(MODRMSeg(i), RMAddr(i), &reg_32);
		BX_CPU_CLASS_PTR read_virtual_word(MODRMSeg(i), RMAddr(i) + 4, &ds);

		BX_CPU_CLASS_PTR load_seg_reg(&BX_CPU_CLASS_PTR program_visible_sregs[BX_SEG_REG_DS], ds);

		WRITE_VIRTUAL_32BIT_REG(MODRMnnn(i), reg_32);
    }
	else
#endif /* BX_CPU_LEVEL > 2 */
    {	/* 16 bit mode */
		Bit16u reg_16, ds;

		BX_CPU_CLASS_PTR read_virtual_word(MODRMSeg(i), RMAddr(i), &reg_16);
		BX_CPU_CLASS_PTR read_virtual_word(MODRMSeg(i), RMAddr(i) + 2, &ds);

		BX_CPU_CLASS_PTR load_seg_reg(&BX_CPU_CLASS_PTR program_visible_sregs[BX_SEG_REG_DS], ds);

		WRITE_VIRTUAL_16BIT_REG(MODRMnnn(i), reg_16);
    }
}

	void
BX_CPU_C::LFS_GvMp(BX_CPU_C *icpu,bxInstruction_c *i)
{
#if BX_CPU_LEVEL < 3
	BX_PANIC(("lfs_gvmp: not supported on 8086"));
#else /* 386+ */

	if (i->modC0())
		{
		BX_PANIC(("invalid use of LFS, must use memory reference!"));
		UndefinedOpcode(icpu,i);
    }

	if (i->size_mode.os_32)
	{	/* 32 bit operand size */
		Bit32u reg_32;
		Bit16u fs;

		BX_CPU_CLASS_PTR read_virtual_dword(MODRMSeg(i), RMAddr(i), &reg_32);
		BX_CPU_CLASS_PTR read_virtual_word(MODRMSeg(i), RMAddr(i) + 4, &fs);

		BX_CPU_CLASS_PTR load_seg_reg(&BX_CPU_CLASS_PTR program_visible_sregs[BX_SEG_REG_FS], fs);

		WRITE_VIRTUAL_32BIT_REG(MODRMnnn(i), reg_32);
    }
	else
	{	/* 16 bit operand size */
		Bit16u reg_16;
		Bit16u fs;

		BX_CPU_CLASS_PTR read_virtual_word(MODRMSeg(i), RMAddr(i), &reg_16);
		BX_CPU_CLASS_PTR read_virtual_word(MODRMSeg(i), RMAddr(i) + 2, &fs);

	    BX_CPU_CLASS_PTR load_seg_reg(&BX_CPU_CLASS_PTR program_visible_sregs[BX_SEG_REG_FS], fs);

		WRITE_VIRTUAL_16BIT_REG(MODRMnnn(i), reg_16);
    }
#endif
}

	void
BX_CPU_C::LGS_GvMp(BX_CPU_C *icpu,bxInstruction_c *i)
{
#if BX_CPU_LEVEL < 3
	BX_PANIC(("lgs_gvmp: not supported on 8086"));
#else /* 386+ */

	if (i->modC0())
	{
		BX_PANIC(("invalid use of LGS, must use memory reference!"));
		UndefinedOpcode(icpu,i);
    }

	if (i->size_mode.os_32)
	{	/* 32 bit operand size */
		Bit32u reg_32;
		Bit16u gs;

		BX_CPU_CLASS_PTR read_virtual_dword(MODRMSeg(i), RMAddr(i), &reg_32);
		BX_CPU_CLASS_PTR read_virtual_word(MODRMSeg(i), RMAddr(i) + 4, &gs);

		BX_CPU_CLASS_PTR load_seg_reg(&BX_CPU_CLASS_PTR program_visible_sregs[BX_SEG_REG_GS], gs);

		WRITE_VIRTUAL_32BIT_REG(MODRMnnn(i), reg_32);
    }
	else
	{	/* 16 bit operand size */
		Bit16u reg_16;
		Bit16u gs;

		BX_CPU_CLASS_PTR read_virtual_word(MODRMSeg(i), RMAddr(i), &reg_16);
		BX_CPU_CLASS_PTR read_virtual_word(MODRMSeg(i), RMAddr(i) + 2, &gs);

		BX_CPU_CLASS_PTR load_seg_reg(&BX_CPU_CLASS_PTR program_visible_sregs[BX_SEG_REG_GS], gs);

		WRITE_VIRTUAL_16BIT_REG(MODRMnnn(i), reg_16);
    }
#endif
}

	void
BX_CPU_C::LSS_GvMp(BX_CPU_C *icpu,bxInstruction_c *i)
{
#if BX_CPU_LEVEL < 3
	BX_PANIC(("lss_gvmp: not supported on 8086"));
#else /* 386+ */

	if (i->modC0())
	{
		BX_PANIC(("invalid use of LSS, must use memory reference!"));
		UndefinedOpcode(icpu,i);
    }

	if (i->size_mode.os_32)
	{	/* 32 bit operand size */
		Bit32u reg_32;
		Bit16u ss_raw;

		BX_CPU_CLASS_PTR read_virtual_dword(MODRMSeg(i), RMAddr(i), &reg_32);
		BX_CPU_CLASS_PTR read_virtual_word(MODRMSeg(i), RMAddr(i) + 4, &ss_raw);

		BX_CPU_CLASS_PTR load_seg_reg(&BX_CPU_CLASS_PTR program_visible_sregs[BX_SEG_REG_SS], ss_raw);

		WRITE_VIRTUAL_32BIT_REG(MODRMnnn(i), reg_32);
    }
	else
	{	/* 16 bit operand size */
		Bit16u reg_16;
		Bit16u ss_raw;

		BX_CPU_CLASS_PTR read_virtual_word(MODRMSeg(i), RMAddr(i), &reg_16);
		BX_CPU_CLASS_PTR read_virtual_word(MODRMSeg(i), RMAddr(i) + 2, &ss_raw);

		BX_CPU_CLASS_PTR load_seg_reg(&BX_CPU_CLASS_PTR program_visible_sregs[BX_SEG_REG_SS], ss_raw);

		WRITE_VIRTUAL_16BIT_REG(MODRMnnn(i), reg_16);
    }
#endif
}
