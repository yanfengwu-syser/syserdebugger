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

;外部函数声明
;EXTERN	 HvmSubvertCpu@4:PROC  
;EXTERN	 HvmResumeGuest@0:PROC
EXTERN   SyserIsSupportRDMSRInstruction@0:PROC
EXTERN  InsertKeyboardBuffer@4:PROC
EXTERN	GetCurrentCPULocalAPICID@0:PROC
EXTERN	Beep@8:PROC
EXTERN SaveFpuRegister@0:PROC
EXTERN SaveLocalApic@4:PROC
EXTERN EnableHardwaveBreakpoint@0:PROC
EXTERN SyserGetbUpdateReg@0:PROC
EXTERN SyserSetbUpdateReg@4:PROC
EXTERN RestorFpuRegister@0:PROC
EXTERN SyserGetIsDbgRegAccessMon@0:PROC

;函数原型定义
SyserPrivateReadMSR Proto :DWORD
SyserPrivateGetTSC Proto
SyserPrivateWriteMSR Proto :DWORD,:DWORD,:DWORD
SyserGetIDTBase Proto :DWORD
InsertKeyboardBuffer	Proto :BYTE
SyserSaveFlags	Proto :DWORD
SyserRestoreFlags Proto :DWORD
Beep Proto :DWORD,:DWORD
GetCurrentCPULocalAPICID Proto
SaveFpuRegister	Proto
SaveLocalApic	Proto :DWORD
EnableHardwaveBreakpoint	Proto
SyserGetbUpdateReg	Proto
SyserSetbUpdateReg	Proto :DWORD
RestorFpuRegister	Proto
SyserGetIsDbgRegAccessMon	Proto
SyserCloseDebugRegisterMontior	Proto
SyserOpenDebugRegisterMontior	Proto

;
extern gSystemFSRegisterSelector:DWORD
extern gSystemSSRegisterSelector:DWORD
extern gSystemCSRegisterSelector:DWORD
extern gSystemDSRegisterSelector:DWORD
extern gbActive:BYTE
extern stKeyGlobalVariable:KEYINTERRUPTVARIABLE
extern dwMousePackageBeginOffset:DWORD
extern dwWaitMouseInterrupt:DWORD
extern gCPUNumbers:DWORD
extern gLoopCpuNumber:DWORD
extern gdwExitNmiLock:DWORD
extern gdwMulitCpuSpinlock:DWORD
extern gdwCurrentCPUIndex:DWORD
extern gdwMulitCpuSendIPIFlags:DWORD
extern gdwLocalAPICLineAddress:DWORD
extern Reg:X86REGCONTEXT
extern OldESP:DWORD
extern gpMCPUReg:ptr X86REGCONTEXT
extern ReadOnlyActiveReg:X86REGCONTEXT
extern gpMCPULocalApic:ptr LOCALAPICINFO
extern ReturnContext:RETURNCONTEXT
extern gPrevStepEIP:DWORD

;
;	和GUEST_REGS结构对应
;
CM_SAVE_ALL_NOSEGREGS MACRO
        push edi
        push esi
        push ebp
        push ebp ;        push esp
        push ebx
        push edx
        push ecx
        push eax
ENDM

CM_RESTORE_ALL_NOSEGREGS MACRO
        pop eax
        pop ecx
        pop edx
        pop ebx
        pop ebp ;        pop esp
        pop ebp
        pop esi
        pop edi        
ENDM

.DATA

bInit	db	0
bHaveCPUIDInstruction	db 0
CR0Backup	dd	0
bInitIsSupportRDMSRInstruction db 0
bHaveReadWriteMSRInstruction	db 0


.CODE

;
;	公共功能
;

;VOID  SyserSaveFlagsLow16(PWORD	_SaveFlags);
SyserSaveFlagsLow16	PROC _SaveFlags
	push eax
	push esi
	pushf
	pop ax
	mov esi,_SaveFlags
	mov [esi],ax
	pop esi
	pop eax
	ret
SyserSaveFlagsLow16	ENDP

;VOID  SyserRestoreFlagsLow16(WORD	_Flags);
SyserRestoreFlagsLow16	PROC  _Flags
	push eax
	push _Flags
	popf
	pop eax
	ret
SyserRestoreFlagsLow16	ENDP

;VOID	SyserPushad(PX86SaveRegs	Regs);以后可以考虑用拷贝做优化
SyserPushad	PROC Regs
	pushad
	mov esi,esp
	mov edi,Regs
	mov eax,[esi + X86SAVEREGS.SaveEdi]
	mov [edi + X86SAVEREGS.SaveEdi],eax
	mov eax,[esi + X86SAVEREGS.SaveEsi]
	mov [edi + X86SAVEREGS.SaveEsi],eax
	mov eax,[esi + X86SAVEREGS.SaveEbp]
	mov [edi + X86SAVEREGS.SaveEbp],eax
	mov eax,[esi + X86SAVEREGS.SaveEsp]
	mov [edi + X86SAVEREGS.SaveEsp],eax
	mov eax,[esi + X86SAVEREGS.SaveEbx]
	mov [edi + X86SAVEREGS.SaveEbx],eax
	mov eax,[esi + X86SAVEREGS.SaveEdx]
	mov [edi + X86SAVEREGS.SaveEdx],eax
	mov eax,[esi + X86SAVEREGS.SaveEcx]
	mov [edi + X86SAVEREGS.SaveEcx],eax
	mov eax,[esi + X86SAVEREGS.SaveEax]
	mov [edi + X86SAVEREGS.SaveEax],eax
	popad
	ret
SyserPushad	ENDP

;VOID	SyserPopad(PX86SaveRegs	Regs);以后可以考虑用拷贝做优化
SyserPopad	PROC Regs
	pushad
	mov edi,esp
	mov esi,Regs
	mov eax,[esi + X86SAVEREGS.SaveEdi]
	mov [edi + X86SAVEREGS.SaveEdi],eax
	mov eax,[esi + X86SAVEREGS.SaveEsi]
	mov [edi + X86SAVEREGS.SaveEsi],eax
	mov eax,[esi + X86SAVEREGS.SaveEbp]
	mov [edi + X86SAVEREGS.SaveEbp],eax
	mov eax,[esi + X86SAVEREGS.SaveEsp]
	mov [edi + X86SAVEREGS.SaveEsp],eax
	mov eax,[esi + X86SAVEREGS.SaveEbx]
	mov [edi + X86SAVEREGS.SaveEbx],eax
	mov eax,[esi + X86SAVEREGS.SaveEdx]
	mov [edi + X86SAVEREGS.SaveEdx],eax
	mov eax,[esi + X86SAVEREGS.SaveEcx]
	mov [edi + X86SAVEREGS.SaveEcx],eax
	mov eax,[esi + X86SAVEREGS.SaveEax]
	mov [edi + X86SAVEREGS.SaveEax],eax
	popad
	ret
SyserPopad	ENDP

;VOID SyserCli(VOID);
SyserCli	PROC
	cli
	ret
SyserCli	ENDP

;VOID SyserSti(VOID);
SyserSti	PROC
	sti
	ret
SyserSti	ENDP

;VOID SyserHlt(VOID);
SyserHlt	PROC
	hlt
	ret
SyserHlt	ENDP

;VOID SyserCltr(VOID);
SyserCltr	PROC
	clts
	ret
SyserCltr	ENDP

;VOID SyserFnsave(PUCHAR	pState);
SyserFnsave	PROC pState
	push eax
	mov eax,pState
	fnsave byte ptr [eax]
	pop eax
	ret
SyserFnsave	ENDP

;VOID SyserFrstor(PUCHAR	pState);
SyserFrstor	PROC pState
	push eax
	mov eax,pState
	frstor byte ptr [eax]
	pop eax
	ret
SyserFrstor	ENDP

;VOID SyserFnstsw(PUSHORT	pState);
SyserFnstsw	PROC pState
	push eax
	push ebx
	mov ebx,pState
	xor eax,eax
	fnstsw ax
	mov word ptr[ebx],ax
	pop ebx
	pop eax
	ret
SyserFnstsw	ENDP

;VOID SyserFnstcw(PUSHORT	pControl);
SyserFnstcw	PROC pControl
	push eax
	push ebx
	mov ebx,pControl
	fnstcw word ptr [ebx]
	pop ebx
	pop eax
	ret
SyserFnstcw	ENDP

;VOID SyserFlushInsCache(BYTE*	AddPte);
SyserFlushInsCache	PROC	AddPte
	invlpg	AddPte
	push eax
	mov eax,cr3
	mov cr3,eax
	pop eax
	ret
SyserFlushInsCache	ENDP

;VOID SyserFlushProcessInsCache(VOID);
SyserFlushProcessInsCache	PROC
	push eax
	mov eax,cr3
	mov cr3,eax
	pop eax
	ret
SyserFlushProcessInsCache	ENDP

;DWORD SyserLar(DWORD	Selector);
SyserLar	PROC Selector
	push ebx
	mov ebx,Selector
	lar eax,ebx
	pop ebx
	ret
SyserLar	ENDP

;
;	SysDep.cpp
;

;ULONG64	SyserGetRdTsc(VOID);
SyserGetRdTsc	PROC
	rdtsc
	ret
SyserGetRdTsc	ENDP

;
;	X86Optr.cpp
;

;VOID  SyserCloseInterrupt(VOID);
SyserCloseInterrupt PROC
	cli
	ret
SyserCloseInterrupt ENDP

;VOID  SyserOpenInterrupt(VOID);
SyserOpenInterrupt PROC
	sti
	ret
SyserOpenInterrupt ENDP

;VOID  SyserSaveFlags(PULONG_PTR	_SaveFlags);
SyserSaveFlags PROC _SaveFlags
	push eax
	push ebx
	pushfd
	pop eax
	mov ebx,_SaveFlags
	mov [ebx],eax
	pop ebx
	pop eax	
	ret
SyserSaveFlags ENDP

;VOID  SyserRestoreFlags(ULONG_PTR	_Flags);
SyserRestoreFlags PROC _Flags
	push _Flags
	popfd
	ret
SyserRestoreFlags ENDP

;VOID  SyserCld(VOID);
SyserCld PROC
	cld
	ret
SyserCld ENDP

;VOID SyserGetCPUID(CPUID_INFO *pCPUInfo,DWORD dwIndex);
SyserGetCPUID PROC pCPUInfo,dwIndex
	pushad
	pushfd
	mov eax,dwIndex
	cpuid
	mov esi,pCPUInfo
	mov [esi],eax
	mov [esi+4],ebx
	mov [esi+8],ecx
	mov [esi+12],edx
	popfd
	popad
	ret
SyserGetCPUID ENDP

;DWORD SyserGetCPUIDMaxIndex();
SyserGetCPUIDMaxIndex PROC
	pushad
	pushfd
	mov eax,0
	cpuid
	mov [esp+32],eax
	popfd
	popad
	ret
SyserGetCPUIDMaxIndex ENDP

;bool SyserIsSupportCPUIDInstruction();
SyserIsSupportCPUIDInstruction PROC
	push ebp
	mov ebp,esp
	push ebx
	push ecx
	push edx
	movzx eax,bInit
	test eax,eax
	jnz @@3
	pushad
	pushfd
	mov eax,[esp]
	mov ebx,eax
	xor eax,200000h
	push eax
	popf
	pushf
	pop eax
	xor eax,ebx
	mov eax,0
	jz @@2
	cpuid
	cmp eax,1
	jnb @@1
	mov bHaveCPUIDInstruction,0
	jmp @@2
@@1:
	mov bHaveCPUIDInstruction,1
@@2:
	popfd
	popad
	mov bInit,1
@@3:
	xor eax,eax
	mov al,bHaveCPUIDInstruction
	pop edx
	pop ecx
	pop ebx
	leave
	ret
SyserIsSupportCPUIDInstruction ENDP

;__int64 __stdcall SyserPrivateReadMSR(DWORD dwIndex);
SyserPrivateReadMSR PROC dwIndex
	mov ecx,dwIndex
	rdmsr
	clc
	ret 4
SyserPrivateReadMSR ENDP

;__int64 __stdcall SyserPrivateReadMSRError();
SyserPrivateReadMSRError PROC
	stc
	ret 4
SyserPrivateReadMSRError ENDP

;VOID __stdcall SyserPrivateWriteMSR(DWORD dwIndex,DWORD dwValueLow,DWORD dwValueHigh);
SyserPrivateWriteMSR PROC dwIndex,dwValueLow,dwValueHigh
	mov ecx,dwIndex
	mov eax,dwValueLow
	mov edx,dwValueHigh
	wrmsr
	clc
	ret
SyserPrivateWriteMSR ENDP

;VOID __stdcall SyserPrivateWriteMSRError(VOID);
SyserPrivateWriteMSRError PROC
	stc
	ret 0Ch
SyserPrivateWriteMSRError ENDP

;bool SyserReadMSR(DWORD dwIndex,DWORD *dwHigh,DWORD *dwLow);
SyserReadMSR PROC dwIndex,dwHigh,dwLow
	local dwRetValue:DWORD
	mov dwRetValue,0
	call SyserIsSupportRDMSRInstruction
	movzx eax, al
	test eax,eax
	jz @@2
	pushad
	invoke SyserPrivateReadMSR,dwIndex
	jb @@1
	mov dwRetValue,1
	push ecx
	mov ecx,dwHigh
	mov [ecx],edx
	mov ecx,dwLow
	mov [ecx],eax
	pop ecx
@@1:
	popad
@@2:
	xor eax,eax
	cmp dwRetValue,1
	setz al
	ret
SyserReadMSR ENDP

;__int64 __stdcall SyserPrivateGetTSC();
SyserPrivateGetTSC PROC
	rdtsc
	clc
	ret
SyserPrivateGetTSC ENDP

;__int64 __stdcall SyserPrivateGetTSCError();
SyserPrivateGetTSCError PROC
	stc
	ret
SyserPrivateGetTSCError ENDP

;ULONGLONG SyserGetTSC();
SyserGetTSC PROC
	invoke SyserPrivateGetTSC
	ret
SyserGetTSC ENDP

;bool SyserWriteMSR(DWORD dwIndex,DWORD dwHigh,DWORD dwLow);
SyserWriteMSR PROC dwIndex,dwHigh,dwLow
	local dwRetValue:DWORD
	mov dwRetValue,0
	;稍后需要把注释去掉call IsSupportRDMSRInstruction
	movzx eax, al
	test eax,eax
	jz @@1
	pushad
	invoke SyserPrivateWriteMSR,dwIndex,dwHigh,dwLow
	movzx eax,al
	mov dwRetValue,eax
	popad
@@1:
	xor eax,eax
	cmp dwRetValue,1
	setz al
	ret
SyserWriteMSR ENDP

;DWORD SyserGetTSSSelector();
SyserGetTSSSelector PROC
	xor eax,eax
	str ax
	ret
SyserGetTSSSelector	ENDP

;DWORD SyserGetLDTSelector();
SyserGetLDTSelector	PROC
	xor eax,eax
	sldt ax
	ret
SyserGetLDTSelector ENDP

;VADDR32 SyserGetIDTBase(DWORD *dwIdtSize);
SyserGetIDTBase PROC dwIdtSize
	local SIDTBffer:QWORD
	local vIDTBase:DWORD
	push esi
	push ebx
	lea esi,SIDTBffer
	sidt [esi]
	mov eax,[esi+2]
	mov vIDTBase,eax
	mov eax,dwIdtSize
	test eax,eax
	jz @@1
	mov bx,[esi]
	movzx ebx,bx
	mov [eax],ebx
@@1:
	mov eax,vIDTBase
	pop ebx
	pop esi
	ret
SyserGetIDTBase ENDP

;VADDR32 SyserGetGDTBase(DWORD *dwGdtSize);
SyserGetGDTBase	PROC dwGdtSize
	local dwSize:DWORD
	local GDTInfo:QWORD
	push esi
	push edi
	lea esi,GDTInfo
	sgdt [esi]
	mov edi,dwGdtSize
	test edi,edi
	jz @@1
	movzx eax,word ptr[esi]
	mov [edi],eax
@@1:
	mov eax,[esi+2]
	pop edi
	pop esi
	ret
SyserGetGDTBase ENDP

;SELECTOR SyserGetCurCSeg();
SyserGetCurCSeg	PROC
	xor eax,eax
	mov ax,cs
	ret
SyserGetCurCSeg	ENDP

;SELECTOR SyserGetCurDSeg();
SyserGetCurDSeg	PROC
	xor eax,eax
	mov ax,ds
	ret
SyserGetCurDSeg	ENDP

;SELECTOR SyserGetCurFSeg();
SyserGetCurFSeg	PROC
	xor eax,eax
	mov ax,fs
	ret
SyserGetCurFSeg	ENDP

;REG32 SyserGetCR0Reg();
SyserGetCR0Reg	PROC
	mov eax,cr0
	ret
SyserGetCR0Reg	ENDP

;VOID SyserSetCR0Reg(IN REG32 uReg);
SyserSetCR0Reg	PROC uReg
	push eax
	mov eax,uReg
	mov cr0,eax
	pop eax
	ret
SyserSetCR0Reg	ENDP

;REG32 SyserGetCR3Reg();
SyserGetCR3Reg	PROC
	mov eax,cr3
	ret
SyserGetCR3Reg	ENDP

;VOID SyserSetCR3Reg(IN REG32 uReg);
SyserSetCR3Reg	PROC uReg
	push eax
	mov eax,uReg
	mov cr3,eax
	pop eax
	ret
SyserSetCR3Reg	ENDP

;REG32 SyserGetCR4Reg();
SyserGetCR4Reg	PROC
	mov eax,cr4
	ret
SyserGetCR4Reg	ENDP

;VOID SyserSetCR4Reg(IN REG32 uReg);
SyserSetCR4Reg	PROC uReg
	push eax
	mov eax,uReg
	mov cr4,eax
	pop eax
	ret
SyserSetCR4Reg	ENDP

;VOID SyserClrCR0WP()
SyserClrCR0WP	PROC
	push eax
	mov eax,CR0Backup
	and eax,080000000h
	jz @@1
	mov eax,cr0
	and eax,0FFFEFFFFh
	mov cr0,eax
	pop eax
	ret
@@1:
	mov eax,cr0
	mov CR0Backup,eax
	and eax,0FFFEFFFFh
	mov cr0,eax
	pop eax
	ret
SyserClrCR0WP	ENDP

;VOID SyserSetCR0WP();
SyserSetCR0WP	PROC
	push eax
	mov eax,cr0
	mov CR0Backup,eax
	or eax,10000h
	mov cr0,eax
	pop eax
	ret
SyserSetCR0WP	ENDP

;VOID SyserRestoreCR0();
SyserRestoreCR0	PROC
	push eax
	mov eax,CR0Backup
	and eax,080000000h
	jz @@1
	mov eax,CR0Backup
	mov cr0,eax
	xor eax,eax
	mov CR0Backup,eax	
@@1:
	pop eax
	ret
SyserRestoreCR0	ENDP

;DWORD SyserClearCR0WP();
SyserClearCR0WP	PROC
	mov eax,cr0
	push eax
	and eax,0FFFEFFFFh
	mov cr0,eax
	pop eax
	ret
SyserClearCR0WP	ENDP

;VOID SyserRestoreCR0WP(DWORD dwCR0);
SyserRestoreCR0WP	PROC dwCR0
	push eax
	mov eax,dwCR0
	mov cr0,eax
	pop eax
	ret
SyserRestoreCR0WP	ENDP

;REG32 SyserGetDRX(IN UINT ID);
SyserGetDRX	PROC ID
	pushfd
	push ecx
	mov ecx,@@1
	mov eax,ID
	shl eax,2
	add eax,ecx
	mov eax,[eax]
	pop ecx
	popfd
	jmp eax
@@1:
	dd @@2
	dd @@3
	dd @@4
	dd @@5
	dd @@1
	dd @@1
	dd @@6
	dd @@7
@@2:
	mov eax,dr0
	ret
@@3:
	mov eax,dr1
	ret
@@4:
	mov eax,dr2
	ret
@@5:
	mov eax,dr3
	ret
@@6:
	mov eax,dr6
	ret
@@7:
	mov eax,dr7
	ret
SyserGetDRX ENDP

;VOID SyserSetDRX(IN UINT ID,IN REG32 Reg1);
SyserSetDRX	PROC ID,Reg1
	push eax
	pushfd
	push ecx
	mov ecx,@@1
	mov eax,ID
	shl eax,2
	add eax,ecx
	mov eax,[eax]
	pop ecx
	popfd
	jmp eax
@@1:
	dd @@2
	dd @@3
	dd @@4
	dd @@5
	dd @@1
	dd @@1
	dd @@6
	dd @@7
@@2:
	mov eax,Reg1
	mov dr0,eax
	pop eax
	ret
@@3:
	mov eax,Reg1
	mov dr1,eax
	pop eax
	ret
@@4:
	mov eax,Reg1
	mov dr2,eax
	pop eax
	ret
@@5:
	mov eax,Reg1
	mov dr3,eax
	pop eax
	ret
@@6:
	mov eax,Reg1
	mov dr6,eax
	pop eax
	ret
@@7:
	mov eax,Reg1
	mov dr7,eax
	pop eax
	ret
SyserSetDRX	ENDP

;BYTE SyserReadPortByte(DWORD wPort);
SyserReadPortByte	PROC wPort
	push edx
	mov edx,wPort
	in al,dx
	movzx eax,al
	pop edx
	ret
SyserReadPortByte	ENDP

;WORD SyserReadPortWord(DWORD wPort);
SyserReadPortWord	PROC wPort
	push edx
	mov edx,wPort
	in ax,dx
	movzx eax,ax
	pop edx
	ret
SyserReadPortWord	ENDP

;DWORD SyserReadPortDword(DWORD wPort);
SyserReadPortDword	PROC wPort
	push edx
	mov edx,wPort
	in eax,dx
	pop edx
	ret
SyserReadPortDword	ENDP

;VOID SyserWritePortDword(DWORD dwPort, DWORD dwValue);
SyserWritePortDword	PROC dwPort,dwValue
	push eax
	push edx
	mov edx,dwPort
	mov eax,dwValue
	out dx,eax
	pop edx
	pop eax
	ret
SyserWritePortDword	ENDP

;VOID SyserWritePortWord(DWORD dwPort, WORD wValue);
SyserWritePortWord	PROC dwPort,wValue
	push eax
	push edx
	mov edx,dwPort
	mov ax,word ptr wValue
	out dx,ax
	pop edx
	pop eax
	ret
SyserWritePortWord	ENDP

;VOID SyserWritePortByte(DWORD dwPort, BYTE byteValue);
SyserWritePortByte	PROC dwPort,byteValue
	push eax
	push edx
	mov edx,dwPort
	mov al,byte ptr byteValue
	out dx,al
	pop edx
	pop eax
	ret
SyserWritePortByte	ENDP

;bool SyserIsSupportRDMSRInstruction();
SyserIsSupportRDMSRInstruction	PROC
	xor eax,eax
	mov al,bInitIsSupportRDMSRInstruction
	test eax,eax
	jnz @@3
	xor eax,eax
	invoke SyserIsSupportCPUIDInstruction
	test eax,eax
	jz @@2
	pushad
	mov eax,1
	cpuid
	test edx,020h
	mov bHaveReadWriteMSRInstruction,0
	jz @@1
	mov bHaveReadWriteMSRInstruction,1
@@1:
	popad
	mov bInitIsSupportRDMSRInstruction,1
	jmp @@1
@@2:
	mov bHaveReadWriteMSRInstruction,0
@@3:
	xor eax,eax
	mov al,bHaveReadWriteMSRInstruction
	ret
SyserIsSupportRDMSRInstruction	ENDP

;void* SyserMemoryCopy(void *dst, const void*src,int count);
SyserMemoryCopy	PROC dst,src,count
	pushad
	pushfd
	cld
	mov esi,src
	mov edi,dst
	mov ecx,count
	mov eax,esi
	and eax,3
	jz @@2
@@1:
	jecxz @@3
	movsb
	dec ecx
	dec eax
	jnz @@1
@@2:
	jecxz @@3
	mov eax,ecx
	shr eax,2
	rep movsd
	and eax,3
	mov ecx,eax
	rep movsb
@@3:
	popfd
	popad
	mov eax,dst
	ret
SyserMemoryCopy	ENDP

;
;
;

;VOID	SyserGetLDTSelectorBySelector(DWORD* dwLdtSelector,DWORD* dwSize);
;这个需要好好调试下
SyserGetLDTSelectorBySelector	PROC dwLdtSelector,dwSize
	pushfd
	push eax
	push esi
	cmp dwLdtSelector,0
	jz @@2
	cmp dwSize,0
	jz @@2
	mov esi,dwLdtSelector
	mov eax,[esi]
	test eax,eax
	jnz @@1
	sldt ax
	mov [esi],eax
@@1:
	lsl eax,eax
	jnz @@2
	mov esi,dwSize
	mov [esi],eax
@@2:
	pop esi
	pop eax
	popfd
	ret
SyserGetLDTSelectorBySelector	ENDP

;DWORD	SyserGetSegmentLimit(WORD SegmentSelector);
SyserGetSegmentLimit	PROC SegmentSelector
	movzx eax,word ptr SegmentSelector
	lsl eax,eax
	jz @@1
	xor eax,eax
@@1:
	ret
SyserGetSegmentLimit	ENDP

;VOID SyserX86FxSave(BYTE *RegisterBuffer);
SyserX86FxSave	PROC RegisterBuffer
	push eax
	mov eax,RegisterBuffer
	fxsave dword ptr[eax]
	pop eax
	ret
SyserX86FxSave	ENDP

;bool SyserGetFpuErrorState();
SyserGetFpuErrorState	PROC
	local dwError:DWORD
	local dwMxcsr:DWORD
	pushfd
	push eax
	push ebx
	mov dwError,0
	mov dwMxcsr,0
	clts
	stmxcsr dwMxcsr
	mov eax,dwMxcsr
	mov ebx,eax 
	shr ebx,7 
	and eax,03fh 
	and ebx,03fh 
	and bl,al 
	not bl 
	test bl,al 
	mov dwError,0
	jz @@1
	mov dwError,1
@@1:
	pop ebx
	pop eax
	popfd
	xor eax,eax
	cmp dwError,1
	setz al
	ret
SyserGetFpuErrorState	ENDP

;VOID SyserInitSystemSegmentRegister(VOID);
SyserInitSystemSegmentRegister	PROC
	push eax
	xor eax,eax
	mov ax,fs
	mov gSystemFSRegisterSelector,eax
	mov ax,ss 
	mov gSystemSSRegisterSelector,eax 
	mov ax,cs 
	mov gSystemCSRegisterSelector,eax
	mov ax,ds 
	mov gSystemDSRegisterSelector,eax
	pop eax
	ret
SyserInitSystemSegmentRegister	ENDP

;
;	InputDriver.cpp
;

;VOID SyserWaitKeyboardOutPutBufferFull(VOID);
SyserWaitKeyboardOutPutBufferFull	PROC
	push ecx
	push eax
	mov ecx,02000h
@@1:
	in al,064h
	push ecx
	mov ecx,014h
@@2:
	loop @@2
	pop ecx
	test al,1
	loope @@1
	pop eax
	pop ecx
	ret
SyserWaitKeyboardOutPutBufferFull	ENDP

;VOID SyserWaitKeyboardInputBufferEmpte(VOID);
SyserWaitKeyboardInputBufferEmpte	PROC
	push ecx
	push eax
	mov ecx,02000h
@@1:
	in al,064h
	push ecx
	mov ecx,014h
@@2:
	loop @@2
	pop ecx
	test al,2
	loopne @@1
	pop eax
	pop ecx
	ret
SyserWaitKeyboardInputBufferEmpte	ENDP

;VOID SyserSimulateKeyboardInput(BYTE scancode,bool isDisableInterrupt);
SyserSimulateKeyboardInput	PROC scancode,isDisableInterrupt
	local dwIsInterrupt:DWORD
	cmp isDisableInterrupt,0
	jz @@1
	mov dwIsInterrupt,0
@@1:
	pushad
	xor eax,eax
	mov ah,BYTE PTR scancode
;	and eax,0ffh
;	shl eax,8
	mov edx,dwIsInterrupt
	cmp edx,0
	jz @@6
	mov al,020		;读键盘命令字 的命令
	out 064h,al
	push ecx
	mov ecx,014h
@@2:
	loop @@2
	pop ecx
	call SyserWaitKeyboardOutPutBufferFull
	in al, 060h		;读书键盘命令字
	push ecx
	mov ecx, 014h
@@3:
	loop @@3
	pop ecx
	call SyserWaitKeyboardInputBufferEmpte
	mov al,060h		;写键盘命令字 的命令
	out 064h,al
	push ecx
	mov ecx, 014h
@@4:
	loop @@4
	pop ecx
	call SyserWaitKeyboardInputBufferEmpte
	mov al,cl
	and al,0feh		;禁止键盘产生中断  
	out 060h,al
	push ecx
	mov ecx, 014h
@@5:
	loop @@5
	pop ecx
@@6:		
	call SyserWaitKeyboardInputBufferEmpte
	mov al, 0d2h	;写键盘输出缓冲区 命令
	out 064h,al
	push ecx
	mov ecx, 014h
@@7:
	loop @@7
	pop ecx
	call SyserWaitKeyboardInputBufferEmpte
	mov al,ah
	out 060h,al		;写入扫描码
	push ecx
	mov ecx, 014h
@@8:
	loop @@8
	pop ecx
	call SyserWaitKeyboardOutPutBufferFull
	or dl,dl
	jz @@11
	call SyserWaitKeyboardInputBufferEmpte
	mov al,060h
	out 064h,al
	push ecx
	mov ecx, 014h
@@9:
	loop @@9
	pop ecx
	call SyserWaitKeyboardInputBufferEmpte
	mov al,cl
	or al,1
	out 060h,al
	push ecx
	mov ecx, 014h
@@10:
	loop @@10
	pop ecx
	call SyserWaitKeyboardInputBufferEmpte
@@11:		
	popad		
	ret
SyserSimulateKeyboardInput	ENDP

;VOID SyserInterrupt_0xF8_Keyboard_Service(VOID);
SyserInterrupt_0xF8_Keyboard_Service	PROC
	pushfd
	cmp gbActive,0
	jnz @@1
	push eax
	in al,064h
	test al,1
	pop eax
	jnz @@1
	popfd
	ret
@@1:
	popfd
	;push KeyboardInterruptService
	ret
SyserInterrupt_0xF8_Keyboard_Service	ENDP

;VOID	SyserWaitMouseStatus(VOID);
SyserWaitMouseStatus	PROC
	push eax
	in al,064h
	test al,1
	jz @@1
	in al,060h
@@1:
	pop eax
	ret
SyserWaitMouseStatus	ENDP

;VOID SyserWaitMouseInputBufferEmpte(VOID);
SyserWaitMouseInputBufferEmpte	PROC
	push eax
	push ecx
	mov ecx,2
@@1:
	push ecx
	xor ecx,ecx
@@2:
	in al,064h
	test al,2
	loopne @@2
	pop ecx
	jz @@3
	loop @@1
@@3:
	pop ecx
	pop eax
	ret
SyserWaitMouseInputBufferEmpte	ENDP

;VOID SyserWaitMouseOutPutBufferFull(VOID);
SyserWaitMouseOutPutBufferFull	PROC
	push ecx
	push eax
	mov ecx,02000h
@@1:
	in al,064h
	and al,021h
	cmp al,021h
	loopne @@1
	pop eax
	pop ecx
	ret
SyserWaitMouseOutPutBufferFull	ENDP

;VOID SyserCleanMouseOutPutBuffer(VOID);
SyserCleanMouseOutPutBuffer	PROC
	push eax
	push ecx
	mov ecx,01000h
	in al,064h
	test al,021h
	jz	@@2 
	in al,060h
@@1:
	loop @@1
@@2:
	pop ecx
	pop eax
	ret
SyserCleanMouseOutPutBuffer	ENDP

;bool SyserIsMouseOutPutBufferFull(VOID);
SyserIsMouseOutPutBufferFull	PROC
	in al,064h
	test al,021h
	cmp al,021h
	jnz @@1
	mov eax,1
	jmp @@2
@@1:
	xor eax,eax
@@2:
	ret
SyserIsMouseOutPutBufferFull	ENDP

;VOID SyserWriteMouseCommandByte(BYTE chCmd);
SyserWriteMouseCommandByte	PROC chCmd
	push eax
	xor eax,eax
	call SyserIsMouseOutPutBufferFull
	test eax,eax
	jz @@1
	call SyserCleanMouseOutPutBuffer
@@1:
	mov al,byte ptr chCmd
	out 060h,al
	pop eax
	ret
SyserWriteMouseCommandByte	ENDP

;BYTE SyserReadMouseByte(VOID);
SyserReadMouseByte	PROC
	call SyserWaitMouseOutPutBufferFull
	xor eax,eax
	in al,060h
	ret
SyserReadMouseByte	ENDP

;VOID SyserGetPortState(VOID)//在给键盘发送了命令以后该函数用来读取键盘的返回值
SyserGetPortState	PROC
	push eax
	push ecx
	mov ecx,01000h
@@1:
	in al,064h
	push ecx
	mov ecx,8
@@2:
	jmp @@3
@@3:
	loop @@2
	pop ecx
	test al,1
	loope @@1
	jz @@4
	in al,060h
	cmp al,0fah
	jnz @@1
@@4:
	pop ecx
	pop eax
	ret
SyserGetPortState	ENDP

;VOID SyserSimulateWindowsKeyboardInput(BYTE byteScanCode);
SyserSimulateWindowsKeyboardInput	PROC byteScanCode
	local Flags:DWORD
	push eax
	lea eax,byteScanCode
	push eax
	call InsertKeyboardBuffer
	lea eax,Flags
	call SyserSaveFlags
	cli
	pushfd
	push cs
	push @@1
	jmp dword ptr cs:stKeyGlobalVariable.dwOldKeyboardInterrupt
@@1:
	invoke SyserRestoreFlags,Flags
	pop eax
	ret
SyserSimulateWindowsKeyboardInput	ENDP

;VOID SyserSyncMouseInterrupt(VOID);
SyserSyncMouseInterrupt	PROC
	push eax
	push ecx
	mov ax,010h
	mov ds,ax
	mov ecx,088000h				;有足够的时间来等待鼠标中断的发生，在最坏的情况下要等待 3 个鼠标中断
	mov eax,dwMousePackageBeginOffset
	cmp eax,stKeyGlobalVariable.dwMouseDataIndex
	jz @@2
	mov dwWaitMouseInterrupt,1
	sti
@@1:
	cmp eax,stKeyGlobalVariable.dwMouseDataIndex
	loopne @@1
	cli
@@2:
	mov gbActive,0
	pop ds
	pop ecx
	pop eax
	ret
SyserSyncMouseInterrupt	ENDP

;bool SyserReadPort60(BYTE* ReturnValue,bool IsMouse);
SyserReadPort60	PROC ReturnValue,IsMouse
	local bRet:BYTE
	local Value:BYTE
	push ecx
	push ebx
	mov bl,1
	cmp IsMouse,0
	jz @@1
	or bl,020h
@@1:
	mov ecx,0800000h
@@2:
	in al,064h
	and al,bl
	cmp al,bl
	jz @@3
	loop @@2
	jmp @@4
@@3:
	mov bRet,1
	in al,060h
	mov Value,al
@@4:
	cmp ReturnValue,0
	jz	@@5
	mov ebx,ReturnValue
	xor eax,eax
	mov al,byte ptr Value
	mov [ebx],al
@@5:
	xor eax,eax
	mov al,byte ptr bRet
	pop ebx
	pop ecx
	ret
SyserReadPort60	ENDP

;bool SyserWaitI8042InputBufferEmpty(VOID);
SyserWaitI8042InputBufferEmpty	PROC
	local bRet:BYTE
	mov bRet,0
	push ecx
	mov ecx,080000h
@@1:
	in al,064h
	test al,2
	jz @@2
	loop @@1
	jmp @@7
@@2:
	push ecx
	mov ecx,100
@@3:
	jmp @@4
@@4:
	loop @@3
	pop ecx
@@5:
	in al,064h
	test al,2
	jz @@6
	loop @@5
	jmp @@7
@@6:
	mov bRet,1
@@7:
	pop ecx
	xor eax,eax
	mov al,byte ptr bRet
	ret
SyserWaitI8042InputBufferEmpty	ENDP

;bool SyserClearI8042OutputBuffer(VOID);
SyserClearI8042OutputBuffer	PROC
	local bRet:BYTE
	mov bRet,0
	push ecx
	xor ecx,ecx
@@1:
	in al,064h
	test al,1
	jz @@4
	in al,060h
	mov eax,020h
@@2:
	jmp @@3
@@3:
	dec eax
	jnz @@2
	loop @@1
	jmp @@5
@@4:
	mov bRet,1
@@5:	
	pop ecx
	xor eax,eax
	mov al,byte ptr bRet
	ret
SyserClearI8042OutputBuffer	ENDP

;
;	DbgProcess.cpp
;
;VOID	SyserClearFlag(WORD	vEs,PDWORD	Value,DWORD	ClearFlag);
SyserClearFlag	PROC vEs,Value,ClearFlag
	push es
	push eax
	push ebx
	push ecx
	mov ecx,0FFFFFFFFh
	xor ecx,ClearFlag
	mov ebx,Value
    mov ax,word ptr vEs
    mov es,ax
    and es:[ebx],ecx
	pop ecx
	pop ebx
	pop eax
	pop es
	ret
SyserClearFlag	ENDP

;VOID SyserBpintEntryPointer(VOID);
SyserBpintEntryPointer	PROC

	;
	;	0
	;
	
	push 0
	jmp $
	push 0
	jmp $
	push 0
	jmp $
	push 0
	jmp $
	push 0
	jmp $
	push 0
	jmp $
	push 0
	jmp $
	push 0
	jmp $
	push 0
	jmp $
	push 0
	jmp $
	push 0
	jmp $
	push 0
	jmp $
	push 0
	jmp $
	push 0
	jmp $
	push 0
	jmp $
	push 0
	jmp $
	
	;
	;	1
	;
	
	push 0
	jmp $
	push 0
	jmp $
	push 0
	jmp $
	push 0
	jmp $
	push 0
	jmp $
	push 0
	jmp $
	push 0
	jmp $
	push 0
	jmp $
	push 0
	jmp $
	push 0
	jmp $
	push 0
	jmp $
	push 0
	jmp $
	push 0
	jmp $
	push 0
	jmp $
	push 0
	jmp $
	push 0
	jmp $
	
	;
	;	2
	;
	
	push 0
	jmp $
	push 0
	jmp $
	push 0
	jmp $
	push 0
	jmp $
	push 0
	jmp $
	push 0
	jmp $
	push 0
	jmp $
	push 0
	jmp $
	push 0
	jmp $
	push 0
	jmp $
	push 0
	jmp $
	push 0
	jmp $
	push 0
	jmp $
	push 0
	jmp $
	push 0
	jmp $
	push 0
	jmp $
	
	;
	;	3
	;
	
	push 0
	jmp $
	push 0
	jmp $
	push 0
	jmp $
	push 0
	jmp $
	push 0
	jmp $
	push 0
	jmp $
	push 0
	jmp $
	push 0
	jmp $
	push 0
	jmp $
	push 0
	jmp $
	push 0
	jmp $
	push 0
	jmp $
	push 0
	jmp $
	push 0
	jmp $
	push 0
	jmp $
	push 0
	jmp $
	
	;
	;	4
	;
	
	push 0
	jmp $
	push 0
	jmp $
	push 0
	jmp $
	push 0
	jmp $
	push 0
	jmp $
	push 0
	jmp $
	push 0
	jmp $
	push 0
	jmp $
	push 0
	jmp $
	push 0
	jmp $
	push 0
	jmp $
	push 0
	jmp $
	push 0
	jmp $
	push 0
	jmp $
	push 0
	jmp $
	push 0
	jmp $
	
	;
	;	5
	;
	
	push 0
	jmp $
	push 0
	jmp $
	push 0
	jmp $
	push 0
	jmp $
	push 0
	jmp $
	push 0
	jmp $
	push 0
	jmp $
	push 0
	jmp $
	push 0
	jmp $
	push 0
	jmp $
	push 0
	jmp $
	push 0
	jmp $
	push 0
	jmp $
	push 0
	jmp $
	push 0
	jmp $
	push 0
	jmp $
	
	;
	;	6
	;
	
	push 0
	jmp $
	push 0
	jmp $
	push 0
	jmp $
	push 0
	jmp $
	push 0
	jmp $
	push 0
	jmp $
	push 0
	jmp $
	push 0
	jmp $
	push 0
	jmp $
	push 0
	jmp $
	push 0
	jmp $
	push 0
	jmp $
	push 0
	jmp $
	push 0
	jmp $
	push 0
	jmp $
	push 0
	jmp $
	
	;
	;	7
	;
	
	push 0
	jmp $
	push 0
	jmp $
	push 0
	jmp $
	push 0
	jmp $
	push 0
	jmp $
	push 0
	jmp $
	push 0
	jmp $
	push 0
	jmp $
	push 0
	jmp $
	push 0
	jmp $
	push 0
	jmp $
	push 0
	jmp $
	push 0
	jmp $
	push 0
	jmp $
	push 0
	jmp $
	push 0
	jmp $
	
	;
	;	8
	;
	
	push 0
	jmp $
	push 0
	jmp $
	push 0
	jmp $
	push 0
	jmp $
	push 0
	jmp $
	push 0
	jmp $
	push 0
	jmp $
	push 0
	jmp $
	push 0
	jmp $
	push 0
	jmp $
	push 0
	jmp $
	push 0
	jmp $
	push 0
	jmp $
	push 0
	jmp $
	push 0
	jmp $
	push 0
	jmp $
	
	;
	;	9
	;
	
	push 0
	jmp $
	push 0
	jmp $
	push 0
	jmp $
	push 0
	jmp $
	push 0
	jmp $
	push 0
	jmp $
	push 0
	jmp $
	push 0
	jmp $
	push 0
	jmp $
	push 0
	jmp $
	push 0
	jmp $
	push 0
	jmp $
	push 0
	jmp $
	push 0
	jmp $
	push 0
	jmp $
	push 0
	jmp $
	
	;
	;	a
	;
	
	push 0
	jmp $
	push 0
	jmp $
	push 0
	jmp $
	push 0
	jmp $
	push 0
	jmp $
	push 0
	jmp $
	push 0
	jmp $
	push 0
	jmp $
	push 0
	jmp $
	push 0
	jmp $
	push 0
	jmp $
	push 0
	jmp $
	push 0
	jmp $
	push 0
	jmp $
	push 0
	jmp $
	push 0
	jmp $
	
	;
	;	b
	;
	
	push 0
	jmp $
	push 0
	jmp $
	push 0
	jmp $
	push 0
	jmp $
	push 0
	jmp $
	push 0
	jmp $
	push 0
	jmp $
	push 0
	jmp $
	push 0
	jmp $
	push 0
	jmp $
	push 0
	jmp $
	push 0
	jmp $
	push 0
	jmp $
	push 0
	jmp $
	push 0
	jmp $
	push 0
	jmp $
	
	;
	;	c
	;
	
	push 0
	jmp $
	push 0
	jmp $
	push 0
	jmp $
	push 0
	jmp $
	push 0
	jmp $
	push 0
	jmp $
	push 0
	jmp $
	push 0
	jmp $
	push 0
	jmp $
	push 0
	jmp $
	push 0
	jmp $
	push 0
	jmp $
	push 0
	jmp $
	push 0
	jmp $
	push 0
	jmp $
	push 0
	jmp $
	
	;
	;	d
	;
	
	push 0
	jmp $
	push 0
	jmp $
	push 0
	jmp $
	push 0
	jmp $
	push 0
	jmp $
	push 0
	jmp $
	push 0
	jmp $
	push 0
	jmp $
	push 0
	jmp $
	push 0
	jmp $
	push 0
	jmp $
	push 0
	jmp $
	push 0
	jmp $
	push 0
	jmp $
	push 0
	jmp $
	push 0
	jmp $
	
	;
	;	e
	;
	
	push 0
	jmp $
	push 0
	jmp $
	push 0
	jmp $
	push 0
	jmp $
	push 0
	jmp $
	push 0
	jmp $
	push 0
	jmp $
	push 0
	jmp $
	push 0
	jmp $
	push 0
	jmp $
	push 0
	jmp $
	push 0
	jmp $
	push 0
	jmp $
	push 0
	jmp $
	push 0
	jmp $
	push 0
	jmp $
	
	;
	;	f
	;
	
	push 0
	jmp $
	push 0
	jmp $
	push 0
	jmp $
	push 0
	jmp $
	push 0
	jmp $
	push 0
	jmp $
	push 0
	jmp $
	push 0
	jmp $
	push 0
	jmp $
	push 0
	jmp $
	push 0
	jmp $
	push 0
	jmp $
	push 0
	jmp $
	push 0
	jmp $
	push 0
	jmp $
	push 0
	jmp $
SyserBpintEntryPointer	ENDP

;VOID SyserBpintBreakEntry(VOID)
SyserBpintBreakEntry	PROC
SyserBpintBreakEntry	ENDP

;
;	MultiCPU.cpp
;

;VOID  SyserStartOtherCPUs(VOID);
SyserStartOtherCPUs	PROC
	pushfd
	cmp cs:gCPUNumbers,1
	jbe @@3
	push eax
	push ds
	mov eax,cs:gSystemSSRegisterSelector
	mov ds,ax
	cmp dword ptr gLoopCpuNumber,0    ;gLoopCpuNumber 这个变量是用来判断是否有进入死循环的 cpu 
	jz @@2
	lock inc gdwExitNmiLock
	mov gdwMulitCpuSpinlock,0
	mov gdwCurrentCPUIndex,0FFFFFFFFh
@@1:
	cmp gdwExitNmiLock,0
	jnz @@1
@@2:
	pop ds
	pop eax
@@3:
	popfd
	ret
SyserStartOtherCPUs	ENDP

;VOID SyserStopOtherCPUs(VOID);
SyserStopOtherCPUs	PROC
	local TmpCurrentCPUIndex:DWORD
	pushfd
	cmp cs:gCPUNumbers,1
	jnz @@1
	popfd
	ret
@@1:
	pushad
	push ds
	mov eax,cs:gSystemSSRegisterSelector
	mov ds,ax
	mov ebp,esp
	sub esp,4
	call GetCurrentCPULocalAPICID
	mov TmpCurrentCPUIndex,eax
@@20:
	lock bts gdwMulitCpuSpinlock,01fh	;如果同时有多个CPU执行这个指令，则只有一个CPU能获得改锁，
	jnb @@3
	mov ecx,0100h
@@2:
	loop @@2
	mov eax,TmpCurrentCPUIndex
	cmp eax,gdwCurrentCPUIndex
	jnz @@6
	inc gdwMulitCpuSpinlock				;如果当前的CPU已经停止了其他CPU 则只增加锁的计数后直接退出
	jmp @@Quit
@@6:
	invoke Beep,10,10
	cmp gdwMulitCpuSpinlock,0			;如果是其他CPU保持这个锁 则等待其他CPU释放掉这个锁   
	jnz @@6
	jmp @@20
@@3:
	mov gdwCurrentCPUIndex,eax
	inc gdwMulitCpuSpinlock		
	mov eax, gdwLocalAPICLineAddress
@@9:
	test DWORD PTR [eax+0300h],01000h   ;Delivery Mode  判断时候有 Send Pending
	jnz @@9
	mov ebx,0c44ffh						;NMI 物理模式 EDGE  高电平出发  All Excluding Self
	mov gdwMulitCpuSendIPIFlags,1
	mov [eax+0300h],ebx
@@11:
	test DWORD PTR [eax+0300h],01000h   ;等待中断被处理
	jnz @@11
@@12:
	cmp gdwMulitCpuSendIPIFlags,0		;等待其他CPU进入死循环
	jnz @@12
@@Quit:
	add esp,4
	pop ds
	popad
	popfd
	ret
SyserStopOtherCPUs	ENDP

;
;	IOAPIC.cpp
;

;VOID	SyserGetApicInfo(DWORD	*RdmsrEax,DWORD *RdmsrEdx);
SyserGetApicInfo	PROC	RdmsrEax,RdmsrEdx
	pushfd
	push eax
	push ecx
	push edx
	mov ecx,MSR_INDEX_IA32_APIC_BASE
	rdmsr
	mov ecx,RdmsrEax
	mov [ecx],eax
	mov ecx,RdmsrEdx
	mov [ecx],edx
	pop edx
	pop ecx
	pop eax
	popfd
	ret
SyserGetApicInfo	ENDP

;DWORD	SyserGetIOAPICData(DWORD*  IoApicLineAddress, DWORD	Index);
SyserGetIOAPICData	PROC	IoApicLineAddress,Index
	local dwValue:DWORD
	pushfd
	pushad
	mov eax,IoApicLineAddress
	mov ebx,Index
	cli
	mov [eax],ebx
	mov eax,[eax+010h]
	mov dwValue,eax
	popad
	popfd
	mov eax,dwValue
	ret
SyserGetIOAPICData	ENDP

;DWORD	SyserSetIOAPICData(DWORD*  IoApicLineAddress, DWORD	Index,DWORD	Data);
SyserSetIOAPICData	PROC	IoApicLineAddress,Index,Data
	pushfd
	pushad
	mov eax,IoApicLineAddress
	mov ebx,Index
	mov ecx,Data
	cli
	mov [eax],ebx
	mov [eax+010h],ecx
	popad
	popfd
	ret
SyserSetIOAPICData	ENDP

;VOID	SyserIOAPICBeep(VOID);
SyserIOAPICBeep	PROC
	push eax
	in al,064h
	test al,1
	jz @@Quit
	in al,060h
	push 0100h
	push 0100h
	call Beep
@@Quit:
	pop eax
	ret
SyserIOAPICBeep	ENDP

;
;	NTUtility.cpp
;	

;VOID SyserResetSystem(VOID);
SyserResetSystem	PROC
	in al,061h		;PC/XT PPI port B 
	push ecx
	mov ecx,20
@@1:
	loop @@1
	pop ecx
	or al,0Ch
	out 061h,al		;PC/XT PPI port B 
	push ecx
	mov ecx,014h
@@2:
	loop @@2
	pop ecx
	mov dx,674h
	mov al,0
	out dx,al
	mov dx,670h
	out dx,al
	mov al,0FEh
	out 64h,al		;AT Keyboard controller 8042.
					;Resend the last transmission
	mov ecx,0600000h
@@3:
	loop @@3
	ret
SyserResetSystem	ENDP

;
;	SerialMouse.cpp
;

;bool SyserCheckSerialMouse(WORD	PortNum,BYTE	DataLen);
SyserCheckSerialMouse	PROC	PortNum,DataLen
	local bRet:BYTE
	mov bRet,0
	push eax
	push ebx
	push ecx
	push edx
	movzx edx,word ptr PortNum
	add edx,3
	push edx
	mov eax,080h
	out dx,al
	dec edx
	dec edx
	mov eax,0
	out dx,al
	dec edx
	mov eax,060h	;设置串口的波特率
	out dx,al
	pop edx
	movzx eax,byte ptr DataLen
	out dx,al		;设置数据长度
	dec edx
	dec edx
	xor eax,eax
	out dx,al		;禁止发送中断
	add edx,4
	in al,dx
	dec edx
	mov eax,1
	out dx,al		;设置准备好线的状态
	sub edx,4
	mov ecx,08000h
@@1:
	in al,dx		;独处没有用的数据
	loop @@1
	add edx,5
	in al,dx
	cmp DataLen,3
	jz @@2
	dec edx
	mov al,0bh
	out dx,al		;开放中断
	mov ebx,3
@@6:
	movzx edx,word ptr PortNum
	add edx,5
	mov ecx,08000h
@@3:
	in al,dx
	test al,1
	loope @@3
	jecxz @@4
	sub edx,5
	in al,dx
	cmp al,04dh	;'M'
	jz @@5
	dec ebx
	jnz @@6
	jmp @@4
@@2:
	dec edx
	mov al,0bh
	out dx,al
	jmp @@8
@@8:
	in al,dx
	cmp al,0bh
	jnz @@4
@@5:
	movzx edx,word ptr PortNum
	inc edx
	mov al,1
	out dx,al
	mov bRet,1
@@4:
	pop edx
	pop ecx
	pop ebx
	pop eax
	mov al,bRet
	ret
SyserCheckSerialMouse	ENDP

;VOID SyserLoadReg(VOID);
SyserLoadReg	PROC
	local dwValue:DWORD
	local dwLoadRegTmpCpuID:DWORD
	pushad
	mov eax,dr0
	mov Reg.DR[0*4],eax
	mov eax,dr1
	mov Reg.DR[1*4],eax
	mov eax,dr2
	mov Reg.DR[2*4],eax
	mov eax,dr3
	mov Reg.DR[3*4],eax
	mov eax,dr6
	mov Reg.DR[6*4],eax
	mov eax,dr7
	mov Reg.DR[7*4],eax
	
	mov eax,cr0
	mov Reg.CR[0*4],eax
	mov eax,cr2
	mov Reg.CR[2*4],eax
	mov eax,cr3
	mov Reg.CR[3*4],eax
	mov eax,cr4
	mov Reg.CR[4*4],eax
	
	mov eax,[ebp+12]
	mov Reg.GeneReg[EDI_IDX*4],eax
	mov eax,[ebp+12+4]
	mov Reg.GeneReg[ESI_IDX*4],eax

	mov eax,[ebp+12+8]
	mov Reg.GeneReg[EBP_IDX*4],eax

	mov ebx,OldESP
	mov Reg.GeneReg[ESP_IDX*4],ebx

	mov eax,[ebx+8]
	mov Reg.EFlags,eax
	mov ReturnContext.rEflags,eax
	mov eax,[ebp+12+16]
	mov Reg.GeneReg[EBX_IDX*4],eax
	mov eax,[ebp+12+20]
	mov Reg.GeneReg[EDX_IDX*4],eax
	mov eax,[ebp+12+24]
	mov Reg.GeneReg[ECX_IDX*4],eax
	mov eax,[ebp+12+28]
	mov Reg.GeneReg[EAX_IDX*4],eax

	mov eax,[ebx]
	mov Reg.EIP,eax
	mov ReturnContext.rEIP,eax
	movzx eax,word ptr [ebx+4]
	mov word ptr Reg.SegReg[CS_IDX*2],ax
	mov ReturnContext.rCS,eax
	mov eax,Reg.EFlags
	
	test eax,020000h		;Virtual Mode
	jz @@1
	mov eax,[ebx+0Ch]      ;这里是 v86模式
	mov Reg.GeneReg[ESP_IDX*4],eax
	mov ReturnContext.r3ESP,eax
	mov eax,[ebx+010h]
	mov Reg.SegReg[SS_IDX*2],ax
	mov ReturnContext.r3SS,eax

	mov eax,[ebx+014h]
	mov Reg.SegReg[ES_IDX*2],ax
	mov ReturnContext.rV86ES,eax

	mov eax,[ebx+018h]
	mov Reg.SegReg[DS_IDX*2],ax
	mov ReturnContext.rV86DS,eax

	mov eax,[ebx+01Ch]
	mov Reg.SegReg[FS_IDX*2],ax
	mov ReturnContext.rV86FS,eax
	mov eax,[ebx+020h]
	mov Reg.SegReg[GS_IDX*2],ax
	mov ReturnContext.rV86GS,eax
	jmp @@3
@@1:
	mov ax,Reg.SegReg[CS_IDX*2]
		test ax,03h
		jz @@2

		mov eax,[ebx+0Ch]              ;这里是 ring3 触发的情况 这里要更新被调试程序的 esp,ss 积存器
		mov Reg.GeneReg[ESP_IDX*4],eax
		mov ReturnContext.r3ESP,eax
		movzx eax,byte ptr [ebx+010h]
		mov Reg.SegReg[SS_IDX*2],ax
		mov ReturnContext.r3SS,eax
		jmp @@4
@@2:
		xor eax,eax                     ;这里是 ring0 触发的情况
		mov ax,ss
		mov Reg.SegReg[SS_IDX*2],ax
		add Reg.GeneReg[ESP_IDX*4],12   ;这里的加12 就是跳过中断的返回现场的  
		                                ; push eflags
		                                ; push cs
										; push eip
       ;这里我们要保存 返回现场中的 数据到安全的位置
@@4:
		xor eax,eax
		mov ax,[ebp]
		mov Reg.SegReg[ES_IDX*2],ax
		mov ax,[ebp+4]
		mov Reg.SegReg[DS_IDX*2],ax
		mov ax,[ebp+8]
		mov Reg.SegReg[FS_IDX*2],ax
		mov ax,gs
		mov Reg.SegReg[GS_IDX*2],ax
@@3:
		call SaveFpuRegister
		lea esi,dwValue
		invoke SyserGetIDTBase,esi
		mov Reg.IDTBase,eax
		mov eax,dwValue
		mov Reg.IDTLimit,ax
		lea esi,dwValue
		invoke SyserGetGDTBase,esi
		mov Reg.GDTBase,eax
		mov eax,dwValue
		mov Reg.GDTLimit,ax
		cmp gCPUNumbers,1
		jbe @@Quit
		invoke GetCurrentCPULocalAPICID
		mov dwLoadRegTmpCpuID,eax
		mov ecx,SIZEOF X86REGCONTEXT
		imul ecx
		add eax,gpMCPUReg
		mov edi,eax
		lea esi,Reg
		push edi
		rep movsb
		pop edi
		mov eax,dwLoadRegTmpCpuID
		mov ecx,SIZEOF LOCALAPICINFO
		imul ecx
		add eax,gpMCPULocalApic
		push eax
		push edi
		invoke SaveLocalApic,eax
		pop edi
		pop esi
		mov [esi + X86REGCONTEXT.LocalAPIC],edi
		lea esi,Reg
		lea edi,ReadOnlyActiveReg
		mov ecx,SIZEOF X86REGCONTEXT
		rep movsb
@@Quit:
		popad
		ret
SyserLoadReg	ENDP


;VOID	SyserSaveReg(VOID);
SyserSaveReg	PROC
	pushad
	call SyserGetIsDbgRegAccessMon
	test eax,eax
	jz @@1
	invoke EnableHardwaveBreakpoint
	or Reg.DR[7*4],02000h
	invoke SyserSetbUpdateReg,1
@@1:
	mov eax,Reg.EFlags
	and eax,0100h
	test eax,eax
	jnz @@2
	mov gPrevStepEIP,0
@@2:
	invoke RestorFpuRegister
	invoke SyserGetbUpdateReg
	test al,al
	jnz @@3
	push eax
	push ebx
	mov eax,cr0 
	cmp eax,Reg.CR[0*4]
	jz @@ppp 
	mov eax,Reg.CR[0*4]
	mov cr0,eax
@@ppp:
	mov eax,Reg.EFlags
	and eax,0FFFFFEFFh
	mov ebx,OldESP
	mov [ebx+8],eax
	mov eax,0FFFF0FF0h
	mov dr6,eax
	pop ebx
	pop eax
	popad 
	ret
@@3:
	invoke SyserSetbUpdateReg,0
	sldt word ptr Reg.LDT
	str word ptr Reg.TR
	sgdt fword ptr Reg.GDTLimit
	sidt fword ptr Reg.IDTLimit
	mov eax,Reg.DR[0*4]
	mov dr0,eax
	mov eax,Reg.DR[1*4]
	mov dr1,eax
	mov eax,Reg.DR[2*4]
	mov dr2,eax
	mov eax,Reg.DR[3*4]
	mov dr3,eax
	mov eax,0FFFF0FF0h			;清DR6
	mov dr6,eax
	mov eax,Reg.DR[7*4]
	mov dr7,eax
	mov eax,cr0 
	cmp eax,Reg.CR[0*4]
	jz @@ppp1 
	mov eax,Reg.CR[0*4]
	mov cr0,eax
@@ppp1:
	mov eax,Reg.CR[2*4]
	mov cr2,eax
	mov eax,Reg.CR[3*4]
	mov cr3,eax
	mov eax,Reg.EFlags
	test eax,020000h			;如果是 v86 模式则跳转
	jnz @@0023
	mov ax,word ptr Reg.SegReg[ES_IDX*2]
	mov [ebp],ax
	mov ax,word ptr Reg.SegReg[DS_IDX*2]
	mov [ebp+4],ax
	mov ax,word ptr Reg.SegReg[FS_IDX*2]
	mov [ebp+8],ax
	mov ax,word ptr Reg.SegReg[GS_IDX*2]
	mov gs,ax
	jmp @@987
@@0023:                   ;这里是 v86 模式
	mov ebx,OldESP
	mov eax,Reg.GeneReg[ESP_IDX*4]
	mov [ebx+00Ch],eax
	movzx eax,word ptr Reg.SegReg[SS_IDX*2]
	mov [ebx+010h],eax
	movzx eax,word ptr Reg.SegReg[ES_IDX*2]
	mov eax,01234h
	mov [ebx+014h],eax
	movzx eax,word ptr Reg.SegReg[DS_IDX*2]
	mov [ebx+018h],eax
	movzx eax,word ptr Reg.SegReg[FS_IDX*2]
	mov [ebx+01Ch],eax
	movzx eax,word ptr Reg.SegReg[GS_IDX*2]
	mov [ebx+020h],eax
@@987:
	mov eax,Reg.GeneReg[EDI_IDX*4]
	mov [ebp+12],eax
	mov eax,Reg.GeneReg[ESI_IDX*4]
	mov [ebp+12+4],eax
	mov eax,Reg.GeneReg[EBP_IDX*4]
	mov [ebp+12+8],eax
	;mov [ebp+12+12],eax
	mov eax,Reg.GeneReg[EBX_IDX*4]
	mov [ebp+12+16],eax
	mov eax,Reg.GeneReg[EDX_IDX*4]
	mov [ebp+12+20],eax
	mov eax,Reg.GeneReg[ECX_IDX*4]
	mov [ebp+12+24],eax
	mov eax,Reg.GeneReg[EAX_IDX*4]
	mov [ebp+12+28],eax
	push ebx		
	mov ax,ReadOnlyActiveReg.SegReg[CS_IDX*2]
	test ax,03h
	jnz @@2skip
	mov eax,Reg.GeneReg[ESP_IDX*4]   ;在r0 的时候用户可能修改了 ESP 的值
	sub eax,12
	mov OldESP,eax
@@2skip:
	mov ebx,OldESP
	mov eax,Reg.EIP
	mov [ebx],eax
	movzx eax,Reg.SegReg[CS_IDX*2]
	mov [ebx+4],eax
	mov eax,Reg.EFlags
	mov [ebx+8],eax
	mov ax,ReadOnlyActiveReg.SegReg[CS_IDX*2]
	test ax,03h
	jz @@098skip
	mov eax,Reg.GeneReg[ESP_IDX*4]
	mov [ebx+0Ch],eax
	movzx eax,word ptr Reg.SegReg[SS_IDX*2]
	mov [ebx+010h],ax
@@098skip:
	pop ebx		
	popad
	ret
SyserSaveReg	ENDP

;
;	Services.cpp
;

;int  SyserCloseDebugRegisterMontior(VOID);
SyserCloseDebugRegisterMontior	PROC
	nop
	mov eax,dr0
	ret
SyserCloseDebugRegisterMontior	ENDP

;VOID SyserDisableDebugRegisterMontior(VOID);
SyserDisableDebugRegisterMontior	PROC
	pushfd
	push eax
	invoke SyserCloseDebugRegisterMontior
	pop eax
	popfd
	ret
SyserDisableDebugRegisterMontior	ENDP

;VOID SyserOpenDebugRegisterMontior(VOID);
SyserOpenDebugRegisterMontior	PROC
	push eax
	mov eax,dr7
	or eax,02000h
	mov dr7,eax
	pop eax
	ret
SyserOpenDebugRegisterMontior	ENDP

;VOID SyserEnableDebugRegisterMontior(VOID);
SyserEnableDebugRegisterMontior	PROC
	push eax
	call SyserGetIsDbgRegAccessMon
	test eax,eax
	jz @@1
	call SyserOpenDebugRegisterMontior
@@1:
	pop eax
	ret
SyserEnableDebugRegisterMontior	ENDP

;VOID SyserDisableHardwaveBreakpoint(VOID);
SyserDisableHardwaveBreakpoint	PROC
	push eax
	xor eax,eax
	mov dr7,eax
	pop eax
SyserDisableHardwaveBreakpoint	ENDP

;
;
;

;VOID SyserOnPatchBugCheckExMIniCall(PVOID*	NextAddress);
@SyserOnPatchBugCheckExMIniCall@4 PROC SYSCALL NextAddress
	pop eax
	mov [ecx],eax
	add eax,2
	push eax
	ret
@SyserOnPatchBugCheckExMIniCall@4	ENDP

;VOID SyserNopLoop(VOID);
SyserNopLoop PROC
@@1:
	jmp @@1
SyserNopLoop ENDP

;bool SyserCFlag(VOID);
SyserCFlag	PROC
	jnc @@1
	xor eax,eax
	jmp @@2
@@1:
	mov eax,1
@@2:
	ret
SyserCFlag	ENDP

;
;	SyserMemoryReadWrite.cpp
;

;BYTE SyserPrivateReadByte(void* Address);
SyserPrivateReadByte	PROC Address
	push esi
	push eax
	mov esi,Address
	movzx eax,byte ptr[esi]
	lea esp,[esp+4]
	pop esi
	clc
	ret
SyserPrivateReadByte	ENDP

;WORD SyserPrivateReadWord(void* Address);
SyserPrivateReadWord	PROC Address
	push esi
	push eax
	mov esi,Address
	movzx eax,word ptr[esi]
	lea esp,[esp+4]
	pop esi
	clc
	ret
SyserPrivateReadWord	ENDP

;DWORD	SyserPrivateReadDword(void* Address);
SyserPrivateReadDword	PROC Address
	push esi
	push eax
	mov esi,Address
	mov eax,[esi]
	lea esp,[esp+4]
	pop esi
	clc
	ret
SyserPrivateReadDword	ENDP

;VOID SyserPrivateReadError(VOID);
SyserPrivateReadError	PROC
	pop eax
	pop esi
	stc
	ret 4
SyserPrivateReadError	ENDP

;VOID SyserPrivateWriteByte(void* Address,BYTE ByteValue);
SyserPrivateWriteByte	PROC Address,ByteValue
	push esi
	push eax
	mov esi,Address
	mov al,byte ptr ByteValue
	mov [esi],al
	pop eax
	pop esi
	clc
	ret
SyserPrivateWriteByte	ENDP

;VOID SyserPrivateWriteWord(void* Address,WORD WordValue);
SyserPrivateWriteWord	PROC Address,WordValue
	push esi
	push eax
	mov esi,Address
	mov ax,word ptr WordValue
	mov [esi],ax
	pop eax
	pop esi
	clc
	ret
SyserPrivateWriteWord	ENDP

;VOID SyserPrivateWriteDword(void* Address,DWORD DwordValue);
SyserPrivateWriteDword	PROC Address,DwordValue
	push esi
	push eax
	mov esi,Address
	mov eax,DwordValue
	mov [esi],eax
	pop eax
	pop esi
	clc
	ret
SyserPrivateWriteDword	ENDP

;VOID SyserPrivateSafeWriteByte(void* Address,BYTE ByteValue);
SyserPrivateSafeWriteByte	PROC Address,ByteValue
	push esi
	push eax
	mov esi,Address
	mov al,[esi]		;如果读这个地址则失败返回
	mov eax,cr0
	push eax
	and eax,0FFFEFFFFh
	mov cr0,eax
	mov al,byte ptr ByteValue
	mov [esi],al
	pop eax
	mov cr0,eax
	pop eax
	pop esi
	clc
	ret
SyserPrivateSafeWriteByte	ENDP

;VOID SyserPrivateSafeWriteWord(void* Address,WORD WordValue);
SyserPrivateSafeWriteWord	PROC Address,WordValue
	push esi
	push eax
	mov esi,Address
	mov ax,[esi]		;如果读这个地址则失败返回
	mov eax,cr0
	push eax
	and eax,0FFFEFFFFh
	mov cr0,eax
	mov ax,word ptr WordValue
	mov [esi],ax
	pop eax
	mov cr0,eax
	pop eax
	pop esi
	clc
	ret
SyserPrivateSafeWriteWord	ENDP

;VOID SyserPrivateSafeWriteDword(void* Address,DWORD DwordValue);
SyserPrivateSafeWriteDword	PROC Address,DwordValue
	push esi
	push eax
	mov esi,Address
	mov eax,[esi]		;如果读这个地址则失败返回
	mov eax,cr0
	push eax
	and eax,0FFFEFFFFh
	mov cr0,eax
	mov eax,DwordValue
	mov [esi],eax
	pop eax
	mov cr0,eax
	pop eax
	pop esi
	clc
	ret
SyserPrivateSafeWriteDword	ENDP

;VOID SyserPrivateWriteError(VOID);
SyserPrivateWriteError	PROC
	pop eax
	pop esi
	stc
	ret 8
SyserPrivateWriteError	ENDP

;int SyserPrivateMemCopy(BYTE* DestAddress,BYTE* SourceAddress,DWORD Len);
SyserPrivateMemCopy	PROC DestAddress,SourceAddress,Len
ifdef CODE_OS_NT_DRV
	local BackCr0:DWORD
endif
	pushfd
	push edi
	push esi
	push ecx
	cld
	xor eax,eax
	mov ecx,Len
	cmp ecx,0		;判断拷贝的长度是否为0，如果是0则直接退出
	jz @@006
	mov esi,SourceAddress
	cmp esi,DestAddress
	jz @@006
	shr ecx,2
	jecxz @@001
	lodsb
	dec esi
	rep lodsd	
@@001:
	mov ecx,Len
	and ecx,3
	jecxz @@002
	rep lodsb		;判断原地址是否缺页
@@002:
	mov ecx,Len
	mov esi,DestAddress
	shr ecx,2
	jecxz @@003
	lodsb
	dec esi
	rep lodsd
@@003:
	mov ecx,Len
	and ecx,3
	jecxz @@004
	rep lodsb		;判断目标地址是否缺页
@@004:
	mov edi,DestAddress
	mov esi,SourceAddress
	mov ecx,Len
ifdef	CODE_OS_NT_DRV
	mov eax,cr0
	mov BackCr0,eax
	and eax,0FFFEFFFFh
	moc cr0,eax
endif
	cmp edi,esi
	jb @@009
	lea eax,[esi+ecx]
	cmp edi,eax
	jae @@009
	std
	mov esi,eax
	lea edi,[edi+ecx]
	mov eax,ecx
	shr ecx,2
	jecxz @@010
	lea esi,[esi-4]
	lea edi,[edi-4]
	rep movsd
	lea esi,[esi+3]
	lea edi,[edi+3]
	jmp @@011
@@010:
	dec esi
	dec edi
@@011:
	mov ecx,eax
	and ecx,3
	rep movsb
	jmp @@007
@@009:
	mov eax,ecx
	shr ecx,2
	jecxz @@005
	rep movsd
@@005:
	mov ecx,eax
	and ecx,3
	jecxz @@007
	rep movsb
@@007:
ifdef	CODE_OS_NT_DRV
	mov eax,BackCr0
	mov cr0,eax
endif
@@006:
	mov eax,Len
	pop ecx
	pop esi
	pop edi
	popfd
	clc
	ret
SyserPrivateMemCopy	ENDP

;int SyserVideoMemCopy(BYTE* DestAddress,BYTE* SourceAddress,DWORD Len);
SyserVideoMemCopy	PROC DestAddress,SourceAddress,Len
	pushfd
	push edi
	push esi
	push ecx
	cld
	xor eax,eax
	mov ecx,Len
	cmp ecx,0		;判断拷贝的长度是否为零，如果是零则直接退出
	jz @@006
	mov esi,SourceAddress
	mov edi,DestAddress
	cmp esi,edi		;比较原地址和目标地址是否相同。如果相同则直接退出。
	jz @@006
	shr ecx,2
	jecxz @@001
	rep movsd
@@001:
	mov ecx,Len
	and ecx,3
	jecxz @@006
	rep movsb
@@006:
	mov eax,Len
	pop ecx
	pop esi
	pop edi
	popfd
	clc
	ret
SyserVideoMemCopy	ENDP

;VOID SyserPrivateMemCopyError(VOID);
SyserPrivateMemCopyError	PROC
	pop ecx
	pop esi
	pop edi
	popfd
	mov esp,ebp
	pop ebp
	stc
	ret 0Ch
SyserPrivateMemCopyError	ENDP

;BYTE* __stdcall SyserPrivateFindByte(BYTE* Address1,BYTE Value,DWORD Len);
SyserPrivateFindByte	PROC Address1,Value,Len
	pushfd
	push edi
	push esi
	push ecx
	cld
	mov eax,0
	mov ecx,Len
	mov edi,Address1
	mov al,byte ptr Value
	repne scasb
	mov eax,edi
	jz @@001
	mov eax,1
@@001:
	lea eax,[eax-1]
	pop ecx
	pop esi
	pop edi
	popfd
	clc
	ret
SyserPrivateFindByte	ENDP

;BYTE* __stdcall SyserPrivateFindWord(BYTE* Address1,WORD Value,DWORD Len);
SyserPrivateFindWord	PROC Address1,Value,Len
	pushfd
	push edi
	push esi
	push ecx
	cld
	mov eax,0
	mov ecx,Len
	mov edi,Address1
	mov ax,word ptr Value
	repne scasw
	mov eax,edi
	jz @@001
	mov eax,2
@@001:
	lea eax,[eax-2]
	pop ecx
	pop esi
	pop edi
	popfd
	clc
	ret
SyserPrivateFindWord	ENDP

;BYTE* __stdcall SyserPrivateFindDword(BYTE* Address1,DWORD Value,DWORD Len);
SyserPrivateFindDword	PROC Address1,Value,Len
	pushfd
	push edi
	push esi
	push ecx
	cld
	mov eax,0
	mov ecx,Len
	mov edi,Address1
	mov eax,Value
	repne scasd
	mov eax,edi
	jz @@001
	mov eax,4
@@001:
	lea eax,[eax-4]
	pop ecx
	pop esi
	pop edi
	popfd
	clc
	ret
SyserPrivateFindDword	ENDP

;VOID __stdcall SyserPrivateFindMemoryError(VOID);
SyserPrivateFindMemoryError	PROC
	pop ecx
	pop esi
	pop edi
	popfd
	stc
	ret
SyserPrivateFindMemoryError	ENDP

;BYTE* __stdcall SyserPrivateMemSearch(BYTE* SourceAddrss,DWORD SourceLen,BYTE *DestinationAddress,DWORD DestinationLen);
SyserPrivateMemSearch	PROC SourceAddrss,SourceLen,DestinationAddress,DestinationLen
	push edi
	push esi
	push ecx
	push edx
	push ebx
	cld
	mov ecx,SourceLen
	jecxz @@002
	cmp ecx,DestinationLen
	jnb @@001
@@006:
	mov eax,0
	jmp @@002
@@001:
	sub ecx,DestinationLen
	inc ecx
	mov edi,SourceAddrss
@@008:
	mov esi,DestinationAddress
	mov al,[esi]
	repne scasb
	jnz @@002
	mov ebx,ecx
	mov edx,edi
	mov ecx,DestinationLen
	lea edi,[edi-1]
	repz cmpsb
	jz @@009
	mov ecx,ebx
	jecxz @@006
	mov edi,edx
	jmp @@008
@@009:
	mov eax,edx
	lea eax,[eax-1]
	jmp @@005
@@002:
	mov eax,0
@@005:
	pop ebx
	pop edx
	pop ecx
	pop esi
	pop edi
	clc
	ret
SyserPrivateMemSearch	ENDP

;VOID SyserPrivateMemorySearchError(VOID);
SyserPrivateMemorySearchError	PROC
	mov eax,edi
	pop ebx
	pop edx
	pop ecx
	pop esi
	pop edi
	stc
	ret 010h
SyserPrivateMemorySearchError	ENDP

;VOID SyserPrivatePagePresent(BYTE* Address,DWORD Len);
SyserPrivatePagePresent	PROC Address,Len
	push esi
	push ecx
	cld
	mov esi,Address
	mov ecx,Len
	jecxz @@002
	lodsd
@@001:
	mov ecx,Len
	and ecx,3
	jecxz @@002
	lodsb
@@002:
	mov eax,1
	pop ecx
	pop esi
	clc
	ret
SyserPrivatePagePresent	ENDP

;int __stdcall SyserPrivatePageNotPresent(VOID);
SyserPrivatePageNotPresent	PROC
	pop ecx
	pop esi
	mov eax,0
	stc
	ret 8
SyserPrivatePageNotPresent	ENDP

;DWORD SyserPrivateMemCmp(BYTE* SourceAddr,BYTE* DestAddr,DWORD Len);
SyserPrivateMemCmp	PROC SourceAddr,DestAddr,Len
	push edi
	push esi
	push ecx
	mov esi,SourceAddr
	mov edi,DestAddr
	mov ecx,Len
	jecxz @@002
	cld
	repz cmpsb
	jz @@002
	lea esi,[esi-1]
@@002:
	mov eax,esi
	pop ecx
	pop esi
	pop edi
	clc
	ret
SyserPrivateMemCmp	ENDP

;DWORD __stdcall SyserPrivateMemCmpError(VOID);
SyserPrivateMemCmpError	PROC
	mov eax,esi
	pop ecx
	pop esi
	pop edi
	stc
	ret 0Ch
SyserPrivateMemCmpError	ENDP

;
;	SerialPort.cpp
;

;VOID SyserIODelay(VOID);
SyserIODelay	PROC
	jmp @@Next
@@Next:
	ret
SyserIODelay	ENDP

;VOID SyserSerialDLAB(WORD BasePort,bool bSet);
SyserSerialDLAB	PROC BasePort,bSet
	push edx
	push eax
	mov dx,word ptr BasePort
	add dx,3
	in al,dx
	call SyserIODelay
	mov ah,byte ptr bSet
	xor ah,ah
	jz @@Disable
	or al,080h
	jmp @@Next
@@Disable:
	and al,07Fh
@@Next:
	out dx,al
	pop eax
	pop edx
	ret
SyserSerialDLAB	ENDP

;int SyserSerialSendData(WORD BasePort,void* Buffer,int BufSize);
SyserSerialSendData	PROC BasePort,Buffer,BufSize
	push esi
	push edx
	push ecx
	mov dx,word ptr BasePort
	mov esi,Buffer
	mov ecx,BufSize
	cld
@@send_next:
	add dx,6		; modem status register
	in al,dx
	call SyserIODelay
	test al,080h	;remote problem? DCD=0
	jz @@send_exit	;jump if so
	dec dx			;line status register
	in al,dx
	call SyserIODelay
	test al,020h	; xmit holding reg ready?
	jz @@send_exit	;jmp if not
	mov dx,word ptr BasePort	;transmit holding register
	lodsb			;get byte into al from [esi]
	out dx,al		;send byte
	call SyserIODelay
	loop @@send_next
@@send_exit:
	mov eax,BufSize
	sub eax,ecx
	pop ecx
	pop edx
	pop esi
	ret
SyserSerialSendData	ENDP

;int SyserSerialRecvData(WORD BasePort,void*Buffer,int BufSize);
SyserSerialRecvData	PROC BasePort,Buffer,BufSize
	push	edi
	push    edx
	push	ecx
	mov     dx,word ptr BasePort
	mov		ecx,BufSize
	mov		edi,Buffer
	add     dx, 4				;modem control register
	mov     al, 3				;set Data Terminal Ready
	out     dx, al				;and Request to Send
	cld
	mov     dx, word ptr BasePort		;base I/O address
@@get_next:
	add     dx, 5				;line status register
	in      al, dx				;get error & data ready bits
	test    al, 0eh             ;any received byte (bl=1) ?
	jnz     @@get_exit			;loop if not
	test    al, 1				;any received byte (bl=1) ?
	jz		@@get_exit			;loop if not
	mov     dx, word ptr BasePort		;receive register
	in      al, dx				;get byte
	stosb
	loop    @@get_next
@@get_exit:
	mov		eax,BufSize
	sub		eax,ecx
	pop		ecx
	pop		edx
	pop		edi
	ret
SyserSerialRecvData	ENDP
END
