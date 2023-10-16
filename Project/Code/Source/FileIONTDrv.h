#ifndef	_FILE_IO_NT_DRV_H_
#define	_FILE_IO_NT_DRV_H_

#define FIO_INVALID_HANDLE		INVALID_HANDLE_VALUE

VOID NTAPI ZwQueryDirectoryFileApc (IN PVOID ApcContext,IN PIO_STATUS_BLOCK IoStatusBlock,IN ULONG Reserved );
extern "C" NTSYSAPI NTSTATUS NTAPI ZwQueryDirectoryFile(IN HANDLE FileHandle,
														IN HANDLE Event ,
														IN PIO_APC_ROUTINE ApcRoutine ,
														IN PVOID ApcContext ,
														OUT PIO_STATUS_BLOCK IoStatusBlock,
														OUT PVOID FileInformation,
														IN ULONG FileInformationLength,
														IN FILE_INFORMATION_CLASS FileInformationClass,
														IN BOOLEAN ReturnSingleEntry,
														IN PUNICODE_STRING FileName ,
														IN BOOLEAN RestartScan
														);
NAME_SPACE_BEGIN
 


typedef struct _CODEFILE_NAMES_INFORMATION {
	ULONG NextEntryOffset;
	ULONG FileIndex;
	ULONG FileNameLength;
	WCHAR FileName[1];
} CODEFILE_NAMES_INFORMATION, *PCODEFILE_NAMES_INFORMATION;
typedef struct _FILE_FULL_DIRECTORY_INFORMATION { // Information Class 2
	ULONG NextEntryOffset;
	ULONG Unknown;
	LARGE_INTEGER CreationTime;
	LARGE_INTEGER LastAccessTime;
	LARGE_INTEGER LastWriteTime;
	LARGE_INTEGER ChangeTime;
	LARGE_INTEGER EndOfFile;
	LARGE_INTEGER AllocationSize;
	ULONG FileAttributes;
	ULONG FileNameLength;
	ULONG EaInformationLength;
	WCHAR FileName[1];
} FILE_FULL_DIRECTORY_INFORMATION, *PFILE_FULL_DIRECTORY_INFORMATION;

class CLocalFileIO : public CFileIO
{
public:
	bool	OpenDirectory(IN PCSTR FileName,INOUT HANDLE*phFile,IN DWORD Mode);
public:
	static	WCHAR	m_CurDirName[MAX_FN_LEN];
	//static BYTE m_FindNamesBuffer[MAX_FN_LEN*sizeof(WCHAR)+sizeof(CODEFILE_NAMES_INFORMATION)+sizeof(FILE_STANDARD_INFORMATION)];
	void	SetCurDir(IN PCWSTR DirName);
	bool	OpenFile(PUNICODE_STRING  FullImageName,OUT HANDLE*phFile,IN DWORD Mode = FIO_READ | FIO_SHARE_READ);
public:
	bool	OpenFile(IN PCSTR FileName,OUT HANDLE*phFile,IN DWORD Mode = FIO_READ | FIO_SHARE_READ);
	bool	CreateFile(IN PCSTR FileName,OUT HANDLE*phFile,IN DWORD Mode = FIO_CREATE | FIO_SHARE_READ);
	bool	CloseHandle(IN HANDLE hFile);

	ULSIZE	ReadFile(IN HANDLE hFile,IN void* Buffer,IN ULSIZE Size,IN ULLPOS Offset);
	ULSIZE	WriteFile(IN HANDLE hFile,IN const void* Buffer,IN ULSIZE Size,IN ULLPOS Offset);

	ULLSIZE	GetFileLength(IN HANDLE hFile);
	bool	SetFileLength(IN HANDLE hFile,IN ULLSIZE Length);
	bool	DeleteFile(IN PCSTR FileName);
	bool	RenameFile(IN PCSTR FileName,IN PCSTR NewFileName);
	bool	IsDir(IN HANDLE hFile);
	bool	IsDir(IN PCSTR FileName);
	bool	FindFirstFile(IN PCSTR DirName,OUT FILE_FIND_DATA*pFindData);
	bool	FindNextFile(INOUT FILE_FIND_DATA*pFindData);
	bool	FindClose(IN FILE_FIND_DATA*pFindData);
	
};

extern CLocalFileIO*gpFileIO;

NAME_SPACE_END

#endif
