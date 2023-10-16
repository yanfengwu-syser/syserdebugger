#include "StdAfx.h"
#include "WispConsoleWnd.h"

#define OUTPUT_PREALLOCATE_LEN	MAX_LINE_CHAR*10+1

WISP_MSG_MAP_BEGIN(CWispTerminalWnd)
	WISP_MSG_MAP_ON_EVENT
	WISP_MSG_MAP_ON_COMMAND
	WISP_MSG_MAP(WISP_WM_CREATE,OnCreate)
	WISP_MSG_MAP(WISP_WM_CHAR,OnChar);
	WISP_MSG_MAP(WISP_WM_KEY_EVENT,OnKeyEvent)
WISP_MSG_MAP_END(CWispColorStrWnd)

WISP_MSG_CMD_MAP_BEGIN(CWispTerminalWnd)
WISP_MSG_CMD_MAP_DEFAULT_END(OnCmdGetCmd)

WISP_MSG_EVENT_MAP_BEGIN(CWispTerminalWnd)
	WISP_MSG_EVENT_MAP(WISP_ID_PASTE,OnEventPaste)	
WISP_MSG_EVENT_MAP_END

CWispTerminalWnd::CWispTerminalWnd()
{
	m_CtrlType = WISP_CTRL_TERMINAL_WND;
	m_pConsoleWnd = NULL;
	m_Prefix=WISP_STR(">");
	m_MaxChars = m_Prefix.m_Length;
	m_OutPutStr.Preallocate(OUTPUT_PREALLOCATE_LEN);
	m_pStream = NULL;
	m_StreamStyle = WISP_SSTREAM_UNIX;
}

CWispTerminalWnd::~CWispTerminalWnd()
{
}

bool CWispTerminalWnd::OnCreate(IN WISP_MSG*pMsg)
{
	EnableScrollBar(WISP_SB_VERT);
	EnableScrollBar(WISP_SB_HORZ);
	m_InputStr.Empty();
	m_InputStr=m_Prefix;
	m_CaretPos.x=m_ScrPos.x+m_InputStr.m_Length;
	m_CaretPos.y=m_LineList.Count();
	m_CurHisIndex=-1;
	RecalcLayout();
	UpdateCaretState();
	CreateCaret(WISP_DI_CARET);
	ShowCaret(true);
	BlinkCaret(300);
	m_bBGColor	= true;
	m_crBGColor = m_pWispBase->m_pCurDrawObj->m_crSystem[SC_BLACK];
	m_TextColor = SC_WHITE;
	m_bNewLine = true;
	m_Style|=WISP_WCSS_SELECT_STRING;
	return true;
}

bool CWispTerminalWnd::OnKeyEvent(IN WISP_MSG*pMsg)
{
	if(pMsg->KeyEvent.bKeyDown)
	{
		switch(pMsg->KeyEvent.KeyType)
		{
		case WISP_VK_UP:
			{
				if(m_CmdHistroy.Count() && m_CurHisIndex<m_CmdHistroy.Count()-1)
				{
					if(m_CurHisIndex<0)
						m_CurHisIndex=0;
					else
						m_CurHisIndex++;
					m_InputStr = m_CmdHistroy[m_CurHisIndex];
					m_CaretPos.x = m_InputStr.GetLength();
					RecalcLayout();
					Update();
				}
			}
			break;
		case WISP_VK_DOWN:
			{
				if(m_CmdHistroy.Count() && m_CurHisIndex>0)
				{
					m_CurHisIndex--;
					m_InputStr = m_CmdHistroy[m_CurHisIndex];
					m_CaretPos.x = m_InputStr.Length();
					RecalcLayout();
					Update();
				}
			}
			break;
		case WISP_VK_LBUTTON:
			{
				int NewX,ScrY;
				ScrY = (pMsg->MsgMouseCltPT.y-m_Margin)/m_ClientDC.m_pFont->m_Height;
				if(ScrY == m_LineList.Count() - m_ScrPos.y)
				{
					NewX = (pMsg->MsgMouseCltPT.x-m_Margin)/m_ClientDC.m_pFont->m_Width + m_ScrPos.x;
					if(NewX >= m_Prefix.Length() && NewX<=m_InputStr.Length())
					{
						m_CaretPos.x = NewX;
						RecalcLayout();
						UpdateClient();
					}
				}
			}
			break;
		case WISP_VK_LEFT:
			ClearSelect();
			if(m_CaretPos.x>m_Prefix.Length())
			{
				m_CaretPos.x--;
				EnsureInputCaretVisible();
				RecalcLayout();
			}
			UpdateClient();
			break;
		case WISP_VK_RIGHT:
			ClearSelect();
			if(m_CaretPos.x<m_InputStr.Length())
			{	
				m_CaretPos.x++;
				EnsureInputCaretVisible();
				RecalcLayout();
			}
			UpdateClient();
			break;
		case WISP_MOD_SHIFT|WISP_VK_LEFT:
			if(m_bSelect)
			{
				if(m_CaretPos.x > m_Prefix.Length() && m_RealSelEndPos.y==m_LineList.Count())
				{
					m_CaretPos.x--;
					m_RealSelEndPos.x = m_CaretPos.x;
					UpdateCaretState();
					m_RealSelEndPos.y = m_RealSelStartPos.y;
				}
			}
			else
			{
				if(m_CaretPos.x>m_Prefix.Length())
				{
					m_bSelect = true;
					m_RealSelStartPos = m_CaretPos;
					m_RealSelStartPos.x--;
					m_RealSelEndPos = m_RealSelStartPos;
					m_CaretPos.x = m_RealSelEndPos.x;
					UpdateCaretState();
				}
			}
			if(m_RealSelEndPos.y < m_RealSelStartPos.y || (m_RealSelEndPos.y == m_RealSelStartPos.y && m_RealSelEndPos.x < m_RealSelStartPos.x) )
			{
				m_pSelStartPos = &m_RealSelEndPos;
				m_pSelEndPos = &m_RealSelStartPos;
			}
			else
			{
				m_pSelStartPos = &m_RealSelStartPos;
				m_pSelEndPos = &m_RealSelEndPos;
			}
			Update();
			break;
		case WISP_MOD_SHIFT|WISP_VK_RIGHT:
			if(m_bSelect)
			{
				if(m_CaretPos.x<m_InputStr.Length() && m_RealSelEndPos.y==m_LineList.Count())
				{
					m_RealSelEndPos.x = m_CaretPos.x;
					m_CaretPos.x++;
					UpdateCaretState();
					m_RealSelEndPos.y = m_RealSelStartPos.y;
				}
			}
			else
			{
				if(m_CaretPos.x<m_InputStr.Length())
				{
					m_bSelect = true;
					m_RealSelStartPos = m_CaretPos;
					m_RealSelEndPos = m_CaretPos;
					m_CaretPos.x++;
					UpdateCaretState();
				}
			}
			if(m_RealSelEndPos.y < m_RealSelStartPos.y || (m_RealSelEndPos.y == m_RealSelStartPos.y && m_RealSelEndPos.x < m_RealSelStartPos.x) )
			{
				m_pSelStartPos = &m_RealSelEndPos;
				m_pSelEndPos = &m_RealSelStartPos;
			}
			else
			{
				m_pSelStartPos = &m_RealSelStartPos;
				m_pSelEndPos = &m_RealSelEndPos;
			}
			Update();
			break;
		case WISP_MOD_CTRL|WISP_VK_X:
		case WISP_VK_DELETE:
			if(m_bSelect && m_pSelStartPos->y==m_LineList.Count() && m_pSelStartPos->x>=m_Prefix.Length() && m_pSelEndPos->x>=m_pSelStartPos->x)
			{
				int Count = m_pSelEndPos->x-m_pSelStartPos->x+1;
				if(pMsg->KeyEvent.KeyType == (WISP_MOD_CTRL|WISP_VK_X))
				{
					CWispString Str;
					Str.Preallocate(Count+1);
					Str.m_Length=TStrCpyLimit(Str.m_pData,&m_InputStr.m_pData[m_pSelStartPos->x],Count+1);
					m_pWispBase->SetClipboardString(Str);
				}
				m_InputStr.Delete(m_pSelStartPos->x,Count);
				m_bSelect = false;
				m_CaretPos.x = m_pSelStartPos->x;
				RecalcLayout();
				UpdateClient();
			}
			else if(m_CaretPos.x<m_InputStr.Length())
			{
				m_InputStr.Delete(m_CaretPos.x);
				RecalcLayout();
				UpdateClient();
			}
			break;
		case WISP_VK_HOME:
			{
				m_CaretPos.x = m_Prefix.Length();
				EnsureInputCaretVisible();
				RecalcLayout();
				UpdateClient();
			}
			break;
		case WISP_VK_END:
			{
				m_CaretPos.x = m_InputStr.Length();
				EnsureInputCaretVisible();
				RecalcLayout();
				UpdateClient();
			}
			break;
		}
	}
	return true;
}

bool CWispTerminalWnd::OnChar(IN WISP_MSG*pMsg)
{
	if(m_CaretPos.x>=MAX_CHARS_PER_LINE-1 && pMsg->Char.Char!=0x08/*Back Space*/&&pMsg->Char.Char!='\n')
		return true;
	if(m_LineList.Count()>m_nLinesPerPage && m_ScrPos.y < m_LineList.Count() - m_nLinesPerPage + 1)
		EnsureInputVisible();
	if(pMsg->Char.Char==0x08/*Back Space*/)
	{
		if(m_bSelect && m_pSelStartPos->y==m_LineList.Count() && m_pSelStartPos->x>=m_Prefix.Length() && m_pSelEndPos->x>m_pSelStartPos->x)
		{
			m_InputStr.Delete(m_pSelStartPos->x,m_pSelEndPos->x-m_pSelStartPos->x);
			m_bSelect = false;
			m_CaretPos.x = m_pSelStartPos->x;
			RecalcLayout();
			UpdateClient();					
		}
		else
		{
			if(m_CaretPos.x<=m_Prefix.Length())
				return true;
			m_CaretPos.x--;
			if(m_CaretPos.x<m_ScrPos.x)
			{
				m_ScrPos.x-=m_nCharsPerLine/2;
				if(m_ScrPos.x<0)
					m_ScrPos.x=0;
			}
			if(m_CaretPos.x<=m_InputStr.Length())
			{
				if(m_CaretPos.x>=m_Prefix.Length())
					m_InputStr.Delete(m_CaretPos.x);
			}
			else
				m_InputStr.Truncate(m_CaretPos.x);
			RecalcLayout();
			Update();
		}
		return true;
	}
	if(pMsg->Char.Char!='\n')
	{
		if(pMsg->Char.Char=='\t')
		{//×Ô¶¯²¹Æë
			for(CCmdMap::IT Iter=m_pConsoleWnd->m_CmdMap.Begin();Iter!=m_pConsoleWnd->m_CmdMap.End();Iter++)
			{
				if(TStrNICmp(&m_InputStr[m_Prefix.m_Length],(CMD_CHAR*)Iter.Key(),m_InputStr.m_Length-m_Prefix.m_Length)==0)
				{
					m_InputStr = m_Prefix+Iter.Key();
					m_CaretPos.x = m_InputStr.m_Length;
					break;
				}
			}
		}
		else
		{
			if(m_CaretPos.x<m_InputStr.Length())
			{
				m_InputStr.Insert(m_CaretPos.x,pMsg->Char.Char);
			}
			else
			{
				m_InputStr+=pMsg->Char.Char;
			}
			m_CaretPos.x++;
			if(m_InputStr.m_Length+1>m_MaxChars)
				m_MaxChars = m_InputStr.m_Length+1;
			if(m_CaretPos.x>=m_ScrPos.x+m_nCharsPerLine)
				m_ScrPos.x++;
		}
	}
	if(pMsg->Char.Char=='\n')
	{
		if(m_InputStr.GetLength()>m_Prefix.GetLength())
		{
			m_CmdHistroy.Push(m_InputStr);
			m_CurHisIndex = -1;
		}
		WISP_MSG Msg;
		Msg.hWnd = this;
		Msg.Msg = WISP_WM_COMMAND;
		Msg.Command.CmdID = WISP_ID_SELF;
		Msg.Command.CmdMsg = WISP_CMD_GET_CMD;
		Msg.Command.Param2 = m_InputStr;
		m_CmdStr = &m_InputStr[m_Prefix.m_Length];
		m_InputStr.SetAt(m_Prefix.m_Length,0);
		m_CaretPos.x=m_Prefix.m_Length;
		SEND_MSG(&Msg);
		if(m_nLinesPerPage>0)
		{
			m_ScrPos.y=m_LineList.Count()-m_nLinesPerPage+1;
			MIN_LIMIT(m_ScrPos.y,0);
			SetScrollBarCurPos(WISP_SB_VERT,m_ScrPos.y);
		}
		m_CaretPos.y=m_LineList.Count();
		m_ScrPos.x=0;
	}
	RecalcLayout();
	Update();
	return true;
}

bool CWispTerminalWnd::OnCmdGetCmd(IN WISP_MSG*pMsg)
{
	if(pMsg->Command.CmdMsg==WISP_CMD_GET_CMD)
	{
		LockUpdate();
		Printf(WISP_STR("%s%s\n"),(WISP_PCSTR)m_InputStr,(WISP_PCSTR)m_CmdStr);
		if(m_pConsoleWnd==NULL)
		{
			Printf(WISP_STR("Error : inside error!\n"));
			UnlockUpdate();
			return false;
		}
		if(m_CmdStr.Length())
		{
			if(m_CtrlType == WISP_CTRL_TERMINAL_WND)
				m_pConsoleWnd->m_pTerminalWnd = this;
			if(m_pConsoleWnd->RunCmdNotify(m_CmdStr))
			{
				if(m_pConsoleWnd->RunCmd(m_CmdStr)==false)
					Printf(WISP_STR("Error : unknown command !\n"));
				AfterRunCmdNotify(m_CmdStr);
			}
			if(m_CtrlType == WISP_CTRL_TERMINAL_WND)
				m_pConsoleWnd->m_pTerminalWnd = NULL;
		}
		UnlockUpdate();
	}
	return true;
}

bool CWispTerminalWnd::OnEventPaste(IN WISP_MSG*pMsg)
{
	if(m_pWispBase->m_ClipboardString.IsEmpty()==false)
	{
		m_InputStr.Insert(m_CaretPos.x,m_pWispBase->m_ClipboardString);
		if(m_InputStr.GetLength()>=MAX_CHARS_PER_LINE)
			m_InputStr.Truncate(MAX_CHARS_PER_LINE);
		m_CaretPos.x += m_pWispBase->m_ClipboardString.Length();
		MAX_LIMIT(m_CaretPos.x,m_InputStr.GetLength());
		UpdateCaretState();
		Update();
	}
	return true;
}

void CWispTerminalWnd::SetFontColor(BYTE ColorIndex)
{
	if(m_CtrlType == WISP_CTRL_CONSOLE_WND && ((CWispConsoleWnd*)this)->m_pTerminalWnd)
		((CWispConsoleWnd*)this)->m_pTerminalWnd->m_TextColor = ColorIndex;
	else
		m_TextColor = ColorIndex;
}

void CWispTerminalWnd::SaveFontColor()
{
	if(m_CtrlType == WISP_CTRL_CONSOLE_WND && ((CWispConsoleWnd*)this)->m_pTerminalWnd)
		((CWispConsoleWnd*)this)->m_pTerminalWnd->m_OldTextColor = ((CWispConsoleWnd*)this)->m_pTerminalWnd->m_TextColor;
	else
		m_OldTextColor = m_TextColor;
}

void CWispTerminalWnd::RestoreFontColor()
{
	if(m_CtrlType == WISP_CTRL_CONSOLE_WND && ((CWispConsoleWnd*)this)->m_pTerminalWnd)
		((CWispConsoleWnd*)this)->m_pTerminalWnd->m_TextColor = ((CWispConsoleWnd*)this)->m_pTerminalWnd->m_OldTextColor;
	else
		m_TextColor = m_OldTextColor;
}

void CWispTerminalWnd::EnsureInputVisible()
{
	m_ScrPos.y=m_LineList.Count()-m_nLinesPerPage+1;
	MIN_LIMIT(m_ScrPos.y,0);
	SetScrollBarCurPos(WISP_SB_VERT,m_ScrPos.y);
	UpdateCaretState();
}

void CWispTerminalWnd::EnsureInputCaretVisible()
{
	if(m_CaretPos.x < m_ScrPos.x)
		m_ScrPos.x = m_CaretPos.x;
	if(m_CaretPos.x >= m_ScrPos.x+m_nCharsPerLine)
		m_ScrPos.x = m_CaretPos.x - m_nCharsPerLine+1;
	MIN_LIMIT(m_CaretPos.x,0);
	UpdateCaretState();
	Update();
}

bool CWispTerminalWnd::RunModulePathBat(PCSTR FileName,PCSTR szCmdArg,int*pResult)
{
	WCHAR wszBuffer[MAX_FN_LEN];
	char szBuffer[MAX_FN_LEN],*pStr;
	pStr = szBuffer + TStrCpy(szBuffer,"bat ");
	if(szCmdArg)
	{
		pStr+=TStrCpy(pStr,szCmdArg);
		pStr+=TStrCpy(pStr," ");
	}
	pStr+=GetModulePath(pStr);
	pStr+=TStrCpy(pStr,FileName);
	AnsiToUnicode(szBuffer,wszBuffer,MAX_FN_LEN);
	return m_pConsoleWnd->RunCmd(wszBuffer,pResult);
}

bool CWispTerminalWnd::TermRunCmd(const CMD_CHAR*szCmd,int*pResult)
{
	bool Result;
	if(m_CtrlType == WISP_CTRL_TERMINAL_WND)
		m_pConsoleWnd->m_pTerminalWnd = this;
	Result = m_pConsoleWnd->RunCmd(szCmd,pResult);
	if(m_CtrlType == WISP_CTRL_TERMINAL_WND)
		m_pConsoleWnd->m_pTerminalWnd = NULL;
	return Result;
}

bool CWispTerminalWnd::SaveHistroys(PCSTR FileName)
{
	int Length;
	WCHAR wszBuffer[MAX_CHARS_PER_LINE+2];
	CHAR szBuffer[MAX_CHARS_PER_LINE+2];
	CImageFileStream FileObj;
	gpFileIO->DeleteFile(FileName);
	if(FileObj.Create(FileName)==false)
		return false;
	for(int n=0;n<m_LineList.Count();n++)
	{
		TStrCpyLimit(wszBuffer,(WISP_COLOR_CHAR*)m_LineList[n],sizeof(szBuffer));
		Length=UnicodeToAnsi(wszBuffer,szBuffer,sizeof(szBuffer));
		TStrCpy(&szBuffer[Length],"\r\n");
		Length+=2;
		FileObj.Puts(szBuffer,Length);
	}
	FileObj.Close();
	return true;
}

void CWispTerminalWnd::SetHistoryLines(IN int nLine)
{
	if(nLine> 0 && nLine<10000)
		m_LineList.Resize(nLine);
}

void CWispTerminalWnd::ClearScreen()
{
	m_LineList.Clear();
	m_CaretPos.x = m_Prefix.m_Length;
	m_CaretPos.y = 0;
	m_ScrPos.x = m_ScrPos.y = 0;
	m_MaxChars = m_Prefix.m_Length+1;
	SetMaxLines(m_LineList.Count()+1);
	m_InputStr = m_Prefix;
	RecalcLayout();
	Update();
}

void CWispTerminalWnd::Output(IN const WISP_CHAR*szLine)
{
	int Length,TotalLength,LineLengthLeft;
	const WISP_CHAR*pThisLine,*pNextLine;
	WISP_COLOR_CHAR szLineBuffer[MAX_CHARS_PER_LINE+1];
	CWispColorString*pLine;

	if(m_CtrlType == WISP_CTRL_CONSOLE_WND && ((CWispConsoleWnd*)this)->m_pTerminalWnd)
	{
		((CWispConsoleWnd*)this)->m_pTerminalWnd->Output(szLine);
		return;
	}
	TotalLength = TStrLen(szLine);
	if(m_bNewLine)
	{
		LineLengthLeft = MAX_CHARS_PER_LINE;
		pLine = m_LineList.Append();
		SetMaxLines(m_LineList.Count()+1);
		pLine->Empty();
		m_bNewLine = false;
	}
	else
	{
		LineLengthLeft = MAX_CHARS_PER_LINE - m_LineList[m_LineList.Count()-1].m_Length;
		pLine = &m_LineList[m_LineList.Count()-1];
	}
	pThisLine = szLine;
	while(pThisLine && *pThisLine)
	{
		if(LineLengthLeft==0)
		{
			LineLengthLeft = MAX_CHARS_PER_LINE;
			pLine = m_LineList.Append();
			SetMaxLines(m_LineList.Count()+1);
			pLine->Empty();
		}
		pNextLine=TStrChr(pThisLine,(WISP_CHAR)'\n');
		if(pNextLine)
		{
			Length = (int) (pNextLine - pThisLine);
			if(Length>LineLengthLeft)
				Length = LineLengthLeft;
			pNextLine++;
			ColorStrNCpy(szLineBuffer,pThisLine,Length,m_TextColor,0);
			if(*pNextLine==0)
			{
				m_bNewLine=true;
				if(m_pStream)
				{
					if(m_StreamStyle&WISP_SSTREAM_DOS)
						szLineBuffer[Length++] = (WISP_COLOR_CHAR)'\r';
					szLineBuffer[Length++] = (WISP_COLOR_CHAR)'\n';
					szLineBuffer[Length] = 0;
				}
			}
			if(m_pStream)
				m_pStream->Puts((void*)szLineBuffer,Length*sizeof(WISP_COLOR_CHAR));
			*pLine += szLineBuffer;
			if(pLine->m_Length > m_MaxChars)
				m_MaxChars = pLine->m_Length;
			LineLengthLeft = 0;
		}
		else
		{
			Length = TStrLen(pThisLine);
			if(Length>LineLengthLeft)
				Length = LineLengthLeft;
			pNextLine = &pThisLine[Length];
			ColorStrNCpy(szLineBuffer,pThisLine,Length,m_TextColor,0);
			*pLine += szLineBuffer;
			if(m_pStream)
				m_pStream->Puts((void*)szLineBuffer,Length*sizeof(WISP_COLOR_CHAR));
			if(pLine->m_Length > m_MaxChars)
				m_MaxChars = pLine->m_Length;
			LineLengthLeft = MAX_CHARS_PER_LINE - pLine->m_Length;
		}
		pThisLine = pNextLine;
	}
	m_CaretPos.y=m_LineList.Count();
	if(m_nLinesPerPage>0)
	{
		m_ScrPos.y=m_LineList.Count()-m_nLinesPerPage+1;
		MIN_LIMIT(m_ScrPos.y,0);
		SetScrollBarCurPos(WISP_SB_VERT,m_ScrPos.y);
	}
	RecalcLayout();
}

void CWispTerminalWnd::Output(IN const WISP_COLOR_CHAR*szLine)
{
	int Length,TotalLength,LineLengthLeft;
	const WISP_COLOR_CHAR*pThisLine,*pNextLine;
	WISP_COLOR_CHAR szLineBuffer[MAX_CHARS_PER_LINE+1];
	CWispColorString*pLine;

	if(m_CtrlType == WISP_CTRL_CONSOLE_WND && ((CWispConsoleWnd*)this)->m_pTerminalWnd)
	{
		((CWispConsoleWnd*)this)->m_pTerminalWnd->Output(szLine);
		return;
	}
	TotalLength = TStrLen(szLine);
	if(m_bNewLine)
	{
		LineLengthLeft = MAX_CHARS_PER_LINE;
		pLine = m_LineList.Append();
		SetMaxLines(m_LineList.Count()+1);
		pLine->Empty();
		m_bNewLine = false;
	}
	else
	{
		LineLengthLeft = MAX_CHARS_PER_LINE - m_LineList[m_LineList.Count()-1].m_Length;
		pLine = &m_LineList[m_LineList.Count()-1];
	}
	pThisLine = szLine;
	while(pThisLine && *pThisLine)
	{
		if(LineLengthLeft==0)
		{
			LineLengthLeft = MAX_CHARS_PER_LINE;
			pLine = m_LineList.Append();
			SetMaxLines(m_LineList.Count()+1);
			pLine->Empty();
		}
		pNextLine=TStrChr(pThisLine,(WISP_COLOR_CHAR)'\n');
		if(pNextLine)
		{
			Length = (int) (pNextLine - pThisLine);
			if(Length>LineLengthLeft)
				Length = LineLengthLeft;
			pNextLine++;
			TStrCpyLimit(szLineBuffer,pThisLine,Length+1);
			if(*pNextLine==0)
			{
				m_bNewLine=true;
				if(m_pStream)
				{
					if(m_StreamStyle&WISP_SSTREAM_DOS)
						szLineBuffer[Length++] = (WISP_COLOR_CHAR)'\r';
					szLineBuffer[Length++] = (WISP_COLOR_CHAR)'\n';
					szLineBuffer[Length] = 0;
				}
			}
			if(m_pStream)
				m_pStream->Puts((void*)szLineBuffer,Length*sizeof(WISP_COLOR_CHAR));
			*pLine += szLineBuffer;
			if(pLine->m_Length > m_MaxChars)
				m_MaxChars = pLine->m_Length;
			LineLengthLeft = 0;
		}
		else
		{
			Length = TStrLen(pThisLine);
			if(Length>LineLengthLeft)
				Length = LineLengthLeft;
			pNextLine = &pThisLine[Length];
			TStrCpyLimit(szLineBuffer,pThisLine,Length+1);
			*pLine += szLineBuffer;
			if(m_pStream)
				m_pStream->Puts((void*)szLineBuffer,Length*sizeof(WISP_COLOR_CHAR));
			if(pLine->m_Length > m_MaxChars)
				m_MaxChars = pLine->m_Length;
			LineLengthLeft = MAX_CHARS_PER_LINE - pLine->m_Length;
		}
		pThisLine = pNextLine;
	}
}

void CWispTerminalWnd::Output(WISP_CHAR ch)
{
	if(ch)
	{
		m_OutPutStr+=ch;
	}
	if((ch==0 && m_OutPutStr.m_Length) || m_OutPutStr.m_Length >= MAX_CHARS_PER_LINE)
	{
		Output(m_OutPutStr);
		m_OutPutStr.Truncate(0);
	}
}

void CWispTerminalWnd::AttachConsole(CWispConsoleWnd*pConsoleWnd)
{
	m_pConsoleWnd = pConsoleWnd;
}

BYTE CWispTerminalWnd::GetLineStr(IN int LineIndex,OUT WISP_COLOR_CHAR*pColorStr)
{
	if(LineIndex>m_LineList.Count())
		return 0;
	if(LineIndex<m_LineList.Count())
	{
		TStrCpy(pColorStr,(WISP_COLOR_CHAR*)m_LineList[LineIndex]);
	}
	else
	{
		ColorStrCpy(pColorStr,(WISP_CHAR*)m_InputStr,m_TextColor,0);
	}
	int len=TStrLen(pColorStr);
	return 0;
}

CWispConsoleWnd::CWispConsoleWnd()
{
	m_CtrlType = WISP_CTRL_CONSOLE_WND;
	m_pConsoleWnd = this;
	m_pTerminalWnd = NULL;
}

WISP_MSG_MAP_BEGIN(CWispConsoleWnd)
	WISP_MSG_MAP(WISP_WM_CREATE,OnCreate)
	WISP_MSG_MAP(WISP_WM_DESTROY,OnDestroy)
WISP_MSG_MAP_END(CWispTerminalWnd)

bool CWispConsoleWnd::OnCreate(IN WISP_MSG*pMsg)
{
	InsertCmd(WISP_STR("cls"),(CMDPROC)CWispConsoleWnd::Cls,this,WISP_STR("Clear screen"),NULL);
	InsertCmd(WISP_STR("wispver"),(CMDPROC)CWispConsoleWnd::WispVer,this,NULL,NULL);
	InsertCmd(WISP_STR("hl"),(CMDPROC)CWispConsoleWnd::HL,this,WISP_STR("Set count of histroy lines"),NULL);
	InsertCmd(WISP_STR("hcc"),(CMDPROC)CWispConsoleWnd::HCC,this,WISP_STR("Set count of command histroy"),NULL);
	InsertCmd(WISP_STR("hc"),(CMDPROC)CWispConsoleWnd::HC,this,WISP_STR("add a command string into histroy"),NULL);
	InsertCmd(WISP_STR("Color"),(CMDPROC)CWispConsoleWnd::Color,this,WISP_STR("Set default font color"),NULL);
	InsertCmd(WISP_STR("BKColor"),(CMDPROC)CWispConsoleWnd::BKColor,this,WISP_STR("Set default font color"),NULL);
	InsertCmd(WISP_STR("help"),(CMDPROC)CWispConsoleWnd::Help,this,WISP_STR("Display this help information"),NULL);
	InsertCmd(WISP_STR("h"),(CMDPROC)CWispConsoleWnd::Help,this,WISP_STR("Display this help information"),NULL);
	InsertCmd(WISP_STR("bat"),(CMDPROC)CWispConsoleWnd::Bat,this,NULL,NULL);
	InsertCmd(WISP_STR("set"),(CMDPROC)CWispConsoleWnd::Set,this,NULL,NULL);
	InsertCmd(WISP_STR("#"),(CMDPROC)CWispConsoleWnd::DoNothing,this,NULL,NULL);
	InsertCmd(WISP_STR("@"),(CMDPROC)CWispConsoleWnd::Print,this,NULL,NULL);
	return true;
}

bool CWispConsoleWnd::OnDestroy(IN WISP_MSG*pMsg)
{
	Reset();
	return true;
}

void CWispConsoleWnd::DisplayColor()
{
	Printf(WISP_STR("%<0>0 ------- Black\n"));
	Printf(WISP_STR("%<1>1 ------- White\n"));
	Printf(WISP_STR("%<2>2 ------- Red\n"));
	Printf(WISP_STR("%<3>3 ------- Light Red\n"));
	Printf(WISP_STR("%<4>4 ------- Green\n"));
	Printf(WISP_STR("%<5>5 ------- Light Green\n"));
	Printf(WISP_STR("%<6>6 ------- Blue\n"));
	Printf(WISP_STR("%<7>7 ------- Light Blue\n"));
	Printf(WISP_STR("%<8>8 ------- Brown\n"));
	Printf(WISP_STR("%<9>9 ------- Light Brown\n"));
	Printf(WISP_STR("%<A>A ------- Cyan\n"));
	Printf(WISP_STR("%<B>B ------- Light Cyan\n"));
	Printf(WISP_STR("%<C>C ------- Gray\n"));
	Printf(WISP_STR("%<D>D ------- Light Gray\n"));
	Printf(WISP_STR("%<E>E ------- Yellow\n"));
	Printf(WISP_STR("%<F>F ------- Light Yellow\n"));
}

int CWispConsoleWnd::Color(int argc, WISP_CHAR *argv[ ],WISP_PCSTR szCommandLine, CWispConsoleWnd*pConWnd)
{
	CONSOLE_TERMINAL(pConWnd);
	BYTE Color;
	if(argc!=2 || USHexStrToNum(argv[1],&Color)==false)
	{
		pConWnd->Printf(WSTR("Usage : Color Color_Index[0 - FF]\n"));
		pConWnd->DisplayColor();
		return 0;
	}
	pConWnd->SetFontColor(Color);
	return 0;
}

int CWispConsoleWnd::BKColor(int argc, WISP_CHAR *argv[ ],WISP_PCSTR szCommandLine, CWispConsoleWnd*pConWnd)
{
	CONSOLE_TERMINAL(pConWnd);
	BYTE Color;
	if(argc!=2 || USHexStrToNum(argv[1],&Color)==false)
	{
		pConWnd->Printf(WSTR("Usage : BKColor Color_Index[0 - FF]\n"));
		pConWnd->DisplayColor();
		return 0;
	}
	pConWnd->SetBGColor(pConWnd->SYS_COLOR[Color]);
	return 0;
}

int CWispConsoleWnd::Cls(int argc, WISP_CHAR *argv[ ],WISP_PCSTR szCommandLine, CWispConsoleWnd*pConWnd)
{
	CONSOLE_TERMINAL(pConWnd);
	pConWnd->ClearScreen();
	return 0;
}

int CWispConsoleWnd::HL(int argc, WISP_CHAR *argv[ ],WISP_PCSTR szCommandLine, CWispConsoleWnd*pConWnd)
{
	CONSOLE_TERMINAL(pConWnd);
	ULSIZE Line;
	if(argc!=2)
	{
		pConWnd->Printf(WISP_STR("Usage : hl <histroy lines count>\n"));
		pConWnd->Printf(WISP_STR("Current count of histroy lines = %<E>%d (dec)\n"),pConWnd->m_LineList.Size());
		return -1;
	}
	if(USDecStrToNum(argv[1],&Line)==false)
	{
		pConWnd->Printf(WISP_STR("Error : %s is Invalid !\n"),argv[1]);
		return -1;
	}
	if(Line<1 || Line> 10000)
	{
		pConWnd->Printf(WISP_STR("Error : please input from 1 to 1000\n"));
		return -1;
	}
	pConWnd->SetHistoryLines(Line);
	return 0;
}

int CWispConsoleWnd::HCC(int argc, WISP_CHAR *argv[ ],WISP_PCSTR szCommandLine, CWispConsoleWnd*pConWnd)
{
	ULONG Count;
	CONSOLE_TERMINAL(pConWnd);
	if(argc==1)
	{
		pConWnd->Printf(WSTR("command histroy count = %d\n"),pConWnd->m_CmdHistroy.Count());
		return 0;
	}
	if(argc>2 || USDecStrToNum(argv[1],&Count)==false)
	{
		pConWnd->Printf(WSTR("Usage : hcc command_histroy_count\n"));
		return 1;
	}
	pConWnd->m_CmdHistroy.Resize(Count);
	return 0;
}

int CWispConsoleWnd::HC(int argc, WISP_CHAR *argv[ ],WISP_PCSTR szCommandLine, CWispConsoleWnd*pConWnd)
{
	if(argc==1)
	{
		pConWnd->Printf(WSTR("Usage : hc sz_command_line\n"));
		return 1;
	}
	pConWnd->m_CmdHistroy.Push(pConWnd->m_Prefix+&szCommandLine[argv[1]-argv[0]]);
	return 0;
}

int CWispConsoleWnd::Bat(int argc,WISP_CHAR *argv[ ],WISP_PCSTR szCommandLine,CWispConsoleWnd*pConWnd)
{
	bool bSilence,bBreak;
	WISP_PCSTR pszFileName;
	WCHAR szCmd[MAX_CHARS_PER_LINE+1];
	char FileName[MAX_FN_LEN];
	CTXTFile TextFile;
	int Result;
	if(argc<2)
		goto ShowUsage;
	bSilence = false;
	bBreak = false;
	if(argv[1][0]=='-')
	{
		bSilence = TStrIChr(argv[1],WCHAR('s'))!=NULL;
		bBreak = TStrIChr(argv[1],WCHAR('b'))!=NULL;
		if(argc<3)
			goto ShowUsage;
		pszFileName = &szCommandLine[argv[2]-argv[0]];
	}
	else
		pszFileName = &szCommandLine[argv[1]-argv[0]];
	UnicodeToAnsi(pszFileName,FileName,MAX_FN_LEN);
	if(TextFile.Open(FileName)==false)
	{
		if(bSilence==false)
			pConWnd->Printf(WSTR("%<3>Error : %<B>Fail to open file %<F>%s %<1>!\n"),argv[1]);
		return 1;
	}
	pConWnd->BatBeginNodify(szCommandLine);
	Result = 0;
	for(TTXTStrList::IT LineIter = TextFile.m_StrList.Begin();LineIter!=TextFile.m_StrList.End();LineIter++)
	{
		AnsiToUnicode(*LineIter,szCmd,sizeof(szCmd)/sizeof(WCHAR));
		Result = 1;
		pConWnd->BatRunNodify(szCmd);
		if(pConWnd->RunCmd(szCmd,&Result)==false && bBreak)
			break;
		if(bBreak && Result!=0)
			break;
	}
	TextFile.Close();
	pConWnd->BatEndNodify(szCommandLine);
	return Result;
ShowUsage:
	pConWnd->Printf(WSTR("Usage:%<B>bat [-s|b] %<1>bat_file_name \n"));
	pConWnd->Printf(WSTR("s : silence mode\n"));
	pConWnd->Printf(WSTR("b : break if command fail\n"));
	return 1;

}

void show_env_value(PCWSTR szName,STOptVal::TYPE Type,void*pValue,CWispConsoleWnd*pTermWnd)
{
	switch(Type)
	{
	case STOptVal::INT_VAL:
		pTermWnd->Printf(WSTR("%<B>%-12s %<1>= %<4>%d %<1>(dec)\n"),szName,*(int*)pValue);
		break;
	case STOptVal::UINT_VAL:
		pTermWnd->Printf(WSTR("%<B>%-12s %<1>= %<4>%u %<1>(dec)\n"),szName,*(UINT*)pValue);
		break;
	case STOptVal::FLOAT_VAL:
		break;
	case STOptVal::STR_VAL:
		pTermWnd->Printf(WSTR("%<B>%-12s %<1>= %<F>\"%s\"%<1>\n"),szName,(PCWSTR)pValue);
		break;
	case STOptVal::NULL_VAL:
		pTermWnd->Printf(WSTR("Error : Invalid value name !\n"));
		break;
	}
}

int CWispConsoleWnd::Set(int argc,WISP_CHAR *argv[ ],WISP_PCSTR szCommandLine,CWispConsoleWnd*pConWnd)
{
	CWispConsoleWnd*pOrgConWnd = pConWnd;
	CONSOLE_TERMINAL(pConWnd);
	STOptVal::TYPE Type;
	int Length;
	bool Result;
	void*pValue;
	if(argc==1)
	{
		for(COptValMap::IT Iter = pOrgConWnd->m_Option.m_OptValMap.Begin();Iter!=pOrgConWnd->m_Option.m_OptValMap.End();Iter++)
		{
			show_env_value(Iter.Key(),Iter->Type,Iter->pValue,pConWnd);
		}
		return 1;
	}
	if(argc==2)
	{
		Type = pOrgConWnd->m_Option.GetValue(argv[1],&pValue,&Length);
		show_env_value(argv[1],Type,pValue,pConWnd);
		return 1;
	}
	Type = pOrgConWnd->m_Option.GetValue(argv[1],&pValue,&Length);
	switch(Type)
	{
	case STOptVal::INT_VAL:
		Result = SDecStrToNum(argv[2],(int*)pValue);
		break;
	case STOptVal::UINT_VAL:
		Result = USDecStrToNum(argv[2],(int*)pValue);
		break;
	case STOptVal::FLOAT_VAL:
		break;
	case STOptVal::STR_VAL:
		TStrCpyLimit((PWSTR)pValue,argv[2],Length);
		Result = true;
		break;
	case STOptVal::NULL_VAL:
		pConWnd->Printf(WSTR("Error : Invalid value name!\n"));
		return 1;
	}
	if(Result==false)
	{
		pConWnd->Printf(WSTR("Error : Invalid value!\n"));
		return 1;
	}
	return 0;
}


int CWispConsoleWnd::DoNothing(int argc, WISP_CHAR *argv[ ],WISP_PCSTR szCommandLine, CWispConsoleWnd*pConWnd)
{
	return 0;
}

int CWispConsoleWnd::Print(int argc, WISP_CHAR *argv[ ],WISP_PCSTR szCommandLine, CWispConsoleWnd*pConWnd)
{
	CONSOLE_TERMINAL(pConWnd);
	pConWnd->Printf(&szCommandLine[TStrLen(argv[0])+1]);
	pConWnd->Output(WISP_STR("\n"));
	return 0;
}

int CWispConsoleWnd::WispVer(int argc, WISP_CHAR *argv[ ],WISP_PCSTR szCommandLine, CWispConsoleWnd*pConWnd)
{
	WISP_CHAR szData[64],szTime[64];
	CONSOLE_TERMINAL(pConWnd);
	pConWnd->Printf(WISP_STR("Wisp GUI System\n"));
	TStrCpy(szData,__DATE__);
	TStrCpy(szTime,__TIME__);
	pConWnd->Printf(WISP_STR("Build Time : %s  %s\n"),szData,szTime);
	return 0;
}

int CWispConsoleWnd::Help(int argc, WISP_CHAR *argv[ ],WISP_PCSTR szCommandLine, CWispConsoleWnd*pConWnd)
{
	WCHAR szPatten[MAX_LONG_NAME_LEN];
	*szPatten = 0;
	CWispConsoleWnd*pConsoleWnd = pConWnd;
	CONSOLE_TERMINAL(pConWnd);
	if(argc>1)
	{
		TStrCpy(szPatten,argv[1]);
		TStrLwr(szPatten);
		if(TStrChr(szPatten,'*')==NULL && TStrChr(szPatten,'?')==NULL)
		{
			CCmdMap::IT CmdIter = pConsoleWnd->m_CmdMap.Find(szPatten);
			if(CmdIter.IsExist())
			{
				if(CmdIter->pUsage)
					pConWnd->Printf(CmdIter->pUsage);
				else if(CmdIter->pComment)
					pConWnd->Printf(WSTR("%s %s\n"),(WCHAR*)CmdIter.Key(),CmdIter->pComment);
				return 0;
			}
			else
			{
				pConWnd->Printf(WSTR("Invalid Command\n"));
			}
			return 0;
		}
	}
	else
		TStrCpy(szPatten,"*");
	for(CCmdMap::IT Iter = pConsoleWnd->m_CmdMap.Begin();Iter!=pConsoleWnd->m_CmdMap.End();Iter++)
	{
		if(TMultiMatchWithPattern(szPatten,(WCHAR*)Iter.Key()) && Iter->pComment)
		{
			pConWnd->Printf(WSTR("%<B>%-12s    %<F>%s\n"),(WCHAR*)Iter.Key(),Iter->pComment);
		}
	}
	return 0;
}

void CWispTerminalWnd::Printf(IN const WCHAR*szLine,...)
{
	va_list Next;
	va_start(Next,szLine);
	VPrintf(szLine,Next);
	va_end(Next);
}

#define WISP_PUTONE(c)		{Output(c);Length++;}

int CWispTerminalWnd::VPrintf(const WISP_CHAR*format,void*ParamList)
{
	int   Length;				// Limit at entry point
	bool  bMore;				// Loop control
	int	  Width;				// Optional width
	int   Precision;			// Optional precision
	WISP_CHAR  *str;			// String
	WISP_CHAR  strbuf[36];		// Constructed string
	int	  len;					// Length of string
	int	  nLeadingZeros;		// Number of leading zeros required
	int	  nPad;					// Number of pad characters required
	WISP_CHAR  *sPrefix;		// Prefix string
	ULONG val;					// Value of current number
	bool  bLeftJustify;			// Justification
	bool  bPlusSign;			// Show plus sign?
	bool  bBlankSign;			// Blank for positives?
	bool  bZeroPrefix;			// Want 0x for hex, 0 for octal?
	bool  bIsShort;				// TRUE if short
	bool  bIsLong;				// TRUE if long
	WISP_CHAR  cPad;
	WISP_CHAR* savestr;
	bool  bIsLonglong;			// TRUE if LONGLONG
	ULONGLONG val64;
	va_list Next;
	Next = (va_list)ParamList;
	Length=0;
	static WISP_CHAR strPlus[]={'+',0};
	static WISP_CHAR strSub[]={'-',0};
	static WISP_CHAR str0x[]={'0','x',0};
	static WISP_CHAR str0X[]={'0','X',0};
	static WISP_CHAR strNULL[]={0};
	static WISP_CHAR strSpace[]={' ',0};
	static WISP_CHAR strZero[]={'0',0};
	static WISP_CHAR strError[]={'<','E','r','r','o','r','>',0};

	SaveFontColor();

	while(*format != '\0')
	{
		// Everything but '%' is copied to buffer
		if (*format != '%') WISP_PUTONE(*format++)
			// '%' gets special handling here
		else {
			// Set default flags, etc
			Width = 0;
			Precision = -1;
			bLeftJustify = FALSE;
			bPlusSign = FALSE;
			bBlankSign = FALSE;
			bZeroPrefix = FALSE;
			bIsShort = FALSE;
			bIsLong = FALSE;
			bIsLonglong = FALSE;
			cPad = ' ';
			sPrefix = strNULL;
			format++;
			bMore = TRUE;
			while (bMore) {
				// optional flags
				switch (*format) {
		case '-':  bLeftJustify = TRUE; format++; break;
		case '+':  bPlusSign = TRUE; format++; break;
		case '0':  cPad = '0'; format++; break;
		case ' ':  bBlankSign = TRUE; format++; break;
		case '#':  bZeroPrefix = TRUE; format++; break;
		default:   bMore = FALSE;
				}
			}
			// optional width		
			if (*format == '*') {
				Width = (int) va_arg(Next, int);
				format++;
			}
			else if (IS_DIGIT(*format)) {
				while (IS_DIGIT(*format)) {
					Width *= 10;
					Width += (*format++) - '0';
				}
			}
			// optional precision		
			if (*format == '.') {
				format++;
				Precision = 0;
				if (*format == '*') {
					Precision = (int) va_arg(Next, int);
					format++;
				}
				else while (IS_DIGIT(*format)) {
					Precision *= 10;
					Precision += (*format++) - '0';
				}
			}
			// optional size'o'
			switch (*format) 
			{
			case 'h':  bIsShort = TRUE; format++; break;
			case 'l':  bIsLong = TRUE;  format++; break;
			case 'I':
				if ( (format[1]=='6') && (format[2]=='4') )
				{
					format += 3;
					bIsLonglong = TRUE;
				}
				break;
			}
			// All controls are completed, dispatch on the conversion character
			switch (*format++) {
		case 'd':
		case 'i':
			if (bIsLonglong)
				NumToStr( (LONGLONG) va_arg (Next, LONGLONG), strbuf, 10);
			else
				if (bIsLong)		// Signed long int
					NumToStr( (long) va_arg(Next, long), strbuf, 10);
				else			// Signed int
					NumToStr( (int) va_arg(Next, int), strbuf, 10);
			if (strbuf[0] == '-') sPrefix = strSub;
			else {
				if (bPlusSign) sPrefix = strPlus;
				else if (bBlankSign) sPrefix = strSpace;
			}
			goto EmitNumber;
		case 'u':
			if (bIsLonglong)
				uNumToStr( (ULONGLONG) va_arg(Next, ULONGLONG), strbuf, 10);
			else
				if (bIsLong)	// Unsigned long int
					uNumToStr( (long) va_arg(Next, long), strbuf, 10);
				else			// Unsigned int
					uNumToStr( (long) (int) va_arg(Next, int), strbuf, 10);
			goto EmitNumber;
			// set sPrefix for these...
		case 'o':
			if (bIsLonglong)
				uNumToStr( (ULONGLONG) va_arg(Next, ULONGLONG), strbuf, 10);
			else
			{
				if (bZeroPrefix) sPrefix = strZero;
				if (bIsLong)
					val = (long) va_arg(Next, long);
				else
					val = (int) va_arg(Next, int);
				uNumToStr(val, strbuf, 8);
				if (val == 0) sPrefix = strNULL;
			}
			goto EmitNumber;
		case 'p':	// pointer 
		case 'x':
			if (bZeroPrefix) sPrefix = str0x;
			if (bIsLonglong)
			{
				val64 = (ULONGLONG) va_arg(Next, ULONGLONG);
				uNumToStr( val64, strbuf, 16);
				if (val64 == 0) sPrefix = strNULL;
			}
			else
			{
				if (bIsLong)
					val = (ULONG) va_arg(Next, long);
				else
					val = (unsigned int) va_arg(Next, int);			
				uNumToStr(val, strbuf, 16);
				if (val == 0) sPrefix = strNULL;
			}
			goto EmitNumber;
		case 'X':
			if (bZeroPrefix) sPrefix = str0X;
			if (bIsLonglong)
			{
				val64 = (ULONGLONG) va_arg(Next, ULONGLONG);
				uNumToStr( val64, strbuf, 16);
				if (val64 == 0) sPrefix = strNULL;
			}
			else
			{
				if (bIsLong)
					val = (ULONG) va_arg(Next, long);
				else
					val = (unsigned int) va_arg(Next, int);
				uNumToStr(val, strbuf, 16);
				if (val == 0) sPrefix = strNULL;
			}
			TStrUpr(strbuf);
			goto EmitNumber;
		case 'c':
			strbuf[0] = (WISP_CHAR) va_arg(Next, WISP_CHAR);
			str = strbuf;
			len = 1;
			goto EmitString;
		case 's':
			str = (WISP_CHAR *) va_arg(Next, WISP_CHAR*);
			len =  TStrLen(str);
			if (Precision != -1 &&
				Precision < len)
				len = Precision;
			goto EmitString;
		case 'n':
			break;
		case '%':
			strbuf[0] = '%';
			str = strbuf;
			len = 1;
			goto EmitString;
			break;
		case 'f':
		case 'e':
		case 'E':
		case 'g':
		case 'G':
		case 'U':
			str = strError;//"<float format not supported>";
			len =  TStrLen(str);
			goto EmitString;
		case '<':
			{
				int Length;
				WISP_CHAR ColorNum[3],*pStr;
				BYTE ColorIndex;
				pStr = TStrChr(format,(WISP_CHAR)'>');				
				if(pStr)
				{
					Length = (int)(pStr - format);
					if(Length==1 || Length==2)
					{
						TStrCpyLimit(ColorNum,format,Length+1);
						format+=Length+1;
						if(USHexStrToNum(ColorNum,&ColorIndex))
						{
							Output((WISP_CHAR)0);
							SetFontColor(ColorIndex);
						}
						else
							pStr = NULL;
					}
					else
						pStr = NULL;
				}
				if(pStr == NULL)
				{
					str = strError;
					len =  TStrLen(str);
					goto EmitString;
				}
				strbuf[0] = 0;
				str = strbuf;
				len = 0;
				Precision = 0;
			}
			break;
		default:
			str = strError;//"<bad format character>";
			len =  TStrLen(str);
			goto EmitString;
			}
EmitNumber:
			if (Precision == -1) Precision = 1;
			str = strbuf;
			if (*str == '-') str++;		// if negative, already have prefix
			len =  TStrLen(str);
			nLeadingZeros = Precision - len;
			if (nLeadingZeros < 0) nLeadingZeros = 0;
			nPad = Width - (len + nLeadingZeros +  TStrLen(sPrefix));
			if (nPad < 0) nPad = 0;
			// If 0-padding, emit prefix first.
			// if ' ' padding, emit padding first
			if (cPad == '0') {
				while (*sPrefix != '\0') WISP_PUTONE(*sPrefix++);
			}
			if (nPad && !bLeftJustify) {
				// Left padding required
				while (nPad--) {
					WISP_PUTONE(cPad);
				}
				nPad = 0;		// Indicate padding completed
			}
			// Put prefix now if not used up earlier (i.e. if blank padding)
			while (*sPrefix != '\0') WISP_PUTONE(*sPrefix++);
			while (nLeadingZeros-- > 0) WISP_PUTONE('0');
			while (len-- > 0) {
				WISP_PUTONE(*str++);
			}
			if (nPad) {
				// Right padding required
				while (nPad--) WISP_PUTONE(' ');
			}
			goto Done;
EmitString:
			// Here we have the string ready to emit.  Handle padding, etc.
			if (Width > len) nPad = Width - len;
			else nPad = 0;
			if (nPad && !bLeftJustify) {
				// Left padding required
				while (nPad--) WISP_PUTONE(cPad);
			}
			savestr = str;
			while (len-- > 0) WISP_PUTONE(*str++);
			if (nPad && bLeftJustify) {
				// Right padding required
				while (nPad--) WISP_PUTONE(' ');
			}
Done:	;
		}
	}
	Output((WISP_CHAR)'\0');
	RestoreFontColor();
	CWispTerminalWnd*pCmdWnd;
	if(m_CtrlType == WISP_CTRL_CONSOLE_WND && ((CWispConsoleWnd*)this)->m_pTerminalWnd)		
		pCmdWnd = ((CWispConsoleWnd*)this)->m_pTerminalWnd;
	else
		pCmdWnd = this;
	pCmdWnd->m_CaretPos.y=pCmdWnd->m_LineList.Count();
	if(pCmdWnd->m_nLinesPerPage>0)
	{
		pCmdWnd->m_ScrPos.y=pCmdWnd->m_LineList.Count()-pCmdWnd->m_nLinesPerPage+1;
		MIN_LIMIT(pCmdWnd->m_ScrPos.y,0);
		pCmdWnd->SetScrollBarCurPos(WISP_SB_VERT,pCmdWnd->m_ScrPos.y);
	}
	m_bSelect=false;
	pCmdWnd->UpdateCaretState();
	pCmdWnd->RecalcLayout();
	pCmdWnd->Update();
	return Length;		// Don't count terminating NULL
}
