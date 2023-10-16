/////////////////////////////////////////////////////////////////////////
// $Id: protect_ctrl_pro.cc,v 1.6 2001/10/03 13:10:37 bdenney Exp $
/////////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "x86cpu.h"

	void
BX_CPU_C::enter_protected_mode(void)
{
// BX_INFO(("processor switching into PROTECTED mode!!!"));
// debug(BX_CPU_THIS_PTR prev_eip);
	if (v8086_mode())
		BX_PANIC(("protect_ctrl: v8086 mode unsupported"));

	if (bx_dbg.reset)
		BX_INFO(("processor switching into PROTECTED mode!!!"));

	if ( BX_CPU_THIS_PTR program_visible_sregs[BX_SEG_REG_CS].selector.rpl!=0 || BX_CPU_THIS_PTR program_visible_sregs[BX_SEG_REG_SS].selector.rpl!=0 )
		BX_PANIC(("enter_protected_mode: CS or SS rpl != 0"));
}


  void
BX_CPU_C::enter_real_mode(void)
{
// ???
// BX_INFO(("processor switching into REAL mode!!!"));
// debug(BX_CPU_THIS_PTR prev_eip);
	if (v8086_mode())
		BX_PANIC(("protect_ctrl: v8086 mode unsupported"));

	if (bx_dbg.reset)
		BX_INFO(("processor switching into REAL mode!!!"));

	if ( BX_CPU_THIS_PTR program_visible_sregs[BX_SEG_REG_CS].selector.rpl!=0 || BX_CPU_THIS_PTR program_visible_sregs[BX_SEG_REG_SS].selector.rpl!=0 )
		BX_PANIC(("enter_real_mode: CS or SS rpl != 0"));
}
