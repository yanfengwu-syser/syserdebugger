#include "StdAfx.h"
#include "LogFile.h"
#include "StrMem.h"

NAME_SPACE_BEGIN
//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////
bool CLogFile::CreateNew(PCSTR Filename)
{
	CHAR LogFileName[MAX_FN_LEN];
	m_BufLen=0;
	m_TickCount=0;
	TStrCpy(LogFileName,Filename);
	return Create(LogFileName,0);
}

bool CLogFile::CreateConsole()
{
#ifdef CODE_OS_WIN
	AllocConsole();
	m_hFile=GetStdHandle(STD_OUTPUT_HANDLE);
	return m_hFile!= INVALID_HANDLE_VALUE;
#else
	return false;
#endif
}

CLogFile& CLogFile::operator <<(PCSTR LogStr)
{
	Record(LogStr);
	return *this;
}

CLogFile& CLogFile::operator <<(PCWSTR LogStr)
{
	CHAR szBuffer[0x400],*pStr;
	int Len;
	Len=(int)TStrLen(LogStr);
	if(Len>=sizeof(szBuffer))
		pStr=new CHAR[Len+1];
	else
		pStr=szBuffer;
	TStrCpy(pStr,LogStr);
	Record(pStr);
	if(pStr!=szBuffer)
		delete pStr;
	return *this;
}

CLogFile& CLogFile::operator <<(LONG Hex)
{
	CHAR szBuffer[32];
	szBuffer[0]='0';
	szBuffer[1]='x';
	uNumToStr(Hex,&szBuffer[2]);
	Record(szBuffer);
	return *this;
}

CLogFile& CLogFile::operator <<(INT Hex)
{
	CHAR szBuffer[32];
	szBuffer[0]='0';
	szBuffer[1]='x';
	uNumToStr(Hex,&szBuffer[2]);
	Record(szBuffer);
	return *this;
}

CLogFile& CLogFile::operator <<(CHAR Hex)
{
	CHAR szBuffer[32];
	szBuffer[0]='0';
	szBuffer[1]='x';
	uNumToStr(Hex,&szBuffer[2]);
	Record(szBuffer);
	return *this;
}

CLogFile& CLogFile::operator <<(DWORD Hex)
{
	CHAR szBuffer[32];
	szBuffer[0]='0';
	szBuffer[1]='x';
	uNumToStr(Hex,&szBuffer[2]);
	Record(szBuffer);
	return *this;
}

CLogFile& CLogFile::operator <<(WORD Hex)
{
	CHAR szBuffer[32];
	szBuffer[0]='0';
	szBuffer[1]='x';
	uNumToStr(Hex,&szBuffer[2]);
	Record(szBuffer);
	return *this;
}

CLogFile& CLogFile::operator <<(BYTE Hex)
{
	CHAR szBuffer[32];
	szBuffer[0]='0';
	szBuffer[1]='x';
	uNumToStr(Hex,&szBuffer[2]);
	Record(szBuffer);
	return *this;
}

CLogFile& CLogFile::operator ++(int)
{
	Record("\r\n");
	return *this;
}

bool CLogFile::Record(PCSTR LogString)
{
	int Strlen;
	Strlen=TStrLen(LogString);
	if(m_BufLen+Strlen>=LOG_BUFFER_SIZE)
	{
		if(m_BufLen)
		{
			WriteFile(m_Buffer,m_BufLen);
			m_BufLen=0;
		}
		else
		{
			return WriteFile((LPVOID)LogString,Strlen);
		}
	}
	TStrCpy(&m_Buffer[m_BufLen],LogString);
	m_BufLen+=Strlen;
	return true;
}

void CLogFile::Close()
{
	m_Timer.Clear();
	if(m_BufLen)
	{
		WriteFile(m_Buffer,m_BufLen);
		m_BufLen=0;
	}
	CImageFile::Close();
}

bool CLogFile::EnterTimer(DWORD ID)
{
	UpdateTickCount(&m_TickCount);
	m_Timer.InsertUnique(ID,m_TickCount);
	return true;
}

bool CLogFile::ExitTimer(DWORD ID,PCSTR FormatStr)
{
	CHAR szBuffer[256];
	CLogTimer::IT Iter=m_Timer.Find(ID);
	if(Iter==m_Timer.End())
		return false;
	UpdateTickCount(&m_TickCount);
	TSPrintf(szBuffer,FormatStr,(void*)(m_TickCount - *Iter));
	Record(szBuffer);
	m_Timer.Remove(Iter);
	return true;
}


int CLogFile::Printf(PCSTR szMsg,...)
{
	int Length;
	char szBuffer[0x400];
	va_list Next;
	va_start(Next,szMsg);
	Length = TVSPrintf(szBuffer,szMsg,Next);
	va_end(Next);
	Record(szBuffer);
	return Length;
}

int CLogFile::Printf(PCWSTR szMsg,...)
{
	int Length;
	WCHAR wszBuffer[0x400];
	char szBuffer[0x400];
	va_list Next;
	va_start(Next,szMsg);
	Length = TVSPrintf(wszBuffer,szMsg,Next);
	va_end(Next);
	UnicodeToAnsi(wszBuffer,szBuffer,sizeof(szBuffer));
	Record(szBuffer);
	return Length;
}

NAME_SPACE_END
