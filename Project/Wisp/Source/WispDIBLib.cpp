#include "StdAfx.h"
#include "WispDIBLib.h"
#include "WispBase.h"


CWispDIBLib::CWispDIBLib()
{

}

CWispDIBLib::~CWispDIBLib()
{

}

CWispDIB* CWispDIBLib::LoadDIB(PCSTR FileName,int Index)
{
	CHAR szFile[MAX_FN_LEN],*pStr,*pSplit;
	TStrCpy(szFile,FileName);
	pStr = TStrRChr(szFile,'\\');
	if(pStr==NULL)
		pStr = szFile;
	pSplit = TStrChr(pStr,'#');
	if(pSplit)
	{
		int Width,Height;
		if(sscanf(pSplit,"#%d#%d:%d",&Width,&Height,&Index)!=3)
			return false;
		*pSplit=0;
		return LoadDIBList(szFile,Width,Height,0,WISP_TK)->GetDIB(Index);
	}
	pSplit = TStrRChr(pStr,':');
	if(pSplit)
	{
		*pSplit=0;
		pSplit++;
		if(USDecStrToNum(pSplit,&Index)==false)
			return false;
	}
	CWispDIBMap::IT Iter=m_DIBMap.Find(FileName);
	if(Iter!=m_DIBMap.End())
	{	
		Iter->m_RefCount++;
		return &(*Iter);
	}
	Iter = m_DIBMap.InsertUnique(FileName);
	if(Iter->Load(szFile,Index)==false)
	{
		m_DIBMap.Remove(Iter);
		return NULL;
	}
	Iter->m_RefCount++;
	return &(*Iter);
}

CWispDIB* CWispDIBLib::LoadDIB(PCSTR FileName,int Index,COLORREF ColorKey)
{
	CWispDIB*pDIB = LoadDIB(FileName,Index);
	if(pDIB==NULL)
		return NULL;
	pDIB->SetColorKey(ColorKey);
	return pDIB;
}

CWispDIBList*CWispDIBLib::LoadDIBList(PCSTR FileName,int TileWidth,int TileHeight,int Count)
{
	CWispDIBListMap::IT Iter=m_DIBListMap.Find(FileName);
	if(Iter!=m_DIBListMap.End())
	{
		Iter->m_RefCount++;
		return &(*Iter);
	}
	Iter = m_DIBListMap.InsertUnique(FileName);
	if(Iter->Load(FileName,TileWidth,TileHeight,Count)==false)
	{
		m_DIBListMap.Remove(Iter);
		return NULL;
	}
	Iter->m_RefCount++;
	return &(*Iter);
}

CWispDIBList*CWispDIBLib::LoadDIBList(PCSTR FileName,int TileWidth,int TileHeight,int Count,COLORREF ColorKey)
{
	CWispDIBList*pDIBList = LoadDIBList(FileName,TileWidth,TileHeight,Count);
	if(pDIBList==NULL)
		return NULL;
	pDIBList->SetColorKey(ColorKey);
	return pDIBList;
}

CWispDIBList*CWispDIBLib::LoadIconDIBList(PCSTR FileName)
{
	CWispDIBListMap::IT Iter=m_DIBListMap.Find(FileName);
	if(Iter!=m_DIBListMap.End())
	{
		Iter->m_RefCount++;
		return &(*Iter);
	}
	Iter = m_DIBListMap.InsertUnique(FileName);
	if(Iter->LoadIcon(FileName)==false)
	{
		m_DIBListMap.Remove(Iter);
		return NULL;
	}
	Iter->m_RefCount++;
	return &(*Iter);
}

void CWispDIBLib::ReleaseDIB(PCSTR FileName)
{
	CWispDIBMap::IT Iter=m_DIBMap.Find(FileName);
	if(Iter==m_DIBMap.End())
		return;
	Iter->m_RefCount--;
	if(Iter->m_RefCount<=0)
		m_DIBMap.Remove(Iter);
}

void CWispDIBLib::DestroyDIBList(PCSTR FileName)
{
	CWispDIBListMap::IT Iter=m_DIBListMap.Find(FileName);
	if(Iter==m_DIBListMap.End())
		return;
	Iter->m_RefCount--;
	if(Iter->m_RefCount<=0)
		m_DIBListMap.Remove(Iter);
}

void CWispDIBLib::ReleaseAll()
{
	m_DIBMap.Clear();
	m_DIBListMap.Clear();
}

