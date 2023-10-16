#ifndef _POLY_FS_H_
#define _POLY_FS_H_

#include "FileIO.h"
#include "Handle.h"
#include "PageMem.h"

NAME_SPACE_BEGIN

#define PFS_ERROR_NAME_CODE		0x00FFFFFF
#define PFS_END_CLUS			0xFFFFFFFF
#define PFS_ERROR_FP			0xFFFFFFFF
#define PFS_FILE_ERROR			0x00000000
#define PFS_FILE_DIR			0x00000001
#define PFS_FILE_NORMAL			0x00000002
#define PFS_FILE_READONLY		0x00000004
#define PFS_FILE_HIDDEN			0x00000008
#define PFS_FILE_SYSTEM			0x00000010
#define PFS_FILE_COMPRESS		0x00000020


struct PFS_FILE_ENTRY
{
	DWORD	BeginClus;
	DWORD	FileSize;
	DWORD	Attribute;
	DWORD	NameCode;
	char	FileName[0x20];
};

struct PFS_HEAD
{
	char	Sign[8];		//"PFS"
	DWORD	ClusSize;
	DWORD	ClusCount;
	PFS_FILE_ENTRY	FatEntry;
	PFS_FILE_ENTRY	RootEntry;
};

struct PFS_FILE_DATA
{
	DWORD	FilePoint;
	DWORD	FileEntryFP;
	PFS_FILE_ENTRY	ThisFileEntry;
	PFS_FILE_ENTRY	ParentEntry;
};

struct PFS_FIND_DATA
{
	char	FileName[256];
	char	PattenName[256];
	PFS_FILE_ENTRY	ParentEntry;
	PFS_FILE_ENTRY	ThisFileEntry;
	DWORD	FileEntryFP;
};

#define PFS_NORMAL				0x00000000
#define PFS_WRITE_COPY			0x00000001
#define PFS_FULL_DISK_CACHE		0x00000002

class CPFSFileIO;
class CPolyFS
{
public:
	CPolyFS();
	virtual ~CPolyFS();
	friend class CPFSFileIO;
public:
	CImageFile		m_DiskImage;
	CPageMemory		m_PageMemory;
	CFileIO*		m_pFileIO;
	DWORD	m_MaxCachePageCount;
	DWORD	m_FatOff;
	DWORD	m_ClusSize;
	DWORD	m_ClusCount;
	UINT	m_Style;
	PFS_FILE_ENTRY	m_RootEntry;
	BYTE*	m_ZeroBuffer;
public:
	bool	ReadDiskFile(DWORD Pos,void*Buffer,DWORD Size);
	bool	WriteDiskFile(DWORD Pos,void*Buffer,DWORD Size);
	bool	ReadClus(DWORD Index,void*Buffer);
	bool	WriteClus(DWORD Index,void*Buffer);
	bool	ReadFatCell(DWORD Index,void*Buffer);
	bool	WriteFatCell(DWORD Index,void*Buffer);
protected:
	DWORD	FindFreeFileEntryFP(PFS_FILE_ENTRY*pParentEntry);
	DWORD	FindNextFreeClus(DWORD ClusIdx);
	bool	CreateFile(PCSTR FileName,DWORD Attr,DWORD Size,PFS_FILE_ENTRY*pParentEntry,DWORD ParenFileEntryFP);
	DWORD	ReadFile(PFS_FILE_ENTRY*pFileEntry,DWORD Offset,void*Buffer,DWORD Size);
	DWORD	WriteFile(PFS_FILE_ENTRY*pFileEntry,DWORD Offset,const void*Buffer,DWORD Size);
	bool	DeleteFileClus(DWORD BeginClus);
	DWORD	FileOffToDP(DWORD ClusIndex,DWORD Offset);
	DWORD	FileOffToClus(DWORD ClusIndex,DWORD Offset);
	bool	CmpFileName(PCSTR FilePattenName,PFS_FILE_ENTRY*pFileEntry);
public:
	void	ChangeFileIO(CFileIO*pFileIO);
	virtual bool	OpenDisk(PCSTR FileName,UINT Style = PFS_NORMAL);
	virtual void	CloseDisk();
	virtual void	InitParam();
	bool	Format(PCSTR DiskFileName,ULONG Size,DWORD ClusSize);
	bool	DeleteFile(PCSTR FullFileName);
	bool	FindFirstFile(PCSTR FullFileName,PFS_FIND_DATA*pFindData);
	bool	FindNextFile(PFS_FIND_DATA*pFindData);
	bool	CreateFile(PCSTR FullFileName,DWORD Attr,DWORD Size,PFS_FILE_DATA*pHandleData);
	bool	OpenFile(PCSTR FullFileName,PFS_FILE_DATA*pHandleData);
	DWORD	WriteFile(PFS_FILE_DATA*pHandleData,DWORD Offset,const void*Buffer,DWORD Size);
	DWORD	ReadFile(PFS_FILE_DATA*pHandleData,DWORD Offset,void*Buffer,DWORD Size);
	bool	SetFileLength(PFS_FILE_DATA*pHandleData,DWORD Length);
	bool	SetFileLength(PCSTR FullFileName,DWORD Length);
	DWORD	GetFileLength(PCSTR FullFileName);
	bool	SetFileAttribute(PCSTR FullFileName,DWORD Attr);
	DWORD	GetFileAttribute(PCSTR FullFileName);
};

#define PFS_HANDLE_FILE		0x0001

struct PFS_FILE_IO_HANDLE
{
	CPolyFS*		pDisk;
	PFS_FILE_DATA	FileData;
};

struct PFS_FILE_IO_FIND_DATA
{
	CPolyFS*		pDisk;
	PFS_FIND_DATA	FindData;
};

class CPFSFileIO : public CFileIO
{
	CHandle			m_Handle;
	TList<CPolyFS>	m_PolyFSList;
	CFileIO*		m_pFileIO;
public:
	CPFSFileIO();
	void	ChangeFileIO(CFileIO*pFileIO);

	virtual bool	OpenDisk(PCSTR FileName,UINT Style = PFS_NORMAL);
	virtual void	CloseAllDisk();

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

	virtual bool	SetFileAttr(IN PCSTR FileName,DWORD Attr);
	virtual DWORD	GetFileAttr(IN PCSTR FileName);

	virtual bool	IsDir(IN PCSTR FileName);
	virtual bool	DeleteDir(IN PCSTR FileName);
	virtual bool	FindFirstFile(IN PCSTR DirName,OUT FILE_FIND_DATA*pFindData);
	virtual bool	FindNextFile(INOUT FILE_FIND_DATA*pFindData);
	virtual bool	FindClose(IN FILE_FIND_DATA*pFindData);
};

NAME_SPACE_END

#endif

