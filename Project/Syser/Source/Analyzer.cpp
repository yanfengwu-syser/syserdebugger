#include "StdAfx.h"
#include "Analyzer.h"


void CFuncCodeMaker::MakeFirst(STFuncCode*pFuncCode)
{
	InstrCount = 0;
	dbCheckSum = 0;
	dwVal = dwCheckSum = 0;
	ddVal = ddCheckSum = 0;
}

void CFuncCodeMaker::MakeNext(BYTE*CodeBuffer,STFuncCode*pFuncCode)
{
	//取字节累加和
	dbCheckSum+=*CodeBuffer;
	if(InstrCount%2)
	{//1,3
		dwVal+=*CodeBuffer<<8;
		dwCheckSum+=dwVal;
		if(InstrCount%3)
		{//1
			ddVal += *CodeBuffer<<8;
		}
		else
		{//3
			ddVal += *CodeBuffer<<24;
			ddCheckSum += ddVal;
		}
	}
	else
	{//0,2
		dwVal=*CodeBuffer;
		if(InstrCount%4)
		{//2
			ddVal += *CodeBuffer<<16;
		}
		else
		{//0
			ddVal = *CodeBuffer;
		}
	}
	InstrCount++;
}

void CFuncCodeMaker::MakeEnd(STFuncCode*pFuncCode,int Size)
{
	pFuncCode->FuncSize = (WORD)Size;
	pFuncCode->InstrCount = InstrCount;
	pFuncCode->dbCheckSum = dbCheckSum;
	pFuncCode->dwCheckSum = dwCheckSum;
	pFuncCode->ddCheckSum = ddCheckSum;		
}

void CFuncCodeMaker::Make(BYTE*CodeBuffer,int Size,STFuncCode*pFuncCode)
{
	CFuncCodeMaker Maker;
	int Off;
	Off = 0;
	Maker.MakeFirst(pFuncCode);
	while(Off<Size)
	{
		Maker.MakeNext(&CodeBuffer[Off],pFuncCode);
		Off+=MAX(CInstrSym::InstrLen(&CodeBuffer[Off],Size-Off),1);
	}
	Maker.MakeEnd(pFuncCode,Size);
}


CAnalyzer::CAnalyzer()
{
	m_pImageFile = &m_PEFile;
	m_Style = 0;
}

CAnalyzer::~CAnalyzer()
{
}

int	CAnalyzer::ReadMemory(ULPOS Address,void*Buffer,int Size)
{
	return m_ImageCache.ReadMemory(Address,Buffer,Size,&m_ImageCache);
}

bool CAnalyzer::IsInvalidAddress(ULPOS Address)
{
	return m_PEFile.IsInvalidAddress(Address);
}

bool CAnalyzer::Open(DWORD ModuleBase,DWORD ModuleSize,RWProc RMFunction,void*RMParam)
{
	if(m_Style&AS_NO_SYM)
		m_PEFile.m_OpenMode|=PE_OPEN_NO_IMPORT|PE_OPEN_NO_EXPORT;
	if(RMFunction)
		m_PEFile.SetRMProc(RMFunction,RMParam);
	else
		m_PEFile.SetRMProc(CImageFile::StaticReadRealMemory,RMParam);
	m_PEFile.m_ImageBase = ModuleBase;
	if(ModuleSize)
		m_PEFile.m_ImageSize=ModuleSize;
	m_PEFile.m_FileObjType = FILE_OBJ_TYPE_OS_MEMORY_IMAGE;
	if(m_PEFile.Open(NULL)==false)
		return false;
	m_ImageCache.Init(m_PEFile.m_ImageSize/MP_SIZE,PMS_DYN_PAGE);
	m_ImageCache.MapImage(&m_PEFile);
	return true;
}

bool CAnalyzer::Open(PCSTR FileName)
{
	if(m_Style&AS_NO_SYM)
		m_PEFile.m_OpenMode|=PE_OPEN_NO_IMPORT|PE_OPEN_NO_EXPORT;
	if(m_PEFile.Open(FileName)==false)
		return false;
	m_ImageCache.Init(MIN(m_PEFile.m_ImageSize,0x100000)/MP_SIZE,PMS_DYN_PAGE);
	m_ImageCache.MapImage(&m_PEFile);
	return true;
}

void CAnalyzer::Close()
{
	m_ImageCache.UnmapImage(&m_PEFile);
	m_ImageCache.Release();
	m_FuncMap.Clear();
	m_PEFile.Close();
	m_CodeBuffer.Resize(MP_SIZE);
	m_RecogCodeList.Clear();
}

bool CAnalyzer::LoadFDC(PCSTR FileName)
{
	CImageFileStream FileStream;
	if(FileStream.Open(FileName)==false)
		return false;
	m_FuncDescrMap.Load(FileStream);
	FileStream.Close();
	return true;
}

bool CAnalyzer::AnalyzerFromExportFunction(int Deep,int MaxFuncCount)
{
	int i;
	TFuncMap::IT Iter;
	int nMaxFuncCount;
	m_AnalyzerDeep = Deep;
	if(m_PEFile.m_ExportFuncCount==0)
		return AnalyzerFromEntryPoint(Deep,MaxFuncCount);
	for(i=0;i<m_PEFile.m_ExportFuncCount;i++)
	{
		if(m_PEFile.m_ExportFunc[i].Address==0x102012d0)
			Deep=100;
		Iter = m_FuncMap.InsertUnique(m_PEFile.m_ExportFunc[i].Address);
		if(Iter==m_FuncMap.End())
			continue;
		Iter->m_bLibFunc = false;
		Iter->m_CmtEnd = Iter->m_End = Iter->m_Start = m_PEFile.m_ExportFunc[i].Address;
		nMaxFuncCount=MaxFuncCount;
		AnalyzerFunction(&(*Iter),0,nMaxFuncCount);
	}	
	return true;
}

bool CAnalyzer::AnalyzerFromEntryPoint(int Deep,int MaxFuncCount)
{
	TFuncMap::IT Iter;
	Iter = m_FuncMap.InsertUnique(m_PEFile.m_EntryPoint);
	if(Iter==m_FuncMap.End())
		return true;
	Iter->m_bLibFunc = false;
	Iter->m_CmtEnd = Iter->m_End = Iter->m_Start = m_PEFile.m_EntryPoint;
	m_AnalyzerDeep = Deep;
	AnalyzerFunction(&(*Iter),0,MaxFuncCount);
	return true;
}

bool CAnalyzer::Analyzer(ULPOS Address,int Deep,int MaxFuncCount)
{
	TFuncMap::IT Iter;
	Iter = m_FuncMap.InsertUnique(Address);
	Iter->m_bLibFunc = false;
	Iter->m_CmtEnd = Iter->m_End = Iter->m_Start = Address;
	m_AnalyzerDeep = Deep;
	AnalyzerFunction(&(*Iter),0,MaxFuncCount);
	return true;
}


bool CAnalyzer::AnalyzerFunction(CFunction*pFun,int Deep,int&CountLeft)
{
	bool	bRetExist;
	WCHAR	wszBuffer[256];
	ULPOS	Address,MaxJmpAddr,DesAddr;
	DWORD	Length,CodeLen;
	BYTE	Buffer[64],OpCode;
	Address = pFun->m_Start;
	STFuncCode	FuncCode;
	CFuncCodeMaker	CodeMake;
	if(CountLeft<=0 || Deep>=m_AnalyzerDeep)
		return false;
	CodeMake.MakeFirst(&FuncCode);
	MaxJmpAddr = 0;
	bRetExist = false;
	while(Address < m_pImageFile->m_ImageHighBase)
	{
		Length = m_pImageFile->ReadMemory(Address,Buffer,MAX_INSTR_LEN);
		if(Length==0)
			break;
		OpCode = *Buffer;
		CodeLen=CInstrSym::InstrLen(Buffer,Length);
		MIN_LIMIT(CodeLen,1);
		if(bRetExist==false && (OpCode==0xC3 || OpCode==0xC2))
			bRetExist = true;
		if(Address == pFun->m_Start && OpCode==0xE9)
		{
			pFun->m_CmtEnd = Address;
			pFun->m_End = Address+CodeLen;
			ULPOS FuncAddr = Address+GET_DWORD(Buffer,1)+CodeLen;
			TFuncMap::IT FuncIt = m_FuncMap.InsertUnique(FuncAddr);
			if(FuncIt==m_FuncMap.End())
			{
				FuncIt = m_FuncMap.Find(FuncAddr);
				if(FuncIt==m_FuncMap.End())
					return false;
			}
			else
			{
				FuncIt->m_bLibFunc = false;
				FuncIt->m_CmtEnd = FuncIt->m_End = FuncIt->m_Start = FuncAddr;
				if(AnalyzerFunction(&(*FuncIt),Deep+1,CountLeft)==false)
					return false;
			}
			pFun->m_ChildFunc.InsertUnique(Address - pFun->m_Start,&(*FuncIt));
			break;
		}
		CodeMake.MakeNext(Buffer,&FuncCode);
		MAX_LIMIT(CodeLen,Length);
		if(Deep<m_AnalyzerDeep)
		{//分析子函数
			if(CodeLen == 5 && OpCode==0xE8)
			{
				ULPOS FuncAddr = Address+GET_DWORD(Buffer,1)+CodeLen;
				TFuncMap::IT FuncIt = m_FuncMap.InsertUnique(FuncAddr);
				if(FuncIt==m_FuncMap.End())
				{
					FuncIt = m_FuncMap.Find(FuncAddr);
					if(FuncIt==m_FuncMap.End())
						return false;
				}
				else
				{
					FuncIt->m_bLibFunc = false;
					FuncIt->m_CmtEnd = FuncIt->m_End = FuncIt->m_Start = FuncAddr;
					if(AnalyzerFunction(&(*FuncIt),Deep+1,CountLeft)==false)
						return false;
				}
				pFun->m_ChildFunc.InsertUnique(Address - pFun->m_Start,&(*FuncIt));
			}
		}
		if(OpCode==0xEB || (OpCode>=0x70 && OpCode<=0x7f))
		{
			DesAddr = Address+(char)Buffer[1]+2;
			if(DesAddr>MaxJmpAddr)
				MaxJmpAddr = DesAddr;
		}
		else if(OpCode==0x0F && (Buffer[1]>=0x80 && Buffer[1]<=0x8F))
		{
			DesAddr = Address+(int)GET_DWORD(Buffer,2)+6;
			if(DesAddr>MaxJmpAddr)
				MaxJmpAddr = DesAddr;
		}

		if(Address>=MaxJmpAddr)
		{		
			if(	OpCode==0xCC || OpCode==0xC3 || OpCode==0xC2 || 
				((OpCode==0xE9 && (int)GET_DWORD(Buffer,1) < 0) || (OpCode==0xEB && (char)GET_BYTE(Buffer,1) < 0) && bRetExist) ||
				(OpCode==0xFF && GET_BYTE(Buffer,1)==0x25 ) )
			{
				pFun->m_CmtEnd = Address;
				pFun->m_End = Address+CodeLen;
				break;
			}
		}
		Address+=CodeLen;
	}
	CodeMake.MakeEnd(&FuncCode,pFun->m_End-pFun->m_Start);
	CFuncDescrMap::IT DescrIter = m_FuncDescrMap.Find(FuncCode);
	if(DescrIter!=m_FuncDescrMap.End())
	{
		TStrCpy(wszBuffer,(char*)DescrIter->Name);
		pFun->m_Name = wszBuffer;
		pFun->m_bLibFunc = true;
	}
	//else if(pFun->m_Name.IsEmpty())
	//	pFun->m_Name.Format(WSTR("Func%08X"),pFun->m_Start);
	CountLeft--;
	return true;
}

int CAnalyzer::GetFuncSize(BYTE*CodeBuff,int Size)
{
	bool	bRetExist;
	ULPOS	Address,MaxJmpAddr,DesAddr;
	int		CodeLen;
	BYTE	OpCode,*Buffer;
	Address = 0;
	MaxJmpAddr = 0;
	bRetExist = false;
	while(Address < (ULPOS)Size)
	{
		Buffer = &CodeBuff[Address];
		OpCode =*Buffer;
		CodeLen = CInstrSym::InstrLen(Buffer,Size-Address);
		MIN_LIMIT(CodeLen,1);
		if(bRetExist==false && (OpCode==0xC3 || OpCode==0xC2))
			bRetExist = true;
		if(Address==0 && OpCode==0xE9)
			return 	Address+CodeLen;
		if(OpCode==0xEB || (OpCode>=0x70 && OpCode<=0x7f))
		{
			DesAddr = Address+(char)Buffer[1]+2;
			if(DesAddr>MaxJmpAddr)
				MaxJmpAddr = DesAddr;
		}
		else if(OpCode==0x0F && (Buffer[1]>=0x80 && Buffer[1]<=0x8F))
		{
			DesAddr = Address+(int)GET_DWORD(Buffer,2)+6;
			if(DesAddr>MaxJmpAddr)
				MaxJmpAddr = DesAddr;
		}
		if(Address>=MaxJmpAddr)
		{
			if(	OpCode==0xCC || OpCode==0xC3 || OpCode==0xC2 || 
				(OpCode==0xE9 && (int)GET_DWORD(Buffer,1) < 0) ||
				(OpCode==0xEB && (char)GET_BYTE(Buffer,1) < 0) && bRetExist)
			{
				return 	Address+CodeLen;
			}
		}
		Address+=CodeLen;
	}
	return Size;
}

void CAnalyzer::MakeFuncDescr(ULPOS Start,ULSIZE Size,STFuncCode*pFuncCode)
{
	if(m_CodeBuffer.Size()< (int)Size+MAX_INSTR_LEN)
		m_CodeBuffer.Resize(Size+MAX_INSTR_LEN);
	Size = ReadMemory(Start,(BYTE*)m_CodeBuffer,Size);
	m_FuncCodeMaker.Make(m_CodeBuffer,Size,pFuncCode);
}

PCWSTR CAnalyzer::AnalyzerScan(CLogicStateCAD*pStateCAD)
{
	STStatePathEntry*pResultEntry;
	m_RecogCodeList.Clear();
	m_RecogPathMethodList.Clear();
	m_RecogPathAddrList.Clear();
	m_ReportInfo.Name.Empty();
	pResultEntry = AnalyzerScanPath(m_PEFile.m_EntryPoint,&pStateCAD->m_StateRoot);
	if(pResultEntry)
		return pResultEntry->ReportInfo.Name;
	return NULL;
}

STStatePathEntry*CAnalyzer::PathFunc(ULPOS BaseAddr,STStatePathEntry*pParentEntry)
{
	bool	bRetExist;
	TStatePathEntrySet::IT PathEntryIter;
	STStatePathEntry Entry;
	ULPOS	Address,MaxJmpAddr,DesAddr;
	ULSIZE	Length,CodeLen,FuncSize;
	BYTE	Buffer[64],OpCode;
	int		SafeCount;
	CFuncCodeMaker	CodeMake;
	CodeMake.MakeFirst(&Entry.RecogCode.FuncCode);
	Address = BaseAddr;
	SafeCount = 0;
	FuncSize = 0;
	MaxJmpAddr = 0;
	bRetExist = false;
	while(Address < m_pImageFile->m_ImageHighBase && SafeCount<0x1000)
	{
		Length=ReadMemory(Address,Buffer,MAX_INSTR_LEN);
		if(Length==0)
			break;
		OpCode = *Buffer;
		CodeLen=CInstrSym::InstrLen(Buffer,Length);
		MIN_LIMIT(CodeLen,1);
		CodeMake.MakeNext(Buffer,&Entry.RecogCode.FuncCode);
		if(bRetExist==false && (OpCode==0xC3 || OpCode==0xC2))
			bRetExist = true;
		if(Address==BaseAddr && OpCode==0xE9)
		{
			FuncSize+=CodeLen;
			break;
		}
		if(OpCode==0xEB || (OpCode>=0x70 && OpCode<=0x7f))
		{
			DesAddr = Address+(char)Buffer[1]+2;
			if(DesAddr>MaxJmpAddr)
				MaxJmpAddr = DesAddr;
		}
		else if(OpCode==0x0F && (Buffer[1]>=0x80 && Buffer[1]<=0x8F))
		{
			DesAddr = Address+(int)GET_DWORD(Buffer,2)+6;
			if(DesAddr>MaxJmpAddr)
				MaxJmpAddr = DesAddr;
		}
		if(Address>=MaxJmpAddr)
		{
			if(	OpCode==0xCC || OpCode==0xC3 || OpCode==0xC2 || 
				(OpCode==0xE9 && (int)GET_DWORD(Buffer,1) < 0) ||
				(OpCode==0xEB && (char)GET_BYTE(Buffer,1) < 0) && bRetExist)
			{
				FuncSize+=CodeLen;
				break;
			}
		}
		Address+=CodeLen;
		FuncSize+=CodeLen;
		SafeCount++;
	}
	Entry.RecogCode.CodeType = STRecogCode::FUNCTION;
	CodeMake.MakeEnd(&Entry.RecogCode.FuncCode,FuncSize);
	PathEntryIter = pParentEntry->NextEntry.Find(Entry);
	if(PathEntryIter==pParentEntry->NextEntry.End())
		return NULL;
	return &(*PathEntryIter);
}

STStatePathEntry* CAnalyzer::PathInitTermTable(ULPOS BaseAddr,ULSIZE Count,ULSIZE Length,STStatePathEntry*pParentEntry)
{
	ULPOS Address;
	STStatePathEntry*pEntry;
	for(ULSIZE n=0;n<Count;n++)
	{
		Address = 0;
		if(ReadMemory(BaseAddr+n*Length,&Address,Length)==0)
			return NULL;
		pEntry = AnalyzerScanPath(Address,pParentEntry);
		if(pEntry)
			return pEntry;
	}
	return NULL;
}

STStatePathEntry* CAnalyzer::AnalyzerScanPath(ULPOS BaseAddr,STStatePathEntry*pParentEntry)
{
	ULSIZE Length,Count;
	ULPOS Address,Offset,Address1;
	STPathMethod*pMethod;
	STStatePathEntry*pEntry,Entry;
	pEntry = NULL;
	switch(pParentEntry->RecogCode.CodeType)
	{
	case STRecogCode::FUNCTION:
		pEntry = PathFunc(BaseAddr,pParentEntry);
		break;
	case STRecogCode::IGNORE_ENTRY:
		if(pParentEntry->NextEntry.Count())
			pEntry = &(*pParentEntry->NextEntry.Begin());
		break;
	}
	if(pEntry == NULL)
		return NULL;
	m_RecogCodeList.Append(pEntry->RecogCode);
	m_RecogPathAddrList.Append(BaseAddr);
	if(pEntry->ReportInfo.Name.GetLength())
	{
		if(pEntry->ReportInfo.Type == STReportInfo::RI_TYPE_REPORT)
		{
			m_ReportInfo = pEntry->ReportInfo;
			return pEntry;
		}
		else
		{
			m_ReportInfo = pEntry->ReportInfo;
		}
	}
	pMethod = &pParentEntry->PathMethod;
	m_RecogPathMethodList.Append(*pMethod);
	switch(pMethod->Method)
	{
	case STPathMethod::OFFSET:
		Address = pMethod->Offset;
		break;
	case STPathMethod::ADDR_PTR:
		Address = 0;
		Length = ReadMemory(BaseAddr+pMethod->Offset,&Address,MIN(pMethod->Length,sizeof(Address)));
		if(Length==0)
			return NULL;
		break;
	case STPathMethod::OFFSET_PTR:
		Offset = 0;
		Length = ReadMemory(BaseAddr+pMethod->Offset,&Offset,MIN(pMethod->Length,sizeof(Offset)));
		if(Length==0)
			return NULL;
		Address = BaseAddr + pMethod->Offset + Offset + pMethod->Delta;
		break;
	case STPathMethod::CPP_INIT_TERM_TABLE:
		Address = 0;
		Length = ReadMemory(BaseAddr+pMethod->Offset,&Address,MIN(pMethod->Length,sizeof(Offset)));
		if(Length==0)
			return NULL;
		Address1 = 0;
		Length = ReadMemory(BaseAddr+pMethod->Offset+pMethod->Delta,&Address1,MIN(pMethod->Length,sizeof(Offset)));
		if(Length==0)
			return NULL;
		if(Address<Address1)
			Address1=Address;
		Count = (Address1 - Address)/pMethod->Length;
		pEntry=PathInitTermTable(Address,Count,pMethod->Length,pParentEntry);
		if(pEntry==NULL)
			return NULL;
		break;
	default:
		return NULL;
		break;
	}
	if(IsInvalidAddress(Address))
		return NULL;
	return AnalyzerScanPath(Address,pEntry);
}

