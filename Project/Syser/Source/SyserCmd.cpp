#include "StdAfx.h"
#include "Syser.h"
#include "SyserCmd.h"
#include "VideoDriver.h"
#include "DbgProcess.h"
#include "TimerInterrupt.h"
#include "IOAPIC.h"
#include "HardWareInterruptCtrl.h"
#include "PIC_8259.h"
#include "UHCIDevice.h"
#include "LocalAPIC.h"
#include "Dump.h"
#include "cmd_cpuid.h"
#include "cmd_cpu.h"
#include "HwndCmd.h"
#include "OSProcessThread.h"

int get_do_command_string(int argc, WCHAR *argv[ ],PCWSTR szCommandLine,char* szDoCmd,int MaxSize);
int get_command_condition_string(int argc, WCHAR *argv[ ],PCWSTR szCommandLine,char* szCondition,int MaxSize);
const WCHAR cmd_faults_usage[]=
{
	L"faults: Turn fault trapping on or off.\n"
	L"format: faults [ on | off ]\n"
	L"Example1: faults on\n"
};

const WCHAR cmd_bpint_usage[]=
{
	L"bpint: Set interrupt breakpoint\n"
	L"format: bpint interrupt_index\n"
	L"Example1: bpint 2e\n"
};

const WCHAR cmd_bpr_usage[]=
{
	L"bpr: Set breakpoint at the range of memory(only support memory address < 2G)\n"
	L"format: bpr process-type address length r|w|rw|x [if ...] [do ...]\n"
	L"Example1: bpr notepad eip 800 x\n"
	L"Example2: bpr 144 404000 3000 w\n"
	L"Example3: bpr 82023D78 7c004000 3000 w\n"
};

const WCHAR cmd_handle_usage[]=
{
	L"handle: Displays information about a handle or handles that one or all processes .\n"
	L"format: handle [handle | 0] [process-type]\n"
	L"Example1: handle 4\n"
	L"Example2: handle 4 idle\n"
	L"Example3: handle 0 idle\n"
};

const WCHAR cmd_dt_usage[]=
{
	L"dt: Displays information about a local variable, global variable or data type. This can display information about simple data types, as well as structures and unions.\n"
	L"format: dt Typename [address]\n"
	L"Example1: dt _ETHREAD\n"
	L"Example2: dt _EPROCESS 804d5788\n"	
};

const WCHAR cmd_apic_usage[]=
{
	L"apic: Dump local apic information\n"
	L"Format: apic\n"
};

const WCHAR cmd_ioapic_usage[]=
{
	L"ioapic: Dump ioapic information\n"
	L"Format: ioapic\n"
};

const WCHAR cmd_addr_usage[]=
{
	L"addr: Change process address space\n"
	L"Format: addr [process_id][process_name][cr3]\n"
	L"Example1: addr 0004         (switch to process which PID is 0004)\n"
	L"Example2: addr calc         (switch to process calc)\n"
	L"Example3: addr 36000        (switch to process which CR3 is 36000)\n"
};
const WCHAR cmd_i3here_usage[]=
{
	L"i3here : Direct INT3 to Syser\n"
	L"Format: i3here [ on | off | drv ]\n"
	L"Example1: i3here on\n"
};
const WCHAR cmd_proc_usage[]=
{
	L"proc: List processes in system\n"
	L"Format: proc\n"
};

const WCHAR cmd_cpu_usage[]=
{
	L"cpu: Display cpu information\n"
	L"Format: cpu [cpu_index] [ cr0 | cr3 | cr4 | efl ]\n"
	L"Example1: cpu 0\n"
	L"Example2: cpu 0 cr0 cr4\n"
	L"Example3: cpu efl\n"
};

const WCHAR cmd_cpuid_usage[]=
{
	L"cpuid: Display CPUID information\n"
	L"Format: cpuid\n"
};

const WCHAR cmd_idt_usage[]=
{
	L"idt: Display IDT information\n"
	L"Format: idt [idt_index]\n"
	L"Example1: idt 8\n"
};

const WCHAR cmd_gdt_usage[]=
{
	L"gdt: Display GDT information\n"
	L"Format: gdt [gdt_sel]\n"
	L"Example1: gdt 30\n"
};

const WCHAR cmd_phys_usage[]=
{
	L"phys: Convert physical address to virtual address\n"
	L"Format: phys [physical_address]\n"
	L"Example1: phys 1100000\n"
};

const WCHAR cmd_page_usage[]=
{
	L"page: Convert virtual address to physical address\n"
	L"Format: page [virtual_address]\n"
	L"Example1: page 401000\n"
};

const WCHAR cmd_tss_usage[]=
{
	L"tss: Display task state segment\n"
	L"Format: tss\n"
};

const WCHAR cmd_dump_usage[]=
{
	L"dump: dump Bin data to file\n"
	L"Format: dump address length dump_file_name\n"
	L"Examle: dump 401000 1000 C:\\dump.bin\n"
};

const WCHAR cmd_makepe_usage[]=
{
	L"makepe: dump PE module to file\n"
	L"Format: makepe module_name dump_file_name\n"
	L"Examle: makepe kernel32 C:\\kernel32.dll\n"
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



SYSER_CMD_ENTRY	SysCmdTable[]=
{
	{WSTR("apic"),		WSTR("Dump local apic"),									localapic_command,			cmd_apic_usage},
	{WSTR("ioapic"),	WSTR("Dump io apic"),										ioapic_command,				cmd_ioapic_usage},
	{WSTR("export"),	WSTR("Display Module export function"),						export_command},
	{WSTR("addr"),		WSTR("Display/change process context"),						addr_command,				cmd_addr_usage},
	{WSTR("proc"),		WSTR("Display process information"),						proc_command,				cmd_proc_usage},
	{WSTR("ver"),		WSTR("Show WinSyser Version"),								ver_command},
	{WSTR("i"),			WSTR("Input data form I/O port"),							ib_command},
	{WSTR("ib"),		WSTR("Input data form I/O port"),							ib_command},
	{WSTR("iw"),		WSTR("Input data form I/O port"),							ib_command},
	{WSTR("id"),		WSTR("Input data form I/O port"),							ib_command},
	{WSTR("o"),			WSTR("Output data to I/O port"),							ob_command},
	{WSTR("ob"),		WSTR("Output data to I/O port"),							ob_command},
	{WSTR("ow"),		WSTR("Output data to I/O port"),							ob_command},
	{WSTR("od"),		WSTR("Output data to I/O port"),							ob_command},
	{WSTR("makepe"),	WSTR("dump PE Module to file"),								makepe_command,				cmd_makepe_usage},
	{WSTR("dump"),		WSTR("dump Bin data to file"),								dump_command,				cmd_dump_usage},
	/////////////////////////////////////////////////////////////////////////////////////////////////////////////
	//系统数据类
	{WSTR("idt"),		WSTR("Display interrupt descriptor table"),					idt_command,				cmd_idt_usage},
	{WSTR("gdt"),		WSTR("Display global descriptor table"),					gdt_command,				cmd_gdt_usage},
	{WSTR("ldt"),		WSTR("Display local descriptor table"),						ldt_command},
	{WSTR("cpuid"),		WSTR("Show CPUID Information"),								cpuid_command,				cmd_cpuid_usage},
	{WSTR("cpu"),		WSTR("Show cpu register"),									cpu_command,				cmd_cpu_usage},
	{WSTR("page"),		WSTR("Display page table information"),						page_command,				cmd_page_usage},
	//系统数据类
	/////////////////////////////////////////////////////////////////////////////////////////////////////////////
	{WSTR("bpint"),		WSTR("Breakpoint on interrupt"),							bpint_command},
	{WSTR("pci"),		WSTR("Dump PCI information"),								pci_command},
	{WSTR("ignore"),	WSTR("return to default exception handler"),				ignore_command},
	{WSTR("faults"),	WSTR("Turn fault trapping on or off."),						faults_command,				cmd_faults_usage},
	{WSTR("phys"),		WSTR("Display all virtual addresses for physical address"),	phys_command,				cmd_phys_usage},
	{WSTR("tss"),		WSTR("Display task state segment"),							tss_command,				cmd_tss_usage},
	{WSTR("irq"),		WSTR("Display hardware IRQ Information"),					irq_command},
	{WSTR("msr"),		WSTR("Display Model Specific Register information"),		msr_command},
	{WSTR("peek"),		WSTR("Read from physical address"),							peekb_command},
	{WSTR("peekb"),		WSTR("Read from physical address"),							peekb_command},
	{WSTR("peekw"),		WSTR("Read from physical address"),							peekb_command},
	{WSTR("peekd"),		WSTR("Read from physical address"),							peekb_command},
	{WSTR("poke"),		WSTR("Write to physical address"),							pokeb_command},
	{WSTR("pokeb"),		WSTR("Write to physical address"),							pokeb_command},
	{WSTR("pokew"),		WSTR("Write to physical address"),							pokeb_command},
	{WSTR("poked"),		WSTR("Write to physical address"),							pokeb_command},
	{WSTR("ntcall"),	WSTR("Display NTOSKRNL system calls"),						ntcall_command},
	{WSTR("ntcall2"),	WSTR("Display WIN32K system calls"),						ntcall2_command},	
	{WSTR("usb"),		WSTR("Display USB device or transaction information"),		usb_command},
	{WSTR("objdir"),	WSTR("Display info about an object directory"),				objdir_command},
	{WSTR("device"),	WSTR("Display info about a device"),						device_command},
	{WSTR("driver"),	WSTR("Display info about a driver"),						driver_command},
	{WSTR("kmutex"),	WSTR("Display info about a Kernel Mutex"),					kmutex_command},
	{WSTR("kevent"),	WSTR("Display info about a Kernel Event"),					kevent_command},
	{WSTR("ksem"),		WSTR("Display info about a Kernel Semaphore"),				ksem_command},
	{WSTR("i1here"),	WSTR("Direct INT1 to Syser"),								i1here_command},
	{WSTR("i3here"),	WSTR("Direct INT3 to Syser"),								i3here_command,cmd_i3here_usage},
	{WSTR("genint"),	WSTR("Generate an interrupt"),								genint_command},
	{WSTR("hboot"),		WSTR("Forces the system to reboot"),		 				hboot_command},
	{WSTR("wf1"),		WSTR("Display FPU Register Informat"),						wf1_command},
	{WSTR("center"),	WSTR("center syser windows"),								window_center_command},
	{WSTR("vad"),		WSTR("Displays details of the virtual address descriptor (VAD) for one or more virtual addresses"),			vad_command},
	{WSTR("pte"),		WSTR("Displays the page table entry (PTE) and page directory entry (PDE) for the specified address"),		pte_command},
	{WSTR("DispInfo"),	WSTR("Show Display Information"),							dispinfo_command},
	{WSTR("uhcil"),		WSTR("Display UHCI QH or TD Pointed by Link"),				uhci_link_command},
	{WSTR("ohcied"),	WSTR("Display OHCI ED Struct Info"),						ohci_ed_command},
	{WSTR("Plugin"),	WSTR("Display Syser Plugin List"),							plugin_command},
	{WSTR("thread"),	WSTR("Display thread information"),							thread_command},
	{WSTR("objtab"),	WSTR("Display user object table"),							objtab_command},
	{WSTR("bpt"),		WSTR("Set breakpoint at thread"),							bpt_command},
	{WSTR("bpp"),		WSTR("Set breakpoint at process"),							bpp_command},
	//{WSTR("softice"),	WSTR("Active SoftIce"),										activesoftice_command},
	//{WSTR("ikey"),		WSTR("keyboard input to softice"),							ikey_command},
	//{WSTR("pagein"),	WSTR("Load a page into physical memory"),					pagein_command},
	//{WSTR("beep"),		WSTR("Beep"),												beep_command},
	//{WSTR("sysertest"),	WSTR("sysertest"),											sysertest},
	{WSTR("hwnd"),		WSTR("Display window handle information"),					hwnd_command,cmd_hwnd_usage},
	//{WSTR("test111"),		WSTR("test write memory command"),							test_command},
	//{WSTR("testr"),		WSTR("test read memory command"),							test_command},
	{WSTR("drm"),		WSTR("Set Debug Register Access BreakPoint"),				DebugRegisterMonitor_command},
	{WSTR("syserheapinfo"),	WSTR("Display syser heap information"),					syserheapinfo_command},
	{WSTR("shutdown"),	WSTR("shutdown PC"),										acpi_shutdown_command},
	{WSTR("exitproc"),	WSTR("Terminate Current Process"),								TerminateProcess_command},
	{WSTR("bmsg"),	WSTR("Breakpoint on Window message"),								bmsg_command, cmd_bmsg_usage},
	
	{WSTR("do"),	WSTR("Display data auto add offset value to start address"),										d_softice_command},
	{WSTR("uo"),	WSTR("Unassemble instructions auto add offset value to start address"),								u_softice_command},
	{WSTR("so"),	WSTR("Set 'do','uo' command offset value"),								set_softice_baseaddress_command},
	{WSTR("handle"),	WSTR("Displays information about a handle or handles that one or all processes"),								handle_command,cmd_handle_usage},
	{WSTR("dt"),	WSTR("Displays information about a handle or handles that one or all processes"),								dt_command,cmd_handle_usage},
	//{WSTR("bpr"),	WSTR("Set breakpoint at the range of memory(only support memory address < 2G)"),								bpr_command,cmd_bpr_usage},
	{WSTR("lastbranch"),	WSTR("Display last branch MSR register information"),								lastbranch_command},	
	
	///////////////////////////////////////////////////////
	{NULL,NULL,NULL}
};

int beep_command(int argc,WCHAR *argv[],PCWSTR szCommandLine,CSyser *pSyser)
{	
	DWORD Counter=10 ,frequency=0;
	if(argc>1)
		if(CALCEXP(argv[1],&Counter)==FALSE)
			Counter = 10;
	if(argc>2)
		if(CALCEXP(argv[2],&frequency)==FALSE)
			frequency = 0;
	Beep(Counter,frequency);
	return 0;
}

int wf1_command(int argc,WCHAR *argv[],PCWSTR szCommandLine,CSyser *pSyser)
{
	DWORD dwCR0;
	BYTE FpuReg[108];
	WORD wFpuState,wFpuControl,wFpuTagWord;
	DWORD* pPointer,dwFpuTop,dwType;
// 	__asm mov eax,cr0
// 	__asm mov dwCR0,eax

	dwCR0 = SyserGetCR0Reg();

	if((dwCR0 & 4) || (dwCR0 & 0x10) == 0)
		return 1;
// 	__asm clts
// 	__asm fnstsw word ptr [wFpuState]
// 	__asm fnstcw word ptr [wFpuControl]

	SyserCltr();
	SyserFnstsw(&wFpuState);
	SyserFnstcw(&wFpuControl);

	memset(FpuReg,0,sizeof(FpuReg));
	SyserFnsave(FpuReg);
	SyserFrstor(FpuReg);

// 	__asm fnsave BYTE PTR [FpuReg]
// 	__asm frstor BYTE PTR [FpuReg]

	wFpuTagWord = *(WORD *)(8+FpuReg);
	dwFpuTop = (wFpuState >> 11) & 7;
	OUTPUT(WSTR("FPU State = %04x FPU Control = %04x FPU Tag Word = %04x Top Index = %d\n"),wFpuState,wFpuControl,wFpuTagWord,dwFpuTop);
	switch(wFpuControl & 0x30) {
	case 0:
		OUTPUT(WSTR("24 Bit Precision\n"));
		break;
	case 0x10:
		OUTPUT(WSTR("Reserved\n"));
		break;
	case 0x20:
		OUTPUT(WSTR("53 Bit Precision\n"));
		break;
	case 0x30:
		OUTPUT(WSTR("64 Bit Precision\n"));
		break;
	default:
		break;
	}
	for(int i = 0,j=dwFpuTop; i < 8; i++,j++)
	{
		j = j % 8;
		dwType = (wFpuTagWord >> (j * 2))&3;
		pPointer = (DWORD *)(28+i*10+FpuReg);
		OUTPUT(WSTR("ST(%d) = %08x %08x Type = %d\n"),i,pPointer[1],pPointer[0],dwType);
	}
	return 0;
}

int ikey_command(int argc,WCHAR *argv[],PCWSTR szCommandLine,CSyser *pSyser)
{
	bKeytoSoftice ^= 1;
	return 0;
}

int peekb_command(int argc, WCHAR *argv[],PCWSTR szCommandLine,CSyser*pSyser)
{
	DWORD PhysicalAddress;
	DWORD* pPageTableItem,*dwPointer;
	WORD * wPointer;
	BYTE * bPointer;
	if(argc != 2|| CALCEXP(argv[1],&PhysicalAddress)==FALSE)
	{
		OUTPUT(WSTR("Error : %<3>Input error !\n"));
		return -1;
	}
	if(OwnerPageTabItemAddress == 0 && (dwPhysical_0_LinesAddress==0 || dwPhysical_0_LinesAddress== 0xffffffff))
	{	
		return 1;
	}
	pPageTableItem =*(DWORD **)&OwnerPageTabItemAddress;
	pPageTableItem[0] = ((PhysicalAddress & 0xfffff000) | 7);
// 	__asm
// 	{
// 		push eax
// 		mov eax,cr3 
// 		mov cr3,eax
// 		pop eax 
// 	}

	SyserFlushProcessInsCache();

	switch(argv[0][4])
	{
	case 0:
	case 'b':
	case 'B':
		bPointer = (BYTE*)(dwPhysical_0_LinesAddress|(PhysicalAddress&0xfff));
		OUTPUT(WSTR("%02x\n"),bPointer[0]);
		break;
	case 'w':
	case 'W':
		wPointer = (WORD*)(dwPhysical_0_LinesAddress|(PhysicalAddress&0xfff));
		OUTPUT(WSTR("%04x\n"),wPointer[0]);
		break;
	case 'd':
	case 'D':
		dwPointer = (DWORD*)(dwPhysical_0_LinesAddress|(PhysicalAddress&0xfff));
		OUTPUT(WSTR("%08x\n"),dwPointer[0]);
		break;
	}
	return 0;
}

int pokeb_command(int argc, WCHAR *argv[],PCWSTR szCommandLine,CSyser*pSyser)
{
	DWORD PhysicalAddress,dwValue;
	DWORD* pPageTableItem,*dwPointer;

	WORD * wPointer;
	BYTE * bPointer;
	if(argc != 3|| CALCEXP(argv[1],&PhysicalAddress)==FALSE || CALCEXP(argv[2],&dwValue)==FALSE)
	{
		OUTPUT(WSTR("Error : %<3>Input error !\n"));
		return -1;
	}
	if(OwnerPageTabItemAddress == 0 && (dwPhysical_0_LinesAddress==0 || dwPhysical_0_LinesAddress== 0xffffffff))
	{
		return 1;
	}
	pPageTableItem =*(DWORD **)&OwnerPageTabItemAddress;
	pPageTableItem[0] = ((PhysicalAddress & 0xfffff000) | 7);
// 	__asm
// 	{
// 		push eax
// 		mov eax,cr3
// 		mov cr3,eax
// 		pop eax
// 	}

	SyserFlushProcessInsCache();

	switch(argv[0][4])
	{
	case 0:
	case 'b':
	case 'B':
		bPointer = (BYTE*)(dwPhysical_0_LinesAddress|(PhysicalAddress&0xfff));
		bPointer[0]=(BYTE)dwValue;
		OUTPUT(WSTR("%02x\n"),bPointer[0]);
		break;
	case 'w':
	case 'W':
		wPointer = (WORD*)(dwPhysical_0_LinesAddress|(PhysicalAddress&0xfff));
		wPointer[0]=(WORD)dwValue;
		OUTPUT(WSTR("%04x\n"),wPointer[0]);
		break;
	case 'd':
	case 'D':
		dwPointer = (DWORD*)(dwPhysical_0_LinesAddress|(PhysicalAddress&0xfff));
		dwPointer[0]=dwValue;
		OUTPUT(WSTR("%08x\n"),dwPointer[0]);
		break;
	}		
	return 0;
}

int bpint_command(int argc, WCHAR *argv[],PCWSTR szCommandLine,CSyser*pSyser)
{
	DWORD dwInterruptNumber;
	DWORD dwSegBase;
	WISP_CHAR CommandString[32];
	
	if(argc != 2|| CALCEXP(argv[1],&dwInterruptNumber)==FALSE)
	{
		OUTPUT(WSTR("Error : %<3>Input error !\n"));
		return -1;
	}
	if(dwInterruptNumber>0xff)
	{
		OUTPUT(WSTR("Error : %<3>Input error !\n"));
		return -1;
	}
	if(gOldInterruptProcAddress[dwInterruptNumber])//如果是在我们处理的中断
	{
		TSPrintf(CommandString,WSTR("bpx %08x"),gOldInterruptProcAddress[dwInterruptNumber]);
		RUNCMD(CommandString);
	}else
	{		
		X86_GATE_DECR* pGateDecr =(X86_GATE_DECR*) SyserGetIDTBase();
		switch(pGateDecr[dwInterruptNumber].Type)
		{
		case SYS_SEG_GATE_DECR_TYPE_32CALL_GATE:
		case SYS_SEG_GATE_DECR_TYPE_32INT_GATE:
		case SYS_SEG_GATE_DECR_TYPE_32TRAP_GATE:
			dwSegBase=GetSegmentBaseAddress(pGateDecr[dwInterruptNumber].Selector); 
			TSPrintf(CommandString,WSTR("bpx %08x"),dwSegBase+MAKE_DWORD(pGateDecr[dwInterruptNumber].OffsetHigh,pGateDecr[dwInterruptNumber].OffsetLow));
			RUNCMD(CommandString);
			break;
		case SYS_SEG_GATE_DECR_TYPE_16TRAP_GATE:
		case SYS_SEG_GATE_DECR_TYPE_16INT_GATE:
		case SYS_SEG_GATE_DECR_TYPE_16CALL_GATE:
			break;
		case SYS_SEG_GATE_DECR_TYPE_TASK_GATE:
			break;
		default:
			break;
		}
	}	
	return 0;
}
int ntcall2_command(int argc, WCHAR *argv[],PCWSTR szCommandLine,CSyser*pSyser)
{
	/*
	ULPOS		m_W32ServiceTableAddress;
	ULPOS*		m_W32ServiceTable;
	ULONG		m_Win32kImageBase;
	BYTE*		m_W32ServiceArgv;
	DWORD		m_W32ServiceNumbers;
	*/
	TNtcallNameIDMap::IT it;
	WCHAR NullStr[256];

	OUTPUT(WSTR("KeServiceDescriptorTableShadow line address %<f>%08x\n"),gpSyser->m_SysInfo.m_W32ServiceTableAddress);
	
	if(gpSyser->m_SysInfo.m_W32ServiceNumbers&&gpSyser->m_SysInfo.m_W32ServiceArgv&&gpSyser->m_SysInfo.m_W32ServiceTable)
	{
		for(DWORD i=0;i<gpSyser->m_SysInfo.m_W32ServiceNumbers;i++)
		{
			NullStr[0]=0;
			it = gpSyser->m_SysInfo.m_Win32kNtcallMap.Find(i|0x1000);
			if(it!=gpSyser->m_SysInfo.m_Win32kNtcallMap.End())
			{
				TStrCpy(NullStr,(*it).m_pData);
			}
			OUTPUT(WSTR("%04X 0008:%08X %2d %s\n"),i|0x1000,gpSyser->m_SysInfo.m_W32ServiceTable[i],gpSyser->m_SysInfo.m_W32ServiceArgv[i],&NullStr[0]);
		}
	}
	return 0;
}

int ntcall_command(int argc, WCHAR *argv[],PCWSTR szCommandLine,CSyser*pSyser)
{
	CHAR szBuffer[256];
	WCHAR SymbolName[256],SymbolName2[256],szTitle[MAX_FN_LEN];;
	DWORD i,j,*ServiceTable,dwAddress;
	BYTE *ArgTable,ArgCount;
	PSERVICETABLE CurTable;
	CDbgModule*pDbgModule=NULL;
	bool bOrgSym=false;
	DWORD OrgAddress;
	bool bSame;
	TNtcallMap::IT BIter,EIter;
	DWORD dwCurrentIndex;
	bool bHaveId=false;
	DWORD dwMin,dwMax;
	
	//CALCEXP(argv[1],&dwInterruptNumber)==FALSE
	for(i = 0;gpSyser->m_SysInfo.m_gNtoskrnlName[i];i++)
	{
		pDbgModule = gpSyser->m_pSysDebugger->GetModule(gpSyser->m_SysInfo.m_gNtoskrnlName[i]);
		if(pDbgModule)
			break;
	}
	if(ReadDword(&KeServiceDescriptorTable->LowCall,&i)==false)
		return 1;
	if(ReadDword(&KeServiceDescriptorTable->HiCall,&j)==false)
		return 1;
	if(ReadDword(&KeServiceDescriptorTable->ServiceTable,(DWORD*)&ServiceTable)==false)
		return 1;
	if(ReadDword(&KeServiceDescriptorTable->ArgTable,(DWORD*)&ArgTable)==false)
		return 1;
	dwMin=i,dwMax=j;
	OUTPUT(WSTR("KeServiceDescriptorTable line address %<f>%08x\n"),KeServiceDescriptorTable);
	if(argc>=2)
	{
		bHaveId=true;
		i=1;
		j=argc;
	}
	for(;i<j;i++)
	{
		if(bHaveId)
		{
			if(CALCEXP(argv[i],&dwCurrentIndex)==FALSE)
				continue;
			if(dwCurrentIndex>=dwMax)
				continue;
		}
		else
		{
			dwCurrentIndex=i;
		}
		if(ReadDword(&ServiceTable[dwCurrentIndex],&dwAddress)==false)
			continue;
		if(ReadByte(&ArgTable[dwCurrentIndex],&ArgCount)==false)
			continue;		
		SymbolName[0]=0;
		SymbolName2[0]=0;		
		BIter=pSyser->m_SysInfo.m_NtcallMap.Begin();
		EIter=pSyser->m_SysInfo.m_NtcallMap.End();
		bOrgSym=false;
		for(;BIter!=EIter;BIter++)
		{
			if(dwCurrentIndex == (DWORD)*BIter)
			{
				if(bOrgSym)
				{
					TStrCpy(SymbolName2,(char*)BIter.Key());
					break;
				}
				else
				{
					TStrCpy(SymbolName,(char*)BIter.Key());
					bOrgSym=true;
				}				
			}
		}
		bSame = true;
		OrgAddress=0;
		if(gpSyser->m_SysInfo.m_OrgWindowsServiceTable)
		{
			if(dwCurrentIndex < (gpSyser->m_SysInfo.m_HiCount-gpSyser->m_SysInfo.m_LoCount))
				if(dwAddress != gpSyser->m_SysInfo.m_OrgWindowsServiceTable[dwCurrentIndex])
				{
					OrgAddress = gpSyser->m_SysInfo.m_OrgWindowsServiceTable[dwCurrentIndex];
					bSame=false;
				}
		}
		else
		{
			if(pDbgModule)
			{
				if(dwAddress <= pDbgModule->m_ModuleBase || dwAddress > (pDbgModule->m_ModuleBase+pDbgModule->m_ModuleSize))
					bSame=false;
			}
		}
		szTitle[0]=0;
		if(bSame)
			OUTPUT(WSTR("%04X 0008:%08X %2d "),dwCurrentIndex,dwAddress,ArgCount>>2);
		else
		{
			CDbgModuleMap::IT Iter = pSyser->m_pSysDebugger->m_ModuleList.m_DbgModuleMap.Find(dwAddress);
			if(Iter.IsExist()==false)
				Iter = pSyser->m_pDebugger->m_ModuleList.m_DbgModuleMap.Find(dwAddress);
			if(Iter.IsExist())
			{
				CDbgModule* pModule;
				pModule = &(*Iter);
				AnsiToUnicode(pModule->m_ModuleTitle,szTitle,MAX_FN_LEN);
			}
			if(OrgAddress)
				OUTPUT(WSTR("%04X %<f>0008:%08X (0008:%08x)"),dwCurrentIndex,dwAddress,OrgAddress);
			else 
				OUTPUT(WSTR("%04X %<f>0008:%08X"),dwCurrentIndex,dwAddress);
			OUTPUT(WSTR(" %2d "),ArgCount>>2);
		}
		if(bOrgSym)
		{
			OUTPUT(WSTR("%s "),SymbolName);
			if(SymbolName2[0]!=0)
				OUTPUT(WSTR("%<b>(%s)"),SymbolName2);
		}
		else
		{
			if(SymbolName2[0]!=0)
				OUTPUT(WSTR("%s"),SymbolName2);
		}
		OUTPUT(WSTR(" %<f>%s"),szTitle);
		OUTPUT(WSTR("\n"));
	}
	
	return 0;
}



int irq_command(int argc, WCHAR *argv[],PCWSTR szCommandLine,CSyser*pSyser)
{
	DWORD dwIndex = 0;
	DWORD dwCounter = 0xff;
	DWORD dwIRQVector;
	DWORD dwHardInterruptNum;
	DWORD i;
	DWORD dwInterruptInfoLow,dwInterruptInfoHigh;
	WCHAR *statevalue[]=
	{
		WSTR("Masked"),
		WSTR("Unmasked"),
	};
	WCHAR *state;
	bool bOrg=false;
	WCHAR *DeliveryMode[]=
	{
		WSTR("Fixed   "),
		WSTR("Low. Pri"),
		WSTR("SMI     "),
		WSTR("Reserved"),
		WSTR("NMI     "),
		WSTR("INIT    "),
		WSTR("Reserved"),
		WSTR("ExtINT  "),
	};
	WCHAR *format=WSTR("%02x    %02x      %s  %s    %s     %s  %d\n");
	for(i =1;i < (DWORD)argc;i++)
	{
		if(TStrICmp(argv[i],"/o")==0 || TStrICmp(argv[i],"-o")==0)
		{
			bOrg=true;
			for(int j = i;j<argc-1;j++)
			{
				argv[j]=argv[j+1];
				argv[j+1]=NULL;
			}
			argc--;
		}
	}
	if(argc == 2)
	{
		if(CALCEXP(argv[1],&dwIndex)==FALSE)
		{
			OUTPUT(WSTR("Error : %<3>Input error !\n"));
			return -1;
		}
		dwCounter = 1;
	}
	if(gbIsUseAPIC)
	{
		dwHardInterruptNum = GetIOAPICInterruptNum();
		if(dwHardInterruptNum <= dwIndex)
		{
			OUTPUT(WSTR("Bad inti value\n"));
			return 1;
		}
		OUTPUT(WSTR("Inti  Vector  Delivery  Status     Trigger   Dest Mode Destination\n"));		
		for(i = 0; i < dwCounter;i++,dwIndex++)
		{
			if(dwIndex >= dwHardInterruptNum)
				break;		
			if(bOrg)
				dwInterruptInfoLow = IOAPICInterruptVectorTab[i].dwVectorLow;
			else
				dwInterruptInfoLow = GetIOAPICData(0x10 + dwIndex * 2);
			if(dwInterruptInfoLow & 0x10000)
				continue;
			if(bOrg)
				dwInterruptInfoHigh = IOAPICInterruptVectorTab[i].dwVectorHigh;
			else
				dwInterruptInfoHigh = GetIOAPICData(0x11 + dwIndex * 2);
			OUTPUT(format,
					dwIndex,
					dwInterruptInfoLow & 0xff,
					DeliveryMode[((dwInterruptInfoLow>>8)&7)],
					(dwInterruptInfoLow & 0x1000)?WSTR("Pending"):WSTR("Idle   "),
					(dwInterruptInfoLow & 0x8000)?WSTR("Level"):WSTR("Edge "),
					(dwInterruptInfoLow & 0x800)?WSTR("Logical "):WSTR("Physical"),
					dwInterruptInfoHigh >> 24);
		}
		if(i != 0)
		{
		dwInterruptInfoLow = GetIOAPICData(0);
		dwInterruptInfoHigh = GetIOAPICData(1);
		OUTPUT(WSTR("I/O unit id register: %08X\n"),dwInterruptInfoLow);
		OUTPUT(WSTR("I/O unit version register: %08x\n"),dwInterruptInfoHigh);
	}
	}
	else
	{
		OUTPUT(WSTR("IRQ   Vector  Status\n"));
		for(i = 0;i < dwCounter; i++,dwIndex++)
		{
			dwIRQVector = GetHardwareInterruptVectorNum(dwIndex);
			if(!dwIRQVector)
				break;
			if(dwIndex < 8)
				if((gdwPIC8259Shield_1 >> dwIndex) & 1)
					state =statevalue[0];
				else
					state =statevalue[1];
			else
				if((gdwPIC8259Shield_2 >> (dwIndex - 8)) & 1)
					state =statevalue[0];
				else
					state =statevalue[1];
			OUTPUT(WSTR("%02X    %02x      %s\n"),dwIndex,dwIRQVector,state);
		}
		if(i == 0)
			OUTPUT(WSTR("Bad IRQ parameter\n"));
	}
	return 0;
}

int tss_command(int argc, WCHAR *argv[],PCWSTR szCommandLine,CSyser*pSyser)
{
	VADDR32 dwGDTBase = 0;
	DWORD dwSelector,dwGDTSize = 0;
	DWORD dwTSSBase = 0,dwTSSSize = 0;
	TASK32SEGMENT *pTask32Segment;
	TASK16SEGMENT *pTask16Segment;
	DWORD dwAttributes,i,j;
	if(argc == 2)
	{
		if(CALCEXP(argv[1],&dwSelector)==FALSE)
		{
			OUTPUT(WSTR("Error : %<3>Input error !\n"));
			return -1;
		}
		dwTSSBase =GetTSSBase(&dwTSSSize,dwSelector);		
	}
	if(dwTSSSize == 0)
	{
		dwSelector = SyserGetTSSSelector();
		dwTSSBase =GetTSSBase(&dwTSSSize);
	}	
// 	__asm
// 	{
// 		lar eax,dwSelector
// 		mov dwAttributes,eax
// 	}	
	dwAttributes = SyserLar(dwSelector);

	dwAttributes &= 0x9f00;
	dwTSSSize++;
	if(dwAttributes == 0x8900 || dwAttributes == 0x8b00)
	{
		pTask32Segment = *(TASK32SEGMENT **)&dwTSSBase;
		OUTPUT(WSTR("TR=%04X  BASE=%08X  LIMIT=%X\n"),dwSelector,dwTSSBase,dwTSSSize-1);
		OUTPUT(WSTR("LDT=%04X  GS=%04X  FS=%04X  DS=%04X  SS=%04x  CS=%04X  ES=%04X  CR3=%08X\n"),pTask32Segment->LDT,pTask32Segment->GS,pTask32Segment->FS,pTask32Segment->DS,pTask32Segment->SS,pTask32Segment->CS,pTask32Segment->ES,pTask32Segment->CR3);
		OUTPUT(WSTR("EAX=%08X  EBX=%08X  ECX=%08X  EDX=%08X  EIP=%08X\n"),pTask32Segment->eax,pTask32Segment->ebp,pTask32Segment->ecx,pTask32Segment->edi,pTask32Segment->eip);
		OUTPUT(WSTR("ESI=%08X  EDI=%08X  EBP=%08X  ESP=%08X  EFL=%08X\n"),pTask32Segment->esi,pTask32Segment->edi,pTask32Segment->ebp,pTask32Segment->esp,pTask32Segment->efl);
		OUTPUT(WSTR("SS0=%04X:%08X  SS1=%04X:%08X  SS2=%04X:%08X\n"),pTask32Segment->SS0,pTask32Segment->ESP0,pTask32Segment->SS1,pTask32Segment->ESP1,pTask32Segment->SS2,pTask32Segment->ESP2);
		if(pTask32Segment->io_map_base>=dwTSSSize)
			OUTPUT(WSTR("I/O Map Base=%04x  I/O Map Size=0\n"),pTask32Segment->io_map_base);
		else
			OUTPUT(WSTR("I/O Map Base=%04x  I/O Map Size=%x\n"),pTask32Segment->io_map_base,dwTSSSize-pTask32Segment->io_map_base);
		if(dwTSSSize >= 0x68+0x20)
		{
			OUTPUT(WSTR("Interrupt redirection bit map. Base=0x%08x Size=%d\n"),dwTSSBase+0x68,0x20);
			OUTPUT(WSTR("                %<B>  0 1 2 3 4 5 6 7 - 8 9 A B C D E F\n"));
			BYTE* pIrbm=(BYTE*)(dwTSSBase+0x68);
			
			
			BYTE MaskValue;
			BYTE Value;
			
			for(j = 0,i=0,MaskValue=1; j < 16;j++)
			{
				OUTPUT(WSTR("0x%08x %02x%02x %<B>%X "),&pIrbm[j*2],pIrbm[j*2],pIrbm[j*2+1],j);
				Value=pIrbm[j*2];
				for(i = 0,MaskValue=1;i< 8;i++,MaskValue<<=1)
				{				
					if(Value&MaskValue)
						OUTPUT(WSTR("1 "));
					else
						OUTPUT(WSTR("0 "));
				}
				OUTPUT(WSTR("- "));
				Value=pIrbm[j*2+1];
				for(i = 0,MaskValue=1;i< 8;i++,MaskValue<<=1)
				{				
					if(Value&MaskValue)
						OUTPUT(WSTR("1 "));
					else
						OUTPUT(WSTR("0 "));
				}
				OUTPUT(WSTR("%<B>%X\n"),j);
			}
			OUTPUT(WSTR("                %<B>  0 1 2 3 4 5 6 7 - 8 9 A B C D E F\n"));
		}
	}
	if(dwAttributes == 0x8100 || dwAttributes == 0x8300)
	{
		pTask16Segment = *(TASK16SEGMENT **)&dwTSSBase;
		OUTPUT(WSTR("TR=%04X  BASE=%08X  LIMIT=%X\n"),dwSelector,dwTSSBase,dwTSSSize-1);
		OUTPUT(WSTR("LDT=%04X  DS=%04X  SS=%04x  CS=%04X  ES=%04X\n"),pTask16Segment->LDT,pTask16Segment->DS,pTask16Segment->SS,pTask16Segment->CS,pTask16Segment->ES);
		OUTPUT(WSTR("AX=%04X   BX=%04X  CX=%04X  DX=%04X  IP=%04X\n"),pTask16Segment->ax,pTask16Segment->bp,pTask16Segment->cx,pTask16Segment->di,pTask16Segment->ip);
		OUTPUT(WSTR("SI=%04X   DI=%04X  BP=%04X  SP=%04X  FL=%04X\n"),pTask16Segment->si,pTask16Segment->di,pTask16Segment->bp,pTask16Segment->sp,pTask16Segment->fl);
		OUTPUT(WSTR("SS0=%04X:%04X  SS1=%04X:%04X  SS2=%04X:%04X\n"),pTask16Segment->SS0,pTask16Segment->SP0,pTask16Segment->SS1,pTask16Segment->SP1,pTask16Segment->SS2,pTask16Segment->SP2);
	}
	return 0;
}

int ldt_command(int argc, WCHAR *argv[],PCWSTR szCommandLine,CSyser*pSyser1)
{
	return gdt_command(argc,argv,szCommandLine,pSyser1);
}

int idt_command(int argc, WCHAR *argv[],PCWSTR szCommandLine,CSyser*pSyser)
{
	CDbgModule*pDbgModule;
	DWORD dwSelector,dwIDTSize,dwOffset,dwTmpValue,*ptr;
	VADDR32 dwIDTBase;
	bool bSame;
	WCHAR szBuffer[MAX_FN_LEN];
	DWORD i = 0,j;
	WCHAR *Format=WSTR("%04x  %s  %04x:%08x                DPL=%d %s");
	X86_GATE_DECR *pGateDecr;
	WCHAR *DescType[16]={
		WSTR("Reserved"),
		WSTR("TSS16   "),
		WSTR("LDT     "),
		WSTR("TSS32   "),
		WSTR("CallG16 "),
		WSTR("TaskG   "),
		WSTR("IntG16  "),
		WSTR("TrapG16 "),
		WSTR("Reserved"),
		WSTR("TSS32   "),
		WSTR("Reserved"),
		WSTR("TSS32   "),
		WSTR("CallG32 "),
		WSTR("Reserved"),
		WSTR("IntG32  "),
		WSTR("TrapG32 "),
	};

	dwIDTBase = SyserGetIDTBase(&dwIDTSize);
	j = (dwIDTSize + 1) / sizeof(X86_GATE_DECR);
	if(argc >= 2)
	{
		if(CALCEXP(argv[1],&dwSelector)==FALSE)
		{			
			OUTPUT(WSTR("Error : %<3>Input error !\n"));
			return -1;
		}
		if(dwSelector > 0xff)
		{
			dwIDTBase=dwSelector;			
			if(ReadDword(*(void**)&dwIDTBase,&dwTmpValue)==false)
			{		
				OUTPUT(WSTR("Error : %<3>Read virtual address %08x\n"),*(void**)&dwIDTBase);
				return 1;
			}			
			argc =1;
		}
		else
		{
			argc = 1;
			i = dwSelector;
			j = i+1;
		}
	}
	pGateDecr = *(X86_GATE_DECR**)&dwIDTBase;
	ptr=(DWORD*)pGateDecr;
	if(argc == 1)
	{
		OUTPUT(WSTR("IDTBase=%08x  Limit=%x\n"),dwIDTBase,dwIDTSize);
		OUTPUT(WSTR("Int   Type      Sel : Offset                 Attributes    Module\n"));
		for(; i < j; i++)
		{		
			bSame=true;
			szBuffer[0]=0;
			if(ReadDword((void*)&ptr[i*2],&dwTmpValue)==false)
			{
				OUTPUT(WSTR("Error : %<3>Read virtual address %08x\n"),(void*)&ptr[i*2]);
				return 1;
			}
			if(ReadDword((void*)&ptr[i*2+1],&dwTmpValue)==false)
			{
				OUTPUT(WSTR("Error : %<3>Read virtual address %08x\n"),(void*)&ptr[i*2+1]);
				return 1;
			}
			dwSelector = pGateDecr[i].Selector;
			dwOffset = pGateDecr[i].OffsetLow | (pGateDecr[i].OffsetHigh << 16);
			if(gOldInterruptProcAddress[i])
			{
				DWORD SelfStart = *(DWORD*)&pSyser->m_DriverObject->DriverStart;
				if(dwOffset>SelfStart&&dwOffset<(SelfStart+pSyser->m_DriverObject->DriverSize))
					dwOffset=gOldInterruptProcAddress[i];
			}
			if(gpSyser->m_SysInfo.m_OrgWindowIDT)
			{
				if(gpSyser->m_SysInfo.m_OrgWindowIDT[i].EntryPoint!=dwOffset)
				{
					bSame=false;
				}
			}
			if(bSame)
			{
				OUTPUT(Format,i,DescType[pGateDecr[i].Type],dwSelector,dwOffset,pGateDecr[i].DPL,pGateDecr[i].P ? WSTR("P       "):WSTR("NP      "));
				pDbgModule = gpSyser->m_pSysDebugger->GetModule(dwOffset);
				if(pDbgModule)
				{
					AnsiToUnicode(pDbgModule->m_ModuleTitle,szBuffer,MAX_FN_LEN);
					OUTPUT(WSTR("%s"),szBuffer);
				}
				else
					OUTPUT(WSTR("<Unknown Module>"));
			}
			else
			{
				OUTPUT(WSTR("%04x  %s  %<F>%04x:%08x"),i,DescType[pGateDecr[i].Type],dwSelector,dwOffset);
				OUTPUT(WSTR("(%04x:%08x) "),gpSyser->m_SysInfo.m_OrgWindowIDT[i].Selector,gpSyser->m_SysInfo.m_OrgWindowIDT[i].EntryPoint);
				OUTPUT(WSTR("DPL=%d %s"),pGateDecr[i].DPL,pGateDecr[i].P ? WSTR("P       "):WSTR("NP      "));
				pDbgModule = gpSyser->m_pSysDebugger->GetModule(dwOffset);
				if(pDbgModule)
				{
					AnsiToUnicode(pDbgModule->m_ModuleTitle,szBuffer,MAX_FN_LEN);
					OUTPUT(WSTR("%<F>%s"),szBuffer);
				}
				else
					OUTPUT(WSTR("%<F><Unknown Module>"));

				pDbgModule = gpSyser->m_pSysDebugger->GetModule(gpSyser->m_SysInfo.m_OrgWindowIDT[i].EntryPoint);
				if(pDbgModule)
				{
					AnsiToUnicode(pDbgModule->m_ModuleTitle,szBuffer,MAX_FN_LEN);
					OUTPUT(WSTR("(%s)"),szBuffer);
				}
				else
					OUTPUT(WSTR("(<Unknown Module>)"));

			}
			OUTPUT(WSTR("\n"));
		}
	}
	return 0;
}

int gdt_command(int argc, WCHAR *argv[],PCWSTR szCommandLine,CSyser*pSyser)
{
	DWORD dwSelector=0,dwGDTSize,dwShowSelector;
	VADDR32 dwGDTBase = 0;
	DWORD dwSegmentBase,dwSegmentLimit,dwTmpValue,*Ptr;
	DWORD i = 0,j;
	bool	bLDTCommand = false;
	X86_SEGMENT_DESCRIPTOR *pSegDesc;
	int nOrgArgc;

	WCHAR *Format=WSTR("%04x  %s  %08x  %08x  %d    %s  %s %s %s\n");
	X86_GATE_DECR *GateDecr;
	
	WCHAR *DescType[16]=
	{
		WSTR("Reserved"),
		WSTR("TSS16   "),
		WSTR("LDT     "),
		WSTR("TSS32   "),
		WSTR("CallG16 "),
		WSTR("TaskG   "),
		WSTR("IntG16  "),
		WSTR("TrapG16 "),
		WSTR("Reserved"),
		WSTR("TSS32   "),
		WSTR("Reserved"),
		WSTR("TSS32   "),
		WSTR("CallG32 "),
		WSTR("Reserved"),
		WSTR("IntG32  "),
		WSTR("TrapG32 "),
	};
	nOrgArgc = argc;
	if(argc == 2)
	{
		if(CALCEXP(argv[1],&dwSelector)==FALSE)
		{
			OUTPUT(WSTR("Error : %<3>Input error !\n"));
			return -1;
		}
		if(dwSelector <= 0xffff)
		{
			if(dwSelector & 4)
				bLDTCommand = true;
		}
	}
	if((TStrICmp(argv[0],WSTR("LDT")) == 0) && (argc == 1))
	{
		bLDTCommand = true;
	}
	if(bLDTCommand)
	{
		dwGDTBase = GetLDTBase(&dwGDTSize);
		if(dwGDTBase == 0)
		{	
			OUTPUT(WSTR("No LDT\n"));
			return 1;
		}
	}else
		dwGDTBase = SyserGetGDTBase(&dwGDTSize);
	j = (dwGDTSize + 1)/sizeof(X86_SEGMENT_DESCRIPTOR);

	if(argc == 2)
	{
		if(dwSelector > 0xffff)
		{
			dwGDTBase=dwSelector;
			if(ReadDword((void*)dwGDTBase,&dwTmpValue)==false)
			{
				OUTPUT(WSTR("Error : %<3>Read virtual address %08x\n"),dwGDTBase);
				return 1;
			}			
			argc =1;
		}else
		{			
			argc = 1;
			i = dwSelector>>3;
			j = i+1;
		}
	}
	if((TStrICmp(argv[0],WSTR("ldtlist")) == 0) && argc==9999)
	{
		CALCEXP(argv[1],&dwGDTBase);
		if(ReadDword((void*)dwGDTBase,&dwTmpValue)==false)
		{
			OUTPUT(WSTR("Error : %<3>Read virtual address %08x\n"),dwGDTBase);
			return 1;
		}			
		CALCEXP(argv[2],&dwGDTSize);
		i = 0;
		j = (dwGDTSize + 1)/sizeof(X86_SEGMENT_DESCRIPTOR);
		argc = 1;
		nOrgArgc = 1;
		bLDTCommand = true;
	}
	
	if(argc == 1)
	{	
		if(nOrgArgc == 1)
		{
			if(bLDTCommand)
				OUTPUT(WSTR("LDTBase=%08x  Limit=%x\n"),dwGDTBase,dwGDTSize);
			else
				OUTPUT(WSTR("GDTBase=%08x  Limit=%x\n"),dwGDTBase,dwGDTSize);
		}
		OUTPUT(WSTR("Sel.  Type      Base      Limit     DPL  Attributes\n"));
		pSegDesc = *(X86_SEGMENT_DESCRIPTOR **)&dwGDTBase;
		Ptr=(DWORD*)pSegDesc;
		DWORD UpperLimit=0;
		for(; i < j; i++)
		{
			if(ReadDword((void*)&Ptr[i*2],&dwTmpValue)==false)
			{
				OUTPUT(WSTR("Error : %<3>Read virtual address %08x\n"),&Ptr[i*2]);
				return 1;
			}
			if(ReadDword((void*)&Ptr[i*2+1],&dwTmpValue)==false)
			{
				OUTPUT(WSTR("Error : %<3>Read virtual address %08x\n"),&Ptr[i*2+1]);
				return 1;
			}
			dwSegmentBase = (pSegDesc[i].base_H1<<24) |(pSegDesc[i].base_H0 << 16)|(pSegDesc[i].base_L1 << 8)|pSegDesc[i].base_L0;
			dwSegmentLimit = (pSegDesc[i].limit_H << 16) | (pSegDesc[i].limit_L1<<8)|pSegDesc[i].limit_L0;
			if(!pSegDesc[i].P)
			{
				OUTPUT(Format,bLDTCommand ? (i * 8) | 4:(i*8),WSTR("Reserved"),dwSegmentBase,dwSegmentLimit,pSegDesc[i].DPL,WSTR("NP"),WSTR("  "),WSTR("  "),WSTR(" "));
				continue;
			}
			dwShowSelector = (i*8)|pSegDesc[i].DPL;
				if(bLDTCommand)
					dwShowSelector |= 4;
			if(pSegDesc[i].DT)//存储段描述符
			{
				if(pSegDesc[i].G)
					dwSegmentLimit = (dwSegmentLimit << 12) | 0xfff;
				
				if(pSegDesc[i].TYPE & 8)//代码段
				{
					OUTPUT(Format,dwShowSelector,pSegDesc[i].D ? WSTR("Code32  "):WSTR("Code16  "),dwSegmentBase,dwSegmentLimit,pSegDesc[i].DPL,WSTR("P "),(pSegDesc[i].TYPE & 2) ? WSTR("RE") : WSTR("EO"),(pSegDesc[i].TYPE & 4) ?WSTR("C "):WSTR("  "),(pSegDesc[i].TYPE & 1) ? WSTR("A") : WSTR(" "));
				}
				else
				{					
					if(pSegDesc[i].TYPE & 4)
					{
						UpperLimit=dwSegmentLimit;
						if(pSegDesc[i].D)
							dwSegmentLimit=0xffffffff;
						else
							dwSegmentLimit=0x0000ffff;						
						UpperLimit+=1;
						OUTPUT(WSTR("%04x  %s  %08x  %08x-%08x  %d    %s  %s %s %s\n"),dwShowSelector,pSegDesc[i].D ? WSTR("Data32  "):WSTR("Data16  "),dwSegmentBase,UpperLimit,dwSegmentLimit,pSegDesc[i].DPL,WSTR("P "),(pSegDesc[i].TYPE & 2) ? WSTR("RW") : WSTR("RO"),(pSegDesc[i].TYPE & 4) ? WSTR("ED"):WSTR("  "),(pSegDesc[i].TYPE & 1) ? WSTR("A") : WSTR(" "));
					}
					else
					{
						OUTPUT(Format,dwShowSelector,pSegDesc[i].D ? WSTR("Data32  "):WSTR("Data16  "),dwSegmentBase,dwSegmentLimit,pSegDesc[i].DPL,WSTR("P "),(pSegDesc[i].TYPE & 2) ? WSTR("RW") : WSTR("RO"),(pSegDesc[i].TYPE & 4) ? WSTR("ED"):WSTR("  "),(pSegDesc[i].TYPE & 1) ? WSTR("A") : WSTR(" "));						
					}					
				}
				continue;
			}
			//系统段描述符
			if(	pSegDesc[i].TYPE == SYS_SEG_GATE_DECR_TYPE_16TSS_AVAIL ||
				pSegDesc[i].TYPE == SYS_SEG_GATE_DECR_TYPE_LDT ||
				pSegDesc[i].TYPE == SYS_SEG_GATE_DECR_TYPE_16TSS_BUSY ||
				pSegDesc[i].TYPE == SYS_SEG_GATE_DECR_TYPE_32TSS_AVAIL ||
				pSegDesc[i].TYPE == SYS_SEG_GATE_DECR_TYPE_32TSS_BUSY)
			{
				if(pSegDesc[i].TYPE == SYS_SEG_GATE_DECR_TYPE_LDT)
				{
					if((nOrgArgc == 2) && (TStrICmp(argv[0],WSTR("LDT")) == 0) && (dwSelector >> 3) == i)
					{
						WCHAR NewCommandArgc[10];
						WCHAR NewCommandArgc1[10];
						TSPrintf(NewCommandArgc,WSTR("%08x"),dwSegmentBase);
						TSPrintf(NewCommandArgc1,WSTR("%08x"),dwSegmentLimit);
						WCHAR* newargv[]={WSTR("ldtlist"),NewCommandArgc,NewCommandArgc1,NULL};
						return gdt_command(9999,newargv,szCommandLine,pSyser);
					}
					else
						OUTPUT(Format,dwShowSelector,DescType[pSegDesc[i].TYPE],dwSegmentBase,dwSegmentLimit,pSegDesc[i].DPL,WSTR("P "),WSTR("  "),WSTR("  "),WSTR(" "));
				}
				else
					OUTPUT(Format,dwShowSelector,DescType[pSegDesc[i].TYPE],dwSegmentBase,dwSegmentLimit,pSegDesc[i].DPL,WSTR("P "),(pSegDesc[i].TYPE & 2) ? WSTR("B "):WSTR("  "),WSTR("  "),WSTR(" "));
				continue;
			}
			GateDecr = (X86_GATE_DECR* )(&pSegDesc[i]);
			dwSegmentLimit = GateDecr->OffsetLow | (GateDecr->OffsetHigh << 16);
			dwSegmentBase = GateDecr->Selector;
			if(GateDecr->Type == SYS_SEG_GATE_DECR_TYPE_TASK_GATE)
			{
				continue;
			}
			if((GateDecr->Type == SYS_SEG_GATE_DECR_TYPE_32CALL_GATE) && (GateDecr->Type == SYS_SEG_GATE_DECR_TYPE_16CALL_GATE))
				OUTPUT(WSTR("%04x  %s  %04x:%08x       %d    %s\n"),dwShowSelector,DescType[pSegDesc[i].TYPE],dwSegmentBase,dwSegmentLimit,pSegDesc[i].DPL,WSTR("P "));
		}
		return 0;
	}
	return 0;
}

int phys_command(int argc, WCHAR *argv[],PCWSTR szCommandLine,CSyser*pSyser)
{
	int Count;
	ULPOS VAddr[0x100],Address;
	if(argc!=2 || CALCEXP(argv[1],&Address)==false)
	{
		OUTPUT(WSTR("Usage : phys LinesAddress\n"));
		return 1;
	}
	Count = MapToVAddr(Address,VAddr,sizeof(VAddr)/sizeof(ULPOS));
	for(int n=0;n<Count;n++)
	{
		OUTPUT(WSTR("%08X\n"),VAddr[n]);
	}
	return 0;
}

#define PAGE_DIRECTORY_LINES_ADDRESS	0xc0300000
#define	PAGE_TABLE_LINES_ADDRESS		0xc0000000
#define PAGE_DIRECTORY_36_LINES_ADDRESS	0xc0600000
#define	PAGE_TABLE_36_LINES_ADDRESS		0xc0000000
int page_command(int argc, WCHAR *argv[],PCWSTR szCommandLine,CSyser*pSyser)
{
	X86_PDE *pCurrentPDEBegin;
	X86_PDE_4M *pCurrentPDE4M;
	X86_PTE *dwPageTableBegin;
	PX86_36_PDE pCurrent36PDEBegin;
	PX86_36_PDE_2M pCurrent36PDE2M;
	PX86_36_PTE pPageTable36Begin;
	X86_36_PDE PDE36Value;
	X86_36_PDE_2M PDE36Value2M;
	X86_36_PTE PTE36Value;
	bool bPAE=false;  //如果是36位的物理地址扩展方式则该变量为真。
	int i,j;
	bool bNXE=false;
	DWORD dwPageDirectoryIndex,dwPageTableIndex;
	DWORD *dwPDEValue;
	DWORD dwVirtualAddress,dwTmpVar;;
	WCHAR *Format=WSTR("%08x    %sP %s %s %s %s %s %s    %08x - %08x\n");
	WCHAR *Format1=WSTR("%08x    %08x      %sP %s %s %s %s %s %s\n");
	WCHAR *FormatPAE=WSTR("%09I64x   %08x - %08x  %cP R%c %c %c %c %c %s %s %s %s\n");
	WCHAR *Format1PAE=WSTR("%08x   %09I64x  %cP R%c %c %c %c %c %s %s %s %s\n");

	CPUID_INFO ExInfo,TmpInfo;
	memset(&TmpInfo,0,sizeof(TmpInfo));
	memset(&ExInfo,0,sizeof(ExInfo));
	SyserGetCPUID(&TmpInfo,0x80000000);
	DWORD dwHiMiscFeature,dwLoMiscFeature;
	if(TmpInfo.dwEAX>=0x80000001)
	{		
		SyserGetCPUID(&ExInfo,0x80000001);
		if(((ExInfo.dwEDX & 0x20000000)>>29)==1 || ((ExInfo.dwEDX & 0x100000)>>20)==1)
		{
			bNXE=true;
		}
		
		if(bNXE)
		{
			if(SyserReadMSR(0xc0000080,&dwHiMiscFeature,&dwLoMiscFeature))
			{
				if(((dwLoMiscFeature&0x800)>>11)==0)
					bNXE=false;
			}
		}				
	}

	bPAE = (GetCR4Register() & CR4_PAE_BIT_MASK) ? true : false;
	pCurrentPDEBegin = (X86_PDE *)PAGE_DIRECTORY_LINES_ADDRESS;
	if(argc==1)
	{
		OUTPUT(WSTR("Page Directory Physical %08X\n"),Reg.CR[3]);		
		if(bPAE)
		{
			OUTPUT(WSTR("Physical        Linear Address Range  Attributes\n"));
			pCurrent36PDEBegin=(PX86_36_PDE)PAGE_DIRECTORY_36_LINES_ADDRESS;
			pPageTable36Begin=(PX86_36_PTE)PAGE_TABLE_36_LINES_ADDRESS;
			for(i = 0; i < 2048; i++)
			{
				if(SafeMemCopy((BYTE*)&PDE36Value,(BYTE*)&pCurrent36PDEBegin[i],sizeof(X86_36_PDE))==0)
					continue;
				if(PDE36Value.u.P==0)
					continue;
				PDE36Value2M.PDE36Value2M = PDE36Value.PDE36Value;
				if(PDE36Value2M.u.Page2M)
				{
					OUTPUT(FormatPAE,
						PDE36Value2M.PDE36Value2M&(~0xfff),					
						i*0x200000,i*0x200000+0x1FFFFF,
						PDE36Value2M.u.P?' ':'N',
						PDE36Value2M.u.RW?'W':' ',
						PDE36Value2M.u.US?'U':'S',						
						PDE36Value2M.u.A?'A':' ',
						PDE36Value2M.u.D?'D':' ',
						PDE36Value2M.u.G?'G':' ',
						PDE36Value2M.u.PCD?WSTR("CD"):WSTR("  "),
						PDE36Value2M.u.PWT?WSTR("WT"):WSTR("  "),
						WSTR("2M"),
						(bNXE && PDE36Value2M.u.NXE)?WSTR("NE"):WSTR("  ")
						);
				}
				else
				{
					OUTPUT(FormatPAE,
						PDE36Value.PDE36Value&(~0xfff),					
						i*0x200000,i*0x200000+0x1FFFFF,
						PDE36Value.u.P?' ':'N',
						PDE36Value.u.RW?'W':' ',
						PDE36Value.u.US?'U':'S',						
						' ',
						' ',
						' ',
						PDE36Value.u.PCD?WSTR("CD"):WSTR("  "),
						PDE36Value.u.PWT?WSTR("WT"):WSTR("  "),
						WSTR(""),
						(bNXE && PDE36Value.u.NXE)?WSTR("NE"):WSTR("  ")
						);
				}
			}
		}
		else
		{
			OUTPUT(WSTR("Physical     Attributes         Linear Address Range\n"));
			for(j = 0,i = 0; i < 1024; i++)
			{
				dwPDEValue = (DWORD *)&pCurrentPDEBegin[i];
				if(ReadDword(&pCurrentPDEBegin[i],&dwTmpVar)==false)
					continue;
				if(!pCurrentPDEBegin[i].u.Present)
					continue;
				if(pCurrentPDEBegin[i].u.Page4M)
				{
					pCurrentPDE4M = (X86_PDE_4M *)&pCurrentPDEBegin[i];
					OUTPUT(Format,
						*dwPDEValue &0xfffff000,
						WSTR(" "),
						pCurrentPDE4M->GlobePage ? WSTR("G"):WSTR(" "),
						pCurrentPDE4M->Dirty ? WSTR("D"):WSTR(" "),
						pCurrentPDE4M->Accessed ? WSTR("A"):WSTR(" "),
						pCurrentPDE4M->UserPage ? WSTR("U"):WSTR("S"),
						pCurrentPDE4M->ReadWrite ? WSTR("RW"):WSTR("R "),
						WSTR("4M"),
						i*0x400000,i*0x400000+0x3FFFFF);
				}
				else
				{
					OUTPUT(Format,
						*dwPDEValue &0xfffff000,
						WSTR(" "),
						WSTR(" "),
						WSTR(" "),
						pCurrentPDEBegin[i].u.Accessed ? WSTR("A"):WSTR(" "),
						pCurrentPDEBegin[i].u.UserPage ? WSTR("U"):WSTR("S"),
						pCurrentPDEBegin[i].u.ReadWrite ? WSTR("RW"):WSTR("R "),
						WSTR("  "),
						i*0x400000,i*0x400000+0x3fffff);
				}
			}
		}		
		return 0;
	}
	if(argc == 2 )
	{		
		if(CALCEXP(argv[1],&dwVirtualAddress) == false)
			return 1;
		if(bPAE)
		{
			dwPageDirectoryIndex = dwVirtualAddress;
			dwPageDirectoryIndex >>= 21;
			pCurrent36PDEBegin=(PX86_36_PDE)PAGE_DIRECTORY_36_LINES_ADDRESS;
			pPageTable36Begin=(PX86_36_PTE)PAGE_TABLE_36_LINES_ADDRESS;
			if(SafeMemCopy((BYTE*)&PDE36Value,(BYTE*)&pCurrent36PDEBegin[dwPageDirectoryIndex],sizeof(X86_36_PDE))==0)
				return 1;
			if(PDE36Value.u.P==0)
				return 1;
			PDE36Value2M.PDE36Value2M = PDE36Value.PDE36Value;
			if(PDE36Value2M.u.Page2M)
			{
				OUTPUT(WSTR("Linear     Physical    Attributes\n"));
				OUTPUT(Format1PAE,
					dwVirtualAddress,					
					(PDE36Value2M.PDE36Value2M&0x0000000fffe00000) | (dwVirtualAddress&0x1fffff),
					PDE36Value2M.u.P?' ':'N',
					PDE36Value2M.u.RW?'W':' ',
					PDE36Value2M.u.US?'U':'S',
					PDE36Value2M.u.A?'A':' ',
					PDE36Value2M.u.D?'D':' ',
					PDE36Value2M.u.G?'G':' ',
					PDE36Value2M.u.PCD?WSTR("CD"):WSTR("  "),
					PDE36Value2M.u.PWT?WSTR("WT"):WSTR("  "),
					WSTR("2M"),
					(bNXE && PDE36Value2M.u.NXE)?WSTR("NE"):WSTR("  ")
					);
			}
			else
			{
				dwPageDirectoryIndex<<=9;
				dwPageTableIndex = dwVirtualAddress;
				dwPageTableIndex = dwVirtualAddress >> 12;
				dwPageTableIndex &= 0x1ff;

				if(SafeMemCopy((BYTE*)&PTE36Value,(BYTE*)&pPageTable36Begin[dwPageDirectoryIndex+dwPageTableIndex],sizeof(X86_36_PTE))==0)
					return 1;
				if(PTE36Value.u.P==0)
					return 1;
				OUTPUT(WSTR("Linear     Physical    Attributes\n"));
				OUTPUT(Format1PAE,
					dwVirtualAddress,					
					(PTE36Value.PTE36Value&0x0000000fffff000) | (dwVirtualAddress&0xfff),
					PTE36Value.u.P?' ':'N',
					PTE36Value.u.RW?'W':' ',
					PTE36Value.u.US?'U':'S',
					PTE36Value.u.A?'A':' ',
					PTE36Value.u.D?'D':' ',
					PTE36Value.u.G?'G':' ',
					PTE36Value.u.PCD?WSTR("CD"):WSTR("  "),
					PTE36Value.u.PWT?WSTR("WT"):WSTR("  "),
					WSTR(""),
					(bNXE && (PDE36Value.u.NXE || PTE36Value.u.NXE))?WSTR("NE"):WSTR("  ")
					);
			}
		}
		else
		{
			dwPageDirectoryIndex = dwVirtualAddress;
			dwPageDirectoryIndex >>= 22;
			if(ReadDword(&pCurrentPDEBegin[dwPageDirectoryIndex],&dwTmpVar)==false)
				return 1;
			if(!pCurrentPDEBegin[dwPageDirectoryIndex].u.Present)
				return 1;		
			OUTPUT(WSTR("Linear     Physical        Attributes\n"));
			if(pCurrentPDEBegin[dwPageDirectoryIndex].u.Page4M)
			{
				pCurrentPDE4M = (X86_PDE_4M *)&pCurrentPDEBegin[dwPageDirectoryIndex];
				dwPDEValue = (DWORD *)&pCurrentPDEBegin[dwPageDirectoryIndex];
				OUTPUT(Format1,
					dwVirtualAddress,
					(dwTmpVar & 0xffc00000) | (dwVirtualAddress & 0x3fffff),
					WSTR(" "),
					pCurrentPDE4M->GlobePage ? WSTR("G"):WSTR(" "),
					pCurrentPDE4M->Dirty ? WSTR("D"):WSTR(" "),
					pCurrentPDE4M->Accessed ? WSTR("A"):WSTR(" "),
					pCurrentPDE4M->UserPage ? WSTR("U"):WSTR("S"),
					pCurrentPDE4M->ReadWrite ? WSTR("RW"):WSTR("R "),
					WSTR("4M\n"));
				return 1;
			}
			dwPageDirectoryIndex <<= 12;
			dwPageTableBegin = (X86_PTE*)(PAGE_TABLE_LINES_ADDRESS + dwPageDirectoryIndex);
			dwPageTableIndex = dwVirtualAddress;
			dwPageTableIndex = dwVirtualAddress >> 12;
			dwPageTableIndex &= 0x3ff;
			if(ReadDword(&dwPageTableBegin[dwPageTableIndex],&dwTmpVar)==false)
				return 1;
			if(!dwPageTableBegin[dwPageTableIndex].Present)
				return 1;			
			OUTPUT(Format1,
				dwVirtualAddress,
				(dwTmpVar & 0xfffff000) | (dwVirtualAddress & 0xfff),
				WSTR(" "),
				dwPageTableBegin[dwPageTableIndex].GlobePage ? WSTR("G"):WSTR(" "),
				dwPageTableBegin[dwPageTableIndex].Dirty ? WSTR("D"):WSTR(" "),
				dwPageTableBegin[dwPageTableIndex].Accessed ? WSTR("A"):WSTR(" "),
				dwPageTableBegin[dwPageTableIndex].UserPage ? WSTR("U"):WSTR("S"),
				dwPageTableBegin[dwPageTableIndex].ReadWrite ? WSTR("RW"):WSTR("R "),
				WSTR("  \n"));
		}		
	}
	return 0;

}

int export_command(int argc, WCHAR *argv[ ],PCWSTR szCommandLine, CSyser*pSyser)
{
	if(argc!=2)
	{
		OUTPUT(WSTR("Usage : export module_name\n"));
		return 0;
	}
	CDbgModule* pModule = gpSyser->m_pDebugger->GetModule(argv[1]);
	if(pModule==NULL)
	{
		pModule = gpSyser->m_pSysDebugger->GetModule(argv[1]);
		if(pModule==NULL)
		{
			OUTPUT(WSTR("Error : Can't find this module %s\n"),argv[1]);
			return 1;
		}
	}
	WCHAR szBuffer[256];
	CPEFile* pPEFile = new CPEFile;
	pPEFile->SetRMProc(CImageFile::StaticReadRealMemory);
	pPEFile->m_ImageBase = pModule->m_ModuleBase;
	pPEFile->m_ImageSize = pModule->m_ModuleSize;
	pPEFile->m_FileObjType = FILE_OBJ_TYPE_OS_MEMORY_IMAGE;
	if(pPEFile->Open(NULL))
	{
		OUTPUT(WSTR("Address      Function Name"));
		for(int n=0;n<pPEFile->m_ExportFuncCount;n++)
		{
			AnsiToUnicode(pPEFile->m_ExportFunc[n].FuncName,szBuffer,256);
			OUTPUT(WSTR("%08X     %s\n"),pPEFile->m_ExportFunc[n].Address,szBuffer);
		}
		pPEFile->Close();
	}
	delete pPEFile;
	return 0;
}

int addr_command(int argc, WCHAR *argv[ ],PCWSTR szCommandLine, CSyser*pSyser)
{
	CDbgProcess*pDbgProcess;
	WCHAR szBuffer[MAX_FN_LEN];
	DWORD PID;
	if(argc==1)
		return proc_command(argc,argv,szCommandLine,pSyser);
	TStrCpyLimit(szBuffer,&szCommandLine[argv[1]-argv[0]],MAX_FN_LEN);
	pDbgProcess=pSyser->m_SysInfo.GetProcess(szBuffer);
	if(pDbgProcess)
	{
		pSyser->MapToProcess(pDbgProcess);
		gpSyser->m_SyserUI.m_SyserDI.UpdateContext();
		return 0;
	}
	TStrCat(szBuffer,".exe");
	pDbgProcess=pSyser->m_SysInfo.GetProcess(szBuffer);
	if(pDbgProcess)
	{
		pSyser->MapToProcess(pDbgProcess);
		gpSyser->m_SyserUI.m_SyserDI.UpdateContext();
		return 0;
	}
	if(CALCEXP(argv[1],&PID)==FALSE)
	{
		OUTPUT(WSTR("Error : Can't find process!\n"));
		return 1;
	}
	pDbgProcess=pSyser->m_SysInfo.GetProcess(PID);
	if(pDbgProcess)
	{
		pSyser->MapToProcess(pDbgProcess);
		gpSyser->m_SyserUI.m_SyserDI.UpdateContext();
		return 0;
	}
	OUTPUT(WSTR("Error : Can't find process!\n"));
	return 1;
}




int proc_command(int argc, WCHAR *argv[ ],PCWSTR szCommandLine,CSyser*pSyser)
{
	if(argc==1)
	{
		int Count;
		Count = 0;
		OUTPUT(WSTR("Process ID    CR3               EPROCESS Process Name\n"));
		for(CProcMap::IT Iter=pSyser->m_SysInfo.m_ProcMap.Begin();Iter!=pSyser->m_SysInfo.m_ProcMap.End();Iter++)
		{
			if(&(*Iter)==pSyser->m_pDebugger)
				OUTPUT(WSTR("%<B>PID = 0x%04X  CR3 = 0x%08X  %08X [%s]\n"),Iter->m_PID,Iter->m_CR3,Iter->m_PEProcess,(PWSTR)Iter->m_ProcNameW);
			else
				OUTPUT(WSTR("PID = 0x%04X  CR3 = 0x%08X  %08X %<F>[%s]\n"),Iter->m_PID,Iter->m_CR3,Iter->m_PEProcess,(PWSTR)Iter->m_ProcNameW);
			Count++;
		}
		OUTPUT(WSTR("%d Process(s)\n"),Count);
		return 0;
	}
	argc--;
	int i;
	DWORD dwValue;
	SYSER_PROCESS Process;
	SYSER_THREAD Thread;
	SYSER_VALUE_TYPE ValueType;
	bool bOK;
	bool bTitle=false;
	WCHAR Name[20];
	for(i=0;i<argc;i++)
	{
		if(CALCEXP(argv[i+1],&dwValue)==FALSE)
			continue;
		ValueType = GetValueType(dwValue);
		if(ValueType==VALUE_TYPE_UNKNOW || ValueType==VALUE_TYPE_HWND_ID || ValueType == VALUE_TYPE_HWND_PTR)
			continue;
		bOK=false;
		switch(ValueType)
		{
		case VALUE_TYPE_THREAD_PTR:
			bOK = GetProcessByETHREAD(dwValue,&Process);
			break;
		case VALUE_TYPE_PROCESS_ID:
			bOK=GetProcessByID(dwValue,&Process);
			break;
		case VALUE_TYPE_PROCESS_PTR:
			bOK=GetProcessInfoByEPROCESS(dwValue,&Process);
			break;
		case VALUE_TYPE_THREAD_ID:
			bOK=GetProcessByThreadID(dwValue,&Process);
			break;
		}
		if(bOK==false)
			continue;
		if(bTitle==false)
		{
			bTitle=true;
			OUTPUT(WSTR("Process ID    CR3               EPROCESS Process Name\n"));
		}
		TStrCpy(Name,Process.ImageFileName);
		OUTPUT(WSTR("PID = 0x%04X  CR3 = 0x%08X  %08X %<F>[%s]\n"),Process.UniqueProcessId,Process.PDT,Process.OSProcess,Name);
	}
	return 0;
}

int ver_command(int argc, WCHAR *argv[ ],PCWSTR szCommandLine, CSyser*pSyser)
{
	WISP_CHAR szBuffer[256];
	TStrCpy(szBuffer,"Syser version : ");
	TStrCat(szBuffer,VER_PRODUCTVERSION_STR);
	TStrCat(szBuffer,"\nBuild Time    : ");
	TStrCat(szBuffer,__DATE__);
	TStrCat(szBuffer," ");
	TStrCat(szBuffer,__TIME__);
	TStrCat(szBuffer,"\n");
	OUTPUT(szBuffer);
	return 0;
}

int set_softice_baseaddress_command(int argc, WCHAR *argv[ ],PCWSTR szCommandLine, CSyser*pSyser)
{
	DWORD dwAddress;
	if(argc!=2 || CALCEXP(argv[1],&dwAddress)==FALSE)
	{
		OUTPUT(WSTR("Error : %<3>Input error !\n"));
		return -1;
	}
	dwSofticeDriverBase = dwAddress;
	OUTPUT(WSTR("Offset Value = %08x\n"), dwSofticeDriverBase);
	return 0;
}

int d_softice_command(int argc, WCHAR *argv[ ],PCWSTR szCommandLine, CSyser*pSyser)
{
	DWORD dwAddress;
	if(argc!=2 || CALCEXP(argv[1],&dwAddress)==FALSE)
	{
		OUTPUT(WSTR("Error : %<3>Input error !\n"));
		return -1;
	}	
	if(dwSofticeDriverBase)
	{
		//dwAddress -= 0xf83c7000;
		dwAddress += dwSofticeDriverBase;
	}	
	pSyser->m_MainFrame.m_SystemExplorer.m_MultiDataView.SetActiveAddress(dwAddress);
	OUTPUT(WSTR("Offset Value = %08x\n"),dwSofticeDriverBase);
	return 0;
}

int u_softice_command(int argc, WCHAR *argv[ ],PCWSTR szCommandLine, CSyser*pSyser)
{
	DWORD dwAddress;
	if(argc!=2 || CALCEXP(argv[1],&dwAddress)==FALSE)
	{
		OUTPUT(WSTR("Error : %<3>Input error !\n"));
		return -1;
	}
	if(dwSofticeDriverBase)
	{
		//dwAddress -= 0xf83c7000;
		dwAddress += dwSofticeDriverBase;
	}
	pSyser->m_MainFrame.m_SystemExplorer.m_MultiCodeView.SetActiveAddress(dwAddress);
	OUTPUT(WSTR("Offset Value = %08x\n"),dwSofticeDriverBase);
	return 0;
}

int activesoftice_command(int argc, WCHAR *argv[ ],PCWSTR szCommandLine, CSyser*pSyser)
{
	if(dwSofticeDriverBase)
	{		
		bGoToSoftice=true;
		pSyser->m_bSaveReg=false;
		pSyser->Exit(TRUE);
		//pSofticeActivePointer();
	}
	else
	{
		OUTPUT(WSTR("SoftICE is not active.\n"));
	}
	return 0;
}

int ib_command(int argc, WCHAR *argv[ ],PCWSTR szCommandLine, CSyser*pSyser)
{
	DWORD dwAddress;	

	if(argc!=2 || CALCEXP(argv[1],&dwAddress)==FALSE)
	{
		OUTPUT(WSTR("Error : %<3>Input error !\n"));
		return -1;
	}
	
	if(dwAddress > 0xffff)
	{
		OUTPUT(WSTR("Error : %<3>Input error !\n"));
		return 1;
	}
	switch(argv[0][1]) {
	case 0:	
	case 'b':
	case 'B':
		if(!gbIsUseAPIC)
		{
			if(dwAddress == 0x21)
			{
				OUTPUT(WSTR("%02x\n"),gdwPIC8259Shield_1);
				return 0;
			}
			if(dwAddress == 0xa1)
			{
				OUTPUT(WSTR("%02x\n"),gdwPIC8259Shield_2);
				return 0;
			}
		}
		OUTPUT(WSTR("%02x\n"), SyserReadPortByte(dwAddress));
		break;
	case 'w':
	case 'W':
		OUTPUT(WSTR("%04x\n"), SyserReadPortWord(dwAddress));
		break;
	case 'd':
	case 'D':
		OUTPUT(WSTR("%08x\n"), SyserReadPortDword(dwAddress));
		break;
	default:
		OUTPUT(WSTR("Error : %<3>Input error !\n"));
		return 1;
	}
	
	return 0;
}

int ob_command(int argc, WCHAR *argv[ ],PCWSTR szCommandLine, CSyser*pSyser)
{
	DWORD dwAddress,dwValue;
	if(argc!=3 || CALCEXP(argv[1],&dwAddress)==FALSE ||CALCEXP(argv[2],&dwValue)==FALSE)
	{
		OUTPUT(WSTR("Error : %<3>Input error !\n"));
		return -1;
	}	
	if(dwAddress > 0xffff)
	{
		OUTPUT(WSTR("Error : %<3>Input error !\n"));
		return -1;
	}
	switch(argv[0][1]) {
	case 0:
	case 'b':
	case 'B':
		if(dwValue >= 0x100)
		{
			OUTPUT(WSTR("Error : %<3>Input error !\n"));
			return -1;
		}
		if(!gbIsUseAPIC)
		{
			if(dwAddress == 0x21)
			{
				gdwPIC8259Shield_1 = (BYTE)dwValue;
				return 0;
			}
			if(dwAddress == 0xa1)
			{
				gdwPIC8259Shield_2 = (BYTE)dwValue;
				return 0;
			}
		}
		SyserWritePortByte(dwAddress,(BYTE)dwValue);
		break;
	case 'W':
	case 'w':
		if(dwValue>0x10000)
		{
			OUTPUT(WSTR("Error : %<3>Input error !\n"));
			return -1;
		}
		SyserWritePortWord(dwAddress,(WORD)dwValue);
		break;
	case 'd':
	case 'D':
		SyserWritePortDword(dwAddress,dwValue);
		break;
	default:
		OUTPUT(WSTR("Error : %<3>Input error !\n"));
		return -1;
	}	
	return 0;
}



int setkeyboardLED_command(int argc, WCHAR *argv[ ],PCWSTR szCommandLine, CSyser*pSyser)
{
	DWORD dwAddress;
	
	if(argc == 1)
	{
		if(bKeyScrollLockStatInitOK)
			OUTPUT(WSTR("Scroll Lock %02x\n"),bKeyScrollLockStat);
		if(bKeyNumLockStatInitOK)
			OUTPUT(WSTR("Num Lock %02x\n"),bKeyNumLockStat);
		if(bKeyCapsLockStatInitOK)
			OUTPUT(WSTR("Caps Lock %02x\n"),bKeyCapsLockStat);
		return 1;
	}
	if(argc!=2 || CALCEXP(argv[1],&dwAddress)==FALSE)
	{
		OUTPUT(WSTR("Error : %<3>Input error !\n"));
		return -1;
	}	
	SetKeyboardLEDState(dwAddress & 1,dwAddress & 2,dwAddress & 4);
	return 0;
}

int DebugRegisterMonitor_command(int argc, WCHAR *argv[ ],PCWSTR szCommandLine, CSyser*pSyser)
{
	DWORD wStat = 0;
	if(argc > 2)
	{
local_exit:
		OUTPUT(WSTR("Error : %<3>Input error !\n"));
		OUTPUT(WSTR("example : drm      \"Show Debug Register Access State\"\n"));
		OUTPUT(WSTR("example : drm on   \"Set Debug Register Access BreakPoint\"\n"));
		OUTPUT(WSTR("example : drm off  \"Clean Debug Register Access BreakPoint\"\n"));
		return -1;
	}
	if(argc == 1)
	{
		if(pSyser->m_bDbgRegAccessMon)
		{
			OUTPUT(WSTR("drm on\n"));
		}
		else
			OUTPUT(WSTR("drm off\n"));
		return 0;
	}
	if((argv[1][0] & 0xffdf) != 'O' || (argv[1][2] && argv[1][3]))
	{		
		goto local_exit;
	}
	wStat = *(DWORD *)(&argv[1][1]);
	wStat &= 0xffdfffdf;
	if(wStat == 'N')
	{
		pSyser->m_bDbgRegAccessMon = TRUE;
		Reg.DR[7] |= 0x2000;
		pSyser->m_bUpdateReg=TRUE;
		OUTPUT(WSTR("drm on\n"));
		return 0;
	}
	if((wStat == 0x460046) && (argv[1][3] == 0))
	{
		pSyser->m_bDbgRegAccessMon = FALSE;
		Reg.DR[7] &= 0xffffdfff;
		pSyser->m_bUpdateReg=TRUE;
		OUTPUT(WSTR("drm off\n"));
	}
	return 0;
}

int pci_command(int argc, WCHAR *argv[],PCWSTR szCommandLine,CSyser *pSyser)
{	
	PCI_CONFIG_COMMON PCIConfigREG;
	DWORD dwOldValue;
	DWORD dwSize=0;
	pci_dev dev;
	int j;

	for(j =0;j<0x100;j++)
	{
		dev.bus = j;
		for(int i = 0; i < 0x100; i++)
		{
			dev.devfn = i;
			gpSyser->m_PCSystem.ReadPCICFGWord(j,i,PCI_VENDOR_ID,&PCIConfigREG.VendorID);
			if(PCIConfigREG.VendorID != 0xffff && PCIConfigREG.VendorID != 0)
			{
				OUTPUT(WSTR("Bus %02X Device %02X Function %02X\n"),j,i>>3,i&7);
				OUTPUT(WSTR("Vendor : %04X\n"),PCIConfigREG.VendorID);
				gpSyser->m_PCSystem.ReadPCICFGWord(j,i,PCI_DEVICE_ID,&PCIConfigREG.DeviceID);
				OUTPUT(WSTR("Device : %04X\n"),PCIConfigREG.DeviceID);
				gpSyser->m_PCSystem.ReadPCICFGDWord(j,i,PCI_REVISION_ID,(DWORD *)&PCIConfigREG.RevisionID);
				OUTPUT(WSTR("Revision : %02X\n"),PCIConfigREG.RevisionID);
				OUTPUT(WSTR("Device class : %02X\n"),PCIConfigREG.BaseClass);
				OUTPUT(WSTR("Device subclass : %02X\n"),PCIConfigREG.SubClass);
				OUTPUT(WSTR("Device ProgIf : %02X\n"),PCIConfigREG.ProgIf);
				gpSyser->m_PCSystem.ReadPCICFGDWord(j,i,PCI_BASE_ADDRESS_0,&dwOldValue);
				//gpSyser->m_PCSystem.WritePCICFGDWord(j,i,PCI_BASE_ADDRESS_0,0xffffffff);
				//gpSyser->m_PCSystem.ReadPCICFGDWord(j,i,PCI_BASE_ADDRESS_0,&dwSize);
				//gpSyser->m_PCSystem.WritePCICFGDWord(j,i,PCI_BASE_ADDRESS_0,dwOldValue);
				OUTPUT(WSTR("Memory Base : %08X  Memory Limit:   %08X\n"),dwOldValue,dwSize);
				gpSyser->m_PCSystem.ReadPCICFGDWord(j,i,PCI_BASE_ADDRESS_1,&dwOldValue);
				OUTPUT(WSTR("Memory Base : %08X  Memory Limit:   %08X\n"),dwOldValue,dwSize);
				gpSyser->m_PCSystem.ReadPCICFGDWord(j,i,PCI_BASE_ADDRESS_2,&dwOldValue);
				OUTPUT(WSTR("Memory Base : %08X  Memory Limit:   %08X\n"),dwOldValue,dwSize);
				gpSyser->m_PCSystem.ReadPCICFGDWord(j,i,PCI_BASE_ADDRESS_3,&dwOldValue);
				OUTPUT(WSTR("Memory Base : %08X  Memory Limit:   %08X\n"),dwOldValue,dwSize);
				gpSyser->m_PCSystem.ReadPCICFGDWord(j,i,PCI_BASE_ADDRESS_4,&dwOldValue);
				OUTPUT(WSTR("Memory Base : %08X  Memory Limit:   %08X\n"),dwOldValue,dwSize);
				OUTPUT(WSTR("---------------------------------------------------------------------------------\n"),dwOldValue,dwSize);
			}
		}
	 }
	return 0;
}

int acpi_shutdown_command(int argc, WCHAR *argv[ ],PCWSTR szCommandLine, CSyser*pSyser)
{
	PCI_CONFIG_COMMON PCIConfigREG;
	DWORD dwOldValue;
	DWORD dwSize=0;
	WORD Value;
	pci_dev dev;
	int j;

	for(j =0;j<0x100;j++)
	{
		dev.bus = j;
		for(int i = 0; i < 0x100; i++)
		{
			dev.devfn = i;
			gpSyser->m_PCSystem.ReadPCICFGWord(j,i,PCI_VENDOR_ID,&PCIConfigREG.VendorID);
			if(PCIConfigREG.VendorID != 0xffff && PCIConfigREG.VendorID != 0)
			{				
				gpSyser->m_PCSystem.ReadPCICFGDWord(j,i,PCI_REVISION_ID,(DWORD *)&PCIConfigREG.RevisionID);				
				if(PCIConfigREG.BaseClass==6 &&PCIConfigREG.SubClass==1) //南桥
				{
					gpSyser->m_PCSystem.ReadPCICFGDWord(j,i,0x40,(DWORD *)&dwOldValue);
					dwOldValue &= 0xff80;
					Value = SyserReadPortWord(dwOldValue + 4);
					Value |= 0x3C00;
					SyserWritePortWord( dwOldValue + 4,Value);
				}				
			}
		}
	}
	return 0;
}

int ignore_command(int argc, WCHAR *argv[ ],PCWSTR szCommandLine, CSyser*pSyser)
{
	pSyser->m_bHandle = false;
	return 0;
}

int pagein_command(int argc, WCHAR *argv[ ],PCWSTR szCommandLine, CSyser*pSyser)
{
	DWORD dwAddress;
	if(argc < 2)
		return -1;
	if(CALCEXP(argv[1],&dwAddress)==FALSE)
		return 1;
	if(Reg.EFlags & 0x20000)
	{
		OUTPUT(WSTR("Paging is only supported in 32-bit mode.\n"));
		return 1;
	}
	if((Reg.EFlags & 0x200)==0)
	{
		OUTPUT(WSTR("Interrupts must be enabled to page in memory.\n"));
		return 1;
	}
	if(Reg.SegReg[CS_IDX] & 3)
	{
		if(dwAddress<0x80000000)
		{
			OUTPUT(WSTR("Function not implemented\n"));
		}
	}
	return 0;
}

int i1here_command(int argc, WCHAR *argv[],PCWSTR szCommandLine,CSyser* pSyser)
{
	if(argc==1)
	{
		if(pSyser->m_bInterrupt1HereStat)
			OUTPUT(WSTR("I1Here is on\n"));
		else
			OUTPUT(WSTR("I1Here is off\n"));
		return 1;
	}
	if(argc == 2)
	{		
		if(TStrICmp(argv[1],WSTR("ON"))==0)
		{
			pSyser->m_bInterrupt1HereStat=true;
			return 1;
		}
		if(TStrICmp(argv[1],WSTR("Off"))==0)
		{
			pSyser->m_bInterrupt1HereStat=false;
			return 1;
		}
	}
	OUTPUT(WSTR("Error : %<3>Input error !\n"));
	return 0;
}

int i3here_command(int argc, WCHAR* argv[],PCWSTR szCommandLine,CSyser *pSyser)
{
	if(argc==1)
	{
		switch(pSyser->m_Interrupt3HereStat)
		{
		case 1:
			OUTPUT(WSTR("I3Here is on\n"));
			break;
		case 2:
			OUTPUT(WSTR("I3Here is on for device drivers (addr > 2G)\n"));
			break;
		case 0:
			OUTPUT(WSTR("I3Here is off\n"));
			break;
		}					
		return 0;
	}
	if(argc == 2)
	{		
		if(TStrICmp(argv[1],WSTR("ON"))==0)
		{
			pSyser->m_Interrupt3HereStat=1;
			return 1;
		}
		if(TStrICmp(argv[1],WSTR("OFF"))==0)
		{
			pSyser->m_Interrupt3HereStat=0;
			return 1;
		}
		if(TStrICmp(argv[1],WSTR("DRV"))==0)
		{
			pSyser->m_Interrupt3HereStat=2;
			return 1;
		}
	}
	OUTPUT(WSTR("Error : %<3>Input error !\n"));
	return 0;
}

int genint_command(int argc, WCHAR* argv[],PCWSTR szCommandLine,CSyser *pSyser)
{
	DWORD dwInterruptNumber;
	if(argc != 2 || CALCEXP(argv[1],&dwInterruptNumber)==FALSE)
	{
		OUTPUT(WSTR("Error : %<3>Input error !\n"));
		return -1;
	}
	if(dwInterruptNumber>0xff)
	{
		OUTPUT(WSTR("Error : %<3>Input error !\n"));
		return -1;
	}
	if(Reg.SegReg[CS_IDX] & 0x3)
	{
	}
	else
	{
		gGenInterruptNumber = dwInterruptNumber;
		gGenInterruptOffset = MAKE_DWORD(gOldInterruptDescropterTable[dwInterruptNumber].OffsetHigh,gOldInterruptDescropterTable[dwInterruptNumber].OffsetLow);
		pSyser->Exit();
	}
	return 0;
}



int hboot_command(int argc,WCHAR *argv[],PCWSTR szCommandLine,CSyser *pSyser)
{
	SyserResetSystem();
	return 0;
}



int	vad_command(int argc,WCHAR *argv[],PCWSTR szCommandLine,CSyser *pSyser)
{
	OUTPUT(WSTR("Process [%s] , PEPROCESS [%08X] VADRoot[%08X]\n"),
		(PCWSTR)gpSyser->m_pDebugger->m_ProcNameW,gpSyser->m_pDebugger->m_PEProcess,gpSyser->m_pDebugger->m_PEProcess->VadRoot);
	return 1;
}

int bpr_command(int argc,WCHAR *argv[],PCWSTR szCommandLine,CSyser *pSyser)
{	

	DWORD dwVirtualAddress;
	DWORD dwRangeStart;
	DWORD dwRangeLength;
	DWORD dwRangeEnd;
	DWORD dwMode;
	BP_RANGE_INFO Bpr;
	PROC_RANGE_BP_MAP::IT FindIT;
	BP_RANGE_LIST::IT BprIT;
	if(argc <4)
		goto error_label;
	DWORD dwProcess = GetEProcessPointer(argv[1]);
	if(dwProcess==0)
		goto error_label;	
	if(CALCEXP(argv[2],&dwRangeStart) == false)
		goto error_label;
	if(dwRangeStart>=0x80000000)
		goto error_label;
	if(CALCEXP(argv[3],&dwRangeLength) == false)
		goto error_label;
	dwRangeEnd = dwRangeStart+dwRangeLength;
	if(dwRangeEnd>=0x80000000)
		dwRangeLength = 0x80000000-dwRangeStart-1;
	dwMode = *(DWORD*)&argv[4][0];
	switch(dwMode)
	{
		case 'r':
		case 'R':			
			dwMode=BP_TYPE_READ;
			break;
		case 'w':
		case 'W':
			dwMode=BP_TYPE_WRITE;
			break;
		case 'x':
		case 'X':
			dwMode=BP_TYPE_EXECUTE;
			break;
		case 0x720077:
		case 0x720057:
		case 0x770072:
		case 0x770052:
		case 0x520077:
		case 0x520057:
		case 0x570052:
		case 0x570072:
			if(argv[4][2]!=0)
				return 1;
				dwMode=BP_TYPE_READWRITE;
			break;
		default:
			dwMode=0;
			break;
	}
	if(dwMode==0)
		return 1;
	CHAR Name[256],Condition[256],DoCmd[256];
	Condition[0]=0;
	DoCmd[0]=0;

	if(get_command_condition_string(argc,argv,szCommandLine,Condition,256)>0)
	{
		if(CALCEXP(Condition,NULL)==false)
		{
			OUTPUT(WSTR("Error : Invalid condition string !\n"));
			return -1;
		}
	}
	get_do_command_string(argc,argv,szCommandLine,DoCmd,256);
	
	FindIT = gpSyser->m_RangeBPList.Find(dwProcess);
	if(FindIT==gpSyser->m_RangeBPList.End())
	{
		FindIT = gpSyser->m_RangeBPList.InsertUnique(dwProcess,BP_RANGE_LIST());
	}
	if(FindIT == gpSyser->m_RangeBPList.End())
		goto error_label;
	
	DWORD PageSize;
	DWORD PageSizeBak;
	DWORD PTESize=0;
	void* pteptr;
	pteptr = GetPTE(dwRangeStart,&PageSize,&PTESize);
	PageSizeBak=PageSize;
	Bpr.RangeStartAddress=dwRangeStart;
	Bpr.RangeLength=dwRangeLength;
	Bpr.Type=dwMode;
	Bpr.State=BP_STATE_ENABLE;
	Bpr.PageSize=PageSize;
	Bpr.PTECount=0;
	Bpr.PTESize=(WORD)PTESize;
	Bpr.PTEAddress=(DWORD)pteptr;
	BprIT = FindIT->Append(Bpr);
	if(BprIT!=FindIT->End())
	{
		BprIT->DoCmd=DoCmd;
		BprIT->Condition=Condition;
	}
	return 0;
error_label:
	OUTPUT(cmd_bpr_usage);
	return 1;
}



int	pte_command(int argc,WCHAR *argv[],PCWSTR szCommandLine,CSyser *pSyser)
{
	DWORD dwTmp;
	CR4REGISTER stCR4;
	CPUID_1_EDX_FEATURE stCPUID_1_EDX;
	X86_PDE *pCurrentPDEBegin;
	X86_PTE *dwPageTableBegin;	
	X86_36_PDE* PDE36Value;
	X86_36_PDE_2M* PDE36Value2M;
	X86_36_PTE* PTE36Value;
	CPUID_INFO TmpInfo;
	DWORD dwPageDirectoryIndex;
	DWORD dwVirtualAddress;
	WCHAR *Format=WSTR("%08x    %sP %s %s %s %s %s %s    %08x - %08x\n");
	WCHAR *Format1=WSTR("%08x    %08x      %sP %s %s %s %s %s %s\n");

	pCurrentPDEBegin = (X86_PDE *)PAGE_DIRECTORY_LINES_ADDRESS;
	PDE36Value=(X86_36_PDE*)PAGE_DIRECTORY_36_LINES_ADDRESS;
	PDE36Value2M=(X86_36_PDE_2M*)PAGE_DIRECTORY_36_LINES_ADDRESS;
	if(argc == 2 )
	{		
		if(CALCEXP(argv[1],&dwVirtualAddress) == false)
			return 1;		
		stCPUID_1_EDX = *(CPUID_1_EDX_FEATURE*)&gpCPUIDInfo[1].dwEDX;
		dwTmp = GetCR4Register();		
		stCR4 = *(CR4REGISTER*)&dwTmp;
		if(stCR4.PAE)	
		{
			dwPageDirectoryIndex = dwVirtualAddress;
			dwPageDirectoryIndex >>= 21;
			PTE36Value=(X86_36_PTE*)0xc0000000;
			PTE36Value=&PTE36Value[dwVirtualAddress>>12];
			
			OUTPUT(WSTR("PDE at   %08x        PTE at %08x\n"),&PDE36Value[dwPageDirectoryIndex],PTE36Value);
			DWORD pde_value,pte_value;
			pde_value=ReadDwordDefaultValue((DWORD*)&PDE36Value[dwPageDirectoryIndex],0);
			if(PDE36Value[dwPageDirectoryIndex].u.Page2M)
				pte_value = 0;
			else
				pte_value=ReadDwordDefaultValue((DWORD*)PTE36Value,0);

			OUTPUT(WSTR("contains %08x        contains %08x\n"),pde_value,pte_value);
		}
		else
		{
			
			dwPageDirectoryIndex = dwVirtualAddress;
			dwPageDirectoryIndex >>= 22;
			dwPageTableBegin=(X86_PTE*)(0xc0000000+((dwVirtualAddress>>12)<<2));
			
			OUTPUT(WSTR("PDE at   %08x        PTE at %08x\n"),&pCurrentPDEBegin[dwPageDirectoryIndex],dwPageTableBegin);
			DWORD pde_value,pte_value;
			pde_value=ReadDwordDefaultValue((DWORD*)&pCurrentPDEBegin[dwPageDirectoryIndex],0);
			if(pCurrentPDEBegin[dwPageDirectoryIndex].u.Page4M)
				pte_value = 0;
			else
				pte_value=ReadDwordDefaultValue((DWORD*)dwPageTableBegin,0);

			OUTPUT(WSTR("contains %08x        contains %08x\n"),pde_value,pte_value);
		}
		
	}
	return 0;
}
int	faults_command(int argc,WCHAR *argv[],PCWSTR szCommandLine,CSyser *pSyser)
{
	if(argc==1)
	{
		if(pSyser->m_bFaultsStat)
			OUTPUT(WSTR("Faults is on\n"));
		else
			OUTPUT(WSTR("Faults is off\n"));
		return 0;
	}
	if(argc == 2)
	{		
		if(TStrICmp(argv[1],WSTR("ON"))==0)
		{
			pSyser->m_bFaultsStat=true;
			return 0;
		}
		if(TStrICmp(argv[1],WSTR("Off"))==0)
		{
			pSyser->m_bFaultsStat=false;
			return 0;
		}
	}
	OUTPUT(WSTR("Error : %<3>Input error !\n"));
	return 1;
}

int window_center_command(int argc,WCHAR *argv[],PCWSTR szCommandLine,CSyser *pSyser)
{
	gpSyser->RestoreScreen();
	gpSyser->CenterScreen();
	gpSyser->BackupScreen();
	return 0;
}

int dispinfo_command(int argc,WCHAR *argv[],PCWSTR szCommandLine,CSyser *pSyser)
{
	OUTPUT(WSTR("FrameBuffer\n"));
	OUTPUT(WSTR("Width = %d , Height = %d , Bpp = %d\n"),gpSyser->m_RealFrameBuffer.Width,gpSyser->m_RealFrameBuffer.Height,gpSyser->m_RealFrameBuffer.Bpp);
	OUTPUT(WSTR("LineDistance = 0x%08X\n"),gpSyser->m_RealFrameBuffer.LineDistance);
	OUTPUT(WSTR("Video Buffer = 0x%08X\n"),gpSyser->m_RealFrameBuffer.Buffer);
	return 0;
}

int sysertest(int argc,WCHAR *argv[],PCWSTR szCommandLine,CSyser *pSyser)
{
	OUTPUT(WSTR("SyserDR7 = %08X\n"),SyserDR[7]);
	return 0;
}

int sdsrv_command(int argc,WCHAR *argv[],PCWSTR szCommandLine,CSyser *pSyser)
{
	gpSyser->m_SDServer.StartServer();
	return 0;
}


int plugin_command(int argc,WCHAR *argv[],PCWSTR szCommandLine,CSyser *pSyser)
{
	OUTPUT(WSTR("Plugin Name        Information\n"));
	for(CPluginMap::IT Iter=pSyser->m_PluginMap.Begin();Iter!=pSyser->m_PluginMap.End();Iter++)
	{
		OUTPUT(WSTR("%20s %s\n"),(PCWSTR)Iter.Key(),Iter->PluginInfo);
	}
	return 0;
}

int ioapic_command(int argc,WCHAR *argv[],PCWSTR szCommandLine,CSyser *pSyser)
{
	DWORD Vaule;
	if(gbIsUseAPIC==0)
		return 1;
	OUTPUT(WSTR("IOAPIC Line Address %08x Physical Address %08x\n"),gdwIOAPICLineAddress,gdwIOAPICPhysAddress);
	Vaule = GetIOAPICData(0);
	OUTPUT(WSTR("Address Offset   Default Value   Attribute   Value\n"));
	OUTPUT(WSTR("0                0x0             Read/Write  %08x\n"),Vaule);
	Vaule = GetIOAPICData(1);
	OUTPUT(WSTR("1                0x00170011      Read Only   %08x\n"),Vaule);
	Vaule = GetIOAPICData(2);
	OUTPUT(WSTR("2                0x0             Read Only   %08x\n\n"),Vaule);
	irq_command(1,NULL,NULL,pSyser);
	return 0;
}
int localapic_command(int argc,WCHAR *argv[],PCWSTR szCommandLine,CSyser *pSyser)
{
	if(gbIsUseAPIC==0)
		return 1;
	DWORD Value;
	DWORD* LocalApic;
	int i;
	WCHAR *DeliveryMode[]=
	{
		WSTR("Fixed   "),
		WSTR("Low. Pri"),
		WSTR("SMI     "),
		WSTR("Reserved"),
		WSTR("NMI     "),
		WSTR("INIT    "),
		WSTR("Reserved"),
		WSTR("ExtINT  "),
	};
	LocalApic = *(DWORD**)&gdwLocalAPICLineAddress;
	OUTPUT(WSTR("Local APIC Line Address %08x Physical Address %08x\n"),gdwLocalAPICLineAddress,gdwLocalAPICPhysAddress);
	OUTPUT(WSTR("Index      IRR      ISR     TMR\n"));
	for(i =0;i<8;i++)
	{
		OUTPUT(WSTR("(%02x-%02x)   %08x %08x %08x\n"),i*32,i*32+31,LocalApic[(0x200+i*10)/sizeof(DWORD)],LocalApic[(0x100+i*10)/sizeof(DWORD)],LocalApic[(0x180+i*10)/sizeof(DWORD)]);
	}
	OUTPUT(WSTR("\n"));
	Value = LocalApic[0x20/sizeof(DWORD)];
	OUTPUT(WSTR("Local APIC ID Register:                       %<b>%08x\n"),Value);
	Value = LocalApic[0x30/sizeof(DWORD)];
	OUTPUT(WSTR("Local APIC Version Register:                  %<b>%08x. Max. LVT Entry(16-23)=%d; Version(0-7bit)=%d\n"),Value,(Value>>16)&0xff,Value&0xff);
	OUTPUT(WSTR("Task Priority Register (TPR):                 %<b>%08x\n"),gdwLocalAPICTaskPriority);
	Value = LocalApic[0x90/sizeof(DWORD)];
	OUTPUT(WSTR("Arbitration Priority Register (APR):          %<b>%08x\n"),Value);
	Value = LocalApic[0xa0/sizeof(DWORD)];
	OUTPUT(WSTR("Processor Priority Register (PPR):            %<b>%08x\n"),Value);
	Value = LocalApic[0xd0/sizeof(DWORD)];
	OUTPUT(WSTR("Logical Destination Register:                 %<b>%08x\n"),Value);
	Value = LocalApic[0xe0/sizeof(DWORD)];
	OUTPUT(WSTR("Destination Format Register:                  %<b>%08x\n"),Value);
	Value = LocalApic[0xf0/sizeof(DWORD)];
	OUTPUT(WSTR("Spurious Interrupt Vector Register:           %<b>%08x\n"),Value);
	Value = LocalApic[0x100/sizeof(DWORD)];
	OUTPUT(WSTR("In-Service Register:                          %<b>%08x\n"),Value);
	Value = LocalApic[0x180/sizeof(DWORD)];
	OUTPUT(WSTR("Trigger Mode Register:                        %<b>%08x\n"),Value);
	Value = LocalApic[0x200/sizeof(DWORD)];
	OUTPUT(WSTR("Interrupt Request Register:                   %<b>%08x\n"),Value);
	Value = LocalApic[0x280/sizeof(DWORD)];
	OUTPUT(WSTR("Error Status Register:                        %<b>%08x\n"),Value);
	Value = LocalApic[0x300/sizeof(DWORD)];
	OUTPUT(WSTR("Interrupt Command Register (ICR) [0-31]:      %<b>%08x\n"),Value);
	Value = LocalApic[0x310/sizeof(DWORD)];
	OUTPUT(WSTR("Interrupt Command Register (ICR) [32-63]:     %<b>%08x\n"),Value);
	Value = LocalApic[0x320/sizeof(DWORD)];
	OUTPUT(WSTR("LVT Timer Register:                           %<b>%08x %s\n"),Value,Value&0x1000?WSTR("IDLE        "):WSTR("Send Pending"),Value&0x10000?WSTR("Unmark"):WSTR("Mark"),Value&0x20000?WSTR("Periodic"):WSTR("One-shot"));
	Value = LocalApic[0x330/sizeof(DWORD)];
	OUTPUT(WSTR("LVT Thermal Sensor Register:                  %<b>%08x\n"),Value);
	Value = LocalApic[0x340/sizeof(DWORD)];
	OUTPUT(WSTR("LVT Performance Monitoring Counters Register: %<b>%08x\n"),Value);
	Value = LocalApic[0x350/sizeof(DWORD)];
	OUTPUT(WSTR("LVT LINT0 Register;                           %<b>%08x %s %s %s\n"),Value,DeliveryMode[(Value>>8)&0x7],Value&0x1000?WSTR("IDLE        "):WSTR("Send Pending"),Value&0x20000?WSTR("Unmark"):WSTR("Mark  "));
	Value = LocalApic[0x360/sizeof(DWORD)];
	OUTPUT(WSTR("LVT LINT1 Register:                           %<b>%08x %s %s %s\n"),Value,DeliveryMode[(Value>>8)&0x7],Value&0x1000?WSTR("IDLE        "):WSTR("Send Pending"),Value&0x20000?WSTR("Unmark"):WSTR("Mark  "));
	Value = LocalApic[0x370/sizeof(DWORD)];
	OUTPUT(WSTR("LVT Error Register:                           %<b>%08x\n"),Value);
	Value = LocalApic[0x380/sizeof(DWORD)];
	OUTPUT(WSTR("Initial Count Register (for Timer):           %<b>%08x\n"),Value);
	Value = LocalApic[0x390/sizeof(DWORD)];
	OUTPUT(WSTR("Current Count Register (for Timer):           %<b>%08x\n"),Value);
	Value = LocalApic[0x3e0/sizeof(DWORD)];
	OUTPUT(WSTR("Divide Configuration Register (for Timer):    %<b>%08x\n"),Value);
	return 0;
}



DWORD gHandleFirst[1024];
DWORD gHandleSecond[1024];

typedef struct _XP2600_2180_HANDLE_TABLE_ENTRY /* sizeof 00000008 8 */
{
	union
	{
		void*	Object;
		unsigned long	ObAttributes;
		//struct _XP2600_2180_HANDLE_TABLE_ENTRY_INFO*	InfoTable;
		unsigned long	Value;
	};
	union
	{
		unsigned long	GrantedAccess;
		struct 
		{		
			unsigned short	GrantedAccessIndex;
			unsigned short	CreatorBackTraceIndex;
		};
		long	NextFreeTableEntry;

	};
}HANDLE_TABLE_ENTRY,*PHANDLE_TABLE_ENTRY;



extern "C"
NTSTATUS
ObQueryNameString(
				  IN PVOID  Object,
				  OUT POBJECT_NAME_INFORMATION  ObjectNameInfo,
				  IN ULONG  Length,
				  OUT PULONG  ReturnLength
				  ); 
int Handle_List(DWORD RootAddress,DWORD dwHandleIndex)
{
	DWORD* HandleTableEntry;
	DWORD dwFlags;
	DWORD i,ii,iii=0,j,jj,jjj=0,k,kk,kkk=0;
	DWORD* First;
	DWORD dwFirstValue;
	DWORD* Second;
	PHANDLE_TABLE_ENTRY Three;
	DWORD dwObjectHeader,dwObject;
	if(dwHandleIndex!=0-1)
	{
		iii=(dwHandleIndex & 0x7ffffffc) >> 21;
		jjj=((dwHandleIndex & 0x7ffffffc) >> 11) & 0x3ff;
		kkk=((dwHandleIndex & 0x7ffffffc) >> 2) & 0x1ff;
	}
	
	if(ReadDword((void*)RootAddress,&dwFirstValue)==false)
		return 0;
	RootAddress=dwFirstValue;
	dwFlags=RootAddress&0x3;
	RootAddress&=0xfffffffc;
	
	switch(dwFlags)
	{
	case 0:
		{
			i=1;
			j=1;
			k=512;
			memset(gHandleFirst,0,sizeof(gHandleFirst));
			memset(gHandleSecond,0,sizeof(gHandleSecond));
			gHandleFirst[0]=(DWORD)gHandleSecond;
			gHandleSecond[0]=RootAddress;
			First=gHandleFirst;
			break;
		}
	case 1:
		{
			i=1;j=1024;
			k=512;
			memset(gHandleFirst,0,sizeof(gHandleFirst));
			memset(gHandleSecond,0,sizeof(gHandleSecond));
			gHandleFirst[0]=RootAddress;
			First=gHandleFirst;
			break;
		}
	case 2:
		{
			First=(DWORD*)RootAddress;
			i=1024;
			j=1024;
			k=512;
			break;
		}
	}
	SYSER_PROCESS Process;
	SYSER_THREAD Thread;
	bool bOK;
	DWORD dwCountHandle=0;
	WCHAR TypeName[65];
	WCHAR ObjName[65];
	WCHAR KeyName[512];
	DWORD dwLen1;
	bool bDisplayTitle=false;
	if(dwHandleIndex!=0-1)
	{
		for(ii=0;ii<=iii;ii++)
		{
			Second = (DWORD*)ReadDword((void*)&First[ii],&bOK);
			if(Second==0)
				break;
		}
		if(Second==0)
			return 0;
		for(jj=0;jj<=jjj;jj++)
		{
			Three = (PHANDLE_TABLE_ENTRY)ReadDword((void*)&Second[jj],&bOK);
			if(Three==0)
				break;
		}
		if(Three==0)
			return 0;
		dwHandleIndex=((iii<<19)+(jjj<<9)+kkk)<<2;
		if(ReadDword(&Three[kkk].Object,&dwObjectHeader)==false)
			return 0;
		if(dwObjectHeader==0)
			return 0;		
		if(bDisplayTitle==false)
		{
			OUTPUT(WSTR("Handle    Object    TypeName            Name\n"));
			bDisplayTitle=true;
		}
		dwObject=(dwObjectHeader&0xfffffff8)+0x18;
		dwCountHandle++;				
		OUTPUT(WSTR("%08x  [%08x]  "),dwHandleIndex,dwObjectHeader+0x18);
		if(GetObjectTypeName(dwObject,TypeName))
		{
			OUTPUT(WSTR("%-20s"),TypeName);
			if(TStrICmp(TypeName,"File")==0)
			{						
				FILE_OBJECT* FileObj=(FILE_OBJECT*)(dwObject);
				if(GetFileObjectName(FileObj,TypeName,0))
				{
					OUTPUT(WSTR("%s "),TypeName);
				}
				else
				{							
					if(ReadDword(&FileObj->DeviceObject,&dwObjectHeader))
						if(GetObjectName(dwObjectHeader,ObjName))
							OUTPUT(WSTR("%s "),ObjName);
				}
			}
		}
		if(GetObjectName(dwObject,ObjName))
			OUTPUT(WSTR("%s"),ObjName);
		OUTPUT(WSTR("\n"));
		return 1;
	}

	for(ii=0;ii<i;ii++)
	{		
		Second = (DWORD*)ReadDword((void*)&First[ii],&bOK);
		if(Second==0)
			break;
		
		for(jj=0;jj<j;jj++)
		{
			Three = (PHANDLE_TABLE_ENTRY)ReadDword((void*)&Second[jj],&bOK);
			if(Three==0)
				break;
			Three++;
			
			for(kk=0;kk<k;kk++)
			{
				dwHandleIndex=((ii<<19)+(jj<<9)+kk+1)<<2;
				if(ReadDword(&Three[kk].Object,&dwObjectHeader)==false)
					continue;
				if(dwObjectHeader==0)
					continue;
				if(ReadDwordDefaultValue((void*)dwObjectHeader,0)==0)
					continue;
				if(bDisplayTitle==false)
				{
					OUTPUT(WSTR("Handle    Object    TypeName            Name\n"));
					bDisplayTitle=true;
				}
				dwObject=(dwObjectHeader&0xfffffff8)+0x18;
				dwCountHandle++;				
				OUTPUT(WSTR("%08x  %08x  "),dwHandleIndex,dwObject);
				if(GetObjectTypeName(dwObject,TypeName))
				{
					OUTPUT(WSTR("%-20s"),TypeName);
					if(TStrICmp(TypeName,"File")==0)
					{						
						FILE_OBJECT* FileObj=(FILE_OBJECT*)(dwObject);
						if(GetFileObjectName(FileObj,TypeName,0))
						{
							OUTPUT(WSTR("%s "),TypeName);
						}
						else
						{							
							if(ReadDword(&FileObj->DeviceObject,&dwObjectHeader))
								if(GetObjectName(dwObjectHeader,ObjName))
									OUTPUT(WSTR("%s "),ObjName);
						}
					}
					else if(TStrICmp(TypeName,"Process")==0)
					{
						
						if(GetProcessInfoByEPROCESS(dwObject,&Process))
						{
							TStrCpy(ObjName,Process.ImageFileName);
							OUTPUT(WSTR("%s (%x)"),ObjName,Process.UniqueProcessId);
						}
					} else if(TStrICmp(TypeName,"Thread")==0)
					{
						
						if(GetThreadInfoByETHREAD(dwObject,&Thread))
						{							
							if(GetProcessInfoByEPROCESS(Thread.Process,&Process))
							{
								TStrCpy(ObjName,Process.ImageFileName);
								OUTPUT(WSTR("%s (%x"),ObjName,Process.UniqueProcessId);
							}
							OUTPUT(WSTR(":%x)"),Thread.ThreadID);
						}
					}
				}
				if(GetObjectName(dwObject,ObjName))
					OUTPUT(WSTR("%s"),ObjName);
				OUTPUT(WSTR("\n"));
				
			}
		}
	}
	OUTPUT(WSTR("Handle (%d)\n"),dwCountHandle);
	return 0;
}

int test_command(int argc,WCHAR *argv[],PCWSTR szCommandLine,CSyser *pSyser)
{

	return 0;
}
bool GetProcessInfoByValue(WCHAR* argv,PSYSER_PROCESS Process)
{
	SYSER_THREAD Thread;
	DWORD dwValue=0;
	DWORD dwThread;
	if(argv==NULL)
		return false;
	if(CALCEXP(argv,&dwValue)==false)
	{
		CDbgProcess*pDbgProcess;
		pDbgProcess=gpSyser->m_SysInfo.GetProcess(argv);
		if(pDbgProcess==NULL)
			return false;
		dwValue=(DWORD)pDbgProcess->GetEPROCESS();	
		return GetProcessInfoByEPROCESS(dwValue,Process);
	}
	SYSER_VALUE_TYPE Type = GetValueType(dwValue);
	switch(Type)
	{
	case VALUE_TYPE_THREAD_ID:
		if(GetThreadByID(dwValue,&Thread))
			return GetProcessInfoByEPROCESS(Thread.Process,Process);
		break;
	case VALUE_TYPE_THREAD_PTR:
		if(GetThreadInfoByETHREAD(dwValue,&Thread)==false)
			return false;
		dwValue=Thread.Process;
	case VALUE_TYPE_PROCESS_PTR:
		return GetProcessInfoByEPROCESS(dwValue,Process);
	case VALUE_TYPE_PROCESS_ID:
		return GetProcessByID(dwValue,Process);					 
	}
	return false;
	
}
int handle_command(int argc,WCHAR *argv[],PCWSTR szCommandLine,CSyser *pSyser)
{
	SYSER_PROCESS Process;
	WCHAR Name[32];
	DWORD dwThread,dwProcess;
	DWORD dwRootAddress;
	DWORD dwRootAddress1=0;
	bool bOK;	
	DWORD dwHandle;
	if(argc==1)
	{
		if(GetCurrentProcessInfo(&Process)==false)
		{
			OUTPUT(WSTR("handle : Get Process information error!\n"));
			return 1;
		}		
		Handle_List(Process.ObjectTable,0-1);
		return 0;
	}
	if(argc>3)
	{
error:
		OUTPUT(cmd_handle_usage);
		return 1;
	}
	if(GetProcessInfoByValue(argv[1],&Process)==false)		
	{
		if(CALCEXP(argv[1],&dwHandle)==false)
		{
			goto error;
		}
		if(dwHandle==0 || dwHandle==0-1)
			dwHandle=0-1;
		if(argc==3)
		{
			if(GetProcessInfoByValue(argv[2],&Process)==false)
				goto error;
		}
		else
		{
			if(GetCurrentProcessInfo(&Process)==false)
				goto error;
		}
	}
	else
	{
		dwHandle=0-1;		
		if(argc==3)
		{
			if(CALCEXP(argv[2],&dwHandle))
			{
				if(dwHandle==0 || dwHandle==0-1)
					dwHandle=0-1;
			}
			else
				goto error;
		}
	}
	
	Handle_List(Process.ObjectTable,dwHandle);
	return 0;

}

int TerminateProcess_command(int argc,WCHAR *argv[],PCWSTR szCommandLine,CSyser *pSyser)
{
	DWORD ExitCode=0,BaseAddress;
	DWORD CodeBufer[]={
		0x68909090,//push exitcode
		0,         //     exitcode          
		0xe8909090,//call GetCurrentProcess
		0,         //		
		0xe8909050,//push eax   call TerminateProcess
		0x0,       //
		0xc3909090,//ret		
	};
	if(argc>2)
	{
		OUTPUT(WSTR("Error: exitprocess exitcode\n"));
		return 1;
	}
	if(argc==2)
	{
		CALCEXP(argv[1],&ExitCode);
	}
	CodeBufer[1]=ExitCode;
	if(pSyser->m_pOrgProcess->m_PID==0 || 
		pSyser->m_pOrgProcess->m_PID==4 || 
		TStrNICmp((WCHAR*)pSyser->m_pOrgProcess->m_ProcNameW,"lsass.exe",9)==0 ||
		TStrNICmp((WCHAR*)pSyser->m_pOrgProcess->m_ProcNameW,"smss.exe",8)==0 ||
		TStrNICmp((WCHAR*)pSyser->m_pOrgProcess->m_ProcNameW,"services.exe",12)==0 ||
		pSyser->m_pOrgProcess == pSyser->m_pCsrssProcess
		)
	{
		OUTPUT(WSTR("Error: not exit %s process\n"),(WCHAR*)pSyser->m_pOrgProcess->m_ProcNameW);
		return 1;
	}
	if((Reg.SegReg[CS_IDX]&3)!=3 || gpSyser->m_pOrgProcess!=gpSyser->m_pDebugger || Reg.EIP>=0x80000000)
	{
		return 1;
	}	
	if(GetCurrentIRQLLevel()>=2)
	{
		OUTPUT(WSTR("Error: IRQL must be below DISPATCH_LEVEL.\n"));
		return 1;
	}
	char szSym[MAX_SYMBOL_LEN],szModule[MAX_FN_LEN];
	WCHAR szBuffer[MAX_SYMBOL_LEN],szModuleName[MAX_FN_LEN];
	
	CSymbolModule* pSymMod;
	pSymMod = pSyser->m_pDebugger->GetSymbolModule("kernel32.dll");
	if(pSymMod)
	{



		DWORD GetCurrentProcessAddress;
		DWORD TerminateProcessAddress;
		bool bNXE=false,bPAE=false;
		CPUID_INFO ExInfo,TmpInfo;
		memset(&TmpInfo,0,sizeof(TmpInfo));
		memset(&ExInfo,0,sizeof(ExInfo));
		SyserGetCPUID(&TmpInfo,0x80000000);
		DWORD dwHiMiscFeature,dwLoMiscFeature;
		if(TmpInfo.dwEAX>=0x80000001)
		{		
			SyserGetCPUID(&ExInfo,0x80000001);
			if(((ExInfo.dwEDX & 0x20000000)>>29)==1 || ((ExInfo.dwEDX & 0x100000)>>20)==1)
			{
				bNXE=true;
			}
			if(bNXE)
			{
				if(SyserReadMSR(0xc0000080,&dwHiMiscFeature,&dwLoMiscFeature))
				{
					if(((dwLoMiscFeature&0x800)>>11)==0)
						bNXE=false;
				}
			}				
		}

		bPAE = (GetCR4Register() & CR4_PAE_BIT_MASK) ? true : false;

		if(pSymMod->GetAddress("GetCurrentProcess",&GetCurrentProcessAddress)==false)
			return 1;
		if(pSymMod->GetAddress("TerminateProcess",&TerminateProcessAddress)==false)
			return 1;	
		RUNCMD(WSTR("r eip esp-3c"));
		
		CodeBufer[3]=GetCurrentProcessAddress-Reg.EIP-5-8-3;
		CodeBufer[5]=TerminateProcessAddress-Reg.EIP-5-0x10-3;
		if(bPAE&&bNXE)
		{
			PX86_36_PDE pCurrent36PDEBegin;
			PX86_36_PDE_2M pCurrent36PDE2M;
			PX86_36_PTE pPageTable36Begin;
			pCurrent36PDE2M=(PX86_36_PDE_2M)0xc0600000;
			pCurrent36PDEBegin=(PX86_36_PDE)0xc0600000;
			pPageTable36Begin=(PX86_36_PTE)0xc0000000;
			if(pCurrent36PDEBegin[Reg.EIP>>21].u.Page2M)
			{
				pCurrent36PDEBegin[Reg.EIP>>21].u.NXE=0;
			}
			else
			{
				pPageTable36Begin[Reg.EIP>>12].u.NXE=0;
			}
		}
		SafeMemCopy((BYTE*)Reg.EIP,(BYTE*)CodeBufer,sizeof(CodeBufer));		
		//Reg.GeneReg[ESP_IDX]-=sizeof(CodeBufer);
		//Reg.GeneReg[ESP_IDX]-=0x14;
		//RUNCMD(WSTR("r esp esp-30"));
		//RUNCMD(WSTR("x"));
	}	
	
	gpSyserCfg->m_ExceptionDebugInfo=1;
	return 0;
}

PCWSTR SyserHeapName[]=
{
	WSTR("Main   Heap 主堆    "),
	WSTR("Screen Heap 屏幕堆  "),
	WSTR("Source Heap 源代码堆"),
};

int syserheapinfo_command(int argc,WCHAR *argv[],PCWSTR szCommandLine,CSyser *pSyser)
{
	OUTPUT(WSTR("-------------------------------------------------------------\n"));
	OUTPUT(WSTR("Syser Kernel Debugger Inside Information\n"));
	for(int n=0;n<gMaxUserHeapCount;n++)
	{
		OUTPUT(WSTR("%<F>%s %<1>总空间%<5>%10d%<1>k / 剩余%<5>%10d%<1>k\n"),SyserHeapName[n],gpUserHeap[n]->m_HeapSize/1024,gpUserHeap[n]->m_FreeChunkCount*MP_SIZE/1024);
	}
	OUTPUT(WSTR("-------------------------------------------------------------\n"));
	return 0;
}
typedef struct _SYSER_OBJTAB
{
	DWORD Object;
	DWORD OwnerThread;
	union
	{
		BYTE Flags[4];
		DWORD Value;
		WORD wValue[2];
	};
	
}SYSER_OBJTAB,*PSYSER_OBJTAB;

DWORD GetObjtabRoot()
{	
	if(gpSyser->m_OSMajorVersion==5 && gpSyser->m_OSMinorVersion==0)
		return 0xA0200000;			 
	if(gpSyser->m_OSMajorVersion==5 && gpSyser->m_OSMinorVersion==1)
		return 0xbc510000;
	if(gpSyser->m_OSMinorVersion==6 && gpSyser->m_OSMinorVersion==0)
		return 0xff910000;
	return 0;
}
bool GetObjtabEntry(PSYSER_OBJTAB Info,DWORD& Index,DWORD dwType)
{
	
	DWORD Root=GetObjtabRoot();
	if(Root==0)
		return false;
	PSYSER_OBJTAB ObjTab=(PSYSER_OBJTAB)Root;
	memset(Info,0,sizeof(SYSER_OBJTAB));
	do 
	{
		if(SafeMemCopy((BYTE*)Info,(BYTE*)&ObjTab[Index],sizeof(SYSER_OBJTAB))!=sizeof(SYSER_OBJTAB))
		{
			Index++;
			return false;
		}
		Index++;
	} while(dwType!=0-1 && Info->Flags[0]!=dwType);		
	return true;
}

int bpp_command(int argc,WCHAR *argv[],PCWSTR szCommandLine,CSyser *pSyser)
{
	DWORD dwValue,Address;
	bool bOK=false,bOK1=false;
	SYSER_THREAD pThread;	
	SYSER_VALUE_TYPE ValueType;
	PSYSER_KTRAP_FRAME pTrapFrame;
	SYSER_PROCESS pProcess;

	if(argc!=2)
		return 0;
	if(CALCEXP(argv[1],&dwValue)==false)
		return 0;
	memset(&pThread,0,sizeof(pThread));
	ValueType = GetValueType(dwValue);
	switch(ValueType)
	{
	case VALUE_TYPE_THREAD_PTR:
		bOK=GetThreadInfoByETHREAD(dwValue,&pThread);	
		if(bOK)
			bOK=GetProcessByEPROCESS(pThread.Process,&pProcess);
		break;
	case VALUE_TYPE_THREAD_ID:			
		bOK = GetThreadByID(dwValue,&pThread);	
		if(bOK)
			bOK=GetProcessByEPROCESS(pThread.Process,&pProcess);
		break;		
	case VALUE_TYPE_PROCESS_ID:
		bOK=GetProcessByID(dwValue,&pProcess);
		break;
	case VALUE_TYPE_PROCESS_PTR:
		bOK=GetProcessInfoByEPROCESS(dwValue,&pProcess);
		break;

	}
	
	if(bOK==false)
		return 0;

	memset(&pThread,0,sizeof(pThread));
	bOK1 = GetThreadInfoByETHREAD((DWORD)pProcess.ThreadHead,&pThread);
	TMap<DWORD,DWORD> AddrMap;
	WCHAR cmdString[50];
	TSPrintf(cmdString,WSTR("addr %x"),pProcess.UniqueProcessId);
	RUNCMD(cmdString);
	while(bOK1)
	{
		pTrapFrame = (PSYSER_KTRAP_FRAME)pThread.TrapFrame;
		if(pTrapFrame)
		{
			Address = (DWORD)&pTrapFrame->Eip;
			if(gpSyser->m_pDebugger->ReadMemory(Address,&dwValue,sizeof(dwValue))==sizeof(dwValue))
			{
				if(AddrMap.Find(dwValue)==AddrMap.End())
				{
					TSPrintf(cmdString,WSTR("bpx %08x if PID==%x"),dwValue,pProcess.UniqueProcessId);
					RUNCMD(cmdString);
					AddrMap.InsertUnique(dwValue,0);
				}
			}
		}
		bOK1=GetNextThread(&pThread);		
	}
	AddrMap.Clear();
	return 0;
}

int bpt_command(int argc,WCHAR *argv[],PCWSTR szCommandLine,CSyser *pSyser)
{
	DWORD dwValue,Address;
	bool bOK=false;
	SYSER_THREAD pThread;
	SYSER_VALUE_TYPE ValueType;
	PSYSER_KTRAP_FRAME pTrapFrame;
	SYSER_PROCESS pProcess;
	
	if(argc!=2)
		return 0;
	if(CALCEXP(argv[1],&dwValue)==false)
		return 0;
	memset(&pThread,0,sizeof(pThread));
	ValueType = GetValueType(dwValue);
	switch(ValueType)
	{
		case VALUE_TYPE_THREAD_PTR:
			bOK=GetThreadInfoByETHREAD(dwValue,&pThread);	
			break;
		case VALUE_TYPE_THREAD_ID:			
			bOK = GetThreadByID(dwValue,&pThread);	
			break;
	}
	
	if(bOK==false||pThread.TrapFrame==0)
		return 0;
	memset(&pProcess,0,sizeof(pProcess));
	bOK = GetProcessByEPROCESS(pThread.Process,&pProcess);
	if(bOK==false)
		return 0;
	
	pTrapFrame = (PSYSER_KTRAP_FRAME)pThread.TrapFrame;
	Address = (DWORD)&pTrapFrame->Eip;

	if(gpSyser->m_pDebugger->ReadMemory(Address,&dwValue,sizeof(dwValue))==sizeof(dwValue))
	{
		WCHAR cmdString[50];
		TSPrintf(cmdString,WSTR("addr %x"),pProcess.UniqueProcessId);
		RUNCMD(cmdString);
		TSPrintf(cmdString,WSTR("bpx %08x if TID==%x"),dwValue,pThread.ThreadID);
		RUNCMD(cmdString);
	}
	return 0;
}
int objtab_command(int argc,WCHAR *argv[],PCWSTR szCommandLine,CSyser *pSyser)
{
	CDbgProcess*pDbgProcess=NULL;
	DWORD dwParam;
	WCHAR unknowtype[]=WSTR("???");
	WCHAR* pTypeName;
	WCHAR *TypeName[][2]=
	{
		{WSTR("FREE"),				WSTR("FREE")},
		{WSTR("Hwnd"),             WSTR("HWND")},
		{WSTR("Menu"),			   WSTR("MENU")},
		{WSTR("Icon/Cursor"),	   WSTR("ICON")},
		{WSTR("DeferWindow"),	   WSTR("DFRW")},
		{WSTR("Hook"),			   WSTR("HOOK")},
		{WSTR("Thread Info"),	   WSTR("TINF")},
		{WSTR("CB Format"),		   WSTR("CBF")},
		{WSTR("Call Proc"),		   WSTR("CPD")},
		{WSTR("Accel. Table"),	   WSTR("ACCL")},
		{WSTR("Dde Object"),		WSTR("DDE")},
		{WSTR("???"),			   WSTR("unkB")},
		{WSTR("???"),			   WSTR("unkC")},
		{WSTR("???"),			   WSTR("unkD")},
		{WSTR("Kbd Layout"),	WSTR("KBD")},
		{WSTR("Wndw Station"),	   WSTR("WSTN")},
	};
#ifdef CODE_OS_NT_DRV
	pDbgProcess=gpSyser->m_SysInfo.GetProcess(WSTR("csrss"));
	if(pDbgProcess==NULL)
		return 0;
	gpSyser->MapToProcess(pDbgProcess);		
#endif
	DWORD ObjtabRoot=GetObjtabRoot();
	if(ObjtabRoot==0)
		return 0;
	DWORD dwIndex=0,dwType=0-1;
	SYSER_OBJTAB objtab;
	int i,m,j;
	WCHAR Title[]=WSTR("Object    Type            Id  Handle    Owner     Flags\n");
	DWORD owner;
	DWORD dwHandle;
	DWORD dwCount=0;
	if(argc==1)
	{
		dwIndex=0;
		dwType=-1;
		OUTPUT(Title);
		while(GetObjtabEntry(&objtab,dwIndex,dwType))
		{
			owner=0;
			if(objtab.Value)
			{							
				if(objtab.OwnerThread )
					ReadDword((void*)objtab.OwnerThread,&owner);
				dwHandle=objtab.wValue[1];
				dwHandle<<=0x10;
				dwHandle+=dwIndex;
				if(objtab.Flags[0]<sizeof(TypeName)/sizeof(TypeName[0]))
					pTypeName=TypeName[objtab.Flags[0]][0];
				else
					pTypeName=unknowtype;
				OUTPUT(WSTR("%08x %-15s %02x %08x %08x %02x\n"),objtab.Object,pTypeName,objtab.Flags[0],dwHandle-1,owner,objtab.Flags[1]);
				dwCount++;
			}
		}
		OUTPUT(WSTR("Objects (%d)\n"),dwCount);
		return 0;
	}
	if(argc>1)
	{
		for(i=1;i<argc;i++)
		{
			if(argv[i][0]=='-' || argv[i][0]=='/')
			{
				if((argv[i][1]=='h' || argv[i][1]=='H')&& argv[i][2]==0)
				{
					OUTPUT(WSTR("OBJTAB [-h] [index | handle | type-name]\n\n"));
					OUTPUT(WSTR("Object type names:\n"));
					for(j=0;j<sizeof(TypeName)/sizeof(TypeName[0]);j++)
					{
						OUTPUT(WSTR("%-4s  - %s\n"),TypeName[j][1],TypeName[j][0]);
					}
					return 0;
				}
				else
				{
					OUTPUT(WSTR("Objtab input error!\n"));
					return 0;
				}
			}

			
			if(CALCEXP(argv[i],&dwIndex)==false)
			{
				for(m=0;m<sizeof(TypeName)/sizeof(TypeName[0]);m++)
				{
					if(TStrICmp(TypeName[m][1],argv[i])==0)
					{
						dwType=m;
						dwIndex=0;
						while(GetObjtabEntry(&objtab,dwIndex,dwType))
						{
							owner=0;
							if(objtab.Value)
							{							
								if(objtab.OwnerThread )
									ReadDword((void*)objtab.OwnerThread,&owner);
								dwHandle=objtab.wValue[1];
								dwHandle<<=0x10;
								dwHandle+=dwIndex;
								OUTPUT(WSTR("%08x %-15s %02x %08x %08x %02x\n"),objtab.Object,TypeName[m][0],objtab.Flags[0],dwHandle-1,owner,objtab.Flags[1]);
								dwCount++;
							}
						}
						break;
					}
				}
				if(m==sizeof(TypeName)/sizeof(TypeName[0]))
				{
					OUTPUT(WSTR("Objtab input error!\n"));
					return 0;
				}				
			}
			else
			{
				if(dwIndex>=0x10000)
					dwIndex&=0xffff;
				dwType=0-1;
				if(GetObjtabEntry(&objtab,dwIndex,dwType))
				{
					owner=0;
					if(objtab.Value)
					{							
						if(objtab.OwnerThread )
							ReadDword((void*)objtab.OwnerThread,&owner);
						dwHandle=objtab.wValue[1];
						dwHandle<<=0x10;
						dwHandle+=dwIndex;
						if(objtab.Flags[0]<sizeof(TypeName)/sizeof(TypeName[0]))
							pTypeName=TypeName[objtab.Flags[0]][0];
						else
							pTypeName=unknowtype;
						OUTPUT(WSTR("%08x %-15s %02x %08x %08x %02x\n"),objtab.Object,pTypeName,objtab.Flags[0],dwHandle-1,owner,objtab.Flags[1]);
						dwCount++;
					}
				}
			}						
		}
	}
	OUTPUT(WSTR("Objects (%d)\n"),dwCount);
	return 0;
}

int dt_command(int argc,WCHAR *argv[],PCWSTR szCommandLine,CSyser *pSyser)
{
	return 0;
}

int lastbranch_command(int argc,WCHAR *argv[],PCWSTR szCommandLine,CSyser *pSyser)
{
	DWORD Index,From,To;
	
	for(int i =0;i<16;i++)
	{
		if(GetLastBranchAddress(i,&From,&To)==false)
			break;
		OUTPUT(WSTR("[%d] MSR LastBranchFromIP %08X     LastBranchToIP %08X\n"),i,From,To);
	}
	return 0;
}

