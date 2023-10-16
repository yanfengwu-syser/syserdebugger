/////////////////////////////////////////////////////////////////////////
// $Id: ctrl_xfer.cc,v 1.0 2002/10/10 04:57:05 bdenney Exp $
/////////////////////////////////////////////////////////////////////////


#include "stdafx.h"
#include "x86cpu.h"
//---------------------------------------------------------
//虚拟执行--指令微函数  无条件转移指令
//---------------------------------------------------------


	void
BX_CPU_C::CALL16_Ap(BX_CPU_C *icpu,bxInstruction_c *i)
{
	Bit32u new_eip;

	Bit16u new_cs;
	new_eip = IMMEDIATEIw(i);
	new_cs = IMMEDIATEIw2(i);
	BX_CPU_CLASS_PTR invalidate_prefetch_q();
	if (BX_CPU_CLASS_PTR protected_mode())
	{
		BX_CPU_CLASS_PTR call_protected(i,new_cs,new_eip);
		goto done;
	}
	BX_CPU_CLASS_PTR call_push_16(BX_CPU_CLASS_PTR program_visible_sregs[BX_SEG_REG_CS].selector.value);
	BX_CPU_CLASS_PTR call_push_16((Bit16u) BX_CPU_CLASS_PTR program_visible_eip);
	BX_CPU_CLASS_PTR program_visible_eip = (Bit32u) new_eip;
	BX_CPU_CLASS_PTR load_seg_reg(&BX_CPU_CLASS_PTR program_visible_sregs[BX_SEG_REG_CS],new_cs);
done:
	BX_INSTR_FAR_BRANCH(BX_INSTR_IS_CALL,
			BX_CPU_CLASS_PTR program_visible_sregs[BX_SEG_REG_CS].selector.value,
			BX_CPU_CLASS_PTR program_visible_eip);
	return ;
}

	void
BX_CPU_C::CALL32_Ap(BX_CPU_C *icpu,bxInstruction_c *i)
{
	Bit32u new_eip;

	Bit16u new_cs;
	new_eip = IMMEDIATEId(i);
	new_cs = IMMEDIATEIw2(i);
	BX_CPU_CLASS_PTR invalidate_prefetch_q();
	if (BX_CPU_CLASS_PTR protected_mode())
	{
		BX_CPU_CLASS_PTR call_protected(i,new_cs,new_eip);
		goto done;
	}
	BX_CPU_CLASS_PTR call_push_32(BX_CPU_CLASS_PTR program_visible_sregs[BX_SEG_REG_CS].selector.value);
	BX_CPU_CLASS_PTR call_push_32((Bit16u) BX_CPU_CLASS_PTR program_visible_eip);
	BX_CPU_CLASS_PTR program_visible_eip = (Bit32u) new_eip;
	BX_CPU_CLASS_PTR load_seg_reg(&BX_CPU_CLASS_PTR program_visible_sregs[BX_SEG_REG_CS],new_cs);
done:
	BX_INSTR_FAR_BRANCH(BX_INSTR_IS_CALL,
			BX_CPU_CLASS_PTR program_visible_sregs[BX_SEG_REG_CS].selector.value,
			BX_CPU_CLASS_PTR program_visible_eip);
	return ;
}

	void
BX_CPU_C::JMP16_Ap(BX_CPU_C *icpu,bxInstruction_c *i)
{
	Bit32u new_eip;

	Bit16u new_cs;
	new_eip = IMMEDIATEIw(i);
	new_cs = IMMEDIATEIw2(i);
	BX_CPU_CLASS_PTR invalidate_prefetch_q();
	if (BX_CPU_CLASS_PTR protected_mode())
	{
		BX_CPU_CLASS_PTR jump_protected(i,new_cs,new_eip);
		goto done;
	}
	BX_CPU_CLASS_PTR program_visible_eip = (Bit32u) new_eip;
	BX_CPU_CLASS_PTR load_seg_reg(&BX_CPU_CLASS_PTR program_visible_sregs[BX_SEG_REG_CS],new_cs);
done:
	BX_INSTR_FAR_BRANCH(BX_INSTR_IS_JMP,
			BX_CPU_CLASS_PTR program_visible_sregs[BX_SEG_REG_CS].selector.value,
			BX_CPU_CLASS_PTR program_visible_eip);
	return ;
}

	void
BX_CPU_C::JMP32_Ap(BX_CPU_C *icpu,bxInstruction_c *i)
{
	Bit32u new_eip;

	Bit16u new_cs;
	new_eip = IMMEDIATEId(i);
	new_cs = IMMEDIATEIw2(i);
	BX_CPU_CLASS_PTR invalidate_prefetch_q();
	if (BX_CPU_CLASS_PTR protected_mode())
	{
		BX_CPU_CLASS_PTR jump_protected(i,new_cs,new_eip);
		goto done;
	}
	BX_CPU_CLASS_PTR program_visible_eip = (Bit32u) new_eip;
	BX_CPU_CLASS_PTR load_seg_reg(&BX_CPU_CLASS_PTR program_visible_sregs[BX_SEG_REG_CS],new_cs);
done:
	BX_INSTR_FAR_BRANCH(BX_INSTR_IS_JMP,
			BX_CPU_CLASS_PTR program_visible_sregs[BX_SEG_REG_CS].selector.value,
			BX_CPU_CLASS_PTR program_visible_eip);
	return ;
}

	void
BX_CPU_C::CALL16_Ep(BX_CPU_C *icpu,bxInstruction_c *i)
{
	Bit32u new_eip;

	Bit16u new_cs;
	Bit16u aim_ip;
	READ_VIRTUAL_WORD(MODRMSeg(i),RMAddr(i),&aim_ip);
	READ_VIRTUAL_WORD(MODRMSeg(i),RMAddr(i)+2,&new_cs);
	new_eip = aim_ip;
	BX_CPU_CLASS_PTR invalidate_prefetch_q();
	if (BX_CPU_CLASS_PTR protected_mode())
	{
		BX_CPU_CLASS_PTR call_protected(i,new_cs,new_eip);
		goto done;
	}
	BX_CPU_CLASS_PTR call_push_16(BX_CPU_CLASS_PTR program_visible_sregs[BX_SEG_REG_CS].selector.value);
	BX_CPU_CLASS_PTR call_push_16((Bit16u) BX_CPU_CLASS_PTR program_visible_eip);
	BX_CPU_CLASS_PTR program_visible_eip = (Bit32u) new_eip;
	BX_CPU_CLASS_PTR load_seg_reg(&BX_CPU_CLASS_PTR program_visible_sregs[BX_SEG_REG_CS],new_cs);
done:
	BX_INSTR_FAR_BRANCH(BX_INSTR_IS_CALL,
			BX_CPU_CLASS_PTR program_visible_sregs[BX_SEG_REG_CS].selector.value,
			BX_CPU_CLASS_PTR program_visible_eip);
	return ;
}

	void
BX_CPU_C::CALL32_Ep(BX_CPU_C *icpu,bxInstruction_c *i)
{
	Bit32u new_eip;

	Bit16u new_cs;
	Bit32u aim_eip;
	READ_VIRTUAL_DWORD(MODRMSeg(i),RMAddr(i),&aim_eip);
	READ_VIRTUAL_WORD(MODRMSeg(i),RMAddr(i)+4,&new_cs);
	new_eip = aim_eip;
	BX_CPU_CLASS_PTR invalidate_prefetch_q();
	if (BX_CPU_CLASS_PTR protected_mode())
	{
		BX_CPU_CLASS_PTR call_protected(i,new_cs,new_eip);
		goto done;
	}
	BX_CPU_CLASS_PTR call_push_32(BX_CPU_CLASS_PTR program_visible_sregs[BX_SEG_REG_CS].selector.value);
	BX_CPU_CLASS_PTR call_push_32((Bit16u) BX_CPU_CLASS_PTR program_visible_eip);
	BX_CPU_CLASS_PTR program_visible_eip = (Bit32u) new_eip;
	BX_CPU_CLASS_PTR load_seg_reg(&BX_CPU_CLASS_PTR program_visible_sregs[BX_SEG_REG_CS],new_cs);
done:
	BX_INSTR_FAR_BRANCH(BX_INSTR_IS_CALL,
			BX_CPU_CLASS_PTR program_visible_sregs[BX_SEG_REG_CS].selector.value,
			BX_CPU_CLASS_PTR program_visible_eip);
	return ;
}

	void
BX_CPU_C::JMP16_Ep(BX_CPU_C *icpu,bxInstruction_c *i)
{
	Bit32u new_eip;

	Bit16u new_cs;
	Bit16u aim_ip;
	READ_VIRTUAL_WORD(MODRMSeg(i),RMAddr(i),&aim_ip);
	READ_VIRTUAL_WORD(MODRMSeg(i),RMAddr(i)+2,&new_cs);
	new_eip = aim_ip;
	BX_CPU_CLASS_PTR invalidate_prefetch_q();
	if (BX_CPU_CLASS_PTR protected_mode())
	{
		BX_CPU_CLASS_PTR jump_protected(i,new_cs,new_eip);
		goto done;
	}
	BX_CPU_CLASS_PTR program_visible_eip = (Bit32u) new_eip;
	BX_CPU_CLASS_PTR load_seg_reg(&BX_CPU_CLASS_PTR program_visible_sregs[BX_SEG_REG_CS],new_cs);
done:
	BX_INSTR_FAR_BRANCH(BX_INSTR_IS_JMP,
			BX_CPU_CLASS_PTR program_visible_sregs[BX_SEG_REG_CS].selector.value,
			BX_CPU_CLASS_PTR program_visible_eip);
	return ;
}

	void
BX_CPU_C::JMP32_Ep(BX_CPU_C *icpu,bxInstruction_c *i)
{
	Bit32u new_eip;

	Bit16u new_cs;
	Bit32u aim_eip;
	READ_VIRTUAL_DWORD(MODRMSeg(i),RMAddr(i),&aim_eip);
	READ_VIRTUAL_WORD(MODRMSeg(i),RMAddr(i)+4,&new_cs);
	new_eip = aim_eip;
	BX_CPU_CLASS_PTR invalidate_prefetch_q();
	if (BX_CPU_CLASS_PTR protected_mode())
	{
		BX_CPU_CLASS_PTR jump_protected(i,new_cs,new_eip);
		goto done;
	}
	BX_CPU_CLASS_PTR program_visible_eip = (Bit32u) new_eip;
	BX_CPU_CLASS_PTR load_seg_reg(&BX_CPU_CLASS_PTR program_visible_sregs[BX_SEG_REG_CS],new_cs);
done:
	BX_INSTR_FAR_BRANCH(BX_INSTR_IS_JMP,
			BX_CPU_CLASS_PTR program_visible_sregs[BX_SEG_REG_CS].selector.value,
			BX_CPU_CLASS_PTR program_visible_eip);
	return ;
}

	void
BX_CPU_C::JMP_EGw(BX_CPU_C *icpu,bxInstruction_c *i)
{
	Bit32u new_eip;

	new_eip = READ_VIRTUAL_16BIT_REG(MODRMrm(i));
#if BX_CPU_LEVEL >= 2
	if ( new_eip > BX_CPU_CLASS_PTR program_visible_sregs[BX_SEG_REG_CS].cache.u.segment.limit_scaled )
	{
		BX_PANIC(("JMP_EGw_routine: offset outside of CS limits"));
	    BX_CPU_CLASS_PTR exception(BX_GP_EXCEPTION, 0, 0);
	}
#endif
	BX_CPU_CLASS_PTR program_visible_eip = new_eip;
	BX_INSTR_CNEAR_BRANCH_TAKEN(new_eip);

	BX_CPU_CLASS_PTR revalidate_prefetch_q();
}

	void
BX_CPU_C::JMP_EEw(BX_CPU_C *icpu,bxInstruction_c *i)
{
	Bit32u new_eip;

	Bit16u op1;
	READ_VIRTUAL_WORD(MODRMSeg(i),RMAddr(i),&op1);
	new_eip = op1;
#if BX_CPU_LEVEL >= 2
	if ( new_eip > BX_CPU_CLASS_PTR program_visible_sregs[BX_SEG_REG_CS].cache.u.segment.limit_scaled )
	{
		BX_PANIC(("JMP_EEw_routine: offset outside of CS limits"));
	    BX_CPU_CLASS_PTR exception(BX_GP_EXCEPTION, 0, 0);
	}
#endif
	BX_CPU_CLASS_PTR program_visible_eip = new_eip;
	BX_INSTR_CNEAR_BRANCH_TAKEN(new_eip);

	BX_CPU_CLASS_PTR revalidate_prefetch_q();
}

	void
BX_CPU_C::JMP_EGd(BX_CPU_C *icpu,bxInstruction_c *i)
{
	Bit32u new_eip;

	new_eip = READ_VIRTUAL_32BIT_REG(MODRMrm(i));
#if BX_CPU_LEVEL >= 2
	if ( new_eip > BX_CPU_CLASS_PTR program_visible_sregs[BX_SEG_REG_CS].cache.u.segment.limit_scaled )
	{
		BX_PANIC(("JMP_EGd_routine: offset outside of CS limits"));
	    BX_CPU_CLASS_PTR exception(BX_GP_EXCEPTION, 0, 0);
	}
#endif
	BX_CPU_CLASS_PTR program_visible_eip = new_eip;
	BX_INSTR_CNEAR_BRANCH_TAKEN(new_eip);

	BX_CPU_CLASS_PTR revalidate_prefetch_q();
}

	void
BX_CPU_C::JMP_EEd(BX_CPU_C *icpu,bxInstruction_c *i)
{
	Bit32u new_eip;

	Bit32u op1;
	READ_VIRTUAL_DWORD(MODRMSeg(i),RMAddr(i),&op1);
	new_eip = op1;
#if BX_CPU_LEVEL >= 2
	if ( new_eip > BX_CPU_CLASS_PTR program_visible_sregs[BX_SEG_REG_CS].cache.u.segment.limit_scaled )
	{
		BX_PANIC(("JMP_EEd_routine: offset outside of CS limits"));
	    BX_CPU_CLASS_PTR exception(BX_GP_EXCEPTION, 0, 0);
	}
#endif
	BX_CPU_CLASS_PTR program_visible_eip = new_eip;
	BX_INSTR_CNEAR_BRANCH_TAKEN(new_eip);

	BX_CPU_CLASS_PTR revalidate_prefetch_q();
}

	void
BX_CPU_C::CALL_EGw(BX_CPU_C *icpu,bxInstruction_c *i)
{
	Bit32u new_eip;

	new_eip = READ_VIRTUAL_16BIT_REG(MODRMrm(i));
	BX_CPU_CLASS_PTR call_push_16((Bit16u)BX_CPU_CLASS_PTR program_visible_eip);
#if BX_CPU_LEVEL >= 2
	if ( new_eip > BX_CPU_CLASS_PTR program_visible_sregs[BX_SEG_REG_CS].cache.u.segment.limit_scaled )
	{
		BX_PANIC(("CALL_EGw_routine: offset outside of CS limits"));
	    BX_CPU_CLASS_PTR exception(BX_GP_EXCEPTION, 0, 0);
	}
#endif
	BX_CPU_CLASS_PTR program_visible_eip = new_eip;
	BX_INSTR_CNEAR_BRANCH_TAKEN(new_eip);

	BX_CPU_CLASS_PTR revalidate_prefetch_q();
}

	void
BX_CPU_C::CALL_EEw(BX_CPU_C *icpu,bxInstruction_c *i)
{
	Bit32u new_eip;

	Bit16u op1;
	READ_VIRTUAL_WORD(MODRMSeg(i),RMAddr(i),&op1);
	new_eip = op1;
	BX_CPU_CLASS_PTR call_push_16((Bit16u)BX_CPU_CLASS_PTR program_visible_eip);
#if BX_CPU_LEVEL >= 2
	if ( new_eip > BX_CPU_CLASS_PTR program_visible_sregs[BX_SEG_REG_CS].cache.u.segment.limit_scaled )
	{
		BX_PANIC(("CALL_EEw_routine: offset outside of CS limits"));
	    BX_CPU_CLASS_PTR exception(BX_GP_EXCEPTION, 0, 0);
	}
#endif
	BX_CPU_CLASS_PTR program_visible_eip = new_eip;
	BX_INSTR_CNEAR_BRANCH_TAKEN(new_eip);

	BX_CPU_CLASS_PTR revalidate_prefetch_q();
}

	void
BX_CPU_C::CALL_EGd(BX_CPU_C *icpu,bxInstruction_c *i)
{
	Bit32u new_eip;

	new_eip = READ_VIRTUAL_32BIT_REG(MODRMrm(i));
	BX_CPU_CLASS_PTR call_push_32(BX_CPU_CLASS_PTR program_visible_eip);
#if BX_CPU_LEVEL >= 2
	if ( new_eip > BX_CPU_CLASS_PTR program_visible_sregs[BX_SEG_REG_CS].cache.u.segment.limit_scaled )
	{
		BX_PANIC(("CALL_EGd_routine: offset outside of CS limits"));
	    BX_CPU_CLASS_PTR exception(BX_GP_EXCEPTION, 0, 0);
	}
#endif
	BX_CPU_CLASS_PTR program_visible_eip = new_eip;
	BX_INSTR_CNEAR_BRANCH_TAKEN(new_eip);

	BX_CPU_CLASS_PTR revalidate_prefetch_q();
}

	void
BX_CPU_C::CALL_EEd(BX_CPU_C *icpu,bxInstruction_c *i)
{
	Bit32u new_eip;

	Bit32u op1;
	READ_VIRTUAL_DWORD(MODRMSeg(i),RMAddr(i),&op1);
	new_eip = op1;
	BX_CPU_CLASS_PTR call_push_32(BX_CPU_CLASS_PTR program_visible_eip);
#if BX_CPU_LEVEL >= 2
	if ( new_eip > BX_CPU_CLASS_PTR program_visible_sregs[BX_SEG_REG_CS].cache.u.segment.limit_scaled )
	{
		BX_PANIC(("CALL_EEd_routine: offset outside of CS limits"));
	    BX_CPU_CLASS_PTR exception(BX_GP_EXCEPTION, 0, 0);
	}
#endif
	BX_CPU_CLASS_PTR program_visible_eip = new_eip;
	BX_INSTR_CNEAR_BRANCH_TAKEN(new_eip);

	BX_CPU_CLASS_PTR revalidate_prefetch_q();
}

	void
BX_CPU_C::RETnear16(BX_CPU_C *icpu,bxInstruction_c *i)
{
	Bit32u new_eip;

	Bit16u aim_ip;
	BX_CPU_CLASS_PTR pop_16(&aim_ip);
	new_eip = aim_ip;
#if BX_CPU_LEVEL >= 2
	if ( new_eip > BX_CPU_CLASS_PTR program_visible_sregs[BX_SEG_REG_CS].cache.u.segment.limit_scaled )
	{
		BX_PANIC(("RETnear16_routine: offset outside of CS limits"));
	    BX_CPU_CLASS_PTR exception(BX_GP_EXCEPTION, 0, 0);
	}
#endif
	BX_CPU_CLASS_PTR program_visible_eip = new_eip;
	BX_INSTR_CNEAR_BRANCH_TAKEN(new_eip);

	BX_CPU_CLASS_PTR revalidate_prefetch_q();
}

	void
BX_CPU_C::RETnear32(BX_CPU_C *icpu,bxInstruction_c *i)
{
	Bit32u new_eip;

	Bit32u aim_eip;
	BX_CPU_CLASS_PTR pop_32(&aim_eip);
	new_eip = aim_eip;
#if BX_CPU_LEVEL >= 2
	if ( new_eip > BX_CPU_CLASS_PTR program_visible_sregs[BX_SEG_REG_CS].cache.u.segment.limit_scaled )
	{
		BX_PANIC(("RETnear32_routine: offset outside of CS limits"));
	    BX_CPU_CLASS_PTR exception(BX_GP_EXCEPTION, 0, 0);
	}
#endif
	BX_CPU_CLASS_PTR program_visible_eip = new_eip;
	BX_INSTR_CNEAR_BRANCH_TAKEN(new_eip);

	BX_CPU_CLASS_PTR revalidate_prefetch_q();
}

	void
BX_CPU_C::RETnear16_Iw(BX_CPU_C *icpu,bxInstruction_c *i)
{
	Bit32u new_eip;

	Bit16u aim_ip;
	BX_CPU_CLASS_PTR pop_16(&aim_ip);
	new_eip = aim_ip;
	if (BX_CPU_CLASS_PTR program_visible_sregs[BX_SEG_REG_SS].cache.u.segment.d_b)
		RW_ESP += IMMEDIATEIw(i);
	else
		RW_SP  += IMMEDIATEIw(i);
#if BX_CPU_LEVEL >= 2
	if ( new_eip > BX_CPU_CLASS_PTR program_visible_sregs[BX_SEG_REG_CS].cache.u.segment.limit_scaled )
	{
		BX_PANIC(("RETnear16_Iw_routine: offset outside of CS limits"));
	    BX_CPU_CLASS_PTR exception(BX_GP_EXCEPTION, 0, 0);
	}
#endif
	BX_CPU_CLASS_PTR program_visible_eip = new_eip;
	BX_INSTR_CNEAR_BRANCH_TAKEN(new_eip);

	BX_CPU_CLASS_PTR revalidate_prefetch_q();
}

	void
BX_CPU_C::RETnear32_Iw(BX_CPU_C *icpu,bxInstruction_c *i)
{
	Bit32u new_eip;

	Bit32u aim_eip;
	BX_CPU_CLASS_PTR pop_32(&aim_eip);
	new_eip = aim_eip;
	if (BX_CPU_CLASS_PTR program_visible_sregs[BX_SEG_REG_SS].cache.u.segment.d_b)
		RW_ESP += IMMEDIATEIw(i);
	else
		RW_SP  += IMMEDIATEIw(i);
#if BX_CPU_LEVEL >= 2
	if ( new_eip > BX_CPU_CLASS_PTR program_visible_sregs[BX_SEG_REG_CS].cache.u.segment.limit_scaled )
	{
		BX_PANIC(("RETnear32_Iw_routine: offset outside of CS limits"));
	    BX_CPU_CLASS_PTR exception(BX_GP_EXCEPTION, 0, 0);
	}
#endif
	BX_CPU_CLASS_PTR program_visible_eip = new_eip;
	BX_INSTR_CNEAR_BRANCH_TAKEN(new_eip);

	BX_CPU_CLASS_PTR revalidate_prefetch_q();
}

	void
BX_CPU_C::RETfar16(BX_CPU_C *icpu,bxInstruction_c *i)
{
	Bit32u new_eip;

	BX_CPU_CLASS_PTR invalidate_prefetch_q();
	if (BX_CPU_CLASS_PTR protected_mode())
	{
		BX_CPU_CLASS_PTR return_protected(i,0);
		goto done;
	}
	Bit16u aim_ip,new_cs;
	BX_CPU_CLASS_PTR pop_16(&aim_ip);
	BX_CPU_CLASS_PTR pop_16(&new_cs);
	new_eip = aim_ip;
	BX_CPU_CLASS_PTR program_visible_eip = new_eip;
	BX_CPU_CLASS_PTR load_seg_reg(&BX_CPU_CLASS_PTR program_visible_sregs[BX_SEG_REG_CS],new_cs);
done:
	BX_INSTR_FAR_BRANCH(BX_INSTR_IS_RET,
			BX_CPU_CLASS_PTR program_visible_sregs[BX_SEG_REG_CS].selector.value,
			BX_CPU_CLASS_PTR program_visible_eip);
	return ;
}

	void
BX_CPU_C::RETfar32(BX_CPU_C *icpu,bxInstruction_c *i)
{
	Bit32u new_eip;

	BX_CPU_CLASS_PTR invalidate_prefetch_q();
	if (BX_CPU_CLASS_PTR protected_mode())
	{
		BX_CPU_CLASS_PTR return_protected(i,0);
		goto done;
	}
	Bit32u aim_eip,new_cs;
	BX_CPU_CLASS_PTR pop_32(&aim_eip);
	BX_CPU_CLASS_PTR pop_32(&new_cs);
	new_eip = aim_eip;
	BX_CPU_CLASS_PTR program_visible_eip = new_eip;
	BX_CPU_CLASS_PTR load_seg_reg(&BX_CPU_CLASS_PTR program_visible_sregs[BX_SEG_REG_CS],new_cs);
done:
	BX_INSTR_FAR_BRANCH(BX_INSTR_IS_RET,
			BX_CPU_CLASS_PTR program_visible_sregs[BX_SEG_REG_CS].selector.value,
			BX_CPU_CLASS_PTR program_visible_eip);
	return ;
}

	void
BX_CPU_C::RETfar16_Iw(BX_CPU_C *icpu,bxInstruction_c *i)
{
	Bit32u new_eip;

	BX_CPU_CLASS_PTR invalidate_prefetch_q();
	if (BX_CPU_CLASS_PTR protected_mode())
	{
		BX_CPU_CLASS_PTR return_protected(i,IMMEDIATEIw(i));
		goto done;
	}
	Bit16u aim_ip,new_cs;
	BX_CPU_CLASS_PTR pop_16(&aim_ip);
	BX_CPU_CLASS_PTR pop_16(&new_cs);
	new_eip = aim_ip;
	BX_CPU_CLASS_PTR program_visible_eip = new_eip;
	BX_CPU_CLASS_PTR load_seg_reg(&BX_CPU_CLASS_PTR program_visible_sregs[BX_SEG_REG_CS],new_cs);
	if (BX_CPU_CLASS_PTR program_visible_sregs[BX_SEG_REG_SS].cache.u.segment.d_b)
		RW_ESP += IMMEDIATEIw(i);
	else
		RW_SP  += IMMEDIATEIw(i);
done:
	BX_INSTR_FAR_BRANCH(BX_INSTR_IS_RET,
			BX_CPU_CLASS_PTR program_visible_sregs[BX_SEG_REG_CS].selector.value,
			BX_CPU_CLASS_PTR program_visible_eip);
	return ;
}

	void
BX_CPU_C::RETfar32_Iw(BX_CPU_C *icpu,bxInstruction_c *i)
{
	Bit32u new_eip;

	BX_CPU_CLASS_PTR invalidate_prefetch_q();
	if (BX_CPU_CLASS_PTR protected_mode())
	{
		BX_CPU_CLASS_PTR return_protected(i,IMMEDIATEIw(i));
		goto done;
	}
	Bit32u aim_eip,new_cs;
	BX_CPU_CLASS_PTR pop_32(&aim_eip);
	BX_CPU_CLASS_PTR pop_32(&new_cs);
	new_eip = aim_eip;
	BX_CPU_CLASS_PTR program_visible_eip = new_eip;
	BX_CPU_CLASS_PTR load_seg_reg(&BX_CPU_CLASS_PTR program_visible_sregs[BX_SEG_REG_CS],new_cs);
	if (BX_CPU_CLASS_PTR program_visible_sregs[BX_SEG_REG_SS].cache.u.segment.d_b)
		RW_ESP += IMMEDIATEIw(i);
	else
		RW_SP  += IMMEDIATEIw(i);
done:
	BX_INSTR_FAR_BRANCH(BX_INSTR_IS_RET,
			BX_CPU_CLASS_PTR program_visible_sregs[BX_SEG_REG_CS].selector.value,
			BX_CPU_CLASS_PTR program_visible_eip);
	return ;
}

	void
BX_CPU_C::IRET16(BX_CPU_C *icpu,bxInstruction_c *i)
{
	Bit32u new_eip;

	Bit16u aim_ip, new_cs,flags;
#if BX_DEBUGGER
	BX_CPU_CLASS_PTR show_flag |= Flag_iret;
	BX_CPU_CLASS_PTR show_eip = BX_CPU_CLASS_PTR program_visible_eip;
#endif
	BX_CPU_CLASS_PTR invalidate_prefetch_q();
	if (BX_CPU_CLASS_PTR v8086_mode())
	{
		// IOPL check in stack_return_from_v86()
		BX_CPU_CLASS_PTR stack_return_from_v86(i);
		goto done;
	}
#if BX_CPU_LEVEL >= 2
	if (BX_CPU_CLASS_PTR cr0.pe)
	{
		BX_CPU_CLASS_PTR iret_protected(i);
		goto done;
	}
#endif
	BX_CPU_CLASS_PTR pop_16(&aim_ip);
	BX_CPU_CLASS_PTR pop_16(&new_cs);
	BX_CPU_CLASS_PTR pop_16(&flags);
	new_eip = aim_ip;
	BX_CPU_CLASS_PTR load_seg_reg(&BX_CPU_CLASS_PTR program_visible_sregs[BX_SEG_REG_CS],new_cs);
	BX_CPU_CLASS_PTR program_visible_eip = new_eip;
	BX_CPU_CLASS_PTR write_flags(flags, /* change IOPL? */ 1, /* change IF? */ 1);
	BX_CPU_CLASS_PTR inhibit_mask |= BX_INHIBIT_INTERRUPTS | BX_INHIBIT_DEBUG;
	BX_CPU_CLASS_PTR async_event = 1;
done:
	BX_INSTR_FAR_BRANCH(BX_INSTR_IS_IRET,
			        BX_CPU_CLASS_PTR program_visible_sregs[BX_SEG_REG_CS].selector.value,
					BX_CPU_CLASS_PTR program_visible_eip);
	return ;
}

	void
BX_CPU_C::IRET32(BX_CPU_C *icpu,bxInstruction_c *i)
{
	Bit32u new_eip;

	Bit32u aim_eip,new_cs,eflags;
#if BX_DEBUGGER
	BX_CPU_CLASS_PTR show_flag |= Flag_iret;
	BX_CPU_CLASS_PTR show_eip = BX_CPU_CLASS_PTR program_visible_eip;
#endif
	BX_CPU_CLASS_PTR invalidate_prefetch_q();
	if (BX_CPU_CLASS_PTR v8086_mode())
	{
		// IOPL check in stack_return_from_v86()
		BX_CPU_CLASS_PTR stack_return_from_v86(i);
		goto done;
	}
#if BX_CPU_LEVEL >= 2
	if (BX_CPU_CLASS_PTR cr0.pe)
	{
		BX_CPU_CLASS_PTR iret_protected(i);
		goto done;
	}
#endif
	BX_ERROR(("IRET32 called when you're not in vm8086 mode or protected mode."));
	BX_ERROR(("IRET32 may not be implemented right, since it doesn't check anything."));
	BX_PANIC(("Please report that you have found a test case for BX_CPU_C::IRET32."));
	BX_CPU_CLASS_PTR pop_32(&aim_eip);
	BX_CPU_CLASS_PTR pop_32(&new_cs);
	BX_CPU_CLASS_PTR pop_32(&eflags);
	new_eip = aim_eip;
	BX_CPU_CLASS_PTR load_seg_reg(&BX_CPU_CLASS_PTR program_visible_sregs[BX_SEG_REG_CS], (Bit16u)new_cs);
	BX_CPU_CLASS_PTR program_visible_eip = new_eip;
	//FIXME: this should do (eflags & 0x257FD5) | (EFLAGS | 0x1A0000)
	BX_CPU_CLASS_PTR write_eflags(eflags, /* change IOPL? */ 1, /* change IF? */ 1, 0, 1);
	BX_CPU_CLASS_PTR inhibit_mask |= BX_INHIBIT_INTERRUPTS | BX_INHIBIT_DEBUG;
	BX_CPU_CLASS_PTR async_event = 1;
done:
	BX_INSTR_FAR_BRANCH(BX_INSTR_IS_IRET,
			        BX_CPU_CLASS_PTR program_visible_sregs[BX_SEG_REG_CS].selector.value,
					BX_CPU_CLASS_PTR program_visible_eip);
	return ;
}

