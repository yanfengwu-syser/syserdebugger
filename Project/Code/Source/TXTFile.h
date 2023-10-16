#ifndef _TXT_FILE_H_
#define _TXT_FILE_H_

#include "alt/alt.hpp"
#include "ImageFile.h"

NAME_SPACE_BEGIN

typedef TList<PSTR>			TTXTStrList;

class CTXTFile : public CImageFile
{
public:
	CTXTFile();
	~CTXTFile();
	bool	Open(PCSTR FileName,HANDLE*pHandleOpen = NULL);
	bool	Open(PCSTR szTXTBuffer,ULLSIZE BufferSize);
	int		SplitLine(PCSTR Buffer,ULLSIZE BufferSize);
	bool	Save(PCSTR FileName);
	void	Close();
	bool	Insert(ULPOS nLine,ULPOS nCol,char*szBuffer);
	bool	Replace(ULPOS nLine,ULPOS nCol,char*szBuffer,ULSIZE Replen);
	TTXTStrList		m_StrList;
};

////////////////////////////////////////////////////////////////////////////////////////////

typedef TList<PWSTR>		TTXTStrWList;

class CUTXTFile : public CImageFile
{
public:
	CUTXTFile();
	~CUTXTFile();
	bool	Open(PCSTR FileName,HANDLE*pHandleOpen = NULL);
	bool	Open(PCWSTR szTXTBuffer,ULLSIZE BufferSize);
	int		SplitLine(PCWSTR Buffer,ULLSIZE BufferSize);
	bool	Save(PCSTR FileName);
	void	Close();
	bool	Insert(ULPOS nLine,ULPOS nCol,WCHAR*szBuffer);
	bool	Replace(ULPOS nLine,ULPOS nCol,WCHAR*szBuffer,ULSIZE Replen);
	TTXTStrWList	m_StrList;
};


NAME_SPACE_END

#endif
