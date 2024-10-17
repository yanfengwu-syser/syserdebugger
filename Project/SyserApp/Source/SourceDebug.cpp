#include "StdAfx.h"
#include "SourceDebug.h"
#define NTOSKRNLVER ""
CSourceDebug::CSourceDebug()
{
	m_CurrentSourceFileIndex=0;
	m_CurrentCompilandIndex=0;
	m_CurrentDataSymbolIndex=0x1;
	m_CurrentFunctionSymbolIndex=0x1;
	m_CurrentSymbolIndex=0x1;
	m_DataTagVector.push_back(NULL);
	
	m_DiaDllGetClassObject=NULL;
	m_DiaDllModule=NULL;
	m_PEFileName=NULL;
	m_PDBFileName=NULL;
	m_StringNameID=0;
	m_StringName=false;
	m_GlobalEnumSegments=NULL;
	m_GlobalEnumFrameData=NULL;
	m_GlobalScopeSymbol=NULL;
	m_DiaSession=NULL;
	m_DiaDataSource=NULL;
	m_pfnSetRange = NULL;
	m_pfnSetPos = NULL;
}
bool CSourceDebug::Init()
{
	
	if(m_DiaDllModule==NULL)
	{
		m_DiaDllModule = 	LoadLibrary("msdia80.dll");
		if(!m_DiaDllModule)
		{
			m_DiaDllModule = 	LoadLibrary("c:\\Prg\\Syser\\Addition\\DiaSDK\\bin\\msdia80.dll");
		}
		if(!m_DiaDllModule)
		return false;
	}
	if(m_DiaDllGetClassObject==NULL)
	{
		m_DiaDllGetClassObject = (PDLLGETCLASSOBJECT)GetProcAddress(m_DiaDllModule,"DllGetClassObject");
	}
	
	return true;
}
bool CSourceDebug::Release()
{
	if(m_DiaDllModule)
		FreeLibrary(m_DiaDllModule);
	m_DiaDllModule=NULL;
	return true;
}
CSourceDebug::~CSourceDebug()
{
}

bool CSourceDebug::PackedSourceFile(PCSTR pSymbolFileName,PACKEDSOURCEFILEFAILEDCALLBACK pCallBack)
{
	DWORD i;
	int CallBackRet;
	bool bSkipAll=false;
	DWORD SourceFileCount=0;
	HANDLE hFile;
	PSDSYMBOLFILE FileHeader;
	PSDSOURCEFILEID pSourceFile;
	ULLSIZE FileLen;
	ULLSIZE FileCurPos;
	char* StringTable;
	CLocalFileIO SourceFileIO;
	char* SourceName;
	char NewFileName[1024];
	char *FileReadWriteBuf=NULL;
	DWORD* StringTableIndex;
	if(gpFileIO->OpenFile(pSymbolFileName,&hFile,FIO_READ|FIO_WRITE)==false)
		return false;
	FileLen = gpFileIO->GetFileLength(hFile);
	FileHeader=(PSDSYMBOLFILE)new char[*(size_t*)&FileLen];
	gpFileIO->ReadFile(hFile,FileHeader,*(ULSIZE*)&FileLen,0);
	if(FileHeader->UnionSourceFile.SourceFileOffset)
	{
		delete []FileHeader;
		gpFileIO->CloseHandle(hFile);
		return false;
	}

	StringTableIndex = (DWORD*)((char*)FileHeader + FileHeader->UnionStringIndexTable.StringIndexTableOffset);
	StringTable = (char*)FileHeader+FileHeader->UnionStringTable.StringTableOffset;
	gpFileIO->SetFilePointer(hFile,FileHeader->UnionSourceFileIDTable.SourceFileIDTableOffset,FILE_BEGIN);
	pSourceFile = (PSDSOURCEFILEID)((char*)FileHeader+FileHeader->UnionSourceFileIDTable.SourceFileIDTableOffset);
	for(i = 0; i < FileHeader->SourceFileCounter;i++)
	{
		SourceName =StringTable +  StringTableIndex[pSourceFile[i].uName.MemberNameInStringTableIndex];
Local_001:
		if(gpFileIO->IsFileExist(SourceName)==false)
		{
			pSourceFile[i].OffsetAtFile=0;
			pSourceFile[i].FileLen=0;
			if(pCallBack&&bSkipAll==false)
			{
				CallBackRet = pCallBack(SourceName,NewFileName);
				switch(CallBackRet)
				{
				case 0:
					SourceName=NewFileName;
					goto Local_001;
				case 2:
					bSkipAll=true;
				case 1:
					break;
				}
			}
		}
		else
		{	
			SourceFileCount++;
			FileLen = gpFileIO->GetFileSize(SourceName);
			FileReadWriteBuf=new char[*(size_t*)&FileLen];
			FileCurPos = gpFileIO->SetFilePointer(hFile,0,FILE_END);
			pSourceFile[i].OffsetAtFile=*(DWORD*)&FileCurPos;
			pSourceFile[i].FileLen=*(DWORD*)&FileLen;
			gpFileIO->ReadFromFile(SourceName,FileReadWriteBuf,*(ULSIZE*)&FileLen);
			gpFileIO->WriteFile(hFile,FileReadWriteBuf,*(ULSIZE*)&FileLen);
			delete []FileReadWriteBuf;
		}
	}
	gpFileIO->WriteFile(hFile,pSourceFile,sizeof(SDSOURCEFILEID)*FileHeader->SourceFileCounter,FileHeader->UnionSourceFileIDTable.SourceFileIDTableOffset);
	FileLen = gpFileIO->SetFilePointer(hFile,0,FILE_END);
	DWORD Tmp = *(DWORD*)&FileLen & 0xFFF;
	if(Tmp)
	{
		Tmp = 0x1000-Tmp;
		char *BufChar=new char[Tmp];
		if(BufChar)
		{
			memset(BufChar,0,Tmp);
			gpFileIO->WriteFile(hFile,BufChar,Tmp);
			FileLen = gpFileIO->SetFilePointer(hFile,0,FILE_END);
			delete []BufChar;
		}
		else
		{
			FileHeader->CheckSum=0;
		}
	}
	FileHeader->UnionSourceFile.SourceFileOffset = FileHeader->FileLen;
	FileHeader->FileLen=*(DWORD*)&FileLen;
	FileHeader->PackageSourceFileCounter=SourceFileCount;
	gpFileIO->WriteFile(hFile,FileHeader,SDSF_FILE_HEADER_SIZE,0);
	delete []FileHeader;
	gpFileIO->CloseHandle(hFile);
	WriteSDSymbolFileCheckSum(pSymbolFileName);
	return true;
}

bool CSourceDebug::GetPEFileTimeDateStamp(IN PCSTR szPEFileName,OUT DWORD *TimeDateStamp,OUT DWORD* PECheckSum)
{
	CPEFile PEFile;
	if(TimeDateStamp)
		*TimeDateStamp=0;
	if(PECheckSum)
		*PECheckSum=0;
	PEFile.m_OpenMode |= PE_OPEN_NO_IMPORT|PE_OPEN_NO_EXPORT;
	if(PEFile.Open(szPEFileName)==false)
		return false;
	if(TimeDateStamp)
		*TimeDateStamp=PEFile.m_PEHead.TimeDateStamp;	
	if(PECheckSum)
		*PECheckSum=PEFile.m_PEHead.CheckSum;
	PEFile.Close();
	return true;
}

bool CSourceDebug::IsSymbolFile(PCSTR pFileName)
{
	ULLSIZE FileLen;
	SDSYMBOLFILE SDSymbolFile;
	if(gpFileIO->IsFileExist(pFileName)==false)
		return false;
	if(gpFileIO->ReadFromFile(pFileName,&SDSymbolFile,sizeof(SDSymbolFile))!=sizeof(SDSymbolFile))
		return false;
	if(SDSymbolFile.Sig!=SYSER_DEBUG_SYMBOL_FILE_SIG)
		return false;
	FileLen =gpFileIO->GetFileSize(pFileName);
	if(FileLen!=SDSymbolFile.FileLen)
		return false;
	return true;
}

bool CSourceDebug::GetPDBFileName(char* pSymbolFileName,char* pPDBFileName,DWORD* BufferLen)
{
	if(IsSymbolFile(pSymbolFileName)==false)
		return false;
	return true;
}

bool CSourceDebug::GetPEFileFullName(PCSTR FileName,char* pPEFileFullName,DWORD* BufferLen)
{
	char* Name=NULL;
	char buf[SDSF_FILE_HEADER_SIZE];
	HANDLE hFile;
	PSDSYMBOLFILE pSDSymbolFile=(PSDSYMBOLFILE)buf;
	if(IsSymbolFile(FileName)==false)
		return false;
	if(gpFileIO->OpenFile(FileName,&hFile)==false)
	{
		return false;
	}
	if(gpFileIO->ReadFile(hFile,pSDSymbolFile,sizeof(buf),0)!=sizeof(buf))
	{
		gpFileIO->CloseHandle(hFile);
		return false;
	}
	if(pSDSymbolFile->uPEFileFullName.PEFileFullNameOffset+pSDSymbolFile->PEFileFullNameLen <= sizeof(buf))
	{
		gpFileIO->CloseHandle(hFile);
		Name=(char*)pSDSymbolFile; 
		if(BufferLen)
		{
			if(*BufferLen < pSDSymbolFile->PEFileFullNameLen)
			{
				*BufferLen=pSDSymbolFile->PEFileFullNameLen;
				return false;
			}
		}
		TStrCpy(pPEFileFullName,&Name[pSDSymbolFile->uPEFileFullName.PEFileFullNameOffset]);
		return true;
	}
	else
	{
		if(BufferLen)
		{
			if(*BufferLen < pSDSymbolFile->PEFileFullNameLen)
			{
				gpFileIO->CloseHandle(hFile);
				*BufferLen=pSDSymbolFile->PEFileFullNameLen;
				return false;
			}
		}
		Name = new char[pSDSymbolFile->PEFileFullNameLen];
		if(gpFileIO->ReadFile(hFile,Name,pSDSymbolFile->PEFileFullNameLen,pSDSymbolFile->uPEFileFullName.PEFileFullNameOffset)!=pSDSymbolFile->PEFileFullNameLen)
		{
			delete []Name;
			gpFileIO->CloseHandle(hFile);
			return false;
		}
		TStrCpy(pPEFileFullName,Name);
		delete []Name;
		gpFileIO->CloseHandle(hFile);
		return true;
	}
	return true;
}

bool CSourceDebug::IsTranslated(IN PCSTR szModuleName,PSTR szSymbolFileName)
{
	ULLSIZE FileLen;
	SDSYMBOLFILE SDSymbolFile;
	DWORD TimeDateStamp,PECheckSum;
	char SDSPath[MAX_FN_LEN];
	TStrCpy(SDSPath,szModuleName);
	TStrCat(SDSPath,".sds");
	if(szSymbolFileName)
		TStrCpy(szSymbolFileName,SDSPath);
	if(gpFileIO->IsFileExist(SDSPath)==false)
		return false;
	GetPEFileTimeDateStamp(szModuleName,&TimeDateStamp,&PECheckSum);
	if(gpFileIO->ReadFromFile(SDSPath,&SDSymbolFile,sizeof(SDSYMBOLFILE))!=sizeof(SDSYMBOLFILE))
		return false;
	FileLen = gpFileIO->GetFileSize(SDSPath);
	if(SDSymbolFile.FileLen==FileLen&&SDSymbolFile.ModuleID.TimeDateStamp==TimeDateStamp && SDSymbolFile.Version==SYSER_DEBUG_SYMBOL_FILE_VER&&PECheckSum==SDSymbolFile.ModuleID.OrgPECheckSum)		
		return true;
	return false;
}

bool CSourceDebug::TranslateSymbolFile(IN PCSTR szModuleName,OUT char *szSymbolFileName,bool bPackedSrcFile)
{
	bool bRet,IsPDBFile;
	CHAR szDestSymbolName[MAX_FN_LEN];
	DWORD TimeDateStamp=0,PECheckSum=0;
	if(gpFileIO->IsFileExist(szModuleName)==false)
		return false;
	TStrCpy(szDestSymbolName,szModuleName);
	TStrCat(szDestSymbolName,".sds");
	if(szSymbolFileName)
		TStrCpy(szSymbolFileName,szDestSymbolName);
	if(OpenPdbFile(szModuleName, &m_DiaDataSource, &m_DiaSession, &m_GlobalScopeSymbol,&IsPDBFile)==false)
		return false;
	IsPDBFile = false;
	if(ListGlobalSymbols(IsPDBFile))
	{
		if(IsPDBFile)
			szModuleName=NULL;
		else
			LoadPESym(szModuleName);
		DumpHeaderFile("c:\\ntddkvista.h");	
		GetPEFileTimeDateStamp(szModuleName,&TimeDateStamp,&PECheckSum);
		bRet = CreateSDSymbolFile(szDestSymbolName,TimeDateStamp,PECheckSum,szModuleName);
	}
	ReleaseSDType();
	ClosePdbFile();
	if(bRet && bPackedSrcFile)
	{
		PackedSourceFile(szDestSymbolName,NULL);
	}
	return bRet;
}

bool CSourceDebug::TestFunction()
{
	SYMBOL_ID_MAP::iterator BeginIT1,EndIT1;
	SDTYPE* pType;
	bool bFind=false;
	CTempSymbol* pTempSymbol;
	BeginIT1 = m_UDTSymbolID.begin();
	for(;BeginIT1!=m_UDTSymbolID.end();BeginIT1++)
	{
		pTempSymbol = (CTempSymbol*)&(*BeginIT1).first;
		pType =pTempSymbol->GetSDType() ;
		char *vtablename;
		PUBLIC_SYMBOL_MAP::iterator BeginIt2,EndIt2;
		BeginIt2=m_VTablePublicSymbolList.begin();
		EndIt2=m_VTablePublicSymbolList.end();
		bFind =false;
		for(;BeginIt2!=EndIt2;BeginIt2++)
		{
			vtablename=(*BeginIt2).first.uName.Name;
			char*vtablename1 = TStrStr(vtablename,pType->SDTypeInfile.uName.Name);
			if(vtablename1)
			{
				if(TStrNCmp(&vtablename1[TStrLen(pType->SDTypeInfile.uName.Name)],"::`vftable'",TStrLen("::`vftable'"))==0)
				{
					//m_VTablePublicSymbolList.erase(BeginIt2);
					bFind=true;
					break;
				}
			}	
		}
		if(bFind==true)
		{
			OutputDebugString(pType->SDTypeInfile.uName.Name);
			OutputDebugString("\n");
		}
	}
//	char *Name11;
	PUBLIC_SYMBOL_MAP::iterator BeginIt3,EndIt3;
	BeginIt3=m_VTablePublicSymbolList.begin();
	EndIt3=m_VTablePublicSymbolList.end();
	bFind =false;
	OutputDebugString("========================================================\n");
	char displaybuffer[100];
	for(;BeginIt3!=EndIt3;BeginIt3++)
	{
		sprintf(displaybuffer,"%08x %08x %s\n",(*BeginIt3).first.Rva,(*BeginIt3).first.Length ,(*BeginIt3).first.uName.Name);
		OutputDebugString(displaybuffer);
	
	}
	return true;
}
bool CSourceDebug::MakeSDSegment()
{
	LONG Count = 0;
	BOOL bValue;
	ULONG celt;
	IDiaSegment *pIDiaSegment=NULL;
	SDSEGMENT* pSegment=NULL;
	int i=0;
	if(SUCCEEDED(m_GlobalEnumSegments->get_Count(&Count))&&Count)
	{
		pSegment = new SDSEGMENT[Count];
		memset(pSegment,0,sizeof(SDSEGMENT)*Count);
		while(SUCCEEDED(m_GlobalEnumSegments->Next(1,&pIDiaSegment,&celt))&&celt==1&&pIDiaSegment)
		{
			pIDiaSegment->get_frame(&pSegment[i].SegmentNumber);
			pIDiaSegment->get_addressSection(&pSegment[i].SectionNumber);
			pIDiaSegment->get_length(&pSegment[i].Length);
			pIDiaSegment->get_offset(&pSegment[i].Offset);
			pIDiaSegment->get_relativeVirtualAddress(&pSegment[i].RVA);
			pIDiaSegment->get_virtualAddress(&pSegment[i].VA);
			pIDiaSegment->get_read(&bValue);
			pSegment[i].IsRead=bValue?1:0;
			pIDiaSegment->get_write(&bValue);
			pSegment[i].IsWrite=bValue?1:0;
			pIDiaSegment->get_execute(&bValue);
			pSegment[i].IsExecute=bValue?1:0;
			pIDiaSegment->Release();
			pIDiaSegment=NULL;celt=0;i++;
		}
	}
	return 0;
}
bool CSourceDebug::DumpFrameData()
{
	if(m_GlobalEnumFrameData==NULL)
		return false;
	static int FrameDataCount=0;
	SDPUBLICSYMBOL SdPublicSymbol;
	LONG count=0;
	ULONG celt;
	IDiaFrameData* pFrameData;
	DWORD Rav;
	if(SUCCEEDED(m_GlobalEnumFrameData->get_Count(&count))&& count)
	{
		while(SUCCEEDED(m_GlobalEnumFrameData->Next(1,&pFrameData,&celt))&&celt)
		{
			Rav = 0;
			if(SUCCEEDED(pFrameData->get_relativeVirtualAddress(&Rav)))
			{				
				list<DWORD>::iterator BeginIt,EndIt,findIt;
				BeginIt = m_FunctionRavList.begin();EndIt=m_FunctionRavList.end();
				findIt = find(BeginIt,EndIt,Rav);
				if(findIt==EndIt)
				{
					char* name2;
					name2 = new char[13];
					memset(&SdPublicSymbol,0,sizeof(SDPUBLICSYMBOL));
					TSPrintf(name2,"SEH_%08x",Rav);
					SdPublicSymbol.uName.Name = name2;
					SdPublicSymbol.Rva=Rav;
					DWORD BlockLength=0;
					pFrameData->get_lengthBlock(&BlockLength);
					SdPublicSymbol.Length=BlockLength;
					//m_PublicSymbolList.push_back(SdPublicSymbol);
					m_PublicSymbolList.insert(PUBLIC_SYMBOL_MAP::value_type(SdPublicSymbol,SdPublicSymbol.Rva));// push_back(SdPublicSymbol);
				}
				FrameDataCount++;
			}						
		}
	}
	FrameDataCount++;
	return true;
}
HRESULT CSourceDebug::NoRegCoCreate(PCSTR dllName,REFCLSID rclsid,REFIID riid,void **ppv)
{		
	HRESULT	hr=-1;
	IClassFactory* classFactory;
	if(m_DiaDllModule==NULL)
		Init();
	if(m_DiaDllGetClassObject)
	{
		hr = m_DiaDllGetClassObject(rclsid, IID_IClassFactory ,(void **) &classFactory);
		if(FAILED(hr))
			return hr;
		classFactory->CreateInstance(NULL,riid,ppv);
		classFactory->Release();
	}
	
	return hr;
}
void CSourceDebug::ClosePdbFile()
{
	if(m_GlobalEnumSegments)
	{
		m_GlobalEnumSegments->Release();
		m_GlobalEnumSegments=NULL;
	}
	if(m_GlobalEnumFrameData)
	{
		m_GlobalEnumFrameData->Release();
		m_GlobalEnumFrameData=NULL;
	}
	if(m_GlobalScopeSymbol)
	{
		m_GlobalScopeSymbol->Release();
		m_GlobalScopeSymbol=NULL;
	}
	if(m_DiaSession)
	{
		m_DiaSession->Release();
		m_DiaSession=NULL;
	}
	if(m_DiaDataSource)
	{
		m_DiaDataSource->Release();
		m_DiaDataSource=NULL;
	}
	return;
}
bool CSourceDebug::OpenPdbFile(PCSTR filename,  IDiaDataSource** DiaDataSource, IDiaSession** DiaSession,  IDiaSymbol** GlobalScopeSymbol,OUT bool* IsPDBFile) 
{					 
	HRESULT hr;
	if(IsPDBFile)
		*IsPDBFile=true;
#ifdef COM_INTERFACE_DIA
	hr = CoInitialize(NULL);
	if(FAILED(hr))
		return false;
	hr = CoCreateInstance(__uuidof(DiaSource) , NULL, CLSCTX_INPROC_SERVER, __uuidof( IDiaDataSource ), (void **) DiaDataSource);
	hr = CoCreateInstance(__uuidof(DiaSource),//CLSID_DiaSource, 
		NULL, 
		CLSCTX_INPROC_SERVER, 
		__uuidof(IDiaDataSource),
		(void **) DiaDataSource);
#else
	hr = NoRegCoCreate(NULL,__uuidof( DiaSourceAlt ),__uuidof( IDiaDataSource ), (void **) DiaDataSource);
	
	if (FAILED(hr))
	{   
		hr = NoRegCoCreate(NULL,__uuidof( DiaSourceAlt ),__uuidof( IDiaDataSource ), (void **) DiaDataSource);
		if (FAILED(hr))
			return false;
	}
#endif
	if (FAILED(hr))
	{   
		return false;
	}
	WCHAR wFileName[MAX_PATH*4];
	AnsiToUnicode(filename,wFileName,sizeof(wFileName));

	// Load the PDB file
	if (FAILED((*DiaDataSource)->loadDataFromPdb(wFileName)))
	{
		if(IsPDBFile)
			*IsPDBFile=false;
		if (FAILED((*DiaDataSource)->loadDataForExe(wFileName,NULL,NULL))) 
		{
			return false;
		}
	}

	// Open a session
	if (FAILED((*DiaDataSource)->openSession(DiaSession))) 
	{
		return false;
	}

	// Get the global scope
	if (FAILED((*DiaSession)->get_globalScope(GlobalScopeSymbol))) 
	{
		return false;
	}
	return true;
}


WCHAR*basetypename[]=
{

	WSTR("btNoType = 0"),
	WSTR("btVoid = 1"),
	WSTR("btChar = 2"),
	WSTR("btWChar = 3"),
	WSTR(""),
	WSTR(""),
	WSTR("btInt = 6"),
	WSTR("btUInt = 7"),
	WSTR("btFloat = 8"),
	WSTR("btBCD = 9"),
	WSTR("btBool = 10"),
	WSTR(""),
	WSTR(""),
	WSTR("btLong = 13"),
	WSTR("btULong = 14"),
	WSTR(""),
	WSTR(""),
	WSTR(""),
	WSTR(""),
	WSTR(""),
	WSTR(""),
	WSTR(""),
	WSTR(""),
	WSTR(""),
	WSTR(""),
	WSTR("btCurrency = 25"),
	WSTR("btDate = 26"),
	WSTR("btVariant = 27"),
	WSTR("btComplex = 28"),
	WSTR("btBit = 29"),
	WSTR("btBSTR = 30"),
	WSTR("btHresult = 31"),
	NULL,
};


WCHAR *SymTagName[]=
{	
		WSTR("SymTagNull"),
		WSTR("SymTagExe"),
		WSTR("SymTagCompiland"),
		WSTR("SymTagCompilandDetails"),
		WSTR("SymTagCompilandEnv"),
		WSTR("SymTagFunction"),
		WSTR("SymTagBlock"),
		WSTR("SymTagData"),
		WSTR("SymTagAnnotation"),
		WSTR("SymTagLabel"),
		WSTR("SymTagPublicSymbol"),
		WSTR("SymTagUDT"),
		WSTR("SymTagEnum"),
		WSTR("SymTagFunctionType"),
		WSTR("SymTagPointerType"),
		WSTR("SymTagArrayType"),
		WSTR("SymTagBaseType"),
		WSTR("SymTagTypedef"),
		WSTR("SymTagBaseClass"),
		WSTR("SymTagFriend"),
		WSTR("SymTagFunctionArgType"),
		WSTR("SymTagFuncDebugStart"),
		WSTR("SymTagFuncDebugEnd"),
		WSTR("SymTagUsingNamespace"),
		WSTR("SymTagVTableShape"),
		WSTR("SymTagVTable"),
		WSTR("SymTagCustom"),
		WSTR("SymTagThunk"),
		WSTR("SymTagCustomType"),
		WSTR("SymTagManagedType"),
		WSTR("SymTagDimension"),
		WSTR("SymTagMax"),
		NULL,
};
bool CSourceDebug::GetSymbolType(IDiaSymbol* Symbol,DWORD &TypeId,DWORD &symTag)
{
	IDiaSymbol *SymbolType=NULL;
	
	if(FAILED(Symbol->get_typeId(&TypeId)))
		return false;
	if(FAILED(Symbol->get_type(&SymbolType)))
		return false;
	if(SymbolType==NULL)
		return false;
	
	if(FAILED(SymbolType->get_symTag(&symTag)))
		return false;
	if(symTag==SymTagBaseType)		
		if(FAILED(SymbolType->get_baseType(&TypeId)))
			return false;

	return true;
}

WCHAR *CSourceDebug::GetSymbolTypeName(IN IDiaSymbol* Symbol,IN DWORD NameMaxLen,OUT WCHAR *Name)
{
	IDiaSymbol *SymbolType=NULL;
	BSTR SymbolTypeName=NULL;
	DWORD TypeId,symTag;
	DWORD pointerDepth;

	if(Symbol==NULL)
	{
		if(Name)
		{
			Name[0]=0;
			return Name;
		}else
			return NULL;
	}
	if(FAILED(Symbol->get_type(&SymbolType)))
		return NULL;
	if(SymbolType==NULL)
		return NULL;

	if(FAILED(SymbolType->get_symTag(&symTag)))
		return NULL;
	pointerDepth=0;
	while(symTag==SymTagPointerType)
	{
		pointerDepth++;
		// Get the next type down
		IDiaSymbol* tmpPointeeType;
		if (FAILED(SymbolType->get_type(&tmpPointeeType)))
		{
			break;
		}
		SymbolType->Release();
		SymbolType = tmpPointeeType;

		// get symtag of next type down
		if (FAILED(SymbolType->get_symTag(&symTag))) 
		{
			break;
		}
	}
	if(symTag==SymTagBaseType)
	{
		if(FAILED(SymbolType->get_baseType(&TypeId)))
			return false;
		if(Name)
			TStrCpyLimit(Name,basetypename[TypeId],NameMaxLen-1);
		return Name;
	}
	if(SUCCEEDED(SymbolType->get_name(&SymbolTypeName))&&SymbolTypeName)
	{
		if(Name)
		{
			int i=0;
			TStrCpyLimit(Name,SymbolTypeName,NameMaxLen-1);
			if(pointerDepth)
			{
				i = TStrLen(Name);
				for(;pointerDepth;i++,pointerDepth--)
				{
					Name[i]='*';
				}
				Name[i]=0;
			}
		}
		return Name;
	}else
	{				
		if(Name)
			TStrCpyLimit(Name,SymTagName[symTag],NameMaxLen-1);
		return Name;
	}
	return NULL;
}
WCHAR *datakindname[]=
{
	WSTR("DataIsUnknown"),
	WSTR("DataIsLocal"),
	WSTR("DataIsStaticLocal"),
	WSTR("DataIsParam"),
	WSTR("DataIsObjectPtr"),
	WSTR("DataIsFileStatic"),
	WSTR("DataIsGlobal"),
	WSTR("DataIsMember"),
	WSTR("DataIsStaticMember"),
	WSTR("DataIsConstant"),
	NULL,
};


WCHAR* DataKindName[]=
{		
	WSTR("DataIsUnknown"),
	WSTR("DataIsLocal"),
	WSTR("DataIsStaticLocal"),
	WSTR("DataIsParam"),
	WSTR("DataIsObjectPtr"),
	WSTR("DataIsFileStatic"),
	WSTR("DataIsGlobal"),
	WSTR("DataIsMember"),
	WSTR("DataIsStaticMember"),
	WSTR("DataIsConstant"),
	WSTR(""),
};
WCHAR* LocationTypeName[]=
{
	WSTR("LocIsNull"),
	WSTR("LocIsStatic"),
	WSTR("LocIsTLS"),
	WSTR("LocIsRegRel"),
	WSTR("LocIsThisRel"),
	WSTR("LocIsEnregistered"),
	WSTR("LocIsBitField"),
	WSTR("LocIsSlot"),
	WSTR("LocIsIlRel"),
	WSTR("LocInMetaData"),
	WSTR("LocIsConstant"),
	WSTR("LocTypeMax"),
	WSTR(""),
};
WCHAR *CV_access_eName[]=
{
	WSTR(""),
	WSTR("CV_private"),
	WSTR("CV_protected"),
	WSTR("CV_public"),
	WSTR(""),
};



bool CSourceDebug::ListGlobalSymbols(bool IsPDBFile)
{
	ULONG celt;
	IDiaSymbol *Symbol;
	int i =0;
	DWORD SelfReleaseFlags;
	IDiaEnumSymbols * EnumSymbols;
	SDTYPE *RetSDTYPE;
	if(m_GlobalScopeSymbol==NULL)
		return false;
	MakeSDEXE(m_GlobalScopeSymbol);
	InitEnumFrameDataTable();
	if(FAILED(m_GlobalScopeSymbol->findChildren(SymTagPublicSymbol,NULL,nsNone,&EnumSymbols))||EnumSymbols==NULL)
		return false;
	while(SUCCEEDED(EnumSymbols->Next(1,&Symbol,&celt))&&celt==1&&Symbol)
	{
		SelfReleaseFlags=1;
		MakeSDPublicSymbol(Symbol,&SelfReleaseFlags,NULL);
		if(SelfReleaseFlags)
		{
			Symbol->Release();
			Symbol=NULL;
		}
	}
	EnumSymbols->Release();
	EnumSymbols=NULL;
	if(FAILED(m_GlobalScopeSymbol->findChildren(SymTagCompiland,NULL,nsNone,&EnumSymbols))||EnumSymbols==NULL)
		return false;
	while(SUCCEEDED(EnumSymbols->Next(1,&Symbol,&celt))&&celt==1&&Symbol)
	{
		MakeSDCompiland(Symbol);
		Symbol->Release();
		Symbol=NULL;
	}
	EnumSymbols->Release();
	//return true;
	EnumSymbols=NULL;
	IsPDBFile=true;
	if(IsPDBFile)
	{
		//////////////////////////////////////////////////////////////////////////
		//    生成预先定义的 基本数据类型
		//////////////////////////////////////////////////////////////////////////
		MakePredefineSDBaseType();
		//////////////////////////////////////////////////////////////////////////
		//    先提取基本的数据类型
		//////////////////////////////////////////////////////////////////////////	
		if(FAILED(m_GlobalScopeSymbol->findChildren(SymTagBaseType,NULL,nsNone,&EnumSymbols))||EnumSymbols==NULL)
			return true;
		long n;
		EnumSymbols->get_Count(&n);
		while(SUCCEEDED(EnumSymbols->Next(1,&Symbol,&celt))&&celt==1&&Symbol)
		{
			SelfReleaseFlags=1;
			MakeSDType(Symbol,&SelfReleaseFlags,&RetSDTYPE);
			if(SelfReleaseFlags)		
				Symbol->Release();			
		}
		EnumSymbols->Release();


		if(FAILED(m_GlobalScopeSymbol->findChildren(SymTagNull,NULL,nsNone,&EnumSymbols))||EnumSymbols==NULL)
			return true;
		
		if(m_pfnSetRange)
		{
			LONG Count;
			EnumSymbols->get_Count(&Count);
			m_pfnSetRange(Count);
			m_ProgressStep = Count/100;
		}
		while(SUCCEEDED(EnumSymbols->Next(1,&Symbol,&celt))&&celt==1&&Symbol)
		{

			SelfReleaseFlags=1;
			MakeSDType(Symbol,&SelfReleaseFlags,&RetSDTYPE);
			if(SelfReleaseFlags)		
				Symbol->Release();
			i++;
			if(m_pfnSetPos)
			{
				if(m_ProgressStep && i%m_ProgressStep==0)
					m_pfnSetPos(i);
			}
		}
		EnumSymbols->Release();
	}
	else
	{
		if(FAILED(m_GlobalScopeSymbol->findChildren(SymTagData,NULL,nsNone,&EnumSymbols))||EnumSymbols==NULL)
			return true;
		while(SUCCEEDED(EnumSymbols->Next(1,&Symbol,&celt))&&celt==1&&Symbol)
		{

			SelfReleaseFlags=1;
			MakeSDType(Symbol,&SelfReleaseFlags,&RetSDTYPE);
			if(SelfReleaseFlags)		
				Symbol->Release();
			i++;

		}
		EnumSymbols->Release();
		EnumSymbols=NULL;
		if(FAILED(m_GlobalScopeSymbol->findChildren(SymTagFunction,NULL,nsNone,&EnumSymbols))||EnumSymbols==NULL)
			return true;
		while(SUCCEEDED(EnumSymbols->Next(1,&Symbol,&celt))&&celt==1&&Symbol)
		{

			SelfReleaseFlags=1;
			MakeSDType(Symbol,&SelfReleaseFlags,&RetSDTYPE);
			if(SelfReleaseFlags)		
				Symbol->Release();
			i++;

		}
		EnumSymbols->Release();
	}
	ReleaseIDiaSymbol();
	//m_FuntionID.sort();
	//sort(m_SymbolList.begin(),m_SymbolList.end());
	//m_SymbolList.sort();
	return true;
}


WCHAR *CSourceDebug::GetSymbolName(IN IDiaSymbol* Symbol,IN DWORD NameMaxLen,OUT WCHAR *Name)
{
	BSTR SymbolName=NULL;
	if(Symbol==NULL)
	{
		if(Name)
		{
			Name[0]=0;
			return Name;
		}else
			return NULL;
	}
	if(SUCCEEDED(Symbol->get_name(&SymbolName))&&SymbolName)
	{
		if(Name)
			TStrCpyLimit(Name,SymbolName,NameMaxLen-1);
		return Name;
	}else
	{
		DWORD symIndexId;
		symIndexId=0xffffffff;
		if(SUCCEEDED(Symbol->get_symIndexId(&symIndexId))&&symIndexId!=0xffffffff)
		{
			TSPrintf(Name,WSTR("%08x"),symIndexId);			
		}else
		{		
			if(Name)
			{
				Name[0]=0;
				return Name;
			}else
				return NULL;
		}
	}
	return NULL;
}
bool CSourceDebug::CheckSymbolSymTagType(IDiaSymbol *Symbol,enum SymTagEnum TagType)
{
	DWORD symTag;
	if(Symbol==NULL)
		return false;
	if(FAILED(Symbol->get_symTag(&symTag)))
		return false;
	return symTag==TagType;
}

bool CSourceDebug::InitEnumFrameDataTable()
{
	IDiaTable* pTable=NULL;
	ULONG celt;
	IDiaEnumTables *EnumTables=NULL;
	IDiaEnumFrameData* pIDiaEnumFrameData=NULL;
	IDiaEnumSegments* pIDiaEnumSegments=NULL;
	m_GlobalEnumFrameData=NULL;
	if(FAILED(m_DiaSession->getEnumTables(&EnumTables))||EnumTables==NULL)	
		return false;
	while(SUCCEEDED(EnumTables->Next(1,&pTable,&celt))&&celt==1)
	{
		if(SUCCEEDED(pTable->QueryInterface(_uuidof(IDiaSegment),(void**)&pIDiaEnumSegments))&&pIDiaEnumSegments)
		{
			m_GlobalEnumSegments=pIDiaEnumSegments;
			pTable->Release();
			break;
		}
		pTable->Release();
		pTable=NULL;
	}
	EnumTables->Release();
	if(FAILED(m_DiaSession->getEnumTables(&EnumTables))||EnumTables==NULL)	
		return false;
	while(SUCCEEDED(EnumTables->Next(1,&pTable,&celt))&&celt==1)
	{
		if(SUCCEEDED(pTable->QueryInterface(_uuidof(IDiaEnumFrameData),(void**)&pIDiaEnumFrameData))&&pIDiaEnumFrameData)
		{
			m_GlobalEnumFrameData=pIDiaEnumFrameData;
			pTable->Release();
			break;
		}
		pTable->Release();
		pTable=NULL;
	}
	EnumTables->Release();
	return true;
}
WCHAR *udtKindName[]={
	WSTR("struct"),
	WSTR("class"),
	WSTR("union"),
	WSTR("error udt kind"),
};

IDiaSymbol* CSourceDebug::FindSymbol(WCHAR *SymbolName,enum SymTagEnum SymTag,IDiaSymbol* Symbol)
{
	ULONG celt;
	IDiaEnumSymbols *EnumSymbols;
	IDiaSymbol* pCurSymbol;
	if(Symbol==NULL)
		Symbol=m_GlobalScopeSymbol;
	if(FAILED(Symbol->findChildren(SymTag,SymbolName,nsNone,&EnumSymbols))||EnumSymbols==NULL)
		return NULL;
	if(SUCCEEDED(EnumSymbols->Next(1,&pCurSymbol,&celt))&&celt==1)
		return pCurSymbol;
	return NULL;
}

IDiaSymbol* CSourceDebug::DumpSymTagPointerType(IDiaSymbol *Symbol,HANDLE pItem/*,CWispList* pListTree*/,DWORD *Depth)
{
	DWORD pointerDepth=0;
	if(Symbol==NULL)
		return NULL;
	if(CheckSymbolSymTagType(Symbol,SymTagPointerType)==false)
		return NULL;
	BOOL ref;
	if(FAILED(Symbol->get_reference(&ref)))
		return NULL;
	if(ref)
		return NULL;
	IDiaSymbol * pCurSymbol=NULL;
	DWORD dwSymTag;
	bool First=false;
	while(SUCCEEDED(Symbol->get_type(&pCurSymbol))&&pCurSymbol!=NULL)
	{
		pointerDepth++;
		if(FAILED(pCurSymbol->get_symTag(&dwSymTag)))
		{
			pCurSymbol->Release();
			return NULL;
		}
		if(dwSymTag!=SymTagPointerType)
		{
			if(Depth)
				*Depth=pointerDepth;
			if(First)
				Symbol->Release();
			return pCurSymbol;
		}
		if(FAILED(pCurSymbol->get_reference(&ref)))
		{
			pCurSymbol->Release();
			return NULL;
		}
		if(ref)
		{
			pCurSymbol->Release();
			return NULL;
		}
		if(First)
			Symbol->Release();
		Symbol=pCurSymbol;
		First=true;
	}
	return NULL;
}

bool CSourceDebug::CreateSDSymbolFile(const char *FileName,DWORD TimeDateStamp,DWORD PECheckSum,PCSTR szModuleName)
{
	char *NullPage,*TempChar,*FileHeaderBuf;
	SDSYMBOLFILE* pSDSymbolFile;
	SDTYPE NullType;
	SDUDTDATAITEM NullData;
	SDFUNCTIONITEM NullFunction;
	DWORD dwWriteLen,DataCounter,Temp,SymbolCounter,Index=0,FunctionCounter;
	SDTYPE* pType;
	DWORD* pSymbolOffsetArray,*pFunctionOffsetArray;
	SYMBOLLIST sl;
	size_t Size;
	DWORD FileHeaderLen;

	NullPage=new char[0x1000];
	memset(NullPage,0,0x1000);
	m_StringTableBlockBeginOffset=0;
	m_CurrentStringTableMaxLen=STRINGTABLEDUMPBLOCKSIZE;
	m_StringTable = new char[m_CurrentStringTableMaxLen];
	memset(m_StringTable,0,m_CurrentStringTableMaxLen);
	m_StringTableOffset=1;
	m_StringIndex=1;

	FileHeaderBuf = new char[SDSF_FILE_HEADER_SIZE];
	memset(FileHeaderBuf,0,SDSF_FILE_HEADER_SIZE);
	pSDSymbolFile = (SDSYMBOLFILE*)FileHeaderBuf;
	pSDSymbolFile->Sig = SYSER_DEBUG_SYMBOL_FILE_SIG;
	pSDSymbolFile->SymbolDirectoryEntryNum=SD_MAX_TYPEIDS;
	pSDSymbolFile->Version=SYSER_DEBUG_SYMBOL_FILE_VER;

	Size = m_SymbolList.size();
	pSDSymbolFile->SymbolTotalNum=*(DWORD*)&Size;
	pSDSymbolFile->SymbolTotalNum++;//因为欲留一个空的所以要加一个
	pSDSymbolFile->UnionSymbolTable.SymbolTableOffset=SDSF_FILE_HEADER_SIZE;
	pSDSymbolFile->ModuleID.TimeDateStamp = TimeDateStamp;
	pSDSymbolFile->ModuleID.OrgPECheckSum=PECheckSum;
	if(gpFileIO->CreateFile(FileName,&m_hFile)==false)
		return false;
	gpFileIO->WriteFile(m_hFile,FileHeaderBuf,SDSF_FILE_HEADER_SIZE);//写入文件头	
	m_FileOffset=SDSF_FILE_HEADER_SIZE;		
	SymbolCounter=pSDSymbolFile->SymbolTotalNum;	
	Size=m_DataTagVector.size();
	DataCounter=*(DWORD*)&Size;
	pSymbolOffsetArray = new DWORD [SymbolCounter];
	memset(pSymbolOffsetArray,0,sizeof(DWORD)*SymbolCounter);		
	
	Index=0;
	pSymbolOffsetArray[Index]=m_FileOffset;
	memset(&NullType,0,sizeof(SDTYPE));
	gpFileIO->WriteFile(m_hFile,&NullType,sizeof(SDTYPE));			//写入第一个空结构
	m_FileOffset+=sizeof(SDTYPE);
	m_StringIDVector.push_back(0);									//空的字符串的索引
	ULLPOS CurFileLen;
	CurFileLen = gpFileIO->SetFilePointer(m_hFile,0,FILE_CURRENT);
	CODE_ASSERT(CurFileLen==m_FileOffset);
	////////////////////////////////////////////////////////
	//保存符号到文件
	////////////////////////////////////////////////////////
	//sort(m_SymbolList.begin(),m_SymbolList.end());
	//m_SymbolList.sort();
	//SDSymbolList::iterator BeginIt,EndIt;
	SD_SYMBOL_MAP::iterator BeginIt,EndIt;

	BeginIt = m_SymbolList.begin();EndIt=m_SymbolList.end();
	for(Index=1;BeginIt!=EndIt;BeginIt++,Index++)
	{	
		pSymbolOffsetArray[Index]=m_FileOffset;
		sl = (*BeginIt).first;
		//sl = *BeginIt;
		
		pType = sl.type;		
		dwWriteLen=0;
		if(Index!=sl.id)
			MessageBox(NULL,"Sort error","error",MB_OK);
		switch(pType->SDTypeInfile.Type) 
		{
		case SD_CLASS:
		case SD_STRUCT:
		case SD_UNION:
			dwWriteLen = DumpSDUDTTypeToFile(pType);
			break;
		case SD_TYPEDEF:
			dwWriteLen = DumpSDTypedefTypeToFile(pType);			
			break;
		case SD_ENUMERATION:
			dwWriteLen = DumpSDEnumTypeToFile(pType);
			break;
		case SD_REFERENCE:
			dwWriteLen = DumpSDReferenceTypeToFile(pType);			
			break;
		case SD_POINTER:
			dwWriteLen = DumpSDPointerTypeToFile(pType);			
			break;
		case SD_FUNCTIONTYPE:
			dwWriteLen = DumpSDFunctionTypeToFile(pType);
			break;
		case SD_ARRAY:
			dwWriteLen = DumpSDArrayToFile(pType);
			break;
		case SD_BASECLASS:
			dwWriteLen = DumpSDUDTBaseClassTypeToFile(pType);			
			break;
		case SD_THUNK:
			dwWriteLen = DumpSDThunkTypeToFile(pType);			
			break;
		case SD_BASIC:
			dwWriteLen = DumpSDBasicTypeToFile(pType);
			break;
		case SD_MANAGED:
			dwWriteLen = DumpSDManagedToFile(pType);
			break;
		case SD_CUSTOM:
			dwWriteLen = DumpSDCustomToFile(pType);
			break;
		case SD_BLOCK:
			dwWriteLen = DumpSDBlockToFile(pType);
			break;
		case SD_VTABLE:
			dwWriteLen = DumpSDVTableToFile(pType);
		case SD_FRIEND:
			dwWriteLen = DumpSDFriendToFile(pType);
		default:
			pSymbolOffsetArray[Index]=SDSF_FILE_HEADER_SIZE;
			break;
		}
		if(dwWriteLen==0)
			pSymbolOffsetArray[Index]=SDSF_FILE_HEADER_SIZE;
		m_FileOffset+=dwWriteLen;	
		CurFileLen = gpFileIO->SetFilePointer(m_hFile,0,FILE_CURRENT);
		CODE_ASSERT(CurFileLen==m_FileOffset);
	}
	CurFileLen = gpFileIO->SetFilePointer(m_hFile,0,FILE_CURRENT);
	CODE_ASSERT(CurFileLen==m_FileOffset);
	Temp = m_FileOffset % SECTION_ALIGN_SIZE;
	if(Temp)
	{
		Temp = SECTION_ALIGN_SIZE - Temp;
		gpFileIO->WriteFile(m_hFile,NullPage,Temp);
	}
	m_FileOffset+=Temp;
	CurFileLen = gpFileIO->SetFilePointer(m_hFile,0,FILE_CURRENT);
	CODE_ASSERT(CurFileLen==m_FileOffset);
	////////////////////////////////////////////////////////
	//保存符号偏移表到文件
	////////////////////////////////////////////////////////
	pSDSymbolFile->UnionSymbolIndexTable.SymbolIndexTableOffset=m_FileOffset;
	gpFileIO->WriteFile(m_hFile,pSymbolOffsetArray,sizeof(DWORD)*SymbolCounter);
	m_FileOffset+=(sizeof(DWORD)*SymbolCounter);
	Temp = m_FileOffset % SECTION_ALIGN_SIZE;
	if(Temp)
	{
		Temp = SECTION_ALIGN_SIZE - Temp;
		gpFileIO->WriteFile(m_hFile,NullPage,Temp);
	}
	m_FileOffset+=Temp;
	CurFileLen = gpFileIO->SetFilePointer(m_hFile,0,FILE_CURRENT);
	CODE_ASSERT(CurFileLen==m_FileOffset);
	////////////////////////////////////////////////////////
	//保存数据信息到文件
	////////////////////////////////////////////////////////

	pSDSymbolFile->UnionDataInformation.DataInformationOffset=m_FileOffset;
	m_FileOffset+=sizeof(SDUDTDATAITEM);
	memset(&NullData,0,sizeof(SDUDTDATAITEM));
	gpFileIO->WriteFile(m_hFile,&NullData,sizeof(SDUDTDATAITEM));			//写入第一个空数据信息
	CurFileLen = gpFileIO->SetFilePointer(m_hFile,0,FILE_CURRENT);
	CODE_ASSERT(CurFileLen==m_FileOffset);
	for(Index = 1; Index < DataCounter;Index++)
	{
		dwWriteLen = DumpSDDataToFile(m_DataTagVector[Index]);
		m_FileOffset+=dwWriteLen;
		CurFileLen = gpFileIO->SetFilePointer(m_hFile,0,FILE_CURRENT);
		CODE_ASSERT(CurFileLen==m_FileOffset);;
	}
	pSDSymbolFile->DataInformationNum=DataCounter;
	CurFileLen = gpFileIO->SetFilePointer(m_hFile,0,FILE_CURRENT);
	CODE_ASSERT(CurFileLen==m_FileOffset);
	Temp = m_FileOffset % SECTION_ALIGN_SIZE;
	if(Temp)
	{
		Temp = SECTION_ALIGN_SIZE - Temp;
		gpFileIO->WriteFile(m_hFile,NullPage,Temp);
	}
	m_FileOffset+=Temp;
	CurFileLen = gpFileIO->SetFilePointer(m_hFile,0,FILE_CURRENT);
	CODE_ASSERT(CurFileLen==m_FileOffset);
	////////////////////////////////////////////////////////
	//保存函数符号信息到文件
	////////////////////////////////////////////////////////
	//m_FuntionID.sort();
	Size = m_FuntionID.size();
	FunctionCounter =1 + *(DWORD*)&Size;
	pFunctionOffsetArray = new DWORD[FunctionCounter];
	memset(pFunctionOffsetArray,0,sizeof(DWORD)*FunctionCounter);

	pSDSymbolFile->UnionFunctionSymbol.FunctionSymbolOffset =m_FileOffset;
	pFunctionOffsetArray[0]=m_FileOffset;
	m_FileOffset+=sizeof(SDFUNCTIONITEM);
	memset(&NullFunction,0,sizeof(SDFUNCTIONITEM));
	gpFileIO->WriteFile(m_hFile,&NullFunction,sizeof(SDFUNCTIONITEM));			//写入第一个空数据信息
	CurFileLen = gpFileIO->SetFilePointer(m_hFile,0,FILE_CURRENT);
	CODE_ASSERT(CurFileLen==m_FileOffset);
	FUNCTION_ID_MAP::iterator FuncIdBeginIT,FuncIdEndIT;// m_FuntionID;
	FuncIdBeginIT = m_FuntionID.begin();
	FuncIdEndIT = m_FuntionID.end();
	PSDFUNCTIONITEM pFunctionItem;
	for(;FuncIdBeginIT!=FuncIdEndIT;FuncIdBeginIT++)
		m_IDFuntionMap.insert(ID_FUNCTION_MAP::value_type((*FuncIdBeginIT).second,(PSTFUNCTIONID)&(*FuncIdBeginIT).first));// .push_back(&(*FuncBeginIT).first);
	ID_FUNCTION_MAP::iterator FuncBeginIT,FuncEndIT;// m_FuntionID;
	FuncBeginIT = m_IDFuntionMap.begin();
	FuncEndIT=m_IDFuntionMap.end();

	for(;FuncBeginIT!=FuncEndIT;FuncBeginIT++)
	{
		pFunctionItem = (*FuncBeginIT).second->pFuncItem;
		pFunctionOffsetArray[pFunctionItem->ID]=m_FileOffset;
		CODE_ASSERT(FunctionCounter>=pFunctionItem->ID);
		dwWriteLen = DumpSDFunctionToFile(pFunctionItem);
		if(dwWriteLen==0)
			pFunctionOffsetArray[pFunctionItem->ID]=pFunctionOffsetArray[0];
		m_FileOffset+=dwWriteLen;
		//CurFileLen = gpFileIO->SetFilePointer(m_hFile,0,FILE_CURRENT);
		//CODE_ASSERT(CurFileLen==m_FileOffset);
	}	
	m_IDFuntionMap.clear();
	pSDSymbolFile->FunctionSymbolNum=FunctionCounter;
	Temp = m_FileOffset % SECTION_ALIGN_SIZE;
	if(Temp)
	{
		Temp = SECTION_ALIGN_SIZE - Temp;
		gpFileIO->WriteFile(m_hFile,NullPage,Temp);
	}
	m_FileOffset+=Temp;
	CurFileLen = gpFileIO->SetFilePointer(m_hFile,0,FILE_CURRENT);
	CODE_ASSERT(CurFileLen==m_FileOffset);	
	////////////////////////////////////////////////////////
	//保存函数符号信息偏移表到文件
	////////////////////////////////////////////////////////
	pSDSymbolFile->UnionFunctionSymbolIndexTable.FunctionSymbolIndexTableOffset=m_FileOffset;
	gpFileIO->WriteFile(m_hFile,pFunctionOffsetArray,sizeof(DWORD)*FunctionCounter);
	delete []pFunctionOffsetArray;
	m_FileOffset+=(sizeof(DWORD)*FunctionCounter);
	Temp = m_FileOffset % SECTION_ALIGN_SIZE;
	if(Temp)
	{
		Temp = SECTION_ALIGN_SIZE - Temp;
		gpFileIO->WriteFile(m_hFile,NullPage,Temp);
	}
	m_FileOffset+=Temp;
	CurFileLen = gpFileIO->SetFilePointer(m_hFile,0,FILE_CURRENT);
	CODE_ASSERT(CurFileLen==m_FileOffset);
	////////////////////////////////////////////////////////
	//保存行号信息到文件
	////////////////////////////////////////////////////////
	pSDSymbolFile->UnionLineNumber.LineNumberOffset=m_FileOffset;
	DWORD WritedLen = DumpSDLineNumberToFile(&pSDSymbolFile->LineNumberCounter);
	m_FileOffset+=WritedLen;
	Temp = m_FileOffset % SECTION_ALIGN_SIZE;
	if(Temp)
	{
		Temp = SECTION_ALIGN_SIZE - Temp;
		gpFileIO->WriteFile(m_hFile,NullPage,Temp);
	}
	m_FileOffset+=Temp;
	CurFileLen = gpFileIO->SetFilePointer(m_hFile,0,FILE_CURRENT);
	CODE_ASSERT(CurFileLen==m_FileOffset);
	////////////////////////////////////////////////////////
	//保存源文件列表到文件
	////////////////////////////////////////////////////////
	pSDSymbolFile->UnionSourceFileIDTable.SourceFileIDTableOffset=m_FileOffset;
	ULLPOS ll;
	ll = gpFileIO->SetFilePointer(m_hFile,0,FILE_CURRENT);
	WritedLen = DumpSDSourceFileToFile(&pSDSymbolFile->SourceFileCounter);
	m_FileOffset+=WritedLen;

	Temp = m_FileOffset % SECTION_ALIGN_SIZE;
	if(Temp)
	{
		Temp = SECTION_ALIGN_SIZE - Temp;
		gpFileIO->WriteFile(m_hFile,NullPage,Temp);
	}
	m_FileOffset+=Temp;
	CurFileLen = gpFileIO->SetFilePointer(m_hFile,0,FILE_CURRENT);
	CODE_ASSERT(CurFileLen==m_FileOffset);
	////////////////////////////////////////////////////////
	//保存全局的符号表到文件
	////////////////////////////////////////////////////////
	pSDSymbolFile->UnionPublicSymbol.PublicSymbolOffset=m_FileOffset;
	WritedLen = DumpSDPublicSymbolToFile(&pSDSymbolFile->PublicSymbolCounter);
	m_FileOffset+=WritedLen;
	Temp = m_FileOffset % SECTION_ALIGN_SIZE;
	if(Temp)
	{
		Temp = SECTION_ALIGN_SIZE - Temp;
		gpFileIO->WriteFile(m_hFile,NullPage,Temp);
	}
	m_FileOffset+=Temp;
	CurFileLen = gpFileIO->SetFilePointer(m_hFile,0,FILE_CURRENT);
	CODE_ASSERT(CurFileLen==m_FileOffset);
	////////////////////////////////////////////////////////
	//保存 Compiland 到文件
	////////////////////////////////////////////////////////
	pSDSymbolFile->UniosCompiland.CompilandOffset=m_FileOffset;
	WritedLen = DumpSDCompilandToFile(&pSDSymbolFile->CompilandCounter);
	m_FileOffset+=WritedLen;
	Temp = m_FileOffset % SECTION_ALIGN_SIZE;
	if(Temp)
	{
		Temp = SECTION_ALIGN_SIZE - Temp;
		gpFileIO->WriteFile(m_hFile,NullPage,Temp);
	}
	m_FileOffset+=Temp;
	CurFileLen = gpFileIO->SetFilePointer(m_hFile,0,FILE_CURRENT);
	CODE_ASSERT(CurFileLen==m_FileOffset);
	////////////////////////////////////////////////////////
	//保存字符串的偏移表到文件
	////////////////////////////////////////////////////////
	Size = m_StringIDVector.size();
	pSDSymbolFile->StringTotalNum=*(DWORD*)&Size;
	pSDSymbolFile->UnionStringIndexTable.StringIndexTableOffset=m_FileOffset;
	if(pSDSymbolFile->StringTotalNum>SymbolCounter)
	{		
		delete []pSymbolOffsetArray;
		pSymbolOffsetArray = new DWORD[pSDSymbolFile->StringTotalNum];	
	}		
	for(unsigned i=0;i<pSDSymbolFile->StringTotalNum;i++)
		pSymbolOffsetArray[i]=m_StringIDVector[i];		
	gpFileIO->WriteFile(m_hFile,pSymbolOffsetArray,sizeof(DWORD)*pSDSymbolFile->StringTotalNum);
	delete []pSymbolOffsetArray;
	m_FileOffset+=(sizeof(DWORD)*pSDSymbolFile->StringTotalNum);
	Temp = m_FileOffset % SECTION_ALIGN_SIZE;
	if(Temp)
	{
		Temp = SECTION_ALIGN_SIZE - Temp;
		gpFileIO->WriteFile(m_hFile,NullPage,Temp);
	}
	m_FileOffset+=Temp;
	CurFileLen = gpFileIO->SetFilePointer(m_hFile,0,FILE_CURRENT);
	CODE_ASSERT(CurFileLen==m_FileOffset);
	////////////////////////////////////////////////////////
	//保存 串表到文件
	////////////////////////////////////////////////////////
	pSDSymbolFile->UnionStringTable.StringTableOffset=m_FileOffset;
	DUMP_STRING_LOCK_LIST::iterator FirstIt,LastIt;
	FirstIt = m_StringDumpBlockList.begin();
	LastIt = m_StringDumpBlockList.end();
	for(;FirstIt!=LastIt;FirstIt++)
	{
		void * WBuf=(*FirstIt).BlockBaseAddress ;
		DWORD WLen=(*FirstIt).EndOffset-(*FirstIt).BeginOffset;
		gpFileIO->WriteFile(m_hFile,WBuf,WLen);
		m_FileOffset+=WLen;
		delete []WBuf;
	}

	gpFileIO->WriteFile(m_hFile,m_StringTable,m_StringTableOffset-m_StringTableBlockBeginOffset);
	m_FileOffset+=m_StringTableOffset-m_StringTableBlockBeginOffset;
	delete []m_StringTable;
	Temp = m_FileOffset % SECTION_ALIGN_SIZE;
	if(Temp)
	{
		Temp = SECTION_ALIGN_SIZE - Temp;
		gpFileIO->WriteFile(m_hFile,NullPage,Temp);
	}
	m_FileOffset+=Temp;
	FileHeaderLen=SDSF_FILE_HEADER_SIZE-sizeof(SDSYMBOLFILE);

	Temp = TStrLen(m_PEFileName)+1;
	if(FileHeaderLen<Temp)
	{
		pSDSymbolFile->uPEFileName.PEFileNameOffset = m_FileOffset;
		gpFileIO->WriteFile(m_hFile,m_PEFileName,Temp);
		m_FileOffset += Temp;
		pSDSymbolFile->PEFileNameLen=Temp;
	}
	else
	{
		pSDSymbolFile->uPEFileName.PEFileNameOffset = SDSF_FILE_HEADER_SIZE-FileHeaderLen;
		TempChar=(char*)pSDSymbolFile;
		TStrCpy(&TempChar[SDSF_FILE_HEADER_SIZE-FileHeaderLen],m_PEFileName);
		FileHeaderLen-=Temp;
		pSDSymbolFile->PEFileNameLen=Temp;
	}
	Temp = TStrLen(m_PDBFileName)+1;
	if(FileHeaderLen<Temp)
	{
		pSDSymbolFile->uPDBFileName.PDBFileNameOffset = m_FileOffset;
		gpFileIO->WriteFile(m_hFile,m_PDBFileName,Temp);
		m_FileOffset += Temp;
		pSDSymbolFile->PDBFileNameLen=Temp;
	}
	else
	{
		pSDSymbolFile->uPDBFileName.PDBFileNameOffset = SDSF_FILE_HEADER_SIZE-FileHeaderLen;
		TempChar=(char*)pSDSymbolFile;
		TStrCpy(&TempChar[SDSF_FILE_HEADER_SIZE-FileHeaderLen],m_PDBFileName);
		FileHeaderLen-=Temp;
		pSDSymbolFile->PDBFileNameLen=Temp;
	}
	if(szModuleName)
	{
		Temp = TStrLen(szModuleName)+1;
		if(FileHeaderLen<Temp)
		{
			pSDSymbolFile->uPEFileFullName.PEFileFullNameOffset=m_FileOffset;
			gpFileIO->WriteFile(m_hFile,szModuleName,Temp);
			m_FileOffset+=Temp;
			pSDSymbolFile->PEFileFullNameLen=Temp;
		}
		else
		{
			pSDSymbolFile->uPEFileFullName.PEFileFullNameOffset=SDSF_FILE_HEADER_SIZE-FileHeaderLen;
			TempChar=(char*)pSDSymbolFile;
			TStrCpy(&TempChar[SDSF_FILE_HEADER_SIZE-FileHeaderLen],szModuleName);
			FileHeaderLen-=Temp;
			pSDSymbolFile->PEFileFullNameLen=Temp;
		}
	}
	Temp = m_FileOffset % 0x1000;
	if(Temp)
	{
		Temp = 0x1000 - Temp;
		gpFileIO->WriteFile(m_hFile,NullPage,Temp);
	}
	m_FileOffset += Temp;
	pSDSymbolFile->FileLen=m_FileOffset;
	gpFileIO->WriteFile(m_hFile,pSDSymbolFile,SDSF_FILE_HEADER_SIZE,0);
	gpFileIO->CloseHandle(m_hFile);
	WriteSDSymbolFileCheckSum(FileName);
	//ReleaseSDType();
	delete []NullPage;
	delete []FileHeaderBuf;
	return true;
}
bool CSourceDebug::WriteSDSymbolFileCheckSum(const char *FileName)
{
	DWORD FileLen,i;
	DWORD* pBuffer;
	HANDLE hFile;
	PSDSYMBOLFILE pSDSymbolFile;
	ULONGLONG CheckSum=0;
	if(gpFileIO->OpenFile(FileName,&hFile,FIO_READ|FIO_WRITE)==false)
		return false;
	
	FileLen = (DWORD)gpFileIO->GetFileLength(hFile);
	if(FileLen&0xfff)
	{
		gpFileIO->CloseHandle(hFile);
		return false;
	}
	pBuffer = (DWORD*)new BYTE[FileLen];
	if(pBuffer==NULL)
	{
		gpFileIO->CloseHandle(hFile);
		return false;
	}
	gpFileIO->SetFilePointer(hFile,0,FILE_CURRENT);
	if(gpFileIO->ReadFile(hFile,pBuffer,FileLen,0)!=FileLen)
	{
		gpFileIO->CloseHandle(hFile);
		return false;
	}	
	pSDSymbolFile = (PSDSYMBOLFILE)pBuffer;
	pSDSymbolFile->CheckSum=0;
	for(i = 0; i < FileLen/sizeof(DWORD);i++)
	{
		CheckSum+=pBuffer[i];
	}

	pSDSymbolFile->CheckSum=*(DWORD*)&CheckSum;
	gpFileIO->WriteFile(hFile,pSDSymbolFile,sizeof(SDSYMBOLFILE),0);
	gpFileIO->FlushFileBuffer(hFile);
	gpFileIO->CloseHandle(hFile);
	delete []pBuffer;
	return true;
}
DWORD CSourceDebug::DumpSDSourceFileToFile(DWORD* SourceFileCounter)
{	
	ID_TO_SOURCE_FILE_NAME_MAP::iterator BeginIT,EndIT;
	SDSOURCEFILEID* pSourceID;
	DWORD WriteLen;
	DWORD OffsetAtFile = 0;
	size_t Size;
	DWORD Counter; 
	Size = m_IdToSourceFileNameMap.size();
	Counter=*(DWORD*)&Size;
	pSourceID = new SDSOURCEFILEID[Counter];
	WriteLen = sizeof(SDSOURCEFILEID)*Counter;
	memset(pSourceID,0,WriteLen);
	BeginIT=m_IdToSourceFileNameMap.begin();
	EndIT=m_IdToSourceFileNameMap.end();
	int i = 0;
	for(;BeginIT!=EndIT;BeginIT++,i++)
	{
		pSourceID[i].uName.MemberNameInStringTableIndex = DumpSDTypeName(BeginIT->first.Name);
		pSourceID[i].FileID=BeginIT->first.Id;
	}
	CODE_ASSERT(i==Counter);
	gpFileIO->WriteFile(m_hFile,pSourceID,WriteLen);
	if(SourceFileCounter)
		*SourceFileCounter=Counter;
	delete []pSourceID;
	return WriteLen;	
}
DWORD CSourceDebug::DumpSDLineNumberToFile(DWORD* LineNumbers)
{	
	DWORD dwTotalLineNumbers=0;	
	size_t Size;
	DWORD WriteTotalLen=0;	
	SDLINE* pLine;	
	list <SDLINE>::iterator BeginIT,EndIT;
	Size = m_TotalLineNumber.size();
	dwTotalLineNumbers = *(DWORD*)&Size;
	pLine = new SDLINE[dwTotalLineNumbers];
	WriteTotalLen = sizeof(SDLINE)*dwTotalLineNumbers;
	m_TotalLineNumber.sort();
	BeginIT=m_TotalLineNumber.begin();
	EndIT=m_TotalLineNumber.end();
	int i = 0;
	for(;BeginIT!=EndIT;BeginIT++,i++)	
		pLine[i]=*BeginIT;
	gpFileIO->WriteFile(m_hFile,pLine,WriteTotalLen);
	if(LineNumbers)
		*LineNumbers=dwTotalLineNumbers;
	delete []pLine;
	return WriteTotalLen;
}
DWORD CSourceDebug::DumpSDPublicSymbolToFile(DWORD* PublicSymbolNumbers)
{		
	SDPUBLICSYMBOL* pPublicSymbol;
	
	char string[]="`string'";
	PUBLIC_SYMBOL_MAP::iterator BeginIt,EndIt;		
	size_t count = m_PublicSymbolList.size();
	DWORD WriteLen =*(DWORD*)&count * sizeof(SDPUBLICSYMBOL);
	vector<DWORD>::iterator beingIt,endIt,valueIt;
	pPublicSymbol = new SDPUBLICSYMBOL[count];
	memset(pPublicSymbol,0,WriteLen);
	BeginIt = m_PublicSymbolList.begin();
	EndIt = m_PublicSymbolList.end();

	int i,j = 0,k=0,m=0;
	for( i =0;BeginIt!=EndIt;BeginIt++)
	{
		pPublicSymbol[i]=(*BeginIt).first;
		if(TStrCmp(string,pPublicSymbol[i].uName.Name))
			pPublicSymbol[i].uName.StringTableIndex = DumpSDTypeName(pPublicSymbol[i].uName.Name);
		else
		{
			if(m_StringName)
			{
				k++;
				pPublicSymbol[i].uName.StringTableIndex=m_StringNameID;
			}
			else
			{
				pPublicSymbol[i].uName.StringTableIndex = DumpSDTypeName(pPublicSymbol[i].uName.Name);
				m_StringName=true;
				m_StringNameID=pPublicSymbol[i].uName.StringTableIndex;
			}
		}
		pPublicSymbol[i].UndecoratedName.StringTableIndex = DumpSDTypeName(pPublicSymbol[i].UndecoratedName.Name);
		i++;
	}
	WriteLen = i*sizeof(SDPUBLICSYMBOL);
	gpFileIO->WriteFile(m_hFile,pPublicSymbol,WriteLen);
	delete []pPublicSymbol;
	if(PublicSymbolNumbers)
		*PublicSymbolNumbers=i;
	return WriteLen;
}
DWORD CSourceDebug::DumpSDManagedToFile(SDTYPE* pType)
{
	DWORD WriteByteSize; 
	char* pOldName = pType->SDTypeInfile.uName.Name;
	WriteByteSize = pType->SDTypeInfile.Size-(sizeof(SDTYPE)-sizeof(SDTYPE_INFILE));
	pType->SDTypeInfile.uName.StringTableIndex = DumpSDTypeName(pType);
	gpFileIO->WriteFile(m_hFile,&pType->SDTypeInfile,WriteByteSize);
	pType->SDTypeInfile.uName.Name=pOldName;
	return WriteByteSize;
}


DWORD CSourceDebug::DumpSDVTableToFile(SDTYPE* pType)
{
	DWORD WriteByteSize; 
	char* pOldName = pType->SDTypeInfile.uName.Name;
	WriteByteSize = pType->SDTypeInfile.Size- (sizeof(SDTYPE)-sizeof(SDTYPE_INFILE));
	pType->SDTypeInfile.uName.StringTableIndex = DumpSDTypeName(pType);
	gpFileIO->WriteFile(m_hFile,&pType->SDTypeInfile,WriteByteSize);
	pType->SDTypeInfile.uName.Name=pOldName;
	return WriteByteSize;
}

DWORD CSourceDebug::DumpSDDataToFile(SDUDTDATAITEM* pUdtDataItem)
{
	DWORD WriteByteSize;
	char* pOldName = pUdtDataItem->uName.Name;
	pUdtDataItem->uName.StringTableIndex=DumpSDDataName(pUdtDataItem);
	WriteByteSize=sizeof(SDUDTDATAITEM);
	gpFileIO->WriteFile(m_hFile,pUdtDataItem,WriteByteSize);
	pUdtDataItem->uName.Name=pOldName;
	return WriteByteSize;
}
DWORD CSourceDebug::DumpSDBlockToFile(SDTYPE* pType)
{		
	DWORD WriteByteSize;
	WriteByteSize = pType->SDTypeInfile.Size-(sizeof(SDTYPE)-sizeof(SDTYPE_INFILE));
	gpFileIO->WriteFile(m_hFile,&pType->SDTypeInfile,WriteByteSize);		
	return WriteByteSize;		
}
DWORD CSourceDebug::DumpSDCustomToFile(SDTYPE* pType)
{
	char* pOldName = pType->SDTypeInfile.uName.Name;
	DWORD WriteByteSize;
	WriteByteSize = pType->SDTypeInfile.Size-(sizeof(SDTYPE)-sizeof(SDTYPE_INFILE));
	pType->SDTypeInfile.uName.StringTableIndex = DumpSDTypeName(pType);
	gpFileIO->WriteFile(m_hFile,&pType->SDTypeInfile,WriteByteSize);
	pType->SDTypeInfile.uName.Name=pOldName;
	return WriteByteSize;
}
DWORD CSourceDebug::DumpSDBasicTypeToFile(SDTYPE* pType)
{
	char* pOldName = pType->SDTypeInfile.uName.Name;
	DWORD WriteByteSize;
	pType->SDTypeInfile.uName.StringTableIndex = DumpSDTypeName(pType);
	WriteByteSize = pType->SDTypeInfile.Size-(sizeof(SDTYPE)-sizeof(SDTYPE_INFILE));
	gpFileIO->WriteFile(m_hFile,&pType->SDTypeInfile,WriteByteSize);
	pType->SDTypeInfile.uName.Name=pOldName;
	return WriteByteSize;
}
DWORD CSourceDebug::DumpSDCompilandToFile(DWORD* CompilandCounter)
{
	int i;
	size_t Count;
	SDCOMPILAND* pCompiland;
	ID_TO_COMPILAND_NAME_MAP::iterator BeginIt,EndIt;
	DWORD WriteByteSize;

	BeginIt = m_IdToCompilandMap.begin();
	EndIt = m_IdToCompilandMap.end();
	Count = m_IdToCompilandMap.size();
	WriteByteSize =*(DWORD*)&Count;
	WriteByteSize = WriteByteSize * sizeof(SDCOMPILAND);
	pCompiland = new SDCOMPILAND[Count];
	for(i=0;BeginIt!=EndIt;BeginIt++,i++)
	{
		pCompiland[i]=*(BeginIt->second);
		pCompiland[i].uName.MemberNameInStringTableIndex=DumpSDTypeName(pCompiland[i].uName.Name);
	}
	gpFileIO->WriteFile(m_hFile,pCompiland,WriteByteSize);
	delete []pCompiland;
	if(CompilandCounter)
		*CompilandCounter=*(DWORD*)&Count;
	return WriteByteSize;
}

DWORD CSourceDebug::DumpSDUDTBaseClassTypeToFile(SDTYPE* pType)
{	
	DWORD WriteByteSize;
	char *OldName = pType->SDTypeInfile.uName.Name;
	WriteByteSize = pType->SDTypeInfile.Size-(sizeof(SDTYPE)-sizeof(SDTYPE_INFILE));
	pType->SDTypeInfile.uName.StringTableIndex = DumpSDTypeName(pType);
	gpFileIO->WriteFile(m_hFile,&pType->SDTypeInfile,WriteByteSize);
	pType->SDTypeInfile.uName.Name=OldName;
	return WriteByteSize;
}
DWORD CSourceDebug::DumpSDArrayToFile(SDTYPE* pType)
{
	DWORD WriteByteSize;
	char *OldName = pType->SDTypeInfile.uName.Name;
	pType->SDTypeInfile.uName.StringTableIndex=DumpSDTypeName(pType);
	WriteByteSize = pType->SDTypeInfile.Size-(sizeof(SDTYPE)-sizeof(SDTYPE_INFILE));
	gpFileIO->WriteFile(m_hFile,&pType->SDTypeInfile,WriteByteSize);
	pType->SDTypeInfile.uName.Name=OldName;
	return WriteByteSize;
}
DWORD CSourceDebug::DumpSDFunctionTypeToFile(SDTYPE* pType)
{
	DWORD WriteByteSize; 
	char *OldName = pType->SDTypeInfile.uName.Name;
	pType->SDTypeInfile.uName.StringTableIndex=DumpSDTypeName(pType);
	WriteByteSize = pType->SDTypeInfile.Size-(sizeof(SDTYPE)-sizeof(SDTYPE_INFILE));
	gpFileIO->WriteFile(m_hFile,&pType->SDTypeInfile,WriteByteSize);
	pType->SDTypeInfile.uName.Name=OldName;
	return WriteByteSize;
}
DWORD CSourceDebug::DumpSDThunkTypeToFile(SDTYPE* pType)
{
	DWORD WriteByteSize;
	char *OldName = pType->SDTypeInfile.uName.Name;
	pType->SDTypeInfile.uName.StringTableIndex=DumpSDTypeName(pType);
	WriteByteSize = pType->SDTypeInfile.Size-(sizeof(SDTYPE)-sizeof(SDTYPE_INFILE));
	gpFileIO->WriteFile(m_hFile,&pType->SDTypeInfile,WriteByteSize);
	pType->SDTypeInfile.uName.Name=OldName;
	return WriteByteSize;
}
DWORD CSourceDebug::DumpSDPointerTypeToFile(SDTYPE* pType)
{
	DWORD WriteByteSize;
	DWORD WriteLen =  sizeof(SDTYPE)+sizeof(SDPOINTERTYPE);
	char *OldName = pType->SDTypeInfile.uName.Name;
	char *name;
	SDPOINTERTYPE* pSdPointerType = (SDPOINTERTYPE*)&pType[1];
	unsigned int i;
	WriteByteSize = pType->SDTypeInfile.Size-(sizeof(SDTYPE)-sizeof(SDTYPE_INFILE));
	int len=TStrLen(pType->SDTypeInfile.uName.Name)-9;
	name = new char [TStrLen(pType->SDTypeInfile.uName.Name)+1+pSdPointerType->PointerDepth];
	TStrCpy(name,pType->SDTypeInfile.uName.Name);
	for(i =0; i<pSdPointerType->PointerDepth;i++ )
		name[len+i]='*';
	name[len+i]=0;
	pType->SDTypeInfile.uName.StringTableIndex=DumpSDTypeName(name);		
	gpFileIO->WriteFile(m_hFile,&pType->SDTypeInfile.Size,WriteByteSize);
	delete []name;
	pType->SDTypeInfile.uName.Name=OldName;
	return WriteByteSize;
}
DWORD CSourceDebug::DumpSDReferenceTypeToFile(SDTYPE* pType)
{
	DWORD WriteByteSize;
	char *OldName = pType->SDTypeInfile.uName.Name;
	WriteByteSize = pType->SDTypeInfile.Size-(sizeof(SDTYPE)-sizeof(SDTYPE_INFILE));
	pType->SDTypeInfile.uName.StringTableIndex=DumpSDTypeName(pType);
	gpFileIO->WriteFile(m_hFile,&pType->SDTypeInfile.Size,WriteByteSize);
	pType->SDTypeInfile.uName.Name=OldName;
	return WriteByteSize;	
}
DWORD CSourceDebug::DumpSDEnumTypeToFile(SDTYPE* pType)
{
	SDENUMERATIONTYPE* pEnumationType;
	DWORD WriteByteSize;
	char *OldName = pType->SDTypeInfile.uName.Name;
	char *TmpPointer;
	SDTYPE_INFILE *pSubType;
	WriteByteSize = pType->SDTypeInfile.Size-(sizeof(SDTYPE)-sizeof(SDTYPE_INFILE));
	pType->SDTypeInfile.uName.StringTableIndex=DumpSDTypeName(pType);
	TmpPointer = new char [WriteByteSize];
	pSubType =(SDTYPE_INFILE*) TmpPointer;
	memcpy(pSubType,&pType->SDTypeInfile,WriteByteSize);
	pEnumationType = (SDENUMERATIONTYPE*)&pSubType[1];
	for(unsigned int i = 0; i < pEnumationType->DataCount; i++)	
		pEnumationType->EnumerationDataMember[i].u.MemberNameInStringTableIndex = DumpSDTypeName(pEnumationType->EnumerationDataMember[i].u.Name);
	gpFileIO->WriteFile(m_hFile,pSubType,WriteByteSize);
	delete []TmpPointer;
	pType->SDTypeInfile.uName.Name=OldName;
	return WriteByteSize;
}
DWORD CSourceDebug::DumpSDTypedefTypeToFile(SDTYPE* pType)
{	
	DWORD WriteByteSize;
	char *OldName = pType->SDTypeInfile.uName.Name;
	WriteByteSize = pType->SDTypeInfile.Size-(sizeof(SDTYPE)-sizeof(SDTYPE_INFILE));
	pType->SDTypeInfile.uName.StringTableIndex=DumpSDTypeName(pType->SDTypeInfile.uName.Name);
	gpFileIO->WriteFile(m_hFile,&pType->SDTypeInfile,WriteByteSize);
	pType->SDTypeInfile.uName.Name=OldName;
	return WriteByteSize;
}
DWORD CSourceDebug::DumpSDFriendToFile(SDTYPE* pType)
{	
	DWORD WriteByteSize;
	char *OldName = pType->SDTypeInfile.uName.Name;
	WriteByteSize = pType->SDTypeInfile.Size-(sizeof(SDTYPE)-sizeof(SDTYPE_INFILE));
	pType->SDTypeInfile.uName.StringTableIndex=DumpSDTypeName(pType->SDTypeInfile.uName.Name);
	gpFileIO->WriteFile(m_hFile,&pType->SDTypeInfile,WriteByteSize);
	pType->SDTypeInfile.uName.Name=OldName;
	return WriteByteSize;
}
DWORD CSourceDebug::DumpSDFunctionToFile(PSDFUNCTIONITEM pFunctionItem)
{	
	DWORD WriteLen =sizeof(SDFUNCTIONITEM);
	PSDFUNCTIONITEM pFuncItem = new SDFUNCTIONITEM;
	PSDFUNCTIONITEM	pOldFuncItem;
	DWORD CurOffset = WriteLen;
	DWORD DataLen;
	DWORD BlockLen;
	*pFuncItem=*pFunctionItem;		
	DataLen = sizeof(DWORD)*pFuncItem->DataCounter;
	BlockLen = sizeof(DWORD)*pFuncItem->BlockCounter;
	pOldFuncItem=pFunctionItem;
	pFuncItem->pData.DataMemberOffset= pFuncItem->DataCounter ? CurOffset:0;
	CurOffset+=DataLen;
	pFuncItem->pBlock.BlockOffset =pFuncItem->BlockCounter ? CurOffset:0;
	CurOffset+=BlockLen;
	pFuncItem->uName.MemberNameInStringTableIndex=DumpSDTypeName(pFuncItem->uName.Name);	
	gpFileIO->WriteFile(m_hFile,pFuncItem,WriteLen);	
	if(pFuncItem->DataCounter)		
		gpFileIO->WriteFile(m_hFile,pOldFuncItem->pData.pDataMember,DataLen);
	if(pFuncItem->BlockCounter)		
		gpFileIO->WriteFile(m_hFile,pOldFuncItem->pBlock.pBlockTypeIdArray,BlockLen);
	if(pFuncItem->LabelCounter)
	{
		PSDLABELITEM pSDLabelArray = new SDLABELITEM[pFuncItem->LabelCounter];
		for(unsigned int i = 0; i < pFuncItem->LabelCounter; i++)
		{
			pSDLabelArray[i].uName.MemberNameInStringTableIndex=DumpSDTypeName(pFuncItem->pLabel.pLabelArray[i].uName.Name);
			pSDLabelArray[i].Rva=pFuncItem->pLabel.pLabelArray[i].Rva;
		}
		CurOffset+=sizeof(SDLABELITEM)*pFuncItem->LabelCounter;
		gpFileIO->WriteFile(m_hFile,pSDLabelArray,sizeof(SDLABELITEM)*pFuncItem->LabelCounter);
		delete []pSDLabelArray;
	}
	delete pFuncItem;
	return CurOffset;
}
DWORD CSourceDebug::DumpSDUDTTypeToFile(SDTYPE* pType)
{
	DWORD dwCurOffset=pType->SDTypeInfile.Size-(sizeof(SDTYPE)-sizeof(SDTYPE_INFILE));
	char* temp = new char[pType->SDTypeInfile.Size];
	SDTYPE * pCurType;
	SDUDTTYPE * pUdtType,*pOldUdtType;
	DWORD FuncIDLen=0;
	DWORD DataLen=0;	
	DWORD FriendLen=0;
	DWORD BaseClassLen=0;
	DWORD VTableLen=0;

	pCurType= (SDTYPE*)temp;
	memcpy(pCurType,pType,pType->SDTypeInfile.Size);
	pUdtType = (SDUDTTYPE*)&pCurType[1];
	pOldUdtType=(SDUDTTYPE*)&pType[1];	
	FuncIDLen=pUdtType->FunctionCounter*sizeof(DWORD);
	DataLen=pUdtType->DataCounter*sizeof(DWORD);
	FriendLen=pUdtType->FriendCounter*sizeof(DWORD);
	BaseClassLen=pUdtType->BaseClassCounter*sizeof(DWORD);
	VTableLen=pUdtType->VTableCount*sizeof(SDUDTVIRTUALTABLE);
	pCurType->SDTypeInfile.uName.StringTableIndex=DumpSDTypeName(pType);
	pUdtType->pData.DataMemberOffset=dwCurOffset;
	dwCurOffset+=DataLen;
	pUdtType->pFunction.FunctionMemberOffset=dwCurOffset;
	dwCurOffset+=FuncIDLen;
	pUdtType->pFriend.FriendMemberOffset=dwCurOffset;
	dwCurOffset+=FriendLen;
	pUdtType->pBaseClass.BaseClassMemberOffset=dwCurOffset;
	dwCurOffset+=BaseClassLen;	
	pUdtType->pVTable.VTableMemberOffset=dwCurOffset;
	dwCurOffset+=VTableLen;	
	gpFileIO->WriteFile(m_hFile,&pCurType->SDTypeInfile.Size,pType->SDTypeInfile.Size-(sizeof(SDTYPE)-sizeof(SDTYPE_INFILE)));
	if(pUdtType->DataCounter)
		gpFileIO->WriteFile(m_hFile,pOldUdtType->pData.pDataMember,DataLen);	
	if(pUdtType->FunctionCounter)
		gpFileIO->WriteFile(m_hFile,pOldUdtType->pFunction.pFunctionMember,FuncIDLen);	
	if(pUdtType->FriendCounter)
		gpFileIO->WriteFile(m_hFile,pOldUdtType->pFriend.pFriendMember,FriendLen);
	if(pUdtType->BaseClassCounter)
		gpFileIO->WriteFile(m_hFile,pOldUdtType->pBaseClass.pBaseClassMember,BaseClassLen);	
	if(pUdtType->VTableCount)
		gpFileIO->WriteFile(m_hFile,pOldUdtType->pVTable.pVTableMember,VTableLen);	
	delete []temp;
	return dwCurOffset;
}

DWORD CSourceDebug::DumpSDDataName(SDUDTDATAITEM* pUdtDataItem)
{
	return DumpSDTypeName(pUdtDataItem->uName.Name);
}
DWORD CSourceDebug::DumpSDTypeName(SDTYPE* pType)
{
	if(pType->SDTypeInfile.uName.Name==NULL||pType->SDTypeInfile.uName.Name[0]==0)
		return 0;
	return DumpSDTypeName(pType->SDTypeInfile.uName.Name);
}
DWORD CSourceDebug::DumpSDTypeName(char* Name)
{
	DWORD NameLen;
	if(Name==NULL||Name[0]==0)
		return 0;
	NameLen = TStrLen(Name);
	if(NameLen+m_StringTableOffset+1 >= m_CurrentStringTableMaxLen)
	{
		DUMPSTRINGTABLEBLOCK DumpStringTableBlock;
		DumpStringTableBlock.BlockBaseAddress = m_StringTable;
		DumpStringTableBlock.EndOffset = m_StringTableOffset;
		DumpStringTableBlock.BeginOffset=m_StringTableBlockBeginOffset;
		m_StringDumpBlockList.push_back(DumpStringTableBlock);
		int Len = STRINGTABLEDUMPBLOCKSIZE - m_StringTableOffset % STRINGTABLEDUMPBLOCKSIZE + STRINGTABLEDUMPBLOCKSIZE;
		m_StringTable = new char[Len];
		m_CurrentStringTableMaxLen+=STRINGTABLEDUMPBLOCKSIZE;
		m_StringTableBlockBeginOffset=m_StringTableOffset;
	}
	
	STRINGOFTABLE StringOfTable(Name);
	STRING_TO_ID_MAP::iterator FindIt=m_String2IDMap.find(StringOfTable);
	if(FindIt==m_String2IDMap.end())
	{
		TStrCpy(m_StringTable-m_StringTableBlockBeginOffset+m_StringTableOffset,Name);
		StringOfTable.String=m_StringTable-m_StringTableBlockBeginOffset+m_StringTableOffset;
		m_String2IDMap.insert(STRING_TO_ID_MAP::value_type(StringOfTable,m_StringIndex));
		m_StringIDVector.push_back(m_StringTableOffset);
		m_StringTableOffset=NameLen+1+m_StringTableOffset;
		m_StringIndex++;
	}
	else
		return FindIt->second;
	
	return m_StringIndex-1;
}

char *CSourceDebug::GetBaseTypeName1(DWORD BaseType,DWORD length)
{
	int count = sizeof(BaseTypeNameStructArray)/sizeof(BaseTypeNameStructArray[0]);
	int i;
	
	if(BaseType==btInt)
		BaseType=length*0x80;
	if(BaseType==btUInt)
		BaseType=length*0x800;
	if(BaseType==btFloat&&length==8)
		BaseType=0x8000;
	for(i = 0; i < count;i++)
		if(BaseType==BaseTypeNameStructArray[i].Type)
			return BaseTypeNameStructArray[i].Name;
	return NULL;
}
char *CSourceDebug::MakeFunctionTypeName(IDiaSymbol*Symbol)
{
	return NULL;
}


DWORD CSourceDebug::MakeSDType(IDiaSymbol* Symbol,DWORD* ReleaseFlags,SDTYPE** pTypeRetrun)
{
	DWORD SymTag;
	DWORD SelfReleaseFlags=1;
	DWORD dwRetSymbolID=NULLSYMBOLID;
	if(pTypeRetrun)
		*pTypeRetrun=NULL;
	if(ReleaseFlags)
		*ReleaseFlags=1;
	if(Symbol==NULL)
		return NULLSYMBOLID;

	if(FAILED(Symbol->get_symTag(&SymTag)))
	{
		CODE_ASSERT(0);
		return NULLSYMBOLID;
	}
	switch(SymTag) 
	{
	case SymTagUDT:		
		dwRetSymbolID = MakeSDUDTType(Symbol,&SelfReleaseFlags,pTypeRetrun);
		break;
	case SymTagEnum:
		dwRetSymbolID = MakeSDEnumType(Symbol,&SelfReleaseFlags,pTypeRetrun);
		break;
	case SymTagFunctionType:
		dwRetSymbolID = MakeSDFunctionType(Symbol,&SelfReleaseFlags,pTypeRetrun);
		break;
	case SymTagBaseClass:
		dwRetSymbolID = MakeSDBaseClassType(Symbol,&SelfReleaseFlags,pTypeRetrun);
		break;
	case SymTagPointerType:
		dwRetSymbolID = MakeSDPointerReferenceType(Symbol,&SelfReleaseFlags,pTypeRetrun);
		break;
	case SymTagArrayType:
		dwRetSymbolID = MakeSDArrayType(Symbol,&SelfReleaseFlags,pTypeRetrun);		
		break;
	case SymTagBaseType:
		dwRetSymbolID = MakeSDBaseType(Symbol,&SelfReleaseFlags,pTypeRetrun);
		break;
	case SymTagCustomType:		
		dwRetSymbolID = MakeSDCustomType(Symbol,&SelfReleaseFlags,pTypeRetrun);
		break;
	case SymTagManagedType:
		dwRetSymbolID = MakeSDManagedType(Symbol,&SelfReleaseFlags,pTypeRetrun);
		break;
	case SymTagTypedef:
		dwRetSymbolID = MakeSDTypeDefType(Symbol,&SelfReleaseFlags,pTypeRetrun);
		break;
	case SymTagFunction: 
		dwRetSymbolID = MakeSDFunction(Symbol,&SelfReleaseFlags,pTypeRetrun);
		break;
	case SymTagThunk:
		MakeSDThunk(Symbol,&SelfReleaseFlags,pTypeRetrun);
		break;
	case SymTagFriend:
		MakeSDFriend(Symbol,&SelfReleaseFlags,pTypeRetrun);
		break;
	case SymTagData:
		{			
			DWORD dwDataKind;
			if(SUCCEEDED(Symbol->get_dataKind(&dwDataKind)))
				if(dwDataKind==DataIsFileStatic||dwDataKind==DataIsGlobal)
					MakeSDDataTagType(Symbol,&SelfReleaseFlags,pTypeRetrun);
		}		
		break;
	/*
	case SymTagFunctionArgType:
		break;
	case SymTagCompiland:
		MakeSDCompiland(Symbol);
		break;
	case SymTagPublicSymbol:
		MakeSDPublicSymbol(Symbol,&SelfReleaseFlags,pTypeRetrun);
		break;
	
	case SymTagVTableShape:
		//dwRetSymbolID = MakeSDVTableShapType(Symbol,&SelfReleaseFlags,pTypeRetrun);
		break;
	case SymTagVTable:
		{
		}	
		break;
	*/
	default:
		break;
	}
	if(ReleaseFlags)
		*ReleaseFlags=SelfReleaseFlags;

	return dwRetSymbolID;
}
DWORD CSourceDebug::MakeSDEXE(IDiaSymbol* Symbol)
{
	BSTR Name=NULL;
	BSTR SymbolsFileName=NULL;
	DWORD TimeStamp=0;
	Symbol->get_name(&Name);
	m_PEFileName = new char [TStrLen(Name)+1];
	TStrCpy(m_PEFileName,Name);
	Symbol->get_timeStamp(&TimeStamp);
	Symbol->get_symbolsFileName(&SymbolsFileName);
	m_PDBFileName = new char[TStrLen(SymbolsFileName)+1];
	TStrCpy(m_PDBFileName,SymbolsFileName);
	LocalFree(Name);
	LocalFree(SymbolsFileName);
	return 0;
}
DWORD CSourceDebug::MakeSDVTable(IDiaSymbol* Symbol,DWORD* ReleaseFlags,SDTYPE** pTypeRetrun)
{
	IDiaSymbol* pSubsymbol=NULL,*pClassParent=NULL;
	DWORD SelfReleaseFlags=1;
	SDTYPE* pType;
	SDVTABLE* pSDVtable;
	DWORD dwSymTag=0;
	IDiaSymbol* NewType=NULL;
	DWORD NumbersEntriesVTable=0;
	if(ReleaseFlags)
		*ReleaseFlags=1;
	pType =(SDTYPE*) new char[sizeof(SDTYPE)+sizeof(SDVTABLE)];
	memset(pType,0,sizeof(SDTYPE)+sizeof(SDVTABLE));
	pType->SDTypeInfile.Size=sizeof(SDTYPE)+sizeof(SDVTABLE);
	pType->SDTypeInfile.Type=SD_VTABLE;
	pType->SDTypeInfile.Id=m_CurrentSymbolIndex;
	m_CurrentSymbolIndex++;
	m_IDToSymbolMap.insert(ID_TO_SYMBOL_MAP::value_type(pType->SDTypeInfile.Id,pType));
	SYMBOLLIST sl;
	sl.id=pType->SDTypeInfile.Id;
	sl.type=pType;
	//m_SymbolList.push_back(sl);	
	m_SymbolList.insert( SD_SYMBOL_MAP::value_type(sl,sl.id));

	pSDVtable = (SDVTABLE*)&pType[1];
	if(SUCCEEDED(Symbol->get_type(&pSubsymbol)))
	{
		if(SUCCEEDED(pSubsymbol->get_symTag(&dwSymTag)))
		{
			if(dwSymTag==SymTagPointerType)
			{
				if(SUCCEEDED(pSubsymbol->get_type(&NewType))||NewType)
				{
					if(SUCCEEDED(NewType->get_symTag(&dwSymTag)))
					{
						if(dwSymTag==SymTagVTableShape)
							NewType->get_count(&NumbersEntriesVTable);
					}
					NewType->Release();
				}
			}
		}
		pSubsymbol->Release();
	}
	pSDVtable->NumbersEntriesVTable=NumbersEntriesVTable;
	if(SUCCEEDED(Symbol->get_classParent(&pClassParent)))
		pSDVtable->TypeIdParentUDT = MakeSDType(pClassParent,&SelfReleaseFlags,pTypeRetrun);
	if(pTypeRetrun)
		*pTypeRetrun=pType;
	return pType->SDTypeInfile.Id;
}
bool CSourceDebug::ModifyVTableName(char *Name)
{
	int i = 0,j=0;
	bool bRet=false;
	char *pClass,*pStruct,*pSrcBegin,*pDestBegin,*pNewName;
	pStruct = TStrStr(Name,"struct ");
	pClass=TStrStr(Name,"class ");
	if(pStruct==NULL&&pClass==NULL)
		return true;
	
	pNewName = new char[TStrLen(Name)+1];
	pNewName[0]=0;
	pSrcBegin=Name;
	pDestBegin=pNewName;
	while(pClass)
	{
		TStrNCpy(pDestBegin,pSrcBegin,*(DWORD*)&pClass-*(DWORD*)&pSrcBegin);
		pDestBegin=&pDestBegin[pClass-pSrcBegin];
		pSrcBegin=&pClass[6];
		pClass = TStrStr(pSrcBegin,"class ");
		bRet=true;
	};
	if(bRet)
	{
		TStrCpy(pDestBegin,pSrcBegin);
		TStrCpy(Name,pNewName);
		pSrcBegin=Name;
		pDestBegin=pNewName;
		bRet=false;
	}
	while(pStruct = TStrStr(pSrcBegin,"struct "))
	{
		TStrNCpy(pDestBegin,pSrcBegin,*(DWORD*)&pStruct-*(DWORD*)&pSrcBegin);
		pDestBegin=&pDestBegin[pStruct-pSrcBegin];
		pSrcBegin=&pStruct[7];
		bRet=true;
	};
	if(bRet)
	{
		TStrCpy(pDestBegin,pSrcBegin);
		TStrCpy(Name,pNewName);
		pSrcBegin=Name;
		pDestBegin=pNewName;
		bRet=false;
	}
	delete []pNewName;
	return bRet;
}
DWORD CSourceDebug::MakeSDPublicSymbol(IDiaSymbol* Symbol,DWORD* ReleaseFlags,SDTYPE** pTypeRetrun)
{
	SDPUBLICSYMBOL SdPublicSymbol;
	DWORD Rav;
	bool bIsString=false;
	BOOL bRet;
	ULONGLONG Length;
	BSTR Name=NULL;
	int Len;

	memset(&SdPublicSymbol,0,sizeof(SDPUBLICSYMBOL));
	if(SUCCEEDED(Symbol->get_undecoratedName(&Name))&&Name)
	{
		Len = TStrLen(Name)+1;
		SdPublicSymbol.uName.Name=new char[Len];
		TStrCpy(SdPublicSymbol.uName.Name,Name);
		LocalFree(Name);
		
		if(TStrStr(SdPublicSymbol.uName.Name,"::`vftable'")!=0)
		{
			SdPublicSymbol.IsVftable=1;
			ModifyVTableName(SdPublicSymbol.uName.Name);
		}else
			if(TStrCmp(SdPublicSymbol.uName.Name,"`string'")==0)
			{
				SdPublicSymbol.IsString = 1;
			}
	}
	else
		return 0;
	bRet = FALSE;
	if(SUCCEEDED(Symbol->get_function(&bRet)))
		SdPublicSymbol.IsFunction = bRet?1:0;
	bRet = FALSE;
	if(SUCCEEDED(Symbol->get_managed(&bRet)))
		SdPublicSymbol.IsMangedCode = bRet?1:0;
	bRet = FALSE;
	if(SUCCEEDED(Symbol->get_code(&bRet)))
		SdPublicSymbol.IsInCode = bRet?1:0;
	bRet = FALSE;
	if(SUCCEEDED(Symbol->get_msil(&bRet)))
		SdPublicSymbol.IsMsil = bRet?1:0;
	if(SUCCEEDED(Symbol->get_relativeVirtualAddress(&Rav)))
		SdPublicSymbol.Rva=Rav;
	if(SUCCEEDED(Symbol->get_length(&Length)))
		SdPublicSymbol.Length=*(DWORD*)&Length;
	m_PublicSymbolList.insert(PUBLIC_SYMBOL_MAP::value_type(SdPublicSymbol,SdPublicSymbol.Rva));// push_back(SdPublicSymbol);
	if(SdPublicSymbol.IsVftable==1)
		m_VTablePublicSymbolList.insert(PUBLIC_SYMBOL_MAP::value_type(SdPublicSymbol,SdPublicSymbol.Rva));// push_back(SdPublicSymbol);
	return 0;
}
DWORD CSourceDebug::MakeSDFriend(IDiaSymbol* Symbol,DWORD* ReleaseFlags,SDTYPE** pTypeRetrun)
{
	BSTR Name=NULL;
	char* FriendName;
	PSDTYPE pType=NULL,pSubType=NULL;
	DWORD SelfReleaseFlags=1;
	IDiaSymbol* pUdtFriendType;
	PSDUDTFRIEND pUdtFriend;
	int Len;
	Len = sizeof(SDUDTFRIEND) + sizeof(SDTYPE);
	pType = (PSDTYPE)new char [Len];
	memset(pType,0,Len);
	Symbol->get_name(&Name);
	FriendName = new char[TStrLen(Name)+1];
	TStrCpy(FriendName,Name);
	LocalFree(Name);
	pUdtFriend = (PSDUDTFRIEND)&pType[1];
	pType->SDTypeInfile.Type=SD_FRIEND;
	pType->SDTypeInfile.Id=m_CurrentSymbolIndex;
	pType->SDTypeInfile.Size=Len;
	pType->SDTypeInfile.uName.Name=FriendName;
	m_CurrentSymbolIndex++;
	m_IDToSymbolMap.insert(ID_TO_SYMBOL_MAP::value_type(pType->SDTypeInfile.Id,pType));
	SYMBOLLIST sl;
	sl.id=pType->SDTypeInfile.Id;
	sl.type=pType;
	//m_SymbolList.push_back(sl);
	m_SymbolList.insert( SD_SYMBOL_MAP::value_type(sl,sl.id));
	
	pUdtFriendType=NULL;
	if(FAILED(Symbol->get_type(&pUdtFriendType))||pUdtFriendType==NULL)
		return NULLSYMBOLID;
	pUdtFriend->TypdeId = MakeSDType(pUdtFriendType,&SelfReleaseFlags,&pSubType);
	if(SelfReleaseFlags)
		pUdtFriendType->Release();
	if(pSubType)
		pUdtFriend->Type=pSubType->SDTypeInfile.Type;
	return pUdtFriend->TypdeId;
}
DWORD CSourceDebug::MakeSDThunk(IDiaSymbol* Symbol,DWORD* ReleaseFlags,SDTYPE** pTypeRetrun)
{
	BSTR Name=NULL;
	SDTYPE *pType;
	DWORD SelfReleaseFlags=1;
	DWORD Rav;
	DWORD Len;
	SDTHUNK * pThunk;
	ULONGLONG Length;
	if(pTypeRetrun)
		*pTypeRetrun=NULL;
	if(ReleaseFlags)
		*ReleaseFlags=SelfReleaseFlags;
	if(FAILED(Symbol->get_relativeVirtualAddress(&Rav)))
		return NULLSYMBOLID;
	map <DWORD,SDTYPE*> ::iterator FindIt = m_ThunkIDMap.find(Rav);
	if(FindIt!=m_ThunkIDMap.end())
	{
		pType=FindIt->second;
		if(pTypeRetrun)
			*pTypeRetrun = pType;
		return pType->SDTypeInfile.Id;
	}
	if(FAILED(Symbol->get_name(&Name))||Name==NULL)
		return NULLSYMBOLID;
	Len = sizeof(SDTHUNK)+sizeof(SDTYPE);//+TStrLen(Name)+1;
	pType=(SDTYPE*)new char[Len];
	memset(pType,0,Len);
	pThunk=(SDTHUNK*)&pType[1];
	pType->SDTypeInfile.uName.Name=new char[TStrLen(Name)+1];
	TStrCpy(pType->SDTypeInfile.uName.Name,Name);
	LocalFree(Name);
	pType->SDTypeInfile.Size=sizeof(SDTHUNK)+sizeof(SDTYPE);
	Symbol->get_length(&Length);
	Symbol->get_thunkOrdinal(&pThunk->thunkOrdinal);
	pType->SDTypeInfile.Id=m_CurrentSymbolIndex;
	m_CurrentSymbolIndex++;
	m_IDToSymbolMap.insert(ID_TO_SYMBOL_MAP::value_type(pType->SDTypeInfile.Id,pType));
	SYMBOLLIST sl;
	sl.id=pType->SDTypeInfile.Id;
	sl.type=pType;
	//m_SymbolList.push_back(sl);	
	m_SymbolList.insert( SD_SYMBOL_MAP::value_type(sl,sl.id));
	m_ThunkIDMap.insert(map<DWORD,SDTYPE*>::value_type(Rav,pType));
	pThunk->Rva=Rav;
	pType->SDTypeInfile.TypeSize=*(DWORD*)&Length;
	pType->SDTypeInfile.Type=SD_THUNK;
	return pType->SDTypeInfile.Id;
}
DWORD CSourceDebug::MakeSDVTableShapType(IDiaSymbol* Symbol,DWORD* ReleaseFlags,SDTYPE** pTypeRetrun)
{
	IDiaSymbol* pCurSymbol=NULL,*pLexicalParent=NULL;
	ULONG celt;
	DWORD SymTag;
	IDiaEnumSymbols* EnumSymbols=NULL;
	BSTR Name=NULL;
	ULONGLONG length;
	if(SUCCEEDED(Symbol->get_type(&pCurSymbol))&&pCurSymbol)
	{
		DWORD LocalReleaseFlags=1;
		MakeSDType(pCurSymbol,&LocalReleaseFlags);
		if(LocalReleaseFlags)
			pCurSymbol->Release();
	}
	if(Symbol->get_classParent(&pLexicalParent)==S_OK)
	{
		CODE_ASSERT(pLexicalParent->get_name(&Name));
	}
	if(SUCCEEDED(Symbol->findChildren(SymTagNull,NULL,nsNone,&EnumSymbols))&&EnumSymbols)
	{
		while(EnumSymbols->Next(1,&pCurSymbol,&celt)&&celt==1)
		{
			if(FAILED(pCurSymbol->get_symTag(&SymTag)))
				continue;
			if(FAILED(pCurSymbol->get_name(&Name)))
				continue;
			if(FAILED(pCurSymbol->get_length(&length)))
				continue;
			pCurSymbol->Release();
			pCurSymbol=NULL;
		}
	}
	return NULLSYMBOLID;
}
DWORD CSourceDebug::MakeSDCompiland(IDiaSymbol* Symbol)
{
	DWORD SourceIndex = 0;
	IDiaSourceFile* SourceFile=NULL;
	SDCOMPILAND *pCompiland=NULL;
	SDSOURCEFILE* pSDSourceFile=NULL;
	ULONG celt=0,celt1=0;
	BSTR Name=NULL;	
	LONG SourceFileCounter=0;
	static ULONGLONG lennumber=0;
	IDiaEnumSymbols * SymbolEnum=NULL;
	IDiaSymbol *curSymbol=NULL,*curSymbolType=NULL;
	IDiaEnumSourceFiles *EnumSourceFiles=NULL;
	IDiaEnumLineNumbers* EnumLineNumbers=NULL;	
	NAMEANDIDPAIR CompilandNamePair;
	DWORD MinRva=0xffffffff,MaxRva=0;
	int Len;
	if(Symbol==NULL)
		return false;
	if(FAILED(Symbol->get_name(&Name))||Name==NULL)
		return 0;
	if(FAILED(m_DiaSession->findFile(Symbol,NULL,nsNone,&EnumSourceFiles))||EnumSourceFiles==NULL)
	{
		LocalFree(Name);
		return 0;
	}
	EnumSourceFiles->get_Count(&SourceFileCounter);
	Len = sizeof(SDCOMPILAND);
	if(SourceFileCounter)
		Len+=(SourceFileCounter-1)*sizeof(SDSOURCEFILE);
	pCompiland=(SDCOMPILAND*)new char [Len];
	memset(pCompiland,0,Len);
	pCompiland->SourceFileCounter=SourceFileCounter;
	pSDSourceFile = (SDSOURCEFILE*)&pCompiland->SourceFile;
	pCompiland->uName.Name = new char[TStrLen(Name)+1];
	TStrCpy(pCompiland->uName.Name,Name);
	LocalFree(Name);
	CompilandNamePair.Name=pCompiland->uName.Name;
	CompilandNamePair.Id=m_CurrentCompilandIndex;
	ID_TO_COMPILAND_NAME_MAP::iterator FindIt = m_IdToCompilandMap.find(CompilandNamePair);
	if(FindIt!=m_IdToCompilandMap.end())
	{
		EnumSourceFiles->Release();
		delete pCompiland->uName.Name;
		delete pCompiland;
		return 0;
	}
	pCompiland->CompilandId=m_CurrentCompilandIndex;
	m_IdToCompilandMap.insert(ID_TO_COMPILAND_NAME_MAP::value_type(CompilandNamePair,pCompiland));
	m_CurrentCompilandIndex++;
	if(SourceFileCounter==0)
	{
		EnumSourceFiles->Release();
		return 0;
	}
	while(SUCCEEDED(EnumSourceFiles->Next(1,&SourceFile,&celt))&&celt==1)
	{			
		bool bInsert;
		BSTR fileName;
		DWORD debug;
		char* SourceFileName=NULL;
		NAMEANDIDPAIR SourceName2Id;
		DWORD UniqueId=0xffffffff;
		DWORD FileNameLen=0;
		fileName=NULL;
		
		if(SUCCEEDED(SourceFile->get_fileName(&fileName))&& fileName)
		{
			FileNameLen = TStrLen(fileName)+1;
			SourceFileName = new char[FileNameLen];
			TStrCpy(SourceFileName,fileName);			
			LocalFree(fileName);
		}
		else
			continue;
		SourceName2Id.Name=SourceFileName;
		SourceName2Id.Id=m_CurrentSourceFileIndex;
		ID_TO_SOURCE_FILE_NAME_MAP::iterator FindIt =m_IdToSourceFileNameMap.find(SourceName2Id);
		if(FindIt==m_IdToSourceFileNameMap.end())
		{
			UniqueId=m_CurrentSourceFileIndex;			
			bInsert=true;
		}
		else
		{
			UniqueId = FindIt->first.Id;
			delete []SourceFileName;			
			bInsert=false;
		}
		
		if(SUCCEEDED(m_DiaSession->findLines(Symbol,SourceFile,&EnumLineNumbers)))
		{
			LONG dwLineCounter=0;
			if(SUCCEEDED(EnumLineNumbers->get_Count(&dwLineCounter))&&dwLineCounter)
			{
				SDLINE SDLine;
				IDiaLineNumber* LineNumber=NULL;
				while(SUCCEEDED(EnumLineNumbers->Next(1,&LineNumber,&celt1))&&celt1==1)
				{
					DWORD RAV=0;
					DWORD lineNumber=0;
					if(FAILED(LineNumber->get_relativeVirtualAddress(&RAV)))
						continue;
					BOOL bStatement=FALSE;
					if(FAILED(LineNumber->get_statement(&bStatement)))
						continue;
					if(bStatement==FALSE)
						debug=1;
					if(MinRva>RAV)
						MinRva=RAV;
					if(MaxRva<RAV)
						MaxRva=RAV;
					if(FAILED(LineNumber->get_lineNumber(&lineNumber)))
						continue;
					DWORD Len;
					if(FAILED(LineNumber->get_length(&Len)))
						continue;
					
					SDLine.CompilandId=pCompiland->CompilandId;
					SDLine.Len=Len;
					SDLine.Rva=RAV;
					SDLine.Statement = bStatement ? 1 : 0;
					SDLine.LineNumber=lineNumber;
					SDLine.FileID=UniqueId;
					m_TotalLineNumber.push_back(SDLine);
					LineNumber->Release();LineNumber=NULL;
				}			
			}
			EnumLineNumbers->Release();
			pSDSourceFile[SourceIndex].LinesNumber=dwLineCounter;
		}
		pSDSourceFile[SourceIndex].FileID=UniqueId;
		SourceFile->Release();
		SourceFile=NULL;		
		if(pSDSourceFile[SourceIndex].LinesNumber)
		{
			if(bInsert)
			{
				m_IdToSourceFileNameMap.insert(ID_TO_SOURCE_FILE_NAME_MAP::value_type(SourceName2Id,m_CurrentSourceFileIndex));			
				m_CurrentSourceFileIndex++;
			}
			SourceIndex++;
		}
		else
		{
			if(bInsert==true)
				delete []SourceFileName;
		}
	}
	if(SourceIndex!=pCompiland->SourceFileCounter)
		pCompiland->SourceFileCounter=SourceIndex;	
	pCompiland->MaxRva=MaxRva;
	pCompiland->MinRva=MinRva;
	EnumSourceFiles->Release();
	return true;
}
int funcsamecount=0;
DWORD CSourceDebug::MakeSDFunctionType(IDiaSymbol* Symbol,DWORD* ReleaseFlags,SDTYPE** pTypeRetrun)
{
	static int gFunctionCounter=0;
	SDTYPE *pType;
	SDFUNCTIONTYPE* ft;
	DWORD *TypeIDArgs=NULL;
	DWORD CallingConvention;
	DWORD len;
	IDiaSymbol * FunctionType;
	IDiaEnumSymbols* argTypesEnum;
	char *temppointer=NULL;
	LONG argcount = 0;
	int i =0;
	IDiaSymbol* diaCurArg;
	SD_SYMBOL_LIST::iterator beginIT,endIT;
/*	
	for(beginIT=m_FuncSymbolList.begin();beginIT!=m_FuncSymbolList.end();beginIT++)
	{
		HRESULT hr;
		IDiaSymbol* OldSymbol;
		OldSymbol=(IDiaSymbol*)beginIT->type->Symbol;
		hr = m_DiaSession->symsAreEquiv(Symbol,OldSymbol);
		if(hr==S_OK)	
		{
			if(ReleaseFlags)
				*ReleaseFlags=1;
			funcsamecount++;
			return beginIT->type->SDTypeInfile.Id;
		}
	}
//*/
	if(ReleaseFlags)
		*ReleaseFlags=0;
	if (FAILED(Symbol->findChildren(SymTagFunctionArgType, NULL, nsNone, &argTypesEnum)))   
		return NULLSYMBOLID;
	if (FAILED(argTypesEnum->get_Count(&argcount)))
		return NULLSYMBOLID;
	len = sizeof(SDFUNCTIONTYPE)+sizeof(SDTYPE);
	if(argcount)	
		len=len + sizeof(DWORD)*(argcount-1);
	pType = (SDTYPE*)new char[len];
	memset(pType,0,len);
	ft =(SDFUNCTIONTYPE*) &pType[1];
	pType->Self=ft;
	pType->SDTypeInfile.Size=len;
	pType->SDTypeInfile.Id=m_CurrentSymbolIndex;
	m_CurrentSymbolIndex++;
	SYMBOLLIST sl;
	sl.id=pType->SDTypeInfile.Id;
	sl.type=pType;
	pType->Symbol=Symbol;
	//m_SymbolList.push_back(sl);
	m_SymbolList.insert( SD_SYMBOL_MAP::value_type(sl,sl.id));
	m_FuncSymbolList.push_back(sl);
	m_IDToSymbolMap.insert(ID_TO_SYMBOL_MAP::value_type(pType->SDTypeInfile.Id,pType));
	
	if(FAILED(Symbol->get_type(&FunctionType))||FunctionType==NULL)	
		return NULLSYMBOLID;
	// Enumerate over them
	
	DWORD LocalReleaseFlags=1;
	ft->TypeIDReturnValue=MakeSDType(FunctionType,&LocalReleaseFlags);
	if(LocalReleaseFlags)
		FunctionType->Release();
	FunctionType=NULL;
	if(FAILED(Symbol->get_objectPointerType(&FunctionType)))
		return NULLSYMBOLID;
	if(FunctionType)
	{
		LocalReleaseFlags=1;
		ft->TypeIDThisPointer=MakeSDType(FunctionType,&LocalReleaseFlags);
		if(LocalReleaseFlags)
		{
			FunctionType->Release();
			FunctionType=NULL;
		}
		LONG ThisAdjust;
		Symbol->get_thisAdjust(&ThisAdjust);
		ft->ThisAdjust=ThisAdjust;
	}
	if(FAILED(Symbol->get_callingConvention(&CallingConvention)))
		return NULLSYMBOLID;
	ft->CallingConvention=CallingConvention;
	ft->ArgsCount=argcount;
	ULONG count=argcount;
	i=0;
	while(SUCCEEDED(argTypesEnum->Next(1, &diaCurArg, &count))&&count==1)
	{
		IDiaSymbol* curArgType;
		if (FAILED(diaCurArg->get_type(&curArgType)))
			return NULLSYMBOLID;
		DWORD LocalReleaseFlags=1;
		ft->TypeIDArgs[i]= MakeSDType(curArgType,&LocalReleaseFlags);
		if(LocalReleaseFlags)
		{
			curArgType->Release();
			curArgType=NULL;
		}
		diaCurArg->Release();
		diaCurArg=NULL;
		i++;
	}
	argTypesEnum->Release();
	pType->SDTypeInfile.Type =SD_FUNCTIONTYPE;
	pType->SDTypeInfile.uName.Name=NULL;
	pType->Symbol=Symbol;
	gFunctionCounter++;
	return pType->SDTypeInfile.Id;
}


DWORD CSourceDebug::MakeSDUDTType(IDiaSymbol* Symbol,DWORD* ReleaseFlags,SDTYPE** pTypeRetrun)
{
	DWORD SelfReleaseFlags=1,dwSymTag,udtkind;
	IDiaEnumSymbols *EnumSymbols;
	IDiaSymbol* pCurSymbol;
	BSTR ClassName=NULL;
	char* name=NULL;
	char *name1=NULL;
	bool bUnnamed=false;
	SDTYPE *pType;
	ULONGLONG length=0;
	LONG count;
	ULONG celt;
	SDCLASSTYPE *ct;
	
	if(ReleaseFlags)
		*ReleaseFlags=1;
	if(pTypeRetrun)
		*pTypeRetrun=NULL;
	if(FAILED(Symbol->get_name(&ClassName)))
		return NULLSYMBOLID;

	name = new char[TStrLen(ClassName)+1];
	TStrCpy(name,ClassName);
	CTempSymbol	TempSymbol(name,0,0);
	if(IsUnnamedSDType(name))
	{
		name1 = new char[TStrLen(ClassName)+10];
		TStrCpy(name1,name);
		TSPrintf(name1+TStrLen(name),"_%08x",m_CurrentSymbolIndex);
		SD_SYMBOL_LIST::iterator beginIT,endIT;
		endIT = m_UnnamedUdtList.end();
		for(beginIT=m_UnnamedUdtList.begin();beginIT!=endIT;beginIT++)
		{
			HRESULT hr;
			IDiaSymbol* OldSymbol;
			OldSymbol=(IDiaSymbol*)beginIT->type->Symbol;
			hr = m_DiaSession->symsAreEquiv(Symbol,OldSymbol);
			if(hr==S_OK)	
			{
				if(pTypeRetrun)
					*pTypeRetrun=beginIT->type;
				delete name1;
				delete name;
				return beginIT->type->SDTypeInfile.Id;
			}
		}
		delete []name;
		name = name1;
		bUnnamed=true;
	}
	else
	{
		m_TempSymbolIDIter = m_UDTSymbolID.find(TempSymbol);
		if(m_TempSymbolIDIter!=m_UDTSymbolID.end())
		{				
			if(pTypeRetrun)
				*pTypeRetrun=GetSDTypeBySymbolID(m_TempSymbolIDIter->second);
			delete []name;
			return (*m_TempSymbolIDIter).second;
		}
	}
	if(FAILED(Symbol->get_udtKind(&udtkind)))
		return NULLSYMBOLID;
	if(FAILED(Symbol->get_length(&length)))
		return NULLSYMBOLID;	
	if(FAILED(Symbol->get_symTag(&dwSymTag)))
		return NULLSYMBOLID;
	int NewSize =sizeof(SDTYPE)+sizeof(SDCLASSTYPE);
	pType = (SDTYPE*)new char[NewSize];
	memset(pType,0,sizeof(SDTYPE));	
	pType->SDTypeInfile.uName.Name = name;
	LocalFree(ClassName);

	switch(udtkind) 
	{
	case UdtClass:
		pType->SDTypeInfile.Type=SD_CLASS;
		break;
	case UdtStruct:
		pType->SDTypeInfile.Type=SD_STRUCT;
		break;
	case UdtUnion:
		pType->SDTypeInfile.Type=SD_UNION;
	}
	pType->SDTypeInfile.TypeSize=*(DWORD*)&length;
	
	ct =(SDCLASSTYPE*)&pType[1];
	memset(ct,0,sizeof(SDCLASSTYPE));
	//ct->IsUnnamed=bUnnamed?1:0;
	pType->SDTypeInfile.Id=m_CurrentSymbolIndex;
	m_CurrentSymbolIndex++;
	pType->Self=ct;
	pType->SDTypeInfile.Size=NewSize;
	SYMBOLLIST sl;
	sl.id=pType->SDTypeInfile.Id;
	sl.type=pType;

	if(bUnnamed)
	{
		m_UnnamedUdtList.push_back(sl);
		ct->IsUnnamed=1;
		pType->Symbol=Symbol;
		if(ReleaseFlags)
			*ReleaseFlags=0;
	}

	//m_SymbolList.push_back(sl);
	m_SymbolList.insert( SD_SYMBOL_MAP::value_type(sl,sl.id));
	TempSymbol.SetSDType(pType,name);
	
	m_UDTSymbolID.insert(SYMBOL_ID_MAP::value_type(TempSymbol,pType->SDTypeInfile.Id));
	m_IDToSymbolMap.insert(ID_TO_SYMBOL_MAP::value_type(pType->SDTypeInfile.Id,pType));
	BOOL bValue=FALSE;
	if(SUCCEEDED(Symbol->get_scoped(&bValue)))	
		ct->IsScoped=bValue?1:0;
	bValue=FALSE;
	if(SUCCEEDED(Symbol->get_nested(&bValue)))	
		ct->IsNested=bValue?1:0;
	bValue=FALSE;
	if(SUCCEEDED(Symbol->get_packed(&bValue)))	
		ct->IsPacked=bValue?1:0;
	bValue=FALSE;
	if(SUCCEEDED(Symbol->get_overloadedOperator(&bValue)))	
		ct->HasOverloadedOperator=bValue?1:0;
	bValue=FALSE;
	if(SUCCEEDED(Symbol->get_hasAssignmentOperator(&bValue)))	
		ct->HasAssignmentOperator=bValue?1:0;
	bValue=FALSE;
	if(SUCCEEDED(Symbol->get_hasCastOperator(&bValue)))	
		ct->HasCastOperator=bValue?1:0;
	bValue=FALSE;
	if(SUCCEEDED(Symbol->get_hasNestedTypes(&bValue)))	
		ct->HasNestedTypes=bValue?1:0;
	bValue=FALSE;
	if(SUCCEEDED(Symbol->get_constructor(&bValue)))	
		ct->IsConstructor=bValue?1:0;
	
	EnumSymbols=NULL;
	
	/*
	if(FAILED(Symbol->findChildren(SymTagVTable,NULL,nsNone,&EnumSymbols))||EnumSymbols==NULL)
		return NULLSYMBOLID;
	LONG VTableCount=0;
	if(SUCCEEDED(EnumSymbols->get_Count(&VTableCount)))
		if(VTableCount>1)
			CODE_ASSERT(0);
	pCurSymbol=NULL;
	while(SUCCEEDED(EnumSymbols->Next(1,&pCurSymbol,&celt))&&celt==1&&pCurSymbol)
	{
		DWORD VTableSize=0;
		IDiaSymbol *pVTableShape=NULL;
		if(SUCCEEDED(pCurSymbol->get_type(&pVTableShape)&&pVTableShape))
		{
			char *vtablename;
			if(SUCCEEDED(pVTableShape->get_count(&VTableSize)))
			{
				if(VTableSize)
					ct->VTableSize=VTableSize;
			}


			PUBLIC_SYMBOL_LIST::iterator BeginIt,EndIt;
			BeginIt=m_VTablePublicSymbolList.begin();
			EndIt=m_VTablePublicSymbolList.end();
			for(;BeginIt!=EndIt;BeginIt++)
			{
				vtablename=(*BeginIt).uName.Name;
				char*vtablename1 = TStrStr(vtablename,pType->SDTypeInfile.uName.Name);
				if(vtablename1)
				{
					if(TStrNCmp(&vtablename1[TStrLen(pType->SDTypeInfile.uName.Name)],"::`vftable'",TStrLen("::`vftable'"))==0)
					{
						ct->VTableRVA=(*BeginIt).Rva;
						ct->VTableSize=(*BeginIt).Length;
					}
				}	
			}
			
			if(ct->VTableRVA==0)
				ct->VTableRVA=0xffffffff;
			pVTableShape->Release();
		}
		pCurSymbol->Release();
	}
	EnumSymbols->Release();
	EnumSymbols=NULL;
	*/
	
	if(FAILED(Symbol->findChildren(SymTagBaseClass,NULL,nsNone,&EnumSymbols))||EnumSymbols==NULL)
		return NULLSYMBOLID;
	if(SUCCEEDED(EnumSymbols->get_Count(&count))&&count!=0)
	{
		DWORD *BaseClassTypeID = new DWORD[count];
		int i = 0;
		pCurSymbol=NULL;
		//static BaseClassCountttt=0;
		while(SUCCEEDED(EnumSymbols->Next(1,&pCurSymbol,&celt))&&celt==1&&pCurSymbol)
		{
			DWORD id;
			DWORD LocalReleaseFlags=1;
			id = MakeSDType(pCurSymbol,&LocalReleaseFlags);
			if(id==NULLSYMBOLID)
			{
				BaseClassTypeID[i]=NULLSYMBOLID;
			}
			else
			{
				BaseClassTypeID[i]=id;
				SDTYPE *pSubType = GetSDTypeBySymbolID(id);
				SDUDTBASECLASS* pSubBaseClass = (SDUDTBASECLASS*)pSubType->Self;
				pSubBaseClass->TypeIDParent=pType->SDTypeInfile.Id;
			}
			if(LocalReleaseFlags)
			{
				pCurSymbol->Release();
				pCurSymbol=NULL;
			}
			i++;
		}
		//BaseClassCountttt++;
		//OutputDebugStr(pType->SDTypeInfile.uName.Name);
		//OutputDebugStr("\n");
		ct->pBaseClass.pBaseClassMember=BaseClassTypeID;
		ct->BaseClassCounter=count;	
	}
	else
	{
		ct->BaseClassCounter=0;
		ct->pBaseClass.pBaseClassMember=NULL;		
	}
	EnumSymbols->Release();
	char *vtablename;
	PUBLIC_SYMBOL_MAP::iterator BeginIt,EndIt;
	PSDUDTVIRTUALTABLE pUdtVTable=new SDUDTVIRTUALTABLE[(ct->BaseClassCounter>1)?ct->BaseClassCounter:1];
	memset(pUdtVTable,0, sizeof(SDUDTVIRTUALTABLE)*(ct->BaseClassCounter>1)?ct->BaseClassCounter:1);// pType->SDTypeInfile.Id,0,)
	BeginIt=m_VTablePublicSymbolList.begin();
	int VTableIndex=0;
	EndIt=m_VTablePublicSymbolList.end();
	for(;BeginIt!=EndIt;BeginIt++)
	{
		vtablename=(*BeginIt).first.uName.Name;
		char* vtablename1 = TStrStr(vtablename,pType->SDTypeInfile.uName.Name);
		char* bcbegin,*bcend;
		if(vtablename1)
		{
			if(TStrNCmp(&vtablename1[TStrLen(pType->SDTypeInfile.uName.Name)],"::`vftable'",11)==0)
			{
				//ct->VTableRVA=(*BeginIt).first.Rva;
				//ct->VTableSize=(*BeginIt).first.Length;
				ct->HasVirtualTable=1;
				pUdtVTable[VTableIndex].VTableSize=(*BeginIt).first.Length;
				pUdtVTable[VTableIndex].VTableRVA=(*BeginIt).first.Rva;
				if(ct->BaseClassCounter>1)
				{
					bcbegin = TStrStr(vtablename,"::`vftable'{for `");
					if(bcbegin)
					{
						bcbegin=bcbegin+17;
						bcend = TStrChr(bcbegin,'\'');
						for(DWORD kk=0;kk<ct->BaseClassCounter;kk++)
						{
							SDTYPE *pSubbcType = GetSDTypeBySymbolID(ct->pBaseClass.pBaseClassMember[kk]);
							SDUDTBASECLASS* pSubbc = (SDUDTBASECLASS*)pSubbcType->Self;
							pSubbcType = GetSDTypeBySymbolID(pSubbc->TypeID);
							
							if(TStrNCmp(pSubbcType->SDTypeInfile.uName.Name,bcbegin, *(int*)&bcend - *(int*)&bcbegin)==0)
							{
								pUdtVTable[VTableIndex].VTBaseClassTypeID=pSubbc->TypeID;
							}
						}												
					}
					
					//find baseclassindex
				}
				else
					pUdtVTable[VTableIndex].VTBaseClassTypeID= pType->SDTypeInfile.Id;
				VTableIndex++;				
				//m_VTablePublicSymbolList.erase(BeginIt);
				break;
			}
		}	
	}
	ct->VTableCount=VTableIndex;
	if(VTableIndex)
	{
		ct->VTableCount=VTableIndex;
		ct->pVTable.pVTableMember=pUdtVTable;
	}
	else
	{
		ct->VTableCount=0;
		ct->pVTable.pVTableMember=NULL;
		delete []pUdtVTable;
	}
	EnumSymbols=NULL;
	if(FAILED(Symbol->findChildren(SymTagFunction,NULL,nsNone,&EnumSymbols))||EnumSymbols==NULL)
		return NULLSYMBOLID;
	count=0;
	if(SUCCEEDED(EnumSymbols->get_Count(&count))&&count!=0)
	{		
		DWORD *pFunctionData = new DWORD[count];
		int i = 0;
		pCurSymbol=NULL;
		while(SUCCEEDED(EnumSymbols->Next(1,&pCurSymbol,&celt))&&celt==1&&pCurSymbol)
		{
			SDTYPE* pLocalTypeReturn=NULL;
			DWORD LocalReleaseFlags=1;
			pFunctionData[i]=MakeSDFunction(pCurSymbol,&LocalReleaseFlags,&pLocalTypeReturn);
			if(LocalReleaseFlags)
			{
				pCurSymbol->Release();
				pCurSymbol=NULL;
			}
			if(pFunctionData[i]==0)
				continue;
			((PSDFUNCTIONITEM)pLocalTypeReturn)->TypeIDParentUDT=pType->SDTypeInfile.Id;
			i++;
		}		
		if(i>1)
		{
			sort(pFunctionData,&pFunctionData[i]);
			unique(pFunctionData,&pFunctionData[i]);
			count=i;
			for(i = 0; i < count-1;i++)
				if(pFunctionData[i]>=pFunctionData[i+1])
					break;
			i++;
		}
		ct->FunctionCounter=i;
		ct->pFunction.pFunctionMember=pFunctionData;
	}
	else
	{	ct->pFunction.pFunctionMember=NULL;
		ct->FunctionCounter=0;
	}
	EnumSymbols->Release();
	EnumSymbols=NULL;
	if(FAILED(Symbol->findChildren(SymTagData,NULL,nsNone,&EnumSymbols))||EnumSymbols==NULL)
		return NULL;
	count=0;
	if(SUCCEEDED(EnumSymbols->get_Count(&count))&&count!=0)
	{
		ct->DataCounter=count;		
		ct->pData.pDataMember = new DWORD[count];
		memset(ct->pData.pDataMember,0,sizeof(DWORD)*count);
		int i =0;
		pCurSymbol=NULL;
		while(SUCCEEDED(EnumSymbols->Next(1,&pCurSymbol,&celt))&&celt==1&&pCurSymbol)
		{
			SDUDTDATAITEM* pUdtDataItem;
			SDTYPE* pReturnType;
			ct->pData.pDataMember[i]=MakeSDDataTagType(pCurSymbol,NULL,&pReturnType);
			if(pReturnType)
			{
				pUdtDataItem = (SDUDTDATAITEM*)pReturnType;
				if(pUdtDataItem)
				{	
					pUdtDataItem->TypeIdParentUDT=pType->SDTypeInfile.Id;
					PSDTYPE pUdtDataType = GetSDTypeBySymbolID(pUdtDataItem->TypeId);
					if(pUdtDataType->SDTypeInfile.Type==SD_CLASS||pUdtDataType->SDTypeInfile.Type==SD_STRUCT||pUdtDataType->SDTypeInfile.Type==SD_UNION)
					{
						PSDCLASSTYPE pSubCt=(PSDCLASSTYPE)&pUdtDataType[1];
						if(pSubCt&&pSubCt->IsUnnamed)
							pSubCt->IsNestedUnnamed=1;
					}
				}
			}
			pCurSymbol->Release();
			pCurSymbol=NULL;
			i++;
		}		
	}
	else
	{
		ct->DataCounter=0;
		ct->pData.pDataMember=NULL;
	}
	EnumSymbols->Release();
	EnumSymbols=NULL;
	
	if(FAILED(Symbol->findChildren(SymTagFriend,NULL,nsNone,&EnumSymbols))||EnumSymbols==NULL)
		return NULL;
	count=0;
	if(SUCCEEDED(EnumSymbols->get_Count(&count))&&count!=0)
	{
		DWORD* pFriendData=new DWORD[count];
		memset(pFriendData,0,sizeof(DWORD)*count);
		int i =0;
		pCurSymbol=NULL;
		while(SUCCEEDED(EnumSymbols->Next(1,&pCurSymbol,&celt))&&celt==1&&pCurSymbol)
		{
			SDTYPE* pLocalTypeReturn=NULL;
			DWORD LocalReleaseFlags=1;
			ct->pFriend.pFriendMember[i]=MakeSDFunction(pCurSymbol,&LocalReleaseFlags,&pLocalTypeReturn);
			if(LocalReleaseFlags)
			{
				pCurSymbol->Release();
				pCurSymbol=NULL;
			}
			if(ct->pFriend.pFriendMember[i]==0)
				continue;
			i++;
		}		
		if(i>1)
		{
			sort(pFriendData,&pFriendData[i]);
			unique(pFriendData,&pFriendData[i]);
			count=i;
			for(i = 0; i < count-1;i++)
				if(pFriendData[i]>=pFriendData[i+1])
					break;
			i++;
		}
		ct->FriendCounter=count;		
		ct->pFriend.pFriendMember=pFriendData;	
	}
	else
	{
		ct->FriendCounter=0;
		ct->pFriend.pFriendMember=NULL;
	}
	EnumSymbols->Release();
	EnumSymbols=NULL;
	/*
	if(FAILED(Symbol->findChildren(SymTagUDT,NULL,nsNone,&EnumSymbols))||EnumSymbols==NULL)
		return NULL;
	count=0;
	if(SUCCEEDED(EnumSymbols->get_Count(&count))&&count!=0)
	{		
		while(SUCCEEDED(EnumSymbols->Next(1,&pCurSymbol,&celt))&&celt==1&&pCurSymbol)
		{
			SDTYPE* pReturnType=NULL;
			DWORD LocalReleaseFlags1=1;
			MakeSDType(pCurSymbol,&LocalReleaseFlags1,&pReturnType);
			if(pReturnType)
			{
				PSDCLASSTYPE pUDT = (PSDCLASSTYPE)pReturnType->Self;
				pUDT->TypeIdParentUDT=pType->SDTypeInfile.Id;				
			}
			if(LocalReleaseFlags1)
				pCurSymbol->Release();
		}		
	}

	IDiaSymbol*ParentUDTType=NULL;
	if(SUCCEEDED(Symbol->get_lexicalParent(&ParentUDTType))&&ParentUDTType)
	{
		DWORD LocalReleaseFlags1=1;
		ct->TypeIdParentUDT=MakeSDType(ParentUDTType,&LocalReleaseFlags1);
		if(ct->TypeIdParentUDT)
			ct->TypeIdParentUDT=0;
		if(LocalReleaseFlags1)
			ParentUDTType->Release();
	}
	*/
	if(pTypeRetrun)
		*pTypeRetrun=pType;
	return pType->SDTypeInfile.Id;
}
bool CSourceDebug::SetUDTDataItem(SDUDTDATAITEM* pUdtDataItem,IDiaSymbol* Symbol)
{
	LONG offset;	
	switch(pUdtDataItem->Location) 
	{
		case LocIsNull:
			break;
		case LocIsStatic:
			Symbol->get_relativeVirtualAddress(&pUdtDataItem->u.LOCISSTATIC.Rva);
			break;
		case LocIsTLS:
			Symbol->get_addressSection(&pUdtDataItem->u.LOCISTLS.AddressSection);
			Symbol->get_addressOffset(&pUdtDataItem->u.LOCISTLS.AddressOffset);
			break;
		case LocIsRegRel:
			Symbol->get_registerId(&pUdtDataItem->u.LOCISREGREL.Register);
			Symbol->get_offset(&offset);
			pUdtDataItem->u.LOCISREGREL.Offset=offset;
			break;
		case LocIsThisRel:
			Symbol->get_offset(&offset);
			pUdtDataItem->u.LOCISTHISREL.Offset=offset;				
			break;
		case LocIsEnregistered:
			//////////////////////////////////////////////////////////////////////////
			//      LocIsEnregistered类型的变量get_registerId 方法返回的积存器号和
			//      他定义的积存器号种是大1  ，所以这里要减掉 1
			//
			//////////////////////////////////////////////////////////////////////////
			Symbol->get_registerId(&pUdtDataItem->u.LOCISENREGISTERED.Register);
			pUdtDataItem->u.LOCISENREGISTERED.Register=pUdtDataItem->u.LOCISENREGISTERED.Register-1;
			break;
		case LocIsBitField:
			{
				ULONGLONG val=0;
				Symbol->get_bitPosition(&pUdtDataItem->u.LOCISBITFIELD.Position);
				Symbol->get_length(&val);
				Symbol->get_offset(&offset);				
				pUdtDataItem->u.LOCISBITFIELD.Size=*(DWORD*)&val;
				pUdtDataItem->u.LOCISBITFIELD.Offset=*(DWORD*)&offset;
			}
			break;
		case LocIsSlot:
			Symbol->get_slot(&pUdtDataItem->u.LOCISLOT.Slot);
			break;
		case LocIsIlRel:
			Symbol->get_offset(&offset);
			pUdtDataItem->u.LOCISLREL.Offset=offset;
			break;
		case LocInMetaData:
			Symbol->get_token(&pUdtDataItem->u.LOCINMETADATA.Token);
			break;
		case LocIsConstant:
			{	
				LONGLONG valueL=0;
				VARIANT value;

				memset(&value,0,sizeof(VARIANT));
				Symbol->get_value(&value);
				switch(value.vt) 
				{
					case VT_UI1: valueL = value.bVal; break;
					case VT_UI2: valueL = value.uiVal; break;
					case VT_UI4: valueL = value.ulVal; break;
					case VT_UINT: valueL = value.uintVal; break;
					case VT_UI8:valueL=value.ullVal; break;
					case VT_INT: valueL = value.intVal; break;
					case VT_I1: valueL = value.cVal; break;
					case VT_I2: valueL = value.iVal; break;
					case VT_I4: valueL = value.lVal; break;
					case VT_I8: valueL = value.llVal; break;
					case VT_ERROR:valueL=0;break;
					default:	
						CODE_ASSERT(0);
						break;
				}
				pUdtDataItem->u.LOCISCONSTSNT.llValue =valueL;
				/*
				SDCONSTVAR ConstVar;
				memset(&ConstVar,0,sizeof(SDCONSTVAR));
				ConstVar.Name=pUdtDataItem->uName.Name;
				ConstVar.u.llValue=valueL;
				CONST_VAR_MAP::iterator findit= m_ConstVarMap.find(ConstVar);
				if(findit!=m_ConstVarMap.end())
				{
					m_ConstVarMap.insert(CONST_VAR_MAP::value_type(ConstVar,0));
				}
				*/
				
			}
			break;
		case LocTypeMax:
			break;
		default:
			break;
	}	
	return true;
}

PREDEFINEBASETYPE gPreDefineBaseType[]=
{
	{1*0x80,1,"char"},
	{2*0x80,2,"short"},
	{4*0x80,4,"int"},
	{8*0x80,8,"__int64"},
	{1*0x800,1,"unsigned char"},
	{2*0x800,2,"unsigned short"},
	{4*0x800,4,"unsigned int"},
	{8*0x800,8,"unsigned __int64"},
	{btLong,4,"long"},
	{btULong,4,"unsigned long"},
};

void CSourceDebug::MakePredefineSDBaseType()
{
	SYMBOLBASETYPE LBaseTypeAttribut;
	SDTYPE* pType;
	SDBASETYPE *bt=NULL;
	char *name=NULL;
	int i;
	for(i = 0;i<sizeof(gPreDefineBaseType)/sizeof(gPreDefineBaseType[0]);i++)
	{
		LBaseTypeAttribut.baseType=gPreDefineBaseType[i].baseType;
		LBaseTypeAttribut.Length=gPreDefineBaseType[i].Length;
		pType = new SDTYPE;
		memset(pType,0,sizeof(SDTYPE));	
		pType->SDTypeInfile.uName.Name = new char[TStrLen(gPreDefineBaseType[i].Name)+1];
		TStrCpy(pType->SDTypeInfile.uName.Name,gPreDefineBaseType[i].Name);
		pType->SDTypeInfile.Size=sizeof(SDTYPE);
		pType->Self=NULL;
		pType->SDTypeInfile.Type=SD_BASIC;
		pType->SDTypeInfile.TypeSize=*(DWORD*)&LBaseTypeAttribut.Length;
		pType->SDTypeInfile.Id=m_CurrentSymbolIndex;
		m_CurrentSymbolIndex++;
		m_BaseTypeID.insert(BASE_TYPE_ID_MAP::value_type(LBaseTypeAttribut,pType->SDTypeInfile.Id));
		m_IDToSymbolMap.insert(ID_TO_SYMBOL_MAP::value_type(pType->SDTypeInfile.Id,pType));
		SYMBOLLIST sl;
		sl.id=pType->SDTypeInfile.Id;
		sl.type=pType;
		m_SymbolList.insert( SD_SYMBOL_MAP::value_type(sl,sl.id));
	}
}

DWORD CSourceDebug::MakeSDBaseType(IDiaSymbol* Symbol, DWORD *ReleaseFlags,SDTYPE** pTypeRetrun)
{
	SYMBOLBASETYPE LBaseTypeAttribut;
	SDTYPE* pType;
	SDBASETYPE *bt=NULL;
	char *name=NULL;

	pType = NULL;	
	if(ReleaseFlags)
		*ReleaseFlags=1;
	if(pTypeRetrun)
		*pTypeRetrun=NULL;
	LBaseTypeAttribut.baseType=0,LBaseTypeAttribut.Length=0;
	if(FAILED(Symbol->get_baseType(&LBaseTypeAttribut.baseType)))
		return NULLSYMBOLID;
	if(FAILED(Symbol->get_length(&LBaseTypeAttribut.Length)))
		return NULLSYMBOLID;
	name = GetBaseTypeName1(LBaseTypeAttribut.baseType,*(DWORD*)&LBaseTypeAttribut.Length);
	BASE_TYPE_ID_MAP::iterator TempMapIter;
	TempMapIter = m_BaseTypeID.find(LBaseTypeAttribut);
	if(TempMapIter!=m_BaseTypeID.end())
	{
		if(pTypeRetrun)
			*pTypeRetrun=GetSDTypeBySymbolID(TempMapIter->second);
		return TempMapIter->second;
	}

	pType = new SDTYPE;
	memset(pType,0,sizeof(SDTYPE));	
	pType->SDTypeInfile.uName.Name = new char[TStrLen(name)+1];
	TStrCpy(pType->SDTypeInfile.uName.Name,name);
	pType->SDTypeInfile.Size=sizeof(SDTYPE);
	pType->Self=NULL;
	pType->SDTypeInfile.Type=SD_BASIC;
	pType->SDTypeInfile.TypeSize=*(DWORD*)&LBaseTypeAttribut.Length;
	pType->SDTypeInfile.Id=m_CurrentSymbolIndex;
	m_CurrentSymbolIndex++;
	pType->Symbol=NULL;
	m_BaseTypeID.insert(BASE_TYPE_ID_MAP::value_type(LBaseTypeAttribut,pType->SDTypeInfile.Id));
	m_IDToSymbolMap.insert(ID_TO_SYMBOL_MAP::value_type(pType->SDTypeInfile.Id,pType));
	SYMBOLLIST sl;
	sl.id=pType->SDTypeInfile.Id;
	sl.type=pType;
	m_SymbolList.insert( SD_SYMBOL_MAP::value_type(sl,sl.id));
	if(pTypeRetrun)
		*pTypeRetrun=pType;		
	return pType->SDTypeInfile.Id;
}
DWORD CSourceDebug::MakeSDBaseClassType(IDiaSymbol* Symbol,DWORD* ReleaseFlags,SDTYPE** pTypeRetrun)
{
	DWORD SelfReleaseFlags=1;
	SDUDTBASECLASS *pUdtBaseClass;
	SDTYPE *pType;
	DWORD TypeLen;
	BSTR Name;
	IDiaSymbol* BaseClassType=NULL;
	if(ReleaseFlags)
		*ReleaseFlags=SelfReleaseFlags;
	SD_SYMBOL_LIST::iterator beginIT,endIT;
	for(beginIT=m_BaseClassList.begin();beginIT!=m_BaseClassList.end();beginIT++)
	{
		HRESULT hr;
		SDTYPE *pCurType,*pSubType;
		SDUDTBASECLASS*pUdtBaseClass;
		IDiaSymbol* OldSymbol;
		
		pCurType=beginIT->type;
		pUdtBaseClass = (SDUDTBASECLASS*)pCurType->Self;
		pSubType = GetSDTypeBySymbolID(pUdtBaseClass->TypeID);
		OldSymbol=(IDiaSymbol*)pCurType->Symbol;
		hr = m_DiaSession->symsAreEquiv(Symbol,OldSymbol);
		if(hr==S_OK)		
			return beginIT->type->SDTypeInfile.Id;
	}
	Name=NULL;
	if(FAILED(Symbol->get_name(&Name))||Name==NULL)
		return NULLSYMBOLID;
	TypeLen = sizeof(SDTYPE)+sizeof(SDUDTBASECLASS);
	pType =(SDTYPE*) new char[TypeLen];	
	pUdtBaseClass = (SDUDTBASECLASS*)&pType[1];
	memset(pType,0,TypeLen);
	pType->SDTypeInfile.Size=TypeLen;
	pType->SDTypeInfile.Type=SD_BASECLASS;
	pType->Symbol=Symbol;
	pType->SDTypeInfile.uName.Name = new char [TStrLen(Name)+1];
	TStrCpy(pType->SDTypeInfile.uName.Name,Name);
	pType->SDTypeInfile.Id=m_CurrentSymbolIndex;
	m_CurrentSymbolIndex++;
	pType->Self=pUdtBaseClass;
	SYMBOLLIST sl;
	sl.id=pType->SDTypeInfile.Id;
	sl.type=pType;
	//m_SymbolList.push_back(sl);
	m_SymbolList.insert( SD_SYMBOL_MAP::value_type(sl,sl.id));
	m_BaseClassList.push_back(sl);
	m_IDToSymbolMap.insert(ID_TO_SYMBOL_MAP::value_type(pType->SDTypeInfile.Id,pType));
	if(FAILED(Symbol->get_type(&BaseClassType))||BaseClassType==NULL)
		return NULLSYMBOLID;
	SDTYPE* pCurType=NULL;
	DWORD LocalReleaseFlags=1;
	pUdtBaseClass->TypeID=MakeSDType(BaseClassType,&LocalReleaseFlags,&pCurType);
	if(pCurType)
		pType->SDTypeInfile.TypeSize = pCurType->SDTypeInfile.TypeSize;
	if(LocalReleaseFlags)
		BaseClassType->Release();
	BOOL bVirtual=false;
	if(FAILED(Symbol->get_virtualBaseClass(&bVirtual)))
		return NULLSYMBOLID;
	pUdtBaseClass->bIsVirtual = bVirtual?true:false;
	bVirtual=false;
	if(FAILED(Symbol->get_indirectVirtualBaseClass(&bVirtual)))
		return NULLSYMBOLID;
	pUdtBaseClass->bIsIndirectBaseClass = bVirtual?true:false;
	LONG Off=0xffffffff;
	if(FAILED(Symbol->get_offset(&Off)))
		return NULLSYMBOLID;
	pUdtBaseClass->Offset=Off;
	DWORD DispIndex=0xffffffff;
	if(FAILED(Symbol->get_virtualBaseDispIndex(&DispIndex)))
		return NULLSYMBOLID;
	pUdtBaseClass->VirtualBaseDispIndex=DispIndex;
	if(FAILED(Symbol->get_virtualBasePointerOffset(&Off)))
		return NULLSYMBOLID;
	DWORD dwAccess=0xffffffff;
	if(FAILED(Symbol->get_access(&dwAccess)))
		return NULLSYMBOLID;
	pUdtBaseClass->Access=dwAccess;
	pUdtBaseClass->VirtualBasePointerOffset=Off;	
	SelfReleaseFlags=0;
	if(ReleaseFlags)
		*ReleaseFlags=SelfReleaseFlags;
	return pType->SDTypeInfile.Id;
}

DWORD CSourceDebug::MakeSDDataTagType(IDiaSymbol* Symbol,DWORD *ReleaseFlags,SDTYPE** pTypeRetrun) 
{
	BSTR TypeName=NULL;
	DWORD dwDataKind;
	SDUDTDATAITEM*pDataMember;
	IDiaSymbol *DataType;
	DWORD TypeLen;
	DWORD typeID;
	bool bThisObjectPtr=false;
	DWORD Local1ReleaseFlags;
	SDTYPE* pTypeReturn=NULL;
	LONG off=0;
	THISOBJECTPTR CurThis;
	DWORD Location;
	DWORD Access=0;
	BOOL bConstType=FALSE,bVolatileType=FALSE;;

	if(pTypeRetrun)
		*pTypeRetrun=NULL;
	if(FAILED(Symbol->get_dataKind(&dwDataKind)))
	{
		CODE_ASSERT(0);
		return NULLSYMBOLID;
	}
	
	if(FAILED(Symbol->get_name(&TypeName)))
	{
		CODE_ASSERT(0);
		return NULLSYMBOLID;
	}
	if(TStrICmp("PsLoadedmodulelist",TypeName)==0)
		Access=0;
	if(dwDataKind==DataIsStaticLocal)
	{
		if(TStrCmp(TypeName,"")==0)
		{
			LocalFree(TypeName);
			return NULLSYMBOLID;
		}
	}
	if(FAILED(Symbol->get_locationType(&Location)))	
	{
		CODE_ASSERT(0);
		return NULLSYMBOLID;
	}
	
	if(TStrCmp(TypeName,"this")==0&&Location==LocIsEnregistered)
	{
		CurThis.dataKind=dwDataKind;
		if(FAILED(Symbol->get_registerId(&CurThis.Register)))
		{
			CODE_ASSERT(0);
			return NULLSYMBOLID;
		}
		//////////////////////////////////////////////////////////////////////////
		//      LocIsEnregistered类型的变量get_registerId 方法返回的积存器号和
		//      他定义的积存器号种是大1  ，所以这里要减掉 1
		//
		//////////////////////////////////////////////////////////////////////////
		CurThis.Register=CurThis.Register-1;
		THIS_OBJECT_PTR_LIST::iterator FindIt=find(m_ThisObjectPtrList.begin(),m_ThisObjectPtrList.end(),CurThis);
		if(FindIt!=m_ThisObjectPtrList.end())
		{
			if(pTypeRetrun)
				*pTypeRetrun=(SDTYPE*)FindIt->pUdtDataItem;
			return FindIt->DataId;
		}
		bThisObjectPtr=true;
	}

	Symbol->get_constType(&bConstType);
	Symbol->get_volatileType(&bVolatileType);
	TypeLen = sizeof(SDUDTDATAITEM)+TStrLen(TypeName)+1;
	pDataMember =(SDUDTDATAITEM*) new char [TypeLen];
	memset(pDataMember,0,TypeLen);
	pDataMember->DataId=m_CurrentDataSymbolIndex;
	m_CurrentDataSymbolIndex++;
	pDataMember->uName.Name=(char *)&pDataMember[1];
	pDataMember->KindData=dwDataKind;
	TStrCpy(pDataMember->uName.Name,TypeName);
	LocalFree(TypeName);
	if(Location==LocIsStatic)
	{
		SDPUBLICSYMBOL  psdp;
		Symbol->get_relativeVirtualAddress(&psdp.Rva);
		PUBLIC_SYMBOL_MAP::iterator FindIt;
		FindIt = m_PublicSymbolList.find(psdp);
		if(FindIt!=m_PublicSymbolList.end())
		{
			delete [](*FindIt).first.uName.Name;
			m_PublicSymbolList.erase(FindIt);
		}
		STATICDATA StaticData;
		StaticData.Name=pDataMember->uName.Name;
		StaticData.Rva=psdp.Rva;
		STATIC_DATA_MAP::iterator It = m_StaticDataMap.find(StaticData);
		if(It!=m_StaticDataMap.end())
		{
			m_CurrentDataSymbolIndex--;
			delete []pDataMember;
			if(pTypeRetrun)
				*pTypeRetrun=(SDTYPE*)m_DataTagVector[It->second];
			return It->second;
		}
		m_StaticDataMap.insert(STATIC_DATA_MAP::value_type(StaticData,pDataMember->DataId));
	}
	Symbol->get_access(&Access);
	pDataMember->Access=Access;
	m_DataTagVector.push_back(pDataMember);
	pDataMember->IsConstType=bConstType?1:0;
	pDataMember->IsVolatileType=bVolatileType?1:0;
	if(bThisObjectPtr)
	{
		CurThis.DataId=pDataMember->DataId;
		CurThis.pUdtDataItem=pDataMember;
		m_ThisObjectPtrList.push_back(CurThis);
	}
	DataType=NULL;
	if(SUCCEEDED(Symbol->get_type(&DataType))&&DataType!=NULL)
	{		
		Local1ReleaseFlags=1;	
		typeID=MakeSDType(DataType,&Local1ReleaseFlags,&pTypeReturn);
		if(pTypeReturn)
		{
			pDataMember->DataSize = pTypeReturn->SDTypeInfile.TypeSize;
		}
		pDataMember->TypeId=typeID;
		if(Local1ReleaseFlags)
			DataType->Release();	
	}else
	{
		if(dwDataKind==DataIsConstant)
		{
			pDataMember->DataSize=4;
			pDataMember->TypeId=0;
		}
		else
		{
			pDataMember->DataSize=0;
			pDataMember->TypeId=0;
		}
	}

	pDataMember->Location=Location;
	SetUDTDataItem(pDataMember,Symbol);
	//if(pDataMember->Location==LocIsStatic)
	//	m_StaticVariable.push_back(pDataMember->u.LOCISSTATIC.Rav);
	IDiaSymbol*ParentUDTType=NULL;
	if(SUCCEEDED(Symbol->get_classParent(&ParentUDTType))&&ParentUDTType)
	{
		DWORD LocalReleaseFlags1=1;
		pDataMember->TypeIdParentUDT=MakeSDType(ParentUDTType,&LocalReleaseFlags1);
		if(LocalReleaseFlags1)
			ParentUDTType->Release();
	}
	if(pTypeRetrun)
		*pTypeRetrun=(SDTYPE*)pDataMember;
	return pDataMember->DataId;

}

DWORD CSourceDebug::MakeSDFunction(IDiaSymbol* Symbol,DWORD *ReleaseFlags,SDTYPE** pTypeRetrun) 
{
	ULONGLONG length;
	BSTR FuncName=NULL;
	bool bIsThunk=false;
	SDTYPE*pType=NULL;
	DWORD TypeLen;
	BOOL bValue;
	DWORD Rav=0;
	DWORD Access;
	if(pTypeRetrun)
		*pTypeRetrun=NULL;
	if(m_CurrentFunctionSymbolIndex==0x40c)
		m_CurrentFunctionSymbolIndex=0x40c;
	if(FAILED(Symbol->get_relativeVirtualAddress(&Rav)))
		return NULLSYMBOLID;
	if(Rav==0)
		return NULLSYMBOLID;
	
	if(FAILED(Symbol->get_name(&FuncName))||FuncName==NULL)
		return NULLSYMBOLID;
	if(FAILED(Symbol->get_length(&length)))
	{
		LocalFree(FuncName);
		return NULLSYMBOLID;
	}
	
	char* name = new char [TStrLen(FuncName)+1];
	TStrCpy(name,FuncName);
	LocalFree(FuncName);
	SDFUNCTIONITEM* pFunctionItem;	
	STFUNCTIONID FunctionID;
	FunctionID.Name=name;
	FunctionID.Rva = Rav;
	FUNCTION_ID_MAP::iterator FindIT;
	FindIT = m_FuntionID.find(FunctionID);
	if(FindIT!=m_FuntionID.end())
	{
		SDFUNCTIONITEM* pFuncItem = (*FindIT).first.pFuncItem;
		if(pTypeRetrun)
			*pTypeRetrun= (PSDTYPE)pFuncItem;
		delete []name;
		return pFuncItem->ID;
	}
		
	{	
		SDPUBLICSYMBOL  psdp;
		psdp.Rva=Rav;
		PUBLIC_SYMBOL_MAP::iterator FindIt;
		FindIt = m_PublicSymbolList.find(psdp);
		if(FindIt!=m_PublicSymbolList.end())
		{
			delete [](*FindIt).first.uName.Name;
			m_PublicSymbolList.erase(FindIt);
		}
	}
	TypeLen = sizeof(SDFUNCTIONITEM);
	pFunctionItem =(SDFUNCTIONITEM*) new char[TypeLen];	
	memset(pFunctionItem,0,TypeLen);
	pFunctionItem->Rva=Rav;
	if(Rav)
		m_FunctionRavList.push_back(Rav);

	pFunctionItem->uName.Name=name;
	pFunctionItem->Size=*(DWORD*)&length;
	pFunctionItem->ID = m_CurrentFunctionSymbolIndex;
	m_CurrentFunctionSymbolIndex++;
	FunctionID.pFuncItem = pFunctionItem;
	m_FuntionID.insert(FUNCTION_ID_MAP::value_type(FunctionID,pFunctionItem->ID));
	//m_FuntionID.push_back(FunctionID);	
	IDiaFrameData* pFrameData=NULL;
	if(SUCCEEDED(m_GlobalEnumFrameData->frameByRVA(Rav,&pFrameData))&&pFrameData)
	{
		BOOL dwSymtemException=FALSE;
		if(SUCCEEDED(pFrameData->get_systemExceptionHandling(&dwSymtemException)))		
			pFunctionItem->IsSystemExceptionHandling=dwSymtemException?1:0;
		dwSymtemException=FALSE;
		if(SUCCEEDED(pFrameData->get_cplusplusExceptionHandling(&dwSymtemException)))
			pFunctionItem->IsCplusplusExceptionHandling=dwSymtemException?1:0;
		pFrameData->Release();
		pFrameData=NULL;
	}
	if(pTypeRetrun)
	{
		*pTypeRetrun=(PSDTYPE)pFunctionItem;
	}

	if(FAILED(Symbol->get_access(&Access)))
		return NULLSYMBOLID;	
	pFunctionItem->Access=Access;
	Access=0;
	if(FAILED(Symbol->get_locationType(&Access)))
		return NULLSYMBOLID;
	pFunctionItem->Location=Access;
	pFunctionItem->Size=*(DWORD*)&length;
	pFunctionItem->IsThunk=bIsThunk;
	BOOL bIsVirtual=false;
	if(FAILED(Symbol->get_virtual(&bIsVirtual)))
		return NULLSYMBOLID;

	if(bIsVirtual)
	{			
		DWORD dwVirtualBaseOffset=0xffffffff;
		if(FAILED(Symbol->get_virtualBaseOffset(&dwVirtualBaseOffset)))
			return NULLSYMBOLID;
		pFunctionItem->IsVirtual=true;
		pFunctionItem->VirtualBaseOffset=dwVirtualBaseOffset;
	}
	bValue=FALSE;
	Symbol->get_pure(&bValue);
	pFunctionItem->IsPure=bValue?1:0;
	bValue=FALSE;
	Symbol->get_intro(&bValue);
	pFunctionItem->IsIntro=bValue?1:0;
	IDiaEnumSymbols *EnumSymbols=NULL;

	
	if(SUCCEEDED(Symbol->findChildren(SymTagFuncDebugEnd,NULL,nsNone,&EnumSymbols))&&EnumSymbols)
	{
		ULONG celt;
		IDiaSymbol* pCurSymbol;
		LONG count=0;
		if(SUCCEEDED(EnumSymbols->get_Count(&count))&&count==1)
		{
			if(SUCCEEDED(EnumSymbols->Next(1,&pCurSymbol,&celt))&&celt==1)
			{				
				pCurSymbol->get_relativeVirtualAddress(&pFunctionItem->DebugEnd);
				pCurSymbol->Release();
				pCurSymbol = NULL;
			}	
		}
		EnumSymbols->Release();	
		EnumSymbols=NULL;
	}
	if(SUCCEEDED(Symbol->findChildren(SymTagFuncDebugStart,NULL,nsNone,&EnumSymbols))&&EnumSymbols)
	{
		ULONG celt;
		IDiaSymbol* pCurSymbol;
		LONG count=0;
		if(SUCCEEDED(EnumSymbols->get_Count(&count))&&count==1)
		{
			if(SUCCEEDED(EnumSymbols->Next(1,&pCurSymbol,&celt))&&celt==1)
			{							
				pCurSymbol->get_relativeVirtualAddress(&pFunctionItem->DebugStart);
				pCurSymbol->Release();
				pCurSymbol = NULL;
			}
		}
		EnumSymbols->Release();	
		EnumSymbols=NULL;
	}
	if(SUCCEEDED(Symbol->findChildren(SymTagBlock,NULL,nsNone,&EnumSymbols))&&EnumSymbols)
	{
		ULONG celt;
		IDiaSymbol* pCurSymbol;
		LONG count=0;
		list<DWORD> FuncBlock;
		list<DWORD>::iterator BeginIt,EndIt;
		size_t Size;
		int i = 0;
		while(SUCCEEDED(EnumSymbols->Next(1,&pCurSymbol,&celt))&&celt==1)
		{								
			MakeSDBlock(pCurSymbol,&FuncBlock);
			pCurSymbol->Release();
			i++;
		}
		Size = FuncBlock.size();
		count = *(LONG*)&Size;
		if(count>=1)
		{
			pFunctionItem->pBlock.pBlockTypeIdArray=new DWORD[count];
			memset(pFunctionItem->pBlock.pBlockTypeIdArray,0,sizeof(DWORD)*count);
			pFunctionItem->BlockCounter=count;
			BeginIt=FuncBlock.begin();EndIt=FuncBlock.end();
			int i = 0;
			for(;BeginIt!=EndIt;BeginIt++,i++)
				pFunctionItem->pBlock.pBlockTypeIdArray[i]=*BeginIt;
		}
		FuncBlock.clear();
		EnumSymbols->Release();
		EnumSymbols=NULL;
	}

	if(SUCCEEDED(Symbol->findChildren(SymTagData,NULL,nsNone,&EnumSymbols))&&EnumSymbols!=NULL)
	{
		IDiaSymbol * pCurSymbol;
		ULONG celt;
		LONG count=0;		
		SDUDTDATAITEM * pUdtDataItem;
		
		if(SUCCEEDED(EnumSymbols->get_Count(&count))&&count)
		{
			pFunctionItem->DataCounter=count;
			pFunctionItem->pData.pDataMember = new DWORD[count];
			memset(pFunctionItem->pData.pDataMember,0,sizeof(DWORD)*count);
		}
		int i = 0;
		while(SUCCEEDED(EnumSymbols->Next(1,&pCurSymbol,&celt))&&celt==1)
		{
			SDTYPE *pReturnType=NULL;
			pFunctionItem->pData.pDataMember[i]=MakeSDDataTagType(pCurSymbol,NULL,&pReturnType);
			if(pFunctionItem->pData.pDataMember[i]==0)
			{
				pCurSymbol->Release();
				continue;
			}
			if(pReturnType)
			{
				pUdtDataItem = (SDUDTDATAITEM*)pReturnType;
				pUdtDataItem->TypeIdParentUDT=pFunctionItem->ID;
			}			
			pCurSymbol->Release();
			i++;
		}	
		pFunctionItem->DataCounter=i;
		EnumSymbols->Release();
		EnumSymbols=NULL;
	}
	if(SUCCEEDED(Symbol->findChildren(SymTagLabel,NULL,nsNone,&EnumSymbols))&&EnumSymbols!=NULL)
	{
		IDiaSymbol * pCurSymbol;
		BSTR LabelName=NULL;
		LONG count=0;
		ULONG celt=0;
		if(SUCCEEDED(EnumSymbols->get_Count(&count)&&count))
		{
			pFunctionItem->LabelCounter=count;
			SDLABELITEM* pSDLabelItem=new SDLABELITEM[count];
			int i = 0;
			pCurSymbol=NULL;
			while(SUCCEEDED(EnumSymbols->Next(1,&pCurSymbol,&celt))&&celt==1&&pCurSymbol)
			{
				pCurSymbol->get_name(&LabelName);
				int Len = TStrLen(LabelName);
				pSDLabelItem[i].uName.Name = new char[Len+1];
				TStrCpy(pSDLabelItem[i].uName.Name,LabelName);
				LocalFree(LabelName);
				pCurSymbol->get_relativeVirtualAddress(&pSDLabelItem[i].Rva);
				pCurSymbol->Release();
				pCurSymbol=NULL;
				i++,celt=0;
			}
			pFunctionItem->pLabel.pLabelArray=pSDLabelItem;
		}
		else
		{
			pFunctionItem->LabelCounter=0;
			pFunctionItem->pLabel.pLabelArray=NULL;
		}
		EnumSymbols->Release();
		EnumSymbols=NULL;
	}
	IDiaSymbol*FuncType=NULL;
	if(SUCCEEDED(Symbol->get_type(&FuncType))&&FuncType)
	{
		DWORD LocalReleaseFlags=1;
		pFunctionItem->TypeID=MakeSDType(FuncType,&LocalReleaseFlags);
		if(LocalReleaseFlags)
			FuncType->Release();
		ID_TO_SYMBOL_MAP::iterator find = m_IDToSymbolMap.find(pFunctionItem->TypeID);
		if(find!=m_IDToSymbolMap.end())
		{
			SDTYPE *pSubType = find->second;
			if(pSubType->SDTypeInfile.Type==SD_FUNCTIONTYPE)
			{
				SDFUNCTIONTYPE* pFunctionType= (SDFUNCTIONTYPE*)pSubType->Self;
				pFunctionItem->TypeIDReturnValue = pFunctionType->TypeIDReturnValue;
			}						
			else	
				pFunctionItem->TypeIDReturnValue=pSubType->SDTypeInfile.Id;//这种情况是系统自动生成的函数，例如 classname::operator= 等			
		}	
	}
	IDiaSymbol*ParentUDTType=NULL;
	if(SUCCEEDED(Symbol->get_classParent(&ParentUDTType))&&ParentUDTType)
	{
		DWORD LocalReleaseFlags1=1;
		pFunctionItem->TypeIDParentUDT=MakeSDType(ParentUDTType,&LocalReleaseFlags1);
		if(LocalReleaseFlags1)
			ParentUDTType->Release();
	}
	return pFunctionItem->ID;
}
DWORD CSourceDebug::MakeSDBlock(IDiaSymbol *Symbol,list<DWORD>* BlockList)
{
	IDiaEnumSymbols *EnumSymbols=NULL;
	LONG count=0;
	DWORD BlockLen=sizeof(SDBLOCK)+sizeof(SDTYPE);
	ULONGLONG length;	
	DWORD RAV=0xffffffff;
	ULONG celt;
	SDBLOCK *block=NULL;
	SDTYPE* pType;
	IDiaSymbol* pCurSymbol=NULL;

	if(Symbol==NULL)
		return NULL;
	if(CheckSymbolSymTagType(Symbol,SymTagBlock)==false)
		return NULL;
	if(FAILED(Symbol->findChildren(SymTagData,NULL,nsNone,&EnumSymbols))||EnumSymbols==NULL)
		CODE_WARNING("CSourceDebug::MakeSDBlock");
	if(FAILED(EnumSymbols->get_Count(&count)))
		CODE_WARNING("CSourceDebug::MakeSDBlock");
	if(count>=1)
		BlockLen +=((count-1)*sizeof(DWORD*));
	pType=(SDTYPE*)new char[BlockLen];
	memset(pType,0,BlockLen);
	pType->SDTypeInfile.Id=m_CurrentSymbolIndex;
	m_CurrentSymbolIndex++;
	pType->SDTypeInfile.Size=BlockLen;
	block=(SDBLOCK *)&pType[1];
	pType->Self=block;
	block->DataCounter=count;
	if(FAILED(Symbol->get_relativeVirtualAddress(&RAV)))
		CODE_WARNING("CSourceDebug::MakeSDBlock");
	block->Rva=RAV;	
	if(FAILED(Symbol->get_length(&length)))
		CODE_WARNING("CSourceDebug::MakeSDBlock");
	block->Len=(DWORD)length;
	int i = 0;
	while(SUCCEEDED(EnumSymbols->Next(1,&pCurSymbol,&celt))&&celt==1)
	{				
		SDTYPE *pReturnType;
		block->pDataMember[i] = MakeSDDataTagType(pCurSymbol,NULL,&pReturnType);
		SDUDTDATAITEM *pUdtDataItem;
		pUdtDataItem=(SDUDTDATAITEM*)pReturnType;
		pUdtDataItem->TypeIdParentUDT=pType->SDTypeInfile.Id;
		pCurSymbol->Release();
		i++;
	}	
	EnumSymbols->Release();
	EnumSymbols=NULL;
	BlockList->push_back(pType->SDTypeInfile.Id);
	pType->SDTypeInfile.Type=SD_BLOCK;
	m_IDToSymbolMap.insert(ID_TO_SYMBOL_MAP::value_type(pType->SDTypeInfile.Id,pType));
	SYMBOLLIST sl;
	sl.id=pType->SDTypeInfile.Id;
	sl.type=pType;
	//m_SymbolList.push_back(sl);
	m_SymbolList.insert( SD_SYMBOL_MAP::value_type(sl,sl.id));

	if(SUCCEEDED(Symbol->findChildren(SymTagBlock,NULL,nsNone,&EnumSymbols))&&EnumSymbols)
	{
		ULONG celt;
		IDiaSymbol* pCurSymbol;			
		while(SUCCEEDED(EnumSymbols->Next(1,&pCurSymbol,&celt))&&celt==1)
		{								
			MakeSDBlock(pCurSymbol,BlockList);
			pCurSymbol->Release();
		}
		EnumSymbols->Release();
	}
	return pType->SDTypeInfile.Id;
}
bool CSourceDebug::GetArrayList(IDiaSymbol* Symbol,ARRAY_DIA_SYMBOL_LIST* ArrayList)
{
	IDiaSymbol* NewSymbol=Symbol;
	DWORD dwSymTag;
	IDiaSymbol* ElementType=NULL;
	ArrayList->clear();
	if(FAILED(NewSymbol->get_symTag(&dwSymTag)))
		return false;
	while(dwSymTag==SymTagArrayType)
	{
		ArrayList->push_front(NewSymbol);
		if (FAILED(NewSymbol->get_type(&ElementType)))
			return false;
		if(FAILED(ElementType->get_symTag(&dwSymTag)))
			return false;
		NewSymbol=ElementType;
	}
	ElementType->Release();
	return true;
}
DWORD CSourceDebug::MakeSDArrayType(IDiaSymbol* Symbol,DWORD *ReleaseFlags,SDTYPE** pTypeRetrun) 
{
	ARRAY_DIA_SYMBOL_LIST::iterator BeginIt,EndIt;
	ARRAY_DIA_SYMBOL_LIST ArrayList;
	IDiaSymbol* TmpSymbol;
	DWORD PrevArrayTypeId=0;
	DWORD ii=0;
	if(pTypeRetrun)
		*pTypeRetrun=NULL;
	if(ReleaseFlags)
		*ReleaseFlags=1;
	if(GetArrayList(Symbol,&ArrayList)==false)
		return NULLSYMBOLID;
	BeginIt=ArrayList.begin();
	EndIt=ArrayList.end();
	for(;BeginIt!=EndIt;BeginIt++)
	{
		if(ii)
			ii++;
		TmpSymbol = *BeginIt;
		PrevArrayTypeId = MakeSDArrayType(TmpSymbol,PrevArrayTypeId,ReleaseFlags,pTypeRetrun);
		if(*ReleaseFlags)
		{
			TmpSymbol->Release();
			*ReleaseFlags=0;
		}
		ii++;
	}
	ArrayList.clear();
	return PrevArrayTypeId;
}
DWORD CSourceDebug::MakeSDArrayType(IDiaSymbol* Symbol,DWORD PrevArrayTypeId,DWORD *ReleaseFlags,SDTYPE** pTypeRetrun) 
{
	SDTYPE *pType;
	SDARRAYTYPE* pArrayType;
	BSTR Name=NULL;	
	SDARRAYINDEX AI;
	list<SDARRAYINDEX> IndexList;
	list<SDARRAYINDEX>::iterator begin,end;
	ULONGLONG TypeLen;
	SD_SYMBOL_LIST::iterator beginIT,endIT;
	IDiaSymbol* curPdbTypeArrayIndex = Symbol;
	ULONGLONG arraySize,tmplonglong;
	DWORD curPdbTypeArrayIndexTag;
	IDiaSymbol* curIndexType;
	IDiaSymbol* diaElementType;
	ULONGLONG curElementSize;
	DWORD LocalReleaseFlags1;
	bool bFirstFlag=true;
	if(pTypeRetrun)
		*pTypeRetrun=NULL;
	if(ReleaseFlags)
		*ReleaseFlags=1;
	for(beginIT=m_ArrayList.begin();beginIT!=m_ArrayList.end();beginIT++)
	{
		HRESULT hr;
		IDiaSymbol* OldSymbol;
		OldSymbol=(IDiaSymbol*)beginIT->type->Symbol;
		hr = m_DiaSession->symsAreEquiv(Symbol,OldSymbol);
		if(hr==S_OK)	
		{
			SYMBOLLIST sl = *beginIT;
			if(pTypeRetrun)
				*pTypeRetrun=sl.type;
			return sl.id;
		}
	}
	// Get total size of top array symbol

	if (FAILED(curPdbTypeArrayIndex->get_length(&arraySize))) 
		return NULLSYMBOLID;
	TypeLen = arraySize;
	// We know we're in an array already
	curPdbTypeArrayIndexTag = SymTagArrayType;
	// get index type of top array index
	curIndexType=NULL;
	if (FAILED(curPdbTypeArrayIndex->get_arrayIndexType(&curIndexType))) 
		return NULLSYMBOLID; 
	// Get type of top array indexes elements
	diaElementType=NULL;
	if (FAILED(curPdbTypeArrayIndex->get_type(&diaElementType))) 
		return NULLSYMBOLID;
	// Get size of of top array indexes elements
	if (FAILED(diaElementType->get_length(&curElementSize))) 
		return NULLSYMBOLID;
	// Now, process the indices 
	while(curPdbTypeArrayIndexTag == SymTagArrayType) 
	{
		if (curElementSize != 0) 	
		{
			tmplonglong=arraySize / curElementSize;
			AI.Size=*(DWORD*)&tmplonglong;
		}
		else			
			AI.Size=0;
		LocalReleaseFlags1=1;
		AI.TypeIDIndex=MakeSDType(curIndexType,&LocalReleaseFlags1);
		if(LocalReleaseFlags1)
		{
			curIndexType->Release();
			curIndexType=NULL;
		}
		IndexList.push_back(AI);
		// Move down to next array index 
		if(bFirstFlag==false)
		{
			curPdbTypeArrayIndex->Release();
			curPdbTypeArrayIndex=NULL;
		}
		bFirstFlag=false;
		curPdbTypeArrayIndex = diaElementType;
		// Size of new array index
		arraySize = curElementSize;
		// get symtag of new array index
		if (FAILED(curPdbTypeArrayIndex->get_symTag(&curPdbTypeArrayIndexTag))) 	
			return NULLSYMBOLID;
		// if it ISNT an array, stop right now
		if (curPdbTypeArrayIndexTag != SymTagArrayType) 
			break;    
		// get index type of sub-array 
		if (FAILED(curPdbTypeArrayIndex->get_arrayIndexType(&curIndexType))) 
			return NULLSYMBOLID;   

		// Get type of sub-array elements
		if (FAILED(curPdbTypeArrayIndex->get_type(&diaElementType))) 
			return NULLSYMBOLID;  
		// get size in bytes of sub-array elements
		if (FAILED(diaElementType->get_length(&curElementSize))) 
			return NULLSYMBOLID;
	}
	DWORD len;
	len = sizeof(SDARRAYTYPE)+sizeof(SDTYPE);
	if(IndexList.size()>1)
		len = len+sizeof(SDARRAYINDEX)*(IndexList.size()-1);
	pType = (SDTYPE *) new char[len];
	pType->SDTypeInfile.Size=len;
	pType->Symbol=Symbol;	
	pType->SDTypeInfile.Id = m_CurrentSymbolIndex;
	m_CurrentSymbolIndex++;
	SYMBOLLIST sl;
	sl.id=pType->SDTypeInfile.Id;
	sl.type=pType;
	//m_SymbolList.push_back(sl);
	m_SymbolList.insert( SD_SYMBOL_MAP::value_type(sl,sl.id));
	m_ArrayList.push_back(sl);
	m_IDToSymbolMap.insert(ID_TO_SYMBOL_MAP::value_type(pType->SDTypeInfile.Id,pType));		
	pArrayType = (SDARRAYTYPE*)&pType[1];
	pType->Self=pArrayType;

	DWORD LocalReleaseFlags=1;
	pArrayType->TypeIDElement=MakeSDType(diaElementType,&LocalReleaseFlags);
	if(LocalReleaseFlags)
		diaElementType->Release();
	begin = IndexList.begin();
	end = IndexList.end();
	int i = 0;
	for(;begin!=end;begin++,i++)	
		pArrayType->Dimensions[i]=(*begin);
	size_t Size;
	Size=IndexList.size();	
	pArrayType->DimensionsSize=*(DWORD*)&Size;
	pArrayType->NextArrayID=PrevArrayTypeId;
	IndexList.clear();
	pType->SDTypeInfile.Type=SD_ARRAY;
	pType->SDTypeInfile.TypeSize=*(DWORD*)&TypeLen;
	pType->Self=pArrayType;	
	pType->SDTypeInfile.uName.Name=GetSDSymbolName(pType->SDTypeInfile.Id);
	if(pTypeRetrun)
		*pTypeRetrun=pType;
	if(ReleaseFlags)
		*ReleaseFlags=0;
	return pType->SDTypeInfile.Id;
}
/*
DWORD CSourceDebug::MakeSDArrayType(IDiaSymbol* Symbol,DWORD *ReleaseFlags,SDTYPE** pTypeRetrun) 
{
	SDTYPE *pType;
	SDARRAYTYPE* pArrayType;
	BSTR Name=NULL;	
	SDARRAYINDEX AI;
	list<SDARRAYINDEX> IndexList;
	list<SDARRAYINDEX>::iterator begin,end;
	ULONGLONG TypeLen;
	SD_SYMBOL_LIST::iterator beginIT,endIT;
	IDiaSymbol* curPdbTypeArrayIndex = Symbol;
	ULONGLONG arraySize,tmplonglong;
	DWORD curPdbTypeArrayIndexTag;
	IDiaSymbol* curIndexType;
	IDiaSymbol* diaElementType;
	ULONGLONG curElementSize;
	DWORD LocalReleaseFlags1;
	bool bFirstFlag=true;
	if(pTypeRetrun)
		*pTypeRetrun=NULL;
	if(ReleaseFlags)
		*ReleaseFlags=1;
	for(beginIT=m_ArrayList.begin();beginIT!=m_ArrayList.end();beginIT++)
	{
		HRESULT hr;
		IDiaSymbol* OldSymbol;
		OldSymbol=(IDiaSymbol*)beginIT->type->Symbol;
		hr = m_DiaSession->symsAreEquiv(Symbol,OldSymbol);
		if(hr==S_OK)	
		{
			SYMBOLLIST sl = *beginIT;
			if(pTypeRetrun)
				*pTypeRetrun=sl.type;
			return sl.id;
		}
	}
	// Get total size of top array symbol
	
	if (FAILED(curPdbTypeArrayIndex->get_length(&arraySize))) 
		return NULLSYMBOLID;
	TypeLen = arraySize;
	// We know we're in an array already
	curPdbTypeArrayIndexTag = SymTagArrayType;
	// get index type of top array index
	curIndexType=NULL;
	if (FAILED(curPdbTypeArrayIndex->get_arrayIndexType(&curIndexType))) 
		return NULLSYMBOLID; 
	// Get type of top array indexes elements
	diaElementType=NULL;
	if (FAILED(curPdbTypeArrayIndex->get_type(&diaElementType))) 
		return NULLSYMBOLID;
	// Get size of of top array indexes elements
	if (FAILED(diaElementType->get_length(&curElementSize))) 
		return NULLSYMBOLID;
	// Now, process the indices 
	while(curPdbTypeArrayIndexTag == SymTagArrayType) 
	{
		if (curElementSize != 0) 	
		{
			tmplonglong=arraySize / curElementSize;
			AI.Size=*(DWORD*)&tmplonglong;
		}
		else			
			AI.Size=0;
		LocalReleaseFlags1=1;
		AI.TypeIDIndex=MakeSDType(curIndexType,&LocalReleaseFlags1);
		if(LocalReleaseFlags1)
		{
			curIndexType->Release();
			curIndexType=NULL;
		}
		IndexList.push_back(AI);
		// Move down to next array index 
		if(bFirstFlag==false)
		{
			curPdbTypeArrayIndex->Release();
			curPdbTypeArrayIndex=NULL;
		}
		bFirstFlag=false;
		curPdbTypeArrayIndex = diaElementType;
		// Size of new array index
		arraySize = curElementSize;
		// get symtag of new array index
		if (FAILED(curPdbTypeArrayIndex->get_symTag(&curPdbTypeArrayIndexTag))) 	
			return NULLSYMBOLID;
		// if it ISNT an array, stop right now
		if (curPdbTypeArrayIndexTag != SymTagArrayType) 
			break;    
		// get index type of sub-array 
		if (FAILED(curPdbTypeArrayIndex->get_arrayIndexType(&curIndexType))) 
			return NULLSYMBOLID;   

		// Get type of sub-array elements
		if (FAILED(curPdbTypeArrayIndex->get_type(&diaElementType))) 
			return NULLSYMBOLID;  
		// get size in bytes of sub-array elements
		if (FAILED(diaElementType->get_length(&curElementSize))) 
			return NULLSYMBOLID;
	}
	DWORD len;
	len = sizeof(SDARRAYTYPE)+sizeof(SDTYPE);
	if(IndexList.size()>1)
		len = len+sizeof(SDARRAYINDEX)*(IndexList.size()-1);
	pType = (SDTYPE *) new char[len];
	pType->SDTypeInfile.Size=len;
	pType->Symbol=Symbol;	
	pType->SDTypeInfile.Id = m_CurrentSymbolIndex;
	m_CurrentSymbolIndex++;
	SYMBOLLIST sl;
	sl.id=pType->SDTypeInfile.Id;
	sl.type=pType;
	m_SymbolList.push_back(sl);
	m_ArrayList.push_back(sl);
	m_IDToSymbolMap.insert(ID_TO_SYMBOL_MAP::value_type(pType->SDTypeInfile.Id,pType));		
	pArrayType = (SDARRAYTYPE*)&pType[1];
	pType->Self=pArrayType;

	DWORD LocalReleaseFlags=1;
	pArrayType->TypeIDElement=MakeSDType(diaElementType,&LocalReleaseFlags);
	if(LocalReleaseFlags)
		diaElementType->Release();
	begin = IndexList.begin();
	end = IndexList.end();
	int i = 0;
	for(;begin!=end;begin++,i++)	
		pArrayType->Dimensions[i]=(*begin);		
	size_t Size;
	Size=IndexList.size();	
	pArrayType->DimensionsSize=*(DWORD*)&Size;
	IndexList.clear();
	pType->SDTypeInfile.Type=SD_ARRAY;
	pType->SDTypeInfile.TypeSize=*(DWORD*)&TypeLen;
	pType->Self=pArrayType;	
	pType->SDTypeInfile.uName.Name=GetSDSymbolName(pType->SDTypeInfile.Id);
	if(pTypeRetrun)
		*pTypeRetrun=pType;
	if(ReleaseFlags)
		*ReleaseFlags=0;
	return pType->SDTypeInfile.Id;
}
*/
DWORD CSourceDebug::MakeSDEnumType(IDiaSymbol* Symbol,DWORD *ReleaseFlags,SDTYPE** pTypeRetrun)
{
	SD_SYMBOL_LIST::iterator beginIT,endIT;
	SDTYPE *pType;
	ULONGLONG length;
	DWORD newlen;
	BOOL bValue;
	BSTR EnumName=NULL;
	DWORD SelfReleaseFlags=1;
	SDENUMERATIONTYPE* EnumData;
	LONG datacount=0;
	ULONG count = 0;
	IDiaSymbol* EnumTypeSymbol=NULL;
	DWORD TypeId=0xffffffff;
	DWORD EnumSymTag=0xffffffff;
	IDiaSymbol* curValue;
	IDiaEnumSymbols* enumValuesEnum=NULL;
	unsigned int i;

	if(pTypeRetrun)
		*pTypeRetrun=NULL;
	if(ReleaseFlags)
		*ReleaseFlags=SelfReleaseFlags;

	for(beginIT=m_EnumList.begin(),endIT=m_EnumList.end();beginIT!=endIT;beginIT++)
	{
		if(m_DiaSession->symsAreEquiv(Symbol,(IDiaSymbol*)beginIT->type->Symbol)==S_OK)
		{
			if(pTypeRetrun)
				*pTypeRetrun=beginIT->type;
			return beginIT->type->SDTypeInfile.Id;
		}
	}

	if (FAILED(Symbol->findChildren(SymTagData, NULL, nsNone, &enumValuesEnum)))
		return NULLSYMBOLID;
	if(FAILED(enumValuesEnum->get_Count(&datacount)))
		return NULLSYMBOLID;	
	newlen = sizeof(SDENUMERATIONTYPE)+sizeof(SDTYPE);
	if(datacount)
		newlen=newlen + sizeof(ENUMERATIONDATAMEMBER)*(datacount-1);
	pType=(SDTYPE*)new char [newlen];
	memset(pType,0,newlen);
	EnumData = (SDENUMERATIONTYPE*)&pType[1];
	EnumData->DataCount=datacount;
	pType->Symbol=Symbol;
	pType->SDTypeInfile.Id = m_CurrentSymbolIndex;
	if(m_CurrentSymbolIndex==0x3b)
		m_CurrentSymbolIndex=0x3b;
	m_CurrentSymbolIndex++;	
	pType->SDTypeInfile.Type=SD_ENUMERATION;	
	pType->SDTypeInfile.Size=newlen;
	SYMBOLLIST sl;
	sl.id=pType->SDTypeInfile.Id;
	sl.type=pType;
	m_EnumList.push_back(sl);
	//m_SymbolList.push_back(sl);
	m_SymbolList.insert( SD_SYMBOL_MAP::value_type(sl,sl.id));
	bValue=FALSE;
	Symbol->get_nested(&bValue);
	EnumData->IsNested=bValue?1:0;
	bValue=FALSE;
	Symbol->get_scoped(&bValue);
	EnumData->IsScoped=bValue?1:0;
	if(FAILED(Symbol->get_name(&EnumName)))
		return NULLSYMBOLID;	
	if(FAILED(Symbol->get_length(&length)))
		return NULLSYMBOLID;	
	pType->SDTypeInfile.TypeSize= *(DWORD*)&length;
	pType->SDTypeInfile.uName.Name=new char[TStrLen(EnumName)+1];
	TStrCpy(pType->SDTypeInfile.uName.Name,EnumName);
	pType->Self=EnumData;
	if(FAILED(Symbol->get_type(&EnumTypeSymbol))&&EnumTypeSymbol==NULL)
		return NULLSYMBOLID;
	DWORD LocalReleaseFlags=1;
	EnumData->TypeID=MakeSDType(EnumTypeSymbol,&LocalReleaseFlags);
	if(LocalReleaseFlags)
		EnumTypeSymbol->Release();
	
	curValue=NULL;
	i = 0;
	count=0;;DWORD locationType;ULONGLONG valueL=0;
	while(SUCCEEDED(enumValuesEnum->Next(1, &curValue, &count))&&count==1&&curValue)
	{	
		char BufTemp[20]={0};
		VARIANT value;
		value.intVal=sizeof(VARIANT);
		char BufTemp2[20]={0};
		//memset(BufTemp2,0,sizeof(BufTemp2));
		//memset(BufTemp,0,sizeof(BufTemp));
		if (FAILED(curValue->get_locationType(&locationType))) 	
			return NULLSYMBOLID;
		if (locationType != LocIsConstant)
			return NULLSYMBOLID;
		
		if (FAILED(curValue->get_value(&value))) 	
			return NULLSYMBOLID;
		valueL=0;
		switch(value.vt) 
		{
		case VT_UI1: valueL = value.bVal; break;
		case VT_UI2: valueL = value.uiVal; break;
		case VT_UI4: valueL = value.ulVal; break;
		case VT_UI8: valueL=value.ullVal;break;
		case VT_UINT: valueL = value.uintVal; break;
		case VT_INT: valueL = value.intVal; break;
		case VT_I1: valueL = value.cVal; break;
		case VT_I2: valueL = value.iVal; break;
		case VT_I4: valueL = value.lVal; break;
		case VT_I8: valueL = value.llVal;break;	
		case VT_ERROR:CODE_ASSERT(0);break;
		default:
			valueL=0;			
			break;		
		}
		
		EnumData->EnumerationDataMember[i].Value=*(ULONGLONG*)&valueL;
		BSTR valueName = NULL;
		if (FAILED(curValue->get_name(&valueName)) || !valueName)
			return NULLSYMBOLID;
		EnumData->EnumerationDataMember[i].u.Name = new char[TStrLen(valueName)+1];
		TStrCpy(EnumData->EnumerationDataMember[i].u.Name,valueName);
		/*
		SDCONSTVAR ConstVar;
		memset(&ConstVar,0,sizeof(SDCONSTVAR));
		ConstVar.Name=EnumData->EnumerationDataMember[i].u.Name;
		CONST_VAR_MAP::iterator findit = m_ConstVarMap.find(ConstVar);
		if(findit==m_ConstVarMap.end())
		{
			m_ConstVarMap.insert(CONST_VAR_MAP::value_type(ConstVar,0));
		}
		*/
		LocalFree(valueName);
		curValue->Release();
		valueName=NULL;
		curValue=NULL;
		count=0;
		i++;
		CODE_ASSERT(i<=EnumData->DataCount);
	}
	enumValuesEnum->Release();
	
	m_IDToSymbolMap.insert(ID_TO_SYMBOL_MAP::value_type(pType->SDTypeInfile.Id,pType));		
	if(ReleaseFlags)
		*ReleaseFlags=0;
	if(pTypeRetrun)
		*pTypeRetrun=pType;
	return pType->SDTypeInfile.Id;
}
DWORD CSourceDebug::MakeSDPointerReferenceType(IDiaSymbol* Symbol,DWORD *ReleaseFlags,SDTYPE** pTypeRetrun)
{
	BOOL bRef;
	if(FAILED( Symbol->get_reference(&bRef)))
		return NULLSYMBOLID;
	if(bRef==false)
		return MakeSDPointerType(Symbol,ReleaseFlags,pTypeRetrun);
	else
		return MakeSDReferenceType(Symbol,ReleaseFlags,pTypeRetrun);

}	
DWORD CSourceDebug::MakeSDPointerType(IDiaSymbol* Symbol,DWORD *ReleaseFlags,SDTYPE** pTypeRetrun)
{
	SDTYPE* pType;
	SDPOINTERTYPE *pt;
	IDiaSymbol * PointerSymbol;//,*ReferenceSymbol;
	ULONGLONG length;
	char NullPointerName[]="";
	char* PointerName=NULL;
	DWORD PrevPointerTypeID=0;
	DWORD TypeLen,i;
	DWORD SubTypeID;
	DWORD PointerDepth=1;
	DWORD SelfReleaseFlags=1;
	char* TempName;
	if(pTypeRetrun)
		*pTypeRetrun=NULL;
	if(ReleaseFlags)
		*ReleaseFlags=SelfReleaseFlags;
	PointerSymbol = DumpSymTagPointerType(Symbol,NULL,&PointerDepth);
	DWORD LocalReleaseFlags=1;
	SubTypeID=MakeSDType(PointerSymbol,&LocalReleaseFlags);	
	if(LocalReleaseFlags)
		PointerSymbol->Release();
	PointerName=GetSDSymbolName(SubTypeID);
	length=0;
	if(FAILED(Symbol->get_length(&length)))
	{
		if(PointerName)
			delete []PointerName;
		return NULLSYMBOLID;
	}
	for(i = 1; i <= PointerDepth;i++)
	{
		if(PointerName)
		{
			TempName = new char [TStrLen(PointerName)+9+1];
			TSPrintf(TempName,"%s_%08x",PointerName,i);
		}
		else
		{
			TempName = new char [18];
			TSPrintf(TempName,"%08x_%08x",SubTypeID,i);
		}
		CTempSymbol	TempSymbol(TempName,SymTagPointerType,0);
		m_TempSymbolIDIter = m_PointerID.find(TempSymbol);
		if(m_TempSymbolIDIter!=m_PointerID.end())
		{
			PrevPointerTypeID = m_TempSymbolIDIter->second;
			if(i == PointerDepth)
			{
				if(pTypeRetrun)		
					*pTypeRetrun=GetSDTypeBySymbolID(m_TempSymbolIDIter->second);		
				delete []TempName;
				if(PointerName)
					delete []PointerName;
				return m_TempSymbolIDIter->second;
			}
			delete []TempName;
			continue;
		}
		m_PointerID.insert(SYMBOL_ID_MAP::value_type(TempSymbol,m_CurrentSymbolIndex));	
		TypeLen=sizeof(SDTYPE)+sizeof(SDPOINTERTYPE);
		pType =(SDTYPE*) new char [TypeLen];
		memset(pType,0,TypeLen);
		pt =(SDPOINTERTYPE*) &pType[1];		
		pt->TypeID	= SubTypeID;	
		pt->PointerDepth=i;
		pt->NextPointer=PrevPointerTypeID;
		pType->SDTypeInfile.Type=SD_POINTER;
		pType->Self=pt;
		pType->SDTypeInfile.Size=TypeLen;
		pType->SDTypeInfile.TypeSize=(DWORD)length;		
		pType->SDTypeInfile.uName.Name=TempName;
		pType->SDTypeInfile.Id=m_CurrentSymbolIndex;
		m_CurrentSymbolIndex++;
		PrevPointerTypeID=pType->SDTypeInfile.Id;
		m_IDToSymbolMap.insert(ID_TO_SYMBOL_MAP::value_type(pType->SDTypeInfile.Id,pType));
		SYMBOLLIST sl;
		sl.id=pType->SDTypeInfile.Id;
		sl.type=pType;
		//m_SymbolList.push_back(sl);
		m_SymbolList.insert( SD_SYMBOL_MAP::value_type(sl,sl.id));
		if(pTypeRetrun)
			*pTypeRetrun=pType;
		if(ReleaseFlags)
			*ReleaseFlags=1;
	}
	if(PointerName)
		delete []PointerName;
	return pType->SDTypeInfile.Id;

}			
#if 0
DWORD CSourceDebug::MakeSDPointerType(IDiaSymbol* Symbol,DWORD *ReleaseFlags,SDTYPE** pTypeRetrun)
{
	SDTYPE* pType;
	SDPOINTERTYPE *pt;
	static int debug2=0;
	IDiaSymbol * PointerSymbol;//,*ReferenceSymbol;
	ULONGLONG length;
	char NullPointerName[]="";
	char* PointerName;
	DWORD TypeLen;
	DWORD SubTypeID;
	DWORD PointerDepth=1;
	DWORD SelfReleaseFlags=1;
	char* TempName;
	if(pTypeRetrun)
		*pTypeRetrun=NULL;
	if(ReleaseFlags)
		*ReleaseFlags=SelfReleaseFlags;

	PointerSymbol = DumpSymTagPointerType(Symbol,NULL,&PointerDepth);
	DWORD LocalReleaseFlags=1;
	SubTypeID=MakeSDType(PointerSymbol,&LocalReleaseFlags);	
	if(LocalReleaseFlags)
		PointerSymbol->Release();
	PointerName=GetSDSymbolName(SubTypeID);
	if(PointerName)
	{
		TempName = new char [TStrLen(PointerName)+9+1];
		TSPrintf(TempName,"%s_%08x",PointerName,PointerDepth);
		delete []PointerName;	
	}
	else
	{
		TempName = new char [18];
		TSPrintf(TempName,"%08x_%08x",SubTypeID,PointerDepth);
	}
	CTempSymbol	TempSymbol(TempName,SymTagPointerType,0);
	m_TempSymbolIDIter = m_PointerID.find(TempSymbol);
	if(m_TempSymbolIDIter!=m_PointerID.end())
	{
		if(pTypeRetrun)		
			*pTypeRetrun=GetSDTypeBySymbolID(m_TempSymbolIDIter->second);		
		delete []TempName;	
		return m_TempSymbolIDIter->second;		
	}
	m_PointerID.insert(SymbolID::value_type(TempSymbol,m_CurrentSymbolIndex));	
	TypeLen=sizeof(SDTYPE)+sizeof(SDPOINTERTYPE);
	pType =(SDTYPE*) new char [TypeLen];
	memset(pType,0,TypeLen);
	pt =(SDPOINTERTYPE*) &pType[1];		
	pt->TypeID	= SubTypeID;	
	pt->PointerDepth=PointerDepth;
	pType->SDTypeInfile.Type=SD_POINTER;
	pType->Self=pt;
	if(FAILED(Symbol->get_length(&length)))
	{
		delete pType;
		delete pt;
		return NULLSYMBOLID;
	}
	pType->SDTypeInfile.Size=TypeLen;
	pType->SDTypeInfile.TypeSize=(DWORD)length;		
	pType->SDTypeInfile.uName.Name=TempName;
	pType->SDTypeInfile.Id=m_CurrentSymbolIndex;
	m_CurrentSymbolIndex++;

	m_IDToSymbolMap.insert(ID_TO_SYMBOL_MAP::value_type(pType->SDTypeInfile.Id,pType));
	SYMBOLLIST sl;
	sl.id=pType->SDTypeInfile.Id;
	sl.type=pType;
	m_SymbolList.push_back(sl);
	if(pTypeRetrun)
		*pTypeRetrun=pType;
	if(ReleaseFlags)
		*ReleaseFlags=1;
	return pType->SDTypeInfile.Id;
}			
#endif
DWORD CSourceDebug::MakeSDReferenceType(IDiaSymbol* Symbol,DWORD *ReleaseFlags,SDTYPE** pTypeRetrun)
{
	SDTYPE* pType;
	SDREFERENCETYPE *reft;
	IDiaSymbol *ReferenceSymbol;
	DWORD TypeLen;
	DWORD SelfReleaseFlags=1;
	DWORD SubTypeID;
	char *ReferenceName;
	char* TempName;
	if(pTypeRetrun)
		*pTypeRetrun=NULL;
	if(ReleaseFlags)
		*ReleaseFlags=SelfReleaseFlags;
	if(FAILED(Symbol->get_type(&ReferenceSymbol))||ReferenceSymbol==NULL)
		return NULLSYMBOLID;
	DWORD Local1ReleaseFlags=1;		
	SubTypeID = MakeSDType(ReferenceSymbol,&Local1ReleaseFlags);
	if(Local1ReleaseFlags)
		ReferenceSymbol->Release();
	
	ReferenceName=GetSDSymbolName(SubTypeID);
	if(ReferenceName)
	{
		TempName = new char [TStrLen(ReferenceName)+1+1];
		TStrCpy(TempName,ReferenceName);
		TStrCat(TempName,"&");
		delete []ReferenceName;
	}
	else
	{
		TempName = new char[2];
		TempName[0]='&';
		TempName[1]=0;
	}
	
	CTempSymbol	TempSymbol(TempName,SymTagPointerType,0);
	m_TempSymbolIDIter = m_ReferenceID.find(TempSymbol);
	if(m_TempSymbolIDIter!=m_ReferenceID.end())
	{
		if(pTypeRetrun)
			*pTypeRetrun=GetSDTypeBySymbolID(m_TempSymbolIDIter->second);
		delete []TempName;		
		return m_TempSymbolIDIter->second;		
	}
	m_ReferenceID.insert(SYMBOL_ID_MAP::value_type(TempSymbol,m_CurrentSymbolIndex));	
	/*
	SD_SYMBOL_LIST::iterator beginIT,endIT;
	for(beginIT=m_PointerReferenceSymbolList.begin();beginIT!=m_PointerReferenceSymbolList.end();beginIT++)
	{
		HRESULT hr;
		SDTYPE* pCurType;
		IDiaSymbol* OldSymbol;
		pCurType=beginIT->type;
		OldSymbol=pCurType->Symbol;
		hr = m_DiaSession->symsAreEquiv(Symbol,OldSymbol);
		if(hr==S_OK)
		return pCurType->Id;
	}
	*/		
	TypeLen=sizeof(SDTYPE)+sizeof(SDREFERENCETYPE);
	pType = (SDTYPE*)new char [TypeLen];
	memset(pType,0,TypeLen);
	pType->SDTypeInfile.Size=TypeLen;
	reft = (SDREFERENCETYPE*)&pType[1];
	reft->TypeID=SubTypeID;
	pType->SDTypeInfile.Id=m_CurrentSymbolIndex;
	pType->SDTypeInfile.Type=SD_REFERENCE;
	pType->SDTypeInfile.uName.Name=TempName;
	//pType->Symbol=Symbol;
	m_CurrentSymbolIndex++;
	pType->Self=reft;
	m_IDToSymbolMap.insert(ID_TO_SYMBOL_MAP::value_type(pType->SDTypeInfile.Id,pType));
	SYMBOLLIST sl;
	sl.id=pType->SDTypeInfile.Id;
	sl.type=pType;
	//m_SymbolList.push_back(sl);	
	m_SymbolList.insert( SD_SYMBOL_MAP::value_type(sl,sl.id));
	SDTYPE*pSubType = GetSDTypeBySymbolID(reft->TypeID);
	if(pSubType)
		pType->SDTypeInfile.TypeSize = pSubType->SDTypeInfile.TypeSize;	
	if(ReleaseFlags)
		*ReleaseFlags=1;
	if(pTypeRetrun)
		*pTypeRetrun=pType;
	return pType->SDTypeInfile.Id;

}			
DWORD CSourceDebug::MakeSDTypeDefType(IDiaSymbol* Symbol,DWORD *ReleaseFlags,SDTYPE** pTypeRetrun)
{
	char* name;
	BSTR TypeName=NULL;
	SDTYPE *pType;
	ULONGLONG length;
	SDTYPEDEFTYPE *tdt;
	DWORD BufferLength=512;
	DWORD SelfReleaseFlags=1;
	DWORD TypeLen;
	TypeName=NULL;

	if(pTypeRetrun)
		*pTypeRetrun=NULL;
	if(ReleaseFlags)
		*ReleaseFlags=SelfReleaseFlags;
#if 0
	SD_SYMBOL_LIST::iterator beginIT,endIT;
	for(beginIT=m_TypeDefList.begin();beginIT!=m_TypeDefList.end();beginIT++)
	{
		SDTYPE* pCurType;
		HRESULT hr;
		IDiaSymbol* OldSymbol;
		OldSymbol=(IDiaSymbol*)beginIT->type->Symbol;
		hr = m_DiaSession->symsAreEquiv(Symbol,OldSymbol);
		if(hr==S_OK)
		{
			pCurType=beginIT->type;
			if(pTypeRetrun)
				*pTypeRetrun=pCurType;
			return pCurType->SDTypeInfile.Id;
		}
	}
#endif

	if(FAILED(Symbol->get_name(&TypeName)))
		return NULLSYMBOLID;
	if(FAILED(Symbol->get_length(&length)))
		return NULLSYMBOLID;
	TypeLen = sizeof(SDTYPE)+sizeof(SDTYPEDEFTYPE);
	pType=(SDTYPE*)new char [TypeLen];
	tdt=(SDTYPEDEFTYPE*)&pType[1];
	name = new char[TStrLen(TypeName)+1];	
	TStrCpy(name,TypeName);
	LocalFree(TypeName);
	IDiaSymbol *TypeSymbol=NULL;
	if(FAILED(Symbol->get_type(&TypeSymbol))||TypeSymbol==NULL)
		return NULLSYMBOLID;
	pType->SDTypeInfile.Id=m_CurrentSymbolIndex;
	m_CurrentSymbolIndex++;
	pType->SDTypeInfile.Size=TypeLen;
	pType->Self=tdt;
	pType->Symbol=Symbol;
	pType->SDTypeInfile.Type=SD_TYPEDEF;
	pType->SDTypeInfile.uName.Name= name;
	pType->SDTypeInfile.TypeSize=(DWORD)length;	
	m_IDToSymbolMap.insert(ID_TO_SYMBOL_MAP::value_type(pType->SDTypeInfile.Id,pType));
	SYMBOLLIST sl;
	sl.id=pType->SDTypeInfile.Id;
	sl.type=pType;
	//m_SymbolList.push_back(sl);
	m_SymbolList.insert( SD_SYMBOL_MAP::value_type(sl,sl.id));
	m_TypeDefList.push_back(sl);
	SelfReleaseFlags=0;
	if(ReleaseFlags)
		*ReleaseFlags=SelfReleaseFlags;
	DWORD LocalReleaseFlags=1;
	tdt->TypeID = MakeSDType(TypeSymbol,&LocalReleaseFlags);
	SDTYPE*pSubType = GetSDTypeBySymbolID(tdt->TypeID);
	if(pSubType)
		pType->SDTypeInfile.TypeSize = pSubType->SDTypeInfile.TypeSize;
	if(LocalReleaseFlags)
		TypeSymbol->Release();
	if(pTypeRetrun)
		*pTypeRetrun=pType;
	return pType->SDTypeInfile.Id;
}
DWORD CSourceDebug::MakeSDCustomType(IDiaSymbol* Symbol,DWORD *ReleaseFlags,SDTYPE** pTypeRetrun)
{
	BSTR TypeName=NULL;
	char* name=NULL;
	SDTYPE* pType;
	ULONGLONG length;
	DWORD SelfReleaseFlags=1;
	if(pTypeRetrun)
		*pTypeRetrun=NULL;
	if(ReleaseFlags)
		*ReleaseFlags=SelfReleaseFlags;
	if(FAILED(Symbol->get_name(&TypeName)))
		return NULLSYMBOLID;
	if(TypeName)
	{
		name = new char [TStrLen(TypeName)+1];
		TStrCpy(name,TypeName);
		LocalFree(TypeName);
	}
	else
		name=NULL;
	CTempSymbol	TempSymbol(name,SymTagCustomType,0);
	m_TempSymbolIDIter = m_TempSymbolID.find(TempSymbol);
	if(m_TempSymbolIDIter!=m_TempSymbolID.end())
	{
		if(pTypeRetrun)
			*pTypeRetrun=GetSDTypeBySymbolID(m_TempSymbolIDIter->second);
		if(name)
			delete []name;
		return (*m_TempSymbolIDIter).second;
	}

	if(FAILED(Symbol->get_length(&length)))
		return NULL;
	pType = new SDTYPE;
	pType->SDTypeInfile.TypeSize=(DWORD)length;
	pType->SDTypeInfile.Size=sizeof(SDTYPE);
	pType->Symbol=Symbol;
	pType->SDTypeInfile.uName.Name = name;
	pType->Self=NULL;
	pType->SDTypeInfile.Type = SD_CUSTOM;
	pType->SDTypeInfile.Id=m_CurrentSymbolIndex;
	m_CurrentSymbolIndex++;
	m_TempSymbolID.insert(SYMBOL_ID_MAP::value_type(TempSymbol,pType->SDTypeInfile.Id));
	m_TempSymbolIDIter = m_TempSymbolID.find(TempSymbol);
	((CTempSymbol &)(m_TempSymbolIDIter->first)).SetSDType(pType);
	m_IDToSymbolMap.insert(ID_TO_SYMBOL_MAP::value_type(pType->SDTypeInfile.Id,pType));
	SYMBOLLIST sl;
	sl.id=pType->SDTypeInfile.Id;
	sl.type=pType;
	//m_SymbolList.push_back(sl);
	m_SymbolList.insert( SD_SYMBOL_MAP::value_type(sl,sl.id));
	SelfReleaseFlags=0;
	if(ReleaseFlags)
		*ReleaseFlags=SelfReleaseFlags;
	if(pTypeRetrun)
		*pTypeRetrun=pType;
	return pType->SDTypeInfile.Id;

}
DWORD CSourceDebug::MakeSDManagedType(IDiaSymbol* Symbol,DWORD* ReleaseFlags,SDTYPE** pTypeRetrun)
{
	BSTR TypeName=NULL;
	char* name=NULL;
	SDTYPE* pType;
	ULONGLONG length;
	DWORD SelfReleaseFlags=1;

	if(pTypeRetrun)
		*pTypeRetrun=NULL;
	if(FAILED(Symbol->get_name(&TypeName)))
		return NULLSYMBOLID;
	if(TypeName)
	{
		name = new char [TStrLen(TypeName)+1];
		TStrCpy(name,TypeName);
		LocalFree(TypeName);
	}
	else
		name=NULL;
	CTempSymbol	TempSymbol(name,SymTagCustomType,0);
	m_TempSymbolIDIter = m_TempSymbolID.find(TempSymbol);
	if(m_TempSymbolIDIter!=m_TempSymbolID.end())	
	{
		if(pTypeRetrun)
			*pTypeRetrun=GetSDTypeBySymbolID(m_TempSymbolIDIter->second);
		if(name)
			delete []name;
		return (*m_TempSymbolIDIter).second;
	}

	if(FAILED(Symbol->get_length(&length)))
		return NULL;
	pType = new SDTYPE;			
	pType->SDTypeInfile.TypeSize=(DWORD)length;
	pType->SDTypeInfile.Size=sizeof(SDTYPE);
	pType->Self=NULL;
	pType->SDTypeInfile.uName.Name = name;
	pType->SDTypeInfile.Type = SD_MANAGED;
	pType->SDTypeInfile.Id=m_CurrentSymbolIndex;
	m_CurrentSymbolIndex++;
	m_TempSymbolID.insert(SYMBOL_ID_MAP::value_type(TempSymbol,pType->SDTypeInfile.Id));
	m_TempSymbolIDIter = m_TempSymbolID.find(TempSymbol);								
	((CTempSymbol &)(m_TempSymbolIDIter->first)).SetSDType(pType);
	m_IDToSymbolMap.insert(ID_TO_SYMBOL_MAP::value_type(pType->SDTypeInfile.Id,pType));
	SYMBOLLIST sl;
	sl.id=pType->SDTypeInfile.Id;
	sl.type=pType;
	//m_SymbolList.push_back(sl);
	m_SymbolList.insert( SD_SYMBOL_MAP::value_type(sl,sl.id));
	SelfReleaseFlags=0;
	if(ReleaseFlags)
		*ReleaseFlags=SelfReleaseFlags;
	if(pTypeRetrun)
		*pTypeRetrun=pType;
	return pType->SDTypeInfile.Id;


}
bool CSourceDebug::IsUnnamedSDType(char *name)
{
	char unnamed[]="<unnamed-tag>";
char unnamed1[]="__unnamed";
	int i,j;
	int len1,len;

	if(name==NULL)
		return false;
	len = TStrLen(name);
	len1 = TStrLen(unnamed);
	if(len==0||len<len1)
		return false;
	for(i = len-1,j=len1-1;j>=0;i--,j--)
	{
		if(name[i]!=unnamed[j])
			return false;
	}
	if(i>0)
		if(name[i]!=':')
			return false;
	return true;
}

WCHAR* CSourceDebug::GetSDSymbolName(DWORD SymbolId,WCHAR *NameBuffer,DWORD *BufferLength)
{
	SDTYPE* pType;
	ID_TO_SYMBOL_MAP::iterator find = m_IDToSymbolMap.find(SymbolId);
	if(NameBuffer)
		NameBuffer[0]=0;
	pType = GetSDTypeBySymbolID(SymbolId);
	if(pType==NULL)
		return NULL;
	return GetSDSymbolName(pType,NameBuffer,BufferLength);
}
SDTYPE* CSourceDebug::GetSDTypeBySymbolID(DWORD SymbolId)
{
	//SDSymbolList::iterator FindIT;
	SD_SYMBOL_MAP::iterator FindIT;
	SYMBOLLIST SymbolValue;
	SymbolValue.id = SymbolId;
	FindIT = m_SymbolList.find(SymbolValue);
	if(FindIT!=m_SymbolList.end())
		return (*FindIT).first.type;//->type;
	return NULL;
}
SDUDTDATAITEM* CSourceDebug::GetSDDateTypeBySymbolID(DWORD DataId)
{
	if(DataId>=m_DataTagVector.size())
		return NULL;
	return m_DataTagVector[DataId];
}
PSDFUNCTIONITEM CSourceDebug::GetSDFunctionByID(DWORD FunctionId)
{
	FUNCTION_ID_MAP::iterator BeginIT,EndIT;
	BeginIT = m_FuntionID.begin();
	EndIT = m_FuntionID.end();
	for(;BeginIT!=EndIT;BeginIT++)
	{
		if((*BeginIT).first.pFuncItem->ID==FunctionId)
			return (*BeginIT).first.pFuncItem;
	}
	return NULL;
}
char *CSourceDebug::GetSDSymbolName(DWORD SymbolId)
{	
	WCHAR *Buf=NULL;
	DWORD len;
	char *Name=NULL;
	DWORD BufferLength=0x2000;
	Buf = new WCHAR[BufferLength];
	GetSDSymbolName(SymbolId,Buf,&BufferLength);
	len = TStrLen(Buf);
	if(len == 0)
	{
		delete []Buf;
		return NULL;
	}
	Name = new char[len+1];
	TStrCpy(Name,Buf);
	delete []Buf;
	return Name;
}

char* CSourceDebug::GetFunctionName(IN PSDFUNCTIONITEM pFuncItem,OUT char* NameBuffer,INOUT int* BufferLength)
{			
	int dwCurrentLen=0;
	SDTYPE *pSubType=NULL;
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
		pSubType=GetSDTypeBySymbolID(pFuncItem->TypeID);
		if(pSubType->SDTypeInfile.Type==SD_FUNCTIONTYPE)
		{
			SDFUNCTIONTYPE* pFunctionType = (SDFUNCTIONTYPE*)pSubType->Self;
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
		SDUDTDATAITEM* pUdtDataItem= GetSDDateTypeBySymbolID(pFuncItem->pData.pDataMember[i]);
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

char* CSourceDebug::GetSDSymbolName(IN PSDTYPE pType,OUT char *NameBuffer,INOUT int *BufferLength)
{
	return GetSDSymbolName(&pType->SDTypeInfile,NameBuffer,BufferLength);
}
char* CSourceDebug::GetSDSymbolName(IN DWORD SymbolId,OUT char *NameBuffer,INOUT int *BufferLength)
{
	SDTYPE* pType;
	SYMBOLLIST SymbolValue;
	//SDSymbolList::iterator FindIT;
	SD_SYMBOL_MAP::iterator FindIT;
	if(NameBuffer)
		NameBuffer[0]=0;
	SymbolValue.id = SymbolId;
	FindIT = m_SymbolList.find(SymbolValue);
	if(FindIT==m_SymbolList.end())
		return NameBuffer;
	pType = (*FindIT).first.type;
	return GetSDSymbolName(pType,NameBuffer,BufferLength);
}
SDCALLCONVENTIONPAIR CSourceDebug::m_CallConvention[24]=
{
	{0xffffffff," Unknown calling convention in function "},
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
char* CSourceDebug::GetCallConventionName(DWORD dwType)
{
	int i;
	if(dwType>=sizeof(m_CallConvention)/sizeof(m_CallConvention[0]))
		return m_CallConvention[0].Name;
	for(i = 0; i < sizeof(m_CallConvention)/sizeof(m_CallConvention[0]);i++)
		if(m_CallConvention[i].Type==dwType)
			return m_CallConvention[i].Name;
	return m_CallConvention[0].Name;
}
char* CSourceDebug::GetSDSymbolName(IN PSDTYPE_INFILE SDTypeInfile,OUT char *NameBuffer,INOUT int *BufferLength)
{
	SDTYPE *SelfType;
	
	char TypeName[50];//={0};
	int dwOrgBufferLen=*BufferLength;
	int dwCurrentLen;
	int len=0;	
	//SDTYPE *pSubType;
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
			SelfType = GetSDTypeBySymbolID(pPointerType->TypeID);
			GetSDSymbolName(pPointerType->TypeID,NameBuffer,BufferLength);
			dwCurrentLen = pPointerType->PointerDepth;
			TmpBuf.Fill('*',dwCurrentLen);
			if(SelfType->SDTypeInfile.Type==SD_FUNCTIONTYPE)
				dwCurrentLen+=2;
			if(*BufferLength<=dwCurrentLen)
			{
				*BufferLength-=dwCurrentLen;
				return NameBuffer;
			}
			
			if(SelfType->SDTypeInfile.Type==SD_FUNCTIONTYPE)
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
			SelfType = GetSDTypeBySymbolID(pReferenceType->TypeID);
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
			SelfType = GetSDTypeBySymbolID(pArrayType->TypeIDElement);
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
		TStrCpy(TypeName,"enum " NTOSKRNLVER);
		len = TStrLen(TypeName);
		if(*BufferLength>len)
			TStrCpy(NameBuffer,TypeName);
		*BufferLength-=len;
		goto local_002;
	case SD_CLASS:
		TStrCpy(TypeName,"class " NTOSKRNLVER);
		len = TStrLen(TypeName);
		if(*BufferLength>len)
			TStrCpy(NameBuffer,TypeName);
		*BufferLength-=len;
		goto local_002;
	case SD_STRUCT:
		TStrCpy(TypeName,"struct " NTOSKRNLVER);
		len = TStrLen(TypeName);
		if(*BufferLength>len)
			TStrCpy(NameBuffer,TypeName);
		*BufferLength-=len;
		goto local_002;
	case SD_UNION:
		TStrCpy(TypeName,"union " NTOSKRNLVER);
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

WCHAR* CSourceDebug::GetSDSymbolName(SDTYPE* pType,WCHAR *NameBuffer,DWORD *BufferLength,OUT DWORD* ReturnLength)
{
	SDTYPE *SelfType;
	if(NameBuffer)
		NameBuffer[0]=0;
	if(pType==NULL)
		return NULL;	
	switch(pType->SDTypeInfile.Type) 
	{
	case SD_FUNCTIONTYPE:
		{
			int len;
			SDFUNCTIONTYPE* pFunctionType= (SDFUNCTIONTYPE*)pType->Self;
			GetSDSymbolName(pFunctionType->TypeIDReturnValue,NameBuffer,BufferLength);
			switch(pFunctionType->CallingConvention)
			{
				case CV_CALL_NEAR_C:
					TStrCat(NameBuffer,WSTR(" __cdecl "));
					break;
				case CV_CALL_NEAR_FAST:
					TStrCat(NameBuffer,WSTR(" __fastcall "));
					break;
				case CV_CALL_NEAR_STD:
					TStrCat(NameBuffer,WSTR(" __stdcall "));
					break;
				case CV_CALL_NEAR_SYS:
					TStrCat(NameBuffer,WSTR(" __syscall "));
					break;
				case CV_CALL_THISCALL:
					TStrCat(NameBuffer,WSTR(" __thiscall "));
					break;
				default:
					TStrCat(NameBuffer,WSTR(" Unknown calling convention in function "));					
			}
			len = TStrLen(NameBuffer);			
			TStrCat(&NameBuffer[len],WSTR("("));
			len++;
			for(unsigned int  i = 0; i< pFunctionType->ArgsCount;i++)
			{
				GetSDSymbolName(pFunctionType->TypeIDArgs[i],&NameBuffer[len],BufferLength);
				len = TStrLen(NameBuffer);
				TStrCat(&NameBuffer[len],WSTR(","));
				len++;
			}
			if(pFunctionType->ArgsCount)
				NameBuffer[len-1]=')';
			else
			{
				TStrCat(&NameBuffer[len],WSTR(")"));
				len++;
			}
		}
		return NameBuffer;		
	case SD_POINTER:
		{		
			unsigned int  i;
			SDPOINTERTYPE* pPointerType;
			pPointerType = (SDPOINTERTYPE*)pType->Self;
			ID_TO_SYMBOL_MAP::iterator find = m_IDToSymbolMap.find(pPointerType->TypeID);
			if(find==m_IDToSymbolMap.end())
				return NULL;
			SelfType = find->second;			
			GetSDSymbolName(pPointerType->TypeID,NameBuffer,BufferLength);
			WCHAR Buf[10];
			WCHAR*pBuf=Buf;
			if(pPointerType->PointerDepth>sizeof(Buf)/sizeof(Buf[0]) - 1)
			{
				pBuf= new WCHAR[pPointerType->PointerDepth+1];
			}
			for(i = 0; i < pPointerType->PointerDepth;i++)
			{
				pBuf[i]='*';
			}
			pBuf[i]=0;
			if(SelfType->SDTypeInfile.Type==SD_FUNCTIONTYPE)
			{								
				WCHAR *NewName;
				WCHAR c='(';
				NewName = new WCHAR[*BufferLength];
				TStrCpy(NewName,NameBuffer);
				WCHAR * pFunc =TStrChr(NameBuffer,c);
				if(pFunc==NULL)
				{
					if(pBuf!=&Buf[0])
						delete pBuf;
					delete []NewName;
					return NameBuffer;
				}
				DWORD len = (*(DWORD*)&pFunc-*(DWORD*)&NameBuffer);
				len = len / sizeof(WCHAR);
				NameBuffer[len]='(';				
				TStrCpy(&NameBuffer[len+1],pBuf);
				TStrCat(NameBuffer,WSTR(")"));
				TStrCat(NameBuffer,&NewName[len]);
				delete NewName;
			}
			else
				TStrCat(NameBuffer,pBuf);
			if(pBuf!=&Buf[0])
				delete pBuf;
			return NameBuffer;
		}	
		break;
	case SD_REFERENCE:
		{		
			SDREFERENCETYPE*pReferenceType;
			pReferenceType = (SDREFERENCETYPE*)pType->Self;
			ID_TO_SYMBOL_MAP::iterator find = m_IDToSymbolMap.find(pReferenceType->TypeID);
			if(find==m_IDToSymbolMap.end())
				return NULL;
			SelfType = find->second;
			GetSDSymbolName(SelfType,NameBuffer,BufferLength);
			TStrCat(NameBuffer,WSTR("&"));
		}	
		break;
	case SD_ARRAY:
		{
			SDARRAYTYPE* pArrayType;
			pArrayType = (SDARRAYTYPE*)pType->Self;
			ID_TO_SYMBOL_MAP::iterator find = m_IDToSymbolMap.find(pArrayType->TypeIDElement);
			if(find==m_IDToSymbolMap.end())
				return NULL;
			SelfType = find->second;
			GetSDSymbolName(SelfType,NameBuffer,BufferLength);
			WCHAR DigBuf[10];
			for(unsigned int  i = 0; i <pArrayType->DimensionsSize;i++)
			{
				TSPrintf(DigBuf,WSTR("%d"),pArrayType->Dimensions[i].Size);
				TStrCat(NameBuffer,WSTR("["));
				TStrCat(NameBuffer,DigBuf);
				TStrCat(NameBuffer,WSTR("]"));
			}
			return NameBuffer;
		}
		break;
	case SD_BASECLASS:
		{
			SDUDTBASECLASS* pUdtBaseClassType= (SDUDTBASECLASS*)pType->Self;
			return 	GetSDSymbolName(pUdtBaseClassType->TypeID,NameBuffer,BufferLength);
		}		
	default:
		{
			if(pType->SDTypeInfile.uName.Name)
			{
				TStrCpy(NameBuffer,pType->SDTypeInfile.uName.Name);
			}
			else
			{
				TStrCpy(NameBuffer,WSTR("no name"));
			}
			return NameBuffer;
		}
	}
	return NULL;
}

/*
SDBASETYPENAME BaseTypeNameStruct[27]=
{
	{btNoType,"NoType"},
	{btVoid,"void"},
	{btChar,"char"},
	{btWChar,"wchar"},
	{btInt,"short"},
	{btInt1,"char"},
	{btInt2,"short"},
	{btInt4,"int"},
	{btInt8,"__int64"},
	{btUInt,"unsigned short int"},
	{btUint1,"unsigned char"},
	{btUint2,"unsigned short"},
	{btUint4,"unsigned int"},
	{btUint8,"unsigned __int64"},
	{btFloat,"float"},
	{btDouble,"double"},
	{btBCD,"BCD"},
	{btBool,"bool"},
	{btLong,"long"},
	{btULong,"unsigned long"},
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
*/
WCHAR* CSourceDebug::GetRegisterNameById(DWORD RegId)
{
	CV_HREG_eName RegName[]=
	{
		{WSTR("CV_REG_NONE     "),CV_REG_NONE     },
		{WSTR("CV_REG_AL       "),CV_REG_AL       },
		{WSTR("CV_REG_CL       "),CV_REG_CL       },
		{WSTR("CV_REG_DL       "),CV_REG_DL       },
		{WSTR("CV_REG_BL       "),CV_REG_BL       },
		{WSTR("CV_REG_AH       "),CV_REG_AH       },
		{WSTR("CV_REG_CH       "),CV_REG_CH       },
		{WSTR("CV_REG_DH       "),CV_REG_DH       },
		{WSTR("CV_REG_BH       "),CV_REG_BH       },
		{WSTR("CV_REG_AX       "),CV_REG_AX       },
		{WSTR("CV_REG_CX       "),CV_REG_CX       },
		{WSTR("CV_REG_DX       "),CV_REG_DX       },
		{WSTR("CV_REG_BX       "),CV_REG_BX       },
		{WSTR("CV_REG_SP       "),CV_REG_SP       },
		{WSTR("CV_REG_BP       "),CV_REG_BP       },
		{WSTR("CV_REG_SI       "),CV_REG_SI       },
		{WSTR("CV_REG_DI       "),CV_REG_DI       },
		{WSTR("CV_REG_EAX      "),CV_REG_EAX      },
		{WSTR("CV_REG_ECX      "),CV_REG_ECX      },
		{WSTR("CV_REG_EDX      "),CV_REG_EDX      },
		{WSTR("CV_REG_EBX      "),CV_REG_EBX      },
		{WSTR("CV_REG_ESP      "),CV_REG_ESP      },
		{WSTR("CV_REG_EBP      "),CV_REG_EBP      },
		{WSTR("CV_REG_ESI      "),CV_REG_ESI      },
		{WSTR("CV_REG_EDI      "),CV_REG_EDI      },
		{WSTR("CV_REG_ES       "),CV_REG_ES       },
		{WSTR("CV_REG_CS       "),CV_REG_CS       },
		{WSTR("CV_REG_SS       "),CV_REG_SS       },
		{WSTR("CV_REG_DS       "),CV_REG_DS       },
		{WSTR("CV_REG_FS       "),CV_REG_FS       },
		{WSTR("CV_REG_GS       "),CV_REG_GS       },
		{WSTR("CV_REG_IP       "),CV_REG_IP       },
		{WSTR("CV_REG_FLAGS    "),CV_REG_FLAGS    },
		{WSTR("CV_REG_EIP      "),CV_REG_EIP      },
		{WSTR("CV_REG_EFLAGS   "),CV_REG_EFLAGS   },
		{WSTR("CV_REG_TEMP     "),CV_REG_TEMP     },
		{WSTR("CV_REG_TEMPH    "),CV_REG_TEMPH    },
		{WSTR("CV_REG_QUOTE    "),CV_REG_QUOTE    },
		{WSTR("CV_REG_PCDR3    "),CV_REG_PCDR3    },
		{WSTR("CV_REG_PCDR4    "),CV_REG_PCDR4    },
		{WSTR("CV_REG_PCDR5    "),CV_REG_PCDR5    },
		{WSTR("CV_REG_PCDR6    "),CV_REG_PCDR6    },
		{WSTR("CV_REG_PCDR7    "),CV_REG_PCDR7    },
		{WSTR("CV_REG_CR0      "),CV_REG_CR0      },
		{WSTR("CV_REG_CR1      "),CV_REG_CR1      },
		{WSTR("CV_REG_CR2      "),CV_REG_CR2      },
		{WSTR("CV_REG_CR3      "),CV_REG_CR3      },
		{WSTR("CV_REG_CR4      "),CV_REG_CR4      },
		{WSTR("CV_REG_DR0      "),CV_REG_DR0      },
		{WSTR("CV_REG_DR1      "),CV_REG_DR1      },
		{WSTR("CV_REG_DR2      "),CV_REG_DR2      },
		{WSTR("CV_REG_DR3      "),CV_REG_DR3      },
		{WSTR("CV_REG_DR4      "),CV_REG_DR4      },
		{WSTR("CV_REG_DR5      "),CV_REG_DR5      },
		{WSTR("CV_REG_DR6      "),CV_REG_DR6      },
		{WSTR("CV_REG_DR7      "),CV_REG_DR7      },
		{WSTR("CV_REG_GDTR     "),CV_REG_GDTR     },
		{WSTR("CV_REG_GDTL     "),CV_REG_GDTL     },
		{WSTR("CV_REG_IDTR     "),CV_REG_IDTR     },
		{WSTR("CV_REG_IDTL     "),CV_REG_IDTL     },
		{WSTR("CV_REG_LDTR     "),CV_REG_LDTR     },
		{WSTR("CV_REG_TR       "),CV_REG_TR       },
		{WSTR("CV_REG_PSEUDO1  "),CV_REG_PSEUDO1  },
		{WSTR("CV_REG_PSEUDO2  "),CV_REG_PSEUDO2  },
		{WSTR("CV_REG_PSEUDO3  "),CV_REG_PSEUDO3  },
		{WSTR("CV_REG_PSEUDO4  "),CV_REG_PSEUDO4  },
		{WSTR("CV_REG_PSEUDO5  "),CV_REG_PSEUDO5  },
		{WSTR("CV_REG_PSEUDO6  "),CV_REG_PSEUDO6  },
		{WSTR("CV_REG_PSEUDO7  "),CV_REG_PSEUDO7  },
		{WSTR("CV_REG_PSEUDO8  "),CV_REG_PSEUDO8  },
		{WSTR("CV_REG_PSEUDO9  "),CV_REG_PSEUDO9  },
		{WSTR("CV_REG_ST0      "),CV_REG_ST0      },
		{WSTR("CV_REG_ST1      "),CV_REG_ST1      },
		{WSTR("CV_REG_ST2      "),CV_REG_ST2      },
		{WSTR("CV_REG_ST3      "),CV_REG_ST3      },
		{WSTR("CV_REG_ST4      "),CV_REG_ST4      },
		{WSTR("CV_REG_ST5      "),CV_REG_ST5      },
		{WSTR("CV_REG_ST6      "),CV_REG_ST6      },
		{WSTR("CV_REG_ST7      "),CV_REG_ST7      },
		{WSTR("CV_REG_CTRL     "),CV_REG_CTRL     },
		{WSTR("CV_REG_STAT     "),CV_REG_STAT     },
		{WSTR("CV_REG_TAG      "),CV_REG_TAG      },
		{WSTR("CV_REG_FPIP     "),CV_REG_FPIP     },
		{WSTR("CV_REG_FPCS     "),CV_REG_FPCS     },
		{WSTR("CV_REG_FPDO     "),CV_REG_FPDO     },
		{WSTR("CV_REG_FPDS     "),CV_REG_FPDS     },
		{WSTR("CV_REG_ISEM     "),CV_REG_ISEM     },
		{WSTR("CV_REG_FPEIP    "),CV_REG_FPEIP    },
		{WSTR("CV_REG_FPEDO    "),CV_REG_FPEDO    },
		{WSTR("CV_REG_MM0      "),CV_REG_MM0      },
		{WSTR("CV_REG_MM1      "),CV_REG_MM1      },
		{WSTR("CV_REG_MM2      "),CV_REG_MM2      },
		{WSTR("CV_REG_MM3      "),CV_REG_MM3      },
		{WSTR("CV_REG_MM4      "),CV_REG_MM4      },
		{WSTR("CV_REG_MM5      "),CV_REG_MM5      },
		{WSTR("CV_REG_MM6      "),CV_REG_MM6      },
		{WSTR("CV_REG_MM7      "),CV_REG_MM7      },
		{WSTR("CV_REG_XMM0     "),CV_REG_XMM0     },
		{WSTR("CV_REG_XMM1     "),CV_REG_XMM1     },
		{WSTR("CV_REG_XMM2     "),CV_REG_XMM2     },
		{WSTR("CV_REG_XMM3     "),CV_REG_XMM3     },
		{WSTR("CV_REG_XMM4     "),CV_REG_XMM4     },
		{WSTR("CV_REG_XMM5     "),CV_REG_XMM5     },
		{WSTR("CV_REG_XMM6     "),CV_REG_XMM6     },
		{WSTR("CV_REG_XMM7     "),CV_REG_XMM7     },
		{WSTR("CV_REG_XMM00    "),CV_REG_XMM00    },
		{WSTR("CV_REG_XMM01    "),CV_REG_XMM01    },
		{WSTR("CV_REG_XMM02    "),CV_REG_XMM02    },
		{WSTR("CV_REG_XMM03    "),CV_REG_XMM03    },
		{WSTR("CV_REG_XMM10    "),CV_REG_XMM10    },
		{WSTR("CV_REG_XMM11    "),CV_REG_XMM11    },
		{WSTR("CV_REG_XMM12    "),CV_REG_XMM12    },
		{WSTR("CV_REG_XMM13    "),CV_REG_XMM13    },
		{WSTR("CV_REG_XMM20    "),CV_REG_XMM20    },
		{WSTR("CV_REG_XMM21    "),CV_REG_XMM21    },
		{WSTR("CV_REG_XMM22    "),CV_REG_XMM22    },
		{WSTR("CV_REG_XMM23    "),CV_REG_XMM23    },
		{WSTR("CV_REG_XMM30    "),CV_REG_XMM30    },
		{WSTR("CV_REG_XMM31    "),CV_REG_XMM31    },
		{WSTR("CV_REG_XMM32    "),CV_REG_XMM32    },
		{WSTR("CV_REG_XMM33    "),CV_REG_XMM33    },
		{WSTR("CV_REG_XMM40    "),CV_REG_XMM40    },
		{WSTR("CV_REG_XMM41    "),CV_REG_XMM41    },
		{WSTR("CV_REG_XMM42    "),CV_REG_XMM42    },
		{WSTR("CV_REG_XMM43    "),CV_REG_XMM43    },
		{WSTR("CV_REG_XMM50    "),CV_REG_XMM50    },
		{WSTR("CV_REG_XMM51    "),CV_REG_XMM51    },
		{WSTR("CV_REG_XMM52    "),CV_REG_XMM52    },
		{WSTR("CV_REG_XMM53    "),CV_REG_XMM53    },
		{WSTR("CV_REG_XMM60    "),CV_REG_XMM60    },
		{WSTR("CV_REG_XMM61    "),CV_REG_XMM61    },
		{WSTR("CV_REG_XMM62    "),CV_REG_XMM62    },
		{WSTR("CV_REG_XMM63    "),CV_REG_XMM63    },
		{WSTR("CV_REG_XMM70    "),CV_REG_XMM70    },
		{WSTR("CV_REG_XMM71    "),CV_REG_XMM71    },
		{WSTR("CV_REG_XMM72    "),CV_REG_XMM72    },
		{WSTR("CV_REG_XMM73    "),CV_REG_XMM73    },
		{WSTR("CV_REG_XMM0L    "),CV_REG_XMM0L    },
		{WSTR("CV_REG_XMM1L    "),CV_REG_XMM1L    },
		{WSTR("CV_REG_XMM2L    "),CV_REG_XMM2L    },
		{WSTR("CV_REG_XMM3L    "),CV_REG_XMM3L    },
		{WSTR("CV_REG_XMM4L    "),CV_REG_XMM4L    },
		{WSTR("CV_REG_XMM5L    "),CV_REG_XMM5L    },
		{WSTR("CV_REG_XMM6L    "),CV_REG_XMM6L    },
		{WSTR("CV_REG_XMM7L    "),CV_REG_XMM7L    },
		{WSTR("CV_REG_XMM0H    "),CV_REG_XMM0H    },
		{WSTR("CV_REG_XMM1H    "),CV_REG_XMM1H    },
		{WSTR("CV_REG_XMM2H    "),CV_REG_XMM2H    },
		{WSTR("CV_REG_XMM3H    "),CV_REG_XMM3H    },
		{WSTR("CV_REG_XMM4H    "),CV_REG_XMM4H    },
		{WSTR("CV_REG_XMM5H    "),CV_REG_XMM5H    },
		{WSTR("CV_REG_XMM6H    "),CV_REG_XMM6H    },
		{WSTR("CV_REG_XMM7H    "),CV_REG_XMM7H    },
		{WSTR("CV_REG_MXCSR    "),CV_REG_MXCSR    },
		{WSTR("CV_REG_EDXEAX   "),CV_REG_EDXEAX   },
		{WSTR("CV_REG_EMM0L    "),CV_REG_EMM0L    },
		{WSTR("CV_REG_EMM1L    "),CV_REG_EMM1L    },
		{WSTR("CV_REG_EMM2L    "),CV_REG_EMM2L    },
		{WSTR("CV_REG_EMM3L    "),CV_REG_EMM3L    },
		{WSTR("CV_REG_EMM4L    "),CV_REG_EMM4L    },
		{WSTR("CV_REG_EMM5L    "),CV_REG_EMM5L    },
		{WSTR("CV_REG_EMM6L    "),CV_REG_EMM6L    },
		{WSTR("CV_REG_EMM7L    "),CV_REG_EMM7L    },
		{WSTR("CV_REG_EMM0H    "),CV_REG_EMM0H    },
		{WSTR("CV_REG_EMM1H    "),CV_REG_EMM1H    },
		{WSTR("CV_REG_EMM2H    "),CV_REG_EMM2H    },
		{WSTR("CV_REG_EMM3H    "),CV_REG_EMM3H    },
		{WSTR("CV_REG_EMM4H    "),CV_REG_EMM4H    },
		{WSTR("CV_REG_EMM5H    "),CV_REG_EMM5H    },
		{WSTR("CV_REG_EMM6H    "),CV_REG_EMM6H    },
		{WSTR("CV_REG_EMM7H    "),CV_REG_EMM7H    },
		{WSTR("CV_REG_MM00     "),CV_REG_MM00     },
		{WSTR("CV_REG_MM01     "),CV_REG_MM01     },
		{WSTR("CV_REG_MM10     "),CV_REG_MM10     },
		{WSTR("CV_REG_MM11     "),CV_REG_MM11     },
		{WSTR("CV_REG_MM20     "),CV_REG_MM20     },
		{WSTR("CV_REG_MM21     "),CV_REG_MM21     },
		{WSTR("CV_REG_MM30     "),CV_REG_MM30     },
		{WSTR("CV_REG_MM31     "),CV_REG_MM31     },
		{WSTR("CV_REG_MM40     "),CV_REG_MM40     },
		{WSTR("CV_REG_MM41     "),CV_REG_MM41     },
		{WSTR("CV_REG_MM50     "),CV_REG_MM50     },
		{WSTR("CV_REG_MM51     "),CV_REG_MM51     },
		{WSTR("CV_REG_MM60     "),CV_REG_MM60     },
		{WSTR("CV_REG_MM61     "),CV_REG_MM61     },
		{WSTR("CV_REG_MM70     "),CV_REG_MM70     },
		{WSTR("CV_REG_MM71     "),CV_REG_MM71     },
	};
	int j = sizeof(RegName)/sizeof(RegName[0]);
	for(int i = 0; i < j;i++)
	if(RegId==RegName[i].id)
	return RegName[i].Name;
	return NULL;
}
void CSourceDebug::ReleaseSDType()
{
	SYMBOLLIST sl;
	SDTYPE* pType;
	DWORD i;
	PSDUDTTYPE pSDUdtType;
	PSDFUNCTIONITEM pSDFunctionItem;
	PSDENUMERATIONTYPE pEnum;
	//SDSymbolList::iterator BeginIt,EndIt;
	SD_SYMBOL_MAP::iterator BeginIt,EndIt;
	BeginIt = m_SymbolList.begin();EndIt=m_SymbolList.end();
	for(;BeginIt!=EndIt;BeginIt++)
	{			
		sl = (*BeginIt).first;
		pType = sl.type;		
		switch(pType->SDTypeInfile.Type) 
		{
		case SD_CLASS:
		case SD_STRUCT:
		case SD_UNION:
			pSDUdtType = (PSDUDTTYPE)&pType[1];
			if(pSDUdtType->pBaseClass.pBaseClassMember)
				delete []pSDUdtType->pBaseClass.pBaseClassMember;
			if(pSDUdtType->pData.pDataMember)
				delete []pSDUdtType->pData.pDataMember;
			if(pSDUdtType->pFunction.pFunctionMember)
				delete []pSDUdtType->pFunction.pFunctionMember;
			if(pSDUdtType->pFriend.pFriendMember)
				delete []pSDUdtType->pFriend.pFriendMember;
			if(pSDUdtType->pVTable.pVTableMember)
				delete []pSDUdtType->pVTable.pVTableMember;
			break;				
		case SD_ENUMERATION:
			pEnum = (PSDENUMERATIONTYPE)&pType[1];
			for(i = 0; i < pEnum->DataCount; i++)
			{
				if(pEnum->EnumerationDataMember[i].u.Name)
					delete []pEnum->EnumerationDataMember[i].u.Name;
			}			
			break;
		case SD_TYPEDEF:			
			break;
		case SD_REFERENCE:			
			break;
		case SD_POINTER:					
			break;
		case SD_FUNCTIONTYPE:			
			break;
		case SD_ARRAY:			
			break;
		case SD_BASECLASS:			
			break;
		case SD_THUNK:			
			break;
		case SD_BASIC:			
			break;
		case SD_MANAGED:			
			break;
		case SD_CUSTOM:			
			break;
		case SD_BLOCK:			
			break;
		case SD_VTABLE:
			break;
		default:			
			break;
		}
		if(pType->SDTypeInfile.uName.Name)
			delete []pType->SDTypeInfile.uName.Name;
		delete pType;
	}
	FUNCTION_ID_MAP::iterator FunctionBeginIt,FunctionEndIt;
	FunctionBeginIt = m_FuntionID.begin();
	FunctionEndIt = m_FuntionID.end();
	for(;FunctionBeginIt!=FunctionEndIt;FunctionBeginIt++)
	{
		pSDFunctionItem = (*FunctionBeginIt).first.pFuncItem;
		if(pSDFunctionItem->pBlock.pBlockTypeIdArray)
			delete pSDFunctionItem->pBlock.pBlockTypeIdArray;
		if(pSDFunctionItem->pData.pDataMember)
			delete pSDFunctionItem->pData.pDataMember;
		for(i = 0; i < pSDFunctionItem->LabelCounter;i++)
			if(pSDFunctionItem->pLabel.pLabelArray[i].uName.Name)
				delete []pSDFunctionItem->pLabel.pLabelArray[i].uName.Name;
		if(pSDFunctionItem->pLabel.pLabelArray)	
			delete []pSDFunctionItem->pLabel.pLabelArray;		
		delete []pSDFunctionItem->uName.Name;
		delete pSDFunctionItem;
	}
	m_FuntionID.clear();
	PUBLIC_SYMBOL_MAP::iterator FirstIt,SecondIt;
	FirstIt = m_PublicSymbolList.begin();
	SecondIt = m_PublicSymbolList.end();
	for(;FirstIt!=SecondIt;FirstIt++)
		if((*FirstIt).first.uName.Name)
			delete (*FirstIt).first.uName.Name;	
	m_PublicSymbolList.clear();
	m_TotalLineNumber.clear();
	ID_TO_COMPILAND_NAME_MAP::iterator CompilandFirstIt,CompilandSecondIt;
	CompilandFirstIt=m_IdToCompilandMap.begin();
	CompilandSecondIt=m_IdToCompilandMap.end();
	for(;CompilandFirstIt!=CompilandSecondIt;CompilandFirstIt++)
	{
		delete [] CompilandFirstIt->first.Name;
		delete CompilandFirstIt->second;
	}
	m_IdToCompilandMap.clear();	
	ID_TO_SOURCE_FILE_NAME_MAP::iterator SourceFileFirstIT,SourceFileSecondIT;
	SourceFileFirstIT = m_IdToSourceFileNameMap.begin();
	SourceFileSecondIT = m_IdToSourceFileNameMap.end();
	for(;SourceFileFirstIT!=SourceFileSecondIT;SourceFileFirstIT++)
	{
		if(SourceFileFirstIT->first.Name)
		{
			delete []SourceFileFirstIT->first.Name;			
		}
	}
	m_IdToSourceFileNameMap.clear();
	DATA_TAG_VECTOR::iterator DataBeginIT,DataEndIT;
	DataBeginIT = m_DataTagVector.begin();
	DataEndIT = m_DataTagVector.end();
	for(;DataBeginIT!=DataEndIT;DataBeginIT++)
		delete *DataBeginIT;
	if(m_PEFileName)
		delete []m_PEFileName;
	if(m_PDBFileName)
		delete []m_PDBFileName;	
	list<STIMPORTMODULENAME>::iterator IMNBeginIT,IMNEndIT;
	IMNBeginIT = m_ImportModuleNameList.begin();
	IMNEndIT = m_ImportModuleNameList.end();
	for(;IMNBeginIT!=IMNEndIT;IMNBeginIT++)
	{
		delete []IMNBeginIT->Name;
	}
	m_StaticDataMap.clear();
	m_ImportModuleNameList.clear();
	m_DataTagVector.clear();
	m_StaticDataMap.clear();
	m_ThisObjectPtrList.clear();
	m_BaseTypeID.clear();
	m_TempSymbolID.clear();
	m_String2IDMap.clear();
	m_ThunkIDMap.clear();
	m_UDTSymbolID.clear();
	m_PointerID.clear();
	m_ReferenceID.clear();
	m_FuncSymbolList.clear();
	m_TypeDefList.clear();
	m_BaseClassList.clear();
	m_FunctionRavList.clear();
	m_EnumList.clear();
	m_ArrayList.clear();
	m_UnnamedUdtList.clear();
	m_IdToSourceFileNameMap.clear();
	m_IdToCompilandMap.clear();
	m_IDToSymbolMap.clear();
	m_SymbolList.clear();
	m_StringIDVector.clear();
	m_TotalLineNumber.clear();
	m_VTablePublicSymbolList.clear();
	m_StringDumpBlockList.clear();
	m_IDToFunctionSymbolMap.clear();
	m_CurrentSourceFileIndex=0;
	m_CurrentCompilandIndex=0;
	m_CurrentDataSymbolIndex=0x1;
	m_CurrentFunctionSymbolIndex=0x1;
	m_CurrentSymbolIndex=0x1;
	m_DataTagVector.push_back(NULL);
	m_StringNameID=0;
	m_StringName=false;
}

bool CSourceDebug::LoadPESym(PCSTR pStrName)
{
	PUBLIC_SYMBOL_MAP::iterator FindIT;
	PSDPUBLICSYMBOL pSdPublicSymbol;
	int n,m;
	char szSymA[1024];
	SDPUBLICSYMBOL SdPublicSymbol;
	IMPORT_MODULE* pImportModule;
	CPEFile PEFile;
	STIMPORTMODULENAME stImportModuleName; 
	list<STIMPORTMODULENAME>::iterator ModuleNameIT;
	char* ImportModuleName;
	//char* pStrName = new char[TStrLen(wFileName)+1];
	//TStrCpy(pStrName,wFileName);
	if(PEFile.Open(pStrName)==false)
	{
		//delete []pStrName;
		return false;
	}
	//delete []pStrName;
	memset(&SdPublicSymbol,0,sizeof(SdPublicSymbol));
	SdPublicSymbol.IsImportEntry=true;
	for(n=0;n<PEFile.m_ImportModuleCount;n++)
	{
		pImportModule=&PEFile.m_ImportModule[n];
		stImportModuleName.Name=pImportModule->ModuleName;
		ModuleNameIT = find(m_ImportModuleNameList.begin(),m_ImportModuleNameList.end(),stImportModuleName);
		if(ModuleNameIT==m_ImportModuleNameList.end())
		{
			ImportModuleName = new char[TStrLen(pImportModule->ModuleName)+1];
			TStrCpy(ImportModuleName,pImportModule->ModuleName);
			stImportModuleName.Name = ImportModuleName;
			m_ImportModuleNameList.push_back(stImportModuleName);
		}
		else
		{
			ImportModuleName = (*ModuleNameIT).Name;
		}
		
		for(m=0;m<pImportModule->FuncCount;m++)
		{
			SdPublicSymbol.Rva = pImportModule->FuncList[m].ThunkAddr-PEFile.m_PEHead.ImageBase;
			FindIT = m_PublicSymbolList.find(SdPublicSymbol);
			if(FindIT==m_PublicSymbolList.end())
			{			
				TSPrintf(szSymA,"Import_%s_%s",pImportModule->ModuleName,pImportModule->FuncList[m].FuncName);
				SdPublicSymbol.uName.Name = new char[TStrLen(szSymA)+1];
				TStrCpy	(SdPublicSymbol.uName.Name,szSymA);
				SdPublicSymbol.Length=0;
				SdPublicSymbol.UndecoratedName.Name=ImportModuleName;
				//m_PublicSymbolList.insert(SdPublicSymbol,SdPublicSymbol.Rva);
				m_PublicSymbolList.insert(PUBLIC_SYMBOL_MAP::value_type(SdPublicSymbol,SdPublicSymbol.Rva));
			}else
			{
				pSdPublicSymbol=(PSDPUBLICSYMBOL)&(*FindIT).first;
				pSdPublicSymbol->IsImportEntry=true;
				pSdPublicSymbol->UndecoratedName.Name=ImportModuleName;
				//(*FindIT).first.IsImportEntry=true;
				//(*FindIT).first.UndecoratedName.Name=ImportModuleName;
			}
		}
		pImportModule++;
	}
	SdPublicSymbol.IsImportEntry=false;
	SdPublicSymbol.IsExportEntry=true;
	SdPublicSymbol.UndecoratedName.Name=NULL;
	for(n=0;n<PEFile.m_ExportFuncCount;n++)
	{
		SdPublicSymbol.Rva = PEFile.m_ExportFunc[n].Address-PEFile.m_PEHead.ImageBase;
		FindIT=m_PublicSymbolList.find(SdPublicSymbol);
		if(FindIT==m_PublicSymbolList.end())
		{			
			TStrCpy(szSymA,PEFile.m_ExportFunc[n].FuncName);
			SdPublicSymbol.uName.Name = new char[TStrLen(szSymA)+1];
			TStrCpy	(SdPublicSymbol.uName.Name,szSymA);
			SdPublicSymbol.Length=0;
			//m_PublicSymbolList.insert(SdPublicSymbol,SdPublicSymbol.Rva);
			m_PublicSymbolList.insert(PUBLIC_SYMBOL_MAP::value_type(SdPublicSymbol,SdPublicSymbol.Rva));
		}else
		{
			pSdPublicSymbol=(PSDPUBLICSYMBOL)&(*FindIT).first;
			pSdPublicSymbol->IsExportEntry=true;
			//(*FindIT).first.IsExportEntry=true;
		}
	}
	PEFile.Close();
	return true;
}
DWORD CSourceDebug::DumpFunctionDeclareToHeaderFile(SDFUNCTIONITEM* pFuncItem,CStrA &OutBuffer)
{
	return 0;
}

void CSourceDebug::InitDependencies()
{
	//SDSymbolList::iterator BeginIt,EndIt;
	SD_SYMBOL_MAP::iterator BeginIt,EndIt;
	PSDTYPE pType;
	BeginIt = m_SymbolList.begin();EndIt=m_SymbolList.end();
	for(;BeginIt!=EndIt;BeginIt++)
	{
		pType = (*BeginIt).first.type;
		switch(pType->SDTypeInfile.Type)
		{
		case SD_CLASS:
		case SD_STRUCT:
		case SD_UNION:
			MakeUDTDependencies(pType);
			break;
		}
	}
	return;
}

bool CSourceDebug::MakeUDTDependencies(PSDTYPE pType)
{
	DWORD i;
	list<DWORD>* pList = new list<DWORD>;
	list<DWORD>::iterator FindIt;
	PSDUDTDATAITEM pUdtDataItem;
	PSDARRAYTYPE pArrayType;
	PSDTYPE pDataType;
	PSDUDTTYPE pUdtType = (PSDUDTTYPE)&pType[1];

	for(i = 0; i < pUdtType->DataCounter; i++)
	{
		pUdtDataItem = GetSDDateTypeBySymbolID(pUdtType->pData.pDataMember[i]);
		if(pUdtDataItem==NULL)
			continue;
		pDataType = GetSDTypeBySymbolID(pUdtDataItem->TypeId);
local_001:		
		if(pDataType==NULL)
			continue;
		switch(pDataType->SDTypeInfile.Type) 
		{
		case SD_CLASS:
		case SD_STRUCT:
		case SD_UNION:
			FindIt = find(pList->begin(),pList->end(),pDataType->SDTypeInfile.Id);
			if(FindIt==pList->end())
			{
				pList->push_back(pDataType->SDTypeInfile.Id);
			}
			break;
		case SD_ARRAY:
			{
				pArrayType = (PSDARRAYTYPE)&pDataType[1];
				pDataType = GetSDTypeBySymbolID(pArrayType->TypeIDElement);
				goto local_001;
			}
		}
	}
	if(pList->size())
	{
		m_TypeDependenciesList.insert(TYPE_DEPENDENCIES_LIST::value_type(pType->SDTypeInfile.Id,pList));
	}
	else
	{
		delete pList;
	}
	return true;
}
bool CSourceDebug::DumpSDUDTTypeToHeaderFile(DWORD TypeID,CStrA& OutBuffer)
{
	list<DWORD>* pList;
	PSDCLASSTYPE pSDClassType;
	list<DWORD>::iterator BeginIt,EndIt;
	PSDTYPE pType;
	TYPE_DEPENDENCIES_LIST::iterator FindIT;
	
	pType = GetSDTypeBySymbolID(TypeID);
	
	//SLIST_HEADER
	if(TStrCmp(pType->SDTypeInfile.uName.Name,"_SLIST_HEADER")==0)
		pList=NULL;
	
	FindIT = m_TypeDependenciesList.find(TypeID);
	if(FindIT==m_TypeDependenciesList.end())
	{
		
		pSDClassType = (PSDCLASSTYPE)&pType[1];
		if(pSDClassType->IsUnnamed&&pSDClassType->IsNestedUnnamed)
			return true;
		DumpSDUDTTypeToHeaderFile(&pType->SDTypeInfile,OutBuffer);
		(*m_HeaderOutStream)<<OutBuffer;
		return true;
	}
	pList = FindIT->second;
	BeginIt = pList->begin();
	EndIt = pList->end();
	for(;BeginIt!=EndIt;BeginIt++)
	{
		DumpSDUDTTypeToHeaderFile(*BeginIt,OutBuffer);
	}
	pSDClassType = (PSDCLASSTYPE)&pType[1];
	if(pSDClassType->IsUnnamed&&pSDClassType->IsNestedUnnamed)
		return true;
	DumpSDUDTTypeToHeaderFile(&pType->SDTypeInfile,OutBuffer);
	(*m_HeaderOutStream)<<OutBuffer;
	return true;
}
bool CSourceDebug::DumpHeaderFile(char* HeaderFileName)
{
	PSDCLASSTYPE pSDClassType;
	PSDTYPE pType;
	CStrA UdtOutBuffer,TypedefOutBuffer,EnumOutBuffer;
	//SDSymbolList::iterator BeginIt,EndIt;
	SD_SYMBOL_MAP::iterator BeginIt,EndIt;
	list<DWORD>::iterator FindOutputIT;
	BeginIt = m_SymbolList.begin();EndIt=m_SymbolList.end();
	if(BeginIt==EndIt)
		return false;
	InitDependencies();
	m_HeaderOutStream = new ofstream;
	m_HeaderOutStream->open(HeaderFileName,ios_base::out | ios_base::trunc);
	for(;BeginIt!=EndIt;BeginIt++)
	{ 
		pType = (*BeginIt).first.type;
		switch(pType->SDTypeInfile.Type)
		{
		case SD_CLASS:
		case SD_STRUCT:
		case SD_UNION:
			pSDClassType = (PSDCLASSTYPE)&pType[1];
			if(pSDClassType->IsUnnamed&&pSDClassType->IsNestedUnnamed)
				continue;
			FindOutputIT = find(m_OutputTypeList.begin(),m_OutputTypeList.end(),pType->SDTypeInfile.Id);
			if(FindOutputIT!=m_OutputTypeList.end())
				continue;
			DumpSDUDTTypeToHeaderFile(pType->SDTypeInfile.Id,UdtOutBuffer);
			break;			
		case SD_TYPEDEF:
			DumpSDTypedefTypeToHeaderFile(&pType->SDTypeInfile,TypedefOutBuffer);
			break;
		case SD_ENUMERATION:
			DumpSDEnumTypeToHeaderFile(&pType->SDTypeInfile,EnumOutBuffer);
			break;
		}
	}
	m_HeaderOutStream->flush();
	delete m_HeaderOutStream;
	m_HeaderOutStream=NULL;
	ReleaseDependencies();
	return true;
}
void CSourceDebug::ReleaseDependencies()
{
	list<DWORD>* pList;
	TYPE_DEPENDENCIES_LIST::iterator BeginIT,EndIT;
	BeginIT = m_TypeDependenciesList.begin();
	EndIT = m_TypeDependenciesList.end();
	for(;BeginIT!=EndIT;BeginIT++)
	{
		pList = BeginIT->second;
		pList->clear();
		delete pList;
	}
	m_TypeDependenciesList.clear();
	return;
}
DWORD CSourceDebug::DumpSDEnumTypeToHeaderFile(SDTYPE* pType,CStrA &OutBuffer)
{
	return DumpSDEnumTypeToHeaderFile(&pType->SDTypeInfile,OutBuffer);
}
DWORD CSourceDebug::DumpSDTypedefTypeToHeaderFile(SDTYPE* pType,CStrA &OutBuffer)
{
	return DumpSDTypedefTypeToHeaderFile(&pType->SDTypeInfile,OutBuffer);
}
DWORD CSourceDebug::DumpSDUDTTypeToHeaderFile(SDTYPE* pType,CStrA& OutBuffer)
{
	return DumpSDUDTTypeToHeaderFile(&pType->SDTypeInfile,OutBuffer);
}

DWORD CSourceDebug::DumpSDEnumTypeToHeaderFile(SDTYPE_INFILE* SDTypeInfile ,CStrA &OutBuffer)
{
	char WriteBuffer[50];
	SDENUMERATIONTYPE* pEnumationType;
	DWORD WriteByteSize=0;
	(*m_HeaderOutStream)<< "enum " NTOSKRNLVER <<SDTypeInfile->uName.Name<<"\n{\n";
	pEnumationType = (SDENUMERATIONTYPE*)&SDTypeInfile[1];
	for(unsigned int i = 0; i < pEnumationType->DataCount; i++)	
	{
		(*m_HeaderOutStream)<<"\t"<<NTOSKRNLVER<<pEnumationType->EnumerationDataMember[i].u.Name<<"\t=";
		TSPrintf(WriteBuffer,"0x%08x\t,//%d\n",pEnumationType->EnumerationDataMember[i].Value,pEnumationType->EnumerationDataMember[i].Value);
		(*m_HeaderOutStream)<<WriteBuffer;
	}
	(*m_HeaderOutStream)<<"};\n";
	return WriteByteSize;
}
DWORD CSourceDebug::DumpSDTypedefTypeToHeaderFile(SDTYPE_INFILE* SDTypeInfile,CStrA& OutBuffer)
{
	bool bFunctionPointer=false;
	char OrgName[0x400];
	int OrgNameLen=sizeof(OrgName)-1;
	char TypeName[20]="\0";
	PSDTYPEDEFTYPE pSDTypeDef=(PSDTYPEDEFTYPE)&SDTypeInfile[1];
	PSDTYPE pSubType = GetSDTypeBySymbolID(pSDTypeDef->TypeID);
	PSDPOINTERTYPE pSDPointer;
	switch(pSubType->SDTypeInfile.Type)
	{
	case SD_STRUCT:
		TStrCpy(TypeName,"struct ");
		break;
	case SD_UNION:
		TStrCpy(TypeName,"union ");
		break;
	case SD_ENUMERATION:
		TStrCpy(TypeName,"enum ");
		break;
	case SD_POINTER:
		pSDPointer = (PSDPOINTERTYPE)&pSubType[1];
		pSubType = GetSDTypeBySymbolID(pSDPointer->TypeID);
		if(pSubType->SDTypeInfile.Type == SD_FUNCTIONTYPE)
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
			(*m_HeaderOutStream)<<"typedef "<<OrgName<<SDTypeInfile->uName.Name<<")"<<pFunc<<";"<<endl;
		}
		else
			(*m_HeaderOutStream)<<"typedef "<<TypeName<<OrgName<<" "<< SDTypeInfile->uName.Name<<";"<<endl;
		
	}
	else
		(*m_HeaderOutStream)<<"typedef "<<TypeName<<OrgName<<" "<< SDTypeInfile->uName.Name<<";"<<endl;
	
	return 0;
}

char* CSourceDebug::GetFuncParamBegin(char* FunctionPointerName)
{
	char* Name;
	int Sum = 0;
	int i;
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
void CSourceDebug::GetDataMemberFullName(IN DWORD DataID,bool HasParentName)
{

}
DWORD CSourceDebug::DumpSDUDTTypeToHeaderFile(SDTYPE_INFILE* SDTypeInfile,CStrA& OutBuffer)
{
	bool bArray=false;
	bool bFunctionPointer=false;
	bool bIsUnnamedUDT=false;
	DWORD PrevAccess;
	DWORD i,j;
	PSDTYPE pSubType;
	PSDFUNCTIONITEM pFuncItem;
	PSDUDTDATAITEM pUdtData;
	char* OrgName;
	PSDUDTBASECLASS pUdtBaseClassType;
	PSDUDTTYPE pUdtType = (PSDUDTTYPE)&SDTypeInfile[1];
	char FuncName[0x400];
	int FuncNameLen = sizeof(FuncName)-1;
	list<DWORD>::iterator FindOutputIT;
	OutBuffer.Empty();
	if(((PSDCLASSTYPE)&SDTypeInfile[1])->IsUnnamed==0)
	{
		FindOutputIT = find(m_OutputTypeList.begin(),m_OutputTypeList.end(),SDTypeInfile->Id);
		if(FindOutputIT!=m_OutputTypeList.end())
			return 0;
		m_OutputTypeList.push_back(SDTypeInfile->Id);
	}
	else
	{
		bIsUnnamedUDT=true;
	}
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
		OutBuffer+=NTOSKRNLVER;
		OutBuffer+=SDTypeInfile->uName.Name;
		if(strcmp("_HANDLE_TABLE_ENTRY",SDTypeInfile->uName.Name)==0)
			bIsUnnamedUDT=false;

	}
	OutBuffer+=" ";
	if(pUdtType->BaseClassCounter)
	{
		OutBuffer+=": ";
		for(i = 0,j=0; i < pUdtType->BaseClassCounter;i++)
		{
			pSubType = GetSDTypeBySymbolID(pUdtType->pBaseClass.pBaseClassMember[i]);
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
			OrgName = GetSDSymbolName(pUdtBaseClassType->TypeID);
			//(*m_HeaderOutStream)<<OrgName;
			OutBuffer+=OrgName;
			delete OrgName;
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
			PSDTYPE pSubType = GetSDTypeBySymbolID(pFuncItem->TypeID);		
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
		OFFSETMAP OffsetMap;
		pair<OFFSETMAP::iterator,bool> pr;
		MEMINFOLIST DataList;
		UNIONMEMBERMAP UnionMemberMap;
		UNIONMEMBERMAP::iterator UnionMemberMapIT;
		pair<UNIONMEMBERMAP::iterator,bool> pr2;
		DWORD dwLocation,dwOffset,dwDataLen,dwInfo;
		MEMINFOLIST::iterator FindIt,DataListBegin,DataListEnd,UnameBIt,UnameEIt;
		STUNIONHELP sht;
		for(i = 0; i < pUdtType->DataCounter; i++)
		{			
			pUdtData = m_DataTagVector[pUdtType->pData.pDataMember[i]];
			bIsUnnamedUDT=false;						
			{
				GetUDTDataMemberName(pUdtType->pData.pDataMember[i],DataName,dwOffset,dwLocation,dwDataLen);				
				FindIt = find(DataList.begin(),DataList.end(),MemberInfo(dwOffset));
				if(FindIt!=DataList.end())
				{
					dwInfo=FindIt->m_Index;
					dwInfo<<=16;//高16位是联合中第一个元素在结构中的位置，低16位是联合中相同偏移成员出现的次数
					pr = OffsetMap.insert(OFFSETMAP::value_type(dwOffset,dwInfo+1));
					if(pr.second==false)
					{
						pr.first->second++;
						UnionMemberMapIT = UnionMemberMap.find(dwOffset);
					}
					else
					{
						pr2 = UnionMemberMap.insert(map<DWORD,MEMINFOLIST>::value_type(dwOffset,MEMINFOLIST()));
						UnionMemberMapIT=pr2.first;
						UnionMemberMapIT->second.push_back(*FindIt);
					}
					UnionMemberMapIT->second.push_back(MemberInfo(DataName,dwOffset,dwLocation,pUdtData->Access,dwDataLen,i));
				}
				DataList.push_back(MemberInfo(DataName,dwOffset,dwLocation,pUdtData->Access,dwDataLen,i));
			}			
		}
		UnionMemberMapIT = UnionMemberMap.begin();
		OFFSETMAP Finish;
		UNIONHELPLIST HelpList;
		for(;UnionMemberMapIT!=UnionMemberMap.end();UnionMemberMapIT++)
		{
			InitUnameUDT(SDTypeInfile->Type, UnionMemberMapIT->first,DataList,UnionMemberMap,HelpList,Finish,true);
		}
		UNIONHELPLIST::iterator HLBIT;
		for(DataListBegin=DataList.begin();DataListBegin!=DataList.end();DataListBegin++)
		{
			for(HLBIT=HelpList.begin();HLBIT!=HelpList.end();HLBIT++)
			{
				if(HLBIT->Index==DataListBegin->m_Index)
				OutBuffer+=HLBIT->Str;
			}
			if(PrevAccess!=DataListBegin->m_Access)
			{
				switch(DataListBegin->m_Access)
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
				PrevAccess=DataListBegin->m_Access;
			}
			OutBuffer+=DataListBegin->m_Name;
		}		
		for(HLBIT=HelpList.begin();HLBIT!=HelpList.end();HLBIT++)
		{
			if(HLBIT->Index==0-1)
				OutBuffer+=HLBIT->Str;
		}
		for(UnionMemberMapIT=UnionMemberMap.begin();UnionMemberMapIT!=UnionMemberMap.end();UnionMemberMapIT++)
		{
			UnionMemberMapIT->second.clear();
		}
		UnionMemberMap.clear();
		Finish.clear();
		HelpList.clear();
		OffsetMap.clear();
		DataList.clear();
	}
	OutBuffer+="};\n";
	return 0;
}
bool CSourceDebug::HaveNestedUnameStruct(DWORD Offset,UNIONMEMBERMAP& UnionMemberMap,MEMINFOLIST& DataList,UNIONHELPLIST& HelpList,DWORD& LastIndex)
{
	DWORD i,j,Length=0,dwMaxMemberLen=0;
	bool bRet=false;
	UNIONMEMBERMAP::iterator UnionMemberMapIT;
	MEMINFOLIST::iterator UnameBIt,UnameEIt,FindIt;
	STUNIONHELP sht;
	UnionMemberMapIT=UnionMemberMap.find(Offset);
	if(UnionMemberMapIT==UnionMemberMap.end())
		return false;

	UnameBIt = UnionMemberMapIT->second.begin();
	i=UnameBIt->m_Index;
	dwMaxMemberLen = max(UnameBIt->m_DataLen,dwMaxMemberLen);
	UnameEIt = UnionMemberMapIT->second.end();	
	UnameBIt++;
	for(j=1;UnameBIt!=UnameEIt;UnameBIt++)//判断联合中的数据成员是否有为命名的结构
	{
		if(j + i != UnameBIt->m_Index)
		{
			sht.Index=i;
			sht.Str="struct\n{\n";
			HelpList.push_back(sht);
			sht.Index=UnameBIt->m_Index;
			sht.Str="};\n";
			HelpList.push_back(sht);
			i=UnameBIt->m_Index;
			j=1;
			bRet=true;
			FindIt=DataList.begin();
			for(;FindIt!=DataList.end();FindIt++)
			{
				if(FindIt->m_Index==i-1)
				{
					Length=FindIt->m_Offset+FindIt->m_DataLen-Offset;
				}
			}
			dwMaxMemberLen = max(Length,dwMaxMemberLen);
		}
		else
		{
			i=UnameBIt->m_Index;
		}
	}
	
	FindIt =DataList.end();
	FindIt--;
	UnameBIt--;
	if(UnameBIt->m_Index < FindIt->m_Index)
		LastIndex = UnameBIt->m_Index+1;
	else
		LastIndex = 0-1;
	if(FindIt->m_Index>UnameBIt->m_Index)//判断联合的最后一个成员是否和随后的成员组成 为命名结构
	{
		FindIt=DataList.begin();
		for(;FindIt!=DataList.end();FindIt++)
		{					
			if(FindIt->m_Index > UnameBIt->m_Index)
			{
				if(FindIt->m_Offset - Offset<dwMaxMemberLen)
					bRet=true;
				if(FindIt->m_Offset - Offset >=dwMaxMemberLen)
				{
					break;							
				}						
			}
		}
		if(bRet)
		{
			sht.Index=UnameBIt->m_Index;
			sht.Str="struct\n{\n";
			HelpList.push_back(sht);
			if(FindIt==DataList.end())
				sht.Index=-1;
			else
				sht.Index=FindIt->m_Index;
			sht.Str="};\n";
			HelpList.push_back(sht);
			LastIndex=sht.Index;
		}			
	}
	return bRet;
}

DWORD CSourceDebug::HaveNestedUnameUnion(DWORD Offset,UNIONMEMBERMAP& UnionMemberMap)
{
	DWORD StartIndex,EndIndex;
	UNIONMEMBERMAP::iterator UnionMemberMapIT;
	MEMINFOLIST::iterator UnameBIt,UnameEIt;
	if(UnionMemberMap.size()==1)
		return 0-1;
	UnionMemberMapIT=UnionMemberMap.find(Offset);
	UnameBIt = UnionMemberMapIT->second.begin();
	UnameEIt = UnionMemberMapIT->second.end();
	UnameEIt--;
	StartIndex=UnameBIt->m_Index;
	EndIndex=UnameEIt->m_Index;
	for(UnionMemberMapIT=UnionMemberMap.begin();UnionMemberMapIT!=UnionMemberMap.end();UnionMemberMapIT++)
	{
		if(UnionMemberMapIT->first!=Offset)
		{
			UnameBIt = UnionMemberMapIT->second.begin();
			UnameEIt = UnionMemberMapIT->second.end();
			UnameEIt--;
			if((UnameEIt->m_Index> StartIndex &&  UnameEIt->m_Index < EndIndex) || (UnameBIt->m_Index> StartIndex &&  UnameBIt->m_Index < EndIndex))
				return UnionMemberMapIT->first;
		}
	}
	return 0-1;
}
void CSourceDebug::InitUnameUDT(SDTYPEIDS TypeIDs, DWORD Offset,MEMINFOLIST& DataList,UNIONMEMBERMAP& UnionMemberMap,  UNIONHELPLIST& HelpList,OFFSETMAP& Finish,bool bFirst)
{
	UNIONMEMBERMAP::iterator UnionMemberMapIT;
	MEMINFOLIST::iterator UnameBIt,UnameEIt,FindIt;
	DWORD dwPrevOffset=Offset,dwOffset,dwMaxMemberLen=0,BitFieldCount,BitFieldBegin,BitFieldEnd;;;
	STUNIONHELP sht,sht2;
	bool bHaveNestedStruct=false;	
	DWORD LastIndex;
	MEMINFOLIST::iterator FindIT;
	pair<OFFSETMAP::iterator,bool> pr;
	UNIONHELPLIST::iterator TempIt,TempIt2;
	bool bAllBitField;
	pr = Finish.insert(OFFSETMAP::value_type(dwPrevOffset,dwPrevOffset));
	if(pr.second==false)
		return;
	
	dwOffset = HaveNestedUnameUnion(dwPrevOffset,UnionMemberMap);	
	if(dwOffset!=0-1)
		InitUnameUDT(TypeIDs,dwOffset,DataList,UnionMemberMap,HelpList,Finish,false);//如果有潜逃的 union 则继续归调用

	UnionMemberMapIT=UnionMemberMap.find(dwPrevOffset);
	bAllBitField=IsAllBitField(UnionMemberMapIT->second,BitFieldCount,BitFieldBegin,BitFieldEnd);
	if(bAllBitField==false && BitFieldCount >1)
	{
		sht.Index=BitFieldBegin;
		sht.Str="struct\n{\n";
		HelpList.push_back(sht);
		FindIt=DataList.end();
		FindIt--;
		if(FindIt->m_Index>BitFieldEnd)
			sht.Index=	BitFieldEnd+1;
		else
			sht.Index=	0-1;
		sht.Str="};\n";
		HelpList.push_back(sht);

	}
	
	bHaveNestedStruct = HaveNestedUnameStruct(dwPrevOffset,UnionMemberMap,DataList,HelpList,LastIndex);
			
	if(TypeIDs!=SD_UNION || bFirst==false || (bFirst==true && TypeIDs==SD_UNION && Offset))
	{		
		if(!bAllBitField)
		{
			UnionMemberMapIT=UnionMemberMap.find(dwPrevOffset);
			UnameBIt = UnionMemberMapIT->second.begin();
			UnameEIt = UnionMemberMapIT->second.end();
			
			
			sht.Index=UnameBIt->m_Index;
			sht.Str="union\n{\n";
			sht2.Index=UnameBIt->m_Index;
			TempIt = find(HelpList.begin(),HelpList.end(),sht2);
			if(TempIt!=HelpList.end())
			{
				TempIt2=TempIt;
				for(;TempIt!=HelpList.end();TempIt++)
				{
					if(TempIt->Index==UnameBIt->m_Index && TempIt->Str == "};\n")
					{
						TempIt2=TempIt;
						TempIt2++;
					}
				}
				CStrA ss1;
	
				if(TempIt2==HelpList.end())
					HelpList.push_back(sht);
				else
					HelpList.insert(TempIt2,sht);

			}
			else
				HelpList.push_back(sht);


			if(bHaveNestedStruct==false)
			{
				FindIt = DataList.end();
				FindIt--;
				UnameEIt = UnionMemberMapIT->second.end();
				UnameEIt--;
				if(UnameEIt->m_Index < FindIt->m_Index)
					LastIndex=UnameEIt->m_Index+1;
				else
					LastIndex=0-1;
			}
			sht.Index=LastIndex;
			sht.Str="};\n";
			HelpList.push_back(sht);
		}
		
	}	
}


bool CSourceDebug::IsAllBitField(MEMINFOLIST& pList,DWORD& BitFieldCount,DWORD& BitFieldBegin,DWORD& BitFieldEnd)
{
	MEMINFOLIST::iterator BeginIT;	
	bool bRet=true;
	BitFieldBegin=0-1;
	BitFieldEnd=0-1;
	BitFieldCount=0;
	for(BeginIT=pList.begin();BeginIT!=pList.end();BeginIT++)
	{
		if(BeginIT->m_Location!=LocIsBitField)
			bRet=false;
		else
		{
			if(BitFieldBegin==0-1)
				BitFieldBegin=BeginIT->m_Index;
			BitFieldEnd=BeginIT->m_Index;
			BitFieldCount++;		
		}
	}
	return bRet;
}
char* CSourceDebug::GetUDTFunctionMemberName(DWORD FuncID,OUT CStrA& NameBuffer)
{
	char FuncName[0x400];
	PSDFUNCTIONITEM pFuncItem;
	int FuncNameLen;
	pFuncItem = GetSDFunctionByID(FuncID);
	CODE_ASSERT(pFuncItem);
	bool bStatic = false;
	PSDFUNCTIONTYPE pFunctionType;
	PSDTYPE pSubType = GetSDTypeBySymbolID(pFuncItem->TypeID);		
	NameBuffer.Empty();
	FuncNameLen = sizeof(FuncName)-1;
	GetFunctionName(pFuncItem,FuncName,&FuncNameLen);
	if(pSubType->SDTypeInfile.Type==SD_FUNCTIONTYPE)
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
bool CSourceDebug::IsFunctionPointer(DWORD dwTypeID)
{
	PSDTYPE pType = GetSDTypeBySymbolID(dwTypeID);
	if(pType==NULL)
		return false;
	if(pType->SDTypeInfile.Type!=SD_POINTER)
		return false;
	return IsFunctionPointer(pType);
}
bool CSourceDebug::IsFunctionPointer(PSDTYPE pType)
{
	return IsFunctionPointer(&pType->SDTypeInfile);
}
bool CSourceDebug::IsFunctionPointer(PSDTYPE_INFILE SDTypeInfile)
{
	PSDTYPE pSubType;
	if(SDTypeInfile->Type!=SD_POINTER)
		return false;
	PSDPOINTERTYPE pPointerType = (PSDPOINTERTYPE)&SDTypeInfile[1];
	pSubType = GetSDTypeBySymbolID(pPointerType->TypeID);
	if(pSubType==NULL)
		return false;
	return pSubType->SDTypeInfile.Type==SD_FUNCTIONTYPE;
}
bool CSourceDebug::GetDataBitFieldInfo(IN DWORD DataID,OUT DWORD& TypeID,OUT DWORD& BitFieldCount,OUT DWORD& TypeLen)
{
	PSDUDTDATAITEM pUdtData;
	PSDTYPE pSubType;
	pUdtData = GetSDDateTypeBySymbolID(DataID);
	pSubType = GetSDTypeBySymbolID(pUdtData->TypeId);
	TypeLen = pSubType->SDTypeInfile.TypeSize;
	TypeID=pUdtData->TypeId;
	BitFieldCount = pUdtData->u.LOCISBITFIELD.Size;
	return pUdtData->Location == LocIsBitField;	
}
bool CSourceDebug::GetUDTDataOffsetAndLength(IN DWORD DataID,OUT DWORD& Offset,OUT DWORD& DataLen)
{
	PSDUDTDATAITEM pUdtData;
	PSDTYPE pSubType;
	pUdtData = GetSDDateTypeBySymbolID(DataID);
	pSubType = GetSDTypeBySymbolID(pUdtData->TypeId);
	if(pUdtData->Location==LocIsThisRel)
	{
		Offset=pUdtData->u.LOCISTHISREL.Offset;
	}
	if(pUdtData->Location==LocIsBitField)
	{
		Offset=pUdtData->u.LOCISBITFIELD.Offset;
	}
	DataLen=pUdtData->DataSize;
	return pUdtData->Location == LocIsThisRel || pUdtData->Location == LocIsBitField;	
}
char* CSourceDebug::GetUDTDataMemberName(IN DWORD DataID,OUT CStrA& NameBuffer,OUT DWORD& dwOffset,OUT DWORD& dwLocation,OUT DWORD& dwDataLen)
{
#define MAX_LENGTH_NAME (0x400)
	char ArrayTypeName[20];
	CStrA DataName;
	bool bArray=false;
	char NullChar=0;
	char TypeName[20];
	char* CallConvention;
	char* OrgDataName;
	char FuncNameBuf[MAX_LENGTH_NAME];
	char *FuncName=FuncNameBuf;
	int FuncNameLen;
	PSDUDTDATAITEM pUdtData;
	PSDTYPE pSubType;
	bool bFunctionPointer;
	bool bUnnamedUDT=false;
	
	NameBuffer.Empty();
	FuncNameLen = MAX_LENGTH_NAME-1;
	FuncName[0]=0;
	pUdtData = GetSDDateTypeBySymbolID(DataID);
	dwDataLen=pUdtData->DataSize;
	OrgDataName = pUdtData->uName.Name;
	GetSDSymbolName(pUdtData->TypeId,FuncName,&FuncNameLen);
	DataName.Empty();
	DataName=FuncName;
	if(pUdtData->Location == LocIsThisRel) 
	{
		NameBuffer.Format("/* off 0x%04x */\t",pUdtData->u.LOCISTHISREL.Offset);
		dwOffset=pUdtData->u.LOCISTHISREL.Offset;
	}
	if (pUdtData->Location == LocIsBitField)
	{
		NameBuffer.Format("/* off 0x%04x */\t",pUdtData->u.LOCISBITFIELD.Offset);
		dwOffset=pUdtData->u.LOCISBITFIELD.Offset;
	}
	if(pUdtData->Location == LocIsStatic)
	{
		NameBuffer+="static ";
		dwOffset=0-1;
	}
	dwLocation=pUdtData->Location;
	bFunctionPointer=false;
	CallConvention=NULL;
	pSubType = GetSDTypeBySymbolID(pUdtData->TypeId);
	TypeName[0]=0;
	ArrayTypeName[0]=0;
	bArray=false;
	if(pSubType)
	{
		switch(pSubType->SDTypeInfile.Type) 
		{
		case SD_POINTER:
			{
				PSDPOINTERTYPE pSDPointer=(PSDPOINTERTYPE)&pSubType[1];
				PSDFUNCTIONTYPE pFunctionProc;
				pSubType = GetSDTypeBySymbolID(pSDPointer->TypeID);
				if(pSubType->SDTypeInfile.Type==SD_FUNCTIONTYPE)
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
				pSubType= GetSDTypeBySymbolID(pSDArrayType->TypeIDElement);
				bArray=true;
				break;
			}
		case SD_CLASS:
		case SD_STRUCT:
		case SD_UNION:
			bUnnamedUDT = IsUnnamedUDT(pSubType->SDTypeInfile.Id);
			break;
		}
	}
	if(bUnnamedUDT)
	{
		CStrA OutBuffer;
		OutBuffer.Empty();
		int i;
		DumpSDUDTTypeToHeaderFile(&pSubType->SDTypeInfile,DataName);
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
			char buf[50];
			TSPrintf(buf,"%d",pUdtData->u.LOCISBITFIELD.Size);
			NameBuffer+=buf;
			TSPrintf(buf,"\t /* start bit %d */",pUdtData->u.LOCISBITFIELD.Position);
			NameBuffer+=buf;
		}
	}
	NameBuffer+=";\n";
	if(FuncName!=FuncNameBuf)
		delete []FuncName;
	return NULL;
}
bool CSourceDebug::IsUnnamedUDT(DWORD dwTypeID)
{
	PSDTYPE pType = GetSDTypeBySymbolID(dwTypeID);
	if(pType==NULL)
		return false;
	if(pType->SDTypeInfile.Type==SD_CLASS || pType->SDTypeInfile.Type==SD_STRUCT || pType->SDTypeInfile.Type==SD_UNION)
		if(((PSDCLASSTYPE)&pType[1])->IsUnnamed)
			return true;
	return false;
}
/*
char* CSourceDebug::GetArrayIndexBegin(char* pArrayName)
{
	return TStrChr(pArrayName,"[");
}
*/
void CSourceDebug::ReleaseIDiaSymbol()
{
	PSDTYPE pType;
	IDiaSymbol* Symbol;
	//SDSymbolList::iterator BeginIt,EndIt;
	SD_SYMBOL_MAP::iterator BeginIt,EndIt;
	BeginIt = m_SymbolList.begin();EndIt=m_SymbolList.end();
	for(;BeginIt!=EndIt;BeginIt++)
	{	
		pType = (*BeginIt).first.type;
		if(pType->Symbol)
		{
			Symbol = (IDiaSymbol*)pType->Symbol;
			pType->Symbol=NULL;
			Symbol->Release();
		}
	}
}

SDBASETYPENAME BaseTypeNameStructArray[27]=
{
	{btNoType,"NoType"},
	{btVoid,"void"},
	{btChar,"char"},
	{btWChar,"wchar"},
	{btInt,"short"},
	{btInt1,"char"},
	{btInt2,"short"},
	{btInt4,"int"},
	{btInt8,"__int64"},
	{btUInt,"unsigned short int"},
	{btUint1,"unsigned char"},
	{btUint2,"unsigned short"},
	{btUint4,"unsigned int"},
	{btUint8,"unsigned __int64"},
	{btFloat,"float"},
	{btDouble,"double"},
	{btBCD,"BCD"},
	{btBool,"bool"},
	{btLong,"long"},
	{btULong,"unsigned long"},
	{btCurrency,"Currency"},
	{btDate,"date"},
	{btVariant,"variant"},
	{btComplex,"complex"},
	{btBit,"bit"},
	{btBSTR,"BSTR"},
	{btHresult,"HRESULT"},
};
