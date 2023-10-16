///////////////////////////////////////////////////////
//image file
//coded by Finaldoom
///////////////////////////////////////////////////////
#ifndef	_IMAGEFILE_H_
#define _IMAGEFILE_H_

#include "FileIO.h"

NAME_SPACE_BEGIN

typedef ULSIZE	(*RWProc)(ULPOS Address,void*Buffer,ULSIZE Size,void*Param);

#define MAX_FILE_OPT_SIZE				0x100000

/////////////////////////////////////////////////////////////////////////////////////////////////////
//File type define
#define	FILE_TYPE_ERROR					0x00000000
#define	FILE_TYPE_BIN					0x00000001
#define FILE_TYPE_EXECUTE				0x00000002
#define FILE_TYPE_NON_I386				0x00000004
#define FILE_TYPE_16BIT					0x00000008
#define FILE_TYPE_32BIT					0x00000010
#define FILE_TYPE_64BIT					0x00000020
#define FILE_TYPE_MEMORY_IMAGE			0x00000040
#define FILE_TYPE_MAIN_MODULE			0x00001000
#define FILE_TYPE_USER_MODULE			0x00002000
#define FILE_TYPE_KERNEL_MODULE			0x00004000
//--------------------------------------------------------------------------------------------------
#define	FILE_TYPE_MZ					(FILE_TYPE_BIN|FILE_TYPE_EXECUTE|FILE_TYPE_16BIT|0x00000100)
#define FILE_TYPE_NE					(FILE_TYPE_BIN|FILE_TYPE_EXECUTE|FILE_TYPE_16BIT|0x00000200)
#define	FILE_TYPE_PE					(FILE_TYPE_BIN|FILE_TYPE_EXECUTE|FILE_TYPE_32BIT|0x00000300)
#define FILE_TYPE_ELF					(FILE_TYPE_BIN|FILE_TYPE_EXECUTE|FILE_TYPE_32BIT|0x00000400)
////////////////////////////////////////////////////////////////////////////////////////////////////
//FILE_TYPE_PE
#define	FILE_TYPE_PE_EXE				(FILE_TYPE_PE|FILE_TYPE_MAIN_MODULE)
#define	FILE_TYPE_PE_DLL				(FILE_TYPE_PE|FILE_TYPE_USER_MODULE)
#define	FILE_TYPE_PE_SYS				(FILE_TYPE_PE|FILE_TYPE_KERNEL_MODULE)
////////////////////////////////////////////////////////////////////////////////////////////////////
//Page Attribute
#define	MP_ERROR						0xFFFFFFFF
#define	MP_MASK							0x0FFF
#define	MP_NOT_MASK						0xFFFFF000
#define	MP64_NOT_MASK					0xFFFFFFFFFFFFF000
#define	MP_SIZE							0x1000
#define	MP_FREE							0x0000
#define	MP_DIRTY						0x0001
#define	MP_READ							0x0002
#define	MP_WRITE						0x0004
#define	MP_WRITEBACK					0x0008
#define	MP_IMAGE						0x0010
#define	MP_CONST						0x0020
#define	MP_WATCH						0x1000
#define	MP_KERNEL						0x2000
#define	MP_COMMIT						0x4000
#define	MP_LOCK							0x8000
//MP_COMMIT 和 MP_DIRTY , MP_IMAGE 冲突
#define	MP_USER_ALL_ATTR				(MP_DIRTY | MP_READ | MP_WRITE)
#define	MP_KERNEL_ALL_ATTR				(MP_DIRTY | MP_READ | MP_WRITE | MP_KERNEL)
#define	MP_READWRITE					(MP_READ  | MP_WRITE)
///////////////////////////////////////////////////////////////////////////////////////////////////
#define FILE_OBJ_USER_MASK				0x0000FFFF
#define	FILE_OBJ_TYPE_NULL				0x00000000
#define	FILE_OBJ_TYPE_AUTO_DELETE		0x00010000
#define	FILE_OBJ_TYPE_OPEN_BY_HANDLE	0x00020000
#define FILE_OBJ_TYPE_OPEN_FOR_WRITE	0x00040000
//-------------------------------------------------------------------------------------------------
#define FILE_OBJ_TYPE_MEMORY_IMAGE		0x01000000	
#define FILE_OBJ_TYPE_USER_MEMORY_IMAGE	0x02000000
#define FILE_OBJ_TYPE_OS_MEMORY_IMAGE	0x04000000
#define FILE_OBJ_TYPE_MEMORY_IMAGE_MASK	(FILE_OBJ_TYPE_USER_MEMORY_IMAGE|FILE_OBJ_TYPE_OS_MEMORY_IMAGE|FILE_OBJ_TYPE_OS_MEMORY_IMAGE)
///////////////////////////////////////////////////////////////////////////////////////////////////

class CPageImage
{
public:
	CStrA		m_ImageName;
	ULSIZE		m_ImageSize;
	ULPOS		m_ImageBase;
	ULPOS		m_ImageHighBase;
	virtual bool	LoadPage(IN ULPOS Address,OUT void* Buffer)=0;
	virtual bool	SavePage(IN ULPOS Address,OUT void* Buffer){return false;}
	virtual DWORD	GetPageAttribute(IN ULPOS Address){return MP_READ;}
};

class CImageFile : public CPageImage
{
	HANDLE	m_hFile;
protected:
	RWProc	m_ReadMemory;
	RWProc	m_WriteMemory;
	void*	m_RMObj;
	void*	m_WMObj;
public:
	CImageFile();
	virtual bool	Create(IN PCSTR FileName,IN ULSIZE Size = 0);											//建立普通文件
	virtual bool	Create(IN ULSIZE Size,IN BYTE*Buffer = NULL OPTIONAL,bool bCompress = false);			//建立内存文件
	virtual bool	Open(IN PCSTR FileName,IN HANDLE*pHandleOpen = NULL OPTIONAL);
	virtual void	Close();
	virtual ULSIZE	ReadImageMemory(IN ULPOS Address,OUT void* Buffer,IN ULSIZE Size);
	virtual ULSIZE	WriteImageMemory(IN ULPOS Address,OUT void* Buffer,IN ULSIZE Size);
	virtual bool	LoadPage(IN ULPOS Address,OUT void* Buffer);
	virtual bool	SavePage(IN ULPOS Address,OUT void* Buffer);
	virtual DWORD	GetPageAttribute(IN ULPOS Address);
	virtual void	RelocLoad(IN ULPOS BaseAddr);
	virtual void	SetRMProc(IN RWProc RMFunc,IN void*RMObj = NULL);
	virtual void	SetWMProc(IN RWProc WMFunc,IN void*WMObj = NULL);
	virtual	bool	IsInvalidAddress(ULPOS Address);
	virtual	ULSIZE	ReadMemory(IN ULPOS Address,OUT void*Buffer,IN ULSIZE Size);
	virtual	ULSIZE	WriteMemory(IN ULPOS Address,OUT void*Buffer,IN ULSIZE Size);
	virtual	void	DumpInfo(){};
	static	ULSIZE	StaticReadMemory(IN ULPOS Address,OUT void*Buffer,IN ULSIZE Size,IN void*RMObj);
	static	ULSIZE	StaticWriteMemory(IN ULPOS Address,OUT void*Buffer,IN ULSIZE Size,IN void*RMObj);
	static	ULSIZE	StaticReadRealMemory(IN ULPOS Address,OUT void*Buffer,IN ULSIZE Size,IN void*RMObj);
	static	ULSIZE	StaticWriteRealMemory(IN ULPOS Address,OUT void*Buffer,IN ULSIZE Size,IN void*RMObj);
public:
	void	InitParam();
	void	ChangeFileIO(IN CFileIO*pFileIO);
	bool	ReadFile(IN ULPOS Pos,OUT void* Buffer,IN ULSIZE Size);
	bool	WriteFile(IN ULPOS Pos,IN void* Buffer,IN ULSIZE Size);
	bool	ReadFile(OUT void* Buffer,IN ULSIZE Size);
	bool	WriteFile(IN void* Buffer,IN ULSIZE Size);
	bool	CutFile(IN ULPOS Pos,IN ULSIZE Size);
	ULSIZE	ReadString(IN ULPOS Pos,OUT CHAR * Buffer,IN ULSIZE MaxLen,ULSIZE AlignLen = 24);
	ULSIZE	ReadString(IN ULPOS Pos,OUT WORD * Buffer,IN ULSIZE MaxLen,ULSIZE AlignLen = 24);
	ULSIZE	ReadString(IN ULPOS Pos,OUT DCHAR* Buffer,IN ULSIZE MaxLen,ULSIZE AlignLen = 24);
	ULSIZE	GetFileLength();
	bool	SetFileLength(IN ULSIZE Length);
	bool	DeleteFile();
	bool	inline IsOpened(){ return m_hFile!= NULL || m_Buffer!=NULL; }
	ULPOS	m_EntryPoint;
	UINT	m_FileType;
	UINT	m_FileObjType;
	DWORD	m_PageAttribute;
	ULSIZE	m_FileSize;
	ULPOS	m_BaseOffset;
	ULPOS	m_FilePointer;
	BYTE*	m_Buffer;
	CFileIO*m_pFileIO;
};

class CImageFileStream : public ALTFileStream,public CImageFile
{
public:
	int		Puts(void*Buffer,int Size);
	int		Gets(void*Buffer,int Size);
};

NAME_SPACE_END

#endif
