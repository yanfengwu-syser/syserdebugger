#ifndef _LANG_LIB_
#define _LANG_LIB_

typedef TMap<CIStrW,CIStrW>	CStrMap;


class CLangLib
{
public:
	CLangLib();
	CStrMap	m_StrMap;
	bool	Load(PCSTR szFileName);
	PCWSTR	GetString(PCWSTR szStr,bool bDefault=true);
	static	XSCAN_RES ScanLang(CFileIO*pFileIO,PCSTR FileName,ULSIZE FileSize,void*CBParam);
	int		ListLang(PCSTR PathName,TList<CStrA>*pLangList);
};


#endif
