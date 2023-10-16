#include "stdafx.h"
#include "HardWareInterruptCtrl.h"
#include "LocalAPIC.h"
#include "IOAPIC.h"
#include "PIC_8259.h"

#ifdef __cplusplus
extern "C" {
#endif

bool gbIsSaveInterruptShieldRegister=false;

#ifdef __cplusplus
}; // extern "C"
#endif

// void DisableAllHardInterrupt()
// {
// 	__asm pushad
// 	if(!gbIsSaveInterruptShieldRegister)
// 	{
// 		if(gbIsUseAPIC)
// 		{
// 			__asm
// 			{
// 				
// 				mov eax,gdwLocalAPICLineAddress
// 				mov eax,[eax+0x80]
// 				mov gdwLocalAPICTaskPriority,eax
// 				
// 			}
// 			SaveIOAPICInterruptVectorTable();
// 		}
// 		else
// 		{
// 			__asm
// 			{
// 				
// 				in  al,0x21
// 				mov gdwPIC8259Shield_1,al				
// 				mov ecx,0x100
// local_1:
// 				loop local_1
// 				in al,0xa1
// 				mov gdwPIC8259Shield_2,al
// 				mov ecx,0x100
// local_2:
// 				loop local_2
// 			}
// 		}
// 		gbIsSaveInterruptShieldRegister=true;
// 	}
// 
// 	if(gbIsUseAPIC)
// 	{
// 		__asm
// 		{
// 			
// 			mov eax,gdwLocalAPICLineAddress
// 			mov dword ptr [eax+0x80],0xff
// 			
// 		}	
// 	}
// 	else
// 	{	
// 		__asm
// 		{
// 			
// 			mov al,0xff
// 			out 0x21,al
// 			mov ecx,0x100
// local_3:		
// 			loop local_3			
// 			out 0xa1,al			
// 			mov ecx,0x100
// local_4:		
// 			loop local_4	
// 			in al,0x21
// 			mov ecx,0x100
// local_5:
// 			loop local_5
// 			in al,0xa1
// 			mov ecx,0x100
// local_6:
// 			loop local_6
// 			
// 		}	
// 	}
// 	__asm popad
// }
// 
// __declspec (naked)void EnableAllHardInterrupt()
// {
// 	__asm
// 	{
// 		pushad
// 		push ds
// 		push es 
// 		mov ax,0x23 
// 		mov ds,ax 
// 		mov es,ax
// 	}
// 	if(gbIsSaveInterruptShieldRegister)
// 	{
// 		if(gbIsUseAPIC)
// 		{
// 			RestoreIOAPICInterruptVectorTable();
// 			__asm{			
// 				mov eax,gdwLocalAPICLineAddress
// 				mov ebx,gdwLocalAPICTaskPriority
// 				mov [eax+0x80],ebx			
// 			}			
// 		}
// 		else
// 		{		
// 			__asm{			
// 				mov al,gdwPIC8259Shield_1
// 				out 0x21,al				
// 				mov ecx,0x100
// local_1:
// 				loop local_1				
// 				mov al,gdwPIC8259Shield_2
// 				out 0xa1,al				
// 				mov ecx,0x100
// local_2:			
// 				loop local_2				
// 			}
// 		}
// 		gbIsSaveInterruptShieldRegister=false;
// 	}	
// 	__asm{
// 		pop es
// 		pop ds
// 		popad
// 		ret
// 	}
// }

void EnableHardWareInterrupt(int arg)
{
	if(arg<0x10)
	{
		if(gbIsUseAPIC)
			EnableAPICHardWareInterrupt(arg);
		else
			SyserEnablePIC8259HardWareInterrupt(arg);
	}
}

DWORD GetHardwareInterruptVectorNum(DWORD dwNum)
{
	if(!gbIsUseAPIC)
	{
		if(dwNum < 16)
			return 0x30+dwNum;	
		return 0;
	}
	return GetIOAPICInterruptVector(dwNum);
}


void SetInteruptEOI(DWORD dwInterruptNum)
{
	DWORD* dwTemp;
	
	if(gbIsUseAPIC)
	{
		SetLocalAPICEOI(dwInterruptNum)	;
	}
	else
	{
		SyserSet8259EOI(dwInterruptNum);
	}				
}