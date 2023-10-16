#include "StdAfx.h"
#include "PEFile.h"

CPEFile::CPEFile()
{
	m_PEOff = 0;
	m_Section = NULL;
	m_ExportFunc = NULL;
	m_ImportModule = NULL;
	m_ResDir = NULL;
	m_BaseReloc = NULL;
	m_TLSCallBackFuncs = NULL;
	m_TLSData = NULL;
	m_SectCount=0;
	m_ImportModuleCount=m_ResDirCount=m_BaseRelocCount=m_AddressOfTLSIndex=
	m_TLSCallBackCount=m_TLSDataSize=m_ExportFuncCount=0;
	m_OpenMode = PE_OPEN_ALL;
}

bool CPEFile::MapToMemory(IN DWORD PhyOff,OUT DWORD*pMemAddr,IN bool bImageBase)
{
	for(int n=0;n<=m_SectCount;n++)
	{
		if(PhyOff>=m_Section[n].PointerToRawData&&PhyOff<m_Section[n].PointerToRawData+m_Section[n].SizeOfRawData)
		{
            if(pMemAddr)
            {
                *pMemAddr=PhyOff-m_Section[n].PointerToRawData+m_Section[n].VirtualAddress;
                if(bImageBase)
                    *pMemAddr+=m_PEHead.ImageBase;
            }
            return true;
		}
	}
	return false;
}

bool CPEFile::MapToFile(IN DWORD MemAddr,OUT DWORD*pPhysAddr,IN bool bImageBase)
{
	DWORD BaseAddr = 0;
	if(bImageBase)
		MemAddr-=m_PEHead.ImageBase;
	for(int n=0;n<=m_SectCount;n++)
	{
		if( MemAddr>=m_Section[n].VirtualAddress && MemAddr< m_Section[n].VirtualAddress + m_Section[n].VirtualSize && 
			MemAddr-m_Section[n].VirtualAddress<=m_Section[n].SizeOfRawData )
		{
            if(pPhysAddr)
                *pPhysAddr=MemAddr-m_Section[n].VirtualAddress+m_Section[n].PointerToRawData;
            return true;
        }
	}
    return false;
}

DWORD CPEFile::GetPageAttribute(DWORD Address)
{
	DWORD Result=MP_READ | MP_WRITE;
	if(Address<m_ImageBase || Address>=m_ImageHighBase)
		return 0;
	Address-=m_ImageBase;
	for(int n=0;n<=m_SectCount;n++)
	{
		if(Address>=m_Section[n].VirtualAddress && Address< m_Section[n].VirtualAddress+m_Section[n].VirtualSize)
		{
			Result=0;
			if(m_Section[n].Characteristics & IMAGE_SCN_MEM_EXECUTE)
				Result|=MP_READ;
			if(m_Section[n].Characteristics & IMAGE_SCN_MEM_READ)
				Result|=MP_READ;
			if(m_Section[n].Characteristics & IMAGE_SCN_MEM_WRITE)
				Result|=MP_READ | MP_WRITE;
			//如果节属性是0，则置页属性位可读写（和Win95兼容）
			if(m_Section[n].Characteristics==0)
				Result=MP_READ | MP_WRITE;
			return Result;
		}
	}
	return Result;
}

ULSIZE CPEFile::ReadImageMemory(ULPOS Address,void*Buffer,ULSIZE Size)
{
	PE_SECTION* pCurSec;
	DWORD dwSize,ReadSize,Pos=0;
	DWORD LeftSize;
	DWORD RangeStart,RangeEnd;
////裁减///////////////////////////////////
	if(Address < m_ImageBase || Address>= m_ImageHighBase)
		return 0;
	if(Address< m_ImageHighBase && Address+Size >m_ImageHighBase)
	{
		Size=m_ImageHighBase-Address;
	}
	if(m_SectCount==0)
		return ReadFile(Address-m_ImageBase,Buffer,Size);
////裁减///////////////////////////////////
	LeftSize=Size;
	Address-=m_ImageBase;
	ZeroMemory(Buffer,Size);
	for(int n=0;n<=m_SectCount&&LeftSize;n++)
	{
 		pCurSec=&m_Section[n];
		RangeStart=pCurSec->VirtualAddress;
		RangeEnd=pCurSec->VirtualAddress+pCurSec->VirtualSize;
		if(Address>=RangeStart && Address < RangeEnd)
		{
			if(Address<pCurSec->SizeOfRawData+pCurSec->VirtualAddress)
			{
				dwSize=pCurSec->SizeOfRawData+pCurSec->VirtualAddress-Address;
				if(LeftSize > dwSize)
				{
					LeftSize=LeftSize-dwSize;
					ReadSize=dwSize;
				}
				else
				{
					ReadSize=LeftSize;
					LeftSize=0;
				}
				ReadFile(Address-pCurSec->VirtualAddress+pCurSec->PointerToRawData,RT_PBYTE(Buffer,Pos),ReadSize);
				Pos+=ReadSize;
				Address+=ReadSize;
			}
			else if(Address<RangeEnd)
			{
				dwSize=RangeEnd-Address;
				if(LeftSize > dwSize)
				{
					LeftSize=LeftSize-dwSize;
					ReadSize=dwSize;
				}
				else
				{
					ReadSize=LeftSize;
					LeftSize=0;
				}
				Pos+=ReadSize;
				Address+=ReadSize;
			}
		}
	}
	return Size;
}

ULSIZE CPEFile::WriteImageMemory(ULPOS Address,void*Buffer,ULSIZE Size)
{
	return 0;
}

bool CPEFile::LoadPage(ULPOS OldAddress,void*Buffer)
{
	DWORD Delta;
	ULPOS Address;
	LONG Size;
	WORD TypeOffset,Offset,Type;
	if(m_SectCount==0 || m_Section==NULL)
		return false;
	Address = OldAddress;
	Address &= ~(0xfff);
	/*
	if(m_PEHead.SectionAlignment!=MP_SIZE)
	{
		ReadImageMemory(Address,Buffer,MP_SIZE);
		return true;
	}
	*/
	ZeroMemory(Buffer,MP_SIZE);
	Address-=m_ImageBase;
	for(int n=0;n<=m_SectCount;n++)
	{
		if(Address>=m_Section[n].VirtualAddress && Address < m_Section[n].VirtualAddress+m_Section[n].VirtualSize)
		{
			Size=m_Section[n].VirtualAddress+m_Section[n].SizeOfRawData-Address;
			if(Size>0)
			{
				if(Size>MP_SIZE)
					Size=MP_SIZE;
				ReadFile(Address-m_Section[n].VirtualAddress+m_Section[n].PointerToRawData,Buffer,Size);
				if(m_ImageBase==m_PEHead.ImageBase)
					return true;
				for(int i=0;i<m_BaseRelocCount;i++)
				{//处理重定位
					if(Address==m_BaseReloc[i].VirtualAddr+MP_SIZE && m_BaseReloc[i].Count)
					{
						TypeOffset=m_BaseReloc[i].TypeOffset[m_BaseReloc[i].Count-1];
						Type=TypeOffset>>12;
						Offset=TypeOffset&0x0FFF;/*@@*/
						if(Type==3 && Offset>0x0FFC)
						{
							Delta=m_ImageBase-m_PEHead.ImageBase;
							switch(Offset)
							{
							case 0xFFD: PUT_3BYTES(Buffer,Offset,GET_3BYTES(Buffer,Offset)+Delta);
										break;
							case 0xFFE: PUT_WORD(Buffer,Offset,GET_WORD(Buffer,Offset)+(WORD)Delta);
										break;
							case 0xFFF: PUT_BYTE(Buffer,Offset,GET_BYTE(Buffer,Offset)+(WORD)Delta);
										break;
							}
						}
					}
					if(Address==m_BaseReloc[i].VirtualAddr)
					{
						for(DWORD r=0;r<m_BaseReloc[i].Count;r++)
						{
							TypeOffset=m_BaseReloc[i].TypeOffset[r];
							Type=TypeOffset>>12;
							Offset=TypeOffset&0x0FFF;/*@@*/
							if(Type==3 && Offset<=0x0FFC)
								PUT_DWORD(Buffer,Offset,GET_DWORD(Buffer,Offset)+m_ImageBase-m_PEHead.ImageBase);
						}
					}
				}
			}
			return true;
		}
	}
	return false;
}

bool CPEFile::Open(PCSTR FileName,HANDLE*pHandleOpen)
{
	DWORD MaxHighSectAddr,MinLowSectAddr,MinLowSectAddrFilePos,SafeSectionAlign,SafeFileAlign,NewSize;
	BYTE HeadBuffer[0x40];
	int i;
	if(CImageFile::Open(FileName,pHandleOpen)==false)
	{
		return false;
	}
	//////////////////////////////////////////////////////////////
	//是否是MZ文件
	//////////////////////////////////////////////////////////////
	if(ReadMemory(m_ImageBase,HeadBuffer,sizeof(HeadBuffer))==false)
	{
		CImageFile::Close();
		return false;
	}
	if(_GET_WORD(HeadBuffer)!=0x4D5A && _GET_WORD(HeadBuffer)!=0x5A4D)
	{
		CImageFile::Close();
		return false;
	}
	//////////////////////////////////////////////////////////////
	//是否是PE文件，并读入PE头
	//////////////////////////////////////////////////////////////
	m_PEOff=GET_DWORD(HeadBuffer,0x3C);
	if(m_PEOff >=m_FileSize-sizeof(PE_HEAD))
	{
		CImageFile::Close();
		return false;
	}
    if(ReadMemory(m_ImageBase+m_PEOff,&m_PEHead,sizeof(PE_HEAD))==false)
	{
		CImageFile::Close();
		return false;
	}
	m_FileType = FILE_TYPE_PE_EXE;
	//PE头大字节序
	BIG_ENDIAN_DWORD(m_PEHead.Signature);
	BIG_ENDIAN_WORD(m_PEHead.Machine);
	BIG_ENDIAN_WORD(m_PEHead.NumberOfSections);
	BIG_ENDIAN_DWORD(m_PEHead.TimeDateStamp);
	BIG_ENDIAN_DWORD(m_PEHead.PointerToSymbolTable);
	BIG_ENDIAN_DWORD(m_PEHead.NumberOfSymbols);
	BIG_ENDIAN_WORD(m_PEHead.SizeOfOptionalHeader);
	BIG_ENDIAN_WORD(m_PEHead.Characteristics);
	BIG_ENDIAN_WORD(m_PEHead.Magic);
	BIG_ENDIAN_DWORD(m_PEHead.SizeOfCode);
	BIG_ENDIAN_DWORD(m_PEHead.SizeOfInitializedData);
	BIG_ENDIAN_DWORD(m_PEHead.SizeOfUninitializedData);
	BIG_ENDIAN_DWORD(m_PEHead.AddressOfEntryPoint);
	BIG_ENDIAN_DWORD(m_PEHead.BaseOfCode);
	BIG_ENDIAN_DWORD(m_PEHead.BaseOfData);
	BIG_ENDIAN_DWORD(m_PEHead.ImageBase);
	BIG_ENDIAN_DWORD(m_PEHead.SectionAlignment);
	BIG_ENDIAN_DWORD(m_PEHead.FileAlignment);
	BIG_ENDIAN_WORD(m_PEHead.MajorOperatingSystemVersion);
	BIG_ENDIAN_WORD(m_PEHead.MinorOperatingSystemVersion);
	BIG_ENDIAN_WORD(m_PEHead.MajorImageVersion);
	BIG_ENDIAN_WORD(m_PEHead.MinorImageVersion);
	BIG_ENDIAN_WORD(m_PEHead.MajorSubsystemVersion);
	BIG_ENDIAN_WORD(m_PEHead.MinorSubsystemVersion);
	BIG_ENDIAN_DWORD(m_PEHead.Win32VersionValue);
	BIG_ENDIAN_DWORD(m_PEHead.SizeOfImage);
	BIG_ENDIAN_DWORD(m_PEHead.SizeOfHeaders);
	BIG_ENDIAN_DWORD(m_PEHead.CheckSum);
	BIG_ENDIAN_WORD(m_PEHead.Subsystem);
	BIG_ENDIAN_WORD(m_PEHead.DllCharacteristics);
	BIG_ENDIAN_DWORD(m_PEHead.SizeOfStackReserve);
	BIG_ENDIAN_DWORD(m_PEHead.SizeOfStackCommit);
	BIG_ENDIAN_DWORD(m_PEHead.SizeOfHeapReserve);
	BIG_ENDIAN_DWORD(m_PEHead.SizeOfHeapCommit);
	BIG_ENDIAN_DWORD(m_PEHead.LoaderFlags);
	BIG_ENDIAN_DWORD(m_PEHead.NumberOfRvaAndSizes);
	for(int n=0;n<MAX_PE_DATA_DIR;n++)
	{
		BIG_ENDIAN_DWORD(m_PEHead.DataDirectory[n].VirtualAddress);
		BIG_ENDIAN_DWORD(m_PEHead.DataDirectory[n].Size);
	}
	if(m_PEHead.Signature!=0x4550)
	{
		CImageFile::Close();
		m_ErrorCode = PE_ERROR_SIGN;
		return false;
	}
	if(m_PEHead.Characteristics & IMAGE_FILE_DLL)
	{
		if((m_OpenMode & PE_OPEN_DLL)==0)
		{
			CImageFile::Close();
			m_ErrorCode=PE_ERROR_MODULE_TYPE;
			return false;
		}
		m_FileType = FILE_TYPE_PE_DLL;
	}
	if(m_PEHead.Subsystem==IMAGE_SUBSYSTEM_NATIVE)
	{
		if((m_OpenMode & PE_OPEN_SYS)==0)
		{
			CImageFile::Close();
			m_ErrorCode = PE_ERROR_MODULE_TYPE;
			return false;
		}
		m_FileType = FILE_TYPE_PE_SYS;
	}
	if(m_PEHead.Machine!=IMAGE_FILE_MACHINE_I386)
	{
		if(m_OpenMode & PE_OPEN_NON_I386)
		{
			CImageFile::Close();
			m_ErrorCode = PE_ERROR_MODULE_TYPE;
			return false;
		}
		m_FileType |= FILE_TYPE_NON_I386;
	}
	SafeSectionAlign = m_PEHead.SectionAlignment;
	SafeFileAlign = m_PEHead.FileAlignment;
	if(SafeSectionAlign>PE_MAX_SECTION_ALIGN || SafeSectionAlign==0)
		SafeSectionAlign = PE_DEFAULT_SECTION_ALIGN;
	if(SafeFileAlign>PE_MAX_FILE_ALIGN || SafeFileAlign==0)
		SafeFileAlign = PE_DEFAULT_FILE_ALIGN;
	if(m_PEHead.NumberOfSections <= 0 || m_PEHead.NumberOfSections>MAX_PE_SECTION)
	{
		CImageFile::Close();
		m_ErrorCode = PE_ERROR_SECTION;
		return false;
	}
	m_Section=new PE_SECTION[m_PEHead.NumberOfSections+1];
	if(m_Section==NULL)
	{
		SafeDelete(m_Section);
		CImageFile::Close();
		m_ErrorCode = PE_ERROR_SECTION;
		return false;
	}
	if(ReadMemory(m_ImageBase+m_PEHead.SizeOfOptionalHeader+m_PEOff+0x18,&m_Section[1],sizeof(PE_SECTION)*m_PEHead.NumberOfSections)==0)
	{
		SafeDelete(m_Section);
		CImageFile::Close();
		m_ErrorCode = PE_ERROR_SECTION;
		return false;
	}
	m_SectCount = m_PEHead.NumberOfSections;
	for(int n=1;n<=m_SectCount;n++)
	{
		BIG_ENDIAN_DWORD(m_Section[n].VirtualSize);
		BIG_ENDIAN_DWORD(m_Section[n].VirtualAddress);
		BIG_ENDIAN_DWORD(m_Section[n].SizeOfRawData);
		BIG_ENDIAN_DWORD(m_Section[n].PointerToRawData);
		BIG_ENDIAN_DWORD(m_Section[n].PointerToRelocations);
		BIG_ENDIAN_DWORD(m_Section[n].PointerToLinenumbers);
		BIG_ENDIAN_WORD(m_Section[n].NumberOfRelocations);
		BIG_ENDIAN_WORD(m_Section[n].NumberOfLinenumbers);
		BIG_ENDIAN_DWORD(m_Section[n].Characteristics);
	}
	ZeroMemory(m_Section,sizeof(PE_SECTION));
	m_Section->PointerToRawData=m_Section->VirtualAddress=0;
	m_Section->SizeOfRawData=m_Section->VirtualSize=m_PEHead.SizeOfHeaders;
	m_Section->Characteristics = IMAGE_SCN_MEM_WRITE | IMAGE_SCN_MEM_READ;
	MaxHighSectAddr = 0;
	MinLowSectAddr = 0xFFFFFFFF;
	for(i=1;i<=m_SectCount;i++)
	{
		if(m_Section[i].VirtualSize == 0)
			m_Section[i].VirtualSize = m_Section[i].SizeOfRawData;
		if(m_Section[i].SizeOfRawData%SafeFileAlign)
			m_Section[i].SizeOfRawData = ALIGN_SIZE(m_Section[i].SizeOfRawData,SafeFileAlign);
		if(m_Section[i].VirtualSize%SafeSectionAlign)
			m_Section[i].VirtualSize = ALIGN_SIZE(m_Section[i].VirtualSize,SafeSectionAlign);
		if(i == m_SectCount)
		{//特殊处理最后一个节
			if(m_Section[i].VirtualSize < m_Section[i].SizeOfRawData)
			{
				NewSize = ALIGN_SIZE(m_Section[i].SizeOfRawData,SafeSectionAlign);
				if(m_Section[i].VirtualAddress+NewSize <= ALIGN_SIZE(m_PEHead.SizeOfImage,MP_SIZE))
					m_Section[i].VirtualSize = NewSize;
			}
		}
		if(m_Section[i].VirtualAddress<m_Section[i-1].VirtualAddress+m_Section[i-1].VirtualSize && m_Section[i-1].VirtualAddress<m_Section[i].VirtualAddress)
			m_Section[i-1].VirtualSize = m_Section[i].VirtualAddress-m_Section[i-1].VirtualAddress;
		if(i < m_SectCount && m_Section[i].VirtualAddress == m_Section[i+1].VirtualAddress)
			m_Section[i].VirtualSize = 0;
		//防止非法数据大小
		if(m_Section[i].PointerToRawData>m_FileSize)
			m_Section[i].SizeOfRawData = 0;
		if(m_Section[i].SizeOfRawData>MAX_PE_IMAGESIZE)
			m_Section[i].SizeOfRawData = m_Section[i].VirtualSize;
		if(m_Section[i].SizeOfRawData + m_Section[i].PointerToRawData > m_FileSize)
			m_Section[i].SizeOfRawData = m_FileSize - m_Section[i].PointerToRawData;
		if(m_Section[i].VirtualSize > MAX_PE_IMAGESIZE)
			m_Section[i].VirtualSize = m_Section[i].SizeOfRawData;
		if(m_Section[i].VirtualAddress+m_Section[i].VirtualSize >MaxHighSectAddr)
			MaxHighSectAddr = m_Section[i].VirtualAddress+m_Section[i].VirtualSize;
		if(m_Section[i].VirtualAddress<MinLowSectAddr)
		{
			MinLowSectAddr = m_Section[i].VirtualAddress;
			MinLowSectAddrFilePos = m_Section[i].PointerToRawData;
		}
	}
	if(m_Section->SizeOfRawData < MinLowSectAddr && MinLowSectAddr!=0xFFFFFFFF)
	{
		m_Section->VirtualSize = MinLowSectAddr;
		if(MinLowSectAddrFilePos)
			m_Section->SizeOfRawData = MinLowSectAddrFilePos;
	}
	if(m_SectCount>0 && m_PEHead.AddressOfEntryPoint>=m_Section[m_SectCount].VirtualAddress+m_Section[m_SectCount].VirtualSize)
	{
		if(m_PEHead.AddressOfEntryPoint<m_PEHead.SizeOfImage)
		{
			m_Section[m_SectCount].VirtualSize = m_PEHead.SizeOfImage - m_Section[m_SectCount].VirtualAddress;
		}
		else
		{
			if(m_FileSize>=m_Section[m_SectCount].PointerToRawData)
				m_Section[m_SectCount].SizeOfRawData = m_FileSize - m_Section[m_SectCount].PointerToRawData;
		}
	}
	m_FileType=FILE_TYPE_PE;
	if((m_FileObjType&FILE_OBJ_TYPE_OS_MEMORY_IMAGE)==0)
		m_ImageBase=m_PEHead.ImageBase;
	m_ImageSize=ALIGN_SIZE(m_PEHead.SizeOfImage,MP_SIZE);
	if(	m_SectCount > 0 && m_Section[m_SectCount].VirtualAddress + m_Section[m_SectCount].SizeOfRawData >  m_ImageSize)
	{
		m_ImageSize = m_Section[m_SectCount].VirtualAddress + m_Section[m_SectCount].SizeOfRawData;
		if(m_Section[m_SectCount].VirtualSize<m_Section[m_SectCount].SizeOfRawData)
			m_Section[m_SectCount].VirtualSize=m_Section[m_SectCount].SizeOfRawData;
	}
	m_EntryPoint=m_PEHead.AddressOfEntryPoint+m_ImageBase;
	if(m_ImageSize<MaxHighSectAddr && MaxHighSectAddr<MAX_PE_IMAGESIZE)
		m_ImageSize = MaxHighSectAddr;
	if(m_ImageSize > MAX_PE_IMAGESIZE && MaxHighSectAddr<MAX_PE_IMAGESIZE)
		m_ImageSize = MaxHighSectAddr;
	m_ImageHighBase=m_ImageBase+m_ImageSize;
	if(Check()==false)
	{
		SafeDelete(m_Section);
		m_SectCount=0;
		CImageFile::Close();
		return false;
	}
	GetTLS();
	m_ImportModuleCount = 0;
	m_ImportModule = NULL;
	if((m_OpenMode & PE_OPEN_NO_IMPORT)==0)
		GetImportModule();
	m_ExportFuncCount = 0;
	m_ExportFunc = NULL;
	if((m_OpenMode & PE_OPEN_NO_EXPORT)==0)
		GetExportFunc();
	m_ErrorCode = PE_ERROR_SUCCESS;
	return true;
}

void CPEFile::Close()
{
	int n;
	for(n=0;n<m_ImportModuleCount;n++)
		SafeDelete(m_ImportModule[n].FuncList)
	SafeDelete(m_ImportModule)
	for(n=0;n<m_ResDirCount;n++)
	{
		if(m_ResDir[n].ResDataDir)
			delete m_ResDir[n].ResDataDir;
	}
	SafeDelete(m_ResDir)
	for(n=0;n<m_BaseRelocCount;n++)
	{
		if(m_BaseReloc[n].TypeOffset)
			delete m_BaseReloc[n].TypeOffset;
	}
	SafeDelete(m_BaseReloc);
	SafeDelete(m_TLSCallBackFuncs);
	SafeDelete(m_TLSData);
	SafeDelete(m_ExportFunc);
	SafeDelete(m_Section);
	m_SectCount=m_ImportModuleCount=m_ResDirCount=m_BaseRelocCount=m_AddressOfTLSIndex=
	m_TLSCallBackCount=m_TLSDataSize=m_ExportFuncCount=0;
	CImageFile::Close();
}

void  CPEFile::RelocLoad(ULPOS BaseAddr)
{
	IMPORT_FUNC*pImportFunc;
	int n;
	ULPOS Delta;
	Delta = BaseAddr-m_ImageBase;
	if(Delta==0 || BaseAddr==0)
		return;
	CImageFile::RelocLoad(BaseAddr);
	if(m_TLSCallBackFuncs)
	{
		for(n=0;n<m_TLSCallBackCount;n++)
			m_TLSCallBackFuncs[n]+=Delta;
	}
	GetBaseReloc();
	for(n=0;n<m_ImportModuleCount;n++)
	{
		pImportFunc=m_ImportModule[n].FuncList;
		for(int m=0;m<m_ImportModule[n].FuncCount;m++)
		{
			pImportFunc->NameAddr+=Delta;
			pImportFunc->ThunkAddr+=Delta;
			pImportFunc++;
		}
	}
	for(n=0;n<m_ExportFuncCount;n++)
	{
		if(m_ExportFunc[n].Address)
			m_ExportFunc[n].Address+=Delta;
		if(m_ExportFunc[n].ThunkAddr)
			m_ExportFunc[n].ThunkAddr+=Delta;
	}
}



bool CPEFile::IsRelocArea(ULPOS RVALow,ULPOS RVAHigh)
{
	ULPOS Low,High;
	if(m_BaseRelocCount==0)
		return false;
	for(int n=0;n<m_BaseRelocCount;n++)
	{
		Low=m_BaseReloc[n].VirtualAddr;
		High=m_BaseReloc[n].VirtualAddr+MP_SIZE;
		if(RVALow>=Low && RVALow<High)
			return true;
		if(RVAHigh>Low && RVAHigh<=High)
			return true;
		if(RVALow<=Low && RVAHigh>=High)
			return true;
	}
	return false;
}

bool CPEFile::IsImportThunkArea(ULPOS RVALow,ULPOS RVAHigh)
{
	ULPOS ThunkRVALow,ThunkRVAHigh;
	if(GetImportThunkArea(&ThunkRVALow,&ThunkRVAHigh)==false)
		return false;
	if(RVALow>=ThunkRVALow && RVALow<ThunkRVAHigh)
		return true;
	if(RVAHigh>ThunkRVALow && RVAHigh<=ThunkRVAHigh)
		return true;
	if(RVALow<=ThunkRVALow && RVAHigh>=ThunkRVAHigh)
		return true;
	return false;
}

bool CPEFile::GetImportThunkArea(ULPOS*pRVALow,ULPOS*pRVAHigh)
{
	IMPORT_MODULE*pModule;
	IMPORT_FUNC*pFunc;
	ULPOS RVALow,RVAHigh;
	if(m_ImportModuleCount==0)
		return false;
	RVALow=0xFFFFFFFF;
	RVAHigh=0;
	pModule=m_ImportModule;
	for(int m=0;m<m_ImportModuleCount;m++)
	{
		pFunc=pModule->FuncList;
		for(int f=0;f<pModule->FuncCount;f++)
		{
			if(RVALow>pFunc->ThunkAddr)
				RVALow=pFunc->ThunkAddr;
			if(RVAHigh<pFunc->ThunkAddr)
				RVAHigh=pFunc->ThunkAddr;
			pFunc++;
		}
		pModule++;
	}
	if(RVALow>=RVAHigh)
		return false;
	*pRVALow=RVALow-m_ImageBase;
	*pRVAHigh=RVAHigh-m_ImageBase;
	return true;
}

void CPEFile::GetTLS()
{
	ULPOS Pos,Address;
	TLS_DIRECTORY32 TLSDir;
	if(m_PEHead.DataDirectory[IMAGE_DIRECTORY_ENTRY_TLS].VirtualAddress==0)
		return;
    if(false==MapToFile(m_PEHead.DataDirectory[IMAGE_DIRECTORY_ENTRY_TLS].VirtualAddress,&Pos,false))
		return;
	ReadFile(Pos,&TLSDir,sizeof(TLS_DIRECTORY32));
	BIG_ENDIAN_DWORD(TLSDir.StartAddressOfRawData);
    BIG_ENDIAN_DWORD(TLSDir.EndAddressOfRawData);
    BIG_ENDIAN_DWORD(TLSDir.AddressOfIndex);
    BIG_ENDIAN_DWORD(TLSDir.AddressOfCallBacks);
    BIG_ENDIAN_DWORD(TLSDir.SizeOfZeroFill);
    BIG_ENDIAN_DWORD(TLSDir.Characteristics);
	if(TLSDir.AddressOfCallBacks==0)
		return;
    if(false==MapToFile(TLSDir.AddressOfCallBacks,&Pos,true))
		return;
	m_TLSCallBackCount=0;
	m_TLSCallBackFuncs=NULL;
	while(ReadFile(Pos+m_TLSCallBackCount*4,&Address,4) && m_TLSCallBackCount<MAX_PE_TLS_CALLBACK)
	{
		BIG_ENDIAN_DWORD(Address);
		if(Address==0)
			break;
		m_TLSCallBackCount++;
	}
	if(m_TLSCallBackCount>0)
	{
		if(m_TLSCallBackCount>=MAX_PE_TLS_CALLBACK)
		{
			m_TLSCallBackCount=0;
			return;
		}
		m_TLSCallBackFuncs = new DWORD[m_TLSCallBackCount];
		if(m_TLSCallBackFuncs==NULL)
			return;
		ReadFile(Pos,m_TLSCallBackFuncs,m_TLSCallBackCount*4);
#ifdef CODE_BIG_ENDIAN
		for(int n=0;n<m_TLSCallBackCount;n++)
			BIG_ENDIAN_DWORD(m_TLSCallBackFuncs[n]);
#endif
	}
	m_TLSDataSize = 0;
	if(TLSDir.AddressOfIndex)
	{
		m_TLSDataSize = TLSDir.EndAddressOfRawData -  TLSDir.StartAddressOfRawData;
		if(m_TLSDataSize>0 && m_TLSDataSize<MAX_PE_TLS_DATA_SIZE)
		{
			m_TLSData = new BYTE[m_TLSDataSize];
			if(m_TLSData==NULL)
			{
				SafeDelete(m_TLSCallBackFuncs);
				return;
			}
			ReadMemory(TLSDir.StartAddressOfRawData,m_TLSData,m_TLSDataSize);
			m_AddressOfTLSIndex = TLSDir.AddressOfIndex;
		}
		else
		{
			m_AddressOfTLSIndex = 0;
			m_TLSDataSize = 0;
		}
	}
}

void CPEFile::GetBaseReloc()
{
	ULPOS ImageRelocPos,ImageRelocBasePos;
	IMAGE_BASE_RELOC ImageReloc;
	if(m_PEHead.DataDirectory[IMAGE_DIRECTORY_ENTRY_BASERELOC].VirtualAddress==0)
		return;
    
    if(false==MapToFile(m_PEHead.DataDirectory[IMAGE_DIRECTORY_ENTRY_BASERELOC].VirtualAddress,&ImageRelocBasePos,false))
		return;

	m_BaseRelocCount=0;
	ImageRelocPos=ImageRelocBasePos;
	while(ReadFile(ImageRelocPos,&ImageReloc,sizeof(IMAGE_BASE_RELOC)))
	{
		BIG_ENDIAN_DWORD(ImageReloc.VirtualAddress);
		BIG_ENDIAN_DWORD(ImageReloc.BlockSize);
		if( ImageReloc.BlockSize ==0 ||
            ImageReloc.BlockSize>MAX_PE_TLS_BLOCK+sizeof(IMAGE_BASE_RELOC) ||
            ImageReloc.BlockSize<=sizeof(IMAGE_BASE_RELOC))
			break;
		m_BaseRelocCount++;
		ImageRelocPos+=ImageReloc.BlockSize;
	}
	if(m_BaseRelocCount<=0 || m_BaseRelocCount>MAX_PE_BASE_RELOC_PAGE)
	{
		m_BaseRelocCount = 0;
		return;
	}
	m_BaseReloc=new BASE_RELOC[m_BaseRelocCount];
	if(m_BaseReloc==NULL)
		return;
	ZeroMemory(m_BaseReloc,sizeof(BASE_RELOC)*m_BaseRelocCount);
	ImageRelocPos=ImageRelocBasePos;
	for(int n=0;n<m_BaseRelocCount;n++)
	{
		ReadFile(ImageRelocPos,&ImageReloc,sizeof(IMAGE_BASE_RELOC));
		BIG_ENDIAN_DWORD(ImageReloc.VirtualAddress);
		BIG_ENDIAN_DWORD(ImageReloc.BlockSize);
		m_BaseReloc[n].VirtualAddr=ImageReloc.VirtualAddress;
		m_BaseReloc[n].Count=(ImageReloc.BlockSize-sizeof(IMAGE_BASE_RELOC))/sizeof(WORD);
		if(m_BaseReloc[n].Count>MAX_PE_BASE_RELOC_PER_PAGE)
		{
			m_BaseReloc[n].Count=0;
			continue;
		}
		if(m_BaseReloc[n].Count>0)
			m_BaseReloc[n].TypeOffset=new WORD[m_BaseReloc[n].Count];
		if(m_BaseReloc[n].TypeOffset==NULL)
		{
			m_BaseRelocCount=n;
			break;
		}
		if(!ReadFile(ImageRelocPos+sizeof(IMAGE_BASE_RELOC),m_BaseReloc[n].TypeOffset,sizeof(WORD)*m_BaseReloc[n].Count))
		{
			delete m_BaseReloc[n].TypeOffset;
			m_BaseRelocCount=n;
			break;
		}
#ifdef CODE_BIG_ENDIAN
		for(int m=0;m<(int)m_BaseReloc[n].Count;m++)
			BIG_ENDIAN_WORD(m_BaseReloc[n].TypeOffset[m]);
#endif
		ImageRelocPos+=ImageReloc.BlockSize;
	}
}

void CPEFile::GetImportModule()
{
	ULPOS	Address;
 	int		ModuleCount,FuncCount;
	DWORD	ImportDescrPos,FuncCallAddr;
	DWORD*	TestFuncThunk;
	IMPORT_DESCR*	pImportDescr,*TestImportDescr;
	IMPORT_MODULE*	pImportModule;
	IMPORT_FUNC*	pImportFunc;
	if(m_PEHead.DataDirectory[IMAGE_DIRECTORY_ENTRY_IMPORT].VirtualAddress==0)
		return;

	/////////////////////////////////////////////////////////
	//取导入模块数并分配内存
	/////////////////////////////////////////////////////////	
	m_ImportModuleCount=ModuleCount=0;
	ImportDescrPos = m_PEHead.DataDirectory[IMAGE_DIRECTORY_ENTRY_IMPORT].VirtualAddress+m_ImageBase;
	TestImportDescr = new IMPORT_DESCR[MAX_PE_IMPORT_MODULE];
	if(TestImportDescr==NULL)
		return;
	while(ModuleCount<MAX_PE_IMPORT_MODULE)
	{
		if(ReadMemory(ImportDescrPos,&TestImportDescr[ModuleCount],sizeof(IMPORT_DESCR))!=sizeof(IMPORT_DESCR))
			break;
		BIG_ENDIAN_DWORD(TestImportDescr[ModuleCount].Characteristics);
		BIG_ENDIAN_DWORD(TestImportDescr[ModuleCount].TimeDateStamp);
		BIG_ENDIAN_DWORD(TestImportDescr[ModuleCount].ForwarderChain);
		BIG_ENDIAN_DWORD(TestImportDescr[ModuleCount].Name);
		BIG_ENDIAN_DWORD(TestImportDescr[ModuleCount].FirstThunk);
		if(TestImportDescr[ModuleCount].FirstThunk==0)
			break;
		ModuleCount++;
		ImportDescrPos+=sizeof(IMPORT_DESCR);
	}
	if(ModuleCount>=MAX_PE_IMPORT_MODULE || ModuleCount<=0)
		return;

	TestFuncThunk = new DWORD[MAX_PE_FUNC_PER_IMPORT_MODULE];
	if(TestFuncThunk==NULL)
	{
		delete TestImportDescr;
		return;
	}
	m_ImportModuleCount = ModuleCount;
	m_ImportModule=new IMPORT_MODULE[ModuleCount];
	if(m_ImportModule==NULL)
	{
		delete TestFuncThunk;
		delete TestImportDescr;
		return;
	}
	ZeroMemory(m_ImportModule,sizeof(IMPORT_MODULE)*ModuleCount);
	//分析模块,并填充信息
	ModuleCount=0;
	pImportModule = m_ImportModule;
	pImportDescr = TestImportDescr;
	while(ModuleCount<m_ImportModuleCount)
	{
		if(pImportDescr->FirstThunk==0)
			break;
		if(0==ReadString(pImportDescr->Name+m_ImageBase,pImportModule->FileName,sizeof(pImportModule->FileName)))
			break;
		pImportModule->Address=pImportDescr->Name+m_ImageBase;
		TGetFileTitle(pImportModule->FileName,pImportModule->ModuleName);
		//取导入函数个数
		FuncCount = 0;
		if(pImportDescr->OriginalFirstThunk)
		{
			FuncCount=ReadString(pImportDescr->OriginalFirstThunk+m_ImageBase,TestFuncThunk,MAX_PE_FUNC_PER_IMPORT_MODULE);
		}
		if(FuncCount==0)
		{
			FuncCount=ReadString(pImportDescr->FirstThunk+m_ImageBase,TestFuncThunk,MAX_PE_FUNC_PER_IMPORT_MODULE);
		}
		if(FuncCount==0)
			break;
		if(FuncCount<MAX_PE_FUNC_PER_IMPORT_MODULE)
		{
			pImportModule->FuncCount = FuncCount;
			pImportFunc=pImportModule->FuncList = new IMPORT_FUNC[FuncCount];
			if(pImportFunc==NULL)
			{
				if(m_ImportModule)
				{
					delete m_ImportModule;
					m_ImportModule = NULL;
					delete TestFuncThunk;
					delete TestImportDescr;
					return;
				}
			}
			ZeroMemory(pImportFunc,sizeof(IMPORT_FUNC)*FuncCount);
			FuncCount=0;
			FuncCallAddr=pImportDescr->FirstThunk;
			while(FuncCount<pImportModule->FuncCount)
			{
				BIG_ENDIAN_DWORD(TestFuncThunk[FuncCount]);
				Address = TestFuncThunk[FuncCount];
				pImportFunc->bUseOrd = (Address&0x80000000) && (Address<m_ImageBase || Address>=m_ImageHighBase);
				if(pImportFunc->bUseOrd)
				{
					pImportFunc->FuncOrd=LOW_WORD(TestFuncThunk[FuncCount]);
					TSPrintf(pImportFunc->FuncName,"Function_ORD_%04X",pImportFunc->FuncOrd);
				}
				else
				{
					pImportFunc->NameAddr = Address;
					if((m_FileObjType&FILE_OBJ_TYPE_OS_MEMORY_IMAGE)==0)
						pImportFunc->NameAddr+=m_ImageBase;
					else
					{
						if(Address<m_ImageBase)
							pImportFunc->NameAddr+=m_ImageBase;
					}
					if(ReadString(pImportFunc->NameAddr + 2,pImportFunc->FuncName,sizeof(pImportFunc->FuncName))==0)
						break;
				}
				pImportFunc->ThunkAddr=FuncCallAddr+m_ImageBase;
				FuncCount++;
				FuncCallAddr+=4;
				pImportFunc++;
			}//遍历导入函数
			pImportModule->FuncCount=FuncCount;
		}
		ModuleCount++;
		pImportModule++;
		pImportDescr++;
	}
	m_ImportModuleCount=ModuleCount;
	delete TestFuncThunk;
	delete TestImportDescr;
}

void CPEFile::GetExportFunc()
{
	EXPORT_DESCR Export;
	DWORD	FuncSize,NameSize;
	DWORD	FuncAddrPos,FuncNameAddrPos,FuncOrdPos;
	DWORD	FuncAddr,FuncNameAddr;
	WORD	FuncOrd;
	DWORD	n;
	m_ExportFuncCount = 0;
	if(m_PEHead.DataDirectory[IMAGE_DIRECTORY_ENTRY_EXPORT].VirtualAddress==0)
		return;
	if(ReadMemory(m_PEHead.DataDirectory[IMAGE_DIRECTORY_ENTRY_EXPORT].VirtualAddress+m_ImageBase,&Export,sizeof(EXPORT_DESCR))!=sizeof(EXPORT_DESCR))
		return;
    BIG_ENDIAN_DWORD(Export.Characteristics);
    BIG_ENDIAN_DWORD(Export.TimeDateStamp);
    BIG_ENDIAN_WORD(Export.MajorVersion);
    BIG_ENDIAN_WORD(Export.MinorVersion);
    BIG_ENDIAN_DWORD(Export.Name);
    BIG_ENDIAN_DWORD(Export.Base);
    BIG_ENDIAN_DWORD(Export.NumberOfFunctions);
    BIG_ENDIAN_DWORD(Export.NumberOfNames);
    BIG_ENDIAN_DWORD(Export.AddressOfFunctions);
    BIG_ENDIAN_DWORD(Export.AddressOfNames);
    BIG_ENDIAN_DWORD(Export.AddressOfNameOrdinals);
	FuncSize=Export.NumberOfFunctions;
	NameSize=Export.NumberOfNames;
	if(FuncSize>MAX_PE_FUNC_SIZE || FuncSize == 0|| NameSize>MAX_PE_SIZE_SIZE)
		return;
	m_ExportFunc=new EXPORT_FUNC[FuncSize];
	if(m_ExportFunc==NULL)
		return;
	ZeroMemory(m_ExportFunc,sizeof(EXPORT_FUNC)*(FuncSize));
	FuncNameAddrPos = Export.AddressOfNames;
	FuncOrdPos = Export.AddressOfNameOrdinals;
	FuncAddrPos = Export.AddressOfFunctions,&FuncAddrPos;
	for( n=0;n<FuncSize;n++)
	{
		if(ReadMemory(FuncNameAddrPos+m_ImageBase,&FuncNameAddr,sizeof(FuncNameAddr))==false)
			break;
		BIG_ENDIAN_DWORD(FuncNameAddr);
		if(n >= NameSize)
		{
			FuncOrd=(WORD)(n+Export.Base);
			TStrCpy(m_ExportFunc[n].FuncName,"Export_by_Ord_");
			uNumToStr(FuncOrd,&m_ExportFunc[n].FuncName[sizeof("Export_by_Ord_")-1],16);
		}
		else
		{
			ReadString(FuncNameAddr+m_ImageBase,m_ExportFunc[n].FuncName,sizeof(m_ExportFunc[n].FuncName));
			ReadMemory(FuncOrdPos+n*2+m_ImageBase,&FuncOrd,2);
			BIG_ENDIAN_WORD(FuncOrd);
		}
		if(FuncOrd<FuncSize)
		{
			if(ReadMemory(FuncAddrPos+FuncOrd*4+m_ImageBase,&FuncAddr,sizeof(FuncAddr))==false)
				break;
			BIG_ENDIAN_DWORD(FuncAddr);
			if(FuncAddr)
			{
				m_ExportFunc[n].Address=FuncAddr;
				m_ExportFunc[n].Address+=m_ImageBase;
			}
			m_ExportFunc[n].ThunkAddr = FuncAddrPos+FuncOrd*4+m_ImageBase;
			m_ExportFunc[n].FuncOrd=FuncOrd+Export.Base;
		}
		else
		{
			m_ExportFunc[n].Address=0;
			m_ExportFunc[n].ThunkAddr=0;
		}
		FuncNameAddrPos+=sizeof(DWORD);
	}
	m_ExportFuncCount=n;
}

void CPEFile::GetResource()
{
	DWORD RDSize;
	WORD  NameLength;
	DWORD Addr,ResBaseAddr,ResDirAddr;
	RESOURCE_DIRECTORY ResDir;
	RESOURCE_DIRECTORY_ENTRY ResDirEntry;
	RESOURCE_DATA_ENTRY	ResDataEntry;
	if(m_ResDir)
		return;
	if(m_PEHead.DataDirectory[IMAGE_DIRECTORY_ENTRY_RESOURCE].VirtualAddress==0)
		return;
	ResBaseAddr = m_PEHead.DataDirectory[IMAGE_DIRECTORY_ENTRY_RESOURCE].VirtualAddress+m_ImageBase;
	if(ReadMemory(ResBaseAddr,&ResDir,sizeof(RESOURCE_DIRECTORY))!=sizeof(RESOURCE_DIRECTORY))
		return;
    BIG_ENDIAN_DWORD(ResDir.Characteristics);
    BIG_ENDIAN_DWORD(ResDir.TimeDateStamp);
    BIG_ENDIAN_WORD(ResDir.MajorVersion);
    BIG_ENDIAN_WORD(ResDir.MinorVersion);
    BIG_ENDIAN_WORD(ResDir.NumberOfNamedEntries);
    BIG_ENDIAN_WORD(ResDir.NumberOfIdEntries);
	m_ResDirCount=ResDir.NumberOfIdEntries+ResDir.NumberOfNamedEntries;
	if(m_ResDirCount<=0 || m_ResDirCount>MAX_PE_RES_DIR)
	{
		m_ResDirCount=0;
		return;
	}
	m_ResDir=new RES_DIR[m_ResDirCount];
	if(m_ResDir==NULL)
		return;
	ZeroMemory(m_ResDir,m_ResDirCount*sizeof(RES_DIR));
	for(int nType=0;nType<m_ResDirCount;nType++)
	{//遍历类型目录
		Addr = ResBaseAddr + sizeof(RESOURCE_DIRECTORY) + nType*sizeof(RESOURCE_DIRECTORY_ENTRY);
		if(ReadMemory(Addr,&ResDirEntry,sizeof(RESOURCE_DIRECTORY_ENTRY)) != sizeof(RESOURCE_DIRECTORY_ENTRY))
			continue;
		BIG_ENDIAN_DWORD(ResDirEntry.Name);
		BIG_ENDIAN_DWORD(ResDirEntry.OffsetToData);
		if((ResDirEntry.OffsetToData&0x80000000)==0)
			continue;
		if(ResDirEntry.Name&0x80000000)
		{
			Addr = ResBaseAddr + ResDirEntry.Name&0xEFFFFFFF;
			if(ReadMemory(Addr,&NameLength,2) != 2)
				continue;
			BIG_ENDIAN_WORD(NameLength);
			RDSize = NameLength*2;
			if(RDSize>=MAX_NAME_LEN)
				continue;
			if(ReadMemory(Addr+2,m_ResDir[nType].TypeName,RDSize) != RDSize)
				continue;
			m_ResDir[nType].Type=INVALID_RES_TYPE;
		}
		else
		{
			m_ResDir[nType].Type=LOW_WORD(ResDirEntry.Name);
		}
		ResDirAddr=Addr=ResBaseAddr+ResDirEntry.OffsetToData&0x7FFFFFFF;
		if(ReadMemory(Addr,&ResDir,sizeof(RESOURCE_DIRECTORY)) != sizeof(RESOURCE_DIRECTORY))
			continue;
		BIG_ENDIAN_DWORD(ResDir.Characteristics);
		BIG_ENDIAN_DWORD(ResDir.TimeDateStamp);
		BIG_ENDIAN_WORD(ResDir.MajorVersion);
		BIG_ENDIAN_WORD(ResDir.MinorVersion);
		BIG_ENDIAN_WORD(ResDir.NumberOfNamedEntries);
		BIG_ENDIAN_WORD(ResDir.NumberOfIdEntries);
		m_ResDir[nType].ResCount=ResDir.NumberOfIdEntries+ResDir.NumberOfNamedEntries;
		if(m_ResDir[nType].ResCount<=0 || m_ResDir[nType].ResCount>MAX_PE_RES_PER_TYPE)
		{
			m_ResDir[nType].ResCount=0;
			continue;
		}
		if(m_ResDir[nType].ResCount)
			m_ResDir[nType].ResDataDir=new RES_DATA[m_ResDir[nType].ResCount];
		if(m_ResDir[nType].ResDataDir==NULL)
			continue;
		ZeroMemory(m_ResDir[nType].ResDataDir,sizeof(RES_DATA)*m_ResDir[nType].ResCount);
		if(m_ResDir[nType].ResDataDir==NULL)
			continue;
		for(int nRes=0;nRes<m_ResDir[nType].ResCount;nRes++)
		{
			Addr=ResDirAddr+sizeof(RESOURCE_DIRECTORY)+nRes*sizeof(RESOURCE_DIRECTORY_ENTRY);
			if(ReadMemory(Addr,&ResDirEntry,sizeof(RESOURCE_DIRECTORY_ENTRY)) != sizeof(RESOURCE_DIRECTORY_ENTRY))
				continue;
			BIG_ENDIAN_DWORD(ResDirEntry.Name);
			BIG_ENDIAN_DWORD(ResDirEntry.OffsetToData);
			if((ResDirEntry.OffsetToData&0x80000000)==0)
				continue;
			if(ResDirEntry.Name&0x80000000)
			{
				Addr=ResBaseAddr+ResDirEntry.Name&0x7FFFFFFF;
				if(ReadMemory(Addr,&NameLength,2) != 2)
					continue;				
				BIG_ENDIAN_WORD(NameLength);
				if(NameLength>sizeof(m_ResDir[nType].ResDataDir[nRes].IDName)/2)
					NameLength=sizeof(m_ResDir[nType].ResDataDir[nRes].IDName)/2;
				RDSize = NameLength*2;
				if(ReadMemory(Addr+2,m_ResDir[nType].ResDataDir[nRes].IDName,RDSize) != RDSize)
					continue;
				m_ResDir[nType].ResDataDir[nRes].IDName[RDSize/2]=0;
			}
			else
			{
				m_ResDir[nType].ResDataDir[nRes].ID=LOW_WORD(ResDirEntry.Name);
			}
			Addr=ResBaseAddr+ResDirEntry.OffsetToData&0x7FFFFFFF;
			if(ReadMemory(Addr,&ResDir,sizeof(RESOURCE_DIRECTORY)) != sizeof(RESOURCE_DIRECTORY))
				continue;
			BIG_ENDIAN_DWORD(ResDir.Characteristics);
			BIG_ENDIAN_DWORD(ResDir.TimeDateStamp);
			BIG_ENDIAN_WORD(ResDir.MajorVersion);
			BIG_ENDIAN_WORD(ResDir.MinorVersion);
			BIG_ENDIAN_WORD(ResDir.NumberOfNamedEntries);
			BIG_ENDIAN_WORD(ResDir.NumberOfIdEntries);
			if(ResDir.NumberOfIdEntries!=1)
				continue;
			Addr=Addr+sizeof(RESOURCE_DIRECTORY);
			if(ReadMemory(Addr,&ResDirEntry,sizeof(RESOURCE_DIRECTORY_ENTRY)) != sizeof(RESOURCE_DIRECTORY_ENTRY))
				continue;
			BIG_ENDIAN_DWORD(ResDirEntry.Name);
			BIG_ENDIAN_DWORD(ResDirEntry.OffsetToData);
			if(ResDirEntry.OffsetToData&0x80000000)
				continue;
			Addr = ResBaseAddr + ResDirEntry.OffsetToData&0x7FFFFFFF;
			if(ReadMemory(Addr,&ResDataEntry,sizeof(RESOURCE_DATA_ENTRY)) != sizeof(RESOURCE_DATA_ENTRY))
				continue;
			BIG_ENDIAN_DWORD(ResDataEntry.OffsetToData);
			BIG_ENDIAN_DWORD(ResDataEntry.Size);
			BIG_ENDIAN_DWORD(ResDataEntry.CodePage);
			BIG_ENDIAN_DWORD(ResDataEntry.Reserved);
			m_ResDir[nType].ResDataDir[nRes].CodePage=ResDataEntry.CodePage;
			m_ResDir[nType].ResDataDir[nRes].Size=ResDataEntry.Size;
			m_ResDir[nType].ResDataDir[nRes].BufferAddr = ResDataEntry.OffsetToData + m_ImageBase;
		}
	}
}

int CPEFile::GetLastPhyPosSection()
{
	DWORD LastPos;
	int  Index;
    LastPos=0;
    Index=0;
	for(int i=1;i<m_SectCount;i++)
	{
		if(m_Section[i].PointerToRawData>LastPos)
		{
			LastPos=m_Section[i].PointerToRawData;
 			Index=i;
		}
	}
	return Index;
}

int CPEFile::GetLastMemAddrSection()
{
	DWORD LastPos;
	int Index;
    LastPos=0;
    Index=0;
	for(int i=1;i<=m_SectCount;i++)
	{
		if(m_Section[i].VirtualAddress>LastPos)
		{
			LastPos=m_Section[i].VirtualAddress;
			Index=i;
		}
	}
	return Index;
}

int CPEFile::GetFirstPhyPosSection()
{
	int Index;
	DWORD LastPos;
    Index=0;
    LastPos=0;
	for(int i=1;i<=m_SectCount;i++)
	{
		if(m_Section[i].PointerToRawData<=LastPos)
		{
			LastPos=m_Section[i].PointerToRawData;
 			Index=i;
		}
	}
	return Index;
}

int CPEFile::GetFirstMemAddrSection()
{
	int Index;
	DWORD LastPos;
    Index=0;
    LastPos=0;
	for(int i=1;i<=m_SectCount;i++)
	{
		if(m_Section[i].VirtualAddress<=LastPos)
		{
			LastPos=m_Section[i].VirtualAddress;
			Index=i;
		}
	}
	return Index;
}

DWORD CPEFile::GetExportFunc(PCSTR FuncName,int*pIndex)
{
	for(int n=0;n<m_ExportFuncCount;n++)
	{
		if(!TStrCmp(m_ExportFunc[n].FuncName,FuncName))
		{
			if(pIndex)
				*pIndex = n;
			return m_ExportFunc[n].Address;
		}
	}
	return 0;
}

DWORD CPEFile::GetExportFunc(DWORD FuncOrd)
{
	for(int n=0;n<m_ExportFuncCount;n++)
	{
		if(m_ExportFunc[n].FuncOrd==FuncOrd)
			return m_ExportFunc[n].Address;
	}
	return 0;
}

int CPEFile::LoadStringW(DWORD StrID,PWORD szBuffer,int MaxLen)
{
	DWORD Offset,Length,Addr;
	RES_DIR*ResDir;
	DWORD StringTableID,StringID;
	int StrLen;
	BYTE* pData;
	int nStrTab;
	if(MaxLen<2)
	{
		*szBuffer=0;
		return 0;
	}
	GetResource();
	ResDir=NULL;
	for(int nType=0;nType<m_ResDirCount;nType++)
	{
		if(m_ResDir[nType].Type==RES_TYPE_STRING)
		{
			ResDir=&m_ResDir[nType];
			break;
		}
	}
	if(ResDir==NULL)
		return 0;
	StringTableID=StrID/16+1;
	for( nStrTab=0;nStrTab<ResDir->ResCount;nStrTab++)
	{
		if(StringTableID==ResDir->ResDataDir[nStrTab].ID)
		{
			Addr=ResDir->ResDataDir[nStrTab].BufferAddr;
			Length=ResDir->ResDataDir[nStrTab].Size;
			break;
		}
	}
	if(nStrTab>=ResDir->ResCount || Addr==0)
	{
		*szBuffer=0;
		return 0;
	}
	StringID=StrID%16;
	if(Length>=MAX_PE_BUFFER_SIZE)
	{
		*szBuffer=0;
		return 0;
	}
	pData=new BYTE[Length];
	if(pData==NULL)
	{
		*szBuffer=0;
		return 0;
	}
	if(ReadMemory(Addr,pData,Length) == 0)
	{
		delete pData;
		*szBuffer=0;
		return 0;
	}
	Offset=0;
	while(Offset<Length && StringID)
	{
		StrLen=GET_WORD(pData,Offset);
		Offset+=2;
		if(StrLen)
			Offset+=StrLen*2;
		StringID--;
	}
	if(StringID>0 || Offset>=Length)
	{
		delete pData;
		*szBuffer=0;
		return 0;
	}
	StrLen=GET_WORD(pData,Offset);
	Offset+=2;
	MAX_LIMIT(StrLen,(MaxLen-2)/2);
	if(Offset+StrLen*2<=Length)
		memcpy(szBuffer,RT_PWORD(pData,Offset),StrLen*2);
	else
		StrLen=0;
	szBuffer[StrLen]=0;
	delete pData;
	return StrLen;
}

int CPEFile::LoadStringA(DWORD StrID,PSTR szBuffer,int MaxLen)
{
	int StrLen;
	PWORD pWStr=new WORD[MaxLen];
	if(pWStr==NULL)
		return false;
	*pWStr=0;
	LoadStringW(StrID,pWStr,MaxLen*2);
	StrLen=0;
	while(pWStr[StrLen])
	{
		szBuffer[StrLen]=(CHAR)pWStr[StrLen];
		StrLen++;
	}
	szBuffer[StrLen]=0;
	delete pWStr;
	return StrLen;
}

RES_DATA* CPEFile::FindResource(const PWORD szResID,DWORD ResID,const PWORD szType,DWORD Type)
{
	DWORD Length,Addr;
	RES_DIR*ResDir;
	GetResource();
	ResDir=NULL;
	for(int nType=0;nType<m_ResDirCount;nType++)
	{
		if(szType)
		{
			if(TStrICmp(m_ResDir[nType].TypeName,szType)==0)
			{
				ResDir=&m_ResDir[nType];
				break;
			}
		}
		else
		{
			if(m_ResDir[nType].Type==Type)
			{
				ResDir=&m_ResDir[nType];
				break;
			}
		}
	}
	if(ResDir==NULL)
		return NULL;
	for(int nStrTab=0;nStrTab<ResDir->ResCount;nStrTab++)
	{
		if(szResID)			
		{
			if(TStrICmp(ResDir->ResDataDir[nStrTab].IDName,szResID)==0)
			{
				Addr=ResDir->ResDataDir[nStrTab].BufferAddr;
				Length=ResDir->ResDataDir[nStrTab].Size;
				return &ResDir->ResDataDir[nStrTab];
			}
		}
		else
		{
			if(ResID==ResDir->ResDataDir[nStrTab].ID)
			{
				Addr=ResDir->ResDataDir[nStrTab].BufferAddr;
				Length=ResDir->ResDataDir[nStrTab].Size;
				return &ResDir->ResDataDir[nStrTab];
			}
		}
	}
	return NULL;
}

bool  CPEFile::GetSectionIndex(IN DWORD Address,OUT int*pIndex)
{
	Address-=m_ImageBase;
	for(int n=0;n<m_SectCount;n++)
	{
		if(Address>=m_Section[n].VirtualAddress && Address<m_Section[n].VirtualAddress + m_Section[n].VirtualSize)
        {
            if(pIndex)
                *pIndex=n;
            return true;
        }
	}
	return false;
}

bool CPEFile::Check()
{
	if(m_ImageBase==0 || m_ImageSize==0)
	{
		m_ErrorCode = PE_ERROR_HEAD;
		return false;
	}
	return true;
}

IMPORT_MODULE* CPEFile::GetImportModule(PCSTR ModuleName)
{
	for(int n=0;n<m_ImportModuleCount;n++)
	{
		if( TStrICmp(m_ImportModule[n].FileName,ModuleName)==0 ||
			TStrICmp(m_ImportModule[n].ModuleName,ModuleName)==0)
			return &m_ImportModule[n];
	}
	return NULL;
}

IMPORT_FUNC* CPEFile::GetImportFunc(IMPORT_MODULE*pModule,PCSTR FuncName)
{
	for(int n=0;n<pModule->FuncCount;n++)
	{
		if( TStrICmp(pModule->FuncList[n].FuncName,FuncName)==0)
			return &pModule->FuncList[n];
	}
	return NULL;
}

IMPORT_FUNC* CPEFile::GetImportModuleFunc(PCSTR ModuleName,PCSTR FuncName)
{
	IMPORT_MODULE*pModule = GetImportModule(ModuleName);
	if(pModule==NULL)
	{
		return NULL;
	}
	return GetImportFunc(pModule,FuncName);
}
bool CPEFile::GetDataDirectory(IN int Index,OUT PPE_DATA_DIR DataDirectory)const
{
	if(Index>=MAX_PE_DATA_DIR)
		return false;
	if(DataDirectory)
		*DataDirectory=m_PEHead.DataDirectory[Index];
	return true;
}

bool CMemPEFile::Open(ULPOS ModuleBase,UINT OpenMode,IN RWProc RMFunc,IN void*RMObj)
{
	if(OpenMode)
		m_OpenMode|=OpenMode;
	SetRMProc(RMFunc,RMObj);
	m_ImageBase = ModuleBase;
	m_FileObjType = FILE_OBJ_TYPE_OS_MEMORY_IMAGE;
	return CPEFile::Open(NULL);
}
