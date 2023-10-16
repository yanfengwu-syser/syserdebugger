#include "StdAfx.h"
#include "ModifyBoot.h"
#include "../../Syser/Source/Ring3Object.h"

int DisableNOGUIBOOT(bool Switch)
{
	CLocalFileIO FileIO;
	char KeyName[1024];
	HANDLE hFile;
	char BufferString[1024];
	char FileName[50]="c:\\boot.ini";
	char*Name,*Tmp;
	DWORD Len,DriverBitMask,DriverType;
	bool bFind=false;
	DWORD Attr;
	int i,RetValue;
	Len = TStrLen(FileName)+1;
	RetValue=0;
	if(GetBootINIKeyName(KeyName,sizeof(KeyName))==false)
		return false;
	DriverBitMask = GetLogicalDrives();
	DriverBitMask>>=2;
	for(i='c';i<='z';i++,DriverBitMask>>=1)
	{
		if((DriverBitMask&1)==0)continue;
		TSPrintf(FileName,"%c:\\",i);
		DriverType = GetDriveType(FileName);
		if(DriverType!=DRIVE_FIXED)continue;
		TSPrintf(FileName,"%c:\\boot.ini",i);
		if(FileIO.OpenFile(FileName,&hFile,FIO_READ))
		{
			RetValue++;
			FileIO.CloseHandle(hFile);
			Attr = ::GetFileAttributes(FileName);
			Len = GetPrivateProfileString("operating systems",KeyName,NULL,BufferString,sizeof(BufferString),FileName);
			if(Len==0)
				continue;
			if(Switch)
			{
				if(TStrIStr(BufferString,"/noguiboot")==0)
				{
					Len = TStrLen(BufferString);
					while(Len >=1 && (BufferString[Len-1]==' '||BufferString[Len-1]=='\t'))Len--;
					SetFileAttributes(FileName,FILE_ATTRIBUTE_NORMAL);
					TStrCat(&BufferString[Len]," /noguiboot");
					WritePrivateProfileString("operating systems",KeyName,BufferString,FileName);
					SetFileAttributes(FileName,Attr);
				}
			}
			else 
			{
				Name = BufferString;
				do 
				{
					Name = TStrIStr(Name,"/noguiboot");
					if(Name==NULL)
						break;
					Tmp = Name;
					while(Name[10])
						Name[0]=Name[10],Name++;
					Name[0]=0;
					bFind=true;
					Name=Tmp;
				}while(Name);
				if(bFind)
				{
					SetFileAttributes(FileName,FILE_ATTRIBUTE_NORMAL);
					WritePrivateProfileString("operating systems",KeyName,BufferString,FileName);
					SetFileAttributes(FileName,Attr);
				}
			}
		}
	}
	return RetValue;
}

bool GetBootINIKeyName(char* RetKeyName,DWORD RetKeyLen)
{
	DWORD KeyLen;
	WCHAR *KeyName;
	DWORD InputLen;
	char WindowsDirectoryName[MAX_PATH];
	int RetLen,Len = sizeof(WindowsDirectoryName);
	char* DirectoryName;
	char DiskNum;
	RetLen = GetWindowsDirectory(WindowsDirectoryName,Len);
	if(RetLen == 0||RetLen>=Len)
		return false;
	DirectoryName = TStrChr(WindowsDirectoryName,'\\');
	if(DirectoryName==NULL||DirectoryName[1]=='\0')
		return false;
	DiskNum = WindowsDirectoryName[0];
	DiskNum&=0xdf;
	if(DiskNum<'A' || DiskNum >'Z')
		return false;
	InputLen = 8192;
	KeyName =(WCHAR*) new char[InputLen];
	KeyLen = GetBootIniKeyNameByDiskNum(DiskNum,KeyName,InputLen);
	if(KeyLen*sizeof(WCHAR)>=InputLen || KeyLen==0)
		goto errorquit;
	TStrCat(KeyName,DirectoryName);
	KeyLen = TStrLen(KeyName);
	if(KeyLen+1>RetKeyLen)
		goto errorquit;
	TStrCpy(RetKeyName,KeyName);
	delete []KeyName;
	return true;
errorquit:
	delete []KeyName;
	return false;
}

int GetBootIniKeyNameByDiskNum(DWORD PhysicalDiskNumber,WCHAR *RetName,DWORD BufRetLen)
{
	WCHAR NameBuffer[260];
	WCHAR DirectoryNameBuf[260];
	WCHAR DirectoryEntryName[4096];
	WCHAR LinkNameBuf[4096];
	NTSTATUS NTStatus;
	BOOL RestartScan=TRUE;
	UNICODE_STRING DirectoryName;
	ULONG Context=0,ReturnLength=0;
	HANDLE DirectoryHandle=NULL,SymbolicHandle=NULL;
	//OBJECT_ATTRIBUTES ObjectAttributes;
	PDIRECTORY_BASIC_INFORMATION pDirectoryBaseInformation=(PDIRECTORY_BASIC_INFORMATION)DirectoryEntryName;
	ULONG DirectoryBaseInformationSize=sizeof(DirectoryEntryName);
	unsigned int iRet = -1;
	WCHAR* MapName=NULL;
	
	WCHAR* DiskLinkList[26];
	int DirectoryNameLen=0;
	if(LoadAPI()==false)
	{
		//MessageBox(NULL,"装载 NTDLL.DLL 中的函数出错！","错误！",MB_OK);
		UnloadAPI();
		return 0;
	}
	DirectoryName.Buffer=DirectoryNameBuf;
	memset(DiskLinkList,0,sizeof(DiskLinkList));
	UNICODE_STRING LinkTargetName;
	SymbolicHandle=NULL;
	
	TSPrintf(NameBuffer,L"\\global??\\%c:",PhysicalDiskNumber);
	LinkTargetName.Buffer=LinkNameBuf;
	LinkTargetName.Length=sizeof(LinkNameBuf)-2;
	LinkTargetName.MaximumLength=sizeof(LinkNameBuf);
	if(GetSymbolicLink(NameBuffer,&LinkTargetName,&ReturnLength)==false)
		return 0;
	MapName = (WCHAR*)new char[ReturnLength];
	TStrCpy(MapName,LinkTargetName.Buffer);
	
	FIND_OBJECT_DATA FindObjectData;
	TStrCpy(DirectoryName.Buffer,"\\ArcName");
	DirectoryNameLen=TStrLen(DirectoryName.Buffer);
	FindFirstObject(DirectoryName.Buffer,&FindObjectData);
	DirectoryHandle = FindObjectData.FindHandle;
	NTStatus = pZwQueryDirectoryObject(DirectoryHandle,pDirectoryBaseInformation,DirectoryBaseInformationSize,TRUE,RestartScan,&Context,&ReturnLength);
	if(NTStatus)
	{
		pZwClose(DirectoryHandle);
		UnloadAPI();
		//MessageBox(NULL,"查询目录信息错误！","错误！",MB_OK);
		return 0;
	}
	RestartScan=FALSE;
	do
	{
		if(TStrICmp(pDirectoryBaseInformation->ObjectTypeName.Buffer,"SymbolicLink")==0)
		{
			DirectoryName.Buffer[DirectoryNameLen]=0;
			TStrCat(DirectoryName.Buffer,"\\");
			TStrCat(DirectoryName.Buffer,pDirectoryBaseInformation->ObjectName.Buffer);
			if(GetSymbolicLink(DirectoryName.Buffer,&LinkTargetName,&ReturnLength))
			{
				if(GetSymbolicLink(LinkTargetName.Buffer,&LinkTargetName,&ReturnLength))
				{
					if(TStrICmp(LinkTargetName.Buffer,MapName)==0)
					{
						iRet = TStrLen(pDirectoryBaseInformation->ObjectName.Buffer);
						if(iRet<BufRetLen/sizeof(WCHAR)&&RetName)
							TStrCpy(RetName,pDirectoryBaseInformation->ObjectName.Buffer);
						pZwClose(DirectoryHandle);
						UnloadAPI();
						return iRet;
					}
				}
				
			}
		}
		NTStatus = pZwQueryDirectoryObject(DirectoryHandle,DirectoryEntryName,sizeof(DirectoryEntryName),TRUE,RestartScan,&Context,&ReturnLength);
		if(NTStatus)
			break;
	}while(1);
	pZwClose(DirectoryHandle);
	UnloadAPI();
	return 0;
}