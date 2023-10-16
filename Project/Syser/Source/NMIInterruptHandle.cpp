#include "StdAfx.h"
#include "MultiCPU.h"
#include "LocalAPIC.h"
#include "NMIInterruptHandle.h"
#include "Syser.h"

#define SAVECONTEXT_OFFSET 8


#ifdef __cplusplus
extern "C" {
#endif

	DWORD dwgcou=0;
	DWORD dwkCount=0;
	DWORD gLoopCpuNumber=0;
	bool gbSyserDRXChg=false;			//用于Active后标示DR寄存器是否被改变

#ifdef __cplusplus
}; // extern "C"
#endif


// 
// __declspec(naked) void LoadContext()
// {
// 	DWORD CurrentCpuID;
// 	X86_REG_CONTEXT TmpContext;	
// 	__asm
// 	{
// 		push ebp 
// 		mov ebp,esp 
// 		sub esp,__LOCAL_SIZE
// 		mov eax,dr0
// 		mov TmpContext.DR[0*4],eax
// 		mov eax,dr1
// 		mov TmpContext.DR[1*4],eax
// 		mov eax,dr2
// 		mov TmpContext.DR[2*4],eax
// 		mov eax,dr3
// 		mov TmpContext.DR[3*4],eax
// 		mov eax,dr6
// 		mov TmpContext.DR[6*4],eax
// 		mov eax,dr7
// 		mov TmpContext.DR[7*4],eax
// 		sldt word ptr TmpContext.LDT
// 		str word ptr TmpContext.TR
// 		sgdt fword ptr TmpContext.GDTLimit
// 		sidt fword ptr TmpContext.IDTLimit
// 		mov eax,[ebp+0x10]
// 		mov TmpContext.GeneReg[EDI_IDX*4],eax 
// 		mov eax,[ebp+0x14]
// 		mov TmpContext.GeneReg[ESI_IDX*4],eax 
// 		mov eax,[ebp+0x18]
// 		mov TmpContext.GeneReg[EBP_IDX*4],eax 
// 		mov eax,[ebp+0x1c]
// 		mov TmpContext.GeneReg[ESP_IDX*4],eax 
// 		mov eax,[ebp+0x20]
// 		mov TmpContext.GeneReg[EBX_IDX*4],eax 
// 		mov eax,[ebp+0x24]
// 		mov TmpContext.GeneReg[EDX_IDX*4],eax 
// 		mov eax,[ebp+0x28]
// 		mov TmpContext.GeneReg[ECX_IDX*4],eax 
// 		mov eax,[ebp+0x2c]
// 		mov TmpContext.GeneReg[EAX_IDX*4],eax 
// 		mov eax,[ebp+0x40]
// 		mov TmpContext.EFlags,eax 
// 		mov eax,[ebp+0x38]
// 		mov TmpContext.EIP,eax 
// 		
// 		mov eax,cr0
// 		mov TmpContext.CR[0*4],eax
// 		mov eax,cr2
// 		mov TmpContext.CR[2*4],eax
// 		mov eax,cr3
// 		mov TmpContext.CR[3*4],eax
// 		_emit(0x0f)//mov eax,cr4 M$ 的编译器不支持 mov eax,cr4 指令
// 		_emit(0x20)
// 		_emit(0xe0)
// 		mov TmpContext.CR[4*4],eax
// 		mov eax,TmpContext.EFlags
// 		test eax,0x20000
// 		jz local_001
// 		mov eax,[ebp+0x44]
// 		mov TmpContext.GeneReg[ESP_IDX*4],eax
// 		mov eax,[ebp+0x48]
// 		mov TmpContext.SegReg[SS_IDX*2],ax
// 		mov eax,[ebp+0x4c]
// 		mov TmpContext.SegReg[ES_IDX*2],ax
// 		mov eax,[ebp+0x50]
// 		mov TmpContext.SegReg[DS_IDX*2],ax
// 		mov eax,[ebp+0x54]
// 		mov TmpContext.SegReg[FS_IDX*2],ax
// 		mov eax,[ebp+0x58]
// 		mov TmpContext.SegReg[GS_IDX*2],ax
// 		jmp local_002
// local_001:
// 		mov eax,[ebp+8]
// 		mov TmpContext.SegReg[ES_IDX*2],ax 
// 		mov eax,[ebp+0xc]
// 		mov TmpContext.SegReg[DS_IDX*2],ax
// 		mov ax,fs 
// 		mov TmpContext.SegReg[FS_IDX*2],ax
// 		mov ax,gs
// 		mov TmpContext.SegReg[GS_IDX*2],ax
// 		mov eax,[ebp+0x3c]
// 		mov TmpContext.SegReg[CS_IDX*2],ax
// 		test ax,3
// 		jnz local_005
// 		lea eax,[ebp+0x44]
// 		mov TmpContext.GeneReg[ESP_IDX*4],eax 
// 		mov ax,ss 
// 		mov TmpContext.SegReg[SS_IDX*2],ax
// 		jmp local_002
// local_005:
// 		mov eax,[ebp+0x44]
// 		mov TmpContext.GeneReg[ESP_IDX*4],eax 
// 		mov eax,[ebp+0x48]
// 		mov TmpContext.SegReg[SS_IDX*2],ax
// local_002:		
// 	}
// 	CurrentCpuID = GetCurrentCPULocalAPICID();
// 	SaveLocalApic(&gpMCPULocalApic[CurrentCpuID]);
// 	gpMCPUReg[CurrentCpuID]=TmpContext;
// 	gpMCPUReg[CurrentCpuID].LocalAPIC=&gpMCPULocalApic[CurrentCpuID];
// 	__asm
// 	{
// 		mov esp,ebp 
// 		pop ebp
// 		ret
// 	}
// }

void UpdateOtherCPUDRX()
{
	gbSyserDRXChg = true;
}

// 
// void EnterLoop(DWORD* dwPtr)
// {
// 	__asm
// 	{
// 		mov eax,gdwLocalAPICLineAddress 
// 		mov ebx,[eax+0x80]
// 		push ebx
// 		mov ebx,0xff
// 		mov [eax+0x80],ebx
// 	}
// 
// 	DWORD CurrentCpuID = GetCurrentCPULocalAPICID();
// 	gdwMulitCpuSendIPIFlags=0;
// 	__asm lock inc dword ptr gLoopCpuNumber
// 	while(gdwMulitCpuSpinlock)
// 	{
// 		if(gbSyserDRXChg)//2 CPU以上要各自分配个变量来表示
// 		{
// 			SaveSyserDRX();
// 			gbSyserDRXChg = false;
// 		}
// 	}
// 	__asm lock dec dword ptr gLoopCpuNumber
// 	__asm
// 	{
// 		mov eax,gdwLocalAPICLineAddress
// 		pop ebx
// 		mov [eax+0x80],ebx
// 	}
// }

// 
// void SaveSyserDRX()
// {
// 	__asm
// 	{
// 		push	eax
// 		mov		eax,SyserDR[0*4]
// 		mov		dr0,eax
// 		mov		eax,SyserDR[1*4]
// 		mov		dr1,eax
// 		mov		eax,SyserDR[2*4]
// 		mov		dr2,eax
// 		mov		eax,SyserDR[3*4]
// 		mov		dr3,eax
// 		xor		eax,eax 
// 		mov		dr6,eax
// 		mov		eax,SyserDR[7*4]
// 		and		eax,0xffffdfff
// 		mov		dr7,eax
// 		pop		eax
// 	}
// }
// 
// __declspec(naked) void SaveSyserDRXNew()
// {
// 	__asm
// 	{
// 		push	eax
// 		mov		eax,SyserDR[2*4]
// 		mov		dr2,eax
// 		mov		eax,SyserDR[1*4]
// 		mov		dr1,eax		
// 		mov		eax,SyserDR[3*4]
// 		mov		dr3,eax
// 		mov		eax,SyserDR[0*4]
// 		mov		dr0,eax
// 		xor		eax,eax 
// 		mov		dr6,eax
// 		mov		eax,SyserDR[7*4]
// 		and		eax,0xffffdfff
// 		mov		dr7,eax
// 		pop		eax
// 		ret
// 	}
// }
// 

//DWORD int2eip=0;
//DWORD gNmiCount=0;

#ifdef __cplusplus
extern "C" {
#endif

extern DWORD gdwExitNmiLock;

#ifdef __cplusplus
}; // extern "C"
#endif
// 
// __declspec (naked) void NMIInterruptService()
// {
// 	DWORD *dwEBP;
// 	__asm
// 	{
// 		pushfd
// 		cmp		ss:gCPUNumbers,1
// 		jnz		MultiCPUMachine
// 		popfd
// 		ret     // 在单cpu 的机器上直接返回到 windows 的中断. fixme 
// MultiCPUMachine:
// 		pushad
// 		push	ds
// 		push	es		
// 		cli
// 		mov		ax,ss
// 		mov		ds,ax
// 		mov		es,ax
// 		mov eax,[esp+12*4]
// 		mov int2eip,eax
// 		lock inc gNmiCount
// 	}
// 	
// 	DisableDebugRegisterMontior();
// 	LoadContext();
// 	__asm
// 	{
// 		push esp 
// 		call EnterLoop		
// 	}	
// 	if(gpSyser->m_bDbgRegAccessMon)
// 		SaveSyserDRXNew();
// 	if(gNmiCount<2)
// 		EnableDebugRegisterMontior();
// 	__asm
// 	{
// 		lock dec gNmiCount
// 		pop		es
// 		pop		ds
// 		popad
// 		popfd
// 		lea		esp,[esp+4]
// 		mov		gdwExitNmiLock,0
// 		iretd
// 	}
// }
