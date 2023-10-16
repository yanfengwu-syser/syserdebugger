#ifndef _SERVICES_H_
#define _SERVICES_H_

#ifdef __cplusplus
extern "C" {
#endif

#define			FPU_REGISTER_IMAGE_SIZE	108
extern X86_GATE_DECR	gOldInterruptDescropterTable[0x100];
extern DWORD			gOldInterruptProcAddress[0x100];
extern bool				bGoToSoftice;
extern bool				gbSystemCrash;
extern bool				gbActive;
extern DWORD			dwTestSampleEntryPoint;
extern DWORD			gSofticeDriverEntry;
extern DWORD			gSofticeDriverEntryReturnAddress;
extern DWORD			OldESP;
extern DWORD			CurrentFpuImageIndex;
extern DWORD			gGenInterruptNumber;
extern DWORD			gGenInterruptOffset;

extern DWORD			SyserDR[8];
extern bool				gbTemplateTraceFlag;//临时设置一个单步断点
extern BYTE*			gpStackBufferBottom;
extern BYTE*			gpStackBufferTop;
extern BYTE*			gpStackBuffer;
extern BYTE				FpuRegisterImage[2][FPU_REGISTER_IMAGE_SIZE];
extern BYTE				FxsaveBuffer[512+15];
extern WORD				gSystemSSSegment;
extern WORD				gGenInterruptSelector;
extern DWORD			gPrevStepEIP;//前一次单步执行的 EIP 地址。这里要处理一些特殊的情况，例如前一次执行的单步命令是 pushfd 那么就要处理堆栈中的 tf 标志
										//如果上一次退出的时候不是单步退出的。这该变量为 0 
extern bool				gbBugCheckExExit;
extern bool				gbBugCheckExFlags;
extern DWORD			gpBugCheckExAddress;
extern bool				gbBugCheckExFirstByteIsCC;
extern LONG				gbLoadImage;

VOID SyserLoadReg(VOID);
VOID SyserSaveReg(VOID);
//段失败异常
VOID SyserInt0bProc(VOID);
//
VOID SyserInt06Proc(VOID);
//
VOID SyserInt0cProc(VOID);
//单步中断
VOID SyserInt01Proc(VOID);
//调试中断
VOID SyserInt2dProc(VOID);

//进程创建构子
void CreateProcessHookProc(IN HANDLE  ParentId,IN HANDLE  ProcessId,IN BOOLEAN  Create);
//线程创建构子
void CreateThreadHookProc(IN HANDLE  ProcessId,IN HANDLE  ThreadId,IN BOOLEAN  Create);
//模块装载构子
void LoadImageHookProc(IN PUNICODE_STRING  FullImageName,IN HANDLE  ProcessId,IN PIMAGE_INFO  ImageInfo);

void DebugOut(void);
void DebugOut1(DWORD dwHeight);
void WispTimeInterrupeService();

bool InstallSwapContextHook();
void RemoveSwapContextHook();
void SaveFpuRegister();
void RestorFpuRegister();

VOID SyserDisableDebugRegisterMontior(VOID);
VOID SyserEnableDebugRegisterMontior(VOID);
void EnableHardwaveBreakpoint();
VOID SyserDisableHardwaveBreakpoint(VOID);

VOID SyserSofticeDriverEntryExitCallBack(VOID);
VOID SyserSaveExceptionRegister(VOID);
void ClearExceptionRegister();
void OnPatchBugCheckEx();
void OnPatchMmUnmapViewOfSection();
void OnDebugSoftice();
void OnPatchTranslateUsageAndPagesToI8042ScanCodes();
int SyserCloseDebugRegisterMontior(VOID);
VOID SyserOpenDebugRegisterMontior(VOID);
//void PatchKeBugCheckEx();

typedef struct _KD_SYMBOLS_INFO 
{
	IN PVOID BaseOfDll;
	IN ULONG_PTR ProcessId;
	IN ULONG CheckSum;
	IN ULONG SizeOfImage;
} KD_SYMBOLS_INFO, *PKD_SYMBOLS_INFO;

void UnloadSystemModuleSymbols(PSTRING pModuleName,PKD_SYMBOLS_INFO pSymInfo);

#ifdef __cplusplus
}; // extern "C"
#endif

#endif


