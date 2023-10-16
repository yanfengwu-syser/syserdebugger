;	/*
;		公共功能封装
;		
;		十二羽翼
;		QQ:764439262
;	*/

EXTERN	HvmSubvertCpu:PROC
EXTERN	HvmResumeGuest:PROC
EXTERN	OldKiFastCallEntry:QWORD

.CODE

MyKiFastCallEntry PROC
jmp OldKiFastCallEntry
MyKiFastCallEntry ENDP
	
CmSubvert PROC

	push	rax
	push	rcx
	push	rdx
	push	rbx
	push	rbp
	push	rsi
	push	rdi
	push	r8
	push	r9
	push	r10
	push	r11
	push	r12
	push	r13
	push	r14
	push	r15

	sub	rsp, 28h

	mov	rcx, rsp
	call	HvmSubvertCpu
	
	add	rsp, 28h
	
	pop	r15
	pop	r14
	pop	r13
	pop	r12
	pop	r11
	pop	r10
	pop	r9
	pop	r8
	pop	rdi
	pop	rsi
	pop	rbp
	pop	rbx
	pop	rdx
	pop	rcx
	pop	rax

	ret
CmSubvert ENDP
CmSlipIntoMatrix PROC

	call	HvmResumeGuest

	add	rsp, 28h

	pop	r15
	pop	r14
	pop	r13
	pop	r12
	pop	r11
	pop	r10
	pop	r9
	pop	r8
	pop	rdi
	pop	rsi
	pop	rbp
	pop	rbx
	pop	rdx
	pop	rcx
	pop	rax

	ret

CmSlipIntoMatrix ENDP

HvmGetCpuIdInfo PROC
    push rbx
    push rcx
    push rdx
    push rsi
    mov rsi,rcx
    mov eax,[rsi]
    cpuid
    mov [rsi], eax
    mov [rsi+4], ebx
    mov [rsi+8], ecx
    mov [rsi+12], edx
    pop rsi
    pop rdx
    pop rcx
    pop rbx    
	ret
HvmGetCpuIdInfo ENDP

;
;	Register Opreation
;

HvmRegGetRdtscp PROC
	push rsi
	mov rsi,rcx
	rdtscp
	mov [rsi],eax
	mov [rsi+8],ecx
	mov [rsi+12],edx
	pop rsi
	ret
HvmRegGetRdtscp ENDP

HvmRegGetTSC PROC
;	rdtscp
	rdtsc
	shl		rdx, 32
	or		rax, rdx
	ret
HvmRegGetTSC ENDP

HvmRegGetRax PROC
	mov		rax, rax
	ret
HvmRegGetRax ENDP


HvmRegGetRbx PROC
	mov		rax, rbx
	ret
HvmRegGetRbx ENDP


HvmRegGetCs PROC
	mov		rax, cs
	ret
HvmRegGetCs ENDP

HvmRegGetDs PROC
	mov		rax, ds
	ret
HvmRegGetDs ENDP

HvmRegGetEs PROC
	mov		rax, es
	ret
HvmRegGetEs ENDP

HvmRegGetSs PROC
	mov		rax, ss
	ret
HvmRegGetSs ENDP

HvmRegGetFs PROC
	mov		rax, fs
	ret
HvmRegGetFs ENDP

HvmRegGetGs PROC
	mov		rax, gs
	ret
HvmRegGetGs ENDP

HvmRegGetCr0 PROC
	mov		rax, cr0
	ret
HvmRegGetCr0 ENDP

HvmRegGetCr2 PROC
	mov		rax, cr2
	ret
HvmRegGetCr2 ENDP

HvmRegGetCr3 PROC
	mov		rax, cr3
	ret
HvmRegGetCr3 ENDP

HvmRegGetCr4 PROC
	mov		rax, cr4
	ret
HvmRegGetCr4 ENDP

HvmRegGetCr8 PROC
	mov		rax, cr8
	ret
HvmRegGetCr8 ENDP

HvmRegSetCr8 PROC
	mov		cr8, rcx
	ret
HvmRegSetCr8 ENDP

HvmRegGetDr6 PROC
	mov		rax, dr6
	ret
HvmRegGetDr6 ENDP

HvmRegGetDr0 PROC
	mov		rax, dr0
	ret
HvmRegGetDr0 ENDP

HvmRegGetDr1 PROC
	mov		rax, dr1
	ret
HvmRegGetDr1 ENDP

HvmRegGetDr2 PROC
	mov		rax, dr2
	ret
HvmRegGetDr2 ENDP

HvmRegGetDr3 PROC
	mov		rax, dr3
	ret
HvmRegGetDr3 ENDP

;VOID HvmRegSetCR0(ULONG_PTR	NewValue)
HvmRegSetCR0 PROC
	mov		cr0, rcx
	ret
HvmRegSetCR0 ENDP

;VOID HvmRegSetCR2(ULONG_PTR	NewValue)
HvmRegSetCR2 PROC
	mov		cr2, rcx
	ret
HvmRegSetCR2 ENDP

;VOID HvmRegSetCR3(ULONG_PTR	NewValue)
HvmRegSetCR3 PROC
	mov		cr3, rcx
	ret
HvmRegSetCR3 ENDP

;VOID HvmRegSetCR4(ULONG_PTR	NewValue)
HvmRegSetCR4 PROC
	mov		cr4, rcx
	ret
HvmRegSetCR4 ENDP

HvmRegGetRflags PROC
	pushfq
	pop		rax
	ret
HvmRegGetRflags ENDP

HvmRegGetRsp PROC
	mov		rax, rsp
	add		rax, 8
	ret
HvmRegGetRsp ENDP

HvmGetIdtBase PROC
	LOCAL	idtr[10]:BYTE
	
	sidt	idtr
	mov		rax, QWORD PTR idtr[2]
	ret
HvmGetIdtBase ENDP

HvmGetIdtLimit PROC
	LOCAL	idtr[10]:BYTE
	
	sidt	idtr
	mov		ax, WORD PTR idtr[0]
	ret
HvmGetIdtLimit ENDP

HvmGetGdtBase PROC
	LOCAL	gdtr[10]:BYTE

	sgdt	gdtr
	mov		rax, QWORD PTR gdtr[2]
	ret
HvmGetGdtBase ENDP

HvmGetGdtLimit PROC
	LOCAL	gdtr[10]:BYTE

	sgdt	gdtr
	mov		ax, WORD PTR gdtr[0]
	ret
HvmGetGdtLimit ENDP

;add by cini
HvmGetLdtr PROC
	sldt	rax
	ret
HvmGetLdtr ENDP

;add end

HvmGetTrSelector PROC
	str	rax
	ret
HvmGetTrSelector ENDP

;ULONG_PTR	HvmGetCR4(VOID)
HvmGetCR4 PROC
	mov rax,cr4
	ret
HvmGetCR4 ENDP

;VOID HvmSetCR4(ULONG_PTR	NewValue);
HvmSetCR4 PROC
	mov rax,rcx
	mov cr4,rax
	ret
HvmSetCR4 ENDP

;
;	MSR Opreation
;

;ULONG64 MsrRead (ULONG32 reg );
MsrRead PROC
	rdmsr				; MSR[ecx] --> edx:eax
	shl		rdx, 32
	or		rax, rdx
	ret
MsrRead ENDP

; VOID MsrWrite (ULONG32 reg (rcx), ULONG64 MsrValue (rdx));
MsrWrite PROC
	mov		rax, rdx
	shr		rdx, 32
	wrmsr
	ret
MsrWrite ENDP

; ULONG64 MsrReadWithEaxEdx (PULONG32 reg (rcx), PULONG32 eax (rdx), PULONG32 edx (r8));

MsrReadWithEaxEdx PROC
	push	r9
	mov		r9, rdx
	mov		ecx, dword ptr [rcx]
	rdmsr				; MSR[ecx] --> edx:eax
	mov		[r9], eax	
	mov		[r8], edx
	shl		rdx, 32
	mov		edx,eax
	pop		r9
	ret
MsrReadWithEaxEdx ENDP

;
;
;

CmInitSpinLock PROC
	and	dword ptr [rcx], 0
	ret
CmInitSpinLock ENDP


CmAcquireSpinLock PROC
loop_down:
	lock	bts dword ptr [rcx], 0
	jb	loop_down
	ret
CmAcquireSpinLock ENDP


CmReleaseSpinLock PROC
	lock	btr dword ptr [rcx], 0
	ret
CmReleaseSpinLock ENDP

; CmReloadGdtr (PVOID GdtBase (rcx), ULONG GdtLimit (rdx) );

CmReloadGdtr PROC
	push	rcx
	shl		rdx, 48
	push	rdx
	lgdt	fword ptr [rsp+6]	; do not try to modify stack selector with this ;)
	pop		rax
	pop		rax
	ret
CmReloadGdtr ENDP

; CmReloadIdtr (PVOID IdtBase (rcx), ULONG IdtLimit (rdx) );

CmReloadIdtr PROC
	push	rcx
	shl		rdx, 48
	push	rdx
	lidt	fword ptr [rsp+6]
	pop		rax
	pop		rax
	ret
CmReloadIdtr ENDP


END
