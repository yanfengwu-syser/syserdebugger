#include "StdAfx.h"
#include "Syser.h"

#ifdef __cplusplus
extern "C" {
#endif

//
//	调用很别扭
//

VOID FASTCALL SyserOnPatchBugCheckExMIniCall(PVOID*	NextAddress);

VOID SyserNopLoop(VOID);

#ifdef __cplusplus
}; // extern "C"
#endif

void OnPatchBugCheckEx()
{
	static DWORD gPrevExceptionEIP;
	static DWORD gPrevExceptionInterruptNum;
	DWORD* pStack=*(DWORD**)&Reg.GeneReg[ESP_IDX];
	DWORD looplabel;
	DWORD CurrentCpuID;
	DWORD dwCurEIP;
	DWORD* dwValue;
	CurrentCpuID = GetCurrentCPULocalAPICID();

	OUTPUT(WSTR("%<f>Syser : KeBugCheck %x, {%08x, %08x, %08x, %08x}\n"),pStack[1],pStack[2],pStack[3],pStack[4],pStack[5]);
	SRCEXPLR_OUTPUT(WSTR("%<f>Syser : KeBugCheck %x, {%08x, %08x, %08x, %08x}\n"),pStack[1],pStack[2],pStack[3],pStack[4],pStack[5]);
	SYSEXPLR_OUTPUT(WSTR("%<f>Syser : KeBugCheck %x, {%08x, %08x, %08x, %08x}\n"),pStack[1],pStack[2],pStack[3],pStack[4],pStack[5]);
	if(gpSyser->m_bFaultsStat==false)
		return ;
	dwCurEIP=ExceptionReg[CurrentCpuID].EIP;

	if(pStack[4]==0x7f)
	{
		if(pStack[5]==ExceptionInterruptNum)
			goto local_001;
	}

	if(dwCurEIP==pStack[2]||dwCurEIP==pStack[3]||dwCurEIP==pStack[4]||dwCurEIP==pStack[5])
	{
local_001:
		if((dwCurEIP>=gpSyser->m_SysInfo.m_SyserBase && 
			dwCurEIP<gpSyser->m_SysInfo.m_SyserHighBase))
		{				
			OUTPUT(WSTR("%<6>Syser : SYSER crash  , exception EIP = %08X\n"),ExceptionReg[CurrentCpuID].EIP);
// 			__asm
// 			{
// 				call local_0021
// local_0011:
// 
// 				jmp local_0011
// local_0021:
// 				pop eax 
// 				mov looplabel,eax
// 			}

			SyserOnPatchBugCheckExMIniCall((PVOID*)&looplabel);
			SyserNopLoop();
			Reg.EIP=looplabel;
		}
		else
		{
			if(gPrevExceptionEIP == dwCurEIP && gPrevExceptionInterruptNum == ExceptionReg[CurrentCpuID].ExceptionInterruptNumber)
			{
				return;
			}
			Reg.GeneReg[EAX_IDX]=ExceptionReg[CurrentCpuID].GeneReg[EAX_IDX];
			Reg.GeneReg[EBX_IDX]=ExceptionReg[CurrentCpuID].GeneReg[EBX_IDX];
			Reg.GeneReg[ECX_IDX]=ExceptionReg[CurrentCpuID].GeneReg[ECX_IDX];
			Reg.GeneReg[EDX_IDX]=ExceptionReg[CurrentCpuID].GeneReg[EDX_IDX];
			Reg.GeneReg[ESP_IDX]=ExceptionReg[CurrentCpuID].GeneReg[ESP_IDX];
			Reg.GeneReg[EBP_IDX]=ExceptionReg[CurrentCpuID].GeneReg[EBP_IDX];
			Reg.GeneReg[ESI_IDX]=ExceptionReg[CurrentCpuID].GeneReg[ESI_IDX];
			Reg.GeneReg[EDI_IDX]=ExceptionReg[CurrentCpuID].GeneReg[EDI_IDX];
			Reg.SegReg[CS_IDX]=ExceptionReg[CurrentCpuID].SegReg[CS_IDX];
			Reg.SegReg[DS_IDX]=ExceptionReg[CurrentCpuID].SegReg[DS_IDX];
			Reg.SegReg[ES_IDX]=ExceptionReg[CurrentCpuID].SegReg[ES_IDX];
			Reg.SegReg[FS_IDX]=ExceptionReg[CurrentCpuID].SegReg[FS_IDX];
			Reg.SegReg[GS_IDX]=ExceptionReg[CurrentCpuID].SegReg[GS_IDX];
			Reg.SegReg[SS_IDX]=ExceptionReg[CurrentCpuID].SegReg[SS_IDX];
			Reg.EIP=ExceptionReg[CurrentCpuID].EIP;
			Reg.EFlags=ExceptionReg[CurrentCpuID].EFlags;
			OldESP=ExceptionReg[CurrentCpuID].GeneReg[ESP_IDX];
			OldESP-=0xc;
			dwValue=(DWORD*)OldESP;
			gPrevExceptionEIP=ExceptionReg[CurrentCpuID].EIP;
			gPrevExceptionInterruptNum=ExceptionReg[CurrentCpuID].ExceptionInterruptNumber;
			OUTPUT(WSTR("%<3>Syser : system crash  , exception EIP = %08X\n"),ExceptionReg[CurrentCpuID].EIP);
			OUTPUT(WSTR("%<3>Syser : reboot after syser exitting!\n"));
			SYSEXPLR_OUTPUT(WSTR("%<3>Syser : system crash  , exception EIP = %08X\n"),ExceptionReg[CurrentCpuID].EIP);
			SYSEXPLR_OUTPUT(WSTR("%<3>Syser : reboot after syser exitting!\n"));
			gpSyser->m_MainFrame.m_SourceDebugFrameWnd.m_MonitorTabWnd.SetActiveWnd(1);
			SRCEXPLR_OUTPUT(WSTR("%<3>Syser : system crash  , exception EIP = %08X\n"),ExceptionReg[CurrentCpuID].EIP);
			SRCEXPLR_OUTPUT(WSTR("%<3>Syser : reboot after syser exitting!\n"));			
			RUNCMD(WSTR("T"));				
			gpSyser->m_pDebugger->m_bPrevPatchBP=false;
			gbBugCheckExExit=true;

			while(WaitForKey()!=1);
		}
	}
	else
	{
		if(ExceptionReg[CurrentCpuID].EIP<gpSyser->m_SysInfo.m_SyserBase || ExceptionReg[CurrentCpuID].EIP>=gpSyser->m_SysInfo.m_SyserHighBase)
		{
			OUTPUT(WSTR("%<3>Syser : system crash  , exception EIP = %08X\n"),ExceptionReg[CurrentCpuID].EIP);
			OUTPUT(WSTR("%<3>Syser : reboot after syser exitting!\n"));
			SYSEXPLR_OUTPUT(WSTR("%<3>Syser : system crash  , exception EIP = %08X\n"),ExceptionReg[CurrentCpuID].EIP);
			SYSEXPLR_OUTPUT(WSTR("%<3>Syser : reboot after syser exitting!\n"));
			gpSyser->Active();
		}
		else
		{
			OUTPUT(WSTR("%<6>Syser : SYSER crash  , exception EIP = %08X\n"),ExceptionReg[CurrentCpuID].EIP);
// 			__asm
// 			{
// 				call local_002
// local_0013:
// 				jmp local_0013
// local_002:
// 				pop eax 
// 					mov looplabel,eax
// 			}

			SyserOnPatchBugCheckExMIniCall((PVOID*)&looplabel);
			SyserNopLoop();
			Reg.EIP=looplabel;
		}
	}
}

void PatchKeBugCheckEx()
{
	BYTE Value=0;
	void* pKeBugCheckEx=(void*)KeBugCheckEx;
	if(pKeBugCheckEx==NULL)
		return;
	if(ReadByte((BYTE*)pKeBugCheckEx,&Value)==false)
		return;
	gpBugCheckExAddress=*(DWORD*)&pKeBugCheckEx;
	gbBugCheckExFirstByteIsCC = (Value==0xcc)?true:false;
	PATCH_SYSTEM("KeBugCheckEx",pKeBugCheckEx,OnPatchBugCheckEx);
	gbBugCheckExFlags=true;
}

