#include "StdAfx.h"
#include "Syser.h"


void FlushVirtualPCScreenBuffer(int nleft,int ntop,int nright,int nbottom)
{
	__asm
	{
		pushad 
		mov eax,nleft 
		mov ebx,ntop
		mov ecx,nright
		mov edx,nbottom
		__emit (0xf)
		__emit (0x3f)
		__emit (0x1)
		__emit (0x12)
		popad
	}
}


bool gInVirtualPC=false;
bool VirtualPCTest()
{
	__try
	{
		__asm
		{
			pushad			
			mov  ebx, 0 // Flag
			mov  eax, 1 // VPC function number
			__emit 0Fh
			__emit 3Fh
			__emit 07h
			__emit 0Bh
			test ebx, ebx
			jnz local_001
			mov gInVirtualPC,1
local_001:
			popad
		}

	}
	__except(EXCEPTION_EXECUTE_HANDLER)
	{
		gInVirtualPC=false;
	}
	if(gInVirtualPC)
		DbgPrint("Syser : Host machine is VirtualPC !\n");
	return gInVirtualPC;
}