#ifndef _SYSER_LANGUAGE_H_
#define _SYSER_LANGUAGE_H_

typedef int		(*PFN_AnsiToUnicode)(const char*szBuf,WCHAR*WszBuf,int MaxLen);
typedef int		(*PFN_UnicodeToAnsi)(const WCHAR*WszBuf,char*szBuf,int MaxLen);

struct SYSER_LANGUAGE_DEVICE_EXTENSION
{
	int						cbSize;
	PFN_AnsiToUnicode		pfnAnsiToUnicode;
	PFN_UnicodeToAnsi		pfnUnicodeToAnsi;
};

#endif
