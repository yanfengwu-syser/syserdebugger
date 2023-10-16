/////////////////////////////////////////////////////////////////////////
// $Id: lazy_flags.cc,v 1.6 2001/10/03 13:10:37 bdenney Exp $
/////////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "x86cpu.h"

#if (HOST_CPU_IS_I80386==0)

	Boolean
BX_CPU_C::get_CF(void)
{
	Bit32u lf_cf;
	bx_lf_flags_entry *lf_entry;
	unsigned lf_entry_index;

	lf_entry_index = (BX_CPU_THIS_PTR lf_flags_status & 0x00000f);

	if (lf_entry_index==0)
	{
		//PRINTFLAGSINFO(lf_entry_index,"get_CF",BX_CPU_THIS_PTR eflags.x86.cf,BX_CPU_THIS_PTR eflags.cf);
		return (BX_CPU_THIS_PTR eflags.cf);
	}

	lf_entry = &BX_CPU_THIS_PTR lf_entrys[lf_entry_index];

	switch (lf_entry->instr)
	{
	case BX_INSTR_X86:
		lf_cf = BX_CPU_THIS_PTR eflags.cf;
		break;

	case BX_INSTR_ADD8:
	case BX_INSTR_XADD8:
		lf_cf = (lf_entry->result_8 <lf_entry->op2_8);
		break;

    case BX_INSTR_ADD16:
    case BX_INSTR_XADD16:
		lf_cf = (lf_entry->result_16 <lf_entry->op2_16);
		break;

    case BX_INSTR_ADD32:
    case BX_INSTR_XADD32:
		lf_cf = (lf_entry->result_32 < lf_entry->op2_32);
		break;

    case BX_INSTR_ADC8:
		lf_cf = (lf_entry->result_8 <lf_entry->op2_8) ||
				(lf_entry->prev_cf &&lf_entry->result_8 <=lf_entry->op2_8);
		break;

	case BX_INSTR_ADC16:
		lf_cf = (lf_entry->result_16 < lf_entry->op2_16) ||
				(lf_entry->prev_cf &&lf_entry->result_16 <=lf_entry->op2_16);
		break;


	case BX_INSTR_ADC32:
		lf_cf =	(lf_entry->result_32 <	lf_entry->op2_32) ||
				(lf_entry->prev_cf &&lf_entry->result_32 <=lf_entry->op2_32);
		break;

    case BX_INSTR_SUB8:
    case BX_INSTR_CMP8:
    case BX_INSTR_CMPS8:
    case BX_INSTR_SCAS8:
		lf_cf = (lf_entry->op1_8 < lf_entry->op2_8);
		break;

    case BX_INSTR_SUB16:
    case BX_INSTR_CMP16:
    case BX_INSTR_CMPS16:
    case BX_INSTR_SCAS16:
		lf_cf = (lf_entry->op1_16 < lf_entry->op2_16);
		break;

    case BX_INSTR_SUB32:
    case BX_INSTR_CMP32:
    case BX_INSTR_CMPS32:
    case BX_INSTR_SCAS32:
		lf_cf = (lf_entry->op1_32 < lf_entry->op2_32);
		break;

    case BX_INSTR_SBB8:
		lf_cf =	(lf_entry->op1_8 <	lf_entry->op2_8) ||
				(lf_entry->prev_cf &&lf_entry->op1_8 <=lf_entry->op2_8);
		break;

    case BX_INSTR_SBB16:
		lf_cf =	(lf_entry->op1_16 <	lf_entry->op2_16) ||
				(lf_entry->prev_cf &&lf_entry->op1_16 <=lf_entry->op2_16);
		break;

    case BX_INSTR_SBB32:
		lf_cf =	(lf_entry->op1_32 <	lf_entry->op2_32) ||
				(lf_entry->prev_cf &&lf_entry->op1_32 <=lf_entry->op2_32);
		break;

    case BX_INSTR_NEG8:
		lf_cf =	lf_entry->result_8 != 0;
		break;

    case BX_INSTR_NEG16:
		lf_cf =	lf_entry->result_16 != 0;
		break;

    case BX_INSTR_NEG32:
		lf_cf =	lf_entry->result_32 != 0;
		break;

    case BX_INSTR_OR8:
    case BX_INSTR_OR16:
    case BX_INSTR_OR32:
    case BX_INSTR_AND8:
    case BX_INSTR_AND16:
    case BX_INSTR_AND32:
    case BX_INSTR_TEST8:
    case BX_INSTR_TEST16:
    case BX_INSTR_TEST32:
    case BX_INSTR_XOR8:
    case BX_INSTR_XOR16:
    case BX_INSTR_XOR32:
		lf_cf = 0;
		break;

    case BX_INSTR_SHR8:
		lf_cf = (lf_entry->op1_8 >>(lf_entry->shift_counter - 1)) & 0x01;
		break;

    case BX_INSTR_SHR16:
		lf_cf = (lf_entry->op1_16 >>(lf_entry->shift_counter - 1)) & 0x01;
		break;

    case BX_INSTR_SHR32:
		lf_cf = (lf_entry->op1_32 >>(lf_entry->shift_counter - 1)) & 0x01;
		break;

    case BX_INSTR_SHL8:
		lf_cf = ((lf_entry->op1_8 <<(lf_entry->shift_counter - 1))>>0x7) & 0x01;
		break;

    case BX_INSTR_SHL16:
		lf_cf = ((lf_entry->op1_16 <<(lf_entry->shift_counter - 1))>>0xf) & 0x01;
		break;

    case BX_INSTR_SHL32:
		lf_cf = (lf_entry->op1_32 >>(32 - lf_entry->shift_counter)) & 0x01;
			break;

    case BX_INSTR_SAR8:
		lf_cf = ((lf_entry->op1_8 >> (lf_entry->shift_counter - 1)) |
			((0-(lf_entry->op1_8>>(8-1))) << (8 - ((lf_entry->shift_counter- 1)&0x7))))&0x01;
		break;

    case BX_INSTR_SAR16:
		lf_cf = ((lf_entry->op1_16 >> (lf_entry->shift_counter - 1)) |
			((0-(lf_entry->op1_16>>(16-1))) << (16 - ((lf_entry->shift_counter- 1)&0xf))))&0x01;
		break;

    case BX_INSTR_SAR32:
		lf_cf = ((lf_entry->op1_32 >> (lf_entry->shift_counter - 1)))&0x01;
		break;

    case BX_INSTR_SHRD16:
		{
			Bit32u temp_32;

			temp_32 = ((lf_entry->op2_16<<16) | (lf_entry->op1_16));
			temp_32 = (temp_32>> (lf_entry->shift_counter - 1)) |
						(temp_32<< (32-(lf_entry->shift_counter - 1)));
			lf_cf = temp_32 & 0x01;
		}

		break;

    case BX_INSTR_SHRD32:
		lf_cf = (lf_entry->op1_32 >> (lf_entry->shift_counter - 1)) & 0x01;

#if 0
		__asm
		{
			mov ebx,lf_entry
			mov eax,[ebx]bx_lf_flags_entry.op1_32
			mov edx,[ebx]bx_lf_flags_entry.op2_32
			mov cl,[ebx]bx_lf_flags_entry.shift_counter
			shrd eax,edx,cl
			mov eax,0
			setc al
			mov lf_cf,eax
		}
#endif

		break;

    case BX_INSTR_SHLD16:
		{
			Bit32u temp_32;
			temp_32 = ((lf_entry->op2_16<<16) | (lf_entry->op1_16));
			temp_32 = (temp_32<< (lf_entry->shift_counter - 1)) |
						(temp_32>> (32-(lf_entry->shift_counter - 1)));
			lf_cf = (temp_32>>15) & 0x01;
		}
		break;

    case BX_INSTR_SHLD32:
		lf_cf = (lf_entry->op1_32 << (32 - lf_entry->shift_counter)) & 0x01;

#if 0
		__asm
		{
			mov ebx,lf_entry
			mov eax,[ebx]bx_lf_flags_entry.op1_32
			mov edx,[ebx]bx_lf_flags_entry.op2_32
			mov cl,[ebx]bx_lf_flags_entry.shift_counter
			shld eax,edx,cl
			mov eax,0
			setc al
			mov lf_cf,eax
		}
#endif

		break;

    case BX_INSTR_ROR8:
		lf_cf = (lf_entry->result_8>>7);
		break;

    case BX_INSTR_ROR16:
		lf_cf = (lf_entry->result_16>>15);
		break;

    case BX_INSTR_ROR32:
		lf_cf = (lf_entry->result_32>>31);
		break;

    case BX_INSTR_ROL8:
		lf_cf = (lf_entry->result_8&0x01);
		break;

    case BX_INSTR_ROL16:
		lf_cf = (lf_entry->result_16&0x01);
		break;

    case BX_INSTR_ROL32:
		lf_cf = (lf_entry->result_32&0x01);
		break;

    case BX_INSTR_RCR8:
		lf_cf = ((lf_entry->op1_8 >> (lf_entry->shift_counter - 1)) & 0x01);
		break;

    case BX_INSTR_RCR16:
		lf_cf = ((lf_entry->op1_16 >> (lf_entry->shift_counter - 1)) & 0x01);
		break;

    case BX_INSTR_RCR32:
		lf_cf = ((lf_entry->op1_32 >> (lf_entry->shift_counter - 1)) & 0x01);
		break;

    case BX_INSTR_RCL8:
		lf_cf = ((lf_entry->op1_8 >> (8 - lf_entry->shift_counter)) & 0x01);
		break;

    case BX_INSTR_RCL16:
		lf_cf = ((lf_entry->op1_16 >> (16 - lf_entry->shift_counter)) & 0x01);
		break;

    case BX_INSTR_RCL32:
		lf_cf = ((lf_entry->op1_32 >> (32 - lf_entry->shift_counter)) & 0x01);
		break;

    default:
          BX_PANIC(("get_CF: OSZAPC,OSZPC,XSZPC,OC,XC: unknown instr %u",
			  (unsigned) lf_entry->instr));
    }

	BX_CPU_THIS_PTR lf_flags_status &= 0xfffff0;
	BX_CPU_THIS_PTR eflags.cf = lf_cf;
	//PRINTFLAGSINFO(lf_entry_index,"get_CF",BX_CPU_THIS_PTR eflags.x86.cf,BX_CPU_THIS_PTR eflags.cf);
	return (lf_cf);
}


	Boolean
BX_CPU_C::get_AF(void)
{
	Bit32u lf_af;
	bx_lf_flags_entry *lf_entry;
	unsigned lf_entry_index;

	lf_entry_index = ((BX_CPU_THIS_PTR lf_flags_status>>8) & 0x00000f);

	if (lf_entry_index==0)
	{
		//PRINTFLAGSINFO(lf_entry_index,"get_AF",BX_CPU_THIS_PTR eflags.x86.af,BX_CPU_THIS_PTR eflags.af);
		return (BX_CPU_THIS_PTR eflags.af);
	}

	lf_entry = &BX_CPU_THIS_PTR lf_entrys[lf_entry_index];

	switch (lf_entry->instr)
	{
	case BX_INSTR_X86:
		lf_af = BX_CPU_THIS_PTR eflags.af;
		break;
        case BX_INSTR_ADD8:
        case BX_INSTR_ADC8:
        case BX_INSTR_SUB8:
        case BX_INSTR_SBB8:
        case BX_INSTR_CMP8:
        case BX_INSTR_XADD8:
        case BX_INSTR_CMPS8:
        case BX_INSTR_SCAS8:
          lf_af = (((lf_entry->op1_8 ^ lf_entry->op2_8) ^lf_entry->result_8) & 0x10)>>4;
          break;

        case BX_INSTR_ADD16:
        case BX_INSTR_ADC16:
        case BX_INSTR_SUB16:
        case BX_INSTR_SBB16:
        case BX_INSTR_CMP16:
        case BX_INSTR_XADD16:
        case BX_INSTR_CMPS16:
        case BX_INSTR_SCAS16:
          lf_af = (((lf_entry->op1_16 ^ lf_entry->op2_16) ^lf_entry->result_16) & 0x10)>>4;
          break;

        case BX_INSTR_ADD32:
        case BX_INSTR_ADC32:
        case BX_INSTR_SUB32:
        case BX_INSTR_SBB32:
        case BX_INSTR_CMP32:
        case BX_INSTR_XADD32:
        case BX_INSTR_CMPS32:
        case BX_INSTR_SCAS32:
          lf_af = (((lf_entry->op1_32 ^ lf_entry->op2_32) ^lf_entry->result_32) & 0x10)>>4;
          break;

    case BX_INSTR_NEG8:
		lf_af =	((0-lf_entry->result_8) & 0x0f) > 0;
		break;

    case BX_INSTR_NEG16:
		lf_af =	((0-lf_entry->result_16) & 0x0f) > 0;
		break;

    case BX_INSTR_NEG32:
		lf_af =	((0-lf_entry->result_32) & 0x0f) > 0;
		break;

    case BX_INSTR_OR8:
    case BX_INSTR_OR16:
    case BX_INSTR_OR32:
    case BX_INSTR_AND8:
    case BX_INSTR_AND16:
    case BX_INSTR_AND32:
    case BX_INSTR_TEST8:
    case BX_INSTR_TEST16:
    case BX_INSTR_TEST32:
    case BX_INSTR_XOR8:
    case BX_INSTR_XOR16:
    case BX_INSTR_XOR32:
		lf_af = 0;
		break;

    case BX_INSTR_SHR8:
    case BX_INSTR_SHR16:
    case BX_INSTR_SHR32:
    case BX_INSTR_SHL8:
    case BX_INSTR_SHL16:
    case BX_INSTR_SHL32:
		/* undefined */
		BX_PANIC(("get_AF: OSZAPC,OSZAP: unknown instr %u",
			(unsigned) lf_entry->instr));
		break;

	case BX_INSTR_INC8:
		lf_af =	(lf_entry->result_8 & 0x0f) == 0x00;
		break;

    case BX_INSTR_INC16:
		lf_af =	(lf_entry->result_16 & 0x0f) == 0x00;
		break;

    case BX_INSTR_INC32:
		lf_af =	(lf_entry->result_32 & 0x0f) == 0x00;
		break;

    case BX_INSTR_DEC8:
		lf_af =	(lf_entry->result_8 & 0x0f) == 0x0f;
		break;

    case BX_INSTR_DEC16:
		lf_af =	(lf_entry->result_16 & 0x0f) == 0x0f;
		break;

    case BX_INSTR_DEC32:
		lf_af =	(lf_entry->result_32 & 0x0f) == 0x0f;
		break;

    default:
		BX_PANIC(("get_AF: OSZAPC,OSZAP: unknown instr %u",
			(unsigned) lf_entry->instr));
    }

	BX_CPU_THIS_PTR lf_flags_status &= 0xfff0ff;
	BX_CPU_THIS_PTR eflags.af = lf_af;
	//PRINTFLAGSINFO(lf_entry_index,"get_AF",BX_CPU_THIS_PTR eflags.x86.af,BX_CPU_THIS_PTR eflags.af);
	return(lf_af);
}

	Boolean
BX_CPU_C::get_ZF(void)
{
	bx_lf_flags_entry *lf_entry;
	unsigned lf_entry_index;

	lf_entry_index = ((BX_CPU_THIS_PTR lf_flags_status>>12) & 0x00000f);

	if (lf_entry_index==0)
	{
		//PRINTFLAGSINFO(lf_entry_index,"get_ZF",BX_CPU_THIS_PTR eflags.x86.zf,BX_CPU_THIS_PTR eflags.zf);
		return (BX_CPU_THIS_PTR eflags.zf);
	}

	lf_entry = &BX_CPU_THIS_PTR lf_entrys[lf_entry_index];

	switch (lf_entry->instr)
	{
	case BX_INSTR_X86:
		BX_CPU_THIS_PTR eflags.zf = BX_CPU_THIS_PTR eflags.zf;
		break;

    case BX_INSTR_ADD8:
    case BX_INSTR_ADC8:
    case BX_INSTR_SUB8:
    case BX_INSTR_SBB8:
    case BX_INSTR_CMP8:
    case BX_INSTR_NEG8:
    case BX_INSTR_XADD8:
    case BX_INSTR_OR8:
    case BX_INSTR_AND8:
    case BX_INSTR_TEST8:
    case BX_INSTR_XOR8:
    case BX_INSTR_CMPS8:
    case BX_INSTR_SCAS8:
    case BX_INSTR_SHR8:
    case BX_INSTR_SHL8:
    case BX_INSTR_SAR8:
		BX_CPU_THIS_PTR eflags.zf = (lf_entry->result_8 == 0);
		break;

    case BX_INSTR_ADD16:
    case BX_INSTR_ADC16:
    case BX_INSTR_SUB16:
    case BX_INSTR_SBB16:
    case BX_INSTR_CMP16:
    case BX_INSTR_NEG16:
    case BX_INSTR_XADD16:
    case BX_INSTR_OR16:
    case BX_INSTR_AND16:
    case BX_INSTR_TEST16:
    case BX_INSTR_XOR16:
    case BX_INSTR_CMPS16:
    case BX_INSTR_SCAS16:
    case BX_INSTR_SHR16:
    case BX_INSTR_SHL16:
    case BX_INSTR_SAR16:
    case BX_INSTR_SHLD16:
    case BX_INSTR_SHRD16:
		BX_CPU_THIS_PTR eflags.zf = (lf_entry->result_16 == 0);
		break;

    case BX_INSTR_ADD32:
    case BX_INSTR_ADC32:
    case BX_INSTR_SUB32:
    case BX_INSTR_SBB32:
    case BX_INSTR_CMP32:
    case BX_INSTR_NEG32:
    case BX_INSTR_XADD32:
    case BX_INSTR_OR32:
    case BX_INSTR_AND32:
    case BX_INSTR_TEST32:
    case BX_INSTR_XOR32:
    case BX_INSTR_CMPS32:
    case BX_INSTR_SCAS32:
    case BX_INSTR_SHR32:
    case BX_INSTR_SHL32:
    case BX_INSTR_SAR32:
    case BX_INSTR_SHLD32:
    case BX_INSTR_SHRD32:
		BX_CPU_THIS_PTR eflags.zf = (lf_entry->result_32 == 0);
		break;

    case BX_INSTR_INC8:
    case BX_INSTR_DEC8:
		BX_CPU_THIS_PTR eflags.zf = (lf_entry->result_8 == 0);
		break;

    case BX_INSTR_INC16:
    case BX_INSTR_DEC16:
		BX_CPU_THIS_PTR eflags.zf = (lf_entry->result_16 == 0);
		break;

    case BX_INSTR_INC32:
    case BX_INSTR_DEC32:
		BX_CPU_THIS_PTR eflags.zf = (lf_entry->result_32 == 0);
		break;

    default:
		BX_PANIC(("get_ZF: OSZAPC,OSZAP,OSZPC,XSZPC: unknown instr",
			lf_entry->instr));

    }

	BX_CPU_THIS_PTR lf_flags_status &= 0xff0fff;
	//PRINTFLAGSINFO(lf_entry_index,"get_ZF",BX_CPU_THIS_PTR eflags.x86.zf,BX_CPU_THIS_PTR eflags.zf);
	return(BX_CPU_THIS_PTR eflags.zf);
}

	Boolean
BX_CPU_C::get_SF(void)
{
	bx_lf_flags_entry *lf_entry;
	unsigned lf_entry_index;

	lf_entry_index = ((BX_CPU_THIS_PTR lf_flags_status>>16) & 0x00000f);

	if (lf_entry_index==0)
	{
		//PRINTFLAGSINFO(lf_entry_index,"get_SF",BX_CPU_THIS_PTR eflags.x86.sf,BX_CPU_THIS_PTR eflags.sf);
		return (BX_CPU_THIS_PTR eflags.sf);
	}

	lf_entry = &BX_CPU_THIS_PTR lf_entrys[lf_entry_index];

	switch (lf_entry->instr)
	{
	case BX_INSTR_X86:
		BX_CPU_THIS_PTR eflags.sf = BX_CPU_THIS_PTR eflags.sf;
		break;

    case BX_INSTR_ADD8:
    case BX_INSTR_ADC8:
    case BX_INSTR_SUB8:
    case BX_INSTR_SBB8:
    case BX_INSTR_CMP8:
    case BX_INSTR_NEG8:
    case BX_INSTR_XADD8:
    case BX_INSTR_OR8:
    case BX_INSTR_AND8:
    case BX_INSTR_TEST8:
    case BX_INSTR_XOR8:
    case BX_INSTR_CMPS8:
    case BX_INSTR_SCAS8:
    case BX_INSTR_SHR8:
    case BX_INSTR_SHL8:
    case BX_INSTR_SAR8:
		BX_CPU_THIS_PTR eflags.sf =	(lf_entry->result_8 >> 7);
		break;

    case BX_INSTR_ADD16:
    case BX_INSTR_ADC16:
    case BX_INSTR_SUB16:
    case BX_INSTR_SBB16:
    case BX_INSTR_CMP16:
    case BX_INSTR_NEG16:
    case BX_INSTR_XADD16:
    case BX_INSTR_OR16:
    case BX_INSTR_AND16:
    case BX_INSTR_TEST16:
    case BX_INSTR_XOR16:
    case BX_INSTR_CMPS16:
    case BX_INSTR_SCAS16:
    case BX_INSTR_SHR16:
    case BX_INSTR_SHL16:
    case BX_INSTR_SAR16:
    case BX_INSTR_SHLD16:
    case BX_INSTR_SHRD16:
		BX_CPU_THIS_PTR eflags.sf =	(lf_entry->result_16 >>15);
		break;

    case BX_INSTR_ADD32:
    case BX_INSTR_ADC32:
    case BX_INSTR_SUB32:
    case BX_INSTR_SBB32:
    case BX_INSTR_CMP32:
    case BX_INSTR_NEG32:
    case BX_INSTR_XADD32:
    case BX_INSTR_OR32:
    case BX_INSTR_AND32:
    case BX_INSTR_TEST32:
    case BX_INSTR_XOR32:
    case BX_INSTR_CMPS32:
    case BX_INSTR_SCAS32:
    case BX_INSTR_SHR32:
    case BX_INSTR_SHL32:
    case BX_INSTR_SAR32:
    case BX_INSTR_SHLD32:
    case BX_INSTR_SHRD32:
		BX_CPU_THIS_PTR eflags.sf = (lf_entry->result_32 >>31);
		break;

    case BX_INSTR_INC8:
    case BX_INSTR_DEC8:
		BX_CPU_THIS_PTR eflags.sf =	(lf_entry->result_8 >> 7);
		break;

    case BX_INSTR_INC16:
    case BX_INSTR_DEC16:
		BX_CPU_THIS_PTR eflags.sf =	(lf_entry->result_16 >> 15);
		break;

    case BX_INSTR_INC32:
    case BX_INSTR_DEC32:
		BX_CPU_THIS_PTR eflags.sf =	(lf_entry->result_32 >> 31);
		break;

    default:
		BX_PANIC(("get_SF: OSZAPC,OSZAP,OSZPC,XSZPC: unknown instr %d",
			lf_entry->instr));
    }

	BX_CPU_THIS_PTR lf_flags_status &= 0xf0ffff;
	//PRINTFLAGSINFO(lf_entry_index,"get_SF",BX_CPU_THIS_PTR eflags.x86.sf,BX_CPU_THIS_PTR eflags.sf);
	return(BX_CPU_THIS_PTR eflags.sf);
}

	Boolean
BX_CPU_C::get_OF(void)
{
	bx_lf_flags_entry *lf_entry;
	unsigned lf_entry_index;

	lf_entry_index = ((BX_CPU_THIS_PTR lf_flags_status>>20) & 0x00000f);

	if (lf_entry_index==0)
	{
		//PRINTFLAGSINFO(lf_entry_index,"get_OF",BX_CPU_THIS_PTR eflags.x86.of,BX_CPU_THIS_PTR eflags.of);
		return (BX_CPU_THIS_PTR eflags.of);
	}

	lf_entry = &BX_CPU_THIS_PTR lf_entrys[lf_entry_index];

	switch (lf_entry->instr)
	{
	case BX_INSTR_X86:
		BX_CPU_THIS_PTR eflags.of = BX_CPU_THIS_PTR eflags.of;
		break;

    case BX_INSTR_ADD8:
    case BX_INSTR_ADC8:
    case BX_INSTR_XADD8:
		BX_CPU_THIS_PTR eflags.of = ((lf_entry->op1_8 ^ lf_entry->result_8) &
									(lf_entry->op2_8 ^ lf_entry->result_8))>>7;
		break;

    case BX_INSTR_ADD16:
    case BX_INSTR_ADC16:
    case BX_INSTR_XADD16:
		BX_CPU_THIS_PTR eflags.of = ((lf_entry->op1_16 ^ lf_entry->result_16) &
									(lf_entry->op2_16 ^ lf_entry->result_16))>>15;
		break;

    case BX_INSTR_ADD32:
    case BX_INSTR_ADC32:
    case BX_INSTR_XADD32:
		BX_CPU_THIS_PTR eflags.of = ((lf_entry->op1_32 ^ lf_entry->result_32) &
									(lf_entry->op2_32 ^ lf_entry->result_32))>>31;
		break;

    case BX_INSTR_SUB8:
    case BX_INSTR_SBB8:
    case BX_INSTR_CMP8:
    case BX_INSTR_CMPS8:
    case BX_INSTR_SCAS8:
		BX_CPU_THIS_PTR eflags.of = ((lf_entry->op1_8 ^ lf_entry->op2_8) &
									(lf_entry->op1_8 ^ lf_entry->result_8))>>7;
		break;

    case BX_INSTR_SUB16:
    case BX_INSTR_SBB16:
    case BX_INSTR_CMP16:
    case BX_INSTR_CMPS16:
    case BX_INSTR_SCAS16:
		BX_CPU_THIS_PTR eflags.of = ((lf_entry->op1_16 ^ lf_entry->op2_16) &
									(lf_entry->op1_16 ^ lf_entry->result_16))>>15;
		break;

    case BX_INSTR_SUB32:
    case BX_INSTR_SBB32:
    case BX_INSTR_CMP32:
    case BX_INSTR_CMPS32:
    case BX_INSTR_SCAS32:
		BX_CPU_THIS_PTR eflags.of = ((lf_entry->op1_32 ^ lf_entry->op2_32) &
									(lf_entry->op1_32 ^ lf_entry->result_32))>>31;
		break;

    case BX_INSTR_NEG8:
		BX_CPU_THIS_PTR eflags.of =	(lf_entry->result_8 == 0x80);
		break;

    case BX_INSTR_NEG16:
		BX_CPU_THIS_PTR eflags.of =	(lf_entry->result_16 == 0x8000);
		break;

    case BX_INSTR_NEG32:
		BX_CPU_THIS_PTR eflags.of = (lf_entry->result_32 == 0x80000000);
		break;

    case BX_INSTR_OR8:
    case BX_INSTR_OR16:
    case BX_INSTR_OR32:
    case BX_INSTR_AND8:
    case BX_INSTR_AND16:
    case BX_INSTR_AND32:
    case BX_INSTR_TEST8:
    case BX_INSTR_TEST16:
    case BX_INSTR_TEST32:
    case BX_INSTR_XOR8:
    case BX_INSTR_XOR16:
    case BX_INSTR_XOR32:
		BX_CPU_THIS_PTR eflags.of = 0;
		break;

    case BX_INSTR_INC8:
		BX_CPU_THIS_PTR eflags.of =	(lf_entry->result_8 == 0x80);
		break;

    case BX_INSTR_INC16:
		BX_CPU_THIS_PTR eflags.of =	(lf_entry->result_16 == 0x8000);
		break;

    case BX_INSTR_INC32:
		BX_CPU_THIS_PTR eflags.of =	(lf_entry->result_32 == 0x80000000);
		break;

    case BX_INSTR_DEC8:
		BX_CPU_THIS_PTR eflags.of =	(lf_entry->result_8 == 0x7f);
		break;

    case BX_INSTR_DEC16:
		BX_CPU_THIS_PTR eflags.of =	(lf_entry->result_16 == 0x7fff);
		break;

    case BX_INSTR_DEC32:
		BX_CPU_THIS_PTR eflags.of =	(lf_entry->result_32 == 0x7fffffff);
		break;

    case BX_INSTR_SHR8:
		BX_CPU_THIS_PTR eflags.of =	(lf_entry->op1_8 >>7);
		break;

    case BX_INSTR_SHR16:
		BX_CPU_THIS_PTR eflags.of =	(lf_entry->op1_16 >>15);
		break;

    case BX_INSTR_SHR32:
		BX_CPU_THIS_PTR eflags.of =	(lf_entry->op1_32 >>31);
		break;

    case BX_INSTR_SHL8:
		BX_CPU_THIS_PTR eflags.of =	((lf_entry->op1_8 ^lf_entry->result_8) >> 7);
		break;

    case BX_INSTR_SHL16:
		BX_CPU_THIS_PTR eflags.of = ((lf_entry->op1_16 ^lf_entry->result_16) >> 15);
		break;

    case BX_INSTR_SHL32:
		BX_CPU_THIS_PTR eflags.of =	((lf_entry->op1_32 ^lf_entry->result_32) >>31);
		break;

    case BX_INSTR_SAR8:
    case BX_INSTR_SAR16:
    case BX_INSTR_SAR32:
		BX_CPU_THIS_PTR eflags.of = 0;
		break;

    case BX_INSTR_SHRD16:
    case BX_INSTR_SHLD16:
		BX_CPU_THIS_PTR eflags.of =	((lf_entry->op1_16 ^lf_entry->result_16) >>15) &0x01;
		break;

    case BX_INSTR_SHRD32:
    case BX_INSTR_SHLD32:
		BX_CPU_THIS_PTR eflags.of =	((lf_entry->op1_32 ^lf_entry->result_32) >>31) 	&0x01;
		break;

    case BX_INSTR_ROR8:
    case BX_INSTR_ROL8:
    case BX_INSTR_RCR8:
    case BX_INSTR_RCL8:
		BX_CPU_THIS_PTR eflags.of = (((lf_entry->op1_8 ^ lf_entry->result_8)>>7));
		break;

    case BX_INSTR_ROR16:
    case BX_INSTR_ROL16:
    case BX_INSTR_RCR16:
    case BX_INSTR_RCL16:
		BX_CPU_THIS_PTR eflags.of = (((lf_entry->op1_16 ^ lf_entry->result_16)>>15));
		break;

    case BX_INSTR_ROR32:
    case BX_INSTR_ROL32:
    case BX_INSTR_RCR32:
    case BX_INSTR_RCL32:
		BX_CPU_THIS_PTR eflags.of = (((lf_entry->op1_32 ^ lf_entry->result_32)>>31));
		break;

	default:
		BX_PANIC(("get_OF: OSZAPC,OSZAP,OSZPC,OC: unknown instr %d",
			lf_entry->instr));
    }

	BX_CPU_THIS_PTR lf_flags_status &= 0x0fffff;
	//PRINTFLAGSINFO(lf_entry_index,"get_OF",BX_CPU_THIS_PTR eflags.x86.of,BX_CPU_THIS_PTR eflags.of);
	return(BX_CPU_THIS_PTR eflags.of);
}

	Boolean
BX_CPU_C::get_PF(void)
{
	bx_lf_flags_entry *lf_entry;
	unsigned lf_entry_index;

	lf_entry_index = ((BX_CPU_THIS_PTR lf_flags_status>>4) & 0x00000f);

	if (lf_entry_index==0)
	{
		//PRINTFLAGSINFO(lf_entry_index,"get_PF",BX_CPU_THIS_PTR eflags.x86.pf,BX_CPU_THIS_PTR eflags.pf);
		return (BX_CPU_THIS_PTR eflags.pf);
	}

	lf_entry = &BX_CPU_THIS_PTR lf_entrys[lf_entry_index];

	switch (lf_entry->instr)
	{
	case BX_INSTR_X86:
		BX_CPU_THIS_PTR eflags.pf = BX_CPU_THIS_PTR eflags.pf;
		break;

    case BX_INSTR_ADD8:
    case BX_INSTR_ADC8:
    case BX_INSTR_SUB8:
    case BX_INSTR_SBB8:
    case BX_INSTR_CMP8:
    case BX_INSTR_NEG8:
    case BX_INSTR_XADD8:
    case BX_INSTR_OR8:
    case BX_INSTR_AND8:
    case BX_INSTR_TEST8:
    case BX_INSTR_XOR8:
    case BX_INSTR_CMPS8:
    case BX_INSTR_SCAS8:
    case BX_INSTR_SHR8:
    case BX_INSTR_SHL8:
    case BX_INSTR_SAR8:
		BX_CPU_THIS_PTR eflags.pf = bx_parity_lookup[lf_entry->result_8];
		break;

    case BX_INSTR_ADD16:
    case BX_INSTR_ADC16:
    case BX_INSTR_SUB16:
    case BX_INSTR_SBB16:
    case BX_INSTR_CMP16:
    case BX_INSTR_NEG16:
    case BX_INSTR_XADD16:
    case BX_INSTR_OR16:
    case BX_INSTR_AND16:
    case BX_INSTR_TEST16:
    case BX_INSTR_XOR16:
    case BX_INSTR_CMPS16:
    case BX_INSTR_SCAS16:
    case BX_INSTR_SHR16:
    case BX_INSTR_SHL16:
    case BX_INSTR_SAR16:
    case BX_INSTR_SHLD16:
    case BX_INSTR_SHRD16:
		BX_CPU_THIS_PTR eflags.pf =	bx_parity_lookup[(Bit8u) lf_entry->result_16];
		break;

    case BX_INSTR_ADD32:
    case BX_INSTR_ADC32:
    case BX_INSTR_SUB32:
    case BX_INSTR_SBB32:
    case BX_INSTR_CMP32:
    case BX_INSTR_NEG32:
    case BX_INSTR_XADD32:
    case BX_INSTR_OR32:
    case BX_INSTR_AND32:
    case BX_INSTR_TEST32:
    case BX_INSTR_XOR32:
    case BX_INSTR_CMPS32:
    case BX_INSTR_SCAS32:
    case BX_INSTR_SHR32:
    case BX_INSTR_SHL32:
    case BX_INSTR_SAR32:
    case BX_INSTR_SHLD32:
    case BX_INSTR_SHRD32:
		BX_CPU_THIS_PTR eflags.pf =	bx_parity_lookup[(Bit8u) lf_entry->result_32];
		break;

    case BX_INSTR_INC8:
    case BX_INSTR_DEC8:
		BX_CPU_THIS_PTR eflags.pf =	bx_parity_lookup[lf_entry->result_8];
		break;

    case BX_INSTR_INC16:
    case BX_INSTR_DEC16:
		BX_CPU_THIS_PTR eflags.pf =	bx_parity_lookup[(Bit8u) lf_entry->result_16];
		break;

    case BX_INSTR_INC32:
    case BX_INSTR_DEC32:
		BX_CPU_THIS_PTR eflags.pf =	bx_parity_lookup[(Bit8u) lf_entry->result_32];
		break;

    default:
		BX_PANIC(("get_PF: OSZAPC,OSZAP,OSZPC,XSZPC: unknown instr %d",
			lf_entry->instr));
    }

	BX_CPU_THIS_PTR lf_flags_status &= 0xffff0f;
	//PRINTFLAGSINFO(lf_entry_index,"get_PF",BX_CPU_THIS_PTR eflags.x86.pf,BX_CPU_THIS_PTR eflags.pf);
	return(BX_CPU_THIS_PTR eflags.pf);
}

#else

	Boolean
BX_CPU_C::get_CF(void)
{
	return ((BX_CPU_THIS_PTR eflags.x86.Descr.cf));
}

	Boolean
BX_CPU_C::get_AF(void)
{
	return ((BX_CPU_THIS_PTR eflags.x86.Descr.af));
}
	Boolean
BX_CPU_C::get_ZF(void)
{
	return ((BX_CPU_THIS_PTR eflags.x86.Descr.zf));
}
	Boolean
BX_CPU_C::get_SF(void)
{
	return ((BX_CPU_THIS_PTR eflags.x86.Descr.sf));
}
	Boolean
BX_CPU_C::get_OF(void)
{
	return ((BX_CPU_THIS_PTR eflags.x86.Descr.of));
}
	Boolean
BX_CPU_C::get_PF(void)
{
	return ((BX_CPU_THIS_PTR eflags.x86.Descr.pf));
}

#endif

	int
BX_CPU_C::PRINTFLAGSINFO(int lf_entry_index,char *name,int m,int c)
{
	if (m==c)
		return 0;
	BX_PANIC(("get_flags: instr = %d,index =%d :%s",
		BX_CPU_THIS_PTR lf_entrys[lf_entry_index].instr,lf_entry_index,name));
	return 0;
}
