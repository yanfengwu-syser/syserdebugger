#include "StdAfx.h"
#include "PolyFS.h"

NAME_SPACE_BEGIN

CPolyFS::CPolyFS()
{
	m_pFileIO = gpFileIO;
	m_ZeroBuffer=NULL;
	m_MaxCachePageCount = 0x100;
}

CPolyFS::~CPolyFS()
{
	CloseDisk();
}

void CPolyFS::ChangeFileIO(CFileIO*pFileIO)
{
	m_pFileIO = pFileIO;
}

bool CPolyFS::Format(PCSTR DiskFileName,ULONG Size,DWORD ClusSize)
{
	DWORD Data;
	if(Size==0)
		return false;
	if(ClusSize==0)
		ClusSize=0x1000;
	m_DiskImage.ChangeFileIO(m_pFileIO);
	if(m_DiskImage.Create(DiskFileName)==false)
		return false;
	m_ClusSize = ALIGN_SIZE(ClusSize,0x100);
	PFS_HEAD PFSHead;
	STZeroMemory(PFSHead);
	TStrCpy((char*)PFSHead.Sign,"PFS");
	m_ClusCount = PFSHead.ClusCount = ALIGN_SIZE(Size/m_ClusSize,m_ClusSize/4);
	Size = m_ClusCount*m_ClusSize;

	PFSHead.ClusSize = m_ClusSize;
	TStrCpy(PFSHead.FatEntry.FileName,"*FAT*");
	PFSHead.FatEntry.Attribute=PFS_FILE_SYSTEM;
	PFSHead.FatEntry.BeginClus=1;
	PFSHead.FatEntry.FileSize=PFSHead.ClusCount*4;
	PFSHead.FatEntry.NameCode=TGetNameCode(PFSHead.FatEntry.FileName);
	m_DiskImage.m_FileSize = m_ClusSize*m_ClusCount;
	m_Style = PFS_NORMAL;
	InitParam();
	m_FatOff = PFSHead.FatEntry.BeginClus*m_ClusSize;
	if(WriteDiskFile(0,&PFSHead,sizeof(PFS_HEAD))==false)
	{
		CloseDisk();
		return false;
	}
	DWORD nClusOfFat=PFSHead.FatEntry.FileSize/m_ClusSize;
	for(DWORD n=0;n<nClusOfFat;n++)
	{
		if(WriteDiskFile(m_FatOff+n*m_ClusSize,m_ZeroBuffer,m_ClusSize)==false)
		{
			CloseDisk();
			return false;
		}
	}
	///////////////////////////////////////////////////////
	//Head
	///////////////////////////////////////////////////////
	Data = PFS_END_CLUS;
	if(WriteFatCell(0,&Data)==false)
	{
		CloseDisk();
		return false;
	}
	///////////////////////////////////////////////////////
	//Fat
	///////////////////////////////////////////////////////
	for(DWORD n=1;n<nClusOfFat;n++)
	{
		Data=n+PFSHead.FatEntry.BeginClus;
		if(WriteFatCell(n,&Data)==false)
		{
			CloseDisk();
			return false;
		}
	}
	Data = PFS_END_CLUS;
	if(WriteFatCell(nClusOfFat,&Data)==false)
	{
		CloseDisk();
		return false;
	}

	///////////////////////////////////////////////////////
	//Root
	///////////////////////////////////////////////////////
	PFS_FILE_ENTRY FileEntry;
	STZeroMemory(FileEntry);
	FileEntry.BeginClus = 0;
	FileEntry.FileSize = m_ClusSize;
	CreateFile("*ROOT*",PFS_FILE_SYSTEM | PFS_FILE_DIR,m_ClusSize,&FileEntry,ST_FIELD_OFF(PFS_HEAD,RootEntry));
	ReadDiskFile(ST_FIELD_OFF(PFS_HEAD,RootEntry),&m_RootEntry,sizeof(m_RootEntry));
	CloseDisk();
	return true;
}

bool CPolyFS::ReadDiskFile(DWORD Pos,void*Buffer,DWORD Size)
{
	return m_PageMemory.ReadMemX(Pos,Buffer,Size)==Size;
}

bool CPolyFS::WriteDiskFile(DWORD Pos,void*Buffer,DWORD Size)
{
	return m_PageMemory.WriteMemX(Pos,Buffer,Size)==Size;
}

bool CPolyFS::ReadFatCell(DWORD Index,void*Buffer)
{
	return ReadDiskFile(m_FatOff+Index*4,Buffer,4);
}

bool CPolyFS::WriteFatCell(DWORD Index,void*Buffer)
{
	return WriteDiskFile(m_FatOff+Index*4,Buffer,4);
}

bool CPolyFS::ReadClus(DWORD Index,void*Buffer)
{
	if(Index>=m_ClusCount)
		return false;
	return ReadDiskFile(Index*m_ClusSize,Buffer,m_ClusSize);
}

bool CPolyFS::WriteClus(DWORD Index,void*Buffer)
{
	if(Index>=m_ClusCount)
		return false;
	return WriteDiskFile(Index*m_ClusSize,Buffer,m_ClusSize);
}

DWORD CPolyFS::FileOffToDP(DWORD ClusIndex,DWORD Offset)
{
	while(Offset>=m_ClusSize)
	{
		if(ReadFatCell(ClusIndex,&ClusIndex)==false)
			return 0;
		if(ClusIndex==PFS_END_CLUS)
			return 0;
		Offset-=m_ClusSize;
	}
	return ClusIndex*m_ClusSize+Offset;
}

DWORD CPolyFS::FileOffToClus(DWORD ClusIndex,DWORD Offset)
{
	while(Offset>=m_ClusSize)
	{
		if(ReadFatCell(ClusIndex,&ClusIndex)==false)
			return PFS_END_CLUS;
		if(ClusIndex==PFS_END_CLUS)
			return PFS_END_CLUS;
		Offset-=m_ClusSize;
	}
	return ClusIndex;
}

DWORD CPolyFS::ReadFile(PFS_FILE_DATA*pHandleData,DWORD Offset,void*Buffer,DWORD Size)
{
	DWORD CompressSize,RealFileLength;
	BYTE*CompressBuffer;
	if((pHandleData->ThisFileEntry.Attribute&PFS_FILE_COMPRESS)==0)
		return ReadFile(&pHandleData->ThisFileEntry,Offset,Buffer,Size);
	if(ReadFile(&pHandleData->ThisFileEntry,0,&RealFileLength,4)!=4)
		return 0;
	if(Offset!=0 || Size!=RealFileLength)
		return 0;
	CompressSize = pHandleData->ThisFileEntry.FileSize;
	CompressBuffer = new BYTE[CompressSize];
	if(CompressBuffer==NULL)
		return 0;
	if(ReadFile(&pHandleData->ThisFileEntry,0,CompressBuffer,CompressSize)!=CompressSize)
	{
		delete CompressBuffer;
		return 0;
	}
	Decompress(CompressBuffer,CompressSize,Buffer);
	delete CompressBuffer;
	return Size;
}

DWORD CPolyFS::WriteFile(PFS_FILE_DATA*pHandleData,DWORD Offset,const void*Buffer,DWORD Size)
{
	if(Offset+Size>pHandleData->ThisFileEntry.FileSize)
	{
		if(SetFileLength(pHandleData,Offset+Size)==false)
			return false;
	}
	return WriteFile(&pHandleData->ThisFileEntry,Offset,Buffer,Size);
}

DWORD CPolyFS::ReadFile(PFS_FILE_ENTRY*pFileEntry,DWORD Offset,void*Buffer,DWORD Size)
{
	DWORD FileDP,nBytes,PageSize,Mod,ClusIndex;
	if(Offset>=pFileEntry->FileSize || Size==0)
		return 0;
	nBytes=0;
	Mod = Offset%m_ClusSize;
	if(Mod)
	{
		FileDP=FileOffToDP(pFileEntry->BeginClus,Offset);
		if(FileDP==0)
			return 0;
		PageSize=MIN(m_ClusSize-Mod,Size);
		if(ReadDiskFile(FileDP,RT_PVOID(Buffer,nBytes),PageSize)==false)
			return 0;
		nBytes+=PageSize;
	}
	ClusIndex=FileOffToClus(pFileEntry->BeginClus,Offset+nBytes);
	for(DWORD n=(Size-nBytes)/m_ClusSize;n>0 && Offset+nBytes<pFileEntry->FileSize;n--)
	{
		if(ClusIndex==PFS_END_CLUS || ReadClus(ClusIndex,RT_PVOID(Buffer,nBytes))==false)
			return false;
		nBytes+=m_ClusSize;
		ClusIndex = FileOffToClus(ClusIndex,m_ClusSize);
	}
	if(Size-nBytes && Offset+nBytes<pFileEntry->FileSize)
	{
		FileDP=FileOffToDP(ClusIndex,(Offset+nBytes)%m_ClusSize);
		if(FileDP==0)
			return nBytes;
		PageSize = Size-nBytes;
		if(ReadDiskFile(FileDP,RT_PVOID(Buffer,nBytes),PageSize)==false)
			return nBytes;
		nBytes+=PageSize;
	}
	return nBytes;
}

DWORD CPolyFS::WriteFile(PFS_FILE_ENTRY*pFileEntry,DWORD Offset,const void*Buffer,DWORD Size)
{
	DWORD FileDP,nBytes,PageSize,Mod,ClusIndex;
	if(Offset>=pFileEntry->FileSize || Size==0)
		return 0;
	nBytes=0;
	Mod = Offset%m_ClusSize;
	if(Mod)
	{
		FileDP=FileOffToDP(pFileEntry->BeginClus,Offset);
		if(FileDP==0)
			return 0;
		PageSize=MIN(m_ClusSize-Mod,Size);
		if(WriteDiskFile(FileDP,RT_PVOID(Buffer,nBytes),PageSize)==false)
			return 0;
		nBytes+=PageSize;
	}
	ClusIndex=FileOffToClus(pFileEntry->BeginClus,Offset+nBytes);
	for(DWORD n=(Size-nBytes)/m_ClusSize;n>0 && Offset+nBytes<pFileEntry->FileSize;n--)
	{
		if(ClusIndex==PFS_END_CLUS || WriteClus(ClusIndex,RT_PVOID(Buffer,nBytes))==false)
			return false;
		nBytes+=m_ClusSize;
		ClusIndex = FileOffToClus(ClusIndex,m_ClusSize);
	}
	if(Size-nBytes && Offset+nBytes<pFileEntry->FileSize)
	{
		FileDP=FileOffToDP(ClusIndex,(Offset+nBytes)%m_ClusSize);
		if(FileDP==0)
			return nBytes;
		PageSize = Size-nBytes;
		if(WriteDiskFile(FileDP,RT_PVOID(Buffer,nBytes),PageSize)==false)
			return nBytes;
		nBytes+=PageSize;
	}
	return nBytes;
}

DWORD CPolyFS::FindFreeFileEntryFP(PFS_FILE_ENTRY*pParentEntry)
{
	PFS_FILE_ENTRY FileEntry;
	DWORD Off;
	Off=0;
	while(Off<pParentEntry->FileSize)
	{
		if(ReadFile(pParentEntry,Off,&FileEntry,sizeof(FileEntry))!=sizeof(FileEntry))
			return PFS_ERROR_FP;
		if(FileEntry.NameCode==0 || FileEntry.NameCode==PFS_ERROR_NAME_CODE)
			return Off;
		Off+=sizeof(FileEntry);
	}
	return PFS_ERROR_FP;
}

bool CPolyFS::CreateFile(PCSTR FileName,DWORD Attr,DWORD Size,PFS_FILE_ENTRY*pParentDirEntry,DWORD ParenFileEntryFP)
{
	DWORD BeginClus,NextClus,PrevClus,nClus,Off;
	nClus=PAGE_COUNT(Size,m_ClusSize);
	if(nClus==0)
	{
		BeginClus=PFS_END_CLUS;
	}
	else
	{
		BeginClus=NextClus=FindNextFreeClus(0);
		for(DWORD n=0;n<nClus-1;n++)
		{
			PrevClus = NextClus;
			NextClus=FindNextFreeClus(NextClus+1);
			if(NextClus==PFS_END_CLUS)
				return false;
			if(WriteFatCell(PrevClus,&NextClus)==false)
				return false;
		}
		PrevClus=NextClus;
		NextClus=PFS_END_CLUS;
		if(WriteFatCell(PrevClus,&NextClus)==false)
			return false;
	}
	PFS_FILE_ENTRY FileEntry;
	STZeroMemory(FileEntry);
	FileEntry.Attribute = Attr;
	FileEntry.FileSize = Size;
	FileEntry.BeginClus = BeginClus;
	TStrCpyLimit(FileEntry.FileName,FileName,sizeof(FileEntry.FileName));
	FileEntry.NameCode = TGetNameCode(FileEntry.FileName);
	if(CPolyFS::WriteFile(pParentDirEntry,ParenFileEntryFP,&FileEntry,sizeof(FileEntry))!=sizeof(FileEntry))
		return false;
	if(Size==0)
		return true;
	Off=0;
	while(Off<Size)
	{
		if(WriteFile(&FileEntry,Off,m_ZeroBuffer,m_ClusSize)==false)
			break;
		Off+=m_ClusSize;
	}
	return true;
}

bool CPolyFS::CreateFile(PCSTR FullFileName,DWORD Attr,DWORD Size,PFS_FILE_DATA*pHandleData)
{
	DWORD	FreeFileEntryFP;
	PFS_FIND_DATA FindData;
	char PathName[256],FileName[256];
	if(*FullFileName!='\\')
	{
		return false;
	}
	else
	{
		if(FullFileName[1]==0)
			return false;
	}
	if(FindFirstFile(FullFileName,&FindData))
	{
		FreeFileEntryFP = FindData.FileEntryFP;
		if(SetFileLength(FullFileName,Size)==false)
			return false;
		pHandleData->FilePoint=0;
		pHandleData->ParentEntry = FindData.ParentEntry;
		pHandleData->FileEntryFP = FreeFileEntryFP;
		return CPolyFS::ReadFile(&pHandleData->ParentEntry,FreeFileEntryFP,&pHandleData->ThisFileEntry,sizeof(pHandleData->ThisFileEntry))==sizeof(pHandleData->ThisFileEntry);
	}
	else
	{
		TStrCpy(FileName,TGetFileName(FullFileName));
		TGetFilePath(FullFileName,PathName);
		if(*PathName==0)
			TStrCpy(PathName,"\\");
		if(FindFirstFile(PathName,&FindData)==false)
			return false;
		FreeFileEntryFP=FindFreeFileEntryFP(&FindData.ThisFileEntry);
		if(FreeFileEntryFP==PFS_ERROR_FP)
		{
			if(SetFileLength(PathName,FindData.ThisFileEntry.FileSize+m_ClusSize)==false)
				return false;
			FindData.ThisFileEntry.FileSize+=m_ClusSize;
			if(*PathName=='\\' && PathName[1]==0)
				m_RootEntry = FindData.ThisFileEntry;
			FreeFileEntryFP=FindFreeFileEntryFP(&FindData.ThisFileEntry);
			if(FreeFileEntryFP==PFS_ERROR_FP)
				return false;
		}
		pHandleData->FilePoint=0;
		if(CreateFile(FileName,Attr,Size,&FindData.ThisFileEntry,FreeFileEntryFP)==false)
			return false;
		pHandleData->ParentEntry = FindData.ThisFileEntry;
		pHandleData->FileEntryFP = FreeFileEntryFP;
		return CPolyFS::ReadFile(&pHandleData->ParentEntry,FreeFileEntryFP,&pHandleData->ThisFileEntry,sizeof(pHandleData->ThisFileEntry))==sizeof(pHandleData->ThisFileEntry);
	}
}

bool CPolyFS::OpenFile(PCSTR FullFileName,PFS_FILE_DATA*pHandleData)
{
	PFS_FIND_DATA FindData;
	if(FindFirstFile(FullFileName,&FindData)==false)
		return false;
	pHandleData->FilePoint=0;
	pHandleData->ThisFileEntry = FindData.ThisFileEntry;
	pHandleData->ParentEntry = FindData.ParentEntry;
	pHandleData->FileEntryFP = FindData.FileEntryFP;
	return true;
}

DWORD CPolyFS::FindNextFreeClus(DWORD ClusIdx)
{
	DWORD Data;
	for(DWORD Index=ClusIdx;Index<m_ClusCount;Index++)
	{
		if(ReadFatCell(Index,&Data)==false)
			return PFS_END_CLUS;
		if(Data==0)
			return Index;
	}
	return PFS_END_CLUS;
}

bool CPolyFS::SetFileLength(PCSTR FullFileName,DWORD Length)
{
	PFS_FILE_DATA FileData;
	if(OpenFile(FullFileName,&FileData)==false)
		return false;
	return SetFileLength(&FileData,Length);
}

bool CPolyFS::SetFileLength(PFS_FILE_DATA*pHandleData,DWORD Length)
{
	DWORD nNewClus,nOldClus,Data,ClusIdx,PrevIdx,PrevFatDP;
	nNewClus=PAGE_COUNT(Length,m_ClusSize);
	nOldClus=PAGE_COUNT(pHandleData->ThisFileEntry.FileSize,m_ClusSize);
	if(nNewClus>nOldClus)
	{
		if(nOldClus)
		{
			ClusIdx=FileOffToClus(pHandleData->ThisFileEntry.BeginClus,(nOldClus-1)*m_ClusSize);
			if(ClusIdx==PFS_END_CLUS)
				return false;
		}
		for(DWORD n=nOldClus;n<nNewClus;n++)
		{
			if(n==0)
			{
				PrevFatDP = FileOffToDP(pHandleData->ParentEntry.BeginClus,pHandleData->FileEntryFP)+ST_FIELD_OFF(PFS_FILE_ENTRY,BeginClus);
				if(PrevFatDP==0)
					return false;
				ClusIdx=FindNextFreeClus(1);
				pHandleData->ThisFileEntry.BeginClus = ClusIdx;
				if(WriteDiskFile(PrevFatDP,&ClusIdx,4)==false)
					return false;
			}
			else
			{
				PrevIdx = ClusIdx;
				ClusIdx=FindNextFreeClus(ClusIdx+1);
				if(ClusIdx==PFS_END_CLUS)
					return false;
				if(WriteFatCell(PrevIdx,&ClusIdx)==false)
					return false;
			}
		}
		Data=PFS_END_CLUS;
		if(WriteFatCell(ClusIdx,&Data)==false)
			return false;

		DWORD Off,WTSize;
		Off = pHandleData->ThisFileEntry.FileSize;
		pHandleData->ThisFileEntry.FileSize = Length;
		while(Off < pHandleData->ThisFileEntry.FileSize)
		{
			WTSize = MIN(m_ClusSize,pHandleData->ThisFileEntry.FileSize - Off);
			WriteFile(&pHandleData->ThisFileEntry,Off,m_ZeroBuffer,WTSize);
			Off+=WTSize;
		}
	}
	else if(nNewClus<nOldClus)
	{
		ClusIdx=FileOffToClus(pHandleData->ThisFileEntry.BeginClus,nNewClus*m_ClusSize);
		if(DeleteFileClus(ClusIdx)==false)
			return false;
		Data=PFS_END_CLUS;
		if(WriteFatCell(ClusIdx,&Data)==false)
			return false;
		pHandleData->ThisFileEntry.FileSize=Length;
	}
	else
	{
		pHandleData->ThisFileEntry.FileSize = Length;
	}
	return WriteFile(&pHandleData->ParentEntry,pHandleData->FileEntryFP+ST_FIELD_OFF(PFS_FILE_ENTRY,FileSize),&Length,4)==4;
}

DWORD CPolyFS::GetFileLength(PCSTR FullFileName)
{
	DWORD RealFileLength;
	PFS_FIND_DATA FindData;
	if(FindFirstFile(FullFileName,&FindData)==false)
		return false;
	if(FindData.ThisFileEntry.Attribute&PFS_FILE_COMPRESS)
	{
		if(ReadFile(&FindData.ThisFileEntry,0,&RealFileLength,4)!=4)
			return 0;
		return RealFileLength;
	}
	return FindData.ThisFileEntry.FileSize;
}


bool CPolyFS::DeleteFile(PCSTR FullFileName)
{
	PFS_FIND_DATA FindData;
	if(*FullFileName!='\\' || FullFileName[1]==0)
		return false;
	if(FindFirstFile(FullFileName,&FindData)==false)
		return false;
	if(DeleteFileClus(FindData.ThisFileEntry.BeginClus)==false)
		return false;
	PFS_FILE_ENTRY FileEntry;
	STZeroMemory(FileEntry);
	FileEntry.NameCode = PFS_ERROR_NAME_CODE;
	return WriteFile(&FindData.ParentEntry,FindData.FileEntryFP,&FileEntry,sizeof(FileEntry))==sizeof(FileEntry);
}

bool CPolyFS::DeleteFileClus(DWORD BeginClus)
{
	DWORD Data,nThisClus,nNextClus = BeginClus;
	Data=0;
	while(nNextClus!=PFS_END_CLUS)
	{
		nThisClus = nNextClus;
		if(ReadFatCell(nThisClus,&nNextClus)==false)
			return false;
		if(WriteFatCell(nThisClus,&Data)==false)
			return false;
	}
	return true;
}

bool CPolyFS::FindFirstFile(PCSTR FullFileName,PFS_FIND_DATA*pFindData)
{
	PFS_FIND_DATA FindData;
	int Length;
	if(*FullFileName=='\\')
	{
		PCSTR pStr;
		char FileName[256];
		STZeroMemory(FindData);
		FindData.ThisFileEntry=m_RootEntry;
		FindData.ParentEntry.BeginClus = 0;
		FindData.ParentEntry.FileSize = sizeof(PFS_HEAD);
		FindData.ParentEntry.Attribute = m_RootEntry.Attribute;
		FindData.FileEntryFP = ST_FIELD_OFF(PFS_HEAD,RootEntry);

		pStr=FullFileName;
		while(*pStr)
		{
			Length=0;
			while(*pStr && *pStr!='\\')
			{
				FileName[Length]=*pStr;
				Length++;
				pStr++;
			}
			FileName[Length]=0;
			if(Length)
			{
				FindData.ParentEntry=FindData.ThisFileEntry;
				if(FindFirstFile(FileName,&FindData)==false)
					return false;			
			}
			while(*pStr=='\\')
				*pStr++;
		}
		*pFindData = FindData;
		return true;
	}
	DWORD Off=0;
	while(Off<pFindData->ParentEntry.FileSize)
	{
		if(ReadFile(&pFindData->ParentEntry,Off,&pFindData->ThisFileEntry,sizeof(PFS_FILE_ENTRY))!=sizeof(PFS_FILE_ENTRY))
			return false;
		if(CmpFileName(FullFileName,&pFindData->ThisFileEntry))
		{
			TStrCpyLimit(pFindData->FileName,pFindData->ThisFileEntry.FileName,sizeof(pFindData->FileName));
			pFindData->FileEntryFP = Off;
			TStrCpyLimit(pFindData->PattenName,FullFileName,sizeof(pFindData->PattenName));
			return true;
		}
		Off+=sizeof(PFS_FILE_ENTRY);
	}
	return false;
}

bool CPolyFS::FindNextFile(PFS_FIND_DATA*pFindData)
{
	DWORD Off;
	Off=pFindData->FileEntryFP+sizeof(PFS_FILE_ENTRY);
	while(Off<pFindData->ParentEntry.FileSize)
	{
		if(ReadFile(&pFindData->ParentEntry,Off,&pFindData->ThisFileEntry,sizeof(PFS_FILE_ENTRY))!=sizeof(PFS_FILE_ENTRY))
			return false;
		if(pFindData->ThisFileEntry.NameCode==0)
			return false;
		if(CmpFileName(pFindData->PattenName,&pFindData->ThisFileEntry))
		{
			TStrCpyLimit(pFindData->FileName,pFindData->ThisFileEntry.FileName,sizeof(pFindData->FileName));
			pFindData->FileEntryFP = Off;
			return true;
		}
		Off+=sizeof(PFS_FILE_ENTRY);
	}
	return false;
}

bool CPolyFS::CmpFileName(PCSTR FilePattenName,PFS_FILE_ENTRY*pFileEntry)
{
	if(*pFileEntry->FileName==0)
		return false;
	if(FilePattenName[0]=='*' && FilePattenName[1]=='0')
		return true;
	if(TStrChr(FilePattenName,'*') || TStrChr(FilePattenName,'?'))
		return 	TIMultiMatchWithPattern(FilePattenName,pFileEntry->FileName);
	if(TStrICmp(FilePattenName,pFileEntry->FileName)==0)
		return true;
	return false;
}

bool CPolyFS::SetFileAttribute(PCSTR FullFileName,DWORD Attr)
{
	PFS_FIND_DATA FindData;
	if(FindFirstFile(FullFileName,&FindData)==false)
		return false;
	return WriteFile(&FindData.ParentEntry,FindData.FileEntryFP+ST_FIELD_OFF(PFS_FILE_ENTRY,Attribute),&Attr,4)==4;
}

DWORD CPolyFS::GetFileAttribute(PCSTR FullFileName)
{
	PFS_FIND_DATA FindData;
	if(FindFirstFile(FullFileName,&FindData)==false)
		return false;
	return FindData.ThisFileEntry.Attribute;
}

void CPolyFS::InitParam()
{
	UINT MemMode;
	int PageCount;
	if(m_Style & PFS_FULL_DISK_CACHE)
		PageCount = (int)PAGE_COUNT(m_DiskImage.m_FileSize,MP_SIZE);
	else
		PageCount = (int)MIN(PAGE_COUNT(m_DiskImage.m_FileSize,MP_SIZE),m_MaxCachePageCount);

	if(m_Style & PFS_WRITE_COPY)
		MemMode = PMS_NO_PAGE_OUT;
	else
		MemMode = PMS_PAGE_OUT;

	m_PageMemory.Init(PageCount,MemMode);
	m_DiskImage.m_ImageBase = 0;
	m_DiskImage.m_ImageSize = m_ClusSize*m_ClusCount;
	m_DiskImage.m_ImageHighBase = m_DiskImage.m_ImageBase + m_DiskImage.m_ImageSize;
	m_PageMemory.MapImage(&m_DiskImage);
	m_ZeroBuffer = new BYTE[m_ClusSize];
	if(m_Style & PFS_FULL_DISK_CACHE)
	{
		for(DWORD Address=(DWORD)m_DiskImage.m_ImageBase;Address<(DWORD)PageCount*MP_SIZE;Address+=m_ClusSize)
		{
			ReadDiskFile(Address,m_ZeroBuffer,m_ClusSize);
		}
	}
	ZeroMemory(m_ZeroBuffer,m_ClusSize);
}

bool CPolyFS::OpenDisk(PCSTR FileName,UINT Style)
{
	m_Style = Style;
	m_DiskImage.ChangeFileIO(m_pFileIO);
	if(m_DiskImage.Open(FileName)==false)
		return false;
	PFS_HEAD PFSHead;
	if(m_DiskImage.ReadFile(&PFSHead,sizeof(PFSHead))==false)
		return false;
	if(TStrNCmp(PFSHead.Sign,"PFS",3))
	{
		m_DiskImage.Close();
		return false;
	}
	m_ClusSize = PFSHead.ClusSize;
	m_ClusCount = PFSHead.ClusCount;
	m_FatOff = PFSHead.FatEntry.BeginClus*m_ClusSize;
	m_RootEntry = PFSHead.RootEntry;
	InitParam();
	return true;
}

void CPolyFS::CloseDisk()
{
	if(m_DiskImage.IsOpened()==false)
		return;
	if((m_Style & PFS_WRITE_COPY)==0)
		m_PageMemory.FlushAllPage();
	m_PageMemory.Release();
	SafeDelete(m_ZeroBuffer);
	m_DiskImage.Close();
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//CPFSFileIO
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

CPFSFileIO::CPFSFileIO()
{
	m_pszSepar = "\\";
	m_pFileIO = NULL;
}

void CPFSFileIO::ChangeFileIO(CFileIO*pFileIO)
{
	m_pFileIO = pFileIO;
}

bool CPFSFileIO::OpenDisk(PCSTR FileName,UINT Style)
{
	m_Handle.Reset();
	m_Handle.Register();
	TList<CPolyFS>::IT Iter = m_PolyFSList.Append();
	if(m_pFileIO)
		Iter->ChangeFileIO(m_pFileIO);
	if(Iter->OpenDisk(FileName,Style)==false)
	{
		m_PolyFSList.Remove(Iter);
		return false;
	}
	return true;
}

void CPFSFileIO::CloseAllDisk()
{
	m_Handle.CloseAllHandle();
	m_PolyFSList.Clear();
}

bool CPFSFileIO::OpenFile(IN PCSTR FileName,OUT HANDLE*phFile,IN DWORD Mode)
{
	PFS_FILE_DATA FileData;
	TList<CPolyFS>::IT Iter = m_PolyFSList.Begin();
	while(Iter!=m_PolyFSList.End())
	{
		if(Iter->OpenFile(FileName,&FileData))
			break;
		Iter++;
	}
	if(Iter==m_PolyFSList.End())
		return false;
	PFS_FILE_IO_HANDLE*pHandle= new PFS_FILE_IO_HANDLE;
	pHandle->FileData = FileData;
	pHandle->pDisk = &(*Iter);
	*phFile = NUM_TO_PTR(m_Handle.CreateHandle(pHandle,PFS_HANDLE_FILE));
	return true;
}

bool CPFSFileIO::CreateFile(IN PCSTR FileName,OUT HANDLE*phFile,IN DWORD Mode)
{
	PFS_FILE_DATA FileData;
	if(m_PolyFSList.Count()==0)
		return false;
	TList<CPolyFS>::IT Iter = m_PolyFSList.Begin();
	if(Iter->CreateFile(FileName,PFS_FILE_NORMAL,0,&FileData)==false)
		return false;
	PFS_FILE_IO_HANDLE*pHandle= new PFS_FILE_IO_HANDLE;
	pHandle->FileData = FileData;
	pHandle->pDisk = &(*Iter);
	*phFile = NUM_TO_PTR(m_Handle.CreateHandle(pHandle,PFS_HANDLE_FILE));
	return true;
}

bool CPFSFileIO::CreateDir(IN PCSTR FileName)
{
	if(m_PolyFSList.Count()==0)
		return false;
	TList<CPolyFS>::IT Iter = m_PolyFSList.Begin();
	PFS_FILE_DATA FileData;
	return Iter->CreateFile(FileName,PFS_FILE_DIR,Iter->m_ClusSize,&FileData);
}

bool CPFSFileIO::CloseHandle(IN HANDLE hFile)
{
	return m_Handle.CloseHandle(PTR_TO_NUM(hFile));
}

ULSIZE CPFSFileIO::ReadFile(IN HANDLE hFile,IN void* Buffer,IN ULSIZE Size,IN ULLPOS Offset)
{
	PFS_FILE_IO_HANDLE*pHandle;
	pHandle = (PFS_FILE_IO_HANDLE*)m_Handle.GetHandleInfo(PTR_TO_NUM(hFile));
	if(pHandle==NULL)
		return 0;
	return pHandle->pDisk->ReadFile(&pHandle->FileData,(DWORD)Offset,Buffer,Size);
}

ULSIZE CPFSFileIO::WriteFile(IN HANDLE hFile,IN const void* Buffer,IN ULSIZE Size,IN ULLPOS Offset)
{
	PFS_FILE_IO_HANDLE*pHandle;
	pHandle = (PFS_FILE_IO_HANDLE*)m_Handle.GetHandleInfo(PTR_TO_NUM(hFile));
	if(pHandle==NULL)
		return 0;
	return pHandle->pDisk->WriteFile(&pHandle->FileData,(DWORD)Offset,Buffer,Size);
}

ULSIZE CPFSFileIO::ReadFile(IN HANDLE hFile,IN void* Buffer,IN ULSIZE Size)
{
	return 0;
}

ULSIZE CPFSFileIO::WriteFile(IN HANDLE hFile,IN const void* Buffer,IN ULSIZE Size)
{
	return 0;
}

ULLPOS CPFSFileIO::SetFilePointer(IN HANDLE hFile,IN LLPOS Offset,IN DWORD Pos)
{
	return 0;
}

ULLSIZE CPFSFileIO::GetFileLength(IN HANDLE hFile)
{
	DWORD RealFileLength;
	PFS_FILE_IO_HANDLE*pHandle;
	pHandle = (PFS_FILE_IO_HANDLE*)m_Handle.GetHandleInfo(PTR_TO_NUM(hFile));
	if(pHandle==NULL)
		return (ULLSIZE)-1;
	if(pHandle->FileData.ThisFileEntry.Attribute&PFS_FILE_COMPRESS)
	{
		if(pHandle->pDisk->ReadFile(&pHandle->FileData.ThisFileEntry,0,&RealFileLength,4)!=4)
			return 0;
		return RealFileLength;
	}
	return pHandle->FileData.ThisFileEntry.FileSize;
}

bool CPFSFileIO::SetFileLength(IN HANDLE hFile,IN ULLSIZE Length)
{
	PFS_FILE_IO_HANDLE*pHandle;
	pHandle = (PFS_FILE_IO_HANDLE*)m_Handle.GetHandleInfo(PTR_TO_NUM(hFile));
	if(pHandle==NULL)
		return false;
	return pHandle->pDisk->SetFileLength(&pHandle->FileData,(DWORD)Length);
}

bool CPFSFileIO::DeleteFile(IN PCSTR FileName)
{
	int Count=0;
	for(TList<CPolyFS>::IT Iter=m_PolyFSList.Begin();Iter!=m_PolyFSList.End();Iter++)
	{
		if(Iter->DeleteFile(FileName))
			Count++;
	}
	return Count>0;
}

bool CPFSFileIO::RenameFile(IN PCSTR FileName,IN PCSTR NewFileName)
{
	return 0;
}

bool CPFSFileIO::SetFileAttr(IN PCSTR FileName,DWORD Attr)
{
	DWORD PFSAttr;
	PFSAttr=0;
	if(Attr & FIO_FA_READONLY)
		PFSAttr|=PFS_FILE_READONLY;
	if(Attr & FIO_FA_SYSTEM)
		PFSAttr|=PFS_FILE_SYSTEM;
	if(Attr & FIO_FA_DIR)
		PFSAttr|=PFS_FILE_DIR;
	if(Attr & FIO_FA_HIDDEN)
		PFSAttr|=PFS_FILE_HIDDEN;
	if(Attr & FIO_FA_COMPRESS)
		PFSAttr|=PFS_FILE_COMPRESS;
	int Count=0;
	for(TList<CPolyFS>::IT Iter=m_PolyFSList.Begin();Iter!=m_PolyFSList.End();Iter++)
	{
		if(Iter->SetFileAttribute(FileName,PFSAttr))
			Count++;
	}
	return Count>0;
}

DWORD CPFSFileIO::GetFileAttr(IN PCSTR FileName)
{
	DWORD PFSAttr,FIOAttr;
	TList<CPolyFS>::IT Iter=m_PolyFSList.Begin();
	PFSAttr=PFS_FILE_ERROR;
	while(Iter!=m_PolyFSList.End())
	{
		PFSAttr = Iter->GetFileAttribute(FileName);		
		if(PFSAttr!=FIO_FA_ERROR)
			break;
		Iter++;
	}
	if(PFSAttr==PFS_FILE_ERROR)
		return FIO_FA_ERROR;
	FIOAttr = 0;
	if(PFSAttr & PFS_FILE_SYSTEM)
		FIOAttr|=FIO_FA_SYSTEM;
	if(PFSAttr & PFS_FILE_READONLY)
		FIOAttr|=FIO_FA_READONLY;
	if(PFSAttr & PFS_FILE_HIDDEN)
		FIOAttr|=FIO_FA_HIDDEN;
	if(PFSAttr & PFS_FILE_DIR)
		FIOAttr|=FIO_FA_DIR;
	if(PFSAttr & PFS_FILE_COMPRESS)
		FIOAttr|=FIO_FA_COMPRESS;
	return FIOAttr;
}

bool CPFSFileIO::IsDir(IN PCSTR FileName)
{
	PFS_FIND_DATA FindData;
	TList<CPolyFS>::IT Iter=m_PolyFSList.Begin();
	while(Iter!=m_PolyFSList.End())
	{
		if(Iter->FindFirstFile(FileName,&FindData))
			return (FindData.ThisFileEntry.Attribute & PFS_FILE_DIR)!=0;
		Iter++;
	}
	return false;
}

bool CPFSFileIO::DeleteDir(IN PCSTR FileName)
{	
	PFS_FIND_DATA FindData;
	char szBuffer[MAX_FN_LEN];
	TStrCpy(szBuffer,FileName);
	TStrCat(szBuffer,"\\*");
	TList<CPolyFS>::IT Iter=m_PolyFSList.Begin();
	while(Iter!=m_PolyFSList.End())
	{
		if(Iter->FindFirstFile(FileName,&FindData))
			break;
		Iter++;
	}
	if(Iter==m_PolyFSList.End())
		return false;
	return Iter->DeleteFile(szBuffer);
}

bool CPFSFileIO::FindFirstFile(IN PCSTR DirName,OUT FILE_FIND_DATA*pFindData)
{
	int Length;
	char szBuffer[MAX_FN_LEN];
	DWORD PFSAttr;
	PFS_FILE_IO_FIND_DATA*pPFSFindData;
	PFS_FIND_DATA FindData;
	ZeroMemory(pFindData,sizeof(FILE_FIND_DATA));
	Length = TStrCpy(szBuffer,DirName);
	if(Length && szBuffer[Length-1]=='\\')
		TStrCat(szBuffer,"*");
	else
		TStrCat(szBuffer,"\\*");

	TList<CPolyFS>::IT Iter=m_PolyFSList.Begin();
	while(Iter!=m_PolyFSList.End())
	{
		if(Iter->FindFirstFile(szBuffer,&FindData))
			break;
		Iter++;
	}
	if(Iter==m_PolyFSList.End())
		return false;

	pPFSFindData = new PFS_FILE_IO_FIND_DATA;
	pPFSFindData->FindData = FindData;
	pPFSFindData->pDisk = &(*Iter);

	pFindData->FindDataBuffer = pPFSFindData;
	TStrCpy(pFindData->FileName,pPFSFindData->FindData.FileName);
	pFindData->FileAttribute = 0;
	PFSAttr = FindData.ThisFileEntry.Attribute;
	if(PFSAttr  & PFS_FILE_READONLY)
		pFindData->FileAttribute|=FIO_FA_READONLY;
	if(PFSAttr  & PFS_FILE_HIDDEN)
		pFindData->FileAttribute|=FIO_FA_HIDDEN;
	if(PFSAttr  & PFS_FILE_SYSTEM)
		pFindData->FileAttribute|=FIO_FA_SYSTEM;
	if(PFSAttr  & PFS_FILE_DIR)
		pFindData->FileAttribute|=FIO_FA_DIR;
	if(PFSAttr  & PFS_FILE_COMPRESS)
		pFindData->FileAttribute|=FIO_FA_COMPRESS;
	pFindData->FileLength =	pPFSFindData->FindData.ThisFileEntry.FileSize;
	pFindData->hFindFile = NULL;
	return true;
}

bool CPFSFileIO::FindNextFile(INOUT FILE_FIND_DATA*pFindData)
{
	DWORD PFSAttr;
	PFS_FILE_IO_FIND_DATA*pPFSFindData;
	pPFSFindData = (PFS_FILE_IO_FIND_DATA*)pFindData->FindDataBuffer;
	if(pPFSFindData->pDisk->FindNextFile(&pPFSFindData->FindData)==false)
		return false;
	TStrCpy(pFindData->FileName,pPFSFindData->FindData.FileName);
	pFindData->FileAttribute = 0;
	PFSAttr = pPFSFindData->FindData.ThisFileEntry.Attribute;
	if(PFSAttr  & PFS_FILE_READONLY)
		pFindData->FileAttribute|=FIO_FA_READONLY;
	if(PFSAttr  & PFS_FILE_HIDDEN)
		pFindData->FileAttribute|=FIO_FA_HIDDEN;
	if(PFSAttr  & PFS_FILE_SYSTEM)
		pFindData->FileAttribute|=FIO_FA_SYSTEM;
	if(PFSAttr  & PFS_FILE_DIR)
		pFindData->FileAttribute|=FIO_FA_DIR;
	if(PFSAttr  & PFS_FILE_COMPRESS)
		pFindData->FileAttribute|=FIO_FA_COMPRESS;
	pFindData->FileLength =	pPFSFindData->FindData.ThisFileEntry.FileSize;
	pFindData->hFindFile = NULL;
	return true;
}

bool CPFSFileIO::FindClose(IN FILE_FIND_DATA*pFindData)
{
	delete (BYTE*)pFindData->FindDataBuffer;
	return true;
}

NAME_SPACE_END
