#include "stdafx.h"
#include "LastBranch.h"
#include "X86Optr.h"

static int gLastBranchType=0;

int GetLastBranchType()
{
	return gLastBranchType;
}
bool GetLastBranchAddress(DWORD Index,DWORD* FromAddr,DWORD* ToAddr)
{
	if(gLastBranchType==-1)
		return false;

	return gfnGetLastBranchInfo[gLastBranchType](Index,FromAddr,ToAddr);
}

bool GetLastBranchAddressPentium(DWORD Index,DWORD* FromAddr,DWORD* ToAddr)
{
	DWORD dwTmp,dwTmp2;
	if(Index!=0)
		return false;
	SyserReadMSR(0x1db,&dwTmp,&dwTmp2);
	if(FromAddr)
		*FromAddr = dwTmp2;
	SyserReadMSR(0x1dc,&dwTmp,&dwTmp2);
	if(ToAddr)
		*ToAddr = dwTmp2;
	return true;
}

bool GetLastBranchAddressPentiumPro(DWORD Index,DWORD* FromAddr,DWORD* ToAddr)
{
	DWORD dwTmp=0,dwTmp2=0;
	if(Index>3)
		return false;
	SyserReadMSR(0x1c9,&dwTmp,&dwTmp2);
	dwTmp2 &= 3;
	dwTmp2 += 4;
	dwTmp2 -= Index;
	dwTmp2 &= 3;
	SyserReadMSR(0x1db+dwTmp2,&dwTmp,&dwTmp2);
	if(FromAddr)
		*FromAddr=dwTmp2;
	if(ToAddr)
		*ToAddr=dwTmp;
	return true;
}


bool GetLastBranchAddressPentium4New_16(DWORD Index,DWORD* FromAddr,DWORD* ToAddr)
{
	DWORD dwTmp=0,dwTmp2=0;
	if(Index>15)
		return false;
	SyserReadMSR(0x1c9,&dwTmp,&dwTmp2);
	dwTmp2 &= 15;
	dwTmp2 += 16;
	dwTmp2 -= Index;
	dwTmp2 &= 15;
	Index = dwTmp2;
	SyserReadMSR(0x680+dwTmp2,&dwTmp,&dwTmp2);
	if(FromAddr)
		*FromAddr=dwTmp2;
	SyserReadMSR(0x6C0+Index,&dwTmp,&dwTmp2);
	if(ToAddr)
		*ToAddr=dwTmp2;
	return true;
}

bool GetLastBranchAddressPentium4New_4(DWORD Index,DWORD* FromAddr,DWORD* ToAddr)
{
	DWORD dwTmp=0,dwTmp2=0;
	if(Index>3)
		return false;
	SyserReadMSR(0x1c9,&dwTmp,&dwTmp2);
	dwTmp2 &= 3;
	dwTmp2 += 4;
	dwTmp2 -= Index;
	dwTmp2 &= 3;
	Index = dwTmp2;
	SyserReadMSR(0x40+dwTmp2,&dwTmp,&dwTmp2);
	if(FromAddr)
		*FromAddr=dwTmp2;
	SyserReadMSR(0x60+Index,&dwTmp,&dwTmp2);
	if(ToAddr)
		*ToAddr=dwTmp2;
	return true;
}

bool GetLastBranchAddressPentium4New_8(DWORD Index,DWORD* FromAddr,DWORD* ToAddr)
{
	DWORD dwTmp=0,dwTmp2=0;
	if(Index>7)
		return false;
	SyserReadMSR(0x1c9,&dwTmp,&dwTmp2);
	dwTmp2 &= 7;
	dwTmp2 += 8;
	dwTmp2 -= Index;
	dwTmp2 &= 7;
	Index = dwTmp2;
	SyserReadMSR(0x40+dwTmp2,&dwTmp,&dwTmp2);
	if(FromAddr)
		*FromAddr=dwTmp2;
	SyserReadMSR(0x60+Index,&dwTmp,&dwTmp2);
	if(ToAddr)
		*ToAddr=dwTmp2;
	return true;
}

bool GetLastBranchAddressPentiumM_8(DWORD Index,DWORD* FromAddr,DWORD* ToAddr)
{
	DWORD dwTmp=0,dwTmp2=0;
	if(Index>7)
		return false;
	SyserReadMSR(0x1c9,&dwTmp,&dwTmp2);
	dwTmp2 &= 7;
	dwTmp2 += 8;
	dwTmp2 -= Index;
	dwTmp2 &= 7;
	SyserReadMSR(0x40+dwTmp2,&dwTmp,&dwTmp2);
	if(FromAddr)
		*FromAddr=dwTmp2;
	if(ToAddr)
		*ToAddr=dwTmp;
	return true;
}

bool GetLastBranchAddressPentiumM_4(DWORD Index,DWORD* FromAddr,DWORD* ToAddr)
{
	DWORD dwTmp=0,dwTmp2=0;
	if(Index>3)
		return false;
	SyserReadMSR(0x1c9,&dwTmp,&dwTmp2);
	dwTmp2 &= 3;
	dwTmp2 += 4;
	dwTmp2 -= Index;
	dwTmp2 &= 3;
	SyserReadMSR(0x40+dwTmp2,&dwTmp,&dwTmp2);
	if(FromAddr)
		*FromAddr=dwTmp2;
	if(ToAddr)
		*ToAddr=dwTmp;
	return true;
}


// 
// 
// int DetectLastBranchType()
// {
// 	DWORD Type=0,Index=0,Index2=0;
// 	DWORD  From=0,To=0,From1=0,To1=0,Tos1=0,Tos2=0,From2=0,To2=0;
// 	__asm{
// 		pushad
// 		pushfd
// 		cli
// 		mov ecx,0x1d9 
// 		xor eax,eax 
// 		xor edx,edx 
// 		rdmsr 
// 		or eax,1 
// 		wrmsr
// 		call local_001
// 		nop
// local_001:
// 		pop eax
// 		xor eax, eax 
// 		xor edx, edx
// 		mov ecx, 0x1c9 
// 		rdmsr
// 		mov Tos1,eax
// 		call local_002
// 		nop
// local_002:
// 		pop eax 
// 		xor eax, eax 
// 		xor edx, edx
// 		mov ecx, 0x1c9 
// 		rdmsr
// 		mov Tos2,eax 		
// 		popfd
// 		popad
// 	}	
// 	if((Tos1 & 0xf) == (Tos2 & 0xf))  //早期的 P6 处理器， 没有 MSR_LASTBRANCH_TOP 
// 		return 0;
// 	__asm{
// 		pushad
// 		pushfd
// 		cli
// 		call local_003
// 		nop
// local_003:
// 		pop eax
// 		lea eax,[eax-5]
// 		mov From,eax
// 		lea eax,[eax+6]
// 		mov To,eax
// 		xor eax, eax 
// 		xor edx, edx
// 		mov ecx, 0x1c9 
// 		rdmsr
// 		and eax,3
// 		mov ecx, eax		
// 		add ecx, 0x1db
// 		xor eax, eax 
// 		xor edx, edx
// 		rdmsr
// 		mov From1, eax
// 		mov To1, edx		
// 		popfd
// 		popad
// 	}
// 	if((From == From1 && To == To1) || (From == To1 && To == From1))
// 		return 1;
// 	__asm{
// 		pushad
// 		pushfd
// 		cli
// 		call local_004
// 		nop
// local_004:
// 		pop eax
// 		lea eax,[eax-5]
// 		mov From,eax
// 		lea eax,[eax+6]
// 		mov To,eax
// 		xor eax, eax 
// 		xor edx, edx
// 		mov ecx, 0x1c9 
// 		rdmsr
// 		and eax,7
// 		mov Index,eax
// 		mov ecx, eax		
// 		add ecx, 0x40
// 		xor eax, eax 
// 		xor edx, edx
// 		rdmsr
// 		mov From1, eax
// 		mov To1, edx	
// 		jmp local_102
// 		nop
// local_102:
// 		jmp local_103
// 			nop
// local_103:
// 		jmp local_104
// 			nop
// local_104:
// 		jmp local_105
// 			nop
// local_105:		
// 		mov ecx,0x1d9 
// 		xor eax,eax 
// 		xor edx,edx 
// 		rdmsr 
// 		and eax,7 
// 		mov Index2,eax 
// 		popfd
// 		popad
// 	}
// 	if((From == From1 && To == To1) || (From == To1 && To == From1))//测试一下循环栈里面有几个元素
// 	{				
// 		return Index==Index2 ? 2 : 3;  //如果 Index == Index2 则	循环栈里是4个元素 否则是 8 个元素
// 	}		
// 	__asm{
// 		pushad
// 		pushfd
// 		cli
// 		call local_034
// 		nop
// local_034:
// 		pop eax
// 		lea eax,[eax-5]
// 		mov From,eax
// 		lea eax,[eax+6]
// 		mov To,eax
// 		xor eax, eax 
// 		xor edx, edx
// 		mov ecx, 0x1c9 
// 		rdmsr
// 		and eax,7
// 		mov Index,eax		
// 		mov ecx, eax		
// 		add ecx, 0x40
// 		xor eax, eax 
// 		xor edx, edx
// 		rdmsr
// 		mov From1, eax		
// 		mov ecx,Index 
// 		add ecx,0x60 
// 		xor eax,eax 
// 		xor edx,edx
// 		rdmsr		
// 		mov To1,eax
// 		jmp local_005
// 		nop
// local_005:
// 		jmp local_006
// 		nop 
// local_006:
// 		jmp local_007
// 		nop 
// local_007:
// 		jmp local_008
// 		nop 
// local_008:
// 		xor eax, eax 
// 		xor edx, edx
// 		mov ecx, 0x1c9 
// 		rdmsr
// 		and eax,7 
// 		mov Index2,eax 
// 		popfd
// 		popad
// 	}
// 	if((From == From1 && To == To1) || (From == To1 && To == From1))//测试一下循环栈里面有几个元素
// 	{				
// 		return Index==Index2 ? 4 : 5;  //如果 Index == Index2 则	循环栈里是4个元素 否则是 8 个元素
// 	}		
// 
// 	__asm{
// 		pushad
// 		pushfd
// 		cli
// 		call local_036
// 		nop
// local_036:
// 		pop eax
// 		lea eax,[eax-5]
// 		mov From,eax
// 		lea eax,[eax+6]
// 		mov To,eax
// 		xor eax, eax 
// 		xor edx, edx
// 		mov ecx, 0x1c9 
// 		rdmsr
// 		and eax,15
// 		mov Index,eax		
// 		mov ecx, eax		
// 		add ecx, 0x680
// 		xor eax, eax 
// 		xor edx, edx
// 		rdmsr
// 		mov From1, eax		
// 		mov ecx,Index 
// 		add ecx,0x6c0 
// 		xor eax,eax 
// 		xor edx,edx
// 		rdmsr		
// 		mov To1,eax		
// 		popfd
// 		popad
// 	}
// 	if((From == From1 && To == To1) || (From == To1 && To == From1))
// 		return 6;
// 	return -1;
// }

bool InitBranchMointer()
{	
	if(gpCPUIDInfo==NULL || SyserIsSupportCPUIDInstruction()==false || SyserIsSupportRDMSRInstruction()==false)
		return false;	
	if((gpCPUIDInfo[1].dwEAX&0xf00)<0x600)
		return false;		
	gLastBranchType = SyserDetectLastBranchType();
	if(gLastBranchType==-1)
		return false;
	gbHaveLastBranchMointer = true;
	SetLastBranchMointer();
	return true;
}
bool SetLastBranchMointer()
{
	DWORD dwHigh,dwLow;
	if(gLastBranchType==-1)
		return false;
	SyserReadMSR(0x1d9,&dwHigh,&dwLow);
	dwLow |= 1;
	SyserWriteMSR(0x1d9,dwHigh,dwLow);
	return true;
}


GETLASTBRANCHINFO gfnGetLastBranchInfo[7]=
{
	GetLastBranchAddressPentium,
	GetLastBranchAddressPentiumPro,
	GetLastBranchAddressPentiumM_4,
	GetLastBranchAddressPentiumM_8,
	GetLastBranchAddressPentium4New_4,
	GetLastBranchAddressPentium4New_8,
	GetLastBranchAddressPentium4New_16,
};

