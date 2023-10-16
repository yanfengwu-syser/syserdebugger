#ifndef _SYSER_CONSOLE_WND_H_
#define _SYSER_CONSOLE_WND_H_

enum CON_DATA_TYPE
{
	CDT_VADDR,
	CDT_PADDR,
	CDT_STRING,
	CDT_SYMBOL,
	CDT_HEX_NUM,
	CDT_DEC_NUM,
	MAX_COLOR_COUNT
};


class CConsoleWnd : public CWispConsoleWnd
{
public:
	CConsoleWnd();
	bool	m_IsInBatProcess;
	BYTE	m_CDTColor[MAX_COLOR_COUNT];
	int		m_Radix;
public:
	DECLARE_WISP_MSG_MAP
	DECLARE_WISP_MSG(OnCreate)
	DECLARE_WISP_MSG(OnKeyEvent)
	void	BatBeginNodify(WISP_PCSTR szCmd);
	void	BatEndNodify(WISP_PCSTR szCmd);
	void	AfterRunCmdNotify(const CMD_CHAR*szCmd);
public:
	CConsoleWnd& operator <<(BYTE Num8);
	CConsoleWnd& operator <<(WORD Num16);
	CConsoleWnd& operator <<(DWORD Num32);
	CConsoleWnd& operator <<(QWORD Num64);
	CConsoleWnd& operator <<(CON_DATA_TYPE Type);
	CConsoleWnd& operator <<(const WCHAR*String);
};


class CTerminalWnd : public CWispTerminalWnd
{
public:
	DECLARE_WISP_MSG_MAP
	DECLARE_WISP_MSG(OnKeyEvent)
};

#endif


