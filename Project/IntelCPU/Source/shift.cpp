/////////////////////////////////////////////////////////////////////////
// $Id: shift.cc,v 1.0 2002/10/10 04:57:05 bdenney Exp $
/////////////////////////////////////////////////////////////////////////


#include "stdafx.h"
#include "x86cpu.h"
//---------------------------------------------------------
//虚拟执行--指令微函数  移位指令
//---------------------------------------------------------


// shift dst(r/m), src(i8/1/cl)
// src <-- i8	| b1: 0xc0/0xc1
// src <-- 1    | b1: 0xd0/0xd1
// src <-- cl   | b1: 0xd2/0xd3
// shift double dst(r/m),src(r),  src(i8/cl)
// src <-- i8	| b1: 0x1a4
// src <-- cl   | b1: 0x1a5


	void
BX_CPU_C::ROL_EGb(BX_CPU_C *icpu,bxInstruction_c *i)
{
	Bit8u count;
	count = IMMEDIATEIb(i)&0x1f;
	IMMEDIATEIb(i) = count;
	i->Word.shift = BxOpcodeShiftTableG_RO__Eb[count].count;
	i->execute = BxOpcodeShiftTableG_RO__Eb[count].shift_fun->shiftL_EG;
	//call method on BX_CPU_C object
	BX_CPU_CALL_METHOD(i->execute, (icpu,i));
}

	void
BX_CPU_C::ROL_EGw(BX_CPU_C *icpu,bxInstruction_c *i)
{
	Bit8u count;
	count = IMMEDIATEIb(i)&0x1f;
	IMMEDIATEIb(i) = count;
	i->Word.shift = BxOpcodeShiftTableG_RO__Ew[count].count;
	i->execute = BxOpcodeShiftTableG_RO__Ew[count].shift_fun->shiftL_EG;
	//call method on BX_CPU_C object
	BX_CPU_CALL_METHOD(i->execute, (icpu,i));
}

	void
BX_CPU_C::ROL_EGd(BX_CPU_C *icpu,bxInstruction_c *i)
{
	Bit8u count;
	count = IMMEDIATEIb(i)&0x1f;
	IMMEDIATEIb(i) = count;
	i->Word.shift = BxOpcodeShiftTableG_RO__Ed[count].count;
	i->execute = BxOpcodeShiftTableG_RO__Ed[count].shift_fun->shiftL_EG;
	//call method on BX_CPU_C object
	BX_CPU_CALL_METHOD(i->execute, (icpu,i));
}

	void
BX_CPU_C::ROR_EGb(BX_CPU_C *icpu,bxInstruction_c *i)
{
	Bit8u count;
	count = IMMEDIATEIb(i)&0x1f;
	IMMEDIATEIb(i) = count;
	i->Word.shift = BxOpcodeShiftTableG_RO__Eb[count].count;
	i->execute = BxOpcodeShiftTableG_RO__Eb[count].shift_fun->shiftR_EG;
	//call method on BX_CPU_C object
	BX_CPU_CALL_METHOD(i->execute, (icpu,i));
}

	void
BX_CPU_C::ROR_EGw(BX_CPU_C *icpu,bxInstruction_c *i)
{
	Bit8u count;
	count = IMMEDIATEIb(i)&0x1f;
	IMMEDIATEIb(i) = count;
	i->Word.shift = BxOpcodeShiftTableG_RO__Ew[count].count;
	i->execute = BxOpcodeShiftTableG_RO__Ew[count].shift_fun->shiftR_EG;
	//call method on BX_CPU_C object
	BX_CPU_CALL_METHOD(i->execute, (icpu,i));
}

	void
BX_CPU_C::ROR_EGd(BX_CPU_C *icpu,bxInstruction_c *i)
{
	Bit8u count;
	count = IMMEDIATEIb(i)&0x1f;
	IMMEDIATEIb(i) = count;
	i->Word.shift = BxOpcodeShiftTableG_RO__Ed[count].count;
	i->execute = BxOpcodeShiftTableG_RO__Ed[count].shift_fun->shiftR_EG;
	//call method on BX_CPU_C object
	BX_CPU_CALL_METHOD(i->execute, (icpu,i));
}

	void
BX_CPU_C::RCL_EGb(BX_CPU_C *icpu,bxInstruction_c *i)
{
	Bit8u count;
	count = IMMEDIATEIb(i)&0x1f;
	IMMEDIATEIb(i) = count;
	i->Word.shift = BxOpcodeShiftTableG_RC__Eb[count].count;
	i->execute = BxOpcodeShiftTableG_RC__Eb[count].shift_fun->shiftL_EG;
	//call method on BX_CPU_C object
	BX_CPU_CALL_METHOD(i->execute, (icpu,i));
}

	void
BX_CPU_C::RCL_EGw(BX_CPU_C *icpu,bxInstruction_c *i)
{
	Bit8u count;
	count = IMMEDIATEIb(i)&0x1f;
	IMMEDIATEIb(i) = count;
	i->Word.shift = BxOpcodeShiftTableG_RC__Ew[count].count;
	i->execute = BxOpcodeShiftTableG_RC__Ew[count].shift_fun->shiftL_EG;
	//call method on BX_CPU_C object
	BX_CPU_CALL_METHOD(i->execute, (icpu,i));
}

	void
BX_CPU_C::RCL_EGd(BX_CPU_C *icpu,bxInstruction_c *i)
{
	Bit8u count;
	count = IMMEDIATEIb(i)&0x1f;
	IMMEDIATEIb(i) = count;
	i->Word.shift = BxOpcodeShiftTableG_RC__Ed[count].count;
	i->execute = BxOpcodeShiftTableG_RC__Ed[count].shift_fun->shiftL_EG;
	//call method on BX_CPU_C object
	BX_CPU_CALL_METHOD(i->execute, (icpu,i));
}

	void
BX_CPU_C::RCR_EGb(BX_CPU_C *icpu,bxInstruction_c *i)
{
	Bit8u count;
	count = IMMEDIATEIb(i)&0x1f;
	IMMEDIATEIb(i) = count;
	i->Word.shift = BxOpcodeShiftTableG_RC__Eb[count].count;
	i->execute = BxOpcodeShiftTableG_RC__Eb[count].shift_fun->shiftR_EG;
	//call method on BX_CPU_C object
	BX_CPU_CALL_METHOD(i->execute, (icpu,i));
}

	void
BX_CPU_C::RCR_EGw(BX_CPU_C *icpu,bxInstruction_c *i)
{
	Bit8u count;
	count = IMMEDIATEIb(i)&0x1f;
	IMMEDIATEIb(i) = count;
	i->Word.shift = BxOpcodeShiftTableG_RC__Ew[count].count;
	i->execute = BxOpcodeShiftTableG_RC__Ew[count].shift_fun->shiftR_EG;
	//call method on BX_CPU_C object
	BX_CPU_CALL_METHOD(i->execute, (icpu,i));
}

	void
BX_CPU_C::RCR_EGd(BX_CPU_C *icpu,bxInstruction_c *i)
{
	Bit8u count;
	count = IMMEDIATEIb(i)&0x1f;
	IMMEDIATEIb(i) = count;
	i->Word.shift = BxOpcodeShiftTableG_RC__Ed[count].count;
	i->execute = BxOpcodeShiftTableG_RC__Ed[count].shift_fun->shiftR_EG;
	//call method on BX_CPU_C object
	BX_CPU_CALL_METHOD(i->execute, (icpu,i));
}

	void
BX_CPU_C::SHL_EGb(BX_CPU_C *icpu,bxInstruction_c *i)
{
	Bit8u count;
	count = IMMEDIATEIb(i)&0x1f;
	IMMEDIATEIb(i) = count;
	i->Word.shift = BxOpcodeShiftTableG_SH__Eb[count].count;
	i->execute = BxOpcodeShiftTableG_SH__Eb[count].shift_fun->shiftL_EG;
	//call method on BX_CPU_C object
	BX_CPU_CALL_METHOD(i->execute, (icpu,i));
}

	void
BX_CPU_C::SHL_EGw(BX_CPU_C *icpu,bxInstruction_c *i)
{
	Bit8u count;
	count = IMMEDIATEIb(i)&0x1f;
	IMMEDIATEIb(i) = count;
	i->Word.shift = BxOpcodeShiftTableG_SH__Ew[count].count;
	i->execute = BxOpcodeShiftTableG_SH__Ew[count].shift_fun->shiftL_EG;
	//call method on BX_CPU_C object
	BX_CPU_CALL_METHOD(i->execute, (icpu,i));
}

	void
BX_CPU_C::SHL_EGd(BX_CPU_C *icpu,bxInstruction_c *i)
{
	Bit8u count;
	count = IMMEDIATEIb(i)&0x1f;
	IMMEDIATEIb(i) = count;
	i->Word.shift = BxOpcodeShiftTableG_SH__Ed[count].count;
	i->execute = BxOpcodeShiftTableG_SH__Ed[count].shift_fun->shiftL_EG;
	//call method on BX_CPU_C object
	BX_CPU_CALL_METHOD(i->execute, (icpu,i));
}

	void
BX_CPU_C::SHR_EGb(BX_CPU_C *icpu,bxInstruction_c *i)
{
	Bit8u count;
	count = IMMEDIATEIb(i)&0x1f;
	IMMEDIATEIb(i) = count;
	i->Word.shift = BxOpcodeShiftTableG_SH__Eb[count].count;
	i->execute = BxOpcodeShiftTableG_SH__Eb[count].shift_fun->shiftR_EG;
	//call method on BX_CPU_C object
	BX_CPU_CALL_METHOD(i->execute, (icpu,i));
}

	void
BX_CPU_C::SHR_EGw(BX_CPU_C *icpu,bxInstruction_c *i)
{
	Bit8u count;
	count = IMMEDIATEIb(i)&0x1f;
	IMMEDIATEIb(i) = count;
	i->Word.shift = BxOpcodeShiftTableG_SH__Ew[count].count;
	i->execute = BxOpcodeShiftTableG_SH__Ew[count].shift_fun->shiftR_EG;
	//call method on BX_CPU_C object
	BX_CPU_CALL_METHOD(i->execute, (icpu,i));
}

	void
BX_CPU_C::SHR_EGd(BX_CPU_C *icpu,bxInstruction_c *i)
{
	Bit8u count;
	count = IMMEDIATEIb(i)&0x1f;
	IMMEDIATEIb(i) = count;
	i->Word.shift = BxOpcodeShiftTableG_SH__Ed[count].count;
	i->execute = BxOpcodeShiftTableG_SH__Ed[count].shift_fun->shiftR_EG;
	//call method on BX_CPU_C object
	BX_CPU_CALL_METHOD(i->execute, (icpu,i));
}

	void
BX_CPU_C::SAR_EGb(BX_CPU_C *icpu,bxInstruction_c *i)
{
	Bit8u count;
	count = IMMEDIATEIb(i)&0x1f;
	IMMEDIATEIb(i) = count;
	i->Word.shift = BxOpcodeShiftTableG_SA__Eb[count].count;
	i->execute = BxOpcodeShiftTableG_SA__Eb[count].shift_fun->shiftR_EG;
	//call method on BX_CPU_C object
	BX_CPU_CALL_METHOD(i->execute, (icpu,i));
}

	void
BX_CPU_C::SAR_EGw(BX_CPU_C *icpu,bxInstruction_c *i)
{
	Bit8u count;
	count = IMMEDIATEIb(i)&0x1f;
	IMMEDIATEIb(i) = count;
	i->Word.shift = BxOpcodeShiftTableG_SA__Ew[count].count;
	i->execute = BxOpcodeShiftTableG_SA__Ew[count].shift_fun->shiftR_EG;
	//call method on BX_CPU_C object
	BX_CPU_CALL_METHOD(i->execute, (icpu,i));
}

	void
BX_CPU_C::SAR_EGd(BX_CPU_C *icpu,bxInstruction_c *i)
{
	Bit8u count;
	count = IMMEDIATEIb(i)&0x1f;
	IMMEDIATEIb(i) = count;
	i->Word.shift = BxOpcodeShiftTableG_SA__Ed[count].count;
	i->execute = BxOpcodeShiftTableG_SA__Ed[count].shift_fun->shiftR_EG;
	//call method on BX_CPU_C object
	BX_CPU_CALL_METHOD(i->execute, (icpu,i));
}

	void
BX_CPU_C::ROL_EEb(BX_CPU_C *icpu,bxInstruction_c *i)
{
	Bit8u count;
	count = IMMEDIATEIb(i)&0x1f;
	IMMEDIATEIb(i) = count;
	i->Word.shift = BxOpcodeShiftTableG_RO__Eb[count].count;
	i->execute = BxOpcodeShiftTableG_RO__Eb[count].shift_fun->shiftL_EE;
	//call method on BX_CPU_C object
	BX_CPU_CALL_METHOD(i->execute, (icpu,i));
}

	void
BX_CPU_C::ROL_EEw(BX_CPU_C *icpu,bxInstruction_c *i)
{
	Bit8u count;
	count = IMMEDIATEIb(i)&0x1f;
	IMMEDIATEIb(i) = count;
	i->Word.shift = BxOpcodeShiftTableG_RO__Ew[count].count;
	i->execute = BxOpcodeShiftTableG_RO__Ew[count].shift_fun->shiftL_EE;
	//call method on BX_CPU_C object
	BX_CPU_CALL_METHOD(i->execute, (icpu,i));
}

	void
BX_CPU_C::ROL_EEd(BX_CPU_C *icpu,bxInstruction_c *i)
{
	Bit8u count;
	count = IMMEDIATEIb(i)&0x1f;
	IMMEDIATEIb(i) = count;
	i->Word.shift = BxOpcodeShiftTableG_RO__Ed[count].count;
	i->execute = BxOpcodeShiftTableG_RO__Ed[count].shift_fun->shiftL_EE;
	//call method on BX_CPU_C object
	BX_CPU_CALL_METHOD(i->execute, (icpu,i));
}

	void
BX_CPU_C::ROR_EEb(BX_CPU_C *icpu,bxInstruction_c *i)
{
	Bit8u count;
	count = IMMEDIATEIb(i)&0x1f;
	IMMEDIATEIb(i) = count;
	i->Word.shift = BxOpcodeShiftTableG_RO__Eb[count].count;
	i->execute = BxOpcodeShiftTableG_RO__Eb[count].shift_fun->shiftR_EE;
	//call method on BX_CPU_C object
	BX_CPU_CALL_METHOD(i->execute, (icpu,i));
}

	void
BX_CPU_C::ROR_EEw(BX_CPU_C *icpu,bxInstruction_c *i)
{
	Bit8u count;
	count = IMMEDIATEIb(i)&0x1f;
	IMMEDIATEIb(i) = count;
	i->Word.shift = BxOpcodeShiftTableG_RO__Ew[count].count;
	i->execute = BxOpcodeShiftTableG_RO__Ew[count].shift_fun->shiftR_EE;
	//call method on BX_CPU_C object
	BX_CPU_CALL_METHOD(i->execute, (icpu,i));
}

	void
BX_CPU_C::ROR_EEd(BX_CPU_C *icpu,bxInstruction_c *i)
{
	Bit8u count;
	count = IMMEDIATEIb(i)&0x1f;
	IMMEDIATEIb(i) = count;
	i->Word.shift = BxOpcodeShiftTableG_RO__Ed[count].count;
	i->execute = BxOpcodeShiftTableG_RO__Ed[count].shift_fun->shiftR_EE;
	//call method on BX_CPU_C object
	BX_CPU_CALL_METHOD(i->execute, (icpu,i));
}

	void
BX_CPU_C::RCL_EEb(BX_CPU_C *icpu,bxInstruction_c *i)
{
	Bit8u count;
	count = IMMEDIATEIb(i)&0x1f;
	IMMEDIATEIb(i) = count;
	i->Word.shift = BxOpcodeShiftTableG_RC__Eb[count].count;
	i->execute = BxOpcodeShiftTableG_RC__Eb[count].shift_fun->shiftL_EE;
	//call method on BX_CPU_C object
	BX_CPU_CALL_METHOD(i->execute, (icpu,i));
}

	void
BX_CPU_C::RCL_EEw(BX_CPU_C *icpu,bxInstruction_c *i)
{
	Bit8u count;
	count = IMMEDIATEIb(i)&0x1f;
	IMMEDIATEIb(i) = count;
	i->Word.shift = BxOpcodeShiftTableG_RC__Ew[count].count;
	i->execute = BxOpcodeShiftTableG_RC__Ew[count].shift_fun->shiftL_EE;
	//call method on BX_CPU_C object
	BX_CPU_CALL_METHOD(i->execute, (icpu,i));
}

	void
BX_CPU_C::RCL_EEd(BX_CPU_C *icpu,bxInstruction_c *i)
{
	Bit8u count;
	count = IMMEDIATEIb(i)&0x1f;
	IMMEDIATEIb(i) = count;
	i->Word.shift = BxOpcodeShiftTableG_RC__Ed[count].count;
	i->execute = BxOpcodeShiftTableG_RC__Ed[count].shift_fun->shiftL_EE;
	//call method on BX_CPU_C object
	BX_CPU_CALL_METHOD(i->execute, (icpu,i));
}

	void
BX_CPU_C::RCR_EEb(BX_CPU_C *icpu,bxInstruction_c *i)
{
	Bit8u count;
	count = IMMEDIATEIb(i)&0x1f;
	IMMEDIATEIb(i) = count;
	i->Word.shift = BxOpcodeShiftTableG_RC__Eb[count].count;
	i->execute = BxOpcodeShiftTableG_RC__Eb[count].shift_fun->shiftR_EE;
	//call method on BX_CPU_C object
	BX_CPU_CALL_METHOD(i->execute, (icpu,i));
}

	void
BX_CPU_C::RCR_EEw(BX_CPU_C *icpu,bxInstruction_c *i)
{
	Bit8u count;
	count = IMMEDIATEIb(i)&0x1f;
	IMMEDIATEIb(i) = count;
	i->Word.shift = BxOpcodeShiftTableG_RC__Ew[count].count;
	i->execute = BxOpcodeShiftTableG_RC__Ew[count].shift_fun->shiftR_EE;
	//call method on BX_CPU_C object
	BX_CPU_CALL_METHOD(i->execute, (icpu,i));
}

	void
BX_CPU_C::RCR_EEd(BX_CPU_C *icpu,bxInstruction_c *i)
{
	Bit8u count;
	count = IMMEDIATEIb(i)&0x1f;
	IMMEDIATEIb(i) = count;
	i->Word.shift = BxOpcodeShiftTableG_RC__Ed[count].count;
	i->execute = BxOpcodeShiftTableG_RC__Ed[count].shift_fun->shiftR_EE;
	//call method on BX_CPU_C object
	BX_CPU_CALL_METHOD(i->execute, (icpu,i));
}

	void
BX_CPU_C::SHL_EEb(BX_CPU_C *icpu,bxInstruction_c *i)
{
	Bit8u count;
	count = IMMEDIATEIb(i)&0x1f;
	IMMEDIATEIb(i) = count;
	i->Word.shift = BxOpcodeShiftTableG_SH__Eb[count].count;
	i->execute = BxOpcodeShiftTableG_SH__Eb[count].shift_fun->shiftL_EE;
	//call method on BX_CPU_C object
	BX_CPU_CALL_METHOD(i->execute, (icpu,i));
}

	void
BX_CPU_C::SHL_EEw(BX_CPU_C *icpu,bxInstruction_c *i)
{
	Bit8u count;
	count = IMMEDIATEIb(i)&0x1f;
	IMMEDIATEIb(i) = count;
	i->Word.shift = BxOpcodeShiftTableG_SH__Ew[count].count;
	i->execute = BxOpcodeShiftTableG_SH__Ew[count].shift_fun->shiftL_EE;
	//call method on BX_CPU_C object
	BX_CPU_CALL_METHOD(i->execute, (icpu,i));
}

	void
BX_CPU_C::SHL_EEd(BX_CPU_C *icpu,bxInstruction_c *i)
{
	Bit8u count;
	count = IMMEDIATEIb(i)&0x1f;
	IMMEDIATEIb(i) = count;
	i->Word.shift = BxOpcodeShiftTableG_SH__Ed[count].count;
	i->execute = BxOpcodeShiftTableG_SH__Ed[count].shift_fun->shiftL_EE;
	//call method on BX_CPU_C object
	BX_CPU_CALL_METHOD(i->execute, (icpu,i));
}

	void
BX_CPU_C::SHR_EEb(BX_CPU_C *icpu,bxInstruction_c *i)
{
	Bit8u count;
	count = IMMEDIATEIb(i)&0x1f;
	IMMEDIATEIb(i) = count;
	i->Word.shift = BxOpcodeShiftTableG_SH__Eb[count].count;
	i->execute = BxOpcodeShiftTableG_SH__Eb[count].shift_fun->shiftR_EE;
	//call method on BX_CPU_C object
	BX_CPU_CALL_METHOD(i->execute, (icpu,i));
}

	void
BX_CPU_C::SHR_EEw(BX_CPU_C *icpu,bxInstruction_c *i)
{
	Bit8u count;
	count = IMMEDIATEIb(i)&0x1f;
	IMMEDIATEIb(i) = count;
	i->Word.shift = BxOpcodeShiftTableG_SH__Ew[count].count;
	i->execute = BxOpcodeShiftTableG_SH__Ew[count].shift_fun->shiftR_EE;
	//call method on BX_CPU_C object
	BX_CPU_CALL_METHOD(i->execute, (icpu,i));
}

	void
BX_CPU_C::SHR_EEd(BX_CPU_C *icpu,bxInstruction_c *i)
{
	Bit8u count;
	count = IMMEDIATEIb(i)&0x1f;
	IMMEDIATEIb(i) = count;
	i->Word.shift = BxOpcodeShiftTableG_SH__Ed[count].count;
	i->execute = BxOpcodeShiftTableG_SH__Ed[count].shift_fun->shiftR_EE;
	//call method on BX_CPU_C object
	BX_CPU_CALL_METHOD(i->execute, (icpu,i));
}

	void
BX_CPU_C::SAR_EEb(BX_CPU_C *icpu,bxInstruction_c *i)
{
	Bit8u count;
	count = IMMEDIATEIb(i)&0x1f;
	IMMEDIATEIb(i) = count;
	i->Word.shift = BxOpcodeShiftTableG_SA__Eb[count].count;
	i->execute = BxOpcodeShiftTableG_SA__Eb[count].shift_fun->shiftR_EE;
	//call method on BX_CPU_C object
	BX_CPU_CALL_METHOD(i->execute, (icpu,i));
}

	void
BX_CPU_C::SAR_EEw(BX_CPU_C *icpu,bxInstruction_c *i)
{
	Bit8u count;
	count = IMMEDIATEIb(i)&0x1f;
	IMMEDIATEIb(i) = count;
	i->Word.shift = BxOpcodeShiftTableG_SA__Ew[count].count;
	i->execute = BxOpcodeShiftTableG_SA__Ew[count].shift_fun->shiftR_EE;
	//call method on BX_CPU_C object
	BX_CPU_CALL_METHOD(i->execute, (icpu,i));
}

	void
BX_CPU_C::SAR_EEd(BX_CPU_C *icpu,bxInstruction_c *i)
{
	Bit8u count;
	count = IMMEDIATEIb(i)&0x1f;
	IMMEDIATEIb(i) = count;
	i->Word.shift = BxOpcodeShiftTableG_SA__Ed[count].count;
	i->execute = BxOpcodeShiftTableG_SA__Ed[count].shift_fun->shiftR_EE;
	//call method on BX_CPU_C object
	BX_CPU_CALL_METHOD(i->execute, (icpu,i));
}

	void
BX_CPU_C::SHLD_EGwGw(BX_CPU_C *icpu,bxInstruction_c *i)
{
	Bit8u count;
	count = IMMEDIATEIb(i)&0x1f;
	IMMEDIATEIb(i) = count;
	i->Word.shift = BxOpcodeShiftTableG_SH_D_EwGw[count].count;
	i->execute = BxOpcodeShiftTableG_SH_D_EwGw[count].shift_fun->shiftL_EG;
	//call method on BX_CPU_C object
	BX_CPU_CALL_METHOD(i->execute, (icpu,i));
}

	void
BX_CPU_C::SHLD_EGdGd(BX_CPU_C *icpu,bxInstruction_c *i)
{
	Bit8u count;
	count = IMMEDIATEIb(i)&0x1f;
	IMMEDIATEIb(i) = count;
	i->Word.shift = BxOpcodeShiftTableG_SH_D_EdGd[count].count;
	i->execute = BxOpcodeShiftTableG_SH_D_EdGd[count].shift_fun->shiftL_EG;
	//call method on BX_CPU_C object
	BX_CPU_CALL_METHOD(i->execute, (icpu,i));
}

	void
BX_CPU_C::SHRD_EGwGw(BX_CPU_C *icpu,bxInstruction_c *i)
{
	Bit8u count;
	count = IMMEDIATEIb(i)&0x1f;
	IMMEDIATEIb(i) = count;
	i->Word.shift = BxOpcodeShiftTableG_SH_D_EwGw[count].count;
	i->execute = BxOpcodeShiftTableG_SH_D_EwGw[count].shift_fun->shiftR_EG;
	//call method on BX_CPU_C object
	BX_CPU_CALL_METHOD(i->execute, (icpu,i));
}

	void
BX_CPU_C::SHRD_EGdGd(BX_CPU_C *icpu,bxInstruction_c *i)
{
	Bit8u count;
	count = IMMEDIATEIb(i)&0x1f;
	IMMEDIATEIb(i) = count;
	i->Word.shift = BxOpcodeShiftTableG_SH_D_EdGd[count].count;
	i->execute = BxOpcodeShiftTableG_SH_D_EdGd[count].shift_fun->shiftR_EG;
	//call method on BX_CPU_C object
	BX_CPU_CALL_METHOD(i->execute, (icpu,i));
}

	void
BX_CPU_C::SHLD_EEwGw(BX_CPU_C *icpu,bxInstruction_c *i)
{
	Bit8u count;
	count = IMMEDIATEIb(i)&0x1f;
	IMMEDIATEIb(i) = count;
	i->Word.shift = BxOpcodeShiftTableG_SH_D_EwGw[count].count;
	i->execute = BxOpcodeShiftTableG_SH_D_EwGw[count].shift_fun->shiftL_EE;
	//call method on BX_CPU_C object
	BX_CPU_CALL_METHOD(i->execute, (icpu,i));
}

	void
BX_CPU_C::SHLD_EEdGd(BX_CPU_C *icpu,bxInstruction_c *i)
{
	Bit8u count;
	count = IMMEDIATEIb(i)&0x1f;
	IMMEDIATEIb(i) = count;
	i->Word.shift = BxOpcodeShiftTableG_SH_D_EdGd[count].count;
	i->execute = BxOpcodeShiftTableG_SH_D_EdGd[count].shift_fun->shiftL_EE;
	//call method on BX_CPU_C object
	BX_CPU_CALL_METHOD(i->execute, (icpu,i));
}

	void
BX_CPU_C::SHRD_EEwGw(BX_CPU_C *icpu,bxInstruction_c *i)
{
	Bit8u count;
	count = IMMEDIATEIb(i)&0x1f;
	IMMEDIATEIb(i) = count;
	i->Word.shift = BxOpcodeShiftTableG_SH_D_EwGw[count].count;
	i->execute = BxOpcodeShiftTableG_SH_D_EwGw[count].shift_fun->shiftR_EE;
	//call method on BX_CPU_C object
	BX_CPU_CALL_METHOD(i->execute, (icpu,i));
}

	void
BX_CPU_C::SHRD_EEdGd(BX_CPU_C *icpu,bxInstruction_c *i)
{
	Bit8u count;
	count = IMMEDIATEIb(i)&0x1f;
	IMMEDIATEIb(i) = count;
	i->Word.shift = BxOpcodeShiftTableG_SH_D_EdGd[count].count;
	i->execute = BxOpcodeShiftTableG_SH_D_EdGd[count].shift_fun->shiftR_EE;
	//call method on BX_CPU_C object
	BX_CPU_CALL_METHOD(i->execute, (icpu,i));
}

	void
BX_CPU_C::ROL_EGbCL(BX_CPU_C *icpu,bxInstruction_c *i)
{
	Bit8u count;
	count = RW_CL&0x1f;
	IMMEDIATEIb(i) = count;
	i->Word.shift = BxOpcodeShiftTableG_RO__Eb[count].count;
	//call method on BX_CPU_C object
	BX_CPU_CALL_METHOD(BxOpcodeShiftTableG_RO__Eb[count].shift_fun->shiftL_EG,(icpu,i));
}

	void
BX_CPU_C::ROL_EGwCL(BX_CPU_C *icpu,bxInstruction_c *i)
{
	Bit8u count;
	count = RW_CL&0x1f;
	IMMEDIATEIb(i) = count;
	i->Word.shift = BxOpcodeShiftTableG_RO__Ew[count].count;
	//call method on BX_CPU_C object
	BX_CPU_CALL_METHOD(BxOpcodeShiftTableG_RO__Ew[count].shift_fun->shiftL_EG,(icpu,i));
}

	void
BX_CPU_C::ROL_EGdCL(BX_CPU_C *icpu,bxInstruction_c *i)
{
	Bit8u count;
	count = RW_CL&0x1f;
	IMMEDIATEIb(i) = count;
	i->Word.shift = BxOpcodeShiftTableG_RO__Ed[count].count;
	//call method on BX_CPU_C object
	BX_CPU_CALL_METHOD(BxOpcodeShiftTableG_RO__Ed[count].shift_fun->shiftL_EG,(icpu,i));
}

	void
BX_CPU_C::ROR_EGbCL(BX_CPU_C *icpu,bxInstruction_c *i)
{
	Bit8u count;
	count = RW_CL&0x1f;
	IMMEDIATEIb(i) = count;
	i->Word.shift = BxOpcodeShiftTableG_RO__Eb[count].count;
	//call method on BX_CPU_C object
	BX_CPU_CALL_METHOD(BxOpcodeShiftTableG_RO__Eb[count].shift_fun->shiftR_EG,(icpu,i));
}

	void
BX_CPU_C::ROR_EGwCL(BX_CPU_C *icpu,bxInstruction_c *i)
{
	Bit8u count;
	count = RW_CL&0x1f;
	IMMEDIATEIb(i) = count;
	i->Word.shift = BxOpcodeShiftTableG_RO__Ew[count].count;
	//call method on BX_CPU_C object
	BX_CPU_CALL_METHOD(BxOpcodeShiftTableG_RO__Ew[count].shift_fun->shiftR_EG,(icpu,i));
}

	void
BX_CPU_C::ROR_EGdCL(BX_CPU_C *icpu,bxInstruction_c *i)
{
	Bit8u count;
	count = RW_CL&0x1f;
	IMMEDIATEIb(i) = count;
	i->Word.shift = BxOpcodeShiftTableG_RO__Ed[count].count;
	//call method on BX_CPU_C object
	BX_CPU_CALL_METHOD(BxOpcodeShiftTableG_RO__Ed[count].shift_fun->shiftR_EG,(icpu,i));
}

	void
BX_CPU_C::RCL_EGbCL(BX_CPU_C *icpu,bxInstruction_c *i)
{
	Bit8u count;
	count = RW_CL&0x1f;
	IMMEDIATEIb(i) = count;
	i->Word.shift = BxOpcodeShiftTableG_RC__Eb[count].count;
	//call method on BX_CPU_C object
	BX_CPU_CALL_METHOD(BxOpcodeShiftTableG_RC__Eb[count].shift_fun->shiftL_EG,(icpu,i));
}

	void
BX_CPU_C::RCL_EGwCL(BX_CPU_C *icpu,bxInstruction_c *i)
{
	Bit8u count;
	count = RW_CL&0x1f;
	IMMEDIATEIb(i) = count;
	i->Word.shift = BxOpcodeShiftTableG_RC__Ew[count].count;
	//call method on BX_CPU_C object
	BX_CPU_CALL_METHOD(BxOpcodeShiftTableG_RC__Ew[count].shift_fun->shiftL_EG,(icpu,i));
}

	void
BX_CPU_C::RCL_EGdCL(BX_CPU_C *icpu,bxInstruction_c *i)
{
	Bit8u count;
	count = RW_CL&0x1f;
	IMMEDIATEIb(i) = count;
	i->Word.shift = BxOpcodeShiftTableG_RC__Ed[count].count;
	//call method on BX_CPU_C object
	BX_CPU_CALL_METHOD(BxOpcodeShiftTableG_RC__Ed[count].shift_fun->shiftL_EG,(icpu,i));
}

	void
BX_CPU_C::RCR_EGbCL(BX_CPU_C *icpu,bxInstruction_c *i)
{
	Bit8u count;
	count = RW_CL&0x1f;
	IMMEDIATEIb(i) = count;
	i->Word.shift = BxOpcodeShiftTableG_RC__Eb[count].count;
	//call method on BX_CPU_C object
	BX_CPU_CALL_METHOD(BxOpcodeShiftTableG_RC__Eb[count].shift_fun->shiftR_EG,(icpu,i));
}

	void
BX_CPU_C::RCR_EGwCL(BX_CPU_C *icpu,bxInstruction_c *i)
{
	Bit8u count;
	count = RW_CL&0x1f;
	IMMEDIATEIb(i) = count;
	i->Word.shift = BxOpcodeShiftTableG_RC__Ew[count].count;
	//call method on BX_CPU_C object
	BX_CPU_CALL_METHOD(BxOpcodeShiftTableG_RC__Ew[count].shift_fun->shiftR_EG,(icpu,i));
}

	void
BX_CPU_C::RCR_EGdCL(BX_CPU_C *icpu,bxInstruction_c *i)
{
	Bit8u count;
	count = RW_CL&0x1f;
	IMMEDIATEIb(i) = count;
	i->Word.shift = BxOpcodeShiftTableG_RC__Ed[count].count;
	//call method on BX_CPU_C object
	BX_CPU_CALL_METHOD(BxOpcodeShiftTableG_RC__Ed[count].shift_fun->shiftR_EG,(icpu,i));
}

	void
BX_CPU_C::SHL_EGbCL(BX_CPU_C *icpu,bxInstruction_c *i)
{
	Bit8u count;
	count = RW_CL&0x1f;
	IMMEDIATEIb(i) = count;
	i->Word.shift = BxOpcodeShiftTableG_SH__Eb[count].count;
	//call method on BX_CPU_C object
	BX_CPU_CALL_METHOD(BxOpcodeShiftTableG_SH__Eb[count].shift_fun->shiftL_EG,(icpu,i));
}

	void
BX_CPU_C::SHL_EGwCL(BX_CPU_C *icpu,bxInstruction_c *i)
{
	Bit8u count;
	count = RW_CL&0x1f;
	IMMEDIATEIb(i) = count;
	i->Word.shift = BxOpcodeShiftTableG_SH__Ew[count].count;
	//call method on BX_CPU_C object
	BX_CPU_CALL_METHOD(BxOpcodeShiftTableG_SH__Ew[count].shift_fun->shiftL_EG,(icpu,i));
}

	void
BX_CPU_C::SHL_EGdCL(BX_CPU_C *icpu,bxInstruction_c *i)
{
	Bit8u count;
	count = RW_CL&0x1f;
	IMMEDIATEIb(i) = count;
	i->Word.shift = BxOpcodeShiftTableG_SH__Ed[count].count;
	//call method on BX_CPU_C object
	BX_CPU_CALL_METHOD(BxOpcodeShiftTableG_SH__Ed[count].shift_fun->shiftL_EG,(icpu,i));
}

	void
BX_CPU_C::SHR_EGbCL(BX_CPU_C *icpu,bxInstruction_c *i)
{
	Bit8u count;
	count = RW_CL&0x1f;
	IMMEDIATEIb(i) = count;
	i->Word.shift = BxOpcodeShiftTableG_SH__Eb[count].count;
	//call method on BX_CPU_C object
	BX_CPU_CALL_METHOD(BxOpcodeShiftTableG_SH__Eb[count].shift_fun->shiftR_EG,(icpu,i));
}

	void
BX_CPU_C::SHR_EGwCL(BX_CPU_C *icpu,bxInstruction_c *i)
{
	Bit8u count;
	count = RW_CL&0x1f;
	IMMEDIATEIb(i) = count;
	i->Word.shift = BxOpcodeShiftTableG_SH__Ew[count].count;
	//call method on BX_CPU_C object
	BX_CPU_CALL_METHOD(BxOpcodeShiftTableG_SH__Ew[count].shift_fun->shiftR_EG,(icpu,i));
}

	void
BX_CPU_C::SHR_EGdCL(BX_CPU_C *icpu,bxInstruction_c *i)
{
	Bit8u count;
	count = RW_CL&0x1f;
	IMMEDIATEIb(i) = count;
	i->Word.shift = BxOpcodeShiftTableG_SH__Ed[count].count;
	//call method on BX_CPU_C object
	BX_CPU_CALL_METHOD(BxOpcodeShiftTableG_SH__Ed[count].shift_fun->shiftR_EG,(icpu,i));
}

	void
BX_CPU_C::SAR_EGbCL(BX_CPU_C *icpu,bxInstruction_c *i)
{
	Bit8u count;
	count = RW_CL&0x1f;
	IMMEDIATEIb(i) = count;
	i->Word.shift = BxOpcodeShiftTableG_SA__Eb[count].count;
	//call method on BX_CPU_C object
	BX_CPU_CALL_METHOD(BxOpcodeShiftTableG_SA__Eb[count].shift_fun->shiftR_EG,(icpu,i));
}

	void
BX_CPU_C::SAR_EGwCL(BX_CPU_C *icpu,bxInstruction_c *i)
{
	Bit8u count;
	count = RW_CL&0x1f;
	IMMEDIATEIb(i) = count;
	i->Word.shift = BxOpcodeShiftTableG_SA__Ew[count].count;
	//call method on BX_CPU_C object
	BX_CPU_CALL_METHOD(BxOpcodeShiftTableG_SA__Ew[count].shift_fun->shiftR_EG,(icpu,i));
}

	void
BX_CPU_C::SAR_EGdCL(BX_CPU_C *icpu,bxInstruction_c *i)
{
	Bit8u count;
	count = RW_CL&0x1f;
	IMMEDIATEIb(i) = count;
	i->Word.shift = BxOpcodeShiftTableG_SA__Ed[count].count;
	//call method on BX_CPU_C object
	BX_CPU_CALL_METHOD(BxOpcodeShiftTableG_SA__Ed[count].shift_fun->shiftR_EG,(icpu,i));
}

	void
BX_CPU_C::ROL_EEbCL(BX_CPU_C *icpu,bxInstruction_c *i)
{
	Bit8u count;
	count = RW_CL&0x1f;
	IMMEDIATEIb(i) = count;
	i->Word.shift = BxOpcodeShiftTableG_RO__Eb[count].count;
	//call method on BX_CPU_C object
	BX_CPU_CALL_METHOD(BxOpcodeShiftTableG_RO__Eb[count].shift_fun->shiftL_EE,(icpu,i));
}

	void
BX_CPU_C::ROL_EEwCL(BX_CPU_C *icpu,bxInstruction_c *i)
{
	Bit8u count;
	count = RW_CL&0x1f;
	IMMEDIATEIb(i) = count;
	i->Word.shift = BxOpcodeShiftTableG_RO__Ew[count].count;
	//call method on BX_CPU_C object
	BX_CPU_CALL_METHOD(BxOpcodeShiftTableG_RO__Ew[count].shift_fun->shiftL_EE,(icpu,i));
}

	void
BX_CPU_C::ROL_EEdCL(BX_CPU_C *icpu,bxInstruction_c *i)
{
	Bit8u count;
	count = RW_CL&0x1f;
	IMMEDIATEIb(i) = count;
	i->Word.shift = BxOpcodeShiftTableG_RO__Ed[count].count;
	//call method on BX_CPU_C object
	BX_CPU_CALL_METHOD(BxOpcodeShiftTableG_RO__Ed[count].shift_fun->shiftL_EE,(icpu,i));
}

	void
BX_CPU_C::ROR_EEbCL(BX_CPU_C *icpu,bxInstruction_c *i)
{
	Bit8u count;
	count = RW_CL&0x1f;
	IMMEDIATEIb(i) = count;
	i->Word.shift = BxOpcodeShiftTableG_RO__Eb[count].count;
	//call method on BX_CPU_C object
	BX_CPU_CALL_METHOD(BxOpcodeShiftTableG_RO__Eb[count].shift_fun->shiftR_EE,(icpu,i));
}

	void
BX_CPU_C::ROR_EEwCL(BX_CPU_C *icpu,bxInstruction_c *i)
{
	Bit8u count;
	count = RW_CL&0x1f;
	IMMEDIATEIb(i) = count;
	i->Word.shift = BxOpcodeShiftTableG_RO__Ew[count].count;
	//call method on BX_CPU_C object
	BX_CPU_CALL_METHOD(BxOpcodeShiftTableG_RO__Ew[count].shift_fun->shiftR_EE,(icpu,i));
}

	void
BX_CPU_C::ROR_EEdCL(BX_CPU_C *icpu,bxInstruction_c *i)
{
	Bit8u count;
	count = RW_CL&0x1f;
	IMMEDIATEIb(i) = count;
	i->Word.shift = BxOpcodeShiftTableG_RO__Ed[count].count;
	//call method on BX_CPU_C object
	BX_CPU_CALL_METHOD(BxOpcodeShiftTableG_RO__Ed[count].shift_fun->shiftR_EE,(icpu,i));
}

	void
BX_CPU_C::RCL_EEbCL(BX_CPU_C *icpu,bxInstruction_c *i)
{
	Bit8u count;
	count = RW_CL&0x1f;
	IMMEDIATEIb(i) = count;
	i->Word.shift = BxOpcodeShiftTableG_RC__Eb[count].count;
	//call method on BX_CPU_C object
	BX_CPU_CALL_METHOD(BxOpcodeShiftTableG_RC__Eb[count].shift_fun->shiftL_EE,(icpu,i));
}

	void
BX_CPU_C::RCL_EEwCL(BX_CPU_C *icpu,bxInstruction_c *i)
{
	Bit8u count;
	count = RW_CL&0x1f;
	IMMEDIATEIb(i) = count;
	i->Word.shift = BxOpcodeShiftTableG_RC__Ew[count].count;
	//call method on BX_CPU_C object
	BX_CPU_CALL_METHOD(BxOpcodeShiftTableG_RC__Ew[count].shift_fun->shiftL_EE,(icpu,i));
}

	void
BX_CPU_C::RCL_EEdCL(BX_CPU_C *icpu,bxInstruction_c *i)
{
	Bit8u count;
	count = RW_CL&0x1f;
	IMMEDIATEIb(i) = count;
	i->Word.shift = BxOpcodeShiftTableG_RC__Ed[count].count;
	//call method on BX_CPU_C object
	BX_CPU_CALL_METHOD(BxOpcodeShiftTableG_RC__Ed[count].shift_fun->shiftL_EE,(icpu,i));
}

	void
BX_CPU_C::RCR_EEbCL(BX_CPU_C *icpu,bxInstruction_c *i)
{
	Bit8u count;
	count = RW_CL&0x1f;
	IMMEDIATEIb(i) = count;
	i->Word.shift = BxOpcodeShiftTableG_RC__Eb[count].count;
	//call method on BX_CPU_C object
	BX_CPU_CALL_METHOD(BxOpcodeShiftTableG_RC__Eb[count].shift_fun->shiftR_EE,(icpu,i));
}

	void
BX_CPU_C::RCR_EEwCL(BX_CPU_C *icpu,bxInstruction_c *i)
{
	Bit8u count;
	count = RW_CL&0x1f;
	IMMEDIATEIb(i) = count;
	i->Word.shift = BxOpcodeShiftTableG_RC__Ew[count].count;
	//call method on BX_CPU_C object
	BX_CPU_CALL_METHOD(BxOpcodeShiftTableG_RC__Ew[count].shift_fun->shiftR_EE,(icpu,i));
}

	void
BX_CPU_C::RCR_EEdCL(BX_CPU_C *icpu,bxInstruction_c *i)
{
	Bit8u count;
	count = RW_CL&0x1f;
	IMMEDIATEIb(i) = count;
	i->Word.shift = BxOpcodeShiftTableG_RC__Ed[count].count;
	//call method on BX_CPU_C object
	BX_CPU_CALL_METHOD(BxOpcodeShiftTableG_RC__Ed[count].shift_fun->shiftR_EE,(icpu,i));
}

	void
BX_CPU_C::SHL_EEbCL(BX_CPU_C *icpu,bxInstruction_c *i)
{
	Bit8u count;
	count = RW_CL&0x1f;
	IMMEDIATEIb(i) = count;
	i->Word.shift = BxOpcodeShiftTableG_SH__Eb[count].count;
	//call method on BX_CPU_C object
	BX_CPU_CALL_METHOD(BxOpcodeShiftTableG_SH__Eb[count].shift_fun->shiftL_EE,(icpu,i));
}

	void
BX_CPU_C::SHL_EEwCL(BX_CPU_C *icpu,bxInstruction_c *i)
{
	Bit8u count;
	count = RW_CL&0x1f;
	IMMEDIATEIb(i) = count;
	i->Word.shift = BxOpcodeShiftTableG_SH__Ew[count].count;
	//call method on BX_CPU_C object
	BX_CPU_CALL_METHOD(BxOpcodeShiftTableG_SH__Ew[count].shift_fun->shiftL_EE,(icpu,i));
}

	void
BX_CPU_C::SHL_EEdCL(BX_CPU_C *icpu,bxInstruction_c *i)
{
	Bit8u count;
	count = RW_CL&0x1f;
	IMMEDIATEIb(i) = count;
	i->Word.shift = BxOpcodeShiftTableG_SH__Ed[count].count;
	//call method on BX_CPU_C object
	BX_CPU_CALL_METHOD(BxOpcodeShiftTableG_SH__Ed[count].shift_fun->shiftL_EE,(icpu,i));
}

	void
BX_CPU_C::SHR_EEbCL(BX_CPU_C *icpu,bxInstruction_c *i)
{
	Bit8u count;
	count = RW_CL&0x1f;
	IMMEDIATEIb(i) = count;
	i->Word.shift = BxOpcodeShiftTableG_SH__Eb[count].count;
	//call method on BX_CPU_C object
	BX_CPU_CALL_METHOD(BxOpcodeShiftTableG_SH__Eb[count].shift_fun->shiftR_EE,(icpu,i));
}

	void
BX_CPU_C::SHR_EEwCL(BX_CPU_C *icpu,bxInstruction_c *i)
{
	Bit8u count;
	count = RW_CL&0x1f;
	IMMEDIATEIb(i) = count;
	i->Word.shift = BxOpcodeShiftTableG_SH__Ew[count].count;
	//call method on BX_CPU_C object
	BX_CPU_CALL_METHOD(BxOpcodeShiftTableG_SH__Ew[count].shift_fun->shiftR_EE,(icpu,i));
}

	void
BX_CPU_C::SHR_EEdCL(BX_CPU_C *icpu,bxInstruction_c *i)
{
	Bit8u count;
	count = RW_CL&0x1f;
	IMMEDIATEIb(i) = count;
	i->Word.shift = BxOpcodeShiftTableG_SH__Ed[count].count;
	//call method on BX_CPU_C object
	BX_CPU_CALL_METHOD(BxOpcodeShiftTableG_SH__Ed[count].shift_fun->shiftR_EE,(icpu,i));
}

	void
BX_CPU_C::SAR_EEbCL(BX_CPU_C *icpu,bxInstruction_c *i)
{
	Bit8u count;
	count = RW_CL&0x1f;
	IMMEDIATEIb(i) = count;
	i->Word.shift = BxOpcodeShiftTableG_SA__Eb[count].count;
	//call method on BX_CPU_C object
	BX_CPU_CALL_METHOD(BxOpcodeShiftTableG_SA__Eb[count].shift_fun->shiftR_EE,(icpu,i));
}

	void
BX_CPU_C::SAR_EEwCL(BX_CPU_C *icpu,bxInstruction_c *i)
{
	Bit8u count;
	count = RW_CL&0x1f;
	IMMEDIATEIb(i) = count;
	i->Word.shift = BxOpcodeShiftTableG_SA__Ew[count].count;
	//call method on BX_CPU_C object
	BX_CPU_CALL_METHOD(BxOpcodeShiftTableG_SA__Ew[count].shift_fun->shiftR_EE,(icpu,i));
}

	void
BX_CPU_C::SAR_EEdCL(BX_CPU_C *icpu,bxInstruction_c *i)
{
	Bit8u count;
	count = RW_CL&0x1f;
	IMMEDIATEIb(i) = count;
	i->Word.shift = BxOpcodeShiftTableG_SA__Ed[count].count;
	//call method on BX_CPU_C object
	BX_CPU_CALL_METHOD(BxOpcodeShiftTableG_SA__Ed[count].shift_fun->shiftR_EE,(icpu,i));
}

	void
BX_CPU_C::SHLD_EGwGwCL(BX_CPU_C *icpu,bxInstruction_c *i)
{
	Bit8u count;
	count = RW_CL&0x1f;
	IMMEDIATEIb(i) = count;
	i->Word.shift = BxOpcodeShiftTableG_SH_D_EwGw[count].count;
	//call method on BX_CPU_C object
	BX_CPU_CALL_METHOD(BxOpcodeShiftTableG_SH_D_EwGw[count].shift_fun->shiftL_EG,(icpu,i));
}

	void
BX_CPU_C::SHLD_EGdGdCL(BX_CPU_C *icpu,bxInstruction_c *i)
{
	Bit8u count;
	count = RW_CL&0x1f;
	IMMEDIATEIb(i) = count;
	i->Word.shift = BxOpcodeShiftTableG_SH_D_EdGd[count].count;
	//call method on BX_CPU_C object
	BX_CPU_CALL_METHOD(BxOpcodeShiftTableG_SH_D_EdGd[count].shift_fun->shiftL_EG,(icpu,i));
}

	void
BX_CPU_C::SHRD_EGwGwCL(BX_CPU_C *icpu,bxInstruction_c *i)
{
	Bit8u count;
	count = RW_CL&0x1f;
	IMMEDIATEIb(i) = count;
	i->Word.shift = BxOpcodeShiftTableG_SH_D_EwGw[count].count;
	//call method on BX_CPU_C object
	BX_CPU_CALL_METHOD(BxOpcodeShiftTableG_SH_D_EwGw[count].shift_fun->shiftR_EG,(icpu,i));
}

	void
BX_CPU_C::SHRD_EGdGdCL(BX_CPU_C *icpu,bxInstruction_c *i)
{
	Bit8u count;
	count = RW_CL&0x1f;
	IMMEDIATEIb(i) = count;
	i->Word.shift = BxOpcodeShiftTableG_SH_D_EdGd[count].count;
	//call method on BX_CPU_C object
	BX_CPU_CALL_METHOD(BxOpcodeShiftTableG_SH_D_EdGd[count].shift_fun->shiftR_EG,(icpu,i));
}

	void
BX_CPU_C::SHLD_EEwGwCL(BX_CPU_C *icpu,bxInstruction_c *i)
{
	Bit8u count;
	count = RW_CL&0x1f;
	IMMEDIATEIb(i) = count;
	i->Word.shift = BxOpcodeShiftTableG_SH_D_EwGw[count].count;
	//call method on BX_CPU_C object
	BX_CPU_CALL_METHOD(BxOpcodeShiftTableG_SH_D_EwGw[count].shift_fun->shiftL_EE,(icpu,i));
}

	void
BX_CPU_C::SHLD_EEdGdCL(BX_CPU_C *icpu,bxInstruction_c *i)
{
	Bit8u count;
	count = RW_CL&0x1f;
	IMMEDIATEIb(i) = count;
	i->Word.shift = BxOpcodeShiftTableG_SH_D_EdGd[count].count;
	//call method on BX_CPU_C object
	BX_CPU_CALL_METHOD(BxOpcodeShiftTableG_SH_D_EdGd[count].shift_fun->shiftL_EE,(icpu,i));
}

	void
BX_CPU_C::SHRD_EEwGwCL(BX_CPU_C *icpu,bxInstruction_c *i)
{
	Bit8u count;
	count = RW_CL&0x1f;
	IMMEDIATEIb(i) = count;
	i->Word.shift = BxOpcodeShiftTableG_SH_D_EwGw[count].count;
	//call method on BX_CPU_C object
	BX_CPU_CALL_METHOD(BxOpcodeShiftTableG_SH_D_EwGw[count].shift_fun->shiftR_EE,(icpu,i));
}

	void
BX_CPU_C::SHRD_EEdGdCL(BX_CPU_C *icpu,bxInstruction_c *i)
{
	Bit8u count;
	count = RW_CL&0x1f;
	IMMEDIATEIb(i) = count;
	i->Word.shift = BxOpcodeShiftTableG_SH_D_EdGd[count].count;
	//call method on BX_CPU_C object
	BX_CPU_CALL_METHOD(BxOpcodeShiftTableG_SH_D_EdGd[count].shift_fun->shiftR_EE,(icpu,i));
}

