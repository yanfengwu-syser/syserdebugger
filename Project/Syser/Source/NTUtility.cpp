#include "StdAfx.h"
#include "NTUtility.h"
#include "X86Optr.h"

WORD NTAllocSelector(DWORD Base,DWORD Limit,BYTE bCodeSeg,BYTE bWritable,BYTE bSeg32,BYTE bDplDwon)
{
	SEG_DESCRIPTOR	seg;
    WORD			Selectors;
    seg.limit_0_15 = LOW_WORD(Limit);
    seg.base_0_15 = LOW_WORD(Base); 
    seg.base_16_23 = LOW_BYTE(HIGH_WORD(Base));
    seg.accessed = 0;
	seg.readwrite = bWritable;
    seg.conforming = bDplDwon;
    seg.code_data = bCodeSeg;
    seg.app_system = 1;
    seg.dpl = 0;
    seg.present = 1;
    seg.limit_16_19 = LOW_BYTE(HIGH_WORD(Limit)) & 0xF;
    seg.always_0 = 0;
    seg.seg_16_32 = bSeg32;
    seg.granularity = 1;
    seg.base_24_31 = HIGH_BYTE(HIGH_WORD(Base));
	KeI386AllocateGdtSelectors(&Selectors,1);
	KeI386SetGdtSelector(Selectors,&seg);
	return Selectors;
}

void NTReleaseSelector(WORD Selectors)
{
	KeI386ReleaseGdtSelectors(&Selectors,1);
}

BYTE ReadVideoCRTRegByte(BYTE Index)
{
	BYTE Result;
// 	__asm
// 	{
// 		mov al,Index
// 		mov dx,0x3D4
// 		out dx,al
// 		mov dx,0x3D5
// 		in  al,dx
// 		mov Result,al
// 	}

	SyserWritePortByte(0x3D4,Index);
	Result = SyserReadPortByte(0x3D5);

	return Result;
}

BYTE ReadCmosRegister(BYTE Index)
{
	BYTE Result;
// 	__asm
// 	{
// 		mov al,Index
// 		out 0x70,al
// 		in  al,0x71
// 		mov Result,al
// 	}

	SyserWritePortByte(0x70,Index);
	Result = SyserReadPortByte(0x71);
	return Result;
}

UINT GetOSVer(ULONG* pMajorVersion,ULONG* pMinorVersion,ULONG* pBuildNumber)
{
	static UINT	OSVer=0;
	static bool bInitOsV=false;
	static ULONG MajorVersion,MinorVersion,BuildNumber;
	if(bInitOsV==false)
	{	
		PsGetVersion(&MajorVersion,&MinorVersion,&BuildNumber,NULL);
		OSVer=((MajorVersion)<<8)+(MinorVersion);
		bInitOsV=true;
	}
	*pMajorVersion=MajorVersion;
	*pMinorVersion=MinorVersion;
	*pBuildNumber=BuildNumber;
	if(OSVer>=0x501) //ÅÐ±ðÏµÍ³.
		return DRV_OS_XP;
	else
		return DRV_OS_2K;
}

// void ResetSystem()
// {
// 	__asm
// 	{
// 		in   al, 61h	//PC/XT PPI port B 
// 		push ecx
// 		mov  ecx, 20
// this_label1:				//CODE XREF: hboot+8j
// 		loop    this_label1
// 		pop     ecx
// 		or      al, 0Ch
// 		out     61h, al		//PC/XT PPI port B 
// 		push    ecx
// 		mov     ecx, 14h
// this_label2:              //CODE XREF: hboot+15j
// 		loop    this_label2
// 		pop     ecx
// 		mov     dx, 674h
// 		mov     al, 0
// 		out     dx, al
// 		mov     dx, 670h
// 		out     dx, al
// 		mov     al, 0FEh
// 		out     64h, al //AT Keyboard controller 8042.
// 						//Resend the last transmission
// 		mov     ecx,600000h
// this_label3:
// 		loop    this_label3
// 	}
// }

char WaitForKey()
{
	char res;
// 	__asm
// 	{
// local_loop:
// 		in al,0x64
// 		test al,1
// 		jz local_loop
// 		in al,0x60
// 		mov res,al
// 	}

	while(SyserReadPortByte(0x64) == 0);
	res = SyserReadPortByte(0x60);

	return res;
}


void Beep(DWORD Counter,DWORD frequency)
{
	BYTE Port61Value;
//     __asm
// 	{
// 		push eax 
// 		push ebx
// 		push ecx 
// 		in al,0x61
// 		mov Port61Value,al
// 		and al,0xfe
// 		out 0x61,al
// 		mov ecx,frequency		
// 		mov al,0xb6
// 		out 0x43,al 
// 		mov al,cl
// 		out 0x42,al 
// 		jmp local_2
// local_2:
// 		mov al,ch
// 		out 0x42,al 		
// 		in al,0x61
//         or al,3
// 		out 0x61,al
// 		mov ebx,Counter
// local_1:
// 		in al,0x61
// 		test al,0x20
// 		jnz local_1
// 		dec ebx 
// 		jz local_3
// local_4:
// 		in al,0x61
// 		test al,0x20 
// 		jz local_4
// 		jmp local_1
// local_3:
// 		mov al,Port61Value
// 		out 0x61,al 
// 		pop ecx
// 		pop ebx
// 		pop eax
// 	}

	Port61Value = SyserReadPortByte(0x61);
	SyserWritePortByte(0x61,Port61Value&0xfe);
	SyserWritePortByte(0x43,0xb6);
	SyserWritePortByte(0x42,(BYTE)frequency);
	SyserWritePortByte(0x42,(BYTE)((frequency&0xff00)>>8));
	SyserWritePortByte(0x61,SyserReadPortByte(0x61)|3);

	do 
	{
		while(SyserReadPortByte(0x61)&0x20);

		Counter--;
		if (!Counter)
		{
			break;
		}

		while(SyserReadPortByte(0x61)&0x20);
	} while (TRUE);

	SyserWritePortByte(0x61,Port61Value);
}

ULSIZE	GetVirtualAddressBlockSize(ULPOS Address)
{
	ULSIZE Size=0;
	Address&=MP_NOT_MASK;
	while(MmIsAddressValid((void*)Address))
	{
		Address+=MP_SIZE;
		Size+=MP_SIZE;
	}
	return Size;
}

// void* GetCurrentPEB()
// {
// 	void*pPEB;
// 	__asm
// 	{
// 		mov eax,fs:[0x30]
// 		mov pPEB,eax
// 	}
// 	return pPEB;
// }


bool IsAddressValid(void* Addr)
{
	return MmIsAddressValid(Addr)!=0;
}

