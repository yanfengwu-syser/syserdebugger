#include "StdAfx.h"
#include "ImageFile.h"

NAME_SPACE_BEGIN

CImageFile::CImageFile()
{
	m_hFile = NULL;
	m_FileType = FILE_TYPE_BIN;
	m_pFileIO = gpFileIO;
	m_Buffer=NULL;
	m_FileObjType = FILE_OBJ_TYPE_NULL;
	m_FilePointer = 0;
	m_ReadMemory = (RWProc)StaticReadMemory;
	m_RMObj = this;
	m_WriteMemory = (RWProc)StaticWriteMemory;
	m_WMObj = this;
}

void CImageFile::InitParam()
{
	m_PageAttribute=MP_READWRITE | MP_IMAGE;
	m_ImageBase = m_BaseOffset = m_EntryPoint = 0;
	m_ImageHighBase=m_ImageSize=m_FileSize;
	m_FileType=FILE_TYPE_BIN;
	m_FilePointer=0;
}

bool CImageFile::Create(IN PCSTR FileName,IN ULSIZE Size)
{
	if(m_pFileIO==NULL)
		m_pFileIO = gpFileIO;
	if(m_pFileIO->CreateFile(FileName,&m_hFile)==false)
		return false;
	m_ImageName=FileName;
	m_FileObjType=FILE_OBJ_TYPE_OPEN_FOR_WRITE;
	SetFileLength(Size);
	GetFileLength();
	InitParam();
	return true;
}

bool CImageFile::Create(IN ULSIZE Size,IN BYTE*Buffer,bool bCompress)
{
	if(Buffer==NULL || bCompress)
	{
		m_Buffer=new BYTE[Size];
		m_FileObjType |= FILE_OBJ_TYPE_MEMORY_IMAGE;
	}
	else
	{
		m_Buffer = Buffer;
		m_FileObjType |= FILE_OBJ_TYPE_USER_MEMORY_IMAGE;
	}
	if(bCompress)
	{
#ifdef _CODE_COMPRESS_H_
		if(Buffer==NULL || Size==0)
			return false;
		if(Decompress(Buffer,Size,m_Buffer)!=Size)
		{
			delete m_Buffer;
			m_FileObjType &= ~FILE_OBJ_TYPE_MEMORY_IMAGE;
			return false;
		}
#else
		return false;
#endif
	}
	m_FileSize = Size;
	m_FilePointer = 0;
	InitParam();
	return true;
}

bool CImageFile::Open(IN PCSTR FileName,IN HANDLE*pHandleOpen)
{
	if(m_pFileIO==NULL)
		m_pFileIO = gpFileIO;
	if(FileName)
	{
		m_FileObjType = FILE_OBJ_TYPE_NULL;
		if(m_pFileIO->OpenFile(FileName,&m_hFile)==false)
 			return false;
		m_ImageName=FileName;
	}
	else
	{
		m_FileObjType |= FILE_OBJ_TYPE_OPEN_FOR_WRITE;
		if(m_FileObjType&FILE_OBJ_TYPE_MEMORY_IMAGE_MASK)
			return true;
		m_hFile=*pHandleOpen;
		m_ImageName.Empty();
		m_FileObjType |= FILE_OBJ_TYPE_OPEN_BY_HANDLE;
	}
	m_FilePointer = 0;
	m_FileSize=(ULSIZE)m_pFileIO->GetFileLength(m_hFile);
	InitParam();
	return true;
}

void CImageFile::Close()
{
	m_ImageName.Empty();
	if(m_FileObjType&FILE_OBJ_TYPE_MEMORY_IMAGE)
		SafeDelete(m_Buffer);
	if((m_FileObjType&FILE_OBJ_TYPE_OPEN_BY_HANDLE)==0)
	{
		m_pFileIO->CloseHandle(m_hFile);
		m_hFile=NULL;
	}
	m_ImageHighBase = m_ImageBase = 0;	
	m_ImageSize = 0;
	m_FilePointer = 0;
	if(m_FileObjType&FILE_OBJ_TYPE_AUTO_DELETE)
		delete this;
	else
		m_FileObjType=FILE_OBJ_TYPE_NULL;
}

void CImageFile::ChangeFileIO(IN CFileIO*pFileIO)
{
	m_pFileIO = pFileIO;
}

bool CImageFile::ReadFile(IN ULPOS Pos,OUT void* Buffer,IN ULSIZE Size)
{
	ULSIZE RDSize;
	if(m_Buffer)
	{
		if(Pos>=m_FileSize)
			return false;		
		RDSize = m_FileSize-Pos;
		MAX_LIMIT(RDSize,Size);		
		memcpy(Buffer,RT_PBYTE(m_Buffer,Pos+m_BaseOffset),RDSize);
		m_FilePointer=Pos+RDSize;
		return true;
	}
	if(m_FileSize==0)
		GetFileLength();
	if(Pos>m_FileSize)
		return false;
	RDSize=m_pFileIO->ReadFile(m_hFile,Buffer,Size,Pos+m_BaseOffset);
	m_FilePointer=Pos+m_BaseOffset+RDSize;
	return RDSize==Size;
}

bool CImageFile::WriteFile(IN ULPOS Pos,IN void* Buffer,IN ULSIZE Size)
{
	ULSIZE WTSize;
	if(m_Buffer)
	{
		if(Pos>=m_FileSize)
			return false;
		WTSize = m_FileSize-Pos;
		MAX_LIMIT(WTSize,Size);
		memcpy(RT_PBYTE(m_Buffer,Pos+m_BaseOffset),Buffer,WTSize);
		m_FilePointer=Pos+WTSize;
		return true;
	}
	if((m_FileObjType&FILE_OBJ_TYPE_OPEN_FOR_WRITE)==0)
	{
		m_pFileIO->CloseHandle(m_hFile);
		if(m_pFileIO->OpenFile(m_ImageName,&m_hFile,FIO_WRITE|FIO_SHARE_READ)==false)
			return false;
		m_FileObjType |= FILE_OBJ_TYPE_OPEN_FOR_WRITE;
	}
	WTSize=m_pFileIO->WriteFile(m_hFile,Buffer,Size,Pos+m_BaseOffset);
	m_FilePointer=Pos+m_BaseOffset+WTSize;
	if(m_FileSize<m_FilePointer)
		m_FileSize = m_FilePointer;
	return  WTSize==Size;
}

bool CImageFile::ReadFile(OUT void* Buffer,IN ULSIZE Size)
{
	ULSIZE RDSize;
	if(m_Buffer)
	{
		if(m_FilePointer>=m_FileSize)
			return false;
		RDSize = m_FileSize-m_FilePointer;
		MAX_LIMIT(RDSize,Size);		
		memcpy(Buffer,RT_PBYTE(m_Buffer,m_FilePointer),RDSize);
		m_FilePointer+=RDSize;
		return true;
	}
	RDSize = m_pFileIO->ReadFile(m_hFile,Buffer,Size,m_FilePointer);
	m_FilePointer+=RDSize;
	return RDSize == Size;
}

bool CImageFile::WriteFile(IN void* Buffer,IN ULSIZE Size)
{
	ULSIZE WTSize;
	if(m_Buffer)
	{
		if(m_FilePointer>=m_FileSize)
			return false;
		WTSize = m_FileSize-m_FilePointer;
		MAX_LIMIT(WTSize,Size);
		memcpy(RT_PBYTE(m_Buffer,m_FilePointer),Buffer,WTSize);
		m_FilePointer+=WTSize;
		return true;
	}
	WTSize = m_pFileIO->WriteFile(m_hFile,Buffer,Size,m_FilePointer);
	m_FilePointer+=WTSize;
	if(m_FileSize<m_FilePointer)
		m_FileSize = m_FilePointer;
	return WTSize == Size;
}

bool CImageFile::CutFile(IN ULPOS Pos,IN ULSIZE Size)
{
	int nBlock,Offset;
	ULSIZE TailSize,LeftSize;
	BYTE*Buffer;
	if(Pos+Size>m_FileSize)
		return false;
	TailSize = m_FileSize - Pos - Size;
	if(TailSize <= MAX_FILE_OPT_SIZE)
	{
		Buffer = new BYTE[TailSize];
		if(Buffer==NULL)
			return false;
		ReadFile(Pos+Size,Buffer,TailSize);
		WriteFile(Pos,Buffer,TailSize);
		SetFileLength(Pos+TailSize);
		delete Buffer;
	}
	else
	{
		Buffer = new BYTE[MAX_FILE_OPT_SIZE];
		if(Buffer==NULL)
			return false;
		nBlock = PAGE_COUNT(TailSize,MAX_FILE_OPT_SIZE);
		Offset = 0;
		LeftSize = TailSize%MAX_FILE_OPT_SIZE;
		for(int n=1;n<nBlock;n++)
		{
			ReadFile(Pos+Size+Offset,Buffer,MAX_FILE_OPT_SIZE);
			WriteFile(Pos+Offset,Buffer,MAX_FILE_OPT_SIZE);
			Offset+=MAX_FILE_OPT_SIZE;
		}
		ReadFile(Pos+Size+Offset,Buffer,LeftSize);
		WriteFile(Pos+Offset,Buffer,LeftSize);
		SetFileLength(Pos+TailSize);
		delete Buffer;
	}
	return true;
}

bool CImageFile::DeleteFile()
{
	return m_pFileIO->DeleteFile(m_ImageName);
}

ULSIZE CImageFile::ReadString(IN ULPOS Pos,OUT CHAR* Buffer,IN ULSIZE MaxLen,IN ULSIZE AlignLen)
{
	ULPOS Offset;
	ULSIZE Len;
	Offset=0;
	if(MaxLen==0)
		return 0;
	while(Offset<MaxLen)
	{
		Len=MIN(MaxLen-Offset,AlignLen);
		ReadMemory(Pos+Offset*sizeof(*Buffer),&Buffer[Offset],Len*sizeof(*Buffer));
		for(ULSIZE n=0;n<Len;n++)
		{
			if(Buffer[Offset+n]==0)
				return Offset+n;
		}
		Offset+=Len;
	}
	MaxLen--;
	Buffer[MaxLen]=0;
	return MaxLen;
}

ULSIZE CImageFile::ReadString(IN ULPOS Pos,OUT WORD* Buffer,IN ULSIZE MaxLen,IN ULSIZE AlignLen)
{
	ULPOS Offset;
	ULSIZE Len;	
	Offset=0;
	if(MaxLen==0)
		return 0;
	while(Offset<MaxLen)
	{
		Len=MIN(MaxLen-Offset,AlignLen);
		ReadMemory(Pos+Offset*sizeof(*Buffer),&Buffer[Offset],Len*sizeof(*Buffer));
		for(ULSIZE n=0;n<Len;n++)
		{
			if(Buffer[Offset+n]==0)
				return Offset+n;
		}
		Offset+=Len;
	}
	MaxLen--;
	Buffer[MaxLen]=0;
	return MaxLen;
}

ULSIZE CImageFile::ReadString(IN ULPOS Pos,OUT DCHAR* Buffer,IN ULSIZE MaxLen,IN ULSIZE AlignLen)
{
	ULPOS Offset;
	ULSIZE Len;	
	Offset=0;
	if(MaxLen==0)
		return 0;
	while(Offset<MaxLen)
	{
		Len=MIN(MaxLen-Offset,AlignLen);
		ReadMemory(Pos+Offset*sizeof(*Buffer),&Buffer[Offset],Len*sizeof(*Buffer));
		for(ULSIZE n=0;n<Len;n++)
		{
			if(Buffer[Offset+n]==0)
				return Offset+n;
		}
		Offset+=Len;
	}
	MaxLen--;
	Buffer[MaxLen]=0;
	return MaxLen;
}

ULSIZE CImageFile::GetFileLength()
{
	if(m_Buffer==NULL)
		m_FileSize = (ULSIZE)m_pFileIO->GetFileLength(m_hFile);
	return m_FileSize;
}

bool CImageFile::SetFileLength(IN ULSIZE Length)
{
	if(m_Buffer)
		return false;
	if((m_FileObjType&FILE_OBJ_TYPE_OPEN_FOR_WRITE)==0)
	{
		m_pFileIO->CloseHandle(m_hFile);
		if(!m_pFileIO->OpenFile(m_ImageName,&m_hFile,FIO_WRITE | FIO_SHARE_READ))
			return false;
		m_FileObjType|=FILE_OBJ_TYPE_OPEN_FOR_WRITE;
	}
	if(m_pFileIO->SetFileLength(m_hFile,Length)==false)
		return false;
	m_FileSize = (ULSIZE)m_pFileIO->GetFileLength(m_hFile);
	return true;
}

ULSIZE CImageFile::ReadImageMemory(IN ULPOS Address,OUT void*Buffer,IN ULSIZE Size)
{
////加受///////////////////////////////////
	if(Address < m_ImageBase || Address>= m_ImageHighBase)
		return 0;
	if(Address< m_ImageHighBase && Address+Size >m_ImageHighBase)
		Size=m_ImageHighBase-Address;
////加受///////////////////////////////////
	ReadFile(Address-m_ImageBase,Buffer,Size);
	return Size;
}

ULSIZE CImageFile::WriteImageMemory(IN ULPOS Address,OUT void*Buffer,IN ULSIZE Size)
{
	////加受///////////////////////////////////
	if(Address < m_ImageBase || Address>= m_ImageHighBase)
		return 0;
	if(Address< m_ImageHighBase && Address+Size >m_ImageHighBase)
		Size=m_ImageHighBase-Address;
	////加受///////////////////////////////////
	WriteFile(Address-m_ImageBase,Buffer,Size);
	return Size;
}

bool CImageFile::LoadPage(IN ULPOS Address,OUT void* Buffer)
{
	ZeroMemory(Buffer,MP_SIZE);
	ReadMemory(Address-m_ImageBase,Buffer,MP_SIZE);
	return true;
}

bool CImageFile::SavePage(IN ULPOS Address,OUT void* Buffer)
{
	return WriteFile(Address-m_ImageBase,Buffer,MP_SIZE);
}

DWORD CImageFile::GetPageAttribute(IN ULPOS Address)
{
	return m_PageAttribute;
}

void CImageFile::RelocLoad(IN ULPOS BaseAddr)
{
	ULPOS Delta;
	Delta=BaseAddr-m_ImageBase;
	m_ImageBase=BaseAddr;
	m_ImageHighBase+=Delta;
	m_EntryPoint+=Delta;
}

void CImageFile::SetRMProc(IN RWProc RMFunc,IN void*RMObj)
{
	m_ReadMemory = RMFunc;
	m_RMObj = RMObj;
}

void CImageFile::SetWMProc(IN RWProc WMFunc,IN void*WMObj)
{
	m_WriteMemory = WMFunc;
	m_WMObj = WMObj;
}

ULSIZE CImageFile::ReadMemory(IN ULPOS Address,OUT void*Buffer,IN ULSIZE Size)
{
	if(m_ReadMemory==NULL)
		return 0;
	return m_ReadMemory(Address,Buffer,Size,m_RMObj);
}

ULSIZE CImageFile::WriteMemory(IN ULPOS Address,OUT void*Buffer,IN ULSIZE Size)
{
	if(m_WriteMemory==NULL)
		return 0;
	return m_WriteMemory(Address,Buffer,Size,m_WMObj);
}

ULSIZE CImageFile::StaticReadMemory(IN ULPOS Address,IN void*Buffer,IN ULSIZE Size,IN void*RMObj)
{
	return ((CImageFile*)RMObj)->ReadImageMemory(Address,Buffer,Size);
}

ULSIZE CImageFile::StaticWriteMemory(IN ULPOS Address,IN void*Buffer,IN ULSIZE Size,IN void*RMObj)
{
	return ((CImageFile*)RMObj)->WriteImageMemory(Address,Buffer,Size);
}

ULSIZE CImageFile::StaticReadRealMemory(IN ULPOS Address,IN void*Buffer,IN ULSIZE Size,IN void*RMObj)
{
	memcpy(Buffer,NUM_TO_PTR(Address),Size);
	return Size;
}

ULSIZE CImageFile::StaticWriteRealMemory(IN ULPOS Address,IN void*Buffer,IN ULSIZE Size,IN void*RMObj)
{
	memcpy(NUM_TO_PTR(Address),Buffer,Size);
	return Size;
}

bool CImageFile::IsInvalidAddress(ULPOS Address)
{
	return Address<m_ImageBase || Address>=m_ImageHighBase;
}

int CImageFileStream::Puts(void*Buffer,int Size)
{
	return WriteFile(Buffer,Size)?Size:0;
}

int CImageFileStream::Gets(void*Buffer,int Size)
{
	return ReadFile(Buffer,Size)?Size:0;
}

NAME_SPACE_END

