#include "StdAfx.h"
#include "FileType.h"


DWORD CFileType::GetFileType()
{
	PE_HEAD PEHead;
	WORD  wFlag;
	DWORD Offset,Result = FILE_TYPE_BIN;
	ReadFile(0,&wFlag,2);
	if(wFlag == 0x4D5A || wFlag == 0x5A4D)
		Result = FILE_TYPE_MZ;
	if(Result == FILE_TYPE_MZ)
	{
		if(ReadFile(0x3C,&Offset,4))
		{
			if(ReadFile(Offset,&PEHead,sizeof(PEHead)))
			{
				if(PEHead.Signature == 0x4550)
					Result = FILE_TYPE_PE;
				if(PEHead.Signature == 0x454E)
					Result = FILE_TYPE_NE;
			}
			if(Result == FILE_TYPE_PE && (PEHead.Characteristics & IMAGE_FILE_DLL))
				Result = FILE_TYPE_PE_DLL;
			if(Result == FILE_TYPE_PE && (PEHead.Subsystem & IMAGE_FILE_DLL))
				Result = FILE_TYPE_PE_SYS;
		}
	}
	return Result;
}

bool CFileType::IsMaybePEUnpackSelfFile(DWORD MaxUnpackSize,bool bExcludeDll)
{
	PE_HEAD PEHead;
	DWORD Offset;
	PE_SECTION Section;
	WORD  wFlag;
	ReadFile(0,&wFlag,2);
	if(wFlag != 0x4D5A && wFlag != 0x5A4D)
		return false;
	if(!ReadFile(0x3C,&Offset,4))
		return false;
	if(!ReadFile(Offset,&PEHead,sizeof(PEHead)))
		return false;
	BIG_ENDIAN_DWORD(PEHead.Signature);
	if(PEHead.Signature != 0x4550)
		return false;
	BIG_ENDIAN_WORD(PEHead.Characteristics);
	if(bExcludeDll && (PEHead.Characteristics & IMAGE_FILE_DLL))
		return false;
	BIG_ENDIAN_DWORD(PEHead.SizeOfOptionalHeader);
	if(!ReadFile(PEHead.SizeOfOptionalHeader+Offset+0x18,&Section,sizeof(PE_SECTION)))
		return false;
	BIG_ENDIAN_DWORD(Section.Characteristics);
	if((Section.Characteristics & IMAGE_SCN_MEM_WRITE)==0)
		return false;
	BIG_ENDIAN_DWORD(PEHead.SizeOfImage);
	if(PEHead.SizeOfImage>MaxUnpackSize)
		return false;
	return true;
}

bool CFileType::IsUPXFile(CPEFile*pPEFile)
{
	ULPOS FilePos;
	BYTE Buffer[0x10];
	if(pPEFile->MapToFile(pPEFile->m_EntryPoint,&FilePos)==false)
		return false;
	if(pPEFile->ReadFile(FilePos,Buffer,sizeof(Buffer))==false)
		return false;
	return Buffer[0x0] == 0x60 && Buffer[0x1] == 0xBE &&Buffer[0x6] == 0x8D &&Buffer[0xC] == 0x57;
}
