#include "StdAfx.h"
#include "Syser.h"
#include "cmd_msr.h"

typedef struct _stSMRName
{
	DWORD Index;
	WCHAR* Name;
}SMRNAME;
SMRNAME MsrName[]=
{
	{0x0,WSTR("IA32_P5_MC_ADDR")},
	{0x1,WSTR("IA32_P5_MC_TYPE")},
	{0x10,WSTR("IA32_TIME_STAMP_COUNTER")},
	{0x11,WSTR("CESR")},
	{0x12,WSTR("CTR0")},
	{0x13,WSTR("CTR1")},
	{0x17,WSTR("IA32_PLATFORM_ID")},
	{0x1b,WSTR("IA32_APIC_BASE")},
	{0x2A,WSTR("EBL_CR_POWERON")},
	{0x2B,WSTR("MSR_EBC_SOFT_POWERON")},
	{0x2C,WSTR("MSR_EBC_FREQUENCY_ID")},		
	{0x33,WSTR("TEST_CTL")},
	{0x3A,WSTR("IA32_FEATURE_CONTROL")},
	{0x40,WSTR("MSR_LASTBRANCH_0_FROM_IP")},
	{0x41,WSTR("MSR_LASTBRANCH_1_FROM_IP")},
	{0x42,WSTR("MSR_LASTBRANCH_2_FROM_IP")},
	{0x43,WSTR("MSR_LASTBRANCH_3_FROM_IP")},
	{0x44,WSTR("MSR_LASTBRANCH_4_FROM_IP")},
	{0x45,WSTR("MSR_LASTBRANCH_5_FROM_IP")},
	{0x46,WSTR("MSR_LASTBRANCH_6_FROM_IP")},
	{0x47,WSTR("MSR_LASTBRANCH_7_FROM_IP")},
	{0x60,WSTR("MSR_LASTBRANCH_0_TO_IP")},
	{0x61,WSTR("MSR_LASTBRANCH_1_TO_IP")},
	{0x62,WSTR("MSR_LASTBRANCH_2_TO_IP")},
	{0x63,WSTR("MSR_LASTBRANCH_3_TO_IP")},
	{0x64,WSTR("MSR_LASTBRANCH_4_TO_IP")},
	{0x65,WSTR("MSR_LASTBRANCH_5_TO_IP")},
	{0x66,WSTR("MSR_LASTBRANCH_6_TO_IP")},
	{0x67,WSTR("MSR_LASTBRANCH_7_TO_IP")},
	{0x79,WSTR("IA32_BIOS_UPDT_TRIG")},
	{0x88,WSTR("BBL_CR_D0[63:0]")},
	{0x89,WSTR("BBL_CR_D1[63:0]")},
	{0x8A,WSTR("BBL_CR_D2[63:0]")},
	{0x8b,WSTR("IA32_BIOS_SIGN_ID")},
	{0x9b,WSTR("IA32_SMM_MONITOR_CTL")},
	{0xC1,WSTR("PerfCtr0 (PERFCTR0)")},
	{0xC2,WSTR("PerfCtr1 (PERFCTR1)")},
	{0xfe,WSTR("IA32_MTRRCAP")},
	{0x118,WSTR("BBL_CR_DECC[63:0]")},
	{0x119,WSTR("IA32_MISC_CTL")},
	{0x11A,WSTR("BBL_CR_CTL3")},
	{0x11B,WSTR("BBL_CR_BUSY")},
	{0x11E,WSTR("BBL_CR_CTL3")},
	{0x174,WSTR("IA32_SYSENTER_CS")},
	{0x175,WSTR("IA32_SYSENTER_ESP")},
	{0x176,WSTR("IA32_SYSENTER_EIP")},
	{0x179,WSTR("IA32_MCG_CAP")},
	{0x17a,WSTR("IA32_MCG_STATUS")},
	{0x17b,WSTR("IA32_MCG_CTL")},
	{0x180,WSTR("IA32_MCG_EAX")},
	{0x181,WSTR("IA32_MCG_EBX")},
	{0x182,WSTR("IA32_MCG_ECX")},
	{0x183,WSTR("IA32_MCG_EDX")},
	{0x184,WSTR("IA32_MCG_EDI")},
	{0x185,WSTR("IA32_MCG_ESI")},
	{0x186,WSTR("IA32_MCG_EBP")},
	{0x187,WSTR("IA32_MCG_ESP")},
	{0x188,WSTR("IA32_MCG_EFLAGS")},
	{0x189,WSTR("IA32_MCG_EIP")},
	{0x18a,WSTR("IA32_MCG_MISC")},
	{0x190,WSTR("IA32_MCG_R8")},
	{0x191,WSTR("IA32_MCG_R9")},
	{0x192,WSTR("IA32_MCG_R10")},
	{0x193,WSTR("IA32_MCG_R11")},
	{0x194,WSTR("IA32_MCG_R12")},
	{0x195,WSTR("IA32_MCG_R13")},
	{0x196,WSTR("IA32_MCG_R14")},
	{0x197,WSTR("IA32_MCG_R15")},
	{0x198,WSTR("IA32_PERF_STATUS")},
	{0x199,WSTR("IA32_PERF_CTL")},
	{0x19a,WSTR("IA32_CLOCK_MODULATION")},
	{0x19b,WSTR("IA32_THERM_INTERRUPT")},
	{0x19c,WSTR("IA32_THERM_STATUS")},
	{0x1A0,WSTR("IA32_MISC_ENABLE")},
	{0x1C9,WSTR("MSR_LASTBRANCH_TOS")},
	{0x1D9,WSTR("IA32_DEBUGCTL")},
	{0x1DB,WSTR("LASTBRANCHFROMIP")},
	{0x1DC,WSTR("LASTBRANCHTOIP")},
	{0x1DD,WSTR("LASTINTFROMIP")},
	{0x1DE,WSTR("LASTINTTOIP")},
	{0x1E0,WSTR("ROB_CR_BKUPTMPDR6")},
	{0x200,WSTR("IA32_MTRR_PHYSBASE0")},
	{0x201,WSTR("IA32_MTRR_PHYSMASK0")},
	{0x202,WSTR("IA32_MTRR_PHYSBASE1")},
	{0x203,WSTR("IA32_MTRR_PHYSMASK1")},
	{0x204,WSTR("IA32_MTRR_PHYSBASE2")},
	{0x205,WSTR("IA32_MTRR_PHYSMASK2")},
	{0x206,WSTR("IA32_MTRR_PHYSBASK3")},
	{0x207,WSTR("IA32_MTRR_PHYSMASK3")},
	{0x208,WSTR("IA32_MTRR_PHYSBASE4")},
	{0x209,WSTR("IA32_MTRR_PHYSMASK4")},
	{0x20a,WSTR("IA32_MTRR_PHYSBASE5")},
	{0x20b,WSTR("IA32_MTRR_PHYSMASK5")},
	{0x20c,WSTR("IA32_MTRR_PHYSBASE6")},
	{0x20d,WSTR("IA32_MTRR_PHYSMASK6")},
	{0x20e,WSTR("IA32_MTRR_PHYSBASE7")},
	{0x20f,WSTR("IA32_MTRR_PHYSMASK7")},
	{0x250,WSTR("IA32_MTRR_FIX64K_00000")},
	{0x258,WSTR("IA32_MTRR_FIX16K_80000")},
	{0x259,WSTR("IA32_MTRR_FIX16K_A0000")},
	{0x268,WSTR("IA32_MTRR_FIX4K_C0000")},
	{0x269,WSTR("IA32_MTRR_FIX4K_C8000")},
	{0x26a,WSTR("IA32_MTRR_FIX4K_E0000")},
	{0x26b,WSTR("IA32_MTRR_FIX4K_D8000")},
	{0x26c,WSTR("IA32_MTRR_FIX4K_E0000")},
	{0x26d,WSTR("IA32_MTRR_FIX4K_E8000")},
	{0x26e,WSTR("IA32_MTRR_FIX4K_F0000")},
	{0x26f,WSTR("IA32_MTRR_FIX4K_F8000")},
	{0x277,WSTR("IA32_CR_PAT")},
	{0x2ff,WSTR("IA32_MTRR_DEF_TYPE")},
	{0x3f1,WSTR("IA32_PEBS_ENABLE")},
	{0x400,WSTR("IA32_MC0_CTL")},
	{0x401,WSTR("IA32_MC0_STATUS")},
	{0x402,WSTR("IA32_MC0_ADDR")},
	{0x403,WSTR("IA32_MC0_MISC")},
	{0x404,WSTR("IA32_MC1_CTL")},
	{0x405,WSTR("IA32_MC1_STATUS")},
	{0x406,WSTR("IA32_MC1_ADDR")},
	{0x407,WSTR("IA32_MC1_MISC")},
	{0x408,WSTR("IA32_MC2_CTL")},
	{0x409,WSTR("IA32_MC2_STATUS")},
	{0x40a,WSTR("IA32_MC2_ADDR")},
	{0x40b,WSTR("IA32_MC2_MISC")},
	{0x40c,WSTR("IA32_MC3_CTL")},
	{0x40d,WSTR("IA32_MC3_STATUS")},
	{0x40e,WSTR("IA32_MC3_ADDR")},
	{0x40f,WSTR("IA32_MC3_MISC")},
	{0x410,WSTR("IA32_MC4_CTL")},
	{0x411,WSTR("IA32_MC4_STATUS")},
	{0x412,WSTR("IA32_MC4_ADDR")},
	{0x413,WSTR("IA32_MC4_MISC")},
	{0x480,WSTR("IA32_VMX_BASIC")},
	{0x481,WSTR("IA32_VMX_PINBASED_CTL")},
	{0x482,WSTR("IA32_VMX_PROCBASED_C")},
	{0x483,WSTR("IA32_VMX_EXIT_CTLS")},
	{0x484,WSTR("IA32_VMX_ENTRY_CTLS")},
	{0x485,WSTR("IA32_VMX_MISC_CTLS")},
	{0x486,WSTR("IA32_VMX_CRO_FIXED0")},
	{0x487,WSTR("IA32_VMX_CRO_FIXED1")},
	{0x488,WSTR("IA32_VMX_CR4_FIXED0")},
	{0x489,WSTR("IA32_VMX_CR4_FIXED1")},
	{0x48A,WSTR("IA32_VMX_VMCS_ENUM")},
	{0x600,WSTR("IA32_DS_AREA")},
	{0x680,WSTR("MSR_LASTBRANCH_0_FROM_LIP")},
	{0x681,WSTR("MSR_LASTBRANCH_1_FROM_LIP")},
	{0x682,WSTR("MSR_LASTBRANCH_2_FROM_LIP")},
	{0x683,WSTR("MSR_LASTBRANCH_3_FROM_LIP")},
	{0x684,WSTR("MSR_LASTBRANCH_4_FROM_LIP")},
	{0x685,WSTR("MSR_LASTBRANCH_5_FROM_LIP")},
	{0x686,WSTR("MSR_LASTBRANCH_6_FROM_LIP")},
	{0x687,WSTR("MSR_LASTBRANCH_7_FROM_LIP")},
	{0x688,WSTR("MSR_LASTBRANCH_8_FROM_LIP")},
	{0x689,WSTR("MSR_LASTBRANCH_9_FROM_LIP")},
	{0x68a,WSTR("MSR_LASTBRANCH_10_FROM_LIP")},
	{0x68b,WSTR("MSR_LASTBRANCH_11_FROM_LIP")},
	{0x68c,WSTR("MSR_LASTBRANCH_12_FROM_LIP")},
	{0x68d,WSTR("MSR_LASTBRANCH_13_FROM_LIP")},
	{0x68e,WSTR("MSR_LASTBRANCH_14_FROM_LIP")},
	{0x68f,WSTR("MSR_LASTBRANCH_15_FROM_LIP")},	
	{0x6c0,WSTR("MSR_LASTBRANCH_0_TO_LIP")},
	{0x6c1,WSTR("MSR_LASTBRANCH_1_TO_LIP")},
	{0x6c2,WSTR("MSR_LASTBRANCH_2_TO_LIP")},
	{0x6c3,WSTR("MSR_LASTBRANCH_3_TO_LIP")},
	{0x6c4,WSTR("MSR_LASTBRANCH_4_TO_LIP")},
	{0x6c5,WSTR("MSR_LASTBRANCH_5_TO_LIP")},
	{0x6c6,WSTR("MSR_LASTBRANCH_6_TO_LIP")},
	{0x6c7,WSTR("MSR_LASTBRANCH_7_TO_LIP")},
	{0x6c8,WSTR("MSR_LASTBRANCH_8_TO_LIP")},
	{0x6c9,WSTR("MSR_LASTBRANCH_9_TO_LIP")},
	{0x6ca,WSTR("MSR_LASTBRANCH_10_TO_LIP")},
	{0x6cb,WSTR("MSR_LASTBRANCH_11_TO_LIP")},
	{0x6cc,WSTR("MSR_LASTBRANCH_12_TO_LIP")},
	{0x6cd,WSTR("MSR_LASTBRANCH_13_TO_LIP")},
	{0x6ce,WSTR("MSR_LASTBRANCH_14_TO_LIP")},
	{0x6cf,WSTR("MSR_LASTBRANCH_15_TO_LIP")},	
	{0x107cc,WSTR("MSR_IFSB_BUSQ0")},	
	{0x107cd,WSTR("MSR_IFSB_BUSQ1")},	
	{0x107ce,WSTR("MSR_IFSB_SNPQ0")},	
	{0x107cf,WSTR("MSR_IFSB_SNPQ1")},	
	{0x107d0,WSTR("MSR_IFSB_DRDY0")},	
	{0x107d1,WSTR("MSR_IFSB_DRDY1")},	
	{0x107d2,WSTR("MSR_IFSB_CTL6")},	
	{0x107d3,WSTR("MSR_IFSB_CNTR7")},	
	{0xC0000080,WSTR("IA32_EFER")},
	{0xC0000081,WSTR("IA32_STAR")},
	{0xC0000082,WSTR("IA32_LSTAR")},
	{0xC0000083,WSTR("IA32_CSTAR")},
	{0xC0000084,WSTR("IA32_FMASK")},
	{0xC0000100,WSTR("IA32_FS_BASE")},
	{0xC0000101,WSTR("IA32_GS_BASE")},
	{0xC0000102,WSTR("IA32_KERNEL_GS_BASE")},
	{0xC0000103,WSTR("TSC_AUX")},
	{0xC0000408,WSTR("MC4_MISC1")},
	{0xC0000409,WSTR("MC4_MISC2")},
	{0xC000040a,WSTR("MC4_MISC3")},
	
	{0xC0010000,WSTR("PerfEvtSel0")},
	{0xC0010001,WSTR("PerfEvtSel1")},
	{0xC0010002,WSTR("PerfEvtSel2")},
	{0xC0010003,WSTR("PerfEvtSel3")},
	{0xC0010004,WSTR("PerfCtr0")},
	{0xC0010005,WSTR("PerfCtr1")},
	{0xC0010006,WSTR("PerfCtr2")},
	{0xC0010007,WSTR("PerfCtr3")},
	{0xC0010010,WSTR("SYSCFG")},
	{0xC0010016,WSTR("IORRBase0")},
	{0xC0010017,WSTR("IORRMask0")},
	{0xC0010018,WSTR("IORRBase1")},
	{0xC0010019,WSTR("IORRMask1")},
	{0xC001001a,WSTR("TOP_MEM")},
	{0xC001001d,WSTR("TOP_MEM2")},
	{0xC0010030,WSTR("Processor_Name_String")},
	{0xC0010031,WSTR("Processor_Name_String")},
	{0xC0010032,WSTR("Processor_Name_String")},
	{0xC0010033,WSTR("Processor_Name_String")},
	{0xC0010034,WSTR("Processor_Name_String")},
	{0xC0010035,WSTR("Processor_Name_String")},
	{0xC0010061,WSTR("P-State Current Limit")},
	{0xC0010062,WSTR("P-State Control")},
	{0xC0010063,WSTR("P-State Status")},
	{0xC0010074,WSTR("CPU_Watchdog_Timer")},
	{0xC0010111,WSTR("SMBASE")},
	{0xC0010112,WSTR("SMM_ADDR")},
	{0xC0010113,WSTR("SMM_MASK")},
	{0xC0010114,WSTR("VM_CR")},
	{0xC0010115,WSTR("IGNNE")},
	{0xC0010116,WSTR("SMM_CTL")},
	{0xC0010117,WSTR("VM_HSAVE_PA")},
	{0xC0010118,WSTR("SVM_KEY_MSR")},
	{0xC0010119,WSTR("SMM_KEY_MSR")},
	{0xC001011a,WSTR("Local_SMI_Status")},
	{0xC0010056,WSTR("SMI_Trigger_IO_Cycle")},
	{0xC0010140,WSTR("OSVW_ID_Length")},	
	{0xC0010141,WSTR("OSVM Status")},
};
WCHAR *GetMSRName(int dwIndex)
{
	int j,i;
	j =sizeof(MsrName)/sizeof(MsrName[0]);
	for(i =0; i<j;i++)
	{
		if(MsrName[i].Index==dwIndex)
			return MsrName[i].Name;
	}
	return NULL;
}
int msr_command(int argc, WCHAR *argv[],PCWSTR szCommandLine,CSyser*pSyser)
{
	DWORD dwHighDword,dwLowDword;
	DWORD dwBeginIndex,dwCount;
	DWORD dwTmp,dwTmp2;
	int j;
	bool bWrite;
	WCHAR* Title=WSTR("Reg       Value                   Acc ID Name                   Description\n");
	bool bTitleShow;
	dwHighDword=0xffffffff;
	dwLowDword=0xffffffff;
	bool bUndocument;
	WCHAR* Format=WSTR("%-10x%08x:%08x   %s%-30s%s\n");

	bTitleShow=true	;
	bWrite=false;
	bUndocument=false;
	dwCount=0xffffffff;
	dwBeginIndex=0;
	if(argc >= 2)
	{
		if(TStrICmp(argv[1],WSTR("-w"))==0)
		{			
			bWrite=true;
			if(argc==2 || argc==3)
				return 0;
			if(CALCEXP(argv[2],&dwBeginIndex)==FALSE)
			{
				OUTPUT(WSTR("Syser: Input error!\n"));
				return 0;
			}						
			dwHighDword=0,dwLowDword=0;
			if(SyserReadMSR(dwBeginIndex,&dwHighDword,&dwLowDword)==false)
				return 0;		

			if(argc==4)
			{
				if(CALCEXP(argv[3],&dwTmp)==true)
				{
					dwLowDword=dwTmp;
					SyserWriteMSR(dwBeginIndex,dwHighDword,dwLowDword);			
				}
				return 0;
			}
			dwTmp2=dwTmp=0xffffffff;
			if(CALCEXP(argv[4],&dwTmp)==true)
				dwLowDword=dwTmp;
			if(CALCEXP(argv[3],&dwTmp2)==true)
				dwHighDword=dwTmp2;
			if(dwLowDword==dwTmp || dwHighDword==dwTmp2)
			{
				SyserWriteMSR(dwBeginIndex,dwHighDword,dwLowDword);				
			}
			return 0;
		}
		dwCount=1;
		DWORD delt;
		dwBeginIndex=0;

		if(TStrICmp(argv[1],WSTR("-u"))==0)
		{
			delt=1;
			bUndocument=true;
		}
		else
			delt=0;
		if(argc==delt+2)
		{
			if(CALCEXP(argv[1+delt],&dwTmp2)==true)
				dwBeginIndex=dwTmp2;
		}else
			if(argc==delt+3)
			{
				if(CALCEXP(argv[1+delt],&dwTmp2)==true)
					dwBeginIndex=dwTmp2;
				if(CALCEXP(argv[2+delt],&dwTmp)==true)
					dwCount=dwTmp-dwBeginIndex;
			}else
				dwCount=0xffffffff;
	}
	if(dwCount==0xffffffff)		
	{
		j =sizeof(MsrName)/sizeof(MsrName[0]);
		for(int i=0;i<j;i++)
		{
			dwHighDword=0,dwLowDword=0;
			if(SyserReadMSR(MsrName[i].Index,&dwHighDword,&dwLowDword))
			{
				if(bTitleShow==true)
				{
					bTitleShow=false;
					OUTPUT(Title);
				}
				OUTPUT(Format,MsrName[i].Index,dwHighDword,dwLowDword,WSTR("    "),MsrName[i].Name,WSTR("A"));
			}
			else
				if(bUndocument)
					OUTPUT(WSTR("Syser: Error reading MSR %x\n"),i);
		}
	}
	else
	{
		for(int i = (int)dwBeginIndex,j=0;j<(int)dwCount;j++,i++)
		{
			dwHighDword=0,dwLowDword=0;
			if(SyserReadMSR(i,&dwHighDword,&dwLowDword))
			{
				WCHAR *name;
				name =GetMSRName(i);
				if(bTitleShow==true)
				{
					bTitleShow=false;
					OUTPUT(Title);
				}
				if(name==NULL)
					OUTPUT(Format,i,dwHighDword,dwLowDword,WSTR("    "),WSTR(""),WSTR("A"));
				else
					OUTPUT(Format,i,dwHighDword,dwLowDword,WSTR("    "),name,WSTR("A"));
			}
			else
				if(bUndocument)
					OUTPUT(WSTR("Syser: Error reading MSR %x\n"),i);
		}
	}
	return 0;
}