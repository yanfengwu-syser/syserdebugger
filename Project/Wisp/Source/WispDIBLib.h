#ifndef _WISP_DIB_LIB_H_
#define _WISP_DIB_LIB_H_

#include "WispDIB.h"

typedef TMap<CStrA,CWispDIB>			CWispDIBMap;
typedef TMap<CStrA,CWispDIBList>		CWispDIBListMap;

class CWispDIBLib
{
	CWispDIBMap		m_DIBMap;
	CWispDIBListMap	m_DIBListMap;
public:
	CWispDIBLib();
	~CWispDIBLib();
public:
	CWispDIB*		LoadDIB(PCSTR FileName,int Index = -1);
	CWispDIB*		LoadDIB(PCSTR FileName,int Index,COLORREF ColorKey);
	CWispDIBList*	LoadDIBList(PCSTR FileName,int TileWidth,int TileHeight,int Count);
	CWispDIBList*	LoadDIBList(PCSTR FileName,int TileWidth,int TileHeight,int Count,COLORREF ColorKey);
	CWispDIBList*	LoadIconDIBList(PCSTR FileName);
	void	ReleaseDIB(PCSTR FileName);
	void	DestroyDIBList(PCSTR FileName);
	void	ReleaseAll();
};

#endif
