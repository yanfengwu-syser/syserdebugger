/////////////////////////////////////////////////////////////////////////
// $Id: stack_pro.cc,v 1.6 2001/10/03 13:10:37 bdenney Exp $
/////////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "x86cpu.h"

  void
BX_CPU_C::push_16(Bit16u value16)
{
  Bit32u temp_ESP;

#if BX_CPU_LEVEL >= 2
  if (protected_mode()) {
#if BX_CPU_LEVEL >= 3
    if (BX_CPU_THIS_PTR program_visible_sregs[BX_SEG_REG_SS].cache.u.segment.d_b)
      temp_ESP = X86_ESP;
    else
#endif
      temp_ESP = X86_SP;
    if (!can_push(&BX_CPU_THIS_PTR program_visible_sregs[BX_SEG_REG_SS].cache, temp_ESP, 2)) {
      BX_PANIC(("push_16(): can't push on stack"));
      exception(BX_SS_EXCEPTION, 0, 0);
      return;
      }

    /* access within limits */
#if BX_SupportICache
	bxReadWriteGuess *guess;
	guess = &BX_CPU_THIS_PTR iCache.PushPop[((temp_ESP-2)>>12)&(32-1)];
#endif
    BX_CPU_THIS_PTR write_virtual_word(BX_SEG_REG_SS, temp_ESP - 2, &value16);
    if (BX_CPU_THIS_PTR program_visible_sregs[BX_SEG_REG_SS].cache.u.segment.d_b)
      X86_ESP -= 2;
    else
      X86_SP -= 2;
    return;
    }
  else
#endif
    { /* real mode */
    if (BX_CPU_THIS_PTR program_visible_sregs[BX_SEG_REG_SS].cache.u.segment.d_b) {
      if (X86_ESP == 1)
        BX_PANIC(("CPU shutting down due to lack of stack space, ESP==1"));
      X86_ESP -= 2;
      temp_ESP = X86_ESP;
      }
    else {
      if (X86_SP == 1)
        BX_PANIC(("CPU shutting down due to lack of stack space, SP==1"));
      X86_SP -= 2;
      temp_ESP = X86_SP;
      }

    BX_CPU_THIS_PTR write_virtual_word(BX_SEG_REG_SS, temp_ESP, &value16);
    return;
    }
}

  void
BX_CPU_C::call_push_16(Bit16u value16)
{
  Bit32u temp_ESP;

#if BX_CPU_LEVEL >= 2
  if (protected_mode()) {
#if BX_CPU_LEVEL >= 3
    if (BX_CPU_THIS_PTR program_visible_sregs[BX_SEG_REG_SS].cache.u.segment.d_b)
      temp_ESP = X86_ESP;
    else
#endif
      temp_ESP = X86_SP;
    if (!can_push(&BX_CPU_THIS_PTR program_visible_sregs[BX_SEG_REG_SS].cache, temp_ESP, 2)) {
      BX_PANIC(("push_16(): can't push on stack"));
      exception(BX_SS_EXCEPTION, 0, 0);
      return;
      }

    /* access within limits */
#if BX_SupportICache
	bxReadWriteGuess *guess;
	guess = &BX_CPU_THIS_PTR iCache.PushPop[((temp_ESP-2)>>12)&(32-1)];
#endif
    BX_CPU_THIS_PTR write_push_word(BX_SEG_REG_SS, temp_ESP - 2, &value16);
    if (BX_CPU_THIS_PTR program_visible_sregs[BX_SEG_REG_SS].cache.u.segment.d_b)
      X86_ESP -= 2;
    else
      X86_SP -= 2;
    return;
    }
  else
#endif
    { /* real mode */
    if (BX_CPU_THIS_PTR program_visible_sregs[BX_SEG_REG_SS].cache.u.segment.d_b) {
      if (X86_ESP == 1)
        BX_PANIC(("CPU shutting down due to lack of stack space, ESP==1"));
      X86_ESP -= 2;
      temp_ESP = X86_ESP;
      }
    else {
      if (X86_SP == 1)
        BX_PANIC(("CPU shutting down due to lack of stack space, SP==1"));
      X86_SP -= 2;
      temp_ESP = X86_SP;
      }

    BX_CPU_THIS_PTR write_push_word(BX_SEG_REG_SS, temp_ESP, &value16);
    return;
    }
}

#if BX_CPU_LEVEL >= 3
  /* push 32 bit operand size */
   void
BX_CPU_C::push_32(Bit32u value32)
{
  /* must use StackAddrSize, and either ESP or SP accordingly */
  if (BX_CPU_THIS_PTR program_visible_sregs[BX_SEG_REG_SS].cache.u.segment.d_b) { /* StackAddrSize = 32 */
    /* 32bit stack size: pushes use SS:ESP  */
    if (protected_mode()) {
      if (!can_push(&BX_CPU_THIS_PTR program_visible_sregs[BX_SEG_REG_SS].cache, X86_ESP, 4)) {
        BX_PANIC(("push_32(): push outside stack limits"));
        /* #SS(0) */
        }
      }
    else { /* real mode */
      if ((X86_ESP>=1) && (X86_ESP<=3)) {
        BX_PANIC(("push_32: ESP=%08x", (unsigned) X86_ESP));
        }
      }

    BX_CPU_THIS_PTR write_virtual_dword(BX_SEG_REG_SS, X86_ESP-4, &value32);
    X86_ESP -= 4;
    /* will return after error anyway */
    return;
    }
  else { /* 16bit stack size: pushes use SS:SP  */
    if (protected_mode()) {
      if (!can_push(&BX_CPU_THIS_PTR program_visible_sregs[BX_SEG_REG_SS].cache, X86_SP, 4)) {
        BX_PANIC(("push_32(): push outside stack limits"));
        /* #SS(0) */
        }
      }
    else { /* real mode */
      if ((X86_SP>=1) && (X86_SP<=3)) {
        BX_PANIC(("push_32: SP=%08x", (unsigned) X86_SP));
        }
      }

    BX_CPU_THIS_PTR write_virtual_dword(BX_SEG_REG_SS, (Bit16u) (X86_SP-4), &value32);
    X86_SP -= 4;
    /* will return after error anyway */
    return;
    }
}

   void
BX_CPU_C::call_push_32(Bit32u value32)
{
  /* must use StackAddrSize, and either ESP or SP accordingly */
  if (BX_CPU_THIS_PTR program_visible_sregs[BX_SEG_REG_SS].cache.u.segment.d_b) { /* StackAddrSize = 32 */
    /* 32bit stack size: pushes use SS:ESP  */
    if (protected_mode()) {
      if (!can_push(&BX_CPU_THIS_PTR program_visible_sregs[BX_SEG_REG_SS].cache, X86_ESP, 4)) {
        BX_PANIC(("push_32(): push outside stack limits"));
        /* #SS(0) */
        }
      }
    else { /* real mode */
      if ((X86_ESP>=1) && (X86_ESP<=3)) {
        BX_PANIC(("push_32: ESP=%08x", (unsigned) X86_ESP));
        }
      }

    BX_CPU_THIS_PTR write_push_dword(BX_SEG_REG_SS, X86_ESP-4, &value32);
    X86_ESP -= 4;
    /* will return after error anyway */
    return;
    }
  else { /* 16bit stack size: pushes use SS:SP  */
    if (protected_mode()) {
      if (!can_push(&BX_CPU_THIS_PTR program_visible_sregs[BX_SEG_REG_SS].cache, X86_SP, 4)) {
        BX_PANIC(("push_32(): push outside stack limits"));
        /* #SS(0) */
        }
      }
    else { /* real mode */
      if ((X86_SP>=1) && (X86_SP<=3)) {
        BX_PANIC(("push_32: SP=%08x", (unsigned) X86_SP));
        }
      }

    BX_CPU_THIS_PTR write_push_dword(BX_SEG_REG_SS, (Bit16u) (X86_SP-4), &value32);
    X86_SP -= 4;
    /* will return after error anyway */
    return;
    }
}

#endif /* BX_CPU_LEVEL >= 3 */

  void
BX_CPU_C::pop_16(Bit16u *value16_ptr)
{
  Bit32u temp_ESP;

#if BX_CPU_LEVEL >= 3
  if (BX_CPU_THIS_PTR program_visible_sregs[BX_SEG_REG_SS].cache.u.segment.d_b)
    temp_ESP = X86_ESP;
  else
#endif
    temp_ESP = X86_SP;

#if BX_CPU_LEVEL >= 2
  if (protected_mode()) {
    if ( !can_pop(2) ) {
      BX_INFO(("pop_16(): can't pop from stack"));
      exception(BX_SS_EXCEPTION, 0, 0);
      return;
      }
    }
#endif


  /* access within limits */
  BX_CPU_THIS_PTR read_virtual_word(BX_SEG_REG_SS, temp_ESP, value16_ptr);

  if (BX_CPU_THIS_PTR program_visible_sregs[BX_SEG_REG_SS].cache.u.segment.d_b)
    X86_ESP += 2;
  else
    X86_SP += 2;
}

#if BX_CPU_LEVEL >= 3
  void
BX_CPU_C::pop_32(Bit32u *value32_ptr)
{
  Bit32u temp_ESP;

  /* 32 bit stack mode: use SS:ESP */
  if (BX_CPU_THIS_PTR program_visible_sregs[BX_SEG_REG_SS].cache.u.segment.d_b)
    temp_ESP = X86_ESP;
  else
    temp_ESP = X86_SP;

  /* 16 bit stack mode: use SS:SP */
  if (protected_mode()) {
    if ( !can_pop(4) ) {
      BX_PANIC(("pop_32(): can't pop from stack"));
      exception(BX_SS_EXCEPTION, 0, 0);
      return;
      }
    }

  /* access within limits */
  BX_CPU_THIS_PTR read_virtual_dword(BX_SEG_REG_SS, temp_ESP, value32_ptr);

  if (BX_CPU_THIS_PTR program_visible_sregs[BX_SEG_REG_SS].cache.u.segment.d_b==1)
    X86_ESP += 4;
  else
    X86_SP += 4;
}
#endif



#if BX_CPU_LEVEL >= 2
  Boolean
BX_CPU_C::can_push(bx_descriptor_t *descriptor, Bit32u esp, Bit32u bytes)
{
  if ( real_mode() ) { /* code not needed ??? */
    BX_PANIC(("can_push(): called in real mode"));
    return(0); /* never gets here */
    }

  // small stack compares against 16-bit SP
  if (!descriptor->u.segment.d_b)
    esp &= 0x0000ffff;


  if (descriptor->valid==0) {
    BX_PANIC(("can_push(): SS invalidated."));
    return(0);
    }

  if (descriptor->p==0) {
    BX_PANIC(("can_push(): not present"));
    return(0);
    }


  if (descriptor->u.segment.c_ed) { /* expand down segment */
    Bit32u expand_down_limit;

    if (descriptor->u.segment.d_b)
      expand_down_limit = 0xffffffff;
    else
      expand_down_limit = 0x0000ffff;

    if (esp==0) {
      BX_PANIC(("can_push(): esp=0, wraparound?"));
      return(0);
      }

    if (esp < bytes) {
      BX_PANIC(("can_push(): expand-down: esp < N"));
      return(0);
      }
    if ( (esp - bytes) <= descriptor->u.segment.limit_scaled ) {
      BX_PANIC(("can_push(): expand-down: esp-N < limit"));
      return(0);
      }
    if ( esp > expand_down_limit ) {
      BX_PANIC(("can_push(): esp > expand-down-limit"));
      return(0);
      }
    return(1);
    }
  else { /* normal (expand-up) segment */
    if (descriptor->u.segment.limit_scaled==0) {
      BX_PANIC(("can_push(): found limit of 0"));
      return(0);
      }

    // Look at case where esp==0.  Possibly, it's an intentional wraparound
    // If so, limit must be the maximum for the given stack size
    if (esp==0) {
      if (descriptor->u.segment.d_b && (descriptor->u.segment.limit_scaled==0xffffffff))
        return(1);
      if ((descriptor->u.segment.d_b==0) && (descriptor->u.segment.limit_scaled>=0xffff))
        return(1);
      BX_PANIC(("can_push(): esp=0, normal, wraparound? limit=%08x",
        descriptor->u.segment.limit_scaled));
      return(0);
      }

    if (esp < bytes) {
      BX_INFO(("can_push(): expand-up: esp < N"));
      return(0);
      }
    if ((esp-1) > descriptor->u.segment.limit_scaled) {
      BX_INFO(("can_push(): expand-up: SP > limit"));
      return(0);
      }
    /* all checks pass */
    return(1);
    }
}
#endif


#if BX_CPU_LEVEL >= 2
  Boolean
BX_CPU_C::can_pop(Bit32u bytes)
{
  Bit32u temp_ESP, expand_down_limit;

  /* ??? */
  if (real_mode())
  	BX_PANIC(("can_pop(): called in real mode?"));

  if (BX_CPU_THIS_PTR program_visible_sregs[BX_SEG_REG_SS].cache.u.segment.d_b) { /* Big bit set: use ESP */
    temp_ESP = X86_ESP;
    expand_down_limit = 0xFFFFFFFF;
    }
  else { /* Big bit clear: use SP */
    temp_ESP = X86_SP;
    expand_down_limit = 0xFFFF;
    }

  if (BX_CPU_THIS_PTR program_visible_sregs[BX_SEG_REG_SS].cache.valid==0) {
    BX_PANIC(("can_pop(): SS invalidated."));
    return(0); /* never gets here */
    }

  if (BX_CPU_THIS_PTR program_visible_sregs[BX_SEG_REG_SS].cache.p==0) { /* ??? */
    BX_PANIC(("can_pop(): SS.p = 0"));
    return(0);
    }


  if (BX_CPU_THIS_PTR program_visible_sregs[BX_SEG_REG_SS].cache.u.segment.c_ed) { /* expand down segment */
    if ( temp_ESP == expand_down_limit ) {
      BX_PANIC(("can_pop(): found SP=ffff"));
      return(0);
      }
    if ( ((expand_down_limit - temp_ESP) + 1) >= bytes )
      return(1);
    return(0);
    }
  else { /* normal (expand-up) segment */
    if (BX_CPU_THIS_PTR program_visible_sregs[BX_SEG_REG_SS].cache.u.segment.limit_scaled==0) {
      BX_PANIC(("can_pop(): SS.limit = 0"));
      }
    if ( temp_ESP == expand_down_limit ) {
      BX_PANIC(("can_pop(): found SP=ffff"));
      return(0);
      }
    if ( temp_ESP > BX_CPU_THIS_PTR program_visible_sregs[BX_SEG_REG_SS].cache.u.segment.limit_scaled ) {
      BX_PANIC(("can_pop(): eSP > SS.limit"));
      return(0);
      }
    if ( ((BX_CPU_THIS_PTR program_visible_sregs[BX_SEG_REG_SS].cache.u.segment.limit_scaled - temp_ESP) + 1) >= bytes )
      return(1);
    return(0);
    }
}
#endif
