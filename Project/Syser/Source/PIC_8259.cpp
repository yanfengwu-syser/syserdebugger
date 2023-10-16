#include "StdAfx.h"
#include "PIC_8259.h"

#ifdef __cplusplus
extern "C" {
#endif

BYTE gdwPIC8259Shield_1=0;
BYTE gdwPIC8259Shield_2=0;

#ifdef __cplusplus
}; // extern "C"
#endif
// 
// void EnablePIC8259HardWareInterrupt(DWORD arg)
// {
// 	if(arg < 0x8)
// 	{
// 		__asm{
// 			push ebx
// 			push eax
// 			mov ebx, arg
// 			in al,0x21
// 			push ecx
// 			mov ecx, 0x100
// local_1:				
// 			loop local_1
// 			pop ecx
// 			btr eax,ebx
// 			out 0x21,al
// 			push ecx
// 			mov ecx,0x100
// local_2:				
// 			loop local_2
// 			pop ecx	
// 			pop eax 
// 			pop ebx
// 		}
// 	}
// 	else
// 	{
// 		arg -= 8;
// 		__asm{
// 			push ebx 
// 			push eax 
// 			push ecx
// 			mov ebx, arg
// 			in al,0xa1
// 			mov ecx,0x100
// local_3:				
// 			loop local_3
// 			btr eax,ebx
// 			out 0xa1,al
// 			mov ecx,0x100
// local_4:				
// 			loop local_4
// 			in al,0x21
// 			mov ecx,0x100
// local_5:
// 			loop local_5
// 			and al,0xfb
// 			out 0x21,al
// 			mov ecx,0x100
// local_6:				
// 			loop local_6
// 			pop ecx
// 			pop eax 
// 			pop ebx
// 		}
// 	}
// }
// void Set8259EOI(DWORD dwInterruptNum)
// {
// 	if(dwInterruptNum < 0x10)
// 	{
// 		if(dwInterruptNum >= 8)
// 		{
// 
// 			__asm{
// 				push eax 
// 				push ecx
// 				mov eax, dwInterruptNum
// 				sub eax,8
// 				add eax,0x60
// 				out 0xa0,al	
// 				
// 				mov ecx,0x200
// local_2:		
// 				loop local_2	
// 				mov al,0x62
// 				out 0x20,al
// 				mov ecx,0x200
// local_3:
// 				loop local_3
// 				pop ecx
// 				pop eax
// 			}
// 		}
// 		else
// 		{
// 			__asm
// 			{
// 				push eax
// 				mov eax,dwInterruptNum
// 				add eax,0x60
// 				out 0x20,al
// 				push ecx
// 				mov ecx,0x200
// local_1:		
// 				loop local_1
// 				pop ecx
// 				pop eax
// 			}
// 		}
// 	}
// }