/////////////////////////////////////////////////////////////////////////
// $Id: inteli16.cpp,v 1.0 2002/10/08 16:04:05 bdenney Exp $
/////////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "x86cpu.h"
#include "icpu_dos.h"

void PrintfCPU(BX_CPU_C *cpu,char *s,int i=0);

	void
CMSDOS_X86_CPU::write_virtual_byte(unsigned s, Bit32u offset, Bit8u *data)
{
	Bit32u laddr;
	bx_segment_reg_t *seg;

	seg = &BX_CPU_THIS_PTR program_visible_sregs[s];
	//write_virtual_checks(seg, offset, 1);

	laddr = seg->cache.u.segment.base + offset;
	BX_INSTR_MEM_DATA(laddr, 1, BX_WRITE);

	// all checks OK
	access_linear(laddr, 1, CPL==3, BX_WRITE, (void *) data);
}

	void
CMSDOS_X86_CPU::write_virtual_word(unsigned s, Bit32u offset, Bit16u *data)
{
	Bit32u laddr;
	bx_segment_reg_t *seg;

	seg = &BX_CPU_THIS_PTR program_visible_sregs[s];
	//write_virtual_checks(seg, offset, 2);

	laddr = seg->cache.u.segment.base + offset;
	BX_INSTR_MEM_DATA(laddr, 2, BX_WRITE);

	// all checks OK
	access_linear(laddr, 2, CPL==3, BX_WRITE, (void *) data);
}

	void
CMSDOS_X86_CPU::write_virtual_dword(unsigned s, Bit32u offset, Bit32u *data)
{
	Bit32u laddr;
	bx_segment_reg_t *seg;

	seg = &BX_CPU_THIS_PTR program_visible_sregs[s];
	//write_virtual_checks(seg, offset, 4);

	laddr = seg->cache.u.segment.base + offset;
	BX_INSTR_MEM_DATA(laddr, 4, BX_WRITE);

	// all checks OK
	access_linear(laddr, 4, CPL==3, BX_WRITE, (void *) data);
}

	void
CMSDOS_X86_CPU::write_push_word(unsigned s, Bit32u offset, Bit16u *data)
{
	Bit32u laddr;
	bx_segment_reg_t *seg;

	seg = &BX_CPU_THIS_PTR program_visible_sregs[s];
	//write_virtual_checks(seg, offset, 2);

	laddr = seg->cache.u.segment.base + offset;
	BX_INSTR_MEM_DATA(laddr, 2, BX_WRITE);

	// all checks OK
	access_linear(laddr, 2, CPL==3, BX_WRITE, (void *) data);

	last_read_write.write_bytes = 0;
}

	void
CMSDOS_X86_CPU::write_push_dword(unsigned s, Bit32u offset, Bit32u *data)
{
	Bit32u laddr;
	bx_segment_reg_t *seg;

	seg = &BX_CPU_THIS_PTR program_visible_sregs[s];
	//write_virtual_checks(seg, offset, 4);

	laddr = seg->cache.u.segment.base + offset;
	BX_INSTR_MEM_DATA(laddr, 4, BX_WRITE);

	// all checks OK
	access_linear(laddr, 4, CPL==3, BX_WRITE, (void *) data);

	last_read_write.write_bytes = 0;
}

	void
CMSDOS_X86_CPU::read_virtual_byte(unsigned s, Bit32u offset, Bit8u *data)
{
	Bit32u laddr;
	bx_segment_reg_t *seg;

	seg = &BX_CPU_THIS_PTR program_visible_sregs[s];
	//read_virtual_checks(seg, offset, 1);

	laddr = seg->cache.u.segment.base + offset;
	BX_INSTR_MEM_DATA(laddr, 1, BX_READ);

	// all checks OK
	access_linear(laddr, 1, CPL==3, BX_READ, (void *) data);
}


	void
CMSDOS_X86_CPU::read_virtual_word(unsigned s, Bit32u offset, Bit16u *data)
{
	Bit32u laddr;
	bx_segment_reg_t *seg;

	seg = &BX_CPU_THIS_PTR program_visible_sregs[s];
	//read_virtual_checks(seg, offset, 2);

	laddr = seg->cache.u.segment.base + offset;
	BX_INSTR_MEM_DATA(laddr, 2, BX_READ);

	// all checks OK
	access_linear(laddr, 2, CPL==3, BX_READ, (void *) data);
}

	void
CMSDOS_X86_CPU::read_virtual_dword(unsigned s, Bit32u offset, Bit32u *data)
{
	Bit32u laddr;
	bx_segment_reg_t *seg;

	seg = &BX_CPU_THIS_PTR program_visible_sregs[s];
	//read_virtual_checks(seg, offset, 4);

	laddr = seg->cache.u.segment.base + offset;
	BX_INSTR_MEM_DATA(laddr, 4, BX_READ);

	// all checks OK
	access_linear(laddr, 4, CPL==3, BX_READ, (void *) data);
}

//////////////////////////////////////////////////////////////
// special Read-Modify-Write operations                     //
// address translation info is kept across read/write calls //
//////////////////////////////////////////////////////////////

	void
CMSDOS_X86_CPU::read_RMW_virtual_byte(unsigned s, Bit32u offset, Bit8u *data)
{
	Bit32u laddr;
	bx_segment_reg_t *seg;

	seg = &BX_CPU_THIS_PTR program_visible_sregs[s];
	//write_virtual_checks(seg, offset, 1);

	laddr = seg->cache.u.segment.base + offset;
	BX_INSTR_MEM_DATA(laddr, 1, BX_READ);

	// all checks OK
	access_linear(laddr, 1, CPL==3, BX_READ, (void *) data);

	ReadModifyWriteLinearAddress = laddr;
	return ;
}


	void
CMSDOS_X86_CPU::read_RMW_virtual_word(unsigned s, Bit32u offset, Bit16u *data)
{
	Bit32u laddr;
	bx_segment_reg_t *seg;

	seg = &BX_CPU_THIS_PTR program_visible_sregs[s];
	//write_virtual_checks(seg, offset, 2);

	laddr = seg->cache.u.segment.base + offset;
	BX_INSTR_MEM_DATA(laddr, 2, BX_READ);

	// all checks OK
	access_linear(laddr, 2, CPL==3, BX_READ, (void *) data);

	ReadModifyWriteLinearAddress = laddr;
	return ;
}

	void
CMSDOS_X86_CPU::read_RMW_virtual_dword(unsigned s, Bit32u offset, Bit32u *data)
{
	Bit32u laddr;
	bx_segment_reg_t *seg;

	seg = &BX_CPU_THIS_PTR program_visible_sregs[s];
	//write_virtual_checks(seg, offset, 4);

	laddr = seg->cache.u.segment.base + offset;
	BX_INSTR_MEM_DATA(laddr, 4, BX_READ);

	// all checks OK
	access_linear(laddr, 4, CPL==3, BX_READ, (void *) data);

	ReadModifyWriteLinearAddress = laddr;
	return ;
}

	void
CMSDOS_X86_CPU::write_RMW_virtual_byte(Bit8u val8)
{
	Bit32u laddr;
	laddr = ReadModifyWriteLinearAddress;
	BX_INSTR_MEM_DATA(laddr, 1, BX_READ);
	// all checks OK
	access_linear(laddr, 1, CPL==3, BX_WRITE, (void *)&val8);
	return ;
}

	void
CMSDOS_X86_CPU::write_RMW_virtual_word(Bit16u val16)
{
	Bit32u laddr;
	laddr = ReadModifyWriteLinearAddress;
	BX_INSTR_MEM_DATA(laddr, 2, BX_READ);
	// all checks OK
	access_linear(laddr, 2, CPL==3, BX_WRITE, (void *)&val16);
	return ;
}

  void
CMSDOS_X86_CPU::write_RMW_virtual_dword(Bit32u val32)
{
	Bit32u laddr;
	laddr = ReadModifyWriteLinearAddress;
	BX_INSTR_MEM_DATA(laddr, 4, BX_READ);
	// all checks OK
	access_linear(laddr, 4, CPL==3, BX_WRITE, (void *)&val32);
	return ;
}

void CMSDOS_X86_CPU::access_linear(Bit32u address, unsigned length, unsigned pl,
				 unsigned rw, void *data)
{
	if (address>(0x100000+0x10000))
		exception(BX_PF_EXCEPTION, 0, 0);

	if (rw==BX_WRITE)
	{
		last_read_write.write_address = address;
		last_read_write.write_bytes = length;
		if (length==4)
		{
#ifdef BX_BIG_ENDIAN
			(*(LinearMemory+address)) = (*(Bit32u*)data);
			(*(LinearMemory+address+1))  = (*(Bit32u*)data)>>8;
			(*(LinearMemory+address+2))  = (*(Bit32u*)data)>>16;
			(*(LinearMemory+address+3))  = (*(Bit32u*)data)>>24;
#else
			(*(Bit32u*)(LinearMemory+address)) = (*(Bit32u*)data);
#endif

#if BX_SupportICache
			iCache.decWriteStamp(this,address);
			iCache.decWriteStamp(this,address + 3);
			iCache.decWriteHole(this,address,0x000f);
#endif
			return ;
		}
		if (length==2)
		{
#ifdef BX_BIG_ENDIAN
			(*(LinearMemory+address)) = (*(Bit16u*)data);
			(*(LinearMemory+address+1))  = (*(Bit16u*)data)>>8;
#else
			(*(Bit16u*)(LinearMemory+address)) = (*(Bit16u*)data);
#endif

#if BX_SupportICache
			iCache.decWriteStamp(this,address);
			iCache.decWriteStamp(this,address + 2);
			iCache.decWriteHole(this,address,0x0003);
#endif
			return ;
		}
		if (length==1)
		{
			(*(LinearMemory+address)) = (*(Bit8u*)data);
#if BX_SupportICache
			iCache.decWriteStamp(this,address);
			iCache.decWriteHole(this,address,0x0001);
#endif
			return ;
		}
	}
	else
	{
		last_read_write.read_address = address;
		last_read_write.read_bytes = length;
		if (length==4)
		{
#ifdef BX_BIG_ENDIAN
			*(Bit32u*)data = (*(LinearMemory+address)) +
							(*(LinearMemory+address+1)<<8) +
							(*(LinearMemory+address+2)<<16) +
							(*(LinearMemory+address+3)<<24);
#else
			*(Bit32u*)data = (*(Bit32u*)(LinearMemory+address));
#endif
			return ;
		}
		if (length==2)
		{
#ifdef BX_BIG_ENDIAN
			*(Bit16u*)data = (*(LinearMemory+address)) +
							(*(LinearMemory+address+1)<<8);
#else
			*(Bit16u*)data = (*(Bit16u*)(LinearMemory+address));
#endif
			return ;
		}
		if (length==1)
		{
			*(Bit8u*)data = (*(LinearMemory+address));
			return ;
		}
	}
	return;
}

Bit32u CMSDOS_X86_CPU::itranslate_linear(Bit32u laddress, unsigned pl)
{
	return laddress;
}

Bit32u CMSDOS_X86_CPU::dtranslate_linear(Bit32u laddress, unsigned pl, unsigned rw)
{
	return laddress;
}

int CMSDOS_X86_CPU::get_physical_host_memory(void **physical_address_base)
{
	*physical_address_base = LinearMemory;
	return ((0x100000+0x10000)/0x1000);
}

Bit32u temp_access_stamp_ptr;

	Bit8u *
CMSDOS_X86_CPU::getHostMemPtr(Bit32u linear_addr,unsigned op,Bit32u **access_stamp_ptr)
{
	Bit8u *fetch_ptr;
	fetch_ptr = LinearMemory + (linear_addr&(0-1-0x0fff));

	if (access_stamp_ptr)
		*access_stamp_ptr = &temp_access_stamp_ptr;
	if (linear_addr>(0x100000+0x10000))
	{
		fetch_ptr = NULL;
	}
	if (fetch_ptr == NULL)
		exception(BX_PF_EXCEPTION, 0, 0);

	return fetch_ptr;
}

	void 
CMSDOS_X86_CPU::Init(unsigned char *addrspace)
{
	LinearMemory = addrspace;
	init(mem);

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
CMSDOS_X86_CPU::Exit(void)
{
	this->exit();
}

	void
CMSDOS_X86_CPU::Reset(void)
{
	reset(1);
	BX_CPU_THIS_PTR lf_entrys[0].instr = 0;
	memset(&last_read_write,0,sizeof(last_read_write));
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
CMSDOS_X86_CPU::Steps(int steps)
{
	return x86_cpu_loop(steps);
}

	void
CMSDOS_X86_CPU::UpdateContext(Boolean b)
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




