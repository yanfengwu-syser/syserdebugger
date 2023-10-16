/////////////////////////////////////////////////////////////////////////
// $Id: data_xfer32.cc,v 1.6 2001/10/03 13:10:37 bdenney Exp $
/////////////////////////////////////////////////////////////////////////


#include "stdafx.h"
#include "x86cpu.h"

	void
BX_CPU_C::XLAT(BX_CPU_C *icpu,bxInstruction_c *i)
{
	Bit32u offset_32;
	Bit8u  al;

#if BX_CPU_LEVEL >= 3
	if (i->size_mode.as_32)
	{
		offset_32 = RW_EBX + RW_AL;
    }
	else
#endif /* BX_CPU_LEVEL >= 3 */
    {
		offset_32 = RW_BX + RW_AL;
    }

	if (!BX_NULL_SEG_REG(MODRMSeg(i)))
	{
		BX_CPU_CLASS_PTR read_virtual_byte(MODRMSeg(i), offset_32, &al);
    }
	else
	{
		BX_CPU_CLASS_PTR read_virtual_byte(BX_SEG_REG_DS, offset_32, &al);
    }

	RW_AL = al;
}

	void
BX_CPU_C::CBW(BX_CPU_C *icpu,bxInstruction_c *i)
{
	RW_AX = (Bit8s)RW_AL;
}
	void
BX_CPU_C::CWDE(BX_CPU_C *icpu,bxInstruction_c *i)
{
    RW_EAX = (Bit16s)RW_AX;
}
	void
BX_CPU_C::CWD(BX_CPU_C *icpu,bxInstruction_c *i)
{
	RW_DX = (0-(RW_AX>>15));
}

	void
BX_CPU_C::CDQ(BX_CPU_C *icpu,bxInstruction_c *i)
{
	RW_EDX = (0-(RW_EAX>>31));
}
	void
BX_CPU_C::CMOV_GwEGw(BX_CPU_C *icpu,bxInstruction_c *i)
{
#if (BX_CPU_LEVEL >= 6) || (BX_CPU_LEVEL_HACKED >= 6)
	// Note: CMOV accesses a memory source operand (read), regardless
	//       of whether condition is true or not.  Thus, exceptions may
	//       occur even if the MOV does not take place.

	Boolean condition;
	Bit16u op2_16;

	switch (OPCODEb1(i)) {
    // CMOV opcodes:
    case 0x140: condition = BX_CPU_CLASS_PTR get_OF(); break;
    case 0x141: condition = !BX_CPU_CLASS_PTR get_OF(); break;
    case 0x142: condition = BX_CPU_CLASS_PTR get_CF(); break;
    case 0x143: condition = !BX_CPU_CLASS_PTR get_CF(); break;
    case 0x144: condition = BX_CPU_CLASS_PTR get_ZF(); break;
    case 0x145: condition = !BX_CPU_CLASS_PTR get_ZF(); break;
    case 0x146: condition = BX_CPU_CLASS_PTR get_CF() || BX_CPU_CLASS_PTR get_ZF(); break;
    case 0x147: condition = !BX_CPU_CLASS_PTR get_CF() && !BX_CPU_CLASS_PTR get_ZF(); break;
    case 0x148: condition = BX_CPU_CLASS_PTR get_SF(); break;
    case 0x149: condition = !BX_CPU_CLASS_PTR get_SF(); break;
    case 0x14A: condition = BX_CPU_CLASS_PTR get_PF(); break;
    case 0x14B: condition = !BX_CPU_CLASS_PTR get_PF(); break;
    case 0x14C: condition = BX_CPU_CLASS_PTR get_SF() != BX_CPU_CLASS_PTR get_OF(); break;
    case 0x14D: condition = BX_CPU_CLASS_PTR get_SF() == BX_CPU_CLASS_PTR get_OF(); break;
    case 0x14E: condition = BX_CPU_CLASS_PTR get_ZF() || (BX_CPU_CLASS_PTR get_SF() != BX_CPU_CLASS_PTR get_OF()); break;
    case 0x14F: condition = !BX_CPU_CLASS_PTR get_ZF() && (BX_CPU_CLASS_PTR get_SF() == BX_CPU_CLASS_PTR get_OF()); break;
    default:
      condition = 0;
      BX_PANIC(("CMOV_GwEw: default case"));
    }

	if (i->modC0()) {
    op2_16 = READ_VIRTUAL_16BIT_REG(MODRMrm(i));
    }
	else {
    /* pointer, segment address pair */
    BX_CPU_CLASS_PTR read_virtual_word(MODRMSeg(i), RMAddr(i), &op2_16);
    }

	if (condition)
	{
		WRITE_VIRTUAL_16BIT_REG(MODRMnnn(i), op2_16);
    }

#else
	BX_PANIC(("cmov_gwew called"));
#endif
}

	void
BX_CPU_C::CMOV_GwEEw(BX_CPU_C *icpu,bxInstruction_c *i)
{
#if (BX_CPU_LEVEL >= 6) || (BX_CPU_LEVEL_HACKED >= 6)
	// Note: CMOV accesses a memory source operand (read), regardless
	//       of whether condition is true or not.  Thus, exceptions may
	//       occur even if the MOV does not take place.

	Boolean condition;
	Bit16u op2_16;

	switch (OPCODEb1(i)) {
    // CMOV opcodes:
    case 0x140: condition = BX_CPU_CLASS_PTR get_OF(); break;
    case 0x141: condition = !BX_CPU_CLASS_PTR get_OF(); break;
    case 0x142: condition = BX_CPU_CLASS_PTR get_CF(); break;
    case 0x143: condition = !BX_CPU_CLASS_PTR get_CF(); break;
    case 0x144: condition = BX_CPU_CLASS_PTR get_ZF(); break;
    case 0x145: condition = !BX_CPU_CLASS_PTR get_ZF(); break;
    case 0x146: condition = BX_CPU_CLASS_PTR get_CF() || BX_CPU_CLASS_PTR get_ZF(); break;
    case 0x147: condition = !BX_CPU_CLASS_PTR get_CF() && !BX_CPU_CLASS_PTR get_ZF(); break;
    case 0x148: condition = BX_CPU_CLASS_PTR get_SF(); break;
    case 0x149: condition = !BX_CPU_CLASS_PTR get_SF(); break;
    case 0x14A: condition = BX_CPU_CLASS_PTR get_PF(); break;
    case 0x14B: condition = !BX_CPU_CLASS_PTR get_PF(); break;
    case 0x14C: condition = BX_CPU_CLASS_PTR get_SF() != BX_CPU_CLASS_PTR get_OF(); break;
    case 0x14D: condition = BX_CPU_CLASS_PTR get_SF() == BX_CPU_CLASS_PTR get_OF(); break;
    case 0x14E: condition = BX_CPU_CLASS_PTR get_ZF() || (BX_CPU_CLASS_PTR get_SF() != BX_CPU_CLASS_PTR get_OF()); break;
    case 0x14F: condition = !BX_CPU_CLASS_PTR get_ZF() && (BX_CPU_CLASS_PTR get_SF() == BX_CPU_CLASS_PTR get_OF()); break;
    default:
      condition = 0;
      BX_PANIC(("CMOV_GwEw: default case"));
    }

	if (i->modC0()) {
    op2_16 = READ_VIRTUAL_16BIT_REG(MODRMrm(i));
    }
	else {
    /* pointer, segment address pair */
    BX_CPU_CLASS_PTR read_virtual_word(MODRMSeg(i), RMAddr(i), &op2_16);
    }

	if (condition)
	{
		WRITE_VIRTUAL_16BIT_REG(MODRMnnn(i), op2_16);
    }

#else
	BX_PANIC(("cmov_gwew called"));
#endif
}


	void
BX_CPU_C::CMOV_GdEGd(BX_CPU_C *icpu,bxInstruction_c *i)
{
#if (BX_CPU_LEVEL >= 6) || (BX_CPU_LEVEL_HACKED >= 6||1)
	// Note: CMOV accesses a memory source operand (read), regardless
	//       of whether condition is true or not.  Thus, exceptions may
	//       occur even if the MOV does not take place.

	Boolean condition;
	Bit32u op2_32;


	switch (OPCODEb1(i)) {
    // CMOV opcodes:
    case 0x140: condition = BX_CPU_CLASS_PTR get_OF(); break;
    case 0x141: condition = !BX_CPU_CLASS_PTR get_OF(); break;
    case 0x142: condition = BX_CPU_CLASS_PTR get_CF(); break;
    case 0x143: condition = !BX_CPU_CLASS_PTR get_CF(); break;
    case 0x144: condition = BX_CPU_CLASS_PTR get_ZF(); break;
    case 0x145: condition = !BX_CPU_CLASS_PTR get_ZF(); break;
    case 0x146: condition = BX_CPU_CLASS_PTR get_CF() || BX_CPU_CLASS_PTR get_ZF(); break;
    case 0x147: condition = !BX_CPU_CLASS_PTR get_CF() && !BX_CPU_CLASS_PTR get_ZF(); break;
    case 0x148: condition = BX_CPU_CLASS_PTR get_SF(); break;
    case 0x149: condition = !BX_CPU_CLASS_PTR get_SF(); break;
    case 0x14A: condition = BX_CPU_CLASS_PTR get_PF(); break;
    case 0x14B: condition = !BX_CPU_CLASS_PTR get_PF(); break;
    case 0x14C: condition = BX_CPU_CLASS_PTR get_SF() != BX_CPU_CLASS_PTR get_OF(); break;
    case 0x14D: condition = BX_CPU_CLASS_PTR get_SF() == BX_CPU_CLASS_PTR get_OF(); break;
    case 0x14E: condition = BX_CPU_CLASS_PTR get_ZF() || (BX_CPU_CLASS_PTR get_SF() != BX_CPU_CLASS_PTR get_OF()); break;
    case 0x14F: condition = !BX_CPU_CLASS_PTR get_ZF() && (BX_CPU_CLASS_PTR get_SF() == BX_CPU_CLASS_PTR get_OF()); break;
    default:
      condition = 0;
      BX_PANIC(("CMOV_GdEd: default case"));
    }

	if (i->modC0()) {
    op2_32 = READ_VIRTUAL_32BIT_REG(MODRMrm(i));
    }
	else {
    /* pointer, segment address pair */
    BX_CPU_CLASS_PTR read_virtual_dword(MODRMSeg(i), RMAddr(i), &op2_32);
    }

	if (condition) {
    WRITE_VIRTUAL_32BIT_REG(MODRMnnn(i), op2_32);
    }
	
#else
	BX_PANIC(("cmov_gded called"));
#endif
}

	void
BX_CPU_C::CMOV_GdEEd(BX_CPU_C *icpu,bxInstruction_c *i)
{
#if (BX_CPU_LEVEL >= 6) || (BX_CPU_LEVEL_HACKED >= 6||1)
	// Note: CMOV accesses a memory source operand (read), regardless
	//       of whether condition is true or not.  Thus, exceptions may
	//       occur even if the MOV does not take place.

	Boolean condition;
	Bit32u op2_32;


	switch (OPCODEb1(i)) {
    // CMOV opcodes:
    case 0x140: condition = BX_CPU_CLASS_PTR get_OF(); break;
    case 0x141: condition = !BX_CPU_CLASS_PTR get_OF(); break;
    case 0x142: condition = BX_CPU_CLASS_PTR get_CF(); break;
    case 0x143: condition = !BX_CPU_CLASS_PTR get_CF(); break;
    case 0x144: condition = BX_CPU_CLASS_PTR get_ZF(); break;
    case 0x145: condition = !BX_CPU_CLASS_PTR get_ZF(); break;
    case 0x146: condition = BX_CPU_CLASS_PTR get_CF() || BX_CPU_CLASS_PTR get_ZF(); break;
    case 0x147: condition = !BX_CPU_CLASS_PTR get_CF() && !BX_CPU_CLASS_PTR get_ZF(); break;
    case 0x148: condition = BX_CPU_CLASS_PTR get_SF(); break;
    case 0x149: condition = !BX_CPU_CLASS_PTR get_SF(); break;
    case 0x14A: condition = BX_CPU_CLASS_PTR get_PF(); break;
    case 0x14B: condition = !BX_CPU_CLASS_PTR get_PF(); break;
    case 0x14C: condition = BX_CPU_CLASS_PTR get_SF() != BX_CPU_CLASS_PTR get_OF(); break;
    case 0x14D: condition = BX_CPU_CLASS_PTR get_SF() == BX_CPU_CLASS_PTR get_OF(); break;
    case 0x14E: condition = BX_CPU_CLASS_PTR get_ZF() || (BX_CPU_CLASS_PTR get_SF() != BX_CPU_CLASS_PTR get_OF()); break;
    case 0x14F: condition = !BX_CPU_CLASS_PTR get_ZF() && (BX_CPU_CLASS_PTR get_SF() == BX_CPU_CLASS_PTR get_OF()); break;
    default:
      condition = 0;
      BX_PANIC(("CMOV_GdEd: default case"));
    }

	if (i->modC0()) {
    op2_32 = READ_VIRTUAL_32BIT_REG(MODRMrm(i));
    }
	else {
    /* pointer, segment address pair */
    BX_CPU_CLASS_PTR read_virtual_dword(MODRMSeg(i), RMAddr(i), &op2_32);
    }

	if (condition) {
    WRITE_VIRTUAL_32BIT_REG(MODRMnnn(i), op2_32);
    }
	
#else
	BX_PANIC(("cmov_gded called"));
#endif
}


	void
BX_CPU_C::SETcc_EGb(BX_CPU_C *icpu,bxInstruction_c *i)
{
#if BX_CPU_LEVEL < 3
	BX_PANIC(("SETO: not available on < 386"));
#else
	Bit8u result_8;

	Boolean condition = 0;

	switch (OPCODEb1(i) & 0x0f) {
    case 0x00: /* JO */ condition = BX_CPU_CLASS_PTR get_OF(); break;
    case 0x01: /* JNO */ condition = !BX_CPU_CLASS_PTR get_OF(); break;
    case 0x02: /* JB */ condition = BX_CPU_CLASS_PTR get_CF(); break;
    case 0x03: /* JNB */ condition = !BX_CPU_CLASS_PTR get_CF(); break;
    case 0x04: /* JZ */ condition = BX_CPU_CLASS_PTR get_ZF(); break;
    case 0x05: /* JNZ */ condition = !BX_CPU_CLASS_PTR get_ZF(); break;
    case 0x06: /* JBE */ condition = BX_CPU_CLASS_PTR get_CF() || BX_CPU_CLASS_PTR get_ZF(); break;
    case 0x07: /* JNBE */ condition = !BX_CPU_CLASS_PTR get_CF() && !BX_CPU_CLASS_PTR get_ZF(); break;
    case 0x08: /* JS */ condition = BX_CPU_CLASS_PTR get_SF(); break;
    case 0x09: /* JNS */ condition = !BX_CPU_CLASS_PTR get_SF(); break;
    case 0x0A: /* JP */ condition = BX_CPU_CLASS_PTR get_PF(); break;
    case 0x0B: /* JNP */ condition = !BX_CPU_CLASS_PTR get_PF(); break;
    case 0x0C: /* JL */ condition = BX_CPU_CLASS_PTR get_SF() != BX_CPU_CLASS_PTR get_OF(); break;
    case 0x0D: /* JNL */ condition = BX_CPU_CLASS_PTR get_SF() == BX_CPU_CLASS_PTR get_OF(); break;
    case 0x0E: /* JLE */ condition = BX_CPU_CLASS_PTR get_ZF() || (BX_CPU_CLASS_PTR get_SF() != BX_CPU_CLASS_PTR get_OF());
      break;
    case 0x0F: /* JNLE */ condition = (BX_CPU_CLASS_PTR get_SF() == BX_CPU_CLASS_PTR get_OF()) &&
                            !BX_CPU_CLASS_PTR get_ZF();
      break;
    }
  
	result_8 = condition;

	WRITE_VIRTUAL_8BIT_REG(MODRMrm(i), result_8);

#endif
}

	void
BX_CPU_C::SETcc_EEb(BX_CPU_C *icpu,bxInstruction_c *i)
{
#if BX_CPU_LEVEL < 3
	BX_PANIC(("SETO: not available on < 386"));
#else
	Bit8u result_8;

	Boolean condition = 0;

	switch (OPCODEb1(i) & 0x0f) {
    case 0x00: /* JO */ condition = BX_CPU_CLASS_PTR get_OF(); break;
    case 0x01: /* JNO */ condition = !BX_CPU_CLASS_PTR get_OF(); break;
    case 0x02: /* JB */ condition = BX_CPU_CLASS_PTR get_CF(); break;
    case 0x03: /* JNB */ condition = !BX_CPU_CLASS_PTR get_CF(); break;
    case 0x04: /* JZ */ condition = BX_CPU_CLASS_PTR get_ZF(); break;
    case 0x05: /* JNZ */ condition = !BX_CPU_CLASS_PTR get_ZF(); break;
    case 0x06: /* JBE */ condition = BX_CPU_CLASS_PTR get_CF() || BX_CPU_CLASS_PTR get_ZF(); break;
    case 0x07: /* JNBE */ condition = !BX_CPU_CLASS_PTR get_CF() && !BX_CPU_CLASS_PTR get_ZF(); break;
    case 0x08: /* JS */ condition = BX_CPU_CLASS_PTR get_SF(); break;
    case 0x09: /* JNS */ condition = !BX_CPU_CLASS_PTR get_SF(); break;
    case 0x0A: /* JP */ condition = BX_CPU_CLASS_PTR get_PF(); break;
    case 0x0B: /* JNP */ condition = !BX_CPU_CLASS_PTR get_PF(); break;
    case 0x0C: /* JL */ condition = BX_CPU_CLASS_PTR get_SF() != BX_CPU_CLASS_PTR get_OF(); break;
    case 0x0D: /* JNL */ condition = BX_CPU_CLASS_PTR get_SF() == BX_CPU_CLASS_PTR get_OF(); break;
    case 0x0E: /* JLE */ condition = BX_CPU_CLASS_PTR get_ZF() || (BX_CPU_CLASS_PTR get_SF() != BX_CPU_CLASS_PTR get_OF());
      break;
    case 0x0F: /* JNLE */ condition = (BX_CPU_CLASS_PTR get_SF() == BX_CPU_CLASS_PTR get_OF()) &&
                            !BX_CPU_CLASS_PTR get_ZF();
      break;
    }
  
	result_8 = condition;
	BX_CPU_CLASS_PTR write_virtual_byte(MODRMSeg(i), RMAddr(i), &result_8);
#endif
}

	void
BX_CPU_C::BSWAP_ERX(BX_CPU_C *icpu,bxInstruction_c *i)
{
#if (BX_CPU_LEVEL >= 4) || (BX_CPU_LEVEL_HACKED >= 4)

	Bit32u erx, b0, b1, b2, b3;

	erx = READ_VIRTUAL_32BIT_REG(OPCODEb1(i)&0x07);

	b0  = erx & 0xff; erx >>= 8;
	b1  = erx & 0xff; erx >>= 8;
	b2  = erx & 0xff; erx >>= 8;
	b3  = erx;
	erx = (b0<<24) | (b1<<16) | (b2<<8) | b3;

	WRITE_VIRTUAL_32BIT_REG(OPCODEb1(i)&0x07,erx);

#else

	BX_PANIC(("BSWAP_ERX: not implemented CPU <= 3"));

#endif
}

// Some info on the opcodes at {0F,A6} and {0F,A7}
// On 386 steps A0-B0:
//   {OF,A6} = XBTS
//   {OF,A7} = IBTS
// On 486 steps A0-B0:
//   {OF,A6} = CMPXCHG 8
//   {OF,A7} = CMPXCHG 16|32
//
// On 486 >= B steps, and further processors, the
// CMPXCHG instructions were moved to opcodes:
//   {OF,B0} = CMPXCHG 8
//   {OF,B1} = CMPXCHG 16|32

	void
BX_CPU_C::CMPXCHG_XBTS(BX_CPU_C *icpu,bxInstruction_c *i)
{
	BX_INFO(("CMPXCHG_XBTS:"));
	UndefinedOpcode(icpu,i);
}

	void
BX_CPU_C::CMPXCHG_IBTS(BX_CPU_C *icpu,bxInstruction_c *i)
{
	BX_INFO(("CMPXCHG_IBTS:"));
	UndefinedOpcode(icpu,i);
}

	void
BX_CPU_C::CMPXCHG8B(BX_CPU_C *icpu,bxInstruction_c *i)
{
#if (BX_CPU_LEVEL >= 5) || (BX_CPU_LEVEL_HACKED >= 5)

    Bit32u op1_64_lo, op1_64_hi, diff;

	if (i->modC0())
	{
		BX_INFO(("CMPXCHG8B: dest is reg: #UD"));
		UndefinedOpcode(icpu,i);
	}

    /* pointer, segment address pair */
    BX_CPU_CLASS_PTR read_virtual_dword(MODRMSeg(i), RMAddr(i), &op1_64_lo);
    BX_CPU_CLASS_PTR read_RMW_virtual_dword(MODRMSeg(i), RMAddr(i) + 4, &op1_64_hi);

    diff = RW_EAX - op1_64_lo;
    diff |= RW_EDX - op1_64_hi;

//	SET_FLAGS_OSZAPC_32(RW_EAX, op1_32, diff_32, BX_INSTR_CMP32);

    if (diff == 0)
	{	// if accumulator == dest
		// ZF = 1
		BX_CPU_CLASS_PTR set_ZF(1);
		// dest <-- src
		BX_CPU_CLASS_PTR write_RMW_virtual_dword(RW_ECX);
		BX_CPU_CLASS_PTR write_virtual_dword(MODRMSeg(i), RMAddr(i), &RW_EBX);
	}
    else
	{
		// ZF = 0
		BX_CPU_CLASS_PTR set_ZF(0);
		// accumulator <-- dest
		RW_EAX = op1_64_lo;
		RW_EDX = op1_64_hi;
	}
  
#else
	BX_INFO(("CMPXCHG8B: not implemented yet"));
	UndefinedOpcode(icpu,i);
#endif
}




