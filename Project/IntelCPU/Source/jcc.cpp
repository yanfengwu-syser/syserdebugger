/////////////////////////////////////////////////////////////////////////
// $Id: jcc.cc,v 1.0 2002/10/10 04:57:05 bdenney Exp $
/////////////////////////////////////////////////////////////////////////


#include "stdafx.h"
#include "x86cpu.h"
//---------------------------------------------------------
//虚拟执行--指令微函数  条件转移指令
//---------------------------------------------------------


	void
BX_CPU_C::Jcc0_Jw(BX_CPU_C *icpu,bxInstruction_c *i)
{
	Bit32u new_eip;

	if (BX_CPU_CLASS_PTR get_OF())
	{
		new_eip = (BX_CPU_CLASS_PTR program_visible_eip + IMMEDIATEId(i))&0x0000ffff;
#if BX_CPU_LEVEL >= 2
		if ( new_eip > BX_CPU_CLASS_PTR program_visible_sregs[BX_SEG_REG_CS].cache.u.segment.limit_scaled )
		{
			BX_PANIC(("Jcc0_Jw_routine: offset outside of CS limits"));
		    BX_CPU_CLASS_PTR exception(BX_GP_EXCEPTION, 0, 0);
		}
#endif
		BX_CPU_CLASS_PTR program_visible_eip = new_eip;
		BX_INSTR_CNEAR_BRANCH_TAKEN(new_eip);
		BX_CPU_CLASS_PTR revalidate_prefetch_q();
	}
#if BX_INSTRUMENTATION
	else
	{
		BX_INSTR_CNEAR_BRANCH_NOT_TAKEN();
	}
#endif

}

	void
BX_CPU_C::Jcc1_Jw(BX_CPU_C *icpu,bxInstruction_c *i)
{
	Bit32u new_eip;

	if (!BX_CPU_CLASS_PTR get_OF())
	{
		new_eip = (BX_CPU_CLASS_PTR program_visible_eip + IMMEDIATEId(i))&0x0000ffff;
#if BX_CPU_LEVEL >= 2
		if ( new_eip > BX_CPU_CLASS_PTR program_visible_sregs[BX_SEG_REG_CS].cache.u.segment.limit_scaled )
		{
			BX_PANIC(("Jcc1_Jw_routine: offset outside of CS limits"));
		    BX_CPU_CLASS_PTR exception(BX_GP_EXCEPTION, 0, 0);
		}
#endif
		BX_CPU_CLASS_PTR program_visible_eip = new_eip;
		BX_INSTR_CNEAR_BRANCH_TAKEN(new_eip);
		BX_CPU_CLASS_PTR revalidate_prefetch_q();
	}
#if BX_INSTRUMENTATION
	else
	{
		BX_INSTR_CNEAR_BRANCH_NOT_TAKEN();
	}
#endif

}

	void
BX_CPU_C::Jcc2_Jw(BX_CPU_C *icpu,bxInstruction_c *i)
{
	Bit32u new_eip;

	if (BX_CPU_CLASS_PTR get_CF())
	{
		new_eip = (BX_CPU_CLASS_PTR program_visible_eip + IMMEDIATEId(i))&0x0000ffff;
#if BX_CPU_LEVEL >= 2
		if ( new_eip > BX_CPU_CLASS_PTR program_visible_sregs[BX_SEG_REG_CS].cache.u.segment.limit_scaled )
		{
			BX_PANIC(("Jcc2_Jw_routine: offset outside of CS limits"));
		    BX_CPU_CLASS_PTR exception(BX_GP_EXCEPTION, 0, 0);
		}
#endif
		BX_CPU_CLASS_PTR program_visible_eip = new_eip;
		BX_INSTR_CNEAR_BRANCH_TAKEN(new_eip);
		BX_CPU_CLASS_PTR revalidate_prefetch_q();
	}
#if BX_INSTRUMENTATION
	else
	{
		BX_INSTR_CNEAR_BRANCH_NOT_TAKEN();
	}
#endif

}

	void
BX_CPU_C::Jcc3_Jw(BX_CPU_C *icpu,bxInstruction_c *i)
{
	Bit32u new_eip;

	if (!BX_CPU_CLASS_PTR get_CF())
	{
		new_eip = (BX_CPU_CLASS_PTR program_visible_eip + IMMEDIATEId(i))&0x0000ffff;
#if BX_CPU_LEVEL >= 2
		if ( new_eip > BX_CPU_CLASS_PTR program_visible_sregs[BX_SEG_REG_CS].cache.u.segment.limit_scaled )
		{
			BX_PANIC(("Jcc3_Jw_routine: offset outside of CS limits"));
		    BX_CPU_CLASS_PTR exception(BX_GP_EXCEPTION, 0, 0);
		}
#endif
		BX_CPU_CLASS_PTR program_visible_eip = new_eip;
		BX_INSTR_CNEAR_BRANCH_TAKEN(new_eip);
		BX_CPU_CLASS_PTR revalidate_prefetch_q();
	}
#if BX_INSTRUMENTATION
	else
	{
		BX_INSTR_CNEAR_BRANCH_NOT_TAKEN();
	}
#endif

}

	void
BX_CPU_C::Jcc4_Jw(BX_CPU_C *icpu,bxInstruction_c *i)
{
	Bit32u new_eip;

	if (BX_CPU_CLASS_PTR get_ZF())
	{
		new_eip = (BX_CPU_CLASS_PTR program_visible_eip + IMMEDIATEId(i))&0x0000ffff;
#if BX_CPU_LEVEL >= 2
		if ( new_eip > BX_CPU_CLASS_PTR program_visible_sregs[BX_SEG_REG_CS].cache.u.segment.limit_scaled )
		{
			BX_PANIC(("Jcc4_Jw_routine: offset outside of CS limits"));
		    BX_CPU_CLASS_PTR exception(BX_GP_EXCEPTION, 0, 0);
		}
#endif
		BX_CPU_CLASS_PTR program_visible_eip = new_eip;
		BX_INSTR_CNEAR_BRANCH_TAKEN(new_eip);
		BX_CPU_CLASS_PTR revalidate_prefetch_q();
	}
#if BX_INSTRUMENTATION
	else
	{
		BX_INSTR_CNEAR_BRANCH_NOT_TAKEN();
	}
#endif

}

	void
BX_CPU_C::Jcc5_Jw(BX_CPU_C *icpu,bxInstruction_c *i)
{
	Bit32u new_eip;

	if (!BX_CPU_CLASS_PTR get_ZF())
	{
		new_eip = (BX_CPU_CLASS_PTR program_visible_eip + IMMEDIATEId(i))&0x0000ffff;
#if BX_CPU_LEVEL >= 2
		if ( new_eip > BX_CPU_CLASS_PTR program_visible_sregs[BX_SEG_REG_CS].cache.u.segment.limit_scaled )
		{
			BX_PANIC(("Jcc5_Jw_routine: offset outside of CS limits"));
		    BX_CPU_CLASS_PTR exception(BX_GP_EXCEPTION, 0, 0);
		}
#endif
		BX_CPU_CLASS_PTR program_visible_eip = new_eip;
		BX_INSTR_CNEAR_BRANCH_TAKEN(new_eip);
		BX_CPU_CLASS_PTR revalidate_prefetch_q();
	}
#if BX_INSTRUMENTATION
	else
	{
		BX_INSTR_CNEAR_BRANCH_NOT_TAKEN();
	}
#endif

}

	void
BX_CPU_C::Jcc6_Jw(BX_CPU_C *icpu,bxInstruction_c *i)
{
	Bit32u new_eip;

	if (BX_CPU_CLASS_PTR get_CF() || BX_CPU_CLASS_PTR get_ZF())
	{
		new_eip = (BX_CPU_CLASS_PTR program_visible_eip + IMMEDIATEId(i))&0x0000ffff;
#if BX_CPU_LEVEL >= 2
		if ( new_eip > BX_CPU_CLASS_PTR program_visible_sregs[BX_SEG_REG_CS].cache.u.segment.limit_scaled )
		{
			BX_PANIC(("Jcc6_Jw_routine: offset outside of CS limits"));
		    BX_CPU_CLASS_PTR exception(BX_GP_EXCEPTION, 0, 0);
		}
#endif
		BX_CPU_CLASS_PTR program_visible_eip = new_eip;
		BX_INSTR_CNEAR_BRANCH_TAKEN(new_eip);
		BX_CPU_CLASS_PTR revalidate_prefetch_q();
	}
#if BX_INSTRUMENTATION
	else
	{
		BX_INSTR_CNEAR_BRANCH_NOT_TAKEN();
	}
#endif

}

	void
BX_CPU_C::Jcc7_Jw(BX_CPU_C *icpu,bxInstruction_c *i)
{
	Bit32u new_eip;

	if (!BX_CPU_CLASS_PTR get_CF() && !BX_CPU_CLASS_PTR get_ZF())
	{
		new_eip = (BX_CPU_CLASS_PTR program_visible_eip + IMMEDIATEId(i))&0x0000ffff;
#if BX_CPU_LEVEL >= 2
		if ( new_eip > BX_CPU_CLASS_PTR program_visible_sregs[BX_SEG_REG_CS].cache.u.segment.limit_scaled )
		{
			BX_PANIC(("Jcc7_Jw_routine: offset outside of CS limits"));
		    BX_CPU_CLASS_PTR exception(BX_GP_EXCEPTION, 0, 0);
		}
#endif
		BX_CPU_CLASS_PTR program_visible_eip = new_eip;
		BX_INSTR_CNEAR_BRANCH_TAKEN(new_eip);
		BX_CPU_CLASS_PTR revalidate_prefetch_q();
	}
#if BX_INSTRUMENTATION
	else
	{
		BX_INSTR_CNEAR_BRANCH_NOT_TAKEN();
	}
#endif

}

	void
BX_CPU_C::Jcc8_Jw(BX_CPU_C *icpu,bxInstruction_c *i)
{
	Bit32u new_eip;

	if (BX_CPU_CLASS_PTR get_SF())
	{
		new_eip = (BX_CPU_CLASS_PTR program_visible_eip + IMMEDIATEId(i))&0x0000ffff;
#if BX_CPU_LEVEL >= 2
		if ( new_eip > BX_CPU_CLASS_PTR program_visible_sregs[BX_SEG_REG_CS].cache.u.segment.limit_scaled )
		{
			BX_PANIC(("Jcc8_Jw_routine: offset outside of CS limits"));
		    BX_CPU_CLASS_PTR exception(BX_GP_EXCEPTION, 0, 0);
		}
#endif
		BX_CPU_CLASS_PTR program_visible_eip = new_eip;
		BX_INSTR_CNEAR_BRANCH_TAKEN(new_eip);
		BX_CPU_CLASS_PTR revalidate_prefetch_q();
	}
#if BX_INSTRUMENTATION
	else
	{
		BX_INSTR_CNEAR_BRANCH_NOT_TAKEN();
	}
#endif

}

	void
BX_CPU_C::Jcc9_Jw(BX_CPU_C *icpu,bxInstruction_c *i)
{
	Bit32u new_eip;

	if (!BX_CPU_CLASS_PTR get_SF())
	{
		new_eip = (BX_CPU_CLASS_PTR program_visible_eip + IMMEDIATEId(i))&0x0000ffff;
#if BX_CPU_LEVEL >= 2
		if ( new_eip > BX_CPU_CLASS_PTR program_visible_sregs[BX_SEG_REG_CS].cache.u.segment.limit_scaled )
		{
			BX_PANIC(("Jcc9_Jw_routine: offset outside of CS limits"));
		    BX_CPU_CLASS_PTR exception(BX_GP_EXCEPTION, 0, 0);
		}
#endif
		BX_CPU_CLASS_PTR program_visible_eip = new_eip;
		BX_INSTR_CNEAR_BRANCH_TAKEN(new_eip);
		BX_CPU_CLASS_PTR revalidate_prefetch_q();
	}
#if BX_INSTRUMENTATION
	else
	{
		BX_INSTR_CNEAR_BRANCH_NOT_TAKEN();
	}
#endif

}

	void
BX_CPU_C::Jcca_Jw(BX_CPU_C *icpu,bxInstruction_c *i)
{
	Bit32u new_eip;

	if (BX_CPU_CLASS_PTR get_PF())
	{
		new_eip = (BX_CPU_CLASS_PTR program_visible_eip + IMMEDIATEId(i))&0x0000ffff;
#if BX_CPU_LEVEL >= 2
		if ( new_eip > BX_CPU_CLASS_PTR program_visible_sregs[BX_SEG_REG_CS].cache.u.segment.limit_scaled )
		{
			BX_PANIC(("Jcca_Jw_routine: offset outside of CS limits"));
		    BX_CPU_CLASS_PTR exception(BX_GP_EXCEPTION, 0, 0);
		}
#endif
		BX_CPU_CLASS_PTR program_visible_eip = new_eip;
		BX_INSTR_CNEAR_BRANCH_TAKEN(new_eip);
		BX_CPU_CLASS_PTR revalidate_prefetch_q();
	}
#if BX_INSTRUMENTATION
	else
	{
		BX_INSTR_CNEAR_BRANCH_NOT_TAKEN();
	}
#endif

}

	void
BX_CPU_C::Jccb_Jw(BX_CPU_C *icpu,bxInstruction_c *i)
{
	Bit32u new_eip;

	if (!BX_CPU_CLASS_PTR get_PF())
	{
		new_eip = (BX_CPU_CLASS_PTR program_visible_eip + IMMEDIATEId(i))&0x0000ffff;
#if BX_CPU_LEVEL >= 2
		if ( new_eip > BX_CPU_CLASS_PTR program_visible_sregs[BX_SEG_REG_CS].cache.u.segment.limit_scaled )
		{
			BX_PANIC(("Jccb_Jw_routine: offset outside of CS limits"));
		    BX_CPU_CLASS_PTR exception(BX_GP_EXCEPTION, 0, 0);
		}
#endif
		BX_CPU_CLASS_PTR program_visible_eip = new_eip;
		BX_INSTR_CNEAR_BRANCH_TAKEN(new_eip);
		BX_CPU_CLASS_PTR revalidate_prefetch_q();
	}
#if BX_INSTRUMENTATION
	else
	{
		BX_INSTR_CNEAR_BRANCH_NOT_TAKEN();
	}
#endif

}

	void
BX_CPU_C::Jccc_Jw(BX_CPU_C *icpu,bxInstruction_c *i)
{
	Bit32u new_eip;

	if (BX_CPU_CLASS_PTR get_SF() != BX_CPU_CLASS_PTR get_OF())
	{
		new_eip = (BX_CPU_CLASS_PTR program_visible_eip + IMMEDIATEId(i))&0x0000ffff;
#if BX_CPU_LEVEL >= 2
		if ( new_eip > BX_CPU_CLASS_PTR program_visible_sregs[BX_SEG_REG_CS].cache.u.segment.limit_scaled )
		{
			BX_PANIC(("Jccc_Jw_routine: offset outside of CS limits"));
		    BX_CPU_CLASS_PTR exception(BX_GP_EXCEPTION, 0, 0);
		}
#endif
		BX_CPU_CLASS_PTR program_visible_eip = new_eip;
		BX_INSTR_CNEAR_BRANCH_TAKEN(new_eip);
		BX_CPU_CLASS_PTR revalidate_prefetch_q();
	}
#if BX_INSTRUMENTATION
	else
	{
		BX_INSTR_CNEAR_BRANCH_NOT_TAKEN();
	}
#endif

}

	void
BX_CPU_C::Jccd_Jw(BX_CPU_C *icpu,bxInstruction_c *i)
{
	Bit32u new_eip;

	if (BX_CPU_CLASS_PTR get_SF() == BX_CPU_CLASS_PTR get_OF())
	{
		new_eip = (BX_CPU_CLASS_PTR program_visible_eip + IMMEDIATEId(i))&0x0000ffff;
#if BX_CPU_LEVEL >= 2
		if ( new_eip > BX_CPU_CLASS_PTR program_visible_sregs[BX_SEG_REG_CS].cache.u.segment.limit_scaled )
		{
			BX_PANIC(("Jccd_Jw_routine: offset outside of CS limits"));
		    BX_CPU_CLASS_PTR exception(BX_GP_EXCEPTION, 0, 0);
		}
#endif
		BX_CPU_CLASS_PTR program_visible_eip = new_eip;
		BX_INSTR_CNEAR_BRANCH_TAKEN(new_eip);
		BX_CPU_CLASS_PTR revalidate_prefetch_q();
	}
#if BX_INSTRUMENTATION
	else
	{
		BX_INSTR_CNEAR_BRANCH_NOT_TAKEN();
	}
#endif

}

	void
BX_CPU_C::Jcce_Jw(BX_CPU_C *icpu,bxInstruction_c *i)
{
	Bit32u new_eip;

	if (BX_CPU_CLASS_PTR get_ZF() || (BX_CPU_CLASS_PTR get_SF() != BX_CPU_CLASS_PTR get_OF()))
	{
		new_eip = (BX_CPU_CLASS_PTR program_visible_eip + IMMEDIATEId(i))&0x0000ffff;
#if BX_CPU_LEVEL >= 2
		if ( new_eip > BX_CPU_CLASS_PTR program_visible_sregs[BX_SEG_REG_CS].cache.u.segment.limit_scaled )
		{
			BX_PANIC(("Jcce_Jw_routine: offset outside of CS limits"));
		    BX_CPU_CLASS_PTR exception(BX_GP_EXCEPTION, 0, 0);
		}
#endif
		BX_CPU_CLASS_PTR program_visible_eip = new_eip;
		BX_INSTR_CNEAR_BRANCH_TAKEN(new_eip);
		BX_CPU_CLASS_PTR revalidate_prefetch_q();
	}
#if BX_INSTRUMENTATION
	else
	{
		BX_INSTR_CNEAR_BRANCH_NOT_TAKEN();
	}
#endif

}

	void
BX_CPU_C::Jccf_Jw(BX_CPU_C *icpu,bxInstruction_c *i)
{
	Bit32u new_eip;

	if ((BX_CPU_CLASS_PTR get_SF() == BX_CPU_CLASS_PTR get_OF()) &&!BX_CPU_CLASS_PTR get_ZF())
	{
		new_eip = (BX_CPU_CLASS_PTR program_visible_eip + IMMEDIATEId(i))&0x0000ffff;
#if BX_CPU_LEVEL >= 2
		if ( new_eip > BX_CPU_CLASS_PTR program_visible_sregs[BX_SEG_REG_CS].cache.u.segment.limit_scaled )
		{
			BX_PANIC(("Jccf_Jw_routine: offset outside of CS limits"));
		    BX_CPU_CLASS_PTR exception(BX_GP_EXCEPTION, 0, 0);
		}
#endif
		BX_CPU_CLASS_PTR program_visible_eip = new_eip;
		BX_INSTR_CNEAR_BRANCH_TAKEN(new_eip);
		BX_CPU_CLASS_PTR revalidate_prefetch_q();
	}
#if BX_INSTRUMENTATION
	else
	{
		BX_INSTR_CNEAR_BRANCH_NOT_TAKEN();
	}
#endif

}

	void
BX_CPU_C::Jcc0_Jd(BX_CPU_C *icpu,bxInstruction_c *i)
{
	Bit32u new_eip;

	if (BX_CPU_CLASS_PTR get_OF())
	{
		new_eip = (BX_CPU_CLASS_PTR program_visible_eip + IMMEDIATEId(i));
#if BX_CPU_LEVEL >= 2
		if ( new_eip > BX_CPU_CLASS_PTR program_visible_sregs[BX_SEG_REG_CS].cache.u.segment.limit_scaled )
		{
			BX_PANIC(("Jcc0_Jd_routine: offset outside of CS limits"));
		    BX_CPU_CLASS_PTR exception(BX_GP_EXCEPTION, 0, 0);
		}
#endif
		BX_CPU_CLASS_PTR program_visible_eip = new_eip;
		BX_INSTR_CNEAR_BRANCH_TAKEN(new_eip);
		BX_CPU_CLASS_PTR revalidate_prefetch_q();
	}
#if BX_INSTRUMENTATION
	else
	{
		BX_INSTR_CNEAR_BRANCH_NOT_TAKEN();
	}
#endif

}

	void
BX_CPU_C::Jcc1_Jd(BX_CPU_C *icpu,bxInstruction_c *i)
{
	Bit32u new_eip;

	if (!BX_CPU_CLASS_PTR get_OF())
	{
		new_eip = (BX_CPU_CLASS_PTR program_visible_eip + IMMEDIATEId(i));
#if BX_CPU_LEVEL >= 2
		if ( new_eip > BX_CPU_CLASS_PTR program_visible_sregs[BX_SEG_REG_CS].cache.u.segment.limit_scaled )
		{
			BX_PANIC(("Jcc1_Jd_routine: offset outside of CS limits"));
		    BX_CPU_CLASS_PTR exception(BX_GP_EXCEPTION, 0, 0);
		}
#endif
		BX_CPU_CLASS_PTR program_visible_eip = new_eip;
		BX_INSTR_CNEAR_BRANCH_TAKEN(new_eip);
		BX_CPU_CLASS_PTR revalidate_prefetch_q();
	}
#if BX_INSTRUMENTATION
	else
	{
		BX_INSTR_CNEAR_BRANCH_NOT_TAKEN();
	}
#endif

}

	void
BX_CPU_C::Jcc2_Jd(BX_CPU_C *icpu,bxInstruction_c *i)
{
	Bit32u new_eip;

	if (BX_CPU_CLASS_PTR get_CF())
	{
		new_eip = (BX_CPU_CLASS_PTR program_visible_eip + IMMEDIATEId(i));
#if BX_CPU_LEVEL >= 2
		if ( new_eip > BX_CPU_CLASS_PTR program_visible_sregs[BX_SEG_REG_CS].cache.u.segment.limit_scaled )
		{
			BX_PANIC(("Jcc2_Jd_routine: offset outside of CS limits"));
		    BX_CPU_CLASS_PTR exception(BX_GP_EXCEPTION, 0, 0);
		}
#endif
		BX_CPU_CLASS_PTR program_visible_eip = new_eip;
		BX_INSTR_CNEAR_BRANCH_TAKEN(new_eip);
		BX_CPU_CLASS_PTR revalidate_prefetch_q();
	}
#if BX_INSTRUMENTATION
	else
	{
		BX_INSTR_CNEAR_BRANCH_NOT_TAKEN();
	}
#endif

}

	void
BX_CPU_C::Jcc3_Jd(BX_CPU_C *icpu,bxInstruction_c *i)
{
	Bit32u new_eip;

	if (!BX_CPU_CLASS_PTR get_CF())
	{
		new_eip = (BX_CPU_CLASS_PTR program_visible_eip + IMMEDIATEId(i));
#if BX_CPU_LEVEL >= 2
		if ( new_eip > BX_CPU_CLASS_PTR program_visible_sregs[BX_SEG_REG_CS].cache.u.segment.limit_scaled )
		{
			BX_PANIC(("Jcc3_Jd_routine: offset outside of CS limits"));
		    BX_CPU_CLASS_PTR exception(BX_GP_EXCEPTION, 0, 0);
		}
#endif
		BX_CPU_CLASS_PTR program_visible_eip = new_eip;
		BX_INSTR_CNEAR_BRANCH_TAKEN(new_eip);
		BX_CPU_CLASS_PTR revalidate_prefetch_q();
	}
#if BX_INSTRUMENTATION
	else
	{
		BX_INSTR_CNEAR_BRANCH_NOT_TAKEN();
	}
#endif

}

	void
BX_CPU_C::Jcc4_Jd(BX_CPU_C *icpu,bxInstruction_c *i)
{
	Bit32u new_eip;

	if (BX_CPU_CLASS_PTR get_ZF())
	{
		new_eip = (BX_CPU_CLASS_PTR program_visible_eip + IMMEDIATEId(i));
#if BX_CPU_LEVEL >= 2
		if ( new_eip > BX_CPU_CLASS_PTR program_visible_sregs[BX_SEG_REG_CS].cache.u.segment.limit_scaled )
		{
			BX_PANIC(("Jcc4_Jd_routine: offset outside of CS limits"));
		    BX_CPU_CLASS_PTR exception(BX_GP_EXCEPTION, 0, 0);
		}
#endif
		BX_CPU_CLASS_PTR program_visible_eip = new_eip;
		BX_INSTR_CNEAR_BRANCH_TAKEN(new_eip);
		BX_CPU_CLASS_PTR revalidate_prefetch_q();
	}
#if BX_INSTRUMENTATION
	else
	{
		BX_INSTR_CNEAR_BRANCH_NOT_TAKEN();
	}
#endif

}

	void
BX_CPU_C::Jcc5_Jd(BX_CPU_C *icpu,bxInstruction_c *i)
{
	Bit32u new_eip;

	if (!BX_CPU_CLASS_PTR get_ZF())
	{
		new_eip = (BX_CPU_CLASS_PTR program_visible_eip + IMMEDIATEId(i));
#if BX_CPU_LEVEL >= 2
		if ( new_eip > BX_CPU_CLASS_PTR program_visible_sregs[BX_SEG_REG_CS].cache.u.segment.limit_scaled )
		{
			BX_PANIC(("Jcc5_Jd_routine: offset outside of CS limits"));
		    BX_CPU_CLASS_PTR exception(BX_GP_EXCEPTION, 0, 0);
		}
#endif
		BX_CPU_CLASS_PTR program_visible_eip = new_eip;
		BX_INSTR_CNEAR_BRANCH_TAKEN(new_eip);
		BX_CPU_CLASS_PTR revalidate_prefetch_q();
	}
#if BX_INSTRUMENTATION
	else
	{
		BX_INSTR_CNEAR_BRANCH_NOT_TAKEN();
	}
#endif

}

	void
BX_CPU_C::Jcc6_Jd(BX_CPU_C *icpu,bxInstruction_c *i)
{
	Bit32u new_eip;

	if (BX_CPU_CLASS_PTR get_CF() || BX_CPU_CLASS_PTR get_ZF())
	{
		new_eip = (BX_CPU_CLASS_PTR program_visible_eip + IMMEDIATEId(i));
#if BX_CPU_LEVEL >= 2
		if ( new_eip > BX_CPU_CLASS_PTR program_visible_sregs[BX_SEG_REG_CS].cache.u.segment.limit_scaled )
		{
			BX_PANIC(("Jcc6_Jd_routine: offset outside of CS limits"));
		    BX_CPU_CLASS_PTR exception(BX_GP_EXCEPTION, 0, 0);
		}
#endif
		BX_CPU_CLASS_PTR program_visible_eip = new_eip;
		BX_INSTR_CNEAR_BRANCH_TAKEN(new_eip);
		BX_CPU_CLASS_PTR revalidate_prefetch_q();
	}
#if BX_INSTRUMENTATION
	else
	{
		BX_INSTR_CNEAR_BRANCH_NOT_TAKEN();
	}
#endif

}

	void
BX_CPU_C::Jcc7_Jd(BX_CPU_C *icpu,bxInstruction_c *i)
{
	Bit32u new_eip;

	if (!BX_CPU_CLASS_PTR get_CF() && !BX_CPU_CLASS_PTR get_ZF())
	{
		new_eip = (BX_CPU_CLASS_PTR program_visible_eip + IMMEDIATEId(i));
#if BX_CPU_LEVEL >= 2
		if ( new_eip > BX_CPU_CLASS_PTR program_visible_sregs[BX_SEG_REG_CS].cache.u.segment.limit_scaled )
		{
			BX_PANIC(("Jcc7_Jd_routine: offset outside of CS limits"));
		    BX_CPU_CLASS_PTR exception(BX_GP_EXCEPTION, 0, 0);
		}
#endif
		BX_CPU_CLASS_PTR program_visible_eip = new_eip;
		BX_INSTR_CNEAR_BRANCH_TAKEN(new_eip);
		BX_CPU_CLASS_PTR revalidate_prefetch_q();
	}
#if BX_INSTRUMENTATION
	else
	{
		BX_INSTR_CNEAR_BRANCH_NOT_TAKEN();
	}
#endif

}

	void
BX_CPU_C::Jcc8_Jd(BX_CPU_C *icpu,bxInstruction_c *i)
{
	Bit32u new_eip;

	if (BX_CPU_CLASS_PTR get_SF())
	{
		new_eip = (BX_CPU_CLASS_PTR program_visible_eip + IMMEDIATEId(i));
#if BX_CPU_LEVEL >= 2
		if ( new_eip > BX_CPU_CLASS_PTR program_visible_sregs[BX_SEG_REG_CS].cache.u.segment.limit_scaled )
		{
			BX_PANIC(("Jcc8_Jd_routine: offset outside of CS limits"));
		    BX_CPU_CLASS_PTR exception(BX_GP_EXCEPTION, 0, 0);
		}
#endif
		BX_CPU_CLASS_PTR program_visible_eip = new_eip;
		BX_INSTR_CNEAR_BRANCH_TAKEN(new_eip);
		BX_CPU_CLASS_PTR revalidate_prefetch_q();
	}
#if BX_INSTRUMENTATION
	else
	{
		BX_INSTR_CNEAR_BRANCH_NOT_TAKEN();
	}
#endif

}

	void
BX_CPU_C::Jcc9_Jd(BX_CPU_C *icpu,bxInstruction_c *i)
{
	Bit32u new_eip;

	if (!BX_CPU_CLASS_PTR get_SF())
	{
		new_eip = (BX_CPU_CLASS_PTR program_visible_eip + IMMEDIATEId(i));
#if BX_CPU_LEVEL >= 2
		if ( new_eip > BX_CPU_CLASS_PTR program_visible_sregs[BX_SEG_REG_CS].cache.u.segment.limit_scaled )
		{
			BX_PANIC(("Jcc9_Jd_routine: offset outside of CS limits"));
		    BX_CPU_CLASS_PTR exception(BX_GP_EXCEPTION, 0, 0);
		}
#endif
		BX_CPU_CLASS_PTR program_visible_eip = new_eip;
		BX_INSTR_CNEAR_BRANCH_TAKEN(new_eip);
		BX_CPU_CLASS_PTR revalidate_prefetch_q();
	}
#if BX_INSTRUMENTATION
	else
	{
		BX_INSTR_CNEAR_BRANCH_NOT_TAKEN();
	}
#endif

}

	void
BX_CPU_C::Jcca_Jd(BX_CPU_C *icpu,bxInstruction_c *i)
{
	Bit32u new_eip;

	if (BX_CPU_CLASS_PTR get_PF())
	{
		new_eip = (BX_CPU_CLASS_PTR program_visible_eip + IMMEDIATEId(i));
#if BX_CPU_LEVEL >= 2
		if ( new_eip > BX_CPU_CLASS_PTR program_visible_sregs[BX_SEG_REG_CS].cache.u.segment.limit_scaled )
		{
			BX_PANIC(("Jcca_Jd_routine: offset outside of CS limits"));
		    BX_CPU_CLASS_PTR exception(BX_GP_EXCEPTION, 0, 0);
		}
#endif
		BX_CPU_CLASS_PTR program_visible_eip = new_eip;
		BX_INSTR_CNEAR_BRANCH_TAKEN(new_eip);
		BX_CPU_CLASS_PTR revalidate_prefetch_q();
	}
#if BX_INSTRUMENTATION
	else
	{
		BX_INSTR_CNEAR_BRANCH_NOT_TAKEN();
	}
#endif

}

	void
BX_CPU_C::Jccb_Jd(BX_CPU_C *icpu,bxInstruction_c *i)
{
	Bit32u new_eip;

	if (!BX_CPU_CLASS_PTR get_PF())
	{
		new_eip = (BX_CPU_CLASS_PTR program_visible_eip + IMMEDIATEId(i));
#if BX_CPU_LEVEL >= 2
		if ( new_eip > BX_CPU_CLASS_PTR program_visible_sregs[BX_SEG_REG_CS].cache.u.segment.limit_scaled )
		{
			BX_PANIC(("Jccb_Jd_routine: offset outside of CS limits"));
		    BX_CPU_CLASS_PTR exception(BX_GP_EXCEPTION, 0, 0);
		}
#endif
		BX_CPU_CLASS_PTR program_visible_eip = new_eip;
		BX_INSTR_CNEAR_BRANCH_TAKEN(new_eip);
		BX_CPU_CLASS_PTR revalidate_prefetch_q();
	}
#if BX_INSTRUMENTATION
	else
	{
		BX_INSTR_CNEAR_BRANCH_NOT_TAKEN();
	}
#endif

}

	void
BX_CPU_C::Jccc_Jd(BX_CPU_C *icpu,bxInstruction_c *i)
{
	Bit32u new_eip;

	if (BX_CPU_CLASS_PTR get_SF() != BX_CPU_CLASS_PTR get_OF())
	{
		new_eip = (BX_CPU_CLASS_PTR program_visible_eip + IMMEDIATEId(i));
#if BX_CPU_LEVEL >= 2
		if ( new_eip > BX_CPU_CLASS_PTR program_visible_sregs[BX_SEG_REG_CS].cache.u.segment.limit_scaled )
		{
			BX_PANIC(("Jccc_Jd_routine: offset outside of CS limits"));
		    BX_CPU_CLASS_PTR exception(BX_GP_EXCEPTION, 0, 0);
		}
#endif
		BX_CPU_CLASS_PTR program_visible_eip = new_eip;
		BX_INSTR_CNEAR_BRANCH_TAKEN(new_eip);
		BX_CPU_CLASS_PTR revalidate_prefetch_q();
	}
#if BX_INSTRUMENTATION
	else
	{
		BX_INSTR_CNEAR_BRANCH_NOT_TAKEN();
	}
#endif

}

	void
BX_CPU_C::Jccd_Jd(BX_CPU_C *icpu,bxInstruction_c *i)
{
	Bit32u new_eip;

	if (BX_CPU_CLASS_PTR get_SF() == BX_CPU_CLASS_PTR get_OF())
	{
		new_eip = (BX_CPU_CLASS_PTR program_visible_eip + IMMEDIATEId(i));
#if BX_CPU_LEVEL >= 2
		if ( new_eip > BX_CPU_CLASS_PTR program_visible_sregs[BX_SEG_REG_CS].cache.u.segment.limit_scaled )
		{
			BX_PANIC(("Jccd_Jd_routine: offset outside of CS limits"));
		    BX_CPU_CLASS_PTR exception(BX_GP_EXCEPTION, 0, 0);
		}
#endif
		BX_CPU_CLASS_PTR program_visible_eip = new_eip;
		BX_INSTR_CNEAR_BRANCH_TAKEN(new_eip);
		BX_CPU_CLASS_PTR revalidate_prefetch_q();
	}
#if BX_INSTRUMENTATION
	else
	{
		BX_INSTR_CNEAR_BRANCH_NOT_TAKEN();
	}
#endif

}

	void
BX_CPU_C::Jcce_Jd(BX_CPU_C *icpu,bxInstruction_c *i)
{
	Bit32u new_eip;

	if (BX_CPU_CLASS_PTR get_ZF() || (BX_CPU_CLASS_PTR get_SF() != BX_CPU_CLASS_PTR get_OF()))
	{
		new_eip = (BX_CPU_CLASS_PTR program_visible_eip + IMMEDIATEId(i));
#if BX_CPU_LEVEL >= 2
		if ( new_eip > BX_CPU_CLASS_PTR program_visible_sregs[BX_SEG_REG_CS].cache.u.segment.limit_scaled )
		{
			BX_PANIC(("Jcce_Jd_routine: offset outside of CS limits"));
		    BX_CPU_CLASS_PTR exception(BX_GP_EXCEPTION, 0, 0);
		}
#endif
		BX_CPU_CLASS_PTR program_visible_eip = new_eip;
		BX_INSTR_CNEAR_BRANCH_TAKEN(new_eip);
		BX_CPU_CLASS_PTR revalidate_prefetch_q();
	}
#if BX_INSTRUMENTATION
	else
	{
		BX_INSTR_CNEAR_BRANCH_NOT_TAKEN();
	}
#endif

}

	void
BX_CPU_C::Jccf_Jd(BX_CPU_C *icpu,bxInstruction_c *i)
{
	Bit32u new_eip;

	if ((BX_CPU_CLASS_PTR get_SF() == BX_CPU_CLASS_PTR get_OF()) &&!BX_CPU_CLASS_PTR get_ZF())
	{
		new_eip = (BX_CPU_CLASS_PTR program_visible_eip + IMMEDIATEId(i));
#if BX_CPU_LEVEL >= 2
		if ( new_eip > BX_CPU_CLASS_PTR program_visible_sregs[BX_SEG_REG_CS].cache.u.segment.limit_scaled )
		{
			BX_PANIC(("Jccf_Jd_routine: offset outside of CS limits"));
		    BX_CPU_CLASS_PTR exception(BX_GP_EXCEPTION, 0, 0);
		}
#endif
		BX_CPU_CLASS_PTR program_visible_eip = new_eip;
		BX_INSTR_CNEAR_BRANCH_TAKEN(new_eip);
		BX_CPU_CLASS_PTR revalidate_prefetch_q();
	}
#if BX_INSTRUMENTATION
	else
	{
		BX_INSTR_CNEAR_BRANCH_NOT_TAKEN();
	}
#endif

}

	void
BX_CPU_C::JCXZ_Jw(BX_CPU_C *icpu,bxInstruction_c *i)
{
	Bit32u new_eip;

	if ((i->size_mode.as_32 ? RW_ECX : RW_CX)==0)
	{
		new_eip = (BX_CPU_CLASS_PTR program_visible_eip + IMMEDIATEId(i))&0x0000ffff;
#if BX_CPU_LEVEL >= 2
		if ( new_eip > BX_CPU_CLASS_PTR program_visible_sregs[BX_SEG_REG_CS].cache.u.segment.limit_scaled )
		{
			BX_PANIC(("JCXZ_Jw_routine: offset outside of CS limits"));
		    BX_CPU_CLASS_PTR exception(BX_GP_EXCEPTION, 0, 0);
		}
#endif
		BX_CPU_CLASS_PTR program_visible_eip = new_eip;
		BX_INSTR_CNEAR_BRANCH_TAKEN(new_eip);
		BX_CPU_CLASS_PTR revalidate_prefetch_q();
	}
#if BX_INSTRUMENTATION
	else
	{
		BX_INSTR_CNEAR_BRANCH_NOT_TAKEN();
	}
#endif

}

	void
BX_CPU_C::JCXZ_Jd(BX_CPU_C *icpu,bxInstruction_c *i)
{
	Bit32u new_eip;

	if ((i->size_mode.as_32 ? RW_ECX : RW_CX)==0)
	{
		new_eip = (BX_CPU_CLASS_PTR program_visible_eip + IMMEDIATEId(i));
#if BX_CPU_LEVEL >= 2
		if ( new_eip > BX_CPU_CLASS_PTR program_visible_sregs[BX_SEG_REG_CS].cache.u.segment.limit_scaled )
		{
			BX_PANIC(("JCXZ_Jd_routine: offset outside of CS limits"));
		    BX_CPU_CLASS_PTR exception(BX_GP_EXCEPTION, 0, 0);
		}
#endif
		BX_CPU_CLASS_PTR program_visible_eip = new_eip;
		BX_INSTR_CNEAR_BRANCH_TAKEN(new_eip);
		BX_CPU_CLASS_PTR revalidate_prefetch_q();
	}
#if BX_INSTRUMENTATION
	else
	{
		BX_INSTR_CNEAR_BRANCH_NOT_TAKEN();
	}
#endif

}

	void
BX_CPU_C::LOOP_Jw(BX_CPU_C *icpu,bxInstruction_c *i)
{
	Bit32u new_eip;

	Bit32u count;
#if BX_CPU_LEVEL>= 3
	if (i->size_mode.as_32)
		count = (RW_ECX-1);
	else
#endif // if BX_CPU_LEVEL >= 3
		count = (RW_CX-1);
	if ((count))
	{
		new_eip = (BX_CPU_CLASS_PTR program_visible_eip + IMMEDIATEId(i))&0x0000ffff;
#if BX_CPU_LEVEL >= 2
		if ( new_eip > BX_CPU_CLASS_PTR program_visible_sregs[BX_SEG_REG_CS].cache.u.segment.limit_scaled )
		{
			BX_PANIC(("LOOP_Jw_routine: offset outside of CS limits"));
		    BX_CPU_CLASS_PTR exception(BX_GP_EXCEPTION, 0, 0);
		}
#endif
		BX_CPU_CLASS_PTR program_visible_eip = new_eip;
		BX_INSTR_CNEAR_BRANCH_TAKEN(new_eip);
		BX_CPU_CLASS_PTR revalidate_prefetch_q();
	}
#if BX_INSTRUMENTATION
	else
	{
		BX_INSTR_CNEAR_BRANCH_NOT_TAKEN();
	}
#endif
#if BX_CPU_LEVEL>= 3
	if (i->size_mode.as_32)
		RW_ECX = count;
	else
#endif //if BX_CPU_LEVEL >= 3 
		RW_CX = (Bit16u)count;

}

	void
BX_CPU_C::LOOP_Jd(BX_CPU_C *icpu,bxInstruction_c *i)
{
	Bit32u new_eip;

	Bit32u count;
#if BX_CPU_LEVEL>= 3
	if (i->size_mode.as_32)
		count = (RW_ECX-1);
	else
#endif // if BX_CPU_LEVEL >= 3
		count = (RW_CX-1);
	if ((count))
	{
		new_eip = (BX_CPU_CLASS_PTR program_visible_eip + IMMEDIATEId(i));
#if BX_CPU_LEVEL >= 2
		if ( new_eip > BX_CPU_CLASS_PTR program_visible_sregs[BX_SEG_REG_CS].cache.u.segment.limit_scaled )
		{
			BX_PANIC(("LOOP_Jd_routine: offset outside of CS limits"));
		    BX_CPU_CLASS_PTR exception(BX_GP_EXCEPTION, 0, 0);
		}
#endif
		BX_CPU_CLASS_PTR program_visible_eip = new_eip;
		BX_INSTR_CNEAR_BRANCH_TAKEN(new_eip);
		BX_CPU_CLASS_PTR revalidate_prefetch_q();
	}
#if BX_INSTRUMENTATION
	else
	{
		BX_INSTR_CNEAR_BRANCH_NOT_TAKEN();
	}
#endif
#if BX_CPU_LEVEL>= 3
	if (i->size_mode.as_32)
		RW_ECX = count;
	else
#endif //if BX_CPU_LEVEL >= 3 
		RW_CX = (Bit16u)count;

}

	void
BX_CPU_C::LOOPE_Jw(BX_CPU_C *icpu,bxInstruction_c *i)
{
	Bit32u new_eip;

	Bit32u count;
#if BX_CPU_LEVEL>= 3
	if (i->size_mode.as_32)
		count = (RW_ECX-1);
	else
#endif // if BX_CPU_LEVEL >= 3
		count = (RW_CX-1);
	if ((count) && BX_CPU_CLASS_PTR get_ZF())
	{
		new_eip = (BX_CPU_CLASS_PTR program_visible_eip + IMMEDIATEId(i))&0x0000ffff;
#if BX_CPU_LEVEL >= 2
		if ( new_eip > BX_CPU_CLASS_PTR program_visible_sregs[BX_SEG_REG_CS].cache.u.segment.limit_scaled )
		{
			BX_PANIC(("LOOPE_Jw_routine: offset outside of CS limits"));
		    BX_CPU_CLASS_PTR exception(BX_GP_EXCEPTION, 0, 0);
		}
#endif
		BX_CPU_CLASS_PTR program_visible_eip = new_eip;
		BX_INSTR_CNEAR_BRANCH_TAKEN(new_eip);
		BX_CPU_CLASS_PTR revalidate_prefetch_q();
	}
#if BX_INSTRUMENTATION
	else
	{
		BX_INSTR_CNEAR_BRANCH_NOT_TAKEN();
	}
#endif
#if BX_CPU_LEVEL>= 3
	if (i->size_mode.as_32)
		RW_ECX = count;
	else
#endif //if BX_CPU_LEVEL >= 3 
		RW_CX = (Bit16u)count;

}

	void
BX_CPU_C::LOOPE_Jd(BX_CPU_C *icpu,bxInstruction_c *i)
{
	Bit32u new_eip;

	Bit32u count;
#if BX_CPU_LEVEL>= 3
	if (i->size_mode.as_32)
		count = (RW_ECX-1);
	else
#endif // if BX_CPU_LEVEL >= 3
		count = (RW_CX-1);
	if ((count) && BX_CPU_CLASS_PTR get_ZF())
	{
		new_eip = (BX_CPU_CLASS_PTR program_visible_eip + IMMEDIATEId(i));
#if BX_CPU_LEVEL >= 2
		if ( new_eip > BX_CPU_CLASS_PTR program_visible_sregs[BX_SEG_REG_CS].cache.u.segment.limit_scaled )
		{
			BX_PANIC(("LOOPE_Jd_routine: offset outside of CS limits"));
		    BX_CPU_CLASS_PTR exception(BX_GP_EXCEPTION, 0, 0);
		}
#endif
		BX_CPU_CLASS_PTR program_visible_eip = new_eip;
		BX_INSTR_CNEAR_BRANCH_TAKEN(new_eip);
		BX_CPU_CLASS_PTR revalidate_prefetch_q();
	}
#if BX_INSTRUMENTATION
	else
	{
		BX_INSTR_CNEAR_BRANCH_NOT_TAKEN();
	}
#endif
#if BX_CPU_LEVEL>= 3
	if (i->size_mode.as_32)
		RW_ECX = count;
	else
#endif //if BX_CPU_LEVEL >= 3 
		RW_CX = (Bit16u)count;

}

	void
BX_CPU_C::LOOPNE_Jw(BX_CPU_C *icpu,bxInstruction_c *i)
{
	Bit32u new_eip;

	Bit32u count;
#if BX_CPU_LEVEL>= 3
	if (i->size_mode.as_32)
		count = (RW_ECX-1);
	else
#endif // if BX_CPU_LEVEL >= 3
		count = (RW_CX-1);
	if ((count) && (!BX_CPU_CLASS_PTR get_ZF()))
	{
		new_eip = (BX_CPU_CLASS_PTR program_visible_eip + IMMEDIATEId(i))&0x0000ffff;
#if BX_CPU_LEVEL >= 2
		if ( new_eip > BX_CPU_CLASS_PTR program_visible_sregs[BX_SEG_REG_CS].cache.u.segment.limit_scaled )
		{
			BX_PANIC(("LOOPNE_Jw_routine: offset outside of CS limits"));
		    BX_CPU_CLASS_PTR exception(BX_GP_EXCEPTION, 0, 0);
		}
#endif
		BX_CPU_CLASS_PTR program_visible_eip = new_eip;
		BX_INSTR_CNEAR_BRANCH_TAKEN(new_eip);
		BX_CPU_CLASS_PTR revalidate_prefetch_q();
	}
#if BX_INSTRUMENTATION
	else
	{
		BX_INSTR_CNEAR_BRANCH_NOT_TAKEN();
	}
#endif
#if BX_CPU_LEVEL>= 3
	if (i->size_mode.as_32)
		RW_ECX = count;
	else
#endif //if BX_CPU_LEVEL >= 3 
		RW_CX = (Bit16u)count;

}

	void
BX_CPU_C::LOOPNE_Jd(BX_CPU_C *icpu,bxInstruction_c *i)
{
	Bit32u new_eip;

	Bit32u count;
#if BX_CPU_LEVEL>= 3
	if (i->size_mode.as_32)
		count = (RW_ECX-1);
	else
#endif // if BX_CPU_LEVEL >= 3
		count = (RW_CX-1);
	if ((count) && (!BX_CPU_CLASS_PTR get_ZF()))
	{
		new_eip = (BX_CPU_CLASS_PTR program_visible_eip + IMMEDIATEId(i));
#if BX_CPU_LEVEL >= 2
		if ( new_eip > BX_CPU_CLASS_PTR program_visible_sregs[BX_SEG_REG_CS].cache.u.segment.limit_scaled )
		{
			BX_PANIC(("LOOPNE_Jd_routine: offset outside of CS limits"));
		    BX_CPU_CLASS_PTR exception(BX_GP_EXCEPTION, 0, 0);
		}
#endif
		BX_CPU_CLASS_PTR program_visible_eip = new_eip;
		BX_INSTR_CNEAR_BRANCH_TAKEN(new_eip);
		BX_CPU_CLASS_PTR revalidate_prefetch_q();
	}
#if BX_INSTRUMENTATION
	else
	{
		BX_INSTR_CNEAR_BRANCH_NOT_TAKEN();
	}
#endif
#if BX_CPU_LEVEL>= 3
	if (i->size_mode.as_32)
		RW_ECX = count;
	else
#endif //if BX_CPU_LEVEL >= 3 
		RW_CX = (Bit16u)count;

}

	void
BX_CPU_C::JMP_Jw(BX_CPU_C *icpu,bxInstruction_c *i)
{
	Bit32u new_eip;

	if (1)
	{
		new_eip = (BX_CPU_CLASS_PTR program_visible_eip + IMMEDIATEId(i))&0x0000ffff;
#if BX_CPU_LEVEL >= 2
		if ( new_eip > BX_CPU_CLASS_PTR program_visible_sregs[BX_SEG_REG_CS].cache.u.segment.limit_scaled )
		{
			BX_PANIC(("JMP_Jw_routine: offset outside of CS limits"));
		    BX_CPU_CLASS_PTR exception(BX_GP_EXCEPTION, 0, 0);
		}
#endif
		BX_CPU_CLASS_PTR program_visible_eip = new_eip;
		BX_INSTR_CNEAR_BRANCH_TAKEN(new_eip);
		BX_CPU_CLASS_PTR revalidate_prefetch_q();

		BX_CPU_CLASS_PTR eipPageWindowSize = 0;
		BX_CPU_CLASS_PTR bytesleft = 0;

	}
#if BX_INSTRUMENTATION
	else
	{
		BX_INSTR_CNEAR_BRANCH_NOT_TAKEN();
	}
#endif

}

	void
BX_CPU_C::JMP_Jd(BX_CPU_C *icpu,bxInstruction_c *i)
{
	Bit32u new_eip;

	if (1)
	{
		new_eip = (BX_CPU_CLASS_PTR program_visible_eip + IMMEDIATEId(i));
#if BX_CPU_LEVEL >= 2
		if ( new_eip > BX_CPU_CLASS_PTR program_visible_sregs[BX_SEG_REG_CS].cache.u.segment.limit_scaled )
		{
			BX_PANIC(("JMP_Jd_routine: offset outside of CS limits"));
		    BX_CPU_CLASS_PTR exception(BX_GP_EXCEPTION, 0, 0);
		}
#endif
		BX_CPU_CLASS_PTR program_visible_eip = new_eip;
		BX_INSTR_CNEAR_BRANCH_TAKEN(new_eip);
		BX_CPU_CLASS_PTR revalidate_prefetch_q();

		BX_CPU_CLASS_PTR eipPageWindowSize = 0;
		BX_CPU_CLASS_PTR bytesleft = 0;
	}
#if BX_INSTRUMENTATION
	else
	{
		BX_INSTR_CNEAR_BRANCH_NOT_TAKEN();
	}
#endif

}

	void
BX_CPU_C::CALL_Jw(BX_CPU_C *icpu,bxInstruction_c *i)
{
	Bit32u new_eip;

	BX_CPU_CLASS_PTR call_push_16((Bit16u)(BX_CPU_CLASS_PTR program_visible_eip));
	if (1)
	{
		new_eip = (BX_CPU_CLASS_PTR program_visible_eip + IMMEDIATEId(i))&0x0000ffff;
#if BX_CPU_LEVEL >= 2
		if ( new_eip > BX_CPU_CLASS_PTR program_visible_sregs[BX_SEG_REG_CS].cache.u.segment.limit_scaled )
		{
			BX_PANIC(("CALL_Jw_routine: offset outside of CS limits"));
		    BX_CPU_CLASS_PTR exception(BX_GP_EXCEPTION, 0, 0);
		}
#endif
		BX_CPU_CLASS_PTR program_visible_eip = new_eip;
		BX_INSTR_CNEAR_BRANCH_TAKEN(new_eip);
		BX_CPU_CLASS_PTR revalidate_prefetch_q();

		BX_CPU_CLASS_PTR eipPageWindowSize = 0;
		BX_CPU_CLASS_PTR bytesleft = 0;
	}
#if BX_INSTRUMENTATION
	else
	{
		BX_INSTR_CNEAR_BRANCH_NOT_TAKEN();
	}
#endif

}

	void
BX_CPU_C::CALL_Jd(BX_CPU_C *icpu,bxInstruction_c *i)
{
	Bit32u new_eip;

	BX_CPU_CLASS_PTR call_push_32(BX_CPU_CLASS_PTR program_visible_eip);
	if (1)
	{
		new_eip = (BX_CPU_CLASS_PTR program_visible_eip + IMMEDIATEId(i));
#if BX_CPU_LEVEL >= 2
		if ( new_eip > BX_CPU_CLASS_PTR program_visible_sregs[BX_SEG_REG_CS].cache.u.segment.limit_scaled )
		{
			BX_PANIC(("CALL_Jd_routine: offset outside of CS limits"));
		    BX_CPU_CLASS_PTR exception(BX_GP_EXCEPTION, 0, 0);
		}
#endif
		BX_CPU_CLASS_PTR program_visible_eip = new_eip;
		BX_INSTR_CNEAR_BRANCH_TAKEN(new_eip);
		BX_CPU_CLASS_PTR revalidate_prefetch_q();

		BX_CPU_CLASS_PTR eipPageWindowSize = 0;
		BX_CPU_CLASS_PTR bytesleft = 0;
	}
#if BX_INSTRUMENTATION
	else
	{
		BX_INSTR_CNEAR_BRANCH_NOT_TAKEN();
	}
#endif

}

