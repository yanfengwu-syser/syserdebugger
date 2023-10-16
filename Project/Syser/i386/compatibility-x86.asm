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

include compatibility-x86.inc

;外部函数声明
;EXTERN CloseDebugRegisterMontior@0:PROC

;函数原型定义
;SyserPrivateReadMSR Proto :DWORD

;
;extern gbActive:BYTE

.DATA

;bInit	db	0


.CODE

;
;	VMWareSupport.cpp
;

;bool SyserVMWareTest(VOID);
SyserVMWareTest	PROC
	local bInVMWARE:DWORD
	pushad
	pushfd
	mov bInVMWARE,0
	xor ebx,ebx
	mov ecx,0ah
	mov eax,'VMXh'	; EAX=magic
	mov dx,'VX'		; DX=magic
	in eax,dx		; specially processed io cmd
	cmp ebx,'VMXh'
	jne @@NoInVmware
	mov bInVMWARE,1
@@NoInVmware:
	popfd
	popad
	xor eax,eax
	mov eax,bInVMWARE
	ret
SyserVMWareTest	ENDP

;VOID SyserIsDisableVmMouse(BYTE  *PortValue1,BYTE *PortValue2);
SyserIsDisableVmMouse	PROC PortValue1,PortValue2
	push eax
	push edx
	xor eax,eax
	in al,064h
	mov edx,PortValue1
	mov [edx],byte ptr al
	xor eax,eax
	in eax,064h
	mov edx,PortValue2
	mov [edx],byte ptr al
	pop edx
	pop eax
	ret
SyserIsDisableVmMouse	ENDP

;DWORD SyserVMWareCall(VMVWARE_CALL* pVMCParam);
SyserVMWareCall	PROC	pVMCParam
	local Status:DWORD
	pushad
	mov eax,pVMCParam
	mov word ptr[eax + VMVWARE_CALL.Port],'VX'
	mov dword ptr[eax + VMVWARE_CALL.Return_Status],'VMXh'
	mov edi,[eax + VMVWARE_CALL.Trans_Dest]
	mov esi,[eax + VMVWARE_CALL.Trans_Src]
	mov edx,[eax + VMVWARE_CALL.Port]
	mov ecx,[eax + VMVWARE_CALL.Func_num]
	mov ebx,[eax + VMVWARE_CALL.Exist_flag]
	mov eax,[eax + VMVWARE_CALL.Return_Status]
	mov eax,[eax]
	in eax,dx
	mov Status,eax
	mov eax,pVMCParam
	mov [eax + VMVWARE_CALL.Exist_flag],ebx
	mov [eax + VMVWARE_CALL.Func_num],ecx
	mov [eax + VMVWARE_CALL.Port],edx
	mov [eax + VMVWARE_CALL.Trans_Src],esi
	mov [eax + VMVWARE_CALL.Trans_Dest],edi
	mov edi,Status
	mov [eax + VMVWARE_CALL.Return_Status],edi
	popad
	mov eax,Status
	ret
SyserVMWareCall	ENDP
END
