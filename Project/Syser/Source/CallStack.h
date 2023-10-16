#ifndef _CALL_STACK_H_
#define _CALL_STACK_H_

struct FRAME_ENTRY
{
	ULPOS	PrevFrame;
	ULPOS	CallReturn;
};

struct CALL_FRAME
{
	ULPOS	FrameAddress;
	ULPOS	CallReturn;
	ULPOS	FuncAddr;
	CStrA	FuncName;
};

#define MAX_CALL_STACK_COUNT	0x100

class CCallStack
{
public:
	CCallStack();
	TList<CALL_FRAME>	m_CallFrameList;
	CALL_FRAME*			m_pCurCallFrame;
	ULPOS	m_PrevEBP;
	void	UpdateContext(ULPOS EBP=0);
	void	UpdateContext1(ULPOS EBP=0);
};

#endif //_CALL_STACK_WND_