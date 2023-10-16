#include "StdAfx.h"
#include "Services.h"

// 
// __declspec(naked) void Int0bProc()
// {
// 	__asm
// 	{
// 		push dword ptr 0xb
// 		call SaveExceptionRegister
// 		lea esp,[esp+4]
// 		pushfd
// 		pushad
// 		push ds
// 		push es
// 		push fs
// 		mov eax,0x23
// 		mov ds,ax
// 		mov es,ax
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