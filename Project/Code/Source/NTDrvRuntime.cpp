#include "stdafx.h"
#include "NTDrvRuntime.h"

#define _PAGESIZE_ 4096

// void __declspec(naked) __cdecl _chkstk(void)
// {
// 	__asm
// 	{
// 		push    ecx                     ; save ecx
// 		cmp     eax,_PAGESIZE_          ; more than one page requested?
// 		lea     ecx,[esp] + 8           ; compute new stack pointer in ecx
// 										; correct for return address and
// 										; saved ecx
// 		jb      short lastpage          ; no
// probepages:
// 		sub     ecx,_PAGESIZE_          ; yes, move down a page
// 		sub     eax,_PAGESIZE_          ; adjust request and...
// 		test    dword ptr [ecx],eax     ; ...probe it
// 		cmp     eax,_PAGESIZE_          ; more than one page requested?
// 		jae     short probepages        ; no
// lastpage:
// 		sub     ecx,eax                 ; move stack down by eax
// 		mov     eax,esp                 ; save current tos and do a...
// 		test    dword ptr [ecx],eax     ; ...probe in case a page was crossed
// 		mov     esp,ecx                 ; set the new stack pointer
// 		mov     ecx,dword ptr [eax]     ; recover ecx
// 		mov     eax,dword ptr [eax + 4] ; recover return address
// 		push    eax                     ; prepare return address
// 		ret
// 	}
// }

int UnicodeStrCpy(PWSTR szBuffer,PUNICODE_STRING pUnicodeString,int MaxLength)
{
	if(szBuffer == NULL || MaxLength<=0 || pUnicodeString==NULL || pUnicodeString->Buffer==NULL || pUnicodeString->Length<=0)
	{
		*szBuffer=0;
		return 0;
	}
	if(MaxLength>pUnicodeString->Length/2)
	{
		MaxLength = pUnicodeString->Length/2;
		memcpy(szBuffer,pUnicodeString->Buffer,pUnicodeString->Length);
	}
	else
	{
		MaxLength--;
		memcpy(szBuffer,pUnicodeString->Buffer,MaxLength*2);
	}
	szBuffer[MaxLength] = 0;
	return MaxLength;
}

