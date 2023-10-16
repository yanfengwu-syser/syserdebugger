/////////////////////////////////////////////////////////////////////////
// $Id: soft_int.cc,v 1.6 2001/10/03 13:10:37 bdenney Exp $
/////////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "x86cpu.h"



  void
BX_CPU_C::BOUND_GvMa(BX_CPU_C *icpu,bxInstruction_c *i)
{
#if BX_CPU_LEVEL < 2
  BX_PANIC(("BOUND_GvMa: not supported on 8086!"));
#else

  if (i->modC0()) {
    /* undefined opcode exception */
    BX_PANIC(("bound: op2 must be mem ref"));
    UndefinedOpcode(icpu,i);
    }

  if (i->size_mode.os_32) {
    Bit32s bound_min, bound_max;
    Bit32s op1_32;

    op1_32 = READ_VIRTUAL_32BIT_REG(MODRMnnn(i));

    BX_CPU_CLASS_PTR read_virtual_dword(MODRMSeg(i), RMAddr(i), (Bit32u *) &bound_min);
    BX_CPU_CLASS_PTR read_virtual_dword(MODRMSeg(i), RMAddr(i)+4, (Bit32u *) &bound_max);

    /* ??? */
    if ( (op1_32 < bound_min) || (op1_32 > bound_max) ) {
      BX_INFO(("BOUND: fails bounds test"));
      BX_CPU_CLASS_PTR exception(5, 0, 0);
      }
    }
  else {
    Bit16s bound_min, bound_max;
    Bit16s op1_16;

    op1_16 = READ_VIRTUAL_16BIT_REG(MODRMnnn(i));

    BX_CPU_CLASS_PTR read_virtual_word(MODRMSeg(i), RMAddr(i), (Bit16u *) &bound_min);
    BX_CPU_CLASS_PTR read_virtual_word(MODRMSeg(i), RMAddr(i)+2, (Bit16u *) &bound_max);

    /* ??? */
    if ( (op1_16 < bound_min) || (op1_16 > bound_max) ) {
      BX_INFO(("BOUND: fails bounds test"));
      BX_CPU_CLASS_PTR exception(5, 0, 0);
      }
    }

#endif
}

  void
BX_CPU_C::INT1(BX_CPU_C *icpu,bxInstruction_c *i)
{
  // This is an undocumented instrucion (opcode 0xf1)
  // which is useful for an ICE system.

#if BX_DEBUGGER
  BX_CPU_CLASS_PTR show_flag |= Flag_int;
#endif

  BX_CPU_CLASS_PTR intel_interrupt(1, 1, 0, 0);
  BX_INSTR_FAR_BRANCH(BX_INSTR_IS_INT,
                      BX_CPU_CLASS_PTR sregs[BX_SEG_REG_CS].selector.value,
                      BX_CPU_CLASS_PTR eip);
}

  void
BX_CPU_C::INT3(BX_CPU_C *icpu,bxInstruction_c *i)
{
  // INT 3 is not IOPL sensitive

#if BX_DEBUGGER
  BX_CPU_CLASS_PTR show_flag |= Flag_int;
#endif

//BX_PANIC(("INT3: bailing"));
  BX_CPU_CLASS_PTR intel_interrupt(3, 1, 0, 0);
  BX_INSTR_FAR_BRANCH(BX_INSTR_IS_INT,
                      BX_CPU_CLASS_PTR sregs[BX_SEG_REG_CS].selector.value,
                      BX_CPU_CLASS_PTR eip);
}

	void
BX_CPU_C::INT_Ib(BX_CPU_C *icpu,bxInstruction_c *i)
{
  Bit8u imm8;

#if BX_DEBUGGER
  BX_CPU_CLASS_PTR show_flag |= Flag_int;
#endif

  imm8 = IMMEDIATEIb(i);

  if (BX_CPU_CLASS_PTR v8086_mode() && (RW_IOPL<3)) {
    //BX_INFO(("int_ib: v8086: IOPL<3"));
    BX_CPU_CLASS_PTR exception(BX_GP_EXCEPTION, 0, 0);
    }

#ifdef SHOW_EXIT_STATUS
if ( (imm8 == 0x21) && (AH == 0x4c) ) {
  BX_INFO(("INT 21/4C called AL=0x%02x, BX=0x%04x", (unsigned) AL, (unsigned) BX));
  }
#endif

  BX_CPU_CLASS_PTR intel_interrupt(imm8, 1, 0, 0);
  BX_INSTR_FAR_BRANCH(BX_INSTR_IS_INT,
                      BX_CPU_CLASS_PTR sregs[BX_SEG_REG_CS].selector.value,
                      BX_CPU_CLASS_PTR eip);
}


  void
BX_CPU_C::INTO(BX_CPU_C *icpu,bxInstruction_c *i)
{

#if BX_DEBUGGER
  BX_CPU_CLASS_PTR show_flag |= Flag_int;
#endif

  /* ??? is this IOPL sensitive ? */
  if (BX_CPU_CLASS_PTR v8086_mode()) BX_PANIC(("soft_int: v8086 mode unsupported"));

  if (BX_CPU_CLASS_PTR get_OF()) {
    BX_CPU_CLASS_PTR intel_interrupt(4, 1, 0, 0);
    BX_INSTR_FAR_BRANCH(BX_INSTR_IS_INT,
                        BX_CPU_CLASS_PTR sregs[BX_SEG_REG_CS].selector.value,
                        BX_CPU_CLASS_PTR eip);
    }
}
