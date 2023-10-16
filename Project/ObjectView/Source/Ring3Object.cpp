#include "Stdafx.h"
#include "Ring3Object.h"

static HMODULE hNtdllModule=NULL;

PZWCLOSE pZwClose=NULL;
PZWOPENFILE pZwOpenFile=NULL;
PZWOPENSECTION pZwOpenSection=NULL;
PZWQUERYOBJECT pZwQueryObject=NULL;
PRTLINITUNICODESTRING pRtlInitUnicodeString=NULL;
PZWOPENDIRECTORYOBJECT pZwOpenDirectoryObject=NULL;
PZWQUERYDIRECTORYOBJECT pZwQueryDirectoryObject=NULL;
PZWQUERYSYSTEMINFORMATION pZwQuerySystemInformation=NULL;
PZWOPENSYMBOLICLINKOBJECT pZwOpenSymbolicLinkObject=NULL;
PZWQUERYSYMBOLICLINKOBJECT pZwQuerySymbolicLinkObject=NULL;
bool UnloadAPI()
{
	if(hNtdllModule)
		FreeLibrary(hNtdllModule);
	return TRUE;
}

bool LoadAPI()
{
	hNtdllModule = GetModuleHandle("ntdll.dll");
	if(!hNtdllModule)
		return false;
	pZwClose = (PZWCLOSE)GetProcAddress(hNtdllModule,"ZwClose");
	if(!pZwClose)
		return false;
	pZwQuerySystemInformation = (PZWQUERYSYSTEMINFORMATION)GetProcAddress(hNtdllModule,"ZwQuerySystemInformation");
	if(!pZwQuerySystemInformation)
		return false;
	pZwOpenSection = (PZWOPENSECTION)GetProcAddress(hNtdllModule,"ZwOpenSection");	
	if(!pZwOpenSection)
		return false;
	pZwOpenFile = (PZWOPENFILE)GetProcAddress(hNtdllModule,"ZwOpenFile");
	if(!pZwOpenFile)
		return false;
	pRtlInitUnicodeString = (PRTLINITUNICODESTRING)GetProcAddress(hNtdllModule,"RtlInitUnicodeString");	
	if(!pRtlInitUnicodeString)
		return false;
	pZwQueryObject = (PZWQUERYOBJECT)GetProcAddress(hNtdllModule,"ZwQueryObject");
	if(!pZwQueryObject)
		return false;
	pZwOpenDirectoryObject = (PZWOPENDIRECTORYOBJECT)GetProcAddress(hNtdllModule,"ZwOpenDirectoryObject");
	if(!pZwOpenDirectoryObject)
		return false;
	pZwQueryDirectoryObject = (PZWQUERYDIRECTORYOBJECT)GetProcAddress(hNtdllModule,"ZwQueryDirectoryObject");
	if(!pZwQueryDirectoryObject)
		return false;
	pZwOpenSymbolicLinkObject = (PZWOPENSYMBOLICLINKOBJECT)GetProcAddress(hNtdllModule,"ZwOpenSymbolicLinkObject");
	if(!pZwOpenSymbolicLinkObject)
		return false;
	pZwQuerySymbolicLinkObject = (PZWQUERYSYMBOLICLINKOBJECT)GetProcAddress(hNtdllModule,"ZwQuerySymbolicLinkObject");
	if(!pZwQuerySymbolicLinkObject)
		return false;
	return true;
}
bool GetSymbolicLink(WCHAR* LinkName,OUT UNICODE_STRING* LinkTargetName,OUT PULONG ReturnLength)
{
	NTSTATUS NTStatus;
	HANDLE SymbolicHandle=NULL;
	UNICODE_STRING UnicodeString;
	OBJECT_ATTRIBUTES ObjectAttributes;
	if(pRtlInitUnicodeString==NULL)
		if(LoadAPI()==false)
			return false;
	if(pRtlInitUnicodeString)
		pRtlInitUnicodeString(&UnicodeString,LinkName);
	InitializeObjectAttributes(&ObjectAttributes,&UnicodeString,OBJ_CASE_INSENSITIVE,0,NULL);
	NTStatus = pZwOpenSymbolicLinkObject(&SymbolicHandle,SYMBOLIC_LINK_QUERY,&ObjectAttributes);
	if(NTStatus)
		return false;
	
	NTStatus = pZwQuerySymbolicLinkObject(SymbolicHandle,LinkTargetName,ReturnLength);
	if(NTStatus)
	{
		pZwClose(SymbolicHandle);
		return false;
	}
	pZwClose(SymbolicHandle);
	return true;
}


bool FindFirstObject(WCHAR* DirectoryName,INOUT PFIND_OBJECT_DATA pFindData)
{
	NTSTATUS NTStatus;
	UNICODE_STRING DirString;
	HANDLE DirectoryHandle=NULL;
	OBJECT_ATTRIBUTES ObjectAttributes;
	pRtlInitUnicodeString(&DirString,DirectoryName);
	pFindData->FindDataBuffer = new FINDDATABUF;
	memset(pFindData->FindDataBuffer,0,sizeof(FINDDATABUF));
	pFindData->CurrentDirName = new WCHAR[TStrLen(DirectoryName)+1];
	TStrCpy(pFindData->CurrentDirName,DirectoryName);
	InitializeObjectAttributes(&ObjectAttributes,&DirString,OBJ_CASE_INSENSITIVE,0,NULL);
	NTStatus = pZwOpenDirectoryObject(&pFindData->FindHandle,DIRECTORY_QUERY,&ObjectAttributes);
	if(NTStatus)
	{
		delete pFindData->FindDataBuffer;
		delete pFindData->CurrentDirName;
		pFindData->FindHandle=NULL;
		return false;
	}
	NTStatus = pZwQueryDirectoryObject(pFindData->FindHandle,pFindData->FindDataBuffer,sizeof(FINDDATABUF),TRUE,TRUE,&pFindData->Context,&pFindData->NameMaxLen);
	if(NTStatus)
	{
		pZwClose(pFindData->FindHandle);
		delete pFindData->FindDataBuffer;
		delete pFindData->CurrentDirName;
		pFindData->FindHandle=NULL;
		return false;
	}
	return true;
}
bool FindNextObject(INOUT PFIND_OBJECT_DATA pFindData)
{
	NTSTATUS NTStatus;
	NTStatus = pZwQueryDirectoryObject(pFindData->FindHandle,pFindData->FindDataBuffer,sizeof (FINDDATABUF),TRUE,FALSE,&pFindData->Context,&pFindData->NameMaxLen);
	if(NTStatus)
		return false;
	return true;
}
void CloseFindObject(PFIND_OBJECT_DATA pFindData)
{
	if(pFindData->FindHandle)
	{
		pZwClose(pFindData->FindHandle);
		pFindData->FindHandle=NULL;
	}
	delete pFindData->FindDataBuffer;
	delete pFindData->CurrentDirName;
	return;
}