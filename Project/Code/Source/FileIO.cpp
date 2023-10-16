#include "StdAfx.h"
#include "FileIO.h"

NAME_SPACE_BEGIN

CFileIO::CFileIO()
{
	m_pszSepar=PATH_SEPARATOR_STR;
}

bool CFileIO::OpenFile(IN PCSTR FileName,OUT HANDLE*phFile,IN DWORD Mode)
{
	return false;
}

bool CFileIO::CreateFile(IN PCSTR FileName,OUT HANDLE*phFile,IN DWORD Mode)
{
	return false;
}

bool CFileIO::CreateDir(IN PCSTR FileName)
{
	return false;
}

bool CFileIO::CloseHandle(IN HANDLE hFile)
{
	return false;
}

ULSIZE CFileIO::ReadFile(IN HANDLE hFile,IN void* Buffer,IN ULSIZE Size,IN ULLPOS Offset)
{
	return 0;
}

ULSIZE CFileIO::WriteFile(IN HANDLE hFile,IN const void* Buffer,IN ULSIZE Size,IN ULLPOS Offset)
{
	return 0;
}

ULSIZE CFileIO::ReadFile(IN HANDLE hFile,IN void* Buffer,IN ULSIZE Size)
{
	return 0;
}

ULSIZE CFileIO::WriteFile(IN HANDLE hFile,IN const void* Buffer,IN ULSIZE Size)
{
	return 0;
}

ULLPOS CFileIO::SetFilePointer(IN HANDLE hFile,IN LLPOS Offset,IN DWORD Pos)
{
	return 0;
}

ULLSIZE CFileIO::GetFileLength(IN HANDLE hFile)
{
	return 0;
}

bool CFileIO::SetFileLength(IN HANDLE hFile,IN ULLSIZE Length)
{
	return false;
}

bool CFileIO::DeleteFile(IN PCSTR FileName)
{
	return false;
}

bool CFileIO::RenameFile(IN PCSTR FileName,IN PCSTR NewFileName)
{
	return false;
}

bool CFileIO::IsDir(IN PCSTR FileName)
{
	return false;
}

bool CFileIO::DeleteDir(IN PCSTR FileName)
{
	return false;
}

bool CFileIO::SetFileAttr(IN PCSTR FileName,DWORD Attr)
{
	return false;
}

DWORD CFileIO::GetFileAttr(IN PCSTR FileName)
{
	return FIO_FA_ERROR;
}

bool CFileIO::FindFirstFile(IN PCSTR DirName,OUT FILE_FIND_DATA*pFindData)
{
	*pFindData->FileName=0;
	return false;
}

bool CFileIO::FindNextFile(INOUT FILE_FIND_DATA*pFindData)
{
	*pFindData->FileName=0;
	return false;
}

bool CFileIO::FindClose(IN FILE_FIND_DATA*pFindData)
{
	*pFindData->FileName=0;
	return false;
}

bool CFileIO::WriteToFile(IN PCSTR Filename,IN const void* Buffer,IN ULSIZE BufSize)
{
	HANDLE hFile;
	if(CreateFile(Filename,&hFile)==false)
		return false;
	WriteFile(hFile,Buffer,BufSize,0);
	CloseHandle(hFile);
	return true;
}

ULSIZE CFileIO::ReadFromFile(IN PCSTR Filename,OUT void* Buffer,IN ULSIZE BufSize)
{
	HANDLE hFile;
	ULSIZE cbRW;
	if(OpenFile(Filename,&hFile)==false)
		return false;
	if(BufSize==0)
		BufSize=(ULSIZE)GetFileLength(hFile);
	cbRW = ReadFile(hFile,Buffer,BufSize,0);
	CloseHandle(hFile);
	return cbRW;
}

ULLSIZE CFileIO::GetFileSize(IN PCSTR Filename)
{
#ifdef CODE_OS_WIN
	int Len=TStrLen(Filename);
	if((Len==2 || Len==3 ) && Filename[1]==':')
	{
		ULARGE_INTEGER FreeBytesAvailable,TotalNumberOfBytes,TotalNumberOfFreeBytes;
		FreeBytesAvailable.QuadPart = 0;
		TotalNumberOfBytes.QuadPart = 0;
		TotalNumberOfFreeBytes.QuadPart = 0;
		GetDiskFreeSpaceEx(Filename,&FreeBytesAvailable,&TotalNumberOfBytes,&TotalNumberOfFreeBytes);
		return TotalNumberOfBytes.QuadPart;
	}
#endif
	HANDLE hFile;
	ULLSIZE Result;
	if(OpenFile(Filename,&hFile)==false)
		return (ULLSIZE)-1;
	Result=GetFileLength(hFile);
	CloseHandle(hFile);
	return Result;
}

bool CFileIO::GetFileTime(IN PCSTR FileName,IN ULONGLONG*pModifyTime,IN ULONGLONG*pCreateTime,IN ULONGLONG*pAccessTime)
{
	return false;
}

bool CFileIO::IsFileExist(IN PCSTR FileName)
{
	HANDLE hFile;
	if(OpenFile(FileName,&hFile)==false)
		return false;	
	return CloseHandle(hFile);
}
bool CFileIO::IsDirEmpty(IN PCSTR FileName)
{
	return false;
}
bool CFileIO::DeleteDirTree(IN PCSTR FileName)
{
	FILE_FIND_DATA FindData;
	bool bFind = FindFirstFile(FileName,&FindData);
	while(bFind)
	{
		if(FindData.FileAttribute & FIO_FA_DIR)
		{
			if(DeleteDirTree(FileName)==false)
				return false;
		}
		else
		{
			DeleteFile(FileName);
		}
		bFind = FindNextFile(&FindData);
	}
	return true;
}

bool CFileIO::XDelete(IN PCSTR FileName)
{
	if(IsDir(FileName))
		return DeleteDirTree(FileName);
	else
		return DeleteFile(FileName);
}

bool CFileIO::XCopy(CFileIO*pSrcIO,CFileIO*pDesIO,PCSTR SrcFileName,PCSTR DesFileName,FUNC_XCOPY_CB pfnCallBack,void*CBParam)
{
	int Length;
	if(pSrcIO->IsDir(SrcFileName))
	{
		if(pDesIO->IsDir(DesFileName)==false && pDesIO->CreateDir(DesFileName)==false)
			return false;
		FILE_FIND_DATA FindData;
		if(pSrcIO->FindFirstFile(SrcFileName,&FindData)==false)
			return true;
		do
		{
			if(	(FindData.FileName[0]=='.' && FindData.FileName[1]==0) ||
				(FindData.FileName[0]=='.' && FindData.FileName[1]=='.' && FindData.FileName[2]==0) )
				continue;
			char szSrcBuffer[MAX_FN_LEN],szDesBuffer[MAX_FN_LEN];
			Length = TStrCpy(szSrcBuffer,SrcFileName);
			if(Length && szSrcBuffer[Length-1] != *pSrcIO->m_pszSepar)
				TStrCat(szSrcBuffer,pSrcIO->m_pszSepar);
			TStrCat(szSrcBuffer,FindData.FileName);

			Length = TStrCpy(szDesBuffer,DesFileName);
			if(Length && szDesBuffer[Length-1] != *pDesIO->m_pszSepar)
				TStrCat(szDesBuffer,pDesIO->m_pszSepar);
			TStrCat(szDesBuffer,FindData.FileName);

			if(XCopy(pSrcIO,pDesIO,szSrcBuffer,szDesBuffer,pfnCallBack,CBParam)==false)
				break;
		}while(pSrcIO->FindNextFile(&FindData));
		pSrcIO->FindClose(&FindData);
	}
	else
	{
		ULSIZE Size = (ULSIZE)pSrcIO->GetFileSize(SrcFileName);
		if(pfnCallBack)
		{
			switch(pfnCallBack(pSrcIO,pDesIO,SrcFileName,DesFileName,Size,CBParam))
			{
				case XCOPY_RES_COPY:
					break;
				case XCOPY_RES_IGNORE:
					return true;
				case XCOPY_RES_BREAK:
					return false;
			}
		}
		BYTE*Buffer = new BYTE[Size];
		pSrcIO->ReadFromFile(SrcFileName,Buffer);
		pDesIO->WriteToFile(DesFileName,Buffer,Size);
		delete Buffer;
	}
	return true;
}

void CFileIO::FlushFileBuffer(IN HANDLE hFile)
{

}

int CFileIO::XScan(PCSTR DirName,FUNC_XSCAN_CB pfnCallBack,void*CBParam,bool Recursive,XSCAN_RES*pRes)
{
	XSCAN_RES Res;
	int Count,Length;
	FILE_FIND_DATA FindData;
	char *pFileName,szDirName[MAX_FN_LEN],szSrcBuffer[MAX_FN_LEN],szPattern[MAX_FN_LEN];
	Count = 0;

	if(pRes==NULL)
	{
		pRes = &Res;
		Res = XSCAN_RES_CONTINUE;
	}

	pFileName = TGetFileName(DirName);
	if(TStrChr(pFileName,'*')==NULL && TStrChr(pFileName,'?')==NULL)
	{
		*szPattern=0;
		if(IsDir(DirName)==false && IsFileExist(DirName))
		{
			if(pfnCallBack(this,DirName,(ULSIZE)GetFileSize(DirName),CBParam)==XSCAN_RES_CONTINUE)
				Count++;
			return Count;
		}
	}
	else
	{
		TStrCpy(szPattern,TGetFileName(DirName));
		TGetFilePath(DirName,szDirName);
		DirName = szDirName;
	}
	if(FindFirstFile(DirName,&FindData)==false)
		return Count;
	do
	{
		if(	(FindData.FileName[0]=='.' && FindData.FileName[1]==0) ||
			(FindData.FileName[0]=='.' && FindData.FileName[1]=='.' && FindData.FileName[2]==0) )
			continue;
		Length = TStrCpy(szSrcBuffer,szDirName);
		if(Length && szSrcBuffer[Length-1] != *m_pszSepar)
			TStrCat(szSrcBuffer,m_pszSepar);
		TStrCat(szSrcBuffer,FindData.FileName);
		if( (FindData.FileAttribute&FIO_FA_DIR) && (FindData.FileAttribute&FIO_FA_SYM_LINK)==0)
		{
			if(Recursive)
			{
				if(*szPattern)
				{
					TStrCat(szSrcBuffer,"\\");
					TStrCat(szSrcBuffer,szPattern);
				}
				Count+=XScan(szSrcBuffer,pfnCallBack,CBParam,Recursive,pRes);
				if(*pRes!=XSCAN_RES_CONTINUE)
					break;
			}
		}
		else
		{
			if((FindData.FileAttribute&FIO_FA_NON_REG)==0)
			{
				if(*szPattern==0 || TIMultiMatchWithPattern(szPattern,szSrcBuffer))
				{
					XSCAN_RES Result = pfnCallBack(this,szSrcBuffer,(ULSIZE)FindData.FileLength,CBParam);
					if(Result==XSCAN_RES_BREAK)
					{
						*pRes=XSCAN_RES_BREAK;
						break;
					}
					if(Result==XSCAN_RES_CONTINUE)
						Count++;
				}
			}
		}
	}while(FindNextFile(&FindData));
	FindClose(&FindData);
	return Count;
}

NAME_SPACE_END


