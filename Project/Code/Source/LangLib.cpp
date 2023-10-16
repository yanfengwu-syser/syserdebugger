#include "StdAfx.h"
#include "LangLib.h"

CLangLib::CLangLib()
{

}

bool CLangLib::Load(PCSTR szFileName)
{
	PCWSTR szStr,szLang;
	CUTXTFile File;
	m_StrMap.Clear();
	if(File.Open(szFileName)==false)
		return false;
	TTXTStrWList::IT LineIter=File.m_StrList.Begin();
	while(LineIter!=File.m_StrList.End())
	{
		szStr = *LineIter;
		LineIter++;
		if(*szStr==0)
			continue;
		if(LineIter==File.m_StrList.End())
			break;

		szLang = *LineIter;
		if(*szLang==0)
		{
			LineIter++;
			continue;
		}
		m_StrMap.InsertUnique(szStr,szLang);
		LineIter++;
	}
	File.Close();
	return true;
}

PCWSTR CLangLib::GetString(PCWSTR szStr,bool bDefault)
{
	CStrMap::IT Iter = m_StrMap.Find(szStr);
	if(Iter.IsExist())
		return *Iter;
	if(bDefault)
		return szStr;
	return NULL;
}

XSCAN_RES CLangLib::ScanLang(CFileIO*pFileIO,PCSTR FileName,ULSIZE FileSize,void*CBParam)
{
	TList<CStrA>*pLangList=(TList<CStrA>*)CBParam;
	char szFileTitle[MAX_FN_LEN];
	TGetFileTitle(FileName,szFileTitle);
	pLangList->Append(szFileTitle);
	return XSCAN_RES_CONTINUE;
}

int CLangLib::ListLang(PCSTR PathName,TList<CStrA>*pLangList)
{
	pLangList->Clear();
	gpFileIO->XScan(PathName,ScanLang,pLangList);
	return pLangList->Count();
}