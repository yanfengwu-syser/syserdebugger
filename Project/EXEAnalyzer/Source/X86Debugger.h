#ifndef _X86_DEBUGGER_H_
#define _X86_DEBUGGER_H_

#include "Debugger.h"

struct EFL_REG
{//标志寄存器位段定义
	int	CF:1;		//0
	int	b1:1;		//1
	int	PF:1;		//2
	int	b3:1;		//3
	int	AF:1;		//4
	int	b5:1;		//5
	int	ZF:1;		//6
	int	SF:1;		//7
	int	TF:1;		//8
	int	IF:1;		//9
	int	DF:1;		//10
	int	OF:1;		//11
	int	IOPL:2;	//12--13
	int	NT:1;		//14
	int	bf:1;		//15
	int	RF:1;		//16
	int	VM:1;		//17
	int	AC:1;		//18
	int	VIF:1;		//19
	int	VIP:1;		//20
	int	ID:1;		//21
	int	_22_23:2;	//22--23
	int	_24_31:8;	//24--31
};

struct X86_CPU_REG_PTR
{
	DWORD*pEAX;
	DWORD*pEBX;
	DWORD*pECX;
	DWORD*pEDX;
	DWORD*pEDI;
	DWORD*pESI;
	DWORD*pEBP;
	DWORD*pESP;
	DWORD*pEIP;
	EFL_REG*pEFL;
	WORD*pCS;
	WORD*pDS;
	WORD*pES;
	WORD*pFS;
	WORD*pGS;
	WORD*pSS;
	DWORD*pDR[8];
	DWORD*pGDTRBase;
	WORD*pGDTRLimit;
	DWORD*pIDTRBase;
	WORD*pIDTRLimit;
	WORD*pLDTR;
	WORD*pTR;
	DWORD* pCR2;
	WORD* pFPUControlWord;
	WORD* pFPUStatusWord;
	WORD* pFPUTagWord;
	BYTE* pFPURegisterArea;
};

struct X86_CPU_REG
{
	DWORD EAX;
	DWORD EBX;
	DWORD ECX;
	DWORD EDX;
	DWORD EDI;
	DWORD ESI;
	DWORD EBP;
	DWORD ESP;
	DWORD EIP;
	DWORD EFL;
	WORD CS;
	WORD DS;
	WORD ES;
	WORD FS;
	WORD GS;
	WORD SS;
	DWORD DR[8];
};

enum
{
	CODE_MODE_16 = 0,
	CODE_MODE_32,
};

class CX86Debugger : public CDebugger
{
public:
	CX86Debugger();
	virtual ~CX86Debugger();
	UINT	m_CodeMode;
public:
	virtual void	GetX86RegPtr(X86_CPU_REG_PTR*pCPURegPtr);						//从外部取得寄存器指针
	virtual void	GetCPUX86RegPtr(X86_CPU_REG_PTR*pCPURegPtr,DWORD dwCPUID);
	virtual bool	GetSegRegBase(int SegIndex,DWORD*pAddress,DWORD* pSize=NULL);	//取段基址	
	virtual bool	SetCCBP(BREAK_POINT&BP);
	virtual bool	ClearCCBP(BREAK_POINT&BP);
	virtual	bool	RecoverCCBP(BREAK_POINT&BP);
	virtual	bool	SetX86HDBP(BREAK_POINT&BP,DWORD*pDR,DWORD*pDR7);
	virtual	bool	ClearX86HDBP(BREAK_POINT&BP,DWORD*pDR,DWORD*pDR7);
	virtual	BREAK_POINT*IsHanldeHDBP(DWORD DR6);
	virtual	bool	IsRecoverBPExist();
	virtual int		RecoverBreakPoint();
	
};

#endif


