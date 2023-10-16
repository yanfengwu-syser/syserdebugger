#ifndef _X86_DEFINE_H_
#define _X86_DEFINE_H_
#include "LocalAPIC.h"
//标志寄存器位段定义
struct EFLAG_REG
{
	bool CF		:1;		//0
	bool b1		:1;		//1 
	bool PF		:1;		//2
	bool b3		:1;		//3
	bool AF		:1;		//4
	bool b5		:1;		//5
	bool ZF		:1;		//6
	bool SF		:1;		//7
	bool TF		:1;		//8
	bool IF		:1;		//9
	bool DF		:1;		//10
	bool OF		:1;		//11
	UINT IOPL	:2;		//12--13
	bool NT		:1;		//14
	bool bf		:1;		//15
	bool RF		:1;		//16
	bool VM		:1;		//17
	bool AC		:1;		//18
	bool VIF	:1;		//19
	bool VIP	:1;		//20
	bool ID		:1;		//21
	UINT Reserve:10;	//22--23
};

struct FPU_STATUS_REG
{
	WORD IE:1;
	WORD DE:1;
	WORD ZE:1;
	WORD OE:1;
	WORD UE:1;
	WORD PE:1;
	WORD SF:1;
	WORD ES:1;
	WORD C0:1;
	WORD C1:1;
	WORD C2:1;
	WORD TOP:3;
	WORD C3:1;
	WORD B:1;
};

struct FPU_TAG_WORD_REG
{
	WORD TAG0:2;
	WORD TAG1:2;
	WORD TAG2:2;
	WORD TAG3:2;
	WORD TAG4:2;
	WORD TAG5:2;
	WORD TAG6:2;
	WORD TAG7:2;
};

struct FPU_CONTROL_REG
{
	WORD IM:1;
	WORD DM:1;
	WORD ZM:1;
	WORD OM:1;
	WORD UM:1;
	WORD PM:1;
	WORD Reserved1:2;
	WORD PC:2;
	WORD RC:2;
	WORD X:1;
	WORD Reserved2:3;
};


typedef struct _FPU_SAVE_STATUS
{
	WORD ControlWord;
	WORD Reserved1;
	WORD StatusWord;
	WORD Reserved2;
	WORD TagWord;
	WORD Reserved3;
	DWORD InstructionPointer;
	DWORD Zero:5;
	DWORD Opcode:11;
	DWORD InstructionPointerSelector:16;
	DWORD OperandPointerOffset;
	WORD Reserved4;
	WORD OperandPointerSelector;
	BYTE Reg[8][10];
}FPU_SAVE_STATUS,*PFPU_SAVE_STATUS;

struct DEBUG_CTRL_REG
{
	bool	L0	:1;
	bool	G0	:1;
	bool	L1	:1;
	bool	G1	:1;
	bool	L2	:1;
	bool	G2	:1;
	bool	L3	:1;
	bool	G3	:1;
	bool	LE	:1;
	bool	GE	:1;	
	bool		:3;
	bool	GD	:1;
	bool		:2;
	UINT	RWE0:2;
	UINT	LEN0:2;
	UINT	RWE1:2;
	UINT	LEN1:2;
	UINT	RWE2:2;
	UINT	LEN2:2;
	UINT	RWE3:2;
	UINT	LEN3:2;	
};

struct DEBUG_STATUS_REG
{
	bool	B0	:1;
	bool	B1	:1;
	bool	B2	:1;
	bool	B3	:1;
	UINT		:9;
	bool	BD	:1;
	bool	BS	:1;
	bool	BT	:1;
	UINT		:16;
};

enum GENE_REG_INDEX
{
	EAX_IDX = 0,
	ECX_IDX,
	EDX_IDX,
	EBX_IDX,
	ESP_IDX,
	EBP_IDX,
	ESI_IDX,
	EDI_IDX,
	GENE_IDX_MAX
};

enum SEG_REG_INDEX
{
	ES_IDX = 0,
	CS_IDX,
	SS_IDX,
	DS_IDX,
	FS_IDX,
	GS_IDX,
	SEG_IDX_MAX
};

typedef struct _RETURN_CONTEXT
{
	DWORD rEIP;
	DWORD rCS;
	DWORD rEflags;
	DWORD r3ESP;
	DWORD r3SS;
	DWORD rV86ES;
	DWORD rV86DS;
	DWORD rV86FS;
	DWORD rV86GS;
}RETURN_CONTEXT,*PRETURN_CONTEXT;

typedef struct _X86_REG_CONTEXT
{
	DWORD GeneReg[GENE_IDX_MAX];
	DWORD CR[5];
	DWORD DR[8];
	DWORD EIP;
	DWORD EFlags;
	WORD  SegReg[SEG_IDX_MAX];
	WORD  TR;
	WORD  LDT;
	WORD  Reserved1;
	WORD  GDTLimit;
	DWORD GDTBase;
	WORD  Reserved2;
	WORD  IDTLimit;
	DWORD IDTBase;
	DWORD ExceptionEIP;						//发生异常时的EIP，   只用在异常中才用
	DWORD ExceptionInterruptNumber;			//异常的中断号例如 0e 缺页中断, 0d 通用异常
	DWORD ExceptionInterruptErrorCode;		//异常的错误代码
	PSAVELOCALAPIC LocalAPIC;
	WORD FPUStatusWord;
	WORD FPUControlWord;	
	WORD FPUTagWord;
	WORD Reserved3;

}X86_REG_CONTEXT,*PX86_REG_CONTEXT;

enum
{
	SYS_SEG_GATE_DECR_TYPE_RESERVED_1	= 0x00,		//保留
	SYS_SEG_GATE_DECR_TYPE_16TSS_AVAIL	= 0x01,		//16位TSS(可用)
	SYS_SEG_GATE_DECR_TYPE_LDT			= 0x02,		//LDT
	SYS_SEG_GATE_DECR_TYPE_16TSS_BUSY	= 0x03,		//16位TSS(忙)
	SYS_SEG_GATE_DECR_TYPE_16CALL_GATE	= 0x04,		//16位调用门
	SYS_SEG_GATE_DECR_TYPE_TASK_GATE	= 0x05,		//任务门
	SYS_SEG_GATE_DECR_TYPE_16INT_GATE	= 0x06,		//16位中断门
	SYS_SEG_GATE_DECR_TYPE_16TRAP_GATE	= 0x07,		//16位陷阱门
	SYS_SEG_GATE_DECR_TYPE_RESERVED_2	= 0x08,		//保留
	SYS_SEG_GATE_DECR_TYPE_32TSS_AVAIL	= 0x09,		//32位TSS(可用)
	SYS_SEG_GATE_DECR_TYPE_RESERVED_3	= 0x0A,		//保留
	SYS_SEG_GATE_DECR_TYPE_32TSS_BUSY	= 0x0B,		//32位TSS(忙)
	SYS_SEG_GATE_DECR_TYPE_32CALL_GATE	= 0x0C,		//32位调用门
	SYS_SEG_GATE_DECR_TYPE_RESERVED_4	= 0x0D,		//保留
	SYS_SEG_GATE_DECR_TYPE_32INT_GATE	= 0x0E,		//32位中断门
	SYS_SEG_GATE_DECR_TYPE_32TRAP_GATE	= 0x0F,		//32位陷阱门
};

typedef DWORD	REG32;
typedef DWORD	VADDR32;
typedef DWORD	PADDR32;
typedef WORD	SELECTOR;

struct SELECTOR_DECR
{
	UINT RPL:2;
	UINT TI:1;
	UINT Index:13;
};

typedef struct _X86_GATE_DECR
{
	WORD		OffsetLow;
	SELECTOR	Selector;
	BYTE		DCount	:5;
	BYTE		Reserved:3;
	BYTE		Type	:4;
	BYTE		DT		:1;//storage segment (value=1) system segment and system gate (value=0)
	BYTE		DPL		:2;//Descriptor Privilege Level
	BYTE		P		:1;//Present
	WORD		OffsetHigh;
}X86_GATE_DECR,*PX86_GATE_DECR;

typedef struct _X86_SEGMENT_DESCRIPTOR		//descriptor
{
	DWORD limit_L0:8;
	DWORD limit_L1:8;
	DWORD base_L0:8;
	DWORD base_L1:8;
	DWORD base_H0:8;
	DWORD TYPE:4;							//type
	DWORD DT:1;								//storage segment (value=1) system segment and system gate (value=0)
	DWORD DPL:2;							//Descriptor Privilege Level
	DWORD P:1;								//Present
	DWORD limit_H:4;
	DWORD AVL:1;							//soft accessed
	DWORD reseved:1;						//reseved (value=0)
	DWORD D:1;								// segment size BIT31(1) BIT16(0) (storage segment)
	DWORD G:1;								//Granularity
	DWORD base_H1:8;	
}X86_SEGMENT_DESCRIPTOR;

typedef struct _X86_PDE_4M
{
	DWORD	Present			:1;
	DWORD	ReadWrite		:1;
	DWORD	UserPage		:1;
	DWORD	WriteThrough	:1;
	DWORD	CacheDisable	:1;
	DWORD	Accessed		:1;
	DWORD	Dirty			:1;
	DWORD	Page4M			:1;
	DWORD	GlobePage		:1;
	DWORD	Avail			:3;
	DWORD	PageTabAttrIdx	:1;
	DWORD	Reserved1		:9;
	DWORD	PageBase		:10;
}X86_PDE_4M,*PX86_PDE_4M;

typedef union _X86_PDE
{
	struct _u{
	DWORD	Present			:1;
	DWORD	ReadWrite		:1;
	DWORD	UserPage		:1;
	DWORD	WriteThrough	:1;
	DWORD	CacheDisable	:1;
	DWORD	Accessed		:1;
	DWORD	Reserved		:1;
	DWORD	Page4M			:1;
	DWORD	GlobePage		:1;
	DWORD	Avail			:3;
	DWORD	PageTabBase		:20;
	}u;
	ULONG  PDEValue;
}X86_PDE,*PX86_PDE;

typedef union _X86_36_PDE
{
	struct _u{
		DWORD P:1;
		DWORD RW:1;
		DWORD US:1;
		DWORD PWT:1;
		DWORD PCD:1;
		DWORD A:1;
		DWORD Reserved:1;
		DWORD Page2M:1;
		DWORD Reserved1:1;
		DWORD Avail:3;
		DWORD BaseAddressLow:20;
		DWORD BaseAddressHigh:4;
		DWORD Reserved2:27;
		DWORD NXE:1;
	}u;
	ULONGLONG PDE36Value;
}X86_36_PDE,*PX86_36_PDE;


typedef union _X86_36_PDE_2M
{
	struct _u{
		DWORD P:1;
		DWORD RW:1;
		DWORD US:1;
		DWORD PWT:1;
		DWORD PCD:1;
		DWORD A:1;
		DWORD D:1;
		DWORD Page2M:1;
		DWORD G:1;
		DWORD Avail:3;
		DWORD PAT:1;
		DWORD Reserved:8;
		DWORD BaseAddress:11;
		DWORD BaseAddressHigh:4;
		DWORD Reserved1:27;
		DWORD NXE:1;
	}u;
	ULONGLONG PDE36Value2M;
}X86_36_PDE_2M,*PX86_36_PDE_2M;

typedef struct _X86_36_PDE_4M 
{
	DWORD P:1;
	DWORD RW:1;
	DWORD US:1;
	DWORD PWT:1;
	DWORD PCD:1;
	DWORD A:1;
	DWORD D:1;
	DWORD Page4M:1;
	DWORD G:1;
	DWORD Avail:3;
	DWORD PAT:1;
	DWORD BaseAddressHigh:4;
	DWORD Reserved:5;
	DWORD BaseAddressLow:10;
}X86_36_PDE_4M,*PX86_36_PDE_4M;

typedef union _X86_36_PTE
{
	struct _u{
		DWORD P:1;
		DWORD RW:1;
		DWORD US:1;
		DWORD PWT:1;
		DWORD PCD:1;
		DWORD A:1;
		DWORD D:1;
		DWORD PAT:1;
		DWORD G:1;
		DWORD Avail:3;
		DWORD BaseAddressLow:20;
		DWORD BaseAddressHigh:4;
		DWORD Reserved:27;
		DWORD NXE:1;
	}u;
	ULONGLONG PTE36Value;	
}X86_36_PTE,*PX86_36_PTE;

typedef struct _X86_PTE
{
	DWORD	Present			:1;
	DWORD	ReadWrite		:1;
	DWORD	UserPage		:1;
	DWORD	WriteThrough	:1;
	DWORD	CacheDisable	:1;
	DWORD	Accessed		:1;
	DWORD	Dirty			:1;
	DWORD	PageTabAttrIdx	:1;
	DWORD	GlobePage		:1;
	DWORD	Avail			:3;
	DWORD	PageTabBase		:20;
}X86_PTE;

typedef struct _TASK32SEGMENT
{
	WORD TaskLink;
	WORD TaskLink_word_filler;
	//-------------
	DWORD ESP0;
	WORD SS0;
	WORD SS0_word_filler;
	DWORD ESP1;
	WORD SS1;
	WORD SS1_word_filler;
	DWORD ESP2;
	WORD SS2;
	WORD SS2_word_filler;
	//-------------
	DWORD CR3;
	DWORD eip;
	DWORD efl;
	DWORD eax;
	DWORD ecx;
	DWORD edx;
	DWORD ebx;
	DWORD esp;
	DWORD ebp;
	DWORD esi;
	DWORD edi;
	//-------------
	WORD ES;
	WORD ES_word_filler;
	WORD CS;
	WORD CS_word_filler;
	WORD SS;
	WORD SS_word_filler;
	WORD DS;
	WORD DS_word_filler;
	WORD FS;
	WORD FS_word_filler;
	WORD GS;
	WORD GS_word_filler;
	//-------------
	WORD LDT;
	WORD LDT_word_filler;
	//-------------
	WORD Trap;
	WORD io_map_base;
	BYTE io_map;
}TASK32SEGMENT,*PTASK32SEGMENT;

typedef struct _TASK16SEGMENT
{
	WORD TaskLink;
	//-------------
	WORD SP0;
	WORD SS0;
	WORD SP1;
	WORD SS1;
	WORD SP2;
	WORD SS2;
	//-------------
	WORD ip;
	WORD fl;
	WORD ax;
	WORD cx;
	WORD dx;
	WORD bx;
	WORD sp;
	WORD bp;
	WORD si;
	WORD di;
	//-------------
	WORD ES;
	WORD CS;
	WORD SS;
	WORD DS;
	//-------------
	WORD LDT;
}TASK16SEGMENT,*PTASK16SEGMENT;

typedef struct _CR4REGISTER
{
	DWORD VEM:1;		//Virtual-8086 Mode Extensions (bit 0 of CR4).
	DWORD PVI:1;		//Protected-Mode Virtual Interrupts (bit 1 of CR4).
	DWORD TSD:1;		//Time Stamp Disable (bit 2 of CR4).
	DWORD DE:1;			//Debugging Extensions (bit 3 of CR4).
	DWORD PSE:1;		//Page Size Extensions (bit 4 of CR4).
	DWORD PAE:1;		//Physical Address Extension (bit 5 of CR4).
	DWORD MCE:1;		//Machine-Check Enable (bit 6 of CR4).
	DWORD PGE:1;		//Page Global Enable (bit 7 of CR4).
	DWORD PCE:1;		//Performance-Monitoring Counter Enable (bit 8 of CR4).
	DWORD OSFXSR:1;		//Operating System Support for FXSAVE and FXRSTOR instructions (bit 9 of	CR4).
	DWORD OSXMMEXCPT:1;	//Operating System Support for Unmasked SIMD Floating-Point Exceptions (bit 10 of CR4).
	DWORD Reserved:21;
}CR4REGISTER,*PCR4REGISTER;

typedef struct _CR0REGISTER
{
	ULONG PE:1;                   //Paging (bit 31 of CR0)
	ULONG MP:1;                   //Monitor Coprocessor (bit 1 of CR0).
	ULONG EM:1;                   //Emulation (bit 2 of CR0)
	ULONG TS:1;                   //Task Switched (bit 3 of CR0)
	ULONG ET:1;                   //Extension Type (bit 4 of CR0)
	ULONG NE:1;                   //Numeric Error (bit 5 of CR0)
	ULONG ReservedBit6_15:10;
	ULONG WP:1;                   //Write Protect (bit 16 of CR0)
	ULONG ReservedBit17:1;
	ULONG AM:1;                   //Alignment Mask (bit 18 of CR0)
	ULONG ReservedBit19_28:10;
	ULONG NW:1;                   //Not Write-through (bit 29 of CR0)
	ULONG CD:1;                   //Cache Disable (bit 30 of CR0)
	ULONG PG:1;                   //Paging (bit 31 of CR0)
}CR0REGISTER,*PCR0REGISTER;

typedef struct _CR3REGISTER
{
	ULONG ReservedBit0_2:3;
	ULONG PWT:1;                  //Page-level Cache Disable (bit 4 of CR3)
	ULONG PCD:1;                  //Page-level Writes Transparent (bit 3 of CR3)
	ULONG ReservedBit5_11:7;	
	ULONG PageDirectoryBase:20;
}CR3REGISTER,*PCR3REGISTER;

typedef struct _PDECSRIPTOR
{
	WORD Limit;
	DWORD Base;
}PDECSRIPTOR,*PPDECSRIPTOR;

typedef struct _CPUID_1_EAX_VERSION
{
	DWORD SteppingID:4;
	DWORD Model:4;
	DWORD Family:4;
	DWORD ProcessorType:2;
	DWORD Reserved:2;
	DWORD ExtendedModel:4;
	DWORD ExtendedFamily:8;
	DWORD Reserved1:4;
}CPUID_1_EAX_VERSION,*PCPUID_1_EAX_VERSION;

typedef struct _CPUID_1_EDX_FEATURE
{
	DWORD FPU:1;		//Floating Point Unit On-Chip. The processor contains an x87 FPU.
	DWORD VME:1;		//Virtual 8086 Mode Enhancements. Virtual 8086 mode enhancements,including CR4.VME for controlling the feature, CR4.PVI for protected mode virtual interrupts, software interrupt indirection, expansion of the TSS with the software indirection bitmap, and EFLAGS.VIF and EFLAGS.VIP flags.
	DWORD DE:1;			//Debugging Extensions. Support for I/O breakpoints, including CR4.DE for controlling the feature, and optional trapping of accesses to DR4 and DR5.
	DWORD PSE:1;		//Page Size Extension. Large pages of size 4 MByte are supported, including	CR4.PSE for controlling the feature, the defined dirty bit in PDE (Page	Directory Entries), optional reserved bit trapping in CR3, PDEs, and PTEs.
	DWORD TSC:1;		//Time Stamp Counter. The RDTSC instruction is supported, including CR4.TSD	for controlling privilege.
	DWORD MSR:1;		//Model Specific Registers RDMSR and WRMSR Instructions. The RDMSR and WRMSR instructions are supported. Some of the MSRs are implementation dependent.
	DWORD PAE:1;		//Physical Address Extension. Physical addresses greater than 32 bits are supported: extended page table entry formats, an extra level in the page translation tables is defined, 2-MByte pages are supported instead of 4 Mbyte pages if PAE bit is 1. The actual number of address bits beyond 32 is not defined, and is implementation specific.
	DWORD MCE:1;		//Machine Check Exception. Exception 18 is defined for Machine Checks,including CR4.MCE for controlling the feature. This feature does not define the model-specific implementations of machine-check error logging,reporting, and processor shutdowns. Machine Check exception handlers may have to depend on processor version to do model specific processing of the	exception, or test for the presence of the Machine Check feature.
	DWORD CX8:1;		//CMPXCHG8B Instruction. The compare-and-exchange 8 bytes (64 bits)	instruction is supported (implicitly locked and atomic).
	DWORD APIC:1;		//APIC On-Chip. The processor contains an Advanced Programmable Interrupt Controller (APIC), responding to memory mapped commands in the physical address range FFFE0000H to FFFE0FFFH (by default - some processors permit the APIC to be relocated).
	DWORD Reserved:1;	//Reserved
	DWORD SEP:1;		//SYSENTER and SYSEXIT Instructions. The SYSENTER and SYSEXIT and associated MSRs are supported.
	DWORD MTRR:1;		//Memory Type Range Registers. MTRRs are supported. The MTRRcap MSR	contains feature bits that describe what memory types are supported, how many variable MTRRs are supported, and whether fixed MTRRs are	supported.
	DWORD PGE:1;		//PTE Global Bit. The global bit in page directory entries (PDEs) and page table entries (PTEs) is supported, indicating TLB entries that are common to	different processes and need not be flushed. The CR4.PGE bit controls this feature.
	DWORD MCA:1;		//Machine Check Architecture. The Machine Check Architecture, which	provides a compatible mechanism for error reporting in P6 family, Pentium 4,Intel Xeon processors, and future processors, is supported. The MCG_CAP	MSR contains feature bits describing how many banks of error reporting	MSRs are supported.
	DWORD CMOV:1;		//Conditional Move Instructions. The conditional move instruction CMOV is supported. In addition, if x87 FPU is present as indicated by the CPUID.FPU feature bit, then the FCOMI and FCMOV instructions are supported
	DWORD PAT:1;		//Page Attribute Table. Page Attribute Table is supported. This feature	augments the Memory Type Range Registers (MTRRs), allowing an operating	system to specify attributes of memory on a 4K granularity through a linear	address.
	DWORD PSE_36:1;		//36-Bit Page Size Extension. Extended 4-MByte pages that are capable of addressing physical memory beyond 4 GBytes are supported. This feature	indicates that the upper four bits of the physical address of the 4-MByte page is encoded by bits 13-16 of the page directory entry.
	DWORD PSN:1;		//Processor Serial Number. The processor supports the 96-bit processor	identification number feature and the feature is enabled.
	DWORD CLFSH:1;		//CLFLUSH Instruction. CLFLUSH Instruction is supported.
	DWORD Reserved1:1;	//Reserved
	DWORD DS:1;			//Debug Store. The processor supports the ability to write debug information into a memory resident buffer. This feature is used by the branch trace store (BTS) and precise event-based sampling (PEBS) facilities
	DWORD ACPI:1;		//Thermal Monitor and Software Controlled Clock Facilities. The processor implements internal MSRs that allow processor temperature to be monitored	and processor performance to be modulated in predefined duty cycles under software control.
	DWORD MXX:1;		//Intel MMX Technology. The processor supports the Intel MMX technology.
	DWORD FXSR:1;		//FXSAVE and FXRSTOR Instructions. The FXSAVE and FXRSTOR instructions are supported for fast save and restore of the floating point context.Presence of this bit also indicates that CR4.OSFXSR is available for an operating system to indicate that it supports the FXSAVE and FXRSTOR instructions.
	DWORD SSE:1;		//SSE. The processor supports the SSE extensions.
	DWORD SSE2:1;		//SSE2. The processor supports the SSE2 extensions.
	DWORD SS:1;			//Self Snoop. The processor supports the management of conflicting memory types by performing a snoop of its own cache structure for transactions issued to the bus.
	DWORD HTT:1;		//Multi-Threading. The physical processor package is capable of supporting more than one logical processor.
	DWORD TM:1;			//Thermal Monitor. The processor implements the thermal monitor automatic thermal control circuitry (TCC).
	DWORD Reserved2:1;	//Reserved
	DWORD PBE:1;		//Pending Break Enable. The processor supports the use of the FERR#/PBE# pin when the processor is in the stop-clock state (STPCLK# is asserted) to	signal the processor that an interrupt is pending and that the processor should return to normal operation to handle the interrupt. Bit 10 (PBE	enable) in the IA32_MISC_ENABLE MSR enables this capability.
}CPUID_1_EDX_FEATURE,*PCPUID_1_EDX_FEATURE;

typedef struct _CPUID_1_ECX_EXTENDED_FEATURE
{
	ULONG SSE3:1;                 //Streaming SIMD Extensions 3 (SSE3). A value of 1 indicates the processor supports this technology.
	ULONG ReservedBit1:1;
	ULONG ReservedBit2:1;
	ULONG MONITOR:1;              //MONITOR/MWAIT. A value of 1 indicates the processor supports this feature.
	ULONG DS_CPL:1;               //CPL Qualified Debug Store. A value of 1 indicates the processor	supports the extensions to the Debug Store feature to allow for	branch message storage qualified by CPL.
	ULONG VMX:1;                  //Virtual Machine Extensions. A value of 1 indicates that the	processor supports this technology
	ULONG ReservedBit6:1;
	ULONG EST:1;                  //Enhanced Intel SpeedStep? technology. A value of 1 indicates that the processor supports this technology.
	ULONG TM2:1;                  //Thermal Monitor 2. A value of 1 indicates whether the processor	supports this technology.
	ULONG SSSE3:1;                //A value of 1 indicates the presence of the Supplemental	Streaming SIMD Extensions 4 (SSSE3). A value of 0 indicates the	instruction extensions are not present in the processor
	ULONG CNXT_ID:1;              //L1 Context ID. A value of 1 indicates the L1 data cache mode can be set to either adaptive mode or shared mode. A value of 0 indicates this feature is not supported. See definition of the	IA32_MISC_ENABLE MSR Bit 24 (L1 Data Cache Context Mode) for details.
	ULONG ReservedBit11:1;
	ULONG ReservedBit12:1;
	ULONG CMPXCHG16B:1;           //CMPXCHG16B Available. A value of 1 indicates that the feature is available. See the “CMPXCHG8B/CMPXCHG16B—Compare and	Exchange Bytes” section in this chapter for a description.
	ULONG xTPR_Update_Control:1;  //xTPR Update Control. A value of 1 indicates that the processor supports changing IA32_MISC_ENABLES[bit 23].
	ULONG ReservedBit15_31:17;
}CPUID_1_ECX_EXTENDED_FEATURE,*PCPUID_1_ECX_EXTENDED_FEATURE;

typedef struct _MSR_IA32_MISC_ENABLE
{
	ULONG FastString:1;
	ULONG ReservedBit1:1;
	ULONG FPUMode:1;
	ULONG TM1E:1;
	ULONG SLD:1;
	ULONG ReservedBit5:1;
	ULONG TLCD:1;
	ULONG PMA:1;
	ULONG SLE:1;
	ULONG PQD:1;
	ULONG FerrIRE:1;
	ULONG BTSU:1;
	ULONG PEBSU:1;
	ULONG TM2E:1;
	ULONG ReservedBit14_17:4;
	ULONG EMFSM:1;
	ULONG ACLPD:1;
	ULONG ReservedBit20_21:2;
	ULONG LCPUIDMAXVAL:1;
	ULONG ReservedBit23:1;
	ULONG L1DCCM:1;
	ULONG ReservedBit25_31:7;
}MSR_IA32_MISC_ENABLE,*PMSR_IA32_MISC_ENABLE;

typedef struct _CPU_EFLAGS
{
	ULONG CF:1;
	ULONG ReservedBit1_One:1;
	ULONG PF:1;
	ULONG ReservedBit3_Zero:1;
	ULONG AF:1;
	ULONG ReservedBit5_Zero:1;
	ULONG ZF:1;
	ULONG SF:1;
	ULONG TF:1;
	ULONG IF:1;
	ULONG DF:1;
	ULONG OF:1;
	ULONG IOPL:2;
	ULONG NT:1;
	ULONG ReservedBit15_Zero:1;
	ULONG RF:1;
	ULONG VM:1;
	ULONG AC:1;
	ULONG VIF:1;
	ULONG VIP:1;
	ULONG ID:1;
	ULONG ReservedBit22_31:10;
}CPU_EFLAGS,*PCPU_EFLAGS;

typedef struct _AMD_CPUID_1_ECX 
{
	DWORD SSE3:1;           //SSE3 extensions.
	DWORD ReservedBit1_12:12;
	DWORD CMPXCHG16B:1;
	DWORD ReservedBit14_30:17;
	DWORD RAZ:1;
}AMD_CPUID_1_ECX,*PAMD_CPUID_1_ECX;

typedef struct _AMD_CPUID_1_EDX 
{
	DWORD FPU:1;           //SSE3 extensions.
	DWORD VME:1;
	DWORD DE:1;
	DWORD PSE:1;
	DWORD TSC:1;
	DWORD MSR:1;
	DWORD PAE:1;
	DWORD MCE:1;
	DWORD CMPXCHG8B:1;
	DWORD APIC:1;
	DWORD ReservedBit10:1;
	DWORD SysEnterSysExit:1;
	DWORD MTRR:1;
	DWORD PGE:1;
	DWORD MCA:1;
	DWORD CMOV:1;
	DWORD PAT:1;
	DWORD PSE36:1;
	DWORD ReservedBit18:1;
	DWORD CLFSH:1;
	DWORD ReservedBit20_22:3;
	DWORD MMX:1;
	DWORD FXSR:1;
	DWORD SSE:1;
	DWORD SSE2:1;
	DWORD ReservedBit27:1;
	DWORD HTT:1;
	DWORD ReservedBit29_31:3;
}AMD_CPUID_1_EDX,*PAMD_CPUID_1_EDX;

typedef struct _AMD_CPUID_80000001_ECX 
{
	DWORD LahfSahf:1;           //SSE3 extensions.
	DWORD CmpLegacy:1;
	DWORD SVM:1;
	DWORD ReservedBit3:1;
	DWORD AltMovCr8:1;
	DWORD ReservedBit5_31:27;
}AMD_CPUID_80000001_ECX,*PAMD_CPUID_80000001_ECX;

typedef struct _AMD_CPUID_80000001_EDX 
{
	DWORD FPU:1;           //SSE3 extensions.
	DWORD VME:1;
	DWORD DE:1;
	DWORD PSE:1;
	DWORD TSC:1;
	DWORD MSR:1;
	DWORD PAE:1;
	DWORD MCE:1;
	DWORD CMPXCHG8B:1;
	DWORD APIC:1;
	DWORD ReservedBit10:1;
	DWORD SysCallSysRet:1;
	DWORD MTRR:1;
	DWORD PGE:1;
	DWORD MCA:1;
	DWORD CMOV:1;
	DWORD PAT:1;
	DWORD PSE36:1;
	DWORD ReservedBit18_19:2;
	DWORD NX:1;
	DWORD ReservedBit21:1;
	DWORD MmxExt:1;
	DWORD MMX:1;
	DWORD FXSR:1;
	DWORD FFXSR:1;
	DWORD ReservedBit26:1;
	DWORD RDTSCP:1;
	DWORD ReservedBit28:1;
	DWORD LM:1;
	DWORD _3DNowExt:1;
	DWORD _3DNow:1;
}AMD_CPUID_80000001_EDX,*PAMD_CPUID_80000001_EDX;


#define NT_CS		(0x8)
#define NT_UCS		(0x1B)
#define NT_DS		(0x23)
#define NT_FS		(0x30)

//Dr6
#define DR6_BD			0x2000
#define DR6_BS			0x4000
#define DR6_BT			0x8000

#define DR6_NOT_BD		0xFFFFDFFF
#define DR6_NOT_BS		0xFFFFBFFF
#define DR6_NOT_BT		0xFFFF7FFF

#define CR4_VME_BIT_MASK		0x1
#define CR4_PVI_BIT_MASK		0x2
#define CR4_TSD_BIT_MASK		0x4
#define CR4_DE_BIT_MASK			0x8
#define CR4_PSE_BIT_MASK		0x10
#define CR4_PAE_BIT_MASK		0x20
#define CR4_MCE_BIT_MASK		0x40
#define CR4_PGE_BIT_MASK		0x80
#define CR4_PCE_BIT_MASK		0x100
#define CR4_OSFXSR_BIT_MASK		0x200
#define CR4_OSXMMEXCPT_BIT_MASK 0x400

#endif
