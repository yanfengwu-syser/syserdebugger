#include "StdAfx.h"
#include "FileIO.h"

NAME_SPACE_BEGIN

bool CLocalFileIO::OpenFile(IN PCSTR FileName,OUT HANDLE*phFile,IN DWORD Mode)
{
	DWORD OpenMode,ShareMode;
	OpenMode = GENERIC_READ;
	if(Mode & FIO_WRITE)
		OpenMode |= GENERIC_WRITE;
	ShareMode = 0;
	if(Mode & FIO_SHARE_READ)
		ShareMode |= FILE_SHARE_READ;
	if(Mode & FIO_SHARE_WRITE)
		ShareMode |= FILE_SHARE_WRITE;
	*phFile = ::CreateFile(FileName,OpenMode,ShareMode,NULL,OPEN_EXISTING,0,NULL);
	return *phFile != INVALID_HANDLE_VALUE;
}

bool CLocalFileIO::CreateFile(IN PCSTR FileName,OUT HANDLE*phFile,IN DWORD Mode)
{
	DWORD ShareMode,CreateMode;
	CreateMode = CREATE_NEW;
	if(Mode & FIO_CREATE)
		CreateMode = CREATE_ALWAYS;
	ShareMode = 0;
	if(Mode & FIO_SHARE_READ)
		ShareMode |= FILE_SHARE_READ;
	if(Mode & FIO_SHARE_WRITE)
		ShareMode |= FILE_SHARE_WRITE;
	*phFile = ::CreateFile(FileName,GENERIC_READ | GENERIC_WRITE,ShareMode,NULL,CreateMode,0,NULL);
	return *phFile != INVALID_HANDLE_VALUE;
}

bool CLocalFileIO::CreateDir(IN PCSTR FileName)
{
	return ::CreateDirectory(FileName,NULL)!=0;
}

bool CLocalFileIO::CloseHandle(IN HANDLE hFile)
{
	return ::CloseHandle(hFile)!=0;
}
void CLocalFileIO::FlushFileBuffer(IN HANDLE hFile)
{
	::FlushFileBuffers(hFile);
}
ULSIZE CLocalFileIO::ReadFile(IN HANDLE hFile,OUT void* Buffer,IN ULSIZE Size,IN ULLPOS Offset)
{
	DWORD RDSize;
	if(SetFilePointer(hFile,(LLPOS)Offset,FILE_BEGIN)==FIO_ERROR_FILE_PTR)
		return 0;
	::ReadFile(hFile,Buffer,Size,&RDSize,NULL);
	return RDSize;
}

ULSIZE CLocalFileIO::WriteFile(IN HANDLE hFile,IN const void* Buffer,IN ULSIZE Size,IN ULLPOS Offset)
{
	DWORD WTSize=0;
	if(SetFilePointer(hFile,(LLPOS)Offset,FILE_BEGIN)==FIO_ERROR_FILE_PTR)
		return 0;
	::WriteFile(hFile,Buffer,Size,&WTSize,NULL);
	return WTSize;
}

ULSIZE CLocalFileIO::ReadFile(IN HANDLE hFile,IN void* Buffer,IN ULSIZE Size)
{
	DWORD RDSize=0;
	::ReadFile(hFile,Buffer,Size,&RDSize,NULL);
	return RDSize;
}

ULSIZE CLocalFileIO::WriteFile(IN HANDLE hFile,IN const void* Buffer,IN ULSIZE Size)
{
	DWORD WTSize=0;
	::WriteFile(hFile,Buffer,Size,&WTSize,NULL);
	return WTSize;
}

ULLPOS CLocalFileIO::SetFilePointer(IN HANDLE hFile,IN LLPOS Offset,IN DWORD Pos)
{
	ULLPOS NewPos;
	ULONG FilePosLow;
	LONG  FilePosHigh;
	FilePosLow = LOW_DWORD(Offset);
	FilePosHigh = HIGH_DWORD(Offset);
	FilePosLow = ::SetFilePointer(hFile,FilePosLow,&FilePosHigh,Pos);
	if(FilePosLow==INVALID_SET_FILE_POINTER)
		return FIO_ERROR_FILE_PTR;
	NewPos = MAKE_QDWORD(FilePosHigh,FilePosLow);
	return NewPos;
}

ULLSIZE CLocalFileIO::GetFileLength(IN HANDLE hFile)
{
	return ::GetFileSize(hFile,NULL);
}

bool CLocalFileIO::SetFileLength(IN HANDLE hFile,IN ULLSIZE Length)
{
	ULONG FilePosLow;
	LONG  FilePosHigh;
	FilePosLow = LOW_DWORD(Length);
	FilePosHigh = HIGH_DWORD(Length);
	if(::SetFilePointer(hFile,FilePosLow,&FilePosHigh,FILE_BEGIN)==INVALID_SET_FILE_POINTER)
		return false;
	return ::SetEndOfFile(hFile)!=0;
}

bool CLocalFileIO::DeleteFile(IN PCSTR FileName)
{
	return ::DeleteFile(FileName)!=0;
}

bool CLocalFileIO::RenameFile(IN PCSTR FileName,IN PCSTR NewFileName)
{
	return ::MoveFile(FileName,NewFileName)!=0;
}

bool CLocalFileIO::GetFileTime(IN PCSTR FileName,IN ULONGLONG*pModifyTime,IN ULONGLONG*pCreateTime,IN ULONGLONG*pAccessTime)
{
	bool Result;
	HANDLE hFile = ::CreateFile(FileName,GENERIC_READ,FILE_SHARE_READ|FILE_SHARE_WRITE,NULL,OPEN_EXISTING,0,NULL);
	if(hFile==INVALID_HANDLE_VALUE)
		return false;
	Result = ::GetFileTime(hFile,(FILETIME*)pCreateTime,(FILETIME*)pAccessTime,(FILETIME*)pModifyTime) == TRUE;
	CloseHandle(hFile);
	return Result;
}

bool CLocalFileIO::IsDir(IN PCSTR FileName)
{
	DWORD Attr;
	Attr = ::GetFileAttributes(FileName);
	if(Attr == (DWORD)-1)
		return GetDriveType(FileName)!=DRIVE_NO_ROOT_DIR;
	return (Attr & FILE_ATTRIBUTE_DIRECTORY)!=0;
}

bool CLocalFileIO::DeleteDir(IN PCSTR FileName)
{
	return ::RemoveDirectory(FileName)!=0;
}

bool CLocalFileIO::FindFirstFile(IN PCSTR DirName,OUT FILE_FIND_DATA*pFindData)
{
	char szBuffer[MAX_FN_LEN];
	DWORD Attr;
	pFindData->FindDataBuffer = (void*)new WIN32_FIND_DATA;
	TStrCpy(szBuffer,DirName);
	if(TStrChr(DirName,'*')==NULL && TStrChr(DirName,'?')==NULL)
	{
		TStrCat(szBuffer,m_pszSepar);
		TStrCat(szBuffer,"*");
	}
	pFindData->hFindFile = ::FindFirstFile(szBuffer,(LPWIN32_FIND_DATA)pFindData->FindDataBuffer);
	if(pFindData->hFindFile==INVALID_HANDLE_VALUE)
	{
		delete pFindData->FindDataBuffer;
		pFindData->FindDataBuffer=NULL;
		return false;
	}
	TStrCpy(pFindData->FileName,((LPWIN32_FIND_DATA)pFindData->FindDataBuffer)->cFileName);
	pFindData->FileAttribute = 0;
	Attr = ((LPWIN32_FIND_DATA)pFindData->FindDataBuffer)->dwFileAttributes;
	if(Attr  & FILE_ATTRIBUTE_READONLY)
		pFindData->FileAttribute|=FIO_FA_READONLY;
	if(Attr  & FILE_ATTRIBUTE_HIDDEN)
		pFindData->FileAttribute|=FIO_FA_HIDDEN;
	if(Attr  & FILE_ATTRIBUTE_SYSTEM)
		pFindData->FileAttribute|=FIO_FA_SYSTEM;
	if(Attr  & FILE_ATTRIBUTE_DIRECTORY)
		pFindData->FileAttribute|=FIO_FA_DIR;
	pFindData->FileLength =	((LPWIN32_FIND_DATA)pFindData->FindDataBuffer)->nFileSizeLow;
	return true;
}

bool CLocalFileIO::FindNextFile(INOUT FILE_FIND_DATA*pFindData)
{
	DWORD Attr;
	bool Result=::FindNextFile(pFindData->hFindFile,(LPWIN32_FIND_DATA)pFindData->FindDataBuffer)!=0;
	strcpy_s(pFindData->FileName,sizeof(pFindData->FileName),((LPWIN32_FIND_DATA)pFindData->FindDataBuffer)->cFileName);
	pFindData->FileAttribute = ((LPWIN32_FIND_DATA)pFindData->FindDataBuffer)->dwFileAttributes;
	pFindData->FileAttribute = 0;
	Attr = ((LPWIN32_FIND_DATA)pFindData->FindDataBuffer)->dwFileAttributes;
	if(Attr  & FILE_ATTRIBUTE_READONLY)
		pFindData->FileAttribute|=FIO_FA_READONLY;
	if(Attr  & FILE_ATTRIBUTE_HIDDEN)
		pFindData->FileAttribute|=FIO_FA_HIDDEN;
	if(Attr  & FILE_ATTRIBUTE_SYSTEM)
		pFindData->FileAttribute|=FIO_FA_SYSTEM;
	if(Attr  & FILE_ATTRIBUTE_DIRECTORY)
		pFindData->FileAttribute|=FIO_FA_DIR;
	pFindData->FileLength =	((LPWIN32_FIND_DATA)pFindData->FindDataBuffer)->nFileSizeLow;
	return Result;
}

bool CLocalFileIO::FindClose(IN FILE_FIND_DATA*pFindData)
{
	if(pFindData->FindDataBuffer)
		delete pFindData->FindDataBuffer;
	return ::FindClose(pFindData->hFindFile)!=0;
}

CLocalFileIO	gLocalFileIO;
CLocalFileIO*	gpFileIO = &gLocalFileIO;

NAME_SPACE_END

