#ifndef _SDWIN32_H_
#define _SDWIN32_H_

struct THREAD_DBG_INFO
{
	UINT	ThreadID;
	HANDLE	hThread;
};

typedef TMap<DWORD,THREAD_DBG_INFO>	CThreadMap;

class CSDWin32 : public CX86Debugger
{
public:
	CSDWin32();
	~CSDWin32();
public:
	bool	Open(PCSTR ModuleName);
	bool	Close();
	void	Release();
	ULSIZE	WriteMemory(ULPOS Address,void*Buffer,ULSIZE Size);
	ULSIZE	ReadMemory(ULPOS Address,void*Buffer,ULSIZE Size);
	bool	SetCodeBreakPoint(BREAK_POINT&BP);
	bool	ClearCodeBreakPoint(BREAK_POINT&BP);
	bool	SetDataBreakPoint(BREAK_POINT&BP);
	bool	ClearDataBreakPoint(BREAK_POINT&BP);
	bool	SetSingleStep();
	bool	RemoveSingleStep();
	bool	UpdateRegister();
	bool	SaveRegister();
	bool	ContinueDebug(bool bRestoreScreen = true);
	static	DWORD DebugThread(CSDWin32*pThis);
	DWORD	HandleException(DEBUG_EVENT*pDebugEnent);
	void	GetX86RegPtr(X86_CPU_REG_PTR*pCPURegPtr);
	void	GetCPUX86RegPtr(X86_CPU_REG_PTR*pCPURegPtr,DWORD dwCPUID);
	bool	GetSegRegBase(int SegIndex,DWORD*pAddress,DWORD* pSize);
public:
	CStrA	m_MainModuleName;
	CThreadMap	m_ThreadMap;
	UINT	m_DebugThreadID;
	UINT	m_DebugProcessID;
	HANDLE	m_hDebugThread;
	HANDLE	m_hDebugProcess;
	HANDLE	m_CurProcHandle;
	CONTEXT m_Context;
	ULPOS	m_ExpAddr;
	HANDLE	m_hWaitEvent;
private:
	bool	GetModulePEHead(ULPOS Base,PE_HEAD*pHead);
	bool	SetThreadEIPBack(UINT ThreadID);
	bool	GetThreadContext(UINT ID);
	bool	SetThreadContext(UINT ID);
	bool	InsertThread(UINT ID,HANDLE Handle);
	bool	RemoveThread(UINT ID);
	void	DebugPlunge(UINT PlungeType);
	bool	m_bDebuging;
	bool	m_bExit;
	bool	m_bActiveProcess;
	int		m_BPCount;
};


#endif
