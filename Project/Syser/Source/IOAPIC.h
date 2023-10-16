#ifndef _IOAPIC_H_
#define _IOAPIC_H_

#ifdef __cplusplus
extern "C" {
#endif


#define SYSER_APIC_TIME_INTERRUPT_VECTOR			0xfa
#define SYSER_APIC_KEYBOARD_INTERRUPT_VECTOR		0xf8 
#define SYSER_APIC_MOUSE_INTERRUPT_VECTOR			0xf9

typedef struct stIOAPICInterruptVectorTable{
	DWORD dwVectorLow;
	DWORD dwVectorHigh;
}IOAPICInterruptVectorTable;
extern DWORD gdwIOAPICPhysAddress;
extern DWORD gdwIOAPICLineAddress;
extern bool gbIsUseAPIC;
bool GetIOAPICBase();
void SetIOAPICData(DWORD dwIndex,DWORD dwValue);
DWORD GetIOAPICData(DWORD dwIndex);
void EnableLocalAPICInterrupt();
void RestoreIOAPICInterruptVectorTable();
void SaveIOAPICInterruptVectorTable();
//得到 IOAPIC 支持的中断的数目
DWORD GetIOAPICInterruptNum();//得到 IOAPIC 支持的中断的数目
DWORD GetIOAPICInterruptVector(DWORD dwHardwareIndex);
bool SetIOAPICInterruptVector(DWORD dwInterruptVector, DWORD dwLow,DWORD dwHeig);
void EnableAPICHardWareInterrupt(DWORD arg);

extern IOAPICInterruptVectorTable IOAPICInterruptVectorTab[0x20];

VOID	SyserGetApicInfo(DWORD	*RdmsrEax,DWORD *RdmsrEdx);

DWORD	SyserGetIOAPICData(DWORD*  IoApicLineAddress, DWORD	Index);
DWORD	SyserSetIOAPICData(DWORD*  IoApicLineAddress, DWORD	Index,DWORD	Data);
VOID	SyserIOAPICBeep(VOID);

#ifdef __cplusplus
}; // extern "C"
#endif

#endif //_IOAPIC_H_