/////////////////////////////////////////////////////////////////////////
// $Id: io.cc,v 1.5 2001/10/03 13:10:37 bdenney Exp $
/////////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "x86cpu.h"

  void
BX_CPU_C::INSB_YbDX(BX_CPU_C *icpu,bxInstruction_c *i)
{
  Bit8u value8=0;

  if (BX_CPU_CLASS_PTR cr0.pe && (BX_CPU_CLASS_PTR eflags.vm || (RW_CPL>RW_IOPL))) {
    if ( !BX_CPU_CLASS_PTR allow_io(RW_DX, 1) ) {
      BX_CPU_CLASS_PTR exception(BX_GP_EXCEPTION, 0, 0);
      }
    }

  if (i->size_mode.as_32) {
    // Write a zero to memory, to trigger any segment or page
    // faults before reading from IO port.
    BX_CPU_CLASS_PTR write_virtual_byte(BX_SEG_REG_ES, RW_EDI, &value8);

    value8 = BX_CPU_CLASS_PTR BX_INP(RW_DX, 1);

    /* no seg override possible */
    BX_CPU_CLASS_PTR write_virtual_byte(BX_SEG_REG_ES, RW_EDI, &value8);

    if (BX_CPU_CLASS_PTR eflags.df) {
      RW_EDI = RW_EDI - 1;
      }
    else {
      RW_EDI = RW_EDI + 1;
      }
    }
  else {
    // Write a zero to memory, to trigger any segment or page
    // faults before reading from IO port.
    BX_CPU_CLASS_PTR write_virtual_byte(BX_SEG_REG_ES, RW_DI, &value8);

    value8 = BX_CPU_CLASS_PTR BX_INP(RW_DX, 1);

    /* no seg override possible */
    BX_CPU_CLASS_PTR write_virtual_byte(BX_SEG_REG_ES, RW_DI, &value8);

    if (BX_CPU_CLASS_PTR eflags.df) {
      RW_DI = RW_DI - 1;
      }
    else {
      RW_DI = RW_DI + 1;
      }
    }
}

  void
BX_CPU_C::INSW_YvDX(BX_CPU_C *icpu,bxInstruction_c *i)
  // input word/doubleword from port to string
{
  Bit32u edi;
  unsigned int incr;

  if (i->size_mode.as_32)
    edi = RW_EDI;
  else
    edi = RW_DI;

  if (i->size_mode.os_32) {
    Bit32u value32=0;

    if (BX_CPU_CLASS_PTR cr0.pe && (BX_CPU_CLASS_PTR eflags.vm || (RW_CPL>RW_IOPL))) {
      if ( !BX_CPU_CLASS_PTR allow_io(RW_DX, 4) ) {
        BX_CPU_CLASS_PTR exception(BX_GP_EXCEPTION, 0, 0);
        }
      }

    // Write a zero to memory, to trigger any segment or page
    // faults before reading from IO port.
    BX_CPU_CLASS_PTR write_virtual_dword(BX_SEG_REG_ES, edi, &value32);

    value32 = BX_CPU_CLASS_PTR BX_INP(RW_DX, 4);

    /* no seg override allowed */
    BX_CPU_CLASS_PTR write_virtual_dword(BX_SEG_REG_ES, edi, &value32);
    incr = 4;
    }
  else {
    Bit16u value16=0;

    if (BX_CPU_CLASS_PTR cr0.pe && (BX_CPU_CLASS_PTR eflags.vm || (RW_CPL>RW_IOPL))) {
      if ( !BX_CPU_CLASS_PTR allow_io(RW_DX, 2) ) {
        BX_CPU_CLASS_PTR exception(BX_GP_EXCEPTION, 0, 0);
        }
      }

    // Write a zero to memory, to trigger any segment or page
    // faults before reading from IO port.
    BX_CPU_CLASS_PTR write_virtual_word(BX_SEG_REG_ES, edi, &value16);

    value16 = BX_CPU_CLASS_PTR BX_INP(RW_DX, 2);

    /* no seg override allowed */
    BX_CPU_CLASS_PTR write_virtual_word(BX_SEG_REG_ES, edi, &value16);
    incr = 2;
    }

  if (i->size_mode.as_32) {
    if (BX_CPU_CLASS_PTR eflags.df)
      RW_EDI = RW_EDI - incr;
    else
      RW_EDI = RW_EDI + incr;
    }
  else {
    if (BX_CPU_CLASS_PTR eflags.df)
      RW_DI = RW_DI - incr;
    else
      RW_DI = RW_DI + incr;
    }
}

  void
BX_CPU_C::OUTSB_DXXb(BX_CPU_C *icpu,bxInstruction_c *i)
{
  unsigned seg;
  Bit8u value8;
  Bit32u esi;

  if (BX_CPU_CLASS_PTR cr0.pe && (BX_CPU_CLASS_PTR eflags.vm || (RW_CPL>RW_IOPL))) {
    if ( !BX_CPU_CLASS_PTR allow_io(RW_DX, 1) ) {
      BX_CPU_CLASS_PTR exception(BX_GP_EXCEPTION, 0, 0);
      }
    }

  if (!BX_NULL_SEG_REG(MODRMSeg(i))) {
    seg = MODRMSeg(i);
    }
  else {
    seg = BX_SEG_REG_DS;
    }

  if (i->size_mode.as_32)
    esi = RW_ESI;
  else
    esi = RW_SI;

  BX_CPU_CLASS_PTR read_virtual_byte(seg, esi, &value8);

  BX_CPU_CLASS_PTR BX_OUTP(RW_DX, value8, 1);

  if (i->size_mode.as_32) {
    if (BX_CPU_CLASS_PTR eflags.df)
      RW_ESI -= 1;
    else
      RW_ESI += 1;
    }
  else {
    if (BX_CPU_CLASS_PTR eflags.df)
      RW_SI -= 1;
    else
      RW_SI += 1;
    }
}

  void
BX_CPU_C::OUTSW_DXXv(BX_CPU_C *icpu,bxInstruction_c *i)
  // output word/doubleword string to port
{
  unsigned seg;
  Bit32u esi;
  unsigned int incr;

  if (!BX_NULL_SEG_REG(MODRMSeg(i))) {
    seg = MODRMSeg(i);
    }
  else {
    seg = BX_SEG_REG_DS;
    }

  if (i->size_mode.as_32)
    esi = RW_ESI;
  else
    esi = RW_SI;

  if (i->size_mode.os_32) {
    Bit32u value32;

    if (BX_CPU_CLASS_PTR cr0.pe && (BX_CPU_CLASS_PTR eflags.vm || (RW_CPL>RW_IOPL))) {
      if ( !BX_CPU_CLASS_PTR allow_io(RW_DX, 4) ) {
        BX_CPU_CLASS_PTR exception(BX_GP_EXCEPTION, 0, 0);
        }
      }

    BX_CPU_CLASS_PTR read_virtual_dword(seg, esi, &value32);

    BX_CPU_CLASS_PTR BX_OUTP(RW_DX, value32, 4);
    incr = 4;
    }
  else {
    Bit16u value16;

    if (BX_CPU_CLASS_PTR cr0.pe && (BX_CPU_CLASS_PTR eflags.vm || (RW_CPL>RW_IOPL))) {
      if ( !BX_CPU_CLASS_PTR allow_io(RW_DX, 2) ) {
        BX_CPU_CLASS_PTR exception(BX_GP_EXCEPTION, 0, 0);
        }
      }

    BX_CPU_CLASS_PTR read_virtual_word(seg, esi, &value16);

    BX_CPU_CLASS_PTR BX_OUTP(RW_DX, value16, 2);
    incr = 2;
    }

  if (i->size_mode.as_32) {
    if (BX_CPU_CLASS_PTR eflags.df)
      RW_ESI = RW_ESI - incr;
    else
      RW_ESI = RW_ESI + incr;
    }
  else {
    if (BX_CPU_CLASS_PTR eflags.df)
      RW_SI = RW_SI - incr;
    else
      RW_SI = RW_SI + incr;
    }
}


  void
BX_CPU_C::IN_ALIb(BX_CPU_C *icpu,bxInstruction_c *i)
{
  Bit8u al, imm8;

  imm8 = IMMEDIATEIb(i);

  al = BX_CPU_CLASS_PTR inp8(imm8);

  RW_AL = al;
}

  void
BX_CPU_C::IN_eAXIb(BX_CPU_C *icpu,bxInstruction_c *i)
{
  Bit8u imm8;


  imm8 = IMMEDIATEIb(i);

#if BX_CPU_LEVEL > 2
  if (i->size_mode.os_32) {
    Bit32u eax;

    eax = BX_CPU_CLASS_PTR inp32(imm8);
    RW_EAX = eax;
    }
  else
#endif /* BX_CPU_LEVEL > 2 */
    {
    Bit16u ax;

    ax = BX_CPU_CLASS_PTR inp16(imm8);
    RW_AX = ax;
    }
}

  void
BX_CPU_C::OUT_IbAL(BX_CPU_C *icpu,bxInstruction_c *i)
{
  Bit8u al, imm8;

  imm8 = IMMEDIATEIb(i);

  al = RW_AL;

  BX_CPU_CLASS_PTR outp8(imm8, al);
}

  void
BX_CPU_C::OUT_IbeAX(BX_CPU_C *icpu,bxInstruction_c *i)
{
  Bit8u imm8;

  imm8 = IMMEDIATEIb(i);

#if BX_CPU_LEVEL > 2
  if (i->size_mode.os_32) {
    BX_CPU_CLASS_PTR outp32(imm8, RW_EAX);
    }
  else
#endif /* BX_CPU_LEVEL > 2 */
    {
    BX_CPU_CLASS_PTR outp16(imm8, RW_AX);
    }
}

  void
BX_CPU_C::IN_ALDX(BX_CPU_C *icpu,bxInstruction_c *i)
{
  Bit8u al;

  al = BX_CPU_CLASS_PTR inp8(RW_DX);

  RW_AL = al;
}

  void
BX_CPU_C::IN_eAXDX(BX_CPU_C *icpu,bxInstruction_c *i)
{
#if BX_CPU_LEVEL > 2
  if (i->size_mode.os_32) {
    Bit32u eax;

    eax = BX_CPU_CLASS_PTR inp32(RW_DX);
    RW_EAX = eax;
    }
  else
#endif /* BX_CPU_LEVEL > 2 */
    {
    Bit16u ax;

    ax = BX_CPU_CLASS_PTR inp16(RW_DX);
    RW_AX = ax;
    }
}

  void
BX_CPU_C::OUT_DXAL(BX_CPU_C *icpu,bxInstruction_c *i)
{
  Bit16u dx;
  Bit8u al;

  dx = RW_DX;
  al = RW_AL;

  BX_CPU_CLASS_PTR outp8(dx, al);
}

  void
BX_CPU_C::OUT_DXeAX(BX_CPU_C *icpu,bxInstruction_c *i)
{
  Bit16u dx;

  dx = RW_DX;

#if BX_CPU_LEVEL > 2
  if (i->size_mode.os_32) {
    BX_CPU_CLASS_PTR outp32(dx, RW_EAX);
    }
  else
#endif /* BX_CPU_LEVEL > 2 */
    {
    BX_CPU_CLASS_PTR outp16(dx, RW_AX);
    }
}
