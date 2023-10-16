#ifndef _FILE_TYPE_H_
#define _FILE_TYPE_H_


class CFileType : public CImageFile  
{
public:
	DWORD	GetFileType();
	bool	IsMaybePEUnpackSelfFile(DWORD MaxUnpackSize,bool bExcludeDll = true);
	static	bool	IsUPXFile(CPEFile*pPEFile);
};

#endif
