#include "StdAfx.h"
#include "Syser.h"
#include "cmd_cpu.h"



int cpu_command(int argc, WCHAR *argv[ ],PCWSTR szCommandLine, CSyser*pSyser)
{
	typedef struct _CPU_REG_INDEX
	{
		char* name;
		bool Show;
	}CPU_REG_INDEX;
	int i;
	PSAVELOCALAPIC pLocalApic;
	DWORD dwCurrentCpuID;
	DWORD dwCPUIndex;
	PX86_REG_CONTEXT pReg;
	PDECSRIPTOR Decs;
	PCR4REGISTER pCR4;
	PCR3REGISTER pCR3;
	PCR0REGISTER pCR0;
	PCPU_EFLAGS pEfl;
	VADDR32 dwBase,dwSize,dwSelector;
	CPU_REG_INDEX RegIndex[]={{"cr0",false},{"cr3",false},{"cr4",false},{"efl",false}};
	dwCurrentCpuID = GetCurrentCPULocalAPICID();
	if(gCPUNumbers>1 && argc==1)
	{
		
		OUTPUT(WSTR("CPU PKPCR    IDT Base   GDT Base	\n"));
		for(DWORD i = 0; i < gCPUNumbers;i++)
		{
			if(dwCurrentCpuID==i)
				OUTPUT(WSTR("%<b>%d   %08x %08x   %08x\n"),i,gPCRArray[i],gPCRArray[i]->IDT,gPCRArray[i]->GDT);
			else
				OUTPUT(WSTR("%d   %08x %08x   %08x\n"),i,gPCRArray[i],gPCRArray[i]->IDT,gPCRArray[i]->GDT);
		}
		return 0;
	}
	for(i = 1; i < argc;i++)
	{
		for(int j = 0; j < sizeof(RegIndex)/sizeof(RegIndex[0]);j++)
		{
			if(TStrICmp(argv[i],RegIndex[j].name)==0)
			{
				RegIndex[j].Show=true;
				break;
			}
		}
	}
	if(gCPUNumbers==1)
	{
		OUTPUT(WSTR("Generate Register\n"));
		OUTPUT(WSTR("EAX=0x%08X,EBX=0x%08X,ECX=0x%08X,EDX=0x%08X\n"),Reg.GeneReg[EAX_IDX],Reg.GeneReg[EBX_IDX],Reg.GeneReg[ECX_IDX],Reg.GeneReg[EDX_IDX]);
		OUTPUT(WSTR("EDI=0x%08X,ESI=0x%08X,EBP=0x%08X,ESP=0x%08X\n"),Reg.GeneReg[EDI_IDX],Reg.GeneReg[ESI_IDX],Reg.GeneReg[EBP_IDX],Reg.GeneReg[ESP_IDX]);
		OUTPUT(WSTR("EIP=0x%08X,EFlags=0x%08X\n"),Reg.EIP,Reg.EFlags);
		OUTPUT(WSTR("Segment Register\n"));
		OUTPUT(WSTR("CS=0x%04X,DS=0x%04X,ES=0x%04X,FS=0x%04X,GS=0x%04X,SS=0x%04X\n"),Reg.SegReg[CS_IDX],Reg.SegReg[DS_IDX],Reg.SegReg[ES_IDX],Reg.SegReg[FS_IDX],Reg.SegReg[GS_IDX],Reg.SegReg[SS_IDX]);
		OUTPUT(WSTR("Debug Register\n"));
		OUTPUT(WSTR("DR0=0x%08X,DR1=0x%08X,DR2=0x%08X,DR3=0x%08X\n"),Reg.DR[0],Reg.DR[1],Reg.DR[2],Reg.DR[3]);
		OUTPUT(WSTR("DR6=0x%08X,DR7=0x%08X\n"),Reg.DR[6],Reg.DR[7]);
		OUTPUT(WSTR("Control Register\n"));
		OUTPUT(WSTR("CR0=0x%08X,CR2=0x%08X,CR3=0x%08X,CR4=0x%08X\n"),Reg.CR[0],Reg.CR[2],Reg.CR[3],Reg.CR[4]);
		pCR4=(PCR4REGISTER)&Reg.CR[4];
		pCR3=(PCR3REGISTER)&Reg.CR[3];
		pCR0=(PCR0REGISTER)&Reg.CR[0];
		OUTPUT(WSTR("CR0=%08x PE=%d MP=%d EM=%d TS=%d ET=%d NE=%d WP=%d AM=%d CD=%d PG=%d\n"),Reg.CR[0],pCR0->PE,pCR0->MP,pCR0->EM,pCR0->TS,pCR0->ET,pCR0->NE,pCR0->WP,pCR0->AM,pCR0->CD,pCR0->PG);
		OUTPUT(WSTR("CR3=%08x PWT=%d PCD=%d Page-Directory Base=%08x\n"),Reg.CR[3],pCR3->PWT,pCR3->PCD,Reg.CR[3]&0xfffff000);
		OUTPUT(WSTR("CR4=%08x VEM=%d PVI=%d TSD=%d DE=%d PSE=%d PAE=%d MCE=%d PGE=%d PCE=%d OSFXSR=%d OSXMMEXCPT=%d\n"),Reg.CR[4],
			pCR4->VEM,pCR4->PVI,pCR4->TSD,pCR4->DE,pCR4->PSE,pCR4->PAE,pCR4->MCE,pCR4->PGE,pCR4->PCE,pCR4->OSFXSR,pCR4->OSXMMEXCPT);
		pEfl=(PCPU_EFLAGS)&Reg.EFlags;
		OUTPUT(WSTR("EFLAGS=%08x CF=%d PF=%d AF=%d ZF=%d SF=%d TF=%d IF=%d DF=%d OF=%d IOPL=%d NT=%d RF=%d VM=%d AC=%d VIF=%d VIP=%d ID=%d\n"),Reg.EFlags,
			pEfl->CF,pEfl->PF,pEfl->AF,pEfl->ZF,pEfl->SF,pEfl->TF,pEfl->IF,pEfl->DF,pEfl->OF,pEfl->IOPL,pEfl->NT,pEfl->RF,pEfl->VM,pEfl->AC,pEfl->VIF,pEfl->VIP,pEfl->ID);
		dwSelector = SyserGetTSSSelector();
		dwBase =		GetTSSBase(&dwSize);
		OUTPUT(WSTR("TSS Selector=%04x Base=%08x Limit=%04x "),dwSelector,dwBase,dwSize);
		dwBase =		SyserGetIDTBase(&dwSize);
		OUTPUT(WSTR("IDT Base=%08x Limit=%04x\n"),dwBase,dwSize);
		dwBase =		GetLDTBase(&dwSize);
		dwSelector = SyserGetLDTSelector();
		OUTPUT(WSTR("LDT Selector=%04x Base=%08x Limit=%04x "),dwBase,dwSize);
		dwBase =				SyserGetGDTBase(&dwSize);
		OUTPUT(WSTR("GDT Base=%08x Limit=%04x\n"),dwBase,dwSize);	
		if(RegIndex[0].Show)
		{
			OUTPUT(WSTR("                     %<F>CR0 = %08x\n"),Reg.CR[0]);
			OUTPUT(WSTR("             Paging [PG] = %d %<B>(CR0 31 bit) \n"),pCR0->PG);
			OUTPUT(WSTR("      Cache Disable [CD] = %d %<B>(CR0 30 bit)\n"),pCR0->CD);
			OUTPUT(WSTR("  Not Write-through [NW] = %d %<B>(CR0 29 bit)\n"),pCR0->NW);
			OUTPUT(WSTR("     Alignment Mask [AM] = %d %<B>(CR0 18 bit)\n"),pCR0->AM);
			OUTPUT(WSTR("      Write Protect [WP] = %d %<B>(CR0 16 bit)\n"),pCR0->WP);
			OUTPUT(WSTR("      Numeric Error [NE] = %d %<B>(CR0  5 bit)\n"),pCR0->NE);
			OUTPUT(WSTR("     Extension Type [ET] = %d %<B>(CR0  4 bit)\n"),pCR0->ET);
			OUTPUT(WSTR("      Task Switched [TS] = %d %<B>(CR0  3 bit)\n"),pCR0->TS);
			OUTPUT(WSTR("          Emulation [EM] = %d %<B>(CR0  2 bit)\n"),pCR0->EM);
			OUTPUT(WSTR("Monitor Coprocessor [MP] = %d %<B>(CR0  1 bit)\n"),pCR0->MP);
			OUTPUT(WSTR("  Protection Enable [PE] = %d %<B>(CR0  0 bit)\n"),pCR0->PE);			
		}
		if(RegIndex[1].Show)
		{
			OUTPUT(WSTR("                                %<F>CR3 = %08x\n"),Reg.CR[3]);
			OUTPUT(WSTR("     Page-level Cache Disable [PCD] = %d %<B>(CR3 4 bit) \n"),pCR3->PCD);
			OUTPUT(WSTR("Page-level Writes transparent [PWT] = %d %<B>(CR0 3 bit)\n"),pCR3->PWT);
			OUTPUT(WSTR("                Page-Directory Base = 0x%08x %<B>(CR0 12-31 bit)\n"),(pCR3->PageDirectoryBase << 12));			
		}
		if(RegIndex[2].Show)
		{
			OUTPUT(WSTR("                                                                              %<F>CR4 = %08x\n"),Reg.CR[4]);
			OUTPUT(WSTR("                                               Virtual-8086 Mode Extensions [VME] = %d %<B>(CR4  0 bit) \n"),pCR4->VEM);
			OUTPUT(WSTR("                                          Protected-Mode Virtual Interrupts [PVI] = %d %<B>(CR4  1 bit) \n"),pCR4->PVI);
			OUTPUT(WSTR("                                                         Time Stamp Disable [TSD] = %d %<B>(CR4  2 bit) \n"),pCR4->TSD);
			OUTPUT(WSTR("                                                        Debugging Extensions [DE] = %d %<B>(CR4  3 bit) \n"),pCR4->DE);
			OUTPUT(WSTR("                                                       Page Size Extensions [PSE] = %d %<B>(CR4  4 bit) \n"),pCR4->PSE);
			OUTPUT(WSTR("                                                 Physical Address Extension [PAE] = %d %<B>(CR4  5 bit) \n"),pCR4->PAE);
			OUTPUT(WSTR("                                                       Machine-Check Enable [MCE] = %d %<B>(CR4  6 bit) \n"),pCR4->MCE);
			OUTPUT(WSTR("                                                         Page Global Enable [PGE] = %d %<B>(CR4  7 bit) \n"),pCR4->PGE);
			OUTPUT(WSTR("                                      Performance-Monitoring Counter Enable [PCE] = %d %<B>(CR4  8 bit) \n"),pCR4->PCE);
			OUTPUT(WSTR("            Operating System Support for FXSAVE and FXRSTOR instructions [OSFXSR] = %d %<B>(CR4  9 bit) \n"),pCR4->OSFXSR);
			OUTPUT(WSTR("Operating System Support for Unmasked SIMD Floating-Point Exceptions [OSXMMEXCPT] = %d %<B>(CR4 10 bit) \n"),pCR4->OSXMMEXCPT);
		}
		if(RegIndex[3].Show)
		{
			OUTPUT(WSTR("                  %<F>EFLAGS = %08x\n"),Reg.EFlags);
			OUTPUT(WSTR("                Carry Flag [CF] = %d %<B>(EFLAGS  0 bit) \n"),pEfl->CF);
			OUTPUT(WSTR("               Parity Flag [PF] = %d %<B>(EFLAGS  2 bit)\n"),pEfl->PF);
			OUTPUT(WSTR("      Auxiliary Carry Flag [AF] = %d %<B>(EFLAGS  4 bit)\n"),pEfl->AF);
			OUTPUT(WSTR("                 Zero Flag [ZF] = %d %<B>(EFLAGS  6 bit)\n"),pEfl->ZF);
			OUTPUT(WSTR("                 Sign Flag [SF] = %d %<B>(EFLAGS  7 bit)\n"),pEfl->SF);
			OUTPUT(WSTR("                 Trap Flag [TF] = %d %<B>(EFLAGS  8 bit)\n"),pEfl->TF);
			OUTPUT(WSTR("     Interrupt Enable Flag [IF] = %d %<B>(EFLAGS  9 bit)\n"),pEfl->IF);
			OUTPUT(WSTR("            Direction Flag [DF] = %d %<B>(EFLAGS 10 bit)\n"),pEfl->DF);
			OUTPUT(WSTR("             Overflow Flag [OF] = %d %<B>(EFLAGS 11 bit)\n"),pEfl->OF);
			OUTPUT(WSTR("     I/O Privilege Level [IOPL] = %d %<B>(EFLAGS 12-13 bit)\n"),pEfl->IOPL);
			OUTPUT(WSTR("               Nested Task [NT] = %d %<B>(EFLAGS 14 bit)\n"),pEfl->NT);
			OUTPUT(WSTR("               Resume Flag [RF] = %d %<B>(EFLAGS 16 bit)\n"),pEfl->RF);
			OUTPUT(WSTR("         Virtual-8086 Mode [VM] = %d %<B>(EFLAGS 17 bit)\n"),pEfl->VM);
			OUTPUT(WSTR("           Alignment Check [AC] = %d %<B>(EFLAGS 18 bit)\n"),pEfl->AC);			
			OUTPUT(WSTR("  Virtual Intterrupt Flag [VIF] = %d %<B>(EFLAGS 19 bit)\n"),pEfl->VIF);
			OUTPUT(WSTR("Virtual Interrupt Pending [VIP] = %d %<B>(EFLAGS 20 bit)\n"),pEfl->VIP);
			OUTPUT(WSTR("                   ID Flag [ID] = %d %<B>(EFLAGS 21 bit)\n"),pEfl->ID);			

		}
	}
	else
	{
		for(i=1;i<argc;i++)
		{
			if(CALCEXP(argv[i],&dwCPUIndex)==FALSE)
				continue;
			if(dwCPUIndex>=gCPUNumbers)
				continue;
			if(dwCurrentCpuID==dwCPUIndex)
				pReg=&Reg;
			else
				pReg = &gpMCPUReg[dwCPUIndex];
			pLocalApic = &gpMCPULocalApic[dwCPUIndex];
			pCR4=(PCR4REGISTER)&pReg->CR[4];
			pCR3=(PCR3REGISTER)&pReg->CR[3];
			pCR0=(PCR0REGISTER)&pReg->CR[0];
			OUTPUT(WSTR("CPU %d\n"),dwCPUIndex);
			OUTPUT(WSTR("Generate Register\n"));
			OUTPUT(WSTR("EAX=0x%08X,EBX=0x%08X,ECX=0x%08X,EDX=0x%08X\n"),pReg->GeneReg[EAX_IDX],pReg->GeneReg[EBX_IDX],pReg->GeneReg[ECX_IDX],pReg->GeneReg[EDX_IDX]);
			OUTPUT(WSTR("EDI=0x%08X,ESI=0x%08X,EBP=0x%08X,ESP=0x%08X\n"),pReg->GeneReg[EDI_IDX],pReg->GeneReg[ESI_IDX],pReg->GeneReg[EBP_IDX],pReg->GeneReg[ESP_IDX]);
			OUTPUT(WSTR("EIP=0x%08X,EFlags=0x%08X\n"),pReg->EIP,pReg->EFlags);
			OUTPUT(WSTR("Segment Register\n"));
			OUTPUT(WSTR("CS=0x%04X,DS=0x%04X,ES=0x%04X,FS=0x%04X,GS=0x%04X,SS=0x%04X\n"),pReg->SegReg[CS_IDX],pReg->SegReg[DS_IDX],pReg->SegReg[ES_IDX],pReg->SegReg[FS_IDX],pReg->SegReg[GS_IDX],pReg->SegReg[SS_IDX]);
			OUTPUT(WSTR("Debug Register\n"));
			OUTPUT(WSTR("DR0=0x%08X,DR1=0x%08X,DR2=0x%08X,DR3=0x%08X\n"),pReg->DR[0],pReg->DR[1],pReg->DR[2],pReg->DR[3]);
			OUTPUT(WSTR("DR6=0x%08X,DR7=0x%08X\n"),pReg->DR[6],pReg->DR[7]);
			OUTPUT(WSTR("Control Register\n"));
			OUTPUT(WSTR("CR0=0x%08X,CR2=0x%08X,CR3=0x%08X,CR4=0x%08X\n"),pReg->CR[0],pReg->CR[2],pReg->CR[3],pReg->CR[4]);
			OUTPUT(WSTR("CR0=%08x PE=%d MP=%d EM=%d TS=%d ET=%d NE=%d WP=%d AM=%d CD=%d PG=%d\n"),pReg->CR[0],pCR0->PE,pCR0->MP,pCR0->EM,pCR0->TS,pCR0->ET,pCR0->NE,pCR0->WP,pCR0->AM,pCR0->CD,pCR0->PG);
			OUTPUT(WSTR("CR3=%08x PWT=%d PCD=%d Page-Directory Base=%08x\n"),pReg->CR[3],pCR3->PWT,pCR3->PCD,pReg->CR[3]&0xfffff000);
			OUTPUT(WSTR("CR4=%08x VEM=%d PVI=%d TSD=%d DE=%d PSE=%d PAE=%d MCE=%d PGE=%d PCE=%d OSFXSR=%d OSXMMEXCPT=%d\n"),pReg->CR[4],
				pCR4->VEM,pCR4->PVI,pCR4->TSD,pCR4->DE,pCR4->PSE,pCR4->PAE,pCR4->MCE,pCR4->PGE,pCR4->PCE,pCR4->OSFXSR,pCR4->OSXMMEXCPT);
			pEfl=(PCPU_EFLAGS)&pReg->EFlags;
			OUTPUT(WSTR("EFLAGS=%08x CF=%d PF=%d AF=%d ZF=%d SF=%d TF=%d IF=%d DF=%d OF=%d IOPL=%d NT=%d RF=%d VM=%d AC=%d VIF=%d VIP=%d ID=%d\n"),pReg->EFlags,
				pEfl->CF,pEfl->PF,pEfl->AF,pEfl->ZF,pEfl->SF,pEfl->TF,pEfl->IF,pEfl->DF,pEfl->OF,pEfl->IOPL,pEfl->NT,pEfl->RF,pEfl->VM,pEfl->AC,pEfl->VIF,pEfl->VIP,pEfl->ID);

			OUTPUT(WSTR("TSS Selector=%04x Base=%08x Limit=%04x "),pReg->TR,0,0);
			OUTPUT(WSTR("IDT Base=%08x Limit=%04x\n"),pReg->IDTBase,pReg->IDTLimit);
			OUTPUT(WSTR("LDT Selector=%04x Base=%08x Limit=%04x "),pReg->LDT,0,0);
			OUTPUT(WSTR("GDT Base=%08x Limit=%04x\n"),pReg->GDTBase,pReg->GDTLimit);

			OUTPUT(WSTR("\n%<d>-------- Local apic --------\n"));
			OUTPUT(WSTR("%-20s: %x\n"),WSTR("ID"),pLocalApic->APIC_ID);
			OUTPUT(WSTR("%-20s: %x\n"),WSTR("Version"),pLocalApic->APICVersion);
			OUTPUT(WSTR("%-20s: %x\n"),WSTR("Task Priority"),pLocalApic->TaskPriority);
			OUTPUT(WSTR("%-20s: %x\n"),WSTR("Arbitration Priority"),pLocalApic->ArbitrationPriority);
			OUTPUT(WSTR("%-20s: %x\n"),WSTR("Processor Priority"),pLocalApic->ProcessorPriority);
			OUTPUT(WSTR("%-20s: %x\n"),WSTR("Destination Format"),pLocalApic->DestinationFormat);
			OUTPUT(WSTR("%-20s: %x\n"),WSTR("Logical Destination"),pLocalApic->LogicalDestination);
			OUTPUT(WSTR("%-20s: %x\n"),WSTR("Spurious Vector"),pLocalApic->SpuriousInterruptVector);
			OUTPUT(WSTR("%-20s: %08x %08x\n"),WSTR("Interrupt Command"),pLocalApic->InterruptCommandHigh,pLocalApic->InterruptCommandLow);
			OUTPUT(WSTR("%-20s: %x\n"),WSTR("LVT (Timer)"),pLocalApic->LVTTimer);
			OUTPUT(WSTR("%-20s: %x\n"),WSTR("LVT (Perf. Counter)"),pLocalApic->LVTPerformanceMonitoringCounters);
			OUTPUT(WSTR("%-20s: %x\n"),WSTR("LVT (Lint0)"),pLocalApic->LVTLINT0);
			OUTPUT(WSTR("%-20s: %x\n"),WSTR("LVT (Lint1)"),pLocalApic->LVTLINT1);
			OUTPUT(WSTR("%-20s: %x\n"),WSTR("LVT (Error)"),pLocalApic->LVTError);			
			OUTPUT(WSTR("%-20s: %x\n"),WSTR("Timer Count"),pLocalApic->InitialCount);
			OUTPUT(WSTR("%-20s: %x\n"),WSTR("Timer Current"),pLocalApic->CurrentCount);
			OUTPUT(WSTR("%-20s: %x\n"),WSTR("Timer Divide"),pLocalApic->DivideConfiguration);
			if(RegIndex[0].Show)
			{
				OUTPUT(WSTR("                     %<F>CR0 = %08x\n"),Reg.CR[0]);
				OUTPUT(WSTR("             Paging [PG] = %d %<B>(CR0 31 bit) \n"),pCR0->PG);
				OUTPUT(WSTR("      Cache Disable [CD] = %d %<B>(CR0 30 bit)\n"),pCR0->CD);
				OUTPUT(WSTR("  Not Write-through [NW] = %d %<B>(CR0 29 bit)\n"),pCR0->NW);
				OUTPUT(WSTR("     Alignment Mask [AM] = %d %<B>(CR0 18 bit)\n"),pCR0->AM);
				OUTPUT(WSTR("      Write Protect [WP] = %d %<B>(CR0 16 bit)\n"),pCR0->WP);
				OUTPUT(WSTR("      Numeric Error [NE] = %d %<B>(CR0  5 bit)\n"),pCR0->NE);
				OUTPUT(WSTR("     Extension Type [ET] = %d %<B>(CR0  4 bit)\n"),pCR0->ET);
				OUTPUT(WSTR("      Task Switched [TS] = %d %<B>(CR0  3 bit)\n"),pCR0->TS);
				OUTPUT(WSTR("          Emulation [EM] = %d %<B>(CR0  2 bit)\n"),pCR0->EM);
				OUTPUT(WSTR("Monitor Coprocessor [MP] = %d %<B>(CR0  1 bit)\n"),pCR0->MP);
				OUTPUT(WSTR("  Protection Enable [PE] = %d %<B>(CR0  0 bit)\n"),pCR0->PE);			
			}
			if(RegIndex[1].Show)
			{
				OUTPUT(WSTR("                                %<F>CR3 = %08x\n"),Reg.CR[3]);
				OUTPUT(WSTR("     Page-level Cache Disable [PCD] = %d %<B>(CR3 4 bit) \n"),pCR3->PCD);
				OUTPUT(WSTR("Page-level Writes transparent [PWT] = %d %<B>(CR0 3 bit)\n"),pCR3->PWT);
				OUTPUT(WSTR("                Page-Directory Base = 0x%08x %<B>(CR0 12-31 bit)\n"),(pCR3->PageDirectoryBase << 12));			
			}
			if(RegIndex[2].Show)
			{
				OUTPUT(WSTR("                                                                              %<F>CR4 = %08x\n"),Reg.CR[4]);
				OUTPUT(WSTR("                                               Virtual-8086 Mode Extensions [VME] = %d %<B>(CR4  0 bit) \n"),pCR4->VEM);
				OUTPUT(WSTR("                                          Protected-Mode Virtual Interrupts [PVI] = %d %<B>(CR4  1 bit) \n"),pCR4->PVI);
				OUTPUT(WSTR("                                                         Time Stamp Disable [TSD] = %d %<B>(CR4  2 bit) \n"),pCR4->TSD);
				OUTPUT(WSTR("                                                        Debugging Extensions [DE] = %d %<B>(CR4  3 bit) \n"),pCR4->DE);
				OUTPUT(WSTR("                                                       Page Size Extensions [PSE] = %d %<B>(CR4  4 bit) \n"),pCR4->PSE);
				OUTPUT(WSTR("                                                 Physical Address Extension [PAE] = %d %<B>(CR4  5 bit) \n"),pCR4->PAE);
				OUTPUT(WSTR("                                                       Machine-Check Enable [MCE] = %d %<B>(CR4  6 bit) \n"),pCR4->MCE);
				OUTPUT(WSTR("                                                         Page Global Enable [PGE] = %d %<B>(CR4  7 bit) \n"),pCR4->PGE);
				OUTPUT(WSTR("                                      Performance-Monitoring Counter Enable [PCE] = %d %<B>(CR4  8 bit) \n"),pCR4->PCE);
				OUTPUT(WSTR("            Operating System Support for FXSAVE and FXRSTOR instructions [OSFXSR] = %d %<B>(CR4  9 bit) \n"),pCR4->OSFXSR);
				OUTPUT(WSTR("Operating System Support for Unmasked SIMD Floating-Point Exceptions [OSXMMEXCPT] = %d %<B>(CR4 10 bit) \n"),pCR4->OSXMMEXCPT);
			}
			if(RegIndex[3].Show)
			{
				OUTPUT(WSTR("                  %<F>EFLAGS = %08x\n"),pReg->EFlags);
				OUTPUT(WSTR("                Carry Flag [CF] = %d %<B>(EFLAGS  0 bit) \n"),pEfl->CF);
				OUTPUT(WSTR("               Parity Flag [PF] = %d %<B>(EFLAGS  2 bit)\n"),pEfl->PF);
				OUTPUT(WSTR("      Auxiliary Carry Flag [AF] = %d %<B>(EFLAGS  4 bit)\n"),pEfl->AF);
				OUTPUT(WSTR("                 Zero Flag [ZF] = %d %<B>(EFLAGS  6 bit)\n"),pEfl->ZF);
				OUTPUT(WSTR("                 Sign Flag [SF] = %d %<B>(EFLAGS  7 bit)\n"),pEfl->SF);
				OUTPUT(WSTR("                 Trap Flag [TF] = %d %<B>(EFLAGS  8 bit)\n"),pEfl->TF);
				OUTPUT(WSTR("     Interrupt Enable Flag [IF] = %d %<B>(EFLAGS  9 bit)\n"),pEfl->IF);
				OUTPUT(WSTR("            Direction Flag [DF] = %d %<B>(EFLAGS 10 bit)\n"),pEfl->DF);
				OUTPUT(WSTR("             Overflow Flag [OF] = %d %<B>(EFLAGS 11 bit)\n"),pEfl->OF);
				OUTPUT(WSTR("     I/O Privilege Level [IOPL] = %d %<B>(EFLAGS 12-13 bit)\n"),pEfl->IOPL);
				OUTPUT(WSTR("               Nested Task [NT] = %d %<B>(EFLAGS 14 bit)\n"),pEfl->NT);
				OUTPUT(WSTR("               Resume Flag [RF] = %d %<B>(EFLAGS 16 bit)\n"),pEfl->RF);
				OUTPUT(WSTR("         Virtual-8086 Mode [VM] = %d %<B>(EFLAGS 17 bit)\n"),pEfl->VM);
				OUTPUT(WSTR("           Alignment Check [AC] = %d %<B>(EFLAGS 18 bit)\n"),pEfl->AC);			
				OUTPUT(WSTR("  Virtual Intterrupt Flag [VIF] = %d %<B>(EFLAGS 19 bit)\n"),pEfl->VIF);
				OUTPUT(WSTR("Virtual Interrupt Pending [VIP] = %d %<B>(EFLAGS 20 bit)\n"),pEfl->VIP);
				OUTPUT(WSTR("                   ID Flag [ID] = %d %<B>(EFLAGS 21 bit)\n"),pEfl->ID);			
			}
		}
	}


	return 0;
}