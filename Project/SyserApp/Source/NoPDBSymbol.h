#ifndef _NOPDBSYMBOL_H_
#define _NOPDBSYMBOL_H_

#define MY_PROCESS_HANDLE 0
#define IMAGEAPI_POINTER __stdcall
typedef BOOL
(IMAGEAPI_POINTER* fpSymInitialize)(
			  IN HANDLE   hProcess,
			  IN PSTR     UserSearchPath,
			  IN BOOL     fInvadeProcess
			  );
typedef DWORD64
(IMAGEAPI_POINTER* fpSymLoadModule64)(
				IN  HANDLE          hProcess,
				IN  HANDLE          hFile,
				IN  PSTR            ImageName,
				IN  PSTR            ModuleName,
				IN  DWORD64         BaseOfDll,
				IN  DWORD           SizeOfDll
				);
typedef BOOL
(IMAGEAPI_POINTER* fpSymEnumSymbols)(
			   IN HANDLE                       hProcess,
			   IN ULONG64                      BaseOfDll,
			   IN PCSTR                        Mask,
			   IN PSYM_ENUMERATESYMBOLS_CALLBACK    EnumSymbolsCallback,
			   IN PVOID                        UserContext
			   );
typedef BOOL
(IMAGEAPI_POINTER* fpSymEnumTypes)(
			 IN HANDLE                       hProcess,
			 IN ULONG64                      BaseOfDll,
			 IN PSYM_ENUMERATESYMBOLS_CALLBACK    EnumSymbolsCallback,
			 IN PVOID                        UserContext
			 );
/*
typedef struct _SRCCODEINFO 
{  
	DWORD SizeOfStruct;  
	PVOID Key;  
	DWORD64 ModBase;  
	CHAR Obj[MAX_PATH+1];  
	CHAR FileName[MAX_PATH+1];  
	DWORD LineNumber;  
	DWORD64 Address;
} SRCCODEINFO, *PSRCCODEINFO;
*/
typedef BOOL (CALLBACK *PSYM_ENUMLINES_CALLBACK)(PSRCCODEINFO LineInfo,PVOID UserContext);
typedef BOOL
(IMAGEAPI_POINTER* fpSymEnumLines)(
				  HANDLE hProcess,
				  ULONG64 Base,
				  PCSTR Obj,
				  PCSTR File,
				  PSYM_ENUMLINES_CALLBACK EnumSymbolsCallback,
				  PVOID UserContext
				  );

typedef BOOL
(IMAGEAPI_POINTER* fpSymUnloadModule64)(
				  IN  HANDLE          hProcess,
				  IN  DWORD64         BaseOfDll
				  );
typedef BOOL
(IMAGEAPI_POINTER* fpSymCleanup)(
		   IN HANDLE hProcess
		   );
typedef BOOL 
(IMAGEAPI_POINTER* fpSymGetTypeInfo)(
					HANDLE hProcess,
					DWORD64 ModBase,
					ULONG TypeId,
					IMAGEHLP_SYMBOL_TYPE_INFO GetType,
					PVOID pInfo
					);
typedef BOOL 
(IMAGEAPI_POINTER*fpSymGetTypeFromName)(
						HANDLE hProcess,
						ULONG64 BaseOfDll,
						PCSTR Name,
						PSYMBOL_INFO Symbol
						);
typedef DWORD (IMAGEAPI_POINTER*fpSymSetOptions)(
					DWORD SymOptions
					);
typedef DWORD
(IMAGEAPI_POINTER* fpSymGetOptions)(void);
typedef DWORD 
(IMAGEAPI_POINTER* fpUnDecorateSymbolName)(
						   PCSTR DecoratedName,
						   PSTR UnDecoratedName,
						   DWORD UndecoratedLength,
						   DWORD Flags
						   );

typedef union Param
{
	ULONG64 ul64Value;
	VARIANT Variant;
	DWORD dwValue;
	WCHAR* wName;
}GETTYPEINFOPARAM;

class CNoPDBSymbol
{
	bool m_OnlyImportSymbol;
	bool m_OnlyExportSymbol;
public:	
	friend BOOL CALLBACK SymEnumLinesCallBackProc(PSRCCODEINFO LineInfo,PVOID UserContext);
	friend BOOL CALLBACK SymEnumSymbolsCallBackProc(PSYMBOL_INFO pSymInfo,ULONG SymbolSize,PVOID UserContext);
	friend BOOL CALLBACK SymEnumTypesCallBackProc(PSYMBOL_INFO pSymInfo,ULONG SymbolSize,PVOID UserContext);
	DWORD m_CurrentCompilandIndex;
	DWORD m_CurrentSourceFileIndex;
	ID_TO_SOURCE_FILE_NAME_MAP m_IdToSourceFileNameMap;
	ID_TO_COMPILAND_NAME_MAP m_IdToCompilandMap;
	LINE_LIST m_TotalLineNumber;
	HMODULE m_DbgHelpModule;
	DWORD64 m_LoadModule64;
	char* m_StringTable;
	HANDLE m_hFile;
	DWORD m_FileOffset;
	DWORD m_StringTableOffset;
	DWORD m_StringIndex;
	vector <DWORD>m_StringIDVector;
	//PUBLIC_SYMBOL_LIST m_PublicSymbolList;
	PUBLIC_SYMBOL_MAP m_PublicSymbolList;
	DWORD m_CurrentStringTableMaxLen;
	DWORD m_StringTableBlockBeginOffset;
	DUMP_STRING_LOCK_LIST m_StringDumpBlockList;
	STRING_TO_ID_MAP m_String2IDMap;
	char * m_PEFileName;
	char * m_PDBFileName;
	list<STIMPORTMODULENAME> m_ImportModuleNameList;

	fpSymCleanup m_SymCleanup;
	fpSymLoadModule64 m_SymLoadModule64;
	fpSymEnumSymbols m_SymEnumSymbols;
	fpSymInitialize m_SymInitialize;
	fpSymEnumLines m_SymEnumLines;
	fpSymUnloadModule64 m_SymUnloadModule64;
	fpSymEnumTypes m_SymEnumTypes;
	fpSymGetTypeInfo m_SymGetTypeInfo;
	fpSymGetTypeFromName m_SymGetTypeFromName;
	fpSymSetOptions m_SymSetOptions;
	fpSymGetOptions m_SymGetOptions;
	fpUnDecorateSymbolName m_UnDecorateSymbolName;
	bool LoadDbgHelpApi();
	void OutputLineInfo();
	CNoPDBSymbol();
	~CNoPDBSymbol();
	bool Init();
	void Release();
	void CalculateLineLen();
	bool ListGlobalSymbols(IN WCHAR* pExeFileName);
	bool ListGlobalSymbols(IN char* pExeFileName);
	bool CreateSDSymbolFile(char *FileName,DWORD TimeDateStamp,DWORD PECheckSum,WCHAR* pExeFileName);
	DWORD DumpSDPublicSymbolToFile(DWORD* PublicSymbolNumbers=NULL);
	DWORD DumpSDTypeName(char* Name);
	bool TranslateSymbolFile(IN PCSTR pExeFileName,OUT PSTR pSymbolFileName);
	bool TranslateSymbolFile(IN WCHAR* pExeFileName,OUT WCHAR *pSymbolFileName);
	bool IsSymbolFile(char* pFileName,OUT bool* Valid);
	bool IsSymbolFile(WCHAR* pFileName,OUT bool* Valid);
	bool GetPEFileTimeDateStamp(IN char* pPEFileName,OUT DWORD *TimeDateStamp,OUT DWORD *pPECheckSum);
	bool GetPEFileTimeDateStamp(IN WCHAR* pPEFileName,OUT DWORD *TimeDateStamp,OUT DWORD *pPECheckSum);
	bool GetPEFileFullName(WCHAR* pSymbolFileName,WCHAR* pPEFileFullName,DWORD* BufferLen=NULL);
	bool GetPEFileFullName(char* pSymbolFileName,WCHAR* pPEFileFullName,DWORD* BufferLen=NULL);
	DWORD DumpSDLineNumberToFile(DWORD* LineNumbers=NULL);
	void test(PSYMBOL_INFO pSymInfo,ULONG SymbolSize);
	bool LoadPESym(char* FileName);
	DWORD ReleaseResource();
	void SetImportSymbols(bool bOnly);
	void SetExportSymbols(bool bOnly);
	bool WriteSDSymbolFileCheckSum(const char *FileName);
	
};
BOOL CALLBACK SymEnumSymbolsCallBackProc(PSYMBOL_INFO pSymInfo,ULONG SymbolSize,PVOID UserContext);
BOOL CALLBACK SymEnumLinesCallBackProc(PSRCCODEINFO LineInfo,PVOID UserContext);
#endif //_NOPDBSYMBOL_H_