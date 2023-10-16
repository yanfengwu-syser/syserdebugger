#ifndef _SYSERSYMANALYZER_H_
#define _SYSERSYMANALYZER_H_
#include "../../Addition/SyserDebugger/SDSymbol.h"

enum
{
	RVA_FUNCTION_BODY,
	RVA_DATA_ITEM,
	RVA_PUBLIC_SYMBOL,
};

typedef struct _SYMNAMEIDKEY
{
	char* m_Name;
public:	
	bool operator <(const struct _SYMNAMEIDKEY& Dest)const
	{
		return TStrCmp(m_Name,Dest.m_Name)<0;
	}
	bool operator ==(const struct _SYMNAMEIDKEY& Dest)const
	{
		return TStrCmp(m_Name,Dest.m_Name)==0;
	}
}SYMNAMEIDKEY;
typedef TList<PSDLINE> SDLINELIST;
typedef TMap<SYMNAMEIDKEY,DWORD> SYM2NAME2IDMAP;
typedef struct _SDLINEINFO
{
	PSDLINE pLine;
	DWORD Number;//表示一个行号和几个RVA对应，主要是模板有这种现象，或者被优化后的函数
}SDLINEINFO,*PSDLINEINFO;
typedef TMap<DWORD,SDLINEINFO> LINENUMBERMAP;

class CSDSModule
{
	bool m_bInitOK;
	ULLSIZE m_SymFileSize;
	HANDLE m_hFileHandle;
	char** m_StrTable;
	char*	m_FileBuffer;
	SYM2NAME2IDMAP m_Sym2Name2IDMap;
	SYM2NAME2IDMAP m_DataSymName2IDMap;
	//const char* GetSymbolName(SYMORDATAINDEX Symbol)const;
public:
	PSDSYMBOLFILE	m_SDSymbolFile;
	TList<ULPOS>	m_BreakPointList;
	CIStrA			m_ModuleFileName;
	CIStrA			m_SymbolFileName;
	CDbgModule*		m_pCurDbgModule;	//指向当前进程的DbgModule，零时使用，有gpSyser->m_SyserUI.GetSDSModuleByXXXX装填
	int				m_MemoryUsed;
	DWORD			m_ParentPID;
	//SYMORDATAINDEXLIST m_SymbolMap;
	CSDSModule();
	~CSDSModule();
	static MODULE_ID GetSDSMouleID(PCSTR szSDSFileName);
	MODULE_ID GetModuleID();

	void	SetModuleFileName(PCSTR szFileName);
	DWORD GetTimeDateStamp()const;
	DWORD GetPECheckSum()const;
	void CreateName2IDMap();
	void DeleteName2IDMap();	
	void CreateDataName2IDMap();
	void DeleteDataName2IDMap();	
	bool LoadSymFile(IN PCSTR FileName);
	void SymRelocation(IN PSDSYMBOLFILE pSymbolFile);
	void UnloadSymFile();
	void* GetSymbolAddressBySymbolName(IN const char* SymbolName,OUT DWORD* SymbolLength=NULL);
	
	PSDUDTDATAITEM GetDataSymbol(IN unsigned int index)const;
	PSDTYPE_INFILE GetTypeSymbol(IN unsigned int index)const;
	PSDPUBLICSYMBOL GetPublicSymbol(IN unsigned int index)const;

	const char* GetSymbolNameByRVA(IN DWORD Rva);
	const char* GetDataName(IN PSDUDTDATAITEM pUdtDataItem)const;
	const char* GetTypeName(IN PSDTYPE_INFILE pSDType)const;
	const char* GetPublicSymbolName(IN PSDPUBLICSYMBOL pSDPublicSymbol)const;
	PSDSOURCEFILEID GetSourceFileList(OUT DWORD *SourceFileNum=NULL)const;
	PSDSOURCEFILEID GetSourceFileByID(IN DWORD SourceFileId)const;
	PSDSOURCEFILEID GetSourceFileByName(const char* SourceFileName)const;
	DWORD GetLineBySourceFileID(IN DWORD SourceFileId,INOUT SDLINELIST* Line)const;
	DWORD GetLineByRva(IN DWORD Rva,INOUT SDLINELIST* Line)const;
	DWORD GetLineFromRva(IN DWORD Rva,INOUT SDLINELIST* Line)const;
	PSDFUNCTIONITEM GetFunctionFromRav(DWORD Rva)const;
	DWORD GetLineBySourceFileID(IN DWORD SourceFileId,IN DWORD LineNum,INOUT SDLINELIST* Line)const;
	DWORD GetLineBySourceFileID(IN DWORD SourceFileId,INOUT LINENUMBERMAP* LineMap)const;	
	PSDLINE GetContiguityLineBySourceFileID(IN DWORD SourceFileId,IN DWORD LineNum)const;
	PSDTYPE_INFILE GetSymbolByName(const char* Name,bool bCase=true);
	PSDFUNCTIONITEM GetFunctionSymbolByName(const char*Name,bool bCase=true)const;
	char* GetFuncNameByRva(IN DWORD Rva)const;
	PSDCOMPILAND GetCompilandList(OUT DWORD* Count)const;
	PSDTYPE_INFILE* GetSymbolList(OUT DWORD* ItemCount)const;
	PSDPUBLICSYMBOL GetPublicSymbolList(OUT DWORD* Count=NULL);
	PSDUDTDATAITEM GetDataSymbolList(OUT DWORD* Count=NULL);
	PSDFUNCTIONITEM* GetFunctionSymbolList(OUT DWORD* Count);
	PCSTR GetPEFileFullName()const;
	PCSTR GetSymbolModuleName()const;
	PCSTR GetPDBFileName()const;
	const char* GetTypeNameByID(unsigned int id)const;
	PSDFUNCTIONITEM GetSDFunctionByID(IN DWORD Index)const;
	//PSDFUNCTIONITEM GetFunctionByLineNumber(IN DWORD FileId,IN DWORD LineNum)const;
	PSDFUNCTIONITEM GetFunctionSymbol(IN DWORD Index)const;
	char* GetUDTFunctionMemberName(DWORD FuncID,OUT CStrA& NameBuffer);
	DWORD DumpSDUDTTypeToHeaderFile(SDTYPE_INFILE* SDTypeInfile,CStrA& OutBuffer);
	char* GetUDTDataMemberName(IN DWORD DataID,OUT CStrA& NameBuffer);
	static SDCALLCONVENTIONPAIR m_CallConvention[24];
	static char* GetCallConventionName(DWORD dwType);
	bool IsFunctionPointer(DWORD dwTypeID);
	bool IsFunctionPointer(PSDTYPE pType);
	bool IsFunctionPointer(PSDTYPE_INFILE SDTypeInfile);
	char* GetFuncParamBegin(char* FunctionPointerName);
	char* GetFunctionName(IN PSDFUNCTIONITEM pFuncItem,OUT char* NameBuffer,INOUT int* BufferLength);
	bool IsUnnamedUDT(DWORD dwTypeID);
	char* GetSDSymbolName(IN DWORD TypeID,OUT char *NameBuffer,INOUT int *BufferLength);
	char* GetSDSymbolName(IN PSDTYPE_INFILE SDTypeInfile,OUT char *NameBuffer,INOUT int *BufferLength);
	DWORD DumpSDTypedefTypeToHeaderFile(SDTYPE_INFILE* SDTypeInfile,CStrA& OutBuffer);
	DWORD DumpSDEnumTypeToHeaderFile(SDTYPE_INFILE* SDTypeInfile ,CStrA &OutBuffer);
	PSDUDTDATAITEM GetUdtClassDataMemberByName(const char *Name,PSDTYPE_INFILE pType,DWORD* ThisOffset=NULL)const;
	PSDFUNCTIONITEM GetUdtClassFuncMemberByName(const char* Name,PSDTYPE_INFILE pType,bool bFullName=false)const;
	PSDFUNCTIONITEM GetFunctionByLineNumber(IN DWORD FileId,IN DWORD LineNum)const;
	PSDUDTDATAITEM GetDataSymbolByString(char* pStr,PSDFUNCTIONITEM pCurrentFunc,bool* IsFunc=NULL,DWORD* RetOffset=NULL)const;
	PSDUDTDATAITEM GetDataSymbolByString(char* pStr,DWORD FileId,DWORD LineNum,bool* IsFunc=NULL,DWORD* RetOffset=NULL)const;
	PSDUDTDATAITEM GetDataSymbolInFunctionByName(const char* pStr,PSDFUNCTIONITEM pFuncItem)const;
	PSDUDTDATAITEM GetDataSymbolByNameAndKind(const char* Name,int nDataKind)const;
	PSDUDTDATAITEM GetDataSymbolByNameAndLocation(char* Name,int nDataKind)const;
	PSDUDTDATAITEM GetDataSymbolByName(char* Name)const;
	char* GetEnumerationByValue(DWORD TypeIndex,ULONGLONG ullValue)const;
	bool CheckSDSymbolFileCheckSum();
	DWORD GetSourceFileCountInPackages()const;	
};

typedef TMap<MODULE_ID,CSDSModule> CSDSModuleMap;

DWORD GetBaseTypeIdByName(char*Name);
#endif /* _SYSERSYMANALYZER_H_ */