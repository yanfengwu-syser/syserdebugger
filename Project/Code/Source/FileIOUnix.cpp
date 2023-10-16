#include "StdAfx.h"
#include "FileIO.h"

NAME_SPACE_BEGIN

bool CLocalFileIO::OpenFile(IN PCSTR FileName,INOUT HANDLE*phFile,IN DWORD Mode)
{
	PSTR ModeStr;
	ModeStr="r";
	if(Mode&FIO_WRITE)
		ModeStr="r+";
	*(FILE**)phFile=fopen(FileName,ModeStr);
	return *phFile!=NULL;
}

bool CLocalFileIO::CreateFile(IN PCSTR FileName,INOUT HANDLE*phFile,IN DWORD Mode)
{
	PSTR ModeStr;
	ModeStr="w+";
	if((Mode&FIO_CREATE)==0)
	{
		if(OpenFile(FileName,phFile,FIO_WRITE))
		{
			CloseHandle(*phFile);
			return false;
		}
		return true;
	}
	*(FILE**)phFile=fopen(FileName,ModeStr);
	return *phFile!=NULL;
}

bool CLocalFileIO::CloseHandle(HANDLE hFile)
{
	return fclose((FILE*)hFile)==0;
}

ULSIZE CLocalFileIO::ReadFile(HANDLE hFile,void* Buffer,ULONG Size,ULLPOS Offset)
{
	if(fseek((FILE*)hFile,Offset,SEEK_SET))
		return 0;
	return (ULONG)fread(Buffer,1,Size,(FILE*)hFile);
}

ULSIZE CLocalFileIO::WriteFile(HANDLE hFile,const void* Buffer,ULSIZE Size,ULLPOS Offset)
{
	if(fseek((FILE*)hFile,Offset,SEEK_SET))
		return 0;
	return (ULSIZE)fwrite(Buffer,1,Size,(FILE*)hFile);
}

ULSIZE CLocalFileIO::ReadFile(IN HANDLE hFile,IN void* Buffer,IN ULSIZE Size)
{
	return (ULONG)fread(Buffer,1,Size,(FILE*)hFile);
}

ULSIZE CLocalFileIO::WriteFile(IN HANDLE hFile,IN const void* Buffer,IN ULSIZE Size)
{
	return (ULSIZE)fwrite(Buffer,1,Size,(FILE*)hFile);
}

ULLPOS CLocalFileIO::SetFilePointer(IN HANDLE hFile,IN LLPOS Offset,IN DWORD Pos)
{
	fseek((FILE*)hFile,Offset,Pos);
	return ftell((FILE*)hFile);
}

ULLSIZE CLocalFileIO::GetFileLength(HANDLE hFile)
{
	DWORD dwFileLength,dwOldFileLength;
	dwOldFileLength = dwFileLength = ftell((FILE*)hFile);
	fseek((FILE*)hFile,0,SEEK_END);
	dwFileLength=ftell((FILE*)hFile);
	fseek((FILE*)hFile,dwOldFileLength,SEEK_SET);
	return (ULLSIZE)dwFileLength;
}

bool CLocalFileIO::SetFileLength(HANDLE hFile,ULLSIZE Length)
{
	ULSIZE FileSize=GetFileLength(hFile);
	if(Length==FileSize || Length==0)
		return true;
	if(Length>FileSize)
	{
		FileSize=fseek((FILE*)hFile,Length-1,SEEK_SET);
		fputc(0,(FILE*)hFile);
		return true;
	}
#ifdef CODE_OS_UNIX
	int fd;
	fd = fileno((FILE *)hFile);
	return ftruncate(fd,Length)==0;
#else
	return false;
#endif
}

bool CLocalFileIO::IsDir(IN PCSTR FileName)
{
	struct stat st;
	int bRet = lstat(FileName,&st);
	if(bRet)
		return false;
	return S_ISDIR(st.st_mode) && S_ISLNK(st.st_mode)==0;
}

bool CLocalFileIO::DeleteDir(IN PCSTR FileName)
{
	return false;
}

bool CLocalFileIO::CreateDir(IN PCSTR FileName)
{
	return false;
}

bool CLocalFileIO::DeleteFile(PCSTR FileName)
{
	return remove(FileName)==0;
}

bool CLocalFileIO::RenameFile(IN PCSTR FileName,IN PCSTR NewFileName)
{
	return rename(FileName,NewFileName)==0;
}

bool CLocalFileIO::FindFirstFile(IN PCSTR DirName,OUT FILE_FIND_DATA*pFindData)
{
	struct dirent *pdir;
	char CurrentDirName[MAX_FN_LEN];
	struct stat st;
	char *tmpstr;
	int ret,Len;
	if(IsDir(DirName)==false)
		return false;
	pFindData->hFindFile = opendir(DirName);
	if(pFindData->hFindFile==NULL)
		return false;
	tmpstr = new char[MAX_FN_LEN];
	pFindData->FindDataBuffer = tmpstr;
	TStrCpyLimit((char*)pFindData->FindDataBuffer,DirName,MAX_FN_LEN);
	Len = TStrLen(tmpstr);
	if(tmpstr[Len-1]!='/')
		tmpstr[Len]='/', tmpstr[Len+1]=0;	
	TStrCpy(CurrentDirName,tmpstr);
	do
	{
		pdir = readdir((DIR*)pFindData->hFindFile);
		if(pdir == NULL)
		{
			delete [](char*)pFindData->FindDataBuffer;
			pFindData->FindDataBuffer=NULL;
			FindClose(pFindData);
			return false;
		}
	}while(strcmp(pdir->d_name,".") == 0 || strcmp(pdir->d_name,"..") == 0);
	TStrCpyLimit(pFindData->FileName,pdir->d_name,MAX_FN_LEN);
	TStrCat(CurrentDirName,pdir->d_name);
	pFindData->FileAttribute = lstat(CurrentDirName,&st) ? 0 : ConvertFileAttribute(st.st_mode);
	return true;
}

DWORD CLocalFileIO::ConvertFileAttribute(unsigned short st_mode)
{
	DWORD Result;
	Result = 0;
	if(S_ISDIR(st_mode))
		Result|=FIO_FA_DIR;
	if(S_ISLNK(st_mode))
		Result|=FIO_FA_SYM_LINK;
	if(S_ISREG(st_mode)==0)
		Result|=FIO_FA_NON_REG;
	return Result;
}

bool CLocalFileIO::FindNextFile(INOUT FILE_FIND_DATA*pFindData)
{
	char CurrentDirName[MAX_FN_LEN];
	struct dirent *pdir;
	struct stat st;
	pdir = readdir((DIR*)pFindData->hFindFile);
	if(pdir == NULL)
		return false;
	TStrCpyLimit(pFindData->FileName,pdir->d_name,MAX_FN_LEN);
	TStrCpyLimit(CurrentDirName,(const char *)pFindData->FindDataBuffer,MAX_FN_LEN);
	TStrCat(CurrentDirName,pdir->d_name);
	pFindData->FileAttribute = lstat(CurrentDirName,&st) ? 0 : ConvertFileAttribute(st.st_mode);
	return true;
}

bool CLocalFileIO::FindClose(IN FILE_FIND_DATA*pFindData)
{
	SafeDelete((char*)pFindData->FindDataBuffer)
	return closedir((DIR*)pFindData->hFindFile);
}

bool CLocalFileIO::IsFileExist(IN PCSTR FileName)
{
	int ret;
	struct stat st;
	ret = lstat(FileName,&st);
	if(ret != 0)
	{
		if(errno==ENOENT)
		return false;
	}
	return true;
}

bool CLocalFileIO::IsDirEmpty(IN PCSTR FileName)
{
	FILE_FIND_DATA FileFindData;
	if(FindFirstFile(FileName,&FileFindData))
	{
		FindClose(&FileFindData);
		return false;
	}
	return true;
}

DWORD CLocalFileIO::GetFileAttr(IN PCSTR FileName)
{
	int ret;
	struct stat st;
	ret = lstat(FileName,&st);
	if(ret!=0)
		return FIO_FA_ERROR;
	return ConvertFileAttribute(st.st_mode);
}

CLocalFileIO	gLocalFileIO;
CLocalFileIO*	gpFileIO = &gLocalFileIO;

NAME_SPACE_END
