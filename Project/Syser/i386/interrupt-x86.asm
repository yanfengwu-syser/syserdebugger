;	/*
;		公共功能封装
;		
;		十二羽翼
;		QQ:764439262
;	*/
.686p
.MMX
.XMM
.model flat,StdCall
option casemap:none

include common-x86.inc
include interrupt-x86.inc

;外部函数声明
EXTERN SyserCloseDebugRegisterMontior@0:PROC
EXTERN SyserStartOtherCPUs@0:PROC
EXTERN SyserStopOtherCPUs@0:PROC
EXTERN KeBugCheckEx@20:PROC
EXTERN SyserLoadReg@0:PROC
EXTERN ActiveHookInt0e@4:PROC
EXTERN SyserAttachPopupProcess@4:PROC
EXTERN SyserDbgProcessHandleInt1@4:PROC
EXTERN SyserDbgProcessHandleInt3@4:PROC
EXTERN SetLastBranchMointer@0:PROC
EXTERN SyserEnableDebugRegisterMontior@0:PROC
EXTERN SyserSaveReg@0:PROC
EXTERN SyserSyncMouseInterrupt@0:PROC
EXTERN SyserDisableDebugRegisterMontior@0:PROC
EXTERN SetLastBranchMointer@0:PROC
EXTERN Int0dHandle@4:PROC
EXTERN Int0eHandle@4:PROC
EXTERN SyserIsgpSyserValid@0:PROC
EXTERN HandleBpr@12:PROC
EXTERN SyserInt0eProc@0:PROC
EXTERN PS2MouseOperation@0:PROC
EXTERN SetInteruptEOI@4:PROC
EXTERN GetCurrentCPULocalAPICID@0:PROC
EXTERN SaveLocalApic@4:PROC
EXTERN SyserGetIsDbgRegAccessMon@0:PROC
EXTERN SaveIOAPICInterruptVectorTable@0:PROC
EXTERN RestoreIOAPICInterruptVectorTable@0:PROC
EXTERN SyserEnableAllHardInterrupt@0:PROC
EXTERN SyserDisableAllHardInterrupt@0:PROC
EXTERN UnloadSystemModuleSymbols@8:PROC
EXTERN SyserGetInstallDebug@0:PROC
EXTERN SyserDbgPrint:PROC
EXTERN SyserGetbInitSuccess@0:PROC
EXTERN SyserbIsgpSyserValid@0:PROC
EXTERN SyserGetSysInfoSyserBase@0:PROC
EXTERN SyserGetSysInfoSyserHighBase@0:PROC
EXTERN SyserSerialMouseInterruptServiceInternal@0:PROC

;函数原型定义
;SyserPrivateReadMSR Proto :DWORD
ActiveHookInt0e Proto :BYTE
SyserAttachPopupProcess Proto	:DWORD
SyserDbgProcessHandleInt1 Proto :DWORD
SyserDbgProcessHandleInt3 Proto :DWORD
SyserStartOtherCPUs Proto
SyserStopOtherCPUs Proto
SyserLoadReg Proto
SyserDisableDebugRegisterMontior Proto
SetLastBranchMointer Proto
SyserEnableDebugRegisterMontior Proto
SyserSaveReg Proto
SyserSyncMouseInterrupt Proto
SaveExceptionRegister	Proto
Int0dHandle	Proto :DWORD
Int0eHandle Proto :DWORD
SyserIsgpSyserValid	Proto
HandleBpr	Proto :DWORD,:DWORD,:DWORD
SyserInt0eProc	Proto
KeBugCheckEx Proto :DWORD,:DWORD,:DWORD,:DWORD,:DWORD
PS2MouseOperation	Proto
SetInteruptEOI	Proto :DWORD
MouseInterruptService	Proto
GetCurrentCPULocalAPICID	Proto
SaveLocalApic	Proto :DWORD
SyserSaveSyserDRX	Proto
SyserSaveSyserDRXNew	Proto
SyserLoadContext	Proto
SyserGetIsDbgRegAccessMon	Proto
SaveIOAPICInterruptVectorTable	Proto
RestoreIOAPICInterruptVectorTable	Proto
SyserEnableAllHardInterrupt	Proto
SyserDisableAllHardInterrupt	Proto
UnloadSystemModuleSymbols	Proto :DWORD,:DWORD
SyserGetInstallDebug	Proto
SyserGetbInitSuccess	Proto
SyserbIsgpSyserValid	Proto
SyserGetSysInfoSyserBase	Proto
SyserGetSysInfoSyserHighBase	Proto
SyserSaveExceptionRegister	Proto
SyserSerialMouseInterruptServiceInternal	Proto

;
extern gbActive:BYTE
extern gbBugCheckExExit:BYTE
extern bIsMouseData:BYTE
extern gOldInt01Proc:DWORD
extern gOldInt03Proc:DWORD
extern gpStackBufferTop:DWORD
extern gpStackBuffer:DWORD
extern Reg:X86REGCONTEXT
extern OldESP:DWORD
extern gIntCounter:DWORD
extern gGenInterruptNumber:DWORD
extern bGoToSoftice:BYTE
extern pSofticeActivePointer:DWORD
extern gGenInterruptOffset:DWORD
extern gdwActiveInt0eProcAddress:DWORD
extern stKeyGlobalVariable:KEYINTERRUPTVARIABLE
extern MouseInterruptCount:DWORD
extern gpMCPULocalApic:ptr 	LOCALAPICINFO
extern gpMCPUReg:ptr X86REGCONTEXT
extern gdwLocalAPICLineAddress:DWORD
extern gdwMulitCpuSendIPIFlags:DWORD
extern gLoopCpuNumber:DWORD
extern gbSyserDRXChg:BYTE
extern gdwMulitCpuSpinlock:DWORD
extern SyserDR:ptr DWORD
extern gdwExitNmiLock:DWORD
extern gCPUNumbers:DWORD
extern gdwPIC8259Shield_1:BYTE
extern gdwPIC8259Shield_2:BYTE
extern gbIsSaveInterruptShieldRegister:BYTE
extern gdwLocalAPICTaskPriority:DWORD
extern gbIsUseAPIC:BYTE
extern gSofticeDriverEntry:DWORD
extern gSofticeDriverEntryReturnAddress:DWORD
;extern ExceptionTmpReg:X86REGCONTEXT
;extern gExceptionCurrentCpuID:DWORD
extern ExceptionReg:DWORD
extern dwOldInterruptF9:DWORD
extern dwInterruptF9Address:DWORD
extern wSerialMousePort:DWORD
extern byte3FD:BYTE

.DATA

;bInit	db	0
nnByte	db  0
gNmiCount	dd 0
int2eip		dd 0
gExceptionSpinLock	dd 0
gExceptionCurrentCpuID	dd 0
ExceptionTmpReg X86REGCONTEXT <>

SofticeDriverEntryExitCallBackStrW db 053h, 000h, 059h, 000h, 053h, 000h, 045h, 000h, 052h, 000h, 020h, 000h, 03Ah, 000h, 020h, 000h
    db 049h, 000h, 06Eh, 000h, 073h, 000h, 074h, 000h, 061h, 000h, 06Ch, 000h, 06Ch, 000h, 044h, 000h
    db 065h, 000h, 062h, 000h, 075h, 000h, 067h, 000h, 03Dh, 000h, 03Dh, 000h, 066h, 000h, 061h, 000h
    db 06Ch, 000h, 073h, 000h, 065h, 000h, 0,0
;变量内容是:
;    SYSER : InstallDebug==false
;================================================================================

.CODE

;
;	Int1.cpp
;

;VOID  SyserInt01Proc(VOID);
SyserInt01Proc	PROC
	pushfd
;	CMP		DWORD PTR[esp+8],offset CloseDebugRegisterMontior+1
	jnz @@HandleSetDbgReg
	push eax
	xor eax,eax
	mov dr6,eax
	pop eax
	popfd
	lea esp,[esp+4]
	iretd
@@HandleSetDbgReg:
	cmp ss:gbActive,0	;如果没有被激活则跳转
	jz @@EntryProc
	jmp @@HandleSetDbgReg
	popfd				;走到这里可能是一种错误情况
	ret
@@EntryProc:
	popfd
	invoke SyserStopOtherCPUs
	invoke SyserDisableDebugRegisterMontior
	pop ss:gOldInt01Proc
	cmp esp,ss:gpStackBuffer
	jb @@uu
	cmp esp,ss:gpStackBufferTop
	ja @@uu
	push 0
	push ebp
	push esp
	push Reg.EIP
	push 031313131h
	mov eax,KeBugCheckEx
	call eax
@@uu:
	mov ss:OldESP,esp
	mov esp,ss:gpStackBufferTop
	pushad
	push fs
	push ds
	push es
	mov ax,023h
	mov ds,ax
	mov es,ax
	mov ebp,esp
	cld
	invoke SyserLoadReg
	invoke ActiveHookInt0e,1
	invoke SyserAttachPopupProcess,Reg.CR[3*4]
	inc gIntCounter
	invoke SyserDbgProcessHandleInt1,Reg.EIP
	test al,al
	jnz @@SyserNotActive
	invoke ActiveHookInt0e,0
	invoke SetLastBranchMointer
	invoke SyserEnableDebugRegisterMontior
	pop es
	pop ds
	pop fs
	popad
	mov esp,ss:OldESP
	jmp cs:[gOldInt01Proc]
@@SyserNotActive:
	invoke ActiveHookInt0e,0
	invoke SetLastBranchMointer
	invoke SyserSaveReg
	pop es
	pop ds
	pop fs
	popad
	mov esp,ss:OldESP
	mov ss:OldESP,0
	invoke SyserSyncMouseInterrupt
	xchg eax,[esp+8]
	test eax,0100h
	jnz @@StepNext
	invoke SyserEnableAllHardInterrupt
	invoke SyserStartOtherCPUs
	jmp @@PassSoftice
@@StepNext:
	call SyserDisableAllHardInterrupt
@@PassSoftice:
	xchg eax,[esp+8]
	cmp ss:gGenInterruptNumber,0FFFFFFFFh
	jnz @@PassGenInterrupt
	cmp ss:bGoToSoftice,0
	jz @@TmpGoSoftice
	mov ss:bGoToSoftice,0
	call pSofticeActivePointer
@@TmpGoSoftice:
	iretd
@@PassGenInterrupt:
	mov ss:gGenInterruptNumber,0FFFFFFFFh
	jmp cs:[gGenInterruptOffset]
SyserInt01Proc	ENDP

;
;	Int3.cpp
;

;VOID  SyserInt03Proc(VOID)
SyserInt03Proc	PROC
	pushfd
	cmp ss:gbActive,1
	jnz @@SyserNotActive
	popfd
	ret		;?不应该是Iret吗？
@@SyserNotActive:
	popfd
	call SyserStopOtherCPUs
	call SyserDisableDebugRegisterMontior
	pop ss:gOldInt03Proc
	cmp esp,ss:gpStackBuffer
	jb @@uu
	cmp esp,ss:gpStackBufferTop
	ja @@uu
	push 0
	push 0
	push esp
	push 0
	push 033333333h
	mov eax,KeBugCheckEx
	call eax
@@uu:
	mov ss:OldESP,esp
	mov esp,ss:gpStackBufferTop
	pushad
	push fs
	push ds
	push es
	mov ax,NT_DS
	mov ds,ax
	mov es,ax
	mov ebp,esp
	cld
	invoke SyserLoadReg
	invoke ActiveHookInt0e,1
	invoke SyserAttachPopupProcess,Reg.CR[3*4]
	invoke SyserDbgProcessHandleInt3,Reg.EIP-1
	test al,al
	jnz @@NoSyserActiveEntry
	invoke ActiveHookInt0e,0
	invoke SyserEnableDebugRegisterMontior
	pop es
	pop ds
	pop fs
	popad
	mov esp,ss:OldESP
	invoke SyserStartOtherCPUs
	jmp ss:[gOldInt03Proc]
@@NoSyserActiveEntry:
	invoke ActiveHookInt0e,0
	invoke SyserSaveReg
	pop es
	pop ds
	pop fs
	popad
	mov esp,ss:OldESP
	mov ss:OldESP,0
	invoke SyserSyncMouseInterrupt
	xchg eax,[esp+8]	;eflags
	test eax,0100h
	jnz @@StepNext				;如果是以单步方式退出的，则不开启硬件中断也不允许其他 cpu 执行指令
	invoke SyserEnableAllHardInterrupt
	invoke SyserStartOtherCPUs
	jmp @@101
@@StepNext:
	invoke SyserDisableAllHardInterrupt 
@@101:
	xchg eax,[esp+8]
	cmp cs:gGenInterruptNumber,0FFFFFFFFh
	jnz @@100
	cmp cs:bGoToSoftice,0
	jz @@tmpgosoftice
	mov ss:bGoToSoftice,0
	call pSofticeActivePointer
@@tmpgosoftice:
	cmp ss:gbBugCheckExExit,1
	mov ss:gbBugCheckExExit,0
	jnz @@ppp
	test dword ptr[esp+8],0100h
	jz @@ppp
	and dword ptr[esp+8],0FFFFFEFFh
	pushfd
	or dword ptr[esp],0100h
	popfd
@@ppp:
	iretd
@@100:
	mov ss:gGenInterruptNumber,0FFFFFFFFh
	jmp cs:[gGenInterruptOffset]
SyserInt03Proc	ENDP

;
;	Int0x6.cpp
;

;VOID SyserInt06Proc(VOID);
SyserInt06Proc	PROC
	push dword ptr 06h
	invoke SyserSaveExceptionRegister
	lea esp,[esp+4]
	pushfd
	pushad
	mov ebp,esp
	push ds
	push es
	push fs
	mov eax,NT_DS
	mov ds,ax
	mov es,ax
	pop fs
	pop es
	pop ds
	popad
	popfd
	ret		;为什么不用iretd
SyserInt06Proc	ENDP

;
;	Int0xb.cpp
;

;VOID SyserInt0bProc(VOID);
SyserInt0bProc	PROC
	push dword ptr 0bh
	lea esp,[esp+4]
	pushfd
	pushad
	push ds
	push es
	push fs
	mov eax,NT_DS
	mov ds,ax
	mov es,ax
	pop fs
	pop es
	pop ds
	popad
	popfd
	ret
SyserInt0bProc	ENDP

;
;	Int0xc.cpp
;

;VOID SyserInt0cProc(VOID);
SyserInt0cProc	PROC
	push dword ptr 0ch
	call SyserSaveExceptionRegister
	lea esp,[esp+4]
	pushfd
	pushad
	mov ebp,esp
	push ds
	push es
	push fs
	mov ax,NT_DS
	mov ds,ax
	mov es,ax
	mov ax,NT_FS
	mov fs,ax
	pop fs
	pop es
	pop ds
	popad
	popfd
	ret
SyserInt0cProc	ENDP

;
;	Int0xd.cpp
;

;VOID SyserInt0dProc(VOID);
SyserInt0dProc	PROC
;	local Int0dStackPointer:DWORD	;不能用,不然会导致编译器自己去变ESP这些
	push dword ptr 0dh
	call SyserSaveExceptionRegister
	lea esp,[esp+4]				;丢掉 push dword ptr 0dh
	pushfd
	pushad
	push ds
	push es
	push fs
	mov eax,NT_DS
	mov ds,ax
	mov es,ax
	mov eax,NT_FS 
	mov fs,ax
	mov ebp,esp
	lea esp,[esp-4]
	mov [ebp-4],ebp		;[ebp-4]在这里就相当于Int0dStackPointer
	add [ebp-4],038h
	invoke Int0dHandle,[ebp-4]
	test al,al
	jz @@Int0dQuit
	lea esp,[esp+4]		;这里是丢掉 Int0dStackPointer 局部变量
	pop fs
	pop es
	pop ds
	popad   
	popfd
	lea esp,[esp+8]		;code error;windows return address
	iretd
@@Int0dQuit:
	lea esp,[esp+4]
	pop fs
	pop es
	pop ds
	popad
	popfd
	ret
SyserInt0dProc	ENDP

;
;	Int0xe.cpp
;

;VOID SyserInt0eProc(VOID);
SyserInt0eProc	PROC
;	local Int0eStackPointer:DWORD	[ebp-4]
;	local PagedCR2:DWORD	[ebp-8]
	push dword ptr 0Eh
	call SyserSaveExceptionRegister
	lea esp,[esp+4]		;丢掉 push dword ptr 0xe
	pushfd
	pushad
	mov ebp,esp
	lea esp,[esp-08h]    ;留出两个局部变量的空间
	mov [ebp-4],ebp 
	mov eax,cr2 
	mov [ebp-8],eax
	add [ebp-4],028h
	push ds
	push es
	push fs
	mov ax,NT_DS 
	mov ds,ax 
	mov es,ax
	mov ax,NT_FS
	mov fs,ax
	mov eax,cr2
	cld
	invoke Int0eHandle,[ebp-4]
	test al,al
	jz @@NoErrorInSyser
	pop fs
	pop es
	pop ds
	lea esp,[esp+8]	;丢掉两个局部变量
	popad
	popfd
	lea esp,[esp+8]	;丢掉 errorcode 和 windows return address
	iretd			;直接返回
@@NoErrorInSyser:
	invoke SyserIsgpSyserValid
	test al,al
	jz @@gpSyserInValid
	push edi
	mov edi,[ebp-4]
	push edi
	push [edi]
	push [ebp-8]
	call HandleBpr
	pop edi
	test al,al
	jz @@gpSyserInValid
	pop fs
	pop es
	pop ds
	lea esp,[esp+8]	;丢掉两个局部变量
	popad
	popfd
	lea esp,[esp+8]	;丢掉 errorcode 和 windows return address
	or dword ptr[esp+8],0100h
	iretd
@@gpSyserInValid:
	push edi
	mov edi,[ebp-4]
	add edi,12
	and [edi],0100h
	test edi,edi
	jz @@Quit
	invoke SyserEnableAllHardInterrupt
	invoke SyserStartOtherCPUs
@@Quit:
	pop fs
	pop es
	pop ds
	lea esp,[esp+8]	;丢掉两个局部变量
	popad
	popfd
	ret				;返回到原始的WINDOWS中断处理地址
SyserInt0eProc	ENDP

;VOID SyserActive_Int0eProcStub(VOID);
SyserActive_Int0eProcStub	PROC
	push ss:gdwActiveInt0eProcAddress
	jmp SyserInt0eProc
SyserActive_Int0eProcStub	ENDP

;
;	PS2Mouse.cpp
;

;VOID SyserInterrupt_0xF9_Mouse_Service(VOID);
SyserInterrupt_0xF9_Mouse_Service	PROC
	pushfd
	cmp cs:gbActive,0
	jnz @@SyserActive
	push eax
	in al,064h
	test al,1
	pop eax
	jnz @@SyserActive
	popfd
	ret
@@SyserActive:
	popfd
	push cs:MouseInterruptService
	ret
SyserInterrupt_0xF9_Mouse_Service	ENDP

;VOID MouseInterruptService(VOID);
MouseInterruptService	PROC
	cmp cs:gbActive,1
	jz @@SyserActive
	mov ss:bIsMouseData,1
	ret
@@SyserActive:
	lea esp,[esp+4]
	pushad
	pushfd
	in al,064h
	and eax,0ffh
	mov nnByte,al
	mov ebx,eax
	in al,060h
	mov stKeyGlobalVariable.chCurrentMouseData,al
	invoke PS2MouseOperation
	inc MouseInterruptCount
	invoke SetInteruptEOI,0Ch
	popfd
	popad
	iretd
MouseInterruptService	ENDP

;
;	NMIInterruptHandle.cpp
;

;VOID SyserLoadContext(VOID);
SyserLoadContext	PROC
	local CurrentCpuID:DWORD
	local TmpContext:X86REGCONTEXT
	pushad
	pushfd
	mov eax,dr0
	mov TmpContext.DR[0*4],eax
	mov eax,dr1
	mov TmpContext.DR[1*4],eax
	mov eax,dr2
	mov TmpContext.DR[2*4],eax
	mov eax,dr3
	mov TmpContext.DR[3*4],eax
	mov eax,dr6
	mov TmpContext.DR[6*4],eax
	mov eax,dr7
	mov TmpContext.DR[7*4],eax
	sldt word ptr TmpContext.LDT
	str word ptr TmpContext.TR
	sgdt fword ptr TmpContext.GDTLimit
	sidt fword ptr TmpContext.IDTLimit
	mov eax,[ebp+010h]
	mov TmpContext.GeneReg[EDI_IDX*4],eax 
	mov eax,[ebp+014h]
	mov TmpContext.GeneReg[ESI_IDX*4],eax 
	mov eax,[ebp+018h]
	mov TmpContext.GeneReg[EBP_IDX*4],eax 
	mov eax,[ebp+01Ch]
	mov TmpContext.GeneReg[ESP_IDX*4],eax 
	mov eax,[ebp+020h]
	mov TmpContext.GeneReg[EBX_IDX*4],eax 
	mov eax,[ebp+024h]
	mov TmpContext.GeneReg[EDX_IDX*4],eax 
	mov eax,[ebp+028h]
	mov TmpContext.GeneReg[ECX_IDX*4],eax 
	mov eax,[ebp+02Ch]
	mov TmpContext.GeneReg[EAX_IDX*4],eax 
	mov eax,[ebp+040h]
	mov TmpContext.EFlags,eax 
	mov eax,[ebp+038h]
	mov TmpContext.EIP,eax 
	
	mov eax,cr0
	mov TmpContext.CR[0*4],eax
	mov eax,cr2
	mov TmpContext.CR[2*4],eax
	mov eax,cr3
	mov TmpContext.CR[3*4],eax
	mov eax,cr4
	mov TmpContext.CR[4*4],eax
	mov eax,TmpContext.EFlags
	test eax,020000h
	jz @@001
	mov eax,[ebp+044h]
	mov TmpContext.GeneReg[ESP_IDX*4],eax
	mov eax,[ebp+048h]
	mov TmpContext.SegReg[SS_IDX*2],ax
	mov eax,[ebp+04Ch]
	mov TmpContext.SegReg[ES_IDX*2],ax
	mov eax,[ebp+050h]
	mov TmpContext.SegReg[DS_IDX*2],ax
	mov eax,[ebp+054h]
	mov TmpContext.SegReg[FS_IDX*2],ax
	mov eax,[ebp+058h]
	mov TmpContext.SegReg[GS_IDX*2],ax
	jmp @@002
@@001:
	mov eax,[ebp+8]
	mov TmpContext.SegReg[ES_IDX*2],ax 
	mov eax,[ebp+0Ch]
	mov TmpContext.SegReg[DS_IDX*2],ax
	mov ax,fs 
	mov TmpContext.SegReg[FS_IDX*2],ax
	mov ax,gs
	mov TmpContext.SegReg[GS_IDX*2],ax
	mov eax,[ebp+03Ch]
	mov TmpContext.SegReg[CS_IDX*2],ax
	test ax,3
	jnz @@005
	lea eax,[ebp+044h]
	mov TmpContext.GeneReg[ESP_IDX*4],eax 
	mov ax,ss 
	mov TmpContext.SegReg[SS_IDX*2],ax
	jmp @@002
@@005:
	mov eax,[ebp+044h]
	mov TmpContext.GeneReg[ESP_IDX*4],eax 
	mov eax,[ebp+048h]
	mov TmpContext.SegReg[SS_IDX*2],ax
@@002:
	invoke GetCurrentCPULocalAPICID
	mov CurrentCpuID,eax
	mov ecx,SIZEOF LOCALAPICINFO
	imul ecx
	add eax,gpMCPULocalApic
	push eax					;&gpMCPULocalApic[CurrentCpuID]
	invoke SaveLocalApic,eax
	lea esi,TmpContext
	mov ecx,SIZEOF X86REGCONTEXT
	mov eax,CurrentCpuID
	imul ecx
	add eax,gpMCPUReg
	mov edi,eax
	rep movsb
	pop esi
	mov [eax + X86REGCONTEXT.LocalAPIC],esi
	popfd
	popad
	ret
SyserLoadContext	ENDP

;VOID SyserEnterLoop(DWORD* dwPtr);
SyserEnterLoop	PROC	dwPtr
	local CurrentCpuID:DWORD
	pushad
	pushfd
	mov eax,gdwLocalAPICLineAddress
	mov ebx,[eax+080h]
	push ebx
	mov ebx,0ffh
	mov [eax+080h],ebx
	invoke GetCurrentCPULocalAPICID
	mov CurrentCpuID,eax
	mov gdwMulitCpuSendIPIFlags,0
	lock inc dword ptr gLoopCpuNumber
@@Loop:
	cmp gdwMulitCpuSpinlock,0
	jz @@QuitLoop
	test gbSyserDRXChg,0
	jz @@ContineLoop
	call SyserSaveSyserDRX
	mov gbSyserDRXChg,0
@@ContineLoop:	
	jmp @@Loop
@@QuitLoop:
	lock dec dword ptr gLoopCpuNumber
	mov eax,gdwLocalAPICLineAddress
	pop ebx
	mov [eax+080h],ebx
	popfd
	popad
	ret
SyserEnterLoop	ENDP

;VOID SyserSaveSyserDRX(VOID);
SyserSaveSyserDRX	PROC
	push eax
	push ecx
	mov ecx,SyserDR
	mov	eax,[ecx + 0*4]
	mov	dr0,eax
	mov	eax,[ecx + 1*4]
	mov	dr1,eax
	mov	eax,[ecx + 2*4]
	mov	dr2,eax
	mov	eax,[ecx + 3*4]
	mov	dr3,eax
	xor	eax,eax 
	mov	dr6,eax
	mov	eax,[ecx + 7*4]
	and	eax,0ffffdfffh
	mov	dr7,eax
	pop ecx
	pop eax
	ret
SyserSaveSyserDRX	ENDP

;VOID SyserSaveSyserDRXNew(VOID);
SyserSaveSyserDRXNew	PROC
	push	eax
	push	ecx
	mov		ecx,SyserDR
	mov		eax,[ecx + 2*4]
	mov		dr2,eax
	mov		eax,[ecx + 1*4]
	mov		dr1,eax		
	mov		eax,[ecx + 3*4]
	mov		dr3,eax
	mov		eax,[ecx + 0*4]
	mov		dr0,eax
	xor		eax,eax 
	mov		dr6,eax
	mov		eax,[ecx + 7*4]
	and		eax,0ffffdfffh
	mov		dr7,eax
	pop		ecx
	pop		eax
	ret
SyserSaveSyserDRXNew	ENDP

;VOID SyserNMIInterruptService(VOID);
SyserNMIInterruptService	PROC
	local dwEBP:ptr DWORD
	pushfd
	cmp		gCPUNumbers,1
	jnz		@@MultiCPUMachine
	popfd
	ret						;在单cpu 的机器上直接返回到 windows 的中断. fixme 
@@MultiCPUMachine:
	pushad
	push	ds
	push	es		
	cli
	mov		ax,ss
	mov		ds,ax
	mov		es,ax
	mov eax,[esp+12*4]
	mov		int2eip,eax
	lock inc gNmiCount
	invoke SyserDisableDebugRegisterMontior
	invoke SyserLoadContext
	push esp
	call SyserEnterLoop
	invoke SyserGetIsDbgRegAccessMon
	test al,0
	jz @@DbgRegAMonFalse
	call SyserSaveSyserDRXNew
@@DbgRegAMonFalse:
	cmp gNmiCount,2
	jge @@Quit
	invoke SyserEnableDebugRegisterMontior
@@Quit:
	lock dec gNmiCount
	pop es
	pop ds
	popad
	popfd
	lea esp,[esp+4]
	mov gdwExitNmiLock,0
	iretd
SyserNMIInterruptService	ENDP

;
;	HardWareInterruptCtrl.cpp
;

;VOID SyserDisableAllHardInterrupt(VOID);
SyserDisableAllHardInterrupt	PROC
	pushad
	cmp gbIsSaveInterruptShieldRegister,0
	jnz @@5
	cmp  gbIsUseAPIC,0
	jz @@1
	mov eax,gdwLocalAPICLineAddress
	mov eax,[eax + 080h]
	mov gdwLocalAPICLineAddress,eax
	invoke SaveIOAPICInterruptVectorTable
	jmp @@4
@@1:
	in al,021h
	mov gdwPIC8259Shield_1,al
	mov ecx,0100h
@@2:
	loop @@2
	in al,0A1h
	mov gdwPIC8259Shield_2,al
	mov ecx,0100h
@@3:
	loop @@3
@@4:
	mov gbIsSaveInterruptShieldRegister,1
@@5:
	cmp gbIsUseAPIC,0
	jz @@6
	mov eax,gdwLocalAPICLineAddress
	mov dword ptr [eax+080h],0ffh
	jmp @@Quit
@@6:
	mov al,0ffh
	out 021h,al
	mov ecx,0100h
@@7:
	loop @@7
	out 0A1h,al
	mov ecx,0100h
@@8:
	loop @@8
	in al,021h
	mov ecx,0100h
@@9:
	loop @@9
	in al,0A1h
	mov ecx,0100h
@@10:
	loop @@10
@@Quit:
	popad
	ret
SyserDisableAllHardInterrupt	ENDP

;VOID SyserEnableAllHardInterrupt(VOID);
SyserEnableAllHardInterrupt	PROC
	pushad
	push ds
	push es
	mov ax,NT_DS
	mov ds,ax
	mov es,ax
	cmp gbIsSaveInterruptShieldRegister,0
	jz @@Quit
	cmp gbIsUseAPIC,0
	jz @@IsUseAPICElse
	invoke RestoreIOAPICInterruptVectorTable
	mov eax,gdwLocalAPICLineAddress
	mov ebx,gdwLocalAPICTaskPriority
	mov [eax+080h],ebx
	jmp @@IfEnd		
@@IsUseAPICElse:
	mov al,gdwPIC8259Shield_1
	out 021h,al				
	mov ecx,0100h
@@1:
	loop @@1				
	mov al,gdwPIC8259Shield_2
	out 0A1h,al				
	mov ecx,0100h
@@2:			
	loop @@2			
@@IfEnd:
	mov gbIsSaveInterruptShieldRegister,0
@@Quit:
	pop es
	pop ds
	popad
	ret
SyserEnableAllHardInterrupt	ENDP

;
;	Services.cpp
;

;VOID SyserInt2dProc(VOID);
SyserInt2dProc	PROC
	pushad
	push ds
	push es
	push fs
	mov bp,NT_DS
	mov ds,bp
	mov es,bp
	mov bp,NT_FS
	mov fs,bp
	mov ebp,esp
	sub esp,12
	mov [ebp],eax;	;SrvID
	mov [ebp-4],ecx	;Arg1
	mov [ebp-8],edx	;Arg2
	cmp eax,3
	jnz @@Case4
	jmp @@EndSwitch
@@Case4:
	cmp eax,4
	jnz @@EndSwitch
	invoke UnloadSystemModuleSymbols,[ebp-4],[ebp-8]
@@EndSwitch:
	mov esp,ebp
	pop fs
	pop es
	pop ds
	popad
	ret
SyserInt2dProc	ENDP

;VOID SyserSofticeDriverEntryExitCallBack(VOID);
SyserSofticeDriverEntryExitCallBack	PROC
	pushad
	pushfd
	invoke SyserGetInstallDebug
	test eax,eax
	jnz @@1
	lea eax,SofticeDriverEntryExitCallBackStrW
	push eax
	push 296
	push 2
	call SyserDbgPrint
	add esp,12
@@1:
	mov gSofticeDriverEntry,0
	popad
	popfd
	push ss:gSofticeDriverEntryReturnAddress
	ret
SyserSofticeDriverEntryExitCallBack	ENDP

;
;	PIC_8259.cpp
;

;VOID SyserEnablePIC8259HardWareInterrupt(DWORD arg);
SyserEnablePIC8259HardWareInterrupt	PROC arg
	cmp arg,08h
	jnb @@Else
	push ebx
	push eax
	mov ebx,arg
	in al,021h
	push ecx
	mov ecx,0100h
@@1:
	loop @@1
	pop ecx
	btr eax,ebx
	out 021h,al
	push ecx
	mov ecx,0100h
@@2:
	loop @@2
	pop ecx
	pop eax
	pop ebx
	jmp @@Quit
@@Else:
	mov eax,arg
	sub eax,8
	mov arg,eax
	push ebx
	push eax
	push ecx
	mov ebx,arg
	in al,0A1h
	mov ecx,0100h
@@3:
	loop @@3
	btr eax,ebx
	out 0A1h,al
	mov ecx,0100h
@@4:
	loop @@4
	in al,021h
	mov ecx,0100h
@@5:
	loop @@5
	and al,0FBh
	out 021h,al
	mov ecx,0100h
@@6:
	loop @@6
	pop ecx
	pop eax
	pop ebx
@@Quit:
	ret
SyserEnablePIC8259HardWareInterrupt	ENDP

;VOID SyserSet8259EOI(DWORD dwInterruptNum);
SyserSet8259EOI	PROC dwInterruptNum
	cmp dwInterruptNum,010h
	jnb @@Quit
	cmp dwInterruptNum,8
	jb @@Else
	push eax
	push ecx
	mov eax,dwInterruptNum
	sub eax,8
	add eax,060h
	out 0A0h,al
	mov ecx,0200h
@@2:
	loop @@2
	mov al,062h
	out 020h,al
	mov ecx,0200h
@@3:
	loop @@3
	pop ecx
	pop eax
	jmp @@Quit	
@@Else:
	push eax
	mov eax,dwInterruptNum
	add eax,060h
	out 020h,al
	push ecx
	mov ecx,0200h
@@1:
	loop @@1
	pop ecx
	pop eax
@@Quit:
	ret
SyserSet8259EOI	ENDP

;VOID SyserSaveExceptionRegister(VOID);
SyserSaveExceptionRegister	PROC
	push ebp
	mov ebp,esp
	sub esp,4
	mov [ebp - 4],0
@@002:
	inc dword ptr [ebp-4]
	cmp [ebp-4],01000h
	jg @@3
	lock bts dword ptr gExceptionSpinLock,01Fh
	jb @@002
@@003:
	push eax
	push ds
	mov eax,010h
	mov ds,ax
	mov eax,[esp+4]
	mov ExceptionTmpReg.GeneReg[EAX_IDX*4],eax 
	xor eax,eax
	mov eax,[esp]
	mov ExceptionTmpReg.SegReg[DS_IDX*2],ax 
	mov ExceptionTmpReg.GeneReg[ECX_IDX*4],ecx 
	mov ExceptionTmpReg.GeneReg[EDX_IDX*4],edx 
	mov ExceptionTmpReg.GeneReg[EBX_IDX*4],ebx 
	mov ExceptionTmpReg.GeneReg[ESI_IDX*4],esi 
	mov ExceptionTmpReg.GeneReg[EDI_IDX*4],edi 
	mov eax,[ebp+0]
	mov ExceptionTmpReg.GeneReg[EBP_IDX*4],eax		
	mov eax,[ebp+018h]
	mov ExceptionTmpReg.SegReg[CS_IDX*2],ax 
	test ax,03h
	jz @@2
	mov eax,[ebp+020h] 
	mov ExceptionTmpReg.GeneReg[ESP_IDX*4],eax
	mov eax,[ebp+024h]
	mov ExceptionTmpReg.SegReg[SS_IDX*2],ax 
	jmp @@3
@@2:
	lea eax,[ebp+020h]
	mov ExceptionTmpReg.GeneReg[ESP_IDX*4],eax
	mov ax,ss
	mov ExceptionTmpReg.SegReg[SS_IDX*2],ax 
@@3:
	xor eax,eax 
	mov ax,fs
	mov ExceptionTmpReg.SegReg[FS_IDX*2],ax 
	mov ax,es
	mov ExceptionTmpReg.SegReg[ES_IDX*2],ax 
	mov ax,gs
	mov ExceptionTmpReg.SegReg[GS_IDX*2],ax
	mov eax,[ebp+010h]
	mov ExceptionTmpReg.ExceptionInterruptErrorCode,eax 
	mov eax,[ebp+08h]
	mov ExceptionTmpReg.ExceptionInterruptNumber,eax
	mov eax,[ebp+014h]
	mov ExceptionTmpReg.EIP,eax 
	mov eax,[ebp+01Ch]
	mov ExceptionTmpReg.EFlags,eax 
	pop ds 
	pop eax
	pushad
	pushfd 
	cld
	call SyserbIsgpSyserValid
	test al,al
	jz @@EndIf
	call SyserbIsgpSyserValid
	test al,al
	jz @@EndIf
	call GetCurrentCPULocalAPICID
	mov gExceptionCurrentCpuID,eax
	call SyserGetSysInfoSyserBase
	cmp ExceptionTmpReg.EIP,eax
	jb @@IfBody
	call SyserGetSysInfoSyserHighBase
	cmp ExceptionTmpReg.EIP,eax
	jnb @@IfBody
	jmp @@EndIf
@@IfBody:
	mov eax,gExceptionCurrentCpuID
	mov ecx,SIZEOF X86REGCONTEXT
	imul ecx
	add eax,ExceptionReg
	mov edi,eax
	lea esi,ExceptionTmpReg
	rep movsb
@@EndIf:
	lock btr dword ptr gExceptionSpinLock,01Fh
	popfd
	popad 
	mov esp,ebp
	pop ebp
	ret
SyserSaveExceptionRegister	ENDP

;VOID SyserSerialCom1Com3Proc(VOID);
SyserSerialCom1Com3Proc	PROC
	pushfd
	cmp cs:gbActive,1
	jz @@001
	popfd
	ret
@@001:
	pushad
	push ds
	push es
	mov eax,010h
	mov ds,ax
	mov es,ax
	invoke SetInteruptEOI,4
	pop es
	pop ds
	popad
	popfd
	lea esp,[esp+4]
	iretd
SyserSerialCom1Com3Proc	ENDP

;VOID SyserSerialCom2Com4Proc(VOID);
SyserSerialCom2Com4Proc	PROC
	pushfd	
	cmp cs:gbActive,1
	jz @@001
	popfd
	ret
@@001:
	pushad
	push ds
	push es
	mov eax,010H
	mov ds,ax
	mov es,ax
	invoke SetInteruptEOI,3;
	pop es
	pop ds		
	popad
	popfd
	lea esp,[esp+4]
	iretd
SyserSerialCom2Com4Proc	ENDP

;VOID SyserInterrupt_0xFB_Com1_Com3_Service(VOID);
SyserInterrupt_0xFB_Com1_Com3_Service	PROC
	pushfd
	cmp cs:gbActive,0
	jnz @@2
	popfd
	ret
@@2:
	popfd
	push cs:SyserSerialCom1Com3Proc
	ret
SyserInterrupt_0xFB_Com1_Com3_Service	ENDP

;VOID SyserInterrupt_0xFC_Com2_Com4_Service(VOID);
SyserInterrupt_0xFC_Com2_Com4_Service	PROC
	pushfd
	cmp cs:gbActive,0
	jnz @@2
	popfd
	ret
@@2:
	popfd
	push cs:SyserSerialCom2Com4Proc
	ret
SyserInterrupt_0xFC_Com2_Com4_Service	ENDP

;
;	SerialMouse.cpp
;

;VOID SyserSerialMouseInterruptService(VOID);
SyserSerialMouseInterruptService	PROC
	cmp cs:dwOldInterruptF9,1
	jnz @@007
	mov ss:dwOldInterruptF9,0
	push cs:dwInterruptF9Address
	ret
@@007:
	cmp cs:gbActive,1
	jz @@1
	push dword ptr cs:stKeyGlobalVariable.dwOldMouseInterrupt
	ret		
@@1:
	pushad
	pushfd			
	push ds
	mov edx,wSerialMousePort
	lea edx,[edx+5]
	in al,dx
	mov byte3FD,al
	lea edx,[edx-5]
	in al,dx	
	mov stKeyGlobalVariable.chCurrentMouseData,al
	call SyserSerialMouseInterruptServiceInternal
	invoke SetInteruptEOI,3
	pop ds
	popfd
	popad
	iretd
SyserSerialMouseInterruptService	ENDP
END
