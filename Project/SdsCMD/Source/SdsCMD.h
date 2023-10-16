#ifndef _SDSCMD_H_
#define _SDSCMD_H_
#include "../../SyserApp/Source/SourceDebug.h"
class CSdsCMD
{
	CSourceDebug m_SourceDebug;
public:
	CSdsCMD();
	~CSdsCMD();
	bool TranslateSymbolFile(IN PCSTR FileName,OUT PSTR SymbolFileName);
};
#endif //_SDSCMD_H_