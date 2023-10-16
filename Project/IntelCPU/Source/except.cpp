/////////////////////////////////////////////////////////////////////////
// $Id: exception.cc,v 1.12 2002/03/12 19:00:44 bdenney Exp $
/////////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "x86cpu.h"


/* Exception classes.  These are used as indexes into the 'is_exception_OK'
 * array below, and are stored in the 'exception' array also
 */
#define BX_ET_BENIGN       0
#define BX_ET_CONTRIBUTORY 1
#define BX_ET_PAGE_FAULT   2

#define BX_ET_DOUBLE_FAULT 10


const Boolean BX_CPU_C::is_exception_OK[3][3] = {
    { 1, 1, 1 }, /* 1st exception is BENIGN */
    { 1, 0, 1 }, /* 1st exception is CONTRIBUTORY */
    { 1, 0, 0 }  /* 1st exception is PAGE_FAULT */
    };


  void
BX_CPU_C::intel_interrupt(Bit8u _vector, Boolean is_INT, Boolean is_error_code,
                    Bit16u error_code)
{
#if BX_DEBUGGER
  if (bx_guard.special_unwind_stack) {
    BX_INFO (("intel_interrupt() returning early because special_unwind_stack is set"));
    return;
  }
  BX_CPU_THIS_PTR show_flag |= Flag_intsig;
#if BX_DEBUG_LINUX
  if (bx_dbg.linux_syscall) {
    if (_vector == 0x80) bx_dbg_linux_syscall ();
  }
#endif
#endif

//BX_DEBUG(( "::intel_interrupt(%u)", _vector ));

  BX_INSTR_INTERRUPT(_vector);
  invalidate_prefetch_q();

  // Discard any traps and inhibits for new context; traps will
  // resume upon return.
  BX_CPU_THIS_PTR debug_trap = 0;
  BX_CPU_THIS_PTR inhibit_mask = 0;

#if BX_CPU_LEVEL >= 2
//  unsigned prev_errno;

  BX_DEBUG(("intel_interrupt(): _vector = %u, INT = %u, EXT = %u",
      (unsigned) _vector, (unsigned) is_INT, (unsigned) BX_CPU_THIS_PTR EXT));

#if (X86CPU_MSWIN_MSDOS==1)
BX_CPU_THIS_PTR save_eflags = BX_CPU_THIS_PTR eflags;
#endif
BX_CPU_THIS_PTR save_cs  = BX_CPU_THIS_PTR program_visible_sregs[BX_SEG_REG_CS];
BX_CPU_THIS_PTR save_ss  = BX_CPU_THIS_PTR program_visible_sregs[BX_SEG_REG_SS];
BX_CPU_THIS_PTR save_eip = X86_EIP;
BX_CPU_THIS_PTR save_esp = X86_ESP;


//  prev_errno = BX_CPU_THIS_PTR errorno;

  if(!real_mode()) {
    Bit32u  dword1, dword2;
    bx_descriptor_t gate_descriptor, cs_descriptor;
    bx_selector_t cs_selector;

    Bit16u raw_tss_selector;
    bx_selector_t   tss_selector;
    bx_descriptor_t tss_descriptor;

    Bit16u gate_dest_selector;
    Bit32u gate_dest_offset;


    // intel_interrupt _vector must be within IDT table limits,
    // else #GP(_vector number*8 + 2 + EXT)
    if ( (_vector*8 + 7) > BX_CPU_THIS_PTR idtr.limit) {
      BX_DEBUG(("IDT.limit = %04x", (unsigned) BX_CPU_THIS_PTR idtr.limit));
      BX_DEBUG(("IDT.base  = %06x", (unsigned) BX_CPU_THIS_PTR idtr.base));
      BX_DEBUG(("intel_interrupt _vector must be within IDT table limits"));
      BX_DEBUG(("bailing"));
      BX_DEBUG(("intel_interrupt(): _vector > idtr.limit"));

      exception(BX_GP_EXCEPTION, _vector*8 + 2, 0);
      }

    // descriptor AR byte must indicate intel_interrupt gate, trap gate,
    // or task gate, else #GP(_vector*8 + 2 + EXT)
    BX_CPU_THIS_PTR access_linear(BX_CPU_THIS_PTR idtr.base + _vector*8,     4, 0,
      BX_READ, &dword1);
    BX_CPU_THIS_PTR access_linear(BX_CPU_THIS_PTR idtr.base + _vector*8 + 4, 4, 0,
      BX_READ, &dword2);

    parse_descriptor(dword1, dword2, &gate_descriptor);

    if ( (gate_descriptor.valid==0) || gate_descriptor.segment) {
      BX_DEBUG(("intel_interrupt(): gate descriptor is not valid sys seg"));
      exception(BX_GP_EXCEPTION, _vector*8 + 2, 0);
      }

    switch (gate_descriptor.type) {
      case 5: // task gate
      case 6: // 286 intel_interrupt gate
      case 7: // 286 trap gate
      case 14: // 386 intel_interrupt gate
      case 15: // 386 trap gate
        break;
      default:
        BX_DEBUG(("intel_interrupt(): gate.type(%u) != {5,6,7,14,15}",
          (unsigned) gate_descriptor.type));
        exception(BX_GP_EXCEPTION, _vector*8 + 2, 0);
        return;
      }

    // if software intel_interrupt, then gate descripor DPL must be >= CPL,
    // else #GP(_vector * 8 + 2 + EXT)
    if (is_INT  &&  (gate_descriptor.dpl < CPL)) {
/* ??? */
      BX_DEBUG(("intel_interrupt(): is_INT && (dpl < CPL)"));
      exception(BX_GP_EXCEPTION, _vector*8 + 2, 0);
      return;
      }

    // Gate must be present, else #NP(_vector * 8 + 2 + EXT)
    if (gate_descriptor.p == 0) {
      BX_DEBUG(("intel_interrupt(): p == 0"));
      exception(BX_NP_EXCEPTION, _vector*8 + 2, 0);
      }

    switch (gate_descriptor.type) {
      case 5: // 286/386 task gate
        // examine selector to TSS, given in task gate descriptor
        raw_tss_selector = gate_descriptor.u.taskgate.tss_selector;
        parse_selector(raw_tss_selector, &tss_selector);

        // must specify global in the local/global bit,
        //      else #TS(TSS selector)
// +++
// 486/Pent books say #TSS(selector)
// PPro+ says #GP(selector)
        if (tss_selector.ti) {
          BX_PANIC(("intel_interrupt: tss_selector.ti=1"));
          exception(BX_TS_EXCEPTION, raw_tss_selector & 0xfffc, 0);
          return;
          }

        // index must be within GDT limits, else #TS(TSS selector)
        fetch_raw_descriptor(&tss_selector, &dword1, &dword2,
          BX_TS_EXCEPTION);

        // AR byte must specify available TSS,
        //   else #TS(TSS selector)
        parse_descriptor(dword1, dword2, &tss_descriptor);
        if (tss_descriptor.valid==0 || tss_descriptor.segment) {
          BX_PANIC(("exception: TSS selector points to bad TSS"));
          exception(BX_TS_EXCEPTION, raw_tss_selector & 0xfffc, 0);
          return;
          }
        if (tss_descriptor.type!=9 && tss_descriptor.type!=1) {
          BX_PANIC(("exception: TSS selector points to bad TSS"));
          exception(BX_TS_EXCEPTION, raw_tss_selector & 0xfffc, 0);
          return;
          }


        // TSS must be present, else #NP(TSS selector)
        // done in task_switch()

        // switch tasks with nesting to TSS
        task_switch(&tss_selector, &tss_descriptor,
                    BX_TASK_FROM_CALL_OR_INT, dword1, dword2);

        // if intel_interrupt was caused by fault with error code
        //   stack limits must allow push of 2 more bytes, else #SS(0)
        // push error code onto stack

        //??? push_16 vs push_32
        if ( is_error_code ) {
          //if (tss_descriptor.type==9)
          if (BX_CPU_THIS_PTR program_visible_sregs[BX_SEG_REG_CS].cache.u.segment.d_b)
            call_push_32(error_code);
          else
            call_push_16(error_code);
          }

        // instruction pointer must be in CS limit, else #GP(0)
        //if (BX_EIP > cs_descriptor.u.segment.limit_scaled) {}
        if (X86_EIP > BX_CPU_THIS_PTR program_visible_sregs[BX_SEG_REG_CS].cache.u.segment.limit_scaled) {
          BX_PANIC(("exception(): eIP > CS.limit"));
          exception(BX_GP_EXCEPTION, 0x0000, 0);
          }
        return;
        break;

      case 6: // 286 intel_interrupt gate
      case 7: // 286 trap gate
      case 14: // 386 intel_interrupt gate
      case 15: // 386 trap gate
        if ( gate_descriptor.type >= 14 ) { // 386 gate
          gate_dest_selector = gate_descriptor.u.gate386.dest_selector;
          gate_dest_offset   = gate_descriptor.u.gate386.dest_offset;
          }
        else { // 286 gate
          gate_dest_selector = gate_descriptor.u.gate286.dest_selector;
          gate_dest_offset   = gate_descriptor.u.gate286.dest_offset;
          }

        // examine CS selector and descriptor given in gate descriptor
        // selector must be non-null else #GP(EXT)
        if ( (gate_dest_selector & 0xfffc) == 0 ) {
          BX_PANIC(("int_trap_gate(): selector null"));
          exception(BX_GP_EXCEPTION, 0, 0);
          }

        parse_selector(gate_dest_selector, &cs_selector);

        // selector must be within its descriptor table limits
        // else #GP(selector+EXT)
        fetch_raw_descriptor(&cs_selector, &dword1, &dword2,
                                BX_GP_EXCEPTION);
        parse_descriptor(dword1, dword2, &cs_descriptor);

        // descriptor AR byte must indicate code seg
        // and code segment descriptor DPL<=CPL, else #GP(selector+EXT)
        if ( cs_descriptor.valid==0 ||
             cs_descriptor.segment==0 ||
             cs_descriptor.u.segment.executable==0 ||
             cs_descriptor.dpl>CPL ) {
          BX_DEBUG(("intel_interrupt(): not code segment"));
          exception(BX_GP_EXCEPTION, cs_selector.value & 0xfffc, 0);
          }

        // segment must be present, else #NP(selector + EXT)
        if ( cs_descriptor.p==0 ) {
          BX_DEBUG(("intel_interrupt(): segment not present"));
          exception(BX_NP_EXCEPTION, cs_selector.value & 0xfffc, 0);
          }

        // if code segment is non-conforming and DPL < CPL then
        // INTERRUPT TO INNER PRIVILEGE:
        if ( cs_descriptor.u.segment.c_ed==0 && cs_descriptor.dpl<CPL ) {
          Bit16u old_SS, old_CS, SS_for_cpl_x;
          Bit32u ESP_for_cpl_x, old_EIP, old_ESP;
          bx_descriptor_t ss_descriptor;
          bx_selector_t   ss_selector;
          int bytes;

          BX_DEBUG(("intel_interrupt(): INTERRUPT TO INNER PRIVILEGE"));

          // check selector and descriptor for new stack in current TSS
          get_SS_ESP_from_TSS(cs_descriptor.dpl,
                              &SS_for_cpl_x, &ESP_for_cpl_x);

          // Selector must be non-null else #TS(EXT)
          if ( (SS_for_cpl_x & 0xfffc) == 0 ) {
            BX_PANIC(("intel_interrupt(): SS selector null"));
            /* TS(ext) */
            exception(BX_TS_EXCEPTION, 0, 0);
            }

          // selector index must be within its descriptor table limits
          // else #TS(SS selector + EXT)
          parse_selector(SS_for_cpl_x, &ss_selector);
          // fetch 2 dwords of descriptor; call handles out of limits checks
          fetch_raw_descriptor(&ss_selector, &dword1, &dword2,
                                  BX_TS_EXCEPTION);
          parse_descriptor(dword1, dword2, &ss_descriptor);

          // selector rpl must = dpl of code segment,
          // else #TS(SS selector + ext)
          if (ss_selector.rpl != cs_descriptor.dpl) {
            BX_PANIC(("intel_interrupt(): SS.rpl != CS.dpl"));
            exception(BX_TS_EXCEPTION, SS_for_cpl_x & 0xfffc, 0);
            }

          // stack seg DPL must = DPL of code segment,
          // else #TS(SS selector + ext)
          if (ss_descriptor.dpl != cs_descriptor.dpl) {
            BX_PANIC(("intel_interrupt(): SS.dpl != CS.dpl"));
            exception(BX_TS_EXCEPTION, SS_for_cpl_x & 0xfffc, 0);
            }

          // descriptor must indicate writable data segment,
          // else #TS(SS selector + EXT)
          if (ss_descriptor.valid==0 ||
              ss_descriptor.segment==0  ||
              ss_descriptor.u.segment.executable==1  ||
              ss_descriptor.u.segment.r_w==0) {
            BX_PANIC(("intel_interrupt(): SS not writable data segment"));
            exception(BX_TS_EXCEPTION, SS_for_cpl_x & 0xfffc, 0);
            }

          // seg must be present, else #SS(SS selector + ext)
          if (ss_descriptor.p==0) {
            BX_PANIC(("intel_interrupt(): SS not present"));
            exception(BX_SS_EXCEPTION, SS_for_cpl_x & 0xfffc, 0);
            }

          if (gate_descriptor.type>=14) {
            // 386 int/trap gate
            // new stack must have room for 20|24 bytes, else #SS(0)
            if ( is_error_code )
              bytes = 24;
            else
              bytes = 20;
            if (v8086_mode())
              bytes += 16;
            }
          else {
            // new stack must have room for 10|12 bytes, else #SS(0)
            if ( is_error_code )
              bytes = 12;
            else
              bytes = 10;
            if (v8086_mode()) {
              bytes += 8;
              BX_PANIC(("intel_interrupt: int/trap gate VM"));
              }
            }

// 486,Pentium books
// new stack must have room for 10/12 bytes, else #SS(0) 486 book
// PPro+
// new stack must have room for 10/12 bytes, else #SS(seg selector)
          if ( !can_push(&ss_descriptor, ESP_for_cpl_x, bytes) ) {
            BX_PANIC(("intel_interrupt(): new stack doesn't have room for %u bytes",
               (unsigned) bytes));
            // SS(???)
            }

          // IP must be within CS segment boundaries, else #GP(0)
          if (gate_dest_offset > cs_descriptor.u.segment.limit_scaled) {
            BX_PANIC(("intel_interrupt(): gate eIP > CS.limit"));
            exception(BX_GP_EXCEPTION, 0, 0);
            }

          old_ESP = X86_ESP;
          old_SS  = BX_CPU_THIS_PTR program_visible_sregs[BX_SEG_REG_SS].selector.value;
          old_EIP = X86_EIP;
          old_CS  = BX_CPU_THIS_PTR program_visible_sregs[BX_SEG_REG_CS].selector.value;

          // load new SS:SP values from TSS
          load_ss(&ss_selector, &ss_descriptor, cs_descriptor.dpl);

          if (ss_descriptor.u.segment.d_b)
            X86_ESP = ESP_for_cpl_x;
          else
            X86_SP = ESP_for_cpl_x; // leave upper 16bits

          // load new CS:IP values from gate
          // set CPL to new code segment DPL
          // set RPL of CS to CPL
          load_cs(&cs_selector, &cs_descriptor, cs_descriptor.dpl);
          X86_EIP = gate_dest_offset;

          if (gate_descriptor.type>=14) { // 386 int/trap gate
            if (v8086_mode()) {
              call_push_32(BX_CPU_THIS_PTR program_visible_sregs[BX_SEG_REG_GS].selector.value);
              call_push_32(BX_CPU_THIS_PTR program_visible_sregs[BX_SEG_REG_FS].selector.value);
              call_push_32(BX_CPU_THIS_PTR program_visible_sregs[BX_SEG_REG_DS].selector.value);
              call_push_32(BX_CPU_THIS_PTR program_visible_sregs[BX_SEG_REG_ES].selector.value);
              BX_CPU_THIS_PTR program_visible_sregs[BX_SEG_REG_GS].cache.valid = 0;
              BX_CPU_THIS_PTR program_visible_sregs[BX_SEG_REG_GS].selector.value = 0;
              BX_CPU_THIS_PTR program_visible_sregs[BX_SEG_REG_FS].cache.valid = 0;
              BX_CPU_THIS_PTR program_visible_sregs[BX_SEG_REG_FS].selector.value = 0;
              BX_CPU_THIS_PTR program_visible_sregs[BX_SEG_REG_DS].cache.valid = 0;
              BX_CPU_THIS_PTR program_visible_sregs[BX_SEG_REG_DS].selector.value = 0;
              BX_CPU_THIS_PTR program_visible_sregs[BX_SEG_REG_ES].cache.valid = 0;
              BX_CPU_THIS_PTR program_visible_sregs[BX_SEG_REG_ES].selector.value = 0;
              }
            // push long pointer to old stack onto new stack
            call_push_32(old_SS);
            call_push_32(old_ESP);

            // push EFLAGS
            call_push_32(read_eflags());

            // push long pointer to return address onto new stack
            call_push_32(old_CS);
            call_push_32(old_EIP);

            if ( is_error_code )
              call_push_32(error_code);
            }
          else { // 286 int/trap gate
            if (v8086_mode()) {
              BX_PANIC(("286 int/trap gate, VM"));
              }
            // push long pointer to old stack onto new stack
            call_push_16(old_SS);
            call_push_16(old_ESP); // ignores upper 16bits

            // push FLAGS
            call_push_16(read_flags());

            // push return address onto new stack
            call_push_16(old_CS);
            call_push_16(old_EIP); // ignores upper 16bits

            if ( is_error_code )
              call_push_16(error_code);
            }

          // if INTERRUPT GATE set IF to 0
          if ( !(gate_descriptor.type & 1) ) // even is int-gate
            BX_CPU_THIS_PTR eflags.if_ = 0;
          BX_CPU_THIS_PTR eflags.tf = 0;
          BX_CPU_THIS_PTR eflags.vm = 0;
          BX_CPU_THIS_PTR eflags.rf = 0;
          BX_CPU_THIS_PTR eflags.nt = 0;
          return;
          }

        if (v8086_mode()) {
          exception(BX_GP_EXCEPTION, cs_selector.value & 0xfffc, 0);
          }

        // if code segment is conforming OR code segment DPL = CPL then
        // INTERRUPT TO SAME PRIVILEGE LEVEL:
        if ( cs_descriptor.u.segment.c_ed==1 || cs_descriptor.dpl==CPL ) {
          int bytes;
          Bit32u temp_ESP;

          if (BX_CPU_THIS_PTR program_visible_sregs[BX_SEG_REG_SS].cache.u.segment.d_b)
            temp_ESP = X86_ESP;
          else
            temp_ESP = X86_SP;

          BX_DEBUG(("int_trap_gate286(): INTERRUPT TO SAME PRIVILEGE"));

          // Current stack limits must allow pushing 6|8 bytes, else #SS(0)
          if (gate_descriptor.type >= 14) { // 386 gate
            if ( is_error_code )
              bytes = 16;
            else
              bytes = 12;
            }
          else { // 286 gate
            if ( is_error_code )
              bytes = 8;
            else
              bytes = 6;
            }

          if ( !can_push(&BX_CPU_THIS_PTR program_visible_sregs[BX_SEG_REG_SS].cache,
                         temp_ESP, bytes) ) {
            BX_DEBUG(("intel_interrupt(): stack doesn't have room"));
            exception(BX_SS_EXCEPTION, 0, 0);
            }

          // eIP must be in CS limit else #GP(0)
          if (gate_dest_offset > cs_descriptor.u.segment.limit_scaled) {
            BX_PANIC(("intel_interrupt(): IP > cs descriptor limit"));
            exception(BX_GP_EXCEPTION, 0, 0);
            }

          // push flags onto stack
          // push current CS selector onto stack
          // push return offset onto stack
          if (gate_descriptor.type >= 14) { // 386 gate
            call_push_32(read_eflags());
            call_push_32(BX_CPU_THIS_PTR program_visible_sregs[BX_SEG_REG_CS].selector.value);
            call_push_32(X86_EIP);
            if ( is_error_code )
              call_push_32(error_code);
            }
          else { // 286 gate
            call_push_16(read_flags());
            call_push_16(BX_CPU_THIS_PTR program_visible_sregs[BX_SEG_REG_CS].selector.value);
            call_push_16(X86_IP);
            if ( is_error_code )
              call_push_16(error_code);
            }

          // load CS:IP from gate
          // load CS descriptor
          // set the RPL field of CS to CPL
          load_cs(&cs_selector, &cs_descriptor, CPL);
          X86_EIP = gate_dest_offset;

          // if intel_interrupt gate then set IF to 0
          if ( !(gate_descriptor.type & 1) ) // even is int-gate
            BX_CPU_THIS_PTR eflags.if_ = 0;
          BX_CPU_THIS_PTR eflags.tf = 0;
          BX_CPU_THIS_PTR eflags.nt = 0;
          BX_CPU_THIS_PTR eflags.vm = 0;
          BX_CPU_THIS_PTR eflags.rf = 0;
          return;
          }

        // else #GP(CS selector + ext)
        BX_DEBUG(("intel_interrupt: bad descriptor"));
        BX_DEBUG(("c_ed=%u, descriptor.dpl=%u, CPL=%u",
          (unsigned) cs_descriptor.u.segment.c_ed,
          (unsigned) cs_descriptor.dpl,
          (unsigned) CPL));
        BX_DEBUG(("cs.segment = %u", (unsigned) cs_descriptor.segment));
        exception(BX_GP_EXCEPTION, cs_selector.value & 0xfffc, 0);
        break;

      default:
        BX_PANIC(("bad descriptor type in intel_interrupt()!"));
        break;
      }
    }
  else
#endif
    { /* real mode */
    Bit16u cs_selector, ip;

#define _T_DEBUG_ 0

#if _T_DEBUG_	
	bx_segment_reg_t *tempseg;
#endif

    if ( (_vector*4+3) > BX_CPU_THIS_PTR idtr.limit )
      BX_PANIC(("intel_interrupt(real mode) _vector > limit"));

    call_push_16(read_flags());

    cs_selector = BX_CPU_THIS_PTR program_visible_sregs[BX_SEG_REG_CS].selector.value;
    call_push_16(cs_selector);
    ip = BX_CPU_THIS_PTR program_visible_eip;
    call_push_16(ip);

#if _T_DEBUG_	
	tempseg = &BX_CPU_THIS_PTR program_visible_sregs[BX_SEG_REG_CS];
	printf("_vector==%02x, ip == %04x,cs_selector == %04x\n",_vector,ip,cs_selector);
	printf("base ==%08x, cs_selector == %04x,eip == %08x\n",tempseg->cache.u.segment.base,tempseg->selector.value,X86_EIP);
#endif

    BX_CPU_THIS_PTR access_linear(BX_CPU_THIS_PTR idtr.base + 4 * _vector,     2, 0, BX_READ, &ip);
    X86_EIP = ip;
    BX_CPU_THIS_PTR access_linear(BX_CPU_THIS_PTR idtr.base + 4 * _vector + 2, 2, 0, BX_READ, &cs_selector);
    load_seg_reg(&BX_CPU_THIS_PTR program_visible_sregs[BX_SEG_REG_CS], cs_selector);

#if _T_DEBUG_	
	tempseg = &BX_CPU_THIS_PTR program_visible_sregs[BX_SEG_REG_CS];
	printf("=_vector==%02x, ip == %04x,cs_selector == %04x\n",_vector,ip,cs_selector);
	printf("=base ==%08x, cs_selector == %04x,eip == %08x\n",tempseg->cache.u.segment.base,tempseg->selector.value,X86_EIP);
#endif

    /* INT affects the following flags: I,T */
    BX_CPU_THIS_PTR eflags.if_ = 0;
    BX_CPU_THIS_PTR eflags.tf  = 0;
#if BX_CPU_LEVEL >= 4
    BX_CPU_THIS_PTR eflags.ac  = 0;
#endif
    BX_CPU_THIS_PTR eflags.rf = 0;
    }
}

  void
BX_CPU_C::exception(unsigned _vector, Bit16u error_code, Boolean is_INT)
  // _vector:     0..255: _vector in IDT
  // error_code: if exception generates and error, push this error code
{
  Boolean  push_error;
  Bit8u    exception_type;
  unsigned prev_errno;

#if BX_DEBUGGER
  if (bx_guard.special_unwind_stack) {
    BX_INFO (("exception() returning early because special_unwind_stack is set"));
    return;
  }
#endif

//BX_DEBUG(( "::exception(%u)", _vector ));

  BX_INSTR_EXCEPTION(_vector);
  invalidate_prefetch_q();

  BX_CPU_THIS_PTR intNumber = _vector;

  UNUSED(is_INT);

  BX_DEBUG(("exception(%02x h)", (unsigned) _vector));

  // if not initial error, restore previous register values from
  // previous attempt to handle exception
  if (BX_CPU_THIS_PTR errorno) {
    BX_CPU_THIS_PTR program_visible_sregs[BX_SEG_REG_CS]  = BX_CPU_THIS_PTR save_cs;
    BX_CPU_THIS_PTR program_visible_sregs[BX_SEG_REG_SS]  = BX_CPU_THIS_PTR save_ss;
    X86_EIP = BX_CPU_THIS_PTR save_eip;
    X86_ESP = BX_CPU_THIS_PTR save_esp;
    }

  BX_CPU_THIS_PTR errorno++;
  if (BX_CPU_THIS_PTR errorno >= 3) {
    BX_PANIC(("exception(): 3rd exception with no resolution"));
    BX_ERROR(("WARNING: Any simulation after this point is completely bogus."));
#if BX_DEBUGGER
    bx_guard.special_unwind_stack = true;
#endif
	shutdown_cpu();
    return;
    }

  /* careful not to get here with curr_exception[1]==DOUBLE_FAULT */
  /* ...index on DOUBLE_FAULT below, will be out of bounds */

  /* if 1st was a double fault (software INT?), then shutdown */
  if ( (BX_CPU_THIS_PTR errorno==2) && (BX_CPU_THIS_PTR curr_exception[0]==BX_ET_DOUBLE_FAULT) ) {
    BX_PANIC(("exception(): triple fault encountered"));
    BX_ERROR(("WARNING: Any simulation after this point is completely bogus."));
#if BX_DEBUGGER
    bx_guard.special_unwind_stack = true;
#endif
	shutdown_cpu();
    return;
    }

  /* ??? this is not totally correct, should be done depending on
   * _vector */
  /* backup IP to value before error occurred */
  X86_EIP = BX_CPU_THIS_PTR prev_eip;
  X86_ESP = BX_CPU_THIS_PTR prev_esp;

  // note: fault-class exceptions _except_ #DB set RF in
  //       eflags image.

  switch (_vector) {
    case  0: // DIV by 0
      push_error = 0;
      exception_type = BX_ET_CONTRIBUTORY;
      BX_CPU_THIS_PTR eflags.rf = 1;
      break;
    case  1: // debug exceptions
      push_error = 0;
      exception_type = BX_ET_BENIGN;
      break;
    case  2: // NMI
      push_error = 0;
      exception_type = BX_ET_BENIGN;
      break;
    case  3: // breakpoint
      push_error = 0;
      exception_type = BX_ET_BENIGN;
      break;
    case  4: // overflow
      push_error = 0;
      exception_type = BX_ET_BENIGN;
      break;
    case  5: // bounds check
      push_error = 0;
      exception_type = BX_ET_BENIGN;
      BX_CPU_THIS_PTR eflags.rf = 1;
      break;
    case  6: // invalid opcode
      push_error = 0;
      exception_type = BX_ET_BENIGN;
      BX_CPU_THIS_PTR eflags.rf = 1;
      break;
    case  7: // device not available
      push_error = 0;
      exception_type = BX_ET_BENIGN;
      BX_CPU_THIS_PTR eflags.rf = 1;
      break;
    case  8: // double fault
      push_error = 1;
      exception_type = BX_ET_DOUBLE_FAULT;
      break;
    case  9: // coprocessor segment overrun (286,386 only)
      push_error = 0;
      exception_type = BX_ET_CONTRIBUTORY;
      BX_CPU_THIS_PTR eflags.rf = 1;
      BX_PANIC(("exception(9): unfinished"));
      break;
    case 10: // invalid TSS
      push_error = 1;
      exception_type = BX_ET_CONTRIBUTORY;
      error_code = (error_code & 0xfffe) | BX_CPU_THIS_PTR EXT;
      BX_CPU_THIS_PTR eflags.rf = 1;
      break;
    case 11: // segment not present
      push_error = 1;
      exception_type = BX_ET_CONTRIBUTORY;
      error_code = (error_code & 0xfffe) | BX_CPU_THIS_PTR EXT;
      BX_CPU_THIS_PTR eflags.rf = 1;
      break;
    case 12: // stack fault
      push_error = 1;
      exception_type = BX_ET_CONTRIBUTORY;
      error_code = (error_code & 0xfffe) | BX_CPU_THIS_PTR EXT;
      BX_CPU_THIS_PTR eflags.rf = 1;
      break;
    case 13: // general protection
      push_error = 1;
      exception_type = BX_ET_CONTRIBUTORY;
      error_code = (error_code & 0xfffe) | BX_CPU_THIS_PTR EXT;
      BX_CPU_THIS_PTR eflags.rf = 1;
      break;
    case 14: // page fault
      push_error = 1;
      exception_type = BX_ET_PAGE_FAULT;
      // ??? special format error returned
      BX_CPU_THIS_PTR eflags.rf = 1;
      break;
    case 15: // reserved
      BX_PANIC(("exception(15): reserved"));
      push_error = 0;     // keep compiler happy for now
      exception_type = 0; // keep compiler happy for now
      break;
    case 16: // floating-point error
      push_error = 0;
      exception_type = BX_ET_BENIGN;
      BX_CPU_THIS_PTR eflags.rf = 1;
      break;
#if BX_CPU_LEVEL >= 4
    case 17: // alignment check
      BX_PANIC(("exception(): alignment-check, _vector 17 unimplemented"));
      push_error = 0;     // keep compiler happy for now
      exception_type = 0; // keep compiler happy for now
      BX_CPU_THIS_PTR eflags.rf = 1;
      break;
#endif
#if BX_CPU_LEVEL >= 5
    case 18: // machine check
      BX_PANIC(("exception(): machine-check, _vector 18 unimplemented"));
      push_error = 0;     // keep compiler happy for now
      exception_type = 0; // keep compiler happy for now
      break;
#endif
    default:
      BX_PANIC(("exception(%u): bad _vector", (unsigned) _vector));
      push_error = 0;     // keep compiler happy for now
      exception_type = 0; // keep compiler happy for now
      break;
    }

  if (exception_type != BX_ET_PAGE_FAULT) {
    // Page faults have different format
    error_code = (error_code & 0xfffe) | BX_CPU_THIS_PTR EXT;
    }
  BX_CPU_THIS_PTR EXT = 1;

  /* if we've already had 1st exception, see if 2nd causes a
   * Double Fault instead.  Otherwise, just record 1st exception
   */
  if (BX_CPU_THIS_PTR errorno >= 2) {
    if (is_exception_OK[BX_CPU_THIS_PTR curr_exception[0]][exception_type])
      BX_CPU_THIS_PTR curr_exception[1] = exception_type;
    else {
      BX_CPU_THIS_PTR curr_exception[1] = BX_ET_DOUBLE_FAULT;
      _vector = 8;
    }
  }
  else {
    BX_CPU_THIS_PTR curr_exception[0] = exception_type;
  }


#if BX_CPU_LEVEL >= 2
  if (!real_mode()) {
    prev_errno = BX_CPU_THIS_PTR errorno;
    BX_CPU_THIS_PTR intel_interrupt(_vector, 0, push_error, error_code);
//    if (BX_CPU_THIS_PTR errorno > prev_errno) {
//      BX_INFO(("segment_exception(): errorno changed"));
//      longjmp(jmp_buf_env, 1); // go back to main decode loop
//      return;
//      }

//    if (push_error) {
//      /* push error code on stack, after handling intel_interrupt */
//      /* pushed as a word or dword depending upon default size ??? */
//      if (ss.cache.u.segment.d_b)
//        call_push_32((Bit32u) error_code); /* upper bits reserved */
//      else
//        call_push_16(error_code);
//      if (BX_CPU_THIS_PTR errorno > prev_errno) {
//        BX_PANIC(("segment_exception(): errorno changed"));
//        return;
//        }
//      }
    BX_CPU_THIS_PTR errorno = 0; // error resolved
    longjmp(BX_CPU_THIS_PTR jmp_buf_env, 1); // go back to main decode loop
    }
  else // real mode
#endif
    {
    // not INT, no error code pushed
    BX_CPU_THIS_PTR intel_interrupt(_vector, 0, 0, 0);
    BX_CPU_THIS_PTR errorno = 0; // error resolved
    longjmp(BX_CPU_THIS_PTR jmp_buf_env, 1); // go back to main decode loop
    }
}


  int
BX_CPU_C::int_number(bx_segment_reg_t *seg)
{
  if (seg == &BX_CPU_THIS_PTR program_visible_sregs[BX_SEG_REG_SS])
    return(BX_SS_EXCEPTION);
  else
    return(BX_GP_EXCEPTION);
}

  void
BX_CPU_C::shutdown_cpu(void)
{

#if BX_CPU_LEVEL > 2
  BX_PANIC(("shutdown_cpu(): not implemented for 386"));
#endif

  invalidate_prefetch_q();
  BX_PANIC(("shutdown_cpu(): not finished"));

  longjmp(BX_CPU_THIS_PTR jmp_buf_env, 2); // go back to main decode loop
}
