// MFCSymbols.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
#include <fstream>
using namespace std;

XSCAN_RES xScanCB3(CFileIO*pFileIO,PCSTR FileName,ULSIZE FileSize,void*CBParam)
{
	char Path[MAX_PATH];
	GetSystemDirectoryA(Path,sizeof(Path));
	HANDLE hFile;
	bool bOK;

	bOK=gpFileIO->OpenFile(FileName,&hFile);
	if(!bOK)
		return XSCAN_RES_CONTINUE;
	ULLSIZE Length;
	Length = gpFileIO->GetFileLength(hFile);
	DWORD* Ptr=(DWORD*)new char[Length];
	gpFileIO->ReadFile(hFile,Ptr,Length,0);
	gpFileIO->CloseHandle(hFile);
	
	char* p2 = TStrRChr(FileName,'\\');
	if(p2==NULL)
		p2=(char*)FileName;
	else
		p2++;
	TStrCat(Path,"\\drivers\\plugin\\");
	TStrCat(Path,p2);
	p2 = TStrIStr(Path,".sym");
	if(p2)
		p2[0]=0;
	ofstream of(Path);
	char* ptr=(char*)CBParam;
	for(DWORD i=0;i<Ptr[0];i++)
	{		
		if(ptr[Ptr[2+i]]!=0)
			of<< Ptr[1]+i << " "<< ptr+Ptr[2+i]<<endl;
	}
	of.flush();
	of.close();
	return XSCAN_RES_CONTINUE;
}
int main(int argc, char* argv[])
{
	char SourcePath[MAX_PATH];
	HANDLE hFile;
	FreeConsole();
	GetModulePath(SourcePath);
	strcat(SourcePath,"mfcsym.txt");
	if(gpFileIO->OpenFile(SourcePath,&hFile)==false)
		return 1;
	char* p = TStrRChr(SourcePath,'\\');
	if(p==NULL)
	{
		GetCurrentDirectoryA(sizeof(SourcePath),SourcePath);
	}
	else
	{
		p[0]=0;	
	}
	TStrCat(SourcePath,"\\*.sym");
	ULLSIZE Length;
	Length = gpFileIO->GetFileLength(hFile);
	char* Ptr=new char[Length];
	gpFileIO->ReadFile(hFile,Ptr,Length,0);
	gpFileIO->CloseHandle(hFile);	
	gpFileIO->XScan(SourcePath,xScanCB3,Ptr,false);
	delete []Ptr;
	return 0;
}

