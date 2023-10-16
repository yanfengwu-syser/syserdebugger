#include "StdAfx.h"
#include "X86Optr.h"
#include "Syser.h"
#include "Services.h"
#include "IOAPIC.h"

#ifdef __cplusplus
extern "C" {
#endif

X86_REG_CONTEXT	Reg;
X86_REG_CONTEXT	PrevReg;
X86_REG_CONTEXT gExceptionReg;
X86_REG_CONTEXT* ExceptionReg=&gExceptionReg;
X86_REG_CONTEXT ReadOnlyActiveReg;
RETURN_CONTEXT  ReturnContext;
DWORD			ExceptionInterruptNum;
DWORD			ExceptionInterruptErrorCode;
DWORD			GeneralReg[8];
SAVELOCALAPIC*	gpMCPULocalApic=NULL;
X86_REG_CONTEXT*gpMCPUReg=NULL;
//REG32	CR0Backup=0;
bool	gbHaveLastBranchMointer = false;
DWORD	dwLastBranchFromEIP;
DWORD	dwLastBranchToEIP;
DWORD	dwLastIntFromEIP;
DWORD	dwLastIntToEIP;

BYTE gIRQLLevel[16]={
	0x0,
	0xff,
	0xff,
	0x1,
	0x2,	
	0x4,
	0x5,
	0x6,
	0x7,
	0x8,
	0x9,
	0xa,
	0x1b,
	0x1c,
	0x1d,
	0x1e
};

#ifdef __cplusplus
}; // extern "C"
#endif


BYTE GetCurrentIRQLLevel()
{
	DWORD Limit;
	DWORD BaseAddress;
	BYTE Level;
	if(gbIsUseAPIC)
	{
		return gIRQLLevel[(gdwLocalAPICTaskPriority>>4)&0xf];
	}
	else
	{
		BaseAddress = GetSegmentBaseAddress((WORD)gSystemFSRegisterSelector,&Limit);
		BaseAddress+=0x24;
		Level = ReadByteDefaultValue((void*)BaseAddress,0xff);
	}
	return Level;
}
DWORD GetCPU_ID()
{
	CPUID_INFO Info;
	SyserGetCPUID(&Info,1);
	return (Info.dwEBX >>24);
}
//////////////////////////////////////////////////////////////////////////////////////
//CPUID
//
CPUID_INFO*gpCPUIDInfo=NULL;
DWORD gMaxCPUIDIndex = 0;
// 
// void GetCPUID(CPUID_INFO *pCPUInfo,DWORD dwIndex)
// {
// 	__asm
// 	{
// 		pushad
// 		pushfd
// 		mov eax,dwIndex
// 		cpuid
// 		mov esi,pCPUInfo
// 		mov [esi],eax
// 		mov [esi+4],ebx
// 		mov [esi+8],ecx
// 		mov [esi+12],edx
// 		popfd
// 		popad
// 	}
// }

// __declspec(naked) DWORD GetCPUIDMaxIndex()
// {
// 	__asm
// 	{
// 		PUSHAD
// 		PUSHFD
// 		MOV EAX,0
// 		CPUID
// 		MOV [esp+0x20],eax
// 		POPFD
// 		POPAD
// 		ret
// 	}
// }

CPUID_INFO*InitCPUIDInfo()
{
	if(SyserIsSupportCPUIDInstruction()==false)
		return NULL;
	gMaxCPUIDIndex=SyserGetCPUIDMaxIndex();
	if(gMaxCPUIDIndex==0||gMaxCPUIDIndex>0x10)
		return NULL;
	gpCPUIDInfo=new CPUID_INFO[gMaxCPUIDIndex+1];
	for(DWORD i = 0; i <= gMaxCPUIDIndex;i++)
		SyserGetCPUID(&gpCPUIDInfo[i],i);
	return gpCPUIDInfo;
}

void ReleaseCPUIDInfo(CPUID_INFO*pCPUIDInfo)
{
	if(pCPUIDInfo==NULL)
		pCPUIDInfo = gpCPUIDInfo;
	if(pCPUIDInfo)
		delete []pCPUIDInfo;
	pCPUIDInfo=NULL;
}

// bool IsSupportCPUIDInstruction()
// {
// 	static bool bInit = false;
// 	static bool bHaveCPUIDInstruction = false;
// 	if(bInit==false)
// 	{
// 		__asm
// 		{
// 			PUSHAD
// 			PUSHFD
// 			MOV		EAX,[ESP]
// 			MOV		EBX,EAX
// 			XOR		EAX,0X200000
// 			PUSH	EAX
// 			POPF
// 			PUSHF
// 			POP		EAX
// 			XOR		EAX,EBX
// 			MOV		EAX,0
// 			JZ		ExitFunc
// 			CPUID
// 			CMP		EAX,1
// 			JNB		Success
// 			MOV		bHaveCPUIDInstruction,0
// 			JMP		ExitFunc
// Success:
// 			MOV		bHaveCPUIDInstruction,1
// ExitFunc:		
// 			POPFD
// 			POPAD		
// 		}
// 		bInit = true;
// 	}
// 	return bHaveCPUIDInstruction;
// }

//
//CPUID
//////////////////////////////////////////////////////////////////////////////////////



// 
// __declspec(naked) __int64 __stdcall PrivateReadMSR(DWORD dwIndex)
// {
// 	__asm
// 	{
// 		mov ecx,[esp+4]
// 		rdmsr
// 		clc
// 		ret 4
// 	}
// }


// __declspec(naked) __int64 __stdcall PrivateReadMSRError()
// {
// 	__asm
// 	{
// 		stc 
// 		ret 4
// 	}
// }
// ;


// __declspec(naked) void __stdcall PrivateWriteMSR(DWORD dwIndex,DWORD dwValueLow,DWORD dwValueHigh)
// {
// 	__asm
// 	{
// 		mov ecx,[esp+4]
// 		mov eax,[esp+8]
// 		mov edx,[esp+0xc]
// 		wrmsr
// 		clc
// 		ret 0xc
// 	}
// }
// __declspec(naked) void __stdcall PrivateWriteMSRError()
// {
// 	__asm
// 	{
// 		stc 
// 		ret 0xc
// 	}
// }

// bool ReadMSR(DWORD dwIndex,DWORD *dwHigh,DWORD *dwLow)
// {
// 	DWORD dwTmpHigh,dwTmpLow,dwRetValue=0;
// 	if(IsSupportRDMSRInstruction()==FALSE)
// 		return FALSE;
// 	__asm
// 	{
// 		pushad				
// 		mov ecx,dwIndex
// 		push ecx 
// 		call SyserPrivateReadMSR
// 		jb local_1 		
// 		mov dwTmpHigh,edx
// 		mov dwTmpLow,eax
// 		mov eax,1 
// 		mov dwRetValue,eax
// 		jmp local_2
// local_1:
// 		mov eax,0 
// 		mov dwRetValue,eax
// local_2:
// 		popad
// 	}
// 	*dwHigh=dwTmpHigh;
// 	*dwLow=dwTmpLow;
// 	return dwRetValue==1;
// }


// __declspec(naked) __int64 __stdcall PrivateGetTSC()
// {
// 	__asm
// 	{
// 		rdtsc
// 		clc
// 		ret 
// 	}
// }
// 
// 
// __declspec(naked) __int64 __stdcall PrivateGetTSCError()
// {
// 	__asm
// 	{
// 		stc 
// 		ret 
// 	}
// }

// __declspec(naked)ULONGLONG GetTSC()
// {
// 	__asm
// 	{
// 		call PrivateGetTSC
// 		ret
// 	}
// }

// bool ReadTSC(ULONGLONG *llValue)
// {
// 	DWORD dwHigh,dwLow,dwRetValue;
// 	__asm{		
// 		push eax 
// 		push edx
// 		call PrivateGetTSC
// 		jb local_001 
// 		mov dwHigh,edx
// 		mov dwLow,eax
// 		mov eax,1
// 		mov dwRetValue,eax
// 		jmp local_002
// local_001:
// 		mov eax,0
// 		mov dwRetValue,eax
// local_002:
// 		pop edx 
// 		pop eax
// 		
// 	}
// 	*llValue=dwHigh;
// 	*llValue<<=32;
// 	*llValue|=dwLow;
// 	return dwRetValue==1;
// }
// bool WriteMSR(DWORD dwIndex,DWORD dwHigh,DWORD dwLow)
// {
// 	DWORD dwRetValue;
// 	if(IsSupportRDMSRInstruction()==FALSE)	
// 		return FALSE;	
// 	__asm{
// 		pushad
// 		push edx
// 		push eax 
// 		push ecx
// 		call SyserPrivateWriteMSR
// 		mov eax,1 
// 		jnb local_001
// 		dec eax
// local_001:		
// 		mov dwRetValue,eax
// 		popad
// 	}
// 	return dwRetValue==1;
// }

bool SetBranchStepRun()
{
	DWORD dwHigh,dwLow;
	if(gbHaveLastBranchMointer==false)
		return false;
	SyserReadMSR(0x1d9,&dwHigh,&dwLow);
	dwLow |= 2;
	SyserWriteMSR(0x1d9,dwHigh,dwLow);
	return true;
}
bool ClearBranchStepRun()
{
	DWORD dwHigh,dwLow;
	if(gbHaveLastBranchMointer==false)
		return false;
	SyserReadMSR(0x1d9,&dwHigh,&dwLow);
	dwLow &= 0xfffffffd;
	SyserWriteMSR(0x1d9,dwHigh,dwLow);
	return true;
}

#define 	PDEBase		((DWORD*)0xC0300000)
#define 	PTEBase		((DWORD*)0xC0000000)

DWORD GetTSSBase(DWORD *pTSSSize,DWORD dwSelector)
{
	VADDR32 dwGDTBase = 0;
	DWORD dwGDTSize = 0;
	DWORD dwTSSBase = 0;
	DWORD dwSize = 0;
	X86_SEGMENT_DESCRIPTOR *pSegDesc;

	if(dwSelector == 0)
		dwSelector = SyserGetTSSSelector();
	if(dwSelector & 4)
		dwGDTBase = GetLDTBase(&dwGDTSize);
	else
		dwGDTBase = SyserGetGDTBase(&dwGDTSize);
	
	if(dwGDTBase && ((dwSelector & 0xfffffff8) < dwGDTSize))
	{
		pSegDesc = (X86_SEGMENT_DESCRIPTOR *)(dwGDTBase+(dwSelector & 0xfffffff8));
		if(pSegDesc->P && (!pSegDesc->DT) && 
			(pSegDesc->TYPE == SYS_SEG_GATE_DECR_TYPE_16TSS_AVAIL ||
			pSegDesc->TYPE == SYS_SEG_GATE_DECR_TYPE_16TSS_BUSY ||
			pSegDesc->TYPE == SYS_SEG_GATE_DECR_TYPE_32TSS_AVAIL ||
			pSegDesc->TYPE == SYS_SEG_GATE_DECR_TYPE_32TSS_BUSY))
		{
			dwTSSBase = (pSegDesc->base_H1 << 24) | (pSegDesc->base_H0 << 16) | (pSegDesc->base_L1 << 8) | pSegDesc->base_L0;
			dwSize = (pSegDesc->limit_H << 16) | (pSegDesc->limit_L1 << 8) | (pSegDesc->limit_L0);
		}
	}
	if(pTSSSize)
		*pTSSSize = dwSize;
	return dwTSSBase;
}

// DWORD GetTSSSelector()
// {
// 	DWORD dwTSSSelector;
// 	__asm
// 	{
// 		xor eax,eax
// 		str ax
// 		mov dwTSSSelector,eax
// 	}
// 	return dwTSSSelector;
// }

// DWORD GetLDTSelector()
// {
// 	DWORD dwLDTSelector;
// 	__asm
// 	{
// 		xor eax,eax
// 		sldt ax
// 		mov dwLDTSelector,eax
// 	}
// 	return dwLDTSelector;
// }

// VADDR32 GetIDTBase(DWORD *dwIdtSize)
// {
// 	BYTE SIDTBffer[8];
// 	VADDR32 IDTBase;
// 	__asm
// 	{
// 		push esi
// 		lea  esi,SIDTBffer
// 		sidt [esi]
// 		pop  esi
// 	}
// 	IDTBase = *(VADDR32*)&SIDTBffer[2];
// 	if(dwIdtSize)
// 		*dwIdtSize = (DWORD)*(WORD*)SIDTBffer;
// 	return IDTBase;
// }

VADDR32 GetLDTBase(DWORD *dwLdtSize,DWORD dwLdtSelector)
{
	VADDR32 LDTBase = 0;
	VADDR32 GDTBase,GDTSize;
	X86_SEGMENT_DESCRIPTOR *pSegDesc;
	DWORD dwSize = 0;

	if(dwLdtSize)
		*dwLdtSize = 0;
// 	__asm{
// 		cmp dwLdtSelector,0
// 		mov eax,dwLdtSelector
// 		jnz local_1
// 		sldt ax
// 		mov dwLdtSelector,eax
// local_1:
// 		lsl eax,eax
// 		jnz local_2
// 		mov dwSize,eax
// local_2:
// 	}

	SyserGetLDTSelectorBySelector(&dwLdtSelector,&dwSize);

	if(dwSize)
	{
		GDTBase = SyserGetGDTBase(&GDTSize);
		if(dwLdtSelector <= GDTSize)
		{
			pSegDesc = (X86_SEGMENT_DESCRIPTOR *)(GDTBase + (dwLdtSelector & 0xfff8));
			if((!pSegDesc->DT) && pSegDesc->TYPE == SYS_SEG_GATE_DECR_TYPE_LDT)
			{
				LDTBase = (pSegDesc->base_H1 << 24) | (pSegDesc->base_H0 << 16) | (pSegDesc->base_L1 << 8) | (pSegDesc->base_L0);
				if(dwLdtSize)
					*dwLdtSize = dwSize;
			}
		}
	}
	return LDTBase;
}

// VADDR32 GetGDTBase(DWORD *dwGdtSize)
// {
// 	VADDR32 GDTBase;
// 	DWORD dwSize;
// 	__asm
// 	{
// 		sub esp,6
// 		sgdt [esp]
// 		movzx eax,word ptr[esp]
// 		mov dwSize,eax
// 		lea esp,[esp+2]
// 		pop eax
// 		mov GDTBase,eax
// 	}
// 	if(dwGdtSize)
// 		*dwGdtSize = dwSize;
// 	return GDTBase;
// }

// SELECTOR GetCurCSeg()
// {
// 	SELECTOR CSeg;
// 	__asm
// 	{		
// 		xor eax,eax
// 		mov ax,cs
// 		mov CSeg,ax
// 	}
// 	return CSeg;
// }

// SELECTOR GetCurDSeg()
// {
// 	SELECTOR DSeg;
// 	__asm
// 	{		
// 		mov ax,ds
// 		mov DSeg,ax
// 	}
// 	return DSeg;
// }
// 
// REG32 GetCR0Reg()
// {
// 	REG32 uReg;
// 	__asm
// 	{
// 		mov eax,cr0
// 		mov uReg,eax
// 	}
// 	return uReg;
// }

// void SetCR0Reg(IN REG32 uReg)
// {
// 	__asm
// 	{
// 		Push EAX 
// 		mov eax,uReg
// 		mov cr0,eax
// 		POP EAX
// 	}
// }

// REG32 GetCR3Reg()
// {
// 	REG32 uReg;
// 	__asm
// 	{
// 		mov eax,cr3
// 		mov uReg,eax
// 	}
// 	return uReg;
// }
// 
// void SetCR3Reg(IN REG32 uReg)
// {
// 	__asm
// 	{
// 		Push EAX 
// 		mov eax,uReg
// 		mov cr3,eax
// 		POP EAX
// 	}
// }

// void ClrCR0WP()
// {
// 	if(CR0Backup&0x80000000)
// 	{
// 		__asm
// 		{
// 			push eax
// 			mov eax,cr0 
// 			and eax,0xFFFEFFFF
// 			mov cr0,eax
// 			pop eax 
// 		}
// 		return;
// 	}
// 	
// 	__asm
// 	{
// 		Push EAX 
// 		mov eax,cr0
// 		mov CR0Backup,eax
// 		and eax,0xFFFEFFFF
// 		mov cr0,eax
// 		POP EAX
// 	}
// }

// void SetCR0WP()
// {
// 	__asm
// 	{
// 		Push EAX 
// 		mov eax,cr0
// 		mov CR0Backup,eax
// 		or  eax,0x10000
// 		mov cr0,eax
// 		POP EAX
// 	}
// }

// void RestoreCR0()
// {
// 	if(CR0Backup&0x80000000)
// 	{	
// 		_asm
// 		{
// 			Push EAX 
// 			mov eax,CR0Backup
// 			mov cr0,eax
// 			POP EAX
// 		}
// 		CR0Backup=0;
// 	}
// }

// DWORD ClearCR0WP()
// {
// 	DWORD OldCR0;
// 	__asm
// 	{
// 		mov eax,cr0
// 		push eax 
// 		and eax,0xFFFEFFFF
// 		mov cr0,eax 
// 		pop eax
// 		mov OldCR0,eax
// 	}
// 	return OldCR0;
// }

// void RestoreCR0WP(DWORD dwCR0)
// {
// 	__asm
// 	{
// 		push eax
// 		mov eax,dwCR0
// 		mov cr0,eax
// 		pop eax
// 	}
// }

// REG32 GetDRX(IN UINT ID)
// {
// 	REG32 DRReg=0;
// 	switch(ID)
// 	{
// 	case 0:
// 		__asm mov eax,dr0
// 		break;
// 	case 1:
// 		__asm mov eax,dr1
// 		break;
// 	case 2:
// 		__asm mov eax,dr2
// 		 break;
// 	case 3:
// 		__asm mov eax,dr3
// 		 break;
// 	case 6:
// 		__asm mov eax,dr6
// 		 break;
// 	case 7:
// 		__asm mov eax,dr7
// 		 break;
// 	}
// 	__asm mov DRReg,eax
// 	return DRReg;
// }

// void SetDRX(IN UINT ID,IN REG32 Reg1)
// {
// 	__asm{
// 		push eax 
// 		push ecx
// 		mov eax,Reg1
// 		mov ecx,ID 
// 		cmp ecx,6 
// 		jnz local_001
// 		mov dr6,eax
// 		jmp local_quit
// local_001:
// 		cmp ecx,7
// 		jnz local_002
// 		mov dr7,eax
// 		jmp local_quit
// local_002:
// 		cmp ecx,0
// 		jnz local_003
// 		mov dr0,eax 
// 		jmp local_quit
// local_003:
// 		cmp ecx,1 
// 		jnz local_004
// 		mov dr1,eax 
// 		jmp local_quit
// local_004:
// 		cmp ecx,2 
// 		jnz local_005 
// 		mov dr2,eax 
// 		jmp local_quit
// local_005:
// 		cmp ecx,3
// 		jnz local_quit
// 		mov dr3,eax 
// local_quit:
// 		pop ecx 
// 		pop eax
// 	}
// }

bool MapToPAddr(IN ULPOS Address,OUT ULONGLONG*pResult)
{
	DWORD PV,HighDD,dwTmp;
	DWORD*PDE=(DWORD*)0xC0300000;
	DWORD*PTE=(DWORD*)0xC0000000;
	CR4REGISTER stCR4;
	CPUID_1_EDX_FEATURE stCPUID_1_EDX;
	stCPUID_1_EDX = *(CPUID_1_EDX_FEATURE*)&gpCPUIDInfo[1].dwEDX;
	(DWORD&)stCR4 = GetCR4Register();
	if(stCR4.PAE)
	{
		PDE = (DWORD*)(0xC0600000+((Address >> 0x12) & 0x3ff8));
		if(ReadDword(PDE,&dwTmp)==false)
			return false;
		if((PDE[0] & 1)== 0)
			return false;
		if(PDE[0] & 0x80)//2M的页
		{
			if(pResult)
				*pResult = MAKE_QDWORD(PDE[1]&0xF,(PDE[0] & 0xffe00000) | (Address & 0x1fffff));
			return true;
		}
		else
		{
			PTE=(DWORD*)(0xC0000000+((Address >> 9) & 0x7ffff8));
			if(ReadDword(PTE,&dwTmp)==false)
				return false;
			if((PTE[0]&1)==0)
				return false;
			if(pResult)
				*pResult=MAKE_QDWORD(PTE[1]&0xF,(PTE[0] & 0xfffff000) + (Address & 0xfff));
			return true;
		}
	}
	else
	{					
		if(ReadDword(&PDE[Address>>22],&dwTmp)==false)
			return false;
		PV=PDE[Address>>22];
		if(PV&0x80)//判断是否为 4M 页面。
		{			
			if(stCR4.PSE && stCPUID_1_EDX.PSE)//判断 CPU 是否支持 4M 页面
			{	
				if(!stCPUID_1_EDX.PSE_36)
					HighDD=0;
				else
					HighDD=(PV>>13)&0xf;
				if(pResult)
					*pResult = MAKE_QDWORD(HighDD,(PV&0xFFC00000) | (Address&0x3FFFFF));
				return true;
			}
			return false;
		}	
		if(ReadDword(&PTE[Address>>12],&dwTmp)==false)
			return false;
		PV=PTE[Address>>12];
		if((PV&1)==0)
			return false;
		if(pResult)
			*pResult = (PV&0xFFFFF000) | (Address&0xFFF);
		return true;
	}
}

//取虚拟地址所对应的物理地址的连续大小
ULSIZE GetVirtualPhysSize(IN ULPOS Address,IN ULSIZE MaxSize)
{
	DWORD PV;
	DWORD dwTmp;
	ULONGLONG	PhysAddress,PrevPhysAddress;
	ULSIZE Size,PrevPageSize,PageSize;
	DWORD*PDE=(DWORD*)0xC0300000;
	DWORD*PTE=(DWORD*)0xC0000000;
	Address&=0xFFFFF000;
	CR4REGISTER stCR4;
	CPUID_1_EDX_FEATURE stCPUID_1_EDX;
	stCPUID_1_EDX = *(CPUID_1_EDX_FEATURE*)&gpCPUIDInfo[1].dwEDX;
	dwTmp = GetCR4Register();
	stCR4 = *(CR4REGISTER*)&dwTmp;
	Size = 0;
	if(stCR4.PAE)
	{
		while(Address)
		{
			PDE = (DWORD*)(0xC0600000+((Address >> 0x12) & 0x3ff8));
			if(ReadDword(PDE,&dwTmp)==false)
				return Size;
			if((PDE[0] & 1)== 0)
				return Size;
			if(PDE[0] & 0x80)
			{
				PageSize=0x200000;
				PhysAddress =MAKE_QDWORD(PDE[1],(PDE[0] & 0xffe00000) | (Address & 0x1fffff) );

				if(Size && PhysAddress!=PrevPhysAddress+PrevPageSize)
					return Size;
				PrevPhysAddress = PhysAddress;
				PrevPageSize = PageSize;
			}
			else
			{
				PTE=(DWORD*)(0xC0000000+((Address >> 9) & 0x7ffff8));
				if(ReadDword(PTE,&dwTmp)==false)
					return Size;
				if((PTE[0]&1)==0)
					return Size;
				PageSize=0x1000;
				PhysAddress =MAKE_QDWORD(PTE[1],(PTE[0] & 0xfffff000) + (Address & 0xfff));
				if(Size && PhysAddress!=PrevPhysAddress+PrevPageSize)
					return Size;
				PrevPhysAddress = PhysAddress;
				PrevPageSize = PageSize;
			}
			Address+=PageSize;
			Size+=PageSize;
			if(Size >= MaxSize)
				return Size;
		}
	}
	else
	{
		while(Address)
		{
			if(ReadDword(&PDE[Address>>22],&dwTmp)==false)
				return Size;
			PV=PDE[Address>>22];			
			if(PV&0x80)//判断是否为 4M 页面。
			{
				if(stCR4.PSE && stCPUID_1_EDX.PSE)//判断 CPU 是否支持 4M 页面
				{
					PageSize=0x400000;
					PhysAddress =MAKE_QDWORD(stCPUID_1_EDX.PSE_36? ((PV>>13)&0xf) : 0 ,(PV&0xFFC00000) | (Address&0x3FFFFF));
					if(Size && PhysAddress!=PrevPhysAddress+PrevPageSize)
						return Size;
					PrevPhysAddress = PhysAddress;
					PrevPageSize = PageSize;
				}
				else
					return Size;
			}
			else
			{
				if(ReadDword(&PTE[Address>>12],&dwTmp)==false)
					return Size;
				PV=PTE[Address>>12];
				
				if((PV&1)==0)
					return Size;
				PageSize=0x1000;
				PhysAddress = (PV&0xFFFFF000) | (Address&0xFFF);
				if(Size && PhysAddress!=PrevPhysAddress+PrevPageSize)
					return Size;
				PrevPhysAddress = PhysAddress;
				PrevPageSize = PageSize;
			}
			Address+=PageSize;
			Size+=PageSize;
			if(Size >= MaxSize)
				return Size;
		}
	}
	return Size;
}

bool MapPhysical0()
{
	DWORD dwTmp,dwTmp1;
	CR4REGISTER stCR4;
	PHYSICAL_ADDRESS PhysAddress;

	dwTmp = GetCR4Register();
	stCR4 = *(CR4REGISTER*)&dwTmp;	
	PhysAddress.QuadPart=0;
	dwPhysical_0_LinesAddress =(DWORD) MmMapIoSpace(PhysAddress,0x100000,MmNonCached);
	if(dwPhysical_0_LinesAddress==NULL)
		return false;
	if(dwPhysical_0_LinesAddress)
	{
		if(stCR4.PAE)	
		{
			OwnerPageDirItemAddress = 0xc0600000 +((dwPhysical_0_LinesAddress >> 21)<<3);
			OwnerPageTabItemAddress = 0xc0000000 +((dwPhysical_0_LinesAddress >> 21) << 12)+(((dwPhysical_0_LinesAddress >> 12) & 0x1ff)<<3);
		}
		else
		{
			OwnerPageDirItemAddress = 0xc0300000 + ((dwPhysical_0_LinesAddress >> 22)<<2);
			OwnerPageTabItemAddress = 0xc0000000 + ((dwPhysical_0_LinesAddress >> 22) << 12)+(((dwPhysical_0_LinesAddress >> 12) & 0x3ff)<<2);
		}
	}	
	return true;
}
void UnmapPhysical0()
{
	if(dwPhysical_0_LinesAddress!=0 && dwPhysical_0_LinesAddress!=0xffffffff)
	{		
		MmUnmapIoSpace((PVOID)dwPhysical_0_LinesAddress,0x100000);
		dwPhysical_0_LinesAddress=0xffffffff;
		OwnerPageDirItemAddress = 0;
		OwnerPageTabItemAddress = 0;
	}
}

int MapToVAddr(IN ULPOS Address,OUT ULPOS*pResult,IN int MaxCount,IN ULPOS HighAddress,ULLPOS AcceptedLowestAddress)
{
	int Count=0;
	ULPOS VAddress;
	DWORD Index;
	DWORD*PDE=(DWORD*)0xC0300000;
	DWORD*PTE=(DWORD*)0xC0000000;
	DWORD dwTmp,dwTmp1;
	CR4REGISTER stCR4;
	CPUID_1_EDX_FEATURE stCPUID_1_EDX;
	stCPUID_1_EDX = *(CPUID_1_EDX_FEATURE*)&gpCPUIDInfo[1].dwEDX;

	dwTmp = GetCR4Register();
	stCR4 = *(CR4REGISTER*)&dwTmp;
	if(stCR4.PAE)
	{
		PDE=(DWORD*)0xC0600000;
		for(DWORD nDir = 0; nDir < 512 * 4;nDir++)
		{
			if(ReadDword(&PDE[nDir*2],&dwTmp)==false)
				continue;
			if(ReadDword(&PDE[nDir*2+1],&dwTmp1)==false)
				continue;
			if((PDE[nDir*2]&1)==0)
				continue;
			if(PDE[nDir*2]&0x80)
			{
				if(HighAddress==PDE[nDir*2+1] && (Address & 0xFFE00000)==(PDE[nDir*2]&0xFFE00000))
				{
					VAddress = ((nDir / 512)<<30) | ((nDir % 512) <<21) | (Address &0x1FFFFF);
					if((ULLPOS)VAddress>=AcceptedLowestAddress)
					{
						if(pResult)
						{
							pResult[Count] = VAddress;
							Count++;
						}
						if(Count>=MaxCount)
							return Count;
					}
				}
			}
			else
			{
				PTE = (DWORD*)(nDir * 0x1000 + 0xC0000000);
				for(Index = 0; Index<512;Index++)
				{
					if(ReadDword(&PTE[Index*2],&dwTmp)==false)
						continue;
					if(ReadDword(&PTE[Index*2+1],&dwTmp1)==false)
						continue;
					if((PTE[Index*2]&1) && (PTE[Index*2] & 0xFFFFF000) == (Address & 0xFFFFF000) && PTE[Index*2+1] == HighAddress)
					{
						VAddress = ((nDir / 512) << 30)|((nDir % 512) <<21)|(Index << 12)|(Address & 0xFFF);
						if((ULLPOS)VAddress>=AcceptedLowestAddress)
						{
							if(pResult)
							{
								pResult[Count] = VAddress;
									Count++;
							}
							if(Count>=MaxCount)
								return Count;
						}
					}
				}
			}
		}
	}
	else
	{	
		for(DWORD nDir=0;nDir<0x400;nDir++)
		{
			if(ReadDword(&PDE[nDir],&dwTmp)==false)
				continue;
			if((PDE[nDir]&1) == 0)
				continue;		
			if((PDE[nDir]&0x80))//如果是 4M 页面
			{
				if((PDE[nDir]&0xFFC00000)==(Address&0xFFC00000))
				{
					VAddress = ((nDir<<22)|(Address&0x3FFFFF));
					if((ULLPOS)VAddress>=AcceptedLowestAddress)
					{
						if(pResult)
						{
							pResult[Count] = VAddress;
							Count++;
						}
						if(Count>=MaxCount)
							return Count;
					}
				}
			}
			else
			{
				Index = nDir*0x400;
				for(DWORD nPage=0;nPage<0x400;nPage++,Index++)
				{
					if(ReadDword(&PTE[Index],&dwTmp1)==false)
						continue;
					if((PTE[Index]&1) && (PTE[Index]&0xFFFFF000)==(Address&0xFFFFF000))
					{
						VAddress = ((nDir<<22)|(nPage<<12))|(Address&0xFFF);
						if((ULLPOS)VAddress>=AcceptedLowestAddress)
						{
							if(pResult)
							{								
								pResult[Count] = VAddress;
								Count++;
							}
							if(Count>=MaxCount)
								return Count;
						}
					}
				}
			}		
		}
	}
	return Count;
}

bool IsValidPage(IN VADDR32 Address,IN int Size)
{
	if(Size<=0)
		return false;
	Address -= Address%MP_SIZE;
	Size += (int)(Address%MP_SIZE);
	while(Size>0)
	{
		if(GetPTE(Address)==NULL)
			return false;
		Size-=MP_SIZE;
		Address+=MP_SIZE;
	}
	return true; 
}

bool IsWritablePage(IN VADDR32 Address)
{
	DWORD*PV;
	PV=GetPTE(Address);
	if((*PV&2)==0)
		return false;
	return true;
}

DWORD*GetPTE(VADDR32 Address,DWORD* PageSize,DWORD* PTESize,bool Present)
{
	DWORD *PDE,*PTE;
	CR4REGISTER stCR4;
	DWORD dwTmp;

	dwTmp=GetCR4Register();
	stCR4 = *(CR4REGISTER*)&dwTmp;
	if(stCR4.PAE)
	{
		if(PTESize)
			*PTESize=8;
		PDE=(DWORD*)0xC0600000;
		PDE = (DWORD*)(0xC0600000+((Address >> 0x12) & 0x3ff8));
		if(ReadDword(PDE,&dwTmp)==false)
			return NULL;
		if(Present)
		{
			if((PDE[0] & 1)== 0)
				return NULL;
		}

		if(PDE[0] & 0x80)
		{
			if(PageSize)
				*PageSize=0x200000;
			return &PDE[0];
		}
		PTE=(DWORD*)(0xC0000000+((Address >> 9) & 0x7ffff8));
		if(ReadDword(PTE,&dwTmp)==false)
			return NULL;
		if(Present)
		{
			if((PTE[0]&1)==0)
				return NULL;
		}
		if(PageSize)
			*PageSize=0x1000;
		return &PTE[0];
		
	}
	else
	{
		DWORD*PV;
		if(PTESize)
			*PTESize=4;
		PV=&PDEBase[Address>>22];
		if(ReadDword(PV,&dwTmp)==false)
			return NULL;
		if(Present)
		{
			if((*PV&1)==0)
				return NULL;
		}
		if(*PV&0x80)
		{
			if(PageSize)
				*PageSize=0x400000;
			return PV;
		}
		PV=&PTEBase[Address>>12];
		if(ReadDword(PV,&dwTmp)==false)
			return NULL;
		if(Present)
		{
			if((*PV&1)==0)
				return NULL;
		}
		if(PageSize)
			*PageSize=0x1000;
		return PV;
	}
}

bool MakePageWritable(IN VADDR32 Address)
{
	DWORD*PV;
	PV=GetPTE(Address);
	if(PV==NULL)
		return false;
	*PV|=2;
	return true;
}
DWORD GetCurrentCPUInterruptProcAddress(IN DWORD Index)
{
	PX86_GATE_DECR pDecr;
	VADDR32 IDTSize;
	pDecr = (PX86_GATE_DECR)SyserGetIDTBase(&IDTSize);
	return MAKE_DWORD(pDecr[Index].OffsetHigh,pDecr[Index].OffsetLow);
}
bool InstallInterruptHandle(IN BYTE Num,IN VADDR32 InterruptHandler,IN BYTE DescriptorType,IN BYTE DescriptorPrivilegeLevel,IN WORD Selector)
{
	VADDR32 IDTBase;
	DWORD i;
	KIRQL OldIRQL = KeGetCurrentIrql();
	KfRaiseIrql(HIGH_LEVEL);

	ULONG_PTR	Flags;
	SyserSaveFlags(&Flags);
	SyserCloseInterrupt();
	if(gCPUNumbers>1)
	{
		for(i = 0; i < gCPUNumbers;i++)
		{
			IDTBase=(VADDR32)gPCRArray[i]->IDT;
			if(SetInterruptHandlerFunction(Num,IDTBase,InterruptHandler,DescriptorType,DescriptorPrivilegeLevel,Selector)==NULL)
				goto Error_Exit;
		}
	}
	else
	{
		IDTBase = SyserGetIDTBase();
		if(SetInterruptHandlerFunction(Num,IDTBase,InterruptHandler,DescriptorType,DescriptorPrivilegeLevel,Selector)==NULL)
			goto Error_Exit;
	}
	SyserRestoreFlags(Flags);
	KfLowerIrql(OldIRQL);
	return true;
Error_Exit:
	SyserRestoreFlags(Flags);
	KfLowerIrql(OldIRQL);
	return false;
}

PINTERRUPT_STUB SetInterruptHandlerFunction(IN BYTE Num,IN DWORD IDTBase,IN VADDR32 InterruptHandler,IN BYTE DescriptorType,IN BYTE DescriptorPrivilegeLevel,IN WORD Selector)
{
	PINTERRUPT_STUB pIntStub;
	X86_GATE_DECR NewGetDecr;
	X86_GATE_DECR*pGateDecr;
	DWORD dwCR0;
	pIntStub = GetInterruptStub();
	if(pIntStub==NULL)
		return NULL;
	pGateDecr = (X86_GATE_DECR*)(IDTBase+Num*sizeof(X86_GATE_DECR));
	pIntStub->GateDecr = *pGateDecr;
	pIntStub->OldInterruptAddress=MAKE_DWORD(pGateDecr->OffsetHigh,pGateDecr->OffsetLow);
	pIntStub->IDTBaseAddress=IDTBase;
	pIntStub->InterruptVector=Num;
	pIntStub->OwnerInterruptAddress=InterruptHandler;
	NewGetDecr=*pGateDecr;
	NewGetDecr.OffsetHigh = HIGH_WORD(pIntStub);
	NewGetDecr.OffsetLow = LOW_WORD(pIntStub);
	NewGetDecr.P=1;
	NewGetDecr.DT=0;
	NewGetDecr.DCount=0;
	NewGetDecr.Reserved=0;
	if(DescriptorType<0x10)
	{
		NewGetDecr.Type=DescriptorType;
	}
	if(DescriptorPrivilegeLevel<0x4)
	{
		NewGetDecr.DPL=DescriptorPrivilegeLevel;
	}
	if(Selector)
	{
		NewGetDecr.Selector=Selector;
	}
	dwCR0 = SyserClearCR0WP();
	*pGateDecr=NewGetDecr;
	SyserRestoreCR0WP(dwCR0);
	return pIntStub;
}
DWORD UninstallInterruptHandle(IN BYTE Num)
{
	DWORD Count=0;
	X86_GATE_DECR*pGateDecr;
	for(int i = 0; i < sizeof(gInterruptStub)/sizeof(gInterruptStub[0]);i++)
	{
		if(gInterruptStub[i].InterruptVector==Num&&gInterruptStub[i].IDTBaseAddress)
		{
			Count++;
			pGateDecr = (X86_GATE_DECR*)(gInterruptStub[i].IDTBaseAddress+Num*sizeof(X86_GATE_DECR));
			*pGateDecr=gInterruptStub[i].GateDecr;
			ReleaseInterruptStub(&gInterruptStub[i]);
		}
	}
	return Count;
}

// BYTE ReadPortByte(DWORD wPort)
// {
// 	BYTE bRet;
// 	__asm{
// 		push edx
// 		push eax
// 		mov edx,wPort
// 		in al,dx
// 		mov bRet,al
// 		pop eax
// 		pop edx
// 	}
// 	return bRet;
// }

// WORD ReadPortWord(DWORD wPort)
// {
// 	WORD wRet;
// 	__asm{
// 		push edx
// 		push eax
// 		mov edx,wPort
// 		in ax,dx
// 		mov wRet,ax
// 		pop eax
// 		pop edx
// 	}
// 	return wRet;
// }


// DWORD ReadPortDword(DWORD wPort)
// {
// 	DWORD dwRet;
// 	__asm{
// 		push edx
// 		push eax
// 		mov edx,wPort
// 		in eax,dx
// 		mov dwRet,eax
// 		pop eax
// 		pop edx
// 	}
// 	return dwRet;
// }

// void WritePortDword(DWORD dwPort, DWORD dwValue)
// {
// 	__asm{
// 		push eax
// 		push edx
// 		mov edx,dwPort
// 		mov eax,dwValue
// 		out dx,eax
// 		pop edx
// 		pop eax
// 	}
// }

// void WritePortWord(DWORD dwPort, WORD wValue)
// {
// 	__asm{
// 		push eax
// 		push edx
// 		mov edx,dwPort
// 		mov ax,wValue
// 		out dx,ax
// 		pop edx
// 		pop eax
// 	}
// }
// void WritePortByte(DWORD dwPort, BYTE byteValue)
// {
// 	__asm{
// 		push eax
// 		push edx
// 		mov edx,dwPort
// 		mov al,byteValue
// 		out dx,al
// 		pop edx
// 		pop eax
// 	}
// }

void CopyGeneralRegister(void)
{
	memcpy(GeneralReg,Reg.GeneReg,sizeof(GeneralReg));
}

// bool IsSupportRDMSRInstruction()
// {
// 	static bool bInitIsSupportRDMSRInstruction = false;
// 	static bool bHaveReadWriteMSRInstruction = false;
// 	DWORD bRet;
// 	if(bInitIsSupportRDMSRInstruction==false)
// 	{	
// 		if(SyserIsSupportCPUIDInstruction() == false)
// 		{
// 			bHaveReadWriteMSRInstruction = false;
// 			return false;
// 		}
// 		__asm{	
// 			pushad		
// 			mov eax,1
// 			cpuid
// 			test edx,0x20        //判断是否支持 RDMSR WDMSR 指令
// 			mov bHaveReadWriteMSRInstruction,0
// 			jz local_1			
// 			mov bHaveReadWriteMSRInstruction,1
// 	local_1:			
// 			popad
// 		}
// 		bInitIsSupportRDMSRInstruction = true;
// 	}
// 	return bHaveReadWriteMSRInstruction;
// }

// void* MemoryCopy(void *dst, const void*src,int count)
// {
// 	void * ret;
// 	ret = dst;
// 	__asm{
// 		pushad
// 		pushfd
// 		cld
// 		mov esi,src
// 		mov edi,dst
// 		mov ecx,count
// 		mov eax,esi
// 		and eax,3
// 		jz local_1
// local_2:
// 		jecxz local_quit
// 		movsb
// 		dec ecx
// 		dec eax
// 		jnz local_2
// local_1:
// 		jecxz local_quit
// 		mov eax,ecx
// 		shr ecx,2
// 		rep movsd
// 		and eax,3
// 		mov ecx,eax
// 		rep movsb
// local_quit:
// 		popfd
// 		popad
// 	}
// 	return ret;
// }
bool ReadPhysicalAddress(DWORD dwPhysicalAddress,DWORD &dwValue)
{
	VADDR32 dwLineAddress;
	
	if(MapToVAddr(dwPhysicalAddress,&dwLineAddress))
	{
		dwValue=*(DWORD *)dwLineAddress;		
		return true;
	}
	else
	{
		return false;
	}
}

DWORD SafeReadSegmentDword(DWORD Offset,WORD SegmentSelector)
{
	return 0;
}
DWORD GetSegmentBaseAddress(WORD SegmentSelector,DWORD *SegmentLimit)
{
	VADDR32 TableBase;
	DWORD TableSize;
	DWORD BaseAddress;
	X86_SEGMENT_DESCRIPTOR* SegDesc;
	DWORD Limit;
	if(SegmentSelector&0xfff8)
	{
		if(SegmentSelector&0x4)		
			TableBase = GetLDTBase(&TableSize);
		else		
			TableBase = SyserGetGDTBase(&TableSize);		
		if((SegmentSelector&0xfff8)>(WORD)TableSize)
			goto errorout;
		SegDesc=(X86_SEGMENT_DESCRIPTOR*)TableBase;
		BaseAddress = SegDesc[(SegmentSelector>>3)].base_L0+ (SegDesc[(SegmentSelector>>3)].base_L1<<8)+(SegDesc[(SegmentSelector>>3)].base_H0<<16)+(SegDesc[(SegmentSelector>>3)].base_H1<<24);		
		if(SegmentLimit)
		{
// 			__asm{
// 				push eax
// 				movzx eax,SegmentSelector
// 				lsl eax,eax
// 				jz local_001
// 				xor eax,eax
// local_001:
// 				mov Limit,eax
// 				pop eax 
// 			}

			Limit = SyserGetSegmentLimit(SegmentSelector);

			*SegmentLimit=Limit;
		}
		return BaseAddress;
	}else
	{
errorout:
		if(SegmentLimit)
			*SegmentLimit=0;
		return 0xffffffff;
	}
}

DWORD GetX86CR4(DWORD BitMask)
{
	DWORD dwRet;
// 	__asm{
// 		push eax 
// 		_emit(0x0f)
// 		_emit(0x20)
// 		_emit(0xe0)
// 		mov dwRet,eax
// 		pop eax
// 	}

	dwRet = SyserGetCR4Reg();

	if(BitMask==0xffffffff)
		return dwRet;
	BitMask %= 32;
	if(BitMask)
		dwRet>>=BitMask;
	return dwRet&1;
}

DWORD GetCR4Register()
{	
// 	DWORD dwRet;
// 	__asm{
// 		push eax 
// 		_emit(0x0f)
// 		_emit(0x20)
// 		_emit(0xe0)
// 		mov dwRet,eax
// 		pop eax 
// 	}
// 	return dwRet;

	return SyserGetCR4Reg();
}
DWORD SetCR4Register(DWORD NewValue)
{	
	DWORD OldValue;
	OldValue = GetCR4Register();
// 	__asm{
// 		push eax 
// 		mov eax,NewValue
// 		_emit(0x0f)
// 		_emit(0x22)
// 		_emit(0xe0)
// 		pop eax 
// 	}
	SyserSetCR4Reg(NewValue);
	return OldValue;
}
DWORD GetCR0Register()
{
// 	DWORD dwRet;
// 	__asm{
// 		push eax 
// 		mov eax,cr0 
// 		mov dwRet,eax 
// 		pop eax 
// 	}
// 	return dwRet;

	return SyserGetCR0Reg();
}
bool X86_FXSAVE(BYTE *RegisterBuffer)
{
	DWORD dwTmp = (DWORD)RegisterBuffer;
	if(dwTmp&0xf)
		return false;
// 	__asm
// 	{
// 		push eax 
// 		mov eax, RegisterBuffer
// 		fxsave dword ptr [eax]
// 		pop eax
// 	}

	SyserX86FxSave(RegisterBuffer);

	return true;
}
// bool GetFpuErrorState()
// {
// 	DWORD dwError,dwMxcsr;
// 	__asm
// 	{
// 		pushfd
// 		push eax
// 		push ebx
// 		clts
// 		stmxcsr dwMxcsr
// 		mov eax,dwMxcsr
// 		mov ebx,eax 
// 		shr ebx,7 
// 		and eax,0x3f 
// 		and ebx,0x3f 
// 		and bl,al 
// 		not bl 
// 		test bl,al 
// 		mov dwError,0
// 		jz local_1
// 		mov dwError,1
// local_1:
// 		pop ebx
// 		pop eax
// 		popfd
// 	}	
// 	return (dwError == 1);
// }

bool GetSegDescr(WORD Sel,X86_SEGMENT_DESCRIPTOR*pSegDescr)
{
	SELECTOR_DECR*pSel;
	DWORD DTBase,DTSize;
	pSel = (SELECTOR_DECR*)&Sel;
	if(pSel->TI)
		DTBase = GetLDTBase(&DTSize);
	else
		DTBase = SyserGetGDTBase(&DTSize);
	if(DTBase==0)
		return false;
	if(pSel->Index>=DTSize/sizeof(X86_SEGMENT_DESCRIPTOR))
		return false;
	if(pSegDescr)
		*pSegDescr = ((X86_SEGMENT_DESCRIPTOR*)DTBase)[pSel->Index];
	return true;
}

// void InitSystemSegmentRegister()
// {
// 	__asm
// 	{
// 		push eax 
//		xor eax,eax
//		mov ax,fs 
//		mov gSystemFSRegisterSelector,eax
//		mov ax,ss 
//		mov gSystemSSRegisterSelector,eax 
//		mov ax,cs 
//		mov gSystemCSRegisterSelector,eax
//		mov ax,ds 
//		mov gSystemDSRegisterSelector,eax
//		pop eax
//	}
//}