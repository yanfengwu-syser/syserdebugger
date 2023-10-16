
/////////////////////////////////////////////////////////////////////////
// $Id: bcd.cc,v 1.5 2001/10/03 13:10:37 bdenney Exp $
/////////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "x86cpu.h"

  void
BX_CPU_C::DAS(BX_CPU_C *icpu,bxInstruction_c *i)
{
	Bit8u tmpCF, tmpAL;

  /* ??? */
  /* the algorithm for DAS is fashioned after the pseudo code in the
   * Pentium Processor Family Developer's Manual, volume 3.  It seems
   * to have changed from earlier processor's manuals.  I'm not sure
   * if this is a correction in the algorithm printed, or Intel has
   * changed the handling of instruction.  It might not even be
   * correct yet...
   */

//IF (AL AND 0FH) > 9 OR AF =1
//THEN
//AL ¡ûAL - 6;
//CF ¡ûCF OR BorrowFromLastSubtraction; (* CF OR borrow from AL ¡ûAL - 6 *)
//AF ¡û1;
//ELSE AF ¡û0;
//FI;
//IF ((AL >9FH) or CF =1)
//THEN
//AL ¡ûAL - 60H;
//CF ¡û1;
//ELSE CF ¡û0;
//FI;

	tmpCF = 0;
	tmpAL = RW_AL;

	/* DAS effect the following flags: A,C,S,Z,P */
	if (((tmpAL & 0x0F) > 0x09) || BX_CPU_CLASS_PTR get_AF())
	{
		BX_CPU_CLASS_PTR set_AF(1);
		tmpCF = (RW_AL < 0x06) || BX_CPU_CLASS_PTR get_CF();
		RW_AL = RW_AL - 0x06;
		/*tmpCF = (AL < 0) || CF;*/
    }
	else
	{
		BX_CPU_CLASS_PTR set_AF(0);
	}

	if ( (tmpAL > 0x9f) || tmpCF )
	{
		RW_AL = RW_AL - 0x60;
		tmpCF = 1;
    }

	BX_CPU_CLASS_PTR set_CF(tmpCF);
	BX_CPU_CLASS_PTR set_SF(RW_AL >> 7);
	BX_CPU_CLASS_PTR set_ZF(RW_AL==0);
	BX_CPU_CLASS_PTR set_PF_base(RW_AL);
}

	void
BX_CPU_C::AAA(BX_CPU_C *icpu,bxInstruction_c *i)
{
//IF ((AL AND 0FH) > 9) OR (AF =1)
//THEN
//AL ¡û(AL + 6);
//AH ¡ûAH + 1;
//AF ¡û1;
//CF ¡û1;
//ELSE
//AF ¡û0;
//CF ¡û0;
//FI;
//AL ¡ûAL AND 0FH;

	/* AAA effects the following flags: A,C */
	if ( ((RW_AL & 0x0f) > 9) || BX_CPU_CLASS_PTR get_AF() )
	{
		RW_AL = (RW_AL + 6);
		RW_AH = RW_AH + 1;
		BX_CPU_CLASS_PTR set_AF(1);
		BX_CPU_CLASS_PTR set_CF(1);
    }
	else
	{
		BX_CPU_CLASS_PTR set_AF(0);
		BX_CPU_CLASS_PTR set_CF(0);
    }

	RW_AL = RW_AL & 0x0f;
}

  void
BX_CPU_C::AAS(BX_CPU_C *icpu,bxInstruction_c *i)
{
//IF ((AL AND 0FH) > 9) OR (AF =1)
//THEN
//AL ¡ûAL ¨C 6;
//AH ¡ûAH ¨C 1;
//AF ¡û1;
//CF ¡û1;
//ELSE
//CF ¡û0;
//AF ¡û0;
//FI;
//AL ¡ûAL AND 0FH;

	/* AAS affects the following flags: A,C */
	if ( ((RW_AL & 0x0F) > 0x09) || BX_CPU_CLASS_PTR get_AF() )
	{
		RW_AL = (RW_AL - 6);
	    RW_AH = RW_AH - 1;
	    BX_CPU_CLASS_PTR set_AF(1);
		BX_CPU_CLASS_PTR set_CF(1);
    }
	else
	{
		BX_CPU_CLASS_PTR set_CF(0);
		BX_CPU_CLASS_PTR set_AF(0);
    }

    RW_AL = RW_AL & 0x0f;
}

	void
BX_CPU_C::AAM(BX_CPU_C *icpu,bxInstruction_c *i)
{
//tempAL ¡ûAL;
//AH ¡ûtempAL / imm8; (* imm8 is set to 0AH for the AAD mnemonic *)
//AL ¡ûtempAL MOD imm8;
//The immediate value (imm8) is taken from the second byte of the instruction.
//Flags Affected
//The SF, ZF, and PF flags are set according to the resulting binary value in the AL register. The
//OF, AF, and CF flags are undefined.

	Bit8u al, imm8;

	imm8 = IMMEDIATEIb(i);

	if (imm8==0)
	{
		BX_CPU_CLASS_PTR exception(BX_DE_EXCEPTION, 0, 0);
	}

	al = RW_AL;
	RW_AH = al / imm8;
	RW_AL = al % imm8;

	/* AAM affects the following flags: S,Z,P */
	BX_CPU_CLASS_PTR set_SF(al>>7);
	BX_CPU_CLASS_PTR set_ZF(al==0);
	BX_CPU_CLASS_PTR set_PF_base(al); /* ??? */
}

	void
BX_CPU_C::AAD(BX_CPU_C *icpu,bxInstruction_c *i)
{
//tempAL ¡ûAL;
//tempAH ¡ûAH;
//AL ¡û(tempAL + (tempAH imm8)) AND FFH; (* imm8 is set to 0AH for the AAD mnemonic *)
//AH ¡û0
//The immediate value (imm8) is taken from the second byte of the instruction.
//Flags Affected
//The SF, ZF, and PF flags are set according to the resulting binary value in the AL register; the
//OF, AF, and CF flags are undefined.
		
	Bit8u imm8;

	imm8 = IMMEDIATEIb(i);

	RW_AL = RW_AH * imm8 + RW_AL;
	RW_AH = 0;

	/* AAD effects the following flags: S,Z,P */
	BX_CPU_CLASS_PTR set_SF(RW_AL >> 7);
	BX_CPU_CLASS_PTR set_ZF(RW_AL == 0);
	BX_CPU_CLASS_PTR set_PF_base(RW_AL);
}

	void
BX_CPU_C::DAA(BX_CPU_C *icpu,bxInstruction_c *i)
{
	Bit8u al;

//IF (((AL AND 0FH) > 9) or AF =1)
//THEN
//AL ¡ûAL + 6;
//CF ¡ûCF OR CarryFromLastAddition; (* CF OR carry from AL ¡ûAL + 6 *)
//AF ¡û1;
//ELSE
//AF ¡û0;
//FI;
//IF ((AL AND F0H) >90H) or CF =1)
//THEN
//AL ¡ûAL + 60H;
//CF ¡û1;
//ELSE
//CF ¡û0;
//FI;

	al = RW_AL;

	// DAA affects the following flags: S,Z,A,P,C
	// ???
	if (((al & 0x0F) > 0x09) || BX_CPU_CLASS_PTR get_AF())
	{
		BX_CPU_CLASS_PTR set_CF(BX_CPU_CLASS_PTR get_CF() || (Bit8u)(al +6) <6 );
		al = al + 0x06;
		BX_CPU_CLASS_PTR set_AF(1);
    }
	else
	{
		BX_CPU_CLASS_PTR set_AF(0);
	}

	if ((al > 0x9F) || BX_CPU_CLASS_PTR get_CF())
	{
		al = al + 0x60;
		BX_CPU_CLASS_PTR set_CF(1);
    }
	else
	{
		BX_CPU_CLASS_PTR set_CF(0);
	}

	RW_AL = al;

	BX_CPU_CLASS_PTR set_SF(al >> 7);
	BX_CPU_CLASS_PTR set_ZF(al == 0);
	BX_CPU_CLASS_PTR set_PF_base(al);
}

