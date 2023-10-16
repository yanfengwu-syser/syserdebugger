#include "stdafx.h"
#include "Syser.h"
#include "IOAPIC.h"
#include "LocalAPIC.h"
#include "X86Optr.h"
#include "SerialPort.h"
DWORD gdwIOAPICPhysAddress=0;
DWORD gdwIOAPICLineAddress=0;
bool gbIsUseAPIC=false;
IOAPICInterruptVectorTable IOAPICInterruptVectorTab[0x20];

DWORD dwAPICPatchInterruptVectorNum[]=
{
		SYSER_APIC_TIME_INTERRUPT_VECTOR,			//index 0 Timter
		SYSER_APIC_KEYBOARD_INTERRUPT_VECTOR,		//index 1 keyboard	
		SYSER_APIC_TIME_INTERRUPT_VECTOR,			//index 2
		SYSER_APIC_COM2_INTERRUPT_VECTOR,			//index 3
		SYSER_APIC_COM1_INTERRUPT_VECTOR,			//index 4
		0x0,										//index 5
		0x0,										//index 6
		0x0,										//index 7
		0x0,										//index 8
		0x0,										//index 9
		0x0,										//index a
		0x0,										//index b
		SYSER_APIC_MOUSE_INTERRUPT_VECTOR,			//index c mouse
		0x0,										//index d
		0x0,										//index e
		0x0,										//index f
};

#define IOAPIC_DEFAULT_PHYSICAL_BASE					0xFEC00000
#define MSR_INDEX_IA32_APIC_BASE						0x1b
#define MSR_APIC_GLOBAL_ENABLE_BIT_MASK					0x800
#define MSR_APIC_BASE_ADDRESS_BIT_MASK					0xfffff000
#define CPUID_1_EDX_FEATURE_APIC_ON_CHIP_BIT_MASK		0x200

bool GetIOAPICBase()
{
	DWORD dwPhysicalAddress = IOAPIC_DEFAULT_PHYSICAL_BASE;
	CPUID_INFO	CpuInfo;
	DWORD dwLineAddr = 0;
	DWORD dwRdmsrEax = 0;
	DWORD dwRdmsrEdx = 0;
 	DWORD dwCpuidEax = 0;
 	DWORD dwCpuidEdx = 0;

	gbIsUseAPIC = FALSE;
	if(SyserIsSupportCPUIDInstruction() == FALSE)
		return FALSE;
	if(SyserIsSupportRDMSRInstruction() == FALSE)
		return FALSE;
// 	__asm
// 	{
// 		pushad		
// 		mov eax,1
// 		cpuid
// 		mov dwCpuidEax,eax
// 		mov dwCpuidEdx,edx
// 		mov ecx,MSR_INDEX_IA32_APIC_BASE
// 		rdmsr 
// 		mov dwRdmsrEax,eax
// 		mov dwRdmsrEdx,edx	
// 		popad
// 	}

	SyserGetCPUID(&CpuInfo,1);
	SyserGetApicInfo(&dwRdmsrEax,&dwRdmsrEdx);

	dwCpuidEax = CpuInfo.dwEAX;
	dwCpuidEdx = CpuInfo.dwEDX;

	if((dwRdmsrEax & MSR_APIC_GLOBAL_ENABLE_BIT_MASK) &&( dwCpuidEdx & CPUID_1_EDX_FEATURE_APIC_ON_CHIP_BIT_MASK))
	{
		for(;dwPhysicalAddress != 0xfec10000 ;dwPhysicalAddress += 0x1000)
		{
			if(MapToVAddr(dwPhysicalAddress, (VADDR32 *)&dwLineAddr) == TRUE)
				break;
		}	
		if(dwPhysicalAddress==0xfec10000)
			return false;
		gdwIOAPICPhysAddress = dwPhysicalAddress;
		gdwIOAPICLineAddress = dwLineAddr;
		gdwLocalAPICPhysAddress = dwRdmsrEax & MSR_APIC_BASE_ADDRESS_BIT_MASK;
		if(MapToVAddr(gdwLocalAPICPhysAddress, (VADDR32 *)&dwLineAddr) == FALSE)
			return false;
		gdwLocalAPICLineAddress =dwLineAddr;
		gbIsUseAPIC = true;
	}
	else
		return false;
	return true;
}
//得到 IOAPIC 的数据，参数 dwIndex 是索引
DWORD GetIOAPICData(DWORD dwIndex)
{
	DWORD *pIoapicLineAddress,dwReturn = 0;
	if(gbIsUseAPIC)
	{
		pIoapicLineAddress = *(DWORD **)&gdwIOAPICLineAddress;
// 		__asm
// 		{
// 			pushfd
// 			pushad
// 			mov eax,pIoapicLineAddress
// 			mov ebx,dwIndex
// 			cli
// 			mov [eax],ebx
// 			mov eax, [eax+0x10]
// 			mov dwReturn,eax
// 			popad
// 			popfd
// 		}	

		dwReturn = SyserGetIOAPICData(pIoapicLineAddress,dwIndex);
	}
	return dwReturn;
}

void SetIOAPICData(DWORD dwIndex,DWORD dwValue)
{
	DWORD *pIoapicLineAddress;
	if(gbIsUseAPIC)
	{
		pIoapicLineAddress = *(DWORD **)&gdwIOAPICLineAddress;		
// 		__asm
// 		{
// 			pushfd
// 			pushad
// 			mov eax,pIoapicLineAddress
// 			mov ebx,dwIndex
// 			mov ecx,dwValue
// 			cli
// 			mov [eax],ebx
// 			mov [eax+0x10],ecx
// 			popad
// 			popfd
// 		}

		SyserSetIOAPICData(pIoapicLineAddress,dwIndex,dwValue);
		return ;
	}
}

bool SetIOAPICInterruptVector(DWORD dwInterruptVector, DWORD dwLow,DWORD dwHeig)
{
	SetIOAPICData(dwInterruptVector*2+0x10,dwLow);
	SetIOAPICData(dwInterruptVector*2+0x11,dwHeig);
	return TRUE;
}

//通过硬件中断的索引的到
DWORD GetIOAPICInterruptVector(DWORD dwHardwareIndex)
{
	dwHardwareIndex = dwHardwareIndex * 2 + 0x10;	 
	dwHardwareIndex = GetIOAPICData(dwHardwareIndex);	
	return dwHardwareIndex & 0xff;
}

DWORD GetIOAPICInterruptNum()//取得ioapic 的中断个数
{
	DWORD dwRet;
	dwRet = GetIOAPICData(1);
	dwRet >>= 0x10;
	dwRet &= 0xff;
	if(dwRet > 0x20)
		dwRet = 0x20;
	return dwRet;
}

void SaveIOAPICInterruptVectorTable()
{
	DWORD dwInterruptNum;
	if(!gbIsUseAPIC)
		return;
	dwInterruptNum = GetIOAPICInterruptNum();
	for(DWORD i=0;i<dwInterruptNum;i++)
	{
		IOAPICInterruptVectorTab[i].dwVectorLow = GetIOAPICData(0x10 + i * 2);
		IOAPICInterruptVectorTab[i].dwVectorHigh = GetIOAPICData(0x11 + i * 2);		
	}
}

void RestoreIOAPICInterruptVectorTable()
{
	DWORD dwLow,dwHigh;
	DWORD dwInterruptNum;
	if(!gbIsUseAPIC)
		return;
	dwInterruptNum = GetIOAPICInterruptNum();
	for(DWORD i = 0;i<dwInterruptNum;i++)
	{
		if(i==1 && i==0xc)
		{
			dwLow=GetIOAPICData(0x10 + i * 2);
			if(dwLow&0x1000)
			{
// 				__asm
// 				{
// 					push eax
// 					in al,0x64
// 					test al,1
// 					jz local_001
// 					in al,0x60
// 					push 0x100 
// 					push 0x100
// 					call Beep
// local_001:						
// 					pop eax 
// 				}

				SyserIOAPICBeep();
			}
		}
		SetIOAPICData(0x11 + i * 2, IOAPICInterruptVectorTab[i].dwVectorHigh );
		SetIOAPICData(0x10 + i * 2, IOAPICInterruptVectorTab[i].dwVectorLow );
		
	}
}

void EnableAPICHardWareInterrupt(DWORD arg)
{
	DWORD dwInterruptVectorNum;
	DWORD dwHigh,MaskValue;
	if(arg < 0x10)
	{
		if(gCPUNumbers==1)
			MaskValue=0x900;
		else
			MaskValue=0x800;
		dwInterruptVectorNum = dwAPICPatchInterruptVectorNum[arg]|MaskValue;//Fixed Mode不考虑CPU优先级
		dwHigh=0xff;
		dwHigh = dwHigh>>(8-gCPUNumbers);
		dwHigh<<=24;
		SetIOAPICInterruptVector(arg,dwInterruptVectorNum,dwHigh);
	}
}
