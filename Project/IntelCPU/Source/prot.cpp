/////////////////////////////////////////////////////////////////////////
// $Id: protect_ctrl.cc,v 1.10 2001/10/09 21:15:14 bdenney Exp $
/////////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "x86cpu.h"

/* 1: available TSS */
/* 2: LDT */
/* 3: busy TSS */
/* 4: 286 call gate */
/* 5: task gate */
/* 9: available 32bit TSS */
/* 11: busy 32bit TSS */
/* 12: 32bit call gate */
/* xx: code data segment */
Bit8u AR_BYTE_LAR[0x20] =
{
	0,	1,	1,	1,		1,	1,	0,	0,
	0,	1,	0,	1,		1,	0,	0,	0,
	1,	1,	1,	1,		1,	1,	1,	1,
	1,	1,	1,	1,		1,	1,	1,	1,
};

// 1: 16bit TSS
// 3: 16bit TSS
// 2: LDT
// 9: 32bit TSS    G00A
// 11:32bit TSS    G00A
Bit8u AR_BYTE_LSL[0x20] =
{
	0,	1,	1,	1,		0,	0,	0,	0,
	0,	1,	0,	1,		0,	0,	0,	0,
	1,	1,	1,	1,		1,	1,	1,	1,
	1,	1,	1,	1,		1,	1,	1,	1,
};


Bit8u AR_BYTE_VERR[0x20] =
{
	0,	0,	0,	0,		0,	0,	0,	0,
	0,	0,	0,	0,		0,	0,	0,	0,
	1,	1,	1,	1,		1,	1,	1,	1,
	0,	0,	1,	1,		0,	0,	1,	1,
};

Bit8u AR_BYTE_VERW[0x20] =
{
	0,	0,	0,	0,		0,	0,	0,	0,
	0,	0,	0,	0,		0,	0,	0,	0,
	0,	0,	1,	1,		0,	0,	1,	1,
	0,	0,	0,	0,		0,	0,	0,	0,
};


	void
BX_CPU_C::ARPL_EwGw(BX_CPU_C *icpu,bxInstruction_c *i)
{
#if BX_CPU_LEVEL < 2
	BX_PANIC(("ARPL_EwRw: not supported on 8086!"));
#else /* 286+ */

	Bit16u op2_16, op1_16;

	if (BX_CPU_CLASS_PTR protected_mode())
	{
		/* op1_16 is a register or memory reference */
		if (i->modC0())
		{
			op1_16 = READ_VIRTUAL_16BIT_REG(MODRMrm(i));
		}
		else
		{	/* pointer, segment address pair */
			BX_CPU_CLASS_PTR read_RMW_virtual_word(MODRMSeg(i), RMAddr(i), &op1_16);
		}

		op2_16 = READ_VIRTUAL_16BIT_REG(MODRMnnn(i));

		if ( (op1_16 & 0x03) < (op2_16 & 0x03) )
		{
			op1_16 = (op1_16 & 0xfffc) | (op2_16 & 0x03);

			/* now write back to destination */
			if (i->modC0())
			{
			/*
				if (i->size_mode.os_32)
				{
					// if 32bit opsize, then 0xff3f is or'd into
					// upper 16bits of register
					Bit32u op1_32;

					op1_32 = READ_VIRTUAL_32BIT_REG(MODRMrm(i));
					op1_32 = (op1_32 & 0xffff0000) | op1_16;
					op1_32 |= 0xff3f0000;
					WRITE_VIRTUAL_32BIT_REG(MODRMrm(i), op1_32);
				}
				else
				{
					WRITE_VIRTUAL_16BIT_REG(MODRMrm(i), op1_16);
				}
			*/
				WRITE_VIRTUAL_16BIT_REG(MODRMrm(i), op1_16);
			}
			else
			{
				BX_CPU_CLASS_PTR write_RMW_virtual_word(op1_16);
			}

			BX_CPU_CLASS_PTR set_ZF(1);
		}
		else
		{
			BX_CPU_CLASS_PTR set_ZF(0);
		}
	}
	else
	{
		// ARPL not recognized in real or v8086 mode
		BX_CPU_CLASS_PTR UndefinedOpcode(icpu,i);
		return;
    }

#endif
}

	void
BX_CPU_C::LAR_GvEw(BX_CPU_C *icpu,bxInstruction_c *i)
{
	/* for 16 bit operand size mode */
	Bit16u raw_selector;
	bx_descriptor_t descriptor;
	bx_selector_t   selector;
	Bit32u dword1, dword2;

	if (BX_CPU_CLASS_PTR v8086_mode())
		BX_PANIC(("protect_ctrl: v8086 mode unsupported"));

	if (BX_CPU_CLASS_PTR real_mode())
	{
		BX_PANIC(("LAR_GvEw: not recognized in real mode"));
		BX_CPU_CLASS_PTR UndefinedOpcode(icpu,i);
		return;
	}

	if (i->modC0())
	{
		raw_selector = READ_VIRTUAL_16BIT_REG(MODRMrm(i));
    }
	else
	{ /* pointer, segment address pair */
		BX_CPU_CLASS_PTR read_virtual_word(MODRMSeg(i), RMAddr(i), &raw_selector);
    }

	/* if selector null, clear ZF and done */
	if ( (raw_selector & 0xfffc) == 0 )
	{
		BX_CPU_CLASS_PTR set_ZF(0);
		return;
    }

	BX_CPU_CLASS_PTR parse_selector(raw_selector, &selector);

	if ( !BX_CPU_CLASS_PTR fetch_raw_descriptor2(&selector, &dword1, &dword2) )
	{ /* not within descriptor table */
		BX_CPU_CLASS_PTR set_ZF(0);
		return;
	}

	BX_CPU_CLASS_PTR parse_descriptor(dword1, dword2, &descriptor);

	/* if source selector is visible at CPL & RPL,
	 * within the descriptor table, and of type accepted by LAR instruction,
	 * then load register with segment limit and set ZF
	*/

	if (AR_BYTE_LAR[descriptor.AR_byte&0x1f]==0)
	{
		BX_CPU_CLASS_PTR set_ZF(0);
		//BX_DEBUG(("lar(): descriptor valid bit cleared"));
		return;
    }

	if ((descriptor.AR_byte&0x1c)!=0x1c)
	{
		if ( (descriptor.dpl<RW_CPL) || (descriptor.dpl<selector.rpl) )
		{
			BX_CPU_CLASS_PTR set_ZF(0);
			return;
		}
	}
	/* ignore DPL for conforming segments */

    BX_CPU_CLASS_PTR set_ZF(1);

    if (i->size_mode.os_32)
	{ /* masked by 00FxFF00, where x is undefined */
		WRITE_VIRTUAL_32BIT_REG(MODRMnnn(i), dword2 & 0x00ffff00);
	}
    else
	{
		WRITE_VIRTUAL_16BIT_REG(MODRMnnn(i), dword2 & 0xff00);
	}

    return;
}

	void
BX_CPU_C::LSL_GvEw(BX_CPU_C *icpu,bxInstruction_c *i)
{
	/* for 16 bit operand size mode */
	Bit16u raw_selector;
	bx_descriptor_t descriptor;
	bx_selector_t   selector;
	Bit32u dword1, dword2;
	Bit32u limit32;

	if (BX_CPU_CLASS_PTR v8086_mode())
		BX_PANIC(("protect_ctrl: v8086 mode unsupported"));

	if (BX_CPU_CLASS_PTR real_mode())
	{
		BX_PANIC(("LSL_GvEw: not recognized in real mode"));
		BX_CPU_CLASS_PTR UndefinedOpcode(icpu,i);
		return;
    }

	if (i->modC0())
	{
		raw_selector = READ_VIRTUAL_16BIT_REG(MODRMrm(i));
    }
	else
	{ /* pointer, segment address pair */
		BX_CPU_CLASS_PTR read_virtual_word(MODRMSeg(i), RMAddr(i), &raw_selector);
    }


	/* if selector null, clear ZF and done */
	if ( (raw_selector & 0xfffc) == 0 )
	{
		BX_CPU_CLASS_PTR set_ZF(0);
		return;
    }

	BX_CPU_CLASS_PTR parse_selector(raw_selector, &selector);

	if ( !BX_CPU_CLASS_PTR fetch_raw_descriptor2(&selector, &dword1, &dword2) )
	{
		/* not within descriptor table */
		BX_CPU_CLASS_PTR set_ZF(0);
		return;
	}

	BX_CPU_CLASS_PTR parse_descriptor(dword1, dword2, &descriptor);

	if (AR_BYTE_LSL[descriptor.AR_byte&0x1f]==0)
	{
		BX_CPU_CLASS_PTR set_ZF(0);
		//BX_DEBUG(("lar(): descriptor valid bit cleared"));
		return;
    }

	if ((descriptor.AR_byte&0x1c)!=0x1c)
	{
		if ( (descriptor.dpl<RW_CPL) || (descriptor.dpl<selector.rpl) )
		{
			BX_CPU_CLASS_PTR set_ZF(0);
			return;
		}
	}
	/* ignore DPL for conforming segments */

    BX_CPU_CLASS_PTR set_ZF(1);

	/* all checks pass, limit32 is now byte granular, write to op1 */
	limit32 = (dword1 & 0x0000ffff) | (dword2 & 0x000f0000);

	if ( dword2 & 0x00800000 )
		limit32 = (limit32 << 12) | 0x00000fff;

	if (i->size_mode.os_32)
		WRITE_VIRTUAL_32BIT_REG(MODRMnnn(i), limit32)
	else // chop off upper 16 bits
		WRITE_VIRTUAL_16BIT_REG(MODRMnnn(i), (Bit16u) limit32)

	return ;
}

	void
BX_CPU_C::SLDT_Ew(BX_CPU_C *icpu,bxInstruction_c *i)
{
#if BX_CPU_LEVEL < 2
	BX_PANIC(("SLDT_Ew: not supported on 8086!"));
#else
	if (BX_CPU_CLASS_PTR v8086_mode())
		BX_PANIC(("protect_ctrl: v8086 mode unsupported"));

	if (BX_CPU_CLASS_PTR real_mode())
	{ /* not recognized in real address mode */
		BX_ERROR(("SLDT_Ew: encountered in real mode."));
		BX_CPU_CLASS_PTR UndefinedOpcode(icpu,i);
    }
	else
	{
		Bit16u val16;
		
		val16 = BX_CPU_CLASS_PTR ldtr.selector.value;
		if (i->modC0())
		{
			if (i->size_mode.os_32)
			{
				WRITE_VIRTUAL_32BIT_REG(MODRMrm(i), (Bit32u)val16);
			}
			else
			{
				WRITE_VIRTUAL_32BIT_REG(MODRMrm(i),val16);
			}
		}
		else
		{
			BX_CPU_CLASS_PTR write_virtual_word(MODRMSeg(i), RMAddr(i), &val16);
		}
    }
#endif
}

	void
BX_CPU_C::STR_Ew(BX_CPU_C *icpu,bxInstruction_c *i)
{
	if (BX_CPU_CLASS_PTR v8086_mode())
		BX_PANIC(("protect_ctrl: v8086 mode unsupported"));

	if (BX_CPU_CLASS_PTR real_mode())
	{
		// not recognized in real address mode
		BX_PANIC(("STR_Ew: encountered in real mode."));
		BX_CPU_CLASS_PTR UndefinedOpcode(icpu,i);
    }
	else
	{
		Bit16u val16;
		
		val16 = BX_CPU_CLASS_PTR tr.selector.value;

		if (i->modC0())
		{
			if (i->size_mode.os_32)
			{
				WRITE_VIRTUAL_32BIT_REG(MODRMrm(i),(Bit32u)val16);
			}
			else
			{
				WRITE_VIRTUAL_16BIT_REG(MODRMrm(i), val16);
			}
		}
		else
		{
			BX_CPU_CLASS_PTR write_virtual_word(MODRMSeg(i), RMAddr(i), &val16);
		}
    }
}

	void
BX_CPU_C::LLDT_Ew(BX_CPU_C *icpu,bxInstruction_c *i)
{
#if BX_CPU_LEVEL < 2
	BX_PANIC(("LLDT_Ew: not supported on 8086!"));
#else
	if (BX_CPU_CLASS_PTR v8086_mode())
		BX_PANIC(("protect_ctrl: v8086 mode unsupported"));

	//invalidate_prefetch_q();

	if (BX_CPU_CLASS_PTR real_mode())
	{
		BX_PANIC(("lldt: not recognized in real mode"));
		BX_CPU_CLASS_PTR UndefinedOpcode(icpu,i);
		return;
    }
	else
	{ /* protected mode */
		bx_descriptor_t  descriptor;
		bx_selector_t    selector;
		Bit16u raw_selector;
		Bit32u dword1, dword2;


		/* #GP(0) if the current privilege level is not 0 */
		if (RW_CPL != 0)
		{
			BX_PANIC(("LLDT: CPL != 0"));
			BX_CPU_CLASS_PTR exception(BX_GP_EXCEPTION, 0, 0);
			return;
		}

		if (i->modC0())
		{
			raw_selector = READ_VIRTUAL_16BIT_REG(MODRMrm(i));
		}
		else
		{
			BX_CPU_CLASS_PTR read_virtual_word(MODRMSeg(i), RMAddr(i), &raw_selector);
		}

		/* if selector is NULL, invalidate and done */
		if ((raw_selector & 0xfffc) == 0)
		{
			BX_CPU_CLASS_PTR ldtr.selector.value = raw_selector;
			BX_CPU_CLASS_PTR ldtr.cache.valid = 0;
			return;
		}

		/* parse fields in selector */
		BX_CPU_CLASS_PTR parse_selector(raw_selector, &selector);
		
		// #GP(selector) if the selector operand does not point into GDT
		if (selector.ti != 0)
		{
			BX_ERROR(("LLDT: selector.ti != 0"));
			BX_CPU_CLASS_PTR exception(BX_GP_EXCEPTION, raw_selector & 0xfffc, 0);
		}

		if ((selector.index*8 + 7) > BX_CPU_CLASS_PTR gdtr.limit)
		{
			BX_PANIC(("lldt: GDT: index > limit"));
			BX_CPU_CLASS_PTR exception(BX_GP_EXCEPTION, raw_selector & 0xfffc, 0);
			return;
		}

		BX_CPU_CLASS_PTR access_linear(BX_CPU_CLASS_PTR gdtr.base + selector.index*8,     4, 0,
			BX_READ, &dword1);
		BX_CPU_CLASS_PTR access_linear(BX_CPU_CLASS_PTR gdtr.base + selector.index*8 + 4, 4, 0,
			BX_READ, &dword2);

		BX_CPU_CLASS_PTR parse_descriptor(dword1, dword2, &descriptor);

		/* if selector doesn't point to an LDT descriptor #GP(selector) */
		if ((descriptor.AR_byte&0x1f)!=0x02)
		{
			BX_ERROR(("lldt: doesn't point to an LDT descriptor!"));
			BX_CPU_CLASS_PTR exception(BX_GP_EXCEPTION, raw_selector & 0xfffc, 0);
		}

		/* #NP(selector) if LDT descriptor is not present */
		if (descriptor.p==0)
		{
			BX_ERROR(("lldt: LDT descriptor not present!"));
			BX_CPU_CLASS_PTR exception(BX_NP_EXCEPTION, raw_selector & 0xfffc, 0);
		}

		if (descriptor.u.ldt.limit < 7)
		{
			BX_ERROR(("lldt: ldtr.limit < 7"));
		}

		BX_CPU_CLASS_PTR ldtr.selector = selector;
		BX_CPU_CLASS_PTR ldtr.cache = descriptor;
		BX_CPU_CLASS_PTR ldtr.cache.valid = 1;
		return;
    }
#endif
}

	void
BX_CPU_C::LTR_Ew(BX_CPU_C *icpu,bxInstruction_c *i)
{
#if BX_CPU_LEVEL < 2
	BX_PANIC(("LTR_Ew: not supported on 8086!"));
#else
	if (BX_CPU_CLASS_PTR v8086_mode())
		BX_PANIC(("protect_ctrl: v8086 mode unsupported"));

	//invalidate_prefetch_q();

	if (BX_CPU_CLASS_PTR protected_mode())
	{
		bx_descriptor_t  descriptor;
		bx_selector_t    selector;
		Bit16u raw_selector;
		Bit32u dword1, dword2;

		/* #GP(0) if the current privilege level is not 0 */
		if (RW_CPL != 0)
		{
			BX_PANIC(("LTR: CPL != 0"));
			BX_CPU_CLASS_PTR exception(BX_GP_EXCEPTION, 0, 0);
			return;
		}

		if (i->modC0())
		{
			raw_selector = READ_VIRTUAL_16BIT_REG(MODRMrm(i));
		}
		else
		{
			BX_CPU_CLASS_PTR read_virtual_word(MODRMSeg(i), RMAddr(i), &raw_selector);
		}

		/* if selector is NULL, invalidate and done */
		if ((raw_selector & 0xfffc) == 0)
		{
			BX_PANIC(("ltr: loading with NULL selector!"));
			/* if this is OK, then invalidate and load selector & descriptor cache */
			/* load here */
			BX_CPU_CLASS_PTR tr.selector.value = raw_selector;
			BX_CPU_CLASS_PTR tr.cache.valid = 0;
			return;
		}
		/* parse fields in selector, then check for null selector */
		BX_CPU_CLASS_PTR parse_selector(raw_selector, &selector);

		if (selector.ti)
		{
			BX_PANIC(("ltr: selector.ti != 0"));
			BX_CPU_CLASS_PTR exception(BX_GP_EXCEPTION, raw_selector & 0xfffc, 0);
			return;
		}

		/* fetch 2 dwords of descriptor; call handles out of limits checks */
		BX_CPU_CLASS_PTR fetch_raw_descriptor(&selector, &dword1, &dword2, BX_GP_EXCEPTION);
		
		BX_CPU_CLASS_PTR parse_descriptor(dword1, dword2, &descriptor);


		/* #GP(selector) if object is not a TSS or is already busy */
		if ( (descriptor.AR_byte&0x1f) != 1 && (descriptor.AR_byte&0x1f) != 9)
		{
			BX_PANIC(("ltr: doesn't point to an available TSS descriptor!"));
			BX_CPU_CLASS_PTR exception(BX_GP_EXCEPTION, raw_selector & 0xfffc, 0); /* 0 ??? */
			return;
		}

		/* #NP(selector) if TSS descriptor is not present */
		if (descriptor.p==0)
		{
			BX_PANIC(("ltr: LDT descriptor not present!"));
			BX_CPU_CLASS_PTR exception(BX_NP_EXCEPTION, raw_selector & 0xfffc, 0); /* 0 ??? */
			return;
		}

		if (descriptor.type==1 && descriptor.u.tss286.limit<43)
		{
			BX_PANIC(("ltr:286TSS: loading tr.limit < 43"));
		}
		else if (descriptor.type==9 && descriptor.u.tss386.limit_scaled<103)
		{
			BX_PANIC(("ltr:386TSS: loading tr.limit < 103"));
		}

		BX_CPU_CLASS_PTR tr.selector = selector;
		BX_CPU_CLASS_PTR tr.cache    = descriptor;
		BX_CPU_CLASS_PTR tr.cache.valid = 1;
		// tr.cache.type should not have busy bit, or it would not get 
		// through the conditions above.
		BX_ASSERT((BX_CPU_CLASS_PTR tr.cache.type & 2) == 0);

		/* mark as busy */
		dword2 |= 0x00000200; /* set busy bit */
		BX_CPU_CLASS_PTR access_linear(BX_CPU_CLASS_PTR gdtr.base + selector.index*8 + 4, 4, 0,
			BX_WRITE, &dword2);

		return;
    }
	else
	{
		BX_PANIC(("ltr_ew: not recognized in real-mode!"));
		BX_CPU_CLASS_PTR UndefinedOpcode(icpu,i);
		return;
    }
#endif
}

	void
BX_CPU_C::VERR_Ew(BX_CPU_C *icpu,bxInstruction_c *i)
{
	/* for 16 bit operand size mode */
	Bit16u raw_selector;
	bx_descriptor_t descriptor;
	bx_selector_t   selector;
	Bit32u dword1, dword2;

	if (BX_CPU_CLASS_PTR v8086_mode())
		BX_PANIC(("protect_ctrl: v8086 mode unsupported"));
	
	if (BX_CPU_CLASS_PTR real_mode())
	{
		BX_PANIC(("VERR_Ew: not recognized in real mode"));
		BX_CPU_CLASS_PTR UndefinedOpcode(icpu,i);
		return;
    }

	if (i->modC0())
	{
		raw_selector = READ_VIRTUAL_16BIT_REG(MODRMrm(i));
    }
	else
	{ /* pointer, segment address pair */
		BX_CPU_CLASS_PTR read_virtual_word(MODRMSeg(i), RMAddr(i), &raw_selector);
    }

	/* if selector null, clear ZF and done */
	if ( (raw_selector & 0xfffc) == 0 )
	{
		BX_CPU_CLASS_PTR set_ZF(0);
		BX_ERROR(("VERR: null selector"));
		return;
    }

	/* if source selector is visible at CPL & RPL,
	 * within the descriptor table, and of type accepted by VERR instruction,
	 * then load register with segment limit and set ZF */
	BX_CPU_CLASS_PTR parse_selector(raw_selector, &selector);

	if ( !BX_CPU_CLASS_PTR fetch_raw_descriptor2(&selector, &dword1, &dword2) )
	{
		/* not within descriptor table */
		BX_CPU_CLASS_PTR set_ZF(0);
		BX_ERROR(("VERR: not in table"));
		return;
    }
	
	BX_CPU_CLASS_PTR parse_descriptor(dword1, dword2, &descriptor);

	if (AR_BYTE_VERR[descriptor.AR_byte&0x1f]==0)
	{
		BX_CPU_CLASS_PTR set_ZF(0); /* inaccessible */
		BX_ERROR(("VERR: system descriptor"));
		return;
    }

	if ((descriptor.AR_byte&0x1c)!=0x1c)
	{
		if ( (descriptor.dpl<RW_CPL) || (descriptor.dpl<selector.rpl) )
		{
			BX_CPU_CLASS_PTR set_ZF(0); /* not accessible */
			BX_INFO(("VERR: data seg not withing priv level"));
			return;
		}
	}

    BX_CPU_CLASS_PTR set_ZF(1); /* accessible */
    BX_ERROR(("VERR: data segment OK"));
    return;
}

	void
BX_CPU_C::VERW_Ew(BX_CPU_C *icpu,bxInstruction_c *i)
{
	/* for 16 bit operand size mode */
	Bit16u raw_selector;
	bx_descriptor_t descriptor;
	bx_selector_t   selector;
	Bit32u dword1, dword2;

	if (BX_CPU_CLASS_PTR v8086_mode())
		BX_PANIC(("protect_ctrl: v8086 mode unsupported"));
	
	if (BX_CPU_CLASS_PTR real_mode())
	{
		BX_PANIC(("VERW_Ew: not recognized in real mode"));
		BX_CPU_CLASS_PTR UndefinedOpcode(icpu,i);
		return;
    }

	if (i->modC0())
	{
		raw_selector = READ_VIRTUAL_16BIT_REG(MODRMrm(i));
    }
	else
	{
		/* pointer, segment address pair */
		BX_CPU_CLASS_PTR read_virtual_word(MODRMSeg(i), RMAddr(i), &raw_selector);
    }

	/* if selector null, clear ZF and done */
	if ( (raw_selector & 0xfffc) == 0 )
	{
		BX_CPU_CLASS_PTR set_ZF(0);
		BX_ERROR(("VERW: null selector"));
		return;
    }

	/* if source selector is visible at CPL & RPL,
	 * within the descriptor table, and of type accepted by VERW instruction,
	 * then load register with segment limit and set ZF */
	BX_CPU_CLASS_PTR parse_selector(raw_selector, &selector);

	if ( !BX_CPU_CLASS_PTR fetch_raw_descriptor2(&selector, &dword1, &dword2) )
	{
		/* not within descriptor table */
		BX_CPU_CLASS_PTR set_ZF(0);
		BX_ERROR(("VERW: not in table"));
		return;
    }

	BX_CPU_CLASS_PTR parse_descriptor(dword1, dword2, &descriptor);
	
	/* rule out system segments & code segments */
	if (AR_BYTE_VERW[descriptor.AR_byte&0x1f]==0)
	{
	    BX_CPU_CLASS_PTR set_ZF(0);
		BX_ERROR(("VERW: system seg or code"));
		BX_INFO(("VERW: data seg not writable"));
		return;
    }

	/* data segment */
    if ( (descriptor.dpl<RW_CPL) || (descriptor.dpl<selector.rpl) )
	{
		BX_CPU_CLASS_PTR set_ZF(0); /* not accessible */
		BX_INFO(("VERW: writable data seg not within priv level"));
		return;
	}

    BX_CPU_CLASS_PTR set_ZF(1); /* accessible */
    BX_ERROR(("VERW: data seg writable"));
    return;
}

	void
BX_CPU_C::SGDT_Ms(BX_CPU_C *icpu,bxInstruction_c *i)
{
#if BX_CPU_LEVEL < 2
	BX_PANIC(("SGDT_Ms: not supported on 8086!"));
#else
	Bit16u limit_16;
	Bit32u base_32;

	if (BX_CPU_CLASS_PTR v8086_mode())
		BX_PANIC(("protect_ctrl: v8086 mode unsupported"));

	/* op1 is a register or memory reference */
	if (i->modC0())
	{
		/* undefined opcode exception */
		BX_PANIC(("SGDT_Ms: use of register is undefined opcode."));
		BX_CPU_CLASS_PTR UndefinedOpcode(icpu,i);
		return;
    }

	limit_16 = BX_CPU_CLASS_PTR gdtr.limit;
	base_32  = BX_CPU_CLASS_PTR gdtr.base;
#if BX_CPU_LEVEL == 2
	base_32 |= 0xff000000; /* ??? */
#else /* 386+ */
	/* 32bit processors always write 32bits of base */
#endif

	BX_CPU_CLASS_PTR write_virtual_word(MODRMSeg(i), RMAddr(i), &limit_16);

	BX_CPU_CLASS_PTR write_virtual_dword(MODRMSeg(i), RMAddr(i)+2, &base_32);

#endif
}

	void
BX_CPU_C::SIDT_Ms(BX_CPU_C *icpu,bxInstruction_c *i)
{
#if BX_CPU_LEVEL < 2
	BX_PANIC(("SIDT_Ms: not supported on 8086!"));
#else
	Bit16u limit_16;
	Bit32u base_32;

	if (BX_CPU_CLASS_PTR v8086_mode())
		BX_PANIC(("protect_ctrl: v8086 mode unsupported"));

	/* op1 is a register or memory reference */
	if (i->modC0())
	{
		/* undefined opcode exception */
		BX_PANIC(("SIDT: use of register is undefined opcode."));
		BX_CPU_CLASS_PTR UndefinedOpcode(icpu,i);
		return;
    }

	limit_16 = BX_CPU_CLASS_PTR idtr.limit;
	base_32  = BX_CPU_CLASS_PTR idtr.base;

#if BX_CPU_LEVEL == 2
	base_32 |= 0xff000000;
#else /* 386+ */
	/* ??? regardless of operand size, all 32bits of base are stored */
#endif

	BX_CPU_CLASS_PTR write_virtual_word(MODRMSeg(i), RMAddr(i), &limit_16);

	BX_CPU_CLASS_PTR write_virtual_dword(MODRMSeg(i), RMAddr(i)+2, &base_32);

#endif
}

	void
BX_CPU_C::LGDT_Ms(BX_CPU_C *icpu,bxInstruction_c *i)
{
#if BX_CPU_LEVEL < 2
	BX_PANIC(("LGDT_Ms: not supported on 8086!"));
#else
	Bit16u limit_16;
	Bit32u base_32;

	if (BX_CPU_CLASS_PTR v8086_mode())
		BX_PANIC(("protect_ctrl: v8086 mode unsupported"));

	//invalidate_prefetch_q();

	if (BX_CPU_CLASS_PTR protected_mode() && (RW_CPL!=0))
	{
		BX_PANIC(("LGDT: protected mode: CPL!=0"));
		BX_CPU_CLASS_PTR exception(BX_GP_EXCEPTION, 0, 0);
		return;
    }

	/* op1 is a register or memory reference */
	if (i->modC0())
	{
		BX_PANIC(("LGDT generating exception 6"));
		BX_CPU_CLASS_PTR UndefinedOpcode(icpu,i);
		return;
    }

	BX_CPU_CLASS_PTR read_virtual_word(MODRMSeg(i), RMAddr(i), &limit_16);

	BX_CPU_CLASS_PTR read_virtual_dword(MODRMSeg(i), RMAddr(i) + 2, &base_32);

	BX_CPU_CLASS_PTR gdtr.limit = limit_16;

#if BX_CPU_LEVEL >= 3
	if (i->size_mode.os_32)
		BX_CPU_CLASS_PTR gdtr.base = base_32;
	else
#endif
		BX_CPU_CLASS_PTR gdtr.base = base_32 & 0x00ffffff; /* ignore upper 8 bits */

#endif
}

	void
BX_CPU_C::LIDT_Ms(BX_CPU_C *icpu,bxInstruction_c *i)
{
#if BX_CPU_LEVEL < 2
	BX_PANIC(("LIDT_Ms: not supported on 8086!"));
#else
	Bit16u limit_16;
	Bit32u base_32;

	if (BX_CPU_CLASS_PTR v8086_mode())
		BX_PANIC(("protect_ctrl: v8086 mode unsupported"));

	//invalidate_prefetch_q();

	if (BX_CPU_CLASS_PTR protected_mode()&&(RW_CPL != 0))
	{
		BX_PANIC(("LIDT(): CPL(%u) != 0", (unsigned) RW_CPL));
		BX_CPU_CLASS_PTR exception(BX_GP_EXCEPTION, 0, 0);
		return;
	}

	/* op1 is a register or memory reference */
	if (i->modC0())
	{
		/* undefined opcode exception */
		BX_PANIC(("LIDT generating exception 6"));
		BX_CPU_CLASS_PTR UndefinedOpcode(icpu,i);
		return;
    }

	BX_CPU_CLASS_PTR read_virtual_word(MODRMSeg(i), RMAddr(i), &limit_16);

	BX_CPU_CLASS_PTR read_virtual_dword(MODRMSeg(i), RMAddr(i) + 2, &base_32);

	BX_CPU_CLASS_PTR idtr.limit = limit_16;

#if BX_CPU_LEVEL >= 3
	if (i->size_mode.os_32)
		BX_CPU_CLASS_PTR idtr.base = base_32;
	else
#endif
		BX_CPU_CLASS_PTR idtr.base = base_32 & 0x00ffffff; /* ignore upper 8 bits */

#endif
}
