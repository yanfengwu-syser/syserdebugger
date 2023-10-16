/////////////////////////////////////////////////////////////////////////
// $Id: flag_ctrl.cc,v 1.6 2001/10/03 13:10:37 bdenney Exp $
/////////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "x86cpu.h"


  void
BX_CPU_C::SAHF(BX_CPU_C *icpu,bxInstruction_c *i)
{
  BX_CPU_CLASS_PTR set_SF((RW_AH & 0x80) >> 7);
  BX_CPU_CLASS_PTR set_ZF((RW_AH & 0x40) >> 6);
  BX_CPU_CLASS_PTR set_AF((RW_AH & 0x10) >> 4);
  BX_CPU_CLASS_PTR set_CF(RW_AH & 0x01);
  BX_CPU_CLASS_PTR set_PF((RW_AH & 0x04) >> 2);
}

  void
BX_CPU_C::LAHF(BX_CPU_C *icpu,bxInstruction_c *i)
{
  RW_AH = (BX_CPU_CLASS_PTR get_SF() ? 0x80 : 0) |
       (BX_CPU_CLASS_PTR get_ZF() ? 0x40 : 0) |
       (BX_CPU_CLASS_PTR get_AF() ? 0x10 : 0) |
       (BX_CPU_CLASS_PTR get_PF() ? 0x04 : 0) |
       (0x02) |
       (BX_CPU_CLASS_PTR get_CF() ? 0x01 : 0);
}

  void
BX_CPU_C::CLC(BX_CPU_C *icpu,bxInstruction_c *i)
{
  BX_CPU_CLASS_PTR set_CF(0);
}

  void
BX_CPU_C::STC(BX_CPU_C *icpu,bxInstruction_c *i)
{
  BX_CPU_CLASS_PTR set_CF(1);
}

  void
BX_CPU_C::CLI(BX_CPU_C *icpu,bxInstruction_c *i)
{
#if (X86CPU_MSWIN_MSDOS==1)
	BX_CPU_CLASS_PTR  eflags.if_ = 0;
	return ;
#endif

#if BX_CPU_LEVEL >= 2
  if (BX_CPU_CLASS_PTR protected_mode()) {
    if (RW_CPL > RW_IOPL) {
      //BX_INFO(("CLI: RW_CPL > IOPL")); /* ??? */
      BX_CPU_CLASS_PTR exception(BX_GP_EXCEPTION, 0, 0);
      return;
      }
    }
#if BX_CPU_LEVEL >= 3
  else if (BX_CPU_CLASS_PTR v8086_mode()) {
    if (RW_IOPL != 3) {
      //BX_INFO(("CLI: IOPL != 3")); /* ??? */
      BX_CPU_CLASS_PTR exception(BX_GP_EXCEPTION, 0, 0);
      return;
      }
    }
#endif
#endif

  BX_CPU_CLASS_PTR  eflags.if_ = 0;
}

  void
BX_CPU_C::STI(BX_CPU_C *icpu,bxInstruction_c *i)
{
#if (X86CPU_MSWIN_MSDOS==1)

	BX_CPU_CLASS_PTR  eflags.if_ = 1;
	return ;
#endif

#if BX_CPU_LEVEL >= 2
  if (BX_CPU_CLASS_PTR protected_mode()) {
    if (RW_CPL > RW_IOPL) {
      //BX_INFO(("STI: RW_CPL > IOPL")); /* ??? */
      BX_CPU_CLASS_PTR exception(BX_GP_EXCEPTION, 0, 0);
      return;
      }
    }
#if BX_CPU_LEVEL >= 3
  else if (BX_CPU_CLASS_PTR v8086_mode()) {
    if (RW_IOPL != 3) {
      //BX_INFO(("STI: IOPL != 3")); /* ??? */
      BX_CPU_CLASS_PTR exception(BX_GP_EXCEPTION, 0, 0);
      return;
      }
    }
#endif
#endif

  if (!BX_CPU_CLASS_PTR  eflags.if_) {
    BX_CPU_CLASS_PTR  eflags.if_ = 1;
    BX_CPU_CLASS_PTR  inhibit_mask |= BX_INHIBIT_INTERRUPTS;
    BX_CPU_CLASS_PTR  async_event = 1;
    }
}

  void
BX_CPU_C::CLD(BX_CPU_C *icpu,bxInstruction_c *i)
{
  BX_CPU_CLASS_PTR  eflags.df = 0;
}

  void
BX_CPU_C::STD(BX_CPU_C *icpu,bxInstruction_c *i)
{
  BX_CPU_CLASS_PTR  eflags.df = 1;
}

  void
BX_CPU_C::CMC(BX_CPU_C *icpu,bxInstruction_c *i)
{
  BX_CPU_CLASS_PTR set_CF( !BX_CPU_CLASS_PTR get_CF() );
}

  void
BX_CPU_C::PUSHF(BX_CPU_C *icpu,bxInstruction_c *i)
{
  if (BX_CPU_CLASS_PTR v8086_mode() && (RW_IOPL<3)) {
    BX_CPU_CLASS_PTR exception(BX_GP_EXCEPTION, 0, 0);
    return;
    }

#if BX_CPU_LEVEL >= 3
  if (i->size_mode.os_32) {
    BX_CPU_CLASS_PTR push_32(BX_CPU_CLASS_PTR read_eflags() & 0x00fcffff);
    }
  else
#endif
    {
    BX_CPU_CLASS_PTR push_16(BX_CPU_CLASS_PTR read_flags());
    }
}


  void
BX_CPU_C::POPF(BX_CPU_C *icpu,bxInstruction_c *i)
{
#if BX_CPU_LEVEL >= 3
  if (BX_CPU_CLASS_PTR v8086_mode()) {
    if (RW_IOPL < 3) {
      //BX_INFO(("popf_fv: IOPL < 3"));
      BX_CPU_CLASS_PTR exception(BX_GP_EXCEPTION, 0, 0);
      return;
      }
    if (i->size_mode.os_32) {
      BX_PANIC(("POPFD(): not supported in virtual mode"));
      BX_CPU_CLASS_PTR exception(BX_GP_EXCEPTION, 0, 0);
      return;
      }
    }

  if (i->size_mode.os_32) {
    Bit32u eflags;

    BX_CPU_CLASS_PTR pop_32(&eflags);

    eflags &= 0x00277fd7;
    if (!BX_CPU_CLASS_PTR real_mode()) {
      BX_CPU_CLASS_PTR write_eflags(eflags, /* change IOPL? */ RW_CPL==0, /* change IF? */ RW_CPL<=RW_IOPL, 0, 0);
      }
    else { /* real mode */
      BX_CPU_CLASS_PTR write_eflags(eflags, /* change IOPL? */ 1, /* change IF? */ 1, 0, 0);
      }
    }
  else
#endif /* BX_CPU_LEVEL >= 3 */
    { /* 16 bit opsize */
    Bit16u flags;

    BX_CPU_CLASS_PTR pop_16(&flags);

    if (!BX_CPU_CLASS_PTR real_mode()) {
      BX_CPU_CLASS_PTR write_flags(flags, /* change IOPL? */ RW_CPL==0, /* change IF? */ RW_CPL<=RW_IOPL);
      }
    else { /* real mode */
      BX_CPU_CLASS_PTR write_flags(flags, /* change IOPL? */ 1, /* change IF? */ 1);
      }
    }
}


  void
BX_CPU_C::SALC(BX_CPU_C *icpu,bxInstruction_c *i)
{
  if ( BX_CPU_CLASS_PTR get_CF() ) {
    RW_AL = 0xff;
    }
  else {
    RW_AL = 0x00;
    }
}
