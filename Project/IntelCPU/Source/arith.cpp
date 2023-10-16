/////////////////////////////////////////////////////////////////////////
// $Id: arith.cc,v 1.0 2002/10/10 04:57:05 bdenney Exp $
/////////////////////////////////////////////////////////////////////////


#include "stdafx.h"
#include "x86cpu.h"
//---------------------------------------------------------
//ÐéÄâÖ´ÐÐ--Ö¸ÁîÎ¢º¯Êý  ËãÊõÖ¸Áî
//---------------------------------------------------------


	void
BX_CPU_C::INC_EGb(BX_CPU_C *icpu,bxInstruction_c *i)
{
	Bit8u op1,sum;

	op1 = READ_VIRTUAL_8BIT_REG(MODRMrm(i));

	sum =  op1 +  1;

	WRITE_VIRTUAL_8BIT_REG(MODRMrm(i), sum);

#if (HOST_CPU_IS_I80386==0)
	BX_CPU_CLASS_PTR lf_entrys[BX_LF_INDEX_OSZAP].result_8 = sum;
	BX_CPU_CLASS_PTR lf_entrys[BX_LF_INDEX_OSZAP].instr = BX_INSTR_INC8;
	BX_CPU_CLASS_PTR lf_flags_status = (BX_CPU_CLASS_PTR lf_flags_status & 0x00000f) | BX_LF_MASK_OSZAP;
#endif //#if (HOST_CPU_IS_I80386==0) 

#if (HOST_CPU_IS_I80386==1) 
	Bit32u x86_lf_flags = BX_CPU_CLASS_PTR eflags.x86.eax;
	__asm
	{
		mov eax,x86_lf_flags
		sahf
		INC op1
		lahf
		seto al
		mov x86_lf_flags,eax
	}
	BX_CPU_CLASS_PTR eflags.x86.eax = x86_lf_flags;
#endif //#if (HOST_CPU_IS_I80386==1) 
}

	void
BX_CPU_C::INC_EGw(BX_CPU_C *icpu,bxInstruction_c *i)
{
	Bit16u op1,sum;

	op1 = READ_VIRTUAL_16BIT_REG(MODRMrm(i));

	sum =  op1 +  1;

	WRITE_VIRTUAL_16BIT_REG(MODRMrm(i), sum);

#if (HOST_CPU_IS_I80386==0)
	BX_CPU_CLASS_PTR lf_entrys[BX_LF_INDEX_OSZAP].result_16 = sum;
	BX_CPU_CLASS_PTR lf_entrys[BX_LF_INDEX_OSZAP].instr = BX_INSTR_INC16;
	BX_CPU_CLASS_PTR lf_flags_status = (BX_CPU_CLASS_PTR lf_flags_status & 0x00000f) | BX_LF_MASK_OSZAP;
#endif //#if (HOST_CPU_IS_I80386==0) 

#if (HOST_CPU_IS_I80386==1) 
	Bit32u x86_lf_flags = BX_CPU_CLASS_PTR eflags.x86.eax;
	__asm
	{
		mov eax,x86_lf_flags
		sahf
		INC op1
		lahf
		seto al
		mov x86_lf_flags,eax
	}
	BX_CPU_CLASS_PTR eflags.x86.eax = x86_lf_flags;
#endif //#if (HOST_CPU_IS_I80386==1) 
}

	void
BX_CPU_C::INC_EGd(BX_CPU_C *icpu,bxInstruction_c *i)
{
	Bit32u op1,sum;

	op1 = READ_VIRTUAL_32BIT_REG(MODRMrm(i));

	sum =  op1 +  1;

	WRITE_VIRTUAL_32BIT_REG(MODRMrm(i), sum);

#if (HOST_CPU_IS_I80386==0)
	BX_CPU_CLASS_PTR lf_entrys[BX_LF_INDEX_OSZAP].result_32 = sum;
	BX_CPU_CLASS_PTR lf_entrys[BX_LF_INDEX_OSZAP].instr = BX_INSTR_INC32;
	BX_CPU_CLASS_PTR lf_flags_status = (BX_CPU_CLASS_PTR lf_flags_status & 0x00000f) | BX_LF_MASK_OSZAP;
#endif //#if (HOST_CPU_IS_I80386==0) 

#if (HOST_CPU_IS_I80386==1) 
	Bit32u x86_lf_flags = BX_CPU_CLASS_PTR eflags.x86.eax;
	__asm
	{
		mov eax,x86_lf_flags
		sahf
		INC op1
		lahf
		seto al
		mov x86_lf_flags,eax
	}
	BX_CPU_CLASS_PTR eflags.x86.eax = x86_lf_flags;
#endif //#if (HOST_CPU_IS_I80386==1) 
}

	void
BX_CPU_C::INC_RX(BX_CPU_C *icpu,bxInstruction_c *i)
{
	Bit16u op1,sum;

	op1 = READ_VIRTUAL_16BIT_REG(OPCODEb1(i)&7);

	sum =  op1 +  1;

	WRITE_VIRTUAL_16BIT_REG(OPCODEb1(i)&7, sum);

#if (HOST_CPU_IS_I80386==0)
	BX_CPU_CLASS_PTR lf_entrys[BX_LF_INDEX_OSZAP].result_16 = sum;
	BX_CPU_CLASS_PTR lf_entrys[BX_LF_INDEX_OSZAP].instr = BX_INSTR_INC16;
	BX_CPU_CLASS_PTR lf_flags_status = (BX_CPU_CLASS_PTR lf_flags_status & 0x00000f) | BX_LF_MASK_OSZAP;
#endif //#if (HOST_CPU_IS_I80386==0) 

#if (HOST_CPU_IS_I80386==1) 
	Bit32u x86_lf_flags = BX_CPU_CLASS_PTR eflags.x86.eax;
	__asm
	{
		mov eax,x86_lf_flags
		sahf
		INC op1
		lahf
		seto al
		mov x86_lf_flags,eax
	}
	BX_CPU_CLASS_PTR eflags.x86.eax = x86_lf_flags;
#endif //#if (HOST_CPU_IS_I80386==1) 
}

	void
BX_CPU_C::INC_ERX(BX_CPU_C *icpu,bxInstruction_c *i)
{
	Bit32u op1,sum;

	op1 = READ_VIRTUAL_32BIT_REG(OPCODEb1(i)&7);

	sum =  op1 +  1;

	WRITE_VIRTUAL_32BIT_REG(OPCODEb1(i)&7, sum);

#if (HOST_CPU_IS_I80386==0)
	BX_CPU_CLASS_PTR lf_entrys[BX_LF_INDEX_OSZAP].result_32 = sum;
	BX_CPU_CLASS_PTR lf_entrys[BX_LF_INDEX_OSZAP].instr = BX_INSTR_INC32;
	BX_CPU_CLASS_PTR lf_flags_status = (BX_CPU_CLASS_PTR lf_flags_status & 0x00000f) | BX_LF_MASK_OSZAP;
#endif //#if (HOST_CPU_IS_I80386==0) 

#if (HOST_CPU_IS_I80386==1) 
	Bit32u x86_lf_flags = BX_CPU_CLASS_PTR eflags.x86.eax;
	__asm
	{
		mov eax,x86_lf_flags
		sahf
		INC op1
		lahf
		seto al
		mov x86_lf_flags,eax
	}
	BX_CPU_CLASS_PTR eflags.x86.eax = x86_lf_flags;
#endif //#if (HOST_CPU_IS_I80386==1) 
}

	void
BX_CPU_C::DEC_EGb(BX_CPU_C *icpu,bxInstruction_c *i)
{
	Bit8u op1,sum;

	op1 = READ_VIRTUAL_8BIT_REG(MODRMrm(i));

	sum =  op1 -  1;

	WRITE_VIRTUAL_8BIT_REG(MODRMrm(i), sum);

#if (HOST_CPU_IS_I80386==0)
	BX_CPU_CLASS_PTR lf_entrys[BX_LF_INDEX_OSZAP].result_8 = sum;
	BX_CPU_CLASS_PTR lf_entrys[BX_LF_INDEX_OSZAP].instr = BX_INSTR_DEC8;
	BX_CPU_CLASS_PTR lf_flags_status = (BX_CPU_CLASS_PTR lf_flags_status & 0x00000f) | BX_LF_MASK_OSZAP;
#endif //#if (HOST_CPU_IS_I80386==0) 

#if (HOST_CPU_IS_I80386==1) 
	Bit32u x86_lf_flags = BX_CPU_CLASS_PTR eflags.x86.eax;
	__asm
	{
		mov eax,x86_lf_flags
		sahf
		DEC op1
		lahf
		seto al
		mov x86_lf_flags,eax
	}
	BX_CPU_CLASS_PTR eflags.x86.eax = x86_lf_flags;
#endif //#if (HOST_CPU_IS_I80386==1) 
}

	void
BX_CPU_C::DEC_EGw(BX_CPU_C *icpu,bxInstruction_c *i)
{
	Bit16u op1,sum;

	op1 = READ_VIRTUAL_16BIT_REG(MODRMrm(i));

	sum =  op1 -  1;

	WRITE_VIRTUAL_16BIT_REG(MODRMrm(i), sum);

#if (HOST_CPU_IS_I80386==0)
	BX_CPU_CLASS_PTR lf_entrys[BX_LF_INDEX_OSZAP].result_16 = sum;
	BX_CPU_CLASS_PTR lf_entrys[BX_LF_INDEX_OSZAP].instr = BX_INSTR_DEC16;
	BX_CPU_CLASS_PTR lf_flags_status = (BX_CPU_CLASS_PTR lf_flags_status & 0x00000f) | BX_LF_MASK_OSZAP;
#endif //#if (HOST_CPU_IS_I80386==0) 

#if (HOST_CPU_IS_I80386==1) 
	Bit32u x86_lf_flags = BX_CPU_CLASS_PTR eflags.x86.eax;
	__asm
	{
		mov eax,x86_lf_flags
		sahf
		DEC op1
		lahf
		seto al
		mov x86_lf_flags,eax
	}
	BX_CPU_CLASS_PTR eflags.x86.eax = x86_lf_flags;
#endif //#if (HOST_CPU_IS_I80386==1) 
}

	void
BX_CPU_C::DEC_EGd(BX_CPU_C *icpu,bxInstruction_c *i)
{
	Bit32u op1,sum;

	op1 = READ_VIRTUAL_32BIT_REG(MODRMrm(i));

	sum =  op1 -  1;

	WRITE_VIRTUAL_32BIT_REG(MODRMrm(i), sum);

#if (HOST_CPU_IS_I80386==0)
	BX_CPU_CLASS_PTR lf_entrys[BX_LF_INDEX_OSZAP].result_32 = sum;
	BX_CPU_CLASS_PTR lf_entrys[BX_LF_INDEX_OSZAP].instr = BX_INSTR_DEC32;
	BX_CPU_CLASS_PTR lf_flags_status = (BX_CPU_CLASS_PTR lf_flags_status & 0x00000f) | BX_LF_MASK_OSZAP;
#endif //#if (HOST_CPU_IS_I80386==0) 

#if (HOST_CPU_IS_I80386==1) 
	Bit32u x86_lf_flags = BX_CPU_CLASS_PTR eflags.x86.eax;
	__asm
	{
		mov eax,x86_lf_flags
		sahf
		DEC op1
		lahf
		seto al
		mov x86_lf_flags,eax
	}
	BX_CPU_CLASS_PTR eflags.x86.eax = x86_lf_flags;
#endif //#if (HOST_CPU_IS_I80386==1) 
}

	void
BX_CPU_C::DEC_RX(BX_CPU_C *icpu,bxInstruction_c *i)
{
	Bit16u op1,sum;

	op1 = READ_VIRTUAL_16BIT_REG(OPCODEb1(i)&7);

	sum =  op1 -  1;

	WRITE_VIRTUAL_16BIT_REG(OPCODEb1(i)&7, sum);

#if (HOST_CPU_IS_I80386==0)
	BX_CPU_CLASS_PTR lf_entrys[BX_LF_INDEX_OSZAP].result_16 = sum;
	BX_CPU_CLASS_PTR lf_entrys[BX_LF_INDEX_OSZAP].instr = BX_INSTR_DEC16;
	BX_CPU_CLASS_PTR lf_flags_status = (BX_CPU_CLASS_PTR lf_flags_status & 0x00000f) | BX_LF_MASK_OSZAP;
#endif //#if (HOST_CPU_IS_I80386==0) 

#if (HOST_CPU_IS_I80386==1) 
	Bit32u x86_lf_flags = BX_CPU_CLASS_PTR eflags.x86.eax;
	__asm
	{
		mov eax,x86_lf_flags
		sahf
		DEC op1
		lahf
		seto al
		mov x86_lf_flags,eax
	}
	BX_CPU_CLASS_PTR eflags.x86.eax = x86_lf_flags;
#endif //#if (HOST_CPU_IS_I80386==1) 
}

	void
BX_CPU_C::DEC_ERX(BX_CPU_C *icpu,bxInstruction_c *i)
{
	Bit32u op1,sum;

	op1 = READ_VIRTUAL_32BIT_REG(OPCODEb1(i)&7);

	sum =  op1 -  1;

	WRITE_VIRTUAL_32BIT_REG(OPCODEb1(i)&7, sum);

#if (HOST_CPU_IS_I80386==0)
	BX_CPU_CLASS_PTR lf_entrys[BX_LF_INDEX_OSZAP].result_32 = sum;
	BX_CPU_CLASS_PTR lf_entrys[BX_LF_INDEX_OSZAP].instr = BX_INSTR_DEC32;
	BX_CPU_CLASS_PTR lf_flags_status = (BX_CPU_CLASS_PTR lf_flags_status & 0x00000f) | BX_LF_MASK_OSZAP;
#endif //#if (HOST_CPU_IS_I80386==0) 

#if (HOST_CPU_IS_I80386==1) 
	Bit32u x86_lf_flags = BX_CPU_CLASS_PTR eflags.x86.eax;
	__asm
	{
		mov eax,x86_lf_flags
		sahf
		DEC op1
		lahf
		seto al
		mov x86_lf_flags,eax
	}
	BX_CPU_CLASS_PTR eflags.x86.eax = x86_lf_flags;
#endif //#if (HOST_CPU_IS_I80386==1) 
}

	void
BX_CPU_C::NEG_EGb(BX_CPU_C *icpu,bxInstruction_c *i)
{
	Bit8u op1,sum;

	op1 = READ_VIRTUAL_8BIT_REG(MODRMrm(i));

	sum =  0- op1;

	WRITE_VIRTUAL_8BIT_REG(MODRMrm(i), sum);

#if (HOST_CPU_IS_I80386==0)
	BX_CPU_CLASS_PTR lf_entrys[BX_LF_INDEX_OSZAPC].result_8 = sum;
	BX_CPU_CLASS_PTR lf_entrys[BX_LF_INDEX_OSZAPC].instr = BX_INSTR_NEG8;
	BX_CPU_CLASS_PTR lf_flags_status = BX_LF_MASK_OSZAPC;
#endif //#if (HOST_CPU_IS_I80386==0) 

#if (HOST_CPU_IS_I80386==1) 
	Bit32u x86_lf_flags;
	__asm
	{
		NEG op1
		lahf
		seto al
		mov x86_lf_flags,eax
	}
	BX_CPU_CLASS_PTR eflags.x86.eax = x86_lf_flags;
#endif //#if (HOST_CPU_IS_I80386==1) 
}

	void
BX_CPU_C::NEG_EGw(BX_CPU_C *icpu,bxInstruction_c *i)
{
	Bit16u op1,sum;

	op1 = READ_VIRTUAL_16BIT_REG(MODRMrm(i));

	sum =  0- op1;

	WRITE_VIRTUAL_16BIT_REG(MODRMrm(i), sum);

#if (HOST_CPU_IS_I80386==0)
	BX_CPU_CLASS_PTR lf_entrys[BX_LF_INDEX_OSZAPC].result_16 = sum;
	BX_CPU_CLASS_PTR lf_entrys[BX_LF_INDEX_OSZAPC].instr = BX_INSTR_NEG16;
	BX_CPU_CLASS_PTR lf_flags_status = BX_LF_MASK_OSZAPC;
#endif //#if (HOST_CPU_IS_I80386==0) 

#if (HOST_CPU_IS_I80386==1) 
	Bit32u x86_lf_flags;
	__asm
	{
		NEG op1
		lahf
		seto al
		mov x86_lf_flags,eax
	}
	BX_CPU_CLASS_PTR eflags.x86.eax = x86_lf_flags;
#endif //#if (HOST_CPU_IS_I80386==1) 
}

	void
BX_CPU_C::NEG_EGd(BX_CPU_C *icpu,bxInstruction_c *i)
{
	Bit32u op1,sum;

	op1 = READ_VIRTUAL_32BIT_REG(MODRMrm(i));

	sum =  0- op1;

	WRITE_VIRTUAL_32BIT_REG(MODRMrm(i), sum);

#if (HOST_CPU_IS_I80386==0)
	BX_CPU_CLASS_PTR lf_entrys[BX_LF_INDEX_OSZAPC].result_32 = sum;
	BX_CPU_CLASS_PTR lf_entrys[BX_LF_INDEX_OSZAPC].instr = BX_INSTR_NEG32;
	BX_CPU_CLASS_PTR lf_flags_status = BX_LF_MASK_OSZAPC;
#endif //#if (HOST_CPU_IS_I80386==0) 

#if (HOST_CPU_IS_I80386==1) 
	Bit32u x86_lf_flags;
	__asm
	{
		NEG op1
		lahf
		seto al
		mov x86_lf_flags,eax
	}
	BX_CPU_CLASS_PTR eflags.x86.eax = x86_lf_flags;
#endif //#if (HOST_CPU_IS_I80386==1) 
}

	void
BX_CPU_C::NOT_EGb(BX_CPU_C *icpu,bxInstruction_c *i)
{
	Bit8u op1,sum;

	op1 = READ_VIRTUAL_8BIT_REG(MODRMrm(i));

	sum =  ~  op1;

	WRITE_VIRTUAL_8BIT_REG(MODRMrm(i), sum);

#if (HOST_CPU_IS_I80386==0)
#endif //#if (HOST_CPU_IS_I80386==0) 

#if (HOST_CPU_IS_I80386==1) 
#endif //#if (HOST_CPU_IS_I80386==1) 
}

	void
BX_CPU_C::NOT_EGw(BX_CPU_C *icpu,bxInstruction_c *i)
{
	Bit16u op1,sum;

	op1 = READ_VIRTUAL_16BIT_REG(MODRMrm(i));

	sum =  ~  op1;

	WRITE_VIRTUAL_16BIT_REG(MODRMrm(i), sum);

#if (HOST_CPU_IS_I80386==0)
#endif //#if (HOST_CPU_IS_I80386==0) 

#if (HOST_CPU_IS_I80386==1) 
#endif //#if (HOST_CPU_IS_I80386==1) 
}

	void
BX_CPU_C::NOT_EGd(BX_CPU_C *icpu,bxInstruction_c *i)
{
	Bit32u op1,sum;

	op1 = READ_VIRTUAL_32BIT_REG(MODRMrm(i));

	sum =  ~  op1;

	WRITE_VIRTUAL_32BIT_REG(MODRMrm(i), sum);

#if (HOST_CPU_IS_I80386==0)
#endif //#if (HOST_CPU_IS_I80386==0) 

#if (HOST_CPU_IS_I80386==1) 
#endif //#if (HOST_CPU_IS_I80386==1) 
}

	void
BX_CPU_C::INC_EEb(BX_CPU_C *icpu,bxInstruction_c *i)
{
	Bit8u op1,sum;

	READ_RMW_VIRTUAL_BYTE(MODRMSeg(i),RMAddr(i),&op1);

	sum =  op1 +  1;

	WRITE_RMW_VIRTUAL_BYTE(sum);

#if (HOST_CPU_IS_I80386==0)
	BX_CPU_CLASS_PTR lf_entrys[BX_LF_INDEX_OSZAP].result_8 = sum;
	BX_CPU_CLASS_PTR lf_entrys[BX_LF_INDEX_OSZAP].instr = BX_INSTR_INC8;
	BX_CPU_CLASS_PTR lf_flags_status = (BX_CPU_CLASS_PTR lf_flags_status & 0x00000f) | BX_LF_MASK_OSZAP;
#endif //#if (HOST_CPU_IS_I80386==0) 

#if (HOST_CPU_IS_I80386==1) 
	Bit32u x86_lf_flags = BX_CPU_CLASS_PTR eflags.x86.eax;
	__asm
	{
		mov eax,x86_lf_flags
		sahf
		INC op1
		lahf
		seto al
		mov x86_lf_flags,eax
	}
	BX_CPU_CLASS_PTR eflags.x86.eax = x86_lf_flags;
#endif //#if (HOST_CPU_IS_I80386==1) 
}

	void
BX_CPU_C::INC_EEw(BX_CPU_C *icpu,bxInstruction_c *i)
{
	Bit16u op1,sum;

	READ_RMW_VIRTUAL_WORD(MODRMSeg(i),RMAddr(i),&op1);

	sum =  op1 +  1;

	WRITE_RMW_VIRTUAL_WORD(sum);

#if (HOST_CPU_IS_I80386==0)
	BX_CPU_CLASS_PTR lf_entrys[BX_LF_INDEX_OSZAP].result_16 = sum;
	BX_CPU_CLASS_PTR lf_entrys[BX_LF_INDEX_OSZAP].instr = BX_INSTR_INC16;
	BX_CPU_CLASS_PTR lf_flags_status = (BX_CPU_CLASS_PTR lf_flags_status & 0x00000f) | BX_LF_MASK_OSZAP;
#endif //#if (HOST_CPU_IS_I80386==0) 

#if (HOST_CPU_IS_I80386==1) 
	Bit32u x86_lf_flags = BX_CPU_CLASS_PTR eflags.x86.eax;
	__asm
	{
		mov eax,x86_lf_flags
		sahf
		INC op1
		lahf
		seto al
		mov x86_lf_flags,eax
	}
	BX_CPU_CLASS_PTR eflags.x86.eax = x86_lf_flags;
#endif //#if (HOST_CPU_IS_I80386==1) 
}

	void
BX_CPU_C::INC_EEd(BX_CPU_C *icpu,bxInstruction_c *i)
{
	Bit32u op1,sum;

	READ_RMW_VIRTUAL_DWORD(MODRMSeg(i),RMAddr(i),&op1);

	sum =  op1 +  1;

	WRITE_RMW_VIRTUAL_DWORD(sum);

#if (HOST_CPU_IS_I80386==0)
	BX_CPU_CLASS_PTR lf_entrys[BX_LF_INDEX_OSZAP].result_32 = sum;
	BX_CPU_CLASS_PTR lf_entrys[BX_LF_INDEX_OSZAP].instr = BX_INSTR_INC32;
	BX_CPU_CLASS_PTR lf_flags_status = (BX_CPU_CLASS_PTR lf_flags_status & 0x00000f) | BX_LF_MASK_OSZAP;
#endif //#if (HOST_CPU_IS_I80386==0) 

#if (HOST_CPU_IS_I80386==1) 
	Bit32u x86_lf_flags = BX_CPU_CLASS_PTR eflags.x86.eax;
	__asm
	{
		mov eax,x86_lf_flags
		sahf
		INC op1
		lahf
		seto al
		mov x86_lf_flags,eax
	}
	BX_CPU_CLASS_PTR eflags.x86.eax = x86_lf_flags;
#endif //#if (HOST_CPU_IS_I80386==1) 
}

	void
BX_CPU_C::DEC_EEb(BX_CPU_C *icpu,bxInstruction_c *i)
{
	Bit8u op1,sum;

	READ_RMW_VIRTUAL_BYTE(MODRMSeg(i),RMAddr(i),&op1);

	sum =  op1 -  1;

	WRITE_RMW_VIRTUAL_BYTE(sum);

#if (HOST_CPU_IS_I80386==0)
	BX_CPU_CLASS_PTR lf_entrys[BX_LF_INDEX_OSZAP].result_8 = sum;
	BX_CPU_CLASS_PTR lf_entrys[BX_LF_INDEX_OSZAP].instr = BX_INSTR_DEC8;
	BX_CPU_CLASS_PTR lf_flags_status = (BX_CPU_CLASS_PTR lf_flags_status & 0x00000f) | BX_LF_MASK_OSZAP;
#endif //#if (HOST_CPU_IS_I80386==0) 

#if (HOST_CPU_IS_I80386==1) 
	Bit32u x86_lf_flags = BX_CPU_CLASS_PTR eflags.x86.eax;
	__asm
	{
		mov eax,x86_lf_flags
		sahf
		DEC op1
		lahf
		seto al
		mov x86_lf_flags,eax
	}
	BX_CPU_CLASS_PTR eflags.x86.eax = x86_lf_flags;
#endif //#if (HOST_CPU_IS_I80386==1) 
}

	void
BX_CPU_C::DEC_EEw(BX_CPU_C *icpu,bxInstruction_c *i)
{
	Bit16u op1,sum;

	READ_RMW_VIRTUAL_WORD(MODRMSeg(i),RMAddr(i),&op1);

	sum =  op1 -  1;

	WRITE_RMW_VIRTUAL_WORD(sum);

#if (HOST_CPU_IS_I80386==0)
	BX_CPU_CLASS_PTR lf_entrys[BX_LF_INDEX_OSZAP].result_16 = sum;
	BX_CPU_CLASS_PTR lf_entrys[BX_LF_INDEX_OSZAP].instr = BX_INSTR_DEC16;
	BX_CPU_CLASS_PTR lf_flags_status = (BX_CPU_CLASS_PTR lf_flags_status & 0x00000f) | BX_LF_MASK_OSZAP;
#endif //#if (HOST_CPU_IS_I80386==0) 

#if (HOST_CPU_IS_I80386==1) 
	Bit32u x86_lf_flags = BX_CPU_CLASS_PTR eflags.x86.eax;
	__asm
	{
		mov eax,x86_lf_flags
		sahf
		DEC op1
		lahf
		seto al
		mov x86_lf_flags,eax
	}
	BX_CPU_CLASS_PTR eflags.x86.eax = x86_lf_flags;
#endif //#if (HOST_CPU_IS_I80386==1) 
}

	void
BX_CPU_C::DEC_EEd(BX_CPU_C *icpu,bxInstruction_c *i)
{
	Bit32u op1,sum;

	READ_RMW_VIRTUAL_DWORD(MODRMSeg(i),RMAddr(i),&op1);

	sum =  op1 -  1;

	WRITE_RMW_VIRTUAL_DWORD(sum);

#if (HOST_CPU_IS_I80386==0)
	BX_CPU_CLASS_PTR lf_entrys[BX_LF_INDEX_OSZAP].result_32 = sum;
	BX_CPU_CLASS_PTR lf_entrys[BX_LF_INDEX_OSZAP].instr = BX_INSTR_DEC32;
	BX_CPU_CLASS_PTR lf_flags_status = (BX_CPU_CLASS_PTR lf_flags_status & 0x00000f) | BX_LF_MASK_OSZAP;
#endif //#if (HOST_CPU_IS_I80386==0) 

#if (HOST_CPU_IS_I80386==1) 
	Bit32u x86_lf_flags = BX_CPU_CLASS_PTR eflags.x86.eax;
	__asm
	{
		mov eax,x86_lf_flags
		sahf
		DEC op1
		lahf
		seto al
		mov x86_lf_flags,eax
	}
	BX_CPU_CLASS_PTR eflags.x86.eax = x86_lf_flags;
#endif //#if (HOST_CPU_IS_I80386==1) 
}

	void
BX_CPU_C::NEG_EEb(BX_CPU_C *icpu,bxInstruction_c *i)
{
	Bit8u op1,sum;

	READ_RMW_VIRTUAL_BYTE(MODRMSeg(i),RMAddr(i),&op1);

	sum =  0- op1;

	WRITE_RMW_VIRTUAL_BYTE(sum);

#if (HOST_CPU_IS_I80386==0)
	BX_CPU_CLASS_PTR lf_entrys[BX_LF_INDEX_OSZAPC].result_8 = sum;
	BX_CPU_CLASS_PTR lf_entrys[BX_LF_INDEX_OSZAPC].instr = BX_INSTR_NEG8;
	BX_CPU_CLASS_PTR lf_flags_status = BX_LF_MASK_OSZAPC;
#endif //#if (HOST_CPU_IS_I80386==0) 

#if (HOST_CPU_IS_I80386==1) 
	Bit32u x86_lf_flags;
	__asm
	{
		NEG op1
		lahf
		seto al
		mov x86_lf_flags,eax
	}
	BX_CPU_CLASS_PTR eflags.x86.eax = x86_lf_flags;
#endif //#if (HOST_CPU_IS_I80386==1) 
}

	void
BX_CPU_C::NEG_EEw(BX_CPU_C *icpu,bxInstruction_c *i)
{
	Bit16u op1,sum;

	READ_RMW_VIRTUAL_WORD(MODRMSeg(i),RMAddr(i),&op1);

	sum =  0- op1;

	WRITE_RMW_VIRTUAL_WORD(sum);

#if (HOST_CPU_IS_I80386==0)
	BX_CPU_CLASS_PTR lf_entrys[BX_LF_INDEX_OSZAPC].result_16 = sum;
	BX_CPU_CLASS_PTR lf_entrys[BX_LF_INDEX_OSZAPC].instr = BX_INSTR_NEG16;
	BX_CPU_CLASS_PTR lf_flags_status = BX_LF_MASK_OSZAPC;
#endif //#if (HOST_CPU_IS_I80386==0) 

#if (HOST_CPU_IS_I80386==1) 
	Bit32u x86_lf_flags;
	__asm
	{
		NEG op1
		lahf
		seto al
		mov x86_lf_flags,eax
	}
	BX_CPU_CLASS_PTR eflags.x86.eax = x86_lf_flags;
#endif //#if (HOST_CPU_IS_I80386==1) 
}

	void
BX_CPU_C::NEG_EEd(BX_CPU_C *icpu,bxInstruction_c *i)
{
	Bit32u op1,sum;

	READ_RMW_VIRTUAL_DWORD(MODRMSeg(i),RMAddr(i),&op1);

	sum =  0- op1;

	WRITE_RMW_VIRTUAL_DWORD(sum);

#if (HOST_CPU_IS_I80386==0)
	BX_CPU_CLASS_PTR lf_entrys[BX_LF_INDEX_OSZAPC].result_32 = sum;
	BX_CPU_CLASS_PTR lf_entrys[BX_LF_INDEX_OSZAPC].instr = BX_INSTR_NEG32;
	BX_CPU_CLASS_PTR lf_flags_status = BX_LF_MASK_OSZAPC;
#endif //#if (HOST_CPU_IS_I80386==0) 

#if (HOST_CPU_IS_I80386==1) 
	Bit32u x86_lf_flags;
	__asm
	{
		NEG op1
		lahf
		seto al
		mov x86_lf_flags,eax
	}
	BX_CPU_CLASS_PTR eflags.x86.eax = x86_lf_flags;
#endif //#if (HOST_CPU_IS_I80386==1) 
}

	void
BX_CPU_C::NOT_EEb(BX_CPU_C *icpu,bxInstruction_c *i)
{
	Bit8u op1,sum;

	READ_RMW_VIRTUAL_BYTE(MODRMSeg(i),RMAddr(i),&op1);

	sum =  ~  op1;

	WRITE_RMW_VIRTUAL_BYTE(sum);

#if (HOST_CPU_IS_I80386==0)
#endif //#if (HOST_CPU_IS_I80386==0) 

#if (HOST_CPU_IS_I80386==1) 
#endif //#if (HOST_CPU_IS_I80386==1) 
}

	void
BX_CPU_C::NOT_EEw(BX_CPU_C *icpu,bxInstruction_c *i)
{
	Bit16u op1,sum;

	READ_RMW_VIRTUAL_WORD(MODRMSeg(i),RMAddr(i),&op1);

	sum =  ~  op1;

	WRITE_RMW_VIRTUAL_WORD(sum);

#if (HOST_CPU_IS_I80386==0)
#endif //#if (HOST_CPU_IS_I80386==0) 

#if (HOST_CPU_IS_I80386==1) 
#endif //#if (HOST_CPU_IS_I80386==1) 
}

	void
BX_CPU_C::NOT_EEd(BX_CPU_C *icpu,bxInstruction_c *i)
{
	Bit32u op1,sum;

	READ_RMW_VIRTUAL_DWORD(MODRMSeg(i),RMAddr(i),&op1);

	sum =  ~  op1;

	WRITE_RMW_VIRTUAL_DWORD(sum);

#if (HOST_CPU_IS_I80386==0)
#endif //#if (HOST_CPU_IS_I80386==0) 

#if (HOST_CPU_IS_I80386==1) 
#endif //#if (HOST_CPU_IS_I80386==1) 
}

	void
BX_CPU_C::ADD_EGbGb(BX_CPU_C *icpu,bxInstruction_c *i)
{
	Bit8u op1, op2, sum;

	op1 = READ_VIRTUAL_8BIT_REG(MODRMrm(i));

	op2 = READ_VIRTUAL_8BIT_REG(MODRMnnn(i));

	sum = op1 + op2;

	WRITE_VIRTUAL_8BIT_REG(MODRMrm(i), sum);

#if (HOST_CPU_IS_I80386==0)
	SET_FLAGS_OSZAPC_8(op1,op2,sum,BX_INSTR_ADD8);
#endif //#if (HOST_CPU_IS_I80386==0)
#if (HOST_CPU_IS_I80386==1) 
	Bit32u x86_lf_flags = BX_CPU_CLASS_PTR eflags.x86.eax;
	__asm
	{
		mov dl,op2
		ADD op1,dl
		lahf
		seto al
		mov x86_lf_flags,eax
	}
	BX_CPU_CLASS_PTR eflags.x86.eax = x86_lf_flags;
#endif //#if (HOST_CPU_IS_I80386==1)

}

	void
BX_CPU_C::ADD_EGwGw(BX_CPU_C *icpu,bxInstruction_c *i)
{
	Bit16u op1, op2, sum;

	op1 = READ_VIRTUAL_16BIT_REG(MODRMrm(i));

	op2 = READ_VIRTUAL_16BIT_REG(MODRMnnn(i));

	sum = op1 + op2;

	WRITE_VIRTUAL_16BIT_REG(MODRMrm(i), sum);

#if (HOST_CPU_IS_I80386==0)
	SET_FLAGS_OSZAPC_16(op1,op2,sum,BX_INSTR_ADD16);
#endif //#if (HOST_CPU_IS_I80386==0)
#if (HOST_CPU_IS_I80386==1) 
	Bit32u x86_lf_flags = BX_CPU_CLASS_PTR eflags.x86.eax;
	__asm
	{
		mov dx,op2
		ADD op1,dx
		lahf
		seto al
		mov x86_lf_flags,eax
	}
	BX_CPU_CLASS_PTR eflags.x86.eax = x86_lf_flags;
#endif //#if (HOST_CPU_IS_I80386==1)

}

	void
BX_CPU_C::ADD_EGdGd(BX_CPU_C *icpu,bxInstruction_c *i)
{
	Bit32u op1, op2, sum;

	op1 = READ_VIRTUAL_32BIT_REG(MODRMrm(i));

	op2 = READ_VIRTUAL_32BIT_REG(MODRMnnn(i));

	sum = op1 + op2;

	WRITE_VIRTUAL_32BIT_REG(MODRMrm(i), sum);

#if (HOST_CPU_IS_I80386==0)
	SET_FLAGS_OSZAPC_32(op1,op2,sum,BX_INSTR_ADD32);
#endif //#if (HOST_CPU_IS_I80386==0)
#if (HOST_CPU_IS_I80386==1) 
	Bit32u x86_lf_flags = BX_CPU_CLASS_PTR eflags.x86.eax;
	__asm
	{
		mov edx,op2
		ADD op1,edx
		lahf
		seto al
		mov x86_lf_flags,eax
	}
	BX_CPU_CLASS_PTR eflags.x86.eax = x86_lf_flags;
#endif //#if (HOST_CPU_IS_I80386==1)

}

	void
BX_CPU_C::ADD_GbEGb(BX_CPU_C *icpu,bxInstruction_c *i)
{
	Bit8u op1, op2, sum;

	op1 = READ_VIRTUAL_8BIT_REG(MODRMnnn(i));

	op2 = READ_VIRTUAL_8BIT_REG(MODRMrm(i));

	sum = op1 + op2;

	WRITE_VIRTUAL_8BIT_REG(MODRMnnn(i),sum);

#if (HOST_CPU_IS_I80386==0)
	SET_FLAGS_OSZAPC_8(op1,op2,sum,BX_INSTR_ADD8);
#endif //#if (HOST_CPU_IS_I80386==0)
#if (HOST_CPU_IS_I80386==1) 
	Bit32u x86_lf_flags = BX_CPU_CLASS_PTR eflags.x86.eax;
	__asm
	{
		mov dl,op2
		ADD op1,dl
		lahf
		seto al
		mov x86_lf_flags,eax
	}
	BX_CPU_CLASS_PTR eflags.x86.eax = x86_lf_flags;
#endif //#if (HOST_CPU_IS_I80386==1)

}

	void
BX_CPU_C::ADD_GwEGw(BX_CPU_C *icpu,bxInstruction_c *i)
{
	Bit16u op1, op2, sum;

	op1 = READ_VIRTUAL_16BIT_REG(MODRMnnn(i));

	op2 = READ_VIRTUAL_16BIT_REG(MODRMrm(i));

	sum = op1 + op2;

	WRITE_VIRTUAL_16BIT_REG(MODRMnnn(i),sum);

#if (HOST_CPU_IS_I80386==0)
	SET_FLAGS_OSZAPC_16(op1,op2,sum,BX_INSTR_ADD16);
#endif //#if (HOST_CPU_IS_I80386==0)
#if (HOST_CPU_IS_I80386==1) 
	Bit32u x86_lf_flags = BX_CPU_CLASS_PTR eflags.x86.eax;
	__asm
	{
		mov dx,op2
		ADD op1,dx
		lahf
		seto al
		mov x86_lf_flags,eax
	}
	BX_CPU_CLASS_PTR eflags.x86.eax = x86_lf_flags;
#endif //#if (HOST_CPU_IS_I80386==1)

}

	void
BX_CPU_C::ADD_GdEGd(BX_CPU_C *icpu,bxInstruction_c *i)
{
	Bit32u op1, op2, sum;

	op1 = READ_VIRTUAL_32BIT_REG(MODRMnnn(i));

	op2 = READ_VIRTUAL_32BIT_REG(MODRMrm(i));

	sum = op1 + op2;

	WRITE_VIRTUAL_32BIT_REG(MODRMnnn(i),sum);

#if (HOST_CPU_IS_I80386==0)
	SET_FLAGS_OSZAPC_32(op1,op2,sum,BX_INSTR_ADD32);
#endif //#if (HOST_CPU_IS_I80386==0)
#if (HOST_CPU_IS_I80386==1) 
	Bit32u x86_lf_flags = BX_CPU_CLASS_PTR eflags.x86.eax;
	__asm
	{
		mov edx,op2
		ADD op1,edx
		lahf
		seto al
		mov x86_lf_flags,eax
	}
	BX_CPU_CLASS_PTR eflags.x86.eax = x86_lf_flags;
#endif //#if (HOST_CPU_IS_I80386==1)

}

	void
BX_CPU_C::ADD_EGbIb(BX_CPU_C *icpu,bxInstruction_c *i)
{
	Bit8u op1, op2, sum;

	op1 = READ_VIRTUAL_8BIT_REG(MODRMrm(i));

	op2 = IMMEDIATEIb(i);

	sum = op1 + op2;

	WRITE_VIRTUAL_8BIT_REG(MODRMrm(i),sum);

#if (HOST_CPU_IS_I80386==0)
	SET_FLAGS_OSZAPC_8(op1,op2,sum,BX_INSTR_ADD8);
#endif //#if (HOST_CPU_IS_I80386==0)
#if (HOST_CPU_IS_I80386==1) 
	Bit32u x86_lf_flags = BX_CPU_CLASS_PTR eflags.x86.eax;
	__asm
	{
		mov dl,op2
		ADD op1,dl
		lahf
		seto al
		mov x86_lf_flags,eax
	}
	BX_CPU_CLASS_PTR eflags.x86.eax = x86_lf_flags;
#endif //#if (HOST_CPU_IS_I80386==1)

}

	void
BX_CPU_C::ADD_EGwIw(BX_CPU_C *icpu,bxInstruction_c *i)
{
	Bit16u op1, op2, sum;

	op1 = READ_VIRTUAL_16BIT_REG(MODRMrm(i));

	op2 = IMMEDIATEIw(i);

	sum = op1 + op2;

	WRITE_VIRTUAL_16BIT_REG(MODRMrm(i),sum);

#if (HOST_CPU_IS_I80386==0)
	SET_FLAGS_OSZAPC_16(op1,op2,sum,BX_INSTR_ADD16);
#endif //#if (HOST_CPU_IS_I80386==0)
#if (HOST_CPU_IS_I80386==1) 
	Bit32u x86_lf_flags = BX_CPU_CLASS_PTR eflags.x86.eax;
	__asm
	{
		mov dx,op2
		ADD op1,dx
		lahf
		seto al
		mov x86_lf_flags,eax
	}
	BX_CPU_CLASS_PTR eflags.x86.eax = x86_lf_flags;
#endif //#if (HOST_CPU_IS_I80386==1)

}

	void
BX_CPU_C::ADD_EGdId(BX_CPU_C *icpu,bxInstruction_c *i)
{
	Bit32u op1, op2, sum;

	op1 = READ_VIRTUAL_32BIT_REG(MODRMrm(i));

	op2 = IMMEDIATEId(i);

	sum = op1 + op2;

	WRITE_VIRTUAL_32BIT_REG(MODRMrm(i),sum);

#if (HOST_CPU_IS_I80386==0)
	SET_FLAGS_OSZAPC_32(op1,op2,sum,BX_INSTR_ADD32);
#endif //#if (HOST_CPU_IS_I80386==0)
#if (HOST_CPU_IS_I80386==1) 
	Bit32u x86_lf_flags = BX_CPU_CLASS_PTR eflags.x86.eax;
	__asm
	{
		mov edx,op2
		ADD op1,edx
		lahf
		seto al
		mov x86_lf_flags,eax
	}
	BX_CPU_CLASS_PTR eflags.x86.eax = x86_lf_flags;
#endif //#if (HOST_CPU_IS_I80386==1)

}

	void
BX_CPU_C::ADD_ALIb(BX_CPU_C *icpu,bxInstruction_c *i)
{
	Bit8u op1, op2, sum;

	op1 = READ_VIRTUAL_8BIT_REG(0);

	op2 = IMMEDIATEIb(i);

	sum = op1 + op2;

	WRITE_VIRTUAL_8BIT_REG(0,sum);

#if (HOST_CPU_IS_I80386==0)
	SET_FLAGS_OSZAPC_8(op1,op2,sum,BX_INSTR_ADD8);
#endif //#if (HOST_CPU_IS_I80386==0)
#if (HOST_CPU_IS_I80386==1) 
	Bit32u x86_lf_flags = BX_CPU_CLASS_PTR eflags.x86.eax;
	__asm
	{
		mov dl,op2
		ADD op1,dl
		lahf
		seto al
		mov x86_lf_flags,eax
	}
	BX_CPU_CLASS_PTR eflags.x86.eax = x86_lf_flags;
#endif //#if (HOST_CPU_IS_I80386==1)

}

	void
BX_CPU_C::ADD_AXIw(BX_CPU_C *icpu,bxInstruction_c *i)
{
	Bit16u op1, op2, sum;

	op1 = READ_VIRTUAL_16BIT_REG(0);

	op2 = IMMEDIATEIw(i);

	sum = op1 + op2;

	WRITE_VIRTUAL_16BIT_REG(0,sum);

#if (HOST_CPU_IS_I80386==0)
	SET_FLAGS_OSZAPC_16(op1,op2,sum,BX_INSTR_ADD16);
#endif //#if (HOST_CPU_IS_I80386==0)
#if (HOST_CPU_IS_I80386==1) 
	Bit32u x86_lf_flags = BX_CPU_CLASS_PTR eflags.x86.eax;
	__asm
	{
		mov dx,op2
		ADD op1,dx
		lahf
		seto al
		mov x86_lf_flags,eax
	}
	BX_CPU_CLASS_PTR eflags.x86.eax = x86_lf_flags;
#endif //#if (HOST_CPU_IS_I80386==1)

}

	void
BX_CPU_C::ADD_EAXId(BX_CPU_C *icpu,bxInstruction_c *i)
{
	Bit32u op1, op2, sum;

	op1 = READ_VIRTUAL_32BIT_REG(0);

	op2 = IMMEDIATEId(i);

	sum = op1 + op2;

	WRITE_VIRTUAL_32BIT_REG(0,sum);

#if (HOST_CPU_IS_I80386==0)
	SET_FLAGS_OSZAPC_32(op1,op2,sum,BX_INSTR_ADD32);
#endif //#if (HOST_CPU_IS_I80386==0)
#if (HOST_CPU_IS_I80386==1) 
	Bit32u x86_lf_flags = BX_CPU_CLASS_PTR eflags.x86.eax;
	__asm
	{
		mov edx,op2
		ADD op1,edx
		lahf
		seto al
		mov x86_lf_flags,eax
	}
	BX_CPU_CLASS_PTR eflags.x86.eax = x86_lf_flags;
#endif //#if (HOST_CPU_IS_I80386==1)

}

	void
BX_CPU_C::ADD_EEbGb(BX_CPU_C *icpu,bxInstruction_c *i)
{
	Bit8u op1, op2, sum;

	READ_RMW_VIRTUAL_BYTE(MODRMSeg(i),RMAddr(i),&op1);

	op2 = READ_VIRTUAL_8BIT_REG(MODRMnnn(i));

	sum = op1 + op2;

	WRITE_RMW_VIRTUAL_BYTE(sum);

#if (HOST_CPU_IS_I80386==0)
	SET_FLAGS_OSZAPC_8(op1,op2,sum,BX_INSTR_ADD8);
#endif //#if (HOST_CPU_IS_I80386==0)
#if (HOST_CPU_IS_I80386==1) 
	Bit32u x86_lf_flags = BX_CPU_CLASS_PTR eflags.x86.eax;
	__asm
	{
		mov dl,op2
		ADD op1,dl
		lahf
		seto al
		mov x86_lf_flags,eax
	}
	BX_CPU_CLASS_PTR eflags.x86.eax = x86_lf_flags;
#endif //#if (HOST_CPU_IS_I80386==1)

}

	void
BX_CPU_C::ADD_EEwGw(BX_CPU_C *icpu,bxInstruction_c *i)
{
	Bit16u op1, op2, sum;

	READ_RMW_VIRTUAL_WORD(MODRMSeg(i),RMAddr(i),&op1);

	op2 = READ_VIRTUAL_16BIT_REG(MODRMnnn(i));

	sum = op1 + op2;

	WRITE_RMW_VIRTUAL_WORD(sum);

#if (HOST_CPU_IS_I80386==0)
	SET_FLAGS_OSZAPC_16(op1,op2,sum,BX_INSTR_ADD16);
#endif //#if (HOST_CPU_IS_I80386==0)
#if (HOST_CPU_IS_I80386==1) 
	Bit32u x86_lf_flags = BX_CPU_CLASS_PTR eflags.x86.eax;
	__asm
	{
		mov dx,op2
		ADD op1,dx
		lahf
		seto al
		mov x86_lf_flags,eax
	}
	BX_CPU_CLASS_PTR eflags.x86.eax = x86_lf_flags;
#endif //#if (HOST_CPU_IS_I80386==1)

}

	void
BX_CPU_C::ADD_EEdGd(BX_CPU_C *icpu,bxInstruction_c *i)
{
	Bit32u op1, op2, sum;

	READ_RMW_VIRTUAL_DWORD(MODRMSeg(i),RMAddr(i),&op1);

	op2 = READ_VIRTUAL_32BIT_REG(MODRMnnn(i));

	sum = op1 + op2;

	WRITE_RMW_VIRTUAL_DWORD(sum);

#if (HOST_CPU_IS_I80386==0)
	SET_FLAGS_OSZAPC_32(op1,op2,sum,BX_INSTR_ADD32);
#endif //#if (HOST_CPU_IS_I80386==0)
#if (HOST_CPU_IS_I80386==1) 
	Bit32u x86_lf_flags = BX_CPU_CLASS_PTR eflags.x86.eax;
	__asm
	{
		mov edx,op2
		ADD op1,edx
		lahf
		seto al
		mov x86_lf_flags,eax
	}
	BX_CPU_CLASS_PTR eflags.x86.eax = x86_lf_flags;
#endif //#if (HOST_CPU_IS_I80386==1)

}

	void
BX_CPU_C::ADD_GbEEb(BX_CPU_C *icpu,bxInstruction_c *i)
{
	Bit8u op1, op2, sum;

	op1 = READ_VIRTUAL_8BIT_REG(MODRMnnn(i));

	READ_VIRTUAL_BYTE(MODRMSeg(i),RMAddr(i),&op2);

	sum = op1 + op2;

	WRITE_VIRTUAL_8BIT_REG(MODRMnnn(i),sum);

#if (HOST_CPU_IS_I80386==0)
	SET_FLAGS_OSZAPC_8(op1,op2,sum,BX_INSTR_ADD8);
#endif //#if (HOST_CPU_IS_I80386==0)
#if (HOST_CPU_IS_I80386==1) 
	Bit32u x86_lf_flags = BX_CPU_CLASS_PTR eflags.x86.eax;
	__asm
	{
		mov dl,op2
		ADD op1,dl
		lahf
		seto al
		mov x86_lf_flags,eax
	}
	BX_CPU_CLASS_PTR eflags.x86.eax = x86_lf_flags;
#endif //#if (HOST_CPU_IS_I80386==1)

}

	void
BX_CPU_C::ADD_GwEEw(BX_CPU_C *icpu,bxInstruction_c *i)
{
	Bit16u op1, op2, sum;

	op1 = READ_VIRTUAL_16BIT_REG(MODRMnnn(i));

	READ_VIRTUAL_WORD(MODRMSeg(i),RMAddr(i),&op2);

	sum = op1 + op2;

	WRITE_VIRTUAL_16BIT_REG(MODRMnnn(i),sum);

#if (HOST_CPU_IS_I80386==0)
	SET_FLAGS_OSZAPC_16(op1,op2,sum,BX_INSTR_ADD16);
#endif //#if (HOST_CPU_IS_I80386==0)
#if (HOST_CPU_IS_I80386==1) 
	Bit32u x86_lf_flags = BX_CPU_CLASS_PTR eflags.x86.eax;
	__asm
	{
		mov dx,op2
		ADD op1,dx
		lahf
		seto al
		mov x86_lf_flags,eax
	}
	BX_CPU_CLASS_PTR eflags.x86.eax = x86_lf_flags;
#endif //#if (HOST_CPU_IS_I80386==1)

}

	void
BX_CPU_C::ADD_GdEEd(BX_CPU_C *icpu,bxInstruction_c *i)
{
	Bit32u op1, op2, sum;

	op1 = READ_VIRTUAL_32BIT_REG(MODRMnnn(i));

	READ_VIRTUAL_DWORD(MODRMSeg(i),RMAddr(i),&op2);

	sum = op1 + op2;

	WRITE_VIRTUAL_32BIT_REG(MODRMnnn(i),sum);

#if (HOST_CPU_IS_I80386==0)
	SET_FLAGS_OSZAPC_32(op1,op2,sum,BX_INSTR_ADD32);
#endif //#if (HOST_CPU_IS_I80386==0)
#if (HOST_CPU_IS_I80386==1) 
	Bit32u x86_lf_flags = BX_CPU_CLASS_PTR eflags.x86.eax;
	__asm
	{
		mov edx,op2
		ADD op1,edx
		lahf
		seto al
		mov x86_lf_flags,eax
	}
	BX_CPU_CLASS_PTR eflags.x86.eax = x86_lf_flags;
#endif //#if (HOST_CPU_IS_I80386==1)

}

	void
BX_CPU_C::ADD_EEbIb(BX_CPU_C *icpu,bxInstruction_c *i)
{
	Bit8u op1, op2, sum;

	READ_RMW_VIRTUAL_BYTE(MODRMSeg(i),RMAddr(i),&op1);

	op2 = IMMEDIATEIb(i);

	sum = op1 + op2;

	WRITE_RMW_VIRTUAL_BYTE(sum);

#if (HOST_CPU_IS_I80386==0)
	SET_FLAGS_OSZAPC_8(op1,op2,sum,BX_INSTR_ADD8);
#endif //#if (HOST_CPU_IS_I80386==0)
#if (HOST_CPU_IS_I80386==1) 
	Bit32u x86_lf_flags = BX_CPU_CLASS_PTR eflags.x86.eax;
	__asm
	{
		mov dl,op2
		ADD op1,dl
		lahf
		seto al
		mov x86_lf_flags,eax
	}
	BX_CPU_CLASS_PTR eflags.x86.eax = x86_lf_flags;
#endif //#if (HOST_CPU_IS_I80386==1)

}

	void
BX_CPU_C::ADD_EEwIw(BX_CPU_C *icpu,bxInstruction_c *i)
{
	Bit16u op1, op2, sum;

	READ_RMW_VIRTUAL_WORD(MODRMSeg(i),RMAddr(i),&op1);

	op2 = IMMEDIATEIw(i);

	sum = op1 + op2;

	WRITE_RMW_VIRTUAL_WORD(sum);

#if (HOST_CPU_IS_I80386==0)
	SET_FLAGS_OSZAPC_16(op1,op2,sum,BX_INSTR_ADD16);
#endif //#if (HOST_CPU_IS_I80386==0)
#if (HOST_CPU_IS_I80386==1) 
	Bit32u x86_lf_flags = BX_CPU_CLASS_PTR eflags.x86.eax;
	__asm
	{
		mov dx,op2
		ADD op1,dx
		lahf
		seto al
		mov x86_lf_flags,eax
	}
	BX_CPU_CLASS_PTR eflags.x86.eax = x86_lf_flags;
#endif //#if (HOST_CPU_IS_I80386==1)

}

	void
BX_CPU_C::ADD_EEdId(BX_CPU_C *icpu,bxInstruction_c *i)
{
	Bit32u op1, op2, sum;

	READ_RMW_VIRTUAL_DWORD(MODRMSeg(i),RMAddr(i),&op1);

	op2 = IMMEDIATEId(i);

	sum = op1 + op2;

	WRITE_RMW_VIRTUAL_DWORD(sum);

#if (HOST_CPU_IS_I80386==0)
	SET_FLAGS_OSZAPC_32(op1,op2,sum,BX_INSTR_ADD32);
#endif //#if (HOST_CPU_IS_I80386==0)
#if (HOST_CPU_IS_I80386==1) 
	Bit32u x86_lf_flags = BX_CPU_CLASS_PTR eflags.x86.eax;
	__asm
	{
		mov edx,op2
		ADD op1,edx
		lahf
		seto al
		mov x86_lf_flags,eax
	}
	BX_CPU_CLASS_PTR eflags.x86.eax = x86_lf_flags;
#endif //#if (HOST_CPU_IS_I80386==1)

}

	void
BX_CPU_C::SUB_EGbGb(BX_CPU_C *icpu,bxInstruction_c *i)
{
	Bit8u op1, op2, sum;

	op1 = READ_VIRTUAL_8BIT_REG(MODRMrm(i));

	op2 = READ_VIRTUAL_8BIT_REG(MODRMnnn(i));

	sum = op1 - op2;

	WRITE_VIRTUAL_8BIT_REG(MODRMrm(i), sum);

#if (HOST_CPU_IS_I80386==0)
	SET_FLAGS_OSZAPC_8(op1,op2,sum,BX_INSTR_SUB8);
#endif //#if (HOST_CPU_IS_I80386==0)
#if (HOST_CPU_IS_I80386==1) 
	Bit32u x86_lf_flags = BX_CPU_CLASS_PTR eflags.x86.eax;
	__asm
	{
		mov dl,op2
		SUB op1,dl
		lahf
		seto al
		mov x86_lf_flags,eax
	}
	BX_CPU_CLASS_PTR eflags.x86.eax = x86_lf_flags;
#endif //#if (HOST_CPU_IS_I80386==1)

}

	void
BX_CPU_C::SUB_EGwGw(BX_CPU_C *icpu,bxInstruction_c *i)
{
	Bit16u op1, op2, sum;

	op1 = READ_VIRTUAL_16BIT_REG(MODRMrm(i));

	op2 = READ_VIRTUAL_16BIT_REG(MODRMnnn(i));

	sum = op1 - op2;

	WRITE_VIRTUAL_16BIT_REG(MODRMrm(i), sum);

#if (HOST_CPU_IS_I80386==0)
	SET_FLAGS_OSZAPC_16(op1,op2,sum,BX_INSTR_SUB16);
#endif //#if (HOST_CPU_IS_I80386==0)
#if (HOST_CPU_IS_I80386==1) 
	Bit32u x86_lf_flags = BX_CPU_CLASS_PTR eflags.x86.eax;
	__asm
	{
		mov dx,op2
		SUB op1,dx
		lahf
		seto al
		mov x86_lf_flags,eax
	}
	BX_CPU_CLASS_PTR eflags.x86.eax = x86_lf_flags;
#endif //#if (HOST_CPU_IS_I80386==1)

}

	void
BX_CPU_C::SUB_EGdGd(BX_CPU_C *icpu,bxInstruction_c *i)
{
	Bit32u op1, op2, sum;

	op1 = READ_VIRTUAL_32BIT_REG(MODRMrm(i));

	op2 = READ_VIRTUAL_32BIT_REG(MODRMnnn(i));

	sum = op1 - op2;

	WRITE_VIRTUAL_32BIT_REG(MODRMrm(i), sum);

#if (HOST_CPU_IS_I80386==0)
	SET_FLAGS_OSZAPC_32(op1,op2,sum,BX_INSTR_SUB32);
#endif //#if (HOST_CPU_IS_I80386==0)
#if (HOST_CPU_IS_I80386==1) 
	Bit32u x86_lf_flags = BX_CPU_CLASS_PTR eflags.x86.eax;
	__asm
	{
		mov edx,op2
		SUB op1,edx
		lahf
		seto al
		mov x86_lf_flags,eax
	}
	BX_CPU_CLASS_PTR eflags.x86.eax = x86_lf_flags;
#endif //#if (HOST_CPU_IS_I80386==1)

}

	void
BX_CPU_C::SUB_GbEGb(BX_CPU_C *icpu,bxInstruction_c *i)
{
	Bit8u op1, op2, sum;

	op1 = READ_VIRTUAL_8BIT_REG(MODRMnnn(i));

	op2 = READ_VIRTUAL_8BIT_REG(MODRMrm(i));

	sum = op1 - op2;

	WRITE_VIRTUAL_8BIT_REG(MODRMnnn(i),sum);

#if (HOST_CPU_IS_I80386==0)
	SET_FLAGS_OSZAPC_8(op1,op2,sum,BX_INSTR_SUB8);
#endif //#if (HOST_CPU_IS_I80386==0)
#if (HOST_CPU_IS_I80386==1) 
	Bit32u x86_lf_flags = BX_CPU_CLASS_PTR eflags.x86.eax;
	__asm
	{
		mov dl,op2
		SUB op1,dl
		lahf
		seto al
		mov x86_lf_flags,eax
	}
	BX_CPU_CLASS_PTR eflags.x86.eax = x86_lf_flags;
#endif //#if (HOST_CPU_IS_I80386==1)

}

	void
BX_CPU_C::SUB_GwEGw(BX_CPU_C *icpu,bxInstruction_c *i)
{
	Bit16u op1, op2, sum;

	op1 = READ_VIRTUAL_16BIT_REG(MODRMnnn(i));

	op2 = READ_VIRTUAL_16BIT_REG(MODRMrm(i));

	sum = op1 - op2;

	WRITE_VIRTUAL_16BIT_REG(MODRMnnn(i),sum);

#if (HOST_CPU_IS_I80386==0)
	SET_FLAGS_OSZAPC_16(op1,op2,sum,BX_INSTR_SUB16);
#endif //#if (HOST_CPU_IS_I80386==0)
#if (HOST_CPU_IS_I80386==1) 
	Bit32u x86_lf_flags = BX_CPU_CLASS_PTR eflags.x86.eax;
	__asm
	{
		mov dx,op2
		SUB op1,dx
		lahf
		seto al
		mov x86_lf_flags,eax
	}
	BX_CPU_CLASS_PTR eflags.x86.eax = x86_lf_flags;
#endif //#if (HOST_CPU_IS_I80386==1)

}

	void
BX_CPU_C::SUB_GdEGd(BX_CPU_C *icpu,bxInstruction_c *i)
{
	Bit32u op1, op2, sum;

	op1 = READ_VIRTUAL_32BIT_REG(MODRMnnn(i));

	op2 = READ_VIRTUAL_32BIT_REG(MODRMrm(i));

	sum = op1 - op2;

	WRITE_VIRTUAL_32BIT_REG(MODRMnnn(i),sum);

#if (HOST_CPU_IS_I80386==0)
	SET_FLAGS_OSZAPC_32(op1,op2,sum,BX_INSTR_SUB32);
#endif //#if (HOST_CPU_IS_I80386==0)
#if (HOST_CPU_IS_I80386==1) 
	Bit32u x86_lf_flags = BX_CPU_CLASS_PTR eflags.x86.eax;
	__asm
	{
		mov edx,op2
		SUB op1,edx
		lahf
		seto al
		mov x86_lf_flags,eax
	}
	BX_CPU_CLASS_PTR eflags.x86.eax = x86_lf_flags;
#endif //#if (HOST_CPU_IS_I80386==1)

}

	void
BX_CPU_C::SUB_EGbIb(BX_CPU_C *icpu,bxInstruction_c *i)
{
	Bit8u op1, op2, sum;

	op1 = READ_VIRTUAL_8BIT_REG(MODRMrm(i));

	op2 = IMMEDIATEIb(i);

	sum = op1 - op2;

	WRITE_VIRTUAL_8BIT_REG(MODRMrm(i),sum);

#if (HOST_CPU_IS_I80386==0)
	SET_FLAGS_OSZAPC_8(op1,op2,sum,BX_INSTR_SUB8);
#endif //#if (HOST_CPU_IS_I80386==0)
#if (HOST_CPU_IS_I80386==1) 
	Bit32u x86_lf_flags = BX_CPU_CLASS_PTR eflags.x86.eax;
	__asm
	{
		mov dl,op2
		SUB op1,dl
		lahf
		seto al
		mov x86_lf_flags,eax
	}
	BX_CPU_CLASS_PTR eflags.x86.eax = x86_lf_flags;
#endif //#if (HOST_CPU_IS_I80386==1)

}

	void
BX_CPU_C::SUB_EGwIw(BX_CPU_C *icpu,bxInstruction_c *i)
{
	Bit16u op1, op2, sum;

	op1 = READ_VIRTUAL_16BIT_REG(MODRMrm(i));

	op2 = IMMEDIATEIw(i);

	sum = op1 - op2;

	WRITE_VIRTUAL_16BIT_REG(MODRMrm(i),sum);

#if (HOST_CPU_IS_I80386==0)
	SET_FLAGS_OSZAPC_16(op1,op2,sum,BX_INSTR_SUB16);
#endif //#if (HOST_CPU_IS_I80386==0)
#if (HOST_CPU_IS_I80386==1) 
	Bit32u x86_lf_flags = BX_CPU_CLASS_PTR eflags.x86.eax;
	__asm
	{
		mov dx,op2
		SUB op1,dx
		lahf
		seto al
		mov x86_lf_flags,eax
	}
	BX_CPU_CLASS_PTR eflags.x86.eax = x86_lf_flags;
#endif //#if (HOST_CPU_IS_I80386==1)

}

	void
BX_CPU_C::SUB_EGdId(BX_CPU_C *icpu,bxInstruction_c *i)
{
	Bit32u op1, op2, sum;

	op1 = READ_VIRTUAL_32BIT_REG(MODRMrm(i));

	op2 = IMMEDIATEId(i);

	sum = op1 - op2;

	WRITE_VIRTUAL_32BIT_REG(MODRMrm(i),sum);

#if (HOST_CPU_IS_I80386==0)
	SET_FLAGS_OSZAPC_32(op1,op2,sum,BX_INSTR_SUB32);
#endif //#if (HOST_CPU_IS_I80386==0)
#if (HOST_CPU_IS_I80386==1) 
	Bit32u x86_lf_flags = BX_CPU_CLASS_PTR eflags.x86.eax;
	__asm
	{
		mov edx,op2
		SUB op1,edx
		lahf
		seto al
		mov x86_lf_flags,eax
	}
	BX_CPU_CLASS_PTR eflags.x86.eax = x86_lf_flags;
#endif //#if (HOST_CPU_IS_I80386==1)

}

	void
BX_CPU_C::SUB_ALIb(BX_CPU_C *icpu,bxInstruction_c *i)
{
	Bit8u op1, op2, sum;

	op1 = READ_VIRTUAL_8BIT_REG(0);

	op2 = IMMEDIATEIb(i);

	sum = op1 - op2;

	WRITE_VIRTUAL_8BIT_REG(0,sum);

#if (HOST_CPU_IS_I80386==0)
	SET_FLAGS_OSZAPC_8(op1,op2,sum,BX_INSTR_SUB8);
#endif //#if (HOST_CPU_IS_I80386==0)
#if (HOST_CPU_IS_I80386==1) 
	Bit32u x86_lf_flags = BX_CPU_CLASS_PTR eflags.x86.eax;
	__asm
	{
		mov dl,op2
		SUB op1,dl
		lahf
		seto al
		mov x86_lf_flags,eax
	}
	BX_CPU_CLASS_PTR eflags.x86.eax = x86_lf_flags;
#endif //#if (HOST_CPU_IS_I80386==1)

}

	void
BX_CPU_C::SUB_AXIw(BX_CPU_C *icpu,bxInstruction_c *i)
{
	Bit16u op1, op2, sum;

	op1 = READ_VIRTUAL_16BIT_REG(0);

	op2 = IMMEDIATEIw(i);

	sum = op1 - op2;

	WRITE_VIRTUAL_16BIT_REG(0,sum);

#if (HOST_CPU_IS_I80386==0)
	SET_FLAGS_OSZAPC_16(op1,op2,sum,BX_INSTR_SUB16);
#endif //#if (HOST_CPU_IS_I80386==0)
#if (HOST_CPU_IS_I80386==1) 
	Bit32u x86_lf_flags = BX_CPU_CLASS_PTR eflags.x86.eax;
	__asm
	{
		mov dx,op2
		SUB op1,dx
		lahf
		seto al
		mov x86_lf_flags,eax
	}
	BX_CPU_CLASS_PTR eflags.x86.eax = x86_lf_flags;
#endif //#if (HOST_CPU_IS_I80386==1)

}

	void
BX_CPU_C::SUB_EAXId(BX_CPU_C *icpu,bxInstruction_c *i)
{
	Bit32u op1, op2, sum;

	op1 = READ_VIRTUAL_32BIT_REG(0);

	op2 = IMMEDIATEId(i);

	sum = op1 - op2;

	WRITE_VIRTUAL_32BIT_REG(0,sum);

#if (HOST_CPU_IS_I80386==0)
	SET_FLAGS_OSZAPC_32(op1,op2,sum,BX_INSTR_SUB32);
#endif //#if (HOST_CPU_IS_I80386==0)
#if (HOST_CPU_IS_I80386==1) 
	Bit32u x86_lf_flags = BX_CPU_CLASS_PTR eflags.x86.eax;
	__asm
	{
		mov edx,op2
		SUB op1,edx
		lahf
		seto al
		mov x86_lf_flags,eax
	}
	BX_CPU_CLASS_PTR eflags.x86.eax = x86_lf_flags;
#endif //#if (HOST_CPU_IS_I80386==1)

}

	void
BX_CPU_C::SUB_EEbGb(BX_CPU_C *icpu,bxInstruction_c *i)
{
	Bit8u op1, op2, sum;

	READ_RMW_VIRTUAL_BYTE(MODRMSeg(i),RMAddr(i),&op1);

	op2 = READ_VIRTUAL_8BIT_REG(MODRMnnn(i));

	sum = op1 - op2;

	WRITE_RMW_VIRTUAL_BYTE(sum);

#if (HOST_CPU_IS_I80386==0)
	SET_FLAGS_OSZAPC_8(op1,op2,sum,BX_INSTR_SUB8);
#endif //#if (HOST_CPU_IS_I80386==0)
#if (HOST_CPU_IS_I80386==1) 
	Bit32u x86_lf_flags = BX_CPU_CLASS_PTR eflags.x86.eax;
	__asm
	{
		mov dl,op2
		SUB op1,dl
		lahf
		seto al
		mov x86_lf_flags,eax
	}
	BX_CPU_CLASS_PTR eflags.x86.eax = x86_lf_flags;
#endif //#if (HOST_CPU_IS_I80386==1)

}

	void
BX_CPU_C::SUB_EEwGw(BX_CPU_C *icpu,bxInstruction_c *i)
{
	Bit16u op1, op2, sum;

	READ_RMW_VIRTUAL_WORD(MODRMSeg(i),RMAddr(i),&op1);

	op2 = READ_VIRTUAL_16BIT_REG(MODRMnnn(i));

	sum = op1 - op2;

	WRITE_RMW_VIRTUAL_WORD(sum);

#if (HOST_CPU_IS_I80386==0)
	SET_FLAGS_OSZAPC_16(op1,op2,sum,BX_INSTR_SUB16);
#endif //#if (HOST_CPU_IS_I80386==0)
#if (HOST_CPU_IS_I80386==1) 
	Bit32u x86_lf_flags = BX_CPU_CLASS_PTR eflags.x86.eax;
	__asm
	{
		mov dx,op2
		SUB op1,dx
		lahf
		seto al
		mov x86_lf_flags,eax
	}
	BX_CPU_CLASS_PTR eflags.x86.eax = x86_lf_flags;
#endif //#if (HOST_CPU_IS_I80386==1)

}

	void
BX_CPU_C::SUB_EEdGd(BX_CPU_C *icpu,bxInstruction_c *i)
{
	Bit32u op1, op2, sum;

	READ_RMW_VIRTUAL_DWORD(MODRMSeg(i),RMAddr(i),&op1);

	op2 = READ_VIRTUAL_32BIT_REG(MODRMnnn(i));

	sum = op1 - op2;

	WRITE_RMW_VIRTUAL_DWORD(sum);

#if (HOST_CPU_IS_I80386==0)
	SET_FLAGS_OSZAPC_32(op1,op2,sum,BX_INSTR_SUB32);
#endif //#if (HOST_CPU_IS_I80386==0)
#if (HOST_CPU_IS_I80386==1) 
	Bit32u x86_lf_flags = BX_CPU_CLASS_PTR eflags.x86.eax;
	__asm
	{
		mov edx,op2
		SUB op1,edx
		lahf
		seto al
		mov x86_lf_flags,eax
	}
	BX_CPU_CLASS_PTR eflags.x86.eax = x86_lf_flags;
#endif //#if (HOST_CPU_IS_I80386==1)

}

	void
BX_CPU_C::SUB_GbEEb(BX_CPU_C *icpu,bxInstruction_c *i)
{
	Bit8u op1, op2, sum;

	op1 = READ_VIRTUAL_8BIT_REG(MODRMnnn(i));

	READ_VIRTUAL_BYTE(MODRMSeg(i),RMAddr(i),&op2);

	sum = op1 - op2;

	WRITE_VIRTUAL_8BIT_REG(MODRMnnn(i),sum);

#if (HOST_CPU_IS_I80386==0)
	SET_FLAGS_OSZAPC_8(op1,op2,sum,BX_INSTR_SUB8);
#endif //#if (HOST_CPU_IS_I80386==0)
#if (HOST_CPU_IS_I80386==1) 
	Bit32u x86_lf_flags = BX_CPU_CLASS_PTR eflags.x86.eax;
	__asm
	{
		mov dl,op2
		SUB op1,dl
		lahf
		seto al
		mov x86_lf_flags,eax
	}
	BX_CPU_CLASS_PTR eflags.x86.eax = x86_lf_flags;
#endif //#if (HOST_CPU_IS_I80386==1)

}

	void
BX_CPU_C::SUB_GwEEw(BX_CPU_C *icpu,bxInstruction_c *i)
{
	Bit16u op1, op2, sum;

	op1 = READ_VIRTUAL_16BIT_REG(MODRMnnn(i));

	READ_VIRTUAL_WORD(MODRMSeg(i),RMAddr(i),&op2);

	sum = op1 - op2;

	WRITE_VIRTUAL_16BIT_REG(MODRMnnn(i),sum);

#if (HOST_CPU_IS_I80386==0)
	SET_FLAGS_OSZAPC_16(op1,op2,sum,BX_INSTR_SUB16);
#endif //#if (HOST_CPU_IS_I80386==0)
#if (HOST_CPU_IS_I80386==1) 
	Bit32u x86_lf_flags = BX_CPU_CLASS_PTR eflags.x86.eax;
	__asm
	{
		mov dx,op2
		SUB op1,dx
		lahf
		seto al
		mov x86_lf_flags,eax
	}
	BX_CPU_CLASS_PTR eflags.x86.eax = x86_lf_flags;
#endif //#if (HOST_CPU_IS_I80386==1)

}

	void
BX_CPU_C::SUB_GdEEd(BX_CPU_C *icpu,bxInstruction_c *i)
{
	Bit32u op1, op2, sum;

	op1 = READ_VIRTUAL_32BIT_REG(MODRMnnn(i));

	READ_VIRTUAL_DWORD(MODRMSeg(i),RMAddr(i),&op2);

	sum = op1 - op2;

	WRITE_VIRTUAL_32BIT_REG(MODRMnnn(i),sum);

#if (HOST_CPU_IS_I80386==0)
	SET_FLAGS_OSZAPC_32(op1,op2,sum,BX_INSTR_SUB32);
#endif //#if (HOST_CPU_IS_I80386==0)
#if (HOST_CPU_IS_I80386==1) 
	Bit32u x86_lf_flags = BX_CPU_CLASS_PTR eflags.x86.eax;
	__asm
	{
		mov edx,op2
		SUB op1,edx
		lahf
		seto al
		mov x86_lf_flags,eax
	}
	BX_CPU_CLASS_PTR eflags.x86.eax = x86_lf_flags;
#endif //#if (HOST_CPU_IS_I80386==1)

}

	void
BX_CPU_C::SUB_EEbIb(BX_CPU_C *icpu,bxInstruction_c *i)
{
	Bit8u op1, op2, sum;

	READ_RMW_VIRTUAL_BYTE(MODRMSeg(i),RMAddr(i),&op1);

	op2 = IMMEDIATEIb(i);

	sum = op1 - op2;

	WRITE_RMW_VIRTUAL_BYTE(sum);

#if (HOST_CPU_IS_I80386==0)
	SET_FLAGS_OSZAPC_8(op1,op2,sum,BX_INSTR_SUB8);
#endif //#if (HOST_CPU_IS_I80386==0)
#if (HOST_CPU_IS_I80386==1) 
	Bit32u x86_lf_flags = BX_CPU_CLASS_PTR eflags.x86.eax;
	__asm
	{
		mov dl,op2
		SUB op1,dl
		lahf
		seto al
		mov x86_lf_flags,eax
	}
	BX_CPU_CLASS_PTR eflags.x86.eax = x86_lf_flags;
#endif //#if (HOST_CPU_IS_I80386==1)

}

	void
BX_CPU_C::SUB_EEwIw(BX_CPU_C *icpu,bxInstruction_c *i)
{
	Bit16u op1, op2, sum;

	READ_RMW_VIRTUAL_WORD(MODRMSeg(i),RMAddr(i),&op1);

	op2 = IMMEDIATEIw(i);

	sum = op1 - op2;

	WRITE_RMW_VIRTUAL_WORD(sum);

#if (HOST_CPU_IS_I80386==0)
	SET_FLAGS_OSZAPC_16(op1,op2,sum,BX_INSTR_SUB16);
#endif //#if (HOST_CPU_IS_I80386==0)
#if (HOST_CPU_IS_I80386==1) 
	Bit32u x86_lf_flags = BX_CPU_CLASS_PTR eflags.x86.eax;
	__asm
	{
		mov dx,op2
		SUB op1,dx
		lahf
		seto al
		mov x86_lf_flags,eax
	}
	BX_CPU_CLASS_PTR eflags.x86.eax = x86_lf_flags;
#endif //#if (HOST_CPU_IS_I80386==1)

}

	void
BX_CPU_C::SUB_EEdId(BX_CPU_C *icpu,bxInstruction_c *i)
{
	Bit32u op1, op2, sum;

	READ_RMW_VIRTUAL_DWORD(MODRMSeg(i),RMAddr(i),&op1);

	op2 = IMMEDIATEId(i);

	sum = op1 - op2;

	WRITE_RMW_VIRTUAL_DWORD(sum);

#if (HOST_CPU_IS_I80386==0)
	SET_FLAGS_OSZAPC_32(op1,op2,sum,BX_INSTR_SUB32);
#endif //#if (HOST_CPU_IS_I80386==0)
#if (HOST_CPU_IS_I80386==1) 
	Bit32u x86_lf_flags = BX_CPU_CLASS_PTR eflags.x86.eax;
	__asm
	{
		mov edx,op2
		SUB op1,edx
		lahf
		seto al
		mov x86_lf_flags,eax
	}
	BX_CPU_CLASS_PTR eflags.x86.eax = x86_lf_flags;
#endif //#if (HOST_CPU_IS_I80386==1)

}

	void
BX_CPU_C::AND_EGbGb(BX_CPU_C *icpu,bxInstruction_c *i)
{
	Bit8u op1, op2, sum;

	op1 = READ_VIRTUAL_8BIT_REG(MODRMrm(i));

	op2 = READ_VIRTUAL_8BIT_REG(MODRMnnn(i));

	sum = op1 & op2;

	WRITE_VIRTUAL_8BIT_REG(MODRMrm(i), sum);

#if (HOST_CPU_IS_I80386==0)
	BX_CPU_CLASS_PTR lf_entrys[BX_LF_INDEX_OSZAPC].result_8 = sum;
	BX_CPU_CLASS_PTR lf_entrys[BX_LF_INDEX_OSZAPC].instr = BX_INSTR_AND8;
	BX_CPU_CLASS_PTR lf_flags_status = BX_LF_MASK_OSZAPC;
#endif //#if (HOST_CPU_IS_I80386==0)
#if (HOST_CPU_IS_I80386==1) 
	Bit32u x86_lf_flags = BX_CPU_CLASS_PTR eflags.x86.eax;
	__asm
	{
		mov dl,op2
		AND op1,dl
		lahf
		seto al
		mov x86_lf_flags,eax
	}
	BX_CPU_CLASS_PTR eflags.x86.eax = x86_lf_flags;
#endif //#if (HOST_CPU_IS_I80386==1)

}

	void
BX_CPU_C::AND_EGwGw(BX_CPU_C *icpu,bxInstruction_c *i)
{
	Bit16u op1, op2, sum;

	op1 = READ_VIRTUAL_16BIT_REG(MODRMrm(i));

	op2 = READ_VIRTUAL_16BIT_REG(MODRMnnn(i));

	sum = op1 & op2;

	WRITE_VIRTUAL_16BIT_REG(MODRMrm(i), sum);

#if (HOST_CPU_IS_I80386==0)
	BX_CPU_CLASS_PTR lf_entrys[BX_LF_INDEX_OSZAPC].result_16 = sum;
	BX_CPU_CLASS_PTR lf_entrys[BX_LF_INDEX_OSZAPC].instr = BX_INSTR_AND16;
	BX_CPU_CLASS_PTR lf_flags_status = BX_LF_MASK_OSZAPC;
#endif //#if (HOST_CPU_IS_I80386==0)
#if (HOST_CPU_IS_I80386==1) 
	Bit32u x86_lf_flags = BX_CPU_CLASS_PTR eflags.x86.eax;
	__asm
	{
		mov dx,op2
		AND op1,dx
		lahf
		seto al
		mov x86_lf_flags,eax
	}
	BX_CPU_CLASS_PTR eflags.x86.eax = x86_lf_flags;
#endif //#if (HOST_CPU_IS_I80386==1)

}

	void
BX_CPU_C::AND_EGdGd(BX_CPU_C *icpu,bxInstruction_c *i)
{
	Bit32u op1, op2, sum;

	op1 = READ_VIRTUAL_32BIT_REG(MODRMrm(i));

	op2 = READ_VIRTUAL_32BIT_REG(MODRMnnn(i));

	sum = op1 & op2;

	WRITE_VIRTUAL_32BIT_REG(MODRMrm(i), sum);

#if (HOST_CPU_IS_I80386==0)
	BX_CPU_CLASS_PTR lf_entrys[BX_LF_INDEX_OSZAPC].result_32 = sum;
	BX_CPU_CLASS_PTR lf_entrys[BX_LF_INDEX_OSZAPC].instr = BX_INSTR_AND32;
	BX_CPU_CLASS_PTR lf_flags_status = BX_LF_MASK_OSZAPC;
#endif //#if (HOST_CPU_IS_I80386==0)
#if (HOST_CPU_IS_I80386==1) 
	Bit32u x86_lf_flags = BX_CPU_CLASS_PTR eflags.x86.eax;
	__asm
	{
		mov edx,op2
		AND op1,edx
		lahf
		seto al
		mov x86_lf_flags,eax
	}
	BX_CPU_CLASS_PTR eflags.x86.eax = x86_lf_flags;
#endif //#if (HOST_CPU_IS_I80386==1)

}

	void
BX_CPU_C::AND_GbEGb(BX_CPU_C *icpu,bxInstruction_c *i)
{
	Bit8u op1, op2, sum;

	op1 = READ_VIRTUAL_8BIT_REG(MODRMnnn(i));

	op2 = READ_VIRTUAL_8BIT_REG(MODRMrm(i));

	sum = op1 & op2;

	WRITE_VIRTUAL_8BIT_REG(MODRMnnn(i),sum);

#if (HOST_CPU_IS_I80386==0)
	BX_CPU_CLASS_PTR lf_entrys[BX_LF_INDEX_OSZAPC].result_8 = sum;
	BX_CPU_CLASS_PTR lf_entrys[BX_LF_INDEX_OSZAPC].instr = BX_INSTR_AND8;
	BX_CPU_CLASS_PTR lf_flags_status = BX_LF_MASK_OSZAPC;
#endif //#if (HOST_CPU_IS_I80386==0)
#if (HOST_CPU_IS_I80386==1) 
	Bit32u x86_lf_flags = BX_CPU_CLASS_PTR eflags.x86.eax;
	__asm
	{
		mov dl,op2
		AND op1,dl
		lahf
		seto al
		mov x86_lf_flags,eax
	}
	BX_CPU_CLASS_PTR eflags.x86.eax = x86_lf_flags;
#endif //#if (HOST_CPU_IS_I80386==1)

}

	void
BX_CPU_C::AND_GwEGw(BX_CPU_C *icpu,bxInstruction_c *i)
{
	Bit16u op1, op2, sum;

	op1 = READ_VIRTUAL_16BIT_REG(MODRMnnn(i));

	op2 = READ_VIRTUAL_16BIT_REG(MODRMrm(i));

	sum = op1 & op2;

	WRITE_VIRTUAL_16BIT_REG(MODRMnnn(i),sum);

#if (HOST_CPU_IS_I80386==0)
	BX_CPU_CLASS_PTR lf_entrys[BX_LF_INDEX_OSZAPC].result_16 = sum;
	BX_CPU_CLASS_PTR lf_entrys[BX_LF_INDEX_OSZAPC].instr = BX_INSTR_AND16;
	BX_CPU_CLASS_PTR lf_flags_status = BX_LF_MASK_OSZAPC;
#endif //#if (HOST_CPU_IS_I80386==0)
#if (HOST_CPU_IS_I80386==1) 
	Bit32u x86_lf_flags = BX_CPU_CLASS_PTR eflags.x86.eax;
	__asm
	{
		mov dx,op2
		AND op1,dx
		lahf
		seto al
		mov x86_lf_flags,eax
	}
	BX_CPU_CLASS_PTR eflags.x86.eax = x86_lf_flags;
#endif //#if (HOST_CPU_IS_I80386==1)

}

	void
BX_CPU_C::AND_GdEGd(BX_CPU_C *icpu,bxInstruction_c *i)
{
	Bit32u op1, op2, sum;

	op1 = READ_VIRTUAL_32BIT_REG(MODRMnnn(i));

	op2 = READ_VIRTUAL_32BIT_REG(MODRMrm(i));

	sum = op1 & op2;

	WRITE_VIRTUAL_32BIT_REG(MODRMnnn(i),sum);

#if (HOST_CPU_IS_I80386==0)
	BX_CPU_CLASS_PTR lf_entrys[BX_LF_INDEX_OSZAPC].result_32 = sum;
	BX_CPU_CLASS_PTR lf_entrys[BX_LF_INDEX_OSZAPC].instr = BX_INSTR_AND32;
	BX_CPU_CLASS_PTR lf_flags_status = BX_LF_MASK_OSZAPC;
#endif //#if (HOST_CPU_IS_I80386==0)
#if (HOST_CPU_IS_I80386==1) 
	Bit32u x86_lf_flags = BX_CPU_CLASS_PTR eflags.x86.eax;
	__asm
	{
		mov edx,op2
		AND op1,edx
		lahf
		seto al
		mov x86_lf_flags,eax
	}
	BX_CPU_CLASS_PTR eflags.x86.eax = x86_lf_flags;
#endif //#if (HOST_CPU_IS_I80386==1)

}

	void
BX_CPU_C::AND_EGbIb(BX_CPU_C *icpu,bxInstruction_c *i)
{
	Bit8u op1, op2, sum;

	op1 = READ_VIRTUAL_8BIT_REG(MODRMrm(i));

	op2 = IMMEDIATEIb(i);

	sum = op1 & op2;

	WRITE_VIRTUAL_8BIT_REG(MODRMrm(i),sum);

#if (HOST_CPU_IS_I80386==0)
	BX_CPU_CLASS_PTR lf_entrys[BX_LF_INDEX_OSZAPC].result_8 = sum;
	BX_CPU_CLASS_PTR lf_entrys[BX_LF_INDEX_OSZAPC].instr = BX_INSTR_AND8;
	BX_CPU_CLASS_PTR lf_flags_status = BX_LF_MASK_OSZAPC;
#endif //#if (HOST_CPU_IS_I80386==0)
#if (HOST_CPU_IS_I80386==1) 
	Bit32u x86_lf_flags = BX_CPU_CLASS_PTR eflags.x86.eax;
	__asm
	{
		mov dl,op2
		AND op1,dl
		lahf
		seto al
		mov x86_lf_flags,eax
	}
	BX_CPU_CLASS_PTR eflags.x86.eax = x86_lf_flags;
#endif //#if (HOST_CPU_IS_I80386==1)

}

	void
BX_CPU_C::AND_EGwIw(BX_CPU_C *icpu,bxInstruction_c *i)
{
	Bit16u op1, op2, sum;

	op1 = READ_VIRTUAL_16BIT_REG(MODRMrm(i));

	op2 = IMMEDIATEIw(i);

	sum = op1 & op2;

	WRITE_VIRTUAL_16BIT_REG(MODRMrm(i),sum);

#if (HOST_CPU_IS_I80386==0)
	BX_CPU_CLASS_PTR lf_entrys[BX_LF_INDEX_OSZAPC].result_16 = sum;
	BX_CPU_CLASS_PTR lf_entrys[BX_LF_INDEX_OSZAPC].instr = BX_INSTR_AND16;
	BX_CPU_CLASS_PTR lf_flags_status = BX_LF_MASK_OSZAPC;
#endif //#if (HOST_CPU_IS_I80386==0)
#if (HOST_CPU_IS_I80386==1) 
	Bit32u x86_lf_flags = BX_CPU_CLASS_PTR eflags.x86.eax;
	__asm
	{
		mov dx,op2
		AND op1,dx
		lahf
		seto al
		mov x86_lf_flags,eax
	}
	BX_CPU_CLASS_PTR eflags.x86.eax = x86_lf_flags;
#endif //#if (HOST_CPU_IS_I80386==1)

}

	void
BX_CPU_C::AND_EGdId(BX_CPU_C *icpu,bxInstruction_c *i)
{
	Bit32u op1, op2, sum;

	op1 = READ_VIRTUAL_32BIT_REG(MODRMrm(i));

	op2 = IMMEDIATEId(i);

	sum = op1 & op2;

	WRITE_VIRTUAL_32BIT_REG(MODRMrm(i),sum);

#if (HOST_CPU_IS_I80386==0)
	BX_CPU_CLASS_PTR lf_entrys[BX_LF_INDEX_OSZAPC].result_32 = sum;
	BX_CPU_CLASS_PTR lf_entrys[BX_LF_INDEX_OSZAPC].instr = BX_INSTR_AND32;
	BX_CPU_CLASS_PTR lf_flags_status = BX_LF_MASK_OSZAPC;
#endif //#if (HOST_CPU_IS_I80386==0)
#if (HOST_CPU_IS_I80386==1) 
	Bit32u x86_lf_flags = BX_CPU_CLASS_PTR eflags.x86.eax;
	__asm
	{
		mov edx,op2
		AND op1,edx
		lahf
		seto al
		mov x86_lf_flags,eax
	}
	BX_CPU_CLASS_PTR eflags.x86.eax = x86_lf_flags;
#endif //#if (HOST_CPU_IS_I80386==1)

}

	void
BX_CPU_C::AND_ALIb(BX_CPU_C *icpu,bxInstruction_c *i)
{
	Bit8u op1, op2, sum;

	op1 = READ_VIRTUAL_8BIT_REG(0);

	op2 = IMMEDIATEIb(i);

	sum = op1 & op2;

	WRITE_VIRTUAL_8BIT_REG(0,sum);

#if (HOST_CPU_IS_I80386==0)
	BX_CPU_CLASS_PTR lf_entrys[BX_LF_INDEX_OSZAPC].result_8 = sum;
	BX_CPU_CLASS_PTR lf_entrys[BX_LF_INDEX_OSZAPC].instr = BX_INSTR_AND8;
	BX_CPU_CLASS_PTR lf_flags_status = BX_LF_MASK_OSZAPC;
#endif //#if (HOST_CPU_IS_I80386==0)
#if (HOST_CPU_IS_I80386==1) 
	Bit32u x86_lf_flags = BX_CPU_CLASS_PTR eflags.x86.eax;
	__asm
	{
		mov dl,op2
		AND op1,dl
		lahf
		seto al
		mov x86_lf_flags,eax
	}
	BX_CPU_CLASS_PTR eflags.x86.eax = x86_lf_flags;
#endif //#if (HOST_CPU_IS_I80386==1)

}

	void
BX_CPU_C::AND_AXIw(BX_CPU_C *icpu,bxInstruction_c *i)
{
	Bit16u op1, op2, sum;

	op1 = READ_VIRTUAL_16BIT_REG(0);

	op2 = IMMEDIATEIw(i);

	sum = op1 & op2;

	WRITE_VIRTUAL_16BIT_REG(0,sum);

#if (HOST_CPU_IS_I80386==0)
	BX_CPU_CLASS_PTR lf_entrys[BX_LF_INDEX_OSZAPC].result_16 = sum;
	BX_CPU_CLASS_PTR lf_entrys[BX_LF_INDEX_OSZAPC].instr = BX_INSTR_AND16;
	BX_CPU_CLASS_PTR lf_flags_status = BX_LF_MASK_OSZAPC;
#endif //#if (HOST_CPU_IS_I80386==0)
#if (HOST_CPU_IS_I80386==1) 
	Bit32u x86_lf_flags = BX_CPU_CLASS_PTR eflags.x86.eax;
	__asm
	{
		mov dx,op2
		AND op1,dx
		lahf
		seto al
		mov x86_lf_flags,eax
	}
	BX_CPU_CLASS_PTR eflags.x86.eax = x86_lf_flags;
#endif //#if (HOST_CPU_IS_I80386==1)

}

	void
BX_CPU_C::AND_EAXId(BX_CPU_C *icpu,bxInstruction_c *i)
{
	Bit32u op1, op2, sum;

	op1 = READ_VIRTUAL_32BIT_REG(0);

	op2 = IMMEDIATEId(i);

	sum = op1 & op2;

	WRITE_VIRTUAL_32BIT_REG(0,sum);

#if (HOST_CPU_IS_I80386==0)
	BX_CPU_CLASS_PTR lf_entrys[BX_LF_INDEX_OSZAPC].result_32 = sum;
	BX_CPU_CLASS_PTR lf_entrys[BX_LF_INDEX_OSZAPC].instr = BX_INSTR_AND32;
	BX_CPU_CLASS_PTR lf_flags_status = BX_LF_MASK_OSZAPC;
#endif //#if (HOST_CPU_IS_I80386==0)
#if (HOST_CPU_IS_I80386==1) 
	Bit32u x86_lf_flags = BX_CPU_CLASS_PTR eflags.x86.eax;
	__asm
	{
		mov edx,op2
		AND op1,edx
		lahf
		seto al
		mov x86_lf_flags,eax
	}
	BX_CPU_CLASS_PTR eflags.x86.eax = x86_lf_flags;
#endif //#if (HOST_CPU_IS_I80386==1)

}

	void
BX_CPU_C::AND_EEbGb(BX_CPU_C *icpu,bxInstruction_c *i)
{
	Bit8u op1, op2, sum;

	READ_RMW_VIRTUAL_BYTE(MODRMSeg(i),RMAddr(i),&op1);

	op2 = READ_VIRTUAL_8BIT_REG(MODRMnnn(i));

	sum = op1 & op2;

	WRITE_RMW_VIRTUAL_BYTE(sum);

#if (HOST_CPU_IS_I80386==0)
	BX_CPU_CLASS_PTR lf_entrys[BX_LF_INDEX_OSZAPC].result_8 = sum;
	BX_CPU_CLASS_PTR lf_entrys[BX_LF_INDEX_OSZAPC].instr = BX_INSTR_AND8;
	BX_CPU_CLASS_PTR lf_flags_status = BX_LF_MASK_OSZAPC;
#endif //#if (HOST_CPU_IS_I80386==0)
#if (HOST_CPU_IS_I80386==1) 
	Bit32u x86_lf_flags = BX_CPU_CLASS_PTR eflags.x86.eax;
	__asm
	{
		mov dl,op2
		AND op1,dl
		lahf
		seto al
		mov x86_lf_flags,eax
	}
	BX_CPU_CLASS_PTR eflags.x86.eax = x86_lf_flags;
#endif //#if (HOST_CPU_IS_I80386==1)

}

	void
BX_CPU_C::AND_EEwGw(BX_CPU_C *icpu,bxInstruction_c *i)
{
	Bit16u op1, op2, sum;

	READ_RMW_VIRTUAL_WORD(MODRMSeg(i),RMAddr(i),&op1);

	op2 = READ_VIRTUAL_16BIT_REG(MODRMnnn(i));

	sum = op1 & op2;

	WRITE_RMW_VIRTUAL_WORD(sum);

#if (HOST_CPU_IS_I80386==0)
	BX_CPU_CLASS_PTR lf_entrys[BX_LF_INDEX_OSZAPC].result_16 = sum;
	BX_CPU_CLASS_PTR lf_entrys[BX_LF_INDEX_OSZAPC].instr = BX_INSTR_AND16;
	BX_CPU_CLASS_PTR lf_flags_status = BX_LF_MASK_OSZAPC;
#endif //#if (HOST_CPU_IS_I80386==0)
#if (HOST_CPU_IS_I80386==1) 
	Bit32u x86_lf_flags = BX_CPU_CLASS_PTR eflags.x86.eax;
	__asm
	{
		mov dx,op2
		AND op1,dx
		lahf
		seto al
		mov x86_lf_flags,eax
	}
	BX_CPU_CLASS_PTR eflags.x86.eax = x86_lf_flags;
#endif //#if (HOST_CPU_IS_I80386==1)

}

	void
BX_CPU_C::AND_EEdGd(BX_CPU_C *icpu,bxInstruction_c *i)
{
	Bit32u op1, op2, sum;

	READ_RMW_VIRTUAL_DWORD(MODRMSeg(i),RMAddr(i),&op1);

	op2 = READ_VIRTUAL_32BIT_REG(MODRMnnn(i));

	sum = op1 & op2;

	WRITE_RMW_VIRTUAL_DWORD(sum);

#if (HOST_CPU_IS_I80386==0)
	BX_CPU_CLASS_PTR lf_entrys[BX_LF_INDEX_OSZAPC].result_32 = sum;
	BX_CPU_CLASS_PTR lf_entrys[BX_LF_INDEX_OSZAPC].instr = BX_INSTR_AND32;
	BX_CPU_CLASS_PTR lf_flags_status = BX_LF_MASK_OSZAPC;
#endif //#if (HOST_CPU_IS_I80386==0)
#if (HOST_CPU_IS_I80386==1) 
	Bit32u x86_lf_flags = BX_CPU_CLASS_PTR eflags.x86.eax;
	__asm
	{
		mov edx,op2
		AND op1,edx
		lahf
		seto al
		mov x86_lf_flags,eax
	}
	BX_CPU_CLASS_PTR eflags.x86.eax = x86_lf_flags;
#endif //#if (HOST_CPU_IS_I80386==1)

}

	void
BX_CPU_C::AND_GbEEb(BX_CPU_C *icpu,bxInstruction_c *i)
{
	Bit8u op1, op2, sum;

	op1 = READ_VIRTUAL_8BIT_REG(MODRMnnn(i));

	READ_VIRTUAL_BYTE(MODRMSeg(i),RMAddr(i),&op2);

	sum = op1 & op2;

	WRITE_VIRTUAL_8BIT_REG(MODRMnnn(i),sum);

#if (HOST_CPU_IS_I80386==0)
	BX_CPU_CLASS_PTR lf_entrys[BX_LF_INDEX_OSZAPC].result_8 = sum;
	BX_CPU_CLASS_PTR lf_entrys[BX_LF_INDEX_OSZAPC].instr = BX_INSTR_AND8;
	BX_CPU_CLASS_PTR lf_flags_status = BX_LF_MASK_OSZAPC;
#endif //#if (HOST_CPU_IS_I80386==0)
#if (HOST_CPU_IS_I80386==1) 
	Bit32u x86_lf_flags = BX_CPU_CLASS_PTR eflags.x86.eax;
	__asm
	{
		mov dl,op2
		AND op1,dl
		lahf
		seto al
		mov x86_lf_flags,eax
	}
	BX_CPU_CLASS_PTR eflags.x86.eax = x86_lf_flags;
#endif //#if (HOST_CPU_IS_I80386==1)

}

	void
BX_CPU_C::AND_GwEEw(BX_CPU_C *icpu,bxInstruction_c *i)
{
	Bit16u op1, op2, sum;

	op1 = READ_VIRTUAL_16BIT_REG(MODRMnnn(i));

	READ_VIRTUAL_WORD(MODRMSeg(i),RMAddr(i),&op2);

	sum = op1 & op2;

	WRITE_VIRTUAL_16BIT_REG(MODRMnnn(i),sum);

#if (HOST_CPU_IS_I80386==0)
	BX_CPU_CLASS_PTR lf_entrys[BX_LF_INDEX_OSZAPC].result_16 = sum;
	BX_CPU_CLASS_PTR lf_entrys[BX_LF_INDEX_OSZAPC].instr = BX_INSTR_AND16;
	BX_CPU_CLASS_PTR lf_flags_status = BX_LF_MASK_OSZAPC;
#endif //#if (HOST_CPU_IS_I80386==0)
#if (HOST_CPU_IS_I80386==1) 
	Bit32u x86_lf_flags = BX_CPU_CLASS_PTR eflags.x86.eax;
	__asm
	{
		mov dx,op2
		AND op1,dx
		lahf
		seto al
		mov x86_lf_flags,eax
	}
	BX_CPU_CLASS_PTR eflags.x86.eax = x86_lf_flags;
#endif //#if (HOST_CPU_IS_I80386==1)

}

	void
BX_CPU_C::AND_GdEEd(BX_CPU_C *icpu,bxInstruction_c *i)
{
	Bit32u op1, op2, sum;

	op1 = READ_VIRTUAL_32BIT_REG(MODRMnnn(i));

	READ_VIRTUAL_DWORD(MODRMSeg(i),RMAddr(i),&op2);

	sum = op1 & op2;

	WRITE_VIRTUAL_32BIT_REG(MODRMnnn(i),sum);

#if (HOST_CPU_IS_I80386==0)
	BX_CPU_CLASS_PTR lf_entrys[BX_LF_INDEX_OSZAPC].result_32 = sum;
	BX_CPU_CLASS_PTR lf_entrys[BX_LF_INDEX_OSZAPC].instr = BX_INSTR_AND32;
	BX_CPU_CLASS_PTR lf_flags_status = BX_LF_MASK_OSZAPC;
#endif //#if (HOST_CPU_IS_I80386==0)
#if (HOST_CPU_IS_I80386==1) 
	Bit32u x86_lf_flags = BX_CPU_CLASS_PTR eflags.x86.eax;
	__asm
	{
		mov edx,op2
		AND op1,edx
		lahf
		seto al
		mov x86_lf_flags,eax
	}
	BX_CPU_CLASS_PTR eflags.x86.eax = x86_lf_flags;
#endif //#if (HOST_CPU_IS_I80386==1)

}

	void
BX_CPU_C::AND_EEbIb(BX_CPU_C *icpu,bxInstruction_c *i)
{
	Bit8u op1, op2, sum;

	READ_RMW_VIRTUAL_BYTE(MODRMSeg(i),RMAddr(i),&op1);

	op2 = IMMEDIATEIb(i);

	sum = op1 & op2;

	WRITE_RMW_VIRTUAL_BYTE(sum);

#if (HOST_CPU_IS_I80386==0)
	BX_CPU_CLASS_PTR lf_entrys[BX_LF_INDEX_OSZAPC].result_8 = sum;
	BX_CPU_CLASS_PTR lf_entrys[BX_LF_INDEX_OSZAPC].instr = BX_INSTR_AND8;
	BX_CPU_CLASS_PTR lf_flags_status = BX_LF_MASK_OSZAPC;
#endif //#if (HOST_CPU_IS_I80386==0)
#if (HOST_CPU_IS_I80386==1) 
	Bit32u x86_lf_flags = BX_CPU_CLASS_PTR eflags.x86.eax;
	__asm
	{
		mov dl,op2
		AND op1,dl
		lahf
		seto al
		mov x86_lf_flags,eax
	}
	BX_CPU_CLASS_PTR eflags.x86.eax = x86_lf_flags;
#endif //#if (HOST_CPU_IS_I80386==1)

}

	void
BX_CPU_C::AND_EEwIw(BX_CPU_C *icpu,bxInstruction_c *i)
{
	Bit16u op1, op2, sum;

	READ_RMW_VIRTUAL_WORD(MODRMSeg(i),RMAddr(i),&op1);

	op2 = IMMEDIATEIw(i);

	sum = op1 & op2;

	WRITE_RMW_VIRTUAL_WORD(sum);

#if (HOST_CPU_IS_I80386==0)
	BX_CPU_CLASS_PTR lf_entrys[BX_LF_INDEX_OSZAPC].result_16 = sum;
	BX_CPU_CLASS_PTR lf_entrys[BX_LF_INDEX_OSZAPC].instr = BX_INSTR_AND16;
	BX_CPU_CLASS_PTR lf_flags_status = BX_LF_MASK_OSZAPC;
#endif //#if (HOST_CPU_IS_I80386==0)
#if (HOST_CPU_IS_I80386==1) 
	Bit32u x86_lf_flags = BX_CPU_CLASS_PTR eflags.x86.eax;
	__asm
	{
		mov dx,op2
		AND op1,dx
		lahf
		seto al
		mov x86_lf_flags,eax
	}
	BX_CPU_CLASS_PTR eflags.x86.eax = x86_lf_flags;
#endif //#if (HOST_CPU_IS_I80386==1)

}

	void
BX_CPU_C::AND_EEdId(BX_CPU_C *icpu,bxInstruction_c *i)
{
	Bit32u op1, op2, sum;

	READ_RMW_VIRTUAL_DWORD(MODRMSeg(i),RMAddr(i),&op1);

	op2 = IMMEDIATEId(i);

	sum = op1 & op2;

	WRITE_RMW_VIRTUAL_DWORD(sum);

#if (HOST_CPU_IS_I80386==0)
	BX_CPU_CLASS_PTR lf_entrys[BX_LF_INDEX_OSZAPC].result_32 = sum;
	BX_CPU_CLASS_PTR lf_entrys[BX_LF_INDEX_OSZAPC].instr = BX_INSTR_AND32;
	BX_CPU_CLASS_PTR lf_flags_status = BX_LF_MASK_OSZAPC;
#endif //#if (HOST_CPU_IS_I80386==0)
#if (HOST_CPU_IS_I80386==1) 
	Bit32u x86_lf_flags = BX_CPU_CLASS_PTR eflags.x86.eax;
	__asm
	{
		mov edx,op2
		AND op1,edx
		lahf
		seto al
		mov x86_lf_flags,eax
	}
	BX_CPU_CLASS_PTR eflags.x86.eax = x86_lf_flags;
#endif //#if (HOST_CPU_IS_I80386==1)

}

	void
BX_CPU_C::XOR_EGbGb(BX_CPU_C *icpu,bxInstruction_c *i)
{
	Bit8u op1, op2, sum;

	op1 = READ_VIRTUAL_8BIT_REG(MODRMrm(i));

	op2 = READ_VIRTUAL_8BIT_REG(MODRMnnn(i));

	sum = op1 ^ op2;

	WRITE_VIRTUAL_8BIT_REG(MODRMrm(i), sum);

#if (HOST_CPU_IS_I80386==0)
	BX_CPU_CLASS_PTR lf_entrys[BX_LF_INDEX_OSZAPC].result_8 = sum;
	BX_CPU_CLASS_PTR lf_entrys[BX_LF_INDEX_OSZAPC].instr = BX_INSTR_XOR8;
	BX_CPU_CLASS_PTR lf_flags_status = BX_LF_MASK_OSZAPC;
#endif //#if (HOST_CPU_IS_I80386==0)
#if (HOST_CPU_IS_I80386==1) 
	Bit32u x86_lf_flags = BX_CPU_CLASS_PTR eflags.x86.eax;
	__asm
	{
		mov dl,op2
		XOR op1,dl
		lahf
		seto al
		mov x86_lf_flags,eax
	}
	BX_CPU_CLASS_PTR eflags.x86.eax = x86_lf_flags;
#endif //#if (HOST_CPU_IS_I80386==1)

}

	void
BX_CPU_C::XOR_EGwGw(BX_CPU_C *icpu,bxInstruction_c *i)
{
	Bit16u op1, op2, sum;

	op1 = READ_VIRTUAL_16BIT_REG(MODRMrm(i));

	op2 = READ_VIRTUAL_16BIT_REG(MODRMnnn(i));

	sum = op1 ^ op2;

	WRITE_VIRTUAL_16BIT_REG(MODRMrm(i), sum);

#if (HOST_CPU_IS_I80386==0)
	BX_CPU_CLASS_PTR lf_entrys[BX_LF_INDEX_OSZAPC].result_16 = sum;
	BX_CPU_CLASS_PTR lf_entrys[BX_LF_INDEX_OSZAPC].instr = BX_INSTR_XOR16;
	BX_CPU_CLASS_PTR lf_flags_status = BX_LF_MASK_OSZAPC;
#endif //#if (HOST_CPU_IS_I80386==0)
#if (HOST_CPU_IS_I80386==1) 
	Bit32u x86_lf_flags = BX_CPU_CLASS_PTR eflags.x86.eax;
	__asm
	{
		mov dx,op2
		XOR op1,dx
		lahf
		seto al
		mov x86_lf_flags,eax
	}
	BX_CPU_CLASS_PTR eflags.x86.eax = x86_lf_flags;
#endif //#if (HOST_CPU_IS_I80386==1)

}

	void
BX_CPU_C::XOR_EGdGd(BX_CPU_C *icpu,bxInstruction_c *i)
{
	Bit32u op1, op2, sum;

	op1 = READ_VIRTUAL_32BIT_REG(MODRMrm(i));

	op2 = READ_VIRTUAL_32BIT_REG(MODRMnnn(i));

	sum = op1 ^ op2;

	WRITE_VIRTUAL_32BIT_REG(MODRMrm(i), sum);

#if (HOST_CPU_IS_I80386==0)
	BX_CPU_CLASS_PTR lf_entrys[BX_LF_INDEX_OSZAPC].result_32 = sum;
	BX_CPU_CLASS_PTR lf_entrys[BX_LF_INDEX_OSZAPC].instr = BX_INSTR_XOR32;
	BX_CPU_CLASS_PTR lf_flags_status = BX_LF_MASK_OSZAPC;
#endif //#if (HOST_CPU_IS_I80386==0)
#if (HOST_CPU_IS_I80386==1) 
	Bit32u x86_lf_flags = BX_CPU_CLASS_PTR eflags.x86.eax;
	__asm
	{
		mov edx,op2
		XOR op1,edx
		lahf
		seto al
		mov x86_lf_flags,eax
	}
	BX_CPU_CLASS_PTR eflags.x86.eax = x86_lf_flags;
#endif //#if (HOST_CPU_IS_I80386==1)

}

	void
BX_CPU_C::XOR_GbEGb(BX_CPU_C *icpu,bxInstruction_c *i)
{
	Bit8u op1, op2, sum;

	op1 = READ_VIRTUAL_8BIT_REG(MODRMnnn(i));

	op2 = READ_VIRTUAL_8BIT_REG(MODRMrm(i));

	sum = op1 ^ op2;

	WRITE_VIRTUAL_8BIT_REG(MODRMnnn(i),sum);

#if (HOST_CPU_IS_I80386==0)
	BX_CPU_CLASS_PTR lf_entrys[BX_LF_INDEX_OSZAPC].result_8 = sum;
	BX_CPU_CLASS_PTR lf_entrys[BX_LF_INDEX_OSZAPC].instr = BX_INSTR_XOR8;
	BX_CPU_CLASS_PTR lf_flags_status = BX_LF_MASK_OSZAPC;
#endif //#if (HOST_CPU_IS_I80386==0)
#if (HOST_CPU_IS_I80386==1) 
	Bit32u x86_lf_flags = BX_CPU_CLASS_PTR eflags.x86.eax;
	__asm
	{
		mov dl,op2
		XOR op1,dl
		lahf
		seto al
		mov x86_lf_flags,eax
	}
	BX_CPU_CLASS_PTR eflags.x86.eax = x86_lf_flags;
#endif //#if (HOST_CPU_IS_I80386==1)

}

	void
BX_CPU_C::XOR_GwEGw(BX_CPU_C *icpu,bxInstruction_c *i)
{
	Bit16u op1, op2, sum;

	op1 = READ_VIRTUAL_16BIT_REG(MODRMnnn(i));

	op2 = READ_VIRTUAL_16BIT_REG(MODRMrm(i));

	sum = op1 ^ op2;

	WRITE_VIRTUAL_16BIT_REG(MODRMnnn(i),sum);

#if (HOST_CPU_IS_I80386==0)
	BX_CPU_CLASS_PTR lf_entrys[BX_LF_INDEX_OSZAPC].result_16 = sum;
	BX_CPU_CLASS_PTR lf_entrys[BX_LF_INDEX_OSZAPC].instr = BX_INSTR_XOR16;
	BX_CPU_CLASS_PTR lf_flags_status = BX_LF_MASK_OSZAPC;
#endif //#if (HOST_CPU_IS_I80386==0)
#if (HOST_CPU_IS_I80386==1) 
	Bit32u x86_lf_flags = BX_CPU_CLASS_PTR eflags.x86.eax;
	__asm
	{
		mov dx,op2
		XOR op1,dx
		lahf
		seto al
		mov x86_lf_flags,eax
	}
	BX_CPU_CLASS_PTR eflags.x86.eax = x86_lf_flags;
#endif //#if (HOST_CPU_IS_I80386==1)

}

	void
BX_CPU_C::XOR_GdEGd(BX_CPU_C *icpu,bxInstruction_c *i)
{
	Bit32u op1, op2, sum;

	op1 = READ_VIRTUAL_32BIT_REG(MODRMnnn(i));

	op2 = READ_VIRTUAL_32BIT_REG(MODRMrm(i));

	sum = op1 ^ op2;

	WRITE_VIRTUAL_32BIT_REG(MODRMnnn(i),sum);

#if (HOST_CPU_IS_I80386==0)
	BX_CPU_CLASS_PTR lf_entrys[BX_LF_INDEX_OSZAPC].result_32 = sum;
	BX_CPU_CLASS_PTR lf_entrys[BX_LF_INDEX_OSZAPC].instr = BX_INSTR_XOR32;
	BX_CPU_CLASS_PTR lf_flags_status = BX_LF_MASK_OSZAPC;
#endif //#if (HOST_CPU_IS_I80386==0)
#if (HOST_CPU_IS_I80386==1) 
	Bit32u x86_lf_flags = BX_CPU_CLASS_PTR eflags.x86.eax;
	__asm
	{
		mov edx,op2
		XOR op1,edx
		lahf
		seto al
		mov x86_lf_flags,eax
	}
	BX_CPU_CLASS_PTR eflags.x86.eax = x86_lf_flags;
#endif //#if (HOST_CPU_IS_I80386==1)

}

	void
BX_CPU_C::XOR_EGbIb(BX_CPU_C *icpu,bxInstruction_c *i)
{
	Bit8u op1, op2, sum;

	op1 = READ_VIRTUAL_8BIT_REG(MODRMrm(i));

	op2 = IMMEDIATEIb(i);

	sum = op1 ^ op2;

	WRITE_VIRTUAL_8BIT_REG(MODRMrm(i),sum);

#if (HOST_CPU_IS_I80386==0)
	BX_CPU_CLASS_PTR lf_entrys[BX_LF_INDEX_OSZAPC].result_8 = sum;
	BX_CPU_CLASS_PTR lf_entrys[BX_LF_INDEX_OSZAPC].instr = BX_INSTR_XOR8;
	BX_CPU_CLASS_PTR lf_flags_status = BX_LF_MASK_OSZAPC;
#endif //#if (HOST_CPU_IS_I80386==0)
#if (HOST_CPU_IS_I80386==1) 
	Bit32u x86_lf_flags = BX_CPU_CLASS_PTR eflags.x86.eax;
	__asm
	{
		mov dl,op2
		XOR op1,dl
		lahf
		seto al
		mov x86_lf_flags,eax
	}
	BX_CPU_CLASS_PTR eflags.x86.eax = x86_lf_flags;
#endif //#if (HOST_CPU_IS_I80386==1)

}

	void
BX_CPU_C::XOR_EGwIw(BX_CPU_C *icpu,bxInstruction_c *i)
{
	Bit16u op1, op2, sum;

	op1 = READ_VIRTUAL_16BIT_REG(MODRMrm(i));

	op2 = IMMEDIATEIw(i);

	sum = op1 ^ op2;

	WRITE_VIRTUAL_16BIT_REG(MODRMrm(i),sum);

#if (HOST_CPU_IS_I80386==0)
	BX_CPU_CLASS_PTR lf_entrys[BX_LF_INDEX_OSZAPC].result_16 = sum;
	BX_CPU_CLASS_PTR lf_entrys[BX_LF_INDEX_OSZAPC].instr = BX_INSTR_XOR16;
	BX_CPU_CLASS_PTR lf_flags_status = BX_LF_MASK_OSZAPC;
#endif //#if (HOST_CPU_IS_I80386==0)
#if (HOST_CPU_IS_I80386==1) 
	Bit32u x86_lf_flags = BX_CPU_CLASS_PTR eflags.x86.eax;
	__asm
	{
		mov dx,op2
		XOR op1,dx
		lahf
		seto al
		mov x86_lf_flags,eax
	}
	BX_CPU_CLASS_PTR eflags.x86.eax = x86_lf_flags;
#endif //#if (HOST_CPU_IS_I80386==1)

}

	void
BX_CPU_C::XOR_EGdId(BX_CPU_C *icpu,bxInstruction_c *i)
{
	Bit32u op1, op2, sum;

	op1 = READ_VIRTUAL_32BIT_REG(MODRMrm(i));

	op2 = IMMEDIATEId(i);

	sum = op1 ^ op2;

	WRITE_VIRTUAL_32BIT_REG(MODRMrm(i),sum);

#if (HOST_CPU_IS_I80386==0)
	BX_CPU_CLASS_PTR lf_entrys[BX_LF_INDEX_OSZAPC].result_32 = sum;
	BX_CPU_CLASS_PTR lf_entrys[BX_LF_INDEX_OSZAPC].instr = BX_INSTR_XOR32;
	BX_CPU_CLASS_PTR lf_flags_status = BX_LF_MASK_OSZAPC;
#endif //#if (HOST_CPU_IS_I80386==0)
#if (HOST_CPU_IS_I80386==1) 
	Bit32u x86_lf_flags = BX_CPU_CLASS_PTR eflags.x86.eax;
	__asm
	{
		mov edx,op2
		XOR op1,edx
		lahf
		seto al
		mov x86_lf_flags,eax
	}
	BX_CPU_CLASS_PTR eflags.x86.eax = x86_lf_flags;
#endif //#if (HOST_CPU_IS_I80386==1)

}

	void
BX_CPU_C::XOR_ALIb(BX_CPU_C *icpu,bxInstruction_c *i)
{
	Bit8u op1, op2, sum;

	op1 = READ_VIRTUAL_8BIT_REG(0);

	op2 = IMMEDIATEIb(i);

	sum = op1 ^ op2;

	WRITE_VIRTUAL_8BIT_REG(0,sum);

#if (HOST_CPU_IS_I80386==0)
	BX_CPU_CLASS_PTR lf_entrys[BX_LF_INDEX_OSZAPC].result_8 = sum;
	BX_CPU_CLASS_PTR lf_entrys[BX_LF_INDEX_OSZAPC].instr = BX_INSTR_XOR8;
	BX_CPU_CLASS_PTR lf_flags_status = BX_LF_MASK_OSZAPC;
#endif //#if (HOST_CPU_IS_I80386==0)
#if (HOST_CPU_IS_I80386==1) 
	Bit32u x86_lf_flags = BX_CPU_CLASS_PTR eflags.x86.eax;
	__asm
	{
		mov dl,op2
		XOR op1,dl
		lahf
		seto al
		mov x86_lf_flags,eax
	}
	BX_CPU_CLASS_PTR eflags.x86.eax = x86_lf_flags;
#endif //#if (HOST_CPU_IS_I80386==1)

}

	void
BX_CPU_C::XOR_AXIw(BX_CPU_C *icpu,bxInstruction_c *i)
{
	Bit16u op1, op2, sum;

	op1 = READ_VIRTUAL_16BIT_REG(0);

	op2 = IMMEDIATEIw(i);

	sum = op1 ^ op2;

	WRITE_VIRTUAL_16BIT_REG(0,sum);

#if (HOST_CPU_IS_I80386==0)
	BX_CPU_CLASS_PTR lf_entrys[BX_LF_INDEX_OSZAPC].result_16 = sum;
	BX_CPU_CLASS_PTR lf_entrys[BX_LF_INDEX_OSZAPC].instr = BX_INSTR_XOR16;
	BX_CPU_CLASS_PTR lf_flags_status = BX_LF_MASK_OSZAPC;
#endif //#if (HOST_CPU_IS_I80386==0)
#if (HOST_CPU_IS_I80386==1) 
	Bit32u x86_lf_flags = BX_CPU_CLASS_PTR eflags.x86.eax;
	__asm
	{
		mov dx,op2
		XOR op1,dx
		lahf
		seto al
		mov x86_lf_flags,eax
	}
	BX_CPU_CLASS_PTR eflags.x86.eax = x86_lf_flags;
#endif //#if (HOST_CPU_IS_I80386==1)

}

	void
BX_CPU_C::XOR_EAXId(BX_CPU_C *icpu,bxInstruction_c *i)
{
	Bit32u op1, op2, sum;

	op1 = READ_VIRTUAL_32BIT_REG(0);

	op2 = IMMEDIATEId(i);

	sum = op1 ^ op2;

	WRITE_VIRTUAL_32BIT_REG(0,sum);

#if (HOST_CPU_IS_I80386==0)
	BX_CPU_CLASS_PTR lf_entrys[BX_LF_INDEX_OSZAPC].result_32 = sum;
	BX_CPU_CLASS_PTR lf_entrys[BX_LF_INDEX_OSZAPC].instr = BX_INSTR_XOR32;
	BX_CPU_CLASS_PTR lf_flags_status = BX_LF_MASK_OSZAPC;
#endif //#if (HOST_CPU_IS_I80386==0)
#if (HOST_CPU_IS_I80386==1) 
	Bit32u x86_lf_flags = BX_CPU_CLASS_PTR eflags.x86.eax;
	__asm
	{
		mov edx,op2
		XOR op1,edx
		lahf
		seto al
		mov x86_lf_flags,eax
	}
	BX_CPU_CLASS_PTR eflags.x86.eax = x86_lf_flags;
#endif //#if (HOST_CPU_IS_I80386==1)

}

	void
BX_CPU_C::XOR_EEbGb(BX_CPU_C *icpu,bxInstruction_c *i)
{
	Bit8u op1, op2, sum;

	READ_RMW_VIRTUAL_BYTE(MODRMSeg(i),RMAddr(i),&op1);

	op2 = READ_VIRTUAL_8BIT_REG(MODRMnnn(i));

	sum = op1 ^ op2;

	WRITE_RMW_VIRTUAL_BYTE(sum);

#if (HOST_CPU_IS_I80386==0)
	BX_CPU_CLASS_PTR lf_entrys[BX_LF_INDEX_OSZAPC].result_8 = sum;
	BX_CPU_CLASS_PTR lf_entrys[BX_LF_INDEX_OSZAPC].instr = BX_INSTR_XOR8;
	BX_CPU_CLASS_PTR lf_flags_status = BX_LF_MASK_OSZAPC;
#endif //#if (HOST_CPU_IS_I80386==0)
#if (HOST_CPU_IS_I80386==1) 
	Bit32u x86_lf_flags = BX_CPU_CLASS_PTR eflags.x86.eax;
	__asm
	{
		mov dl,op2
		XOR op1,dl
		lahf
		seto al
		mov x86_lf_flags,eax
	}
	BX_CPU_CLASS_PTR eflags.x86.eax = x86_lf_flags;
#endif //#if (HOST_CPU_IS_I80386==1)

}

	void
BX_CPU_C::XOR_EEwGw(BX_CPU_C *icpu,bxInstruction_c *i)
{
	Bit16u op1, op2, sum;

	READ_RMW_VIRTUAL_WORD(MODRMSeg(i),RMAddr(i),&op1);

	op2 = READ_VIRTUAL_16BIT_REG(MODRMnnn(i));

	sum = op1 ^ op2;

	WRITE_RMW_VIRTUAL_WORD(sum);

#if (HOST_CPU_IS_I80386==0)
	BX_CPU_CLASS_PTR lf_entrys[BX_LF_INDEX_OSZAPC].result_16 = sum;
	BX_CPU_CLASS_PTR lf_entrys[BX_LF_INDEX_OSZAPC].instr = BX_INSTR_XOR16;
	BX_CPU_CLASS_PTR lf_flags_status = BX_LF_MASK_OSZAPC;
#endif //#if (HOST_CPU_IS_I80386==0)
#if (HOST_CPU_IS_I80386==1) 
	Bit32u x86_lf_flags = BX_CPU_CLASS_PTR eflags.x86.eax;
	__asm
	{
		mov dx,op2
		XOR op1,dx
		lahf
		seto al
		mov x86_lf_flags,eax
	}
	BX_CPU_CLASS_PTR eflags.x86.eax = x86_lf_flags;
#endif //#if (HOST_CPU_IS_I80386==1)

}

	void
BX_CPU_C::XOR_EEdGd(BX_CPU_C *icpu,bxInstruction_c *i)
{
	Bit32u op1, op2, sum;

	READ_RMW_VIRTUAL_DWORD(MODRMSeg(i),RMAddr(i),&op1);

	op2 = READ_VIRTUAL_32BIT_REG(MODRMnnn(i));

	sum = op1 ^ op2;

	WRITE_RMW_VIRTUAL_DWORD(sum);

#if (HOST_CPU_IS_I80386==0)
	BX_CPU_CLASS_PTR lf_entrys[BX_LF_INDEX_OSZAPC].result_32 = sum;
	BX_CPU_CLASS_PTR lf_entrys[BX_LF_INDEX_OSZAPC].instr = BX_INSTR_XOR32;
	BX_CPU_CLASS_PTR lf_flags_status = BX_LF_MASK_OSZAPC;
#endif //#if (HOST_CPU_IS_I80386==0)
#if (HOST_CPU_IS_I80386==1) 
	Bit32u x86_lf_flags = BX_CPU_CLASS_PTR eflags.x86.eax;
	__asm
	{
		mov edx,op2
		XOR op1,edx
		lahf
		seto al
		mov x86_lf_flags,eax
	}
	BX_CPU_CLASS_PTR eflags.x86.eax = x86_lf_flags;
#endif //#if (HOST_CPU_IS_I80386==1)

}

	void
BX_CPU_C::XOR_GbEEb(BX_CPU_C *icpu,bxInstruction_c *i)
{
	Bit8u op1, op2, sum;

	op1 = READ_VIRTUAL_8BIT_REG(MODRMnnn(i));

	READ_VIRTUAL_BYTE(MODRMSeg(i),RMAddr(i),&op2);

	sum = op1 ^ op2;

	WRITE_VIRTUAL_8BIT_REG(MODRMnnn(i),sum);

#if (HOST_CPU_IS_I80386==0)
	BX_CPU_CLASS_PTR lf_entrys[BX_LF_INDEX_OSZAPC].result_8 = sum;
	BX_CPU_CLASS_PTR lf_entrys[BX_LF_INDEX_OSZAPC].instr = BX_INSTR_XOR8;
	BX_CPU_CLASS_PTR lf_flags_status = BX_LF_MASK_OSZAPC;
#endif //#if (HOST_CPU_IS_I80386==0)
#if (HOST_CPU_IS_I80386==1) 
	Bit32u x86_lf_flags = BX_CPU_CLASS_PTR eflags.x86.eax;
	__asm
	{
		mov dl,op2
		XOR op1,dl
		lahf
		seto al
		mov x86_lf_flags,eax
	}
	BX_CPU_CLASS_PTR eflags.x86.eax = x86_lf_flags;
#endif //#if (HOST_CPU_IS_I80386==1)

}

	void
BX_CPU_C::XOR_GwEEw(BX_CPU_C *icpu,bxInstruction_c *i)
{
	Bit16u op1, op2, sum;

	op1 = READ_VIRTUAL_16BIT_REG(MODRMnnn(i));

	READ_VIRTUAL_WORD(MODRMSeg(i),RMAddr(i),&op2);

	sum = op1 ^ op2;

	WRITE_VIRTUAL_16BIT_REG(MODRMnnn(i),sum);

#if (HOST_CPU_IS_I80386==0)
	BX_CPU_CLASS_PTR lf_entrys[BX_LF_INDEX_OSZAPC].result_16 = sum;
	BX_CPU_CLASS_PTR lf_entrys[BX_LF_INDEX_OSZAPC].instr = BX_INSTR_XOR16;
	BX_CPU_CLASS_PTR lf_flags_status = BX_LF_MASK_OSZAPC;
#endif //#if (HOST_CPU_IS_I80386==0)
#if (HOST_CPU_IS_I80386==1) 
	Bit32u x86_lf_flags = BX_CPU_CLASS_PTR eflags.x86.eax;
	__asm
	{
		mov dx,op2
		XOR op1,dx
		lahf
		seto al
		mov x86_lf_flags,eax
	}
	BX_CPU_CLASS_PTR eflags.x86.eax = x86_lf_flags;
#endif //#if (HOST_CPU_IS_I80386==1)

}

	void
BX_CPU_C::XOR_GdEEd(BX_CPU_C *icpu,bxInstruction_c *i)
{
	Bit32u op1, op2, sum;

	op1 = READ_VIRTUAL_32BIT_REG(MODRMnnn(i));

	READ_VIRTUAL_DWORD(MODRMSeg(i),RMAddr(i),&op2);

	sum = op1 ^ op2;

	WRITE_VIRTUAL_32BIT_REG(MODRMnnn(i),sum);

#if (HOST_CPU_IS_I80386==0)
	BX_CPU_CLASS_PTR lf_entrys[BX_LF_INDEX_OSZAPC].result_32 = sum;
	BX_CPU_CLASS_PTR lf_entrys[BX_LF_INDEX_OSZAPC].instr = BX_INSTR_XOR32;
	BX_CPU_CLASS_PTR lf_flags_status = BX_LF_MASK_OSZAPC;
#endif //#if (HOST_CPU_IS_I80386==0)
#if (HOST_CPU_IS_I80386==1) 
	Bit32u x86_lf_flags = BX_CPU_CLASS_PTR eflags.x86.eax;
	__asm
	{
		mov edx,op2
		XOR op1,edx
		lahf
		seto al
		mov x86_lf_flags,eax
	}
	BX_CPU_CLASS_PTR eflags.x86.eax = x86_lf_flags;
#endif //#if (HOST_CPU_IS_I80386==1)

}

	void
BX_CPU_C::XOR_EEbIb(BX_CPU_C *icpu,bxInstruction_c *i)
{
	Bit8u op1, op2, sum;

	READ_RMW_VIRTUAL_BYTE(MODRMSeg(i),RMAddr(i),&op1);

	op2 = IMMEDIATEIb(i);

	sum = op1 ^ op2;

	WRITE_RMW_VIRTUAL_BYTE(sum);

#if (HOST_CPU_IS_I80386==0)
	BX_CPU_CLASS_PTR lf_entrys[BX_LF_INDEX_OSZAPC].result_8 = sum;
	BX_CPU_CLASS_PTR lf_entrys[BX_LF_INDEX_OSZAPC].instr = BX_INSTR_XOR8;
	BX_CPU_CLASS_PTR lf_flags_status = BX_LF_MASK_OSZAPC;
#endif //#if (HOST_CPU_IS_I80386==0)
#if (HOST_CPU_IS_I80386==1) 
	Bit32u x86_lf_flags = BX_CPU_CLASS_PTR eflags.x86.eax;
	__asm
	{
		mov dl,op2
		XOR op1,dl
		lahf
		seto al
		mov x86_lf_flags,eax
	}
	BX_CPU_CLASS_PTR eflags.x86.eax = x86_lf_flags;
#endif //#if (HOST_CPU_IS_I80386==1)

}

	void
BX_CPU_C::XOR_EEwIw(BX_CPU_C *icpu,bxInstruction_c *i)
{
	Bit16u op1, op2, sum;

	READ_RMW_VIRTUAL_WORD(MODRMSeg(i),RMAddr(i),&op1);

	op2 = IMMEDIATEIw(i);

	sum = op1 ^ op2;

	WRITE_RMW_VIRTUAL_WORD(sum);

#if (HOST_CPU_IS_I80386==0)
	BX_CPU_CLASS_PTR lf_entrys[BX_LF_INDEX_OSZAPC].result_16 = sum;
	BX_CPU_CLASS_PTR lf_entrys[BX_LF_INDEX_OSZAPC].instr = BX_INSTR_XOR16;
	BX_CPU_CLASS_PTR lf_flags_status = BX_LF_MASK_OSZAPC;
#endif //#if (HOST_CPU_IS_I80386==0)
#if (HOST_CPU_IS_I80386==1) 
	Bit32u x86_lf_flags = BX_CPU_CLASS_PTR eflags.x86.eax;
	__asm
	{
		mov dx,op2
		XOR op1,dx
		lahf
		seto al
		mov x86_lf_flags,eax
	}
	BX_CPU_CLASS_PTR eflags.x86.eax = x86_lf_flags;
#endif //#if (HOST_CPU_IS_I80386==1)

}

	void
BX_CPU_C::XOR_EEdId(BX_CPU_C *icpu,bxInstruction_c *i)
{
	Bit32u op1, op2, sum;

	READ_RMW_VIRTUAL_DWORD(MODRMSeg(i),RMAddr(i),&op1);

	op2 = IMMEDIATEId(i);

	sum = op1 ^ op2;

	WRITE_RMW_VIRTUAL_DWORD(sum);

#if (HOST_CPU_IS_I80386==0)
	BX_CPU_CLASS_PTR lf_entrys[BX_LF_INDEX_OSZAPC].result_32 = sum;
	BX_CPU_CLASS_PTR lf_entrys[BX_LF_INDEX_OSZAPC].instr = BX_INSTR_XOR32;
	BX_CPU_CLASS_PTR lf_flags_status = BX_LF_MASK_OSZAPC;
#endif //#if (HOST_CPU_IS_I80386==0)
#if (HOST_CPU_IS_I80386==1) 
	Bit32u x86_lf_flags = BX_CPU_CLASS_PTR eflags.x86.eax;
	__asm
	{
		mov edx,op2
		XOR op1,edx
		lahf
		seto al
		mov x86_lf_flags,eax
	}
	BX_CPU_CLASS_PTR eflags.x86.eax = x86_lf_flags;
#endif //#if (HOST_CPU_IS_I80386==1)

}

	void
BX_CPU_C:: OR_EGbGb(BX_CPU_C *icpu,bxInstruction_c *i)
{
	Bit8u op1, op2, sum;

	op1 = READ_VIRTUAL_8BIT_REG(MODRMrm(i));

	op2 = READ_VIRTUAL_8BIT_REG(MODRMnnn(i));

	sum = op1 | op2;

	WRITE_VIRTUAL_8BIT_REG(MODRMrm(i), sum);

#if (HOST_CPU_IS_I80386==0)
	BX_CPU_CLASS_PTR lf_entrys[BX_LF_INDEX_OSZAPC].result_8 = sum;
	BX_CPU_CLASS_PTR lf_entrys[BX_LF_INDEX_OSZAPC].instr = BX_INSTR_OR8;
	BX_CPU_CLASS_PTR lf_flags_status = BX_LF_MASK_OSZAPC;
#endif //#if (HOST_CPU_IS_I80386==0)
#if (HOST_CPU_IS_I80386==1) 
	Bit32u x86_lf_flags = BX_CPU_CLASS_PTR eflags.x86.eax;
	__asm
	{
		mov dl,op2
		OR op1,dl
		lahf
		seto al
		mov x86_lf_flags,eax
	}
	BX_CPU_CLASS_PTR eflags.x86.eax = x86_lf_flags;
#endif //#if (HOST_CPU_IS_I80386==1)

}

	void
BX_CPU_C:: OR_EGwGw(BX_CPU_C *icpu,bxInstruction_c *i)
{
	Bit16u op1, op2, sum;

	op1 = READ_VIRTUAL_16BIT_REG(MODRMrm(i));

	op2 = READ_VIRTUAL_16BIT_REG(MODRMnnn(i));

	sum = op1 | op2;

	WRITE_VIRTUAL_16BIT_REG(MODRMrm(i), sum);

#if (HOST_CPU_IS_I80386==0)
	BX_CPU_CLASS_PTR lf_entrys[BX_LF_INDEX_OSZAPC].result_16 = sum;
	BX_CPU_CLASS_PTR lf_entrys[BX_LF_INDEX_OSZAPC].instr = BX_INSTR_OR16;
	BX_CPU_CLASS_PTR lf_flags_status = BX_LF_MASK_OSZAPC;
#endif //#if (HOST_CPU_IS_I80386==0)
#if (HOST_CPU_IS_I80386==1) 
	Bit32u x86_lf_flags = BX_CPU_CLASS_PTR eflags.x86.eax;
	__asm
	{
		mov dx,op2
		OR op1,dx
		lahf
		seto al
		mov x86_lf_flags,eax
	}
	BX_CPU_CLASS_PTR eflags.x86.eax = x86_lf_flags;
#endif //#if (HOST_CPU_IS_I80386==1)

}

	void
BX_CPU_C:: OR_EGdGd(BX_CPU_C *icpu,bxInstruction_c *i)
{
	Bit32u op1, op2, sum;

	op1 = READ_VIRTUAL_32BIT_REG(MODRMrm(i));

	op2 = READ_VIRTUAL_32BIT_REG(MODRMnnn(i));

	sum = op1 | op2;

	WRITE_VIRTUAL_32BIT_REG(MODRMrm(i), sum);

#if (HOST_CPU_IS_I80386==0)
	BX_CPU_CLASS_PTR lf_entrys[BX_LF_INDEX_OSZAPC].result_32 = sum;
	BX_CPU_CLASS_PTR lf_entrys[BX_LF_INDEX_OSZAPC].instr = BX_INSTR_OR32;
	BX_CPU_CLASS_PTR lf_flags_status = BX_LF_MASK_OSZAPC;
#endif //#if (HOST_CPU_IS_I80386==0)
#if (HOST_CPU_IS_I80386==1) 
	Bit32u x86_lf_flags = BX_CPU_CLASS_PTR eflags.x86.eax;
	__asm
	{
		mov edx,op2
		OR op1,edx
		lahf
		seto al
		mov x86_lf_flags,eax
	}
	BX_CPU_CLASS_PTR eflags.x86.eax = x86_lf_flags;
#endif //#if (HOST_CPU_IS_I80386==1)

}

	void
BX_CPU_C:: OR_GbEGb(BX_CPU_C *icpu,bxInstruction_c *i)
{
	Bit8u op1, op2, sum;

	op1 = READ_VIRTUAL_8BIT_REG(MODRMnnn(i));

	op2 = READ_VIRTUAL_8BIT_REG(MODRMrm(i));

	sum = op1 | op2;

	WRITE_VIRTUAL_8BIT_REG(MODRMnnn(i),sum);

#if (HOST_CPU_IS_I80386==0)
	BX_CPU_CLASS_PTR lf_entrys[BX_LF_INDEX_OSZAPC].result_8 = sum;
	BX_CPU_CLASS_PTR lf_entrys[BX_LF_INDEX_OSZAPC].instr = BX_INSTR_OR8;
	BX_CPU_CLASS_PTR lf_flags_status = BX_LF_MASK_OSZAPC;
#endif //#if (HOST_CPU_IS_I80386==0)
#if (HOST_CPU_IS_I80386==1) 
	Bit32u x86_lf_flags = BX_CPU_CLASS_PTR eflags.x86.eax;
	__asm
	{
		mov dl,op2
		OR op1,dl
		lahf
		seto al
		mov x86_lf_flags,eax
	}
	BX_CPU_CLASS_PTR eflags.x86.eax = x86_lf_flags;
#endif //#if (HOST_CPU_IS_I80386==1)

}

	void
BX_CPU_C:: OR_GwEGw(BX_CPU_C *icpu,bxInstruction_c *i)
{
	Bit16u op1, op2, sum;

	op1 = READ_VIRTUAL_16BIT_REG(MODRMnnn(i));

	op2 = READ_VIRTUAL_16BIT_REG(MODRMrm(i));

	sum = op1 | op2;

	WRITE_VIRTUAL_16BIT_REG(MODRMnnn(i),sum);

#if (HOST_CPU_IS_I80386==0)
	BX_CPU_CLASS_PTR lf_entrys[BX_LF_INDEX_OSZAPC].result_16 = sum;
	BX_CPU_CLASS_PTR lf_entrys[BX_LF_INDEX_OSZAPC].instr = BX_INSTR_OR16;
	BX_CPU_CLASS_PTR lf_flags_status = BX_LF_MASK_OSZAPC;
#endif //#if (HOST_CPU_IS_I80386==0)
#if (HOST_CPU_IS_I80386==1) 
	Bit32u x86_lf_flags = BX_CPU_CLASS_PTR eflags.x86.eax;
	__asm
	{
		mov dx,op2
		OR op1,dx
		lahf
		seto al
		mov x86_lf_flags,eax
	}
	BX_CPU_CLASS_PTR eflags.x86.eax = x86_lf_flags;
#endif //#if (HOST_CPU_IS_I80386==1)

}

	void
BX_CPU_C:: OR_GdEGd(BX_CPU_C *icpu,bxInstruction_c *i)
{
	Bit32u op1, op2, sum;

	op1 = READ_VIRTUAL_32BIT_REG(MODRMnnn(i));

	op2 = READ_VIRTUAL_32BIT_REG(MODRMrm(i));

	sum = op1 | op2;

	WRITE_VIRTUAL_32BIT_REG(MODRMnnn(i),sum);

#if (HOST_CPU_IS_I80386==0)
	BX_CPU_CLASS_PTR lf_entrys[BX_LF_INDEX_OSZAPC].result_32 = sum;
	BX_CPU_CLASS_PTR lf_entrys[BX_LF_INDEX_OSZAPC].instr = BX_INSTR_OR32;
	BX_CPU_CLASS_PTR lf_flags_status = BX_LF_MASK_OSZAPC;
#endif //#if (HOST_CPU_IS_I80386==0)
#if (HOST_CPU_IS_I80386==1) 
	Bit32u x86_lf_flags = BX_CPU_CLASS_PTR eflags.x86.eax;
	__asm
	{
		mov edx,op2
		OR op1,edx
		lahf
		seto al
		mov x86_lf_flags,eax
	}
	BX_CPU_CLASS_PTR eflags.x86.eax = x86_lf_flags;
#endif //#if (HOST_CPU_IS_I80386==1)

}

	void
BX_CPU_C:: OR_EGbIb(BX_CPU_C *icpu,bxInstruction_c *i)
{
	Bit8u op1, op2, sum;

	op1 = READ_VIRTUAL_8BIT_REG(MODRMrm(i));

	op2 = IMMEDIATEIb(i);

	sum = op1 | op2;

	WRITE_VIRTUAL_8BIT_REG(MODRMrm(i),sum);

#if (HOST_CPU_IS_I80386==0)
	BX_CPU_CLASS_PTR lf_entrys[BX_LF_INDEX_OSZAPC].result_8 = sum;
	BX_CPU_CLASS_PTR lf_entrys[BX_LF_INDEX_OSZAPC].instr = BX_INSTR_OR8;
	BX_CPU_CLASS_PTR lf_flags_status = BX_LF_MASK_OSZAPC;
#endif //#if (HOST_CPU_IS_I80386==0)
#if (HOST_CPU_IS_I80386==1) 
	Bit32u x86_lf_flags = BX_CPU_CLASS_PTR eflags.x86.eax;
	__asm
	{
		mov dl,op2
		OR op1,dl
		lahf
		seto al
		mov x86_lf_flags,eax
	}
	BX_CPU_CLASS_PTR eflags.x86.eax = x86_lf_flags;
#endif //#if (HOST_CPU_IS_I80386==1)

}

	void
BX_CPU_C:: OR_EGwIw(BX_CPU_C *icpu,bxInstruction_c *i)
{
	Bit16u op1, op2, sum;

	op1 = READ_VIRTUAL_16BIT_REG(MODRMrm(i));

	op2 = IMMEDIATEIw(i);

	sum = op1 | op2;

	WRITE_VIRTUAL_16BIT_REG(MODRMrm(i),sum);

#if (HOST_CPU_IS_I80386==0)
	BX_CPU_CLASS_PTR lf_entrys[BX_LF_INDEX_OSZAPC].result_16 = sum;
	BX_CPU_CLASS_PTR lf_entrys[BX_LF_INDEX_OSZAPC].instr = BX_INSTR_OR16;
	BX_CPU_CLASS_PTR lf_flags_status = BX_LF_MASK_OSZAPC;
#endif //#if (HOST_CPU_IS_I80386==0)
#if (HOST_CPU_IS_I80386==1) 
	Bit32u x86_lf_flags = BX_CPU_CLASS_PTR eflags.x86.eax;
	__asm
	{
		mov dx,op2
		OR op1,dx
		lahf
		seto al
		mov x86_lf_flags,eax
	}
	BX_CPU_CLASS_PTR eflags.x86.eax = x86_lf_flags;
#endif //#if (HOST_CPU_IS_I80386==1)

}

	void
BX_CPU_C:: OR_EGdId(BX_CPU_C *icpu,bxInstruction_c *i)
{
	Bit32u op1, op2, sum;

	op1 = READ_VIRTUAL_32BIT_REG(MODRMrm(i));

	op2 = IMMEDIATEId(i);

	sum = op1 | op2;

	WRITE_VIRTUAL_32BIT_REG(MODRMrm(i),sum);

#if (HOST_CPU_IS_I80386==0)
	BX_CPU_CLASS_PTR lf_entrys[BX_LF_INDEX_OSZAPC].result_32 = sum;
	BX_CPU_CLASS_PTR lf_entrys[BX_LF_INDEX_OSZAPC].instr = BX_INSTR_OR32;
	BX_CPU_CLASS_PTR lf_flags_status = BX_LF_MASK_OSZAPC;
#endif //#if (HOST_CPU_IS_I80386==0)
#if (HOST_CPU_IS_I80386==1) 
	Bit32u x86_lf_flags = BX_CPU_CLASS_PTR eflags.x86.eax;
	__asm
	{
		mov edx,op2
		OR op1,edx
		lahf
		seto al
		mov x86_lf_flags,eax
	}
	BX_CPU_CLASS_PTR eflags.x86.eax = x86_lf_flags;
#endif //#if (HOST_CPU_IS_I80386==1)

}

	void
BX_CPU_C:: OR_ALIb(BX_CPU_C *icpu,bxInstruction_c *i)
{
	Bit8u op1, op2, sum;

	op1 = READ_VIRTUAL_8BIT_REG(0);

	op2 = IMMEDIATEIb(i);

	sum = op1 | op2;

	WRITE_VIRTUAL_8BIT_REG(0,sum);

#if (HOST_CPU_IS_I80386==0)
	BX_CPU_CLASS_PTR lf_entrys[BX_LF_INDEX_OSZAPC].result_8 = sum;
	BX_CPU_CLASS_PTR lf_entrys[BX_LF_INDEX_OSZAPC].instr = BX_INSTR_OR8;
	BX_CPU_CLASS_PTR lf_flags_status = BX_LF_MASK_OSZAPC;
#endif //#if (HOST_CPU_IS_I80386==0)
#if (HOST_CPU_IS_I80386==1) 
	Bit32u x86_lf_flags = BX_CPU_CLASS_PTR eflags.x86.eax;
	__asm
	{
		mov dl,op2
		OR op1,dl
		lahf
		seto al
		mov x86_lf_flags,eax
	}
	BX_CPU_CLASS_PTR eflags.x86.eax = x86_lf_flags;
#endif //#if (HOST_CPU_IS_I80386==1)

}

	void
BX_CPU_C:: OR_AXIw(BX_CPU_C *icpu,bxInstruction_c *i)
{
	Bit16u op1, op2, sum;

	op1 = READ_VIRTUAL_16BIT_REG(0);

	op2 = IMMEDIATEIw(i);

	sum = op1 | op2;

	WRITE_VIRTUAL_16BIT_REG(0,sum);

#if (HOST_CPU_IS_I80386==0)
	BX_CPU_CLASS_PTR lf_entrys[BX_LF_INDEX_OSZAPC].result_16 = sum;
	BX_CPU_CLASS_PTR lf_entrys[BX_LF_INDEX_OSZAPC].instr = BX_INSTR_OR16;
	BX_CPU_CLASS_PTR lf_flags_status = BX_LF_MASK_OSZAPC;
#endif //#if (HOST_CPU_IS_I80386==0)
#if (HOST_CPU_IS_I80386==1) 
	Bit32u x86_lf_flags = BX_CPU_CLASS_PTR eflags.x86.eax;
	__asm
	{
		mov dx,op2
		OR op1,dx
		lahf
		seto al
		mov x86_lf_flags,eax
	}
	BX_CPU_CLASS_PTR eflags.x86.eax = x86_lf_flags;
#endif //#if (HOST_CPU_IS_I80386==1)

}

	void
BX_CPU_C:: OR_EAXId(BX_CPU_C *icpu,bxInstruction_c *i)
{
	Bit32u op1, op2, sum;

	op1 = READ_VIRTUAL_32BIT_REG(0);

	op2 = IMMEDIATEId(i);

	sum = op1 | op2;

	WRITE_VIRTUAL_32BIT_REG(0,sum);

#if (HOST_CPU_IS_I80386==0)
	BX_CPU_CLASS_PTR lf_entrys[BX_LF_INDEX_OSZAPC].result_32 = sum;
	BX_CPU_CLASS_PTR lf_entrys[BX_LF_INDEX_OSZAPC].instr = BX_INSTR_OR32;
	BX_CPU_CLASS_PTR lf_flags_status = BX_LF_MASK_OSZAPC;
#endif //#if (HOST_CPU_IS_I80386==0)
#if (HOST_CPU_IS_I80386==1) 
	Bit32u x86_lf_flags = BX_CPU_CLASS_PTR eflags.x86.eax;
	__asm
	{
		mov edx,op2
		OR op1,edx
		lahf
		seto al
		mov x86_lf_flags,eax
	}
	BX_CPU_CLASS_PTR eflags.x86.eax = x86_lf_flags;
#endif //#if (HOST_CPU_IS_I80386==1)

}

	void
BX_CPU_C:: OR_EEbGb(BX_CPU_C *icpu,bxInstruction_c *i)
{
	Bit8u op1, op2, sum;

	READ_RMW_VIRTUAL_BYTE(MODRMSeg(i),RMAddr(i),&op1);

	op2 = READ_VIRTUAL_8BIT_REG(MODRMnnn(i));

	sum = op1 | op2;

	WRITE_RMW_VIRTUAL_BYTE(sum);

#if (HOST_CPU_IS_I80386==0)
	BX_CPU_CLASS_PTR lf_entrys[BX_LF_INDEX_OSZAPC].result_8 = sum;
	BX_CPU_CLASS_PTR lf_entrys[BX_LF_INDEX_OSZAPC].instr = BX_INSTR_OR8;
	BX_CPU_CLASS_PTR lf_flags_status = BX_LF_MASK_OSZAPC;
#endif //#if (HOST_CPU_IS_I80386==0)
#if (HOST_CPU_IS_I80386==1) 
	Bit32u x86_lf_flags = BX_CPU_CLASS_PTR eflags.x86.eax;
	__asm
	{
		mov dl,op2
		OR op1,dl
		lahf
		seto al
		mov x86_lf_flags,eax
	}
	BX_CPU_CLASS_PTR eflags.x86.eax = x86_lf_flags;
#endif //#if (HOST_CPU_IS_I80386==1)

}

	void
BX_CPU_C:: OR_EEwGw(BX_CPU_C *icpu,bxInstruction_c *i)
{
	Bit16u op1, op2, sum;

	READ_RMW_VIRTUAL_WORD(MODRMSeg(i),RMAddr(i),&op1);

	op2 = READ_VIRTUAL_16BIT_REG(MODRMnnn(i));

	sum = op1 | op2;

	WRITE_RMW_VIRTUAL_WORD(sum);

#if (HOST_CPU_IS_I80386==0)
	BX_CPU_CLASS_PTR lf_entrys[BX_LF_INDEX_OSZAPC].result_16 = sum;
	BX_CPU_CLASS_PTR lf_entrys[BX_LF_INDEX_OSZAPC].instr = BX_INSTR_OR16;
	BX_CPU_CLASS_PTR lf_flags_status = BX_LF_MASK_OSZAPC;
#endif //#if (HOST_CPU_IS_I80386==0)
#if (HOST_CPU_IS_I80386==1) 
	Bit32u x86_lf_flags = BX_CPU_CLASS_PTR eflags.x86.eax;
	__asm
	{
		mov dx,op2
		OR op1,dx
		lahf
		seto al
		mov x86_lf_flags,eax
	}
	BX_CPU_CLASS_PTR eflags.x86.eax = x86_lf_flags;
#endif //#if (HOST_CPU_IS_I80386==1)

}

	void
BX_CPU_C:: OR_EEdGd(BX_CPU_C *icpu,bxInstruction_c *i)
{
	Bit32u op1, op2, sum;

	READ_RMW_VIRTUAL_DWORD(MODRMSeg(i),RMAddr(i),&op1);

	op2 = READ_VIRTUAL_32BIT_REG(MODRMnnn(i));

	sum = op1 | op2;

	WRITE_RMW_VIRTUAL_DWORD(sum);

#if (HOST_CPU_IS_I80386==0)
	BX_CPU_CLASS_PTR lf_entrys[BX_LF_INDEX_OSZAPC].result_32 = sum;
	BX_CPU_CLASS_PTR lf_entrys[BX_LF_INDEX_OSZAPC].instr = BX_INSTR_OR32;
	BX_CPU_CLASS_PTR lf_flags_status = BX_LF_MASK_OSZAPC;
#endif //#if (HOST_CPU_IS_I80386==0)
#if (HOST_CPU_IS_I80386==1) 
	Bit32u x86_lf_flags = BX_CPU_CLASS_PTR eflags.x86.eax;
	__asm
	{
		mov edx,op2
		OR op1,edx
		lahf
		seto al
		mov x86_lf_flags,eax
	}
	BX_CPU_CLASS_PTR eflags.x86.eax = x86_lf_flags;
#endif //#if (HOST_CPU_IS_I80386==1)

}

	void
BX_CPU_C:: OR_GbEEb(BX_CPU_C *icpu,bxInstruction_c *i)
{
	Bit8u op1, op2, sum;

	op1 = READ_VIRTUAL_8BIT_REG(MODRMnnn(i));

	READ_VIRTUAL_BYTE(MODRMSeg(i),RMAddr(i),&op2);

	sum = op1 | op2;

	WRITE_VIRTUAL_8BIT_REG(MODRMnnn(i),sum);

#if (HOST_CPU_IS_I80386==0)
	BX_CPU_CLASS_PTR lf_entrys[BX_LF_INDEX_OSZAPC].result_8 = sum;
	BX_CPU_CLASS_PTR lf_entrys[BX_LF_INDEX_OSZAPC].instr = BX_INSTR_OR8;
	BX_CPU_CLASS_PTR lf_flags_status = BX_LF_MASK_OSZAPC;
#endif //#if (HOST_CPU_IS_I80386==0)
#if (HOST_CPU_IS_I80386==1) 
	Bit32u x86_lf_flags = BX_CPU_CLASS_PTR eflags.x86.eax;
	__asm
	{
		mov dl,op2
		OR op1,dl
		lahf
		seto al
		mov x86_lf_flags,eax
	}
	BX_CPU_CLASS_PTR eflags.x86.eax = x86_lf_flags;
#endif //#if (HOST_CPU_IS_I80386==1)

}

	void
BX_CPU_C:: OR_GwEEw(BX_CPU_C *icpu,bxInstruction_c *i)
{
	Bit16u op1, op2, sum;

	op1 = READ_VIRTUAL_16BIT_REG(MODRMnnn(i));

	READ_VIRTUAL_WORD(MODRMSeg(i),RMAddr(i),&op2);

	sum = op1 | op2;

	WRITE_VIRTUAL_16BIT_REG(MODRMnnn(i),sum);

#if (HOST_CPU_IS_I80386==0)
	BX_CPU_CLASS_PTR lf_entrys[BX_LF_INDEX_OSZAPC].result_16 = sum;
	BX_CPU_CLASS_PTR lf_entrys[BX_LF_INDEX_OSZAPC].instr = BX_INSTR_OR16;
	BX_CPU_CLASS_PTR lf_flags_status = BX_LF_MASK_OSZAPC;
#endif //#if (HOST_CPU_IS_I80386==0)
#if (HOST_CPU_IS_I80386==1) 
	Bit32u x86_lf_flags = BX_CPU_CLASS_PTR eflags.x86.eax;
	__asm
	{
		mov dx,op2
		OR op1,dx
		lahf
		seto al
		mov x86_lf_flags,eax
	}
	BX_CPU_CLASS_PTR eflags.x86.eax = x86_lf_flags;
#endif //#if (HOST_CPU_IS_I80386==1)

}

	void
BX_CPU_C:: OR_GdEEd(BX_CPU_C *icpu,bxInstruction_c *i)
{
	Bit32u op1, op2, sum;

	op1 = READ_VIRTUAL_32BIT_REG(MODRMnnn(i));

	READ_VIRTUAL_DWORD(MODRMSeg(i),RMAddr(i),&op2);

	sum = op1 | op2;

	WRITE_VIRTUAL_32BIT_REG(MODRMnnn(i),sum);

#if (HOST_CPU_IS_I80386==0)
	BX_CPU_CLASS_PTR lf_entrys[BX_LF_INDEX_OSZAPC].result_32 = sum;
	BX_CPU_CLASS_PTR lf_entrys[BX_LF_INDEX_OSZAPC].instr = BX_INSTR_OR32;
	BX_CPU_CLASS_PTR lf_flags_status = BX_LF_MASK_OSZAPC;
#endif //#if (HOST_CPU_IS_I80386==0)
#if (HOST_CPU_IS_I80386==1) 
	Bit32u x86_lf_flags = BX_CPU_CLASS_PTR eflags.x86.eax;
	__asm
	{
		mov edx,op2
		OR op1,edx
		lahf
		seto al
		mov x86_lf_flags,eax
	}
	BX_CPU_CLASS_PTR eflags.x86.eax = x86_lf_flags;
#endif //#if (HOST_CPU_IS_I80386==1)

}

	void
BX_CPU_C:: OR_EEbIb(BX_CPU_C *icpu,bxInstruction_c *i)
{
	Bit8u op1, op2, sum;

	READ_RMW_VIRTUAL_BYTE(MODRMSeg(i),RMAddr(i),&op1);

	op2 = IMMEDIATEIb(i);

	sum = op1 | op2;

	WRITE_RMW_VIRTUAL_BYTE(sum);

#if (HOST_CPU_IS_I80386==0)
	BX_CPU_CLASS_PTR lf_entrys[BX_LF_INDEX_OSZAPC].result_8 = sum;
	BX_CPU_CLASS_PTR lf_entrys[BX_LF_INDEX_OSZAPC].instr = BX_INSTR_OR8;
	BX_CPU_CLASS_PTR lf_flags_status = BX_LF_MASK_OSZAPC;
#endif //#if (HOST_CPU_IS_I80386==0)
#if (HOST_CPU_IS_I80386==1) 
	Bit32u x86_lf_flags = BX_CPU_CLASS_PTR eflags.x86.eax;
	__asm
	{
		mov dl,op2
		OR op1,dl
		lahf
		seto al
		mov x86_lf_flags,eax
	}
	BX_CPU_CLASS_PTR eflags.x86.eax = x86_lf_flags;
#endif //#if (HOST_CPU_IS_I80386==1)

}

	void
BX_CPU_C:: OR_EEwIw(BX_CPU_C *icpu,bxInstruction_c *i)
{
	Bit16u op1, op2, sum;

	READ_RMW_VIRTUAL_WORD(MODRMSeg(i),RMAddr(i),&op1);

	op2 = IMMEDIATEIw(i);

	sum = op1 | op2;

	WRITE_RMW_VIRTUAL_WORD(sum);

#if (HOST_CPU_IS_I80386==0)
	BX_CPU_CLASS_PTR lf_entrys[BX_LF_INDEX_OSZAPC].result_16 = sum;
	BX_CPU_CLASS_PTR lf_entrys[BX_LF_INDEX_OSZAPC].instr = BX_INSTR_OR16;
	BX_CPU_CLASS_PTR lf_flags_status = BX_LF_MASK_OSZAPC;
#endif //#if (HOST_CPU_IS_I80386==0)
#if (HOST_CPU_IS_I80386==1) 
	Bit32u x86_lf_flags = BX_CPU_CLASS_PTR eflags.x86.eax;
	__asm
	{
		mov dx,op2
		OR op1,dx
		lahf
		seto al
		mov x86_lf_flags,eax
	}
	BX_CPU_CLASS_PTR eflags.x86.eax = x86_lf_flags;
#endif //#if (HOST_CPU_IS_I80386==1)

}

	void
BX_CPU_C:: OR_EEdId(BX_CPU_C *icpu,bxInstruction_c *i)
{
	Bit32u op1, op2, sum;

	READ_RMW_VIRTUAL_DWORD(MODRMSeg(i),RMAddr(i),&op1);

	op2 = IMMEDIATEId(i);

	sum = op1 | op2;

	WRITE_RMW_VIRTUAL_DWORD(sum);

#if (HOST_CPU_IS_I80386==0)
	BX_CPU_CLASS_PTR lf_entrys[BX_LF_INDEX_OSZAPC].result_32 = sum;
	BX_CPU_CLASS_PTR lf_entrys[BX_LF_INDEX_OSZAPC].instr = BX_INSTR_OR32;
	BX_CPU_CLASS_PTR lf_flags_status = BX_LF_MASK_OSZAPC;
#endif //#if (HOST_CPU_IS_I80386==0)
#if (HOST_CPU_IS_I80386==1) 
	Bit32u x86_lf_flags = BX_CPU_CLASS_PTR eflags.x86.eax;
	__asm
	{
		mov edx,op2
		OR op1,edx
		lahf
		seto al
		mov x86_lf_flags,eax
	}
	BX_CPU_CLASS_PTR eflags.x86.eax = x86_lf_flags;
#endif //#if (HOST_CPU_IS_I80386==1)

}

	void
BX_CPU_C::ADC_EGbGb(BX_CPU_C *icpu,bxInstruction_c *i)
{
	Bit8u op1, op2, sum;
	Boolean prev_cf;
	prev_cf = (BX_CPU_CLASS_PTR get_CF());

	op1 = READ_VIRTUAL_8BIT_REG(MODRMrm(i));

	op2 = READ_VIRTUAL_8BIT_REG(MODRMnnn(i));

	sum = op1 + op2 + prev_cf;

	WRITE_VIRTUAL_8BIT_REG(MODRMrm(i), sum);

#if (HOST_CPU_IS_I80386==0)
	SET_FLAGS_OSZAPC_8_CF(op1,op2,sum,BX_INSTR_ADC8,prev_cf);
#endif //#if (HOST_CPU_IS_I80386==0)
#if (HOST_CPU_IS_I80386==1) 
	Bit32u x86_lf_flags = BX_CPU_CLASS_PTR eflags.x86.eax;
	__asm
	{
		mov eax,x86_lf_flags
		sahf
		mov dl,op2
		ADC op1,dl
		lahf
		seto al
		mov x86_lf_flags,eax
	}
	BX_CPU_CLASS_PTR eflags.x86.eax = x86_lf_flags;
#endif //#if (HOST_CPU_IS_I80386==1)

}

	void
BX_CPU_C::ADC_EGwGw(BX_CPU_C *icpu,bxInstruction_c *i)
{
	Bit16u op1, op2, sum;
	Boolean prev_cf;
	prev_cf = (BX_CPU_CLASS_PTR get_CF());

	op1 = READ_VIRTUAL_16BIT_REG(MODRMrm(i));

	op2 = READ_VIRTUAL_16BIT_REG(MODRMnnn(i));

	sum = op1 + op2 + prev_cf;

	WRITE_VIRTUAL_16BIT_REG(MODRMrm(i), sum);

#if (HOST_CPU_IS_I80386==0)
	SET_FLAGS_OSZAPC_16_CF(op1,op2,sum,BX_INSTR_ADC16,prev_cf);
#endif //#if (HOST_CPU_IS_I80386==0)
#if (HOST_CPU_IS_I80386==1) 
	Bit32u x86_lf_flags = BX_CPU_CLASS_PTR eflags.x86.eax;
	__asm
	{
		mov eax,x86_lf_flags
		sahf
		mov dx,op2
		ADC op1,dx
		lahf
		seto al
		mov x86_lf_flags,eax
	}
	BX_CPU_CLASS_PTR eflags.x86.eax = x86_lf_flags;
#endif //#if (HOST_CPU_IS_I80386==1)

}

	void
BX_CPU_C::ADC_EGdGd(BX_CPU_C *icpu,bxInstruction_c *i)
{
	Bit32u op1, op2, sum;
	Boolean prev_cf;
	prev_cf = (BX_CPU_CLASS_PTR get_CF());

	op1 = READ_VIRTUAL_32BIT_REG(MODRMrm(i));

	op2 = READ_VIRTUAL_32BIT_REG(MODRMnnn(i));

	sum = op1 + op2 + prev_cf;

	WRITE_VIRTUAL_32BIT_REG(MODRMrm(i), sum);

#if (HOST_CPU_IS_I80386==0)
	SET_FLAGS_OSZAPC_32_CF(op1,op2,sum,BX_INSTR_ADC32,prev_cf);
#endif //#if (HOST_CPU_IS_I80386==0)
#if (HOST_CPU_IS_I80386==1) 
	Bit32u x86_lf_flags = BX_CPU_CLASS_PTR eflags.x86.eax;
	__asm
	{
		mov eax,x86_lf_flags
		sahf
		mov edx,op2
		ADC op1,edx
		lahf
		seto al
		mov x86_lf_flags,eax
	}
	BX_CPU_CLASS_PTR eflags.x86.eax = x86_lf_flags;
#endif //#if (HOST_CPU_IS_I80386==1)

}

	void
BX_CPU_C::ADC_GbEGb(BX_CPU_C *icpu,bxInstruction_c *i)
{
	Bit8u op1, op2, sum;
	Boolean prev_cf;
	prev_cf = (BX_CPU_CLASS_PTR get_CF());

	op1 = READ_VIRTUAL_8BIT_REG(MODRMnnn(i));

	op2 = READ_VIRTUAL_8BIT_REG(MODRMrm(i));

	sum = op1 + op2 + prev_cf;

	WRITE_VIRTUAL_8BIT_REG(MODRMnnn(i),sum);

#if (HOST_CPU_IS_I80386==0)
	SET_FLAGS_OSZAPC_8_CF(op1,op2,sum,BX_INSTR_ADC8,prev_cf);
#endif //#if (HOST_CPU_IS_I80386==0)
#if (HOST_CPU_IS_I80386==1) 
	Bit32u x86_lf_flags = BX_CPU_CLASS_PTR eflags.x86.eax;
	__asm
	{
		mov eax,x86_lf_flags
		sahf
		mov dl,op2
		ADC op1,dl
		lahf
		seto al
		mov x86_lf_flags,eax
	}
	BX_CPU_CLASS_PTR eflags.x86.eax = x86_lf_flags;
#endif //#if (HOST_CPU_IS_I80386==1)

}

	void
BX_CPU_C::ADC_GwEGw(BX_CPU_C *icpu,bxInstruction_c *i)
{
	Bit16u op1, op2, sum;
	Boolean prev_cf;
	prev_cf = (BX_CPU_CLASS_PTR get_CF());

	op1 = READ_VIRTUAL_16BIT_REG(MODRMnnn(i));

	op2 = READ_VIRTUAL_16BIT_REG(MODRMrm(i));

	sum = op1 + op2 + prev_cf;

	WRITE_VIRTUAL_16BIT_REG(MODRMnnn(i),sum);

#if (HOST_CPU_IS_I80386==0)
	SET_FLAGS_OSZAPC_16_CF(op1,op2,sum,BX_INSTR_ADC16,prev_cf);
#endif //#if (HOST_CPU_IS_I80386==0)
#if (HOST_CPU_IS_I80386==1) 
	Bit32u x86_lf_flags = BX_CPU_CLASS_PTR eflags.x86.eax;
	__asm
	{
		mov eax,x86_lf_flags
		sahf
		mov dx,op2
		ADC op1,dx
		lahf
		seto al
		mov x86_lf_flags,eax
	}
	BX_CPU_CLASS_PTR eflags.x86.eax = x86_lf_flags;
#endif //#if (HOST_CPU_IS_I80386==1)

}

	void
BX_CPU_C::ADC_GdEGd(BX_CPU_C *icpu,bxInstruction_c *i)
{
	Bit32u op1, op2, sum;
	Boolean prev_cf;
	prev_cf = (BX_CPU_CLASS_PTR get_CF());

	op1 = READ_VIRTUAL_32BIT_REG(MODRMnnn(i));

	op2 = READ_VIRTUAL_32BIT_REG(MODRMrm(i));

	sum = op1 + op2 + prev_cf;

	WRITE_VIRTUAL_32BIT_REG(MODRMnnn(i),sum);

#if (HOST_CPU_IS_I80386==0)
	SET_FLAGS_OSZAPC_32_CF(op1,op2,sum,BX_INSTR_ADC32,prev_cf);
#endif //#if (HOST_CPU_IS_I80386==0)
#if (HOST_CPU_IS_I80386==1) 
	Bit32u x86_lf_flags = BX_CPU_CLASS_PTR eflags.x86.eax;
	__asm
	{
		mov eax,x86_lf_flags
		sahf
		mov edx,op2
		ADC op1,edx
		lahf
		seto al
		mov x86_lf_flags,eax
	}
	BX_CPU_CLASS_PTR eflags.x86.eax = x86_lf_flags;
#endif //#if (HOST_CPU_IS_I80386==1)

}

	void
BX_CPU_C::ADC_EGbIb(BX_CPU_C *icpu,bxInstruction_c *i)
{
	Bit8u op1, op2, sum;
	Boolean prev_cf;
	prev_cf = (BX_CPU_CLASS_PTR get_CF());

	op1 = READ_VIRTUAL_8BIT_REG(MODRMrm(i));

	op2 = IMMEDIATEIb(i);

	sum = op1 + op2 + prev_cf;

	WRITE_VIRTUAL_8BIT_REG(MODRMrm(i),sum);

#if (HOST_CPU_IS_I80386==0)
	SET_FLAGS_OSZAPC_8_CF(op1,op2,sum,BX_INSTR_ADC8,prev_cf);
#endif //#if (HOST_CPU_IS_I80386==0)
#if (HOST_CPU_IS_I80386==1) 
	Bit32u x86_lf_flags = BX_CPU_CLASS_PTR eflags.x86.eax;
	__asm
	{
		mov eax,x86_lf_flags
		sahf
		mov dl,op2
		ADC op1,dl
		lahf
		seto al
		mov x86_lf_flags,eax
	}
	BX_CPU_CLASS_PTR eflags.x86.eax = x86_lf_flags;
#endif //#if (HOST_CPU_IS_I80386==1)

}

	void
BX_CPU_C::ADC_EGwIw(BX_CPU_C *icpu,bxInstruction_c *i)
{
	Bit16u op1, op2, sum;
	Boolean prev_cf;
	prev_cf = (BX_CPU_CLASS_PTR get_CF());

	op1 = READ_VIRTUAL_16BIT_REG(MODRMrm(i));

	op2 = IMMEDIATEIw(i);

	sum = op1 + op2 + prev_cf;

	WRITE_VIRTUAL_16BIT_REG(MODRMrm(i),sum);

#if (HOST_CPU_IS_I80386==0)
	SET_FLAGS_OSZAPC_16_CF(op1,op2,sum,BX_INSTR_ADC16,prev_cf);
#endif //#if (HOST_CPU_IS_I80386==0)
#if (HOST_CPU_IS_I80386==1) 
	Bit32u x86_lf_flags = BX_CPU_CLASS_PTR eflags.x86.eax;
	__asm
	{
		mov eax,x86_lf_flags
		sahf
		mov dx,op2
		ADC op1,dx
		lahf
		seto al
		mov x86_lf_flags,eax
	}
	BX_CPU_CLASS_PTR eflags.x86.eax = x86_lf_flags;
#endif //#if (HOST_CPU_IS_I80386==1)

}

	void
BX_CPU_C::ADC_EGdId(BX_CPU_C *icpu,bxInstruction_c *i)
{
	Bit32u op1, op2, sum;
	Boolean prev_cf;
	prev_cf = (BX_CPU_CLASS_PTR get_CF());

	op1 = READ_VIRTUAL_32BIT_REG(MODRMrm(i));

	op2 = IMMEDIATEId(i);

	sum = op1 + op2 + prev_cf;

	WRITE_VIRTUAL_32BIT_REG(MODRMrm(i),sum);

#if (HOST_CPU_IS_I80386==0)
	SET_FLAGS_OSZAPC_32_CF(op1,op2,sum,BX_INSTR_ADC32,prev_cf);
#endif //#if (HOST_CPU_IS_I80386==0)
#if (HOST_CPU_IS_I80386==1) 
	Bit32u x86_lf_flags = BX_CPU_CLASS_PTR eflags.x86.eax;
	__asm
	{
		mov eax,x86_lf_flags
		sahf
		mov edx,op2
		ADC op1,edx
		lahf
		seto al
		mov x86_lf_flags,eax
	}
	BX_CPU_CLASS_PTR eflags.x86.eax = x86_lf_flags;
#endif //#if (HOST_CPU_IS_I80386==1)

}

	void
BX_CPU_C::ADC_ALIb(BX_CPU_C *icpu,bxInstruction_c *i)
{
	Bit8u op1, op2, sum;
	Boolean prev_cf;
	prev_cf = (BX_CPU_CLASS_PTR get_CF());

	op1 = READ_VIRTUAL_8BIT_REG(0);

	op2 = IMMEDIATEIb(i);

	sum = op1 + op2 + prev_cf;

	WRITE_VIRTUAL_8BIT_REG(0,sum);

#if (HOST_CPU_IS_I80386==0)
	SET_FLAGS_OSZAPC_8_CF(op1,op2,sum,BX_INSTR_ADC8,prev_cf);
#endif //#if (HOST_CPU_IS_I80386==0)
#if (HOST_CPU_IS_I80386==1) 
	Bit32u x86_lf_flags = BX_CPU_CLASS_PTR eflags.x86.eax;
	__asm
	{
		mov eax,x86_lf_flags
		sahf
		mov dl,op2
		ADC op1,dl
		lahf
		seto al
		mov x86_lf_flags,eax
	}
	BX_CPU_CLASS_PTR eflags.x86.eax = x86_lf_flags;
#endif //#if (HOST_CPU_IS_I80386==1)

}

	void
BX_CPU_C::ADC_AXIw(BX_CPU_C *icpu,bxInstruction_c *i)
{
	Bit16u op1, op2, sum;
	Boolean prev_cf;
	prev_cf = (BX_CPU_CLASS_PTR get_CF());

	op1 = READ_VIRTUAL_16BIT_REG(0);

	op2 = IMMEDIATEIw(i);

	sum = op1 + op2 + prev_cf;

	WRITE_VIRTUAL_16BIT_REG(0,sum);

#if (HOST_CPU_IS_I80386==0)
	SET_FLAGS_OSZAPC_16_CF(op1,op2,sum,BX_INSTR_ADC16,prev_cf);
#endif //#if (HOST_CPU_IS_I80386==0)
#if (HOST_CPU_IS_I80386==1) 
	Bit32u x86_lf_flags = BX_CPU_CLASS_PTR eflags.x86.eax;
	__asm
	{
		mov eax,x86_lf_flags
		sahf
		mov dx,op2
		ADC op1,dx
		lahf
		seto al
		mov x86_lf_flags,eax
	}
	BX_CPU_CLASS_PTR eflags.x86.eax = x86_lf_flags;
#endif //#if (HOST_CPU_IS_I80386==1)

}

	void
BX_CPU_C::ADC_EAXId(BX_CPU_C *icpu,bxInstruction_c *i)
{
	Bit32u op1, op2, sum;
	Boolean prev_cf;
	prev_cf = (BX_CPU_CLASS_PTR get_CF());

	op1 = READ_VIRTUAL_32BIT_REG(0);

	op2 = IMMEDIATEId(i);

	sum = op1 + op2 + prev_cf;

	WRITE_VIRTUAL_32BIT_REG(0,sum);

#if (HOST_CPU_IS_I80386==0)
	SET_FLAGS_OSZAPC_32_CF(op1,op2,sum,BX_INSTR_ADC32,prev_cf);
#endif //#if (HOST_CPU_IS_I80386==0)
#if (HOST_CPU_IS_I80386==1) 
	Bit32u x86_lf_flags = BX_CPU_CLASS_PTR eflags.x86.eax;
	__asm
	{
		mov eax,x86_lf_flags
		sahf
		mov edx,op2
		ADC op1,edx
		lahf
		seto al
		mov x86_lf_flags,eax
	}
	BX_CPU_CLASS_PTR eflags.x86.eax = x86_lf_flags;
#endif //#if (HOST_CPU_IS_I80386==1)

}

	void
BX_CPU_C::ADC_EEbGb(BX_CPU_C *icpu,bxInstruction_c *i)
{
	Bit8u op1, op2, sum;
	Boolean prev_cf;
	prev_cf = (BX_CPU_CLASS_PTR get_CF());

	READ_RMW_VIRTUAL_BYTE(MODRMSeg(i),RMAddr(i),&op1);

	op2 = READ_VIRTUAL_8BIT_REG(MODRMnnn(i));

	sum = op1 + op2 + prev_cf;

	WRITE_RMW_VIRTUAL_BYTE(sum);

#if (HOST_CPU_IS_I80386==0)
	SET_FLAGS_OSZAPC_8_CF(op1,op2,sum,BX_INSTR_ADC8,prev_cf);
#endif //#if (HOST_CPU_IS_I80386==0)
#if (HOST_CPU_IS_I80386==1) 
	Bit32u x86_lf_flags = BX_CPU_CLASS_PTR eflags.x86.eax;
	__asm
	{
		mov eax,x86_lf_flags
		sahf
		mov dl,op2
		ADC op1,dl
		lahf
		seto al
		mov x86_lf_flags,eax
	}
	BX_CPU_CLASS_PTR eflags.x86.eax = x86_lf_flags;
#endif //#if (HOST_CPU_IS_I80386==1)

}

	void
BX_CPU_C::ADC_EEwGw(BX_CPU_C *icpu,bxInstruction_c *i)
{
	Bit16u op1, op2, sum;
	Boolean prev_cf;
	prev_cf = (BX_CPU_CLASS_PTR get_CF());

	READ_RMW_VIRTUAL_WORD(MODRMSeg(i),RMAddr(i),&op1);

	op2 = READ_VIRTUAL_16BIT_REG(MODRMnnn(i));

	sum = op1 + op2 + prev_cf;

	WRITE_RMW_VIRTUAL_WORD(sum);

#if (HOST_CPU_IS_I80386==0)
	SET_FLAGS_OSZAPC_16_CF(op1,op2,sum,BX_INSTR_ADC16,prev_cf);
#endif //#if (HOST_CPU_IS_I80386==0)
#if (HOST_CPU_IS_I80386==1) 
	Bit32u x86_lf_flags = BX_CPU_CLASS_PTR eflags.x86.eax;
	__asm
	{
		mov eax,x86_lf_flags
		sahf
		mov dx,op2
		ADC op1,dx
		lahf
		seto al
		mov x86_lf_flags,eax
	}
	BX_CPU_CLASS_PTR eflags.x86.eax = x86_lf_flags;
#endif //#if (HOST_CPU_IS_I80386==1)

}

	void
BX_CPU_C::ADC_EEdGd(BX_CPU_C *icpu,bxInstruction_c *i)
{
	Bit32u op1, op2, sum;
	Boolean prev_cf;
	prev_cf = (BX_CPU_CLASS_PTR get_CF());

	READ_RMW_VIRTUAL_DWORD(MODRMSeg(i),RMAddr(i),&op1);

	op2 = READ_VIRTUAL_32BIT_REG(MODRMnnn(i));

	sum = op1 + op2 + prev_cf;

	WRITE_RMW_VIRTUAL_DWORD(sum);

#if (HOST_CPU_IS_I80386==0)
	SET_FLAGS_OSZAPC_32_CF(op1,op2,sum,BX_INSTR_ADC32,prev_cf);
#endif //#if (HOST_CPU_IS_I80386==0)
#if (HOST_CPU_IS_I80386==1) 
	Bit32u x86_lf_flags = BX_CPU_CLASS_PTR eflags.x86.eax;
	__asm
	{
		mov eax,x86_lf_flags
		sahf
		mov edx,op2
		ADC op1,edx
		lahf
		seto al
		mov x86_lf_flags,eax
	}
	BX_CPU_CLASS_PTR eflags.x86.eax = x86_lf_flags;
#endif //#if (HOST_CPU_IS_I80386==1)

}

	void
BX_CPU_C::ADC_GbEEb(BX_CPU_C *icpu,bxInstruction_c *i)
{
	Bit8u op1, op2, sum;
	Boolean prev_cf;
	prev_cf = (BX_CPU_CLASS_PTR get_CF());

	op1 = READ_VIRTUAL_8BIT_REG(MODRMnnn(i));

	READ_VIRTUAL_BYTE(MODRMSeg(i),RMAddr(i),&op2);

	sum = op1 + op2 + prev_cf;

	WRITE_VIRTUAL_8BIT_REG(MODRMnnn(i),sum);

#if (HOST_CPU_IS_I80386==0)
	SET_FLAGS_OSZAPC_8_CF(op1,op2,sum,BX_INSTR_ADC8,prev_cf);
#endif //#if (HOST_CPU_IS_I80386==0)
#if (HOST_CPU_IS_I80386==1) 
	Bit32u x86_lf_flags = BX_CPU_CLASS_PTR eflags.x86.eax;
	__asm
	{
		mov eax,x86_lf_flags
		sahf
		mov dl,op2
		ADC op1,dl
		lahf
		seto al
		mov x86_lf_flags,eax
	}
	BX_CPU_CLASS_PTR eflags.x86.eax = x86_lf_flags;
#endif //#if (HOST_CPU_IS_I80386==1)

}

	void
BX_CPU_C::ADC_GwEEw(BX_CPU_C *icpu,bxInstruction_c *i)
{
	Bit16u op1, op2, sum;
	Boolean prev_cf;
	prev_cf = (BX_CPU_CLASS_PTR get_CF());

	op1 = READ_VIRTUAL_16BIT_REG(MODRMnnn(i));

	READ_VIRTUAL_WORD(MODRMSeg(i),RMAddr(i),&op2);

	sum = op1 + op2 + prev_cf;

	WRITE_VIRTUAL_16BIT_REG(MODRMnnn(i),sum);

#if (HOST_CPU_IS_I80386==0)
	SET_FLAGS_OSZAPC_16_CF(op1,op2,sum,BX_INSTR_ADC16,prev_cf);
#endif //#if (HOST_CPU_IS_I80386==0)
#if (HOST_CPU_IS_I80386==1) 
	Bit32u x86_lf_flags = BX_CPU_CLASS_PTR eflags.x86.eax;
	__asm
	{
		mov eax,x86_lf_flags
		sahf
		mov dx,op2
		ADC op1,dx
		lahf
		seto al
		mov x86_lf_flags,eax
	}
	BX_CPU_CLASS_PTR eflags.x86.eax = x86_lf_flags;
#endif //#if (HOST_CPU_IS_I80386==1)

}

	void
BX_CPU_C::ADC_GdEEd(BX_CPU_C *icpu,bxInstruction_c *i)
{
	Bit32u op1, op2, sum;
	Boolean prev_cf;
	prev_cf = (BX_CPU_CLASS_PTR get_CF());

	op1 = READ_VIRTUAL_32BIT_REG(MODRMnnn(i));

	READ_VIRTUAL_DWORD(MODRMSeg(i),RMAddr(i),&op2);

	sum = op1 + op2 + prev_cf;

	WRITE_VIRTUAL_32BIT_REG(MODRMnnn(i),sum);

#if (HOST_CPU_IS_I80386==0)
	SET_FLAGS_OSZAPC_32_CF(op1,op2,sum,BX_INSTR_ADC32,prev_cf);
#endif //#if (HOST_CPU_IS_I80386==0)
#if (HOST_CPU_IS_I80386==1) 
	Bit32u x86_lf_flags = BX_CPU_CLASS_PTR eflags.x86.eax;
	__asm
	{
		mov eax,x86_lf_flags
		sahf
		mov edx,op2
		ADC op1,edx
		lahf
		seto al
		mov x86_lf_flags,eax
	}
	BX_CPU_CLASS_PTR eflags.x86.eax = x86_lf_flags;
#endif //#if (HOST_CPU_IS_I80386==1)

}

	void
BX_CPU_C::ADC_EEbIb(BX_CPU_C *icpu,bxInstruction_c *i)
{
	Bit8u op1, op2, sum;
	Boolean prev_cf;
	prev_cf = (BX_CPU_CLASS_PTR get_CF());

	READ_RMW_VIRTUAL_BYTE(MODRMSeg(i),RMAddr(i),&op1);

	op2 = IMMEDIATEIb(i);

	sum = op1 + op2 + prev_cf;

	WRITE_RMW_VIRTUAL_BYTE(sum);

#if (HOST_CPU_IS_I80386==0)
	SET_FLAGS_OSZAPC_8_CF(op1,op2,sum,BX_INSTR_ADC8,prev_cf);
#endif //#if (HOST_CPU_IS_I80386==0)
#if (HOST_CPU_IS_I80386==1) 
	Bit32u x86_lf_flags = BX_CPU_CLASS_PTR eflags.x86.eax;
	__asm
	{
		mov eax,x86_lf_flags
		sahf
		mov dl,op2
		ADC op1,dl
		lahf
		seto al
		mov x86_lf_flags,eax
	}
	BX_CPU_CLASS_PTR eflags.x86.eax = x86_lf_flags;
#endif //#if (HOST_CPU_IS_I80386==1)

}

	void
BX_CPU_C::ADC_EEwIw(BX_CPU_C *icpu,bxInstruction_c *i)
{
	Bit16u op1, op2, sum;
	Boolean prev_cf;
	prev_cf = (BX_CPU_CLASS_PTR get_CF());

	READ_RMW_VIRTUAL_WORD(MODRMSeg(i),RMAddr(i),&op1);

	op2 = IMMEDIATEIw(i);

	sum = op1 + op2 + prev_cf;

	WRITE_RMW_VIRTUAL_WORD(sum);

#if (HOST_CPU_IS_I80386==0)
	SET_FLAGS_OSZAPC_16_CF(op1,op2,sum,BX_INSTR_ADC16,prev_cf);
#endif //#if (HOST_CPU_IS_I80386==0)
#if (HOST_CPU_IS_I80386==1) 
	Bit32u x86_lf_flags = BX_CPU_CLASS_PTR eflags.x86.eax;
	__asm
	{
		mov eax,x86_lf_flags
		sahf
		mov dx,op2
		ADC op1,dx
		lahf
		seto al
		mov x86_lf_flags,eax
	}
	BX_CPU_CLASS_PTR eflags.x86.eax = x86_lf_flags;
#endif //#if (HOST_CPU_IS_I80386==1)

}

	void
BX_CPU_C::ADC_EEdId(BX_CPU_C *icpu,bxInstruction_c *i)
{
	Bit32u op1, op2, sum;
	Boolean prev_cf;
	prev_cf = (BX_CPU_CLASS_PTR get_CF());

	READ_RMW_VIRTUAL_DWORD(MODRMSeg(i),RMAddr(i),&op1);

	op2 = IMMEDIATEId(i);

	sum = op1 + op2 + prev_cf;

	WRITE_RMW_VIRTUAL_DWORD(sum);

#if (HOST_CPU_IS_I80386==0)
	SET_FLAGS_OSZAPC_32_CF(op1,op2,sum,BX_INSTR_ADC32,prev_cf);
#endif //#if (HOST_CPU_IS_I80386==0)
#if (HOST_CPU_IS_I80386==1) 
	Bit32u x86_lf_flags = BX_CPU_CLASS_PTR eflags.x86.eax;
	__asm
	{
		mov eax,x86_lf_flags
		sahf
		mov edx,op2
		ADC op1,edx
		lahf
		seto al
		mov x86_lf_flags,eax
	}
	BX_CPU_CLASS_PTR eflags.x86.eax = x86_lf_flags;
#endif //#if (HOST_CPU_IS_I80386==1)

}

	void
BX_CPU_C::SBB_EGbGb(BX_CPU_C *icpu,bxInstruction_c *i)
{
	Bit8u op1, op2, sum;
	Boolean prev_cf;
	prev_cf = (BX_CPU_CLASS_PTR get_CF());

	op1 = READ_VIRTUAL_8BIT_REG(MODRMrm(i));

	op2 = READ_VIRTUAL_8BIT_REG(MODRMnnn(i));

	sum = op1 - op2 - prev_cf;

	WRITE_VIRTUAL_8BIT_REG(MODRMrm(i), sum);

#if (HOST_CPU_IS_I80386==0)
	SET_FLAGS_OSZAPC_8_CF(op1,op2,sum,BX_INSTR_SBB8,prev_cf);
#endif //#if (HOST_CPU_IS_I80386==0)
#if (HOST_CPU_IS_I80386==1) 
	Bit32u x86_lf_flags = BX_CPU_CLASS_PTR eflags.x86.eax;
	__asm
	{
		mov eax,x86_lf_flags
		sahf
		mov dl,op2
		SBB op1,dl
		lahf
		seto al
		mov x86_lf_flags,eax
	}
	BX_CPU_CLASS_PTR eflags.x86.eax = x86_lf_flags;
#endif //#if (HOST_CPU_IS_I80386==1)

}

	void
BX_CPU_C::SBB_EGwGw(BX_CPU_C *icpu,bxInstruction_c *i)
{
	Bit16u op1, op2, sum;
	Boolean prev_cf;
	prev_cf = (BX_CPU_CLASS_PTR get_CF());

	op1 = READ_VIRTUAL_16BIT_REG(MODRMrm(i));

	op2 = READ_VIRTUAL_16BIT_REG(MODRMnnn(i));

	sum = op1 - op2 - prev_cf;

	WRITE_VIRTUAL_16BIT_REG(MODRMrm(i), sum);

#if (HOST_CPU_IS_I80386==0)
	SET_FLAGS_OSZAPC_16_CF(op1,op2,sum,BX_INSTR_SBB16,prev_cf);
#endif //#if (HOST_CPU_IS_I80386==0)
#if (HOST_CPU_IS_I80386==1) 
	Bit32u x86_lf_flags = BX_CPU_CLASS_PTR eflags.x86.eax;
	__asm
	{
		mov eax,x86_lf_flags
		sahf
		mov dx,op2
		SBB op1,dx
		lahf
		seto al
		mov x86_lf_flags,eax
	}
	BX_CPU_CLASS_PTR eflags.x86.eax = x86_lf_flags;
#endif //#if (HOST_CPU_IS_I80386==1)

}

	void
BX_CPU_C::SBB_EGdGd(BX_CPU_C *icpu,bxInstruction_c *i)
{
	Bit32u op1, op2, sum;
	Boolean prev_cf;
	prev_cf = (BX_CPU_CLASS_PTR get_CF());

	op1 = READ_VIRTUAL_32BIT_REG(MODRMrm(i));

	op2 = READ_VIRTUAL_32BIT_REG(MODRMnnn(i));

	sum = op1 - op2 - prev_cf;

	WRITE_VIRTUAL_32BIT_REG(MODRMrm(i), sum);

#if (HOST_CPU_IS_I80386==0)
	SET_FLAGS_OSZAPC_32_CF(op1,op2,sum,BX_INSTR_SBB32,prev_cf);
#endif //#if (HOST_CPU_IS_I80386==0)
#if (HOST_CPU_IS_I80386==1) 
	Bit32u x86_lf_flags = BX_CPU_CLASS_PTR eflags.x86.eax;
	__asm
	{
		mov eax,x86_lf_flags
		sahf
		mov edx,op2
		SBB op1,edx
		lahf
		seto al
		mov x86_lf_flags,eax
	}
	BX_CPU_CLASS_PTR eflags.x86.eax = x86_lf_flags;
#endif //#if (HOST_CPU_IS_I80386==1)

}

	void
BX_CPU_C::SBB_GbEGb(BX_CPU_C *icpu,bxInstruction_c *i)
{
	Bit8u op1, op2, sum;
	Boolean prev_cf;
	prev_cf = (BX_CPU_CLASS_PTR get_CF());

	op1 = READ_VIRTUAL_8BIT_REG(MODRMnnn(i));

	op2 = READ_VIRTUAL_8BIT_REG(MODRMrm(i));

	sum = op1 - op2 - prev_cf;

	WRITE_VIRTUAL_8BIT_REG(MODRMnnn(i),sum);

#if (HOST_CPU_IS_I80386==0)
	SET_FLAGS_OSZAPC_8_CF(op1,op2,sum,BX_INSTR_SBB8,prev_cf);
#endif //#if (HOST_CPU_IS_I80386==0)
#if (HOST_CPU_IS_I80386==1) 
	Bit32u x86_lf_flags = BX_CPU_CLASS_PTR eflags.x86.eax;
	__asm
	{
		mov eax,x86_lf_flags
		sahf
		mov dl,op2
		SBB op1,dl
		lahf
		seto al
		mov x86_lf_flags,eax
	}
	BX_CPU_CLASS_PTR eflags.x86.eax = x86_lf_flags;
#endif //#if (HOST_CPU_IS_I80386==1)

}

	void
BX_CPU_C::SBB_GwEGw(BX_CPU_C *icpu,bxInstruction_c *i)
{
	Bit16u op1, op2, sum;
	Boolean prev_cf;
	prev_cf = (BX_CPU_CLASS_PTR get_CF());

	op1 = READ_VIRTUAL_16BIT_REG(MODRMnnn(i));

	op2 = READ_VIRTUAL_16BIT_REG(MODRMrm(i));

	sum = op1 - op2 - prev_cf;

	WRITE_VIRTUAL_16BIT_REG(MODRMnnn(i),sum);

#if (HOST_CPU_IS_I80386==0)
	SET_FLAGS_OSZAPC_16_CF(op1,op2,sum,BX_INSTR_SBB16,prev_cf);
#endif //#if (HOST_CPU_IS_I80386==0)
#if (HOST_CPU_IS_I80386==1) 
	Bit32u x86_lf_flags = BX_CPU_CLASS_PTR eflags.x86.eax;
	__asm
	{
		mov eax,x86_lf_flags
		sahf
		mov dx,op2
		SBB op1,dx
		lahf
		seto al
		mov x86_lf_flags,eax
	}
	BX_CPU_CLASS_PTR eflags.x86.eax = x86_lf_flags;
#endif //#if (HOST_CPU_IS_I80386==1)

}

	void
BX_CPU_C::SBB_GdEGd(BX_CPU_C *icpu,bxInstruction_c *i)
{
	Bit32u op1, op2, sum;
	Boolean prev_cf;
	prev_cf = (BX_CPU_CLASS_PTR get_CF());

	op1 = READ_VIRTUAL_32BIT_REG(MODRMnnn(i));

	op2 = READ_VIRTUAL_32BIT_REG(MODRMrm(i));

	sum = op1 - op2 - prev_cf;

	WRITE_VIRTUAL_32BIT_REG(MODRMnnn(i),sum);

#if (HOST_CPU_IS_I80386==0)
	SET_FLAGS_OSZAPC_32_CF(op1,op2,sum,BX_INSTR_SBB32,prev_cf);
#endif //#if (HOST_CPU_IS_I80386==0)
#if (HOST_CPU_IS_I80386==1) 
	Bit32u x86_lf_flags = BX_CPU_CLASS_PTR eflags.x86.eax;
	__asm
	{
		mov eax,x86_lf_flags
		sahf
		mov edx,op2
		SBB op1,edx
		lahf
		seto al
		mov x86_lf_flags,eax
	}
	BX_CPU_CLASS_PTR eflags.x86.eax = x86_lf_flags;
#endif //#if (HOST_CPU_IS_I80386==1)

}

	void
BX_CPU_C::SBB_EGbIb(BX_CPU_C *icpu,bxInstruction_c *i)
{
	Bit8u op1, op2, sum;
	Boolean prev_cf;
	prev_cf = (BX_CPU_CLASS_PTR get_CF());

	op1 = READ_VIRTUAL_8BIT_REG(MODRMrm(i));

	op2 = IMMEDIATEIb(i);

	sum = op1 - op2 - prev_cf;

	WRITE_VIRTUAL_8BIT_REG(MODRMrm(i),sum);

#if (HOST_CPU_IS_I80386==0)
	SET_FLAGS_OSZAPC_8_CF(op1,op2,sum,BX_INSTR_SBB8,prev_cf);
#endif //#if (HOST_CPU_IS_I80386==0)
#if (HOST_CPU_IS_I80386==1) 
	Bit32u x86_lf_flags = BX_CPU_CLASS_PTR eflags.x86.eax;
	__asm
	{
		mov eax,x86_lf_flags
		sahf
		mov dl,op2
		SBB op1,dl
		lahf
		seto al
		mov x86_lf_flags,eax
	}
	BX_CPU_CLASS_PTR eflags.x86.eax = x86_lf_flags;
#endif //#if (HOST_CPU_IS_I80386==1)

}

	void
BX_CPU_C::SBB_EGwIw(BX_CPU_C *icpu,bxInstruction_c *i)
{
	Bit16u op1, op2, sum;
	Boolean prev_cf;
	prev_cf = (BX_CPU_CLASS_PTR get_CF());

	op1 = READ_VIRTUAL_16BIT_REG(MODRMrm(i));

	op2 = IMMEDIATEIw(i);

	sum = op1 - op2 - prev_cf;

	WRITE_VIRTUAL_16BIT_REG(MODRMrm(i),sum);

#if (HOST_CPU_IS_I80386==0)
	SET_FLAGS_OSZAPC_16_CF(op1,op2,sum,BX_INSTR_SBB16,prev_cf);
#endif //#if (HOST_CPU_IS_I80386==0)
#if (HOST_CPU_IS_I80386==1) 
	Bit32u x86_lf_flags = BX_CPU_CLASS_PTR eflags.x86.eax;
	__asm
	{
		mov eax,x86_lf_flags
		sahf
		mov dx,op2
		SBB op1,dx
		lahf
		seto al
		mov x86_lf_flags,eax
	}
	BX_CPU_CLASS_PTR eflags.x86.eax = x86_lf_flags;
#endif //#if (HOST_CPU_IS_I80386==1)

}

	void
BX_CPU_C::SBB_EGdId(BX_CPU_C *icpu,bxInstruction_c *i)
{
	Bit32u op1, op2, sum;
	Boolean prev_cf;
	prev_cf = (BX_CPU_CLASS_PTR get_CF());

	op1 = READ_VIRTUAL_32BIT_REG(MODRMrm(i));

	op2 = IMMEDIATEId(i);

	sum = op1 - op2 - prev_cf;

	WRITE_VIRTUAL_32BIT_REG(MODRMrm(i),sum);

#if (HOST_CPU_IS_I80386==0)
	SET_FLAGS_OSZAPC_32_CF(op1,op2,sum,BX_INSTR_SBB32,prev_cf);
#endif //#if (HOST_CPU_IS_I80386==0)
#if (HOST_CPU_IS_I80386==1) 
	Bit32u x86_lf_flags = BX_CPU_CLASS_PTR eflags.x86.eax;
	__asm
	{
		mov eax,x86_lf_flags
		sahf
		mov edx,op2
		SBB op1,edx
		lahf
		seto al
		mov x86_lf_flags,eax
	}
	BX_CPU_CLASS_PTR eflags.x86.eax = x86_lf_flags;
#endif //#if (HOST_CPU_IS_I80386==1)

}

	void
BX_CPU_C::SBB_ALIb(BX_CPU_C *icpu,bxInstruction_c *i)
{
	Bit8u op1, op2, sum;
	Boolean prev_cf;
	prev_cf = (BX_CPU_CLASS_PTR get_CF());

	op1 = READ_VIRTUAL_8BIT_REG(0);

	op2 = IMMEDIATEIb(i);

	sum = op1 - op2 - prev_cf;

	WRITE_VIRTUAL_8BIT_REG(0,sum);

#if (HOST_CPU_IS_I80386==0)
	SET_FLAGS_OSZAPC_8_CF(op1,op2,sum,BX_INSTR_SBB8,prev_cf);
#endif //#if (HOST_CPU_IS_I80386==0)
#if (HOST_CPU_IS_I80386==1) 
	Bit32u x86_lf_flags = BX_CPU_CLASS_PTR eflags.x86.eax;
	__asm
	{
		mov eax,x86_lf_flags
		sahf
		mov dl,op2
		SBB op1,dl
		lahf
		seto al
		mov x86_lf_flags,eax
	}
	BX_CPU_CLASS_PTR eflags.x86.eax = x86_lf_flags;
#endif //#if (HOST_CPU_IS_I80386==1)

}

	void
BX_CPU_C::SBB_AXIw(BX_CPU_C *icpu,bxInstruction_c *i)
{
	Bit16u op1, op2, sum;
	Boolean prev_cf;
	prev_cf = (BX_CPU_CLASS_PTR get_CF());

	op1 = READ_VIRTUAL_16BIT_REG(0);

	op2 = IMMEDIATEIw(i);

	sum = op1 - op2 - prev_cf;

	WRITE_VIRTUAL_16BIT_REG(0,sum);

#if (HOST_CPU_IS_I80386==0)
	SET_FLAGS_OSZAPC_16_CF(op1,op2,sum,BX_INSTR_SBB16,prev_cf);
#endif //#if (HOST_CPU_IS_I80386==0)
#if (HOST_CPU_IS_I80386==1) 
	Bit32u x86_lf_flags = BX_CPU_CLASS_PTR eflags.x86.eax;
	__asm
	{
		mov eax,x86_lf_flags
		sahf
		mov dx,op2
		SBB op1,dx
		lahf
		seto al
		mov x86_lf_flags,eax
	}
	BX_CPU_CLASS_PTR eflags.x86.eax = x86_lf_flags;
#endif //#if (HOST_CPU_IS_I80386==1)

}

	void
BX_CPU_C::SBB_EAXId(BX_CPU_C *icpu,bxInstruction_c *i)
{
	Bit32u op1, op2, sum;
	Boolean prev_cf;
	prev_cf = (BX_CPU_CLASS_PTR get_CF());

	op1 = READ_VIRTUAL_32BIT_REG(0);

	op2 = IMMEDIATEId(i);

	sum = op1 - op2 - prev_cf;

	WRITE_VIRTUAL_32BIT_REG(0,sum);

#if (HOST_CPU_IS_I80386==0)
	SET_FLAGS_OSZAPC_32_CF(op1,op2,sum,BX_INSTR_SBB32,prev_cf);
#endif //#if (HOST_CPU_IS_I80386==0)
#if (HOST_CPU_IS_I80386==1) 
	Bit32u x86_lf_flags = BX_CPU_CLASS_PTR eflags.x86.eax;
	__asm
	{
		mov eax,x86_lf_flags
		sahf
		mov edx,op2
		SBB op1,edx
		lahf
		seto al
		mov x86_lf_flags,eax
	}
	BX_CPU_CLASS_PTR eflags.x86.eax = x86_lf_flags;
#endif //#if (HOST_CPU_IS_I80386==1)

}

	void
BX_CPU_C::SBB_EEbGb(BX_CPU_C *icpu,bxInstruction_c *i)
{
	Bit8u op1, op2, sum;
	Boolean prev_cf;
	prev_cf = (BX_CPU_CLASS_PTR get_CF());

	READ_RMW_VIRTUAL_BYTE(MODRMSeg(i),RMAddr(i),&op1);

	op2 = READ_VIRTUAL_8BIT_REG(MODRMnnn(i));

	sum = op1 - op2 - prev_cf;

	WRITE_RMW_VIRTUAL_BYTE(sum);

#if (HOST_CPU_IS_I80386==0)
	SET_FLAGS_OSZAPC_8_CF(op1,op2,sum,BX_INSTR_SBB8,prev_cf);
#endif //#if (HOST_CPU_IS_I80386==0)
#if (HOST_CPU_IS_I80386==1) 
	Bit32u x86_lf_flags = BX_CPU_CLASS_PTR eflags.x86.eax;
	__asm
	{
		mov eax,x86_lf_flags
		sahf
		mov dl,op2
		SBB op1,dl
		lahf
		seto al
		mov x86_lf_flags,eax
	}
	BX_CPU_CLASS_PTR eflags.x86.eax = x86_lf_flags;
#endif //#if (HOST_CPU_IS_I80386==1)

}

	void
BX_CPU_C::SBB_EEwGw(BX_CPU_C *icpu,bxInstruction_c *i)
{
	Bit16u op1, op2, sum;
	Boolean prev_cf;
	prev_cf = (BX_CPU_CLASS_PTR get_CF());

	READ_RMW_VIRTUAL_WORD(MODRMSeg(i),RMAddr(i),&op1);

	op2 = READ_VIRTUAL_16BIT_REG(MODRMnnn(i));

	sum = op1 - op2 - prev_cf;

	WRITE_RMW_VIRTUAL_WORD(sum);

#if (HOST_CPU_IS_I80386==0)
	SET_FLAGS_OSZAPC_16_CF(op1,op2,sum,BX_INSTR_SBB16,prev_cf);
#endif //#if (HOST_CPU_IS_I80386==0)
#if (HOST_CPU_IS_I80386==1) 
	Bit32u x86_lf_flags = BX_CPU_CLASS_PTR eflags.x86.eax;
	__asm
	{
		mov eax,x86_lf_flags
		sahf
		mov dx,op2
		SBB op1,dx
		lahf
		seto al
		mov x86_lf_flags,eax
	}
	BX_CPU_CLASS_PTR eflags.x86.eax = x86_lf_flags;
#endif //#if (HOST_CPU_IS_I80386==1)

}

	void
BX_CPU_C::SBB_EEdGd(BX_CPU_C *icpu,bxInstruction_c *i)
{
	Bit32u op1, op2, sum;
	Boolean prev_cf;
	prev_cf = (BX_CPU_CLASS_PTR get_CF());

	READ_RMW_VIRTUAL_DWORD(MODRMSeg(i),RMAddr(i),&op1);

	op2 = READ_VIRTUAL_32BIT_REG(MODRMnnn(i));

	sum = op1 - op2 - prev_cf;

	WRITE_RMW_VIRTUAL_DWORD(sum);

#if (HOST_CPU_IS_I80386==0)
	SET_FLAGS_OSZAPC_32_CF(op1,op2,sum,BX_INSTR_SBB32,prev_cf);
#endif //#if (HOST_CPU_IS_I80386==0)
#if (HOST_CPU_IS_I80386==1) 
	Bit32u x86_lf_flags = BX_CPU_CLASS_PTR eflags.x86.eax;
	__asm
	{
		mov eax,x86_lf_flags
		sahf
		mov edx,op2
		SBB op1,edx
		lahf
		seto al
		mov x86_lf_flags,eax
	}
	BX_CPU_CLASS_PTR eflags.x86.eax = x86_lf_flags;
#endif //#if (HOST_CPU_IS_I80386==1)

}

	void
BX_CPU_C::SBB_GbEEb(BX_CPU_C *icpu,bxInstruction_c *i)
{
	Bit8u op1, op2, sum;
	Boolean prev_cf;
	prev_cf = (BX_CPU_CLASS_PTR get_CF());

	op1 = READ_VIRTUAL_8BIT_REG(MODRMnnn(i));

	READ_VIRTUAL_BYTE(MODRMSeg(i),RMAddr(i),&op2);

	sum = op1 - op2 - prev_cf;

	WRITE_VIRTUAL_8BIT_REG(MODRMnnn(i),sum);

#if (HOST_CPU_IS_I80386==0)
	SET_FLAGS_OSZAPC_8_CF(op1,op2,sum,BX_INSTR_SBB8,prev_cf);
#endif //#if (HOST_CPU_IS_I80386==0)
#if (HOST_CPU_IS_I80386==1) 
	Bit32u x86_lf_flags = BX_CPU_CLASS_PTR eflags.x86.eax;
	__asm
	{
		mov eax,x86_lf_flags
		sahf
		mov dl,op2
		SBB op1,dl
		lahf
		seto al
		mov x86_lf_flags,eax
	}
	BX_CPU_CLASS_PTR eflags.x86.eax = x86_lf_flags;
#endif //#if (HOST_CPU_IS_I80386==1)

}

	void
BX_CPU_C::SBB_GwEEw(BX_CPU_C *icpu,bxInstruction_c *i)
{
	Bit16u op1, op2, sum;
	Boolean prev_cf;
	prev_cf = (BX_CPU_CLASS_PTR get_CF());

	op1 = READ_VIRTUAL_16BIT_REG(MODRMnnn(i));

	READ_VIRTUAL_WORD(MODRMSeg(i),RMAddr(i),&op2);

	sum = op1 - op2 - prev_cf;

	WRITE_VIRTUAL_16BIT_REG(MODRMnnn(i),sum);

#if (HOST_CPU_IS_I80386==0)
	SET_FLAGS_OSZAPC_16_CF(op1,op2,sum,BX_INSTR_SBB16,prev_cf);
#endif //#if (HOST_CPU_IS_I80386==0)
#if (HOST_CPU_IS_I80386==1) 
	Bit32u x86_lf_flags = BX_CPU_CLASS_PTR eflags.x86.eax;
	__asm
	{
		mov eax,x86_lf_flags
		sahf
		mov dx,op2
		SBB op1,dx
		lahf
		seto al
		mov x86_lf_flags,eax
	}
	BX_CPU_CLASS_PTR eflags.x86.eax = x86_lf_flags;
#endif //#if (HOST_CPU_IS_I80386==1)

}

	void
BX_CPU_C::SBB_GdEEd(BX_CPU_C *icpu,bxInstruction_c *i)
{
	Bit32u op1, op2, sum;
	Boolean prev_cf;
	prev_cf = (BX_CPU_CLASS_PTR get_CF());

	op1 = READ_VIRTUAL_32BIT_REG(MODRMnnn(i));

	READ_VIRTUAL_DWORD(MODRMSeg(i),RMAddr(i),&op2);

	sum = op1 - op2 - prev_cf;

	WRITE_VIRTUAL_32BIT_REG(MODRMnnn(i),sum);

#if (HOST_CPU_IS_I80386==0)
	SET_FLAGS_OSZAPC_32_CF(op1,op2,sum,BX_INSTR_SBB32,prev_cf);
#endif //#if (HOST_CPU_IS_I80386==0)
#if (HOST_CPU_IS_I80386==1) 
	Bit32u x86_lf_flags = BX_CPU_CLASS_PTR eflags.x86.eax;
	__asm
	{
		mov eax,x86_lf_flags
		sahf
		mov edx,op2
		SBB op1,edx
		lahf
		seto al
		mov x86_lf_flags,eax
	}
	BX_CPU_CLASS_PTR eflags.x86.eax = x86_lf_flags;
#endif //#if (HOST_CPU_IS_I80386==1)

}

	void
BX_CPU_C::SBB_EEbIb(BX_CPU_C *icpu,bxInstruction_c *i)
{
	Bit8u op1, op2, sum;
	Boolean prev_cf;
	prev_cf = (BX_CPU_CLASS_PTR get_CF());

	READ_RMW_VIRTUAL_BYTE(MODRMSeg(i),RMAddr(i),&op1);

	op2 = IMMEDIATEIb(i);

	sum = op1 - op2 - prev_cf;

	WRITE_RMW_VIRTUAL_BYTE(sum);

#if (HOST_CPU_IS_I80386==0)
	SET_FLAGS_OSZAPC_8_CF(op1,op2,sum,BX_INSTR_SBB8,prev_cf);
#endif //#if (HOST_CPU_IS_I80386==0)
#if (HOST_CPU_IS_I80386==1) 
	Bit32u x86_lf_flags = BX_CPU_CLASS_PTR eflags.x86.eax;
	__asm
	{
		mov eax,x86_lf_flags
		sahf
		mov dl,op2
		SBB op1,dl
		lahf
		seto al
		mov x86_lf_flags,eax
	}
	BX_CPU_CLASS_PTR eflags.x86.eax = x86_lf_flags;
#endif //#if (HOST_CPU_IS_I80386==1)

}

	void
BX_CPU_C::SBB_EEwIw(BX_CPU_C *icpu,bxInstruction_c *i)
{
	Bit16u op1, op2, sum;
	Boolean prev_cf;
	prev_cf = (BX_CPU_CLASS_PTR get_CF());

	READ_RMW_VIRTUAL_WORD(MODRMSeg(i),RMAddr(i),&op1);

	op2 = IMMEDIATEIw(i);

	sum = op1 - op2 - prev_cf;

	WRITE_RMW_VIRTUAL_WORD(sum);

#if (HOST_CPU_IS_I80386==0)
	SET_FLAGS_OSZAPC_16_CF(op1,op2,sum,BX_INSTR_SBB16,prev_cf);
#endif //#if (HOST_CPU_IS_I80386==0)
#if (HOST_CPU_IS_I80386==1) 
	Bit32u x86_lf_flags = BX_CPU_CLASS_PTR eflags.x86.eax;
	__asm
	{
		mov eax,x86_lf_flags
		sahf
		mov dx,op2
		SBB op1,dx
		lahf
		seto al
		mov x86_lf_flags,eax
	}
	BX_CPU_CLASS_PTR eflags.x86.eax = x86_lf_flags;
#endif //#if (HOST_CPU_IS_I80386==1)

}

	void
BX_CPU_C::SBB_EEdId(BX_CPU_C *icpu,bxInstruction_c *i)
{
	Bit32u op1, op2, sum;
	Boolean prev_cf;
	prev_cf = (BX_CPU_CLASS_PTR get_CF());

	READ_RMW_VIRTUAL_DWORD(MODRMSeg(i),RMAddr(i),&op1);

	op2 = IMMEDIATEId(i);

	sum = op1 - op2 - prev_cf;

	WRITE_RMW_VIRTUAL_DWORD(sum);

#if (HOST_CPU_IS_I80386==0)
	SET_FLAGS_OSZAPC_32_CF(op1,op2,sum,BX_INSTR_SBB32,prev_cf);
#endif //#if (HOST_CPU_IS_I80386==0)
#if (HOST_CPU_IS_I80386==1) 
	Bit32u x86_lf_flags = BX_CPU_CLASS_PTR eflags.x86.eax;
	__asm
	{
		mov eax,x86_lf_flags
		sahf
		mov edx,op2
		SBB op1,edx
		lahf
		seto al
		mov x86_lf_flags,eax
	}
	BX_CPU_CLASS_PTR eflags.x86.eax = x86_lf_flags;
#endif //#if (HOST_CPU_IS_I80386==1)

}

	void
BX_CPU_C::CMP_EGbGb(BX_CPU_C *icpu,bxInstruction_c *i)
{
	Bit8u op1, op2, sum;

	op1 = READ_VIRTUAL_8BIT_REG(MODRMrm(i));

	op2 = READ_VIRTUAL_8BIT_REG(MODRMnnn(i));

	sum = op1 - op2;


#if (HOST_CPU_IS_I80386==0)
	SET_FLAGS_OSZAPC_8(op1,op2,sum,BX_INSTR_CMP8);
#endif //#if (HOST_CPU_IS_I80386==0)
#if (HOST_CPU_IS_I80386==1) 
	Bit32u x86_lf_flags = BX_CPU_CLASS_PTR eflags.x86.eax;
	__asm
	{
		mov dl,op2
		CMP op1,dl
		lahf
		seto al
		mov x86_lf_flags,eax
	}
	BX_CPU_CLASS_PTR eflags.x86.eax = x86_lf_flags;
#endif //#if (HOST_CPU_IS_I80386==1)

}

	void
BX_CPU_C::CMP_EGwGw(BX_CPU_C *icpu,bxInstruction_c *i)
{
	Bit16u op1, op2, sum;

	op1 = READ_VIRTUAL_16BIT_REG(MODRMrm(i));

	op2 = READ_VIRTUAL_16BIT_REG(MODRMnnn(i));

	sum = op1 - op2;


#if (HOST_CPU_IS_I80386==0)
	SET_FLAGS_OSZAPC_16(op1,op2,sum,BX_INSTR_CMP16);
#endif //#if (HOST_CPU_IS_I80386==0)
#if (HOST_CPU_IS_I80386==1) 
	Bit32u x86_lf_flags = BX_CPU_CLASS_PTR eflags.x86.eax;
	__asm
	{
		mov dx,op2
		CMP op1,dx
		lahf
		seto al
		mov x86_lf_flags,eax
	}
	BX_CPU_CLASS_PTR eflags.x86.eax = x86_lf_flags;
#endif //#if (HOST_CPU_IS_I80386==1)

}

	void
BX_CPU_C::CMP_EGdGd(BX_CPU_C *icpu,bxInstruction_c *i)
{
	Bit32u op1, op2, sum;

	op1 = READ_VIRTUAL_32BIT_REG(MODRMrm(i));

	op2 = READ_VIRTUAL_32BIT_REG(MODRMnnn(i));

	sum = op1 - op2;


#if (HOST_CPU_IS_I80386==0)
	SET_FLAGS_OSZAPC_32(op1,op2,sum,BX_INSTR_CMP32);
#endif //#if (HOST_CPU_IS_I80386==0)
#if (HOST_CPU_IS_I80386==1) 
	Bit32u x86_lf_flags = BX_CPU_CLASS_PTR eflags.x86.eax;
	__asm
	{
		mov edx,op2
		CMP op1,edx
		lahf
		seto al
		mov x86_lf_flags,eax
	}
	BX_CPU_CLASS_PTR eflags.x86.eax = x86_lf_flags;
#endif //#if (HOST_CPU_IS_I80386==1)

}

	void
BX_CPU_C::CMP_GbEGb(BX_CPU_C *icpu,bxInstruction_c *i)
{
	Bit8u op1, op2, sum;

	op1 = READ_VIRTUAL_8BIT_REG(MODRMnnn(i));

	op2 = READ_VIRTUAL_8BIT_REG(MODRMrm(i));

	sum = op1 - op2;


#if (HOST_CPU_IS_I80386==0)
	SET_FLAGS_OSZAPC_8(op1,op2,sum,BX_INSTR_CMP8);
#endif //#if (HOST_CPU_IS_I80386==0)
#if (HOST_CPU_IS_I80386==1) 
	Bit32u x86_lf_flags = BX_CPU_CLASS_PTR eflags.x86.eax;
	__asm
	{
		mov dl,op2
		CMP op1,dl
		lahf
		seto al
		mov x86_lf_flags,eax
	}
	BX_CPU_CLASS_PTR eflags.x86.eax = x86_lf_flags;
#endif //#if (HOST_CPU_IS_I80386==1)

}

	void
BX_CPU_C::CMP_GwEGw(BX_CPU_C *icpu,bxInstruction_c *i)
{
	Bit16u op1, op2, sum;

	op1 = READ_VIRTUAL_16BIT_REG(MODRMnnn(i));

	op2 = READ_VIRTUAL_16BIT_REG(MODRMrm(i));

	sum = op1 - op2;


#if (HOST_CPU_IS_I80386==0)
	SET_FLAGS_OSZAPC_16(op1,op2,sum,BX_INSTR_CMP16);
#endif //#if (HOST_CPU_IS_I80386==0)
#if (HOST_CPU_IS_I80386==1) 
	Bit32u x86_lf_flags = BX_CPU_CLASS_PTR eflags.x86.eax;
	__asm
	{
		mov dx,op2
		CMP op1,dx
		lahf
		seto al
		mov x86_lf_flags,eax
	}
	BX_CPU_CLASS_PTR eflags.x86.eax = x86_lf_flags;
#endif //#if (HOST_CPU_IS_I80386==1)

}

	void
BX_CPU_C::CMP_GdEGd(BX_CPU_C *icpu,bxInstruction_c *i)
{
	Bit32u op1, op2, sum;

	op1 = READ_VIRTUAL_32BIT_REG(MODRMnnn(i));

	op2 = READ_VIRTUAL_32BIT_REG(MODRMrm(i));

	sum = op1 - op2;


#if (HOST_CPU_IS_I80386==0)
	SET_FLAGS_OSZAPC_32(op1,op2,sum,BX_INSTR_CMP32);
#endif //#if (HOST_CPU_IS_I80386==0)
#if (HOST_CPU_IS_I80386==1) 
	Bit32u x86_lf_flags = BX_CPU_CLASS_PTR eflags.x86.eax;
	__asm
	{
		mov edx,op2
		CMP op1,edx
		lahf
		seto al
		mov x86_lf_flags,eax
	}
	BX_CPU_CLASS_PTR eflags.x86.eax = x86_lf_flags;
#endif //#if (HOST_CPU_IS_I80386==1)

}

	void
BX_CPU_C::CMP_EGbIb(BX_CPU_C *icpu,bxInstruction_c *i)
{
	Bit8u op1, op2, sum;

	op1 = READ_VIRTUAL_8BIT_REG(MODRMrm(i));

	op2 = IMMEDIATEIb(i);

	sum = op1 - op2;


#if (HOST_CPU_IS_I80386==0)
	SET_FLAGS_OSZAPC_8(op1,op2,sum,BX_INSTR_CMP8);
#endif //#if (HOST_CPU_IS_I80386==0)
#if (HOST_CPU_IS_I80386==1) 
	Bit32u x86_lf_flags = BX_CPU_CLASS_PTR eflags.x86.eax;
	__asm
	{
		mov dl,op2
		CMP op1,dl
		lahf
		seto al
		mov x86_lf_flags,eax
	}
	BX_CPU_CLASS_PTR eflags.x86.eax = x86_lf_flags;
#endif //#if (HOST_CPU_IS_I80386==1)

}

	void
BX_CPU_C::CMP_EGwIw(BX_CPU_C *icpu,bxInstruction_c *i)
{
	Bit16u op1, op2, sum;

	op1 = READ_VIRTUAL_16BIT_REG(MODRMrm(i));

	op2 = IMMEDIATEIw(i);

	sum = op1 - op2;


#if (HOST_CPU_IS_I80386==0)
	SET_FLAGS_OSZAPC_16(op1,op2,sum,BX_INSTR_CMP16);
#endif //#if (HOST_CPU_IS_I80386==0)
#if (HOST_CPU_IS_I80386==1) 
	Bit32u x86_lf_flags = BX_CPU_CLASS_PTR eflags.x86.eax;
	__asm
	{
		mov dx,op2
		CMP op1,dx
		lahf
		seto al
		mov x86_lf_flags,eax
	}
	BX_CPU_CLASS_PTR eflags.x86.eax = x86_lf_flags;
#endif //#if (HOST_CPU_IS_I80386==1)

}

	void
BX_CPU_C::CMP_EGdId(BX_CPU_C *icpu,bxInstruction_c *i)
{
	Bit32u op1, op2, sum;

	op1 = READ_VIRTUAL_32BIT_REG(MODRMrm(i));

	op2 = IMMEDIATEId(i);

	sum = op1 - op2;


#if (HOST_CPU_IS_I80386==0)
	SET_FLAGS_OSZAPC_32(op1,op2,sum,BX_INSTR_CMP32);
#endif //#if (HOST_CPU_IS_I80386==0)
#if (HOST_CPU_IS_I80386==1) 
	Bit32u x86_lf_flags = BX_CPU_CLASS_PTR eflags.x86.eax;
	__asm
	{
		mov edx,op2
		CMP op1,edx
		lahf
		seto al
		mov x86_lf_flags,eax
	}
	BX_CPU_CLASS_PTR eflags.x86.eax = x86_lf_flags;
#endif //#if (HOST_CPU_IS_I80386==1)

}

	void
BX_CPU_C::CMP_ALIb(BX_CPU_C *icpu,bxInstruction_c *i)
{
	Bit8u op1, op2, sum;

	op1 = READ_VIRTUAL_8BIT_REG(0);

	op2 = IMMEDIATEIb(i);

	sum = op1 - op2;


#if (HOST_CPU_IS_I80386==0)
	SET_FLAGS_OSZAPC_8(op1,op2,sum,BX_INSTR_CMP8);
#endif //#if (HOST_CPU_IS_I80386==0)
#if (HOST_CPU_IS_I80386==1) 
	Bit32u x86_lf_flags = BX_CPU_CLASS_PTR eflags.x86.eax;
	__asm
	{
		mov dl,op2
		CMP op1,dl
		lahf
		seto al
		mov x86_lf_flags,eax
	}
	BX_CPU_CLASS_PTR eflags.x86.eax = x86_lf_flags;
#endif //#if (HOST_CPU_IS_I80386==1)

}

	void
BX_CPU_C::CMP_AXIw(BX_CPU_C *icpu,bxInstruction_c *i)
{
	Bit16u op1, op2, sum;

	op1 = READ_VIRTUAL_16BIT_REG(0);

	op2 = IMMEDIATEIw(i);

	sum = op1 - op2;


#if (HOST_CPU_IS_I80386==0)
	SET_FLAGS_OSZAPC_16(op1,op2,sum,BX_INSTR_CMP16);
#endif //#if (HOST_CPU_IS_I80386==0)
#if (HOST_CPU_IS_I80386==1) 
	Bit32u x86_lf_flags = BX_CPU_CLASS_PTR eflags.x86.eax;
	__asm
	{
		mov dx,op2
		CMP op1,dx
		lahf
		seto al
		mov x86_lf_flags,eax
	}
	BX_CPU_CLASS_PTR eflags.x86.eax = x86_lf_flags;
#endif //#if (HOST_CPU_IS_I80386==1)

}

	void
BX_CPU_C::CMP_EAXId(BX_CPU_C *icpu,bxInstruction_c *i)
{
	Bit32u op1, op2, sum;

	op1 = READ_VIRTUAL_32BIT_REG(0);

	op2 = IMMEDIATEId(i);

	sum = op1 - op2;


#if (HOST_CPU_IS_I80386==0)
	SET_FLAGS_OSZAPC_32(op1,op2,sum,BX_INSTR_CMP32);
#endif //#if (HOST_CPU_IS_I80386==0)
#if (HOST_CPU_IS_I80386==1) 
	Bit32u x86_lf_flags = BX_CPU_CLASS_PTR eflags.x86.eax;
	__asm
	{
		mov edx,op2
		CMP op1,edx
		lahf
		seto al
		mov x86_lf_flags,eax
	}
	BX_CPU_CLASS_PTR eflags.x86.eax = x86_lf_flags;
#endif //#if (HOST_CPU_IS_I80386==1)

}

	void
BX_CPU_C::CMP_EEbGb(BX_CPU_C *icpu,bxInstruction_c *i)
{
	Bit8u op1, op2, sum;

	READ_VIRTUAL_BYTE(MODRMSeg(i),RMAddr(i),&op1);

	op2 = READ_VIRTUAL_8BIT_REG(MODRMnnn(i));

	sum = op1 - op2;


#if (HOST_CPU_IS_I80386==0)
	SET_FLAGS_OSZAPC_8(op1,op2,sum,BX_INSTR_CMP8);
#endif //#if (HOST_CPU_IS_I80386==0)
#if (HOST_CPU_IS_I80386==1) 
	Bit32u x86_lf_flags = BX_CPU_CLASS_PTR eflags.x86.eax;
	__asm
	{
		mov dl,op2
		CMP op1,dl
		lahf
		seto al
		mov x86_lf_flags,eax
	}
	BX_CPU_CLASS_PTR eflags.x86.eax = x86_lf_flags;
#endif //#if (HOST_CPU_IS_I80386==1)

}

	void
BX_CPU_C::CMP_EEwGw(BX_CPU_C *icpu,bxInstruction_c *i)
{
	Bit16u op1, op2, sum;

	READ_VIRTUAL_WORD(MODRMSeg(i),RMAddr(i),&op1);

	op2 = READ_VIRTUAL_16BIT_REG(MODRMnnn(i));

	sum = op1 - op2;


#if (HOST_CPU_IS_I80386==0)
	SET_FLAGS_OSZAPC_16(op1,op2,sum,BX_INSTR_CMP16);
#endif //#if (HOST_CPU_IS_I80386==0)
#if (HOST_CPU_IS_I80386==1) 
	Bit32u x86_lf_flags = BX_CPU_CLASS_PTR eflags.x86.eax;
	__asm
	{
		mov dx,op2
		CMP op1,dx
		lahf
		seto al
		mov x86_lf_flags,eax
	}
	BX_CPU_CLASS_PTR eflags.x86.eax = x86_lf_flags;
#endif //#if (HOST_CPU_IS_I80386==1)

}

	void
BX_CPU_C::CMP_EEdGd(BX_CPU_C *icpu,bxInstruction_c *i)
{
	Bit32u op1, op2, sum;

	READ_VIRTUAL_DWORD(MODRMSeg(i),RMAddr(i),&op1);

	op2 = READ_VIRTUAL_32BIT_REG(MODRMnnn(i));

	sum = op1 - op2;


#if (HOST_CPU_IS_I80386==0)
	SET_FLAGS_OSZAPC_32(op1,op2,sum,BX_INSTR_CMP32);
#endif //#if (HOST_CPU_IS_I80386==0)
#if (HOST_CPU_IS_I80386==1) 
	Bit32u x86_lf_flags = BX_CPU_CLASS_PTR eflags.x86.eax;
	__asm
	{
		mov edx,op2
		CMP op1,edx
		lahf
		seto al
		mov x86_lf_flags,eax
	}
	BX_CPU_CLASS_PTR eflags.x86.eax = x86_lf_flags;
#endif //#if (HOST_CPU_IS_I80386==1)

}

	void
BX_CPU_C::CMP_GbEEb(BX_CPU_C *icpu,bxInstruction_c *i)
{
	Bit8u op1, op2, sum;

	op1 = READ_VIRTUAL_8BIT_REG(MODRMnnn(i));

	READ_VIRTUAL_BYTE(MODRMSeg(i),RMAddr(i),&op2);

	sum = op1 - op2;


#if (HOST_CPU_IS_I80386==0)
	SET_FLAGS_OSZAPC_8(op1,op2,sum,BX_INSTR_CMP8);
#endif //#if (HOST_CPU_IS_I80386==0)
#if (HOST_CPU_IS_I80386==1) 
	Bit32u x86_lf_flags = BX_CPU_CLASS_PTR eflags.x86.eax;
	__asm
	{
		mov dl,op2
		CMP op1,dl
		lahf
		seto al
		mov x86_lf_flags,eax
	}
	BX_CPU_CLASS_PTR eflags.x86.eax = x86_lf_flags;
#endif //#if (HOST_CPU_IS_I80386==1)

}

	void
BX_CPU_C::CMP_GwEEw(BX_CPU_C *icpu,bxInstruction_c *i)
{
	Bit16u op1, op2, sum;

	op1 = READ_VIRTUAL_16BIT_REG(MODRMnnn(i));

	READ_VIRTUAL_WORD(MODRMSeg(i),RMAddr(i),&op2);

	sum = op1 - op2;


#if (HOST_CPU_IS_I80386==0)
	SET_FLAGS_OSZAPC_16(op1,op2,sum,BX_INSTR_CMP16);
#endif //#if (HOST_CPU_IS_I80386==0)
#if (HOST_CPU_IS_I80386==1) 
	Bit32u x86_lf_flags = BX_CPU_CLASS_PTR eflags.x86.eax;
	__asm
	{
		mov dx,op2
		CMP op1,dx
		lahf
		seto al
		mov x86_lf_flags,eax
	}
	BX_CPU_CLASS_PTR eflags.x86.eax = x86_lf_flags;
#endif //#if (HOST_CPU_IS_I80386==1)

}

	void
BX_CPU_C::CMP_GdEEd(BX_CPU_C *icpu,bxInstruction_c *i)
{
	Bit32u op1, op2, sum;

	op1 = READ_VIRTUAL_32BIT_REG(MODRMnnn(i));

	READ_VIRTUAL_DWORD(MODRMSeg(i),RMAddr(i),&op2);

	sum = op1 - op2;


#if (HOST_CPU_IS_I80386==0)
	SET_FLAGS_OSZAPC_32(op1,op2,sum,BX_INSTR_CMP32);
#endif //#if (HOST_CPU_IS_I80386==0)
#if (HOST_CPU_IS_I80386==1) 
	Bit32u x86_lf_flags = BX_CPU_CLASS_PTR eflags.x86.eax;
	__asm
	{
		mov edx,op2
		CMP op1,edx
		lahf
		seto al
		mov x86_lf_flags,eax
	}
	BX_CPU_CLASS_PTR eflags.x86.eax = x86_lf_flags;
#endif //#if (HOST_CPU_IS_I80386==1)

}

	void
BX_CPU_C::CMP_EEbIb(BX_CPU_C *icpu,bxInstruction_c *i)
{
	Bit8u op1, op2, sum;

	READ_VIRTUAL_BYTE(MODRMSeg(i),RMAddr(i),&op1);

	op2 = IMMEDIATEIb(i);

	sum = op1 - op2;


#if (HOST_CPU_IS_I80386==0)
	SET_FLAGS_OSZAPC_8(op1,op2,sum,BX_INSTR_CMP8);
#endif //#if (HOST_CPU_IS_I80386==0)
#if (HOST_CPU_IS_I80386==1) 
	Bit32u x86_lf_flags = BX_CPU_CLASS_PTR eflags.x86.eax;
	__asm
	{
		mov dl,op2
		CMP op1,dl
		lahf
		seto al
		mov x86_lf_flags,eax
	}
	BX_CPU_CLASS_PTR eflags.x86.eax = x86_lf_flags;
#endif //#if (HOST_CPU_IS_I80386==1)

}

	void
BX_CPU_C::CMP_EEwIw(BX_CPU_C *icpu,bxInstruction_c *i)
{
	Bit16u op1, op2, sum;

	READ_VIRTUAL_WORD(MODRMSeg(i),RMAddr(i),&op1);

	op2 = IMMEDIATEIw(i);

	sum = op1 - op2;


#if (HOST_CPU_IS_I80386==0)
	SET_FLAGS_OSZAPC_16(op1,op2,sum,BX_INSTR_CMP16);
#endif //#if (HOST_CPU_IS_I80386==0)
#if (HOST_CPU_IS_I80386==1) 
	Bit32u x86_lf_flags = BX_CPU_CLASS_PTR eflags.x86.eax;
	__asm
	{
		mov dx,op2
		CMP op1,dx
		lahf
		seto al
		mov x86_lf_flags,eax
	}
	BX_CPU_CLASS_PTR eflags.x86.eax = x86_lf_flags;
#endif //#if (HOST_CPU_IS_I80386==1)

}

	void
BX_CPU_C::CMP_EEdId(BX_CPU_C *icpu,bxInstruction_c *i)
{
	Bit32u op1, op2, sum;

	READ_VIRTUAL_DWORD(MODRMSeg(i),RMAddr(i),&op1);

	op2 = IMMEDIATEId(i);

	sum = op1 - op2;


#if (HOST_CPU_IS_I80386==0)
	SET_FLAGS_OSZAPC_32(op1,op2,sum,BX_INSTR_CMP32);
#endif //#if (HOST_CPU_IS_I80386==0)
#if (HOST_CPU_IS_I80386==1) 
	Bit32u x86_lf_flags = BX_CPU_CLASS_PTR eflags.x86.eax;
	__asm
	{
		mov edx,op2
		CMP op1,edx
		lahf
		seto al
		mov x86_lf_flags,eax
	}
	BX_CPU_CLASS_PTR eflags.x86.eax = x86_lf_flags;
#endif //#if (HOST_CPU_IS_I80386==1)

}

	void
BX_CPU_C::TEST_EGbGb(BX_CPU_C *icpu,bxInstruction_c *i)
{
	Bit8u op1, op2, sum;

	op1 = READ_VIRTUAL_8BIT_REG(MODRMrm(i));

	op2 = READ_VIRTUAL_8BIT_REG(MODRMnnn(i));

	sum = op1 & op2;


#if (HOST_CPU_IS_I80386==0)
	BX_CPU_CLASS_PTR lf_entrys[BX_LF_INDEX_OSZAPC].result_8 = sum;
	BX_CPU_CLASS_PTR lf_entrys[BX_LF_INDEX_OSZAPC].instr = BX_INSTR_TEST8;
	BX_CPU_CLASS_PTR lf_flags_status = BX_LF_MASK_OSZAPC;
#endif //#if (HOST_CPU_IS_I80386==0)
#if (HOST_CPU_IS_I80386==1) 
	Bit32u x86_lf_flags = BX_CPU_CLASS_PTR eflags.x86.eax;
	__asm
	{
		mov dl,op2
		TEST op1,dl
		lahf
		seto al
		mov x86_lf_flags,eax
	}
	BX_CPU_CLASS_PTR eflags.x86.eax = x86_lf_flags;
#endif //#if (HOST_CPU_IS_I80386==1)

}

	void
BX_CPU_C::TEST_EGwGw(BX_CPU_C *icpu,bxInstruction_c *i)
{
	Bit16u op1, op2, sum;

	op1 = READ_VIRTUAL_16BIT_REG(MODRMrm(i));

	op2 = READ_VIRTUAL_16BIT_REG(MODRMnnn(i));

	sum = op1 & op2;


#if (HOST_CPU_IS_I80386==0)
	BX_CPU_CLASS_PTR lf_entrys[BX_LF_INDEX_OSZAPC].result_16 = sum;
	BX_CPU_CLASS_PTR lf_entrys[BX_LF_INDEX_OSZAPC].instr = BX_INSTR_TEST16;
	BX_CPU_CLASS_PTR lf_flags_status = BX_LF_MASK_OSZAPC;
#endif //#if (HOST_CPU_IS_I80386==0)
#if (HOST_CPU_IS_I80386==1) 
	Bit32u x86_lf_flags = BX_CPU_CLASS_PTR eflags.x86.eax;
	__asm
	{
		mov dx,op2
		TEST op1,dx
		lahf
		seto al
		mov x86_lf_flags,eax
	}
	BX_CPU_CLASS_PTR eflags.x86.eax = x86_lf_flags;
#endif //#if (HOST_CPU_IS_I80386==1)

}

	void
BX_CPU_C::TEST_EGdGd(BX_CPU_C *icpu,bxInstruction_c *i)
{
	Bit32u op1, op2, sum;

	op1 = READ_VIRTUAL_32BIT_REG(MODRMrm(i));

	op2 = READ_VIRTUAL_32BIT_REG(MODRMnnn(i));

	sum = op1 & op2;


#if (HOST_CPU_IS_I80386==0)
	BX_CPU_CLASS_PTR lf_entrys[BX_LF_INDEX_OSZAPC].result_32 = sum;
	BX_CPU_CLASS_PTR lf_entrys[BX_LF_INDEX_OSZAPC].instr = BX_INSTR_TEST32;
	BX_CPU_CLASS_PTR lf_flags_status = BX_LF_MASK_OSZAPC;
#endif //#if (HOST_CPU_IS_I80386==0)
#if (HOST_CPU_IS_I80386==1) 
	Bit32u x86_lf_flags = BX_CPU_CLASS_PTR eflags.x86.eax;
	__asm
	{
		mov edx,op2
		TEST op1,edx
		lahf
		seto al
		mov x86_lf_flags,eax
	}
	BX_CPU_CLASS_PTR eflags.x86.eax = x86_lf_flags;
#endif //#if (HOST_CPU_IS_I80386==1)

}

	void
BX_CPU_C::TEST_GbEGb(BX_CPU_C *icpu,bxInstruction_c *i)
{
	Bit8u op1, op2, sum;

	op1 = READ_VIRTUAL_8BIT_REG(MODRMnnn(i));

	op2 = READ_VIRTUAL_8BIT_REG(MODRMrm(i));

	sum = op1 & op2;


#if (HOST_CPU_IS_I80386==0)
	BX_CPU_CLASS_PTR lf_entrys[BX_LF_INDEX_OSZAPC].result_8 = sum;
	BX_CPU_CLASS_PTR lf_entrys[BX_LF_INDEX_OSZAPC].instr = BX_INSTR_TEST8;
	BX_CPU_CLASS_PTR lf_flags_status = BX_LF_MASK_OSZAPC;
#endif //#if (HOST_CPU_IS_I80386==0)
#if (HOST_CPU_IS_I80386==1) 
	Bit32u x86_lf_flags = BX_CPU_CLASS_PTR eflags.x86.eax;
	__asm
	{
		mov dl,op2
		TEST op1,dl
		lahf
		seto al
		mov x86_lf_flags,eax
	}
	BX_CPU_CLASS_PTR eflags.x86.eax = x86_lf_flags;
#endif //#if (HOST_CPU_IS_I80386==1)

}

	void
BX_CPU_C::TEST_GwEGw(BX_CPU_C *icpu,bxInstruction_c *i)
{
	Bit16u op1, op2, sum;

	op1 = READ_VIRTUAL_16BIT_REG(MODRMnnn(i));

	op2 = READ_VIRTUAL_16BIT_REG(MODRMrm(i));

	sum = op1 & op2;


#if (HOST_CPU_IS_I80386==0)
	BX_CPU_CLASS_PTR lf_entrys[BX_LF_INDEX_OSZAPC].result_16 = sum;
	BX_CPU_CLASS_PTR lf_entrys[BX_LF_INDEX_OSZAPC].instr = BX_INSTR_TEST16;
	BX_CPU_CLASS_PTR lf_flags_status = BX_LF_MASK_OSZAPC;
#endif //#if (HOST_CPU_IS_I80386==0)
#if (HOST_CPU_IS_I80386==1) 
	Bit32u x86_lf_flags = BX_CPU_CLASS_PTR eflags.x86.eax;
	__asm
	{
		mov dx,op2
		TEST op1,dx
		lahf
		seto al
		mov x86_lf_flags,eax
	}
	BX_CPU_CLASS_PTR eflags.x86.eax = x86_lf_flags;
#endif //#if (HOST_CPU_IS_I80386==1)

}

	void
BX_CPU_C::TEST_GdEGd(BX_CPU_C *icpu,bxInstruction_c *i)
{
	Bit32u op1, op2, sum;

	op1 = READ_VIRTUAL_32BIT_REG(MODRMnnn(i));

	op2 = READ_VIRTUAL_32BIT_REG(MODRMrm(i));

	sum = op1 & op2;


#if (HOST_CPU_IS_I80386==0)
	BX_CPU_CLASS_PTR lf_entrys[BX_LF_INDEX_OSZAPC].result_32 = sum;
	BX_CPU_CLASS_PTR lf_entrys[BX_LF_INDEX_OSZAPC].instr = BX_INSTR_TEST32;
	BX_CPU_CLASS_PTR lf_flags_status = BX_LF_MASK_OSZAPC;
#endif //#if (HOST_CPU_IS_I80386==0)
#if (HOST_CPU_IS_I80386==1) 
	Bit32u x86_lf_flags = BX_CPU_CLASS_PTR eflags.x86.eax;
	__asm
	{
		mov edx,op2
		TEST op1,edx
		lahf
		seto al
		mov x86_lf_flags,eax
	}
	BX_CPU_CLASS_PTR eflags.x86.eax = x86_lf_flags;
#endif //#if (HOST_CPU_IS_I80386==1)

}

	void
BX_CPU_C::TEST_EGbIb(BX_CPU_C *icpu,bxInstruction_c *i)
{
	Bit8u op1, op2, sum;

	op1 = READ_VIRTUAL_8BIT_REG(MODRMrm(i));

	op2 = IMMEDIATEIb(i);

	sum = op1 & op2;


#if (HOST_CPU_IS_I80386==0)
	BX_CPU_CLASS_PTR lf_entrys[BX_LF_INDEX_OSZAPC].result_8 = sum;
	BX_CPU_CLASS_PTR lf_entrys[BX_LF_INDEX_OSZAPC].instr = BX_INSTR_TEST8;
	BX_CPU_CLASS_PTR lf_flags_status = BX_LF_MASK_OSZAPC;
#endif //#if (HOST_CPU_IS_I80386==0)
#if (HOST_CPU_IS_I80386==1) 
	Bit32u x86_lf_flags = BX_CPU_CLASS_PTR eflags.x86.eax;
	__asm
	{
		mov dl,op2
		TEST op1,dl
		lahf
		seto al
		mov x86_lf_flags,eax
	}
	BX_CPU_CLASS_PTR eflags.x86.eax = x86_lf_flags;
#endif //#if (HOST_CPU_IS_I80386==1)

}

	void
BX_CPU_C::TEST_EGwIw(BX_CPU_C *icpu,bxInstruction_c *i)
{
	Bit16u op1, op2, sum;

	op1 = READ_VIRTUAL_16BIT_REG(MODRMrm(i));

	op2 = IMMEDIATEIw(i);

	sum = op1 & op2;


#if (HOST_CPU_IS_I80386==0)
	BX_CPU_CLASS_PTR lf_entrys[BX_LF_INDEX_OSZAPC].result_16 = sum;
	BX_CPU_CLASS_PTR lf_entrys[BX_LF_INDEX_OSZAPC].instr = BX_INSTR_TEST16;
	BX_CPU_CLASS_PTR lf_flags_status = BX_LF_MASK_OSZAPC;
#endif //#if (HOST_CPU_IS_I80386==0)
#if (HOST_CPU_IS_I80386==1) 
	Bit32u x86_lf_flags = BX_CPU_CLASS_PTR eflags.x86.eax;
	__asm
	{
		mov dx,op2
		TEST op1,dx
		lahf
		seto al
		mov x86_lf_flags,eax
	}
	BX_CPU_CLASS_PTR eflags.x86.eax = x86_lf_flags;
#endif //#if (HOST_CPU_IS_I80386==1)

}

	void
BX_CPU_C::TEST_EGdId(BX_CPU_C *icpu,bxInstruction_c *i)
{
	Bit32u op1, op2, sum;

	op1 = READ_VIRTUAL_32BIT_REG(MODRMrm(i));

	op2 = IMMEDIATEId(i);

	sum = op1 & op2;


#if (HOST_CPU_IS_I80386==0)
	BX_CPU_CLASS_PTR lf_entrys[BX_LF_INDEX_OSZAPC].result_32 = sum;
	BX_CPU_CLASS_PTR lf_entrys[BX_LF_INDEX_OSZAPC].instr = BX_INSTR_TEST32;
	BX_CPU_CLASS_PTR lf_flags_status = BX_LF_MASK_OSZAPC;
#endif //#if (HOST_CPU_IS_I80386==0)
#if (HOST_CPU_IS_I80386==1) 
	Bit32u x86_lf_flags = BX_CPU_CLASS_PTR eflags.x86.eax;
	__asm
	{
		mov edx,op2
		TEST op1,edx
		lahf
		seto al
		mov x86_lf_flags,eax
	}
	BX_CPU_CLASS_PTR eflags.x86.eax = x86_lf_flags;
#endif //#if (HOST_CPU_IS_I80386==1)

}

	void
BX_CPU_C::TEST_ALIb(BX_CPU_C *icpu,bxInstruction_c *i)
{
	Bit8u op1, op2, sum;

	op1 = READ_VIRTUAL_8BIT_REG(0);

	op2 = IMMEDIATEIb(i);

	sum = op1 & op2;


#if (HOST_CPU_IS_I80386==0)
	BX_CPU_CLASS_PTR lf_entrys[BX_LF_INDEX_OSZAPC].result_8 = sum;
	BX_CPU_CLASS_PTR lf_entrys[BX_LF_INDEX_OSZAPC].instr = BX_INSTR_TEST8;
	BX_CPU_CLASS_PTR lf_flags_status = BX_LF_MASK_OSZAPC;
#endif //#if (HOST_CPU_IS_I80386==0)
#if (HOST_CPU_IS_I80386==1) 
	Bit32u x86_lf_flags = BX_CPU_CLASS_PTR eflags.x86.eax;
	__asm
	{
		mov dl,op2
		TEST op1,dl
		lahf
		seto al
		mov x86_lf_flags,eax
	}
	BX_CPU_CLASS_PTR eflags.x86.eax = x86_lf_flags;
#endif //#if (HOST_CPU_IS_I80386==1)

}

	void
BX_CPU_C::TEST_AXIw(BX_CPU_C *icpu,bxInstruction_c *i)
{
	Bit16u op1, op2, sum;

	op1 = READ_VIRTUAL_16BIT_REG(0);

	op2 = IMMEDIATEIw(i);

	sum = op1 & op2;


#if (HOST_CPU_IS_I80386==0)
	BX_CPU_CLASS_PTR lf_entrys[BX_LF_INDEX_OSZAPC].result_16 = sum;
	BX_CPU_CLASS_PTR lf_entrys[BX_LF_INDEX_OSZAPC].instr = BX_INSTR_TEST16;
	BX_CPU_CLASS_PTR lf_flags_status = BX_LF_MASK_OSZAPC;
#endif //#if (HOST_CPU_IS_I80386==0)
#if (HOST_CPU_IS_I80386==1) 
	Bit32u x86_lf_flags = BX_CPU_CLASS_PTR eflags.x86.eax;
	__asm
	{
		mov dx,op2
		TEST op1,dx
		lahf
		seto al
		mov x86_lf_flags,eax
	}
	BX_CPU_CLASS_PTR eflags.x86.eax = x86_lf_flags;
#endif //#if (HOST_CPU_IS_I80386==1)

}

	void
BX_CPU_C::TEST_EAXId(BX_CPU_C *icpu,bxInstruction_c *i)
{
	Bit32u op1, op2, sum;

	op1 = READ_VIRTUAL_32BIT_REG(0);

	op2 = IMMEDIATEId(i);

	sum = op1 & op2;


#if (HOST_CPU_IS_I80386==0)
	BX_CPU_CLASS_PTR lf_entrys[BX_LF_INDEX_OSZAPC].result_32 = sum;
	BX_CPU_CLASS_PTR lf_entrys[BX_LF_INDEX_OSZAPC].instr = BX_INSTR_TEST32;
	BX_CPU_CLASS_PTR lf_flags_status = BX_LF_MASK_OSZAPC;
#endif //#if (HOST_CPU_IS_I80386==0)
#if (HOST_CPU_IS_I80386==1) 
	Bit32u x86_lf_flags = BX_CPU_CLASS_PTR eflags.x86.eax;
	__asm
	{
		mov edx,op2
		TEST op1,edx
		lahf
		seto al
		mov x86_lf_flags,eax
	}
	BX_CPU_CLASS_PTR eflags.x86.eax = x86_lf_flags;
#endif //#if (HOST_CPU_IS_I80386==1)

}

	void
BX_CPU_C::TEST_EEbGb(BX_CPU_C *icpu,bxInstruction_c *i)
{
	Bit8u op1, op2, sum;

	READ_VIRTUAL_BYTE(MODRMSeg(i),RMAddr(i),&op1);

	op2 = READ_VIRTUAL_8BIT_REG(MODRMnnn(i));

	sum = op1 & op2;


#if (HOST_CPU_IS_I80386==0)
	BX_CPU_CLASS_PTR lf_entrys[BX_LF_INDEX_OSZAPC].result_8 = sum;
	BX_CPU_CLASS_PTR lf_entrys[BX_LF_INDEX_OSZAPC].instr = BX_INSTR_TEST8;
	BX_CPU_CLASS_PTR lf_flags_status = BX_LF_MASK_OSZAPC;
#endif //#if (HOST_CPU_IS_I80386==0)
#if (HOST_CPU_IS_I80386==1) 
	Bit32u x86_lf_flags = BX_CPU_CLASS_PTR eflags.x86.eax;
	__asm
	{
		mov dl,op2
		TEST op1,dl
		lahf
		seto al
		mov x86_lf_flags,eax
	}
	BX_CPU_CLASS_PTR eflags.x86.eax = x86_lf_flags;
#endif //#if (HOST_CPU_IS_I80386==1)

}

	void
BX_CPU_C::TEST_EEwGw(BX_CPU_C *icpu,bxInstruction_c *i)
{
	Bit16u op1, op2, sum;

	READ_VIRTUAL_WORD(MODRMSeg(i),RMAddr(i),&op1);

	op2 = READ_VIRTUAL_16BIT_REG(MODRMnnn(i));

	sum = op1 & op2;


#if (HOST_CPU_IS_I80386==0)
	BX_CPU_CLASS_PTR lf_entrys[BX_LF_INDEX_OSZAPC].result_16 = sum;
	BX_CPU_CLASS_PTR lf_entrys[BX_LF_INDEX_OSZAPC].instr = BX_INSTR_TEST16;
	BX_CPU_CLASS_PTR lf_flags_status = BX_LF_MASK_OSZAPC;
#endif //#if (HOST_CPU_IS_I80386==0)
#if (HOST_CPU_IS_I80386==1) 
	Bit32u x86_lf_flags = BX_CPU_CLASS_PTR eflags.x86.eax;
	__asm
	{
		mov dx,op2
		TEST op1,dx
		lahf
		seto al
		mov x86_lf_flags,eax
	}
	BX_CPU_CLASS_PTR eflags.x86.eax = x86_lf_flags;
#endif //#if (HOST_CPU_IS_I80386==1)

}

	void
BX_CPU_C::TEST_EEdGd(BX_CPU_C *icpu,bxInstruction_c *i)
{
	Bit32u op1, op2, sum;

	READ_VIRTUAL_DWORD(MODRMSeg(i),RMAddr(i),&op1);

	op2 = READ_VIRTUAL_32BIT_REG(MODRMnnn(i));

	sum = op1 & op2;


#if (HOST_CPU_IS_I80386==0)
	BX_CPU_CLASS_PTR lf_entrys[BX_LF_INDEX_OSZAPC].result_32 = sum;
	BX_CPU_CLASS_PTR lf_entrys[BX_LF_INDEX_OSZAPC].instr = BX_INSTR_TEST32;
	BX_CPU_CLASS_PTR lf_flags_status = BX_LF_MASK_OSZAPC;
#endif //#if (HOST_CPU_IS_I80386==0)
#if (HOST_CPU_IS_I80386==1) 
	Bit32u x86_lf_flags = BX_CPU_CLASS_PTR eflags.x86.eax;
	__asm
	{
		mov edx,op2
		TEST op1,edx
		lahf
		seto al
		mov x86_lf_flags,eax
	}
	BX_CPU_CLASS_PTR eflags.x86.eax = x86_lf_flags;
#endif //#if (HOST_CPU_IS_I80386==1)

}

	void
BX_CPU_C::TEST_GbEEb(BX_CPU_C *icpu,bxInstruction_c *i)
{
	Bit8u op1, op2, sum;

	op1 = READ_VIRTUAL_8BIT_REG(MODRMnnn(i));

	READ_VIRTUAL_BYTE(MODRMSeg(i),RMAddr(i),&op2);

	sum = op1 & op2;


#if (HOST_CPU_IS_I80386==0)
	BX_CPU_CLASS_PTR lf_entrys[BX_LF_INDEX_OSZAPC].result_8 = sum;
	BX_CPU_CLASS_PTR lf_entrys[BX_LF_INDEX_OSZAPC].instr = BX_INSTR_TEST8;
	BX_CPU_CLASS_PTR lf_flags_status = BX_LF_MASK_OSZAPC;
#endif //#if (HOST_CPU_IS_I80386==0)
#if (HOST_CPU_IS_I80386==1) 
	Bit32u x86_lf_flags = BX_CPU_CLASS_PTR eflags.x86.eax;
	__asm
	{
		mov dl,op2
		TEST op1,dl
		lahf
		seto al
		mov x86_lf_flags,eax
	}
	BX_CPU_CLASS_PTR eflags.x86.eax = x86_lf_flags;
#endif //#if (HOST_CPU_IS_I80386==1)

}

	void
BX_CPU_C::TEST_GwEEw(BX_CPU_C *icpu,bxInstruction_c *i)
{
	Bit16u op1, op2, sum;

	op1 = READ_VIRTUAL_16BIT_REG(MODRMnnn(i));

	READ_VIRTUAL_WORD(MODRMSeg(i),RMAddr(i),&op2);

	sum = op1 & op2;


#if (HOST_CPU_IS_I80386==0)
	BX_CPU_CLASS_PTR lf_entrys[BX_LF_INDEX_OSZAPC].result_16 = sum;
	BX_CPU_CLASS_PTR lf_entrys[BX_LF_INDEX_OSZAPC].instr = BX_INSTR_TEST16;
	BX_CPU_CLASS_PTR lf_flags_status = BX_LF_MASK_OSZAPC;
#endif //#if (HOST_CPU_IS_I80386==0)
#if (HOST_CPU_IS_I80386==1) 
	Bit32u x86_lf_flags = BX_CPU_CLASS_PTR eflags.x86.eax;
	__asm
	{
		mov dx,op2
		TEST op1,dx
		lahf
		seto al
		mov x86_lf_flags,eax
	}
	BX_CPU_CLASS_PTR eflags.x86.eax = x86_lf_flags;
#endif //#if (HOST_CPU_IS_I80386==1)

}

	void
BX_CPU_C::TEST_GdEEd(BX_CPU_C *icpu,bxInstruction_c *i)
{
	Bit32u op1, op2, sum;

	op1 = READ_VIRTUAL_32BIT_REG(MODRMnnn(i));

	READ_VIRTUAL_DWORD(MODRMSeg(i),RMAddr(i),&op2);

	sum = op1 & op2;


#if (HOST_CPU_IS_I80386==0)
	BX_CPU_CLASS_PTR lf_entrys[BX_LF_INDEX_OSZAPC].result_32 = sum;
	BX_CPU_CLASS_PTR lf_entrys[BX_LF_INDEX_OSZAPC].instr = BX_INSTR_TEST32;
	BX_CPU_CLASS_PTR lf_flags_status = BX_LF_MASK_OSZAPC;
#endif //#if (HOST_CPU_IS_I80386==0)
#if (HOST_CPU_IS_I80386==1) 
	Bit32u x86_lf_flags = BX_CPU_CLASS_PTR eflags.x86.eax;
	__asm
	{
		mov edx,op2
		TEST op1,edx
		lahf
		seto al
		mov x86_lf_flags,eax
	}
	BX_CPU_CLASS_PTR eflags.x86.eax = x86_lf_flags;
#endif //#if (HOST_CPU_IS_I80386==1)

}

	void
BX_CPU_C::TEST_EEbIb(BX_CPU_C *icpu,bxInstruction_c *i)
{
	Bit8u op1, op2, sum;

	READ_VIRTUAL_BYTE(MODRMSeg(i),RMAddr(i),&op1);

	op2 = IMMEDIATEIb(i);

	sum = op1 & op2;


#if (HOST_CPU_IS_I80386==0)
	BX_CPU_CLASS_PTR lf_entrys[BX_LF_INDEX_OSZAPC].result_8 = sum;
	BX_CPU_CLASS_PTR lf_entrys[BX_LF_INDEX_OSZAPC].instr = BX_INSTR_TEST8;
	BX_CPU_CLASS_PTR lf_flags_status = BX_LF_MASK_OSZAPC;
#endif //#if (HOST_CPU_IS_I80386==0)
#if (HOST_CPU_IS_I80386==1) 
	Bit32u x86_lf_flags = BX_CPU_CLASS_PTR eflags.x86.eax;
	__asm
	{
		mov dl,op2
		TEST op1,dl
		lahf
		seto al
		mov x86_lf_flags,eax
	}
	BX_CPU_CLASS_PTR eflags.x86.eax = x86_lf_flags;
#endif //#if (HOST_CPU_IS_I80386==1)

}

	void
BX_CPU_C::TEST_EEwIw(BX_CPU_C *icpu,bxInstruction_c *i)
{
	Bit16u op1, op2, sum;

	READ_VIRTUAL_WORD(MODRMSeg(i),RMAddr(i),&op1);

	op2 = IMMEDIATEIw(i);

	sum = op1 & op2;


#if (HOST_CPU_IS_I80386==0)
	BX_CPU_CLASS_PTR lf_entrys[BX_LF_INDEX_OSZAPC].result_16 = sum;
	BX_CPU_CLASS_PTR lf_entrys[BX_LF_INDEX_OSZAPC].instr = BX_INSTR_TEST16;
	BX_CPU_CLASS_PTR lf_flags_status = BX_LF_MASK_OSZAPC;
#endif //#if (HOST_CPU_IS_I80386==0)
#if (HOST_CPU_IS_I80386==1) 
	Bit32u x86_lf_flags = BX_CPU_CLASS_PTR eflags.x86.eax;
	__asm
	{
		mov dx,op2
		TEST op1,dx
		lahf
		seto al
		mov x86_lf_flags,eax
	}
	BX_CPU_CLASS_PTR eflags.x86.eax = x86_lf_flags;
#endif //#if (HOST_CPU_IS_I80386==1)

}

	void
BX_CPU_C::TEST_EEdId(BX_CPU_C *icpu,bxInstruction_c *i)
{
	Bit32u op1, op2, sum;

	READ_VIRTUAL_DWORD(MODRMSeg(i),RMAddr(i),&op1);

	op2 = IMMEDIATEId(i);

	sum = op1 & op2;


#if (HOST_CPU_IS_I80386==0)
	BX_CPU_CLASS_PTR lf_entrys[BX_LF_INDEX_OSZAPC].result_32 = sum;
	BX_CPU_CLASS_PTR lf_entrys[BX_LF_INDEX_OSZAPC].instr = BX_INSTR_TEST32;
	BX_CPU_CLASS_PTR lf_flags_status = BX_LF_MASK_OSZAPC;
#endif //#if (HOST_CPU_IS_I80386==0)
#if (HOST_CPU_IS_I80386==1) 
	Bit32u x86_lf_flags = BX_CPU_CLASS_PTR eflags.x86.eax;
	__asm
	{
		mov edx,op2
		TEST op1,edx
		lahf
		seto al
		mov x86_lf_flags,eax
	}
	BX_CPU_CLASS_PTR eflags.x86.eax = x86_lf_flags;
#endif //#if (HOST_CPU_IS_I80386==1)

}

	void
BX_CPU_C::XADD_EGbGb(BX_CPU_C *icpu,bxInstruction_c *i)
{
#if (BX_CPU_LEVEL >= 4) || (BX_CPU_LEVEL_HACKED >= 4)
	Bit8u op2, op1, sum;
	/* XADD dst(r/m8), src(r8)
	 * temp <-- src + dst         | sum = op2 + op1
	 * src  <-- dst               | op2 = op1
	 * dst  <-- tmp               | op1 = sum
	 */
	/* op2 is a register, RMAddr(i) is an index of a register */
	op2 = READ_VIRTUAL_8BIT_REG(MODRMnnn(i));
	/* op1 is a register or memory reference */
	op1 = READ_VIRTUAL_8BIT_REG(MODRMrm(i));
	sum = op1 + op2;

	/* now write sum back to destination */
	// and write destination into source
	// Note: if both op1 & op2 are registers, the last one written
	//       should be the sum, as op1 & op2 may be the same register.
	//       For example:  XADD AL, AL
	WRITE_VIRTUAL_8BIT_REG(MODRMnnn(i), op1);
	WRITE_VIRTUAL_8BIT_REG(MODRMrm(i), sum);
#if (HOST_CPU_IS_I80386==0)
	SET_FLAGS_OSZAPC_8(op1,op2,sum,BX_INSTR_XADD8);

#endif //#if (HOST_CPU_IS_I80386==0) 

#if (HOST_CPU_IS_I80386==1)
	Bit32u x86_lf_flags;
	__asm
	{
		mov dl,op2
		XADD op1,dl
		lahf
		seto al
		mov x86_lf_flags,eax
	}
	BX_CPU_CLASS_PTR eflags.x86.eax = x86_lf_flags;
#endif //#if (HOST_CPU_IS_I80386==1) 

#else
	BX_PANIC(("XADD_EGbGb: not supported on < 80486"));
	UndefinedOpcode(icpu,i);
#endif
}

	void
BX_CPU_C::XADD_EGwGw(BX_CPU_C *icpu,bxInstruction_c *i)
{
#if (BX_CPU_LEVEL >= 4) || (BX_CPU_LEVEL_HACKED >= 4)
	Bit16u op2, op1, sum;
	/* XADD dst(r/m16), src(r16)
	 * temp <-- src + dst         | sum = op2 + op1
	 * src  <-- dst               | op2 = op1
	 * dst  <-- tmp               | op1 = sum
	 */
	/* op2 is a register, RMAddr(i) is an index of a register */
	op2 = READ_VIRTUAL_16BIT_REG(MODRMnnn(i));
	/* op1 is a register or memory reference */
	op1 = READ_VIRTUAL_16BIT_REG(MODRMrm(i));
	sum = op1 + op2;

	/* now write sum back to destination */
	// and write destination into source
	// Note: if both op1 & op2 are registers, the last one written
	//       should be the sum, as op1 & op2 may be the same register.
	//       For example:  XADD AL, AL
	WRITE_VIRTUAL_16BIT_REG(MODRMnnn(i), op1);
	WRITE_VIRTUAL_16BIT_REG(MODRMrm(i), sum);
#if (HOST_CPU_IS_I80386==0)
	SET_FLAGS_OSZAPC_16(op1,op2,sum,BX_INSTR_XADD16);

#endif //#if (HOST_CPU_IS_I80386==0) 

#if (HOST_CPU_IS_I80386==1)
	Bit32u x86_lf_flags;
	__asm
	{
		mov dx,op2
		XADD op1,dx
		lahf
		seto al
		mov x86_lf_flags,eax
	}
	BX_CPU_CLASS_PTR eflags.x86.eax = x86_lf_flags;
#endif //#if (HOST_CPU_IS_I80386==1) 

#else
	BX_PANIC(("XADD_EGwGw: not supported on < 80486"));
	UndefinedOpcode(icpu,i);
#endif
}

	void
BX_CPU_C::XADD_EGdGd(BX_CPU_C *icpu,bxInstruction_c *i)
{
#if (BX_CPU_LEVEL >= 4) || (BX_CPU_LEVEL_HACKED >= 4)
	Bit32u op2, op1, sum;
	/* XADD dst(r/m32), src(r32)
	 * temp <-- src + dst         | sum = op2 + op1
	 * src  <-- dst               | op2 = op1
	 * dst  <-- tmp               | op1 = sum
	 */
	/* op2 is a register, RMAddr(i) is an index of a register */
	op2 = READ_VIRTUAL_32BIT_REG(MODRMnnn(i));
	/* op1 is a register or memory reference */
	op1 = READ_VIRTUAL_32BIT_REG(MODRMrm(i));
	sum = op1 + op2;

	/* now write sum back to destination */
	// and write destination into source
	// Note: if both op1 & op2 are registers, the last one written
	//       should be the sum, as op1 & op2 may be the same register.
	//       For example:  XADD AL, AL
	WRITE_VIRTUAL_32BIT_REG(MODRMnnn(i), op1);
	WRITE_VIRTUAL_32BIT_REG(MODRMrm(i), sum);
#if (HOST_CPU_IS_I80386==0)
	SET_FLAGS_OSZAPC_32(op1,op2,sum,BX_INSTR_XADD32);

#endif //#if (HOST_CPU_IS_I80386==0) 

#if (HOST_CPU_IS_I80386==1)
	Bit32u x86_lf_flags;
	__asm
	{
		mov edx,op2
		XADD op1,edx
		lahf
		seto al
		mov x86_lf_flags,eax
	}
	BX_CPU_CLASS_PTR eflags.x86.eax = x86_lf_flags;
#endif //#if (HOST_CPU_IS_I80386==1) 

#else
	BX_PANIC(("XADD_EGdGd: not supported on < 80486"));
	UndefinedOpcode(icpu,i);
#endif
}

	void
BX_CPU_C::XADD_EEbGb(BX_CPU_C *icpu,bxInstruction_c *i)
{
#if (BX_CPU_LEVEL >= 4) || (BX_CPU_LEVEL_HACKED >= 4)
	Bit8u op2, op1, sum;
	/* XADD dst(r/m8), src(r8)
	 * temp <-- src + dst         | sum = op2 + op1
	 * src  <-- dst               | op2 = op1
	 * dst  <-- tmp               | op1 = sum
	 */
	/* op2 is a register, RMAddr(i) is an index of a register */
	op2 = READ_VIRTUAL_8BIT_REG(MODRMnnn(i));
	/* op1 is a register or memory reference */
	READ_RMW_VIRTUAL_BYTE(MODRMSeg(i),RMAddr(i),&op1);
	sum = op1 + op2;

	/* now write sum back to destination */
	WRITE_RMW_VIRTUAL_BYTE(sum);
	/* and write destination into source */
	WRITE_VIRTUAL_8BIT_REG(MODRMnnn(i), op1);
#if (HOST_CPU_IS_I80386==0)
	SET_FLAGS_OSZAPC_8(op1,op2,sum,BX_INSTR_XADD8);

#endif //#if (HOST_CPU_IS_I80386==0) 

#if (HOST_CPU_IS_I80386==1)
	Bit32u x86_lf_flags;
	__asm
	{
		mov dl,op2
		XADD op1,dl
		lahf
		seto al
		mov x86_lf_flags,eax
	}
	BX_CPU_CLASS_PTR eflags.x86.eax = x86_lf_flags;
#endif //#if (HOST_CPU_IS_I80386==1) 

#else
	BX_PANIC(("XADD_EEbGb: not supported on < 80486"));
	UndefinedOpcode(icpu,i);
#endif
}

	void
BX_CPU_C::XADD_EEwGw(BX_CPU_C *icpu,bxInstruction_c *i)
{
#if (BX_CPU_LEVEL >= 4) || (BX_CPU_LEVEL_HACKED >= 4)
	Bit16u op2, op1, sum;
	/* XADD dst(r/m16), src(r16)
	 * temp <-- src + dst         | sum = op2 + op1
	 * src  <-- dst               | op2 = op1
	 * dst  <-- tmp               | op1 = sum
	 */
	/* op2 is a register, RMAddr(i) is an index of a register */
	op2 = READ_VIRTUAL_16BIT_REG(MODRMnnn(i));
	/* op1 is a register or memory reference */
	READ_RMW_VIRTUAL_WORD(MODRMSeg(i),RMAddr(i),&op1);
	sum = op1 + op2;

	/* now write sum back to destination */
	WRITE_RMW_VIRTUAL_WORD(sum);
	/* and write destination into source */
	WRITE_VIRTUAL_16BIT_REG(MODRMnnn(i), op1);
#if (HOST_CPU_IS_I80386==0)
	SET_FLAGS_OSZAPC_16(op1,op2,sum,BX_INSTR_XADD16);

#endif //#if (HOST_CPU_IS_I80386==0) 

#if (HOST_CPU_IS_I80386==1)
	Bit32u x86_lf_flags;
	__asm
	{
		mov dx,op2
		XADD op1,dx
		lahf
		seto al
		mov x86_lf_flags,eax
	}
	BX_CPU_CLASS_PTR eflags.x86.eax = x86_lf_flags;
#endif //#if (HOST_CPU_IS_I80386==1) 

#else
	BX_PANIC(("XADD_EEwGw: not supported on < 80486"));
	UndefinedOpcode(icpu,i);
#endif
}

	void
BX_CPU_C::XADD_EEdGd(BX_CPU_C *icpu,bxInstruction_c *i)
{
#if (BX_CPU_LEVEL >= 4) || (BX_CPU_LEVEL_HACKED >= 4)
	Bit32u op2, op1, sum;
	/* XADD dst(r/m32), src(r32)
	 * temp <-- src + dst         | sum = op2 + op1
	 * src  <-- dst               | op2 = op1
	 * dst  <-- tmp               | op1 = sum
	 */
	/* op2 is a register, RMAddr(i) is an index of a register */
	op2 = READ_VIRTUAL_32BIT_REG(MODRMnnn(i));
	/* op1 is a register or memory reference */
	READ_RMW_VIRTUAL_DWORD(MODRMSeg(i),RMAddr(i),&op1);
	sum = op1 + op2;

	/* now write sum back to destination */
	WRITE_RMW_VIRTUAL_DWORD(sum);
	/* and write destination into source */
	WRITE_VIRTUAL_32BIT_REG(MODRMnnn(i), op1);
#if (HOST_CPU_IS_I80386==0)
	SET_FLAGS_OSZAPC_32(op1,op2,sum,BX_INSTR_XADD32);

#endif //#if (HOST_CPU_IS_I80386==0) 

#if (HOST_CPU_IS_I80386==1)
	Bit32u x86_lf_flags;
	__asm
	{
		mov edx,op2
		XADD op1,edx
		lahf
		seto al
		mov x86_lf_flags,eax
	}
	BX_CPU_CLASS_PTR eflags.x86.eax = x86_lf_flags;
#endif //#if (HOST_CPU_IS_I80386==1) 

#else
	BX_PANIC(("XADD_EEdGd: not supported on < 80486"));
	UndefinedOpcode(icpu,i);
#endif
}

	void
BX_CPU_C::CMPXCHG_EGbGb(BX_CPU_C *icpu,bxInstruction_c *i)
{
#if (BX_CPU_LEVEL >= 4) || (BX_CPU_LEVEL_HACKED >= 4)
	Bit8u op1, op2, diff;
	op1 = READ_VIRTUAL_8BIT_REG(MODRMrm(i));
	diff = READ_VIRTUAL_8BIT_REG(0) - op1;

#if (HOST_CPU_IS_I80386==0)

	SET_FLAGS_OSZAPC_8(READ_VIRTUAL_8BIT_REG(0),op1,diff,BX_INSTR_CMP8)

#endif //#if (HOST_CPU_IS_I80386==0) 

#if (HOST_CPU_IS_I80386==1)

	Bit8u temp;
	temp = READ_VIRTUAL_8BIT_REG(0);
	Bit32u x86_lf_flags = BX_CPU_CLASS_PTR eflags.x86.eax;
	__asm
	{
		mov dl,op1
		cmp temp,dl
		lahf
		seto al
		mov x86_lf_flags,eax
	}

	BX_CPU_CLASS_PTR eflags.x86.eax = x86_lf_flags;
#endif //#if (HOST_CPU_IS_I80386==1) 

	if (diff == 0)
	{	// if accumulator == dest
		// ZF = 1
		BX_CPU_CLASS_PTR set_ZF(1);
		// dest <-- src
		op2 = READ_VIRTUAL_8BIT_REG(MODRMnnn(i));
		WRITE_VIRTUAL_8BIT_REG(MODRMrm(i), op2);
	}
	else
	{
		// ZF = 0
		BX_CPU_CLASS_PTR set_ZF(0);
		// accumulator <-- dest
		READ_VIRTUAL_8BIT_REG(0) = op1;
	}
#else
	BX_PANIC(("CMPXCHG_EGbGb:"));
#endif
}

	void
BX_CPU_C::CMPXCHG_EGwGw(BX_CPU_C *icpu,bxInstruction_c *i)
{
#if (BX_CPU_LEVEL >= 4) || (BX_CPU_LEVEL_HACKED >= 4)
	Bit16u op1, op2, diff;
	op1 = READ_VIRTUAL_16BIT_REG(MODRMrm(i));
	diff = READ_VIRTUAL_16BIT_REG(0) - op1;

#if (HOST_CPU_IS_I80386==0)

	SET_FLAGS_OSZAPC_16(READ_VIRTUAL_16BIT_REG(0),op1,diff,BX_INSTR_CMP16)

#endif //#if (HOST_CPU_IS_I80386==0) 

#if (HOST_CPU_IS_I80386==1)

	Bit16u temp;
	temp = READ_VIRTUAL_16BIT_REG(0);
	Bit32u x86_lf_flags = BX_CPU_CLASS_PTR eflags.x86.eax;
	__asm
	{
		mov dx,op1
		cmp temp,dx
		lahf
		seto al
		mov x86_lf_flags,eax
	}

	BX_CPU_CLASS_PTR eflags.x86.eax = x86_lf_flags;
#endif //#if (HOST_CPU_IS_I80386==1) 

	if (diff == 0)
	{	// if accumulator == dest
		// ZF = 1
		BX_CPU_CLASS_PTR set_ZF(1);
		// dest <-- src
		op2 = READ_VIRTUAL_16BIT_REG(MODRMnnn(i));
		WRITE_VIRTUAL_16BIT_REG(MODRMrm(i), op2);
	}
	else
	{
		// ZF = 0
		BX_CPU_CLASS_PTR set_ZF(0);
		// accumulator <-- dest
		READ_VIRTUAL_16BIT_REG(0) = op1;
	}
#else
	BX_PANIC(("CMPXCHG_EGwGw:"));
#endif
}

	void
BX_CPU_C::CMPXCHG_EGdGd(BX_CPU_C *icpu,bxInstruction_c *i)
{
#if (BX_CPU_LEVEL >= 4) || (BX_CPU_LEVEL_HACKED >= 4)
	Bit32u op1, op2, diff;
	op1 = READ_VIRTUAL_32BIT_REG(MODRMrm(i));
	diff = READ_VIRTUAL_32BIT_REG(0) - op1;

#if (HOST_CPU_IS_I80386==0)

	SET_FLAGS_OSZAPC_32(READ_VIRTUAL_32BIT_REG(0),op1,diff,BX_INSTR_CMP32)

#endif //#if (HOST_CPU_IS_I80386==0) 

#if (HOST_CPU_IS_I80386==1)

	Bit32u temp;
	temp = READ_VIRTUAL_32BIT_REG(0);
	Bit32u x86_lf_flags = BX_CPU_CLASS_PTR eflags.x86.eax;
	__asm
	{
		mov edx,op1
		cmp temp,edx
		lahf
		seto al
		mov x86_lf_flags,eax
	}

	BX_CPU_CLASS_PTR eflags.x86.eax = x86_lf_flags;
#endif //#if (HOST_CPU_IS_I80386==1) 

	if (diff == 0)
	{	// if accumulator == dest
		// ZF = 1
		BX_CPU_CLASS_PTR set_ZF(1);
		// dest <-- src
		op2 = READ_VIRTUAL_32BIT_REG(MODRMnnn(i));
		WRITE_VIRTUAL_32BIT_REG(MODRMrm(i), op2);
	}
	else
	{
		// ZF = 0
		BX_CPU_CLASS_PTR set_ZF(0);
		// accumulator <-- dest
		READ_VIRTUAL_32BIT_REG(0) = op1;
	}
#else
	BX_PANIC(("CMPXCHG_EGdGd:"));
#endif
}

	void
BX_CPU_C::CMPXCHG_EEbGb(BX_CPU_C *icpu,bxInstruction_c *i)
{
#if (BX_CPU_LEVEL >= 4) || (BX_CPU_LEVEL_HACKED >= 4)
	Bit8u op1, op2, diff;
	READ_RMW_VIRTUAL_BYTE(MODRMSeg(i),RMAddr(i),&op1);
	diff = READ_VIRTUAL_8BIT_REG(0) - op1;

#if (HOST_CPU_IS_I80386==0)

	SET_FLAGS_OSZAPC_8(READ_VIRTUAL_8BIT_REG(0),op1,diff,BX_INSTR_CMP8)

#endif //#if (HOST_CPU_IS_I80386==0) 

#if (HOST_CPU_IS_I80386==1)

	Bit8u temp;
	temp = READ_VIRTUAL_8BIT_REG(0);
	Bit32u x86_lf_flags = BX_CPU_CLASS_PTR eflags.x86.eax;
	__asm
	{
		mov dl,op1
		cmp temp,dl
		lahf
		seto al
		mov x86_lf_flags,eax
	}

	BX_CPU_CLASS_PTR eflags.x86.eax = x86_lf_flags;
#endif //#if (HOST_CPU_IS_I80386==1) 

	if (diff == 0)
	{	// if accumulator == dest
		// ZF = 1
		BX_CPU_CLASS_PTR set_ZF(1);
		// dest <-- src
		op2 = READ_VIRTUAL_8BIT_REG(MODRMnnn(i));
		WRITE_RMW_VIRTUAL_BYTE(op2);
	}
	else
	{
		// ZF = 0
		BX_CPU_CLASS_PTR set_ZF(0);
		// accumulator <-- dest
		READ_VIRTUAL_8BIT_REG(0) = op1;
	}
#else
	BX_PANIC(("CMPXCHG_EEbGb:"));
#endif
}

	void
BX_CPU_C::CMPXCHG_EEwGw(BX_CPU_C *icpu,bxInstruction_c *i)
{
#if (BX_CPU_LEVEL >= 4) || (BX_CPU_LEVEL_HACKED >= 4)
	Bit16u op1, op2, diff;
	READ_RMW_VIRTUAL_WORD(MODRMSeg(i),RMAddr(i),&op1);
	diff = READ_VIRTUAL_16BIT_REG(0) - op1;

#if (HOST_CPU_IS_I80386==0)

	SET_FLAGS_OSZAPC_16(READ_VIRTUAL_16BIT_REG(0),op1,diff,BX_INSTR_CMP16)

#endif //#if (HOST_CPU_IS_I80386==0) 

#if (HOST_CPU_IS_I80386==1)

	Bit16u temp;
	temp = READ_VIRTUAL_16BIT_REG(0);
	Bit32u x86_lf_flags = BX_CPU_CLASS_PTR eflags.x86.eax;
	__asm
	{
		mov dx,op1
		cmp temp,dx
		lahf
		seto al
		mov x86_lf_flags,eax
	}

	BX_CPU_CLASS_PTR eflags.x86.eax = x86_lf_flags;
#endif //#if (HOST_CPU_IS_I80386==1) 

	if (diff == 0)
	{	// if accumulator == dest
		// ZF = 1
		BX_CPU_CLASS_PTR set_ZF(1);
		// dest <-- src
		op2 = READ_VIRTUAL_16BIT_REG(MODRMnnn(i));
		WRITE_RMW_VIRTUAL_WORD(op2);
	}
	else
	{
		// ZF = 0
		BX_CPU_CLASS_PTR set_ZF(0);
		// accumulator <-- dest
		READ_VIRTUAL_16BIT_REG(0) = op1;
	}
#else
	BX_PANIC(("CMPXCHG_EEwGw:"));
#endif
}

	void
BX_CPU_C::CMPXCHG_EEdGd(BX_CPU_C *icpu,bxInstruction_c *i)
{
#if (BX_CPU_LEVEL >= 4) || (BX_CPU_LEVEL_HACKED >= 4)
	Bit32u op1, op2, diff;
	READ_RMW_VIRTUAL_DWORD(MODRMSeg(i),RMAddr(i),&op1);
	diff = READ_VIRTUAL_32BIT_REG(0) - op1;

#if (HOST_CPU_IS_I80386==0)

	SET_FLAGS_OSZAPC_32(READ_VIRTUAL_32BIT_REG(0),op1,diff,BX_INSTR_CMP32)

#endif //#if (HOST_CPU_IS_I80386==0) 

#if (HOST_CPU_IS_I80386==1)

	Bit32u temp;
	temp = READ_VIRTUAL_32BIT_REG(0);
	Bit32u x86_lf_flags = BX_CPU_CLASS_PTR eflags.x86.eax;
	__asm
	{
		mov edx,op1
		cmp temp,edx
		lahf
		seto al
		mov x86_lf_flags,eax
	}

	BX_CPU_CLASS_PTR eflags.x86.eax = x86_lf_flags;
#endif //#if (HOST_CPU_IS_I80386==1) 

	if (diff == 0)
	{	// if accumulator == dest
		// ZF = 1
		BX_CPU_CLASS_PTR set_ZF(1);
		// dest <-- src
		op2 = READ_VIRTUAL_32BIT_REG(MODRMnnn(i));
		WRITE_RMW_VIRTUAL_DWORD(op2);
	}
	else
	{
		// ZF = 0
		BX_CPU_CLASS_PTR set_ZF(0);
		// accumulator <-- dest
		READ_VIRTUAL_32BIT_REG(0) = op1;
	}
#else
	BX_PANIC(("CMPXCHG_EEdGd:"));
#endif
}

	void
BX_CPU_C::MOV_EGbGb(BX_CPU_C *icpu,bxInstruction_c *i)
{
	Bit8u sum;

	sum = READ_VIRTUAL_8BIT_REG(MODRMnnn(i));
	WRITE_VIRTUAL_8BIT_REG(MODRMrm(i), sum);
}

	void
BX_CPU_C::MOV_EGwGw(BX_CPU_C *icpu,bxInstruction_c *i)
{
	Bit16u sum;

	sum = READ_VIRTUAL_16BIT_REG(MODRMnnn(i));
	WRITE_VIRTUAL_16BIT_REG(MODRMrm(i), sum);
}

	void
BX_CPU_C::MOV_EGdGd(BX_CPU_C *icpu,bxInstruction_c *i)
{
	Bit32u sum;

	sum = READ_VIRTUAL_32BIT_REG(MODRMnnn(i));
	WRITE_VIRTUAL_32BIT_REG(MODRMrm(i), sum);
}

	void
BX_CPU_C::MOV_EGbIb(BX_CPU_C *icpu,bxInstruction_c *i)
{
	Bit8u sum;

	if (MODRMnnn(i)!=0)
	{
		BX_PANIC(("MOV_EGbIb: incomplete MODRMnnn(i) !=0"));
		UndefinedOpcode(icpu,i);
	}
	sum = IMMEDIATEIb(i);
	WRITE_VIRTUAL_8BIT_REG(MODRMrm(i),sum);
}

	void
BX_CPU_C::MOV_EGwIw(BX_CPU_C *icpu,bxInstruction_c *i)
{
	Bit16u sum;

	if (MODRMnnn(i)!=0)
	{
		BX_PANIC(("MOV_EGwIw: incomplete MODRMnnn(i) !=0"));
		UndefinedOpcode(icpu,i);
	}
	sum = IMMEDIATEIw(i);
	WRITE_VIRTUAL_16BIT_REG(MODRMrm(i),sum);
}

	void
BX_CPU_C::MOV_EGdId(BX_CPU_C *icpu,bxInstruction_c *i)
{
	Bit32u sum;

	if (MODRMnnn(i)!=0)
	{
		BX_PANIC(("MOV_EGdId: incomplete MODRMnnn(i) !=0"));
		UndefinedOpcode(icpu,i);
	}
	sum = IMMEDIATEId(i);
	WRITE_VIRTUAL_32BIT_REG(MODRMrm(i),sum);
}

	void
BX_CPU_C::MOV_GbEGb(BX_CPU_C *icpu,bxInstruction_c *i)
{
	Bit8u sum;

	sum = READ_VIRTUAL_8BIT_REG(MODRMrm(i));
	WRITE_VIRTUAL_8BIT_REG(MODRMnnn(i),sum);
}

	void
BX_CPU_C::MOV_GwEGw(BX_CPU_C *icpu,bxInstruction_c *i)
{
	Bit16u sum;

	sum = READ_VIRTUAL_16BIT_REG(MODRMrm(i));
	WRITE_VIRTUAL_16BIT_REG(MODRMnnn(i),sum);
}

	void
BX_CPU_C::MOV_GdEGd(BX_CPU_C *icpu,bxInstruction_c *i)
{
	Bit32u sum;

	sum = READ_VIRTUAL_32BIT_REG(MODRMrm(i));
	WRITE_VIRTUAL_32BIT_REG(MODRMnnn(i),sum);
}

	void
BX_CPU_C::MOV_EEbGb(BX_CPU_C *icpu,bxInstruction_c *i)
{
	Bit8u sum;

	sum = READ_VIRTUAL_8BIT_REG(MODRMnnn(i));
	WRITE_VIRTUAL_BYTE(MODRMSeg(i),RMAddr(i),&sum);
}

	void
BX_CPU_C::MOV_EEwGw(BX_CPU_C *icpu,bxInstruction_c *i)
{
	Bit16u sum;

	sum = READ_VIRTUAL_16BIT_REG(MODRMnnn(i));
	WRITE_VIRTUAL_WORD(MODRMSeg(i),RMAddr(i),&sum);
}

	void
BX_CPU_C::MOV_EEdGd(BX_CPU_C *icpu,bxInstruction_c *i)
{
	Bit32u sum;

	sum = READ_VIRTUAL_32BIT_REG(MODRMnnn(i));
	WRITE_VIRTUAL_DWORD(MODRMSeg(i),RMAddr(i),&sum);
}

	void
BX_CPU_C::MOV_EEbIb(BX_CPU_C *icpu,bxInstruction_c *i)
{
	Bit8u sum;

	if (MODRMnnn(i)!=0)
	{
		BX_PANIC(("MOV_EEbIb: incomplete MODRMnnn(i) !=0"));
		UndefinedOpcode(icpu,i);
	}
	sum = IMMEDIATEIb(i);
	WRITE_VIRTUAL_BYTE(MODRMSeg(i),RMAddr(i),&sum);
}

	void
BX_CPU_C::MOV_EEwIw(BX_CPU_C *icpu,bxInstruction_c *i)
{
	Bit16u sum;

	if (MODRMnnn(i)!=0)
	{
		BX_PANIC(("MOV_EEwIw: incomplete MODRMnnn(i) !=0"));
		UndefinedOpcode(icpu,i);
	}
	sum = IMMEDIATEIw(i);
	WRITE_VIRTUAL_WORD(MODRMSeg(i),RMAddr(i),&sum);
}

	void
BX_CPU_C::MOV_EEdId(BX_CPU_C *icpu,bxInstruction_c *i)
{
	Bit32u sum;

	if (MODRMnnn(i)!=0)
	{
		BX_PANIC(("MOV_EEdId: incomplete MODRMnnn(i) !=0"));
		UndefinedOpcode(icpu,i);
	}
	sum = IMMEDIATEId(i);
	WRITE_VIRTUAL_DWORD(MODRMSeg(i),RMAddr(i),&sum);
}

	void
BX_CPU_C::MOV_GbEEb(BX_CPU_C *icpu,bxInstruction_c *i)
{
	Bit8u sum;

	READ_VIRTUAL_BYTE(MODRMSeg(i),RMAddr(i),&sum);
	WRITE_VIRTUAL_8BIT_REG(MODRMnnn(i),sum);
}

	void
BX_CPU_C::MOV_GwEEw(BX_CPU_C *icpu,bxInstruction_c *i)
{
	Bit16u sum;

	READ_VIRTUAL_WORD(MODRMSeg(i),RMAddr(i),&sum);
	WRITE_VIRTUAL_16BIT_REG(MODRMnnn(i),sum);
}

	void
BX_CPU_C::MOV_GdEEd(BX_CPU_C *icpu,bxInstruction_c *i)
{
	Bit32u sum;

	READ_VIRTUAL_DWORD(MODRMSeg(i),RMAddr(i),&sum);
	WRITE_VIRTUAL_32BIT_REG(MODRMnnn(i),sum);
}

	void
BX_CPU_C::MOVZX_GwEGb(BX_CPU_C *icpu,bxInstruction_c *i)
{
	Bit8u sum;

#if BX_CPU_LEVEL < 3
	BX_PANIC(("MOVZX_GwEGb: not supported on < 386"));
#else
	sum = READ_VIRTUAL_8BIT_REG(MODRMrm(i));
	WRITE_VIRTUAL_16BIT_REG(MODRMnnn(i),(Bit16u)sum);
#endif
}

	void
BX_CPU_C::MOVSX_GwEGb(BX_CPU_C *icpu,bxInstruction_c *i)
{
	Bit8u sum;

#if BX_CPU_LEVEL < 3
	BX_PANIC(("MOVSX_GwEGb: not supported on < 386"));
#else
	sum = READ_VIRTUAL_8BIT_REG(MODRMrm(i));
	WRITE_VIRTUAL_16BIT_REG(MODRMnnn(i),(Bit8s)sum);
#endif
}

	void
BX_CPU_C::MOVZX_GwEGw(BX_CPU_C *icpu,bxInstruction_c *i)
{
	Bit16u sum;

#if BX_CPU_LEVEL < 3
	BX_PANIC(("MOVZX_GwEGw: not supported on < 386"));
#else
	sum = READ_VIRTUAL_16BIT_REG(MODRMrm(i));
	WRITE_VIRTUAL_16BIT_REG(MODRMnnn(i),(Bit16u)sum);
#endif
}

	void
BX_CPU_C::MOVSX_GwEGw(BX_CPU_C *icpu,bxInstruction_c *i)
{
	Bit16u sum;

#if BX_CPU_LEVEL < 3
	BX_PANIC(("MOVSX_GwEGw: not supported on < 386"));
#else
	sum = READ_VIRTUAL_16BIT_REG(MODRMrm(i));
	WRITE_VIRTUAL_16BIT_REG(MODRMnnn(i),(Bit16s)sum);
#endif
}

	void
BX_CPU_C::MOVZX_GdEGb(BX_CPU_C *icpu,bxInstruction_c *i)
{
	Bit8u sum;

#if BX_CPU_LEVEL < 3
	BX_PANIC(("MOVZX_GdEGb: not supported on < 386"));
#else
	sum = READ_VIRTUAL_8BIT_REG(MODRMrm(i));
	WRITE_VIRTUAL_32BIT_REG(MODRMnnn(i),(Bit32u)sum);
#endif
}

	void
BX_CPU_C::MOVSX_GdEGb(BX_CPU_C *icpu,bxInstruction_c *i)
{
	Bit8u sum;

#if BX_CPU_LEVEL < 3
	BX_PANIC(("MOVSX_GdEGb: not supported on < 386"));
#else
	sum = READ_VIRTUAL_8BIT_REG(MODRMrm(i));
	WRITE_VIRTUAL_32BIT_REG(MODRMnnn(i),(Bit8s)sum);
#endif
}

	void
BX_CPU_C::MOVZX_GdEGw(BX_CPU_C *icpu,bxInstruction_c *i)
{
	Bit16u sum;

#if BX_CPU_LEVEL < 3
	BX_PANIC(("MOVZX_GdEGw: not supported on < 386"));
#else
	sum = READ_VIRTUAL_16BIT_REG(MODRMrm(i));
	WRITE_VIRTUAL_32BIT_REG(MODRMnnn(i),(Bit32u)sum);
#endif
}

	void
BX_CPU_C::MOVSX_GdEGw(BX_CPU_C *icpu,bxInstruction_c *i)
{
	Bit16u sum;

#if BX_CPU_LEVEL < 3
	BX_PANIC(("MOVSX_GdEGw: not supported on < 386"));
#else
	sum = READ_VIRTUAL_16BIT_REG(MODRMrm(i));
	WRITE_VIRTUAL_32BIT_REG(MODRMnnn(i),(Bit16s)sum);
#endif
}

	void
BX_CPU_C::MOVZX_GwEEb(BX_CPU_C *icpu,bxInstruction_c *i)
{
	Bit8u sum;

#if BX_CPU_LEVEL < 3
	BX_PANIC(("MOVZX_GwEEb: not supported on < 386"));
#else
	READ_VIRTUAL_BYTE(MODRMSeg(i),RMAddr(i),&sum);
	WRITE_VIRTUAL_16BIT_REG(MODRMnnn(i),(Bit16u)sum);
#endif
}

	void
BX_CPU_C::MOVSX_GwEEb(BX_CPU_C *icpu,bxInstruction_c *i)
{
	Bit8u sum;

#if BX_CPU_LEVEL < 3
	BX_PANIC(("MOVSX_GwEEb: not supported on < 386"));
#else
	READ_VIRTUAL_BYTE(MODRMSeg(i),RMAddr(i),&sum);
	WRITE_VIRTUAL_16BIT_REG(MODRMnnn(i),(Bit8s)sum);
#endif
}

	void
BX_CPU_C::MOVZX_GwEEw(BX_CPU_C *icpu,bxInstruction_c *i)
{
	Bit16u sum;

#if BX_CPU_LEVEL < 3
	BX_PANIC(("MOVZX_GwEEw: not supported on < 386"));
#else
	READ_VIRTUAL_WORD(MODRMSeg(i),RMAddr(i),&sum);
	WRITE_VIRTUAL_16BIT_REG(MODRMnnn(i),(Bit16u)sum);
#endif
}

	void
BX_CPU_C::MOVSX_GwEEw(BX_CPU_C *icpu,bxInstruction_c *i)
{
	Bit16u sum;

#if BX_CPU_LEVEL < 3
	BX_PANIC(("MOVSX_GwEEw: not supported on < 386"));
#else
	READ_VIRTUAL_WORD(MODRMSeg(i),RMAddr(i),&sum);
	WRITE_VIRTUAL_16BIT_REG(MODRMnnn(i),(Bit16s)sum);
#endif
}

	void
BX_CPU_C::MOVZX_GdEEb(BX_CPU_C *icpu,bxInstruction_c *i)
{
	Bit8u sum;

#if BX_CPU_LEVEL < 3
	BX_PANIC(("MOVZX_GdEEb: not supported on < 386"));
#else
	READ_VIRTUAL_BYTE(MODRMSeg(i),RMAddr(i),&sum);
	WRITE_VIRTUAL_32BIT_REG(MODRMnnn(i),(Bit32u)sum);
#endif
}

	void
BX_CPU_C::MOVSX_GdEEb(BX_CPU_C *icpu,bxInstruction_c *i)
{
	Bit8u sum;

#if BX_CPU_LEVEL < 3
	BX_PANIC(("MOVSX_GdEEb: not supported on < 386"));
#else
	READ_VIRTUAL_BYTE(MODRMSeg(i),RMAddr(i),&sum);
	WRITE_VIRTUAL_32BIT_REG(MODRMnnn(i),(Bit8s)sum);
#endif
}

	void
BX_CPU_C::MOVZX_GdEEw(BX_CPU_C *icpu,bxInstruction_c *i)
{
	Bit16u sum;

#if BX_CPU_LEVEL < 3
	BX_PANIC(("MOVZX_GdEEw: not supported on < 386"));
#else
	READ_VIRTUAL_WORD(MODRMSeg(i),RMAddr(i),&sum);
	WRITE_VIRTUAL_32BIT_REG(MODRMnnn(i),(Bit32u)sum);
#endif
}

	void
BX_CPU_C::MOVSX_GdEEw(BX_CPU_C *icpu,bxInstruction_c *i)
{
	Bit16u sum;

#if BX_CPU_LEVEL < 3
	BX_PANIC(("MOVSX_GdEEw: not supported on < 386"));
#else
	READ_VIRTUAL_WORD(MODRMSeg(i),RMAddr(i),&sum);
	WRITE_VIRTUAL_32BIT_REG(MODRMnnn(i),(Bit16s)sum);
#endif
}

	void
BX_CPU_C::LEA_GwM(BX_CPU_C *icpu,bxInstruction_c *i)
{

	if (i->modC0())
	{
		BX_PANIC(("LEA_GvM: op2 is a register"));
		UndefinedOpcode(icpu,i);
		return;
	}
	WRITE_VIRTUAL_16BIT_REG(MODRMnnn(i),(Bit16u)RMAddr(i));
}

	void
BX_CPU_C::LEA_GdM(BX_CPU_C *icpu,bxInstruction_c *i)
{

	if (i->modC0())
	{
		BX_PANIC(("LEA_GvM: op2 is a register"));
		UndefinedOpcode(icpu,i);
		return;
	}
	WRITE_VIRTUAL_32BIT_REG(MODRMnnn(i),(Bit32u)RMAddr(i));
}

	void
BX_CPU_C::MOV_ALOb(BX_CPU_C *icpu,bxInstruction_c *i)
{
	Bit8u sum;

	RMAddr(i) = IMMEDIATEId(i);
	READ_VIRTUAL_BYTE(MODRMSeg(i),RMAddr(i),&sum);
	WRITE_VIRTUAL_8BIT_REG(0,sum);
}

	void
BX_CPU_C::MOV_ObAL(BX_CPU_C *icpu,bxInstruction_c *i)
{
	Bit8u sum;

	RMAddr(i) = IMMEDIATEId(i);
	sum = READ_VIRTUAL_8BIT_REG(0);
	WRITE_VIRTUAL_BYTE(MODRMSeg(i),RMAddr(i),&sum);
}

	void
BX_CPU_C::MOV_AXOw(BX_CPU_C *icpu,bxInstruction_c *i)
{
	Bit16u sum;

	RMAddr(i) = IMMEDIATEId(i);
	READ_VIRTUAL_WORD(MODRMSeg(i),RMAddr(i),&sum);
	WRITE_VIRTUAL_16BIT_REG(0,sum);
}

	void
BX_CPU_C::MOV_OwAX(BX_CPU_C *icpu,bxInstruction_c *i)
{
	Bit16u sum;

	RMAddr(i) = IMMEDIATEId(i);
	sum = READ_VIRTUAL_16BIT_REG(0);
	WRITE_VIRTUAL_WORD(MODRMSeg(i),RMAddr(i),&sum);
}

	void
BX_CPU_C::MOV_EAXOd(BX_CPU_C *icpu,bxInstruction_c *i)
{
	Bit32u sum;

	RMAddr(i) = IMMEDIATEId(i);
	READ_VIRTUAL_DWORD(MODRMSeg(i),RMAddr(i),&sum);
	WRITE_VIRTUAL_32BIT_REG(0,sum);
}

	void
BX_CPU_C::MOV_OdEAX(BX_CPU_C *icpu,bxInstruction_c *i)
{
	Bit32u sum;

	RMAddr(i) = IMMEDIATEId(i);
	sum = READ_VIRTUAL_32BIT_REG(0);
	WRITE_VIRTUAL_DWORD(MODRMSeg(i),RMAddr(i),&sum);
}

	void
BX_CPU_C::MOV_RLIb(BX_CPU_C *icpu,bxInstruction_c *i)
{
	Bit8u sum;

	sum = IMMEDIATEIb(i);
	BX_CPU_CLASS_PTR program_visible_gen_reg[(OPCODEb1(i)&0x3)].word.byte.rl = sum;
}

	void
BX_CPU_C::MOV_RHIb(BX_CPU_C *icpu,bxInstruction_c *i)
{
	Bit8u sum;

	sum = IMMEDIATEIb(i);
	BX_CPU_CLASS_PTR program_visible_gen_reg[(OPCODEb1(i)&0x3)].word.byte.rh = sum;
}

	void
BX_CPU_C::MOV_RXIw(BX_CPU_C *icpu,bxInstruction_c *i)
{
	Bit16u sum;

	sum = IMMEDIATEIw(i);
	WRITE_VIRTUAL_16BIT_REG((OPCODEb1(i)&0x7),sum);
}

	void
BX_CPU_C::MOV_ERXId(BX_CPU_C *icpu,bxInstruction_c *i)
{
	Bit32u sum;

	sum = IMMEDIATEId(i);
	WRITE_VIRTUAL_32BIT_REG((OPCODEb1(i)&0x7),sum);
}

	void
BX_CPU_C::XCHG_EGbGb(BX_CPU_C *icpu,bxInstruction_c *i)
{
	Bit8u op1,op2;

	op2 = READ_VIRTUAL_8BIT_REG(MODRMnnn(i));
	op1 = READ_VIRTUAL_8BIT_REG(MODRMrm(i));
	WRITE_VIRTUAL_8BIT_REG(MODRMrm(i), op2);
	WRITE_VIRTUAL_8BIT_REG(MODRMnnn(i), op1);
}

	void
BX_CPU_C::XCHG_EGwGw(BX_CPU_C *icpu,bxInstruction_c *i)
{
	Bit16u op1,op2;

	op2 = READ_VIRTUAL_16BIT_REG(MODRMnnn(i));
	op1 = READ_VIRTUAL_16BIT_REG(MODRMrm(i));
	WRITE_VIRTUAL_16BIT_REG(MODRMrm(i), op2);
	WRITE_VIRTUAL_16BIT_REG(MODRMnnn(i), op1);
}

	void
BX_CPU_C::XCHG_EGdGd(BX_CPU_C *icpu,bxInstruction_c *i)
{
	Bit32u op1,op2;

	op2 = READ_VIRTUAL_32BIT_REG(MODRMnnn(i));
	op1 = READ_VIRTUAL_32BIT_REG(MODRMrm(i));
	WRITE_VIRTUAL_32BIT_REG(MODRMrm(i), op2);
	WRITE_VIRTUAL_32BIT_REG(MODRMnnn(i), op1);
}

	void
BX_CPU_C::XCHG_RXAX(BX_CPU_C *icpu,bxInstruction_c *i)
{
	Bit16u op1,op2;

	op2 = READ_VIRTUAL_16BIT_REG(0);
	op1 = READ_VIRTUAL_16BIT_REG((OPCODEb1(i) & 0x07));
	WRITE_VIRTUAL_16BIT_REG(0, op1);
	WRITE_VIRTUAL_16BIT_REG((OPCODEb1(i) & 0x07), op2);
}

	void
BX_CPU_C::XCHG_ERXEAX(BX_CPU_C *icpu,bxInstruction_c *i)
{
	Bit32u op1,op2;

	op2 = READ_VIRTUAL_32BIT_REG(0);
	op1 = READ_VIRTUAL_32BIT_REG((OPCODEb1(i) & 0x07));
	WRITE_VIRTUAL_32BIT_REG(0, op1);
	WRITE_VIRTUAL_32BIT_REG((OPCODEb1(i) & 0x07), op2);
}

	void
BX_CPU_C::XCHG_EEbGb(BX_CPU_C *icpu,bxInstruction_c *i)
{
	Bit8u op1,op2;

	op2 = READ_VIRTUAL_8BIT_REG(MODRMnnn(i));
	READ_RMW_VIRTUAL_BYTE(MODRMSeg(i), RMAddr(i), &op1);
	WRITE_RMW_VIRTUAL_BYTE(op2);
	WRITE_VIRTUAL_8BIT_REG(MODRMnnn(i), op1);
}

	void
BX_CPU_C::XCHG_EEwGw(BX_CPU_C *icpu,bxInstruction_c *i)
{
	Bit16u op1,op2;

	op2 = READ_VIRTUAL_16BIT_REG(MODRMnnn(i));
	READ_RMW_VIRTUAL_WORD(MODRMSeg(i), RMAddr(i), &op1);
	WRITE_RMW_VIRTUAL_WORD(op2);
	WRITE_VIRTUAL_16BIT_REG(MODRMnnn(i), op1);
}

	void
BX_CPU_C::XCHG_EEdGd(BX_CPU_C *icpu,bxInstruction_c *i)
{
	Bit32u op1,op2;

	op2 = READ_VIRTUAL_32BIT_REG(MODRMnnn(i));
	READ_RMW_VIRTUAL_DWORD(MODRMSeg(i), RMAddr(i), &op1);
	WRITE_RMW_VIRTUAL_DWORD(op2);
	WRITE_VIRTUAL_32BIT_REG(MODRMnnn(i), op1);
}

