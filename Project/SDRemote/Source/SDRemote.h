#ifndef _SDREMOTE_H_
#define _SDREMOTE_H_


class CSDRemote : public CX86Debugger,public CPageImage
{
public:
	CSDRemote();
	~CSDRemote();
public:
	CPageMemory	m_ProcessCache;
	bool	LoadPage(IN ULPOS Address,OUT void* Buffer);
	bool	SavePage(IN ULPOS Address,OUT void* Buffer);
	DWORD	GetPageAttribute(IN ULPOS Address);
	bool	Open(PCSTR ModuleName);
	bool	Close();
	void	Release();
	ULSIZE	WriteMemory(ULPOS Address,void*Buffer,ULSIZE Size);
	ULSIZE	ReadMemory(ULPOS Address,void*Buffer,ULSIZE Size);
	bool	SetSingleStep();
	bool	SetRecoverStep();
	bool	RemoveSingleStep();
	bool	UpdateRegister();
	bool	SaveRegister();
	bool	ContinueDebug();
	void	GetX86RegPtr(X86_CPU_REG_PTR*pCPURegPtr);
	void	GetCPUX86RegPtr(X86_CPU_REG_PTR*pCPURegPtr,DWORD dwCPUID);
	bool	GetSegRegBase(int SegIndex,DWORD*pAddress,DWORD* pSize);
	X86_CPU_REG	m_Context;
	HANDLE	m_hPipe;
private:
	bool	ReadProcessMemory(ULPOS Address,void*Buffer,ULSIZE Size);
	bool	WriteProcessMemory(ULPOS Address,void*Buffer,ULSIZE Size);
};


#endif
