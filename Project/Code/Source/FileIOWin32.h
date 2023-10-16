#ifndef	_FILE_IO_WIN32_H_
#define	_FILE_IO_WIN32_H_

#define FIO_INVALID_HANDLE		INVALID_HANDLE_VALUE

NAME_SPACE_BEGIN

class CLocalFileIO : public CFileIO
{
public:
	bool	OpenFile(IN PCSTR FileName,OUT HANDLE*phFile,IN DWORD Mode = FIO_READ | FIO_SHARE_READ);
	bool	CreateFile(IN PCSTR FileName,OUT HANDLE*phFile,IN DWORD Mode = FIO_CREATE | FIO_SHARE_READ);
	bool	CloseHandle(IN HANDLE hFile);

	ULSIZE	ReadFile(IN HANDLE hFile,IN void* Buffer,IN ULSIZE Size,IN ULLPOS Offset);
	ULSIZE	WriteFile(IN HANDLE hFile,IN const void* Buffer,IN ULSIZE Size,IN ULLPOS Offset);
	ULSIZE	ReadFile(IN HANDLE hFile,IN void* Buffer,IN ULSIZE Size);
	ULSIZE	WriteFile(IN HANDLE hFile,IN const void* Buffer,IN ULSIZE Size);

	ULLSIZE	GetFileLength(IN HANDLE hFile);
	bool	SetFileLength(IN HANDLE hFile,IN ULLSIZE Length);
	bool	DeleteFile(IN PCSTR FileName);
	bool	RenameFile(IN PCSTR FileName,IN PCSTR NewFileName);
	bool	GetFileTime(IN PCSTR FileName,IN ULONGLONG*pModifyTime=NULL,IN ULONGLONG*pCreateTime=NULL,IN ULONGLONG*pAccessTime=NULL);
	bool	IsDir(IN PCSTR FileName);
	bool	DeleteDir(IN PCSTR FileName);
	bool	CreateDir(IN PCSTR FileName);
	ULLPOS	SetFilePointer(IN HANDLE hFile,IN LLPOS Offset,IN DWORD Pos);
	bool	FindFirstFile(IN PCSTR DirName,IN FILE_FIND_DATA*pFindData);
	bool	FindNextFile(INOUT FILE_FIND_DATA*pFindData);
	bool	FindClose(IN FILE_FIND_DATA*pFindData);
	void	FlushFileBuffer(IN HANDLE hFile);
};

extern CLocalFileIO*gpFileIO;

NAME_SPACE_END

#endif

