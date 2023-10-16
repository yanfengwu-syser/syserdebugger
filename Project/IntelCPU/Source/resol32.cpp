/////////////////////////////////////////////////////////////////////////
// $Id: resolve32.cc,v 1.5 2001/10/03 13:10:37 bdenney Exp $
/////////////////////////////////////////////////////////////////////////


#include "stdafx.h"
#include "x86cpu.h"
//---------------------------------------------------------
//三十二位有效地址 计算函数
//---------------------------------------------------------


	void
BX_CPU_C::Resolve32Mod0Rm0(BX_CPU_C *icpu,bxInstruction_c *i)
{
	RMAddr(i) = READ_VIRTUAL_32BIT_REG(0x00);
}
	void
BX_CPU_C::Resolve32Mod0Rm1(BX_CPU_C *icpu,bxInstruction_c *i)
{
	RMAddr(i) = READ_VIRTUAL_32BIT_REG(0x01);
}
	void
BX_CPU_C::Resolve32Mod0Rm2(BX_CPU_C *icpu,bxInstruction_c *i)
{
	RMAddr(i) = READ_VIRTUAL_32BIT_REG(0x02);
}
	void
BX_CPU_C::Resolve32Mod0Rm3(BX_CPU_C *icpu,bxInstruction_c *i)
{
	RMAddr(i) = READ_VIRTUAL_32BIT_REG(0x03);
}
	void
BX_CPU_C::Resolve32Mod0Rm4(BX_CPU_C *icpu,bxInstruction_c *i)
{
	// escape to 2-byte
}
	void
BX_CPU_C::Resolve32Mod0Rm5(BX_CPU_C *icpu,bxInstruction_c *i)
{
	// d32, no registers used
	RMAddr(i) = i->displ32u;
}
	void
BX_CPU_C::Resolve32Mod0Rm6(BX_CPU_C *icpu,bxInstruction_c *i)
{
	RMAddr(i) = READ_VIRTUAL_32BIT_REG(0x06);
}
	void
BX_CPU_C::Resolve32Mod0Rm7(BX_CPU_C *icpu,bxInstruction_c *i)
{
	RMAddr(i) = READ_VIRTUAL_32BIT_REG(0x07);
}
//---------------------------------------------------------
	void
BX_CPU_C::Resolve32Mod1or2Rm0(BX_CPU_C *icpu,bxInstruction_c *i)
{
	RMAddr(i) = READ_VIRTUAL_32BIT_REG(0x00) + i->displ32u;
}
	void
BX_CPU_C::Resolve32Mod1or2Rm1(BX_CPU_C *icpu,bxInstruction_c *i)
{
	RMAddr(i) = READ_VIRTUAL_32BIT_REG(0x01) + i->displ32u;
}
	void
BX_CPU_C::Resolve32Mod1or2Rm2(BX_CPU_C *icpu,bxInstruction_c *i)
{
	RMAddr(i) = READ_VIRTUAL_32BIT_REG(0x02) + i->displ32u;
}
	void
BX_CPU_C::Resolve32Mod1or2Rm3(BX_CPU_C *icpu,bxInstruction_c *i)
{
	RMAddr(i) = READ_VIRTUAL_32BIT_REG(0x03) + i->displ32u;
}
	void
BX_CPU_C::Resolve32Mod1or2Rm4(BX_CPU_C *icpu,bxInstruction_c *i)
{
	// escape to 2-byte
}
	void
BX_CPU_C::Resolve32Mod1or2Rm5(BX_CPU_C *icpu,bxInstruction_c *i)
{
	RMAddr(i) = READ_VIRTUAL_32BIT_REG(0x05) + i->displ32u;
}
	void
BX_CPU_C::Resolve32Mod1or2Rm6(BX_CPU_C *icpu,bxInstruction_c *i)
{
	RMAddr(i) = READ_VIRTUAL_32BIT_REG(0x06) + i->displ32u;
}
	void
BX_CPU_C::Resolve32Mod1or2Rm7(BX_CPU_C *icpu,bxInstruction_c *i)
{
	RMAddr(i) = READ_VIRTUAL_32BIT_REG(0x07) + i->displ32u;
}
//---------------------------------------------------------
	void
BX_CPU_C::Resolve32Mod1or2EffectAddress_sib0x00(BX_CPU_C *icpu,bxInstruction_c *i)
{
	RMAddr(i) = READ_VIRTUAL_32BIT_REG(0x00) +
		(READ_VIRTUAL_32BIT_REG(0x00) <<0x00) + i->displ32u;
}

	void
BX_CPU_C::Resolve32Mod1or2EffectAddress_sib0x01(BX_CPU_C *icpu,bxInstruction_c *i)
{
	RMAddr(i) = READ_VIRTUAL_32BIT_REG(0x01) +
		(READ_VIRTUAL_32BIT_REG(0x00) <<0x00) + i->displ32u;
}

	void
BX_CPU_C::Resolve32Mod1or2EffectAddress_sib0x02(BX_CPU_C *icpu,bxInstruction_c *i)
{
	RMAddr(i) = READ_VIRTUAL_32BIT_REG(0x02) +
		(READ_VIRTUAL_32BIT_REG(0x00) <<0x00) + i->displ32u;
}

	void
BX_CPU_C::Resolve32Mod1or2EffectAddress_sib0x03(BX_CPU_C *icpu,bxInstruction_c *i)
{
	RMAddr(i) = READ_VIRTUAL_32BIT_REG(0x03) +
		(READ_VIRTUAL_32BIT_REG(0x00) <<0x00) + i->displ32u;
}

	void
BX_CPU_C::Resolve32Mod1or2EffectAddress_sib0x04(BX_CPU_C *icpu,bxInstruction_c *i)
{
	RMAddr(i) = READ_VIRTUAL_32BIT_REG(0x04) +
		(READ_VIRTUAL_32BIT_REG(0x00) <<0x00) + i->displ32u;
}

	void
BX_CPU_C::Resolve32Mod1or2EffectAddress_sib0x05(BX_CPU_C *icpu,bxInstruction_c *i)
{
	RMAddr(i) = READ_VIRTUAL_32BIT_REG(0x05) +
		(READ_VIRTUAL_32BIT_REG(0x00) <<0x00) + i->displ32u;
}

	void
BX_CPU_C::Resolve32Mod1or2EffectAddress_sib0x06(BX_CPU_C *icpu,bxInstruction_c *i)
{
	RMAddr(i) = READ_VIRTUAL_32BIT_REG(0x06) +
		(READ_VIRTUAL_32BIT_REG(0x00) <<0x00) + i->displ32u;
}

	void
BX_CPU_C::Resolve32Mod1or2EffectAddress_sib0x07(BX_CPU_C *icpu,bxInstruction_c *i)
{
	RMAddr(i) = READ_VIRTUAL_32BIT_REG(0x07) +
		(READ_VIRTUAL_32BIT_REG(0x00) <<0x00) + i->displ32u;
}

	void
BX_CPU_C::Resolve32Mod1or2EffectAddress_sib0x08(BX_CPU_C *icpu,bxInstruction_c *i)
{
	RMAddr(i) = READ_VIRTUAL_32BIT_REG(0x00) +
		(READ_VIRTUAL_32BIT_REG(0x01) <<0x00) + i->displ32u;
}

	void
BX_CPU_C::Resolve32Mod1or2EffectAddress_sib0x09(BX_CPU_C *icpu,bxInstruction_c *i)
{
	RMAddr(i) = READ_VIRTUAL_32BIT_REG(0x01) +
		(READ_VIRTUAL_32BIT_REG(0x01) <<0x00) + i->displ32u;
}

	void
BX_CPU_C::Resolve32Mod1or2EffectAddress_sib0x0a(BX_CPU_C *icpu,bxInstruction_c *i)
{
	RMAddr(i) = READ_VIRTUAL_32BIT_REG(0x02) +
		(READ_VIRTUAL_32BIT_REG(0x01) <<0x00) + i->displ32u;
}

	void
BX_CPU_C::Resolve32Mod1or2EffectAddress_sib0x0b(BX_CPU_C *icpu,bxInstruction_c *i)
{
	RMAddr(i) = READ_VIRTUAL_32BIT_REG(0x03) +
		(READ_VIRTUAL_32BIT_REG(0x01) <<0x00) + i->displ32u;
}

	void
BX_CPU_C::Resolve32Mod1or2EffectAddress_sib0x0c(BX_CPU_C *icpu,bxInstruction_c *i)
{
	RMAddr(i) = READ_VIRTUAL_32BIT_REG(0x04) +
		(READ_VIRTUAL_32BIT_REG(0x01) <<0x00) + i->displ32u;
}

	void
BX_CPU_C::Resolve32Mod1or2EffectAddress_sib0x0d(BX_CPU_C *icpu,bxInstruction_c *i)
{
	RMAddr(i) = READ_VIRTUAL_32BIT_REG(0x05) +
		(READ_VIRTUAL_32BIT_REG(0x01) <<0x00) + i->displ32u;
}

	void
BX_CPU_C::Resolve32Mod1or2EffectAddress_sib0x0e(BX_CPU_C *icpu,bxInstruction_c *i)
{
	RMAddr(i) = READ_VIRTUAL_32BIT_REG(0x06) +
		(READ_VIRTUAL_32BIT_REG(0x01) <<0x00) + i->displ32u;
}

	void
BX_CPU_C::Resolve32Mod1or2EffectAddress_sib0x0f(BX_CPU_C *icpu,bxInstruction_c *i)
{
	RMAddr(i) = READ_VIRTUAL_32BIT_REG(0x07) +
		(READ_VIRTUAL_32BIT_REG(0x01) <<0x00) + i->displ32u;
}

	void
BX_CPU_C::Resolve32Mod1or2EffectAddress_sib0x10(BX_CPU_C *icpu,bxInstruction_c *i)
{
	RMAddr(i) = READ_VIRTUAL_32BIT_REG(0x00) +
		(READ_VIRTUAL_32BIT_REG(0x02) <<0x00) + i->displ32u;
}

	void
BX_CPU_C::Resolve32Mod1or2EffectAddress_sib0x11(BX_CPU_C *icpu,bxInstruction_c *i)
{
	RMAddr(i) = READ_VIRTUAL_32BIT_REG(0x01) +
		(READ_VIRTUAL_32BIT_REG(0x02) <<0x00) + i->displ32u;
}

	void
BX_CPU_C::Resolve32Mod1or2EffectAddress_sib0x12(BX_CPU_C *icpu,bxInstruction_c *i)
{
	RMAddr(i) = READ_VIRTUAL_32BIT_REG(0x02) +
		(READ_VIRTUAL_32BIT_REG(0x02) <<0x00) + i->displ32u;
}

	void
BX_CPU_C::Resolve32Mod1or2EffectAddress_sib0x13(BX_CPU_C *icpu,bxInstruction_c *i)
{
	RMAddr(i) = READ_VIRTUAL_32BIT_REG(0x03) +
		(READ_VIRTUAL_32BIT_REG(0x02) <<0x00) + i->displ32u;
}

	void
BX_CPU_C::Resolve32Mod1or2EffectAddress_sib0x14(BX_CPU_C *icpu,bxInstruction_c *i)
{
	RMAddr(i) = READ_VIRTUAL_32BIT_REG(0x04) +
		(READ_VIRTUAL_32BIT_REG(0x02) <<0x00) + i->displ32u;
}

	void
BX_CPU_C::Resolve32Mod1or2EffectAddress_sib0x15(BX_CPU_C *icpu,bxInstruction_c *i)
{
	RMAddr(i) = READ_VIRTUAL_32BIT_REG(0x05) +
		(READ_VIRTUAL_32BIT_REG(0x02) <<0x00) + i->displ32u;
}

	void
BX_CPU_C::Resolve32Mod1or2EffectAddress_sib0x16(BX_CPU_C *icpu,bxInstruction_c *i)
{
	RMAddr(i) = READ_VIRTUAL_32BIT_REG(0x06) +
		(READ_VIRTUAL_32BIT_REG(0x02) <<0x00) + i->displ32u;
}

	void
BX_CPU_C::Resolve32Mod1or2EffectAddress_sib0x17(BX_CPU_C *icpu,bxInstruction_c *i)
{
	RMAddr(i) = READ_VIRTUAL_32BIT_REG(0x07) +
		(READ_VIRTUAL_32BIT_REG(0x02) <<0x00) + i->displ32u;
}

	void
BX_CPU_C::Resolve32Mod1or2EffectAddress_sib0x18(BX_CPU_C *icpu,bxInstruction_c *i)
{
	RMAddr(i) = READ_VIRTUAL_32BIT_REG(0x00) +
		(READ_VIRTUAL_32BIT_REG(0x03) <<0x00) + i->displ32u;
}

	void
BX_CPU_C::Resolve32Mod1or2EffectAddress_sib0x19(BX_CPU_C *icpu,bxInstruction_c *i)
{
	RMAddr(i) = READ_VIRTUAL_32BIT_REG(0x01) +
		(READ_VIRTUAL_32BIT_REG(0x03) <<0x00) + i->displ32u;
}

	void
BX_CPU_C::Resolve32Mod1or2EffectAddress_sib0x1a(BX_CPU_C *icpu,bxInstruction_c *i)
{
	RMAddr(i) = READ_VIRTUAL_32BIT_REG(0x02) +
		(READ_VIRTUAL_32BIT_REG(0x03) <<0x00) + i->displ32u;
}

	void
BX_CPU_C::Resolve32Mod1or2EffectAddress_sib0x1b(BX_CPU_C *icpu,bxInstruction_c *i)
{
	RMAddr(i) = READ_VIRTUAL_32BIT_REG(0x03) +
		(READ_VIRTUAL_32BIT_REG(0x03) <<0x00) + i->displ32u;
}

	void
BX_CPU_C::Resolve32Mod1or2EffectAddress_sib0x1c(BX_CPU_C *icpu,bxInstruction_c *i)
{
	RMAddr(i) = READ_VIRTUAL_32BIT_REG(0x04) +
		(READ_VIRTUAL_32BIT_REG(0x03) <<0x00) + i->displ32u;
}

	void
BX_CPU_C::Resolve32Mod1or2EffectAddress_sib0x1d(BX_CPU_C *icpu,bxInstruction_c *i)
{
	RMAddr(i) = READ_VIRTUAL_32BIT_REG(0x05) +
		(READ_VIRTUAL_32BIT_REG(0x03) <<0x00) + i->displ32u;
}

	void
BX_CPU_C::Resolve32Mod1or2EffectAddress_sib0x1e(BX_CPU_C *icpu,bxInstruction_c *i)
{
	RMAddr(i) = READ_VIRTUAL_32BIT_REG(0x06) +
		(READ_VIRTUAL_32BIT_REG(0x03) <<0x00) + i->displ32u;
}

	void
BX_CPU_C::Resolve32Mod1or2EffectAddress_sib0x1f(BX_CPU_C *icpu,bxInstruction_c *i)
{
	RMAddr(i) = READ_VIRTUAL_32BIT_REG(0x07) +
		(READ_VIRTUAL_32BIT_REG(0x03) <<0x00) + i->displ32u;
}

	void
BX_CPU_C::Resolve32Mod1or2EffectAddress_sib0x20(BX_CPU_C *icpu,bxInstruction_c *i)
{
	RMAddr(i) = READ_VIRTUAL_32BIT_REG(0x00) + i->displ32u;
}

	void
BX_CPU_C::Resolve32Mod1or2EffectAddress_sib0x21(BX_CPU_C *icpu,bxInstruction_c *i)
{
	RMAddr(i) = READ_VIRTUAL_32BIT_REG(0x01) + i->displ32u;
}

	void
BX_CPU_C::Resolve32Mod1or2EffectAddress_sib0x22(BX_CPU_C *icpu,bxInstruction_c *i)
{
	RMAddr(i) = READ_VIRTUAL_32BIT_REG(0x02) + i->displ32u;
}

	void
BX_CPU_C::Resolve32Mod1or2EffectAddress_sib0x23(BX_CPU_C *icpu,bxInstruction_c *i)
{
	RMAddr(i) = READ_VIRTUAL_32BIT_REG(0x03) + i->displ32u;
}

	void
BX_CPU_C::Resolve32Mod1or2EffectAddress_sib0x24(BX_CPU_C *icpu,bxInstruction_c *i)
{
	RMAddr(i) = READ_VIRTUAL_32BIT_REG(0x04) + i->displ32u;
}

	void
BX_CPU_C::Resolve32Mod1or2EffectAddress_sib0x25(BX_CPU_C *icpu,bxInstruction_c *i)
{
	RMAddr(i) = READ_VIRTUAL_32BIT_REG(0x05) + i->displ32u;
}

	void
BX_CPU_C::Resolve32Mod1or2EffectAddress_sib0x26(BX_CPU_C *icpu,bxInstruction_c *i)
{
	RMAddr(i) = READ_VIRTUAL_32BIT_REG(0x06) + i->displ32u;
}

	void
BX_CPU_C::Resolve32Mod1or2EffectAddress_sib0x27(BX_CPU_C *icpu,bxInstruction_c *i)
{
	RMAddr(i) = READ_VIRTUAL_32BIT_REG(0x07) + i->displ32u;
}

	void
BX_CPU_C::Resolve32Mod1or2EffectAddress_sib0x28(BX_CPU_C *icpu,bxInstruction_c *i)
{
	RMAddr(i) = READ_VIRTUAL_32BIT_REG(0x00) +
		(READ_VIRTUAL_32BIT_REG(0x05) <<0x00) + i->displ32u;
}

	void
BX_CPU_C::Resolve32Mod1or2EffectAddress_sib0x29(BX_CPU_C *icpu,bxInstruction_c *i)
{
	RMAddr(i) = READ_VIRTUAL_32BIT_REG(0x01) +
		(READ_VIRTUAL_32BIT_REG(0x05) <<0x00) + i->displ32u;
}

	void
BX_CPU_C::Resolve32Mod1or2EffectAddress_sib0x2a(BX_CPU_C *icpu,bxInstruction_c *i)
{
	RMAddr(i) = READ_VIRTUAL_32BIT_REG(0x02) +
		(READ_VIRTUAL_32BIT_REG(0x05) <<0x00) + i->displ32u;
}

	void
BX_CPU_C::Resolve32Mod1or2EffectAddress_sib0x2b(BX_CPU_C *icpu,bxInstruction_c *i)
{
	RMAddr(i) = READ_VIRTUAL_32BIT_REG(0x03) +
		(READ_VIRTUAL_32BIT_REG(0x05) <<0x00) + i->displ32u;
}

	void
BX_CPU_C::Resolve32Mod1or2EffectAddress_sib0x2c(BX_CPU_C *icpu,bxInstruction_c *i)
{
	RMAddr(i) = READ_VIRTUAL_32BIT_REG(0x04) +
		(READ_VIRTUAL_32BIT_REG(0x05) <<0x00) + i->displ32u;
}

	void
BX_CPU_C::Resolve32Mod1or2EffectAddress_sib0x2d(BX_CPU_C *icpu,bxInstruction_c *i)
{
	RMAddr(i) = READ_VIRTUAL_32BIT_REG(0x05) +
		(READ_VIRTUAL_32BIT_REG(0x05) <<0x00) + i->displ32u;
}

	void
BX_CPU_C::Resolve32Mod1or2EffectAddress_sib0x2e(BX_CPU_C *icpu,bxInstruction_c *i)
{
	RMAddr(i) = READ_VIRTUAL_32BIT_REG(0x06) +
		(READ_VIRTUAL_32BIT_REG(0x05) <<0x00) + i->displ32u;
}

	void
BX_CPU_C::Resolve32Mod1or2EffectAddress_sib0x2f(BX_CPU_C *icpu,bxInstruction_c *i)
{
	RMAddr(i) = READ_VIRTUAL_32BIT_REG(0x07) +
		(READ_VIRTUAL_32BIT_REG(0x05) <<0x00) + i->displ32u;
}

	void
BX_CPU_C::Resolve32Mod1or2EffectAddress_sib0x30(BX_CPU_C *icpu,bxInstruction_c *i)
{
	RMAddr(i) = READ_VIRTUAL_32BIT_REG(0x00) +
		(READ_VIRTUAL_32BIT_REG(0x06) <<0x00) + i->displ32u;
}

	void
BX_CPU_C::Resolve32Mod1or2EffectAddress_sib0x31(BX_CPU_C *icpu,bxInstruction_c *i)
{
	RMAddr(i) = READ_VIRTUAL_32BIT_REG(0x01) +
		(READ_VIRTUAL_32BIT_REG(0x06) <<0x00) + i->displ32u;
}

	void
BX_CPU_C::Resolve32Mod1or2EffectAddress_sib0x32(BX_CPU_C *icpu,bxInstruction_c *i)
{
	RMAddr(i) = READ_VIRTUAL_32BIT_REG(0x02) +
		(READ_VIRTUAL_32BIT_REG(0x06) <<0x00) + i->displ32u;
}

	void
BX_CPU_C::Resolve32Mod1or2EffectAddress_sib0x33(BX_CPU_C *icpu,bxInstruction_c *i)
{
	RMAddr(i) = READ_VIRTUAL_32BIT_REG(0x03) +
		(READ_VIRTUAL_32BIT_REG(0x06) <<0x00) + i->displ32u;
}

	void
BX_CPU_C::Resolve32Mod1or2EffectAddress_sib0x34(BX_CPU_C *icpu,bxInstruction_c *i)
{
	RMAddr(i) = READ_VIRTUAL_32BIT_REG(0x04) +
		(READ_VIRTUAL_32BIT_REG(0x06) <<0x00) + i->displ32u;
}

	void
BX_CPU_C::Resolve32Mod1or2EffectAddress_sib0x35(BX_CPU_C *icpu,bxInstruction_c *i)
{
	RMAddr(i) = READ_VIRTUAL_32BIT_REG(0x05) +
		(READ_VIRTUAL_32BIT_REG(0x06) <<0x00) + i->displ32u;
}

	void
BX_CPU_C::Resolve32Mod1or2EffectAddress_sib0x36(BX_CPU_C *icpu,bxInstruction_c *i)
{
	RMAddr(i) = READ_VIRTUAL_32BIT_REG(0x06) +
		(READ_VIRTUAL_32BIT_REG(0x06) <<0x00) + i->displ32u;
}

	void
BX_CPU_C::Resolve32Mod1or2EffectAddress_sib0x37(BX_CPU_C *icpu,bxInstruction_c *i)
{
	RMAddr(i) = READ_VIRTUAL_32BIT_REG(0x07) +
		(READ_VIRTUAL_32BIT_REG(0x06) <<0x00) + i->displ32u;
}

	void
BX_CPU_C::Resolve32Mod1or2EffectAddress_sib0x38(BX_CPU_C *icpu,bxInstruction_c *i)
{
	RMAddr(i) = READ_VIRTUAL_32BIT_REG(0x00) +
		(READ_VIRTUAL_32BIT_REG(0x07) <<0x00) + i->displ32u;
}

	void
BX_CPU_C::Resolve32Mod1or2EffectAddress_sib0x39(BX_CPU_C *icpu,bxInstruction_c *i)
{
	RMAddr(i) = READ_VIRTUAL_32BIT_REG(0x01) +
		(READ_VIRTUAL_32BIT_REG(0x07) <<0x00) + i->displ32u;
}

	void
BX_CPU_C::Resolve32Mod1or2EffectAddress_sib0x3a(BX_CPU_C *icpu,bxInstruction_c *i)
{
	RMAddr(i) = READ_VIRTUAL_32BIT_REG(0x02) +
		(READ_VIRTUAL_32BIT_REG(0x07) <<0x00) + i->displ32u;
}

	void
BX_CPU_C::Resolve32Mod1or2EffectAddress_sib0x3b(BX_CPU_C *icpu,bxInstruction_c *i)
{
	RMAddr(i) = READ_VIRTUAL_32BIT_REG(0x03) +
		(READ_VIRTUAL_32BIT_REG(0x07) <<0x00) + i->displ32u;
}

	void
BX_CPU_C::Resolve32Mod1or2EffectAddress_sib0x3c(BX_CPU_C *icpu,bxInstruction_c *i)
{
	RMAddr(i) = READ_VIRTUAL_32BIT_REG(0x04) +
		(READ_VIRTUAL_32BIT_REG(0x07) <<0x00) + i->displ32u;
}

	void
BX_CPU_C::Resolve32Mod1or2EffectAddress_sib0x3d(BX_CPU_C *icpu,bxInstruction_c *i)
{
	RMAddr(i) = READ_VIRTUAL_32BIT_REG(0x05) +
		(READ_VIRTUAL_32BIT_REG(0x07) <<0x00) + i->displ32u;
}

	void
BX_CPU_C::Resolve32Mod1or2EffectAddress_sib0x3e(BX_CPU_C *icpu,bxInstruction_c *i)
{
	RMAddr(i) = READ_VIRTUAL_32BIT_REG(0x06) +
		(READ_VIRTUAL_32BIT_REG(0x07) <<0x00) + i->displ32u;
}

	void
BX_CPU_C::Resolve32Mod1or2EffectAddress_sib0x3f(BX_CPU_C *icpu,bxInstruction_c *i)
{
	RMAddr(i) = READ_VIRTUAL_32BIT_REG(0x07) +
		(READ_VIRTUAL_32BIT_REG(0x07) <<0x00) + i->displ32u;
}

	void
BX_CPU_C::Resolve32Mod1or2EffectAddress_sib0x40(BX_CPU_C *icpu,bxInstruction_c *i)
{
	RMAddr(i) = READ_VIRTUAL_32BIT_REG(0x00) +
		(READ_VIRTUAL_32BIT_REG(0x00) <<0x01) + i->displ32u;
}

	void
BX_CPU_C::Resolve32Mod1or2EffectAddress_sib0x41(BX_CPU_C *icpu,bxInstruction_c *i)
{
	RMAddr(i) = READ_VIRTUAL_32BIT_REG(0x01) +
		(READ_VIRTUAL_32BIT_REG(0x00) <<0x01) + i->displ32u;
}

	void
BX_CPU_C::Resolve32Mod1or2EffectAddress_sib0x42(BX_CPU_C *icpu,bxInstruction_c *i)
{
	RMAddr(i) = READ_VIRTUAL_32BIT_REG(0x02) +
		(READ_VIRTUAL_32BIT_REG(0x00) <<0x01) + i->displ32u;
}

	void
BX_CPU_C::Resolve32Mod1or2EffectAddress_sib0x43(BX_CPU_C *icpu,bxInstruction_c *i)
{
	RMAddr(i) = READ_VIRTUAL_32BIT_REG(0x03) +
		(READ_VIRTUAL_32BIT_REG(0x00) <<0x01) + i->displ32u;
}

	void
BX_CPU_C::Resolve32Mod1or2EffectAddress_sib0x44(BX_CPU_C *icpu,bxInstruction_c *i)
{
	RMAddr(i) = READ_VIRTUAL_32BIT_REG(0x04) +
		(READ_VIRTUAL_32BIT_REG(0x00) <<0x01) + i->displ32u;
}

	void
BX_CPU_C::Resolve32Mod1or2EffectAddress_sib0x45(BX_CPU_C *icpu,bxInstruction_c *i)
{
	RMAddr(i) = READ_VIRTUAL_32BIT_REG(0x05) +
		(READ_VIRTUAL_32BIT_REG(0x00) <<0x01) + i->displ32u;
}

	void
BX_CPU_C::Resolve32Mod1or2EffectAddress_sib0x46(BX_CPU_C *icpu,bxInstruction_c *i)
{
	RMAddr(i) = READ_VIRTUAL_32BIT_REG(0x06) +
		(READ_VIRTUAL_32BIT_REG(0x00) <<0x01) + i->displ32u;
}

	void
BX_CPU_C::Resolve32Mod1or2EffectAddress_sib0x47(BX_CPU_C *icpu,bxInstruction_c *i)
{
	RMAddr(i) = READ_VIRTUAL_32BIT_REG(0x07) +
		(READ_VIRTUAL_32BIT_REG(0x00) <<0x01) + i->displ32u;
}

	void
BX_CPU_C::Resolve32Mod1or2EffectAddress_sib0x48(BX_CPU_C *icpu,bxInstruction_c *i)
{
	RMAddr(i) = READ_VIRTUAL_32BIT_REG(0x00) +
		(READ_VIRTUAL_32BIT_REG(0x01) <<0x01) + i->displ32u;
}

	void
BX_CPU_C::Resolve32Mod1or2EffectAddress_sib0x49(BX_CPU_C *icpu,bxInstruction_c *i)
{
	RMAddr(i) = READ_VIRTUAL_32BIT_REG(0x01) +
		(READ_VIRTUAL_32BIT_REG(0x01) <<0x01) + i->displ32u;
}

	void
BX_CPU_C::Resolve32Mod1or2EffectAddress_sib0x4a(BX_CPU_C *icpu,bxInstruction_c *i)
{
	RMAddr(i) = READ_VIRTUAL_32BIT_REG(0x02) +
		(READ_VIRTUAL_32BIT_REG(0x01) <<0x01) + i->displ32u;
}

	void
BX_CPU_C::Resolve32Mod1or2EffectAddress_sib0x4b(BX_CPU_C *icpu,bxInstruction_c *i)
{
	RMAddr(i) = READ_VIRTUAL_32BIT_REG(0x03) +
		(READ_VIRTUAL_32BIT_REG(0x01) <<0x01) + i->displ32u;
}

	void
BX_CPU_C::Resolve32Mod1or2EffectAddress_sib0x4c(BX_CPU_C *icpu,bxInstruction_c *i)
{
	RMAddr(i) = READ_VIRTUAL_32BIT_REG(0x04) +
		(READ_VIRTUAL_32BIT_REG(0x01) <<0x01) + i->displ32u;
}

	void
BX_CPU_C::Resolve32Mod1or2EffectAddress_sib0x4d(BX_CPU_C *icpu,bxInstruction_c *i)
{
	RMAddr(i) = READ_VIRTUAL_32BIT_REG(0x05) +
		(READ_VIRTUAL_32BIT_REG(0x01) <<0x01) + i->displ32u;
}

	void
BX_CPU_C::Resolve32Mod1or2EffectAddress_sib0x4e(BX_CPU_C *icpu,bxInstruction_c *i)
{
	RMAddr(i) = READ_VIRTUAL_32BIT_REG(0x06) +
		(READ_VIRTUAL_32BIT_REG(0x01) <<0x01) + i->displ32u;
}

	void
BX_CPU_C::Resolve32Mod1or2EffectAddress_sib0x4f(BX_CPU_C *icpu,bxInstruction_c *i)
{
	RMAddr(i) = READ_VIRTUAL_32BIT_REG(0x07) +
		(READ_VIRTUAL_32BIT_REG(0x01) <<0x01) + i->displ32u;
}

	void
BX_CPU_C::Resolve32Mod1or2EffectAddress_sib0x50(BX_CPU_C *icpu,bxInstruction_c *i)
{
	RMAddr(i) = READ_VIRTUAL_32BIT_REG(0x00) +
		(READ_VIRTUAL_32BIT_REG(0x02) <<0x01) + i->displ32u;
}

	void
BX_CPU_C::Resolve32Mod1or2EffectAddress_sib0x51(BX_CPU_C *icpu,bxInstruction_c *i)
{
	RMAddr(i) = READ_VIRTUAL_32BIT_REG(0x01) +
		(READ_VIRTUAL_32BIT_REG(0x02) <<0x01) + i->displ32u;
}

	void
BX_CPU_C::Resolve32Mod1or2EffectAddress_sib0x52(BX_CPU_C *icpu,bxInstruction_c *i)
{
	RMAddr(i) = READ_VIRTUAL_32BIT_REG(0x02) +
		(READ_VIRTUAL_32BIT_REG(0x02) <<0x01) + i->displ32u;
}

	void
BX_CPU_C::Resolve32Mod1or2EffectAddress_sib0x53(BX_CPU_C *icpu,bxInstruction_c *i)
{
	RMAddr(i) = READ_VIRTUAL_32BIT_REG(0x03) +
		(READ_VIRTUAL_32BIT_REG(0x02) <<0x01) + i->displ32u;
}

	void
BX_CPU_C::Resolve32Mod1or2EffectAddress_sib0x54(BX_CPU_C *icpu,bxInstruction_c *i)
{
	RMAddr(i) = READ_VIRTUAL_32BIT_REG(0x04) +
		(READ_VIRTUAL_32BIT_REG(0x02) <<0x01) + i->displ32u;
}

	void
BX_CPU_C::Resolve32Mod1or2EffectAddress_sib0x55(BX_CPU_C *icpu,bxInstruction_c *i)
{
	RMAddr(i) = READ_VIRTUAL_32BIT_REG(0x05) +
		(READ_VIRTUAL_32BIT_REG(0x02) <<0x01) + i->displ32u;
}

	void
BX_CPU_C::Resolve32Mod1or2EffectAddress_sib0x56(BX_CPU_C *icpu,bxInstruction_c *i)
{
	RMAddr(i) = READ_VIRTUAL_32BIT_REG(0x06) +
		(READ_VIRTUAL_32BIT_REG(0x02) <<0x01) + i->displ32u;
}

	void
BX_CPU_C::Resolve32Mod1or2EffectAddress_sib0x57(BX_CPU_C *icpu,bxInstruction_c *i)
{
	RMAddr(i) = READ_VIRTUAL_32BIT_REG(0x07) +
		(READ_VIRTUAL_32BIT_REG(0x02) <<0x01) + i->displ32u;
}

	void
BX_CPU_C::Resolve32Mod1or2EffectAddress_sib0x58(BX_CPU_C *icpu,bxInstruction_c *i)
{
	RMAddr(i) = READ_VIRTUAL_32BIT_REG(0x00) +
		(READ_VIRTUAL_32BIT_REG(0x03) <<0x01) + i->displ32u;
}

	void
BX_CPU_C::Resolve32Mod1or2EffectAddress_sib0x59(BX_CPU_C *icpu,bxInstruction_c *i)
{
	RMAddr(i) = READ_VIRTUAL_32BIT_REG(0x01) +
		(READ_VIRTUAL_32BIT_REG(0x03) <<0x01) + i->displ32u;
}

	void
BX_CPU_C::Resolve32Mod1or2EffectAddress_sib0x5a(BX_CPU_C *icpu,bxInstruction_c *i)
{
	RMAddr(i) = READ_VIRTUAL_32BIT_REG(0x02) +
		(READ_VIRTUAL_32BIT_REG(0x03) <<0x01) + i->displ32u;
}

	void
BX_CPU_C::Resolve32Mod1or2EffectAddress_sib0x5b(BX_CPU_C *icpu,bxInstruction_c *i)
{
	RMAddr(i) = READ_VIRTUAL_32BIT_REG(0x03) +
		(READ_VIRTUAL_32BIT_REG(0x03) <<0x01) + i->displ32u;
}

	void
BX_CPU_C::Resolve32Mod1or2EffectAddress_sib0x5c(BX_CPU_C *icpu,bxInstruction_c *i)
{
	RMAddr(i) = READ_VIRTUAL_32BIT_REG(0x04) +
		(READ_VIRTUAL_32BIT_REG(0x03) <<0x01) + i->displ32u;
}

	void
BX_CPU_C::Resolve32Mod1or2EffectAddress_sib0x5d(BX_CPU_C *icpu,bxInstruction_c *i)
{
	RMAddr(i) = READ_VIRTUAL_32BIT_REG(0x05) +
		(READ_VIRTUAL_32BIT_REG(0x03) <<0x01) + i->displ32u;
}

	void
BX_CPU_C::Resolve32Mod1or2EffectAddress_sib0x5e(BX_CPU_C *icpu,bxInstruction_c *i)
{
	RMAddr(i) = READ_VIRTUAL_32BIT_REG(0x06) +
		(READ_VIRTUAL_32BIT_REG(0x03) <<0x01) + i->displ32u;
}

	void
BX_CPU_C::Resolve32Mod1or2EffectAddress_sib0x5f(BX_CPU_C *icpu,bxInstruction_c *i)
{
	RMAddr(i) = READ_VIRTUAL_32BIT_REG(0x07) +
		(READ_VIRTUAL_32BIT_REG(0x03) <<0x01) + i->displ32u;
}

	void
BX_CPU_C::Resolve32Mod1or2EffectAddress_sib0x60(BX_CPU_C *icpu,bxInstruction_c *i)
{
	RMAddr(i) = READ_VIRTUAL_32BIT_REG(0x00) + i->displ32u;
}

	void
BX_CPU_C::Resolve32Mod1or2EffectAddress_sib0x61(BX_CPU_C *icpu,bxInstruction_c *i)
{
	RMAddr(i) = READ_VIRTUAL_32BIT_REG(0x01) + i->displ32u;
}

	void
BX_CPU_C::Resolve32Mod1or2EffectAddress_sib0x62(BX_CPU_C *icpu,bxInstruction_c *i)
{
	RMAddr(i) = READ_VIRTUAL_32BIT_REG(0x02) + i->displ32u;
}

	void
BX_CPU_C::Resolve32Mod1or2EffectAddress_sib0x63(BX_CPU_C *icpu,bxInstruction_c *i)
{
	RMAddr(i) = READ_VIRTUAL_32BIT_REG(0x03) + i->displ32u;
}

	void
BX_CPU_C::Resolve32Mod1or2EffectAddress_sib0x64(BX_CPU_C *icpu,bxInstruction_c *i)
{
	RMAddr(i) = READ_VIRTUAL_32BIT_REG(0x04) + i->displ32u;
}

	void
BX_CPU_C::Resolve32Mod1or2EffectAddress_sib0x65(BX_CPU_C *icpu,bxInstruction_c *i)
{
	RMAddr(i) = READ_VIRTUAL_32BIT_REG(0x05) + i->displ32u;
}

	void
BX_CPU_C::Resolve32Mod1or2EffectAddress_sib0x66(BX_CPU_C *icpu,bxInstruction_c *i)
{
	RMAddr(i) = READ_VIRTUAL_32BIT_REG(0x06) + i->displ32u;
}

	void
BX_CPU_C::Resolve32Mod1or2EffectAddress_sib0x67(BX_CPU_C *icpu,bxInstruction_c *i)
{
	RMAddr(i) = READ_VIRTUAL_32BIT_REG(0x07) + i->displ32u;
}

	void
BX_CPU_C::Resolve32Mod1or2EffectAddress_sib0x68(BX_CPU_C *icpu,bxInstruction_c *i)
{
	RMAddr(i) = READ_VIRTUAL_32BIT_REG(0x00) +
		(READ_VIRTUAL_32BIT_REG(0x05) <<0x01) + i->displ32u;
}

	void
BX_CPU_C::Resolve32Mod1or2EffectAddress_sib0x69(BX_CPU_C *icpu,bxInstruction_c *i)
{
	RMAddr(i) = READ_VIRTUAL_32BIT_REG(0x01) +
		(READ_VIRTUAL_32BIT_REG(0x05) <<0x01) + i->displ32u;
}

	void
BX_CPU_C::Resolve32Mod1or2EffectAddress_sib0x6a(BX_CPU_C *icpu,bxInstruction_c *i)
{
	RMAddr(i) = READ_VIRTUAL_32BIT_REG(0x02) +
		(READ_VIRTUAL_32BIT_REG(0x05) <<0x01) + i->displ32u;
}

	void
BX_CPU_C::Resolve32Mod1or2EffectAddress_sib0x6b(BX_CPU_C *icpu,bxInstruction_c *i)
{
	RMAddr(i) = READ_VIRTUAL_32BIT_REG(0x03) +
		(READ_VIRTUAL_32BIT_REG(0x05) <<0x01) + i->displ32u;
}

	void
BX_CPU_C::Resolve32Mod1or2EffectAddress_sib0x6c(BX_CPU_C *icpu,bxInstruction_c *i)
{
	RMAddr(i) = READ_VIRTUAL_32BIT_REG(0x04) +
		(READ_VIRTUAL_32BIT_REG(0x05) <<0x01) + i->displ32u;
}

	void
BX_CPU_C::Resolve32Mod1or2EffectAddress_sib0x6d(BX_CPU_C *icpu,bxInstruction_c *i)
{
	RMAddr(i) = READ_VIRTUAL_32BIT_REG(0x05) +
		(READ_VIRTUAL_32BIT_REG(0x05) <<0x01) + i->displ32u;
}

	void
BX_CPU_C::Resolve32Mod1or2EffectAddress_sib0x6e(BX_CPU_C *icpu,bxInstruction_c *i)
{
	RMAddr(i) = READ_VIRTUAL_32BIT_REG(0x06) +
		(READ_VIRTUAL_32BIT_REG(0x05) <<0x01) + i->displ32u;
}

	void
BX_CPU_C::Resolve32Mod1or2EffectAddress_sib0x6f(BX_CPU_C *icpu,bxInstruction_c *i)
{
	RMAddr(i) = READ_VIRTUAL_32BIT_REG(0x07) +
		(READ_VIRTUAL_32BIT_REG(0x05) <<0x01) + i->displ32u;
}

	void
BX_CPU_C::Resolve32Mod1or2EffectAddress_sib0x70(BX_CPU_C *icpu,bxInstruction_c *i)
{
	RMAddr(i) = READ_VIRTUAL_32BIT_REG(0x00) +
		(READ_VIRTUAL_32BIT_REG(0x06) <<0x01) + i->displ32u;
}

	void
BX_CPU_C::Resolve32Mod1or2EffectAddress_sib0x71(BX_CPU_C *icpu,bxInstruction_c *i)
{
	RMAddr(i) = READ_VIRTUAL_32BIT_REG(0x01) +
		(READ_VIRTUAL_32BIT_REG(0x06) <<0x01) + i->displ32u;
}

	void
BX_CPU_C::Resolve32Mod1or2EffectAddress_sib0x72(BX_CPU_C *icpu,bxInstruction_c *i)
{
	RMAddr(i) = READ_VIRTUAL_32BIT_REG(0x02) +
		(READ_VIRTUAL_32BIT_REG(0x06) <<0x01) + i->displ32u;
}

	void
BX_CPU_C::Resolve32Mod1or2EffectAddress_sib0x73(BX_CPU_C *icpu,bxInstruction_c *i)
{
	RMAddr(i) = READ_VIRTUAL_32BIT_REG(0x03) +
		(READ_VIRTUAL_32BIT_REG(0x06) <<0x01) + i->displ32u;
}

	void
BX_CPU_C::Resolve32Mod1or2EffectAddress_sib0x74(BX_CPU_C *icpu,bxInstruction_c *i)
{
	RMAddr(i) = READ_VIRTUAL_32BIT_REG(0x04) +
		(READ_VIRTUAL_32BIT_REG(0x06) <<0x01) + i->displ32u;
}

	void
BX_CPU_C::Resolve32Mod1or2EffectAddress_sib0x75(BX_CPU_C *icpu,bxInstruction_c *i)
{
	RMAddr(i) = READ_VIRTUAL_32BIT_REG(0x05) +
		(READ_VIRTUAL_32BIT_REG(0x06) <<0x01) + i->displ32u;
}

	void
BX_CPU_C::Resolve32Mod1or2EffectAddress_sib0x76(BX_CPU_C *icpu,bxInstruction_c *i)
{
	RMAddr(i) = READ_VIRTUAL_32BIT_REG(0x06) +
		(READ_VIRTUAL_32BIT_REG(0x06) <<0x01) + i->displ32u;
}

	void
BX_CPU_C::Resolve32Mod1or2EffectAddress_sib0x77(BX_CPU_C *icpu,bxInstruction_c *i)
{
	RMAddr(i) = READ_VIRTUAL_32BIT_REG(0x07) +
		(READ_VIRTUAL_32BIT_REG(0x06) <<0x01) + i->displ32u;
}

	void
BX_CPU_C::Resolve32Mod1or2EffectAddress_sib0x78(BX_CPU_C *icpu,bxInstruction_c *i)
{
	RMAddr(i) = READ_VIRTUAL_32BIT_REG(0x00) +
		(READ_VIRTUAL_32BIT_REG(0x07) <<0x01) + i->displ32u;
}

	void
BX_CPU_C::Resolve32Mod1or2EffectAddress_sib0x79(BX_CPU_C *icpu,bxInstruction_c *i)
{
	RMAddr(i) = READ_VIRTUAL_32BIT_REG(0x01) +
		(READ_VIRTUAL_32BIT_REG(0x07) <<0x01) + i->displ32u;
}

	void
BX_CPU_C::Resolve32Mod1or2EffectAddress_sib0x7a(BX_CPU_C *icpu,bxInstruction_c *i)
{
	RMAddr(i) = READ_VIRTUAL_32BIT_REG(0x02) +
		(READ_VIRTUAL_32BIT_REG(0x07) <<0x01) + i->displ32u;
}

	void
BX_CPU_C::Resolve32Mod1or2EffectAddress_sib0x7b(BX_CPU_C *icpu,bxInstruction_c *i)
{
	RMAddr(i) = READ_VIRTUAL_32BIT_REG(0x03) +
		(READ_VIRTUAL_32BIT_REG(0x07) <<0x01) + i->displ32u;
}

	void
BX_CPU_C::Resolve32Mod1or2EffectAddress_sib0x7c(BX_CPU_C *icpu,bxInstruction_c *i)
{
	RMAddr(i) = READ_VIRTUAL_32BIT_REG(0x04) +
		(READ_VIRTUAL_32BIT_REG(0x07) <<0x01) + i->displ32u;
}

	void
BX_CPU_C::Resolve32Mod1or2EffectAddress_sib0x7d(BX_CPU_C *icpu,bxInstruction_c *i)
{
	RMAddr(i) = READ_VIRTUAL_32BIT_REG(0x05) +
		(READ_VIRTUAL_32BIT_REG(0x07) <<0x01) + i->displ32u;
}

	void
BX_CPU_C::Resolve32Mod1or2EffectAddress_sib0x7e(BX_CPU_C *icpu,bxInstruction_c *i)
{
	RMAddr(i) = READ_VIRTUAL_32BIT_REG(0x06) +
		(READ_VIRTUAL_32BIT_REG(0x07) <<0x01) + i->displ32u;
}

	void
BX_CPU_C::Resolve32Mod1or2EffectAddress_sib0x7f(BX_CPU_C *icpu,bxInstruction_c *i)
{
	RMAddr(i) = READ_VIRTUAL_32BIT_REG(0x07) +
		(READ_VIRTUAL_32BIT_REG(0x07) <<0x01) + i->displ32u;
}

	void
BX_CPU_C::Resolve32Mod1or2EffectAddress_sib0x80(BX_CPU_C *icpu,bxInstruction_c *i)
{
	RMAddr(i) = READ_VIRTUAL_32BIT_REG(0x00) +
		(READ_VIRTUAL_32BIT_REG(0x00) <<0x02) + i->displ32u;
}

	void
BX_CPU_C::Resolve32Mod1or2EffectAddress_sib0x81(BX_CPU_C *icpu,bxInstruction_c *i)
{
	RMAddr(i) = READ_VIRTUAL_32BIT_REG(0x01) +
		(READ_VIRTUAL_32BIT_REG(0x00) <<0x02) + i->displ32u;
}

	void
BX_CPU_C::Resolve32Mod1or2EffectAddress_sib0x82(BX_CPU_C *icpu,bxInstruction_c *i)
{
	RMAddr(i) = READ_VIRTUAL_32BIT_REG(0x02) +
		(READ_VIRTUAL_32BIT_REG(0x00) <<0x02) + i->displ32u;
}

	void
BX_CPU_C::Resolve32Mod1or2EffectAddress_sib0x83(BX_CPU_C *icpu,bxInstruction_c *i)
{
	RMAddr(i) = READ_VIRTUAL_32BIT_REG(0x03) +
		(READ_VIRTUAL_32BIT_REG(0x00) <<0x02) + i->displ32u;
}

	void
BX_CPU_C::Resolve32Mod1or2EffectAddress_sib0x84(BX_CPU_C *icpu,bxInstruction_c *i)
{
	RMAddr(i) = READ_VIRTUAL_32BIT_REG(0x04) +
		(READ_VIRTUAL_32BIT_REG(0x00) <<0x02) + i->displ32u;
}

	void
BX_CPU_C::Resolve32Mod1or2EffectAddress_sib0x85(BX_CPU_C *icpu,bxInstruction_c *i)
{
	RMAddr(i) = READ_VIRTUAL_32BIT_REG(0x05) +
		(READ_VIRTUAL_32BIT_REG(0x00) <<0x02) + i->displ32u;
}

	void
BX_CPU_C::Resolve32Mod1or2EffectAddress_sib0x86(BX_CPU_C *icpu,bxInstruction_c *i)
{
	RMAddr(i) = READ_VIRTUAL_32BIT_REG(0x06) +
		(READ_VIRTUAL_32BIT_REG(0x00) <<0x02) + i->displ32u;
}

	void
BX_CPU_C::Resolve32Mod1or2EffectAddress_sib0x87(BX_CPU_C *icpu,bxInstruction_c *i)
{
	RMAddr(i) = READ_VIRTUAL_32BIT_REG(0x07) +
		(READ_VIRTUAL_32BIT_REG(0x00) <<0x02) + i->displ32u;
}

	void
BX_CPU_C::Resolve32Mod1or2EffectAddress_sib0x88(BX_CPU_C *icpu,bxInstruction_c *i)
{
	RMAddr(i) = READ_VIRTUAL_32BIT_REG(0x00) +
		(READ_VIRTUAL_32BIT_REG(0x01) <<0x02) + i->displ32u;
}

	void
BX_CPU_C::Resolve32Mod1or2EffectAddress_sib0x89(BX_CPU_C *icpu,bxInstruction_c *i)
{
	RMAddr(i) = READ_VIRTUAL_32BIT_REG(0x01) +
		(READ_VIRTUAL_32BIT_REG(0x01) <<0x02) + i->displ32u;
}

	void
BX_CPU_C::Resolve32Mod1or2EffectAddress_sib0x8a(BX_CPU_C *icpu,bxInstruction_c *i)
{
	RMAddr(i) = READ_VIRTUAL_32BIT_REG(0x02) +
		(READ_VIRTUAL_32BIT_REG(0x01) <<0x02) + i->displ32u;
}

	void
BX_CPU_C::Resolve32Mod1or2EffectAddress_sib0x8b(BX_CPU_C *icpu,bxInstruction_c *i)
{
	RMAddr(i) = READ_VIRTUAL_32BIT_REG(0x03) +
		(READ_VIRTUAL_32BIT_REG(0x01) <<0x02) + i->displ32u;
}

	void
BX_CPU_C::Resolve32Mod1or2EffectAddress_sib0x8c(BX_CPU_C *icpu,bxInstruction_c *i)
{
	RMAddr(i) = READ_VIRTUAL_32BIT_REG(0x04) +
		(READ_VIRTUAL_32BIT_REG(0x01) <<0x02) + i->displ32u;
}

	void
BX_CPU_C::Resolve32Mod1or2EffectAddress_sib0x8d(BX_CPU_C *icpu,bxInstruction_c *i)
{
	RMAddr(i) = READ_VIRTUAL_32BIT_REG(0x05) +
		(READ_VIRTUAL_32BIT_REG(0x01) <<0x02) + i->displ32u;
}

	void
BX_CPU_C::Resolve32Mod1or2EffectAddress_sib0x8e(BX_CPU_C *icpu,bxInstruction_c *i)
{
	RMAddr(i) = READ_VIRTUAL_32BIT_REG(0x06) +
		(READ_VIRTUAL_32BIT_REG(0x01) <<0x02) + i->displ32u;
}

	void
BX_CPU_C::Resolve32Mod1or2EffectAddress_sib0x8f(BX_CPU_C *icpu,bxInstruction_c *i)
{
	RMAddr(i) = READ_VIRTUAL_32BIT_REG(0x07) +
		(READ_VIRTUAL_32BIT_REG(0x01) <<0x02) + i->displ32u;
}

	void
BX_CPU_C::Resolve32Mod1or2EffectAddress_sib0x90(BX_CPU_C *icpu,bxInstruction_c *i)
{
	RMAddr(i) = READ_VIRTUAL_32BIT_REG(0x00) +
		(READ_VIRTUAL_32BIT_REG(0x02) <<0x02) + i->displ32u;
}

	void
BX_CPU_C::Resolve32Mod1or2EffectAddress_sib0x91(BX_CPU_C *icpu,bxInstruction_c *i)
{
	RMAddr(i) = READ_VIRTUAL_32BIT_REG(0x01) +
		(READ_VIRTUAL_32BIT_REG(0x02) <<0x02) + i->displ32u;
}

	void
BX_CPU_C::Resolve32Mod1or2EffectAddress_sib0x92(BX_CPU_C *icpu,bxInstruction_c *i)
{
	RMAddr(i) = READ_VIRTUAL_32BIT_REG(0x02) +
		(READ_VIRTUAL_32BIT_REG(0x02) <<0x02) + i->displ32u;
}

	void
BX_CPU_C::Resolve32Mod1or2EffectAddress_sib0x93(BX_CPU_C *icpu,bxInstruction_c *i)
{
	RMAddr(i) = READ_VIRTUAL_32BIT_REG(0x03) +
		(READ_VIRTUAL_32BIT_REG(0x02) <<0x02) + i->displ32u;
}

	void
BX_CPU_C::Resolve32Mod1or2EffectAddress_sib0x94(BX_CPU_C *icpu,bxInstruction_c *i)
{
	RMAddr(i) = READ_VIRTUAL_32BIT_REG(0x04) +
		(READ_VIRTUAL_32BIT_REG(0x02) <<0x02) + i->displ32u;
}

	void
BX_CPU_C::Resolve32Mod1or2EffectAddress_sib0x95(BX_CPU_C *icpu,bxInstruction_c *i)
{
	RMAddr(i) = READ_VIRTUAL_32BIT_REG(0x05) +
		(READ_VIRTUAL_32BIT_REG(0x02) <<0x02) + i->displ32u;
}

	void
BX_CPU_C::Resolve32Mod1or2EffectAddress_sib0x96(BX_CPU_C *icpu,bxInstruction_c *i)
{
	RMAddr(i) = READ_VIRTUAL_32BIT_REG(0x06) +
		(READ_VIRTUAL_32BIT_REG(0x02) <<0x02) + i->displ32u;
}

	void
BX_CPU_C::Resolve32Mod1or2EffectAddress_sib0x97(BX_CPU_C *icpu,bxInstruction_c *i)
{
	RMAddr(i) = READ_VIRTUAL_32BIT_REG(0x07) +
		(READ_VIRTUAL_32BIT_REG(0x02) <<0x02) + i->displ32u;
}

	void
BX_CPU_C::Resolve32Mod1or2EffectAddress_sib0x98(BX_CPU_C *icpu,bxInstruction_c *i)
{
	RMAddr(i) = READ_VIRTUAL_32BIT_REG(0x00) +
		(READ_VIRTUAL_32BIT_REG(0x03) <<0x02) + i->displ32u;
}

	void
BX_CPU_C::Resolve32Mod1or2EffectAddress_sib0x99(BX_CPU_C *icpu,bxInstruction_c *i)
{
	RMAddr(i) = READ_VIRTUAL_32BIT_REG(0x01) +
		(READ_VIRTUAL_32BIT_REG(0x03) <<0x02) + i->displ32u;
}

	void
BX_CPU_C::Resolve32Mod1or2EffectAddress_sib0x9a(BX_CPU_C *icpu,bxInstruction_c *i)
{
	RMAddr(i) = READ_VIRTUAL_32BIT_REG(0x02) +
		(READ_VIRTUAL_32BIT_REG(0x03) <<0x02) + i->displ32u;
}

	void
BX_CPU_C::Resolve32Mod1or2EffectAddress_sib0x9b(BX_CPU_C *icpu,bxInstruction_c *i)
{
	RMAddr(i) = READ_VIRTUAL_32BIT_REG(0x03) +
		(READ_VIRTUAL_32BIT_REG(0x03) <<0x02) + i->displ32u;
}

	void
BX_CPU_C::Resolve32Mod1or2EffectAddress_sib0x9c(BX_CPU_C *icpu,bxInstruction_c *i)
{
	RMAddr(i) = READ_VIRTUAL_32BIT_REG(0x04) +
		(READ_VIRTUAL_32BIT_REG(0x03) <<0x02) + i->displ32u;
}

	void
BX_CPU_C::Resolve32Mod1or2EffectAddress_sib0x9d(BX_CPU_C *icpu,bxInstruction_c *i)
{
	RMAddr(i) = READ_VIRTUAL_32BIT_REG(0x05) +
		(READ_VIRTUAL_32BIT_REG(0x03) <<0x02) + i->displ32u;
}

	void
BX_CPU_C::Resolve32Mod1or2EffectAddress_sib0x9e(BX_CPU_C *icpu,bxInstruction_c *i)
{
	RMAddr(i) = READ_VIRTUAL_32BIT_REG(0x06) +
		(READ_VIRTUAL_32BIT_REG(0x03) <<0x02) + i->displ32u;
}

	void
BX_CPU_C::Resolve32Mod1or2EffectAddress_sib0x9f(BX_CPU_C *icpu,bxInstruction_c *i)
{
	RMAddr(i) = READ_VIRTUAL_32BIT_REG(0x07) +
		(READ_VIRTUAL_32BIT_REG(0x03) <<0x02) + i->displ32u;
}

	void
BX_CPU_C::Resolve32Mod1or2EffectAddress_sib0xa0(BX_CPU_C *icpu,bxInstruction_c *i)
{
	RMAddr(i) = READ_VIRTUAL_32BIT_REG(0x00) + i->displ32u;
}

	void
BX_CPU_C::Resolve32Mod1or2EffectAddress_sib0xa1(BX_CPU_C *icpu,bxInstruction_c *i)
{
	RMAddr(i) = READ_VIRTUAL_32BIT_REG(0x01) + i->displ32u;
}

	void
BX_CPU_C::Resolve32Mod1or2EffectAddress_sib0xa2(BX_CPU_C *icpu,bxInstruction_c *i)
{
	RMAddr(i) = READ_VIRTUAL_32BIT_REG(0x02) + i->displ32u;
}

	void
BX_CPU_C::Resolve32Mod1or2EffectAddress_sib0xa3(BX_CPU_C *icpu,bxInstruction_c *i)
{
	RMAddr(i) = READ_VIRTUAL_32BIT_REG(0x03) + i->displ32u;
}

	void
BX_CPU_C::Resolve32Mod1or2EffectAddress_sib0xa4(BX_CPU_C *icpu,bxInstruction_c *i)
{
	RMAddr(i) = READ_VIRTUAL_32BIT_REG(0x04) + i->displ32u;
}

	void
BX_CPU_C::Resolve32Mod1or2EffectAddress_sib0xa5(BX_CPU_C *icpu,bxInstruction_c *i)
{
	RMAddr(i) = READ_VIRTUAL_32BIT_REG(0x05) + i->displ32u;
}

	void
BX_CPU_C::Resolve32Mod1or2EffectAddress_sib0xa6(BX_CPU_C *icpu,bxInstruction_c *i)
{
	RMAddr(i) = READ_VIRTUAL_32BIT_REG(0x06) + i->displ32u;
}

	void
BX_CPU_C::Resolve32Mod1or2EffectAddress_sib0xa7(BX_CPU_C *icpu,bxInstruction_c *i)
{
	RMAddr(i) = READ_VIRTUAL_32BIT_REG(0x07) + i->displ32u;
}

	void
BX_CPU_C::Resolve32Mod1or2EffectAddress_sib0xa8(BX_CPU_C *icpu,bxInstruction_c *i)
{
	RMAddr(i) = READ_VIRTUAL_32BIT_REG(0x00) +
		(READ_VIRTUAL_32BIT_REG(0x05) <<0x02) + i->displ32u;
}

	void
BX_CPU_C::Resolve32Mod1or2EffectAddress_sib0xa9(BX_CPU_C *icpu,bxInstruction_c *i)
{
	RMAddr(i) = READ_VIRTUAL_32BIT_REG(0x01) +
		(READ_VIRTUAL_32BIT_REG(0x05) <<0x02) + i->displ32u;
}

	void
BX_CPU_C::Resolve32Mod1or2EffectAddress_sib0xaa(BX_CPU_C *icpu,bxInstruction_c *i)
{
	RMAddr(i) = READ_VIRTUAL_32BIT_REG(0x02) +
		(READ_VIRTUAL_32BIT_REG(0x05) <<0x02) + i->displ32u;
}

	void
BX_CPU_C::Resolve32Mod1or2EffectAddress_sib0xab(BX_CPU_C *icpu,bxInstruction_c *i)
{
	RMAddr(i) = READ_VIRTUAL_32BIT_REG(0x03) +
		(READ_VIRTUAL_32BIT_REG(0x05) <<0x02) + i->displ32u;
}

	void
BX_CPU_C::Resolve32Mod1or2EffectAddress_sib0xac(BX_CPU_C *icpu,bxInstruction_c *i)
{
	RMAddr(i) = READ_VIRTUAL_32BIT_REG(0x04) +
		(READ_VIRTUAL_32BIT_REG(0x05) <<0x02) + i->displ32u;
}

	void
BX_CPU_C::Resolve32Mod1or2EffectAddress_sib0xad(BX_CPU_C *icpu,bxInstruction_c *i)
{
	RMAddr(i) = READ_VIRTUAL_32BIT_REG(0x05) +
		(READ_VIRTUAL_32BIT_REG(0x05) <<0x02) + i->displ32u;
}

	void
BX_CPU_C::Resolve32Mod1or2EffectAddress_sib0xae(BX_CPU_C *icpu,bxInstruction_c *i)
{
	RMAddr(i) = READ_VIRTUAL_32BIT_REG(0x06) +
		(READ_VIRTUAL_32BIT_REG(0x05) <<0x02) + i->displ32u;
}

	void
BX_CPU_C::Resolve32Mod1or2EffectAddress_sib0xaf(BX_CPU_C *icpu,bxInstruction_c *i)
{
	RMAddr(i) = READ_VIRTUAL_32BIT_REG(0x07) +
		(READ_VIRTUAL_32BIT_REG(0x05) <<0x02) + i->displ32u;
}

	void
BX_CPU_C::Resolve32Mod1or2EffectAddress_sib0xb0(BX_CPU_C *icpu,bxInstruction_c *i)
{
	RMAddr(i) = READ_VIRTUAL_32BIT_REG(0x00) +
		(READ_VIRTUAL_32BIT_REG(0x06) <<0x02) + i->displ32u;
}

	void
BX_CPU_C::Resolve32Mod1or2EffectAddress_sib0xb1(BX_CPU_C *icpu,bxInstruction_c *i)
{
	RMAddr(i) = READ_VIRTUAL_32BIT_REG(0x01) +
		(READ_VIRTUAL_32BIT_REG(0x06) <<0x02) + i->displ32u;
}

	void
BX_CPU_C::Resolve32Mod1or2EffectAddress_sib0xb2(BX_CPU_C *icpu,bxInstruction_c *i)
{
	RMAddr(i) = READ_VIRTUAL_32BIT_REG(0x02) +
		(READ_VIRTUAL_32BIT_REG(0x06) <<0x02) + i->displ32u;
}

	void
BX_CPU_C::Resolve32Mod1or2EffectAddress_sib0xb3(BX_CPU_C *icpu,bxInstruction_c *i)
{
	RMAddr(i) = READ_VIRTUAL_32BIT_REG(0x03) +
		(READ_VIRTUAL_32BIT_REG(0x06) <<0x02) + i->displ32u;
}

	void
BX_CPU_C::Resolve32Mod1or2EffectAddress_sib0xb4(BX_CPU_C *icpu,bxInstruction_c *i)
{
	RMAddr(i) = READ_VIRTUAL_32BIT_REG(0x04) +
		(READ_VIRTUAL_32BIT_REG(0x06) <<0x02) + i->displ32u;
}

	void
BX_CPU_C::Resolve32Mod1or2EffectAddress_sib0xb5(BX_CPU_C *icpu,bxInstruction_c *i)
{
	RMAddr(i) = READ_VIRTUAL_32BIT_REG(0x05) +
		(READ_VIRTUAL_32BIT_REG(0x06) <<0x02) + i->displ32u;
}

	void
BX_CPU_C::Resolve32Mod1or2EffectAddress_sib0xb6(BX_CPU_C *icpu,bxInstruction_c *i)
{
	RMAddr(i) = READ_VIRTUAL_32BIT_REG(0x06) +
		(READ_VIRTUAL_32BIT_REG(0x06) <<0x02) + i->displ32u;
}

	void
BX_CPU_C::Resolve32Mod1or2EffectAddress_sib0xb7(BX_CPU_C *icpu,bxInstruction_c *i)
{
	RMAddr(i) = READ_VIRTUAL_32BIT_REG(0x07) +
		(READ_VIRTUAL_32BIT_REG(0x06) <<0x02) + i->displ32u;
}

	void
BX_CPU_C::Resolve32Mod1or2EffectAddress_sib0xb8(BX_CPU_C *icpu,bxInstruction_c *i)
{
	RMAddr(i) = READ_VIRTUAL_32BIT_REG(0x00) +
		(READ_VIRTUAL_32BIT_REG(0x07) <<0x02) + i->displ32u;
}

	void
BX_CPU_C::Resolve32Mod1or2EffectAddress_sib0xb9(BX_CPU_C *icpu,bxInstruction_c *i)
{
	RMAddr(i) = READ_VIRTUAL_32BIT_REG(0x01) +
		(READ_VIRTUAL_32BIT_REG(0x07) <<0x02) + i->displ32u;
}

	void
BX_CPU_C::Resolve32Mod1or2EffectAddress_sib0xba(BX_CPU_C *icpu,bxInstruction_c *i)
{
	RMAddr(i) = READ_VIRTUAL_32BIT_REG(0x02) +
		(READ_VIRTUAL_32BIT_REG(0x07) <<0x02) + i->displ32u;
}

	void
BX_CPU_C::Resolve32Mod1or2EffectAddress_sib0xbb(BX_CPU_C *icpu,bxInstruction_c *i)
{
	RMAddr(i) = READ_VIRTUAL_32BIT_REG(0x03) +
		(READ_VIRTUAL_32BIT_REG(0x07) <<0x02) + i->displ32u;
}

	void
BX_CPU_C::Resolve32Mod1or2EffectAddress_sib0xbc(BX_CPU_C *icpu,bxInstruction_c *i)
{
	RMAddr(i) = READ_VIRTUAL_32BIT_REG(0x04) +
		(READ_VIRTUAL_32BIT_REG(0x07) <<0x02) + i->displ32u;
}

	void
BX_CPU_C::Resolve32Mod1or2EffectAddress_sib0xbd(BX_CPU_C *icpu,bxInstruction_c *i)
{
	RMAddr(i) = READ_VIRTUAL_32BIT_REG(0x05) +
		(READ_VIRTUAL_32BIT_REG(0x07) <<0x02) + i->displ32u;
}

	void
BX_CPU_C::Resolve32Mod1or2EffectAddress_sib0xbe(BX_CPU_C *icpu,bxInstruction_c *i)
{
	RMAddr(i) = READ_VIRTUAL_32BIT_REG(0x06) +
		(READ_VIRTUAL_32BIT_REG(0x07) <<0x02) + i->displ32u;
}

	void
BX_CPU_C::Resolve32Mod1or2EffectAddress_sib0xbf(BX_CPU_C *icpu,bxInstruction_c *i)
{
	RMAddr(i) = READ_VIRTUAL_32BIT_REG(0x07) +
		(READ_VIRTUAL_32BIT_REG(0x07) <<0x02) + i->displ32u;
}

	void
BX_CPU_C::Resolve32Mod1or2EffectAddress_sib0xc0(BX_CPU_C *icpu,bxInstruction_c *i)
{
	RMAddr(i) = READ_VIRTUAL_32BIT_REG(0x00) +
		(READ_VIRTUAL_32BIT_REG(0x00) <<0x03) + i->displ32u;
}

	void
BX_CPU_C::Resolve32Mod1or2EffectAddress_sib0xc1(BX_CPU_C *icpu,bxInstruction_c *i)
{
	RMAddr(i) = READ_VIRTUAL_32BIT_REG(0x01) +
		(READ_VIRTUAL_32BIT_REG(0x00) <<0x03) + i->displ32u;
}

	void
BX_CPU_C::Resolve32Mod1or2EffectAddress_sib0xc2(BX_CPU_C *icpu,bxInstruction_c *i)
{
	RMAddr(i) = READ_VIRTUAL_32BIT_REG(0x02) +
		(READ_VIRTUAL_32BIT_REG(0x00) <<0x03) + i->displ32u;
}

	void
BX_CPU_C::Resolve32Mod1or2EffectAddress_sib0xc3(BX_CPU_C *icpu,bxInstruction_c *i)
{
	RMAddr(i) = READ_VIRTUAL_32BIT_REG(0x03) +
		(READ_VIRTUAL_32BIT_REG(0x00) <<0x03) + i->displ32u;
}

	void
BX_CPU_C::Resolve32Mod1or2EffectAddress_sib0xc4(BX_CPU_C *icpu,bxInstruction_c *i)
{
	RMAddr(i) = READ_VIRTUAL_32BIT_REG(0x04) +
		(READ_VIRTUAL_32BIT_REG(0x00) <<0x03) + i->displ32u;
}

	void
BX_CPU_C::Resolve32Mod1or2EffectAddress_sib0xc5(BX_CPU_C *icpu,bxInstruction_c *i)
{
	RMAddr(i) = READ_VIRTUAL_32BIT_REG(0x05) +
		(READ_VIRTUAL_32BIT_REG(0x00) <<0x03) + i->displ32u;
}

	void
BX_CPU_C::Resolve32Mod1or2EffectAddress_sib0xc6(BX_CPU_C *icpu,bxInstruction_c *i)
{
	RMAddr(i) = READ_VIRTUAL_32BIT_REG(0x06) +
		(READ_VIRTUAL_32BIT_REG(0x00) <<0x03) + i->displ32u;
}

	void
BX_CPU_C::Resolve32Mod1or2EffectAddress_sib0xc7(BX_CPU_C *icpu,bxInstruction_c *i)
{
	RMAddr(i) = READ_VIRTUAL_32BIT_REG(0x07) +
		(READ_VIRTUAL_32BIT_REG(0x00) <<0x03) + i->displ32u;
}

	void
BX_CPU_C::Resolve32Mod1or2EffectAddress_sib0xc8(BX_CPU_C *icpu,bxInstruction_c *i)
{
	RMAddr(i) = READ_VIRTUAL_32BIT_REG(0x00) +
		(READ_VIRTUAL_32BIT_REG(0x01) <<0x03) + i->displ32u;
}

	void
BX_CPU_C::Resolve32Mod1or2EffectAddress_sib0xc9(BX_CPU_C *icpu,bxInstruction_c *i)
{
	RMAddr(i) = READ_VIRTUAL_32BIT_REG(0x01) +
		(READ_VIRTUAL_32BIT_REG(0x01) <<0x03) + i->displ32u;
}

	void
BX_CPU_C::Resolve32Mod1or2EffectAddress_sib0xca(BX_CPU_C *icpu,bxInstruction_c *i)
{
	RMAddr(i) = READ_VIRTUAL_32BIT_REG(0x02) +
		(READ_VIRTUAL_32BIT_REG(0x01) <<0x03) + i->displ32u;
}

	void
BX_CPU_C::Resolve32Mod1or2EffectAddress_sib0xcb(BX_CPU_C *icpu,bxInstruction_c *i)
{
	RMAddr(i) = READ_VIRTUAL_32BIT_REG(0x03) +
		(READ_VIRTUAL_32BIT_REG(0x01) <<0x03) + i->displ32u;
}

	void
BX_CPU_C::Resolve32Mod1or2EffectAddress_sib0xcc(BX_CPU_C *icpu,bxInstruction_c *i)
{
	RMAddr(i) = READ_VIRTUAL_32BIT_REG(0x04) +
		(READ_VIRTUAL_32BIT_REG(0x01) <<0x03) + i->displ32u;
}

	void
BX_CPU_C::Resolve32Mod1or2EffectAddress_sib0xcd(BX_CPU_C *icpu,bxInstruction_c *i)
{
	RMAddr(i) = READ_VIRTUAL_32BIT_REG(0x05) +
		(READ_VIRTUAL_32BIT_REG(0x01) <<0x03) + i->displ32u;
}

	void
BX_CPU_C::Resolve32Mod1or2EffectAddress_sib0xce(BX_CPU_C *icpu,bxInstruction_c *i)
{
	RMAddr(i) = READ_VIRTUAL_32BIT_REG(0x06) +
		(READ_VIRTUAL_32BIT_REG(0x01) <<0x03) + i->displ32u;
}

	void
BX_CPU_C::Resolve32Mod1or2EffectAddress_sib0xcf(BX_CPU_C *icpu,bxInstruction_c *i)
{
	RMAddr(i) = READ_VIRTUAL_32BIT_REG(0x07) +
		(READ_VIRTUAL_32BIT_REG(0x01) <<0x03) + i->displ32u;
}

	void
BX_CPU_C::Resolve32Mod1or2EffectAddress_sib0xd0(BX_CPU_C *icpu,bxInstruction_c *i)
{
	RMAddr(i) = READ_VIRTUAL_32BIT_REG(0x00) +
		(READ_VIRTUAL_32BIT_REG(0x02) <<0x03) + i->displ32u;
}

	void
BX_CPU_C::Resolve32Mod1or2EffectAddress_sib0xd1(BX_CPU_C *icpu,bxInstruction_c *i)
{
	RMAddr(i) = READ_VIRTUAL_32BIT_REG(0x01) +
		(READ_VIRTUAL_32BIT_REG(0x02) <<0x03) + i->displ32u;
}

	void
BX_CPU_C::Resolve32Mod1or2EffectAddress_sib0xd2(BX_CPU_C *icpu,bxInstruction_c *i)
{
	RMAddr(i) = READ_VIRTUAL_32BIT_REG(0x02) +
		(READ_VIRTUAL_32BIT_REG(0x02) <<0x03) + i->displ32u;
}

	void
BX_CPU_C::Resolve32Mod1or2EffectAddress_sib0xd3(BX_CPU_C *icpu,bxInstruction_c *i)
{
	RMAddr(i) = READ_VIRTUAL_32BIT_REG(0x03) +
		(READ_VIRTUAL_32BIT_REG(0x02) <<0x03) + i->displ32u;
}

	void
BX_CPU_C::Resolve32Mod1or2EffectAddress_sib0xd4(BX_CPU_C *icpu,bxInstruction_c *i)
{
	RMAddr(i) = READ_VIRTUAL_32BIT_REG(0x04) +
		(READ_VIRTUAL_32BIT_REG(0x02) <<0x03) + i->displ32u;
}

	void
BX_CPU_C::Resolve32Mod1or2EffectAddress_sib0xd5(BX_CPU_C *icpu,bxInstruction_c *i)
{
	RMAddr(i) = READ_VIRTUAL_32BIT_REG(0x05) +
		(READ_VIRTUAL_32BIT_REG(0x02) <<0x03) + i->displ32u;
}

	void
BX_CPU_C::Resolve32Mod1or2EffectAddress_sib0xd6(BX_CPU_C *icpu,bxInstruction_c *i)
{
	RMAddr(i) = READ_VIRTUAL_32BIT_REG(0x06) +
		(READ_VIRTUAL_32BIT_REG(0x02) <<0x03) + i->displ32u;
}

	void
BX_CPU_C::Resolve32Mod1or2EffectAddress_sib0xd7(BX_CPU_C *icpu,bxInstruction_c *i)
{
	RMAddr(i) = READ_VIRTUAL_32BIT_REG(0x07) +
		(READ_VIRTUAL_32BIT_REG(0x02) <<0x03) + i->displ32u;
}

	void
BX_CPU_C::Resolve32Mod1or2EffectAddress_sib0xd8(BX_CPU_C *icpu,bxInstruction_c *i)
{
	RMAddr(i) = READ_VIRTUAL_32BIT_REG(0x00) +
		(READ_VIRTUAL_32BIT_REG(0x03) <<0x03) + i->displ32u;
}

	void
BX_CPU_C::Resolve32Mod1or2EffectAddress_sib0xd9(BX_CPU_C *icpu,bxInstruction_c *i)
{
	RMAddr(i) = READ_VIRTUAL_32BIT_REG(0x01) +
		(READ_VIRTUAL_32BIT_REG(0x03) <<0x03) + i->displ32u;
}

	void
BX_CPU_C::Resolve32Mod1or2EffectAddress_sib0xda(BX_CPU_C *icpu,bxInstruction_c *i)
{
	RMAddr(i) = READ_VIRTUAL_32BIT_REG(0x02) +
		(READ_VIRTUAL_32BIT_REG(0x03) <<0x03) + i->displ32u;
}

	void
BX_CPU_C::Resolve32Mod1or2EffectAddress_sib0xdb(BX_CPU_C *icpu,bxInstruction_c *i)
{
	RMAddr(i) = READ_VIRTUAL_32BIT_REG(0x03) +
		(READ_VIRTUAL_32BIT_REG(0x03) <<0x03) + i->displ32u;
}

	void
BX_CPU_C::Resolve32Mod1or2EffectAddress_sib0xdc(BX_CPU_C *icpu,bxInstruction_c *i)
{
	RMAddr(i) = READ_VIRTUAL_32BIT_REG(0x04) +
		(READ_VIRTUAL_32BIT_REG(0x03) <<0x03) + i->displ32u;
}

	void
BX_CPU_C::Resolve32Mod1or2EffectAddress_sib0xdd(BX_CPU_C *icpu,bxInstruction_c *i)
{
	RMAddr(i) = READ_VIRTUAL_32BIT_REG(0x05) +
		(READ_VIRTUAL_32BIT_REG(0x03) <<0x03) + i->displ32u;
}

	void
BX_CPU_C::Resolve32Mod1or2EffectAddress_sib0xde(BX_CPU_C *icpu,bxInstruction_c *i)
{
	RMAddr(i) = READ_VIRTUAL_32BIT_REG(0x06) +
		(READ_VIRTUAL_32BIT_REG(0x03) <<0x03) + i->displ32u;
}

	void
BX_CPU_C::Resolve32Mod1or2EffectAddress_sib0xdf(BX_CPU_C *icpu,bxInstruction_c *i)
{
	RMAddr(i) = READ_VIRTUAL_32BIT_REG(0x07) +
		(READ_VIRTUAL_32BIT_REG(0x03) <<0x03) + i->displ32u;
}

	void
BX_CPU_C::Resolve32Mod1or2EffectAddress_sib0xe0(BX_CPU_C *icpu,bxInstruction_c *i)
{
	RMAddr(i) = READ_VIRTUAL_32BIT_REG(0x00) + i->displ32u;
}

	void
BX_CPU_C::Resolve32Mod1or2EffectAddress_sib0xe1(BX_CPU_C *icpu,bxInstruction_c *i)
{
	RMAddr(i) = READ_VIRTUAL_32BIT_REG(0x01) + i->displ32u;
}

	void
BX_CPU_C::Resolve32Mod1or2EffectAddress_sib0xe2(BX_CPU_C *icpu,bxInstruction_c *i)
{
	RMAddr(i) = READ_VIRTUAL_32BIT_REG(0x02) + i->displ32u;
}

	void
BX_CPU_C::Resolve32Mod1or2EffectAddress_sib0xe3(BX_CPU_C *icpu,bxInstruction_c *i)
{
	RMAddr(i) = READ_VIRTUAL_32BIT_REG(0x03) + i->displ32u;
}

	void
BX_CPU_C::Resolve32Mod1or2EffectAddress_sib0xe4(BX_CPU_C *icpu,bxInstruction_c *i)
{
	RMAddr(i) = READ_VIRTUAL_32BIT_REG(0x04) + i->displ32u;
}

	void
BX_CPU_C::Resolve32Mod1or2EffectAddress_sib0xe5(BX_CPU_C *icpu,bxInstruction_c *i)
{
	RMAddr(i) = READ_VIRTUAL_32BIT_REG(0x05) + i->displ32u;
}

	void
BX_CPU_C::Resolve32Mod1or2EffectAddress_sib0xe6(BX_CPU_C *icpu,bxInstruction_c *i)
{
	RMAddr(i) = READ_VIRTUAL_32BIT_REG(0x06) + i->displ32u;
}

	void
BX_CPU_C::Resolve32Mod1or2EffectAddress_sib0xe7(BX_CPU_C *icpu,bxInstruction_c *i)
{
	RMAddr(i) = READ_VIRTUAL_32BIT_REG(0x07) + i->displ32u;
}

	void
BX_CPU_C::Resolve32Mod1or2EffectAddress_sib0xe8(BX_CPU_C *icpu,bxInstruction_c *i)
{
	RMAddr(i) = READ_VIRTUAL_32BIT_REG(0x00) +
		(READ_VIRTUAL_32BIT_REG(0x05) <<0x03) + i->displ32u;
}

	void
BX_CPU_C::Resolve32Mod1or2EffectAddress_sib0xe9(BX_CPU_C *icpu,bxInstruction_c *i)
{
	RMAddr(i) = READ_VIRTUAL_32BIT_REG(0x01) +
		(READ_VIRTUAL_32BIT_REG(0x05) <<0x03) + i->displ32u;
}

	void
BX_CPU_C::Resolve32Mod1or2EffectAddress_sib0xea(BX_CPU_C *icpu,bxInstruction_c *i)
{
	RMAddr(i) = READ_VIRTUAL_32BIT_REG(0x02) +
		(READ_VIRTUAL_32BIT_REG(0x05) <<0x03) + i->displ32u;
}

	void
BX_CPU_C::Resolve32Mod1or2EffectAddress_sib0xeb(BX_CPU_C *icpu,bxInstruction_c *i)
{
	RMAddr(i) = READ_VIRTUAL_32BIT_REG(0x03) +
		(READ_VIRTUAL_32BIT_REG(0x05) <<0x03) + i->displ32u;
}

	void
BX_CPU_C::Resolve32Mod1or2EffectAddress_sib0xec(BX_CPU_C *icpu,bxInstruction_c *i)
{
	RMAddr(i) = READ_VIRTUAL_32BIT_REG(0x04) +
		(READ_VIRTUAL_32BIT_REG(0x05) <<0x03) + i->displ32u;
}

	void
BX_CPU_C::Resolve32Mod1or2EffectAddress_sib0xed(BX_CPU_C *icpu,bxInstruction_c *i)
{
	RMAddr(i) = READ_VIRTUAL_32BIT_REG(0x05) +
		(READ_VIRTUAL_32BIT_REG(0x05) <<0x03) + i->displ32u;
}

	void
BX_CPU_C::Resolve32Mod1or2EffectAddress_sib0xee(BX_CPU_C *icpu,bxInstruction_c *i)
{
	RMAddr(i) = READ_VIRTUAL_32BIT_REG(0x06) +
		(READ_VIRTUAL_32BIT_REG(0x05) <<0x03) + i->displ32u;
}

	void
BX_CPU_C::Resolve32Mod1or2EffectAddress_sib0xef(BX_CPU_C *icpu,bxInstruction_c *i)
{
	RMAddr(i) = READ_VIRTUAL_32BIT_REG(0x07) +
		(READ_VIRTUAL_32BIT_REG(0x05) <<0x03) + i->displ32u;
}

	void
BX_CPU_C::Resolve32Mod1or2EffectAddress_sib0xf0(BX_CPU_C *icpu,bxInstruction_c *i)
{
	RMAddr(i) = READ_VIRTUAL_32BIT_REG(0x00) +
		(READ_VIRTUAL_32BIT_REG(0x06) <<0x03) + i->displ32u;
}

	void
BX_CPU_C::Resolve32Mod1or2EffectAddress_sib0xf1(BX_CPU_C *icpu,bxInstruction_c *i)
{
	RMAddr(i) = READ_VIRTUAL_32BIT_REG(0x01) +
		(READ_VIRTUAL_32BIT_REG(0x06) <<0x03) + i->displ32u;
}

	void
BX_CPU_C::Resolve32Mod1or2EffectAddress_sib0xf2(BX_CPU_C *icpu,bxInstruction_c *i)
{
	RMAddr(i) = READ_VIRTUAL_32BIT_REG(0x02) +
		(READ_VIRTUAL_32BIT_REG(0x06) <<0x03) + i->displ32u;
}

	void
BX_CPU_C::Resolve32Mod1or2EffectAddress_sib0xf3(BX_CPU_C *icpu,bxInstruction_c *i)
{
	RMAddr(i) = READ_VIRTUAL_32BIT_REG(0x03) +
		(READ_VIRTUAL_32BIT_REG(0x06) <<0x03) + i->displ32u;
}

	void
BX_CPU_C::Resolve32Mod1or2EffectAddress_sib0xf4(BX_CPU_C *icpu,bxInstruction_c *i)
{
	RMAddr(i) = READ_VIRTUAL_32BIT_REG(0x04) +
		(READ_VIRTUAL_32BIT_REG(0x06) <<0x03) + i->displ32u;
}

	void
BX_CPU_C::Resolve32Mod1or2EffectAddress_sib0xf5(BX_CPU_C *icpu,bxInstruction_c *i)
{
	RMAddr(i) = READ_VIRTUAL_32BIT_REG(0x05) +
		(READ_VIRTUAL_32BIT_REG(0x06) <<0x03) + i->displ32u;
}

	void
BX_CPU_C::Resolve32Mod1or2EffectAddress_sib0xf6(BX_CPU_C *icpu,bxInstruction_c *i)
{
	RMAddr(i) = READ_VIRTUAL_32BIT_REG(0x06) +
		(READ_VIRTUAL_32BIT_REG(0x06) <<0x03) + i->displ32u;
}

	void
BX_CPU_C::Resolve32Mod1or2EffectAddress_sib0xf7(BX_CPU_C *icpu,bxInstruction_c *i)
{
	RMAddr(i) = READ_VIRTUAL_32BIT_REG(0x07) +
		(READ_VIRTUAL_32BIT_REG(0x06) <<0x03) + i->displ32u;
}

	void
BX_CPU_C::Resolve32Mod1or2EffectAddress_sib0xf8(BX_CPU_C *icpu,bxInstruction_c *i)
{
	RMAddr(i) = READ_VIRTUAL_32BIT_REG(0x00) +
		(READ_VIRTUAL_32BIT_REG(0x07) <<0x03) + i->displ32u;
}

	void
BX_CPU_C::Resolve32Mod1or2EffectAddress_sib0xf9(BX_CPU_C *icpu,bxInstruction_c *i)
{
	RMAddr(i) = READ_VIRTUAL_32BIT_REG(0x01) +
		(READ_VIRTUAL_32BIT_REG(0x07) <<0x03) + i->displ32u;
}

	void
BX_CPU_C::Resolve32Mod1or2EffectAddress_sib0xfa(BX_CPU_C *icpu,bxInstruction_c *i)
{
	RMAddr(i) = READ_VIRTUAL_32BIT_REG(0x02) +
		(READ_VIRTUAL_32BIT_REG(0x07) <<0x03) + i->displ32u;
}

	void
BX_CPU_C::Resolve32Mod1or2EffectAddress_sib0xfb(BX_CPU_C *icpu,bxInstruction_c *i)
{
	RMAddr(i) = READ_VIRTUAL_32BIT_REG(0x03) +
		(READ_VIRTUAL_32BIT_REG(0x07) <<0x03) + i->displ32u;
}

	void
BX_CPU_C::Resolve32Mod1or2EffectAddress_sib0xfc(BX_CPU_C *icpu,bxInstruction_c *i)
{
	RMAddr(i) = READ_VIRTUAL_32BIT_REG(0x04) +
		(READ_VIRTUAL_32BIT_REG(0x07) <<0x03) + i->displ32u;
}

	void
BX_CPU_C::Resolve32Mod1or2EffectAddress_sib0xfd(BX_CPU_C *icpu,bxInstruction_c *i)
{
	RMAddr(i) = READ_VIRTUAL_32BIT_REG(0x05) +
		(READ_VIRTUAL_32BIT_REG(0x07) <<0x03) + i->displ32u;
}

	void
BX_CPU_C::Resolve32Mod1or2EffectAddress_sib0xfe(BX_CPU_C *icpu,bxInstruction_c *i)
{
	RMAddr(i) = READ_VIRTUAL_32BIT_REG(0x06) +
		(READ_VIRTUAL_32BIT_REG(0x07) <<0x03) + i->displ32u;
}

	void
BX_CPU_C::Resolve32Mod1or2EffectAddress_sib0xff(BX_CPU_C *icpu,bxInstruction_c *i)
{
	RMAddr(i) = READ_VIRTUAL_32BIT_REG(0x07) +
		(READ_VIRTUAL_32BIT_REG(0x07) <<0x03) + i->displ32u;
}

	void
BX_CPU_C::Resolve32Mod0EffectAddress_sib0x00(BX_CPU_C *icpu,bxInstruction_c *i)
{
	RMAddr(i) = READ_VIRTUAL_32BIT_REG(0x00) +
		(READ_VIRTUAL_32BIT_REG(0x00) <<0x00);
}

	void
BX_CPU_C::Resolve32Mod0EffectAddress_sib0x01(BX_CPU_C *icpu,bxInstruction_c *i)
{
	RMAddr(i) = READ_VIRTUAL_32BIT_REG(0x01) +
		(READ_VIRTUAL_32BIT_REG(0x00) <<0x00);
}

	void
BX_CPU_C::Resolve32Mod0EffectAddress_sib0x02(BX_CPU_C *icpu,bxInstruction_c *i)
{
	RMAddr(i) = READ_VIRTUAL_32BIT_REG(0x02) +
		(READ_VIRTUAL_32BIT_REG(0x00) <<0x00);
}

	void
BX_CPU_C::Resolve32Mod0EffectAddress_sib0x03(BX_CPU_C *icpu,bxInstruction_c *i)
{
	RMAddr(i) = READ_VIRTUAL_32BIT_REG(0x03) +
		(READ_VIRTUAL_32BIT_REG(0x00) <<0x00);
}

	void
BX_CPU_C::Resolve32Mod0EffectAddress_sib0x04(BX_CPU_C *icpu,bxInstruction_c *i)
{
	RMAddr(i) = READ_VIRTUAL_32BIT_REG(0x04) +
		(READ_VIRTUAL_32BIT_REG(0x00) <<0x00);
}

	void
BX_CPU_C::Resolve32Mod0EffectAddress_sib0x05(BX_CPU_C *icpu,bxInstruction_c *i)
{
	RMAddr(i) = (READ_VIRTUAL_32BIT_REG(0x00) <<0x00) +
		i->displ32u;
}

	void
BX_CPU_C::Resolve32Mod0EffectAddress_sib0x06(BX_CPU_C *icpu,bxInstruction_c *i)
{
	RMAddr(i) = READ_VIRTUAL_32BIT_REG(0x06) +
		(READ_VIRTUAL_32BIT_REG(0x00) <<0x00);
}

	void
BX_CPU_C::Resolve32Mod0EffectAddress_sib0x07(BX_CPU_C *icpu,bxInstruction_c *i)
{
	RMAddr(i) = READ_VIRTUAL_32BIT_REG(0x07) +
		(READ_VIRTUAL_32BIT_REG(0x00) <<0x00);
}

	void
BX_CPU_C::Resolve32Mod0EffectAddress_sib0x08(BX_CPU_C *icpu,bxInstruction_c *i)
{
	RMAddr(i) = READ_VIRTUAL_32BIT_REG(0x00) +
		(READ_VIRTUAL_32BIT_REG(0x01) <<0x00);
}

	void
BX_CPU_C::Resolve32Mod0EffectAddress_sib0x09(BX_CPU_C *icpu,bxInstruction_c *i)
{
	RMAddr(i) = READ_VIRTUAL_32BIT_REG(0x01) +
		(READ_VIRTUAL_32BIT_REG(0x01) <<0x00);
}

	void
BX_CPU_C::Resolve32Mod0EffectAddress_sib0x0a(BX_CPU_C *icpu,bxInstruction_c *i)
{
	RMAddr(i) = READ_VIRTUAL_32BIT_REG(0x02) +
		(READ_VIRTUAL_32BIT_REG(0x01) <<0x00);
}

	void
BX_CPU_C::Resolve32Mod0EffectAddress_sib0x0b(BX_CPU_C *icpu,bxInstruction_c *i)
{
	RMAddr(i) = READ_VIRTUAL_32BIT_REG(0x03) +
		(READ_VIRTUAL_32BIT_REG(0x01) <<0x00);
}

	void
BX_CPU_C::Resolve32Mod0EffectAddress_sib0x0c(BX_CPU_C *icpu,bxInstruction_c *i)
{
	RMAddr(i) = READ_VIRTUAL_32BIT_REG(0x04) +
		(READ_VIRTUAL_32BIT_REG(0x01) <<0x00);
}

	void
BX_CPU_C::Resolve32Mod0EffectAddress_sib0x0d(BX_CPU_C *icpu,bxInstruction_c *i)
{
	RMAddr(i) = (READ_VIRTUAL_32BIT_REG(0x01) <<0x00) +
		i->displ32u;
}

	void
BX_CPU_C::Resolve32Mod0EffectAddress_sib0x0e(BX_CPU_C *icpu,bxInstruction_c *i)
{
	RMAddr(i) = READ_VIRTUAL_32BIT_REG(0x06) +
		(READ_VIRTUAL_32BIT_REG(0x01) <<0x00);
}

	void
BX_CPU_C::Resolve32Mod0EffectAddress_sib0x0f(BX_CPU_C *icpu,bxInstruction_c *i)
{
	RMAddr(i) = READ_VIRTUAL_32BIT_REG(0x07) +
		(READ_VIRTUAL_32BIT_REG(0x01) <<0x00);
}

	void
BX_CPU_C::Resolve32Mod0EffectAddress_sib0x10(BX_CPU_C *icpu,bxInstruction_c *i)
{
	RMAddr(i) = READ_VIRTUAL_32BIT_REG(0x00) +
		(READ_VIRTUAL_32BIT_REG(0x02) <<0x00);
}

	void
BX_CPU_C::Resolve32Mod0EffectAddress_sib0x11(BX_CPU_C *icpu,bxInstruction_c *i)
{
	RMAddr(i) = READ_VIRTUAL_32BIT_REG(0x01) +
		(READ_VIRTUAL_32BIT_REG(0x02) <<0x00);
}

	void
BX_CPU_C::Resolve32Mod0EffectAddress_sib0x12(BX_CPU_C *icpu,bxInstruction_c *i)
{
	RMAddr(i) = READ_VIRTUAL_32BIT_REG(0x02) +
		(READ_VIRTUAL_32BIT_REG(0x02) <<0x00);
}

	void
BX_CPU_C::Resolve32Mod0EffectAddress_sib0x13(BX_CPU_C *icpu,bxInstruction_c *i)
{
	RMAddr(i) = READ_VIRTUAL_32BIT_REG(0x03) +
		(READ_VIRTUAL_32BIT_REG(0x02) <<0x00);
}

	void
BX_CPU_C::Resolve32Mod0EffectAddress_sib0x14(BX_CPU_C *icpu,bxInstruction_c *i)
{
	RMAddr(i) = READ_VIRTUAL_32BIT_REG(0x04) +
		(READ_VIRTUAL_32BIT_REG(0x02) <<0x00);
}

	void
BX_CPU_C::Resolve32Mod0EffectAddress_sib0x15(BX_CPU_C *icpu,bxInstruction_c *i)
{
	RMAddr(i) = (READ_VIRTUAL_32BIT_REG(0x02) <<0x00) +
		i->displ32u;
}

	void
BX_CPU_C::Resolve32Mod0EffectAddress_sib0x16(BX_CPU_C *icpu,bxInstruction_c *i)
{
	RMAddr(i) = READ_VIRTUAL_32BIT_REG(0x06) +
		(READ_VIRTUAL_32BIT_REG(0x02) <<0x00);
}

	void
BX_CPU_C::Resolve32Mod0EffectAddress_sib0x17(BX_CPU_C *icpu,bxInstruction_c *i)
{
	RMAddr(i) = READ_VIRTUAL_32BIT_REG(0x07) +
		(READ_VIRTUAL_32BIT_REG(0x02) <<0x00);
}

	void
BX_CPU_C::Resolve32Mod0EffectAddress_sib0x18(BX_CPU_C *icpu,bxInstruction_c *i)
{
	RMAddr(i) = READ_VIRTUAL_32BIT_REG(0x00) +
		(READ_VIRTUAL_32BIT_REG(0x03) <<0x00);
}

	void
BX_CPU_C::Resolve32Mod0EffectAddress_sib0x19(BX_CPU_C *icpu,bxInstruction_c *i)
{
	RMAddr(i) = READ_VIRTUAL_32BIT_REG(0x01) +
		(READ_VIRTUAL_32BIT_REG(0x03) <<0x00);
}

	void
BX_CPU_C::Resolve32Mod0EffectAddress_sib0x1a(BX_CPU_C *icpu,bxInstruction_c *i)
{
	RMAddr(i) = READ_VIRTUAL_32BIT_REG(0x02) +
		(READ_VIRTUAL_32BIT_REG(0x03) <<0x00);
}

	void
BX_CPU_C::Resolve32Mod0EffectAddress_sib0x1b(BX_CPU_C *icpu,bxInstruction_c *i)
{
	RMAddr(i) = READ_VIRTUAL_32BIT_REG(0x03) +
		(READ_VIRTUAL_32BIT_REG(0x03) <<0x00);
}

	void
BX_CPU_C::Resolve32Mod0EffectAddress_sib0x1c(BX_CPU_C *icpu,bxInstruction_c *i)
{
	RMAddr(i) = READ_VIRTUAL_32BIT_REG(0x04) +
		(READ_VIRTUAL_32BIT_REG(0x03) <<0x00);
}

	void
BX_CPU_C::Resolve32Mod0EffectAddress_sib0x1d(BX_CPU_C *icpu,bxInstruction_c *i)
{
	RMAddr(i) = (READ_VIRTUAL_32BIT_REG(0x03) <<0x00) +
		i->displ32u;
}

	void
BX_CPU_C::Resolve32Mod0EffectAddress_sib0x1e(BX_CPU_C *icpu,bxInstruction_c *i)
{
	RMAddr(i) = READ_VIRTUAL_32BIT_REG(0x06) +
		(READ_VIRTUAL_32BIT_REG(0x03) <<0x00);
}

	void
BX_CPU_C::Resolve32Mod0EffectAddress_sib0x1f(BX_CPU_C *icpu,bxInstruction_c *i)
{
	RMAddr(i) = READ_VIRTUAL_32BIT_REG(0x07) +
		(READ_VIRTUAL_32BIT_REG(0x03) <<0x00);
}

	void
BX_CPU_C::Resolve32Mod0EffectAddress_sib0x20(BX_CPU_C *icpu,bxInstruction_c *i)
{
	RMAddr(i) = READ_VIRTUAL_32BIT_REG(0x00);
}

	void
BX_CPU_C::Resolve32Mod0EffectAddress_sib0x21(BX_CPU_C *icpu,bxInstruction_c *i)
{
	RMAddr(i) = READ_VIRTUAL_32BIT_REG(0x01);
}

	void
BX_CPU_C::Resolve32Mod0EffectAddress_sib0x22(BX_CPU_C *icpu,bxInstruction_c *i)
{
	RMAddr(i) = READ_VIRTUAL_32BIT_REG(0x02);
}

	void
BX_CPU_C::Resolve32Mod0EffectAddress_sib0x23(BX_CPU_C *icpu,bxInstruction_c *i)
{
	RMAddr(i) = READ_VIRTUAL_32BIT_REG(0x03);
}

	void
BX_CPU_C::Resolve32Mod0EffectAddress_sib0x24(BX_CPU_C *icpu,bxInstruction_c *i)
{
	RMAddr(i) = READ_VIRTUAL_32BIT_REG(0x04);
}

	void
BX_CPU_C::Resolve32Mod0EffectAddress_sib0x25(BX_CPU_C *icpu,bxInstruction_c *i)
{
	// d32, no registers used 
	RMAddr(i) = i->displ32u;
}

	void
BX_CPU_C::Resolve32Mod0EffectAddress_sib0x26(BX_CPU_C *icpu,bxInstruction_c *i)
{
	RMAddr(i) = READ_VIRTUAL_32BIT_REG(0x06);
}

	void
BX_CPU_C::Resolve32Mod0EffectAddress_sib0x27(BX_CPU_C *icpu,bxInstruction_c *i)
{
	RMAddr(i) = READ_VIRTUAL_32BIT_REG(0x07);
}

	void
BX_CPU_C::Resolve32Mod0EffectAddress_sib0x28(BX_CPU_C *icpu,bxInstruction_c *i)
{
	RMAddr(i) = READ_VIRTUAL_32BIT_REG(0x00) +
		(READ_VIRTUAL_32BIT_REG(0x05) <<0x00);
}

	void
BX_CPU_C::Resolve32Mod0EffectAddress_sib0x29(BX_CPU_C *icpu,bxInstruction_c *i)
{
	RMAddr(i) = READ_VIRTUAL_32BIT_REG(0x01) +
		(READ_VIRTUAL_32BIT_REG(0x05) <<0x00);
}

	void
BX_CPU_C::Resolve32Mod0EffectAddress_sib0x2a(BX_CPU_C *icpu,bxInstruction_c *i)
{
	RMAddr(i) = READ_VIRTUAL_32BIT_REG(0x02) +
		(READ_VIRTUAL_32BIT_REG(0x05) <<0x00);
}

	void
BX_CPU_C::Resolve32Mod0EffectAddress_sib0x2b(BX_CPU_C *icpu,bxInstruction_c *i)
{
	RMAddr(i) = READ_VIRTUAL_32BIT_REG(0x03) +
		(READ_VIRTUAL_32BIT_REG(0x05) <<0x00);
}

	void
BX_CPU_C::Resolve32Mod0EffectAddress_sib0x2c(BX_CPU_C *icpu,bxInstruction_c *i)
{
	RMAddr(i) = READ_VIRTUAL_32BIT_REG(0x04) +
		(READ_VIRTUAL_32BIT_REG(0x05) <<0x00);
}

	void
BX_CPU_C::Resolve32Mod0EffectAddress_sib0x2d(BX_CPU_C *icpu,bxInstruction_c *i)
{
	RMAddr(i) = (READ_VIRTUAL_32BIT_REG(0x05) <<0x00) +
		i->displ32u;
}

	void
BX_CPU_C::Resolve32Mod0EffectAddress_sib0x2e(BX_CPU_C *icpu,bxInstruction_c *i)
{
	RMAddr(i) = READ_VIRTUAL_32BIT_REG(0x06) +
		(READ_VIRTUAL_32BIT_REG(0x05) <<0x00);
}

	void
BX_CPU_C::Resolve32Mod0EffectAddress_sib0x2f(BX_CPU_C *icpu,bxInstruction_c *i)
{
	RMAddr(i) = READ_VIRTUAL_32BIT_REG(0x07) +
		(READ_VIRTUAL_32BIT_REG(0x05) <<0x00);
}

	void
BX_CPU_C::Resolve32Mod0EffectAddress_sib0x30(BX_CPU_C *icpu,bxInstruction_c *i)
{
	RMAddr(i) = READ_VIRTUAL_32BIT_REG(0x00) +
		(READ_VIRTUAL_32BIT_REG(0x06) <<0x00);
}

	void
BX_CPU_C::Resolve32Mod0EffectAddress_sib0x31(BX_CPU_C *icpu,bxInstruction_c *i)
{
	RMAddr(i) = READ_VIRTUAL_32BIT_REG(0x01) +
		(READ_VIRTUAL_32BIT_REG(0x06) <<0x00);
}

	void
BX_CPU_C::Resolve32Mod0EffectAddress_sib0x32(BX_CPU_C *icpu,bxInstruction_c *i)
{
	RMAddr(i) = READ_VIRTUAL_32BIT_REG(0x02) +
		(READ_VIRTUAL_32BIT_REG(0x06) <<0x00);
}

	void
BX_CPU_C::Resolve32Mod0EffectAddress_sib0x33(BX_CPU_C *icpu,bxInstruction_c *i)
{
	RMAddr(i) = READ_VIRTUAL_32BIT_REG(0x03) +
		(READ_VIRTUAL_32BIT_REG(0x06) <<0x00);
}

	void
BX_CPU_C::Resolve32Mod0EffectAddress_sib0x34(BX_CPU_C *icpu,bxInstruction_c *i)
{
	RMAddr(i) = READ_VIRTUAL_32BIT_REG(0x04) +
		(READ_VIRTUAL_32BIT_REG(0x06) <<0x00);
}

	void
BX_CPU_C::Resolve32Mod0EffectAddress_sib0x35(BX_CPU_C *icpu,bxInstruction_c *i)
{
	RMAddr(i) = (READ_VIRTUAL_32BIT_REG(0x06) <<0x00) +
		i->displ32u;
}

	void
BX_CPU_C::Resolve32Mod0EffectAddress_sib0x36(BX_CPU_C *icpu,bxInstruction_c *i)
{
	RMAddr(i) = READ_VIRTUAL_32BIT_REG(0x06) +
		(READ_VIRTUAL_32BIT_REG(0x06) <<0x00);
}

	void
BX_CPU_C::Resolve32Mod0EffectAddress_sib0x37(BX_CPU_C *icpu,bxInstruction_c *i)
{
	RMAddr(i) = READ_VIRTUAL_32BIT_REG(0x07) +
		(READ_VIRTUAL_32BIT_REG(0x06) <<0x00);
}

	void
BX_CPU_C::Resolve32Mod0EffectAddress_sib0x38(BX_CPU_C *icpu,bxInstruction_c *i)
{
	RMAddr(i) = READ_VIRTUAL_32BIT_REG(0x00) +
		(READ_VIRTUAL_32BIT_REG(0x07) <<0x00);
}

	void
BX_CPU_C::Resolve32Mod0EffectAddress_sib0x39(BX_CPU_C *icpu,bxInstruction_c *i)
{
	RMAddr(i) = READ_VIRTUAL_32BIT_REG(0x01) +
		(READ_VIRTUAL_32BIT_REG(0x07) <<0x00);
}

	void
BX_CPU_C::Resolve32Mod0EffectAddress_sib0x3a(BX_CPU_C *icpu,bxInstruction_c *i)
{
	RMAddr(i) = READ_VIRTUAL_32BIT_REG(0x02) +
		(READ_VIRTUAL_32BIT_REG(0x07) <<0x00);
}

	void
BX_CPU_C::Resolve32Mod0EffectAddress_sib0x3b(BX_CPU_C *icpu,bxInstruction_c *i)
{
	RMAddr(i) = READ_VIRTUAL_32BIT_REG(0x03) +
		(READ_VIRTUAL_32BIT_REG(0x07) <<0x00);
}

	void
BX_CPU_C::Resolve32Mod0EffectAddress_sib0x3c(BX_CPU_C *icpu,bxInstruction_c *i)
{
	RMAddr(i) = READ_VIRTUAL_32BIT_REG(0x04) +
		(READ_VIRTUAL_32BIT_REG(0x07) <<0x00);
}

	void
BX_CPU_C::Resolve32Mod0EffectAddress_sib0x3d(BX_CPU_C *icpu,bxInstruction_c *i)
{
	RMAddr(i) = (READ_VIRTUAL_32BIT_REG(0x07) <<0x00) +
		i->displ32u;
}

	void
BX_CPU_C::Resolve32Mod0EffectAddress_sib0x3e(BX_CPU_C *icpu,bxInstruction_c *i)
{
	RMAddr(i) = READ_VIRTUAL_32BIT_REG(0x06) +
		(READ_VIRTUAL_32BIT_REG(0x07) <<0x00);
}

	void
BX_CPU_C::Resolve32Mod0EffectAddress_sib0x3f(BX_CPU_C *icpu,bxInstruction_c *i)
{
	RMAddr(i) = READ_VIRTUAL_32BIT_REG(0x07) +
		(READ_VIRTUAL_32BIT_REG(0x07) <<0x00);
}

	void
BX_CPU_C::Resolve32Mod0EffectAddress_sib0x40(BX_CPU_C *icpu,bxInstruction_c *i)
{
	RMAddr(i) = READ_VIRTUAL_32BIT_REG(0x00) +
		(READ_VIRTUAL_32BIT_REG(0x00) <<0x01);
}

	void
BX_CPU_C::Resolve32Mod0EffectAddress_sib0x41(BX_CPU_C *icpu,bxInstruction_c *i)
{
	RMAddr(i) = READ_VIRTUAL_32BIT_REG(0x01) +
		(READ_VIRTUAL_32BIT_REG(0x00) <<0x01);
}

	void
BX_CPU_C::Resolve32Mod0EffectAddress_sib0x42(BX_CPU_C *icpu,bxInstruction_c *i)
{
	RMAddr(i) = READ_VIRTUAL_32BIT_REG(0x02) +
		(READ_VIRTUAL_32BIT_REG(0x00) <<0x01);
}

	void
BX_CPU_C::Resolve32Mod0EffectAddress_sib0x43(BX_CPU_C *icpu,bxInstruction_c *i)
{
	RMAddr(i) = READ_VIRTUAL_32BIT_REG(0x03) +
		(READ_VIRTUAL_32BIT_REG(0x00) <<0x01);
}

	void
BX_CPU_C::Resolve32Mod0EffectAddress_sib0x44(BX_CPU_C *icpu,bxInstruction_c *i)
{
	RMAddr(i) = READ_VIRTUAL_32BIT_REG(0x04) +
		(READ_VIRTUAL_32BIT_REG(0x00) <<0x01);
}

	void
BX_CPU_C::Resolve32Mod0EffectAddress_sib0x45(BX_CPU_C *icpu,bxInstruction_c *i)
{
	RMAddr(i) = (READ_VIRTUAL_32BIT_REG(0x00) <<0x01) +
		i->displ32u;
}

	void
BX_CPU_C::Resolve32Mod0EffectAddress_sib0x46(BX_CPU_C *icpu,bxInstruction_c *i)
{
	RMAddr(i) = READ_VIRTUAL_32BIT_REG(0x06) +
		(READ_VIRTUAL_32BIT_REG(0x00) <<0x01);
}

	void
BX_CPU_C::Resolve32Mod0EffectAddress_sib0x47(BX_CPU_C *icpu,bxInstruction_c *i)
{
	RMAddr(i) = READ_VIRTUAL_32BIT_REG(0x07) +
		(READ_VIRTUAL_32BIT_REG(0x00) <<0x01);
}

	void
BX_CPU_C::Resolve32Mod0EffectAddress_sib0x48(BX_CPU_C *icpu,bxInstruction_c *i)
{
	RMAddr(i) = READ_VIRTUAL_32BIT_REG(0x00) +
		(READ_VIRTUAL_32BIT_REG(0x01) <<0x01);
}

	void
BX_CPU_C::Resolve32Mod0EffectAddress_sib0x49(BX_CPU_C *icpu,bxInstruction_c *i)
{
	RMAddr(i) = READ_VIRTUAL_32BIT_REG(0x01) +
		(READ_VIRTUAL_32BIT_REG(0x01) <<0x01);
}

	void
BX_CPU_C::Resolve32Mod0EffectAddress_sib0x4a(BX_CPU_C *icpu,bxInstruction_c *i)
{
	RMAddr(i) = READ_VIRTUAL_32BIT_REG(0x02) +
		(READ_VIRTUAL_32BIT_REG(0x01) <<0x01);
}

	void
BX_CPU_C::Resolve32Mod0EffectAddress_sib0x4b(BX_CPU_C *icpu,bxInstruction_c *i)
{
	RMAddr(i) = READ_VIRTUAL_32BIT_REG(0x03) +
		(READ_VIRTUAL_32BIT_REG(0x01) <<0x01);
}

	void
BX_CPU_C::Resolve32Mod0EffectAddress_sib0x4c(BX_CPU_C *icpu,bxInstruction_c *i)
{
	RMAddr(i) = READ_VIRTUAL_32BIT_REG(0x04) +
		(READ_VIRTUAL_32BIT_REG(0x01) <<0x01);
}

	void
BX_CPU_C::Resolve32Mod0EffectAddress_sib0x4d(BX_CPU_C *icpu,bxInstruction_c *i)
{
	RMAddr(i) = (READ_VIRTUAL_32BIT_REG(0x01) <<0x01) +
		i->displ32u;
}

	void
BX_CPU_C::Resolve32Mod0EffectAddress_sib0x4e(BX_CPU_C *icpu,bxInstruction_c *i)
{
	RMAddr(i) = READ_VIRTUAL_32BIT_REG(0x06) +
		(READ_VIRTUAL_32BIT_REG(0x01) <<0x01);
}

	void
BX_CPU_C::Resolve32Mod0EffectAddress_sib0x4f(BX_CPU_C *icpu,bxInstruction_c *i)
{
	RMAddr(i) = READ_VIRTUAL_32BIT_REG(0x07) +
		(READ_VIRTUAL_32BIT_REG(0x01) <<0x01);
}

	void
BX_CPU_C::Resolve32Mod0EffectAddress_sib0x50(BX_CPU_C *icpu,bxInstruction_c *i)
{
	RMAddr(i) = READ_VIRTUAL_32BIT_REG(0x00) +
		(READ_VIRTUAL_32BIT_REG(0x02) <<0x01);
}

	void
BX_CPU_C::Resolve32Mod0EffectAddress_sib0x51(BX_CPU_C *icpu,bxInstruction_c *i)
{
	RMAddr(i) = READ_VIRTUAL_32BIT_REG(0x01) +
		(READ_VIRTUAL_32BIT_REG(0x02) <<0x01);
}

	void
BX_CPU_C::Resolve32Mod0EffectAddress_sib0x52(BX_CPU_C *icpu,bxInstruction_c *i)
{
	RMAddr(i) = READ_VIRTUAL_32BIT_REG(0x02) +
		(READ_VIRTUAL_32BIT_REG(0x02) <<0x01);
}

	void
BX_CPU_C::Resolve32Mod0EffectAddress_sib0x53(BX_CPU_C *icpu,bxInstruction_c *i)
{
	RMAddr(i) = READ_VIRTUAL_32BIT_REG(0x03) +
		(READ_VIRTUAL_32BIT_REG(0x02) <<0x01);
}

	void
BX_CPU_C::Resolve32Mod0EffectAddress_sib0x54(BX_CPU_C *icpu,bxInstruction_c *i)
{
	RMAddr(i) = READ_VIRTUAL_32BIT_REG(0x04) +
		(READ_VIRTUAL_32BIT_REG(0x02) <<0x01);
}

	void
BX_CPU_C::Resolve32Mod0EffectAddress_sib0x55(BX_CPU_C *icpu,bxInstruction_c *i)
{
	RMAddr(i) = (READ_VIRTUAL_32BIT_REG(0x02) <<0x01) +
		i->displ32u;
}

	void
BX_CPU_C::Resolve32Mod0EffectAddress_sib0x56(BX_CPU_C *icpu,bxInstruction_c *i)
{
	RMAddr(i) = READ_VIRTUAL_32BIT_REG(0x06) +
		(READ_VIRTUAL_32BIT_REG(0x02) <<0x01);
}

	void
BX_CPU_C::Resolve32Mod0EffectAddress_sib0x57(BX_CPU_C *icpu,bxInstruction_c *i)
{
	RMAddr(i) = READ_VIRTUAL_32BIT_REG(0x07) +
		(READ_VIRTUAL_32BIT_REG(0x02) <<0x01);
}

	void
BX_CPU_C::Resolve32Mod0EffectAddress_sib0x58(BX_CPU_C *icpu,bxInstruction_c *i)
{
	RMAddr(i) = READ_VIRTUAL_32BIT_REG(0x00) +
		(READ_VIRTUAL_32BIT_REG(0x03) <<0x01);
}

	void
BX_CPU_C::Resolve32Mod0EffectAddress_sib0x59(BX_CPU_C *icpu,bxInstruction_c *i)
{
	RMAddr(i) = READ_VIRTUAL_32BIT_REG(0x01) +
		(READ_VIRTUAL_32BIT_REG(0x03) <<0x01);
}

	void
BX_CPU_C::Resolve32Mod0EffectAddress_sib0x5a(BX_CPU_C *icpu,bxInstruction_c *i)
{
	RMAddr(i) = READ_VIRTUAL_32BIT_REG(0x02) +
		(READ_VIRTUAL_32BIT_REG(0x03) <<0x01);
}

	void
BX_CPU_C::Resolve32Mod0EffectAddress_sib0x5b(BX_CPU_C *icpu,bxInstruction_c *i)
{
	RMAddr(i) = READ_VIRTUAL_32BIT_REG(0x03) +
		(READ_VIRTUAL_32BIT_REG(0x03) <<0x01);
}

	void
BX_CPU_C::Resolve32Mod0EffectAddress_sib0x5c(BX_CPU_C *icpu,bxInstruction_c *i)
{
	RMAddr(i) = READ_VIRTUAL_32BIT_REG(0x04) +
		(READ_VIRTUAL_32BIT_REG(0x03) <<0x01);
}

	void
BX_CPU_C::Resolve32Mod0EffectAddress_sib0x5d(BX_CPU_C *icpu,bxInstruction_c *i)
{
	RMAddr(i) = (READ_VIRTUAL_32BIT_REG(0x03) <<0x01) +
		i->displ32u;
}

	void
BX_CPU_C::Resolve32Mod0EffectAddress_sib0x5e(BX_CPU_C *icpu,bxInstruction_c *i)
{
	RMAddr(i) = READ_VIRTUAL_32BIT_REG(0x06) +
		(READ_VIRTUAL_32BIT_REG(0x03) <<0x01);
}

	void
BX_CPU_C::Resolve32Mod0EffectAddress_sib0x5f(BX_CPU_C *icpu,bxInstruction_c *i)
{
	RMAddr(i) = READ_VIRTUAL_32BIT_REG(0x07) +
		(READ_VIRTUAL_32BIT_REG(0x03) <<0x01);
}

	void
BX_CPU_C::Resolve32Mod0EffectAddress_sib0x60(BX_CPU_C *icpu,bxInstruction_c *i)
{
	RMAddr(i) = READ_VIRTUAL_32BIT_REG(0x00);
}

	void
BX_CPU_C::Resolve32Mod0EffectAddress_sib0x61(BX_CPU_C *icpu,bxInstruction_c *i)
{
	RMAddr(i) = READ_VIRTUAL_32BIT_REG(0x01);
}

	void
BX_CPU_C::Resolve32Mod0EffectAddress_sib0x62(BX_CPU_C *icpu,bxInstruction_c *i)
{
	RMAddr(i) = READ_VIRTUAL_32BIT_REG(0x02);
}

	void
BX_CPU_C::Resolve32Mod0EffectAddress_sib0x63(BX_CPU_C *icpu,bxInstruction_c *i)
{
	RMAddr(i) = READ_VIRTUAL_32BIT_REG(0x03);
}

	void
BX_CPU_C::Resolve32Mod0EffectAddress_sib0x64(BX_CPU_C *icpu,bxInstruction_c *i)
{
	RMAddr(i) = READ_VIRTUAL_32BIT_REG(0x04);
}

	void
BX_CPU_C::Resolve32Mod0EffectAddress_sib0x65(BX_CPU_C *icpu,bxInstruction_c *i)
{
	// d32, no registers used 
	RMAddr(i) = i->displ32u;
}

	void
BX_CPU_C::Resolve32Mod0EffectAddress_sib0x66(BX_CPU_C *icpu,bxInstruction_c *i)
{
	RMAddr(i) = READ_VIRTUAL_32BIT_REG(0x06);
}

	void
BX_CPU_C::Resolve32Mod0EffectAddress_sib0x67(BX_CPU_C *icpu,bxInstruction_c *i)
{
	RMAddr(i) = READ_VIRTUAL_32BIT_REG(0x07);
}

	void
BX_CPU_C::Resolve32Mod0EffectAddress_sib0x68(BX_CPU_C *icpu,bxInstruction_c *i)
{
	RMAddr(i) = READ_VIRTUAL_32BIT_REG(0x00) +
		(READ_VIRTUAL_32BIT_REG(0x05) <<0x01);
}

	void
BX_CPU_C::Resolve32Mod0EffectAddress_sib0x69(BX_CPU_C *icpu,bxInstruction_c *i)
{
	RMAddr(i) = READ_VIRTUAL_32BIT_REG(0x01) +
		(READ_VIRTUAL_32BIT_REG(0x05) <<0x01);
}

	void
BX_CPU_C::Resolve32Mod0EffectAddress_sib0x6a(BX_CPU_C *icpu,bxInstruction_c *i)
{
	RMAddr(i) = READ_VIRTUAL_32BIT_REG(0x02) +
		(READ_VIRTUAL_32BIT_REG(0x05) <<0x01);
}

	void
BX_CPU_C::Resolve32Mod0EffectAddress_sib0x6b(BX_CPU_C *icpu,bxInstruction_c *i)
{
	RMAddr(i) = READ_VIRTUAL_32BIT_REG(0x03) +
		(READ_VIRTUAL_32BIT_REG(0x05) <<0x01);
}

	void
BX_CPU_C::Resolve32Mod0EffectAddress_sib0x6c(BX_CPU_C *icpu,bxInstruction_c *i)
{
	RMAddr(i) = READ_VIRTUAL_32BIT_REG(0x04) +
		(READ_VIRTUAL_32BIT_REG(0x05) <<0x01);
}

	void
BX_CPU_C::Resolve32Mod0EffectAddress_sib0x6d(BX_CPU_C *icpu,bxInstruction_c *i)
{
	RMAddr(i) = (READ_VIRTUAL_32BIT_REG(0x05) <<0x01) +
		i->displ32u;
}

	void
BX_CPU_C::Resolve32Mod0EffectAddress_sib0x6e(BX_CPU_C *icpu,bxInstruction_c *i)
{
	RMAddr(i) = READ_VIRTUAL_32BIT_REG(0x06) +
		(READ_VIRTUAL_32BIT_REG(0x05) <<0x01);
}

	void
BX_CPU_C::Resolve32Mod0EffectAddress_sib0x6f(BX_CPU_C *icpu,bxInstruction_c *i)
{
	RMAddr(i) = READ_VIRTUAL_32BIT_REG(0x07) +
		(READ_VIRTUAL_32BIT_REG(0x05) <<0x01);
}

	void
BX_CPU_C::Resolve32Mod0EffectAddress_sib0x70(BX_CPU_C *icpu,bxInstruction_c *i)
{
	RMAddr(i) = READ_VIRTUAL_32BIT_REG(0x00) +
		(READ_VIRTUAL_32BIT_REG(0x06) <<0x01);
}

	void
BX_CPU_C::Resolve32Mod0EffectAddress_sib0x71(BX_CPU_C *icpu,bxInstruction_c *i)
{
	RMAddr(i) = READ_VIRTUAL_32BIT_REG(0x01) +
		(READ_VIRTUAL_32BIT_REG(0x06) <<0x01);
}

	void
BX_CPU_C::Resolve32Mod0EffectAddress_sib0x72(BX_CPU_C *icpu,bxInstruction_c *i)
{
	RMAddr(i) = READ_VIRTUAL_32BIT_REG(0x02) +
		(READ_VIRTUAL_32BIT_REG(0x06) <<0x01);
}

	void
BX_CPU_C::Resolve32Mod0EffectAddress_sib0x73(BX_CPU_C *icpu,bxInstruction_c *i)
{
	RMAddr(i) = READ_VIRTUAL_32BIT_REG(0x03) +
		(READ_VIRTUAL_32BIT_REG(0x06) <<0x01);
}

	void
BX_CPU_C::Resolve32Mod0EffectAddress_sib0x74(BX_CPU_C *icpu,bxInstruction_c *i)
{
	RMAddr(i) = READ_VIRTUAL_32BIT_REG(0x04) +
		(READ_VIRTUAL_32BIT_REG(0x06) <<0x01);
}

	void
BX_CPU_C::Resolve32Mod0EffectAddress_sib0x75(BX_CPU_C *icpu,bxInstruction_c *i)
{
	RMAddr(i) = (READ_VIRTUAL_32BIT_REG(0x06) <<0x01) +
		i->displ32u;
}

	void
BX_CPU_C::Resolve32Mod0EffectAddress_sib0x76(BX_CPU_C *icpu,bxInstruction_c *i)
{
	RMAddr(i) = READ_VIRTUAL_32BIT_REG(0x06) +
		(READ_VIRTUAL_32BIT_REG(0x06) <<0x01);
}

	void
BX_CPU_C::Resolve32Mod0EffectAddress_sib0x77(BX_CPU_C *icpu,bxInstruction_c *i)
{
	RMAddr(i) = READ_VIRTUAL_32BIT_REG(0x07) +
		(READ_VIRTUAL_32BIT_REG(0x06) <<0x01);
}

	void
BX_CPU_C::Resolve32Mod0EffectAddress_sib0x78(BX_CPU_C *icpu,bxInstruction_c *i)
{
	RMAddr(i) = READ_VIRTUAL_32BIT_REG(0x00) +
		(READ_VIRTUAL_32BIT_REG(0x07) <<0x01);
}

	void
BX_CPU_C::Resolve32Mod0EffectAddress_sib0x79(BX_CPU_C *icpu,bxInstruction_c *i)
{
	RMAddr(i) = READ_VIRTUAL_32BIT_REG(0x01) +
		(READ_VIRTUAL_32BIT_REG(0x07) <<0x01);
}

	void
BX_CPU_C::Resolve32Mod0EffectAddress_sib0x7a(BX_CPU_C *icpu,bxInstruction_c *i)
{
	RMAddr(i) = READ_VIRTUAL_32BIT_REG(0x02) +
		(READ_VIRTUAL_32BIT_REG(0x07) <<0x01);
}

	void
BX_CPU_C::Resolve32Mod0EffectAddress_sib0x7b(BX_CPU_C *icpu,bxInstruction_c *i)
{
	RMAddr(i) = READ_VIRTUAL_32BIT_REG(0x03) +
		(READ_VIRTUAL_32BIT_REG(0x07) <<0x01);
}

	void
BX_CPU_C::Resolve32Mod0EffectAddress_sib0x7c(BX_CPU_C *icpu,bxInstruction_c *i)
{
	RMAddr(i) = READ_VIRTUAL_32BIT_REG(0x04) +
		(READ_VIRTUAL_32BIT_REG(0x07) <<0x01);
}

	void
BX_CPU_C::Resolve32Mod0EffectAddress_sib0x7d(BX_CPU_C *icpu,bxInstruction_c *i)
{
	RMAddr(i) = (READ_VIRTUAL_32BIT_REG(0x07) <<0x01) +
		i->displ32u;
}

	void
BX_CPU_C::Resolve32Mod0EffectAddress_sib0x7e(BX_CPU_C *icpu,bxInstruction_c *i)
{
	RMAddr(i) = READ_VIRTUAL_32BIT_REG(0x06) +
		(READ_VIRTUAL_32BIT_REG(0x07) <<0x01);
}

	void
BX_CPU_C::Resolve32Mod0EffectAddress_sib0x7f(BX_CPU_C *icpu,bxInstruction_c *i)
{
	RMAddr(i) = READ_VIRTUAL_32BIT_REG(0x07) +
		(READ_VIRTUAL_32BIT_REG(0x07) <<0x01);
}

	void
BX_CPU_C::Resolve32Mod0EffectAddress_sib0x80(BX_CPU_C *icpu,bxInstruction_c *i)
{
	RMAddr(i) = READ_VIRTUAL_32BIT_REG(0x00) +
		(READ_VIRTUAL_32BIT_REG(0x00) <<0x02);
}

	void
BX_CPU_C::Resolve32Mod0EffectAddress_sib0x81(BX_CPU_C *icpu,bxInstruction_c *i)
{
	RMAddr(i) = READ_VIRTUAL_32BIT_REG(0x01) +
		(READ_VIRTUAL_32BIT_REG(0x00) <<0x02);
}

	void
BX_CPU_C::Resolve32Mod0EffectAddress_sib0x82(BX_CPU_C *icpu,bxInstruction_c *i)
{
	RMAddr(i) = READ_VIRTUAL_32BIT_REG(0x02) +
		(READ_VIRTUAL_32BIT_REG(0x00) <<0x02);
}

	void
BX_CPU_C::Resolve32Mod0EffectAddress_sib0x83(BX_CPU_C *icpu,bxInstruction_c *i)
{
	RMAddr(i) = READ_VIRTUAL_32BIT_REG(0x03) +
		(READ_VIRTUAL_32BIT_REG(0x00) <<0x02);
}

	void
BX_CPU_C::Resolve32Mod0EffectAddress_sib0x84(BX_CPU_C *icpu,bxInstruction_c *i)
{
	RMAddr(i) = READ_VIRTUAL_32BIT_REG(0x04) +
		(READ_VIRTUAL_32BIT_REG(0x00) <<0x02);
}

	void
BX_CPU_C::Resolve32Mod0EffectAddress_sib0x85(BX_CPU_C *icpu,bxInstruction_c *i)
{
	RMAddr(i) = (READ_VIRTUAL_32BIT_REG(0x00) <<0x02) +
		i->displ32u;
}

	void
BX_CPU_C::Resolve32Mod0EffectAddress_sib0x86(BX_CPU_C *icpu,bxInstruction_c *i)
{
	RMAddr(i) = READ_VIRTUAL_32BIT_REG(0x06) +
		(READ_VIRTUAL_32BIT_REG(0x00) <<0x02);
}

	void
BX_CPU_C::Resolve32Mod0EffectAddress_sib0x87(BX_CPU_C *icpu,bxInstruction_c *i)
{
	RMAddr(i) = READ_VIRTUAL_32BIT_REG(0x07) +
		(READ_VIRTUAL_32BIT_REG(0x00) <<0x02);
}

	void
BX_CPU_C::Resolve32Mod0EffectAddress_sib0x88(BX_CPU_C *icpu,bxInstruction_c *i)
{
	RMAddr(i) = READ_VIRTUAL_32BIT_REG(0x00) +
		(READ_VIRTUAL_32BIT_REG(0x01) <<0x02);
}

	void
BX_CPU_C::Resolve32Mod0EffectAddress_sib0x89(BX_CPU_C *icpu,bxInstruction_c *i)
{
	RMAddr(i) = READ_VIRTUAL_32BIT_REG(0x01) +
		(READ_VIRTUAL_32BIT_REG(0x01) <<0x02);
}

	void
BX_CPU_C::Resolve32Mod0EffectAddress_sib0x8a(BX_CPU_C *icpu,bxInstruction_c *i)
{
	RMAddr(i) = READ_VIRTUAL_32BIT_REG(0x02) +
		(READ_VIRTUAL_32BIT_REG(0x01) <<0x02);
}

	void
BX_CPU_C::Resolve32Mod0EffectAddress_sib0x8b(BX_CPU_C *icpu,bxInstruction_c *i)
{
	RMAddr(i) = READ_VIRTUAL_32BIT_REG(0x03) +
		(READ_VIRTUAL_32BIT_REG(0x01) <<0x02);
}

	void
BX_CPU_C::Resolve32Mod0EffectAddress_sib0x8c(BX_CPU_C *icpu,bxInstruction_c *i)
{
	RMAddr(i) = READ_VIRTUAL_32BIT_REG(0x04) +
		(READ_VIRTUAL_32BIT_REG(0x01) <<0x02);
}

	void
BX_CPU_C::Resolve32Mod0EffectAddress_sib0x8d(BX_CPU_C *icpu,bxInstruction_c *i)
{
	RMAddr(i) = (READ_VIRTUAL_32BIT_REG(0x01) <<0x02) +
		i->displ32u;
}

	void
BX_CPU_C::Resolve32Mod0EffectAddress_sib0x8e(BX_CPU_C *icpu,bxInstruction_c *i)
{
	RMAddr(i) = READ_VIRTUAL_32BIT_REG(0x06) +
		(READ_VIRTUAL_32BIT_REG(0x01) <<0x02);
}

	void
BX_CPU_C::Resolve32Mod0EffectAddress_sib0x8f(BX_CPU_C *icpu,bxInstruction_c *i)
{
	RMAddr(i) = READ_VIRTUAL_32BIT_REG(0x07) +
		(READ_VIRTUAL_32BIT_REG(0x01) <<0x02);
}

	void
BX_CPU_C::Resolve32Mod0EffectAddress_sib0x90(BX_CPU_C *icpu,bxInstruction_c *i)
{
	RMAddr(i) = READ_VIRTUAL_32BIT_REG(0x00) +
		(READ_VIRTUAL_32BIT_REG(0x02) <<0x02);
}

	void
BX_CPU_C::Resolve32Mod0EffectAddress_sib0x91(BX_CPU_C *icpu,bxInstruction_c *i)
{
	RMAddr(i) = READ_VIRTUAL_32BIT_REG(0x01) +
		(READ_VIRTUAL_32BIT_REG(0x02) <<0x02);
}

	void
BX_CPU_C::Resolve32Mod0EffectAddress_sib0x92(BX_CPU_C *icpu,bxInstruction_c *i)
{
	RMAddr(i) = READ_VIRTUAL_32BIT_REG(0x02) +
		(READ_VIRTUAL_32BIT_REG(0x02) <<0x02);
}

	void
BX_CPU_C::Resolve32Mod0EffectAddress_sib0x93(BX_CPU_C *icpu,bxInstruction_c *i)
{
	RMAddr(i) = READ_VIRTUAL_32BIT_REG(0x03) +
		(READ_VIRTUAL_32BIT_REG(0x02) <<0x02);
}

	void
BX_CPU_C::Resolve32Mod0EffectAddress_sib0x94(BX_CPU_C *icpu,bxInstruction_c *i)
{
	RMAddr(i) = READ_VIRTUAL_32BIT_REG(0x04) +
		(READ_VIRTUAL_32BIT_REG(0x02) <<0x02);
}

	void
BX_CPU_C::Resolve32Mod0EffectAddress_sib0x95(BX_CPU_C *icpu,bxInstruction_c *i)
{
	RMAddr(i) = (READ_VIRTUAL_32BIT_REG(0x02) <<0x02) +
		i->displ32u;
}

	void
BX_CPU_C::Resolve32Mod0EffectAddress_sib0x96(BX_CPU_C *icpu,bxInstruction_c *i)
{
	RMAddr(i) = READ_VIRTUAL_32BIT_REG(0x06) +
		(READ_VIRTUAL_32BIT_REG(0x02) <<0x02);
}

	void
BX_CPU_C::Resolve32Mod0EffectAddress_sib0x97(BX_CPU_C *icpu,bxInstruction_c *i)
{
	RMAddr(i) = READ_VIRTUAL_32BIT_REG(0x07) +
		(READ_VIRTUAL_32BIT_REG(0x02) <<0x02);
}

	void
BX_CPU_C::Resolve32Mod0EffectAddress_sib0x98(BX_CPU_C *icpu,bxInstruction_c *i)
{
	RMAddr(i) = READ_VIRTUAL_32BIT_REG(0x00) +
		(READ_VIRTUAL_32BIT_REG(0x03) <<0x02);
}

	void
BX_CPU_C::Resolve32Mod0EffectAddress_sib0x99(BX_CPU_C *icpu,bxInstruction_c *i)
{
	RMAddr(i) = READ_VIRTUAL_32BIT_REG(0x01) +
		(READ_VIRTUAL_32BIT_REG(0x03) <<0x02);
}

	void
BX_CPU_C::Resolve32Mod0EffectAddress_sib0x9a(BX_CPU_C *icpu,bxInstruction_c *i)
{
	RMAddr(i) = READ_VIRTUAL_32BIT_REG(0x02) +
		(READ_VIRTUAL_32BIT_REG(0x03) <<0x02);
}

	void
BX_CPU_C::Resolve32Mod0EffectAddress_sib0x9b(BX_CPU_C *icpu,bxInstruction_c *i)
{
	RMAddr(i) = READ_VIRTUAL_32BIT_REG(0x03) +
		(READ_VIRTUAL_32BIT_REG(0x03) <<0x02);
}

	void
BX_CPU_C::Resolve32Mod0EffectAddress_sib0x9c(BX_CPU_C *icpu,bxInstruction_c *i)
{
	RMAddr(i) = READ_VIRTUAL_32BIT_REG(0x04) +
		(READ_VIRTUAL_32BIT_REG(0x03) <<0x02);
}

	void
BX_CPU_C::Resolve32Mod0EffectAddress_sib0x9d(BX_CPU_C *icpu,bxInstruction_c *i)
{
	RMAddr(i) = (READ_VIRTUAL_32BIT_REG(0x03) <<0x02) +
		i->displ32u;
}

	void
BX_CPU_C::Resolve32Mod0EffectAddress_sib0x9e(BX_CPU_C *icpu,bxInstruction_c *i)
{
	RMAddr(i) = READ_VIRTUAL_32BIT_REG(0x06) +
		(READ_VIRTUAL_32BIT_REG(0x03) <<0x02);
}

	void
BX_CPU_C::Resolve32Mod0EffectAddress_sib0x9f(BX_CPU_C *icpu,bxInstruction_c *i)
{
	RMAddr(i) = READ_VIRTUAL_32BIT_REG(0x07) +
		(READ_VIRTUAL_32BIT_REG(0x03) <<0x02);
}

	void
BX_CPU_C::Resolve32Mod0EffectAddress_sib0xa0(BX_CPU_C *icpu,bxInstruction_c *i)
{
	RMAddr(i) = READ_VIRTUAL_32BIT_REG(0x00);
}

	void
BX_CPU_C::Resolve32Mod0EffectAddress_sib0xa1(BX_CPU_C *icpu,bxInstruction_c *i)
{
	RMAddr(i) = READ_VIRTUAL_32BIT_REG(0x01);
}

	void
BX_CPU_C::Resolve32Mod0EffectAddress_sib0xa2(BX_CPU_C *icpu,bxInstruction_c *i)
{
	RMAddr(i) = READ_VIRTUAL_32BIT_REG(0x02);
}

	void
BX_CPU_C::Resolve32Mod0EffectAddress_sib0xa3(BX_CPU_C *icpu,bxInstruction_c *i)
{
	RMAddr(i) = READ_VIRTUAL_32BIT_REG(0x03);
}

	void
BX_CPU_C::Resolve32Mod0EffectAddress_sib0xa4(BX_CPU_C *icpu,bxInstruction_c *i)
{
	RMAddr(i) = READ_VIRTUAL_32BIT_REG(0x04);
}

	void
BX_CPU_C::Resolve32Mod0EffectAddress_sib0xa5(BX_CPU_C *icpu,bxInstruction_c *i)
{
	// d32, no registers used 
	RMAddr(i) = i->displ32u;
}

	void
BX_CPU_C::Resolve32Mod0EffectAddress_sib0xa6(BX_CPU_C *icpu,bxInstruction_c *i)
{
	RMAddr(i) = READ_VIRTUAL_32BIT_REG(0x06);
}

	void
BX_CPU_C::Resolve32Mod0EffectAddress_sib0xa7(BX_CPU_C *icpu,bxInstruction_c *i)
{
	RMAddr(i) = READ_VIRTUAL_32BIT_REG(0x07);
}

	void
BX_CPU_C::Resolve32Mod0EffectAddress_sib0xa8(BX_CPU_C *icpu,bxInstruction_c *i)
{
	RMAddr(i) = READ_VIRTUAL_32BIT_REG(0x00) +
		(READ_VIRTUAL_32BIT_REG(0x05) <<0x02);
}

	void
BX_CPU_C::Resolve32Mod0EffectAddress_sib0xa9(BX_CPU_C *icpu,bxInstruction_c *i)
{
	RMAddr(i) = READ_VIRTUAL_32BIT_REG(0x01) +
		(READ_VIRTUAL_32BIT_REG(0x05) <<0x02);
}

	void
BX_CPU_C::Resolve32Mod0EffectAddress_sib0xaa(BX_CPU_C *icpu,bxInstruction_c *i)
{
	RMAddr(i) = READ_VIRTUAL_32BIT_REG(0x02) +
		(READ_VIRTUAL_32BIT_REG(0x05) <<0x02);
}

	void
BX_CPU_C::Resolve32Mod0EffectAddress_sib0xab(BX_CPU_C *icpu,bxInstruction_c *i)
{
	RMAddr(i) = READ_VIRTUAL_32BIT_REG(0x03) +
		(READ_VIRTUAL_32BIT_REG(0x05) <<0x02);
}

	void
BX_CPU_C::Resolve32Mod0EffectAddress_sib0xac(BX_CPU_C *icpu,bxInstruction_c *i)
{
	RMAddr(i) = READ_VIRTUAL_32BIT_REG(0x04) +
		(READ_VIRTUAL_32BIT_REG(0x05) <<0x02);
}

	void
BX_CPU_C::Resolve32Mod0EffectAddress_sib0xad(BX_CPU_C *icpu,bxInstruction_c *i)
{
	RMAddr(i) = (READ_VIRTUAL_32BIT_REG(0x05) <<0x02) +
		i->displ32u;
}

	void
BX_CPU_C::Resolve32Mod0EffectAddress_sib0xae(BX_CPU_C *icpu,bxInstruction_c *i)
{
	RMAddr(i) = READ_VIRTUAL_32BIT_REG(0x06) +
		(READ_VIRTUAL_32BIT_REG(0x05) <<0x02);
}

	void
BX_CPU_C::Resolve32Mod0EffectAddress_sib0xaf(BX_CPU_C *icpu,bxInstruction_c *i)
{
	RMAddr(i) = READ_VIRTUAL_32BIT_REG(0x07) +
		(READ_VIRTUAL_32BIT_REG(0x05) <<0x02);
}

	void
BX_CPU_C::Resolve32Mod0EffectAddress_sib0xb0(BX_CPU_C *icpu,bxInstruction_c *i)
{
	RMAddr(i) = READ_VIRTUAL_32BIT_REG(0x00) +
		(READ_VIRTUAL_32BIT_REG(0x06) <<0x02);
}

	void
BX_CPU_C::Resolve32Mod0EffectAddress_sib0xb1(BX_CPU_C *icpu,bxInstruction_c *i)
{
	RMAddr(i) = READ_VIRTUAL_32BIT_REG(0x01) +
		(READ_VIRTUAL_32BIT_REG(0x06) <<0x02);
}

	void
BX_CPU_C::Resolve32Mod0EffectAddress_sib0xb2(BX_CPU_C *icpu,bxInstruction_c *i)
{
	RMAddr(i) = READ_VIRTUAL_32BIT_REG(0x02) +
		(READ_VIRTUAL_32BIT_REG(0x06) <<0x02);
}

	void
BX_CPU_C::Resolve32Mod0EffectAddress_sib0xb3(BX_CPU_C *icpu,bxInstruction_c *i)
{
	RMAddr(i) = READ_VIRTUAL_32BIT_REG(0x03) +
		(READ_VIRTUAL_32BIT_REG(0x06) <<0x02);
}

	void
BX_CPU_C::Resolve32Mod0EffectAddress_sib0xb4(BX_CPU_C *icpu,bxInstruction_c *i)
{
	RMAddr(i) = READ_VIRTUAL_32BIT_REG(0x04) +
		(READ_VIRTUAL_32BIT_REG(0x06) <<0x02);
}

	void
BX_CPU_C::Resolve32Mod0EffectAddress_sib0xb5(BX_CPU_C *icpu,bxInstruction_c *i)
{
	RMAddr(i) = (READ_VIRTUAL_32BIT_REG(0x06) <<0x02) +
		i->displ32u;
}

	void
BX_CPU_C::Resolve32Mod0EffectAddress_sib0xb6(BX_CPU_C *icpu,bxInstruction_c *i)
{
	RMAddr(i) = READ_VIRTUAL_32BIT_REG(0x06) +
		(READ_VIRTUAL_32BIT_REG(0x06) <<0x02);
}

	void
BX_CPU_C::Resolve32Mod0EffectAddress_sib0xb7(BX_CPU_C *icpu,bxInstruction_c *i)
{
	RMAddr(i) = READ_VIRTUAL_32BIT_REG(0x07) +
		(READ_VIRTUAL_32BIT_REG(0x06) <<0x02);
}

	void
BX_CPU_C::Resolve32Mod0EffectAddress_sib0xb8(BX_CPU_C *icpu,bxInstruction_c *i)
{
	RMAddr(i) = READ_VIRTUAL_32BIT_REG(0x00) +
		(READ_VIRTUAL_32BIT_REG(0x07) <<0x02);
}

	void
BX_CPU_C::Resolve32Mod0EffectAddress_sib0xb9(BX_CPU_C *icpu,bxInstruction_c *i)
{
	RMAddr(i) = READ_VIRTUAL_32BIT_REG(0x01) +
		(READ_VIRTUAL_32BIT_REG(0x07) <<0x02);
}

	void
BX_CPU_C::Resolve32Mod0EffectAddress_sib0xba(BX_CPU_C *icpu,bxInstruction_c *i)
{
	RMAddr(i) = READ_VIRTUAL_32BIT_REG(0x02) +
		(READ_VIRTUAL_32BIT_REG(0x07) <<0x02);
}

	void
BX_CPU_C::Resolve32Mod0EffectAddress_sib0xbb(BX_CPU_C *icpu,bxInstruction_c *i)
{
	RMAddr(i) = READ_VIRTUAL_32BIT_REG(0x03) +
		(READ_VIRTUAL_32BIT_REG(0x07) <<0x02);
}

	void
BX_CPU_C::Resolve32Mod0EffectAddress_sib0xbc(BX_CPU_C *icpu,bxInstruction_c *i)
{
	RMAddr(i) = READ_VIRTUAL_32BIT_REG(0x04) +
		(READ_VIRTUAL_32BIT_REG(0x07) <<0x02);
}

	void
BX_CPU_C::Resolve32Mod0EffectAddress_sib0xbd(BX_CPU_C *icpu,bxInstruction_c *i)
{
	RMAddr(i) = (READ_VIRTUAL_32BIT_REG(0x07) <<0x02) +
		i->displ32u;
}

	void
BX_CPU_C::Resolve32Mod0EffectAddress_sib0xbe(BX_CPU_C *icpu,bxInstruction_c *i)
{
	RMAddr(i) = READ_VIRTUAL_32BIT_REG(0x06) +
		(READ_VIRTUAL_32BIT_REG(0x07) <<0x02);
}

	void
BX_CPU_C::Resolve32Mod0EffectAddress_sib0xbf(BX_CPU_C *icpu,bxInstruction_c *i)
{
	RMAddr(i) = READ_VIRTUAL_32BIT_REG(0x07) +
		(READ_VIRTUAL_32BIT_REG(0x07) <<0x02);
}

	void
BX_CPU_C::Resolve32Mod0EffectAddress_sib0xc0(BX_CPU_C *icpu,bxInstruction_c *i)
{
	RMAddr(i) = READ_VIRTUAL_32BIT_REG(0x00) +
		(READ_VIRTUAL_32BIT_REG(0x00) <<0x03);
}

	void
BX_CPU_C::Resolve32Mod0EffectAddress_sib0xc1(BX_CPU_C *icpu,bxInstruction_c *i)
{
	RMAddr(i) = READ_VIRTUAL_32BIT_REG(0x01) +
		(READ_VIRTUAL_32BIT_REG(0x00) <<0x03);
}

	void
BX_CPU_C::Resolve32Mod0EffectAddress_sib0xc2(BX_CPU_C *icpu,bxInstruction_c *i)
{
	RMAddr(i) = READ_VIRTUAL_32BIT_REG(0x02) +
		(READ_VIRTUAL_32BIT_REG(0x00) <<0x03);
}

	void
BX_CPU_C::Resolve32Mod0EffectAddress_sib0xc3(BX_CPU_C *icpu,bxInstruction_c *i)
{
	RMAddr(i) = READ_VIRTUAL_32BIT_REG(0x03) +
		(READ_VIRTUAL_32BIT_REG(0x00) <<0x03);
}

	void
BX_CPU_C::Resolve32Mod0EffectAddress_sib0xc4(BX_CPU_C *icpu,bxInstruction_c *i)
{
	RMAddr(i) = READ_VIRTUAL_32BIT_REG(0x04) +
		(READ_VIRTUAL_32BIT_REG(0x00) <<0x03);
}

	void
BX_CPU_C::Resolve32Mod0EffectAddress_sib0xc5(BX_CPU_C *icpu,bxInstruction_c *i)
{
	RMAddr(i) = (READ_VIRTUAL_32BIT_REG(0x00) <<0x03) +
		i->displ32u;
}

	void
BX_CPU_C::Resolve32Mod0EffectAddress_sib0xc6(BX_CPU_C *icpu,bxInstruction_c *i)
{
	RMAddr(i) = READ_VIRTUAL_32BIT_REG(0x06) +
		(READ_VIRTUAL_32BIT_REG(0x00) <<0x03);
}

	void
BX_CPU_C::Resolve32Mod0EffectAddress_sib0xc7(BX_CPU_C *icpu,bxInstruction_c *i)
{
	RMAddr(i) = READ_VIRTUAL_32BIT_REG(0x07) +
		(READ_VIRTUAL_32BIT_REG(0x00) <<0x03);
}

	void
BX_CPU_C::Resolve32Mod0EffectAddress_sib0xc8(BX_CPU_C *icpu,bxInstruction_c *i)
{
	RMAddr(i) = READ_VIRTUAL_32BIT_REG(0x00) +
		(READ_VIRTUAL_32BIT_REG(0x01) <<0x03);
}

	void
BX_CPU_C::Resolve32Mod0EffectAddress_sib0xc9(BX_CPU_C *icpu,bxInstruction_c *i)
{
	RMAddr(i) = READ_VIRTUAL_32BIT_REG(0x01) +
		(READ_VIRTUAL_32BIT_REG(0x01) <<0x03);
}

	void
BX_CPU_C::Resolve32Mod0EffectAddress_sib0xca(BX_CPU_C *icpu,bxInstruction_c *i)
{
	RMAddr(i) = READ_VIRTUAL_32BIT_REG(0x02) +
		(READ_VIRTUAL_32BIT_REG(0x01) <<0x03);
}

	void
BX_CPU_C::Resolve32Mod0EffectAddress_sib0xcb(BX_CPU_C *icpu,bxInstruction_c *i)
{
	RMAddr(i) = READ_VIRTUAL_32BIT_REG(0x03) +
		(READ_VIRTUAL_32BIT_REG(0x01) <<0x03);
}

	void
BX_CPU_C::Resolve32Mod0EffectAddress_sib0xcc(BX_CPU_C *icpu,bxInstruction_c *i)
{
	RMAddr(i) = READ_VIRTUAL_32BIT_REG(0x04) +
		(READ_VIRTUAL_32BIT_REG(0x01) <<0x03);
}

	void
BX_CPU_C::Resolve32Mod0EffectAddress_sib0xcd(BX_CPU_C *icpu,bxInstruction_c *i)
{
	RMAddr(i) = (READ_VIRTUAL_32BIT_REG(0x01) <<0x03) +
		i->displ32u;
}

	void
BX_CPU_C::Resolve32Mod0EffectAddress_sib0xce(BX_CPU_C *icpu,bxInstruction_c *i)
{
	RMAddr(i) = READ_VIRTUAL_32BIT_REG(0x06) +
		(READ_VIRTUAL_32BIT_REG(0x01) <<0x03);
}

	void
BX_CPU_C::Resolve32Mod0EffectAddress_sib0xcf(BX_CPU_C *icpu,bxInstruction_c *i)
{
	RMAddr(i) = READ_VIRTUAL_32BIT_REG(0x07) +
		(READ_VIRTUAL_32BIT_REG(0x01) <<0x03);
}

	void
BX_CPU_C::Resolve32Mod0EffectAddress_sib0xd0(BX_CPU_C *icpu,bxInstruction_c *i)
{
	RMAddr(i) = READ_VIRTUAL_32BIT_REG(0x00) +
		(READ_VIRTUAL_32BIT_REG(0x02) <<0x03);
}

	void
BX_CPU_C::Resolve32Mod0EffectAddress_sib0xd1(BX_CPU_C *icpu,bxInstruction_c *i)
{
	RMAddr(i) = READ_VIRTUAL_32BIT_REG(0x01) +
		(READ_VIRTUAL_32BIT_REG(0x02) <<0x03);
}

	void
BX_CPU_C::Resolve32Mod0EffectAddress_sib0xd2(BX_CPU_C *icpu,bxInstruction_c *i)
{
	RMAddr(i) = READ_VIRTUAL_32BIT_REG(0x02) +
		(READ_VIRTUAL_32BIT_REG(0x02) <<0x03);
}

	void
BX_CPU_C::Resolve32Mod0EffectAddress_sib0xd3(BX_CPU_C *icpu,bxInstruction_c *i)
{
	RMAddr(i) = READ_VIRTUAL_32BIT_REG(0x03) +
		(READ_VIRTUAL_32BIT_REG(0x02) <<0x03);
}

	void
BX_CPU_C::Resolve32Mod0EffectAddress_sib0xd4(BX_CPU_C *icpu,bxInstruction_c *i)
{
	RMAddr(i) = READ_VIRTUAL_32BIT_REG(0x04) +
		(READ_VIRTUAL_32BIT_REG(0x02) <<0x03);
}

	void
BX_CPU_C::Resolve32Mod0EffectAddress_sib0xd5(BX_CPU_C *icpu,bxInstruction_c *i)
{
	RMAddr(i) = (READ_VIRTUAL_32BIT_REG(0x02) <<0x03) +
		i->displ32u;
}

	void
BX_CPU_C::Resolve32Mod0EffectAddress_sib0xd6(BX_CPU_C *icpu,bxInstruction_c *i)
{
	RMAddr(i) = READ_VIRTUAL_32BIT_REG(0x06) +
		(READ_VIRTUAL_32BIT_REG(0x02) <<0x03);
}

	void
BX_CPU_C::Resolve32Mod0EffectAddress_sib0xd7(BX_CPU_C *icpu,bxInstruction_c *i)
{
	RMAddr(i) = READ_VIRTUAL_32BIT_REG(0x07) +
		(READ_VIRTUAL_32BIT_REG(0x02) <<0x03);
}

	void
BX_CPU_C::Resolve32Mod0EffectAddress_sib0xd8(BX_CPU_C *icpu,bxInstruction_c *i)
{
	RMAddr(i) = READ_VIRTUAL_32BIT_REG(0x00) +
		(READ_VIRTUAL_32BIT_REG(0x03) <<0x03);
}

	void
BX_CPU_C::Resolve32Mod0EffectAddress_sib0xd9(BX_CPU_C *icpu,bxInstruction_c *i)
{
	RMAddr(i) = READ_VIRTUAL_32BIT_REG(0x01) +
		(READ_VIRTUAL_32BIT_REG(0x03) <<0x03);
}

	void
BX_CPU_C::Resolve32Mod0EffectAddress_sib0xda(BX_CPU_C *icpu,bxInstruction_c *i)
{
	RMAddr(i) = READ_VIRTUAL_32BIT_REG(0x02) +
		(READ_VIRTUAL_32BIT_REG(0x03) <<0x03);
}

	void
BX_CPU_C::Resolve32Mod0EffectAddress_sib0xdb(BX_CPU_C *icpu,bxInstruction_c *i)
{
	RMAddr(i) = READ_VIRTUAL_32BIT_REG(0x03) +
		(READ_VIRTUAL_32BIT_REG(0x03) <<0x03);
}

	void
BX_CPU_C::Resolve32Mod0EffectAddress_sib0xdc(BX_CPU_C *icpu,bxInstruction_c *i)
{
	RMAddr(i) = READ_VIRTUAL_32BIT_REG(0x04) +
		(READ_VIRTUAL_32BIT_REG(0x03) <<0x03);
}

	void
BX_CPU_C::Resolve32Mod0EffectAddress_sib0xdd(BX_CPU_C *icpu,bxInstruction_c *i)
{
	RMAddr(i) = (READ_VIRTUAL_32BIT_REG(0x03) <<0x03) +
		i->displ32u;
}

	void
BX_CPU_C::Resolve32Mod0EffectAddress_sib0xde(BX_CPU_C *icpu,bxInstruction_c *i)
{
	RMAddr(i) = READ_VIRTUAL_32BIT_REG(0x06) +
		(READ_VIRTUAL_32BIT_REG(0x03) <<0x03);
}

	void
BX_CPU_C::Resolve32Mod0EffectAddress_sib0xdf(BX_CPU_C *icpu,bxInstruction_c *i)
{
	RMAddr(i) = READ_VIRTUAL_32BIT_REG(0x07) +
		(READ_VIRTUAL_32BIT_REG(0x03) <<0x03);
}

	void
BX_CPU_C::Resolve32Mod0EffectAddress_sib0xe0(BX_CPU_C *icpu,bxInstruction_c *i)
{
	RMAddr(i) = READ_VIRTUAL_32BIT_REG(0x00);
}

	void
BX_CPU_C::Resolve32Mod0EffectAddress_sib0xe1(BX_CPU_C *icpu,bxInstruction_c *i)
{
	RMAddr(i) = READ_VIRTUAL_32BIT_REG(0x01);
}

	void
BX_CPU_C::Resolve32Mod0EffectAddress_sib0xe2(BX_CPU_C *icpu,bxInstruction_c *i)
{
	RMAddr(i) = READ_VIRTUAL_32BIT_REG(0x02);
}

	void
BX_CPU_C::Resolve32Mod0EffectAddress_sib0xe3(BX_CPU_C *icpu,bxInstruction_c *i)
{
	RMAddr(i) = READ_VIRTUAL_32BIT_REG(0x03);
}

	void
BX_CPU_C::Resolve32Mod0EffectAddress_sib0xe4(BX_CPU_C *icpu,bxInstruction_c *i)
{
	RMAddr(i) = READ_VIRTUAL_32BIT_REG(0x04);
}

	void
BX_CPU_C::Resolve32Mod0EffectAddress_sib0xe5(BX_CPU_C *icpu,bxInstruction_c *i)
{
	// d32, no registers used 
	RMAddr(i) = i->displ32u;
}

	void
BX_CPU_C::Resolve32Mod0EffectAddress_sib0xe6(BX_CPU_C *icpu,bxInstruction_c *i)
{
	RMAddr(i) = READ_VIRTUAL_32BIT_REG(0x06);
}

	void
BX_CPU_C::Resolve32Mod0EffectAddress_sib0xe7(BX_CPU_C *icpu,bxInstruction_c *i)
{
	RMAddr(i) = READ_VIRTUAL_32BIT_REG(0x07);
}

	void
BX_CPU_C::Resolve32Mod0EffectAddress_sib0xe8(BX_CPU_C *icpu,bxInstruction_c *i)
{
	RMAddr(i) = READ_VIRTUAL_32BIT_REG(0x00) +
		(READ_VIRTUAL_32BIT_REG(0x05) <<0x03);
}

	void
BX_CPU_C::Resolve32Mod0EffectAddress_sib0xe9(BX_CPU_C *icpu,bxInstruction_c *i)
{
	RMAddr(i) = READ_VIRTUAL_32BIT_REG(0x01) +
		(READ_VIRTUAL_32BIT_REG(0x05) <<0x03);
}

	void
BX_CPU_C::Resolve32Mod0EffectAddress_sib0xea(BX_CPU_C *icpu,bxInstruction_c *i)
{
	RMAddr(i) = READ_VIRTUAL_32BIT_REG(0x02) +
		(READ_VIRTUAL_32BIT_REG(0x05) <<0x03);
}

	void
BX_CPU_C::Resolve32Mod0EffectAddress_sib0xeb(BX_CPU_C *icpu,bxInstruction_c *i)
{
	RMAddr(i) = READ_VIRTUAL_32BIT_REG(0x03) +
		(READ_VIRTUAL_32BIT_REG(0x05) <<0x03);
}

	void
BX_CPU_C::Resolve32Mod0EffectAddress_sib0xec(BX_CPU_C *icpu,bxInstruction_c *i)
{
	RMAddr(i) = READ_VIRTUAL_32BIT_REG(0x04) +
		(READ_VIRTUAL_32BIT_REG(0x05) <<0x03);
}

	void
BX_CPU_C::Resolve32Mod0EffectAddress_sib0xed(BX_CPU_C *icpu,bxInstruction_c *i)
{
	RMAddr(i) = (READ_VIRTUAL_32BIT_REG(0x05) <<0x03) +
		i->displ32u;
}

	void
BX_CPU_C::Resolve32Mod0EffectAddress_sib0xee(BX_CPU_C *icpu,bxInstruction_c *i)
{
	RMAddr(i) = READ_VIRTUAL_32BIT_REG(0x06) +
		(READ_VIRTUAL_32BIT_REG(0x05) <<0x03);
}

	void
BX_CPU_C::Resolve32Mod0EffectAddress_sib0xef(BX_CPU_C *icpu,bxInstruction_c *i)
{
	RMAddr(i) = READ_VIRTUAL_32BIT_REG(0x07) +
		(READ_VIRTUAL_32BIT_REG(0x05) <<0x03);
}

	void
BX_CPU_C::Resolve32Mod0EffectAddress_sib0xf0(BX_CPU_C *icpu,bxInstruction_c *i)
{
	RMAddr(i) = READ_VIRTUAL_32BIT_REG(0x00) +
		(READ_VIRTUAL_32BIT_REG(0x06) <<0x03);
}

	void
BX_CPU_C::Resolve32Mod0EffectAddress_sib0xf1(BX_CPU_C *icpu,bxInstruction_c *i)
{
	RMAddr(i) = READ_VIRTUAL_32BIT_REG(0x01) +
		(READ_VIRTUAL_32BIT_REG(0x06) <<0x03);
}

	void
BX_CPU_C::Resolve32Mod0EffectAddress_sib0xf2(BX_CPU_C *icpu,bxInstruction_c *i)
{
	RMAddr(i) = READ_VIRTUAL_32BIT_REG(0x02) +
		(READ_VIRTUAL_32BIT_REG(0x06) <<0x03);
}

	void
BX_CPU_C::Resolve32Mod0EffectAddress_sib0xf3(BX_CPU_C *icpu,bxInstruction_c *i)
{
	RMAddr(i) = READ_VIRTUAL_32BIT_REG(0x03) +
		(READ_VIRTUAL_32BIT_REG(0x06) <<0x03);
}

	void
BX_CPU_C::Resolve32Mod0EffectAddress_sib0xf4(BX_CPU_C *icpu,bxInstruction_c *i)
{
	RMAddr(i) = READ_VIRTUAL_32BIT_REG(0x04) +
		(READ_VIRTUAL_32BIT_REG(0x06) <<0x03);
}

	void
BX_CPU_C::Resolve32Mod0EffectAddress_sib0xf5(BX_CPU_C *icpu,bxInstruction_c *i)
{
	RMAddr(i) = (READ_VIRTUAL_32BIT_REG(0x06) <<0x03) +
		i->displ32u;
}

	void
BX_CPU_C::Resolve32Mod0EffectAddress_sib0xf6(BX_CPU_C *icpu,bxInstruction_c *i)
{
	RMAddr(i) = READ_VIRTUAL_32BIT_REG(0x06) +
		(READ_VIRTUAL_32BIT_REG(0x06) <<0x03);
}

	void
BX_CPU_C::Resolve32Mod0EffectAddress_sib0xf7(BX_CPU_C *icpu,bxInstruction_c *i)
{
	RMAddr(i) = READ_VIRTUAL_32BIT_REG(0x07) +
		(READ_VIRTUAL_32BIT_REG(0x06) <<0x03);
}

	void
BX_CPU_C::Resolve32Mod0EffectAddress_sib0xf8(BX_CPU_C *icpu,bxInstruction_c *i)
{
	RMAddr(i) = READ_VIRTUAL_32BIT_REG(0x00) +
		(READ_VIRTUAL_32BIT_REG(0x07) <<0x03);
}

	void
BX_CPU_C::Resolve32Mod0EffectAddress_sib0xf9(BX_CPU_C *icpu,bxInstruction_c *i)
{
	RMAddr(i) = READ_VIRTUAL_32BIT_REG(0x01) +
		(READ_VIRTUAL_32BIT_REG(0x07) <<0x03);
}

	void
BX_CPU_C::Resolve32Mod0EffectAddress_sib0xfa(BX_CPU_C *icpu,bxInstruction_c *i)
{
	RMAddr(i) = READ_VIRTUAL_32BIT_REG(0x02) +
		(READ_VIRTUAL_32BIT_REG(0x07) <<0x03);
}

	void
BX_CPU_C::Resolve32Mod0EffectAddress_sib0xfb(BX_CPU_C *icpu,bxInstruction_c *i)
{
	RMAddr(i) = READ_VIRTUAL_32BIT_REG(0x03) +
		(READ_VIRTUAL_32BIT_REG(0x07) <<0x03);
}

	void
BX_CPU_C::Resolve32Mod0EffectAddress_sib0xfc(BX_CPU_C *icpu,bxInstruction_c *i)
{
	RMAddr(i) = READ_VIRTUAL_32BIT_REG(0x04) +
		(READ_VIRTUAL_32BIT_REG(0x07) <<0x03);
}

	void
BX_CPU_C::Resolve32Mod0EffectAddress_sib0xfd(BX_CPU_C *icpu,bxInstruction_c *i)
{
	RMAddr(i) = (READ_VIRTUAL_32BIT_REG(0x07) <<0x03) +
		i->displ32u;
}

	void
BX_CPU_C::Resolve32Mod0EffectAddress_sib0xfe(BX_CPU_C *icpu,bxInstruction_c *i)
{
	RMAddr(i) = READ_VIRTUAL_32BIT_REG(0x06) +
		(READ_VIRTUAL_32BIT_REG(0x07) <<0x03);
}

	void
BX_CPU_C::Resolve32Mod0EffectAddress_sib0xff(BX_CPU_C *icpu,bxInstruction_c *i)
{
	RMAddr(i) = READ_VIRTUAL_32BIT_REG(0x07) +
		(READ_VIRTUAL_32BIT_REG(0x07) <<0x03);
}

