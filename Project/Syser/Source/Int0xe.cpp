#include "stdafx.h"
#include "int0xe.h"
#include "Syser.h"
#include "SyserMemoryReadWrite.h"
#include "HardWareInterruptCtrl.h"
#include "OSProcessThread.h"

#ifdef __cplusplus
extern "C" {
#endif
bool HandleBpr(DWORD PagedCR2,DWORD ErrorCode,DWORD*P);
#ifdef __cplusplus
}; // extern "C"
#endif

bool Int0eHandle(DWORD *StackPointer)
{
	DWORD begin,end;
	begin = (DWORD)SyserPrivateReadByte;
	end =(DWORD) SyserPrivateReadError;
	if(StackPointer[1]>begin&&StackPointer[1]<end)
	{
		StackPointer[1]=(DWORD)SyserPrivateReadError;
		return true;
	}
	begin = (DWORD)SyserPrivateWriteByte;
	end =(DWORD) SyserPrivateWriteError;
	if(StackPointer[1]>begin&&StackPointer[1]<end)
	{
		StackPointer[1]=(DWORD)SyserPrivateWriteError;
		return true;
	}
	
	begin = (DWORD)SyserPrivateMemCopy;
	end =(DWORD) SyserPrivateMemCopyError;
	if(StackPointer[1]>begin&&StackPointer[1]<end)
	{
		StackPointer[1]=(DWORD)SyserPrivateMemCopyError;
		return true;
	}
	begin = (DWORD)SyserVideoMemCopy;
	end =(DWORD) SyserPrivateMemCopyError;
	if(StackPointer[1]>begin&&StackPointer[1]<end)
	{
		StackPointer[1]=(DWORD)SyserPrivateMemCopyError;
		return true;
	}	
	begin = (DWORD)SyserPrivateFindByte;
	end =(DWORD) SyserPrivateFindMemoryError;
	if(StackPointer[1]>begin&&StackPointer[1]<end)
	{
		StackPointer[1]=(DWORD)SyserPrivateFindMemoryError;
		return true;
	}	
	begin = (DWORD)SyserPrivateMemSearch;
	end =(DWORD) SyserPrivateMemorySearchError;
	if(StackPointer[1]>begin&&StackPointer[1]<end)
	{
		StackPointer[1]=(DWORD)SyserPrivateMemorySearchError;
		return true;
	}	
	begin = (DWORD)SyserPrivatePagePresent;
	end =(DWORD) SyserPrivatePageNotPresent;
	if(StackPointer[1]>begin&&StackPointer[1]<end)
	{
		StackPointer[1]=(DWORD)SyserPrivatePageNotPresent;
		return true;
	}
	begin = (DWORD)SyserPrivateMemCmp;
	end =(DWORD) SyserPrivateMemCmpError;
	if(StackPointer[1]>begin&&StackPointer[1]<end)
	{
		StackPointer[1]=(DWORD)SyserPrivateMemCmpError;
		return true;
	}
	return false;
}

//int _0E_TickCount=0;
DWORD gdwActiveInt0eProcAddress;
DWORD gSyserInt0eAddress;

// 
// __declspec(naked) void Active_Int0eProcStub()
// {
// 	__asm
// 	{
// 		Push ss:gdwActiveInt0eProcAddress
// 		jmp Int0eProc
// 	}
// }


void ActiveHookInt0e(bool bInstall)
{
	DWORD IDTBase,IDTSize;
	PX86_GATE_DECR pDecr;
	IDTBase=SyserGetIDTBase(&IDTSize);
	pDecr = *(PX86_GATE_DECR*)&IDTBase;
	if(bInstall)
	{		
		gdwActiveInt0eProcAddress = MAKE_DWORD(pDecr[0xe].OffsetHigh, pDecr[0xe].OffsetLow);
		if(gdwActiveInt0eProcAddress != (DWORD)SyserActive_Int0eProcStub)
		{
			if(gSyserInt0eAddress)
			{
				IDTBase=gSyserInt0eAddress;			
			}
			else
			{
				IDTBase=(DWORD)SyserActive_Int0eProcStub;
			}
			pDecr[0xe].OffsetHigh=(WORD)(IDTBase>>16);
			pDecr[0xe].OffsetLow=(WORD)(IDTBase&0xffff);
		}
	}
	else
	{
		pDecr[0xe].OffsetHigh=(WORD)(gdwActiveInt0eProcAddress>>16);
		pDecr[0xe].OffsetLow=(WORD)(gdwActiveInt0eProcAddress&0xffff);
	}
}
DWORD g1count=0;


// 
// 
// __declspec(naked) void SyserInt0eProc()
// {
// 	DWORD* Int0eStackPointer;
// 	DWORD PagedCR2;
// 
// 	__asm
// 	{
// 		push dword ptr 0xE
// 		call SaveExceptionRegister
// 		lea esp,[esp+4]   //丢掉 push dword ptr 0xe
// 		pushfd
// 		pushad
// 		mov ebp,esp
// 		lea esp,[esp-0x8]    //留出两个局部变量的空间
// 		mov Int0eStackPointer,ebp 
// 		mov eax,cr2 
// 		mov PagedCR2,eax
// 		/*
// 		eflags       [ebp+34]
// 		cs           [ebp+30]
// 		eip          [ebp+2c]
// 		error        [ebp+28]
// 		winorginte   [ebp+24]
// 		eflags       [ebp+20]
// 		eax          [ebp+1c]
// 		ecx          [ebp+18]
// 		edx          [ebp+14]
// 		ebx          [ebp+10]
// 		esp          [ebp+c]
// 		ebp          [ebp+8]
// 		esi          [ebp+4]
// 		edi          [ebp+0] 
// 		*/
// 		add Int0eStackPointer,0x28
// 		push ds
// 		push es
// 		push fs
// 		mov ax,0x23 
// 		mov ds,ax 
// 		mov es,ax
// 		mov ax,0x30
// 		mov fs,ax
// 		mov eax,cr2
// 		CLD
// 	}
// 	//GetLastBranchAddress();
// 	
// 	if(Int0eHandle(Int0eStackPointer))//判断是不是在 Syser.sys 内部发生了异常
// 	{
// 		//_0E_TickCount--;
// 		__asm
// 		{
// 			pop fs
// 			pop es
// 			pop ds
// 			lea esp,[esp+8]   //丢掉两个局部变量
// 			popad
// 			popfd
// 			lea esp,[esp+8]   //丢掉 errorcode 和 windows return address
// 			iretd             //直接返回
// 		}
// 	}
// 
// 	if(gpSyser)
// 	{
// 		if(HandleBpr(PagedCR2,Int0eStackPointer[0],Int0eStackPointer))
// 		{
// 			__asm
// 			{
// 				pop fs
// 				pop es
// 				pop ds 
// 				lea esp,[esp+8]//丢掉两个局部变量
// 				popad
// 				popfd
// 				lea esp,[esp+8]   //丢掉 errorcode 和 windows return address			
// 				OR DWORD PTR[esp+8],0x100
// 				IRETD
// 			}			
// 		}		
// 	}
// 	
// 	//_0E_TickCount--;
// 
// 	if(Int0eStackPointer[3]&0x100)//在单步调试的时候导致了一个缺页异常
// 	{		
// 		EnableAllHardInterrupt();
// 		SyserStartOtherCPUs();		
// 	}
// 	__asm
// 	{
// 		pop fs
// 		pop es
// 		pop ds 
// 		lea esp,[esp+8]//丢掉两个局部变量
// 		popad
// 		popfd
// 		ret            //返回到原始的WINDOWS中断处理地址
// 	}
// }


DWORD dwHandleBpr=0;
DWORD HandleBprcOUNT=0;
bool HandleBpr(DWORD PagedCR2,DWORD ErrorCode,DWORD*P )
{
	DWORD dwValue,PageAlignment;
	DWORD Process,Thread;
	bool bOK;
	static int count1=0;
	if(ErrorCode&1)
		return false;
	bOK = GetCurrentProcessAndThread(&Process,&Thread);
	if(bOK==false)
		return false;

	BP_RANGE_LIST::IT BeginIT,EndIT;
	PROC_RANGE_BP_MAP::IT FindIT = gpSyser->m_RangeBPList.Find(Process);
	if(FindIT == gpSyser->m_RangeBPList.End())
		return false;
	
	DWORD PtePtr=0,PageSize=0,PTESize=0,StartAddr1=0,EndAddr1=0;
	PtePtr = (DWORD)GetPTE(PagedCR2,&PageSize,&PTESize,false);
	if(!PtePtr)
		return false;
	StartAddr1 = PagedCR2 & (~(PageSize-1));
	EndAddr1 = StartAddr1+PageSize;		
	BeginIT = FindIT->Begin();
	EndIT = FindIT->End();
	for(;BeginIT!=EndIT;BeginIT++)
	{			
		DWORD StartAddr = BeginIT->RangeStartAddress;
		DWORD EndAddr = BeginIT->RangeStartAddress+BeginIT->RangeLength-1;
		if(!(BeginIT->Type & BP_SET_BPR_TYPE))
			continue;
		if(!((EndAddr < StartAddr1) || (StartAddr >= EndAddr1)))
		
		//	if((StartAddr>=StartAddr1 && StartAddr < EndAddr1) || (EndAddr>StartAddr1 && EndAddr < EndAddr1) || (StartAddr < StartAddr1 && EndAddr >EndAddr1))
		{		
			
			if(ReadDword((void*)PtePtr,&dwValue))
			{
				if(WriteDword((void*)PtePtr,dwValue|1))
				{
					BeginIT->Type |= BP_REV_BPR_TYPE;														
					gpSyser->m_SyserUI.m_SyserDI.SetTracePageRangeCondition(PagedCR2,P[1]);							
					return true;							
				}
			}					
		}
	}

	return false;
}