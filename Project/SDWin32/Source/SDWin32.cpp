#include "StdAfx.h"
#include "SDWin32.h"


BOOL APIENTRY DllMain( HANDLE hModule, DWORD  ul_reason_for_call, LPVOID lpReserved)
{
    return TRUE;
}

CDebugger*CreateDebugger(void*UIObj)
{
	CSDWin32*pDebugger = new CSDWin32;
	return pDebugger;
}

void GetFileFilter(WCHAR*szFilte)
{
	TStrCpy(szFilte,WSTR("Executable Files|*.exe;*.dll;*.sys;*.scr|All Files|*.*|"));
}

void GetInfo(CHAR*szInfo)
{
	TStrCpy(szInfo,"Win32 User Mode Debugger");
#ifdef _DEBUG
	TStrCat(szInfo,"(DEBUG)");
#endif
}

CSDWin32::CSDWin32()
{
	m_CurProcHandle = GetCurrentProcess();
	m_bDebuging=false;
	m_bExit=false;
	m_hDebugProcess = NULL;
	m_pExecutePoint = &m_Context.Eip;
}

CSDWin32::~CSDWin32()
{
}

bool CSDWin32::Open(PCSTR ModuleName)
{
	DWORD DTID;
	if( gpFileIO->IsFileExist(ModuleName)==false &&
		TStrNICmp(ModuleName,"\\PID:",sizeof("\\PID:")-1))
		return false;
	if(CX86Debugger::Open(ModuleName)==false)
		return false;
	m_MainModuleName = ModuleName;
	m_hWaitEvent = CreateEvent(NULL,FALSE,FALSE,NULL);
	m_hDebugThread=::CreateThread(NULL,0,(DWORD(WINAPI*)(LPVOID))DebugThread,(LPVOID)this,0,&DTID);
	if(m_hDebugThread==NULL)
	{
		CloseHandle(m_hWaitEvent);
		CX86Debugger::Close();
		return false;
	}
	WaitForSingleObject(m_hWaitEvent,INFINITE);
	if(m_PID==0)
	{
		CloseHandle(m_hWaitEvent);
		CX86Debugger::Close();
		return false;
	}
	return true;
}

bool CSDWin32::Close()
{
	if(m_hDebugProcess==NULL)
		return CX86Debugger::Close();
	CloseHandle(m_hDebugProcess);
	m_hDebugProcess=OpenProcess(PROCESS_TERMINATE,FALSE,m_PID);
	if(TerminateProcess(m_hDebugProcess,0)==false)
		return false;
	CloseHandle(m_hDebugProcess);
	m_hDebugProcess = NULL;
	m_bExit=true;
	ContinueDebug();
	CloseHandle(m_hWaitEvent);
	return CX86Debugger::Close();
}

void CSDWin32::Release()
{
	CX86Debugger::Release();
	delete this;
}

bool CSDWin32::InsertThread(UINT ID,HANDLE Handle)
{
	CThreadMap::IT Iter = m_ThreadMap.InsertUnique(ID);
	if(Iter==m_ThreadMap.End())
		return false;
	if(DuplicateHandle(m_CurProcHandle,Handle,m_CurProcHandle,&Iter->hThread,THREAD_GET_CONTEXT | THREAD_SET_CONTEXT | THREAD_SUSPEND_RESUME|THREAD_QUERY_INFORMATION,FALSE,0)==FALSE)
		return false;
	return true;
}

bool CSDWin32::RemoveThread(UINT ID)
{
	return m_ThreadMap.Remove(ID)!=0;
}

void CSDWin32::DebugPlunge(UINT PlungeType)
{
	m_pDebugInterface->OnDebugPlungeMultiThread(PlungeType);
}

bool CSDWin32::GetThreadContext(UINT ID)
{
	HANDLE hThread;
	CThreadMap::IT Iter = m_ThreadMap.Find(ID);
	if(Iter==m_ThreadMap.End())
		return false;
	m_Context.ContextFlags=CONTEXT_ALL;
	hThread = Iter->hThread;
	if(::GetThreadContext(hThread,&m_Context)==FALSE)
		return false;
	return true;
}

bool CSDWin32::SetThreadContext(UINT ID)
{
	CThreadMap::IT Iter = m_ThreadMap.Find(ID);
	if(Iter==m_ThreadMap.End())
		return false;
	m_Context.ContextFlags=CONTEXT_FULL | CONTEXT_DEBUG_REGISTERS;
	return ::SetThreadContext(Iter->hThread,&m_Context)!=FALSE;
}

bool CSDWin32::SetThreadEIPBack(UINT ThreadID)
{
	if(GetThreadContext(ThreadID)==false)
		return false;
	m_Context.Eip--;
	if(SetThreadContext(ThreadID)==false)
		return false;
	return true;
}

ULSIZE CSDWin32::WriteMemory(ULPOS Address,void*Buffer,ULSIZE Size)
{
	DWORD RWSize;
	RWSize = 0;
	if(::WriteProcessMemory(m_hDebugProcess,NUM_TO_PTR(Address),Buffer,Size,&RWSize)==FALSE)
		return 0;
	return RWSize;
}

ULSIZE CSDWin32::ReadMemory(ULPOS Address,void*Buffer,ULSIZE Size)
{
	DWORD RWSize;
	RWSize = 0;
	if(::ReadProcessMemory(m_hDebugProcess,NUM_TO_PTR(Address),Buffer,Size,&RWSize)==FALSE)
		return 0;
	return RWSize;
}

bool CSDWin32::SetCodeBreakPoint(BREAK_POINT&BP)
{
	return SetCCBP(BP);
}

bool CSDWin32::ClearCodeBreakPoint(BREAK_POINT&BP)
{
	return ClearCCBP(BP);
}

bool CSDWin32::SetDataBreakPoint(BREAK_POINT&BP)
{
	return SetX86HDBP(BP,&m_Context.Dr0,&m_Context.Dr7);
}

bool CSDWin32::ClearDataBreakPoint(BREAK_POINT&BP)
{
	return ClearX86HDBP(BP,&m_Context.Dr0,&m_Context.Dr7);
}

bool CSDWin32::SetSingleStep()
{
	CONTEXT Context;
	for(CThreadMap::IT Iter=m_ThreadMap.Begin();Iter!=m_ThreadMap.End();Iter++)
	{
		Context.ContextFlags = CONTEXT_FULL;
		if(::GetThreadContext(Iter->hThread,&Context)==FALSE)
			continue;
		Context.EFlags|=0x100;
		Context.ContextFlags = CONTEXT_FULL;
		if(::SetThreadContext(Iter->hThread,&Context)==FALSE)
			continue;
	}
	return true;
}

bool CSDWin32::RemoveSingleStep()
{
	CONTEXT Context;
	for(CThreadMap::IT Iter=m_ThreadMap.Begin();Iter!=m_ThreadMap.End();Iter++)
	{
		Context.ContextFlags = CONTEXT_FULL;
		if(::GetThreadContext(Iter->hThread,&Context)==FALSE)
			continue;
		Context.EFlags&=0xFFFFFEFF;
		Context.ContextFlags = CONTEXT_FULL;
		if(::SetThreadContext(Iter->hThread,&Context)==FALSE)
			continue;
	}
	return true;
}

bool CSDWin32::UpdateRegister()
{
	return GetThreadContext(m_DebugThreadID);
}

bool CSDWin32::SaveRegister()
{
	return SetThreadContext(m_DebugThreadID);
}

bool CSDWin32::ContinueDebug(bool bRestoreScreen)
{
	return ::ResumeThread(m_hDebugThread)!=FALSE;
}

void CSDWin32::GetCPUX86RegPtr(X86_CPU_REG_PTR*pCPURegPtr,DWORD dwCPUID)
{
	GetX86RegPtr(pCPURegPtr);
}

void CSDWin32::GetX86RegPtr(X86_CPU_REG_PTR*pCPURegPtr)
{
	pCPURegPtr->pCS = (WORD*)&m_Context.SegCs;
	pCPURegPtr->pDS = (WORD*)&m_Context.SegDs;
	pCPURegPtr->pES = (WORD*)&m_Context.SegEs;
	pCPURegPtr->pFS = (WORD*)&m_Context.SegFs;
	pCPURegPtr->pGS = (WORD*)&m_Context.SegGs;
	pCPURegPtr->pSS = (WORD*)&m_Context.SegSs;
	pCPURegPtr->pEAX = (DWORD*)&m_Context.Eax;
	pCPURegPtr->pEBX = (DWORD*)&m_Context.Ebx;
	pCPURegPtr->pECX = (DWORD*)&m_Context.Ecx;
	pCPURegPtr->pEDX = (DWORD*)&m_Context.Edx;
	pCPURegPtr->pESI = (DWORD*)&m_Context.Esi;
	pCPURegPtr->pEDI = (DWORD*)&m_Context.Edi;
	pCPURegPtr->pEBP = (DWORD*)&m_Context.Ebp;
	pCPURegPtr->pESP = (DWORD*)&m_Context.Esp;
	pCPURegPtr->pEFL = (EFL_REG*)&m_Context.EFlags;
	pCPURegPtr->pEIP = (DWORD*)&m_Context.Eip;
	pCPURegPtr->pDR[0] = (DWORD*)&m_Context.Dr0;
	pCPURegPtr->pDR[1] = (DWORD*)&m_Context.Dr1;
	pCPURegPtr->pDR[2] = (DWORD*)&m_Context.Dr2;
	pCPURegPtr->pDR[3] = (DWORD*)&m_Context.Dr3;
	pCPURegPtr->pDR[4] = NULL;
	pCPURegPtr->pDR[5] = NULL;
	pCPURegPtr->pDR[6] = (DWORD*)&m_Context.Dr6;
	pCPURegPtr->pDR[7] = (DWORD*)&m_Context.Dr7;
	pCPURegPtr->pFPUControlWord = (WORD*)&m_Context.FloatSave.ControlWord;
	pCPURegPtr->pFPUStatusWord = (WORD*)&m_Context.FloatSave.StatusWord;
	pCPURegPtr->pFPUTagWord = (WORD*)&m_Context.FloatSave.TagWord;
	pCPURegPtr->pFPURegisterArea = (BYTE*)&m_Context.FloatSave.RegisterArea;
}

bool CSDWin32::GetSegRegBase(int SegIndex,DWORD*pAddress,DWORD* pSize)
{
	BOOL bret;
	LDT_ENTRY lpSelectorEntry;
	CThreadMap::IT FindIT;
	HANDLE hThread;
	FindIT = m_ThreadMap.Find(m_DebugThreadID);
	if(FindIT==m_ThreadMap.End())
		return false;
	hThread=(*FindIT).hThread;
	bret = GetThreadSelectorEntry(hThread,SegIndex,&lpSelectorEntry);
	if(bret)
	{
		if(pAddress)
		{
			*pAddress=lpSelectorEntry.HighWord.Bytes.BaseHi<<24;
			*pAddress|=lpSelectorEntry.HighWord.Bytes.BaseMid<<16;
			*pAddress|=lpSelectorEntry.BaseLow;
		}
		if(pSize)
		{
			*pSize=lpSelectorEntry.HighWord.Bits.LimitHi;
		}
	}
	return bret==TRUE;
}


bool CSDWin32::GetModulePEHead(ULPOS Base,PE_HEAD*pHead)
{
	DWORD Offset;
	ZeroMemory(pHead,sizeof(PE_HEAD));
	if(ReadMemory(Base+0x3C,&Offset,sizeof(Offset))!=sizeof(Offset))
		return false;
	if(ReadMemory(Base+Offset,pHead,sizeof(PE_HEAD))!=sizeof(PE_HEAD))
		return false;
	if(pHead->Signature!=0x4550)
		return false;
	return true;
}

DWORD CSDWin32::DebugThread(CSDWin32*pThis)
{
	char szBuffer[MAX_FN_LEN];
	WCHAR wszBuffer[MAX_FN_LEN];
	ULPOS Address;
	PROCESS_INFORMATION ProcInfo;
	STARTUPINFO StartupInfo;
	DEBUG_EVENT DebugEvent;
	PE_HEAD ModulePEHead;
	DWORD dwContinue=0;
	pThis->m_bExit=false;
	pThis->m_PID=0;
	if(TStrStr((PCSTR)pThis->m_MainModuleName,"\\PID:")==NULL)
	{
		STZeroMemory(StartupInfo);
		StartupInfo.cb=sizeof(StartupInfo);
		if(::CreateProcess(pThis->m_MainModuleName,NULL,NULL,NULL,TRUE,NORMAL_PRIORITY_CLASS | DEBUG_PROCESS,NULL,NULL,&StartupInfo,&ProcInfo)==FALSE)
		{
			SetEvent(pThis->m_hWaitEvent);
			return 0;
		}
		pThis->m_PID=ProcInfo.dwProcessId;
		pThis->m_hDebugProcess=ProcInfo.hProcess;
		pThis->m_bActiveProcess=false;
	}
	else
	{
		sscanf(pThis->m_MainModuleName,"\\PID:%08X",&pThis->m_PID);
		if(DebugActiveProcess(pThis->m_PID)==FALSE)
		{
			SetEvent(pThis->m_hWaitEvent);
			return 0;
		}
		pThis->m_hDebugProcess=OpenProcess(PROCESS_ALL_ACCESS,FALSE,pThis->m_PID);
		if(pThis->m_hDebugProcess==NULL)
		{
			pThis->m_PID=0;
			SetEvent(pThis->m_hWaitEvent);
			return 0;
		}
		pThis->m_bActiveProcess=true;
	}
	pThis->m_ProcName = TGetFileName((PCSTR)pThis->m_MainModuleName);
	pThis->m_bDebuging=false;
	STZeroMemory(pThis->m_Context);
	while(pThis->m_bExit==false && WaitForDebugEvent(&DebugEvent,INFINITE))
	{
		dwContinue = DBG_CONTINUE;
		switch(DebugEvent.dwDebugEventCode)
		{
		case EXCEPTION_DEBUG_EVENT:
			dwContinue=pThis->HandleException(&DebugEvent);
			break;
		case CREATE_THREAD_DEBUG_EVENT:
			pThis->InsertThread(DebugEvent.dwThreadId,DebugEvent.u.CreateThread.hThread);
			break;
		case CREATE_PROCESS_DEBUG_EVENT:
			pThis->m_BPCount = 0;
			pThis->InsertThread(DebugEvent.dwThreadId,DebugEvent.u.CreateProcessInfo.hThread);
			if(pThis->m_bActiveProcess==false)
				pThis->InsertCodeBP(PTR_TO_NUM(DebugEvent.u.CreateProcessInfo.lpStartAddress),BP_TYPE_DEBUG,BP_STATE_ENABLE);
			Address = PTR_TO_NUM(DebugEvent.u.CreateProcessInfo.lpBaseOfImage);
			pThis->GetModulePEHead(Address,&ModulePEHead);
			pThis->m_pDebugInterface->OnLoadModule(pThis,pThis->m_MainModuleName,Address,ModulePEHead.SizeOfImage,MAKE_MODULE_ID(ModulePEHead.CheckSum,ModulePEHead.TimeDateStamp));
			break;
		case EXIT_THREAD_DEBUG_EVENT:
			pThis->RemoveThread(DebugEvent.dwThreadId);
			break;
		case EXIT_PROCESS_DEBUG_EVENT:
			pThis->RemoveAllCodeBP();
			sprintf(szBuffer,"Debug Event : Process Terminated , Exit Code = %d (0x%X) !\n",DebugEvent.u.ExitProcess.dwExitCode,DebugEvent.u.ExitProcess.dwExitCode);
			pThis->m_pDebugInterface->DisplayMsg(szBuffer);
			pThis->m_pDebugInterface->OnDebugTerminateMultiThread(true);
			pThis->m_bExit = true;
			break;
		case LOAD_DLL_DEBUG_EVENT:
			if(DebugEvent.u.LoadDll.lpImageName)
			{
				Address=0;
				*szBuffer=0;
				pThis->ReadMemory(PTR_TO_NUM(DebugEvent.u.LoadDll.lpImageName),&Address,sizeof(Address));
				if(Address)
				{
					if(DebugEvent.u.LoadDll.fUnicode)
					{
						*wszBuffer=0;
						pThis->ReadMemory(Address,wszBuffer,MAX_FN_LEN*2);
						//UnicodeToAnsi((const wchar_t *)wszBuffer,szBuffer,MAX_FN_LEN);
						WideCharToMultiByte(CP_ACP,0,wszBuffer,-1,szBuffer,MAX_FN_LEN,NULL,NULL);
					}
					else
					{
						pThis->ReadMemory(Address,szBuffer,MAX_FN_LEN);
					}
				}
				if(TGetFileName(szBuffer)==szBuffer)
				{
					char szSystemDir[MAX_FN_LEN];
					GetSystemDirectory(szSystemDir,MAX_FN_LEN);
					TStrCat(szSystemDir,"\\");
					TStrCat(szSystemDir,szBuffer);
					TStrCpy(szBuffer,szSystemDir);
				}
				Address = PTR_TO_NUM(DebugEvent.u.LoadDll.lpBaseOfDll);
				pThis->GetModulePEHead(Address,&ModulePEHead);
				if(Address && *szBuffer)
					pThis->m_pDebugInterface->OnLoadModule(pThis,szBuffer,Address,ModulePEHead.SizeOfImage,MAKE_MODULE_ID(ModulePEHead.CheckSum,ModulePEHead.TimeDateStamp));
			}
			break;
		case UNLOAD_DLL_DEBUG_EVENT:
			break;
		case OUTPUT_DEBUG_STRING_EVENT:
			break;
		case RIP_EVENT:
			break;
		default:
			break;
		}
		ContinueDebugEvent(DebugEvent.dwProcessId,DebugEvent.dwThreadId,dwContinue);
	}
	pThis->m_hDebugProcess=NULL;
	SetEvent(pThis->m_hWaitEvent);
	return 1;
}

//异常处理
DWORD CSDWin32::HandleException(DEBUG_EVENT*pDebugEnent)
{
	PE_HEAD ModulePEHead;
	char szBuffer[256];
	bool bActive;
	BREAK_POINT*pBP;
	DWORD dwContinue;
	switch(pDebugEnent->u.Exception.ExceptionRecord.ExceptionCode)
	{
	case EXCEPTION_ACCESS_VIOLATION://非法处理
		dwContinue = DBG_CONTINUE;
		m_DebugThreadID=pDebugEnent->dwThreadId;
		GetThreadContext(pDebugEnent->dwThreadId);
		m_ExpAddr=PTR_TO_NUM(pDebugEnent->u.Exception.ExceptionRecord.ExceptionAddress);
		sprintf(szBuffer,"Debug Event : Access Violation , Address = %08X !\n",m_ExpAddr);
		m_pDebugInterface->DisplayMsg(szBuffer);
		DebugPlunge(DEBUG_PLUNGE_EXCEPTION);
		m_bDebuging=true;
		SuspendThread(m_hDebugThread);
		GetThreadContext(pDebugEnent->dwThreadId);
		m_bDebuging=false;
		break;
	case EXCEPTION_BREAKPOINT://断点
		dwContinue = DBG_CONTINUE;
		m_BPCount++;
		if(m_BPCount==1)
		{
			if(m_bActiveProcess)
			{
				m_DebugThreadID=pDebugEnent->dwThreadId;
				GetThreadContext(m_DebugThreadID);
				DebugPlunge(DEBUG_PLUNGE_OTHER);
				m_bDebuging=true;
				SetEvent(m_hWaitEvent);
				SuspendThread(m_hDebugThread);
				m_bDebuging=false;

				HANDLE  hModuleSnap;
				MODULEENTRY32 me32;
				hModuleSnap = CreateToolhelp32Snapshot(TH32CS_SNAPMODULE,m_PID);
				if(hModuleSnap == INVALID_HANDLE_VALUE)
					return false;
				me32.dwSize = sizeof(MODULEENTRY32);
				if(Module32First(hModuleSnap,&me32))
				{
					do
					{
						GetModulePEHead(PTR_TO_NUM(me32.modBaseAddr),&ModulePEHead);
						m_pDebugInterface->OnLoadModule(this,me32.szExePath,PTR_TO_NUM(me32.modBaseAddr),me32.modBaseSize,MAKE_MODULE_ID(ModulePEHead.CheckSum,ModulePEHead.TimeDateStamp));
					}
					while(Module32Next(hModuleSnap,&me32)); 
				}
				CloseHandle(hModuleSnap);
			}
		}
		else
		{
			m_DebugThreadID=pDebugEnent->dwThreadId;
			pBP = GetCodeBP(PTR_TO_NUM(pDebugEnent->u.Exception.ExceptionRecord.ExceptionAddress));
			if(pBP && pBP->State==BP_STATE_ENABLE)
			{
				SetThreadEIPBack(pDebugEnent->dwThreadId);
				if(WriteMemory(m_Context.Eip,&pBP->CodeBackup,1))
					pBP->State = BP_STATE_RECOV;
				if(m_pDebugInterface->TestCondition(pBP->Condition))
				{
					m_pDebugInterface->RunCmdList(pBP->DoCmd);
					if((pBP->Type & BP_TYPE_DEBUG)==0)
					{
						m_pDebugInterface->ResetTrace();
						bActive = true;
					}
					if(m_pDebugInterface->IsHandledTraceEvent())
					{
						RemoveAllCodeBP(BP_TYPE_DEBUG);
						DebugPlunge(DEBUG_PLUNGE_BREAK_POINT);
						m_bDebuging=true;
						if(m_BPCount==2)
							SetEvent(m_hWaitEvent);
						SuspendThread(m_hDebugThread);
						m_bDebuging=false;
					}
				}
				if(IsRecoverBPExist())
					SetSingleStep();
			}
		}
		break;
	case EXCEPTION_SINGLE_STEP://单步
		dwContinue = DBG_CONTINUE;
		m_DebugThreadID=pDebugEnent->dwThreadId;
		GetThreadContext(pDebugEnent->dwThreadId);
		RecoverBreakPoint();
		bActive = false;
		pBP = GetCodeBP(m_Context.Eip);
		if(pBP && pBP->State==BP_STATE_ENABLE)
		{
			if(WriteMemory(m_Context.Eip,&pBP->CodeBackup,1))
				pBP->State = BP_STATE_RECOV;
			if(m_pDebugInterface->TestCondition(pBP->Condition))
			{
				m_pDebugInterface->RunCmdList(pBP->DoCmd);
				if((pBP->Type & BP_TYPE_DEBUG)==0)
				{
					m_pDebugInterface->ResetTrace();
					bActive = true;
				}
			}
		}
		if(m_pDebugInterface->m_TraceType!=TRACE_NULL && m_pDebugInterface->IsHandledTraceEvent())
			bActive = true;
		else
		{
			if(GetDataBPList()>0)
				bActive = true;
		}
		if(bActive)
		{
			RemoveAllCodeBP(BP_TYPE_DEBUG,BP_TYPE_EXC_NON);
			DebugPlunge(DEBUG_PLUNGE_BREAK_POINT);
			m_bDebuging=true;
			SuspendThread(m_hDebugThread);
			m_bDebuging=false;
		}
		if(IsRecoverBPExist())
			SetSingleStep();
		break;
	case DBG_CONTROL_C:
	case DBG_CONTROL_BREAK:
		dwContinue = DBG_CONTINUE;
		m_DebugThreadID=pDebugEnent->dwThreadId;
		GetThreadContext(pDebugEnent->dwThreadId);
		DebugPlunge(DEBUG_PLUNGE_USER_BREAK);
		m_bDebuging=true;
		SuspendThread(m_hDebugThread);
		m_bDebuging=false;
		break;
	default:
		dwContinue = DBG_EXCEPTION_NOT_HANDLED;
		m_DebugThreadID=pDebugEnent->dwThreadId;
		GetThreadContext(pDebugEnent->dwThreadId);
		DebugPlunge(DEBUG_PLUNGE_OTHER);
		m_bDebuging=true;
		SuspendThread(m_hDebugThread);
		GetThreadContext(pDebugEnent->dwThreadId);
		m_bDebuging=false;
		break;
	}
	return dwContinue;
}
