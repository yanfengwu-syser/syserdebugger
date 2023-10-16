/////////////////////////////////////////////////////////////////////////
// $Id: cpu.cc,v 1.25 2002/03/20 23:50:23 bdenney Exp $
/////////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "x86cpu.h"

/*
__declspec(naked)int mysetjump(MY_JUMP_BUFFER *jump_buff)
{
	unsigned int *p;
	unsigned int save_Eax;
	unsigned int save_Edx;
	unsigned int save_Ecx;
	unsigned int save_Ebx;
	unsigned int save_Esp;
	unsigned int save_Ebp;
	unsigned int save_Esi;
	unsigned int save_Edi;
	unsigned int save_Eip;

	__asm
	{
		push   ebp
		mov      ebp, esp
		sub      esp, __LOCAL_SIZE
	}

	__asm
	{
		mov save_Eax,Eax 
		mov save_Edx,Edx 
		mov save_Ecx,Ecx 
		mov save_Ebx,Ebx 
		mov save_Esp,Esp 
		mov save_Ebp,Ebp 
		mov save_Esi,Esi 
		mov save_Edi,Edi 
	}
	jump_buff->Eax = save_Eax;
	jump_buff->Edx = save_Edx;
	jump_buff->Ecx = save_Ecx;
	jump_buff->Ebx = save_Ebx;
	jump_buff->Esp = save_Esp;
	jump_buff->Ebp = save_Ebp;
	jump_buff->Esi = save_Esi;
	jump_buff->Edi = save_Edi;
	jump_buff->Eip = save_Eip;

	jump_buff->Esp = save_Ebp;
	p = (unsigned int *)(save_Ebp);
	jump_buff->Ebp = *(p+0);
	jump_buff->Eip = *(p+1);

	jump_buff->check_s = 0x55aaaa55;
	jump_buff->check_e = 0x55aaaa55;

	__asm  
	{
		xor      eax,eax
		mov      esp, ebp
		pop      ebp
		ret
	}

}

void mylongjump(MY_JUMP_BUFFER *jump_buff,unsigned int code)
{
	if (jump_buff->check_s != 0x55aaaa55 ||
        jump_buff->check_e != 0x55aaaa55)
	{
		__asm int 3;
	}

	__asm
	{
			mov eax,code
			mov ebx,jump_buff

			//		mov Eax,[ebx]MY_JUMP_BUFFER.Eax
			//		mov Edx,[ebx]MY_JUMP_BUFFER.Edx
			//		mov Ecx,[ebx]MY_JUMP_BUFFER.Ecx
			//		mov Ebx,[ebx]MY_JUMP_BUFFER.Ebx
			mov Esp,[ebx]MY_JUMP_BUFFER.Esp
			mov Ebp,[ebx]MY_JUMP_BUFFER.Ebp
			mov Esi,[ebx]MY_JUMP_BUFFER.Esi
			mov Edi,[ebx]MY_JUMP_BUFFER.Edi

			mov ecx,[ebx]MY_JUMP_BUFFER.Ebp
			mov edx,[ebx]MY_JUMP_BUFFER.Eip

			mov dword ptr [esp+0],ecx
			mov dword ptr [esp+4],edx 

			mov Edx,[ebx]MY_JUMP_BUFFER.Edx
			mov Ecx,[ebx]MY_JUMP_BUFFER.Ecx
			mov Ebx,[ebx]MY_JUMP_BUFFER.Ebx
			pop Ebp 
			ret
	}

	return ;
}
*/
#define BX_INSTR_SPY 0

//unsigned counter[2] = { 0, 0 };



#if BX_SIM_ID == 0   // only need to define once
// This array defines a look-up table for the even parity-ness
// of an 8bit quantity, for optimal assignment of the parity bit
// in the EFLAGS register
const Boolean bx_parity_lookup[256] = {
  1, 0, 0, 1, 0, 1, 1, 0, 0, 1, 1, 0, 1, 0, 0, 1,
  0, 1, 1, 0, 1, 0, 0, 1, 1, 0, 0, 1, 0, 1, 1, 0,
  0, 1, 1, 0, 1, 0, 0, 1, 1, 0, 0, 1, 0, 1, 1, 0,
  1, 0, 0, 1, 0, 1, 1, 0, 0, 1, 1, 0, 1, 0, 0, 1,
  0, 1, 1, 0, 1, 0, 0, 1, 1, 0, 0, 1, 0, 1, 1, 0,
  1, 0, 0, 1, 0, 1, 1, 0, 0, 1, 1, 0, 1, 0, 0, 1,
  1, 0, 0, 1, 0, 1, 1, 0, 0, 1, 1, 0, 1, 0, 0, 1,
  0, 1, 1, 0, 1, 0, 0, 1, 1, 0, 0, 1, 0, 1, 1, 0,
  0, 1, 1, 0, 1, 0, 0, 1, 1, 0, 0, 1, 0, 1, 1, 0,
  1, 0, 0, 1, 0, 1, 1, 0, 0, 1, 1, 0, 1, 0, 0, 1,
  1, 0, 0, 1, 0, 1, 1, 0, 0, 1, 1, 0, 1, 0, 0, 1,
  0, 1, 1, 0, 1, 0, 0, 1, 1, 0, 0, 1, 0, 1, 1, 0,
  1, 0, 0, 1, 0, 1, 1, 0, 0, 1, 1, 0, 1, 0, 0, 1,
  0, 1, 1, 0, 1, 0, 0, 1, 1, 0, 0, 1, 0, 1, 1, 0,
  0, 1, 1, 0, 1, 0, 0, 1, 1, 0, 0, 1, 0, 1, 1, 0,
  1, 0, 0, 1, 0, 1, 1, 0, 0, 1, 1, 0, 1, 0, 0, 1
  };
#endif


#if (X86CPU_MSWIN_MSDOS==1)
bx_debug_t bx_dbg;
#endif

#if BX_SMP_PROCESSORS==1
// single processor simulation, so there's one of everything
BX_CPU_C    bx_cpu;
BX_MEM_C    bx_mem;
#else
// multiprocessor simulation, we need an array of cpus and memories
BX_CPU_C    *bx_cpu_array[BX_SMP_PROCESSORS+1];
BX_MEM_C    *bx_mem_array[BX_ADDRESS_SPACES+1];
#endif

// notes:
//
// check limit of CS?

#ifdef REGISTER_IADDR
extern void REGISTER_IADDR(Bit32u addr);
#endif

// The CHECK_MAX_INSTRUCTIONS macro allows cpu_loop to execute a few
// instructions and then return so that the other processors have a chance to
// run.  This is used only when simulating multiple processors.
// 
// If maximum instructions have been executed, return.  A count less
// than zero means run forever.
#define CHECK_MAX_INSTRUCTIONS(count) if (count >= 0) { count--; if (count == 0) return; }

#if BX_SMP_PROCESSORS==1
#  define BX_TICK1_IF_SINGLE_PROCESSOR() BX_TICK1()
#else
#  define BX_TICK1_IF_SINGLE_PROCESSOR()
#endif

#if BX_DYNAMIC_TRANSLATION == 0

	void
BX_CPU_C::cpu_loop(Bit32s max_instr_count)
{
	unsigned ilength;
	bxInstruction_c i;
	Bit8u *fetch_ptr;
	Boolean is_32;

#if BX_DEBUGGER
	BX_CPU_THIS_PTR break_point = 0;
#ifdef MAGIC_BREAKPOINT
	BX_CPU_THIS_PTR magic_break = 0;
#endif
	BX_CPU_THIS_PTR stop_reason = STOP_NO_REASON;
#endif

	(void) setjmp( BX_CPU_THIS_PTR jmp_buf_env );

	// not sure if these two are used during the async handling... --bbd
	BX_CPU_THIS_PTR prev_eip = X86_EIP; // commit new EIP
	BX_CPU_THIS_PTR prev_esp = X86_ESP; // commit new ESP

main_cpu_loop:
	
	// ???
	BX_CPU_THIS_PTR EXT = 0;
	BX_CPU_THIS_PTR errorno = 0;

	// First check on events which occurred for previous instructions
	// (traps) and ones which are asynchronous to the CPU
	// (hardware interrupts).
	if (BX_CPU_THIS_PTR async_event)
		goto handle_async_event;

async_events_processed:
  // added so that all debugging/tracing code uses the correct EIP even in the
  // instruction just after a trap/intel_interrupt.  If you use the prev_eip that was
  // set before handle_async_event, traces and breakpoints fail to show the
  // first instruction of int/trap handlers.
  BX_CPU_THIS_PTR prev_eip = X86_EIP; // commit new EIP
  BX_CPU_THIS_PTR prev_esp = X86_ESP; // commit new ESP
  
  // Now we can handle things which are synchronous to instruction
  // execution.
  if (BX_CPU_THIS_PTR eflags.rf) {
    BX_CPU_THIS_PTR eflags.rf = 0;
    }
#if BX_X86_DEBUGGER
  else {
    // only bother comparing if any breakpoints enabled
    if ( BX_CPU_THIS_PTR dr7 & 0x000000ff ) {
      Bit32u iaddr =
        BX_CPU_THIS_PTR program_visible_sregs[BX_SEG_REG_CS].cache.u.segment.base +
        BX_CPU_THIS_PTR prev_eip;
      Bit32u dr6_bits;
      if ( (dr6_bits = hwdebug_compare(iaddr, 1, BX_HWDebugInstruction,
                                       BX_HWDebugInstruction)) ) {
        // Add to the list of debug events thus far.
        BX_CPU_THIS_PTR debug_trap |= dr6_bits;
        BX_CPU_THIS_PTR async_event = 1;
        // If debug events are not inhibited on this boundary,
        // fire off a debug fault.  Otherwise handle it on the next
        // boundary. (becomes a trap)
        if ( !(BX_CPU_THIS_PTR inhibit_mask & BX_INHIBIT_DEBUG) ) {
          // Commit debug events to DR6
          BX_CPU_THIS_PTR dr6 = BX_CPU_THIS_PTR debug_trap;
          exception(BX_DB_EXCEPTION, 0, 0); // no error, not intel_interrupt
          }
        }
      }
    }
#endif

  // We have ignored processing of external interrupts and
  // debug events on this boundary.  Reset the mask so they
  // will be processed on the next boundary.
  BX_CPU_THIS_PTR inhibit_mask = 0;


#if BX_DEBUGGER
  {
  Bit32u debug_eip = BX_CPU_THIS_PTR prev_eip;
  if ( dbg_is_begin_instr_bpoint(
         BX_CPU_THIS_PTR program_visible_sregs[BX_SEG_REG_CS].selector.value,
         debug_eip,
         BX_CPU_THIS_PTR program_visible_sregs[BX_SEG_REG_CS].cache.u.segment.base + debug_eip,
         BX_CPU_THIS_PTR program_visible_sregs[BX_SEG_REG_CS].cache.u.segment.d_b) ) {
    return;
    }
  }
#endif  // #if BX_DEBUGGER
  
#if BX_INSTR_SPY
  {
    int n=0;
    if ((n & 0xffffff) == 0) {
      Bit32u cs = BX_CPU_THIS_PTR program_visible_sregs[BX_SEG_REG_CS].selector.value;
      Bit32u eip = BX_CPU_THIS_PTR prev_eip;
      fprintf (stdout, "instr %d, time %lld, pc %04x:%08x, fetch_ptr=%p\n", n, bx_pc_system.time_ticks (), cs, eip, fetch_ptr);
    }
    n++;
  }
#endif

	is_32 = BX_CPU_THIS_PTR program_visible_sregs[BX_SEG_REG_CS].cache.u.segment.d_b;

	if (BX_CPU_THIS_PTR bytesleft == 0)
	{
		prefetch();
    }

	fetch_ptr = BX_CPU_THIS_PTR fetch_ptr;
	ilength = fetchDecode(fetch_ptr, &i,MIN(BX_CPU_THIS_PTR bytesleft,0x0f));

	if (ilength)
	{
		if (i.ResolveModrm)
		{
			// call method on BX_CPU_C object
			BX_CPU_CALL_METHOD(i.ResolveModrm, (BX_CPU_THIS,&i));
		}

		BX_CPU_THIS_PTR fetch_ptr += ilength;
		BX_CPU_THIS_PTR bytesleft -= ilength;

fetch_decode_OK:

#if BX_DEBUGGER
	    if (BX_CPU_THIS_PTR trace)
		{
			// print the instruction that is about to be executed.
#if (BX_SMP_PROCESSORS==1)
			bx_dbg_disassemble_current (0, 1);  // only one cpu, print time stamp
#else
			bx_dbg_disassemble_current (local_apic.get_id (), 1); // this cpu only
#endif
		}
#endif

	{
		// non repeating instruction
		BX_CPU_THIS_PTR program_visible_eip += ilength;
		BX_CPU_CALL_METHOD(i.execute, (BX_CPU_THIS,&i));
	}

    BX_CPU_THIS_PTR prev_eip = X86_EIP; // commit new EIP
    BX_CPU_THIS_PTR prev_esp = X86_ESP; // commit new ESP
#ifdef REGISTER_IADDR
    REGISTER_IADDR(BX_CPU_THIS_PTR program_visible_eip + BX_CPU_THIS_PTR program_visible_sregs[BX_SREG_CS].cache.u.segment.base);
#endif

#ifndef DEBUG_GUEST_MACHINE
    BX_TICK1_IF_SINGLE_PROCESSOR();
#endif

//debugger_check:

#ifdef DEBUG_GUEST_MACHINE

    CHECK_MAX_INSTRUCTIONS(max_instr_count);

#endif


#if (BX_SMP_PROCESSORS>1 && BX_DEBUGGER==0)
    // The CHECK_MAX_INSTRUCTIONS macro allows cpu_loop to execute a few
    // instructions and then return so that the other processors have a chance
    // to run.  This is used only when simulating multiple processors.  If only
    // one processor, don't waste any cycles on it!  Also, it is not needed
    // with the debugger because its guard mechanism provides the same
    // functionality.
    CHECK_MAX_INSTRUCTIONS(max_instr_count);
#endif

#if BX_DEBUGGER

    // BW vm mode switch support is in dbg_is_begin_instr_bpoint
    // note instr generating exceptions never reach this point.

    // (mch) Read/write, time break point support
    if (BX_CPU_THIS_PTR break_point) {
	  switch (BX_CPU_THIS_PTR break_point) {
		case BREAK_POINT_TIME:
		      BX_INFO(("[%lld] Caught time breakpoint", bx_pc_system.time_ticks()));
		      BX_CPU_THIS_PTR stop_reason = STOP_TIME_BREAK_POINT;
		      return;
		case BREAK_POINT_READ:
		      BX_INFO(("[%lld] Caught read watch point", bx_pc_system.time_ticks()));
		      BX_CPU_THIS_PTR stop_reason = STOP_READ_WATCH_POINT;
		      return;
		case BREAK_POINT_WRITE:
		      BX_INFO(("[%lld] Caught write watch point", bx_pc_system.time_ticks()));
		      BX_CPU_THIS_PTR stop_reason = STOP_WRITE_WATCH_POINT;
		      return;
		default:
		      BX_PANIC(("Weird break point condition"));
	  }
    }
#ifdef MAGIC_BREAKPOINT
    // (mch) Magic break point support
    if (BX_CPU_THIS_PTR magic_break) {
	  if (bx_dbg.magic_break_enabled) {
		BX_DEBUG(("Stopped on MAGIC BREAKPOINT"));
		BX_CPU_THIS_PTR stop_reason = STOP_MAGIC_BREAK_POINT;
		return;
	  } else {
		BX_CPU_THIS_PTR magic_break = 0;
		BX_CPU_THIS_PTR stop_reason = STOP_NO_REASON;
		BX_DEBUG(("Ignoring MAGIC BREAKPOINT"));
	  }
    }
#endif

    {
      // check for icount or control-C.  If found, set guard reg and return.
    Bit32u debug_eip = BX_CPU_THIS_PTR prev_eip;
    if ( dbg_is_end_instr_bpoint(
           BX_CPU_THIS_PTR program_visible_sregs[BX_SEG_REG_CS].selector.value,
           debug_eip,
           BX_CPU_THIS_PTR program_visible_sregs[BX_SEG_REG_CS].cache.u.segment.base + debug_eip,
           BX_CPU_THIS_PTR program_visible_sregs[BX_SEG_REG_CS].cache.u.segment.d_b) ) {
      return;
      }
    }

#endif  // #if BX_DEBUGGER
    goto main_cpu_loop;
    }



	else
	{
            unsigned remain,j;
            Bit8u FetchBuffer[16];
			Bit8u *temp_ptr;

			remain = BX_CPU_THIS_PTR bytesleft;

			if (remain>=0x0f)
			{
				BX_PANIC(("fetchdecode: opcode length >= 0x0f"));
				exception(BX_GP_EXCEPTION, 0, 0);
			}

			// read all leftover bytes in current page
			for (j=0;j<remain;j++)
			{
				FetchBuffer[j] = *fetch_ptr++;
			}

			// get remaining bytes for prefetch in next page
			// prefetch() needs eip current
			BX_CPU_THIS_PTR program_visible_eip += BX_CPU_THIS_PTR bytesleft;
			prefetch();
			temp_ptr = fetch_ptr = BX_CPU_THIS_PTR fetch_ptr;

			// read leftover bytes in next page
			for (; j<0x0f; j++)
			{
				FetchBuffer[j] = *temp_ptr++;
			}

			ilength = fetchDecode(FetchBuffer, &i, 0x0f);

			if (ilength==0||ilength>(remain+BX_CPU_THIS_PTR bytesleft))
			{
				BX_PANIC(("fetchdecode: cross boundary: opcode length >= bytesleft"));
				exception(BX_GP_EXCEPTION, 0, 0);
			}

			if (i.ResolveModrm)
			{
				BX_CPU_CALL_METHOD(i.ResolveModrm, (BX_CPU_THIS,&i));
			}

			remain = ilength - remain;

			// note: eip has already been advanced to beginning of page
			BX_CPU_THIS_PTR fetch_ptr = fetch_ptr + remain;
			BX_CPU_THIS_PTR bytesleft -= remain;
			//BX_CPU_THIS_PTR program_visible_eip += remain;


		BX_CPU_THIS_PTR program_visible_eip = BX_CPU_THIS_PTR prev_eip;
		goto fetch_decode_OK;
    }


  //
  // This area is where we process special conditions and events.
  //

handle_async_event:

	if (BX_CPU_THIS_PTR debug_trap & 0x80000000)
	{
		// I made up the bitmask above to mean HALT state.
#if BX_SMP_PROCESSORS==1
		BX_CPU_THIS_PTR debug_trap = 0; // clear traps for after resume
		BX_CPU_THIS_PTR inhibit_mask = 0; // clear inhibits for after resume
		// for one processor, pass the time as quickly as possible until
		// an intel_interrupt wakes up the CPU.
		while (1)
		{
			if (BX_CPU_THIS_PTR INTR && BX_CPU_THIS_PTR eflags.if_)
			{
				break;
			}

			BX_TICK1();
	    }
#else      /* BX_SMP_PROCESSORS != 1 */
	    // for multiprocessor simulation, even if this CPU is halted we still
		// must give the others a chance to simulate.  If an intel_interrupt has 
		// arrived, then clear the HALT condition; otherwise just return from
		// the CPU loop with stop_reason STOP_CPU_HALTED.
		if (BX_CPU_THIS_PTR INTR && BX_CPU_THIS_PTR eflags.if_)
		{
			// intel_interrupt ends the HALT condition
			BX_CPU_THIS_PTR debug_trap = 0; // clear traps for after resume
			BX_CPU_THIS_PTR inhibit_mask = 0; // clear inhibits for after resume
			//bx_printf ("halt condition has been cleared in %s", name);
		}
		else
		{
			// HALT condition remains, return so other CPUs have a chance
#if BX_DEBUGGER
			BX_CPU_THIS_PTR stop_reason = STOP_CPU_HALTED;
#endif
			return;
		}
#endif

	}


  // Priority 1: Hardware Reset and Machine Checks
  //   RESET
  //   Machine Check
  // (bochs doesn't support these)

  // Priority 2: Trap on Task Switch
  //   T flag in TSS is set
	if (BX_CPU_THIS_PTR debug_trap & 0x00008000)
	{
		BX_CPU_THIS_PTR dr6 |= BX_CPU_THIS_PTR debug_trap;
		exception(BX_DB_EXCEPTION, 0, 0); // no error, not intel_interrupt
    }

  // Priority 3: External Hardware Interventions
  //   FLUSH
  //   STOPCLK
  //   SMI
  //   INIT
  // (bochs doesn't support these)

  // Priority 4: Traps on Previous Instruction
  //   Breakpoints
  //   Debug Trap Exceptions (TF flag set or data/IO breakpoint)
	if ( BX_CPU_THIS_PTR debug_trap &&
		!(BX_CPU_THIS_PTR inhibit_mask & BX_INHIBIT_DEBUG) )
	{
    // A trap may be inhibited on this boundary due to an instruction
    // which loaded SS.  If so we clear the inhibit_mask below
    // and don't execute this code until the next boundary.
    // Commit debug events to DR6
		BX_CPU_THIS_PTR dr6 |= BX_CPU_THIS_PTR debug_trap;
		exception(BX_DB_EXCEPTION, 0, 0); // no error, not intel_interrupt
    }

  // Priority 5: External Interrupts
  //   NMI Interrupts
  //   Maskable Hardware Interrupts
	if (BX_CPU_THIS_PTR inhibit_mask & BX_INHIBIT_INTERRUPTS)
	{
    // Processing external interrupts is inhibited on this
    // boundary because of certain instructions like STI.
    // inhibit_mask is cleared below, in which case we will have
    // an opportunity to check interrupts on the next instruction
    // boundary.
    }
	else if (BX_CPU_THIS_PTR INTR && BX_CPU_THIS_PTR eflags.if_ && BX_DBG_ASYNC_INTR)
	{
		Bit8u _vector;

		// NOTE: similar code in ::take_irq()
#if BX_SUPPORT_APIC
		if (BX_CPU_THIS_PTR int_from_local_apic)
			_vector = BX_CPU_THIS_PTR local_apic.acknowledge_int ();
		else
			_vector = BX_IAC(); // may set INTR with next intel_interrupt
#else
		// if no local APIC, always acknowledge the PIC.
		_vector = BX_IAC(); // may set INTR with next intel_interrupt

#endif
		//BX_DEBUG(("decode: intel_interrupt %u",
		//                                   (unsigned) _vector));
		BX_CPU_THIS_PTR errorno = 0;
		BX_CPU_THIS_PTR EXT   = 1; /* external event */
		intel_interrupt(_vector, 0, 0, 0);
		BX_INSTR_HWINTERRUPT(_vector, BX_CPU_THIS_PTR program_visible_sregs[BX_SEG_REG_CS].selector.value, BX_CPU_THIS_PTR program_visible_eip);
    }
	else if (BX_HRQ && BX_DBG_ASYNC_DMA)
	{
		// NOTE: similar code in ::take_dma()
		// assert Hold Acknowledge (HLDA) and go into a bus hold state
		BX_RAISE_HLDA();
	}

  // Priority 6: Faults from fetching next instruction
  //   Code breakpoint fault
  //   Code segment limit violation (priority 7 on 486/Pentium)
  //   Code page fault (priority 7 on 486/Pentium)
  // (handled in main decode loop)

  // Priority 7: Faults from decoding next instruction
  //   Instruction length > 15 bytes
  //   Illegal opcode
  //   Coprocessor not available
  // (handled in main decode loop etc)

  // Priority 8: Faults on executing an instruction
  //   Floating point execution
  //   Overflow
  //   Bound error
  //   Invalid TSS
  //   Segment not present
  //   Stack fault
  //   General protection
  //   Data page fault
  //   Alignment check
  // (handled by rest of the code)


	if (BX_CPU_THIS_PTR eflags.tf)
	{
		// TF is set before execution of next instruction.  Schedule
		// a debug trap (#DB) after execution.  After completion of
		// next instruction, the code above will invoke the trap.
		BX_CPU_THIS_PTR debug_trap |= 0x00004000; // BS flag in DR6
    }

	if ( !(BX_CPU_THIS_PTR INTR ||
			BX_CPU_THIS_PTR debug_trap ||
			BX_HRQ ||
			BX_CPU_THIS_PTR eflags.tf)
		)
	{
		 BX_CPU_THIS_PTR async_event = 0;
	}

	goto async_events_processed;
}

#endif  // #if BX_DYNAMIC_TRANSLATION == 0




// boundaries of consideration:
//
//  * physical memory boundary: 1024k (1Megabyte) (increments of...)
//  * A20 boundary:             1024k (1Megabyte)
//  * page boundary:            4k
//  * ROM boundary:             2k (dont care since we are only reading)
//  * segment boundary:         any


  void
BX_CPU_C::prefetch(void)
{
  // cs:eIP
  // prefetch QSIZE byte quantity aligned on corresponding boundary
  Bit32u new_linear_addr;
  Bit32u new_phy_addr;
  Bit32u temp_eip, temp_limit;

  temp_eip   = BX_CPU_THIS_PTR program_visible_eip;
  temp_limit = BX_CPU_THIS_PTR program_visible_sregs[BX_SEG_REG_CS].cache.u.segment.limit_scaled;

  new_linear_addr = BX_CPU_THIS_PTR program_visible_sregs[BX_SEG_REG_CS].cache.u.segment.base + temp_eip;
  BX_CPU_THIS_PTR prev_linear_page = new_linear_addr & 0xfffff000;
  if (temp_eip > temp_limit) {
    BX_PANIC(("prefetch: EIP > CS.limit"));
	exception(BX_GP_EXCEPTION, 0, 0);
    }

#if BX_SUPPORT_PAGING
  if (BX_CPU_THIS_PTR cr0.pg) {
    // aligned block guaranteed to be all in one page, same A20 address
    new_phy_addr = itranslate_linear(new_linear_addr, CPL==3);
    new_phy_addr = A20ADDR(new_phy_addr);
    }
  else
#endif // BX_SUPPORT_PAGING
    {
    new_phy_addr = A20ADDR(new_linear_addr);
    }

  if ( new_phy_addr >= BX_CPU_THIS_PTR mem->len ) {
    // don't take this out if dynamic translation enabled,
    // otherwise you must make a check to see if bytesleft is 0 after
    // a call to prefetch() in the dynamic code.
    BX_ERROR(("prefetch: running in bogus memory"));
    }

  // max physical address as confined by page boundary
  BX_CPU_THIS_PTR prev_phy_page = new_phy_addr & 0xfffff000;
  BX_CPU_THIS_PTR max_phy_addr = BX_CPU_THIS_PTR prev_phy_page | 0x00000fff;

  // check if segment boundary comes into play
  //if ((temp_limit - temp_eip) < 4096) {
  //  }

#if BX_PCI_SUPPORT
  if ((new_phy_addr >= 0x000C0000) && (new_phy_addr <= 0x000FFFFF)) {
    BX_CPU_THIS_PTR bytesleft = 0x4000 - (new_phy_addr & 0x3FFF);
    BX_CPU_THIS_PTR fetch_ptr = bx_devices.pci->i440fx_fetch_ptr(new_phy_addr);
  } else {
    BX_CPU_THIS_PTR bytesleft = (BX_CPU_THIS_PTR max_phy_addr - new_phy_addr) + 1;
    BX_CPU_THIS_PTR fetch_ptr = &BX_CPU_THIS_PTR mem->_vector[new_phy_addr];
  }
#else
  BX_CPU_THIS_PTR bytesleft = (BX_CPU_THIS_PTR max_phy_addr - new_phy_addr) + 1;
  BX_CPU_THIS_PTR fetch_ptr = &BX_CPU_THIS_PTR mem->_vector[new_phy_addr];
#endif
}


  // If control has transfered locally, it is possible the prefetch Q is
  // still valid.  This would happen for repeat instructions, and small
  // branches.
	void
BX_CPU_C::revalidate_prefetch_q(void)
{
	Bit32u new_linear_addr, new_linear_page, new_linear_offset;
	Bit32u new_phy_addr;

#if (X86CPU_MSWIN_MSDOS==1)
	BX_CPU_THIS_PTR LBR.LastBranchToCS_EIP =
		BX_CPU_THIS_PTR program_visible_sregs[BX_SEG_REG_CS].cache.u.segment.base +
		BX_CPU_THIS_PTR program_visible_eip;

	BX_CPU_THIS_PTR LBR.LastBranchFromCS_EIP =
		BX_CPU_THIS_PTR program_visible_sregs[BX_SEG_REG_CS].cache.u.segment.base +
		BX_CPU_THIS_PTR prev_eip;

	return ;

#endif

	new_linear_addr = BX_CPU_THIS_PTR program_visible_sregs[BX_SEG_REG_CS].cache.u.segment.base + BX_CPU_THIS_PTR program_visible_eip;
	new_linear_page = new_linear_addr & 0xfffff000;

	if (new_linear_page == BX_CPU_THIS_PTR prev_linear_page){
    // same linear address, old linear->physical translation valid
    new_linear_offset = new_linear_addr & 0x00000fff;
    new_phy_addr = BX_CPU_THIS_PTR prev_phy_page | new_linear_offset;

#if BX_PCI_SUPPORT
    if ((new_phy_addr >= 0x000C0000) && (new_phy_addr <= 0x000FFFFF)) {
      BX_CPU_THIS_PTR bytesleft = 0x4000 - (new_phy_addr & 0x3FFF);
      BX_CPU_THIS_PTR fetch_ptr = bx_devices.pci->i440fx_fetch_ptr(new_phy_addr);
      }
    else {
      BX_CPU_THIS_PTR bytesleft = (BX_CPU_THIS_PTR max_phy_addr - new_phy_addr) + 1;
      BX_CPU_THIS_PTR fetch_ptr = &BX_CPU_THIS_PTR mem->_vector[new_phy_addr];
      }
#else
    BX_CPU_THIS_PTR bytesleft = (BX_CPU_THIS_PTR max_phy_addr - new_phy_addr) + 1;
    BX_CPU_THIS_PTR fetch_ptr = &BX_CPU_THIS_PTR mem->_vector[new_phy_addr];
#endif
    }
	else
	{
		BX_CPU_THIS_PTR bytesleft = 0; // invalidate prefetch Q
	}
}

	void
BX_CPU_C::invalidate_prefetch_q(void)
{
	BX_CPU_THIS_PTR eipPageWindowSize = 0;
	BX_CPU_THIS_PTR bytesleft = 0;
}

#if BX_DEBUGGER
extern unsigned int dbg_show_mask;

  Boolean
BX_CPU_C::dbg_is_begin_instr_bpoint(Bit32u cs, Bit32u eip, Bit32u laddr,
                                    Bit32u is_32)
{
  //fprintf (stderr, "begin_instr_bp: checking cs:eip %04x:%08x\n", cs, eip);
  BX_CPU_THIS_PTR guard_found.cs  = cs;
  BX_CPU_THIS_PTR guard_found.eip = eip;
  BX_CPU_THIS_PTR guard_found.laddr = laddr;
  BX_CPU_THIS_PTR guard_found.is_32bit_code = is_32;

  // BW mode switch breakpoint
  // instruction which generate exceptions never reach the end of the
  // loop due to a long jump. Thats why we check at start of instr.
  // Downside is that we show the instruction about to be executed
  // (not the one generating the mode switch).
  if (BX_CPU_THIS_PTR mode_break && 
      (BX_CPU_THIS_PTR debug_vm != BX_CPU_THIS_PTR eflags.vm)) {
    BX_INFO(("Caught vm mode switch breakpoint"));
    BX_CPU_THIS_PTR debug_vm = BX_CPU_THIS_PTR eflags.vm;
    BX_CPU_THIS_PTR stop_reason = STOP_MODE_BREAK_POINT;
    return 1;
  }

  if( (BX_CPU_THIS_PTR show_flag) & (dbg_show_mask)) {
    int rv;
    if((rv = bx_dbg_symbolic_output()))
      return rv;
  }

  // see if debugger is looking for iaddr breakpoint of any type
  if (bx_guard.guard_for & BX_DBG_GUARD_IADDR_ALL) {
#if BX_DBG_SUPPORT_VIR_BPOINT
    if (bx_guard.guard_for & BX_DBG_GUARD_IADDR_VIR) {
      if (BX_CPU_THIS_PTR guard_found.icount!=0) {
        for (unsigned i=0; i<bx_guard.iaddr.num_virtual; i++) {
          if ( (bx_guard.iaddr.vir[i].cs  == cs) &&
               (bx_guard.iaddr.vir[i].eip == eip) ) {
            BX_CPU_THIS_PTR guard_found.guard_found = BX_DBG_GUARD_IADDR_VIR;
            BX_CPU_THIS_PTR guard_found.iaddr_index = i;
            return(1); // on a breakpoint
            }
          }
        }
      }
#endif
#if BX_DBG_SUPPORT_LIN_BPOINT
    if (bx_guard.guard_for & BX_DBG_GUARD_IADDR_LIN) {
      if (BX_CPU_THIS_PTR guard_found.icount!=0) {
        for (unsigned i=0; i<bx_guard.iaddr.num_linear; i++) {
          if ( bx_guard.iaddr.lin[i].addr == BX_CPU_THIS_PTR guard_found.laddr ) {
            BX_CPU_THIS_PTR guard_found.guard_found = BX_DBG_GUARD_IADDR_LIN;
            BX_CPU_THIS_PTR guard_found.iaddr_index = i;
            return(1); // on a breakpoint
            }
          }
        }
      }
#endif
#if BX_DBG_SUPPORT_PHY_BPOINT
    if (bx_guard.guard_for & BX_DBG_GUARD_IADDR_PHY) {
      Bit32u phy;
      Boolean valid;
      dbg_xlate_linear2phy(BX_CPU_THIS_PTR guard_found.laddr,
                              &phy, &valid);
      // The "guard_found.icount!=0" condition allows you to step or
      // continue beyond a breakpoint.  Bryce tried removing it once,
      // and once you get to a breakpoint you are stuck there forever.
      // Not pretty.
      if (valid && (BX_CPU_THIS_PTR guard_found.icount!=0)) {
        for (unsigned i=0; i<bx_guard.iaddr.num_physical; i++) {
          if ( bx_guard.iaddr.phy[i].addr == phy ) {
            BX_CPU_THIS_PTR guard_found.guard_found = BX_DBG_GUARD_IADDR_PHY;
            BX_CPU_THIS_PTR guard_found.iaddr_index = i;
            return(1); // on a breakpoint
            }
          }
        }
      }
#endif
    }
  return(0); // not on a breakpoint
}


  Boolean
BX_CPU_C::dbg_is_end_instr_bpoint(Bit32u cs, Bit32u eip, Bit32u laddr,
                                  Bit32u is_32)
{
  //fprintf (stderr, "end_instr_bp: checking for icount or ^C\n");
  BX_CPU_THIS_PTR guard_found.icount++;

  // convenient point to see if user typed Ctrl-C
  if (bx_guard.interrupt_requested &&
      (bx_guard.guard_for & BX_DBG_GUARD_CTRL_C)) {
    BX_CPU_THIS_PTR guard_found.guard_found = BX_DBG_GUARD_CTRL_C;
    return(1);
    }

  // see if debugger requesting icount guard
  if (bx_guard.guard_for & BX_DBG_GUARD_ICOUNT) {
    if (BX_CPU_THIS_PTR guard_found.icount >= bx_guard.icount) {
      BX_CPU_THIS_PTR guard_found.cs  = cs;
      BX_CPU_THIS_PTR guard_found.eip = eip;
      BX_CPU_THIS_PTR guard_found.laddr = laddr;
      BX_CPU_THIS_PTR guard_found.is_32bit_code = is_32;
      BX_CPU_THIS_PTR guard_found.guard_found = BX_DBG_GUARD_ICOUNT;
      return(1);
      }
    }

#if (BX_NUM_SIMULATORS >= 2)
  // if async event pending, acknowlege them
  if (bx_guard.async_changes_pending.which) {
    if (bx_guard.async_changes_pending.which & BX_DBG_ASYNC_PENDING_A20)
      bx_dbg_async_pin_ack(BX_DBG_ASYNC_PENDING_A20,
                           bx_guard.async_changes_pending.a20);
    if (bx_guard.async_changes_pending.which) {
      BX_PANIC(("decode: async pending unrecognized."));
      }
    }
#endif
  return(0); // no breakpoint
}


  void
BX_CPU_C::dbg_take_irq(void)
{
  unsigned _vector;

  // NOTE: similar code in ::cpu_loop()

  if ( BX_CPU_THIS_PTR INTR && BX_CPU_THIS_PTR eflags.if_ ) {
    if ( setjmp(BX_CPU_THIS_PTR jmp_buf_env) == 0 ) {
      // normal return from setjmp setup
      _vector = BX_IAC(); // may set INTR with next intel_interrupt
      BX_CPU_THIS_PTR errorno = 0;
      BX_CPU_THIS_PTR EXT   = 1; // external event
      BX_CPU_THIS_PTR async_event = 1; // set in case INTR is triggered
      intel_interrupt(_vector, 0, 0, 0);
      }
    }
}

  void
BX_CPU_C::dbg_force_interrupt(unsigned _vector)
{
  // Used to force slave simulator to take an intel_interrupt, without
  // regard to IF

  if ( setjmp(BX_CPU_THIS_PTR jmp_buf_env) == 0 ) {
    // normal return from setjmp setup
    BX_CPU_THIS_PTR errorno = 0;
    BX_CPU_THIS_PTR EXT   = 1; // external event
    BX_CPU_THIS_PTR async_event = 1; // probably don't need this
    intel_interrupt(_vector, 0, 0, 0);
    }
}

  void
BX_CPU_C::dbg_take_dma(void)
{
  // NOTE: similar code in ::cpu_loop()
  if ( BX_HRQ ) {
    BX_CPU_THIS_PTR async_event = 1; // set in case INTR is triggered
    BX_RAISE_HLDA();
    }
}
#endif  // #if BX_DEBUGGER

#if BX_SUPPORT_FPU==0

#undef LOG_THIS
#define LOG_THIS genlog->

// Nomenclature used to signify argument types
//
// Es = single real
// El = double real
// Ea = 14/28 bytes    98/108b bytes (FRSTOR,FSAVE)???
// Ew = word integer (2 bytes)
// Ed = dword integer (4 bytes) (short int)
// Et = extended real
// Eb = packed BCD
// Eq = quadword integer (8 bytes) (long integer)

void
BX_CPU_C::ESC0(BX_CPU_C *icpu,bxInstruction_c *i)
{
	if ( BX_CPU_CLASS_PTR cr0.em || BX_CPU_CLASS_PTR cr0.ts ) {
		BX_CPU_CLASS_PTR exception(BX_NM_EXCEPTION, 0, 0);
	}
#if BX_SUPPORT_FPU
	BX_CPU_CLASS_PTR fpu_execute(i);
#else
	BX_INFO(("ESC0 not implemented"));
#endif
}

void
BX_CPU_C::ESC1(BX_CPU_C *icpu,bxInstruction_c *i)
{
	if ( BX_CPU_CLASS_PTR cr0.em || BX_CPU_CLASS_PTR cr0.ts ) {
		BX_CPU_CLASS_PTR exception(BX_NM_EXCEPTION, 0, 0);
	}
#if BX_SUPPORT_FPU
	BX_CPU_CLASS_PTR fpu_execute(i);
#else
	BX_INFO(("ESC1 not implemented"));
#endif
}

void
BX_CPU_C::ESC2(BX_CPU_C *icpu,bxInstruction_c *i)
{
	if ( BX_CPU_CLASS_PTR cr0.em || BX_CPU_CLASS_PTR cr0.ts ) {
		BX_CPU_CLASS_PTR exception(BX_NM_EXCEPTION, 0, 0);
	}
#if BX_SUPPORT_FPU
	BX_CPU_CLASS_PTR fpu_execute(i);
#else
	BX_INFO(("ESC2 not implemented"));
#endif
}

void
BX_CPU_C::ESC3(BX_CPU_C *icpu,bxInstruction_c *i)
{
	if ( BX_CPU_CLASS_PTR cr0.em || BX_CPU_CLASS_PTR cr0.ts ) {
		BX_CPU_CLASS_PTR exception(BX_NM_EXCEPTION, 0, 0);
	}

	//BX_DEBUG(( "CS:EIP = %04x:%08x",
	//  BX_CPU.sregs[BX_SEG_REG_CS].selector.value, BX_CPU.prev_eip));

#if BX_SUPPORT_FPU
	BX_CPU_CLASS_PTR fpu_execute(i);
#else
	BX_INFO(("ESC3 not implemented"));
#endif
}

void
BX_CPU_C::ESC4(BX_CPU_C *icpu,bxInstruction_c *i)
{
	if ( BX_CPU_CLASS_PTR cr0.em || BX_CPU_CLASS_PTR cr0.ts ) {
		BX_CPU_CLASS_PTR exception(BX_NM_EXCEPTION, 0, 0);
	}
#if BX_SUPPORT_FPU
	BX_CPU_CLASS_PTR fpu_execute(i);
#else
	BX_INFO(("ESC4 not implemented"));
#endif
}

void
BX_CPU_C::ESC5(BX_CPU_C *icpu,bxInstruction_c *i)
{
	if ( BX_CPU_CLASS_PTR cr0.em || BX_CPU_CLASS_PTR cr0.ts ) {
		BX_CPU_CLASS_PTR exception(BX_NM_EXCEPTION, 0, 0);
	}
#if BX_SUPPORT_FPU
	BX_CPU_CLASS_PTR fpu_execute(i);
#else
	BX_INFO(("ESC5 not implemented"));
#endif
}

void
BX_CPU_C::ESC6(BX_CPU_C *icpu,bxInstruction_c *i)
{
	if ( BX_CPU_CLASS_PTR cr0.em || BX_CPU_CLASS_PTR cr0.ts ) {
		BX_CPU_CLASS_PTR exception(BX_NM_EXCEPTION, 0, 0);
	}
#if BX_SUPPORT_FPU
	BX_CPU_CLASS_PTR fpu_execute(i);
#else
	BX_INFO(("ESC6 not implemented"));
#endif
}

void
BX_CPU_C::ESC7(BX_CPU_C *icpu,bxInstruction_c *i)
{
	if ( BX_CPU_CLASS_PTR cr0.em || BX_CPU_CLASS_PTR cr0.ts ) {
		BX_CPU_CLASS_PTR exception(BX_NM_EXCEPTION, 0, 0);
	}
#if BX_SUPPORT_FPU
	BX_CPU_CLASS_PTR fpu_execute(i);
#else
	BX_INFO(("ESC7 not implemented"));
#endif
}

void
BX_CPU_C::FWAIT(BX_CPU_C *icpu,bxInstruction_c *i)
{
#if BX_CPU_LEVEL < 3
	// WAIT doesn't generate single steps on 8086.
	// The same goes for prefix instructions, and instructions which
	// modify segment registers. (pg4-16)
	// single_step_event = 0;
	BX_PANIC(("WAIT: not implemented for < 386"));
#else // BX_CPU_LEVEL >= 3

	if ( BX_CPU_CLASS_PTR cr0.ts && BX_CPU_CLASS_PTR cr0.mp ) {
		BX_CPU_CLASS_PTR exception(BX_NM_EXCEPTION, 0, 0); // no error
	}
#if BX_SUPPORT_FPU
	BX_CPU_CLASS_PTR fpu_execute(i);
#else
	BX_INFO(("FWAIT: no FPU"));
#endif

#endif
}

#if BX_SUPPORT_FPU==0

  // if supporting FPU, this function in glue logic file
  void
BX_CPU_C::fpu_init(void)
{
}

#endif

#endif



