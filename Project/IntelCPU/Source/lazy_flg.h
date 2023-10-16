/////////////////////////////////////////////////////////////////////////
// $Id: lazy_flags.h,v 1.3 2001/10/03 13:10:37 bdenney Exp $
/////////////////////////////////////////////////////////////////////////

#ifndef BX_FLAGS_H
#define BX_FLAGS_H

#if BX_PROVIDE_CPU_MEMORY==1

#define BX_INSTR_X86	0

#define BX_INSTR_ADD8   1
#define BX_INSTR_ADD16  2
#define BX_INSTR_ADD32  3

#define BX_INSTR_SUB8   4
#define BX_INSTR_SUB16  5
#define BX_INSTR_SUB32  6

#define BX_INSTR_ADC8   7
#define BX_INSTR_ADC16  8
#define BX_INSTR_ADC32  9

#define BX_INSTR_SBB8   10
#define BX_INSTR_SBB16  11
#define BX_INSTR_SBB32  12

#define BX_INSTR_CMP8   13
#define BX_INSTR_CMP16  14
#define BX_INSTR_CMP32  15

#define BX_INSTR_INC8   16
#define BX_INSTR_INC16  17
#define BX_INSTR_INC32  18

#define BX_INSTR_DEC8   19
#define BX_INSTR_DEC16  20
#define BX_INSTR_DEC32  21

#define BX_INSTR_NEG8   22
#define BX_INSTR_NEG16  23
#define BX_INSTR_NEG32  24

#define BX_INSTR_XADD8  25
#define BX_INSTR_XADD16 26
#define BX_INSTR_XADD32 27

#define BX_INSTR_OR8    28
#define BX_INSTR_OR16   29
#define BX_INSTR_OR32   30

#define BX_INSTR_AND8   31
#define BX_INSTR_AND16  32
#define BX_INSTR_AND32  33

#define BX_INSTR_TEST8  34
#define BX_INSTR_TEST16 35
#define BX_INSTR_TEST32 36

#define BX_INSTR_XOR8   37
#define BX_INSTR_XOR16  38
#define BX_INSTR_XOR32  39

#define BX_INSTR_CMPS8  40
#define BX_INSTR_CMPS16 41
#define BX_INSTR_CMPS32 42

#define BX_INSTR_SCAS8  43
#define BX_INSTR_SCAS16 44
#define BX_INSTR_SCAS32 45

#define BX_INSTR_SHR8   46
#define BX_INSTR_SHR16  47
#define BX_INSTR_SHR32  48

#define BX_INSTR_SHL8   49
#define BX_INSTR_SHL16  50
#define BX_INSTR_SHL32  51

#define BX_INSTR_SAR8   52
#define BX_INSTR_SAR16  53
#define BX_INSTR_SAR32  54

#define BX_INSTR_ROL8   55
#define BX_INSTR_ROL16  56
#define BX_INSTR_ROL32  57

#define BX_INSTR_ROR8   58
#define BX_INSTR_ROR16  59
#define BX_INSTR_ROR32  60

#define BX_INSTR_RCL8   61
#define BX_INSTR_RCL16  62
#define BX_INSTR_RCL32  63

#define BX_INSTR_RCR8   64
#define BX_INSTR_RCR16  65
#define BX_INSTR_RCR32  66

#define BX_INSTR_SHRD16	67
#define BX_INSTR_SHRD32	68
#define BX_INSTR_SHLD16	69
#define BX_INSTR_SHLD32	70


#define BX_LF_INDEX_KNOWN   0
#define BX_LF_INDEX_OSZAPC  1
#define BX_LF_INDEX_OSZAP   2
#define BX_LF_INDEX_OSZPC   3
#define BX_LF_INDEX_XSZPC   4
#define BX_LF_INDEX_OC		5
#define BX_LF_INDEX_XC		6
#define BX_LF_INDEX_SIZE	7

#define BX_LF_MASK_OSZAPC 0x111111
#define BX_LF_MASK_OSZAP  0x222220
#define BX_LF_MASK_OSZPC  0x333033
#define BX_LF_MASK_XSZPC  0x044044
#define BX_LF_MASK_OC	  0x500005
#define BX_LF_MASK_XC	  0x000006

typedef struct
{
	Bit8u op1_8;
	Bit8u op2_8;
	Bit8u result_8;

	Bit16u op1_16;
	Bit16u op2_16;
	Bit16u result_16;

	Bit32u op1_32;
	Bit32u op2_32;
	Bit32u result_32;


	unsigned shift_counter;
	unsigned prev_cf;
	unsigned instr;

} bx_lf_flags_entry;

#endif /* BX_PROVIDE_CPU_MEMORY==1 */

#endif //#ifndef BX_FLAGS_H

