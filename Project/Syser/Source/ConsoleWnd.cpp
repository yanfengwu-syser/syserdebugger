#include "StdAfx.h"
#include "Syser.h"
#include "SyserCmd.h"
#include "DebugCmd.h"
#include "OtherCmd.h"
#include "ShareCmd.h"
#include "SyserOption.h"

#define SYSER_VALIDATE_SN

WISP_MSG_MAP_BEGIN (CConsoleWnd)
	WISP_MSG_MAP(WISP_WM_CREATE,OnCreate)
	WISP_MSG_MAP(WISP_WM_KEY_EVENT,OnKeyEvent)
WISP_MSG_MAP_END(CWispConsoleWnd)

CConsoleWnd::CConsoleWnd()
{
	m_IsInBatProcess = false;
	m_Radix = 16;
	m_CDTColor[CDT_VADDR] = SC_LIGHT_GREEN;
	m_CDTColor[CDT_PADDR] = SC_LIGHT_BLUE;
	m_CDTColor[CDT_STRING] = SC_LIGHT_YELLOW;
	m_CDTColor[CDT_SYMBOL] = SC_LIGHT_YELLOW;
	m_CDTColor[CDT_HEX_NUM] = SC_WHITE;
	m_CDTColor[CDT_DEC_NUM] = SC_WHITE;
}


CConsoleWnd& CConsoleWnd::operator <<(CON_DATA_TYPE Type)
{
	SetFontColor((BYTE)Type);
	return *this;
}

CConsoleWnd& CConsoleWnd::operator <<(BYTE Num8)
{
	WCHAR szBuffer[32];
	TSPrintf(szBuffer,WSTR("%02X"),Num8);
	Output(szBuffer);
	return *this;
}

CConsoleWnd& CConsoleWnd::operator <<(WORD Num16)
{
	WCHAR szBuffer[32];
	TSPrintf(szBuffer,WSTR("%04X"),Num16);
	Output(szBuffer);
	return *this;
}

CConsoleWnd& CConsoleWnd::operator <<(DWORD Num32)
{
	WCHAR szBuffer[32];
	TSPrintf(szBuffer,WSTR("%08X"),Num32);
	Output(szBuffer);
	return *this;
}

CConsoleWnd& CConsoleWnd::operator <<(QWORD Num64)
{
	WCHAR szBuffer[32];
	TSPrintf(szBuffer,WSTR("%I64X"),Num64);
	Output(szBuffer);
	return *this;
}

CConsoleWnd& CConsoleWnd::operator <<(const WCHAR*String)
{
	Output(String);
	return *this;
}

bool CConsoleWnd::OnCreate(IN WISP_MSG*pMsg)
{
	for(int n=0;DebugCmdTable[n].CmdStr;n++)
	{
		InsertCmd(DebugCmdTable[n].CmdStr,(CMDPROC)DebugCmdTable[n].CmdProc,gpSyser,DebugCmdTable[n].CmdCmt,DebugCmdTable[n].CmdUsage);
	}
	for(int n=0;OtherCmdTable[n].CmdStr;n++)
	{
		InsertCmd(OtherCmdTable[n].CmdStr,(CMDPROC)OtherCmdTable[n].CmdProc,gpSyser,OtherCmdTable[n].CmdCmt,OtherCmdTable[n].CmdUsage);
	}
	for(int n=0;ShareCmdTable[n].CmdStr;n++)
	{
		InsertCmd(ShareCmdTable[n].CmdStr,(CMDPROC)ShareCmdTable[n].CmdProc,gpSyser,ShareCmdTable[n].CmdCmt,ShareCmdTable[n].CmdUsage);
	}
#ifdef CODE_OS_NT_DRV
	for(int n=0;SysCmdTable[n].CmdStr;n++)
	{
		InsertCmd(SysCmdTable[n].CmdStr,(CMDPROC)SysCmdTable[n].CmdProc,gpSyser,SysCmdTable[n].CmdCmt,SysCmdTable[n].CmdUsage);
	}
#endif
	m_Option.RegisterValueAry(SyserOptVal);
	SetHistoryLines(SyserOption.iHistroyLines);
	return true;
}

bool CConsoleWnd::OnKeyEvent(IN WISP_MSG*pMsg)
{
	int Length,NewLength;
	CHAR szBuffer[MAX_SYMBOL_LEN];
	WCHAR wszBuffer[MAX_SYMBOL_LEN];
	WISP_PSTR pStr;
	if(pMsg->KeyEvent.KeyType == WISP_VK_TAB && pMsg->KeyEvent.bKeyDown)
	{
		pStr = TStrRChr((WISP_PCSTR)m_InputStr,(WCHAR)' ');
		if(pStr && TStrLen(pStr)>2)
		{
			Length = TStrCpy(szBuffer,&pStr[1]);
			NewLength = gpSyser->m_SyserUI.GetFullSymbol(szBuffer);
			if(NewLength>Length)
			{
				m_InputStr.Truncate((int)(pStr-m_InputStr.m_pData)+1);
				AnsiToUnicode(szBuffer,wszBuffer,MAX_SYMBOL_LEN);
				m_InputStr+=wszBuffer;
				m_CaretPos.x = m_InputStr.Length();
			}
		}
	}
	return true;
}

void CConsoleWnd::BatBeginNodify(WISP_PCSTR szCmd)
{
	m_IsInBatProcess = true;
}

void CConsoleWnd::BatEndNodify(WISP_PCSTR szCmd)
{
	m_IsInBatProcess = false;
}

void CConsoleWnd::AfterRunCmdNotify(const CMD_CHAR*szCmd)
{
#ifdef CODE_OS_NT_DRV
#ifdef SYSER_VALIDATE_SN
	if(gpSyser->m_SysInfo.m_bSNPass==false && gpSyser->m_SysInfo.m_bEvlVer==false)
	{
		OUTPUT(WSTR("%<3>%s\n"),(PCWSTR)gpSyser->m_SysInfo.m_LicTip);
	}
#endif
#endif
}

WISP_MSG_MAP_BEGIN (CTerminalWnd)
	WISP_MSG_MAP(WISP_WM_KEY_EVENT,OnKeyEvent)
WISP_MSG_MAP_END(CWispTerminalWnd)

bool CTerminalWnd::OnKeyEvent(IN WISP_MSG*pMsg)
{
	int Length,NewLength;
	CHAR szBuffer[MAX_SYMBOL_LEN];
	WCHAR wszBuffer[MAX_SYMBOL_LEN];
	WISP_PSTR pStr;
	if(pMsg->KeyEvent.KeyType == WISP_VK_TAB && pMsg->KeyEvent.bKeyDown)
	{
		pStr = TStrRChr((WISP_PCSTR)m_InputStr,(WCHAR)' ');
		if(pStr && TStrLen(pStr)>2)
		{
			Length = TStrCpy(szBuffer,&pStr[1]);
			NewLength = gpSyser->m_SyserUI.GetFullSymbol(szBuffer);
			if(NewLength>Length)
			{
				m_InputStr.Truncate((int)(pStr-m_InputStr.m_pData)+1);
				AnsiToUnicode(szBuffer,wszBuffer,MAX_SYMBOL_LEN);
				m_InputStr+=wszBuffer;
				m_CaretPos.x = m_InputStr.Length();
			}
		}
	}
	return true;
}