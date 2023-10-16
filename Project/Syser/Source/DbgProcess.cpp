#include "StdAfx.h"
#include "Syser.h"
#include "SystemIoctl.h"
#include "NMIInterruptHandle.h"

CDbgProcess::CDbgProcess()
{
	m_pExecutePoint = &Reg.EIP;
	m_pOrgDbgProc = NULL;
	m_pCodeBPMap = &gpSyser->m_SyserUI.m_CodeBPMap;
	m_pDataBPList = &gpSyser->m_SyserUI.m_DataBPList;
	m_bPrevPatchBP = false;
}

CDbgProcess::~CDbgProcess()
{
}

void CDbgProcess::InitProcess(DWORD PID)
{
	char szBuffer[MAX_FN_LEN];
	WCHAR szProceName[MAX_FN_LEN];
	PEPROCESS Pr = NULL;
	PsLookupProcessByProcessId(NUM_TO_PTR(PID),&Pr);
	if(Pr)
	{
		gpSyser->m_SysInfo.GetProcessName(Pr,szProceName,MAX_FN_LEN);		
		m_CR3 = ((DWORD*)Pr)[gpSyser->m_SysInfo.m_ProcCR3dwOff];
		m_ProcNameW = szProceName;
		if(gpSyser->m_SysInfo.m_PEBOffsetOfEPROCESS)
		{
			BYTE* Pointer;
			Pointer = *(BYTE**)&Pr;
			m_pCurrentPEB = *(PEB**)&Pointer[gpSyser->m_SysInfo.m_PEBOffsetOfEPROCESS];
		}
		else
			m_pCurrentPEB = (PEB*)0;
		m_PEProcess=Pr;
	}
	else
	{
		m_CR3 = SyserGetCR3Reg();
		m_pCurrentPEB = NULL;
		if(PID)
			m_ProcNameW = WSTR("System");
		else
			m_ProcNameW = WSTR("System Idle Process");
		m_PEProcess=NULL;
	}
	UnicodeToAnsi(m_ProcNameW,szBuffer,sizeof(szBuffer));
	m_ProcName = szBuffer;
	m_PID = PID;
	Init(&gpSyser->m_SyserUI.m_SyserDI);
	UnicodeToAnsi(m_ProcNameW,szBuffer,sizeof(szBuffer));
	Open(szBuffer);
}

void CDbgProcess::Release()
{
	CCodeBPMap::IT Iter = m_pCodeBPMap->Begin();
	while(Iter.IsExist())
	{
		if(Iter->PID == m_PID)
		{
			CCodeBPMap::IT RemoveIter=Iter;
			Iter++;
			//::DbgPrint("Syser : Clear Left BP [%s] %08X %s\n",(PCSTR)m_ProcName,RemoveIter->Address,(PCSTR)RemoveIter->Name);
			if(RemoveCodeBP(&(*RemoveIter))==false)
				::DbgPrint("Syser : Fail to clear left BP [%s] %08X %s\n",(PCSTR)m_ProcName,RemoveIter->Address,(PCSTR)RemoveIter->Name);
		}
		else
			Iter++;
	}
	gpSyser->ClearProcessBPR(*(DWORD*)&m_PEProcess);
	Close();
	CX86Debugger::Release();
}

ULSIZE CDbgProcess::ReadMemory(ULPOS Address,void*Buffer,ULSIZE Size)
{
	return ReadProcessMemory(Address,Buffer,Size);
}

ULSIZE CDbgProcess::WriteMemory(ULPOS Address,void*Buffer,ULSIZE Size)
{
	return WriteProcessMemory(Address,Buffer,Size);
}

ULSIZE CDbgProcess::MoveMem(ULPOS DesAddr,ULPOS SrcAddr,ULSIZE Size)
{
	return SyserPrivateMemCopy((BYTE*)DesAddr,(BYTE*)SrcAddr,Size);
}

bool CDbgProcess::SaveRegister()
{
	return true;
}

bool CDbgProcess::UpdateRegister()
{
	return true;
}

bool CDbgProcess::ContinueDebug(bool bRestoreScreen)
{
	gpSyser->m_bSaveReg=false;
	gpSyser->Exit(bRestoreScreen);
	return true;
}

bool CDbgProcess::SetCodeBreakPoint(BREAK_POINT&BP)
{
	bool Result = SetCCBP(BP);
	if(Result)
	{
		if(BP.Address >= gpSyser->m_SysInfo.m_SystemStartAddr)
		{
			if(gpSyser->m_pCsrssProcess && gpSyser->m_SysInfo.m_win32kImageBase)
			{//如果断点在系统空间win32k范围则改变断点Owner为csrss
				if( BP.Address >= gpSyser->m_SysInfo.m_win32kImageBase && 
					BP.Address < gpSyser->m_SysInfo.m_win32kImageBase+gpSyser->m_SysInfo.m_win32kImageSize)
				{
					BP.OwnerName = gpSyser->m_pCsrssProcess->m_ProcName;
					BP.PID = gpSyser->m_pCsrssProcess->m_PID;
				}
			}
			else
			{//如果断点在系统空间则改变断点Owner为System
				BP.PID = gpSyser->m_pSysDebugger->m_PID;
				BP.OwnerName = gpSyser->m_pSysDebugger->m_ProcName;
			}
		}
	}
	return Result;
}

bool CDbgProcess::ClearCodeBreakPoint(BREAK_POINT&BP)
{
	return ClearCCBP(BP);
}

bool CDbgProcess::SetDataBreakPoint(BREAK_POINT&BP)
{
	bool Result = SetX86HDBP(BP,SyserDR,&SyserDR[7]);
	if(Result)
	{
		gpSyser->m_bDbgRegAccessMon = true;
		gpSyser->m_bUpdateReg = true;
		memcpy(Reg.DR,SyserDR,sizeof(SyserDR));
		UpdateOtherCPUDRX();//通知其他CPU,释放时,设置SyserDRX
		BP.OwnerName = gpSyser->m_pSysDebugger->m_ProcName;
		BP.PID = gpSyser->m_pSysDebugger->m_PID;
	}
	return Result;
}

bool CDbgProcess::ClearDataBreakPoint(BREAK_POINT&BP)
{
	bool Result = ClearX86HDBP(BP,SyserDR,&SyserDR[7]);
	if(Result)
	{
		gpSyser->m_bDbgRegAccessMon = (SyserDR[7]&0xFF)!=0;
		gpSyser->m_bUpdateReg = true;
		memcpy(Reg.DR,SyserDR,sizeof(SyserDR));
		UpdateOtherCPUDRX();//通知其他CPU,释放时,设置SyserDRX
	}
	return Result;
}

bool CDbgProcess::MapToPhysAddr(ULPOS Address,ULONGLONG&PhysAddr)
{
	return MapToPAddr(Address,&PhysAddr);
}

bool CDbgProcess::SwitchProcessSpace(UINT PID)
{
	CDbgProcess*pNewProc;
	pNewProc = gpSyser->m_SysInfo.GetProcess(PID);
	if(pNewProc)
	{
		if(pNewProc->m_CR3 != SyserGetCR3Reg())
		{
			m_pOrgDbgProc = gpSyser->m_pDebugger;
			gpSyser->MapToProcess(pNewProc);
		}
		return true;
	}
	return false;
}

void CDbgProcess::RestoreProcessSpace()
{
	if(m_pOrgDbgProc)
	{
		gpSyser->MapToProcess(m_pOrgDbgProc);
		m_pOrgDbgProc = NULL;
	}
}

void CDbgProcess::PatchSystem(PCSTR Name,ULPOS Address,PVFV PatchFunc)
{
	BREAK_POINT*pBP;
	pBP = gpSyser->m_pSysDebugger->InsertCodeBP(Address,BP_TYPE_PATCH,BP_STATE_ENABLE);
	if(pBP)
	{
		pBP->UserData = (NUM_PTR)PatchFunc;
		pBP->Name = Name;
		DbgPrint("Syser : Patch %s %08X\n",Name,Address);
	}
	else
	{
		DbgPrint("Syser : Fail to patch %s %08X\n",Name,Address);
	}
}

bool CDbgProcess::SetSingleStep()
{
	Reg.EFlags|=0x100;
	gpSyser->m_bUpdateReg=true;
	gPrevStepEIP=Reg.EIP;
	return true;
}

bool CDbgProcess::RemoveSingleStep()
{
	Reg.EFlags&=0xFFFFFEFF;
	gpSyser->m_bUpdateReg=true;
	return true;
}

void CDbgProcess::GetCPUX86RegPtr(X86_CPU_REG_PTR*pCPURegPtr,DWORD dwCPUID)
{
	if(dwCPUID>gCPUNumbers)
		dwCPUID=0;
	pCPURegPtr->pCS = &gpMCPUReg[dwCPUID].SegReg[CS_IDX];
	pCPURegPtr->pDS = &gpMCPUReg[dwCPUID].SegReg[DS_IDX];
	pCPURegPtr->pES = &gpMCPUReg[dwCPUID].SegReg[ES_IDX];
	pCPURegPtr->pFS = &gpMCPUReg[dwCPUID].SegReg[FS_IDX];
	pCPURegPtr->pGS = &gpMCPUReg[dwCPUID].SegReg[GS_IDX];
	pCPURegPtr->pSS = &gpMCPUReg[dwCPUID].SegReg[SS_IDX];

	pCPURegPtr->pEAX = &gpMCPUReg[dwCPUID].GeneReg[EAX_IDX];
	pCPURegPtr->pEBX = &gpMCPUReg[dwCPUID].GeneReg[EBX_IDX];
	pCPURegPtr->pECX = &gpMCPUReg[dwCPUID].GeneReg[ECX_IDX];
	pCPURegPtr->pEDX = &gpMCPUReg[dwCPUID].GeneReg[EDX_IDX];
	pCPURegPtr->pESI = &gpMCPUReg[dwCPUID].GeneReg[ESI_IDX];
	pCPURegPtr->pEDI = &gpMCPUReg[dwCPUID].GeneReg[EDI_IDX];
	pCPURegPtr->pEBP = &gpMCPUReg[dwCPUID].GeneReg[EBP_IDX];
	pCPURegPtr->pESP = &gpMCPUReg[dwCPUID].GeneReg[ESP_IDX];

	pCPURegPtr->pEFL = (EFL_REG*)&gpMCPUReg[dwCPUID].EFlags;
	pCPURegPtr->pEIP = &gpMCPUReg[dwCPUID].EIP;

	pCPURegPtr->pDR[0] = &gpMCPUReg[dwCPUID].DR[0];
	pCPURegPtr->pDR[1] = &gpMCPUReg[dwCPUID].DR[1];
	pCPURegPtr->pDR[2] = &gpMCPUReg[dwCPUID].DR[2];
	pCPURegPtr->pDR[3] = &gpMCPUReg[dwCPUID].DR[3];
	pCPURegPtr->pDR[6] = &gpMCPUReg[dwCPUID].DR[6];
	pCPURegPtr->pDR[7] = &gpMCPUReg[dwCPUID].DR[7];
	pCPURegPtr->pGDTRBase = &gpMCPUReg[dwCPUID].GDTBase;
	pCPURegPtr->pGDTRLimit = &gpMCPUReg[dwCPUID].GDTLimit;
	pCPURegPtr->pIDTRBase = &gpMCPUReg[dwCPUID].IDTBase;
	pCPURegPtr->pIDTRLimit = &gpMCPUReg[dwCPUID].IDTLimit;
	pCPURegPtr->pLDTR = &gpMCPUReg[dwCPUID].LDT;
	pCPURegPtr->pTR = &gpMCPUReg[dwCPUID].TR;
}

void CDbgProcess::GetX86RegPtr(X86_CPU_REG_PTR*pCPURegPtr)
{
	pCPURegPtr->pCS = &Reg.SegReg[CS_IDX];
	pCPURegPtr->pDS = &Reg.SegReg[DS_IDX];
	pCPURegPtr->pES = &Reg.SegReg[ES_IDX];
	pCPURegPtr->pFS = &Reg.SegReg[FS_IDX];
	pCPURegPtr->pGS = &Reg.SegReg[GS_IDX];
	pCPURegPtr->pSS = &Reg.SegReg[SS_IDX];

	pCPURegPtr->pEAX = &Reg.GeneReg[EAX_IDX];
	pCPURegPtr->pEBX = &Reg.GeneReg[EBX_IDX];
	pCPURegPtr->pECX = &Reg.GeneReg[ECX_IDX];
	pCPURegPtr->pEDX = &Reg.GeneReg[EDX_IDX];
	pCPURegPtr->pESI = &Reg.GeneReg[ESI_IDX];
	pCPURegPtr->pEDI = &Reg.GeneReg[EDI_IDX];
	pCPURegPtr->pEBP = &Reg.GeneReg[EBP_IDX];
	pCPURegPtr->pESP = &Reg.GeneReg[ESP_IDX];

	pCPURegPtr->pEFL = (EFL_REG*)&Reg.EFlags;
	pCPURegPtr->pEIP = &Reg.EIP;

	pCPURegPtr->pDR[0] = &Reg.DR[0];
	pCPURegPtr->pDR[1] = &Reg.DR[1];
	pCPURegPtr->pDR[2] = &Reg.DR[2];
	pCPURegPtr->pDR[3] = &Reg.DR[3];
	pCPURegPtr->pDR[6] = &Reg.DR[6];
	pCPURegPtr->pDR[7] = &Reg.DR[7];
	pCPURegPtr->pGDTRBase = &Reg.GDTBase;
	pCPURegPtr->pGDTRLimit = &Reg.GDTLimit;
	pCPURegPtr->pIDTRBase = &Reg.IDTBase;
	pCPURegPtr->pIDTRLimit = &Reg.IDTLimit;
	pCPURegPtr->pLDTR = &Reg.LDT;
	pCPURegPtr->pTR = &Reg.TR;
	pCPURegPtr->pCR2 = &Reg.CR[2];
}

bool CDbgProcess::GetSegRegBase(int SegIndex,DWORD*pAddress,DWORD *pSize)
{
	X86_SEGMENT_DESCRIPTOR x86SegDescr;
	if(pAddress==NULL || GetSegDescr((WORD)SegIndex,&x86SegDescr)==false)
		return false;
	*pAddress = x86SegDescr.base_L0+(x86SegDescr.base_L1<<8)+(x86SegDescr.base_H0<<16)+(x86SegDescr.base_H1<<24);
	return true;
}

bool CDbgProcess::HandleInt1(ULPOS Address)
{
	BREAK_POINT*pBP=NULL;
	bool bActive = false;
	pBP = GetCodeBP(Address);
	if(pBP)
	{
		pBP->BPCount++;		
	}

	if(Reg.DR[6] & DR6_BS)
	{                             //如果是单步执行断点						
		gpSyser->m_bHandle = RecoverBreakPoint()>0;
		if(m_bPrevPatchBP && gpSyser->m_bHandle)
		{			
			RemoveSingleStep();
			m_bPrevPatchBP = false;
			return true;
		}		
		ProcessSpecialCode(gPrevStepEIP);
		RemoveSingleStep();
		//pBP = GetCodeBP(Address);
		if(pBP && pBP->State==BP_STATE_ENABLE)
		{	//当单步和断点重合时
			if(WriteProcessMemory(Address,&pBP->CodeBackup,1))//恢复原指令
				pBP->State = BP_STATE_RECOV;			
			if(gpSyser->m_SyserUI.m_SyserDI.TestCondition(pBP->Condition,pBP))
			{
				gpSyser->m_SyserUI.m_SyserDI.RunCmdList(pBP->DoCmd);
				if((pBP->Type & BP_TYPE_PATCH))
				{
					if(pBP->UserData)
						((PVFV)pBP->UserData)();
				}
				else
				{	//遇到其他Active断点时重置条件Trace
					if((pBP->Type & BP_TYPE_DEBUG)==0)
					{
						gpSyser->m_SyserUI.m_SyserDI.ResetTrace();
						bActive = true;
					}
				}
			}
			if(pBP->Type&BP_TYPE_ONCE)//删除一次性断点
			{
				RemoveCodeBP(pBP);
			}
		}
		RemoveAllCodeBP(BP_TYPE_DEBUG);
		if(gpSyser->m_SyserUI.m_SyserDI.m_TraceType!=TRACE_NULL)
		{		
			gpSyser->m_bHandle = true;
			if(gpSyser->m_SyserUI.m_SyserDI.IsHandledTraceEvent())
				bActive = true;
		}
	}
	else
	{
		if( (Reg.DR[6]&DR6_BD) || (gpSyser->m_bDbgRegAccessMon&&((Reg.DR[6]&0xF)==0)))
		{//监控其他程序修改
			ExcuteDebugRegisterMontior((BYTE*)Reg.EIP);
			Reg.EIP+=3;
			gpSyser->m_bUpdateReg=true;
			return true;
		}
		if(gpSyser->m_bDbgRegAccessMon==false)
			return false;
			if(ProcessHardwareBreak())
			{
				bActive = true;
			}										
			RemoveAllCodeBP(BP_TYPE_DEBUG);
		}

	if(bActive)
	{
		gpSyser->m_bHandle = true;
		gpSyser->Active();
	}
	if(IsRecoverBPExist())
	{
		SetSingleStep();
	}
	gpSyser->SetBPR();
	return gpSyser->m_bHandle;
}

bool CDbgProcess::HandleInt3(ULPOS Address)
{
	bool bActive;
	bool bPopup;
	BREAK_POINT*pBP;
		
	pBP = GetCodeBP(Address);
	if(pBP)
		pBP->BPCount++;//增加断点执行计数
	if(pBP==NULL || pBP->State!=BP_STATE_ENABLE)
	{//不是自己的断点
		bPopup=false;
		if(gpSyser->m_Interrupt3HereStat==1 || (gpSyser->m_Interrupt3HereStat==2 && Reg.EIP > gpSyser->m_SysInfo.m_SystemStartAddr))		
			bPopup=true;				
		if(bPopup)
		{//在和其他的调试器协作
			gpSyser->m_bHandle = true;
			gpSyser->Active();
			return gpSyser->m_bHandle;
		}
		return false;
	}
	Reg.EIP--;
	gpSyser->m_bUpdateReg=true;
	if(WriteProcessMemory(Address,&pBP->CodeBackup,1))//恢复原指令
		pBP->State = BP_STATE_RECOV;
	if(gpSyser->m_SyserUI.m_SyserDI.TestCondition(pBP->Condition,pBP)==false)
	{//此断点条件不满足直接返回
		SetSingleStep();
		return true;
	}
	gpSyser->m_bExit=false;
	gpSyser->m_SyserUI.m_SyserDI.RunCmdList(pBP->DoCmd);
	if(pBP->DoCmd && gpSyser->m_bExit)
	{//此断点条件不满足直接返回
		//这种情况是 runcmdlist 中有 x 或 exit 命令
		SetSingleStep();
		return true;
	}
	bActive = false;
	gpSyser->m_bHandle = true;
	if(pBP->Type & BP_TYPE_PATCH)
	{//Patch放过
		m_bPrevPatchBP = true;
		if(pBP->UserData)
		{
			gbActive=true;
			((PVFV)pBP->UserData)();
			gbActive=false;
		}
	}
	else
	{
		if((pBP->Type & BP_TYPE_DEBUG)==0)
		{//遇到其他Active断点时重置条件Trace,并且记录位置点
			ACTIVE_CODE_VIEW->RecordCurAddr(pBP->Address,ACTIVE_CODE_VIEW->m_CurAddr);
			DisplayCodeBP(pBP);
			gpSyser->m_SyserUI.m_SyserDI.ResetTrace();
			bActive = true;
		}
		RemoveAllCodeBP(BP_TYPE_DEBUG);
		if(gpSyser->m_SyserUI.m_SyserDI.IsHandledTraceEvent())
			bActive=true;
	}
	if(pBP->Type&BP_TYPE_ONCE)//删除一次性断点
		RemoveCodeBP(pBP);
	if(bActive)
	{
		gpSyser->Active();
	}
	if(IsRecoverBPExist())
	{
		SetSingleStep();
	}
	return gpSyser->m_bHandle;
}

void CDbgProcess::DisplayCodeBP(BREAK_POINT*pBP)
{
	if(pBP->Name.IsEmpty())
	{
		SYSEXPLR_OUTPUT(WSTR("Break at Code BP %<4>%08X\n"),pBP->Address);
	}
	else
	{
		WCHAR szBuffer[128];
		AnsiToUnicode(pBP->Name,szBuffer,128);
		SYSEXPLR_OUTPUT(WSTR("Break at %<F>%s\n"),szBuffer);
	}
}

void CDbgProcess::DisplayDataBP(BREAK_POINT*pBP)
{
	WCHAR szBuffer[128];
	AnsiToUnicode(pBP->Description,szBuffer,128);
	SYSEXPLR_OUTPUT(WSTR("Break at Data BP %<F>%08X %<7>%s\n"),pBP->Address,szBuffer);
}

bool CDbgProcess::ProcessHardwareBreak()
{
	BREAK_POINT*pBP;
	DWORD Mask;
	UINT Index;
	bool bret=false;
	if((SyserDR[7]&0xFF)==0)
		return false;
	if(Reg.DR[6]&0x1)
		Index = 0;
	else if(Reg.DR[6]&0x2)
		Index = 1;
	else if(Reg.DR[6]&0x4)
		Index = 2;
	else if(Reg.DR[6]&0x8)
		Index = 3;
	else
		return false;
	pBP = NULL;
	for(CDataBPList::IT Iter = gpSyser->m_SyserUI.m_DataBPList.Begin();Iter!=gpSyser->m_SyserUI.m_DataBPList.End();Iter++)
	{
		if(Iter->State == BP_STATE_ENABLE && Iter->CodeBackup==Index)
		{
			pBP = &(*Iter);
			if(gpSyser->m_SyserUI.m_SyserDI.TestCondition(pBP->Condition,pBP))
			{
				bret=true;
				gpSyser->m_bExit=false;
				gpSyser->m_SyserUI.m_SyserDI.RunCmdList(pBP->DoCmd);				
				if(pBP->DoCmd && gpSyser->m_bExit)
				{
					//这种情况是 runcmdlist 中有 x 或 exit 命令
					bret=false;
				}
				break;
			}
		}
	}
	if(pBP)
		DisplayDataBP(pBP);
	Mask = 0x3<<(16+Index*4);
	if((SyserDR[7]&Mask)==0)//如果是代码断点
	{
		Reg.EFlags |= 0x10000;//忽略指令断点
		gpSyser->m_bUpdateReg = true;		
	}
	return bret;
}

void CDbgProcess::ProcessSpecialCode(DWORD Address)
{
	ULSIZE CodeLen;
	BYTE CodeBuffer[16];
	CodeLen = ReadMemory(Address,CodeBuffer,sizeof(CodeBuffer));
	if(CodeLen==0)
		return;
	if(gPrevStepEIP==0)
		return;
	if(CodeBuffer[0]==0x9C)//还有中断命令的单步调试要做处理
	{	//如果前一个单步指令执行的是 pushfd 指令则要正确调整 TF 标志
		//
// 		__asm
// 		{
// 			push es
// 			push eax
// 			push ebx
// 			mov ax,Reg.SegReg[SS_IDX*2]
// 			mov es,ax
// 			mov eax,Reg.GeneReg[ESP_IDX*4]
// 			mov ebx,0xFFFFFEFF
// 			and es:[eax],ebx
// 			pop ebx
// 			pop eax
// 			pop es
// 		}
		SyserClearFlag(Reg.SegReg[SS_IDX],&Reg.GeneReg[ESP_IDX],0x100);
		gpSyser->m_bUpdateReg = true;
	}
}

CDbgModule* CDbgProcess::GetModule(PCWSTR ModuleName)
{
	CHAR szBuffer[MAX_FN_LEN];
	for(CDbgModuleMap::IT Iter=m_ModuleList.m_DbgModuleMap.Begin();Iter!=m_ModuleList.m_DbgModuleMap.End();Iter++)
	{
		UnicodeToAnsi(ModuleName,szBuffer,MAX_FN_LEN);
		if(TCmpModuleName((PCSTR)Iter->m_ModuleFullName,szBuffer))
			return &(*Iter);
	}
	return NULL;
}

CDbgModule* CDbgProcess::GetModule(PCSTR ModuleName)
{
	for(CDbgModuleMap::IT Iter=m_ModuleList.m_DbgModuleMap.Begin();Iter!=m_ModuleList.m_DbgModuleMap.End();Iter++)
	{
		if(TCmpModuleName((PCSTR)Iter->m_ModuleFullName ,ModuleName))
			return &(*Iter);
	}
	return NULL;
}

CDbgModule*	CDbgProcess::GetModule(ULPOS ModuleBase)
{
	return m_ModuleList.GetModule(ModuleBase);
}

CSymbolModule* CDbgProcess::GetSymbolModule(ULPOS ModuleBase)
{
	CDbgModule*pDbgModule = m_ModuleList.GetModule(ModuleBase);
	if(pDbgModule==NULL)
		return NULL;
	return pDbgModule->m_pSymbolModule;
}

CSymbolModule* CDbgProcess::GetSymbolModule(PCSTR ModuleName)
{
	CDbgModule*pDbgModule = m_ModuleList.GetModule(ModuleName);
	if(pDbgModule==NULL)
		return NULL;
	return pDbgModule->m_pSymbolModule;
}

void CDbgProcess::ExcuteDebugRegisterMontior(BYTE* InstructionBuffer)
{
	WCHAR *DRName[]={WSTR("DR0"),WSTR("DR1"),WSTR("DR2"),WSTR("DR3"),WSTR("DR4"),WSTR("DR5"),WSTR("DR6"),WSTR("DR7")};
	WCHAR *GRName[]={WSTR("EAX"),WSTR("ECX"),WSTR("EDX"),WSTR("EBX"),WSTR("ESP"),WSTR("EBP"),WSTR("ESI"),WSTR("EDI")};
	DWORD Dest,Src;
	bool bRet;
	DWORD DebugRegisterIndex,GeneralRegisterIndex;
	BYTE r;
	if(InstructionBuffer[0]!=0xf)
		return;
	r = InstructionBuffer[2];
	GeneralRegisterIndex=r&7;
	DebugRegisterIndex = (r>>3)&7;
	static dwDRMCount=0;
	dwDRMCount++;
	if((InstructionBuffer[1]==0x21)&&(r&0xc0))//读调式寄存器命令
	{
		Src=SyserDR[DebugRegisterIndex];
		if(DebugRegisterIndex==7)
		{
			Src|=0x400;
			Src&=0xffff27ff;
		}
		if(DebugRegisterIndex==6)
		{
			Src |= 0xffff0ff0;
			Src &= 0xffffefff;
		}
		switch(GeneralRegisterIndex) 
		{
		case 0:		Reg.GeneReg[EAX_IDX]=Src;break;
		case 1:		Reg.GeneReg[ECX_IDX]=Src;break;
		case 2:		Reg.GeneReg[EDX_IDX]=Src;break;
		case 3:		Reg.GeneReg[EBX_IDX]=Src;break;
		case 4:		Reg.GeneReg[ESP_IDX]=Src;break;
		case 5:		Reg.GeneReg[EBP_IDX]=Src;break;
		case 6:		Reg.GeneReg[ESI_IDX]=Src;break;
		case 7:		Reg.GeneReg[EDI_IDX]=Src;break;
		}	
		//gpSyser->DbgPrint(0,768-12*DebugRegisterIndex,WSTR("0x%08x mov %s,%s c[%d]"),Reg.EIP,GRName[GeneralRegisterIndex],DRName[DebugRegisterIndex],dwDRMCount);
		return;
	}
	else if((InstructionBuffer[1]==0x23)&&(r&0xc0))
	{
		;
		//gpSyser->DbgPrint(0,12*DebugRegisterIndex,WSTR("0x%08x mov %s,%s [%08x] c[%d]"),Reg.EIP,DRName[DebugRegisterIndex],GRName[GeneralRegisterIndex],Reg.GeneReg[GeneralRegisterIndex],dwDRMCount);
	}
}

int CDbgProcess::WriteProcessMemory(ULPOS Addr,void*Buffer,int Size)
{
	return SafeMemCopy(_RT_PBYTE(Addr),(BYTE*)Buffer,Size);
}

int CDbgProcess::ReadProcessMemory(ULPOS Addr,void*Buffer,int Size)
{
	return SafeMemCopy((BYTE*)Buffer,_RT_PBYTE(Addr),Size);
}

int	CDbgProcess::SafeReadProcessMemory(ULPOS addr,void* Buffer,int Size)
{
	int Len = SafeMemCopy((BYTE*)Buffer,_RT_PBYTE(addr),Size);
	return Len;
}

int	CDbgProcess::SafeWriteProcessMemory(ULPOS addr,void* Buffer,int Size)
{
	/*
	DWORD CR0 = GetCR0Reg();
	if(CR0&0x10000)
		SetCR0Reg(CR0&0xFFFEFFFF);
	*/
	int Len = SafeMemCopy(_RT_PBYTE(addr),(BYTE*)Buffer,Size);
	/*
	if(CR0&0x10000)
		SetCR0Reg(CR0);
	*/
	return Len;
}

void TouchModuleMemory(ULPOS ModuleBase,ULSIZE ModuleSize)
{
	BYTE TouchData;
	ULPOS Address,ModuleHighBase;
	ModuleHighBase = ModuleBase + ModuleSize;
	Address = ModuleBase;
	while(Address < ModuleHighBase)
	{
		__try
		{
			TouchData = _GET_BYTE(Address);
		}
		__except(EXCEPTION_EXECUTE_HANDLER)
		{
		}
		Address += MP_SIZE;
	}
}


int CDbgProcess::RecoverBreakPointRange()
{
	int Count=0;
	for(CCodeBPMap::IT Iter=m_pCodeBPMap->Begin();Iter.IsExist();Iter++)
	{
		if(Iter->State == BP_STATE_RECOV)
		{
			if(SwitchProcessSpace(Iter->PID))
			{
				if(RecoverCCBP(*Iter))
					Iter->State = BP_STATE_ENABLE;
				RestoreProcessSpace();
			}
			Count++;
		}
	}
	return Count;
}