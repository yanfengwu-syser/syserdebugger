#ifndef _DBG_PROCESS_H_
#define _DBG_PROCESS_H_

enum
{
	BP_DELAY_CODE,
	BP_DELAY_HARDWARE_INSTRUCTION,
	BP_DELAY_HARDWARE_MONITOR,
	BP_DELAY_PUSHFD,
};

class CDbgProcess : public CX86Debugger
{
public:
	CDbgProcess();
	virtual ~CDbgProcess();
public:
	void	InitProcess(DWORD PID);
	void	Release();
	///////////////////////////////////////////////////////////////////////////////////////////////////////////////
	//断点
	bool	SetCodeBreakPoint(BREAK_POINT&BP);
	bool	ClearCodeBreakPoint(BREAK_POINT&BP);
	bool	SetDataBreakPoint(BREAK_POINT&BP);
	bool	ClearDataBreakPoint(BREAK_POINT&BP);
	bool	MapToPhysAddr(ULPOS Address,ULONGLONG&PhysAddr);
	bool	SwitchProcessSpace(UINT PID);
	void	RestoreProcessSpace();
	///////////////////////////////////////////////////////////////////////////////////////////////////////////////
	void	PatchSystem(PCSTR Name,ULPOS Address,PVFV PatchFunc);
	bool	SetSingleStep();
	bool	RemoveSingleStep();
	void	GetX86RegPtr(X86_CPU_REG_PTR*pCPURegPtr);
	void	GetCPUX86RegPtr(X86_CPU_REG_PTR*pCPURegPtr,DWORD dwCPUID);
	bool	GetSegRegBase(int SegIndex,DWORD*pAddress,DWORD*pSize=NULL);
	bool	SaveRegister();
	bool	UpdateRegister();
	bool	UpdateDRXRegister();			//更新硬件调试寄存器	
	bool	ContinueDebug(bool bRestoreScreen = true);
	ULSIZE	ReadMemory(ULPOS Address,void*Buffer,ULSIZE Size);
	ULSIZE	WriteMemory(ULPOS Address,void*Buffer,ULSIZE Size);
	ULSIZE	MoveMem(ULPOS DesAddr,ULPOS SrcAddr,ULSIZE Size);
/////////////////////////////////////////////////////////////////////////////////////////////
	int		WriteProcessMemory(ULPOS Addr,void*Buffer,int Size);
	int		ReadProcessMemory(ULPOS Addr,void*Buffer,int Size);
	int		SafeReadProcessMemory(ULPOS addr,void* Buffer,int Size);
	int		SafeWriteProcessMemory(ULPOS addr,void* Buffer,int Size);
/////////////////////////////////////////////////////////////////////////////////////////////
	CDbgProcess*m_pOrgDbgProc;
	DWORD		m_CR3;				//CR3
	CStrW		m_ProcNameW;		//进程名
#ifdef CODE_OS_NT_DRV
	PEB*		m_pCurrentPEB;
	PEPROCESS	m_PEProcess;
	PEPROCESS	GetEPROCESS()const {return m_PEProcess;}
#endif
	bool	m_bPrevPatchBP;
public:
	bool	HandleInt3(ULPOS Address);
	bool	HandleInt1(ULPOS Address);
	void	DisplayCodeBP(BREAK_POINT*pBP);
	void	DisplayDataBP(BREAK_POINT*pBP);
	bool	ProcessHardwareBreak();
	void	ExcuteDebugRegisterMontior(BYTE* InstructionBuffer);
public:
	CDbgModule*	GetModule(PCWSTR ModuleName);
	CDbgModule* GetModule(PCSTR ModuleName);
	CDbgModule*	GetModule(ULPOS ModuleBase);
	CSymbolModule*GetSymbolModule(ULPOS ModuleBase);
	CSymbolModule*GetSymbolModule(PCSTR ModuleName);
	bool	RemoveSymbolModule(DWORD ModuleBase);
	void	ProcessSpecialCode(DWORD Address);
	int		RecoverBreakPointRange();
	
};

void TouchModuleMemory(ULPOS ModuleBase,ULSIZE ModuleSize);

#endif


