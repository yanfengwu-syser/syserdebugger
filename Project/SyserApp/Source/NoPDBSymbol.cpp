#include "StdAfx.h"
#include "NoPDBSymbol.h"
#include "AnalyseCom.h"
CNoPDBSymbol::CNoPDBSymbol()
{
	m_CurrentSourceFileIndex=0;
	m_CurrentCompilandIndex=0;
	m_PEFileName=NULL;
	m_PDBFileName=NULL;
	m_OnlyImportSymbol=false;
	m_OnlyExportSymbol=false;
}
CNoPDBSymbol::~CNoPDBSymbol()
{

}

bool CNoPDBSymbol::Init()
{
	DWORD Options;
	m_DbgHelpModule = LoadLibrary("DbgHelp.dll");
	if(m_DbgHelpModule==NULL)
		return false;
	LoadDbgHelpApi();
	if(m_SymInitialize(MY_PROCESS_HANDLE,NULL,FALSE)==false)
		return false;
	Options = m_SymGetOptions();
	m_SymSetOptions(0);
	return true;
}
bool CNoPDBSymbol::LoadDbgHelpApi()
{
	m_SymInitialize = (fpSymInitialize)GetProcAddress(m_DbgHelpModule,"SymInitialize");
	m_SymLoadModule64 = (fpSymLoadModule64)GetProcAddress(m_DbgHelpModule,"SymLoadModule64");
	m_SymEnumSymbols = (fpSymEnumSymbols)GetProcAddress(m_DbgHelpModule,"SymEnumSymbols");
	m_SymEnumTypes = (fpSymEnumTypes)GetProcAddress(m_DbgHelpModule,"SymEnumTypes");
	m_SymEnumLines = (fpSymEnumLines)GetProcAddress(m_DbgHelpModule,"SymEnumLines");
	m_SymUnloadModule64 = (fpSymUnloadModule64)GetProcAddress(m_DbgHelpModule,"SymUnloadModule64");
	m_SymCleanup = (fpSymCleanup)GetProcAddress(m_DbgHelpModule,"SymCleanup");
	m_SymGetTypeInfo = (fpSymGetTypeInfo)GetProcAddress(m_DbgHelpModule,"SymGetTypeInfo");
	m_SymGetTypeFromName = (fpSymGetTypeFromName)GetProcAddress(m_DbgHelpModule,"SymGetTypeFromName");
	m_SymSetOptions = (fpSymSetOptions)GetProcAddress(m_DbgHelpModule,"SymSetOptions");
	m_SymGetOptions = (fpSymGetOptions)GetProcAddress(m_DbgHelpModule,"SymGetOptions");
	m_UnDecorateSymbolName = (fpUnDecorateSymbolName)GetProcAddress(m_DbgHelpModule,"UnDecorateSymbolName");
	return true;
}
bool CNoPDBSymbol::ListGlobalSymbols(WCHAR* pExeFileName)
{
	bool bRet;
	char* FileName = new char[TStrLen(pExeFileName)+1];
	TStrCpy(FileName,pExeFileName);
	bRet = ListGlobalSymbols(FileName);
	delete []FileName;
	return bRet;
}
bool CNoPDBSymbol::ListGlobalSymbols(char* pExeFileName)
{
	bool bRet = false;
	bool bLineRet=false;
	m_LoadModule64 = m_SymLoadModule64(MY_PROCESS_HANDLE,NULL,pExeFileName,NULL,0,0);
	if(m_LoadModule64==0)
		return false;
	if(m_SymEnumSymbols(MY_PROCESS_HANDLE,m_LoadModule64,NULL,SymEnumSymbolsCallBackProc,this))
	{
		bRet=true;
	}
	/*
	if(m_SymEnumTypes(MY_PROCESS_HANDLE,m_LoadModule64,SymEnumTypesCallBackProc,this))
	{
		bRet=true;
	}
	if(m_SymEnumLines(MY_PROCESS_HANDLE,m_LoadModule64,NULL,NULL,SymEnumLinesCallBackProc,this))
	{
		bLineRet=true;
	}
	if(bLineRet)
	{
		CalculateLineLen();
	}
	OutputLineInfo();
	*/
	m_SymUnloadModule64(MY_PROCESS_HANDLE,m_LoadModule64);
	LoadPESym(pExeFileName);
	COMSYMBOL_MAP symmap;

	PUBLIC_SYMBOL_MAP::iterator FindIT;
	
	
	SDPUBLICSYMBOL SdPublicSymbol;
	
	memset(&SdPublicSymbol,0,sizeof(SdPublicSymbol));
	SdPublicSymbol.UndecoratedName.Name=NULL;
	
	COMSYMBOL_MAP::iterator BeginIT,EndIT;
	if(GetComSymbols(pExeFileName,symmap))
	{
		BeginIT=symmap.begin();
		EndIT=symmap.end();
		for(;BeginIT!=EndIT;BeginIT++)
		{
			SdPublicSymbol.Rva=BeginIT->second;
			SdPublicSymbol.uName.Name = new char[BeginIT->first.length()+1];
			TStrCpy(SdPublicSymbol.uName.Name,BeginIT->first.c_str());
			SdPublicSymbol.IsComVftable=1;
			m_PublicSymbolList.insert(PUBLIC_SYMBOL_MAP::value_type(SdPublicSymbol,SdPublicSymbol.Rva));
		}
		symmap.clear();
	}

	return true;
}
bool CNoPDBSymbol::LoadPESym(char* FileName)
{
	PUBLIC_SYMBOL_MAP::iterator FindIT;
	int n,m;
	char szSymA[1024];
	SDPUBLICSYMBOL SdPublicSymbol;
	PSDPUBLICSYMBOL pSdPublicSymbol;
	IMPORT_MODULE* pImportModule;
	STIMPORTMODULENAME stImportModuleName; 
	list<STIMPORTMODULENAME>::iterator ModuleNameIT;
	char* ImportModuleName;
	CPEFile PEFile;
	if(PEFile.Open(FileName)==false)
		return false;
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
				//TSPrintf(szSymA,"Import_%s_%s",pImportModule->ModuleName,pImportModule->FuncList[m].FuncName);
				TSPrintf(szSymA,"%s",pImportModule->FuncList[m].FuncName);
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
				//   (*FindIT).first.UndecoratedName.Name=ImportModuleName;
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
			//(*FindIT).first.IsExportEntry=true;
			pSdPublicSymbol->IsExportEntry=	true;
		}
	}
	PEFile.Close();
	return true;
}
BOOL CALLBACK SymEnumSymbolsCallBackProc(PSYMBOL_INFO pSymInfo,ULONG SymbolSize,PVOID UserContext)
{
	CNoPDBSymbol* pNoPDBSymbol = (CNoPDBSymbol*)UserContext;
	SDPUBLICSYMBOL SdPublicSymbol;
	char buf[1024];
	DWORD RetLen=0;
	DWORD64 Rva;
	WCHAR* Name=NULL;
	DWORD offset = 0;
	memset(&SdPublicSymbol,0,sizeof(SdPublicSymbol));
	if(TStrNICmp(pSymInfo->Name,"__imp_",6)==0)
	{
		offset = 6;
		TStrCpy(buf,"__imp_");
	}
	RetLen = pNoPDBSymbol->m_UnDecorateSymbolName(&pSymInfo->Name[offset],&buf[offset],sizeof(buf)-1-offset,0);
	if(RetLen)
	{
		SdPublicSymbol.uName.Name = new char[RetLen+1+offset];
		TStrCpy(SdPublicSymbol.uName.Name,buf);
	}else
	{
		SdPublicSymbol.uName.Name=new char [TStrLen(pSymInfo->Name)+1];
		TStrCpy(SdPublicSymbol.uName.Name,pSymInfo->Name);
	}

	Rva = pSymInfo->Address - pNoPDBSymbol->m_LoadModule64;
	SdPublicSymbol.Rva=*(DWORD*)&Rva;
	SdPublicSymbol.Length=pSymInfo->Size;
	pNoPDBSymbol->m_PublicSymbolList.insert(PUBLIC_SYMBOL_MAP::value_type(SdPublicSymbol,SdPublicSymbol.Rva));
	//pNoPDBSymbol.insert(PUBLIC_SYMBOL_MAP::value_type(SdPublicSymbol,SdPublicSymbol.Rva));
	return true;
}
BOOL CALLBACK SymEnumLinesCallBackProc(PSRCCODEINFO LineInfo,PVOID UserContext)
{
	DWORD64 Rva;
	CNoPDBSymbol* pNoPDBSymbol = (CNoPDBSymbol*)UserContext;
	NAMEANDIDPAIR SourceName2Id,CompilandName2Id;
	DWORD SourceFileID,CompilandID;
	PSDCOMPILAND pCompiland;
	ID_TO_SOURCE_FILE_NAME_MAP::iterator FindIT;
	ID_TO_COMPILAND_NAME_MAP::iterator CompilandFindIT;
	SDLINE SDLine;
	SourceName2Id.Name=LineInfo->FileName;
	FindIT = pNoPDBSymbol->m_IdToSourceFileNameMap.find(SourceName2Id);
	if(FindIT==pNoPDBSymbol->m_IdToSourceFileNameMap.end())
	{
		SourceName2Id.Name = new char[TStrLen(LineInfo->FileName)+1];
		TStrCpy(SourceName2Id.Name,LineInfo->FileName);
		SourceName2Id.Id = pNoPDBSymbol->m_CurrentSourceFileIndex++;
		SourceFileID = SourceName2Id.Id;
		pNoPDBSymbol->m_IdToSourceFileNameMap.insert(ID_TO_SOURCE_FILE_NAME_MAP::value_type(SourceName2Id,SourceFileID));
	}
	else
	{
		SourceFileID = FindIT->first.Id;
	}
	CompilandName2Id.Name=LineInfo->Obj;
	CompilandFindIT = pNoPDBSymbol->m_IdToCompilandMap.find(CompilandName2Id);	
	if(CompilandFindIT == pNoPDBSymbol->m_IdToCompilandMap.end())
	{
		pCompiland = new SDCOMPILAND;
		memset(pCompiland,0,sizeof(SDCOMPILAND));
		pCompiland->uName.Name = new char[TStrLen(LineInfo->Obj)+1];
		TStrCpy(pCompiland->uName.Name,LineInfo->Obj);
		pCompiland->CompilandId=pNoPDBSymbol->m_CurrentCompilandIndex++;
		CompilandID=pCompiland->CompilandId;
		pNoPDBSymbol->m_IdToCompilandMap.insert(ID_TO_COMPILAND_NAME_MAP::value_type(CompilandName2Id,pCompiland));
	}
	else
	{
		pCompiland = CompilandFindIT->second;
		CompilandID = pCompiland->CompilandId;
	}
	Rva = LineInfo->Address-pNoPDBSymbol->m_LoadModule64;
	SDLine.Rva = *(DWORD*)&Rva;
	SDLine.FileID=SourceFileID;
	SDLine.CompilandId=CompilandID;
	SDLine.LineNumber=LineInfo->LineNumber;
	pNoPDBSymbol->m_TotalLineNumber.push_back(SDLine);
	return true;
}


void CNoPDBSymbol::test(PSYMBOL_INFO pSymInfo,ULONG SymbolSize)
{
	CNoPDBSymbol* pNoPDBSymbol=this;
	GETTYPEINFOPARAM Param;
	int i = 1;
	
	if(m_SymGetTypeInfo(MY_PROCESS_HANDLE,pNoPDBSymbol->m_LoadModule64,pSymInfo->TypeIndex,TI_GET_ADDRESS,&Param.ul64Value))
	{
		i = 0;
	}
	if(m_SymGetTypeInfo(MY_PROCESS_HANDLE,pNoPDBSymbol->m_LoadModule64,pSymInfo->TypeIndex,TI_GET_ADDRESSOFFSET,&Param.dwValue))
	{
		i = 0;
	}
	if(m_SymGetTypeInfo(MY_PROCESS_HANDLE,pNoPDBSymbol->m_LoadModule64,pSymInfo->TypeIndex,TI_GET_ARRAYINDEXTYPEID,&Param.dwValue))
	{
		i = 0;
	}
	if(m_SymGetTypeInfo(MY_PROCESS_HANDLE,pNoPDBSymbol->m_LoadModule64,pSymInfo->TypeIndex,TI_GET_BASETYPE,&Param.dwValue))
	{
		i = 0;
	}
	if(m_SymGetTypeInfo(MY_PROCESS_HANDLE,pNoPDBSymbol->m_LoadModule64,pSymInfo->TypeIndex,TI_GET_BITPOSITION,&Param.dwValue))
	{
		i = 0;
	}
	if(m_SymGetTypeInfo(MY_PROCESS_HANDLE,pNoPDBSymbol->m_LoadModule64,pSymInfo->TypeIndex,TI_GET_CALLING_CONVENTION,&Param.dwValue))
	{
		i = 0;
	}

	if(m_SymGetTypeInfo(MY_PROCESS_HANDLE,pNoPDBSymbol->m_LoadModule64,pSymInfo->TypeIndex,TI_GET_CHILDRENCOUNT,&Param.dwValue))
	{
		i = 0;
	}
	if(m_SymGetTypeInfo(MY_PROCESS_HANDLE,pNoPDBSymbol->m_LoadModule64,pSymInfo->TypeIndex,TI_GET_CLASSPARENTID,&Param.dwValue))
	{
		i = 0;
	}
	if(m_SymGetTypeInfo(MY_PROCESS_HANDLE,pNoPDBSymbol->m_LoadModule64,pSymInfo->TypeIndex,TI_GET_COUNT,&Param.dwValue))
	{
		i = 0;
	}
	if(m_SymGetTypeInfo(MY_PROCESS_HANDLE,pNoPDBSymbol->m_LoadModule64,pSymInfo->TypeIndex,TI_GET_DATAKIND,&Param.dwValue))
	{
		i = 0;
	}
	if(m_SymGetTypeInfo(MY_PROCESS_HANDLE,pNoPDBSymbol->m_LoadModule64,pSymInfo->TypeIndex,TI_GET_LENGTH,&Param.ul64Value))
	{
		i = 0;
	}

	if(m_SymGetTypeInfo(MY_PROCESS_HANDLE,pNoPDBSymbol->m_LoadModule64,pSymInfo->TypeIndex,TI_GET_LEXICALPARENT,&Param.dwValue))
	{
		i = 0;
	}
	if(m_SymGetTypeInfo(MY_PROCESS_HANDLE,pNoPDBSymbol->m_LoadModule64,pSymInfo->TypeIndex,TI_GET_NESTED,&Param.dwValue))
	{
		i = 0;
	}
	if(m_SymGetTypeInfo(MY_PROCESS_HANDLE,pNoPDBSymbol->m_LoadModule64,pSymInfo->TypeIndex,TI_GET_OFFSET,&Param.dwValue))
	{
		i = 0;
	}
	if(m_SymGetTypeInfo(MY_PROCESS_HANDLE,pNoPDBSymbol->m_LoadModule64,pSymInfo->TypeIndex,TI_GET_SYMINDEX,&Param.dwValue))
	{
		i = 0;
	}
	if(pNoPDBSymbol->m_SymGetTypeInfo(MY_PROCESS_HANDLE,pNoPDBSymbol->m_LoadModule64,pSymInfo->TypeIndex,TI_GET_SYMNAME,&Param.wName))
	{
		i = 0;
		//delete Param.wName;
	}
	if(m_SymGetTypeInfo(MY_PROCESS_HANDLE,pNoPDBSymbol->m_LoadModule64,pSymInfo->TypeIndex,TI_GET_SYMTAG,&Param.dwValue))
	{
		i = 0;
	}
	if(m_SymGetTypeInfo(MY_PROCESS_HANDLE,pNoPDBSymbol->m_LoadModule64,pSymInfo->TypeIndex,TI_GET_THISADJUST,&Param.dwValue))
	{
		i = 0;
	}
	if(m_SymGetTypeInfo(MY_PROCESS_HANDLE,pNoPDBSymbol->m_LoadModule64,pSymInfo->TypeIndex,TI_GET_TYPEID,&Param.dwValue))
	{
		i = 0;
	}
	if(m_SymGetTypeInfo(MY_PROCESS_HANDLE,pNoPDBSymbol->m_LoadModule64,pSymInfo->TypeIndex,TI_GET_UDTKIND,&Param.dwValue))
	{
		i = 0;
	}
	if(m_SymGetTypeInfo(MY_PROCESS_HANDLE,pNoPDBSymbol->m_LoadModule64,pSymInfo->TypeIndex,TI_GET_VALUE,&Param.Variant))
	{
		i = 0;
	}
	if(m_SymGetTypeInfo(MY_PROCESS_HANDLE,pNoPDBSymbol->m_LoadModule64,pSymInfo->TypeIndex,TI_GET_VIRTUALBASECLASS,&Param.dwValue))
	{
		i = 0;
	}
	if(m_SymGetTypeInfo(MY_PROCESS_HANDLE,pNoPDBSymbol->m_LoadModule64,pSymInfo->TypeIndex,TI_GET_VIRTUALBASEPOINTEROFFSET,&Param.dwValue))
	{
		i = 0;
	}
	/*
	if(m_SymGetTypeInfo(MY_PROCESS_HANDLE,pNoPDBSymbol->m_LoadModule64,pSymInfo->TypeIndex,TI_GET_SYMINDEX,&Param.dwValue))
	{
		i = 0;
	}
	*/
}
BOOL CALLBACK SymEnumTypesCallBackProc(PSYMBOL_INFO pSymInfo,ULONG SymbolSize,PVOID UserContext)
{
	CNoPDBSymbol* pNoPDBSymbol = (CNoPDBSymbol*)UserContext;
	OutputDebugString("TYPE:");
	OutputDebugString(pSymInfo->Name);
	OutputDebugString("\n");
	return true;
}
void CNoPDBSymbol::Release()
{
	if(m_LoadModule64)
		m_SymUnloadModule64(MY_PROCESS_HANDLE,m_LoadModule64);
	m_LoadModule64=0;
	m_SymCleanup( MY_PROCESS_HANDLE ); 
}
void CNoPDBSymbol::CalculateLineLen()
{
	DWORD PrevRva,CurrentRva;
	
	LINE_LIST::iterator BeginIT,EndIT,PrevIT;
	if(m_TotalLineNumber.size()==0)
		return;
	m_TotalLineNumber.sort();
	BeginIT = m_TotalLineNumber.begin();
	PrevIT=BeginIT;
	EndIT=m_TotalLineNumber.end();
	if(BeginIT==EndIT)
		return;
	BeginIT++;
	PrevRva = BeginIT->Rva;
	for(;BeginIT!=EndIT;BeginIT++,PrevIT++)
	{
		CurrentRva = BeginIT->Rva;
		PrevIT->Len=CurrentRva-PrevRva;
		PrevRva=CurrentRva;
	}
	if(PrevIT!=EndIT)
		PrevIT->Len=1;
}
void CNoPDBSymbol::OutputLineInfo()
{
	char DisplayBuf[100];
	ID_TO_SOURCE_FILE_NAME_MAP::iterator SourceFileBeginIT,SourceFileEndIT;
	ID_TO_COMPILAND_NAME_MAP::iterator CompilandBeginIT,CompilandEndIT;
	LINE_LIST::iterator LineBeginIT,LineEndIT;
	SourceFileBeginIT = m_IdToSourceFileNameMap.begin();
	SourceFileEndIT = m_IdToSourceFileNameMap.end();
	for(;SourceFileBeginIT!=SourceFileEndIT;SourceFileBeginIT++)
	{
		OutputDebugString(SourceFileBeginIT->first.Name);
		OutputDebugString("\n");
	}
	CompilandBeginIT = m_IdToCompilandMap.begin();
	CompilandEndIT = m_IdToCompilandMap.end();
	for(;CompilandBeginIT!=CompilandEndIT;CompilandBeginIT++)
	{
		OutputDebugString(CompilandBeginIT->first.Name);
		OutputDebugString("\n");
	}
	LineBeginIT = m_TotalLineNumber.begin();
	LineEndIT = m_TotalLineNumber.end();
	for(;LineBeginIT!=LineEndIT;LineBeginIT++)
	{
		sprintf(DisplayBuf,"LineNumber =%04d %08x %08x %d %d\n",LineBeginIT->LineNumber,LineBeginIT->Rva,LineBeginIT->Len,LineBeginIT->CompilandId,LineBeginIT->FileID);
		OutputDebugString(DisplayBuf);
	}
}

bool CNoPDBSymbol::TranslateSymbolFile(IN PCSTR pExeFileName,OUT PSTR pSymbolFileName)
{
	int Len;
	bool bRet;
	WCHAR* pwszExeFileName,*pwszSymbolFileName=NULL;
	if(pSymbolFileName)
	{
		Len = TStrLen(pSymbolFileName)+1;
		pwszSymbolFileName = new WCHAR[512];
		AnsiToUnicode(pSymbolFileName,pwszSymbolFileName,Len);
	}
	Len = TStrLen(pExeFileName)+1;
	pwszExeFileName = new WCHAR[Len];
	AnsiToUnicode(pExeFileName,pwszExeFileName,Len);
	bRet = TranslateSymbolFile(pwszExeFileName,pwszSymbolFileName);
	if(pSymbolFileName)
	{
		TStrCpy(pSymbolFileName,pwszSymbolFileName);
		delete []pwszSymbolFileName;
	}
	delete []pwszExeFileName;
	return bRet;
}

bool CNoPDBSymbol::TranslateSymbolFile(IN WCHAR* pExeFileName,OUT WCHAR *pSymbolFileName)
{		
	char *pDestSymbolName;
	char *ExtFile;
	ULLSIZE FileLen;
	WCHAR NewExeFile[MAX_PATH];
	SDSYMBOLFILE SDSymbolFile;
	bool Valid;
	DWORD TimeDateStamp=0;
	DWORD PECheckSum=0;
	bool IsPDBFile=false;
	if(IsSymbolFile(pExeFileName,&Valid))
	{
		if(Valid)
		{
			if(pSymbolFileName)
				TStrCpy(pSymbolFileName,pExeFileName);
			return true;
		}
		DWORD Len=sizeof(NewExeFile)/sizeof(NewExeFile[0]);
		if(GetPEFileFullName(pExeFileName,NewExeFile,&Len)==false)
			return false;
		pExeFileName=NewExeFile;
		goto local_001;
	}
	else
	{	
local_001:
		char ModulePath[MAX_FN_LEN];
		DWORD ModulePathLen;
		WCHAR*pTempName;
		pDestSymbolName = new char[MAX_FN_LEN];
		ModulePathLen = GetModulePath(ModulePath);
		TStrCat(ModulePath,"Symbols");
		if(gpFileIO->IsDir(ModulePath)==false)
		{
			if(CreateDirectory(ModulePath,NULL)==false)
			{
				::MessageBox(NULL,"Fail to create directory!",ModulePath,MB_OK);
				delete []pDestSymbolName;
				return false;
			}
		}
		TStrCat(ModulePath,PATH_SEPARATOR_STR);
		pTempName=TGetFileExt(pExeFileName);
		TStrCat(ModulePath,pTempName);
		if(gpFileIO->IsDir(ModulePath)==false)
		{
			if(CreateDirectory(ModulePath,NULL)==false)
			{
				::MessageBox(NULL,"Fail to create directory!",ModulePath,MB_OK);
				delete []pDestSymbolName;
				return false;
			}
		}
		TStrCat(ModulePath,PATH_SEPARATOR_STR);
		TStrCat(ModulePath,TGetFileName(pExeFileName));
		ExtFile = TGetFileExt(ModulePath);
		TStrCpy(ExtFile,"sds");
		if(pSymbolFileName)
			TStrCpy(pSymbolFileName,ModulePath);
		TStrCpy(pDestSymbolName,ModulePath);
		DWORD PECheckSum;
		GetPEFileTimeDateStamp(pExeFileName,&TimeDateStamp,&PECheckSum);
		if(gpFileIO->IsFileExist(pDestSymbolName))
		{
			if(gpFileIO->ReadFromFile(pDestSymbolName,&SDSymbolFile,sizeof(SDSYMBOLFILE))==sizeof(SDSYMBOLFILE))
			{
				FileLen = gpFileIO->GetFileSize(pDestSymbolName);
				if(SDSymbolFile.FileLen==*(DWORD*)&FileLen&&SDSymbolFile.ModuleID.TimeDateStamp==TimeDateStamp)
				{
					delete []pDestSymbolName;
					return true;
				}
			}
		}
	}
	ListGlobalSymbols(pExeFileName);
	CreateSDSymbolFile(pDestSymbolName,TimeDateStamp,PECheckSum,pExeFileName);
	delete []pDestSymbolName;
	return true;
}



bool CNoPDBSymbol::CreateSDSymbolFile(char *FileName,DWORD TimeDateStamp,DWORD PECheckSum,WCHAR* pExeFileName)
{
	char *NullPage,*TempChar,*FileHeaderBuf;
	SDSYMBOLFILE* pSDSymbolFile;
	SDTYPE NullType;
	DWORD dwWriteLen,DataCounter,Temp,SymbolCounter,Index=0;
	DWORD* pSymbolOffsetArray;
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

	
	pSDSymbolFile->SymbolTotalNum=1;//因为欲留一个空的所以要加一个
	pSDSymbolFile->UnionSymbolTable.SymbolTableOffset=SDSF_FILE_HEADER_SIZE;
	pSDSymbolFile->ModuleID.TimeDateStamp = TimeDateStamp;
	pSDSymbolFile->ModuleID.OrgPECheckSum=PECheckSum;
	if(gpFileIO->CreateFile(FileName,&m_hFile)==false)
		return false;
	gpFileIO->WriteFile(m_hFile,FileHeaderBuf,SDSF_FILE_HEADER_SIZE);//写入文件头	
	m_FileOffset=SDSF_FILE_HEADER_SIZE;		
	SymbolCounter=pSDSymbolFile->SymbolTotalNum;	
	Size=0;
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

	////////////////////////////////////////////////////////
	//保存函数符号信息到文件
	////////////////////////////////////////////////////////

	////////////////////////////////////////////////////////
	//保存函数符号信息偏移表到文件
	////////////////////////////////////////////////////////

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
	
	////////////////////////////////////////////////////////
	//保存全局的符号表到文件
	////////////////////////////////////////////////////////
	pSDSymbolFile->UnionPublicSymbol.PublicSymbolOffset=m_FileOffset;
	dwWriteLen = DumpSDPublicSymbolToFile(&pSDSymbolFile->PublicSymbolCounter);
	m_FileOffset+=dwWriteLen;
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

	Temp = TStrLen(TGetFileName(pExeFileName))+1;
	if(FileHeaderLen<Temp)
	{
		pSDSymbolFile->uPEFileName.PEFileNameOffset = m_FileOffset;
		TStrCpy(NullPage,TGetFileName(pExeFileName));
		gpFileIO->WriteFile(m_hFile,NullPage,Temp);
		m_FileOffset += Temp;
		pSDSymbolFile->PEFileNameLen=Temp;
	}
	else
	{
		pSDSymbolFile->uPEFileName.PEFileNameOffset = SDSF_FILE_HEADER_SIZE-FileHeaderLen;
		TempChar=(char*)pSDSymbolFile;
		TStrCpy(&TempChar[SDSF_FILE_HEADER_SIZE-FileHeaderLen],TGetFileName(pExeFileName));
		FileHeaderLen-=Temp;
		pSDSymbolFile->PEFileNameLen=Temp;
	}
	Temp = TStrLen(pExeFileName)+1;
	if(FileHeaderLen<Temp)
	{
		pSDSymbolFile->uPDBFileName.PDBFileNameOffset = m_FileOffset;
		TStrCpy(NullPage,pExeFileName);
		gpFileIO->WriteFile(m_hFile,NullPage,Temp);
		m_FileOffset += Temp;
		pSDSymbolFile->PDBFileNameLen=Temp;
	}
	else
	{
		pSDSymbolFile->uPDBFileName.PDBFileNameOffset = SDSF_FILE_HEADER_SIZE-FileHeaderLen;
		TempChar=(char*)pSDSymbolFile;
		TStrCpy(&TempChar[SDSF_FILE_HEADER_SIZE-FileHeaderLen],pExeFileName);
		FileHeaderLen-=Temp;
		pSDSymbolFile->PDBFileNameLen=Temp;
	}
	if(pExeFileName)
	{
		Temp = TStrLen(pExeFileName)+1;
		if(FileHeaderLen<Temp)
		{
			TempChar = new char[Temp];
			TStrCpy(TempChar,pExeFileName);
			pSDSymbolFile->uPEFileFullName.PEFileFullNameOffset=m_FileOffset;
			gpFileIO->WriteFile(m_hFile,TempChar,Temp);
			m_FileOffset+=Temp;
			pSDSymbolFile->PEFileFullNameLen=Temp;
			delete []TempChar;
		}
		else
		{
			pSDSymbolFile->uPEFileFullName.PEFileFullNameOffset=SDSF_FILE_HEADER_SIZE-FileHeaderLen;
			TempChar=(char*)pSDSymbolFile;
			TStrCpy(&TempChar[SDSF_FILE_HEADER_SIZE-FileHeaderLen],pExeFileName);
			FileHeaderLen-=Temp;
			pSDSymbolFile->PEFileFullNameLen=Temp;
		}
	}
	pSDSymbolFile->FileLen=m_FileOffset;
	DWORD FileLen = gpFileIO->SetFilePointer(m_hFile,0,FILE_END);
	DWORD Tmp = *(DWORD*)&FileLen & 0xFFF;
	if(Tmp)
	{
		Tmp = 0x1000-Tmp;
		char *BufChar=new char[Tmp];
		if(BufChar)
		{
			memset(BufChar,0,Tmp);
			gpFileIO->WriteFile(m_hFile,BufChar,Tmp);
			FileLen = gpFileIO->SetFilePointer(m_hFile,0,FILE_END);
			pSDSymbolFile->FileLen = FileLen;
			delete []BufChar;
		}
		else
		{
			pSDSymbolFile->CheckSum=0;
		}
	}


	gpFileIO->WriteFile(m_hFile,pSDSymbolFile,SDSF_FILE_HEADER_SIZE,0);
	gpFileIO->CloseHandle(m_hFile);
	WriteSDSymbolFileCheckSum(FileName);
	delete []NullPage;
	delete []FileHeaderBuf;
	ReleaseResource();
	return true;
}

bool CNoPDBSymbol::WriteSDSymbolFileCheckSum(const char *FileName)
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

DWORD CNoPDBSymbol::ReleaseResource()
{
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
		delete []SourceFileFirstIT->first.Name;
	m_IdToSourceFileNameMap.clear();
	list<STIMPORTMODULENAME>::iterator IMNBeginIT,IMNEndIT;
	IMNBeginIT = m_ImportModuleNameList.begin();
	IMNEndIT = m_ImportModuleNameList.end();
	for(;IMNBeginIT!=IMNEndIT;IMNBeginIT++)
	{
		delete []IMNBeginIT->Name;
	}
	m_ImportModuleNameList.clear();
	return true;
}

DWORD CNoPDBSymbol::DumpSDPublicSymbolToFile(DWORD* PublicSymbolNumbers)
{		
	SDPUBLICSYMBOL* pPublicSymbol;
	SDPUBLICSYMBOL TmpPubSymbols;
	static bool stringname=false;
	static DWORD stringnameid=0;
	char string[]="`string'";
	bool bOK;
	DWORD ImportNum=0,ExportNum=0;
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
		bOK=false;
		if(m_OnlyImportSymbol||m_OnlyExportSymbol)
		{
			TmpPubSymbols = (*BeginIt).first;
			if(m_OnlyImportSymbol)
			{
				if(TmpPubSymbols.IsImportEntry)
					bOK=true;
			}
			if(m_OnlyExportSymbol)
			{
				if(TmpPubSymbols.IsExportEntry)
					bOK=true;
			}
		}
		else
		{
			bOK=true;
		}
		if(bOK==false)
			continue;
		pPublicSymbol[i]=(*BeginIt).first;
		if(TStrCmp(string,pPublicSymbol[i].uName.Name))
			pPublicSymbol[i].uName.StringTableIndex = DumpSDTypeName(pPublicSymbol[i].uName.Name);
		else
		{
			if(stringname)
			{
				k++;
				pPublicSymbol[i].uName.StringTableIndex=stringnameid;
			}
			else
			{
				pPublicSymbol[i].uName.StringTableIndex = DumpSDTypeName(pPublicSymbol[i].uName.Name);
				stringname=true;
				stringnameid=pPublicSymbol[i].uName.StringTableIndex;
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

DWORD CNoPDBSymbol::DumpSDTypeName(char* Name)
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
		m_String2IDMap.insert(STRING_TO_ID_MAP::value_type(StringOfTable,m_StringIndex));
		TStrCpy(m_StringTable-m_StringTableBlockBeginOffset+m_StringTableOffset,Name);
		m_StringIDVector.push_back(m_StringTableOffset);
		m_StringTableOffset=NameLen+1+m_StringTableOffset;
		m_StringIndex++;
	}
	else
		return FindIt->second;

	return m_StringIndex-1;
}


bool CNoPDBSymbol::IsSymbolFile(WCHAR* pFileName,OUT bool* Valid)
{
	ULLSIZE FileLen;
	SDSYMBOLFILE SDSymbolFile;
	char* pStrFileName = new char[TStrLen(pFileName)+1];
	TStrCpy(pStrFileName,pFileName);
	if(gpFileIO->IsFileExist(pStrFileName)==false)
		goto exit_local_001;
	if(gpFileIO->ReadFromFile(pStrFileName,&SDSymbolFile,sizeof(SDSymbolFile))!=sizeof(SDSymbolFile))
		goto exit_local_001;
	if(SDSymbolFile.Sig!=SYSER_DEBUG_SYMBOL_FILE_SIG)
		goto exit_local_001;
	if(Valid)
	{
		FileLen =gpFileIO->GetFileSize(pStrFileName);
		if(FileLen==SDSymbolFile.FileLen)
			*Valid=true;
		else
			*Valid=false;
	}
	delete []pStrFileName;
	return true;
exit_local_001:
	delete []pStrFileName;
	return false;
}
bool CNoPDBSymbol::IsSymbolFile(char* pFileName,OUT bool* Valid)
{
	ULLSIZE FileLen;
	SDSYMBOLFILE SDSymbolFile;
	char* pStrFileName = new char[TStrLen(pFileName)+1];
	TStrCpy(pStrFileName,pFileName);
	if(gpFileIO->IsFileExist(pStrFileName)==false)
		goto exit_local_001;
	if(gpFileIO->ReadFromFile(pStrFileName,&SDSymbolFile,sizeof(SDSymbolFile))!=sizeof(SDSymbolFile))
		goto exit_local_001;
	if(SDSymbolFile.Sig!=SYSER_DEBUG_SYMBOL_FILE_SIG)
		goto exit_local_001;
	if(Valid)
	{
		FileLen =gpFileIO->GetFileSize(pStrFileName);
		if(FileLen==SDSymbolFile.FileLen)
			*Valid=true;
		else
			*Valid=false;
	}
	delete []pStrFileName;
	return true;
exit_local_001:
	delete []pStrFileName;
	return false;
}

bool CNoPDBSymbol::GetPEFileFullName(char* pSymbolFileName,WCHAR* pPEFileFullName,DWORD* BufferLen)
{
	bool bRet;
	WCHAR* pwSymbolFileName = new WCHAR[TStrLen(pSymbolFileName)+1];
	TStrCpy(pwSymbolFileName,pSymbolFileName);
	bRet = GetPEFileFullName(pwSymbolFileName,pPEFileFullName,BufferLen);
	delete []pwSymbolFileName;
	return bRet;
}
bool CNoPDBSymbol::GetPEFileFullName(WCHAR* pSymbolFileName,WCHAR* pPEFileFullName,DWORD* BufferLen)
{
	bool Valid;
	char *FileName;
	char buf[SDSF_FILE_HEADER_SIZE];
	HANDLE hFile;
	PSDSYMBOLFILE pSDSymbolFile=(PSDSYMBOLFILE)buf;
	if(IsSymbolFile(pSymbolFileName,&Valid)==false)
		return false;
	if(Valid==false)
		return false;
	FileName = new char[TStrLen(pSymbolFileName)+1];
	TStrCpy(FileName,pSymbolFileName);

	if(gpFileIO->OpenFile(FileName,&hFile)==false)
	{
		delete []FileName;
		return false;
	}
	if(gpFileIO->ReadFile(hFile,pSDSymbolFile,sizeof(buf),0)!=sizeof(buf))
	{
		delete []FileName;
		gpFileIO->CloseHandle(hFile);
		return false;
	}
	delete []FileName;
	if(pSDSymbolFile->uPEFileFullName.PEFileFullNameOffset+pSDSymbolFile->PEFileFullNameLen <= sizeof(buf))
	{
		gpFileIO->CloseHandle(hFile);
		char* Name=(char*)pSDSymbolFile; 
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
		char *Name = new char[pSDSymbolFile->PEFileFullNameLen];
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
bool CNoPDBSymbol::GetPEFileTimeDateStamp(IN WCHAR* pPEFileName,OUT DWORD *TimeDateStamp,OUT DWORD *pPECheckSum)
{
	bool bRet;
	char* NewFileName;
	DWORD Len = TStrLen(pPEFileName);
	NewFileName =new char[Len+1];
	TStrCpy(NewFileName,pPEFileName);
	bRet = GetPEFileTimeDateStamp(NewFileName,TimeDateStamp,pPECheckSum);
	delete []NewFileName;
	return bRet;
}
bool CNoPDBSymbol::GetPEFileTimeDateStamp(IN char* pPEFileName,OUT DWORD *TimeDateStamp,OUT DWORD *pPECheckSum)
{
	char Buf[0x1000];
	MZHEAD* pMZHeader=(MZHEAD*)Buf;
	PE_HEAD* pPEHeader=NULL;	
	DWORD Offset;
	char* TempStr;
	ULLSIZE FileSize;
	if(TimeDateStamp)
		*TimeDateStamp=0;
	if(gpFileIO->IsFileExist(pPEFileName)==false)
		return false;
	FileSize = gpFileIO->GetFileSize(pPEFileName);

	if(gpFileIO->ReadFromFile(pPEFileName,Buf,sizeof(Buf))!=sizeof(Buf))
		return false;
	if(pMZHeader->Signature != MZFILE_SIGNATURE && pMZHeader->Signature != MZFILE_SIGNATURE1)
		return false;
	TempStr = (char*)&pPEHeader->TimeDateStamp+sizeof(pPEHeader->TimeDateStamp);
	Offset = *(DWORD*)&TempStr;
	if(pMZHeader->pfNewHead + Offset<=sizeof(Buf))
	{
		if(TimeDateStamp)
		{

			pPEHeader =(PE_HEAD*) &Buf[pMZHeader->pfNewHead];
			if(pPEHeader->Signature != PE_HEAD_SIGNATURE)
				return false;
			*TimeDateStamp = pPEHeader->TimeDateStamp;
			*pPECheckSum=pPEHeader->CheckSum;
			return true;
		}
	}
	else
	{
		HANDLE hFile;
		PE_HEAD PEHeader;
		if(gpFileIO->OpenFile(pPEFileName,&hFile)==false)
			return false;
		if(gpFileIO->ReadFile(hFile,&PEHeader,sizeof(PEHeader),pMZHeader->pfNewHead)!=sizeof(PEHeader))
		{
			gpFileIO->CloseHandle(hFile);
			return false;
		}
		if(PEHeader.Signature != PE_HEAD_SIGNATURE)
		{
			gpFileIO->CloseHandle(hFile);
			return false;
		}
		if(TimeDateStamp)
			*TimeDateStamp=PEHeader.TimeDateStamp;
		gpFileIO->CloseHandle(hFile);
		return true;
	}
	return false;
}
DWORD CNoPDBSymbol::DumpSDLineNumberToFile(DWORD* LineNumbers)
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
void CNoPDBSymbol::SetImportSymbols(bool bOnly)
{
	m_OnlyImportSymbol=bOnly;
}
void CNoPDBSymbol::SetExportSymbols(bool bOnly)
{
	m_OnlyExportSymbol=bOnly;
}