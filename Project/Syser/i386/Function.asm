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
;	LastBranch.cpp
;

;int SyserDetectLastBranchType(VOID);
SyserDetectLastBranchType	PROC
	local Index:DWORD
	local Index2:DWORD
	local From:DWORD
	local To:DWORD
	local From1:DWORD
	local To1:DWORD
	local Tos1:DWORD
	local Tos2:DWORD
	local From2:DWORD
	local To2:DWORD
	mov Index,0
	mov Index2,0
	mov From,0
	mov To,0
	mov From1,0
	mov To1,0
	mov Tos1,0
	mov Tos2,0
	mov From2,0
	mov To2,0
	pushad
	pushfd
	cli
	mov ecx,01D9h
	xor eax,eax
	xor edx,edx
	rdmsr
	or eax,1
	wrmsr
	call @@001
	nop
@@001:
	pop eax
	xor eax,eax
	xor edx,edx
	mov ecx,01C9h
	rdmsr
	mov Tos1,eax
	call @@002
	nop
@@002:
	pop eax
	xor eax,eax
	xor edx,edx
	mov ecx,01C9h
	rdmsr
	mov Tos2,eax
	popfd
	popad
	
	push ebx		;早期的 P6 处理器， 没有 MSR_LASTBRANCH_TOP 
	mov eax,Tos1
	and eax,0Fh
	mov ebx,Tos2
	and ebx,0Fh
	test eax,ebx
	jnz @@EndIf
	pop ebx
	xor eax,eax
	ret
	
@@EndIf:
	pop ebx
	pushad
	pushfd
	cli
	call @@003
	nop
@@003:
	pop eax
	lea eax,[eax-5]
	mov From,eax
	lea eax,[eax+6]
	mov To,eax
	xor eax,eax
	xor edx,edx
	mov ecx,01C9h
	rdmsr
	and eax,3
	mov ecx,eax
	add ecx,01DBh
	xor eax,eax
	xor edx,edx
	rdmsr
	mov From1,eax
	mov To1,edx
	popfd
	popad
	
	mov eax,From
	cmp eax,From1
	jnz @@NextCon
	mov eax,To
	cmp eax,To1
	jnz @@NextCon
	jmp @@Ret1
@@NextCon:
	mov eax,From
	cmp eax,To1
	jnz	@@EndIf1
	mov eax,To
	cmp eax,From1
	jnz @@EndIf1
@@Ret1:
	mov eax,1
	ret
	
@@EndIf1:
	pushad
	pushfd
	cli
	call @@004
	nop
@@004:
	pop eax
	lea eax,[eax-5]
	mov From,eax
	lea eax,[eax+6]
	mov To,eax
	xor eax,eax
	xor edx,edx
	mov ecx,01C9h
	rdmsr
	and eax,7
	mov Index,eax
	mov ecx,eax
	add ecx,040h
	xor eax,eax
	xor edx,edx
	rdmsr
	mov From1,eax
	mov To1,edx
	jmp @@102
	nop
@@102:
	jmp @@103
	nop
@@103:
	jmp @@104
	nop
@@104:
	jmp @@105
	nop
@@105:
	mov ecx,01D9h
	xor eax,eax
	xor edx,edx
	rdmsr
	and eax,7
	mov Index2,eax
	popfd
	popad
	
	mov eax,From		;测试一下循环栈里面有几个元素
	cmp eax,From1
	jnz @@NextCon1
	mov eax,To
	cmp eax,To1
	jnz @@NextCon1
	jmp @@Ret2
@@NextCon1:
	mov eax,From
	cmp eax,To1
	jnz	@@EndIf2
	mov eax,To
	cmp eax,From1
	jnz @@EndIf2
@@Ret2:
	mov eax,Index	;如果 Index == Index2 则	循环栈里是4个元素 否则是 8 个元素
	cmp eax,Index2
	jz @@Eax2
	mov eax,3
	ret
@@Eax2:
	mov eax,2
	ret
	
@@EndIf2:
	pushad
	pushfd
	cli
	call @@034
	nop
@@034:
	pop eax
	lea eax,[eax-5]
	mov From,eax
	lea eax,[eax+6]
	mov To,eax
	xor eax,eax
	xor edx,edx
	mov ecx,01C9h
	rdmsr
	and eax,7
	mov Index,eax
	mov ecx,eax
	add ecx,040h
	xor eax,eax
	xor edx,edx
	rdmsr
	mov From1,eax
	mov ecx,Index
	add ecx,060h
	xor eax,eax
	xor edx,edx
	rdmsr
	mov To1,eax
	jmp @@005
	nop
@@005:
	jmp @@006
	nop
@@006:
	jmp @@007
	nop
@@007:
	jmp @@008
	nop
@@008:
	xor eax,eax
	xor edx,edx
	mov ecx,01C9h
	rdmsr
	and eax,7
	mov Index2,eax
	popfd
	popad
	
	mov eax,From		;测试一下循环栈里面有几个元素
	cmp eax,From1
	jnz @@NextCon2
	mov eax,To
	cmp eax,To1
	jnz @@NextCon2
	jmp @@Ret3
@@NextCon2:
	mov eax,From
	cmp eax,To1
	jnz	@@EndIf3
	mov eax,To
	cmp eax,From1
	jnz @@EndIf3
@@Ret3:
	mov eax,Index	;如果 Index == Index2 则	循环栈里是4个元素 否则是 8 个元素
	cmp eax,Index2
	jz @@Eax4
	mov eax,5
	ret
@@Eax4:
	mov eax,4
	ret
	
@@EndIf3:
	pushad
	pushfd
	cli
	call @@036
	nop
@@036:
	pop eax
	lea eax,[eax-5]
	mov From,eax
	lea eax,[eax+6]
	mov To,eax
	xor eax,eax
	xor edx,edx
	mov ecx,01C9h
	rdmsr
	and eax,15
	mov Index,eax
	mov ecx,eax
	add ecx,0680h
	xor eax,eax
	xor edx,edx
	rdmsr
	mov From1,eax
	mov ecx,Index
	add ecx,06C0h
	xor eax,eax
	xor edx,edx
	rdmsr
	mov To1,eax
	popfd
	popad
	
	mov eax,From		;测试一下循环栈里面有几个元素
	cmp eax,From1
	jnz @@NextCon3
	mov eax,To
	cmp eax,To1
	jnz @@NextCon3
	jmp @@Ret4
@@NextCon3:
	mov eax,From
	cmp eax,To1
	jnz	@@EndIf4
	mov eax,To
	cmp eax,From1
	jnz @@EndIf4
@@Ret4:
	mov eax,6
	ret
	
@@EndIf4:
	mov eax,0FFFFFFFFh
	ret
SyserDetectLastBranchType	ENDP
END
