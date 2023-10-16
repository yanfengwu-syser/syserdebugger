#include "Stdafx.h"
#include "Syser.h"

DWORD dwObjectRootDirectory = 0;
WISP_CHAR *ObjectTypeName[]= {
	WSTR("Directory"),
	WSTR("Mutant"),
	WSTR("Thread"),
	WSTR("Controller"),
	WSTR("Profile"),
	WSTR("Event"),
	WSTR("Type"),
	WSTR("Section"),
	WSTR("EventPair"),
	WSTR("SymbolicLink"),
	WSTR("Timer"),
	WSTR("File"),
	WSTR("Driver"),
	WSTR("Device"),
	WSTR("Token"),
	WSTR("IoCompletion"),
	WSTR("Process"),
	WSTR("Adapter"),
	WSTR("Key"),
	WSTR("Port"),
	WSTR("Semaphore"),	
	WSTR("WmiGuid"),
	NULL,
};

bool GetFileObjectName(FILE_OBJECT* FileObject,WCHAR* ObjectName,DWORD dwBufferLen)
{
	WCHAR* Name;
	bool bOK;
	DWORD dwLen;
	ObjectName[0]=0;	
	Name = (WCHAR*)ReadDword(&FileObject->FileName.Buffer,&bOK);
	if(!bOK)
		return false;
	if(ReadWord(&FileObject->FileName.Length,(WORD*)&dwLen)==false)
		return false;
	if(dwLen==0 || Name==0)
		return false;
	dwLen>>=1;
	if(dwLen>64)
		dwLen=64;
	SyserPrivateMemCopy((BYTE *)ObjectName, (BYTE *)Name,dwLen<<1);	
	ObjectName[dwLen]=0;
	return true;
}



bool GetObjectName(DWORD ObjectHandle,WCHAR* ObjectName)
{	
	DWORD dwTmp;
	BYTE dwLen;
	WISP_CHAR *Name=NULL;
	ObjectName[0]=0;
	if(ObjectHandle==0)
		return false;
	dwLen =(BYTE) ReadByteDefaultValue((DWORD *)(ObjectHandle-0xc),0);
	if(dwLen==0)	
		return false;
	dwTmp = ObjectHandle-0x18 - dwLen;
	dwLen = ReadByteDefaultValue((DWORD *)(dwTmp+4),0);
	if(dwLen==0)
		return false;
	dwLen>>=1;
	Name = (WISP_CHAR*)ReadDwordDefaultValue((DWORD *)(dwTmp+8),0);
	if(Name==NULL)
		return false;
	if(dwLen>64)
		dwLen=64;
	SyserPrivateMemCopy((BYTE *)ObjectName, (BYTE *)Name,dwLen<<1);	
	ObjectName[dwLen] = 0;
	return true;
}
DWORD GetObjectTypeID(DWORD ObjectHandle)
{
	WISP_CHAR ObjectTypeNameBuf[64];
	int i,j;
	if(GetObjectTypeName(ObjectHandle,ObjectTypeNameBuf)==false)
		return MAX_OBJECT_TYPE;
	j = sizeof(ObjectTypeName)/sizeof(ObjectTypeName[0]);
	for(i = 0; i < j-1;i++)
	{
		if(TStrCmp(ObjectTypeName[i],ObjectTypeNameBuf)==0)
			return i;
	}
	return MAX_OBJECT_TYPE;
}
bool GetObjectTypeName(DWORD ObjectHandle,WCHAR *TypeName)
{
	WCHAR* Name;
	DWORD dwValue;
	DWORD dwLen;
	TypeName[0]=0;

	dwValue = ReadDwordDefaultValue((DWORD *)(ObjectHandle-0x10),0);
	if(dwValue==0)
		return false;
	Name=(WCHAR*)ReadDwordDefaultValue ((void*)(dwValue+0x44),0);
	if(Name==NULL)
		return false;
	dwLen = ReadWordDefaultValue ((void*)(dwValue+0x40),0);
	if(dwLen==0)
		return false;
	dwLen>>=1;
	if(dwLen>64)
		dwLen=64;
	SyserPrivateMemCopy((BYTE *)TypeName, (BYTE *)Name,dwLen<<1);	
	TypeName[dwLen]=0;
	return true;
}

bool FindFirstObject(WISP_CHAR *ObjectName,OBJFINDDATA &FindData)
{
	if(ObjectName==NULL)
	{
		FindData.ObjectHandle=GetObjectRootDirectoryHandle();
		FindData.ReturnObjectHandle=0;
		FindData.NextObjectPointer=NULL;
		FindData.DirectoryItemIndex=0;
		return true;
	}
	return false;
}
bool FindNextObject(OBJFINDDATA &FindData)
{	
	int i;
	DWORD ObjectHandle;
	PObjectPointer Pointer;
	if(FindData.ObjectHandle==0)
	{
		if(FindFirstObject(NULL,FindData)==false)
			return false;
	}
	for(;FindData.DirectoryItemIndex<0x25;FindData.DirectoryItemIndex++)
	{		
		if(FindData.NextObjectPointer)
		{
			FindData.ReturnObjectHandle = ReadDwordDefaultValue(&FindData.NextObjectPointer->ObjectHandle,0);
			FindData.NextObjectPointer = (PObjectPointer)ReadDwordDefaultValue((DWORD*)&FindData.NextObjectPointer->Next,0);
		}else
		{
			Pointer = (PObjectPointer)ReadDwordDefaultValue((DWORD*)& FindData.ObjectDirectoryTablePointer->Pointer[FindData.DirectoryItemIndex],0);
			if(Pointer==NULL)
				continue;
			FindData.ReturnObjectHandle = ReadDwordDefaultValue(&Pointer->ObjectHandle,0);			
			FindData.NextObjectPointer = (PObjectPointer)ReadDwordDefaultValue((DWORD*)&Pointer->Next,0);
		}
		if(FindData.NextObjectPointer==NULL)
			FindData.DirectoryItemIndex++;
		return true;
	}
	return false;
}
DWORD dwListObjectCounter = 0;

bool ListObject(OBJFINDDATA &FindData,DWORD ObjectType,ObjectOperatorCallBack CallBack,WISP_CHAR **Name)
{
	OBJFINDDATA CurFindData;
	while(FindNextObject(FindData))
	{
		
		if(GetObjectTypeID(FindData.ReturnObjectHandle)==ObjectType)
		{
			if(CallBack!=NULL)
				if(CallBack(FindData.ReturnObjectHandle,Name)==false)
					return false;			
		}
		if(IsDirectoryObjectType(FindData.ReturnObjectHandle))
		{
			CurFindData.ObjectHandle=FindData.ReturnObjectHandle;
			CurFindData.DirectoryItemIndex=0;
			CurFindData.NextObjectPointer=NULL;
			if(ListObject(CurFindData,ObjectType,CallBack,Name)==false)
				return false;
		}
	}
	return true;
}

DWORD GetObjectRootDirectoryHandle()
{
	if(dwObjectRootDirectory==0)		
		InitObjectDirectory();
	return dwObjectRootDirectory;
}

DWORD GetObjectDirectoryHandleByName(WISP_CHAR * Name,DWORD dwParentDirectoryHandle)
{
	WISP_CHAR PathSeparator='\\';
	WISP_CHAR *SubDirName = NULL;
	WISP_CHAR ObjectName[MAX_PATH+1];
	WISP_CHAR PathName[MAX_PATH+1];
	WISP_CHAR *DirectoryName=PathName;		
	//DWORD dwSum,dwOldSum;
	DWORD *Pointer;	
	DWORD dwStrLen,i,dwLen,dwTmpValue;
	PObjectPointer PObjPointer;

	
	if(Name==NULL)
		return 0;
	dwTmpValue = TStrLen(Name);
	if(dwTmpValue>=MAX_PATH)
		return 0;
	ObjectName[MAX_PATH]=0;
	PathName[MAX_PATH]=0;
	TStrCpyLimit(DirectoryName,Name,MAX_PATH);
	if(dwParentDirectoryHandle==0)
		dwParentDirectoryHandle=GetObjectRootDirectoryHandle();
	if(DirectoryName[0]==PathSeparator)
		DirectoryName++;
	dwStrLen = TStrLen(DirectoryName);
	for(i = 0; i < dwStrLen && DirectoryName[0]==PathSeparator;i++,DirectoryName++);
	SubDirName = TStrChr(DirectoryName,PathSeparator);	
	while(SubDirName!=NULL)
	{			
		SubDirName[0]=0;
		dwParentDirectoryHandle = GetChildObjectHandleByName(DirectoryName,dwParentDirectoryHandle);
		if(dwParentDirectoryHandle==0)
			return 0;		
		if(IsDirectoryObjectType(dwParentDirectoryHandle)==false)
			return 0;
		DirectoryName = SubDirName+1;
		dwStrLen = TStrLen(DirectoryName);
		for(i = 0; i < dwStrLen && DirectoryName[0]==PathSeparator;i++,DirectoryName++);
		SubDirName = TStrChr(DirectoryName,PathSeparator);
	}	
	return GetChildObjectHandleByName(DirectoryName,dwParentDirectoryHandle);
}
bool IsDirectoryObjectType(DWORD ObjectHandle)
{
	DWORD dwTypeId = GetObjectTypeID(ObjectHandle);
	return dwTypeId==DIRECTORY_OBJECT_TYPE;	
}
DWORD GetChildObjectHandleByName(WISP_CHAR * DirectoryName,DWORD dwParentDirectoryHandle)
{
	WISP_CHAR PathSeparator='\\';
	WISP_CHAR *SubDirName = NULL;
	WISP_CHAR ObjectName[MAX_PATH+1];
	DWORD dwSum,dwOldSum;
	DWORD *Pointer;
	DWORD dwTmpValue;
	DWORD dwLen;
	PObjectPointer PObjPointer;
	int i;

	if(DirectoryName==NULL)
		return 0;		
	if(dwParentDirectoryHandle==0)
		dwParentDirectoryHandle=GetObjectRootDirectoryHandle();
	dwLen = TStrLen(DirectoryName);
	for(i = 0; i < (int)dwLen && DirectoryName[0]==PathSeparator;i++,DirectoryName++);	
	dwLen	= TStrLen(DirectoryName);
	if(dwLen==0)
		return 0;
	dwSum = 0;
	for(i = 0; i < (int)dwLen; i++)
	{			
		dwOldSum = dwSum;
		dwSum >>=1;
		dwOldSum *= 3;
		dwSum += dwOldSum;
		dwTmpValue = DirectoryName[i];
		if(dwTmpValue>='a' && dwTmpValue <='z')
			dwTmpValue-=0x20;
		dwSum+=dwTmpValue;
	}
	dwSum %= 0x25;			
	PObjPointer = (PObjectPointer)ReadDwordDefaultValue((DWORD*)(dwParentDirectoryHandle+dwSum*4),0);
	while(PObjPointer!=NULL)
	{						
		dwTmpValue = ReadDwordDefaultValue(&PObjPointer->ObjectHandle,0);
		if(dwTmpValue==0)
			return 0;
		if(GetObjectName(dwTmpValue,ObjectName)==true)
		{
			if(TStrICmp(ObjectName,DirectoryName)==0)
				return dwTmpValue;
		}
		PObjPointer = (PObjectPointer)ReadDwordDefaultValue((DWORD *)&PObjPointer->Next,0);
	}
	return 0;
}
DWORD GetObjectHeader(DWORD ObjectHandle)
{
	BYTE Len;
	Len =ReadByteDefaultValue((DWORD *)(ObjectHandle-0xc),0);
	return ObjectHandle-0x18 - Len;
}
bool InitObjectDirectory()
{	
	PVOID				pObject;	
	HANDLE				Handle;
	NTSTATUS			Status;	
	UNICODE_STRING		RootDirectory;
	OBJECT_ATTRIBUTES	ObjAtt;

	if(dwObjectRootDirectory)
		return true;		
	RtlInitUnicodeString(&RootDirectory,OBJECT_ROOT_DIRECTORY);	
	ObjAtt.Length=sizeof(OBJECT_ATTRIBUTES);
	ObjAtt.ObjectName=&RootDirectory;
	ObjAtt.SecurityDescriptor=0;
	ObjAtt.Attributes=0x40;
	ObjAtt.SecurityQualityOfService=0;
	ObjAtt.RootDirectory=0;	
	Status =ZwOpenDirectoryObject(&Handle,1,&ObjAtt);
	if (!NT_SUCCESS(Status))
	{
		::DbgPrint("ZwOpenDirectoryObject Fault");
		return false;
	}
	Status = ObReferenceObjectByHandle(Handle,1,0,0,(PVOID*)&dwObjectRootDirectory,0);
	if (!NT_SUCCESS(Status))
	{
		::DbgPrint("ObReferenceObjectByHandle Fault");
		ZwClose(Handle);
		return false;
	}
	ObfDereferenceObject((PVOID)dwObjectRootDirectory);
	ZwClose(Handle);
	return true;
}

