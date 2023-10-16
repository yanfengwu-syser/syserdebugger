#include "stdafx.h"
#include "Int1.h"
#include "HardWareInterruptCtrl.h"
#include "Syser.h"
#include "Services.h"
#include "Int0xe.h"

#ifdef __cplusplus
extern "C" {
#endif
DWORD gIntCounter=0;
VADDR32	gOldInt01Proc=0;
DWORD dwgSetDbgReg=0;

#ifdef __cplusplus
}; // extern "C"
#endif

// __declspec(naked) void  Int01Proc()
// {
// 	__asm
// 	{		
// 		PUSHFD
// 		CMP		DWORD PTR[esp+8],offset CloseDebugRegisterMontior+1
// 		JNZ HANDLE_SET_DBG_REG
// 		PUSH	EAX
// 		MOV		EAX,0
// 		MOV		DR6,EAX
// 		POP		EAX
// 		POPFD
// 		LEA		ESP,[ESP+4]
// 		IRETD
// HANDLE_SET_DBG_REG:
// 		CMP		SS:gbActive,0		//如果没有被激活则跳转
// 		JZ		ENTER_PROC
// 		jmp HANDLE_SET_DBG_REG
// 		POPFD						//走到这里可能是一种错误情况
// 		RET		
// ENTER_PROC:
// 		POPFD
// 		CALL	StopOtherCPUs
// 		CALL	DisableDebugRegisterMontior    //虽然调用中断1 会自动关闭 Debug register 但是有可能在真正停止其他CPU之前被其他CPU中断，如果被中断则Debug rigister 监控可能被重新设置。
// 		POP		SS:gOldInt01Proc		
// 		cmp ESP,SS:gpStackBuffer
// 		jb local_uu
// 		cmp ESP,SS:gpStackBufferTop
// 		ja local_uu 
// 		push 0
// 		push EBP
// 		push ESP
// 		push Reg.EIP
// 		PUSH 0X31313131
// 		MOV EAX,KeBugCheckEx
// 		call eax
// local_uu:
// 		MOV		SS:OldESP,ESP
// 		MOV		ESP,SS:gpStackBufferTop
// 		PUSHAD
// 		PUSH FS
// 		PUSH DS
// 		PUSH ES
// 		MOV		AX,0x23		
// 		MOV		DS,AX
// 		MOV		ES,AX
// 		MOV		EBP,ESP
// 		CLD
// 	}
// 
// 	LoadReg();	
// 	ActiveHookInt0e(true);
// 	gpSyser->AttachPopupProcess(Reg.CR[3]);
// 	gIntCounter++;
// 	
// 	if(gpSyser->m_pDebugger->HandleInt1(Reg.EIP)==false)//Syser Active入口
// 	{		
// 		ActiveHookInt0e(false);
// 		SetLastBranchMointer();
// 		EnableDebugRegisterMontior();
// 		__asm
// 		{
// 			POP     ES
// 			POP     DS
// 			POP     FS
// 			POPAD
// 			MOV		ESP,SS:OldESP
// 			CALL	StartOtherCPUs
// 			JMP		CS:[gOldInt01Proc]
// 		}
// 	}	
// 	ActiveHookInt0e(false);
// 	SetLastBranchMointer();
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
// 		XCHG	EAX,[ESP+8]
// 		TEST	EAX,0x100
// 		JNZ		STEP_NEXT
// 		CALL	EnableAllHardInterrupt
// 		CALL	StartOtherCPUs
// 		JMP		local_101
// STEP_NEXT:
// 		CALL	DisableAllHardInterrupt
// local_101:
// 		XCHG	EAX,[ESP+8]
// 		CMP		SS:gGenInterruptNumber,0xFFFFFFFF
// 		JNZ		local_00100
// 		CMP		SS:bGoToSoftice,0
// 		JZ		tmpgosoftice
// 		MOV		SS:bGoToSoftice,0
// 		CALL	pSofticeActivePointer
// tmpgosoftice:
// 		IRETD
// local_00100:
// 		MOV		SS:gGenInterruptNumber,0xFFFFFFFF;
// 		JMP		CS:[gGenInterruptOffset]
// 	}
// }
