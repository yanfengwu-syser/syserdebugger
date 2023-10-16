#include "StdAfx.h"
#include "ObjFile.h"

#define IsFunction(s)	(s.Type == 0x20 && s.StorageClass == IMAGE_SYM_CLASS_EXTERNAL && s.SectionNumber>0)


CObjFile::CObjFile()
{
	m_StrTabBuf = NULL;
	m_Section = NULL;
	m_FuncCount = m_SectCount = 0;
	m_ObjSymAry = NULL;
	m_FileBody = NULL;
}

CObjFile::~CObjFile()
{
}

bool CObjFile::Open(PCSTR FileName,HANDLE*pHandleOpen)
{
	DWORD StrTabSize;
	int Offset,n;
	if(CImageFile::Open(FileName,pHandleOpen)==false)
		return false;
	if(m_FileSize<=0x100)
	{
		CImageFile::Close();
		return false;
	}
	m_FileBody = new BYTE[m_FileSize];
	if(ReadFile(0,m_FileBody,m_FileSize)==false)
	{
		delete []m_FileBody;
		CImageFile::Close();
		return false;
	}
	if(ReadFile(0,&m_ObjHead,sizeof(OBJ_IMAGE_FILE_HEADER))==false)
	{
		delete []m_FileBody;
		CImageFile::Close();
		return false;
	}
	for(n=0;m_ObjMachineSign[n];n++)
	{
		if(m_ObjHead.Machine==m_ObjMachineSign[n])
			break;
	}
	if(m_ObjMachineSign[n]==IMAGE_FILE_MACHINE_UNKNOWN)
	{
		delete []m_FileBody;
		CImageFile::Close();
		return false;
	}
	m_SectCount = m_ObjHead.NumberOfSections;
	m_Section = (OBJ_SECTION*)&m_FileBody[sizeof(m_ObjHead)];
	//m_Section = new OBJ_SECTION[m_SectCount];
	//ReadFile(sizeof(m_ObjHead),m_Section,sizeof(OBJ_SECTION)*m_SectCount);
	//Read String Table
	Offset = m_ObjHead.PointerToSymbolTable + IMAGE_SIZEOF_SYMBOL*m_ObjHead.NumberOfSymbols;
	m_StrTabBuf =(char*) &m_FileBody[Offset];
	//StrTabSize = 0;
	StrTabSize = *(DWORD*)&m_FileBody[Offset];
	//ReadFile(Offset,&StrTabSize,4);
	//m_StrTabBuf = new char[StrTabSize+6];
	//m_StrTabBuf[StrTabSize+4]=m_StrTabBuf[StrTabSize+5]=0;
	//ReadFile(Offset,m_StrTabBuf,StrTabSize);
	//Read Symbol Table
	m_ObjSymAry = (OBJ_IMAGE_SYMBOL*)&m_FileBody[m_ObjHead.PointerToSymbolTable];
	//m_ObjSymAry = new OBJ_IMAGE_SYMBOL[m_ObjHead.NumberOfSymbols];
	/*
	Offset = m_ObjHead.PointerToSymbolTable;
	for(n=0;n<(int)m_ObjHead.NumberOfSymbols;n++)
	{
		ReadFile(Offset,&m_ObjSymAry[n],IMAGE_SIZEOF_SYMBOL);
		Offset+=IMAGE_SIZEOF_SYMBOL;
	}
	*/
	n=0;
	//Read Data
	while(n<(int)m_ObjHead.NumberOfSymbols)
	{
		if(IsFunction(m_ObjSymAry[n]))
		{
			AddFunction(&m_ObjSymAry[n]);
		}
		n+=m_ObjSymAry[n].NumberOfAuxSymbols+1;
	}
	return true;
}

void CObjFile::Close()
{
	//SafeDelete(m_Section);
	//SafeDelete(m_ObjSymAry);
	//SafeDelete(m_StrTabBuf);
	SafeDelete(m_FileBody);
	m_FuncList.Clear();
	CImageFile::Close();
}
char* CObjFile::GetSectionName(int SectionIndex)
{
	char TmpName[9];
	DWORD StrIndex;
	if(SectionIndex<m_SectCount)
	{
		if(m_Section[SectionIndex].Name[0]!='/')
		{
			return (char*) &m_Section[SectionIndex].Name[0];
		}
		else
		{
			TStrNCpy(TmpName,&m_Section[SectionIndex].Name[1],7);
			if(SDecStrToNum(TmpName,&StrIndex)==false)
			{
				return NULL;
			}
			return &m_StrTabBuf[StrIndex];
		}
	}
	return 0;
}
char* CObjFile::GetSymbolNameByIndex(DWORD Index)
{
	if(Index>m_ObjHead.NumberOfSymbols)
		return NULL;
	return GetSymbolName(&m_ObjSymAry[Index]);
}
char* CObjFile::GetSymbolName(OBJ_IMAGE_SYMBOL* Sym)
{
	char* szName;
	if(Sym->N.Name.Short)
	{
		szName = new char[9];
		TStrCpyLimit(szName,Sym->N.ShortName,9);
		return szName;
	}
	else
	{
		szName = new char [TStrLen(&m_StrTabBuf[Sym->N.Name.Long])+1];
		TStrCpy(szName,&m_StrTabBuf[Sym->N.Name.Long]);
		return szName;
	}
	return 0;
}
void CObjFile::AddFunction(OBJ_IMAGE_SYMBOL*ObjSym)
{
	char szName[9];
	int nSec;
	OBJ_IMAGE_AUX_SYMBOL*ObjAuxSym;
	ObjAuxSym=(OBJ_IMAGE_AUX_SYMBOL*)&ObjSym[1];
	nSec = (int)(ObjSym->SectionNumber-1);
	TObjFuncList::IT Iter = m_FuncList.Append();
	Iter->FilePos = m_Section[nSec].PointerToRawData;
	Iter->Size = m_Section[nSec].SizeOfRawData;
	if(ObjSym->N.Name.Short)
	{
		TStrCpyLimit(szName,ObjSym->N.ShortName,9);
		Iter->FuncName = szName;
	}
	else
	{
		Iter->FuncName = &m_StrTabBuf[ObjSym->N.Name.Long];
	}
}

DWORD CObjFile::m_ObjMachineSign[] =
{
	IMAGE_FILE_MACHINE_I386,
	IMAGE_FILE_MACHINE_R3000,
	IMAGE_FILE_MACHINE_R4000,
	IMAGE_FILE_MACHINE_R10000,
	IMAGE_FILE_MACHINE_WCEMIPSV2,
	IMAGE_FILE_MACHINE_ALPHA,
	IMAGE_FILE_MACHINE_POWERPC,
	IMAGE_FILE_MACHINE_SH3,
	IMAGE_FILE_MACHINE_SH3E,
	IMAGE_FILE_MACHINE_SH4,
	IMAGE_FILE_MACHINE_ARM,
	IMAGE_FILE_MACHINE_THUMB,
	IMAGE_FILE_MACHINE_IA64,
	IMAGE_FILE_MACHINE_MIPS16,
	IMAGE_FILE_MACHINE_MIPSFPU,
	IMAGE_FILE_MACHINE_MIPSFPU16,
	IMAGE_FILE_MACHINE_ALPHA64,
	IMAGE_FILE_MACHINE_UNKNOWN
};
