/////////////////////////////////////////////////////////////////////////
// $Id: stack32.cc,v 1.8 2002/03/05 15:50:17 bdenney Exp $
/////////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "x86cpu.h"


	void
BX_CPU_C::POP_EGd(BX_CPU_C *icpu,bxInstruction_c *i)
{
	Bit32u val32;

	if (MODRMnnn(i)!=0)
	{
		BX_PANIC(("POP_Ed: incomplete MODRMnnn(i) !=0"));
		BX_CPU_CLASS_PTR UndefinedOpcode(icpu,i);
	}

	BX_CPU_CLASS_PTR pop_32(&val32);

	if (i->modC0())
	{
		WRITE_VIRTUAL_32BIT_REG(MODRMrm(i), val32);
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
		BX_CPU_CLASS_PTR write_virtual_dword(MODRMSeg(i), RMAddr(i), &val32);
	}
}

	void
BX_CPU_C::POP_EEd(BX_CPU_C *icpu,bxInstruction_c *i)
{
	Bit32u val32;

	if (MODRMnnn(i)!=0)
	{
		BX_PANIC(("POP_Ed: incomplete MODRMnnn(i) !=0"));
		BX_CPU_CLASS_PTR UndefinedOpcode(icpu,i);
	}

	BX_CPU_CLASS_PTR pop_32(&val32);

	if (i->modC0())
	{
		WRITE_VIRTUAL_32BIT_REG(MODRMrm(i), val32);
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
		BX_CPU_CLASS_PTR write_virtual_dword(MODRMSeg(i), RMAddr(i), &val32);
	}
}
	void
BX_CPU_C::PUSH_ERX(BX_CPU_C *icpu,bxInstruction_c *i)
{
	BX_CPU_CLASS_PTR push_32(BX_CPU_CLASS_PTR program_visible_gen_reg[OPCODEb1(i) & 0x07].erx);
}

	void
BX_CPU_C::POP_ERX(BX_CPU_C *icpu,bxInstruction_c *i)
{
	Bit32u erx;

	BX_CPU_CLASS_PTR pop_32(&erx);
	BX_CPU_CLASS_PTR program_visible_gen_reg[OPCODEb1(i) & 0x07].erx = erx;
}

  void
BX_CPU_C::PUSHAD32(BX_CPU_C *icpu,bxInstruction_c *i)
{
#if BX_CPU_LEVEL < 2
  BX_PANIC(("PUSHAD: not supported on an 8086"));
#else
  Bit32u temp_ESP;
  Bit32u esp;

  if (BX_CPU_CLASS_PTR program_visible_sregs[BX_SEG_REG_SS].cache.u.segment.d_b)
    temp_ESP = RW_ESP;
  else
    temp_ESP = RW_SP;


    if (BX_CPU_CLASS_PTR protected_mode()) {
      if ( !BX_CPU_CLASS_PTR can_push(&BX_CPU_CLASS_PTR program_visible_sregs[BX_SEG_REG_SS].cache, temp_ESP, 32) ) {
        BX_PANIC(("PUSHAD(): stack doesn't have enough room!"));
        BX_CPU_CLASS_PTR exception(BX_SS_EXCEPTION, 0, 0);
        return;
        }
      }
    else {
      if (temp_ESP < 32)
        BX_PANIC(("pushad: eSP < 32"));
      }

    esp = RW_ESP;

    /* ??? optimize this by using virtual write, all checks passed */
    BX_CPU_CLASS_PTR push_32(RW_EAX);
    BX_CPU_CLASS_PTR push_32(RW_ECX);
    BX_CPU_CLASS_PTR push_32(RW_EDX);
    BX_CPU_CLASS_PTR push_32(RW_EBX);
    BX_CPU_CLASS_PTR push_32(esp);
    BX_CPU_CLASS_PTR push_32(RW_EBP);
    BX_CPU_CLASS_PTR push_32(RW_ESI);
    BX_CPU_CLASS_PTR push_32(RW_EDI);
#endif
}

  void
BX_CPU_C::POPAD32(BX_CPU_C *icpu,bxInstruction_c *i)
{
#if BX_CPU_LEVEL < 2
	BX_PANIC(("POPAD not supported on an 8086"));
#else /* 286+ */
    Bit32u edi, esi, ebp, esp, ebx, edx, ecx, eax;

    if (BX_CPU_CLASS_PTR protected_mode()) {
      if ( !BX_CPU_CLASS_PTR can_pop(32) ) {
        BX_PANIC(("pop_ad: not enough bytes on stack"));
        BX_CPU_CLASS_PTR exception(BX_SS_EXCEPTION, 0, 0);
        return;
        }
      }

    /* ??? optimize this */
    BX_CPU_CLASS_PTR pop_32(&edi);
    BX_CPU_CLASS_PTR pop_32(&esi);
    BX_CPU_CLASS_PTR pop_32(&ebp);
    BX_CPU_CLASS_PTR pop_32(&esp); /* value for ESP discarded */
    BX_CPU_CLASS_PTR pop_32(&ebx);
    BX_CPU_CLASS_PTR pop_32(&edx);
    BX_CPU_CLASS_PTR pop_32(&ecx);
    BX_CPU_CLASS_PTR pop_32(&eax);

    RW_EDI = edi;
    RW_ESI = esi;
    RW_EBP = ebp;
//  RW_ESP = esp;
    RW_EBX = ebx;
    RW_EDX = edx;
    RW_ECX = ecx;
    RW_EAX = eax;
#endif
}

  void
BX_CPU_C::PUSH_Id(BX_CPU_C *icpu,bxInstruction_c *i)
{
#if BX_CPU_LEVEL < 2
  BX_PANIC(("PUSH_Iv: not supported on 8086!"));
#else

    Bit32u imm32;

    imm32 = IMMEDIATEId(i);

    BX_CPU_CLASS_PTR push_32(imm32);
#endif
}

  void
BX_CPU_C::PUSH_EGd(BX_CPU_C *icpu,bxInstruction_c *i)
{
    Bit32u op1_32;

    if (i->modC0())
	{
		op1_32 = READ_VIRTUAL_32BIT_REG(MODRMrm(i));
	}
    else
	{
		BX_CPU_CLASS_PTR read_virtual_dword(MODRMSeg(i), RMAddr(i), &op1_32);
	}

    BX_CPU_CLASS_PTR push_32(op1_32);
}

  void
BX_CPU_C::PUSH_EEd(BX_CPU_C *icpu,bxInstruction_c *i)
{
    Bit32u op1_32;

    if (i->modC0())
	{
		op1_32 = READ_VIRTUAL_32BIT_REG(MODRMrm(i));
	}
    else
	{
		BX_CPU_CLASS_PTR read_virtual_dword(MODRMSeg(i), RMAddr(i), &op1_32);
	}

    BX_CPU_CLASS_PTR push_32(op1_32);
}

  void
BX_CPU_C::ENTER_IwIb(BX_CPU_C *icpu,bxInstruction_c *i)
{
#if BX_CPU_LEVEL < 2
  BX_PANIC(("ENTER_IwIb: not supported by 8086!"));
#else
  Bit32u frame_ptr32;
  Bit16u frame_ptr16;
  Bit8u level;
  static Bit8u first_time = 1;

  level = IMMEDIATEIb2(i);

  BX_CPU_CLASS_PTR invalidate_prefetch_q();

  level %= 32;
/* ??? */
  if (first_time && level>0) {
    BX_ERROR(("enter() with level > 0. The emulation of this instruction may not be complete.  This warning will be printed only once per bochs run."));
    first_time = 0;
  }
//if (BX_CPU_CLASS_PTR program_visible_sregs[BX_SEG_REG_SS].cache.u.segment.d_b && i->size_mode.os_32==0) {
//  BX_INFO(("enter(): stacksize!=opsize: I'm unsure of the code for this"));
//  BX_PANIC(("         The Intel manuals are a mess on this one!"));
//  }

  if ( BX_CPU_CLASS_PTR protected_mode() ) {
    Bit32u bytes_to_push, temp_ESP;

    if (level == 0) {
      if (i->size_mode.os_32)
        bytes_to_push = 4 + IMMEDIATEIw(i);
      else
        bytes_to_push = 2 + IMMEDIATEIw(i);
      }
    else { /* level > 0 */
      if (i->size_mode.os_32)
        bytes_to_push = 4 + (level-1)*4 + 4 + IMMEDIATEIw(i);
      else
        bytes_to_push = 2 + (level-1)*2 + 2 + IMMEDIATEIw(i);
      }
    if (BX_CPU_CLASS_PTR program_visible_sregs[BX_SEG_REG_SS].cache.u.segment.d_b)
      temp_ESP = RW_ESP;
    else
      temp_ESP = RW_SP;
    if ( !BX_CPU_CLASS_PTR can_push(&BX_CPU_CLASS_PTR program_visible_sregs[BX_SEG_REG_SS].cache, temp_ESP, bytes_to_push) ) {
      BX_PANIC(("ENTER: not enough room on stack!"));
      BX_CPU_CLASS_PTR exception(BX_SS_EXCEPTION, 0, 0);
      }
    }

  if (i->size_mode.os_32)
    BX_CPU_CLASS_PTR push_32(RW_EBP);
  else
    BX_CPU_CLASS_PTR push_16(RW_BP);

  // can just do frame_ptr32 = ESP for either case ???
  if (BX_CPU_CLASS_PTR program_visible_sregs[BX_SEG_REG_SS].cache.u.segment.d_b)
    frame_ptr32 = RW_ESP;
  else
    frame_ptr32 = RW_SP;

  if (level > 0) {
    /* do level-1 times */
    while (--level) {
      if (i->size_mode.os_32) {
        Bit32u temp32;

        if (BX_CPU_CLASS_PTR program_visible_sregs[BX_SEG_REG_SS].cache.u.segment.d_b) { /* 32bit stacksize */
          RW_EBP -= 4;
          BX_CPU_CLASS_PTR read_virtual_dword(BX_SEG_REG_SS, RW_EBP, &temp32);
          RW_ESP -= 4;
          BX_CPU_CLASS_PTR write_virtual_dword(BX_SEG_REG_SS, RW_ESP, &temp32);
          }
        else { /* 16bit stacksize */
          RW_BP -= 4;
          BX_CPU_CLASS_PTR read_virtual_dword(BX_SEG_REG_SS, RW_BP, &temp32);
          RW_SP -= 4;
          BX_CPU_CLASS_PTR write_virtual_dword(BX_SEG_REG_SS, RW_SP, &temp32);
          }
        }
      else { /* 16bit opsize */
        Bit16u temp16;

        if (BX_CPU_CLASS_PTR program_visible_sregs[BX_SEG_REG_SS].cache.u.segment.d_b) { /* 32bit stacksize */
          RW_EBP -= 2;
          BX_CPU_CLASS_PTR read_virtual_word(BX_SEG_REG_SS, RW_EBP, &temp16);
          RW_ESP -= 2;
          BX_CPU_CLASS_PTR write_virtual_word(BX_SEG_REG_SS, RW_ESP, &temp16);
          }
        else { /* 16bit stacksize */
          RW_BP -= 2;
          BX_CPU_CLASS_PTR read_virtual_word(BX_SEG_REG_SS, RW_BP, &temp16);
          RW_SP -= 2;
          BX_CPU_CLASS_PTR write_virtual_word(BX_SEG_REG_SS, RW_SP, &temp16);
          }
        }
      } /* while (--level) */

    /* push(frame pointer) */
    if (i->size_mode.os_32) {
      if (BX_CPU_CLASS_PTR program_visible_sregs[BX_SEG_REG_SS].cache.u.segment.d_b) { /* 32bit stacksize */
        RW_ESP -= 4;
        BX_CPU_CLASS_PTR write_virtual_dword(BX_SEG_REG_SS, RW_ESP, &frame_ptr32);
        }
      else {
        RW_SP -= 4;
        BX_CPU_CLASS_PTR write_virtual_dword(BX_SEG_REG_SS, RW_SP, &frame_ptr32);
        }
      }
    else { /* 16bit opsize */
      if (BX_CPU_CLASS_PTR program_visible_sregs[BX_SEG_REG_SS].cache.u.segment.d_b) { /* 32bit stacksize */
        frame_ptr16 = frame_ptr32;
        RW_ESP -= 2;
        BX_CPU_CLASS_PTR write_virtual_word(BX_SEG_REG_SS, RW_ESP, &frame_ptr16);
        }
      else {
        frame_ptr16 = frame_ptr32;
        RW_SP -= 2;
        BX_CPU_CLASS_PTR write_virtual_word(BX_SEG_REG_SS, RW_SP, &frame_ptr16);
        }
      }
    } /* if (level > 0) ... */

  if (i->size_mode.os_32)
    RW_EBP = frame_ptr32;
  else
    RW_BP = frame_ptr32;

  if (BX_CPU_CLASS_PTR program_visible_sregs[BX_SEG_REG_SS].cache.u.segment.d_b) { /* 32bit stacksize */
    RW_ESP = RW_ESP - IMMEDIATEIw(i);
    }
  else { /* 16bit stack */
    RW_SP = RW_SP - IMMEDIATEIw(i);
    }
#endif
}

  void
BX_CPU_C::LEAVE(BX_CPU_C *icpu,bxInstruction_c *i)
{
#if BX_CPU_LEVEL < 2
  BX_PANIC(("LEAVE: not supported by 8086!"));
#else
  Bit32u temp_EBP;


  BX_CPU_CLASS_PTR invalidate_prefetch_q();

#if BX_CPU_LEVEL >= 3
  if (BX_CPU_CLASS_PTR program_visible_sregs[BX_SEG_REG_SS].cache.u.segment.d_b)
    temp_EBP = RW_EBP;
  else
#endif
    temp_EBP = RW_BP;

  if ( BX_CPU_CLASS_PTR protected_mode() ) {
    if (BX_CPU_CLASS_PTR program_visible_sregs[BX_SEG_REG_SS].cache.u.segment.c_ed) { /* expand up */
      if (temp_EBP <= BX_CPU_CLASS_PTR program_visible_sregs[BX_SEG_REG_SS].cache.u.segment.limit_scaled) {
        BX_PANIC(("LEAVE: BP > BX_CPU_CLASS_PTR program_visible_sregs[BX_SEG_REG_SS].limit"));
        BX_CPU_CLASS_PTR exception(BX_SS_EXCEPTION, 0, 0);
        return;
        }
      }
    else { /* normal */
      if (temp_EBP > BX_CPU_CLASS_PTR program_visible_sregs[BX_SEG_REG_SS].cache.u.segment.limit_scaled) {
        BX_PANIC(("LEAVE: BP > BX_CPU_CLASS_PTR program_visible_sregs[BX_SEG_REG_SS].limit"));
        BX_CPU_CLASS_PTR exception(BX_SS_EXCEPTION, 0, 0);
        return;
        }
      }
    }


  // delete frame
#if BX_CPU_LEVEL >= 3
  if (BX_CPU_CLASS_PTR program_visible_sregs[BX_SEG_REG_SS].cache.u.segment.d_b)
    RW_ESP = RW_EBP;
  else
#endif
    RW_SP = RW_BP;

  // restore frame pointer
#if BX_CPU_LEVEL >= 3
  if (i->size_mode.os_32) {
    Bit32u temp32;

    BX_CPU_CLASS_PTR pop_32(&temp32);
    RW_EBP = temp32;
    }
  else
#endif
    {
    Bit16u temp16;

    BX_CPU_CLASS_PTR pop_16(&temp16);
    RW_BP = temp16;
    }
#endif
}
