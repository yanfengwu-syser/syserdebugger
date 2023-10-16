#ifndef _WISP_CONSOLE_WND_H_
#define _WISP_CONSOLE_WND_H_

#include "WispColorStrWnd.h"

#define WISP_SSTREAM_UNIX		0x00000000
#define WISP_SSTREAM_DOS		0x00000001
#define WISP_SSTREAM_DISPLAY	0x00000002

#define CONSOLE_TERMINAL(pConWnd)		if(pConWnd->m_pTerminalWnd) \
											pConWnd = (CWispConsoleWnd*) pConWnd->m_pTerminalWnd;

struct WISP_CMD_ENTRY
{
	WISP_CHAR*	CmdStr;
	WISP_CHAR*	CmdCmt;
	void*		CmdProc;
};

class CWispConsoleWnd;
class CWispTerminalWnd : public CWispColorStrWnd
{
public:
	CWispTerminalWnd();
	virtual ~CWispTerminalWnd();
public:
	bool	SaveHistroys(PCSTR FileName);
	void	SetHistoryLines(IN int nLine);
	void	ClearScreen();
	void	Output(IN const WISP_CHAR*szLine);
	void	Output(IN const WISP_COLOR_CHAR*szLine);
	void	Output(WISP_CHAR ch);
	int		VPrintf(const WISP_CHAR*format,void*ParamList);
	void	Printf(IN const WISP_CHAR*szLine,...);
	void	AttachConsole(CWispConsoleWnd*pConsoleWnd);
	void	SetFontColor(BYTE ColorIndex);
	void	SaveFontColor();
	void	RestoreFontColor();
	void	EnsureInputVisible();
	void	EnsureInputCaretVisible();
	bool	RunModulePathBat(PCSTR FileName,PCSTR szCmdArg,int*pResult=NULL);
	bool	TermRunCmd(const CMD_CHAR*szCmd,int*pResult = NULL);
	virtual bool RunCmdNotify(const CMD_CHAR*szCmd){return true;}
	virtual void AfterRunCmdNotify(const CMD_CHAR*szCmd){};
public:
	DECLARE_WISP_MSG_MAP
	DECLARE_WISP_MSG(OnChar);
	DECLARE_WISP_MSG(OnCreate);
	DECLARE_WISP_MSG(OnKeyEvent);
	DECLARE_WISP_MSG(OnDestroy);
	DECLARE_WISP_MSG_CMD_MAP;
	DECLARE_WISP_MSG_CMD(OnCmdGetCmd);
	DECLARE_WISP_MSG_EVENT_MAP
	DECLARE_WISP_MSG(OnEventPaste);
public:
	virtual BYTE GetLineStr(IN int LineIndex,OUT WISP_COLOR_CHAR*pColorStr);
public:
	CWispConsoleWnd*m_pConsoleWnd;
	TQueue<CWispColorString,64>m_LineList;
	TStack<CWispString,64>m_CmdHistroy;
	CWispString	m_CmdStr;
	CWispString	m_InputStr;
	CWispString	m_Prefix;
	CWispString	m_OutPutStr;
	UINT		m_StreamStyle;
	int			m_CurHisIndex;
	BYTE		m_TextColor;
	BYTE		m_OldTextColor;
	bool		m_bNewLine;
	int			m_MaxCharLine;
	ALTFileStream*m_pStream;
};


class CWispConsoleWnd : public CWispTerminalWnd,public CCmdParser
{
public:
	CWispConsoleWnd();
	static	int Cls(int argc, WISP_CHAR *argv[ ],WISP_PCSTR szCommandLine, CWispConsoleWnd*pConWnd);
	static	int WispVer(int argc, WISP_CHAR *argv[ ],WISP_PCSTR szCommandLine, CWispConsoleWnd*pConWnd);
	static	int HL(int argc, WISP_CHAR *argv[ ],WISP_PCSTR szCommandLine, CWispConsoleWnd*pConWnd);
	static	int	HCC(int argc, WISP_CHAR *argv[ ],WISP_PCSTR szCommandLine, CWispConsoleWnd*pConWnd);
	static	int	HC(int argc, WISP_CHAR *argv[ ],WISP_PCSTR szCommandLine, CWispConsoleWnd*pConWnd);
	static	int Color(int argc, WISP_CHAR *argv[ ],WISP_PCSTR szCommandLine, CWispConsoleWnd*pConWnd);
	static	int BKColor(int argc, WISP_CHAR *argv[ ],WISP_PCSTR szCommandLine, CWispConsoleWnd*pConWnd);
	static	int Help(int argc, WISP_CHAR *argv[ ],WISP_PCSTR szCommandLine, CWispConsoleWnd*pConWnd);
	static	int	Bat(int argc, WISP_CHAR *argv[ ],WISP_PCSTR szCommandLine, CWispConsoleWnd*pConWnd);
	static	int	Set(int argc, WISP_CHAR *argv[ ],WISP_PCSTR szCommandLine, CWispConsoleWnd*pConWnd);
	static	int	DoNothing(int argc, WISP_CHAR *argv[ ],WISP_PCSTR szCommandLine, CWispConsoleWnd*pConWnd);
	static	int	Print(int argc, WISP_CHAR *argv[ ],WISP_PCSTR szCommandLine, CWispConsoleWnd*pConWnd);
	void	DisplayColor();
public:
	COptionValue	m_Option;
	CWispTerminalWnd*m_pTerminalWnd;
	DECLARE_WISP_MSG_MAP
	DECLARE_WISP_MSG(OnCreate);
	DECLARE_WISP_MSG(OnDestroy);
	virtual void BatBeginNodify(WISP_PCSTR szCmd){}
	virtual void BatRunNodify(WISP_PCSTR szCmd){}
	virtual void BatEndNodify(WISP_PCSTR szCmd){}
public:
	virtual void PrintString(CMD_CHAR* pString){ Printf(pString);};
};


#endif
