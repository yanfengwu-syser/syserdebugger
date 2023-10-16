#ifndef _INTEL_DEFINE_H_
#define _INTEL_DEFINE_H_

#define BIT16				0
#define BIT32				1
#define BIT64				2
#define INTEL_MAX_LENGTH	0x10


#define sign_BYTE		0x80
#define sign_WORD		0x8000
#define sign_DWORD		0x80000000
#define sign_QWORD		0x8000000000000000ll

#define shift_BYTE		0x07
#define shift_WORD		0x0f
#define shift_DWORD		0x1f
#define max_BYTE		0xff
#define max_WORD		0xffff
#define max_DWORD		0xffffffff
#define min_BYTE		0x7f
#define min_WORD		0x7fff
#define min_DWORD		0x7fffffff

#define OP_R 1
#define OP_W 2
#define OP_RW 3
#define MAKE_OP_RW_FLAG(f1,f2,f3) ((f1)|((f2)<<2)|((f3)<<4)) 

#ifndef BYTE
typedef unsigned char	BYTE;
typedef unsigned short	WORD;
typedef unsigned long	DWORD;
typedef int				BOOL;

#endif

#ifndef BIT8U

typedef unsigned char	BIT8U;
typedef unsigned short	BIT16U;
typedef unsigned long	BIT32U;
typedef ULONGLONG		BIT64U;

#endif

#ifndef BIT8S
typedef char	BIT8S;
typedef short	BIT16S;
typedef int		BIT32S;

#endif





#ifndef BX_BIG_ENDIAN
	
#define GetValue_b(p) (*(BYTE*)(p))
#define GetValue_w(p) (*(WORD*)(p))
#define GetValue_d(p) (*(DWORD*)(p))
#define GetValue_q(p) (*(QWORD*)(p))

#define SetValue_b(p,value) (*(BYTE*)(p) = (value)) 
#define SetValue_w(p,value) (*(WORD*)(p) = (value)) 
#define SetValue_d(p,value) (*(DWORD*)(p) = (value)) 

#else

#define GetValue_b(p)	(*(BYTE*)(p))
#define GetValue_w(p)	((*(BYTE*)(p)) +\
						(*(BYTE*)(p+1)<<0x08))

#define GetValue_d(p)	((*(BYTE*)(p)) +\
						(*(BYTE*)(p+1)<<0x08) +\
						(*(BYTE*)(p+2)<<0x10) +\
						(*(BYTE*)(p+3)<<0x18))

#define GetValue_q(p)	((*(BYTE*)(p)) +\
						(*(BYTE*)(p+1)<<0x08) +\
						(*(BYTE*)(p+2)<<0x10) +\
						(*(BYTE*)(p+3)<<0x18) +\
						(*(BYTE*)(p+4)<<0x20) +\
						(*(BYTE*)(p+5)<<0x28) +\
						(*(BYTE*)(p+6)<<0x30) +\
						(*(BYTE*)(p+7)<<0x38) +\
						)

#define SetValue_b(p,value)	(*(BYTE*)(p) = (value));
#define SetValue_w(p,value)	(*(BYTE*)(p) = (value));\
							(*(BYTE*)(p+1) = (value)>>0x08);

#define SetValue_d(p,value)	(*(BYTE*)(p) = (value));\
							(*(BYTE*)(p+1) = (value)>>0x08);\
							(*(BYTE*)(p+2) = (value)>>0x10);\
							(*(BYTE*)(p+3) = (value)>>0x18);

#endif

#define MOD_NNN_RM_MOD00 0x00
#define MOD_NNN_RM_MOD01 0x40
#define MOD_NNN_RM_MOD10 0x80
#define MOD_NNN_RM_MOD11 0xc0



//							保护方式下的中断与异常
		
//		助记符			向量号		说明		类型		错误码		源 
#define INTEL_DE_EXCEPTION   0 // Divide Error (fault)
#define INTEL_DB_EXCEPTION   1 // Debug (fault/trap)
#define INTEL_BP_EXCEPTION   3 // Breakpoint (trap)
#define INTEL_OF_EXCEPTION   4 // Overflow (trap)
#define INTEL_BR_EXCEPTION   5 // BOUND (fault)
#define INTEL_UD_EXCEPTION   6
#define INTEL_NM_EXCEPTION   7
#define INTEL_DF_EXCEPTION   8
#define INTEL_TS_EXCEPTION  10
#define INTEL_NP_EXCEPTION  11
#define INTEL_SS_EXCEPTION  12
#define INTEL_GP_EXCEPTION  13
#define INTEL_PF_EXCEPTION  14
#define INTEL_MF_EXCEPTION  16
#define INTEL_AC_EXCEPTION  17
#define INTEL_MC_EXCEPTION	0x12
#define INTEL_XF_EXCEPTION	0x13


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


//INTEL_DE_EXCEPTION //除法出错故障(除零错\除溢出) int 0x00 无错误码 #DE
//INTEL_DB_EXCEPTION //边界检查故障(BOUND指令) int 0x05 无错误码 #BR
//INTEL_BP_EXCEPTION 
//INTEL_OF_EXCEPTION 
//INTEL_BR_EXCEPTION 
//INTEL_UD_EXCEPTION //非法指令编码或操作数 int 0x06 无错误码 #UD
//INTEL_NM_EXCEPTION //协处理器不可用 int 0x07 无错误码 #NM
//INTEL_DF_EXCEPTION //双重故障 int 0x08 errorcode #DF()
//					//系统严重出错，例如:段描述表、页表或中断描述表

//INTEL_TS_EXCEPTION //非法TSS int 0x0a errorcode #TS()
//INTEL_NP_EXCEPTION //段不存在故障 int 0x0b errorcode #NP
//INTEL_SS_EXCEPTION //堆栈段故障 int 0x0c errorcode #SS
//INTEL_GP_EXCEPTION //一般保护故障 int 0x0d errorcode #GP()
//					//所有不引起另一异常的保护违
//					//例都会引起一个一般保护异常
//INTEL_PF_EXCEPTION //页面故障 int 0x0e errorcode #PF(fault-code)
// 					//处理器在CR2寄存器中存放用于
//					//引起异常的访问中的线性地址
//INTEL_MF_EXCEPTION //协处理器错 int 0x10 无错误码 #MF
//INTEL_AC_EXCEPTION //Any data reference in memory	int 0x11 无错误码 #AC
//INTEL_MC_EXCEPTION //Model dependent machine check errors int 0x12 #MC
//INTEL_XF_EXCEPTION //Floating-Point	Numeric ErrorSSE and SSE2 floating-point
//					//instructions. int 0x13 #XF
//INTEL_HF_EXCEPTION //严重错误，处理器停止工作
//					//系统严重出错，例如:段描述表、页表或中断描述表


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

#define I_EAX	0
#define I_ECX	1
#define I_EDX	2
#define I_EBX	3
#define I_ESP	4
#define I_EBP	5
#define I_ESI	6
#define I_EDI	7
#define I_NUL	8

#define I_ES	0
#define I_CS	1
#define I_SS	2
#define I_DS	3
#define I_FS	4
#define I_GS	5
#define I_6S	6
#define I_7S	7

#define I_TR	8
#define I_LDTR	9


#define INTEL_GEG_REG_EAX	0
#define INTEL_GEG_REG_ECX	1
#define INTEL_GEG_REG_EDX	2
#define INTEL_GEG_REG_EBX	3
#define INTEL_GEG_REG_ESP	4
#define INTEL_GEG_REG_EBP	5
#define INTEL_GEG_REG_ESI	6
#define INTEL_GEG_REG_EDI	7

#define INTEL_SEG_REG_ES	0
#define INTEL_SEG_REG_CS	1
#define INTEL_SEG_REG_SS	2
#define INTEL_SEG_REG_DS	3
#define INTEL_SEG_REG_FS	4
#define INTEL_SEG_REG_GS	5
#define INTEL_SEG_REG_6S	6
#define INTEL_SEG_REG_7S	7

#define INTEL_SEG_REG_TR	8
#define INTEL_SEG_REG_LDTR	9

#define INTEL_SEG_REG_NULL	0x0f

#define R_M		0x0200
#define D_64 0x8000000
#define F_64 0x4000000
#define O_64 0x10000000
#define I_64 0x20000000

#define  C_ESC_GROUP_TYPE   (0x100)
#define  C_GROUP_0_TYPE   (0x200)
#define  C_GROUP_1_TYPE   (0x400)
#define  C_GROUP_2_TYPE   (0x800)
#define  C_GROUP_3_TYPE   (0x1000)
#define  C_GROUP_4_TYPE   (0x2000)
#define  C_GROUP_5_TYPE   (0x4000)
#define  C_GROUP_3DNOW_TYPE   (0x8000)

#define Immediate___      0x00ff // bits 3..0: any immediate

typedef enum _IMMEDIATE___
{
	Immediate_,			// 8 bits regardless
	Immediate_1,		// shl eax,1
	Immediate_CL,		// shl eax,cl
	Immediate_Ib,       // 8 bits regardless
	Immediate_sIb,		// sign extend to OS size
	Immediate_zIb,		// zero extend to OS size
	Immediate_Iv,       // 16 or 32 depending on OS size
	Immediate_Iw,       // 16 bits regardless
	Immediate_Iz,       // Word for 16-bit operand-size or doubleword for 32 or 64-bit operand-size
	Immediate_IvIw,     // call_Ap
	Immediate_IwIb,     // enter_IwIb
	Immediate_O,        // mov_ALOb, mov_ObAL, mov_eAXOv, mov_OveAX
	Immediate_BrOff8,   // Relative branch offset byte
	Immediate_BrOff16,  // Relative branch offset word
	Immediate_BrOff32,  // Relative branch offset dword
	Immediate_Jb,	    // Relative branch offset byte
	Immediate_Jv,	    // Relative branch offset word/dword
	

	//PREFIX_ES,		// 0x26 segment override prefix.
	//PREFIX_CS,		// 0x2e segment override prefix.
	//PREFIX_SS,		// 0x36 segment override prefix.
	//PREFIX_DS,		// 0x3e segment override prefix.
	//PREFIX_FS,		// 0x64 segment override prefix.
	//PREFIX_GS,		// 0x65 segment override prefix.
	//PREFIX_66,		// 0x66 Operand-size override prefix.
	//PREFIX_67,		// 0x67 Address-size override prefix.
	//PREFIX_F0,		// 0xf0 LOCK
	//PREFIX_F2,		// 0xf2 REPNE/REPNZ (used only with string instructions).
	//PREFIX_F3,		// 0xf3 REPE/REPZ (use only with string instructions).
	//
	//STRING_Move,	// movs stos lods ins outs (use only with string instructions).
	//STRING_Comp,	// cmps scan (use only with string instructions).

	//Extended_2byte, // pop cs (use only with two byte instructions).
	//Extended_Group, // mov al,0x80 (use only with extent opcode byte instructions).
	//Extended_Float, // fld [bx]  (use only with float exten byte instructions).
	//Extended_Group1,// prefetch (use only with extent opcode byte instructions).

	//OPCODE_UD,
};


typedef enum _OPCODETYPE
{
	//----------------------------------------------
	//----------------------------------------------
	C_NULL,
	C_ES,C_CS,C_SS,C_DS,C_FS,C_GS, // 0x26 0x2e 0x36 0x3e 0x64 0x65 segment override
								   // 0x2e 0x3e branch hint prefixes
								   // 0x2e Branch not taken (used only with Jcc instructions).
								   // 0x3e Branch taken (used only with Jcc instructions).
	C_REX_PREFIX,
   //----------------------------------------------
    C_OPER, // 0x66 Operand-size override prefix.
	C_ADDR, // 0x67 Address-size override prefix.
	C_LOCK, // 0xf0 LOCK
	C_REPN, // 0xf2 REPNE/REPNZ (used only with string instructions).
	C_REPZ, // 0xf3 REPE/REPZ (use only with string instructions).

	//----------------------------------------------
	
	C_GRP,C_ESC,C_2BYTE,C_GRP1,C_GRP2,C_3BYTE_0X38,C_3BYTE_0X3A,C_GRP3,C_GRP4,C_GRP5,C_3DNOW_GRP,C_GRP6,
	//----------------------------------------------

	C_MOVS,C_STOS,C_LODS,C_INS,C_OUTS,
	C_CMPS,C_SCAS,
	C_IN,C_OUT,

	//----------------------------------------------
	C_LES,C_LCS,C_LSS,C_LDS,C_LFS,C_LGS,C_POPCNT,C_LZCNT,
	//----------------------------------------------
	C_LOOPNZ,C_LOOPZ,C_LOOP,C_JCXZ,C_JMP,
	//----------------------------------------------
	
	C_MOVUPS,C_MOVUSS,C_MOVLPS,C_UNPCKLPS,C_UNPCKHPS,C_MOVHLPS,C_MOVHPS,

	C_CVTPS2PS,	C_CVTPS2SS,	C_CVTTPS2PI,
	C_CVTTPS2SI,C_CVTPS2PI,	C_CVTPS2SI,
	C_SQRTPS,	C_SQRTSS,
	C_RSQRTPS,	C_RSQRTSS,
	C_RCPPS,	C_RCPSS,
	C_ADDPS,	C_ADDSS,
	C_MULPS,	C_MULSS,
	C_SUBPS,	C_SUBSS,
	C_MINPS,	C_MINSS,
	C_DIVPS,	C_DIVSS,
	C_MAXPS,	C_MAXSS,
	C_CMPPS,	C_CMPSS,
	//----------------------------------------------
	//----------------------------------------------
	C_ADD,C_OR,C_ADC,C_SBB,C_AND,C_SUB,C_XOR,C_CMP,
	C_ROL,C_ROR,C_RCL,C_RCR,C_SHL,C_SHR,C_SAL,C_SAR,
	//----------------------------------------------
	//----------------------------------------------

	C_DAA,C_DAS,C_AAA,C_AAS,
	C_INC,C_DEC,C_PUSH,C_POP,C_PUSHA,C_POPA,
	C_BOUND,C_ARPL,C_IMUL,C_MOVSXD,
	
	//----------------------------------------------
	//----------------------------------------------

	C_JtO,
	C_JfO,
	C_JtC,
	C_JfC,
	C_JtZ,
	C_JfZ,
	C_JfA,
	C_JtA,
	C_JtS,
	C_JfS,
	C_JtP,
	C_JfP,
	C_JtL,
	C_JfL,
	C_JfG,
	C_JtG,

	C_SETtO,
	C_SETfO,
	C_SETtC,
	C_SETfC,
	C_SETtZ,
	C_SETfZ,
	C_SETfA,
	C_SETtA,
	C_SETtS,
	C_SETfS,
	C_SETtP,
	C_SETfP,
	C_SETtL,
	C_SETfL,
	C_SETfG,
	C_SETtG,
	C_CMOVtO,
	C_CMOVfO,
	C_CMOVtC,
	C_CMOVfC,
	C_CMOVtZ,
	C_CMOVfZ,
	C_CMOVfA,
	C_CMOVtA,
	C_CMOVtS,
	C_CMOVfS,
	C_CMOVtP,
	C_CMOVfP,
	C_CMOVtL,
	C_CMOVfL,
	C_CMOVfG,
	C_CMOVtG,

	//----------------------------------------------
	//----------------------------------------------

	C_TEST,C_NOP,C_XCHG,C_MOV,C_LEA,C_CBW,C_CWD,C_CALL,C_WAIT,C_XCHG_NOP,

	C_PUSHF,C_POPF,C_SAHF,C_LAHF,

	C_RET,C_ENTER,C_LEAVE,C_RETF,C_INT1,C_INT3,C_INT,C_INTO,C_IRET,

	C_AAM,C_AAD,

	C_SALC,C_XLAT,

	C_HLT,C_CMC,C_CLC,C_STC,C_CLI,C_STI,C_CLD,C_STD,

	C_NOT,C_NEG,C_MUL,C_DIV,C_IDIV,
	// One-byte opcode table completed.


	//FPU Instruction
    C_FSTCW,C_FSTENV,C_FCLEX,C_FINIT,C_FSAVE,C_FSTSW,C_FWAIT,


	C_FADD,C_FMUL,C_FCOM,C_FCOMP,C_FSUB,C_FSUBR,C_FDIV,C_FDIVR,

    C_FLD,C_FXCH,C_FNOP,C_FCHS,C_FABS,C_FTST,
	C_FLD1,C_FLDL2T,C_FLDL2E,C_FLDPI,C_FLDLG2, C_FLDLN2,

    C_FLDZ,
    C_F2XM1,
    C_FPTAN,
    C_FPATAN, 
    C_FXTRACT,
    C_FPREM1,
    C_FDECSTP,
    
    C_FINCSTP,
    C_FYL2XP1,
    C_FSQRT,

	C_FSINCOS,
	C_FRNDINT,
	C_FSCALE,
	C_FSIN,
	C_FCOS,

	C_FLDCW, 
	C_FLDENV,
	C_FNSTCW,
	C_FNSTENV,
	C_FST,
	C_FSTP,
	C_FCMOVB,
	C_FCMOVE,
	C_FCMOVBE,
	C_FCMOVU,
	C_FUCOMPP,
	
	C_FIADD,C_FICOM,C_FICOMP,C_FIDIV,C_FIDIVR,C_FIMUL,C_FISUB,C_FISUBR,

	C_FCMOVNB,
	C_FCMOVNE,
	C_FCMOVNBE,
	C_FCMOVNU,
	C_FNCLEX,
	C_FNINIT,
	C_FUCOMI,
	C_FCOMI,
	C_FILD,
	C_FISTTP,
	C_FIST,
	C_FISTP,
	
	C_FFREE,
	C_FUCOM,
	C_FUCOMP,

	C_FNSAVE,
	C_FNSTSW,
	C_FRSTOR,
	C_FADDP,
	C_FMULP,
	C_FCOMPP,
	C_FSUBRP,
	C_FSUBP,
	C_FDIVRP,
	C_FDIVP,

	C_FUCOMIP,
	C_FCOMIP,
	C_FBLD,
	C_FBSTP,

	C_FXAM,
	C_FLD2T,
	C_FYL2X,
	C_FPREM,

	//386 CPU Instruction
	//----------------------------------------------
	//----------------------------------------------
	C_SLDT,C_STR,C_LLDT,C_LTR,C_VERR,C_VERW,
	C_SGDT,C_SIDT,C_LGDT,C_LIDT,C_SMSW,C_LMSW,
	//----------------------------------------------
	//----------------------------------------------

 	C_LAR,
	C_LSL,
	C_MOVZX,
	C_MOVSX,

	C_RSM,//0F AA RSM Resume operation of interrupted program
		  //Resume from System Management Mode
	C_BT,
	C_BTR,
	C_BTS,
	C_BTC,
	C_BSF,
	C_BSR,
	C_SHLD,
	C_SHRD,
	C_CMPXCHG_XBTS,
	C_CMPXCHG_IBTS,

	C_CMPXCHG,
	C_XADD,
	C_BSWAP,//Byte Swap
	C_CLTS,
	C_CPUID, //0F A2 CPUID Returns processor identification and feature information
			//	to the EAX, EBX, ECX, and EDX registers, according to
			//	the input value entered initially in the EAX register

	C_MOVAPS,				
	C_CVTPI2PS,
	C_MOVNTPS,	
	C_UCOMISS,	
	C_COMISS,	
	
	C_MOVMSKPS,
	C_ANDPS,	
	C_ANDNPS,	
	C_ORPS,	
	C_XORPS,	
	C_XORPD,
	C_MOVNTI,
	C_PINSRW,
	C_PEXTRW,
	C_SHUFPS,

	C_PSRLW,	
	C_PSRLD,	
	C_PSRLQ,	
	C_PADDQ,	
	C_PMULLW,	
	C_MOVQ,	
	C_PMOVMSKB,

	C_CVTPS2PD,
	C_CVTDQ2PS,

	C_PSHUFW,	
	C_PCMPEQB,	
	C_PCMPEQW,	
	C_PCMPEQD,				
	C_EMMS,		


	C_PREFETCH,
	C_FXSAVE,
	C_FXRSTOR,
	C_LDMXCSR,
	C_STMXCSR,
	C_XSAVE,
	C_XRSTOR,

	C_WRMSR, //0F 30 WRMSR Write the value in EDX:EAX to MSR specified by ECX
	C_RDTSC, //0F 31 RDTSC Read time-stamp counter into EDX:EAX
	C_RDMSR, //0F 32 RDMSR Load MSR specified by ECX into EDX:EAX
	C_RDPMC, //0F 33 RDPMC Read performance-monitoring counter specified by ECX	into EDX:EAX
	C_SYSCALL,
	C_SYSRET,
	C_SYSENTER, //0F 34 Fast call to privilege level 0 system procedures
	C_SYSEXIT, //0F 35 Fast return to privilege level 3 user code
	C_GETSEC,
	C_INVD, //0F 08 INVD Flush internal caches; initiate flushing of external caches.
	C_WBINVD, //0F 09 WBINVD Write back and flush Internal caches; initiate writing-back
			  //and flushing of external caches

	C_INVLPG,
	C_CMPXCHG8B,
	C_CMPXCHG16B,


	C_PUNPCKLBW,	
	C_PUNPCKLWD,	
	C_PUNPCKLDQ,	
	C_PACKSSWB,	
	C_PCMPGTB,		
	C_PCMPGTW,		
	C_PCMPGTD,		
	C_PACKUSWB,	

	C_PUNPCKHBW,	
	C_PUNPCKHWD,	
	C_PUNPCKHDQ,	
	C_PACKSSDW,	
	C_PUNPCKLQDQ,	
	C_PUNPCKHQDQ,	
	C_MOVD,		

	C_PSUBB,
	C_PSUBW,
	C_PSUBD,
	C_PSUBQ,
	C_PADDB,
	C_PADDW,
	C_PADDD,

	C_PSUBUSB,	
	C_PSUNUSW,	
	C_PMINUB,	
	C_PAND,	
	C_PADDUSB,	
	C_PADDUSW,	
	C_PMAXUB,	
	C_PANDN,	

	C_PAVGB,	
	C_PSRAW,	
	C_PSRAD,	
	C_PAVGW,	
	C_PMULHUW,	
	C_PMULHW,	
	C_CVTPD2DQ,
	C_MOVNTQ,	

	C_PSUBSB,	
	C_PSUBSW,	
	C_PMINSW,	
	C_POR,		
	C_PADDSB,	
	C_PADDSW,	
	C_PMAXSW,	
	C_PXOR,	

	C_PSLLW,	
	C_PSLLD,	
	C_PSLLQ,	
	C_PMULUDQ,	
	C_PMADDWD,	
	C_PSADBW,	
	C_MASKMOVQ,

	C_CLFLUSH,
	C_LFENCE, 
	C_MFENCE, 
	C_SFENCE, 
	C_UD2,
	C_VMPTRLD,
	C_VMCLEAR,
	C_VMXON,
	C_VMPTRST,
	C_VMCALL,
	C_VMLAUNCH,
	C_VMRESUME,
	C_VMXOFF,
	C_VMREAD,
	C_VMWRITE,
	C_MONITOR,
	C_MWAIT,
	C_SWAPGS,
	C_PSHUFB,
	C_PHADDW,
	C_PHADDD,
	C_PHADDSW,
	C_PMADDUDSW,
	C_PHSUBW,
	C_PHSUBD,
	C_PHSUBSW,
	C_PSIGNB,
	C_PSIGNW,
	C_PSIGND,
	C_PMULHRSW,
	C_PABSB,
	C_PABSW,
	C_PABSD,
	C_PALIGNR,
	C_PSHUFD,	
	C_PSHUFHW,
	C_PSHUFLW,
	C_HADDPD,	
	C_HADDPS,	
	C_HSUBPD,	
	C_HSUBPS,	
	C_MOVDQA,	
	C_MOVDQU,	
	C_MOVMSKPD,
	C_SQRTPD,
	C_SQRTSD,
	C_ANDPD,
	C_ANDNPD,
	C_ORPD,
	C_ADDPD,
	C_ADDSD,
	C_MULPD,
	C_MULSD,
	C_CVTPD2PS,
	C_CVTSD2SS,
	C_CVTSS2SD,
	C_CVTPS2DQ,
	C_CVTTPS2DQ,
	C_SUBPD,
	C_SUBSD,
	C_MINPD,
	C_MINSD,
	C_DIVPD,
	C_DIVSD,
	C_MAXPD,
	C_MAXSD,
	C_MOVUPD,	
	C_MOVSD,	
	C_MOVSS,	
	C_MOVLPD,	
	C_MOVDDUP,
	C_MOVSLDUP,
	C_UNPCKLPD,
	C_UNPCKHPD,
	C_MOVHPD,
	C_MOVSHDUP,
	C_MOVLHPS,
	C_MOVAPD,
	C_CVTPI2PD,
	C_CVTSI2SD,
	C_CVTSI2SS,
	C_MOVNTPD,
	C_MOVNTSD,
	C_MOVNTSS,
	C_CVTTPD2PI,
	C_CVTTSD2SI,
	C_CVTTSS2SI,
	C_CVTPD2PI,
	C_CVTSD2SI,
	C_CVTSS2SI,
	C_UCOMISD,
	C_COMISD,
	C_ADDSUBPD,
	C_ADDSUBPS,
	C_MOVDQ2Q,
	C_MOVQ2DQ,
	C_PSUBUSW,

	C_CVTTPD2DQ,
	C_CVTDQ2PD,
	C_MOVNTDQ,
	C_LDDQU,
	C_MASKMOVDQU,	
	C_PMADDUBSW,
	C_PMOVSXBW,
	C_PMOVSXBD,
	C_PMOVSXBQ,
	C_PMOVSXWD,
	C_PMOVSXWQ,
	C_PMOVSXDQ,
	C_PMULDQ,
	C_PCMPEQQ,
	C_MOVNTDQA,
	C_PACKUSDW,
	C_PMOVZXBW,
	C_PMOVZXBD,
	C_PMOVZXBQ,
	C_PMOVZXWD,
	C_PMOVZXWQ,
	C_PMOVZXDQ,
	C_PCMPGTQ,
	C_PMINSB,
	C_PMINSD,
	C_PMINUW,
	C_PMINUD,
	C_PMAXSB,
	C_PMAXSD,
	C_PMAXUW,
	C_PMAXUD,
	C_PMULLD,
	C_PHMINPOSUW,	
	C_CRC32,
	C_PBLENDVB,
	C_BLENDVPS,
	C_BLENDVPD,
	C_PTEST,
	C_ROUNDPS,
	C_ROUNDPD,
	C_ROUNDSS,
	C_ROUNDSD,
	C_BLENDPS,
	C_BLENDPD,
	C_PBLENDW,
	C_PEXTRB,
	C_PEXTRD,
	C_PEXTRQ,
	C_EXTRACTPS,
	C_PINSRB,
	C_INSERTPS,
	C_PINSRD,
	C_DPPS,
	C_DPPD,
	C_MPSADBW,
	C_PCLMULQDQ,
	C_PCMPESTRM,
	C_PCMPESTRI,
	C_PCMPISTRM,
	C_PCMPISTRI,
	C_SHUFPD,
	C_INVEPT,
	C_INVVPID,
	C_MOVBE,
	C_AESKEYGENASSIST,
	C_AESIMC,
	C_AESENC,
	C_AESENCLAST,
	C_AESDEC,
	C_AESDECLAST,
C_XGETBV,
C_XSETBV,
C_RDTSCP,
C_PAUSE,
C_CMPPD,
C_CMPSD,
C_PSRLDQ,
C_PSLLDQ,


//AMD CPU INSTRUCTION

C_VMRUN,	
C_VMMCALL,
C_VMLOAD,	
C_VMSAVE,	
C_STGI,	
C_CLGI,	
C_SKINIT,	
C_INVLPGA,
C_EXTRQ,


//AMD 3DNOW! INSTRUCTION
C_PI2FW,
C_PI2FD,
C_PF2IW,
C_PF2ID,
C_PFNACC,
C_PFPNACC,
C_PFCMPGE,
C_PFMIN,
C_PFRCP,
C_PFRSQRT,
C_PFSUB,
C_PFADD,
C_PFCMPGT,
C_PFMAX,
C_PFRCPIT1,
C_PFRSQIT1,
C_PFSUBR,
C_PFACC,
C_PFCMPEQ,
C_PFMUL,
C_PFRCPIT2,
C_PMULHRW,
C_PSWAPD,
C_PAVGUSB,
C_3DNOW,
// Two-byte opcode table completed.
//---------------------------------------
	C_DBYTE,
	C_DWORD,
	C_DDWORD,
	C_TAIL

};

	
/*

A.1. KEY TO ABBREVIATIONS

Operands are identified by a two-character code of the form Zz. The first character, an uppercase
letter, specifies the addressing method; the second character, a lowercase letter, specifies the
type of operand.

A.1.1. Codes for Addressing Method

The following abbreviations are used for addressing methods:

A	Direct address. The instruction has no ModR/M byte; the address of the operand is en-coded
	in the instruction; and no base register, index register, or scaling factor can be
	applied (for example, far JMP (EA)).

C	The reg field of the ModR/M byte selects a control register (for example,
	MOV (0F20, 0F22)).

D	The reg field of the ModR/M byte selects a debug register (for example,
	MOV (0F21,0F23)).

E	A ModR/M byte follows the opcode and specifies the operand. The operand is either a
	general-purpose register or a memory address. If it is a memory address, the address is
	computed from a segment register and any of the following values: a base register, an
	index register, a scaling factor, a displacement.

F	EFLAGS Register.

G	The reg field of the ModR/M byte selects a general register (for example, AX (000)).

I	Immediate data. The operand value is encoded in subsequent bytes of the instruction.

J	The instruction contains a relative offset to be added to the instruction pointer register
	(for example, JMP (0E9), LOOP).

M	The ModR/M byte may refer only to memory (for example, BOUND, LES, LDS, LSS,
	LFS, LGS, CMPXCHG8B).

O	The instruction has no ModR/M byte; the offset of the operand is coded as a word or
	double word (depending on address size attribute) in the instruction. No base register,
	index register, or scaling factor can be applied (for example, MOV (A0朅3)).

P	The reg field of the ModR/M byte selects a packed quadword MMX?technology reg-ister.

Q	A ModR/M byte follows the opcode and specifies the operand. The operand is either
	an MMX?technology register or a memory address. If it is a memory address, the ad-dress
	is computed from a segment register and any of the following values: a base reg-ister,
	an index register, a scaling factor, and a displacement.

R	The mod field of the ModR/M byte may refer only to a general register (for example,
	MOV (0F20-0F24, 0F26)).

S	The reg field of the ModR/M byte selects a segment register (for example, MOV
	(8C,8E)).

T	The reg field of the ModR/M byte selects a test register (for example, MOV
	(0F24,0F26)).

V	The reg field of the ModR/M byte selects a packed SIMD floating-point register.

W	An ModR/M byte follows the opcode and specifies the operand. The operand is either
	a SIMD floating-point register or a memory address. If it is a memory address, the ad-dress
	is computed from a segment register and any of the following values: a base reg-ister,
	an index register, a scaling factor, and a displacement

X	Memory addressed by the DS:SI register pair (for example, MOVS, CMPS, OUTS, or
	LODS).

Y	Memory addressed by the ES:DI register pair (for example, MOVS, CMPS, INS,
	STOS, or SCAS).

  
A.1.2. Codes for Operand Type

The following abbreviations are used for operand types:

a	Two one-word operands in memory or two double-word operands in memory, depend-ing
	on operand-size attribute (used only by the BOUND instruction).

b	Byte, regardless of operand-size attribute.

c	Byte or word, depending on operand-size attribute.

d	Doubleword, regardless of operand-size attribute.

dq	Double-quadword, regardless of operand-size attribute.

p	32-bit or 48-bit pointer, depending on operand-size attribute.

pi	Quadword MMX?technology register (e.g. mm0)

ps	128-bit packed FP single-precision data.

q	Quadword, regardless of operand-size attribute.

s	6-byte pseudo-descriptor.

ss	Scalar element of a 128-bit packed FP single-precision data.

si	Doubleword integer register (e.g., eax)

v	Word or doubleword, depending on operand-size attribute.

w	Word, regardless of operand-size attribute.

A.1.3. Register Codes

When an operand is a specific register encoded in the opcode, the register is identified by its
name (for example, AX, CL, or ESI). The name of the register indicates whether the register is
32, 16, or 8 bits wide. A register identifier of the form eXX is used when the width of the register
depends on the operand-size attribute. For example, eAX indicates that the AX register is used
when the operand-size attribute is 16, and the EAX register is used when the operand-size at-tribute
is 32.

*/

typedef enum _OPERATOR_DATA_TYPE
{
	D__NONE,
	
	// The reg field of the ModR/M byte selects a control register (for example,
	// MOV (0F20, 0F22)).
	D__Cd,

	// The reg field of the ModR/M byte selects a debug register (for example,
	// MOV (0F21,0F23)).
	D__Dd,

	// The reg field of the ModR/M byte selects a test register (for example,
	// MOV (0F24,0F26)).
	D__Td,
	
	// EFLAGS Register.
	D__Fv,
	
	// The reg field of the ModR/M byte selects a general register (for example, AX (000)).	
	D__Gb,D__rGb,D__wGb,D__rwGb,
	D__Gw,D__rGw,D__wGw,D__rwGw,
	D__Gv,D__rGv,D__wGv,D__rwGv,
	D__Gd,D__rGd,D__wGd,D__rwGd,
	D__Gy,D__rGy,D__wGy,D__rwGy,
	// Immediate data. The operand value is encoded in subsequent bytes of the instruction.
	D__Ib,D__Ib2,D__sIb,D__Iw,D__Id,D__Iv,D__1,D__Iz,
	// The instruction contains a relative offset to be added to the instruction pointer register
	// (for example, JMP (0E9), LOOP).
	D__Jb,D__Jz,

	// The instruction has no ModR/M byte; the offset of the operand is coded as a word or
	// double word (depending on address size attribute) in the instruction. No base register,
	// index register, or scaling factor can be applied (for example, MOV (A0-A3)).
	D__Ob,D__rOb,D__wOb,D__rwOb,
	D__Ov,D__rOv,D__wOv,D__rwOv,

	// Direct address. The instruction has no ModR/M byte; the address of the operand is en-coded
	// in the instruction; and no base register, index register, or scaling factor can be
	// applied (for example, far JMP (EA)).	
	D__Ap,

	
	// The reg field of the ModR/M byte selects a packed quadword MMX?technology reg-ister.
	D__Pd,D__rPd,D__wPd,D__rwPd,
	D__Pq,D__rPq,D__wPq,D__rwPq,
	D__Ppi,D__rPpi,D__wPpi,D__rwPpi,

	// The mod field of the ModR/M byte may refer only to a general register (for example,
	// MOV (0F20-0F24, 0F26)).
	D__Rd,
	D__Ry,
	// The reg field of the ModR/M byte selects a segment register (for example, MOV
	//(8C,8E)).
	D__Sw,

	//unkown opdata
	D__NTA,

	// The reg field of the ModR/M byte selects a test register (for example, MOV
	// (0F24,0F26)).
	D__T0,D__T1,D__T2,D__T3,D__T4,D__T5,D__T6,D__T7,

	// The reg field of the ModR/M byte selects a packed SIMD floating-point register.


	// Memory addressed by the DS:SI register pair (for example, MOVS, CMPS, OUTS, or
    // LODS).
	D__Xb,D_rXb,D_wXb,
	D__Xw,D_rXw,D_wXw,
	D__Xv,D_rXv,D_wXv,
	D__Xd,D_rXd,D_wXd,
	D__Xz,D_rXz,D_wXz,
	
	// Memory addressed by the ES:DI register pair (for example, MOVS, CMPS, INS,
	//STOS, or SCAS).
	D__Yb,D__rYb,D__wYb,
	D__Yw,D__rYw,D__wYw,
	D__Yv,D__rYv,D__wYv,
	D__Yd,D__rYd,D__wYd,
	D__Yz,D__rYz,D__wYz,
	
	
	// When an operand is a specific register encoded in the opcode, the register is identified by its
	// name (for example, AX, CL, or ESI). The name of the register indicates whether the register is
	// 32, 16, or 8 bits wide. A register identifier of the form eXX is used when the width of the register
	// depends on the operand-size attribute. For example, eAX indicates that the AX register is used
	// when the operand-size attribute is 16, and the EAX register is used when the operand-size at-tribute
	// is 32.	

	D__AL,D__CL,D__DL,D__BL,D__AH,D__CH,D__DH,D__BH,
	D__AL_r8L,D__CL_r9L,D__DL_r10L,D__BL_r11L,D__AH_r12L,D__CH_r13L,D__DH_r14L,D__BH_r15L,
	D__AX,D__CX,D__DX,D__BX,D__SP,D__BP,D__SI,D__DI,

	D__eAX,D__eCX,D__eDX,D__eBX,D__eSP,D__eBP,D__eSI,D__eDI,

	D__rAX_r8,D__rCX_r9,D__rDX_r10,D__rBX_r11,D__rSP_r12,D__rBP_r13,D__rSI_r14,D__rDI_r15,

	D__rAX,D__rCX,D__rDX,D__rBX,D__rSP,D__rBP,D__rSI,D__rDI,
#define D__eX	D__eAX

	D__EAX,D__ECX,D__EDX,D__EBX,D__ESP,D__EBP,D__ESI,D__EDI,
	D__RAX_EAX_R8_R8D,D__RCX_ECX_R9_R9D,D__RDX_EDX_R10_R10D,D__RBX_EBX_R11_R11D,D__RSP_ESP_R12_R12D,D__RBP_EBP_R13_R13D,D__RSI_ESI_R14_R14D,D__RDI_EDI_R15_R15D,
	D__ES,D__CS,D__SS,D__DS,D__FS,D__GS,

	D__st,
	D__st0,D__st1,D__st2,D__st3,D__st4,D__st5,D__st6,D__st7,

	
	// A ModR/M byte follows the opcode and specifies the operand. The operand is either a
	// general-purpose register or a memory address. If it is a memory address, the address is
	// computed from a segment register and any of the following values: a base register, an
	// index register, a scaling factor, a displacement.		
	D__Eb,D__rEb,D__wEb,D__rwEb,
	D__Ew,D__rEw,D__wEw,D__rwEw,
	D__Ev,D__rEv,D__wEv,D__rwEv,
	D__Ed,D__rEd,D__wEd,D__rwEd,
	D__Ep,D__rEp,D__wEp,D__rwEp,
	D__Ey,D__rEy,D__wEy,D__rwEy,
	// The ModR/M byte may refer only to memory (for example, LEA,BOUND, LES, LDS, LSS,
	// LFS, LGS, CMPXCHG8B).
	D__M,D__rM,D__wM,D__rwM,
	D__Ma,D__rMa,D__wMa,D__rwMa,
	D__Mb,D__rMb,D__wMb,D__rwMb,
	D__Mp,D__rMp,D__wMp,D__rwMp,
	D__Ms,D__rMs,D__wMs,D__rwMs,
	D__Mq,D__wMq,D__rMq,D__rwMq,
	D__MqMdq,D__wMqMdq,D__rMqMdq,D__rwMqMdq,

	D__Mps,D__wMps,D__rMps,D__rwMps,
	D__Mpd,D__wMpd,D__rMpd,D__rwMpd,
	D__Mdq,D__wMdq,D__rMdq,D__rwMdq,	
	D__Md,D__rMd,D__wMd,D__rwMd,
	D__Mw,D__rMw,D__wMw,D__rwMw,
	//D__MwRv,D__rMwRv,D__wMwRv,D__rwMwRv,
	D__wMwRv,
	D__Mv,D__rMv,D__wMv,D__rwMv,
	D__My,D__rMy,D__wMy,D__rwMy,
	
	// A ModR/M byte follows the opcode and specifies the operand. The operand is either
	// an MMX?technology register or a memory address. If it is a memory address, the ad-dress
	// is computed from a segment register and any of the following values: a base reg-ister,
	// an index register, a scaling factor, and a displacement.
	D__Qd,D__wQd,D__rQd,D__rwQd,
	D__Qq,D__wQq,D__rQq,D__rwQq,
	D__Qpi,D__wQpi,D__rQpi,D__rwQpi,
	D__Qdq,D__wQdq,D__rQdq,D__rwQdq,

	// An ModR/M byte follows the opcode and specifies the operand. The operand is either
	// a SIMD floating-point register or a memory address. If it is a memory address, the ad-dress
	// is computed from a segment register and any of the following values: a base reg-ister,
	// an index register, a scaling factor, and a displacement


	D__Vpd,D__rVpd,D__wVpd,D__rwVpd,
	D__Vdq,D__rVdq,D__wVdq,D__rwVdq,
	D__Vsd,D__wVsd,D__rVsd,D__rwVsd,
	D__Vq,D__wVq,D__rVq,D__rwVq,
	D__Vps,D__wVps,D__rVps,D__rwVps,
	D__Vss,D__wVss,D__rVss,D__rwVss,
	D__Vy,D__wVy,D__rVy,D__rwVy,

	D__Wsd,D__wWsd,D__rWsd,D__rwWsd,
	D__Wdq,D__rWdq,D__wWdq,D__rwWdq,
	D__Wpd,D__wWpd,D__rWpd,D__rwWpd,
	D__Wq,D__wWq,D__rWq,D__rwWq,
	D__Wps,D__wWps,D__rWps,D__rwWps,
	D__Wss,D__wWss,D__rWss,D__rwWss,

	D__Ups,D__wUps,D__rUps,D__rwUps,
	D__Upd,D__wUpd,D__rUpd,D__rwUpd,
	D__Uq,D__wUq,D__rUq,D__rwUq,
	D__Udq,D__wUdq,D__rUdq,D__rwUdq,

	D__Nq,D__wNq,D__rNq,D__rwNq,

	//浮点数据类型
	D__word_int,
	D__dword_int,
	D__qword_int,
	D__single_real,
	D__double_real,
	D__extend_real,
	D__packed_BCD,
	D__2b,
	D__14_28b,
	D__98_108b,

	//为虚拟执行而补充的操作数类型
	D__tO,D__fO,D__tC,D__fC,D__tZ,D__fZ,D__fA,D__tA,
	D__tS,D__fS,D__tP,D__fP,D__tL,D__fL,D__fG,D__tG,
	D__LOOPNZ,	D__LOOPZ,	D__LOOP,	D__JCXZ,	D__JMP,

	//为正汇编而补充的操作数类型
	D_NEAR,D_MFAR,  // The ModR/M byte may refer only to memory or word register for call and jmp
	D_DBYTE, //正汇编命令 db
	D_DWORD, //正汇编命令 dw 
	D_DDWORD,//正汇编命令 dd 
	D_STRING,//正汇编命令 db "string" 
}OPCODETYPE;



#endif
