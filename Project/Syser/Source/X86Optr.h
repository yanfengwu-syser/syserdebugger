#ifndef X86_OPTR_H_
#define X86_OPTR_H_

#include "X86Define.h"
#include "LastBranch.h"
#ifdef CODE_OS_NT_DRV
#include "MultiCPU.h"
#endif
#include "InterruptPatch.h"

#ifdef __cplusplus
extern "C" {
#endif

#define IsSupportWRMSRInstruction SyserIsSupportRDMSRInstruction
extern DWORD			ExceptionInterruptNum;
extern DWORD			ExceptionInterruptErrorCode;
extern X86_REG_CONTEXT*	ExceptionReg;
extern X86_REG_CONTEXT	Reg;
extern X86_REG_CONTEXT	PrevReg;
extern X86_REG_CONTEXT	ReadOnlyActiveReg;
extern RETURN_CONTEXT  ReturnContext;
extern X86_REG_CONTEXT*	gpMCPUReg;
extern SAVELOCALAPIC*	gpMCPULocalApic;

typedef	struct	_X86SaveRegs_
{
	DWORD	Edi;
	DWORD	Esi;
	DWORD	Ebp;
	DWORD	Esp;
	DWORD	Ebx;
	DWORD	Edx;
	DWORD	Ecx;
	DWORD	Eax;
}	X86SaveRegs,*PX86SaveRegs;

	VOID  SyserCloseInterrupt(VOID);
	VOID  SyserOpenInterrupt(VOID);

	VOID  SyserSaveFlags(PULONG_PTR		_SaveFlags);
	VOID  SyserRestoreFlags(ULONG_PTR	_Flags);

	VOID  SyserSaveFlagsLow16(PWORD	_SaveFlags);
	VOID  SyserRestoreFlagsLow16(WORD	_Flags);

	VOID	SyserPushad(PX86SaveRegs	Regs);
	VOID	SyserPopad(PX86SaveRegs	Regs);

	VOID  SyserCld(VOID);
	VOID SyserCltr(VOID);
	DWORD SyserLar(DWORD	Selector);

	VOID SyserCli(VOID);
	VOID SyserSti(VOID);
	VOID SyserHlt(VOID);
	VOID SyserFlushInsCache(BYTE*	AddPte);
	VOID SyserFlushProcessInsCache(VOID);
	ULONG64	SyserGetRdTsc(VOID);
	VOID SyserFnsave(PUCHAR	pState);
	VOID SyserFrstor(PUCHAR	pState);
	VOID SyserFnstsw(PUSHORT	pState);
	VOID SyserFnstcw(PUSHORT	pControl);

	VOID	SyserClearFlag(WORD	vEs,PDWORD	Value,DWORD	ClearFlag);

	DWORD SyserGetCPUIDMaxIndex();

DWORD		SyserGetTSSSelector();
DWORD		SyserGetLDTSelector();
DWORD		GetTSSBase(DWORD *pTSSSize = NULL,DWORD dwSelector = 0);
VADDR32		SyserGetIDTBase(DWORD* dwIDTSize=NULL);
VADDR32		SyserGetGDTBase(DWORD* dwGDTSize=NULL);
VOID		SyserGetLDTSelectorBySelector(DWORD* dwLdtSelector,DWORD* dwSize);
VADDR32		GetLDTBase(DWORD* dwLdtSize = NULL, DWORD dwLdtSelector = 0);
SELECTOR	SyserGetCurCSeg();
SELECTOR	SyserGetCurDSeg();
SELECTOR	SyserGetCurFSeg();

REG32		SyserGetCR0Reg();
void		SyserSetCR0Reg(IN REG32 uReg);
REG32		SyserGetCR3Reg();
VOID		SyserSetCR3Reg(IN REG32 Reg);

REG32		SyserGetCR4Reg();
VOID		SyserSetCR4Reg(IN REG32 uReg);

VOID		SyserSetCR0WP(void);					//置页保护位
VOID		SyserClrCR0WP(void);					//清页保护位
VOID		SyserRestoreCR0(void);
ULSIZE		GetVirtualPhysSize(IN ULPOS Address,IN ULSIZE MaxSize);
bool		MapToPAddr(IN ULPOS Address,OUT ULONGLONG*pResult);
int			MapToVAddr(IN ULPOS Address,OUT ULPOS*pResult,IN int MaxCount = 1,IN ULPOS HighAddress = 0,ULLPOS AcceptedLowestAddress = 0);

DWORD*		GetPTE(VADDR32 Address,DWORD* PageSize=NULL,DWORD* PTESize=NULL,bool Present=1);

bool		IsValidPage(IN VADDR32 Address,IN int Size = 1);
bool		IsWritablePage(IN VADDR32 Address);
bool		IsAddressValid(void*p);
bool		MakePageWritable(IN VADDR32 Address);
REG32		SyserGetDRX(IN UINT ID);
void		SyserSetDRX(IN UINT ID,IN REG32 Reg);
BYTE		SyserReadPortByte(DWORD wPort);
WORD		SyserReadPortWord(DWORD wPort);
DWORD		SyserReadPortDword(DWORD wPort);
void		SyserWritePortDword(DWORD dwPort, DWORD dwValue);
void		SyserWritePortWord(DWORD dwPort, WORD wValue);
void		SyserWritePortByte(DWORD dwPort, BYTE byteValue);

void		CopyGeneralRegister(void);
bool		SyserIsSupportCPUIDInstruction(void);
bool		SyserIsSupportRDMSRInstruction(void);
void*		SyserMemoryCopy(void *dst, const void*src,int count);
bool		GetSegDescr(WORD Sel,X86_SEGMENT_DESCRIPTOR*pSegDescr);

bool		MapPhysical0();
void		UnmapPhysical0();
bool		GetLastBranchAddressPentiumM(DWORD Index,DWORD* FromAddr,DWORD* ToAddr);
PINTERRUPT_STUB SetInterruptHandlerFunction(IN BYTE Num,IN DWORD IDTBase,IN VADDR32 InterruptHandler,BYTE DescriptorType=0x10,BYTE DescriptorPrivilegeLevel=0x4,WORD Selector=0);
bool		InstallInterruptHandle(IN BYTE Num,IN VADDR32 InterruptHandler,BYTE DescriptorType=0x10,BYTE DescriptorPrivilegeLevel=0x4,WORD Selector=0);
DWORD		UninstallInterruptHandle(IN BYTE Num);
//////////////////////////////////////////////////////////////////////////////////////
//CPUID
//
struct CPUID_INFO
{
	DWORD dwEAX;
	DWORD dwEBX;
	DWORD dwECX;
	DWORD dwEDX;
};

extern		CPUID_INFO*	gpCPUIDInfo;
extern		DWORD gMaxCPUIDIndex;
extern		DWORD dwLastBranchFromEIP;
extern		DWORD dwLastBranchToEIP;
extern		DWORD dwLastIntFromEIP;
extern		DWORD dwLastIntToEIP;
extern		bool gbHaveLastBranchMointer;
VOID		SyserGetCPUID(CPUID_INFO *CPUInfo,DWORD dwIndex);
CPUID_INFO*	InitCPUIDInfo();
void		ReleaseCPUIDInfo(CPUID_INFO*pCPUIDInfo=NULL);
//
//CPUID
//////////////////////////////////////////////////////////////////////////////////////


DWORD		GetCurrentCPUInterruptProcAddress(IN DWORD Index);
bool		SyserReadMSR(DWORD dwIndex,DWORD *dwHigh,DWORD *dwLow);
bool		SyserWriteMSR(DWORD dwIndex,DWORD dwHigh,DWORD dwLow);

bool		SetBranchStepRun();
bool		ClearBranchStepRun();

bool		ReadPhysicalAddress(DWORD dwPhyscialAddress,DWORD &dwValue);
DWORD		SyserGetSegmentLimit(WORD SegmentSelector);
DWORD		GetSegmentBaseAddress(WORD SegmentSelector,DWORD *SegmentLimit=NULL);
DWORD		GetX86CR4(DWORD BitMask=0xffffffff);
DWORD		GetCR0Register();
DWORD		GetCR4Register();
DWORD		SetCR4Register(DWORD NewValue);
VOID		SyserX86FxSave(BYTE *RegisterBuffer);
bool		X86_FXSAVE(BYTE *RegisterBuffer);
bool		SyserGetFpuErrorState();
DWORD		GetNoUseDebugRegister();
bool		ReadTSC(OUT ULONGLONG *llValue);
ULONGLONG	SyserGetTSC();
BYTE GetCurrentIRQLLevel();
DWORD GetCPU_ID();
DWORD SyserClearCR0WP();
VOID SyserRestoreCR0WP(DWORD dwCR0);

__int64 __stdcall SyserPrivateReadMSR(DWORD dwIndex);
__int64 __stdcall SyserPrivateReadMSRError(VOID);
VOID __stdcall SyserPrivateWriteMSR(DWORD dwIndex,DWORD dwValueLow,DWORD dwValueHigh);
VOID __stdcall SyserPrivateWriteMSRError(VOID);
__int64 __stdcall SyserPrivateGetTSC();
__int64 __stdcall SyserPrivateGetTSCError();
VOID SyserInitSystemSegmentRegister(VOID);

#ifdef __cplusplus
}; // extern "C"
#endif


#endif
