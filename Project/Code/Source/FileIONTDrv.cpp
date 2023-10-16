#include "StdAfx.h"
#include "FileIO.h"

NAME_SPACE_BEGIN

WCHAR CLocalFileIO::m_CurDirName[MAX_FN_LEN];

void CLocalFileIO::SetCurDir(IN PCWSTR DirName)
{
	int Length;
	Length=TStrCpy(m_CurDirName,DirName);
	if(Length && m_CurDirName[Length-1]!='\\' && m_CurDirName[Length-1]!='/')
	{
		m_CurDirName[Length] = '\\';
		m_CurDirName[Length+1]=0;
	}
}

#define NT_FILE_OPEN_OPTION		(FILE_RANDOM_ACCESS|FILE_NON_DIRECTORY_FILE|FILE_SYNCHRONOUS_IO_NONALERT|FILE_COMPLETE_IF_OPLOCKED)

bool CLocalFileIO::OpenFile(IN PCSTR FileName,INOUT HANDLE*phFile,IN DWORD Mode)
{
	ANSI_STRING	AnsiName;
	UNICODE_STRING UniName;
	IO_STATUS_BLOCK IOStatus;
	OBJECT_ATTRIBUTES oa;
	int Length;
	ULONG   ShareMode;
	ACCESS_MASK  DesiredAccess;
	WCHAR szBuffer[MAX_FN_LEN];
	if(*FileName!='\\' && TStrChr(FileName,':')==NULL)
		Length = TStrCpy(szBuffer,m_CurDirName);
	else
		Length = 0;
	AnsiName.Buffer = (PCHAR)FileName;
	AnsiName.Length = (USHORT)TStrLen(FileName);
	AnsiName.MaximumLength = AnsiName.Length+1;
	UniName.Buffer = &szBuffer[Length];
	UniName.Length = 0;
	UniName.MaximumLength =sizeof(WCHAR)*MAX_FN_LEN - Length*sizeof(WCHAR);
	RtlAnsiStringToUnicodeString(&UniName,&AnsiName,false);

	UniName.Buffer = szBuffer;
	UniName.Length = TStrLen(szBuffer)*sizeof(WCHAR);
	UniName.MaximumLength = sizeof(WCHAR)*MAX_FN_LEN;

	InitializeObjectAttributes(&oa,&UniName,OBJ_KERNEL_HANDLE|OBJ_CASE_INSENSITIVE,NULL,NULL);
	DesiredAccess = GENERIC_READ;
	if(Mode & FIO_WRITE)
		DesiredAccess |= GENERIC_WRITE;
	ShareMode=0;
	if(Mode & FIO_SHARE_READ)
		ShareMode |= FILE_SHARE_READ;
	if(Mode & FIO_SHARE_WRITE)
		ShareMode |= FILE_SHARE_WRITE;
	return ZwOpenFile(phFile,DesiredAccess,&oa,&IOStatus,ShareMode,NT_FILE_OPEN_OPTION)==STATUS_SUCCESS;
}

bool CLocalFileIO::OpenFile(PUNICODE_STRING FullImageName,OUT HANDLE*phFile,IN DWORD Mode)
{
	OBJECT_ATTRIBUTES oa;
	IO_STATUS_BLOCK	IOStatus;
	ACCESS_MASK  DesiredAccess;
	ULONG ShareMode;
	InitializeObjectAttributes(&oa,FullImageName, OBJ_KERNEL_HANDLE|OBJ_CASE_INSENSITIVE, NULL, NULL);
	DesiredAccess = GENERIC_READ;
	if(Mode & FIO_WRITE)
		DesiredAccess |= GENERIC_WRITE;
	ShareMode = 0;
	if(Mode & FIO_SHARE_READ)
		ShareMode |= FILE_SHARE_READ;
	if(Mode & FIO_SHARE_WRITE)
		ShareMode |= FILE_SHARE_WRITE;
	return ZwOpenFile(phFile,DesiredAccess,&oa,&IOStatus,ShareMode,NT_FILE_OPEN_OPTION)==STATUS_SUCCESS;
}

bool CLocalFileIO::CreateFile(IN PCSTR FileName,INOUT HANDLE*phFile,IN DWORD Mode)
{
	ANSI_STRING	AnsiName;
	UNICODE_STRING UniName;
	OBJECT_ATTRIBUTES oa;
	IO_STATUS_BLOCK	IOStatus;
	int Length;
	ULONG CreateMode,ShareMode;
	WCHAR NameBuf[MAX_FN_LEN];
	if(*FileName!='\\' && TStrChr(FileName,':')==NULL)
		Length = TStrCpy(NameBuf,m_CurDirName);
	else
		Length = 0;
	AnsiName.Buffer = (PCHAR)FileName;
	AnsiName.Length = (USHORT)TStrLen(FileName);
	AnsiName.MaximumLength = AnsiName.Length+1;
	UniName.Buffer = &NameBuf[Length];
	UniName.Length = 0;
	UniName.MaximumLength = MAX_FN_LEN*sizeof(WCHAR) - Length*sizeof(WCHAR);
	RtlAnsiStringToUnicodeString(&UniName,&AnsiName,false);
	UniName.Buffer = NameBuf;
	UniName.Length = TStrLen(NameBuf)*sizeof(WCHAR);
	UniName.MaximumLength = MAX_FN_LEN*sizeof(WCHAR);

	InitializeObjectAttributes(&oa,&UniName, OBJ_KERNEL_HANDLE|OBJ_CASE_INSENSITIVE, NULL, NULL);
	CreateMode = FILE_CREATE;
	if(Mode & FIO_CREATE)
		CreateMode = FILE_OVERWRITE_IF;
	ShareMode=0;
	if(Mode & FIO_SHARE_READ)
		ShareMode |= FILE_SHARE_READ;
	if(Mode & FIO_SHARE_WRITE)
		ShareMode |= FILE_SHARE_WRITE;
	return ZwCreateFile(phFile,GENERIC_READ|GENERIC_WRITE,&oa,&IOStatus,NULL,FILE_ATTRIBUTE_NORMAL,ShareMode,CreateMode,NT_FILE_OPEN_OPTION,NULL,0)==STATUS_SUCCESS;
}

bool CLocalFileIO::CloseHandle(HANDLE hFile)
{
	return ZwClose(hFile)==STATUS_SUCCESS;
}

ULSIZE CLocalFileIO::ReadFile(HANDLE hFile,void* Buffer,ULSIZE Size,ULLPOS Offset)
{
	IO_STATUS_BLOCK	IOStatus;
	LARGE_INTEGER Offset64;
	Offset64.LowPart = LOW_DWORD(Offset);
	Offset64.HighPart = HIGH_DWORD(Offset);
	if(ZwReadFile(hFile,NULL,NULL,NULL,&IOStatus,Buffer,Size,&Offset64,NULL)!=STATUS_SUCCESS)
		return 0;
	return (ULSIZE)IOStatus.Information;
}

ULSIZE CLocalFileIO::WriteFile(HANDLE hFile,const void* Buffer,ULSIZE Size,ULLPOS Offset)
{
	IO_STATUS_BLOCK	IOStatus;
	LARGE_INTEGER Offset64;
	Offset64.LowPart = LOW_DWORD(Offset);
	Offset64.HighPart = HIGH_DWORD(Offset);
	if(ZwWriteFile(hFile,NULL,NULL,NULL,&IOStatus,(void*)Buffer,Size,&Offset64,NULL)!=STATUS_SUCCESS)
		return 0;
	return (ULSIZE)IOStatus.Information;
}

ULLSIZE CLocalFileIO::GetFileLength(HANDLE hFile)
{
	IO_STATUS_BLOCK	IOStatus;
	FILE_STANDARD_INFORMATION StdInfo;
	if(ZwQueryInformationFile(hFile,&IOStatus,&StdInfo,sizeof(FILE_STANDARD_INFORMATION),FileStandardInformation)!=STATUS_SUCCESS)
		return 0;
	return (ULLSIZE)StdInfo.EndOfFile.QuadPart;
}

bool CLocalFileIO::SetFileLength(HANDLE hFile,ULLSIZE Length)
{
	IO_STATUS_BLOCK	IOStatus;
	FILE_END_OF_FILE_INFORMATION feofi;
	feofi.EndOfFile.QuadPart = (LONGLONG)Length;
	return ZwSetInformationFile(hFile,&IOStatus,&feofi,sizeof(FILE_END_OF_FILE_INFORMATION),FileEndOfFileInformation)==STATUS_SUCCESS;
}

bool CLocalFileIO::DeleteFile(PCSTR FileName)
{
	return false;
}

bool CLocalFileIO::RenameFile(IN PCSTR FileName,IN PCSTR NewFileName)
{
	return false;
}

bool CLocalFileIO::OpenDirectory(IN PCSTR FileName,INOUT HANDLE*phFile,IN DWORD Mode)
{
	NTSTATUS Status;
	OBJECT_ATTRIBUTES	oa;
	IO_STATUS_BLOCK		IOStatus;
	int Length;
	ANSI_STRING	AnsiName;
	UNICODE_STRING UniName;
	WCHAR NameBuf[MAX_FN_LEN];
	if(*FileName!='\\' && TStrChr(FileName,':')==NULL)
		Length = TStrCpy(NameBuf,m_CurDirName);
	else
		Length = 0;
	AnsiName.Buffer = (PCHAR)FileName;
	AnsiName.Length = (USHORT)TStrLen(FileName);
	AnsiName.MaximumLength = AnsiName.Length+1;
	UniName.Buffer = &NameBuf[Length];
	UniName.Length = 0;
	UniName.MaximumLength = MAX_FN_LEN*sizeof(WCHAR) - Length*sizeof(WCHAR);
	RtlAnsiStringToUnicodeString(&UniName,&AnsiName,false);
	UniName.Buffer = NameBuf;
	UniName.Length = TStrLen(NameBuf)*sizeof(WCHAR);
	UniName.MaximumLength = MAX_FN_LEN*sizeof(WCHAR);

	InitializeObjectAttributes(&oa,&UniName, OBJ_KERNEL_HANDLE|OBJ_CASE_INSENSITIVE, NULL, NULL);	
	Status = ZwOpenFile(phFile,Mode,&oa,&IOStatus,FILE_SHARE_WRITE|FILE_SHARE_DELETE|FILE_SHARE_READ,FILE_DIRECTORY_FILE);	
	return Status==STATUS_SUCCESS;
}

bool CLocalFileIO::FindFirstFile(IN PCSTR DirName,OUT FILE_FIND_DATA*pFindData)
{
	IO_STATUS_BLOCK		IOStatus;
	NTSTATUS Status;
	DWORD BufferLength=MAX_FN_LEN*sizeof(WCHAR)+sizeof(CODEFILE_NAMES_INFORMATION)+sizeof(FILE_STANDARD_INFORMATION);
	KEVENT Event;
	char *OrgDirName;
	PCODEFILE_NAMES_INFORMATION pFileNamesInformation;
	if(pFindData==NULL)
		return  false;
	memset(pFindData,0,sizeof(FILE_FIND_DATA));
	*pFindData->FileName=0;
	if(KeGetCurrentIrql()>PASSIVE_LEVEL)	
		return false;	
	if(OpenDirectory(DirName,&pFindData->hFindFile,FILE_LIST_DIRECTORY|FILE_ALL_ACCESS)==false)	
		return false;
	pFileNamesInformation =(PCODEFILE_NAMES_INFORMATION) new char [BufferLength];
	if(pFileNamesInformation==NULL)
		return false;
	OrgDirName = new char[MAX_FN_LEN];
	if(OrgDirName==NULL)
	{
		delete []pFileNamesInformation;
		ZwClose(pFindData->hFindFile);
		return false;
	}
	TStrCpyLimit(OrgDirName,DirName,MAX_FN_LEN);
	pFindData->FindDataBuffer=OrgDirName;
	KeInitializeEvent(&Event, SynchronizationEvent,FALSE);	
	memset(pFileNamesInformation,0,BufferLength);
	Status = ZwQueryDirectoryFile(pFindData->hFindFile,NULL,ZwQueryDirectoryFileApc,&Event,&IOStatus,pFileNamesInformation,BufferLength-2,
		FileNamesInformation,TRUE,NULL,TRUE);
	if (Status == STATUS_PENDING) 	
		KeWaitForSingleObject(&Event, UserRequest,KernelMode, TRUE, NULL);
	if(IOStatus.Status)
	{	
		ZwClose(pFindData->hFindFile);	
		delete []pFileNamesInformation;
		return false;
	}	
	TStrCpyLimit(pFindData->FileName,pFileNamesInformation->FileName,MAX_FN_LEN);
	if(TStrCmp(pFindData->FileName,".")==0 || TStrCmp(pFindData->FileName,"..")==0)
		pFindData->FileAttribute |= FIO_FA_DIR;
	else
	{
		//TODO:
		if(IsDir(pFindData->FileName))
			pFindData->FileAttribute |= FIO_FA_DIR;
		else 
			pFindData->FileAttribute &= (~FIO_FA_DIR);
	}
	delete []pFileNamesInformation;
	return true;
}

bool CLocalFileIO::FindNextFile(INOUT FILE_FIND_DATA*pFindData)
{
	IO_STATUS_BLOCK		IOStatus;
	NTSTATUS Status;
	DWORD BufferLength=MAX_FN_LEN*sizeof(WCHAR)+sizeof(CODEFILE_NAMES_INFORMATION)+sizeof(FILE_STANDARD_INFORMATION);
	KEVENT Event;
	char *TempFileName;
	PCODEFILE_NAMES_INFORMATION pFileNamesInformation;

	*pFindData->FileName=0;
	if(KeGetCurrentIrql()>PASSIVE_LEVEL)	
		return false;	
	
	KeInitializeEvent(&Event, SynchronizationEvent,FALSE);
	pFileNamesInformation = (PCODEFILE_NAMES_INFORMATION)new char [BufferLength];
	if(pFileNamesInformation==NULL)
		return false;
	memset(pFileNamesInformation,0,BufferLength);
	Status = ZwQueryDirectoryFile(pFindData->hFindFile,NULL,ZwQueryDirectoryFileApc,&Event,&IOStatus,pFileNamesInformation,BufferLength-2,
		FileNamesInformation,TRUE,NULL,FALSE);
	if (Status == STATUS_PENDING)
		KeWaitForSingleObject(&Event, UserRequest,KernelMode, TRUE, NULL);
	if(IOStatus.Status)	
	{
		delete []pFileNamesInformation;
		return false;
	}
	
	TStrCpyLimit(pFindData->FileName,pFileNamesInformation->FileName,MAX_FN_LEN);
	pFindData->FileAttribute=FIO_FA_NORMAL;
	if(TStrCmp(pFindData->FileName,".")==0 || TStrCmp(pFindData->FileName,"..")==0)
		pFindData->FileAttribute |= FIO_FA_DIR;
	else
	{
		TempFileName=(char*)pFileNamesInformation;
		char * OrgDirName = (char*)pFindData->FindDataBuffer;
		TStrCpy(TempFileName,OrgDirName);
		int len = strlen(OrgDirName);
		if(OrgDirName[len-1]!='\\')
			TStrCat(TempFileName,"\\");
		TStrCat(TempFileName,pFindData->FileName);
		if(IsDir(TempFileName))
			pFindData->FileAttribute|=FIO_FA_DIR;
	}		
	delete []pFileNamesInformation;
	return true;
}

bool CLocalFileIO::FindClose(IN FILE_FIND_DATA*pFindData)
{
	*pFindData->FileName=0;
	CloseHandle(pFindData->hFindFile);
	if(pFindData->FindDataBuffer)
	{
		delete []pFindData->FindDataBuffer;
		pFindData->FindDataBuffer=NULL;
	}
	return true;
}

bool CLocalFileIO::IsDir(IN HANDLE hFile)
{
	NTSTATUS Status;
	IO_STATUS_BLOCK	IOStatus;
	FILE_STANDARD_INFORMATION StdInfo;
	Status = ZwQueryInformationFile(hFile,&IOStatus,&StdInfo,sizeof(FILE_STANDARD_INFORMATION),FileStandardInformation);
	if(Status)
		return false;
	return StdInfo.Directory==TRUE;
}

bool CLocalFileIO::IsDir(IN PCSTR FileName)
{
	HANDLE hFile;
	bool bOK;
	bOK = OpenDirectory(FileName,&hFile,FILE_LIST_DIRECTORY);
	if(bOK)
		CloseHandle(hFile);
	return bOK;
}

CLocalFileIO*	gpFileIO = NULL;

NAME_SPACE_END
VOID NTAPI ZwQueryDirectoryFileApc (IN PVOID ApcContext,IN PIO_STATUS_BLOCK IoStatusBlock,IN ULONG Reserved )
{	
	KeSetEvent(PRKEVENT (ApcContext),0,false);
	return;
}

