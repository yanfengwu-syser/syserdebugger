/////////////////////////////////////////////////////////////////////////
// $Id: stack16.cc,v 1.7 2001/10/03 13:10:37 bdenney Exp $
/////////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "x86cpu.h"

	void
BX_CPU_C::PUSH_RX(BX_CPU_C *icpu,bxInstruction_c *i)
{
	BX_CPU_CLASS_PTR push_16( BX_CPU_CLASS_PTR program_visible_gen_reg[OPCODEb1(i) & 0x07].word.rx );
}

	void
BX_CPU_C::POP_RX(BX_CPU_C *icpu,bxInstruction_c *i)
{
	Bit16u rx;

	BX_CPU_CLASS_PTR pop_16(&rx);
	BX_CPU_CLASS_PTR program_visible_gen_reg[OPCODEb1(i) & 0x07].word.rx = rx;
}

	void
BX_CPU_C::POP_EGw(BX_CPU_C *icpu,bxInstruction_c *i)
{
	Bit16u val16;

	if (MODRMnnn(i)!=0)
	{
		BX_PANIC(("POP_Ew: incomplete MODRMnnn(i) !=0"));
		BX_CPU_CLASS_PTR UndefinedOpcode(icpu,i);
	}

	BX_CPU_CLASS_PTR pop_16(&val16);

	if (i->modC0())
	{
		WRITE_VIRTUAL_16BIT_REG(MODRMrm(i), val16);
    }
	else
	{
		// Note: there is one little weirdism here.  When 32bit addressing
		// is used, it is possible to use ESP in the modrm addressing.
		// If used, the value of ESP after the pop is used to calculate
		// the address.
		if (i->size_mode.as_32&&MODRMrm(i)==4)
		{
			// call method on BX_CPU_C object
			BX_CPU_CALL_METHOD(i->ResolveModrm, (icpu,i));
		}
	    BX_CPU_CLASS_PTR write_virtual_word(MODRMSeg(i), RMAddr(i), &val16);
    }
}

	void
BX_CPU_C::POP_EEw(BX_CPU_C *icpu,bxInstruction_c *i)
{
	Bit16u val16;

	if (MODRMnnn(i)!=0)
	{
		BX_PANIC(("POP_Ew: incomplete MODRMnnn(i) !=0"));
		BX_CPU_CLASS_PTR UndefinedOpcode(icpu,i);
	}

	BX_CPU_CLASS_PTR pop_16(&val16);

	if (i->modC0())
	{
		WRITE_VIRTUAL_16BIT_REG(MODRMrm(i), val16);
    }
	else
	{
		// Note: there is one little weirdism here.  When 32bit addressing
		// is used, it is possible to use ESP in the modrm addressing.
		// If used, the value of ESP after the pop is used to calculate
		// the address.
		if (i->size_mode.as_32&&MODRMrm(i)==4)
		{
			// call method on BX_CPU_C object
			BX_CPU_CALL_METHOD(i->ResolveModrm, (icpu,i));
		}
	    BX_CPU_CLASS_PTR write_virtual_word(MODRMSeg(i), RMAddr(i), &val16);
    }
}

	void
BX_CPU_C::PUSHAD16(BX_CPU_C *icpu,bxInstruction_c *i)
{
#if BX_CPU_LEVEL < 2
	BX_PANIC(("PUSHAD: not supported on an 8086"));
#else
	Bit32u temp_ESP;
	Bit16u sp;

	if (BX_CPU_CLASS_PTR program_visible_sregs[BX_SEG_REG_SS].cache.u.segment.d_b)
		temp_ESP = RW_ESP;
	else
		temp_ESP = RW_SP;

#if BX_CPU_LEVEL >= 2
    if (BX_CPU_CLASS_PTR protected_mode()) {
      if ( !BX_CPU_CLASS_PTR can_push(&BX_CPU_CLASS_PTR program_visible_sregs[BX_SEG_REG_SS].cache, temp_ESP, 16) ) {
        BX_PANIC(("PUSHA(): stack doesn't have enough room!"));
        BX_CPU_CLASS_PTR exception(BX_SS_EXCEPTION, 0, 0);
        return;
        }
      }
    else
#endif
      {
      if (temp_ESP < 16)
        BX_PANIC(("pushad: eSP < 16"));
      }

    sp = RW_SP;

    /* ??? optimize this by using virtual write, all checks passed */
    BX_CPU_CLASS_PTR push_16(RW_AX);
    BX_CPU_CLASS_PTR push_16(RW_CX);
    BX_CPU_CLASS_PTR push_16(RW_DX);
    BX_CPU_CLASS_PTR push_16(RW_BX);
    BX_CPU_CLASS_PTR push_16(sp);
    BX_CPU_CLASS_PTR push_16(RW_BP);
    BX_CPU_CLASS_PTR push_16(RW_SI);
    BX_CPU_CLASS_PTR push_16(RW_DI);
#endif
}

  void
BX_CPU_C::POPAD16(BX_CPU_C *icpu,bxInstruction_c *i)
{
#if BX_CPU_LEVEL < 2
	BX_PANIC(("POPAD not supported on an 8086"));
#else /* 286+ */

    Bit16u di, si, bp, sp, bx, dx, cx, ax;

    if (BX_CPU_CLASS_PTR protected_mode()) {
      if ( !BX_CPU_CLASS_PTR can_pop(16) ) {
        BX_PANIC(("pop_a: not enough bytes on stack"));
        BX_CPU_CLASS_PTR exception(BX_SS_EXCEPTION, 0, 0);
        return;
        }
      }

    /* ??? optimize this */
    BX_CPU_CLASS_PTR pop_16(&di);
    BX_CPU_CLASS_PTR pop_16(&si);
    BX_CPU_CLASS_PTR pop_16(&bp);
    BX_CPU_CLASS_PTR pop_16(&sp); /* value for SP discarded */
    BX_CPU_CLASS_PTR pop_16(&bx);
    BX_CPU_CLASS_PTR pop_16(&dx);
    BX_CPU_CLASS_PTR pop_16(&cx);
    BX_CPU_CLASS_PTR pop_16(&ax);

    RW_DI = di;
    RW_SI = si;
    RW_BP = bp;
//  BX_SP = sp;
    RW_BX = bx;
    RW_DX = dx;
    RW_CX = cx;
    RW_AX = ax;
#endif
}

  void
BX_CPU_C::PUSH_Iw(BX_CPU_C *icpu,bxInstruction_c *i)
{
#if BX_CPU_LEVEL < 2
	BX_PANIC(("PUSH_Iv: not supported on 8086!"));
#else

    Bit16u imm16;

    imm16 = IMMEDIATEIw(i);

    BX_CPU_CLASS_PTR push_16(imm16);
#endif
}

  void
BX_CPU_C::PUSH_EGw(BX_CPU_C *icpu,bxInstruction_c *i)
{
    Bit16u op1_16;

	if (i->modC0())
	{
		op1_16 = READ_VIRTUAL_16BIT_REG(MODRMrm(i));
	}
    else
	{
		BX_CPU_CLASS_PTR read_virtual_word(MODRMSeg(i), RMAddr(i), &op1_16);
    }

    BX_CPU_CLASS_PTR push_16(op1_16);
}

  void
BX_CPU_C::PUSH_EEw(BX_CPU_C *icpu,bxInstruction_c *i)
{
    Bit16u op1_16;

	if (i->modC0())
	{
		op1_16 = READ_VIRTUAL_16BIT_REG(MODRMrm(i));
	}
    else
	{
		BX_CPU_CLASS_PTR read_virtual_word(MODRMSeg(i), RMAddr(i), &op1_16);
    }

    BX_CPU_CLASS_PTR push_16(op1_16);
}

