#include "StdAfx.h"
#include "Syser.h"
#include "cmd_cpuid.h"


PCWSTR szProcessor[]=
{
	WSTR("Original OEM Processor"),
	WSTR("Intel OverDrive Processor"),
	WSTR("Dual processor*"),
	WSTR("Intel reserved")
};

typedef struct _TLBDESCRIPTOR
{
	UCHAR Type;
	char* Descriptor;
}TLBDESCRIPTOR,*PTLBDESCRIPTOR;

TLBDESCRIPTOR gTLBDescriptorArray[]=
{
	{0x00, "Null descriptor"},
	{0x01, "Instruction TLB: 4 KByte pages, 4-way set associative, 32 entries"},
	{0x02, "Instruction TLB: 4 MByte pages, 4-way set associative, 2 entries"},
	{0x03, "Data TLB: 4 KByte pages, 4-way set associative, 64 entries"},
	{0x04, "Data TLB: 4 MByte pages, 4-way set associative, 8 entries"},
	{0x05, "Data TLB1: 4 MByte pages, 4-way set associative, 32 entries"},
	{0x06, "1st-level instruction cache: 8 KBytes, 4-way set associative, 32 byte line size"},
	{0x08, "1st-level instruction cache: 16 KBytes, 4-way set associative, 32 byte line size"},
	{0x0A, "1st-level data cache: 8 KBytes, 2-way set associative, 32 byte line size"},
	{0x0B, "Instruction TLB: 4 MByte pages, 4-way set associative, 4 entries"},
	{0x0C, "1st-level data cache: 16 KBytes, 4-way set associative, 32 byte line size"},
	{0x22, "3rd-level cache: 512 KBytes, 4-way set associative, 64 byte line size, 2 lines per sector"},
	{0x23, "3rd-level cache: 1 MBytes, 8-way set associative, 64 byte line size, 2 lines per sector"},
	{0x25, "3rd-level cache: 2 MBytes, 8-way set associative, 64 byte line size, 2 lines per sector"},
	{0x29, "3rd-level cache: 4 MBytes, 8-way set associative, 64 byte line size, 2 lines per sector"},
	{0x2C, "1st-level data cache: 32 KBytes, 8-way set associative, 64 byte line size"},
	{0x30, "1st-level instruction cache: 32 KBytes, 8-way set associative, 64 byte line size"},
	{0x40, "No 2nd-level cache or, if processor contains a valid 2nd-level cache, no 3rdlevel cache"},
	{0x41, "2nd-level cache: 128 KBytes, 4-way set associative, 32 byte line size"},
	{0x42, "2nd-level cache: 256 KBytes, 4-way set associative, 32 byte line size"},
	{0x43, "2nd-level cache: 512 KBytes, 4-way set associative, 32 byte line size"},
	{0x44, "2nd-level cache: 1 MByte, 4-way set associative, 32 byte line size"},
	{0x45, "2nd-level cache: 2 MByte, 4-way set associative, 32 byte line size"},
	{0x46, "3rd-level cache: 4 MByte, 4-way set associative, 64 byte line size"},
	{0x47, "3rd-level cache: 8 MByte, 8-way set associative, 64 byte line size"},
	{0x49, "2nd-level cache: 4 MByte, 16-way set associative, 64 byte line size"},
	{0x50, "Instruction TLB: 4 KByte and 2-MByte or 4-MByte pages, 64 entries"},
	{0x51, "Instruction TLB: 4 KByte and 2-MByte or 4-MByte pages, 128 entries"},
	{0x52, "Instruction TLB: 4 KByte and 2-MByte or 4-MByte pages, 256 entries"},
	{0x56, "Data TLB0: 4 MByte pages, 4-way set associative, 16 entries"},
	{0x57, "Data TLB0: 4 KByte pages, 4-way associative, 16 entries"},
	{0x5B, "Data TLB: 4 KByte and 4 MByte pages, 64 entries"},
	{0x5C, "Data TLB: 4 KByte and 4 MByte pages,128 entries"},
	{0x5D, "Data TLB: 4 KByte and 4 MByte pages,256 entries"},
	{0x60, "1st-level data cache: 16 KByte, 8-way set associative, 64 byte line size"},
	{0x66, "1st-level data cache: 8 KByte, 4-way set associative, 64 byte line size"},
	{0x67, "1st-level data cache: 16 KByte, 4-way set associative, 64 byte line size"},
	{0x68, "1st-level data cache: 32 KByte, 4-way set associative, 64 byte line size"},
	{0x70, "Trace cache: 12 K-¦Ìop, 8-way set associative"},
	{0x71, "Trace cache: 16 K-¦Ìop, 8-way set associative"},
	{0x72, "Trace cache: 32 K-¦Ìop, 8-way set associative"},
	{0x78, "2nd-level cache: 1 MByte, 4-way set associative, 64byte line size"},
	{0x79, "2nd-level cache: 128 KByte, 8-way set associative, 64 byte line size, 2 lines per sector"},
	{0x7A, "2nd-level cache: 256 KByte, 8-way set associative, 64 byte line size, 2 lines per sector"},
	{0x7B, "2nd-level cache: 512 KByte, 8-way set associative, 64 byte line size, 2 lines per sector"},
	{0x7C, "2nd-level cache: 1 MByte, 8-way set associative, 64 byte line size, 2 lines per sector"},
	{0x7D, "2nd-level cache: 2 MByte, 8-way set associative, 64byte line size"},
	{0x7F, "2nd-level cache: 512 KByte, 2-way set associative, 64-byte line size"},
	{0x82, "2nd-level cache: 256 KByte, 8-way set associative, 32 byte line size"},
	{0x83, "2nd-level cache: 512 KByte, 8-way set associative, 32 byte line size"},
	{0x84, "2nd-level cache: 1 MByte, 8-way set associative, 32 byte line size"},
	{0x85, "2nd-level cache: 2 MByte, 8-way set associative, 32 byte line size"},
	{0x86, "2nd-level cache: 512 KByte, 4-way set associative, 64 byte line size"},
	{0x87, "2nd-level cache: 1 MByte, 8-way set associative, 64 byte line size"},
	{0xB0, "Instruction TLB: 4 KByte pages, 4-way set associative, 128 entries"},
	{0xB3, "Data TLB: 4 KByte pages, 4-way set associative, 128 entries"},
	{0xB4, "Data TLB1: 4 KByte pages, 4-way associative, 256 entries"},
	{0xF0, "64-Byte prefetching"},
	{0xF1, "128-Byte prefetching"},
	{0x0,"Reserved"},
};
PTLBDESCRIPTOR GetTLBDescriptor(UCHAR Type)
{
	int i;
	for(i =0;i<sizeof(gTLBDescriptorArray)/sizeof(gTLBDescriptorArray[0]);i++)
	{
		if(Type==gTLBDescriptorArray[i].Type)
			return &gTLBDescriptorArray[i];
	}
	return &gTLBDescriptorArray[i-1];
}

int cpuid_command(int argc, WCHAR *argv[ ],PCWSTR szCommandLine, CSyser*pSyser)
{
	OUTPUT(WSTR("Pentium TSC calibration. Processor at %<B>%u.%d MHZ\n"),(ULONG)(TscPerSec+500000)/1000000,((TscPerSec+50000)/100000)%10);
	OUTPUT(WSTR("CPUID Information\n"));
	WCHAR wszBuffer[20];
	char szBuffer[20];
	bool bBrandString=false;
	DWORD dwTemp;
	bool bIsAMD=false,bIsIntel=false;
	char* szBrandString;
	WCHAR wszBrandString[250];
	CPUID_INFO TmpInfo[5];
	CPUID_INFO ExInfo;
	DWORD ExtMaxIndex;
	DWORD MaxIndex;
	DWORD dwIndex;
	DWORD i;
	bool bShowAll=false;
	memset(TmpInfo,0,sizeof(TmpInfo));
	SyserGetCPUID(TmpInfo,0);
	MaxIndex=TmpInfo[0].dwEAX;
	memset(TmpInfo,0,sizeof(TmpInfo));
	SyserGetCPUID(TmpInfo,0x80000000);
	ExtMaxIndex = TmpInfo[0].dwEAX;
	if(argc>1)
	{
		for(i = 1; i< (DWORD)argc;i++)
		{
			if(TStrICmp(argv[i],"-a")==0)
			{
				bShowAll=true;
				break;
			}
		}
		if(bShowAll)
		{
			for(i = 0; i <= MaxIndex;i++)
			{
				memset(&ExInfo,0,sizeof(ExInfo));
				SyserGetCPUID(&ExInfo,i);
				OUTPUT(WSTR("CPUID[EAX=%08x] %08x %08x %08x %08x\n"),i,ExInfo.dwEAX,ExInfo.dwEBX,ExInfo.dwECX,ExInfo.dwEDX);
			}
			for(i=0x80000000;i<=ExtMaxIndex;i++)
			{
				memset(&ExInfo,0,sizeof(ExInfo));
				SyserGetCPUID(&ExInfo,i);
				OUTPUT(WSTR("CPUID[EAX=%08x] %08x %08x %08x %08x\n"),i,ExInfo.dwEAX,ExInfo.dwEBX,ExInfo.dwECX,ExInfo.dwEDX);
			}
			return 0;
		}
		for(i = 1; i < (DWORD)argc;i++)
		{
			if(CALCEXP(argv[i],&dwIndex)==FALSE)
				continue;
			if(dwIndex <= MaxIndex || ((dwIndex>=0x80000000) && (dwIndex <= ExtMaxIndex)))
			{
				memset(&ExInfo,0,sizeof(ExInfo));
				SyserGetCPUID(&ExInfo,dwIndex);
				OUTPUT(WSTR("CPUID[EAX=%08x] %08x %08x %08x %08x\n"),dwIndex,ExInfo.dwEAX,ExInfo.dwEBX,ExInfo.dwECX,ExInfo.dwEDX);
			}
		}
		return 0;
	}

	SyserGetCPUID(TmpInfo,0x80000000);
	ExtMaxIndex = TmpInfo[0].dwEAX;
	if(ExtMaxIndex>=0x80000004)
	{
		memset(TmpInfo,0,sizeof(CPUID_INFO));
		memset(&ExInfo,0,sizeof(ExInfo));
		SyserGetCPUID(&ExInfo,0x80000001);
		SyserGetCPUID(&TmpInfo[0],0x80000002);
		SyserGetCPUID(&TmpInfo[1],0x80000003);
		SyserGetCPUID(&TmpInfo[2],0x80000004);
		szBrandString=(char*)&TmpInfo[0];
		TStrCpy(wszBrandString,szBrandString);
		bBrandString=true;
	}

	memset(TmpInfo,0,sizeof(TmpInfo));
	SyserGetCPUID(TmpInfo,0);
	MaxIndex=TmpInfo[0].dwEAX;
	//if(MaxIndex>=1)
	{		
		ZeroMemory(szBuffer,sizeof(szBuffer));
		PUT_DWORD(szBuffer,0,TmpInfo[0].dwEBX);
		PUT_DWORD(szBuffer,4,TmpInfo[0].dwEDX);
		PUT_DWORD(szBuffer,8,TmpInfo[0].dwECX);
		TStrCpy(wszBuffer,szBuffer);
		if(TStrCmp("AuthenticAMD",wszBuffer)==0)
		{
			bIsAMD=true;
			OUTPUT(WSTR("AMD\n"));
		}
		else if(TStrCmp("GenuineIntel",wszBuffer)==0)
			bIsIntel=true;
		OUTPUT(WSTR("                                        Vendor ID String = %<F>\"%s\"\n"),wszBuffer);
	}
	if(MaxIndex>=1)
	{		
		SyserGetCPUID(&TmpInfo[1],1);
		if(bIsIntel)
		{
			OUTPUT(WSTR("                                     Version Information = 0x%08X\n"),TmpInfo[1].dwEAX);
			CPUID_1_EAX_VERSION*pVer = (CPUID_1_EAX_VERSION*)&TmpInfo[1].dwEAX;
			PCPUID_1_ECX_EXTENDED_FEATURE pExtFeature=(PCPUID_1_ECX_EXTENDED_FEATURE)&TmpInfo[1].dwECX;
			OUTPUT(WSTR("                                          Processor Type = 0x%X %<F>%s\n"),pVer->ProcessorType,szProcessor[pVer->ProcessorType]);
			if(bBrandString)
				OUTPUT(WSTR("%<6>%s\n"),wszBrandString);		
			if(pVer->Family==0xf)
				dwTemp = pVer->Family + pVer->ExtendedFamily;
			OUTPUT(WSTR("                                                  Family = 0x%X\n"),pVer->Family);
			if(pVer->Family==0xf || pVer->Family == 0x6)		
				dwTemp=(pVer->Model+(pVer->ExtendedModel<<4));		
			OUTPUT(WSTR("                                                   Model = 0x%X\n"),pVer->Model);
			OUTPUT(WSTR("                                             Stepping ID = 0x%X\n"),pVer->SteppingID);
			OUTPUT(WSTR("                                     %<F>Feature Information = CPUID EAX=0x00000001 EDX=0x%08X\n"),TmpInfo[1].dwEDX);
			CPUID_1_EDX_FEATURE*pFeature = (CPUID_1_EDX_FEATURE*)&TmpInfo[1].dwEDX;
			OUTPUT(WSTR("                             Floating Point Unit On-Chip = %d %<B>(EDX 0  bit)\n"),pFeature->FPU);
			OUTPUT(WSTR("                          Virtual 8086 Mode Enhancements = %d %<B>(EDX 1  bit)\n"),pFeature->VME);
			OUTPUT(WSTR("                                    Debugging Extensions = %d %<B>(EDX 2  bit)\n"),pFeature->DE);
			OUTPUT(WSTR("                                     Page Size Extension = %d %<B>(EDX 3  bit)\n"),pFeature->PSE);
			OUTPUT(WSTR("                                      Time Stamp Counter = %d %<B>(EDX 4  bit)\n"),pFeature->TSC);
			OUTPUT(WSTR("   Model Specific Registers RDMSR and WRMSR Instructions = %d %<B>(EDX 5  bit)\n"),pFeature->MSR);
			OUTPUT(WSTR("                              Physical Address Extension = %d %<B>(EDX 6  bit)\n"),pFeature->PAE);
			OUTPUT(WSTR("                                 Machine Check Exception = %d %<B>(EDX 7  bit)\n"),pFeature->MCE);
			OUTPUT(WSTR("                                   CMPXCHG8B Instruction = %d %<B>(EDX 8  bit)\n"),pFeature->CX8);
			OUTPUT(WSTR("                                            APIC On-Chip = %d %<B>(EDX 9  bit)\n"),pFeature->APIC);
			OUTPUT(WSTR("                       SYSENTER and SYSEXIT Instructions = %d %<B>(EDX 11 bit)\n"),pFeature->SEP);
			OUTPUT(WSTR("                             Memory Type Range Registers = %d %<B>(EDX 12 bit)\n"),pFeature->MTRR);
			OUTPUT(WSTR("                                          PTE Global Bit = %d %<B>(EDX 13 bit)\n"),pFeature->PGE);
			OUTPUT(WSTR("                              Machine Check Architecture = %d %<B>(EDX 14 bit)\n"),pFeature->MCA);
			OUTPUT(WSTR("                           Conditional Move Instructions = %d %<B>(EDX 15 bit)\n"),pFeature->CMOV);
			OUTPUT(WSTR("                                    Page Attribute Table = %d %<B>(EDX 16 bit)\n"),pFeature->PAT);
			OUTPUT(WSTR("                              36-Bit Page Size Extension = %d %<B>(EDX 17 bit)\n"),pFeature->PSE_36);
			OUTPUT(WSTR("                                 Processor Serial Number = %d %<B>(EDX 18 bit)\n"),pFeature->PSN);
			OUTPUT(WSTR("                                     CLFLUSH Instruction = %d %<B>(EDX 19 bit)\n"),pFeature->CLFSH);
			OUTPUT(WSTR("                                             Debug Store = %d %<B>(EDX 21 bit)\n"),pFeature->DS);
			OUTPUT(WSTR("Thermal Monitor and Software Controlled Clock Facilities = %d %<B>(EDX 22 bit)\n"),pFeature->ACPI);
			OUTPUT(WSTR("                                    Intel MMX Technology = %d %<B>(EDX 23 bit)\n"),pFeature->MXX);
			OUTPUT(WSTR("                         FXSAVE and FXRSTOR Instructions = %d %<B>(EDX 24 bit)\n"),pFeature->FXSR);
			OUTPUT(WSTR("                               Streaming SIMD Extensions = %d %<B>(EDX 25 bit)\n"),pFeature->SSE);
			OUTPUT(WSTR("                             Streaming SIMD Extensions 2 = %d %<B>(EDX 26 bit)\n"),pFeature->SSE2);
			OUTPUT(WSTR("                                              Self Snoop = %d %<B>(EDX 27 bit)\n"),pFeature->SS);
			OUTPUT(WSTR("                              Hyper-Threading Technology = %d %<B>(EDX 28 bit)\n"),pFeature->HTT);
			OUTPUT(WSTR("                                         Thermal Monitor = %d %<B>(EDX 29 bit)\n"),pFeature->TM);
			OUTPUT(WSTR("                                    Pending Break Enable = %d %<B>(EDX 31 bit)\n"),pFeature->PBE);
			OUTPUT(WSTR("                            %<F>Extended Feature Information = CPUID EAX=0x00000001 ECX=0x%08X\n"),TmpInfo[1].dwECX);
			OUTPUT(WSTR("                             Streaming SIMD Extensions 3 = %d %<B>(ECX 0  bit)\n"),pExtFeature->SSE3);
			OUTPUT(WSTR("                                           MONITOR/MWAIT = %d %<B>(ECX 3  bit)\n"),pExtFeature->MONITOR);
			OUTPUT(WSTR("                               CPL Qualified Debug Store = %d %<B>(ECX 4  bit)\n"),pExtFeature->DS_CPL);
			OUTPUT(WSTR("                              Virtual Machine Extensions = %d %<B>(ECX 5  bit)\n"),pExtFeature->VMX);
			OUTPUT(WSTR("                     Enhanced Intel SpeedStep technology = %d %<B>(ECX 7  bit)\n"),pExtFeature->EST);
			OUTPUT(WSTR("                                       Thermal Monitor 2 = %d %<B>(ECX 8  bit)\n"),pExtFeature->TM2);
			//OUTPUT(WSTR("                Supplemental Streaming SIMD Extensions 4 = %d %<B>(EDX 1  bit)\n"),pExtFeature->SSSE3);
			OUTPUT(WSTR("                                           L1 Context ID = %d %<B>(ECX 10 bit)\n"),pExtFeature->CNXT_ID);
			OUTPUT(WSTR("                                    CMPXCHG16B Available = %d %<B>(ECX 13 bit)\n"),pExtFeature->CMPXCHG16B);
			OUTPUT(WSTR("                                     xTPR Update Control = %d %<B>(ECX 14 bit)\n"),pExtFeature->xTPR_Update_Control);
			if(ExtMaxIndex>=0x80000004)
			{
				OUTPUT(WSTR("%<F>Extended Processor Signature and Extended Feature Bits.(CPUID EAX=0x80000001 ECX=0x%08x EDX=0x%08x)\n"),ExInfo.dwECX,ExInfo.dwEDX);
				OUTPUT(WSTR("                      LAHF/SAHF available in 64-bit mode = %d %<B>(ECX 1  bit)\n"),ExInfo.dwECX&0x1);
				OUTPUT(WSTR("           SYSCALL/SYSRET available(when in 64-bit mode) = %d %<B>(EDX 11 bit)\n"),(ExInfo.dwEDX & 0x800)>>11);
				OUTPUT(WSTR("                           Execute Disable Bit available = %d %<B>(EDX 20 bit)\n"),(ExInfo.dwEDX & 0x100000)>>20);
				OUTPUT(WSTR("                                   Intel EM64T available = %d %<B>(EDX 29 bit)\n"),(ExInfo.dwEDX & 0x20000000)>>29);
			}
			OUTPUT(WSTR("%<f>CPU TLB Information\n"));
			SyserGetCPUID(TmpInfo,2);
			unsigned char* ucType;
			PTLBDESCRIPTOR pTlbDesc;
			ucType = (unsigned char*)&TmpInfo[0];		
			for(int i = 1;i < sizeof(CPUID_INFO);i++)
			{
				if(ucType[i]==0)
					continue;
				pTlbDesc = GetTLBDescriptor(ucType[i]);
				TStrCpy(wszBrandString,pTlbDesc->Descriptor);
				OUTPUT(WSTR("%02x %s\n"),ucType[i],wszBrandString);
			}
			DWORD dwHiMiscFeature=0,dwLoMiscFeature=0;
			PMSR_IA32_MISC_ENABLE pMiscEnable;
			if(SyserReadMSR(0x1a0,&dwHiMiscFeature,&dwLoMiscFeature))
			{
				OUTPUT(WSTR("                                    %<f>CPU IA32_MISC_ENABLE = MSR 0x000001A0 0x%08x 0x%08x\n"),dwHiMiscFeature,dwLoMiscFeature);
				pMiscEnable = (PMSR_IA32_MISC_ENABLE)&dwLoMiscFeature;
				OUTPUT(WSTR("                                     Fast-Strings Enable = %d %<B>(0  bit)\n"),pMiscEnable->FastString);
				OUTPUT(WSTR("               x87 FPU Fopcode Compatibility Mode Enable = %d %<B>(2  bit)\n"),pMiscEnable->FPUMode);
				OUTPUT(WSTR("                                Thermal Monitor 1 Enable = %d %<B>(3  bit)\n"),pMiscEnable->TM1E);
				OUTPUT(WSTR("                                      Split-Lock Disable = %d %<B>(4  bit)\n"),pMiscEnable->SLD);
				OUTPUT(WSTR("                               Third-Level Cache Disable = %d %<B>(6  bit)\n"),pMiscEnable->TLCD);
				OUTPUT(WSTR("                        Performance Monitoring Available = %d %<B>(7  bit)\n"),pMiscEnable->PMA);
				OUTPUT(WSTR("                                    Suppress Lock Enable = %d %<B>(8  bit)\n"),pMiscEnable->SLE);
				OUTPUT(WSTR("                                  Prefetch Queue Disable = %d %<B>(9  bit)\n"),pMiscEnable->PQD);
				OUTPUT(WSTR("                        FERR# Interrupt Reporting Enable = %d %<B>(10 bit)\n"),pMiscEnable->FerrIRE);
				OUTPUT(WSTR("                        Branch Trace Storage Unavailable = %d %<B>(11 bit)\n"),pMiscEnable->BTSU);
				OUTPUT(WSTR("                Precise Event Based Sampling Unavailable = %d %<B>(12 bit)\n"),pMiscEnable->PEBSU);
				OUTPUT(WSTR("                                              TM2 Enable = %d %<B>(13 bit)\n"),pMiscEnable->TM2E);
				OUTPUT(WSTR("                                      ENABLE MONITOR FSM = %d %<B>(18 bit)\n"),pMiscEnable->EMFSM);
				OUTPUT(WSTR("                    Adjacent Cache Line Prefetch Disable = %d %<B>(19 bit)\n"),pMiscEnable->ACLPD);
				OUTPUT(WSTR("                                      Limit CPUID MAXVAL = %d %<B>(22 bit)\n"),pMiscEnable->LCPUIDMAXVAL);
				OUTPUT(WSTR("                              L1 Data Cache Context Mode = %d %<B>(24 bit)\n"),pMiscEnable->L1DCCM);
			}
			if(SyserReadMSR(0xc0000080,&dwHiMiscFeature,&dwLoMiscFeature))
			{
				OUTPUT(WSTR("                                           %<f>CPU IA32_EFER = MSR 0xC0000080 0x%08x 0x%08x\n"),dwHiMiscFeature,dwLoMiscFeature);				
				OUTPUT(WSTR("                                          SYSCALL Enable = %d %<B>(0  bit)\n"),dwLoMiscFeature&0x1);
				OUTPUT(WSTR("                                      IA-32e Mode Enable = %d %<B>(8  bit)\n"),(dwLoMiscFeature&0x100)>>8);
				OUTPUT(WSTR("                                      IA-32e Mode Active = %d %<B>(10 bit)\n"),(dwLoMiscFeature&0x400)>>10);
				OUTPUT(WSTR("                              Execute Disable Bit Enable = %d %<B>(11 bit)\n"),(dwLoMiscFeature&0x800)>>11);
			}

		}
		else if(bIsAMD)
		{
			PAMD_CPUID_1_EDX pAMDEDX = (PAMD_CPUID_1_EDX)&TmpInfo[1].dwEDX;
			PAMD_CPUID_1_ECX pAMDECX = (PAMD_CPUID_1_ECX)&TmpInfo[1].dwECX;
			OUTPUT(WSTR("                                     %<F>Feature Information = CPUID EAX=0x00000001 EDX=0x%08X\n"),TmpInfo[1].dwEDX);

			//OUTPUT(WSTR("                                 %<F>Feature Information EDX = 0x%08X\n"),TmpInfo[1].dwEDX);
			if(bBrandString)
				OUTPUT(WSTR("%<6>%s\n"),wszBrandString);	
			OUTPUT(WSTR("                             Floating Point Unit On-Chip = %d %<B>(EDX 0  bit)\n"),pAMDEDX->FPU);
			OUTPUT(WSTR("                          Virtual 8086 Mode Enhancements = %d %<B>(EDX 1  bit)\n"),pAMDEDX->VME);
			OUTPUT(WSTR("                                    Debugging Extensions = %d %<B>(EDX 2  bit)\n"),pAMDEDX->DE);
			OUTPUT(WSTR("                                     Page Size Extension = %d %<B>(EDX 3  bit)\n"),pAMDEDX->PSE);
			OUTPUT(WSTR("                                      Time Stamp Counter = %d %<B>(EDX 4  bit)\n"),pAMDEDX->TSC);
			OUTPUT(WSTR("   Model Specific Registers RDMSR and WRMSR Instructions = %d %<B>(EDX 5  bit)\n"),pAMDEDX->MSR);
			OUTPUT(WSTR("                              Physical Address Extension = %d %<B>(EDX 6  bit)\n"),pAMDEDX->PAE);
			OUTPUT(WSTR("                                 Machine Check Exception = %d %<B>(EDX 7  bit)\n"),pAMDEDX->MCE);
			OUTPUT(WSTR("                                   CMPXCHG8B Instruction = %d %<B>(EDX 8  bit)\n"),pAMDEDX->CMPXCHG8B);
			OUTPUT(WSTR("                                            APIC On-Chip = %d %<B>(EDX 9  bit)\n"),pAMDEDX->APIC);
			OUTPUT(WSTR("                       SYSENTER and SYSEXIT Instructions = %d %<B>(EDX 11 bit)\n"),pAMDEDX->SysEnterSysExit);
			OUTPUT(WSTR("                             Memory Type Range Registers = %d %<B>(EDX 12 bit)\n"),pAMDEDX->MTRR);
			OUTPUT(WSTR("                                          PGE Global Bit = %d %<B>(EDX 13 bit)\n"),pAMDEDX->PGE);
			OUTPUT(WSTR("                              Machine Check Architecture = %d %<B>(EDX 14 bit)\n"),pAMDEDX->MCA);
			OUTPUT(WSTR("                           Conditional Move Instructions = %d %<B>(EDX 15 bit)\n"),pAMDEDX->CMOV);
			OUTPUT(WSTR("                                    Page Attribute Table = %d %<B>(EDX 16 bit)\n"),pAMDEDX->PAT);
			OUTPUT(WSTR("                              36-Bit Page Size Extension = %d %<B>(EDX 17 bit)\n"),pAMDEDX->PSE36);
			OUTPUT(WSTR("                                     CLFLUSH Instruction = %d %<B>(EDX 19 bit)\n"),pAMDEDX->CLFSH);
			OUTPUT(WSTR("                                        MMX instructions = %d %<B>(EDX 23 bit)\n"),pAMDEDX->MMX);
			OUTPUT(WSTR("                         FXSAVE and FXRSTOR Instructions = %d %<B>(EDX 24 bit)\n"),pAMDEDX->FXSR);
			OUTPUT(WSTR("                               Streaming SIMD Extensions = %d %<B>(EDX 25 bit)\n"),pAMDEDX->SSE);
			OUTPUT(WSTR("                             Streaming SIMD Extensions 2 = %d %<B>(EDX 26 bit)\n"),pAMDEDX->SSE2);
			OUTPUT(WSTR("                              Hyper-Threading Technology = %d %<B>(EDX 28 bit)\n"),pAMDEDX->HTT);			
			//OUTPUT(WSTR("                                 %<F>Feature Information ECX = 0x%08X\n"),TmpInfo[1].dwECX);
			OUTPUT(WSTR("                                     %<F>Feature Information = CPUID EAX=0x00000001 ECX=0x%08X\n"),TmpInfo[1].dwECX);
			OUTPUT(WSTR("                                    CMPXCHG16B Available = %d %<B>(ECX 0  bit)\n"),pAMDECX->CMPXCHG16B);
			OUTPUT(WSTR("                             Streaming SIMD Extensions 3 = %d %<B>(ECX 13 bit)\n"),pAMDECX->SSE3);
			if(ExtMaxIndex>=0x80000001)
			{
				memset(&ExInfo,0,sizeof(ExInfo));
				SyserGetCPUID(&ExInfo,0x80000001);
				PAMD_CPUID_80000001_EDX pAMDEXEDX = (PAMD_CPUID_80000001_EDX)&ExInfo.dwEDX;
				PAMD_CPUID_80000001_ECX pAMDEXECX = (PAMD_CPUID_80000001_ECX)&ExInfo.dwECX;				
				OUTPUT(WSTR("                            %<F>Extended Feature Information = CPUID EAX=0x80000001 EDX=0x%08X\n"),ExInfo.dwEDX);

				//OUTPUT(WSTR("                        %<F>Extended Feature Information EDX = 0x%08X\n"),ExInfo.dwEDX);
				OUTPUT(WSTR("                             Floating Point Unit On-Chip = %d %<B>(EDX 0  bit)\n"),pAMDEXEDX->FPU);
				OUTPUT(WSTR("                          Virtual 8086 Mode Enhancements = %d %<B>(EDX 1  bit)\n"),pAMDEXEDX->VME);
				OUTPUT(WSTR("                                    Debugging Extensions = %d %<B>(EDX 2  bit)\n"),pAMDEXEDX->DE);
				OUTPUT(WSTR("                                     Page Size Extension = %d %<B>(EDX 3  bit)\n"),pAMDEXEDX->PSE);
				OUTPUT(WSTR("                                      Time Stamp Counter = %d %<B>(EDX 4  bit)\n"),pAMDEXEDX->TSC);
				OUTPUT(WSTR("   Model Specific Registers RDMSR and WRMSR Instructions = %d %<B>(EDX 5  bit)\n"),pAMDEXEDX->MSR);
				OUTPUT(WSTR("                              Physical Address Extension = %d %<B>(EDX 6  bit)\n"),pAMDEXEDX->PAE);
				OUTPUT(WSTR("                                 Machine Check Exception = %d %<B>(EDX 7  bit)\n"),pAMDEXEDX->MCE);
				OUTPUT(WSTR("                                   CMPXCHG8B Instruction = %d %<B>(EDX 8  bit)\n"),pAMDEXEDX->CMPXCHG8B);
				OUTPUT(WSTR("                                            APIC On-Chip = %d %<B>(EDX 9  bit)\n"),pAMDEXEDX->APIC);
				OUTPUT(WSTR("                         SYSCALL and SYSRET instructions = %d %<B>(EDX 11 bit)\n"),pAMDEXEDX->SysCallSysRet);
				OUTPUT(WSTR("                             Memory Type Range Registers = %d %<B>(EDX 12 bit)\n"),pAMDEXEDX->MTRR);
				OUTPUT(WSTR("                                          PGE Global Bit = %d %<B>(EDX 13 bit)\n"),pAMDEXEDX->PGE);
				OUTPUT(WSTR("                              Machine Check Architecture = %d %<B>(EDX 14 bit)\n"),pAMDEXEDX->MCA);
				OUTPUT(WSTR("                           Conditional Move Instructions = %d %<B>(EDX 15 bit)\n"),pAMDEXEDX->CMOV);
				OUTPUT(WSTR("                                    Page Attribute Table = %d %<B>(EDX 16 bit)\n"),pAMDEXEDX->PAT);
				OUTPUT(WSTR("                              36-Bit Page Size Extension = %d %<B>(EDX 17 bit)\n"),pAMDEXEDX->PSE36);
				OUTPUT(WSTR("                              No-execute page protection = %d %<B>(EDX 20 bit)\n"),pAMDEXEDX->NX);				
				OUTPUT(WSTR("                      AMD extensions to MMX instructions = %d %<B>(EDX 22 bit)\n"),pAMDEXEDX->MmxExt);
				OUTPUT(WSTR("                                        MMX instructions = %d %<B>(EDX 23 bit)\n"),pAMDEXEDX->MMX);
				OUTPUT(WSTR("                         FXSAVE and FXRSTOR Instructions = %d %<B>(EDX 24 bit)\n"),pAMDEXEDX->FXSR);
				OUTPUT(WSTR("           FXSAVE and FXRSTOR Instructions optimizations = %d %<B>(EDX 25 bit)\n"),pAMDEXEDX->FFXSR);				
				OUTPUT(WSTR("                                      RDTSCP instruction = %d %<B>(EDX 27 bit)\n"),pAMDEXEDX->RDTSCP);
				OUTPUT(WSTR("                                               Long mode = %d %<B>(EDX 29 bit)\n"),pAMDEXEDX->LM);
				OUTPUT(WSTR("                   AMD extensions to 3DNow! instructions = %d %<B>(EDX 30 bit)\n"),pAMDEXEDX->_3DNowExt);
				OUTPUT(WSTR("                                     3DNow! instructions = %d %<B>(EDX 31 bit)\n"),pAMDEXEDX->_3DNow);	
				//OUTPUT(WSTR("                        %<F>Extended Feature Information ECX = 0x%08X\n"),ExInfo.dwECX);
				OUTPUT(WSTR("                            %<F>Extended Feature Information = CPUID EAX=0x80000001 ECX = 0x%08X\n"),ExInfo.dwECX);
				OUTPUT(WSTR("        LAHF and SAHF instruction support in 64-bit mode = %d %<B>(ECX 0 bit)\n"),pAMDEXECX->LahfSahf);
				OUTPUT(WSTR("                       Core multi-processing legacy mode = %d %<B>(ECX 1 bit)\n"),pAMDEXECX->CmpLegacy);
				OUTPUT(WSTR("                          Secure virtual machine feature = %d %<B>(ECX 2 bit)\n"),pAMDEXECX->SVM);				
				OUTPUT(WSTR("                              LOCK MOV CR0 means MOV CR8 = %d %<B>(ECX 4 bit)\n"),pAMDEXECX->AltMovCr8);

			}
			if(ExtMaxIndex>=0x80000005)
			{				
				memset(TmpInfo,0,sizeof(TmpInfo));
				SyserGetCPUID(TmpInfo,0x80000005);
				switch(TmpInfo[0].dwEAX >>24)
				{
				case 0:
					OUTPUT(WSTR("L1 2M/4M Page Data TLB %<B>Reserved. "));
					break;
				case 1:
					OUTPUT(WSTR("L1 2M/4M Page Data TLB %<B>Direct mapped. "));
					break;
				case 0xff:
					OUTPUT(WSTR("L1 2M/4M Page Data TLB %<B>Fully associative. "));	
					break;
				default:
					OUTPUT(WSTR("L1 2M/4M Page Data TLB %<B>%d-way associative. "),(TmpInfo[0].dwEAX >>24));
					break;
				}
				OUTPUT(WSTR("%d entries.\n"),((TmpInfo[0].dwEAX>>16)&0xff));
				switch((TmpInfo[0].dwEAX >>8)&0xff)
				{
				case 0:
					OUTPUT(WSTR("L1 2M/4M Page Instruction TLB %<B>Reserved. "));
					break;
				case 1:
					OUTPUT(WSTR("L1 2M/4M Page Instruction TLB %<B>Direct mapped. "));
					break;
				case 0xff:
					OUTPUT(WSTR("L1 2M/4M Page Instruction TLB %<B>Fully associative. "));	
					break;
				default:
					OUTPUT(WSTR("L1 2M/4M Page Instruction TLB %<B>%d-way associative. "),((TmpInfo[0].dwEAX >>8)&0xff));
					break;
				}
				OUTPUT(WSTR("%d entries.\n"),(TmpInfo[0].dwEAX&0xff));
				switch(TmpInfo[0].dwEBX >>24)
				{
				case 0:
					OUTPUT(WSTR("L1 4K Page Data TLB %<B>Reserved. "));
					break;
				case 1:
					OUTPUT(WSTR("L1 4K Page Data TLB %<B>Direct mapped. "));
					break;
				case 0xff:
					OUTPUT(WSTR("L1 4K Page Data TLB %<B>Fully associative. "));	
					break;
				default:
					OUTPUT(WSTR("L1 4K Page Data TLB %<B>%d-way associative. "),(TmpInfo[0].dwEBX >>24));
					break;
				}
				OUTPUT(WSTR("%d entries.\n"),((TmpInfo[0].dwEBX>>16)&0xff));
				switch((TmpInfo[0].dwEBX >>8)&0xff)
				{
				case 0:
					OUTPUT(WSTR("L1 4K Page Instruction TLB %<B>Reserved. "));
					break;
				case 1:
					OUTPUT(WSTR("L1 4K Page Instruction TLB %<B>Direct mapped. "));
					break;
				case 0xff:
					OUTPUT(WSTR("L1 4K Page Instruction TLB %<B>Fully associative. "));	
					break;
				default:
					OUTPUT(WSTR("L1 4K Page Instruction TLB %<B>%d-way associative. "),((TmpInfo[0].dwEBX >>8)&0xff));
					break;
				}
				OUTPUT(WSTR("%d entries.\n"),(TmpInfo[0].dwEBX&0xff));
				if((TmpInfo[0].dwEDX >> 24))
				{
					OUTPUT(WSTR("L1 instruction cache %d KB, "),(TmpInfo[0].dwEDX >> 24));
					switch((TmpInfo[0].dwEDX >> 16)&0xff)
					{
					case 1:
						OUTPUT(WSTR("Direct mapped. "));
						break;
					case 0xff:
						OUTPUT(WSTR("Fully associative. "));
						break;
					default:
						OUTPUT(WSTR("%d-way associative. "),((TmpInfo[0].dwEDX >> 16)&0xff));
						break;
					}
					OUTPUT(WSTR("cache line %d Bytes\n"),(TmpInfo[0].dwEDX&0xff));
				}
				if((TmpInfo[0].dwECX >> 24))
				{
					OUTPUT(WSTR("L1 data cache %d KB, "),(TmpInfo[0].dwECX >> 24));
					switch((TmpInfo[0].dwECX >> 16)&0xff)
					{
					case 1:
						OUTPUT(WSTR("Direct mapped. "));
						break;
					case 0xff:
						OUTPUT(WSTR("Fully associative. "));
						break;
					default:
						OUTPUT(WSTR("%d-way associative. "),((TmpInfo[0].dwECX >> 16)&0xff));
						break;
					}
					OUTPUT(WSTR("cache line %d Bytes\n"),(TmpInfo[0].dwECX&0xff));
				}
				//OUTPUT(WSTR("L1 data cache %d KB, %d-way associative. cache line %d Bytes\n"),(TmpInfo[0].dwECX >> 24),((TmpInfo[0].dwECX >> 16)&0xff),(TmpInfo[0].dwECX&0xff));
				//OUTPUT(WSTR("EAX=%08x EBX=%08x ECX=%08x EDX=%08x\n"),TmpInfo[0].dwEAX,TmpInfo[0].dwEBX,TmpInfo[0].dwECX,TmpInfo[0].dwEDX);
			}
			if(ExtMaxIndex>=0x80000006)
			{
				WCHAR* Associative[]={
					WSTR("%<b>The L2 cache disabled."),
						WSTR("Direct mapped."),
						WSTR("2-way associative."),
						WSTR("Reserved"),
						WSTR("4-way associative."),
						WSTR("Reserved"),
						WSTR("8-way associative."),
						WSTR("Reserved"),
						WSTR("16-way associative."),
						WSTR("Reserved"),
						WSTR("32-way associative."),
						WSTR("48-way associative."),
						WSTR("64-way associative."),
						WSTR("96-way associative."),
						WSTR("128-way associative."),
						WSTR("Fully associative."),
				};

				memset(TmpInfo,0,sizeof(TmpInfo));
				SyserGetCPUID(TmpInfo,0x80000006);
				//OUTPUT(WSTR("EAX=%08x EBX=%08x ECX=%08x EDX=%08x\n"),TmpInfo[0].dwEAX,TmpInfo[0].dwEBX,TmpInfo[0].dwECX,TmpInfo[0].dwEDX);				
				switch(TmpInfo[0].dwEAX >>28)
				{
				case 0:
					OUTPUT(WSTR("L2 2M/4M Page Data TLB %<B>disabled. "));
					break;
				default:
					OUTPUT(WSTR("L2 2M/4M Page Data TLB %<B>%s. "),Associative[TmpInfo[0].dwEAX >>28]);
					break;
				}
				OUTPUT(WSTR("%d entries.\n"),((TmpInfo[0].dwEAX>>16)&0xfff));
				switch((TmpInfo[0].dwEAX >>12)&0xf)
				{
				case 0:
					OUTPUT(WSTR("L2 2M/4M Page Instruction TLB %<B>disabled. "));
					break;				
				default:
					OUTPUT(WSTR("L2 2M/4M Page Instruction TLB %<B>%s. "),Associative[((TmpInfo[0].dwEAX >>12)&0xf)]);
					break;
				}				
				OUTPUT(WSTR("%d entries.\n"),(TmpInfo[0].dwEAX&0xfff));
				switch(TmpInfo[0].dwEBX >>28)
				{
				case 0:
					OUTPUT(WSTR("L2 4K Page Data TLB %<B>disabled. "));
					break;
				default:
					OUTPUT(WSTR("L2 4K Page Data TLB %<B>%s. "),Associative[TmpInfo[0].dwEBX >>28]);
					break;
				}
				OUTPUT(WSTR("%d entries.\n"),((TmpInfo[0].dwEBX>>16)&0xfff));
				switch((TmpInfo[0].dwEBX >>12)&0xf)
				{
				case 0:
					OUTPUT(WSTR("L2 4K Page Instruction TLB %<B>disabled. "));
					break;				
				default:
					OUTPUT(WSTR("L2 4K Page Instruction TLB %<B>%s. "),Associative[((TmpInfo[0].dwEBX >>12)&0xf)]);
					break;
				}		
				OUTPUT(WSTR("%d entries.\n"),(TmpInfo[0].dwEBX&0xfff));				
				OUTPUT(WSTR(" L2 cache %d KB, %s cache line %d Bytes\n"),(TmpInfo[0].dwECX >> 16),Associative[(TmpInfo[0].dwECX >> 12) & 0xf],(TmpInfo[0].dwECX & 0xff));				
			}
		}

	}
	else
	{
		OUTPUT(WSTR("Not Support CPU Feature\n"));
	}
	return 0;
}