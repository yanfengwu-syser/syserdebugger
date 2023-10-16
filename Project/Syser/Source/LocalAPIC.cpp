#include "stdafx.h"
#include "LocalAPIC.h"
#include "IOAPIC.h"

#ifdef __cplusplus
extern "C" {
#endif

DWORD gdwLocalAPICTaskPriority=0;
DWORD gdwLocalAPICLineAddress=0;
DWORD gdwLocalAPICPhysAddress=0;

#ifdef __cplusplus
}; // extern "C"
#endif

void DisableAllLocalAPICInterrupt()
{
	if(gbIsUseAPIC)
	{		
		DWORD* TaskPriorityRegister=*(DWORD**)&gdwLocalAPICLineAddress;
		TaskPriorityRegister[0x80/sizeof(DWORD)]=0xff;
	}
}
void EnableLocalAPICInterrupt()
{
	if(gbIsUseAPIC)
	{
		DWORD* TaskPriorityRegister=*(DWORD**)&gdwLocalAPICLineAddress;
		TaskPriorityRegister[0x80/sizeof(DWORD)]=0xef;
	}
}
void SetLocalAPICEOI(DWORD dwInterruptNum)
{
	DWORD* pdwTemp;
	pdwTemp =*(DWORD**)&gdwLocalAPICLineAddress;
	pdwTemp[0xb0/sizeof(DWORD)]=0;	
}
DWORD GetLocalAPICID()
{
	DWORD LocalApicID;
	DWORD *APICIDRegister = *(DWORD**)&gdwLocalAPICLineAddress;
	LocalApicID = APICIDRegister[0x20/sizeof(DWORD)];
	LocalApicID>>=18;
	return LocalApicID;
}
void SaveLocalApic(PSAVELOCALAPIC Save)
{
	DWORD *pLapic = *(DWORD**)&gdwLocalAPICLineAddress,i;
	Save->APIC_ID=pLapic[0x20/sizeof(DWORD)];
	Save->APICVersion=pLapic[0x30/sizeof(DWORD)];
	Save->TaskPriority=pLapic[0x80/sizeof(DWORD)];
	Save->ArbitrationPriority=pLapic[0x90/sizeof(DWORD)];
	Save->ProcessorPriority=pLapic[0xa0/sizeof(DWORD)];
	Save->LogicalDestination=pLapic[0xd0/sizeof(DWORD)];
	Save->DestinationFormat=pLapic[0xe0/sizeof(DWORD)];
	Save->SpuriousInterruptVector=pLapic[0xf0/sizeof(DWORD)];
	Save->ErrorStatus=pLapic[0x280/sizeof(DWORD)];
	Save->InterruptCommandLow=pLapic[0x300/sizeof(DWORD)];
	Save->InterruptCommandHigh=pLapic[0x310/sizeof(DWORD)];
	Save->LVTTimer=pLapic[0x320/sizeof(DWORD)];
	Save->LVTThermalSensor=pLapic[0x330/sizeof(DWORD)];
	Save->LVTPerformanceMonitoringCounters=pLapic[0x340/sizeof(DWORD)];
	Save->LVTLINT0=pLapic[0x350/sizeof(DWORD)];
	Save->LVTLINT1=pLapic[0x360/sizeof(DWORD)];
	Save->LVTError=pLapic[0x370/sizeof(DWORD)];
	Save->InitialCount=pLapic[0x380/sizeof(DWORD)];
	Save->CurrentCount=pLapic[0x390/sizeof(DWORD)];
	Save->DivideConfiguration=pLapic[0x3e0/sizeof(DWORD)];
	for(i = 0; i < 8;i++)
	{
		Save->InService[i]=pLapic[(0x100+i*0x10)/sizeof(DWORD)];
		Save->TriggerMode[i]=pLapic[(0x180+i*0x10)/sizeof(DWORD)];
		Save->InterruptRequest[i]=pLapic[(0x200+i*0x10)/sizeof(DWORD)];
	}
}
