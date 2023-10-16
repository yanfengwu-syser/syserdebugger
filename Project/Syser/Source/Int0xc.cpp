#include "StdAfx.h"
#include "Services.h"

// 
// __declspec(naked) void Int0cProc()
// {
// 	__asm
// 	{
// 		push dword ptr 0xc
// 		call SaveExceptionRegister
// 		lea esp,[esp+4]
// 		pushfd
// 		pushad
// 		mov ebp,esp
// 		push ds
// 		push es
// 		push fs
// 		mov ax,0x23
// 		mov ds,ax
// 		mov es,ax
// 		mov ax,0x30
// 		mov fs,ax
// 	}
// 	__asm
// 	{
// 		pop fs
// 		pop es
// 		pop ds
// 		popad
// 		popfd
// 		ret
// 	}
// }