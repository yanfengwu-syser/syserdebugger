#include "StdAfx.h"
#include "Syser.h"
#include "MultiCPU.h"
#include "X86Optr.h"
#include "LocalAPIC.h"
#include "IOAPIC.h"

#ifdef __cplusplus
extern "C" {
#endif

DWORD gSystemFSRegisterSelector=0x30;
DWORD gSystemSSRegisterSelector=0x10;
DWORD gSystemCSRegisterSelector=0X8;
DWORD gCPUNumbers = 1;
PKPCR gDefaultPCR=(PKPCR)0xffdff000;
PKPCR*gPCRArray=&gDefaultPCR;
BYTE  gCPULocalAPIC_ID[256];
DWORD gdwMulitCpuSpinlock=0;
DWORD gdwCurrentCPUIndex=0xffffffff;   //
DWORD gdwMulitCpuSendIPIFlags=0;
DWORD gSystemDSRegisterSelector=0x23;
PKDPC gpMultiCpuDPC=NULL;
PCPUSTRUCT gpCPUStruct=NULL;
DWORD gdwExitNmiLock=0;

#ifdef __cplusplus
}; // extern "C"
#endif

typedef int (*PFN_KeSetAffinityThread)(PKTHREAD,int);

ULONG GetCPUCount()
{
	typedef ULONG (*PFN_KeQueryActiveProcessorCount)(OUT PKAFFINITY  ActiveProcessors);
	ULONG CPUCount;
	UNICODE_STRING UnicodeName;
	KAFFINITY  ActiveProcessor;
	PCCHAR pKeNumberProcessors;
	PFN_KeQueryActiveProcessorCount pfnKeQueryActiveProcessorCount;

	RtlInitUnicodeString(&UnicodeName,WSTR("KeQueryActiveProcessorCount"));
	pfnKeQueryActiveProcessorCount=(PFN_KeQueryActiveProcessorCount)MmGetSystemRoutineAddress(&UnicodeName);
	if(pfnKeQueryActiveProcessorCount)
	{
		CPUCount = pfnKeQueryActiveProcessorCount(&ActiveProcessor);
	}
	else
	{
		RtlInitUnicodeString(&UnicodeName,WSTR("KeNumberProcessors"));
		pKeNumberProcessors=(PCCHAR)MmGetSystemRoutineAddress(&UnicodeName);
		if(pKeNumberProcessors==NULL)
		{
			return 1;
		}
		CPUCount = (ULONG)*pKeNumberProcessors;
	}
	return CPUCount;
}

bool InitMultiCPUInformation()
{
	PKTHREAD pThread;
	ULONG CpuID,i;
	ULONG IdtBase;
	DWORD* dwPCRAddr=NULL;
	ULONG TargetProcessor;
	ULONG TargetProcessor2;
	UNICODE_STRING UnicodeName;
	PFN_KeSetAffinityThread pfnKeSetAffinityThread;
	memset(gCPULocalAPIC_ID,0xff,sizeof(gCPULocalAPIC_ID));
	gCPUNumbers = GetCPUCount();
	DbgPrint("Syser : CPU Numbers = %d\n",gCPUNumbers);

	if(gCPUNumbers==1)
		return true;
	RtlInitUnicodeString(&UnicodeName,WSTR("KeSetAffinityThread"));
	pfnKeSetAffinityThread=(PFN_KeSetAffinityThread)MmGetSystemRoutineAddress(&UnicodeName);
	if(pfnKeSetAffinityThread==NULL)
	{
		::DbgPrint("Syser : Fail to find KeSetAffinityThread\n");
		return false;
	}
	dwPCRAddr = new DWORD[gCPUNumbers+1];
	if(dwPCRAddr==NULL)
		return false;
	memset(dwPCRAddr,0,(gCPUNumbers+1)*sizeof(DWORD));
	gPCRArray = (PKPCR*)dwPCRAddr;
	gpMCPUReg = new X86_REG_CONTEXT[gCPUNumbers];
	if(gpMCPUReg==NULL)
	{
		if(dwPCRAddr)
		{
			delete dwPCRAddr;
			dwPCRAddr=NULL;
		}
		return false;
	}
	ExceptionReg=new X86_REG_CONTEXT[gCPUNumbers];
	if(ExceptionReg==NULL)
	{
		if(dwPCRAddr)
		{
			delete dwPCRAddr;
			dwPCRAddr=NULL;
		}
		if(gpMCPUReg)
		{
			delete gpMCPUReg;
			gpMCPUReg=NULL;
		}
		return false;
	}
	gpMCPULocalApic = new SAVELOCALAPIC[gCPUNumbers];
	if(gpMCPULocalApic==NULL)
	{
		if(dwPCRAddr)
			delete dwPCRAddr;
		if(gpMCPUReg)
		{
			delete gpMCPUReg;
			gpMCPUReg=NULL;
		}
		return false;
	}
	
	TargetProcessor = KeGetCurrentProcessorNumber();//取得当前的CPU ID 在退出函数的时候要恢复
	pThread = KeGetCurrentThread();
	CpuID=1;
	for(i=0;i<gCPUNumbers;i++,CpuID<<=1)
	{
		pfnKeSetAffinityThread(pThread,CpuID);
		dwPCRAddr[i]=GetSegmentBaseAddress(0x30);
	}
	CpuID=1<<TargetProcessor;
	pfnKeSetAffinityThread(pThread,CpuID);	
	return	true;
}

#ifdef __cplusplus
extern "C" {
#endif

extern DWORD gLoopCpuNumber;

#ifdef __cplusplus
}; // extern "C"
#endif

// __declspec(naked) void  StartOtherCPUs()
// {
// 	__asm
// 	{
// 		pushfd
// 		cmp cs:gCPUNumbers,1 
// 		jbe local_quit111
// 		push eax 
// 		push ds 
// 		mov eax,cs:gSystemSSRegisterSelector 
// 		mov ds,ax
// 		cmp dword ptr gLoopCpuNumber,0    //gLoopCpuNumber 这个变量是用来判断是否有进入死循环的 cpu 
// 		jz local_00222
// 
// 		lock inc gdwExitNmiLock
// 		mov gdwMulitCpuSpinlock,0 
// 		mov gdwCurrentCPUIndex,0xffffffff
// local_011:
// 		cmp gdwExitNmiLock,0  //等待其他CPU完全退出中断2
// 		jnz local_011
// local_00222:
// 		pop ds 
// 		pop eax
// local_quit111:
// 		popfd
// 		ret
// 	}
// }

// void __declspec(naked) StopOtherCPUs()
// {
// 	DWORD TmpCurrentCPUIndex;
// 	__asm
// 	{
// 		pushfd
// 		cmp cs:gCPUNumbers,1
// 		jnz local_001
// 		popfd
// 		ret
// local_001:
// 		pushad
// 		push ds
// 		mov eax, cs:gSystemSSRegisterSelector
// 		mov ds,ax
// 		mov ebp,esp
// 		sub esp,4
// 	}
// 	TmpCurrentCPUIndex = GetCurrentCPULocalAPICID();
// 	__asm
// 	{
// 		mov eax,TmpCurrentCPUIndex
// local_020:
// 		lock bts gdwMulitCpuSpinlock,0x1f  //如果同时有多个CPU执行这个指令，则只有一个CPU能获得改锁，
// 		jnb local_003
// 		mov ecx,100
// local_002:
// 		loop local_002
// 		mov eax,TmpCurrentCPUIndex
// 		cmp eax,gdwCurrentCPUIndex
// 		jnz local_006
// 		inc gdwMulitCpuSpinlock        //如果当前的CPU已经停止了其他CPU 则只增加锁的计数后直接退出
// 		jmp local_quit
// local_006:
// 		push 10
// 		push 10
// 		call Beep
// 		cmp gdwMulitCpuSpinlock,0      //如果是其他CPU保持这个锁 则等待其他CPU释放掉这个锁   
// 		jnz local_006
// 		jmp local_020
// local_003:
// 		mov gdwCurrentCPUIndex,eax
// 		inc gdwMulitCpuSpinlock		
// 		mov eax, gdwLocalAPICLineAddress
// local_009:
// 		test DWORD PTR [eax+0x300],0x1000         //Delivery Mode  判断时候有 Send Pending
// 		jnz local_009
// 		mov ebx,0xc44ff                           //NMI 物理模式 EDGE  高电平出发  All Excluding Self
// 		mov gdwMulitCpuSendIPIFlags,1
// 		mov [eax+0x300],ebx
// local_011:
// 		test DWORD PTR [eax+0x300],0x1000         //等待中断被处理
// 		jnz local_011
// local_12:
// 		cmp gdwMulitCpuSendIPIFlags,0			//等待其他CPU进入死循环
// 		jnz local_12		
// local_quit:
// 		add esp,4
// 		pop ds
// 		popad
// 		popfd
// 		ret
// 	}
// }

DWORD GetCurrentCPULocalAPICID()
{
	DWORD LocalApicID,i;
	PKPCR FSBaseAddress;
	if(gCPUNumbers==1)
		return 0;
	LocalApicID = GetLocalAPICID();
	if(gCPULocalAPIC_ID[LocalApicID]<=0xf)
		return gCPULocalAPIC_ID[LocalApicID];
	FSBaseAddress =(PKPCR) GetSegmentBaseAddress((WORD)gSystemFSRegisterSelector);
	for(i=0;i<gCPUNumbers;i++)
	{
		if(gPCRArray[i]==FSBaseAddress)
		{
			gCPULocalAPIC_ID[LocalApicID]=(BYTE)i;
			return i;
		}
	}
	return 0;
}

