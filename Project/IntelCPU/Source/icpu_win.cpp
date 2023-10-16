/////////////////////////////////////////////////////////////////////////
// $Id: inteli32.cpp,v 1.0 2002/10/08 16:04:05 bdenney Exp $
/////////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "x86cpu.h"
#include "icpu_win.h"
#include "../../vex86/Source/VEMemory.h"

void PrintfCPU(BX_CPU_C *cpu,char *s,int i=0);


#define T_READ_WRITE_BYTES 1 

	void
CMSWIN_X86_CPU::write_virtual_byte(unsigned s, Bit32u offset, Bit8u *data)
{
	Bit32u laddr;
	bx_segment_reg_t *seg;

	seg = &BX_CPU_THIS_PTR program_visible_sregs[s];
	write_virtual_checks(seg, offset, 1);

	laddr = seg->cache.u.segment.base + offset;
	BX_INSTR_MEM_DATA(laddr, 1, BX_WRITE);

	// all checks OK

#if (T_READ_WRITE_BYTES==1)

	if (!(LinearMemory->WriteMemByte(laddr,(void *) data, CPL==3)))
	{
		Bit16u error_code;
		error_code |= ((CPL==3) << 2) | (1 << 1);
		BX_CPU_THIS_PTR cr2 = laddr;
		// invalidate entry - we can get away without maintaining A bit in PTE
		// if we don't maintain TLB entries without it set.
		exception(BX_PF_EXCEPTION, error_code, 0);
	}
	return ;

#endif

	access_linear(laddr, 1, CPL==3, BX_WRITE, (void *) data);
}

	void
CMSWIN_X86_CPU::write_virtual_word(unsigned s, Bit32u offset, Bit16u *data)
{
	Bit32u laddr;
	bx_segment_reg_t *seg;

	seg = &BX_CPU_THIS_PTR program_visible_sregs[s];
	write_virtual_checks(seg, offset, 2);

	laddr = seg->cache.u.segment.base + offset;
	BX_INSTR_MEM_DATA(laddr, 2, BX_WRITE);

	// all checks OK

#if (T_READ_WRITE_BYTES==1)

	if (!(LinearMemory->WriteMemWord(laddr,(void *) data, CPL==3)))
	{
		Bit16u error_code;
		error_code |= ((CPL==3) << 2) | (1 << 1);
		BX_CPU_THIS_PTR cr2 = laddr;
		// invalidate entry - we can get away without maintaining A bit in PTE
		// if we don't maintain TLB entries without it set.
		exception(BX_PF_EXCEPTION, error_code, 0);
	}
	return;

#endif

	access_linear(laddr, 2, CPL==3, BX_WRITE, (void *) data);
}

	void
CMSWIN_X86_CPU::write_virtual_dword(unsigned s, Bit32u offset, Bit32u *data)
{
	Bit32u laddr;
	bx_segment_reg_t *seg;

	seg = &BX_CPU_THIS_PTR program_visible_sregs[s];
	write_virtual_checks(seg, offset, 4);

	laddr = seg->cache.u.segment.base + offset;
	BX_INSTR_MEM_DATA(laddr, 4, BX_WRITE);

	// all checks OK

#if (T_READ_WRITE_BYTES==1)

	if (!(LinearMemory->WriteMemDWord(laddr,(void *) data, CPL==3)))
	{
		Bit16u error_code;
		error_code |= ((CPL==3) << 2) | (1 << 1);
		BX_CPU_THIS_PTR cr2 = laddr;
		// invalidate entry - we can get away without maintaining A bit in PTE
		// if we don't maintain TLB entries without it set.
		exception(BX_PF_EXCEPTION, error_code, 0);
	}
	return;

#endif

	access_linear(laddr, 4, CPL==3, BX_WRITE, (void *) data);
}

	void
CMSWIN_X86_CPU::write_push_word(unsigned s, Bit32u offset, Bit16u *data)
{
	Bit32u laddr;
	bx_segment_reg_t *seg;

	seg = &BX_CPU_THIS_PTR program_visible_sregs[s];
	write_virtual_checks(seg, offset, 2);

	laddr = seg->cache.u.segment.base + offset;
	BX_INSTR_MEM_DATA(laddr, 2, BX_WRITE);

	// all checks OK

#if (T_READ_WRITE_BYTES==1)

	if (!(LinearMemory->WriteMemWord(laddr,(void *) data, CPL==3)))
	{
		Bit16u error_code;
		error_code |= ((CPL==3) << 2) | (1 << 1);
		BX_CPU_THIS_PTR cr2 = laddr;
		// invalidate entry - we can get away without maintaining A bit in PTE
		// if we don't maintain TLB entries without it set.
		exception(BX_PF_EXCEPTION, error_code, 0);
	}
	LinearMemory->m_LastWriteMemSize = 0;
	return;

#endif

	access_linear(laddr, 2, CPL==3, BX_WRITE, (void *) data);
}

	void
CMSWIN_X86_CPU::write_push_dword(unsigned s, Bit32u offset, Bit32u *data)
{
	Bit32u laddr;
	bx_segment_reg_t *seg;

	seg = &BX_CPU_THIS_PTR program_visible_sregs[s];
	write_virtual_checks(seg, offset, 4);

	laddr = seg->cache.u.segment.base + offset;
	BX_INSTR_MEM_DATA(laddr, 4, BX_WRITE);

	// all checks OK

#if (T_READ_WRITE_BYTES==1)

	if (!(LinearMemory->WriteMemDWord(laddr,(void *) data, CPL==3)))
	{
		Bit16u error_code;
		error_code |= ((CPL==3) << 2) | (1 << 1);
		BX_CPU_THIS_PTR cr2 = laddr;
		// invalidate entry - we can get away without maintaining A bit in PTE
		// if we don't maintain TLB entries without it set.
		exception(BX_PF_EXCEPTION, error_code, 0);
	}
	LinearMemory->m_LastWriteMemSize = 0;
	return;

#endif

	access_linear(laddr, 4, CPL==3, BX_WRITE, (void *) data);
}

	void
CMSWIN_X86_CPU::read_virtual_byte(unsigned s, Bit32u offset, Bit8u *data)
{
	Bit32u laddr;
	bx_segment_reg_t *seg;

	seg = &BX_CPU_THIS_PTR program_visible_sregs[s];
	read_virtual_checks(seg, offset, 1);

	laddr = seg->cache.u.segment.base + offset;
	BX_INSTR_MEM_DATA(laddr, 1, BX_READ);

	// all checks OK

#if (T_READ_WRITE_BYTES==1)

	if (!(LinearMemory->ReadMemByte(laddr,(void *) data, CPL==3)))
	{
		Bit16u error_code;
		error_code |= ((CPL==3) << 2) | (1 << 1);
		BX_CPU_THIS_PTR cr2 = laddr;
		// invalidate entry - we can get away without maintaining A bit in PTE
		// if we don't maintain TLB entries without it set.
		exception(BX_PF_EXCEPTION, error_code, 0);
	}
	return;

#endif

	access_linear(laddr, 1, CPL==3, BX_READ, (void *) data);
}


	void
CMSWIN_X86_CPU::read_virtual_word(unsigned s, Bit32u offset, Bit16u *data)
{
	Bit32u laddr;
	bx_segment_reg_t *seg;

	seg = &BX_CPU_THIS_PTR program_visible_sregs[s];
	read_virtual_checks(seg, offset, 2);

	laddr = seg->cache.u.segment.base + offset;
	BX_INSTR_MEM_DATA(laddr, 2, BX_READ);

	// all checks OK

#if (T_READ_WRITE_BYTES==1)

	if (!(LinearMemory->ReadMemWord(laddr,(void *) data, CPL==3)))
	{
		Bit16u error_code;
		error_code |= ((CPL==3) << 2) | (1 << 1);
		BX_CPU_THIS_PTR cr2 = laddr;
		// invalidate entry - we can get away without maintaining A bit in PTE
		// if we don't maintain TLB entries without it set.
		exception(BX_PF_EXCEPTION, error_code, 0);
	}
	return;

#endif

	access_linear(laddr, 2, CPL==3, BX_READ, (void *) data);
}

	void
CMSWIN_X86_CPU::read_virtual_dword(unsigned s, Bit32u offset, Bit32u *data)
{
	Bit32u laddr;
	bx_segment_reg_t *seg;

	seg = &BX_CPU_THIS_PTR program_visible_sregs[s];
	read_virtual_checks(seg, offset, 4);

	laddr = seg->cache.u.segment.base + offset;
	BX_INSTR_MEM_DATA(laddr, 4, BX_READ);

	// all checks OK

#if (T_READ_WRITE_BYTES==1)

	if (!(LinearMemory->ReadMemDWord(laddr,(void *) data, CPL==3)))
	{
		Bit16u error_code;
		error_code |= ((CPL==3) << 2) | (1 << 1);
		BX_CPU_THIS_PTR cr2 = laddr;
		// invalidate entry - we can get away without maintaining A bit in PTE
		// if we don't maintain TLB entries without it set.
		exception(BX_PF_EXCEPTION, error_code, 0);
	}
	return;

#endif

	access_linear(laddr, 4, CPL==3, BX_READ, (void *) data);
}

//////////////////////////////////////////////////////////////
// special Read-Modify-Write operations                     //
// address translation info is kept across read/write calls //
//////////////////////////////////////////////////////////////

	void
CMSWIN_X86_CPU::read_RMW_virtual_byte(unsigned s, Bit32u offset, Bit8u *data)
{
	Bit32u laddr;
	bx_segment_reg_t *seg;

	seg = &BX_CPU_THIS_PTR program_visible_sregs[s];
	write_virtual_checks(seg, offset, 1);

	laddr = seg->cache.u.segment.base + offset;
	BX_INSTR_MEM_DATA(laddr, 1, BX_READ);

	// all checks OK

#if (T_READ_WRITE_BYTES==1)

	if (!(LinearMemory->ReadModifyMemByte(laddr,(void *) data, CPL==3)))
	{
		Bit16u error_code;
		error_code |= ((CPL==3) << 2) | (1 << 1);
		BX_CPU_THIS_PTR cr2 = laddr;
		// invalidate entry - we can get away without maintaining A bit in PTE
		// if we don't maintain TLB entries without it set.
		exception(BX_PF_EXCEPTION, error_code, 0);
	}
	return;

#endif

	ReadModifyWriteLinearAddress = laddr;

	access_linear(laddr, 1, CPL==3, BX_RW, (void *) data);
}


	void
CMSWIN_X86_CPU::read_RMW_virtual_word(unsigned s, Bit32u offset, Bit16u *data)
{
	Bit32u laddr;
	bx_segment_reg_t *seg;

	seg = &BX_CPU_THIS_PTR program_visible_sregs[s];
	write_virtual_checks(seg, offset, 2);

	laddr = seg->cache.u.segment.base + offset;
	BX_INSTR_MEM_DATA(laddr, 2, BX_READ);

	// all checks OK

#if (T_READ_WRITE_BYTES==1)

	if (!(LinearMemory->ReadModifyMemWord(laddr,(void *) data, CPL==3)))
	{
		Bit16u error_code;
		error_code |= ((CPL==3) << 2) | (1 << 1);
		BX_CPU_THIS_PTR cr2 = laddr;
		// invalidate entry - we can get away without maintaining A bit in PTE
		// if we don't maintain TLB entries without it set.
		exception(BX_PF_EXCEPTION, error_code, 0);
	}
	return;

#endif

	ReadModifyWriteLinearAddress = laddr;

	access_linear(laddr, 2, CPL==3, BX_RW, (void *) data);
}

	void
CMSWIN_X86_CPU::read_RMW_virtual_dword(unsigned s, Bit32u offset, Bit32u *data)
{
	Bit32u laddr;
	bx_segment_reg_t *seg;

	seg = &BX_CPU_THIS_PTR program_visible_sregs[s];
	write_virtual_checks(seg, offset, 4);

	laddr = seg->cache.u.segment.base + offset;
	BX_INSTR_MEM_DATA(laddr, 4, BX_READ);

	// all checks OK

#if (T_READ_WRITE_BYTES==1)

	if (!(LinearMemory->ReadModifyMemDWord(laddr,(void *) data, CPL==3)))
	{
		Bit16u error_code;
		error_code |= ((CPL==3) << 2) | (1 << 1);
		BX_CPU_THIS_PTR cr2 = laddr;
		// invalidate entry - we can get away without maintaining A bit in PTE
		// if we don't maintain TLB entries without it set.
		exception(BX_PF_EXCEPTION, error_code, 0);
	}
	return;

#endif

	ReadModifyWriteLinearAddress = laddr;

	access_linear(laddr, 4, CPL==3, BX_RW, (void *) data);
}

	void
CMSWIN_X86_CPU::write_RMW_virtual_byte(Bit8u val8)
{
	BX_INSTR_MEM_DATA(BX_CPU_THIS_PTR address_xlation.paddress1, 1, BX_WRITE);

#if (T_READ_WRITE_BYTES==1)

	LinearMemory->WriteModifyMemByte((void *)&val8);
	return;

#endif

	Bit32u laddr = ReadModifyWriteLinearAddress;

	access_linear(laddr, 1, CPL==3, BX_WRITE, (void *)&val8);
}

	void
CMSWIN_X86_CPU::write_RMW_virtual_word(Bit16u val16)
{
	BX_INSTR_MEM_DATA(BX_CPU_THIS_PTR address_xlation.paddress1, 2, BX_WRITE);

#if (T_READ_WRITE_BYTES==1)

	LinearMemory->WriteModifyMemWord((void *)&val16);
	return;

#endif

	Bit32u laddr = ReadModifyWriteLinearAddress;

	access_linear(laddr, 2, CPL==3, BX_WRITE, (void *)&val16);
}

  void
CMSWIN_X86_CPU::write_RMW_virtual_dword(Bit32u val32)
{
	BX_INSTR_MEM_DATA(BX_CPU_THIS_PTR address_xlation.paddress1, 4, BX_WRITE);

#if (T_READ_WRITE_BYTES==1)

	LinearMemory->WriteModifyMemDWord((void *)&val32);
	return;

#endif

	Bit32u laddr = ReadModifyWriteLinearAddress;

	access_linear(laddr, 4, CPL==3, BX_WRITE, (void *)&val32);
}

void CMSWIN_X86_CPU::access_linear(Bit32u address, unsigned length, unsigned pl,
				 unsigned rw, void *data)
{
	bool ret_code;

	Bit8u buff[16];

	if (rw==BX_WRITE)
	{
		if (length==4)
		{
			Bit32u temp = *(Bit32u*)data;
			buff[0] = (Bit8u)temp;
			buff[1] = (Bit8u)(temp>>8);
			buff[2] = (Bit8u)(temp>>16);
			buff[3] = (Bit8u)(temp>>24);
		}
		if (length==2)
		{
			Bit16u temp = *(Bit16u*)data;
			buff[0] = (Bit8u)temp;
			buff[1] = (Bit8u)(temp>>8);
		}
		if (length==1)
		{
			Bit8u temp = *(Bit8u*)data;
			buff[0] = (Bit8u)temp;
		}

		ret_code = LinearMemory->WriteMemXBytes(address,length,buff,pl);

		if (!ret_code)
		{
			Bit16u error_code;
			error_code |= ((CPL==3) << 2) | (1 << 1);
			BX_CPU_THIS_PTR cr2 = address;
			// invalidate entry - we can get away without maintaining A bit in PTE
			// if we don't maintain TLB entries without it set.
			exception(BX_PF_EXCEPTION, error_code, 0);
		}
	}
	else
	{
		ret_code = LinearMemory->ReadMemXBytes(address,length,buff,pl);

		if (!ret_code)
		{
			Bit16u error_code;
			error_code |= ((CPL==3) << 2) | (1 << 1);
			BX_CPU_THIS_PTR cr2 = address;
			// invalidate entry - we can get away without maintaining A bit in PTE
			// if we don't maintain TLB entries without it set.
			exception(BX_PF_EXCEPTION, error_code, 0);
		}

		if (length==4)
		{
			*(Bit32u*)data = buff[0] + (buff[1]<<8) + (buff[2]<<16) + (buff[3]<<24);
		}
		if (length==2)
		{
			*(Bit16u*)data = buff[0] + (buff[1]<<8) ;
		}
		if (length==1)
		{
			*(Bit8u*)data = buff[0];
		}
	}

	return;
}

Bit32u CMSWIN_X86_CPU::itranslate_linear(Bit32u laddress, unsigned pl)
{
	return 0;
}

Bit32u CMSWIN_X86_CPU::dtranslate_linear(Bit32u laddress, unsigned pl, unsigned rw)
{
	return 0;
}

int CMSWIN_X86_CPU::get_physical_host_memory(void **physical_address_base)
{
	return LinearMemory->GetPhysicalHostMemory((Bit8u**)physical_address_base);
}

	Bit8u *
CMSWIN_X86_CPU::getHostMemPtr(Bit32u linear_addr,unsigned op,Bit32u **access_stamp_ptr)
{
	MEMORY_PAGE *mem_page;
	Bit8u *fetch_ptr;

	mem_page = LinearMemory->GetCodePage(linear_addr);

	if( mem_page==NULL || ((mem_page->Attribute & MP_KERNEL) && CPL==3))
	{
		fetch_ptr = NULL;
	}		
	else
	{
		fetch_ptr = (Bit8u*)mem_page->PhysAddr;
		if (access_stamp_ptr)
		{
            *access_stamp_ptr = 
				(Bit32u*)&mem_page->AccessExecuteCount;
		}
	}

	if (fetch_ptr == NULL)
		exception(BX_PF_EXCEPTION, 0, 0);

	return fetch_ptr;
}

	void 
CMSWIN_X86_CPU::Init(CVEMemory *addrspace)
{
	LinearMemory = addrspace;
	init(mem);

	memset(&last_read_write,0,sizeof(last_read_write));
	strcpy(program_visible_sregs[BX_SEG_REG_ES].strseg,"ES");
	strcpy(program_visible_sregs[BX_SEG_REG_CS].strseg,"CS");
	strcpy(program_visible_sregs[BX_SEG_REG_SS].strseg,"SS");
	strcpy(program_visible_sregs[BX_SEG_REG_DS].strseg,"DS");
	strcpy(program_visible_sregs[BX_SEG_REG_FS].strseg,"FS");
	strcpy(program_visible_sregs[BX_SEG_REG_GS].strseg,"GS");

	program_visible_sregs[BX_SEG_REG_ES].exception_number = BX_GP_EXCEPTION;
	program_visible_sregs[BX_SEG_REG_CS].exception_number = BX_GP_EXCEPTION;
	program_visible_sregs[BX_SEG_REG_SS].exception_number = BX_SS_EXCEPTION;
	program_visible_sregs[BX_SEG_REG_DS].exception_number = BX_GP_EXCEPTION;
	program_visible_sregs[BX_SEG_REG_FS].exception_number = BX_GP_EXCEPTION;
	program_visible_sregs[BX_SEG_REG_GS].exception_number = BX_GP_EXCEPTION;

	return ;
}

	void 
CMSWIN_X86_CPU::Exit(void)
{
	this->exit();
}

	void
CMSWIN_X86_CPU::Reset(void)
{
	reset(1);
	BX_CPU_THIS_PTR lf_entrys[0].instr = 0;

#if (HOST_CPU_IS_I80386==1)
	BX_CPU_THIS_PTR eflags.x86.Word.lahf = 0x02;
	BX_CPU_THIS_PTR eflags.x86.Word.seto = 0x00;
#endif

    BX_CPU_THIS_PTR async_event = 0;
	BX_CPU_THIS_PTR program_visible_eflags = 0x02;
	//-----------------------------------------
	return;
}

	int
CMSWIN_X86_CPU::Execute(int steps)
{
	return x86_cpu_loop(steps);
}

	int
CMSWIN_X86_CPU::LoadAll286(LOADALL286 *pLoadAll)
{
	if (pLoadAll->MSW&0x01)
	{
		BX_CPU_THIS_PTR cr0.pe = 1;
	}
	else
	{
		BX_CPU_THIS_PTR cr0.pe = 0;
	}

	BX_CPU_THIS_PTR  write_flags(pLoadAll->fl,true,true);
	BX_CPU_THIS_PTR  REG_EIP = pLoadAll->ip;
	BX_CPU_THIS_PTR  GENERAL_REG_WORD(I_EAX) = pLoadAll->ax;
	BX_CPU_THIS_PTR  GENERAL_REG_WORD(I_ECX) = pLoadAll->cx;
	BX_CPU_THIS_PTR  GENERAL_REG_WORD(I_EDX) = pLoadAll->dx;
	BX_CPU_THIS_PTR  GENERAL_REG_WORD(I_EBX) = pLoadAll->bx;
	BX_CPU_THIS_PTR  GENERAL_REG_WORD(I_ESP) = pLoadAll->sp;
	BX_CPU_THIS_PTR  GENERAL_REG_WORD(I_EBP) = pLoadAll->bp;
	BX_CPU_THIS_PTR  GENERAL_REG_WORD(I_ESI) = pLoadAll->si;
	BX_CPU_THIS_PTR  GENERAL_REG_WORD(I_EDI) = pLoadAll->di;

	BX_CPU_THIS_PTR  gdtr.base = (Bit32u)pLoadAll->GDT.All.Base;
	BX_CPU_THIS_PTR  gdtr.limit = (Bit16u)pLoadAll->GDT.Dword.Limit;
	BX_CPU_THIS_PTR  idtr.base = (Bit32u)pLoadAll->GDT.All.Base;
	BX_CPU_THIS_PTR  idtr.limit = (Bit16u)pLoadAll->GDT.Dword.Limit;

	BX_CPU_THIS_PTR  tr.selector.value =  (Bit16u)pLoadAll->TR;
	BX_CPU_THIS_PTR  ldtr.selector.value =  (Bit16u)pLoadAll->LDTR;
	BX_CPU_THIS_PTR  program_visible_sregs[BX_SEG_REG_ES].selector.value = (Bit16u)pLoadAll->ES;
	BX_CPU_THIS_PTR  program_visible_sregs[BX_SEG_REG_CS].selector.value = (Bit16u)pLoadAll->CS;
	BX_CPU_THIS_PTR  program_visible_sregs[BX_SEG_REG_SS].selector.value = (Bit16u)pLoadAll->SS;
	BX_CPU_THIS_PTR  program_visible_sregs[BX_SEG_REG_DS].selector.value = (Bit16u)pLoadAll->DS;

	WriteSegmentCache286(&BX_CPU_THIS_PTR tr,&pLoadAll->TSS);
	WriteSegmentCache286(&BX_CPU_THIS_PTR ldtr,&pLoadAll->LDT);

	WriteSegmentCache286(&BX_CPU_THIS_PTR program_visible_sregs[BX_SEG_REG_ES],&pLoadAll->ES_D);
	WriteSegmentCache286(&BX_CPU_THIS_PTR program_visible_sregs[BX_SEG_REG_CS],&pLoadAll->CS_D);
	WriteSegmentCache286(&BX_CPU_THIS_PTR program_visible_sregs[BX_SEG_REG_SS],&pLoadAll->SS_D);
	WriteSegmentCache286(&BX_CPU_THIS_PTR program_visible_sregs[BX_SEG_REG_DS],&pLoadAll->DS_D);
	BX_CPU_THIS_PTR async_event = 0;
	return 1;
}

	int
CMSWIN_X86_CPU::LoadAll386(LOADALL386 *pLoadAll)
{
	if (pLoadAll->CR0&0x01)
	{
		BX_CPU_THIS_PTR cr0.pe = 1;
	}
	else
	{
		BX_CPU_THIS_PTR cr0.pe = 0;
	}

	BX_CPU_THIS_PTR write_eflags(pLoadAll->efl,true,true,true,true);
	BX_CPU_THIS_PTR REG_EIP = pLoadAll->eip;
	BX_CPU_THIS_PTR GENERAL_REG_DWORD(I_EAX) = pLoadAll->eax;
	BX_CPU_THIS_PTR GENERAL_REG_DWORD(I_ECX) = pLoadAll->ecx;
	BX_CPU_THIS_PTR GENERAL_REG_DWORD(I_EDX) = pLoadAll->edx;
	BX_CPU_THIS_PTR GENERAL_REG_DWORD(I_EBX) = pLoadAll->ebx;
	BX_CPU_THIS_PTR GENERAL_REG_DWORD(I_ESP) = pLoadAll->esp;
	BX_CPU_THIS_PTR GENERAL_REG_DWORD(I_EBP) = pLoadAll->ebp;
	BX_CPU_THIS_PTR GENERAL_REG_DWORD(I_ESI) = pLoadAll->esi;
	BX_CPU_THIS_PTR GENERAL_REG_DWORD(I_EDI) = pLoadAll->edi;

	BX_CPU_THIS_PTR gdtr.base = (Bit32u)pLoadAll->GDT.QWord.Base;
	BX_CPU_THIS_PTR gdtr.limit = (Bit16u)pLoadAll->GDT.QWord.Limit;
	BX_CPU_THIS_PTR idtr.base = (Bit32u)pLoadAll->IDT.QWord.Base;
	BX_CPU_THIS_PTR idtr.limit = (Bit16u)pLoadAll->IDT.QWord.Limit;

	BX_CPU_THIS_PTR tr.selector.value =  (Bit16u)pLoadAll->TR;
	BX_CPU_THIS_PTR ldtr.selector.value =  (Bit16u)pLoadAll->LDTR;
	BX_CPU_THIS_PTR program_visible_sregs[BX_SEG_REG_ES].selector.value = (Bit16u)pLoadAll->ES;
	BX_CPU_THIS_PTR program_visible_sregs[BX_SEG_REG_CS].selector.value = (Bit16u)pLoadAll->CS;
	BX_CPU_THIS_PTR program_visible_sregs[BX_SEG_REG_SS].selector.value = (Bit16u)pLoadAll->SS;
	BX_CPU_THIS_PTR program_visible_sregs[BX_SEG_REG_DS].selector.value = (Bit16u)pLoadAll->DS;
	BX_CPU_THIS_PTR program_visible_sregs[BX_SEG_REG_FS].selector.value = (Bit16u)pLoadAll->FS;
	BX_CPU_THIS_PTR program_visible_sregs[BX_SEG_REG_GS].selector.value = (Bit16u)pLoadAll->GS;

	WriteSegmentCache386(&BX_CPU_THIS_PTR tr,&pLoadAll->TSS);
	WriteSegmentCache386(&BX_CPU_THIS_PTR ldtr,&pLoadAll->LDT);

	WriteSegmentCache386(&BX_CPU_THIS_PTR program_visible_sregs[BX_SEG_REG_ES],&pLoadAll->ES_D);
	WriteSegmentCache386(&BX_CPU_THIS_PTR program_visible_sregs[BX_SEG_REG_CS],&pLoadAll->CS_D);
	WriteSegmentCache386(&BX_CPU_THIS_PTR program_visible_sregs[BX_SEG_REG_SS],&pLoadAll->SS_D);
	WriteSegmentCache386(&BX_CPU_THIS_PTR program_visible_sregs[BX_SEG_REG_DS],&pLoadAll->DS_D);
	WriteSegmentCache386(&BX_CPU_THIS_PTR program_visible_sregs[BX_SEG_REG_FS],&pLoadAll->FS_D);
	WriteSegmentCache386(&BX_CPU_THIS_PTR program_visible_sregs[BX_SEG_REG_GS],&pLoadAll->GS_D);
	BX_CPU_THIS_PTR async_event = 0;
	return 1;
}

	Boolean
CMSWIN_X86_CPU::WriteSegmentCache286(bx_segment_reg_t *pSegment,LOADALL286_DESCRIPTOR_T *pLoadDescriptor)
{
	pSegment->selector.rpl = (Bit8u)(pSegment->selector.value&0x03);
	pSegment->selector.ti = ((pSegment->selector.value>>2)&0x01);
	pSegment->selector.index = (pSegment->selector.value>>3);

	pSegment->cache.valid = 1;							// 0 = invalid, 1 = valid
	pSegment->cache.p = 1; //pLoadDescriptor->P;				// present
	pSegment->cache.dpl = pLoadDescriptor->Descr.DPL;			// descriptor privilege level 0..3
	pSegment->cache.segment = pLoadDescriptor->Descr.DT;		// 0 = system/gate, 1 = data/code segment
	pSegment->cache.type = pLoadDescriptor->Descr.TYPE;       // For system & gate descriptors, only

	if (pSegment==&BX_CPU_THIS_PTR tr)
	{
		pSegment->cache.u.tss286.base = pLoadDescriptor->All.Base;
		pSegment->cache.u.tss286.limit = pLoadDescriptor->Dword.Limit;
		return true;
	}

	if (pSegment==&BX_CPU_THIS_PTR ldtr)
	{
		pSegment->cache.u.ldt.base = pLoadDescriptor->All.Base;
		pSegment->cache.u.ldt.limit = (Bit16u)pLoadDescriptor->Dword.Limit;
		return true;
	}

	pSegment->cache.u.segment.base = pLoadDescriptor->All.Base;
	pSegment->cache.u.segment.limit_scaled = pLoadDescriptor->Dword.Limit;
	pSegment->cache.u.segment.d_b = BIT16;
	pSegment->cache.u.segment.g = 0;

	pSegment->cache.u.segment.executable = ((pSegment->cache.type>>0x03)&0x01);
	pSegment->cache.u.segment.c_ed = ((pSegment->cache.type>>0x02)&0x01);
	pSegment->cache.u.segment.r_w = ((pSegment->cache.type>>0x01)&0x01);
	pSegment->cache.u.segment.a = 1;

	if ((pSegment->cache.type&0x08)==0x08)
	{
		pSegment->cache.u.segment.c_ed = (pSegment->cache.type>>2)&0x01;
		pSegment->cache.u.segment.executable = 1;
	}
	else
	{
		pSegment->cache.u.segment.c_ed = (pSegment->cache.type>>2)&0x01;
		pSegment->cache.u.segment.executable = 0;
	}

	return true;
}

	Boolean
CMSWIN_X86_CPU::WriteSegmentCache386(bx_segment_reg_t *pSegment,LOADALL386_DESCRIPTOR_T *pLoadDescriptor)
{
	pSegment->selector.rpl = (Bit8u)(pSegment->selector.value&0x03);
	pSegment->selector.ti = ((pSegment->selector.value>>2)&0x01);
	pSegment->selector.index = (pSegment->selector.value>>3);

	pSegment->cache.valid = 1;							// 0 = invalid, 1 = valid
	pSegment->cache.p = 1; //pLoadDescriptor->P;		// present
	pSegment->cache.dpl = pLoadDescriptor->Descr.DPL;			// descriptor privilege level 0..3
	pSegment->cache.segment = pLoadDescriptor->Descr.DT;		// 0 = system/gate, 1 = data/code segment
	pSegment->cache.type = pLoadDescriptor->Descr.TYPE;       // For system & gate descriptors, only

	if (pSegment==&BX_CPU_THIS_PTR tr)
	{
		pSegment->cache.u.tss386.base = pLoadDescriptor->QWord.Base;
		pSegment->cache.u.tss386.limit = pLoadDescriptor->QWord.Limit;
		pSegment->cache.u.tss386.limit_scaled = pLoadDescriptor->QWord.Limit;
		return true;
	}

	if (pSegment==&BX_CPU_THIS_PTR ldtr)
	{
		pSegment->cache.u.ldt.base = pLoadDescriptor->QWord.Base;
		pSegment->cache.u.ldt.limit = (Bit16u)pLoadDescriptor->QWord.Limit;
		return true;
	}

	pSegment->cache.u.segment.base = pLoadDescriptor->QWord.Base;
	pSegment->cache.u.segment.limit_scaled = pLoadDescriptor->QWord.Limit;
	pSegment->cache.u.segment.d_b = BIT32;
	pSegment->cache.u.segment.g = 1;

	pSegment->cache.u.segment.executable = ((pSegment->cache.type>>0x03)&0x01);
	pSegment->cache.u.segment.c_ed = ((pSegment->cache.type>>0x02)&0x01);
	pSegment->cache.u.segment.r_w = ((pSegment->cache.type>>0x01)&0x01);
	pSegment->cache.u.segment.a = 1;


	if ((pSegment->cache.type&0x08)==0x08)
	{
		pSegment->cache.u.segment.c_ed = (pSegment->cache.type>>2)&0x01;
		pSegment->cache.u.segment.executable = 1;
	}
	else
	{
		pSegment->cache.u.segment.c_ed = (pSegment->cache.type>>2)&0x01;
		pSegment->cache.u.segment.executable = 0;
	}

	return true;
}

	Boolean
CMSWIN_X86_CPU::IntelIntFault(int _vector)
{
	static int errorCode[0x20+0x08] =
	{
		0,0,0,0,	0,0,0,0,
		1,0,1,1,	1,1,1,0,
		0,0,0,0,	0,0,0,0,
		0,0,0,0,	0,0,0,0,
		0,0,0,0,	0,0,0,0,
	};

	if (_vector>0x20)
		_vector= 0x20;

	if (errorCode[_vector]==1)
	{
		X86_ESP += 4;
	}

	return true;
}

	Boolean
CMSWIN_X86_CPU::IntelIntIret(int _vector)
{
	BX_CPU_THIS_PTR program_visible_sregs[BX_SEG_REG_CS] = BX_CPU_THIS_PTR save_cs;
	BX_CPU_THIS_PTR program_visible_sregs[BX_SEG_REG_SS] = BX_CPU_THIS_PTR save_ss;
	X86_EIP = BX_CPU_THIS_PTR save_eip;
	X86_ESP = BX_CPU_THIS_PTR save_esp;
	BX_CPU_THIS_PTR eflags = BX_CPU_THIS_PTR save_eflags;

	return true;
}
	void
CMSWIN_X86_CPU::UpdateContext(Boolean b)
{
	if (b)
	{
		write_eflags(BX_CPU_THIS_PTR program_visible_eflags,true,true,true,true);
		bytesleft = 0;
	}
	else
	{
		BX_CPU_THIS_PTR program_visible_eflags = read_eflags();
	}
}

