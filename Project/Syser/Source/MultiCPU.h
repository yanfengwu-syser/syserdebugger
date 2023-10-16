#ifndef _MULITCPU_H_
#define _MULITCPU_H_

#ifdef CODE_OS_NT_DRV
extern PKPCR gDefaultPCR;
extern PKPCR* gPCRArray;
#endif

#ifdef __cplusplus
extern "C" {
#endif

extern ULONG gCPUNumbers;
extern ULONG gdwCurrentCPUIndex;
extern BYTE gCPULocalAPIC_ID[256];
extern DWORD gdwMulitCpuSpinlock;
extern DWORD gdwMulitCpuSendIPIFlags;
extern DWORD gSystemFSRegisterSelector;
extern DWORD gSystemSSRegisterSelector;
extern DWORD gSystemCSRegisterSelector;
extern DWORD gSystemDSRegisterSelector;

VOID SyserStartOtherCPUs(VOID);
VOID SyserStopOtherCPUs(VOID);
bool InitMultiCPUInformation();
DWORD GetCurrentCPULocalAPICID();

typedef struct _CPUSTRUCT
{
	DWORD LocalAPICID;
	PDECSRIPTOR GDT;
	PDECSRIPTOR IDT;
}CPUSTRUCT,*PCPUSTRUCT;

#ifdef __cplusplus
}; // extern "C"
#endif


#endif //_MULITCPU_H_