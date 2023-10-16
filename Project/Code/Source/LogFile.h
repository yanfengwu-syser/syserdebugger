#ifndef	_LOGFILE_H_
#define _LOGFILE_H_

#include "ImageFile.h"
#include "SysDep.h"

NAME_SPACE_BEGIN

#define LOG_BUFFER_SIZE		0x1000

typedef TMap<DWORD,ULONGLONG> CLogTimer;

class CLogFile : CImageFile
{
public:
	CHAR  m_Buffer[LOG_BUFFER_SIZE];
	int   m_BufLen;
	DWORD m_CurLine;
	DWORD m_MaxLine;
	HANDLE m_hFile;
	bool CreateNew(PCSTR Filename);
	bool CreateConsole();
	CLogFile& operator <<(PCSTR LogStr);
	CLogFile& operator <<(PCWSTR LogStr);
	CLogFile& operator <<(LONG Hex);
	CLogFile& operator <<(INT Hex);
	CLogFile& operator <<(CHAR Hex);
	CLogFile& operator <<(DWORD Hex);
	CLogFile& operator <<(WORD Hex);
	CLogFile& operator <<(BYTE Hex);
	CLogFile& operator ++(int);
	int		Printf(PCSTR szMsg,...);
	int		Printf(PCWSTR szMsg,...);
	bool	Record(PCSTR LogString);
	void	Close();
	bool	EnterTimer(DWORD ID);
	bool	ExitTimer(DWORD ID,PCSTR FormatStr = "%d (ms)");
	CLogTimer m_Timer;
	ULONGLONG m_TickCount;
};

NAME_SPACE_END

#endif


