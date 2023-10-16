#ifndef	_FILE_IO_H_
#define	_FILE_IO_H_

NAME_SPACE_BEGIN

#define FIO_READ			0x00000000
#define FIO_WRITE			0x00000001
#define FIO_NEW				0x00000000
#define FIO_CREATE			0x00000001
#define FIO_SHARE_READ		0x00010000
#define FIO_SHARE_WRITE		0x00020000

#define FIO_FA_NORMAL		0x00000000
#define FIO_FA_READONLY		0x00000001
#define FIO_FA_HIDDEN		0x00000002
#define FIO_FA_SYSTEM		0x00000004
#define FIO_FA_DIR			0x00000010
#define FIO_FA_COMPRESS		0x00000020
#define FIO_FA_SYM_LINK		0x00000040
#define FIO_FA_NON_REG		0x80000000
#define FIO_FA_ERROR		0xFFFFFFFF


#define FIO_ERROR_FILE_PTR	((ULLPOS)-1)

struct FILE_FIND_DATA
{
	char	FileName[MAX_FN_LEN];
	DWORD	FileAttribute;
	HANDLE	hFindFile;
	void*	FindDataBuffer;
	ULLSIZE	FileLength;
};

enum XCOPY_RES
{
	XCOPY_RES_COPY,
	XCOPY_RES_IGNORE,
	XCOPY_RES_BREAK,
};

enum XSCAN_RES
{
	XSCAN_RES_CONTINUE,
	XSCAN_RES_BREAK,
	XSCAN_RES_IGNORE,
};

class CFileIO;
typedef XCOPY_RES (*FUNC_XCOPY_CB)(CFileIO*pSrcIO,CFileIO*pDesIO,PCSTR SrcFileName,PCSTR DesFileName,ULSIZE FileSize,void*CBParam);
typedef XSCAN_RES (*FUNC_XSCAN_CB)(CFileIO*pFileIO,PCSTR FileName,ULSIZE FileSize,void*CBParam);

class CFileIO
{
public:
	char*	m_pszSepar;
	CFileIO();
	virtual bool	OpenFile(IN PCSTR FileName,OUT HANDLE*phFile,IN DWORD Mode = FIO_READ | FIO_SHARE_READ);
	virtual bool	CreateFile(IN PCSTR FileName,OUT HANDLE*phFile,IN DWORD Mode = FIO_CREATE | FIO_SHARE_READ);
	virtual bool	CreateDir(IN PCSTR FileName);
	virtual bool	CloseHandle(IN HANDLE hFile);
	virtual ULSIZE	ReadFile(IN HANDLE hFile,IN void* Buffer,IN ULSIZE Size,IN ULLPOS Offset);
	virtual ULSIZE	WriteFile(IN HANDLE hFile,IN const void* Buffer,IN ULSIZE Size,IN ULLPOS Offset);

	virtual ULSIZE	ReadFile(IN HANDLE hFile,IN void* Buffer,IN ULSIZE Size);
	virtual ULSIZE	WriteFile(IN HANDLE hFile,IN const void* Buffer,IN ULSIZE Size);
	virtual ULLPOS	SetFilePointer(IN HANDLE hFile,IN LLPOS Offset,IN DWORD Pos);

	virtual ULLSIZE	GetFileLength(IN HANDLE hFile);
	virtual bool	SetFileLength(IN HANDLE hFile,IN ULLSIZE Length);

	virtual bool	DeleteFile(IN PCSTR FileName);
	virtual bool	RenameFile(IN PCSTR FileName,IN PCSTR NewFileName);
	virtual	bool	GetFileTime(IN PCSTR FileName,IN ULONGLONG*pModifyTime=NULL,IN ULONGLONG*pCreateTime=NULL,IN ULONGLONG*pAccessTime=NULL);
	virtual bool	IsDir(IN PCSTR FileName);
	virtual bool	DeleteDir(IN PCSTR FileName);
	virtual bool	SetFileAttr(IN PCSTR FileName,DWORD Attr);
	virtual DWORD	GetFileAttr(IN PCSTR FileName);
	virtual bool	FindFirstFile(IN PCSTR DirName,OUT FILE_FIND_DATA*pFindData);
	virtual bool	FindNextFile(INOUT FILE_FIND_DATA*pFindData);
	virtual bool	FindClose(IN FILE_FIND_DATA*pFindData);
	virtual void	FlushFileBuffer(IN HANDLE hFile);
public:
	virtual bool	WriteToFile(IN PCSTR Filename,IN const void* Buffer,IN ULSIZE BufSize);
	virtual ULSIZE	ReadFromFile(IN PCSTR Filename,IN void* Buffer,IN ULSIZE BufSize = 0);
	virtual ULLSIZE	GetFileSize(IN PCSTR Filename);
	virtual bool	IsFileExist(IN PCSTR FileName);
	virtual bool	IsDirEmpty(IN PCSTR FileName);
	virtual bool	DeleteDirTree(IN PCSTR FileName);
	virtual bool	XDelete(IN PCSTR FileName);
	virtual int		XScan(PCSTR DirName,FUNC_XSCAN_CB pfnCallBack,void*CBParam = NULL,bool Recursive = true,XSCAN_RES*pRes=NULL);
	static	bool	XCopy(CFileIO*pSrcIO,CFileIO*pDesIO,PCSTR SrcFileName,PCSTR DesFileName,FUNC_XCOPY_CB pfnCallBack=NULL,void*CBParam = NULL);
};

NAME_SPACE_END

#ifdef	CODE_OS_WIN
#include "FileIOWin32.h"
#endif

#ifdef	CODE_OS_UNIX
#include "FileIOUnix.h"
#endif

#ifdef	CODE_OS_NT_DRV
#include "FileIONTDrv.h"
#endif

#endif

