/////////////////////////////////////////////////////////////////////////
// $Id: flag_ctrl_pro.cc,v 1.6 2001/10/03 13:10:37 bdenney Exp $
/////////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "x86cpu.h"


  void
BX_CPU_C::write_flags(Bit16u flags, Boolean change_IOPL, Boolean change_IF)
{
  BX_CPU_THIS_PTR set_CF(flags & 0x01);
  BX_CPU_THIS_PTR set_PF((flags >> 2) & 0x01);
  BX_CPU_THIS_PTR set_AF((flags >> 4) & 0x01);
  BX_CPU_THIS_PTR set_ZF((flags >> 6) & 0x01);
  BX_CPU_THIS_PTR set_SF((flags >> 7) & 0x01);

#if 0
// +++
if (BX_CPU_THIS_PTR eflags.tf==0 && (flags&0x0100))
  BX_DEBUG(( "TF 0->1" ));
else if (BX_CPU_THIS_PTR eflags.tf && !(flags&0x0100))
  BX_DEBUG(( "TF 1->0" ));
else if (BX_CPU_THIS_PTR eflags.tf && (flags&0x0100))
  BX_DEBUG(( "TF 1->1" ));
#endif

  BX_CPU_THIS_PTR eflags.tf = (flags >> 8) & 0x01;
  if (BX_CPU_THIS_PTR eflags.tf) {
    BX_CPU_THIS_PTR async_event = 1;
    }

	if (change_IF)
	{
		if (!BX_CPU_THIS_PTR eflags.if_&&((flags >> 9) & 0x01))
		{
			BX_CPU_THIS_PTR eflags.if_ = 1;
			BX_CPU_THIS_PTR inhibit_mask |= BX_INHIBIT_INTERRUPTS;
			BX_CPU_THIS_PTR async_event = 1;
		}
		else
		{
			BX_CPU_THIS_PTR eflags.if_ = (flags >> 9) & 0x01;
		}
	}

  BX_CPU_THIS_PTR eflags.df = (flags >> 10) & 0x01;
  BX_CPU_THIS_PTR set_OF((flags >> 11) & 0x01);


#if BX_CPU_LEVEL == 2
  BX_CPU_THIS_PTR eflags.iopl = 0;
  BX_CPU_THIS_PTR eflags.nt = 0;
#else
  if (change_IOPL)
    BX_CPU_THIS_PTR eflags.iopl = (flags >> 12) & 0x03;
  BX_CPU_THIS_PTR eflags.nt = (flags >> 14) & 0x01;
#endif
}


#if BX_CPU_LEVEL >= 3
  void
BX_CPU_C::write_eflags(Bit32u eflags_raw, Boolean change_IOPL, Boolean change_IF,
                Boolean change_VM, Boolean change_RF)
{
  BX_CPU_THIS_PTR set_CF(eflags_raw & 0x01);
  BX_CPU_THIS_PTR set_PF((eflags_raw >> 2) & 0x01);
  BX_CPU_THIS_PTR set_AF((eflags_raw >> 4) & 0x01);
  BX_CPU_THIS_PTR set_ZF((eflags_raw >> 6) & 0x01);
  BX_CPU_THIS_PTR set_SF((eflags_raw >> 7) & 0x01);

#if 0
// +++
if (BX_CPU_THIS_PTR eflags.tf==0 && (eflags_raw&0x0100))
  BX_DEBUG(( "TF 0->1" ));
else if (BX_CPU_THIS_PTR eflags.tf && !(eflags_raw&0x0100))
  BX_DEBUG(( "TF 1->0" ));
else if (BX_CPU_THIS_PTR eflags.tf && (eflags_raw&0x0100))
  BX_DEBUG(( "TF 1->1" ));
#endif

  BX_CPU_THIS_PTR eflags.tf = (eflags_raw >> 8) & 0x01;
  if (BX_CPU_THIS_PTR eflags.tf) {
    BX_CPU_THIS_PTR async_event = 1;
    }

	if (change_IF)
	{
		if (!BX_CPU_THIS_PTR eflags.if_&&((eflags_raw >> 9) & 0x01))
		{
			BX_CPU_THIS_PTR eflags.if_ = 1;
			BX_CPU_THIS_PTR inhibit_mask |= BX_INHIBIT_INTERRUPTS;
			BX_CPU_THIS_PTR async_event = 1;
		}
		else
		{
			BX_CPU_THIS_PTR eflags.if_ = (eflags_raw >> 9) & 0x01;
		}
	}

  BX_CPU_THIS_PTR eflags.df = (eflags_raw >> 10) & 0x01;
  BX_CPU_THIS_PTR set_OF((eflags_raw >> 11) & 0x01);

  if (change_IOPL)
    BX_CPU_THIS_PTR eflags.iopl = (eflags_raw >> 12) & 0x03;
  BX_CPU_THIS_PTR eflags.nt = (eflags_raw >> 14) & 0x01;

  if (change_VM) {
    BX_CPU_THIS_PTR eflags.vm = (eflags_raw >> 17) & 0x01;
#if BX_SUPPORT_V8086_MODE == 0
    if (BX_CPU_THIS_PTR eflags.vm)
      BX_PANIC(("write_eflags: VM bit set: BX_SUPPORT_V8086_MODE==0"));
#endif
    }
  if (change_RF) {
    BX_CPU_THIS_PTR eflags.rf = (eflags_raw >> 16) & 0x01;
    }

#if BX_CPU_LEVEL >= 4
  BX_CPU_THIS_PTR eflags.ac = (eflags_raw >> 18) & 0x01;
  BX_CPU_THIS_PTR eflags.id = (eflags_raw >> 21) & 0x01;
#endif

}
#endif /* BX_CPU_LEVEL >= 3 */


  Bit16u
BX_CPU_C::read_flags(void)
{
  Bit16u flags;

  flags = (get_CF()) |
          (BX_CPU_THIS_PTR eflags.bit1 << 1) |
          ((get_PF()) << 2) |
          (BX_CPU_THIS_PTR eflags.bit3 << 3) |
          ((get_AF()>0) << 4) |
          (BX_CPU_THIS_PTR eflags.bit5 << 5) |
          ((get_ZF()>0) << 6) |
          ((get_SF()>0) << 7) |
          (BX_CPU_THIS_PTR eflags.tf << 8) |
          (BX_CPU_THIS_PTR eflags.if_ << 9) |
          (BX_CPU_THIS_PTR eflags.df << 10) |
          ((get_OF()>0) << 11) |
          (BX_CPU_THIS_PTR eflags.iopl << 12) |
          (BX_CPU_THIS_PTR eflags.nt << 14) |
          (BX_CPU_THIS_PTR eflags.bit15 << 15);

  /* 8086: bits 12-15 always set to 1.
   * 286: in real mode, bits 12-15 always cleared.
   * 386+: real-mode: bit15 cleared, bits 14..12 are last loaded value
   *       protected-mode: bit 15 clear, bit 14 = last loaded, IOPL?
   */
#if BX_CPU_LEVEL < 2
  flags |= 0xF000;  /* 8086 nature */
#elif BX_CPU_LEVEL == 2
  if (real_mode()) {
    flags &= 0x0FFF;  /* 80286 in real mode nature */
    }
#else /* 386+ */
#endif

  return(flags);
}


#if BX_CPU_LEVEL >= 3
  Bit32u
BX_CPU_C::read_eflags(void)
{
  Bit32u eflags_raw;

  eflags_raw =
          (get_CF()) |
          (BX_CPU_THIS_PTR eflags.bit1 << 1) |
          ((get_PF()) << 2) |
          (BX_CPU_THIS_PTR eflags.bit3 << 3) |
          ((get_AF()>0) << 4) |
          (BX_CPU_THIS_PTR eflags.bit5 << 5) |
          ((get_ZF()>0) << 6) |
          ((get_SF()>0) << 7) |
          (BX_CPU_THIS_PTR eflags.tf << 8) |
          (BX_CPU_THIS_PTR eflags.if_ << 9) |
          (BX_CPU_THIS_PTR eflags.df << 10) |
          ((get_OF()>0) << 11) |
          (BX_CPU_THIS_PTR eflags.iopl << 12) |
          (BX_CPU_THIS_PTR eflags.nt << 14) |
          (BX_CPU_THIS_PTR eflags.bit15 << 15) |
          (BX_CPU_THIS_PTR eflags.rf << 16) |
          (BX_CPU_THIS_PTR eflags.vm << 17)
#if BX_CPU_LEVEL >= 4
          | (BX_CPU_THIS_PTR eflags.ac << 18)
          | (BX_CPU_THIS_PTR eflags.id << 21)
#endif
           ;

#if 0
  /*
   * 386+: real-mode: bit15 cleared, bits 14..12 are last loaded value
   *       protected-mode: bit 15 clear, bit 14 = last loaded, IOPL?
   */
#endif

  return(eflags_raw);
}
#endif /* BX_CPU_LEVEL >= 3 */
