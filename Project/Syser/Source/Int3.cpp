#include "stdafx.h"
#include "Int3.h"
#include "Int0xe.h"
#include "HardWareInterruptCtrl.h"
#include "Syser.h"
#include "Services.h"
#include "MultiCPU.h"

#ifdef __cplusplus
extern "C" {
#endif

VADDR32	gOldInt03Proc=0;
extern DWORD gIntCounter;

#ifdef __cplusplus
}; // extern "C"
#endif


// __declspec(naked) void  Int03Proc()
// {
// 	__asm
// 	{
// 		PUSHFD
// 		CMP		SS:gbActive,1
// 		JNZ		SYSER_NOT_ACTIVE
// 		POPFD
// 		RET
// SYSER_NOT_ACTIVE:
// 		POPFD
// 		CALL	SyserStopOtherCPUs
// 		CALL	DisableDebugRegisterMontior		
// 		POP		SS:gOldInt03Proc				
// 		cmp ESP,SS:gpStackBuffer
// 		jb local_uu
// 		cmp ESP,SS:gpStackBufferTop
// 		ja local_uu 
// 		push 0
// 		push 0
// 		push ESP
// 		push 0
// 		PUSH 0X33333333
// 		MOV EAX,KeBugCheckEx
// 		call eax
// local_uu:
// 		MOV		SS:OldESP,esp
// 		MOV		ESP,SS:gpStackBufferTop
// 		PUSHAD 
// 		PUSH	FS
// 		PUSH	DS
// 		PUSH	ES
// 		MOV		AX,NT_DS
// 		MOV		DS,AX
// 		MOV		ES,AX
// 		MOV		EBP,ESP
// 		CLD
// 	}
// 
// 	LoadReg();
// 	ActiveHookInt0e(true);	
// 	gpSyser->AttachPopupProcess(Reg.CR[3]);
// 	
// 	if(gpSyser->m_pDebugger->HandleInt3(Reg.EIP-1)==false)//Syser Active入口
// 	{
// 		ActiveHookInt0e(false);
// 		EnableDebugRegisterMontior();
// 		__asm
// 		{
// 			POP     ES
// 			POP     DS
// 			POP     FS
// 			POPAD
// 			MOV		ESP,SS:OldESP
// 			CALL	SyserStartOtherCPUs
// 			JMP		SS:[gOldInt03Proc]
// 		}
// 	}
// 	ActiveHookInt0e(false);
// 	SaveReg();
// 	__asm
// 	{
// 		POP     ES
// 		POP     DS
// 		POP     FS
// 		POPAD
// 		MOV		ESP,SS:OldESP
// 		MOV		SS:OldESP,0
// 		CALL	SyserSyncMouseInterrupt
// 		XCHG	EAX,[ESP+8]    // EFLAGS 
// 		TEST	EAX,0x100
// 		JNZ		STEP_NEXT     //如果是以单步方式退出的，则不开启硬件中断也不允许其他 cpu 执行指令
// 		CALL	EnableAllHardInterrupt   
// 		CALL	SyserStartOtherCPUs
// 		JMP		local_101
// STEP_NEXT:
// 		CALL	DisableAllHardInterrupt
// local_101:
// 		XCHG	EAX,[ESP+8]
// 		CMP		CS:gGenInterruptNumber,0xFFFFFFFF
// 		JNZ		local_00100		
// 		CMP		CS:bGoToSoftice,0
// 		JZ		tmpgosoftice
// 		MOV		SS:bGoToSoftice,0
// 		CALL	pSofticeActivePointer
// tmpgosoftice:
// 		CMP		SS:gbBugCheckExExit,1
// 		MOV		SS:gbBugCheckExExit,0
// 		JNZ		local_ppp
// 		TEST	DWORD PTR[ESP+8],0x100
// 		JZ		local_ppp
// 		AND		DWORD PTR[ESP+8],0xFFFFFEFF
// 		PUSHFD
// 		OR		DWORD PTR[ESP],0x100
// 		POPFD
// local_ppp:
// 		IRETD
// local_00100:
// 		MOV		SS:gGenInterruptNumber,0xFFFFFFFF;
// 		JMP		CS:[gGenInterruptOffset]
// 	}
// }
