
/////////////////////////////////////////////////////////////////////////
// $Id: cpu.h,v 1.17 2002/03/27 16:04:04 bdenney Exp $
/////////////////////////////////////////////////////////////////////////

#ifndef BX_CPU_H
#define BX_CPU_H 1

#define X86CPU_MSWIN_MSDOS 1

#include <setjmp.h>
/*
typedef struct MY__JUMP_BUFFER {

	unsigned long check_s;
	unsigned long Eax;
	unsigned long Edx;
	unsigned long Ecx;
	unsigned long Ebx;
	unsigned long Esp;
	unsigned long Ebp;
	unsigned long Esi;
	unsigned long Edi;

	unsigned long Eip;
	unsigned long Registration;
	unsigned long TryLevel;
	unsigned long Cookie;
	unsigned long UnwindFunc;
	unsigned long UnwindData[6];
	unsigned long check_e;

} MY_JUMP_BUFFER;


int mysetjump(MY_JUMP_BUFFER *jump_buff);
void mylongjump(MY_JUMP_BUFFER *jump_buff,unsigned int code);

#define setjmp(a)			mysetjump(&a)
#define longjmp(a,b)		mylongjump(&a,b)
typedef MY_JUMP_BUFFER* jmp_buf;
*/
#include "lazy_flg.h"

#define BX_SREG_ES    0
#define BX_SREG_CS    1
#define BX_SREG_SS    2
#define BX_SREG_DS    3
#define BX_SREG_FS    4
#define BX_SREG_GS    5

// segment register encoding
#define BX_SEG_REG_ES    0
#define BX_SEG_REG_CS    1
#define BX_SEG_REG_SS    2
#define BX_SEG_REG_DS    3
#define BX_SEG_REG_FS    4
#define BX_SEG_REG_GS    5
#define BX_SEG_REG_NULL  8
#define BX_NULL_SEG_REG(seg) ((seg) & BX_SEG_REG_NULL)


#ifdef BX_LITTLE_ENDIAN
#define BX_REG8L_OFFSET 0
#define BX_REG8H_OFFSET 1
#define BX_REG16_OFFSET 0
#else // BX_BIG_ENDIAN
#define BX_REG8L_OFFSET 3
#define BX_REG8H_OFFSET 2
#define BX_REG16_OFFSET 2
#endif // ifdef BX_LITTLE_ENDIAN

#define BX_8BIT_REG_AL  0
#define BX_8BIT_REG_CL  1
#define BX_8BIT_REG_DL  2
#define BX_8BIT_REG_BL  3
#define BX_8BIT_REG_AH  4
#define BX_8BIT_REG_CH  5
#define BX_8BIT_REG_DH  6
#define BX_8BIT_REG_BH  7

#define BX_16BIT_REG_AX 0
#define BX_16BIT_REG_CX 1
#define BX_16BIT_REG_DX 2
#define BX_16BIT_REG_BX 3
#define BX_16BIT_REG_SP 4
#define BX_16BIT_REG_BP 5
#define BX_16BIT_REG_SI 6
#define BX_16BIT_REG_DI 7

#define BX_32BIT_REG_EAX 0
#define BX_32BIT_REG_ECX 1
#define BX_32BIT_REG_EDX 2
#define BX_32BIT_REG_EBX 3
#define BX_32BIT_REG_ESP 4
#define BX_32BIT_REG_EBP 5
#define BX_32BIT_REG_ESI 6
#define BX_32BIT_REG_EDI 7

#if (X86CPU_MSWIN_MSDOS==1)
#define program_visible_gen_reg			program_visible_register.gen_reg
#define program_visible_sregs			program_visible_register.sregs
#define program_visible_eip				program_visible_register.eip
#define program_visible_eflags			program_visible_register.eflags
#endif

#if defined(NEED_CPU_REG_SHORTCUTS)

/* WARNING: 
   Only BX_CPU_C member functions can use these shortcuts safely!
   Functions that use the shortcuts outside of BX_CPU_C might work 
   when BX_USE_CPU_SMF=1 but will fail when BX_USE_CPU_SMF=0
   (for example in SMP mode).
*/

// access to 8 bit general registers
#define X86_AL (BX_CPU_THIS_PTR program_visible_gen_reg[0].word.byte.rl)
#define X86_CL (BX_CPU_THIS_PTR program_visible_gen_reg[1].word.byte.rl)
#define X86_DL (BX_CPU_THIS_PTR program_visible_gen_reg[2].word.byte.rl)
#define X86_BL (BX_CPU_THIS_PTR program_visible_gen_reg[3].word.byte.rl)
#define X86_AH (BX_CPU_THIS_PTR program_visible_gen_reg[0].word.byte.rh)
#define X86_CH (BX_CPU_THIS_PTR program_visible_gen_reg[1].word.byte.rh)
#define X86_DH (BX_CPU_THIS_PTR program_visible_gen_reg[2].word.byte.rh)
#define X86_BH (BX_CPU_THIS_PTR program_visible_gen_reg[3].word.byte.rh)


// access to 16 bit general registers
#define X86_AX (BX_CPU_THIS_PTR program_visible_gen_reg[0].word.rx)
#define X86_CX (BX_CPU_THIS_PTR program_visible_gen_reg[1].word.rx)
#define X86_DX (BX_CPU_THIS_PTR program_visible_gen_reg[2].word.rx)
#define X86_BX (BX_CPU_THIS_PTR program_visible_gen_reg[3].word.rx)
#define X86_SP (BX_CPU_THIS_PTR program_visible_gen_reg[4].word.rx)
#define X86_BP (BX_CPU_THIS_PTR program_visible_gen_reg[5].word.rx)
#define X86_SI (BX_CPU_THIS_PTR program_visible_gen_reg[6].word.rx)
#define X86_DI (BX_CPU_THIS_PTR program_visible_gen_reg[7].word.rx)

// access to 16 bit instruction pointer
#define X86_IP (* (Bit16u *) (((Bit8u *) &BX_CPU_THIS_PTR program_visible_eip) + BX_REG16_OFFSET))

// accesss to 32 bit general registers
#define X86_EAX BX_CPU_THIS_PTR program_visible_gen_reg[0].erx
#define X86_ECX BX_CPU_THIS_PTR program_visible_gen_reg[1].erx
#define X86_EDX BX_CPU_THIS_PTR program_visible_gen_reg[2].erx
#define X86_EBX BX_CPU_THIS_PTR program_visible_gen_reg[3].erx
#define X86_ESP BX_CPU_THIS_PTR program_visible_gen_reg[4].erx
#define X86_EBP BX_CPU_THIS_PTR program_visible_gen_reg[5].erx
#define X86_ESI BX_CPU_THIS_PTR program_visible_gen_reg[6].erx
#define X86_EDI BX_CPU_THIS_PTR program_visible_gen_reg[7].erx

// access to 32 bit instruction pointer
#define X86_EIP BX_CPU_THIS_PTR program_visible_eip

// access to 64 bit instruction pointer
#if BX_SUPPORT_X86_64==1
#define X86_RIP BX_CPU_THIS_PTR program_visible_eip
#define RIP		BX_CPU_THIS_PTR program_visible_eip
#endif


#define BX_READ_8BIT_REG(index)  (*(BX_CPU_THIS_PTR bytes_ptr[index]))
#define BX_READ_16BIT_REG(index) (BX_CPU_THIS_PTR program_visible_gen_reg[index].word.rx)
#define BX_READ_32BIT_REG(index) (BX_CPU_THIS_PTR program_visible_gen_reg[index].erx)

#define BX_READ_16BIT_BASE_REG(var, index) { var = *BX_CPU_THIS_PTR _16bit_base_reg[index]; }

#define BX_READ_16BIT_INDEX_REG(var, index) { var = *BX_CPU_THIS_PTR _16bit_index_reg[index]; }

#define BX_WRITE_8BIT_REG(index, val) {*(BX_CPU_THIS_PTR bytes_ptr[index]) = val; }

#define BX_WRITE_16BIT_REG(index, val) { BX_CPU_THIS_PTR program_visible_gen_reg[index].word.rx = val; }
#define BX_WRITE_32BIT_REG(index, val) { BX_CPU_THIS_PTR program_visible_gen_reg[index].erx = val; }



//===========================================================================
#define BX_CPU_CLASS_PTR	icpu->
#define BX_CPU_CLASS		icpu

// access to 8 bit general registers
#define RW_AL (BX_CPU_CLASS_PTR program_visible_gen_reg[0].word.byte.rl)
#define RW_CL (BX_CPU_CLASS_PTR program_visible_gen_reg[1].word.byte.rl)
#define RW_DL (BX_CPU_CLASS_PTR program_visible_gen_reg[2].word.byte.rl)
#define RW_BL (BX_CPU_CLASS_PTR program_visible_gen_reg[3].word.byte.rl)
#define RW_AH (BX_CPU_CLASS_PTR program_visible_gen_reg[0].word.byte.rh)
#define RW_CH (BX_CPU_CLASS_PTR program_visible_gen_reg[1].word.byte.rh)
#define RW_DH (BX_CPU_CLASS_PTR program_visible_gen_reg[2].word.byte.rh)
#define RW_BH (BX_CPU_CLASS_PTR program_visible_gen_reg[3].word.byte.rh)


// access to 16 bit general registers
#define RW_AX (BX_CPU_CLASS_PTR program_visible_gen_reg[0].word.rx)
#define RW_CX (BX_CPU_CLASS_PTR program_visible_gen_reg[1].word.rx)
#define RW_DX (BX_CPU_CLASS_PTR program_visible_gen_reg[2].word.rx)
#define RW_BX (BX_CPU_CLASS_PTR program_visible_gen_reg[3].word.rx)
#define RW_SP (BX_CPU_CLASS_PTR program_visible_gen_reg[4].word.rx)
#define RW_BP (BX_CPU_CLASS_PTR program_visible_gen_reg[5].word.rx)
#define RW_SI (BX_CPU_CLASS_PTR program_visible_gen_reg[6].word.rx)
#define RW_DI (BX_CPU_CLASS_PTR program_visible_gen_reg[7].word.rx)

// access to 16 bit instruction pointer
#define RW_IP (* (Bit16u *) (((Bit8u *) &BX_CPU_CLASS_PTR program_visible_eip) + BX_REG16_OFFSET))

// accesss to 32 bit general registers
#define RW_EAX BX_CPU_CLASS_PTR program_visible_gen_reg[0].erx
#define RW_ECX BX_CPU_CLASS_PTR program_visible_gen_reg[1].erx
#define RW_EDX BX_CPU_CLASS_PTR program_visible_gen_reg[2].erx
#define RW_EBX BX_CPU_CLASS_PTR program_visible_gen_reg[3].erx
#define RW_ESP BX_CPU_CLASS_PTR program_visible_gen_reg[4].erx
#define RW_EBP BX_CPU_CLASS_PTR program_visible_gen_reg[5].erx
#define RW_ESI BX_CPU_CLASS_PTR program_visible_gen_reg[6].erx
#define RW_EDI BX_CPU_CLASS_PTR program_visible_gen_reg[7].erx

// access to 32 bit instruction pointer
#define RW_EIP BX_CPU_CLASS_PTR program_visible_eip


#define READ_VIRTUAL_8BIT_REG(index)  (*(BX_CPU_CLASS_PTR bytes_ptr[index]))
#define READ_VIRTUAL_16BIT_REG(index) (BX_CPU_CLASS_PTR program_visible_gen_reg[index].word.rx)
#define READ_VIRTUAL_32BIT_REG(index) (BX_CPU_CLASS_PTR program_visible_gen_reg[index].erx)

#define WRITE_VIRTUAL_8BIT_REG(index, val) { *(BX_CPU_CLASS_PTR bytes_ptr[index]) = val; }

#define WRITE_VIRTUAL_16BIT_REG(index, val) { BX_CPU_CLASS_PTR program_visible_gen_reg[index].word.rx = val; }
#define WRITE_VIRTUAL_32BIT_REG(index, val) { BX_CPU_CLASS_PTR program_visible_gen_reg[index].erx = val; }

//#define WRITE_VIRTUAL_BYTE(seg,offset,data)		BX_CPU_THIS_PTR write_virtual_byte(seg,offset,data)
#define WRITE_VIRTUAL_BYTE		BX_CPU_CLASS_PTR write_virtual_byte
#define WRITE_VIRTUAL_WORD		BX_CPU_CLASS_PTR write_virtual_word
#define WRITE_VIRTUAL_DWORD		BX_CPU_CLASS_PTR write_virtual_dword
#define READ_VIRTUAL_BYTE		BX_CPU_CLASS_PTR read_virtual_byte
#define READ_VIRTUAL_WORD		BX_CPU_CLASS_PTR read_virtual_word
#define READ_VIRTUAL_DWORD		BX_CPU_CLASS_PTR read_virtual_dword

#define READ_RMW_VIRTUAL_BYTE		BX_CPU_CLASS_PTR read_RMW_virtual_byte
#define READ_RMW_VIRTUAL_WORD		BX_CPU_CLASS_PTR read_RMW_virtual_word
#define READ_RMW_VIRTUAL_DWORD		BX_CPU_CLASS_PTR read_RMW_virtual_dword
#define WRITE_RMW_VIRTUAL_BYTE		BX_CPU_CLASS_PTR write_RMW_virtual_byte
#define WRITE_RMW_VIRTUAL_WORD		BX_CPU_CLASS_PTR write_RMW_virtual_word
#define WRITE_RMW_VIRTUAL_DWORD		BX_CPU_CLASS_PTR write_RMW_virtual_dword


#define RW_IOPL			BX_CPU_CLASS_PTR eflags.iopl

#ifndef RW_CPL
#define RW_CPL  (BX_CPU_CLASS_PTR program_visible_sregs[BX_SEG_REG_CS].selector.rpl)
#endif


//===========================================================================

#define X86_IOPL			BX_CPU_THIS_PTR eflags.iopl

#ifndef CPL
#define CPL  (BX_CPU_THIS_PTR program_visible_sregs[BX_SEG_REG_CS].selector.rpl)
#endif


#endif  // defined(NEED_CPU_REG_SHORTCUTS)


//							保护方式下的中断与异常
		
//		助记符			向量号		说明		类型		错误码		源 
#define BX_DE_EXCEPTION   0 // Divide Error (fault)
#define BX_DB_EXCEPTION   1 // Debug (fault/trap)
#define BX_BP_EXCEPTION   3 // Breakpoint (trap)
#define BX_OF_EXCEPTION   4 // Overflow (trap)
#define BX_BR_EXCEPTION   5 // BOUND (fault)
#define BX_UD_EXCEPTION   6
#define BX_NM_EXCEPTION   7
#define BX_DF_EXCEPTION   8
#define BX_TS_EXCEPTION  10
#define BX_NP_EXCEPTION  11
#define BX_SS_EXCEPTION  12
#define BX_GP_EXCEPTION  13
#define BX_PF_EXCEPTION  14
#define BX_MF_EXCEPTION  16
#define BX_AC_EXCEPTION  17

/*
#define X86_DE_EXCEPTION //除法出错故障(除零错\除溢出) int 0x00 无错误码 #DE
#define X86_DB_EXCEPTION //边界检查故障(BOUND指令) int 0x05 无错误码 #BR
#define X86_BP_EXCEPTION 
#define X86_OF_EXCEPTION 
#define X86_BR_EXCEPTION 
#define X86_UD_EXCEPTION //非法指令编码或操作数 int 0x06 无错误码 #UD
#define X86_NM_EXCEPTION //协处理器不可用 int 0x07 无错误码 #NM
#define X86_DF_EXCEPTION //双重故障 int 0x08 errorcode #DF()
//						//系统严重出错，例如:段描述表、页表或中断描述表

#define X86_TS_EXCEPTION //非法TSS int 0x0a errorcode #TS()
#define X86_NP_EXCEPTION //段不存在故障 int 0x0b errorcode #NP
#define X86_SS_EXCEPTION //堆栈段故障 int 0x0c errorcode #SS
#define X86_GP_EXCEPTION //一般保护故障 int 0x0d errorcode #GP()
//						//所有不引起另一异常的保护违
//						//例都会引起一个一般保护异常
#define X86_PF_EXCEPTION //页面故障 int 0x0e errorcode #PF(fault-code)
// 						//处理器在CR2寄存器中存放用于
//						//引起异常的访问中的线性地址
#define X86_MF_EXCEPTION //协处理器错 int 0x10 无错误码 #MF
#define X86_AC_EXCEPTION //Any data reference in memory	int 0x11 无错误码 #AC
#define X86_MC_EXCEPTION //Model dependent machine check errors int 0x12 #MC
#define X86_XF_EXCEPTION //Floating-Point	Numeric ErrorSSE and SSE2 floating-point
//							//instructions. int 0x13 #XF
#define X86_HF_EXCEPTION //严重错误，处理器停止工作
//						//系统严重出错，例如:段描述表、页表或中断描述表


//CODE SEGMENT and DATA SEGMENT type define // 只读;读/写;向下扩展;只执行;执行/读;相容;已访问;
#define CODE_DATA_SEGMENT_R			0x0		// 只读;
#define CODE_DATA_SEGMENT_RA		0x1		// 只读;已访问;
#define CODE_DATA_SEGMENT_RW		0x2		// 读/写;
#define CODE_DATA_SEGMENT_RWA		0x3		// 读/写;已访问;
#define CODE_DATA_SEGMENT_RD		0x4		// 只读;向下扩展;
#define CODE_DATA_SEGMENT_RDA		0x5		// 只读;向下扩展;已访问;
#define CODE_DATA_SEGMENT_RWD		0x6		// 读/写;向下扩展;
#define CODE_DATA_SEGMENT_RWDA		0x7		// 读/写;向下扩展;已访问;
#define CODE_DATA_SEGMENT_E			0x8		// 只执行;
#define CODE_DATA_SEGMENT_EA		0x9		// 只执行;已访问;
#define CODE_DATA_SEGMENT_ER		0xa		// 执行/读;
#define CODE_DATA_SEGMENT_ERA		0xb		// 执行/读;已访问;
#define CODE_DATA_SEGMENT_EC		0xc		// 只执行;相容;
#define CODE_DATA_SEGMENT_ECA		0xd		// 只执行;相容;已访问;
#define CODE_DATA_SEGMENT_ERC		0xe		// 执行/读;相容;
#define CODE_DATA_SEGMENT_ERCA		0xf		// 执行/读;相容;已访问;

//SYSTEM SEGMENT and SYSTEM GATE type define	// 保留;16位;32位;TSS(可用);LDT;TSS(忙);调用门;任务门;中断门;陷阱门;
#define SYSTEM_SEGMENT_UNDEFINE0x0		0x0		// 保留;
#define SYSTEM_SEGMENT_286TSS			0x1		// 16位TSS(可用);
#define SYSTEM_SEGMENT_LDT				0x2		// LDT;
#define SYSTEM_SEGMENT_286TSS_BUSY		0x3		// 16位TSS(忙);
#define SYSTEM_GATE_286CALL				0x4		// 16位调用门;
#define SYSTEM_GATE_TASK				0x5		// 任务门;
#define SYSTEM_GATE_286INT				0x6		// 16位中断门;
#define SYSTEM_GATE_286TRAP				0x7		// 16位陷阱门;
#define SYSTEM_SEGMENT_UNDEFINE0x8		0x8		// 保留;
#define SYSTEM_SEGMENT_386TSS			0x9		// 32位TSS(可用);
#define SYSTEM_SEGMENT_UNDEFINE0xA		0xA		// 保留;
#define SYSTEM_SEGMENT_386TSS_BUSY		0xB		// 32位TSS(忙);
#define SYSTEM_GATE_386CALL				0xC		// 32位调用门;
#define SYSTEM_SEGMENT_UNDEFINE0xD		0xD		// 保留;
#define SYSTEM_GATE_386INT				0xE		// 32位中断门;
#define SYSTEM_GATE_386TRAP				0xF		// 32位陷阱门;

	{M_E, C_JtO,	D__Jb,	 D__NONE, D__NONE, 	"JO"    },//0x70,
	{M_E, C_JfO,	D__Jb,	 D__NONE, D__NONE, 	"JNO"   },//0x71,
	{M_E, C_JtC,	D__Jb,	 D__NONE, D__NONE, 	"JB"    },//0x72,
	{M_E, C_JtC,	D__Jb,	 D__NONE, D__NONE, 	"JC"    },//0x72,
	{M_E, C_JtC,	D__Jb,	 D__NONE, D__NONE, 	"JNAE"  },//0x72,
	{M_E, C_JfC,	D__Jb,	 D__NONE, D__NONE, 	"JAE"   },//0x73,
	{M_E, C_JfC,	D__Jb,	 D__NONE, D__NONE, 	"JNB"   },//0x73,
	{M_E, C_JfC,	D__Jb,	 D__NONE, D__NONE, 	"JNC"   },//0x73,
	{M_E, C_JtZ,	D__Jb,	 D__NONE, D__NONE, 	"JE"    },//0x74,
	{M_E, C_JtZ,	D__Jb,	 D__NONE, D__NONE, 	"JZ"    },//0x74,
	{M_E, C_JfZ,	D__Jb,	 D__NONE, D__NONE, 	"JNE"   },//0x75,
	{M_E, C_JfZ,	D__Jb,	 D__NONE, D__NONE, 	"JNZ"   },//0x75,
	{M_E, C_JfA,	D__Jb,	 D__NONE, D__NONE, 	"JBE"   },//0x76,
	{M_E, C_JfA,	D__Jb,	 D__NONE, D__NONE, 	"JNA"   },//0x76,
	{M_E, C_JtA,	D__Jb,	 D__NONE, D__NONE, 	"JA"    },//0x77,
	{M_E, C_JtA,	D__Jb,	 D__NONE, D__NONE, 	"JNBE"  },//0x77,
	{M_E, C_JtS,	D__Jb,	 D__NONE, D__NONE, 	"JS"    },//0x78,
	{M_E, C_JfS,	D__Jb,	 D__NONE, D__NONE, 	"JNS"   },//0x79,
	{M_E, C_JtP,	D__Jb,	 D__NONE, D__NONE, 	"JP"    },//0x7a,
	{M_E, C_JtP,	D__Jb,	 D__NONE, D__NONE, 	"JPE"   },//0x7a,
	{M_E, C_JfP,	D__Jb,	 D__NONE, D__NONE, 	"JNP"   },//0x7b,
	{M_E, C_JfP,	D__Jb,	 D__NONE, D__NONE, 	"JPO"   },//0x7b,
	{M_E, C_JtL,	D__Jb,	 D__NONE, D__NONE, 	"JL"    },//0x7c,
	{M_E, C_JtL,	D__Jb,	 D__NONE, D__NONE, 	"JNGE"  },//0x7c,
	{M_E, C_JfL,	D__Jb,	 D__NONE, D__NONE, 	"JGE"   },//0x7d,
	{M_E, C_JfL,	D__Jb,	 D__NONE, D__NONE, 	"JNL"   },//0x7d,
	{M_E, C_JfG,	D__Jb,	 D__NONE, D__NONE, 	"JLE"   },//0x7e,
	{M_E, C_JfG,	D__Jb,	 D__NONE, D__NONE, 	"JNG"   },//0x7e,
	{M_E, C_JtG,	D__Jb,	 D__NONE, D__NONE, 	"JG"	},//0x7f,
	{M_E, C_JtG,	D__Jb,	 D__NONE, D__NONE, 	"JNLE"  },//0x7f,
*/


/* MSR registers */
#define BX_MSR_P5_MC_ADDR	0x0000
#define BX_MSR_MC_TYPE		0x0001
#define BX_MSR_TSC			0x0010
#define BX_MSR_CESR			0x0011
#define BX_MSR_CTR0			0x0012
#define BX_MSR_CTR1			0x0013
#define BX_MSR_APICBASE		0x001b
#define BX_MSR_EBL_CR_POWERON	0x002a
#define BX_MSR_TEST_CTL			0x0033
#define BX_MSR_BIOS_UPDT_TRIG	0x0079
#define BX_MSR_BBL_CR_D0	0x0088
#define BX_MSR_BBL_CR_D1	0x0089
#define BX_MSR_BBL_CR_D2	0x008a
#define BX_MSR_BBL_CR_D3	0x008b	/* = BIOS_SIGN */
#define BX_MSR_PERFCTR0		0x00c1
#define BX_MSR_PERFCTR1		0x00c2
#define BX_MSR_MTRRCAP		0x00fe
#define BX_MSR_BBL_CR_ADDR	0x0116
#define BX_MSR_BBL_DECC		0x0118
#define BX_MSR_BBL_CR_CTL	0x0119
#define BX_MSR_BBL_CR_TRIG	0x011a
#define BX_MSR_BBL_CR_BUSY	0x011b
#define BX_MSR_BBL_CR_CTL3	0x011e
#define BX_MSR_MCG_CAP		0x0179
#define BX_MSR_MCG_STATUS	0x017a
#define BX_MSR_MCG_CTL		0x017b
#define BX_MSR_EVNTSEL0		0x0186
#define BX_MSR_EVNTSEL1		0x0187
#define BX_MSR_DEBUGCTLMSR	0x01d9
#define BX_MSR_LASTBRANCHFROMIP	0x01db
#define BX_MSR_LASTBRANCHTOIP	0x01dc
#define BX_MSR_LASTINTOIP		0x01dd
#define BX_MSR_ROB_CR_BKUPTMPDR6	0x01e0
#define BX_MSR_MTRRPHYSBASE0	0x0200
#define BX_MSR_MTRRPHYSMASK0	0x0201
#define BX_MSR_MTRRPHYSBASE1	0x0202

typedef struct
{
  /* 31|30|29|28|27|26|25|24|23|22|21|20|19|18|17|16
   * ==|==|=====|==|==|==|==|==|==|==|==|==|==|==|==
   *  0| 0| 0| 0| 0| 0| 0| 0| 0| 0|ID|VP|VF|AC|VM|RF
   *
   * 15|14|13|12|11|10| 9| 8| 7| 6| 5| 4| 3| 2| 1| 0
   * ==|==|=====|==|==|==|==|==|==|==|==|==|==|==|==
   *  0|NT| IOPL|OF|DF|IF|TF|SF|ZF| 0|AF| 0|PF| 1|CF
   */

	// In order to get access to these fields from the Dynamic Translation
	// code, using only 8bit offsets, I needed to move these fields
	// together.
	unsigned cf;
	unsigned pf;
	unsigned af;
	unsigned zf;
	unsigned sf;
	unsigned of;

	Boolean bit1;
	Boolean bit3;
	Boolean bit5;
	Boolean tf;
	Boolean if_;
	Boolean df;

#if BX_CPU_LEVEL >= 2
	Bit8u   iopl;
	Boolean nt;
#endif
	Boolean bit15;
#if BX_CPU_LEVEL >= 3
	Boolean rf;
	Boolean vm;
#endif
#if BX_CPU_LEVEL >= 4
	Boolean ac;  // alignment check
	// Boolean vif; // Virtual Interrupt Flag
	// Boolean vip; // Virtual Interrupt Pending
	Boolean id;  // late model 486 and beyond had CPUID
#endif

	union
	{
		struct
		{
			unsigned of:8;
			unsigned cf:1; //0
			unsigned b1:1; //1
			unsigned pf:1; //2
			unsigned b3:1; //3
			unsigned af:1; //4
			unsigned b5:1; //5
			unsigned zf:1; //6
			unsigned sf:1; //7
		}Descr;

		struct
		{
			Bit8u seto;
			Bit8u lahf;
		}Word;

		Bit32u	eax;

	} x86;
	
} bx_flags_reg_t;


#if BX_CPU_LEVEL >= 2
typedef struct
{
	Bit32u  val32; // 32bit value of register

	// bitfields broken out for efficient access
#if BX_CPU_LEVEL >= 3
	Boolean pg; // paging
#endif

// CR0 notes:
//   Each x86 level has its own quirks regarding how it handles
//   reserved bits.  I used DOS DEBUG.EXE in real mode on the
//   following processors, tried to clear bits 1..30, then tried
//   to set bits 1..30, to see how these bits are handled.
//   I found the following:
//
//   Processor    try to clear bits 1..30    try to set bits 1..30
//   386          7FFFFFF0                   7FFFFFFE
//   486DX2       00000010                   6005003E
//   Pentium      00000010                   7FFFFFFE
//   Pentium-II   00000010                   6005003E
//
// My assumptions:
//   All processors: bit 4 is hardwired to 1 (not true on all clones)
//   386: bits 5..30 of CR0 are also hardwired to 1
//   Pentium: reserved bits retain value set using mov cr0, reg32
//   486DX2/Pentium-II: reserved bits are hardwired to 0

#if BX_CPU_LEVEL >= 4
	Boolean cd; // cache disable
	Boolean nw; // no write-through
	Boolean am; // alignment mask
	Boolean wp; // write-protect
	Boolean ne; // numerics exception
#endif

	Boolean ts; // task switched
	Boolean em; // emulate math coprocessor
	Boolean mp; // monitor coprocessor
	Boolean pe; // protected mode enable
} bx_cr0_t;
#endif

#if BX_CPU_LEVEL >= 5
typedef struct
{
	Bit8u p5_mc_addr;
	Bit8u p5_mc_type;
	Bit8u tsc;
	Bit8u cesr;
	Bit8u ctr0;
	Bit8u ctr1;
	Bit64u apicbase;
	/* TODO finish of the others */
} bx_regs_msr_t;
#endif

typedef struct
{	/* bx_selector_t */
	Bit16u value;   /* the 16bit value of the selector */
#if BX_CPU_LEVEL >= 2
    /* the following fields are extracted from the value field in protected
       mode only.  They're used for sake of efficiency */
	Bit16u index;   /* 13bit index extracted from value in protected mode */
	Bit8u  ti;      /* table indicator bit extracted from value */
	Bit8u  rpl;     /* RPL extracted from value */
	Boolean cpl__3; // system status or user status
#endif
} bx_selector_t;

typedef struct
{
	Boolean valid;         /* 0 = invalid, 1 = valid */
	Boolean p;             /* present */
	Bit8u   dpl;           /* descriptor privilege level 0..3 */
	Boolean segment;       /* 0 = system/gate, 1 = data/code segment */
	Bit8u   type;          /* For system & gate descriptors, only
	                      *  0 = invalid descriptor (reserved)
                          *  1 = 286 available Task State Segment (TSS)
                          *  2 = LDT descriptor
                          *  3 = 286 busy Task State Segment (TSS)
                          *  4 = 286 call gate
                          *  5 = task gate
                          *  6 = 286 intel_interrupt gate
                          *  7 = 286 trap gate
                          *  8 = (reserved)
                          *  9 = 386 available TSS
                          * 10 = (reserved)
                          * 11 = 386 busy TSS
                          * 12 = 386 call gate
                          * 13 = (reserved)
                          * 14 = 386 intel_interrupt gate
                          * 15 = 386 trap gate */
	Bit8u AR_byte;

	union
	{
		struct
		{
			Boolean executable;    /* 1=code, 0=data or stack segment */
			Boolean c_ed;          /* for code: 1=conforming,
									  for data/stack: 1=expand down */
			Boolean r_w;           /* for code: readable?, for data/stack: writeable? */
			Boolean a;             /* accessed? */
			Bit32u  base;          /* base address: 286=24bits, 386=32bits */
			Bit32u  limit;         /* limit: 286=16bits, 386=20bits */
			Bit32u  limit_scaled;  /* for efficiency, this contrived field is set to
							        * limit for byte granular, and
									* (limit << 12) | 0xfff for page granular seg's
									*/
#if BX_CPU_LEVEL >= 3
		    Boolean g;             /* granularity: 0=byte, 1=4K (page) */
			Boolean d_b;           /* default size: 0=16bit, 1=32bit */
			Boolean avl;           /* available for use by system */
#endif
		} segment;

		struct
		{
			Bit8u   word_count;    /* 5bits (0..31) #words to copy from caller's stack
					                * to called procedure's stack.  (call gates only)*/
		    Bit16u  dest_selector;
			Bit16u  dest_offset;
		} gate286;

		struct
		{			               // type 5: Task Gate Descriptor
			Bit16u  tss_selector;  // TSS segment selector
		} taskgate;

#if BX_CPU_LEVEL >= 3
		struct
		{
			Bit8u   dword_count;   /* 5bits (0..31) #dwords to copy from caller's stack
					                * to called procedure's stack.  (call gates only)*/
			Bit16u  dest_selector;
			Bit32u  dest_offset;
		} gate386;
#endif
		struct
		{
			Bit32u  base;          /* 24 bit 286 TSS base  */
			Bit16u  limit;         /* 16 bit 286 TSS limit */
		} tss286;
#if BX_CPU_LEVEL >= 3
		struct
		{
			Bit32u  base;          /* 32 bit 386 TSS base  */
			Bit32u  limit;         /* 20 bit 386 TSS limit */
			Bit32u  limit_scaled;  // Same notes as for 'segment' field
			Boolean g;             /* granularity: 0=byte, 1=4K (page) */
			Boolean avl;           /* available for use by system */
		} tss386;
#endif
		struct
		{
			Bit32u  base;  /* 286=24 386+ =32 bit LDT base */
			Bit16u  limit; /* 286+ =16 bit LDT limit */
		} ldt;
	} u;

} bx_descriptor_t;

typedef struct
{
	bx_selector_t  selector;
	bx_descriptor_t  cache;
	char strseg[4];
	int exception_number;

} bx_segment_reg_t;

#if BX_USE_CPU_SMF == 0
// normal member functions.  This can ONLY be used within BX_CPU_C classes.
// Anyone on the outside should use the BX_CPU macro (defined in bochs.h) 
// instead.
#  define BX_CPU_THIS_PTR	this->
#  define BX_CPU_THIS		this
#  define BX_SMF
#  define BX_CPU_C_PREFIX	BX_CPU_C::
// with normal member functions, calling a member fn pointer looks like
// object->*(fnptr)(arg, ...);
// Since this is different from when SMF=1, encapsulate it in a macro.
#  define BX_CPU_CALL_METHOD(func, args) BX_INSTR_OPCODE_BEGIN(BX_CPU_THIS_PTR program_visible_sregs[BX_SREG_CS].cache.u.segment.base + BX_CPU_THIS_PTR prev_eip); (((BxExecutePtr_t) (func))) args BX_INSTR_OPCODE_END(BX_CPU_THIS_PTR program_visible_sregs[BX_SREG_CS].cache.u.segment.base + BX_CPU_THIS_PTR prev_eip);
#else
// static member functions.  With SMF, there is only one CPU by definition.
//#  define BX_CPU_THIS_PTR  BX_CPU(0)->

#  define BX_CPU_THIS_PTR	bx_cpu.
#  define BX_CPU_THIS		&bx_cpu
#  define BX_SMF			static
#  define BX_CPU_C_PREFIX
#  define BX_CPU_CALL_METHOD(func, args)   BX_INSTR_OPCODE_BEGIN(BX_CPU_THIS_PTR program_visible_sregs[BX_SREG_CS].cache.u.segment.base + BX_CPU_THIS_PTR prev_eip); ((BxExecutePtr_t) (func)) args; BX_INSTR_OPCODE_END (BX_CPU_THIS_PTR program_visible_sregs[BX_SREG_CS].cache.u.segment.base + BX_CPU_THIS_PTR prev_eip);
#endif


typedef void * (*BxVoidFPtr_t)(void);
class BX_CPU_C;
class bxInstruction_c;

#define OPCODEb1(i)			i->i_b1
#define OPCODEb2(i)			i->i_b2
#define MODRMrm(i)			i->i_rm
#define MODRMnnn(i)			i->i_nnn
#define MODRMSeg(i)			i->i_seg
#define IMMEDIATEIb(i)		i->Word.i_Ib
#define IMMEDIATEIw(i)		i->i_Iw
#define IMMEDIATEId(i)		i->i_Id
#define IMMEDIATEIb2(i)		i->i_Ib2
#define IMMEDIATEIw2(i)		i->i_Iw2

struct bxReadWriteGuess
{
	Bit32u linear_address;
	Bit32u remain_bytes;
	Bit8u *host_page_ptr,*host_page_ptr1;
	Bit32u *stamp_ptr,*stamp_ptr1;
};

class bxInstruction_c
{
public:
	// Function pointers; a function to resolve the modRM address
	// given the current state of the CPU and the instruction data,
	// and a function to execute the instruction after resolving
	// the memory address (if any).

#if BX_USE_CPU_SMF
//	void (*ResolveModrm)(BX_CPU_C * , bxInstruction_c * );
//	void (*execute)(BX_CPU_C * , bxInstruction_c * );
#else
//	void (BX_CPU_C::*ResolveModrm)(BX_CPU_C * , bxInstruction_c * );
//	void (BX_CPU_C::*execute)(BX_CPU_C * , bxInstruction_c * );
#endif

	void (*ResolveModrm)(BX_CPU_C * , bxInstruction_c * );
	void (*execute)(BX_CPU_C * , bxInstruction_c * );


#if BX_DYNAMIC_TRANSLATION
	BxVoidFPtr_t DTResolveModrm;
#endif
#if BX_DYNAMIC_TRANSLATION
	unsigned DTAttr;
	Bit8u *   (*DTFPtr)(Bit8u *, bxInstruction_c *);
	unsigned DTMemRegsUsed;
#endif

	Bit8u i_b1;	// opcode1 byte
	Bit8u i_b2;	// mod-nnn-r/m byte
    Bit8u i_nnn;
    Bit8u i_rm;
	Bit8u i_bytes;	// instruction bytes
	Bit8u i_seg;

	short ReadWriteGuess; //本指令内存读写猜测

	struct
	{
		unsigned char os_32:1;	// operand size is 32bit
		unsigned char as_32:1;	// address size is 32bit
	}size_mode;

	union
	{
		Bit32u   i_Id;
		Bit16u   i_Iw;
		struct
		{
			Bit8u	i_Ib;
			Bit8u	shift;
		}Word;
	};


	union
	{
		Bit16u displ16u; // for 16-bit modrm forms
		Bit32u displ32u; // for 32-bit modrm forms
        Bit8u    i_Ib2; // for ENTER_IwIb
        Bit16u   i_Iw2; // for JMP_Ap
	};

public:

  BX_CPP_INLINE unsigned  as32B(void) {
		return size_mode.as_32;
	}
  BX_CPP_INLINE unsigned  os32B(void) {
		return size_mode.os_32;
	}
  BX_CPP_INLINE unsigned seg(void) {
		return i_seg;
  }
  BX_CPP_INLINE unsigned b1(void) {
		return i_b1;
  }

  // Note this is the highest field, and thus needs no masking.
  // DON'T PUT ANY FIELDS HIGHER THAN THIS ONE WITHOUT ADDING A MASK.
  BX_CPP_INLINE unsigned ilen(void) {
      return i_bytes;
      }

  BX_CPP_INLINE unsigned modrm() { return i_b2; }
  BX_CPP_INLINE unsigned mod() { return i_b2 & 0xc0; }
  BX_CPP_INLINE unsigned modC0()
    {
    // This is a cheaper way to test for modRM instructions where
    // the mod field is 0xc0.  FetchDecode flags this condition since
    // it is quite common to be tested for.
    return (i_b2>=0xc0);
    }
//  BX_CPP_INLINE unsigned nnn() {
//      return nnn;
//      }
//  BX_CPP_INLINE unsigned rm()  { return rm; }

};

typedef void (*BxVirtualToRealityPtr_t)(void);

#if BX_USE_CPU_SMF
//typedef void (*BxExecutePtr_t)(BX_CPU_C *,bxInstruction_c *);
typedef int  (*BxTranslatePtr_t)(bxInstruction_c *instr,int addrsize,int modrmlength,Bit8u *iptr,Bit8u *tptr);
#else
//typedef void (BX_CPU_C::*BxExecutePtr_t)(BX_CPU_C *,bxInstruction_c *);
typedef int  (BX_CPU_C::*BxTranslatePtr_t)(bxInstruction_c *instr,int addrsize,int modrmlength,Bit8u *iptr,Bit8u *tptr);
#endif

typedef void (*BxExecutePtr_t)(BX_CPU_C *,bxInstruction_c *);


// ========== iCache =============================================
#define BX_SupportICache 0
// ========== iCache =============================================

#if BX_SupportICache

#define BxICacheEntries (16*(4096))  // Must be a power of 2.
  // bit31: 1=CS is 32/64-bit, 0=CS is 16-bit.
  // bit30: 1=Long Mode, 0=not Long Mode.
  // bit29: 1=iCache page, 0=Data.
#define ICacheWriteStampInvalid   0x1fffffff
#define ICacheWriteStampMax       0x1fffffff // Decrements from here.
#define ICacheWriteStampMask      0x1fffffff

class bxICacheEntry_c {
  public:

  Bit32u pAddr;       // Physical address of the instruction.
  Bit32u writeStamp;  // Generation ID.  Each write to a physical page
                      // decrements this value.
  bxInstruction_c i;  // The instruction decode information.
  };

#define BXREADWRITEMEMORYHOLES 16

struct bxReadWriteMemoryHole {
  Bit32u front_dummy;
  Bit8u bitMap[512];	//512 * 8 = 4096
  Bit32u dummy;
  Bit32u LinearAddress;
  Bit32u page;
  int busy;
};

struct bxPageHoleEntry {
  Bit32u laddr;
  Bit32u paddr;
  Bit32u bitLen;
  Bit8u bitMap[32];
  Bit8u *pMaping;
};

class bxICache_c {
  public:

  bxICacheEntry_c entry[BxICacheEntries/8];
  bxReadWriteGuess guess[BxICacheEntries/8/4];
  bxReadWriteGuess PushPop[32];

  short iAllocStampEntry[BxICacheEntries];
  short iAllocStamp;

  bxReadWriteMemoryHole hole[BXREADWRITEMEMORYHOLES];
  bxPageHoleEntry writeHoleEntries[128];

  int iAllocHoleEntry;
  int iAllocHole;
  int iAllocGuess;

  // A table (dynamically allocated) to store write-stamp
  // generation IDs.  Each time a write occurs to a physical page,
  // a generation ID is decremented.  Only iCache entries which have
  // write stamps matching the physical page write stamp are valid.
  Bit32u *pageWriteStampTable; // Allocated later.
  Bit8u *pageWriteHoleTable; // Allocated later.
  Bit8u *pageWriteHoleMaping; // Allocated later.

  Bit32u  fetchModeMask;

  bxICache_c()
  {
  }

  ~bxICache_c()
  {
  }

  BX_CPP_INLINE void  init(void) {
    // Initially clear the iCache;
    memset(this, 0, sizeof(*this));
    pageWriteStampTable = NULL;
    pageWriteHoleTable = NULL;
	iAllocHoleEntry = 0;
	unsigned i;
    for (i=0; i<BxICacheEntries; i++) {
      //entry[i].writeStamp = ICacheWriteStampInvalid;
      iAllocStampEntry[i] = 0;
      }
    for (i=0; i<BXREADWRITEMEMORYHOLES; i++) {
	  hole[i].busy = 0;
      }
    }

	BX_CPP_INLINE void  exit(void)
	{
		if (pageWriteStampTable)
		{
			free(pageWriteStampTable);
			pageWriteStampTable = NULL;
		}

		if (pageWriteHoleTable)
		{
			free(pageWriteHoleTable);
			pageWriteHoleTable = NULL;
		}
	}

  BX_CPP_INLINE void alloc(unsigned memSizeInBytes) {
    unsigned i;
	pageWriteStampTable = (Bit32u*) malloc(sizeof(Bit32u) * (memSizeInBytes>>12));
    for (i=0; i<(memSizeInBytes>>12); i++) {
      pageWriteStampTable[i] = ICacheWriteStampInvalid;
      }

	pageWriteHoleTable = (Bit8u*) malloc((memSizeInBytes>>12) + (memSizeInBytes>>12)/8);
	pageWriteHoleMaping = pageWriteHoleTable + (memSizeInBytes>>12);
	for (i=0; i<(memSizeInBytes>>12) + (memSizeInBytes>>12)/8; i++) {
      pageWriteHoleTable[i] = 0;
      }
    }

  int gatherWriteHole(bxReadWriteMemoryHole *h);
  bxReadWriteMemoryHole *allocWriteHole(Bit32u a20Addr);

  BX_CPP_INLINE void decWriteHole(BX_CPU_C *cpu,Bit32u a20Addr,int bits = 15)
  {
	  bxReadWriteMemoryHole *h;

	  h = hole + pageWriteHoleTable[a20Addr>>12];

	  if (h->page!=(a20Addr&0xffff000))
	  {
		 h = allocWriteHole(a20Addr);
	  }

#ifdef BX_BIG_ENDIAN
	  h->bitMap[((a20Addr&0xfff)>>3)] |= (bits<<(a20Addr&7));
	  h->bitMap[((a20Addr&0xfff)>>3)+1] |= (bits<<(a20Addr&7))>>8;
#else
	  *(Bit16u*)&h->bitMap[((a20Addr&0xfff)>>3)] |= (bits<<(a20Addr&7));
#endif
  }

  BX_CPP_INLINE void decWriteStamp(BX_CPU_C *cpu, Bit32u a20Addr);

  BX_CPP_INLINE void clear(void) {
    memset(this, 0, sizeof(*this));
    }
  BX_CPP_INLINE unsigned hash(Bit32u pAddr) {
    // A pretty dumb hash function for now.
    return pAddr & (BxICacheEntries-1);
    }
  BX_CPP_INLINE Bit32u createFetchModeMask(BX_CPU_C *cpu);
  };
#endif
// ===============================================================


#if BX_DYNAMIC_TRANSLATION
typedef Bit8u * (*BxDTASResolveModrm_t)(Bit8u *, bxInstruction_c *,
  unsigned, unsigned);
#endif

//extern BxExecutePtr_t BxResolve32Mod1or2EffectAddressBaseIndexScaled[0x100];
//extern BxExecutePtr_t BxResolve32Mod0EffectAddressBaseIndexScaled[0x100];

#if BX_DYNAMIC_TRANSLATION
// Arrays of function pointers which handle a specific
// mod-rm address format
extern BxDTASResolveModrm_t  BxDTResolve32Mod0[];
extern BxDTASResolveModrm_t  BxDTResolve32Mod1or2[];
extern BxDTASResolveModrm_t  BxDTResolve32Mod0Base[];
extern BxDTASResolveModrm_t  BxDTResolve32Mod1or2Base[];
extern BxDTASResolveModrm_t  BxDTResolve16Mod1or2[];
extern BxDTASResolveModrm_t  BxDTResolve16Mod0[];
#endif


#if BX_CPU_LEVEL < 2
  /* no GDTR or IDTR register in an 8086 */
#else
typedef struct
{
	Bit32u                 base;      /* base address: 24bits=286,32bits=386 */
	Bit16u                 limit;     /* limit, 16bits */
} bx_global_segment_reg_t;
#endif


#if BX_USE_TLB

typedef struct
{
    Bit32u lpf; // linear page frame
    Bit32u ppf; // physical page frame
    Bit32u pte_addr; // Page Table Address for updating A & D bits
    Bit32u combined_access;
} bx_TLB_entry;

#endif  // #if BX_USE_TLB


#ifdef BX_BIG_ENDIAN
typedef struct
{
	union
	{
		Bit32u erx;
		struct
		{
			Bit16u word_filler;
			union
			{
				Bit16u rx;
				struct
				{
					Bit8u rh;
					Bit8u rl;
				} byte;
			};
		} word;
	};

} bx_gen_reg_t;

#else
typedef struct
{
	union
	{
		Bit32u erx;
		struct
		{
			union
			{
				Bit16u rx;
				struct
				{
					Bit8u rl;
					Bit8u rh;
				} byte;
			};
			Bit16u word_filler;
		} word;
	};

} bx_gen_reg_t;

#endif

typedef enum
{
	APIC_TYPE_NONE,
	APIC_TYPE_IOAPIC,
	APIC_TYPE_LOCAL_APIC
} bx_apic_type_t;

#define APIC_BASE_ADDR	0xfee00000	// default APIC address

#if BX_SUPPORT_APIC
class bx_generic_apic_c //: public logfunctions
{
protected:
	Bit32u base_addr;
	Bit8u id;
#define APIC_UNKNOWN_ID 0xff
#define APIC_VERSION_ID 0x00170011  // same version as 82093 IOAPIC
public:
	bx_generic_apic_c ();
	virtual ~bx_generic_apic_c ();
	virtual void init ();
	virtual void hwreset () { }
	Bit32u get_base (void) { return base_addr; }
	void set_base (Bit32u newbase);
	void set_id (Bit8u newid);
	Bit8u get_id () { return id; }
	virtual char *get_name();
	Boolean is_selected (Bit32u addr, Bit32u len);
	void read (Bit32u addr, void *data, unsigned len);
	virtual void read_aligned(Bit32u address, Bit32u *data, unsigned len);
	virtual void write(Bit32u address, Bit32u *value, unsigned len);
	virtual void startup_msg (Bit32u _vector);
	// on local APIC, trigger means deliver to the CPU.
	// on I/O APIC, trigger means direct to another APIC according to table.
	virtual void trigger_irq (unsigned num, unsigned from);
	virtual void untrigger_irq (unsigned num, unsigned from);
	virtual Bit32u get_delivery_bitmask (Bit8u dest, Bit8u dest_mode);
	virtual Boolean deliver (Bit8u destination, Bit8u dest_mode, Bit8u delivery_mode, Bit8u _vector, Bit8u polarity, Bit8u trig_mode);
	virtual Boolean match_logical_addr (Bit8u address);
	virtual bx_apic_type_t get_type ();
	virtual void set_arb_id (int newid);  // only implemented on local apics
};

class bx_local_apic_c : public bx_generic_apic_c
{
#define BX_LOCAL_APIC_MAX_INTS 256
	// TMR=trigger mode register.  Cleared for edge-triggered interrupts
	// and set for level-triggered interrupts.  If set, local APIC must send
	// EOI message to all other APICs.  EOI's are not implemented.
	Bit8u tmr[BX_LOCAL_APIC_MAX_INTS];
	// IRR=intel_interrupt request register.  When an intel_interrupt is triggered by
	// the I/O APIC or another processor, it sets a bit in irr.  The bit is
	// cleared when the intel_interrupt is acknowledged by the processor.
	Bit8u irr[BX_LOCAL_APIC_MAX_INTS];
	// ISR=in-service register.  When an IRR bit is cleared, the corresponding
	// bit in ISR is set.  The ISR bit is cleared when 
	Bit8u isr[BX_LOCAL_APIC_MAX_INTS];
	Bit32u arb_id, arb_priority, task_priority, log_dest, dest_format, spurious_vec;
	Bit32u lvt[6];
#define APIC_LVT_TIMER   0
#define APIC_LVT_THERMAL 1
#define APIC_LVT_PERFORM 2
#define APIC_LVT_LINT0   3
#define APIC_LVT_LINT1   4
#define APIC_LVT_ERROR   5
	Bit32u timer_initial, timer_current, timer_divconf;
	Boolean timer_active;  // internal state, not accessible from bus
	Bit32u timer_divide_counter, timer_divide_factor;
	Bit32u icr_high, icr_low;
	Bit32u err_status;
#define APIC_ERR_ILLEGAL_ADDR    0x80
#define APIC_ERR_RX_ILLEGAL_VEC  0x40
#define APIC_ERR_TX_ILLEGAL_VEC  0x20
#define APIC_ERR_RX_ACCEPT_ERR   0x08
#define APIC_ERR_TX_ACCEPT_ERR   0x04
#define APIC_ERR_RX_CHECKSUM     0x02
#define APIC_ERR_TX_CHECKSUM     0x01
public:
	bx_local_apic_c(BX_CPU_C *mycpu);
	virtual ~bx_local_apic_c(void);
	BX_CPU_C *cpu;
	virtual void hwreset ();
	virtual void init ();
	BX_CPU_C *get_cpu (Bit8u id);
	void set_id (Bit8u newid);   // redefine to set cpu->name
	virtual char *get_name();
	virtual void write (Bit32u addr, Bit32u *data, unsigned len);
	virtual void read_aligned(Bit32u address, Bit32u *data, unsigned len);
	virtual void startup_msg (Bit32u _vector);
	// on local APIC, trigger means raise the CPU's INTR line.  For now
	// I also have to raise pc_system.INTR but that should be replaced
	// with the cpu-specific INTR signals.
	virtual void trigger_irq (unsigned num, unsigned from);
	virtual void untrigger_irq (unsigned num, unsigned from);
	Bit8u acknowledge_int ();  // only the local CPU should call this
	int highest_priority_int (Bit8u *array);
	void service_local_apic ();
	void print_status ();
	virtual Boolean match_logical_addr (Bit8u address);
	virtual Boolean is_local_apic () { return true; }
	virtual bx_apic_type_t get_type () { return APIC_TYPE_LOCAL_APIC; }
	virtual Bit32u get_delivery_bitmask (Bit8u dest, Bit8u dest_mode);
	virtual Boolean deliver (Bit8u destination, Bit8u dest_mode, Bit8u delivery_mode, Bit8u _vector, Bit8u polarity, Bit8u trig_mode);
	Bit8u get_ppr ();
	Bit8u get_apr ();
	void periodic (Bit32u usec_delta);
	void set_divide_configuration (Bit32u value);
	virtual void update_msr_apicbase(Bit32u newaddr);
	virtual void set_arb_id (int newid);
};

#define APIC_MAX_ID 16
extern bx_generic_apic_c *apic_index[APIC_MAX_ID];
#endif // if BX_SUPPORT_APIC

typedef void (*BxDTShim_t)(void);

//====================================================
typedef struct _X86_SEGMENT_DESCRIPTOR  //descriptor
{
	unsigned limit_L0:8;
	unsigned limit_L1:8;
	unsigned base_L0:8;
	unsigned base_L1:8;
	unsigned base_H0:8;
	unsigned TYPE:4;		//type
	unsigned DT:1;			//storage segment (value=1) system segment and system gate (value=0)
	unsigned DPL:2;			//Descriptor Privilege Level
	unsigned P:1;			//Present
	unsigned limit_H:4;
	unsigned AVL:1;	//soft accessed
	unsigned    :1; //reseved (value=0)
	unsigned D:1; // segment size BIT31(1) BIT16(0) (storage segment)
	unsigned G:1; //Granularity
	unsigned base_H1:8;
	
} X86_SEGMENT_DESCRIPTOR;

typedef struct _X86_GATE_DESCRIPTOR  //system  gate
{
	unsigned offset_L0:8;
	unsigned offset_L1:8;
	unsigned select_L0:8;
	unsigned select_L1:8;
	unsigned dwordcount:5;
	unsigned	  :3; // reseved (value=0)
	unsigned TYPE:4; //type
	unsigned DT:1;			//storage segment (value=1) system segment and system gate (value=0)
	unsigned DPL:2;			//Descriptor Privilege Level
	unsigned P:1;			//Present
	unsigned offset_H0:8;
	unsigned offset_H1:8;
	
} X86_GATE_DESCRIPTOR;

typedef struct _TASK16SEGMENT
{
	Bit16u TaskLink;
	//-------------
	Bit16u SP0;
	Bit16u SS0;
	Bit16u SP1;
	Bit16u SS1;
	Bit16u SP2;
	Bit16u SS2;
	//-------------
	Bit16u ip;
	Bit16u fl;
	Bit16u ax;
	Bit16u cx;
	Bit16u dx;
	Bit16u bx;
	Bit16u sp;
	Bit16u bp;
	Bit16u si;
	Bit16u di;
	//-------------
	Bit16u ES;
	Bit16u CS;
	Bit16u SS;
	Bit16u DS;
	//-------------
	Bit16u LDT;

} TASK16SEGMENT;

typedef struct _LOADALL286_DESCRIPTOR_T
{
	union
	{
		struct
		{
			unsigned Base:24;	//	24bit segment line base address
		}All;

		struct
		{
			unsigned byte0:8;		// base0
			unsigned byte1:8;		// base1
			unsigned byte2:8;		// base2
			unsigned TYPE:4;		//type
			unsigned DT:1;			//storage segment (value=1) system segment and system gate (value=0)
			unsigned DPL:2;			//Descriptor Privilege Level
			unsigned P:1;			//Present
		}Descr;

		struct
		{
			Bit16u word0;
			Bit16u word1;
			Bit16u Limit; // segment limit
		}Dword;
	};

} LOADALL286_DESCRIPTOR_T;

typedef struct _LOADALL286
{
	Bit16u _[3];
	Bit16u MSW;
	Bit16u __[7];
	Bit16u TR;
	Bit16u fl;
	Bit16u ip;
	Bit16u LDTR;
	Bit16u DS;
	Bit16u SS;
	Bit16u CS;
	Bit16u ES;

	Bit16u di;
	Bit16u si;
	Bit16u bp;
	Bit16u sp;
	Bit16u bx;
	Bit16u dx;
	Bit16u cx;
	Bit16u ax;

	LOADALL286_DESCRIPTOR_T ES_D;
	LOADALL286_DESCRIPTOR_T CS_D;
	LOADALL286_DESCRIPTOR_T SS_D;
	LOADALL286_DESCRIPTOR_T DS_D;

	LOADALL286_DESCRIPTOR_T GDT;
	LOADALL286_DESCRIPTOR_T LDT;

	LOADALL286_DESCRIPTOR_T IDT;
	LOADALL286_DESCRIPTOR_T TSS;

} LOADALL286;

typedef struct _TASK32SEGMENT
{
	Bit16u TaskLink;
	Bit16u TaskLink_word_filler;
	//-------------
	Bit32u ESP0;
	Bit16u SS0;
	Bit16u SS0_word_filler;
	Bit32u ESP1;
	Bit16u SS1;
	Bit16u SS1_word_filler;
	Bit32u ESP2;
	Bit16u SS2;
	Bit16u SS2_word_filler;
	//-------------
	Bit32u CR3;
	Bit32u eip;
	Bit32u efl;
	Bit32u eax;
	Bit32u ecx;
	Bit32u edx;
	Bit32u ebx;
	Bit32u esp;
	Bit32u ebp;
	Bit32u esi;
	Bit32u edi;
	//-------------
	Bit16u ES;
	Bit16u ES_word_filler;
	Bit16u CS;
	Bit16u CS_word_filler;
	Bit16u SS;
	Bit16u SS_word_filler;
	Bit16u DS;
	Bit16u DS_word_filler;
	Bit16u FS;
	Bit16u FS_word_filler;
	Bit16u GS;
	Bit16u GS_word_filler;
	//-------------
	Bit16u LDT;
	Bit16u LDT_word_filler;
	//-------------
	Bit16u Trap;
	Bit16u io_map_base;
	Bit8u io_map;
		
} TASK32SEGMENT;

typedef struct _LOADALL386_DESCRIPTOR_T
{
	struct
	{
		unsigned _:8;			// 设置为 0
		unsigned TYPE:4;		//type
		unsigned DT:1;			//storage segment (value=1);system segment and system gate (value=0)
		unsigned DPL:2;			//Descriptor Privilege Level
		unsigned P:1;			//Present
		unsigned __:8;			// 设置为 0
		unsigned ____:8;		// 设置为 0
	}Descr;
	struct
	{
		Bit32u Base;		//	segment line base address
		Bit32u Limit;	//  segment limit
	}QWord;

} LOADALL386_DESCRIPTOR_T;

typedef struct _LOADALL386
{
	Bit32u CR0;
	Bit32u efl;
	Bit32u eip;
	Bit32u edi;
	Bit32u esi;
	Bit32u ebp;
	Bit32u esp;
	Bit32u ebx;
	Bit32u edx;
	Bit32u ecx;
	Bit32u eax;
	Bit32u DR6;
	Bit32u DR7;
	Bit32u TR;
	Bit32u LDTR;
	Bit32u GS;
	Bit32u FS;
	Bit32u DS;
	Bit32u SS;
	Bit32u CS;
	Bit32u ES;
	LOADALL386_DESCRIPTOR_T TSS;
	LOADALL386_DESCRIPTOR_T IDT;
	LOADALL386_DESCRIPTOR_T GDT;
	LOADALL386_DESCRIPTOR_T LDT;
	LOADALL386_DESCRIPTOR_T GS_D;
	LOADALL386_DESCRIPTOR_T FS_D;
	LOADALL386_DESCRIPTOR_T DS_D;
	LOADALL386_DESCRIPTOR_T SS_D;
	LOADALL386_DESCRIPTOR_T CS_D;
	LOADALL386_DESCRIPTOR_T ES_D;
	Bit32u Length;
	Bit32u _[12];
	Bit32u TST;
	Bit32u IDX;
	Bit32u TempH;
	Bit32u TempG;
	Bit32u TempF;
	Bit32u TempE;
	Bit32u TempD;
	Bit32u TempC;
	Bit32u TempB;
	Bit32u TempA;
	Bit32u CR2;
	Bit32u CR3;
	Bit32u MSR0x1001L;
	Bit32u MSR0x1001H;
	Bit32u MSR0x1000L;
	Bit32u DR0;
	Bit32u DR1;
	Bit32u DR2;
	Bit32u DR3;
	Bit32u PEIP;

} LOADALL386;

typedef union //标志寄存器位段定义
{
	Bit32u eflags;

	struct  //标志寄存器位段定义
	{
		unsigned cf:1; //0
		unsigned b1:1; //1
		unsigned pf:1; //2
		unsigned b3:1; //3
		unsigned af:1; //4
		unsigned b5:1; //5
		unsigned zf:1; //6
		unsigned sf:1; //7
		
		unsigned tf:1; //8
		unsigned _if:1; //9
		unsigned df:1; //10
		unsigned of:1; //11
		unsigned iopl:2; //12--13
		unsigned nt:1; //14
		unsigned bf:1; //15
		
		unsigned rf:1; //16
		unsigned vm:1; //17
		unsigned ac:1; //18
		unsigned vif:1; //19
		unsigned _vip:1; //20
		unsigned id:1; //21
		unsigned	:2; //22--23

		unsigned	:8; //24--31
		
	}Descr;

} X86_CPU_EFLAGS;

typedef struct //mul64 div64 通用数据寄存器
{
	Bit32u l32;
	Bit32u h32;
} X86_CPU_INT64;

void DivideBit64(X86_CPU_INT64 *source,Bit32u dst,X86_CPU_INT64 *result);
void MultiplyBit64(X86_CPU_INT64 *result,Bit32u src,Bit32u dst);

//============================================

class BX_MEM_C;

#include "i387.h"

struct BxOpcodeShiftFun_t
{
	BxExecutePtr_t shiftL_EG;
	BxExecutePtr_t shiftR_EG;
	BxExecutePtr_t shiftL_EE;
	BxExecutePtr_t shiftR_EE;

};

struct BxOpcodeShiftTable_t
{
	unsigned count;
	const BxOpcodeShiftFun_t *shift_fun;
};

extern const BxOpcodeShiftTable_t BxOpcodeShiftTableG_RO__Eb[];
extern const BxOpcodeShiftTable_t BxOpcodeShiftTableG_RO__Ew[];
extern const BxOpcodeShiftTable_t BxOpcodeShiftTableG_RO__Ed[];
extern const BxOpcodeShiftTable_t BxOpcodeShiftTableG_RC__Eb[];
extern const BxOpcodeShiftTable_t BxOpcodeShiftTableG_RC__Ew[];
extern const BxOpcodeShiftTable_t BxOpcodeShiftTableG_RC__Ed[];
extern const BxOpcodeShiftTable_t BxOpcodeShiftTableG_SH__Eb[];
extern const BxOpcodeShiftTable_t BxOpcodeShiftTableG_SH__Ew[];
extern const BxOpcodeShiftTable_t BxOpcodeShiftTableG_SH__Ed[];
extern const BxOpcodeShiftTable_t BxOpcodeShiftTableG_SA__Eb[];
extern const BxOpcodeShiftTable_t BxOpcodeShiftTableG_SA__Ew[];
extern const BxOpcodeShiftTable_t BxOpcodeShiftTableG_SA__Ed[];
extern const BxOpcodeShiftTable_t BxOpcodeShiftTableG_SH_D_EwGw[];
extern const BxOpcodeShiftTable_t BxOpcodeShiftTableG_SH_D_EdGd[];

struct BxOpcodeInfo_t
{
	unsigned Attr;

	BxExecutePtr_t ExecutePtr;

	const struct BxOpcodeInfo_t *OpcodeInfoPtr;

	BxTranslatePtr_t TranslatePtr;
};

extern const BxOpcodeInfo_t BxOpcodeInfoG_INSB[];
extern const BxOpcodeInfo_t BxOpcodeInfoG_INSW[];
extern const BxOpcodeInfo_t BxOpcodeInfoG_OUTSB[];
extern const BxOpcodeInfo_t BxOpcodeInfoG_OUTSW[];
extern const BxOpcodeInfo_t BxOpcodeInfoG_MOVSB[];
extern const BxOpcodeInfo_t BxOpcodeInfoG_MOVSW[];
extern const BxOpcodeInfo_t BxOpcodeInfoG_CMPSB[];
extern const BxOpcodeInfo_t BxOpcodeInfoG_CMPSW[];
extern const BxOpcodeInfo_t BxOpcodeInfoG_STOSB[];
extern const BxOpcodeInfo_t BxOpcodeInfoG_STOSW[];
extern const BxOpcodeInfo_t BxOpcodeInfoG_LODSB[];
extern const BxOpcodeInfo_t BxOpcodeInfoG_LODSW[];
extern const BxOpcodeInfo_t BxOpcodeInfoG_SCASB[];
extern const BxOpcodeInfo_t BxOpcodeInfoG_SCASW[];

extern const BxOpcodeInfo_t BxOpcodeInfoG_INSD[];
extern const BxOpcodeInfo_t BxOpcodeInfoG_OUTSD[];
extern const BxOpcodeInfo_t BxOpcodeInfoG_MOVSD[];
extern const BxOpcodeInfo_t BxOpcodeInfoG_CMPSD[];
extern const BxOpcodeInfo_t BxOpcodeInfoG_STOSD[];
extern const BxOpcodeInfo_t BxOpcodeInfoG_LODSD[];
extern const BxOpcodeInfo_t BxOpcodeInfoG_SCASD[];

extern const BxOpcodeInfo_t BxOpcodeInfoG1EGbIb[];
extern const BxOpcodeInfo_t BxOpcodeInfoG1EGwIw[];
extern const BxOpcodeInfo_t BxOpcodeInfoG1EGwIsb[];
extern const BxOpcodeInfo_t BxOpcodeInfoG0x8fEGw[];
extern const BxOpcodeInfo_t BxOpcodeInfoG2EGbIb[];
extern const BxOpcodeInfo_t BxOpcodeInfoG2EGwIb[];
extern const BxOpcodeInfo_t BxOpcodeInfoG0xc6EGbIb[];
extern const BxOpcodeInfo_t BxOpcodeInfoG0xc7EGwIw[];
extern const BxOpcodeInfo_t BxOpcodeInfoG2EGb_1[];
extern const BxOpcodeInfo_t BxOpcodeInfoG2EGw_1[];
extern const BxOpcodeInfo_t BxOpcodeInfoG2EGbCL[];
extern const BxOpcodeInfo_t BxOpcodeInfoG2EGwCL[];
extern const BxOpcodeInfo_t BxOpcodeInfoG3EGb[];
extern const BxOpcodeInfo_t BxOpcodeInfoG3EGw[];
extern const BxOpcodeInfo_t BxOpcodeInfoG4EGb[];
extern const BxOpcodeInfo_t BxOpcodeInfoG5EGw[];
extern const BxOpcodeInfo_t BxOpcodeInfoG6[];
extern const BxOpcodeInfo_t BxOpcodeInfoG7[];
extern const BxOpcodeInfo_t BxOpcodeInfoG8EGwIb[];
extern const BxOpcodeInfo_t BxOpcodeInfoG9[];
extern const BxOpcodeInfo_t BxOpcodeInfoG1EGdId[];
extern const BxOpcodeInfo_t BxOpcodeInfoG1EGdIsb[];
extern const BxOpcodeInfo_t BxOpcodeInfoG0x8fEGd[];
extern const BxOpcodeInfo_t BxOpcodeInfoG2EGdIb[];
extern const BxOpcodeInfo_t BxOpcodeInfoG0xc7EGdId[];
extern const BxOpcodeInfo_t BxOpcodeInfoG2EGd_1[];
extern const BxOpcodeInfo_t BxOpcodeInfoG2EGdCL[];
extern const BxOpcodeInfo_t BxOpcodeInfoG5EGd[];
extern const BxOpcodeInfo_t BxOpcodeInfoG8EGdIb[];
extern const BxOpcodeInfo_t BxOpcodeInfoG1EEbIb[];
extern const BxOpcodeInfo_t BxOpcodeInfoG1EEwIw[];
extern const BxOpcodeInfo_t BxOpcodeInfoG1EEwIsb[];
extern const BxOpcodeInfo_t BxOpcodeInfoG0x8fEEw[];
extern const BxOpcodeInfo_t BxOpcodeInfoG2EEbIb[];
extern const BxOpcodeInfo_t BxOpcodeInfoG2EEwIb[];
extern const BxOpcodeInfo_t BxOpcodeInfoG0xc6EEbIb[];
extern const BxOpcodeInfo_t BxOpcodeInfoG0xc7EEwIw[];
extern const BxOpcodeInfo_t BxOpcodeInfoG2EEb_1[];
extern const BxOpcodeInfo_t BxOpcodeInfoG2EEw_1[];
extern const BxOpcodeInfo_t BxOpcodeInfoG2EEbCL[];
extern const BxOpcodeInfo_t BxOpcodeInfoG2EEwCL[];
extern const BxOpcodeInfo_t BxOpcodeInfoG3EEb[];
extern const BxOpcodeInfo_t BxOpcodeInfoG3EEw[];

extern const BxOpcodeInfo_t BxOpcodeInfoG3EGd[];
extern const BxOpcodeInfo_t BxOpcodeInfoG4EEb[];
extern const BxOpcodeInfo_t BxOpcodeInfoG5EEw[];
extern const BxOpcodeInfo_t BxOpcodeInfoG8EEwIb[];
extern const BxOpcodeInfo_t BxOpcodeInfoG1EEdId[];
extern const BxOpcodeInfo_t BxOpcodeInfoG1EEdIsb[];
extern const BxOpcodeInfo_t BxOpcodeInfoG0x8fEEd[];
extern const BxOpcodeInfo_t BxOpcodeInfoG2EEdIb[];
extern const BxOpcodeInfo_t BxOpcodeInfoG0xc7EEdId[];
extern const BxOpcodeInfo_t BxOpcodeInfoG2EEd_1[];
extern const BxOpcodeInfo_t BxOpcodeInfoG2EEdCL[];
extern const BxOpcodeInfo_t BxOpcodeInfoG3EEd[];
extern const BxOpcodeInfo_t BxOpcodeInfoG5EEd[];
extern const BxOpcodeInfo_t BxOpcodeInfoG8EEdIb[];

extern const BxOpcodeInfo_t BxOpcodeInfo[]; //512*2*2

typedef struct _X86_CPU_PROGRAM_VISIBLE_REGISTER
{
	bx_gen_reg_t gen_reg[8];
	bx_segment_reg_t sregs[8];
	Bit32u eip;
	Bit32u eflags;
} X86_CPU_PROGRAM_VISIBLE_REGISTER;

struct __LAST_READ_WRITE
{
	Bit32u read_address,write_address;
	int read_bytes,write_bytes;
	int i_bytes;
};

#if (X86CPU_MSWIN_MSDOS==0)
class BX_CPU_C : public logfunctions
#else
class BX_CPU_C //: public logfunctions
#endif
{
public: // for now...

	struct {
		Bit64u popCounter;
		Bit64u pushCounter;
		Bit64u ReadMemoryCounter;
		Bit64u WriteMemoryCounter;
		Bit64u cahceLoop;
		Bit64u fetchdecode;
	} stamp;

	bxInstruction_c *instr;

	int intNumber;
	int lastInstr;
	BxExecutePtr_t lastInstructionListTable[0x100];

	char name[64];

	// General register set
	// eax: accumulator
	// ebx: base
	// ecx: count
	// edx: data
	// ebp: base pointer
	// esi: source index
	// edi: destination index
	// esp: stack pointer
#if (X86CPU_MSWIN_MSDOS==0)
	bx_gen_reg_t program_visible_gen_reg[8];
	/* user segment register set */
	bx_segment_reg_t  program_visible_sregs[8];
    // instruction pointer
	Bit32u program_visible_eip;
	Bit32u program_visible_eflags;
#else
	X86_CPU_PROGRAM_VISIBLE_REGISTER program_visible_register;
#endif

	struct __LAST_READ_WRITE last_read_write;
	Bit8u *	bytes_ptr[8];

	/* system segment registers */
#if BX_CPU_LEVEL >= 2
	bx_global_segment_reg_t gdtr; /* global descriptor table register */
	bx_global_segment_reg_t idtr; /* intel_interrupt descriptor table register */
#endif
	bx_segment_reg_t        ldtr; /* intel_interrupt descriptor table register */
	bx_segment_reg_t        tr;   /* task register */
	
#if BX_CPU_LEVEL > 0
	// so that we can back up when handling faults, exceptions, etc.
	// we need to store the value of the instruction pointer, before
	// each fetch/execute cycle.
	Bit32u prev_eip;
	Bit32u prev_esp;
#endif

  // A few pointer to functions for use by the dynamic translation
  // code.  Keep them close to the program_visible_gen_reg declaration, so I can
  // use an 8bit offset to access them.

#if BX_DYNAMIC_TRANSLATION
  BxDTShim_t DTWrite8vShim;
  BxDTShim_t DTWrite16vShim;
  BxDTShim_t DTWrite32vShim;
  BxDTShim_t DTRead8vShim;
  BxDTShim_t DTRead16vShim;
  BxDTShim_t DTRead32vShim;
  BxDTShim_t DTReadRMW8vShim;
  BxDTShim_t DTReadRMW16vShim;
  BxDTShim_t DTReadRMW32vShim;
  BxDTShim_t DTWriteRMW8vShim;
  BxDTShim_t DTWriteRMW16vShim;
  BxDTShim_t DTWriteRMW32vShim;
  BxDTShim_t DTSetFlagsOSZAPCPtr;
  BxDTShim_t DTIndBrHandler;
  BxDTShim_t DTDirBrHandler;
#endif

	// status and control flags register set
	Bit32u jcc;
	Bit32u jcc_steps;
	Bit32u  lf_flags_status;
	bx_flags_reg_t eflags;
	bx_lf_flags_entry lf_entrys[BX_LF_INDEX_SIZE];
	BX_SMF int PRINTFLAGSINFO(int ,char *,int ,int);

#define BX_INHIBIT_INTERRUPTS 0x01
#define BX_INHIBIT_DEBUG      0x02
	// What events to inhibit at any given time.  Certain instructions
	// inhibit interrupts, some debug exceptions and single-step traps.
	unsigned inhibit_mask;

	/* debug registers 0-7 (unimplemented) */
#if BX_CPU_LEVEL >= 3
	Bit32u dr0;
	Bit32u dr1;
	Bit32u dr2;
	Bit32u dr3;
	Bit32u dr6;
	Bit32u dr7;
#endif

	/* TR3 - TR7 (Test Register 3-7), unimplemented */

	/* Control registers */
#if BX_CPU_LEVEL >= 2
	bx_cr0_t  cr0;

	Bit32u    cr1;
	Bit32u    cr2;
	Bit32u    cr3;
#endif
#if BX_CPU_LEVEL >= 4
	Bit32u    cr4;
#endif

#if BX_CPU_LEVEL >= 5
	bx_regs_msr_t	msr;  
#endif

	i387_t the_i387;
	// pointer to the address space that this processor uses.
	BX_MEM_C *mem;

	Boolean EXT; /* 1 if processing external intel_interrupt or exception
                * or if not related to current instruction,
                * 0 if current CS:IP caused exception */
	unsigned errorno;   /* signal exception during instruction emulation */

	Bit32u   debug_trap; // holds DR6 value to be set as well
	volatile Boolean async_event;
	volatile Boolean INTR;

	/* wether this CPU is the BSP always set for UP */
	Boolean bsp;
	// for accessing registers by index number
	Bit16u *_16bit_base_reg[8];
	Bit16u *_16bit_index_reg[8];
	Bit32u empty_register;

	// for decoding instructions; accessing seg reg's by index
	unsigned sreg_mod00_rm16[8];
	unsigned sreg_mod01_rm16[8];
	unsigned sreg_mod10_rm16[8];
	unsigned sreg_mod01_rm32[8];
	unsigned sreg_mod10_rm32[8];
	unsigned sreg_mod0_base32[8];
	unsigned sreg_mod1or2_base32[8];
	// for exceptions
	jmp_buf jmp_buf_env;
	Bit8u curr_exception[2];
	static const Boolean is_exception_OK[3][3];
	bx_flags_reg_t save_eflags;
	bx_segment_reg_t save_cs;
	bx_segment_reg_t save_ss;
	Bit32u           save_eip;
	Bit32u           save_esp;



  // Boundaries of current page, based on EIP
  bx_address eipPageBias;
  bx_address eipPageWindowSize;
  Bit8u     *eipFetchPtr;
  Bit32u     pAddrA20Page; // Guest physical address of current instruction
                           // page with A20() already applied.


	// For prefetch'ing instructions
	int bytesleft;
	Bit8u *fetch_ptr;
	Bit32u prev_linear_page;
	Bit32u prev_phy_page;
	Bit32u max_phy_addr;

#if BX_DEBUGGER
	Bit8u break_point;
#ifdef MAGIC_BREAKPOINT
	Bit8u magic_break;
#endif
	Bit8u stop_reason;
	Bit8u trace;
	Bit8u trace_reg;
	Bit8u mode_break;		/* BW */
	Boolean debug_vm;		/* BW contains current mode*/
	Bit8u show_eip;			/* BW record eip at special instr f.ex eip */
	Bit8u show_flag;		/* BW shows instr class executed */
	bx_guard_found_t guard_found;
#endif

	// for paging
#if BX_USE_TLB
	struct
	{
		bx_TLB_entry entry[BX_TLB_SIZE];
    } TLB;
#endif

  // An instruction cache.  Each entry should be exactly 32 bytes, and
  // this structure should be aligned on a 32-byte boundary to be friendly
  // with the host cache lines.
#if BX_SupportICache
  bxICache_c iCache; //  BX_CPP_AlignN(32);
#endif


  struct {
    bx_address  rm_addr; // The address offset after resolution.
    Bit32u  paddress1;  // physical address after translation of 1st len1 bytes of data
    Bit32u  paddress2;  // physical address after translation of 2nd len2 bytes of data
    Bit32u  len1;       // Number of bytes in page 1
    Bit32u  len2;       // Number of bytes in page 2
    Bit32u  pages;      // Number of pages access spans (1 or 2).  Also used
                        //   for the case when a native host pointer is
                        //   available for the R-M-W instructions.  The host
                        //   pointer is stuffed here.  Since this field has
                        //   to be checked anyways (and thus cached), if it
                        //   is greated than 2 (the maximum possible for
                        //   normal cases) it is a native pointer and is used
                        //   for a direct write access.
    } address_xlation;

  struct {
	Bit32u LastBranchToCS_EIP;
	Bit32u LastBranchFromCS_EIP;
	Bit32u LastExceptionToCS_EIP;
	Bit32u LastExceptionFromCS_EIP;
  } LBR;

	// for lazy flags processing
	BX_SMF Boolean get_OF(void);
	BX_SMF Boolean get_SF(void);
	BX_SMF Boolean get_ZF(void);
	BX_SMF Boolean get_AF(void);
	BX_SMF Boolean get_PF(void);
	BX_SMF Boolean get_CF(void);
	// constructors & destructors...
	BX_CPU_C();
	~BX_CPU_C(void);
	void init (BX_MEM_C *addrspace);
	void exit (void);

	int x86_cpu_loop(Bit32s max_instr_count);
	unsigned x86_handleAsyncEvent(void);
	void x86_boundaryFetch(bxInstruction_c *i);
	void x86_prefetch(void);

	inline Bit16u READ_SEGMENT_SELECTOR(int i)
	{
		return program_visible_sregs[(i)].selector.value;
	}

	inline void WRITE_SEGMENT_SELECTOR(int i,Bit16u selector)
	{
		program_visible_sregs[(i)].selector.value = selector;
		program_visible_sregs[(i)].cache.u.segment.base = selector<<4;
		invalidate_prefetch_q();
	}

	inline Bit16u READ_FLAGS_REGISTER(void) { return read_flags();}
	inline Bit32u READ_EFLAGS_REGISTER(void) { return read_eflags();}

	inline void WRITE_FLAGS_REGISTER(Bit16u flags)
	{
		write_flags(flags,true,true);
	}
	inline void WRITE_EFLAGS_REGISTER(Bit32u eflags)
	{
		write_eflags(eflags,true,true,true,true);
	}

	Bit32u mem_len;
	Bit32u *page_access_stamp_ptr;

	//虚拟执行--指令微函数

#define HOST_CPU_IS_I80386  0

#define BIT16 0
#define BIT32 1
#define BIT64 2

#define PREV_EIP				prev_eip
#define REG_EIP					program_visible_eip
#define REG_EFLAGS				program_visible_eflags
#define LAST_INSTRUCTION_BYTES  last_read_write.i_bytes

#define GENERAL_REG_DWORD(x)	program_visible_gen_reg[(x)].erx
#define GENERAL_REG_WORD(x)		program_visible_gen_reg[(x)].word.rx
#define GENERAL_REG_BYTE_L(x)	program_visible_gen_reg[(x)].word.byte.rl
#define GENERAL_REG_BYTE_H(x)	program_visible_gen_reg[(x)].word.byte.rh
#define SEGMENT_REG(x)			program_visible_sregs[(x)]
#define SEGMENT_MODE(x)			program_visible_sregs[(x)].cache.u.segment.d_b
#define SEGMENT_SELECTOR(x)		program_visible_sregs[(x)].selector.value
#define SEGMENT_BASE_ADDRESS(x)	program_visible_sregs[(x)].cache.u.segment.base

#define PROGRAM_REG_EIP					eip
#define PROGRAM_REG_EFLAGS				eflags

#define PROGRAM_GENERAL_REG_DWORD(x)	gen_reg[(x)].erx
#define PROGRAM_GENERAL_REG_WORD(x)		gen_reg[(x)].word.rx
#define PROGRAM_GENERAL_REG_BYTE_L(x)	gen_reg[(x)].word.byte.rl
#define PROGRAM_GENERAL_REG_BYTE_H(x)	gen_reg[(x)].word.byte.rh
#define PROGRAM_SEGMENT_REG(x)			sregs[(x)]
#define PROGRAM_SEGMENT_MODE(x)			sregs[(x)].cache.u.segment.d_b
#define PROGRAM_SEGMENT_SELECTOR(x)		sregs[(x)].selector.value
#define PROGRAM_SEGMENT_BASE_ADDRESS(x)	sregs[(x)].cache.u.segment.base

#ifndef I_EAX
#define I_EAX	0
#define I_ECX	1
#define I_EDX	2
#define I_EBX	3
#define I_ESP	4
#define I_EBP	5
#define I_ESI	6
#define I_EDI	7
#endif
#ifndef I_ES
#define I_ES	0
#define I_CS	1
#define I_SS	2
#define I_DS	3
#define I_FS	4
#define I_GS	5
#endif

	//-------------------------------------------------------------------
	//-------------------------------------------------------------------
	//虚拟执行--指令微函数
	BX_SMF int Translate_ADD_ALIb(bxInstruction_c *instr,int addrsize,int modrmlength,Bit8u *iptr,Bit8u *tptr);
	BX_SMF int Translate_ADD_AXIw(bxInstruction_c *instr,int addrsize,int modrmlength,Bit8u *iptr,Bit8u *tptr);
	BX_SMF int Translate_ADD_EAXId(bxInstruction_c *instr,int addrsize,int modrmlength,Bit8u *iptr,Bit8u *tptr);

	BX_SMF int Translate_MOV_RLIb(bxInstruction_c *instr,int addrsize,int modrmlength,Bit8u *iptr,Bit8u *tptr);
	BX_SMF int Translate_MOV_RHIb(bxInstruction_c *instr,int addrsize,int modrmlength,Bit8u *iptr,Bit8u *tptr);
	BX_SMF int Translate_MOV_RXIw(bxInstruction_c *instr,int addrsize,int modrmlength,Bit8u *iptr,Bit8u *tptr);
	BX_SMF int Translate_MOV_ERXId(bxInstruction_c *instr,int addrsize,int modrmlength,Bit8u *iptr,Bit8u *tptr);

	BX_SMF int Translate_MOV_ALOb(bxInstruction_c *instr,int addrsize,int modrmlength,Bit8u *iptr,Bit8u *tptr);
	BX_SMF int Translate_MOV_AXOw(bxInstruction_c *instr,int addrsize,int modrmlength,Bit8u *iptr,Bit8u *tptr);
	BX_SMF int Translate_MOV_ObAL(bxInstruction_c *instr,int addrsize,int modrmlength,Bit8u *iptr,Bit8u *tptr);
	BX_SMF int Translate_MOV_OwAX(bxInstruction_c *instr,int addrsize,int modrmlength,Bit8u *iptr,Bit8u *tptr);

	BX_SMF int Translate_MOV_EAXOd(bxInstruction_c *instr,int addrsize,int modrmlength,Bit8u *iptr,Bit8u *tptr);
	BX_SMF int Translate_MOV_OdEAX(bxInstruction_c *instr,int addrsize,int modrmlength,Bit8u *iptr,Bit8u *tptr);

	BX_SMF int Translate_ADD_EGbGb(bxInstruction_c *instr,int addrsize,int modrmlength,Bit8u *iptr,Bit8u *tptr);
	BX_SMF int Translate_ADD_EGwGw(bxInstruction_c *instr,int addrsize,int modrmlength,Bit8u *iptr,Bit8u *tptr);
	BX_SMF int Translate_ADD_EGdGd(bxInstruction_c *instr,int addrsize,int modrmlength,Bit8u *iptr,Bit8u *tptr);

	BX_SMF int Translate_ADD_EGbIb(bxInstruction_c *instr,int addrsize,int modrmlength,Bit8u *iptr,Bit8u *tptr);
	BX_SMF int Translate_ADD_EGwIb(bxInstruction_c *instr,int addrsize,int modrmlength,Bit8u *iptr,Bit8u *tptr);
	BX_SMF int Translate_ADD_EGwIw(bxInstruction_c *instr,int addrsize,int modrmlength,Bit8u *iptr,Bit8u *tptr);
	BX_SMF int Translate_ADD_EGdIb(bxInstruction_c *instr,int addrsize,int modrmlength,Bit8u *iptr,Bit8u *tptr);
	BX_SMF int Translate_ADD_EGdId(bxInstruction_c *instr,int addrsize,int modrmlength,Bit8u *iptr,Bit8u *tptr);

	BX_SMF int Translate_ADD_EEbGb(bxInstruction_c *instr,int addrsize,int modrmlength,Bit8u *iptr,Bit8u *tptr);
	BX_SMF int Translate_ADD_EEwGw(bxInstruction_c *instr,int addrsize,int modrmlength,Bit8u *iptr,Bit8u *tptr);
	BX_SMF int Translate_ADD_EEdGd(bxInstruction_c *instr,int addrsize,int modrmlength,Bit8u *iptr,Bit8u *tptr);

	BX_SMF int Translate_ADD_EEbIb(bxInstruction_c *instr,int addrsize,int modrmlength,Bit8u *iptr,Bit8u *tptr);
	BX_SMF int Translate_ADD_EEwIb(bxInstruction_c *instr,int addrsize,int modrmlength,Bit8u *iptr,Bit8u *tptr);
	BX_SMF int Translate_ADD_EEwIw(bxInstruction_c *instr,int addrsize,int modrmlength,Bit8u *iptr,Bit8u *tptr);
	BX_SMF int Translate_ADD_EEdIb(bxInstruction_c *instr,int addrsize,int modrmlength,Bit8u *iptr,Bit8u *tptr);
	BX_SMF int Translate_ADD_EEdId(bxInstruction_c *instr,int addrsize,int modrmlength,Bit8u *iptr,Bit8u *tptr);

	BX_SMF int Translate_SHIFT_EGb(bxInstruction_c *instr,int addrsize,int modrmlength,Bit8u *iptr,Bit8u *tptr);
	BX_SMF int Translate_SHIFT_EGw(bxInstruction_c *instr,int addrsize,int modrmlength,Bit8u *iptr,Bit8u *tptr);
	BX_SMF int Translate_SHIFT_EGd(bxInstruction_c *instr,int addrsize,int modrmlength,Bit8u *iptr,Bit8u *tptr);
	BX_SMF int Translate_SHIFT_EEb(bxInstruction_c *instr,int addrsize,int modrmlength,Bit8u *iptr,Bit8u *tptr);
	BX_SMF int Translate_SHIFT_EEw(bxInstruction_c *instr,int addrsize,int modrmlength,Bit8u *iptr,Bit8u *tptr);
	BX_SMF int Translate_SHIFT_EEd(bxInstruction_c *instr,int addrsize,int modrmlength,Bit8u *iptr,Bit8u *tptr);

	BX_SMF int Translate_SHIFT_EGbIb(bxInstruction_c *instr,int addrsize,int modrmlength,Bit8u *iptr,Bit8u *tptr);
	BX_SMF int Translate_SHIFT_EGwIb(bxInstruction_c *instr,int addrsize,int modrmlength,Bit8u *iptr,Bit8u *tptr);
	BX_SMF int Translate_SHIFT_EGdIb(bxInstruction_c *instr,int addrsize,int modrmlength,Bit8u *iptr,Bit8u *tptr);
	BX_SMF int Translate_SHIFT_EEbIb(bxInstruction_c *instr,int addrsize,int modrmlength,Bit8u *iptr,Bit8u *tptr);
	BX_SMF int Translate_SHIFT_EEwIb(bxInstruction_c *instr,int addrsize,int modrmlength,Bit8u *iptr,Bit8u *tptr);
	BX_SMF int Translate_SHIFT_EEdIb(bxInstruction_c *instr,int addrsize,int modrmlength,Bit8u *iptr,Bit8u *tptr);

	BX_SMF int Translate_1byte_b(bxInstruction_c *instr,int addrsize,int modrmlength,Bit8u *iptr,Bit8u *tptr);
	BX_SMF int Translate_1byte_w(bxInstruction_c *instr,int addrsize,int modrmlength,Bit8u *iptr,Bit8u *tptr);
	BX_SMF int Translate_1byte_d(bxInstruction_c *instr,int addrsize,int modrmlength,Bit8u *iptr,Bit8u *tptr);
	BX_SMF int Translate_1byte_EGbGb(bxInstruction_c *instr,int addrsize,int modrmlength,Bit8u *iptr,Bit8u *tptr);
	BX_SMF int Translate_1byte_EGwGw(bxInstruction_c *instr,int addrsize,int modrmlength,Bit8u *iptr,Bit8u *tptr);
	BX_SMF int Translate_1byte_EGdGd(bxInstruction_c *instr,int addrsize,int modrmlength,Bit8u *iptr,Bit8u *tptr);

	BX_SMF int Translate_1byte_EEbGb(bxInstruction_c *instr,int addrsize,int modrmlength,Bit8u *iptr,Bit8u *tptr);
	BX_SMF int Translate_1byte_EEwGw(bxInstruction_c *instr,int addrsize,int modrmlength,Bit8u *iptr,Bit8u *tptr);
	BX_SMF int Translate_1byte_EEdGd(bxInstruction_c *instr,int addrsize,int modrmlength,Bit8u *iptr,Bit8u *tptr);

	BX_SMF int Translate_2byte_b(bxInstruction_c *instr,int addrsize,int modrmlength,Bit8u *iptr,Bit8u *tptr);
	BX_SMF int Translate_2byte_w(bxInstruction_c *instr,int addrsize,int modrmlength,Bit8u *iptr,Bit8u *tptr);
	BX_SMF int Translate_2byte_d(bxInstruction_c *instr,int addrsize,int modrmlength,Bit8u *iptr,Bit8u *tptr);
	BX_SMF int Translate_2byte_EGbGb(bxInstruction_c *instr,int addrsize,int modrmlength,Bit8u *iptr,Bit8u *tptr);
	BX_SMF int Translate_2byte_EGwGw(bxInstruction_c *instr,int addrsize,int modrmlength,Bit8u *iptr,Bit8u *tptr);
	BX_SMF int Translate_2byte_EGdGd(bxInstruction_c *instr,int addrsize,int modrmlength,Bit8u *iptr,Bit8u *tptr);

	BX_SMF int Translate_2byte_EEbGb(bxInstruction_c *instr,int addrsize,int modrmlength,Bit8u *iptr,Bit8u *tptr);
	BX_SMF int Translate_2byte_EEwGw(bxInstruction_c *instr,int addrsize,int modrmlength,Bit8u *iptr,Bit8u *tptr);
	BX_SMF int Translate_2byte_EEdGd(bxInstruction_c *instr,int addrsize,int modrmlength,Bit8u *iptr,Bit8u *tptr);

	BX_SMF int Translate_INCDEC_EGb(bxInstruction_c *instr,int addrsize,int modrmlength,Bit8u *iptr,Bit8u *tptr);
	BX_SMF int Translate_INCDEC_EGw(bxInstruction_c *instr,int addrsize,int modrmlength,Bit8u *iptr,Bit8u *tptr);
	BX_SMF int Translate_INCDEC_EGd(bxInstruction_c *instr,int addrsize,int modrmlength,Bit8u *iptr,Bit8u *tptr);
	BX_SMF int Translate_INCDEC_EEb(bxInstruction_c *instr,int addrsize,int modrmlength,Bit8u *iptr,Bit8u *tptr);
	BX_SMF int Translate_INCDEC_EEw(bxInstruction_c *instr,int addrsize,int modrmlength,Bit8u *iptr,Bit8u *tptr);
	BX_SMF int Translate_INCDEC_EEd(bxInstruction_c *instr,int addrsize,int modrmlength,Bit8u *iptr,Bit8u *tptr);

	BX_SMF int Translate_NOT_EGb(bxInstruction_c *instr,int addrsize,int modrmlength,Bit8u *iptr,Bit8u *tptr);
	BX_SMF int Translate_NOT_EGw(bxInstruction_c *instr,int addrsize,int modrmlength,Bit8u *iptr,Bit8u *tptr);
	BX_SMF int Translate_NOT_EGd(bxInstruction_c *instr,int addrsize,int modrmlength,Bit8u *iptr,Bit8u *tptr);
	BX_SMF int Translate_NOT_EEb(bxInstruction_c *instr,int addrsize,int modrmlength,Bit8u *iptr,Bit8u *tptr);
	BX_SMF int Translate_NOT_EEw(bxInstruction_c *instr,int addrsize,int modrmlength,Bit8u *iptr,Bit8u *tptr);
	BX_SMF int Translate_NOT_EEd(bxInstruction_c *instr,int addrsize,int modrmlength,Bit8u *iptr,Bit8u *tptr);

	BX_SMF int Translate_NEG_EGb(bxInstruction_c *instr,int addrsize,int modrmlength,Bit8u *iptr,Bit8u *tptr);
	BX_SMF int Translate_NEG_EGw(bxInstruction_c *instr,int addrsize,int modrmlength,Bit8u *iptr,Bit8u *tptr);
	BX_SMF int Translate_NEG_EGd(bxInstruction_c *instr,int addrsize,int modrmlength,Bit8u *iptr,Bit8u *tptr);

	BX_SMF int Translate_NEG_EEb(bxInstruction_c *instr,int addrsize,int modrmlength,Bit8u *iptr,Bit8u *tptr);
	BX_SMF int Translate_NEG_EEw(bxInstruction_c *instr,int addrsize,int modrmlength,Bit8u *iptr,Bit8u *tptr);
	BX_SMF int Translate_NEG_EEd(bxInstruction_c *instr,int addrsize,int modrmlength,Bit8u *iptr,Bit8u *tptr);

	BX_SMF int Translate_MULT_EGb(bxInstruction_c *instr,int addrsize,int modrmlength,Bit8u *iptr,Bit8u *tptr);
	BX_SMF int Translate_MULT_EGw(bxInstruction_c *instr,int addrsize,int modrmlength,Bit8u *iptr,Bit8u *tptr);
	BX_SMF int Translate_MULT_EGd(bxInstruction_c *instr,int addrsize,int modrmlength,Bit8u *iptr,Bit8u *tptr);

	BX_SMF int Translate_MULT_EEb(bxInstruction_c *instr,int addrsize,int modrmlength,Bit8u *iptr,Bit8u *tptr);
	BX_SMF int Translate_MULT_EEw(bxInstruction_c *instr,int addrsize,int modrmlength,Bit8u *iptr,Bit8u *tptr);
	BX_SMF int Translate_MULT_EEd(bxInstruction_c *instr,int addrsize,int modrmlength,Bit8u *iptr,Bit8u *tptr);


	BX_SMF int Translate_AAM_(bxInstruction_c *instr,int addrsize,int modrmlength,Bit8u *iptr,Bit8u *tptr);
	BX_SMF int Translate_AAD_(bxInstruction_c *instr,int addrsize,int modrmlength,Bit8u *iptr,Bit8u *tptr);
	BX_SMF int Translate_XLAT_(bxInstruction_c *instr,int addrsize,int modrmlength,Bit8u *iptr,Bit8u *tptr);

	BX_SMF int Translate_virtual_run(bxInstruction_c *instr,int addrsize,int modrmlength,Bit8u *iptr,Bit8u *tptr);
	BX_SMF int Translate_virtual_run_m(bxInstruction_c *instr,int addrsize,int modrmlength,Bit8u *iptr,Bit8u *tptr);

	BX_SMF int Translate_JCC_J_(bxInstruction_c *instr,int addrsize,int modrmlength,Bit8u *iptr,Bit8u *tptr);
	BX_SMF int Translate_JMP_J_(bxInstruction_c *instr,int addrsize,int modrmlength,Bit8u *iptr,Bit8u *tptr);
	BX_SMF int Translate_LOOP_J_(bxInstruction_c *instr,int addrsize,int modrmlength,Bit8u *iptr,Bit8u *tptr);
	BX_SMF int Translate_JCXZ_J_(bxInstruction_c *instr,int addrsize,int modrmlength,Bit8u *iptr,Bit8u *tptr);

	BX_SMF int Translate_JMP_(bxInstruction_c *instr,int addrsize,int modrmlength,Bit8u *iptr,Bit8u *tptr);
	BX_SMF int Translate_JMP_m(bxInstruction_c *instr,int addrsize,int modrmlength,Bit8u *iptr,Bit8u *tptr);


	//虚拟执行--指令微函数
#if 0
	ADD SUB AND XOR OR ADC SBB CMP TEST
#endif

#define BX_SMF_FORCE static

	BX_SMF_FORCE void ADD_EGbGb( BX_CPU_C *,bxInstruction_c *);
	BX_SMF_FORCE void ADD_EGwGw( BX_CPU_C *,bxInstruction_c *);
	BX_SMF_FORCE void ADD_EGdGd( BX_CPU_C *,bxInstruction_c *);
	BX_SMF_FORCE void ADD_GbEGb( BX_CPU_C *,bxInstruction_c *);
	BX_SMF_FORCE void ADD_GwEGw( BX_CPU_C *,bxInstruction_c *);
	BX_SMF_FORCE void ADD_GdEGd( BX_CPU_C *,bxInstruction_c *);
	BX_SMF_FORCE void ADD_EGbIb( BX_CPU_C *,bxInstruction_c *);
	BX_SMF_FORCE void ADD_EGwIw( BX_CPU_C *,bxInstruction_c *);
	BX_SMF_FORCE void ADD_EGdId( BX_CPU_C *,bxInstruction_c *);

	BX_SMF_FORCE void ADD_EEbGb( BX_CPU_C *,bxInstruction_c *);
	BX_SMF_FORCE void ADD_EEwGw( BX_CPU_C *,bxInstruction_c *);
	BX_SMF_FORCE void ADD_EEdGd( BX_CPU_C *,bxInstruction_c *);
	BX_SMF_FORCE void ADD_GbEEb( BX_CPU_C *,bxInstruction_c *);
	BX_SMF_FORCE void ADD_GwEEw( BX_CPU_C *,bxInstruction_c *);
	BX_SMF_FORCE void ADD_GdEEd( BX_CPU_C *,bxInstruction_c *);
	BX_SMF_FORCE void ADD_EEbIb( BX_CPU_C *,bxInstruction_c *);
	BX_SMF_FORCE void ADD_EEwIw( BX_CPU_C *,bxInstruction_c *);
	BX_SMF_FORCE void ADD_EEdId( BX_CPU_C *,bxInstruction_c *);

	BX_SMF_FORCE void ADD_ALIb ( BX_CPU_C *,bxInstruction_c *);
	BX_SMF_FORCE void ADD_AXIw ( BX_CPU_C *,bxInstruction_c *);
	BX_SMF_FORCE void ADD_EAXId( BX_CPU_C *,bxInstruction_c *);
	//---------------------

	BX_SMF_FORCE void SUB_EGbGb( BX_CPU_C *,bxInstruction_c *);
	BX_SMF_FORCE void SUB_EGwGw( BX_CPU_C *,bxInstruction_c *);
	BX_SMF_FORCE void SUB_EGdGd( BX_CPU_C *,bxInstruction_c *);
	BX_SMF_FORCE void SUB_GbEGb( BX_CPU_C *,bxInstruction_c *);
	BX_SMF_FORCE void SUB_GwEGw( BX_CPU_C *,bxInstruction_c *);
	BX_SMF_FORCE void SUB_GdEGd( BX_CPU_C *,bxInstruction_c *);
	BX_SMF_FORCE void SUB_EGbIb( BX_CPU_C *,bxInstruction_c *);
	BX_SMF_FORCE void SUB_EGwIw( BX_CPU_C *,bxInstruction_c *);
	BX_SMF_FORCE void SUB_EGdId( BX_CPU_C *,bxInstruction_c *);

	BX_SMF_FORCE void SUB_EEbGb( BX_CPU_C *,bxInstruction_c *);
	BX_SMF_FORCE void SUB_EEwGw( BX_CPU_C *,bxInstruction_c *);
	BX_SMF_FORCE void SUB_EEdGd( BX_CPU_C *,bxInstruction_c *);
	BX_SMF_FORCE void SUB_GbEEb( BX_CPU_C *,bxInstruction_c *);
	BX_SMF_FORCE void SUB_GwEEw( BX_CPU_C *,bxInstruction_c *);
	BX_SMF_FORCE void SUB_GdEEd( BX_CPU_C *,bxInstruction_c *);
	BX_SMF_FORCE void SUB_EEbIb( BX_CPU_C *,bxInstruction_c *);
	BX_SMF_FORCE void SUB_EEwIw( BX_CPU_C *,bxInstruction_c *);
	BX_SMF_FORCE void SUB_EEdId( BX_CPU_C *,bxInstruction_c *);

	BX_SMF_FORCE void SUB_ALIb ( BX_CPU_C *,bxInstruction_c *);
	BX_SMF_FORCE void SUB_AXIw ( BX_CPU_C *,bxInstruction_c *);
	BX_SMF_FORCE void SUB_EAXId( BX_CPU_C *,bxInstruction_c *);
	//---------------------

	BX_SMF_FORCE void AND_EGbGb( BX_CPU_C *,bxInstruction_c *);
	BX_SMF_FORCE void AND_EGwGw( BX_CPU_C *,bxInstruction_c *);
	BX_SMF_FORCE void AND_EGdGd( BX_CPU_C *,bxInstruction_c *);
	BX_SMF_FORCE void AND_GbEGb( BX_CPU_C *,bxInstruction_c *);
	BX_SMF_FORCE void AND_GwEGw( BX_CPU_C *,bxInstruction_c *);
	BX_SMF_FORCE void AND_GdEGd( BX_CPU_C *,bxInstruction_c *);
	BX_SMF_FORCE void AND_EGbIb( BX_CPU_C *,bxInstruction_c *);
	BX_SMF_FORCE void AND_EGwIw( BX_CPU_C *,bxInstruction_c *);
	BX_SMF_FORCE void AND_EGdId( BX_CPU_C *,bxInstruction_c *);

	BX_SMF_FORCE void AND_EEbGb( BX_CPU_C *,bxInstruction_c *);
	BX_SMF_FORCE void AND_EEwGw( BX_CPU_C *,bxInstruction_c *);
	BX_SMF_FORCE void AND_EEdGd( BX_CPU_C *,bxInstruction_c *);
	BX_SMF_FORCE void AND_GbEEb( BX_CPU_C *,bxInstruction_c *);
	BX_SMF_FORCE void AND_GwEEw( BX_CPU_C *,bxInstruction_c *);
	BX_SMF_FORCE void AND_GdEEd( BX_CPU_C *,bxInstruction_c *);
	BX_SMF_FORCE void AND_EEbIb( BX_CPU_C *,bxInstruction_c *);
	BX_SMF_FORCE void AND_EEwIw( BX_CPU_C *,bxInstruction_c *);
	BX_SMF_FORCE void AND_EEdId( BX_CPU_C *,bxInstruction_c *);

	BX_SMF_FORCE void AND_ALIb ( BX_CPU_C *,bxInstruction_c *);
	BX_SMF_FORCE void AND_AXIw ( BX_CPU_C *,bxInstruction_c *);
	BX_SMF_FORCE void AND_EAXId( BX_CPU_C *,bxInstruction_c *);
	//---------------------

	BX_SMF_FORCE void XOR_EGbGb( BX_CPU_C *,bxInstruction_c *);
	BX_SMF_FORCE void XOR_EGwGw( BX_CPU_C *,bxInstruction_c *);
	BX_SMF_FORCE void XOR_EGdGd( BX_CPU_C *,bxInstruction_c *);
	BX_SMF_FORCE void XOR_GbEGb( BX_CPU_C *,bxInstruction_c *);
	BX_SMF_FORCE void XOR_GwEGw( BX_CPU_C *,bxInstruction_c *);
	BX_SMF_FORCE void XOR_GdEGd( BX_CPU_C *,bxInstruction_c *);
	BX_SMF_FORCE void XOR_EGbIb( BX_CPU_C *,bxInstruction_c *);
	BX_SMF_FORCE void XOR_EGwIw( BX_CPU_C *,bxInstruction_c *);
	BX_SMF_FORCE void XOR_EGdId( BX_CPU_C *,bxInstruction_c *);

	BX_SMF_FORCE void XOR_EEbGb( BX_CPU_C *,bxInstruction_c *);
	BX_SMF_FORCE void XOR_EEwGw( BX_CPU_C *,bxInstruction_c *);
	BX_SMF_FORCE void XOR_EEdGd( BX_CPU_C *,bxInstruction_c *);
	BX_SMF_FORCE void XOR_GbEEb( BX_CPU_C *,bxInstruction_c *);
	BX_SMF_FORCE void XOR_GwEEw( BX_CPU_C *,bxInstruction_c *);
	BX_SMF_FORCE void XOR_GdEEd( BX_CPU_C *,bxInstruction_c *);
	BX_SMF_FORCE void XOR_EEbIb( BX_CPU_C *,bxInstruction_c *);
	BX_SMF_FORCE void XOR_EEwIw( BX_CPU_C *,bxInstruction_c *);
	BX_SMF_FORCE void XOR_EEdId( BX_CPU_C *,bxInstruction_c *);

	BX_SMF_FORCE void XOR_ALIb ( BX_CPU_C *,bxInstruction_c *);
	BX_SMF_FORCE void XOR_AXIw ( BX_CPU_C *,bxInstruction_c *);
	BX_SMF_FORCE void XOR_EAXId( BX_CPU_C *,bxInstruction_c *);
	//---------------------

	BX_SMF_FORCE void  OR_EGbGb( BX_CPU_C *,bxInstruction_c *);
	BX_SMF_FORCE void  OR_EGwGw( BX_CPU_C *,bxInstruction_c *);
	BX_SMF_FORCE void  OR_EGdGd( BX_CPU_C *,bxInstruction_c *);
	BX_SMF_FORCE void  OR_GbEGb( BX_CPU_C *,bxInstruction_c *);
	BX_SMF_FORCE void  OR_GwEGw( BX_CPU_C *,bxInstruction_c *);
	BX_SMF_FORCE void  OR_GdEGd( BX_CPU_C *,bxInstruction_c *);
	BX_SMF_FORCE void  OR_EGbIb( BX_CPU_C *,bxInstruction_c *);
	BX_SMF_FORCE void  OR_EGwIw( BX_CPU_C *,bxInstruction_c *);
	BX_SMF_FORCE void  OR_EGdId( BX_CPU_C *,bxInstruction_c *);

	BX_SMF_FORCE void  OR_EEbGb( BX_CPU_C *,bxInstruction_c *);
	BX_SMF_FORCE void  OR_EEwGw( BX_CPU_C *,bxInstruction_c *);
	BX_SMF_FORCE void  OR_EEdGd( BX_CPU_C *,bxInstruction_c *);
	BX_SMF_FORCE void  OR_GbEEb( BX_CPU_C *,bxInstruction_c *);
	BX_SMF_FORCE void  OR_GwEEw( BX_CPU_C *,bxInstruction_c *);
	BX_SMF_FORCE void  OR_GdEEd( BX_CPU_C *,bxInstruction_c *);
	BX_SMF_FORCE void  OR_EEbIb( BX_CPU_C *,bxInstruction_c *);
	BX_SMF_FORCE void  OR_EEwIw( BX_CPU_C *,bxInstruction_c *);
	BX_SMF_FORCE void  OR_EEdId( BX_CPU_C *,bxInstruction_c *);

	BX_SMF_FORCE void  OR_ALIb ( BX_CPU_C *,bxInstruction_c *);
	BX_SMF_FORCE void  OR_AXIw ( BX_CPU_C *,bxInstruction_c *);
	BX_SMF_FORCE void  OR_EAXId( BX_CPU_C *,bxInstruction_c *);
	//---------------------

	BX_SMF_FORCE void ADC_EGbGb( BX_CPU_C *,bxInstruction_c *);
	BX_SMF_FORCE void ADC_EGwGw( BX_CPU_C *,bxInstruction_c *);
	BX_SMF_FORCE void ADC_EGdGd( BX_CPU_C *,bxInstruction_c *);
	BX_SMF_FORCE void ADC_GbEGb( BX_CPU_C *,bxInstruction_c *);
	BX_SMF_FORCE void ADC_GwEGw( BX_CPU_C *,bxInstruction_c *);
	BX_SMF_FORCE void ADC_GdEGd( BX_CPU_C *,bxInstruction_c *);
	BX_SMF_FORCE void ADC_EGbIb( BX_CPU_C *,bxInstruction_c *);
	BX_SMF_FORCE void ADC_EGwIw( BX_CPU_C *,bxInstruction_c *);
	BX_SMF_FORCE void ADC_EGdId( BX_CPU_C *,bxInstruction_c *);
	BX_SMF_FORCE void ADC_ALIb ( BX_CPU_C *,bxInstruction_c *);
	BX_SMF_FORCE void ADC_AXIw ( BX_CPU_C *,bxInstruction_c *);
	BX_SMF_FORCE void ADC_EAXId( BX_CPU_C *,bxInstruction_c *);

	BX_SMF_FORCE void ADC_EEbGb( BX_CPU_C *,bxInstruction_c *);
	BX_SMF_FORCE void ADC_EEwGw( BX_CPU_C *,bxInstruction_c *);
	BX_SMF_FORCE void ADC_EEdGd( BX_CPU_C *,bxInstruction_c *);
	BX_SMF_FORCE void ADC_GbEEb( BX_CPU_C *,bxInstruction_c *);
	BX_SMF_FORCE void ADC_GwEEw( BX_CPU_C *,bxInstruction_c *);
	BX_SMF_FORCE void ADC_GdEEd( BX_CPU_C *,bxInstruction_c *);
	BX_SMF_FORCE void ADC_EEbIb( BX_CPU_C *,bxInstruction_c *);
	BX_SMF_FORCE void ADC_EEwIw( BX_CPU_C *,bxInstruction_c *);
	BX_SMF_FORCE void ADC_EEdId( BX_CPU_C *,bxInstruction_c *);
	//---------------------

	BX_SMF_FORCE void SBB_EGbGb( BX_CPU_C *,bxInstruction_c *);
	BX_SMF_FORCE void SBB_EGwGw( BX_CPU_C *,bxInstruction_c *);
	BX_SMF_FORCE void SBB_EGdGd( BX_CPU_C *,bxInstruction_c *);
	BX_SMF_FORCE void SBB_GbEGb( BX_CPU_C *,bxInstruction_c *);
	BX_SMF_FORCE void SBB_GwEGw( BX_CPU_C *,bxInstruction_c *);
	BX_SMF_FORCE void SBB_GdEGd( BX_CPU_C *,bxInstruction_c *);
	BX_SMF_FORCE void SBB_EGbIb( BX_CPU_C *,bxInstruction_c *);
	BX_SMF_FORCE void SBB_EGwIw( BX_CPU_C *,bxInstruction_c *);
	BX_SMF_FORCE void SBB_EGdId( BX_CPU_C *,bxInstruction_c *);

	BX_SMF_FORCE void SBB_EEbGb( BX_CPU_C *,bxInstruction_c *);
	BX_SMF_FORCE void SBB_EEwGw( BX_CPU_C *,bxInstruction_c *);
	BX_SMF_FORCE void SBB_EEdGd( BX_CPU_C *,bxInstruction_c *);
	BX_SMF_FORCE void SBB_GbEEb( BX_CPU_C *,bxInstruction_c *);
	BX_SMF_FORCE void SBB_GwEEw( BX_CPU_C *,bxInstruction_c *);
	BX_SMF_FORCE void SBB_GdEEd( BX_CPU_C *,bxInstruction_c *);
	BX_SMF_FORCE void SBB_EEbIb( BX_CPU_C *,bxInstruction_c *);
	BX_SMF_FORCE void SBB_EEwIw( BX_CPU_C *,bxInstruction_c *);
	BX_SMF_FORCE void SBB_EEdId( BX_CPU_C *,bxInstruction_c *);

	BX_SMF_FORCE void SBB_ALIb ( BX_CPU_C *,bxInstruction_c *);
	BX_SMF_FORCE void SBB_AXIw ( BX_CPU_C *,bxInstruction_c *);
	BX_SMF_FORCE void SBB_EAXId( BX_CPU_C *,bxInstruction_c *);
	//---------------------

	BX_SMF_FORCE void CMP_EGbGb( BX_CPU_C *,bxInstruction_c *);
	BX_SMF_FORCE void CMP_EGwGw( BX_CPU_C *,bxInstruction_c *);
	BX_SMF_FORCE void CMP_EGdGd( BX_CPU_C *,bxInstruction_c *);
	BX_SMF_FORCE void CMP_GbEGb( BX_CPU_C *,bxInstruction_c *);
	BX_SMF_FORCE void CMP_GwEGw( BX_CPU_C *,bxInstruction_c *);
	BX_SMF_FORCE void CMP_GdEGd( BX_CPU_C *,bxInstruction_c *);
	BX_SMF_FORCE void CMP_EGbIb( BX_CPU_C *,bxInstruction_c *);
	BX_SMF_FORCE void CMP_EGwIw( BX_CPU_C *,bxInstruction_c *);
	BX_SMF_FORCE void CMP_EGdId( BX_CPU_C *,bxInstruction_c *);

	BX_SMF_FORCE void CMP_EEbGb( BX_CPU_C *,bxInstruction_c *);
	BX_SMF_FORCE void CMP_EEwGw( BX_CPU_C *,bxInstruction_c *);
	BX_SMF_FORCE void CMP_EEdGd( BX_CPU_C *,bxInstruction_c *);
	BX_SMF_FORCE void CMP_GbEEb( BX_CPU_C *,bxInstruction_c *);
	BX_SMF_FORCE void CMP_GwEEw( BX_CPU_C *,bxInstruction_c *);
	BX_SMF_FORCE void CMP_GdEEd( BX_CPU_C *,bxInstruction_c *);
	BX_SMF_FORCE void CMP_EEbIb( BX_CPU_C *,bxInstruction_c *);
	BX_SMF_FORCE void CMP_EEwIw( BX_CPU_C *,bxInstruction_c *);
	BX_SMF_FORCE void CMP_EEdId( BX_CPU_C *,bxInstruction_c *);

	BX_SMF_FORCE void CMP_ALIb ( BX_CPU_C *,bxInstruction_c *);
	BX_SMF_FORCE void CMP_AXIw ( BX_CPU_C *,bxInstruction_c *);
	BX_SMF_FORCE void CMP_EAXId( BX_CPU_C *,bxInstruction_c *);
	//---------------------

	BX_SMF_FORCE void TEST_EGbGb( BX_CPU_C *,bxInstruction_c *);
	BX_SMF_FORCE void TEST_EGwGw( BX_CPU_C *,bxInstruction_c *);
	BX_SMF_FORCE void TEST_EGdGd( BX_CPU_C *,bxInstruction_c *);
	BX_SMF_FORCE void TEST_GbEGb( BX_CPU_C *,bxInstruction_c *);
	BX_SMF_FORCE void TEST_GwEGw( BX_CPU_C *,bxInstruction_c *);
	BX_SMF_FORCE void TEST_GdEGd( BX_CPU_C *,bxInstruction_c *);
	BX_SMF_FORCE void TEST_EGbIb( BX_CPU_C *,bxInstruction_c *);
	BX_SMF_FORCE void TEST_EGwIw( BX_CPU_C *,bxInstruction_c *);
	BX_SMF_FORCE void TEST_EGdId( BX_CPU_C *,bxInstruction_c *);

	BX_SMF_FORCE void TEST_EEbGb( BX_CPU_C *,bxInstruction_c *);
	BX_SMF_FORCE void TEST_EEwGw( BX_CPU_C *,bxInstruction_c *);
	BX_SMF_FORCE void TEST_EEdGd( BX_CPU_C *,bxInstruction_c *);
	BX_SMF_FORCE void TEST_GbEEb( BX_CPU_C *,bxInstruction_c *);
	BX_SMF_FORCE void TEST_GwEEw( BX_CPU_C *,bxInstruction_c *);
	BX_SMF_FORCE void TEST_GdEEd( BX_CPU_C *,bxInstruction_c *);
	BX_SMF_FORCE void TEST_EEbIb( BX_CPU_C *,bxInstruction_c *);
	BX_SMF_FORCE void TEST_EEwIw( BX_CPU_C *,bxInstruction_c *);
	BX_SMF_FORCE void TEST_EEdId( BX_CPU_C *,bxInstruction_c *);

	BX_SMF_FORCE void TEST_ALIb ( BX_CPU_C *,bxInstruction_c *);
	BX_SMF_FORCE void TEST_AXIw ( BX_CPU_C *,bxInstruction_c *);
	BX_SMF_FORCE void TEST_EAXId( BX_CPU_C *,bxInstruction_c *);
	//---------------------

	//-------------------------------------------

	BX_SMF_FORCE void INC_EGb( BX_CPU_C *,bxInstruction_c *);
	BX_SMF_FORCE void INC_EGw( BX_CPU_C *,bxInstruction_c *);
	BX_SMF_FORCE void INC_EGd( BX_CPU_C *,bxInstruction_c *);
	BX_SMF_FORCE void INC_RX ( BX_CPU_C *,bxInstruction_c *);
	BX_SMF_FORCE void INC_ERX( BX_CPU_C *,bxInstruction_c *);
	BX_SMF_FORCE void DEC_EGb( BX_CPU_C *,bxInstruction_c *);
	BX_SMF_FORCE void DEC_EGw( BX_CPU_C *,bxInstruction_c *);
	BX_SMF_FORCE void DEC_EGd( BX_CPU_C *,bxInstruction_c *);
	BX_SMF_FORCE void DEC_RX ( BX_CPU_C *,bxInstruction_c *);
	BX_SMF_FORCE void DEC_ERX( BX_CPU_C *,bxInstruction_c *);

	BX_SMF_FORCE void NEG_EGb( BX_CPU_C *,bxInstruction_c *);
	BX_SMF_FORCE void NEG_EGw( BX_CPU_C *,bxInstruction_c *);
	BX_SMF_FORCE void NEG_EGd( BX_CPU_C *,bxInstruction_c *);
	BX_SMF_FORCE void NOT_EGb( BX_CPU_C *,bxInstruction_c *);
	BX_SMF_FORCE void NOT_EGw( BX_CPU_C *,bxInstruction_c *);
	BX_SMF_FORCE void NOT_EGd( BX_CPU_C *,bxInstruction_c *);

	BX_SMF_FORCE void INC_EEb( BX_CPU_C *,bxInstruction_c *);
	BX_SMF_FORCE void INC_EEw( BX_CPU_C *,bxInstruction_c *);
	BX_SMF_FORCE void INC_EEd( BX_CPU_C *,bxInstruction_c *);
	BX_SMF_FORCE void DEC_EEb( BX_CPU_C *,bxInstruction_c *);
	BX_SMF_FORCE void DEC_EEw( BX_CPU_C *,bxInstruction_c *);
	BX_SMF_FORCE void DEC_EEd( BX_CPU_C *,bxInstruction_c *);

	BX_SMF_FORCE void NEG_EEb( BX_CPU_C *,bxInstruction_c *);
	BX_SMF_FORCE void NEG_EEw( BX_CPU_C *,bxInstruction_c *);
	BX_SMF_FORCE void NEG_EEd( BX_CPU_C *,bxInstruction_c *);
	BX_SMF_FORCE void NOT_EEb( BX_CPU_C *,bxInstruction_c *);
	BX_SMF_FORCE void NOT_EEw( BX_CPU_C *,bxInstruction_c *);
	BX_SMF_FORCE void NOT_EEd( BX_CPU_C *,bxInstruction_c *);

	BX_SMF_FORCE void XADD_EGbGb( BX_CPU_C *,bxInstruction_c *);
	BX_SMF_FORCE void XADD_EGwGw( BX_CPU_C *,bxInstruction_c *);
	BX_SMF_FORCE void XADD_EGdGd( BX_CPU_C *,bxInstruction_c *);

	BX_SMF_FORCE void XADD_EEbGb( BX_CPU_C *,bxInstruction_c *);
	BX_SMF_FORCE void XADD_EEwGw( BX_CPU_C *,bxInstruction_c *);
	BX_SMF_FORCE void XADD_EEdGd( BX_CPU_C *,bxInstruction_c *);

	BX_SMF_FORCE void CMPXCHG_EGbGb( BX_CPU_C *,bxInstruction_c *);
	BX_SMF_FORCE void CMPXCHG_EGwGw( BX_CPU_C *,bxInstruction_c *);
	BX_SMF_FORCE void CMPXCHG_EGdGd( BX_CPU_C *,bxInstruction_c *);

	BX_SMF_FORCE void CMPXCHG_EEbGb( BX_CPU_C *,bxInstruction_c *);
	BX_SMF_FORCE void CMPXCHG_EEwGw( BX_CPU_C *,bxInstruction_c *);
	BX_SMF_FORCE void CMPXCHG_EEdGd( BX_CPU_C *,bxInstruction_c *);


	BX_SMF_FORCE void MOV_EGbGb( BX_CPU_C *,bxInstruction_c *);
	BX_SMF_FORCE void MOV_EGwGw( BX_CPU_C *,bxInstruction_c *);
	BX_SMF_FORCE void MOV_EGdGd( BX_CPU_C *,bxInstruction_c *);
	BX_SMF_FORCE void MOV_GbEGb( BX_CPU_C *,bxInstruction_c *);
	BX_SMF_FORCE void MOV_GwEGw( BX_CPU_C *,bxInstruction_c *);
	BX_SMF_FORCE void MOV_GdEGd( BX_CPU_C *,bxInstruction_c *);
	BX_SMF_FORCE void MOV_EGbIb( BX_CPU_C *,bxInstruction_c *);
	BX_SMF_FORCE void MOV_EGwIw( BX_CPU_C *,bxInstruction_c *);
	BX_SMF_FORCE void MOV_EGdId( BX_CPU_C *,bxInstruction_c *);

	BX_SMF_FORCE void MOV_EEbGb( BX_CPU_C *,bxInstruction_c *);
	BX_SMF_FORCE void MOV_EEwGw( BX_CPU_C *,bxInstruction_c *);
	BX_SMF_FORCE void MOV_EEdGd( BX_CPU_C *,bxInstruction_c *);
	BX_SMF_FORCE void MOV_GbEEb( BX_CPU_C *,bxInstruction_c *);
	BX_SMF_FORCE void MOV_GwEEw( BX_CPU_C *,bxInstruction_c *);
	BX_SMF_FORCE void MOV_GdEEd( BX_CPU_C *,bxInstruction_c *);
	BX_SMF_FORCE void MOV_EEbIb( BX_CPU_C *,bxInstruction_c *);
	BX_SMF_FORCE void MOV_EEwIw( BX_CPU_C *,bxInstruction_c *);
	BX_SMF_FORCE void MOV_EEdId( BX_CPU_C *,bxInstruction_c *);

	BX_SMF_FORCE void MOVZX_GwEGb( BX_CPU_C *,bxInstruction_c *);
	BX_SMF_FORCE void MOVSX_GwEGb( BX_CPU_C *,bxInstruction_c *);
	BX_SMF_FORCE void MOVZX_GwEGw( BX_CPU_C *,bxInstruction_c *);
	BX_SMF_FORCE void MOVSX_GwEGw( BX_CPU_C *,bxInstruction_c *);
	BX_SMF_FORCE void MOVZX_GdEGb( BX_CPU_C *,bxInstruction_c *);
	BX_SMF_FORCE void MOVSX_GdEGb( BX_CPU_C *,bxInstruction_c *);
	BX_SMF_FORCE void MOVZX_GdEGw( BX_CPU_C *,bxInstruction_c *);
	BX_SMF_FORCE void MOVSX_GdEGw( BX_CPU_C *,bxInstruction_c *);

	BX_SMF_FORCE void MOVZX_GwEEb( BX_CPU_C *,bxInstruction_c *);
	BX_SMF_FORCE void MOVSX_GwEEb( BX_CPU_C *,bxInstruction_c *);
	BX_SMF_FORCE void MOVZX_GwEEw( BX_CPU_C *,bxInstruction_c *);
	BX_SMF_FORCE void MOVSX_GwEEw( BX_CPU_C *,bxInstruction_c *);
	BX_SMF_FORCE void MOVZX_GdEEb( BX_CPU_C *,bxInstruction_c *);
	BX_SMF_FORCE void MOVSX_GdEEb( BX_CPU_C *,bxInstruction_c *);
	BX_SMF_FORCE void MOVZX_GdEEw( BX_CPU_C *,bxInstruction_c *);
	BX_SMF_FORCE void MOVSX_GdEEw( BX_CPU_C *,bxInstruction_c *);

	BX_SMF_FORCE void MOV_ALOb( BX_CPU_C *,bxInstruction_c *);
	BX_SMF_FORCE void MOV_ObAL( BX_CPU_C *,bxInstruction_c *);
	BX_SMF_FORCE void MOV_AXOw( BX_CPU_C *,bxInstruction_c *);
	BX_SMF_FORCE void MOV_OwAX( BX_CPU_C *,bxInstruction_c *);
	BX_SMF_FORCE void MOV_EAXOd( BX_CPU_C *,bxInstruction_c *);
	BX_SMF_FORCE void MOV_OdEAX( BX_CPU_C *,bxInstruction_c *);


	BX_SMF_FORCE void MOV_RLIb( BX_CPU_C *,bxInstruction_c *);
	BX_SMF_FORCE void MOV_RHIb( BX_CPU_C *,bxInstruction_c *);
	BX_SMF_FORCE void MOV_RXIw( BX_CPU_C *,bxInstruction_c *);
	BX_SMF_FORCE void MOV_ERXId( BX_CPU_C *,bxInstruction_c *);

	BX_SMF_FORCE void XCHG_EGbGb( BX_CPU_C *,bxInstruction_c *);
	BX_SMF_FORCE void XCHG_EGwGw( BX_CPU_C *,bxInstruction_c *);
	BX_SMF_FORCE void XCHG_EGdGd( BX_CPU_C *,bxInstruction_c *);

	BX_SMF_FORCE void XCHG_EEbGb( BX_CPU_C *,bxInstruction_c *);
	BX_SMF_FORCE void XCHG_EEwGw( BX_CPU_C *,bxInstruction_c *);
	BX_SMF_FORCE void XCHG_EEdGd( BX_CPU_C *,bxInstruction_c *);

	BX_SMF_FORCE void XCHG_RXAX( BX_CPU_C *,bxInstruction_c *);
	BX_SMF_FORCE void XCHG_ERXEAX( BX_CPU_C *,bxInstruction_c *);

	BX_SMF_FORCE void BSF_GwEGw( BX_CPU_C *,bxInstruction_c *);
	BX_SMF_FORCE void BSF_GdEGd( BX_CPU_C *,bxInstruction_c *);
	BX_SMF_FORCE void BSR_GwEGw( BX_CPU_C *,bxInstruction_c *);
	BX_SMF_FORCE void BSR_GdEGd( BX_CPU_C *,bxInstruction_c *);

	BX_SMF_FORCE void BSF_GwEEw( BX_CPU_C *,bxInstruction_c *);
	BX_SMF_FORCE void BSF_GdEEd( BX_CPU_C *,bxInstruction_c *);
	BX_SMF_FORCE void BSR_GwEEw( BX_CPU_C *,bxInstruction_c *);
	BX_SMF_FORCE void BSR_GdEEd( BX_CPU_C *,bxInstruction_c *);

	BX_SMF_FORCE void BT_EGwGw( BX_CPU_C *,bxInstruction_c *);
	BX_SMF_FORCE void BT_EGdGd( BX_CPU_C *,bxInstruction_c *);
	BX_SMF_FORCE void BT_EGwIb( BX_CPU_C *,bxInstruction_c *);
	BX_SMF_FORCE void BT_EGdIb( BX_CPU_C *,bxInstruction_c *);

	BX_SMF_FORCE void BT_EEwGw( BX_CPU_C *,bxInstruction_c *);
	BX_SMF_FORCE void BT_EEdGd( BX_CPU_C *,bxInstruction_c *);
	BX_SMF_FORCE void BT_EEwIb( BX_CPU_C *,bxInstruction_c *);
	BX_SMF_FORCE void BT_EEdIb( BX_CPU_C *,bxInstruction_c *);

	BX_SMF_FORCE void BTS_EGwGw( BX_CPU_C *,bxInstruction_c *);
	BX_SMF_FORCE void BTS_EGdGd( BX_CPU_C *,bxInstruction_c *);
	BX_SMF_FORCE void BTS_EGwIb( BX_CPU_C *,bxInstruction_c *);
	BX_SMF_FORCE void BTS_EGdIb( BX_CPU_C *,bxInstruction_c *);

	BX_SMF_FORCE void BTS_EEwGw( BX_CPU_C *,bxInstruction_c *);
	BX_SMF_FORCE void BTS_EEdGd( BX_CPU_C *,bxInstruction_c *);
	BX_SMF_FORCE void BTS_EEwIb( BX_CPU_C *,bxInstruction_c *);
	BX_SMF_FORCE void BTS_EEdIb( BX_CPU_C *,bxInstruction_c *);

	BX_SMF_FORCE void BTR_EGwGw( BX_CPU_C *,bxInstruction_c *);
	BX_SMF_FORCE void BTR_EGdGd( BX_CPU_C *,bxInstruction_c *);
	BX_SMF_FORCE void BTR_EGwIb( BX_CPU_C *,bxInstruction_c *);
	BX_SMF_FORCE void BTR_EGdIb( BX_CPU_C *,bxInstruction_c *);

	BX_SMF_FORCE void BTR_EEwGw( BX_CPU_C *,bxInstruction_c *);
	BX_SMF_FORCE void BTR_EEdGd( BX_CPU_C *,bxInstruction_c *);
	BX_SMF_FORCE void BTR_EEwIb( BX_CPU_C *,bxInstruction_c *);
	BX_SMF_FORCE void BTR_EEdIb( BX_CPU_C *,bxInstruction_c *);

	BX_SMF_FORCE void BTC_EGwGw( BX_CPU_C *,bxInstruction_c *);
	BX_SMF_FORCE void BTC_EGdGd( BX_CPU_C *,bxInstruction_c *);
	BX_SMF_FORCE void BTC_EGwIb( BX_CPU_C *,bxInstruction_c *);
	BX_SMF_FORCE void BTC_EGdIb( BX_CPU_C *,bxInstruction_c *);

	BX_SMF_FORCE void BTC_EEwGw( BX_CPU_C *,bxInstruction_c *);
	BX_SMF_FORCE void BTC_EEdGd( BX_CPU_C *,bxInstruction_c *);
	BX_SMF_FORCE void BTC_EEwIb( BX_CPU_C *,bxInstruction_c *);
	BX_SMF_FORCE void BTC_EEdIb( BX_CPU_C *,bxInstruction_c *);
	//---------------------------------------------------------------

	BX_SMF_FORCE void ROL_EGb_0( BX_CPU_C *,bxInstruction_c *);
	BX_SMF_FORCE void ROL_EGw_0( BX_CPU_C *,bxInstruction_c *);
	BX_SMF_FORCE void ROL_EGd_0( BX_CPU_C *,bxInstruction_c *);
	BX_SMF_FORCE void ROL_EEb_0( BX_CPU_C *,bxInstruction_c *);
	BX_SMF_FORCE void ROL_EEw_0( BX_CPU_C *,bxInstruction_c *);
	BX_SMF_FORCE void ROL_EEd_0( BX_CPU_C *,bxInstruction_c *);

	BX_SMF_FORCE void ROL_EGb_1( BX_CPU_C *,bxInstruction_c *);
	BX_SMF_FORCE void ROL_EGw_1( BX_CPU_C *,bxInstruction_c *);
	BX_SMF_FORCE void ROL_EGd_1( BX_CPU_C *,bxInstruction_c *);
	BX_SMF_FORCE void ROR_EGb_1( BX_CPU_C *,bxInstruction_c *);
	BX_SMF_FORCE void ROR_EGw_1( BX_CPU_C *,bxInstruction_c *);
	BX_SMF_FORCE void ROR_EGd_1( BX_CPU_C *,bxInstruction_c *);
	BX_SMF_FORCE void RCL_EGb_1( BX_CPU_C *,bxInstruction_c *);
	BX_SMF_FORCE void RCL_EGw_1( BX_CPU_C *,bxInstruction_c *);
	BX_SMF_FORCE void RCL_EGd_1( BX_CPU_C *,bxInstruction_c *);
	BX_SMF_FORCE void RCR_EGb_1( BX_CPU_C *,bxInstruction_c *);
	BX_SMF_FORCE void RCR_EGw_1( BX_CPU_C *,bxInstruction_c *);
	BX_SMF_FORCE void RCR_EGd_1( BX_CPU_C *,bxInstruction_c *);
	BX_SMF_FORCE void SHL_EGb_1( BX_CPU_C *,bxInstruction_c *);
	BX_SMF_FORCE void SHL_EGw_1( BX_CPU_C *,bxInstruction_c *);
	BX_SMF_FORCE void SHL_EGd_1( BX_CPU_C *,bxInstruction_c *);
	BX_SMF_FORCE void SHR_EGb_1( BX_CPU_C *,bxInstruction_c *);
	BX_SMF_FORCE void SHR_EGw_1( BX_CPU_C *,bxInstruction_c *);
	BX_SMF_FORCE void SHR_EGd_1( BX_CPU_C *,bxInstruction_c *);
	BX_SMF_FORCE void SAR_EGb_1( BX_CPU_C *,bxInstruction_c *);
	BX_SMF_FORCE void SAR_EGw_1( BX_CPU_C *,bxInstruction_c *);
	BX_SMF_FORCE void SAR_EGd_1( BX_CPU_C *,bxInstruction_c *);

	BX_SMF_FORCE void ROL_EGb_n( BX_CPU_C *,bxInstruction_c *);
	BX_SMF_FORCE void ROL_EGw_n( BX_CPU_C *,bxInstruction_c *);
	BX_SMF_FORCE void ROL_EGd_n( BX_CPU_C *,bxInstruction_c *);
	BX_SMF_FORCE void ROR_EGb_n( BX_CPU_C *,bxInstruction_c *);
	BX_SMF_FORCE void ROR_EGw_n( BX_CPU_C *,bxInstruction_c *);
	BX_SMF_FORCE void ROR_EGd_n( BX_CPU_C *,bxInstruction_c *);
	BX_SMF_FORCE void RCL_EGb_n( BX_CPU_C *,bxInstruction_c *);
	BX_SMF_FORCE void RCL_EGw_n( BX_CPU_C *,bxInstruction_c *);
	BX_SMF_FORCE void RCL_EGd_n( BX_CPU_C *,bxInstruction_c *);
	BX_SMF_FORCE void RCR_EGb_n( BX_CPU_C *,bxInstruction_c *);
	BX_SMF_FORCE void RCR_EGw_n( BX_CPU_C *,bxInstruction_c *);
	BX_SMF_FORCE void RCR_EGd_n( BX_CPU_C *,bxInstruction_c *);
	BX_SMF_FORCE void SHL_EGb_n( BX_CPU_C *,bxInstruction_c *);
	BX_SMF_FORCE void SHL_EGw_n( BX_CPU_C *,bxInstruction_c *);
	BX_SMF_FORCE void SHL_EGd_n( BX_CPU_C *,bxInstruction_c *);
	BX_SMF_FORCE void SHR_EGb_n( BX_CPU_C *,bxInstruction_c *);
	BX_SMF_FORCE void SHR_EGw_n( BX_CPU_C *,bxInstruction_c *);
	BX_SMF_FORCE void SHR_EGd_n( BX_CPU_C *,bxInstruction_c *);
	BX_SMF_FORCE void SAR_EGb_n( BX_CPU_C *,bxInstruction_c *);
	BX_SMF_FORCE void SAR_EGw_n( BX_CPU_C *,bxInstruction_c *);
	BX_SMF_FORCE void SAR_EGd_n( BX_CPU_C *,bxInstruction_c *);

	BX_SMF_FORCE void SHLD_EGwGw_1( BX_CPU_C *,bxInstruction_c *);
	BX_SMF_FORCE void SHLD_EGdGd_1( BX_CPU_C *,bxInstruction_c *);
	BX_SMF_FORCE void SHRD_EGwGw_1( BX_CPU_C *,bxInstruction_c *);
	BX_SMF_FORCE void SHRD_EGdGd_1( BX_CPU_C *,bxInstruction_c *);
	BX_SMF_FORCE void SHLD_EGwGw_n( BX_CPU_C *,bxInstruction_c *);
	BX_SMF_FORCE void SHLD_EGdGd_n( BX_CPU_C *,bxInstruction_c *);
	BX_SMF_FORCE void SHRD_EGwGw_n( BX_CPU_C *,bxInstruction_c *);
	BX_SMF_FORCE void SHRD_EGdGd_n( BX_CPU_C *,bxInstruction_c *);
	//-------------------------------------------


	BX_SMF_FORCE void ROL_EEb_1( BX_CPU_C *,bxInstruction_c *);
	BX_SMF_FORCE void ROL_EEw_1( BX_CPU_C *,bxInstruction_c *);
	BX_SMF_FORCE void ROL_EEd_1( BX_CPU_C *,bxInstruction_c *);
	BX_SMF_FORCE void ROR_EEb_1( BX_CPU_C *,bxInstruction_c *);
	BX_SMF_FORCE void ROR_EEw_1( BX_CPU_C *,bxInstruction_c *);
	BX_SMF_FORCE void ROR_EEd_1( BX_CPU_C *,bxInstruction_c *);
	BX_SMF_FORCE void RCL_EEb_1( BX_CPU_C *,bxInstruction_c *);
	BX_SMF_FORCE void RCL_EEw_1( BX_CPU_C *,bxInstruction_c *);
	BX_SMF_FORCE void RCL_EEd_1( BX_CPU_C *,bxInstruction_c *);
	BX_SMF_FORCE void RCR_EEb_1( BX_CPU_C *,bxInstruction_c *);
	BX_SMF_FORCE void RCR_EEw_1( BX_CPU_C *,bxInstruction_c *);
	BX_SMF_FORCE void RCR_EEd_1( BX_CPU_C *,bxInstruction_c *);
	BX_SMF_FORCE void SHL_EEb_1( BX_CPU_C *,bxInstruction_c *);
	BX_SMF_FORCE void SHL_EEw_1( BX_CPU_C *,bxInstruction_c *);
	BX_SMF_FORCE void SHL_EEd_1( BX_CPU_C *,bxInstruction_c *);
	BX_SMF_FORCE void SHR_EEb_1( BX_CPU_C *,bxInstruction_c *);
	BX_SMF_FORCE void SHR_EEw_1( BX_CPU_C *,bxInstruction_c *);
	BX_SMF_FORCE void SHR_EEd_1( BX_CPU_C *,bxInstruction_c *);
	BX_SMF_FORCE void SAR_EEb_1( BX_CPU_C *,bxInstruction_c *);
	BX_SMF_FORCE void SAR_EEw_1( BX_CPU_C *,bxInstruction_c *);
	BX_SMF_FORCE void SAR_EEd_1( BX_CPU_C *,bxInstruction_c *);

	BX_SMF_FORCE void ROL_EEb_n( BX_CPU_C *,bxInstruction_c *);
	BX_SMF_FORCE void ROL_EEw_n( BX_CPU_C *,bxInstruction_c *);
	BX_SMF_FORCE void ROL_EEd_n( BX_CPU_C *,bxInstruction_c *);
	BX_SMF_FORCE void ROR_EEb_n( BX_CPU_C *,bxInstruction_c *);
	BX_SMF_FORCE void ROR_EEw_n( BX_CPU_C *,bxInstruction_c *);
	BX_SMF_FORCE void ROR_EEd_n( BX_CPU_C *,bxInstruction_c *);
	BX_SMF_FORCE void RCL_EEb_n( BX_CPU_C *,bxInstruction_c *);
	BX_SMF_FORCE void RCL_EEw_n( BX_CPU_C *,bxInstruction_c *);
	BX_SMF_FORCE void RCL_EEd_n( BX_CPU_C *,bxInstruction_c *);
	BX_SMF_FORCE void RCR_EEb_n( BX_CPU_C *,bxInstruction_c *);
	BX_SMF_FORCE void RCR_EEw_n( BX_CPU_C *,bxInstruction_c *);
	BX_SMF_FORCE void RCR_EEd_n( BX_CPU_C *,bxInstruction_c *);
	BX_SMF_FORCE void SHL_EEb_n( BX_CPU_C *,bxInstruction_c *);
	BX_SMF_FORCE void SHL_EEw_n( BX_CPU_C *,bxInstruction_c *);
	BX_SMF_FORCE void SHL_EEd_n( BX_CPU_C *,bxInstruction_c *);
	BX_SMF_FORCE void SHR_EEb_n( BX_CPU_C *,bxInstruction_c *);
	BX_SMF_FORCE void SHR_EEw_n( BX_CPU_C *,bxInstruction_c *);
	BX_SMF_FORCE void SHR_EEd_n( BX_CPU_C *,bxInstruction_c *);
	BX_SMF_FORCE void SAR_EEb_n( BX_CPU_C *,bxInstruction_c *);
	BX_SMF_FORCE void SAR_EEw_n( BX_CPU_C *,bxInstruction_c *);
	BX_SMF_FORCE void SAR_EEd_n( BX_CPU_C *,bxInstruction_c *);

	BX_SMF_FORCE void SHLD_EEwGw_1( BX_CPU_C *,bxInstruction_c *);
	BX_SMF_FORCE void SHLD_EEdGd_1( BX_CPU_C *,bxInstruction_c *);
	BX_SMF_FORCE void SHRD_EEwGw_1( BX_CPU_C *,bxInstruction_c *);
	BX_SMF_FORCE void SHRD_EEdGd_1( BX_CPU_C *,bxInstruction_c *);
	BX_SMF_FORCE void SHLD_EEwGw_n( BX_CPU_C *,bxInstruction_c *);
	BX_SMF_FORCE void SHLD_EEdGd_n( BX_CPU_C *,bxInstruction_c *);
	BX_SMF_FORCE void SHRD_EEwGw_n( BX_CPU_C *,bxInstruction_c *);
	BX_SMF_FORCE void SHRD_EEdGd_n( BX_CPU_C *,bxInstruction_c *);
	//--------------------------------------------

	BX_SMF_FORCE void ROL_EGb( BX_CPU_C *,bxInstruction_c *);
	BX_SMF_FORCE void ROL_EGw( BX_CPU_C *,bxInstruction_c *);
	BX_SMF_FORCE void ROL_EGd( BX_CPU_C *,bxInstruction_c *);
	BX_SMF_FORCE void ROR_EGb( BX_CPU_C *,bxInstruction_c *);
	BX_SMF_FORCE void ROR_EGw( BX_CPU_C *,bxInstruction_c *);
	BX_SMF_FORCE void ROR_EGd( BX_CPU_C *,bxInstruction_c *);
	BX_SMF_FORCE void RCL_EGb( BX_CPU_C *,bxInstruction_c *);
	BX_SMF_FORCE void RCL_EGw( BX_CPU_C *,bxInstruction_c *);
	BX_SMF_FORCE void RCL_EGd( BX_CPU_C *,bxInstruction_c *);
	BX_SMF_FORCE void RCR_EGb( BX_CPU_C *,bxInstruction_c *);
	BX_SMF_FORCE void RCR_EGw( BX_CPU_C *,bxInstruction_c *);
	BX_SMF_FORCE void RCR_EGd( BX_CPU_C *,bxInstruction_c *);
	BX_SMF_FORCE void SHL_EGb( BX_CPU_C *,bxInstruction_c *);
	BX_SMF_FORCE void SHL_EGw( BX_CPU_C *,bxInstruction_c *);
	BX_SMF_FORCE void SHL_EGd( BX_CPU_C *,bxInstruction_c *);
	BX_SMF_FORCE void SHR_EGb( BX_CPU_C *,bxInstruction_c *);
	BX_SMF_FORCE void SHR_EGw( BX_CPU_C *,bxInstruction_c *);
	BX_SMF_FORCE void SHR_EGd( BX_CPU_C *,bxInstruction_c *);
	BX_SMF_FORCE void SAR_EGb( BX_CPU_C *,bxInstruction_c *);
	BX_SMF_FORCE void SAR_EGw( BX_CPU_C *,bxInstruction_c *);
	BX_SMF_FORCE void SAR_EGd( BX_CPU_C *,bxInstruction_c *);
	//-------------------------------------------

	BX_SMF_FORCE void ROL_EEb( BX_CPU_C *,bxInstruction_c *);
	BX_SMF_FORCE void ROL_EEw( BX_CPU_C *,bxInstruction_c *);
	BX_SMF_FORCE void ROL_EEd( BX_CPU_C *,bxInstruction_c *);
	BX_SMF_FORCE void ROR_EEb( BX_CPU_C *,bxInstruction_c *);
	BX_SMF_FORCE void ROR_EEw( BX_CPU_C *,bxInstruction_c *);
	BX_SMF_FORCE void ROR_EEd( BX_CPU_C *,bxInstruction_c *);
	BX_SMF_FORCE void RCL_EEb( BX_CPU_C *,bxInstruction_c *);
	BX_SMF_FORCE void RCL_EEw( BX_CPU_C *,bxInstruction_c *);
	BX_SMF_FORCE void RCL_EEd( BX_CPU_C *,bxInstruction_c *);
	BX_SMF_FORCE void RCR_EEb( BX_CPU_C *,bxInstruction_c *);
	BX_SMF_FORCE void RCR_EEw( BX_CPU_C *,bxInstruction_c *);
	BX_SMF_FORCE void RCR_EEd( BX_CPU_C *,bxInstruction_c *);
	BX_SMF_FORCE void SHL_EEb( BX_CPU_C *,bxInstruction_c *);
	BX_SMF_FORCE void SHL_EEw( BX_CPU_C *,bxInstruction_c *);
	BX_SMF_FORCE void SHL_EEd( BX_CPU_C *,bxInstruction_c *);
	BX_SMF_FORCE void SHR_EEb( BX_CPU_C *,bxInstruction_c *);
	BX_SMF_FORCE void SHR_EEw( BX_CPU_C *,bxInstruction_c *);
	BX_SMF_FORCE void SHR_EEd( BX_CPU_C *,bxInstruction_c *);
	BX_SMF_FORCE void SAR_EEb( BX_CPU_C *,bxInstruction_c *);
	BX_SMF_FORCE void SAR_EEw( BX_CPU_C *,bxInstruction_c *);
	BX_SMF_FORCE void SAR_EEd( BX_CPU_C *,bxInstruction_c *);
	//-------------------------------------------
	//-------------------------------------------
	BX_SMF_FORCE void ROL_EGbCL( BX_CPU_C *,bxInstruction_c *);
	BX_SMF_FORCE void ROL_EGwCL( BX_CPU_C *,bxInstruction_c *);
	BX_SMF_FORCE void ROL_EGdCL( BX_CPU_C *,bxInstruction_c *);
	BX_SMF_FORCE void ROR_EGbCL( BX_CPU_C *,bxInstruction_c *);
	BX_SMF_FORCE void ROR_EGwCL( BX_CPU_C *,bxInstruction_c *);
	BX_SMF_FORCE void ROR_EGdCL( BX_CPU_C *,bxInstruction_c *);
	BX_SMF_FORCE void RCL_EGbCL( BX_CPU_C *,bxInstruction_c *);
	BX_SMF_FORCE void RCL_EGwCL( BX_CPU_C *,bxInstruction_c *);
	BX_SMF_FORCE void RCL_EGdCL( BX_CPU_C *,bxInstruction_c *);
	BX_SMF_FORCE void RCR_EGbCL( BX_CPU_C *,bxInstruction_c *);
	BX_SMF_FORCE void RCR_EGwCL( BX_CPU_C *,bxInstruction_c *);
	BX_SMF_FORCE void RCR_EGdCL( BX_CPU_C *,bxInstruction_c *);
	BX_SMF_FORCE void SHL_EGbCL( BX_CPU_C *,bxInstruction_c *);
	BX_SMF_FORCE void SHL_EGwCL( BX_CPU_C *,bxInstruction_c *);
	BX_SMF_FORCE void SHL_EGdCL( BX_CPU_C *,bxInstruction_c *);
	BX_SMF_FORCE void SHR_EGbCL( BX_CPU_C *,bxInstruction_c *);
	BX_SMF_FORCE void SHR_EGwCL( BX_CPU_C *,bxInstruction_c *);
	BX_SMF_FORCE void SHR_EGdCL( BX_CPU_C *,bxInstruction_c *);
	BX_SMF_FORCE void SAR_EGbCL( BX_CPU_C *,bxInstruction_c *);
	BX_SMF_FORCE void SAR_EGwCL( BX_CPU_C *,bxInstruction_c *);
	BX_SMF_FORCE void SAR_EGdCL( BX_CPU_C *,bxInstruction_c *);

	BX_SMF_FORCE void ROL_EEbCL( BX_CPU_C *,bxInstruction_c *);
	BX_SMF_FORCE void ROL_EEwCL( BX_CPU_C *,bxInstruction_c *);
	BX_SMF_FORCE void ROL_EEdCL( BX_CPU_C *,bxInstruction_c *);
	BX_SMF_FORCE void ROR_EEbCL( BX_CPU_C *,bxInstruction_c *);
	BX_SMF_FORCE void ROR_EEwCL( BX_CPU_C *,bxInstruction_c *);
	BX_SMF_FORCE void ROR_EEdCL( BX_CPU_C *,bxInstruction_c *);
	BX_SMF_FORCE void RCL_EEbCL( BX_CPU_C *,bxInstruction_c *);
	BX_SMF_FORCE void RCL_EEwCL( BX_CPU_C *,bxInstruction_c *);
	BX_SMF_FORCE void RCL_EEdCL( BX_CPU_C *,bxInstruction_c *);
	BX_SMF_FORCE void RCR_EEbCL( BX_CPU_C *,bxInstruction_c *);
	BX_SMF_FORCE void RCR_EEwCL( BX_CPU_C *,bxInstruction_c *);
	BX_SMF_FORCE void RCR_EEdCL( BX_CPU_C *,bxInstruction_c *);
	BX_SMF_FORCE void SHL_EEbCL( BX_CPU_C *,bxInstruction_c *);
	BX_SMF_FORCE void SHL_EEwCL( BX_CPU_C *,bxInstruction_c *);
	BX_SMF_FORCE void SHL_EEdCL( BX_CPU_C *,bxInstruction_c *);
	BX_SMF_FORCE void SHR_EEbCL( BX_CPU_C *,bxInstruction_c *);
	BX_SMF_FORCE void SHR_EEwCL( BX_CPU_C *,bxInstruction_c *);
	BX_SMF_FORCE void SHR_EEdCL( BX_CPU_C *,bxInstruction_c *);
	BX_SMF_FORCE void SAR_EEbCL( BX_CPU_C *,bxInstruction_c *);
	BX_SMF_FORCE void SAR_EEwCL( BX_CPU_C *,bxInstruction_c *);
	BX_SMF_FORCE void SAR_EEdCL( BX_CPU_C *,bxInstruction_c *);

	//-------------------------------------------
	//-------------------------------------------
	BX_SMF_FORCE void SHLD_EGwGw( BX_CPU_C *,bxInstruction_c *);
	BX_SMF_FORCE void SHLD_EGdGd( BX_CPU_C *,bxInstruction_c *);
	BX_SMF_FORCE void SHRD_EGwGw( BX_CPU_C *,bxInstruction_c *);
	BX_SMF_FORCE void SHRD_EGdGd( BX_CPU_C *,bxInstruction_c *);

	BX_SMF_FORCE void SHLD_EEwGw( BX_CPU_C *,bxInstruction_c *);
	BX_SMF_FORCE void SHLD_EEdGd( BX_CPU_C *,bxInstruction_c *);
	BX_SMF_FORCE void SHRD_EEwGw( BX_CPU_C *,bxInstruction_c *);
	BX_SMF_FORCE void SHRD_EEdGd( BX_CPU_C *,bxInstruction_c *);

	BX_SMF_FORCE void SHLD_EGwGwCL( BX_CPU_C *,bxInstruction_c *);
	BX_SMF_FORCE void SHLD_EGdGdCL( BX_CPU_C *,bxInstruction_c *);
	BX_SMF_FORCE void SHRD_EGwGwCL( BX_CPU_C *,bxInstruction_c *);
	BX_SMF_FORCE void SHRD_EGdGdCL( BX_CPU_C *,bxInstruction_c *);

	BX_SMF_FORCE void SHLD_EEwGwCL( BX_CPU_C *,bxInstruction_c *);
	BX_SMF_FORCE void SHLD_EEdGdCL( BX_CPU_C *,bxInstruction_c *);
	BX_SMF_FORCE void SHRD_EEwGwCL( BX_CPU_C *,bxInstruction_c *);
	BX_SMF_FORCE void SHRD_EEdGdCL( BX_CPU_C *,bxInstruction_c *);
	//-------------------------------------------
	//-------------------------------------------
	BX_SMF_FORCE void DIV_ALEGb( BX_CPU_C *,bxInstruction_c *);
	BX_SMF_FORCE void DIV_AXEGw( BX_CPU_C *,bxInstruction_c *);
	BX_SMF_FORCE void DIV_EAXEGd( BX_CPU_C *,bxInstruction_c *);
	BX_SMF_FORCE void IDIV_ALEGb( BX_CPU_C *,bxInstruction_c *);
	BX_SMF_FORCE void IDIV_AXEGw( BX_CPU_C *,bxInstruction_c *);
	BX_SMF_FORCE void IDIV_EAXEGd( BX_CPU_C *,bxInstruction_c *);

	BX_SMF_FORCE void DIV_ALEEb( BX_CPU_C *,bxInstruction_c *);
	BX_SMF_FORCE void DIV_AXEEw( BX_CPU_C *,bxInstruction_c *);
	BX_SMF_FORCE void DIV_EAXEEd( BX_CPU_C *,bxInstruction_c *);
	BX_SMF_FORCE void IDIV_ALEEb( BX_CPU_C *,bxInstruction_c *);
	BX_SMF_FORCE void IDIV_AXEEw( BX_CPU_C *,bxInstruction_c *);
	BX_SMF_FORCE void IDIV_EAXEEd( BX_CPU_C *,bxInstruction_c *);

	BX_SMF_FORCE void MUL_ALEGb( BX_CPU_C *,bxInstruction_c *);
	BX_SMF_FORCE void MUL_AXEGw( BX_CPU_C *,bxInstruction_c *);
	BX_SMF_FORCE void MUL_EAXEGd( BX_CPU_C *,bxInstruction_c *);
	BX_SMF_FORCE void IMUL_ALEGb( BX_CPU_C *,bxInstruction_c *);
	BX_SMF_FORCE void IMUL_AXEGw( BX_CPU_C *,bxInstruction_c *);
	BX_SMF_FORCE void IMUL_EAXEGd( BX_CPU_C *,bxInstruction_c *);
	BX_SMF_FORCE void IMUL_GwEGw( BX_CPU_C *,bxInstruction_c *);
	BX_SMF_FORCE void IMUL_GdEGd( BX_CPU_C *,bxInstruction_c *);
	BX_SMF_FORCE void IMUL_GwEGwIw( BX_CPU_C *,bxInstruction_c *);
	BX_SMF_FORCE void IMUL_GdEGdId( BX_CPU_C *,bxInstruction_c *);

	BX_SMF_FORCE void MUL_ALEEb( BX_CPU_C *,bxInstruction_c *);
	BX_SMF_FORCE void MUL_AXEEw( BX_CPU_C *,bxInstruction_c *);
	BX_SMF_FORCE void MUL_EAXEEd( BX_CPU_C *,bxInstruction_c *);
	BX_SMF_FORCE void IMUL_ALEEb( BX_CPU_C *,bxInstruction_c *);
	BX_SMF_FORCE void IMUL_AXEEw( BX_CPU_C *,bxInstruction_c *);
	BX_SMF_FORCE void IMUL_EAXEEd( BX_CPU_C *,bxInstruction_c *);
	BX_SMF_FORCE void IMUL_GwEEw( BX_CPU_C *,bxInstruction_c *);
	BX_SMF_FORCE void IMUL_GdEEd( BX_CPU_C *,bxInstruction_c *);
	BX_SMF_FORCE void IMUL_GwEEwIw( BX_CPU_C *,bxInstruction_c *);
	BX_SMF_FORCE void IMUL_GdEEdId( BX_CPU_C *,bxInstruction_c *);

  // prototypes for CPU instructions...

  BX_SMF_FORCE void PUSH_ES( BX_CPU_C *,bxInstruction_c *);
  BX_SMF_FORCE void PUSH_CS( BX_CPU_C *,bxInstruction_c *);
  BX_SMF_FORCE void PUSH_SS( BX_CPU_C *,bxInstruction_c *);
  BX_SMF_FORCE void PUSH_DS( BX_CPU_C *,bxInstruction_c *);
  BX_SMF_FORCE void PUSH_FS( BX_CPU_C *,bxInstruction_c *);
  BX_SMF_FORCE void PUSH_GS( BX_CPU_C *,bxInstruction_c *);
  BX_SMF_FORCE void POP_ES( BX_CPU_C *,bxInstruction_c *);
  BX_SMF_FORCE void POP_SS( BX_CPU_C *,bxInstruction_c *);
  BX_SMF_FORCE void POP_DS( BX_CPU_C *,bxInstruction_c *);
  BX_SMF_FORCE void POP_FS( BX_CPU_C *,bxInstruction_c *);
  BX_SMF_FORCE void POP_GS( BX_CPU_C *,bxInstruction_c *);
  BX_SMF_FORCE void MOV_EwSw( BX_CPU_C *,bxInstruction_c *);
  BX_SMF_FORCE void MOV_SwEw( BX_CPU_C *,bxInstruction_c *);
  BX_SMF_FORCE void LES_GvMp( BX_CPU_C *,bxInstruction_c *);
  BX_SMF_FORCE void LDS_GvMp( BX_CPU_C *,bxInstruction_c *);
  BX_SMF_FORCE void LSS_GvMp( BX_CPU_C *,bxInstruction_c *);
  BX_SMF_FORCE void LFS_GvMp( BX_CPU_C *,bxInstruction_c *);
  BX_SMF_FORCE void LGS_GvMp( BX_CPU_C *,bxInstruction_c *);

  BX_SMF_FORCE void DAA( BX_CPU_C *,bxInstruction_c *);
  BX_SMF_FORCE void DAS( BX_CPU_C *,bxInstruction_c *);
  BX_SMF_FORCE void AAA( BX_CPU_C *,bxInstruction_c *);
  BX_SMF_FORCE void AAS( BX_CPU_C *,bxInstruction_c *);
  BX_SMF_FORCE void AAM( BX_CPU_C *,bxInstruction_c *);
  BX_SMF_FORCE void AAD( BX_CPU_C *,bxInstruction_c *);

  BX_SMF_FORCE void CBW( BX_CPU_C *,bxInstruction_c *);
  BX_SMF_FORCE void CWD( BX_CPU_C *,bxInstruction_c *);
  BX_SMF_FORCE void CDQ( BX_CPU_C *,bxInstruction_c *);
  BX_SMF_FORCE void CWDE( BX_CPU_C *,bxInstruction_c *);

  BX_SMF_FORCE void SALC( BX_CPU_C *,bxInstruction_c *);
  BX_SMF_FORCE void XLAT( BX_CPU_C *,bxInstruction_c *);

  BX_SMF_FORCE void PUSHAD32( BX_CPU_C *,bxInstruction_c *);
  BX_SMF_FORCE void PUSHAD16( BX_CPU_C *,bxInstruction_c *);
  BX_SMF_FORCE void POPAD32( BX_CPU_C *,bxInstruction_c *);
  BX_SMF_FORCE void POPAD16( BX_CPU_C *,bxInstruction_c *);
  BX_SMF_FORCE void PUSH_Id( BX_CPU_C *,bxInstruction_c *);
  BX_SMF_FORCE void PUSH_Iw( BX_CPU_C *,bxInstruction_c *);
  BX_SMF_FORCE void POP_Ev( BX_CPU_C *,bxInstruction_c *);

  BX_SMF_FORCE void BOUND_GvMa( BX_CPU_C *,bxInstruction_c *);
  BX_SMF_FORCE void ARPL_EwGw( BX_CPU_C *,bxInstruction_c *);

  BX_SMF_FORCE void INSB_YbDX( BX_CPU_C *,bxInstruction_c *);
  BX_SMF_FORCE void INSW_YvDX( BX_CPU_C *,bxInstruction_c *);
  BX_SMF_FORCE void OUTSB_DXXb( BX_CPU_C *,bxInstruction_c *);
  BX_SMF_FORCE void OUTSW_DXXv( BX_CPU_C *,bxInstruction_c *);

  BX_SMF_FORCE void LEA_GdM( BX_CPU_C *,bxInstruction_c *);
  BX_SMF_FORCE void LEA_GwM( BX_CPU_C *,bxInstruction_c *);

  BX_SMF_FORCE void FWAIT( BX_CPU_C *,bxInstruction_c *);
  BX_SMF_FORCE void PUSHF( BX_CPU_C *,bxInstruction_c *);
  BX_SMF_FORCE void POPF( BX_CPU_C *,bxInstruction_c *);
  BX_SMF_FORCE void SAHF( BX_CPU_C *,bxInstruction_c *);
  BX_SMF_FORCE void LAHF( BX_CPU_C *,bxInstruction_c *);

  BX_SMF_FORCE void MOVSB_XbYb_E16_rep__( BX_CPU_C *,bxInstruction_c *);
  BX_SMF_FORCE void MOVSB_XbYb_E16_repf2( BX_CPU_C *,bxInstruction_c *);
  BX_SMF_FORCE void MOVSB_XbYb_E16_repf3( BX_CPU_C *,bxInstruction_c *);
  BX_SMF_FORCE void MOVSB_XbYb_E32_rep__( BX_CPU_C *,bxInstruction_c *);
  BX_SMF_FORCE void MOVSB_XbYb_E32_repf2( BX_CPU_C *,bxInstruction_c *);
  BX_SMF_FORCE void MOVSB_XbYb_E32_repf3( BX_CPU_C *,bxInstruction_c *);

  BX_SMF_FORCE void MOVSW_XvYv_E16_rep__( BX_CPU_C *,bxInstruction_c *);
  BX_SMF_FORCE void MOVSW_XvYv_E16_repf2( BX_CPU_C *,bxInstruction_c *);
  BX_SMF_FORCE void MOVSW_XvYv_E16_repf3( BX_CPU_C *,bxInstruction_c *);
  BX_SMF_FORCE void MOVSW_XvYv_E32_rep__( BX_CPU_C *,bxInstruction_c *);
  BX_SMF_FORCE void MOVSW_XvYv_E32_repf2( BX_CPU_C *,bxInstruction_c *);
  BX_SMF_FORCE void MOVSW_XvYv_E32_repf3( BX_CPU_C *,bxInstruction_c *);

  BX_SMF_FORCE void MOVSD_XvYv_E16_rep__( BX_CPU_C *,bxInstruction_c *);
  BX_SMF_FORCE void MOVSD_XvYv_E16_repf2( BX_CPU_C *,bxInstruction_c *);
  BX_SMF_FORCE void MOVSD_XvYv_E16_repf3( BX_CPU_C *,bxInstruction_c *);
  BX_SMF_FORCE void MOVSD_XvYv_E32_rep__( BX_CPU_C *,bxInstruction_c *);
  BX_SMF_FORCE void MOVSD_XvYv_E32_repf2( BX_CPU_C *,bxInstruction_c *);
  BX_SMF_FORCE void MOVSD_XvYv_E32_repf3( BX_CPU_C *,bxInstruction_c *);

  BX_SMF_FORCE void CMPSB_XbYb_E16_rep__( BX_CPU_C *,bxInstruction_c *);
  BX_SMF_FORCE void CMPSB_XbYb_E16_repf2( BX_CPU_C *,bxInstruction_c *);
  BX_SMF_FORCE void CMPSB_XbYb_E16_repf3( BX_CPU_C *,bxInstruction_c *);
  BX_SMF_FORCE void CMPSB_XbYb_E32_rep__( BX_CPU_C *,bxInstruction_c *);
  BX_SMF_FORCE void CMPSB_XbYb_E32_repf2( BX_CPU_C *,bxInstruction_c *);
  BX_SMF_FORCE void CMPSB_XbYb_E32_repf3( BX_CPU_C *,bxInstruction_c *);
								   
  BX_SMF_FORCE void CMPSW_XvYv_E16_rep__( BX_CPU_C *,bxInstruction_c *);
  BX_SMF_FORCE void CMPSW_XvYv_E16_repf2( BX_CPU_C *,bxInstruction_c *);
  BX_SMF_FORCE void CMPSW_XvYv_E16_repf3( BX_CPU_C *,bxInstruction_c *);
  BX_SMF_FORCE void CMPSW_XvYv_E32_rep__( BX_CPU_C *,bxInstruction_c *);
  BX_SMF_FORCE void CMPSW_XvYv_E32_repf2( BX_CPU_C *,bxInstruction_c *);
  BX_SMF_FORCE void CMPSW_XvYv_E32_repf3( BX_CPU_C *,bxInstruction_c *);
								   
  BX_SMF_FORCE void CMPSD_XvYv_E16_rep__( BX_CPU_C *,bxInstruction_c *);
  BX_SMF_FORCE void CMPSD_XvYv_E16_repf2( BX_CPU_C *,bxInstruction_c *);
  BX_SMF_FORCE void CMPSD_XvYv_E16_repf3( BX_CPU_C *,bxInstruction_c *);
  BX_SMF_FORCE void CMPSD_XvYv_E32_rep__( BX_CPU_C *,bxInstruction_c *);
  BX_SMF_FORCE void CMPSD_XvYv_E32_repf2( BX_CPU_C *,bxInstruction_c *);
  BX_SMF_FORCE void CMPSD_XvYv_E32_repf3( BX_CPU_C *,bxInstruction_c *);

  BX_SMF_FORCE void SCASB_ALYb_E16_rep__ ( BX_CPU_C *,bxInstruction_c *);
  BX_SMF_FORCE void SCASB_ALYb_E16_repf2 ( BX_CPU_C *,bxInstruction_c *);
  BX_SMF_FORCE void SCASB_ALYb_E16_repf3 ( BX_CPU_C *,bxInstruction_c *);
  BX_SMF_FORCE void SCASB_ALYb_E32_rep__ ( BX_CPU_C *,bxInstruction_c *);
  BX_SMF_FORCE void SCASB_ALYb_E32_repf2 ( BX_CPU_C *,bxInstruction_c *);
  BX_SMF_FORCE void SCASB_ALYb_E32_repf3 ( BX_CPU_C *,bxInstruction_c *);
									
  BX_SMF_FORCE void SCASW_eAXYv_E16_rep__( BX_CPU_C *,bxInstruction_c *);
  BX_SMF_FORCE void SCASW_eAXYv_E16_repf2( BX_CPU_C *,bxInstruction_c *);
  BX_SMF_FORCE void SCASW_eAXYv_E16_repf3( BX_CPU_C *,bxInstruction_c *);
  BX_SMF_FORCE void SCASW_eAXYv_E32_rep__( BX_CPU_C *,bxInstruction_c *);
  BX_SMF_FORCE void SCASW_eAXYv_E32_repf2( BX_CPU_C *,bxInstruction_c *);
  BX_SMF_FORCE void SCASW_eAXYv_E32_repf3( BX_CPU_C *,bxInstruction_c *);
									
  BX_SMF_FORCE void SCASD_eAXYv_E16_rep__( BX_CPU_C *,bxInstruction_c *);
  BX_SMF_FORCE void SCASD_eAXYv_E16_repf2( BX_CPU_C *,bxInstruction_c *);
  BX_SMF_FORCE void SCASD_eAXYv_E16_repf3( BX_CPU_C *,bxInstruction_c *);
  BX_SMF_FORCE void SCASD_eAXYv_E32_rep__( BX_CPU_C *,bxInstruction_c *);
  BX_SMF_FORCE void SCASD_eAXYv_E32_repf2( BX_CPU_C *,bxInstruction_c *);
  BX_SMF_FORCE void SCASD_eAXYv_E32_repf3( BX_CPU_C *,bxInstruction_c *);

  BX_SMF_FORCE void STOSB_ALYb_E16_rep__ ( BX_CPU_C *,bxInstruction_c *);
  BX_SMF_FORCE void STOSB_ALYb_E16_repf2 ( BX_CPU_C *,bxInstruction_c *);
  BX_SMF_FORCE void STOSB_ALYb_E16_repf3 ( BX_CPU_C *,bxInstruction_c *);
  BX_SMF_FORCE void STOSB_ALYb_E32_rep__ ( BX_CPU_C *,bxInstruction_c *);
  BX_SMF_FORCE void STOSB_ALYb_E32_repf2 ( BX_CPU_C *,bxInstruction_c *);
  BX_SMF_FORCE void STOSB_ALYb_E32_repf3 ( BX_CPU_C *,bxInstruction_c *);
									
  BX_SMF_FORCE void STOSW_eAXYv_E16_rep__( BX_CPU_C *,bxInstruction_c *);
  BX_SMF_FORCE void STOSW_eAXYv_E16_repf2( BX_CPU_C *,bxInstruction_c *);
  BX_SMF_FORCE void STOSW_eAXYv_E16_repf3( BX_CPU_C *,bxInstruction_c *);
  BX_SMF_FORCE void STOSW_eAXYv_E32_rep__( BX_CPU_C *,bxInstruction_c *);
  BX_SMF_FORCE void STOSW_eAXYv_E32_repf2( BX_CPU_C *,bxInstruction_c *);
  BX_SMF_FORCE void STOSW_eAXYv_E32_repf3( BX_CPU_C *,bxInstruction_c *);
									
  BX_SMF_FORCE void STOSD_eAXYv_E16_rep__( BX_CPU_C *,bxInstruction_c *);
  BX_SMF_FORCE void STOSD_eAXYv_E16_repf2( BX_CPU_C *,bxInstruction_c *);
  BX_SMF_FORCE void STOSD_eAXYv_E16_repf3( BX_CPU_C *,bxInstruction_c *);
  BX_SMF_FORCE void STOSD_eAXYv_E32_rep__( BX_CPU_C *,bxInstruction_c *);
  BX_SMF_FORCE void STOSD_eAXYv_E32_repf2( BX_CPU_C *,bxInstruction_c *);
  BX_SMF_FORCE void STOSD_eAXYv_E32_repf3( BX_CPU_C *,bxInstruction_c *);

  BX_SMF_FORCE void LODSB_ALXb_E16_rep__ ( BX_CPU_C *,bxInstruction_c *);
  BX_SMF_FORCE void LODSB_ALXb_E16_repf2 ( BX_CPU_C *,bxInstruction_c *);
  BX_SMF_FORCE void LODSB_ALXb_E16_repf3 ( BX_CPU_C *,bxInstruction_c *);
  BX_SMF_FORCE void LODSB_ALXb_E32_rep__ ( BX_CPU_C *,bxInstruction_c *);
  BX_SMF_FORCE void LODSB_ALXb_E32_repf2 ( BX_CPU_C *,bxInstruction_c *);
  BX_SMF_FORCE void LODSB_ALXb_E32_repf3 ( BX_CPU_C *,bxInstruction_c *);
									
  BX_SMF_FORCE void LODSW_eAXXv_E16_rep__( BX_CPU_C *,bxInstruction_c *);
  BX_SMF_FORCE void LODSW_eAXXv_E16_repf2( BX_CPU_C *,bxInstruction_c *);
  BX_SMF_FORCE void LODSW_eAXXv_E16_repf3( BX_CPU_C *,bxInstruction_c *);
  BX_SMF_FORCE void LODSW_eAXXv_E32_rep__( BX_CPU_C *,bxInstruction_c *);
  BX_SMF_FORCE void LODSW_eAXXv_E32_repf2( BX_CPU_C *,bxInstruction_c *);
  BX_SMF_FORCE void LODSW_eAXXv_E32_repf3( BX_CPU_C *,bxInstruction_c *);
									
  BX_SMF_FORCE void LODSD_eAXXv_E16_rep__( BX_CPU_C *,bxInstruction_c *);
  BX_SMF_FORCE void LODSD_eAXXv_E16_repf2( BX_CPU_C *,bxInstruction_c *);
  BX_SMF_FORCE void LODSD_eAXXv_E16_repf3( BX_CPU_C *,bxInstruction_c *);
  BX_SMF_FORCE void LODSD_eAXXv_E32_rep__( BX_CPU_C *,bxInstruction_c *);
  BX_SMF_FORCE void LODSD_eAXXv_E32_repf2( BX_CPU_C *,bxInstruction_c *);
  BX_SMF_FORCE void LODSD_eAXXv_E32_repf3( BX_CPU_C *,bxInstruction_c *);

  BX_SMF_FORCE void OUTSB_DXXb_E16_rep__( BX_CPU_C *,bxInstruction_c *);
  BX_SMF_FORCE void OUTSB_DXXb_E16_repf2( BX_CPU_C *,bxInstruction_c *);
  BX_SMF_FORCE void OUTSB_DXXb_E16_repf3( BX_CPU_C *,bxInstruction_c *);
  BX_SMF_FORCE void OUTSB_DXXb_E32_rep__( BX_CPU_C *,bxInstruction_c *);
  BX_SMF_FORCE void OUTSB_DXXb_E32_repf2( BX_CPU_C *,bxInstruction_c *);
  BX_SMF_FORCE void OUTSB_DXXb_E32_repf3( BX_CPU_C *,bxInstruction_c *);
			
  BX_SMF_FORCE void OUTSW_DXXv_E16_rep__( BX_CPU_C *,bxInstruction_c *);
  BX_SMF_FORCE void OUTSW_DXXv_E16_repf2( BX_CPU_C *,bxInstruction_c *);
  BX_SMF_FORCE void OUTSW_DXXv_E16_repf3( BX_CPU_C *,bxInstruction_c *);
  BX_SMF_FORCE void OUTSW_DXXv_E32_rep__( BX_CPU_C *,bxInstruction_c *);
  BX_SMF_FORCE void OUTSW_DXXv_E32_repf2( BX_CPU_C *,bxInstruction_c *);
  BX_SMF_FORCE void OUTSW_DXXv_E32_repf3( BX_CPU_C *,bxInstruction_c *);
			
  BX_SMF_FORCE void OUTSD_DXXv_E16_rep__( BX_CPU_C *,bxInstruction_c *);
  BX_SMF_FORCE void OUTSD_DXXv_E16_repf2( BX_CPU_C *,bxInstruction_c *);
  BX_SMF_FORCE void OUTSD_DXXv_E16_repf3( BX_CPU_C *,bxInstruction_c *);
  BX_SMF_FORCE void OUTSD_DXXv_E32_rep__( BX_CPU_C *,bxInstruction_c *);
  BX_SMF_FORCE void OUTSD_DXXv_E32_repf2( BX_CPU_C *,bxInstruction_c *);
  BX_SMF_FORCE void OUTSD_DXXv_E32_repf3( BX_CPU_C *,bxInstruction_c *);

  BX_SMF_FORCE void INSB_YbDX_E16_rep__( BX_CPU_C *,bxInstruction_c *);
  BX_SMF_FORCE void INSB_YbDX_E16_repf2( BX_CPU_C *,bxInstruction_c *);
  BX_SMF_FORCE void INSB_YbDX_E16_repf3( BX_CPU_C *,bxInstruction_c *);
  BX_SMF_FORCE void INSB_YbDX_E32_rep__( BX_CPU_C *,bxInstruction_c *);
  BX_SMF_FORCE void INSB_YbDX_E32_repf2( BX_CPU_C *,bxInstruction_c *);
  BX_SMF_FORCE void INSB_YbDX_E32_repf3( BX_CPU_C *,bxInstruction_c *);
			
  BX_SMF_FORCE void INSW_YvDX_E16_rep__( BX_CPU_C *,bxInstruction_c *);
  BX_SMF_FORCE void INSW_YvDX_E16_repf2( BX_CPU_C *,bxInstruction_c *);
  BX_SMF_FORCE void INSW_YvDX_E16_repf3( BX_CPU_C *,bxInstruction_c *);
  BX_SMF_FORCE void INSW_YvDX_E32_rep__( BX_CPU_C *,bxInstruction_c *);
  BX_SMF_FORCE void INSW_YvDX_E32_repf2( BX_CPU_C *,bxInstruction_c *);
  BX_SMF_FORCE void INSW_YvDX_E32_repf3( BX_CPU_C *,bxInstruction_c *);
			
  BX_SMF_FORCE void INSD_YvDX_E16_rep__( BX_CPU_C *,bxInstruction_c *);
  BX_SMF_FORCE void INSD_YvDX_E16_repf2( BX_CPU_C *,bxInstruction_c *);
  BX_SMF_FORCE void INSD_YvDX_E16_repf3( BX_CPU_C *,bxInstruction_c *);
  BX_SMF_FORCE void INSD_YvDX_E32_rep__( BX_CPU_C *,bxInstruction_c *);
  BX_SMF_FORCE void INSD_YvDX_E32_repf2( BX_CPU_C *,bxInstruction_c *);
  BX_SMF_FORCE void INSD_YvDX_E32_repf3( BX_CPU_C *,bxInstruction_c *);

  BX_SMF_FORCE void ENTER_IwIb( BX_CPU_C *,bxInstruction_c *);
  BX_SMF_FORCE void LEAVE( BX_CPU_C *,bxInstruction_c *);

  BX_SMF_FORCE void INT1( BX_CPU_C *,bxInstruction_c *);
  BX_SMF_FORCE void INT3( BX_CPU_C *,bxInstruction_c *);
  BX_SMF_FORCE void INT_Ib( BX_CPU_C *,bxInstruction_c *);
  BX_SMF_FORCE void INTO( BX_CPU_C *,bxInstruction_c *);
  BX_SMF_FORCE void IRET32( BX_CPU_C *,bxInstruction_c *);
  BX_SMF_FORCE void IRET16( BX_CPU_C *,bxInstruction_c *);

  BX_SMF_FORCE void IN_ALIb( BX_CPU_C *,bxInstruction_c *);
  BX_SMF_FORCE void IN_eAXIb( BX_CPU_C *,bxInstruction_c *);
  BX_SMF_FORCE void OUT_IbAL( BX_CPU_C *,bxInstruction_c *);
  BX_SMF_FORCE void OUT_IbeAX( BX_CPU_C *,bxInstruction_c *);
  BX_SMF_FORCE void IN_ALDX( BX_CPU_C *,bxInstruction_c *);
  BX_SMF_FORCE void IN_eAXDX( BX_CPU_C *,bxInstruction_c *);
  BX_SMF_FORCE void OUT_DXAL( BX_CPU_C *,bxInstruction_c *);
  BX_SMF_FORCE void OUT_DXeAX( BX_CPU_C *,bxInstruction_c *);

  BX_SMF_FORCE void HLT( BX_CPU_C *,bxInstruction_c *);
  BX_SMF_FORCE void CMC( BX_CPU_C *,bxInstruction_c *);
  BX_SMF_FORCE void CLC( BX_CPU_C *,bxInstruction_c *);
  BX_SMF_FORCE void STC( BX_CPU_C *,bxInstruction_c *);
  BX_SMF_FORCE void CLI( BX_CPU_C *,bxInstruction_c *);
  BX_SMF_FORCE void STI( BX_CPU_C *,bxInstruction_c *);
  BX_SMF_FORCE void CLD( BX_CPU_C *,bxInstruction_c *);
  BX_SMF_FORCE void STD( BX_CPU_C *,bxInstruction_c *);


  BX_SMF_FORCE void LAR_GvEw( BX_CPU_C *,bxInstruction_c *);
  BX_SMF_FORCE void LSL_GvEw( BX_CPU_C *,bxInstruction_c *);
  BX_SMF_FORCE void CLTS( BX_CPU_C *,bxInstruction_c *);
  BX_SMF_FORCE void INVD( BX_CPU_C *,bxInstruction_c *);
  BX_SMF_FORCE void WBINVD( BX_CPU_C *,bxInstruction_c *);

  BX_SMF_FORCE void MOV_CdRd( BX_CPU_C *,bxInstruction_c *);
  BX_SMF_FORCE void MOV_DdRd( BX_CPU_C *,bxInstruction_c *);
  BX_SMF_FORCE void MOV_RdCd( BX_CPU_C *,bxInstruction_c *);
  BX_SMF_FORCE void MOV_RdDd( BX_CPU_C *,bxInstruction_c *);
  BX_SMF_FORCE void MOV_TdRd( BX_CPU_C *,bxInstruction_c *);
  BX_SMF_FORCE void MOV_RdTd( BX_CPU_C *,bxInstruction_c *);

  BX_SMF_FORCE void SETcc_EGb( BX_CPU_C *,bxInstruction_c *);
  BX_SMF_FORCE void SETcc_EEb( BX_CPU_C *,bxInstruction_c *);

  BX_SMF_FORCE void Jcc0_Jw( BX_CPU_C *,bxInstruction_c *);
  BX_SMF_FORCE void Jcc1_Jw( BX_CPU_C *,bxInstruction_c *);
  BX_SMF_FORCE void Jcc2_Jw( BX_CPU_C *,bxInstruction_c *);
  BX_SMF_FORCE void Jcc3_Jw( BX_CPU_C *,bxInstruction_c *);
  BX_SMF_FORCE void Jcc4_Jw( BX_CPU_C *,bxInstruction_c *);
  BX_SMF_FORCE void Jcc5_Jw( BX_CPU_C *,bxInstruction_c *);
  BX_SMF_FORCE void Jcc6_Jw( BX_CPU_C *,bxInstruction_c *);
  BX_SMF_FORCE void Jcc7_Jw( BX_CPU_C *,bxInstruction_c *);
  BX_SMF_FORCE void Jcc8_Jw( BX_CPU_C *,bxInstruction_c *);
  BX_SMF_FORCE void Jcc9_Jw( BX_CPU_C *,bxInstruction_c *);
  BX_SMF_FORCE void Jcca_Jw( BX_CPU_C *,bxInstruction_c *);
  BX_SMF_FORCE void Jccb_Jw( BX_CPU_C *,bxInstruction_c *);
  BX_SMF_FORCE void Jccc_Jw( BX_CPU_C *,bxInstruction_c *);
  BX_SMF_FORCE void Jccd_Jw( BX_CPU_C *,bxInstruction_c *);
  BX_SMF_FORCE void Jcce_Jw( BX_CPU_C *,bxInstruction_c *);
  BX_SMF_FORCE void Jccf_Jw( BX_CPU_C *,bxInstruction_c *);
                
  BX_SMF_FORCE void Jcc0_Jd( BX_CPU_C *,bxInstruction_c *);
  BX_SMF_FORCE void Jcc1_Jd( BX_CPU_C *,bxInstruction_c *);
  BX_SMF_FORCE void Jcc2_Jd( BX_CPU_C *,bxInstruction_c *);
  BX_SMF_FORCE void Jcc3_Jd( BX_CPU_C *,bxInstruction_c *);
  BX_SMF_FORCE void Jcc4_Jd( BX_CPU_C *,bxInstruction_c *);
  BX_SMF_FORCE void Jcc5_Jd( BX_CPU_C *,bxInstruction_c *);
  BX_SMF_FORCE void Jcc6_Jd( BX_CPU_C *,bxInstruction_c *);
  BX_SMF_FORCE void Jcc7_Jd( BX_CPU_C *,bxInstruction_c *);
  BX_SMF_FORCE void Jcc8_Jd( BX_CPU_C *,bxInstruction_c *);
  BX_SMF_FORCE void Jcc9_Jd( BX_CPU_C *,bxInstruction_c *);
  BX_SMF_FORCE void Jcca_Jd( BX_CPU_C *,bxInstruction_c *);
  BX_SMF_FORCE void Jccb_Jd( BX_CPU_C *,bxInstruction_c *);
  BX_SMF_FORCE void Jccc_Jd( BX_CPU_C *,bxInstruction_c *);
  BX_SMF_FORCE void Jccd_Jd( BX_CPU_C *,bxInstruction_c *);
  BX_SMF_FORCE void Jcce_Jd( BX_CPU_C *,bxInstruction_c *);
  BX_SMF_FORCE void Jccf_Jd( BX_CPU_C *,bxInstruction_c *);

  BX_SMF_FORCE void JCXZ_Jw( BX_CPU_C *,bxInstruction_c *);
  BX_SMF_FORCE void JCXZ_Jd( BX_CPU_C *,bxInstruction_c *);

  BX_SMF_FORCE void LOOP_Jw( BX_CPU_C *,bxInstruction_c *);
  BX_SMF_FORCE void LOOP_Jd( BX_CPU_C *,bxInstruction_c *);

  BX_SMF_FORCE void LOOPE_Jw( BX_CPU_C *,bxInstruction_c *);
  BX_SMF_FORCE void LOOPE_Jd( BX_CPU_C *,bxInstruction_c *);

  BX_SMF_FORCE void LOOPNE_Jw( BX_CPU_C *,bxInstruction_c *);
  BX_SMF_FORCE void LOOPNE_Jd( BX_CPU_C *,bxInstruction_c *);

  BX_SMF_FORCE void JMP_Jw( BX_CPU_C *,bxInstruction_c *);
  BX_SMF_FORCE void JMP_Jd( BX_CPU_C *,bxInstruction_c *);

  BX_SMF_FORCE void CALL_Jw( BX_CPU_C *,bxInstruction_c *);
  BX_SMF_FORCE void CALL_Jd( BX_CPU_C *,bxInstruction_c *);

  BX_SMF_FORCE void JMP_EGw( BX_CPU_C *,bxInstruction_c *);
  BX_SMF_FORCE void JMP_EGd( BX_CPU_C *,bxInstruction_c *);
  BX_SMF_FORCE void JMP_EEw( BX_CPU_C *,bxInstruction_c *);
  BX_SMF_FORCE void JMP_EEd( BX_CPU_C *,bxInstruction_c *);
  BX_SMF_FORCE void CALL_EGw( BX_CPU_C *,bxInstruction_c *);
  BX_SMF_FORCE void CALL_EGd( BX_CPU_C *,bxInstruction_c *);
  BX_SMF_FORCE void CALL_EEw( BX_CPU_C *,bxInstruction_c *);
  BX_SMF_FORCE void CALL_EEd( BX_CPU_C *,bxInstruction_c *);

  BX_SMF_FORCE void JMP16_Ap( BX_CPU_C *,bxInstruction_c *);
  BX_SMF_FORCE void JMP16_Ep( BX_CPU_C *,bxInstruction_c *);
  BX_SMF_FORCE void JMP32_Ap( BX_CPU_C *,bxInstruction_c *);
  BX_SMF_FORCE void JMP32_Ep( BX_CPU_C *,bxInstruction_c *);

  BX_SMF_FORCE void CALL16_Ap( BX_CPU_C *,bxInstruction_c *);
  BX_SMF_FORCE void CALL16_Ep( BX_CPU_C *,bxInstruction_c *);
  BX_SMF_FORCE void CALL32_Ap( BX_CPU_C *,bxInstruction_c *);
  BX_SMF_FORCE void CALL32_Ep( BX_CPU_C *,bxInstruction_c *);

  BX_SMF_FORCE void RETnear32( BX_CPU_C *,bxInstruction_c *);
  BX_SMF_FORCE void RETnear16( BX_CPU_C *,bxInstruction_c *);
  BX_SMF_FORCE void RETnear32_Iw( BX_CPU_C *,bxInstruction_c *);
  BX_SMF_FORCE void RETnear16_Iw( BX_CPU_C *,bxInstruction_c *);
  BX_SMF_FORCE void RETfar32( BX_CPU_C *,bxInstruction_c *);
  BX_SMF_FORCE void RETfar16( BX_CPU_C *,bxInstruction_c *);
  BX_SMF_FORCE void RETfar32_Iw( BX_CPU_C *,bxInstruction_c *);
  BX_SMF_FORCE void RETfar16_Iw( BX_CPU_C *,bxInstruction_c *);

  BX_SMF_FORCE void BSWAP_ERX( BX_CPU_C *,bxInstruction_c *);
  BX_SMF_FORCE void BSWAP_EAX( BX_CPU_C *,bxInstruction_c *);
  BX_SMF_FORCE void BSWAP_ECX( BX_CPU_C *,bxInstruction_c *);
  BX_SMF_FORCE void BSWAP_EDX( BX_CPU_C *,bxInstruction_c *);
  BX_SMF_FORCE void BSWAP_EBX( BX_CPU_C *,bxInstruction_c *);
  BX_SMF_FORCE void BSWAP_ESP( BX_CPU_C *,bxInstruction_c *);
  BX_SMF_FORCE void BSWAP_EBP( BX_CPU_C *,bxInstruction_c *);
  BX_SMF_FORCE void BSWAP_ESI( BX_CPU_C *,bxInstruction_c *);
  BX_SMF_FORCE void BSWAP_EDI( BX_CPU_C *,bxInstruction_c *);

  BX_SMF_FORCE void SLDT_Ew( BX_CPU_C *,bxInstruction_c *);
  BX_SMF_FORCE void STR_Ew( BX_CPU_C *,bxInstruction_c *);
  BX_SMF_FORCE void LLDT_Ew( BX_CPU_C *,bxInstruction_c *);
  BX_SMF_FORCE void LTR_Ew( BX_CPU_C *,bxInstruction_c *);
  BX_SMF_FORCE void VERR_Ew( BX_CPU_C *,bxInstruction_c *);
  BX_SMF_FORCE void VERW_Ew( BX_CPU_C *,bxInstruction_c *);

  BX_SMF_FORCE void SGDT_Ms( BX_CPU_C *,bxInstruction_c *);
  BX_SMF_FORCE void SIDT_Ms( BX_CPU_C *,bxInstruction_c *);
  BX_SMF_FORCE void LGDT_Ms( BX_CPU_C *,bxInstruction_c *);
  BX_SMF_FORCE void LIDT_Ms( BX_CPU_C *,bxInstruction_c *);
  BX_SMF_FORCE void SMSW_Ew( BX_CPU_C *,bxInstruction_c *);
  BX_SMF_FORCE void LMSW_Ew( BX_CPU_C *,bxInstruction_c *);

  BX_SMF_FORCE void ESC0( BX_CPU_C *,bxInstruction_c *);
  BX_SMF_FORCE void ESC1( BX_CPU_C *,bxInstruction_c *);
  BX_SMF_FORCE void ESC2( BX_CPU_C *,bxInstruction_c *);
  BX_SMF_FORCE void ESC3( BX_CPU_C *,bxInstruction_c *);
  BX_SMF_FORCE void ESC4( BX_CPU_C *,bxInstruction_c *);
  BX_SMF_FORCE void ESC5( BX_CPU_C *,bxInstruction_c *);
  BX_SMF_FORCE void ESC6( BX_CPU_C *,bxInstruction_c *);
  BX_SMF_FORCE void ESC7( BX_CPU_C *,bxInstruction_c *);


  BX_SMF void fpu_execute(bxInstruction_c *i);
  BX_SMF void fpu_init(void);
  BX_SMF void fpu_print_regs (void);

  BX_SMF_FORCE void CMPXCHG_XBTS( BX_CPU_C *,bxInstruction_c *);
  BX_SMF_FORCE void CMPXCHG_IBTS( BX_CPU_C *,bxInstruction_c *);
  BX_SMF_FORCE void CMPXCHG8B( BX_CPU_C *,bxInstruction_c *);

  BX_SMF_FORCE void CPUID( BX_CPU_C *,bxInstruction_c *);
  BX_SMF_FORCE void LOADALL( BX_CPU_C *,bxInstruction_c *);
  BX_SMF_FORCE void CMOV_GwEGw( BX_CPU_C *,bxInstruction_c *);
  BX_SMF_FORCE void CMOV_GwEEw( BX_CPU_C *,bxInstruction_c *);
  BX_SMF_FORCE void CMOV_GdEGd( BX_CPU_C *,bxInstruction_c *);
  BX_SMF_FORCE void CMOV_GdEEd( BX_CPU_C *,bxInstruction_c *);

  BX_SMF_FORCE void NOP( BX_CPU_C *,bxInstruction_c *);
  BX_SMF_FORCE void PUSH_RX( BX_CPU_C *,bxInstruction_c *);
  BX_SMF_FORCE void POP_RX( BX_CPU_C *,bxInstruction_c *);
  BX_SMF_FORCE void PUSH_ERX( BX_CPU_C *,bxInstruction_c *);
  BX_SMF_FORCE void POP_ERX( BX_CPU_C *,bxInstruction_c *);

  BX_SMF_FORCE void PUSH_EGw( BX_CPU_C *,bxInstruction_c *);
  BX_SMF_FORCE void PUSH_EEw( BX_CPU_C *,bxInstruction_c *);
  BX_SMF_FORCE void PUSH_EGd( BX_CPU_C *,bxInstruction_c *);
  BX_SMF_FORCE void PUSH_EEd( BX_CPU_C *,bxInstruction_c *);
  BX_SMF_FORCE void POP_EGw( BX_CPU_C *,bxInstruction_c *);
  BX_SMF_FORCE void POP_EEw( BX_CPU_C *,bxInstruction_c *);
  BX_SMF_FORCE void POP_EGd( BX_CPU_C *,bxInstruction_c *);
  BX_SMF_FORCE void POP_EEd( BX_CPU_C *,bxInstruction_c *);

  // mch added
  BX_SMF_FORCE void INVLPG( BX_CPU_C *,bxInstruction_c *);
  BX_SMF void wait_for_interrupt();
  BX_SMF_FORCE void RSM( BX_CPU_C *,bxInstruction_c *);

  BX_SMF_FORCE void WRMSR( BX_CPU_C *,bxInstruction_c *);
  BX_SMF_FORCE void RDTSC( BX_CPU_C *,bxInstruction_c *);
  BX_SMF_FORCE void RDMSR( BX_CPU_C *,bxInstruction_c *);
  BX_SMF void SetCR0(Bit32u val_32);
  BX_SMF void dynamic_translate(void);
  BX_SMF void dynamic_init(void);

  /////////// FetchDecode
  BX_SMF unsigned fetchDecode(Bit8u *, bxInstruction_c *, unsigned);
  BX_SMF_FORCE void UndefinedOpcode( BX_CPU_C *,bxInstruction_c *);
  BX_SMF_FORCE void BxError( BX_CPU_C *,bxInstruction_c *);
  BX_SMF_FORCE void BxResolveError( BX_CPU_C *,bxInstruction_c *);

  BX_SMF_FORCE void Resolve16Mod0Rm0(BX_CPU_C * , bxInstruction_c * );
  BX_SMF_FORCE void Resolve16Mod0Rm1(BX_CPU_C * , bxInstruction_c * );
  BX_SMF_FORCE void Resolve16Mod0Rm2(BX_CPU_C * , bxInstruction_c * );
  BX_SMF_FORCE void Resolve16Mod0Rm3(BX_CPU_C * , bxInstruction_c * );
  BX_SMF_FORCE void Resolve16Mod0Rm4(BX_CPU_C * , bxInstruction_c * );
  BX_SMF_FORCE void Resolve16Mod0Rm5(BX_CPU_C * , bxInstruction_c * );
  BX_SMF_FORCE void Resolve16Mod0Rm6(BX_CPU_C * , bxInstruction_c * );
  BX_SMF_FORCE void Resolve16Mod0Rm7(BX_CPU_C * , bxInstruction_c * );

  BX_SMF_FORCE void Resolve16Mod1or2Rm0(BX_CPU_C * , bxInstruction_c * );
  BX_SMF_FORCE void Resolve16Mod1or2Rm1(BX_CPU_C * , bxInstruction_c * );
  BX_SMF_FORCE void Resolve16Mod1or2Rm2(BX_CPU_C * , bxInstruction_c * );
  BX_SMF_FORCE void Resolve16Mod1or2Rm3(BX_CPU_C * , bxInstruction_c * );
  BX_SMF_FORCE void Resolve16Mod1or2Rm4(BX_CPU_C * , bxInstruction_c * );
  BX_SMF_FORCE void Resolve16Mod1or2Rm5(BX_CPU_C * , bxInstruction_c * );
  BX_SMF_FORCE void Resolve16Mod1or2Rm6(BX_CPU_C * , bxInstruction_c * );
  BX_SMF_FORCE void Resolve16Mod1or2Rm7(BX_CPU_C * , bxInstruction_c * );

  BX_SMF_FORCE void Resolve32Mod0Rm0(BX_CPU_C * , bxInstruction_c * );
  BX_SMF_FORCE void Resolve32Mod0Rm1(BX_CPU_C * , bxInstruction_c * );
  BX_SMF_FORCE void Resolve32Mod0Rm2(BX_CPU_C * , bxInstruction_c * );
  BX_SMF_FORCE void Resolve32Mod0Rm3(BX_CPU_C * , bxInstruction_c * );
  BX_SMF_FORCE void Resolve32Mod0Rm4(BX_CPU_C * , bxInstruction_c * );
  BX_SMF_FORCE void Resolve32Mod0Rm5(BX_CPU_C * , bxInstruction_c * );
  BX_SMF_FORCE void Resolve32Mod0Rm6(BX_CPU_C * , bxInstruction_c * );
  BX_SMF_FORCE void Resolve32Mod0Rm7(BX_CPU_C * , bxInstruction_c * );

  BX_SMF_FORCE void Resolve32Mod1or2Rm0(BX_CPU_C * , bxInstruction_c * );
  BX_SMF_FORCE void Resolve32Mod1or2Rm1(BX_CPU_C * , bxInstruction_c * );
  BX_SMF_FORCE void Resolve32Mod1or2Rm2(BX_CPU_C * , bxInstruction_c * );
  BX_SMF_FORCE void Resolve32Mod1or2Rm3(BX_CPU_C * , bxInstruction_c * );
  BX_SMF_FORCE void Resolve32Mod1or2Rm4(BX_CPU_C * , bxInstruction_c * );
  BX_SMF_FORCE void Resolve32Mod1or2Rm5(BX_CPU_C * , bxInstruction_c * );
  BX_SMF_FORCE void Resolve32Mod1or2Rm6(BX_CPU_C * , bxInstruction_c * );
  BX_SMF_FORCE void Resolve32Mod1or2Rm7(BX_CPU_C * , bxInstruction_c * );

  BX_SMF_FORCE void Resolve32Mod1or2EffectAddress_sib0x00(BX_CPU_C * , bxInstruction_c * );
  BX_SMF_FORCE void Resolve32Mod1or2EffectAddress_sib0x01(BX_CPU_C * , bxInstruction_c * );
  BX_SMF_FORCE void Resolve32Mod1or2EffectAddress_sib0x02(BX_CPU_C * , bxInstruction_c * );
  BX_SMF_FORCE void Resolve32Mod1or2EffectAddress_sib0x03(BX_CPU_C * , bxInstruction_c * );
  BX_SMF_FORCE void Resolve32Mod1or2EffectAddress_sib0x04(BX_CPU_C * , bxInstruction_c * );
  BX_SMF_FORCE void Resolve32Mod1or2EffectAddress_sib0x05(BX_CPU_C * , bxInstruction_c * );
  BX_SMF_FORCE void Resolve32Mod1or2EffectAddress_sib0x06(BX_CPU_C * , bxInstruction_c * );
  BX_SMF_FORCE void Resolve32Mod1or2EffectAddress_sib0x07(BX_CPU_C * , bxInstruction_c * );
  BX_SMF_FORCE void Resolve32Mod1or2EffectAddress_sib0x08(BX_CPU_C * , bxInstruction_c * );
  BX_SMF_FORCE void Resolve32Mod1or2EffectAddress_sib0x09(BX_CPU_C * , bxInstruction_c * );
  BX_SMF_FORCE void Resolve32Mod1or2EffectAddress_sib0x0a(BX_CPU_C * , bxInstruction_c * );
  BX_SMF_FORCE void Resolve32Mod1or2EffectAddress_sib0x0b(BX_CPU_C * , bxInstruction_c * );
  BX_SMF_FORCE void Resolve32Mod1or2EffectAddress_sib0x0c(BX_CPU_C * , bxInstruction_c * );
  BX_SMF_FORCE void Resolve32Mod1or2EffectAddress_sib0x0d(BX_CPU_C * , bxInstruction_c * );
  BX_SMF_FORCE void Resolve32Mod1or2EffectAddress_sib0x0e(BX_CPU_C * , bxInstruction_c * );
  BX_SMF_FORCE void Resolve32Mod1or2EffectAddress_sib0x0f(BX_CPU_C * , bxInstruction_c * );
  BX_SMF_FORCE void Resolve32Mod1or2EffectAddress_sib0x10(BX_CPU_C * , bxInstruction_c * );
  BX_SMF_FORCE void Resolve32Mod1or2EffectAddress_sib0x11(BX_CPU_C * , bxInstruction_c * );
  BX_SMF_FORCE void Resolve32Mod1or2EffectAddress_sib0x12(BX_CPU_C * , bxInstruction_c * );
  BX_SMF_FORCE void Resolve32Mod1or2EffectAddress_sib0x13(BX_CPU_C * , bxInstruction_c * );
  BX_SMF_FORCE void Resolve32Mod1or2EffectAddress_sib0x14(BX_CPU_C * , bxInstruction_c * );
  BX_SMF_FORCE void Resolve32Mod1or2EffectAddress_sib0x15(BX_CPU_C * , bxInstruction_c * );
  BX_SMF_FORCE void Resolve32Mod1or2EffectAddress_sib0x16(BX_CPU_C * , bxInstruction_c * );
  BX_SMF_FORCE void Resolve32Mod1or2EffectAddress_sib0x17(BX_CPU_C * , bxInstruction_c * );
  BX_SMF_FORCE void Resolve32Mod1or2EffectAddress_sib0x18(BX_CPU_C * , bxInstruction_c * );
  BX_SMF_FORCE void Resolve32Mod1or2EffectAddress_sib0x19(BX_CPU_C * , bxInstruction_c * );
  BX_SMF_FORCE void Resolve32Mod1or2EffectAddress_sib0x1a(BX_CPU_C * , bxInstruction_c * );
  BX_SMF_FORCE void Resolve32Mod1or2EffectAddress_sib0x1b(BX_CPU_C * , bxInstruction_c * );
  BX_SMF_FORCE void Resolve32Mod1or2EffectAddress_sib0x1c(BX_CPU_C * , bxInstruction_c * );
  BX_SMF_FORCE void Resolve32Mod1or2EffectAddress_sib0x1d(BX_CPU_C * , bxInstruction_c * );
  BX_SMF_FORCE void Resolve32Mod1or2EffectAddress_sib0x1e(BX_CPU_C * , bxInstruction_c * );
  BX_SMF_FORCE void Resolve32Mod1or2EffectAddress_sib0x1f(BX_CPU_C * , bxInstruction_c * );
  BX_SMF_FORCE void Resolve32Mod1or2EffectAddress_sib0x20(BX_CPU_C * , bxInstruction_c * );
  BX_SMF_FORCE void Resolve32Mod1or2EffectAddress_sib0x21(BX_CPU_C * , bxInstruction_c * );
  BX_SMF_FORCE void Resolve32Mod1or2EffectAddress_sib0x22(BX_CPU_C * , bxInstruction_c * );
  BX_SMF_FORCE void Resolve32Mod1or2EffectAddress_sib0x23(BX_CPU_C * , bxInstruction_c * );
  BX_SMF_FORCE void Resolve32Mod1or2EffectAddress_sib0x24(BX_CPU_C * , bxInstruction_c * );
  BX_SMF_FORCE void Resolve32Mod1or2EffectAddress_sib0x25(BX_CPU_C * , bxInstruction_c * );
  BX_SMF_FORCE void Resolve32Mod1or2EffectAddress_sib0x26(BX_CPU_C * , bxInstruction_c * );
  BX_SMF_FORCE void Resolve32Mod1or2EffectAddress_sib0x27(BX_CPU_C * , bxInstruction_c * );
  BX_SMF_FORCE void Resolve32Mod1or2EffectAddress_sib0x28(BX_CPU_C * , bxInstruction_c * );
  BX_SMF_FORCE void Resolve32Mod1or2EffectAddress_sib0x29(BX_CPU_C * , bxInstruction_c * );
  BX_SMF_FORCE void Resolve32Mod1or2EffectAddress_sib0x2a(BX_CPU_C * , bxInstruction_c * );
  BX_SMF_FORCE void Resolve32Mod1or2EffectAddress_sib0x2b(BX_CPU_C * , bxInstruction_c * );
  BX_SMF_FORCE void Resolve32Mod1or2EffectAddress_sib0x2c(BX_CPU_C * , bxInstruction_c * );
  BX_SMF_FORCE void Resolve32Mod1or2EffectAddress_sib0x2d(BX_CPU_C * , bxInstruction_c * );
  BX_SMF_FORCE void Resolve32Mod1or2EffectAddress_sib0x2e(BX_CPU_C * , bxInstruction_c * );
  BX_SMF_FORCE void Resolve32Mod1or2EffectAddress_sib0x2f(BX_CPU_C * , bxInstruction_c * );
  BX_SMF_FORCE void Resolve32Mod1or2EffectAddress_sib0x30(BX_CPU_C * , bxInstruction_c * );
  BX_SMF_FORCE void Resolve32Mod1or2EffectAddress_sib0x31(BX_CPU_C * , bxInstruction_c * );
  BX_SMF_FORCE void Resolve32Mod1or2EffectAddress_sib0x32(BX_CPU_C * , bxInstruction_c * );
  BX_SMF_FORCE void Resolve32Mod1or2EffectAddress_sib0x33(BX_CPU_C * , bxInstruction_c * );
  BX_SMF_FORCE void Resolve32Mod1or2EffectAddress_sib0x34(BX_CPU_C * , bxInstruction_c * );
  BX_SMF_FORCE void Resolve32Mod1or2EffectAddress_sib0x35(BX_CPU_C * , bxInstruction_c * );
  BX_SMF_FORCE void Resolve32Mod1or2EffectAddress_sib0x36(BX_CPU_C * , bxInstruction_c * );
  BX_SMF_FORCE void Resolve32Mod1or2EffectAddress_sib0x37(BX_CPU_C * , bxInstruction_c * );
  BX_SMF_FORCE void Resolve32Mod1or2EffectAddress_sib0x38(BX_CPU_C * , bxInstruction_c * );
  BX_SMF_FORCE void Resolve32Mod1or2EffectAddress_sib0x39(BX_CPU_C * , bxInstruction_c * );
  BX_SMF_FORCE void Resolve32Mod1or2EffectAddress_sib0x3a(BX_CPU_C * , bxInstruction_c * );
  BX_SMF_FORCE void Resolve32Mod1or2EffectAddress_sib0x3b(BX_CPU_C * , bxInstruction_c * );
  BX_SMF_FORCE void Resolve32Mod1or2EffectAddress_sib0x3c(BX_CPU_C * , bxInstruction_c * );
  BX_SMF_FORCE void Resolve32Mod1or2EffectAddress_sib0x3d(BX_CPU_C * , bxInstruction_c * );
  BX_SMF_FORCE void Resolve32Mod1or2EffectAddress_sib0x3e(BX_CPU_C * , bxInstruction_c * );
  BX_SMF_FORCE void Resolve32Mod1or2EffectAddress_sib0x3f(BX_CPU_C * , bxInstruction_c * );
  BX_SMF_FORCE void Resolve32Mod1or2EffectAddress_sib0x40(BX_CPU_C * , bxInstruction_c * );
  BX_SMF_FORCE void Resolve32Mod1or2EffectAddress_sib0x41(BX_CPU_C * , bxInstruction_c * );
  BX_SMF_FORCE void Resolve32Mod1or2EffectAddress_sib0x42(BX_CPU_C * , bxInstruction_c * );
  BX_SMF_FORCE void Resolve32Mod1or2EffectAddress_sib0x43(BX_CPU_C * , bxInstruction_c * );
  BX_SMF_FORCE void Resolve32Mod1or2EffectAddress_sib0x44(BX_CPU_C * , bxInstruction_c * );
  BX_SMF_FORCE void Resolve32Mod1or2EffectAddress_sib0x45(BX_CPU_C * , bxInstruction_c * );
  BX_SMF_FORCE void Resolve32Mod1or2EffectAddress_sib0x46(BX_CPU_C * , bxInstruction_c * );
  BX_SMF_FORCE void Resolve32Mod1or2EffectAddress_sib0x47(BX_CPU_C * , bxInstruction_c * );
  BX_SMF_FORCE void Resolve32Mod1or2EffectAddress_sib0x48(BX_CPU_C * , bxInstruction_c * );
  BX_SMF_FORCE void Resolve32Mod1or2EffectAddress_sib0x49(BX_CPU_C * , bxInstruction_c * );
  BX_SMF_FORCE void Resolve32Mod1or2EffectAddress_sib0x4a(BX_CPU_C * , bxInstruction_c * );
  BX_SMF_FORCE void Resolve32Mod1or2EffectAddress_sib0x4b(BX_CPU_C * , bxInstruction_c * );
  BX_SMF_FORCE void Resolve32Mod1or2EffectAddress_sib0x4c(BX_CPU_C * , bxInstruction_c * );
  BX_SMF_FORCE void Resolve32Mod1or2EffectAddress_sib0x4d(BX_CPU_C * , bxInstruction_c * );
  BX_SMF_FORCE void Resolve32Mod1or2EffectAddress_sib0x4e(BX_CPU_C * , bxInstruction_c * );
  BX_SMF_FORCE void Resolve32Mod1or2EffectAddress_sib0x4f(BX_CPU_C * , bxInstruction_c * );
  BX_SMF_FORCE void Resolve32Mod1or2EffectAddress_sib0x50(BX_CPU_C * , bxInstruction_c * );
  BX_SMF_FORCE void Resolve32Mod1or2EffectAddress_sib0x51(BX_CPU_C * , bxInstruction_c * );
  BX_SMF_FORCE void Resolve32Mod1or2EffectAddress_sib0x52(BX_CPU_C * , bxInstruction_c * );
  BX_SMF_FORCE void Resolve32Mod1or2EffectAddress_sib0x53(BX_CPU_C * , bxInstruction_c * );
  BX_SMF_FORCE void Resolve32Mod1or2EffectAddress_sib0x54(BX_CPU_C * , bxInstruction_c * );
  BX_SMF_FORCE void Resolve32Mod1or2EffectAddress_sib0x55(BX_CPU_C * , bxInstruction_c * );
  BX_SMF_FORCE void Resolve32Mod1or2EffectAddress_sib0x56(BX_CPU_C * , bxInstruction_c * );
  BX_SMF_FORCE void Resolve32Mod1or2EffectAddress_sib0x57(BX_CPU_C * , bxInstruction_c * );
  BX_SMF_FORCE void Resolve32Mod1or2EffectAddress_sib0x58(BX_CPU_C * , bxInstruction_c * );
  BX_SMF_FORCE void Resolve32Mod1or2EffectAddress_sib0x59(BX_CPU_C * , bxInstruction_c * );
  BX_SMF_FORCE void Resolve32Mod1or2EffectAddress_sib0x5a(BX_CPU_C * , bxInstruction_c * );
  BX_SMF_FORCE void Resolve32Mod1or2EffectAddress_sib0x5b(BX_CPU_C * , bxInstruction_c * );
  BX_SMF_FORCE void Resolve32Mod1or2EffectAddress_sib0x5c(BX_CPU_C * , bxInstruction_c * );
  BX_SMF_FORCE void Resolve32Mod1or2EffectAddress_sib0x5d(BX_CPU_C * , bxInstruction_c * );
  BX_SMF_FORCE void Resolve32Mod1or2EffectAddress_sib0x5e(BX_CPU_C * , bxInstruction_c * );
  BX_SMF_FORCE void Resolve32Mod1or2EffectAddress_sib0x5f(BX_CPU_C * , bxInstruction_c * );
  BX_SMF_FORCE void Resolve32Mod1or2EffectAddress_sib0x60(BX_CPU_C * , bxInstruction_c * );
  BX_SMF_FORCE void Resolve32Mod1or2EffectAddress_sib0x61(BX_CPU_C * , bxInstruction_c * );
  BX_SMF_FORCE void Resolve32Mod1or2EffectAddress_sib0x62(BX_CPU_C * , bxInstruction_c * );
  BX_SMF_FORCE void Resolve32Mod1or2EffectAddress_sib0x63(BX_CPU_C * , bxInstruction_c * );
  BX_SMF_FORCE void Resolve32Mod1or2EffectAddress_sib0x64(BX_CPU_C * , bxInstruction_c * );
  BX_SMF_FORCE void Resolve32Mod1or2EffectAddress_sib0x65(BX_CPU_C * , bxInstruction_c * );
  BX_SMF_FORCE void Resolve32Mod1or2EffectAddress_sib0x66(BX_CPU_C * , bxInstruction_c * );
  BX_SMF_FORCE void Resolve32Mod1or2EffectAddress_sib0x67(BX_CPU_C * , bxInstruction_c * );
  BX_SMF_FORCE void Resolve32Mod1or2EffectAddress_sib0x68(BX_CPU_C * , bxInstruction_c * );
  BX_SMF_FORCE void Resolve32Mod1or2EffectAddress_sib0x69(BX_CPU_C * , bxInstruction_c * );
  BX_SMF_FORCE void Resolve32Mod1or2EffectAddress_sib0x6a(BX_CPU_C * , bxInstruction_c * );
  BX_SMF_FORCE void Resolve32Mod1or2EffectAddress_sib0x6b(BX_CPU_C * , bxInstruction_c * );
  BX_SMF_FORCE void Resolve32Mod1or2EffectAddress_sib0x6c(BX_CPU_C * , bxInstruction_c * );
  BX_SMF_FORCE void Resolve32Mod1or2EffectAddress_sib0x6d(BX_CPU_C * , bxInstruction_c * );
  BX_SMF_FORCE void Resolve32Mod1or2EffectAddress_sib0x6e(BX_CPU_C * , bxInstruction_c * );
  BX_SMF_FORCE void Resolve32Mod1or2EffectAddress_sib0x6f(BX_CPU_C * , bxInstruction_c * );
  BX_SMF_FORCE void Resolve32Mod1or2EffectAddress_sib0x70(BX_CPU_C * , bxInstruction_c * );
  BX_SMF_FORCE void Resolve32Mod1or2EffectAddress_sib0x71(BX_CPU_C * , bxInstruction_c * );
  BX_SMF_FORCE void Resolve32Mod1or2EffectAddress_sib0x72(BX_CPU_C * , bxInstruction_c * );
  BX_SMF_FORCE void Resolve32Mod1or2EffectAddress_sib0x73(BX_CPU_C * , bxInstruction_c * );
  BX_SMF_FORCE void Resolve32Mod1or2EffectAddress_sib0x74(BX_CPU_C * , bxInstruction_c * );
  BX_SMF_FORCE void Resolve32Mod1or2EffectAddress_sib0x75(BX_CPU_C * , bxInstruction_c * );
  BX_SMF_FORCE void Resolve32Mod1or2EffectAddress_sib0x76(BX_CPU_C * , bxInstruction_c * );
  BX_SMF_FORCE void Resolve32Mod1or2EffectAddress_sib0x77(BX_CPU_C * , bxInstruction_c * );
  BX_SMF_FORCE void Resolve32Mod1or2EffectAddress_sib0x78(BX_CPU_C * , bxInstruction_c * );
  BX_SMF_FORCE void Resolve32Mod1or2EffectAddress_sib0x79(BX_CPU_C * , bxInstruction_c * );
  BX_SMF_FORCE void Resolve32Mod1or2EffectAddress_sib0x7a(BX_CPU_C * , bxInstruction_c * );
  BX_SMF_FORCE void Resolve32Mod1or2EffectAddress_sib0x7b(BX_CPU_C * , bxInstruction_c * );
  BX_SMF_FORCE void Resolve32Mod1or2EffectAddress_sib0x7c(BX_CPU_C * , bxInstruction_c * );
  BX_SMF_FORCE void Resolve32Mod1or2EffectAddress_sib0x7d(BX_CPU_C * , bxInstruction_c * );
  BX_SMF_FORCE void Resolve32Mod1or2EffectAddress_sib0x7e(BX_CPU_C * , bxInstruction_c * );
  BX_SMF_FORCE void Resolve32Mod1or2EffectAddress_sib0x7f(BX_CPU_C * , bxInstruction_c * );
  BX_SMF_FORCE void Resolve32Mod1or2EffectAddress_sib0x80(BX_CPU_C * , bxInstruction_c * );
  BX_SMF_FORCE void Resolve32Mod1or2EffectAddress_sib0x81(BX_CPU_C * , bxInstruction_c * );
  BX_SMF_FORCE void Resolve32Mod1or2EffectAddress_sib0x82(BX_CPU_C * , bxInstruction_c * );
  BX_SMF_FORCE void Resolve32Mod1or2EffectAddress_sib0x83(BX_CPU_C * , bxInstruction_c * );
  BX_SMF_FORCE void Resolve32Mod1or2EffectAddress_sib0x84(BX_CPU_C * , bxInstruction_c * );
  BX_SMF_FORCE void Resolve32Mod1or2EffectAddress_sib0x85(BX_CPU_C * , bxInstruction_c * );
  BX_SMF_FORCE void Resolve32Mod1or2EffectAddress_sib0x86(BX_CPU_C * , bxInstruction_c * );
  BX_SMF_FORCE void Resolve32Mod1or2EffectAddress_sib0x87(BX_CPU_C * , bxInstruction_c * );
  BX_SMF_FORCE void Resolve32Mod1or2EffectAddress_sib0x88(BX_CPU_C * , bxInstruction_c * );
  BX_SMF_FORCE void Resolve32Mod1or2EffectAddress_sib0x89(BX_CPU_C * , bxInstruction_c * );
  BX_SMF_FORCE void Resolve32Mod1or2EffectAddress_sib0x8a(BX_CPU_C * , bxInstruction_c * );
  BX_SMF_FORCE void Resolve32Mod1or2EffectAddress_sib0x8b(BX_CPU_C * , bxInstruction_c * );
  BX_SMF_FORCE void Resolve32Mod1or2EffectAddress_sib0x8c(BX_CPU_C * , bxInstruction_c * );
  BX_SMF_FORCE void Resolve32Mod1or2EffectAddress_sib0x8d(BX_CPU_C * , bxInstruction_c * );
  BX_SMF_FORCE void Resolve32Mod1or2EffectAddress_sib0x8e(BX_CPU_C * , bxInstruction_c * );
  BX_SMF_FORCE void Resolve32Mod1or2EffectAddress_sib0x8f(BX_CPU_C * , bxInstruction_c * );
  BX_SMF_FORCE void Resolve32Mod1or2EffectAddress_sib0x90(BX_CPU_C * , bxInstruction_c * );
  BX_SMF_FORCE void Resolve32Mod1or2EffectAddress_sib0x91(BX_CPU_C * , bxInstruction_c * );
  BX_SMF_FORCE void Resolve32Mod1or2EffectAddress_sib0x92(BX_CPU_C * , bxInstruction_c * );
  BX_SMF_FORCE void Resolve32Mod1or2EffectAddress_sib0x93(BX_CPU_C * , bxInstruction_c * );
  BX_SMF_FORCE void Resolve32Mod1or2EffectAddress_sib0x94(BX_CPU_C * , bxInstruction_c * );
  BX_SMF_FORCE void Resolve32Mod1or2EffectAddress_sib0x95(BX_CPU_C * , bxInstruction_c * );
  BX_SMF_FORCE void Resolve32Mod1or2EffectAddress_sib0x96(BX_CPU_C * , bxInstruction_c * );
  BX_SMF_FORCE void Resolve32Mod1or2EffectAddress_sib0x97(BX_CPU_C * , bxInstruction_c * );
  BX_SMF_FORCE void Resolve32Mod1or2EffectAddress_sib0x98(BX_CPU_C * , bxInstruction_c * );
  BX_SMF_FORCE void Resolve32Mod1or2EffectAddress_sib0x99(BX_CPU_C * , bxInstruction_c * );
  BX_SMF_FORCE void Resolve32Mod1or2EffectAddress_sib0x9a(BX_CPU_C * , bxInstruction_c * );
  BX_SMF_FORCE void Resolve32Mod1or2EffectAddress_sib0x9b(BX_CPU_C * , bxInstruction_c * );
  BX_SMF_FORCE void Resolve32Mod1or2EffectAddress_sib0x9c(BX_CPU_C * , bxInstruction_c * );
  BX_SMF_FORCE void Resolve32Mod1or2EffectAddress_sib0x9d(BX_CPU_C * , bxInstruction_c * );
  BX_SMF_FORCE void Resolve32Mod1or2EffectAddress_sib0x9e(BX_CPU_C * , bxInstruction_c * );
  BX_SMF_FORCE void Resolve32Mod1or2EffectAddress_sib0x9f(BX_CPU_C * , bxInstruction_c * );
  BX_SMF_FORCE void Resolve32Mod1or2EffectAddress_sib0xa0(BX_CPU_C * , bxInstruction_c * );
  BX_SMF_FORCE void Resolve32Mod1or2EffectAddress_sib0xa1(BX_CPU_C * , bxInstruction_c * );
  BX_SMF_FORCE void Resolve32Mod1or2EffectAddress_sib0xa2(BX_CPU_C * , bxInstruction_c * );
  BX_SMF_FORCE void Resolve32Mod1or2EffectAddress_sib0xa3(BX_CPU_C * , bxInstruction_c * );
  BX_SMF_FORCE void Resolve32Mod1or2EffectAddress_sib0xa4(BX_CPU_C * , bxInstruction_c * );
  BX_SMF_FORCE void Resolve32Mod1or2EffectAddress_sib0xa5(BX_CPU_C * , bxInstruction_c * );
  BX_SMF_FORCE void Resolve32Mod1or2EffectAddress_sib0xa6(BX_CPU_C * , bxInstruction_c * );
  BX_SMF_FORCE void Resolve32Mod1or2EffectAddress_sib0xa7(BX_CPU_C * , bxInstruction_c * );
  BX_SMF_FORCE void Resolve32Mod1or2EffectAddress_sib0xa8(BX_CPU_C * , bxInstruction_c * );
  BX_SMF_FORCE void Resolve32Mod1or2EffectAddress_sib0xa9(BX_CPU_C * , bxInstruction_c * );
  BX_SMF_FORCE void Resolve32Mod1or2EffectAddress_sib0xaa(BX_CPU_C * , bxInstruction_c * );
  BX_SMF_FORCE void Resolve32Mod1or2EffectAddress_sib0xab(BX_CPU_C * , bxInstruction_c * );
  BX_SMF_FORCE void Resolve32Mod1or2EffectAddress_sib0xac(BX_CPU_C * , bxInstruction_c * );
  BX_SMF_FORCE void Resolve32Mod1or2EffectAddress_sib0xad(BX_CPU_C * , bxInstruction_c * );
  BX_SMF_FORCE void Resolve32Mod1or2EffectAddress_sib0xae(BX_CPU_C * , bxInstruction_c * );
  BX_SMF_FORCE void Resolve32Mod1or2EffectAddress_sib0xaf(BX_CPU_C * , bxInstruction_c * );
  BX_SMF_FORCE void Resolve32Mod1or2EffectAddress_sib0xb0(BX_CPU_C * , bxInstruction_c * );
  BX_SMF_FORCE void Resolve32Mod1or2EffectAddress_sib0xb1(BX_CPU_C * , bxInstruction_c * );
  BX_SMF_FORCE void Resolve32Mod1or2EffectAddress_sib0xb2(BX_CPU_C * , bxInstruction_c * );
  BX_SMF_FORCE void Resolve32Mod1or2EffectAddress_sib0xb3(BX_CPU_C * , bxInstruction_c * );
  BX_SMF_FORCE void Resolve32Mod1or2EffectAddress_sib0xb4(BX_CPU_C * , bxInstruction_c * );
  BX_SMF_FORCE void Resolve32Mod1or2EffectAddress_sib0xb5(BX_CPU_C * , bxInstruction_c * );
  BX_SMF_FORCE void Resolve32Mod1or2EffectAddress_sib0xb6(BX_CPU_C * , bxInstruction_c * );
  BX_SMF_FORCE void Resolve32Mod1or2EffectAddress_sib0xb7(BX_CPU_C * , bxInstruction_c * );
  BX_SMF_FORCE void Resolve32Mod1or2EffectAddress_sib0xb8(BX_CPU_C * , bxInstruction_c * );
  BX_SMF_FORCE void Resolve32Mod1or2EffectAddress_sib0xb9(BX_CPU_C * , bxInstruction_c * );
  BX_SMF_FORCE void Resolve32Mod1or2EffectAddress_sib0xba(BX_CPU_C * , bxInstruction_c * );
  BX_SMF_FORCE void Resolve32Mod1or2EffectAddress_sib0xbb(BX_CPU_C * , bxInstruction_c * );
  BX_SMF_FORCE void Resolve32Mod1or2EffectAddress_sib0xbc(BX_CPU_C * , bxInstruction_c * );
  BX_SMF_FORCE void Resolve32Mod1or2EffectAddress_sib0xbd(BX_CPU_C * , bxInstruction_c * );
  BX_SMF_FORCE void Resolve32Mod1or2EffectAddress_sib0xbe(BX_CPU_C * , bxInstruction_c * );
  BX_SMF_FORCE void Resolve32Mod1or2EffectAddress_sib0xbf(BX_CPU_C * , bxInstruction_c * );
  BX_SMF_FORCE void Resolve32Mod1or2EffectAddress_sib0xc0(BX_CPU_C * , bxInstruction_c * );
  BX_SMF_FORCE void Resolve32Mod1or2EffectAddress_sib0xc1(BX_CPU_C * , bxInstruction_c * );
  BX_SMF_FORCE void Resolve32Mod1or2EffectAddress_sib0xc2(BX_CPU_C * , bxInstruction_c * );
  BX_SMF_FORCE void Resolve32Mod1or2EffectAddress_sib0xc3(BX_CPU_C * , bxInstruction_c * );
  BX_SMF_FORCE void Resolve32Mod1or2EffectAddress_sib0xc4(BX_CPU_C * , bxInstruction_c * );
  BX_SMF_FORCE void Resolve32Mod1or2EffectAddress_sib0xc5(BX_CPU_C * , bxInstruction_c * );
  BX_SMF_FORCE void Resolve32Mod1or2EffectAddress_sib0xc6(BX_CPU_C * , bxInstruction_c * );
  BX_SMF_FORCE void Resolve32Mod1or2EffectAddress_sib0xc7(BX_CPU_C * , bxInstruction_c * );
  BX_SMF_FORCE void Resolve32Mod1or2EffectAddress_sib0xc8(BX_CPU_C * , bxInstruction_c * );
  BX_SMF_FORCE void Resolve32Mod1or2EffectAddress_sib0xc9(BX_CPU_C * , bxInstruction_c * );
  BX_SMF_FORCE void Resolve32Mod1or2EffectAddress_sib0xca(BX_CPU_C * , bxInstruction_c * );
  BX_SMF_FORCE void Resolve32Mod1or2EffectAddress_sib0xcb(BX_CPU_C * , bxInstruction_c * );
  BX_SMF_FORCE void Resolve32Mod1or2EffectAddress_sib0xcc(BX_CPU_C * , bxInstruction_c * );
  BX_SMF_FORCE void Resolve32Mod1or2EffectAddress_sib0xcd(BX_CPU_C * , bxInstruction_c * );
  BX_SMF_FORCE void Resolve32Mod1or2EffectAddress_sib0xce(BX_CPU_C * , bxInstruction_c * );
  BX_SMF_FORCE void Resolve32Mod1or2EffectAddress_sib0xcf(BX_CPU_C * , bxInstruction_c * );
  BX_SMF_FORCE void Resolve32Mod1or2EffectAddress_sib0xd0(BX_CPU_C * , bxInstruction_c * );
  BX_SMF_FORCE void Resolve32Mod1or2EffectAddress_sib0xd1(BX_CPU_C * , bxInstruction_c * );
  BX_SMF_FORCE void Resolve32Mod1or2EffectAddress_sib0xd2(BX_CPU_C * , bxInstruction_c * );
  BX_SMF_FORCE void Resolve32Mod1or2EffectAddress_sib0xd3(BX_CPU_C * , bxInstruction_c * );
  BX_SMF_FORCE void Resolve32Mod1or2EffectAddress_sib0xd4(BX_CPU_C * , bxInstruction_c * );
  BX_SMF_FORCE void Resolve32Mod1or2EffectAddress_sib0xd5(BX_CPU_C * , bxInstruction_c * );
  BX_SMF_FORCE void Resolve32Mod1or2EffectAddress_sib0xd6(BX_CPU_C * , bxInstruction_c * );
  BX_SMF_FORCE void Resolve32Mod1or2EffectAddress_sib0xd7(BX_CPU_C * , bxInstruction_c * );
  BX_SMF_FORCE void Resolve32Mod1or2EffectAddress_sib0xd8(BX_CPU_C * , bxInstruction_c * );
  BX_SMF_FORCE void Resolve32Mod1or2EffectAddress_sib0xd9(BX_CPU_C * , bxInstruction_c * );
  BX_SMF_FORCE void Resolve32Mod1or2EffectAddress_sib0xda(BX_CPU_C * , bxInstruction_c * );
  BX_SMF_FORCE void Resolve32Mod1or2EffectAddress_sib0xdb(BX_CPU_C * , bxInstruction_c * );
  BX_SMF_FORCE void Resolve32Mod1or2EffectAddress_sib0xdc(BX_CPU_C * , bxInstruction_c * );
  BX_SMF_FORCE void Resolve32Mod1or2EffectAddress_sib0xdd(BX_CPU_C * , bxInstruction_c * );
  BX_SMF_FORCE void Resolve32Mod1or2EffectAddress_sib0xde(BX_CPU_C * , bxInstruction_c * );
  BX_SMF_FORCE void Resolve32Mod1or2EffectAddress_sib0xdf(BX_CPU_C * , bxInstruction_c * );
  BX_SMF_FORCE void Resolve32Mod1or2EffectAddress_sib0xe0(BX_CPU_C * , bxInstruction_c * );
  BX_SMF_FORCE void Resolve32Mod1or2EffectAddress_sib0xe1(BX_CPU_C * , bxInstruction_c * );
  BX_SMF_FORCE void Resolve32Mod1or2EffectAddress_sib0xe2(BX_CPU_C * , bxInstruction_c * );
  BX_SMF_FORCE void Resolve32Mod1or2EffectAddress_sib0xe3(BX_CPU_C * , bxInstruction_c * );
  BX_SMF_FORCE void Resolve32Mod1or2EffectAddress_sib0xe4(BX_CPU_C * , bxInstruction_c * );
  BX_SMF_FORCE void Resolve32Mod1or2EffectAddress_sib0xe5(BX_CPU_C * , bxInstruction_c * );
  BX_SMF_FORCE void Resolve32Mod1or2EffectAddress_sib0xe6(BX_CPU_C * , bxInstruction_c * );
  BX_SMF_FORCE void Resolve32Mod1or2EffectAddress_sib0xe7(BX_CPU_C * , bxInstruction_c * );
  BX_SMF_FORCE void Resolve32Mod1or2EffectAddress_sib0xe8(BX_CPU_C * , bxInstruction_c * );
  BX_SMF_FORCE void Resolve32Mod1or2EffectAddress_sib0xe9(BX_CPU_C * , bxInstruction_c * );
  BX_SMF_FORCE void Resolve32Mod1or2EffectAddress_sib0xea(BX_CPU_C * , bxInstruction_c * );
  BX_SMF_FORCE void Resolve32Mod1or2EffectAddress_sib0xeb(BX_CPU_C * , bxInstruction_c * );
  BX_SMF_FORCE void Resolve32Mod1or2EffectAddress_sib0xec(BX_CPU_C * , bxInstruction_c * );
  BX_SMF_FORCE void Resolve32Mod1or2EffectAddress_sib0xed(BX_CPU_C * , bxInstruction_c * );
  BX_SMF_FORCE void Resolve32Mod1or2EffectAddress_sib0xee(BX_CPU_C * , bxInstruction_c * );
  BX_SMF_FORCE void Resolve32Mod1or2EffectAddress_sib0xef(BX_CPU_C * , bxInstruction_c * );
  BX_SMF_FORCE void Resolve32Mod1or2EffectAddress_sib0xf0(BX_CPU_C * , bxInstruction_c * );
  BX_SMF_FORCE void Resolve32Mod1or2EffectAddress_sib0xf1(BX_CPU_C * , bxInstruction_c * );
  BX_SMF_FORCE void Resolve32Mod1or2EffectAddress_sib0xf2(BX_CPU_C * , bxInstruction_c * );
  BX_SMF_FORCE void Resolve32Mod1or2EffectAddress_sib0xf3(BX_CPU_C * , bxInstruction_c * );
  BX_SMF_FORCE void Resolve32Mod1or2EffectAddress_sib0xf4(BX_CPU_C * , bxInstruction_c * );
  BX_SMF_FORCE void Resolve32Mod1or2EffectAddress_sib0xf5(BX_CPU_C * , bxInstruction_c * );
  BX_SMF_FORCE void Resolve32Mod1or2EffectAddress_sib0xf6(BX_CPU_C * , bxInstruction_c * );
  BX_SMF_FORCE void Resolve32Mod1or2EffectAddress_sib0xf7(BX_CPU_C * , bxInstruction_c * );
  BX_SMF_FORCE void Resolve32Mod1or2EffectAddress_sib0xf8(BX_CPU_C * , bxInstruction_c * );
  BX_SMF_FORCE void Resolve32Mod1or2EffectAddress_sib0xf9(BX_CPU_C * , bxInstruction_c * );
  BX_SMF_FORCE void Resolve32Mod1or2EffectAddress_sib0xfa(BX_CPU_C * , bxInstruction_c * );
  BX_SMF_FORCE void Resolve32Mod1or2EffectAddress_sib0xfb(BX_CPU_C * , bxInstruction_c * );
  BX_SMF_FORCE void Resolve32Mod1or2EffectAddress_sib0xfc(BX_CPU_C * , bxInstruction_c * );
  BX_SMF_FORCE void Resolve32Mod1or2EffectAddress_sib0xfd(BX_CPU_C * , bxInstruction_c * );
  BX_SMF_FORCE void Resolve32Mod1or2EffectAddress_sib0xfe(BX_CPU_C * , bxInstruction_c * );
  BX_SMF_FORCE void Resolve32Mod1or2EffectAddress_sib0xff(BX_CPU_C * , bxInstruction_c * );

  BX_SMF_FORCE void Resolve32Mod0EffectAddress_sib0x00(BX_CPU_C * , bxInstruction_c * );
  BX_SMF_FORCE void Resolve32Mod0EffectAddress_sib0x01(BX_CPU_C * , bxInstruction_c * );
  BX_SMF_FORCE void Resolve32Mod0EffectAddress_sib0x02(BX_CPU_C * , bxInstruction_c * );
  BX_SMF_FORCE void Resolve32Mod0EffectAddress_sib0x03(BX_CPU_C * , bxInstruction_c * );
  BX_SMF_FORCE void Resolve32Mod0EffectAddress_sib0x04(BX_CPU_C * , bxInstruction_c * );
  BX_SMF_FORCE void Resolve32Mod0EffectAddress_sib0x05(BX_CPU_C * , bxInstruction_c * );
  BX_SMF_FORCE void Resolve32Mod0EffectAddress_sib0x06(BX_CPU_C * , bxInstruction_c * );
  BX_SMF_FORCE void Resolve32Mod0EffectAddress_sib0x07(BX_CPU_C * , bxInstruction_c * );
  BX_SMF_FORCE void Resolve32Mod0EffectAddress_sib0x08(BX_CPU_C * , bxInstruction_c * );
  BX_SMF_FORCE void Resolve32Mod0EffectAddress_sib0x09(BX_CPU_C * , bxInstruction_c * );
  BX_SMF_FORCE void Resolve32Mod0EffectAddress_sib0x0a(BX_CPU_C * , bxInstruction_c * );
  BX_SMF_FORCE void Resolve32Mod0EffectAddress_sib0x0b(BX_CPU_C * , bxInstruction_c * );
  BX_SMF_FORCE void Resolve32Mod0EffectAddress_sib0x0c(BX_CPU_C * , bxInstruction_c * );
  BX_SMF_FORCE void Resolve32Mod0EffectAddress_sib0x0d(BX_CPU_C * , bxInstruction_c * );
  BX_SMF_FORCE void Resolve32Mod0EffectAddress_sib0x0e(BX_CPU_C * , bxInstruction_c * );
  BX_SMF_FORCE void Resolve32Mod0EffectAddress_sib0x0f(BX_CPU_C * , bxInstruction_c * );
  BX_SMF_FORCE void Resolve32Mod0EffectAddress_sib0x10(BX_CPU_C * , bxInstruction_c * );
  BX_SMF_FORCE void Resolve32Mod0EffectAddress_sib0x11(BX_CPU_C * , bxInstruction_c * );
  BX_SMF_FORCE void Resolve32Mod0EffectAddress_sib0x12(BX_CPU_C * , bxInstruction_c * );
  BX_SMF_FORCE void Resolve32Mod0EffectAddress_sib0x13(BX_CPU_C * , bxInstruction_c * );
  BX_SMF_FORCE void Resolve32Mod0EffectAddress_sib0x14(BX_CPU_C * , bxInstruction_c * );
  BX_SMF_FORCE void Resolve32Mod0EffectAddress_sib0x15(BX_CPU_C * , bxInstruction_c * );
  BX_SMF_FORCE void Resolve32Mod0EffectAddress_sib0x16(BX_CPU_C * , bxInstruction_c * );
  BX_SMF_FORCE void Resolve32Mod0EffectAddress_sib0x17(BX_CPU_C * , bxInstruction_c * );
  BX_SMF_FORCE void Resolve32Mod0EffectAddress_sib0x18(BX_CPU_C * , bxInstruction_c * );
  BX_SMF_FORCE void Resolve32Mod0EffectAddress_sib0x19(BX_CPU_C * , bxInstruction_c * );
  BX_SMF_FORCE void Resolve32Mod0EffectAddress_sib0x1a(BX_CPU_C * , bxInstruction_c * );
  BX_SMF_FORCE void Resolve32Mod0EffectAddress_sib0x1b(BX_CPU_C * , bxInstruction_c * );
  BX_SMF_FORCE void Resolve32Mod0EffectAddress_sib0x1c(BX_CPU_C * , bxInstruction_c * );
  BX_SMF_FORCE void Resolve32Mod0EffectAddress_sib0x1d(BX_CPU_C * , bxInstruction_c * );
  BX_SMF_FORCE void Resolve32Mod0EffectAddress_sib0x1e(BX_CPU_C * , bxInstruction_c * );
  BX_SMF_FORCE void Resolve32Mod0EffectAddress_sib0x1f(BX_CPU_C * , bxInstruction_c * );
  BX_SMF_FORCE void Resolve32Mod0EffectAddress_sib0x20(BX_CPU_C * , bxInstruction_c * );
  BX_SMF_FORCE void Resolve32Mod0EffectAddress_sib0x21(BX_CPU_C * , bxInstruction_c * );
  BX_SMF_FORCE void Resolve32Mod0EffectAddress_sib0x22(BX_CPU_C * , bxInstruction_c * );
  BX_SMF_FORCE void Resolve32Mod0EffectAddress_sib0x23(BX_CPU_C * , bxInstruction_c * );
  BX_SMF_FORCE void Resolve32Mod0EffectAddress_sib0x24(BX_CPU_C * , bxInstruction_c * );
  BX_SMF_FORCE void Resolve32Mod0EffectAddress_sib0x25(BX_CPU_C * , bxInstruction_c * );
  BX_SMF_FORCE void Resolve32Mod0EffectAddress_sib0x26(BX_CPU_C * , bxInstruction_c * );
  BX_SMF_FORCE void Resolve32Mod0EffectAddress_sib0x27(BX_CPU_C * , bxInstruction_c * );
  BX_SMF_FORCE void Resolve32Mod0EffectAddress_sib0x28(BX_CPU_C * , bxInstruction_c * );
  BX_SMF_FORCE void Resolve32Mod0EffectAddress_sib0x29(BX_CPU_C * , bxInstruction_c * );
  BX_SMF_FORCE void Resolve32Mod0EffectAddress_sib0x2a(BX_CPU_C * , bxInstruction_c * );
  BX_SMF_FORCE void Resolve32Mod0EffectAddress_sib0x2b(BX_CPU_C * , bxInstruction_c * );
  BX_SMF_FORCE void Resolve32Mod0EffectAddress_sib0x2c(BX_CPU_C * , bxInstruction_c * );
  BX_SMF_FORCE void Resolve32Mod0EffectAddress_sib0x2d(BX_CPU_C * , bxInstruction_c * );
  BX_SMF_FORCE void Resolve32Mod0EffectAddress_sib0x2e(BX_CPU_C * , bxInstruction_c * );
  BX_SMF_FORCE void Resolve32Mod0EffectAddress_sib0x2f(BX_CPU_C * , bxInstruction_c * );
  BX_SMF_FORCE void Resolve32Mod0EffectAddress_sib0x30(BX_CPU_C * , bxInstruction_c * );
  BX_SMF_FORCE void Resolve32Mod0EffectAddress_sib0x31(BX_CPU_C * , bxInstruction_c * );
  BX_SMF_FORCE void Resolve32Mod0EffectAddress_sib0x32(BX_CPU_C * , bxInstruction_c * );
  BX_SMF_FORCE void Resolve32Mod0EffectAddress_sib0x33(BX_CPU_C * , bxInstruction_c * );
  BX_SMF_FORCE void Resolve32Mod0EffectAddress_sib0x34(BX_CPU_C * , bxInstruction_c * );
  BX_SMF_FORCE void Resolve32Mod0EffectAddress_sib0x35(BX_CPU_C * , bxInstruction_c * );
  BX_SMF_FORCE void Resolve32Mod0EffectAddress_sib0x36(BX_CPU_C * , bxInstruction_c * );
  BX_SMF_FORCE void Resolve32Mod0EffectAddress_sib0x37(BX_CPU_C * , bxInstruction_c * );
  BX_SMF_FORCE void Resolve32Mod0EffectAddress_sib0x38(BX_CPU_C * , bxInstruction_c * );
  BX_SMF_FORCE void Resolve32Mod0EffectAddress_sib0x39(BX_CPU_C * , bxInstruction_c * );
  BX_SMF_FORCE void Resolve32Mod0EffectAddress_sib0x3a(BX_CPU_C * , bxInstruction_c * );
  BX_SMF_FORCE void Resolve32Mod0EffectAddress_sib0x3b(BX_CPU_C * , bxInstruction_c * );
  BX_SMF_FORCE void Resolve32Mod0EffectAddress_sib0x3c(BX_CPU_C * , bxInstruction_c * );
  BX_SMF_FORCE void Resolve32Mod0EffectAddress_sib0x3d(BX_CPU_C * , bxInstruction_c * );
  BX_SMF_FORCE void Resolve32Mod0EffectAddress_sib0x3e(BX_CPU_C * , bxInstruction_c * );
  BX_SMF_FORCE void Resolve32Mod0EffectAddress_sib0x3f(BX_CPU_C * , bxInstruction_c * );
  BX_SMF_FORCE void Resolve32Mod0EffectAddress_sib0x40(BX_CPU_C * , bxInstruction_c * );
  BX_SMF_FORCE void Resolve32Mod0EffectAddress_sib0x41(BX_CPU_C * , bxInstruction_c * );
  BX_SMF_FORCE void Resolve32Mod0EffectAddress_sib0x42(BX_CPU_C * , bxInstruction_c * );
  BX_SMF_FORCE void Resolve32Mod0EffectAddress_sib0x43(BX_CPU_C * , bxInstruction_c * );
  BX_SMF_FORCE void Resolve32Mod0EffectAddress_sib0x44(BX_CPU_C * , bxInstruction_c * );
  BX_SMF_FORCE void Resolve32Mod0EffectAddress_sib0x45(BX_CPU_C * , bxInstruction_c * );
  BX_SMF_FORCE void Resolve32Mod0EffectAddress_sib0x46(BX_CPU_C * , bxInstruction_c * );
  BX_SMF_FORCE void Resolve32Mod0EffectAddress_sib0x47(BX_CPU_C * , bxInstruction_c * );
  BX_SMF_FORCE void Resolve32Mod0EffectAddress_sib0x48(BX_CPU_C * , bxInstruction_c * );
  BX_SMF_FORCE void Resolve32Mod0EffectAddress_sib0x49(BX_CPU_C * , bxInstruction_c * );
  BX_SMF_FORCE void Resolve32Mod0EffectAddress_sib0x4a(BX_CPU_C * , bxInstruction_c * );
  BX_SMF_FORCE void Resolve32Mod0EffectAddress_sib0x4b(BX_CPU_C * , bxInstruction_c * );
  BX_SMF_FORCE void Resolve32Mod0EffectAddress_sib0x4c(BX_CPU_C * , bxInstruction_c * );
  BX_SMF_FORCE void Resolve32Mod0EffectAddress_sib0x4d(BX_CPU_C * , bxInstruction_c * );
  BX_SMF_FORCE void Resolve32Mod0EffectAddress_sib0x4e(BX_CPU_C * , bxInstruction_c * );
  BX_SMF_FORCE void Resolve32Mod0EffectAddress_sib0x4f(BX_CPU_C * , bxInstruction_c * );
  BX_SMF_FORCE void Resolve32Mod0EffectAddress_sib0x50(BX_CPU_C * , bxInstruction_c * );
  BX_SMF_FORCE void Resolve32Mod0EffectAddress_sib0x51(BX_CPU_C * , bxInstruction_c * );
  BX_SMF_FORCE void Resolve32Mod0EffectAddress_sib0x52(BX_CPU_C * , bxInstruction_c * );
  BX_SMF_FORCE void Resolve32Mod0EffectAddress_sib0x53(BX_CPU_C * , bxInstruction_c * );
  BX_SMF_FORCE void Resolve32Mod0EffectAddress_sib0x54(BX_CPU_C * , bxInstruction_c * );
  BX_SMF_FORCE void Resolve32Mod0EffectAddress_sib0x55(BX_CPU_C * , bxInstruction_c * );
  BX_SMF_FORCE void Resolve32Mod0EffectAddress_sib0x56(BX_CPU_C * , bxInstruction_c * );
  BX_SMF_FORCE void Resolve32Mod0EffectAddress_sib0x57(BX_CPU_C * , bxInstruction_c * );
  BX_SMF_FORCE void Resolve32Mod0EffectAddress_sib0x58(BX_CPU_C * , bxInstruction_c * );
  BX_SMF_FORCE void Resolve32Mod0EffectAddress_sib0x59(BX_CPU_C * , bxInstruction_c * );
  BX_SMF_FORCE void Resolve32Mod0EffectAddress_sib0x5a(BX_CPU_C * , bxInstruction_c * );
  BX_SMF_FORCE void Resolve32Mod0EffectAddress_sib0x5b(BX_CPU_C * , bxInstruction_c * );
  BX_SMF_FORCE void Resolve32Mod0EffectAddress_sib0x5c(BX_CPU_C * , bxInstruction_c * );
  BX_SMF_FORCE void Resolve32Mod0EffectAddress_sib0x5d(BX_CPU_C * , bxInstruction_c * );
  BX_SMF_FORCE void Resolve32Mod0EffectAddress_sib0x5e(BX_CPU_C * , bxInstruction_c * );
  BX_SMF_FORCE void Resolve32Mod0EffectAddress_sib0x5f(BX_CPU_C * , bxInstruction_c * );
  BX_SMF_FORCE void Resolve32Mod0EffectAddress_sib0x60(BX_CPU_C * , bxInstruction_c * );
  BX_SMF_FORCE void Resolve32Mod0EffectAddress_sib0x61(BX_CPU_C * , bxInstruction_c * );
  BX_SMF_FORCE void Resolve32Mod0EffectAddress_sib0x62(BX_CPU_C * , bxInstruction_c * );
  BX_SMF_FORCE void Resolve32Mod0EffectAddress_sib0x63(BX_CPU_C * , bxInstruction_c * );
  BX_SMF_FORCE void Resolve32Mod0EffectAddress_sib0x64(BX_CPU_C * , bxInstruction_c * );
  BX_SMF_FORCE void Resolve32Mod0EffectAddress_sib0x65(BX_CPU_C * , bxInstruction_c * );
  BX_SMF_FORCE void Resolve32Mod0EffectAddress_sib0x66(BX_CPU_C * , bxInstruction_c * );
  BX_SMF_FORCE void Resolve32Mod0EffectAddress_sib0x67(BX_CPU_C * , bxInstruction_c * );
  BX_SMF_FORCE void Resolve32Mod0EffectAddress_sib0x68(BX_CPU_C * , bxInstruction_c * );
  BX_SMF_FORCE void Resolve32Mod0EffectAddress_sib0x69(BX_CPU_C * , bxInstruction_c * );
  BX_SMF_FORCE void Resolve32Mod0EffectAddress_sib0x6a(BX_CPU_C * , bxInstruction_c * );
  BX_SMF_FORCE void Resolve32Mod0EffectAddress_sib0x6b(BX_CPU_C * , bxInstruction_c * );
  BX_SMF_FORCE void Resolve32Mod0EffectAddress_sib0x6c(BX_CPU_C * , bxInstruction_c * );
  BX_SMF_FORCE void Resolve32Mod0EffectAddress_sib0x6d(BX_CPU_C * , bxInstruction_c * );
  BX_SMF_FORCE void Resolve32Mod0EffectAddress_sib0x6e(BX_CPU_C * , bxInstruction_c * );
  BX_SMF_FORCE void Resolve32Mod0EffectAddress_sib0x6f(BX_CPU_C * , bxInstruction_c * );
  BX_SMF_FORCE void Resolve32Mod0EffectAddress_sib0x70(BX_CPU_C * , bxInstruction_c * );
  BX_SMF_FORCE void Resolve32Mod0EffectAddress_sib0x71(BX_CPU_C * , bxInstruction_c * );
  BX_SMF_FORCE void Resolve32Mod0EffectAddress_sib0x72(BX_CPU_C * , bxInstruction_c * );
  BX_SMF_FORCE void Resolve32Mod0EffectAddress_sib0x73(BX_CPU_C * , bxInstruction_c * );
  BX_SMF_FORCE void Resolve32Mod0EffectAddress_sib0x74(BX_CPU_C * , bxInstruction_c * );
  BX_SMF_FORCE void Resolve32Mod0EffectAddress_sib0x75(BX_CPU_C * , bxInstruction_c * );
  BX_SMF_FORCE void Resolve32Mod0EffectAddress_sib0x76(BX_CPU_C * , bxInstruction_c * );
  BX_SMF_FORCE void Resolve32Mod0EffectAddress_sib0x77(BX_CPU_C * , bxInstruction_c * );
  BX_SMF_FORCE void Resolve32Mod0EffectAddress_sib0x78(BX_CPU_C * , bxInstruction_c * );
  BX_SMF_FORCE void Resolve32Mod0EffectAddress_sib0x79(BX_CPU_C * , bxInstruction_c * );
  BX_SMF_FORCE void Resolve32Mod0EffectAddress_sib0x7a(BX_CPU_C * , bxInstruction_c * );
  BX_SMF_FORCE void Resolve32Mod0EffectAddress_sib0x7b(BX_CPU_C * , bxInstruction_c * );
  BX_SMF_FORCE void Resolve32Mod0EffectAddress_sib0x7c(BX_CPU_C * , bxInstruction_c * );
  BX_SMF_FORCE void Resolve32Mod0EffectAddress_sib0x7d(BX_CPU_C * , bxInstruction_c * );
  BX_SMF_FORCE void Resolve32Mod0EffectAddress_sib0x7e(BX_CPU_C * , bxInstruction_c * );
  BX_SMF_FORCE void Resolve32Mod0EffectAddress_sib0x7f(BX_CPU_C * , bxInstruction_c * );
  BX_SMF_FORCE void Resolve32Mod0EffectAddress_sib0x80(BX_CPU_C * , bxInstruction_c * );
  BX_SMF_FORCE void Resolve32Mod0EffectAddress_sib0x81(BX_CPU_C * , bxInstruction_c * );
  BX_SMF_FORCE void Resolve32Mod0EffectAddress_sib0x82(BX_CPU_C * , bxInstruction_c * );
  BX_SMF_FORCE void Resolve32Mod0EffectAddress_sib0x83(BX_CPU_C * , bxInstruction_c * );
  BX_SMF_FORCE void Resolve32Mod0EffectAddress_sib0x84(BX_CPU_C * , bxInstruction_c * );
  BX_SMF_FORCE void Resolve32Mod0EffectAddress_sib0x85(BX_CPU_C * , bxInstruction_c * );
  BX_SMF_FORCE void Resolve32Mod0EffectAddress_sib0x86(BX_CPU_C * , bxInstruction_c * );
  BX_SMF_FORCE void Resolve32Mod0EffectAddress_sib0x87(BX_CPU_C * , bxInstruction_c * );
  BX_SMF_FORCE void Resolve32Mod0EffectAddress_sib0x88(BX_CPU_C * , bxInstruction_c * );
  BX_SMF_FORCE void Resolve32Mod0EffectAddress_sib0x89(BX_CPU_C * , bxInstruction_c * );
  BX_SMF_FORCE void Resolve32Mod0EffectAddress_sib0x8a(BX_CPU_C * , bxInstruction_c * );
  BX_SMF_FORCE void Resolve32Mod0EffectAddress_sib0x8b(BX_CPU_C * , bxInstruction_c * );
  BX_SMF_FORCE void Resolve32Mod0EffectAddress_sib0x8c(BX_CPU_C * , bxInstruction_c * );
  BX_SMF_FORCE void Resolve32Mod0EffectAddress_sib0x8d(BX_CPU_C * , bxInstruction_c * );
  BX_SMF_FORCE void Resolve32Mod0EffectAddress_sib0x8e(BX_CPU_C * , bxInstruction_c * );
  BX_SMF_FORCE void Resolve32Mod0EffectAddress_sib0x8f(BX_CPU_C * , bxInstruction_c * );
  BX_SMF_FORCE void Resolve32Mod0EffectAddress_sib0x90(BX_CPU_C * , bxInstruction_c * );
  BX_SMF_FORCE void Resolve32Mod0EffectAddress_sib0x91(BX_CPU_C * , bxInstruction_c * );
  BX_SMF_FORCE void Resolve32Mod0EffectAddress_sib0x92(BX_CPU_C * , bxInstruction_c * );
  BX_SMF_FORCE void Resolve32Mod0EffectAddress_sib0x93(BX_CPU_C * , bxInstruction_c * );
  BX_SMF_FORCE void Resolve32Mod0EffectAddress_sib0x94(BX_CPU_C * , bxInstruction_c * );
  BX_SMF_FORCE void Resolve32Mod0EffectAddress_sib0x95(BX_CPU_C * , bxInstruction_c * );
  BX_SMF_FORCE void Resolve32Mod0EffectAddress_sib0x96(BX_CPU_C * , bxInstruction_c * );
  BX_SMF_FORCE void Resolve32Mod0EffectAddress_sib0x97(BX_CPU_C * , bxInstruction_c * );
  BX_SMF_FORCE void Resolve32Mod0EffectAddress_sib0x98(BX_CPU_C * , bxInstruction_c * );
  BX_SMF_FORCE void Resolve32Mod0EffectAddress_sib0x99(BX_CPU_C * , bxInstruction_c * );
  BX_SMF_FORCE void Resolve32Mod0EffectAddress_sib0x9a(BX_CPU_C * , bxInstruction_c * );
  BX_SMF_FORCE void Resolve32Mod0EffectAddress_sib0x9b(BX_CPU_C * , bxInstruction_c * );
  BX_SMF_FORCE void Resolve32Mod0EffectAddress_sib0x9c(BX_CPU_C * , bxInstruction_c * );
  BX_SMF_FORCE void Resolve32Mod0EffectAddress_sib0x9d(BX_CPU_C * , bxInstruction_c * );
  BX_SMF_FORCE void Resolve32Mod0EffectAddress_sib0x9e(BX_CPU_C * , bxInstruction_c * );
  BX_SMF_FORCE void Resolve32Mod0EffectAddress_sib0x9f(BX_CPU_C * , bxInstruction_c * );
  BX_SMF_FORCE void Resolve32Mod0EffectAddress_sib0xa0(BX_CPU_C * , bxInstruction_c * );
  BX_SMF_FORCE void Resolve32Mod0EffectAddress_sib0xa1(BX_CPU_C * , bxInstruction_c * );
  BX_SMF_FORCE void Resolve32Mod0EffectAddress_sib0xa2(BX_CPU_C * , bxInstruction_c * );
  BX_SMF_FORCE void Resolve32Mod0EffectAddress_sib0xa3(BX_CPU_C * , bxInstruction_c * );
  BX_SMF_FORCE void Resolve32Mod0EffectAddress_sib0xa4(BX_CPU_C * , bxInstruction_c * );
  BX_SMF_FORCE void Resolve32Mod0EffectAddress_sib0xa5(BX_CPU_C * , bxInstruction_c * );
  BX_SMF_FORCE void Resolve32Mod0EffectAddress_sib0xa6(BX_CPU_C * , bxInstruction_c * );
  BX_SMF_FORCE void Resolve32Mod0EffectAddress_sib0xa7(BX_CPU_C * , bxInstruction_c * );
  BX_SMF_FORCE void Resolve32Mod0EffectAddress_sib0xa8(BX_CPU_C * , bxInstruction_c * );
  BX_SMF_FORCE void Resolve32Mod0EffectAddress_sib0xa9(BX_CPU_C * , bxInstruction_c * );
  BX_SMF_FORCE void Resolve32Mod0EffectAddress_sib0xaa(BX_CPU_C * , bxInstruction_c * );
  BX_SMF_FORCE void Resolve32Mod0EffectAddress_sib0xab(BX_CPU_C * , bxInstruction_c * );
  BX_SMF_FORCE void Resolve32Mod0EffectAddress_sib0xac(BX_CPU_C * , bxInstruction_c * );
  BX_SMF_FORCE void Resolve32Mod0EffectAddress_sib0xad(BX_CPU_C * , bxInstruction_c * );
  BX_SMF_FORCE void Resolve32Mod0EffectAddress_sib0xae(BX_CPU_C * , bxInstruction_c * );
  BX_SMF_FORCE void Resolve32Mod0EffectAddress_sib0xaf(BX_CPU_C * , bxInstruction_c * );
  BX_SMF_FORCE void Resolve32Mod0EffectAddress_sib0xb0(BX_CPU_C * , bxInstruction_c * );
  BX_SMF_FORCE void Resolve32Mod0EffectAddress_sib0xb1(BX_CPU_C * , bxInstruction_c * );
  BX_SMF_FORCE void Resolve32Mod0EffectAddress_sib0xb2(BX_CPU_C * , bxInstruction_c * );
  BX_SMF_FORCE void Resolve32Mod0EffectAddress_sib0xb3(BX_CPU_C * , bxInstruction_c * );
  BX_SMF_FORCE void Resolve32Mod0EffectAddress_sib0xb4(BX_CPU_C * , bxInstruction_c * );
  BX_SMF_FORCE void Resolve32Mod0EffectAddress_sib0xb5(BX_CPU_C * , bxInstruction_c * );
  BX_SMF_FORCE void Resolve32Mod0EffectAddress_sib0xb6(BX_CPU_C * , bxInstruction_c * );
  BX_SMF_FORCE void Resolve32Mod0EffectAddress_sib0xb7(BX_CPU_C * , bxInstruction_c * );
  BX_SMF_FORCE void Resolve32Mod0EffectAddress_sib0xb8(BX_CPU_C * , bxInstruction_c * );
  BX_SMF_FORCE void Resolve32Mod0EffectAddress_sib0xb9(BX_CPU_C * , bxInstruction_c * );
  BX_SMF_FORCE void Resolve32Mod0EffectAddress_sib0xba(BX_CPU_C * , bxInstruction_c * );
  BX_SMF_FORCE void Resolve32Mod0EffectAddress_sib0xbb(BX_CPU_C * , bxInstruction_c * );
  BX_SMF_FORCE void Resolve32Mod0EffectAddress_sib0xbc(BX_CPU_C * , bxInstruction_c * );
  BX_SMF_FORCE void Resolve32Mod0EffectAddress_sib0xbd(BX_CPU_C * , bxInstruction_c * );
  BX_SMF_FORCE void Resolve32Mod0EffectAddress_sib0xbe(BX_CPU_C * , bxInstruction_c * );
  BX_SMF_FORCE void Resolve32Mod0EffectAddress_sib0xbf(BX_CPU_C * , bxInstruction_c * );
  BX_SMF_FORCE void Resolve32Mod0EffectAddress_sib0xc0(BX_CPU_C * , bxInstruction_c * );
  BX_SMF_FORCE void Resolve32Mod0EffectAddress_sib0xc1(BX_CPU_C * , bxInstruction_c * );
  BX_SMF_FORCE void Resolve32Mod0EffectAddress_sib0xc2(BX_CPU_C * , bxInstruction_c * );
  BX_SMF_FORCE void Resolve32Mod0EffectAddress_sib0xc3(BX_CPU_C * , bxInstruction_c * );
  BX_SMF_FORCE void Resolve32Mod0EffectAddress_sib0xc4(BX_CPU_C * , bxInstruction_c * );
  BX_SMF_FORCE void Resolve32Mod0EffectAddress_sib0xc5(BX_CPU_C * , bxInstruction_c * );
  BX_SMF_FORCE void Resolve32Mod0EffectAddress_sib0xc6(BX_CPU_C * , bxInstruction_c * );
  BX_SMF_FORCE void Resolve32Mod0EffectAddress_sib0xc7(BX_CPU_C * , bxInstruction_c * );
  BX_SMF_FORCE void Resolve32Mod0EffectAddress_sib0xc8(BX_CPU_C * , bxInstruction_c * );
  BX_SMF_FORCE void Resolve32Mod0EffectAddress_sib0xc9(BX_CPU_C * , bxInstruction_c * );
  BX_SMF_FORCE void Resolve32Mod0EffectAddress_sib0xca(BX_CPU_C * , bxInstruction_c * );
  BX_SMF_FORCE void Resolve32Mod0EffectAddress_sib0xcb(BX_CPU_C * , bxInstruction_c * );
  BX_SMF_FORCE void Resolve32Mod0EffectAddress_sib0xcc(BX_CPU_C * , bxInstruction_c * );
  BX_SMF_FORCE void Resolve32Mod0EffectAddress_sib0xcd(BX_CPU_C * , bxInstruction_c * );
  BX_SMF_FORCE void Resolve32Mod0EffectAddress_sib0xce(BX_CPU_C * , bxInstruction_c * );
  BX_SMF_FORCE void Resolve32Mod0EffectAddress_sib0xcf(BX_CPU_C * , bxInstruction_c * );
  BX_SMF_FORCE void Resolve32Mod0EffectAddress_sib0xd0(BX_CPU_C * , bxInstruction_c * );
  BX_SMF_FORCE void Resolve32Mod0EffectAddress_sib0xd1(BX_CPU_C * , bxInstruction_c * );
  BX_SMF_FORCE void Resolve32Mod0EffectAddress_sib0xd2(BX_CPU_C * , bxInstruction_c * );
  BX_SMF_FORCE void Resolve32Mod0EffectAddress_sib0xd3(BX_CPU_C * , bxInstruction_c * );
  BX_SMF_FORCE void Resolve32Mod0EffectAddress_sib0xd4(BX_CPU_C * , bxInstruction_c * );
  BX_SMF_FORCE void Resolve32Mod0EffectAddress_sib0xd5(BX_CPU_C * , bxInstruction_c * );
  BX_SMF_FORCE void Resolve32Mod0EffectAddress_sib0xd6(BX_CPU_C * , bxInstruction_c * );
  BX_SMF_FORCE void Resolve32Mod0EffectAddress_sib0xd7(BX_CPU_C * , bxInstruction_c * );
  BX_SMF_FORCE void Resolve32Mod0EffectAddress_sib0xd8(BX_CPU_C * , bxInstruction_c * );
  BX_SMF_FORCE void Resolve32Mod0EffectAddress_sib0xd9(BX_CPU_C * , bxInstruction_c * );
  BX_SMF_FORCE void Resolve32Mod0EffectAddress_sib0xda(BX_CPU_C * , bxInstruction_c * );
  BX_SMF_FORCE void Resolve32Mod0EffectAddress_sib0xdb(BX_CPU_C * , bxInstruction_c * );
  BX_SMF_FORCE void Resolve32Mod0EffectAddress_sib0xdc(BX_CPU_C * , bxInstruction_c * );
  BX_SMF_FORCE void Resolve32Mod0EffectAddress_sib0xdd(BX_CPU_C * , bxInstruction_c * );
  BX_SMF_FORCE void Resolve32Mod0EffectAddress_sib0xde(BX_CPU_C * , bxInstruction_c * );
  BX_SMF_FORCE void Resolve32Mod0EffectAddress_sib0xdf(BX_CPU_C * , bxInstruction_c * );
  BX_SMF_FORCE void Resolve32Mod0EffectAddress_sib0xe0(BX_CPU_C * , bxInstruction_c * );
  BX_SMF_FORCE void Resolve32Mod0EffectAddress_sib0xe1(BX_CPU_C * , bxInstruction_c * );
  BX_SMF_FORCE void Resolve32Mod0EffectAddress_sib0xe2(BX_CPU_C * , bxInstruction_c * );
  BX_SMF_FORCE void Resolve32Mod0EffectAddress_sib0xe3(BX_CPU_C * , bxInstruction_c * );
  BX_SMF_FORCE void Resolve32Mod0EffectAddress_sib0xe4(BX_CPU_C * , bxInstruction_c * );
  BX_SMF_FORCE void Resolve32Mod0EffectAddress_sib0xe5(BX_CPU_C * , bxInstruction_c * );
  BX_SMF_FORCE void Resolve32Mod0EffectAddress_sib0xe6(BX_CPU_C * , bxInstruction_c * );
  BX_SMF_FORCE void Resolve32Mod0EffectAddress_sib0xe7(BX_CPU_C * , bxInstruction_c * );
  BX_SMF_FORCE void Resolve32Mod0EffectAddress_sib0xe8(BX_CPU_C * , bxInstruction_c * );
  BX_SMF_FORCE void Resolve32Mod0EffectAddress_sib0xe9(BX_CPU_C * , bxInstruction_c * );
  BX_SMF_FORCE void Resolve32Mod0EffectAddress_sib0xea(BX_CPU_C * , bxInstruction_c * );
  BX_SMF_FORCE void Resolve32Mod0EffectAddress_sib0xeb(BX_CPU_C * , bxInstruction_c * );
  BX_SMF_FORCE void Resolve32Mod0EffectAddress_sib0xec(BX_CPU_C * , bxInstruction_c * );
  BX_SMF_FORCE void Resolve32Mod0EffectAddress_sib0xed(BX_CPU_C * , bxInstruction_c * );
  BX_SMF_FORCE void Resolve32Mod0EffectAddress_sib0xee(BX_CPU_C * , bxInstruction_c * );
  BX_SMF_FORCE void Resolve32Mod0EffectAddress_sib0xef(BX_CPU_C * , bxInstruction_c * );
  BX_SMF_FORCE void Resolve32Mod0EffectAddress_sib0xf0(BX_CPU_C * , bxInstruction_c * );
  BX_SMF_FORCE void Resolve32Mod0EffectAddress_sib0xf1(BX_CPU_C * , bxInstruction_c * );
  BX_SMF_FORCE void Resolve32Mod0EffectAddress_sib0xf2(BX_CPU_C * , bxInstruction_c * );
  BX_SMF_FORCE void Resolve32Mod0EffectAddress_sib0xf3(BX_CPU_C * , bxInstruction_c * );
  BX_SMF_FORCE void Resolve32Mod0EffectAddress_sib0xf4(BX_CPU_C * , bxInstruction_c * );
  BX_SMF_FORCE void Resolve32Mod0EffectAddress_sib0xf5(BX_CPU_C * , bxInstruction_c * );
  BX_SMF_FORCE void Resolve32Mod0EffectAddress_sib0xf6(BX_CPU_C * , bxInstruction_c * );
  BX_SMF_FORCE void Resolve32Mod0EffectAddress_sib0xf7(BX_CPU_C * , bxInstruction_c * );
  BX_SMF_FORCE void Resolve32Mod0EffectAddress_sib0xf8(BX_CPU_C * , bxInstruction_c * );
  BX_SMF_FORCE void Resolve32Mod0EffectAddress_sib0xf9(BX_CPU_C * , bxInstruction_c * );
  BX_SMF_FORCE void Resolve32Mod0EffectAddress_sib0xfa(BX_CPU_C * , bxInstruction_c * );
  BX_SMF_FORCE void Resolve32Mod0EffectAddress_sib0xfb(BX_CPU_C * , bxInstruction_c * );
  BX_SMF_FORCE void Resolve32Mod0EffectAddress_sib0xfc(BX_CPU_C * , bxInstruction_c * );
  BX_SMF_FORCE void Resolve32Mod0EffectAddress_sib0xfd(BX_CPU_C * , bxInstruction_c * );
  BX_SMF_FORCE void Resolve32Mod0EffectAddress_sib0xfe(BX_CPU_C * , bxInstruction_c * );
  BX_SMF_FORCE void Resolve32Mod0EffectAddress_sib0xff(BX_CPU_C * , bxInstruction_c * );


  BX_SMF void REP(void (*)(void));
  BX_SMF void REP_ZF(void (*)(void), unsigned rep_prefix);
#if BX_DEBUGGER
  BX_SMF void     dbg_take_irq(void);
  BX_SMF void     dbg_force_interrupt(unsigned _vector);
  BX_SMF void     dbg_take_dma(void);
  BX_SMF Boolean  dbg_get_cpu(bx_dbg_cpu_t *cpu);
  BX_SMF Boolean  dbg_set_cpu(bx_dbg_cpu_t *cpu);
  BX_SMF Boolean  dbg_set_reg(unsigned reg, Bit32u val);
  BX_SMF Bit32u   dbg_get_reg(unsigned reg);
  BX_SMF Boolean  dbg_get_sreg(bx_dbg_sreg_t *sreg, unsigned sreg_no);
  BX_SMF unsigned dbg_query_pending(void);
  BX_SMF Bit32u   dbg_get_descriptor_l(bx_descriptor_t *);
  BX_SMF Bit32u   dbg_get_descriptor_h(bx_descriptor_t *);
  BX_SMF Bit32u   dbg_get_eflags(void);
  BX_SMF Boolean  dbg_is_begin_instr_bpoint(Bit32u cs, Bit32u eip, Bit32u laddr,
                                            Bit32u is_32);
  BX_SMF Boolean  dbg_is_end_instr_bpoint(Bit32u cs, Bit32u eip,
                                          Bit32u laddr, Bit32u is_32);
#endif
#if BX_DEBUGGER || BX_DISASM || BX_INSTRUMENTATION
  BX_SMF void     dbg_xlate_linear2phy(Bit32u linear, Bit32u *phy, Boolean *valid);
#endif
  BX_SMF void     atexit(void);

  // now for some ancillary functions...
  BX_SMF void cpu_loop(Bit32s max_instr_count);
  BX_SMF void decode_exgx16(unsigned need_fetch);
  BX_SMF void decode_exgx32(unsigned need_fetch);

  BX_SMF void prefetch(void);
  BX_SMF void revalidate_prefetch_q(void);
  BX_SMF void invalidate_prefetch_q(void);

  BX_SMF void write_virtual_checks(bx_segment_reg_t *seg, Bit32u offset, unsigned length);
  BX_SMF void read_virtual_checks(bx_segment_reg_t *seg, Bit32u offset, unsigned length);

#define BX_IO_READ		0
#define BX_IO_WRITE		1

  BX_SMF Bit32u read_io_(Bit16u addr,unsigned len)
  {
		Bit32u temp = 0;
		BX_CPU_THIS_PTR access_io(addr,len,0,BX_IO_READ,&temp);
		return temp;
  }

  BX_SMF void write_io_(Bit16u addr,unsigned len,Bit32u value)
  {
		BX_CPU_THIS_PTR access_io(addr,len,0,BX_IO_WRITE,&value);
  }

#if (X86CPU_MSWIN_MSDOS==0)
#define BX_LINEAR_MEMORY_READ_WRITE BX_SMF
#else
#define BX_LINEAR_MEMORY_READ_WRITE virtual
#endif

  BX_LINEAR_MEMORY_READ_WRITE void write_virtual_byte(unsigned seg, Bit32u offset, Bit8u *data);
  BX_LINEAR_MEMORY_READ_WRITE void write_virtual_word(unsigned seg, Bit32u offset, Bit16u *data);
  BX_LINEAR_MEMORY_READ_WRITE void write_virtual_dword(unsigned seg, Bit32u offset, Bit32u *data);
  BX_LINEAR_MEMORY_READ_WRITE void read_virtual_byte(unsigned seg, Bit32u offset, Bit8u *data);
  BX_LINEAR_MEMORY_READ_WRITE void read_virtual_word(unsigned seg, Bit32u offset, Bit16u *data);
  BX_LINEAR_MEMORY_READ_WRITE void read_virtual_dword(unsigned seg, Bit32u offset, Bit32u *data);

  BX_LINEAR_MEMORY_READ_WRITE void read_RMW_virtual_byte(unsigned seg, Bit32u offset, Bit8u *data);
  BX_LINEAR_MEMORY_READ_WRITE void read_RMW_virtual_word(unsigned seg, Bit32u offset, Bit16u *data);
  BX_LINEAR_MEMORY_READ_WRITE void read_RMW_virtual_dword(unsigned seg, Bit32u offset, Bit32u *data);
  BX_LINEAR_MEMORY_READ_WRITE void write_RMW_virtual_byte(Bit8u val8);
  BX_LINEAR_MEMORY_READ_WRITE void write_RMW_virtual_word(Bit16u val16);
  BX_LINEAR_MEMORY_READ_WRITE void write_RMW_virtual_dword(Bit32u val32);

  BX_LINEAR_MEMORY_READ_WRITE void access_io(Bit16u addr, unsigned length,unsigned pl,
					  unsigned rw,void *data);
  BX_LINEAR_MEMORY_READ_WRITE void access_linear(Bit32u address, unsigned length, unsigned pl,
                     unsigned rw, void *data);
  BX_SMF Bit32u itranslate_linear(Bit32u laddress, unsigned pl);
  BX_SMF Bit32u dtranslate_linear(Bit32u laddress, unsigned pl, unsigned rw);

  BX_LINEAR_MEMORY_READ_WRITE void write_push_word(unsigned seg, Bit32u offset, Bit16u *data);
  BX_LINEAR_MEMORY_READ_WRITE void write_push_dword(unsigned seg, Bit32u offset, Bit32u *data);

  // 返回:physical page number physical_address_base:最小 physical page 的本机地址
  BX_LINEAR_MEMORY_READ_WRITE int get_physical_host_memory(void **physical_address_base);
  BX_LINEAR_MEMORY_READ_WRITE Bit8u *getHostMemPtr(Bit32u linear_addr,unsigned op,Bit32u **access_stamp);

  BX_SMF void TLB_flush(void);
  BX_SMF void TLB_clear(void);
  BX_SMF void TLB_init(void);
  BX_SMF void set_INTR(Boolean value);
  BX_SMF char *strseg(bx_segment_reg_t *seg);
  BX_SMF void intel_interrupt(Bit8u _vector, Boolean is_INT, Boolean is_error_code,
                 Bit16u error_code);
#if BX_CPU_LEVEL >= 2
  BX_SMF void exception(unsigned _vector, Bit16u error_code, Boolean is_INT);
#endif
  BX_SMF int  int_number(bx_segment_reg_t *seg);
  BX_SMF void shutdown_cpu(void);
  BX_SMF void enable_paging(void);
  BX_SMF void disable_paging(void);
  BX_SMF void CR3_change(Bit32u value32);
  BX_SMF void reset(unsigned source);

  BX_SMF void jump_protected(bxInstruction_c *, Bit16u cs, Bit32u disp32);
  BX_SMF void call_protected(bxInstruction_c *, Bit16u cs, Bit32u disp32);
  BX_SMF void return_protected(bxInstruction_c *, Bit16u pop_bytes);
  BX_SMF void iret_protected(bxInstruction_c *);
  BX_SMF void validate_seg_regs(void);
  BX_SMF void stack_return_to_v86(Bit32u new_eip, Bit32u raw_cs_selector,
                                     Bit32u flags32);
  BX_SMF void stack_return_from_v86(bxInstruction_c *);
  BX_SMF void init_v8086_mode(void);
  BX_SMF void v8086_message(void);
  BX_SMF void task_switch(bx_selector_t *selector,
                     bx_descriptor_t *descriptor,
                     unsigned source,
                     Bit32u dword1, Bit32u dword2);
  BX_SMF void get_SS_ESP_from_TSS(unsigned pl, Bit16u *ss, Bit32u *esp);
  BX_SMF void write_flags(Bit16u flags, Boolean change_IOPL, Boolean change_IF);
  BX_SMF void write_eflags(Bit32u eflags, Boolean change_IOPL, Boolean change_IF,
                    Boolean change_VM, Boolean change_RF);
  BX_SMF Bit16u read_flags(void);
  BX_SMF Bit32u read_eflags(void);

  BX_SMF Bit8u   inp8(Bit16u addr);
  BX_SMF void    outp8(Bit16u addr, Bit8u value);
  BX_SMF Bit16u  inp16(Bit16u addr);
  BX_SMF void    outp16(Bit16u addr, Bit16u value);
  BX_SMF Bit32u  inp32(Bit16u addr);
  BX_SMF void    outp32(Bit16u addr, Bit32u value);
  BX_SMF Boolean allow_io(Bit16u addr, unsigned len);
  BX_SMF void    enter_protected_mode(void);
  BX_SMF void    enter_real_mode(void);
  BX_SMF void    parse_selector(Bit16u raw_selector, bx_selector_t *selector);
  BX_SMF void    parse_descriptor(Bit32u dword1, Bit32u dword2, bx_descriptor_t *temp);
  BX_SMF void    load_ldtr(bx_selector_t *selector, bx_descriptor_t *descriptor);
  BX_SMF void    load_cs(bx_selector_t *selector, bx_descriptor_t *descriptor, Bit8u cpl);
  BX_SMF void    load_ss(bx_selector_t *selector, bx_descriptor_t *descriptor, Bit8u cpl);
  BX_SMF void    fetch_raw_descriptor(bx_selector_t *selector,
                               Bit32u *dword1, Bit32u *dword2, Bit8u exception);

  BX_SMF void    load_seg_reg(bx_segment_reg_t *seg, Bit16u new_value);

  BX_SMF Boolean fetch_raw_descriptor2(bx_selector_t *selector,
                                Bit32u *dword1, Bit32u *dword2);
  BX_SMF void    push_16(Bit16u value16);
  BX_SMF void    push_32(Bit32u value32);
  BX_SMF void    call_push_16(Bit16u value16);
  BX_SMF void    call_push_32(Bit32u value32);
  BX_SMF void    pop_16(Bit16u *value16_ptr);
  BX_SMF void    pop_32(Bit32u *value32_ptr);
  BX_SMF Boolean can_push(bx_descriptor_t *descriptor, Bit32u esp, Bit32u bytes);
  BX_SMF Boolean can_pop(Bit32u bytes);
  BX_SMF void    sanity_checks(void);

  BX_SMF void    debug(Bit32u offset);

#if BX_X86_DEBUGGER
  // x86 hardware debug support
  BX_SMF Bit32u  hwdebug_compare(Bit32u laddr, unsigned size,
                                 unsigned opa, unsigned opb);
#endif

  BX_SMF BX_CPP_INLINE void set_CF(Boolean val);
  BX_SMF BX_CPP_INLINE void set_AF(Boolean val);
  BX_SMF BX_CPP_INLINE void set_ZF(Boolean val);
  BX_SMF BX_CPP_INLINE void set_SF(Boolean val);
  BX_SMF BX_CPP_INLINE void set_OF(Boolean val);
  BX_SMF BX_CPP_INLINE void set_PF(Boolean val);
  BX_SMF BX_CPP_INLINE void set_PF_base(Bit8u val);

  BX_SMF BX_CPP_INLINE void set_AX(Bit16u ax);
  BX_SMF BX_CPP_INLINE void set_BX(Bit16u bx);
  BX_SMF BX_CPP_INLINE void set_CX(Bit16u cx);
  BX_SMF BX_CPP_INLINE void set_DX(Bit16u dx);
  BX_SMF BX_CPP_INLINE void set_AL(Bit8u  al);
  BX_SMF BX_CPP_INLINE void set_AH(Bit8u  ah);
  BX_SMF BX_CPP_INLINE void set_BL(Bit8u  bl);
  BX_SMF BX_CPP_INLINE void set_BH(Bit8u  bh);
  BX_SMF BX_CPP_INLINE void set_CL(Bit8u  cl);
  BX_SMF BX_CPP_INLINE void set_CH(Bit8u  ch);
  BX_SMF BX_CPP_INLINE void set_DL(Bit8u  dl);
  BX_SMF BX_CPP_INLINE void set_DH(Bit8u  dh);

  BX_SMF BX_CPP_INLINE Bit8u get_AL(void);
  BX_SMF BX_CPP_INLINE Bit8u get_AH(void);
  BX_SMF BX_CPP_INLINE Bit8u get_BL(void);
  BX_SMF BX_CPP_INLINE Bit8u get_BH(void);
  BX_SMF BX_CPP_INLINE Bit8u get_CL(void);
  BX_SMF BX_CPP_INLINE Bit8u get_CH(void);
  BX_SMF BX_CPP_INLINE Bit8u get_DL(void);
  BX_SMF BX_CPP_INLINE Bit8u get_DH(void);

  BX_SMF BX_CPP_INLINE Bit16u get_AX(void);
  BX_SMF BX_CPP_INLINE Bit16u get_BX(void);
  BX_SMF BX_CPP_INLINE Bit16u get_CX(void);
  BX_SMF BX_CPP_INLINE Bit16u get_DX(void);

  BX_SMF BX_CPP_INLINE unsigned int get_DF(void);
  BX_SMF BX_CPP_INLINE unsigned int get_IF(void);
  BX_SMF BX_CPP_INLINE unsigned int get_VM(void);
  BX_SMF BX_CPP_INLINE unsigned int get_IOPL(void);

  BX_SMF BX_CPP_INLINE void set_IF(int _bit);

#if BX_CPU_LEVEL >= 2
  BX_SMF BX_CPP_INLINE Boolean real_mode(void);
#endif
#if BX_CPU_LEVEL >= 3
  BX_SMF BX_CPP_INLINE Boolean protected_mode(void);
  BX_SMF BX_CPP_INLINE Boolean v8086_mode(void);
#endif
#if BX_SUPPORT_APIC
  bx_local_apic_c local_apic;
  Boolean int_from_local_apic;
#endif
  };


#if BX_SupportICache

BX_CPP_INLINE void bxICache_c::decWriteStamp(BX_CPU_C *cpu, Bit32u a20Addr) {
  // Increment page write stamp, so iCache entries with older stamps
  // are effectively invalidated.
  Bit32u pageIndex = a20Addr >> 12;
  Bit32u writeStamp = cpu->iCache.pageWriteStampTable[pageIndex];
  if ( writeStamp & 0x20000000 ) {
    // Page possibly contains iCache code.
    if ( writeStamp & ICacheWriteStampMask ) {
      // Short case: there is room to decrement the generation counter.
      cpu->iCache.pageWriteStampTable[pageIndex]--;
      }
    else {
      // Long case: there is no more room to decrement.  We have dump
      // all iCache entries which can possibly hash to this page since
      // we don't keep track of individual entries.

      // Take the hash of the 0th page offset.
      unsigned iCacheHash = cpu->iCache.hash(a20Addr & 0xfffff000);
      for (unsigned o=0; o<4096; o++) {
        cpu->iCache.entry[iCacheHash].writeStamp = ICacheWriteStampInvalid;
        iCacheHash = (iCacheHash + 1) % BxICacheEntries;
        }
      // Reset write stamp to highest value to begin the decrementing process
      // again.
      cpu->iCache.pageWriteStampTable[pageIndex] = ICacheWriteStampInvalid;
      }
    }
  }

BX_CPP_INLINE Bit32u bxICache_c::createFetchModeMask(BX_CPU_C *cpu) {
  return (cpu->program_visible_sregs[BX_SEG_REG_CS].cache.u.segment.d_b << 31)
#if BX_SUPPORT_X86_64
         | ((cpu->cpu_mode == BX_MODE_LONG_64)<<30)
#endif
         | (1<<29) // iCache code.
         ;
  }

#endif

#if BX_X86_DEBUGGER
#define BX_HWDebugInstruction   0x00
#define BX_HWDebugMemW          0x01
#define BX_HWDebugIO            0x02
#define BX_HWDebugMemRW         0x03
#endif


#if BX_SMP_PROCESSORS==1
// single processor simulation, so there's one of everything
extern BX_CPU_C       bx_cpu;
#else
// multiprocessor simulation, we need an array of cpus and memories
extern BX_CPU_C       *bx_cpu_array[BX_SMP_PROCESSORS+1];
#endif

#if defined(NEED_CPU_REG_SHORTCUTS)

BX_SMF BX_CPP_INLINE void BX_CPU_C_PREFIX set_AX(Bit16u ax) { X86_AX = ax; };
BX_SMF BX_CPP_INLINE void BX_CPU_C_PREFIX set_BX(Bit16u bx) { X86_BX = bx; };
BX_SMF BX_CPP_INLINE void BX_CPU_C_PREFIX set_CX(Bit16u cx) { X86_CX = cx; };
BX_SMF BX_CPP_INLINE void BX_CPU_C_PREFIX set_DX(Bit16u dx) { X86_DX = dx; };
BX_SMF BX_CPP_INLINE void BX_CPU_C_PREFIX set_AL(Bit8u  al) { X86_AL = al; };
BX_SMF BX_CPP_INLINE void BX_CPU_C_PREFIX set_AH(Bit8u  ah) { X86_AH = ah; };
BX_SMF BX_CPP_INLINE void BX_CPU_C_PREFIX set_BL(Bit8u  bl) { X86_BL = bl; };
BX_SMF BX_CPP_INLINE void BX_CPU_C_PREFIX set_BH(Bit8u  bh) { X86_BH = bh; };
BX_SMF BX_CPP_INLINE void BX_CPU_C_PREFIX set_CL(Bit8u  cl) { X86_CL = cl; };
BX_SMF BX_CPP_INLINE void BX_CPU_C_PREFIX set_CH(Bit8u  ch) { X86_CH = ch; };
BX_SMF BX_CPP_INLINE void BX_CPU_C_PREFIX set_DL(Bit8u  dl) { X86_DL = dl; };
BX_SMF BX_CPP_INLINE void BX_CPU_C_PREFIX set_DH(Bit8u  dh) { X86_DH = dh; };

BX_SMF BX_CPP_INLINE Bit8u BX_CPU_C_PREFIX get_AL(void) { return(X86_AL); };
BX_SMF BX_CPP_INLINE Bit8u BX_CPU_C_PREFIX get_AH(void) { return(X86_AH); };
BX_SMF BX_CPP_INLINE Bit8u BX_CPU_C_PREFIX get_BL(void) { return(X86_BL); };
BX_SMF BX_CPP_INLINE Bit8u BX_CPU_C_PREFIX get_BH(void) { return(X86_BH); };
BX_SMF BX_CPP_INLINE Bit8u BX_CPU_C_PREFIX get_CL(void) { return(X86_CL); };
BX_SMF BX_CPP_INLINE Bit8u BX_CPU_C_PREFIX get_CH(void) { return(X86_CH); };
BX_SMF BX_CPP_INLINE Bit8u BX_CPU_C_PREFIX get_DL(void) { return(X86_DL); };
BX_SMF BX_CPP_INLINE Bit8u BX_CPU_C_PREFIX get_DH(void) { return(X86_DH); };

BX_SMF BX_CPP_INLINE Bit16u BX_CPU_C_PREFIX get_AX(void) { return(X86_AX); };
BX_SMF BX_CPP_INLINE Bit16u BX_CPU_C_PREFIX get_BX(void) { return(X86_BX); };
BX_SMF BX_CPP_INLINE Bit16u BX_CPU_C_PREFIX get_CX(void) { return(X86_CX); };
BX_SMF BX_CPP_INLINE Bit16u BX_CPU_C_PREFIX get_DX(void) { return(X86_DX); };

#endif

  BX_CPP_INLINE unsigned int BX_CPU_C::get_DF(void) { return(BX_CPU_THIS_PTR eflags.df); };
  BX_CPP_INLINE unsigned int BX_CPU_C::get_IF(void) { return(BX_CPU_THIS_PTR eflags.if_); };
  BX_CPP_INLINE unsigned int BX_CPU_C::get_VM(void) { return(BX_CPU_THIS_PTR eflags.vm); };
  BX_CPP_INLINE unsigned int BX_CPU_C::get_IOPL(void) { return(BX_CPU_THIS_PTR eflags.iopl); };

  BX_CPP_INLINE void BX_CPU_C::set_IF(int _bit) { BX_CPU_THIS_PTR eflags.if_ = _bit; };


#if BX_CPU_LEVEL >= 2
  BX_CPP_INLINE Boolean BX_CPU_C::real_mode(void) { return( !BX_CPU_THIS_PTR cr0.pe ); };
#endif

#if BX_CPU_LEVEL == 2
  BX_CPP_INLINE Boolean BX_CPU_C::protected_mode(void) { return( BX_CPU_THIS_PTR cr0.pe ); };
#endif


#if BX_CPU_LEVEL >= 3
#  if BX_SUPPORT_V8086_MODE
  BX_CPP_INLINE Boolean
BX_CPU_C::v8086_mode(void) {
  return(BX_CPU_THIS_PTR eflags.vm);
  }

  BX_CPP_INLINE Boolean
BX_CPU_C::protected_mode(void) {
  return(BX_CPU_THIS_PTR cr0.pe && !BX_CPU_THIS_PTR eflags.vm);
  }
#  else
  BX_CPP_INLINE Boolean
BX_CPU_C::v8086_mode(void) {
  return(0);
  }

  BX_CPP_INLINE Boolean
BX_CPU_C::protected_mode(void) {
  return(BX_CPU_THIS_PTR cr0.pe);
  }
#  endif
#endif


extern const Boolean bx_parity_lookup[256];

extern const char Translate_modrm32_length[1<<(	2		+3		+3)];
extern const char Translate_modrm16_length[1<<(	2		+3		+3)];
extern const unsigned Translate_modrm_to_rrr[0x100];
extern const Bit8u Translate_modrm_to_lea_modrm[0x100];
extern const Bit8u Translate_modrm_to_new_modrm[0x100];
extern const Bit8u Translate_jmp_codebuff[];
extern const Bit32u Translate_jmp_codeoffset[];
extern const Bit32u Translate_jmp_codeparam[];

#if (HOST_CPU_IS_I80386==0)

    BX_CPP_INLINE void
BX_CPU_C::set_CF(Boolean val) {
    BX_CPU_THIS_PTR lf_flags_status &= 0xfffff0;
    BX_CPU_THIS_PTR eflags.cf = val;
    }

    BX_CPP_INLINE void
BX_CPU_C::set_AF(Boolean val) {
    BX_CPU_THIS_PTR lf_flags_status &= 0xfff0ff;
    BX_CPU_THIS_PTR eflags.af = val;
    }

    BX_CPP_INLINE void
BX_CPU_C::set_ZF(Boolean val) {
    BX_CPU_THIS_PTR lf_flags_status &= 0xff0fff;
    BX_CPU_THIS_PTR eflags.zf = val;
   }

    BX_CPP_INLINE void
BX_CPU_C::set_SF(Boolean val) {
    BX_CPU_THIS_PTR lf_flags_status &= 0xf0ffff;
    BX_CPU_THIS_PTR eflags.sf = val;
    }

    BX_CPP_INLINE void
BX_CPU_C::set_OF(Boolean val) {
    BX_CPU_THIS_PTR lf_flags_status &= 0x0fffff;
    BX_CPU_THIS_PTR eflags.of = val;
    }

    BX_CPP_INLINE void
BX_CPU_C::set_PF(Boolean val) {
    BX_CPU_THIS_PTR lf_flags_status &= 0xffff0f;
    BX_CPU_THIS_PTR eflags.pf = val;
    }

    BX_CPP_INLINE void
BX_CPU_C::set_PF_base(Bit8u val) {
    BX_CPU_THIS_PTR lf_flags_status &= 0xffff0f;
    BX_CPU_THIS_PTR eflags.pf = bx_parity_lookup[val]; // Always returns 0 or 1.
    }

#endif //#if (HOST_CPU_IS_I80386==0)


#if (HOST_CPU_IS_I80386==1)

    BX_CPP_INLINE void
BX_CPU_C::set_CF(Boolean val) {
	BX_CPU_THIS_PTR eflags.x86.Descr.cf = val;
    }

    BX_CPP_INLINE void
BX_CPU_C::set_AF(Boolean val) {
	BX_CPU_THIS_PTR eflags.x86.Descr.af = val;
    }

    BX_CPP_INLINE void
BX_CPU_C::set_ZF(Boolean val) {
	BX_CPU_THIS_PTR eflags.x86.Descr.zf = val;
    }

    BX_CPP_INLINE void
BX_CPU_C::set_SF(Boolean val) {
	BX_CPU_THIS_PTR eflags.x86.Descr.sf = val;
    }

    BX_CPP_INLINE void
BX_CPU_C::set_OF(Boolean val) {
	BX_CPU_THIS_PTR eflags.x86.Descr.of = val;
    }

    BX_CPP_INLINE void
BX_CPU_C::set_PF(Boolean val) {
	BX_CPU_THIS_PTR eflags.x86.Descr.pf = val;
    }

    BX_CPP_INLINE void
BX_CPU_C::set_PF_base(Bit8u val) {
	BX_CPU_THIS_PTR eflags.x86.Descr.pf = bx_parity_lookup[val];
    }

#endif //#if (HOST_CPU_IS_I80386==1)

#if (HOST_CPU_IS_I80386==0)

#define SET_FLAGS_OSZAPC_8(op1, op2, result, ins) { BX_CPU_CLASS_PTR lf_entrys[BX_LF_INDEX_OSZAPC].op1_8 = op1; BX_CPU_CLASS_PTR lf_entrys[BX_LF_INDEX_OSZAPC].op2_8 = op2; BX_CPU_CLASS_PTR lf_entrys[BX_LF_INDEX_OSZAPC].result_8 = result; BX_CPU_CLASS_PTR lf_entrys[BX_LF_INDEX_OSZAPC].instr = ins; BX_CPU_CLASS_PTR lf_flags_status = BX_LF_MASK_OSZAPC; }

#define SET_FLAGS_OSZAPC_8_CF(op1, op2, result, ins, last_cf) { BX_CPU_CLASS_PTR lf_entrys[BX_LF_INDEX_OSZAPC].op1_8 = op1; BX_CPU_CLASS_PTR lf_entrys[BX_LF_INDEX_OSZAPC].op2_8 = op2; BX_CPU_CLASS_PTR lf_entrys[BX_LF_INDEX_OSZAPC].result_8 = result; BX_CPU_CLASS_PTR lf_entrys[BX_LF_INDEX_OSZAPC].instr = ins; BX_CPU_CLASS_PTR lf_entrys[BX_LF_INDEX_OSZAPC].prev_cf = last_cf; BX_CPU_CLASS_PTR lf_flags_status = BX_LF_MASK_OSZAPC; }

#define SET_FLAGS_OSZAPC_16(op1, op2, result, ins) { BX_CPU_CLASS_PTR lf_entrys[BX_LF_INDEX_OSZAPC].op1_16 = op1; BX_CPU_CLASS_PTR lf_entrys[BX_LF_INDEX_OSZAPC].op2_16 = op2; BX_CPU_CLASS_PTR lf_entrys[BX_LF_INDEX_OSZAPC].result_16 = result; BX_CPU_CLASS_PTR lf_entrys[BX_LF_INDEX_OSZAPC].instr = ins; BX_CPU_CLASS_PTR lf_flags_status = BX_LF_MASK_OSZAPC; }

#define SET_FLAGS_OSZAPC_16_CF(op1, op2, result, ins, last_cf) { BX_CPU_CLASS_PTR lf_entrys[BX_LF_INDEX_OSZAPC].op1_16 = op1; BX_CPU_CLASS_PTR lf_entrys[BX_LF_INDEX_OSZAPC].op2_16 = op2; BX_CPU_CLASS_PTR lf_entrys[BX_LF_INDEX_OSZAPC].result_16 = result; BX_CPU_CLASS_PTR lf_entrys[BX_LF_INDEX_OSZAPC].instr = ins; BX_CPU_CLASS_PTR lf_entrys[BX_LF_INDEX_OSZAPC].prev_cf = last_cf; BX_CPU_CLASS_PTR lf_flags_status = BX_LF_MASK_OSZAPC; }

#define SET_FLAGS_OSZAPC_32(op1, op2, result, ins) { BX_CPU_CLASS_PTR lf_entrys[BX_LF_INDEX_OSZAPC].op1_32 = op1; BX_CPU_CLASS_PTR lf_entrys[BX_LF_INDEX_OSZAPC].op2_32 = op2; BX_CPU_CLASS_PTR lf_entrys[BX_LF_INDEX_OSZAPC].result_32 = result; BX_CPU_CLASS_PTR lf_entrys[BX_LF_INDEX_OSZAPC].instr = ins; BX_CPU_CLASS_PTR lf_flags_status = BX_LF_MASK_OSZAPC; }

#define SET_FLAGS_OSZAPC_32_CF(op1, op2, result, ins, last_cf) { BX_CPU_CLASS_PTR lf_entrys[BX_LF_INDEX_OSZAPC].op1_32 = op1; BX_CPU_CLASS_PTR lf_entrys[BX_LF_INDEX_OSZAPC].op2_32 = op2; BX_CPU_CLASS_PTR lf_entrys[BX_LF_INDEX_OSZAPC].result_32 = result; BX_CPU_CLASS_PTR lf_entrys[BX_LF_INDEX_OSZAPC].instr = ins; BX_CPU_CLASS_PTR lf_entrys[BX_LF_INDEX_OSZAPC].prev_cf = last_cf; BX_CPU_CLASS_PTR lf_flags_status = BX_LF_MASK_OSZAPC; }


#define SET_FLAGS_OSZAP_8(op1, op2, result, ins) { BX_CPU_CLASS_PTR lf_entrys[BX_LF_INDEX_OSZAP].op1_8 = op1; BX_CPU_CLASS_PTR lf_entrys[BX_LF_INDEX_OSZAP].op2_8 = op2; BX_CPU_CLASS_PTR lf_entrys[BX_LF_INDEX_OSZAP].result_8 = result; BX_CPU_CLASS_PTR lf_entrys[BX_LF_INDEX_OSZAP].instr = ins; BX_CPU_CLASS_PTR lf_flags_status = (BX_CPU_CLASS_PTR lf_flags_status & 0x00000f) | BX_LF_MASK_OSZAP; }

#define SET_FLAGS_OSZAP_16(op1, op2, result, ins) { BX_CPU_CLASS_PTR lf_entrys[BX_LF_INDEX_OSZAP].op1_16 = op1; BX_CPU_CLASS_PTR lf_entrys[BX_LF_INDEX_OSZAP].op2_16 = op2; BX_CPU_CLASS_PTR lf_entrys[BX_LF_INDEX_OSZAP].result_16 = result; BX_CPU_CLASS_PTR lf_entrys[BX_LF_INDEX_OSZAP].instr = ins; BX_CPU_CLASS_PTR lf_flags_status = (BX_CPU_CLASS_PTR lf_flags_status & 0x00000f) | BX_LF_MASK_OSZAP; }

#define SET_FLAGS_OSZAP_32(op1, op2, result, ins) { BX_CPU_CLASS_PTR lf_entrys[BX_LF_INDEX_OSZAP].op1_32 = op1; BX_CPU_CLASS_PTR lf_entrys[BX_LF_INDEX_OSZAP].op2_32 = op2; BX_CPU_CLASS_PTR lf_entrys[BX_LF_INDEX_OSZAP].result_32 = result; BX_CPU_CLASS_PTR lf_entrys[BX_LF_INDEX_OSZAP].instr = ins; BX_CPU_CLASS_PTR lf_flags_status = (BX_CPU_CLASS_PTR lf_flags_status & 0x00000f) | BX_LF_MASK_OSZAP; }

#define SET_FLAGS_OxxxxC(new_of, new_cf) { BX_CPU_CLASS_PTR eflags.of = (Boolean) (new_of); BX_CPU_CLASS_PTR eflags.cf = (Boolean) (new_cf); BX_CPU_CLASS_PTR lf_flags_status &= 0x0ffff0; /* ??? could also mark other bits undefined here */ }

//-----------------------------------------------------------------------

#define SET_FLAGS_OSZPC_8(op1, count, result, ins) { BX_CPU_CLASS_PTR lf_entrys[BX_LF_INDEX_OSZPC].op1_8 = op1; BX_CPU_CLASS_PTR lf_entrys[BX_LF_INDEX_OSZPC].shift_counter = count; BX_CPU_CLASS_PTR lf_entrys[BX_LF_INDEX_OSZPC].result_8 = result; BX_CPU_CLASS_PTR lf_entrys[BX_LF_INDEX_OSZPC].instr = ins; BX_CPU_CLASS_PTR lf_flags_status = (BX_CPU_CLASS_PTR lf_flags_status & 0x000f00) | BX_LF_MASK_OSZPC; }

#define SET_FLAGS_OSZPC_16(op1, count, result, ins) { BX_CPU_CLASS_PTR lf_entrys[BX_LF_INDEX_OSZPC].op1_16 = op1; BX_CPU_CLASS_PTR lf_entrys[BX_LF_INDEX_OSZPC].shift_counter = count;     BX_CPU_CLASS_PTR lf_entrys[BX_LF_INDEX_OSZPC].result_16 = result;     BX_CPU_CLASS_PTR lf_entrys[BX_LF_INDEX_OSZPC].instr = ins;     BX_CPU_CLASS_PTR lf_flags_status = 	(BX_CPU_CLASS_PTR lf_flags_status & 0x000f00) | BX_LF_MASK_OSZPC;     }

#define SET_FLAGS_OSZPC_32(op1, count, result, ins) {     BX_CPU_CLASS_PTR lf_entrys[BX_LF_INDEX_OSZPC].op1_32 = op1;     BX_CPU_CLASS_PTR lf_entrys[BX_LF_INDEX_OSZPC].shift_counter = count;     BX_CPU_CLASS_PTR lf_entrys[BX_LF_INDEX_OSZPC].result_32 = result;     BX_CPU_CLASS_PTR lf_entrys[BX_LF_INDEX_OSZPC].instr = ins;     BX_CPU_CLASS_PTR lf_flags_status = 	(BX_CPU_CLASS_PTR lf_flags_status & 0x000f00) | BX_LF_MASK_OSZPC;     }

#define SET3_FLAGS_OSZPC_16(op1, op2, count,result, ins) {     BX_CPU_CLASS_PTR lf_entrys[BX_LF_INDEX_OSZPC].op1_16 = op1;     BX_CPU_CLASS_PTR lf_entrys[BX_LF_INDEX_OSZPC].op2_16 = op2;     BX_CPU_CLASS_PTR lf_entrys[BX_LF_INDEX_OSZPC].shift_counter = count;     BX_CPU_CLASS_PTR lf_entrys[BX_LF_INDEX_OSZPC].result_16 = result;     BX_CPU_CLASS_PTR lf_entrys[BX_LF_INDEX_OSZPC].instr = ins;     BX_CPU_CLASS_PTR lf_flags_status = 	(BX_CPU_CLASS_PTR lf_flags_status & 0x000f00) | BX_LF_MASK_OSZPC;     }

#define SET3_FLAGS_OSZPC_32(op1, op2, count,result, ins) {     BX_CPU_CLASS_PTR lf_entrys[BX_LF_INDEX_OSZPC].op1_32 = op1;     BX_CPU_CLASS_PTR lf_entrys[BX_LF_INDEX_OSZPC].op2_32 = op2;     BX_CPU_CLASS_PTR lf_entrys[BX_LF_INDEX_OSZPC].shift_counter = count;     BX_CPU_CLASS_PTR lf_entrys[BX_LF_INDEX_OSZPC].instr = ins;     BX_CPU_CLASS_PTR lf_flags_status = 	(BX_CPU_CLASS_PTR lf_flags_status & 0x000f00) | BX_LF_MASK_OSZPC;     }


#define SET_FLAGS_XSZPC_8(op1, count, result, ins) { BX_CPU_CLASS_PTR lf_entrys[BX_LF_INDEX_XSZPC].op1_8 = op1;     BX_CPU_CLASS_PTR lf_entrys[BX_LF_INDEX_XSZPC].shift_counter = count;     BX_CPU_CLASS_PTR lf_entrys[BX_LF_INDEX_XSZPC].result_8 = result;     BX_CPU_CLASS_PTR lf_entrys[BX_LF_INDEX_XSZPC].instr = ins;     BX_CPU_CLASS_PTR lf_flags_status = 	(BX_CPU_CLASS_PTR lf_flags_status & 0xf00f00) | BX_LF_MASK_XSZPC;     }

#define SET_FLAGS_XSZPC_16(op1, count, result, ins) {     BX_CPU_CLASS_PTR lf_entrys[BX_LF_INDEX_XSZPC].op1_16 = op1;     BX_CPU_CLASS_PTR lf_entrys[BX_LF_INDEX_XSZPC].shift_counter = count;     BX_CPU_CLASS_PTR lf_entrys[BX_LF_INDEX_XSZPC].result_16 = result;     BX_CPU_CLASS_PTR lf_entrys[BX_LF_INDEX_XSZPC].instr = ins;     BX_CPU_CLASS_PTR lf_flags_status = 	(BX_CPU_CLASS_PTR lf_flags_status & 0xf00f00) | BX_LF_MASK_XSZPC;     }

#define SET_FLAGS_XSZPC_32(op1, count, result, ins) {     BX_CPU_CLASS_PTR lf_entrys[BX_LF_INDEX_XSZPC].op1_32 = op1;     BX_CPU_CLASS_PTR lf_entrys[BX_LF_INDEX_XSZPC].shift_counter = count;     BX_CPU_CLASS_PTR lf_entrys[BX_LF_INDEX_XSZPC].result_32 = result;     BX_CPU_CLASS_PTR lf_entrys[BX_LF_INDEX_XSZPC].instr = ins;     BX_CPU_CLASS_PTR lf_flags_status = 	(BX_CPU_CLASS_PTR lf_flags_status & 0xf00f00) | BX_LF_MASK_XSZPC;     }

#define SET3_FLAGS_XSZPC_16(op1, op2, count,result, ins) {     BX_CPU_CLASS_PTR lf_entrys[BX_LF_INDEX_XSZPC].op1_16 = op1;     BX_CPU_CLASS_PTR lf_entrys[BX_LF_INDEX_XSZPC].op2_16 = op2;     BX_CPU_CLASS_PTR lf_entrys[BX_LF_INDEX_XSZPC].shift_counter = count;     BX_CPU_CLASS_PTR lf_entrys[BX_LF_INDEX_XSZPC].result_16 = result;     BX_CPU_CLASS_PTR lf_entrys[BX_LF_INDEX_XSZPC].instr = ins;     BX_CPU_CLASS_PTR lf_flags_status = 	(BX_CPU_CLASS_PTR lf_flags_status & 0xf00f00) | BX_LF_MASK_XSZPC;     }

#define SET3_FLAGS_XSZPC_32(op1, op2, count,result, ins) {     BX_CPU_CLASS_PTR lf_entrys[BX_LF_INDEX_XSZPC].op1_32 = op1;     BX_CPU_CLASS_PTR lf_entrys[BX_LF_INDEX_XSZPC].op2_32 = op2;     BX_CPU_CLASS_PTR lf_entrys[BX_LF_INDEX_XSZPC].shift_counter = count;     BX_CPU_CLASS_PTR lf_entrys[BX_LF_INDEX_XSZPC].result_32 = result;     BX_CPU_CLASS_PTR lf_entrys[BX_LF_INDEX_XSZPC].instr = ins;     BX_CPU_CLASS_PTR lf_flags_status = 	(BX_CPU_CLASS_PTR lf_flags_status & 0xf00f00) | BX_LF_MASK_XSZPC;     }

#define SET_FLAGS_OC_8(op1, count, result, ins) { BX_CPU_CLASS_PTR lf_entrys[BX_LF_INDEX_OC].op1_8 = op1;     BX_CPU_CLASS_PTR lf_entrys[BX_LF_INDEX_OC].shift_counter = count;     BX_CPU_CLASS_PTR lf_entrys[BX_LF_INDEX_OC].result_8 = result;     BX_CPU_CLASS_PTR lf_entrys[BX_LF_INDEX_OC].instr = ins;     BX_CPU_CLASS_PTR lf_flags_status = 	(BX_CPU_CLASS_PTR lf_flags_status & 0x0ffff0) | BX_LF_MASK_OC; }

#define SET_FLAGS_OC_16(op1, count, result, ins) { BX_CPU_CLASS_PTR lf_entrys[BX_LF_INDEX_OC].op1_16 = op1;   BX_CPU_CLASS_PTR lf_entrys[BX_LF_INDEX_OC].shift_counter = count;     BX_CPU_CLASS_PTR lf_entrys[BX_LF_INDEX_OC].result_16 = result;     BX_CPU_CLASS_PTR lf_entrys[BX_LF_INDEX_OC].instr = ins;     BX_CPU_CLASS_PTR lf_flags_status = 	(BX_CPU_CLASS_PTR lf_flags_status & 0x0ffff0) | BX_LF_MASK_OC;  }

#define SET_FLAGS_OC_32(op1, count, result, ins) { BX_CPU_CLASS_PTR lf_entrys[BX_LF_INDEX_OC].op1_32 = op1;     BX_CPU_CLASS_PTR lf_entrys[BX_LF_INDEX_OC].shift_counter = count;     BX_CPU_CLASS_PTR lf_entrys[BX_LF_INDEX_OC].result_32 = result;     BX_CPU_CLASS_PTR lf_entrys[BX_LF_INDEX_OC].instr = ins;     BX_CPU_CLASS_PTR lf_flags_status = 	(BX_CPU_CLASS_PTR lf_flags_status & 0x0ffff0) | BX_LF_MASK_OC; }

#define SET_FLAGS_XC_8(op1, count, result, ins) { BX_CPU_CLASS_PTR lf_entrys[BX_LF_INDEX_XC].op1_8 = op1; BX_CPU_CLASS_PTR lf_entrys[BX_LF_INDEX_XC].shift_counter = count; BX_CPU_CLASS_PTR lf_entrys[BX_LF_INDEX_XC].result_8 = result; BX_CPU_CLASS_PTR lf_entrys[BX_LF_INDEX_XC].instr = ins; BX_CPU_CLASS_PTR lf_flags_status = (BX_CPU_CLASS_PTR lf_flags_status & 0xfffff0) | BX_LF_MASK_XC; }

#define SET_FLAGS_XC_16(op1, count, result, ins) { BX_CPU_CLASS_PTR lf_entrys[BX_LF_INDEX_XC].op1_16 = op1; BX_CPU_CLASS_PTR lf_entrys[BX_LF_INDEX_XC].shift_counter = count; BX_CPU_CLASS_PTR lf_entrys[BX_LF_INDEX_XC].result_16 = result; BX_CPU_CLASS_PTR lf_entrys[BX_LF_INDEX_XC].instr = ins; BX_CPU_CLASS_PTR lf_flags_status = (BX_CPU_CLASS_PTR lf_flags_status & 0xfffff0) | BX_LF_MASK_XC; }

#define SET_FLAGS_XC_32(op1, count, result, ins) { BX_CPU_CLASS_PTR lf_entrys[BX_LF_INDEX_XC].op1_32 = op1; BX_CPU_CLASS_PTR lf_entrys[BX_LF_INDEX_XC].shift_counter = count; BX_CPU_CLASS_PTR lf_entrys[BX_LF_INDEX_XC].result_32 = result; BX_CPU_CLASS_PTR lf_entrys[BX_LF_INDEX_XC].instr = ins; BX_CPU_CLASS_PTR lf_flags_status = (BX_CPU_CLASS_PTR lf_flags_status & 0xfffff0) | BX_LF_MASK_XC;  }

#endif //#if (HOST_CPU_IS_I80386==0)

#if (HOST_CPU_IS_I80386==1)

#define SET_FLAGS_OxxxxC(new_of, new_cf) { BX_CPU_CLASS_PTR eflags.x86.Word.seto = (Boolean)(new_of); BX_CPU_CLASS_PTR eflags.x86.Word.lahf &= 0xfe; BX_CPU_CLASS_PTR eflags.x86.Word.lahf |= (Boolean)(new_cf); /* ??? could also mark other bits undefined here */ }

#endif //#if (HOST_CPU_IS_I80386==1)

extern const Boolean bx_parity_lookup[256];

#define BX_REPE_PREFIX  10
#define BX_REPNE_PREFIX 11

#define BX_TASK_FROM_JUMP         10
#define BX_TASK_FROM_CALL_OR_INT  11
#define BX_TASK_FROM_IRET         12

//
// For decoding...
//

// If the Immediate bit is set, the lowest 3 bits of the attribute
// specify which kinds of immediate data a required by instruction.

#define BxImmediate         0x000f // bits 3..0: any immediate
#define BxImmediate_Ib      0x0001 // 8 bits regardless
#define BxImmediate_Ib_SE   0x0002 // sign extend to OS size
#define BxImmediate_Iv      0x0003 // 16 or 32 depending on OS size
#define BxImmediate_Iw      0x0004 // 16 bits regardless
#define BxImmediate_IvIw    0x0005 // call_Ap
#define BxImmediate_IwIb    0x0006 // enter_IwIb
#define BxImmediate_O       0x0007 // mov_ALOb, mov_ObAL, mov_eAXOv, mov_OveAX
#define BxImmediate_BrOff8  0x0008 // Relative branch offset byte
#define BxImmediate_BrOff16 0x0009 // Relative branch offset word
#define BxImmediate_BrOff32 0x000a // Relative branch offset dword
#define BxImmediate_1       0x000b // shift counter 1
#define BxImmediate_CL      0x000c // shift counter cl


#define BxPrefix          0x0010 // bit  4
#define BxAnother         0x0020 // bit  5
#define BxRepeatable      0x0040 // bit  6
#define BxRepeatableZF    0x0080 // bit  7
#define BxGroupN          0x0100 // bits 8
#define BxGroup1          BxGroupN
#define BxGroup2          BxGroupN
#define BxGroup3          BxGroupN
#define BxGroup4          BxGroupN
#define BxGroup5          BxGroupN
#define BxGroup6          BxGroupN
#define BxGroup7          BxGroupN
#define BxGroup8          BxGroupN
#define BxGroup9          BxGroupN
#define BxGroupa          BxGroupN


#define BxBranch		   0x000f0000 // // bits 19..16: any branch
#define BxBranch_relative  0x00010000 // // bits 19..16: any branch
#define BxBranch_absolute  0x00020000 // // bits 19..16: any branch

#if BX_DEBUGGER
typedef enum _show_flags {
      Flag_call = 0x1,
      Flag_ret = 0x2,
      Flag_int = 0x4,
      Flag_iret = 0x8,
      Flag_intsig = 0x10
} show_flags_t;
#endif

// Can be used as LHS or RHS.
#define RMAddr(i)  (BX_CPU_CLASS_PTR address_xlation.rm_addr)

#endif  // #ifndef BX_CPU_H
