#include "StdAfx.h"
#include "Syser.h"
#include "DebugCmd.h"
#include "InterruptPatch.h"
const WCHAR cmd_a_usage[]=
{
	L"a: Modify memory by assemble code\n"
	L"Format: a address asm_string\n"
	L"Example1: a 401000 inc eax\n"
	L"Example2: a EIP mov eax,ebx\n"
};

const WCHAR cmd_bc_usage[]=
{
	L"bc: Clear breakpoint\n"
	L"Format: bc address_or_index[*]\n"
	L"Example1: bc *\n"
	L"Example2: bc 1\n"
	L"Example3: bc 401000\n"
};

const WCHAR cmd_bd_usage[]=
{
	L"bd: Disable breakpoint\n"
	L"Format: bd address_or_index[*]\n"
	L"Example1: bd *\n"
	L"Example2: bd 1\n"
	L"Example3: bd 401000\n"
};

const WCHAR cmd_be_usage[]=
{
	L"be: Enable breakpoint\n"
	L"Format: be address_or_index[*]\n"
	L"Example1: be *\n"
	L"Example2: be 1\n"
	L"Example3: be 401000\n"
};


const WCHAR cmd_bl_usage[]=
{
	L"bl: List breakpoint\n"
	L"Format: bl\n"
	L"Example1: bl\n"
};


const WCHAR cmd_bpx_usage[]=
{
	L"bpx: Set breakpoint\n"
	L"Format: bpx address [if condition_string] [do command_string]\n"
	L"Example1: bpx 401000 EAX==0302\n"
	L"Example2: bpx MessageBoxA\n"
	L"Example3: bpx 402000 rw if (*esi)&FF==0 do d eip\n"
};

const WCHAR cmd_bpload_usage[]=
{
	L"bpload: Set module loading breakpoint \n"
	L"Format: bpload module_name\n"
	L"Example1: bpload kernel32\n"
	L"Example2: bpload user32.dll\n"
};

const WCHAR cmd_bpmx_usage[]=
{
	L"bpm,bpmw,bpmd: Set data access breakpoint\n"
	L"Format: bpm address [rw,w,x] [if condition_string] [do command_string]\n"
	L"Example1: bpm 401000 w\n"
	L"Example2: bpmw 401000 rw       (set word access breakpoint)\n"
	L"Example3: bpm esi w if *eax==00 do d esi;bc *\n"
};

const WCHAR cmd_bpio_usage[]=
{
	L"bpio: Set a breakpoint on an I/O Port access\n"
	L"Format: bpio I/O_port [r,w,rw] [if condition_string] [do command_string]\n"
	L"Example1: bpio 3E8 rw\n"
	L"Example2: bpio 2E4 rw if eax==0 do dd esi\n"
};

const WCHAR cmd_ex_usage[]=
{
	L"e,eb,ew,ed:  Edit memory\n"
	L"Format: e address data_value\n"
	L"Example1: e 403000 00,01,02,04\n"
	L"Example2: e ESI \"Hello\"\n"
	L"Example3: eb 401000 10\n"
	L"Example4: ew 401000 2030\n"
	L"Example5: ed 401000 40506070\n"
};


const WCHAR cmd_u_usage[]=
{
	L"u: Unassemble instructions\n"
	L"Format: u address\n"
	L"Exapmle1: u 401000\n"
	L"Exapmle2: u eip+1000\n"
	L"Example3: u +\n"
	L"Example4: u -\n"
	L"Example5: u + offset\n"
	L"Example6: u - offset\n"
	L"Example6: u -a address\n"

};


const WCHAR cmd_dot_usage[]=
{
	L".: Locate EIP instruction in Code View (== u eip)\n"
	L"Format: .\n"
};


const WCHAR cmd_src_usage[]=
{
	L"src: Locate address in Source Code File\n"
	L"Format: src [address]\n"
	L"Example1: src (==src EIP)\n"
	L"Example2: src 401000\n"
};


const WCHAR cmd_seg_usage[]=
{
	L"seg: Display segment information\n"
	L"Format: seg segment_register_name\n"
	L"Example1: seg cs\n"
	L"Example2: seg 08\n"
};

const WCHAR cmd_p_usage[]=
{
	L"p: Execute one program step (skip CALL,REP )\n"
	L"Format: p [step count] [condition] [ret]\n"
	L"Example1: p 100                       (run 100 p steps)\n"
	L"Example2: p EIP<401000 && EIP>402000  (break EIP jump out of 401000 - 402000)\n"
	L"Example3: p ret                       (stop at return)\n"
};

const WCHAR cmd_sp_usage[]=
{
	L"sp: Execute one source code step\n"
	L"Format: sp\n"
	L"Example1: sp\n"
};

const WCHAR cmd_go_usage[]=
{
	L"go : set one-time breakpoint at specify address\n"
	L"Format: go address\n"
	L"Example1: go EIP+20\n"
	L"Example2: go 402000\n"
};

const WCHAR cmd_t_usage[]=
{
	L"t: Trace one instruction\n"
	L"Format: t [step count] [condition]\n"
	L"Example1: t 100                       (run 100 t steps)\n"
	L"Example2: t EIP<401000 && EIP>402000  (break EIP jump out of 401000 - 402000)\n"
};

const WCHAR cmd_st_usage[]=
{
	L"st: Trace one source code line\n"
	L"Format: st\n"
	L"Example1: st\n"
};

const WCHAR cmd_x_usage[]=
{
	L"x: exit debugger (continue)\n"
	L"format: x\n"
};

const WCHAR cmd_fill_usage[]=
{
	L"f: Fill memory\n"
	L"Format: f address length data_string\n"
	L"Example1: f esi 4 80001000\n"
	L"Example2: f 401000 5 E9,00,00,00,10\n"
	L"Example3: f 401000 1000 \"hello\"\n"
};


const WCHAR cmd_search_usage[]=
{
	L"s: Search memory\n"
	L"Format: s address length data_string\n"
	L"Example1: s 401000 1000 \"CreateFileA\"\n"
	L"Example2: s EIP 2000 FF,15,00,00,10,40\n"
	L"Example3: s           (continue last search operation)\n"
};


const WCHAR cmd_stack_usage[]=
{
	L"stack: Display call stack\n"
	L"Format: stack [call_frame_address]\n"
	L"Example1: stack             (analyse from ebp)\n"
	L"Example2: stack  124000     (analyse from 124000)\n"
};

const WCHAR cmd_cmt_usage[]=
{
	L"cmt: List module comment in current process\n"
	L"Format: cmt\n"
};

const WCHAR cmd_r_usage[]=
{
	L"r: Display/Change  Register Value\n"
	L"Format: r reg_name [value]\n"
	L"Example1: r eip 402000\n"
	L"Example2: r eax 80001000\n"
	L"Example3: r ah 10\n"
	L"Example4: r ebx\n"
};

const WCHAR cmd_m_usage[]=
{
	L"m: Move data\n"
	L"Format: m source_address length dest_address (length is HEX bytes)\n"
	L"Example1: m esi 100 edi\n"
	L"Example2: m 402000 E00 403000\n"
};

const WCHAR cmd_c_usage[]=
{
	L"c: Compare two data blocks\n"
	L"Format: c source_address length dest_address (length is HEX bytes)\n"
	L"Example1: c esi 100 edi\n"
	L"Example2: c 402000 E00 403000\n"
};

const WCHAR cmd_sym_usage[]=
{
	L"sym: List symbols\n"
	L"Format: sym [module_name] [symbol_wildcard] | -a symbol value\n"
	L"Example1: sym kernel32 *         (List all symbols of kernel32.dll)\n"
	L"Example2: sym CreateFile?        (List CreateFileA and CreateFileW)\n"
	L"Example3: sym -a mysymbol 4013af (Add owner labels)\n"
};

const WCHAR cmd_sdsmod_usage[]=
{
	L"sdsmod: List all syser symbol modules loaded\n"
	L"Format: sdsmod\n"
};


const WCHAR cmd_mod_usage[]=
{
	L"mod: List modules of current process\n"
	L"Format: mod [address][mod_name]\n"
	L"Example1: mod eip           (display module's name on current eip)\n"
	L"Example2: mod nt*           (display module's name fit to \"nt*\")\n"
};


/*
%<0>0 ------- Black
%<1>1 ------- White 
%<2>2 ------- Red
%<3>3 ------- Light Red
%<4>4 ------- Green
%<5>5 ------- Light Green
%<6>6 ------- Blue
%<7>7 ------- Light Blue
%<8>8 ------- Brown
%<9>9 ------- Light Brown
%<A>A ------- Cyan
%<B>B ------- Light Cyan
%<C>C ------- Gray
%<D>D ------- Light Gray
%<E>E ------- Yellow
%<F>F ------- Light Yellow
*/

SYSER_CMD_ENTRY	DebugCmdTable[]=
{
////////////////////////////////////////////////////////////////////////////////////////////
//break point
////////////////////////////////////////////////////////////////////////////////////////////
	{WSTR("bc"),		WSTR("Clear breakpoint"),					bc_command,			cmd_bc_usage},
	{WSTR("bl"),		WSTR("List breakpoints"),					bl_command,			cmd_bl_usage},
	{WSTR("bd"),		WSTR("Disable breakpoints"),				bd_command,			cmd_bd_usage},
	{WSTR("be"),		WSTR("Enable breakpoints"),					be_command,			cmd_be_usage},
	{WSTR("bpx"),		WSTR("Set breakpoint"),						bpx_command,		cmd_bpx_usage},
	{WSTR("bpload"),	WSTR("Set module loading breakpoint"),		bpload_command,		cmd_bpload_usage},
	{WSTR("bpm"),		WSTR("Breakpoint on memory access"),		bpm_command,		cmd_bpmx_usage},
	{WSTR("bpmb"),		WSTR("Breakpoint on memory access"),		bpm_command,		cmd_bpmx_usage},
	{WSTR("bpmw"),		WSTR("Breakpoint on memory access"),		bpm_command,		cmd_bpmx_usage},
	{WSTR("bpmd"),		WSTR("Breakpoint on memory access"),		bpm_command,		cmd_bpmx_usage},
	{WSTR("bpio"),		WSTR("Breakpoint on I/O port access"),		bpio_command,		cmd_bpio_usage},
////////////////////////////////////////////////////////////////////////////////////////////
//trace
////////////////////////////////////////////////////////////////////////////////////////////
	{WSTR("x"),			WSTR("Return to host and continue running"),exit_system_command,		cmd_x_usage},
	{WSTR("exit"),		WSTR("Return to host and continue running"),exit_system_command,		cmd_x_usage},
	{WSTR("g"),			WSTR("Go to address"),						go_command,					cmd_go_usage},
	{WSTR("t"),			WSTR("Trace one instruction"),				trace_command,				cmd_t_usage},
	{WSTR("st"),		WSTR("Trace one source code line"),			source_trace_command,		cmd_st_usage},
	{WSTR("tb"),		WSTR("Trace and break at next branch"),		trace_branch_command},
	{WSTR("p"),			WSTR("Execute one program step"),			p_command,					cmd_p_usage},
	{WSTR("sp"),		WSTR("Execute one source code step"),		source_proceed_command,		cmd_sp_usage},
	{WSTR("skip"),		WSTR("Skip current instruction"),			skip_command},
	{WSTR("stack"),		WSTR("Display call stack context"),			stack_command,				cmd_stack_usage},
////////////////////////////////////////////////////////////////////////////////////////////
//View
////////////////////////////////////////////////////////////////////////////////////////////
	{WSTR("u"),			WSTR("Unassemble instructions"),			u_command,					cmd_u_usage},
	{WSTR("."),			WSTR("Locate EIP instruction in Code View"),u_command,					cmd_dot_usage},
	{WSTR("src"),		WSTR("Locate address in Source Code File"),	src_command,				cmd_src_usage},
////////////////////////////////////////////////////////////////////////////////////////////
//Symbol
////////////////////////////////////////////////////////////////////////////////////////////
	{WSTR("sym"),		WSTR("List symbols"),						sym_command,				cmd_sym_usage},
	{WSTR("symmod"),	WSTR("Display all symbol modules"),			symmod_command},
	{WSTR("sdsmod"),	WSTR("Display all sds symbol modules"),		sdsmod_command,				cmd_sdsmod_usage},

	{WSTR("cmt"),		WSTR("List module comment in current process"),	cmt_command,			cmd_cmt_usage},
////////////////////////////////////////////////////////////////////////////////////////////
//Edit
////////////////////////////////////////////////////////////////////////////////////////////
	{WSTR("seg"),		WSTR("Display segment information"),		seg_command,				cmd_seg_usage},
	{WSTR("r"),			WSTR("Display/Change Register Value"),		r_command,					cmd_r_usage},
	{WSTR("m"),			WSTR("Move data"),							m_command,					cmd_m_usage},
	{WSTR("f"),			WSTR("Fill memory with data"),				f_command,					cmd_fill_usage},
	{WSTR("s"),			WSTR("Search binary data or string"),		s_command,					cmd_search_usage},
	{WSTR("sc"),		WSTR("Search binary data or string,show search resoult at code view"),		s_command,					cmd_search_usage},
	{WSTR("sd"),		WSTR("Search binary data or string,show search resoult at data view"),		s_command,					cmd_search_usage},
	{WSTR("c"),			WSTR("Compare two data blocks"),			c_command,					cmd_c_usage},
	{WSTR("a"),			WSTR("modify memory by assemble code"),		a_command,					cmd_a_usage},
	{WSTR("e"),			WSTR("Edit memory"),						e_command,					cmd_ex_usage},
	{WSTR("eb"),		WSTR("Edit memory (BYTE)"),					e_command,					cmd_ex_usage},
	{WSTR("ew"),		WSTR("Edit memory (WORD)"),					e_command,					cmd_ex_usage},
	{WSTR("ed"),		WSTR("Edit memory (DWORD)"),				e_command,					cmd_ex_usage},
////////////////////////////////////////////////////////////////////////////////////////////
	{WSTR("mod"),		WSTR("Display Modules"),					mod_command,				cmd_mod_usage},
	{WSTR("test"),		WSTR("test write memory command"),							test_command11},
#ifdef CODE_OS_WIN
	{WSTR("open"),		WSTR("open file"),							open_command},
	{WSTR("close"),		WSTR("close file"),							close_command},
	{WSTR("Reset"),		WSTR("reset debug state"),					reset_command},
#endif
////////////////////////////////////////////////////////////////////////////////////////////
	{NULL,NULL,NULL}
};

#ifdef CODE_OS_WIN
int open_command(int argc, WCHAR *argv[ ],PCWSTR szCommandLine, CSyser*pSyser)
{
	char szFileName[MAX_FN_LEN],*pszFileName;
	if(pSyser->m_pDebugger==NULL)
	{
		OUTPUT(WSTR("Error : please load debugger first !\n"));
		return 1;
	}
	if(pSyser->m_SyserUI.m_CodeDoc.IsOpened())
		pSyser->m_SyserUI.m_CodeDoc.Close();
	if(argc==1)
	{
		char szBuffer[MAX_FN_LEN],szFileName[MAX_FN_LEN];
		OPENFILENAME OpenFileName;
		STZeroMemory(OpenFileName);
		OpenFileName.lStructSize = sizeof(OPENFILENAME);
		OpenFileName.hInstance = gpSyser->m_hLocalInst;
		OpenFileName.hwndOwner = gpSyser->m_hLocalWnd;
		UnicodeToAnsi(gpSyser->m_szDbgFileNameFilter,szBuffer,sizeof(szBuffer));
		for(int n = TStrLen(szBuffer);n>=0;n--)
		{
			if(szBuffer[n]=='|')
				szBuffer[n]=0;
		}
		OpenFileName.lpstrFilter = szBuffer;
		OpenFileName.nMaxFile = sizeof(szFileName);
		OpenFileName.lpstrFile = szFileName;
		*szFileName = 0;
		gpSyser->LockTimer();
		if(GetOpenFileName(&OpenFileName)==false)
		{
			gpSyser->UnlockTimer();
			return true;
		}
		pszFileName = OpenFileName.lpstrFile;
		gpSyser->UnlockTimer();
	}
	else
	{
		UnicodeToAnsi(&szCommandLine[argv[1]-argv[0]],szFileName,MAX_FN_LEN);
		pszFileName = szFileName;
	}
	if(pSyser->m_SyserUI.m_CodeDoc.Open(pszFileName)==false)
	{
		OUTPUT(WSTR("Error : Fail to open %s !\n"),argv[1]);
		return 1;
	}
	return 0;
}

int close_command(int argc, WCHAR *argv[ ],PCWSTR szCommandLine, CSyser*pSyser)
{
	if(pSyser->m_SyserUI.m_CodeDoc.IsOpened()==false)
	{
		OUTPUT(WSTR("Error : please open file first !\n"));
		return 1;
	}
	pSyser->m_SyserUI.m_CodeDoc.Close();
	return 0;
}

int reset_command(int argc, WCHAR *argv[ ],PCWSTR szCommandLine, CSyser*pSyser)
{
	WCHAR OpenCmd[MAX_FN_LEN],FileName[MAX_FN_LEN];
	ASSERT_DEBUGGER_OPENED
	AnsiToUnicode(gpSyser->m_SyserUI.m_CodeDoc.m_MainModuleName,FileName,MAX_FN_LEN);
	RUNCMD(WSTR("close"));
	TSPrintf(OpenCmd,WSTR("open %s"),FileName);
	RUNCMD(OpenCmd);
	return 0;
}

#endif

int exit_system_command(int argc, WCHAR *argv[ ],PCWSTR szCommandLine, CSyser*pSyser)
{
	if(pSyser->m_pDebugger==NULL)
		return 0;
	pSyser->m_pDebugger->ContinueDebug();
	return 0;
}

int	go_command(int argc,WCHAR *argv[],PCWSTR szCommandLine,CSyser *pSyser)
{
	ULPOS Address;
	if(argc!=2)
	{
		OUTPUT_COMMAND_USAGE;
		return -1;
	}
	if(CALCEXP(argv[1],&Address)==false)
	{
		OUTPUT_INVALID_ADDRESS;
		return -1;
	}
	if(gpSyser->m_pDebugger->InsertCodeBP(Address,BP_TYPE_DEBUG,BP_STATE_ENABLE)==false)
	{
		OUTPUT(WSTR("Error : Fail to set breakpoint at %08X\n"),Address);
		return -1;
	}
	gpSyser->m_pDebugger->ContinueDebug();
	return 0;
}

int trace_branch_command(int argc, WCHAR *argv[ ],PCWSTR szCommandLine, CSyser*pSyser)
{
#ifdef CODE_OS_NT_DRV
	trace_command(1,argv,szCommandLine,pSyser);
	SetBranchStepRun();
#endif
	return 0;
}

bool IsStepFlagModifyCode(BYTE*CodeBuffer,DWORD dwEip,int* SkipInstLen,CSyser*pSyser)
{
	char buffer[200];
	INSTRUCTION_INFORMATION InstInfo;

	InstInfo.pasm = buffer;
	InstInfo.U_x1 = 6;
	InstInfo.U_x2 = 12;

#ifdef CODE_OS_NT_DRV
	DIS_CPU DispCpu;
	int nLen,nLen2;
	nLen=Disassembly(&InstInfo,CodeBuffer,dwEip,BIT32,&DispCpu);
	if(nLen)
	{
		if(InstInfo.OpCode==C_PUSHF||InstInfo.OpCode==C_POPF)
		{
			*SkipInstLen=nLen;
			return true;
		}

		if(TStrICmp(InstInfo.Name,"mov")==0 && InstInfo.op[0].mode==mode_segment && TStrICmp(InstInfo.op[0].string,"ss")==0)//mov ss,xx
		{
			if(gpSyser->m_pOrgProcess->ReadMemory(*X86_REG_PTR.pEIP+nLen,CodeBuffer,MAX_INSTR_LEN)==MAX_INSTR_LEN)
			{
				memset(&InstInfo,0,sizeof(InstInfo));
				nLen2=Disassembly(&InstInfo,CodeBuffer,dwEip+nLen,BIT32,&DispCpu);
				if(nLen2)
				{
					if(InstInfo.OpCode==C_PUSHF||InstInfo.OpCode==C_POPF)
					{
						*SkipInstLen=nLen+nLen2;
						return true;
					}
				}
				
			}
			return false;
		}
		if(TStrICmp(InstInfo.Name,"pop")==0 && InstInfo.op[0].mode==mode_segment && TStrICmp(InstInfo.op[0].string,"ss")==0)
		{		
			if(gpSyser->m_pOrgProcess->ReadMemory(*X86_REG_PTR.pEIP+nLen,CodeBuffer,MAX_INSTR_LEN)==MAX_INSTR_LEN)
			{
				memset(&InstInfo,0,sizeof(InstInfo));
				nLen2=Disassembly(&InstInfo,CodeBuffer,dwEip+nLen,BIT32,&DispCpu);
				if(nLen2)
				{
					if(InstInfo.OpCode==C_PUSHF||InstInfo.OpCode==C_POPF)
					{
						*SkipInstLen=nLen+nLen2;
						return true;
					}
				}
			}
			return false;
		}
		int index=0-1;
		switch(InstInfo.OpCode)
		{
		case C_INT1:
			index=1;
			break;
		case C_INT3:
			index=3;
			break;
		case C_INT:
			index=(int)InstInfo.op[0].immed.immed_value;
			index&=0xff;
			break;
		case C_INTO:
			if((Reg.EFlags & 0xf00))
				index=4;
			break;
		}
		if(index!=0-1)
		{
			DWORD IDTBase,IDTSize;
			DWORD IntAddress=0;
			PX86_GATE_DECR pDecr;
			IDTBase=SyserGetIDTBase(&IDTSize);
			pDecr = *(PX86_GATE_DECR*)&IDTBase;
			if(pDecr[index].P && ((pDecr[index].Type == SYS_SEG_GATE_DECR_TYPE_32TRAP_GATE)||
				(pDecr[index].Type == SYS_SEG_GATE_DECR_TYPE_32INT_GATE)))
			{
				IntAddress = MAKE_DWORD(pDecr[index].OffsetHigh, pDecr[index].OffsetLow);
				if(IntAddress >=gpSyser->m_DriverStartAddr && IntAddress <gpSyser->m_DriverEndAddr)
				{
					DWORD dwTmp=(DWORD)gInterruptStub;
					DWORD dwTmp2=dwTmp+sizeof(gInterruptStub);
					if(IntAddress>=dwTmp && IntAddress <dwTmp2)
					{
						IntAddress = GetOrgInterruptAddress(*(PINTERRUPT_STUB*)&IntAddress);
					}
				}
				if(IntAddress)
				{
					*SkipInstLen=IntAddress-dwEip;
					return true;
				}
			}
		}
	}
	else
#endif
	{
		switch(*CodeBuffer)
		{
		case 0x9c:
		case 0x9d:
			*SkipInstLen=1;
			return true;
		case 0x66:
			if(CodeBuffer[1]==0x9C || CodeBuffer[1]==0x9D)
			{
				*SkipInstLen=2;
				return true;
			}
			break;
		}
	}
	return false;
}
/*
0xc3://ret	
0xc2://ret imm
0xcb://retf
0xca://retf imm		
0xcf://iret
*/
int trace_command(int argc, WCHAR *argv[ ],PCWSTR szCommandLine, CSyser*pSyser)
{
	CHAR szBuffer[256];
	BYTE CodeBuffer[MAX_INSTR_LEN];
	ULPOS Address;
	ULONG Num;
	ASSERT_DEBUGGER_OPENED
#ifdef CODE_OS_WIN
	CDebugger*pDebugger = gpSyser->m_pDebugger;
#else
	CDebugger*pDebugger = gpSyser->m_pOrgProcess;
#endif
	if(argc>1)
	{
		if(USHexStrToNum(argv[1],&Num))
		{//t 3
			gpSyser->m_SyserUI.m_SyserDI.SetTraceCount(Num);
		}
		else
		{//t eax==4321
			PCWSTR pStr = &szCommandLine[argv[1]-argv[0]];
			if(CALCEXP(pStr,&Num))
			{
				UnicodeToAnsi(pStr,szBuffer,256);
				gpSyser->m_SyserUI.m_SyserDI.SetTraceCondition(szBuffer);
			}
			else
			{
				OUTPUT_INPUT_ERROR;
				return -1;
			}
		}
	}
	else
	{
		if(gpSyser->m_SyserUI.m_SyserDI.m_TraceType==TRACE_NULL)
			gpSyser->m_SyserUI.m_SyserDI.SetTraceCount(1);
	}
#ifdef CODE_OS_NT_DRV
	if(gpSyser->m_pDebugger!=gpSyser->m_pOrgProcess)
		gpSyser->MapToProcess(gpSyser->m_pOrgProcess);
#endif
	int SkipInstLen=0;
	int InstLen=0;
	InstLen=pDebugger->ReadMemory(*X86_REG_PTR.pEIP,CodeBuffer,MAX_INSTR_LEN);
	if(InstLen&&IsStepFlagModifyCode(CodeBuffer,*X86_REG_PTR.pEIP,&SkipInstLen,gpSyser))
	{	
		Address = *X86_REG_PTR.pEIP+SkipInstLen;
		if(gpSyser->m_pDebugger->InsertCodeBP(Address,BP_TYPE_DEBUG,BP_STATE_ENABLE)==false)
		{
			OUTPUT(WSTR("Fail to set Debug BP at %08X\n"),Address);
			return 0;
		}	
	}
	else
	{
		pDebugger->SetSingleStep();		
	}
	pDebugger->ContinueDebug(false);
	return 0;
}

int p_command(int argc, WCHAR *argv[ ],PCWSTR szCommandLine, CSyser*pSyser)
{
	bool bRestorScr;
	BYTE CodeBuffer[MAX_INSTR_LEN];
	CHAR szBuffer[256];
	ULPOS Address;
	ULONG Num;
	int CodeLen;
	ASSERT_DEBUGGER_OPENED
#ifdef CODE_OS_WIN
	CDebugger*pDebugger = gpSyser->m_pDebugger;
#else
	CDebugger*pDebugger = gpSyser->m_pOrgProcess;
#endif
	bRestorScr = false;
	if(argc>1)
	{
		if(USHexStrToNum(argv[1],&Num))
		{//p 3
			gpSyser->m_SyserUI.m_SyserDI.SetProceedCount(Num);
			bRestorScr = true;
		}
		else if(TStrICmp(argv[1],"ret")==0)
		{//p ret
			gpSyser->m_SyserUI.m_SyserDI.SetX86RetBreak(pDebugger);
			bRestorScr = true;
		}
		else
		{//p eax==4321
			PCWSTR pStr = &szCommandLine[argv[1]-argv[0]];
			if(CALCEXP(pStr,&Num))
			{
				UnicodeToAnsi(pStr,szBuffer,256);
				gpSyser->m_SyserUI.m_SyserDI.SetTraceProceedCondition(szBuffer);
			}
			else
			{
				OUTPUT_INPUT_ERROR;
				return -1;
			}
		}
	}
	else
	{
		if(gpSyser->m_SyserUI.m_SyserDI.m_TraceType==TRACE_NULL)
			gpSyser->m_SyserUI.m_SyserDI.SetTraceCount(1);
	}
#ifdef CODE_OS_NT_DRV
	if(gpSyser->m_pDebugger!=gpSyser->m_pOrgProcess)
		gpSyser->MapToProcess(gpSyser->m_pOrgProcess);
#endif
	if(gpSyser->m_SyserUI.m_CodeDoc.IsProcessCode(*X86_REG_PTR.pEIP))
	{
		CodeLen=gpSyser->m_SyserUI.m_CodeDoc.InstrLen(*X86_REG_PTR.pEIP);
		gpSyser->m_pDebugger->InsertCodeBP(*X86_REG_PTR.pEIP+CodeLen,BP_TYPE_DEBUG,BP_STATE_ENABLE);
	}
	else
	{
		int SkipInstLen=0;
		if(pDebugger->ReadMemory(*X86_REG_PTR.pEIP,CodeBuffer,MAX_INSTR_LEN)==MAX_INSTR_LEN && IsStepFlagModifyCode(CodeBuffer,*X86_REG_PTR.pEIP,&SkipInstLen,gpSyser))
		{
			Address = *X86_REG_PTR.pEIP+SkipInstLen;
			if(gpSyser->m_pDebugger->InsertCodeBP(Address,BP_TYPE_DEBUG,BP_STATE_ENABLE)==false)
			{
				OUTPUT(WSTR("Fail to set Debug BP at %08X\n"),Address);
				return 0;				
			}
		}
		else
		{//真的单步不恢复屏幕
			pDebugger->SetSingleStep();
		}
	}
	pDebugger->ContinueDebug(bRestorScr);
	return 0;
}

int source_trace_command(int argc, WCHAR *argv[],PCWSTR szCommandLine, CSyser*pSyser)
{
	ULPOS dwEIPRva,dwEndRva,dwBaseAddress;
	ASSERT_DEBUGGER_OPENED
	CSDSModule*pSDSModule = gpSyser->m_SyserUI.GetSDSModule(*gpSyser->m_SyserUI.m_CodeDoc.m_X86RegPtr.pEIP);
	if(pSDSModule==NULL)
		return 1;
	dwBaseAddress = pSDSModule->m_pCurDbgModule->m_ModuleBase;
	dwEIPRva=*gpSyser->m_SyserUI.m_CodeDoc.m_X86RegPtr.pEIP-dwBaseAddress;
	SDLINELIST LineList;
	DWORD Count;
	Count = pSDSModule->GetLineFromRva(dwEIPRva,&LineList);
	if(Count==0)
		return -1;
	PSDLINE pLine = *LineList[0];
	CSourceCodeWnd* pSourceCodeWnd = gpSyser->m_MainFrame.m_SourceDebugFrameWnd.ShowSourceFile(pSDSModule,pLine->FileID,pLine->LineNumber);
	if(pSourceCodeWnd==NULL)
		return -1;
	HANDLE hItem = pSourceCodeWnd->GetItem(pLine->LineNumber-1);
	if(hItem==NULL)
		return -1;
	if(pSourceCodeWnd->IsItemExpanded(hItem))
	{
		RUNCMD(WSTR("T"));
		return 0;
	}
	dwEndRva = pLine->Rva+pLine->Len;
	RUNCMD(WSTR("T"));
	gpSyser->m_SyserUI.m_SyserDI.SetTraceRange(dwBaseAddress+pLine->Rva,dwBaseAddress+dwEndRva);
	return 0;
}

int source_proceed_command(int argc, WCHAR *argv[ ],PCWSTR szCommandLine, CSyser*pSyser)
{
	ULPOS dwEIPRva,dwEndRva,dwBaseAddress;
	ASSERT_DEBUGGER_OPENED
	CSDSModule*pSDSModule = gpSyser->m_SyserUI.GetSDSModule(*gpSyser->m_SyserUI.m_CodeDoc.m_X86RegPtr.pEIP);
	if(pSDSModule==NULL)
		return -1;
	dwBaseAddress = pSDSModule->m_pCurDbgModule->m_ModuleBase;
	dwEIPRva=*gpSyser->m_SyserUI.m_CodeDoc.m_X86RegPtr.pEIP-dwBaseAddress;
	SDLINELIST LineList;
	DWORD Count;
	Count = pSDSModule->GetLineFromRva(dwEIPRva,&LineList);
	if(Count==0)
		return -1;
	PSDLINE pLine = *LineList[0];
	CSourceCodeWnd* pSourceCodeWnd = gpSyser->m_MainFrame.m_SourceDebugFrameWnd.ShowSourceFile(pSDSModule,pLine->FileID,pLine->LineNumber);
	if(pSourceCodeWnd==NULL)
		return -1;
	HANDLE hItem = pSourceCodeWnd->GetItem(pLine->LineNumber-1);
	if(hItem==NULL)
		return -1;
	if(pSourceCodeWnd->IsItemExpanded(hItem))
	{
		RUNCMD(WSTR("P"));
		return 0;
	}
	dwEndRva = pLine->Rva+pLine->Len;
	RUNCMD(WSTR("P"));
	gpSyser->m_SyserUI.m_SyserDI.SetProceedRange(dwBaseAddress+pLine->Rva,dwBaseAddress+dwEndRva);
	return 0;
}

int bc_command(int argc, WCHAR *argv[ ],PCWSTR szCommandLine, CSyser*pSyser)
{
	char szBuffer[MAX_FN_LEN];
	DWORD Num,Index;
	ASSERT_DEBUGGER_OPENED
	if(argc<2)
	{
		OUTPUT_COMMAND_USAGE;
		return -1;
	}
	CODE_ASSERT(pSyser->m_pDebugger);
	if(*argv[1] == (WCHAR)'*')
	{
		gpSyser->m_pDebugger->RemoveAllCodeBP(BP_TYPE_INC_ALL,BP_TYPE_PATCH);
		gpSyser->m_pDebugger->RemoveAllDataBP(BP_TYPE_INC_ALL,BP_TYPE_PATCH);
		gpSyser->m_SyserUI.m_ModuleBPMap.Clear();
		gpSyser->m_SyserUI.m_ModuleLoadBPMap.Clear();
#ifdef CODE_OS_NT_DRV
		for(PROC_RANGE_BP_MAP::IT Iter = gpSyser->m_RangeBPList.Begin();Iter!=gpSyser->m_RangeBPList.End();Iter++)
		{
			BP_RANGE_LIST::IT ListBIT,ListEIT;
			ListBIT = Iter->Begin();
			ListEIT = Iter->End();
			Iter->Clear();						
		}
		gpSyser->m_RangeBPList.Clear();
#endif	
		UPDATE_CODE_VIEW();
		UPDATE_SOURCE_CODE_VIEW();
		UPDATE_BP_FORM();
		return 0;
	}
	if(CALCEXP(argv[1],&Num)==false)
	{//参数如果不是合法的表达式，则按BPLoad断点处理
		UnicodeToAnsi(argv[1],szBuffer,MAX_FN_LEN);
		if(gpSyser->m_SyserUI.m_ModuleLoadBPMap.Remove(szBuffer)>0)
			return 0;
		OUTPUT_INPUT_ERROR;
		return 1;
	}
	if(Num>0x1000)
	{
		Index = gpSyser->m_SyserUI.RemoveCodeBP(Num);
		Index +=  gpSyser->m_pDebugger->RemoveDataBP(Num,BP_TYPE_INC_ALL,BP_TYPE_DEBUG|BP_TYPE_PATCH);
		if(Index > 0)
		{
			UPDATE_CODE_VIEW();
			UPDATE_SOURCE_CODE_VIEW();
			UPDATE_BP_FORM();
			return 0;
		}
	}
	else
	{
		Index = 0;
		for(CCodeBPMap::IT Iter=gpSyser->m_pDebugger->m_pCodeBPMap->Begin();Iter.IsExist();Iter++)
		{
			if((Iter->Type&(BP_TYPE_DEBUG|BP_TYPE_PATCH))==0 && Iter->pModuleBP==NULL)
			{
				if(Index==Num)
				{
					gpSyser->m_pDebugger->RemoveCodeBP(&(*Iter));
					UPDATE_CODE_VIEW();
					UPDATE_SOURCE_CODE_VIEW();
					UPDATE_BP_FORM();
					return 0;
				}
				Index++;
			}
		}
		for(CModuleBPMap::IT Iter=gpSyser->m_SyserUI.m_ModuleBPMap.Begin();Iter.IsExist();Iter++)
		{
			if(Index==Num)
			{
				gpSyser->m_SyserUI.RemoveCodeBP(Iter.Key());
				UPDATE_CODE_VIEW();
				UPDATE_SOURCE_CODE_VIEW();
				UPDATE_BP_FORM();
				return 0;
			}
			Index++;
		}
		for(CDataBPList::IT Iter=gpSyser->m_pDebugger->m_pDataBPList->Begin();Iter!=gpSyser->m_pDebugger->m_pDataBPList->End();Iter++)
		{
			if((Iter->Type&(BP_TYPE_DEBUG|BP_TYPE_PATCH))==0)
			{
				if(Index==Num)
				{
					gpSyser->m_pDebugger->RemoveDataBP(&(*Iter));
					UPDATE_CODE_VIEW();
					UPDATE_SOURCE_CODE_VIEW();
					UPDATE_BP_FORM();
					return 0;
				}
				Index++;
			}
		}
		for(CModuleLoadBPMap::IT Iter=gpSyser->m_SyserUI.m_ModuleLoadBPMap.Begin();Iter.IsExist();Iter++)
		{
			if(Index==Num)
			{
				gpSyser->m_SyserUI.m_ModuleLoadBPMap.Remove(Iter);
				return 0;
			}
			Index++;
		}

#ifdef CODE_OS_NT_DRV
		for(PROC_RANGE_BP_MAP::IT Iter = gpSyser->m_RangeBPList.Begin();Iter!=gpSyser->m_RangeBPList.End();Iter++)
		{
			BP_RANGE_LIST::IT ListBIT,ListEIT;
			ListBIT = Iter->Begin();
			ListEIT = Iter->End();
			CDbgProcess* pDbgProcess = gpSyser->m_SysInfo.GetProcessByEPROCESS(Iter.Key());
			if(pDbgProcess)
			{
				for(;ListBIT!=ListEIT;ListBIT++)
				{
					if(Index==Num)
					{
						Iter->Remove(ListBIT);	
						if(Iter->Count()==0)
							gpSyser->m_RangeBPList.Remove(Iter);
						return 0;
					}
					Index++;
				}
			}		
		}
#endif

	}
	OUTPUT(WSTR("%<3>Error %<1>: breakpoint isn't exist !\n"));
	return 0;
}

int bd_command(int argc, WCHAR *argv[ ],PCWSTR szCommandLine, CSyser*pSyser)
{
	DWORD Num,Index;
	ASSERT_DEBUGGER_OPENED
	if(argc<2)
	{
		OUTPUT_COMMAND_USAGE;
		return -1;
	}
	CODE_ASSERT(pSyser->m_pDebugger);
	if(*argv[1] == (WCHAR)'*')
	{
		gpSyser->m_pDebugger->DisableAllCodeBP(BP_TYPE_INC_ALL,BP_TYPE_DEBUG|BP_TYPE_PATCH);
		gpSyser->m_pDebugger->DisableAllDataBP(BP_TYPE_INC_ALL,BP_TYPE_DEBUG|BP_TYPE_PATCH);
		gpSyser->m_SyserUI.EnableAllLoadBP(false);
		gpSyser->m_SyserUI.EnableAllModuleBP(false);
		UPDATE_CODE_VIEW();
		UPDATE_SOURCE_CODE_VIEW();
		UPDATE_BP_FORM();
		return 0;
	}
	if(CALCEXP(argv[1],&Num)==false)
	{
		OUTPUT_INPUT_ERROR;
		return 1;
	}
	if(Num>0x1000)
	{
		Index = gpSyser->m_pDebugger->DisableCodeBP(Num,BP_TYPE_INC_ALL,BP_TYPE_DEBUG|BP_TYPE_PATCH);
		Index += gpSyser->m_pDebugger->DisableDataBP(Num,BP_TYPE_INC_ALL,BP_TYPE_DEBUG|BP_TYPE_PATCH);
		Index += gpSyser->m_SyserUI.EnableModuleBP(Num,false);
		if(Index > 0)
		{
			UPDATE_CODE_VIEW();
			UPDATE_SOURCE_CODE_VIEW();
			UPDATE_BP_FORM();
			return 0;
		}
	}
	else
	{
		Index = 0;
		for(CCodeBPMap::IT Iter=gpSyser->m_pDebugger->m_pCodeBPMap->Begin();Iter.IsExist();Iter++)
		{
			if((Iter->Type&(BP_TYPE_DEBUG|BP_TYPE_PATCH))==0 && Iter->pModuleBP==NULL)
			{
				if(Index==Num)
				{
					gpSyser->m_pDebugger->DisableCodeBP(&(*Iter));
					UPDATE_CODE_VIEW();
					UPDATE_SOURCE_CODE_VIEW();
					UPDATE_BP_FORM();
					return 0;
				}
				Index++;
			}
		}
		for(CModuleBPMap::IT Iter=gpSyser->m_SyserUI.m_ModuleBPMap.Begin();Iter.IsExist();Iter++)
		{
			if(Index==Num)
			{
				gpSyser->m_SyserUI.EnableModuleBP(Iter.Key(),false);
				UPDATE_CODE_VIEW();
				UPDATE_SOURCE_CODE_VIEW();
				UPDATE_BP_FORM();
				return 0;
			}
			Index++;
		}
		for(CDataBPList::IT Iter=gpSyser->m_pDebugger->m_pDataBPList->Begin();Iter!=gpSyser->m_pDebugger->m_pDataBPList->End();Iter++)
		{
			if((Iter->Type&(BP_TYPE_DEBUG|BP_TYPE_PATCH))==0)
			{
				if(Index==Num)
				{
					gpSyser->m_pDebugger->DisableDataBP(&(*Iter));
					UPDATE_CODE_VIEW();
					UPDATE_SOURCE_CODE_VIEW();
					UPDATE_BP_FORM();
					return 0;
				}
				Index++;
			}
		}
		for(CModuleLoadBPMap::IT Iter=gpSyser->m_SyserUI.m_ModuleLoadBPMap.Begin();Iter.IsExist();Iter++)
		{
			if((Iter->Type&(BP_TYPE_DEBUG|BP_TYPE_PATCH))==0)
			{
				if(Index==Num)
				{
					Iter->State = BP_STATE_DISABLE;					
					return 0;
				}
				Index++;
			}
		}

#ifdef CODE_OS_NT_DRV
		for(PROC_RANGE_BP_MAP::IT Iter = gpSyser->m_RangeBPList.Begin();Iter!=gpSyser->m_RangeBPList.End();Iter++)
		{
			BP_RANGE_LIST::IT ListBIT,ListEIT;
			ListBIT = Iter->Begin();
			ListEIT = Iter->End();
			CDbgProcess* pDbgProcess = gpSyser->m_SysInfo.GetProcessByEPROCESS(Iter.Key());
			if(pDbgProcess)
			{
				for(;ListBIT!=ListEIT;ListBIT++)
				{
					if(Index==Num)
					{
						ListBIT->State = BP_STATE_DISABLE;
						return 0;
					}
					Index++;
				}
			}		
		}
#endif

	}
	OUTPUT(WSTR("%<3>Error %<1>: breakpoint isn't exist !\n"));
	return 0;
}

int be_command(int argc, WCHAR *argv[ ],PCWSTR szCommandLine, CSyser*pSyser)
{
	DWORD Num,Index;
	ASSERT_DEBUGGER_OPENED
	if(argc<2)
	{
		OUTPUT_COMMAND_USAGE;
		return -1;
	}
	CODE_ASSERT(pSyser->m_pDebugger);
	if(*argv[1] == (WCHAR)'*')
	{
		gpSyser->m_pDebugger->EnableAllCodeBP(BP_TYPE_INC_ALL,BP_TYPE_DEBUG|BP_TYPE_PATCH);
		gpSyser->m_pDebugger->EnableAllDataBP(BP_TYPE_INC_ALL,BP_TYPE_DEBUG|BP_TYPE_PATCH);
		gpSyser->m_SyserUI.EnableAllLoadBP(true);
		gpSyser->m_SyserUI.EnableAllModuleBP(true);
		UPDATE_CODE_VIEW();
		UPDATE_SOURCE_CODE_VIEW();
		UPDATE_BP_FORM();
		return 0;
	}
	if(CALCEXP(argv[1],&Num)==false)
	{
		OUTPUT_INPUT_ERROR;
		return 1;
	}
	if(Num>0x1000)
	{//输入是个地址
		Index =  gpSyser->m_pDebugger->EnableCodeBP(Num,BP_TYPE_INC_ALL,BP_TYPE_DEBUG|BP_TYPE_PATCH);
		Index += gpSyser->m_pDebugger->EnableDataBP(Num,BP_TYPE_INC_ALL,BP_TYPE_DEBUG|BP_TYPE_PATCH);
		Index += gpSyser->m_SyserUI.EnableModuleBP(Num);
		if(Index > 0)
		{
			UPDATE_CODE_VIEW();
			UPDATE_SOURCE_CODE_VIEW();
			UPDATE_BP_FORM();
			return 0;
		}
	}
	else
	{//输入是个序号
		Index = 0;
		for(CCodeBPMap::IT Iter=gpSyser->m_pDebugger->m_pCodeBPMap->Begin();Iter.IsExist();Iter++)
		{
			if((Iter->Type&(BP_TYPE_DEBUG|BP_TYPE_PATCH))==0 && Iter->pModuleBP==NULL)
			{
				if(Index==Num)
				{
					gpSyser->m_pDebugger->EnableCodeBP(&(*Iter));
					UPDATE_CODE_VIEW();
					UPDATE_SOURCE_CODE_VIEW();
					UPDATE_BP_FORM();
					return 0;
				}
				Index++;
			}
		}
		for(CModuleBPMap::IT Iter=gpSyser->m_SyserUI.m_ModuleBPMap.Begin();Iter.IsExist();Iter++)
		{
			if(Index==Num)
			{
				gpSyser->m_SyserUI.EnableModuleBP(Iter.Key());
				UPDATE_CODE_VIEW();
				UPDATE_SOURCE_CODE_VIEW();
				UPDATE_BP_FORM();
				return 0;
			}
			Index++;
		}
		for(CDataBPList::IT Iter=gpSyser->m_pDebugger->m_pDataBPList->Begin();Iter!=gpSyser->m_pDebugger->m_pDataBPList->End();Iter++)
		{
			if((Iter->Type&(BP_TYPE_DEBUG|BP_TYPE_PATCH))==0)
			{
				if(Index==Num)
				{
					gpSyser->m_pDebugger->EnableDataBP(&(*Iter));
					UPDATE_CODE_VIEW();
					UPDATE_SOURCE_CODE_VIEW();
					UPDATE_BP_FORM();
					return 0;
				}
				Index++;
			}
		}
		for(CModuleLoadBPMap::IT Iter=gpSyser->m_SyserUI.m_ModuleLoadBPMap.Begin();Iter.IsExist();Iter++)
		{
			if((Iter->Type&(BP_TYPE_DEBUG|BP_TYPE_PATCH))==0)
			{
				if(Index==Num)
				{
					Iter->State = BP_STATE_ENABLE;					
					return 0;
				}
				Index++;
			}
		}

#ifdef CODE_OS_NT_DRV
		for(PROC_RANGE_BP_MAP::IT Iter = gpSyser->m_RangeBPList.Begin();Iter!=gpSyser->m_RangeBPList.End();Iter++)
		{
			BP_RANGE_LIST::IT ListBIT,ListEIT;
			ListBIT = Iter->Begin();
			ListEIT = Iter->End();
			CDbgProcess* pDbgProcess = gpSyser->m_SysInfo.GetProcessByEPROCESS(Iter.Key());
			if(pDbgProcess)
			{
				for(;ListBIT!=ListEIT;ListBIT++)
				{
					if(Index==Num)
					{
						ListBIT->State=	BP_STATE_ENABLE;			
						return 0;
					}
					Index++;
				}
			}		
		}
#endif

	}
	OUTPUT(WSTR("%<3>Error %<1>: breakpoint isn't exist !\n"));
	return 0;
}

void DispCodeBreakPoint(int&Index,BREAK_POINT&BP,bool bAll)
{
	WCHAR szType[128],szOwner[128],szName[128];
	if(bAll==false && BP.Type&(BP_TYPE_DEBUG|BP_TYPE_PATCH))
		return;
	if(bAll==false && BP.pModuleBP)
		return;
	if(Index==0)
		OUTPUT(WSTR("Index OwnerProcess   Type     Address    Name\n"));
	TStrCpy(szType,"Code");
	AnsiToUnicode(BP.OwnerName,szOwner,128);
	AnsiToUnicode(BP.Name,szName,128);

	if(bAll)
	{
		CCodeBPMap::IT Iter = BP;
		if(BP.State!=BP_STATE_DISABLE)
			OUTPUT(WSTR("%-5X %<B>%-14s %<7>%-8s %<4>%08X   %<1>%s %08X\n"),Index,szOwner,szType,BP.Address,szName,(DWORD)Iter.Key());
		else
			OUTPUT(WSTR("%<C>%-5X %-14s %-8s %08X   %s  %08X\n"),Index,szOwner,szType,BP.Address,szName,(DWORD)Iter.Key());
	}
	else
	{
		if(BP.State!=BP_STATE_DISABLE)
			OUTPUT(WSTR("%-5X %<B>%-14s %<7>%-8s %<4>%08X   %<1>%s\n"),Index,szOwner,szType,BP.Address,szName);
		else
			OUTPUT(WSTR("%<C>%-5X %-14s %-8s %08X   %s\n"),Index,szOwner,szType,BP.Address,szName);
	}
	Index++;
}

void DispModuleBreakPoint(int&Index,MODULE_BP&BP,bool bAll)
{
	WCHAR szBuffer[MAX_FN_LEN];
	if(Index==0)
		OUTPUT(WSTR("Index OwnerProcess   Type     Address    Name\n"));
	AnsiToUnicode(BP.Name,szBuffer,MAX_FN_LEN);
	CModuleBPMap::IT Iter = BP;
	if(BP.State !=BP_STATE_DISABLE)
		OUTPUT(WSTR("%-5X %<B><All Process>  %<7>Code     %<4>%08X   %<1>%s\n"),Index,Iter.Key(),szBuffer);
	else
		OUTPUT(WSTR("%<C>%-5X <All Process>  Code     %08X   %s\n"),Index,Iter.Key(),szBuffer);
	Index++;
}

void DispDataBreakPoint(int&Index,BREAK_POINT&BP,bool bAll)
{
	WCHAR szType[128],szOwner[128],szName[128];
	if(bAll==false && BP.Type&(BP_TYPE_DEBUG|BP_TYPE_PATCH))
		return;
	if(Index==0)
		OUTPUT(WSTR("Index OwnerProcess   Type     Address    Name\n"));
	TStrCpy(szType,"Data ");
	TStrCat(szType,(PCSTR)BP.Description);
	AnsiToUnicode(BP.OwnerName,szOwner,128);
	AnsiToUnicode(BP.Name,szName,128);
	if(BP.State!=BP_STATE_DISABLE)
		OUTPUT(WSTR("%-5X %<B>%-14s %<7>%-8s %<4>%08X   %<1>%s\n"),Index,szOwner,szType,BP.Address,szName);
	else
		OUTPUT(WSTR("%<C>%-5X %-14s %-8s %08X   %s\n"),Index,szOwner,szType,BP.Address,szName);
	Index++;
}

void DispBPLoadBreakPoint(int&Index,BP_LOAD&BP,PCSTR ModuleName,bool bAll)
{
	WCHAR szBuffer[MAX_FN_LEN];
	if(bAll==false && BP.Type&(BP_TYPE_DEBUG|BP_TYPE_PATCH))
		return;
	if(Index==0)
		OUTPUT(WSTR("Index OwnerProcess   Type     Address    Name\n"));
	AnsiToUnicode(ModuleName,szBuffer,MAX_FN_LEN);
	if(BP.State !=BP_STATE_DISABLE)
		OUTPUT(WSTR("%-5X %<B><All Process>  %<7>BPLoad   %<4>EntryPoint %<1>%s\n"),Index,szBuffer);
	else
		OUTPUT(WSTR("%<C>%-5X <All Process>  BPLoad   EntryPoint %s\n"),Index,szBuffer);
	Index++;
}

#ifdef CODE_OS_NT_DRV

void DispBPRBreakPoint(int&Index,BP_RANGE_INFO&BP,WCHAR*ProcName, bool bAll)
{
	WCHAR szBuffer[MAX_FN_LEN];

	if(Index==0)
		OUTPUT(WSTR("Index OwnerProcess   Type     Address    Name\n"));
	if(BP.State!=BP_STATE_DISABLE)
		OUTPUT(WSTR("%-5X %<B>%-14s %<7>%-8s %<4>%08X-%08X\n"),Index,ProcName,WSTR("BMR"),BP.RangeStartAddress,BP.RangeStartAddress+BP.RangeLength);
	else
		OUTPUT(WSTR("%<C>-5X %<B>%-14s %-8s %08X-%08X\n"),Index,ProcName,WSTR("BMR"),BP.RangeStartAddress,BP.RangeStartAddress+BP.RangeLength);
	Index++;
}

#endif

int bl_command(int argc, WCHAR *argv[ ],PCWSTR szCommandLine, CSyser*pSyser)
{
	bool bDispAll;
	int Index=0;
	if(argc>1 && argv[1][0]=='*')
		bDispAll = true;
	else
		bDispAll = false;
	for(CCodeBPMap::IT Iter=gpSyser->m_pDebugger->m_pCodeBPMap->Begin();Iter!=gpSyser->m_pDebugger->m_pCodeBPMap->End();Iter++)
	{
		DispCodeBreakPoint(Index,*Iter,bDispAll);
	}
	for(CModuleBPMap::IT Iter=gpSyser->m_SyserUI.m_ModuleBPMap.Begin();Iter.IsExist();Iter++)
	{
		DispModuleBreakPoint(Index,*Iter,bDispAll);
	}
	for(CDataBPList::IT Iter=gpSyser->m_pDebugger->m_pDataBPList->Begin();Iter!=gpSyser->m_pDebugger->m_pDataBPList->End();Iter++)
	{
		DispDataBreakPoint(Index,*Iter,bDispAll);
	}
	for(CModuleLoadBPMap::IT Iter=gpSyser->m_SyserUI.m_ModuleLoadBPMap.Begin();Iter!=gpSyser->m_SyserUI.m_ModuleLoadBPMap.End();Iter++)
	{
		DispBPLoadBreakPoint(Index,*Iter,Iter.Key(),bDispAll);
	}
#ifdef CODE_OS_NT_DRV
	for(PROC_RANGE_BP_MAP::IT Iter = gpSyser->m_RangeBPList.Begin();Iter!=gpSyser->m_RangeBPList.End();Iter++)
	{
		BP_RANGE_LIST::IT ListBIT,ListEIT;
		ListBIT = Iter->Begin();
		ListEIT = Iter->End();
		CDbgProcess* pDbgProcess = gpSyser->m_SysInfo.GetProcessByEPROCESS(Iter.Key());
		if(pDbgProcess)
		{
			for(;ListBIT!=ListEIT;ListBIT++)
			{
				DispBPRBreakPoint(Index,*ListBIT,(WCHAR*)pDbgProcess->m_ProcNameW,bDispAll);
			}
		}		
	}
#endif

	if(Index==0)
		OUTPUT(WSTR("Breakpoint doesn't exist!\n"));
	return 0;
}

int bpload_command(int argc,WCHAR *argv[],PCWSTR szCommandLine,CSyser *pSyser)
{
	WCHAR szBuffer[MAX_FN_LEN];
	if(argc==1)
	{		
		for(CModuleLoadBPMap::IT Iter=gpSyser->m_SyserUI.m_ModuleLoadBPMap.Begin();Iter!=gpSyser->m_SyserUI.m_ModuleLoadBPMap.End();Iter++)
		{
			AnsiToUnicode(Iter.Key(),szBuffer,MAX_FN_LEN);
			OUTPUT(WSTR("%s\n"),szBuffer);
		}
	}
	else if(argc==2)
	{
		PSTR szBufferA = (PSTR)szBuffer;
		UnicodeToAnsi(argv[1],szBufferA,MAX_FN_LEN);
		gpSyser->m_SyserUI.InsertLoadBP(szBufferA,0,BP_STATE_ENABLE);
	}
	return 0;
}

int get_command_condition_string(int argc, WCHAR *argv[ ],PCWSTR szCommandLine,char* szCondition,int MaxSize)
{
	PCWSTR ConditionBegin,ConditionEnd;
	int n;
	for(n=2;n<argc;n++)
	{
		if(TStrICmp(argv[n],"if")==0)
		{
			n++;
			break;
		}
	}
	if(n>=argc)
	{
		*szCondition=0;
		return 0;
	}
	ConditionBegin = &szCommandLine[argv[n]-argv[0]];
	for(;n<argc;n++)
	{
		if(TStrICmp(argv[n],"do")==0)
			break;
	}
	if(n>=argc)
	{
		return TStrCpyLimit(szCondition,ConditionBegin,MaxSize);
	}
	else
	{
		ConditionEnd = &szCommandLine[argv[n]-argv[0]];
		while(ConditionEnd[-1]==' ' && ConditionEnd>ConditionBegin)
			ConditionEnd--;
		return TStrCpyLimit(szCondition,ConditionBegin,MIN(MaxSize,(int)(ConditionEnd-ConditionBegin)+1));
	}
}

int get_do_command_string(int argc, WCHAR *argv[ ],PCWSTR szCommandLine,char* szDoCmd,int MaxSize)
{
	int n;
	for(n=2;n<argc;n++)
	{
		if(TStrICmp(argv[n],"do")==0)
		{
			n++;
			break;
		}
	}
	if(n>=argc)
	{
		*szDoCmd = 0;
		return 0;
	}
	return TStrCpyLimit(szDoCmd,&szCommandLine[argv[n]-argv[0]],MaxSize);
}


int bpx_command(int argc, WCHAR *argv[ ],PCWSTR szCommandLine, CSyser*pSyser)
{
	ULPOS Address;
	CHAR Name[256],Condition[256],DoCmd[256];
	ASSERT_DEBUGGER_OPENED
	if(argc<=1)
	{
		OUTPUT_COMMAND_USAGE;
		return 1;
	}
	UnicodeToAnsi(argv[1],Name,sizeof(Name));
	if(get_command_condition_string(argc,argv,szCommandLine,Condition,256)>0)
	{
		if(CALCEXP(Condition,NULL)==false)
		{
			OUTPUT(WSTR("Error : Invalid condition string !\n"));
			return -1;
		}
	}
	get_do_command_string(argc,argv,szCommandLine,DoCmd,256);
	int Count = 0;
	if(CALCEXP(argv[1],&Address))
	{
		if(gpSyser->m_SyserUI.InsertCodeBP(Address,Name,Condition,DoCmd)==false)
			OUTPUT(WSTR("Error : Fail to set code breakpoint at %08X!\n"),Address);
		else
			OUTPUT(WSTR("Set code break point at %<B>%08X%<1>!\n"),Address);
	}
	else
	{
#ifdef CODE_OS_NT_DRV
		OUTPUT(WSTR("Error : Counldn't find symbol %<F>%s%<1> in [%<B>%s%<1>] process space\n"),argv[1],(PCWSTR)gpSyser->m_pDebugger->m_ProcNameW);
#endif
#ifdef CODE_OS_WIN
		OUTPUT(WSTR("Error : Counldn't find symbol %<F>%s%\n"),argv[1]);
#endif
	}
	UPDATE_CODE_VIEW();
	UPDATE_SOURCE_CODE_VIEW();
	UPDATE_BP_FORM();
	return 0;
}


int bpm_command(int argc, WCHAR *argv[ ],PCWSTR szCommandLine, CSyser*pSyser)
{
	UINT Type;
	ULPOS Address;
	BREAK_POINT*pBP;
	CHAR Condition[256],DoCmd[256];
	int Length;
	if(argc<2)
	{
		OUTPUT_COMMAND_USAGE;
		return -1;
	}
	switch(argv[0][3])
	{
	case 'b':
	case 'B':
		Length = 1;
		break;
	case 'w':
	case 'W':
		Length = 2;
		break;
	case 'd':
	case 'D':
		Length = 4;
		break;
	default:
		Length = 0;
		break;
	}
	if(CALCEXP(argv[1],&Address)==false)
	{
		OUTPUT_INVALID_ADDRESS;
		return -1;
	}
	Type = BP_TYPE_READWRITE;
	if(argc>2 && TStrICmp(argv[2],"if") && TStrICmp(argv[2],"do"))
	{
		if(TStrICmp(argv[2],"rw")==0)
			Type = BP_TYPE_READWRITE;
		else if(TStrICmp(argv[2],"w")==0)
			Type = BP_TYPE_WRITE;
		else if(TStrICmp(argv[2],"x")==0)
			Type = BP_TYPE_EXECUTE;
		else
		{
			OUTPUT(WSTR("Error : Invalid access type !\n"));
			return -1;
		}
	}
	if(get_command_condition_string(argc,argv,szCommandLine,Condition,256)>0)
	{
		if(CALCEXP(Condition,NULL)==false)
		{
			OUTPUT(WSTR("Error : Invalid condition string !\n"));
			return -1;
		}
	}
	get_do_command_string(argc,argv,szCommandLine,DoCmd,256);
	pBP = gpSyser->m_pDebugger->InsertDataBP(Address,Type,BP_STATE_ENABLE,Length);
	if(pBP)
	{
		if(*Condition)
			pBP->Condition = Condition;
		if(*DoCmd)
			pBP->DoCmd = DoCmd;
		OUTPUT(WSTR("Set data break point at %<B>%08X%<1>!\n"),Address);
	}
	else
	{
		OUTPUT(WSTR("Error : Fail to set dat breakpoint !\n"));
	}
	UPDATE_CODE_VIEW();
	UPDATE_SOURCE_CODE_VIEW();
	UPDATE_BP_FORM();
	return 0;
}

int bpio_command(int argc, WCHAR *argv[ ],PCWSTR szCommandLine, CSyser*pSyser)
{
	UINT Type;
	ULPOS Address;
	BREAK_POINT*pBP;
	CHAR Condition[256],DoCmd[256];
	int Length;
	if(argc<2)
	{
		OUTPUT_COMMAND_USAGE;
		return -1;
	}
	if(CALCEXP(argv[1],&Address)==false || Address>0xFFFF)
	{
		OUTPUT_INVALID_ADDRESS;
		return -1;
	}
	Length = 0;
	Type = BP_TYPE_IO_READWRITE;
	if(get_command_condition_string(argc,argv,szCommandLine,Condition,256)>0)
	{
		if(CALCEXP(Condition,NULL)==false)
		{
			OUTPUT(WSTR("Error : Invalid condition string !\n"));
			return -1;
		}
	}
	get_do_command_string(argc,argv,szCommandLine,DoCmd,256);
	pBP = gpSyser->m_pDebugger->InsertDataBP(Address,Type,BP_STATE_ENABLE,Length);
	if(pBP)
	{
		if(*Condition)
			pBP->Condition = Condition;
		if(*DoCmd)
			pBP->DoCmd = DoCmd;
	}
	else
	{
		OUTPUT(WSTR("Error : fail to set breakpoint !\n"));
	}
	UPDATE_CODE_VIEW();
	UPDATE_SOURCE_CODE_VIEW();
	UPDATE_BP_FORM();
	return 0;
}

int stack_command(int argc, WCHAR *argv[ ],PCWSTR szCommandLine, CSyser*pSyser)
{
	DWORD EBP;
	DWORD *pESP;
	WCHAR szBuffer[256];
	ULSIZE CodeLen,Address;//
	CHAR szSymbol[MAX_SYMBOL_LEN];
	CDbgModule*pDbgModule;
	int m=0;
	ASSERT_DEBUGGER_OPENED
	if(argc==1)
	{
		EBP = *X86_REG_PTR.pEBP;
	}
	else
	{
		if(CALCEXP(argv[1],&EBP)==false)
		{
			OUTPUT_INVALID_PARAM;
			return -1;
		}
	}
	gpSyser->m_SyserUI.m_CallStack.UpdateContext(EBP);
	if(gpSyser->m_SyserUI.m_CallStack.m_CallFrameList.Count())
	{
		OUTPUT(WSTR("CallReturn Frame    Function Name\n"));
	}
	else
		gpSyser->m_SyserUI.m_CallStack.UpdateContext(*X86_REG_PTR.pESP);
	if(gpSyser->m_SyserUI.m_CallStack.m_CallFrameList.Count()==0)
	{
		OUTPUT(WSTR("CallReturn Frame    Function Name  count=0\n"));
		pESP=(DWORD*)*X86_REG_PTR.pESP;// Reg.GeneReg[ESP_IDX];
		DWORD dwTmpAddress,dwTmpAddress2;
		bool bReadOK;
		for(int n=0;1;n++)
		{
			dwTmpAddress = ReadDword(&pESP[n],&bReadOK);
			
			if(bReadOK==false)
				break;

			dwTmpAddress2 = ReadDword(*(void**)&dwTmpAddress,&bReadOK);
			if(bReadOK==false)
				continue;
			
			CodeLen=gpSyser->m_SyserUI.m_CodeDoc.IsPrevCodeCallInstr(dwTmpAddress,szSymbol,&Address);
			if(CodeLen)
			{
				TStrCpy(szBuffer,"no symbols");
				if(*szSymbol==0)//找不到符号就用模块名+偏移形式
				{
					pDbgModule=gpSyser->m_pDebugger->m_ModuleList.GetModule(Address);
					if(pDbgModule==NULL && gpSyser->m_pDebugger!=gpSyser->m_pSysDebugger)
						pDbgModule=gpSyser->m_pSysDebugger->m_ModuleList.GetModule(Address);
					if(pDbgModule)
						TSPrintf(szSymbol,"%s+0x%X",(PCSTR)pDbgModule->m_ModuleTitle,Address-pDbgModule->m_ModuleBase);
					else
						TSPrintf(szSymbol,"unknown_function");
					TStrCpy(szBuffer,szSymbol);
					
				}
				OUTPUT(WSTR("%<7>%08X   %08X %s\n"),dwTmpAddress,pESP,szBuffer);
				m++;
				if(m>20)
					break;
			}
		
		}
		
		return 0;
	}
	for(TList<CALL_FRAME>::IT Iter=gpSyser->m_SyserUI.m_CallStack.m_CallFrameList.Begin();
		Iter!=gpSyser->m_SyserUI.m_CallStack.m_CallFrameList.End();Iter++)
	{
		AnsiToUnicode(Iter->FuncName,szBuffer,256);
		if(gpSyser->m_SyserUI.m_CallStack.m_pCurCallFrame ==&(*Iter))
		{
			OUTPUT(WSTR("%<7>%08X   %08X %s\n"),Iter->CallReturn,Iter->FrameAddress,szBuffer);
		}
		else
		{
			OUTPUT(WSTR("%08X   %08X %s\n"),Iter->CallReturn,Iter->FrameAddress,szBuffer);
		}
	}
#ifdef CODE_OS_NT_DRV
	if(gpSyser->m_SyserUI.m_CallStack.m_CallFrameList.Count()<2)
	{
		OUTPUT(WSTR("------------------------------------------\n"));
		pESP=(DWORD*)Reg.GeneReg[ESP_IDX];
		DWORD dwTmpAddress,dwTmpAddress2;
		bool bReadOK;
		for(int n=0;1;n++)
		{
			dwTmpAddress = ReadDword(&pESP[n],&bReadOK);

			if(bReadOK==false)
				break;

			dwTmpAddress2 = ReadDword(*(void**)&dwTmpAddress,&bReadOK);
			if(bReadOK==false)
				continue;
			szSymbol[0]=0;
			CodeLen=gpSyser->m_SyserUI.m_CodeDoc.IsPrevCodeCallInstr(dwTmpAddress,szSymbol,&Address);
			if(CodeLen)
			{
				//TStrCpy(szBuffer,"no symbols");
				if(*szSymbol==0)//找不到符号就用模块名+偏移形式
				{
					pDbgModule=gpSyser->m_pDebugger->m_ModuleList.GetModule(Address);
					if(pDbgModule==NULL && gpSyser->m_pDebugger!=gpSyser->m_pSysDebugger)
						pDbgModule=gpSyser->m_pSysDebugger->m_ModuleList.GetModule(Address);
					if(pDbgModule)
						TSPrintf(szSymbol,"%s+0x%X",(PCSTR)pDbgModule->m_ModuleTitle,Address-pDbgModule->m_ModuleBase);
					else
						TSPrintf(szSymbol,"unknown_function");
					TStrCpy(szBuffer,szSymbol);

				}
				OUTPUT(WSTR("%<7>%08X   %08X %s\n"),dwTmpAddress,pESP+n,szBuffer);
				m++;
				if(m>20)
					break;
			}

		}
	}
#endif
	return 0;
}

int skip_command(int argc, WCHAR *argv[ ],PCWSTR szCommandLine, CSyser*pSyser)
{
	X86_CPU_REG_PTR RegPtr;
	ASSERT_DEBUGGER_OPENED
	pSyser->m_pDebugger->GetX86RegPtr(&RegPtr);
	*RegPtr.pEIP+=pSyser->m_SyserUI.m_CodeDoc.InstrLen(*RegPtr.pEIP);
	pSyser->m_pDebugger->SaveRegister();
	UPDATE_CONTEXT();
	return 0;
}

int cmt_command(int argc,WCHAR *argv[],PCWSTR szCommandLine,CSyser *pSyser)
{
	WCHAR szBuffer[MAX_FN_LEN];
	ASSERT_DEBUGGER_OPENED
	TMap<MODULE_ID,CCommentModule>::IT ModuleIter = gpSyser->m_SyserUI.m_CommentContainer.Begin();
	while(ModuleIter.IsExist())
	{
		AnsiToUnicode(ModuleIter->m_ModuleName,szBuffer,MAX_FN_LEN);
		OUTPUT(WSTR("Comment Module : %<F>%s\n"),szBuffer);
		CCommentMap::IT CmtIter = ModuleIter->m_CommentMap.Begin();
		while(CmtIter!=ModuleIter->m_CommentMap.End())
		{
			AnsiToUnicode(*CmtIter,szBuffer,MAX_FN_LEN);
			OUTPUT(WSTR("%<5>%08X %<F>%s\n"),CmtIter.Key(),szBuffer);
			CmtIter++;
		}
		ModuleIter++;
	}
	return 0;
}

int u_command(int argc, WCHAR *argv[ ],PCWSTR szCommandLine, CSyser*pSyser)
{
	ULPOS Address,dwBaseAddress;
	int nItemCount;
	HANDLE hItem;
	NUM_PTR nLastAddr;
	CCodeView* pCodeView;
	ASSERT_DEBUGGER_OPENED
	if(argc==1)
	{
		Address=*X86_REG_PTR.pEIP;
		if(argv[0][0]!='.')
		{
			pCodeView=ACTIVE_CODE_VIEW;
			nItemCount = pCodeView->GetItemCount();
			hItem = pCodeView->GetItem(nItemCount);
			nLastAddr = pCodeView->GetItemData(hItem,1);
			Address=(ULPOS)nLastAddr;
		}		
	}
	else
	{
		if(argc==2)
		{
			if(TStrICmp(argv[1],WSTR("-"))==0)
			{
				pCodeView=ACTIVE_CODE_VIEW;
				pCodeView->OnPrevPos(NULL);
				return 0;
			}
			else if(TStrICmp(argv[1],WSTR("+"))==0)
			{
				pCodeView=ACTIVE_CODE_VIEW;
				pCodeView->OnNextPos(NULL);
				return 0;
			}
			else 
				if(CALCEXP(argv[1],&Address)==false)
				{
					OUTPUT(WSTR("Error : %<3>Input error !\n"));
					return 1;
				}
		}
		
		
		
		if(argc==3)
		{
			WCHAR *param1,*param2;
			param1=argv[1];
			param2=argv[2];
			do
			{
				argc--;
				if(TStrICmp(param1,WSTR("-"))==0)
				{
					if(CALCEXP(param2,&Address)==FALSE)
					{
						OUTPUT(WSTR("Error : %<3>Input error !\n"));
						return -1;
					}
					pCodeView=ACTIVE_CODE_VIEW;
					if(pCodeView==NULL)
						return 1;			
					dwBaseAddress = pSyser->m_MainFrame.m_SystemExplorer.m_MultiCodeView.GetActiveAddress();
					Address=dwBaseAddress-Address;
					break;

				}
				else if(TStrICmp(param1,WSTR("+"))==0)
				{
					if(CALCEXP(param2,&Address)==FALSE)
					{
						OUTPUT(WSTR("Error : %<3>Input error !\n"));
						return -1;
					}
					pCodeView=ACTIVE_CODE_VIEW;
					if(pCodeView==NULL)
						return 1;			
					dwBaseAddress = pSyser->m_MainFrame.m_SystemExplorer.m_MultiCodeView.GetActiveAddress();								
					Address=dwBaseAddress+Address;
					break;
				}
				else if(TStrICmp(param1,WSTR("-a"))==0)
				{
					gpSyser->m_MainFrame.m_SystemExplorer.m_MultiCodeView.InsertView(NULL);
					if(CALCEXP(param2,&Address)==FALSE)
					{
						OUTPUT(WSTR("Error : %<3>Input error !\n"));
						return -1;
					}
					break;
				}

				param1=argv[2];
				param2=argv[1];
			}while(argc!=1);
		}
	}
	gpSyser->m_MainFrame.m_SystemExplorer.m_MultiCodeView.SetActiveAddress(Address,true);
	return 0;
}

int src_command(int argc, WCHAR *argv[ ],PCWSTR szCommandLine, CSyser*pSyser)
{
	ULPOS Address;
	if(argc==1)
	{
		Address=*X86_REG_PTR.pEIP;
	}
	else
	{
		if(CALCEXP(argv[1],&Address)==false)
		{
			OUTPUT_INVALID_ADDRESS;
			return 1;
		}
	}
	CSDSModule*pSDSModule = gpSyser->m_SyserUI.GetSDSModule(Address);
	if(pSDSModule==NULL)
	{
		OUTPUT(WSTR("Couldn't find source code in SDS Module list !\n"));
		return -1;
	}
	gpSyser->m_MainFrame.m_SourceDebugFrameWnd.m_SDSModuleList.SetActiveModule(pSDSModule);
	SDLINELIST LineList;
	if(pSDSModule->GetLineFromRva(Address-pSDSModule->m_pCurDbgModule->m_ModuleBase,&LineList))
	{
		gpSyser->m_MainFrame.m_MainTabWnd.SetActiveWnd(SOURCE_EXPLORER_VIEW);
		gpSyser->m_MainFrame.m_SourceDebugFrameWnd.ShowSourceFile(pSDSModule,(*LineList[0])->FileID,(*LineList[0])->LineNumber);
		gpSyser->m_MainFrame.m_SourceDebugFrameWnd.m_MultiSourceCodeView.UpdateAllView();
		gpSyser->m_MainFrame.m_SourceDebugFrameWnd.m_SourceVariableWatchWnd.UpdateContext();
	}
	return 0;
}

int a_command(int argc, WCHAR *argv[],PCWSTR szCommandLine,CSyser *pSyser)
{
	ULSIZE Length;
	CHAR szBuffer[128];
	BYTE CodeBuffer[64];
	DWORD EIP;
	if(!gpSyser->m_SyserUI.m_CodeDoc.IsOpened())
		return 0;
	if(argc<3)
	{
		OUTPUT_COMMAND_USAGE;
		return -1;
	}
	if(CALCEXP(argv[1],&EIP)==false)
	{
		OUTPUT_INVALID_ADDRESS;
		return -1;
	}
	TStrCpyLimit(szBuffer,&szCommandLine[argv[2]-argv[0]],sizeof(szBuffer));
	Length = gpSyser->m_SyserUI.m_CodeDoc.Asm(szBuffer,CodeBuffer,EIP);
	if(Length==0)
	{
		OUTPUT(WSTR("%<3>Error %<1>: Invalid asm code string!\n"));
		return -1;
	}
	if(pSyser->m_pDebugger->WriteMemory(EIP,CodeBuffer,Length)!=Length)
	{
		OUTPUT(WSTR("%<3>Error %<1>: Fail to write code to %08X!\n"),argv[1]);
		return -1;
	}
	//UPDATE_MEMORY_VIEW();
	UPDATE_CONTEXT();
	return 0;
}

int e_command(int argc,WCHAR *argv[],PCWSTR szCommandLine,CSyser *pSyser)
{
	int Length;
	ULPOS Address;
	BYTE Buffer[256];
	PCWSTR szValue;
	if(argc < 2)
	{
		OUTPUT_COMMAND_USAGE;
		return -1;
	}
	if(CALCEXP(argv[1],&Address)==false)
	{
		OUTPUT_INVALID_ADDRESS;
		return -1;
	}
	if(argc == 2)
	{
		pSyser->m_MainFrame.m_SystemExplorer.m_MultiDataView.SetActiveAddress(Address,argv[1]);
		return 0;
	}
	ZeroMemory(Buffer,sizeof(Buffer));
	szValue = &szCommandLine[argv[2]-argv[0]];
	bool Result;
	switch(argv[0][1])
	{
	case 'w':
	case 'W':
		if(CALCEXP(szValue,(ULONG*)Buffer)==false)
		{
			OUTPUT_INVALID_PARAM;
			return -1;
		}
		Result = pSyser->m_pDebugger->WriteMemory(Address,Buffer,2)==2;
		break;
	case 'd':
	case 'D':
		if(CALCEXP(szValue,(ULONG*)Buffer)==false)
		{
			OUTPUT_INVALID_PARAM;
			return -1;
		}
		Result = pSyser->m_pDebugger->WriteMemory(Address,Buffer,4)==4;
		break;
	default:
		{
			if(*szValue=='"'||*szValue=='\'')
			{
				szValue++;
				Length=0;
				while(szValue[Length] && szValue[Length]!='"'&& *szValue!='\'' && Length<sizeof(Buffer)-1)
				{
					Buffer[Length]=(BYTE)szValue[Length];
					Length++;
				}
				Buffer[Length++]=0;
			}
			else
			{
				Length = THexStrToBytes(szValue,Buffer,sizeof(Buffer));
				if(Length==0)
				{
					OUTPUT_INVALID_PARAM;
					return -1;
				}
			}
			Result = pSyser->m_pDebugger->WriteMemory(Address,Buffer,Length)==Length;
		}
		break;
	}
	if(!Result)
		OUTPUT_FAIL_TO_WRITE_MEM;
	UPDATE_CONTEXT();
	return 0;
}

int r_command(int argc, WCHAR *argv[ ],PCWSTR szCommandLine, CSyser*pSyser)
{
	CHAR szValueName[64];
	ULONG Value;
	ASSERT_DEBUGGER_OPENED
	if(argc<2)
	{
		OUTPUT_INPUT_ERROR;
		return -1;
	}
	if(argc>2)
	{
		if(CALCEXP(argv[2],&Value)==false)
		{
			OUTPUT_INVALID_PARAM;
			return -1;
		}
		UnicodeToAnsi(argv[1],szValueName,sizeof(szValueName));
		if(gpSyser->m_SyserUI.m_CodeDoc.SetPtrValue(szValueName,Value)==false)
		{
			OUTPUT_INVALID_PARAM;
			return -1;
		}
		gpSyser->m_pDebugger->SaveRegister();
		UPDATE_CONTEXT();
	}
	else
	{
		if(CALCEXP(argv[1],&Value)==false)
		{
			OUTPUT_INVALID_PARAM;
			return -1;
		}
		OUTPUT(WSTR("%s = %X\n"),argv[1],Value);
	}
	return 0;
}

int m_command(int argc,WCHAR *argv[],PCWSTR szCommandLine,CSyser *pSyser)
{
	DWORD SourceAddress,SourceLen,DestAddress,MoveLen;
	if(argc!=4)
	{
		OUTPUT_COMMAND_USAGE;
		return -1;
	}
	if(CALCEXP(argv[1],&SourceAddress)==false || CALCEXP(argv[3],&DestAddress)==false)
	{
		OUTPUT_INVALID_ADDRESS;
		return -1;
	}
	if(CALCEXP(argv[2],&SourceLen)==false)
	{
		OUTPUT(WSTR("Error : Invalid Length !\n"));
		return -1;
	}
	if(SourceLen>0x10000)
	{
		OUTPUT(WSTR("Error : Length too large !\n"));
		return -1;
	}
	MoveLen = gpSyser->m_pDebugger->MoveMem(DestAddress,SourceAddress,SourceLen); 
	OUTPUT(WSTR("%X bytes moved !\n"),MoveLen);
	UPDATE_CONTEXT();
	return 0;
}


int c_command(int argc, WCHAR *argv[],PCWSTR szCommandLine,CSyser *pSyser)
{
	DWORD SourceAddress,SourceLen,DestAddress,CmpLen;
	if(argc!=4)
	{
		OUTPUT_COMMAND_USAGE;
		return -1;
	}
	if(CALCEXP(argv[1],&SourceAddress)==false || CALCEXP(argv[3],&DestAddress)==false)
	{
		OUTPUT_INVALID_ADDRESS;
		return -1;
	}
	if(CALCEXP(argv[2],&SourceLen)==false)
	{
		OUTPUT(WSTR("Error : Invalid Length !\n"));
		return -1;
	}
	if(SourceLen>0x10000)
	{
		OUTPUT(WSTR("Error : Length too large !\n"));
		return -1;
	}
	CmpLen = gpSyser->m_pDebugger->CmpMem(DestAddress,SourceAddress,SourceLen); 
	OUTPUT(WSTR("%X bytes is same!\n"),CmpLen);
	return 1;
}


int f_command(int argc,WCHAR *argv[],PCWSTR szCommandLine,CSyser *pSyser)
{
	BYTE Buffer[256];
	PCWSTR szValue;
	int BufSize,MemLength,Len,nFilled;
	ULPOS Address;
	if(argc<4)
	{
		OUTPUT_COMMAND_USAGE;
		return -1;
	}
	if(CALCEXP(argv[1],&Address)==false)
	{
		OUTPUT_INVALID_ADDRESS;
		return -1;
	}
	if(CALCEXP(argv[2],(ULSIZE*)&MemLength)==false)
	{
		OUTPUT_INVALID_PARAM;
		return -1;
	}
	szValue = &szCommandLine[argv[3]-argv[0]];
	if(*szValue=='"'||*szValue=='\'')
	{
		szValue++;
		BufSize=0;
		while(szValue[BufSize] && szValue[BufSize]!='"'&& *szValue!='\'' && BufSize<sizeof(Buffer)-1)
		{
			Buffer[BufSize]=(BYTE)szValue[BufSize];
			BufSize++;
		}
		Buffer[BufSize++]=0;
	}
	else
	{
		BufSize = THexStrToBytes(szValue,Buffer,sizeof(Buffer));
		if(BufSize==0)
		{
			OUTPUT_INVALID_PARAM;
			return -1;
		}
	}
	nFilled = 0;
	while(MemLength>0)
	{
		Len = MemLength>BufSize ? BufSize:MemLength;
		if(pSyser->m_pDebugger->WriteMemory(Address+nFilled,Buffer,Len)!=Len)
			break;
		nFilled+=Len;
		MemLength-=Len;
	}
	OUTPUT(WSTR("%d Byte(s) filled !\n"),nFilled);
	UPDATE_CONTEXT();
	//UPDATE_MEMORY_VIEW();
	return 0;
}

int s_command(int argc,WCHAR *argv[],PCWSTR szCommandLine,CSyser *pSyser)
{
	static ULPOS	PrevAddress = 0;
	static ULSIZE	PrevLength = 0;
	static BYTE		SearchBuffer[256];
	static int		SearchBufSize;
	static int		ShowMode=0;
	static int		OrgShowMode=0;
	PCWSTR szValue;
	int MemLength;
	ULPOS Address,ResAddr;
	if(argc<4)
	{
		if(argc==1 && PrevLength>0)
		{
			Address = PrevAddress;
			MemLength = PrevLength;
			goto ContinueSearch;
		}
		OUTPUT_COMMAND_USAGE;
		return -1;
	}
	switch(argv[0][1])
	{
	case 0:
	case 'd':
	case 'D':
		OrgShowMode=0;
		break;
	case 'c':
	case 'C':
		OrgShowMode=1;
		break;
	}
	ShowMode=OrgShowMode;
	if(CALCEXP(argv[1],&Address)==false)
	{
		OUTPUT_INVALID_ADDRESS;
		return -1;
	}
	if(CALCEXP(argv[2],(ULSIZE*)&MemLength)==false)
	{
		OUTPUT_INVALID_PARAM;
		return -1;
	}
	szValue = &szCommandLine[argv[3]-argv[0]];
	if(*szValue=='"'||*szValue=='\'')
	{
		szValue++;
		SearchBufSize=0;
		while(szValue[SearchBufSize] && szValue[SearchBufSize]!='"'&& szValue[SearchBufSize]!='\'' && SearchBufSize<sizeof(SearchBuffer)-1)
		{
			SearchBuffer[SearchBufSize]=(BYTE)szValue[SearchBufSize];
			SearchBufSize++;
		}
		SearchBuffer[SearchBufSize]=0;
	}
	else
	{
		SearchBufSize = THexStrToBytes(szValue,SearchBuffer,sizeof(SearchBuffer));
		if(SearchBufSize==0)
		{
			OUTPUT_INVALID_PARAM;
			return -1;
		}
	}
ContinueSearch:
	ResAddr = gpSyser->m_pDebugger->SearchMem(Address,MemLength,SearchBuffer,SearchBufSize);
	if(ResAddr!=-1)
	{
		switch(argv[0][1])
		{
		case 0:
			ShowMode=OrgShowMode;
			break;
		case 'd':
		case 'D':
			ShowMode=0;
			break;
		case 'c':
		case 'C':
			ShowMode=1;
			break;
		}
		OUTPUT(WSTR("Found at %08X\n"),ResAddr);
		PrevAddress = ResAddr+1;
		PrevLength = MemLength-(PrevAddress-Address);
		if(ShowMode==1)
			VIEW_CODE(ResAddr,true);
		else
			VIEW_DATA(ResAddr,SearchBufSize);
	}
	else
	{
		PrevLength = 0;
		OUTPUT(WSTR("Couldn't found in range!\n"));
	}
	return 0;
}

int seg_command(int argc, WCHAR *argv[ ],PCWSTR szCommandLine, CSyser*pSyser)
{
	int SegIndex,SelectIndex;
	DWORD Value=0;
	ASSERT_DEBUGGER_OPENED
	if(argc!=2)
	{
		OUTPUT(WSTR("Usage : seg segment_name\n"));
		return 1;
	}
	for(SegIndex=0;SegIndex<sizeof(CInstrSym::m_SegStr)/sizeof(PCWSTR);SegIndex++)
	{
		if(TStrICmp(argv[1],CInstrSym::m_SegStr[SegIndex])==0)
			break;
	}
	if(SegIndex>=sizeof(CInstrSym::m_SegStr)/sizeof(PCWSTR))
	{
		OUTPUT(WSTR("Error : %<3>Input error !\n"));
		return 1;
	}
	switch(SegIndex)
	{
	case 0:
		SelectIndex = *X86_REG_PTR.pES;
		break;
	case 1:
		SelectIndex = *X86_REG_PTR.pCS;
		break;
	case 2:
		SelectIndex = *X86_REG_PTR.pSS;
		break;
	case 3:
		SelectIndex = *X86_REG_PTR.pDS;
		break;
	case 4:
		SelectIndex = *X86_REG_PTR.pFS;
		break;
	case 5:
		SelectIndex = *X86_REG_PTR.pGS;
		break;
	}	
	if(pSyser->m_pDebugger->GetSegRegBase(SelectIndex,&Value)==false)
		OUTPUT(WSTR("Seg %s isn't present !\n"),CInstrSym::m_SegStr[SegIndex]);
	else
		OUTPUT(WSTR("Seg %s : Base %08X\n"),CInstrSym::m_SegStr[SegIndex],Value);
	return 0;
}

int sym_command(int argc,WCHAR *argv[],PCWSTR szCommandLine,CSyser *pSyser)
{
	int Count=0;
	char szSym[MAX_SYMBOL_LEN],szModule[MAX_FN_LEN];
	WCHAR szBuffer[MAX_SYMBOL_LEN],szModuleName[MAX_FN_LEN];
	bool bOk=false;
	DWORD Value;
	CSymbolModule*pSymbolModule;
	if(argc==4)
	{
		if(TStrICmp(argv[1],"-a")==0 || TStrICmp(argv[1],"/a")==0)
		{
			UnicodeToAnsi(argv[2],szSym,sizeof(szSym));
			if(CALCEXP(argv[3],&Value))
			{
				CDbgModule*pDbgModule = pSyser->m_pDebugger->m_ModuleList.GetModule(Value);
				if(pDbgModule==NULL)
					pDbgModule = pSyser->m_pSysDebugger->m_ModuleList.GetModule(Value);
				if(pDbgModule!=NULL)
				{
					if(pDbgModule->m_pSymbolModule==NULL)					
					{
						pSymbolModule = gpSyser->m_SyserUI.m_SymbolContainer.InsertSymbolModule(pDbgModule->m_ModuleID);
						if(pSymbolModule)
							pSymbolModule->m_ModuleName = pDbgModule->m_ModuleName;
						if(pDbgModule)
							pDbgModule->AttachSymbolModule(pSymbolModule);												
					}
					bOk = pDbgModule->m_pSymbolModule->SetSymbol(Value-pDbgModule->m_ModuleBase,szSym);
				}
				else
				{
					bOk=gpSyser->m_SyserUI.m_CodeDoc.InsertConstSym(szSym,Value);
					//OUTPUT(WSTR("Error : Can't find this module locate on %08X\n"),Value);
				}
			}
			else
			{
				OUTPUT(WSTR("Error : %s input error!\n"),argv[3]);
			}
		}
		if(bOk)
			OUTPUT(WSTR("Add '%s' ==> %08x succeed\n"),argv[2],Value);
		else
			OUTPUT(WSTR("Error : Add symbols error!\n"),argv[2],Value);
		return 0;
	}
	
	if(argc<=1)
	{
		OUTPUT(WSTR("symbols ModuleName\n"));
		for(CSymbolContainer::IT Iter = gpSyser->m_SyserUI.m_SymbolContainer.Begin();Iter.IsExist();Iter++)
		{
			if(Iter->m_ModuleName.IsEmpty())
				TStrCpy(szModuleName,"<No Name>");
			else
				AnsiToUnicode((PCSTR)Iter->m_ModuleName,szModuleName,MAX_FN_LEN);
			OUTPUT(WSTR("%-5d   %s\n"),Iter->m_SymbolMap.Count(),TGetFileName(szModuleName));
		}
		return 0;
	}
	if(argc==2)
	{
		UnicodeToAnsi(argv[1],szSym,sizeof(szSym));
		*szModule=0;
	}
	else
	{
		UnicodeToAnsi(argv[1],szModule,sizeof(szModule));
		UnicodeToAnsi(argv[2],szSym,sizeof(szSym));
	}
	for(CSymbolContainer::IT ModeIter = gpSyser->m_SyserUI.m_SymbolContainer.Begin();ModeIter.IsExist();ModeIter++)
	{
		if(ModeIter->m_ModuleBase && (TCmpModuleName((PCSTR)ModeIter->m_ModuleName,szModule) || *szModule==0))
		{
			for(CSymbolMap::IT Iter = ModeIter->m_SymbolMap.Begin();Iter.IsExist();Iter++)
			{
				if(TIMatchWithPattern(szSym,(PCSTR)*Iter))
				{
					AnsiToUnicode(*Iter,szBuffer,MAX_SYMBOL_LEN);
					if(ModeIter->m_ModuleName.IsEmpty())
						TStrCpy(szModuleName,"<No Name>");
					else
						AnsiToUnicode((PCSTR)ModeIter->m_ModuleName,szModuleName,MAX_FN_LEN);
					OUTPUT(WSTR("%<B>%08X %<1>: %<F>%s  %<1><%s>\n"),Iter.Key()+ModeIter->m_ModuleBase,szBuffer,TGetFileName(szModuleName));
					Count++;
				}
			}
		}
	}
	for(CDbgModuleMap::IT ModeIter=gpSyser->m_pDebugger->m_ModuleList.m_DbgModuleMap.Begin();ModeIter.IsExist();ModeIter++)
	{
		if(ModeIter->m_pSymbolModule&&ModeIter->m_pSymbolModule->m_ModuleBase==0&&(TCmpModuleName((PCSTR)ModeIter->m_ModuleName,szModule) || *szModule==0))
		{
			for(CSymbolMap::IT Iter = ModeIter->m_pSymbolModule->m_SymbolMap.Begin();Iter.IsExist();Iter++)
			{
				if(TIMatchWithPattern(szSym,(PCSTR)*Iter))
				{
					AnsiToUnicode(*Iter,szBuffer,MAX_SYMBOL_LEN);
					if(ModeIter->m_pSymbolModule->m_ModuleName.IsEmpty())
						TStrCpy(szModuleName,"<No Name>");
					else
						AnsiToUnicode((PCSTR)ModeIter->m_pSymbolModule->m_ModuleName,szModuleName,MAX_FN_LEN);
					OUTPUT(WSTR("%<B>%08X %<1>: %<F>%s  %<1><%s>\n"),Iter.Key()+ModeIter->m_ModuleBase,szBuffer,TGetFileName(szModuleName));
					Count++;
				}
			}
		}
	}
	if(gpSyser->m_pDebugger != gpSyser->m_pSysDebugger)
	{
		for(CDbgModuleMap::IT ModeIter=gpSyser->m_pSysDebugger->m_ModuleList.m_DbgModuleMap.Begin();ModeIter.IsExist();ModeIter++)
		{
			if(ModeIter->m_pSymbolModule&&ModeIter->m_pSymbolModule->m_ModuleBase==0&&(TCmpModuleName((PCSTR)ModeIter->m_ModuleName,szModule) || *szModule==0))
			{
				for(CSymbolMap::IT Iter = ModeIter->m_pSymbolModule->m_SymbolMap.Begin();Iter.IsExist();Iter++)
				{
					if(TIMatchWithPattern(szSym,(PCSTR)*Iter))
					{
						AnsiToUnicode(*Iter,szBuffer,MAX_SYMBOL_LEN);
						if(ModeIter->m_pSymbolModule->m_ModuleName.IsEmpty())
							TStrCpy(szModuleName,"<No Name>");
						else
							AnsiToUnicode((PCSTR)ModeIter->m_pSymbolModule->m_ModuleName,szModuleName,MAX_FN_LEN);
						OUTPUT(WSTR("%<B>%08X %<1>: %<F>%s  %<1><%s>\n"),Iter.Key()+ModeIter->m_ModuleBase,szBuffer,TGetFileName(szModuleName));
						Count++;
					}
				}
			}
		}
	}
	OUTPUT(WSTR("%d Symbol(s)\n"),Count);
	return 0;
}

int symmod_command(int argc,WCHAR *argv[],PCWSTR szCommandLine,CSyser *pSyser)
{
	WCHAR szBuffer[MAX_FN_LEN];
	CSymbolContainer::IT Iter;
	int Count=0;
	OUTPUT(WSTR("Ref  SymbolCount FullFileName\n"));
	Iter = gpSyser->m_SyserUI.m_SymbolContainer.Begin();
	while(Iter.IsExist())
	{
		if(Iter->m_SymbolMap.Count())
		{
			AnsiToUnicode(Iter->m_ModuleName,szBuffer,MAX_FN_LEN);
			OUTPUT(WSTR("%-4d %-8d    %s\n"),Iter->m_ReferenceCount,Iter->m_SymbolMap.Count(),szBuffer);
			Count++;
		}
		Iter++;
	}
	OUTPUT(WSTR("%d Module(s)\n"),Count);
	return 0;
}

int sdsmod_command(int argc,WCHAR *argv[],PCWSTR szCommandLine,CSyser *pSyser)
{
	WCHAR szBuffer[MAX_FN_LEN];
	CSDSModuleMap::IT Iter;
	int Count=0;
	Iter = gpSyser->m_SyserUI.m_SDSModuleMap.Begin();
	while(Iter.IsExist())
	{
		if(Count==0)
			OUTPUT(WSTR("File BP(s) Size(k) CheckSum TimeStamp ModuleName\n"));
		AnsiToUnicode(Iter->m_ModuleFileName,szBuffer,MAX_FN_LEN);
		OUTPUT(WSTR("%-4d %7dk %08X %08X  %s\n"),Iter->m_BreakPointList.Count(),Iter->m_MemoryUsed/1024,
				Iter->m_SDSymbolFile->ModuleID.OrgPECheckSum,Iter->m_SDSymbolFile->ModuleID.TimeDateStamp,szBuffer);
		Count++;
		Iter++;
	}
	OUTPUT(WSTR("%d Module(s)\n"),Count);
	return 0;
}
char* TimeDateStampToString(DWORD TimeDateStamp,char* TimeString);
void DispModuleInfo(CDbgModule*pModule)
{
	char TimeDateStamp[30];
	WCHAR wTimeDateStamp[30];
	TimeDateStampToString(LOW_DWORD(pModule->m_ModuleID)-gpSyser->m_TimeZoneBias,TimeDateStamp);
	TStrCpy(wTimeDateStamp,TimeDateStamp);
	WCHAR szTitle[MAX_FN_LEN],szFullName[MAX_FN_LEN];
	AnsiToUnicode(pModule->m_ModuleTitle,szTitle,MAX_FN_LEN);
	AnsiToUnicode(pModule->m_ModuleFullName,szFullName,MAX_FN_LEN);
	OUTPUT(WSTR("%-20s %08X  %08X  %08X %-20s%s\n"),szTitle,pModule->m_ModuleBase,pModule->m_ModuleSize,HIGH_DWORD(pModule->m_ModuleID),wTimeDateStamp,szFullName);
}

int mod_command(int argc, WCHAR *argv[],PCWSTR szCommandLine,CSyser*pSyser)
{
	WCHAR szBuffer[MAX_FN_LEN];
	DWORD i=0;
	DWORD Address=0xffffffff;
	int TmpIndex=1;
	DWORD dwType=0;
	if(argc==1)
	{
		OUTPUT(WSTR("ModuleName           ImageBase ImageSize CheckSum TimeStamp           FullFileName\n"));
		for(CDbgModuleMap::IT Iter=pSyser->m_pDebugger->m_ModuleList.m_DbgModuleMap.Begin();Iter!=pSyser->m_pDebugger->m_ModuleList.m_DbgModuleMap.End();Iter++)
		{
			DispModuleInfo(&(*Iter));
			i++;
		}
		return 0;
	}

	if(TStrCmp(argv[1],"-u")==0)
	{
		dwType=1;
	}else if(TStrCmp(argv[1],"-s")==0)
	{
		dwType=2;
	}
	if(dwType)
	{
		TmpIndex++;
	}
	if(argc>(int)TmpIndex&& CALCEXP(argv[TmpIndex],&Address))
	{
		CDbgModule*pDbgModule = pSyser->m_pSysDebugger->m_ModuleList.GetModule(Address);
		if(pDbgModule==NULL)
			pDbgModule = pSyser->m_pDebugger->m_ModuleList.GetModule(Address);
		if(pDbgModule==NULL)
		{
			OUTPUT(WSTR("Error : Can't find this module locate on %08X\n"),Address);
			return 1;
		}
		OUTPUT(WSTR("ModuleName           ImageBase ImageSize FullFileName\n"));
		DispModuleInfo(pDbgModule);
	}
	else
	{
		OUTPUT(WSTR("ModuleName           ImageBase ImageSize FullFileName\n"));
		if(pSyser->m_pSysDebugger!=pSyser->m_pDebugger)
		{
			if(dwType!=2)
			{
				for(CDbgModuleMap::IT Iter=pSyser->m_pDebugger->m_ModuleList.m_DbgModuleMap.Begin();Iter!=pSyser->m_pDebugger->m_ModuleList.m_DbgModuleMap.End();Iter++)
				{
					if(argc>TmpIndex)
					{
						AnsiToUnicode(Iter->m_ModuleFullName,szBuffer,MAX_FN_LEN);
						for(int n = TmpIndex;n<argc;n++)
						{
							if(TCmpModuleName(szBuffer,argv[n]) || TIMatchWithPattern(argv[n],TGetFileName(szBuffer)))
							{
								DispModuleInfo(&(*Iter));
							}
						}
					}
					else
					{
						DispModuleInfo(&(*Iter));
					}
				}
			}
		}
		if(dwType!=1)
		{
			for(CDbgModuleMap::IT Iter=pSyser->m_pSysDebugger->m_ModuleList.m_DbgModuleMap.Begin();Iter!=pSyser->m_pSysDebugger->m_ModuleList.m_DbgModuleMap.End();Iter++)
			{
				if(argc>TmpIndex)
				{
					AnsiToUnicode(Iter->m_ModuleFullName,szBuffer,MAX_FN_LEN);
					for(int n = TmpIndex;n<argc;n++)
					{
						if(TCmpModuleName(szBuffer,argv[n]) || TIMatchWithPattern(argv[n],TGetFileName(szBuffer)))
						{
							DispModuleInfo(&(*Iter));
						}
					}
				}
				else
					DispModuleInfo(&(*Iter));
			}
		}
	}
	return 0;
}

int test_command11(int argc,WCHAR *argv[],PCWSTR szCommandLine,CSyser *pSyser)
{
//	CBeaEngine Engine;
//	DISASM MyDisasm;
//	char buf1[1024];
//	WCHAR buffer[256];
//	int i = 0,j=0;
//	DWORD Address;
//
//
//	__asm
//	{
//		call local_1
//		
//		add eax,Address	
//		
//		lock _emit(0x66)
//		_emit(0xf)
//		_emit(0x38)
//		_emit(0x15)
//		nop 
//		nop 
//		nop
//		nop
//		nop 
//		nop 
//		nop
//		nop
//		lock xchg eax,Address
//		xchg Address,eax
//		mov eax,es:[ebx]
//local_1:
//		pop DWORD ptr [Address] 
//		mov eax,0xff 
//		
//		
//
//	}
//	//Address = (DWORD)buf1;
//	memset(&MyDisasm,0,sizeof(MyDisasm));
//	MyDisasm.Options=Tabulation|MasmSyntax|ShowSegmentRegs;
//	MyDisasm.EIP = (__int64)Address;
//	MyDisasm.VirtualAddr=Address;
//
//	/* ============================= Loop for Disasm */
//	while(i<0x200)
//	{
//		MyDisasm.EIP+=j;
//		MyDisasm.VirtualAddr+=j;
//		j=Engine.Disasm(&MyDisasm);
//		
//		i+=j;
//		{
//			TStrCpy(buffer,MyDisasm.CompleteInstr);
//
//			OUTPUT(WSTR("%08X %s        [%d][%x] [%d][%d][%d]\n"),(int)MyDisasm.EIP, buffer,j,MyDisasm.Instruction.Opcode,MyDisasm.Prefix.Number,MyDisasm.Prefix.LockPrefix,MyDisasm.Prefix.OperandSize);
//		}
//	}
	
	return 0;
}