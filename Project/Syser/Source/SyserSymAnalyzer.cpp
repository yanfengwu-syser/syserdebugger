#include "StdAfx.h"
#include "Syser.h"
#include "SyserSymAnalyzer.h"

SDBASETYPENAME BaseTypeNameStruct[27]=
{
	{btNoType,"NoType"},
	{btVoid,"void"},
	{btInt1,"char"},
	{btInt2,"wchar"},
	//{btInt,"short"},
	{btInt1,"char"},
	{btInt2,"short"},
	{btInt4,"int"},
	{btInt8,"__int64"},
	{btUint2,"unsigned short int"},
	{btUint1,"unsigned char"},
	{btUint2,"unsigned short"},
	{btUint4,"unsigned int"},
	{btUint8,"unsigned __int64"},
	{btInt4,"float"},
	{btInt8,"double"},
	{btBCD,"BCD"},
	{btUint1,"bool"},
	{btInt4,"long"},
	{btUint4,"unsigned long"},
	{btCurrency,"Currency"},
	{btDate,"date"},
	{btVariant,"variant"},
	{btComplex,"complex"},
	{btBit,"bit"},
	{btBSTR,"BSTR"},
	{btHresult,"HRESULT"},
};

DWORD GetBaseTypeIdByName(char*Name)
{
	DWORD i,Count = sizeof(BaseTypeNameStruct)/sizeof(BaseTypeNameStruct[0]);
	for(i = 0; i < Count; i++)
	{
		if(TStrCmp(BaseTypeNameStruct[i].Name,Name)==0)
			return BaseTypeNameStruct[i].Type;
	}
	return 0;
}

void CSDSModule::SetModuleFileName(PCSTR szFileName)
{
	m_ModuleFileName = szFileName;
}

bool CSDSModule::LoadSymFile(PCSTR FileName)
{
	SDSYMBOLFILE SymFileHeader;
	ULLSIZE ReadLen;
	if(m_bInitOK)
		return true;
	if(gpFileIO->OpenFile(FileName,&m_hFileHandle)==false)
	{
		return false;
	}
	memset(&SymFileHeader,0,sizeof(SymFileHeader));
	ReadLen = gpFileIO->ReadFile(m_hFileHandle,&SymFileHeader,sizeof(SymFileHeader),0);
	if(ReadLen!=sizeof(SymFileHeader))
	{
		gpFileIO->CloseHandle(m_hFileHandle);		
		return false;
	}
	if(SymFileHeader.Version!=SYSER_DEBUG_SYMBOL_FILE_VER)
	{
		gpFileIO->CloseHandle(m_hFileHandle);		
		return false;
	}
	m_SymFileSize = gpFileIO->GetFileLength(m_hFileHandle);
	if(IsHeapFreeBelow(SYSER_SOURCE_DEBUG_HEAP,m_SymFileSize*2))
	{
		return false;
	}
	m_FileBuffer = new char[(unsigned int)m_SymFileSize];
	if(m_FileBuffer==NULL)
	{
		gpFileIO->CloseHandle(m_hFileHandle);
		return false;
	}
	ReadLen = gpFileIO->ReadFile(m_hFileHandle,m_FileBuffer,(ULSIZE)m_SymFileSize,0);
	if(ReadLen!=m_SymFileSize)
	{
		gpFileIO->CloseHandle(m_hFileHandle);
		delete []m_FileBuffer;
		return false;
	}
	if(CheckSDSymbolFileCheckSum()==false)
	{
		gpFileIO->CloseHandle(m_hFileHandle);
		delete []m_FileBuffer;		
		return false;
	}
	m_SDSymbolFile = (PSDSYMBOLFILE)m_FileBuffer;
	SymRelocation(m_SDSymbolFile);
	gpFileIO->CloseHandle(m_hFileHandle);
	CreateName2IDMap();
	m_SymbolFileName = FileName;
	m_bInitOK=true;
	return true;
}

void CSDSModule::UnloadSymFile()
{
	if(m_bInitOK==false)
		return ;
	if(m_FileBuffer)
		delete []m_FileBuffer;
	//m_SymbolMap.Clear();
	DeleteName2IDMap();
	m_bInitOK=false;
}

CSDSModule::CSDSModule()
{
	m_SymFileSize=0;
	m_hFileHandle=NULL;
	m_SDSymbolFile=NULL;
	m_FileBuffer=NULL;		
	m_StrTable=NULL;
	m_bInitOK=false;
	m_MemoryUsed = 0;
	m_ParentPID = 0;
}

CSDSModule::~CSDSModule()
{
	UnloadSymFile();
}


MODULE_ID CSDSModule::GetSDSMouleID(PCSTR szSDSFileName)
{
	HANDLE hFile;
	SDSYMBOLFILE SymFileHeader;
	ULSIZE ReadLen;
	if(gpFileIO->OpenFile(szSDSFileName,&hFile)==false)
		return 0;
	STZeroMemory(SymFileHeader);
	ReadLen = gpFileIO->ReadFile(hFile,&SymFileHeader,sizeof(SymFileHeader),0);
	gpFileIO->CloseHandle(hFile);
	if(ReadLen!=sizeof(SymFileHeader) || SymFileHeader.Sig!=SYSER_DEBUG_SYMBOL_FILE_SIG ||SymFileHeader.Version!=SYSER_DEBUG_SYMBOL_FILE_VER)
		return 0;
	return MAKE_MODULE_ID(SymFileHeader.ModuleID.OrgPECheckSum,SymFileHeader.ModuleID.TimeDateStamp);
}

MODULE_ID CSDSModule::GetModuleID()
{
	if(m_SDSymbolFile==NULL)
		return 0;
	return MAKE_MODULE_ID(m_SDSymbolFile->ModuleID.OrgPECheckSum,m_SDSymbolFile->ModuleID.TimeDateStamp);
}

PSDSOURCEFILEID CSDSModule::GetSourceFileList(OUT DWORD *SourceFileNum)const
{
	if(SourceFileNum)
		*SourceFileNum=m_SDSymbolFile->SourceFileCounter;
	return m_SDSymbolFile->UnionSourceFileIDTable.SourceFileIDTablePointer;
}
DWORD CSDSModule::GetSourceFileCountInPackages()const
{
	return m_SDSymbolFile->PackageSourceFileCounter;
}
/*
const char* CSDSModule::GetSymbolNameByRVA(DWORD Rva)
{
	SYMORDATAINDEXLIST::IT FindIt;
	SYMORDATAINDEX FindValue;
	FindValue.Rva=Rva;
	FindIt = m_SymbolMap.Find(FindValue);	
	if(FindIt==m_SymbolMap.End())
		return NULL;
	return GetSymbolName(*FindIt);		
}
*/
void CSDSModule::SymRelocation(PSDSYMBOLFILE pSymbolFile)
{
	DWORD *SymIndexTable;
	DWORD *StrIndexTable;
	DWORD *FunctionIndexTable;
	DWORD TempDword;
	DWORD i;
	DWORD BaseAddress=*(DWORD*)&pSymbolFile;	
	PSDTYPE_INFILE pType;
	PSDUDTDATAITEM pUdtDataItem;
	PSDFUNCTIONITEM pFuncItem;
	PSDSOURCEFILEID pSourceFileID;
	//SYMORDATAINDEX SymOrDataIndex={0,0,0};
	DWORD StringTableBaseAddress;

	////////////////////////////////////////////////////////////////////////
	//////重定位 串索引表
	////////////////////////////////////////////////////////////////////////
	TempDword = BaseAddress+pSymbolFile->UnionStringIndexTable.StringIndexTableOffset;
	StrIndexTable=*(DWORD**)&TempDword;
	m_StrTable=(char**)StrIndexTable;
	StringTableBaseAddress=BaseAddress+pSymbolFile->UnionStringTable.StringTableOffset;
	for(i = 0; i < pSymbolFile->StringTotalNum; i++)
	{
		StrIndexTable[i]+=StringTableBaseAddress;
	}
	////////////////////////////////////////////////////////////////////////
	//////重定位 符号文件头
	////////////////////////////////////////////////////////////////////////
	BYTE* TempPtr=(BYTE*)pSymbolFile;
	pSymbolFile->UnionLineNumber.pLineNumberTablePointer =(PSDLINE)&TempPtr[m_SDSymbolFile->UnionLineNumber.LineNumberOffset];
	
	pSymbolFile->UnionFunctionSymbolIndexTable.FunctionSymbolIndexTablePointer = (PSDFUNCTIONITEM*)&TempPtr[pSymbolFile->UnionFunctionSymbolIndexTable.FunctionSymbolIndexTableOffset];
	pSymbolFile->UnionSymbolIndexTable.SymbolIndexTablePointer = (PSDTYPE_INFILE*)&TempPtr[pSymbolFile->UnionSymbolIndexTable.SymbolIndexTableOffset];
	pSymbolFile->UnionSourceFileIDTable.SourceFileIDTablePointer =(PSDSOURCEFILEID)&TempPtr[pSymbolFile->UnionSourceFileIDTable.SourceFileIDTableOffset];
	pSymbolFile->UnionDataInformation.DataInformationPointer =(PSDUDTDATAITEM)&TempPtr[pSymbolFile->UnionDataInformation.DataInformationOffset];
	pSymbolFile->UnionPublicSymbol.PublicSymbolPointer =(PSDPUBLICSYMBOL) &TempPtr[pSymbolFile->UnionPublicSymbol.PublicSymbolOffset];
	if(pSymbolFile->uPDBFileName.PDBFileNameOffset)
		pSymbolFile->uPDBFileName.PDBFileName=(char*)&TempPtr[pSymbolFile->uPDBFileName.PDBFileNameOffset];
	else
		pSymbolFile->uPDBFileName.PDBFileName = m_StrTable[0];
	if(pSymbolFile->uPEFileName.PEFileNameOffset)
		pSymbolFile->uPEFileName.PEFileName=(char*)&TempPtr[pSymbolFile->uPEFileName.PEFileNameOffset];
	else
		pSymbolFile->uPEFileName.PEFileName = m_StrTable[0];
	
	if(pSymbolFile->uPEFileFullName.PEFileFullNameOffset)
		pSymbolFile->uPEFileFullName.PEFileFullName=(char*)&TempPtr[pSymbolFile->uPEFileFullName.PEFileFullNameOffset];
	else
		pSymbolFile->uPEFileFullName.PEFileFullName = m_StrTable[0];
	
	////////////////////////////////////////////////////////////////////////
	//////重定位 source code file 表
	////////////////////////////////////////////////////////////////////////		
	pSourceFileID =pSymbolFile->UnionSourceFileIDTable.SourceFileIDTablePointer;
	for(i = 0; i < pSymbolFile->SourceFileCounter;i++)
	{
		pSourceFileID[i].uName.Name=m_StrTable[pSourceFileID[i].uName.MemberNameInStringTableIndex];
		pSourceFileID[i].OffsetAtFile+=BaseAddress;
	}
	////////////////////////////////////////////////////////////////////////
	//////重定位 符号索引表
	////////////////////////////////////////////////////////////////////////		
	SymIndexTable=(DWORD*)pSymbolFile->UnionSymbolIndexTable.SymbolIndexTablePointer;		
	//SymOrDataIndex.Type = RVA_FUNCTION_BODY;
	for(i = 0; i < pSymbolFile->SymbolTotalNum; i++)
	{
		SymIndexTable[i]+=BaseAddress;
		pType=*(PSDTYPE_INFILE*)&SymIndexTable[i];
		pType->uName.Name = m_StrTable[pType->uName.StringTableIndex];
		if(pType->Type==SD_ENUMERATION)
		{
			PSDENUMERATIONTYPE pEnum = (PSDENUMERATIONTYPE)&pType[1];
			DWORD EnumCount = pEnum->DataCount;
			for(DWORD j = 0; j < EnumCount;j++)
			{
				pEnum->EnumerationDataMember[j].u.Name=m_StrTable[pEnum->EnumerationDataMember[j].u.MemberNameInStringTableIndex];
			}
		}
		if(pType->Type==SD_STRUCT||pType->Type==SD_CLASS||pType->Type==SD_UNION)
		{
			PSDUDTTYPE pUdtType = (PSDUDTTYPE)&pType[1];
			if(pUdtType->DataCounter)
				pUdtType->pData.DataMemberOffset += *(DWORD*)&pType; 
			else
				pUdtType->pData.DataMemberOffset=0;
			if(pUdtType->FunctionCounter)
				pUdtType->pFunction.FunctionMemberOffset += *(DWORD*)&pType;
			else
				pUdtType->pFunction.FunctionMemberOffset=0;
			if(pUdtType->BaseClassCounter)
				pUdtType->pBaseClass.BaseClassMemberOffset += *(DWORD*)&pType;
			else
				pUdtType->pBaseClass.BaseClassMemberOffset=0;
			if(pUdtType->VTableCount)
				pUdtType->pVTable.VTableMemberOffset += *(DWORD*)&pType;
			else
				pUdtType->pVTable.VTableMemberOffset=0;
		}
	}
	////////////////////////////////////////////////////////////////////////
	//////重定位 函数索引表
	////////////////////////////////////////////////////////////////////////		
	FunctionIndexTable=(DWORD*)pSymbolFile->UnionFunctionSymbolIndexTable.FunctionSymbolIndexTablePointer;
	PSDFUNCTIONITEM* pFuncItemArray=(PSDFUNCTIONITEM*)FunctionIndexTable;
	//SymOrDataIndex.Type = RVA_FUNCTION_BODY;
	for(i = 1; i < pSymbolFile->FunctionSymbolNum; i++)
	{
		FunctionIndexTable[i]+=BaseAddress;
		pFuncItem=*(PSDFUNCTIONITEM*)&FunctionIndexTable[i];
		if(pFuncItem->DataCounter)
			pFuncItem->pData.DataMemberOffset+=(*(DWORD*)&pFuncItem);
		else
			pFuncItem->pData.DataMemberOffset=0;
		if(pFuncItem->BlockCounter)
			pFuncItem->pBlock.BlockOffset+=(*(DWORD*)&pFuncItem);
		else
			pFuncItem->pBlock.BlockOffset=0;
		pFuncItem->uName.Name = m_StrTable[pFuncItem->uName.MemberNameInStringTableIndex];		
		//SymOrDataIndex.Name = pFuncItem->uName.Name;			
		//SymOrDataIndex.Index=i;
		//SymOrDataIndex.Rva=pFuncItem->Rva;
		//m_SymbolMap.Append(SymOrDataIndex);
	}
	////////////////////////////////////////////////////////////////////////
	//////重定位 数据表
	////////////////////////////////////////////////////////////////////////				
	//SymOrDataIndex.Type=RVA_DATA_ITEM;
	PSDUDTDATAITEM pDataArray = pSymbolFile->UnionDataInformation.DataInformationPointer;
	for(i = 0; i < pSymbolFile->DataInformationNum; i++)
	{		
		pUdtDataItem=&pDataArray[i];
		pUdtDataItem->uName.Name = m_StrTable[pUdtDataItem->uName.StringTableIndex];
		if(pUdtDataItem->Location==LocIsStatic)
		{
			//SymOrDataIndex.Name = pUdtDataItem->uName.Name;
			//SymOrDataIndex.Index=i;
			//SymOrDataIndex.Rva=pUdtDataItem->u.LOCISSTATIC.Rav;
			//m_SymbolMap.Append(SymOrDataIndex);
		}
	}
	//SymOrDataIndex.Type=RVA_PUBLIC_SYMBOL;
	TempDword = pSymbolFile->PublicSymbolCounter;
	PSDPUBLICSYMBOL pPubArray = pSymbolFile->UnionPublicSymbol.PublicSymbolPointer;
	for(i = 0; i < TempDword; i++)
	{
		pPubArray[i].uName.Name = m_StrTable[pPubArray[i].uName.StringTableIndex];
		pPubArray[i].UndecoratedName.Name = m_StrTable[pPubArray[i].UndecoratedName.StringTableIndex];
		//SymOrDataIndex.Name = pPubArray[i].uName.Name;
		//SymOrDataIndex.Index=i;
		//SymOrDataIndex.Rva=pPubArray[i].Rva;
		//m_SymbolMap.Append(SymOrDataIndex);
	}
}
PSDPUBLICSYMBOL CSDSModule::GetPublicSymbol(unsigned int index)const
{
	if(index >= m_SDSymbolFile->PublicSymbolCounter)
		index=0;
	return &m_SDSymbolFile->UnionPublicSymbol.PublicSymbolPointer[index];
}
PSDUDTDATAITEM CSDSModule::GetDataSymbolByNameAndLocation(char* Name,int nLocation)const
{
	DWORD dwDataCount;
	PSDUDTDATAITEM pDataItem,pDataItemArray;
	dwDataCount=m_SDSymbolFile->DataInformationNum;
	pDataItemArray = m_SDSymbolFile->UnionDataInformation.DataInformationPointer;
	for(DWORD i = 1; i < dwDataCount;i++)
	{
		pDataItem = &pDataItemArray[i];
		//if(pDataItem->Location==nLocation)
		{
			if(TStrCmp(Name,pDataItem->uName.Name)==0)
				return pDataItem;
		}
	}
	return NULL;
}
PSDUDTDATAITEM CSDSModule::GetDataSymbolByName(char* Name)const
{
	DWORD dwDataCount;
	PSDUDTDATAITEM pDataItem,pDataItemArray;
	dwDataCount=m_SDSymbolFile->DataInformationNum;
	pDataItemArray = m_SDSymbolFile->UnionDataInformation.DataInformationPointer;
	for(DWORD i = 1; i < dwDataCount;i++)
	{
		pDataItem = &pDataItemArray[i];		
		if(TStrCmp(Name,pDataItem->uName.Name)==0)
			return pDataItem;		
	}
	return NULL;
}
PSDUDTDATAITEM CSDSModule::GetDataSymbolByNameAndKind(const char* Name,int nDataKind)const
{
	DWORD dwDataCount;
	PSDUDTDATAITEM pDataItem,pDataItemArray;
	dwDataCount=m_SDSymbolFile->DataInformationNum;
	pDataItemArray = m_SDSymbolFile->UnionDataInformation.DataInformationPointer;
	for(DWORD i = 1; i < dwDataCount;i++)
	{
		pDataItem = &pDataItemArray[i];
		if(pDataItem->KindData==nDataKind)
		{
			if(TStrCmp(Name,pDataItem->uName.Name)==0)
				return pDataItem;
		}
	}
	return NULL;
}

PSDUDTDATAITEM CSDSModule::GetDataSymbol(unsigned int index)const 
{
	if(index >= m_SDSymbolFile->DataInformationNum)
		index = 0;
	return &m_SDSymbolFile->UnionDataInformation.DataInformationPointer[index];
}
const char* CSDSModule::GetTypeNameByID(unsigned int id)const
{
	if(id >=m_SDSymbolFile->SymbolTotalNum)
		id = 0;
	return GetTypeSymbol(id)->uName.Name;
}
PSDTYPE_INFILE CSDSModule::GetTypeSymbol(unsigned int index)const
{
	if(index >=m_SDSymbolFile->SymbolTotalNum)
		index = 0;
	return m_SDSymbolFile->UnionSymbolIndexTable.SymbolIndexTablePointer[index];
}
const char* CSDSModule::GetDataName(PSDUDTDATAITEM pUdtDataItem)const
{
	
	if(pUdtDataItem==NULL)
		return m_StrTable[0];
	return pUdtDataItem->uName.Name;
}
const char* CSDSModule::GetTypeName(PSDTYPE_INFILE pSDType)const
{
	
	if(pSDType==NULL)
		return m_StrTable[0];
	return pSDType->uName.Name;
}
const char* CSDSModule::GetPublicSymbolName(PSDPUBLICSYMBOL pSDPublicSymbol)const
{
	if(pSDPublicSymbol==NULL)
		return m_StrTable[0];
	return pSDPublicSymbol->uName.Name;
}
/*
const char* CSDSModule::GetSymbolName(SYMORDATAINDEX Symbol)const
{
	if(Symbol.Type==RVA_FUNCTION_BODY)
		return GetTypeName(GetTypeSymbol(Symbol.Index));
	if(Symbol.Type==RVA_DATA_ITEM)
		return GetDataName(GetDataSymbol(Symbol.Index));
	if(Symbol.Type==RVA_PUBLIC_SYMBOL)
		return GetPublicSymbolName(GetPublicSymbol(Symbol.Index));
	return NULL;
}
*/
void* CSDSModule::GetSymbolAddressBySymbolName(IN const char* SymbolName,OUT DWORD* SymbolLength)
{
	return NULL;	
}
PSDSOURCEFILEID CSDSModule::GetSourceFileByID(IN DWORD SourceFileId)const
{
	DWORD i;
	DWORD dwFileTotalNum=m_SDSymbolFile->SourceFileCounter;
	PSDSOURCEFILEID pSourceFileId = m_SDSymbolFile->UnionSourceFileIDTable.SourceFileIDTablePointer;
	for(i =0;i < dwFileTotalNum;i++)
		if(pSourceFileId[i].FileID==SourceFileId)
			return &pSourceFileId[i];
	return NULL;
}
PSDSOURCEFILEID CSDSModule::GetSourceFileByName(const char* SourceFileName)const
{
	DWORD i;
	char* FileName;
	DWORD dwFileTotalNum=m_SDSymbolFile->SourceFileCounter;
	PSDSOURCEFILEID pSourceFileId = m_SDSymbolFile->UnionSourceFileIDTable.SourceFileIDTablePointer;
	for(i =0;i < dwFileTotalNum;i++)
	{
		FileName=TStrRChr(pSourceFileId[i].uName.Name,'\\');
		if(FileName)
		{
			FileName++;
			if(TStrICmp(FileName,SourceFileName)==0)
				return &pSourceFileId[i];
		}
	}
	return NULL;
}
DWORD CSDSModule::GetLineBySourceFileID(DWORD SourceFileId,SDLINELIST* Line)const
{
	DWORD Count=0;
	DWORD i;
	DWORD dwLineTotalNum=m_SDSymbolFile->LineNumberCounter;
	PSDLINE pLine = m_SDSymbolFile->UnionLineNumber.pLineNumberTablePointer;
	for(i = 0; i < dwLineTotalNum;i++)
	{
		if(pLine[i].FileID==SourceFileId)
		{
			if(Line)
				Line->Append(&pLine[i]);
			Count++;
		}
	}
	return Count;
}
DWORD CSDSModule::GetLineFromRva(DWORD Rva,SDLINELIST* Line)const
{
	DWORD Count=0;
	DWORD dwLineTotalNum=m_SDSymbolFile->LineNumberCounter;
	PSDLINE pLine = m_SDSymbolFile->UnionLineNumber.pLineNumberTablePointer;
	DWORD i;
	for(i = 0; i < dwLineTotalNum;i++)
	{
		if(Rva >= pLine[i].Rva &&Rva < pLine[i].Rva + pLine[i].Len)
		{
			if(Line)
				Line->Append(&pLine[i]);
			Count++;
		}
	}
	return Count;
}
DWORD CSDSModule::GetLineByRva(DWORD Rva,SDLINELIST* Line)const
{
	DWORD Count=0;
	DWORD Begin,End;
	DWORD dwTotalNum = m_SDSymbolFile->LineNumberCounter; 
	PSDLINE pLine=m_SDSymbolFile->UnionLineNumber.pLineNumberTablePointer;
	Begin=0;
	End=dwTotalNum-1;
	for(;Begin<=End;)
	{
		if(Rva>pLine[(Begin+End)/2].Rva)
			Begin=(Begin+End)/2;
		else if(Rva==pLine[(Begin+End)/2].Rva)
		{
			Line->Append(&pLine[(Begin+End)/2]);
			Count=1;
			break;
		}
		else
			End=(Begin+End)/2;
	}
	return Count;
}
DWORD CSDSModule::GetLineBySourceFileID(IN DWORD SourceFileId,INOUT LINENUMBERMAP* LineMap)const
{
	DWORD Count=0;
	SDLINEINFO SDLineInfo;
	LINENUMBERMAP::IT FindIT;
	DWORD dwTotalNum = m_SDSymbolFile->LineNumberCounter;
	PSDLINE pLine=m_SDSymbolFile->UnionLineNumber.pLineNumberTablePointer;

	for(unsigned int i = 0; i < dwTotalNum;i++)
	{
		if(pLine[i].FileID==SourceFileId)
		{
			SDLineInfo.Number=1;
			SDLineInfo.pLine=&pLine[i];
			if(LineMap)
			{
				FindIT = LineMap->InsertUnique(pLine[i].LineNumber,SDLineInfo);
				if(FindIT==LineMap->End())
				{
					FindIT=LineMap->Find(pLine[i].LineNumber);
					(*FindIT).Number++;
				}
			}
			Count++;
		}
	}
	if(Count>1)
		Count--,Count++;
	return Count;
}
DWORD CSDSModule::GetLineBySourceFileID(DWORD SourceFileId,DWORD LineNum,SDLINELIST* Line)const
{
	DWORD Count=0;
	DWORD dwTotalNum = m_SDSymbolFile->LineNumberCounter;
	PSDLINE pLine=m_SDSymbolFile->UnionLineNumber.pLineNumberTablePointer;
	for(unsigned int i = 0; i < dwTotalNum;i++)
	{
		if(pLine[i].FileID==SourceFileId&&pLine[i].LineNumber==LineNum)
		{
			if(Line)
				Line->Append(&pLine[i]);
			Count++;
		}
	}
	if(Count>1)
		Count--,Count++;
	return Count;
}
PSDLINE CSDSModule::GetContiguityLineBySourceFileID(DWORD SourceFileId,DWORD LineNum)const

{
	DWORD CurrentLineNum=0xffffffff;
	DWORD LineTotalNum;
	PSDLINE pCurrentLine=NULL,pLine=m_SDSymbolFile->UnionLineNumber.pLineNumberTablePointer; 
	DWORD Count=0;
	LineTotalNum = m_SDSymbolFile->LineNumberCounter;
	for(unsigned int i = 0; i < LineTotalNum;i++)
	{
		if(pLine[i].FileID==SourceFileId&&pLine[i].LineNumber>LineNum)
		{
			if(CurrentLineNum > pLine[i].LineNumber)
				pCurrentLine = &pLine[i],CurrentLineNum=pLine[i].LineNumber;
		}
	}
	return pCurrentLine;
}
PSDFUNCTIONITEM CSDSModule::GetFunctionByLineNumber(IN DWORD FileId,IN DWORD LineNum)const
{
	SDLINELIST LineList;
	PSDLINE pLine;
	if(GetLineBySourceFileID(FileId,LineNum,&LineList))
		pLine = *LineList.Begin();
	else
		pLine = GetContiguityLineBySourceFileID(FileId,LineNum);
	if(pLine==NULL)
		return NULL;
	return GetFunctionFromRav(pLine->Rva);
}
PSDFUNCTIONITEM CSDSModule::GetFunctionFromRav(DWORD Rva)const
{
	DWORD FunctionTotalNum=m_SDSymbolFile->FunctionSymbolNum;
	PSDFUNCTIONITEM* pFuncArray = m_SDSymbolFile->UnionFunctionSymbolIndexTable.FunctionSymbolIndexTablePointer;
	PSDFUNCTIONITEM pFuncItem;
	for(unsigned int i = 1; i < FunctionTotalNum;i++)
	{		
		pFuncItem = pFuncArray[i];
		if(Rva >= pFuncItem->Rva && Rva <pFuncItem->Rva+pFuncItem->Size)
			return pFuncItem;
	}
	return NULL;
}
char* CSDSModule::GetFuncNameByRva(DWORD Rva)const
{
	DWORD FunctionTotalNum=m_SDSymbolFile->FunctionSymbolNum;
	PSDFUNCTIONITEM* pFuncArray=m_SDSymbolFile->UnionFunctionSymbolIndexTable.FunctionSymbolIndexTablePointer;
	PSDFUNCTIONITEM pFuncItem;
	for(unsigned int i = 1; i < FunctionTotalNum;i++)
	{		
		pFuncItem = pFuncArray[i];
		if(Rva >= pFuncItem->Rva && Rva <pFuncItem->Rva+pFuncItem->Size)
			return pFuncItem->uName.Name;
	}
	return m_StrTable[0];
}
PSDTYPE_INFILE* CSDSModule::GetSymbolList(DWORD* ItemCount)const
{
	if(ItemCount)
		*ItemCount = m_SDSymbolFile->SymbolTotalNum;
	return m_SDSymbolFile->UnionSymbolIndexTable.SymbolIndexTablePointer;
}
/*
void CSDSModule::CreateSourceLineMap()
{
	DWORD i;
	SOURCELINEMAP::IT FindIt;
	LINEINDEXLIST LineIndexList;
	LINEINDEXINFO LineIndexInfo;
	DWORD SourceFileID=0-1;
	DWORD dwLineTotalNum=m_SDSymbolFile->LineNumberCounter;
	PSDLINE pLine = m_SDSymbolFile->UnionLineNumber.pLineNumberTablePointer;
	SourceFileID=pLine[0].FileID;
	FindIt = m_SourceLineMap.InsertUnique(SourceFileID,LineIndexList);	
	LineIndexInfo.BeginIndex=0;
	for(i = 0; i < dwLineTotalNum;i++)
	{
		if(SourceFileID==pLine[i].FileID)
			continue;		
		LineIndexInfo.Number=i-LineIndexInfo.BeginIndex;			
		(*FindIt).Append(LineIndexInfo);
		SourceFileID=pLine[i].FileID;
		FindIt = m_SourceLineMap.InsertUnique(SourceFileID,LineIndexList);
		if(FindIt==m_SourceLineMap.End())						
			FindIt=m_SourceLineMap.Find(SourceFileID);					
		LineIndexInfo.BeginIndex=i;		
	}
	LineIndexInfo.Number=i-LineIndexInfo.BeginIndex;
	(*FindIt).Append(LineIndexInfo);
}
void CSDSModule::DeleteSourceLineMap()
{
	SOURCELINEMAP::IT BeginIT,EndIT;
	BeginIT=m_SourceLineMap.Begin();
	EndIT=m_SourceLineMap.End();
	for(;BeginIT!=EndIT;BeginIT++)
	{
		(*BeginIT).Clear();
	}
	m_SourceLineMap.Clear();
}
*/
void CSDSModule::CreateDataName2IDMap()
{
	DWORD dwDataCount;
	SYMNAMEIDKEY SymNameKey;
	PSDUDTDATAITEM pDataItem,pDataItemArray;
	dwDataCount=m_SDSymbolFile->DataInformationNum;
	pDataItemArray = m_SDSymbolFile->UnionDataInformation.DataInformationPointer;
	for(DWORD i = 1; i < dwDataCount;i++)
	{
		pDataItem = &pDataItemArray[i];	
		SymNameKey.m_Name=pDataItem->uName.Name;
		m_DataSymName2IDMap.InsertUnique(SymNameKey,i);				
	}
}
void CSDSModule::DeleteDataName2IDMap()
{
	m_DataSymName2IDMap.Clear();
}
void CSDSModule::CreateName2IDMap()
{
	DWORD dwSymbolTotalNum;
	DWORD i;
	PSDTYPE_INFILE* pTypeArray = m_SDSymbolFile->UnionSymbolIndexTable.SymbolIndexTablePointer;
	SYMNAMEIDKEY SymNameKey;
	dwSymbolTotalNum = m_SDSymbolFile->SymbolTotalNum;
	for(i = 1; i < dwSymbolTotalNum;i++)
	{
		SymNameKey.m_Name=pTypeArray[i]->uName.Name;
		m_Sym2Name2IDMap.InsertUnique(SymNameKey,i);		
	}	
	//m_DataSymName2IDMap
}
void CSDSModule::DeleteName2IDMap()
{
	m_Sym2Name2IDMap.Clear();
}
PSDTYPE_INFILE CSDSModule::GetSymbolByName(const char* Name,bool bCase)
{
	PSDTYPE_INFILE* pTypeArray = m_SDSymbolFile->UnionSymbolIndexTable.SymbolIndexTablePointer;
	SYMNAMEIDKEY SymNameKey;
	SYM2NAME2IDMAP::IT FindIT1;
	DWORD dwSymbolTotalNum;
	SymNameKey.m_Name=(char*)Name;
	if(Name==NULL&&Name[0]==0)
		return NULL;
	FindIT1 = m_Sym2Name2IDMap.Find(SymNameKey);
	dwSymbolTotalNum = m_SDSymbolFile->SymbolTotalNum;
	if(FindIT1!=m_Sym2Name2IDMap.End())
	{
		if(*FindIT1>=dwSymbolTotalNum)
			return NULL;
		return pTypeArray[*FindIT1];
	}
	return NULL;
}
PSDCOMPILAND CSDSModule::GetCompilandList(OUT DWORD* Count)const
{
	PSDCOMPILAND pSDCompiland;
	pSDCompiland =(PSDCOMPILAND)((char*)m_SDSymbolFile + m_SDSymbolFile->UniosCompiland.CompilandOffset);
	if(Count)
		*Count=m_SDSymbolFile->CompilandCounter;
	return pSDCompiland;
}
PSDPUBLICSYMBOL CSDSModule::GetPublicSymbolList(OUT DWORD* Count)
{
	if(Count)
		*Count = m_SDSymbolFile->PublicSymbolCounter;
	return m_SDSymbolFile->UnionPublicSymbol.PublicSymbolPointer;
}
PSDUDTDATAITEM CSDSModule::GetDataSymbolList(OUT DWORD* Count)
{
	if(Count)
		*Count=m_SDSymbolFile->DataInformationNum;
	return m_SDSymbolFile->UnionDataInformation.DataInformationPointer;
}
PCSTR CSDSModule::GetPEFileFullName()const
{	
	return m_SDSymbolFile->uPEFileFullName.PEFileFullName;
}
PCSTR CSDSModule::GetSymbolModuleName()const
{	
	return m_SDSymbolFile->uPEFileName.PEFileName;
}
PCSTR CSDSModule::GetPDBFileName()const
{
	return m_SDSymbolFile->uPDBFileName.PDBFileName;
}

PSDFUNCTIONITEM CSDSModule::GetFunctionSymbol(IN DWORD Index)const
{
	if(Index>=m_SDSymbolFile->FunctionSymbolNum)
		return NULL;
	return m_SDSymbolFile->UnionFunctionSymbolIndexTable.FunctionSymbolIndexTablePointer[Index];
}
PSDFUNCTIONITEM* CSDSModule::GetFunctionSymbolList(OUT DWORD* Count)
{
	if(Count)
		*Count=m_SDSymbolFile->FunctionSymbolNum;
	return m_SDSymbolFile->UnionFunctionSymbolIndexTable.FunctionSymbolIndexTablePointer;
}

PSDFUNCTIONITEM CSDSModule::GetFunctionSymbolByName(const char*Name,bool bCase)const
{
	PSDFUNCTIONITEM* pFunctArray;
	DWORD dwFunctionTotalNum,i;
	if(Name==NULL||Name[0]==0)
		return NULL;
	dwFunctionTotalNum=m_SDSymbolFile->FunctionSymbolNum;
	pFunctArray=m_SDSymbolFile->UnionFunctionSymbolIndexTable.FunctionSymbolIndexTablePointer;
	for(i=1;i < dwFunctionTotalNum;i++)
	{
		if(bCase)
		{
			if(TStrCmp(pFunctArray[i]->uName.Name,Name)==0)
				break;
		}
		else
		{
			if(TStrICmp(pFunctArray[i]->uName.Name,Name)==0)
				break;
		}
	}
	if(i>=dwFunctionTotalNum)
		return NULL;
	return pFunctArray[i];
}

DWORD CSDSModule::DumpSDUDTTypeToHeaderFile(SDTYPE_INFILE* SDTypeInfile,CStrA& OutBuffer)
{
	bool bArray=false;
	bool bFunctionPointer=false;
	bool bIsUnnamedUDT=false;
	DWORD PrevAccess;
	DWORD i,j;
	PSDTYPE_INFILE pSubType;
	PSDFUNCTIONITEM pFuncItem;
	PSDUDTDATAITEM pUdtData;
	char* OrgName;
	PSDUDTBASECLASS pUdtBaseClassType;
	PSDUDTTYPE pUdtType = (PSDUDTTYPE)&SDTypeInfile[1];
	char FuncName[0x400];
	int FuncNameLen = sizeof(FuncName)-1;
	//list<DWORD>::iterator FindOutputIT;
	OutBuffer.Empty();

	bIsUnnamedUDT=true;
	switch(SDTypeInfile->Type) 
	{
	case SD_STRUCT:
		OutBuffer+="struct ";
		PrevAccess=CV_public;
		break;
	case SD_CLASS:
		OutBuffer+="class ";
		PrevAccess=CV_private;
		break;
	case SD_UNION:
		OutBuffer+="union ";
		PrevAccess=CV_public;
		break;
	}
	if(bIsUnnamedUDT==false)
	{
		OutBuffer+=SDTypeInfile->uName.Name;
	}
	OutBuffer+=" ";
	if(pUdtType->BaseClassCounter)
	{
		OutBuffer+=": ";
		for(i = 0,j=0; i < pUdtType->BaseClassCounter;i++)
		{

			pSubType = GetTypeSymbol(pUdtType->pBaseClass.pBaseClassMember[i]);
			CODE_ASSERT(pSubType);
			pUdtBaseClassType = (PSDUDTBASECLASS)&pSubType[1];
			if(pUdtBaseClassType->bIsIndirectBaseClass)
				continue;
			if(j)
			{
				OutBuffer+=",";
			}
			if(pUdtBaseClassType->bIsVirtual)
			{
				OutBuffer+="virtual ";
			}
			switch(pUdtBaseClassType->Access)
			{
			case CV_private:
				OutBuffer+="private ";
				break;
			case CV_protected:
				OutBuffer+="protected ";
				break;
			case CV_public:
				OutBuffer+="public ";
				break;
			}
			
			OrgName = (char*)GetTypeNameByID(pUdtBaseClassType->TypeID);
			OutBuffer+=OrgName;
			j++;
		}
	}
	char udtsize[50];
	TSPrintf(udtsize,"/* sizeof %08x %d */",SDTypeInfile->TypeSize,SDTypeInfile->TypeSize);
	OutBuffer+=udtsize;
	OutBuffer+="\n{\n";
	if(pUdtType->FunctionCounter)
	{
		for(i = 0; i < pUdtType->FunctionCounter;i++)
		{
			pFuncItem = GetSDFunctionByID(pUdtType->pFunction.pFunctionMember[i]);
			CODE_ASSERT(pFuncItem);
			bool bStatic = false;
			PSDTYPE_INFILE pSubType = GetTypeSymbol(pFuncItem->TypeID);		
			if(PrevAccess!=pFuncItem->Access)
			{
				switch(pFuncItem->Access)
				{
				case CV_private:
					OutBuffer+="private:\n";
					break;
				case CV_protected:
					OutBuffer+="protected:\n";
					break;
				case CV_public:
					OutBuffer+="public:\n";
					break;
				}
				PrevAccess=pFuncItem->Access;
			}
			CStrA pStrFuncName;
			GetUDTFunctionMemberName(pUdtType->pFunction.pFunctionMember[i],pStrFuncName);
			OutBuffer+=pStrFuncName;
		}
	}
	if(pUdtType->DataCounter)
	{
		switch(SDTypeInfile->Type) 
		{
		case SD_STRUCT:
			if(PrevAccess!=CV_public)
			{
				OutBuffer+="public:\n";
			}
			PrevAccess=CV_public;
			break;
		case SD_CLASS:
			PrevAccess=0xffffffff;
			break;
		case SD_UNION:
			if(PrevAccess!=CV_public)
			{
				OutBuffer+="public:\n";
			}
			PrevAccess=CV_public;
			break;
		}
		CStrA DataName;
		for(i = 0; i < pUdtType->DataCounter; i++)
		{
			
			pUdtData = GetDataSymbol(pUdtType->pData.pDataMember[i]);// m_DataTagVector[pUdtType->pData.pDataMember[i]];
			bIsUnnamedUDT=false;
			if(PrevAccess!=pUdtData->Access)
			{
				switch(pUdtData->Access)
				{
				case CV_private:
					OutBuffer+="private:\n";
					break;
				case CV_protected:
					OutBuffer+="protected:\n";
					break;
				case CV_public:
					OutBuffer+="public:\n";
					break;
				}
				PrevAccess=pUdtData->Access;
			}

			{
				GetUDTDataMemberName(pUdtType->pData.pDataMember[i],DataName);
				OutBuffer+=DataName;
			}

		}

	}
	OutBuffer+="};\n";
	return 0;
}
PSDFUNCTIONITEM CSDSModule::GetSDFunctionByID(IN DWORD Index)const
{
	if(Index>=m_SDSymbolFile->FunctionSymbolNum)
		return NULL;
	return m_SDSymbolFile->UnionFunctionSymbolIndexTable.FunctionSymbolIndexTablePointer[Index];
}
char* CSDSModule::GetUDTFunctionMemberName(DWORD FuncID,OUT CStrA& NameBuffer)
{
	char FuncName[0x400];
	PSDFUNCTIONITEM pFuncItem;
	int FuncNameLen;
	pFuncItem = GetSDFunctionByID(FuncID);
	CODE_ASSERT(pFuncItem);
	bool bStatic = false;
	PSDFUNCTIONTYPE pFunctionType;
	PSDTYPE_INFILE pSubType = GetTypeSymbol(pFuncItem->TypeID);		
	NameBuffer.Empty();
	FuncNameLen = sizeof(FuncName)-1;
	GetFunctionName(pFuncItem,FuncName,&FuncNameLen);
	if(pSubType->Type==SD_FUNCTIONTYPE)
	{
		pFunctionType = (PSDFUNCTIONTYPE)&pSubType[1];
		if(pFunctionType->CallingConvention==CV_CALL_NEAR_STD)
			bStatic=true;
	}
	if(bStatic)
	{
		NameBuffer+="\t\tstatic ";
		NameBuffer+=FuncName;
	}
	else
	{
		NameBuffer+="\t\t";
		NameBuffer+=FuncName;
	}
	NameBuffer+=";";
	if(pFuncItem->IsVirtual)
	{
		char OffsetBuf[50];
		TSPrintf(OffsetBuf,"/* VTable offset %08x */",pFuncItem->VirtualBaseOffset);
		NameBuffer+=OffsetBuf;
	}
	NameBuffer+="\n";
	return NULL;
}
char* CSDSModule::GetUDTDataMemberName(IN DWORD DataID,OUT CStrA& NameBuffer)
{
#define MAX_LENGTH_NAME (0X400)
	char ArrayTypeName[20];
	CStrA DataName;
	bool bArray=false;
	char NullChar=0;
	char TypeName[20];
	char* CallConvention;
	char* OrgDataName;
	char *FuncName;
	int FuncNameLen;
	PSDUDTDATAITEM pUdtData;
	PSDTYPE_INFILE pSubType;
	bool bFunctionPointer;
	bool bUnnamedUDT=false;
	NameBuffer.Empty();
	FuncNameLen = MAX_LENGTH_NAME-1;
	FuncName=new char[MAX_LENGTH_NAME];
	pUdtData = GetDataSymbol(DataID);
	OrgDataName = pUdtData->uName.Name;
	GetSDSymbolName(pUdtData->TypeId,FuncName,&FuncNameLen);
	DataName.Empty();
	DataName=FuncName;
	if(pUdtData->Location == LocIsThisRel)
	{
		NameBuffer.Format("/* off 0x%04x */\t",pUdtData->u.LOCISTHISREL.Offset);
	}
	if(pUdtData->Location == LocIsStatic)
		NameBuffer+="static ";
	bFunctionPointer=false;
	CallConvention=NULL;
	pSubType = GetTypeSymbol(pUdtData->TypeId);
	TypeName[0]=0;
	ArrayTypeName[0]=0;
	bArray=false;
	if(pSubType)
	{
		switch(pSubType->Type) 
		{
		case SD_POINTER:
			{
				PSDPOINTERTYPE pSDPointer=(PSDPOINTERTYPE)&pSubType[1];
				PSDFUNCTIONTYPE pFunctionProc;
				pSubType = GetTypeSymbol(pSDPointer->TypeID);
				if(pSubType->Type==SD_FUNCTIONTYPE)
				{
					bFunctionPointer=true;
					pFunctionProc = (PSDFUNCTIONTYPE)&pSubType[1];
					CallConvention = GetCallConventionName(pFunctionProc->CallingConvention);
				}
			}
			break;
		case SD_ARRAY:
			{	
				PSDARRAYTYPE pSDArrayType = (PSDARRAYTYPE)&pSubType[1];
				bUnnamedUDT = IsUnnamedUDT(pSDArrayType->TypeIDElement);
				pSubType= GetTypeSymbol(pSDArrayType->TypeIDElement);
				bArray=true;
				break;
			}
		case SD_CLASS:
		case SD_STRUCT:
		case SD_UNION:
			bUnnamedUDT = IsUnnamedUDT(pSubType->Id);
			break;
		}
	}
	if(bUnnamedUDT)
	{
		CStrA OutBuffer;
		OutBuffer.Empty();
		int i;
		DumpSDUDTTypeToHeaderFile(pSubType,DataName);
		char* pString = DataName;
		char* pBegin = DataName;
		OutBuffer+="\n";
		for( i = 0;pString[i];i++)
			if(pString[i]=='\n')
			{
				OutBuffer+="\t";
				pString[i]=0;
				if(pString[i+1])
				{
					OutBuffer+=pBegin;
					OutBuffer+="\n";
				}
				else
				{
					pString[i-1]=0;
					OutBuffer+=pBegin;
				}
				pBegin=&pString[i+1];
			}
			DataName=OutBuffer;
			if(bArray)
			{
				DataName+=TStrChr(FuncName,'[');
			}
			if(DataName.Length()>MAX_LENGTH_NAME)
			{
				delete []FuncName;
				FuncName = new char[DataName.Length()+1];

			}
			TStrCpy(FuncName,(char*)DataName);
	}
	if(bFunctionPointer)
	{
		char * pFunc =GetFuncParamBegin(FuncName);
		if(pFunc)
		{
			pFunc--;
			*pFunc=0;
			pFunc++;
			NameBuffer+=FuncName;
			NameBuffer+=pUdtData->uName.Name;
			NameBuffer+=")";
			NameBuffer+=pFunc;
		}
	}else if(bArray){
		char* pIndexBegin = TStrChr(FuncName,'[');
		if(pIndexBegin)
		{
			*pIndexBegin=0;
			pIndexBegin++;
			NameBuffer+=FuncName;
			NameBuffer+=" ";
			NameBuffer+=pUdtData->uName.Name;
			NameBuffer+="[";
			NameBuffer+=pIndexBegin;
		}
	}else
	{
		NameBuffer+=FuncName;
		NameBuffer+="\t";
		NameBuffer+=pUdtData->uName.Name;

		if(pUdtData->Location == LocIsBitField)
		{
			NameBuffer+=":";
			char buf[20];
			TSPrintf(buf,"%d",pUdtData->u.LOCISBITFIELD.Size);
			NameBuffer+=buf;
		}
	}
	NameBuffer+=";\n";
	delete []FuncName;
	return NULL;
}
SDCALLCONVENTIONPAIR CSDSModule::m_CallConvention[24]=
{
	{0xffffffff," "},
	{CV_CALL_NEAR_C," __cdecl "}, 
	{CV_CALL_NEAR_FAST," __fastcall "}, 
	{CV_CALL_NEAR_STD," __stdcall "},    
	{CV_CALL_NEAR_SYS," __syscall "},    
	{CV_CALL_THISCALL," __thiscall "},    
	{CV_CALL_MIPSCALL," Unknown calling convention in function "},    
	{CV_CALL_GENERIC," Unknown calling convention in function "},    
	{CV_CALL_ALPHACALL," Unknown calling convention in function "},   
	{CV_CALL_PPCCALL," Unknown calling convention in function "},     
	{CV_CALL_SHCALL," Unknown calling convention in function "},      
	{CV_CALL_ARMCALL," Unknown calling convention in function "},     
	{CV_CALL_AM33CALL," Unknown calling convention in function "},    
	{CV_CALL_TRICALL," Unknown calling convention in function "},     
	{CV_CALL_SH5CALL," Unknown calling convention in function "},     
	{CV_CALL_M32RCALL," Unknown calling convention in function "},    
	{CV_CALL_RESERVED," Unknown calling convention in function "},
	{CV_CALL_FAR_C," Unknown calling convention in function "},       
	{CV_CALL_NEAR_PASCAL," Unknown calling convention in function "},
	{CV_CALL_FAR_PASCAL," Unknown calling convention in function "},
	{CV_CALL_FAR_FAST," Unknown calling convention in function "},  
	{CV_CALL_SKIPPED," Unknown calling convention in function "},
	{CV_CALL_FAR_STD," Unknown calling convention in function "}, 
	{CV_CALL_FAR_SYS," Unknown calling convention in function "},     
};
char* CSDSModule::GetCallConventionName(DWORD dwType)
{
	return m_CallConvention[0].Name;
	int i;
	if(dwType>=sizeof(m_CallConvention)/sizeof(m_CallConvention[0]))
		return m_CallConvention[0].Name;
	for(i = 0; i < sizeof(m_CallConvention)/sizeof(m_CallConvention[0]);i++)
		if(m_CallConvention[i].Type==dwType)
			return m_CallConvention[i].Name;
	return m_CallConvention[0].Name;
}

bool CSDSModule::IsFunctionPointer(DWORD dwTypeID)
{
	PSDTYPE_INFILE pType = GetTypeSymbol(dwTypeID);
	if(pType==NULL)
		return false;
	if(pType->Type!=SD_POINTER)
		return false;
	return IsFunctionPointer(pType);
}
bool CSDSModule::IsFunctionPointer(PSDTYPE pType)
{
	return IsFunctionPointer(&pType->SDTypeInfile);
}
bool CSDSModule::IsFunctionPointer(PSDTYPE_INFILE SDTypeInfile)
{
	PSDTYPE_INFILE pSubType;
	if(SDTypeInfile->Type!=SD_POINTER)
		return false;
	PSDPOINTERTYPE pPointerType = (PSDPOINTERTYPE)&SDTypeInfile[1];
	pSubType = GetTypeSymbol(pPointerType->TypeID);
	if(pSubType==NULL)
		return false;
	return pSubType->Type==SD_FUNCTIONTYPE;
}
char* CSDSModule::GetFuncParamBegin(char* FunctionPointerName)
{
	int i;
	char* Name;
	int Sum = 0;
	int Len = TStrLen(FunctionPointerName);
	Name = TStrRChr(FunctionPointerName,')');
	Len =Len - TStrLen(Name);
	for(i = Len;i>=0;i--)
	{
		if(FunctionPointerName[i]==')')
			Sum++;
		else
			if(FunctionPointerName[i]=='(')
				Sum--;
		if(Sum==0)
			break;
	}
	return &FunctionPointerName[i];
}
char* CSDSModule::GetFunctionName(IN PSDFUNCTIONITEM pFuncItem,OUT char* NameBuffer,INOUT int* BufferLength)
{			
	int dwCurrentLen=0;
	PSDTYPE_INFILE pSubType=NULL;
	char pVirtual[]="virtual ";
	int len;
	char pFuncEnd[5]=")";
	char* CallConventionName;

	NameBuffer[0]=0;
	if(pFuncItem->IsVirtual)
	{
		dwCurrentLen = TStrLen(pVirtual);
		if(*BufferLength >dwCurrentLen)
			TStrCpy(NameBuffer,pVirtual);
		(*BufferLength) = (*BufferLength) - dwCurrentLen;
	}
	if(pFuncItem->TypeIDReturnValue)
		GetSDSymbolName(pFuncItem->TypeIDReturnValue,&NameBuffer[dwCurrentLen],BufferLength);
	if(pFuncItem->TypeID)
	{
		pSubType=GetTypeSymbol(pFuncItem->TypeID);
		if(pSubType->Type==SD_FUNCTIONTYPE)
		{
			SDFUNCTIONTYPE* pFunctionType = (SDFUNCTIONTYPE*)&pSubType[1];
			CallConventionName = GetCallConventionName(pFunctionType->CallingConvention);
			dwCurrentLen = TStrLen(CallConventionName);
			if(*BufferLength>dwCurrentLen)
				TStrCat(NameBuffer,CallConventionName);
			*BufferLength=*BufferLength-dwCurrentLen;
		}
	}


	dwCurrentLen = TStrLen(pFuncItem->uName.Name);
	if(*BufferLength > dwCurrentLen)
		TStrCat(NameBuffer,pFuncItem->uName.Name);
	(*BufferLength) = (*BufferLength) - dwCurrentLen;
	if(*BufferLength > 1)
		TStrCat(NameBuffer,"(");
	(*BufferLength)--;

	for(DWORD i = 0; i < pFuncItem->DataCounter; i++)
	{
		SDUDTDATAITEM* pUdtDataItem= GetDataSymbol(pFuncItem->pData.pDataMember[i]);
		if(pUdtDataItem->KindData==DataIsParam)
		{
			len = TStrLen(NameBuffer);
			GetSDSymbolName(pUdtDataItem->TypeId,&NameBuffer[len],BufferLength);
			if(*BufferLength>1)
				TStrCat(NameBuffer," ");
			(*BufferLength)--;
			dwCurrentLen = TStrLen(pUdtDataItem->uName.Name);
			if(*BufferLength>dwCurrentLen)
				TStrCat(NameBuffer,pUdtDataItem->uName.Name);
			(*BufferLength)=(*BufferLength)-dwCurrentLen;
			if(*BufferLength>1)
				TStrCat(NameBuffer,",");
			(*BufferLength)--;
		}
	}
	len = TStrLen(NameBuffer);
	if(NameBuffer[len-1]==',')
		NameBuffer[len-1]=0;
	if(pFuncItem->IsPure)
		TStrCpy(pFuncEnd,")=0");
	dwCurrentLen = TStrLen(pFuncEnd);
	if(*BufferLength>dwCurrentLen)
		TStrCat(NameBuffer,pFuncEnd);
	(*BufferLength)=(*BufferLength)-dwCurrentLen;
	return NameBuffer;
}
bool CSDSModule::IsUnnamedUDT(DWORD dwTypeID)
{
	PSDTYPE_INFILE pType = GetTypeSymbol(dwTypeID);
	if(pType==NULL)
		return false;
	if(pType->Type==SD_CLASS || pType->Type==SD_STRUCT || pType->Type==SD_UNION)
		if(((PSDCLASSTYPE)&pType[1])->IsUnnamed)
			return true;
	return false;
}

char* CSDSModule::GetSDSymbolName(IN DWORD TypeID,OUT char *NameBuffer,INOUT int *BufferLength)
{
	return GetSDSymbolName(GetTypeSymbol(TypeID),NameBuffer,BufferLength);
}
char* CSDSModule::GetSDSymbolName(IN PSDTYPE_INFILE SDTypeInfile,OUT char *NameBuffer,INOUT int *BufferLength)
{
	SDTYPE_INFILE *SelfType;
	char TypeName[50];
	int dwOrgBufferLen=*BufferLength;
	int dwCurrentLen;
	int len=0;	
	char* CallConventionName;
	if(NameBuffer)
		NameBuffer[0]=0;
	if(SDTypeInfile==NULL)
		return NameBuffer;	
	switch(SDTypeInfile->Type) 
	{
	case SD_FUNCTIONTYPE:
		{	
			SDFUNCTIONTYPE* pFunctionType= (SDFUNCTIONTYPE*)&SDTypeInfile[1];
			GetSDSymbolName(pFunctionType->TypeIDReturnValue,NameBuffer,BufferLength);
			CallConventionName = GetCallConventionName(pFunctionType->CallingConvention);
			dwCurrentLen = TStrLen(CallConventionName);
			if(*BufferLength>dwCurrentLen)
				TStrCat(NameBuffer,CallConventionName);
			*BufferLength-=dwCurrentLen;
			if(*BufferLength>1)
				TStrCat(NameBuffer,"(");
			(*BufferLength)--;
			len = TStrLen(NameBuffer);
			for(DWORD  i = 0; i< pFunctionType->ArgsCount;i++)
			{
				len = TStrLen(NameBuffer);
				GetSDSymbolName(pFunctionType->TypeIDArgs[i],&NameBuffer[len],BufferLength);
				len = TStrLen(NameBuffer);
				if(i!=pFunctionType->ArgsCount-1)
				{
					if(*BufferLength>1)
					{
						TStrCat(&NameBuffer[len],",");
						len++;
					}
					(*BufferLength)--;
				}
			}
			if(*BufferLength>1)
			{
				TStrCat(&NameBuffer[len],")");
			}
			(*BufferLength)--;
		}
		return NameBuffer;		
	case SD_POINTER:
		{		
			SDPOINTERTYPE* pPointerType;
			int MaxBufferLen=*BufferLength;
			CStrA TmpBuf;

			pPointerType = (SDPOINTERTYPE*)&SDTypeInfile[1];
			SelfType = GetTypeSymbol(pPointerType->TypeID);
			GetSDSymbolName(pPointerType->TypeID,NameBuffer,BufferLength);
			dwCurrentLen = pPointerType->PointerDepth;
			TmpBuf.Fill('*',dwCurrentLen);
			if(SelfType->Type==SD_FUNCTIONTYPE)
				dwCurrentLen+=2;
			if(*BufferLength<=dwCurrentLen)
			{
				*BufferLength-=dwCurrentLen;
				return NameBuffer;
			}

			if(SelfType->Type==SD_FUNCTIONTYPE)
			{					
				PSDFUNCTIONTYPE pFunctionType = (PSDFUNCTIONTYPE)&SelfType[1];
				char *NewName;
				char* pCallConvention;
				DWORD len;
				char NullChar=0;
				char * pFunc;
				NewName = new char[MaxBufferLen];
				TStrCpy(NewName,NameBuffer);
				CallConventionName = GetCallConventionName(pFunctionType->CallingConvention);
				pCallConvention = TStrStr(NameBuffer,CallConventionName);
				pFunc =GetFuncParamBegin(NewName);
				if(pCallConvention==NULL)
				{
					pCallConvention = &NullChar;
					len = (*(DWORD*)&pFunc-*(DWORD*)&NewName);
				}else
					len = (*(DWORD*)&pCallConvention-*(DWORD*)&NameBuffer);
				NameBuffer[len]='(';
				len++;
				len+=TStrCpy(&NameBuffer[len],CallConventionName);
				TStrCpy(&NameBuffer[len],(char*)TmpBuf);
				TStrCat(NameBuffer,")");
				TStrCat(NameBuffer,pFunc);
				delete NewName;
			}
			else
			{
				TStrCat(NameBuffer,(char*)TmpBuf);
			}

			*BufferLength-=dwCurrentLen;
			return NameBuffer;
		}	
		break;
	case SD_REFERENCE:
		{		
			SDREFERENCETYPE*pReferenceType;
			pReferenceType = (SDREFERENCETYPE*)&SDTypeInfile[1];
			SelfType = GetTypeSymbol(pReferenceType->TypeID);
			GetSDSymbolName(SelfType,NameBuffer,BufferLength);
			if(*BufferLength>1)
				TStrCat(NameBuffer,"&");
			*BufferLength--;
		}	
		break;
	case SD_ARRAY:
		{
			SDARRAYTYPE* pArrayType;
			bool bFunctionPointer=false;
			char DigBuf[30];

			CStrA StrBufA;
			pArrayType = (SDARRAYTYPE*)&SDTypeInfile[1];
			SelfType = GetTypeSymbol(pArrayType->TypeIDElement);
			if(SelfType==NULL)
				return NameBuffer;
			GetSDSymbolName(SelfType,NameBuffer,BufferLength);
			bFunctionPointer=IsFunctionPointer(SelfType);
			dwCurrentLen=0;
			for(DWORD  i = 0; i < pArrayType->DimensionsSize; i++)
			{
				dwCurrentLen += TSPrintf(DigBuf,"%d",pArrayType->Dimensions[i].Size);
				dwCurrentLen+=2;
				StrBufA+="[";
				StrBufA+=DigBuf;
				StrBufA+="]";
			}
			if(*BufferLength>dwCurrentLen)
			{
				if(bFunctionPointer)
				{
					CStrA pFuncParam;
					char* pFunc = GetFuncParamBegin(NameBuffer);
					pFuncParam = pFunc;
					pFunc--;
					pFunc[0]=0;
					TStrCat(NameBuffer,(char*)StrBufA);
					TStrCat(NameBuffer,")");
					TStrCat(NameBuffer,(char*)pFuncParam);
				}
				else
					TStrCat(NameBuffer,(char*)StrBufA);
			}

			*BufferLength = *BufferLength-dwCurrentLen;
			return NameBuffer;
		}
		break;
	case SD_BASECLASS:
		{
			SDUDTBASECLASS* pUdtBaseClassType= (SDUDTBASECLASS*)&SDTypeInfile[1];
			return 	GetSDSymbolName(pUdtBaseClassType->TypeID,NameBuffer,BufferLength);
		}
	case SD_ENUMERATION:
		TStrCpy(TypeName,"enum ");
		len = TStrLen(TypeName);
		if(*BufferLength>len)
			TStrCpy(NameBuffer,TypeName);
		*BufferLength-=len;
		goto local_002;
	case SD_CLASS:
		/*
		TStrCpy(TypeName,"");
		len = TStrLen(TypeName);
		if(*BufferLength>len)
			TStrCpy(NameBuffer,TypeName);
		*BufferLength-=len;
		*/
		goto local_002;
	case SD_STRUCT:
		TStrCpy(TypeName,"struct ");
		len = TStrLen(TypeName);
		if(*BufferLength>len)
			TStrCpy(NameBuffer,TypeName);
		*BufferLength-=len;
		goto local_002;
	case SD_UNION:
		TStrCpy(TypeName,"union ");
		len = TStrLen(TypeName);
		if(*BufferLength>len)
			TStrCpy(NameBuffer,TypeName);
		*BufferLength-=len;
	default:
local_002:
		{
			if(SDTypeInfile->uName.Name)
			{
				dwCurrentLen = TStrLen(SDTypeInfile->uName.Name);
				if(dwCurrentLen<*BufferLength)
					TStrCpy(&NameBuffer[len],SDTypeInfile->uName.Name);
				*BufferLength-=dwCurrentLen;
			}
			else
			{
				dwCurrentLen = TStrLen("no name");
				if(dwCurrentLen<*BufferLength)
					TStrCpy(&NameBuffer[len],"no name");
				*BufferLength-=dwCurrentLen;
			}
		}
	}
	return NameBuffer;
}
DWORD CSDSModule::DumpSDTypedefTypeToHeaderFile(SDTYPE_INFILE* SDTypeInfile,CStrA& OutBuffer)
{
	bool bFunctionPointer=false;
	char OrgName[0x400];
	int OrgNameLen=sizeof(OrgName)-1;
	char TypeName[20]="\0";
	PSDTYPEDEFTYPE pSDTypeDef=(PSDTYPEDEFTYPE)&SDTypeInfile[1];
	PSDTYPE_INFILE pSubType = GetTypeSymbol(pSDTypeDef->TypeID);
	PSDPOINTERTYPE pSDPointer;
	OutBuffer.Empty();
	switch(pSubType->Type)
	{
	case SD_POINTER:
		pSDPointer = (PSDPOINTERTYPE)&pSubType[1];
		pSubType = GetTypeSymbol(pSDPointer->TypeID);
		if(pSubType->Type == SD_FUNCTIONTYPE)
			bFunctionPointer=true;
		break;
	}
	GetSDSymbolName(pSDTypeDef->TypeID,OrgName,&OrgNameLen);
	if(bFunctionPointer)
	{
		char * pFunc =GetFuncParamBegin(OrgName);
		if(pFunc)
		{
			pFunc--;
			*pFunc=0;
			pFunc++;
			OutBuffer+="typedef ";
			OutBuffer+=OrgName;
			OutBuffer+=SDTypeInfile->uName.Name;
			OutBuffer+=")";
			OutBuffer+=pFunc;
		}
		else
		{
			OutBuffer+="typedef ";
			OutBuffer+=TypeName;
			OutBuffer+=" ";
			OutBuffer+=SDTypeInfile->uName.Name;
		}
	}
	else
	{
		OutBuffer+="typedef ";
		OutBuffer+=TypeName;
		OutBuffer+=OrgName;
		OutBuffer+=" ";
		OutBuffer+=SDTypeInfile->uName.Name;
	}

	return 0;
}

DWORD CSDSModule::DumpSDEnumTypeToHeaderFile(SDTYPE_INFILE* SDTypeInfile ,CStrA &OutBuffer)
{
	char WriteBuffer[50];
	SDENUMERATIONTYPE* pEnumationType;
	DWORD WriteByteSize=0;
	OutBuffer.Empty();
	OutBuffer+="enum ";
	OutBuffer+=SDTypeInfile->uName.Name;
	OutBuffer+="{";
	pEnumationType = (SDENUMERATIONTYPE*)&SDTypeInfile[1];
	for(unsigned int i = 0; i < pEnumationType->DataCount; i++)	
	{
		OutBuffer+="\t";
		OutBuffer+=pEnumationType->EnumerationDataMember[i].u.Name;
		OutBuffer+="\t=";
		TSPrintf(WriteBuffer,"0x%08x\t,//%d",pEnumationType->EnumerationDataMember[i].Value,pEnumationType->EnumerationDataMember[i].Value);
		OutBuffer+=WriteBuffer;
	}
	OutBuffer+="};";
	return WriteByteSize;
}
PSDFUNCTIONITEM CSDSModule::GetUdtClassFuncMemberByName(const char* Name,PSDTYPE_INFILE pType,bool bFullName)const
{
	DWORD i;
	DWORD UdtNameLen=0;
	PSDUDTTYPE pUdtType;
	PSDFUNCTIONITEM pFuncItem;
	DWORD * pFuncIdArray;
	if(pType==NULL&&(pType->Type!=SD_STRUCT&&pType->Type!=SD_UNION&&pType->Type!=SD_CLASS))
		return NULL;
	pUdtType = (PSDUDTTYPE)&pType[1];
	pFuncIdArray = pUdtType->pFunction.pFunctionMember;
	if(bFullName==false)
		UdtNameLen = TStrLen(pType->uName.Name)+2;
	for(i = 0; i < pUdtType->FunctionCounter;i++)
	{
		pFuncItem=GetFunctionSymbol(pFuncIdArray[i]);
		if(TStrCmp(&pFuncItem->uName.Name[UdtNameLen],Name)==0)
			return pFuncItem;
	}
	pFuncIdArray = pUdtType->pBaseClass.pBaseClassMember;
	for(i = 0; i < pUdtType->BaseClassCounter;i++)
	{
		pType=GetTypeSymbol(pFuncIdArray[i]);
		PSDUDTBASECLASS pBaseClass=(PSDUDTBASECLASS)&pType[1];
		pFuncItem = GetUdtClassFuncMemberByName(Name,GetTypeSymbol(pBaseClass->TypeID),bFullName);
		if(pFuncItem)
			return pFuncItem;
	}
	return NULL;
}
PSDUDTDATAITEM CSDSModule::GetUdtClassDataMemberByName(const char *Name,PSDTYPE_INFILE pType,DWORD* ThisOffset)const
{
	DWORD i;
	CSDSModule pSDSModule;
	PSDUDTDATAITEM pDataItem;
	PSDUDTTYPE pUdtType;
	PSDUDTBASECLASS pBaseClass;	
	if(pType==NULL||(pType->Type!=SD_STRUCT&&pType->Type!=SD_UNION&&pType->Type!=SD_CLASS))
		return NULL;
	pUdtType = (PSDUDTTYPE)&pType[1];
	DWORD * pDataIdArray = pUdtType->pData.pDataMember;
	
	for(i = 0; i < pUdtType->DataCounter; i++)
	{
		pDataItem = GetDataSymbol(pDataIdArray[i]);
		if(TStrCmp(pDataItem->uName.Name,Name)==0)
		{
			if(ThisOffset)
			{
				if(pDataItem->Location==LocIsThisRel)
					*ThisOffset+=pDataItem->u.LOCISTHISREL.Offset;
				else
					*ThisOffset=pDataItem->u.LOCISSTATIC.Rva;
			}
			return pDataItem;
		}
	}
	DWORD * pBaseClassIdArray= pUdtType->pBaseClass.pBaseClassMember;
	for(i = 0; i < pUdtType->BaseClassCounter; i++)
	{
		pType = GetTypeSymbol(pBaseClassIdArray[i]);
		pBaseClass = (PSDUDTBASECLASS)&pType[1];
		pType = GetTypeSymbol(pBaseClass->TypeID);
		pDataItem = GetUdtClassDataMemberByName(Name,pType,ThisOffset);
		if(pDataItem)
		{
			if(ThisOffset)
			{
				if(pDataItem->Location==LocIsStatic)
					*ThisOffset=pDataItem->u.LOCISSTATIC.Rva;
				if(pDataItem->Location==LocIsThisRel)
					*ThisOffset+=pBaseClass->Offset;
			}
			return pDataItem;
		}
	}
	return NULL;
}
PSDUDTDATAITEM CSDSModule::GetDataSymbolByString(char* pStr,DWORD FileId,DWORD LineNum,bool* IsFunc,DWORD* RetOffset)const
{
	return GetDataSymbolByString (pStr,GetFunctionByLineNumber(FileId,LineNum),IsFunc,RetOffset);
}
PSDUDTDATAITEM CSDSModule::GetDataSymbolByString(char* pStr,PSDFUNCTIONITEM pCurrentFunc,bool* IsFunc,DWORD* RetOffset)const
{
	DWORD Len,i;
	char* pBegin;
	PSDTYPE_INFILE pType=NULL;
	PSDFUNCTIONITEM pFuncItem;
	bool First=true;
	PSDUDTDATAITEM pDataItem;
	PSDPOINTERTYPE pPointerType;
	PSDREFERENCETYPE pReference;
	if(RetOffset)
		*RetOffset=0;
	if(IsFunc)
		*IsFunc=false;
	if(pCurrentFunc==NULL)
		return NULL;
	Len = TStrLen(pStr);
	for(i = 0; i < Len; i++)
	{
		if(pStr[i]=='.')
		{
			pStr[i]=0;
			i++;
			break;
		}
		else if(pStr[i]=='-')
		{
			pStr[i]=0;
			i+=2;
			break;
		}
	}
	pDataItem = GetDataSymbolInFunctionByName(pStr,pCurrentFunc);
	if(pDataItem==NULL)
	{
		if(pCurrentFunc->TypeIDParentUDT)
		{
			pDataItem = GetUdtClassDataMemberByName(pStr,GetTypeSymbol(pCurrentFunc->TypeIDParentUDT));
		}
		if(pDataItem==NULL)
		{
			pDataItem = GetDataSymbolByNameAndKind(pStr,DataIsGlobal);
			if(pDataItem==NULL)
				return NULL;
			if(RetOffset)
			{
				if(pDataItem->Location==LocIsStatic)
					*RetOffset=pDataItem->u.LOCISSTATIC.Rva;
			}
		}
	}
	
	if(pDataItem->TypeId==0)
	{
		if(i!=Len)
			return NULL;
		pFuncItem = GetFunctionSymbolByName(pStr);
		if(pFuncItem)
			if(IsFunc)
				*IsFunc=true;
		return (PSDUDTDATAITEM)pFuncItem;
	}
	if(i==Len)
		return pDataItem;
	pType = GetTypeSymbol(pDataItem->TypeId);
	if(pType->Type==SD_POINTER)
	{
		pPointerType =(PSDPOINTERTYPE) &pType[1];
		pType =GetTypeSymbol(pPointerType->TypeID);
	}
	if(pType->Type==SD_REFERENCE)
	{
		pReference =(PSDREFERENCETYPE) &pType[1];
		pType =GetTypeSymbol(pReference->TypeID);
	}
	if(pType==NULL|| (pType->Type!=SD_UNION&&pType->Type!=SD_CLASS&&pType->Type!=SD_STRUCT))
		return NULL;
	pBegin = &pStr[i];
	pDataItem=NULL;
	for(;i<Len;i++)
	{
		if(pStr[i]=='.')
		{
			pStr[i]=0;
			pDataItem = GetUdtClassDataMemberByName(pBegin,pType,RetOffset);
			if(pDataItem==NULL)
			{
				pFuncItem = GetUdtClassFuncMemberByName(pBegin,pType);
				if(pFuncItem)
					if(IsFunc)
						*IsFunc=true;
				return (PSDUDTDATAITEM)pFuncItem;
			}
			i++;
			if(i==Len)
				return pDataItem;
			pType = GetTypeSymbol(pDataItem->TypeId);
			pBegin=&pStr[i];
			if(pType->Type==SD_REFERENCE)
			{
				pReference =(PSDREFERENCETYPE) &pType[1];
				pType =GetTypeSymbol(pReference->TypeID);
			}
			if(pType==NULL|| (pType->Type!=SD_UNION&&pType->Type!=SD_CLASS&&pType->Type!=SD_STRUCT))
				return NULL;
		}
		else if(pStr[i]=='-')
		{
			pStr[i]=0;
			pDataItem = GetUdtClassDataMemberByName(pBegin,pType,RetOffset);
			if(pDataItem==NULL)
			{
				pFuncItem = GetUdtClassFuncMemberByName(pBegin,pType);
				if(pFuncItem)
				if(IsFunc)
					*IsFunc=true;
				return (PSDUDTDATAITEM)pFuncItem;
			}
			i+=2;
			if(i==Len)
				return pDataItem;
			pType = GetTypeSymbol(pDataItem->TypeId);
			pBegin=&pStr[i];
			if(pType->Type==SD_POINTER)
			{
				pPointerType =(PSDPOINTERTYPE) &pType[1];
				pType =GetTypeSymbol(pPointerType->TypeID);
			}
			if(pType==NULL|| (pType->Type!=SD_UNION&&pType->Type!=SD_CLASS&&pType->Type!=SD_STRUCT))
				return NULL;
		}
	}
	pDataItem=GetUdtClassDataMemberByName(pBegin,pType,RetOffset);
	if(pDataItem==NULL)
	{
		pFuncItem = GetUdtClassFuncMemberByName(pBegin,pType);
		if(pFuncItem)
			if(IsFunc)
				*IsFunc=true;
		return (PSDUDTDATAITEM)pFuncItem;
	}
	return pDataItem;
}
char* CSDSModule::GetEnumerationByValue(DWORD TypeIndex,ULONGLONG ullValue)const
{
	DWORD i;
	PSDTYPE_INFILE pType;
	PSDENUMERATIONTYPE pEnumType;
	pType = GetTypeSymbol(TypeIndex);
	if(pType==NULL)
		return NULL;
	pEnumType = (PSDENUMERATIONTYPE)&pType[1];
	for(i = 0; i < pEnumType->DataCount;i++)
	{
		if(pEnumType->EnumerationDataMember[i].Value==ullValue)
			return pEnumType->EnumerationDataMember[i].u.Name;
	}
	return NULL;
}
PSDUDTDATAITEM CSDSModule::GetDataSymbolInFunctionByName(const char* Name,PSDFUNCTIONITEM pFuncItem)const
{
	PSDUDTDATAITEM pDataItem;
	PSDTYPE_INFILE pType;
	PSDBLOCK pBlock;
	DWORD* pIdArray;
	DWORD Count,i,j;
	if(pFuncItem==NULL||Name==NULL||Name[0]==0)
		return NULL;
	Count = pFuncItem->DataCounter;
	pIdArray=pFuncItem->pData.pDataMember;
	for(i = 0; i < Count; i++)
	{
		pDataItem=GetDataSymbol(pIdArray[i]);
		if(TStrCmp(pDataItem->uName.Name,Name)==0)
			return pDataItem;
	}
	Count = pFuncItem->BlockCounter;
	for(i = 0; i < Count; i++)
	{
		pType = GetTypeSymbol(pFuncItem->pBlock.pBlockTypeIdArray[i]);
		pBlock = (PSDBLOCK)&pType[1];
		for(j = 0; j < pBlock->DataCounter;j++)
		{
			pDataItem = GetDataSymbol(pBlock->pDataMember[j]);
			if(TStrCmp(pDataItem->uName.Name,Name)==0)
				return pDataItem;
		}
	}
	if(pFuncItem->TypeIDParentUDT==0)
		return NULL;
	pType=GetTypeSymbol(pFuncItem->TypeIDParentUDT);
	DWORD ThisOffset;
	pDataItem = GetUdtClassDataMemberByName(Name,pType,&ThisOffset);
	return pDataItem;
}
bool CSDSModule::CheckSDSymbolFileCheckSum()
{
	PSDSYMBOLFILE	pSDSymbolFile;
	DWORD OldCheckSum=0;
	ULONGLONG CheckSum=0;
	DWORD* pBuffer=(DWORD*)m_FileBuffer;
	DWORD i,FileLen = *(DWORD*)&m_SymFileSize;
	pSDSymbolFile = (PSDSYMBOLFILE)m_FileBuffer;
	OldCheckSum = pSDSymbolFile->CheckSum;
	pSDSymbolFile->CheckSum = 0;
	for(i = 0; i < FileLen/sizeof(DWORD);i++)
	{
		CheckSum+=pBuffer[i];
	}
	pSDSymbolFile->CheckSum=OldCheckSum;
	if(*(DWORD*)&CheckSum==OldCheckSum)
		return true;
	return false;
}
DWORD CSDSModule::GetTimeDateStamp()const
{
	PSDSYMBOLFILE	pSDSymbolFile;
	pSDSymbolFile = (PSDSYMBOLFILE)m_FileBuffer;
	return pSDSymbolFile->ModuleID.TimeDateStamp;
}
DWORD CSDSModule::GetPECheckSum()const
{
	PSDSYMBOLFILE	pSDSymbolFile;
	pSDSymbolFile = (PSDSYMBOLFILE)m_FileBuffer;
	return pSDSymbolFile->ModuleID.OrgPECheckSum;
}