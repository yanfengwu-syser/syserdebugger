/////////////////////////////////////////////////////////////////////////
// $Id: bit.cc,v 1.0 2002/10/10 04:57:05 bdenney Exp $
/////////////////////////////////////////////////////////////////////////


#include "stdafx.h"
#include "x86cpu.h"
//---------------------------------------------------------
//虚拟执行--指令微函数  位操作指令
//---------------------------------------------------------


	void
BX_CPU_C::BSF_GwEGw(BX_CPU_C *icpu,bxInstruction_c *i)
{
#if BX_CPU_LEVEL < 3
	BX_PANIC(("BSF_GwEGw(): not supported on < 386"))
#else
	Bit16u op1,op2;

    op2 = READ_VIRTUAL_16BIT_REG(MODRMrm(i));

	if (op2 == 0)
	{
		BX_CPU_CLASS_PTR set_ZF(1);
		/* op1 undefined */
	    return;
	}
	op1 = 0;
	while ( (op2 & 0x01) == 0 )
	{
		op1++;
		op2 >>= 1;
	}

	BX_CPU_CLASS_PTR set_ZF(0);
	WRITE_VIRTUAL_16BIT_REG(MODRMnnn(i),op1);
#endif
}

	void
BX_CPU_C::BSF_GdEGd(BX_CPU_C *icpu,bxInstruction_c *i)
{
#if BX_CPU_LEVEL < 3
	BX_PANIC(("BSF_GdEGd(): not supported on < 386"))
#else
	Bit32u op1,op2;

    op2 = READ_VIRTUAL_32BIT_REG(MODRMrm(i));

	if (op2 == 0)
	{
		BX_CPU_CLASS_PTR set_ZF(1);
		/* op1 undefined */
	    return;
	}
	op1 = 0;
	while ( (op2 & 0x01) == 0 )
	{
		op1++;
		op2 >>= 1;
	}

	BX_CPU_CLASS_PTR set_ZF(0);
	WRITE_VIRTUAL_32BIT_REG(MODRMnnn(i),op1);
#endif
}

	void
BX_CPU_C::BSR_GwEGw(BX_CPU_C *icpu,bxInstruction_c *i)
{
#if BX_CPU_LEVEL < 3
	BX_PANIC(("BSR_GwEGw(): not supported on < 386"))
#else
	Bit16u op1,op2;

    op2 = READ_VIRTUAL_16BIT_REG(MODRMrm(i));

	if (op2 == 0)
	{
		BX_CPU_CLASS_PTR set_ZF(1);
		/* op1 undefined */
	    return;
	}
	op1 = (16-1);
	while ( (op2 & (1<<(16-1)))== 0 )
	{
		op1--;
		op2 <<= 1;
	}

	BX_CPU_CLASS_PTR set_ZF(0);
	WRITE_VIRTUAL_16BIT_REG(MODRMnnn(i),op1);
#endif
}

	void
BX_CPU_C::BSR_GdEGd(BX_CPU_C *icpu,bxInstruction_c *i)
{
#if BX_CPU_LEVEL < 3
	BX_PANIC(("BSR_GdEGd(): not supported on < 386"))
#else
	Bit32u op1,op2;

    op2 = READ_VIRTUAL_32BIT_REG(MODRMrm(i));

	if (op2 == 0)
	{
		BX_CPU_CLASS_PTR set_ZF(1);
		/* op1 undefined */
	    return;
	}
	op1 = (32-1);
	while ( (op2 & (1<<(32-1)))== 0 )
	{
		op1--;
		op2 <<= 1;
	}

	BX_CPU_CLASS_PTR set_ZF(0);
	WRITE_VIRTUAL_32BIT_REG(MODRMnnn(i),op1);
#endif
}

	void
BX_CPU_C::BSF_GwEEw(BX_CPU_C *icpu,bxInstruction_c *i)
{
#if BX_CPU_LEVEL < 3
	BX_PANIC(("BSF_GwEEw(): not supported on < 386"))
#else
	Bit16u op1,op2;

    READ_VIRTUAL_WORD(MODRMSeg(i),RMAddr(i),&op2);

	if (op2 == 0)
	{
		BX_CPU_CLASS_PTR set_ZF(1);
		/* op1 undefined */
	    return;
	}
	op1 = 0;
	while ( (op2 & 0x01) == 0 )
	{
		op1++;
		op2 >>= 1;
	}

	BX_CPU_CLASS_PTR set_ZF(0);
	WRITE_VIRTUAL_16BIT_REG(MODRMnnn(i),op1);
#endif
}

	void
BX_CPU_C::BSF_GdEEd(BX_CPU_C *icpu,bxInstruction_c *i)
{
#if BX_CPU_LEVEL < 3
	BX_PANIC(("BSF_GdEEd(): not supported on < 386"))
#else
	Bit32u op1,op2;

    READ_VIRTUAL_DWORD(MODRMSeg(i),RMAddr(i),&op2);

	if (op2 == 0)
	{
		BX_CPU_CLASS_PTR set_ZF(1);
		/* op1 undefined */
	    return;
	}
	op1 = 0;
	while ( (op2 & 0x01) == 0 )
	{
		op1++;
		op2 >>= 1;
	}

	BX_CPU_CLASS_PTR set_ZF(0);
	WRITE_VIRTUAL_32BIT_REG(MODRMnnn(i),op1);
#endif
}

	void
BX_CPU_C::BSR_GwEEw(BX_CPU_C *icpu,bxInstruction_c *i)
{
#if BX_CPU_LEVEL < 3
	BX_PANIC(("BSR_GwEEw(): not supported on < 386"))
#else
	Bit16u op1,op2;

    READ_VIRTUAL_WORD(MODRMSeg(i),RMAddr(i),&op2);

	if (op2 == 0)
	{
		BX_CPU_CLASS_PTR set_ZF(1);
		/* op1 undefined */
	    return;
	}
	op1 = (16-1);
	while ( (op2 & (1<<(16-1)))== 0 )
	{
		op1--;
		op2 <<= 1;
	}

	BX_CPU_CLASS_PTR set_ZF(0);
	WRITE_VIRTUAL_16BIT_REG(MODRMnnn(i),op1);
#endif
}

	void
BX_CPU_C::BSR_GdEEd(BX_CPU_C *icpu,bxInstruction_c *i)
{
#if BX_CPU_LEVEL < 3
	BX_PANIC(("BSR_GdEEd(): not supported on < 386"))
#else
	Bit32u op1,op2;

    READ_VIRTUAL_DWORD(MODRMSeg(i),RMAddr(i),&op2);

	if (op2 == 0)
	{
		BX_CPU_CLASS_PTR set_ZF(1);
		/* op1 undefined */
	    return;
	}
	op1 = (32-1);
	while ( (op2 & (1<<(32-1)))== 0 )
	{
		op1--;
		op2 <<= 1;
	}

	BX_CPU_CLASS_PTR set_ZF(0);
	WRITE_VIRTUAL_32BIT_REG(MODRMnnn(i),op1);
#endif
}

	void
BX_CPU_C::BT_EGwGw(BX_CPU_C *icpu,bxInstruction_c *i)
{
#if BX_CPU_LEVEL < 3
	BX_PANIC(("BT_EGwGw: not available on <386"));
#else
	Bit16u op1,op2,index,temp_cf;

	op2 = READ_VIRTUAL_16BIT_REG(MODRMnnn(i));
    index = op2 & (16-1);
    op1 = READ_VIRTUAL_16BIT_REG(MODRMrm(i));

    temp_cf = (op1 >> index) & 0x01;

    BX_CPU_CLASS_PTR set_CF(temp_cf);
#endif
}

	void
BX_CPU_C::BT_EGdGd(BX_CPU_C *icpu,bxInstruction_c *i)
{
#if BX_CPU_LEVEL < 3
	BX_PANIC(("BT_EGdGd: not available on <386"));
#else
	Bit32u op1,op2,index,temp_cf;

	op2 = READ_VIRTUAL_32BIT_REG(MODRMnnn(i));
    index = op2 & (32-1);
    op1 = READ_VIRTUAL_32BIT_REG(MODRMrm(i));

    temp_cf = (op1 >> index) & 0x01;

    BX_CPU_CLASS_PTR set_CF(temp_cf);
#endif
}

	void
BX_CPU_C::BT_EGwIb(BX_CPU_C *icpu,bxInstruction_c *i)
{
#if BX_CPU_LEVEL < 3
	BX_PANIC(("BT_EGwIb: not available on <386"));
#else
	Bit16u op1,op2,index,temp_cf;

	op2 = IMMEDIATEIb(i) & (16-1);
    index = op2 & (16-1);
    op1 = READ_VIRTUAL_16BIT_REG(MODRMrm(i));

    temp_cf = (op1 >> index) & 0x01;

    BX_CPU_CLASS_PTR set_CF(temp_cf);
#endif
}

	void
BX_CPU_C::BT_EGdIb(BX_CPU_C *icpu,bxInstruction_c *i)
{
#if BX_CPU_LEVEL < 3
	BX_PANIC(("BT_EGdIb: not available on <386"));
#else
	Bit32u op1,op2,index,temp_cf;

	op2 = IMMEDIATEIb(i) & (32-1);
    index = op2 & (32-1);
    op1 = READ_VIRTUAL_32BIT_REG(MODRMrm(i));

    temp_cf = (op1 >> index) & 0x01;

    BX_CPU_CLASS_PTR set_CF(temp_cf);
#endif
}

	void
BX_CPU_C::BT_EEwGw(BX_CPU_C *icpu,bxInstruction_c *i)
{
#if BX_CPU_LEVEL < 3
	BX_PANIC(("BT_EEwGw: not available on <386"));
#else
	Bit16u op1,op2,index,temp_cf;

	op2 = READ_VIRTUAL_16BIT_REG(MODRMnnn(i));
    index = op2 & (16-1);
    RMAddr(i) += 2 * (((Bit16s) (op2 & (0-16))) / 16);
    READ_VIRTUAL_WORD(MODRMSeg(i),RMAddr(i),&op1);

    temp_cf = (op1 >> index) & 0x01;

    BX_CPU_CLASS_PTR set_CF(temp_cf);
#endif
}

	void
BX_CPU_C::BT_EEdGd(BX_CPU_C *icpu,bxInstruction_c *i)
{
#if BX_CPU_LEVEL < 3
	BX_PANIC(("BT_EEdGd: not available on <386"));
#else
	Bit32u op1,op2,index,temp_cf;

	op2 = READ_VIRTUAL_32BIT_REG(MODRMnnn(i));
    index = op2 & (32-1);
    RMAddr(i) += 4 * (((Bit32s) (op2 & (0-32))) / 32);
    READ_VIRTUAL_DWORD(MODRMSeg(i),RMAddr(i),&op1);

    temp_cf = (op1 >> index) & 0x01;

    BX_CPU_CLASS_PTR set_CF(temp_cf);
#endif
}

	void
BX_CPU_C::BT_EEwIb(BX_CPU_C *icpu,bxInstruction_c *i)
{
#if BX_CPU_LEVEL < 3
	BX_PANIC(("BT_EEwIb: not available on <386"));
#else
	Bit16u op1,op2,index,temp_cf;

	op2 = IMMEDIATEIb(i) & (16-1);
    index = op2 & (16-1);
    READ_VIRTUAL_WORD(MODRMSeg(i),RMAddr(i),&op1);

    temp_cf = (op1 >> index) & 0x01;

    BX_CPU_CLASS_PTR set_CF(temp_cf);
#endif
}

	void
BX_CPU_C::BT_EEdIb(BX_CPU_C *icpu,bxInstruction_c *i)
{
#if BX_CPU_LEVEL < 3
	BX_PANIC(("BT_EEdIb: not available on <386"));
#else
	Bit32u op1,op2,index,temp_cf;

	op2 = IMMEDIATEIb(i) & (32-1);
    index = op2 & (32-1);
    READ_VIRTUAL_DWORD(MODRMSeg(i),RMAddr(i),&op1);

    temp_cf = (op1 >> index) & 0x01;

    BX_CPU_CLASS_PTR set_CF(temp_cf);
#endif
}

	void
BX_CPU_C::BTS_EGwGw(BX_CPU_C *icpu,bxInstruction_c *i)
{
#if BX_CPU_LEVEL < 3
	BX_PANIC(("BTS_EGwGw: not available on <386"));
#else
	Bit16u op1,op2,index,temp_cf;

	op2 = READ_VIRTUAL_16BIT_REG(MODRMnnn(i));
    index = op2 & (16-1);
    op1 = READ_VIRTUAL_16BIT_REG(MODRMrm(i));

    temp_cf = (op1 >> index) & 0x01;
    op1 |= (((Bit16u) 1) << index);

    WRITE_VIRTUAL_16BIT_REG(MODRMrm(i),op1);
    BX_CPU_CLASS_PTR set_CF(temp_cf);
#endif
}

	void
BX_CPU_C::BTS_EGdGd(BX_CPU_C *icpu,bxInstruction_c *i)
{
#if BX_CPU_LEVEL < 3
	BX_PANIC(("BTS_EGdGd: not available on <386"));
#else
	Bit32u op1,op2,index,temp_cf;

	op2 = READ_VIRTUAL_32BIT_REG(MODRMnnn(i));
    index = op2 & (32-1);
    op1 = READ_VIRTUAL_32BIT_REG(MODRMrm(i));

    temp_cf = (op1 >> index) & 0x01;
    op1 |= (((Bit32u) 1) << index);

    WRITE_VIRTUAL_32BIT_REG(MODRMrm(i),op1);
    BX_CPU_CLASS_PTR set_CF(temp_cf);
#endif
}

	void
BX_CPU_C::BTS_EGwIb(BX_CPU_C *icpu,bxInstruction_c *i)
{
#if BX_CPU_LEVEL < 3
	BX_PANIC(("BTS_EGwIb: not available on <386"));
#else
	Bit16u op1,op2,index,temp_cf;

	op2 = IMMEDIATEIb(i) & (16-1);
    index = op2 & (16-1);
    op1 = READ_VIRTUAL_16BIT_REG(MODRMrm(i));

    temp_cf = (op1 >> index) & 0x01;
    op1 |= (((Bit16u) 1) << index);

    WRITE_VIRTUAL_16BIT_REG(MODRMrm(i),op1);
    BX_CPU_CLASS_PTR set_CF(temp_cf);
#endif
}

	void
BX_CPU_C::BTS_EGdIb(BX_CPU_C *icpu,bxInstruction_c *i)
{
#if BX_CPU_LEVEL < 3
	BX_PANIC(("BTS_EGdIb: not available on <386"));
#else
	Bit32u op1,op2,index,temp_cf;

	op2 = IMMEDIATEIb(i) & (32-1);
    index = op2 & (32-1);
    op1 = READ_VIRTUAL_32BIT_REG(MODRMrm(i));

    temp_cf = (op1 >> index) & 0x01;
    op1 |= (((Bit32u) 1) << index);

    WRITE_VIRTUAL_32BIT_REG(MODRMrm(i),op1);
    BX_CPU_CLASS_PTR set_CF(temp_cf);
#endif
}

	void
BX_CPU_C::BTS_EEwGw(BX_CPU_C *icpu,bxInstruction_c *i)
{
#if BX_CPU_LEVEL < 3
	BX_PANIC(("BTS_EEwGw: not available on <386"));
#else
	Bit16u op1,op2,index,temp_cf;

	op2 = READ_VIRTUAL_16BIT_REG(MODRMnnn(i));
    index = op2 & (16-1);
    RMAddr(i) += 2 * (((Bit16s) (op2 & (0-16))) / 16);
    READ_RMW_VIRTUAL_WORD(MODRMSeg(i),RMAddr(i),&op1);

    temp_cf = (op1 >> index) & 0x01;
    op1 |= (((Bit16u) 1) << index);

    WRITE_RMW_VIRTUAL_WORD(op1);
    BX_CPU_CLASS_PTR set_CF(temp_cf);
#endif
}

	void
BX_CPU_C::BTS_EEdGd(BX_CPU_C *icpu,bxInstruction_c *i)
{
#if BX_CPU_LEVEL < 3
	BX_PANIC(("BTS_EEdGd: not available on <386"));
#else
	Bit32u op1,op2,index,temp_cf;

	op2 = READ_VIRTUAL_32BIT_REG(MODRMnnn(i));
    index = op2 & (32-1);
    RMAddr(i) += 4 * (((Bit32s) (op2 & (0-32))) / 32);
    READ_RMW_VIRTUAL_DWORD(MODRMSeg(i),RMAddr(i),&op1);

    temp_cf = (op1 >> index) & 0x01;
    op1 |= (((Bit32u) 1) << index);

    WRITE_RMW_VIRTUAL_DWORD(op1);
    BX_CPU_CLASS_PTR set_CF(temp_cf);
#endif
}

	void
BX_CPU_C::BTS_EEwIb(BX_CPU_C *icpu,bxInstruction_c *i)
{
#if BX_CPU_LEVEL < 3
	BX_PANIC(("BTS_EEwIb: not available on <386"));
#else
	Bit16u op1,op2,index,temp_cf;

	op2 = IMMEDIATEIb(i) & (16-1);
    index = op2 & (16-1);
    READ_RMW_VIRTUAL_WORD(MODRMSeg(i),RMAddr(i),&op1);

    temp_cf = (op1 >> index) & 0x01;
    op1 |= (((Bit16u) 1) << index);

    WRITE_RMW_VIRTUAL_WORD(op1);
    BX_CPU_CLASS_PTR set_CF(temp_cf);
#endif
}

	void
BX_CPU_C::BTS_EEdIb(BX_CPU_C *icpu,bxInstruction_c *i)
{
#if BX_CPU_LEVEL < 3
	BX_PANIC(("BTS_EEdIb: not available on <386"));
#else
	Bit32u op1,op2,index,temp_cf;

	op2 = IMMEDIATEIb(i) & (32-1);
    index = op2 & (32-1);
    READ_RMW_VIRTUAL_DWORD(MODRMSeg(i),RMAddr(i),&op1);

    temp_cf = (op1 >> index) & 0x01;
    op1 |= (((Bit32u) 1) << index);

    WRITE_RMW_VIRTUAL_DWORD(op1);
    BX_CPU_CLASS_PTR set_CF(temp_cf);
#endif
}

	void
BX_CPU_C::BTR_EGwGw(BX_CPU_C *icpu,bxInstruction_c *i)
{
#if BX_CPU_LEVEL < 3
	BX_PANIC(("BTR_EGwGw: not available on <386"));
#else
	Bit16u op1,op2,index,temp_cf;

	op2 = READ_VIRTUAL_16BIT_REG(MODRMnnn(i));
    index = op2 & (16-1);
    op1 = READ_VIRTUAL_16BIT_REG(MODRMrm(i));

    temp_cf = (op1 >> index) & 0x01;
    op1 &= ~(((Bit16u) 1) << index);

    WRITE_VIRTUAL_16BIT_REG(MODRMrm(i),op1);
    BX_CPU_CLASS_PTR set_CF(temp_cf);
#endif
}

	void
BX_CPU_C::BTR_EGdGd(BX_CPU_C *icpu,bxInstruction_c *i)
{
#if BX_CPU_LEVEL < 3
	BX_PANIC(("BTR_EGdGd: not available on <386"));
#else
	Bit32u op1,op2,index,temp_cf;

	op2 = READ_VIRTUAL_32BIT_REG(MODRMnnn(i));
    index = op2 & (32-1);
    op1 = READ_VIRTUAL_32BIT_REG(MODRMrm(i));

    temp_cf = (op1 >> index) & 0x01;
    op1 &= ~(((Bit32u) 1) << index);

    WRITE_VIRTUAL_32BIT_REG(MODRMrm(i),op1);
    BX_CPU_CLASS_PTR set_CF(temp_cf);
#endif
}

	void
BX_CPU_C::BTR_EGwIb(BX_CPU_C *icpu,bxInstruction_c *i)
{
#if BX_CPU_LEVEL < 3
	BX_PANIC(("BTR_EGwIb: not available on <386"));
#else
	Bit16u op1,op2,index,temp_cf;

	op2 = IMMEDIATEIb(i) & (16-1);
    index = op2 & (16-1);
    op1 = READ_VIRTUAL_16BIT_REG(MODRMrm(i));

    temp_cf = (op1 >> index) & 0x01;
    op1 &= ~(((Bit16u) 1) << index);

    WRITE_VIRTUAL_16BIT_REG(MODRMrm(i),op1);
    BX_CPU_CLASS_PTR set_CF(temp_cf);
#endif
}

	void
BX_CPU_C::BTR_EGdIb(BX_CPU_C *icpu,bxInstruction_c *i)
{
#if BX_CPU_LEVEL < 3
	BX_PANIC(("BTR_EGdIb: not available on <386"));
#else
	Bit32u op1,op2,index,temp_cf;

	op2 = IMMEDIATEIb(i) & (32-1);
    index = op2 & (32-1);
    op1 = READ_VIRTUAL_32BIT_REG(MODRMrm(i));

    temp_cf = (op1 >> index) & 0x01;
    op1 &= ~(((Bit32u) 1) << index);

    WRITE_VIRTUAL_32BIT_REG(MODRMrm(i),op1);
    BX_CPU_CLASS_PTR set_CF(temp_cf);
#endif
}

	void
BX_CPU_C::BTR_EEwGw(BX_CPU_C *icpu,bxInstruction_c *i)
{
#if BX_CPU_LEVEL < 3
	BX_PANIC(("BTR_EEwGw: not available on <386"));
#else
	Bit16u op1,op2,index,temp_cf;

	op2 = READ_VIRTUAL_16BIT_REG(MODRMnnn(i));
    index = op2 & (16-1);
    RMAddr(i) += 2 * (((Bit16s) (op2 & (0-16))) / 16);
    READ_RMW_VIRTUAL_WORD(MODRMSeg(i),RMAddr(i),&op1);

    temp_cf = (op1 >> index) & 0x01;
    op1 &= ~(((Bit16u) 1) << index);

    WRITE_RMW_VIRTUAL_WORD(op1);
    BX_CPU_CLASS_PTR set_CF(temp_cf);
#endif
}

	void
BX_CPU_C::BTR_EEdGd(BX_CPU_C *icpu,bxInstruction_c *i)
{
#if BX_CPU_LEVEL < 3
	BX_PANIC(("BTR_EEdGd: not available on <386"));
#else
	Bit32u op1,op2,index,temp_cf;

	op2 = READ_VIRTUAL_32BIT_REG(MODRMnnn(i));
    index = op2 & (32-1);
    RMAddr(i) += 4 * (((Bit32s) (op2 & (0-32))) / 32);
    READ_RMW_VIRTUAL_DWORD(MODRMSeg(i),RMAddr(i),&op1);

    temp_cf = (op1 >> index) & 0x01;
    op1 &= ~(((Bit32u) 1) << index);

    WRITE_RMW_VIRTUAL_DWORD(op1);
    BX_CPU_CLASS_PTR set_CF(temp_cf);
#endif
}

	void
BX_CPU_C::BTR_EEwIb(BX_CPU_C *icpu,bxInstruction_c *i)
{
#if BX_CPU_LEVEL < 3
	BX_PANIC(("BTR_EEwIb: not available on <386"));
#else
	Bit16u op1,op2,index,temp_cf;

	op2 = IMMEDIATEIb(i) & (16-1);
    index = op2 & (16-1);
    READ_RMW_VIRTUAL_WORD(MODRMSeg(i),RMAddr(i),&op1);

    temp_cf = (op1 >> index) & 0x01;
    op1 &= ~(((Bit16u) 1) << index);

    WRITE_RMW_VIRTUAL_WORD(op1);
    BX_CPU_CLASS_PTR set_CF(temp_cf);
#endif
}

	void
BX_CPU_C::BTR_EEdIb(BX_CPU_C *icpu,bxInstruction_c *i)
{
#if BX_CPU_LEVEL < 3
	BX_PANIC(("BTR_EEdIb: not available on <386"));
#else
	Bit32u op1,op2,index,temp_cf;

	op2 = IMMEDIATEIb(i) & (32-1);
    index = op2 & (32-1);
    READ_RMW_VIRTUAL_DWORD(MODRMSeg(i),RMAddr(i),&op1);

    temp_cf = (op1 >> index) & 0x01;
    op1 &= ~(((Bit32u) 1) << index);

    WRITE_RMW_VIRTUAL_DWORD(op1);
    BX_CPU_CLASS_PTR set_CF(temp_cf);
#endif
}

	void
BX_CPU_C::BTC_EGwGw(BX_CPU_C *icpu,bxInstruction_c *i)
{
#if BX_CPU_LEVEL < 3
	BX_PANIC(("BTC_EGwGw: not available on <386"));
#else
	Bit16u op1,op2,index,temp_cf;

	op2 = READ_VIRTUAL_16BIT_REG(MODRMnnn(i));
    index = op2 & (16-1);
    op1 = READ_VIRTUAL_16BIT_REG(MODRMrm(i));

    temp_cf = (op1 >> index) & 0x01;
    op1 &= ~(((Bit16u) 1) << index);
    op1 |= (((Bit16u) !temp_cf) << index);

    WRITE_VIRTUAL_16BIT_REG(MODRMrm(i),op1);
    BX_CPU_CLASS_PTR set_CF(temp_cf);
#endif
}

	void
BX_CPU_C::BTC_EGdGd(BX_CPU_C *icpu,bxInstruction_c *i)
{
#if BX_CPU_LEVEL < 3
	BX_PANIC(("BTC_EGdGd: not available on <386"));
#else
	Bit32u op1,op2,index,temp_cf;

	op2 = READ_VIRTUAL_32BIT_REG(MODRMnnn(i));
    index = op2 & (32-1);
    op1 = READ_VIRTUAL_32BIT_REG(MODRMrm(i));

    temp_cf = (op1 >> index) & 0x01;
    op1 &= ~(((Bit32u) 1) << index);
    op1 |= (((Bit32u) !temp_cf) << index);

    WRITE_VIRTUAL_32BIT_REG(MODRMrm(i),op1);
    BX_CPU_CLASS_PTR set_CF(temp_cf);
#endif
}

	void
BX_CPU_C::BTC_EGwIb(BX_CPU_C *icpu,bxInstruction_c *i)
{
#if BX_CPU_LEVEL < 3
	BX_PANIC(("BTC_EGwIb: not available on <386"));
#else
	Bit16u op1,op2,index,temp_cf;

	op2 = IMMEDIATEIb(i) & (16-1);
    index = op2 & (16-1);
    op1 = READ_VIRTUAL_16BIT_REG(MODRMrm(i));

    temp_cf = (op1 >> index) & 0x01;
    op1 &= ~(((Bit16u) 1) << index);
    op1 |= (((Bit16u) !temp_cf) << index);

    WRITE_VIRTUAL_16BIT_REG(MODRMrm(i),op1);
    BX_CPU_CLASS_PTR set_CF(temp_cf);
#endif
}

	void
BX_CPU_C::BTC_EGdIb(BX_CPU_C *icpu,bxInstruction_c *i)
{
#if BX_CPU_LEVEL < 3
	BX_PANIC(("BTC_EGdIb: not available on <386"));
#else
	Bit32u op1,op2,index,temp_cf;

	op2 = IMMEDIATEIb(i) & (32-1);
    index = op2 & (32-1);
    op1 = READ_VIRTUAL_32BIT_REG(MODRMrm(i));

    temp_cf = (op1 >> index) & 0x01;
    op1 &= ~(((Bit32u) 1) << index);
    op1 |= (((Bit32u) !temp_cf) << index);

    WRITE_VIRTUAL_32BIT_REG(MODRMrm(i),op1);
    BX_CPU_CLASS_PTR set_CF(temp_cf);
#endif
}

	void
BX_CPU_C::BTC_EEwGw(BX_CPU_C *icpu,bxInstruction_c *i)
{
#if BX_CPU_LEVEL < 3
	BX_PANIC(("BTC_EEwGw: not available on <386"));
#else
	Bit16u op1,op2,index,temp_cf;

	op2 = READ_VIRTUAL_16BIT_REG(MODRMnnn(i));
    index = op2 & (16-1);
    RMAddr(i) += 2 * (((Bit16s) (op2 & (0-16))) / 16);
    READ_RMW_VIRTUAL_WORD(MODRMSeg(i),RMAddr(i),&op1);

    temp_cf = (op1 >> index) & 0x01;
    op1 &= ~(((Bit16u) 1) << index);
    op1 |= (((Bit16u) !temp_cf) << index);

    WRITE_RMW_VIRTUAL_WORD(op1);
    BX_CPU_CLASS_PTR set_CF(temp_cf);
#endif
}

	void
BX_CPU_C::BTC_EEdGd(BX_CPU_C *icpu,bxInstruction_c *i)
{
#if BX_CPU_LEVEL < 3
	BX_PANIC(("BTC_EEdGd: not available on <386"));
#else
	Bit32u op1,op2,index,temp_cf;

	op2 = READ_VIRTUAL_32BIT_REG(MODRMnnn(i));
    index = op2 & (32-1);
    RMAddr(i) += 4 * (((Bit32s) (op2 & (0-32))) / 32);
    READ_RMW_VIRTUAL_DWORD(MODRMSeg(i),RMAddr(i),&op1);

    temp_cf = (op1 >> index) & 0x01;
    op1 &= ~(((Bit32u) 1) << index);
    op1 |= (((Bit32u) !temp_cf) << index);

    WRITE_RMW_VIRTUAL_DWORD(op1);
    BX_CPU_CLASS_PTR set_CF(temp_cf);
#endif
}

	void
BX_CPU_C::BTC_EEwIb(BX_CPU_C *icpu,bxInstruction_c *i)
{
#if BX_CPU_LEVEL < 3
	BX_PANIC(("BTC_EEwIb: not available on <386"));
#else
	Bit16u op1,op2,index,temp_cf;

	op2 = IMMEDIATEIb(i) & (16-1);
    index = op2 & (16-1);
    READ_RMW_VIRTUAL_WORD(MODRMSeg(i),RMAddr(i),&op1);

    temp_cf = (op1 >> index) & 0x01;
    op1 &= ~(((Bit16u) 1) << index);
    op1 |= (((Bit16u) !temp_cf) << index);

    WRITE_RMW_VIRTUAL_WORD(op1);
    BX_CPU_CLASS_PTR set_CF(temp_cf);
#endif
}

	void
BX_CPU_C::BTC_EEdIb(BX_CPU_C *icpu,bxInstruction_c *i)
{
#if BX_CPU_LEVEL < 3
	BX_PANIC(("BTC_EEdIb: not available on <386"));
#else
	Bit32u op1,op2,index,temp_cf;

	op2 = IMMEDIATEIb(i) & (32-1);
    index = op2 & (32-1);
    READ_RMW_VIRTUAL_DWORD(MODRMSeg(i),RMAddr(i),&op1);

    temp_cf = (op1 >> index) & 0x01;
    op1 &= ~(((Bit32u) 1) << index);
    op1 |= (((Bit32u) !temp_cf) << index);

    WRITE_RMW_VIRTUAL_DWORD(op1);
    BX_CPU_CLASS_PTR set_CF(temp_cf);
#endif
}

