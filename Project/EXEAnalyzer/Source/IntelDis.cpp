#include "StdAfx.h"
#include "IntelDef.h"
#include "IntelDis.h"

LOCKREPXX LockRepxx[]=
{
	{"LOCK "	,0xf0},
	{"REP "		,0xf3},
	{"REPZ "	,0xf3},
	{"REPE "	,0xf3},
	{"REPNE "	,0xf2},
	{"REPNZ "	,0xf2}
};

OPDATAWIDE OpDataWide[]=
{
	{1,		"SHORT PTR"		},
	{2,		"NEAR PTR"		},
	{4,		"FAR PTR"		},
	{1,		"BYTE PTR"		},
	{2,		"WORD PTR"		},
	{4,		"DWORD PTR"		},
	{6,		"FWORD PTR"		},
	{8,		"QWORD PTR"		},
	{10,	"TBYTE PTR"		},
	{16,	"OWORD PTR"		},
};


char *RegAddr16[]=
{ 

	"[BX+SI]"	,	"[SI+BX]"		,	"[BX][SI]"		,	"[SI][BX]",
	"[BX+DI]"	,	"[DI+BX]"		,	"[BX][DI]"		,	"[DI][BX]",
	"[BP+SI]"	,	"[SI+BP]"		,	"[BP][SI]"		,	"[SI][BP]",
	"[BP+DI]"	,	"[DI+BP]"		,	"[BP][DI]"		,	"[DI][BP]",
	"[SI]"		,	"[SI]"			,	"[SI]"			,	"[SI]",
	"[DI]"		,	"[DI]"			,	"[DI]"			,	"[DI]",
	"[BP]"		,	"[BP]"			,	"[BP]"			,	"[BP]",
	"[BX]"		,	"[BX]"			,	"[BX]"			,	"[BX]"

};

char *xxxxptr[] =
{
	NULL,
	"BYTE",
	"WORD",
	NULL,
	"DWORD",
	NULL,
	"FWORD",
	NULL,
	"QWORD",	
	NULL,
	"TBYTE",
	NULL,
	NULL,
	NULL,
	NULL,
	NULL,
	"OWORD"
};

BYTE SegmentValue[8] =
{
	0x26,0x2e,0x36,0x3e,0x64,0x65,0x00,0x00
};

char *SegReg[8] =
{
	"ES","CS","SS","DS","FS","GS","??","??"
};

char *RegByte[8] =
{
	"AL","CL","DL","BL","AH","CH","DH","BH"
};

char *RegByteFor64bit[16] =
{
	"AL","CL","DL","BL","SPL","BPL","SIL","DIL",
	//"R8L","R9L","R10L","R11L","R12L","R13L","R14L","R15L",
	"R8B","R9B","R10B","R11B","R12B","R13B","R14B","R15B",
};

char *RegWord[16] = 
{
	"AX","CX","DX","BX","SP","BP","SI","DI",
	"R8W","R9W","R10W","R11W","R12W","R13W","R14W","R15W",
};
char *RegQWord[16] = 
{
	"RAX","RCX","RDX","RBX","RSP","RBP","RSI","RDI",
	"R8","R9","R10","R11","R12","R13","R14","R15",
};
char *RegDWord[16] = 
{
	"EAX","ECX","EDX","EBX","ESP","EBP","ESI","EDI",
	"R8D","R9D","R10D","R11D","R12D","R13D","R14D","R15D",
};
char *RegMMXQWord[8] = 
{
	"MM0","MM1","MM2","MM3","MM4","MM5","MM6","MM7",
};
char *RegCR[16] = 
{
	"CR0","CR1","CR2","CR3","CR4","CR5","CR6","CR7",
	"CR8","CR9","CR10","CR11","CR12","CR13","CR14","CR15",
};

char *RegTR[16] = 
{
	"TR0","TR1","TR2","TR3","TR4","TR5","TR6","TR7",
	"TR8","TR9","TR10","TR11","TR12","TR13","TR14","TR15",
};

char *RegDR[16] = 
{
	"DR0","DR1","DR2","DR3","DR4","DR5","DR6","DR7",
	"DR8","DR9","DR10","DR11","DR12","DR13","DR14","DR15",
};
char *RegXMMOWord[16] = 
{
	"XMM0","XMM1","XMM2","XMM3","XMM4","XMM5","XMM6","XMM7",
	"XMM8","XMM9","XMM10","XMM11","XMM12","XMM13","XMM14","XMM15",
};
char *RegFPU[9] = 
{
	"ST(0)","ST(1)","ST(2)","ST(3)","ST(4)","ST(5)","ST(6)","ST(7)","ST"
	
};

char *FlagS[2][8]=
{
	{"NV","UP","DI","PL","NZ","NA","PO","NC"},
	{"OV","DN","EI","NG","ZR","AC","PE","CY"}
};

char *FlagICE[2][8]=
{
	{"o","d","i","s","z","a","p","c"},
	{"O","D","I","S","Z","A","P","C"}
};

BYTE Segment[8] =
{
	0x26,0x2e,0x36,0x3e,0x64,0x65,0x00,0x00
};

char *CtrReg[8] =
{
	"IP","EIP","FLAGS","FLAG","FL","EFLAGS","EFLAG","EFL"
};

char *RegName[][8] =
{
	{"ES","CS","SS","DS","FS","GS","??","??"},
	{"AL","CL","DL","BL","AH","CH","DH","BH"},
	{"AX","CX","DX","BX","SP","BP","SI","DI"},
	{"EAX","ECX","EDX","EBX","ESP","EBP","ESI","EDI"}
};

char *Emblem[0x200] =
{
	"ES","CS","SS","DS","FS","GS",
	"AL","CL","DL","BL","AH","CH","DH","BH",
	"AX","CX","DX","BX","SP","BP","SI","DI",
	"EAX","ECX","EDX","EBX","ESP","EBP","ESI","EDI",
	//----------------------------------
		
	"IP","EIP","FLAGS","EFLAGS",
	//----------------------------------
	
	"BYTE","WORD","DWORD","FWORD","QWORD","TWORD",
	
	//----------------------------------
	"SHORT","NEAR","FAR","PTR",
		
	//----------------------------------
	"ADD","ADC","SUB","SBB","MUL","IDIV",
	"XOR","AND","OR" ,"NOT","NEG","TEST"
};


DIS_OPCODE_T Group0x0f00[] = //CPU保护模式指令
{
	{R_M, C_SLDT,	D__wMwRv,	D__NONE,	D__NONE,	"SLDT" 	,0x000f,2|C_GROUP_0_TYPE|(0<<16),MAKE_OP_RW_FLAG(OP_W,0,0)}, //0x0
	{R_M, C_STR,	D__wMwRv,	D__NONE,	D__NONE,	"STR" 	,0x000f,2|C_GROUP_0_TYPE|(1<<16),MAKE_OP_RW_FLAG(OP_W,0,0)}, //0x1
	{R_M, C_LLDT,	D__rEw,		D__NONE,	D__NONE,	"LLDT" 	,0x000f,2|C_GROUP_0_TYPE|(2<<16),MAKE_OP_RW_FLAG(OP_R,0,0)}, //0x2
	{R_M, C_LTR,	D__rEw,		D__NONE,	D__NONE,	"LTR" 	,0x000f,2|C_GROUP_0_TYPE|(3<<16),MAKE_OP_RW_FLAG(OP_R,0,0)}, //0x3
	{R_M, C_VERR,	D__rEw,		D__NONE,	D__NONE,	"VERR" 	,0x000f,2|C_GROUP_0_TYPE|(4<<16),MAKE_OP_RW_FLAG(OP_R,0,0)}, //0x4
	{R_M, C_VERW,	D__rEw,		D__NONE,	D__NONE,	"VERW" 	,0x000f,2|C_GROUP_0_TYPE|(5<<16),MAKE_OP_RW_FLAG(OP_R,0,0)}, //0x5
	{R_M, C_NULL												}, //0x6
	{R_M, C_NULL												} //0x7

};


DIS_OPCODE_T Group0x0fba[] =  //80386
{
	{R_M, C_NULL,												}, //0x0
	{R_M, C_NULL,												}, //0x1
	{R_M, C_NULL,												}, //0x2
	{R_M, C_NULL,												}, //0x3
	{R_M |Immediate_Ib, C_BT,	D__rEv,		D__Ib,		D__NONE,	"BT" 	,0xba0f,2|C_GROUP_0_TYPE|(4<<16),MAKE_OP_RW_FLAG(OP_R,OP_R,0)}, //0x4
	{R_M |Immediate_Ib, C_BTS,	D__Ev,		D__Ib,		D__NONE,	"BTS" 	,0xba0f,2|C_GROUP_0_TYPE|(5<<16),MAKE_OP_RW_FLAG(OP_W,OP_R,0)}, //0x5
	{R_M |Immediate_Ib, C_BTR,	D__Ev,		D__Ib,		D__NONE,	"BTR" 	,0xba0f,2|C_GROUP_0_TYPE|(6<<16),MAKE_OP_RW_FLAG(OP_W,OP_R,0)}, //0x6
	{R_M |Immediate_Ib, C_BTC,	D__Ev,		D__Ib,		D__NONE,	"BTC" 	,0xba0f,2|C_GROUP_0_TYPE|(7<<16),MAKE_OP_RW_FLAG(OP_W,OP_R,0)} //0x7

};

//---------------------------------------------------------------
//intel 指令表格
//----------------------------------------------------------------
DIS_OPCODE_T Group0x80[] = //immediate group
{
	{R_M |Immediate_Ib, C_ADD,		D__Eb,		D__Ib,		D__NONE,	"ADD" 	,0x80,1|C_GROUP_0_TYPE|(0<<16),MAKE_OP_RW_FLAG(OP_RW,OP_R,0)}, //0x0
	{R_M |Immediate_Ib, C_OR,		D__Eb,		D__Ib,		D__NONE,	"OR" 	,0x80,1|C_GROUP_0_TYPE|(1<<16),MAKE_OP_RW_FLAG(OP_RW,OP_R,0)}, //0x1
	{R_M |Immediate_Ib, C_ADC,		D__Eb,		D__Ib,		D__NONE,	"ADC" 	,0x80,1|C_GROUP_0_TYPE|(2<<16),MAKE_OP_RW_FLAG(OP_RW,OP_R,0)}, //0x2
	{R_M |Immediate_Ib, C_SBB,		D__Eb,		D__Ib,		D__NONE,	"SBB" 	,0x80,1|C_GROUP_0_TYPE|(3<<16),MAKE_OP_RW_FLAG(OP_RW,OP_R,0)}, //0x3
	{R_M |Immediate_Ib, C_AND,		D__Eb,		D__Ib,		D__NONE,	"AND" 	,0x80,1|C_GROUP_0_TYPE|(4<<16),MAKE_OP_RW_FLAG(OP_RW,OP_R,0)}, //0x4
	{R_M |Immediate_Ib, C_SUB,		D__Eb,		D__Ib,		D__NONE,	"SUB" 	,0x80,1|C_GROUP_0_TYPE|(5<<16),MAKE_OP_RW_FLAG(OP_RW,OP_R,0)}, //0x5
	{R_M |Immediate_Ib, C_XOR,		D__Eb,		D__Ib,		D__NONE,	"XOR" 	,0x80,1|C_GROUP_0_TYPE|(6<<16),MAKE_OP_RW_FLAG(OP_RW,OP_R,0)}, //0x6
	{R_M |Immediate_Ib, C_CMP,		D__rEb,		D__Ib,		D__NONE,	"CMP" 	,0x80,1|C_GROUP_0_TYPE|(7<<16),MAKE_OP_RW_FLAG(OP_R,OP_R,0)} //0x7
};

DIS_OPCODE_T Group0x81[] = //immediate group
{
	{R_M |Immediate_Iz, 	C_ADD,		D__Ev,		D__Iz,		D__NONE,	"ADD" 	,0x81,1|C_GROUP_0_TYPE|(0<<16),MAKE_OP_RW_FLAG(OP_RW,OP_R,0)}, //0x0
	{R_M |Immediate_Iz, 	C_OR,		D__Ev,		D__Iz,		D__NONE,	"OR" 	,0x81,1|C_GROUP_0_TYPE|(1<<16),MAKE_OP_RW_FLAG(OP_RW,OP_R,0)}, //0x1
	{R_M |Immediate_Iz, 	C_ADC,		D__Ev,		D__Iz,		D__NONE,	"ADC" 	,0x81,1|C_GROUP_0_TYPE|(2<<16),MAKE_OP_RW_FLAG(OP_RW,OP_R,0)}, //0x2
	{R_M |Immediate_Iz, 	C_SBB,		D__Ev,		D__Iz,		D__NONE,	"SBB" 	,0x81,1|C_GROUP_0_TYPE|(3<<16),MAKE_OP_RW_FLAG(OP_RW,OP_R,0)}, //0x3
	{R_M |Immediate_Iz, 	C_AND,		D__Ev,		D__Iz,		D__NONE,	"AND" 	,0x81,1|C_GROUP_0_TYPE|(4<<16),MAKE_OP_RW_FLAG(OP_RW,OP_R,0)}, //0x4
	{R_M |Immediate_Iz, 	C_SUB,		D__Ev,		D__Iz,		D__NONE,	"SUB" 	,0x81,1|C_GROUP_0_TYPE|(5<<16),MAKE_OP_RW_FLAG(OP_RW,OP_R,0)}, //0x5
	{R_M |Immediate_Iz, 	C_XOR,		D__Ev,		D__Iz,		D__NONE,	"XOR" 	,0x81,1|C_GROUP_0_TYPE|(6<<16),MAKE_OP_RW_FLAG(OP_RW,OP_R,0)}, //0x6
	{R_M |Immediate_Iz, 	C_CMP,		D__rEv,		D__Iz,		D__NONE,	"CMP" 	,0x81,1|C_GROUP_0_TYPE|(7<<16),MAKE_OP_RW_FLAG(OP_R,OP_R,0)} //0x7

};

DIS_OPCODE_T Group0x82[] = //immediate group
{
	{R_M |Immediate_Ib|I_64, 	C_ADD,		D__Eb,		D__Ib,		D__NONE,	"ADD" 	,0x82,1|C_GROUP_0_TYPE|(0<<16),MAKE_OP_RW_FLAG(OP_RW,OP_R,0)}, //0x0
	{R_M |Immediate_Ib|I_64, 	C_OR,		D__Eb,		D__Ib,		D__NONE,	"OR" 	,0x82,1|C_GROUP_0_TYPE|(1<<16),MAKE_OP_RW_FLAG(OP_RW,OP_R,0)}, //0x1
	{R_M |Immediate_Ib|I_64, 	C_ADC,		D__Eb,		D__Ib,		D__NONE,	"ADC" 	,0x82,1|C_GROUP_0_TYPE|(2<<16),MAKE_OP_RW_FLAG(OP_RW,OP_R,0)}, //0x2
	{R_M |Immediate_Ib|I_64, 	C_SBB,		D__Eb,		D__Ib,		D__NONE,	"SBB" 	,0x82,1|C_GROUP_0_TYPE|(3<<16),MAKE_OP_RW_FLAG(OP_RW,OP_R,0)}, //0x3
	{R_M |Immediate_Ib|I_64, 	C_AND,		D__Eb,		D__Ib,		D__NONE,	"AND" 	,0x82,1|C_GROUP_0_TYPE|(4<<16),MAKE_OP_RW_FLAG(OP_RW,OP_R,0)}, //0x4
	{R_M |Immediate_Ib|I_64, 	C_SUB,		D__Eb,		D__Ib,		D__NONE,	"SUB" 	,0x82,1|C_GROUP_0_TYPE|(5<<16),MAKE_OP_RW_FLAG(OP_RW,OP_R,0)}, //0x5
	{R_M |Immediate_Ib|I_64, 	C_XOR,		D__Eb,		D__Ib,		D__NONE,	"XOR" 	,0x82,1|C_GROUP_0_TYPE|(6<<16),MAKE_OP_RW_FLAG(OP_RW,OP_R,0)}, //0x6
	{R_M |Immediate_Ib|I_64, 	C_CMP,		D__rEb,		D__Ib,		D__NONE,	"CMP" 	,0x82,1|C_GROUP_0_TYPE|(7<<16),MAKE_OP_RW_FLAG(OP_R,OP_R,0)} //0x7

};

DIS_OPCODE_T Group0x83[] = //immediate group
{
	{R_M |Immediate_sIb, 	C_ADD,		D__Ev,		D__sIb,		D__NONE,	"ADD" 	,0x83,1|C_GROUP_0_TYPE|(0<<16),MAKE_OP_RW_FLAG(OP_RW,OP_R,0)}, //0x0
	{R_M |Immediate_sIb, 	C_OR,		D__Ev,		D__sIb,		D__NONE,	"OR" 	,0x83,1|C_GROUP_0_TYPE|(1<<16),MAKE_OP_RW_FLAG(OP_RW,OP_R,0)}, //0x1
	{R_M |Immediate_sIb, 	C_ADC,		D__Ev,		D__sIb,		D__NONE,	"ADC" 	,0x83,1|C_GROUP_0_TYPE|(2<<16),MAKE_OP_RW_FLAG(OP_RW,OP_R,0)}, //0x2
	{R_M |Immediate_sIb, 	C_SBB,		D__Ev,		D__sIb,		D__NONE,	"SBB" 	,0x83,1|C_GROUP_0_TYPE|(3<<16),MAKE_OP_RW_FLAG(OP_RW,OP_R,0)}, //0x3
	{R_M |Immediate_sIb, 	C_AND,		D__Ev,		D__sIb,		D__NONE,	"AND" 	,0x83,1|C_GROUP_0_TYPE|(4<<16),MAKE_OP_RW_FLAG(OP_RW,OP_R,0)}, //0x4
	{R_M |Immediate_sIb, 	C_SUB,		D__Ev,		D__sIb,		D__NONE,	"SUB" 	,0x83,1|C_GROUP_0_TYPE|(5<<16),MAKE_OP_RW_FLAG(OP_RW,OP_R,0)}, //0x5
	{R_M |Immediate_sIb, 	C_XOR,		D__Ev,		D__sIb,		D__NONE,	"XOR" 	,0x83,1|C_GROUP_0_TYPE|(6<<16),MAKE_OP_RW_FLAG(OP_RW,OP_R,0)}, //0x6
	{R_M |Immediate_sIb, 	C_CMP,		D__rEv,		D__sIb,		D__NONE,	"CMP" 	,0x83,1|C_GROUP_0_TYPE|(7<<16),MAKE_OP_RW_FLAG(OP_R,OP_R,0)} //0x7

};

DIS_OPCODE_T Group0xc0[] = //shift group
{
	{R_M |Immediate_Ib, 	C_ROL,		D__Eb,		D__Ib,		D__NONE,	"ROL" 	,0xc0,1|C_GROUP_0_TYPE|(0<<16),MAKE_OP_RW_FLAG(OP_RW,OP_R,0)}, //0x0
	{R_M |Immediate_Ib, 	C_ROR,		D__Eb,		D__Ib,		D__NONE,	"ROR" 	,0xc0,1|C_GROUP_0_TYPE|(1<<16),MAKE_OP_RW_FLAG(OP_RW,OP_R,0)}, //0x1
	{R_M |Immediate_Ib, 	C_RCL,		D__Eb,		D__Ib,		D__NONE,	"RCL" 	,0xc0,1|C_GROUP_0_TYPE|(2<<16),MAKE_OP_RW_FLAG(OP_RW,OP_R,0)}, //0x2
	{R_M |Immediate_Ib, 	C_RCR,		D__Eb,		D__Ib,		D__NONE,	"RCR" 	,0xc0,1|C_GROUP_0_TYPE|(3<<16),MAKE_OP_RW_FLAG(OP_RW,OP_R,0)}, //0x3
	{R_M |Immediate_Ib, 	C_SHL,		D__Eb,		D__Ib,		D__NONE,	"SHL" 	,0xc0,1|C_GROUP_0_TYPE|(4<<16),MAKE_OP_RW_FLAG(OP_RW,OP_R,0)}, //0x4
	{R_M |Immediate_Ib, 	C_SHR,		D__Eb,		D__Ib,		D__NONE,	"SHR" 	,0xc0,1|C_GROUP_0_TYPE|(5<<16),MAKE_OP_RW_FLAG(OP_RW,OP_R,0)}, //0x5
	{R_M |Immediate_Ib, 	C_SAL,		D__Eb,		D__Ib,		D__NONE,	"SAL" 	,0xc0,1|C_GROUP_0_TYPE|(6<<16),MAKE_OP_RW_FLAG(OP_RW,OP_R,0)}, //0x6
	{R_M |Immediate_Ib, 	C_SAR,		D__Eb,		D__Ib,		D__NONE,	"SAR" 	,0xc0,1|C_GROUP_0_TYPE|(7<<16),MAKE_OP_RW_FLAG(OP_RW,OP_R,0)} //0x7

};

DIS_OPCODE_T Group0xc1[] = //shift group
{
	{R_M |Immediate_Ib, 	C_ROL,		D__Ev,		D__Ib,		D__NONE,	"ROL" 	,0xc1,1|C_GROUP_0_TYPE|(0<<16),MAKE_OP_RW_FLAG(OP_RW,OP_R,0)}, //0x0
	{R_M |Immediate_Ib, 	C_ROR,		D__Ev,		D__Ib,		D__NONE,	"ROR" 	,0xc1,1|C_GROUP_0_TYPE|(1<<16),MAKE_OP_RW_FLAG(OP_RW,OP_R,0)}, //0x1
	{R_M |Immediate_Ib, 	C_RCL,		D__Ev,		D__Ib,		D__NONE,	"RCL" 	,0xc1,1|C_GROUP_0_TYPE|(2<<16),MAKE_OP_RW_FLAG(OP_RW,OP_R,0)}, //0x2
	{R_M |Immediate_Ib, 	C_RCR,		D__Ev,		D__Ib,		D__NONE,	"RCR" 	,0xc1,1|C_GROUP_0_TYPE|(3<<16),MAKE_OP_RW_FLAG(OP_RW,OP_R,0)}, //0x3
	{R_M |Immediate_Ib, 	C_SHL,		D__Ev,		D__Ib,		D__NONE,	"SHL" 	,0xc1,1|C_GROUP_0_TYPE|(4<<16),MAKE_OP_RW_FLAG(OP_RW,OP_R,0)}, //0x4
	{R_M |Immediate_Ib, 	C_SHR,		D__Ev,		D__Ib,		D__NONE,	"SHR" 	,0xc1,1|C_GROUP_0_TYPE|(5<<16),MAKE_OP_RW_FLAG(OP_RW,OP_R,0)}, //0x5
	{R_M |Immediate_Ib, 	C_SAL,		D__Ev,		D__Ib,		D__NONE,	"SAL" 	,0xc1,1|C_GROUP_0_TYPE|(6<<16),MAKE_OP_RW_FLAG(OP_RW,OP_R,0)}, //0x6
	{R_M |Immediate_Ib, 	C_SAR,		D__Ev,		D__Ib,		D__NONE,	"SAR" 	,0xc1,1|C_GROUP_0_TYPE|(7<<16),MAKE_OP_RW_FLAG(OP_RW,OP_R,0)} //0x7

};

DIS_OPCODE_T Group0xc6[] = //mov group
{
	{R_M |Immediate_Ib,	C_MOV,		D__wEb,		D__Ib,		D__NONE,	"MOV" 	,0xc6,1|C_GROUP_0_TYPE|(0<<16),MAKE_OP_RW_FLAG(OP_W,OP_R,0)}, //0x0
	{R_M,	C_NULL													}, //0x1
	{R_M,	C_NULL													}, //0x2
	{R_M,	C_NULL													}, //0x3
	{R_M,	C_NULL													}, //0x4
	{R_M,	C_NULL													}, //0x5
	{R_M,	C_NULL													}, //0x6
	{R_M,	C_NULL													}, //0x7

};

DIS_OPCODE_T Group0xc7[] = //mov group
{
	{R_M |Immediate_Iz,	C_MOV,		D__wEv,		D__Iz,		D__NONE,	"MOV" 	,0xc7,1|C_GROUP_0_TYPE|(0<<16),MAKE_OP_RW_FLAG(OP_W,OP_R,0)}, //0x0
	{R_M,	C_NULL													}, //0x1
	{R_M,	C_NULL													}, //0x2
	{R_M,	C_NULL													}, //0x3
	{R_M,	C_NULL													}, //0x4
	{R_M,	C_NULL													}, //0x5
	{R_M,	C_NULL													}, //0x6
	{R_M,	C_NULL													}, //0x7

};

DIS_OPCODE_T Group0xd0[] = //shift group
{
	{R_M |Immediate_1, C_ROL,		D__Eb,		D__1,		D__NONE,	"ROL" 	,0xd0,1|C_GROUP_0_TYPE|(0<<16),MAKE_OP_RW_FLAG(OP_RW,OP_R,0)}, //0x0
	{R_M |Immediate_1, C_ROR,		D__Eb,		D__1,		D__NONE,	"ROR" 	,0xd0,1|C_GROUP_0_TYPE|(1<<16),MAKE_OP_RW_FLAG(OP_RW,OP_R,0)}, //0x1
	{R_M |Immediate_1, C_RCL,		D__Eb,		D__1,		D__NONE,	"RCL" 	,0xd0,1|C_GROUP_0_TYPE|(2<<16),MAKE_OP_RW_FLAG(OP_RW,OP_R,0)}, //0x2
	{R_M |Immediate_1, C_RCR,		D__Eb,		D__1,		D__NONE,	"RCR" 	,0xd0,1|C_GROUP_0_TYPE|(3<<16),MAKE_OP_RW_FLAG(OP_RW,OP_R,0)}, //0x3
	{R_M |Immediate_1, C_SHL,		D__Eb,		D__1,		D__NONE,	"SHL" 	,0xd0,1|C_GROUP_0_TYPE|(4<<16),MAKE_OP_RW_FLAG(OP_RW,OP_R,0)}, //0x4
	{R_M |Immediate_1, C_SHR,		D__Eb,		D__1,		D__NONE,	"SHR" 	,0xd0,1|C_GROUP_0_TYPE|(5<<16),MAKE_OP_RW_FLAG(OP_RW,OP_R,0)}, //0x5
	{R_M |Immediate_1, C_SAL,		D__Eb,		D__1,		D__NONE,	"SAL" 	,0xd0,1|C_GROUP_0_TYPE|(6<<16),MAKE_OP_RW_FLAG(OP_RW,OP_R,0)}, //0x6
	{R_M |Immediate_1, C_SAR,		D__Eb,		D__1,		D__NONE,	"SAR" 	,0xd0,1|C_GROUP_0_TYPE|(7<<16),MAKE_OP_RW_FLAG(OP_RW,OP_R,0)} //0x7

};

DIS_OPCODE_T Group0xd1[] = //shift group
{
	{R_M |Immediate_1, C_ROL,		D__Ev,		D__1,		D__NONE,	"ROL" 	,0xd1,1|C_GROUP_0_TYPE|(0<<16),MAKE_OP_RW_FLAG(OP_RW,OP_R,0)}, //0x0
	{R_M |Immediate_1, C_ROR,		D__Ev,		D__1,		D__NONE,	"ROR" 	,0xd1,1|C_GROUP_0_TYPE|(1<<16),MAKE_OP_RW_FLAG(OP_RW,OP_R,0)}, //0x1
	{R_M |Immediate_1, C_RCL,		D__Ev,		D__1,		D__NONE,	"RCL" 	,0xd1,1|C_GROUP_0_TYPE|(2<<16),MAKE_OP_RW_FLAG(OP_RW,OP_R,0)}, //0x2
	{R_M |Immediate_1, C_RCR,		D__Ev,		D__1,		D__NONE,	"RCR" 	,0xd1,1|C_GROUP_0_TYPE|(3<<16),MAKE_OP_RW_FLAG(OP_RW,OP_R,0)}, //0x3
	{R_M |Immediate_1, C_SHL,		D__Ev,		D__1,		D__NONE,	"SHL" 	,0xd1,1|C_GROUP_0_TYPE|(4<<16),MAKE_OP_RW_FLAG(OP_RW,OP_R,0)}, //0x4
	{R_M |Immediate_1, C_SHR,		D__Ev,		D__1,		D__NONE,	"SHR" 	,0xd1,1|C_GROUP_0_TYPE|(5<<16),MAKE_OP_RW_FLAG(OP_RW,OP_R,0)}, //0x5
	{R_M |Immediate_1, C_SAL,		D__Ev,		D__1,		D__NONE,	"SAL" 	,0xd1,1|C_GROUP_0_TYPE|(6<<16),MAKE_OP_RW_FLAG(OP_RW,OP_R,0)}, //0x6
	{R_M |Immediate_1, C_SAR,		D__Ev,		D__1,		D__NONE,	"SAR" 	,0xd1,1|C_GROUP_0_TYPE|(7<<16),MAKE_OP_RW_FLAG(OP_RW,OP_R,0)} //0x7

};

DIS_OPCODE_T Group0xd2[] = //shift group
{
	{R_M, C_ROL,		D__Eb,		D__CL,	D__NONE,	"ROL" 	,0xd2,1|C_GROUP_0_TYPE|(0<<16),MAKE_OP_RW_FLAG(OP_RW,OP_R,0)}, //0x0
	{R_M, C_ROR,		D__Eb,		D__CL,	D__NONE,	"ROR" 	,0xd2,1|C_GROUP_0_TYPE|(1<<16),MAKE_OP_RW_FLAG(OP_RW,OP_R,0)}, //0x1
	{R_M, C_RCL,		D__Eb,		D__CL,	D__NONE,	"RCL" 	,0xd2,1|C_GROUP_0_TYPE|(2<<16),MAKE_OP_RW_FLAG(OP_RW,OP_R,0)}, //0x2
	{R_M, C_RCR,		D__Eb,		D__CL,	D__NONE,	"RCR" 	,0xd2,1|C_GROUP_0_TYPE|(3<<16),MAKE_OP_RW_FLAG(OP_RW,OP_R,0)}, //0x3
	{R_M, C_SHL,		D__Eb,		D__CL,	D__NONE,	"SHL" 	,0xd2,1|C_GROUP_0_TYPE|(4<<16),MAKE_OP_RW_FLAG(OP_RW,OP_R,0)}, //0x4
	{R_M, C_SHR,		D__Eb,		D__CL,	D__NONE,	"SHR" 	,0xd2,1|C_GROUP_0_TYPE|(5<<16),MAKE_OP_RW_FLAG(OP_RW,OP_R,0)}, //0x5
	{R_M, C_SAL,		D__Eb,		D__CL,	D__NONE,	"SAL" 	,0xd2,1|C_GROUP_0_TYPE|(6<<16),MAKE_OP_RW_FLAG(OP_RW,OP_R,0)}, //0x6
	{R_M, C_SAR,		D__Eb,		D__CL,	D__NONE,	"SAR" 	,0xd2,1|C_GROUP_0_TYPE|C_GROUP_0_TYPE|(7<<16),MAKE_OP_RW_FLAG(OP_RW,OP_R,0)} //0x7

};

DIS_OPCODE_T Group0xd3[] = //shift group
{
	{R_M, C_ROL,		D__Ev,		D__CL,	D__NONE,	"ROL" 	,0xd3,1|C_GROUP_0_TYPE|(0<<16),MAKE_OP_RW_FLAG(OP_RW,OP_R,0)}, //0x0
	{R_M, C_ROR,		D__Ev,		D__CL,	D__NONE,	"ROR" 	,0xd3,1|C_GROUP_0_TYPE|(1<<16),MAKE_OP_RW_FLAG(OP_RW,OP_R,0)}, //0x1
	{R_M, C_RCL,		D__Ev,		D__CL,	D__NONE,	"RCL" 	,0xd3,1|C_GROUP_0_TYPE|(2<<16),MAKE_OP_RW_FLAG(OP_RW,OP_R,0)}, //0x2
	{R_M, C_RCR,		D__Ev,		D__CL,	D__NONE,	"RCR" 	,0xd3,1|C_GROUP_0_TYPE|(3<<16),MAKE_OP_RW_FLAG(OP_RW,OP_R,0)}, //0x3
	{R_M, C_SHL,		D__Ev,		D__CL,	D__NONE,	"SHL" 	,0xd3,1|C_GROUP_0_TYPE|(4<<16),MAKE_OP_RW_FLAG(OP_RW,OP_R,0)}, //0x4
	{R_M, C_SHR,		D__Ev,		D__CL,	D__NONE,	"SHR" 	,0xd3,1|C_GROUP_0_TYPE|(5<<16),MAKE_OP_RW_FLAG(OP_RW,OP_R,0)}, //0x5
	{R_M, C_SAL,		D__Ev,		D__CL,	D__NONE,	"SAL" 	,0xd3,1|C_GROUP_0_TYPE|(6<<16),MAKE_OP_RW_FLAG(OP_RW,OP_R,0)}, //0x6
	{R_M, C_SAR,		D__Ev,		D__CL,	D__NONE,	"SAR" 	,0xd3,1|C_GROUP_0_TYPE|(7<<16),MAKE_OP_RW_FLAG(OP_RW,OP_R,0)} //0x7

};

DIS_OPCODE_T Group0xf6[] = //test/not/neg/mul/div group
{
	{R_M |Immediate_Ib, C_TEST,	D__rEb,		D__Ib,		D__NONE,	"TEST" 	,0xf6,1|C_GROUP_0_TYPE|(0<<16),MAKE_OP_RW_FLAG(OP_R,OP_R,0)}, //0x0
	{0, C_NULL,		D__NONE,	D__NONE,	D__NONE,	NULL 	,0xf6,1|C_GROUP_0_TYPE|(1<<16)}, //0x1
	{R_M, C_NOT,	D__Eb,		D__NONE,	D__NONE,	"NOT" 	,0xf6,1|C_GROUP_0_TYPE|(2<<16),MAKE_OP_RW_FLAG(OP_RW,0,0)}, //0x2
	{R_M, C_NEG,	D__Eb,		D__NONE,	D__NONE,	"NEG" 	,0xf6,1|C_GROUP_0_TYPE|(3<<16),MAKE_OP_RW_FLAG(OP_RW,0,0)}, //0x3
	{R_M, C_MUL,	D__rEb,		D__NONE,	D__NONE,	"MUL" 	,0xf6,1|C_GROUP_0_TYPE|(4<<16),MAKE_OP_RW_FLAG(OP_R,0,0)}, //0x4
	{R_M, C_IMUL,	D__rEb,		D__NONE,	D__NONE,	"IMUL" 	,0xf6,1|C_GROUP_0_TYPE|(5<<16),MAKE_OP_RW_FLAG(OP_R,0,0)}, //0x5
	{R_M, C_DIV,	D__rEb,		D__NONE,	D__NONE,	"DIV" 	,0xf6,1|C_GROUP_0_TYPE|(6<<16),MAKE_OP_RW_FLAG(OP_R,0,0)}, //0x6
	{R_M, C_IDIV,	D__rEb,		D__NONE,	D__NONE,	"IDIV" 	,0xf6,1|C_GROUP_0_TYPE|(7<<16),MAKE_OP_RW_FLAG(OP_R,0,0)}, //0x7

};

DIS_OPCODE_T Group0xf7[] = //test/not/neg/mul/div group
{
	{R_M |Immediate_Iz,	C_TEST,	D__rEv,		D__Iz,		D__NONE,	"TEST" 	,0xf7,1|C_GROUP_0_TYPE|(0<<16),MAKE_OP_RW_FLAG(OP_R,OP_R,0)}, //0x0
	{0,C_NULL,	D__NONE,		D__NONE,	D__NONE,	NULL 	,0xf7,1|C_GROUP_0_TYPE|(1<<16)}, //0x1
	{R_M, C_NOT,	D__Ev,		D__NONE,	D__NONE,	"NOT" 	,0xf7,1|C_GROUP_0_TYPE|(2<<16),MAKE_OP_RW_FLAG(OP_RW,0,0)}, //0x2
	{R_M, C_NEG,	D__Ev,		D__NONE,	D__NONE,	"NEG" 	,0xf7,1|C_GROUP_0_TYPE|(3<<16),MAKE_OP_RW_FLAG(OP_RW,0,0)}, //0x3
	{R_M, C_MUL,	D__rEv,		D__NONE,	D__NONE,	"MUL" 	,0xf7,1|C_GROUP_0_TYPE|(4<<16),MAKE_OP_RW_FLAG(OP_R,0,0)}, //0x4
	{R_M, C_IMUL,	D__rEv,		D__NONE,	D__NONE,	"IMUL" 	,0xf7,1|C_GROUP_0_TYPE|(5<<16),MAKE_OP_RW_FLAG(OP_R,0,0)}, //0x5
	{R_M, C_DIV,	D__rEv,		D__NONE,	D__NONE,	"DIV" 	,0xf7,1|C_GROUP_0_TYPE|(6<<16),MAKE_OP_RW_FLAG(OP_R,0,0)}, //0x6
	{R_M, C_IDIV,	D__rEv,		D__NONE,	D__NONE,	"IDIV" 	,0xf7,1|C_GROUP_0_TYPE|(7<<16),MAKE_OP_RW_FLAG(OP_R,0,0)} //0x7
};

DIS_OPCODE_T Group0xfe[] = //inc/dec group
{
	{R_M, C_INC,	D__Eb,		D__NONE,	D__NONE,	"INC" 	,0xfe,1|C_GROUP_0_TYPE|(0<<16),MAKE_OP_RW_FLAG(OP_RW,0,0)}, //0x0
	{R_M, C_DEC,	D__Eb,		D__NONE,	D__NONE,	"DEC" 	,0xfe,1|C_GROUP_0_TYPE|(1<<16),MAKE_OP_RW_FLAG(OP_RW,0,0)}, //0x1
	{R_M, C_NULL												}, //0x2
	{R_M, C_NULL												}, //0x3
	{R_M, C_NULL												}, //0x4
	{R_M, C_NULL												}, //0x5
	{R_M, C_NULL												}, //0x6
	{R_M, C_NULL												}, //0x7

};

DIS_OPCODE_T Group0xff[] = //inc/dec/间接转移指令/push group
{
	{R_M, 		C_INC,	D__rwEv,	D__NONE,	D__NONE,	"INC" 	,0xff,1|C_GROUP_0_TYPE|(0<<16),MAKE_OP_RW_FLAG(OP_RW,0,0)}, //0x0
	{R_M, 		C_DEC,	D__rwEv,	D__NONE,	D__NONE,	"DEC" 	,0xff,1|C_GROUP_0_TYPE|(1<<16),MAKE_OP_RW_FLAG(OP_RW,0,0)}, //0x1
	{R_M|F_64,	C_CALL,	D__rEv,		D__NONE,	D__NONE,	"CALL" 	,0xff,1|C_GROUP_0_TYPE|(2<<16),MAKE_OP_RW_FLAG(OP_R,0,0)}, //0x2
	{R_M,		C_CALL,	D__rEp,		D__NONE,	D__NONE,	"CALL" 	,0xff,1|C_GROUP_0_TYPE|(3<<16),MAKE_OP_RW_FLAG(OP_R,0,0)}, //0x3
	{R_M|F_64,	C_JMP,	D__rEv,		D__NONE,	D__NONE,	"JMP" 	,0xff,1|C_GROUP_0_TYPE|(4<<16),MAKE_OP_RW_FLAG(OP_R,0,0)}, //0x4
	{R_M,		C_JMP,	D__rEp,		D__NONE,	D__NONE,	"JMP" 	,0xff,1|C_GROUP_0_TYPE|(5<<16),MAKE_OP_RW_FLAG(OP_R,0,0)}, //0x5
	{R_M|D_64, 	C_PUSH,	D__rEv,		D__NONE,	D__NONE,	"PUSH" 	,0xff,1|C_GROUP_0_TYPE|(6<<16),MAKE_OP_RW_FLAG(OP_R,0,0)}, //0x6
	{R_M,		C_NULL												} //0x7

};


DIS_OPCODE_T Group0x8f[] = //pop group
{
	{R_M | D_64, C_POP,	D__wEv,		D__NONE,	D__NONE,	"POP" 	,0x8f,1|C_GROUP_0_TYPE,MAKE_OP_RW_FLAG(OP_W,0,0)}, //0x0
	{R_M, C_NULL																}, //0x1
	{R_M, C_NULL																}, //0x2
	{R_M, C_NULL																}, //0x3
	{R_M, C_NULL																}, //0x4
	{R_M, C_NULL																}, //0x5
	{R_M, C_NULL																}, //0x6
	{R_M, C_NULL																}, //0x7

};


DIS_OPCODE_T Group0xd8[] = //fpu group
{
	{R_M, C_FADD,	D__single_real,	D__NONE,D__NONE,	"FADD" 		,0xd8,1|C_ESC_GROUP_TYPE|(0<<16),MAKE_OP_RW_FLAG(OP_R,0,0)}, //0x0
	{R_M, C_FMUL,	D__single_real,	D__NONE,D__NONE,	"FMUL" 		,0xd8,1|C_ESC_GROUP_TYPE|(1<<16),MAKE_OP_RW_FLAG(OP_R,0,0)}, //0x1
	{R_M, C_FCOM,	D__single_real,	D__NONE,D__NONE,	"FCOM" 		,0xd8,1|C_ESC_GROUP_TYPE|(2<<16),MAKE_OP_RW_FLAG(OP_R,0,0)}, //0x2
	{R_M, C_FCOMP,	D__single_real,	D__NONE,D__NONE,	"FCOMP" 	,0xd8,1|C_ESC_GROUP_TYPE|(3<<16),MAKE_OP_RW_FLAG(OP_R,0,0)}, //0x3
	{R_M, C_FSUB,	D__single_real,	D__NONE,D__NONE,	"FSUB" 		,0xd8,1|C_ESC_GROUP_TYPE|(4<<16),MAKE_OP_RW_FLAG(OP_R,0,0)}, //0x4
	{R_M, C_FSUBR,	D__single_real,	D__NONE,D__NONE,	"FSUBR" 	,0xd8,1|C_ESC_GROUP_TYPE|(5<<16),MAKE_OP_RW_FLAG(OP_R,0,0)}, //0x5
	{R_M, C_FDIV,	D__single_real,	D__NONE,D__NONE,	"FDIV" 		,0xd8,1|C_ESC_GROUP_TYPE|(6<<16),MAKE_OP_RW_FLAG(OP_R,0,0)}, //0x6
	{R_M, C_FDIVR,	D__single_real,	D__NONE,D__NONE,	"FDIVR" 	,0xd8,1|C_ESC_GROUP_TYPE|(7<<16),MAKE_OP_RW_FLAG(OP_R,0,0)}, //0x7

	//双字节浮点指令
	{ 0 , C_FADD,	D__st,		D__st0,		D__NONE,	"FADD" 		,0xc0d8,2|C_ESC_GROUP_TYPE|(8<<16) ,MAKE_OP_RW_FLAG(OP_RW,OP_R,0)}, //0xc0   
	{ 0 , C_FADD,	D__st,		D__st1,		D__NONE,	"FADD" 		,0xc1d8,2|C_ESC_GROUP_TYPE|(9<<16) ,MAKE_OP_RW_FLAG(OP_RW,OP_R,0)}, //0xc1   
	{ 0 , C_FADD,	D__st,		D__st2,		D__NONE,	"FADD" 		,0xc2d8,2|C_ESC_GROUP_TYPE|(10<<16),MAKE_OP_RW_FLAG(OP_RW,OP_R,0)}, //0xc2   
	{ 0 , C_FADD,	D__st,		D__st3,		D__NONE,	"FADD" 		,0xc3d8,2|C_ESC_GROUP_TYPE|(11<<16),MAKE_OP_RW_FLAG(OP_RW,OP_R,0)}, //0xc3   
	{ 0 , C_FADD,	D__st,		D__st4,		D__NONE,	"FADD" 		,0xc4d8,2|C_ESC_GROUP_TYPE|(12<<16),MAKE_OP_RW_FLAG(OP_RW,OP_R,0)}, //0xc4   
	{ 0 , C_FADD,	D__st,		D__st5,		D__NONE,	"FADD" 		,0xc5d8,2|C_ESC_GROUP_TYPE|(13<<16),MAKE_OP_RW_FLAG(OP_RW,OP_R,0)}, //0xc5   
	{ 0 , C_FADD,	D__st,		D__st6,		D__NONE,	"FADD" 		,0xc6d8,2|C_ESC_GROUP_TYPE|(14<<16),MAKE_OP_RW_FLAG(OP_RW,OP_R,0)}, //0xc6   
	{ 0 , C_FADD,	D__st,		D__st7,		D__NONE,	"FADD" 		,0xc7d8,2|C_ESC_GROUP_TYPE|(15<<16),MAKE_OP_RW_FLAG(OP_RW,OP_R,0)}, //0xc7   

	{ 0 , C_FMUL,	D__st,		D__st0,		D__NONE,	"FMUL" 		,0xc8d8,2|C_ESC_GROUP_TYPE|(16<<16),MAKE_OP_RW_FLAG(OP_RW,OP_R,0)}, //0xc8
	{ 0 , C_FMUL,	D__st,		D__st1,		D__NONE,	"FMUL" 		,0xc9d8,2|C_ESC_GROUP_TYPE|(17<<16),MAKE_OP_RW_FLAG(OP_RW,OP_R,0)}, //0xc9
	{ 0 , C_FMUL,	D__st,		D__st2,		D__NONE,	"FMUL" 		,0xcad8,2|C_ESC_GROUP_TYPE|(18<<16),MAKE_OP_RW_FLAG(OP_RW,OP_R,0)}, //0xca
	{ 0 , C_FMUL,	D__st,		D__st3,		D__NONE,	"FMUL" 		,0xcbd8,2|C_ESC_GROUP_TYPE|(19<<16),MAKE_OP_RW_FLAG(OP_RW,OP_R,0)}, //0xcb
	{ 0 , C_FMUL,	D__st,		D__st4,		D__NONE,	"FMUL" 		,0xccd8,2|C_ESC_GROUP_TYPE|(20<<16),MAKE_OP_RW_FLAG(OP_RW,OP_R,0)}, //0xcc
	{ 0 , C_FMUL,	D__st,		D__st5,		D__NONE,	"FMUL" 		,0xcdd8,2|C_ESC_GROUP_TYPE|(21<<16),MAKE_OP_RW_FLAG(OP_RW,OP_R,0)}, //0xcd
	{ 0 , C_FMUL,	D__st,		D__st6,		D__NONE,	"FMUL" 		,0xced8,2|C_ESC_GROUP_TYPE|(22<<16),MAKE_OP_RW_FLAG(OP_RW,OP_R,0)}, //0xce
	{ 0 , C_FMUL,	D__st,		D__st7,		D__NONE,	"FMUL" 		,0xcfd8,2|C_ESC_GROUP_TYPE|(23<<16),MAKE_OP_RW_FLAG(OP_RW,OP_R,0)}, //0xcf

	{ 0 , C_FCOM,	D__st,		D__st0,		D__NONE,	"FCOM" 		,0xd0d8,2|C_ESC_GROUP_TYPE|(24<<16),MAKE_OP_RW_FLAG(OP_R,OP_R,0)}, //0xd0
	{ 0 , C_FCOM,	D__st,		D__st1,		D__NONE,	"FCOM" 		,0xd1d8,2|C_ESC_GROUP_TYPE|(25<<16),MAKE_OP_RW_FLAG(OP_R,OP_R,0)}, //0xd1
	{ 0 , C_FCOM,	D__st,		D__st2,		D__NONE,	"FCOM" 		,0xd2d8,2|C_ESC_GROUP_TYPE|(26<<16),MAKE_OP_RW_FLAG(OP_R,OP_R,0)}, //0xd2
	{ 0 , C_FCOM,	D__st,		D__st3,		D__NONE,	"FCOM" 		,0xd3d8,2|C_ESC_GROUP_TYPE|(27<<16),MAKE_OP_RW_FLAG(OP_R,OP_R,0)}, //0xd3
	{ 0 , C_FCOM,	D__st,		D__st4,		D__NONE,	"FCOM" 		,0xd4d8,2|C_ESC_GROUP_TYPE|(28<<16),MAKE_OP_RW_FLAG(OP_R,OP_R,0)}, //0xd4
	{ 0 , C_FCOM,	D__st,		D__st5,		D__NONE,	"FCOM" 		,0xd5d8,2|C_ESC_GROUP_TYPE|(29<<16),MAKE_OP_RW_FLAG(OP_R,OP_R,0)}, //0xd5
	{ 0 , C_FCOM,	D__st,		D__st6,		D__NONE,	"FCOM" 		,0xd6d8,2|C_ESC_GROUP_TYPE|(30<<16),MAKE_OP_RW_FLAG(OP_R,OP_R,0)}, //0xd6
	{ 0 , C_FCOM,	D__st,		D__st7,		D__NONE,	"FCOM" 		,0xd7d8,2|C_ESC_GROUP_TYPE|(31<<16),MAKE_OP_RW_FLAG(OP_R,OP_R,0)}, //0xd7

	{ 0 , C_FCOMP,	D__st,		D__st0,		D__NONE,	"FCOMP" 	,0xd8d8,2|C_ESC_GROUP_TYPE|(32<<16),MAKE_OP_RW_FLAG(OP_R,OP_R,0)}, //0xd8
	{ 0 , C_FCOMP,	D__st,		D__st1,		D__NONE,	"FCOMP" 	,0xd9d8,2|C_ESC_GROUP_TYPE|(33<<16),MAKE_OP_RW_FLAG(OP_R,OP_R,0)}, //0xd9
	{ 0 , C_FCOMP,	D__st,		D__st2,		D__NONE,	"FCOMP" 	,0xdad8,2|C_ESC_GROUP_TYPE|(34<<16),MAKE_OP_RW_FLAG(OP_R,OP_R,0)}, //0xda
	{ 0 , C_FCOMP,	D__st,		D__st3,		D__NONE,	"FCOMP" 	,0xdbd8,2|C_ESC_GROUP_TYPE|(35<<16),MAKE_OP_RW_FLAG(OP_R,OP_R,0)}, //0xdb
	{ 0 , C_FCOMP,	D__st,		D__st4,		D__NONE,	"FCOMP" 	,0xdcd8,2|C_ESC_GROUP_TYPE|(36<<16),MAKE_OP_RW_FLAG(OP_R,OP_R,0)}, //0xdc
	{ 0 , C_FCOMP,	D__st,		D__st5,		D__NONE,	"FCOMP" 	,0xddd8,2|C_ESC_GROUP_TYPE|(37<<16),MAKE_OP_RW_FLAG(OP_R,OP_R,0)}, //0xdd
	{ 0 , C_FCOMP,	D__st,		D__st6,		D__NONE,	"FCOMP" 	,0xded8,2|C_ESC_GROUP_TYPE|(38<<16),MAKE_OP_RW_FLAG(OP_R,OP_R,0)}, //0xde
	{ 0 , C_FCOMP,	D__st,		D__st7,		D__NONE,	"FCOMP" 	,0xdfd8,2|C_ESC_GROUP_TYPE|(39<<16),MAKE_OP_RW_FLAG(OP_R,OP_R,0)}, //0xdf

	{ 0 , C_FSUB,	D__st,		D__st0,		D__NONE,	"FSUB" 		,0xe0d8,2|C_ESC_GROUP_TYPE|(40<<16),MAKE_OP_RW_FLAG(OP_RW,OP_R,0)}, //0xe0
	{ 0 , C_FSUB,	D__st,		D__st1,		D__NONE,	"FSUB" 		,0xe1d8,2|C_ESC_GROUP_TYPE|(41<<16),MAKE_OP_RW_FLAG(OP_RW,OP_R,0)}, //0xe1
	{ 0 , C_FSUB,	D__st,		D__st2,		D__NONE,	"FSUB" 		,0xe2d8,2|C_ESC_GROUP_TYPE|(42<<16),MAKE_OP_RW_FLAG(OP_RW,OP_R,0)}, //0xe2
	{ 0 , C_FSUB,	D__st,		D__st3,		D__NONE,	"FSUB" 		,0xe3d8,2|C_ESC_GROUP_TYPE|(43<<16),MAKE_OP_RW_FLAG(OP_RW,OP_R,0)}, //0xe3
	{ 0 , C_FSUB,	D__st,		D__st4,		D__NONE,	"FSUB" 		,0xe4d8,2|C_ESC_GROUP_TYPE|(44<<16),MAKE_OP_RW_FLAG(OP_RW,OP_R,0)}, //0xe4
	{ 0 , C_FSUB,	D__st,		D__st5,		D__NONE,	"FSUB" 		,0xe5d8,2|C_ESC_GROUP_TYPE|(45<<16),MAKE_OP_RW_FLAG(OP_RW,OP_R,0)}, //0xe5
	{ 0 , C_FSUB,	D__st,		D__st6,		D__NONE,	"FSUB" 		,0xe6d8,2|C_ESC_GROUP_TYPE|(46<<16),MAKE_OP_RW_FLAG(OP_RW,OP_R,0)}, //0xe6
	{ 0 , C_FSUB,	D__st,		D__st7,		D__NONE,	"FSUB" 		,0xe7d8,2|C_ESC_GROUP_TYPE|(47<<16),MAKE_OP_RW_FLAG(OP_RW,OP_R,0)}, //0xe7

	{ 0 , C_FSUBR,	D__st,		D__st0,		D__NONE,	"FSUBR" 	,0xe8d8,2|C_ESC_GROUP_TYPE|(48<<16),MAKE_OP_RW_FLAG(OP_RW,OP_R,0)}, //0xe8
	{ 0 , C_FSUBR,	D__st,		D__st1,		D__NONE,	"FSUBR" 	,0xe9d8,2|C_ESC_GROUP_TYPE|(49<<16),MAKE_OP_RW_FLAG(OP_RW,OP_R,0)}, //0xe9
	{ 0 , C_FSUBR,	D__st,		D__st2,		D__NONE,	"FSUBR" 	,0xead8,2|C_ESC_GROUP_TYPE|(50<<16),MAKE_OP_RW_FLAG(OP_RW,OP_R,0)}, //0xea
	{ 0 , C_FSUBR,	D__st,		D__st3,		D__NONE,	"FSUBR" 	,0xebd8,2|C_ESC_GROUP_TYPE|(51<<16),MAKE_OP_RW_FLAG(OP_RW,OP_R,0)}, //0xeb
	{ 0 , C_FSUBR,	D__st,		D__st4,		D__NONE,	"FSUBR" 	,0xecd8,2|C_ESC_GROUP_TYPE|(52<<16),MAKE_OP_RW_FLAG(OP_RW,OP_R,0)}, //0xec
	{ 0 , C_FSUBR,	D__st,		D__st5,		D__NONE,	"FSUBR" 	,0xedd8,2|C_ESC_GROUP_TYPE|(53<<16),MAKE_OP_RW_FLAG(OP_RW,OP_R,0)}, //0xed
	{ 0 , C_FSUBR,	D__st,		D__st6,		D__NONE,	"FSUBR" 	,0xeed8,2|C_ESC_GROUP_TYPE|(54<<16),MAKE_OP_RW_FLAG(OP_RW,OP_R,0)}, //0xee
	{ 0 , C_FSUBR,	D__st,		D__st7,		D__NONE,	"FSUBR" 	,0xefd8,2|C_ESC_GROUP_TYPE|(55<<16),MAKE_OP_RW_FLAG(OP_RW,OP_R,0)}, //0xef

	{ 0 , C_FDIV,	D__st,		D__st0,		D__NONE,	"FDIV" 		,0xf0d8,2|C_ESC_GROUP_TYPE|(56<<16),MAKE_OP_RW_FLAG(OP_RW,OP_R,0)}, //0xf0
	{ 0 , C_FDIV,	D__st,		D__st1,		D__NONE,	"FDIV" 		,0xf1d8,2|C_ESC_GROUP_TYPE|(57<<16),MAKE_OP_RW_FLAG(OP_RW,OP_R,0)}, //0xf1
	{ 0 , C_FDIV,	D__st,		D__st2,		D__NONE,	"FDIV" 		,0xf2d8,2|C_ESC_GROUP_TYPE|(58<<16),MAKE_OP_RW_FLAG(OP_RW,OP_R,0)}, //0xf2
	{ 0 , C_FDIV,	D__st,		D__st3,		D__NONE,	"FDIV" 		,0xf3d8,2|C_ESC_GROUP_TYPE|(59<<16),MAKE_OP_RW_FLAG(OP_RW,OP_R,0)}, //0xf3
	{ 0 , C_FDIV,	D__st,		D__st4,		D__NONE,	"FDIV" 		,0xf4d8,2|C_ESC_GROUP_TYPE|(60<<16),MAKE_OP_RW_FLAG(OP_RW,OP_R,0)}, //0xf4
	{ 0 , C_FDIV,	D__st,		D__st5,		D__NONE,	"FDIV" 		,0xf5d8,2|C_ESC_GROUP_TYPE|(61<<16),MAKE_OP_RW_FLAG(OP_RW,OP_R,0)}, //0xf5
	{ 0 , C_FDIV,	D__st,		D__st6,		D__NONE,	"FDIV" 		,0xf6d8,2|C_ESC_GROUP_TYPE|(62<<16),MAKE_OP_RW_FLAG(OP_RW,OP_R,0)}, //0xf6
	{ 0 , C_FDIV,	D__st,		D__st7,		D__NONE,	"FDIV" 		,0xf7d8,2|C_ESC_GROUP_TYPE|(63<<16),MAKE_OP_RW_FLAG(OP_RW,OP_R,0)}, //0xf7

	{ 0 , C_FDIVR,	D__st,		D__st0,		D__NONE,	"FDIVR" 	,0xf8d8,2|C_ESC_GROUP_TYPE|(64<<16),MAKE_OP_RW_FLAG(OP_RW,OP_R,0)}, //0xf8
	{ 0 , C_FDIVR,	D__st,		D__st1,		D__NONE,	"FDIVR" 	,0xf9d8,2|C_ESC_GROUP_TYPE|(65<<16),MAKE_OP_RW_FLAG(OP_RW,OP_R,0)}, //0xf9
	{ 0 , C_FDIVR,	D__st,		D__st2,		D__NONE,	"FDIVR" 	,0xfad8,2|C_ESC_GROUP_TYPE|(66<<16),MAKE_OP_RW_FLAG(OP_RW,OP_R,0)}, //0xfa
	{ 0 , C_FDIVR,	D__st,		D__st3,		D__NONE,	"FDIVR" 	,0xfbd8,2|C_ESC_GROUP_TYPE|(67<<16),MAKE_OP_RW_FLAG(OP_RW,OP_R,0)}, //0xfb
	{ 0 , C_FDIVR,	D__st,		D__st4,		D__NONE,	"FDIVR" 	,0xfcd8,2|C_ESC_GROUP_TYPE|(68<<16),MAKE_OP_RW_FLAG(OP_RW,OP_R,0)}, //0xfc
	{ 0 , C_FDIVR,	D__st,		D__st5,		D__NONE,	"FDIVR" 	,0xfdd8,2|C_ESC_GROUP_TYPE|(69<<16),MAKE_OP_RW_FLAG(OP_RW,OP_R,0)}, //0xfd
	{ 0 , C_FDIVR,	D__st,		D__st6,		D__NONE,	"FDIVR" 	,0xfed8,2|C_ESC_GROUP_TYPE|(70<<16),MAKE_OP_RW_FLAG(OP_RW,OP_R,0)}, //0xfe
	{ 0 , C_FDIVR,	D__st,		D__st7,		D__NONE,	"FDIVR" 	,0xffd8,2|C_ESC_GROUP_TYPE|(71<<16),MAKE_OP_RW_FLAG(OP_RW,OP_R,0)} //0xff

};


DIS_OPCODE_T Group0xd9[] = //fpu group
{
	{R_M, C_FLD,		D__single_real,	D__NONE,D__NONE,	"FLD" 		,0xd9,1|C_ESC_GROUP_TYPE|(0<<16),MAKE_OP_RW_FLAG(OP_R,0,0)}, //0x0
	{0, C_NULL														}, //0x1
	{R_M, C_FST,		D__single_real,	D__NONE,D__NONE,	"FST" 		,0xd9,1|C_ESC_GROUP_TYPE|(2<<16),MAKE_OP_RW_FLAG(OP_W,0,0)}, //0x2
	{R_M, C_FSTP,		D__single_real,	D__NONE,D__NONE,	"FSTP" 		,0xd9,1|C_ESC_GROUP_TYPE|(3<<16),MAKE_OP_RW_FLAG(OP_W,0,0)}, //0x3
	{R_M, C_FLDENV,		D__14_28b,		D__NONE,D__NONE,	"FLDENV" 	,0xd9,1|C_ESC_GROUP_TYPE|(4<<16),MAKE_OP_RW_FLAG(OP_R,0,0)}, //0x4
	{R_M, C_FLDCW,		D__2b,			D__NONE,D__NONE,	"FLDCW" 	,0xd9,1|C_ESC_GROUP_TYPE|(5<<16),MAKE_OP_RW_FLAG(OP_R,0,0)}, //0x5
	{R_M, C_FSTENV,		D__14_28b,		D__NONE,D__NONE,	"FSTENV" 	,0xd9,1|C_ESC_GROUP_TYPE|(6<<16),MAKE_OP_RW_FLAG(OP_W,0,0)}, //0x6
	{R_M, C_FSTCW,		D__2b,			D__NONE,D__NONE,	"FSTCW" 	,0xd9,1|C_ESC_GROUP_TYPE|(7<<16),MAKE_OP_RW_FLAG(OP_W,0,0)}, //0x7

	//双字节浮点指令
	{ 0 , C_FLD,		D__st,		D__st0,		D__NONE,	"FLD" 		,0xc0d9,2|C_ESC_GROUP_TYPE|(8<<16) ,MAKE_OP_RW_FLAG(OP_RW,OP_R,0)}, //0xc0
	{ 0 , C_FLD,		D__st,		D__st1,		D__NONE,	"FLD" 		,0xc1d9,2|C_ESC_GROUP_TYPE|(9<<16) ,MAKE_OP_RW_FLAG(OP_RW,OP_R,0)}, //0xc1
	{ 0 , C_FLD,		D__st,		D__st2,		D__NONE,	"FLD" 		,0xc2d9,2|C_ESC_GROUP_TYPE|(10<<16),MAKE_OP_RW_FLAG(OP_RW,OP_R,0)}, //0xc2
	{ 0 , C_FLD,		D__st,		D__st3,		D__NONE,	"FLD" 		,0xc3d9,2|C_ESC_GROUP_TYPE|(11<<16),MAKE_OP_RW_FLAG(OP_RW,OP_R,0)}, //0xc3
	{ 0 , C_FLD,		D__st,		D__st4,		D__NONE,	"FLD" 		,0xc4d9,2|C_ESC_GROUP_TYPE|(12<<16),MAKE_OP_RW_FLAG(OP_RW,OP_R,0)}, //0xc4
	{ 0 , C_FLD,		D__st,		D__st5,		D__NONE,	"FLD" 		,0xc5d9,2|C_ESC_GROUP_TYPE|(13<<16),MAKE_OP_RW_FLAG(OP_RW,OP_R,0)}, //0xc5
	{ 0 , C_FLD,		D__st,		D__st6,		D__NONE,	"FLD" 		,0xc6d9,2|C_ESC_GROUP_TYPE|(14<<16),MAKE_OP_RW_FLAG(OP_RW,OP_R,0)}, //0xc6
	{ 0 , C_FLD,		D__st,		D__st7,		D__NONE,	"FLD" 		,0xc7d9,2|C_ESC_GROUP_TYPE|(15<<16),MAKE_OP_RW_FLAG(OP_RW,OP_R,0)}, //0xc7

	{ 0 , C_FXCH,	D__st,		D__st0,		D__NONE,	"FXCH" 		,0xc8d9,2|C_ESC_GROUP_TYPE|(16<<16),MAKE_OP_RW_FLAG(OP_RW,OP_RW,0)}, //0xc8
	{ 0 , C_FXCH,	D__st,		D__st1,		D__NONE,	"FXCH" 		,0xc9d9,2|C_ESC_GROUP_TYPE|(17<<16),MAKE_OP_RW_FLAG(OP_RW,OP_RW,0)}, //0xc9
	{ 0 , C_FXCH,	D__st,		D__st2,		D__NONE,	"FXCH" 		,0xcad9,2|C_ESC_GROUP_TYPE|(18<<16),MAKE_OP_RW_FLAG(OP_RW,OP_RW,0)}, //0xca
	{ 0 , C_FXCH,	D__st,		D__st3,		D__NONE,	"FXCH" 		,0xcbd9,2|C_ESC_GROUP_TYPE|(19<<16),MAKE_OP_RW_FLAG(OP_RW,OP_RW,0)}, //0xcb
	{ 0 , C_FXCH,	D__st,		D__st4,		D__NONE,	"FXCH" 		,0xccd9,2|C_ESC_GROUP_TYPE|(20<<16),MAKE_OP_RW_FLAG(OP_RW,OP_RW,0)}, //0xcc
	{ 0 , C_FXCH,	D__st,		D__st5,		D__NONE,	"FXCH" 		,0xcdd9,2|C_ESC_GROUP_TYPE|(21<<16),MAKE_OP_RW_FLAG(OP_RW,OP_RW,0)}, //0xcd
	{ 0 , C_FXCH,	D__st,		D__st6,		D__NONE,	"FXCH" 		,0xced9,2|C_ESC_GROUP_TYPE|(22<<16),MAKE_OP_RW_FLAG(OP_RW,OP_RW,0)}, //0xce
	{ 0 , C_FXCH,	D__st,		D__st7,		D__NONE,	"FXCH" 		,0xcfd9,2|C_ESC_GROUP_TYPE|(23<<16),MAKE_OP_RW_FLAG(OP_RW,OP_RW,0)}, //0xcf

	{ 0 , C_FNOP,	D__NONE,	D__NONE,	D__NONE,	"FNOP" 		,0xd0d9,2|C_ESC_GROUP_TYPE|(24<<16)}, //0xd0
	{ 0 , C_NULL													}, //0xd1
	{ 0 , C_NULL													}, //0xd2
	{ 0 , C_NULL													}, //0xd3
	{ 0 , C_NULL													}, //0xd4
	{ 0 , C_NULL													}, //0xd5
	{ 0 , C_NULL													}, //0xd6
	{ 0 , C_NULL													}, //0xd7

	{ 0 , C_NULL													}, //0xd8
	{ 0 , C_NULL													}, //0xd9
	{ 0 , C_NULL													}, //0xda
	{ 0 , C_NULL													}, //0xdb
	{ 0 , C_NULL													}, //0xdc
	{ 0 , C_NULL													}, //0xdd
	{ 0 , C_NULL													}, //0xde
	{ 0 , C_NULL													}, //0xdf

	{ 0 , C_FCHS,	D__NONE,	D__NONE,	D__NONE,	"FCHS" 		,0xe0d9,2|C_ESC_GROUP_TYPE|(40<<16)}, //0xe0
	{ 0 , C_FABS,	D__NONE,	D__NONE,	D__NONE,	"FABS" 		,0xe1d9,2|C_ESC_GROUP_TYPE|(41<<16)}, //0xe1
	{ 0 , C_NULL													}, //0xe2
	{ 0 , C_NULL													}, //0xe3
	{ 0 , C_FTST,	D__NONE,	D__NONE,	D__NONE,	"FTST" 		,0xe4d9,2|C_ESC_GROUP_TYPE|(44<<16)}, //0xe4
	{ 0 , C_FXAM,	D__NONE,	D__NONE,	D__NONE,	"FXAM" 		,0xe5d9,2|C_ESC_GROUP_TYPE|(45<<16)}, //0xe5
	{ 0 , C_NULL													}, //0xe6
	{ 0 , C_NULL													}, //0xe7

	{ 0 , C_FLD1,		D__NONE,	D__NONE,	D__NONE,	"FLD1" 		,0xe8d9,2|C_ESC_GROUP_TYPE|(48<<16)}, //0xe8
	{ 0 , C_FLDL2T,		D__NONE,	D__NONE,	D__NONE,	"FLDL2T" 	,0xe9d9,2|C_ESC_GROUP_TYPE|(49<<16)}, //0xe9
	{ 0 , C_FLDL2E,		D__NONE,	D__NONE,	D__NONE,	"FLDL2E" 	,0xead9,2|C_ESC_GROUP_TYPE|(50<<16)}, //0xea
	{ 0 , C_FLDPI,		D__NONE,	D__NONE,	D__NONE,	"FLDPI" 	,0xebd9,2|C_ESC_GROUP_TYPE|(51<<16)}, //0xeb
	{ 0 , C_FLDLG2,		D__NONE,	D__NONE,	D__NONE,	"FLDLG2" 	,0xecd9,2|C_ESC_GROUP_TYPE|(52<<16)}, //0xec
	{ 0 , C_FLDLN2,		D__NONE,	D__NONE,	D__NONE,	"FLDLN2" 	,0xedd9,2|C_ESC_GROUP_TYPE|(53<<16)}, //0xed
	{ 0 , C_FLDZ,		D__NONE,	D__NONE,	D__NONE,	"FLDZ" 		,0xeed9,2|C_ESC_GROUP_TYPE|(54<<16)}, //0xee
	{ 0 , C_NULL													}, //0xef

	{ 0 , C_F2XM1,	D__NONE,	D__NONE,	D__NONE,	"F2XM1" 	,0xf0d9,2|C_ESC_GROUP_TYPE|(56<<16)}, //0xf0
	{ 0 , C_FYL2X,	D__NONE,	D__NONE,	D__NONE,	"FYL2X" 	,0xf1d9,2|C_ESC_GROUP_TYPE|(57<<16)}, //0xf1
	{ 0 , C_FPTAN,	D__NONE,	D__NONE,	D__NONE,	"FPTAN" 	,0xf2d9,2|C_ESC_GROUP_TYPE|(58<<16)}, //0xf2
	{ 0 , C_FPATAN,	D__NONE,	D__NONE,	D__NONE,	"FPATAN" 	,0xf3d9,2|C_ESC_GROUP_TYPE|(59<<16)}, //0xf3
	{ 0 , C_FXTRACT,D__NONE,	D__NONE,	D__NONE,	"FXTRACT" 	,0xf4d9,2|C_ESC_GROUP_TYPE|(60<<16)}, //0xf4
	{ 0 , C_FPREM1,	D__NONE,	D__NONE,	D__NONE,	"FPREM1" 	,0xf5d9,2|C_ESC_GROUP_TYPE|(61<<16)}, //0xf5
	{ 0 , C_FDECSTP,D__NONE,	D__NONE,	D__NONE,	"FDECSTP" 	,0xf6d9,2|C_ESC_GROUP_TYPE|(62<<16)}, //0xf6
	{ 0 , C_FINCSTP,D__NONE,	D__NONE,	D__NONE,	"FINCSTP" 	,0xf7d9,2|C_ESC_GROUP_TYPE|(63<<16)}, //0xf7

	{ 0 , C_FPREM,	D__NONE,	D__NONE,	D__NONE,	"FPREM" 	,0xf8d9,2|C_ESC_GROUP_TYPE|(64<<16)}, //0xf8
	{ 0 , C_FYL2XP1,D__NONE,	D__NONE,	D__NONE,	"FYL2XP1" 	,0xf9d9,2|C_ESC_GROUP_TYPE|(65<<16)}, //0xf9
	{ 0 , C_FSQRT,	D__NONE,	D__NONE,	D__NONE,	"FSQRT" 	,0xfad9,2|C_ESC_GROUP_TYPE|(66<<16)}, //0xfa
	{ 0 , C_FSINCOS,D__NONE,	D__NONE,	D__NONE,	"FSINCOS" 	,0xfbd9,2|C_ESC_GROUP_TYPE|(67<<16)}, //0xfb
	{ 0 , C_FRNDINT,D__NONE,	D__NONE,	D__NONE,	"FRNDINT" 	,0xfcd9,2|C_ESC_GROUP_TYPE|(68<<16)}, //0xfc
	{ 0 , C_FSCALE,	D__NONE,	D__NONE,	D__NONE,	"FSCALE" 	,0xfdd9,2|C_ESC_GROUP_TYPE|(69<<16)}, //0xfd
	{ 0 , C_FSIN,	D__NONE,	D__NONE,	D__NONE,	"FSIN" 		,0xfed9,2|C_ESC_GROUP_TYPE|(70<<16)}, //0xfe
	{ 0 , C_FCOS,	D__NONE,	D__NONE,	D__NONE,	"FCOS" 		,0xffd9,2|C_ESC_GROUP_TYPE|(71<<16)} //0xff

};


DIS_OPCODE_T Group0xda[] = //fpu group
{
	{R_M, C_FIADD,	D__dword_int,D__NONE,D__NONE,	"FIADD" 	,0xda,1|C_ESC_GROUP_TYPE|(0<<16),MAKE_OP_RW_FLAG(OP_R,0,0)}, //0x0
	{R_M, C_FIMUL,	D__dword_int,D__NONE,D__NONE,	"FIMUL" 	,0xda,1|C_ESC_GROUP_TYPE|(1<<16),MAKE_OP_RW_FLAG(OP_R,0,0)}, //0x1
	{R_M, C_FICOM,	D__dword_int,D__NONE,D__NONE,	"FICOM" 	,0xda,1|C_ESC_GROUP_TYPE|(2<<16),MAKE_OP_RW_FLAG(OP_R,0,0)}, //0x2
	{R_M, C_FICOMP,	D__dword_int,D__NONE,D__NONE,	"FICOMP" 	,0xda,1|C_ESC_GROUP_TYPE|(3<<16),MAKE_OP_RW_FLAG(OP_R,0,0)}, //0x3
	{R_M, C_FISUB,	D__dword_int,D__NONE,D__NONE,	"FISUB" 	,0xda,1|C_ESC_GROUP_TYPE|(4<<16),MAKE_OP_RW_FLAG(OP_R,0,0)}, //0x4
	{R_M, C_FISUBR,	D__dword_int,D__NONE,D__NONE,	"FISUBR" 	,0xda,1|C_ESC_GROUP_TYPE|(5<<16),MAKE_OP_RW_FLAG(OP_R,0,0)}, //0x5
	{R_M, C_FIDIV,	D__dword_int,D__NONE,D__NONE,	"FIDIV" 	,0xda,1|C_ESC_GROUP_TYPE|(6<<16),MAKE_OP_RW_FLAG(OP_R,0,0)}, //0x6
	{R_M, C_FIDIVR,	D__dword_int,D__NONE,D__NONE,	"FIDIVR" 	,0xda,1|C_ESC_GROUP_TYPE|(7<<16),MAKE_OP_RW_FLAG(OP_R,0,0)}, //0x7

	//双字节浮点指令
	{ 0 , C_FCMOVB,	D__st,		D__st0,		D__NONE,	"FCMOVB" 	,0xc0da,2|C_ESC_GROUP_TYPE|(8<<16) ,MAKE_OP_RW_FLAG(OP_R,OP_R,0)}, //0xc0
	{ 0 , C_FCMOVB,	D__st,		D__st1,		D__NONE,	"FCMOVB" 	,0xc1da,2|C_ESC_GROUP_TYPE|(9<<16) ,MAKE_OP_RW_FLAG(OP_R,OP_R,0)}, //0xc1
	{ 0 , C_FCMOVB,	D__st,		D__st2,		D__NONE,	"FCMOVB" 	,0xc2da,2|C_ESC_GROUP_TYPE|(10<<16),MAKE_OP_RW_FLAG(OP_R,OP_R,0)}, //0xc2
	{ 0 , C_FCMOVB,	D__st,		D__st3,		D__NONE,	"FCMOVB" 	,0xc3da,2|C_ESC_GROUP_TYPE|(11<<16),MAKE_OP_RW_FLAG(OP_R,OP_R,0)}, //0xc3
	{ 0 , C_FCMOVB,	D__st,		D__st4,		D__NONE,	"FCMOVB" 	,0xc4da,2|C_ESC_GROUP_TYPE|(12<<16),MAKE_OP_RW_FLAG(OP_R,OP_R,0)}, //0xc4
	{ 0 , C_FCMOVB,	D__st,		D__st5,		D__NONE,	"FCMOVB" 	,0xc5da,2|C_ESC_GROUP_TYPE|(13<<16),MAKE_OP_RW_FLAG(OP_R,OP_R,0)}, //0xc5
	{ 0 , C_FCMOVB,	D__st,		D__st6,		D__NONE,	"FCMOVB" 	,0xc6da,2|C_ESC_GROUP_TYPE|(14<<16),MAKE_OP_RW_FLAG(OP_R,OP_R,0)}, //0xc6
	{ 0 , C_FCMOVB,	D__st,		D__st7,		D__NONE,	"FCMOVB" 	,0xc7da,2|C_ESC_GROUP_TYPE|(15<<16),MAKE_OP_RW_FLAG(OP_R,OP_R,0)}, //0xc7

	{ 0 , C_FCMOVE,	D__st,		D__st0,		D__NONE,	"FCMOVE" 	,0xc8da,2|C_ESC_GROUP_TYPE|(16<<16),MAKE_OP_RW_FLAG(OP_R,OP_R,0)}, //0xc8
	{ 0 , C_FCMOVE,	D__st,		D__st1,		D__NONE,	"FCMOVE" 	,0xc9da,2|C_ESC_GROUP_TYPE|(17<<16),MAKE_OP_RW_FLAG(OP_R,OP_R,0)}, //0xc9
	{ 0 , C_FCMOVE,	D__st,		D__st2,		D__NONE,	"FCMOVE" 	,0xcada,2|C_ESC_GROUP_TYPE|(18<<16),MAKE_OP_RW_FLAG(OP_R,OP_R,0)}, //0xca
	{ 0 , C_FCMOVE,	D__st,		D__st3,		D__NONE,	"FCMOVE" 	,0xcbda,2|C_ESC_GROUP_TYPE|(19<<16),MAKE_OP_RW_FLAG(OP_R,OP_R,0)}, //0xcb
	{ 0 , C_FCMOVE,	D__st,		D__st4,		D__NONE,	"FCMOVE" 	,0xccda,2|C_ESC_GROUP_TYPE|(20<<16),MAKE_OP_RW_FLAG(OP_R,OP_R,0)}, //0xcc
	{ 0 , C_FCMOVE,	D__st,		D__st5,		D__NONE,	"FCMOVE" 	,0xcdda,2|C_ESC_GROUP_TYPE|(21<<16),MAKE_OP_RW_FLAG(OP_R,OP_R,0)}, //0xcd
	{ 0 , C_FCMOVE,	D__st,		D__st6,		D__NONE,	"FCMOVE" 	,0xceda,2|C_ESC_GROUP_TYPE|(22<<16),MAKE_OP_RW_FLAG(OP_R,OP_R,0)}, //0xce
	{ 0 , C_FCMOVE,	D__st,		D__st7,		D__NONE,	"FCMOVE" 	,0xcfda,2|C_ESC_GROUP_TYPE|(23<<16),MAKE_OP_RW_FLAG(OP_R,OP_R,0)}, //0xcf

	{ 0 , C_FCMOVBE,	D__st,		D__st0,		D__NONE,	"FCMOVBE" 	,0xd0da,2|C_ESC_GROUP_TYPE|(24<<16),MAKE_OP_RW_FLAG(OP_R,OP_R,0)}, //0xd0
	{ 0 , C_FCMOVBE,	D__st,		D__st1,		D__NONE,	"FCMOVBE" 	,0xd1da,2|C_ESC_GROUP_TYPE|(25<<16),MAKE_OP_RW_FLAG(OP_R,OP_R,0)}, //0xd1
	{ 0 , C_FCMOVBE,	D__st,		D__st2,		D__NONE,	"FCMOVBE" 	,0xd2da,2|C_ESC_GROUP_TYPE|(26<<16),MAKE_OP_RW_FLAG(OP_R,OP_R,0)}, //0xd2
	{ 0 , C_FCMOVBE,	D__st,		D__st3,		D__NONE,	"FCMOVBE" 	,0xd3da,2|C_ESC_GROUP_TYPE|(27<<16),MAKE_OP_RW_FLAG(OP_R,OP_R,0)}, //0xd3
	{ 0 , C_FCMOVBE,	D__st,		D__st4,		D__NONE,	"FCMOVBE" 	,0xd4da,2|C_ESC_GROUP_TYPE|(28<<16),MAKE_OP_RW_FLAG(OP_R,OP_R,0)}, //0xd4
	{ 0 , C_FCMOVBE,	D__st,		D__st5,		D__NONE,	"FCMOVBE" 	,0xd5da,2|C_ESC_GROUP_TYPE|(29<<16),MAKE_OP_RW_FLAG(OP_R,OP_R,0)}, //0xd5
	{ 0 , C_FCMOVBE,	D__st,		D__st6,		D__NONE,	"FCMOVBE" 	,0xd6da,2|C_ESC_GROUP_TYPE|(30<<16),MAKE_OP_RW_FLAG(OP_R,OP_R,0)}, //0xd6
	{ 0 , C_FCMOVBE,	D__st,		D__st7,		D__NONE,	"FCMOVBE" 	,0xd7da,2|C_ESC_GROUP_TYPE|(31<<16),MAKE_OP_RW_FLAG(OP_R,OP_R,0)}, //0xd7

	{ 0 , C_FCMOVU,	D__st,		D__st0,		D__NONE,	"FCMOVU" 	,0xd8da,2|C_ESC_GROUP_TYPE|(32<<16),MAKE_OP_RW_FLAG(OP_R,OP_R,0)}, //0xd8
	{ 0 , C_FCMOVU,	D__st,		D__st1,		D__NONE,	"FCMOVU" 	,0xd9da,2|C_ESC_GROUP_TYPE|(33<<16),MAKE_OP_RW_FLAG(OP_R,OP_R,0)}, //0xd9
	{ 0 , C_FCMOVU,	D__st,		D__st2,		D__NONE,	"FCMOVU" 	,0xdada,2|C_ESC_GROUP_TYPE|(34<<16),MAKE_OP_RW_FLAG(OP_R,OP_R,0)}, //0xda
	{ 0 , C_FCMOVU,	D__st,		D__st3,		D__NONE,	"FCMOVU" 	,0xdbda,2|C_ESC_GROUP_TYPE|(35<<16),MAKE_OP_RW_FLAG(OP_R,OP_R,0)}, //0xdb
	{ 0 , C_FCMOVU,	D__st,		D__st4,		D__NONE,	"FCMOVU" 	,0xdcda,2|C_ESC_GROUP_TYPE|(36<<16),MAKE_OP_RW_FLAG(OP_R,OP_R,0)}, //0xdc
	{ 0 , C_FCMOVU,	D__st,		D__st5,		D__NONE,	"FCMOVU" 	,0xddda,2|C_ESC_GROUP_TYPE|(37<<16),MAKE_OP_RW_FLAG(OP_R,OP_R,0)}, //0xdd
	{ 0 , C_FCMOVU,	D__st,		D__st6,		D__NONE,	"FCMOVU" 	,0xdeda,2|C_ESC_GROUP_TYPE|(38<<16),MAKE_OP_RW_FLAG(OP_R,OP_R,0)}, //0xde
	{ 0 , C_FCMOVU,	D__st,		D__st7,		D__NONE,	"FCMOVU" 	,0xdfda,2|C_ESC_GROUP_TYPE|(39<<16),MAKE_OP_RW_FLAG(OP_R,OP_R,0)}, //0xdf

	{ 0 , C_NULL													}, //0xe0
	{ 0 , C_NULL													}, //0xe1
	{ 0 , C_NULL													}, //0xe2
	{ 0 , C_NULL													}, //0xe3
	{ 0 , C_NULL													}, //0xe4
	{ 0 , C_NULL													}, //0xe5
	{ 0 , C_NULL													}, //0xe6
	{ 0 , C_NULL													}, //0xe7

	{ 0 , C_NULL													}, //0xe8
	{ 0 , C_FUCOMPP,	D__NONE,	D__NONE,	D__NONE,	"FUCOMPP" 	,0xe9da,2|C_ESC_GROUP_TYPE|(49<<16)}, //0xe9
	{ 0 , C_NULL													}, //0xea
	{ 0 , C_NULL													}, //0xeb
	{ 0 , C_NULL													}, //0xec
	{ 0 , C_NULL													}, //0xed
	{ 0 , C_NULL													}, //0xee
	{ 0 , C_NULL													}, //0xef

	{ 0 , C_NULL													}, //0xf0
	{ 0 , C_NULL													}, //0xf1
	{ 0 , C_NULL													}, //0xf2
	{ 0 , C_NULL													}, //0xf3
	{ 0 , C_NULL													}, //0xf4
	{ 0 , C_NULL													}, //0xf5
	{ 0 , C_NULL													}, //0xf6
	{ 0 , C_NULL													}, //0xf7

	{ 0 , C_NULL													}, //0xf8
	{ 0 , C_NULL													}, //0xf9
	{ 0 , C_NULL													}, //0xfa
	{ 0 , C_NULL													}, //0xfb
	{ 0 , C_NULL													}, //0xfc
	{ 0 , C_NULL													}, //0xfd
	{ 0 , C_NULL													}, //0xfe
	{ 0 , C_NULL													} //0xff

};


DIS_OPCODE_T Group0xdb[] = //fpu group
{
	{R_M, C_FILD,	D__dword_int,	D__NONE,D__NONE,	"FILD" 		,0xdb,1|C_ESC_GROUP_TYPE|(0<<16),MAKE_OP_RW_FLAG(OP_R,0,0)}, //0x0
	{R_M, C_FISTTP, D__dword_int,	D__NONE,D__NONE,	"FISTTP" 	,0xdb,1|C_ESC_GROUP_TYPE|(1<<16),MAKE_OP_RW_FLAG(OP_W,0,0)}, //0x1
	{R_M, C_FIST,	D__dword_int,	D__NONE,D__NONE,	"FIST" 		,0xdb,1|C_ESC_GROUP_TYPE|(2<<16),MAKE_OP_RW_FLAG(OP_W,0,0)}, //0x2
	{R_M, C_FISTP,	D__dword_int,	D__NONE,D__NONE,	"FISTP" 	,0xdb,1|C_ESC_GROUP_TYPE|(3<<16),MAKE_OP_RW_FLAG(OP_W,0,0)}, //0x3
	{R_M, C_NULL													}, //0x4
	{R_M, C_FLD,	D__extend_real,	D__NONE,D__NONE,	"FLD" 		,0xdb,1|C_ESC_GROUP_TYPE|(5<<16),MAKE_OP_RW_FLAG(OP_R,0,0)}, //0x5
	{R_M, C_NULL													}, //0x6
	{R_M, C_FSTP,	D__extend_real,	D__NONE,D__NONE,	"FSTP" 		,0xdb,1|C_ESC_GROUP_TYPE|(7<<16),MAKE_OP_RW_FLAG(OP_W,0,0)}, //0x7

	//双字节浮点指令
	{ 0 , C_FCMOVNB,	D__st,		D__st0,		D__NONE,	"FCMOVNB" 	,0xc0db,2|C_ESC_GROUP_TYPE|(8<<16) ,MAKE_OP_RW_FLAG(0,OP_R,0)}, //0xc0
	{ 0 , C_FCMOVNB,	D__st,		D__st1,		D__NONE,	"FCMOVNB" 	,0xc1db,2|C_ESC_GROUP_TYPE|(9<<16) ,MAKE_OP_RW_FLAG(0,OP_R,0)}, //0xc1
	{ 0 , C_FCMOVNB,	D__st,		D__st2,		D__NONE,	"FCMOVNB" 	,0xc2db,2|C_ESC_GROUP_TYPE|(10<<16),MAKE_OP_RW_FLAG(0,OP_R,0)}, //0xc2
	{ 0 , C_FCMOVNB,	D__st,		D__st3,		D__NONE,	"FCMOVNB" 	,0xc3db,2|C_ESC_GROUP_TYPE|(11<<16),MAKE_OP_RW_FLAG(0,OP_R,0)}, //0xc3
	{ 0 , C_FCMOVNB,	D__st,		D__st4,		D__NONE,	"FCMOVNB" 	,0xc4db,2|C_ESC_GROUP_TYPE|(12<<16),MAKE_OP_RW_FLAG(0,OP_R,0)}, //0xc4
	{ 0 , C_FCMOVNB,	D__st,		D__st5,		D__NONE,	"FCMOVNB" 	,0xc5db,2|C_ESC_GROUP_TYPE|(13<<16),MAKE_OP_RW_FLAG(0,OP_R,0)}, //0xc5
	{ 0 , C_FCMOVNB,	D__st,		D__st6,		D__NONE,	"FCMOVNB" 	,0xc6db,2|C_ESC_GROUP_TYPE|(14<<16),MAKE_OP_RW_FLAG(0,OP_R,0)}, //0xc6
	{ 0 , C_FCMOVNB,	D__st,		D__st7,		D__NONE,	"FCMOVNB" 	,0xc7db,2|C_ESC_GROUP_TYPE|(15<<16),MAKE_OP_RW_FLAG(0,OP_R,0)}, //0xc7

	{ 0 , C_FCMOVNE,	D__st,		D__st0,		D__NONE,	"FCMOVNE" 	,0xc8db,2|C_ESC_GROUP_TYPE|(16<<16),MAKE_OP_RW_FLAG(0,OP_R,0)}, //0xc8
	{ 0 , C_FCMOVNE,	D__st,		D__st1,		D__NONE,	"FCMOVNE" 	,0xc9db,2|C_ESC_GROUP_TYPE|(17<<16),MAKE_OP_RW_FLAG(0,OP_R,0)}, //0xc9
	{ 0 , C_FCMOVNE,	D__st,		D__st2,		D__NONE,	"FCMOVNE" 	,0xcadb,2|C_ESC_GROUP_TYPE|(18<<16),MAKE_OP_RW_FLAG(0,OP_R,0)}, //0xca
	{ 0 , C_FCMOVNE,	D__st,		D__st3,		D__NONE,	"FCMOVNE" 	,0xcbdb,2|C_ESC_GROUP_TYPE|(19<<16),MAKE_OP_RW_FLAG(0,OP_R,0)}, //0xcb
	{ 0 , C_FCMOVNE,	D__st,		D__st4,		D__NONE,	"FCMOVNE" 	,0xccdb,2|C_ESC_GROUP_TYPE|(20<<16),MAKE_OP_RW_FLAG(0,OP_R,0)}, //0xcc
	{ 0 , C_FCMOVNE,	D__st,		D__st5,		D__NONE,	"FCMOVNE" 	,0xcddb,2|C_ESC_GROUP_TYPE|(21<<16),MAKE_OP_RW_FLAG(0,OP_R,0)}, //0xcd
	{ 0 , C_FCMOVNE,	D__st,		D__st6,		D__NONE,	"FCMOVNE" 	,0xcedb,2|C_ESC_GROUP_TYPE|(22<<16),MAKE_OP_RW_FLAG(0,OP_R,0)}, //0xce
	{ 0 , C_FCMOVNE,	D__st,		D__st7,		D__NONE,	"FCMOVNE" 	,0xcfdb,2|C_ESC_GROUP_TYPE|(23<<16),MAKE_OP_RW_FLAG(0,OP_R,0)}, //0xcf

	{ 0 , C_FCMOVNBE,D__st,		D__st0,		D__NONE,	"FCMOVNBE" 	,0xd0db,2|C_ESC_GROUP_TYPE|(24<<16),MAKE_OP_RW_FLAG(0,OP_R,0)}, //0xd0
	{ 0 , C_FCMOVNBE,D__st,		D__st1,		D__NONE,	"FCMOVNBE" 	,0xd1db,2|C_ESC_GROUP_TYPE|(25<<16),MAKE_OP_RW_FLAG(0,OP_R,0)}, //0xd1
	{ 0 , C_FCMOVNBE,D__st,		D__st2,		D__NONE,	"FCMOVNBE" 	,0xd2db,2|C_ESC_GROUP_TYPE|(26<<16),MAKE_OP_RW_FLAG(0,OP_R,0)}, //0xd2
	{ 0 , C_FCMOVNBE,D__st,		D__st3,		D__NONE,	"FCMOVNBE" 	,0xd3db,2|C_ESC_GROUP_TYPE|(27<<16),MAKE_OP_RW_FLAG(0,OP_R,0)}, //0xd3
	{ 0 , C_FCMOVNBE,D__st,		D__st4,		D__NONE,	"FCMOVNBE" 	,0xd4db,2|C_ESC_GROUP_TYPE|(28<<16),MAKE_OP_RW_FLAG(0,OP_R,0)}, //0xd4
	{ 0 , C_FCMOVNBE,D__st,		D__st5,		D__NONE,	"FCMOVNBE" 	,0xd5db,2|C_ESC_GROUP_TYPE|(29<<16),MAKE_OP_RW_FLAG(0,OP_R,0)}, //0xd5
	{ 0 , C_FCMOVNBE,D__st,		D__st6,		D__NONE,	"FCMOVNBE" 	,0xd6db,2|C_ESC_GROUP_TYPE|(30<<16),MAKE_OP_RW_FLAG(0,OP_R,0)}, //0xd6
	{ 0 , C_FCMOVNBE,D__st,		D__st7,		D__NONE,	"FCMOVNBE" 	,0xd7db,2|C_ESC_GROUP_TYPE|(31<<16),MAKE_OP_RW_FLAG(0,OP_R,0)}, //0xd7
	{ 0 , C_FCMOVNU,	D__st,		D__st0,		D__NONE,	"FCMOVNU" 	,0xd8db,2|C_ESC_GROUP_TYPE|(32<<16),MAKE_OP_RW_FLAG(0,OP_R,0)}, //0xd8
	{ 0 , C_FCMOVNU,	D__st,		D__st1,		D__NONE,	"FCMOVNU" 	,0xd9db,2|C_ESC_GROUP_TYPE|(33<<16),MAKE_OP_RW_FLAG(0,OP_R,0)}, //0xd9
	{ 0 , C_FCMOVNU,	D__st,		D__st2,		D__NONE,	"FCMOVNU" 	,0xdadb,2|C_ESC_GROUP_TYPE|(34<<16),MAKE_OP_RW_FLAG(0,OP_R,0)}, //0xda
	{ 0 , C_FCMOVNU,	D__st,		D__st3,		D__NONE,	"FCMOVNU" 	,0xdbdb,2|C_ESC_GROUP_TYPE|(35<<16),MAKE_OP_RW_FLAG(0,OP_R,0)}, //0xdb
	{ 0 , C_FCMOVNU,	D__st,		D__st4,		D__NONE,	"FCMOVNU" 	,0xdcdb,2|C_ESC_GROUP_TYPE|(36<<16),MAKE_OP_RW_FLAG(0,OP_R,0)}, //0xdc
	{ 0 , C_FCMOVNU,	D__st,		D__st5,		D__NONE,	"FCMOVNU" 	,0xdddb,2|C_ESC_GROUP_TYPE|(37<<16),MAKE_OP_RW_FLAG(0,OP_R,0)}, //0xdd
	{ 0 , C_FCMOVNU,	D__st,		D__st6,		D__NONE,	"FCMOVNU" 	,0xdedb,2|C_ESC_GROUP_TYPE|(38<<16),MAKE_OP_RW_FLAG(0,OP_R,0)}, //0xde
	{ 0 , C_FCMOVNU,	D__st,		D__st7,		D__NONE,	"FCMOVNU" 	,0xdfdb,2|C_ESC_GROUP_TYPE|(39<<16),MAKE_OP_RW_FLAG(0,OP_R,0)}, //0xdf

	{ 0 , C_NULL													}, //0xe0
	{ 0 , C_NULL													}, //0xe1
	{ 0 , C_FCLEX,	D__NONE,	D__NONE,	D__NONE,	"FCLEX" 	,0xe2db,2|C_ESC_GROUP_TYPE|(42<<16)}, //0xe2
	{ 0 , C_FINIT,	D__NONE,	D__NONE,	D__NONE,	"FINIT" 	,0xe3db,2|C_ESC_GROUP_TYPE|(43<<16)}, //0xe3
	{ 0 , C_NULL													}, //0xe4
	{ 0 , C_NULL													}, //0xe5
	{ 0 , C_NULL													}, //0xe6
	{ 0 , C_NULL													}, //0xe7

	{ 0 , C_FUCOMI,	D__st,		D__st0,		D__NONE,	"FUCOMI" 	,0xe8db,2|C_ESC_GROUP_TYPE|(48<<16),MAKE_OP_RW_FLAG(OP_R,OP_R,0)}, //0xe8
	{ 0 , C_FUCOMI,	D__st,		D__st1,		D__NONE,	"FUCOMI" 	,0xe9db,2|C_ESC_GROUP_TYPE|(49<<16),MAKE_OP_RW_FLAG(OP_R,OP_R,0)}, //0xe9
	{ 0 , C_FUCOMI,	D__st,		D__st2,		D__NONE,	"FUCOMI" 	,0xeadb,2|C_ESC_GROUP_TYPE|(50<<16),MAKE_OP_RW_FLAG(OP_R,OP_R,0)}, //0xea
	{ 0 , C_FUCOMI,	D__st,		D__st3,		D__NONE,	"FUCOMI" 	,0xebdb,2|C_ESC_GROUP_TYPE|(51<<16),MAKE_OP_RW_FLAG(OP_R,OP_R,0)}, //0xeb
	{ 0 , C_FUCOMI,	D__st,		D__st4,		D__NONE,	"FUCOMI" 	,0xecdb,2|C_ESC_GROUP_TYPE|(52<<16),MAKE_OP_RW_FLAG(OP_R,OP_R,0)}, //0xec
	{ 0 , C_FUCOMI,	D__st,		D__st5,		D__NONE,	"FUCOMI" 	,0xeddb,2|C_ESC_GROUP_TYPE|(53<<16),MAKE_OP_RW_FLAG(OP_R,OP_R,0)}, //0xed
	{ 0 , C_FUCOMI,	D__st,		D__st6,		D__NONE,	"FUCOMI" 	,0xeedb,2|C_ESC_GROUP_TYPE|(54<<16),MAKE_OP_RW_FLAG(OP_R,OP_R,0)}, //0xee
	{ 0 , C_FUCOMI,	D__st,		D__st7,		D__NONE,	"FUCOMI" 	,0xefdb,2|C_ESC_GROUP_TYPE|(55<<16),MAKE_OP_RW_FLAG(OP_R,OP_R,0)}, //0xef

	{ 0 , C_FCOMI,	D__st,		D__st0,		D__NONE,	"FCOMI" 	,0xf0db,2|C_ESC_GROUP_TYPE|(56<<16),MAKE_OP_RW_FLAG(OP_R,OP_R,0)}, //0xf0
	{ 0 , C_FCOMI,	D__st,		D__st1,		D__NONE,	"FCOMI" 	,0xf1db,2|C_ESC_GROUP_TYPE|(57<<16),MAKE_OP_RW_FLAG(OP_R,OP_R,0)}, //0xf1
	{ 0 , C_FCOMI,	D__st,		D__st2,		D__NONE,	"FCOMI" 	,0xf2db,2|C_ESC_GROUP_TYPE|(58<<16),MAKE_OP_RW_FLAG(OP_R,OP_R,0)}, //0xf2
	{ 0 , C_FCOMI,	D__st,		D__st3,		D__NONE,	"FCOMI" 	,0xf3db,2|C_ESC_GROUP_TYPE|(59<<16),MAKE_OP_RW_FLAG(OP_R,OP_R,0)}, //0xf3
	{ 0 , C_FCOMI,	D__st,		D__st4,		D__NONE,	"FCOMI" 	,0xf4db,2|C_ESC_GROUP_TYPE|(60<<16),MAKE_OP_RW_FLAG(OP_R,OP_R,0)}, //0xf4
	{ 0 , C_FCOMI,	D__st,		D__st5,		D__NONE,	"FCOMI" 	,0xf5db,2|C_ESC_GROUP_TYPE|(61<<16),MAKE_OP_RW_FLAG(OP_R,OP_R,0)}, //0xf5
	{ 0 , C_FCOMI,	D__st,		D__st6,		D__NONE,	"FCOMI" 	,0xf6db,2|C_ESC_GROUP_TYPE|(62<<16),MAKE_OP_RW_FLAG(OP_R,OP_R,0)}, //0xf6
	{ 0 , C_FCOMI,	D__st,		D__st7,		D__NONE,	"FCOMI" 	,0xf7db,2|C_ESC_GROUP_TYPE|(63<<16),MAKE_OP_RW_FLAG(OP_R,OP_R,0)}, //0xf7

	{ 0 , C_NULL													}, //0xf8
	{ 0 , C_NULL													}, //0xf9
	{ 0 , C_NULL													}, //0xfa
	{ 0 , C_NULL													}, //0xfb
	{ 0 , C_NULL													}, //0xfc
	{ 0 , C_NULL													}, //0xfd
	{ 0 , C_NULL													}, //0xfe
	{ 0 , C_NULL													} //0xff

};

DIS_OPCODE_T Group0xdc[] = //fpu group
{
	{R_M, C_FADD,	D__double_real,	D__NONE,D__NONE,	"FADD" 		,0xdc,1|C_ESC_GROUP_TYPE|(0<<16),MAKE_OP_RW_FLAG(OP_R,0,0)}, //0x0
	{R_M, C_FMUL,	D__double_real,	D__NONE,D__NONE,	"FMUL" 		,0xdc,1|C_ESC_GROUP_TYPE|(1<<16),MAKE_OP_RW_FLAG(OP_R,0,0)}, //0x1
	{R_M, C_FCOM,	D__double_real,	D__NONE,D__NONE,	"FCOM" 		,0xdc,1|C_ESC_GROUP_TYPE|(2<<16),MAKE_OP_RW_FLAG(OP_R,0,0)}, //0x2
	{R_M, C_FCOMP,	D__double_real,	D__NONE,D__NONE,	"FCOMP" 	,0xdc,1|C_ESC_GROUP_TYPE|(3<<16),MAKE_OP_RW_FLAG(OP_R,0,0)}, //0x3
	{R_M, C_FSUB,	D__double_real,	D__NONE,D__NONE,	"FSUB" 		,0xdc,1|C_ESC_GROUP_TYPE|(4<<16),MAKE_OP_RW_FLAG(OP_R,0,0)}, //0x4
	{R_M, C_FSUBR,	D__double_real,	D__NONE,D__NONE,	"FSUBR" 	,0xdc,1|C_ESC_GROUP_TYPE|(5<<16),MAKE_OP_RW_FLAG(OP_R,0,0)}, //0x5
	{R_M, C_FDIV,	D__double_real,	D__NONE,D__NONE,	"FDIV" 		,0xdc,1|C_ESC_GROUP_TYPE|(6<<16),MAKE_OP_RW_FLAG(OP_R,0,0)}, //0x6
	{R_M, C_FDIVR,	D__double_real,	D__NONE,D__NONE,	"FDIVR" 	,0xdc,1|C_ESC_GROUP_TYPE|(7<<16),MAKE_OP_RW_FLAG(OP_R,0,0)}, //0x7

	//双字节浮点指令
	{ 0 , C_FADD,	D__st0,		D__st,				D__NONE,	"FADD" 		,0xc0dc,2|C_ESC_GROUP_TYPE|(8<<16) ,MAKE_OP_RW_FLAG(OP_RW,OP_R,0)}, //0xc0
	{ 0 , C_FADD,	D__st1,		D__st,				D__NONE,	"FADD" 		,0xc1dc,2|C_ESC_GROUP_TYPE|(9<<16) ,MAKE_OP_RW_FLAG(OP_RW,OP_R,0)}, //0xc1
	{ 0 , C_FADD,	D__st2,		D__st,				D__NONE,	"FADD" 		,0xc2dc,2|C_ESC_GROUP_TYPE|(10<<16),MAKE_OP_RW_FLAG(OP_RW,OP_R,0)}, //0xc2
	{ 0 , C_FADD,	D__st3,		D__st,				D__NONE,	"FADD" 		,0xc3dc,2|C_ESC_GROUP_TYPE|(11<<16),MAKE_OP_RW_FLAG(OP_RW,OP_R,0)}, //0xc3
	{ 0 , C_FADD,	D__st4,		D__st,				D__NONE,	"FADD" 		,0xc4dc,2|C_ESC_GROUP_TYPE|(12<<16),MAKE_OP_RW_FLAG(OP_RW,OP_R,0)}, //0xc4
	{ 0 , C_FADD,	D__st5,		D__st,				D__NONE,	"FADD" 		,0xc5dc,2|C_ESC_GROUP_TYPE|(13<<16),MAKE_OP_RW_FLAG(OP_RW,OP_R,0)}, //0xc5
	{ 0 , C_FADD,	D__st6,		D__st,				D__NONE,	"FADD" 		,0xc6dc,2|C_ESC_GROUP_TYPE|(14<<16),MAKE_OP_RW_FLAG(OP_RW,OP_R,0)}, //0xc6
	{ 0 , C_FADD,	D__st7,		D__st,				D__NONE,	"FADD" 		,0xc7dc,2|C_ESC_GROUP_TYPE|(15<<16),MAKE_OP_RW_FLAG(OP_RW,OP_R,0)}, //0xc7

	{ 0 , C_FMUL,	D__st0,		D__st,		D__NONE,	"FMUL" 		,0xc8dc,2|C_ESC_GROUP_TYPE|(16<<16),MAKE_OP_RW_FLAG(OP_RW,OP_R,0)}, //0xc8
	{ 0 , C_FMUL,	D__st1,		D__st,		D__NONE,	"FMUL" 		,0xc9dc,2|C_ESC_GROUP_TYPE|(17<<16),MAKE_OP_RW_FLAG(OP_RW,OP_R,0)}, //0xc9
	{ 0 , C_FMUL,	D__st2,		D__st,		D__NONE,	"FMUL" 		,0xcadc,2|C_ESC_GROUP_TYPE|(18<<16),MAKE_OP_RW_FLAG(OP_RW,OP_R,0)}, //0xca
	{ 0 , C_FMUL,	D__st3,		D__st,		D__NONE,	"FMUL" 		,0xcbdc,2|C_ESC_GROUP_TYPE|(19<<16),MAKE_OP_RW_FLAG(OP_RW,OP_R,0)}, //0xcb
	{ 0 , C_FMUL,	D__st4,		D__st,		D__NONE,	"FMUL" 		,0xccdc,2|C_ESC_GROUP_TYPE|(20<<16),MAKE_OP_RW_FLAG(OP_RW,OP_R,0)}, //0xcc
	{ 0 , C_FMUL,	D__st5,		D__st,		D__NONE,	"FMUL" 		,0xcddc,2|C_ESC_GROUP_TYPE|(21<<16),MAKE_OP_RW_FLAG(OP_RW,OP_R,0)}, //0xcd
	{ 0 , C_FMUL,	D__st6,		D__st,		D__NONE,	"FMUL" 		,0xcedc,2|C_ESC_GROUP_TYPE|(22<<16),MAKE_OP_RW_FLAG(OP_RW,OP_R,0)}, //0xce
	{ 0 , C_FMUL,	D__st7,		D__st,		D__NONE,	"FMUL" 		,0xcfdc,2|C_ESC_GROUP_TYPE|(23<<16),MAKE_OP_RW_FLAG(OP_RW,OP_R,0)}, //0xcf

	{ 0 , C_NULL													}, //0xd0
	{ 0 , C_NULL													}, //0xd1
	{ 0 , C_NULL													}, //0xd2
	{ 0 , C_NULL													}, //0xd3
	{ 0 , C_NULL													}, //0xd4
	{ 0 , C_NULL													}, //0xd5
	{ 0 , C_NULL													}, //0xd6
	{ 0 , C_NULL													}, //0xd7

	{ 0 , C_NULL													}, //0xd8
	{ 0 , C_NULL													}, //0xd9
	{ 0 , C_NULL													}, //0xda
	{ 0 , C_NULL													}, //0xdb
	{ 0 , C_NULL													}, //0xdc
	{ 0 , C_NULL													}, //0xdd
	{ 0 , C_NULL													}, //0xde
	{ 0 , C_NULL													}, //0xdf

	{ 0 , C_FSUBR,	D__st0,		D__st,		D__NONE,	"FSUBR" 	,0xe0dc,2|C_ESC_GROUP_TYPE|(40<<16),MAKE_OP_RW_FLAG(OP_RW,OP_R,0)}, //0xe0
	{ 0 , C_FSUBR,	D__st1,		D__st,		D__NONE,	"FSUBR" 	,0xe1dc,2|C_ESC_GROUP_TYPE|(41<<16),MAKE_OP_RW_FLAG(OP_RW,OP_R,0)}, //0xe1
	{ 0 , C_FSUBR,	D__st2,		D__st,		D__NONE,	"FSUBR" 	,0xe2dc,2|C_ESC_GROUP_TYPE|(42<<16),MAKE_OP_RW_FLAG(OP_RW,OP_R,0)}, //0xe2
	{ 0 , C_FSUBR,	D__st3,		D__st,		D__NONE,	"FSUBR" 	,0xe3dc,2|C_ESC_GROUP_TYPE|(43<<16),MAKE_OP_RW_FLAG(OP_RW,OP_R,0)}, //0xe3
	{ 0 , C_FSUBR,	D__st4,		D__st,		D__NONE,	"FSUBR" 	,0xe4dc,2|C_ESC_GROUP_TYPE|(44<<16),MAKE_OP_RW_FLAG(OP_RW,OP_R,0)}, //0xe4
	{ 0 , C_FSUBR,	D__st5,		D__st,		D__NONE,	"FSUBR" 	,0xe5dc,2|C_ESC_GROUP_TYPE|(45<<16),MAKE_OP_RW_FLAG(OP_RW,OP_R,0)}, //0xe5
	{ 0 , C_FSUBR,	D__st6,		D__st,		D__NONE,	"FSUBR" 	,0xe6dc,2|C_ESC_GROUP_TYPE|(46<<16),MAKE_OP_RW_FLAG(OP_RW,OP_R,0)}, //0xe6
	{ 0 , C_FSUBR,	D__st7,		D__st,		D__NONE,	"FSUBR" 	,0xe7dc,2|C_ESC_GROUP_TYPE|(47<<16),MAKE_OP_RW_FLAG(OP_RW,OP_R,0)}, //0xe7
					
	{ 0 , C_FSUB,	D__st0,		D__st,		D__NONE,	"FSUB" 		,0xe8dc,2|C_ESC_GROUP_TYPE|(48<<16),MAKE_OP_RW_FLAG(OP_RW,OP_R,0)}, //0xe8
	{ 0 , C_FSUB,	D__st1,		D__st,		D__NONE,	"FSUB" 		,0xe9dc,2|C_ESC_GROUP_TYPE|(49<<16),MAKE_OP_RW_FLAG(OP_RW,OP_R,0)}, //0xe9
	{ 0 , C_FSUB,	D__st2,		D__st,		D__NONE,	"FSUB" 		,0xeadc,2|C_ESC_GROUP_TYPE|(50<<16),MAKE_OP_RW_FLAG(OP_RW,OP_R,0)}, //0xea
	{ 0 , C_FSUB,	D__st3,		D__st,		D__NONE,	"FSUB" 		,0xebdc,2|C_ESC_GROUP_TYPE|(51<<16),MAKE_OP_RW_FLAG(OP_RW,OP_R,0)}, //0xeb
	{ 0 , C_FSUB,	D__st4,		D__st,		D__NONE,	"FSUB" 		,0xecdc,2|C_ESC_GROUP_TYPE|(52<<16),MAKE_OP_RW_FLAG(OP_RW,OP_R,0)}, //0xec
	{ 0 , C_FSUB,	D__st5,		D__st,		D__NONE,	"FSUB" 		,0xeddc,2|C_ESC_GROUP_TYPE|(53<<16),MAKE_OP_RW_FLAG(OP_RW,OP_R,0)}, //0xed
	{ 0 , C_FSUB,	D__st6,		D__st,		D__NONE,	"FSUB" 		,0xeedc,2|C_ESC_GROUP_TYPE|(54<<16),MAKE_OP_RW_FLAG(OP_RW,OP_R,0)}, //0xee
	{ 0 , C_FSUB,	D__st7,		D__st,		D__NONE,	"FSUB" 		,0xefdc,2|C_ESC_GROUP_TYPE|(55<<16),MAKE_OP_RW_FLAG(OP_RW,OP_R,0)}, //0xef

	{ 0 , C_FDIVR,	D__st0,		D__st,		D__NONE,	"FDIVR" 	,0xf0dc,2|C_ESC_GROUP_TYPE|(56<<16),MAKE_OP_RW_FLAG(OP_RW,OP_R,0)}, //0xf0
	{ 0 , C_FDIVR,	D__st1,		D__st,		D__NONE,	"FDIVR" 	,0xf1dc,2|C_ESC_GROUP_TYPE|(57<<16),MAKE_OP_RW_FLAG(OP_RW,OP_R,0)}, //0xf1
	{ 0 , C_FDIVR,	D__st2,		D__st,		D__NONE,	"FDIVR" 	,0xf2dc,2|C_ESC_GROUP_TYPE|(58<<16),MAKE_OP_RW_FLAG(OP_RW,OP_R,0)}, //0xf2
	{ 0 , C_FDIVR,	D__st3,		D__st,		D__NONE,	"FDIVR" 	,0xf3dc,2|C_ESC_GROUP_TYPE|(59<<16),MAKE_OP_RW_FLAG(OP_RW,OP_R,0)}, //0xf3
	{ 0 , C_FDIVR,	D__st4,		D__st,		D__NONE,	"FDIVR" 	,0xf4dc,2|C_ESC_GROUP_TYPE|(60<<16),MAKE_OP_RW_FLAG(OP_RW,OP_R,0)}, //0xf4
	{ 0 , C_FDIVR,	D__st5,		D__st,		D__NONE,	"FDIVR" 	,0xf5dc,2|C_ESC_GROUP_TYPE|(61<<16),MAKE_OP_RW_FLAG(OP_RW,OP_R,0)}, //0xf5
	{ 0 , C_FDIVR,	D__st6,		D__st,		D__NONE,	"FDIVR" 	,0xf6dc,2|C_ESC_GROUP_TYPE|(62<<16),MAKE_OP_RW_FLAG(OP_RW,OP_R,0)}, //0xf6
	{ 0 , C_FDIVR,	D__st7,		D__st,		D__NONE,	"FDIVR" 	,0xf7dc,2|C_ESC_GROUP_TYPE|(63<<16),MAKE_OP_RW_FLAG(OP_RW,OP_R,0)}, //0xf7
					
	{ 0 , C_FDIV,	D__st0,		D__st,		D__NONE,	"FDIV" 		,0xf8dc,2|C_ESC_GROUP_TYPE|(64<<16),MAKE_OP_RW_FLAG(OP_RW,OP_R,0)}, //0xf8
	{ 0 , C_FDIV,	D__st1,		D__st,		D__NONE,	"FDIV" 		,0xf9dc,2|C_ESC_GROUP_TYPE|(65<<16),MAKE_OP_RW_FLAG(OP_RW,OP_R,0)}, //0xf9
	{ 0 , C_FDIV,	D__st2,		D__st,		D__NONE,	"FDIV" 		,0xfadc,2|C_ESC_GROUP_TYPE|(66<<16),MAKE_OP_RW_FLAG(OP_RW,OP_R,0)}, //0xfa
	{ 0 , C_FDIV,	D__st3,		D__st,		D__NONE,	"FDIV" 		,0xfbdc,2|C_ESC_GROUP_TYPE|(67<<16),MAKE_OP_RW_FLAG(OP_RW,OP_R,0)}, //0xfb
	{ 0 , C_FDIV,	D__st4,		D__st,		D__NONE,	"FDIV" 		,0xfcdc,2|C_ESC_GROUP_TYPE|(68<<16),MAKE_OP_RW_FLAG(OP_RW,OP_R,0)}, //0xfc
	{ 0 , C_FDIV,	D__st5,		D__st,		D__NONE,	"FDIV" 		,0xfddc,2|C_ESC_GROUP_TYPE|(69<<16),MAKE_OP_RW_FLAG(OP_RW,OP_R,0)}, //0xfd
	{ 0 , C_FDIV,	D__st6,		D__st,		D__NONE,	"FDIV" 		,0xfedc,2|C_ESC_GROUP_TYPE|(70<<16),MAKE_OP_RW_FLAG(OP_RW,OP_R,0)}, //0xfe
	{ 0 , C_FDIV,	D__st7,		D__st,		D__NONE,	"FDIV" 		,0xffdc,2|C_ESC_GROUP_TYPE|(71<<16),MAKE_OP_RW_FLAG(OP_RW,OP_R,0)} //0xff
};


DIS_OPCODE_T Group0xdd[] = //fpu group
{
	{R_M, C_FLD,	D__double_real,	D__NONE,D__NONE,	"FLD" 		,0xdd,1|C_ESC_GROUP_TYPE|(0<<16),MAKE_OP_RW_FLAG(OP_R,0,0)}, //0x0
	{R_M, C_FISTTP,	D__double_real,	D__NONE,D__NONE,	"FISTTP" 	,0xdd,1|C_ESC_GROUP_TYPE|(1<<16),MAKE_OP_RW_FLAG(OP_W,0,0)}, //0x1
	{R_M, C_FST,	D__double_real,	D__NONE,D__NONE,	"FST" 		,0xdd,1|C_ESC_GROUP_TYPE|(2<<16),MAKE_OP_RW_FLAG(OP_W,0,0)}, //0x2
	{R_M, C_FSTP,	D__double_real,	D__NONE,D__NONE,	"FSTP" 		,0xdd,1|C_ESC_GROUP_TYPE|(3<<16),MAKE_OP_RW_FLAG(OP_W,0,0)}, //0x3
	{R_M, C_FRSTOR,	D__98_108b,		D__NONE,D__NONE,	"FRSTOR" 	,0xdd,1|C_ESC_GROUP_TYPE|(4<<16),MAKE_OP_RW_FLAG(OP_R,0,0)}, //0x4
	{R_M, C_NULL																}, //0x5
	{R_M, C_FSAVE,	D__98_108b,		D__NONE,D__NONE,	"FSAVE" 	,0xdd,1|C_ESC_GROUP_TYPE|(6<<16),MAKE_OP_RW_FLAG(OP_W,0,0)}, //0x6
	{R_M, C_FSTSW,	D__2b,			D__NONE,D__NONE,	"FSTSW" 	,0xdd,1|C_ESC_GROUP_TYPE|(7<<16),MAKE_OP_RW_FLAG(OP_W,0,0)}, //0x7

	//双字节浮点指令
	{ 0 , C_FFREE,	D__st0,		D__NONE,	D__NONE,	"FFREE" 	,0xc0dd,2|C_ESC_GROUP_TYPE|(8<<16),MAKE_OP_RW_FLAG(0,0,0)}, //0xc0
	{ 0 , C_FFREE,	D__st1,		D__NONE,	D__NONE,	"FFREE" 	,0xc1dd,2|C_ESC_GROUP_TYPE|(9<<16),MAKE_OP_RW_FLAG(0,0,0)}, //0xc1
	{ 0 , C_FFREE,	D__st2,		D__NONE,	D__NONE,	"FFREE" 	,0xc2dd,2|C_ESC_GROUP_TYPE|(10<<16),MAKE_OP_RW_FLAG(0,0,0)}, //0xc2
	{ 0 , C_FFREE,	D__st3,		D__NONE,	D__NONE,	"FFREE" 	,0xc3dd,2|C_ESC_GROUP_TYPE|(11<<16),MAKE_OP_RW_FLAG(0,0,0)}, //0xc3
	{ 0 , C_FFREE,	D__st4,		D__NONE,	D__NONE,	"FFREE" 	,0xc4dd,2|C_ESC_GROUP_TYPE|(12<<16),MAKE_OP_RW_FLAG(0,0,0)}, //0xc4
	{ 0 , C_FFREE,	D__st5,		D__NONE,	D__NONE,	"FFREE" 	,0xc5dd,2|C_ESC_GROUP_TYPE|(13<<16),MAKE_OP_RW_FLAG(0,0,0)}, //0xc5
	{ 0 , C_FFREE,	D__st6,		D__NONE,	D__NONE,	"FFREE" 	,0xc6dd,2|C_ESC_GROUP_TYPE|(14<<16),MAKE_OP_RW_FLAG(0,0,0)}, //0xc6
	{ 0 , C_FFREE,	D__st7,		D__NONE,	D__NONE,	"FFREE" 	,0xc7dd,2|C_ESC_GROUP_TYPE|(15<<16),MAKE_OP_RW_FLAG(0,0,0)}, //0xc7

	{ 0 , C_NULL													}, //0xc8
	{ 0 , C_NULL													}, //0xc9
	{ 0 , C_NULL													}, //0xca
	{ 0 , C_NULL													}, //0xcb
	{ 0 , C_NULL													}, //0xcc
	{ 0 , C_NULL													}, //0xcd
	{ 0 , C_NULL													}, //0xce
	{ 0 , C_NULL													}, //0xcf

	{ 0 , C_FST,	D__st0,		D__NONE,	D__NONE,	"FST" 		,0xd0dd,2|C_ESC_GROUP_TYPE|(24<<16),MAKE_OP_RW_FLAG(OP_R,0,0)}, //0xd0
	{ 0 , C_FST,	D__st1,		D__NONE,	D__NONE,	"FST" 		,0xd1dd,2|C_ESC_GROUP_TYPE|(25<<16),MAKE_OP_RW_FLAG(OP_R,0,0)}, //0xd1
	{ 0 , C_FST,	D__st2,		D__NONE,	D__NONE,	"FST" 		,0xd2dd,2|C_ESC_GROUP_TYPE|(26<<16),MAKE_OP_RW_FLAG(OP_R,0,0)}, //0xd2
	{ 0 , C_FST,	D__st3,		D__NONE,	D__NONE,	"FST" 		,0xd3dd,2|C_ESC_GROUP_TYPE|(27<<16),MAKE_OP_RW_FLAG(OP_R,0,0)}, //0xd3
	{ 0 , C_FST,	D__st4,		D__NONE,	D__NONE,	"FST" 		,0xd4dd,2|C_ESC_GROUP_TYPE|(28<<16),MAKE_OP_RW_FLAG(OP_R,0,0)}, //0xd4
	{ 0 , C_FST,	D__st5,		D__NONE,	D__NONE,	"FST" 		,0xd5dd,2|C_ESC_GROUP_TYPE|(29<<16),MAKE_OP_RW_FLAG(OP_R,0,0)}, //0xd5
	{ 0 , C_FST,	D__st6,		D__NONE,	D__NONE,	"FST" 		,0xd6dd,2|C_ESC_GROUP_TYPE|(30<<16),MAKE_OP_RW_FLAG(OP_R,0,0)}, //0xd6
	{ 0 , C_FST,	D__st7,		D__NONE,	D__NONE,	"FST" 		,0xd7dd,2|C_ESC_GROUP_TYPE|(31<<16),MAKE_OP_RW_FLAG(OP_R,0,0)}, //0xd7

	{ 0 , C_FSTP,	D__st0,		D__NONE,	D__NONE,	"FSTP" 		,0xd8dd,2|C_ESC_GROUP_TYPE|(32<<16),MAKE_OP_RW_FLAG(OP_R,0,0)}, //0xd8
	{ 0 , C_FSTP,	D__st1,		D__NONE,	D__NONE,	"FSTP" 		,0xd9dd,2|C_ESC_GROUP_TYPE|(33<<16),MAKE_OP_RW_FLAG(OP_R,0,0)}, //0xd9
	{ 0 , C_FSTP,	D__st2,		D__NONE,	D__NONE,	"FSTP" 		,0xdadd,2|C_ESC_GROUP_TYPE|(34<<16),MAKE_OP_RW_FLAG(OP_R,0,0)}, //0xda
	{ 0 , C_FSTP,	D__st3,		D__NONE,	D__NONE,	"FSTP" 		,0xdbdd,2|C_ESC_GROUP_TYPE|(35<<16),MAKE_OP_RW_FLAG(OP_R,0,0)}, //0xdb
	{ 0 , C_FSTP,	D__st4,		D__NONE,	D__NONE,	"FSTP" 		,0xdcdd,2|C_ESC_GROUP_TYPE|(36<<16),MAKE_OP_RW_FLAG(OP_R,0,0)}, //0xdc
	{ 0 , C_FSTP,	D__st5,		D__NONE,	D__NONE,	"FSTP" 		,0xdddd,2|C_ESC_GROUP_TYPE|(37<<16),MAKE_OP_RW_FLAG(OP_R,0,0)}, //0xdd
	{ 0 , C_FSTP,	D__st6,		D__NONE,	D__NONE,	"FSTP" 		,0xdedd,2|C_ESC_GROUP_TYPE|(38<<16),MAKE_OP_RW_FLAG(OP_R,0,0)}, //0xde
	{ 0 , C_FSTP,	D__st7,		D__NONE,	D__NONE,	"FSTP" 		,0xdfdd,2|C_ESC_GROUP_TYPE|(39<<16),MAKE_OP_RW_FLAG(OP_R,0,0)}, //0xdf

	{ 0 , C_FUCOM,	D__st0,		D__st,		D__NONE,	"FUCOM" 	,0xe0dd,2|C_ESC_GROUP_TYPE|(40<<16),MAKE_OP_RW_FLAG(OP_R,OP_R,0)}, //0xe0
	{ 0 , C_FUCOM,	D__st1,		D__st,		D__NONE,	"FUCOM" 	,0xe1dd,2|C_ESC_GROUP_TYPE|(41<<16),MAKE_OP_RW_FLAG(OP_R,OP_R,0)}, //0xe1
	{ 0 , C_FUCOM,	D__st2,		D__st,		D__NONE,	"FUCOM" 	,0xe2dd,2|C_ESC_GROUP_TYPE|(42<<16),MAKE_OP_RW_FLAG(OP_R,OP_R,0)}, //0xe2
	{ 0 , C_FUCOM,	D__st3,		D__st,		D__NONE,	"FUCOM" 	,0xe3dd,2|C_ESC_GROUP_TYPE|(43<<16),MAKE_OP_RW_FLAG(OP_R,OP_R,0)}, //0xe3
	{ 0 , C_FUCOM,	D__st4,		D__st,		D__NONE,	"FUCOM" 	,0xe4dd,2|C_ESC_GROUP_TYPE|(44<<16),MAKE_OP_RW_FLAG(OP_R,OP_R,0)}, //0xe4
	{ 0 , C_FUCOM,	D__st5,		D__st,		D__NONE,	"FUCOM" 	,0xe5dd,2|C_ESC_GROUP_TYPE|(45<<16),MAKE_OP_RW_FLAG(OP_R,OP_R,0)}, //0xe5
	{ 0 , C_FUCOM,	D__st6,		D__st,		D__NONE,	"FUCOM" 	,0xe6dd,2|C_ESC_GROUP_TYPE|(46<<16),MAKE_OP_RW_FLAG(OP_R,OP_R,0)}, //0xe6
	{ 0 , C_FUCOM,	D__st7,		D__st,		D__NONE,	"FUCOM" 	,0xe7dd,2|C_ESC_GROUP_TYPE|(47<<16),MAKE_OP_RW_FLAG(OP_R,OP_R,0)}, //0xe7

	{ 0 , C_FUCOMP,	D__st0,		D__NONE,	D__NONE,	"FUCOMP" 	,0xe8dd,2|C_ESC_GROUP_TYPE|(48<<16),MAKE_OP_RW_FLAG(OP_R,0,0)}, //0xe8
	{ 0 , C_FUCOMP,	D__st1,		D__NONE,	D__NONE,	"FUCOMP" 	,0xe9dd,2|C_ESC_GROUP_TYPE|(49<<16),MAKE_OP_RW_FLAG(OP_R,0,0)}, //0xe9
	{ 0 , C_FUCOMP,	D__st2,		D__NONE,	D__NONE,	"FUCOMP" 	,0xeadd,2|C_ESC_GROUP_TYPE|(50<<16),MAKE_OP_RW_FLAG(OP_R,0,0)}, //0xea
	{ 0 , C_FUCOMP,	D__st3,		D__NONE,	D__NONE,	"FUCOMP" 	,0xebdd,2|C_ESC_GROUP_TYPE|(51<<16),MAKE_OP_RW_FLAG(OP_R,0,0)}, //0xeb
	{ 0 , C_FUCOMP,	D__st4,		D__NONE,	D__NONE,	"FUCOMP" 	,0xecdd,2|C_ESC_GROUP_TYPE|(52<<16),MAKE_OP_RW_FLAG(OP_R,0,0)}, //0xec
	{ 0 , C_FUCOMP,	D__st5,		D__NONE,	D__NONE,	"FUCOMP" 	,0xeddd,2|C_ESC_GROUP_TYPE|(53<<16),MAKE_OP_RW_FLAG(OP_R,0,0)}, //0xed
	{ 0 , C_FUCOMP,	D__st6,		D__NONE,	D__NONE,	"FUCOMP" 	,0xeedd,2|C_ESC_GROUP_TYPE|(54<<16),MAKE_OP_RW_FLAG(OP_R,0,0)}, //0xee
	{ 0 , C_FUCOMP,	D__st7,		D__NONE,	D__NONE,	"FUCOMP" 	,0xefdd,2|C_ESC_GROUP_TYPE|(55<<16),MAKE_OP_RW_FLAG(OP_R,0,0)}, //0xef

	{ 0 , C_NULL													}, //0xf0
	{ 0 , C_NULL													}, //0xf1
	{ 0 , C_NULL													}, //0xf2
	{ 0 , C_NULL													}, //0xf3
	{ 0 , C_NULL													}, //0xf4
	{ 0 , C_NULL													}, //0xf5
	{ 0 , C_NULL													}, //0xf6
	{ 0 , C_NULL													}, //0xf7

	{ 0 , C_NULL													}, //0xf8
	{ 0 , C_NULL													}, //0xf9
	{ 0 , C_NULL													}, //0xfa
	{ 0 , C_NULL													}, //0xfb
	{ 0 , C_NULL													}, //0xfc
	{ 0 , C_NULL													}, //0xfd
	{ 0 , C_NULL													}, //0xfe
	{ 0 , C_NULL													} //0xff

};

DIS_OPCODE_T Group0xde[] = //fpu group
{
	{R_M, C_FIADD,	D__word_int,D__NONE,D__NONE,	"FIADD" 	,0xde,1|C_ESC_GROUP_TYPE|(0<<16),MAKE_OP_RW_FLAG(OP_RW,OP_R,0)}, //0x0
	{R_M, C_FIMUL,	D__word_int,D__NONE,D__NONE,	"FIMUL" 	,0xde,1|C_ESC_GROUP_TYPE|(1<<16),MAKE_OP_RW_FLAG(OP_RW,OP_R,0)}, //0x1
	{R_M, C_FICOM,	D__word_int,D__NONE,D__NONE,	"FICOM" 	,0xde,1|C_ESC_GROUP_TYPE|(2<<16),MAKE_OP_RW_FLAG(OP_R,OP_R,0)}, //0x2
	{R_M, C_FICOMP,	D__word_int,D__NONE,D__NONE,	"FICOMP" 	,0xde,1|C_ESC_GROUP_TYPE|(3<<16),MAKE_OP_RW_FLAG(OP_R,OP_R,0)}, //0x3
	{R_M, C_FISUB,	D__word_int,D__NONE,D__NONE,	"FISUB" 	,0xde,1|C_ESC_GROUP_TYPE|(4<<16),MAKE_OP_RW_FLAG(OP_RW,OP_R,0)}, //0x4
	{R_M, C_FISUBR,	D__word_int,D__NONE,D__NONE,	"FISUBR" 	,0xde,1|C_ESC_GROUP_TYPE|(5<<16),MAKE_OP_RW_FLAG(OP_RW,OP_R,0)}, //0x5
	{R_M, C_FIDIV,	D__word_int,D__NONE,D__NONE,	"FIDIV" 	,0xde,1|C_ESC_GROUP_TYPE|(6<<16),MAKE_OP_RW_FLAG(OP_RW,OP_R,0)}, //0x6
	{R_M, C_FIDIVR,	D__word_int,D__NONE,D__NONE,	"FIDIVR" 	,0xde,1|C_ESC_GROUP_TYPE|(7<<16),MAKE_OP_RW_FLAG(OP_RW,OP_R,0)}, //0x7

	//双字节浮点指令
	{ 0 , C_FADDP,	D__st0,		D__st,		D__NONE,	"FADDP" 	,0xc0de,2|C_ESC_GROUP_TYPE|(8<<16),MAKE_OP_RW_FLAG(OP_RW,OP_R,0)}, //0xc0
	{ 0 , C_FADDP,	D__st1,		D__st,		D__NONE,	"FADDP" 	,0xc1de,2|C_ESC_GROUP_TYPE|(9<<16),MAKE_OP_RW_FLAG(OP_RW,OP_R,0)}, //0xc1
	{ 0 , C_FADDP,	D__st2,		D__st,		D__NONE,	"FADDP" 	,0xc2de,2|C_ESC_GROUP_TYPE|(10<<16),MAKE_OP_RW_FLAG(OP_RW,OP_R,0)}, //0xc2
	{ 0 , C_FADDP,	D__st3,		D__st,		D__NONE,	"FADDP" 	,0xc3de,2|C_ESC_GROUP_TYPE|(11<<16),MAKE_OP_RW_FLAG(OP_RW,OP_R,0)}, //0xc3
	{ 0 , C_FADDP,	D__st4,		D__st,		D__NONE,	"FADDP" 	,0xc4de,2|C_ESC_GROUP_TYPE|(12<<16),MAKE_OP_RW_FLAG(OP_RW,OP_R,0)}, //0xc4
	{ 0 , C_FADDP,	D__st5,		D__st,		D__NONE,	"FADDP" 	,0xc5de,2|C_ESC_GROUP_TYPE|(13<<16),MAKE_OP_RW_FLAG(OP_RW,OP_R,0)}, //0xc5
	{ 0 , C_FADDP,	D__st6,		D__st,		D__NONE,	"FADDP" 	,0xc6de,2|C_ESC_GROUP_TYPE|(14<<16),MAKE_OP_RW_FLAG(OP_RW,OP_R,0)}, //0xc6
	{ 0 , C_FADDP,	D__st7,		D__st,		D__NONE,	"FADDP" 	,0xc7de,2|C_ESC_GROUP_TYPE|(15<<16),MAKE_OP_RW_FLAG(OP_RW,OP_R,0)}, //0xc7

	{ 0 , C_FMULP,	D__st0,		D__st,		D__NONE,	"FMULP" 	,0xc8de,2|C_ESC_GROUP_TYPE|(16<<16),MAKE_OP_RW_FLAG(OP_RW,OP_R,0)}, //0xc8
	{ 0 , C_FMULP,	D__st1,		D__st,		D__NONE,	"FMULP" 	,0xc9de,2|C_ESC_GROUP_TYPE|(17<<16),MAKE_OP_RW_FLAG(OP_RW,OP_R,0)}, //0xc9
	{ 0 , C_FMULP,	D__st2,		D__st,		D__NONE,	"FMULP" 	,0xcade,2|C_ESC_GROUP_TYPE|(18<<16),MAKE_OP_RW_FLAG(OP_RW,OP_R,0)}, //0xca
	{ 0 , C_FMULP,	D__st3,		D__st,		D__NONE,	"FMULP" 	,0xcbde,2|C_ESC_GROUP_TYPE|(19<<16),MAKE_OP_RW_FLAG(OP_RW,OP_R,0)}, //0xcb
	{ 0 , C_FMULP,	D__st4,		D__st,		D__NONE,	"FMULP" 	,0xccde,2|C_ESC_GROUP_TYPE|(20<<16),MAKE_OP_RW_FLAG(OP_RW,OP_R,0)}, //0xcc
	{ 0 , C_FMULP,	D__st5,		D__st,		D__NONE,	"FMULP" 	,0xcdde,2|C_ESC_GROUP_TYPE|(21<<16),MAKE_OP_RW_FLAG(OP_RW,OP_R,0)}, //0xcd
	{ 0 , C_FMULP,	D__st6,		D__st,		D__NONE,	"FMULP" 	,0xcede,2|C_ESC_GROUP_TYPE|(22<<16),MAKE_OP_RW_FLAG(OP_RW,OP_R,0)}, //0xce
	{ 0 , C_FMULP,	D__st7,		D__st,		D__NONE,	"FMULP" 	,0xcfde,2|C_ESC_GROUP_TYPE|(23<<16),MAKE_OP_RW_FLAG(OP_RW,OP_R,0)}, //0xcf

	{ 0 , C_NULL													}, //0xd0
	{ 0 , C_NULL													}, //0xd1
	{ 0 , C_NULL													}, //0xd2
	{ 0 , C_NULL													}, //0xd3
	{ 0 , C_NULL													}, //0xd4
	{ 0 , C_NULL													}, //0xd5
	{ 0 , C_NULL													}, //0xd6
	{ 0 , C_NULL													}, //0xd7

	{ 0 , C_NULL													}, //0xd8
	{ 0 , C_FCOMPP,	D__NONE,	D__NONE,	D__NONE,	"FCOMPP" 	,0xd9de,2|C_ESC_GROUP_TYPE|(33<<16),MAKE_OP_RW_FLAG(OP_R,OP_R,0)}, //0xd9
	{ 0 , C_NULL													}, //0xda
	{ 0 , C_NULL													}, //0xdb
	{ 0 , C_NULL													}, //0xdc
	{ 0 , C_NULL													}, //0xdd
	{ 0 , C_NULL													}, //0xde
	{ 0 , C_NULL													}, //0xdf

	{ 0 , C_FSUBRP,	D__st0,		D__st,		D__NONE,	"FSUBRP" 	,0xe0de,2|C_ESC_GROUP_TYPE|(40<<16),MAKE_OP_RW_FLAG(OP_RW,OP_R,0)}, //0xe0
	{ 0 , C_FSUBRP,	D__st1,		D__st,		D__NONE,	"FSUBRP" 	,0xe1de,2|C_ESC_GROUP_TYPE|(41<<16),MAKE_OP_RW_FLAG(OP_RW,OP_R,0)}, //0xe1
	{ 0 , C_FSUBRP,	D__st2,		D__st,		D__NONE,	"FSUBRP" 	,0xe2de,2|C_ESC_GROUP_TYPE|(42<<16),MAKE_OP_RW_FLAG(OP_RW,OP_R,0)}, //0xe2
	{ 0 , C_FSUBRP,	D__st3,		D__st,		D__NONE,	"FSUBRP" 	,0xe3de,2|C_ESC_GROUP_TYPE|(43<<16),MAKE_OP_RW_FLAG(OP_RW,OP_R,0)}, //0xe3
	{ 0 , C_FSUBRP,	D__st4,		D__st,		D__NONE,	"FSUBRP" 	,0xe4de,2|C_ESC_GROUP_TYPE|(44<<16),MAKE_OP_RW_FLAG(OP_RW,OP_R,0)}, //0xe4
	{ 0 , C_FSUBRP,	D__st5,		D__st,		D__NONE,	"FSUBRP" 	,0xe5de,2|C_ESC_GROUP_TYPE|(45<<16),MAKE_OP_RW_FLAG(OP_RW,OP_R,0)}, //0xe5
	{ 0 , C_FSUBRP,	D__st6,		D__st,		D__NONE,	"FSUBRP" 	,0xe6de,2|C_ESC_GROUP_TYPE|(46<<16),MAKE_OP_RW_FLAG(OP_RW,OP_R,0)}, //0xe6
	{ 0 , C_FSUBRP,	D__st7,		D__st,		D__NONE,	"FSUBRP" 	,0xe7de,2|C_ESC_GROUP_TYPE|(47<<16),MAKE_OP_RW_FLAG(OP_RW,OP_R,0)}, //0xe7

	{ 0 , C_FSUBP,	D__st0,		D__st,		D__NONE,	"FSUBP" 	,0xe8de,2|C_ESC_GROUP_TYPE|(48<<16),MAKE_OP_RW_FLAG(OP_RW,OP_R,0)}, //0xe8
	{ 0 , C_FSUBP,	D__st1,		D__st,		D__NONE,	"FSUBP" 	,0xe9de,2|C_ESC_GROUP_TYPE|(49<<16),MAKE_OP_RW_FLAG(OP_RW,OP_R,0)}, //0xe9
	{ 0 , C_FSUBP,	D__st2,		D__st,		D__NONE,	"FSUBP" 	,0xeade,2|C_ESC_GROUP_TYPE|(50<<16),MAKE_OP_RW_FLAG(OP_RW,OP_R,0)}, //0xea
	{ 0 , C_FSUBP,	D__st3,		D__st,		D__NONE,	"FSUBP" 	,0xebde,2|C_ESC_GROUP_TYPE|(51<<16),MAKE_OP_RW_FLAG(OP_RW,OP_R,0)}, //0xeb
	{ 0 , C_FSUBP,	D__st4,		D__st,		D__NONE,	"FSUBP" 	,0xecde,2|C_ESC_GROUP_TYPE|(52<<16),MAKE_OP_RW_FLAG(OP_RW,OP_R,0)}, //0xec
	{ 0 , C_FSUBP,	D__st5,		D__st,		D__NONE,	"FSUBP" 	,0xedde,2|C_ESC_GROUP_TYPE|(53<<16),MAKE_OP_RW_FLAG(OP_RW,OP_R,0)}, //0xed
	{ 0 , C_FSUBP,	D__st6,		D__st,		D__NONE,	"FSUBP" 	,0xeede,2|C_ESC_GROUP_TYPE|(54<<16),MAKE_OP_RW_FLAG(OP_RW,OP_R,0)}, //0xee
	{ 0 , C_FSUBP,	D__st7,		D__st,		D__NONE,	"FSUBP" 	,0xefde,2|C_ESC_GROUP_TYPE|(55<<16),MAKE_OP_RW_FLAG(OP_RW,OP_R,0)}, //0xef

	{ 0 , C_FDIVRP,	D__st0,		D__st,		D__NONE,	"FDIVRP" 	,0xf0de,2|C_ESC_GROUP_TYPE|(56<<16),MAKE_OP_RW_FLAG(OP_RW,OP_R,0)}, //0xf0
	{ 0 , C_FDIVRP,	D__st1,		D__st,		D__NONE,	"FDIVRP" 	,0xf1de,2|C_ESC_GROUP_TYPE|(57<<16),MAKE_OP_RW_FLAG(OP_RW,OP_R,0)}, //0xf1
	{ 0 , C_FDIVRP,	D__st2,		D__st,		D__NONE,	"FDIVRP" 	,0xf2de,2|C_ESC_GROUP_TYPE|(58<<16),MAKE_OP_RW_FLAG(OP_RW,OP_R,0)}, //0xf2
	{ 0 , C_FDIVRP,	D__st3,		D__st,		D__NONE,	"FDIVRP" 	,0xf3de,2|C_ESC_GROUP_TYPE|(59<<16),MAKE_OP_RW_FLAG(OP_RW,OP_R,0)}, //0xf3
	{ 0 , C_FDIVRP,	D__st4,		D__st,		D__NONE,	"FDIVRP" 	,0xf4de,2|C_ESC_GROUP_TYPE|(60<<16),MAKE_OP_RW_FLAG(OP_RW,OP_R,0)}, //0xf4
	{ 0 , C_FDIVRP,	D__st5,		D__st,		D__NONE,	"FDIVRP" 	,0xf5de,2|C_ESC_GROUP_TYPE|(61<<16),MAKE_OP_RW_FLAG(OP_RW,OP_R,0)}, //0xf5
	{ 0 , C_FDIVRP,	D__st6,		D__st,		D__NONE,	"FDIVRP" 	,0xf6de,2|C_ESC_GROUP_TYPE|(62<<16),MAKE_OP_RW_FLAG(OP_RW,OP_R,0)}, //0xf6
	{ 0 , C_FDIVRP,	D__st7,		D__st,		D__NONE,	"FDIVRP" 	,0xf7de,2|C_ESC_GROUP_TYPE|(63<<16),MAKE_OP_RW_FLAG(OP_RW,OP_R,0)}, //0xf7

	{ 0 , C_FDIVP,	D__st0,		D__st,		D__NONE,	"FDIVP" 	,0xf8de,2|C_ESC_GROUP_TYPE|(64<<16),MAKE_OP_RW_FLAG(OP_RW,OP_R,0)}, //0xf8
	{ 0 , C_FDIVP,	D__st1,		D__st,		D__NONE,	"FDIVP" 	,0xf9de,2|C_ESC_GROUP_TYPE|(65<<16),MAKE_OP_RW_FLAG(OP_RW,OP_R,0)}, //0xf9
	{ 0 , C_FDIVP,	D__st2,		D__st,		D__NONE,	"FDIVP" 	,0xfade,2|C_ESC_GROUP_TYPE|(66<<16),MAKE_OP_RW_FLAG(OP_RW,OP_R,0)}, //0xfa
	{ 0 , C_FDIVP,	D__st3,		D__st,		D__NONE,	"FDIVP" 	,0xfbde,2|C_ESC_GROUP_TYPE|(67<<16),MAKE_OP_RW_FLAG(OP_RW,OP_R,0)}, //0xfb
	{ 0 , C_FDIVP,	D__st4,		D__st,		D__NONE,	"FDIVP" 	,0xfcde,2|C_ESC_GROUP_TYPE|(68<<16),MAKE_OP_RW_FLAG(OP_RW,OP_R,0)}, //0xfc
	{ 0 , C_FDIVP,	D__st5,		D__st,		D__NONE,	"FDIVP" 	,0xfdde,2|C_ESC_GROUP_TYPE|(69<<16),MAKE_OP_RW_FLAG(OP_RW,OP_R,0)}, //0xfd
	{ 0 , C_FDIVP,	D__st6,		D__st,		D__NONE,	"FDIVP" 	,0xfede,2|C_ESC_GROUP_TYPE|(70<<16),MAKE_OP_RW_FLAG(OP_RW,OP_R,0)}, //0xfe
	{ 0 , C_FDIVP,	D__st7,		D__st,		D__NONE,	"FDIVP" 	,0xffde,2|C_ESC_GROUP_TYPE|(71<<16),MAKE_OP_RW_FLAG(OP_RW,OP_R,0)} //0xff
};


DIS_OPCODE_T Group0xdf[] = //fpu group
{
	//与内存数据有有关的浮点指令 长度跟指令(add D__Gb,D__Eb)一样
	{R_M, C_FILD,	D__word_int,	D__NONE,D__NONE,	"FILD" 		,0xdf,1|C_ESC_GROUP_TYPE|(0<<16),MAKE_OP_RW_FLAG(OP_R,0,0)}, //0x0
	{R_M, C_FISTTP,	D__word_int,	D__NONE,D__NONE,	"FISTTP" 	,0xdf,1|C_ESC_GROUP_TYPE|(1<<16),MAKE_OP_RW_FLAG(OP_R,0,0)}, //0x1
	{R_M, C_FIST,	D__word_int,	D__NONE,D__NONE,	"FIST" 		,0xdf,1|C_ESC_GROUP_TYPE|(2<<16),MAKE_OP_RW_FLAG(OP_W,0,0)}, //0x2
	{R_M, C_FISTP,	D__word_int,	D__NONE,D__NONE,	"FISTP" 	,0xdf,1|C_ESC_GROUP_TYPE|(3<<16),MAKE_OP_RW_FLAG(OP_W,0,0)}, //0x3
	{R_M, C_FBLD,	D__packed_BCD,	D__NONE,D__NONE,	"FBLD" 		,0xdf,1|C_ESC_GROUP_TYPE|(4<<16),MAKE_OP_RW_FLAG(OP_R,0,0)}, //0x4
	{R_M, C_FILD,	D__qword_int,	D__NONE,D__NONE,	"FILD" 		,0xdf,1|C_ESC_GROUP_TYPE|(5<<16),MAKE_OP_RW_FLAG(OP_R,0,0)}, //0x5
	{R_M, C_FBSTP,	D__packed_BCD,	D__NONE,D__NONE,	"FBSTP" 	,0xdf,1|C_ESC_GROUP_TYPE|(6<<16),MAKE_OP_RW_FLAG(OP_W,0,0)}, //0x6
	{R_M, C_FISTP,	D__qword_int,	D__NONE,D__NONE,	"FISTP" 	,0xdf,1|C_ESC_GROUP_TYPE|(7<<16),MAKE_OP_RW_FLAG(OP_W,0,0)}, //0x7

	//双字节浮点指令
	{ 0 , C_NULL													}, //0xc0
	{ 0 , C_NULL													}, //0xc1
	{ 0 , C_NULL													}, //0xc2
	{ 0 , C_NULL													}, //0xc3
	{ 0 , C_NULL													}, //0xc4
	{ 0 , C_NULL													}, //0xc5
	{ 0 , C_NULL													}, //0xc6
	{ 0 , C_NULL													}, //0xc7

	{ 0 , C_NULL													}, //0xc8
	{ 0 , C_NULL													}, //0xc9
	{ 0 , C_NULL													}, //0xca
	{ 0 , C_NULL													}, //0xcb
	{ 0 , C_NULL													}, //0xcc
	{ 0 , C_NULL													}, //0xcd
	{ 0 , C_NULL													}, //0xce
	{ 0 , C_NULL													}, //0xcf

	{ 0 , C_NULL													}, //0xd0
	{ 0 , C_NULL													}, //0xd1
	{ 0 , C_NULL													}, //0xd2
	{ 0 , C_NULL													}, //0xd3
	{ 0 , C_NULL													}, //0xd4
	{ 0 , C_NULL													}, //0xd5
	{ 0 , C_NULL													}, //0xd6
	{ 0 , C_NULL													}, //0xd7

	{ 0 , C_NULL													}, //0xd8
	{ 0 , C_NULL													}, //0xd9
	{ 0 , C_NULL													}, //0xda
	{ 0 , C_NULL													}, //0xdb
	{ 0 , C_NULL													}, //0xdc
	{ 0 , C_NULL													}, //0xdd
	{ 0 , C_NULL													}, //0xde
	{ 0 , C_NULL													}, //0xdf

	{ 0 , C_FSTSW,		D__AX,		D__NONE,	D__NONE,	"FSTSW"					,0xe0df,2|C_ESC_GROUP_TYPE|(40<<16),MAKE_OP_RW_FLAG(OP_W,0,0)}, //0xe0
	{ 0 , C_NULL																	}, //0xe1
	{ 0 , C_NULL																	}, //0xe2
	{ 0 , C_NULL																	}, //0xe3
	{ 0 , C_NULL																	}, //0xe4
	{ 0 , C_NULL																	}, //0xe5
	{ 0 , C_NULL																	}, //0xe6
	{ 0 , C_NULL																	}, //0xe7

	{ 0 , C_FUCOMIP,	D__st0,		D__st,		D__NONE,	"FUCOMIP" 	,0xe8df,2|C_ESC_GROUP_TYPE|(48<<16),MAKE_OP_RW_FLAG(OP_R,OP_R,0)}, //0xe8
	{ 0 , C_FUCOMIP,	D__st1,		D__st,		D__NONE,	"FUCOMIP" 	,0xe9df,2|C_ESC_GROUP_TYPE|(49<<16),MAKE_OP_RW_FLAG(OP_R,OP_R,0)}, //0xe9
	{ 0 , C_FUCOMIP,	D__st2,		D__st,		D__NONE,	"FUCOMIP" 	,0xeadf,2|C_ESC_GROUP_TYPE|(50<<16),MAKE_OP_RW_FLAG(OP_R,OP_R,0)}, //0xea
	{ 0 , C_FUCOMIP,	D__st3,		D__st,		D__NONE,	"FUCOMIP" 	,0xebdf,2|C_ESC_GROUP_TYPE|(51<<16),MAKE_OP_RW_FLAG(OP_R,OP_R,0)}, //0xeb
	{ 0 , C_FUCOMIP,	D__st4,		D__st,		D__NONE,	"FUCOMIP" 	,0xecdf,2|C_ESC_GROUP_TYPE|(52<<16),MAKE_OP_RW_FLAG(OP_R,OP_R,0)}, //0xec
	{ 0 , C_FUCOMIP,	D__st5,		D__st,		D__NONE,	"FUCOMIP" 	,0xeddf,2|C_ESC_GROUP_TYPE|(53<<16),MAKE_OP_RW_FLAG(OP_R,OP_R,0)}, //0xed
	{ 0 , C_FUCOMIP,	D__st6,		D__st,		D__NONE,	"FUCOMIP" 	,0xeedf,2|C_ESC_GROUP_TYPE|(54<<16),MAKE_OP_RW_FLAG(OP_R,OP_R,0)}, //0xee
	{ 0 , C_FUCOMIP,	D__st7,		D__st,		D__NONE,	"FUCOMIP" 	,0xefdf,2|C_ESC_GROUP_TYPE|(55<<16),MAKE_OP_RW_FLAG(OP_R,OP_R,0)}, //0xef

	{ 0 , C_FCOMIP,	D__st0,		D__st,		D__NONE,	"FCOMIP" 	,0xf0df,2|C_ESC_GROUP_TYPE|(56<<16),MAKE_OP_RW_FLAG(OP_R,OP_R,0)}, //0xf0
	{ 0 , C_FCOMIP,	D__st1,		D__st,		D__NONE,	"FCOMIP" 	,0xf1df,2|C_ESC_GROUP_TYPE|(57<<16),MAKE_OP_RW_FLAG(OP_R,OP_R,0)}, //0xf1
	{ 0 , C_FCOMIP,	D__st2,		D__st,		D__NONE,	"FCOMIP" 	,0xf2df,2|C_ESC_GROUP_TYPE|(58<<16),MAKE_OP_RW_FLAG(OP_R,OP_R,0)}, //0xf2
	{ 0 , C_FCOMIP,	D__st3,		D__st,		D__NONE,	"FCOMIP" 	,0xf3df,2|C_ESC_GROUP_TYPE|(59<<16),MAKE_OP_RW_FLAG(OP_R,OP_R,0)}, //0xf3
	{ 0 , C_FCOMIP,	D__st4,		D__st,		D__NONE,	"FCOMIP" 	,0xf4df,2|C_ESC_GROUP_TYPE|(60<<16),MAKE_OP_RW_FLAG(OP_R,OP_R,0)}, //0xf4
	{ 0 , C_FCOMIP,	D__st5,		D__st,		D__NONE,	"FCOMIP" 	,0xf5df,2|C_ESC_GROUP_TYPE|(61<<16),MAKE_OP_RW_FLAG(OP_R,OP_R,0)}, //0xf5
	{ 0 , C_FCOMIP,	D__st6,		D__st,		D__NONE,	"FCOMIP" 	,0xf6df,2|C_ESC_GROUP_TYPE|(62<<16),MAKE_OP_RW_FLAG(OP_R,OP_R,0)}, //0xf6
	{ 0 , C_FCOMIP,	D__st7,		D__st,		D__NONE,	"FCOMIP" 	,0xf7df,2|C_ESC_GROUP_TYPE|(63<<16),MAKE_OP_RW_FLAG(OP_R,OP_R,0)}, //0xf7

	{ 0 , C_NULL													}, //0xf8
	{ 0 , C_NULL													}, //0xf9
	{ 0 , C_NULL													}, //0xfa
	{ 0 , C_NULL													}, //0xfb
	{ 0 , C_NULL													}, //0xfc
	{ 0 , C_NULL													}, //0xfd
	{ 0 , C_NULL													}, //0xfe
	{ 0 , C_NULL													} //0xff

};

DIS_OPCODE_T Group0x0f01[] = //CPU保护模式指令
{
	{R_M, C_SGDT,		D__wMs,		D__NONE,	D__NONE,	"SGDT" 	,0x010f,2|C_GROUP_2_TYPE|(0<<16),MAKE_OP_RW_FLAG(OP_W,0,0)}, //0x0
	{R_M, C_SIDT,		D__wMs,		D__NONE,	D__NONE,	"SIDT" 	,0x010f,2|C_GROUP_2_TYPE|(1<<16),MAKE_OP_RW_FLAG(OP_W,0,0)}, //0x1
	{R_M, C_LGDT,		D__rMs,		D__NONE,	D__NONE,	"LGDT" 	,0x010f,2|C_GROUP_2_TYPE|(2<<16),MAKE_OP_RW_FLAG(OP_R,0,0)}, //0x2
	{R_M, C_LIDT,		D__rMs,		D__NONE,	D__NONE,	"LIDT" 	,0x010f,2|C_GROUP_2_TYPE|(3<<16),MAKE_OP_RW_FLAG(OP_R,0,0)}, //0x3
	{R_M, C_SMSW,		D__wMwRv,	D__NONE,	D__NONE,	"SMSW" 	,0x010f,2|C_GROUP_2_TYPE|(4<<16),MAKE_OP_RW_FLAG(OP_W,0,0)}, //0x4
	{R_M, C_NULL																					}, //0x5
	{R_M, C_LMSW,		D__rEw,		D__NONE,	D__NONE,	"LMSW" 	,0x010f,2|C_GROUP_2_TYPE|(6<<16),MAKE_OP_RW_FLAG(OP_R,0,0)}, //0x6
	{R_M, C_INVLPG,		D__Mb,		D__NONE,	D__NONE,	"INVLPG",0x010f,2|C_GROUP_2_TYPE|(7<<16),MAKE_OP_RW_FLAG(OP_R,0,0)}, //0x7

	//Group0x0f01_11_000[] =  //80386 reg=000	
	{R_M, C_NULL,		D__NONE,		D__NONE,	D__NONE,	}, //RM=0x0
	{R_M, C_VMCALL,		D__NONE,		D__NONE,	D__NONE,	"VMCALL",0x010f,2|C_GROUP_2_TYPE|(9<<16)}, //RM=0x1
	{R_M, C_VMLAUNCH,	D__NONE,		D__NONE,	D__NONE,	"VMLAUNCH",0x010f,2|C_GROUP_2_TYPE|(10<<16)}, //RM=0x2
	{R_M, C_VMRESUME,	D__NONE,		D__NONE,	D__NONE,	"VMRESUME",0x010f,2|C_GROUP_2_TYPE|(11<<16)}, //RM=0x3
	{R_M, C_VMXOFF,		D__NONE,		D__NONE,	D__NONE,	"VMXOFF",0x010f,2|C_GROUP_2_TYPE|(12<<16)}, //RM=0X4
	{R_M, C_NULL,		D__NONE,		D__NONE,	D__NONE,	}, //RM=0x5
	{R_M, C_NULL,		D__NONE,		D__NONE,	D__NONE,	}, //RM=0x6
	{R_M, C_NULL,		D__NONE,		D__NONE,	D__NONE,	}, //RM=0x7

	//Group0x0f01_11_000[] =  //80386 reg=001	

	{R_M, C_MONITOR,	D__NONE,		D__NONE,	D__NONE,	"monitor",0x010f,2|C_GROUP_2_TYPE|(16<<16)}, //RM=0x0
	{R_M, C_MWAIT,		D__NONE,		D__NONE,	D__NONE,	"mwait",0x010f,2|C_GROUP_2_TYPE|(17<<16)}, //RM=0x1
	{R_M, C_NULL,		D__NONE,		D__NONE,	D__NONE,	}, //RM=0x2
	{R_M, C_NULL,		D__NONE,		D__NONE,	D__NONE,	}, //RM=0x3
	{R_M, C_NULL,		D__NONE,		D__NONE,	D__NONE,	}, //RM=0x4
	{R_M, C_NULL,		D__NONE,		D__NONE,	D__NONE,	}, //RM=0x5
	{R_M, C_NULL,		D__NONE,		D__NONE,	D__NONE,	}, //RM=0x6
	{R_M, C_NULL,		D__NONE,		D__NONE,	D__NONE,	}, //RM=0x7

	//Group0x0f01_11_000[] =  //80386 reg=002	

	{R_M, C_XGETBV,		D__NONE,		D__NONE,	D__NONE,"xgetbv"	,0x010f,2|C_GROUP_2_TYPE|(24<<16)}, //RM=0x0
	{R_M, C_XSETBV,		D__NONE,		D__NONE,	D__NONE,"xsetbv"	,0x010f,2|C_GROUP_2_TYPE|(25<<16)}, //RM=0x1
	{R_M, C_NULL,		D__NONE,		D__NONE,	D__NONE,	}, //RM=0x2
	{R_M, C_NULL,		D__NONE,		D__NONE,	D__NONE,	}, //RM=0x3
	{R_M, C_NULL,		D__NONE,		D__NONE,	D__NONE,	}, //RM=0x4
	{R_M, C_NULL,		D__NONE,		D__NONE,	D__NONE,	}, //RM=0x5
	{R_M, C_NULL,		D__NONE,		D__NONE,	D__NONE,	}, //RM=0x6
	{R_M, C_NULL,		D__NONE,		D__NONE,	D__NONE,	}, //RM=0x7

	//Group0x0f01_11_000[] =  //80386 reg=003	

	{R_M, C_VMRUN,		D__EAX,		D__NONE,	D__NONE,"VMRUN"   ,0x010f,2|C_GROUP_2_TYPE|(32<<16),MAKE_OP_RW_FLAG(OP_R,0,0)}, //RM=0x0
	{R_M, C_VMMCALL,	D__NONE,	D__NONE,	D__NONE,"VMMCALL" ,0x010f,2|C_GROUP_2_TYPE|(33<<16)	}, //RM=0x1
	{R_M, C_VMLOAD,		D__EAX,		D__NONE,	D__NONE,"VMLOAD"  ,0x010f,2|C_GROUP_2_TYPE|(34<<16),MAKE_OP_RW_FLAG(OP_R,0,0)}, //RM=0x2
	{R_M, C_VMSAVE,		D__EAX,		D__NONE,	D__NONE,"VMSAVE"  ,0x010f,2|C_GROUP_2_TYPE|(35<<16),MAKE_OP_RW_FLAG(OP_W,0,0)}, //RM=0x3
	{R_M, C_STGI,		D__NONE,	D__NONE,	D__NONE,"STGI"	  ,0x010f,2|C_GROUP_2_TYPE|(36<<16)}, //RM=0x4
	{R_M, C_CLGI,		D__NONE,	D__NONE,	D__NONE,"CLGI"	  ,0x010f,2|C_GROUP_2_TYPE|(37<<16)}, //RM=0x5
	{R_M, C_SKINIT,		D__EAX,		D__NONE,	D__NONE,"SKINIT"  ,0x010f,2|C_GROUP_2_TYPE|(38<<16)	}, //RM=0x6
	{R_M, C_INVLPGA,	D__EAX,		D__ECX,		D__NONE,"INVLPGA" ,0x010f,2|C_GROUP_2_TYPE|(39<<16)	}, //RM=0x7

	//Group0x0f01_11_000[] =  //80386 reg=004	

	{R_M, C_SMSW,		D__wMwRv,		D__NONE,	D__NONE,	"SMSW" 	,0x010f,2|C_GROUP_2_TYPE|(40<<16),MAKE_OP_RW_FLAG(OP_W,0,0)}, //RM=0x0
	{R_M, C_SMSW,		D__wMwRv,		D__NONE,	D__NONE,	"SMSW" 	,0x010f,2|C_GROUP_2_TYPE|(41<<16),MAKE_OP_RW_FLAG(OP_W,0,0)}, //RM=0x1
	{R_M, C_SMSW,		D__wMwRv,		D__NONE,	D__NONE,	"SMSW" 	,0x010f,2|C_GROUP_2_TYPE|(42<<16),MAKE_OP_RW_FLAG(OP_W,0,0)}, //RM=0x2
	{R_M, C_SMSW,		D__wMwRv,		D__NONE,	D__NONE,	"SMSW" 	,0x010f,2|C_GROUP_2_TYPE|(43<<16),MAKE_OP_RW_FLAG(OP_W,0,0)}, //RM=0x3
	{R_M, C_SMSW,		D__wMwRv,		D__NONE,	D__NONE,	"SMSW" 	,0x010f,2|C_GROUP_2_TYPE|(44<<16),MAKE_OP_RW_FLAG(OP_W,0,0)}, //RM=0x4
	{R_M, C_SMSW,		D__wMwRv,		D__NONE,	D__NONE,	"SMSW" 	,0x010f,2|C_GROUP_2_TYPE|(45<<16),MAKE_OP_RW_FLAG(OP_W,0,0)}, //RM=0x5
	{R_M, C_SMSW,		D__wMwRv,		D__NONE,	D__NONE,	"SMSW" 	,0x010f,2|C_GROUP_2_TYPE|(46<<16),MAKE_OP_RW_FLAG(OP_W,0,0)}, //RM=0x6
	{R_M, C_SMSW,		D__wMwRv,		D__NONE,	D__NONE,	"SMSW" 	,0x010f,2|C_GROUP_2_TYPE|(47<<16),MAKE_OP_RW_FLAG(OP_W,0,0)}, //RM=0x7


	//Group0x0f01_11_000[] =  //80386 reg=005	

	{R_M, C_NULL,		D__NONE,		D__NONE,	D__NONE,	}, //RM=0x0
	{R_M, C_NULL,		D__NONE,		D__NONE,	D__NONE,	},//RM=0x1
	{R_M, C_NULL,		D__NONE,		D__NONE,	D__NONE,	}, //RM=0x2
	{R_M, C_NULL,		D__NONE,		D__NONE,	D__NONE,	}, //RM=0x3
	{R_M, C_NULL,		D__NONE,		D__NONE,	D__NONE,	}, //RM=0x4
	{R_M, C_NULL,		D__NONE,		D__NONE,	D__NONE,	}, //RM=0x5
	{R_M, C_NULL,		D__NONE,		D__NONE,	D__NONE,	}, //RM=0x6
	{R_M, C_NULL,		D__NONE,		D__NONE,	D__NONE,	}, //RM=0x7

	//Group0x0f01_11_000[] =  //80386 reg=006	

	{R_M, C_LMSW,		D__rEw,		D__NONE,	D__NONE,	"LMSW" 	,0x010f,2|C_GROUP_2_TYPE|(56<<16),MAKE_OP_RW_FLAG(OP_R,0,0)}, //RM=0x0
	{R_M, C_LMSW,		D__rEw,		D__NONE,	D__NONE,	"LMSW" 	,0x010f,2|C_GROUP_2_TYPE|(57<<16),MAKE_OP_RW_FLAG(OP_R,0,0)}, //RM=0x1
	{R_M, C_LMSW,		D__rEw,		D__NONE,	D__NONE,	"LMSW" 	,0x010f,2|C_GROUP_2_TYPE|(58<<16),MAKE_OP_RW_FLAG(OP_R,0,0)}, //RM=0x2
	{R_M, C_LMSW,		D__rEw,		D__NONE,	D__NONE,	"LMSW" 	,0x010f,2|C_GROUP_2_TYPE|(59<<16),MAKE_OP_RW_FLAG(OP_R,0,0)}, //RM=0x3
	{R_M, C_LMSW,		D__rEw,		D__NONE,	D__NONE,	"LMSW" 	,0x010f,2|C_GROUP_2_TYPE|(60<<16),MAKE_OP_RW_FLAG(OP_R,0,0)}, //RM=0x4
	{R_M, C_LMSW,		D__rEw,		D__NONE,	D__NONE,	"LMSW" 	,0x010f,2|C_GROUP_2_TYPE|(61<<16),MAKE_OP_RW_FLAG(OP_R,0,0)}, //RM=0x5
	{R_M, C_LMSW,		D__rEw,		D__NONE,	D__NONE,	"LMSW" 	,0x010f,2|C_GROUP_2_TYPE|(62<<16),MAKE_OP_RW_FLAG(OP_R,0,0)}, //RM=0x6
	{R_M, C_LMSW,		D__rEw,		D__NONE,	D__NONE,	"LMSW" 	,0x010f,2|C_GROUP_2_TYPE|(63<<16),MAKE_OP_RW_FLAG(OP_R,0,0)}, //RM=0x7


	//Group0x0f01_11_000[] =  //80386 reg=007	

	{R_M, C_SWAPGS,		D__NONE,		D__NONE,	D__NONE,"SWAPGS"	,0x010f,2|C_GROUP_2_TYPE|(64<<16)}, //RM=0x0
	{R_M, C_RDTSCP,		D__NONE,		D__NONE,	D__NONE,"RDTSCP"	,0x010f,2|C_GROUP_2_TYPE|(65<<16)}, //RM=0x1
	{R_M, C_NULL,		D__NONE,		D__NONE,	D__NONE,	}, //RM=0x2
	{R_M, C_NULL,		D__NONE,		D__NONE,	D__NONE,	}, //RM=0x3
	{R_M, C_NULL,		D__NONE,		D__NONE,	D__NONE,	}, //RM=0x4
	{R_M, C_NULL,		D__NONE,		D__NONE,	D__NONE,	}, //RM=0x5
	{R_M, C_NULL,		D__NONE,		D__NONE,	D__NONE,	}, //RM=0x6
	{R_M, C_NULL,		D__NONE,		D__NONE,	D__NONE,	}, //RM=0x7

};


DIS_OPCODE_T Group0x0f18[] =  //80386
{
	{R_M, C_PREFETCH,	D__Mb,		D__NONE,	D__NONE,	"prefetchnta"				,0x180f,2|C_GROUP_0_TYPE|(0<<16),MAKE_OP_RW_FLAG(OP_R,0,0)}, //0x0
	{R_M, C_PREFETCH,	D__Mb,		D__NONE,	D__NONE,	"prefetcht0"				,0x180f,2|C_GROUP_0_TYPE|(1<<16),MAKE_OP_RW_FLAG(OP_R,0,0)}, //0x1
	{R_M, C_PREFETCH,	D__Mb,		D__NONE,	D__NONE,	"prefetcht1"				,0x180f,2|C_GROUP_0_TYPE|(2<<16),MAKE_OP_RW_FLAG(OP_R,0,0)}, //0x2
	{R_M, C_PREFETCH,	D__Mb,		D__NONE,	D__NONE,	"prefetcht2"				,0x180f,2|C_GROUP_0_TYPE|(3<<16),MAKE_OP_RW_FLAG(OP_R,0,0)}, //0x3
	{R_M, C_NULL,																	}, //0x4
	{R_M, C_NULL,																	}, //0x5
	{R_M, C_NULL,																	}, //0x6
	{R_M, C_NULL,																	}, //0x7
};

DIS_OPCODE_T Group0x0f71_reg_010[] =
{
	{R_M |Immediate_Ib, C_PSRLW,	D__Nq,	D__Ib,		D__NONE,"psrlw"	,0x710f,2|C_GROUP_5_TYPE|(2<<16),MAKE_OP_RW_FLAG(OP_RW,OP_R,OP_R)}, //no prefix 
	{R_M |Immediate_Ib, C_PSRLW,	D__Udq,	D__Ib,		D__NONE,"psrlw"	,0x710f66,3|C_GROUP_5_TYPE|(2<<16),MAKE_OP_RW_FLAG(OP_RW,OP_R,OP_R)}, //0x66
	{0, C_NULL,	D__NONE,	D__NONE,		D__NONE,}, //0xf2 
	{0, C_NULL,	D__NONE,	D__NONE,		D__NONE,}, //0xf3 
};

DIS_OPCODE_T Group0x0f71_reg_100[] =
{
	{R_M |Immediate_Ib, C_PSRAW,	D__Nq,	D__Ib,		D__NONE,"psraw"	,0x710f,2|C_GROUP_5_TYPE|(4<<16),MAKE_OP_RW_FLAG(OP_RW,OP_R,OP_R)}, //no prefix 
	{R_M |Immediate_Ib, C_PSRAW,	D__Udq,	D__Ib,		D__NONE,"psraw"	,0x710f66,3|C_GROUP_5_TYPE|(4<<16),MAKE_OP_RW_FLAG(OP_RW,OP_R,OP_R)}, //0x66
	{0, C_NULL,	D__NONE,	D__NONE,		D__NONE,}, //0xf2 
	{0, C_NULL,	D__NONE,	D__NONE,		D__NONE,}, //0xf3 
};

DIS_OPCODE_T Group0x0f71_reg_110[] =
{
	{R_M |Immediate_Ib, C_PSLLW,	D__Nq,	D__Ib,		D__NONE,"psllw"	,0x710f,2|C_GROUP_5_TYPE|(6<<16),MAKE_OP_RW_FLAG(OP_RW,OP_R,OP_R)}, //no prefix 
	{R_M |Immediate_Ib, C_PSLLW,	D__Udq,	D__Ib,		D__NONE,"psllw"	,0x710f66,3|C_GROUP_5_TYPE|(6<<16),MAKE_OP_RW_FLAG(OP_RW,OP_R,OP_R)}, //0x66
	{0, C_NULL,	D__NONE,	D__NONE,		D__NONE,}, //0xf2 
	{0, C_NULL,	D__NONE,	D__NONE,		D__NONE,}, //0xf3 
};

DIS_OPCODE_T Group0x0f71[] =  //80386
{

	{R_M, C_NULL,	D__NONE,	D__NONE,	D__NONE,								}, //0x0
	{R_M, C_NULL,	D__NONE,	D__NONE,	D__NONE,								}, //0x1
	{R_M, C_GRP3,	D__NONE,	D__NONE,	D__NONE,	(char*)Group0x0f71_reg_010 	,0x710f,2|C_GROUP_0_TYPE|(10<<16)}, //0x2
	{R_M, C_NULL,	D__NONE,	D__NONE,	D__NONE,								}, //0x3
	{R_M, C_GRP3,	D__NONE,	D__NONE,	D__NONE,	(char*)Group0x0f71_reg_100  ,0x710f,2|C_GROUP_0_TYPE|(12<<16)}, //0x4
	{R_M, C_NULL,	D__NONE,	D__NONE,	D__NONE,								}, //0x5
	{R_M, C_GRP3,	D__NONE,	D__NONE,	D__NONE,	(char*)Group0x0f71_reg_110  ,0x710f,2|C_GROUP_0_TYPE|(14<<16)}, //0x6
	{R_M, C_NULL,	D__NONE,	D__NONE,	D__NONE,								} //0x7

};

DIS_OPCODE_T Group0x0f72_reg_010[] =
{
	{R_M |Immediate_Ib, C_PSRLD,	D__Nq,	D__Ib,		D__NONE,"psrld"	,0x720f,2|C_GROUP_5_TYPE|(2<<16),MAKE_OP_RW_FLAG(OP_RW,OP_R,OP_R)}, //no prefix 
	{R_M |Immediate_Ib, C_PSRLD,	D__Udq,	D__Ib,		D__NONE,"psrld"	,0x720f66,3|C_GROUP_5_TYPE|(2<<16),MAKE_OP_RW_FLAG(OP_RW,OP_R,OP_R)}, //0x66
	{0, C_NULL,	D__NONE,	D__NONE,		D__NONE,}, //0xf2 
	{0, C_NULL,	D__NONE,	D__NONE,		D__NONE,}, //0xf3 
};

DIS_OPCODE_T Group0x0f72_reg_100[] =
{
	{R_M |Immediate_Ib, C_PSRAD,	D__Nq,	D__Ib,		D__NONE,"psrad"	,0x720f,2|C_GROUP_5_TYPE|(4<<16),MAKE_OP_RW_FLAG(OP_RW,OP_R,OP_R)}, //no prefix 
	{R_M |Immediate_Ib, C_PSRAD,	D__Udq,	D__Ib,		D__NONE,"psrad"	,0x720f66,3|C_GROUP_5_TYPE|(4<<16),MAKE_OP_RW_FLAG(OP_RW,OP_R,OP_R)}, //0x66
	{0, C_NULL,	D__NONE,	D__NONE,		D__NONE,}, //0xf2 
	{0, C_NULL,	D__NONE,	D__NONE,		D__NONE,}, //0xf3 
};

DIS_OPCODE_T Group0x0f72_reg_110[] =
{
	{R_M |Immediate_Ib, C_PSLLD,	D__Nq,	D__Ib,		D__NONE,"pslld"	,0x720f,2|C_GROUP_5_TYPE|(6<<16),MAKE_OP_RW_FLAG(OP_RW,OP_R,OP_R)}, //no prefix 
	{R_M |Immediate_Ib, C_PSLLD,	D__Udq,	D__Ib,		D__NONE,"pslld"	,0x720f66,3|C_GROUP_5_TYPE|(6<<16),MAKE_OP_RW_FLAG(OP_RW,OP_R,OP_R)}, //0x66
	{0, C_NULL,	D__NONE,	D__NONE,		D__NONE,}, //0xf2 
	{0, C_NULL,	D__NONE,	D__NONE,		D__NONE,}, //0xf3 
};

DIS_OPCODE_T Group0x0f72[] =  //80386
{

	{R_M, C_NULL,	D__NONE,	D__NONE,	D__NONE,								}, //0x0
	{R_M, C_NULL,	D__NONE,	D__NONE,	D__NONE,								}, //0x1
	{R_M |Immediate_Ib, C_GRP3,	D__Pq,		D__Ib,		D__NONE,	(char*)Group0x0f72_reg_010	,0x720f,2|C_GROUP_1_TYPE|(10<<16)}, //0x2
	{R_M, C_NULL,	D__NONE,	D__NONE,	D__NONE,								}, //0x3
	{R_M |Immediate_Ib, C_GRP3,	D__Pq,		D__Ib,		D__NONE,	(char*)Group0x0f72_reg_100	,0x720f,2|C_GROUP_1_TYPE|(12<<16)}, //0x4
	{R_M, C_NULL,	D__NONE,	D__NONE,	D__NONE,								}, //0x5
	{R_M |Immediate_Ib, C_GRP3,	D__Pq,		D__Ib,		D__NONE,	(char*)Group0x0f72_reg_110	,0x720f,2|C_GROUP_1_TYPE|(14<<16)}, //0x6
	{R_M, C_NULL,	D__NONE,	D__NONE,	D__NONE,								} //0x7

};


DIS_OPCODE_T Group0x0f73_reg_010[] =
{
	{R_M |Immediate_Ib, C_PSRLQ,	D__Nq,	D__Ib,		D__NONE,"psrlq"	,0x730f,2|C_GROUP_5_TYPE|(2<<16),MAKE_OP_RW_FLAG(OP_RW,OP_R,OP_R)}, //no prefix 
	{R_M |Immediate_Ib, C_PSRLQ,	D__Udq,	D__Ib,		D__NONE,"psrlq"	,0x730f66,3|C_GROUP_5_TYPE|(2<<16),MAKE_OP_RW_FLAG(OP_RW,OP_R,OP_R)}, //0x66
	{0, C_NULL,	D__NONE,	D__NONE,		D__NONE,}, //0xf2 
	{0, C_NULL,	D__NONE,	D__NONE,		D__NONE,}, //0xf3 
};

DIS_OPCODE_T Group0x0f73_reg_011[] =
{
	{R_M |Immediate_Ib, C_NULL,	}, //no prefix 
	{R_M |Immediate_Ib, C_PSRLDQ,	D__Udq,	D__Ib,		D__NONE,"psrldq"	,0x730f66,3|C_GROUP_5_TYPE|(3<<16),MAKE_OP_RW_FLAG(OP_RW,OP_R,OP_R)}, //0x66
	{0, C_NULL,	D__NONE,	D__NONE,		D__NONE,}, //0xf2 
	{0, C_NULL,	D__NONE,	D__NONE,		D__NONE,}, //0xf3 
};

DIS_OPCODE_T Group0x0f73_reg_110[] =
{
	{R_M |Immediate_Ib, C_PSLLQ,	D__Nq,	D__Ib,		D__NONE,"psllq"	,0x730f,2|C_GROUP_5_TYPE|(6<<16),MAKE_OP_RW_FLAG(OP_RW,OP_R,OP_R)}, //no prefix 
	{R_M |Immediate_Ib, C_PSLLQ,	D__Udq,	D__Ib,		D__NONE,"psllq"	,0x730f66,3|C_GROUP_5_TYPE|(6<<16),MAKE_OP_RW_FLAG(OP_RW,OP_R,OP_R)}, //0x66
	{0, C_NULL,	D__NONE,	D__NONE,		D__NONE,}, //0xf2 
	{0, C_NULL,	D__NONE,	D__NONE,		D__NONE,}, //0xf3 
};

DIS_OPCODE_T Group0x0f73_reg_111[] =
{
	{0, C_NULL,	D__NONE,	D__NONE,		D__NONE,},  
	{R_M |Immediate_Ib, C_PSLLDQ,	D__Udq,	D__Ib,		D__NONE,"pslldq"	,0x730f66,3|C_GROUP_5_TYPE|(7<<16),MAKE_OP_RW_FLAG(OP_RW,OP_R,OP_R)}, //0x66
	{0, C_NULL,	D__NONE,	D__NONE,		D__NONE,}, //0xf2 
	{0, C_NULL,	D__NONE,	D__NONE,		D__NONE,}, //0xf3 
};

DIS_OPCODE_T Group0x0f73[] =  //80386
{
	{R_M, C_NULL,	D__NONE,	D__NONE,	D__NONE,								}, //0x0
	{R_M, C_NULL,	D__NONE,	D__NONE,	D__NONE,								}, //0x1
	{R_M |Immediate_Ib, C_GRP3,	D__NONE,	D__NONE,		D__NONE,	(char*)Group0x0f73_reg_010	,0x730f,2|C_GROUP_5_TYPE|(10<<16)}, //0x2
	{R_M |Immediate_Ib, C_GRP3,	D__NONE,	D__NONE,		D__NONE,	(char*)Group0x0f73_reg_011	,0x730f,2|C_GROUP_5_TYPE|(10<<16)}, //0x2
	{R_M, C_NULL,	D__NONE,	D__NONE,	D__NONE,								}, //0x4
	{R_M, C_NULL,	D__NONE,	D__NONE,	D__NONE,								}, //0x5
	{R_M |Immediate_Ib, C_GRP3,	D__NONE,	D__NONE,		D__NONE,	(char*)Group0x0f73_reg_110	,0x730f,2|C_GROUP_5_TYPE|(14<<16)}, //0x6
	{R_M |Immediate_Ib, C_GRP3,	D__NONE,	D__NONE,		D__NONE,	(char*)Group0x0f73_reg_111	,0x730f,2|C_GROUP_5_TYPE|(14<<16)}, //0x6
};

DIS_OPCODE_T Group0x0fae[] =  //80386
{
	{R_M, C_FXSAVE, D__M,	D__NONE,	D__NONE,	"fxsave" 		,0xae0f,2|C_GROUP_1_TYPE|(0<<16),MAKE_OP_RW_FLAG(OP_R,0,0)}, //0x0
	{R_M, C_FXRSTOR,D__M,	D__NONE,	D__NONE,	"fxrstor" 		,0xae0f,2|C_GROUP_1_TYPE|(1<<16),MAKE_OP_RW_FLAG(OP_R,0,0)}, //0x1
	{R_M, C_LDMXCSR,D__Ed,	D__NONE,	D__NONE,	"ldmxcsr" 		,0xae0f,2|C_GROUP_1_TYPE|(2<<16),MAKE_OP_RW_FLAG(OP_R,0,0)}, //0x2
	{R_M, C_STMXCSR,D__Ed,	D__NONE,	D__NONE,	"stmxcsr" 		,0xae0f,2|C_GROUP_1_TYPE|(3<<16),MAKE_OP_RW_FLAG(OP_W,0,0)}, //0x3
	{R_M, C_XSAVE,D__M,		D__NONE,	D__NONE,	"XSAVE"			,0xae0f,2|C_GROUP_1_TYPE|(4<<16),MAKE_OP_RW_FLAG(OP_W,0,0)}, //0x4
	{R_M, C_XRSTOR,D__M,	D__NONE,	D__NONE,	"XRSTOR"		,0xae0f,2|C_GROUP_1_TYPE|(5<<16),MAKE_OP_RW_FLAG(OP_R,0,0)}, //0x5
	{R_M, C_NULL,																	}, //0x6
	{R_M, C_CLFLUSH,D__Eb,	D__NONE,	D__NONE,	"clflush"					,0xae0f,2|C_GROUP_1_TYPE|(7<<16),MAKE_OP_RW_FLAG(OP_W,0,0)}, //0x7

	//Group0x0fae_11b[] =  //80386
	{R_M, C_NULL,																	}, //0x0
	{R_M, C_NULL,																	}, //0x1
	{R_M, C_NULL,																	}, //0x2
	{R_M, C_NULL,																	}, //0x3
	{R_M, C_NULL,																	}, //0x4
	{R_M, C_LFENCE,	D__NONE,	D__NONE,	D__NONE,	"lfence"					,0xae0f,2|C_GROUP_1_TYPE|(13<<16)}, //0x5
	{R_M, C_MFENCE,	D__NONE,	D__NONE,	D__NONE,	"mfence"					,0xae0f,2|C_GROUP_1_TYPE|(14<<16)}, //0x6
	{R_M, C_SFENCE,	D__NONE,	D__NONE,	D__NONE,	"sfence"					,0xae0f,2|C_GROUP_1_TYPE|(15<<16)} //0x7

};



DIS_OPCODE_T Group0x0fc7_reg_001[] =
{
	{R_M|F_64 , C_CMPXCHG8B,	D__MqMdq,	D__NONE,		D__NONE,"CMPXCHG8B"	,0xc70f,2|C_GROUP_5_TYPE|(1<<16),MAKE_OP_RW_FLAG(OP_RW,0,0)}, //0x63
	{0, C_NULL,	D__NONE,	D__NONE,		D__NONE,}, //0x66
	{0, C_NULL,	D__NONE,	D__NONE,		D__NONE,}, //0xf2 
	{0, C_NULL,	D__NONE,	D__NONE,		D__NONE,}, //0xf3 
};

DIS_OPCODE_T Group0x0fc7_reg_110[] =
{
	{R_M , C_VMPTRLD,	D__Mq,	D__NONE,		D__NONE,"VMPTRLD"	,0xc70f,2|C_GROUP_5_TYPE|(6<<16),MAKE_OP_RW_FLAG(OP_R,0,0)}, //no prefix 
	{R_M , C_VMCLEAR,	D__Mq,	D__NONE,		D__NONE,"VMCLEAR"	,0xc70f66,3|C_GROUP_5_TYPE|(6<<16),MAKE_OP_RW_FLAG(OP_R,0,0)}, //0x66
	{0, C_NULL,	D__NONE,	D__NONE,		D__NONE,}, //0xf2 
	{R_M, C_VMXON,	D__Mq,	D__NONE,		D__NONE,"VMXON",0xc70ff3,3|C_GROUP_5_TYPE|(6<<16),MAKE_OP_RW_FLAG(OP_R,0,0)}, //0xf3 
};

DIS_OPCODE_T Group0x0fc7_reg_111[] =
{
	{R_M|F_64 , C_VMPTRST,	D__Mq,	D__NONE,		D__NONE,"VMPTRST"	,0xc70f,2|C_GROUP_5_TYPE|(7<<16),MAKE_OP_RW_FLAG(OP_R,0,0)}, //no prefix 
	{0, C_NULL,	D__NONE,	D__NONE,		D__NONE,}, //0x66
	{0, C_NULL,	D__NONE,	D__NONE,		D__NONE,}, //0xf2 
	{0, C_NULL,	D__NONE,	D__NONE,		D__NONE,}, //0xf3 
};

DIS_OPCODE_T Group0x0fc7[] =  //80386
{
	{R_M, C_NULL,	D__NONE,	D__NONE,	D__NONE,										}, //0x00
	{R_M|F_64 , C_CMPXCHG8B,	D__MqMdq,	D__NONE,		D__NONE,"CMPXCHG8B"	,0xc70f,2|C_GROUP_0_TYPE|(1<<16),MAKE_OP_RW_FLAG(OP_RW,0,0)}, //0x63
	{R_M, C_NULL,	D__NONE,	D__NONE,	D__NONE,									}, //0x2
	{R_M, C_NULL,	D__NONE,	D__NONE,	D__NONE,										}, //0x3
	{R_M, C_NULL,	D__NONE,	D__NONE,	D__NONE,										}, //0x4
	{R_M, C_NULL,	D__NONE,	D__NONE,	D__NONE,										}, //0x5
	{R_M, C_GRP3,D__NONE,		D__NONE,	D__NONE,	(char*)Group0x0fc7_reg_110	,0xc70f,2|C_GROUP_0_TYPE|(6<<16)}, //0x6
	{R_M, C_GRP3,D__NONE,		D__NONE,	D__NONE,	(char*)Group0x0fc7_reg_111	,0xc70f,2|C_GROUP_0_TYPE|(7<<16)}, //0x7
};



DIS_OPCODE_T Group0x0f3800[] =
{
	{R_M, C_PSHUFB,	D__Pq,	D__Qq,	D__NONE	,"pshufb",	0x00380f,3|C_GROUP_3_TYPE,MAKE_OP_RW_FLAG(OP_RW,OP_R,0)}, //no prefix 
	{R_M, C_PSHUFB,	D__Vdq,	D__Wdq,	D__NONE	,"pshufb"			,0x00380f66,4|C_GROUP_3_TYPE,MAKE_OP_RW_FLAG(OP_RW,OP_R,0)}, //prefix 0x66
	{R_M, C_NULL,															}, //prefix 0xf2
	{R_M, C_NULL,		}, //prefix 0xf3
};

DIS_OPCODE_T Group0x0f3801[] =
{
	{R_M, C_PHADDW,	D__Pq,	D__Qq,	D__NONE	,"phaddw",0x01380f,3|C_GROUP_3_TYPE,MAKE_OP_RW_FLAG(OP_RW,OP_R,0)}, //no prefix 
	{R_M, C_PHADDW,	D__Vdq,	D__Wdq,	D__NONE	,"phaddw",0x01380f66,4|C_GROUP_3_TYPE,MAKE_OP_RW_FLAG(OP_RW,OP_R,0)}, //prefix 0x66
	{R_M, C_NULL,															}, //prefix 0xf2
	{R_M, C_NULL,		}, //prefix 0xf3
};
DIS_OPCODE_T Group0x0f3802[] =
{
	{R_M, C_PHADDD,	D__Pq,	D__Qq,	D__NONE	,"phaddd",0x02380f,3|C_GROUP_3_TYPE,MAKE_OP_RW_FLAG(OP_RW,OP_R,0)}, //no prefix 
	{R_M, C_PHADDD,	D__Vdq,	D__Wdq,	D__NONE	,"phaddd",0x02380f66,4|C_GROUP_3_TYPE,MAKE_OP_RW_FLAG(OP_RW,OP_R,0)}, //prefix 0x66
	{R_M, C_NULL,															}, //prefix 0xf2
	{R_M, C_NULL,		}, //prefix 0xf3
};
DIS_OPCODE_T Group0x0f3803[] =
{
	{R_M, C_PHADDSW,	D__Pq,	D__Qq,	D__NONE	,"phaddsw",0x03380f,3|C_GROUP_3_TYPE,MAKE_OP_RW_FLAG(OP_RW,OP_R,0)}, //no prefix 
	{R_M, C_PHADDSW,	D__Vdq,	D__Wdq,	D__NONE	,"phaddsw",0x03380f66,4|C_GROUP_3_TYPE,MAKE_OP_RW_FLAG(OP_RW,OP_R,0)}, //prefix 0x66
	{R_M, C_NULL,															}, //prefix 0xf2
	{R_M, C_NULL,		}, //prefix 0xf3
};
DIS_OPCODE_T Group0x0f3804[] =
{
	{R_M, C_PMADDUBSW,	D__Pq,	D__Qq,	D__NONE	,"pmaddubsw",0x04380f,3|C_GROUP_3_TYPE,MAKE_OP_RW_FLAG(OP_RW,OP_R,0)}, //no prefix 
	{R_M, C_PMADDUBSW,	D__Vdq,	D__Wdq,	D__NONE	,"pmaddubsw",0x04380f66,4|C_GROUP_3_TYPE,MAKE_OP_RW_FLAG(OP_RW,OP_R,0)}, //prefix 0x66
	{R_M, C_NULL,															}, //prefix 0xf2
	{R_M, C_NULL,		}, //prefix 0xf3
};
DIS_OPCODE_T Group0x0f3805[] =
{
	{R_M, C_PHSUBW,	D__Pq,	D__Qq,	D__NONE	,"phsubw",0x05380f,3|C_GROUP_3_TYPE,MAKE_OP_RW_FLAG(OP_RW,OP_R,0)}, //no prefix 
	{R_M, C_PHSUBW,	D__Vdq,	D__Wdq,	D__NONE	,"phsubw",0x05380f66,4|C_GROUP_3_TYPE,MAKE_OP_RW_FLAG(OP_RW,OP_R,0)}, //prefix 0x66
	{R_M, C_NULL,															}, //prefix 0xf2
	{R_M, C_NULL,		}, //prefix 0xf3
};
DIS_OPCODE_T Group0x0f3806[] =
{
	{R_M, C_PHSUBD,	D__Pq,	D__Qq,	D__NONE	,"phsubd",0x06380f,3|C_GROUP_3_TYPE,MAKE_OP_RW_FLAG(OP_RW,OP_R,0)}, //no prefix 
	{R_M, C_PHSUBD,	D__Vdq,	D__Wdq,	D__NONE	,"phsubd",0x06380f66,4|C_GROUP_3_TYPE,MAKE_OP_RW_FLAG(OP_RW,OP_R,0)}, //prefix 0x66
	{R_M, C_NULL,															}, //prefix 0xf2
	{R_M, C_NULL,		}, //prefix 0xf3
};
DIS_OPCODE_T Group0x0f3807[] =
{
	{R_M, C_PHSUBSW,	D__Pq,	D__Qq,	D__NONE	,"phsubsw",0x07380f,3|C_GROUP_3_TYPE,MAKE_OP_RW_FLAG(OP_RW,OP_R,0)}, //no prefix 
	{R_M, C_PHSUBSW,	D__Vdq,	D__Wdq,	D__NONE	,"phsubsw",0x07380f66,4|C_GROUP_3_TYPE,MAKE_OP_RW_FLAG(OP_RW,OP_R,0)}, //prefix 0x66
	{R_M, C_NULL,															}, //prefix 0xf2
	{R_M, C_NULL,		}, //prefix 0xf3
};
DIS_OPCODE_T Group0x0f3808[] =
{
	{R_M, C_PSIGNB,	D__Pq,	D__Qq,	D__NONE	,"psignb",0x08380f,3|C_GROUP_3_TYPE,MAKE_OP_RW_FLAG(OP_RW,OP_R,0)}, //no prefix 
	{R_M, C_PSIGNB,	D__Vdq,	D__Wdq,	D__NONE	,"psignb",0x08380f66,4|C_GROUP_3_TYPE,MAKE_OP_RW_FLAG(OP_RW,OP_R,0)}, //prefix 0x66
	{R_M, C_NULL,															}, //prefix 0xf2
	{R_M, C_NULL,		}, //prefix 0xf3
};
DIS_OPCODE_T Group0x0f3809[] =
{
	{R_M, C_PSIGNW,	D__Pq,	D__Qq,	D__NONE	,"psignw"			,0x09380f,3|C_GROUP_3_TYPE,MAKE_OP_RW_FLAG(OP_RW,OP_R,0)}, //no prefix 
	{R_M, C_PSIGNW,	D__Vdq,	D__Wdq,	D__NONE	,"psignw"			,0x09380f66,4|C_GROUP_3_TYPE,MAKE_OP_RW_FLAG(OP_RW,OP_R,0)}, //prefix 0x66
	{R_M, C_NULL,															}, //prefix 0xf2
	{R_M, C_NULL,		}, //prefix 0xf3
};
DIS_OPCODE_T Group0x0f380a[] =
{
	{R_M, C_PSIGND,	D__Pq,	D__Qq,	D__NONE	,"psignd",0x0a380f,3|C_GROUP_3_TYPE,MAKE_OP_RW_FLAG(OP_RW,OP_R,0)}, //no prefix 
	{R_M, C_PSIGND,	D__Vdq,	D__Wdq,	D__NONE	,"psignd",0x0a380f66,4|C_GROUP_3_TYPE,MAKE_OP_RW_FLAG(OP_RW,OP_R,0)}, //prefix 0x66
	{R_M, C_NULL,															}, //prefix 0xf2
	{R_M, C_NULL,		}, //prefix 0xf3
};
DIS_OPCODE_T Group0x0f380b[] =
{
	{R_M, C_PMULHRSW,	D__Pq,	D__Qq,	D__NONE	,"pmulhrsw",0x0b380f,3|C_GROUP_3_TYPE,MAKE_OP_RW_FLAG(OP_RW,OP_R,0)}, //no prefix 
	{R_M, C_PMULHRSW,	D__Vdq,	D__Wdq,	D__NONE	,"pmulhrsw"	,0x0b380f66,4|C_GROUP_3_TYPE,MAKE_OP_RW_FLAG(OP_RW,OP_R,0)}, //prefix 0x66
	{R_M, C_NULL,															}, //prefix 0xf2
	{R_M, C_NULL,		}, //prefix 0xf3
};

DIS_OPCODE_T Group0x0f3810[] =
{
	{R_M, C_NULL}, //no prefix 
	{R_M, C_PBLENDVB,	D__Vdq,	D__Wdq,	D__NONE	,"pblendvb"			,0x10380f66,4|C_GROUP_3_TYPE,MAKE_OP_RW_FLAG(OP_RW,OP_R,0)}, //prefix 0x66
	{R_M, C_NULL,															}, //prefix 0xf2
	{R_M, C_NULL,		}, //prefix 0xf3
};

DIS_OPCODE_T Group0x0f3814[] =
{
	{R_M, C_NULL}, //no prefix 
	{R_M, C_BLENDVPS,	D__Vdq,	D__Wdq,	D__NONE	,"blendvps"			,0x14380f66,4|C_GROUP_3_TYPE,MAKE_OP_RW_FLAG(OP_RW,OP_R,0)}, //prefix 0x66
	{R_M, C_NULL,															}, //prefix 0xf2
	{R_M, C_NULL,		}, //prefix 0xf3
};

DIS_OPCODE_T Group0x0f3815[] =
{
	{R_M, C_NULL,	}, //no prefix 
	{R_M, C_BLENDVPD,	D__Vdq,	D__Wdq,	D__NONE	,"blendvpd"			,0x15380f66,4|C_GROUP_3_TYPE,MAKE_OP_RW_FLAG(OP_RW,OP_R,0)}, //prefix 0x66
	{R_M, C_NULL,															}, //prefix 0xf2
	{R_M, C_NULL,		}, //prefix 0xf3
};

DIS_OPCODE_T Group0x0f3817[] =
{
	{R_M, C_NULL,		}, //no prefix 
	{R_M, C_PTEST,	D__Vdq,	D__Wdq,	D__NONE	,"ptest"			,0x17380f66,4|C_GROUP_3_TYPE,MAKE_OP_RW_FLAG(OP_R,OP_R,0)}, //prefix 0x66
	{R_M, C_NULL,		}, //prefix 0xf2
	{R_M, C_NULL,		}, //prefix 0xf3
};

DIS_OPCODE_T Group0x0f381c[] =
{
	{R_M, C_PABSB,	D__Pq,	D__Qq,	D__NONE	,"pabsb",0x1c380f,3|C_GROUP_3_TYPE,MAKE_OP_RW_FLAG(OP_W,OP_R,0)}, //no prefix 
	{R_M, C_PABSB,	D__Vdq,	D__Wdq,	D__NONE	,"pabsb",0x1c380f66,4|C_GROUP_3_TYPE,MAKE_OP_RW_FLAG(OP_W,OP_R,0)}, //prefix 0x66
	{R_M, C_NULL,															}, //prefix 0xf2
	{R_M, C_NULL,		}, //prefix 0xf3
};

DIS_OPCODE_T Group0x0f381d[] =
{
	{R_M, C_PABSW,	D__Pq,	D__Qq,	D__NONE	,"pabsw",0x1d380f,3|C_GROUP_3_TYPE,MAKE_OP_RW_FLAG(OP_W,OP_R,0)}, //no prefix 
	{R_M, C_PABSW,	D__Vdq,	D__Wdq,	D__NONE	,"pabsw",0x1d380f66,4|C_GROUP_3_TYPE,MAKE_OP_RW_FLAG(OP_W,OP_R,0)}, //prefix 0x66
	{R_M, C_NULL,															}, //prefix 0xf2
	{R_M, C_NULL,		}, //prefix 0xf3
};

DIS_OPCODE_T Group0x0f381e[] =
{
	{R_M, C_PABSD,	D__Pq,	D__Qq,	D__NONE	,"pabsd",0x1e380f,3|C_GROUP_3_TYPE,MAKE_OP_RW_FLAG(OP_W,OP_R,0)}, //no prefix 
	{R_M, C_PABSD,	D__Vdq,	D__Wdq,	D__NONE	,"pabsd",0x1e380f66,4|C_GROUP_3_TYPE,MAKE_OP_RW_FLAG(OP_W,OP_R,0)}, //prefix 0x66
	{R_M, C_NULL,															}, //prefix 0xf2
	{R_M, C_NULL,		}, //prefix 0xf3
};


DIS_OPCODE_T Group0x0f3820[] =
{
	{R_M, C_NULL,	}, //no prefix 
	{R_M, C_PMOVSXBW,D__Vdq,D__Mq,	D__NONE	,"pmovsxbw"			,0x20380f66,4|C_GROUP_4_TYPE|(1<<16),MAKE_OP_RW_FLAG(OP_W,OP_R,0)}, //prefix 0x66
	{R_M, C_NULL,															}, //prefix 0xf2
	{R_M, C_NULL,		}, //prefix 0xf3
	//mod=11
	{R_M, C_NULL,	}, //no prefix 
	{R_M, C_PMOVSXBW,D__Vdq,D__Udq,	D__NONE	,"pmovsxbw"			,0x20380f66,4|C_GROUP_4_TYPE|(5<<16),MAKE_OP_RW_FLAG(OP_W,OP_R,0)}, //prefix 0x66
	{R_M, C_NULL,															}, //prefix 0xf2
	{R_M, C_NULL,	}, //prefix 0xf3
};

DIS_OPCODE_T Group0x0f3821[] =
{
	{R_M, C_NULL,	}, //no prefix 
	{R_M, C_PMOVSXBD,D__Vdq,D__Md,	D__NONE	,"pmovsxbd"			,0x21380f66,4|C_GROUP_4_TYPE|(1<<16),MAKE_OP_RW_FLAG(OP_W,OP_R,0)}, //prefix 0x66
	{R_M, C_NULL,															}, //prefix 0xf2
	{R_M, C_NULL,		}, //prefix 0xf3
	//mod=11
	{R_M, C_NULL,	}, //no prefix 
	{R_M, C_PMOVSXBW,D__Vdq,D__Udq,	D__NONE	,"pmovsxbd"			,0x21380f66,4|C_GROUP_4_TYPE|(5<<16),MAKE_OP_RW_FLAG(OP_W,OP_R,0)}, //prefix 0x66
	{R_M, C_NULL,															}, //prefix 0xf2
	{R_M, C_NULL,	}, //prefix 0xf3
};

DIS_OPCODE_T Group0x0f3822[] =
{
	{R_M, C_NULL,	}, //no prefix 
	{R_M, C_PMOVSXBQ,D__Vdq,D__Mw,	D__NONE	,"pmovsxbq"			,0x22380f66,4|C_GROUP_4_TYPE|(1<<16),MAKE_OP_RW_FLAG(OP_W,OP_R,0)}, //prefix 0x66
	{R_M, C_NULL,															}, //prefix 0xf2
	{R_M, C_NULL,		}, //prefix 0xf3
	//mod=11
	{R_M, C_NULL,	}, //no prefix 
	{R_M, C_PMOVSXBQ,D__Vdq,D__Udq,	D__NONE	,"pmovsxbq"			,0x22380f66,4|C_GROUP_4_TYPE|(5<<16),MAKE_OP_RW_FLAG(OP_W,OP_R,0)}, //prefix 0x66
	{R_M, C_NULL,															}, //prefix 0xf2
	{R_M, C_NULL,	}, //prefix 0xf3
};

DIS_OPCODE_T Group0x0f3823[] =
{
	{R_M, C_NULL,	}, //no prefix 
	{R_M, C_PMOVSXWD,D__Vdq,D__Mq,	D__NONE	,"pmovsxwd"			,0x23380f66,4|C_GROUP_4_TYPE|(1<<16),MAKE_OP_RW_FLAG(OP_W,OP_R,0)}, //prefix 0x66
	{R_M, C_NULL,															}, //prefix 0xf2
	{R_M, C_NULL,		}, //prefix 0xf3
	//mod=11
	{R_M, C_NULL,	}, //no prefix 
	{R_M, C_PMOVSXWD,D__Vdq,D__Udq,	D__NONE	,"pmovsxwd"			,0x23380f66,4|C_GROUP_4_TYPE|(5<<16),MAKE_OP_RW_FLAG(OP_W,OP_R,0)}, //prefix 0x66
	{R_M, C_NULL,															}, //prefix 0xf2
	{R_M, C_NULL,	}, //prefix 0xf3
};

DIS_OPCODE_T Group0x0f3824[] =
{
	{R_M, C_NULL,	}, //no prefix 
	{R_M, C_PMOVSXWQ,D__Vdq,D__Md,	D__NONE	,"pmovsxwq"			,0x24380f66,4|C_GROUP_4_TYPE|(1<<16),MAKE_OP_RW_FLAG(OP_W,OP_R,0)}, //prefix 0x66
	{R_M, C_NULL,															}, //prefix 0xf2
	{R_M, C_NULL,		}, //prefix 0xf3
	//mod=11
	{R_M, C_NULL,	}, //no prefix 
	{R_M, C_PMOVSXBQ,D__Vdq,D__Udq,	D__NONE	,"pmovsxwq"			,0x24380f66,4|C_GROUP_4_TYPE|(5<<16),MAKE_OP_RW_FLAG(OP_W,OP_R,0)}, //prefix 0x66
	{R_M, C_NULL,															}, //prefix 0xf2
	{R_M, C_NULL,	}, //prefix 0xf3
};

DIS_OPCODE_T Group0x0f3825[] =
{
	{R_M, C_NULL,	}, //no prefix 
	{R_M, C_PMOVSXDQ,D__Vdq,D__Mq,	D__NONE	,"pmovsxdq"			,0x25380f66,4|C_GROUP_4_TYPE|(1<<16),MAKE_OP_RW_FLAG(OP_W,OP_R,0)}, //prefix 0x66
	{R_M, C_NULL,															}, //prefix 0xf2
	{R_M, C_NULL,		}, //prefix 0xf3
	//mod=11
	{R_M, C_NULL,	}, //no prefix 
	{R_M, C_PMOVSXDQ,D__Vdq,D__Udq,	D__NONE	,"pmovsxdq"			,0x25380f66,4|C_GROUP_4_TYPE|(5<<16),MAKE_OP_RW_FLAG(OP_W,OP_R,0)}, //prefix 0x66
	{R_M, C_NULL,															}, //prefix 0xf2
	{R_M, C_NULL,	}, //prefix 0xf3
};

DIS_OPCODE_T Group0x0f3828[]=
{
	{R_M, C_NULL,	}, //no prefix 
	{R_M, C_PMULDQ,D__Vdq,D__Wdq,	D__NONE	,"pmuldq"			,0x28380f66,4|C_GROUP_3_TYPE,MAKE_OP_RW_FLAG(OP_RW,OP_R,0)}, //prefix 0x66
	{R_M, C_NULL,															}, //prefix 0xf2
	{R_M, C_NULL,		}, //prefix 0xf3
};

DIS_OPCODE_T Group0x0f3829[] =
{
	{R_M, C_NULL,	}, //no prefix 
	{R_M, C_PCMPEQQ,D__Vdq,D__Wdq,	D__NONE	,"pcmpeqq"			,0x29380f66,4|C_GROUP_3_TYPE,MAKE_OP_RW_FLAG(OP_RW,OP_R,0)}, //prefix 0x66
	{R_M, C_NULL,															}, //prefix 0xf2
	{R_M, C_NULL,		}, //prefix 0xf3
};

DIS_OPCODE_T Group0x0f382a[] =
{
	{R_M, C_NULL,	}, //no prefix 
	{R_M, C_MOVNTDQA,D__Vdq,D__Mdq,	D__NONE	,"movntdqa"			,0x2a380f66,4|C_GROUP_3_TYPE,MAKE_OP_RW_FLAG(OP_W,OP_R,0)}, //prefix 0x66
	{R_M, C_NULL,															}, //prefix 0xf2
	{R_M, C_NULL,		}, //prefix 0xf3
};

DIS_OPCODE_T Group0x0f382b[] =
{
	{R_M, C_NULL,	}, //no prefix 
	{R_M, C_PACKUSDW,D__Vdq,D__Wdq,	D__NONE	,"packusdw"			,0x2b380f66,4|C_GROUP_3_TYPE,MAKE_OP_RW_FLAG(OP_RW,OP_R,0)}, //prefix 0x66
	{R_M, C_NULL,															}, //prefix 0xf2
	{R_M, C_NULL,		}, //prefix 0xf3
};


DIS_OPCODE_T Group0x0f3830[] =
{
	{R_M, C_NULL,	}, //no prefix 
	{R_M, C_PMOVZXBW,D__Vdq,D__Mq,	D__NONE	,"pmovzxbw"			,0x30380f66,4|C_GROUP_4_TYPE|(1<<16),MAKE_OP_RW_FLAG(OP_W,OP_R,0)}, //prefix 0x66
	{R_M, C_NULL,															}, //prefix 0xf2
	{R_M, C_NULL,		}, //prefix 0xf3
	//mod=11
	{R_M, C_NULL,	}, //no prefix 
	{R_M, C_PMOVZXBW,D__Vdq,D__Udq,	D__NONE	,"pmovzxbw"			,0x30380f66,4|C_GROUP_4_TYPE|(5<<16),MAKE_OP_RW_FLAG(OP_W,OP_R,0)}, //prefix 0x66
	{R_M, C_NULL,															}, //prefix 0xf2
	{R_M, C_NULL,	}, //prefix 0xf3
};

DIS_OPCODE_T Group0x0f3831[] =
{
	{R_M, C_NULL,	}, //no prefix 
	{R_M, C_PMOVZXBD,D__Vdq,D__Md,	D__NONE	,"pmovzxbd"			,0x31380f66,4|C_GROUP_4_TYPE|(1<<16),MAKE_OP_RW_FLAG(OP_W,OP_R,0)}, //prefix 0x66
	{R_M, C_NULL,															}, //prefix 0xf2
	{R_M, C_NULL,		}, //prefix 0xf3
	//mod=11
	{R_M, C_NULL,	}, //no prefix 
	{R_M, C_PMOVZXBW,D__Vdq,D__Udq,	D__NONE	,"pmovzxbd"			,0x31380f66,4|C_GROUP_4_TYPE|(5<<16),MAKE_OP_RW_FLAG(OP_W,OP_R,0)}, //prefix 0x66
	{R_M, C_NULL,															}, //prefix 0xf2
	{R_M, C_NULL,	}, //prefix 0xf3
};

DIS_OPCODE_T Group0x0f3832[] =
{
	{R_M, C_NULL,	}, //no prefix 
	{R_M, C_PMOVZXBQ,D__Vdq,D__Mw,	D__NONE	,"pmovzxbq"			,0x32380f66,4|C_GROUP_4_TYPE|(1<<16),MAKE_OP_RW_FLAG(OP_W,OP_R,0)}, //prefix 0x66
	{R_M, C_NULL,															}, //prefix 0xf2
	{R_M, C_NULL,		}, //prefix 0xf3
	//mod=11
	{R_M, C_NULL,	}, //no prefix 
	{R_M, C_PMOVZXBQ,D__Vdq,D__Udq,	D__NONE	,"pmovzxbq"			,0x32380f66,4|C_GROUP_4_TYPE|(5<<16),MAKE_OP_RW_FLAG(OP_W,OP_R,0)}, //prefix 0x66
	{R_M, C_NULL,															}, //prefix 0xf2
	{R_M, C_NULL,	}, //prefix 0xf3
};

DIS_OPCODE_T Group0x0f3833[] =
{
	{R_M, C_NULL,	}, //no prefix 
	{R_M, C_PMOVZXWD,D__Vdq,D__Mq,	D__NONE	,"pmovzxwd"			,0x33380f66,4|C_GROUP_4_TYPE|(1<<16),MAKE_OP_RW_FLAG(OP_W,OP_R,0)}, //prefix 0x66
	{R_M, C_NULL,															}, //prefix 0xf2
	{R_M, C_NULL,		}, //prefix 0xf3
	//mod=11
	{R_M, C_NULL,	}, //no prefix 
	{R_M, C_PMOVZXWD,D__Vdq,D__Udq,	D__NONE	,"pmovzxwd"			,0x33380f66,4|C_GROUP_4_TYPE|(5<<16),MAKE_OP_RW_FLAG(OP_W,OP_R,0)}, //prefix 0x66
	{R_M, C_NULL,															}, //prefix 0xf2
	{R_M, C_NULL,	}, //prefix 0xf3
};

DIS_OPCODE_T Group0x0f3834[] =
{
	{R_M, C_NULL,	}, //no prefix 
	{R_M, C_PMOVZXWQ,D__Vdq,D__Md,	D__NONE	,"pmovzxwq"			,0x34380f66,4|C_GROUP_4_TYPE|(1<<16),MAKE_OP_RW_FLAG(OP_W,OP_R,0)}, //prefix 0x66
	{R_M, C_NULL,															}, //prefix 0xf2
	{R_M, C_NULL,		}, //prefix 0xf3
	//mod=11
	{R_M, C_NULL,	}, //no prefix 
	{R_M, C_PMOVZXBQ,D__Vdq,D__Udq,	D__NONE	,"pmovzxwq"			,0x34380f66,4|C_GROUP_4_TYPE|(5<<16),MAKE_OP_RW_FLAG(OP_W,OP_R,0)}, //prefix 0x66
	{R_M, C_NULL,															}, //prefix 0xf2
	{R_M, C_NULL,	}, //prefix 0xf3
};

DIS_OPCODE_T Group0x0f3835[] =
{
	{R_M, C_NULL,	}, //no prefix 
	{R_M, C_PMOVZXDQ,D__Vdq,D__Mq,	D__NONE	,"pmovzxdq"			,0x35380f66,4|C_GROUP_4_TYPE|(1<<16),MAKE_OP_RW_FLAG(OP_W,OP_R,0)}, //prefix 0x66
	{R_M, C_NULL,															}, //prefix 0xf2
	{R_M, C_NULL,		}, //prefix 0xf3
	//mod=11
	{R_M, C_NULL,	}, //no prefix 
	{R_M, C_PMOVZXDQ,D__Vdq,D__Udq,	D__NONE	,"pmovzxdq"			,0x35380f66,4|C_GROUP_4_TYPE|(5<<16),MAKE_OP_RW_FLAG(OP_W,OP_R,0)}, //prefix 0x66
	{R_M, C_NULL,															}, //prefix 0xf2
	{R_M, C_NULL,	}, //prefix 0xf3
};

DIS_OPCODE_T Group0x0f3837[] =
{
	{R_M, C_NULL,	}, //no prefix 
	{R_M, C_PCMPGTQ,D__Vdq,D__Wdq,	D__NONE	,"pcmpgtq"			,0x37380f66,4|C_GROUP_3_TYPE,MAKE_OP_RW_FLAG(OP_RW,OP_R,0)}, //prefix 0x66
	{R_M, C_NULL,															}, //prefix 0xf2
	{R_M, C_NULL,		}, //prefix 
};

DIS_OPCODE_T Group0x0f3838[] =
{
	{R_M, C_NULL,	}, //no prefix 
	{R_M, C_PMINSB,D__Vdq,D__Wdq,	D__NONE	,"pminsb"			,0x38380f66,4|C_GROUP_3_TYPE,MAKE_OP_RW_FLAG(OP_RW,OP_R,0)}, //prefix 0x66
	{R_M, C_NULL,															}, //prefix 0xf2
	{R_M, C_NULL,		}, //prefix 0xf3
};

DIS_OPCODE_T Group0x0f3839[] =
{
	{R_M, C_NULL,	}, //no prefix 
	{R_M, C_PMINSD,D__Vdq,D__Wdq,	D__NONE	,"pminsd"			,0x39380f66,4|C_GROUP_3_TYPE,MAKE_OP_RW_FLAG(OP_RW,OP_R,0)}, //prefix 0x66
	{R_M, C_NULL,															}, //prefix 0xf2
	{R_M, C_NULL,		}, //prefix 0xf3
};
DIS_OPCODE_T Group0x0f383a[] =
{
	{R_M, C_NULL,	}, //no prefix 
	{R_M, C_PMINUW,D__Vdq,D__Wdq,	D__NONE	,"pminuw"			,0x3a380f66,4|C_GROUP_3_TYPE,MAKE_OP_RW_FLAG(OP_RW,OP_R,0)}, //prefix 0x66
	{R_M, C_NULL,															}, //prefix 0xf2
	{R_M, C_NULL,		}, //prefix 0xf3
};
DIS_OPCODE_T Group0x0f383b[] =
{
	{R_M, C_NULL,	}, //no prefix 
	{R_M, C_PMINUD,D__Vdq,D__Wdq,	D__NONE	,"pminud"			,0x3b380f66,4|C_GROUP_3_TYPE,MAKE_OP_RW_FLAG(OP_RW,OP_R,0)}, //prefix 0x66
	{R_M, C_NULL,															}, //prefix 0xf2
	{R_M, C_NULL,		}, //prefix 0xf3
};
DIS_OPCODE_T Group0x0f383c[] =
{
	{R_M, C_NULL,	}, //no prefix 
	{R_M, C_PMAXSB,D__Vdq,D__Wdq,	D__NONE	,"pmaxsb"			,0x3c380f66,4|C_GROUP_3_TYPE,MAKE_OP_RW_FLAG(OP_RW,OP_R,0)}, //prefix 0x66
	{R_M, C_NULL,															}, //prefix 0xf2
	{R_M, C_NULL,		}, //prefix 0xf3
};
DIS_OPCODE_T Group0x0f383d[] =
{
	{R_M, C_NULL,	}, //no prefix 
	{R_M, C_PMAXSD,D__Vdq,D__Wdq,	D__NONE	,"pmaxsd"						,0x3d380f66,4|C_GROUP_3_TYPE,MAKE_OP_RW_FLAG(OP_RW,OP_R,0)}, //prefix 0x66
	{R_M, C_NULL,															}, //prefix 0xf2
	{R_M, C_NULL,		}, //prefix 0xf3
};
DIS_OPCODE_T Group0x0f383e[] =
{
	{R_M, C_NULL,	}, //no prefix 
	{R_M, C_PMAXUW,D__Vdq,D__Wdq,	D__NONE	,"pmaxuw"			,0x3e380f66,4|C_GROUP_3_TYPE,MAKE_OP_RW_FLAG(OP_RW,OP_R,0)}, //prefix 0x66
	{R_M, C_NULL,															}, //prefix 0xf2
	{R_M, C_NULL,		}, //prefix 0xf3
};
DIS_OPCODE_T Group0x0f383f[] =
{
	{R_M, C_NULL,	}, //no prefix 
	{R_M, C_PMAXUD,D__Vdq,D__Wdq,	D__NONE	,"pmaxud"			,0x3f380f66,4|C_GROUP_3_TYPE,MAKE_OP_RW_FLAG(OP_RW,OP_R,0)}, //prefix 0x66
	{R_M, C_NULL,															}, //prefix 0xf2
	{R_M, C_NULL,		}, //prefix 0xf3
};

DIS_OPCODE_T Group0x0f3840[] =
{
	{R_M, C_NULL,	}, //no prefix 
	{R_M, C_PMULLD,D__Vdq,D__Wdq,	D__NONE	,"pmulld"			,0x40380f66,4|C_GROUP_3_TYPE,MAKE_OP_RW_FLAG(OP_RW,OP_R,0)}, //prefix 0x66
	{R_M, C_NULL,															}, //prefix 0xf2
	{R_M, C_NULL,		}, //prefix 0xf3
};

DIS_OPCODE_T Group0x0f3841[] =
{
	{R_M, C_NULL,	}, //no prefix 
	{R_M, C_PHMINPOSUW,	D__Vdq,	D__Wdq,	D__NONE,	"phminposuw"			,0x41380f66,4|C_GROUP_3_TYPE,MAKE_OP_RW_FLAG(OP_W,OP_R,0)}, //prefix 0x66
	{R_M, C_NULL,															}, //prefix 0xf2
	{R_M, C_NULL,		}, //prefix 0xf3
};

DIS_OPCODE_T Group0x0f3880[] =
{
	{R_M, C_NULL,	}, //no prefix 
	{R_M, C_INVEPT,D__Gy,D__Mdq,	D__NONE	,"invept"			,0x80380f66,4|C_GROUP_4_TYPE|(1<<16)}, //prefix 0x66
	{R_M, C_NULL,															}, //prefix 0xf2
	{R_M, C_NULL,		}, //prefix 0xf3
	//mod=11
	{R_M, C_NULL,	}, //no prefix 
	{R_M, C_NULL,	}, //prefix 0x66
	{R_M, C_NULL,		}, //prefix 0xf2
	{R_M, C_NULL,		}, //prefix 0xf3
};

DIS_OPCODE_T Group0x0f3881[] =
{
	{R_M, C_NULL,	}, //no prefix 
	{R_M, C_INVVPID,	D__Gy,	D__Mdq,	D__NONE,	"invvpid"			,0x81380f66,4|C_GROUP_4_TYPE|(1<<16)}, //prefix 0x66
	{R_M, C_NULL,															}, //prefix 0xf2
	{R_M, C_NULL,		}, //prefix 0xf3
	//mod=11
	{R_M, C_NULL,	}, //no prefix 
	{R_M, C_NULL,	}, //prefix 0x66
	{R_M, C_NULL,		}, //prefix 0xf2
	{R_M, C_NULL,		}, //prefix 0xf3
};

DIS_OPCODE_T Group0x0f38db[] =
{
	{R_M, C_NULL,	}, //no prefix 
	{R_M, C_AESIMC,	D__Vdq,	D__Wdq,	D__NONE,	"aesimc"	,0xdb380f66,4|C_GROUP_3_TYPE,MAKE_OP_RW_FLAG(OP_W,OP_R,0)}, //prefix 0x66
	{R_M, C_NULL,															}, //prefix 0xf2
	{R_M, C_NULL,		}, //prefix 0xf3
};

DIS_OPCODE_T Group0x0f38dc[] =
{
	{R_M, C_NULL,	}, //no prefix 
	{R_M, C_AESENC,	D__Vdq,	D__Wdq,	D__NONE,	"aesenc"	,0xdc380f66,4|C_GROUP_3_TYPE,MAKE_OP_RW_FLAG(OP_RW,OP_R,0)}, //prefix 0x66
	{R_M, C_NULL,															}, //prefix 0xf2
	{R_M, C_NULL,		}, //prefix 0xf3
};

DIS_OPCODE_T Group0x0f38dd[] =
{
	{R_M, C_NULL,	}, //no prefix 
	{R_M, C_AESENCLAST,	D__Vdq,	D__Wdq,	D__NONE,	"aesenclast",0xdd380f66,4|C_GROUP_3_TYPE,MAKE_OP_RW_FLAG(OP_RW,OP_R,0)}, //prefix 0x66
	{R_M, C_NULL,															}, //prefix 0xf2
	{R_M, C_NULL,		}, //prefix 0xf3
};

DIS_OPCODE_T Group0x0f38de[] =
{
	{R_M, C_NULL,	}, //no prefix 
	{R_M, C_AESDEC,	D__Vdq,	D__Wdq,	D__NONE,	"aesdec"	,0xde380f66,4|C_GROUP_3_TYPE,MAKE_OP_RW_FLAG(OP_RW,OP_R,0)}, //prefix 0x66
	{R_M, C_NULL,															}, //prefix 0xf2
	{R_M, C_NULL,		}, //prefix 0xf3
};

DIS_OPCODE_T Group0x0f38df[] =
{
	{R_M, C_NULL,	}, //no prefix 
	{R_M, C_AESDECLAST,	D__Vdq,	D__Wdq,	D__NONE,	"aesdeclast",0xdf380f66,4|C_GROUP_3_TYPE,MAKE_OP_RW_FLAG(OP_RW,OP_R,0)}, //prefix 0x66
	{R_M, C_NULL,															}, //prefix 0xf2
	{R_M, C_NULL,		}, //prefix 0xf3
};

DIS_OPCODE_T Group0x0f38f0[] =
{
	{R_M, C_MOVBE,D__Gy,D__My,D__NONE,"movbe"				,0xf0380f,3|C_GROUP_4_TYPE|(0<<16),MAKE_OP_RW_FLAG(OP_W,OP_R,0)}, //no prefix 
	{R_M, C_MOVBE,D__Gw,D__Mw,D__NONE,"movbe"				,0xf0380f,3|C_GROUP_4_TYPE|(1<<16),MAKE_OP_RW_FLAG(OP_W,OP_R,0)}, //prefix 0x66
	{R_M, C_CRC32,D__Gy,D__Eb,	D__NONE	,"crc32"			,0xf0380ff2,4|C_GROUP_4_TYPE|(2<<16),MAKE_OP_RW_FLAG(OP_RW,OP_R,0)}, //prefix 0xf2
	{R_M, C_NULL,		}, //prefix 0xf3
	//mod=11
	{R_M, C_NULL,	}, //no prefix 
	{R_M, C_NULL,	}, //prefix 0x66
	{R_M, C_CRC32,D__Gy,D__Eb,	D__NONE	,"crc32"			,0xf0380ff2,4|C_GROUP_4_TYPE|(6<<16),MAKE_OP_RW_FLAG(OP_RW,OP_R,0)}, //prefix 0xf2
	{R_M, C_NULL,		}, //prefix 0xf3
};

DIS_OPCODE_T Group0x0f38f1[] =
{
	{R_M, C_MOVBE,D__My,D__Gy,D__NONE,"movbe",0xf1380f,3|C_GROUP_4_TYPE|(0<<16),MAKE_OP_RW_FLAG(OP_W,OP_R,0)}, //no prefix 
	{R_M, C_MOVBE,D__Mw,D__Gw,D__NONE,"movbe"				,0xf1380f,3|C_GROUP_4_TYPE|(1<<16),MAKE_OP_RW_FLAG(OP_W,OP_R,0)}, //prefix 0x66
	{R_M, C_CRC32,	D__Gy,	D__Ey,	D__NONE	,"crc32"			,0xf1380ff2,4|C_GROUP_4_TYPE|(2<<16),MAKE_OP_RW_FLAG(OP_RW,OP_R,0)}, //prefix 0xf2
	{R_M, C_NULL,												}, //prefix 0xf3
	//mod=11
	{R_M, C_NULL,												}, //no prefix 
	{R_M, C_NULL,												}, //prefix 0x66
	{R_M, C_CRC32,	D__Gy,	D__Ev,	D__NONE	,"crc32"			,0xf1380ff2,4|C_GROUP_4_TYPE|(6<<16),MAKE_OP_RW_FLAG(OP_RW,OP_R,0)}, //prefix 0xf2
	{R_M, C_NULL,												}, //prefix 0xf3
};


DIS_OPCODE_T Group0x0f38[] =
{
	{R_M,	C_GRP3,D__Pq,			D__Qq,		D__NONE,(char*)Group0x0f3800,0x00380f,3},//0f 38 00
	{R_M,	C_GRP3,D__Pq,			D__Qq,		D__NONE,(char*)Group0x0f3801,0x01380f,3},//0f 38 01
	{R_M,	C_GRP3,D__Pq,			D__Qq,		D__NONE,(char*)Group0x0f3802,0x02380f,3},//0f 38 02
	{R_M,	C_GRP3,D__Pq,			D__Qq,		D__NONE,(char*)Group0x0f3803,0x03380f,3},//0f 38 03
	{R_M,	C_GRP3,D__Pq,			D__Qq,		D__NONE,(char*)Group0x0f3804,0x04380f,3},//0f 38 04
	{R_M,	C_GRP3,D__Pq,			D__Qq,		D__NONE,(char*)Group0x0f3805,0x05380f,3},//0f 38 05
	{R_M,	C_GRP3,D__Pq,			D__Qq,		D__NONE,(char*)Group0x0f3806,0x06380f,3},//0f 38 06
	{R_M,	C_GRP3,D__Pq,			D__Qq,		D__NONE,(char*)Group0x0f3807,0x07380f,3},//0f 38 07

	{R_M,	C_GRP3,D__Pq,			D__Qq,		D__NONE,(char*)Group0x0f3808,0x08380f,3},//0f 38 08
	{R_M,	C_GRP3,D__Pq,			D__Qq,		D__NONE,(char*)Group0x0f3809,0x09380f,3},//0f 38 09
	{R_M,	C_GRP3,D__Pq,			D__Qq,		D__NONE,(char*)Group0x0f380a,0x0a380f,3},//0f 38 0a
	{R_M,	C_GRP3,D__Pq,			D__Qq,		D__NONE,(char*)Group0x0f380b,0x0b380f,3},//0f 38 0b
	{R_M,	C_NULL,	D__NONE,		D__NONE,	D__NONE,					},//0f 38 0c
	{R_M,	C_NULL,	D__NONE,		D__NONE,	D__NONE,					},//0f 38 0d
	{R_M,	C_NULL,	D__NONE,		D__NONE,	D__NONE,					},//0f 38 0e
	{R_M,	C_NULL,	D__NONE,		D__NONE,	D__NONE,					},//0f 38 0f

	{R_M,	C_GRP3,	D__NONE,		D__NONE,	D__NONE,(char*)Group0x0f3810,0x10380f,3},//0f 38 10
	{R_M,	C_NULL,	D__NONE,		D__NONE,	D__NONE,					},//0f 38 11
	{R_M,	C_NULL,	D__NONE,		D__NONE,	D__NONE,					},//0f 38 12
	{R_M,	C_NULL,	D__NONE,		D__NONE,	D__NONE,					},//0f 38 13
	{R_M,	C_GRP3,	D__NONE,		D__NONE,	D__NONE,(char*)Group0x0f3814,0x14380f,3},//0f 38 14
	{R_M,	C_GRP3,	D__NONE,		D__NONE,	D__NONE,(char*)Group0x0f3815,0x15380f,3},//0f 38 15
	{R_M,	C_NULL,	D__NONE,		D__NONE,	D__NONE,					},//0f 38 16
	{R_M,	C_GRP3,	D__NONE,		D__NONE,	D__NONE,(char*)Group0x0f3817,0x17380f,3},//0f 38 17

	{R_M,	C_NULL,	D__NONE,		D__NONE,	D__NONE,					},//0f 38 18
	{R_M,	C_NULL,	D__NONE,		D__NONE,	D__NONE,					},//0f 38 19
	{R_M,	C_NULL,	D__NONE,		D__NONE,	D__NONE,					},//0f 38 1a
	{R_M,	C_NULL,	D__NONE,		D__NONE,	D__NONE,					},//0f 38 1b
	{R_M,	C_GRP3,	D__Pq,			D__Qq,		D__NONE,(char*)Group0x0f381c,0x1c380f,3},//0f 38 1c
	{R_M,	C_GRP3,	D__Pq,			D__Qq,		D__NONE,(char*)Group0x0f381d,0x1d380f,3},//0f 38 1d
	{R_M,	C_GRP3,	D__Pq,			D__Qq,		D__NONE,(char*)Group0x0f381e,0x1e380f,3},//0f 38 1e
	{R_M,	C_NULL,	D__NONE,		D__NONE,	D__NONE,					},//0f 38 1f

	{R_M,	C_GRP4,	D__NONE,		D__NONE,	D__NONE,(char*)Group0x0f3820,0x20380f,3},//0f 38 20
	{R_M,	C_GRP4,	D__NONE,		D__NONE,	D__NONE,(char*)Group0x0f3821,0x21380f,3},//0f 38 21
	{R_M,	C_GRP4,	D__NONE,		D__NONE,	D__NONE,(char*)Group0x0f3822,0x22380f,3},//0f 38 22
	{R_M,	C_GRP4,	D__NONE,		D__NONE,	D__NONE,(char*)Group0x0f3823,0x23380f,3},//0f 38 23
	{R_M,	C_GRP4,	D__NONE,		D__NONE,	D__NONE,(char*)Group0x0f3824,0x24380f,3},//0f 38 24
	{R_M,	C_GRP4,	D__NONE,		D__NONE,	D__NONE,(char*)Group0x0f3825,0x25380f,3},//0f 38 25
	{R_M,	C_NULL,	D__NONE,		D__NONE,	D__NONE,					},//0f 38 26
	{R_M,	C_NULL,	D__NONE,		D__NONE,	D__NONE,					},//0f 38 27

	{R_M,	C_GRP3,	D__NONE,		D__NONE,	D__NONE,(char*)Group0x0f3828,0x28380f,3},//0f 38 28
	{R_M,	C_GRP3,	D__NONE,		D__NONE,	D__NONE,(char*)Group0x0f3829,0x29380f,3},//0f 38 29
	{R_M,	C_GRP3,	D__NONE,		D__NONE,	D__NONE,(char*)Group0x0f382a,0x2a380f,3},//0f 38 2a
	{R_M,	C_GRP3,	D__NONE,		D__NONE,	D__NONE,(char*)Group0x0f382b,0x2b380f,3},//0f 38 2b
	{R_M,	C_NULL,	D__NONE,		D__NONE,	D__NONE,					},//0f 38 2c
	{R_M,	C_NULL,	D__NONE,		D__NONE,	D__NONE,					},//0f 38 2d
	{R_M,	C_NULL,	D__NONE,		D__NONE,	D__NONE,					},//0f 38 2e
	{R_M,	C_NULL,	D__NONE,		D__NONE,	D__NONE,					},//0f 38 2f

	{R_M,	C_GRP4,	D__NONE,		D__NONE,	D__NONE,(char*)Group0x0f3830,0x30380f,3},//0f 38 30
	{R_M,	C_GRP4,	D__NONE,		D__NONE,	D__NONE,(char*)Group0x0f3831,0x31380f,3},//0f 38 31
	{R_M,	C_GRP4,	D__NONE,		D__NONE,	D__NONE,(char*)Group0x0f3832,0x32380f,3},//0f 38 32
	{R_M,	C_GRP4,	D__NONE,		D__NONE,	D__NONE,(char*)Group0x0f3833,0x33380f,3},//0f 38 33
	{R_M,	C_GRP4,	D__NONE,		D__NONE,	D__NONE,(char*)Group0x0f3834,0x34380f,3},//0f 38 34
	{R_M,	C_GRP4,	D__NONE,		D__NONE,	D__NONE,(char*)Group0x0f3835,0x35380f,3},//0f 38 35
	{R_M,	C_NULL,	D__NONE,		D__NONE,	D__NONE,					},//0f 38 36
	{R_M,	C_GRP3,	D__NONE,		D__NONE,	D__NONE,(char*)Group0x0f3837,0x37380f,3},//0f 38 37

	{R_M,	C_GRP3,	D__NONE,		D__NONE,	D__NONE,(char*)Group0x0f3838,0x38380f,3},//0f 38 38
	{R_M,	C_GRP3,	D__NONE,		D__NONE,	D__NONE,(char*)Group0x0f3839,0x39380f,3},//0f 38 39
	{R_M,	C_GRP3,	D__NONE,		D__NONE,	D__NONE,(char*)Group0x0f383a,0x3a380f,3},//0f 38 3a
	{R_M,	C_GRP3,	D__NONE,		D__NONE,	D__NONE,(char*)Group0x0f383b,0x3b380f,3},//0f 38 3b
	{R_M,	C_GRP3,	D__NONE,		D__NONE,	D__NONE,(char*)Group0x0f383c,0x3c380f,3},//0f 38 3c
	{R_M,	C_GRP3,	D__NONE,		D__NONE,	D__NONE,(char*)Group0x0f383d,0x3d380f,3},//0f 38 3d
	{R_M,	C_GRP3,	D__NONE,		D__NONE,	D__NONE,(char*)Group0x0f383e,0x3e380f,3},//0f 38 3e
	{R_M,	C_GRP3,	D__NONE,		D__NONE,	D__NONE,(char*)Group0x0f383f,0x3f380f,3},//0f 38 3f

	{R_M,	C_GRP3,	D__NONE,		D__NONE,	D__NONE,(char*)Group0x0f3840,0x40380f,3},//0f 38 40
	{R_M,	C_GRP3,	D__NONE,		D__NONE,	D__NONE,(char*)Group0x0f3841,0x41380f,3},//0f 38 41
	{R_M,	C_NULL,	D__NONE,		D__NONE,	D__NONE,					},//0f 38 42
	{R_M,	C_NULL,	D__NONE,		D__NONE,	D__NONE,					},//0f 38 43
	{R_M,	C_NULL,	D__NONE,		D__NONE,	D__NONE,					},//0f 38 44
	{R_M,	C_NULL,	D__NONE,		D__NONE,	D__NONE,					},//0f 38 45
	{R_M,	C_NULL,	D__NONE,		D__NONE,	D__NONE,					},//0f 38 46
	{R_M,	C_NULL,	D__NONE,		D__NONE,	D__NONE,					},//0f 38 47

	{R_M,	C_NULL,	D__NONE,		D__NONE,	D__NONE,					},//0f 38 48
	{R_M,	C_NULL,	D__NONE,		D__NONE,	D__NONE,					},//0f 38 49
	{R_M,	C_NULL,	D__NONE,		D__NONE,	D__NONE,					},//0f 38 4a
	{R_M,	C_NULL,	D__NONE,		D__NONE,	D__NONE,					},//0f 38 4b
	{R_M,	C_NULL,	D__NONE,		D__NONE,	D__NONE,					},//0f 38 4c
	{R_M,	C_NULL,	D__NONE,		D__NONE,	D__NONE,					},//0f 38 4d
	{R_M,	C_NULL,	D__NONE,		D__NONE,	D__NONE,					},//0f 38 4e
	{R_M,	C_NULL,	D__NONE,		D__NONE,	D__NONE,					},//0f 38 4f

	{R_M,	C_NULL,	D__NONE,		D__NONE,	D__NONE,					},//0f 38 50
	{R_M,	C_NULL,	D__NONE,		D__NONE,	D__NONE,					},//0f 38 51
	{R_M,	C_NULL,	D__NONE,		D__NONE,	D__NONE,					},//0f 38 52
	{R_M,	C_NULL,	D__NONE,		D__NONE,	D__NONE,					},//0f 38 53
	{R_M,	C_NULL,	D__NONE,		D__NONE,	D__NONE,					},//0f 38 54
	{R_M,	C_NULL,	D__NONE,		D__NONE,	D__NONE,					},//0f 38 55
	{R_M,	C_NULL,	D__NONE,		D__NONE,	D__NONE,					},//0f 38 56
	{R_M,	C_NULL,	D__NONE,		D__NONE,	D__NONE,					},//0f 38 57

	{R_M,	C_NULL,	D__NONE,		D__NONE,	D__NONE,					},//0f 38 58
	{R_M,	C_NULL,	D__NONE,		D__NONE,	D__NONE,					},//0f 38 59
	{R_M,	C_NULL,	D__NONE,		D__NONE,	D__NONE,					},//0f 38 5a
	{R_M,	C_NULL,	D__NONE,		D__NONE,	D__NONE,					},//0f 38 5b
	{R_M,	C_NULL,	D__NONE,		D__NONE,	D__NONE,					},//0f 38 5c
	{R_M,	C_NULL,	D__NONE,		D__NONE,	D__NONE,					},//0f 38 5d
	{R_M,	C_NULL,	D__NONE,		D__NONE,	D__NONE,					},//0f 38 5e
	{R_M,	C_NULL,	D__NONE,		D__NONE,	D__NONE,					},//0f 38 5f

	{R_M,	C_NULL,	D__NONE,		D__NONE,	D__NONE,					},//0f 38 60
	{R_M,	C_NULL,	D__NONE,		D__NONE,	D__NONE,					},//0f 38 61
	{R_M,	C_NULL,	D__NONE,		D__NONE,	D__NONE,					},//0f 38 62
	{R_M,	C_NULL,	D__NONE,		D__NONE,	D__NONE,					},//0f 38 63
	{R_M,	C_NULL,	D__NONE,		D__NONE,	D__NONE,					},//0f 38 64
	{R_M,	C_NULL,	D__NONE,		D__NONE,	D__NONE,					},//0f 38 65
	{R_M,	C_NULL,	D__NONE,		D__NONE,	D__NONE,					},//0f 38 66
	{R_M,	C_NULL,	D__NONE,		D__NONE,	D__NONE,					},//0f 38 67

	{R_M,	C_NULL,	D__NONE,		D__NONE,	D__NONE,					},//0f 38 68
	{R_M,	C_NULL,	D__NONE,		D__NONE,	D__NONE,					},//0f 38 69
	{R_M,	C_NULL,	D__NONE,		D__NONE,	D__NONE,					},//0f 38 6a
	{R_M,	C_NULL,	D__NONE,		D__NONE,	D__NONE,					},//0f 38 6b
	{R_M,	C_NULL,	D__NONE,		D__NONE,	D__NONE,					},//0f 38 6c
	{R_M,	C_NULL,	D__NONE,		D__NONE,	D__NONE,					},//0f 38 6d
	{R_M,	C_NULL,	D__NONE,		D__NONE,	D__NONE,					},//0f 38 6e
	{R_M,	C_NULL,	D__NONE,		D__NONE,	D__NONE,					},//0f 38 6f
	{R_M,	C_NULL,	D__NONE,		D__NONE,	D__NONE,					},//0f 38 70
	{R_M,	C_NULL,	D__NONE,		D__NONE,	D__NONE,					},//0f 38 71
	{R_M,	C_NULL,	D__NONE,		D__NONE,	D__NONE,					},//0f 38 72
	{R_M,	C_NULL,	D__NONE,		D__NONE,	D__NONE,					},//0f 38 73
	{R_M,	C_NULL,	D__NONE,		D__NONE,	D__NONE,					},//0f 38 74
	{R_M,	C_NULL,	D__NONE,		D__NONE,	D__NONE,					},//0f 38 75
	{R_M,	C_NULL,	D__NONE,		D__NONE,	D__NONE,					},//0f 38 76
	{R_M,	C_NULL,	D__NONE,		D__NONE,	D__NONE,					},//0f 38 77
	{R_M,	C_NULL,	D__NONE,		D__NONE,	D__NONE,					},//0f 38 78
	{R_M,	C_NULL,	D__NONE,		D__NONE,	D__NONE,					},//0f 38 79
	{R_M,	C_NULL,	D__NONE,		D__NONE,	D__NONE,					},//0f 38 7a
	{R_M,	C_NULL,	D__NONE,		D__NONE,	D__NONE,					},//0f 38 7b
	{R_M,	C_NULL,	D__NONE,		D__NONE,	D__NONE,					},//0f 38 7c
	{R_M,	C_NULL,	D__NONE,		D__NONE,	D__NONE,					},//0f 38 7d
	{R_M,	C_NULL,	D__NONE,		D__NONE,	D__NONE,					},//0f 38 7e
	{R_M,	C_NULL,	D__NONE,		D__NONE,	D__NONE,					},//0f 38 7f

	{R_M,	C_GRP4,	D__NONE,		D__NONE,	D__NONE,(char*)Group0x0f3880					,0x80380f,3},//0f 38 80
	{R_M,	C_GRP4,	D__NONE,		D__NONE,	D__NONE,(char*)Group0x0f3881					,0x81380f,3},//0f 38 81
	{R_M,	C_NULL,	D__NONE,		D__NONE,	D__NONE,					},//0f 38 82
	{R_M,	C_NULL,	D__NONE,		D__NONE,	D__NONE,					},//0f 38 83
	{R_M,	C_NULL,	D__NONE,		D__NONE,	D__NONE,					},//0f 38 84
	{R_M,	C_NULL,	D__NONE,		D__NONE,	D__NONE,					},//0f 38 85
	{R_M,	C_NULL,	D__NONE,		D__NONE,	D__NONE,					},//0f 38 86
	{R_M,	C_NULL,	D__NONE,		D__NONE,	D__NONE,					},//0f 38 87
	{R_M,	C_NULL,	D__NONE,		D__NONE,	D__NONE,					},//0f 38 88
	{R_M,	C_NULL,	D__NONE,		D__NONE,	D__NONE,					},//0f 38 89
	{R_M,	C_NULL,	D__NONE,		D__NONE,	D__NONE,					},//0f 38 8a
	{R_M,	C_NULL,	D__NONE,		D__NONE,	D__NONE,					},//0f 38 8b
	{R_M,	C_NULL,	D__NONE,		D__NONE,	D__NONE,					},//0f 38 8c
	{R_M,	C_NULL,	D__NONE,		D__NONE,	D__NONE,					},//0f 38 8d
	{R_M,	C_NULL,	D__NONE,		D__NONE,	D__NONE,					},//0f 38 8e
	{R_M,	C_NULL,	D__NONE,		D__NONE,	D__NONE,					},//0f 38 8f
	{R_M,	C_NULL,	D__NONE,		D__NONE,	D__NONE,					},//0f 38 90
	{R_M,	C_NULL,	D__NONE,		D__NONE,	D__NONE,					},//0f 38 91
	{R_M,	C_NULL,	D__NONE,		D__NONE,	D__NONE,					},//0f 38 92
	{R_M,	C_NULL,	D__NONE,		D__NONE,	D__NONE,					},//0f 38 93
	{R_M,	C_NULL,	D__NONE,		D__NONE,	D__NONE,					},//0f 38 94
	{R_M,	C_NULL,	D__NONE,		D__NONE,	D__NONE,					},//0f 38 95
	{R_M,	C_NULL,	D__NONE,		D__NONE,	D__NONE,					},//0f 38 96
	{R_M,	C_NULL,	D__NONE,		D__NONE,	D__NONE,					},//0f 38 97
	{R_M,	C_NULL,	D__NONE,		D__NONE,	D__NONE,					},//0f 38 98
	{R_M,	C_NULL,	D__NONE,		D__NONE,	D__NONE,					},//0f 38 99
	{R_M,	C_NULL,	D__NONE,		D__NONE,	D__NONE,					},//0f 38 9a
	{R_M,	C_NULL,	D__NONE,		D__NONE,	D__NONE,					},//0f 38 9b
	{R_M,	C_NULL,	D__NONE,		D__NONE,	D__NONE,					},//0f 38 9c
	{R_M,	C_NULL,	D__NONE,		D__NONE,	D__NONE,					},//0f 38 9d
	{R_M,	C_NULL,	D__NONE,		D__NONE,	D__NONE,					},//0f 38 9e
	{R_M,	C_NULL,	D__NONE,		D__NONE,	D__NONE,					},//0f 38 9f
	{R_M,	C_NULL,	D__NONE,		D__NONE,	D__NONE,					},//0f 38 a0
	{R_M,	C_NULL,	D__NONE,		D__NONE,	D__NONE,					},//0f 38 a1
	{R_M,	C_NULL,	D__NONE,		D__NONE,	D__NONE,					},//0f 38 a2
	{R_M,	C_NULL,	D__NONE,		D__NONE,	D__NONE,					},//0f 38 a3
	{R_M,	C_NULL,	D__NONE,		D__NONE,	D__NONE,					},//0f 38 a4
	{R_M,	C_NULL,	D__NONE,		D__NONE,	D__NONE,					},//0f 38 a5
	{R_M,	C_NULL,	D__NONE,		D__NONE,	D__NONE,					},//0f 38 a6
	{R_M,	C_NULL,	D__NONE,		D__NONE,	D__NONE,					},//0f 38 a7
	{R_M,	C_NULL,	D__NONE,		D__NONE,	D__NONE,					},//0f 38 a8
	{R_M,	C_NULL,	D__NONE,		D__NONE,	D__NONE,					},//0f 38 a9
	{R_M,	C_NULL,	D__NONE,		D__NONE,	D__NONE,					},//0f 38 aa
	{R_M,	C_NULL,	D__NONE,		D__NONE,	D__NONE,					},//0f 38 ab
	{R_M,	C_NULL,	D__NONE,		D__NONE,	D__NONE,					},//0f 38 ac
	{R_M,	C_NULL,	D__NONE,		D__NONE,	D__NONE,					},//0f 38 ad
	{R_M,	C_NULL,	D__NONE,		D__NONE,	D__NONE,					},//0f 38 ae
	{R_M,	C_NULL,	D__NONE,		D__NONE,	D__NONE,					},//0f 38 af
	{R_M,	C_NULL,	D__NONE,		D__NONE,	D__NONE,					},//0f 38 b0
	{R_M,	C_NULL,	D__NONE,		D__NONE,	D__NONE,					},//0f 38 b1
	{R_M,	C_NULL,	D__NONE,		D__NONE,	D__NONE,					},//0f 38 b2
	{R_M,	C_NULL,	D__NONE,		D__NONE,	D__NONE,					},//0f 38 b3
	{R_M,	C_NULL,	D__NONE,		D__NONE,	D__NONE,					},//0f 38 b4
	{R_M,	C_NULL,	D__NONE,		D__NONE,	D__NONE,					},//0f 38 b5
	{R_M,	C_NULL,	D__NONE,		D__NONE,	D__NONE,					},//0f 38 b6
	{R_M,	C_NULL,	D__NONE,		D__NONE,	D__NONE,					},//0f 38 b7
	{R_M,	C_NULL,	D__NONE,		D__NONE,	D__NONE,					},//0f 38 b8
	{R_M,	C_NULL,	D__NONE,		D__NONE,	D__NONE,					},//0f 38 b9
	{R_M,	C_NULL,	D__NONE,		D__NONE,	D__NONE,					},//0f 38 ba
	{R_M,	C_NULL,	D__NONE,		D__NONE,	D__NONE,					},//0f 38 bb
	{R_M,	C_NULL,	D__NONE,		D__NONE,	D__NONE,					},//0f 38 bc
	{R_M,	C_NULL,	D__NONE,		D__NONE,	D__NONE,					},//0f 38 bd
	{R_M,	C_NULL,	D__NONE,		D__NONE,	D__NONE,					},//0f 38 be
	{R_M,	C_NULL,	D__NONE,		D__NONE,	D__NONE,					},//0f 38 bf
	{R_M,	C_NULL,	D__NONE,		D__NONE,	D__NONE,					},//0f 38 c0
	{R_M,	C_NULL,	D__NONE,		D__NONE,	D__NONE,					},//0f 38 c1
	{R_M,	C_NULL,	D__NONE,		D__NONE,	D__NONE,					},//0f 38 c2
	{R_M,	C_NULL,	D__NONE,		D__NONE,	D__NONE,					},//0f 38 c3
	{R_M,	C_NULL,	D__NONE,		D__NONE,	D__NONE,					},//0f 38 c4
	{R_M,	C_NULL,	D__NONE,		D__NONE,	D__NONE,					},//0f 38 c5
	{R_M,	C_NULL,	D__NONE,		D__NONE,	D__NONE,					},//0f 38 c6
	{R_M,	C_NULL,	D__NONE,		D__NONE,	D__NONE,					},//0f 38 c7
	{R_M,	C_NULL,	D__NONE,		D__NONE,	D__NONE,					},//0f 38 c8
	{R_M,	C_NULL,	D__NONE,		D__NONE,	D__NONE,					},//0f 38 c9
	{R_M,	C_NULL,	D__NONE,		D__NONE,	D__NONE,					},//0f 38 ca
	{R_M,	C_NULL,	D__NONE,		D__NONE,	D__NONE,					},//0f 38 cb
	{R_M,	C_NULL,	D__NONE,		D__NONE,	D__NONE,					},//0f 38 cc
	{R_M,	C_NULL,	D__NONE,		D__NONE,	D__NONE,					},//0f 38 cd
	{R_M,	C_NULL,	D__NONE,		D__NONE,	D__NONE,					},//0f 38 ce
	{R_M,	C_NULL,	D__NONE,		D__NONE,	D__NONE,					},//0f 38 cf
	{R_M,	C_NULL,	D__NONE,		D__NONE,	D__NONE,					},//0f 38 d0
	{R_M,	C_NULL,	D__NONE,		D__NONE,	D__NONE,					},//0f 38 d1
	{R_M,	C_NULL,	D__NONE,		D__NONE,	D__NONE,					},//0f 38 d2
	{R_M,	C_NULL,	D__NONE,		D__NONE,	D__NONE,					},//0f 38 d3
	{R_M,	C_NULL,	D__NONE,		D__NONE,	D__NONE,					},//0f 38 d4
	{R_M,	C_NULL,	D__NONE,		D__NONE,	D__NONE,					},//0f 38 d5
	{R_M,	C_NULL,	D__NONE,		D__NONE,	D__NONE,					},//0f 38 d6
	{R_M,	C_NULL,	D__NONE,		D__NONE,	D__NONE,					},//0f 38 d7
	{R_M,	C_NULL,	D__NONE,		D__NONE,	D__NONE,					},//0f 38 d8
	{R_M,	C_NULL,	D__NONE,		D__NONE,	D__NONE,					},//0f 38 d9
	{R_M,	C_NULL,	D__NONE,		D__NONE,	D__NONE,					},//0f 38 da
	{R_M,	C_GRP3,	D__NONE,		D__NONE,	D__NONE,(char*)Group0x0f38db,0xdb380f,3},//0f 38 db
	{R_M,	C_GRP3,	D__NONE,		D__NONE,	D__NONE,(char*)Group0x0f38dc,0xdc380f,3},//0f 38 dc
	{R_M,	C_GRP3,	D__NONE,		D__NONE,	D__NONE,(char*)Group0x0f38dd,0xdd380f,3},//0f 38 dd
	{R_M,	C_GRP3,	D__NONE,		D__NONE,	D__NONE,(char*)Group0x0f38de,0xde380f,3},//0f 38 de
	{R_M,	C_GRP3,	D__NONE,		D__NONE,	D__NONE,(char*)Group0x0f38df,0xdf380f,3},//0f 38 df

	{R_M,	C_NULL,	D__NONE,		D__NONE,	D__NONE,					},//0f 38 e0
	{R_M,	C_NULL,	D__NONE,		D__NONE,	D__NONE,					},//0f 38 e1
	{R_M,	C_NULL,	D__NONE,		D__NONE,	D__NONE,					},//0f 38 e2
	{R_M,	C_NULL,	D__NONE,		D__NONE,	D__NONE,					},//0f 38 e3
	{R_M,	C_NULL,	D__NONE,		D__NONE,	D__NONE,					},//0f 38 e4
	{R_M,	C_NULL,	D__NONE,		D__NONE,	D__NONE,					},//0f 38 e5
	{R_M,	C_NULL,	D__NONE,		D__NONE,	D__NONE,					},//0f 38 e6
	{R_M,	C_NULL,	D__NONE,		D__NONE,	D__NONE,					},//0f 38 e7

	{R_M,	C_NULL,	D__NONE,		D__NONE,	D__NONE,					},//0f 38 e8
	{R_M,	C_NULL,	D__NONE,		D__NONE,	D__NONE,					},//0f 38 e9
	{R_M,	C_NULL,	D__NONE,		D__NONE,	D__NONE,					},//0f 38 ea
	{R_M,	C_NULL,	D__NONE,		D__NONE,	D__NONE,					},//0f 38 eb
	{R_M,	C_NULL,	D__NONE,		D__NONE,	D__NONE,					},//0f 38 ec
	{R_M,	C_NULL,	D__NONE,		D__NONE,	D__NONE,					},//0f 38 ed
	{R_M,	C_NULL,	D__NONE,		D__NONE,	D__NONE,					},//0f 38 ee
	{R_M,	C_NULL,	D__NONE,		D__NONE,	D__NONE,					},//0f 38 ef

	{R_M,	C_GRP4,	D__NONE,		D__NONE,	D__NONE,(char*)Group0x0f38f0,0xf0380f,3},//0f 38 f0
	{R_M,	C_GRP4,	D__NONE,		D__NONE,	D__NONE,(char*)Group0x0f38f1,0xf1380f,3},//0f 38 f1
	{R_M,	C_NULL,	D__NONE,		D__NONE,	D__NONE,					},//0f 38 f2
	{R_M,	C_NULL,	D__NONE,		D__NONE,	D__NONE,					},//0f 38 f3
	{R_M,	C_NULL,	D__NONE,		D__NONE,	D__NONE,					},//0f 38 f4
	{R_M,	C_NULL,	D__NONE,		D__NONE,	D__NONE,					},//0f 38 f5
	{R_M,	C_NULL,	D__NONE,		D__NONE,	D__NONE,					},//0f 38 f6
	{R_M,	C_NULL,	D__NONE,		D__NONE,	D__NONE,					},//0f 38 f7

	{R_M,	C_NULL,	D__NONE,		D__NONE,	D__NONE,					},//0f 38 f8
	{R_M,	C_NULL,	D__NONE,		D__NONE,	D__NONE,					},//0f 38 f9
	{R_M,	C_NULL,	D__NONE,		D__NONE,	D__NONE,					},//0f 38 fa
	{R_M,	C_NULL,	D__NONE,		D__NONE,	D__NONE,					},//0f 38 fb
	{R_M,	C_NULL,	D__NONE,		D__NONE,	D__NONE,					},//0f 38 fc
	{R_M,	C_NULL,	D__NONE,		D__NONE,	D__NONE,					},//0f 38 fd
	{R_M,	C_NULL,	D__NONE,		D__NONE,	D__NONE,					},//0f 38 fe
	{R_M,	C_NULL,	D__NONE,		D__NONE,	D__NONE,					},//0f 38 ff

};

DIS_OPCODE_T Group0x0f3a08[] =
{
	{R_M, C_NULL,												}, //no prefix 
	{R_M | Immediate_Ib, C_ROUNDPS,	D__Vdq,	D__Wdq,	D__Ib,		"roundps"	,0x083a0f66,4|C_GROUP_3_TYPE,MAKE_OP_RW_FLAG(OP_W,OP_R,OP_R)}, //prefix 0x66
	{R_M, C_NULL,												}, //prefix 0xf2
	{R_M, C_NULL,												}, //prefix 0xf3
};

DIS_OPCODE_T Group0x0f3a09[] =
{
	{R_M, C_NULL,												}, //no prefix 
	{R_M | Immediate_Ib, C_ROUNDPD,	D__Vdq,	D__Wdq,	D__Ib,		"roundpd"	,0x093a0f66,4|C_GROUP_3_TYPE,MAKE_OP_RW_FLAG(OP_W,OP_R,OP_R)}, //prefix 0x66
	{R_M, C_NULL,												}, //prefix 0xf2
	{R_M, C_NULL,												}, //prefix 0xf3
};
DIS_OPCODE_T Group0x0f3a0a[] =
{
	{R_M, C_NULL,												}, //no prefix 
	{R_M | Immediate_Ib, C_ROUNDSS,	D__Vdq,	D__Wdq,	D__Ib,		"roundss"	,0x0a3a0f66,4|C_GROUP_3_TYPE,MAKE_OP_RW_FLAG(OP_W,OP_R,OP_R)}, //prefix 0x66
	{R_M, C_NULL,												}, //prefix 0xf2
	{R_M, C_NULL,												}, //prefix 0xf3
};
DIS_OPCODE_T Group0x0f3a0b[] =
{
	{R_M, C_NULL,												}, //no prefix 
	{R_M | Immediate_Ib, C_ROUNDSD,	D__Vdq,	D__Wdq,	D__Ib,		"roundsd"	,0x0b3a0f66,4|C_GROUP_3_TYPE,MAKE_OP_RW_FLAG(OP_W,OP_R,OP_R)}, //prefix 0x66
	{R_M, C_NULL,												}, //prefix 0xf2
	{R_M, C_NULL,												}, //prefix 0xf3
};
DIS_OPCODE_T Group0x0f3a0c[] =
{
	{R_M, C_NULL,												}, //no prefix 
	{R_M | Immediate_Ib, C_BLENDPS,	D__Vdq,	D__Wdq,	D__Ib,		"blendps"	,0x0c3a0f66,4|C_GROUP_3_TYPE,MAKE_OP_RW_FLAG(OP_W,OP_R,OP_R)}, //prefix 0x66
	{R_M, C_NULL,												}, //prefix 0xf2
	{R_M, C_NULL,												}, //prefix 0xf3
};
DIS_OPCODE_T Group0x0f3a0d[] =
{
	{R_M, C_NULL,												}, //no prefix 
	{R_M | Immediate_Ib, C_BLENDPD,	D__Vdq,	D__Wdq,	D__Ib,		"blendpd"	,0x0d3a0f66,4|C_GROUP_3_TYPE,MAKE_OP_RW_FLAG(OP_W,OP_R,OP_R)}, //prefix 0x66
	{R_M, C_NULL,												}, //prefix 0xf2
	{R_M, C_NULL,												}, //prefix 0xf3
};
DIS_OPCODE_T Group0x0f3a0e[] =
{
	{R_M, C_NULL,												}, //no prefix 
	{R_M | Immediate_Ib, C_PBLENDW,	D__Vdq,	D__Wdq,	D__Ib,		"pblendw"	,0x0e3a0f66,4|C_GROUP_3_TYPE,MAKE_OP_RW_FLAG(OP_W,OP_R,OP_R)}, //prefix 0x66
	{R_M, C_NULL,												}, //prefix 0xf2
	{R_M, C_NULL,												}, //prefix 0xf3
};
DIS_OPCODE_T Group0x0f3a0f[] =
{
	{R_M | Immediate_Ib, C_PALIGNR,	D__Pq,	D__Qq,	D__Ib,		"palignr"	,0x0f3a0f,3|C_GROUP_3_TYPE,MAKE_OP_RW_FLAG(OP_RW,OP_R,OP_R)}, //no prefix 
	{R_M | Immediate_Ib, C_PALIGNR,	D__Vdq,	D__Wdq,	D__Ib,		"palignr"	,0x0f3a0f66,4|C_GROUP_3_TYPE,MAKE_OP_RW_FLAG(OP_RW,OP_R,OP_R)}, //prefix 0x66
	{R_M, C_NULL,												}, //prefix 0xf2
	{R_M, C_NULL,												}, //prefix 0xf3
};

DIS_OPCODE_T Group0x0f3a14[] =
{
	{R_M, C_NULL,                                             	}, //no prefix 
	{R_M | Immediate_Ib, C_PEXTRB,	D__Mb,	D__Vdq,	D__Ib,			"pextrb"	,0x143a0f66,4|C_GROUP_4_TYPE|(1<<16),MAKE_OP_RW_FLAG(OP_W,OP_R,OP_R)}, //prefix 0x66
	{R_M, C_NULL,												}, //prefix 0xf2
	{R_M, C_NULL,												}, //prefix 0xf3
	//mod = 0x11
	{R_M, C_NULL,                                             	}, //no prefix 
	{R_M | Immediate_Ib|D_64, C_PEXTRB,	D__Ry,	D__Vdq,	D__Ib,			"pextrb"	,0x143a0f66,4|C_GROUP_4_TYPE|(5<<16),MAKE_OP_RW_FLAG(OP_W,OP_R,OP_R)}, //prefix 0x66
	{R_M, C_NULL,												}, //prefix 0xf2
	{R_M, C_NULL,												}, //prefix 0xf3
};

DIS_OPCODE_T Group0x0f3a15[] =
{
	{R_M, C_NULL												}, //no prefix 
	{R_M | Immediate_Ib, C_PEXTRW,	D__Mw,	D__Vdq,	D__Ib,			"pextrw"	,0x153a0f66,4|C_GROUP_4_TYPE|(1<<16),MAKE_OP_RW_FLAG(OP_W,OP_R,OP_R)}, //prefix 0x66
	{R_M, C_NULL,												}, //prefix 0xf2
	{R_M, C_NULL,												}, //prefix 0xf3
	{R_M, C_NULL												}, //no prefix 
	{R_M | Immediate_Ib|D_64, C_PEXTRW,	D__Ry,	D__Vdq,	D__Ib,	"pextrw"	,0x153a0f66,4|C_GROUP_4_TYPE|(5<<16),MAKE_OP_RW_FLAG(OP_W,OP_R,OP_R)}, //prefix 0x66
	{R_M, C_NULL,												}, //prefix 0xf2
	{R_M, C_NULL,												}, //prefix 0xf3
};

DIS_OPCODE_T Group0x0f3a16[] =
{
	{R_M, C_NULL	}, //no prefix 
	{R_M | Immediate_Ib, C_PEXTRD,	D__Ey,	D__Vdq,	D__Ib,		"pextrd"		,0x163a0f66,4|C_GROUP_3_TYPE,MAKE_OP_RW_FLAG(OP_W,OP_R,OP_R)}, //prefix 0x66
	{R_M, C_NULL,												}, //prefix 0xf2
	{R_M, C_NULL,												}, //prefix 0xf3
};

DIS_OPCODE_T Group0x0f3a17[] =
{
	{R_M, C_NULL												}, //no prefix 
	{R_M | Immediate_Ib, C_EXTRACTPS,	D__Ed,	D__Vdq,	D__Ib,		"extractps"	,0x173a0f66,4|C_GROUP_3_TYPE,MAKE_OP_RW_FLAG(OP_W,OP_R,OP_R)}, //prefix 0x66
	{R_M, C_NULL,												}, //prefix 0xf2
	{R_M, C_NULL,												}, //prefix 0xf3
};

DIS_OPCODE_T Group0x0f3a20[] =
{
	{R_M, C_NULL												}, //no prefix 
	{R_M | Immediate_Ib, C_PINSRB,	D__Vdq,	D__Mb,	D__Ib,		"pinsrb"	,0x203a0f66,4|C_GROUP_3_TYPE|(1<<16),MAKE_OP_RW_FLAG(OP_RW,OP_R,OP_R)}, //prefix 0x66
	{R_M, C_NULL,												}, //prefix 0xf2
	{R_M, C_NULL,												}, //prefix 0xf3
	{R_M, C_NULL												}, //no prefix 
	{R_M | Immediate_Ib, C_PINSRB,	D__Vdq,	D__Ry,	D__Ib,		"pinsrb"	,0x203a0f66,4|C_GROUP_3_TYPE|(5<<16),MAKE_OP_RW_FLAG(OP_RW,OP_R,OP_R)}, //prefix 0x66
	{R_M, C_NULL,												}, //prefix 0xf2
	{R_M, C_NULL,												}, //prefix 0xf3

};

DIS_OPCODE_T Group0x0f3a21[] =
{
	{R_M, C_NULL												}, //no prefix 
	{R_M | Immediate_Ib, C_INSERTPS,	D__Vdq,	D__Md,	D__Ib,		"insertps"	,0x213a0f66,4|C_GROUP_4_TYPE|(1<<16),MAKE_OP_RW_FLAG(OP_RW,OP_R,OP_R)}, //prefix 0x66
	{R_M, C_NULL,												}, //prefix 0xf2
	{R_M, C_NULL,												}, //prefix 0xf3
	{R_M, C_NULL												}, //no prefix 
	{R_M | Immediate_Ib, C_INSERTPS,	D__Vdq,	D__Udq,	D__Ib,		"insertps"	,0x213a0f66,4|C_GROUP_4_TYPE|(5<<16),MAKE_OP_RW_FLAG(OP_RW,OP_R,OP_R)}, //prefix 0x66
	{R_M, C_NULL,												}, //prefix 0xf2
	{R_M, C_NULL,												}, //prefix 0xf3
};

DIS_OPCODE_T Group0x0f3a22[] =
{
	{R_M, C_NULL												}, //no prefix 
	{R_M | Immediate_Ib, C_PINSRD,	D__Vdq,	D__Ey,	D__Ib,		"pinsrd"	,0x223a0f66,4|C_GROUP_3_TYPE,MAKE_OP_RW_FLAG(OP_RW,OP_R,OP_R)}, //prefix 0x66
	{R_M, C_NULL,												}, //prefix 0xf2
	{R_M, C_NULL,												}, //prefix 0xf3
};

DIS_OPCODE_T Group0x0f3a40[] =
{
	{R_M, C_NULL												}, //no prefix 
	{R_M | Immediate_Ib, C_DPPS,	D__Vdq,	D__Wdq,	D__Ib,		"dpps"	,0x403a0f66,4|C_GROUP_3_TYPE,MAKE_OP_RW_FLAG(OP_RW,OP_R,OP_R)}, //prefix 0x66
	{R_M, C_NULL,												}, //prefix 0xf2
	{R_M, C_NULL,												}, //prefix 0xf3
};

DIS_OPCODE_T Group0x0f3a41[] =
{
	{R_M, C_NULL												}, //no prefix 
	{R_M | Immediate_Ib, C_DPPD,	D__Vdq,	D__Wdq,	D__Ib,		"dppd"	,0x413a0f66,4|C_GROUP_3_TYPE,MAKE_OP_RW_FLAG(OP_RW,OP_R,OP_R)}, //prefix 0x66
	{R_M, C_NULL,												}, //prefix 0xf2
	{R_M, C_NULL,												}, //prefix 0xf3
};

DIS_OPCODE_T Group0x0f3a42[] =
{
	{R_M, C_NULL												}, //no prefix 
	{R_M | Immediate_Ib, C_MPSADBW,	D__Vdq,	D__Wdq,	D__Ib,		"mpsadbw"	,0x423a0f66,4|C_GROUP_3_TYPE,MAKE_OP_RW_FLAG(OP_RW,OP_R,OP_R)}, //prefix 0x66
	{R_M, C_NULL,												}, //prefix 0xf2
	{R_M, C_NULL,												}, //prefix 0xf3
};

DIS_OPCODE_T Group0x0f3a44[] =
{
	{R_M, C_NULL												}, //no prefix 
	{R_M | Immediate_Ib, C_PCLMULQDQ,	D__Vdq,	D__Wdq,	D__Ib,		"pclmulqdq"	,0x443a0f66,4|C_GROUP_3_TYPE,MAKE_OP_RW_FLAG(OP_W,OP_R,OP_R)}, //prefix 0x66
	{R_M, C_NULL,												}, //prefix 0xf2
	{R_M, C_NULL,												}, //prefix 0xf3
};



DIS_OPCODE_T Group0x0f3a60[] =
{
	{R_M, C_NULL												}, //no prefix 
	{R_M | Immediate_Ib, C_PCMPESTRM,	D__Vdq,	D__Wdq,	D__Ib,		"pcmpestrm"	,0x603a0f66,4|C_GROUP_3_TYPE,MAKE_OP_RW_FLAG(OP_R,OP_R,OP_R)}, //prefix 0x66
	{R_M, C_NULL,												}, //prefix 0xf2
	{R_M, C_NULL,												}, //prefix 0xf3
};

DIS_OPCODE_T Group0x0f3a61[] =
{
	{R_M, C_NULL												}, //no prefix 
	{R_M | Immediate_Ib, C_PCMPESTRI,	D__Vdq,	D__Wdq,	D__Ib,		"pcmpestri"	,0x613a0f66,4|C_GROUP_3_TYPE,MAKE_OP_RW_FLAG(OP_R,OP_R,OP_R)}, //prefix 0x66
	{R_M, C_NULL,												}, //prefix 0xf2
	{R_M, C_NULL,												}, //prefix 0xf3
};

DIS_OPCODE_T Group0x0f3a62[] =
{
	{R_M, C_NULL												}, //no prefix 
	{R_M | Immediate_Ib, C_PCMPISTRM,	D__Vdq,	D__Wdq,	D__Ib,		"pcmpistrm"	,0x623a0f66,4|C_GROUP_3_TYPE,MAKE_OP_RW_FLAG(OP_R,OP_R,OP_R)}, //prefix 0x66
	{R_M, C_NULL,												}, //prefix 0xf2
	{R_M, C_NULL,												}, //prefix 0xf3
};

DIS_OPCODE_T Group0x0f3a63[] =
{
	{R_M, C_NULL												}, //no prefix 
	{R_M | Immediate_Ib, C_PCMPISTRI,	D__Vdq,	D__Wdq,	D__Ib,		"pcmpistri"	,0x633a0f66,4|C_GROUP_3_TYPE,MAKE_OP_RW_FLAG(OP_R,OP_R,OP_R)}, //prefix 0x66
	{R_M, C_NULL,												}, //prefix 0xf2
	{R_M, C_NULL,												}, //prefix 0xf3
};

DIS_OPCODE_T Group0x0f3adf[] =
{
	{R_M, C_NULL												}, //no prefix 
	{R_M | Immediate_Ib, C_AESKEYGENASSIST,	D__Vdq,	D__Wdq,	D__Ib,		"aeskeygenassist"	,0xdf3a0f66,4|C_GROUP_3_TYPE,MAKE_OP_RW_FLAG(OP_W,OP_R,OP_R)}, //prefix 0x66
	{R_M, C_NULL,												}, //prefix 0xf2
	{R_M, C_NULL,												}, //prefix 0xf3
};

DIS_OPCODE_T Group0x0f3a[] =
{

	{R_M,	C_NULL,	D__NONE,		D__NONE,	D__NONE,					},//0f 3a 00
	{R_M,	C_NULL,	D__NONE,		D__NONE,	D__NONE,					},//0f 3a 01
	{R_M,	C_NULL,	D__NONE,		D__NONE,	D__NONE,					},//0f 3a 02
	{R_M,	C_NULL,	D__NONE,		D__NONE,	D__NONE,					},//0f 3a 03
	{R_M,	C_NULL,	D__NONE,		D__NONE,	D__NONE,					},//0f 3a 04
	{R_M,	C_NULL,	D__NONE,		D__NONE,	D__NONE,					},//0f 3a 05
	{R_M,	C_NULL,	D__NONE,		D__NONE,	D__NONE,					},//0f 3a 06
	{R_M,	C_NULL,	D__NONE,		D__NONE,	D__NONE,					},//0f 3a 07

	{R_M,	C_GRP3,	D__NONE,		D__NONE,	D__NONE,(char*)Group0x0f3a08,0x083a0f,3},//0f 3a 08
	{R_M,	C_GRP3,	D__NONE,		D__NONE,	D__NONE,(char*)Group0x0f3a09,0x093a0f,3},//0f 3a 09
	{R_M,	C_GRP3,	D__NONE,		D__NONE,	D__NONE,(char*)Group0x0f3a0a,0x0a3a0f,3},//0f 3a 0a
	{R_M,	C_GRP3,	D__NONE,		D__NONE,	D__NONE,(char*)Group0x0f3a0b,0x0b3a0f,3},//0f 3a 0b
	{R_M,	C_GRP3,	D__NONE,		D__NONE,	D__NONE,(char*)Group0x0f3a0c,0x0c3a0f,3},//0f 3a 0c
	{R_M,	C_GRP3,	D__NONE,		D__NONE,	D__NONE,(char*)Group0x0f3a0d,0x0d3a0f,3},//0f 3a 0d
	{R_M,	C_GRP3,	D__NONE,		D__NONE,	D__NONE,(char*)Group0x0f3a0e,0x0e3a0f,3},//0f 3a 0e
	{R_M,	C_GRP3,	D__NONE,		D__NONE,	D__NONE,(char*)Group0x0f3a0f,0x0f3a0f,3},//0f 3a 0f

	{R_M,	C_NULL,	D__NONE,		D__NONE,	D__NONE,					},//0f 3a 10
	{R_M,	C_NULL,	D__NONE,		D__NONE,	D__NONE,					},//0f 3a 11
	{R_M,	C_NULL,	D__NONE,		D__NONE,	D__NONE,					},//0f 3a 12
	{R_M,	C_NULL,	D__NONE,		D__NONE,	D__NONE,					},//0f 3a 13
	{R_M,	C_GRP4,	D__NONE,		D__NONE,	D__NONE,(char*)Group0x0f3a14,0x143a0f,3},//0f 3a 14
	{R_M,	C_GRP4,	D__NONE,		D__NONE,	D__NONE,(char*)Group0x0f3a15,0x153a0f,3},//0f 3a 15
	{R_M,	C_GRP3,	D__NONE,		D__NONE,	D__NONE,(char*)Group0x0f3a16,0x163a0f,3},//0f 3a 16
	{R_M,	C_GRP3,	D__NONE,		D__NONE,	D__NONE,(char*)Group0x0f3a17,0x173a0f,3},//0f 3a 17

	{R_M,	C_NULL,	D__NONE,		D__NONE,	D__NONE,					},//0f 3a 18
	{R_M,	C_NULL,	D__NONE,		D__NONE,	D__NONE,					},//0f 3a 19
	{R_M,	C_NULL,	D__NONE,		D__NONE,	D__NONE,					},//0f 3a 1a
	{R_M,	C_NULL,	D__NONE,		D__NONE,	D__NONE,					},//0f 3a 1b
	{R_M,	C_NULL,	D__NONE,		D__NONE,	D__NONE,					},//0f 3a 1c
	{R_M,	C_NULL,	D__NONE,		D__NONE,	D__NONE,					},//0f 3a 1d
	{R_M,	C_NULL,	D__NONE,		D__NONE,	D__NONE,					},//0f 3a 1e
	{R_M,	C_NULL,	D__NONE,		D__NONE,	D__NONE,					},//0f 3a 1f

	{R_M,	C_GRP4,	D__NONE,		D__NONE,	D__NONE,(char*)Group0x0f3a20,0x203a0f,3},//0f 3a 20
	{R_M,	C_GRP4,	D__NONE,		D__NONE,	D__NONE,(char*)Group0x0f3a21,0x213a0f,3},//0f 3a 21
	{R_M,	C_GRP3,	D__NONE,		D__NONE,	D__NONE,(char*)Group0x0f3a22,0x223a0f,3},//0f 3a 22
	{R_M,	C_NULL,	D__NONE,		D__NONE,	D__NONE,					},//0f 3a 23
	{R_M,	C_NULL,	D__NONE,		D__NONE,	D__NONE,					},//0f 3a 24
	{R_M,	C_NULL,	D__NONE,		D__NONE,	D__NONE,					},//0f 3a 25
	{R_M,	C_NULL,	D__NONE,		D__NONE,	D__NONE,					},//0f 3a 26
	{R_M,	C_NULL,	D__NONE,		D__NONE,	D__NONE,					},//0f 3a 27

	{R_M,	C_NULL,	D__NONE,		D__NONE,	D__NONE,					},//0f 3a 28
	{R_M,	C_NULL,	D__NONE,		D__NONE,	D__NONE,					},//0f 3a 29
	{R_M,	C_NULL,	D__NONE,		D__NONE,	D__NONE,					},//0f 3a 2a
	{R_M,	C_NULL,	D__NONE,		D__NONE,	D__NONE,					},//0f 3a 2b
	{R_M,	C_NULL,	D__NONE,		D__NONE,	D__NONE,					},//0f 3a 2c
	{R_M,	C_NULL,	D__NONE,		D__NONE,	D__NONE,					},//0f 3a 2d
	{R_M,	C_NULL,	D__NONE,		D__NONE,	D__NONE,					},//0f 3a 2e
	{R_M,	C_NULL,	D__NONE,		D__NONE,	D__NONE,					},//0f 3a 2f

	{R_M,	C_NULL,	D__NONE,		D__NONE,	D__NONE,					},//0f 3a 30
	{R_M,	C_NULL,	D__NONE,		D__NONE,	D__NONE,					},//0f 3a 31
	{R_M,	C_NULL,	D__NONE,		D__NONE,	D__NONE,					},//0f 3a 32
	{R_M,	C_NULL,	D__NONE,		D__NONE,	D__NONE,					},//0f 3a 33
	{R_M,	C_NULL,	D__NONE,		D__NONE,	D__NONE,					},//0f 3a 34
	{R_M,	C_NULL,	D__NONE,		D__NONE,	D__NONE,					},//0f 3a 35
	{R_M,	C_NULL,	D__NONE,		D__NONE,	D__NONE,					},//0f 3a 36
	{R_M,	C_NULL,	D__NONE,		D__NONE,	D__NONE,					},//0f 3a 37

	{R_M,	C_NULL,	D__NONE,		D__NONE,	D__NONE,					},//0f 3a 38
	{R_M,	C_NULL,	D__NONE,		D__NONE,	D__NONE,					},//0f 3a 39
	{R_M,	C_NULL,	D__NONE,		D__NONE,	D__NONE,					},//0f 3a 3a
	{R_M,	C_NULL,	D__NONE,		D__NONE,	D__NONE,					},//0f 3a 3b
	{R_M,	C_NULL,	D__NONE,		D__NONE,	D__NONE,					},//0f 3a 3c
	{R_M,	C_NULL,	D__NONE,		D__NONE,	D__NONE,					},//0f 3a 3d
	{R_M,	C_NULL,	D__NONE,		D__NONE,	D__NONE,					},//0f 3a 3e
	{R_M,	C_NULL,	D__NONE,		D__NONE,	D__NONE,					},//0f 3a 3f

	{R_M,	C_GRP3,	D__NONE,		D__NONE,	D__NONE,(char*)Group0x0f3a40,0x403a0f,3},//0f 3a 40
	{R_M,	C_GRP3,	D__NONE,		D__NONE,	D__NONE,(char*)Group0x0f3a41,0x413a0f,3},//0f 3a 41
	{R_M,	C_GRP3,	D__NONE,		D__NONE,	D__NONE,(char*)Group0x0f3a42,0x423a0f,3},//0f 3a 42
	{R_M,	C_NULL,	D__NONE,		D__NONE,	D__NONE,					},//0f 3a 43
	{R_M,	C_GRP3,	D__NONE,		D__NONE,	D__NONE,(char*)Group0x0f3a44,0x443a0f,3},//0f 3a 44
	{R_M,	C_NULL,	D__NONE,		D__NONE,	D__NONE,					},//0f 3a 45
	{R_M,	C_NULL,	D__NONE,		D__NONE,	D__NONE,					},//0f 3a 46
	{R_M,	C_NULL,	D__NONE,		D__NONE,	D__NONE,					},//0f 3a 47

	{R_M,	C_NULL,	D__NONE,		D__NONE,	D__NONE,					},//0f 3a 48
	{R_M,	C_NULL,	D__NONE,		D__NONE,	D__NONE,					},//0f 3a 49
	{R_M,	C_NULL,	D__NONE,		D__NONE,	D__NONE,					},//0f 3a 4a
	{R_M,	C_NULL,	D__NONE,		D__NONE,	D__NONE,					},//0f 3a 4b
	{R_M,	C_NULL,	D__NONE,		D__NONE,	D__NONE,					},//0f 3a 4c
	{R_M,	C_NULL,	D__NONE,		D__NONE,	D__NONE,					},//0f 3a 4d
	{R_M,	C_NULL,	D__NONE,		D__NONE,	D__NONE,					},//0f 3a 4e
	{R_M,	C_NULL,	D__NONE,		D__NONE,	D__NONE,					},//0f 3a 4f

	{R_M,	C_NULL,	D__NONE,		D__NONE,	D__NONE,					},//0f 3a 50
	{R_M,	C_NULL,	D__NONE,		D__NONE,	D__NONE,					},//0f 3a 51
	{R_M,	C_NULL,	D__NONE,		D__NONE,	D__NONE,					},//0f 3a 52
	{R_M,	C_NULL,	D__NONE,		D__NONE,	D__NONE,					},//0f 3a 53
	{R_M,	C_NULL,	D__NONE,		D__NONE,	D__NONE,					},//0f 3a 54
	{R_M,	C_NULL,	D__NONE,		D__NONE,	D__NONE,					},//0f 3a 55
	{R_M,	C_NULL,	D__NONE,		D__NONE,	D__NONE,					},//0f 3a 56
	{R_M,	C_NULL,	D__NONE,		D__NONE,	D__NONE,					},//0f 3a 57

	{R_M,	C_NULL,	D__NONE,		D__NONE,	D__NONE,					},//0f 3a 58
	{R_M,	C_NULL,	D__NONE,		D__NONE,	D__NONE,					},//0f 3a 59
	{R_M,	C_NULL,	D__NONE,		D__NONE,	D__NONE,					},//0f 3a 5a
	{R_M,	C_NULL,	D__NONE,		D__NONE,	D__NONE,					},//0f 3a 5b
	{R_M,	C_NULL,	D__NONE,		D__NONE,	D__NONE,					},//0f 3a 5c
	{R_M,	C_NULL,	D__NONE,		D__NONE,	D__NONE,					},//0f 3a 5d
	{R_M,	C_NULL,	D__NONE,		D__NONE,	D__NONE,					},//0f 3a 5e
	{R_M,	C_NULL,	D__NONE,		D__NONE,	D__NONE,					},//0f 3a 5f

	{R_M,	C_GRP3,	D__NONE,		D__NONE,	D__NONE,(char*)Group0x0f3a60,0x603a0f,3},//0f 3a 60
	{R_M,	C_GRP3,	D__NONE,		D__NONE,	D__NONE,(char*)Group0x0f3a61,0x613a0f,3},//0f 3a 61
	{R_M,	C_GRP3,	D__NONE,		D__NONE,	D__NONE,(char*)Group0x0f3a62,0x623a0f,3},//0f 3a 62
	{R_M,	C_GRP3,	D__NONE,		D__NONE,	D__NONE,(char*)Group0x0f3a63,0x633a0f,3},//0f 3a 63
	{R_M,	C_NULL,	D__NONE,		D__NONE,	D__NONE,					},//0f 3a 64
	{R_M,	C_NULL,	D__NONE,		D__NONE,	D__NONE,					},//0f 3a 65
	{R_M,	C_NULL,	D__NONE,		D__NONE,	D__NONE,					},//0f 3a 66
	{R_M,	C_NULL,	D__NONE,		D__NONE,	D__NONE,					},//0f 3a 67
	{R_M,	C_NULL,	D__NONE,		D__NONE,	D__NONE,					},//0f 3a 68
	{R_M,	C_NULL,	D__NONE,		D__NONE,	D__NONE,					},//0f 3a 69
	{R_M,	C_NULL,	D__NONE,		D__NONE,	D__NONE,					},//0f 3a 6a
	{R_M,	C_NULL,	D__NONE,		D__NONE,	D__NONE,					},//0f 3a 6b
	{R_M,	C_NULL,	D__NONE,		D__NONE,	D__NONE,					},//0f 3a 6c
	{R_M,	C_NULL,	D__NONE,		D__NONE,	D__NONE,					},//0f 3a 6d
	{R_M,	C_NULL,	D__NONE,		D__NONE,	D__NONE,					},//0f 3a 6e
	{R_M,	C_NULL,	D__NONE,		D__NONE,	D__NONE,					},//0f 3a 6f
	{R_M,	C_NULL,	D__NONE,		D__NONE,	D__NONE,					},//0f 3a 70
	{R_M,	C_NULL,	D__NONE,		D__NONE,	D__NONE,					},//0f 3a 71
	{R_M,	C_NULL,	D__NONE,		D__NONE,	D__NONE,					},//0f 3a 72
	{R_M,	C_NULL,	D__NONE,		D__NONE,	D__NONE,					},//0f 3a 73
	{R_M,	C_NULL,	D__NONE,		D__NONE,	D__NONE,					},//0f 3a 74
	{R_M,	C_NULL,	D__NONE,		D__NONE,	D__NONE,					},//0f 3a 75
	{R_M,	C_NULL,	D__NONE,		D__NONE,	D__NONE,					},//0f 3a 76
	{R_M,	C_NULL,	D__NONE,		D__NONE,	D__NONE,					},//0f 3a 77
	{R_M,	C_NULL,	D__NONE,		D__NONE,	D__NONE,					},//0f 3a 78
	{R_M,	C_NULL,	D__NONE,		D__NONE,	D__NONE,					},//0f 3a 79
	{R_M,	C_NULL,	D__NONE,		D__NONE,	D__NONE,					},//0f 3a 7a
	{R_M,	C_NULL,	D__NONE,		D__NONE,	D__NONE,					},//0f 3a 7b
	{R_M,	C_NULL,	D__NONE,		D__NONE,	D__NONE,					},//0f 3a 7c
	{R_M,	C_NULL,	D__NONE,		D__NONE,	D__NONE,					},//0f 3a 7d
	{R_M,	C_NULL,	D__NONE,		D__NONE,	D__NONE,					},//0f 3a 7e
	{R_M,	C_NULL,	D__NONE,		D__NONE,	D__NONE,					},//0f 3a 7f
	{R_M,	C_NULL,	D__NONE,		D__NONE,	D__NONE,					},//0f 3a 80
	{R_M,	C_NULL,	D__NONE,		D__NONE,	D__NONE,					},//0f 3a 81
	{R_M,	C_NULL,	D__NONE,		D__NONE,	D__NONE,					},//0f 3a 82
	{R_M,	C_NULL,	D__NONE,		D__NONE,	D__NONE,					},//0f 3a 83
	{R_M,	C_NULL,	D__NONE,		D__NONE,	D__NONE,					},//0f 3a 84
	{R_M,	C_NULL,	D__NONE,		D__NONE,	D__NONE,					},//0f 3a 85
	{R_M,	C_NULL,	D__NONE,		D__NONE,	D__NONE,					},//0f 3a 86
	{R_M,	C_NULL,	D__NONE,		D__NONE,	D__NONE,					},//0f 3a 87
	{R_M,	C_NULL,	D__NONE,		D__NONE,	D__NONE,					},//0f 3a 88
	{R_M,	C_NULL,	D__NONE,		D__NONE,	D__NONE,					},//0f 3a 89
	{R_M,	C_NULL,	D__NONE,		D__NONE,	D__NONE,					},//0f 3a 8a
	{R_M,	C_NULL,	D__NONE,		D__NONE,	D__NONE,					},//0f 3a 8b
	{R_M,	C_NULL,	D__NONE,		D__NONE,	D__NONE,					},//0f 3a 8c
	{R_M,	C_NULL,	D__NONE,		D__NONE,	D__NONE,					},//0f 3a 8d
	{R_M,	C_NULL,	D__NONE,		D__NONE,	D__NONE,					},//0f 3a 8e
	{R_M,	C_NULL,	D__NONE,		D__NONE,	D__NONE,					},//0f 3a 8f
	{R_M,	C_NULL,	D__NONE,		D__NONE,	D__NONE,					},//0f 3a 90
	{R_M,	C_NULL,	D__NONE,		D__NONE,	D__NONE,					},//0f 3a 91
	{R_M,	C_NULL,	D__NONE,		D__NONE,	D__NONE,					},//0f 3a 92
	{R_M,	C_NULL,	D__NONE,		D__NONE,	D__NONE,					},//0f 3a 93
	{R_M,	C_NULL,	D__NONE,		D__NONE,	D__NONE,					},//0f 3a 94
	{R_M,	C_NULL,	D__NONE,		D__NONE,	D__NONE,					},//0f 3a 95
	{R_M,	C_NULL,	D__NONE,		D__NONE,	D__NONE,					},//0f 3a 96
	{R_M,	C_NULL,	D__NONE,		D__NONE,	D__NONE,					},//0f 3a 97
	{R_M,	C_NULL,	D__NONE,		D__NONE,	D__NONE,					},//0f 3a 98
	{R_M,	C_NULL,	D__NONE,		D__NONE,	D__NONE,					},//0f 3a 99
	{R_M,	C_NULL,	D__NONE,		D__NONE,	D__NONE,					},//0f 3a 9a
	{R_M,	C_NULL,	D__NONE,		D__NONE,	D__NONE,					},//0f 3a 9b
	{R_M,	C_NULL,	D__NONE,		D__NONE,	D__NONE,					},//0f 3a 9c
	{R_M,	C_NULL,	D__NONE,		D__NONE,	D__NONE,					},//0f 3a 9d
	{R_M,	C_NULL,	D__NONE,		D__NONE,	D__NONE,					},//0f 3a 9e
	{R_M,	C_NULL,	D__NONE,		D__NONE,	D__NONE,					},//0f 3a 9f
	{R_M,	C_NULL,	D__NONE,		D__NONE,	D__NONE,					},//0f 3a a0
	{R_M,	C_NULL,	D__NONE,		D__NONE,	D__NONE,					},//0f 3a a1
	{R_M,	C_NULL,	D__NONE,		D__NONE,	D__NONE,					},//0f 3a a2
	{R_M,	C_NULL,	D__NONE,		D__NONE,	D__NONE,					},//0f 3a a3
	{R_M,	C_NULL,	D__NONE,		D__NONE,	D__NONE,					},//0f 3a a4
	{R_M,	C_NULL,	D__NONE,		D__NONE,	D__NONE,					},//0f 3a a5
	{R_M,	C_NULL,	D__NONE,		D__NONE,	D__NONE,					},//0f 3a a6
	{R_M,	C_NULL,	D__NONE,		D__NONE,	D__NONE,					},//0f 3a a7
	{R_M,	C_NULL,	D__NONE,		D__NONE,	D__NONE,					},//0f 3a a8
	{R_M,	C_NULL,	D__NONE,		D__NONE,	D__NONE,					},//0f 3a a9
	{R_M,	C_NULL,	D__NONE,		D__NONE,	D__NONE,					},//0f 3a aa
	{R_M,	C_NULL,	D__NONE,		D__NONE,	D__NONE,					},//0f 3a ab
	{R_M,	C_NULL,	D__NONE,		D__NONE,	D__NONE,					},//0f 3a ac
	{R_M,	C_NULL,	D__NONE,		D__NONE,	D__NONE,					},//0f 3a ad
	{R_M,	C_NULL,	D__NONE,		D__NONE,	D__NONE,					},//0f 3a ae
	{R_M,	C_NULL,	D__NONE,		D__NONE,	D__NONE,					},//0f 3a af
	{R_M,	C_NULL,	D__NONE,		D__NONE,	D__NONE,					},//0f 3a b0
	{R_M,	C_NULL,	D__NONE,		D__NONE,	D__NONE,					},//0f 3a b1
	{R_M,	C_NULL,	D__NONE,		D__NONE,	D__NONE,					},//0f 3a b2
	{R_M,	C_NULL,	D__NONE,		D__NONE,	D__NONE,					},//0f 3a b3
	{R_M,	C_NULL,	D__NONE,		D__NONE,	D__NONE,					},//0f 3a b4
	{R_M,	C_NULL,	D__NONE,		D__NONE,	D__NONE,					},//0f 3a b5
	{R_M,	C_NULL,	D__NONE,		D__NONE,	D__NONE,					},//0f 3a b6
	{R_M,	C_NULL,	D__NONE,		D__NONE,	D__NONE,					},//0f 3a b7
	{R_M,	C_NULL,	D__NONE,		D__NONE,	D__NONE,					},//0f 3a b8
	{R_M,	C_NULL,	D__NONE,		D__NONE,	D__NONE,					},//0f 3a b9
	{R_M,	C_NULL,	D__NONE,		D__NONE,	D__NONE,					},//0f 3a ba
	{R_M,	C_NULL,	D__NONE,		D__NONE,	D__NONE,					},//0f 3a bb
	{R_M,	C_NULL,	D__NONE,		D__NONE,	D__NONE,					},//0f 3a bc
	{R_M,	C_NULL,	D__NONE,		D__NONE,	D__NONE,					},//0f 3a bd
	{R_M,	C_NULL,	D__NONE,		D__NONE,	D__NONE,					},//0f 3a be
	{R_M,	C_NULL,	D__NONE,		D__NONE,	D__NONE,					},//0f 3a bf
	{R_M,	C_NULL,	D__NONE,		D__NONE,	D__NONE,					},//0f 3a c0
	{R_M,	C_NULL,	D__NONE,		D__NONE,	D__NONE,					},//0f 3a c1
	{R_M,	C_NULL,	D__NONE,		D__NONE,	D__NONE,					},//0f 3a c2
	{R_M,	C_NULL,	D__NONE,		D__NONE,	D__NONE,					},//0f 3a c3
	{R_M,	C_NULL,	D__NONE,		D__NONE,	D__NONE,					},//0f 3a c4
	{R_M,	C_NULL,	D__NONE,		D__NONE,	D__NONE,					},//0f 3a c5
	{R_M,	C_NULL,	D__NONE,		D__NONE,	D__NONE,					},//0f 3a c6
	{R_M,	C_NULL,	D__NONE,		D__NONE,	D__NONE,					},//0f 3a c7
	{R_M,	C_NULL,	D__NONE,		D__NONE,	D__NONE,					},//0f 3a c8
	{R_M,	C_NULL,	D__NONE,		D__NONE,	D__NONE,					},//0f 3a c9
	{R_M,	C_NULL,	D__NONE,		D__NONE,	D__NONE,					},//0f 3a ca
	{R_M,	C_NULL,	D__NONE,		D__NONE,	D__NONE,					},//0f 3a cb
	{R_M,	C_NULL,	D__NONE,		D__NONE,	D__NONE,					},//0f 3a cc
	{R_M,	C_NULL,	D__NONE,		D__NONE,	D__NONE,					},//0f 3a cd
	{R_M,	C_NULL,	D__NONE,		D__NONE,	D__NONE,					},//0f 3a ce
	{R_M,	C_NULL,	D__NONE,		D__NONE,	D__NONE,					},//0f 3a cf
	{R_M,	C_NULL,	D__NONE,		D__NONE,	D__NONE,					},//0f 3a d0
	{R_M,	C_NULL,	D__NONE,		D__NONE,	D__NONE,					},//0f 3a d1
	{R_M,	C_NULL,	D__NONE,		D__NONE,	D__NONE,					},//0f 3a d2
	{R_M,	C_NULL,	D__NONE,		D__NONE,	D__NONE,					},//0f 3a d3
	{R_M,	C_NULL,	D__NONE,		D__NONE,	D__NONE,					},//0f 3a d4
	{R_M,	C_NULL,	D__NONE,		D__NONE,	D__NONE,					},//0f 3a d5
	{R_M,	C_NULL,	D__NONE,		D__NONE,	D__NONE,					},//0f 3a d6
	{R_M,	C_NULL,	D__NONE,		D__NONE,	D__NONE,					},//0f 3a d7
	{R_M,	C_NULL,	D__NONE,		D__NONE,	D__NONE,					},//0f 3a d8
	{R_M,	C_NULL,	D__NONE,		D__NONE,	D__NONE,					},//0f 3a d9
	{R_M,	C_NULL,	D__NONE,		D__NONE,	D__NONE,					},//0f 3a da
	{R_M,	C_NULL,	D__NONE,		D__NONE,	D__NONE,					},//0f 3a db
	{R_M,	C_NULL,	D__NONE,		D__NONE,	D__NONE,					},//0f 3a dc
	{R_M,	C_NULL,	D__NONE,		D__NONE,	D__NONE,					},//0f 3a dd
	{R_M,	C_NULL,	D__NONE,		D__NONE,	D__NONE,					},//0f 3a de
	{R_M,	C_GRP3,	D__NONE,		D__NONE,	D__NONE,(char*)Group0x0f3adf,0xdf3a0f,3},//0f 3a df
	{R_M,	C_NULL,	D__NONE,		D__NONE,	D__NONE,					},//0f 3a e0
	{R_M,	C_NULL,	D__NONE,		D__NONE,	D__NONE,					},//0f 3a e1
	{R_M,	C_NULL,	D__NONE,		D__NONE,	D__NONE,					},//0f 3a e2
	{R_M,	C_NULL,	D__NONE,		D__NONE,	D__NONE,					},//0f 3a e3
	{R_M,	C_NULL,	D__NONE,		D__NONE,	D__NONE,					},//0f 3a e4
	{R_M,	C_NULL,	D__NONE,		D__NONE,	D__NONE,					},//0f 3a e5
	{R_M,	C_NULL,	D__NONE,		D__NONE,	D__NONE,					},//0f 3a e6
	{R_M,	C_NULL,	D__NONE,		D__NONE,	D__NONE,					},//0f 3a e7
	{R_M,	C_NULL,	D__NONE,		D__NONE,	D__NONE,					},//0f 3a e8
	{R_M,	C_NULL,	D__NONE,		D__NONE,	D__NONE,					},//0f 3a e9
	{R_M,	C_NULL,	D__NONE,		D__NONE,	D__NONE,					},//0f 3a ea
	{R_M,	C_NULL,	D__NONE,		D__NONE,	D__NONE,					},//0f 3a eb
	{R_M,	C_NULL,	D__NONE,		D__NONE,	D__NONE,					},//0f 3a ec
	{R_M,	C_NULL,	D__NONE,		D__NONE,	D__NONE,					},//0f 3a ed
	{R_M,	C_NULL,	D__NONE,		D__NONE,	D__NONE,					},//0f 3a ee
	{R_M,	C_NULL,	D__NONE,		D__NONE,	D__NONE,					},//0f 3a ef
	{R_M,	C_NULL,	D__NONE,		D__NONE,	D__NONE,					},//0f 3a f0
	{R_M,	C_NULL,	D__NONE,		D__NONE,	D__NONE,					},//0f 3a f1
	{R_M,	C_NULL,	D__NONE,		D__NONE,	D__NONE,					},//0f 3a f2
	{R_M,	C_NULL,	D__NONE,		D__NONE,	D__NONE,					},//0f 3a f3
	{R_M,	C_NULL,	D__NONE,		D__NONE,	D__NONE,					},//0f 3a f4
	{R_M,	C_NULL,	D__NONE,		D__NONE,	D__NONE,					},//0f 3a f5
	{R_M,	C_NULL,	D__NONE,		D__NONE,	D__NONE,					},//0f 3a f6
	{R_M,	C_NULL,	D__NONE,		D__NONE,	D__NONE,					},//0f 3a f7
	{R_M,	C_NULL,	D__NONE,		D__NONE,	D__NONE,					},//0f 3a f8
	{R_M,	C_NULL,	D__NONE,		D__NONE,	D__NONE,					},//0f 3a f9
	{R_M,	C_NULL,	D__NONE,		D__NONE,	D__NONE,					},//0f 3a fa
	{R_M,	C_NULL,	D__NONE,		D__NONE,	D__NONE,					},//0f 3a fb
	{R_M,	C_NULL,	D__NONE,		D__NONE,	D__NONE,					},//0f 3a fc
	{R_M,	C_NULL,	D__NONE,		D__NONE,	D__NONE,					},//0f 3a fd
	{R_M,	C_NULL,	D__NONE,		D__NONE,	D__NONE,					},//0f 3a fe
	{R_M,	C_NULL,	D__NONE,		D__NONE,	D__NONE,					},//0f 3a ff
};

DIS_OPCODE_T Group0x0f70[] =
{
	{R_M | Immediate_Ib, C_PSHUFW,		D__Pq,		D__Qq,		D__Ib,		"pshufw"			,0x700f,2|C_GROUP_3_TYPE,MAKE_OP_RW_FLAG(OP_W,OP_R,OP_R)}, //no prefix
	{R_M | Immediate_Ib, C_PSHUFD,		D__Vdq,		D__Wdq,		D__Ib,		"pshufd"			,0x700f66,3|C_GROUP_3_TYPE,MAKE_OP_RW_FLAG(OP_W,OP_R,OP_R)}, //0x66
	{R_M | Immediate_Ib, C_PSHUFLW,	D__Vdq,		D__Wdq,		D__Ib,		"pshuflw"				,0x700ff2,3|C_GROUP_3_TYPE,MAKE_OP_RW_FLAG(OP_W,OP_R,OP_R)}, //0xf2 
	{R_M | Immediate_Ib, C_PSHUFHW,	D__Vdq,		D__Wdq,		D__Ib,		"pshufhw"				,0x700ff3,3|C_GROUP_3_TYPE,MAKE_OP_RW_FLAG(OP_W,OP_R,OP_R)}, //0xf3 	
};

DIS_OPCODE_T Group0x0f74[] =
{
	{R_M, C_PCMPEQB,		D__Pq,		D__Qq,		D__NONE,		"pcmpeqb"				,0x740f,2|C_GROUP_3_TYPE,MAKE_OP_RW_FLAG(OP_RW,OP_R,0)}, //no prefix
	{R_M, C_PCMPEQB,		D__Vdq,		D__Wdq,		D__NONE,		"pcmpeqb"				,0x740f66,3|C_GROUP_3_TYPE,MAKE_OP_RW_FLAG(OP_RW,OP_R,0)}, //0x66
	{R_M, C_NULL,					}, //0xf2 
	{R_M, C_NULL,					}, //0xf3 	
};
DIS_OPCODE_T Group0x0f75[] =
{
	{R_M, C_PCMPEQW,		D__Pq,		D__Qq,		D__NONE,		"pcmpeqw"				,0x750f,2|C_GROUP_3_TYPE,MAKE_OP_RW_FLAG(OP_RW,OP_R,0)}, //no prefix
	{R_M, C_PCMPEQW,		D__Vdq,		D__Wdq,		D__NONE,		"pcmpeqw"				,0x750f66,3|C_GROUP_3_TYPE,MAKE_OP_RW_FLAG(OP_RW,OP_R,0)}, //0x66
	{R_M, C_NULL,					}, //0xf2 
	{R_M, C_NULL,					}, //0xf3 	
};
DIS_OPCODE_T Group0x0f76[] =
{
	{R_M, C_PCMPEQD,		D__Pq,		D__Qq,		D__NONE,		"pcmpeqd"			,0x760f,2|C_GROUP_3_TYPE,MAKE_OP_RW_FLAG(OP_RW,OP_R,0)}, //no prefix
	{R_M, C_PCMPEQD,		D__Vdq,		D__Wdq,		D__NONE,		"pcmpeqd"			,0x760f66,3|C_GROUP_3_TYPE,MAKE_OP_RW_FLAG(OP_RW,OP_R,0)}, //0x66
	{R_M, C_NULL,					}, //0xf2 
	{R_M, C_NULL,					}, //0xf3 	
};

DIS_OPCODE_T Group0x0f78[] =
{
	{R_M|F_64, C_VMREAD,	D__Ey,	D__Gy,	D__NONE,	"VMREAD"	,0x780f,2|C_GROUP_3_TYPE,MAKE_OP_RW_FLAG(OP_W,OP_R,0)}, //no prefix 
	{R_M| Immediate_Ib, C_EXTRQ,	D__Vdq,	D__Ib,		D__Ib2,"extrq"		,0x780f66,3|C_GROUP_3_TYPE}, //0x66
	{R_M, C_NULL,D__NONE,	D__NONE,	D__NONE}, //0xf2 
	{R_M, C_NULL,D__NONE,	D__NONE,	D__NONE}, //0xf3 
};

DIS_OPCODE_T Group0x0f79[] =
{
	{R_M|F_64, C_VMWRITE,D__Gy,	D__Ey,		D__NONE,	"VMWRITE"	,0x790f,2|C_GROUP_3_TYPE,MAKE_OP_RW_FLAG(OP_R,OP_R,0)}, //0x79
	{R_M, C_NULL,D__NONE,	D__NONE,	D__NONE}, //0x66 
	{R_M, C_NULL,D__NONE,	D__NONE,	D__NONE}, //0xf2 
	{R_M, C_NULL,D__NONE,	D__NONE,	D__NONE}, //0xf3 
};

DIS_OPCODE_T Group0x0f7c[] =
{
	{R_M, C_NULL,					}, //no prefix
	{R_M, C_HADDPD,		D__Vdq,		D__Wdq,		D__NONE,		"haddpd"			,0x7c0f66,3|C_GROUP_3_TYPE,MAKE_OP_RW_FLAG(OP_RW,OP_R,0)}, //0x66
	{R_M, C_HADDPS,		D__Vps,		D__Wps,		D__NONE,		"haddps"				,0x7c0ff2,3|C_GROUP_3_TYPE,MAKE_OP_RW_FLAG(OP_RW,OP_R,0)}, //0xf2
	{R_M, C_NULL,					}, //0xf3 	
};

DIS_OPCODE_T Group0x0f7d[] =
{
	{R_M, C_NULL,					}, //no prefix
	{R_M, C_HSUBPD,		D__Vdq,		D__Wdq,		D__NONE,		"hsubpd"			,0x7d0f66,3|C_GROUP_3_TYPE,MAKE_OP_RW_FLAG(OP_RW,OP_R,0)}, //0x66
	{R_M, C_HSUBPS,		D__Vps,		D__Wps,		D__NONE,		"hsubps"				,0x7d0ff2,3|C_GROUP_3_TYPE,MAKE_OP_RW_FLAG(OP_RW,OP_R,0)}, //0xf2
	{R_M, C_NULL,					}, //0xf3 	
};

DIS_OPCODE_T Group0x0f7e[] =
{
	{R_M, C_MOVD,		D__Ey,		D__Pd,		D__NONE,	"movd"	,0x7e0f,2|C_GROUP_3_TYPE,MAKE_OP_RW_FLAG(OP_W,OP_R,0)}, //no prefix
	{R_M, C_MOVD,		D__Ey,		D__Vdq,		D__NONE,	"movd"	,0x7e0f66,3|C_GROUP_3_TYPE,MAKE_OP_RW_FLAG(OP_W,OP_R,0)}, //0x66
	{R_M, C_NULL,					}, //0xf2 
	{R_M, C_MOVQ,		D__Vq,		D__Wq,D__NONE,"movq"			,0x7e0ff3,3|C_GROUP_3_TYPE,MAKE_OP_RW_FLAG(OP_W,OP_R,0)}, //0xf3 	
};

DIS_OPCODE_T Group0x0f7f[] =
{
	{R_M, C_MOVQ,		D__Qq,		D__Pq,		D__NONE,			"movq"				,0x7f0f,2|C_GROUP_3_TYPE,MAKE_OP_RW_FLAG(OP_W,OP_R,0)}, //no prefix
	{R_M, C_MOVDQA,		D__Wdq,		D__Vdq,		D__NONE,			"movdqa"			,0x7f0f66,3|C_GROUP_3_TYPE,MAKE_OP_RW_FLAG(OP_W,OP_R,0)}, //0x66
	{R_M, C_NULL,					}, //0xf2 
	{R_M, C_MOVDQU,		D__Wdq,		D__Vdq,		D__NONE,			"movdqu"			,0x7f0ff3,3|C_GROUP_3_TYPE,MAKE_OP_RW_FLAG(OP_W,OP_R,0)}, //0xf3 	
};


DIS_OPCODE_T Group0x0f60[] =
{
	{R_M, C_PUNPCKLBW,	D__Pq,	D__Qq,		D__NONE,"punpcklbw"				,0x600f,2|C_GROUP_3_TYPE,MAKE_OP_RW_FLAG(OP_RW,OP_R,0)}, //no prefix 
	{R_M, C_PUNPCKLBW,	D__Vdq,	D__Wdq,		D__NONE,"punpcklbw"				,0x600f66,3|C_GROUP_3_TYPE,MAKE_OP_RW_FLAG(OP_RW,OP_R,0)}, //0x66
	{R_M, C_NULL,D__NONE,	D__NONE,	D__NONE}, //0xf2 
	{R_M, C_NULL,D__NONE,	D__NONE,	D__NONE}, //0xf3 
};
DIS_OPCODE_T Group0x0f61[] =
{
	{R_M, C_PUNPCKLWD,	D__Pq,	D__Qq,		D__NONE,"punpcklwd"				,0x610f,2|C_GROUP_3_TYPE,MAKE_OP_RW_FLAG(OP_RW,OP_R,0)}, //no prefix 
	{R_M, C_PUNPCKLWD,	D__Vdq,	D__Wdq,		D__NONE,"punpcklwd"				,0x610f66,3|C_GROUP_3_TYPE,MAKE_OP_RW_FLAG(OP_RW,OP_R,0)}, //0x66
	{R_M, C_NULL,D__NONE,	D__NONE,	D__NONE}, //0xf2 
	{R_M, C_NULL,D__NONE,	D__NONE,	D__NONE}, //0xf3 
};
DIS_OPCODE_T Group0x0f62[] =
{
	{R_M, C_PUNPCKLDQ,	D__Pq,	D__Qq,		D__NONE,"punpckldq"				,0x620f,2|C_GROUP_3_TYPE,MAKE_OP_RW_FLAG(OP_RW,OP_R,0)}, //no prefix 
	{R_M, C_PUNPCKLDQ,	D__Vdq,	D__Wdq,		D__NONE,"punpckldq"				,0x620f66,3|C_GROUP_3_TYPE,MAKE_OP_RW_FLAG(OP_RW,OP_R,0)}, //0x66
	{R_M, C_NULL,D__NONE,	D__NONE,	D__NONE}, //0xf2 
	{R_M, C_NULL,D__NONE,	D__NONE,	D__NONE}, //0xf3 
};
DIS_OPCODE_T Group0x0f63[] =
{
	{R_M, C_PACKSSWB,	D__Pq,	D__Qq,		D__NONE,"packsswb"				,0x630f,2|C_GROUP_3_TYPE,MAKE_OP_RW_FLAG(OP_RW,OP_R,0)}, //no prefix 
	{R_M, C_PACKSSWB,	D__Vdq,	D__Wdq,		D__NONE,"packsswb"				,0x630f66,3|C_GROUP_3_TYPE,MAKE_OP_RW_FLAG(OP_RW,OP_R,0)}, //0x66
	{R_M, C_NULL,D__NONE,	D__NONE,	D__NONE}, //0xf2 
	{R_M, C_NULL,D__NONE,	D__NONE,	D__NONE}, //0xf3 
};
DIS_OPCODE_T Group0x0f64[] =
{
	{R_M, C_PCMPGTB,	D__Pq,	D__Qq,		D__NONE,"pcmpgtb"				,0x640f,2|C_GROUP_3_TYPE,MAKE_OP_RW_FLAG(OP_RW,OP_R,0)}, //no prefix 
	{R_M, C_PCMPGTB,	D__Vdq,	D__Wdq,		D__NONE,"pcmpgtb"				,0x640f66,3|C_GROUP_3_TYPE,MAKE_OP_RW_FLAG(OP_RW,OP_R,0)}, //0x66
	{R_M, C_NULL,D__NONE,	D__NONE,	D__NONE}, //0xf2 
	{R_M, C_NULL,D__NONE,	D__NONE,	D__NONE}, //0xf3 
};
DIS_OPCODE_T Group0x0f65[] =
{
	{R_M, C_PCMPGTW,	D__Pq,	D__Qq,		D__NONE,"pcmpgtw"				,0x650f,2|C_GROUP_3_TYPE,MAKE_OP_RW_FLAG(OP_RW,OP_R,0)}, //no prefix 
	{R_M, C_PCMPGTW,	D__Vdq,	D__Wdq,		D__NONE,"pcmpgtw"				,0x650f66,3|C_GROUP_3_TYPE,MAKE_OP_RW_FLAG(OP_RW,OP_R,0)}, //0x66
	{R_M, C_NULL,D__NONE,	D__NONE,	D__NONE}, //0xf2 
	{R_M, C_NULL,D__NONE,	D__NONE,	D__NONE}, //0xf3 
};
DIS_OPCODE_T Group0x0f66[] =
{
	{R_M, C_PCMPGTD,	D__Pq,	D__Qq,		D__NONE,"pcmpgtd"				,0x660f,2|C_GROUP_3_TYPE,MAKE_OP_RW_FLAG(OP_RW,OP_R,0)}, //no prefix 
	{R_M, C_PCMPGTD,	D__Vdq,	D__Wdq,		D__NONE,"pcmpgtd"				,0x660f66,3|C_GROUP_3_TYPE,MAKE_OP_RW_FLAG(OP_RW,OP_R,0)}, //0x66
	{R_M, C_NULL,D__NONE,	D__NONE,	D__NONE}, //0xf2 
	{R_M, C_NULL,D__NONE,	D__NONE,	D__NONE}, //0xf3 
};
DIS_OPCODE_T Group0x0f67[] =
{
	{R_M, C_PACKUSWB,	D__Pq,	D__Qq,		D__NONE,"packuswb"				,0x670f,2|C_GROUP_3_TYPE,MAKE_OP_RW_FLAG(OP_RW,OP_R,0)}, //no prefix 
	{R_M, C_PACKUSWB,	D__Vdq,	D__Wdq,		D__NONE,"packuswb"				,0x670f66,3|C_GROUP_3_TYPE,MAKE_OP_RW_FLAG(OP_RW,OP_R,0)}, //0x66
	{R_M, C_NULL,D__NONE,	D__NONE,	D__NONE}, //0xf2 
	{R_M, C_NULL,D__NONE,	D__NONE,	D__NONE}, //0xf3 
};
DIS_OPCODE_T Group0x0f68[] =
{
	{R_M, C_PUNPCKHBW,	D__Pq,	D__Qq,		D__NONE,"punpckhbw"				,0x680f,2|C_GROUP_3_TYPE,MAKE_OP_RW_FLAG(OP_RW,OP_R,0)}, //no prefix 
	{R_M, C_PUNPCKHBW,	D__Vdq,	D__Wdq,		D__NONE,"punpckhbw"				,0x680f66,3|C_GROUP_3_TYPE,MAKE_OP_RW_FLAG(OP_RW,OP_R,0)}, //0x66
	{R_M, C_NULL,D__NONE,	D__NONE,	D__NONE}, //0xf2 
	{R_M, C_NULL,D__NONE,	D__NONE,	D__NONE}, //0xf3 
};
DIS_OPCODE_T Group0x0f69[] =
{
	{R_M, C_PUNPCKHWD,	D__Pq,	D__Qq,		D__NONE,"punpckhwd"				,0x690f,2|C_GROUP_3_TYPE,MAKE_OP_RW_FLAG(OP_RW,OP_R,0)}, //no prefix 
	{R_M, C_PUNPCKHWD,	D__Vdq,	D__Wdq,		D__NONE,"punpckhwd"				,0x690f66,3|C_GROUP_3_TYPE,MAKE_OP_RW_FLAG(OP_RW,OP_R,0)}, //0x66
	{R_M, C_NULL,D__NONE,	D__NONE,	D__NONE}, //0xf2 
	{R_M, C_NULL,D__NONE,	D__NONE,	D__NONE}, //0xf3 
};
DIS_OPCODE_T Group0x0f6a[] =
{
	{R_M, C_PUNPCKHDQ,	D__Pq,	D__Qq,		D__NONE,"punpckhdq"				,0x6a0f,2|C_GROUP_3_TYPE,MAKE_OP_RW_FLAG(OP_RW,OP_R,0)}, //no prefix 
	{R_M, C_PUNPCKHDQ,	D__Vdq,	D__Wdq,		D__NONE,"punpckhdq"				,0x6a0f66,3|C_GROUP_3_TYPE,MAKE_OP_RW_FLAG(OP_RW,OP_R,0)}, //0x66
	{R_M, C_NULL,D__NONE,	D__NONE,	D__NONE}, //0xf2 
	{R_M, C_NULL,D__NONE,	D__NONE,	D__NONE}, //0xf3 
};
DIS_OPCODE_T Group0x0f6b[] =
{
	{R_M, C_PACKSSDW,	D__Pq,	D__Qq,		D__NONE,"packssdw"				,0x6b0f,2|C_GROUP_3_TYPE,MAKE_OP_RW_FLAG(OP_RW,OP_R,0)}, //no prefix 
	{R_M, C_PACKSSDW,	D__Vdq,	D__Wdq,		D__NONE,"packssdw"				,0x6b0f66,3|C_GROUP_3_TYPE,MAKE_OP_RW_FLAG(OP_RW,OP_R,0)}, //0x66
	{R_M, C_NULL,D__NONE,	D__NONE,	D__NONE}, //0xf2 
	{R_M, C_NULL,D__NONE,	D__NONE,	D__NONE}, //0xf3 
};
DIS_OPCODE_T Group0x0f6c[] =
{
	{R_M, C_NULL,D__NONE,	D__NONE,	D__NONE				}, //no prefix 
	{R_M, C_PUNPCKLQDQ,	D__Vdq,	D__Wdq,		D__NONE,"punpcklqdq"				,0x6c0f66,3|C_GROUP_3_TYPE,MAKE_OP_RW_FLAG(OP_RW,OP_R,0)}, //0x66
	{R_M, C_NULL,D__NONE,	D__NONE,	D__NONE}, //0xf2 
	{R_M, C_NULL,D__NONE,	D__NONE,	D__NONE}, //0xf3 
};
DIS_OPCODE_T Group0x0f6d[] =
{
	{R_M, C_NULL,D__NONE,	D__NONE,	D__NONE			}, //no prefix 
	{R_M, C_PUNPCKHQDQ,	D__Vdq,	D__Wdq,		D__NONE,"punpckhqdq"				,0x6d0f66,3|C_GROUP_3_TYPE,MAKE_OP_RW_FLAG(OP_RW,OP_R,0)}, //0x66
	{R_M, C_NULL,D__NONE,	D__NONE,	D__NONE}, //0xf2 
	{R_M, C_NULL,D__NONE,	D__NONE,	D__NONE}, //0xf3 
};
DIS_OPCODE_T Group0x0f6e[] =
{
	{R_M, C_MOVD,	D__Pq,	D__Ey,		D__NONE,"movd"				,0x6e0f,2|C_GROUP_3_TYPE,MAKE_OP_RW_FLAG(OP_W,OP_R,0)}, //no prefix 
	{R_M, C_MOVD,	D__Vdq,	D__Ey,		D__NONE,"movd"				,0x6e0f66,3|C_GROUP_3_TYPE,MAKE_OP_RW_FLAG(OP_W,OP_R,0)}, //0x66
	{R_M, C_NULL,D__NONE,	D__NONE,	D__NONE}, //0xf2 
	{R_M, C_NULL,D__NONE,	D__NONE,	D__NONE}, //0xf3 
};
DIS_OPCODE_T Group0x0f6f[] =
{
	{R_M, C_MOVQ,	D__Pq,	D__Qq,		D__NONE,"movq"				,0x6f0f,2|C_GROUP_3_TYPE,MAKE_OP_RW_FLAG(OP_W,OP_R,0)}, //no prefix 
	{R_M, C_MOVDQA,	D__Vdq,	D__Wdq,		D__NONE,"movdqa"				,0x6f0f66,3|C_GROUP_3_TYPE,MAKE_OP_RW_FLAG(OP_W,OP_R,0)}, //0x66
	{R_M, C_NULL,D__NONE,	D__NONE,	D__NONE}, //0xf2 
	{R_M, C_MOVDQU,D__Vdq,	D__Wdq,	D__NONE,"movdqu",0x6f0ff3,3|C_GROUP_3_TYPE,MAKE_OP_RW_FLAG(OP_W,OP_R,0)}, //0xf3 
};
DIS_OPCODE_T Group0x0f50[] =
{
	{R_M, C_NULL,	D__NONE,	D__NONE,	D__NONE,}, //no prefix 
	{R_M, C_NULL,	D__NONE,	D__NONE,	D__NONE,}, //0x66
	{R_M, C_NULL,	D__NONE,	D__NONE,	D__NONE}, //0xf2 
	{R_M, C_NULL,	D__NONE,	D__NONE,	D__NONE}, //0xf3 
	//mod=0x11
	{R_M, C_MOVMSKPS,	D__Gy,	D__Ups,		D__NONE,"movmskps"				,0x500f,2|C_GROUP_4_TYPE|(4<<16),MAKE_OP_RW_FLAG(OP_W,OP_R,0)}, //no prefix 
	{R_M, C_MOVMSKPD,	D__Gy,	D__Upd,		D__NONE,"movmskpd"				,0x500f66,3|C_GROUP_4_TYPE|(5<<16),MAKE_OP_RW_FLAG(OP_W,OP_R,0)}, //0x66
	{R_M, C_NULL,D__NONE,	D__NONE,	D__NONE}, //0xf2 
	{R_M, C_NULL,D__NONE,	D__NONE,	D__NONE}, //0xf3 
};
DIS_OPCODE_T Group0x0f51[] =
{
	{R_M, C_SQRTPS,	D__Vps,	D__Wps,		D__NONE,"sqrtps"				,0x510f,2|C_GROUP_3_TYPE,MAKE_OP_RW_FLAG(OP_W,OP_R,0)}, //no prefix 
	{R_M, C_SQRTPD,	D__Vpd,	D__Wpd,		D__NONE,"sqrtpd"				,0x510f66,3|C_GROUP_3_TYPE,MAKE_OP_RW_FLAG(OP_W,OP_R,0)}, //0x66
	{R_M, C_SQRTSD,	D__Vsd,	D__Wsd,	D__NONE,"sqrtsd",0x510ff2,3|C_GROUP_3_TYPE,MAKE_OP_RW_FLAG(OP_W,OP_R,0)}, //0xf2 
	{R_M,  C_SQRTSS,D__Vss,	D__Wss,	D__NONE,"sqrtss",0x510ff3,3|C_GROUP_3_TYPE,MAKE_OP_RW_FLAG(OP_W,OP_R,0)}, //0xf3 
};
DIS_OPCODE_T Group0x0f52[] =
{
	{R_M, C_RSQRTPS,	D__Vps,	D__Wps,		D__NONE,"rsqrtps"				,0x520f,2|C_GROUP_3_TYPE,MAKE_OP_RW_FLAG(OP_W,OP_R,0)}, //no prefix 
	{R_M, C_NULL,	D__NONE,	D__NONE,		D__NONE,				}, //0x66
	{R_M, C_NULL,D__NONE,	D__NONE,	D__NONE}, //0xf2 
	{R_M,  C_RSQRTSS,D__Vss,	D__Wss,	D__NONE,"rsqrtss",0x520ff3,3|C_GROUP_3_TYPE,MAKE_OP_RW_FLAG(OP_W,OP_R,0)}, //0xf3 
};
DIS_OPCODE_T Group0x0f53[] =
{
	{R_M, C_RCPPS,	D__Vps,	D__Wps,		D__NONE,"rcpps"				,0x530f,2|C_GROUP_3_TYPE,MAKE_OP_RW_FLAG(OP_W,OP_R,0)}, //no prefix 
	{R_M, C_NULL,	D__NONE,	D__NONE,		D__NONE,				}, //0x66
	{R_M, C_NULL,D__NONE,	D__NONE,	D__NONE}, //0xf2 
	{R_M,  C_RCPSS,D__Vss,	D__Wss,	D__NONE,"rcpss",0x530ff3,3|C_GROUP_3_TYPE,MAKE_OP_RW_FLAG(OP_W,OP_R,0)}, //0xf3 
};
DIS_OPCODE_T Group0x0f54[] =
{
	{R_M, C_ANDPS,	D__Vps,	D__Wps,		D__NONE,"andps"				,0x540f,2|C_GROUP_3_TYPE,MAKE_OP_RW_FLAG(OP_RW,OP_R,0)}, //no prefix 
	{R_M,  C_ANDPD,D__Vpd,	D__Wpd,	D__NONE,"andpd",0x540f66,3|C_GROUP_3_TYPE,MAKE_OP_RW_FLAG(OP_RW,OP_R,0)}, //0xf6
	{R_M, C_NULL,	D__NONE,	D__NONE,		D__NONE,				}, //0xf2
	{R_M, C_NULL,D__NONE,	D__NONE,	D__NONE}, //0xf3 
	
};
DIS_OPCODE_T Group0x0f55[] =
{
	{R_M, C_ANDNPS,	D__Vps,	D__Wps,		D__NONE,"andnps"				,0x550f,2|C_GROUP_3_TYPE,MAKE_OP_RW_FLAG(OP_RW,OP_R,0)}, //no prefix 
	{R_M,  C_ANDNPD,D__Vpd,	D__Wpd,	D__NONE,"andnpd",0x550f66,3|C_GROUP_3_TYPE,MAKE_OP_RW_FLAG(OP_RW,OP_R,0)}, //0x66 
	{R_M, C_NULL,	D__NONE,	D__NONE,		D__NONE,				}, //0xf2
	{R_M, C_NULL,D__NONE,	D__NONE,	D__NONE}, //0xf3
	
};
DIS_OPCODE_T Group0x0f56[] =
{
	{R_M, C_ORPS,	D__Vps,	D__Wps,		D__NONE,"orps"				,0x560f,2|C_GROUP_3_TYPE,MAKE_OP_RW_FLAG(OP_RW,OP_R,0)}, //no prefix 
	{R_M,  C_ORPD,D__Vpd,	D__Wpd,	D__NONE,"orpd",0x560f66,3|C_GROUP_3_TYPE,MAKE_OP_RW_FLAG(OP_RW,OP_R,0)}, //0x66 
	{R_M, C_NULL,	D__NONE,	D__NONE,		D__NONE,				}, //0xf2
	{R_M, C_NULL,D__NONE,	D__NONE,	D__NONE}, //0xf3 
	
};
DIS_OPCODE_T Group0x0f57[] =
{
	{R_M, C_XORPS,	D__Vps,	D__Wps,		D__NONE,"xorps"				,0x570f,2|C_GROUP_3_TYPE,MAKE_OP_RW_FLAG(OP_RW,OP_R,0)}, //no prefix 
	{R_M,  C_XORPD,D__Vpd,	D__Wpd,	D__NONE,"xorpd",0x570f66,3|C_GROUP_3_TYPE,MAKE_OP_RW_FLAG(OP_RW,OP_R,0)}, //0x66 
	{R_M, C_NULL,	D__NONE,	D__NONE,		D__NONE,				}, //0xf2
	{R_M, C_NULL,D__NONE,	D__NONE,	D__NONE}, //0xf3 
	
};

DIS_OPCODE_T Group0x0f58[] =
{
	{R_M, C_ADDPS,	D__rwVps,	D__rWps,D__NONE,"addps"		,0x580f,2|C_GROUP_3_TYPE,MAKE_OP_RW_FLAG(OP_RW,OP_R,0)}, //no prefix 
	{R_M, C_ADDPD,	D__rwVpd,	D__rWpd,D__NONE,"addpd"		,0x580f66,3|C_GROUP_3_TYPE,MAKE_OP_RW_FLAG(OP_RW,OP_R,0)}, //0x66
	{R_M, C_ADDSD,	D__rwVsd,	D__rWsd,D__NONE,"addsd"		,0x580ff2,3|C_GROUP_3_TYPE,MAKE_OP_RW_FLAG(OP_RW,OP_R,0)}, //0xf2 
	{R_M, C_ADDSS,	D__rwVss,	D__rWss,D__NONE,"addss"		,0x580ff3,3|C_GROUP_3_TYPE,MAKE_OP_RW_FLAG(OP_RW,OP_R,0)}, //0xf3 
};
DIS_OPCODE_T Group0x0f59[] =
{
	{R_M, C_MULPS,	D__rwVps,	D__rWps,		D__NONE,"mulps"		,0x590f,2|C_GROUP_3_TYPE,MAKE_OP_RW_FLAG(OP_RW,OP_R,0)}, //no prefix 
	{R_M, C_MULPD,	D__rwVpd,	D__rWpd,		D__NONE,"mulpd"		,0x590f66,3|C_GROUP_3_TYPE,MAKE_OP_RW_FLAG(OP_RW,OP_R,0)}, //0x66
	{R_M, C_MULSD,	D__rwVsd,	D__rWsd,		D__NONE,"mulsd"		,0x590ff2,3|C_GROUP_3_TYPE,MAKE_OP_RW_FLAG(OP_RW,OP_R,0)}, //0xf2 
	{R_M, C_MULSS,	D__rwVss,	D__rWss,		D__NONE,"mulss"		,0x590ff3,3|C_GROUP_3_TYPE,MAKE_OP_RW_FLAG(OP_RW,OP_R,0)}, //0xf3 
};
DIS_OPCODE_T Group0x0f5a[] =
{
	{R_M, C_CVTPS2PD,	D__wVpd,	D__rWps,		D__NONE,"cvtps2pd"		,0x5a0f,2|C_GROUP_3_TYPE,MAKE_OP_RW_FLAG(OP_W,OP_R,0)}, //no prefix 
	{R_M, C_CVTPD2PS,	D__wVps,	D__rWpd,		D__NONE,"cvtpd2ps"		,0x5a0f66,3|C_GROUP_3_TYPE,MAKE_OP_RW_FLAG(OP_W,OP_R,0)}, //0x66
	{R_M, C_CVTSD2SS,	D__wVsd,	D__rWsd,		D__NONE,"cvtsd2ss"		,0x5a0ff2,3|C_GROUP_3_TYPE,MAKE_OP_RW_FLAG(OP_W,OP_R,0)}, //0xf2 
	{R_M, C_CVTSS2SD,	D__wVss,	D__rWss,		D__NONE,"cvtss2sd"		,0x5a0ff3,3|C_GROUP_3_TYPE,MAKE_OP_RW_FLAG(OP_W,OP_R,0)}, //0xf3 
};
DIS_OPCODE_T Group0x0f5b[] =
{
	{R_M, C_CVTDQ2PS,	D__wVps,	D__rWdq,		D__NONE,"cvtdq2ps"		,0x5b0f,2|C_GROUP_3_TYPE,MAKE_OP_RW_FLAG(OP_W,OP_R,0)}, //no prefix 
	{R_M, C_CVTPS2DQ,	D__wVdq,	D__rWps,		D__NONE,"cvtps2dq"		,0x5b0f66,3|C_GROUP_3_TYPE,MAKE_OP_RW_FLAG(OP_W,OP_R,0)}, //0x66
	{R_M, C_NULL,	D__NONE,	D__NONE,		D__NONE,		}, //0xf2 
	{R_M, C_CVTTPS2DQ,	D__wVss,	D__rWss,		D__NONE,"cvttps2dq"		,0x5b0ff3,3|C_GROUP_3_TYPE,MAKE_OP_RW_FLAG(OP_W,OP_R,0)}, //0xf3 
};
DIS_OPCODE_T Group0x0f5c[] =
{
	{R_M, C_SUBPS,	D__rwVps,	D__rWps,		D__NONE,"subps"		,0x5c0f,2|C_GROUP_3_TYPE,MAKE_OP_RW_FLAG(OP_RW,OP_R,0)}, //no prefix 
	{R_M, C_SUBPD,	D__rwVpd,	D__rWpd,		D__NONE,"subpd"		,0x5c0f66,3|C_GROUP_3_TYPE,MAKE_OP_RW_FLAG(OP_RW,OP_R,0)}, //0x66
	{R_M, C_SUBSD,	D__rwVsd,	D__rWsd,		D__NONE,"subsd"		,0x5c0ff2,3|C_GROUP_3_TYPE,MAKE_OP_RW_FLAG(OP_RW,OP_R,0)}, //0xf2 
	{R_M, C_SUBSS,	D__rwVss,	D__rWss,		D__NONE,"subss"		,0x5c0ff3,3|C_GROUP_3_TYPE,MAKE_OP_RW_FLAG(OP_RW,OP_R,0)}, //0xf3 
};
DIS_OPCODE_T Group0x0f5d[] =
{
	{R_M, C_MINPS,	D__rwVps,	D__rWps,		D__NONE,"minps"		,0x5d0f,2|C_GROUP_3_TYPE,MAKE_OP_RW_FLAG(OP_RW,OP_R,0)}, //no prefix 
	{R_M, C_MINPD,	D__rwVpd,	D__rWpd,		D__NONE,"minpd"		,0x5d0f66,3|C_GROUP_3_TYPE,MAKE_OP_RW_FLAG(OP_RW,OP_R,0)}, //0x66
	{R_M, C_MINSD,	D__rwVsd,	D__rWsd,		D__NONE,"minsd"		,0x5d0ff2,3|C_GROUP_3_TYPE,MAKE_OP_RW_FLAG(OP_RW,OP_R,0)}, //0xf2 
	{R_M, C_MINSS,	D__rwVss,	D__rWss,		D__NONE,"minss"		,0x5d0ff3,3|C_GROUP_3_TYPE,MAKE_OP_RW_FLAG(OP_RW,OP_R,0)}, //0xf3 
};
DIS_OPCODE_T Group0x0f5e[] =
{
	{R_M, C_DIVPS,	D__Vps,	D__Wps,		D__NONE,"divps"		,0x5e0f,2|C_GROUP_3_TYPE,MAKE_OP_RW_FLAG(OP_RW,OP_R,0)}, //no prefix 
	{R_M, C_DIVPD,	D__Vpd,	D__Wpd,		D__NONE,"divpd"		,0x5e0f66,3|C_GROUP_3_TYPE,MAKE_OP_RW_FLAG(OP_RW,OP_R,0)}, //0x66
	{R_M, C_DIVSD,	D__Vsd,	D__Wsd,		D__NONE,"divsd"		,0x5e0ff2,3|C_GROUP_3_TYPE,MAKE_OP_RW_FLAG(OP_RW,OP_R,0)}, //0xf2 
	{R_M, C_DIVSS,	D__Vss,	D__Wss,		D__NONE,"divss"		,0x5e0ff3,3|C_GROUP_3_TYPE,MAKE_OP_RW_FLAG(OP_RW,OP_R,0)}, //0xf3 
};
DIS_OPCODE_T Group0x0f5f[] =
{
	{R_M, C_MAXPS,	D__Vps,	D__Wps,		D__NONE,"maxps"		,0x5f0f,2|C_GROUP_3_TYPE,MAKE_OP_RW_FLAG(OP_RW,OP_R,0)}, //no prefix 
	{R_M, C_MAXPD,	D__Vpd,	D__Wpd,		D__NONE,"maxpd"		,0x5f0f66,3|C_GROUP_3_TYPE,MAKE_OP_RW_FLAG(OP_RW,OP_R,0)}, //0x66
	{R_M, C_MAXSD,	D__Vsd,	D__Wsd,		D__NONE,"maxsd"		,0x5f0ff2,3|C_GROUP_3_TYPE,MAKE_OP_RW_FLAG(OP_RW,OP_R,0)}, //0xf2 
	{R_M, C_MAXSS,	D__Vss,	D__Wss,		D__NONE,"maxss"		,0x5f0ff3,3|C_GROUP_3_TYPE,MAKE_OP_RW_FLAG(OP_RW,OP_R,0)}, //0xf3 
};

DIS_OPCODE_T Group0x0f10[] =
{
	{R_M, C_MOVUPS,	D__Vps,	D__Wps,		D__NONE,"movups"	,0x100f,2|C_GROUP_3_TYPE,MAKE_OP_RW_FLAG(OP_W,OP_R,0)}, //no prefix 
	{R_M, C_MOVUPD,	D__Vpd,	D__Wpd,		D__NONE,"movupd"	,0x100f66,3|C_GROUP_3_TYPE,MAKE_OP_RW_FLAG(OP_W,OP_R,0)}, //0x66
	{R_M, C_MOVSD,	D__Vsd,	D__Wsd,		D__NONE,"movsd"		,0x100ff2,3|C_GROUP_3_TYPE,MAKE_OP_RW_FLAG(OP_W,OP_R,0)}, //0xf2 
	{R_M, C_MOVSS,	D__Vss,	D__Wss,		D__NONE,"movss"		,0x100ff3,3|C_GROUP_3_TYPE,MAKE_OP_RW_FLAG(OP_W,OP_R,0)}, //0xf3 
};

DIS_OPCODE_T Group0x0f11[] =
{
	{R_M, C_MOVUPS,	D__Wps,	D__Vps,		D__NONE,"movups"		,0x110f,2|C_GROUP_3_TYPE,MAKE_OP_RW_FLAG(OP_W,OP_R,0)}, //no prefix 
	{R_M, C_MOVUPD,	D__Wpd,	D__Vpd,		D__NONE,"movupd"		,0x110f66,3|C_GROUP_3_TYPE,MAKE_OP_RW_FLAG(OP_W,OP_R,0)}, //0x66
	{R_M, C_MOVSD,	D__Wsd,	D__Vsd,		D__NONE,"movsd"		,0x110ff2,3|C_GROUP_3_TYPE,MAKE_OP_RW_FLAG(OP_W,OP_R,0)}, //0xf2 
	{R_M, C_MOVSS,	D__Wss,	D__Vss,		D__NONE,"movss"		,0x110ff3,3|C_GROUP_3_TYPE,MAKE_OP_RW_FLAG(OP_W,OP_R,0)}, //0xf3 
};
DIS_OPCODE_T Group0x0f12[] =
{
	// mod=mem (eg. 00 01 10)
	{R_M, C_MOVLPS,	D__Vq,	D__Mq,		D__NONE,"movlps"		,0x120f,2|C_GROUP_4_TYPE|(0<<16),MAKE_OP_RW_FLAG(OP_RW,OP_R,0)}, //no prefix 
	{R_M, C_MOVLPD,	D__Vq,	D__Mq,		D__NONE,"movlpd"		,0x120f66,3|C_GROUP_4_TYPE|(1<<16),MAKE_OP_RW_FLAG(OP_RW,OP_R,0)}, //0x66
	{R_M, C_MOVDDUP,	D__Vq,	D__Wq,		D__NONE,"movddup"		,0x120ff2,3|C_GROUP_4_TYPE|(2<<16),MAKE_OP_RW_FLAG(OP_W,OP_R,0)}, //0xf2 
	{R_M, C_MOVSLDUP,	D__Vq,	D__Wq,		D__NONE,"movsldup"		,0x120ff3,3|C_GROUP_4_TYPE|(3<<16),MAKE_OP_RW_FLAG(OP_W,OP_R,0)}, //0xf3 

	// mod=11
	{R_M, C_MOVHLPS,	D__Vq,		D__Uq,	D__NONE,"movhlps"		,0x120f,2|C_GROUP_4_TYPE|(4<<16),MAKE_OP_RW_FLAG(OP_W,OP_R,0)}, //no prefix 
	{R_M, C_NULL,		D__NONE,	D__NONE,D__NONE,		}, //0x66
	{R_M, C_MOVDDUP,	D__Vq,	D__Wq,		D__NONE,"movddup"		,0x120ff2,3|C_GROUP_4_TYPE|(6<<16),MAKE_OP_RW_FLAG(OP_W,OP_R,0)}, //0xf2 
	{R_M, C_MOVSLDUP,	D__Vq,	D__Wq,		D__NONE,"movsldup"		,0x120ff3,3|C_GROUP_4_TYPE|(7<<16),MAKE_OP_RW_FLAG(OP_W,OP_R,0)}, //0xf3 

};
DIS_OPCODE_T Group0x0f13[] =
{
	{R_M, C_MOVLPS,	D__Mq,	D__Vq,		D__NONE,"movlps"		,0x130f,2|C_GROUP_4_TYPE|(0<<16),MAKE_OP_RW_FLAG(OP_W,OP_R,0)}, //no prefix 
	{R_M, C_MOVLPD,	D__Mq,	D__Vq,		D__NONE,"movlpd"		,0x130f66,3|C_GROUP_4_TYPE|(1<<16),MAKE_OP_RW_FLAG(OP_W,OP_R,0)}, //0x66
	{R_M, C_NULL,	D__NONE,	D__NONE,		D__NONE,		}, //0xf2 
	{R_M, C_NULL,	D__NONE,	D__NONE,		D__NONE,		}, //0xf3 
};
DIS_OPCODE_T Group0x0f14[] =
{
	{R_M, C_UNPCKLPS,	D__Vps,	D__Wq,		D__NONE,"unpcklps"		,0x140f,2|C_GROUP_3_TYPE,MAKE_OP_RW_FLAG(OP_RW,OP_R,0)}, //no prefix 
	{R_M, C_UNPCKLPD,	D__Vpd,	D__Wq,		D__NONE,"unpcklpd"		,0x140f66,3|C_GROUP_3_TYPE,MAKE_OP_RW_FLAG(OP_RW,OP_R,0)}, //0x66
	{R_M, C_NULL,	D__NONE,	D__NONE,		D__NONE,		}, //0xf2 
	{R_M, C_NULL,	D__NONE,	D__NONE,		D__NONE,		}, //0xf3 
};
DIS_OPCODE_T Group0x0f15[] =
{
	{R_M, C_UNPCKHPS,	D__Vps,	D__Wq,		D__NONE,"unpckhps"		,0x150f,2|C_GROUP_3_TYPE,MAKE_OP_RW_FLAG(OP_RW,OP_R,0)}, //no prefix 
	{R_M, C_UNPCKHPD,	D__Vpd,	D__Wq,		D__NONE,"unpckhpd"		,0x150f66,3|C_GROUP_3_TYPE,MAKE_OP_RW_FLAG(OP_RW,OP_R,0)}, //0x66
	{R_M, C_NULL,	D__Vq,	D__Mq,		D__NONE,		}, //0xf2 
	{R_M, C_NULL,	D__Vq,	D__Mq,		D__NONE,		}, //0xf3 
};
DIS_OPCODE_T Group0x0f16[] =
{
	// mod=mem (eg: 00 01 10)
	{R_M, C_MOVHPS,		D__Vq,		D__Mq,		D__NONE,"movhps"		,0x160f,2|C_GROUP_4_TYPE|(0<<16),MAKE_OP_RW_FLAG(OP_RW,OP_R,0)}, //no prefix 
	{R_M, C_MOVHPD,		D__Vpd,		D__Mq,		D__NONE,"movhpd"		,0x160f66,3|C_GROUP_4_TYPE|(1<<16),MAKE_OP_RW_FLAG(OP_RW,OP_R,0)}, //0x66
	{R_M, C_NULL,		D__NONE,	D__NONE,	D__NONE,		}, //0xf2       this opcode need to fixed. there is one bugs.
	{R_M, C_MOVSHDUP,	D__Vq,		D__Wq,		D__NONE,"movshdup"	,0x160ff3,3|C_GROUP_4_TYPE|(3<<16),MAKE_OP_RW_FLAG(OP_W,OP_R,0)}, //0xf3 

	// mod=11
	{R_M, C_MOVLHPS,	D__Vq,		D__Uq,		D__NONE,"movlhps"		,0x160f,2|C_GROUP_4_TYPE|(4<<16),MAKE_OP_RW_FLAG(OP_W,OP_R,0)}, //no prefix 
	{R_M, C_NULL,		D__NONE,	D__NONE,	D__NONE,		}, //0x66
	{R_M, C_NULL,		D__NONE,	D__NONE,	D__NONE,		}, //0xf2       this opcode need to fixed. there is one bugs.
	{R_M, C_MOVSHDUP,	D__Vq,		D__Wq,		D__NONE,"movshdup"	,0x160ff3,3|C_GROUP_4_TYPE|(7<<16),MAKE_OP_RW_FLAG(OP_W,OP_R,0)}, //0xf3 

};
DIS_OPCODE_T Group0x0f17[] =
{
	{R_M, C_MOVHPS,	D__Mq,	D__Vq,		D__NONE,"movhps"		,0x170f,2|C_GROUP_3_TYPE,MAKE_OP_RW_FLAG(OP_W,OP_R,0)}, //no prefix 
	{R_M, C_MOVHPD,	D__Mq,	D__Vq,		D__NONE,"movhpd"		,0x170f66,3|C_GROUP_3_TYPE,MAKE_OP_RW_FLAG(OP_W,OP_R,0)}, //0x66
	{R_M, C_NULL,	D__NONE,	D__NONE,		D__NONE,		}, //0xf2 
	{R_M, C_NULL,	D__NONE,	D__NONE,		D__NONE,		}, //0xf3 
};
DIS_OPCODE_T Group0x0f28[] =
{
	{R_M, C_MOVAPS,	D__Vps,	D__Wps,		D__NONE,"movaps"		,0x280f,2|C_GROUP_3_TYPE,MAKE_OP_RW_FLAG(OP_W,OP_R,0)}, //no prefix 
	{R_M, C_MOVAPD,	D__Vpd,	D__Wpd,		D__NONE,"movapd"		,0x280f66,3|C_GROUP_3_TYPE,MAKE_OP_RW_FLAG(OP_W,OP_R,0)}, //prefix 0x66
	{0, C_NULL,															}, //prefix 0xf2
	{0, C_NULL,															}, //prefix 0xf3
};
DIS_OPCODE_T Group0x0f29[] =
{
	{R_M, C_MOVAPS,	D__Wps,D__Vps,			D__NONE,"movaps"		,0x290f,2|C_GROUP_3_TYPE,MAKE_OP_RW_FLAG(OP_W,OP_R,0)}, //no prefix 
	{R_M, C_MOVAPD,	D__Wpd,D__Vpd,			D__NONE,"movapd"		,0x290f66,3|C_GROUP_3_TYPE,MAKE_OP_RW_FLAG(OP_W,OP_R,0)}, //prefix 0x66
	{0, C_NULL,															}, //prefix 0xf2
	{0, C_NULL,															}, //prefix 0xf3
};


DIS_OPCODE_T Group0x0f2a[] =
{
	{R_M, C_CVTPI2PS,	D__Vps,	D__Qpi,		D__NONE,"cvtpi2ps"		,0x2a0f,2|C_GROUP_3_TYPE,MAKE_OP_RW_FLAG(OP_W,OP_R,0)}, //no prefix 
	{R_M, C_CVTPI2PD,	D__Vpd,	D__Qpi,		D__NONE,"cvtpi2pd"		,0x2a0f66,3|C_GROUP_3_TYPE,MAKE_OP_RW_FLAG(OP_W,OP_R,0)}, //prefix 0x66
	{R_M, C_CVTSI2SD,	D__Vsd,	D__Ey,		D__NONE,"cvtsi2sd"		,0x2a0ff2,3|C_GROUP_3_TYPE,MAKE_OP_RW_FLAG(OP_W,OP_R,0)}, //prefix 0xf2
	{R_M, C_CVTSI2SS,	D__Vss,	D__Ey,		D__NONE,"cvtsi2ss"		,0x2a0ff3,3|C_GROUP_3_TYPE,MAKE_OP_RW_FLAG(OP_W,OP_R,0)}, //prefix 0xf3
};
DIS_OPCODE_T Group0x0f2b[] =
{
	{R_M, C_MOVNTPS,	D__Mps,	D__Vps,		D__NONE,"movntps"		,0x2b0f,2|C_GROUP_3_TYPE|(0<<16),MAKE_OP_RW_FLAG(OP_W,OP_R,0)}, //no prefix 
	{R_M, C_MOVNTPD,	D__Mpd,	D__Vpd,		D__NONE,"movntpd"		,0x2b0f66,3|C_GROUP_3_TYPE|(1<<16),MAKE_OP_RW_FLAG(OP_W,OP_R,0)}, //prefix 0x66
	{R_M, C_MOVNTSD,	D__Mq,	D__Vsd,		D__NONE,"movntsd"		,0x2b0ff2,3|C_GROUP_3_TYPE|(2<<16),MAKE_OP_RW_FLAG(OP_W,OP_R,0)},//prefix 0xf2
	{R_M, C_MOVNTSS,	D__Md,	D__Vss,		D__NONE,"movntss"		,0x2b0ff3,3|C_GROUP_3_TYPE|(3<<16),MAKE_OP_RW_FLAG(OP_W,OP_R,0)} //prefix 0xf3
};
DIS_OPCODE_T Group0x0f2c[] =
{
	{R_M, C_CVTTPS2PI,	D__Ppi,	D__Wps,		D__NONE,"cvttps2pi"		,0x2c0f,2|C_GROUP_3_TYPE,MAKE_OP_RW_FLAG(OP_W,OP_R,0)}, //no prefix 
	{R_M, C_CVTTPD2PI,	D__Ppi,	D__Wpd,		D__NONE,"cvttpd2pi"		,0x2c0f66,3|C_GROUP_3_TYPE,MAKE_OP_RW_FLAG(OP_W,OP_R,0)}, //prefix 0x66
	{R_M, C_CVTTSD2SI,	D__Gy,	D__Wsd,		D__NONE,"cvttsd2si"		,0x2c0ff2,3|C_GROUP_3_TYPE,MAKE_OP_RW_FLAG(OP_W,OP_R,0)}, //prefix 0xf2
	{R_M, C_CVTTSS2SI,	D__Gy,	D__Wss,		D__NONE,"cvttss2si"		,0x2c0ff3,3|C_GROUP_3_TYPE,MAKE_OP_RW_FLAG(OP_W,OP_R,0)}, //prefix 0xf3
};
DIS_OPCODE_T Group0x0f2d[] =
{
	{R_M, C_CVTPS2PI,	D__Ppi,	D__Wps,		D__NONE,"cvtps2pi"	,0x2d0f,2|C_GROUP_3_TYPE,MAKE_OP_RW_FLAG(OP_W,OP_R,0)}, //no prefix 
	{R_M, C_CVTPD2PI,	D__Ppi,	D__Wpd,		D__NONE,"cvtpd2pi"	,0x2d0f66,3|C_GROUP_3_TYPE,MAKE_OP_RW_FLAG(OP_W,OP_R,0)}, //prefix 0x66
	{R_M, C_CVTSD2SI,	D__Gy,	D__Wsd,		D__NONE,"cvtsd2si"	,0x2d0ff2,3|C_GROUP_3_TYPE,MAKE_OP_RW_FLAG(OP_W,OP_R,0)}, //prefix 0xf2
	{R_M, C_CVTSS2SI,	D__Gy,	D__Wss,		D__NONE,"cvtss2si"	,0x2d0ff3,3|C_GROUP_3_TYPE,MAKE_OP_RW_FLAG(OP_W,OP_R,0)}, //prefix 0xf3
};
DIS_OPCODE_T Group0x0f2e[] =
{
	{R_M, C_UCOMISS,	D__Vss,	D__Wss,		D__NONE,"ucomiss"		,0x2e0f,2|C_GROUP_3_TYPE,MAKE_OP_RW_FLAG(OP_R,OP_R,0)}, //no prefix 
	{R_M, C_UCOMISD,	D__Vsd,	D__Wsd,		D__NONE,"ucomisd"		,0x2e0f66,3|C_GROUP_3_TYPE,MAKE_OP_RW_FLAG(OP_R,OP_R,0)}, //prefix 0x66
	{R_M, C_NULL,															}, //prefix 0xf2
	{R_M, C_NULL,															}, //prefix 0xf3
};
DIS_OPCODE_T Group0x0f2f[] =
{
	{R_M, C_COMISS,	D__Vss,	D__Wss,		D__NONE,"comiss"		,0x2f0f,2|C_GROUP_3_TYPE,MAKE_OP_RW_FLAG(OP_R,OP_R,0)}, //no prefix 
	{R_M, C_COMISD,	D__Vsd,	D__Wsd,		D__NONE,"comisd"		,0x2f0f66,3|C_GROUP_3_TYPE,MAKE_OP_RW_FLAG(OP_R,OP_R,0)}, //prefix 0x66
	{R_M, C_NULL,															}, //prefix 0xf2
	{R_M, C_NULL,															}, //prefix 0xf3
};

DIS_OPCODE_T Group0x0fd0[] =
{
	{R_M, C_NULL,	D__NONE,	D__NONE,		D__NONE,		}, //no prefix 
	{R_M, C_ADDSUBPD,D__rwVpd,	D__rWpd,		D__NONE,"addsubpd"		,0xd00f66,3|C_GROUP_3_TYPE,MAKE_OP_RW_FLAG(OP_RW,OP_R,0)}, //prefix 0x66
	{R_M, C_ADDSUBPS,D__rwVps,	D__rWps,		D__NONE,"addsubps"		,0xd00ff2,3|C_GROUP_3_TYPE,MAKE_OP_RW_FLAG(OP_RW,OP_R,0)}, //prefix 0xf2
	{R_M, C_NULL,															}, //prefix 0xf3
};
DIS_OPCODE_T Group0x0fd1[] =
{
	{R_M, C_PSRLW,	D__Pq,	D__Qq,		D__NONE,"psrlw"		,0xd10f,2|C_GROUP_3_TYPE,MAKE_OP_RW_FLAG(OP_RW,OP_R,0)}, //no prefix 
	{R_M, C_PSRLW,	D__Vdq,	D__Wdq,		D__NONE,"psrlw"		,0xd10f66,3|C_GROUP_3_TYPE,MAKE_OP_RW_FLAG(OP_RW,OP_R,0)}, //prefix 0x66
	{R_M, C_NULL,															}, //prefix 0xf2
	{R_M, C_NULL,															}, //prefix 0xf3
};
DIS_OPCODE_T Group0x0fd2[] =
{
	{R_M, C_PSRLD,	D__Pq,	D__Qq,		D__NONE,"psrld"		,0xd20f,2|C_GROUP_3_TYPE,MAKE_OP_RW_FLAG(OP_RW,OP_R,0)}, //no prefix 
	{R_M, C_PSRLD,	D__Vdq,	D__Wdq,		D__NONE,"psrld"		,0xd20f66,3|C_GROUP_3_TYPE,MAKE_OP_RW_FLAG(OP_RW,OP_R,0)}, //prefix 0x66
	{R_M, C_NULL,															}, //prefix 0xf2
	{R_M, C_NULL,															}, //prefix 0xf3
};
DIS_OPCODE_T Group0x0fd3[] =
{
	{R_M, C_PSRLQ,	D__Pq,	D__Qq,		D__NONE,"psrlq"		,0xd30f,2|C_GROUP_3_TYPE,MAKE_OP_RW_FLAG(OP_RW,OP_R,0)}, //no prefix 
	{R_M, C_PSRLQ,	D__Vdq,	D__Wdq,		D__NONE,"psrlq"		,0xd30f66,3|C_GROUP_3_TYPE,MAKE_OP_RW_FLAG(OP_RW,OP_R,0)}, //prefix 0x66
	{R_M, C_NULL,															}, //prefix 0xf2
	{R_M, C_NULL,															}, //prefix 0xf3
};
DIS_OPCODE_T Group0x0fd4[] =
{
	{R_M, C_PADDQ,	D__Pq,	D__Qq,		D__NONE,"paddq"		,0xd40f,2|C_GROUP_3_TYPE,MAKE_OP_RW_FLAG(OP_RW,OP_R,0)}, //no prefix 
	{R_M, C_PADDQ,	D__Vdq,	D__Wdq,		D__NONE,"paddq"		,0xd40f66,3|C_GROUP_3_TYPE,MAKE_OP_RW_FLAG(OP_RW,OP_R,0)}, //prefix 0x66
	{R_M, C_NULL,															}, //prefix 0xf2
	{R_M, C_NULL,															}, //prefix 0xf3
};
DIS_OPCODE_T Group0x0fd5[] =
{
	{R_M, C_PMULLW,	D__Pq,	D__Qq,		D__NONE,"pmullw"		,0xd50f,2|C_GROUP_3_TYPE,MAKE_OP_RW_FLAG(OP_RW,OP_R,0)}, //no prefix 
	{R_M, C_PMULLW,	D__Vdq,	D__Wdq,		D__NONE,"pmullw"		,0xd50f66,3|C_GROUP_3_TYPE,MAKE_OP_RW_FLAG(OP_RW,OP_R,0)}, //prefix 0x66
	{R_M, C_NULL,															}, //prefix 0xf2
	{R_M, C_NULL,															}, //prefix 0xf3
};
DIS_OPCODE_T Group0x0fd6[] =
{
	{R_M, C_NULL,		D__NONE,	D__NONE,	D__NONE,		}, //no prefix 
	{R_M, C_MOVQ,		D__Wq,		D__Vq,		D__NONE,"movq"		,0xd60f66,3|C_GROUP_4_TYPE|(5<<16),MAKE_OP_RW_FLAG(OP_W,OP_R,0)}, //no prefix 0x66
	{R_M, C_MOVDQ2Q,	D__Pq,		D__Uq,		D__NONE,"movdq2q"	,0xd60ff2,3|C_GROUP_4_TYPE|(6<<16),MAKE_OP_RW_FLAG(OP_W,OP_R,0)}, //prefix 0xf2
	{R_M, C_MOVQ2DQ,	D__Vdq,		D__Nq,		D__NONE,"movq2dq"	,0xd60ff3,3|C_GROUP_4_TYPE|(7<<16),MAKE_OP_RW_FLAG(OP_W,OP_R,0)}, //prefix 0xf3
};
DIS_OPCODE_T Group0x0fd7[] =
{
	{R_M, C_PMOVMSKB,	D__Gy,	D__Nq,		D__NONE,"pmovmskb"		,0xd70f,2|C_GROUP_4_TYPE|(4<<16),MAKE_OP_RW_FLAG(OP_W,OP_R,0)}, //no prefix 
	{R_M, C_PMOVMSKB,	D__Gy,	D__Udq,		D__NONE,"pmovmskb"		,0xd70f66,3|C_GROUP_4_TYPE|(5<<16),MAKE_OP_RW_FLAG(OP_W,OP_R,0)}, //prefix 0x66
	{R_M, C_NULL,															}, //prefix 0xf2
	{R_M, C_NULL,															}, //prefix 0xf3
};
DIS_OPCODE_T Group0x0fd8[] =
{
	{R_M, C_PSUBUSB,	D__Pq,	D__Qq,		D__NONE,"psubusb"		,0xd80f,2|C_GROUP_3_TYPE,MAKE_OP_RW_FLAG(OP_RW,OP_R,0)}, //no prefix 
	{R_M, C_PSUBUSB,	D__Vdq,	D__Wdq,		D__NONE,"psubusb"		,0xd80f66,3|C_GROUP_3_TYPE,MAKE_OP_RW_FLAG(OP_RW,OP_R,0)}, //prefix 0x66
	{R_M, C_NULL,															}, //prefix 0xf2
	{R_M, C_NULL,															}, //prefix 0xf3
};
DIS_OPCODE_T Group0x0fd9[] =
{
	{R_M, C_PSUBUSW,	D__Pq,	D__Qq,		D__NONE,"psubusw"		,0xd90f,2|C_GROUP_3_TYPE,MAKE_OP_RW_FLAG(OP_RW,OP_R,0)}, //no prefix 
	{R_M, C_PSUBUSW,	D__Vdq,	D__Wdq,		D__NONE,"psubusw"		,0xd90f66,3|C_GROUP_3_TYPE,MAKE_OP_RW_FLAG(OP_RW,OP_R,0)}, //prefix 0x66
	{R_M, C_NULL,															}, //prefix 0xf2
	{R_M, C_NULL,															}, //prefix 0xf3
};
DIS_OPCODE_T Group0x0fda[] =
{
	{R_M, C_PMINUB,	D__Pq,	D__Qq,		D__NONE,"pminub"		,0xda0f,2|C_GROUP_3_TYPE,MAKE_OP_RW_FLAG(OP_RW,OP_R,0)}, //no prefix 
	{R_M, C_PMINUB,	D__Vdq,	D__Wdq,		D__NONE,"pminub"		,0xda0f66,3|C_GROUP_3_TYPE,MAKE_OP_RW_FLAG(OP_RW,OP_R,0)}, //prefix 0x66
	{R_M, C_NULL,															}, //prefix 0xf2
	{R_M, C_NULL,															}, //prefix 0xf3
};
DIS_OPCODE_T Group0x0fdb[] =
{
	{R_M, C_PAND,	D__Pq,	D__Qq,		D__NONE,"pand"		,0xdb0f,2|C_GROUP_3_TYPE,MAKE_OP_RW_FLAG(OP_RW,OP_R,0)}, //no prefix 
	{R_M, C_PAND,	D__Vdq,	D__Wdq,		D__NONE,"pand"		,0xdb0f66,3|C_GROUP_3_TYPE,MAKE_OP_RW_FLAG(OP_RW,OP_R,0)}, //prefix 0x66
	{R_M, C_NULL,															}, //prefix 0xf2
	{R_M, C_NULL,															}, //prefix 0xf3
};
DIS_OPCODE_T Group0x0fdc[] =
{
	{R_M, C_PADDUSB,	D__Pq,	D__Qq,		D__NONE,"paddusb"		,0xdc0f,2|C_GROUP_3_TYPE,MAKE_OP_RW_FLAG(OP_RW,OP_R,0)}, //no prefix 
	{R_M, C_PADDUSB,	D__Vdq,	D__Wdq,		D__NONE,"paddusb"		,0xdc0f66,3|C_GROUP_3_TYPE,MAKE_OP_RW_FLAG(OP_RW,OP_R,0)}, //prefix 0x66
	{R_M, C_NULL,															}, //prefix 0xf2
	{R_M, C_NULL,															}, //prefix 0xf3
};
DIS_OPCODE_T Group0x0fdd[] =
{
	{R_M, C_PADDUSW,	D__Pq,	D__Qq,		D__NONE,"paddusw"		,0xdd0f,2|C_GROUP_3_TYPE,MAKE_OP_RW_FLAG(OP_RW,OP_R,0)}, //no prefix 
	{R_M, C_PADDUSW,	D__Vdq,	D__Wdq,		D__NONE,"paddusw"		,0xdd0f66,3|C_GROUP_3_TYPE,MAKE_OP_RW_FLAG(OP_RW,OP_R,0)}, //prefix 0x66
	{R_M, C_NULL,															}, //prefix 0xf2
	{R_M, C_NULL,															}, //prefix 0xf3
};
DIS_OPCODE_T Group0x0fde[] =
{
	{R_M, C_PMAXUB,	D__Pq,	D__Qq,		D__NONE,"pmaxub"		,0xde0f,2|C_GROUP_3_TYPE,MAKE_OP_RW_FLAG(OP_RW,OP_R,0)}, //no prefix 
	{R_M, C_PMAXUB,	D__Vdq,	D__Wdq,		D__NONE,"pmaxub"		,0xde0f66,3|C_GROUP_3_TYPE,MAKE_OP_RW_FLAG(OP_RW,OP_R,0)}, //prefix 0x66
	{R_M, C_NULL,															}, //prefix 0xf2
	{R_M, C_NULL,															}, //prefix 0xf3
};
DIS_OPCODE_T Group0x0fdf[] =
{
	{R_M, C_PANDN,	D__Pq,	D__Qq,		D__NONE,"pandn"		,0xdf0f,2|C_GROUP_3_TYPE,MAKE_OP_RW_FLAG(OP_RW,OP_R,0)}, //no prefix 
	{R_M, C_PANDN,	D__Vdq,	D__Wdq,		D__NONE,"pandn"		,0xdf0f66,3|C_GROUP_3_TYPE,MAKE_OP_RW_FLAG(OP_RW,OP_R,0)}, //prefix 0x66
	{R_M, C_NULL,															}, //prefix 0xf2
	{R_M, C_NULL,															}, //prefix 0xf3
};

DIS_OPCODE_T Group0x0fe0[] =
{
	{R_M, C_PAVGB,	D__Pq,	D__Qq,		D__NONE,"pavgb"		,0xe00f,2|C_GROUP_3_TYPE,MAKE_OP_RW_FLAG(OP_RW,OP_R,0)}, //no prefix 
	{R_M, C_PAVGB,	D__Vdq,	D__Wdq,		D__NONE,"pavgb"		,0xe00f66,3|C_GROUP_3_TYPE,MAKE_OP_RW_FLAG(OP_RW,OP_R,0)}, //prefix 0x66
	{R_M, C_NULL,															}, //prefix 0xf2
	{R_M, C_NULL,															}, //prefix 0xf3
};
DIS_OPCODE_T Group0x0fe1[] =
{
	{R_M, C_PSRAW,	D__Pq,	D__Qq,		D__NONE,"psraw"		,0xe10f,2|C_GROUP_3_TYPE,MAKE_OP_RW_FLAG(OP_RW,OP_R,0)}, //no prefix 
	{R_M, C_PSRAW,	D__Vdq,	D__Wdq,		D__NONE,"psraw"		,0xe10f66,3|C_GROUP_3_TYPE,MAKE_OP_RW_FLAG(OP_RW,OP_R,0)}, //prefix 0x66
	{R_M, C_NULL,															}, //prefix 0xf2
	{R_M, C_NULL,															}, //prefix 0xf3
};
DIS_OPCODE_T Group0x0fe2[] =
{
	{R_M, C_PSRAD,	D__Pq,	D__Qq,		D__NONE,"psrad"		,0xe20f,2|C_GROUP_3_TYPE,MAKE_OP_RW_FLAG(OP_RW,OP_R,0)}, //no prefix 
	{R_M, C_PSRAD,	D__Vdq,	D__Wdq,		D__NONE,"psrad"		,0xe20f66,3|C_GROUP_3_TYPE,MAKE_OP_RW_FLAG(OP_RW,OP_R,0)}, //prefix 0x66
	{R_M, C_NULL,															}, //prefix 0xf2
	{R_M, C_NULL,															}, //prefix 0xf3
};
DIS_OPCODE_T Group0x0fe3[] =
{
	{R_M, C_PAVGW,	D__Pq,	D__Qq,		D__NONE,"pavgw"		,0xe30f,2|C_GROUP_3_TYPE,MAKE_OP_RW_FLAG(OP_RW,OP_R,0)}, //no prefix 
	{R_M, C_PAVGW,	D__Vdq,	D__Wdq,		D__NONE,"pavgw"		,0xe30f66,3|C_GROUP_3_TYPE,MAKE_OP_RW_FLAG(OP_RW,OP_R,0)}, //prefix 0x66
	{R_M, C_NULL,															}, //prefix 0xf2
	{R_M, C_NULL,															}, //prefix 0xf3
};
DIS_OPCODE_T Group0x0fe4[] =
{
	{R_M, C_PMULHUW,	D__Pq,	D__Qq,		D__NONE,"pmulhuw"		,0xe40f,2|C_GROUP_3_TYPE,MAKE_OP_RW_FLAG(OP_RW,OP_R,0)}, //no prefix 
	{R_M, C_PMULHUW,	D__Vdq,	D__Wdq,		D__NONE,"pmulhuw"		,0xe40f66,3|C_GROUP_3_TYPE,MAKE_OP_RW_FLAG(OP_RW,OP_R,0)}, //prefix 0x66
	{R_M, C_NULL,															}, //prefix 0xf2
	{R_M, C_NULL,															}, //prefix 0xf3
};
DIS_OPCODE_T Group0x0fe5[] =
{
	{R_M, C_PMULHW,	D__Pq,	D__Qq,		D__NONE,"pmulhw"		,0xe50f,2|C_GROUP_3_TYPE,MAKE_OP_RW_FLAG(OP_RW,OP_R,0)}, //no prefix 
	{R_M, C_PMULHW,	D__Vdq,	D__Wdq,		D__NONE,"pmulhw"		,0xe50f66,3|C_GROUP_3_TYPE,MAKE_OP_RW_FLAG(OP_RW,OP_R,0)}, //prefix 0x66
	{R_M, C_NULL,															}, //prefix 0xf2
	{R_M, C_NULL,															}, //prefix 0xf3
};
DIS_OPCODE_T Group0x0fe6[] =
{
	{R_M, C_NULL,			}, //no prefix 
	{R_M, C_CVTTPD2DQ,	D__Vdq,	D__Wpd,		D__NONE,"cvttpd2dq"		,0xe60f66,3|C_GROUP_3_TYPE,MAKE_OP_RW_FLAG(OP_W,OP_R,0)}, //prefix 0x66
	{R_M, C_CVTPD2DQ,	D__Vdq,	D__Wpd,		D__NONE,"cvtpd2dq"		,0xe60ff2,3|C_GROUP_3_TYPE,MAKE_OP_RW_FLAG(OP_W,OP_R,0)}, //prefix 0xf2
	{R_M, C_CVTDQ2PD,	D__Vpd,	D__Wdq,		D__NONE,"cvtdq2pd" 		,0xe60ff3,3|C_GROUP_3_TYPE,MAKE_OP_RW_FLAG(OP_W,OP_R,0)}, //prefix 0xf3
};
DIS_OPCODE_T Group0x0fe7[] =
{
	{R_M, C_MOVNTQ,		D__Mq,	D__Pq,		D__NONE,"movntq"		,0xe70f,2|C_GROUP_4_TYPE|(0<<16),MAKE_OP_RW_FLAG(OP_W,OP_R,0)}, //no prefix 
	{R_M, C_MOVNTDQ,	D__Mdq,	D__Vdq,		D__NONE,"movntdq"		,0xe70f66,3|C_GROUP_4_TYPE|(1<<16),MAKE_OP_RW_FLAG(OP_W,OP_R,0)}, //prefix 0x66
	{R_M, C_NULL,															}, //prefix 0xf2
	{R_M, C_NULL,															}, //prefix 0xf3
};
DIS_OPCODE_T Group0x0fe8[] =
{
	{R_M, C_PSUBSB,	D__Pq,	D__Qq,		D__NONE,"psubsb"		,0xe80f,2|C_GROUP_3_TYPE,MAKE_OP_RW_FLAG(OP_RW,OP_R,0)}, //no prefix 
	{R_M, C_PSUBSB,	D__Vdq,	D__Wdq,		D__NONE,"psubsb"		,0xe80f66,3|C_GROUP_3_TYPE,MAKE_OP_RW_FLAG(OP_RW,OP_R,0)}, //prefix 0x66
	{R_M, C_NULL,															}, //prefix 0xf2
	{R_M, C_NULL,															}, //prefix 0xf3
};
DIS_OPCODE_T Group0x0fe9[] =
{
	{R_M, C_PSUBSW,	D__Pq,	D__Qq,		D__NONE,"psubsw"		,0xe90f,2|C_GROUP_3_TYPE,MAKE_OP_RW_FLAG(OP_RW,OP_R,0)}, //no prefix 
	{R_M, C_PSUBSW,	D__Vdq,	D__Wdq,		D__NONE,"psubsw"		,0xe90f66,3|C_GROUP_3_TYPE,MAKE_OP_RW_FLAG(OP_RW,OP_R,0)}, //prefix 0x66
	{R_M, C_NULL,															}, //prefix 0xf2
	{R_M, C_NULL,															}, //prefix 0xf3
};
DIS_OPCODE_T Group0x0fea[] =
{
	{R_M, C_PMINSW,	D__Pq,	D__Qq,		D__NONE,"pminsw"		,0xea0f,2|C_GROUP_3_TYPE,MAKE_OP_RW_FLAG(OP_RW,OP_R,0)}, //no prefix 
	{R_M, C_PMINSW,	D__Vdq,	D__Wdq,		D__NONE,"pminsw"		,0xea0f66,3|C_GROUP_3_TYPE,MAKE_OP_RW_FLAG(OP_RW,OP_R,0)}, //prefix 0x66
	{R_M, C_NULL,															}, //prefix 0xf2
	{R_M, C_NULL,															}, //prefix 0xf3
};
DIS_OPCODE_T Group0x0feb[] =
{
	{R_M, C_POR,	D__Pq,	D__Qq,		D__NONE,"por"		,0xeb0f,2|C_GROUP_3_TYPE,MAKE_OP_RW_FLAG(OP_RW,OP_R,0)}, //no prefix 
	{R_M, C_POR,	D__Vdq,	D__Wdq,		D__NONE,"por"		,0xeb0f66,3|C_GROUP_3_TYPE,MAKE_OP_RW_FLAG(OP_RW,OP_R,0)}, //prefix 0x66
	{R_M, C_NULL,															}, //prefix 0xf2
	{R_M, C_NULL,															}, //prefix 0xf3
};
DIS_OPCODE_T Group0x0fec[] =
{
	{R_M, C_PADDSB,	D__Pq,	D__Qq,		D__NONE,"paddsb"		,0xec0f,2|C_GROUP_3_TYPE,MAKE_OP_RW_FLAG(OP_RW,OP_R,0)}, //no prefix 
	{R_M, C_PADDSB,	D__Vdq,	D__Wdq,		D__NONE,"paddsb"		,0xec0f66,3|C_GROUP_3_TYPE,MAKE_OP_RW_FLAG(OP_RW,OP_R,0)}, //prefix 0x66
	{R_M, C_NULL,															}, //prefix 0xf2
	{R_M, C_NULL,															}, //prefix 0xf3
};
DIS_OPCODE_T Group0x0fed[] =
{
	{R_M, C_PADDSW,	D__Pq,	D__Qq,		D__NONE,"paddsw"		,0xed0f,2|C_GROUP_3_TYPE,MAKE_OP_RW_FLAG(OP_RW,OP_R,0)}, //no prefix 
	{R_M, C_PADDSW,	D__Vdq,	D__Wdq,		D__NONE,"paddsw"		,0xed0f66,3|C_GROUP_3_TYPE,MAKE_OP_RW_FLAG(OP_RW,OP_R,0)}, //prefix 0x66
	{R_M, C_NULL,															}, //prefix 0xf2
	{R_M, C_NULL,															}, //prefix 0xf3
};
DIS_OPCODE_T Group0x0fee[] =
{
	{R_M, C_PMAXSW,	D__Pq,	D__Qq,		D__NONE,"pmaxsw"		,0xee0f,2|C_GROUP_3_TYPE,MAKE_OP_RW_FLAG(OP_RW,OP_R,0)}, //no prefix 
	{R_M, C_PMAXSW,	D__Vdq,	D__Wdq,		D__NONE,"pmaxsw"		,0xee0f66,3|C_GROUP_3_TYPE,MAKE_OP_RW_FLAG(OP_RW,OP_R,0)}, //prefix 0x66
	{R_M, C_NULL,															}, //prefix 0xf2
	{R_M, C_NULL,															}, //prefix 0xf3
};
DIS_OPCODE_T Group0x0fef[] =
{
	{R_M, C_PXOR,	D__Pq,	D__Qq,		D__NONE,"pxor"		,0xef0f,2|C_GROUP_3_TYPE,MAKE_OP_RW_FLAG(OP_RW,OP_R,0)}, //no prefix 
	{R_M, C_PXOR,	D__Vdq,	D__Wdq,		D__NONE,"pxor"		,0xef0f66,3|C_GROUP_3_TYPE,MAKE_OP_RW_FLAG(OP_RW,OP_R,0)}, //prefix 0x66
	{R_M, C_NULL,															}, //prefix 0xf2
	{R_M, C_NULL,															}, //prefix 0xf3
};


DIS_OPCODE_T Group0x0ff0[] =
{
	{R_M, C_NULL,			}, //no prefix 
	{R_M, C_NULL,															}, //prefix 0x66
	{R_M, C_LDDQU,	D__Vdq,	D__Mdq,		D__NONE,"lddqu"		,0xf00ff2,3|C_GROUP_4_TYPE|(2<<16),MAKE_OP_RW_FLAG(OP_W,OP_R,0)}, //prefix 0xf2
	{R_M, C_NULL,															}, //prefix 0xf3

};
DIS_OPCODE_T Group0x0ff1[] =
{
	{R_M, C_PSLLW,	D__Pq,	D__Qq,		D__NONE,"psllw"		,0xf10f,2|C_GROUP_3_TYPE,MAKE_OP_RW_FLAG(OP_RW,OP_R,0)}, //no prefix 
	{R_M, C_PSLLW,	D__Vdq,	D__Wdq,		D__NONE,"psllw"		,0xf10f66,3|C_GROUP_3_TYPE,MAKE_OP_RW_FLAG(OP_RW,OP_R,0)}, //prefix 0x66
	{R_M, C_NULL,															}, //prefix 0xf2
	{R_M, C_NULL,															}, //prefix 0xf3
};
DIS_OPCODE_T Group0x0ff2[] =
{
	{R_M, C_PSLLD,	D__Pq,	D__Qq,		D__NONE,"pslld"		,0xf20f,2|C_GROUP_3_TYPE,MAKE_OP_RW_FLAG(OP_RW,OP_R,0)}, //no prefix 
	{R_M, C_PSLLD,	D__Vdq,	D__Wdq,		D__NONE,"pslld"		,0xf20f66,3|C_GROUP_3_TYPE,MAKE_OP_RW_FLAG(OP_RW,OP_R,0)}, //prefix 0x66
	{R_M, C_NULL,															}, //prefix 0xf2
	{R_M, C_NULL,															}, //prefix 0xf3
};
DIS_OPCODE_T Group0x0ff3[] =
{
	{R_M, C_PSLLQ,	D__Pq,	D__Qq,		D__NONE,"psllq"		,0xf30f,2|C_GROUP_3_TYPE,MAKE_OP_RW_FLAG(OP_RW,OP_R,0)}, //no prefix 
	{R_M, C_PSLLQ,	D__Vdq,	D__Wdq,		D__NONE,"psllq"		,0xf30f66,3|C_GROUP_3_TYPE,MAKE_OP_RW_FLAG(OP_RW,OP_R,0)}, //prefix 0x66
	{R_M, C_NULL,															}, //prefix 0xf2
	{R_M, C_NULL,															}, //prefix 0xf3
};
DIS_OPCODE_T Group0x0ff4[] =
{
	{R_M, C_PMULUDQ,	D__Pq,	D__Qq,		D__NONE,"pmuludq"		,0xf40f,2|C_GROUP_3_TYPE,MAKE_OP_RW_FLAG(OP_RW,OP_R,0)}, //no prefix 
	{R_M, C_PMULUDQ,	D__Vdq,	D__Wdq,		D__NONE,"pmuludq"		,0xf40f66,3|C_GROUP_3_TYPE,MAKE_OP_RW_FLAG(OP_RW,OP_R,0)}, //prefix 0x66
	{R_M, C_NULL,															}, //prefix 0xf2
	{R_M, C_NULL,															}, //prefix 0xf3
};
DIS_OPCODE_T Group0x0ff5[] =
{
	{R_M, C_PMADDWD,	D__Pq,	D__Qq,		D__NONE,"pmaddwd"		,0xf50f,2|C_GROUP_3_TYPE,MAKE_OP_RW_FLAG(OP_RW,OP_R,0)}, //no prefix 
	{R_M, C_PMADDWD,	D__Vdq,	D__Wdq,		D__NONE,"pmaddwd"		,0xf50f66,3|C_GROUP_3_TYPE,MAKE_OP_RW_FLAG(OP_RW,OP_R,0)}, //prefix 0x66
	{R_M, C_NULL,															}, //prefix 0xf2
	{R_M, C_NULL,															}, //prefix 0xf3
};
DIS_OPCODE_T Group0x0ff6[] =
{
	{R_M, C_PSADBW,	D__Pq,	D__Qq,		D__NONE,"psadbw"		,0xf60f,2|C_GROUP_3_TYPE,MAKE_OP_RW_FLAG(OP_RW,OP_R,0)}, //no prefix 
	{R_M, C_PSADBW,	D__Vdq,	D__Wdq,		D__NONE,"psadbw"		,0xf60f66,3|C_GROUP_3_TYPE,MAKE_OP_RW_FLAG(OP_RW,OP_R,0)}, //prefix 0x66
	{R_M, C_NULL,															}, //prefix 0xf2
	{R_M, C_NULL,															}, //prefix 0xf3
};
DIS_OPCODE_T Group0x0ff7[] =
{
	{R_M, C_MASKMOVQ,	D__Pq,	D__Nq,		D__NONE,"maskmovq"		,0xf70f,2|C_GROUP_4_TYPE|(4<<16),MAKE_OP_RW_FLAG(OP_R,OP_R,0)}, //no prefix 
	{R_M, C_MASKMOVDQU,	D__Vdq,	D__Udq,		D__NONE,"maskmovdqu"		,0xf70f66,3|C_GROUP_4_TYPE|(5<<16),MAKE_OP_RW_FLAG(OP_R,OP_R,0)}, //prefix 0x66
	{R_M, C_NULL,															}, //prefix 0xf2
	{R_M, C_NULL,															}, //prefix 0xf3
};
DIS_OPCODE_T Group0x0ff8[] =
{
	{R_M, C_PSUBB,	D__Pq,	D__Qq,		D__NONE,"psubb"		,0xf80f,2|C_GROUP_3_TYPE,MAKE_OP_RW_FLAG(OP_RW,OP_R,0)}, //no prefix 
	{R_M, C_PSUBB,	D__Vdq,	D__Wdq,		D__NONE,"psubb"		,0xf80f66,3|C_GROUP_3_TYPE,MAKE_OP_RW_FLAG(OP_RW,OP_R,0)}, //prefix 0x66
	{R_M, C_NULL,															}, //prefix 0xf2
	{R_M, C_NULL,															}, //prefix 0xf3
};
DIS_OPCODE_T Group0x0ff9[] =
{
	{R_M, C_PSUBW,	D__Pq,	D__Qq,		D__NONE,"psubw"		,0xf90f,2|C_GROUP_3_TYPE,MAKE_OP_RW_FLAG(OP_RW,OP_R,0)}, //no prefix 
	{R_M, C_PSUBW,	D__Vdq,	D__Wdq,		D__NONE,"psubw"		,0xf90f66,3|C_GROUP_3_TYPE,MAKE_OP_RW_FLAG(OP_RW,OP_R,0)}, //prefix 0x66
	{R_M, C_NULL,															}, //prefix 0xf2
	{R_M, C_NULL,															}, //prefix 0xf3
};
DIS_OPCODE_T Group0x0ffa[] =
{
	{R_M, C_PSUBD,	D__Pq,	D__Qq,		D__NONE,"psubd"		,0xfa0f,2|C_GROUP_3_TYPE,MAKE_OP_RW_FLAG(OP_RW,OP_R,0)}, //no prefix 
	{R_M, C_PSUBD,	D__Vdq,	D__Wdq,		D__NONE,"psubd"		,0xfa0f66,3|C_GROUP_3_TYPE,MAKE_OP_RW_FLAG(OP_RW,OP_R,0)}, //prefix 0x66
	{R_M, C_NULL,															}, //prefix 0xf2
	{R_M, C_NULL,															}, //prefix 0xf3
};
DIS_OPCODE_T Group0x0ffb[] =
{
	{R_M, C_PSUBQ,	D__Pq,	D__Qq,		D__NONE,"psubq"		,0xfb0f,2|C_GROUP_3_TYPE,MAKE_OP_RW_FLAG(OP_RW,OP_R,0)}, //no prefix 
	{R_M, C_PSUBQ,	D__Vdq,	D__Wdq,		D__NONE,"psubq"		,0xfb0f66,3|C_GROUP_3_TYPE,MAKE_OP_RW_FLAG(OP_RW,OP_R,0)}, //prefix 0x66
	{R_M, C_NULL,															}, //prefix 0xf2
	{R_M, C_NULL,															}, //prefix 0xf3
};
DIS_OPCODE_T Group0x0ffc[] =
{
	{R_M, C_PADDB,	D__Pq,	D__Qq,		D__NONE,"paddb"		,0xfc0f,2|C_GROUP_3_TYPE,MAKE_OP_RW_FLAG(OP_RW,OP_R,0)}, //no prefix 
	{R_M, C_PADDB,	D__Vdq,	D__Wdq,		D__NONE,"paddb"		,0xfc0f66,3|C_GROUP_3_TYPE,MAKE_OP_RW_FLAG(OP_RW,OP_R,0)}, //prefix 0x66
	{R_M, C_NULL,															}, //prefix 0xf2
	{R_M, C_NULL,															}, //prefix 0xf3
};
DIS_OPCODE_T Group0x0ffd[] =
{
	{R_M, C_PADDW,	D__Pq,	D__Qq,		D__NONE,"paddw"		,0xfd0f,2|C_GROUP_3_TYPE,MAKE_OP_RW_FLAG(OP_RW,OP_R,0)}, //no prefix 
	{R_M, C_PADDW,	D__Vdq,	D__Wdq,		D__NONE,"paddw"		,0xfd0f66,3|C_GROUP_3_TYPE,MAKE_OP_RW_FLAG(OP_RW,OP_R,0)}, //prefix 0x66
	{R_M, C_NULL,															}, //prefix 0xf2
	{R_M, C_NULL,															}, //prefix 0xf3
};
DIS_OPCODE_T Group0x0ffe[] =
{
	{R_M, C_PADDD,	D__Pq,	D__Qq,		D__NONE,"paddd"		,0xfe0f,2|C_GROUP_3_TYPE,MAKE_OP_RW_FLAG(OP_RW,OP_R,0)}, //no prefix 
	{R_M, C_PADDD,	D__Vdq,	D__Wdq,		D__NONE,"paddd"		,0xfe0f66,3|C_GROUP_3_TYPE,MAKE_OP_RW_FLAG(OP_RW,OP_R,0)}, //prefix 0x66
	{R_M, C_NULL,															}, //prefix 0xf2
	{R_M, C_NULL,															}, //prefix 0xf3
};

DIS_OPCODE_T Group0x0fc2[] =
{
	{R_M | Immediate_Ib, C_CMPPS,	D__Vps, D__Wps,	D__Ib,"cmpps"		,0xc20f,2|C_GROUP_3_TYPE,MAKE_OP_RW_FLAG(OP_RW,OP_R,OP_R)}, //no prefix 
	{R_M | Immediate_Ib, C_CMPPD,	D__Vpd,	D__Wpd,	D__Ib,"cmppd"		,0xc20f66,3|C_GROUP_3_TYPE,MAKE_OP_RW_FLAG(OP_RW,OP_R,OP_R)}, //prefix 0x66
	{R_M | Immediate_Ib, C_CMPSD,	D__Vsd,	D__Wsd,	D__Ib,"cmpsd"	,0xc20ff2,3|C_GROUP_3_TYPE,MAKE_OP_RW_FLAG(OP_RW,OP_R,OP_R)}, //prefix 0xf2
	{R_M | Immediate_Ib, C_CMPSS,	D__Vss,	D__Wss,	D__Ib,"cmpss",0xc20ff3,3|C_GROUP_3_TYPE,MAKE_OP_RW_FLAG(OP_RW,OP_R,OP_R)}, //prefix 0xf3
};
DIS_OPCODE_T Group0x0fb8[] =
{
	{R_M, C_NULL,												}, //no prefix
	{R_M, C_NULL,												}, //prefix 0x66
	{R_M, C_NULL,												}, //prefix 0xf2
	{R_M, C_POPCNT,	D__Gv,	D__Ev,	D__NONE,		"popcnt",0xb80ff3,3|C_GROUP_3_TYPE,MAKE_OP_RW_FLAG(OP_W,OP_R,0)}, //prefix 0xf3
};


DIS_OPCODE_T Group0x0fc4[] =
{
	{R_M | Immediate_Ib, C_PINSRW,	D__Pq,	D__Mw,		D__Ib,"pinsrw"		,0xc40f,2|C_GROUP_4_TYPE|(0<<16),MAKE_OP_RW_FLAG(OP_W,OP_R,OP_R)}, //no prefix 
	{R_M | Immediate_Ib, C_PINSRW,	D__Vdq,	D__Mw,		D__Ib,"pinsrw"		,0xc40f66,3|C_GROUP_4_TYPE|(1<<16),MAKE_OP_RW_FLAG(OP_W,OP_R,OP_R)}, //prefix 0x66
	{R_M, C_NULL,												}, //prefix 0xf2
	{R_M, C_NULL,												}, //prefix 0xf3
	//mod = 0x11
	{R_M | Immediate_Ib, C_PINSRW,	D__Pq,	D__Rd,		D__Ib,"pinsrw"		,0xc40f,2|C_GROUP_4_TYPE|(4<<16),MAKE_OP_RW_FLAG(OP_W,OP_R,OP_R)}, //no prefix 
	{R_M | Immediate_Ib, C_PINSRW,	D__Vdq,	D__Rd,		D__Ib,"pinsrw"		,0xc40f66,3|C_GROUP_4_TYPE|(5<<16),MAKE_OP_RW_FLAG(OP_W,OP_R,OP_R)}, //prefix 0x66
	{R_M, C_NULL,															}, //prefix 0xf2
	{R_M, C_NULL,															}, //prefix 0xf3

};

DIS_OPCODE_T Group0x0fc5[] =
{
	{R_M | Immediate_Ib, C_PEXTRW,D__Gy,D__Nq,D__Ib,"pextrw"	,0xc50f,2|C_GROUP_4_TYPE|(4<<16),MAKE_OP_RW_FLAG(OP_W,OP_R,OP_R)}, //no prefix 
	{R_M | Immediate_Ib, C_PEXTRW,D__Gy,D__Udq,D__Ib,"pextrw"	,0xc50f66,3|C_GROUP_4_TYPE|(5<<16),MAKE_OP_RW_FLAG(OP_W,OP_R,OP_R)}, //prefix 0x66
	{R_M, C_NULL,															}, //prefix 0xf2
	{R_M, C_NULL,															}, //prefix 0xf3

};

DIS_OPCODE_T Group0x0fc6[] =
{
	{R_M | Immediate_Ib, C_SHUFPS,	D__Vps,	D__Wps,		D__Ib,"shufps"		,0xc60f,2|C_GROUP_3_TYPE,MAKE_OP_RW_FLAG(OP_RW,OP_R,OP_R)}, //no prefix 
	{R_M | Immediate_Ib, C_SHUFPD,	D__Vpd,	D__Wpd,		D__Ib,"shufpd"		,0xc60f66,3|C_GROUP_3_TYPE,MAKE_OP_RW_FLAG(OP_RW,OP_R,OP_R)}, //prefix 0x66
	{R_M, C_NULL,												}, //prefix 0xf2
	{R_M, C_NULL,												}, //prefix 0xf3
};

DIS_OPCODE_T Group0x90[] =
{
	{0, C_XCHG_NOP,		D__rAX,D__rAX_r8,			D__NONE,"XCHG"	,	0x90,1|C_GROUP_3_TYPE,MAKE_OP_RW_FLAG(OP_RW,OP_RW,0)}, //no prefix 
	{0, C_XCHG_NOP,		D__rAX,D__rAX_r8,			D__NONE,"XCHG"	,	0x9066,2|C_GROUP_3_TYPE,MAKE_OP_RW_FLAG(OP_RW,OP_RW,0)}, //prefix 0x66
	{R_M, C_NULL,												}, //prefix 0xf2
	{0, C_PAUSE,D__NONE,	D__NONE,		D__NONE,"PAUSE",0x90f3,2|C_GROUP_3_TYPE}, //prefix 0xf3
};

DIS_OPCODE_T Group0x0f0f[]=
{
	{R_M, C_NULL,		D__NONE,	D__NONE,	D__NONE,	NULL	,0x0f0f,2|C_GROUP_3DNOW_TYPE}, //0x00
	{R_M, C_NULL,		D__NONE,	D__NONE,	D__NONE,	NULL	,0x0f0f,2|C_GROUP_3DNOW_TYPE}, //0x01
	{R_M, C_NULL,		D__NONE,	D__NONE,	D__NONE,	NULL	,0x0f0f,2|C_GROUP_3DNOW_TYPE}, //0x02
	{R_M, C_NULL,		D__NONE,	D__NONE,	D__NONE,	NULL	,0x0f0f,2|C_GROUP_3DNOW_TYPE}, //0x03
	{R_M, C_NULL,		D__NONE,	D__NONE,	D__NONE,	NULL	,0x0f0f,2|C_GROUP_3DNOW_TYPE}, //0x04
	{R_M, C_NULL,		D__NONE,	D__NONE,	D__NONE,	NULL	,0x0f0f,2|C_GROUP_3DNOW_TYPE}, //0x05
	{R_M, C_NULL,		D__NONE,	D__NONE,	D__NONE,	NULL	,0x0f0f,2|C_GROUP_3DNOW_TYPE}, //0x06
	{R_M, C_NULL,		D__NONE,	D__NONE,	D__NONE,	NULL	,0x0f0f,2|C_GROUP_3DNOW_TYPE}, //0x07

	{R_M, C_NULL,		D__NONE,	D__NONE,	D__NONE,	NULL	,0x0f0f,2|C_GROUP_3DNOW_TYPE}, //0x08
	{R_M, C_NULL,		D__NONE,	D__NONE,	D__NONE,	NULL	,0x0f0f,2|C_GROUP_3DNOW_TYPE}, //0x09
	{R_M, C_NULL,		D__NONE,	D__NONE,	D__NONE,	NULL	,0x0f0f,2|C_GROUP_3DNOW_TYPE}, //0x0a
	{R_M, C_NULL,		D__NONE,	D__NONE,	D__NONE,	NULL	,0x0f0f,2|C_GROUP_3DNOW_TYPE}, //0x0b
	{R_M, C_PI2FW,		D__Pq,		D__Qq,		D__NONE,	"PI2FW"	,0x0f0f,2|C_GROUP_3DNOW_TYPE|(0x0c<<16)}, //0x0c
	{R_M, C_PI2FD,		D__Pq,		D__Qq,		D__NONE,	"PI2FD"	,0x0f0f,2|C_GROUP_3DNOW_TYPE|(0x0d<<16)}, //0x0d
	{R_M, C_NULL,		D__NONE,	D__NONE,	D__NONE,	NULL	,0x0f0f,2|C_GROUP_3DNOW_TYPE}, //0x0e
	{R_M, C_NULL,		D__NONE,	D__NONE,	D__NONE,	NULL	,0x0f0f,2|C_GROUP_3DNOW_TYPE}, //0x0f

	{R_M, C_NULL,		D__NONE,	D__NONE,	D__NONE,	NULL	,0x0f0f,2|C_GROUP_3DNOW_TYPE}, //0x10
	{R_M, C_NULL,		D__NONE,	D__NONE,	D__NONE,	NULL	,0x0f0f,2|C_GROUP_3DNOW_TYPE}, //0x11
	{R_M, C_NULL,		D__NONE,	D__NONE,	D__NONE,	NULL	,0x0f0f,2|C_GROUP_3DNOW_TYPE}, //0x12
	{R_M, C_NULL,		D__NONE,	D__NONE,	D__NONE,	NULL	,0x0f0f,2|C_GROUP_3DNOW_TYPE}, //0x13
	{R_M, C_NULL,		D__NONE,	D__NONE,	D__NONE,	NULL	,0x0f0f,2|C_GROUP_3DNOW_TYPE}, //0x14
	{R_M, C_NULL,		D__NONE,	D__NONE,	D__NONE,	NULL	,0x0f0f,2|C_GROUP_3DNOW_TYPE}, //0x15
	{R_M, C_NULL,		D__NONE,	D__NONE,	D__NONE,	NULL	,0x0f0f,2|C_GROUP_3DNOW_TYPE}, //0x16
	{R_M, C_NULL,		D__NONE,	D__NONE,	D__NONE,	NULL	,0x0f0f,2|C_GROUP_3DNOW_TYPE}, //0x17

	{R_M, C_NULL,		D__NONE,	D__NONE,	D__NONE,	NULL	,0x0f0f,2|C_GROUP_3DNOW_TYPE}, //0x18
	{R_M, C_NULL,		D__NONE,	D__NONE,	D__NONE,	NULL	,0x0f0f,2|C_GROUP_3DNOW_TYPE}, //0x19
	{R_M, C_NULL,		D__NONE,	D__NONE,	D__NONE,	NULL	,0x0f0f,2|C_GROUP_3DNOW_TYPE}, //0x1a
	{R_M, C_NULL,		D__NONE,	D__NONE,	D__NONE,	NULL	,0x0f0f,2|C_GROUP_3DNOW_TYPE}, //0x1b
	{R_M, C_PF2IW,		D__Pq,		D__Qq,		D__NONE,	"PF2IW"	,0x0f0f,2|C_GROUP_3DNOW_TYPE|(0x1c<<16)}, //0x1c
	{R_M, C_PF2ID,		D__Pq,		D__Qq,		D__NONE,	"PF2ID"	,0x0f0f,2|C_GROUP_3DNOW_TYPE|(0x1d<<16)}, //0x1d
	{R_M, C_NULL,		D__NONE,	D__NONE,	D__NONE,	NULL	,0x0f0f,2|C_GROUP_3DNOW_TYPE}, //0x1e
	{R_M, C_NULL,		D__NONE,	D__NONE,	D__NONE,	NULL	,0x0f0f,2|C_GROUP_3DNOW_TYPE}, //0x1f

	{R_M, C_NULL,		D__NONE,	D__NONE,	D__NONE,	NULL	,0x0f0f,2|C_GROUP_3DNOW_TYPE}, //0x20
	{R_M, C_NULL,		D__NONE,	D__NONE,	D__NONE,	NULL	,0x0f0f,2|C_GROUP_3DNOW_TYPE}, //0x21
	{R_M, C_NULL,		D__NONE,	D__NONE,	D__NONE,	NULL	,0x0f0f,2|C_GROUP_3DNOW_TYPE}, //0x22
	{R_M, C_NULL,		D__NONE,	D__NONE,	D__NONE,	NULL	,0x0f0f,2|C_GROUP_3DNOW_TYPE}, //0x23
	{R_M, C_NULL,		D__NONE,	D__NONE,	D__NONE,	NULL	,0x0f0f,2|C_GROUP_3DNOW_TYPE}, //0x24
	{R_M, C_NULL,		D__NONE,	D__NONE,	D__NONE,	NULL	,0x0f0f,2|C_GROUP_3DNOW_TYPE}, //0x25
	{R_M, C_NULL,		D__NONE,	D__NONE,	D__NONE,	NULL	,0x0f0f,2|C_GROUP_3DNOW_TYPE}, //0x26
	{R_M, C_NULL,		D__NONE,	D__NONE,	D__NONE,	NULL	,0x0f0f,2|C_GROUP_3DNOW_TYPE}, //0x27

	{R_M, C_NULL,		D__NONE,	D__NONE,	D__NONE,	NULL	,0x0f0f,2|C_GROUP_3DNOW_TYPE}, //0x28
	{R_M, C_NULL,		D__NONE,	D__NONE,	D__NONE,	NULL	,0x0f0f,2|C_GROUP_3DNOW_TYPE}, //0x29
	{R_M, C_NULL,		D__NONE,	D__NONE,	D__NONE,	NULL	,0x0f0f,2|C_GROUP_3DNOW_TYPE}, //0x2a
	{R_M, C_NULL,		D__NONE,	D__NONE,	D__NONE,	NULL	,0x0f0f,2|C_GROUP_3DNOW_TYPE}, //0x2b
	{R_M, C_NULL,		D__NONE,	D__NONE,	D__NONE,	NULL	,0x0f0f,2|C_GROUP_3DNOW_TYPE}, //0x2c
	{R_M, C_NULL,		D__NONE,	D__NONE,	D__NONE,	NULL	,0x0f0f,2|C_GROUP_3DNOW_TYPE}, //0x2d
	{R_M, C_NULL,		D__NONE,	D__NONE,	D__NONE,	NULL	,0x0f0f,2|C_GROUP_3DNOW_TYPE}, //0x2e
	{R_M, C_NULL,		D__NONE,	D__NONE,	D__NONE,	NULL	,0x0f0f,2|C_GROUP_3DNOW_TYPE}, //0x2f

	{R_M, C_NULL,		D__NONE,	D__NONE,	D__NONE,	NULL	,0x0f0f,2|C_GROUP_3DNOW_TYPE}, //0x30
	{R_M, C_NULL,		D__NONE,	D__NONE,	D__NONE,	NULL	,0x0f0f,2|C_GROUP_3DNOW_TYPE}, //0x31
	{R_M, C_NULL,		D__NONE,	D__NONE,	D__NONE,	NULL	,0x0f0f,2|C_GROUP_3DNOW_TYPE}, //0x32
	{R_M, C_NULL,		D__NONE,	D__NONE,	D__NONE,	NULL	,0x0f0f,2|C_GROUP_3DNOW_TYPE}, //0x33
	{R_M, C_NULL,		D__NONE,	D__NONE,	D__NONE,	NULL	,0x0f0f,2|C_GROUP_3DNOW_TYPE}, //0x34
	{R_M, C_NULL,		D__NONE,	D__NONE,	D__NONE,	NULL	,0x0f0f,2|C_GROUP_3DNOW_TYPE}, //0x35
	{R_M, C_NULL,		D__NONE,	D__NONE,	D__NONE,	NULL	,0x0f0f,2|C_GROUP_3DNOW_TYPE}, //0x36
	{R_M, C_NULL,		D__NONE,	D__NONE,	D__NONE,	NULL	,0x0f0f,2|C_GROUP_3DNOW_TYPE}, //0x37

	{R_M, C_NULL,		D__NONE,	D__NONE,	D__NONE,	NULL	,0x0f0f,2|C_GROUP_3DNOW_TYPE}, //0x38
	{R_M, C_NULL,		D__NONE,	D__NONE,	D__NONE,	NULL	,0x0f0f,2|C_GROUP_3DNOW_TYPE}, //0x39
	{R_M, C_NULL,		D__NONE,	D__NONE,	D__NONE,	NULL	,0x0f0f,2|C_GROUP_3DNOW_TYPE}, //0x3a
	{R_M, C_NULL,		D__NONE,	D__NONE,	D__NONE,	NULL	,0x0f0f,2|C_GROUP_3DNOW_TYPE}, //0x3b
	{R_M, C_NULL,		D__NONE,	D__NONE,	D__NONE,	NULL	,0x0f0f,2|C_GROUP_3DNOW_TYPE}, //0x3c
	{R_M, C_NULL,		D__NONE,	D__NONE,	D__NONE,	NULL	,0x0f0f,2|C_GROUP_3DNOW_TYPE}, //0x3d
	{R_M, C_NULL,		D__NONE,	D__NONE,	D__NONE,	NULL	,0x0f0f,2|C_GROUP_3DNOW_TYPE}, //0x3e
	{R_M, C_NULL,		D__NONE,	D__NONE,	D__NONE,	NULL	,0x0f0f,2|C_GROUP_3DNOW_TYPE}, //0x3f

	{R_M, C_NULL,		D__NONE,	D__NONE,	D__NONE,	NULL	,0x0f0f,2|C_GROUP_3DNOW_TYPE}, //0x40
	{R_M, C_NULL,		D__NONE,	D__NONE,	D__NONE,	NULL	,0x0f0f,2|C_GROUP_3DNOW_TYPE}, //0x41
	{R_M, C_NULL,		D__NONE,	D__NONE,	D__NONE,	NULL	,0x0f0f,2|C_GROUP_3DNOW_TYPE}, //0x42
	{R_M, C_NULL,		D__NONE,	D__NONE,	D__NONE,	NULL	,0x0f0f,2|C_GROUP_3DNOW_TYPE}, //0x43
	{R_M, C_NULL,		D__NONE,	D__NONE,	D__NONE,	NULL	,0x0f0f,2|C_GROUP_3DNOW_TYPE}, //0x44
	{R_M, C_NULL,		D__NONE,	D__NONE,	D__NONE,	NULL	,0x0f0f,2|C_GROUP_3DNOW_TYPE}, //0x45
	{R_M, C_NULL,		D__NONE,	D__NONE,	D__NONE,	NULL	,0x0f0f,2|C_GROUP_3DNOW_TYPE}, //0x46
	{R_M, C_NULL,		D__NONE,	D__NONE,	D__NONE,	NULL	,0x0f0f,2|C_GROUP_3DNOW_TYPE}, //0x47

	{R_M, C_NULL,		D__NONE,	D__NONE,	D__NONE,	NULL	,0x0f0f,2|C_GROUP_3DNOW_TYPE}, //0x48
	{R_M, C_NULL,		D__NONE,	D__NONE,	D__NONE,	NULL	,0x0f0f,2|C_GROUP_3DNOW_TYPE}, //0x49
	{R_M, C_NULL,		D__NONE,	D__NONE,	D__NONE,	NULL	,0x0f0f,2|C_GROUP_3DNOW_TYPE}, //0x4a
	{R_M, C_NULL,		D__NONE,	D__NONE,	D__NONE,	NULL	,0x0f0f,2|C_GROUP_3DNOW_TYPE}, //0x4b
	{R_M, C_NULL,		D__NONE,	D__NONE,	D__NONE,	NULL	,0x0f0f,2|C_GROUP_3DNOW_TYPE}, //0x4c
	{R_M, C_NULL,		D__NONE,	D__NONE,	D__NONE,	NULL	,0x0f0f,2|C_GROUP_3DNOW_TYPE}, //0x4d
	{R_M, C_NULL,		D__NONE,	D__NONE,	D__NONE,	NULL	,0x0f0f,2|C_GROUP_3DNOW_TYPE}, //0x4e
	{R_M, C_NULL,		D__NONE,	D__NONE,	D__NONE,	NULL	,0x0f0f,2|C_GROUP_3DNOW_TYPE}, //0x4f

	{R_M, C_NULL,		D__NONE,	D__NONE,	D__NONE,	NULL	,0x0f0f,2|C_GROUP_3DNOW_TYPE}, //0x50
	{R_M, C_NULL,		D__NONE,	D__NONE,	D__NONE,	NULL	,0x0f0f,2|C_GROUP_3DNOW_TYPE}, //0x51
	{R_M, C_NULL,		D__NONE,	D__NONE,	D__NONE,	NULL	,0x0f0f,2|C_GROUP_3DNOW_TYPE}, //0x52
	{R_M, C_NULL,		D__NONE,	D__NONE,	D__NONE,	NULL	,0x0f0f,2|C_GROUP_3DNOW_TYPE}, //0x53
	{R_M, C_NULL,		D__NONE,	D__NONE,	D__NONE,	NULL	,0x0f0f,2|C_GROUP_3DNOW_TYPE}, //0x54
	{R_M, C_NULL,		D__NONE,	D__NONE,	D__NONE,	NULL	,0x0f0f,2|C_GROUP_3DNOW_TYPE}, //0x55
	{R_M, C_NULL,		D__NONE,	D__NONE,	D__NONE,	NULL	,0x0f0f,2|C_GROUP_3DNOW_TYPE}, //0x56
	{R_M, C_NULL,		D__NONE,	D__NONE,	D__NONE,	NULL	,0x0f0f,2|C_GROUP_3DNOW_TYPE}, //0x57

	{R_M, C_NULL,		D__NONE,	D__NONE,	D__NONE,	NULL	,0x0f0f,2|C_GROUP_3DNOW_TYPE}, //0x58
	{R_M, C_NULL,		D__NONE,	D__NONE,	D__NONE,	NULL	,0x0f0f,2|C_GROUP_3DNOW_TYPE}, //0x59
	{R_M, C_NULL,		D__NONE,	D__NONE,	D__NONE,	NULL	,0x0f0f,2|C_GROUP_3DNOW_TYPE}, //0x5a
	{R_M, C_NULL,		D__NONE,	D__NONE,	D__NONE,	NULL	,0x0f0f,2|C_GROUP_3DNOW_TYPE}, //0x5b
	{R_M, C_NULL,		D__NONE,	D__NONE,	D__NONE,	NULL	,0x0f0f,2|C_GROUP_3DNOW_TYPE}, //0x5c
	{R_M, C_NULL,		D__NONE,	D__NONE,	D__NONE,	NULL	,0x0f0f,2|C_GROUP_3DNOW_TYPE}, //0x5d
	{R_M, C_NULL,		D__NONE,	D__NONE,	D__NONE,	NULL	,0x0f0f,2|C_GROUP_3DNOW_TYPE}, //0x5e
	{R_M, C_NULL,		D__NONE,	D__NONE,	D__NONE,	NULL	,0x0f0f,2|C_GROUP_3DNOW_TYPE}, //0x5f

	{R_M, C_NULL,		D__NONE,	D__NONE,	D__NONE,	NULL	,0x0f0f,2|C_GROUP_3DNOW_TYPE}, //0x60
	{R_M, C_NULL,		D__NONE,	D__NONE,	D__NONE,	NULL	,0x0f0f,2|C_GROUP_3DNOW_TYPE}, //0x61
	{R_M, C_NULL,		D__NONE,	D__NONE,	D__NONE,	NULL	,0x0f0f,2|C_GROUP_3DNOW_TYPE}, //0x62
	{R_M, C_NULL,		D__NONE,	D__NONE,	D__NONE,	NULL	,0x0f0f,2|C_GROUP_3DNOW_TYPE}, //0x63
	{R_M, C_NULL,		D__NONE,	D__NONE,	D__NONE,	NULL	,0x0f0f,2|C_GROUP_3DNOW_TYPE}, //0x64
	{R_M, C_NULL,		D__NONE,	D__NONE,	D__NONE,	NULL	,0x0f0f,2|C_GROUP_3DNOW_TYPE}, //0x65
	{R_M, C_NULL,		D__NONE,	D__NONE,	D__NONE,	NULL	,0x0f0f,2|C_GROUP_3DNOW_TYPE}, //0x66
	{R_M, C_NULL,		D__NONE,	D__NONE,	D__NONE,	NULL	,0x0f0f,2|C_GROUP_3DNOW_TYPE}, //0x67

	{R_M, C_NULL,		D__NONE,	D__NONE,	D__NONE,	NULL	,0x0f0f,2|C_GROUP_3DNOW_TYPE}, //0x68
	{R_M, C_NULL,		D__NONE,	D__NONE,	D__NONE,	NULL	,0x0f0f,2|C_GROUP_3DNOW_TYPE}, //0x69
	{R_M, C_NULL,		D__NONE,	D__NONE,	D__NONE,	NULL	,0x0f0f,2|C_GROUP_3DNOW_TYPE}, //0x6a
	{R_M, C_NULL,		D__NONE,	D__NONE,	D__NONE,	NULL	,0x0f0f,2|C_GROUP_3DNOW_TYPE}, //0x6b
	{R_M, C_NULL,		D__NONE,	D__NONE,	D__NONE,	NULL	,0x0f0f,2|C_GROUP_3DNOW_TYPE}, //0x6c
	{R_M, C_NULL,		D__NONE,	D__NONE,	D__NONE,	NULL	,0x0f0f,2|C_GROUP_3DNOW_TYPE}, //0x6d
	{R_M, C_NULL,		D__NONE,	D__NONE,	D__NONE,	NULL	,0x0f0f,2|C_GROUP_3DNOW_TYPE}, //0x6e
	{R_M, C_NULL,		D__NONE,	D__NONE,	D__NONE,	NULL	,0x0f0f,2|C_GROUP_3DNOW_TYPE}, //0x6f

	{R_M, C_NULL,		D__NONE,	D__NONE,	D__NONE,	NULL	,0x0f0f,2|C_GROUP_3DNOW_TYPE}, //0x70
	{R_M, C_NULL,		D__NONE,	D__NONE,	D__NONE,	NULL	,0x0f0f,2|C_GROUP_3DNOW_TYPE}, //0x71
	{R_M, C_NULL,		D__NONE,	D__NONE,	D__NONE,	NULL	,0x0f0f,2|C_GROUP_3DNOW_TYPE}, //0x72
	{R_M, C_NULL,		D__NONE,	D__NONE,	D__NONE,	NULL	,0x0f0f,2|C_GROUP_3DNOW_TYPE}, //0x73
	{R_M, C_NULL,		D__NONE,	D__NONE,	D__NONE,	NULL	,0x0f0f,2|C_GROUP_3DNOW_TYPE}, //0x74
	{R_M, C_NULL,		D__NONE,	D__NONE,	D__NONE,	NULL	,0x0f0f,2|C_GROUP_3DNOW_TYPE}, //0x75
	{R_M, C_NULL,		D__NONE,	D__NONE,	D__NONE,	NULL	,0x0f0f,2|C_GROUP_3DNOW_TYPE}, //0x76
	{R_M, C_NULL,		D__NONE,	D__NONE,	D__NONE,	NULL	,0x0f0f,2|C_GROUP_3DNOW_TYPE}, //0x77

	{R_M, C_NULL,		D__NONE,	D__NONE,	D__NONE,	NULL	,0x0f0f,2|C_GROUP_3DNOW_TYPE}, //0x78
	{R_M, C_NULL,		D__NONE,	D__NONE,	D__NONE,	NULL	,0x0f0f,2|C_GROUP_3DNOW_TYPE}, //0x79
	{R_M, C_NULL,		D__NONE,	D__NONE,	D__NONE,	NULL	,0x0f0f,2|C_GROUP_3DNOW_TYPE}, //0x7a
	{R_M, C_NULL,		D__NONE,	D__NONE,	D__NONE,	NULL	,0x0f0f,2|C_GROUP_3DNOW_TYPE}, //0x7b
	{R_M, C_NULL,		D__NONE,	D__NONE,	D__NONE,	NULL	,0x0f0f,2|C_GROUP_3DNOW_TYPE}, //0x7c
	{R_M, C_NULL,		D__NONE,	D__NONE,	D__NONE,	NULL	,0x0f0f,2|C_GROUP_3DNOW_TYPE}, //0x7d
	{R_M, C_NULL,		D__NONE,	D__NONE,	D__NONE,	NULL	,0x0f0f,2|C_GROUP_3DNOW_TYPE}, //0x7e
	{R_M, C_NULL,		D__NONE,	D__NONE,	D__NONE,	NULL	,0x0f0f,2|C_GROUP_3DNOW_TYPE}, //0x7f

	{R_M, C_NULL,		D__NONE,	D__NONE,	D__NONE,	NULL	,0x0f0f,2|C_GROUP_3DNOW_TYPE}, //0x80
	{R_M, C_NULL,		D__NONE,	D__NONE,	D__NONE,	NULL	,0x0f0f,2|C_GROUP_3DNOW_TYPE}, //0x81
	{R_M, C_NULL,		D__NONE,	D__NONE,	D__NONE,	NULL	,0x0f0f,2|C_GROUP_3DNOW_TYPE}, //0x82
	{R_M, C_NULL,		D__NONE,	D__NONE,	D__NONE,	NULL	,0x0f0f,2|C_GROUP_3DNOW_TYPE}, //0x83
	{R_M, C_NULL,		D__NONE,	D__NONE,	D__NONE,	NULL	,0x0f0f,2|C_GROUP_3DNOW_TYPE}, //0x84
	{R_M, C_NULL,		D__NONE,	D__NONE,	D__NONE,	NULL	,0x0f0f,2|C_GROUP_3DNOW_TYPE}, //0x85
	{R_M, C_NULL,		D__NONE,	D__NONE,	D__NONE,	NULL	,0x0f0f,2|C_GROUP_3DNOW_TYPE}, //0x86
	{R_M, C_NULL,		D__NONE,	D__NONE,	D__NONE,	NULL	,0x0f0f,2|C_GROUP_3DNOW_TYPE}, //0x87

	{R_M, C_NULL,		D__NONE,	D__NONE,	D__NONE,	NULL	,0x0f0f,2|C_GROUP_3DNOW_TYPE}, //0x88
	{R_M, C_NULL,		D__NONE,	D__NONE,	D__NONE,	NULL	,0x0f0f,2|C_GROUP_3DNOW_TYPE}, //0x89
	{R_M, C_PFNACC,		D__Pq,		D__Qq,		D__NONE,	"PFNACC"	,0x0f0f,2|C_GROUP_3DNOW_TYPE|(0x8a<<16)}, //0x8a
	{R_M, C_NULL,		D__NONE,	D__NONE,	D__NONE,	NULL	,0x0f0f,2|C_GROUP_3DNOW_TYPE}, //0x8b
	{R_M, C_NULL,		D__NONE,	D__NONE,	D__NONE,	NULL	,0x0f0f,2|C_GROUP_3DNOW_TYPE}, //0x8c
	{R_M, C_NULL,		D__NONE,	D__NONE,	D__NONE,	NULL	,0x0f0f,2|C_GROUP_3DNOW_TYPE}, //0x8d
	{R_M, C_PFPNACC,	D__Pq,		D__Qq,		D__NONE,	"PFPNACC"	,0x0f0f,2|C_GROUP_3DNOW_TYPE|(0x8e<<16)}, //0x8e
	{R_M, C_NULL,		D__NONE,	D__NONE,	D__NONE,	NULL	,0x0f0f,2|C_GROUP_3DNOW_TYPE}, //0x8f

	{R_M, C_PFCMPGE,	D__Pq,		D__Qq,		D__NONE,	"PFCMPGE"	,0x0f0f,2|C_GROUP_3DNOW_TYPE|(0x90<<16)}, //0x90
	{R_M, C_NULL,		D__NONE,	D__NONE,	D__NONE,	NULL	,0x0f0f,2|C_GROUP_3DNOW_TYPE}, //0x91
	{R_M, C_NULL,		D__NONE,	D__NONE,	D__NONE,	NULL	,0x0f0f,2|C_GROUP_3DNOW_TYPE}, //0x92
	{R_M, C_NULL,		D__NONE,	D__NONE,	D__NONE,	NULL	,0x0f0f,2|C_GROUP_3DNOW_TYPE}, //0x93
	{R_M, C_PFMIN,		D__Pq,		D__Qq,		D__NONE,	"PFMIN"	,0x0f0f,2|C_GROUP_3DNOW_TYPE|(0x94<<16)}, //0x94
	{R_M, C_NULL,		D__NONE,	D__NONE,	D__NONE,	NULL	,0x0f0f,2|C_GROUP_3DNOW_TYPE}, //0x95
	{R_M, C_PFRCP,		D__Pq,		D__Qq,		D__NONE,	"PFRCP"	,0x0f0f,2|C_GROUP_3DNOW_TYPE|(0x96<<16)}, //0x96
	{R_M, C_PFRSQRT,	D__Pq,		D__Qq,		D__NONE,	"PFRSQRT"	,0x0f0f,2|C_GROUP_3DNOW_TYPE|(0x97<<16)}, //0x97

	{R_M, C_NULL,		D__NONE,	D__NONE,	D__NONE,	NULL	,0x0f0f,2|C_GROUP_3DNOW_TYPE}, //0x98
	{R_M, C_NULL,		D__NONE,	D__NONE,	D__NONE,	NULL	,0x0f0f,2|C_GROUP_3DNOW_TYPE}, //0x99
	{R_M, C_PFSUB,		D__Pq,		D__Qq,		D__NONE,	"PFSUB"	,0x0f0f,2|C_GROUP_3DNOW_TYPE|(0x9a<<16)}, //0x9a
	{R_M, C_NULL,		D__NONE,	D__NONE,	D__NONE,	NULL	,0x0f0f,2|C_GROUP_3DNOW_TYPE}, //0x9b
	{R_M, C_NULL,		D__NONE,	D__NONE,	D__NONE,	NULL	,0x0f0f,2|C_GROUP_3DNOW_TYPE}, //0x9c
	{R_M, C_NULL,		D__NONE,	D__NONE,	D__NONE,	NULL	,0x0f0f,2|C_GROUP_3DNOW_TYPE}, //0x9d
	{R_M, C_PFADD,		D__Pq,		D__Qq,		D__NONE,	"PFADD"	,0x0f0f,2|C_GROUP_3DNOW_TYPE|(0x9e<<16)}, //0x9e
	{R_M, C_NULL,		D__NONE,	D__NONE,	D__NONE,	NULL	,0x0f0f,2|C_GROUP_3DNOW_TYPE}, //0x9f

	{R_M, C_PFCMPGT,	D__Pq,		D__Qq,		D__NONE,	"PFCMPGT"	,0x0f0f,2|C_GROUP_3DNOW_TYPE|(0xa0<<16)}, //0xa0
	{R_M, C_NULL,		D__NONE,	D__NONE,	D__NONE,	NULL	,0x0f0f,2|C_GROUP_3DNOW_TYPE}, //0xa1
	{R_M, C_NULL,		D__NONE,	D__NONE,	D__NONE,	NULL	,0x0f0f,2|C_GROUP_3DNOW_TYPE}, //0xa2
	{R_M, C_NULL,		D__NONE,	D__NONE,	D__NONE,	NULL	,0x0f0f,2|C_GROUP_3DNOW_TYPE}, //0xa3
	{R_M, C_PFMAX,		D__Pq,		D__Qq,		D__NONE,	"PFMAX"	,0x0f0f,2|C_GROUP_3DNOW_TYPE|(0xa4<<16)}, //0xa4
	{R_M, C_NULL,		D__NONE,	D__NONE,	D__NONE,	NULL	,0x0f0f,2|C_GROUP_3DNOW_TYPE}, //0xa5
	{R_M, C_PFRCPIT1,	D__Pq,		D__Qq,		D__NONE,	"PFRCPIT1"	,0x0f0f,2|C_GROUP_3DNOW_TYPE|(0xa6<<16)}, //0xa6
	{R_M, C_PFRSQIT1,	D__Pq,		D__Qq,		D__NONE,	"PFRSQIT1"	,0x0f0f,2|C_GROUP_3DNOW_TYPE|(0xa7<<16)}, //0xa7

	{R_M, C_NULL,		D__NONE,	D__NONE,	D__NONE,	NULL	,0x0f0f,2|C_GROUP_3DNOW_TYPE}, //0xa8
	{R_M, C_NULL,		D__NONE,	D__NONE,	D__NONE,	NULL	,0x0f0f,2|C_GROUP_3DNOW_TYPE}, //0xa9
	{R_M, C_PFSUBR,		D__Pq,		D__Qq,		D__NONE,	"PFSUBR"	,0x0f0f,2|C_GROUP_3DNOW_TYPE|(0xaa<<16)}, //0xaa
	{R_M, C_NULL,		D__NONE,	D__NONE,	D__NONE,	NULL	,0x0f0f,2|C_GROUP_3DNOW_TYPE}, //0xab
	{R_M, C_NULL,		D__NONE,	D__NONE,	D__NONE,	NULL	,0x0f0f,2|C_GROUP_3DNOW_TYPE}, //0xac
	{R_M, C_NULL,		D__NONE,	D__NONE,	D__NONE,	NULL	,0x0f0f,2|C_GROUP_3DNOW_TYPE}, //0xad
	{R_M, C_PFACC,		D__Pq,		D__Qq,		D__NONE,	"PFACC"	,0x0f0f,2|C_GROUP_3DNOW_TYPE|(0xae<<16)}, //0xae
	{R_M, C_NULL,		D__NONE,	D__NONE,	D__NONE,	NULL	,0x0f0f,2|C_GROUP_3DNOW_TYPE}, //0xaf

	{R_M, C_PFCMPEQ,	D__Pq,		D__Qq,		D__NONE,	"PFCMPEQ"	,0x0f0f,2|C_GROUP_3DNOW_TYPE|(0xb0<<16)}, //0xb0
	{R_M, C_NULL,		D__NONE,	D__NONE,	D__NONE,	NULL	,0x0f0f,2|C_GROUP_3DNOW_TYPE}, //0xb1
	{R_M, C_NULL,		D__NONE,	D__NONE,	D__NONE,	NULL	,0x0f0f,2|C_GROUP_3DNOW_TYPE}, //0xb2
	{R_M, C_NULL,		D__NONE,	D__NONE,	D__NONE,	NULL	,0x0f0f,2|C_GROUP_3DNOW_TYPE}, //0xb3
	{R_M, C_PFMUL,		D__Pq,		D__Qq,		D__NONE,	"PFMUL"	,0x0f0f,2|C_GROUP_3DNOW_TYPE|(0xb4<<16)}, //0xb4
	{R_M, C_NULL,		D__NONE,	D__NONE,	D__NONE,	NULL	,0x0f0f,2|C_GROUP_3DNOW_TYPE}, //0xb5
	{R_M, C_PFRCPIT2,	D__Pq,		D__Qq,		D__NONE,	"PFRCPIT2"	,0x0f0f,2|C_GROUP_3DNOW_TYPE|(0xb6<<16)}, //0xb6
	{R_M, C_PMULHRW,	D__Pq,		D__Qq,		D__NONE,	"PMULHRW"	,0x0f0f,2|C_GROUP_3DNOW_TYPE|(0xb7<<16)}, //0xb7

	{R_M, C_NULL,		D__NONE,	D__NONE,	D__NONE,	NULL	,0x0f0f,2|C_GROUP_3DNOW_TYPE}, //0xb8
	{R_M, C_NULL,		D__NONE,	D__NONE,	D__NONE,	NULL	,0x0f0f,2|C_GROUP_3DNOW_TYPE}, //0xb9
	{R_M, C_NULL,		D__NONE,	D__NONE,	D__NONE,	NULL	,0x0f0f,2|C_GROUP_3DNOW_TYPE}, //0xba
	{R_M, C_PSWAPD,		D__Pq,		D__Qq,		D__NONE,	"PSWAPD"	,0x0f0f,2|C_GROUP_3DNOW_TYPE|(0xbb<<16)}, //0xbb
	{R_M, C_NULL,		D__NONE,	D__NONE,	D__NONE,	NULL	,0x0f0f,2|C_GROUP_3DNOW_TYPE}, //0xbc
	{R_M, C_NULL,		D__NONE,	D__NONE,	D__NONE,	NULL	,0x0f0f,2|C_GROUP_3DNOW_TYPE}, //0xbd
	{R_M, C_NULL,		D__NONE,	D__NONE,	D__NONE,	NULL	,0x0f0f,2|C_GROUP_3DNOW_TYPE}, //0xbe
	{R_M, C_PAVGUSB,	D__Pq,		D__Qq,		D__NONE,	"PAVGUSB"	,0x0f0f,2|C_GROUP_3DNOW_TYPE|(0xbf<<16)}, //0xbf

	{R_M, C_NULL,		D__NONE,	D__NONE,	D__NONE,	NULL	,0x0f0f,2|C_GROUP_3DNOW_TYPE}, //0xc0
	{R_M, C_NULL,		D__NONE,	D__NONE,	D__NONE,	NULL	,0x0f0f,2|C_GROUP_3DNOW_TYPE}, //0xc1
	{R_M, C_NULL,		D__NONE,	D__NONE,	D__NONE,	NULL	,0x0f0f,2|C_GROUP_3DNOW_TYPE}, //0xc2
	{R_M, C_NULL,		D__NONE,	D__NONE,	D__NONE,	NULL	,0x0f0f,2|C_GROUP_3DNOW_TYPE}, //0xc3
	{R_M, C_NULL,		D__NONE,	D__NONE,	D__NONE,	NULL	,0x0f0f,2|C_GROUP_3DNOW_TYPE}, //0xc4
	{R_M, C_NULL,		D__NONE,	D__NONE,	D__NONE,	NULL	,0x0f0f,2|C_GROUP_3DNOW_TYPE}, //0xc5
	{R_M, C_NULL,		D__NONE,	D__NONE,	D__NONE,	NULL	,0x0f0f,2|C_GROUP_3DNOW_TYPE}, //0xc6
	{R_M, C_NULL,		D__NONE,	D__NONE,	D__NONE,	NULL	,0x0f0f,2|C_GROUP_3DNOW_TYPE}, //0xc7

	{R_M, C_NULL,		D__NONE,	D__NONE,	D__NONE,	NULL	,0x0f0f,2|C_GROUP_3DNOW_TYPE}, //0xc8
	{R_M, C_NULL,		D__NONE,	D__NONE,	D__NONE,	NULL	,0x0f0f,2|C_GROUP_3DNOW_TYPE}, //0xc9
	{R_M, C_NULL,		D__NONE,	D__NONE,	D__NONE,	NULL	,0x0f0f,2|C_GROUP_3DNOW_TYPE}, //0xca
	{R_M, C_NULL,		D__NONE,	D__NONE,	D__NONE,	NULL	,0x0f0f,2|C_GROUP_3DNOW_TYPE}, //0xcb
	{R_M, C_NULL,		D__NONE,	D__NONE,	D__NONE,	NULL	,0x0f0f,2|C_GROUP_3DNOW_TYPE}, //0xcc
	{R_M, C_NULL,		D__NONE,	D__NONE,	D__NONE,	NULL	,0x0f0f,2|C_GROUP_3DNOW_TYPE}, //0xcd
	{R_M, C_NULL,		D__NONE,	D__NONE,	D__NONE,	NULL	,0x0f0f,2|C_GROUP_3DNOW_TYPE}, //0xce
	{R_M, C_NULL,		D__NONE,	D__NONE,	D__NONE,	NULL	,0x0f0f,2|C_GROUP_3DNOW_TYPE}, //0xcf

	{R_M, C_NULL,		D__NONE,	D__NONE,	D__NONE,	NULL	,0x0f0f,2|C_GROUP_3DNOW_TYPE}, //0xd0
	{R_M, C_NULL,		D__NONE,	D__NONE,	D__NONE,	NULL	,0x0f0f,2|C_GROUP_3DNOW_TYPE}, //0xd1
	{R_M, C_NULL,		D__NONE,	D__NONE,	D__NONE,	NULL	,0x0f0f,2|C_GROUP_3DNOW_TYPE}, //0xd2
	{R_M, C_NULL,		D__NONE,	D__NONE,	D__NONE,	NULL	,0x0f0f,2|C_GROUP_3DNOW_TYPE}, //0xd3
	{R_M, C_NULL,		D__NONE,	D__NONE,	D__NONE,	NULL	,0x0f0f,2|C_GROUP_3DNOW_TYPE}, //0xd4
	{R_M, C_NULL,		D__NONE,	D__NONE,	D__NONE,	NULL	,0x0f0f,2|C_GROUP_3DNOW_TYPE}, //0xd5
	{R_M, C_NULL,		D__NONE,	D__NONE,	D__NONE,	NULL	,0x0f0f,2|C_GROUP_3DNOW_TYPE}, //0xd6
	{R_M, C_NULL,		D__NONE,	D__NONE,	D__NONE,	NULL	,0x0f0f,2|C_GROUP_3DNOW_TYPE}, //0xd7

	{R_M, C_NULL,		D__NONE,	D__NONE,	D__NONE,	NULL	,0x0f0f,2|C_GROUP_3DNOW_TYPE}, //0xd8
	{R_M, C_NULL,		D__NONE,	D__NONE,	D__NONE,	NULL	,0x0f0f,2|C_GROUP_3DNOW_TYPE}, //0xd9
	{R_M, C_NULL,		D__NONE,	D__NONE,	D__NONE,	NULL	,0x0f0f,2|C_GROUP_3DNOW_TYPE}, //0xda
	{R_M, C_NULL,		D__NONE,	D__NONE,	D__NONE,	NULL	,0x0f0f,2|C_GROUP_3DNOW_TYPE}, //0xdb
	{R_M, C_NULL,		D__NONE,	D__NONE,	D__NONE,	NULL	,0x0f0f,2|C_GROUP_3DNOW_TYPE}, //0xdc
	{R_M, C_NULL,		D__NONE,	D__NONE,	D__NONE,	NULL	,0x0f0f,2|C_GROUP_3DNOW_TYPE}, //0xdd
	{R_M, C_NULL,		D__NONE,	D__NONE,	D__NONE,	NULL	,0x0f0f,2|C_GROUP_3DNOW_TYPE}, //0xde
	{R_M, C_NULL,		D__NONE,	D__NONE,	D__NONE,	NULL	,0x0f0f,2|C_GROUP_3DNOW_TYPE}, //0xdf

	{R_M, C_NULL,		D__NONE,	D__NONE,	D__NONE,	NULL	,0x0f0f,2|C_GROUP_3DNOW_TYPE}, //0xe0
	{R_M, C_NULL,		D__NONE,	D__NONE,	D__NONE,	NULL	,0x0f0f,2|C_GROUP_3DNOW_TYPE}, //0xe1
	{R_M, C_NULL,		D__NONE,	D__NONE,	D__NONE,	NULL	,0x0f0f,2|C_GROUP_3DNOW_TYPE}, //0xe2
	{R_M, C_NULL,		D__NONE,	D__NONE,	D__NONE,	NULL	,0x0f0f,2|C_GROUP_3DNOW_TYPE}, //0xe3
	{R_M, C_NULL,		D__NONE,	D__NONE,	D__NONE,	NULL	,0x0f0f,2|C_GROUP_3DNOW_TYPE}, //0xe4
	{R_M, C_NULL,		D__NONE,	D__NONE,	D__NONE,	NULL	,0x0f0f,2|C_GROUP_3DNOW_TYPE}, //0xe5
	{R_M, C_NULL,		D__NONE,	D__NONE,	D__NONE,	NULL	,0x0f0f,2|C_GROUP_3DNOW_TYPE}, //0xe6
	{R_M, C_NULL,		D__NONE,	D__NONE,	D__NONE,	NULL	,0x0f0f,2|C_GROUP_3DNOW_TYPE}, //0xe7

	{R_M, C_NULL,		D__NONE,	D__NONE,	D__NONE,	NULL	,0x0f0f,2|C_GROUP_3DNOW_TYPE}, //0xe8
	{R_M, C_NULL,		D__NONE,	D__NONE,	D__NONE,	NULL	,0x0f0f,2|C_GROUP_3DNOW_TYPE}, //0xe9
	{R_M, C_NULL,		D__NONE,	D__NONE,	D__NONE,	NULL	,0x0f0f,2|C_GROUP_3DNOW_TYPE}, //0xea
	{R_M, C_NULL,		D__NONE,	D__NONE,	D__NONE,	NULL	,0x0f0f,2|C_GROUP_3DNOW_TYPE}, //0xeb
	{R_M, C_NULL,		D__NONE,	D__NONE,	D__NONE,	NULL	,0x0f0f,2|C_GROUP_3DNOW_TYPE}, //0xec
	{R_M, C_NULL,		D__NONE,	D__NONE,	D__NONE,	NULL	,0x0f0f,2|C_GROUP_3DNOW_TYPE}, //0xed
	{R_M, C_NULL,		D__NONE,	D__NONE,	D__NONE,	NULL	,0x0f0f,2|C_GROUP_3DNOW_TYPE}, //0xee
	{R_M, C_NULL,		D__NONE,	D__NONE,	D__NONE,	NULL	,0x0f0f,2|C_GROUP_3DNOW_TYPE}, //0xef

	{R_M, C_NULL,		D__NONE,	D__NONE,	D__NONE,	NULL	,0x0f0f,2|C_GROUP_3DNOW_TYPE}, //0xf0
	{R_M, C_NULL,		D__NONE,	D__NONE,	D__NONE,	NULL	,0x0f0f,2|C_GROUP_3DNOW_TYPE}, //0xf1
	{R_M, C_NULL,		D__NONE,	D__NONE,	D__NONE,	NULL	,0x0f0f,2|C_GROUP_3DNOW_TYPE}, //0xf2
	{R_M, C_NULL,		D__NONE,	D__NONE,	D__NONE,	NULL	,0x0f0f,2|C_GROUP_3DNOW_TYPE}, //0xf3
	{R_M, C_NULL,		D__NONE,	D__NONE,	D__NONE,	NULL	,0x0f0f,2|C_GROUP_3DNOW_TYPE}, //0xf4
	{R_M, C_NULL,		D__NONE,	D__NONE,	D__NONE,	NULL	,0x0f0f,2|C_GROUP_3DNOW_TYPE}, //0xf5
	{R_M, C_NULL,		D__NONE,	D__NONE,	D__NONE,	NULL	,0x0f0f,2|C_GROUP_3DNOW_TYPE}, //0xf6
	{R_M, C_NULL,		D__NONE,	D__NONE,	D__NONE,	NULL	,0x0f0f,2|C_GROUP_3DNOW_TYPE}, //0xf7

	{R_M, C_NULL,		D__NONE,	D__NONE,	D__NONE,	NULL	,0x0f0f,2|C_GROUP_3DNOW_TYPE}, //0xf8
	{R_M, C_NULL,		D__NONE,	D__NONE,	D__NONE,	NULL	,0x0f0f,2|C_GROUP_3DNOW_TYPE}, //0xf9
	{R_M, C_NULL,		D__NONE,	D__NONE,	D__NONE,	NULL	,0x0f0f,2|C_GROUP_3DNOW_TYPE}, //0xfa
	{R_M, C_NULL,		D__NONE,	D__NONE,	D__NONE,	NULL	,0x0f0f,2|C_GROUP_3DNOW_TYPE}, //0xfb
	{R_M, C_NULL,		D__NONE,	D__NONE,	D__NONE,	NULL	,0x0f0f,2|C_GROUP_3DNOW_TYPE}, //0xfc
	{R_M, C_NULL,		D__NONE,	D__NONE,	D__NONE,	NULL	,0x0f0f,2|C_GROUP_3DNOW_TYPE}, //0xfd
	{R_M, C_NULL,		D__NONE,	D__NONE,	D__NONE,	NULL	,0x0f0f,2|C_GROUP_3DNOW_TYPE}, //0xfe
	{R_M, C_NULL,		D__NONE,	D__NONE,	D__NONE,	NULL	,0x0f0f,2|C_GROUP_3DNOW_TYPE}, //0xff

};

DIS_OPCODE_T Group0x0f[] =
{
	{R_M, C_GRP,	D__NONE,	D__NONE,	D__NONE,	(char*)Group0x0f00			,0x000f,2}, //0x00
	{R_M, C_GRP2,	D__NONE,	D__NONE,	D__NONE,	(char*)Group0x0f01			,0x010f,2}, //0x01
	{R_M, C_LAR,	D__Gv,		D__rEv,		D__NONE,	"LAR" 						,0x020f,2,MAKE_OP_RW_FLAG(OP_W,OP_R,0)}, //0x02
	{R_M, C_LSL,	D__Gv,		D__rEv,		D__NONE,	"LSL" 						,0x030f,2,MAKE_OP_RW_FLAG(OP_W,OP_R,0)}, //0x03
	{R_M, C_NULL,																		}, //0x04
	{ 0 | O_64, C_SYSCALL,D__NONE,	D__NONE,	D__NONE,	"SYSCALL"				,0x050f,2}, //0x05	
	{ 0 , C_CLTS,	D__NONE,	D__NONE,	D__NONE,	"CLTS" 						,0x060f,2}, //0x06
	{ 0 | O_64, C_SYSRET,	D__NONE,	D__NONE,	D__NONE,	"SYSRET"					,0x070f,2}, //0x07	

	{ 0 , C_INVD,	D__NONE,	D__NONE,	D__NONE,	"INVD" 						,0x080f,2}, //0x08
	{ 0 , C_WBINVD,	D__NONE,	D__NONE,	D__NONE,	"WBINVD" 					,0x090f,2}, //0x09
	{ 0 , C_NULL																		}, //0x0a
	{ 0 , C_UD2,	D__NONE,	D__NONE,	D__NONE,	"UD2",0x0b0f,2}, //0x0b
	{R_M, C_NULL,																		}, //0x0c
	{R_M, C_NOP,D__Ev,D__NONE,D__NONE,"NOP",0x0d0f,2			}, //0x0d
	{R_M, C_NULL,																		}, //0x0e
	{R_M, C_3DNOW,	D__Pq,		D__Qq,		D__NONE,(char*)	""						,0x0f0f,2}, //0x0f


	{R_M, C_GRP3,		D__NONE,	D__NONE,	D__NONE,	(char*)Group0x0f10			,0x100f,2}, //0x10
	{R_M, C_GRP3,		D__NONE,	D__NONE,	D__NONE,	(char*)Group0x0f11			,0x110f,2}, //0x11
	{R_M, C_GRP4,		D__NONE,	D__NONE,	D__NONE,	(char*)Group0x0f12			,0x120f,2}, //0x12
	{R_M, C_GRP3,		D__NONE,	D__NONE,	D__NONE,	(char*)Group0x0f13			,0x130f,2}, //0x13
	{R_M, C_GRP3,		D__NONE,	D__NONE,	D__NONE,	(char*)Group0x0f14			,0x140f,2}, //0x14
	{R_M, C_GRP3,		D__NONE,	D__NONE,	D__NONE,	(char*)Group0x0f15			,0x150f,2}, //0x15
	{R_M, C_GRP4,		D__NONE,	D__NONE,	D__NONE,	(char*)Group0x0f16			,0x160f,2}, //0x16 
	{R_M, C_GRP3,		D__NONE,	D__NONE,	D__NONE,	(char*)Group0x0f17			,0x170f,2}, //0x17

	{R_M, C_GRP,		D__NONE,	D__NONE,	D__NONE,	(char*)Group0x0f18,0x180f,2}, //0x18
	{ 0	, C_NULL,															}, //0x19
	{ 0	, C_NULL,															}, //0x1a
	{ 0	, C_NULL,															}, //0x1b
	{ 0	, C_NULL,															}, //0x1c
	{ 0	, C_NULL,															}, //0x1d
	{ 0	, C_NULL,															}, //0x1e
	{R_M, C_NOP,D__Ev,D__NONE,D__NONE,"NOP",0x1f0f,2			}, //0x1f

	{R_M|F_64, C_MOV,		D__Ry,		D__Cd,		D__NONE,	"MOV"	,0x200f,2,MAKE_OP_RW_FLAG(OP_W,OP_R,0)}, //0x20
	{R_M|F_64, C_MOV,		D__Ry,		D__Dd,		D__NONE,	"MOV"	,0x210f,2,MAKE_OP_RW_FLAG(OP_W,OP_R,0)}, //0x21
	{R_M|F_64, C_MOV,		D__Cd,		D__Ry,		D__NONE,	"MOV"	,0x220f,2,MAKE_OP_RW_FLAG(OP_W,OP_R,0)}, //0x22
	{R_M|F_64, C_MOV,		D__Dd,		D__Ry,		D__NONE,	"MOV"	,0x230f,2,MAKE_OP_RW_FLAG(OP_W,OP_R,0)}, //0x23
	{R_M|F_64, C_MOV,		D__Ry,		D__Td,		D__NONE,	"MOV"	,0x240f,2,MAKE_OP_RW_FLAG(OP_W,OP_R,0)}, //0x24
	{ 0 , C_NULL,													}, //0x25
	{R_M|F_64, C_MOV,		D__Td,		D__Ry,		D__NONE,	"MOV"	,0x260f,2,MAKE_OP_RW_FLAG(OP_W,OP_R,0)}, //0x26
	{R_M, C_NULL,													}, //0x27

	{R_M, C_GRP3,		D__NONE,	D__NONE,		D__NONE,	(char*)Group0x0f28	,0x280f,2}, //0x28
	{R_M, C_GRP3,		D__NONE,	D__NONE,		D__NONE,	(char*)Group0x0f29	,0x290f,2}, //0x29
	{R_M, C_GRP3,		D__NONE,	D__NONE,		D__NONE,	(char*)Group0x0f2a	,0x2a0f,2}, //0x2a
	{R_M, C_GRP3,		D__NONE,	D__NONE,		D__NONE,	(char*)Group0x0f2b	,0x2b0f,2}, //0x2b
	{R_M, C_GRP3,		D__NONE,	D__NONE,		D__NONE,	(char*)Group0x0f2c	,0x2c0f,2}, //0x2c
	{R_M, C_GRP3,		D__NONE,	D__NONE,		D__NONE,	(char*)Group0x0f2d	,0x2d0f,2}, //0x2d
	{R_M, C_GRP3,		D__NONE,	D__NONE,		D__NONE,	(char*)Group0x0f2e	,0x2e0f,2}, //0x2e
	{R_M, C_GRP3,		D__NONE,	D__NONE,		D__NONE,	(char*)Group0x0f2f	,0x2f0f,2}, //0x2f

	{ 0 , C_WRMSR,		D__NONE,	D__NONE,	D__NONE,	"WRMSR"				,0x300f,2}, //0x30
	{ 0 , C_RDTSC,		D__NONE,	D__NONE,	D__NONE,	"RDTSC"	 			,0x310f,2}, //0x31
	{ 0 , C_RDMSR,		D__NONE,	D__NONE,	D__NONE,	"RDMSR"				,0x320f,2}, //0x32
	{ 0 , C_RDPMC,		D__NONE,	D__NONE,	D__NONE,	"RDPMC"				,0x330f,2}, //0x33
	{ 0 , C_SYSENTER,	D__NONE,	D__NONE,	D__NONE,	"SYSENTER"			,0x340f,2}, //0x34
	{ 0 , C_SYSEXIT,	D__NONE,	D__NONE,	D__NONE,	"SYSEXIT"			,0x350f,2}, //0x35
	{ 0 , C_NULL,															}, //0x36
	{ 0 , C_GETSEC,		D__NONE,	D__NONE,	D__NONE,	"GETSEC"		,0x370f,2}, //0x37

	{R_M, C_3BYTE_0X38,D__NONE,	D__NONE,	D__NONE,		(char*)Group0x0f38	,0x380f,2}, //0x38
	{R_M, C_NULL,												}, //0x39
	{R_M, C_3BYTE_0X3A,D__NONE,	D__NONE,	D__NONE,		(char*)Group0x0f3a	,0x3a0f,2}, //0x3a
	{R_M, C_NULL,												}, //0x3b
	{R_M, C_NULL,												}, //0x3c
	{R_M, C_NULL,				 								}, //0x3d
	{R_M, C_NULL,												}, //0x3e
	{R_M, C_NULL,												}, //0x3f

	{R_M, C_CMOVtO,	D__Gv,		D__rEv,		D__tO,	"CMOVO" 	,0x400f,2,MAKE_OP_RW_FLAG(OP_RW,OP_R,0)}, //0x40
	{R_M, C_CMOVfO,	D__Gv,		D__rEv,		D__fO,	"CMOVNO" 	,0x410f,2,MAKE_OP_RW_FLAG(OP_RW,OP_R,0)}, //0x41
	{R_M, C_CMOVtC,	D__Gv,		D__rEv,		D__tC,	"CMOVB" 	,0x420f,2,MAKE_OP_RW_FLAG(OP_RW,OP_R,0)}, //0x42
	{R_M, C_CMOVfC,	D__Gv,		D__rEv,		D__fC,	"CMOVNB" 	,0x430f,2,MAKE_OP_RW_FLAG(OP_RW,OP_R,0)}, //0x43
	{R_M, C_CMOVtZ,	D__Gv,		D__rEv,		D__tZ,	"CMOVZ" 	,0x440f,2,MAKE_OP_RW_FLAG(OP_RW,OP_R,0)}, //0x44
	{R_M, C_CMOVfZ,	D__Gv,		D__rEv,		D__fZ,	"CMOVNZ" 	,0x450f,2,MAKE_OP_RW_FLAG(OP_RW,OP_R,0)}, //0x45
	{R_M, C_CMOVfA,	D__Gv,		D__rEv,		D__fA,	"CMOVBE" 	,0x460f,2,MAKE_OP_RW_FLAG(OP_RW,OP_R,0)}, //0x46
	{R_M, C_CMOVtA,	D__Gv,		D__rEv,		D__tA,	"CMOVA" 	,0x470f,2,MAKE_OP_RW_FLAG(OP_RW,OP_R,0)}, //0x47
	{R_M, C_CMOVtS,	D__Gv,		D__rEv,		D__tS,	"CMOVS" 	,0x480f,2,MAKE_OP_RW_FLAG(OP_RW,OP_R,0)}, //0x48
	{R_M, C_CMOVfS,	D__Gv,		D__rEv,		D__fS,	"CMOVNS" 	,0x490f,2,MAKE_OP_RW_FLAG(OP_RW,OP_R,0)}, //0x49
	{R_M, C_CMOVtP,	D__Gv,		D__rEv,		D__tP,	"CMOVP" 	,0x4a0f,2,MAKE_OP_RW_FLAG(OP_RW,OP_R,0)}, //0x4a
	{R_M, C_CMOVfP,	D__Gv,		D__rEv,		D__fP,	"CMOVNP" 	,0x4b0f,2,MAKE_OP_RW_FLAG(OP_RW,OP_R,0)}, //0x4b
	{R_M, C_CMOVtL,	D__Gv,		D__rEv,		D__tL,	"CMOVL" 	,0x4c0f,2,MAKE_OP_RW_FLAG(OP_RW,OP_R,0)}, //0x4c
	{R_M, C_CMOVfL,	D__Gv,		D__rEv,		D__fL,	"CMOVGE" 	,0x4d0f,2,MAKE_OP_RW_FLAG(OP_RW,OP_R,0)}, //0x4d
	{R_M, C_CMOVfG,	D__Gv,		D__rEv,		D__fG,	"CMOVLE" 	,0x4e0f,2,MAKE_OP_RW_FLAG(OP_RW,OP_R,0)}, //0x4e
	{R_M, C_CMOVtG,	D__Gv,		D__rEv,		D__tG,	"CMOVG" 	,0x4f0f,2,MAKE_OP_RW_FLAG(OP_RW,OP_R,0)}, //0x4f

	{R_M, C_GRP4,D__Ed,			D__Vps,		D__NONE,	(char*)Group0x0f50	,0x500f,2}, //0x50
	{R_M, C_GRP3,D__Vps,		D__Wps,		D__NONE,	(char*)Group0x0f51	,0x510f,2}, //0x51
	{R_M, C_GRP3,D__Vps,		D__Wps,		D__NONE,	(char*)Group0x0f52	,0x520f,2}, //0x52
	{R_M, C_GRP3,D__Vps,		D__Wps,		D__NONE,	(char*)Group0x0f53	,0x530f,2}, //0x53
	{R_M, C_GRP3,D__Vps,		D__Wps,		D__NONE,	(char*)Group0x0f54	,0x540f,2}, //0x54
	{R_M, C_GRP3,D__Vps,		D__Wps,		D__NONE,	(char*)Group0x0f55	,0x550f,2}, //0x55
	{R_M, C_GRP3,D__Vps,		D__Wps,		D__NONE,	(char*)Group0x0f56	,0x560f,2}, //0x56
	{R_M, C_GRP3,D__Vps,		D__Wps,		D__NONE,	(char*)Group0x0f57	,0x570f,2}, //0x57

	{R_M, C_GRP3,D__Vps,		D__Wps,		D__NONE,	(char*)Group0x0f58	,0x580f,2}, //0x58
	{R_M, C_GRP3,D__Vps,		D__Wps,		D__NONE,	(char*)Group0x0f59	,0x590f,2}, //0x59
	{R_M, C_GRP3,D__Vpd,		D__Wps,		D__NONE,	(char*)Group0x0f5a	,0x5a0f,2}, //0x5a
	{R_M, C_GRP3,D__Vps,		D__Wdq,		D__NONE,	(char*)Group0x0f5b	,0x5b0f,2}, //0x5b
	{R_M, C_GRP3,D__Vps,		D__Wps,		D__NONE,	(char*)Group0x0f5c	,0x5c0f,2}, //0x5c
	{R_M, C_GRP3,D__Vps,		D__Wps,		D__NONE,	(char*)Group0x0f5d	,0x5d0f,2}, //0x5d
	{R_M, C_GRP3,D__Vps,		D__Wps,		D__NONE,	(char*)Group0x0f5e	,0x5e0f,2}, //0x5e
	{R_M, C_GRP3,D__Vps,		D__Wps,		D__NONE,	(char*)Group0x0f5f	,0x5f0f,2}, //0x5f

	{R_M, C_GRP3,	D__NONE,	D__NONE,		D__NONE,	(char*)Group0x0f60,0x600f,2}, //0x60
	{R_M, C_GRP3,	D__NONE,	D__NONE,		D__NONE,	(char*)Group0x0f61,0x610f,2}, //0x61
	{R_M, C_GRP3,	D__NONE,	D__NONE,		D__NONE,	(char*)Group0x0f62,0x620f,2}, //0x62
	{R_M, C_GRP3,	D__NONE,	D__NONE,		D__NONE,	(char*)Group0x0f63,0x630f,2}, //0x63
	{R_M, C_GRP3,	D__NONE,	D__NONE,		D__NONE,	(char*)Group0x0f64,0x640f,2}, //0x64
	{R_M, C_GRP3,	D__NONE,	D__NONE,		D__NONE,	(char*)Group0x0f65,0x650f,2}, //0x65
	{R_M, C_GRP3,	D__NONE,	D__NONE,		D__NONE,	(char*)Group0x0f66,0x660f,2}, //0x66
	{R_M, C_GRP3,	D__NONE,	D__NONE,		D__NONE,	(char*)Group0x0f67,0x670f,2}, //0x67

	{R_M, C_GRP3,	D__NONE,	D__NONE,		D__NONE,	(char*)Group0x0f68,0x680f,2}, //0x68
	{R_M, C_GRP3,	D__NONE,	D__NONE,		D__NONE,	(char*)Group0x0f69,0x690f,2}, //0x69
	{R_M, C_GRP3,	D__NONE,	D__NONE,		D__NONE,	(char*)Group0x0f6a,0x6a0f,2}, //0x6a
	{R_M, C_GRP3,	D__NONE,	D__NONE,		D__NONE,	(char*)Group0x0f6b,0x6b0f,2}, //0x6b
	{R_M, C_GRP3,	D__NONE,	D__NONE,		D__NONE,	(char*)Group0x0f6c,0x6c0f,2}, //0x6c
	{R_M, C_GRP3,	D__NONE,	D__NONE,		D__NONE,	(char*)Group0x0f6d,0x6d0f,2}, //0x6d
	{R_M, C_GRP3,	D__NONE,	D__NONE,		D__NONE,	(char*)Group0x0f6e,0x6e0f,2}, //0x6e
	{R_M, C_GRP3,	D__NONE,	D__NONE,		D__NONE,	(char*)Group0x0f6f,0x6f0f,2}, //0x6f


	{R_M, C_GRP3,		D__NONE,		D__NONE,		D__NONE,	(char*)Group0x0f70		,0x700f,2}, //0x70 
	{R_M, C_GRP5,		D__NONE,		D__NONE,		D__NONE,	(char*)Group0x0f71		,0x710f,2}, //0x71
	{R_M, C_GRP5,		D__NONE,		D__NONE,		D__NONE,	(char*)Group0x0f72		,0x720f,2}, //0x72
	{R_M, C_GRP5,		D__NONE,		D__NONE,		D__NONE,	(char*)Group0x0f73		,0x730f,2}, //0x73
	{R_M, C_GRP3,		D__NONE,		D__NONE,		D__NONE,	(char*)Group0x0f74		,0x740f,2}, //0x74
	{R_M, C_GRP3,		D__NONE,		D__NONE,		D__NONE,	(char*)Group0x0f75		,0x750f,2}, //0x75
	{R_M, C_GRP3,		D__NONE,		D__NONE,		D__NONE,	(char*)Group0x0f76		,0x760f,2}, //0x76
	{ 0 , C_EMMS,		D__NONE,		D__NONE,		D__NONE,	"emms",0x770f,2}, //0x77




	{R_M, C_GRP3,	D__NONE,	D__NONE,	D__NONE,	(char*)Group0x0f78	,0x780f,2}, //0x78
	{R_M, C_GRP3,	D__NONE,	D__NONE,	D__NONE,	(char*)Group0x0f79	,0x790f,2}, //0x79
	{R_M, C_NULL,	D__NONE,	D__NONE,	D__NONE,	"MMX UD"	}, //0x7a
	{R_M, C_NULL,	D__NONE,	D__NONE,	D__NONE,	"MMX UD"	}, //0x7b
	{R_M, C_GRP3,	D__NONE,	D__NONE,	D__NONE,	(char*)Group0x0f7c	,0x7c0f,2}, //0x7c
	{R_M, C_GRP3,	D__NONE,	D__NONE,	D__NONE,	(char*)Group0x0f7d	,0x7d0f,2}, //0x7d
	{R_M, C_GRP3,	D__NONE,	D__NONE,	D__NONE,	(char*)Group0x0f7e		,0x7e0f,2}, //0x7e
	{R_M, C_GRP3,	D__NONE,	D__NONE,	D__NONE,	(char*)Group0x0f7f		,0x7f0f,2}, //0x7f

	{ 0 |Immediate_Jv|F_64, C_JtO,		D__Jz,		D__tO,	D__NONE,	"JO" 		,0x800f,2}, //0x80
	{ 0 |Immediate_Jv|F_64, C_JfO,		D__Jz,		D__fO,	D__NONE,	"JNO" 		,0x810f,2}, //0x81
	{ 0 |Immediate_Jv|F_64, C_JtC,		D__Jz,		D__tC,	D__NONE,	"JC" 		,0x820f,2}, //0x82
	{ 0 |Immediate_Jv|F_64, C_JfC,		D__Jz,		D__fC,	D__NONE,	"JNC" 		,0x830f,2}, //0x83
	{ 0 |Immediate_Jv|F_64, C_JtZ,		D__Jz,		D__tZ,	D__NONE,	"JZ" 		,0x840f,2}, //0x84
	{ 0 |Immediate_Jv|F_64, C_JfZ,		D__Jz,		D__fZ,	D__NONE,	"JNZ" 		,0x850f,2}, //0x85
	{ 0 |Immediate_Jv|F_64, C_JfA,		D__Jz,		D__fA,	D__NONE,	"JNA" 		,0x860f,2}, //0x86
	{ 0 |Immediate_Jv|F_64, C_JtA,		D__Jz,		D__tA,	D__NONE,	"JA" 		,0x870f,2}, //0x87
	{ 0 |Immediate_Jv|F_64, C_JtS,		D__Jz,		D__tS,	D__NONE,	"JS" 		,0x880f,2}, //0x88
	{ 0 |Immediate_Jv|F_64, C_JfS,		D__Jz,		D__fS,	D__NONE,	"JNS" 		,0x890f,2}, //0x89
	{ 0 |Immediate_Jv|F_64, C_JtP,		D__Jz,		D__tP,	D__NONE,	"JP" 		,0x8a0f,2}, //0x8a
	{ 0 |Immediate_Jv|F_64, C_JfP,		D__Jz,		D__fP,	D__NONE,	"JNP" 		,0x8b0f,2}, //0x8b
	{ 0 |Immediate_Jv|F_64, C_JtL,		D__Jz,		D__tL,	D__NONE,	"JL" 		,0x8c0f,2}, //0x8c
	{ 0 |Immediate_Jv|F_64, C_JfL,		D__Jz,		D__fL,	D__NONE,	"JNL" 		,0x8d0f,2}, //0x8d
	{ 0 |Immediate_Jv|F_64, C_JfG,		D__Jz,		D__fG,	D__NONE,	"JNG" 		,0x8e0f,2}, //0x8e
	{ 0 |Immediate_Jv|F_64, C_JtG,		D__Jz,		D__tG,	D__NONE,	"JG" 		,0x8f0f,2}, //0x8f

	{R_M, C_SETtO,	D__wEb,		D__tO,	D__NONE,	"SETO" 	,0x900f,2,MAKE_OP_RW_FLAG(OP_R,0,0)}, //0x90
	{R_M, C_SETfO,	D__wEb,		D__fO,	D__NONE,	"SETNO" ,0x910f,2,MAKE_OP_RW_FLAG(OP_R,0,0)}, //0x91
	{R_M, C_SETtC,	D__wEb,		D__tC,	D__NONE,	"SETC" 	,0x920f,2,MAKE_OP_RW_FLAG(OP_R,0,0)}, //0x92
	{R_M, C_SETfC,	D__wEb,		D__fC,	D__NONE,	"SETNC" ,0x930f,2,MAKE_OP_RW_FLAG(OP_R,0,0)}, //0x93
	{R_M, C_SETtZ,	D__wEb,		D__tZ,	D__NONE,	"SETZ" 	,0x940f,2,MAKE_OP_RW_FLAG(OP_R,0,0)}, //0x94
	{R_M, C_SETfZ,	D__wEb,		D__fZ,	D__NONE,	"SETNZ" ,0x950f,2,MAKE_OP_RW_FLAG(OP_R,0,0)}, //0x95
	{R_M, C_SETfA,	D__wEb,		D__fA,	D__NONE,	"SETNA" ,0x960f,2,MAKE_OP_RW_FLAG(OP_R,0,0)}, //0x96
	{R_M, C_SETtA,	D__wEb,		D__tA,	D__NONE,	"SETA" 	,0x970f,2,MAKE_OP_RW_FLAG(OP_R,0,0)}, //0x97
	{R_M, C_SETtS,	D__wEb,		D__tS,	D__NONE,	"SETS" 	,0x980f,2,MAKE_OP_RW_FLAG(OP_R,0,0)}, //0x98
	{R_M, C_SETfS,	D__wEb,		D__fS,	D__NONE,	"SETNS" ,0x990f,2,MAKE_OP_RW_FLAG(OP_R,0,0)}, //0x99
	{R_M, C_SETtP,	D__wEb,		D__tP,	D__NONE,	"SETP" 	,0x9a0f,2,MAKE_OP_RW_FLAG(OP_R,0,0)}, //0x9a
	{R_M, C_SETfP,	D__wEb,		D__fP,	D__NONE,	"SETNP" ,0x9b0f,2,MAKE_OP_RW_FLAG(OP_R,0,0)}, //0x9b
	{R_M, C_SETtL,	D__wEb,		D__tL,	D__NONE,	"SETL" 	,0x9c0f,2,MAKE_OP_RW_FLAG(OP_R,0,0)}, //0x9c
	{R_M, C_SETfL,	D__wEb,		D__fL,	D__NONE,	"SETNL" ,0x9d0f,2,MAKE_OP_RW_FLAG(OP_R,0,0)}, //0x9d
	{R_M, C_SETfG,	D__wEb,		D__fG,	D__NONE,	"SETNG" ,0x9e0f,2,MAKE_OP_RW_FLAG(OP_R,0,0)}, //0x9e
	{R_M, C_SETtG,	D__wEb,		D__tG,	D__NONE,	"SETG" 	,0x9f0f,2,MAKE_OP_RW_FLAG(OP_R,0,0)}, //0x9f

	{ 0 | D_64 , C_PUSH,	D__FS,	D__NONE,	D__NONE,	"PUSH" 		,0xa00f,2,MAKE_OP_RW_FLAG(OP_R,0,0)}, //0xa0
	{ 0 | D_64 , C_POP,	D__FS,		D__NONE,	D__NONE,	"POP" 		,0xa10f,2,MAKE_OP_RW_FLAG(OP_W,0,0)}, //0xa1
	{ 0 , C_CPUID,	D__NONE,	D__NONE,	D__NONE,	"CPUID" 	,0xa20f,2}, //0xa2
	{R_M, C_BT,		D__rEv,		D__Gv,		D__NONE,	"BT" 		,0xa30f,2,MAKE_OP_RW_FLAG(OP_R,OP_R,0)}, //0xa3
	{R_M |Immediate_Ib, C_SHLD,	D__Ev,		D__Gv,		D__Ib,	"SHLD" 		,0xa40f,2,MAKE_OP_RW_FLAG(OP_W,OP_R,OP_R)}, //0xa4
	{R_M |Immediate_Ib, C_SHLD,	D__Ev,		D__Gv,		D__CL,	"SHLD" 		,0xa50f,2,MAKE_OP_RW_FLAG(OP_W,OP_R,OP_R)}, //0xa5
	{ 0 , C_NULL													}, //0xa6
	{ 0 , C_NULL													}, //0xa7

	{ 0 | D_64 , C_PUSH,	D__GS,		D__NONE,	D__NONE,	"PUSP" 				,0xa80f,2,MAKE_OP_RW_FLAG(OP_R,0,0)}, //0xa8
	{ 0 | D_64 , C_POP,		D__GS,		D__NONE,	D__NONE,	"POP" 				,0xa90f,2,MAKE_OP_RW_FLAG(OP_W,0,0)}, //0xa9
	{ 0 , C_RSM,	D__NONE,	D__NONE,	D__NONE,	"RSM" 						,0xaa0f,2}, //0xaa
	{R_M, C_BTS,	D__Ev,		D__Gv,		D__NONE,	"BTS" 						,0xab0f,2,MAKE_OP_RW_FLAG(OP_RW,OP_R,0)}, //0xab
	{R_M |Immediate_Ib, C_SHRD,	D__Ev,		D__Gv,		D__Ib,		"SHRD" 			,0xac0f,2,MAKE_OP_RW_FLAG(OP_W,OP_R,OP_R)}, //0xac
	{R_M, C_SHRD,	D__Ev,		D__Gv,		D__CL,		"SHRD" 						,0xad0f,2,MAKE_OP_RW_FLAG(OP_W,OP_R,OP_R)}, //0xad
	{R_M, C_GRP1,	D__NONE,	D__NONE,	D__NONE,	(char*)Group0x0fae			,0xae0f,2}, //0xae
	{R_M, C_IMUL,	D__Gv,		D__rEv,		D__NONE,	"IMUL" 						,0xaf0f,2,MAKE_OP_RW_FLAG(OP_RW,OP_R,0)}, //0xaf

	{R_M, C_CMPXCHG,	D__Eb,		D__Gb,		D__NONE,	"CMPXCHG" 				,0xb00f,2,MAKE_OP_RW_FLAG(OP_RW,OP_RW,0)}, //0xb0
	{R_M, C_CMPXCHG,	D__Ev,		D__Gv,		D__NONE,	"CMPXCHG" 				,0xb10f,2,MAKE_OP_RW_FLAG(OP_RW,OP_RW,0)}, //0xb1
	{R_M, C_LSS,		D__Gv,		D__rMp,		D__NONE,	"LSS" 					,0xb20f,2,MAKE_OP_RW_FLAG(OP_W,OP_R,0)}, //0xb2
	{R_M, C_BTR,		D__Ev,		D__Gv,		D__NONE,	"BTR" 					,0xb30f,2,MAKE_OP_RW_FLAG(OP_W,OP_R,0)}, //0xb3
	{R_M, C_LFS,		D__Gv,		D__rMp,		D__NONE,	"LFS" 					,0xb40f,2,MAKE_OP_RW_FLAG(OP_W,OP_R,0)}, //0xb4
	{R_M, C_LGS,		D__Gv,		D__rMp,		D__NONE,	"LGS" 					,0xb50f,2,MAKE_OP_RW_FLAG(OP_W,OP_R,0)}, //0xb5
	{R_M, C_MOVZX,		D__Gv,		D__rEb,		D__NONE,	"MOVZX" 				,0xb60f,2,MAKE_OP_RW_FLAG(OP_W,OP_R,0)}, //0xb6
	{R_M, C_MOVZX,		D__Gv,		D__rEw,		D__NONE,	"MOVZX" 				,0xb70f,2,MAKE_OP_RW_FLAG(OP_W,OP_R,0)}, //0xb7




	{R_M, C_GRP3,		D__NONE,	D__NONE,	D__NONE,	(char*)Group0x0fb8				,0xb80f,2}, //0xb8
	{R_M, C_NULL																					}, //0xb9
	{R_M |Immediate_Ib, C_GRP,		D__Ev,		D__Ib,		D__NONE,	(char*)Group0x0fba		,0xba0f,2}, //0xba
	{R_M, C_BTC,		D__Ev,		D__Gv,		D__NONE,	"BTC" 					,0xbb0f,2,MAKE_OP_RW_FLAG(OP_RW,OP_R,0)}, //0xbb
	{R_M, C_BSF,		D__Gv,		D__Ev,		D__NONE,	"BSF" 					,0xbc0f,2,MAKE_OP_RW_FLAG(OP_W,OP_R,0)}, //0xbc
	{R_M, C_BSR,		D__Gv,		D__Ev,		D__NONE,	"BSR"					,0xbd0f,2,MAKE_OP_RW_FLAG(OP_W,OP_R,0)}, //0xbd
	{R_M, C_MOVSX,		D__Gv,		D__rEb,		D__NONE,	"MOVSX" 				,0xbe0f,2,MAKE_OP_RW_FLAG(OP_W,OP_R,0)}, //0xbe
	{R_M, C_MOVSX,		D__Gv,		D__rEw,		D__NONE,	"MOVSX" 				,0xbf0f,2,MAKE_OP_RW_FLAG(OP_W,OP_R,0)}, //0xbf

	{R_M, C_XADD,		D__Eb,		D__Gb,		D__NONE,	"XADD" 						,0xc00f,2,MAKE_OP_RW_FLAG(OP_RW,OP_R,0)}, //0xc0
	{R_M, C_XADD,		D__Ev,		D__Gv,		D__NONE,	"XADD" 						,0xc10f,2,MAKE_OP_RW_FLAG(OP_RW,OP_R,0)}, //0xc1
	{R_M, C_GRP3,		D__NONE,	D__NONE,	D__NONE,	(char*)Group0x0fc2			,0xc20f,2}, //0xc2
	{R_M, C_MOVNTI,		D__My,		D__Gy,		D__NONE,	"movnti"					,0xc30f,2,MAKE_OP_RW_FLAG(OP_W,OP_R,0)}, //no prefix 
	{R_M, C_GRP4,		D__NONE,	D__NONE,	D__NONE,	(char*)Group0x0fc4,0xc40f,2}, //0xc4
	{R_M, C_GRP3,		D__NONE,	D__NONE,	D__NONE,	(char*)Group0x0fc5,0xc50f,2}, //0xc5
	{R_M, C_GRP3,		D__NONE,	D__NONE,	D__NONE,	(char*)Group0x0fc6,0xc60f,2}, //0xc6
	{R_M, C_GRP5,		D__NONE,	D__NONE,	D__NONE,	(char*)Group0x0fc7,0xc70f,2}, //0xc7

	//D__RAX_EAX_R8_R8D,D__RCX_ECX_R9_R9D,D__RDX_EDX_R10_R10D,D__RBX_EBX_R11_R11D,D__RSP_ESP_R12_R12D,D__RBP_EBP_R13_R13D,D__RSI_ESI_R14_R14D,D__RDI_EDI_R15_R15D,

	{ 0 , C_BSWAP,		D__RAX_EAX_R8_R8D,			D__NONE,	D__NONE,	"BSWAP"	 ,0xc80f,2,MAKE_OP_RW_FLAG(OP_RW,0,0)}, //0xc8
	{ 0 , C_BSWAP,		D__RCX_ECX_R9_R9D,			D__NONE,	D__NONE,	"BSWAP"	 ,0xc90f,2,MAKE_OP_RW_FLAG(OP_RW,0,0)}, //0xc9
	{ 0 , C_BSWAP,		D__RDX_EDX_R10_R10D,		D__NONE,	D__NONE,	"BSWAP"	 ,0xca0f,2,MAKE_OP_RW_FLAG(OP_RW,0,0)}, //0xca
	{ 0 , C_BSWAP,		D__RBX_EBX_R11_R11D,		D__NONE,	D__NONE,	"BSWAP"	 ,0xcb0f,2,MAKE_OP_RW_FLAG(OP_RW,0,0)}, //0xcb
	{ 0 , C_BSWAP,		D__RSP_ESP_R12_R12D,		D__NONE,	D__NONE,	"BSWAP"	 ,0xcc0f,2,MAKE_OP_RW_FLAG(OP_RW,0,0)}, //0xcc
	{ 0 , C_BSWAP,		D__RBP_EBP_R13_R13D,		D__NONE,	D__NONE,	"BSWAP"	 ,0xcd0f,2,MAKE_OP_RW_FLAG(OP_RW,0,0)}, //0xcd
	{ 0 , C_BSWAP,		D__RSI_ESI_R14_R14D,		D__NONE,	D__NONE,	"BSWAP"	 ,0xce0f,2,MAKE_OP_RW_FLAG(OP_RW,0,0)}, //0xce
	{ 0 , C_BSWAP,		D__RDI_EDI_R15_R15D,		D__NONE,	D__NONE,	"BSWAP"	 ,0xcf0f,2,MAKE_OP_RW_FLAG(OP_RW,0,0)}, //0xcf

	{R_M, C_GRP3,		D__Pq,		D__Pq,		D__NONE,	(char*)Group0x0fd0		,0xd00f,2}, //0xd0
	{R_M, C_GRP3,		D__Pq,		D__Qq,		D__NONE,	(char*)Group0x0fd1		,0xd10f,2}, //0xd1
	{R_M, C_GRP3,		D__Pq,		D__Qq,		D__NONE,	(char*)Group0x0fd2		,0xd20f,2}, //0xd2
	{R_M, C_GRP3,		D__Pq,		D__Qq,		D__NONE,	(char*)Group0x0fd3		,0xd30f,2}, //0xd3
	{R_M, C_GRP3,		D__Pq,		D__Qq,		D__NONE,	(char*)Group0x0fd4		,0xd40f,2}, //0xd4
	{R_M, C_GRP3,		D__Pq,		D__Qq,		D__NONE,	(char*)Group0x0fd5		,0xd50f,2}, //0xd5
	{R_M, C_GRP3,		D__Wq,		D__Vq,		D__NONE,	(char*)Group0x0fd6		,0xd60f,2}, //0xd6
	{R_M, C_GRP3,		D__Gd,		D__Pq,		D__NONE,	(char*)Group0x0fd7		,0xd70f,2}, //0xd7

	{R_M, C_GRP3,		D__Pq,		D__Qq,		D__NONE,	(char*)Group0x0fd8,0xd80f,2}, //0xd8
	{R_M, C_GRP3,		D__Pq,		D__Qq,		D__NONE,	(char*)Group0x0fd9,0xd90f,2}, //0xd9
	{R_M, C_GRP3,		D__Pq,		D__Qq,		D__NONE,	(char*)Group0x0fda,0xda0f,2}, //0xda
	{R_M, C_GRP3,		D__Pq,		D__Qq,		D__NONE,	(char*)Group0x0fdb,0xdb0f,2}, //0xdb
	{R_M, C_GRP3,		D__Pq,		D__Qq,		D__NONE,	(char*)Group0x0fdc,0xdc0f,2}, //0xdc
	{R_M, C_GRP3,		D__Pq,		D__Qq,		D__NONE,	(char*)Group0x0fdd,0xdd0f,2}, //0xdd
	{R_M, C_GRP3,		D__Pq,		D__Qq,		D__NONE,	(char*)Group0x0fde,0xde0f,2}, //0xde
	{R_M, C_GRP3,		D__Pq,		D__Qq,		D__NONE,	(char*)Group0x0fdf,0xdf0f,2} , //0xdf

	{R_M, C_GRP3,		D__Pq,		D__Qq,		D__NONE,	(char*)Group0x0fe0			,0xe00f,2}, //0xe0
	{R_M, C_GRP3,		D__Pq,		D__Qq,		D__NONE,	(char*)Group0x0fe1			,0xe10f,2}, //0xe1
	{R_M, C_GRP3,		D__Pq,		D__Qq,		D__NONE,	(char*)Group0x0fe2			,0xe20f,2}, //0xe2
	{R_M, C_GRP3,		D__Pq,		D__Qq,		D__NONE,	(char*)Group0x0fe3			,0xe30f,2}, //0xe3
	{R_M, C_GRP3,		D__Pq,		D__Qq,		D__NONE,	(char*)Group0x0fe4			,0xe40f,2}, //0xe4
	{R_M, C_GRP3,		D__Pq,		D__Qq,		D__NONE,	(char*)Group0x0fe5			,0xe50f,2}, //0xe5
	{R_M, C_GRP3,		D__NONE,	D__NONE,	D__NONE,	(char*)Group0x0fe6			,0xe60f,2}, //0xe6
	{R_M, C_GRP3,		D__Wq,		D__Vq,		D__NONE,	(char*)Group0x0fe7			,0xe70f,2}, //0xe7

	{R_M, C_GRP3,		D__Pq,		D__Qq,		D__NONE,	(char*)Group0x0fe8			,0xe80f,2}, //0xe8
	{R_M, C_GRP3,		D__Pq,		D__Qq,		D__NONE,	(char*)Group0x0fe9			,0xe90f,2}, //0xe9
	{R_M, C_GRP3,		D__Pq,		D__Qq,		D__NONE,	(char*)Group0x0fea			,0xea0f,2}, //0xea
	{R_M, C_GRP3,		D__Pq,		D__Qq,		D__NONE,	(char*)Group0x0feb			,0xeb0f,2}, //0xeb
	{R_M, C_GRP3,		D__Pq,		D__Qq,		D__NONE,	(char*)Group0x0fec			,0xec0f,2}, //0xec
	{R_M, C_GRP3,		D__Pq,		D__Qq,		D__NONE,	(char*)Group0x0fed			,0xed0f,2}, //0xed
	{R_M, C_GRP3,		D__Pq,		D__Qq,		D__NONE,	(char*)Group0x0fee			,0xee0f,2}, //0xee
	{R_M, C_GRP3,		D__Pq,		D__Qq,		D__NONE,	(char*)Group0x0fef			,0xef0f,2}, //0xef

	{R_M, C_GRP4,		D__Pq,		D__Qq,		D__NONE,	(char*)Group0x0ff0			,0xf00f,2}, //0xf0
	{R_M, C_GRP3,		D__Pq,		D__Qq,		D__NONE,	(char*)Group0x0ff1			,0xf10f,2}, //0xf1
	{R_M, C_GRP3,		D__Pq,		D__Qq,		D__NONE,	(char*)Group0x0ff2			,0xf20f,2}, //0xf2
	{R_M, C_GRP3,		D__Pq,		D__Qq,		D__NONE,	(char*)Group0x0ff3			,0xf30f,2}, //0xf3
	{R_M, C_GRP3,		D__Pq,		D__Qq,		D__NONE,	(char*)Group0x0ff4			,0xf40f,2}, //0xf4
	{R_M, C_GRP3,		D__Pq,		D__Qq,		D__NONE,	(char*)Group0x0ff5			,0xf50f,2}, //0xf5
	{R_M, C_GRP3,		D__Pq,		D__Qq,		D__NONE,	(char*)Group0x0ff6			,0xf60f,2}, //0xf6
	{R_M, C_GRP3,		D__Ppi,		D__Qpi,		D__NONE,	(char*)Group0x0ff7			,0xf70f,2}, //0xf7

	{R_M, C_GRP3,		D__Pq,		D__Qq,		D__NONE,	(char*)Group0x0ff8			,0xf80f,2}, //0xf8
	{R_M, C_GRP3,		D__Pq,		D__Qq,		D__NONE,	(char*)Group0x0ff9			,0xf90f,2}, //0xf9
	{R_M, C_GRP3,		D__Pq,		D__Qq,		D__NONE,	(char*)Group0x0ffa			,0xfa0f,2}, //0xfa
	{R_M, C_GRP3,		D__Pq,		D__Qq,		D__NONE,	(char*)Group0x0ffb			,0xfb0f,2}, //0xfb
	{R_M, C_GRP3,		D__Pq,		D__Qq,		D__NONE,	(char*)Group0x0ffc			,0xfc0f,2}, //0xfc
	{R_M, C_GRP3,		D__Pq,		D__Qq,		D__NONE,	(char*)Group0x0ffd			,0xfd0f,2}, //0xfd
	{R_M, C_GRP3,		D__Pq,		D__Qq,		D__NONE,	(char*)Group0x0ffe			,0xfe0f,2}, //0xfe
	{R_M, C_NULL																				 }, //0xff

};
DIS_OPCODE_T Group0x63[]=
{
	{R_M|I_64, C_ARPL,	D__Ew,	D__Gw,		D__NONE,	"ARPL" 		,0x63,1,MAKE_OP_RW_FLAG(OP_W,OP_R,0)}, //0x63
	{R_M|O_64, C_MOVSXD,D__Gv,	D__Ev,		D__NONE,	"MOVSXD" 	,0x63,1,MAKE_OP_RW_FLAG(OP_W,OP_R,0)}, //0x63
};
DIS_OPCODE_T Group_main[] =
{
	{R_M, 	C_ADD,	D__Eb,		D__Gb,		D__NONE,	"ADD" 	,0x00,1,MAKE_OP_RW_FLAG(OP_RW,OP_R,0)}, //0x00
	{R_M, 	C_ADD,	D__Ev,		D__Gv,		D__NONE,	"ADD" 	,0x01,1,MAKE_OP_RW_FLAG(OP_RW,OP_R,0)}, //0x01
	{R_M, 	C_ADD,	D__Gb,		D__rEb,		D__NONE,	"ADD" 	,0x02,1,MAKE_OP_RW_FLAG(OP_RW,OP_R,0)}, //0x02
	{R_M, 	C_ADD,	D__Gv,		D__rEv,		D__NONE,	"ADD" 	,0x03,1,MAKE_OP_RW_FLAG(OP_RW,OP_R,0)}, //0x03
	{ 0 |Immediate_Ib, 	C_ADD,	D__AL,		D__Ib,		D__NONE,	"ADD" 	,0x04,1,MAKE_OP_RW_FLAG(OP_RW,OP_R,0)}, //0x04
	{ 0 |Immediate_Iz, 	C_ADD,	D__rAX,		D__Iz,		D__NONE,	"ADD" 	,0x05,1,MAKE_OP_RW_FLAG(OP_RW,OP_R,0)}, //0x05
	{ 0 |I_64, 	C_PUSH,	D__ES,		D__NONE,	D__NONE,	"PUSH" 	,0x06,1,MAKE_OP_RW_FLAG(OP_R,0,0)}, //0x06
	{ 0 |I_64, 	C_POP,	D__ES,		D__NONE,	D__NONE,	"POP" 	,0x07,1,MAKE_OP_RW_FLAG(OP_W,0,0)}, //0x07

	{R_M, 	C_OR,	D__Eb,		D__Gb,		D__NONE,	"OR" 	,0x08,1,MAKE_OP_RW_FLAG(OP_RW,OP_R,0)}, //0x08
	{R_M, 	C_OR,	D__Ev,		D__Gv,		D__NONE,	"OR" 	,0x09,1,MAKE_OP_RW_FLAG(OP_RW,OP_R,0)}, //0x09
	{R_M, 	C_OR,	D__Gb,		D__rEb,		D__NONE,	"OR" 	,0x0a,1,MAKE_OP_RW_FLAG(OP_RW,OP_R,0)}, //0x0a
	{R_M, 	C_OR,	D__Gv,		D__rEv,		D__NONE,	"OR" 	,0x0b,1,MAKE_OP_RW_FLAG(OP_RW,OP_R,0)}, //0x0b
	{ 0 |Immediate_Ib, 	C_OR,	D__AL,		D__Ib,		D__NONE,	"OR" 	,0x0c,1,MAKE_OP_RW_FLAG(OP_RW,OP_R,0)}, //0x0c
	{ 0 |Immediate_Iz, 	C_OR,	D__rAX,		D__Iz,		D__NONE,	"OR" 	,0x0d,1,MAKE_OP_RW_FLAG(OP_RW,OP_R,0)}, //0x0d
	{ 0 |I_64, 	C_PUSH,	D__CS,		D__NONE,	D__NONE,	"PUSH" 	,0x0e,1,MAKE_OP_RW_FLAG(OP_R,0,0)}, //0x0e
	{ 0 , 	C_2BYTE,	D__CS,		D__NONE,	D__NONE,	(char*)Group0x0f,0x0f,1}, //0x0f

	{R_M, 	C_ADC,	D__Eb,		D__Gb,		D__NONE,	"ADC" 	,0x10,1,MAKE_OP_RW_FLAG(OP_RW,OP_R,0)}, //0x10
	{R_M, 	C_ADC,	D__Ev,		D__Gv,		D__NONE,	"ADC" 	,0x11,1,MAKE_OP_RW_FLAG(OP_RW,OP_R,0)}, //0x11
	{R_M, 	C_ADC,	D__Gb,		D__rEb,		D__NONE,	"ADC" 	,0x12,1,MAKE_OP_RW_FLAG(OP_RW,OP_R,0)}, //0x12
	{R_M, 	C_ADC,	D__Gv,		D__rEv,		D__NONE,	"ADC" 	,0x13,1,MAKE_OP_RW_FLAG(OP_RW,OP_R,0)}, //0x13
	{ 0 |Immediate_Ib, 	C_ADC,	D__AL,		D__Ib,		D__NONE,	"ADC" 	,0x14,1,MAKE_OP_RW_FLAG(OP_RW,OP_R,0)}, //0x14
	{ 0 |Immediate_Iz, 	C_ADC,	D__rAX,		D__Iz,		D__NONE,	"ADC" 	,0x15,1,MAKE_OP_RW_FLAG(OP_RW,OP_R,0)}, //0x15
	{ 0 |I_64, 	C_PUSH,	D__SS,		D__NONE,	D__NONE,	"PUSH" 	,0x16,1,MAKE_OP_RW_FLAG(OP_R,0,0)}, //0x16
	{ 0 |I_64, 	C_POP,	D__SS,		D__NONE,	D__NONE,	"POP" 	,0x17,1,MAKE_OP_RW_FLAG(OP_W,0,0)}, //0x17

	{R_M, 	C_SBB,	D__Eb,		D__Gb,		D__NONE,	"SBB" 	,0x18,1,MAKE_OP_RW_FLAG(OP_RW,OP_R,0)}, //0x18
	{R_M, 	C_SBB,	D__Ev,		D__Gv,		D__NONE,	"SBB" 	,0x19,1,MAKE_OP_RW_FLAG(OP_RW,OP_R,0)}, //0x19
	{R_M, 	C_SBB,	D__Gb,		D__rEb,		D__NONE,	"SBB" 	,0x1a,1,MAKE_OP_RW_FLAG(OP_RW,OP_R,0)}, //0x1a
	{R_M, 	C_SBB,	D__Gv,		D__rEv,		D__NONE,	"SBB" 	,0x1b,1,MAKE_OP_RW_FLAG(OP_RW,OP_R,0)}, //0x1b
	{ 0 |Immediate_Ib, 	C_SBB,	D__AL,		D__Ib,		D__NONE,	"SBB" 	,0x1c,1,MAKE_OP_RW_FLAG(OP_RW,OP_R,0)}, //0x1c
	{ 0 |Immediate_Iz, 	C_SBB,	D__rAX,		D__Iz,		D__NONE,	"SBB" 	,0x1d,1,MAKE_OP_RW_FLAG(OP_RW,OP_R,0)}, //0x1d
	{ 0 |I_64, 	C_PUSH,	D__DS,		D__NONE,	D__NONE,	"PUSH" 	,0x1e,1,MAKE_OP_RW_FLAG(OP_R,0,0)}, //0x1e
	{ 0 |I_64, 	C_POP,	D__DS,		D__NONE,	D__NONE,	"POP" 	,0x1f,1,MAKE_OP_RW_FLAG(OP_W,0,0)}, //0x1f

	{R_M, 	C_AND,	D__Eb,		D__Gb,		D__NONE,	"AND" 		,0x20,1,MAKE_OP_RW_FLAG(OP_RW,OP_R,0)}, //0x20
	{R_M, 	C_AND,	D__Ev,		D__Gv,		D__NONE,	"AND" 		,0x21,1,MAKE_OP_RW_FLAG(OP_RW,OP_R,0)}, //0x21
	{R_M, 	C_AND,	D__Gb,		D__rEb,		D__NONE,	"AND" 		,0x22,1,MAKE_OP_RW_FLAG(OP_RW,OP_R,0)}, //0x22
	{R_M, 	C_AND,	D__Gv,		D__rEv,		D__NONE,	"AND" 		,0x23,1,MAKE_OP_RW_FLAG(OP_RW,OP_R,0)}, //0x23
	{ 0 |Immediate_Ib, 	C_AND,	D__AL,		D__Ib,		D__NONE,	"AND" 		,0x24,1,MAKE_OP_RW_FLAG(OP_RW,OP_R,0)}, //0x24
	{ 0 |Immediate_Iz, 	C_AND,	D__rAX,		D__Iz,		D__NONE,	"AND" 		,0x25,1,MAKE_OP_RW_FLAG(OP_RW,OP_R,0)}, //0x25
	{ 0 , 	C_ES,	D__NONE,	D__NONE,	D__NONE,	"ES:"		,0x26,1}, //0x26
	{ 0 |I_64, 	C_DAA,	D__NONE,	D__NONE,	D__NONE,	"DAA" 		,0x27,1}, //0x27

	{R_M, 	C_SUB,	D__Eb,		D__Gb,		D__NONE,	"SUB" 	,0x28,1,MAKE_OP_RW_FLAG(OP_RW,OP_R,0)}, //0x28
	{R_M, 	C_SUB,	D__Ev,		D__Gv,		D__NONE,	"SUB" 	,0x29,1,MAKE_OP_RW_FLAG(OP_RW,OP_R,0)}, //0x29
	{R_M, 	C_SUB,	D__Gb,		D__rEb,		D__NONE,	"SUB" 	,0x2a,1,MAKE_OP_RW_FLAG(OP_RW,OP_R,0)}, //0x2a
	{R_M, 	C_SUB,	D__Gv,		D__rEv,		D__NONE,	"SUB" 	,0x2b,1,MAKE_OP_RW_FLAG(OP_RW,OP_R,0)}, //0x2b
	{ 0 |Immediate_Ib, 	C_SUB,	D__AL,		D__Ib,		D__NONE,	"SUB" 	,0x2c,1,MAKE_OP_RW_FLAG(OP_RW,OP_R,0)}, //0x2c
	{ 0 |Immediate_Iz, 	C_SUB,	D__rAX,		D__Iz,		D__NONE,	"SUB" 	,0x2d,1,MAKE_OP_RW_FLAG(OP_RW,OP_R,0)}, //0x2d
	{ 0 , 	C_CS,	D__NONE,	D__NONE,	D__NONE,	"CS:"	,0x2e,1}, //0x2e
	{ 0 |I_64, 	C_DAS,	D__NONE,	D__NONE,	D__NONE,	"DAS" 	,0x2f,1}, //0x2f

	{R_M, 	C_XOR,	D__Eb,		D__Gb,		D__NONE,	"XOR" 	,0x30,1,MAKE_OP_RW_FLAG(OP_RW,OP_R,0)}, //0x30
	{R_M, 	C_XOR,	D__Ev,		D__Gv,		D__NONE,	"XOR" 	,0x31,1,MAKE_OP_RW_FLAG(OP_RW,OP_R,0)}, //0x31
	{R_M, 	C_XOR,	D__Gb,		D__rEb,		D__NONE,	"XOR" 	,0x32,1,MAKE_OP_RW_FLAG(OP_RW,OP_R,0)}, //0x32
	{R_M, 	C_XOR,	D__Gv,		D__rEv,		D__NONE,	"XOR" 	,0x33,1,MAKE_OP_RW_FLAG(OP_RW,OP_R,0)}, //0x33
	{ 0 |Immediate_Ib, 	C_XOR,	D__AL,		D__Ib,		D__NONE,	"XOR" 	,0x34,1,MAKE_OP_RW_FLAG(OP_RW,OP_R,0)}, //0x34
	{ 0 |Immediate_Iz, 	C_XOR,	D__rAX,		D__Iz,		D__NONE,	"XOR" 	,0x35,1,MAKE_OP_RW_FLAG(OP_RW,OP_R,0)}, //0x35
	{ 0 , 	C_SS,	D__NONE,	D__NONE,	D__NONE,	"SS:"	,0x36,1}, //0x36
	{ 0 |I_64, 	C_AAA,	D__NONE,	D__NONE,	D__NONE,	"AAA" 	,0x37,1}, //0x37

	{R_M, 	C_CMP,	D__rEb,		D__Gb,		D__NONE,	"CMP" 		,0x38,1,MAKE_OP_RW_FLAG(OP_R,OP_R,0)}, //0x38
	{R_M, 	C_CMP,	D__rEv,		D__Gv,		D__NONE,	"CMP" 		,0x39,1,MAKE_OP_RW_FLAG(OP_R,OP_R,0)}, //0x39
	{R_M, 	C_CMP,	D__Gb,		D__rEb,		D__NONE,	"CMP" 		,0x3a,1,MAKE_OP_RW_FLAG(OP_R,OP_R,0)}, //0x3a
	{R_M, 	C_CMP,	D__Gv,		D__rEv,		D__NONE,	"CMP" 		,0x3b,1,MAKE_OP_RW_FLAG(OP_R,OP_R,0)}, //0x3b
	{ 0 |Immediate_Ib, 	C_CMP,	D__AL,		D__Ib,		D__NONE,	"CMP" ,0x3c,1,MAKE_OP_RW_FLAG(OP_R,OP_R,0)}, //0x3c
	{ 0 |Immediate_Iz, 	C_CMP,	D__rAX,		D__Iz,		D__NONE,	"CMP" ,0x3d,1,MAKE_OP_RW_FLAG(OP_R,OP_R,0)}, //0x3d
	{ 0 , 	C_DS,	D__NONE,	D__NONE,	D__NONE,	"DS:"		,0x3e,1}, //0x3e
	{ 0 |I_64, 	C_AAS,	D__NONE,	D__NONE,	D__NONE,	"AAS" 		,0x3f,1}, //0x3f

	{ 0 |I_64, C_INC,	D__eAX,		D__NONE,	D__NONE,	"INC" 		,0x40,1,MAKE_OP_RW_FLAG(OP_RW,0,0)}, //0x40
	{ 0 |I_64, C_INC,	D__eCX,		D__NONE,	D__NONE,	"INC" 		,0x41,1,MAKE_OP_RW_FLAG(OP_RW,0,0)}, //0x41
	{ 0 |I_64, C_INC,	D__eDX,		D__NONE,	D__NONE,	"INC" 		,0x42,1,MAKE_OP_RW_FLAG(OP_RW,0,0)}, //0x42
	{ 0 |I_64, C_INC,	D__eBX,		D__NONE,	D__NONE,	"INC" 		,0x43,1,MAKE_OP_RW_FLAG(OP_RW,0,0)}, //0x43
	{ 0 |I_64, C_INC,	D__eSP,		D__NONE,	D__NONE,	"INC" 		,0x44,1,MAKE_OP_RW_FLAG(OP_RW,0,0)}, //0x44
	{ 0 |I_64, C_INC,	D__eBP,		D__NONE,	D__NONE,	"INC" 		,0x45,1,MAKE_OP_RW_FLAG(OP_RW,0,0)}, //0x45
	{ 0 |I_64, C_INC,	D__eSI,		D__NONE,	D__NONE,	"INC" 		,0x46,1,MAKE_OP_RW_FLAG(OP_RW,0,0)}, //0x46
	{ 0 |I_64, C_INC,	D__eDI,		D__NONE,	D__NONE,	"INC" 		,0x47,1,MAKE_OP_RW_FLAG(OP_RW,0,0)}, //0x47

	{ 0 |I_64, C_DEC,	D__eAX,		D__NONE,	D__NONE,	"DEC" 		,0x48,1,MAKE_OP_RW_FLAG(OP_RW,0,0)}, //0x48
	{ 0 |I_64, C_DEC,	D__eCX,		D__NONE,	D__NONE,	"DEC" 		,0x49,1,MAKE_OP_RW_FLAG(OP_RW,0,0)}, //0x49
	{ 0 |I_64, C_DEC,	D__eDX,		D__NONE,	D__NONE,	"DEC" 		,0x4a,1,MAKE_OP_RW_FLAG(OP_RW,0,0)}, //0x4a
	{ 0 |I_64, C_DEC,	D__eBX,		D__NONE,	D__NONE,	"DEC" 		,0x4b,1,MAKE_OP_RW_FLAG(OP_RW,0,0)}, //0x4b
	{ 0 |I_64, C_DEC,	D__eSP,		D__NONE,	D__NONE,	"DEC" 		,0x4c,1,MAKE_OP_RW_FLAG(OP_RW,0,0)}, //0x4c
	{ 0 |I_64, C_DEC,	D__eBP,		D__NONE,	D__NONE,	"DEC" 		,0x4d,1,MAKE_OP_RW_FLAG(OP_RW,0,0)}, //0x4d
	{ 0 |I_64, C_DEC,	D__eSI,		D__NONE,	D__NONE,	"DEC" 		,0x4e,1,MAKE_OP_RW_FLAG(OP_RW,0,0)}, //0x4e
	{ 0 |I_64, C_DEC,	D__eDI,		D__NONE,	D__NONE,	"DEC" 		,0x4f,1,MAKE_OP_RW_FLAG(OP_RW,0,0)}, //0x4f

	{ 0 | D_64 , C_PUSH,	D__rAX_r8,	D__NONE,	D__NONE,	"PUSH" 		,0x50,1,MAKE_OP_RW_FLAG(OP_R,0,0)}, //0x50
	{ 0 | D_64 , C_PUSH,	D__rCX_r9,	D__NONE,	D__NONE,	"PUSH" 		,0x51,1,MAKE_OP_RW_FLAG(OP_R,0,0)}, //0x51
	{ 0 | D_64 , C_PUSH,	D__rDX_r10,	D__NONE,	D__NONE,	"PUSH" 		,0x52,1,MAKE_OP_RW_FLAG(OP_R,0,0)}, //0x52
	{ 0 | D_64 , C_PUSH,	D__rBX_r11,	D__NONE,	D__NONE,	"PUSH" 		,0x53,1,MAKE_OP_RW_FLAG(OP_R,0,0)}, //0x53
	{ 0 | D_64 , C_PUSH,	D__rSP_r12,	D__NONE,	D__NONE,	"PUSH" 		,0x54,1,MAKE_OP_RW_FLAG(OP_R,0,0)}, //0x54
	{ 0 | D_64 , C_PUSH,	D__rBP_r13,	D__NONE,	D__NONE,	"PUSH" 		,0x55,1,MAKE_OP_RW_FLAG(OP_R,0,0)}, //0x55
	{ 0 | D_64 , C_PUSH,	D__rSI_r14,	D__NONE,	D__NONE,	"PUSH" 		,0x56,1,MAKE_OP_RW_FLAG(OP_R,0,0)}, //0x56
	{ 0 | D_64 , C_PUSH,	D__rDI_r15,	D__NONE,	D__NONE,	"PUSH" 		,0x57,1,MAKE_OP_RW_FLAG(OP_R,0,0)}, //0x57

	{ 0 | D_64 , C_POP,	D__rAX_r8,	D__NONE,	D__NONE,	"POP" 		,0x58,1,MAKE_OP_RW_FLAG(OP_W,0,0)}, //0x58
	{ 0 | D_64 , C_POP,	D__rCX_r9,	D__NONE,	D__NONE,	"POP" 		,0x59,1,MAKE_OP_RW_FLAG(OP_W,0,0)}, //0x59
	{ 0 | D_64 , C_POP,	D__rDX_r10,	D__NONE,	D__NONE,	"POP" 		,0x5a,1,MAKE_OP_RW_FLAG(OP_W,0,0)}, //0x5a
	{ 0 | D_64 , C_POP,	D__rBX_r11,	D__NONE,	D__NONE,	"POP" 		,0x5b,1,MAKE_OP_RW_FLAG(OP_W,0,0)}, //0x5b
	{ 0 | D_64 , C_POP,	D__rSP_r12,	D__NONE,	D__NONE,	"POP" 		,0x5c,1,MAKE_OP_RW_FLAG(OP_W,0,0)}, //0x5c
	{ 0 | D_64 , C_POP,	D__rBP_r13,	D__NONE,	D__NONE,	"POP" 		,0x5d,1,MAKE_OP_RW_FLAG(OP_W,0,0)}, //0x5d
	{ 0 | D_64 , C_POP,	D__rSI_r14,	D__NONE,	D__NONE,	"POP" 		,0x5e,1,MAKE_OP_RW_FLAG(OP_W,0,0)}, //0x5e
	{ 0 | D_64 , C_POP,	D__rDI_r15,	D__NONE,	D__NONE,	"POP" 		,0x5f,1,MAKE_OP_RW_FLAG(OP_W,0,0)}, //0x5f

	{ 0 |I_64, C_PUSHA,	D__NONE,	D__NONE,	D__NONE,	"PUSHA" 	,0x60,1,MAKE_OP_RW_FLAG(OP_R,0,0)}, //0x60
	{ 0 |I_64, C_POPA,	D__NONE,	D__NONE,	D__NONE,	"POPA" 		,0x61,1,MAKE_OP_RW_FLAG(OP_W,0,0)}, //0x61
	{R_M|I_64, C_BOUND,	D__Gv,		D__rMa,		D__NONE,	"BOUND" 	,0x62,1,MAKE_OP_RW_FLAG(OP_R,OP_R,0)}, //0x62
	{R_M, C_GRP6,	D__NONE,	D__NONE,		D__NONE,	(char*)Group0x63 		,0x63,1}, //0x63
	{ 0 , C_FS,		D__NONE,	D__NONE,	D__NONE,	"FS:"		,0x64,1}, //0x64
	{ 0 , C_GS,		D__NONE,	D__NONE,	D__NONE,	"GS:"		,0x65,1}, //0x65
	{ 0 , C_OPER												,0x66,1}, //0x66
	{ 0 , C_ADDR												,0x67,1}, //0x67

	{ 0  |Immediate_Iz | D_64, C_PUSH,	D__Iz,		D__NONE,	D__NONE,	"PUSH" 	,0x68,1,MAKE_OP_RW_FLAG(OP_R,0,0)}, //0x68
	{R_M |Immediate_Iz, C_IMUL,	D__Gv,	D__rEv,		D__Iz,		"IMUL" 		,0x69,1,MAKE_OP_RW_FLAG(OP_RW,OP_R,OP_R)}, //0x69
	{ 0  |Immediate_sIb | D_64, C_PUSH,	D__sIb,		D__NONE,	D__NONE,	"PUSH" 		,0x6a,1,MAKE_OP_RW_FLAG(OP_R,0,0)}, //0x6a
	{R_M |Immediate_sIb, C_IMUL,	D__Gv,		D__rEv,		D__sIb,		"IMUL" 		,0x6b,1,MAKE_OP_RW_FLAG(OP_RW,OP_R,OP_R)}, //0x6b
	{ 0 , C_INS,	D__Yb,		D__DX,		D__NONE,	"INS" 		,0x6c,1,MAKE_OP_RW_FLAG(OP_W,OP_R,0)}, //0x6c
	{ 0 , C_INS,	D__Yz,		D__DX,		D__NONE,	"INS" 		,0x6d,1,MAKE_OP_RW_FLAG(OP_W,OP_R,0)}, //0x6d
	{ 0 , C_OUTS,	D__DX,		D__Xb,		D__NONE,	"OUTS" 		,0x6e,1,MAKE_OP_RW_FLAG(OP_R,OP_R,0)}, //0x6e
	{ 0 , C_OUTS,	D__DX,		D__Xz,		D__NONE,	"OUTS" 		,0x6f,1,MAKE_OP_RW_FLAG(OP_R,OP_R,0)}, //0x6f

	{ 0 |Immediate_Jb|F_64, C_JtO,	D__Jb,		D__tO,	D__NONE,	"JO" 		,0x70,1}, //0x70
	{ 0 |Immediate_Jb|F_64, C_JfO,	D__Jb,		D__fO,	D__NONE,	"JNO" 		,0x71,1}, //0x71
	{ 0 |Immediate_Jb|F_64, C_JtC,	D__Jb,		D__tC,	D__NONE,	"JC" 		,0x72,1}, //0x72
	{ 0 |Immediate_Jb|F_64, C_JfC,	D__Jb,		D__fC,	D__NONE,	"JNC" 		,0x73,1}, //0x73
	{ 0 |Immediate_Jb|F_64, C_JtZ,	D__Jb,		D__tZ,	D__NONE,	"JZ" 		,0x74,1}, //0x74
	{ 0 |Immediate_Jb|F_64, C_JfZ,	D__Jb,		D__fZ,	D__NONE,	"JNZ" 		,0x75,1}, //0x75
	{ 0 |Immediate_Jb|F_64, C_JfA,	D__Jb,		D__fA,	D__NONE,	"JNA" 		,0x76,1}, //0x76
	{ 0 |Immediate_Jb|F_64, C_JtA,	D__Jb,		D__tA,	D__NONE,	"JA" 		,0x77,1}, //0x77
	{ 0 |Immediate_Jb|F_64, C_JfS,	D__Jb,		D__fP,	D__NONE,	"JS" 		,0x78,1}, //0x78
	{ 0 |Immediate_Jb|F_64, C_JtS,	D__Jb,		D__tS,	D__NONE,	"JNS" 		,0x79,1}, //0x79
	{ 0 |Immediate_Jb|F_64, C_JtP,	D__Jb,		D__tP,	D__NONE,	"JP" 		,0x7a,1}, //0x7a
	{ 0 |Immediate_Jb|F_64, C_JfP,	D__Jb,		D__fS,	D__NONE,	"JNP" 		,0x7b,1}, //0x7b
	{ 0 |Immediate_Jb|F_64, C_JtL,	D__Jb,		D__tL,	D__NONE,	"JL" 		,0x7c,1}, //0x7c
	{ 0 |Immediate_Jb|F_64, C_JfL,	D__Jb,		D__fL,	D__NONE,	"JNL" 		,0x7d,1}, //0x7d
	{ 0 |Immediate_Jb|F_64, C_JfG,	D__Jb,		D__fG,	D__NONE,	"JNG" 		,0x7e,1}, //0x7e
	{ 0 |Immediate_Jb|F_64, C_JtG,	D__Jb,		D__tG,	D__NONE,	"JG" 		,0x7f,1}, //0x7f

	{R_M|Immediate_Ib, 	C_GRP,	D__Eb,		D__Ib,		D__NONE,	(char*)Group0x80		,0x80,1}, //0x80
	{R_M|Immediate_Iz, 	C_GRP,	D__Ev,		D__Iz,		D__NONE,	(char*)Group0x81		,0x81,1}, //0x81
	{R_M|Immediate_Ib, 	C_GRP,	D__Eb,		D__Ib,		D__NONE,	(char*)Group0x82		,0x82,1}, //0x82
	{R_M|Immediate_sIb, C_GRP,	D__Ev,		D__sIb,		D__NONE,	(char*)Group0x83		,0x83,1}, //0x83
	{R_M, 	C_TEST,		D__rEb,		D__Gb,		D__NONE,	"TEST" 		,0x84,1,MAKE_OP_RW_FLAG(OP_R,OP_R,0)}, //0x84
	{R_M, 	C_TEST,		D__rEv,		D__Gv,		D__NONE,	"TEST" 		,0x85,1,MAKE_OP_RW_FLAG(OP_R,OP_R,0)}, //0x85
//	{R_M, 	C_XCHG,		D__Eb,		D__Gb,		D__NONE,	"XCHG" 		,0x86,1}, //0x86
//	{R_M, 	C_XCHG,		D__Ev,		D__Gv,		D__NONE,	"XCHG" 		,0x87,1}, //0x87
	{R_M, 	C_XCHG,		D__Gb,		D__Eb,		D__NONE,	"XCHG" 		,0x86,1,MAKE_OP_RW_FLAG(OP_RW,OP_RW,0)}, //0x86
	{R_M, 	C_XCHG,		D__Gv,		D__Ev,		D__NONE,	"XCHG" 		,0x87,1,MAKE_OP_RW_FLAG(OP_RW,OP_RW,0)}, //0x87

	{R_M, 	C_MOV,		D__wEb,		D__Gb,		D__NONE,	"MOV" 		,0x88,1,MAKE_OP_RW_FLAG(OP_W,OP_R,0)}, //0x88
	{R_M, 	C_MOV,		D__wEv,		D__Gv,		D__NONE,	"MOV" 		,0x89,1,MAKE_OP_RW_FLAG(OP_W,OP_R,0)}, //0x89
	{R_M, 	C_MOV,		D__Gb,		D__rEb,		D__NONE,	"MOV" 		,0x8a,1,MAKE_OP_RW_FLAG(OP_W,OP_R,0)}, //0x8a
	{R_M, 	C_MOV,		D__Gv,		D__rEv,		D__NONE,	"MOV" 		,0x8b,1,MAKE_OP_RW_FLAG(OP_W,OP_R,0)}, //0x8b
	{R_M, 	C_MOV,		D__wEw,		D__Sw, 		D__NONE,	"MOV" 		,0x8c,1,MAKE_OP_RW_FLAG(OP_W,OP_R,0)}, //0x8c
	{R_M, 	C_LEA,		D__Gv,		D__M,		D__NONE,	"LEA" 		,0x8d,1,MAKE_OP_RW_FLAG(OP_W,OP_R,0)}, //0x8d
	{R_M, 	C_MOV,		D__Sw,		D__rEw,		D__NONE,	"MOV" 		,0x8e,1,MAKE_OP_RW_FLAG(OP_W,OP_R,0)}, //0x8e
	{R_M, 	C_GRP,		D__Ev,		D__NONE,	D__NONE,	(char*)Group0x8f,0x8f,1}, //0x8f

	{ 0 , C_XCHG_NOP,		D__rAX,D__rAX_r8,			D__NONE,"XCHG"	,	0x90,1},
	//{ 0 , C_GRP3,	D__NONE,	D__NONE,	D__NONE,	(char*)Group0x90 		,0x90,1}, //0x90
	{ 0 , C_XCHG,	D__rAX,D__rCX_r9,				D__NONE,	"XCHG" 		,0x91,1,MAKE_OP_RW_FLAG(OP_RW,OP_RW,0)}, //0x91
	{ 0 , C_XCHG,	D__rAX,D__rDX_r10,				D__NONE,	"XCHG" 		,0x92,1,MAKE_OP_RW_FLAG(OP_RW,OP_RW,0)}, //0x92
	{ 0 , C_XCHG,	D__rAX,D__rBX_r11,				D__NONE,	"XCHG" 		,0x93,1,MAKE_OP_RW_FLAG(OP_RW,OP_RW,0)}, //0x93
	{ 0 , C_XCHG,	D__rAX,D__rSP_r12,				D__NONE,	"XCHG" 		,0x94,1,MAKE_OP_RW_FLAG(OP_RW,OP_RW,0)}, //0x94
	{ 0 , C_XCHG,	D__rAX,D__rBP_r13,				D__NONE,	"XCHG" 		,0x95,1,MAKE_OP_RW_FLAG(OP_RW,OP_RW,0)}, //0x95
	{ 0 , C_XCHG,	D__rAX,D__rSI_r14,				D__NONE,	"XCHG" 		,0x96,1,MAKE_OP_RW_FLAG(OP_RW,OP_RW,0)}, //0x96
	{ 0 , C_XCHG,	D__rAX,D__rDI_r15,				D__NONE,	"XCHG" 		,0x97,1,MAKE_OP_RW_FLAG(OP_RW,OP_RW,0)}, //0x97

	{ 0 , C_CBW,	D__NONE,	D__NONE,	D__NONE,	"CBW" 		,0x98,1}, //0x98
	{ 0 , C_CWD,	D__NONE,	D__NONE,	D__NONE,	"CWD" 		,0x99,1}, //0x99
	{ 0 |Immediate_IvIw|I_64, C_CALL,	D__Ap,	D__NONE,	D__NONE,	"CALL" 	,0x9a,1,MAKE_OP_RW_FLAG(OP_R,0,0)}, //0x9a
	{ 0 , C_WAIT,	D__NONE,	D__NONE,	D__NONE,	"WAIT" 		,0x9b,1}, //0x9b
	{ 0 | D_64 , C_PUSHF,	D__Fv,		D__NONE,	D__NONE,	"PUSHF" 	,0x9c,1,MAKE_OP_RW_FLAG(OP_R,0,0)}, //0x9c
	{ 0 | D_64 , C_POPF,	D__Fv,		D__NONE,	D__NONE,	"POPF" 		,0x9d,1,MAKE_OP_RW_FLAG(OP_W,0,0)}, //0x9d
	{ 0 , C_SAHF,	D__NONE,	D__NONE,	D__NONE,	"SAHF" 		,0x9e,1}, //0x9e
	{ 0 , C_LAHF,	D__NONE,	D__NONE,	D__NONE,	"LAHF" 		,0x9f,1}, //0x9f

	{ 0 , C_MOV,	D__AL,		D__rOb,		D__NONE,	"MOV" 		,0xa0,1,MAKE_OP_RW_FLAG(OP_W,OP_R,0)}, //0xa0
	{ 0 , C_MOV,	D__rAX,		D__rOv,		D__NONE,	"MOV" 		,0xa1,1,MAKE_OP_RW_FLAG(OP_W,OP_R,0)}, //0xa1
	{ 0 , C_MOV,	D__wOb,		D__AL,		D__NONE,	"MOV" 		,0xa2,1,MAKE_OP_RW_FLAG(OP_W,OP_R,0)}, //0xa2
	{ 0 , C_MOV,	D__wOv,		D__rAX,		D__NONE,	"MOV" 		,0xa3,1,MAKE_OP_RW_FLAG(OP_W,OP_R,0)}, //0xa3
	{ 0 , C_MOVS,	D__wYb,		D_rXb,		D__NONE,	"MOVS" 		,0xa4,1,MAKE_OP_RW_FLAG(OP_W,OP_R,0)}, //0xa4
	{ 0 , C_MOVS,	D__wYv,		D_rXv,		D__NONE,	"MOVS" 		,0xa5,1,MAKE_OP_RW_FLAG(OP_W,OP_R,0)}, //0xa5
	{ 0 , C_CMPS,	D_rXb,		D__rYb,		D__NONE,	"CMPS" 		,0xa6,1,MAKE_OP_RW_FLAG(OP_R,OP_R,0)}, //0xa6
	{ 0 , C_CMPS,	D_rXv,		D__rYv,		D__NONE,	"CMPS" 		,0xa7,1,MAKE_OP_RW_FLAG(OP_R,OP_R,0)}, //0xa7

	{ 0 | Immediate_Ib, 	C_TEST,	D__AL,		D__Ib,		D__NONE,	"TEST" 		,0xa8,1,MAKE_OP_RW_FLAG(OP_R,OP_R,0)}, //0xa8
	{ 0 | Immediate_Iz, 	C_TEST,	D__rAX,		D__Iz,		D__NONE,	"TEST" 		,0xa9,1,MAKE_OP_RW_FLAG(OP_R,OP_R,0)}, //0xa9
	{ 0 , 	C_STOS,	D__wYb,		D__AL,		D__NONE,	"STOS" 		,0xaa,1,MAKE_OP_RW_FLAG(OP_W,OP_R,0)}, //0xaa
	{ 0 , 	C_STOS,	D__wYv,		D__rAX,		D__NONE,	"STOS" 		,0xab,1,MAKE_OP_RW_FLAG(OP_W,OP_R,0)}, //0xab
	{ 0 , 	C_LODS,	D__AL,		D_rXb,		D__NONE,	"LODS" 		,0xac,1,MAKE_OP_RW_FLAG(OP_W,OP_R,0)}, //0xac
	{ 0 , 	C_LODS,	D__rAX,		D_rXv,		D__NONE,	"LODS" 		,0xad,1,MAKE_OP_RW_FLAG(OP_W,OP_R,0)}, //0xad
	{ 0 , 	C_SCAS,	D__rYb,		D__AL,		D__NONE,	"SCAS" 		,0xae,1,MAKE_OP_RW_FLAG(OP_R,OP_R,0)}, //0xae
	{ 0 , 	C_SCAS,	D__rYv,		D__rAX,		D__NONE,	"SCAS" 		,0xaf,1,MAKE_OP_RW_FLAG(OP_R,OP_R,0)}, //0xaf

	{ 0 |Immediate_Ib, C_MOV,	D__AL_r8L,		D__Ib,	D__NONE,	"MOV" 	,0xb0,1,MAKE_OP_RW_FLAG(OP_W,OP_R,0)}, //0xb0
	{ 0 |Immediate_Ib, C_MOV,	D__CL_r9L,		D__Ib,	D__NONE,	"MOV" 	,0xb1,1,MAKE_OP_RW_FLAG(OP_W,OP_R,0)}, //0xb1
	{ 0 |Immediate_Ib, C_MOV,	D__DL_r10L,		D__Ib,	D__NONE,	"MOV" 	,0xb2,1,MAKE_OP_RW_FLAG(OP_W,OP_R,0)}, //0xb2
	{ 0 |Immediate_Ib, C_MOV,	D__BL_r11L,		D__Ib,	D__NONE,	"MOV" 	,0xb3,1,MAKE_OP_RW_FLAG(OP_W,OP_R,0)}, //0xb3
	{ 0 |Immediate_Ib, C_MOV,	D__AH_r12L,		D__Ib,	D__NONE,	"MOV" 	,0xb4,1,MAKE_OP_RW_FLAG(OP_W,OP_R,0)}, //0xb4
	{ 0 |Immediate_Ib, C_MOV,	D__CH_r13L,		D__Ib,	D__NONE,	"MOV" 	,0xb5,1,MAKE_OP_RW_FLAG(OP_W,OP_R,0)}, //0xb5
	{ 0 |Immediate_Ib, C_MOV,	D__DH_r14L,		D__Ib,	D__NONE,	"MOV" 	,0xb6,1,MAKE_OP_RW_FLAG(OP_W,OP_R,0)}, //0xb6
	{ 0 |Immediate_Ib, C_MOV,	D__BH_r15L,		D__Ib,	D__NONE,	"MOV" 	,0xb7,1,MAKE_OP_RW_FLAG(OP_W,OP_R,0)}, //0xb7

	{ 0 |Immediate_Iv, C_MOV,	D__rAX_r8,	D__Iv,	D__NONE,	"MOV" 	,0xb8,1,MAKE_OP_RW_FLAG(OP_W,OP_R,0)}, //0xb8
	{ 0 |Immediate_Iv, C_MOV,	D__rCX_r9,	D__Iv,	D__NONE,	"MOV" 	,0xb9,1,MAKE_OP_RW_FLAG(OP_W,OP_R,0)}, //0xb9
	{ 0 |Immediate_Iv, C_MOV,	D__rDX_r10,	D__Iv,	D__NONE,	"MOV" 	,0xba,1,MAKE_OP_RW_FLAG(OP_W,OP_R,0)}, //0xba
	{ 0 |Immediate_Iv, C_MOV,	D__rBX_r11,	D__Iv,	D__NONE,	"MOV" 	,0xbb,1,MAKE_OP_RW_FLAG(OP_W,OP_R,0)}, //0xbb
	{ 0 |Immediate_Iv, C_MOV,	D__rSP_r12,	D__Iv,	D__NONE,	"MOV" 	,0xbc,1,MAKE_OP_RW_FLAG(OP_W,OP_R,0)}, //0xbc
	{ 0 |Immediate_Iv, C_MOV,	D__rBP_r13,	D__Iv,	D__NONE,	"MOV" 	,0xbd,1,MAKE_OP_RW_FLAG(OP_W,OP_R,0)}, //0xbd
	{ 0 |Immediate_Iv, C_MOV,	D__rSI_r14,	D__Iv,	D__NONE,	"MOV" 	,0xbe,1,MAKE_OP_RW_FLAG(OP_W,OP_R,0)}, //0xbe
	{ 0 |Immediate_Iv, C_MOV,	D__rDI_r15,	D__Iv,	D__NONE,	"MOV" 	,0xbf,1,MAKE_OP_RW_FLAG(OP_W,OP_R,0)}, //0xbf 

	{R_M|Immediate_Ib, C_GRP,	D__NONE,	D__NONE,	D__NONE,	(char*)Group0xc0			,0xc0,1}, //0xc0
	{R_M|Immediate_Ib, C_GRP,	D__NONE,	D__NONE,	D__NONE,	(char*)Group0xc1			,0xc1,1}, //0xc1
	{ 0 |Immediate_Iw|F_64, C_RET,	D__Iw,		D__NONE,	D__NONE,	"RET" 	,0xc2,1,MAKE_OP_RW_FLAG(OP_R,0,0)}, //0xc2
	{ 0 |F_64, C_RET,	D__NONE,	D__NONE,	D__NONE,	"RET" 				,0xc3,1}, //0xc3
	{R_M|I_64, C_LES,	D__Gv,		D__rMp,		D__NONE,	"LES" 				,0xc4,1,MAKE_OP_RW_FLAG(OP_W,OP_R,0)}, //0xc4
	{R_M|I_64, C_LDS,	D__Gv,		D__rMp,		D__NONE,	"LDS" 				,0xc5,1,MAKE_OP_RW_FLAG(OP_W,OP_R,0)}, //0xc5
	{R_M, C_GRP,	D__NONE,	D__NONE,	D__NONE,	(char*)Group0xc6						,0xc6,1}, //0xc6
	{R_M, C_GRP,	D__NONE,	D__NONE,	D__NONE,	(char*)Group0xc7						,0xc7,1}, //0xc7

	{ 0 |Immediate_IwIb, C_ENTER,	D__Iw,		D__Ib,	D__NONE,	"ENTER" 	,0xc8,1,MAKE_OP_RW_FLAG(OP_R,OP_R,0)}, //0xc8
	{ 0 | D_64 , C_LEAVE,	D__NONE,	D__NONE,	D__NONE,	"LEAVE" 	,0xc9,1}, //0xc9
	{ 0 |Immediate_Iw, C_RETF,	D__Iw,		D__NONE,	D__NONE,	"RETF" 		,0xca,1,MAKE_OP_RW_FLAG(OP_R,0,0)}, //0xca
	{ 0 , C_RETF,	D__NONE,	D__NONE,	D__NONE,	"RETF" 		,0xcb,1}, //0xcb
	{ 0 , C_INT3,	D__NONE,	D__NONE,	D__NONE,	"INT3" 		,0xcc,1}, //0xcc
	{ 0 |Immediate_Ib, C_INT,	D__Ib,		D__NONE,	D__NONE,	"INT" 		,0xcd,1,MAKE_OP_RW_FLAG(OP_R,0,0)}, //0xcd
	{ 0 |I_64, C_INTO,	D__NONE,	D__NONE,	D__NONE,	"INTO" 		,0xce,1}, //0xce
	{ 0 , C_IRET,	D__NONE,	D__NONE,	D__NONE,	"IRET" 		,0xcf,1}, //0xcf

	{R_M, 	C_GRP,	D__Eb,		D__1,		D__NONE,	(char*)Group0xd0			,0xd0,1}, //0xd0
	{R_M, 	C_GRP,	D__Ev,		D__1,		D__NONE,	(char*)Group0xd1			,0xd1,1}, //0xd1
	{R_M, 	C_GRP,	D__Eb,		D__CL,	D__NONE,		(char*)Group0xd2			,0xd2,1}, //0xd2
	{R_M, 	C_GRP,	D__Ev,		D__CL,	D__NONE,		(char*)Group0xd3			,0xd3,1}, //0xd3
	{ 0 |Immediate_Ib|I_64, 	C_AAM,	D__Ib,	D__NONE,	D__NONE,"AAM" ,0xd4,1,MAKE_OP_RW_FLAG(OP_R,0,0)}, //0xd4
	{ 0 |Immediate_Ib|I_64, 	C_AAD,	D__Ib,	D__NONE,	D__NONE,"AAD" ,0xd5,1,MAKE_OP_RW_FLAG(OP_R,0,0)}, //0xd5
	{ 0 , 	C_SALC,		D__NONE,	D__NONE,	D__NONE,	"SALC" 		,0xd6,1}, //0xd6
	{ 0 , 	C_XLAT,		D__NONE,	D__NONE,	D__NONE,	"XLAT" 		,0xd7,1}, //0xd7

	{R_M, 	C_ESC,	D__NONE,	D__NONE,	D__NONE,	(char*)Group0xd8 	,0xd8,1}, //0xd8
	{R_M, 	C_ESC,	D__NONE,	D__NONE,	D__NONE,	(char*)Group0xd9 	,0xd9,1}, //0xd9
	{R_M, 	C_ESC,	D__NONE,	D__NONE,	D__NONE,	(char*)Group0xda 	,0xda,1}, //0xda
	{R_M, 	C_ESC,	D__NONE,	D__NONE,	D__NONE,	(char*)Group0xdb 	,0xdb,1}, //0xdb
	{R_M, 	C_ESC,	D__NONE,	D__NONE,	D__NONE,	(char*)Group0xdc 	,0xdc,1}, //0xdc
	{R_M, 	C_ESC,	D__NONE,	D__NONE,	D__NONE,	(char*)Group0xdd 	,0xdd,1}, //0xdd
	{R_M, 	C_ESC,	D__NONE,	D__NONE,	D__NONE,	(char*)Group0xde 	,0xde,1}, //0xde
	{R_M, 	C_ESC,	D__NONE,	D__NONE,	D__NONE,	(char*)Group0xdf 	,0xdf,1}, //0xdf


	{ 0 |Immediate_Jb, 	C_LOOPNZ,	D__Jb,		D__NONE,	D__NONE,	"LOOPNZ" 		,0xe0,1,MAKE_OP_RW_FLAG(OP_R,0,0)}, //0xe0
	{ 0 |Immediate_Jb, 	C_LOOPZ,	D__Jb,		D__NONE,	D__NONE,	"LOOPZ" 		,0xe1,1,MAKE_OP_RW_FLAG(OP_R,0,0)}, //0xe1
	{ 0 |Immediate_Jb, 	C_LOOP,		D__Jb,		D__NONE,	D__NONE,	"LOOP" 			,0xe2,1,MAKE_OP_RW_FLAG(OP_R,0,0)}, //0xe2
	{ 0 |Immediate_Jb, 	C_JCXZ,		D__Jb,		D__NONE,	D__NONE,	"JCXZ" 			,0xe3,1,MAKE_OP_RW_FLAG(OP_R,0,0)}, //0xe3
	{ 0 |Immediate_Ib, 	C_IN,		D__AL,		D__Ib,		D__NONE,	"IN" 			,0xe4,1,MAKE_OP_RW_FLAG(OP_W,OP_R,0)}, //0xe4
	{ 0 |Immediate_Ib, 	C_IN,		D__eX,		D__Ib,		D__NONE,	"IN" 			,0xe5,1,MAKE_OP_RW_FLAG(OP_W,OP_R,0)}, //0xe5
	{ 0 |Immediate_Ib, 	C_OUT,		D__Ib,		D__AL,		D__NONE,	"OUT" 			,0xe6,1,MAKE_OP_RW_FLAG(OP_R,OP_R,0)}, //0xe6
	{ 0 |Immediate_Ib, 	C_OUT,		D__Ib,		D__eX,		D__NONE,	"OUT" 			,0xe7,1,MAKE_OP_RW_FLAG(OP_R,OP_R,0)}, //0xe7

	{ 0 |Immediate_Jv|F_64, 	C_CALL,	D__Jz,		D__NONE,	D__NONE,	"CALL" 		,0xe8,1,MAKE_OP_RW_FLAG(OP_R,0,0)}, //0xe8
	{ 0 |Immediate_Jv|F_64, 	C_JMP,	D__Jz,		D__NONE,	D__NONE,	"JMP" 		,0xe9,1,MAKE_OP_RW_FLAG(OP_R,0,0)}, //0xe9
	{ 0 |Immediate_IvIw|I_64, 	C_JMP,	D__Ap,		D__NONE,	D__NONE,	"JMP" 		,0xea,1,MAKE_OP_RW_FLAG(OP_R,0,0)}, //0xea
	{ 0 |Immediate_Jb|F_64, 	C_JMP,	D__Jb,		D__NONE,	D__NONE,	"JMP" 		,0xeb,1,MAKE_OP_RW_FLAG(OP_R,0,0)}, //0xeb
	{ 0 , 	C_IN,	D__AL,		D__DX,		D__NONE,	"IN" 		,0xec,1,MAKE_OP_RW_FLAG(OP_W,OP_R,0)}, //0xec
	{ 0 , 	C_IN,	D__eX,		D__DX,		D__NONE,	"IN" 		,0xed,1,MAKE_OP_RW_FLAG(OP_W,OP_R,0)}, //0xed
	{ 0 , 	C_OUT,	D__DX,		D__AL,		D__NONE,	"OUT" 		,0xee,1,MAKE_OP_RW_FLAG(OP_R,OP_R,0)}, //0xee
	{ 0 , 	C_OUT,	D__DX,		D__eX,		D__NONE,	"OUT" 		,0xef,1,MAKE_OP_RW_FLAG(OP_R,OP_R,0)}, //0xef

	{ 0 , 	C_LOCK,		D__NONE,	D__NONE,	D__NONE,	"LOCK"	,0xf0,1}, //0xf0
	{ 0 , 	C_INT1,		D__NONE,	D__NONE,	D__NONE,	"INT1" 	,0xf1,1}, //0xf1
	{ 0 , 	C_REPN,		D__NONE,	D__NONE,	D__NONE,	"REPNE"	,0xf2,1}, //0xf2
	{ 0 , 	C_REPZ,		D__NONE,	D__NONE,	D__NONE,	"REP"	,0xf3,1}, //0xf3
	{ 0 , 	C_HLT,		D__NONE,	D__NONE,	D__NONE,	"HLT" 	,0xf4,1}, //0xf4
	{ 0 , 	C_CMC,		D__NONE,	D__NONE,	D__NONE,	"CMC" 	,0xf5,1}, //0xf5
	{R_M, 	C_GRP,		D__Eb,		D__NONE,	D__NONE,	(char*)Group0xf6			,0xf6,1}, //0xf6
	{R_M, 	C_GRP,		D__Ev,		D__NONE,	D__NONE,	(char*)Group0xf7			,0xf7,1}, //0xf7
	{ 0 , 	C_CLC,		D__NONE,	D__NONE,	D__NONE,	"CLC" 		,0xf8,1}, //0xf8
	{ 0 , 	C_STC,		D__NONE,	D__NONE,	D__NONE,	"STC" 		,0xf9,1}, //0xf9
	{ 0 , 	C_CLI,		D__NONE,	D__NONE,	D__NONE,	"CLI" 		,0xfa,1}, //0xfa
	{ 0 , 	C_STI,		D__NONE,	D__NONE,	D__NONE,	"STI" 		,0xfb,1}, //0xfb
	{ 0 , 	C_CLD,		D__NONE,	D__NONE,	D__NONE,	"CLD" 		,0xfc,1}, //0xfc
	{ 0 , 	C_STD,		D__NONE,	D__NONE,	D__NONE,	"STD" 		,0xfd,1}, //0xfd
	{R_M, 	C_GRP,		D__Eb,		D__NONE,	D__NONE,	(char*)Group0xfe			,0xfe,1}, //0xfe
	{R_M, 	C_GRP,		D__Ev,		D__NONE,	D__NONE,	(char*)Group0xff			,0xff,1},  //0xff
//________________________________________________________________________________________
//________________________________________________________________________________________
	{R_M ,   C_INS,		D__Yb,	 D__DX,	D__NONE, 	"INSB"   ,0x6c,1,MAKE_OP_RW_FLAG(OP_W,OP_R,0)},//0x6c,
	{R_M ,   C_INS,		D__Yw,	 D__DX,	D__NONE, 	"INSW"   ,0x6d,1,MAKE_OP_RW_FLAG(OP_W,OP_R,0)},//0x6d,
	{R_M ,   C_INS,		D__Yd,	 D__DX,	D__NONE, 	"INSD"   ,0x6d,1,MAKE_OP_RW_FLAG(OP_W,OP_R,0)},//0x6d,
	{R_M ,   C_OUTS,	D__DX,	 D__Xb,	D__NONE, 	"OUTSB"  ,0x6e,1,MAKE_OP_RW_FLAG(OP_R,OP_R,0)},//0x6e,
	{R_M ,   C_OUTS,	D__DX,	 D__Xw,	D__NONE, 	"OUTSW"  ,0x6f,1,MAKE_OP_RW_FLAG(OP_R,OP_R,0)},//0x6f,
	{R_M ,   C_OUTS,	D__DX,	 D__Xd,	D__NONE, 	"OUTSD"  ,0x6f,1,MAKE_OP_RW_FLAG(OP_R,OP_R,0)},//0x6f,
//______________________________________________
//______________________________________________


	{0 |D_64,     C_PUSHF,	D__NONE,	 D__NONE,D__NONE,  "PUSHFD" ,0x9c,1,MAKE_OP_RW_FLAG(OP_R,0,0)},//0x9c,
	{0 |D_64,     C_POPF,	D__NONE,	 D__NONE,D__NONE,  "POPFD"  ,0x9d,1,MAKE_OP_RW_FLAG(OP_W,0,0)},//0x9d,
	{0 ,			C_PUSHA,	D__NONE,	 D__NONE,D__NONE,  "PUSHAD" ,0x60,1,MAKE_OP_RW_FLAG(OP_R,0,0)},//0x60,
	{0 ,		C_POPA,		D__NONE,	 D__NONE,D__NONE,  "POPAD"  ,0x61,1,MAKE_OP_RW_FLAG(OP_W,0,0)},//0x61,
//____________________________________
//____________________________________
	{R_M ,     C_MOVS,	D__Yb,	 D__NONE,D__NONE, 	"MOVSB" ,0xa4,1,MAKE_OP_RW_FLAG(OP_W,OP_R,0)},//0xa4,
	{R_M ,     C_MOVS,	D__Yw,	 D__NONE,D__NONE, 	"MOVSW" ,0xa5,1,MAKE_OP_RW_FLAG(OP_W,OP_R,0)},//0xa5,
	{R_M ,     C_MOVS,	D__Yd,	 D__NONE,D__NONE, 	"MOVSD" ,0xa5,1,MAKE_OP_RW_FLAG(OP_W,OP_R,0)},//0xa5,
	{R_M ,     C_MOVS,	D__Yd,	 D__NONE,D__NONE, 	"MOVSQ" ,0xa5,1,MAKE_OP_RW_FLAG(OP_W,OP_R,0)},//0xa5,
	{R_M ,     C_CMPS,	D__Yb,	 D__NONE,D__NONE, 	"CMPSB" ,0xa6,1,MAKE_OP_RW_FLAG(OP_R,OP_R,0)},//0xa6,
	{R_M ,     C_CMPS,	D__Yw,	 D__NONE,D__NONE, 	"CMPSW" ,0xa7,1,MAKE_OP_RW_FLAG(OP_R,OP_R,0)},//0xa7,
	{R_M ,     C_CMPS,	D__Yd,	 D__NONE,D__NONE, 	"CMPSD" ,0xa7,1,MAKE_OP_RW_FLAG(OP_R,OP_R,0)},//0xa7,
	{R_M ,     C_CMPS,	D__Yd,	 D__NONE,D__NONE, 	"CMPSQ" ,0xa7,1,MAKE_OP_RW_FLAG(OP_R,OP_R,0)},//0xa7,
	{R_M ,     C_STOS,	D__Yb,	 D__NONE,D__NONE, 	"STOSB" ,0xaa,1,MAKE_OP_RW_FLAG(OP_W,0,0)},//0xaa,
	{R_M ,     C_STOS,	D__Yw,	 D__NONE,D__NONE, 	"STOSW" ,0xab,1,MAKE_OP_RW_FLAG(OP_W,0,0)},//0xab,
	{R_M ,     C_STOS,	D__Yd,	 D__NONE,D__NONE, 	"STOSD" ,0xab,1,MAKE_OP_RW_FLAG(OP_W,0,0)},//0xab,
	{R_M ,     C_STOS,	D__Yd,	 D__NONE,D__NONE, 	"STOSQ" ,0xab,1,MAKE_OP_RW_FLAG(OP_W,0,0)},//0xab,
	{R_M ,     C_LODS,	D__AL,	 D__Xb,	D__NONE, 	"LODSB" ,0xac,1,MAKE_OP_RW_FLAG(OP_W,OP_R,0)},//0xac,
	{R_M ,     C_LODS,	D__AX,	 D__Xw,	D__NONE, 	"LODSW" ,0xad,1,MAKE_OP_RW_FLAG(OP_W,OP_R,0)},//0xad,
	{R_M ,     C_LODS,	D__EAX,	 D__Xd,	D__NONE, 	"LODSD" ,0xad,1,MAKE_OP_RW_FLAG(OP_W,OP_R,0)},//0xad,
	{R_M ,     C_LODS,	D__EAX,	 D__Xd,	D__NONE, 	"LODSQ" ,0xad,1,MAKE_OP_RW_FLAG(OP_W,OP_R,0)},//0xad,
	{R_M ,     C_SCAS,	D__Yb,	 D__NONE,D__NONE, 	"SCASB" ,0xae,1,MAKE_OP_RW_FLAG(OP_R,OP_R,0)},//0xae,
	{R_M ,     C_SCAS,	D__Yw,	 D__NONE,D__NONE, 	"SCASW" ,0xaf,1,MAKE_OP_RW_FLAG(OP_R,OP_R,0)},//0xaf,
	{R_M ,     C_SCAS,	D__Yd,	 D__NONE,D__NONE, 	"SCASD" ,0xaf,1,MAKE_OP_RW_FLAG(OP_R,OP_R,0)},//0xaf,
	{R_M ,     C_SCAS,	D__Yd,	 D__NONE,D__NONE, 	"SCASQ" ,0xaf,1,MAKE_OP_RW_FLAG(OP_R,OP_R,0)},//0xaf,
//____________________________________							  
//____________________________________
	{0 ,     C_XLAT,	D__NONE, D__NONE,D__NONE, 	"XLATB" ,0xd7,1},//0xd7,
//____________________________________
//____________________________________
	{0 ,     C_REPN,	D__NONE, D__NONE,D__NONE,   "REPNZ" ,0xf2,1},//0xf2
	{0 ,     C_REPZ,	D__NONE, D__NONE,D__NONE, 	"REPZ"  ,0xf3,1},//0xf3
	{0 ,     C_REPZ,	D__NONE, D__NONE,D__NONE, 	"REPE"  ,0xf3,1},//0xf3
//____________________________________
//____________________________________

	{0 |Immediate_Jb,     C_JtC,	D__Jb,	 D__NONE, D__NONE, 	"JB"    ,0x72,1},//0x72,
	{0 |Immediate_Jb,     C_JtC,	D__Jb,	 D__NONE, D__NONE, 	"JNAE"  ,0x72,1},//0x72,
	{0 |Immediate_Jb,     C_JfC,	D__Jb,	 D__NONE, D__NONE, 	"JAE"   ,0x73,1},//0x73,
	{0 |Immediate_Ib,     C_JfC,	D__Jb,	 D__NONE, D__NONE, 	"JNB"   ,0x73,1},//0x73,
	{0 |Immediate_Ib,     C_JtZ,	D__Jb,	 D__NONE, D__NONE, 	"JE"    ,0x74,1},//0x74,
	{0 |Immediate_Ib,     C_JfZ,	D__Jb,	 D__NONE, D__NONE, 	"JNE"   ,0x75,1},//0x75,
	{0 |Immediate_Ib,     C_JfA,	D__Jb,	 D__NONE, D__NONE, 	"JBE"   ,0x76,1},//0x76,
	{0 |Immediate_Jb,     C_JtA,	D__Jb,	 D__NONE, D__NONE, 	"JNBE"  ,0x77,1},//0x77,
	{0 |Immediate_Jb,     C_JtP,	D__Jb,	 D__NONE, D__NONE, 	"JPE"   ,0x7a,1},//0x7a,
	{0 |Immediate_Jb,     C_JfP,	D__Jb,	 D__NONE, D__NONE, 	"JPO"   ,0x7b,1},//0x7b,
	{0 |Immediate_Jb,     C_JtL,	D__Jb,	 D__NONE, D__NONE, 	"JNGE"  ,0x7c,1},//0x7c,
	{0 |Immediate_Ib,     C_JfL,	D__Jb,	 D__NONE, D__NONE, 	"JGE"   ,0x7d,1},//0x7d,
	{0 |Immediate_Ib,     C_JfG,	D__Jb,	 D__NONE, D__NONE, 	"JLE"   ,0x7e,1},//0x7e,
	{0 |Immediate_Ib,     C_JtG,	D__Jb,	 D__NONE, D__NONE, 	"JNLE"  ,0x7f,1},//0x7f,

	{ 0 |Immediate_Jv|F_64, C_JtC,		D__Jz,		D__tC,	D__NONE,	"JB" 		,0x820f,2}, //0x82
	{ 0 |Immediate_Jv|F_64, C_JtC,		D__Jz,		D__tC,	D__NONE,	"JNAE" 		,0x820f,2}, //0x82
	{ 0 |Immediate_Jv|F_64, C_JfC,		D__Jz,		D__fC,	D__NONE,	"JNB" 		,0x830f,2}, //0x83
	{ 0 |Immediate_Jv|F_64, C_JfC,		D__Jz,		D__fC,	D__NONE,	"JAE" 		,0x830f,2}, //0x83
	{ 0 |Immediate_Jv|F_64, C_JtZ,		D__Jz,		D__tZ,	D__NONE,	"JE" 		,0x840f,2}, //0x84
	{ 0 |Immediate_Jv|F_64, C_JfZ,		D__Jz,		D__fZ,	D__NONE,	"JNE" 		,0x850f,2}, //0x85
	{ 0 |Immediate_Jv|F_64, C_JfA,		D__Jz,		D__fA,	D__NONE,	"JBE" 		,0x860f,2}, //0x86
	{ 0 |Immediate_Jv|F_64, C_JtA,		D__Jz,		D__tA,	D__NONE,	"JNBE" 		,0x870f,2}, //0x87
	{ 0 |Immediate_Jv|F_64, C_JtP,		D__Jz,		D__tP,	D__NONE,	"JPE" 		,0x8a0f,2}, //0x8a
	{ 0 |Immediate_Jv|F_64, C_JfP,		D__Jz,		D__fP,	D__NONE,	"JPO" 		,0x8b0f,2}, //0x8b
	{ 0 |Immediate_Jv|F_64, C_JtL,		D__Jz,		D__tL,	D__NONE,	"JNGE" 		,0x8c0f,2}, //0x8c
	{ 0 |Immediate_Jv|F_64, C_JfL,		D__Jz,		D__fL,	D__NONE,	"JGE" 		,0x8d0f,2}, //0x8d
	{ 0 |Immediate_Jv|F_64, C_JfG,		D__Jz,		D__fG,	D__NONE,	"JLE" 		,0x8e0f,2}, //0x8e
	{ 0 |Immediate_Jv|F_64, C_JtG,		D__Jz,		D__tG,	D__NONE,	"JNLE" 		,0x8f0f,2}, //0x8f
	{R_M, C_SETtC,	D__wEb,		D__tC,	D__NONE,	"SETB" 	,0x920f,2,MAKE_OP_RW_FLAG(OP_R,0,0)}, //0x92
	{R_M, C_SETtC,	D__wEb,		D__tC,	D__NONE,	"SETNAE",0x920f,2,MAKE_OP_RW_FLAG(OP_R,0,0)}, //0x92
	{R_M, C_SETfC,	D__wEb,		D__fC,	D__NONE,	"SETNB" ,0x930f,2,MAKE_OP_RW_FLAG(OP_R,0,0)}, //0x93
	{R_M, C_SETfC,	D__wEb,		D__fC,	D__NONE,	"SETAE" ,0x930f,2,MAKE_OP_RW_FLAG(OP_R,0,0)}, //0x93
	{R_M, C_SETtZ,	D__wEb,		D__tZ,	D__NONE,	"SETE" 	,0x940f,2,MAKE_OP_RW_FLAG(OP_R,0,0)}, //0x94
	{R_M, C_SETfZ,	D__wEb,		D__fZ,	D__NONE,	"SETNE" ,0x950f,2,MAKE_OP_RW_FLAG(OP_R,0,0)}, //0x95
	{R_M, C_SETfA,	D__wEb,		D__fA,	D__NONE,	"SETBE" ,0x960f,2,MAKE_OP_RW_FLAG(OP_R,0,0)}, //0x96
	{R_M, C_SETtA,	D__wEb,		D__tA,	D__NONE,	"SETNBE",0x970f,2,MAKE_OP_RW_FLAG(OP_R,0,0)}, //0x97
	{R_M, C_SETtP,	D__wEb,		D__tP,	D__NONE,	"SETPE" ,0x9a0f,2,MAKE_OP_RW_FLAG(OP_R,0,0)}, //0x9a
	{R_M, C_SETfP,	D__wEb,		D__fP,	D__NONE,	"SETPO" ,0x9b0f,2,MAKE_OP_RW_FLAG(OP_R,0,0)}, //0x9b
	{R_M, C_SETtL,	D__wEb,		D__tL,	D__NONE,	"SETNGE",0x9c0f,2,MAKE_OP_RW_FLAG(OP_R,0,0)}, //0x9c
	{R_M, C_SETfL,	D__wEb,		D__fL,	D__NONE,	"SETGE" ,0x9d0f,2,MAKE_OP_RW_FLAG(OP_R,0,0)}, //0x9d
	{R_M, C_SETfG,	D__wEb,		D__fG,	D__NONE,	"SETLE" ,0x9e0f,2,MAKE_OP_RW_FLAG(OP_R,0,0)}, //0x9e
	{R_M, C_SETtG,	D__wEb,		D__tG,	D__NONE,	"SETNLE",0x9f0f,2,MAKE_OP_RW_FLAG(OP_R,0,0)}, //0x9f


	//____________________________________	
	{R_M, C_CMOVtC,	D__Gv,		D__rEv,		D__tC,	"CMOVNAE" 	,0x420f,2,MAKE_OP_RW_FLAG(OP_RW,OP_R,0)}, //0x42
	{R_M, C_CMOVtC,	D__Gv,		D__rEv,		D__tC,	"CMOVC" 	,0x420f,2,MAKE_OP_RW_FLAG(OP_RW,OP_R,0)}, //0x42
	{R_M, C_CMOVfC,	D__Gv,		D__rEv,		D__fC,	"CMOVNC" 	,0x430f,2,MAKE_OP_RW_FLAG(OP_RW,OP_R,0)}, //0x43
	{R_M, C_CMOVfC,	D__Gv,		D__rEv,		D__fC,	"CMOVAE" 	,0x430f,2,MAKE_OP_RW_FLAG(OP_RW,OP_R,0)}, //0x43
	{R_M, C_CMOVtZ,	D__Gv,		D__rEv,		D__tZ,	"CMOVE" 	,0x440f,2,MAKE_OP_RW_FLAG(OP_RW,OP_R,0)}, //0x44
	{R_M, C_CMOVfZ,	D__Gv,		D__rEv,		D__fZ,	"CMOVNE" 	,0x450f,2,MAKE_OP_RW_FLAG(OP_RW,OP_R,0)}, //0x45
	{R_M, C_CMOVfA,	D__Gv,		D__rEv,		D__fA,	"CMOVNA" 	,0x460f,2,MAKE_OP_RW_FLAG(OP_RW,OP_R,0)}, //0x46
	{R_M, C_CMOVtA,	D__Gv,		D__rEv,		D__tA,	"CMOVNBE" 	,0x470f,2,MAKE_OP_RW_FLAG(OP_RW,OP_R,0)}, //0x47
	{R_M, C_CMOVtP,	D__Gv,		D__rEv,		D__tP,	"CMOVPE" 	,0x4a0f,2,MAKE_OP_RW_FLAG(OP_RW,OP_R,0)}, //0x4a
	{R_M, C_CMOVfP,	D__Gv,		D__rEv,		D__fP,	"CMOVPO" 	,0x4b0f,2,MAKE_OP_RW_FLAG(OP_RW,OP_R,0)}, //0x4b
	{R_M, C_CMOVtL,	D__Gv,		D__rEv,		D__tL,	"CMOVNGE" 	,0x4c0f,2,MAKE_OP_RW_FLAG(OP_RW,OP_R,0)}, //0x4c
	{R_M, C_CMOVfL,	D__Gv,		D__rEv,		D__fL,	"CMOVNL" 	,0x4d0f,2,MAKE_OP_RW_FLAG(OP_RW,OP_R,0)}, //0x4d
	{R_M, C_CMOVfG,	D__Gv,		D__rEv,		D__fG,	"CMOVNG" 	,0x4e0f,2,MAKE_OP_RW_FLAG(OP_RW,OP_R,0)}, //0x4e
	{R_M, C_CMOVtG,	D__Gv,		D__rEv,		D__tG,	"CMOVNLE" 	,0x4f0f,2,MAKE_OP_RW_FLAG(OP_RW,OP_R,0)}, //0x4f
	{ 0 |Immediate_Jb, 	C_LOOPNZ,	D__Jb,		D__NONE,	D__NONE,	"LOOPNE" 		,0xe0,1}, //0xe0
	{ 0 |Immediate_Jb, 	C_LOOPZ,	D__Jb,		D__NONE,	D__NONE,	"LOOPE" 		,0xe1,1}, //0xe1
	{ 0 , C_NOP,		D__NONE,D__NONE,			D__NONE,"NOP"	,	0x90,1},
//____________________________________	
	{R_M ,     C_DBYTE,	D_DBYTE,	D__NONE,	D__NONE, "DB"	}, //db xx
	{R_M ,     C_DWORD,	D_DWORD,	D__NONE,	D__NONE, "DW"	}, //dw xx
	{R_M ,     C_DDWORD,D_DDWORD,	D__NONE,	D__NONE, "DD"	}, //dd xx
	{R_M ,     C_DBYTE,	D_STRING,	D__NONE,	D__NONE, "DB"	}, //db xx
//____________________________________	

};

DIS_OPCODE_T RexPrefixFor64Bit[]=
{
	{0 ,     C_REX_PREFIX,	D__NONE,	D__NONE,	D__NONE, ""	}, //Rex prefix only for 64 bit
};

//______________________________________________________	
//______________________________________________________	

int GetEffectAddress32Dis(DIS_CPU * pDisCPU,BYTE *pbuff,DISP_INSTRUCTION_T *disp_i)
{
	int r_m,reg,mod,base,index,scale;
	int length;
	QWORD base_index;
	QWORD base_register_val;
	r_m = ((DIS_MODR_M*)pbuff)->r_m;
	reg = ((DIS_MODR_M*)pbuff)->reg;
	mod = ((DIS_MODR_M*)pbuff)->mod;
	reg |= ((disp_i->rex_prefix & 0x4)<<1);
	if(disp_i->rex_prefix & 0x8)  // if ture then ignore 0x66 prefix
	{
		disp_i->os_32=BIT64;
	}
	disp_i->rm = r_m;
	disp_i->nnn = reg;
	disp_i->mod = mod;
	
	disp_i->have_regrm=1;
	disp_i->have_sib=-1;
	if (r_m==4)// 这个指令有 SIB 字节
	{
		base = ((DIS_MODR_M*)pbuff)->base;
		index = ((DIS_MODR_M*)pbuff)->index;
		scale = ((DIS_MODR_M*)pbuff)->scale;
		if(disp_i->mode==BIT64)
		{
			index |= ((disp_i->rex_prefix & 0x2)<<2);
			base |= ((disp_i->rex_prefix & 0x1)<<3);
			disp_i->rm |= ((disp_i->rex_prefix & 0x1)<<3);
		}
		disp_i->have_sib=1;
		pbuff += 2;    //skip modrm and sib byte

		disp_i->base = base;
		if((disp_i->base&0x7)==5 && mod==0)   //only ebp as base register is not used
			disp_i->base=0-1;
		disp_i->index = index;
		disp_i->scale = scale;
		if(disp_i->base==-1)
			base_register_val=0;
		else
			base_register_val=pDisCPU->gen_reg[base].erx;
		if (index==4)  //rsp must not be index register
		{
			base_index = base_register_val;
			disp_i->index = 0-1;
		}
		else
		{
			base_index = base_register_val + (pDisCPU->gen_reg[index].erx<<scale);
		}

		if (disp_i->base==4 || disp_i->base==5) 
			disp_i->seg = I_SS;
		else 
			disp_i->seg = I_DS;

		switch(mod)
		{
		case 0:

			if ((base&0x7)==5)
			{   // address form [xxxxxxxx] there is a modrm and a sib byte
				disp_i->addr_displacement = (__int64)(int)GetValue_d(pbuff);
				disp_i->displacement_size = sizeof(DWORD);
				length = 0x06;
				
				if (index==4) 
					base_index = 0;
				else
					base_index = (pDisCPU->gen_reg[index].erx<<scale);

				disp_i->seg = I_DS;
			}
			else
			{  // address form [register]
				disp_i->addr_displacement = 0;
				disp_i->displacement_size = 0;
				length = 0x02;
			}
			
			break;

		case 1:

			disp_i->addr_displacement = (long)(*(char*)pbuff);
			disp_i->displacement_size = sizeof(BYTE);
			length = 0x03;
			break;

		case 2:

			disp_i->addr_displacement = (__int64)(int)GetValue_d(pbuff);
			disp_i->displacement_size = sizeof(DWORD);
			length = 0x06;
			break;

		case 3: //mod == 3
			disp_i->displacement_size = 0;
			length = 0x01;
			disp_i->have_sib=-1;
			break;
		}
	}
	else
	{
		pbuff++;//skip modrm byte
		r_m |= ((disp_i->rex_prefix & 0x1)<<3);
		disp_i->base = r_m;
		disp_i->index = 0-1;
		disp_i->scale = 0;
		disp_i->rm = r_m;
		base_index = pDisCPU->gen_reg[r_m].erx;

		if (r_m==4 || r_m==5) 
			disp_i->seg = I_SS;
		else 
			disp_i->seg = I_DS;

		switch(mod)
		{
		case 0:

			if ((r_m&7)==5)
			{
				disp_i->addr_displacement = (__int64)(int)GetValue_d(pbuff);
				disp_i->displacement_size = sizeof(DWORD);
				if(disp_i->mode==BIT64)
				{
					disp_i->seg = I_CS;
					disp_i->RIP_Relative=1;
					//disp_i->displacement_size=sizeof(QWORD);
				}
				else
					disp_i->seg = I_DS;
				base_index = 0;
				disp_i->base = 0-1;
			}
			else
			{
				disp_i->addr_displacement = 0;
				disp_i->displacement_size = 0;
			}

			break;

		case 1:

			disp_i->addr_displacement = (__int64)(*(char*)pbuff);
			disp_i->displacement_size = sizeof(BYTE);
			break;

		case 2:

			disp_i->addr_displacement = (__int64)GetValue_d(pbuff);
			disp_i->displacement_size = sizeof(DWORD);
			
			break;

		default: //mod == 3
			
			disp_i->displacement_size = 0;
		}

		length = disp_i->displacement_size + 1;
	}

	disp_i->rm_addr = base_index + disp_i->addr_displacement;
	//此有效地址为三十二位

	return length;
}

int GetEffectAddress16Dis(DIS_CPU * pDisCPU,BYTE *pbuff,DISP_INSTRUCTION_T *disp_i)
{
	int r_m,reg,mod;
	int length;
	DWORD base_index;
	
	r_m = ((DIS_MODR_M*)pbuff)->r_m;
	reg = ((DIS_MODR_M*)pbuff)->reg;
	mod = ((DIS_MODR_M*)pbuff)->mod;
	
	disp_i->rm = r_m;
	disp_i->nnn = reg;
	disp_i->mod = mod;
	disp_i->have_regrm=1;
	disp_i->have_sib=-1;
	pbuff++;

	disp_i->as_32 = BIT16;
	disp_i->scale = 0;

	switch(r_m)
	{
	case 0:

		base_index = pDisCPU->gen_reg[I_EBX].word.u_word.rx + pDisCPU->gen_reg[I_ESI].word.u_word.rx;
		disp_i->seg = I_DS;
		disp_i->base = INTEL_GEG_REG_EBX;
		disp_i->index = INTEL_GEG_REG_ESI;
		break;

	case 1:

		base_index = pDisCPU->gen_reg[I_EBX].word.u_word.rx + pDisCPU->gen_reg[I_EDI].word.u_word.rx;
		disp_i->seg = I_DS;
		disp_i->base = INTEL_GEG_REG_EBX;
		disp_i->index = INTEL_GEG_REG_EDI;
		break;

	case 2:
		
		base_index = pDisCPU->gen_reg[I_EBP].word.u_word.rx + pDisCPU->gen_reg[I_ESI].word.u_word.rx;
		disp_i->seg = I_SS;
		disp_i->base = INTEL_GEG_REG_EBP;
		disp_i->index = INTEL_GEG_REG_ESI;
		break;

	case 3:
		
		base_index = pDisCPU->gen_reg[I_EBP].word.u_word.rx + pDisCPU->gen_reg[I_EDI].word.u_word.rx;
		disp_i->seg = I_SS;
		disp_i->base = INTEL_GEG_REG_EBP;
		disp_i->index = INTEL_GEG_REG_EDI;
		break;

	case 4:
		
		base_index = pDisCPU->gen_reg[I_ESI].word.u_word.rx;
		disp_i->seg = I_DS;
		disp_i->base = INTEL_GEG_REG_ESI;
		disp_i->index = 0-1;
		break;

	case 5:
		
		base_index = pDisCPU->gen_reg[I_EDI].word.u_word.rx;
		disp_i->seg = I_DS;
		disp_i->base = INTEL_GEG_REG_EDI;
		disp_i->index = 0-1;
		break;

	case 6:
		
		base_index = pDisCPU->gen_reg[I_EBP].word.u_word.rx;
		disp_i->seg = I_SS;
		disp_i->base = INTEL_GEG_REG_EBP;
		disp_i->index = 0-1;
		break;
 
	case 7:
		
		base_index = pDisCPU->gen_reg[I_EBX].word.u_word.rx;
		disp_i->seg = I_DS;
		disp_i->base = INTEL_GEG_REG_EBX;
		disp_i->index = 0-1;
		break;
	};

	switch(mod)
	{
	case 0:

		if (r_m==6)
		{
			disp_i->addr_displacement = GetValue_w(pbuff);
			disp_i->displacement_size = sizeof(WORD);

			
			base_index = 0;
			disp_i->seg = I_DS;
			disp_i->base = 0-1;
			disp_i->index = 0-1;
		}
		else
		{
			disp_i->addr_displacement = 0x00;
			disp_i->displacement_size = 0;
		}
		break;

	case 1:

		disp_i->addr_displacement = (long)(*(char*)pbuff);
		disp_i->displacement_size = sizeof(BYTE);
		break;

	case 2:

		disp_i->addr_displacement = GetValue_w(pbuff);
		disp_i->displacement_size = sizeof(WORD);
		break;

	default: //mod == 3

		disp_i->displacement_size = 0;
	}

	disp_i->rm_addr = (unsigned short)(base_index + disp_i->addr_displacement);
	//此有效地址为十六位

	length = disp_i->displacement_size + 1;

	return length;
}


void DispTranDis(DIS_ADDRESS * dis_a,DISP_INSTRUCTION_T *disp_i,QWORD eip)
{
	dis_a->mod = disp_i->mod;
	dis_a->reg = disp_i->nnn;
	dis_a->r_m = disp_i->rm;
	dis_a->base = disp_i->base;
	dis_a->index = disp_i->index;
	dis_a->scale = disp_i->scale;
	dis_a->segment = disp_i->seg;
	dis_a->address_size = disp_i->as_32;
	dis_a->displacement_size = disp_i->displacement_size;
	if(disp_i->RIP_Relative)
	{
		disp_i->addr_displacement+=eip+disp_i->ilen;
		dis_a->displacement_size = 8;
	}
	dis_a->displacement = disp_i->addr_displacement;
	dis_a->effect_address = disp_i->rm_addr;

	return ;
}

//——————————————反汇编模块————————————————

bool ProcessName_dis(INSTRUCTION_INFORMATION* pInstInfo,DIS_OPCODE_T *pIntelOpcode,int OperandSize,int AddressSize)
{
	int opcodetype,Opdata1,Opdata2;

	opcodetype = pIntelOpcode->OpcodeType;
	Opdata1 = pIntelOpcode->Opdata1;
	Opdata2 = pIntelOpcode->Opdata2;

	if (pInstInfo->Lock==0xf0)
		strcpy(pInstInfo->LockName,"LOCK");
	else
		pInstInfo->LockName[0] = '\0';

	if (pInstInfo->Repeat==0xf2)
		strcpy(pInstInfo->RepeatName,"REPNE");
	else if	(pInstInfo->Repeat==0xf3) 
		strcpy(pInstInfo->RepeatName,"REP");
	else
		pInstInfo->RepeatName[0] = '\0';
	
	if (opcodetype==C_NULL)
		return false;

	strcpy(pInstInfo->Name,pIntelOpcode->name);

	if (Opdata1>=D__Xb&&Opdata1<=D_wXb||Opdata1>=D__Yb&&Opdata1<=D__wYb||
		Opdata2>=D__Xb&&Opdata2<=D_wXb||Opdata2>=D__Yb&&Opdata2<=D__wYb)
		sprintf(pInstInfo->Name,"%sB",pIntelOpcode->name);
	if (Opdata1>=D__Xv&&Opdata1<=D_wXv||Opdata1>=D__Yv&&Opdata1<=D__wYv||
		Opdata2>=D__Xv&&Opdata2<=D_wXv||Opdata2>=D__Yv&&Opdata2<=D__wYv)
	{
		switch(OperandSize)
		{
		case BIT16:
			sprintf(pInstInfo->Name,"%sW",pIntelOpcode->name);
			break;
		case BIT32:
			sprintf(pInstInfo->Name,"%sD",pIntelOpcode->name);
			break;
		case BIT64:
			sprintf(pInstInfo->Name,"%sQ",pIntelOpcode->name);
			break;
		}
	}
	switch(OperandSize)
	{
	case BIT16:
		break;
	case BIT32:
		switch(opcodetype)
		{
		case C_CBW:
			strcpy(pInstInfo->Name,"CWDE");
			break;

		case C_CWD:
			strcpy(pInstInfo->Name,"CDQ");
			break;

		case C_PUSHA:
			strcpy(pInstInfo->Name,"PUSHAD");
			break;

		case C_POPA:
			strcpy(pInstInfo->Name,"POPAD");
			break;

		case C_PUSHF:
			strcpy(pInstInfo->Name,"PUSHFD");
			break;

		case C_POPF:
			strcpy(pInstInfo->Name,"POPFD");
			break;

		case C_JCXZ:
			strcpy(pInstInfo->Name,"JECXZ");
			break;

		case C_IRET:
			strcpy(pInstInfo->Name,"IRETD");
			break;
		case C_MOVD:
			strcpy(pInstInfo->Name,"MOVD");
			break;
		case C_PEXTRD:
			strcpy(pInstInfo->Name,"pextrd");
			break;
		case C_PINSRD:
			strcpy(pInstInfo->Name,"pinsrd");
			break;
		};
		break;
	case BIT64:
		switch(opcodetype)
		{
		case C_CMPXCHG8B:
			if(pInstInfo->Rex_Prefix&0x8)
				strcpy(pInstInfo->Name,"CMPXCHG16B");
			break;
		case C_CBW:
			strcpy(pInstInfo->Name,"CDQE");
			break;

		case C_CWD:
			strcpy(pInstInfo->Name,"CQO");
			break;

		case C_PUSHA:
			strcpy(pInstInfo->Name,"");
			break;

		case C_POPA:
			strcpy(pInstInfo->Name,"");
			break;

		case C_PUSHF:
			strcpy(pInstInfo->Name,"PUSHFQ");
			break;

		case C_POPF:
			strcpy(pInstInfo->Name,"POPFQ");
			break;

		case C_JCXZ:
			strcpy(pInstInfo->Name,"JRCXZ");
			break;

		case C_IRET:
			strcpy(pInstInfo->Name,"IRETQ");
			break;
		case C_MOVD:
			strcpy(pInstInfo->Name,"MOVQ");
			break;
		case C_PEXTRD:
			strcpy(pInstInfo->Name,"pextrq");
			break;
		case C_PINSRD:
			strcpy(pInstInfo->Name,"pinsrq");
			break;
		};
		break;
	}

	return true;
}

int ProcessOpdata_dis(int opdata,POPERAND_ITEM op,QWORD eip,DISP_INSTRUCTION_T *disp_i,DIS_CPU *pDisCPU)
{
	int OperandSize = disp_i->os_32;
	int AddressSize = disp_i->as_32;
	__int64 k;
	int opimmedlength;

	int SIZE_c,SIZE_v,SIZE_p,SIZE_z,SIZE_s1,SIZE_y;

	switch(OperandSize)
	{
	case BIT32:
		SIZE_v = 4;
		SIZE_c = 2;
		SIZE_p = 6;
		SIZE_z=4;
		SIZE_s1=6;
		SIZE_y=4;
		break;
	case BIT16:
		SIZE_v = 2;
		SIZE_c = 1;
		SIZE_p = 4;
		SIZE_z=2;
		SIZE_s1=6;
		SIZE_y=4;
		break;
	case BIT64:
		SIZE_v = 8;
		SIZE_c = 2;
		SIZE_p = 10;			
		SIZE_z=4;
		SIZE_s1=10;
		SIZE_y=8;

		break;
	}
	

	opimmedlength = 0;
	op->mode = mode_invalid;
	op->opersize = 0;
	
	switch(opdata)
	{
	case D__NONE:
		break;

	case D__1:
		op->mode = mode_immed;
		op->opersize = 1;
		op->immed.immed_value = 1;
		strcpy(op->string,"1");
		break;

	// Immediate data. The operand value is encoded in subsequent bytes of the instruction.
	case D__Ib:
		op->mode = mode_immed;
		op->opersize = SIZE_b;
		opimmedlength = SIZE_b;
		op->immed.immed_value = disp_i->Ib;
		if(disp_i->Ib>=0xa0)
			sprintf(op->string,"0%X",op->immed.immed_value);
		else
			sprintf(op->string,"%X",op->immed.immed_value);

		break;
	case D__Ib2:
		op->mode = mode_immed;
		op->opersize = SIZE_b;
		opimmedlength = SIZE_b;
		op->immed.immed_value = disp_i->Ib2;
		//sprintf(op->string,"%02X",op->immed.immed_value);
		if(disp_i->Ib2>=0xa0)
			sprintf(op->string,"0%X",op->immed.immed_value);
		else
			sprintf(op->string,"%X",op->immed.immed_value);
		break;

	case D__sIb:
		{
			__int64 value;
			op->mode = mode_immed;
			op->opersize = SIZE_b;
			opimmedlength = SIZE_b;
			value=(int)disp_i->Ib;
			op->immed.immed_value = value;
			k = op->immed.immed_value;
			if (k>=sign_BYTE) 
				sprintf(op->string,"-%X",(BYTE)(0-k));
			else 
				sprintf(op->string,"%X",(BYTE)k);
			break;
		}
	case D__Iw:
		op->mode = mode_immed;
		op->opersize = SIZE_w;
		opimmedlength = SIZE_w;
		op->immed.immed_value = disp_i->Iw;
		
		sprintf(op->string,"%X",op->immed.immed_value);

		break;
	case D__Iv:
		op->mode = mode_immed;
		op->opersize = SIZE_v;
		opimmedlength = SIZE_v;
		if (SIZE_v==SIZE_w)
		{
			op->immed.immed_value = disp_i->Iw;
			if(disp_i->Iw>=0xa000)
				sprintf(op->string,"0%X",op->immed.immed_value);
			else
				sprintf(op->string,"%X",op->immed.immed_value);
		}
		else if (SIZE_v==SIZE_d)
		{
			op->immed.immed_value = disp_i->Id;
			if(disp_i->Id>=0xa0000000)
				sprintf(op->string,"0%X",op->immed.immed_value);
			else
				sprintf(op->string,"%X",op->immed.immed_value);
		}
		else if(SIZE_v==SIZE_q)
		{
			op->immed.immed_value = disp_i->Iq;
			if(disp_i->Iq>=0xa000000000000000I64)
				sprintf(op->string,"0%I64X",op->immed.immed_value);
			else
				sprintf(op->string,"%I64X",op->immed.immed_value);
		}
		break;
	case D__Iz:
		op->mode = mode_immed;
		op->opersize = SIZE_z;
		opimmedlength = SIZE_z;
		if (SIZE_z==SIZE_w)
		{
			op->immed.immed_value = disp_i->Iw;
			if(disp_i->Iw>=0xa000)
				sprintf(op->string,"0%X",op->immed.immed_value);
			else
				sprintf(op->string,"%X",op->immed.immed_value);
		}
		else 
		{
			if(OperandSize==BIT64)
			{
				__int64 value=(int)disp_i->Id;
				if(value<0)
				{
					sprintf(op->string,"0%I64X",value);
				}
				else
				{
					sprintf(op->string,"%I64X",value);
				}
			}
			else
			{
				op->immed.immed_value = disp_i->Id;
				if(disp_i->Id>=0xa0000000)
					sprintf(op->string,"0%X",op->immed.immed_value);
				else
					sprintf(op->string,"%X",op->immed.immed_value);
			}
		}
		
		break;

	// The instruction contains a relative offset to be added to the instruction pointer register
	// (for example, JMP (0E9), LOOP).
	case D__Jb:
		op->mode = mode_near;
		op->opersize = SIZE_b;
		op->nearptr.offset = (__int64)(char)disp_i->Ib;
		opimmedlength = 1;

		k = eip+disp_i->ilen+op->nearptr.offset;

		op->nearptr.label = k;

		switch(OperandSize)
		{
			case BIT32:sprintf(op->string,"%08X",k);break;
			case BIT16:sprintf(op->string,"%04X",k);break;
			case BIT64:sprintf(op->string,"%016I64X",k);break;
		}
		break;

	case D__Jz:
		op->mode = mode_near;
		op->opersize = SIZE_z;

		switch(SIZE_z)
		{
		case SIZE_w:
			op->nearptr.offset = (int)(short)disp_i->Iw;
			break;
		case SIZE_d:
			op->nearptr.offset = (__int64)(int)disp_i->Id;
			break;
		}
		opimmedlength = SIZE_z;

		k = eip+disp_i->ilen+op->nearptr.offset;

		op->nearptr.label = k;
		
		switch(OperandSize)
		{
		case BIT32:sprintf(op->string,"%08X",k);break;
		case BIT16:sprintf(op->string,"%04X",k);break;
		case BIT64:sprintf(op->string,"%016I64X",k);break;
		}
		break;

	// The instruction has no ModR/M byte; the offset of the operand is coded as a word or
	// double word (depending on address size attribute) in the instruction. No base register,
	// index register, or scaling factor can be applied (for example, MOV (A0-A3)).
	case D__Ob:if (op->opersize==0)op->opersize = SIZE_b,op->rwflag = RWFLG_READ|RWFLG_WRITE;;	
	case D__rOb:if (op->opersize==0)op->opersize = SIZE_b,	op->rwflag = RWFLG_READ;;
	case D__wOb:if (op->opersize==0)op->opersize = SIZE_b,op->rwflag = RWFLG_WRITE;;
	case D__rwOb:if (op->opersize==0)op->opersize = SIZE_b,op->rwflag = RWFLG_READ|RWFLG_WRITE;;

	case D__Ov:	if (op->opersize==0)op->opersize = SIZE_v,op->rwflag = RWFLG_READ|RWFLG_WRITE;
	case D__rOv:	if (op->opersize==0)op->opersize = SIZE_v,op->rwflag = RWFLG_READ;
	case D__wOv:	if (op->opersize==0)op->opersize = SIZE_v,op->rwflag = RWFLG_WRITE;
	case D__rwOv:	if (op->opersize==0)op->opersize = SIZE_v,op->rwflag = RWFLG_READ|RWFLG_WRITE;

		disp_i->base = 0-1;
		disp_i->index = 0-1;
		disp_i->scale = 0;
		disp_i->seg = I_DS;
		if (AddressSize==BIT64)
		{
			disp_i->as_32 = BIT64;
			disp_i->displacement_size = 8;
			disp_i->addr_displacement = disp_i->Iq;
			opimmedlength = 8;
			sprintf(op->string,"%016I64X",disp_i->addr_displacement);
		} 
		else if (AddressSize==BIT32)
		{
			disp_i->as_32 = BIT32;
			disp_i->displacement_size = 4;
			disp_i->addr_displacement = disp_i->Id;
			opimmedlength = 4;
			sprintf(op->string,"%08X",disp_i->Id);
		}
		else
		{
			disp_i->as_32 = BIT16;
			disp_i->displacement_size = 2;
			disp_i->addr_displacement = disp_i->Iw;
			opimmedlength = 2;
			sprintf(op->string,"%04X",disp_i->Iw);
		}

		disp_i->rm_addr = disp_i->addr_displacement;

		op->mode = mode_address;
		DispTranDis(&op->addr,disp_i,eip);
		break;

	case D__Ap:

		op->mode = mode_far;
		if (OperandSize==BIT32)
		{
			op->farptr.offset = disp_i->Id;
			op->farptr.segment = disp_i->Iw2;
		}
		else
		{
			op->farptr.offset = disp_i->Iw;
			op->farptr.segment = disp_i->Iw2;
		}

		op->opersize = SIZE_p;
		opimmedlength = SIZE_p;

		if (OperandSize==BIT32)
			sprintf(op->string,"%04X:%08X",op->farptr.segment,op->farptr.offset);
		else
			sprintf(op->string,"%04X:%04X",op->farptr.segment,op->farptr.offset);

		break;
	
	// Direct address. The instruction has no ModR/M byte; the address of the operand is en-coded
	// in the instruction; and no base register, index register, or scaling factor can be
	// applied (for example, far JMP (EA)).	

	// The reg field of the ModR/M byte selects a control register (for example,
	// MOV (0F20, 0F22)).
	case D__Cd:
		if(disp_i->mode == BIT64)
			op->opersize = SIZE_q;
		else
			op->opersize = SIZE_d;
		op->mode = mode_register;
		op->reg.reg_index = disp_i->nnn;
		strcpy(op->string,RegCR[disp_i->nnn]);
		break;

	// The reg field of the ModR/M byte selects a debug register (for example,
	// MOV (0F21,0F23)).
	case D__Dd:
		if(disp_i->mode == BIT64)
			op->opersize = SIZE_q;
		else
			op->opersize = SIZE_d;
		op->mode = mode_register;
		op->reg.reg_index = disp_i->nnn;
		strcpy(op->string,RegDR[disp_i->nnn]);
		break;
	case D__Td:
		if(disp_i->mode == BIT64)
			op->opersize = SIZE_q;
		else
			op->opersize = SIZE_d;
		op->mode = mode_register;
		op->reg.reg_index = disp_i->nnn;
		strcpy(op->string,RegTR[disp_i->nnn]);
		break;
	// EFLAGS Register.
	case D__Fv:
					break;

	// The reg field of the ModR/M byte selects a general register (for example, AX (000)).	
	case D__Gb:if (op->opersize==0)op->opersize = SIZE_b,op->rwflag = RWFLG_READ|RWFLG_WRITE;;
	case D__rGb:if (op->opersize==0)op->opersize = SIZE_b,op->rwflag = RWFLG_READ;;
	case D__wGb:if (op->opersize==0)op->opersize = SIZE_b,op->rwflag = RWFLG_WRITE;;
		op->mode = mode_register;
		op->reg.reg_index = disp_i->nnn;
		if(disp_i->mode==BIT64 && disp_i->rex_prefix)
			strcpy(op->string,RegByteFor64bit[disp_i->nnn]);
		else
			strcpy(op->string,RegByte[disp_i->nnn]);
		break;
	case D__Gw:		if (op->opersize==0)op->opersize = SIZE_w,op->rwflag = RWFLG_READ|RWFLG_WRITE;
	case D__rGw:	if (op->opersize==0)op->opersize = SIZE_w,op->rwflag = RWFLG_READ;					
	case D__wGw:	if (op->opersize==0)op->opersize = SIZE_w,op->rwflag = RWFLG_WRITE;;
			
		op->mode = mode_register;
		op->reg.reg_index = disp_i->nnn;
		strcpy(op->string,RegWord[disp_i->nnn]);
		break;

	case D__Gv:		if (op->opersize==0)op->opersize = SIZE_v,op->rwflag = RWFLG_READ|RWFLG_WRITE;
	case D__rGv:	if (op->opersize==0)op->opersize = SIZE_v,op->rwflag = RWFLG_READ;;
	case D__wGv:	if (op->opersize==0)op->opersize = SIZE_v,op->rwflag = RWFLG_WRITE;;
	case D__rwGv:	if (op->opersize==0)op->opersize = SIZE_v,op->rwflag = RWFLG_READ|RWFLG_WRITE;
					
		op->mode = mode_register;
		op->reg.reg_index = disp_i->nnn;
		if (op->opersize ==SIZE_w) 
			strcpy(op->string,RegWord[disp_i->nnn]);
		else if(op->opersize == SIZE_d)
			strcpy(op->string,RegDWord[disp_i->nnn]);
		else if(op->opersize == SIZE_q)
			strcpy(op->string,RegQWord[disp_i->nnn]);
		break;

	case D__Gd:		if (op->opersize==0)op->opersize = SIZE_d,op->rwflag = RWFLG_READ|RWFLG_WRITE;;
	case D__rGd:	if (op->opersize==0)op->opersize = SIZE_d,op->rwflag = RWFLG_READ;	
	case D__wGd:	if (op->opersize==0)op->opersize = SIZE_d,op->rwflag = RWFLG_WRITE;;
	case D__rwGd:	if (op->opersize==0)op->opersize = SIZE_d,op->rwflag = RWFLG_READ|RWFLG_WRITE;;

		op->mode = mode_register;
		op->reg.reg_index = disp_i->nnn;
		strcpy(op->string,RegDWord[disp_i->nnn]);
		break;
	case D__Gy:		if (op->opersize==0)op->opersize = SIZE_y,op->rwflag = RWFLG_READ|RWFLG_WRITE;;
	case D__rGy:	if (op->opersize==0)op->opersize = SIZE_y,op->rwflag = RWFLG_READ;	
	case D__wGy:	if (op->opersize==0)op->opersize = SIZE_y,op->rwflag = RWFLG_WRITE;;
	case D__rwGy:	if (op->opersize==0)op->opersize = SIZE_y,op->rwflag = RWFLG_READ|RWFLG_WRITE;;

		op->mode = mode_register;
		op->reg.reg_index = disp_i->nnn;
		if(op->opersize!=SIZE_d)
		{
			strcpy(op->string,RegQWord[disp_i->nnn]);
		}
		else
		{
			strcpy(op->string,RegDWord[disp_i->nnn]);
		}
		break;


	// The reg field of the ModR/M byte selects a packed quadword MMX?technology reg-ister.
	case D__Pd:		if (op->opersize==0) op->opersize = SIZE_d;
	case D__rPd:	if (op->opersize==0) op->opersize = SIZE_d,op->rwflag=RWFLG_READ;;
	case D__wPd:	if (op->opersize==0) op->opersize = SIZE_d,op->rwflag=RWFLG_WRITE;;
	case D__rwPd:	if (op->opersize==0) op->opersize = SIZE_d,op->rwflag=RWFLG_READ|RWFLG_WRITE;;

	case D__Pq:		if (op->opersize==0) op->opersize = SIZE_q;
	case D__rPq:	if (op->opersize==0) op->opersize = SIZE_q,op->rwflag=RWFLG_READ;;
	case D__wPq:	if (op->opersize==0) op->opersize = SIZE_q,op->rwflag=RWFLG_WRITE;;
	case D__rwPq:	if (op->opersize==0) op->opersize = SIZE_q,op->rwflag=RWFLG_READ|RWFLG_WRITE;;

	case D__Ppi:	if (op->opersize==0) op->opersize = SIZE_pi;
	case D__rPpi:	if (op->opersize==0) op->opersize = SIZE_pi,op->rwflag=RWFLG_READ;;
	case D__wPpi:	if (op->opersize==0) op->opersize = SIZE_pi,op->rwflag=RWFLG_WRITE;;
	case D__rwPpi:	if (op->opersize==0) op->opersize = SIZE_pi,op->rwflag=RWFLG_READ|RWFLG_WRITE;;

		op->mode = mode_register;
		op->reg.reg_index = disp_i->nnn;
		strcpy(op->string,RegMMXQWord[disp_i->nnn&7]);
		break;

	case D__Uq:		if(op->opersize==0) op->opersize = SIZE_q;
	case D__rUq:	if(op->opersize==0) op->opersize = SIZE_q,op->rwflag=RWFLG_READ;
	case D__wUq:	if(op->opersize==0) op->opersize = SIZE_q,op->rwflag=RWFLG_WRITE;
	case D__rwUq:	if(op->opersize==0) op->opersize = SIZE_q,op->rwflag=RWFLG_READ|RWFLG_WRITE;
		if(disp_i->mod!=3)
			return 0-1;
		op->mode = mode_register;
		op->opersize=SIZE_q;
		op->reg.reg_index = disp_i->rm;
		strcpy(op->string,RegXMMOWord[disp_i->rm]);
		break;
	case D__Nq:		if(op->opersize==0) op->opersize = SIZE_q;
	case D__rNq:	if(op->opersize==0) op->opersize = SIZE_q,op->rwflag=RWFLG_READ;
	case D__wNq:	if(op->opersize==0) op->opersize = SIZE_q,op->rwflag=RWFLG_WRITE;
	case D__rwNq:	if(op->opersize==0) op->opersize = SIZE_q,op->rwflag=RWFLG_READ|RWFLG_WRITE;
		if(disp_i->mod!=3)
		{
			return 0-1;
		}
		op->mode = mode_register;
		op->opersize=SIZE_q;
		op->reg.reg_index = disp_i->rm;
		strcpy(op->string,RegMMXQWord[disp_i->rm&7]);

		break;
					
	// The mod field of the ModR/M byte may refer only to a general register (for example,
	// MOV (0F20-0F24, 0F26)).
	case D__Rd:
		if (disp_i->mod!=3)
			return 0-1;
		op->mode = mode_register;
		op->opersize = SIZE_d;
		op->reg.reg_index = disp_i->rm;
		strcpy(op->string,RegDWord[disp_i->rm]);
		break;
	case D__Ry:
		if (disp_i->mod!=3)
			return 0-1;
		op->mode = mode_register;
		op->opersize = SIZE_y;
		op->reg.reg_index = disp_i->rm;
		if(op->opersize==SIZE_d)
			strcpy(op->string,RegDWord[disp_i->rm]);
		else
			strcpy(op->string,RegQWord[disp_i->rm]);
		break;
	// The reg field of the ModR/M byte selects a segment register (for example, MOV
	//(8C,8E)).
	case D__Sw:
		op->mode = mode_segment;
		op->opersize = SIZE_w;
		op->seg.seg_index = (disp_i->nnn&7);
		strcpy(op->string,SegReg[(disp_i->nnn&7)]);
		break;

	// The reg field of the ModR/M byte selects a test register (for example, MOV
	// (0F24,0F26)).

	case D__NTA:
		break;
	case D__T0:
	case D__T1:
	case D__T2:

		op->mode = mode_register;
		op->opersize = SIZE_d;
		op->reg.reg_index = opdata - D__T0;
		sprintf(op->string,"T%x",opdata-D__T0);
		break;

	// The reg field of the ModR/M byte selects a packed SIMD floating-point register.
	case D__Vq:		if (op->opersize==0) op->opersize = SIZE_q;
	case D__rVq:	if (op->opersize==0) op->opersize = SIZE_q,op->rwflag=RWFLG_READ;;
	case D__wVq:	if (op->opersize==0) op->opersize = SIZE_q,op->rwflag=RWFLG_WRITE;;
	case D__rwVq:	if (op->opersize==0) op->opersize = SIZE_q,op->rwflag=RWFLG_READ|RWFLG_WRITE;;

	case D__Vdq:	if (op->opersize==0) op->opersize = SIZE_dq;
	case D__rVdq:	if (op->opersize==0) op->opersize = SIZE_dq,op->rwflag=RWFLG_READ;;
	case D__wVdq:	if (op->opersize==0) op->opersize = SIZE_dq,op->rwflag=RWFLG_WRITE;;
	case D__rwVdq:	if (op->opersize==0) op->opersize = SIZE_dq,op->rwflag=RWFLG_READ|RWFLG_WRITE;;

	case D__Vps:	if (op->opersize==0) op->opersize = SIZE_ps;
	case D__rVps:	if (op->opersize==0) op->opersize = SIZE_ps,op->rwflag=RWFLG_READ;;
	case D__wVps:	if (op->opersize==0) op->opersize = SIZE_ps,op->rwflag=RWFLG_WRITE;;
	case D__rwVps:	if (op->opersize==0) op->opersize = SIZE_ps,op->rwflag=RWFLG_READ|RWFLG_WRITE;;

	case D__Vss:	if (op->opersize==0) op->opersize = SIZE_ss;
	case D__rVss:	if (op->opersize==0) op->opersize = SIZE_ss,op->rwflag=RWFLG_READ;;
	case D__wVss:	if (op->opersize==0) op->opersize = SIZE_ss,op->rwflag=RWFLG_WRITE;;
	case D__rwVss:	if (op->opersize==0) op->opersize = SIZE_ss,op->rwflag=RWFLG_READ|RWFLG_WRITE;;

	case D__Vsd:	if (op->opersize==0) op->opersize = SIZE_sd;
	case D__rVsd:	if (op->opersize==0) op->opersize = SIZE_sd,op->rwflag=RWFLG_READ;;
	case D__wVsd:	if (op->opersize==0) op->opersize = SIZE_sd,op->rwflag=RWFLG_WRITE;;
	case D__rwVsd:	if (op->opersize==0) op->opersize = SIZE_sd,op->rwflag=RWFLG_READ|RWFLG_WRITE;;

	case D__Vpd:	if (op->opersize==0) op->opersize = SIZE_pd;
	case D__rVpd:	if (op->opersize==0) op->opersize = SIZE_pd,op->rwflag=RWFLG_READ;;
	case D__wVpd:	if (op->opersize==0) op->opersize = SIZE_pd,op->rwflag=RWFLG_WRITE;;
	case D__rwVpd:	if (op->opersize==0) op->opersize = SIZE_pd,op->rwflag=RWFLG_READ|RWFLG_WRITE;;

		op->mode = mode_register;
		op->reg.reg_index = disp_i->nnn;
		strcpy(op->string,RegXMMOWord[disp_i->nnn]);
		break;
	case D__Vy:		if (op->opersize==0) op->opersize = SIZE_y;
	case D__rVy:	if (op->opersize==0) op->opersize = SIZE_y,op->rwflag=RWFLG_READ;;
	case D__wVy:	if (op->opersize==0) op->opersize = SIZE_y,op->rwflag=RWFLG_WRITE;;
	case D__rwVy:	if (op->opersize==0) op->opersize = SIZE_y,op->rwflag=RWFLG_READ|RWFLG_WRITE;;
		if(op->opersize!=SIZE_d)
			op->opersize = SIZE_q;
		op->mode = mode_register;
		op->reg.reg_index = disp_i->nnn;
		strcpy(op->string,RegXMMOWord[disp_i->nnn]);
		break;
	// Memory addressed by the DS:SI register pair (for example, MOVS, CMPS, OUTS, or
    // LODS).
	case D__Xb:if (op->opersize==0) op->opersize = SIZE_b;
	case D_rXb:if (op->opersize==0) op->opersize = SIZE_b;
	case D_wXb:if (op->opersize==0) op->opersize = SIZE_b;
	case D__Xw:if (op->opersize==0) op->opersize = SIZE_w;
	case D_rXw:if (op->opersize==0) op->opersize = SIZE_w;
	case D_wXw:if (op->opersize==0) op->opersize = SIZE_w;
	case D__Xv:if (op->opersize==0) op->opersize = SIZE_v;
	case D_rXv:if (op->opersize==0) op->opersize = SIZE_v;
	case D_wXv:if (op->opersize==0) op->opersize = SIZE_v;
	case D__Xd:if (op->opersize==0) op->opersize = SIZE_d;
	case D_rXd:if (op->opersize==0) op->opersize = SIZE_d;
	case D_wXd:if (op->opersize==0) op->opersize = SIZE_d;
	case D__Xz:if (op->opersize==0) op->opersize = SIZE_z;
	case D_rXz:if (op->opersize==0) op->opersize = SIZE_z;
	case D_wXz:if (op->opersize==0) op->opersize = SIZE_z;
		opimmedlength = 0;
		op->mode=mode_address;
		disp_i->seg=I_DS;
		disp_i->addr_displacement=0;
		disp_i->displacement_size=0;
		disp_i->index=-1;
		disp_i->base=6;
		disp_i->scale=0;
		disp_i->rm_addr=pDisCPU->gen_reg[disp_i->base].erx;
		DispTranDis(&op->addr,disp_i,eip);
		break;

	// Memory addressed by the ES:DI register pair (for example, MOVS, CMPS, INS,
	//STOS, or SCAS).
	case D__Yb:if (op->opersize==0) op->opersize = SIZE_b;
	case D__rYb:if (op->opersize==0) op->opersize = SIZE_b;
	case D__wYb:if (op->opersize==0) op->opersize = SIZE_b;
	case D__Yw:if (op->opersize==0) op->opersize = SIZE_w;
	case D__rYw:if (op->opersize==0) op->opersize = SIZE_w;
	case D__wYw:if (op->opersize==0) op->opersize = SIZE_w;
	case D__Yv:if (op->opersize==0) op->opersize = SIZE_v;
	case D__rYv:if (op->opersize==0) op->opersize = SIZE_v;
	case D__wYv:if (op->opersize==0) op->opersize = SIZE_v;
	case D__Yd:if (op->opersize==0) op->opersize = SIZE_d;
	case D__rYd:if (op->opersize==0) op->opersize = SIZE_d;
	case D__wYd:if (op->opersize==0) op->opersize = SIZE_d;
	case D__Yz:if (op->opersize==0) op->opersize = SIZE_z;
	case D__rYz:if (op->opersize==0) op->opersize = SIZE_z;
	case D__wYz:if (op->opersize==0) op->opersize = SIZE_z;
		opimmedlength = 0;
		op->mode=mode_address;
		disp_i->seg=I_ES;
		disp_i->addr_displacement=0;
		disp_i->displacement_size=0;
		disp_i->index=-1;
		disp_i->base=7;
		disp_i->scale=0;
		disp_i->rm_addr=pDisCPU->gen_reg[disp_i->base].erx;
		DispTranDis(&op->addr,disp_i,eip);
		break;
	
	// When an operand is a specific register encoded in the opcode, the register is identified by its
	// name (for example, AX, CL, or ESI). The name of the register indicates whether the register is
	// 32, 16, or 8 bits wide. A register identifier of the form eXX is used when the width of the register
	// depends on the operand-size attribute. For example, eAX indicates that the AX register is used
	// when the operand-size attribute is 16, and the EAX register is used when the operand-size at-tribute
	// is 32.	
	
	case D__AL:
	case D__CL:
	case D__DL:
	case D__BL:
	case D__AH:
	case D__CH:
	case D__DH:
	case D__BH:
		op->mode = mode_register;
		op->opersize = SIZE_b;
		op->reg.reg_index = opdata - D__AL;
		strcpy(op->string,RegByte[opdata-D__AL]);
		break;
	case D__AL_r8L:
	case D__CL_r9L:
	case D__DL_r10L:
	case D__BL_r11L:
	case D__AH_r12L:
	case D__CH_r13L:
	case D__DH_r14L:
	case D__BH_r15L:
		op->mode = mode_register;
		op->opersize = SIZE_b;
		op->reg.reg_index = (opdata - D__AL_r8L)|((disp_i->rex_prefix & 1) << 3) ;
		if(disp_i->mode==BIT64)
			strcpy(op->string,RegByteFor64bit[op->reg.reg_index]);
		else
			strcpy(op->string,RegByte[op->reg.reg_index]);
		break;
	case D__AX:
	case D__CX:
	case D__DX:
	case D__BX:
	case D__SP:
	case D__BP:
	case D__SI:
	case D__DI:
		op->mode = mode_register;
		op->opersize = SIZE_w;
		op->reg.reg_index = opdata - D__AX;
		strcpy(op->string,RegWord[op->reg.reg_index]);
		break;

	case D__eAX:
	case D__eCX:
	case D__eDX:
	case D__eBX:
	case D__eSP:
	case D__eBP:
	case D__eSI:
	case D__eDI:
		op->mode = mode_register;
		op->opersize = SIZE_v;
		op->reg.reg_index = opdata - D__eAX;

		if (op->opersize==SIZE_w) 
			strcpy(op->string,RegWord[opdata-D__eAX]);
		else 
			strcpy(op->string,RegDWord[opdata-D__eAX]);

		break;
	case D__rAX_r8:
	case D__rCX_r9:
	case D__rDX_r10:
	case D__rBX_r11:
	case D__rSP_r12:
	case D__rBP_r13:
	case D__rSI_r14:
	case D__rDI_r15:
		op->mode = mode_register;
		op->opersize = SIZE_v;
		op->reg.reg_index = opdata - D__rAX_r8 | ((disp_i->rex_prefix & 1) << 3);
		if (op->opersize==SIZE_w) 
			strcpy(op->string,RegWord[op->reg.reg_index]);
		else if (op->opersize==SIZE_d) 
			strcpy(op->string,RegDWord[op->reg.reg_index]);
		else if (op->opersize == SIZE_q)
			strcpy(op->string,RegQWord[op->reg.reg_index]);
		break;
	case D__rAX:
	case D__rCX:
	case D__rDX:
	case D__rBX:
	case D__rSP:
	case D__rBP:
	case D__rSI:
	case D__rDI:
		op->mode = mode_register;
		op->opersize = SIZE_v;
		op->reg.reg_index = opdata - D__rAX;

		if (op->opersize==SIZE_w) 
			strcpy(op->string,RegWord[opdata-D__rAX]);
		else if(op->opersize == SIZE_d) 
			strcpy(op->string,RegDWord[opdata-D__rAX]);
		else if(op->opersize == SIZE_q)
			strcpy(op->string,RegQWord[opdata-D__rAX]);
		break;
	case D__EAX:
	case D__ECX:
	case D__EDX:
	case D__EBX:
	case D__ESP:
	case D__EBP:
	case D__ESI:
	case D__EDI:
		op->mode = mode_register;
		op->opersize = SIZE_d;
		op->reg.reg_index = opdata - D__EAX;
		strcpy(op->string,RegDWord[opdata-D__EAX]);
					break;
	case D__RAX_EAX_R8_R8D:	
	case D__RCX_ECX_R9_R9D:		
	case D__RDX_EDX_R10_R10D:	
	case D__RBX_EBX_R11_R11D:	
	case D__RSP_ESP_R12_R12D:
	case D__RBP_EBP_R13_R13D:
	case D__RSI_ESI_R14_R14D:
	case D__RDI_EDI_R15_R15D:
		op->mode = mode_register;
		op->reg.reg_index = (opdata - D__RAX_EAX_R8_R8D) | ((disp_i->rex_prefix & 1) << 3)  ;
		if(disp_i->os_32==BIT64)
		{
			op->opersize=SIZE_q;
			strcpy(op->string,RegQWord[op->reg.reg_index]);
		}
		else
		{
			op->opersize=SIZE_d;
			strcpy(op->string,RegDWord[op->reg.reg_index]);
		}
		break;
	case D__ES:
	case D__CS:
	case D__SS:
	case D__DS:
	case D__FS:
	case D__GS:
		op->mode = mode_segment;
		op->opersize = SIZE_w;
		op->reg.reg_index = opdata - D__ES;
		strcpy(op->string,SegReg[opdata-D__ES]);
		break;

	case D__st:
		op->mode = mode_register;
		op->opersize = SIZE_t;
		op->reg.reg_index = 0;
		strcpy(op->string,"ST");
		break;
	case D__st0:
	case D__st1:
	case D__st2:
	case D__st3:
	case D__st4:
	case D__st5:
	case D__st6:
	case D__st7:
		op->mode = mode_register;
		op->opersize = SIZE_t;
		op->reg.reg_index = opdata - D__st0;
		sprintf(op->string,"ST(%x)",opdata-D__st0);
		break;


	// A ModR/M byte follows the opcode and specifies the operand. The operand is either a
	// general-purpose register or a memory address. If it is a memory address, the address is
	// computed from a segment register and any of the following values: a base register, an
	// index register, a scaling factor, a displacement.
		
	case D__Eb:		if (op->opersize==0)op->opersize = SIZE_b,op->rwflag = RWFLG_READ|RWFLG_WRITE;			
	case D__rEb:	if (op->opersize==0)op->opersize = SIZE_b,op->rwflag = RWFLG_READ;			
	case D__wEb:	if (op->opersize==0)op->opersize = SIZE_b,op->rwflag = RWFLG_WRITE;			
	case D__rwEb:	if (op->opersize==0)op->opersize = SIZE_b,op->rwflag = RWFLG_WRITE;			

	case D__Ew:		if (op->opersize==0)op->opersize = SIZE_w,op->rwflag = RWFLG_READ|RWFLG_WRITE;			
	case D__rEw:	if (op->opersize==0)op->opersize = SIZE_w,op->rwflag = RWFLG_READ;				
	case D__wEw:	if (op->opersize==0)op->opersize = SIZE_w,op->rwflag = RWFLG_WRITE;			
	case D__rwEw:	if (op->opersize==0)op->opersize = SIZE_w,op->rwflag = RWFLG_WRITE|RWFLG_WRITE;		

	case D__Ev:		if (op->opersize==0)op->opersize = SIZE_v,op->rwflag = RWFLG_READ|RWFLG_WRITE;		
	case D__rEv:	if (op->opersize==0)op->opersize = SIZE_v,op->rwflag = RWFLG_READ;				
	case D__wEv:	if (op->opersize==0)op->opersize = SIZE_v,op->rwflag = RWFLG_WRITE;				
	case D__rwEv:	if (op->opersize==0)op->opersize = SIZE_v,op->rwflag = RWFLG_WRITE|RWFLG_WRITE;			

	case D__Ed:		if (op->opersize==0)op->opersize = SIZE_d,op->rwflag = RWFLG_READ|RWFLG_WRITE;				
	case D__rEd:	if (op->opersize==0)op->opersize = SIZE_d,op->rwflag = RWFLG_READ;
	case D__wEd:	if (op->opersize==0)op->opersize = SIZE_d,op->rwflag = RWFLG_WRITE;
	case D__rwEd:	if (op->opersize==0)op->opersize = SIZE_d,op->rwflag = RWFLG_READ|RWFLG_WRITE;

	case D__Ep:		if (op->opersize==0)op->opersize = SIZE_p,op->rwflag = RWFLG_READ|RWFLG_WRITE;
	case D__rEp:	if (op->opersize==0)op->opersize = SIZE_p,op->rwflag = RWFLG_READ;
	case D__wEp:	if (op->opersize==0)op->opersize = SIZE_p,op->rwflag = RWFLG_WRITE;
	case D__rwEp:	if (op->opersize==0)op->opersize = SIZE_p,op->rwflag = RWFLG_READ|RWFLG_WRITE;

		if (disp_i->mod==3)
		{
			if (opdata==D__Ep||opdata==D__rEp)
			{
				return 0-1;
			}
			else
			{
				op->mode = mode_register;
			}
			k = disp_i->rm;
			op->reg.reg_index = (int)k; 
			if (op->opersize==SIZE_b) 
			{
				if(disp_i->mode==BIT64&&disp_i->rex_prefix)
					strcpy(op->string,RegByteFor64bit[k]);
				else
					strcpy(op->string,RegByte[k]);
			}
			else if (op->opersize==SIZE_w) 
				strcpy(op->string,RegWord[k]);
			else if (op->opersize==SIZE_d) 
				strcpy(op->string,RegDWord[k]);
			else if (op->opersize==SIZE_q) 
				strcpy(op->string,RegQWord[k]);
		}
		else 
		{
			op->mode = mode_address;
			DispTranDis(&op->addr,disp_i,eip);
		}
		break;

	case D__Ey:		if (op->opersize==0)op->opersize = SIZE_y,op->rwflag = RWFLG_READ|RWFLG_WRITE;
	case D__rEy:	if (op->opersize==0)op->opersize = SIZE_y,op->rwflag = RWFLG_READ;
	case D__wEy:	if (op->opersize==0)op->opersize = SIZE_y,op->rwflag = RWFLG_WRITE;
	case D__rwEy:	if (op->opersize==0)op->opersize = SIZE_y,op->rwflag = RWFLG_READ|RWFLG_WRITE;
		if (disp_i->mod==3)
		{
			op->mode = mode_register;
			k = disp_i->rm;
			op->reg.reg_index = (int)k; 
			//if(disp_i->mode==BIT64)
			//	op->opersize=SIZE_q;
			if (op->opersize==SIZE_d) 
				strcpy(op->string,RegDWord[k]);
			else 
				//if (op->opersize==SIZE_q) 
				strcpy(op->string,RegQWord[k]);
		}
		else 
		{
			op->mode = mode_address;
			DispTranDis(&op->addr,disp_i,eip);
		}
		break;

	// The ModR/M byte may refer only to memory (for example, BOUND, LES, LDS, LSS,
	// LFS, LGS, CMPXCHG8B).
	case D__M:		if (op->opersize==0)op->opersize = 0-1,op->rwflag = RWFLG_READ|RWFLG_WRITE;
	case D__rM:		if (op->opersize==0)op->opersize = 0-1,op->rwflag = RWFLG_READ;
	case D__wM:		if (op->opersize==0)op->opersize = 0-1,op->rwflag = RWFLG_WRITE;
	case D__rwM:	if (op->opersize==0)op->opersize = 0-1,op->rwflag = RWFLG_READ|RWFLG_WRITE;

	case D__Ma:		if (op->opersize==0)op->opersize = SIZE_a,op->rwflag = RWFLG_READ|RWFLG_WRITE; //read|write
	case D__rMa:	if (op->opersize==0)op->opersize = SIZE_a,op->rwflag = RWFLG_READ;
	case D__wMa:	if (op->opersize==0)op->opersize = SIZE_a,op->rwflag = RWFLG_WRITE;
	case D__rwMa:	if (op->opersize==0)op->opersize = SIZE_a,op->rwflag = RWFLG_READ|RWFLG_WRITE;
	
	case D__Mb:		if (op->opersize==0)op->opersize = SIZE_b,op->rwflag = RWFLG_READ|RWFLG_WRITE;
	case D__rMb:	if (op->opersize==0)op->opersize = SIZE_b,op->rwflag = RWFLG_READ;
	case D__wMb:	if (op->opersize==0)op->opersize = SIZE_b,op->rwflag = RWFLG_WRITE;
	case D__rwMb:	if (op->opersize==0)op->opersize = SIZE_b,op->rwflag = RWFLG_READ|RWFLG_WRITE;

	case D__Mp:		if (op->opersize==0)op->opersize = SIZE_p,op->rwflag = RWFLG_READ|RWFLG_WRITE;
	case D__rMp:	if (op->opersize==0)op->opersize = SIZE_p,op->rwflag = RWFLG_READ;
	case D__wMp:	if (op->opersize==0)op->opersize = SIZE_p,op->rwflag = RWFLG_WRITE;
	case D__rwMp:	if (op->opersize==0)op->opersize = SIZE_p,op->rwflag = RWFLG_READ|RWFLG_WRITE;

	case D__Ms:		if (op->opersize==0)op->opersize = SIZE_s,op->rwflag = RWFLG_READ|RWFLG_WRITE;
	case D__rMs:	if (op->opersize==0)op->opersize = SIZE_s,op->rwflag = RWFLG_READ;	
	case D__wMs:	if (op->opersize==0)op->opersize = SIZE_s,op->rwflag = RWFLG_WRITE;
	case D__rwMs:	if (op->opersize==0)op->opersize = SIZE_s,op->rwflag = RWFLG_WRITE;

	case D__Mq:		if (op->opersize==0)op->opersize = SIZE_q,op->rwflag = RWFLG_READ|RWFLG_WRITE;
	case D__rMq:	if (op->opersize==0)op->opersize = SIZE_q,op->rwflag = RWFLG_READ;
	case D__wMq:	if (op->opersize==0)op->opersize = SIZE_q,op->rwflag = RWFLG_WRITE;
	case D__rwMq:	if (op->opersize==0)op->opersize = SIZE_q,op->rwflag = RWFLG_READ|RWFLG_WRITE;

	case D__Mw:		if (op->opersize==0)op->opersize = SIZE_w,op->rwflag = RWFLG_READ|RWFLG_WRITE;		
	case D__rMw:	if (op->opersize==0)op->opersize = SIZE_w,op->rwflag = RWFLG_READ;		
	case D__wMw:	if (op->opersize==0)op->opersize = SIZE_w,op->rwflag = RWFLG_WRITE;		
	case D__rwMw:	if (op->opersize==0)op->opersize = SIZE_w,op->rwflag = RWFLG_READ|RWFLG_WRITE;		

	case D__Md:		if (op->opersize==0)op->opersize = SIZE_d,op->rwflag = RWFLG_READ|RWFLG_WRITE;
	case D__rMd:	if (op->opersize==0)op->opersize = SIZE_d,op->rwflag = RWFLG_READ;
	case D__wMd:	if (op->opersize==0)op->opersize = SIZE_d,op->rwflag = RWFLG_WRITE;
	case D__rwMd:	if (op->opersize==0)op->opersize = SIZE_d,op->rwflag = RWFLG_READ|RWFLG_WRITE;

	case D__My:		if (op->opersize==0)op->opersize = SIZE_y,op->rwflag = RWFLG_READ|RWFLG_WRITE;
	case D__rMy:	if (op->opersize==0)op->opersize = SIZE_y,op->rwflag = RWFLG_READ;
	case D__wMy:	if (op->opersize==0)op->opersize = SIZE_y,op->rwflag = RWFLG_WRITE;
	case D__rwMy:	if (op->opersize==0)op->opersize = SIZE_y,op->rwflag = RWFLG_READ|RWFLG_WRITE;

	case D__Mv:		if (op->opersize==0)op->opersize = SIZE_v,op->rwflag = RWFLG_READ|RWFLG_WRITE;
	case D__rMv:	if (op->opersize==0)op->opersize = SIZE_v,op->rwflag = RWFLG_READ;
	case D__wMv:	if (op->opersize==0)op->opersize = SIZE_v,op->rwflag = RWFLG_WRITE;
	case D__rwMv:	if (op->opersize==0)op->opersize = SIZE_v,op->rwflag = RWFLG_READ|RWFLG_WRITE;

	case D__Mdq:	if (op->opersize==0) op->opersize = SIZE_dq;
	case D__rMdq:	if (op->opersize==0) op->opersize = SIZE_dq,op->rwflag=RWFLG_READ;
	case D__wMdq:	if (op->opersize==0) op->opersize = SIZE_dq,op->rwflag=RWFLG_WRITE;
	case D__rwMdq:	if (op->opersize==0) op->opersize = SIZE_dq,op->rwflag=RWFLG_READ|RWFLG_WRITE;

	case D__Mpd:	if (op->opersize==0) op->opersize = SIZE_pd,op->rwflag=RWFLG_READ|RWFLG_WRITE;
	case D__rMpd:	if (op->opersize==0) op->opersize = SIZE_pd,op->rwflag=RWFLG_READ;
	case D__wMpd:	if (op->opersize==0) op->opersize = SIZE_pd,op->rwflag=RWFLG_WRITE;
	case D__rwMpd:	if (op->opersize==0) op->opersize = SIZE_pd,op->rwflag=RWFLG_READ|RWFLG_WRITE;

	case D__Mps:	if (op->opersize==0) op->opersize = SIZE_ps,op->rwflag=RWFLG_READ|RWFLG_WRITE;
	case D__rMps:	if (op->opersize==0) op->opersize = SIZE_ps,op->rwflag=RWFLG_READ;
	case D__wMps:	if (op->opersize==0) op->opersize = SIZE_ps,op->rwflag=RWFLG_WRITE;
	case D__rwMps:	if (op->opersize==0) op->opersize = SIZE_ps,op->rwflag=RWFLG_READ|RWFLG_WRITE;

		if (disp_i->mod==3)
		{
			return 0-1;
		}
		op->mode = mode_address;
		DispTranDis(&op->addr,disp_i,eip);					
		break;
	case D__MqMdq:	if (op->opersize==0)op->opersize = (disp_i->rex_prefix &0x8)?SIZE_dq:SIZE_q,op->rwflag = RWFLG_READ|RWFLG_WRITE;
	case D__rMqMdq:	if (op->opersize==0)op->opersize = (disp_i->rex_prefix &0x8)?SIZE_dq:SIZE_q,op->rwflag = RWFLG_READ;
	case D__wMqMdq:	if (op->opersize==0)op->opersize = (disp_i->rex_prefix &0x8)?SIZE_dq:SIZE_q,op->rwflag = RWFLG_WRITE;
	case D__rwMqMdq:	if (op->opersize==0)op->opersize = (disp_i->rex_prefix &0x8)?SIZE_dq:SIZE_q,op->rwflag = RWFLG_READ|RWFLG_WRITE;
		if (disp_i->mod==3)
		{
			return 0-1;
		}
		op->mode = mode_address;
		DispTranDis(&op->addr,disp_i,eip);
		break;
	//case D__MwRv:	if (op->opersize==0)op->opersize = (disp_i->mod==3)?SIZE_v:SIZE_w,op->rwflag = RWFLG_READ|RWFLG_WRITE;		
	//case D__rMwRv:	if (op->opersize==0)op->opersize = (disp_i->mod==3)?SIZE_v:SIZE_w,op->rwflag = RWFLG_READ;		
	case D__wMwRv:	if (op->opersize==0)op->opersize = (disp_i->mod==3)?SIZE_v:SIZE_w,op->rwflag = RWFLG_WRITE;		
	//case D__rwMwRv:	if (op->opersize==0)op->opersize = (disp_i->mod==3)?SIZE_v:SIZE_w,op->rwflag = RWFLG_READ|RWFLG_WRITE;	
		if (disp_i->mod==3)
		{
			op->mode = mode_register;
			k = disp_i->rm;
			op->reg.reg_index = (int)k; 
			if (op->opersize==SIZE_w) 
				strcpy(op->string,RegWord[k]);
			else if (op->opersize==SIZE_d) 
				strcpy(op->string,RegDWord[k]);
			else if (op->opersize==SIZE_q) 
				strcpy(op->string,RegQWord[k]);
		}
		else 
		{
			op->mode = mode_address;
			DispTranDis(&op->addr,disp_i,eip);
		}
		break;

	// A ModR/M byte follows the opcode and specifies the operand. The operand is either
	// an MMX?technology register or a memory address. If it is a memory address, the ad-dress
	// is computed from a segment register and any of the following values: a base reg-ister,
	// an index register, a scaling factor, and a displacement.
	case D__Qd:		if (op->opersize==0) op->opersize = SIZE_d;
	case D__rQd:	if (op->opersize==0) op->opersize = SIZE_d,op->rwflag=RWFLG_READ;;
	case D__wQd:	if (op->opersize==0) op->opersize = SIZE_d,op->rwflag=RWFLG_WRITE;;
	case D__rwQd:	if (op->opersize==0) op->opersize = SIZE_d,op->rwflag=RWFLG_READ|RWFLG_WRITE;;

	case D__Qq:		if (op->opersize==0) op->opersize = SIZE_q;
	case D__rQq:	if (op->opersize==0) op->opersize = SIZE_q,op->rwflag=RWFLG_READ;;
	case D__wQq:	if (op->opersize==0) op->opersize = SIZE_q,op->rwflag=RWFLG_WRITE;;
	case D__rwQq:	if (op->opersize==0) op->opersize = SIZE_q,op->rwflag=RWFLG_READ|RWFLG_WRITE;;

	case D__Qpi:	if (op->opersize==0) op->opersize = SIZE_pi;
	case D__rQpi:	if (op->opersize==0) op->opersize = SIZE_pi,op->rwflag=RWFLG_READ;;
	case D__wQpi:	if (op->opersize==0) op->opersize = SIZE_pi,op->rwflag=RWFLG_WRITE;;
	case D__rwQpi:	if (op->opersize==0) op->opersize = SIZE_pi,op->rwflag=RWFLG_READ|RWFLG_WRITE;;

		if (disp_i->mod==3)
		{
			op->mode = mode_register;
			op->reg.reg_index = disp_i->rm;
			strcpy(op->string,RegMMXQWord[(disp_i->rm)&0x7]);
		}
		else
		{
			op->mode = mode_address;
			DispTranDis(&op->addr,disp_i,eip);
		}
					
		break;
	case D__Ups:	if (op->opersize==0) op->opersize = SIZE_ps;
	case D__rUps:	if (op->opersize==0) op->opersize = SIZE_ps,op->rwflag=RWFLG_READ;;
	case D__wUps:	if (op->opersize==0) op->opersize = SIZE_ps,op->rwflag=RWFLG_WRITE;;
	case D__rwUps:	if (op->opersize==0) op->opersize = SIZE_ps,op->rwflag=RWFLG_READ|RWFLG_WRITE;;

	case D__Upd:	if (op->opersize==0) op->opersize = SIZE_pd;
	case D__rUpd:	if (op->opersize==0) op->opersize = SIZE_pd,op->rwflag=RWFLG_READ;;
	case D__wUpd:	if (op->opersize==0) op->opersize = SIZE_pd,op->rwflag=RWFLG_WRITE;;
	case D__rwUpd:	if (op->opersize==0) op->opersize = SIZE_pd,op->rwflag=RWFLG_READ|RWFLG_WRITE;;

	case D__Udq:	if (op->opersize==0) op->opersize = SIZE_dq;
	case D__rUdq:	if (op->opersize==0) op->opersize = SIZE_dq,op->rwflag=RWFLG_READ;;
	case D__wUdq:	if (op->opersize==0) op->opersize = SIZE_dq,op->rwflag=RWFLG_WRITE;;
	case D__rwUdq:	if (op->opersize==0) op->opersize = SIZE_dq,op->rwflag=RWFLG_READ|RWFLG_WRITE;;
		if (disp_i->mod!=3)
			return 0-1;
		op->mode = mode_register;
		op->reg.reg_index = disp_i->rm;
		sprintf(op->string,RegXMMOWord[disp_i->rm]);
		
		break;
	// An ModR/M byte follows the opcode and specifies the operand. The operand is either
	// a SIMD floating-point register or a memory address. If it is a memory address, the ad-dress
	// is computed from a segment register and any of the following values: a base reg-ister,
	// an index register, a scaling factor, and a displacement

	case D__Wq:		if (op->opersize==0) op->opersize = SIZE_q;
	case D__rWq:	if (op->opersize==0) op->opersize = SIZE_q,op->rwflag=RWFLG_READ;
	case D__wWq:	if (op->opersize==0) op->opersize = SIZE_q,op->rwflag=RWFLG_WRITE;
	case D__rwWq:	if (op->opersize==0) op->opersize = SIZE_q,op->rwflag=RWFLG_READ|RWFLG_WRITE;

	case D__Wdq:	if (op->opersize==0) op->opersize = SIZE_dq;
	case D__rWdq:	if (op->opersize==0) op->opersize = SIZE_dq,op->rwflag=RWFLG_READ;;
	case D__wWdq:	if (op->opersize==0) op->opersize = SIZE_dq,op->rwflag=RWFLG_WRITE;;
	case D__rwWdq:	if (op->opersize==0) op->opersize = SIZE_dq,op->rwflag=RWFLG_READ|RWFLG_WRITE;;

	case D__Wps:	if (op->opersize==0) op->opersize = SIZE_ps;
	case D__rWps:	if (op->opersize==0) op->opersize = SIZE_ps,op->rwflag=RWFLG_READ;;
	case D__wWps:	if (op->opersize==0) op->opersize = SIZE_ps,op->rwflag=RWFLG_WRITE;;
	case D__rwWps:	if (op->opersize==0) op->opersize = SIZE_ps,op->rwflag=RWFLG_READ|RWFLG_WRITE;;

	case D__Wss:	if (op->opersize==0) op->opersize = SIZE_ss;
	case D__rWss:	if (op->opersize==0) op->opersize = SIZE_ss,op->rwflag=RWFLG_READ;;
	case D__wWss:	if (op->opersize==0) op->opersize = SIZE_ss,op->rwflag=RWFLG_WRITE;;
	case D__rwWss:	if (op->opersize==0) op->opersize = SIZE_ss,op->rwflag=RWFLG_READ|RWFLG_WRITE;;

	case D__Wpd:	if (op->opersize==0) op->opersize = SIZE_pd;
	case D__rWpd:	if (op->opersize==0) op->opersize = SIZE_pd,op->rwflag=RWFLG_READ;;
	case D__wWpd:	if (op->opersize==0) op->opersize = SIZE_pd,op->rwflag=RWFLG_WRITE;;
	case D__rwWpd:	if (op->opersize==0) op->opersize = SIZE_pd,op->rwflag=RWFLG_READ|RWFLG_WRITE;;

	case D__Wsd:	if (op->opersize==0) op->opersize = SIZE_sd;
	case D__rWsd:	if (op->opersize==0) op->opersize = SIZE_sd,op->rwflag=RWFLG_READ;;
	case D__wWsd:	if (op->opersize==0) op->opersize = SIZE_sd,op->rwflag=RWFLG_WRITE;;
	case D__rwWsd:	if (op->opersize==0) op->opersize = SIZE_sd,op->rwflag=RWFLG_READ|RWFLG_WRITE;;
	
		if (disp_i->mod==3)
		{
			op->mode = mode_register;
			op->reg.reg_index = disp_i->rm;
			strcpy(op->string,RegXMMOWord[disp_i->rm]);
		}
		else
		{
			op->mode = mode_address;
			DispTranDis(&op->addr,disp_i,eip);
		}

		break;

	case D__word_int:
		if (op->opersize==0) op->opersize = SIZE_w;
	case D__dword_int:
		if (op->opersize==0) op->opersize = SIZE_d;
	case D__qword_int:
		if (op->opersize==0) op->opersize = SIZE_q;

	case D__single_real:
		if (op->opersize==0) op->opersize = SIZE_d;
	case D__double_real:
		if (op->opersize==0) op->opersize = SIZE_q;
	case D__extend_real:
		if (op->opersize==0) op->opersize = SIZE_t;
	case D__packed_BCD:
		if (op->opersize==0) op->opersize = SIZE_t;

	case D__2b:
		if (op->opersize==0) op->opersize = SIZE_w;
	case D__14_28b:
		if (op->opersize==0) op->opersize = SIZE_t;
	case D__98_108b:
		if (op->opersize==0) op->opersize = SIZE_t;

		if (disp_i->mod==3)
		{
			return 0-1;
		}
		else
		{
			op->mode = mode_address;
			DispTranDis(&op->addr,disp_i,eip);
		}

		break;

	default:
		opimmedlength = 0;
		op->mode = mode_invalid;
		op->opersize = 0;

	}

	return opimmedlength;
}

int ProcessOpdata_immde(int opdata,BYTE *inbuff,DISP_INSTRUCTION_T *disp_i)
{
	int opimmedlength;

	int SIZE_c,SIZE_v,SIZE_p,SIZE_z;
	switch(disp_i->os_32)
	{
	case BIT32:
		SIZE_v = 4;
		SIZE_c = 2;
		SIZE_p = 6;
		SIZE_z = 4;
		break;
	case BIT16:
		SIZE_v = 2;
		SIZE_c = 1;
		SIZE_p = 4;
		SIZE_z = 2;
		break;
	case BIT64:
		SIZE_v = 8;
		SIZE_c = 2;
		SIZE_p = 10;
		SIZE_z = 4;
		break;
	}

	opimmedlength = 0;
	
	switch(opdata)
	{
	case D__1:
		disp_i->Ib = 1;
		break;

	// Immediate data. The operand value is encoded in subsequent bytes of the instruction.
	// The instruction contains a relative offset to be added to the instruction pointer register
	// (for example, JMP (0E9), LOOP).
	case D__Jb:
	case D__Ib:
	case D__sIb:
		opimmedlength = SIZE_b;
		disp_i->Ib = GetValue_b(inbuff);
		break;
	case D__Ib2:
		opimmedlength = SIZE_b;
		disp_i->Ib2 = GetValue_b(inbuff);

		break;
	case D__Iw:
		opimmedlength = SIZE_w;
		disp_i->Iw = GetValue_w(inbuff);
		break;
	case D__Iv:
	
		opimmedlength = SIZE_v;

		switch(SIZE_v)
		{
		case SIZE_w:
			disp_i->Iw = GetValue_w(inbuff);
			break;
		case SIZE_d:
			disp_i->Id = GetValue_d(inbuff);
			break;
		case SIZE_q:
			disp_i->Iq = GetValue_q(inbuff);
			break;
		}
		break;

	case D__Jz:
	case D__Iz:
		opimmedlength = SIZE_z;

		if (SIZE_z==SIZE_w)
		{
			disp_i->Iw = GetValue_w(inbuff);
		}
		else
		{
			disp_i->Id = GetValue_d(inbuff);
		}

		break;

	// The instruction has no ModR/M byte; the offset of the operand is coded as a word or
	// double word (depending on address size attribute) in the instruction. No base register,
	// index register, or scaling factor can be applied (for example, MOV (A0-A3)).
	case D__Ob:
	case D__rOb:
	case D__wOb:
	case D__rwOb:

	case D__Ov:		
	case D__rOv:		
	case D__wOv:		
	case D__rwOv:		
		if (disp_i->as_32==BIT64)
		{
			opimmedlength = 8;
			disp_i->Iq = GetValue_q(inbuff);
		} 
		else if (disp_i->as_32==BIT32)
		{
			opimmedlength = 4;
			disp_i->Id = GetValue_d(inbuff);
		}
		else
		{
			opimmedlength = 2;
			disp_i->Iw = GetValue_w(inbuff);
		}
		break;

	case D__Ap:
		opimmedlength = SIZE_v+2;

		if (SIZE_v==SIZE_w)
		{
			disp_i->Iw = GetValue_w(inbuff);
			disp_i->Iw2 = GetValue_w(inbuff+2);
		}
		else
		{
			disp_i->Id = GetValue_d(inbuff);
			disp_i->Iw2 = GetValue_w(inbuff+4);
		}
		
		break;
	}

	return opimmedlength;
}

int PutStr(char *buff,char *s)
{
	int i;
	for (i=0;s[i]!='\0';i++) 
		buff[i] = s[i];
	return i;
}
int PrintPasm(INSTRUCTION_INFORMATION *pInstInfo,char *pasm,int u_x1,int u_x2)
{
	int i,length;
	char buff[0x20];

	char **preg;

	for (i=0;i<=0x50;i++)
		pasm[i]=' ';

	pasm[i]='\0';

	length = u_x1;

	if (pInstInfo->Lock!=-1)
	{
		i = PutStr(pasm+length,pInstInfo->LockName);
		if (i) length += i+1;
	}

	if (pInstInfo->Repeat!=-1)
	{
		i = PutStr(pasm+length,pInstInfo->RepeatName);
		if (i) length += i+1;
	}

	length += PutStr(pasm+length,pInstInfo->Name);

	OPERAND_ITEM *op = 	pInstInfo->op;
	bool brsp=false;
	for(int ii=0;ii<3;ii++)
	{
		if(op[ii].mode==mode_register && (op[ii].opersize==4 || op[ii].opersize==8))
		{
			if(op[ii].reg.reg_index==4)
			{
				brsp=true;
				break;
			}
		}
	}
	for (i=0;i<3&&op->mode!=mode_invalid;i++,op++)
	{
		if (i==0)
		{
			if (length<u_x2)
				length = u_x2;
			else length++;
		}

		if (i>0)
			length +=PutStr(pasm+length,",");

		if (op->mode==mode_address)
		{
			if (pInstInfo->xxxxptr!=-1&&pInstInfo->xxxxptr!=0)
			{
				length += PutStr(pasm+length,xxxxptr[pInstInfo->xxxxptr]);
				length += PutStr(pasm+length," PTR ");
			}

			if (pInstInfo->SegmentPrefix!=-1)
			{
				length += PutStr(pasm+length,SegReg[pInstInfo->SegmentPrefix]);
				length += PutStr(pasm+length,":");
			}

			if (op->addr.address_size==BIT32) 
				preg = RegDWord;
			else if(op->addr.address_size==BIT64)
				preg = RegQWord;
			else 
				preg = RegWord;
			

			//if(!(op->addr.base==-1 && op->addr.index==-1 && brsp))
				length += PutStr(pasm+length,"[");
			if (op->addr.base!=-1)
				length += PutStr(pasm+length,preg[op->addr.base]);

			if (op->addr.index!=-1)
			{
				if (op->addr.base!=-1) length += PutStr(pasm+length,"+");
				length += PutStr(pasm+length,preg[op->addr.index]);
				if (op->addr.scale>0)
				{
					sprintf(buff,"*%1x",1<<op->addr.scale);
					length += PutStr(pasm+length,buff);
				}
			}

			if (op->addr.displacement_size>=1&&(op->addr.base!=-1||op->addr.index!=-1))
				if(!(op->addr.displacement_size==1 && op->addr.displacement==0))
					length += PutStr(pasm+length,"+");

			if (op->addr.displacement_size==1)
			{
				 
				if(op->addr.displacement)
					if (op->addr.displacement>=sign_BYTE)
					{
						length--;
						sprintf(buff,"-%X",(BYTE)(0-op->addr.displacement));
					}
					else
						sprintf(buff,"%X",(BYTE)op->addr.displacement);
				else
					buff[0]=0;

				length += PutStr(pasm+length,buff);
			}
			else if (op->addr.displacement_size==2)
			{
				sprintf(buff,"%04X",op->addr.displacement);

				length += PutStr(pasm+length,buff);
			}
			else if (op->addr.displacement_size==4)
			{
				sprintf(buff,"%08X",(DWORD)op->addr.displacement);
				length += PutStr(pasm+length,buff);
			}
			else if (op->addr.displacement_size==8)
			{
				sprintf(buff,"%08X",(DWORD)op->addr.displacement);
				length += PutStr(pasm+length,buff);
				//sprintf(buff,"%llX",(QWORD)op->addr.displacement);
				//length += PutStr(pasm+length,buff);
			}

			length += PutStr(pasm+length,"]");
		}
		else length +=PutStr(pasm+length,op->string);
	}

	pasm[length] = '\0';
	for(int m=0;m<length;m++)
		if(pasm[m]>='A' && pasm[m]<='Z')
			pasm[m]+=0x20;

	return length;
}
int PrintPasmForIDA(INSTRUCTION_INFORMATION *pInstInfo,char *pasm,int u_x1,int u_x2)
{
	int i,length;
	char buff[0x20];

	char **preg;

	for (i=0;i<=0x50;i++)
		pasm[i]=' ';

	pasm[i]='\0';

	length = u_x1;

	if (pInstInfo->Lock!=-1)
	{
		i = PutStr(pasm+length,pInstInfo->LockName);
		if (i) length += i+1;
	}

	if (pInstInfo->Repeat!=-1)
	{
		i = PutStr(pasm+length,pInstInfo->RepeatName);
		if (i) length += i+1;
	}

	length += PutStr(pasm+length,pInstInfo->Name);
	
	OPERAND_ITEM *op = 	pInstInfo->op;
	bool brsp=false;
	for(int ii=0;ii<3;ii++)
	{
		if(op[ii].mode==mode_register && (op[ii].opersize==4 || op[ii].opersize==8))
		{
			if(op[ii].reg.reg_index==4)
			{
				brsp=true;
				break;
			}
		}
	}
	for (i=0;i<3&&op->mode!=mode_invalid;i++,op++)
	{
		if (i==0)
		{
			if (length<u_x2)
				length = u_x2;
			else length++;
		}
	
		if (i>0)
			length +=PutStr(pasm+length,", ");

		if (op->mode==mode_address)
		{
			if (pInstInfo->xxxxptr!=-1&&pInstInfo->xxxxptr!=0)
			{
				length += PutStr(pasm+length,xxxxptr[pInstInfo->xxxxptr]);
				length += PutStr(pasm+length," PTR ");
			}
		
			if (pInstInfo->SegmentPrefix!=-1)
			{
				length += PutStr(pasm+length,SegReg[pInstInfo->SegmentPrefix]);
				length += PutStr(pasm+length,":");
			}
			
			if (op->addr.address_size==BIT32) 
				preg = RegDWord;
			else if(op->addr.address_size==BIT64)
				preg = RegQWord;
			else 
				preg = RegWord;
			//if(!brsp && op->addr.base==-1 && op->addr.displacement_size)
			if(op->addr.base==-1 && op->addr.displacement_size)
			{
				if (op->addr.displacement_size==1)
				{
					if (op->addr.displacement>=sign_BYTE) 
						sprintf(buff,"-%X",(BYTE)(0-op->addr.displacement));
					else 
						sprintf(buff,"+%X",(BYTE)op->addr.displacement);

					length += PutStr(pasm+length,buff);
				}
				else if (op->addr.displacement_size==2)
				{
					sprintf(buff,"%04X",op->addr.displacement);

					length += PutStr(pasm+length,buff);
				}
				else if (op->addr.displacement_size==4)
				{
					if(op->addr.address_size==BIT64)
					{
						sprintf(buff,"0%I64X",(QWORD)op->addr.displacement);
						if(buff[1]>='A' && buff[1]<='F')
							length += PutStr(pasm+length,buff);
						else
							length += PutStr(pasm+length,buff+1);
					}
					else
					{
						sprintf(buff,"0%X",(DWORD)op->addr.displacement);
						if(buff[1]>='A' && buff[1]<='F')
							length += PutStr(pasm+length,buff);
						else
							length += PutStr(pasm+length,buff+1);
					}
				}
				else if(op->addr.displacement_size==8)
				{
					sprintf(buff,"0%llX",(QWORD)op->addr.displacement);
					if(buff[1]>='A' && buff[1]<='F')
						length += PutStr(pasm+length,buff);
					else
						length += PutStr(pasm+length,buff+1);
				}
					
				if(op->addr.index!=-1)
				{
					length += PutStr(pasm+length,"[");
					
					if (op->addr.base!=-1) length += PutStr(pasm+length,"+");
					length += PutStr(pasm+length,preg[op->addr.index]);
					if (op->addr.scale>0)
					{
						sprintf(buff,"*%1x",1<<op->addr.scale);
						length += PutStr(pasm+length,buff);
					}
					
					length += PutStr(pasm+length,"]");
				}
			}
			else
			{
				if(!(op->addr.base==-1 && op->addr.index==-1 && brsp))
					length += PutStr(pasm+length,"[");
				if (op->addr.base!=-1)
					length += PutStr(pasm+length,preg[op->addr.base]);

				if (op->addr.index!=-1)
				{
					if (op->addr.base!=-1) length += PutStr(pasm+length,"+");
					length += PutStr(pasm+length,preg[op->addr.index]);
					if (op->addr.scale>0)
					{
						sprintf(buff,"*%1x",1<<op->addr.scale);
						length += PutStr(pasm+length,buff);
					}
				}

				//if (op->addr.displacement_size>=2&&(op->addr.base!=-1||op->addr.index!=-1))
				//	length += PutStr(pasm+length,"+");
			
				if (op->addr.displacement_size==1)
				{
					if (op->addr.displacement>=sign_BYTE) 
						sprintf(buff,"-%X",(BYTE)(0-op->addr.displacement));
					else 
						sprintf(buff,"+%X",(BYTE)op->addr.displacement);

					length += PutStr(pasm+length,buff);
				}
				else if (op->addr.displacement_size==2)
				{
					sprintf(buff,"%04X",op->addr.displacement);

					length += PutStr(pasm+length,buff);
				}
				else if (op->addr.displacement_size==4)
				{

					if (op->addr.displacement>=sign_DWORD) 
						sprintf(buff,"-%X",(DWORD)(0-op->addr.displacement));
					else 
						sprintf(buff,"+%X",(DWORD)op->addr.displacement);

					length += PutStr(pasm+length,buff);
				}
				else if (op->addr.displacement_size==8)
				{
					sprintf(buff,"%llX",(QWORD)op->addr.displacement);
					length += PutStr(pasm+length,buff);
				}
			
				length += PutStr(pasm+length,"]");
			}
		}
 		else length +=PutStr(pasm+length,op->string);
	}

	pasm[length] = '\0';
	for(int m=0;m<length;m++)
		if(pasm[m]>='A' && pasm[m]<='Z')
			pasm[m]+=0x20;

	return length;
}

void WriteEmblem(char *s)
{
	int i;

	if (s==NULL) return;

	for (i=0;Emblem[i]!=NULL;i++)
	{
		if (strcmp(s,Emblem[i])==0) break;
	}

	if (Emblem[i]==NULL) Emblem[i] = s;

	if (i>=0x200)
	{
		//tang add MessageBox(NULL,"Emblem","存储空间太小",MB_OK);
	}
}

void ReadIntelName(char *s,int num)
{
	int i;
	DIS_OPCODE_T *p = (DIS_OPCODE_T*)s;

 	for (i=0;i<num;i++)
	{
		if (p[i].OpcodeType==C_GRP)
		{
			ReadIntelName(p[i].name,0x08);
			continue;
		}

		if (p[i].OpcodeType==C_ESC)
		{
			ReadIntelName(p[i].name,0x08+0x40);
			continue;
		}

		if (p[i].OpcodeType==C_GRP1)
		{
			ReadIntelName(p[i].name,0x08+0x08);
			continue;
		}

		if (p[i].OpcodeType==C_2BYTE)
		{
			ReadIntelName(p[i].name,0x100);
			continue;
		}
		if (p[i].OpcodeType==C_GRP2)
		{
			ReadIntelName(p[i].name,72);
			continue;
		}
		if (p[i].OpcodeType==C_GRP3)
		{
			ReadIntelName(p[i].name,4);
			continue;
		}
		if (p[i].OpcodeType==C_GRP4)
		{
			ReadIntelName(p[i].name,0x08);
			continue;
		}
		if (p[i].OpcodeType==C_3BYTE_0X3A)
		{
			ReadIntelName(p[i].name,0x100);
			continue;
		}
		if (p[i].OpcodeType==C_3BYTE_0X38)
		{
			ReadIntelName(p[i].name,0x100);
			continue;
		}
		WriteEmblem(p[i].name);
	}
}

int Disassembly(INSTRUCTION_INFORMATION *pInstInfo,BYTE *inbuff,QWORD eip,int mode,DIS_CPU *DisCPU)
{
	DIS_OPCODE_T *pIntelOpcode;
	DISP_INSTRUCTION_T disp_i;
	DIS_CPU DisCPU_T;
	int OperatorSize;
	
	if (DisCPU==NULL)
		DisCPU = &DisCPU_T;
	unsigned ByteCount =0;
	unsigned Segment = 0-1;
	unsigned OpcodeType;
	disp_i.opcode_len=1;	
	disp_i.mode=disp_i.os_32 = disp_i.as_32 = mode; //BIT16,BIT32
	if(mode==BIT64)
		disp_i.os_32=BIT32;
	OperatorSize=disp_i.os_32;
	disp_i.lock = disp_i.rep_used = 0-1;
	disp_i.RIP_Relative=0;
	disp_i.mandatory_used=0;
	disp_i.perfix_len=0;
	disp_i.have_regrm=-1;
	disp_i.have_sib=-1;	
	disp_i.rex_prefix=0;
	pInstInfo->Is3DNow=-1;

GET_OPCODE:
	

	if (ByteCount>=0x0f)
		return 0;

	disp_i.b1 = inbuff[ByteCount++];

	pIntelOpcode = Group_main + disp_i.b1;
	if(BIT64 == mode && (disp_i.b1 >=0x40 && disp_i.b1 <=0x4f))
	{
		disp_i.rex_prefix = disp_i.b1;
		pIntelOpcode=RexPrefixFor64Bit+0;
	}
GET_OPATTR:

	OpcodeType = pIntelOpcode->OpcodeType;
	
	switch(OpcodeType)
	{
	case C_REX_PREFIX:
		disp_i.perfix_len++;
		if(disp_i.rex_prefix & 0x8)
		{
			disp_i.os_32 = BIT64;
			OperatorSize=disp_i.os_32;
		}
		goto GET_OPCODE;
	case C_ES:case C_CS:case C_SS:
	case C_DS:case C_FS:case C_GS:
		disp_i.perfix_len++;
		Segment = OpcodeType-C_ES;
		disp_i.rex_prefix=0;	
		disp_i.mandatory_used=0;
		goto GET_OPCODE;
	case C_OPER:
		switch(mode)
		{
		case BIT16:
			disp_i.os_32 = BIT32;
			break;
		case BIT32:
		case BIT64:
			disp_i.os_32 = BIT16;
			break;
		}		
		disp_i.perfix_len++;
		disp_i.mandatory_used=1;
		disp_i.rex_prefix=0;
		goto GET_OPCODE;

	case C_ADDR:

		switch(mode)
		{
		case BIT32:
			disp_i.as_32 = BIT16;
			break;
		case BIT16:			
		case BIT64:
			disp_i.as_32 = BIT32;
			break;
		}
		disp_i.perfix_len++;
		disp_i.mandatory_used=0;
		disp_i.rex_prefix=0;
		goto GET_OPCODE;
	case C_LOCK:
		disp_i.lock = 0xf0;
		disp_i.perfix_len++;
		disp_i.mandatory_used=0;
		disp_i.rex_prefix=0;
		goto GET_OPCODE;
	case C_REPN:
		disp_i.perfix_len++;
		disp_i.rep_used = 0xf2;
		disp_i.mandatory_used=2;
		disp_i.rex_prefix=0;
		goto GET_OPCODE;
	case C_REPZ:
		disp_i.rep_used = 0xf3;
		disp_i.mandatory_used=3;
		disp_i.perfix_len++;
		disp_i.rex_prefix=0;
		goto GET_OPCODE;
	case C_ESC:
		disp_i.opcode_len=2;
		if (inbuff[ByteCount]<0xc0)
			pIntelOpcode = (DIS_OPCODE_T*)pIntelOpcode->name +
								((inbuff[ByteCount]>>3)&0x07);
		else
			pIntelOpcode = (DIS_OPCODE_T*)pIntelOpcode->name+0x08 +
								inbuff[ByteCount++] - 0xc0;
		break;

	case C_3BYTE_0X38:	
		disp_i.opcode_len=3;
		disp_i.b1 = inbuff[ByteCount++];
		pIntelOpcode = (DIS_OPCODE_T*)pIntelOpcode->name + disp_i.b1;
		goto GET_OPATTR;
	case C_3BYTE_0X3A:	
		disp_i.opcode_len=3;
		disp_i.b1 = inbuff[ByteCount++];
		pIntelOpcode = (DIS_OPCODE_T*)pIntelOpcode->name + disp_i.b1;
		goto GET_OPATTR;
	case C_2BYTE:		
		disp_i.opcode_len=2;
		disp_i.b1 = inbuff[ByteCount++];
		pIntelOpcode = (DIS_OPCODE_T*)pIntelOpcode->name + disp_i.b1;
		goto GET_OPATTR;
	
	case C_GRP:						
		pIntelOpcode = (DIS_OPCODE_T*)pIntelOpcode->name +((inbuff[ByteCount]>>3)&0x07);
		break;
	case C_GRP5:

		pIntelOpcode = (DIS_OPCODE_T*)pIntelOpcode->name +((inbuff[ByteCount]>>3)&0x07);
		if(pIntelOpcode->OpcodeType==C_GRP3)
		{
			pIntelOpcode = (DIS_OPCODE_T*)pIntelOpcode->name+disp_i.mandatory_used;
			if(disp_i.mandatory_used==2 || disp_i.mandatory_used==3)
				disp_i.rep_used=0-1;
			else if(disp_i.mandatory_used==1)
				disp_i.os_32=OperatorSize;
		}
		break;
	case C_GRP1:
		if (inbuff[ByteCount]<0xc0)
			pIntelOpcode = (DIS_OPCODE_T*)pIntelOpcode->name + 
								((inbuff[ByteCount]>>3)&0x07);
		else
			pIntelOpcode = (DIS_OPCODE_T*)pIntelOpcode->name + 0x8 +
								((inbuff[ByteCount]>>3)&0x07);
		break;
	case C_GRP2:
		if (inbuff[ByteCount]<0xc0)
			pIntelOpcode = (DIS_OPCODE_T*)pIntelOpcode->name + 
			((inbuff[ByteCount]>>3)&0x07);
		else
			pIntelOpcode = (DIS_OPCODE_T*)pIntelOpcode->name + 0x8 + (((inbuff[ByteCount]>>3)&0x07)*8)+
			((inbuff[ByteCount])&0x07);
		break;
	case C_GRP3:	
		pIntelOpcode = (DIS_OPCODE_T*)pIntelOpcode->name+disp_i.mandatory_used;
		if(disp_i.mandatory_used==2 || disp_i.mandatory_used==3)
			disp_i.rep_used=0-1;
		else if(disp_i.mandatory_used==1)
			disp_i.os_32=OperatorSize;
		break;
	case C_GRP4:
		if (inbuff[ByteCount]<0xc0)//mod  = 0x00 0x01 0x10
			pIntelOpcode = (DIS_OPCODE_T*)pIntelOpcode->name+disp_i.mandatory_used;
		else//mod=0x11
			pIntelOpcode = (DIS_OPCODE_T*)pIntelOpcode->name+4+disp_i.mandatory_used;
		if(disp_i.mandatory_used==2 || disp_i.mandatory_used==3)
			disp_i.rep_used=0-1;
		else if(disp_i.mandatory_used==1)
			disp_i.os_32=OperatorSize;
		break;
	case C_GRP6:
		if(mode == BIT64)
			pIntelOpcode = (DIS_OPCODE_T*)pIntelOpcode->name+1;
		else
			pIntelOpcode = (DIS_OPCODE_T*)pIntelOpcode->name;
		break;

	}

	if (pIntelOpcode->name==NULL)
	{
		return 0;
	}
	if(BIT64 == mode && pIntelOpcode->Attr & I_64)
		return 0;
	if(pIntelOpcode->Attr & O_64 && BIT64 != mode)
		return 0;
	if(( pIntelOpcode->Attr & D_64) && BIT64 == mode && disp_i.os_32 == BIT32)//there are some instruction default operator size is fouce 64bit 
	{
		disp_i.os_32 = BIT64;
	}
	if(( pIntelOpcode->Attr & F_64) && BIT64 == mode)//there are some instruction default operator size is fouce 64bit 
	{
		disp_i.os_32 = BIT64;
	}
	disp_i.attr = pIntelOpcode->Attr;
	disp_i.destination = pIntelOpcode->Opdata1;
	disp_i.source = pIntelOpcode->Opdata2;
	disp_i.other = pIntelOpcode->Opdata3;
	if ((disp_i.attr&R_M)==R_M)
	{
		if (disp_i.as_32==BIT16)
			ByteCount += GetEffectAddress16Dis(DisCPU,inbuff+ByteCount,&disp_i);
		else
			ByteCount += GetEffectAddress32Dis(DisCPU,inbuff+ByteCount,&disp_i);	
	}

	ByteCount += ProcessOpdata_immde(disp_i.destination,inbuff+ByteCount,&disp_i);
	ByteCount += ProcessOpdata_immde(disp_i.source,inbuff+ByteCount,&disp_i);
	ByteCount += ProcessOpdata_immde(disp_i.other,inbuff+ByteCount,&disp_i);

	if (ByteCount>=0x0f)
		return 0;

	disp_i.ilen = ByteCount;

	//--------------------------------------------------------------------

	pInstInfo->OpCode = pIntelOpcode->OpcodeType;
	pInstInfo->OpType = 0;
	pInstInfo->CodeType = 0;
	pInstInfo->Length = disp_i.ilen;
	pInstInfo->Repeat = disp_i.rep_used;
	pInstInfo->Lock = disp_i.lock;
	pInstInfo->OpcodeLen=disp_i.opcode_len;
	pInstInfo->PrefixLen=disp_i.perfix_len;
	pInstInfo->Have_RegRM=disp_i.have_regrm;
	pInstInfo->Have_SIB=disp_i.have_sib;
	pInstInfo->Rex_Prefix=disp_i.rex_prefix;
	if (!ProcessName_dis(pInstInfo,pIntelOpcode,disp_i.os_32,disp_i.as_32))
		return 0;

	int temp;

	temp = ProcessOpdata_dis(pIntelOpcode->Opdata1,&pInstInfo->op[0],eip,&disp_i,DisCPU);
	if (temp==-1)
		return 0;

	temp = ProcessOpdata_dis(pIntelOpcode->Opdata2,&pInstInfo->op[1],eip,&disp_i,DisCPU);
	if (temp==-1)
		return 0;

	temp = ProcessOpdata_dis(pIntelOpcode->Opdata3,&pInstInfo->op[2],eip,&disp_i,DisCPU);
	if (temp==-1)
		return 0;

	if (disp_i.seg!=Segment&&Segment!=-1)
	{
		pInstInfo->SegmentPrefix = Segment;
		for (int i=0;i<3;i++)
		{
			if (pInstInfo->op[i].mode==mode_address)
			{
				pInstInfo->op[i].addr.line_address = 
					pInstInfo->op[i].addr.effect_address + DisCPU->SEG_BASE[Segment];
			}
		}
	}
	else
	{
		pInstInfo->SegmentPrefix = 0-1;
		for (int i=0;i<3;i++)
		{
			if (pInstInfo->op[i].mode==mode_address)
			{
				pInstInfo->op[i].addr.line_address = 
					pInstInfo->op[i].addr.effect_address + DisCPU->SEG_BASE[disp_i.seg];
			}
		}
	}

	
/*
	if (pInstInfo->op[0].mode==mode_address&&pInstInfo->op[0].opersize!=0&&
		(pInstInfo->op[1].mode==mode_immed||pInstInfo->op[1].mode==mode_invalid)
		)
	{
		pInstInfo->xxxxptr = pInstInfo->op[0].opersize;
	}
	else
	{
		pInstInfo->xxxxptr = 0-1;
	}

	if (pInstInfo->op[1].mode==mode_address&&pInstInfo->op[1].opersize!=0&&pInstInfo->op[1].opersize < pInstInfo->op[0].opersize)
	{
		pInstInfo->xxxxptr = pInstInfo->op[1].opersize;
	}
	else
	{
		if(pInstInfo->op[1].mode!=mode_invalid)
			pInstInfo->xxxxptr = 0-1;
	}
*/
	pInstInfo->xxxxptr=-1;
	if(pInstInfo->OpCode==C_3DNOW)
	{
		temp = GetValue_b(inbuff+ByteCount);
		if(Group0x0f0f[(temp&0xff)].OpcodeType==C_NULL||Group0x0f0f[(temp&0xff)].name==NULL)
			return 0;
		strcpy(pInstInfo->Name,Group0x0f0f[(temp&0xff)].name);
		pInstInfo->Length++;
		ByteCount++;
		pInstInfo->OpCode=Group0x0f0f[(temp&0xff)].OpcodeType;
		pInstInfo->Is3DNow=1;
	}
	if(pInstInfo->OpCode==C_XCHG_NOP)
	{
		if(pInstInfo->op[1].reg.reg_index==0)
		{
			if(disp_i.mandatory_used==3&&disp_i.rex_prefix==0)
			{
				pInstInfo->OpCode=C_PAUSE;
				pInstInfo->Repeat=-1;
				strcpy(pInstInfo->Name,"PAUSE");
				pInstInfo->op[0].mode=mode_invalid;
				pInstInfo->op[1].mode=mode_invalid;
			}
			else if(pInstInfo->PrefixLen==0)
			{
				pInstInfo->OpCode=C_NOP;
				strcpy(pInstInfo->Name,"NOP");
				pInstInfo->op[0].mode=mode_invalid;
				pInstInfo->op[1].mode=mode_invalid;
			}
			else
				pInstInfo->OpCode=C_XCHG;
		}
		else
		{
			pInstInfo->OpCode=C_XCHG;
		}
	}
	if (pInstInfo->pasm!=NULL)
	{
		pInstInfo->U_x3 = PrintPasm(pInstInfo,pInstInfo->pasm,
			pInstInfo->U_x1,pInstInfo->U_x2);
	}
	return ByteCount;
}

//——————————————反汇编模块————————————————

//----------------------------------------------------------------------
//----------------------------------------------------------------------
//----------------------------------------------------------------------

//——————————————正汇编模块————————————————

void PutCode_b(ASSEMBLY_INFOMATION *pasm_info,BYTE value)
{
	SetValue_b(pasm_info->CodeBuff+pasm_info->InstLength,value);
	pasm_info->InstLength += 1;
}

void PutCode_w(ASSEMBLY_INFOMATION *pasm_info,WORD value)
{
	SetValue_w(pasm_info->CodeBuff+pasm_info->InstLength,value);
	pasm_info->InstLength += 2;
}

void PutCode_d(ASSEMBLY_INFOMATION *pasm_info,DWORD value)
{
	SetValue_d(pasm_info->CodeBuff+pasm_info->InstLength,value);
	pasm_info->InstLength += 4;
}

DWORD ProcessParameter(char * px,POPER_ITEM op)
{	
	int i,j,k,ii;
	DWORD v1,v2;
	v1=v2=0;
	char s1[0x80];

	op->mode=OP_Invalid;
	op->opersize=0;
	op->prefix_size=-1;
	op->addr.seg_index=0xff;
	op->addr.off_value=0;

	if (px[0]=='\0') 
	{
		op->mode=OP_Invalid;
		return 0;
	}
//Get string
	i = 0;
	if (px[i]=='\''||px[i]=='"')
	{
		for (i++,j=0;px[i]!=px[0]&&px[i]!='\0';j++,i++)
			op->string[j] = px[i];
		if (px[i]==px[0])
		{
			op->string[j]='\0';
			i++;
			op->mode = OP_String;
			return 0;
		}
	}
	
//Get ES: CS: SS: DS: FS: GS: 	
	for (j=0;j<6;j++)
	{
		for (i=0;px[i]==SegReg[j][i];i++);
		if (i==2&&px[i]==':') 
		{
			op->addr.seg_index=j;
			px=px+i+1;
			break;
		}

	}
	
// Get ... Xptr 	
	for (j=0;j<sizeof(OpDataWide)/sizeof(OpDataWide[0]);j++)
	{
		for (i=0;px[i]==OpDataWide[j].Xptr[i];i++);
					
		if (i>2||OpDataWide[j].Xptr[0]!='F'&&i>1) 
		{
			for (;px[i]!='[' && px[i]!=' '&& px[i]!='\0' && (px[i]<'0'&&  px[i]>'9');i++);
			if (px[i]==' ') 
				i++;
			op->opersize=OpDataWide[j].Size;
			op->prefix_size=OpDataWide[j].Size;
			px=px+i;
			break;
		}
	}

//ES: CS: SS: DS: FS: GS: 	
	for (j=0;j<sizeof(SegReg)/sizeof(SegReg[0]);j++)
	{
		for (i=0;px[i]==SegReg[j][i];i++);
		if (i==2&&px[i]==':') 
		{
			op->addr.seg_index=j;
			px=px+i+1;
			break;
		}
	}

//OP_Invalid
	if (px[0]=='\0') 
	{
		op->mode=OP_Invalid;
		return 0;
	}
	
//Register	
	for (i=0;i<8;i++)
	{
		if (TStrICmp(px,RegByte[i])==0)
		{
			op->opersize=1;
			op->reg_type=OP_ByteRegister;
			break;
		}
		if (TStrICmp(px,RegWord[i])==0)
		{
			op->opersize=2;
			op->reg_type=OP_WordRegister;
			break;
		}
		if (TStrICmp(px,RegDWord[i])==0)
		{
			op->opersize=4;
			op->reg_type=OP_DwordRegister;
			break;
		}
		if(TStrICmp(px,RegMMXQWord[i])==0)
		{
			op->opersize=8;
			op->reg_type=OP_MMXRegister;
			break;
		}
		if(TStrICmp(px,RegXMMOWord[i])==0)
		{
			op->opersize=16;
			op->reg_type=OP_XMMRegister;
			break;
		}
		if(TStrICmp(px,RegCR[i])==0)
		{
			op->opersize=4;
			op->reg_type=OP_ControlRegister;
			break;
		}
		if(TStrICmp(px,RegDR[i])==0)
		{
			op->reg_type=OP_DebugRegister;
			op->opersize=4;
			break;
		}
		if(TStrICmp(px,RegFPU[i])==0)
		{
			op->reg_type=OP_FPURegister;
			op->opersize=10;
			break;
		}
		
	}

	if (i<8)
	{
		op->mode=OP_Register;
		op->reg.reg_index=i;
		return 0;
	}
	if(TStrICmp(px,RegFPU[8])==0)
	{
		op->reg_type=OP_FPURegister;
		op->mode=OP_Register;
		op->reg.reg_index=8;
		op->opersize=10;
		return 0;
	}
//Segment register
	for (i=0;i<sizeof(SegReg)/sizeof(SegReg[0]);i++)
	{
		if (TStrICmp(px,SegReg[i])==0)
		{
			op->mode=OP_Segment;
			op->opersize=2;
			op->sreg.sreg_index=i;
			op->reg_type=OP_SegmentRegister;
			break;
		}
	}
	if (i<6) 
		return 0;
	
	
	i=0;
	j=0;
	k=0;

	if (px[i]=='+'||px[i]=='-') i++;

	if (px[i]>='0'&&px[i]<='9'||px[i]>='A'&&px[i]<='F')
	{
		for ( ;px[i]=='0';i++);

		for (ii=0;px[i+ii]>='0'&&px[i+ii]<='9'||
				 px[i+ii]>='A'&&px[i+ii]<='F';ii++);
		if (px[i+ii]=='\0'&&ii<=0x8)
		{
			SHexStrToNum(px,&op->immed.immed_value);
			//sscanf(px,"%x",&(op->immed.immed_value));
			op->mode=OP_Immed;
			return 0;
		}
		
		if (px[i+ii]==':'&&ii<=0x4)
		{
			for (k=i+ii+1;px[k]>='0'&&px[k]<='9'||
				px[k]>='A'&&px[k]<='F';k++);

			if (px[k]=='\0')
			{
				op->mode=OP_Far;
				op->opersize=4;
				//sscanf(px,"%x:%x",&(op->farptr.segment),&(op->farptr.offset));
				char szBuffer[256],*pStr;
				strcpy(szBuffer,px);
				pStr=TStrChr(szBuffer,':');
				if(pStr==NULL)
					return 0;
				*pStr=0;
				pStr++;
				SHexStrToNum(szBuffer,&op->farptr.segment);
				SHexStrToNum(pStr,&op->farptr.offset);
				return 0;
			}
		}

		if (px[i+ii]=='['&&ii<=0x8)  //   4010ac[ebx+ecx]
		{
			//sscanf(px,"%x",&(op->addr.off_value));
			px[i+ii]=0;
			SHexStrToNum(px,&(op->addr.off_value));
			px[i+ii]='[';
			i=i+ii;
		}
		else 
			i=0;
	}
	else 
		i=0;
		

//Get address	
	if (px[i]=='[')
	{	
		for (ii=1;px[i+ii]!='\0';ii++);

		ii--;
		
		if (px[i+ii]==']') ii--;

		if (px[i+ii]>='0'&&px[i+ii]<='9'||
		   px[i+ii]>='A'&&px[i+ii]<='F')
		{
			for (;px[i+ii]>='0'&&px[i+ii]<='9'||
				px[i+ii]>='A'&&px[i+ii]<='F';ii--);
			
			if  (px[i+ii]=='*') ii++;
		
			if  (px[i+ii]=='+'||px[i+ii]=='-') ii--;
			int oo=0;
			char tmpchr=0;
			oo=i+ii+1;
			for(;px[oo]!=']'&& px[oo];oo++);
			tmpchr=px[oo];
			px[oo]=0;
			SHexStrToNum(&px[i+ii+1],&v1);
			px[oo]=tmpchr;
			op->addr.off_value=op->addr.off_value+v1;
		}
		else
		{
			//if (ii==0) return 1;
		}

		
		px[i+ii+1]=']';
		px[i+ii+2]='\0';
		
		px=px+i;
		
//offset16  or offset32 
		if (TStrICmp(px,"[]")==0)
		{
			op->addr.reg_size=0;
			op->mode=OP_Address;
			return 0;
		}
		
//RegAddr16
		for (j=0;j<sizeof(RegAddr16)/sizeof(RegAddr16[0]);j++)
		{
			
			if (TStrICmp(px,RegAddr16[j])==0)
			{
				op->addr.reg_size=2;
				op->addr.base_reg_index=j>>2;
				op->mode=OP_Address;
				return 0;
			}
		}

//RegAddr32 [eax]
		for (j=0;j<sizeof(RegDWord)/sizeof(RegDWord[0]);j++)
		{
			if (j==4) j++;

		    sprintf(s1,"%s%s%s","[",RegDWord[j],"]");

			if (TStrICmp(px,s1)==0)
			{
				op->addr.reg_size=4;
				op->addr.base_reg_index=j;
				op->mode=OP_Address;
				return 0;
			}

		}

//Regaddr32 [esp] or [esp+12] or [esp+12345678]

		if (TStrICmp(px,"[ESP]") == 0)
		{
			op->addr.reg_size=6;
  		    op->addr.base_reg_index=4;
		    op->addr.off_reg_index=4;
		    op->addr.off_reg_scale=0;
			op->mode=OP_Address;
			return 0;
		}
		
//RegAddr32	[eax+eax*1]
		for (i=0;i<8;i++)
			for (j=0;j<8;j++)
				for (k=0;k<4;k++)
				{
					if (j==4) j++;
					
					sprintf(s1,"%s%s%s%s%s%c%s","[",RegDWord[i],"+",
							RegDWord[j],"*",(1<<k)+0x30,"]");

					if (TStrICmp(px,s1)==0)
					{
						op->addr.reg_size=6;
		    		    op->addr.base_reg_index=i;
					    op->addr.off_reg_index=j;
					    op->addr.off_reg_scale=k;
						op->mode=OP_Address;
						return 0;
					}
	
					if (k==0)
					{
						sprintf(s1,"%s%s%s%s%s","[",RegDWord[i],"+",
										RegDWord[j],"]");
						if (TStrICmp(px,s1)==0)
						{
							op->addr.reg_size=6;
		    			    op->addr.base_reg_index=i;
						    op->addr.off_reg_index=j;
						    op->addr.off_reg_scale=0;
							op->mode=OP_Address;
							return 0;
						}
					}
				}
				return 1;
	}		
	
//Get Invalid
	op->mode = OP_Invalid;
	return 1;
}

DWORD ModeAddress(ASSEMBLY_INFOMATION *pasm_info,POPER_ITEM op,int opsize)
{
	if (op->addr.seg_index!=0xff) 
		pasm_info->SegmentPrefix=SegmentValue[op->addr.seg_index];
	if(opsize!=-1 && op->prefix_size!=-1)
	{
		if(opsize!=op->opersize)
			return 1;
	}
	if (op->addr.reg_size==0)
	{
		pasm_info->pmodr_m->mod = 0;

		if (pasm_info->CodeMode==BIT32)
		{  
			pasm_info->AddressSize = 4;
			pasm_info->pmodr_m->r_m = 5;
			PutCode_d(pasm_info,(DWORD)(op->addr.off_value));
			return 0;
		}
		if (op->addr.off_value<=0xffff)
		{
			pasm_info->AddressSize=2;
			pasm_info->pmodr_m->r_m=6;
			PutCode_w(pasm_info,(WORD)(op->addr.off_value));
		}
		else 
		{
			pasm_info->AddressSize=4;
			pasm_info->pmodr_m->r_m=5;
			PutCode_d(pasm_info,(DWORD)(op->addr.off_value));
		}
		return 0;
	}
		
	if (op->addr.reg_size==2)
	{
		pasm_info->AddressSize=2;
		pasm_info->pmodr_m->r_m=op->addr.base_reg_index;
		pasm_info->InstLength=pasm_info->InstLength;
		if (op->addr.off_value==0)
		{
			pasm_info->pmodr_m->mod=0;
			if (op->addr.base_reg_index==6)
			{
				pasm_info->pmodr_m->mod=1;
				PutCode_b(pasm_info,(BYTE)(op->addr.off_value));
			}
			return 0;
		}
			
		if (op->addr.off_value<=0xff||op->addr.off_value>=0xffffff80)
		{
			pasm_info->pmodr_m->mod=1;
			PutCode_b(pasm_info,(BYTE)(op->addr.off_value));
			return 0;
		}
		if (op->addr.off_value<=0xffff)
		{
			pasm_info->pmodr_m->mod=2;
			PutCode_w(pasm_info,(WORD)(op->addr.off_value));
			return 0;
		}
		if (op->addr.off_value>0xffff) return 1;

	}
	
	if (op->addr.reg_size==4)
	{
		pasm_info->AddressSize=4;
		pasm_info->pmodr_m->r_m=op->addr.base_reg_index;
	
		if (op->addr.off_value==0)
		{
			pasm_info->pmodr_m->mod=0;

			if (op->addr.base_reg_index==5)
			{
				pasm_info->pmodr_m->mod=1;
				PutCode_b(pasm_info,(BYTE)(op->addr.off_value));
			}
			return 0;
		}
			
		if (op->addr.off_value<=0xff||op->addr.off_value>=0xffffff80)
		{
			pasm_info->pmodr_m->mod=1;
			PutCode_b(pasm_info,(BYTE)(op->addr.off_value));
			return 0;
		}
		else 
		{
			pasm_info->pmodr_m->mod=2;
			PutCode_d(pasm_info,(DWORD)(op->addr.off_value));
			return 0;
		}
	}

	if (op->addr.reg_size==6)
	{
		
		pasm_info->AddressSize=4;
		pasm_info->pmodr_m->r_m=4;
		pasm_info->pmodr_m->base=op->addr.base_reg_index;
		pasm_info->pmodr_m->index=op->addr.off_reg_index;
		pasm_info->pmodr_m->scale=op->addr.off_reg_scale;
		pasm_info->InstLength=pasm_info->InstLength+1;

		if (op->addr.off_value==0)
		{
			pasm_info->pmodr_m->mod=0;
			if (op->addr.base_reg_index==5)
			{
				pasm_info->pmodr_m->mod=1;
				PutCode_b(pasm_info,(BYTE)(op->addr.off_value));
			}
			return 0;
		}
			
		if (op->addr.off_value<=0xff)
		{
			pasm_info->pmodr_m->mod=1;
			PutCode_b(pasm_info,(BYTE)(op->addr.off_value));
			return 0;
		}
		else 
		{
			pasm_info->pmodr_m->mod=2;
			PutCode_d(pasm_info,(DWORD)(op->addr.off_value));
			return 0;
		}
	}
	
	return 1;
}

int ProcessName_asm(ASSEMBLY_INFOMATION *pasm_info,DIS_OPCODE_T *inst)
{
	int i,codesize;
	int opdata;

	if (inst==NULL) return 0-1;

	if (inst->name==NULL) return 0-1;
	
	if (strcmp(pasm_info->Name,inst->name)==0)
	{
		if (pasm_info->CodeMode==BIT32) codesize = 4;
		else codesize = 2;
		
		for (i=0;i<3;i++)
		{
			if (i==0) opdata = inst->Opdata1;
			else if (i==1) opdata = inst->Opdata2;
			     else  opdata = inst->Opdata3;
			
			switch(opdata)
			{
			case D__Xb:
						pasm_info->NameSize = SIZE_b;
						break;
			case D__Xv:		// Used for ( MOVS: LODS: OUTS: ... )
						pasm_info->NameSize = codesize;
						break;
			case D__Fv:
					// Used for PUSHA/POPA, PUSHF/POPF, SHAF/LAHF
						pasm_info->NameSize = codesize;
						break;
			};
		}

		return 	inst->OpcodeType;
	}
	else return 0-1;
}

int ProcessOpdata_asm(ASSEMBLY_INFOMATION *pasm_info,int OpCodeDataType,POPER_ITEM op)
{
	int i;
	int codesize;
	int optsize=-1;
	OPCODETYPE opdata=(OPCODETYPE)OpCodeDataType;

	if (pasm_info->CodeMode==BIT32) 
		codesize = 4;
	else 
		codesize = 2;

	switch(opdata)
	{
	case D__NONE:			// No any types
				if (op->mode==OP_Invalid) 
					return 0;			
				break;
	case D__Eb:case D__rEb:case D__wEb:case D__rwEb:
	case D__Ew:case D__rEw:case D__wEw:case D__rwEw:
	case D__Ed:case D__rEd:case D__wEd:case D__rwEd:
	case D__Ev:case D__rEv:case D__wEv:case D__rwEv:
			// A ModR/M bytes: specifies the operand size.

			if (opdata>=D__Eb&&opdata<=D__rwEb&&op->opersize!=SIZE_b)
				break;
			if (opdata>=D__Ew&&opdata<=D__rwEw&&op->opersize!=SIZE_w)
				break;
			if (opdata>=D__Ed&&opdata<=D__rwEd&&op->opersize!=SIZE_d)
				break;
			if (opdata>=D__Ev&&opdata<=D__rwEv&&op->opersize!=SIZE_w&&op->opersize!=SIZE_d)
				break;

			if (opdata==D__Ev)
				pasm_info->OperandSize = op->opersize;

			if (op->mode==OP_Register)
			{
				pasm_info->pmodr_m->mod=3;
				pasm_info->pmodr_m->r_m=op->reg.reg_index;
				return 0;
			}
				
			if (op->mode==OP_Address) 
				return ModeAddress(pasm_info,op,-1);

			break;

	case D__word_int:
		if (optsize==-1) optsize = SIZE_w;
	case D__dword_int:
		if (optsize==-1) optsize = SIZE_d;
	case D__qword_int:
		if (optsize==-1) optsize = SIZE_q;

	case D__single_real:
		if (optsize==-1) optsize = SIZE_d;
	case D__double_real:
		if (optsize==-1) optsize = SIZE_q;
	case D__extend_real:
		if (optsize==-1) optsize = SIZE_t;
	case D__packed_BCD:
		if (optsize==-1) optsize = SIZE_t;

	case D__2b:
		if (optsize==-1) optsize = SIZE_w;
	case D__14_28b:
		if (optsize==-1) optsize = SIZE_t;
	case D__98_108b:
		if (optsize==-1) optsize = SIZE_t;
		if (op->mode==OP_Address) 
			return ModeAddress(pasm_info,op,optsize);

		break;

	case D__Gb:case D__rGb:case D__wGb:case D__rwGb:
	case D__Gd:case D__rGd:case D__wGd:case D__rwGd:
	case D__Gw:case D__rGw:case D__wGw:case D__rwGw:
	case D__Gv:case D__rGv:case D__wGv:case D__rwGv:// The reg field of the ModR/M byte selects a normal register.

			if (opdata==D__Gb&&op->opersize!=SIZE_b) 
				break;

			if (opdata==D__Gw&&op->opersize!=SIZE_w) 
				break;

			if (opdata==D__Gd&&op->opersize!=SIZE_d) 
				break;

			if (opdata==D__Gv&&op->opersize!=SIZE_w&&op->opersize!=SIZE_d) 
				break;

			if (opdata==D__Gv)
				pasm_info->OperandSize = op->opersize;
	
			if (op->mode==OP_Register)
			{
				pasm_info->pmodr_m->reg=op->reg.reg_index;
				return 0;
			}
			
			break;

	case D__Ib2:
case D__Ib:
			if (op->mode==OP_Immed&&(op->immed.immed_value<=0xff||op->immed.immed_value>=0xffffff80))
			{
				PutCode_b(pasm_info,(BYTE)op->immed.immed_value);
				return 0;
			}
			
			break;
		

case D__Iw:
			if (op->mode==OP_Immed&&(op->immed.immed_value<=0xffff||op->immed.immed_value>=0xffff8000))
			{
				PutCode_w(pasm_info,(WORD)op->immed.immed_value);
				return 0;
			}
			
			break;
		

case D__Iv:	// Immediate data.
			if (op->mode==OP_Immed&&(pasm_info->OperandSize==SIZE_w&&(op->immed.immed_value<=0xffff||op->immed.immed_value>=0xffff8000)||pasm_info->OperandSize==SIZE_d))
			{
				if (pasm_info->OperandSize==SIZE_d) 
					PutCode_d(pasm_info,(DWORD)op->immed.immed_value);
				else 
					PutCode_w(pasm_info,(WORD)op->immed.immed_value);
				return 0;
			}
			
			break;

case D__sIb:
			if (op->mode==OP_Immed&&(op->immed.immed_value<0x80||op->immed.immed_value>=0xffffff80))
			{
				PutCode_b(pasm_info,(BYTE)op->immed.immed_value);
				return 0;
			}
			
			break;
								// Signed Immediate data.

case D__Sw:			// The reg field of the ModR/M byte selects a segment register.
			if  (op->mode==OP_Segment&&	op->opersize==SIZE_w)
			{
				pasm_info->pmodr_m->reg=op->sreg.sreg_index;
				pasm_info->OperandSize = op->opersize;
				return 0;
			}
			
			break;


case D__M:case D__rM:case D__wM:case D__rwM:
case D__Ma:case D__rMa:case D__wMa:case D__rwMa:
case D__Mb:case D__rMb:case D__wMb:case D__rwMb:
case D__Mp:case D__rMp:case D__wMp:case D__rwMp:
case D__Ms:case D__rMs:case D__wMs:case D__rwMs:
case D__Mq:case D__wMq:case D__rMq:case D__rwMq:
case D__Mps:case D__wMps:case D__rMps:case D__rwMps:
case D__Mpd:case D__wMpd:case D__rMpd:case D__rwMpd:
case D__Mdq:case D__wMdq:case D__rMdq:case D__rwMdq:	
case D__Md:case D__rMd:case D__wMd:case D__rwMd:
case D__Mw:case D__rMw:case D__wMw:case D__rwMw:
case D__Mv:case D__rMv:case D__wMv:case D__rwMv:


			if (op->mode==OP_Address)
				return ModeAddress(pasm_info,op,-1);
			
			break;

case D__st:
	if(op->mode==OP_Register && op->reg_type==OP_FPURegister && (op->reg.reg_index==8||op->reg.reg_index==0))

		return 0;
	break;
case D__st0:
	if(op->mode==OP_Register && op->reg_type==OP_FPURegister && (op->reg.reg_index==0|| op->reg.reg_index==8))
		return 0;
	break;
case D__st1:
	if(op->mode==OP_Register && op->reg_type==OP_FPURegister && op->reg.reg_index==1)
		return 0;
	break;
case D__st2:
	if(op->mode==OP_Register && op->reg_type==OP_FPURegister && op->reg.reg_index==2)
		return 0;
	break;
case D__st3:
	if(op->mode==OP_Register && op->reg_type==OP_FPURegister && op->reg.reg_index==3)
		return 0;
	break;
case D__st4:
	if(op->mode==OP_Register && op->reg_type==OP_FPURegister && op->reg.reg_index==4)
		return 0;
	break;
case D__st5:
	if(op->mode==OP_Register && op->reg_type==OP_FPURegister && op->reg.reg_index==5)
		return 0;
	break;
case D__st6:
	if(op->mode==OP_Register && op->reg_type==OP_FPURegister && op->reg.reg_index==6)
		return 0;
	break;
case D__st7:
	if(op->mode==OP_Register && op->reg_type==OP_FPURegister && op->reg.reg_index==7)
		return 0;
	break;


case D_NEAR:
			if (op->mode==OP_Register&&	(op->opersize==SIZE_w|| op->opersize==SIZE_d))
			{
				pasm_info->OperandSize=op->opersize;
				pasm_info->pmodr_m->mod=3;
				pasm_info->pmodr_m->r_m=op->reg.reg_index;
				pasm_info->InstLength=pasm_info->InstLength+1;
				return 0;
			}
	
			if (op->mode==OP_Address&&op->opersize==codesize)
			{
				pasm_info->OperandSize=op->opersize;
				return ModeAddress(pasm_info,op,-1);
			}
		
			break;

case D_MFAR:

			if (op->mode==OP_Address&&(op->opersize==SIZE_w+SIZE_w|| op->opersize==SIZE_d+SIZE_w))
			{
				pasm_info->OperandSize=op->opersize-SIZE_w;
				return ModeAddress(pasm_info,op,-1);
			}
			break;

case D__Ob:case D__rOb:case D__wOb:case D__rwOb:
case D__Ov:case D__rOv:case D__wOv:case D__rwOv:

			// The offset of the operand is coded as a word or d-word ( no ModR/M )
			if (op->mode==OP_Address&&	op->addr.reg_size==0)
			{
				
				if (op->addr.seg_index!=0xff) 
					pasm_info->SegmentPrefix=SegmentValue[op->addr.seg_index];
				
				if (pasm_info->CodeMode==BIT32)
				{  
					pasm_info->AddressSize= codesize;
					PutCode_d(pasm_info,(DWORD)(op->addr.off_value));
					return 0;
				}
				
				if (op->addr.off_value<=0xffff)
				{
					pasm_info->AddressSize=SIZE_w;
					PutCode_w(pasm_info,(WORD)(op->addr.off_value));
					return 0;
				}
			}
	
			break;

case D__Jb:
			if (op->mode==OP_Immed&& (op->immed.immed_value-pasm_info->eip-2<0x80||  op->immed.immed_value-pasm_info->eip-2>=0xffffff80))
				{
					PutCode_b(pasm_info,(BYTE)(op->immed.immed_value-pasm_info->eip-2));
					return 0;
				}
			
			break;

case D__Jz:
	
			if (op->mode==OP_Immed)
			{
				if (pasm_info->CodeMode==BIT32)
				{
					int deta=5;
					if(pasm_info->OpcodeType >= C_JtO && pasm_info->OpcodeType <= C_JtG)
					{
						if (op->mode==OP_Immed&& (op->immed.immed_value-pasm_info->eip-2<0x80||  op->immed.immed_value-pasm_info->eip-2>=0xffffff80))
							break;
						deta=6;	
					}
					PutCode_d(pasm_info,(DWORD)(op->immed.immed_value-pasm_info->eip-deta));
					return 0;
				}
		
				if  (op->immed.immed_value-pasm_info->eip-3<0x8000|| op->immed.immed_value-pasm_info->eip-3>=0xffff8000)
				{
					PutCode_w(pasm_info,(WORD)(op->immed.immed_value-pasm_info->eip-3));
				}
				else
				{
					pasm_info->OperandSize = SIZE_d;
					PutCode_d(pasm_info,(DWORD)(op->immed.immed_value-pasm_info->eip-5));
				}
				return 0;
			}

			break;

case D__Ap:	// The instruction contains a relative offset to be added to EIP.
			if (op->mode==OP_Far)
			{
				if (pasm_info->CodeMode==BIT32)
				{
					PutCode_d(pasm_info,(DWORD)(op->farptr.offset));
					PutCode_w(pasm_info,(WORD)(op->farptr.segment));
					return 0;
				}

				if (op->farptr.offset<=0xffff)
				{
					PutCode_w(pasm_info,(WORD)(op->farptr.offset));
					PutCode_w(pasm_info,(WORD)(op->farptr.segment));
				}
				else
				{
					pasm_info->OperandSize = SIZE_d;
					PutCode_d(pasm_info,(DWORD)(op->farptr.offset));
					PutCode_w(pasm_info,(WORD)(op->farptr.segment));
				}
				return 0;
			}

			break;

case D__Rd:			// The mod field of the ModR/M byte may refer only to a general register.
	if(op->reg_type==OP_DwordRegister && op->mode==OP_Register)
	{
		pasm_info->pmodr_m->mod=3;
		pasm_info->pmodr_m->r_m=op->reg.reg_index;
		return 0;
	}
	break;
case D__Cd:			// The reg field of the ModR/M byte selects a control register.
	if(op->reg_type==OP_ControlRegister && op->mode==OP_Register)
	{
		pasm_info->pmodr_m->reg=op->reg.reg_index;
		return 0;
	}
	break;
case D__Dd:			// The reg field of the ModR/M byte selects a debug register.
	if(op->reg_type==OP_DebugRegister && op->mode==OP_Register)
	{
		pasm_info->pmodr_m->reg=op->reg.reg_index;
		return 0;				
	}
	break;	
case D__1:			// Only used for ( Group2 SHL/SHR... instruction )
			if  (op->mode==OP_Immed&&op->immed.immed_value==1) 
				return 0;
			
			break;
case D__Pd:case D__rPd:case D__wPd:case D__rwPd:
case D__Pq:case D__rPq:case D__wPq:case D__rwPq:
case D__Ppi:case D__rPpi:case D__wPpi:case D__rwPpi:
	if(op->mode==OP_Register)
	{
		if(op->reg_type==OP_MMXRegister)
		{
			pasm_info->pmodr_m->reg=op->reg.reg_index;
			return 0;
		}
	}
	break;
case D__Qd:case D__wQd:case D__rQd:case D__rwQd:
case D__Qq:case D__wQq:case D__rQq:case D__rwQq:
case D__Qpi:case D__wQpi:case D__rQpi:case D__rwQpi:
case D__Qdq:case D__wQdq:case D__rQdq:case D__rwQdq:
	if(op->mode==OP_Register)
	{
		if(op->reg_type==OP_MMXRegister)
		{
			pasm_info->pmodr_m->mod=3;
			pasm_info->pmodr_m->r_m=op->reg.reg_index;
			return 0;
		}
	}
	else if(op->mode==OP_Address)
	{
		return ModeAddress(pasm_info,op,-1);
	}
	break;
case D__Wq:case  D__wWq:case  D__rWq:case  D__rwWq:
case D__Wsd:case D__wWsd:case D__rWsd:case D__rwWsd:
case D__Wdq:case D__rWdq:case D__wWdq:case D__rwWdq:
case D__Wpd:case D__wWpd:case D__rWpd:case D__rwWpd:
case D__Wps:case D__wWps:case D__rWps:case D__rwWps:
case D__Wss:case D__wWss:case D__rWss:case D__rwWss:
	if(op->mode==OP_Register)
	{
		if(op->reg_type==OP_XMMRegister)
		{
			pasm_info->pmodr_m->mod=3;
			pasm_info->pmodr_m->r_m=op->reg.reg_index;
			return 0;
		}
	}
	else if(op->mode==OP_Address)
	{
		return ModeAddress(pasm_info,op,-1);
	}
	
	break;

case D__Vq:case  D__wVq: case D__rVq: case D__rwVq:
case D__Vpd:case D__rVpd:case D__wVpd:case D__rwVpd:
case D__Vdq:case D__rVdq:case D__wVdq:case D__rwVdq:
case D__Vsd:case D__wVsd:case D__rVsd:case D__rwVsd:
case D__Vps:case D__wVps:case D__rVps:case D__rwVps:
case D__Vss:case D__wVss:case D__rVss:case D__rwVss:
	if(op->mode==OP_Register && op->reg_type==OP_XMMRegister)
	{
		pasm_info->pmodr_m->reg=op->reg.reg_index;
		return 0;
	}	
	break;
case D__Ups:case D__wUps:case D__rUps:case D__rwUps:
case D__Upd:case D__wUpd:case D__rUpd:case D__rwUpd:
case D__Uq: case D__wUq: case D__rUq: case D__rwUq:
case D__Udq:case D__wUdq:case D__rUdq:case D__rwUdq:
	if(op->mode==OP_Register && op->reg_type==OP_XMMRegister)
	{
		pasm_info->pmodr_m->r_m=op->reg.reg_index;
		pasm_info->pmodr_m->mod=3;
		return 0;
	}	
	break;
case D__Nq:case D__wNq:case D__rNq:case D__rwNq:
	if(op->mode==OP_Register && op->reg_type==OP_MMXRegister)
	{
		pasm_info->pmodr_m->r_m=op->reg.reg_index;
		pasm_info->pmodr_m->mod=3;
		return 0;
	}
	break;

case D__AL:			// Specifying AL register
case D__CL:			// Specifying CL register
case D__DL:			// Specifying DL register
case D__BL:			// Specifying BL register
case D__AH:			// Specifying AH register
case D__CH:			// Specifying CH register
case D__DH:			// Specifying DH register
case D__BH:			// Specifying BH register
			if  (op->mode==OP_Register&& op->opersize==SIZE_b&& op->reg.reg_index==opdata-D__AL) 
				return 0;
			
			break;

case D__AX:			// Specifying AX register
case D__CX:			// Specifying CX register
case D__DX:			// Specifying DX register
case D__BX:			// Specifying BX register
case D__SP:			// Specifying SP register
case D__BP:			// Specifying BP register
case D__SI:			// Specifying SI register
case D__DI:			// Specifying DI register
			if  (op->mode==OP_Register&& op->opersize==SIZE_w&& op->reg.reg_index==opdata-D__AX) 
				 return 0;
			
			break;

case D__eAX:			// Specifying eAX register
case D__eCX:			// Specifying eCX register
case D__eDX:			// Specifying eDX register
case D__eBX:			// Specifying eBX register
case D__eSP:			// Specifying eSP register
case D__eBP:			// Specifying eBP register
case D__eSI:			// Specifying eSI register
case D__eDI:			// Specifying eDI register
			if  (op->mode==OP_Register&&(op->opersize==SIZE_w||op->opersize==SIZE_d)&&op->reg.reg_index==opdata-D__eAX)
			{
				pasm_info->OperandSize = op->opersize;
				return 0;
			}
			
			break;

case D__ES:			// Specifying ES register
case D__CS:			// Specifying CS register
case D__SS:			// Specifying SS register
case D__DS:			// Specifying DS register
case D__FS:			// Specifying FS register
case D__GS:			// Specifying GS register
			if  (op->mode==OP_Segment&&	op->opersize==SIZE_w&&op->sreg.sreg_index==opdata-D__ES) 
				return 0;
			
			break;
case D__Xb:
			if (op->mode==OP_Invalid&&	pasm_info->NameSize==SIZE_b) 
				return 0;
			
			break;

case D__Xv:		// Used for ( MOVS: LODS: OUTS: ... )
			if (op->mode==OP_Invalid&&	(pasm_info->NameSize ==SIZE_w||	pasm_info->NameSize ==SIZE_d))
			{
				pasm_info->OperandSize = pasm_info->NameSize;
				return 0;
			}
			
			break;

case D_DBYTE:
			if (op->mode==OP_Immed&&(op->immed.immed_value<=0xff||	op->immed.immed_value>=0xffffff80))
			{
				pasm_info->InstLength --;
				PutCode_b(pasm_info,(BYTE)op->immed.immed_value);
				return 0;
			}
			
			break;

case D_DWORD:
			if (op->mode==OP_Immed&&(op->immed.immed_value<=0xffff||op->immed.immed_value>=0xffff8000))
			{
				pasm_info->InstLength --;
				PutCode_w(pasm_info,(WORD)op->immed.immed_value);
				return 0;
			}
			
			break;

case D_DDWORD:
			if (op->mode==OP_Immed)
			{
				pasm_info->InstLength --;
				PutCode_d(pasm_info,(DWORD)op->immed.immed_value);
				return 0;
			}
			
			break;

case D_STRING:
			if (op->mode==OP_String)
			{
				pasm_info->InstLength --;
				for (i=0;op->string[i]!='\0';i++,pasm_info->InstLength++)
					*(BYTE*)&pasm_info->CodeBuff[pasm_info->InstLength]=(BYTE)(op->string[i]);
				return 0;
			}

default:
			if  (op->mode==OP_Invalid) 
				return 0;
			
			break;
};

	return 1;
}

DWORD ProcessAsmInfo(ASSEMBLY_INFOMATION *pasm_info,
							int OpcodeType,
							char *name,
							int Opdata1,
							int Opdata2,
							int Opdata3)

{
	if (pasm_info->CodeMode==BIT32)
	{
		pasm_info->OperandSize = 4;
		pasm_info->AddressSize = 4;
	}
	else
	{
		pasm_info->OperandSize = 2;
		pasm_info->AddressSize = 2;
	}

	if (OpcodeType != pasm_info->OpcodeType) 
		return 1;
	
	if (ProcessOpdata_asm(pasm_info,Opdata1,&pasm_info->op[0])!=0) 
		return 1;

	if (ProcessOpdata_asm(pasm_info,Opdata2,&pasm_info->op[1])!=0) 
		return 1;
	
	if (ProcessOpdata_asm(pasm_info,Opdata3,&pasm_info->op[2])!=0) 
		return 1;

	if (pasm_info->OpcodeType == C_INT&&pasm_info->op[0].immed.immed_value==0x03)
	{
		pasm_info->InstLength -= 2;
		PutCode_b(pasm_info,0xcc);
	}
	return 0;
}


int ProcessGroup(ASSEMBLY_INFOMATION *pasm_info,DIS_OPCODE_T * pG,DIS_OPCODE_T * inst)
{
	int i,j;
	DWORD value;
	int  OldInstSize;
	j=C_CALL;
	
	OldInstSize = pasm_info->InstLength;

	for (i=0;i<0x08;i++)
	{
		pasm_info->InstLength = OldInstSize;
		pasm_info->pmodr_m->reg = (BYTE)i;
		DWORD	Opdata1 = inst->Opdata1;
		DWORD	Opdata2 = inst->Opdata2;
		DWORD	Opdata3 = inst->Opdata3;
		if (pG[i].Opdata1 != D__NONE)
			Opdata1 = pG[i].Opdata1;
		if (pG[i].Opdata2 != D__NONE)
			Opdata2 = pG[i].Opdata2;
		if (pG[i].Opdata3 != D__NONE)
			Opdata3 = pG[i].Opdata3;
		value =	ProcessAsmInfo(pasm_info,
											pG[i].OpcodeType,
											pG[i].name,
											Opdata1,
											Opdata2,
											Opdata3);
        if (value == 0) 
			return 0;

	}

	return 1;
}


typedef TList<unsigned char*> ASSEMBLE_LIST;
int AssemblerInstruction(ASSEMBLY_INFOMATION *pasm_info,NAME_OPCODE_MAP& pmap,int prefixlength,ASSEMBLE_LIST* plist)
{
	int i,value;
	int OldInstSize;
	CIStrA strname;
	NAME_OPCODE_MAP::IT FindIT;
	DIS_OPCODE_T * pOpcode;
	pasm_info->InstLength = prefixlength;
	OldInstSize=pasm_info->InstLength;
	strname=pasm_info->Name;
	FindIT = pmap.Find(strname);
	
	for(;FindIT!=pmap.End();FindIT++)
	{
		pOpcode=*FindIT;
		if(pOpcode->OpcodeType!=pasm_info->OpcodeType)
			continue;
		pasm_info->InstLength=OldInstSize;
		BYTE*opbyte = (BYTE*)&pOpcode->opbyte;

		for(i=0;i<((pOpcode->opbytelen)&0xff);i++)
		{
			PutCode_b(pasm_info,opbyte[i]);

		}
		pasm_info->pmodr_m=(DIS_MODR_M*)&pasm_info->CodeBuff[pasm_info->InstLength];
		if(pOpcode->Attr&R_M)
			pasm_info->InstLength+=1;
		switch(pOpcode->opbytelen & 0xff00)
		{
		case C_GROUP_0_TYPE:
			pasm_info->pmodr_m->reg=((pOpcode->opbytelen>>16)&7);
			break;
		case C_GROUP_1_TYPE:
			pasm_info->pmodr_m->reg=((pOpcode->opbytelen>>16)&7);
			if((pOpcode->opbytelen>>16)&8)
				pasm_info->pmodr_m->mod=3;
			break;
		case C_GROUP_2_TYPE:
			pasm_info->pmodr_m->reg=((pOpcode->opbytelen>>16)&7);
			if((pOpcode->opbytelen>>16)>=8)
			{
				int opbytelen=(pOpcode->opbytelen>>16)-8;
				pasm_info->pmodr_m->mod=3;
				pasm_info->pmodr_m->reg=((opbytelen>>3)&7);
				pasm_info->pmodr_m->r_m=(opbytelen&7);
			}
			break;
		case C_GROUP_3_TYPE:
			break;
		case C_GROUP_4_TYPE:
			break;
		case C_GROUP_5_TYPE:
			pasm_info->pmodr_m->reg=((pOpcode->opbytelen>>16)&7);
			break;
		case C_ESC_GROUP_TYPE:
			pasm_info->pmodr_m->reg=((pOpcode->opbytelen>>16)&7);
			break;
		}
		
		value = ProcessAsmInfo(pasm_info,
			pOpcode->OpcodeType,
			pOpcode->name,
			pOpcode->Opdata1,
			pOpcode->Opdata2,
			pOpcode->Opdata3);
		if (value == 0) 
		{
			if((pOpcode->opbytelen & 0xff00)==C_GROUP_3DNOW_TYPE)
			{
				PutCode_b(pasm_info,(pOpcode->opbytelen>>16));
			}
			if(plist)
			{
				unsigned char * pcode = new unsigned char[pasm_info->InstLength+1];
				if(pcode)
				{
					pcode[0]=(unsigned char)pasm_info->InstLength;
					memcpy(pcode+1,pasm_info->CodeBuff,pasm_info->InstLength);
					plist->Append(pcode);
				}
			}
			else
				return 0;
		}
	}
	if(plist)
		return plist->Count()?0:1;
	return 1;
}


int ProcessAssemberLanguage(const char *pasm,char *OutBuff)//预先处理掉多余的空格或TAB字符
{	
	int i,j;

	char tempbuff[0x200];

	strcpy(tempbuff,pasm);

	for (i=0;tempbuff[i]!='\0';i++) tempbuff[i]=UPPER_CHAR(tempbuff[i]);//字符变成 大写字符

	for (i--;i>=0 && (tempbuff[i]==' ' || tempbuff[i]=='\t');i--) 
		tempbuff[i] = '\0';//去掉行尾的空格或TAB字符
	
	for (i=0;(tempbuff[i]==' '|| tempbuff[i]=='\t');i++);//去掉行首的空格或TAB字符

	for (j=0;tempbuff[i]!='\0';i++,j++)
	{
		if (tempbuff[i]==' '||tempbuff[i]=='\t')
			for ( ;tempbuff[i+1]==' '||tempbuff[i+1]=='\t';i++);//连续的空格 只保留一个其他的都去掉
		
		if (tempbuff[i]==' '||tempbuff[i]=='\t')  
		{
			switch (tempbuff[i+1])//如果是 空格后面跟以下字符，这把空格或 TAB 字符也去掉
			{
			case '+':
			case '-':
			case '*':
			case ',':
			case ']':
				i++;
				break;
			}
		}

		switch(tempbuff[i])
		{
		case '[':
		case ']':
		case '+':
		case '-':
		case '*':
		case ',':
		case ':':
			OutBuff[j]=tempbuff[i];
			for ( ;tempbuff[i+1]==' '||tempbuff[i+1]=='\t';i++);//去掉以上字符后面跟随的空格或 TAB 字符
			break;
		default :
			OutBuff[j]=tempbuff[i];
			break;
		}
	}

	OutBuff[j]='\0';

	return j;
}	

int InsertGroupMap(DIS_OPCODE_T* pOpcodeTable,int num,NAME_OPCODE_MAP& NameOpcodeMap)
{
	DIS_OPCODE_T* pOpcode;
	int i = 0;
	for(i=0;i<num;i++)
	{
		switch(pOpcodeTable[i].OpcodeType)
		{
		case C_NULL:
			break;
		case C_ESC:
			InsertGroupMap((DIS_OPCODE_T*)pOpcodeTable[i].name,72,NameOpcodeMap);

			break;
		case C_GRP:
			pOpcode=(DIS_OPCODE_T*)pOpcodeTable[i].name;
			InsertGroupMap((DIS_OPCODE_T*)pOpcodeTable[i].name,8,NameOpcodeMap);
			for(int j=0;j<8;j++)
			{
				if(pOpcode[j].OpcodeType==C_NULL)
					continue;
				if((pOpcode[j].opbytelen&0xff00)!=C_GROUP_0_TYPE)
					break;
				if((pOpcode[j].opbytelen>>16)!=j)
					break;
			}
			break;
		case C_GRP1:
			pOpcode=(DIS_OPCODE_T*)pOpcodeTable[i].name;

			InsertGroupMap((DIS_OPCODE_T*)pOpcodeTable[i].name,16,NameOpcodeMap);
			for(int j=0;j<16;j++)
			{
				if(pOpcode[j].OpcodeType==C_NULL)
					continue;
				if((pOpcode[j].opbytelen&0xff00)!=C_GROUP_1_TYPE)
					break;
				if((pOpcode[j].opbytelen>>16)!=j)
					break;
			}

			break;;
		case C_GRP2:
			pOpcode=(DIS_OPCODE_T*)pOpcodeTable[i].name;

			InsertGroupMap((DIS_OPCODE_T*)pOpcodeTable[i].name,72,NameOpcodeMap);

			for(int j=0;j<72;j++)
			{
				if(pOpcode[j].OpcodeType==C_NULL)
					continue;
				if((pOpcode[j].opbytelen&0xff00)!=C_GROUP_2_TYPE)
					break;
				if((pOpcode[j].opbytelen>>16)!=j)
					break;
			}

			break;
		case C_GRP3:
			pOpcode=(DIS_OPCODE_T*)pOpcodeTable[i].name;

			InsertGroupMap((DIS_OPCODE_T*)pOpcodeTable[i].name,4,NameOpcodeMap);

			for(int j=0;j<4;j++)
			{
				if(pOpcode[j].OpcodeType==C_NULL)
					continue;
				if((pOpcode[j].opbytelen&0xff00)!=C_GROUP_3_TYPE)
					break;
				
			}

			break;
		case C_GRP4:
			pOpcode=(DIS_OPCODE_T*)pOpcodeTable[i].name;

			InsertGroupMap((DIS_OPCODE_T*)pOpcodeTable[i].name,8,NameOpcodeMap);

			for(int j=0;j<8;j++)
			{
				if(pOpcode[j].OpcodeType==C_NULL)
					continue;
				if((pOpcode[j].opbytelen&0xff00)!=C_GROUP_4_TYPE)
					break;
				if((pOpcode[j].opbytelen>>16)!=j)
					break;

			}

			break;
		case C_GRP5:
			pOpcode=(DIS_OPCODE_T*)pOpcodeTable[i].name;
			InsertGroupMap((DIS_OPCODE_T*)pOpcodeTable[i].name,8,NameOpcodeMap);
			for(int j=0;j<8;j++)
			{
				if(pOpcode[j].OpcodeType==C_NULL)
					continue;
				if(pOpcode[j].OpcodeType==C_GRP3)
				{
					InsertGroupMap((DIS_OPCODE_T*)pOpcodeTable[i].name,4,NameOpcodeMap);
				}
			}
			break;
		case C_2BYTE:
			InsertGroupMap((DIS_OPCODE_T*)pOpcodeTable[i].name,256,NameOpcodeMap);
			break;
		case C_3BYTE_0X3A:
			InsertGroupMap((DIS_OPCODE_T*)pOpcodeTable[i].name,256,NameOpcodeMap);
			break;
		case C_3BYTE_0X38:
			InsertGroupMap((DIS_OPCODE_T*)pOpcodeTable[i].name,256,NameOpcodeMap);
			break;
		default:
			if(pOpcodeTable[i].name==NULL || pOpcodeTable[i].name[0]==0)
				break;
			if(TStrICmp("cvtsi2sd",pOpcodeTable[i].name)==0)
				if(pOpcodeTable[i].name==NULL || pOpcodeTable[i].name[0]==0)
					break;
			NameOpcodeMap.InsertEqual(pOpcodeTable[i].name,pOpcodeTable+i);
		}
	}
	return 0;
}
int InitAssembler(NAME_OPCODE_MAP& NameOpcodeMap)
{
	InsertGroupMap(Group_main,sizeof(Group_main)/sizeof(Group_main[0]),NameOpcodeMap);
	InsertGroupMap(Group0x0f0f,sizeof(Group0x0f0f)/sizeof(Group0x0f0f[0]),NameOpcodeMap);

	return 0;
}
NAME_OPCODE_MAP* gpNameOpcodeMap=NULL;
int Assembler(const char *pasm,BYTE *outcode,DWORD eip,int mode)
{
	int i,j,k;
	char tempbuffer[0x80];
	unsigned char MachineCodeBuffer[0x20];
	char InstructionName[0x80];
	char PX[4][0x80];
	ASSEMBLY_INFOMATION asm_info,*pasm_info;
	NAME_OPCODE_MAP::IT bit;
	if(gpNameOpcodeMap==NULL)
	{
		gpNameOpcodeMap=new NAME_OPCODE_MAP;
	}
	if(gpNameOpcodeMap==NULL)
		return 0;
	NAME_OPCODE_MAP &NameOpcodeMap=*gpNameOpcodeMap;
	if(NameOpcodeMap.Count()==0)
		InitAssembler(NameOpcodeMap);
	k=NameOpcodeMap.Count();
	pasm_info = &asm_info;
	memset(pasm_info,0x00,sizeof(ASSEMBLY_INFOMATION));
	memset(MachineCodeBuffer,0,sizeof(MachineCodeBuffer));
	pasm_info->CodeBuff = &MachineCodeBuffer[0x10];
	pasm_info->eip = eip;
	pasm_info->CodeMode = mode;
	i = ProcessAssemberLanguage(pasm,tempbuffer);//预先处理掉多余空格或TAB字符
	if(i<2)
	{
		pasm_info->error.name = 1;
		return 0; 
	}
	i=0;

	for (k=0;k<sizeof(LockRepxx)/sizeof(LockRepxx[0]);k++)//处理前缀
	{
		for (j=0;tempbuffer[i+j] == LockRepxx[k].Name[j];j++);
		
		if (LockRepxx[k].Name[j] == 0) 
		{
			if (LockRepxx[k].Code == 0xf0) 
				pasm_info->Lock = LockRepxx[k].Code;
			else 
				pasm_info->Repeat = LockRepxx[k].Code;
			i=i+j;
			break;
		}
	}

	for(j=0;(tempbuffer[i]>='A' && tempbuffer[i] <='Z') || (tempbuffer[i]>='0' && tempbuffer[i] <='9') || tempbuffer[i]=='_';j++,i++)
		InstructionName[j]=tempbuffer[i];
	InstructionName[j]='\0';
	pasm_info->Name = InstructionName;
	bit = NameOpcodeMap.Find(InstructionName);
	if(bit==NameOpcodeMap.End())
	{
		pasm_info->error.name = 1;
		return 0;
	}
	pasm_info->OpcodeType = (*bit)->OpcodeType;
	DIS_OPCODE_T* pTmp=(*bit);
	for ( ;tempbuffer[i]==' '||tempbuffer[i]==',';i++ );

	for (k=0;k<=3;k++)
	{
		for (j=0;tempbuffer[i]!=','&&tempbuffer[i]!='\0';i++,j++)	//分离出3个参数
			PX[k][j]=tempbuffer[i];
		PX[k][j]='\0';
		if (tempbuffer[i]==',') 
			i++;
	}
	pTmp=NULL;
	if (PX[3][0]!='\0') 
	{
		pasm_info->error.P4 = 1;
		return 0;
	}

	for (k=0;k<3;k++)
	{
		if (ProcessParameter(PX[k],&pasm_info->op[k]))
		{
			switch(k)
			{
			case 0:
				pasm_info->error.P1=1;
				break;
			case 1:
				pasm_info->error.P1=1;
				break;
			case 2:
				pasm_info->error.P1=1;
				break;
			default :
				break;
			};
			return 0;
		}
	}

	i=0;
	for (k=0;k<3;k++)
		if (pasm_info->op[k].mode==OP_Register||pasm_info->op[k].mode==OP_Segment)
			i=pasm_info->op[k].opersize;

	for (k=0;k<3;k++)
		if (pasm_info->op[k].mode==OP_Address&&	pasm_info->op[k].opersize!=0)
			i=pasm_info->op[k].opersize;

	for (k=0;k<3;k++)
		if (pasm_info->op[k].mode==OP_Immed&&pasm_info->op[k].opersize!=0)
			i=pasm_info->op[k].opersize;
		
	for (k=0;k<3;k++)
		if (pasm_info->op[k].mode==OP_Address&&	pasm_info->op[k].opersize==0)
			pasm_info->op[k].opersize=i;

	for (k=0;k<3;k++)
		if (pasm_info->op[k].mode==OP_Immed&&pasm_info->op[k].opersize==0)
			pasm_info->op[k].opersize=i;

	i=0;	
	ASSEMBLE_LIST pList;
	if (AssemblerInstruction(pasm_info,NameOpcodeMap,0,NULL)!=0) 
	{
		pasm_info->error.PX = 1;
		return 0;
	}
	ASSEMBLE_LIST::IT lbit,leit;
	for(lbit=pList.Begin();lbit!=pList.End();lbit++)
	{
		unsigned char* pstr=*lbit;
		//for(int i =0;i<pstr[0];i++)
		//	printf("%02x ",pstr[1+i]);
		delete []pstr;
	}
	pList.Clear();
	pasm_info->PrefixLength = 0;
	
	if (pasm_info->Lock == 0xf0 )
	{
		pasm_info->CodeBuff--;
		pasm_info->PrefixLength++;
		*pasm_info->CodeBuff=0xf0;
	}

	if (pasm_info->Repeat != 0)
	{
		pasm_info->CodeBuff--;
		pasm_info->PrefixLength++;
		*pasm_info->CodeBuff = pasm_info->Repeat;
	}

	int codesize;

	if (pasm_info->CodeMode==BIT32) codesize = 4;
	else codesize = 2;

	if (pasm_info->AddressSize!=codesize) 
	{
		pasm_info->CodeBuff--;
		pasm_info->PrefixLength++;
		*pasm_info->CodeBuff=0x67;
	}
	
	if (pasm_info->OperandSize!=codesize) 
	{
		pasm_info->CodeBuff--;
		pasm_info->PrefixLength++;
		*pasm_info->CodeBuff=0x66;
	}
	
	if (pasm_info->SegmentPrefix != 0) 
	{
		pasm_info->CodeBuff--;
		pasm_info->PrefixLength++;
		*pasm_info->CodeBuff=pasm_info->SegmentPrefix;
	}
	
	k = pasm_info->InstLength+pasm_info->PrefixLength;

	for (i=0;i<k;i++)
		outcode[i]=pasm_info->CodeBuff[i];
	 
	return k;
}

//——————————————正汇编模块————————————————
//

int Disassembler(char *OutBuff,BYTE *InBuff,DWORD EIP,int Mode,int U_x1,int U_x2)
{
	INSTRUCTION_INFORMATION InstInfo;

	InstInfo.pasm = OutBuff;
	InstInfo.U_x1 = U_x1;
	InstInfo.U_x2 = U_x2;
	DIS_CPU DispCpu;

	return Disassembly(&InstInfo,InBuff,EIP,Mode,&DispCpu);
}

char ** GetIntelConstName(int *pNumb)
{
	int i;

	static int NameNumb=0;

	if (NameNumb==0)
	{
		i=sizeof(Group_main)/sizeof(Group_main[0]);
		ReadIntelName((char*)Group_main,i);
		for (i=0;Emblem[i]!=NULL;i++)
			NameNumb = i;
	}

	if (pNumb!=NULL)
	{
		*pNumb = NameNumb;
	}
	return Emblem;
}

bool IsJmp(unsigned short pCode,DWORD Eflags)
{
	switch(pCode)
	{
	case 0xf80:
	case 0x70:
		return (Eflags&EFLAGS_OF_MASK) != 0;
	case 0xf81:
	case 0x71:
		return (Eflags&EFLAGS_OF_MASK) == 0;
	case 0xf82:
	case 0x72:
		return (Eflags&EFLAGS_CF_MASK) != 0;
	case 0xf83:
	case 0x73:
		return (Eflags&EFLAGS_CF_MASK) == 0;
	case 0xf84:
	case 0x74:
		return (Eflags&EFLAGS_ZF_MASK) != 0;
	case 0xf85:
	case 0x75:
		return (Eflags&EFLAGS_ZF_MASK) == 0;
	case 0xf86:
	case 0x76:
		return ((Eflags&EFLAGS_ZF_MASK) != 0)&&((Eflags&EFLAGS_CF_MASK) != 0);
	case 0xf87:
	case 0x77:
		return ((Eflags&EFLAGS_ZF_MASK) == 0)&&((Eflags&EFLAGS_CF_MASK) == 0);
	case 0xf88:
	case 0x78:
		return (Eflags&EFLAGS_SF_MASK) != 0;
	case 0xf89:
	case 0x79:
		return (Eflags&EFLAGS_SF_MASK) == 0;
	case 0xf8a:
	case 0x7a:
		return (Eflags&EFLAGS_PF_MASK) != 0;
	case 0xf8b:
	case 0x7b:
		return (Eflags&EFLAGS_PF_MASK) == 0;
	case 0xf8c:
	case 0x7c:
		return (Eflags & EFLAGS_OF_MASK)>>EFLAGS_OF_SHIFT != (Eflags & EFLAGS_SF_MASK)>>EFLAGS_SF_SHIFT;
	case 0xf8d:
	case 0x7d:
		return (Eflags & EFLAGS_OF_MASK)>>EFLAGS_OF_SHIFT == (Eflags & EFLAGS_SF_MASK)>>EFLAGS_SF_SHIFT;
	case 0xf8e:
	case 0x7e:
		return ((Eflags & EFLAGS_OF_MASK)>>EFLAGS_OF_SHIFT != (Eflags & EFLAGS_SF_MASK)>>EFLAGS_SF_SHIFT) && (Eflags&EFLAGS_ZF_MASK) != 0;
	case 0xf8f:
	case 0x7f:
		return ((Eflags & EFLAGS_OF_MASK)>>EFLAGS_OF_SHIFT == (Eflags & EFLAGS_SF_MASK)>>EFLAGS_SF_SHIFT) && (Eflags&EFLAGS_ZF_MASK) == 0;
	}
	return false;
}
int CIntelDisassembler::GetLength(BYTE *InBuff,int Mode)
{
	return ::Disassembler(NULL,InBuff,0x100,Mode);
}

char ** CIntelDisassembler::GetIntelConstName(int *pNumb)
{
	return ::GetIntelConstName(pNumb);
}

int CIntelDisassembler::Disassembler(INSTRUCTION_INFORMATION *pInstInfo,DIS_CPU *dis_cpu)
{
	int mode;
	DWORD eip;
	BYTE *inbuff;

	mode = m_Mode;

	pInstInfo->CodeMode = mode;
	eip = pInstInfo->eip;
	inbuff = pInstInfo->CodeBuff;

	pInstInfo->U_x1 = m_U_x1;
	pInstInfo->U_x2 = m_U_x2;

	return ::Disassembly(pInstInfo,inbuff,eip,mode,dis_cpu);
}

int CIntelDisassembler::Assembler(const char *InBuff,BYTE *OutCode,DWORD EIP,int Mode)
{
	return ::Assembler(InBuff,OutCode,EIP,Mode);
}
