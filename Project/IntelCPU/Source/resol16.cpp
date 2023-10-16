/////////////////////////////////////////////////////////////////////////
// $Id: resolve16.cc,v 1.5 2001/10/03 13:10:37 bdenney Exp $
/////////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "x86cpu.h"

	void
BX_CPU_C::Resolve16Mod0Rm0(BX_CPU_C *icpu,bxInstruction_c *i)
{
	RMAddr(i) = (Bit16u) (RW_BX + RW_SI);
}
	void
BX_CPU_C::Resolve16Mod0Rm1(BX_CPU_C *icpu,bxInstruction_c *i)
{
	RMAddr(i) = (Bit16u) (RW_BX + RW_DI);
}
	void
BX_CPU_C::Resolve16Mod0Rm2(BX_CPU_C *icpu,bxInstruction_c *i)
{
	RMAddr(i) = (Bit16u) (RW_BP + RW_SI);
}
	void
BX_CPU_C::Resolve16Mod0Rm3(BX_CPU_C *icpu,bxInstruction_c *i)
{
	RMAddr(i) = (Bit16u) (RW_BP + RW_DI);
}
	void
BX_CPU_C::Resolve16Mod0Rm4(BX_CPU_C *icpu,bxInstruction_c *i)
{
	RMAddr(i) = (Bit16u) RW_SI;
}
	void
BX_CPU_C::Resolve16Mod0Rm5(BX_CPU_C *icpu,bxInstruction_c *i)
{
	RMAddr(i) = (Bit16u) RW_DI;
}

	void
BX_CPU_C::Resolve16Mod0Rm6(BX_CPU_C *icpu,bxInstruction_c *i)
{
	// d16, no registers used
	RMAddr(i) = (Bit16u) i->displ16u;
}
	void
BX_CPU_C::Resolve16Mod0Rm7(BX_CPU_C *icpu,bxInstruction_c *i)
{
	RMAddr(i) = (Bit16u) RW_BX;
}

	void
BX_CPU_C::Resolve16Mod1or2Rm0(BX_CPU_C *icpu,bxInstruction_c *i)
{
	RMAddr(i) = (Bit16u) (RW_BX + RW_SI + i->displ16u);
}
	void
BX_CPU_C::Resolve16Mod1or2Rm1(BX_CPU_C *icpu,bxInstruction_c *i)
{
	RMAddr(i) = (Bit16u) (RW_BX + RW_DI + i->displ16u);
}
	void
BX_CPU_C::Resolve16Mod1or2Rm2(BX_CPU_C *icpu,bxInstruction_c *i)
{
	RMAddr(i) = (Bit16u) (RW_BP + RW_SI + i->displ16u);
}
	void
BX_CPU_C::Resolve16Mod1or2Rm3(BX_CPU_C *icpu,bxInstruction_c *i)
{
	RMAddr(i) = (Bit16u) (RW_BP + RW_DI + i->displ16u);
}
	void
BX_CPU_C::Resolve16Mod1or2Rm4(BX_CPU_C *icpu,bxInstruction_c *i)
{
	RMAddr(i) = (Bit16u) (RW_SI + i->displ16u);
}
	void
BX_CPU_C::Resolve16Mod1or2Rm5(BX_CPU_C *icpu,bxInstruction_c *i)
{
	RMAddr(i) = (Bit16u) (RW_DI + i->displ16u);
}
	void
BX_CPU_C::Resolve16Mod1or2Rm6(BX_CPU_C *icpu,bxInstruction_c *i)
{
	RMAddr(i) = (Bit16u) (RW_BP + i->displ16u);
}
	void
BX_CPU_C::Resolve16Mod1or2Rm7(BX_CPU_C *icpu,bxInstruction_c *i)
{
	RMAddr(i) = (Bit16u) (RW_BX + i->displ16u);
}

//------------------------------------------------

