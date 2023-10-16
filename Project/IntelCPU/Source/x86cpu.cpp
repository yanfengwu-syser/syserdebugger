/////////////////////////////////////////////////////////////////////////
// $Id: x86cpu.cc,v 1.0 2002/10/08 16:04:05 bdenney Exp $
/////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////
// $Id: x86cpu.cc $Id: x86cpu.cc $Id: x86cpu.cc $Id: x86cpu.cc $Id: x86cpu.cc
/////////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "x86cpu.h"
// notes:
//
// check limit of CS?

#ifdef REGISTER_IADDR
extern void REGISTER_IADDR(bx_addr addr);
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

// Make code more tidy with a few macros.
#if BX_SUPPORT_X86_64==0
#define RIP X86_EIP
#define RSP X86_ESP
#endif

void PrintfCPU(BX_CPU_C *cpu,char *s,int i=0)
{
	return ;
	printf("%s  %d\n",s,i);
	printf(	"EAX=0x%08X , EBX=0x%08X , ECX=0x%08X , EDX=0x%08X\n"
			"ESI=0x%08X , EDI=0x%08X , EBP=0x%08X , ESP=0x%08X\n"
			"EIP=0x%08X , EFLAG=0x%08X\n"
			"CS Mode=0x%08X , CS SELECTOR=0x%08X ,CS Base=0x%08X\n",
			cpu->GENERAL_REG_DWORD(I_EAX),cpu->GENERAL_REG_DWORD(I_EBX),
			cpu->GENERAL_REG_DWORD(I_ECX),cpu->GENERAL_REG_DWORD(I_EDX),

			cpu->GENERAL_REG_DWORD(I_ESI),cpu->GENERAL_REG_DWORD(I_EDI),
			cpu->GENERAL_REG_DWORD(I_EBP),cpu->GENERAL_REG_DWORD(I_ESP),

			cpu->REG_EIP,cpu->REG_EFLAGS,

			cpu->SEGMENT_MODE(I_CS),cpu->SEGMENT_SELECTOR(I_CS),cpu->SEGMENT_BASE_ADDRESS(I_CS)
			);

	getchar();

	return ;
}

int 
BX_CPU_C::x86_cpu_loop(Bit32s max_instr_counter)
{
	unsigned ret;
	bxInstruction_c iStorage;// BX_CPP_AlignN(32);
	bxInstruction_c *i = &iStorage;
	BxExecutePtr_t execute;

	int setjmp_result;
	int copy_max_instr_counter;

	copy_max_instr_counter = max_instr_counter;

	setjmp_result = setjmp( BX_CPU_THIS_PTR jmp_buf_env );

	if (setjmp_result)
	{
		if (1==setjmp_result)
		{
			return copy_max_instr_counter - max_instr_counter;
		}
		if (2==setjmp_result)
		{
			return -1;
		}
		else
		{
			return -1;
		}
	}

	// We get here either by a normal function call, or by a longjmp
	// back from an exception() call.  In either case, commit the
	// new EIP/ESP, and set up other environmental fields.  This code
	// mirrors similar code below, after the interrupt() call.
	BX_CPU_THIS_PTR prev_eip = RIP; // commit new EIP
	BX_CPU_THIS_PTR prev_esp = RSP; // commit new ESP
	BX_CPU_THIS_PTR EXT = 0;
	BX_CPU_THIS_PTR errorno = 0;

	while (1) {

		// First check on events which occurred for previous instructions
		// (traps) and ones which are asynchronous to the CPU
		// (hardware interrupts).
		if (BX_CPU_THIS_PTR async_event) {
			if (x86_handleAsyncEvent()) {
				// If request to return to caller ASAP.
				return 0;
			}
		}


#if BX_EXTERNAL_DEBUGGER
		if (regs.debug_state != debug_run) {
			bx_external_debugger(this);
		}
#endif

		{
			bx_address eipBiased;
			Bit8u *fetchPtr;

			eipBiased = RIP + BX_CPU_THIS_PTR eipPageBias;

			if ( eipBiased >= BX_CPU_THIS_PTR eipPageWindowSize ) 
			{
				x86_prefetch();
				eipBiased = RIP + BX_CPU_THIS_PTR eipPageBias;

#if (X86CPU_MSWIN_MSDOS==1)
				if (max_instr_counter != copy_max_instr_counter)
					longjmp(BX_CPU_THIS_PTR jmp_buf_env,1);
#endif

			}

#if BX_SupportICache
			unsigned iCacheHash;
			Bit32u pAddr, pageWriteStamp, fetchModeMask;

			//#define BxICacheInstructions 0x100 // 28%
			//#define BxICacheInstructions 0x200 // 47%
			//#define BxICacheInstructions 0x400 // 75%
			//#define BxICacheInstructions 0x800 // 85%

			//#define BxICacheInstructions 0x1000 // 88%
			//#define BxICacheInstructions 0x2000 // 89%
			//#define BxICacheInstructions 0x4000 // 89%
			//#define BxICacheInstructions 0x8000 // 89%

#define BxICacheInstructions 0x1000  // 88%

			pAddr = BX_CPU_THIS_PTR pAddrA20Page + eipBiased;
			iCacheHash = BX_CPU_THIS_PTR iCache.hash( pAddr );
			iCacheHash = BX_CPU_THIS_PTR iCache.iAllocStampEntry[iCacheHash];
			i = & BX_CPU_THIS_PTR iCache.entry[iCacheHash].i;

			pageWriteStamp = BX_CPU_THIS_PTR iCache.pageWriteStampTable[pAddr>>12];
			fetchModeMask  = BX_CPU_THIS_PTR iCache.fetchModeMask;

			BX_CPU_THIS_PTR stamp.fetchdecode++;
			static int SPRINTF_COUNTER;
			if (++SPRINTF_COUNTER>=0x1000000)
			{
				SPRINTF_COUNTER = 0;
				char s_fetch[64],s_write[64],s_cahceLoop[64];
				Bit64u all_stamp = BX_CPU_THIS_PTR stamp.fetchdecode;
				sprintf(s_fetch,"fetch: %08x-%08x",(int)(all_stamp>>32),(int)all_stamp);
				sprintf(s_write,"write: %d%%",(BX_CPU_THIS_PTR stamp.WriteMemoryCounter)*100/all_stamp);
				sprintf(s_cahceLoop,"loop: %d%%",(BX_CPU_THIS_PTR stamp.cahceLoop)*100/all_stamp);
				BX_PANIC(("%s %s %s\n",s_fetch,s_write,s_cahceLoop));
			}

			if ( (BX_CPU_THIS_PTR iCache.entry[iCacheHash].pAddr == pAddr) &&
				(BX_CPU_THIS_PTR iCache.entry[iCacheHash].writeStamp == pageWriteStamp) &&
				((pageWriteStamp & fetchModeMask) == fetchModeMask) ) {

					BX_CPU_THIS_PTR stamp.cahceLoop++;

					// iCache hit.  Instruction is already decoded and stored in
					// the instruction cache.
					BxExecutePtr_t resolveModRM = i->ResolveModrm; // Get as soon as possible for speculation.

					execute = i->execute; // fetch as soon as possible for speculation.
					if (resolveModRM) {
						BX_CPU_CALL_METHOD(resolveModRM, (icpu,i));
					}
				}
			else
#endif
			{
				// iCache miss.  No validated instruction with matching fetch parameters
				// is in the iCache.  Or we're not compiling iCache support in, in which
				// case we always have an iCache miss.  :^)
				bx_address remainingInPage;
				unsigned maxFetch;

				remainingInPage = (BX_CPU_THIS_PTR eipPageWindowSize - eipBiased);
				maxFetch = 15;
				if (remainingInPage < 15)
					maxFetch = remainingInPage;
				fetchPtr = BX_CPU_THIS_PTR eipFetchPtr + eipBiased;

#if BX_SupportICache

				short iAllocStamp;
				iCacheHash = BX_CPU_THIS_PTR iCache.hash( pAddr );
				iAllocStamp = BX_CPU_THIS_PTR iCache.iAllocStamp++&(BxICacheInstructions-1);
				BX_CPU_THIS_PTR iCache.iAllocStampEntry[iCacheHash] = iAllocStamp;
				iCacheHash = iAllocStamp;
				i = & BX_CPU_THIS_PTR iCache.entry[iCacheHash].i;

				// In the case where the page is marked ICacheWriteStampInvalid, all
				// counter bits will be high, being eqivalent to ICacheWriteStampMax.
				// In the case where the page is marked as possibly having associated
				// iCache entries, we need to leave the counter as-is, unless we're
				// willing to dump all iCache entries which can hash to this page.
				// Therefore, in either case, we can keep the counter as-is and
				// replace the fetch mode bits.
				pageWriteStamp &= 0x1fffffff;    // Clear out old fetch mode bits.
				pageWriteStamp |= fetchModeMask; // Add in new ones.
				BX_CPU_THIS_PTR iCache.pageWriteStampTable[pAddr>>12] = pageWriteStamp;
				BX_CPU_THIS_PTR iCache.entry[iCacheHash].pAddr = pAddr;
				BX_CPU_THIS_PTR iCache.entry[iCacheHash].writeStamp = pageWriteStamp;
#endif
				//((CMSWIN_X86_CPU*)this)->LinearMemory->m_pVEMemMon->m_ProcObj->LogPrint("EIP = 0x%08X\n");
#if BX_SUPPORT_X86_64
				if (BX_CPU_THIS_PTR cpu_mode == BX_MODE_LONG_64) {
					ret = fetchDecode64(fetchPtr, i, maxFetch);
				}
				else
#endif
				{
					ret = fetchDecode(fetchPtr, i, maxFetch);
				}

				BxExecutePtr_t resolveModRM = i->ResolveModrm; // Get function pointers early.
				if (ret==0) {
#if BX_SupportICache
					// Invalidate entry, since fetch-decode failed with partial updates
					// to the i-> structure.
					BX_CPU_THIS_PTR iCache.entry[iCacheHash].writeStamp =
						ICacheWriteStampInvalid;
					//      i = &iStorage;
#endif

					if (maxFetch==15)
						exception(BX_GP_EXCEPTION, 0, 0);
					x86_boundaryFetch(i);
					resolveModRM = i->ResolveModrm; // Get function pointers as early
				}
#if BX_INSTRUMENTATION
				else
				{
					// An instruction was either fetched, or found in the iCache.
					BX_INSTR_OPCODE(CPU_ID, fetchPtr, i->ilen(),
						BX_CPU_THIS_PTR sregs[BX_SEG_REG_CS].cache.u.segment.d_b);
				}
#endif
				execute = i->execute; // fetch as soon as possible for speculation.
				if (resolveModRM) {
					BX_CPU_CALL_METHOD(resolveModRM, (BX_CPU_THIS,i));
#if BX_SupportICache
					i->ReadWriteGuess =
						BX_CPU_THIS_PTR iCache.iAllocGuess++&(BxICacheInstructions/4-1);
#endif
				}
			}
		}

		// An instruction will have been fetched using either the normal case,
		// or the boundary fetch (across pages), by this point.
		//    BX_INSTR_FETCH_DECODE_COMPLETED(CPU_ID, i);

		BX_CPU_THIS_PTR instr = i;

		if (1) 
		{
			// non repeating instruction
			RIP += i->ilen();
			BX_CPU_CALL_METHOD(execute, (BX_CPU_THIS,i));
			(*page_access_stamp_ptr)++;
			////++++++++
			BX_CPU_THIS_PTR lastInstructionListTable[BX_CPU_THIS_PTR lastInstr++&0xff] = execute;

#ifdef REGISTER_IADDR
			REGISTER_IADDR(RIP + BX_CPU_THIS_PTR sregs[BX_SEG_REG_CS].cache.u.segment.base);
#endif

			BX_TICK1_IF_SINGLE_PROCESSOR();

			if (max_instr_counter >= 0)
			{
				max_instr_counter--;
				if(!real_mode() && eflags.tf)
				{
					BX_CPU_THIS_PTR last_read_write.i_bytes = i->ilen();
					return copy_max_instr_counter - max_instr_counter;
				}
				if (max_instr_counter == 0)
				{
					BX_CPU_THIS_PTR last_read_write.i_bytes = i->ilen();
					return copy_max_instr_counter;
				}
			}
			else
				return copy_max_instr_counter;
			BX_CPU_THIS_PTR prev_eip = RIP; // commit new EIP
			BX_CPU_THIS_PTR prev_esp = RSP; // commit new ESP
		}
		//debugger_check:

		// inform instrumentation about new instruction
		//temp    BX_INSTR_NEW_INSTRUCTION(CPU_ID);

#if (BX_SMP_PROCESSORS>1 && BX_DEBUGGER==0)
		// The CHECK_MAX_INSTRUCTIONS macro allows cpu_loop to execute a few
		// instructions and then return so that the other processors have a chance
		// to run.  This is used only when simulating multiple processors.  If only
		// one processor, don't waste any cycles on it!  Also, it is not needed
		// with the debugger because its guard mechanism provides the same
		// functionality.
		CHECK_MAX_INSTRUCTIONS(max_instr_counter);
#endif

	}  // while (1)
}


  unsigned
BX_CPU_C::x86_handleAsyncEvent(void)
{
  //
  // This area is where we process special conditions and events.
  //
	if(!real_mode() && eflags.tf)
	{
		eflags.tf = false;
		exception(BX_DB_EXCEPTION,0,0);
	}
	return 0;
}


// boundaries of consideration:
//
//  * physical memory boundary: 1024k (1Megabyte) (increments of...)
//  * A20 boundary:             1024k (1Megabyte)
//  * page boundary:            4k
//  * ROM boundary:             2k (dont care since we are only reading)
//  * segment boundary:         any
  void
BX_CPU_C::x86_prefetch(void)
{
  // cs:eIP
  // x86_prefetch QSIZE byte quantity aligned on corresponding boundary
  bx_address laddr;
  Bit32u pAddr;
  bx_address temp_rip;
  Bit32u temp_limit;
  bx_address laddrPageOffset0, eipPageOffset0;

  temp_rip   = RIP;
  temp_limit = BX_CPU_THIS_PTR program_visible_sregs[BX_SEG_REG_CS].cache.u.segment.limit_scaled;

  laddr = BX_CPU_THIS_PTR program_visible_sregs[BX_SEG_REG_CS].cache.u.segment.base +
                    temp_rip;

  if (((Bit32u)temp_rip) > temp_limit) {
    BX_PANIC(("x86_prefetch: RIP > CS.limit"));
	exception(BX_GP_EXCEPTION, 0, 0);
    }

#if BX_SUPPORT_PAGING
  if (BX_CPU_THIS_PTR cr0.pg) {
    // aligned block guaranteed to be all in one page, same A20 address
    pAddr = itranslate_linear(laddr, CPL==3);
    pAddr = A20ADDR(pAddr);
    }
  else
#endif // BX_SUPPORT_PAGING
    {
    pAddr = A20ADDR(laddr);
    }

  // check if segment boundary comes into play
  //if ((temp_limit - (Bit32u)temp_rip) < 4096) {
  //  }

  // Linear address at the beginning of the page.
  laddrPageOffset0 = laddr & 0xfffff000;
  // Calculate RIP at the beginning of the page.
  eipPageOffset0 = RIP - (laddr - laddrPageOffset0);
  BX_CPU_THIS_PTR eipPageBias = (0- eipPageOffset0);
  BX_CPU_THIS_PTR eipPageWindowSize = 4096; // FIXME:
  BX_CPU_THIS_PTR pAddrA20Page = pAddr & 0xfffff000;
//  BX_CPU_THIS_PTR eipFetchPtr =
//      BX_CPU_THIS_PTR mem->getHostMemAddr(this, BX_CPU_THIS_PTR pAddrA20Page,
//                                          BX_READ);
  BX_CPU_THIS_PTR eipFetchPtr =
	  BX_CPU_THIS_PTR getHostMemPtr(laddr,BX_READ,&BX_CPU_THIS_PTR page_access_stamp_ptr);

  // Sanity checks
  if ( !BX_CPU_THIS_PTR eipFetchPtr ) {
    if ( pAddr >= BX_CPU_THIS_PTR mem_len ) {
      BX_PANIC(("x86_prefetch: running in bogus memory"));
      }
    else {
      BX_PANIC(("x86_prefetch: getHostMemAddr vetoed direct read, pAddr=0x%x.",
                pAddr));
      }
    }
}


  void
BX_CPU_C::x86_boundaryFetch(bxInstruction_c *i)
{
    unsigned j;
    Bit8u fetchBuffer[16]; // Really only need 15
    bx_address eipBiased, remainingInPage;
    Bit8u *fetchPtr;
    unsigned ret;

    eipBiased = RIP + BX_CPU_THIS_PTR eipPageBias;
    remainingInPage = (BX_CPU_THIS_PTR eipPageWindowSize - eipBiased);
    if (remainingInPage > 15) {
      BX_PANIC(("fetch_decode: remaining > max ilen"));
      }
    fetchPtr = BX_CPU_THIS_PTR eipFetchPtr + eipBiased;

    // Read all leftover bytes in current page up to boundary.
    for (j=0; j<remainingInPage; j++) {
      fetchBuffer[j] = *fetchPtr++;
      }

    // The 2nd chunk of the instruction is on the next page.
    // Set RIP to the 0th byte of the 2nd page, and force a
    // x86_prefetch so direct access of that physical page is possible, and
    // all the associated info is updated.
    RIP += remainingInPage;
    x86_prefetch();
    if (BX_CPU_THIS_PTR eipPageWindowSize < 15) {
      BX_PANIC(("fetch_decode: small window size after x86_prefetch"));
      }

    // We can fetch straight from the 0th byte, which is eipFetchPtr;
    fetchPtr = BX_CPU_THIS_PTR eipFetchPtr;

    // read leftover bytes in next page
    for (; j<15; j++) {
      fetchBuffer[j] = *fetchPtr++;
      }
#if BX_SUPPORT_X86_64
    if (BX_CPU_THIS_PTR cpu_mode == BX_MODE_LONG_64) {
      ret = fetchDecode64(fetchBuffer, i, 15);
      }
    else
#endif
      {
      ret = fetchDecode(fetchBuffer, i, 15);
      }
    // Restore EIP since we fudged it to start at the 2nd page boundary.
    RIP = BX_CPU_THIS_PTR prev_eip;
    if (ret==0)
	{
      BX_PANIC(("fetchDecode: cross boundary: ret==0"));
      exception(BX_GP_EXCEPTION, 0, 0);
	}

// Since we cross an instruction boundary, note that we need a x86_prefetch()
// again on the next instruction.  Perhaps we can optimize this to
// eliminate the extra x86_prefetch() since we do it above, but have to
// think about repeated instructions, etc.
BX_CPU_THIS_PTR eipPageWindowSize = 0; // Fixme

//temp  BX_INSTR_OPCODE(CPU_ID, fetchBuffer, i->ilen(),
//temp                  BX_CPU_THIS_PTR program_visible_sregs[BX_SEG_REG_CS].cache.u.segment.d_b);
}

#if BX_SupportICache

int setbitmaping(Bit8u *buff,int offset)
{
	int bit = (buff[offset>>3]>>(offset&7))&1;
	
	buff[offset>>3] |= (1<<(offset&7));

	return bit;
}

int getbitmaping(Bit8u *buff,int offset)
{
	return (buff[offset>>3]>>(offset&7))&1;
}

#include "../UPX/conf.h"

int upxdata_compress(ucl_byte *inbuff,unsigned int inlen,ucl_byte *outbuff,unsigned int *poutlen,int method);

int bxICache_c::gatherWriteHole(bxReadWriteMemoryHole *h)
{
	int i,j;
	Bit8u outbuff[512];
	unsigned int outlen;

	i =0;j =0;

	upxdata_compress(h->bitMap,512,outbuff,&outlen,4);

	if (outlen<=128)
	{
		i = outlen;
	}
	else
	{
		i = outlen;
	}

	memset(h->bitMap,0,sizeof(h->bitMap));
	return 0;
}

bxReadWriteMemoryHole *bxICache_c::allocWriteHole(Bit32u a20Addr)
{
	bxReadWriteMemoryHole *h;

	if (hole[iAllocHole&(BXREADWRITEMEMORYHOLES-1)].busy)
	{
		h = &hole[iAllocHole&(BXREADWRITEMEMORYHOLES-1)];
		gatherWriteHole(h);
		setbitmaping(pageWriteHoleMaping,a20Addr>>12);
	}

	pageWriteHoleTable[a20Addr>>12] = iAllocHole++&(BXREADWRITEMEMORYHOLES-1);
	hole[pageWriteHoleTable[a20Addr>>12]].page = (a20Addr&0xffff000);
	hole[pageWriteHoleTable[a20Addr>>12]].busy  = 1;
	h = hole + pageWriteHoleTable[a20Addr>>12];

	return h;
}

#endif // BX_SupportICache



