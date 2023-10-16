#include "stdafx.h"
#include "int0xd.h"
#include "Syser.h"

bool Int0dHandle(DWORD *StackPointer)
{
	DWORD begin,end;
	
	begin = (DWORD)SyserPrivateReadByte;
	end =(DWORD) SyserPrivateReadError;
	if(StackPointer[0]>begin&&StackPointer[0]<end)
	{
		StackPointer[0]=(DWORD)SyserPrivateReadError;
		return true;
	}
	begin = (DWORD)SyserPrivateWriteByte;
	end =(DWORD) SyserPrivateWriteError;
	if(StackPointer[0]>begin&&StackPointer[0]<end)
	{
		StackPointer[0]=(DWORD)SyserPrivateWriteError;
		return true;
	}

	begin = (DWORD)SyserPrivateReadMSR;
	end =(DWORD) SyserPrivateReadMSRError;
	if(StackPointer[0]>begin&&StackPointer[0]<end)
	{
		StackPointer[0]=(DWORD)SyserPrivateReadMSRError;
		return true;
	}

	begin = (DWORD)SyserPrivateWriteMSR;
	end =(DWORD) SyserPrivateWriteMSRError;
	if(StackPointer[0]>begin&&StackPointer[0]<end)
	{
		StackPointer[0]=(DWORD)SyserPrivateWriteMSRError;
		return true;
	}
	begin = (DWORD)SyserPrivateGetTSC;
	end =(DWORD) SyserPrivateGetTSCError;
	if(StackPointer[0]>begin&&StackPointer[0]<end)
	{
		StackPointer[0]=(DWORD)SyserPrivateGetTSCError;
		return true;
	}
	begin = (DWORD)SyserDetectLastBranchType;
	end =(DWORD) InitBranchMointer;
	if(StackPointer[0]>begin&&StackPointer[0]<end)
	{
		StackPointer[0]=StackPointer[0]+2;
		return true;
	}
	return false;
}

// 
// 
// __declspec(naked) void	Int0dProc()
// {
// 	DWORD* Int0dStackPointer;
// 	__asm
// 	{
// 		push dword ptr 0xd 
// 		call SaveExceptionRegister
// 		lea esp,[esp+4]//;丢掉 push dword ptr 0xd
// 		pushfd
// 		pushad
// 		push ds
// 		push es
// 		push fs
// 		mov eax,0x23
// 		mov ds,ax
// 		mov es,ax
// 		mov eax,0x30 
// 		mov fs,ax
// 		mov ebp,esp
// 		lea esp,[esp-4]
// 		mov Int0dStackPointer,ebp
// 		/*
// 		eflags         [ebp+40]          
// 		cs             [ebp+3c]
// 		eip            [ebp+38]          
// 		errorcode      [ebp+34]          
// 		winorgintd     [ebp+30]          
// 		eflags         [ebp+2c]          
// 		eax            [ebp+28]          
// 		ecx            [ebp+24]
// 		edx            [ebp+20]          
// 		ebx            [ebp+1c]          
// 		esp            [ebp+18]          
// 		ebp            [ebp+14]          
// 		esi            [ebp+10]
// 		edi            [ebp+c]
// 		ds             [ebp+8]
// 		es             [ebp+4]
// 		fs             [ebp+0]
// 		*/
// 		add Int0dStackPointer,0x38
// 	}	
// 	
// 	if(Int0dHandle(Int0dStackPointer))
// 	{  
// 		__asm
// 		{
// 			lea esp,[esp+4]  //这里是丢掉 Int0dStackPointer 局部变量
// 			pop fs
// 			pop es
// 			pop ds
// 			popad   
// 			popfd
// 			lea esp,[esp+8]   //;code error;windows return address
// 			iretd
// 		}
// 	}
// 	__asm
// 	{
// 		lea esp,[esp+4]
// 		pop fs
// 		pop es
// 		pop ds
// 		popad
// 		popfd
// 		ret
// 	}
// }
