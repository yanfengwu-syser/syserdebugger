#include "StdAfx.h"
#include "Services.h"
// 
// 
//  __declspec(naked) void Int06Proc()
//  {
//  	__asm
//  	{
// 		push dword ptr 0x6 
// 		call SaveExceptionRegister
// 		lea esp,[esp+4]
// 		pushfd
// 		pushad
// 		mov ebp,esp
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