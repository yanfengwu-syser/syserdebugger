#ifndef _INSTR_SYM_H_
#define _INSTR_SYM_H_

#include "IntelDis.h"
#include "PEFile.h"

#define MAX_INSTR_LEN			0x10
#define MAX_LINES_PER_PAGE		0x80
#define MAX_STR_PER_LINE		0x40

//反汇编风格
#define DS_USE_SYM				0x00000001
#define DS_JMP_API				0x00000002
#define	MAX_LINE_BYTES			0x10




class CInstrSym : public CIntelDisassembler
{
public:
	BYTE	m_CodeBuffer[MAX_INSTR_LEN];
	bool	m_bUseSym;
	ULPOS	m_ImageBase;
	ULPOS	m_ImageHighBase;
	UINT	m_UxAlign;
	UINT	m_Style;
public:
	virtual bool	AddrToSym(ULPOS Address,PSTR szSym,int BufSize);
	virtual ULSIZE	ReadMemory(ULPOS Address,void*Buffer,ULSIZE Size);
	virtual	bool	GetInstrRefPoint(ULPOS*pAddress){return false;}
public:
	CInstrSym();
	virtual ~CInstrSym();
public:
	void	SetDasmStyle(UINT Style){m_Style = Style;}
	ULPOS	GetDasmStyle(){return m_Style;}
	void	HandleAddressOp(OPERAND_ITEM*pOp,WCHAR* szInfo,INSTRUCTION_INFORMATION*pInstrInfo);
	
public://正反汇编

	ULSIZE	Dasm(IN OUT INSTRUCTION_INFORMATION*pDasmInstr,DIS_CPU*pDisCPU = NULL,ULSIZE MaxSize = MAX_INSTR_LEN);
	ULSIZE	Asm(PSTR InstString,PBYTE OutPutCode,ULPOS EIP);
public://指令
	ULSIZE	PrevInstrLen(ULPOS Address);
	ULSIZE	InstrCount(BYTE*CodeBuffer,ULSIZE CodeSize,BYTE*LenAry);
	bool	IsProcessCode(ULPOS Address);
	bool	IsCallInstruction(ULPOS Address,PSTR szFunc=NULL);
	int		IsPrevCodeCallInstr(ULPOS Address,PSTR szFunc,ULPOS*pDesAddr);
	ULSIZE	InstrLen(ULPOS Address,ULSIZE MaxSize = MAX_INSTR_LEN);
	bool	GetInstrDesAddress(ULPOS Address,ULPOS*pDesAddr);
	bool	GetTransferAddress(ULPOS Address,ULPOS*pDesAddr);
	int		GetInstrImmediateAndDesAddress(ULPOS Address,ULPOS*pDesAddr,ULPOS* pImmediate);//主要是用在 code view 中的 enter 键盘跳转用
	bool	GetVariableDesAddress(ULPOS Address,ULPOS*pDesAddr);
	static	bool	GetNearJmpDes(BYTE*CodeBuffer,ULPOS EIP=0,ULPOS*pDes=NULL);
	static	bool	IsActiveNearJmp(BYTE*CodeBuffer,DWORD Eflags);
	static	ULSIZE	InstrLen(BYTE*Buffer,ULSIZE BufSize = MAX_INSTR_LEN);
	static	ULSIZE	InstrLen16(BYTE*Buffer,ULSIZE BufSize = MAX_INSTR_LEN);
	static	PCWSTR	m_RegStr[3][16];
	static	PCWSTR	m_ScaleStr[4];
	static	PCWSTR	m_SizePtr[9];
	static	PCWSTR	m_SizeSym[11];
	static	PCWSTR	m_SegStr[6];
	static	PCWSTR	m_LengthStr[5];
	static	PCWSTR	m_DefaultOPSize[2];
	static	PCSTR	m_TransDesInst[];
	static	PCWSTR	m_UnReaded;
};

#endif

