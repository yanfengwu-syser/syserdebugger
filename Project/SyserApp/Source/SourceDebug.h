#ifndef _SOURCEDEBUG_H_
#define _SOURCEDEBUG_H_

#include "../../../Addition/DiaSDK2005/include/dia2.h"
#include "../../../Addition/DiaSDK2005/include/cvconst.h"
#include "../../../Addition/SyserDebugger/SDSymbol.h"

#define STRINGTABLEDUMPBLOCKSIZE (0x100000)
#define NULLSYMBOLID  0
typedef int (*PACKEDSOURCEFILEFAILEDCALLBACK)(IN char *FileName,OUT char* NewFileName);
typedef void (*PFN_PROGRESS_SET_RANGE)(int Range);
typedef void (*PFN_PROGRESS_SET_POS)(int Pos);

typedef struct _DUMPSTRINGTABLEBLOCK
{
	void * BlockBaseAddress;
	DWORD BeginOffset;
	DWORD EndOffset;
}DUMPSTRINGTABLEBLOCK;
typedef list<DUMPSTRINGTABLEBLOCK> DUMP_STRING_LOCK_LIST;
typedef list<IDiaSymbol*> ARRAY_DIA_SYMBOL_LIST;
typedef struct _STRINGOFTABLE
{
	char* String;
	_STRINGOFTABLE(char* str)
	{
		String=str;
	}
	bool operator<(const struct _STRINGOFTABLE dest)const
	{
		return TStrCmp(String,dest.String)<0;
	}
	inline operator char*()const
	{
		return String;
	}
}STRINGOFTABLE;
typedef map<STRINGOFTABLE,DWORD> STRING_TO_ID_MAP;
typedef struct _CV_HREG_eName
{
	WCHAR* Name;
	DWORD id;
}CV_HREG_eName;
#define SDTYPE_DUMP_DELT sizeof(SDTYPE)-MEMBER_OFFSET(SDTYPE,Size)

extern WCHAR *SymTagName[];
extern WCHAR*basetypename[];
extern WCHAR *datakindname[];
extern SDBASETYPENAME BaseTypeNameStructArray[27];
class CTempSymbol
{
	char *m_Name;
	SDTYPE* m_Sdtype;
public:
	CTempSymbol()
	{
		m_Name=NULL;
		m_Sdtype=NULL;
	}
	CTempSymbol(char *name,DWORD SymTag,DWORD ID)
	{
		m_Name=name;
		m_Sdtype=NULL;
	}

	bool operator <(const CTempSymbol& source)const
	{
		return (TStrCmp(m_Name,source.m_Name)<0);
	}
	void SetSDType(SDTYPE* type,char *Name=NULL)
	{
		m_Sdtype=type;
		if(Name)
			m_Name=Name;
	}
	SDTYPE* GetSDType(){return m_Sdtype;}
};

typedef struct _STATICDATA
{
	char* Name;
	DWORD Rva;
	bool operator<(const struct _STATICDATA dest)const
	{
		if(Rva<dest.Rva)
			return true;
		if(Rva==dest.Rva)
			return TStrCmp(Name,dest.Name)<0;
		return false;
	}
}STATICDATA;
typedef map<STATICDATA,DWORD> STATIC_DATA_MAP;
typedef map<CTempSymbol,DWORD> SYMBOL_ID_MAP;

typedef map<DWORD,SDTYPE*> ID_TO_SYMBOL_MAP;

typedef struct _NAMEANDIDPAIR
{
	char* Name;
	DWORD Id;
	bool operator<(const struct _NAMEANDIDPAIR dest)const
	{
		return TStrCmp(Name,dest.Name)<0;
	}
}NAMEANDIDPAIR,*PNAMEANDIDPAIR;
typedef map<NAMEANDIDPAIR,DWORD>ID_TO_SOURCE_FILE_NAME_MAP;

typedef map<NAMEANDIDPAIR,SDCOMPILAND*> ID_TO_COMPILAND_NAME_MAP;

typedef struct _PREDEFINEBASETYPE
{
	DWORD baseType;
	ULONGLONG Length;
	char Name[32];
}PREDEFINEBASETYPE,*PPREDEFINEBASETYPE;
typedef struct _SYMBOLBASETYPE
{
	DWORD baseType;
	ULONGLONG Length;
	bool operator <(const struct _SYMBOLBASETYPE dest)const
	{
		if(baseType<dest.baseType)
			return true;
		if(baseType==dest.baseType&& Length<dest.Length)
			return true;
		return false;
	}
}SYMBOLBASETYPE,*PSYMBOLBASETYPE;
typedef vector<SDUDTDATAITEM*> DATA_TAG_VECTOR;
typedef map <SYMBOLBASETYPE,DWORD> BASE_TYPE_ID_MAP;
typedef struct stSymbolList
{
	DWORD id;
	SDTYPE* type;
	bool operator<(const stSymbolList dest)const
	{
		return id < dest.id;
	}
	bool operator==(const stSymbolList dest)const
	{
		return id == dest.id;
	}
}SYMBOLLIST;

typedef list<SYMBOLLIST> SD_SYMBOL_LIST;

typedef map<SYMBOLLIST,DWORD> SD_SYMBOL_MAP;//SymbolMap;

typedef struct _SDCONSTVAR
{
	char* Name;
	union{
		DWORD Value;
		ULONGLONG llValue;
	}u;
	bool operator<(const struct _SDCONSTVAR dest)const
	{
		if(u.llValue<dest.u.llValue)
			return true;
		if(u.llValue==dest.u.llValue)
		{
			return TStrCmp(Name,dest.Name)<0;
		}
		return false;
	}
}SDCONSTVAR,*PSDCONSTVAR;
typedef map<SDCONSTVAR,int> CONST_VAR_MAP;
typedef map<DWORD,PSDFUNCTIONITEM> ID_TO_FUNCTION_SYMBOL_MAP;//ToFunctionSymbolMap;
typedef struct stObjectPtr
{
	DWORD dataKind;
	DWORD Register;
	DWORD DataId;
	SDUDTDATAITEM *pUdtDataItem;
	bool operator==(const struct stObjectPtr dest)const
	{
		if(dataKind==dest.dataKind&&Register==dest.Register)
			return true;
		return false;
	}
}THISOBJECTPTR;
typedef struct stFunctionID
{
	char* Name;
	DWORD Rva;
	PSDFUNCTIONITEM pFuncItem;

	bool operator<(const struct stFunctionID dest)const
	{
		if(Rva<dest.Rva)
			return true;
		if(Rva>dest.Rva)
			return false;
		return TStrCmp(Name,dest.Name)<0;
		
	}
}STFUNCTIONID,*PSTFUNCTIONID;
typedef struct _STIMPORTMODULENAME
{
	char* Name;
	bool operator ==(const struct _STIMPORTMODULENAME dest)const
	{
		return TStrICmp(Name,dest.Name)==0;
	}
}STIMPORTMODULENAME,*PSTIMPORTMODULENAME;
typedef list <SDLINE> LINE_LIST;
typedef map<DWORD,PSTFUNCTIONID> ID_FUNCTION_MAP;
typedef map<STFUNCTIONID,DWORD> FUNCTION_ID_MAP;
typedef list<THISOBJECTPTR> THIS_OBJECT_PTR_LIST;

typedef map <SDPUBLICSYMBOL,DWORD> PUBLIC_SYMBOL_MAP ;
typedef long (__stdcall *PDLLGETCLASSOBJECT)(REFCLSID rclsid,REFIID riid,LPVOID * ppv);	

typedef map<DWORD,list<DWORD>*> TYPE_DEPENDENCIES_LIST;

class MemberInfo
{
public:
	MemberInfo(){}
	MemberInfo(CStrA Name,DWORD Offset,DWORD Location,DWORD Access,DWORD DataLen,DWORD Index)
	{
		m_Offset=Offset;
		m_Location=Location;
		m_Name=Name;
		m_Access=Access;		
		m_DataLen=DataLen;
		m_Index=Index;
	}
	MemberInfo(DWORD Offset)
	{
		m_Offset=Offset;		
	}
	MemberInfo(const MemberInfo& dest)
	{
		m_Offset=dest.m_Offset;
		m_Location=dest.m_Location;
		m_Name=dest.m_Name;
		m_Access=dest.m_Access;	
		m_DataLen=dest.m_DataLen;
		m_Index=dest.m_Index;
	}
	~MemberInfo(){}
	DWORD m_Offset;
	DWORD m_Location;
	DWORD m_Access;	
	DWORD m_DataLen;
	DWORD m_Index;
	CStrA m_Name;
	bool operator == (const MemberInfo& dest)const
	{		
		return m_Offset==dest.m_Offset;
	}
};
typedef list <MemberInfo> MEMINFOLIST;
typedef struct _STUNIONHELP
{
	DWORD Index;
	CStrA Str;
	bool operator ==(const struct _STUNIONHELP& dest)const
	{
		return Index==dest.Index;
	}
}STUNIONHELP,*P_STUNIONHELP;
typedef list<STUNIONHELP> UNIONHELPLIST;
typedef map<DWORD,DWORD> OFFSETMAP;
typedef map<DWORD,MEMINFOLIST> UNIONMEMBERMAP;

class CSourceDebug
{
	IDiaSymbol* m_GlobalScopeSymbol;
	IDiaSession* m_DiaSession;
	IDiaDataSource *m_DiaDataSource;
	IDiaEnumFrameData* m_GlobalEnumFrameData;
	IDiaEnumSegments* m_GlobalEnumSegments;
	PDLLGETCLASSOBJECT m_DiaDllGetClassObject;
	HMODULE m_DiaDllModule;
public:
	CSourceDebug();
	~CSourceDebug();
	bool Init();
	bool Release();
	void ReleaseIDiaSymbol();
	bool IsTranslated(IN PCSTR szModuleName,PSTR szSymbolFileName=NULL);
	bool TranslateSymbolFile(IN PCSTR szModuleName,OUT char *szSymbolFileName,bool bPackedSrcFile=true);
	bool PackedSourceFile(PCSTR pSymbolFileName,PACKEDSOURCEFILEFAILEDCALLBACK pCallBack);
	bool GetSymbolType(IDiaSymbol* Symbol,DWORD &TypeId,DWORD& symTag);
	bool InitEnumFrameDataTable();
	WCHAR * GetRegisterNameById(DWORD RegId);
	bool DumpFrameData();
	bool MakeSDSegment();
	bool CreateSDSymbolFile(const char *FileName,DWORD TimeDateStamp=0,DWORD PECheckSum=0,const char* pExeFileName=NULL);
	char *GetBaseTypeName1(DWORD BaseType,DWORD length=0);
	IDiaSymbol* FindSymbol(WCHAR *SymbolName,enum SymTagEnum SymTag=SymTagNull,IDiaSymbol* Symbol=NULL);
	IDiaSymbol* DumpSymTagPointerType(IDiaSymbol *Symbol,HANDLE pItem=NULL,DWORD *Depth=NULL);
	bool ListGlobalSymbols(bool IsPDBFile=false);		
	char *MakeFunctionTypeName(IDiaSymbol*Symbol);
	bool WriteSDSymbolFileCheckSum(const char *FileName);
	//	保存数据到文件
	DWORD DumpSDPublicSymbolToFile(DWORD* PublicSymbolNumbers=NULL);
	DWORD DumpSDThunkTypeToFile(SDTYPE* pType);
	DWORD DumpSDBasicTypeToFile(SDTYPE* pType);
	DWORD DumpSDUDTBaseClassTypeToFile(SDTYPE* pType);
	DWORD DumpSDArrayToFile(SDTYPE* pType);
	DWORD DumpSDFunctionTypeToFile(SDTYPE* pType);
	DWORD DumpSDFriendToFile(SDTYPE* pType);
	DWORD DumpSDPointerTypeToFile(SDTYPE* pType);
	DWORD DumpSDReferenceTypeToFile(SDTYPE* pType);
	DWORD DumpSDEnumTypeToFile(SDTYPE* pType);
	DWORD DumpSDTypedefTypeToFile(SDTYPE* pType);
	DWORD DumpSDUDTTypeToFile(SDTYPE* pType);	
	DWORD DumpSDManagedToFile(SDTYPE* pType);	
	DWORD DumpSDCustomToFile(SDTYPE* pType);
	DWORD DumpSDLineNumberToFile(DWORD* LineNumbers=NULL);
	DWORD DumpSDSourceFileToFile(DWORD* SourceFileCounter=NULL);	
	DWORD DumpSDBlockToFile(SDTYPE* pType);
	DWORD DumpSDVTableToFile(SDTYPE* pType);
	DWORD DumpSDCompilandToFile(DWORD* CompilandCounter=NULL);
	DWORD DumpSDDataToFile(SDUDTDATAITEM* pUdtDataItem);
	DWORD DumpSDFunctionToFile(PSDFUNCTIONITEM pType);
	//
	DWORD DumpSDTypeName(SDTYPE* pType);
	DWORD DumpSDTypeName(char* Name);
	DWORD DumpSDDataName(SDUDTDATAITEM* pUdtDataItem);
	// dump type to header file
	DWORD DumpSDEnumTypeToHeaderFile(SDTYPE_INFILE* SDTypeInfile,CStrA& OutBuffer);
	DWORD DumpSDTypedefTypeToHeaderFile(SDTYPE_INFILE* SDTypeInfile,CStrA& OutBuffer);
	DWORD DumpSDUDTTypeToHeaderFile(SDTYPE_INFILE* SDTypeInfile,CStrA& OutBuffer);
	DWORD DumpSDEnumTypeToHeaderFile(SDTYPE* pType,CStrA& OutBuffer);
	DWORD DumpSDTypedefTypeToHeaderFile(SDTYPE* pType,CStrA& OutBuffer);
	DWORD DumpSDUDTTypeToHeaderFile(SDTYPE* pType,CStrA& OutBuffer);
	DWORD DumpFunctionDeclareToHeaderFile(SDFUNCTIONITEM* pFuncItem,CStrA& OutBuffer);
	bool DumpHeaderFile(char* HeaderFileName);
	//类型项
	DWORD MakeSDEXE(IDiaSymbol* Symbol);
	DWORD MakeSDCompiland(IDiaSymbol* Symbol);
	DWORD MakeSDUDTType(IDiaSymbol* Symbol,DWORD* ReleaseFlags=NULL,SDTYPE** pTypeRetrun=NULL);
	DWORD MakeSDVTableShapType(IDiaSymbol* Symbol,DWORD* ReleaseFlags=NULL,SDTYPE** pTypeRetrun=NULL);
	DWORD MakeSDBaseType(IDiaSymbol* Symbol,DWORD* ReleaseFlags=NULL,SDTYPE** pTypeRetrun=NULL);
	void  MakePredefineSDBaseType();
	DWORD MakeSDType(IDiaSymbol* Symbol,DWORD* ReleaseFlags=NULL,SDTYPE** pTypeRetrun=NULL);
	DWORD MakeSDFunctionType(IDiaSymbol* Symbol,DWORD* ReleaseFlags=NULL,SDTYPE** pTypeRetrun=NULL);
	DWORD MakeSDPointerReferenceType(IDiaSymbol* Symbol,DWORD* ReleaseFlags=NULL,SDTYPE** pTypeRetrun=NULL);
	DWORD MakeSDPointerType(IDiaSymbol* Symbol,DWORD* ReleaseFlags=NULL,SDTYPE** pTypeRetrun=NULL);
	DWORD MakeSDReferenceType(IDiaSymbol* Symbol,DWORD* ReleaseFlags=NULL,SDTYPE** pTypeRetrun=NULL);
	DWORD MakeSDTypeDefType(IDiaSymbol* Symbol,DWORD* ReleaseFlags=NULL,SDTYPE** pTypeRetrun=NULL);
	DWORD MakeSDArrayType(IDiaSymbol* Symbol,DWORD* ReleaseFlags=NULL,SDTYPE** pTypeRetrun=NULL);
	DWORD MakeSDArrayType(IDiaSymbol* Symbol,DWORD PrevArrayTypeId,DWORD* ReleaseFlags=NULL,SDTYPE** pTypeRetrun=NULL);
	DWORD MakeSDFriend(IDiaSymbol* Symbol,DWORD* ReleaseFlags=NULL,SDTYPE** pTypeRetrun=NULL);
	DWORD MakeSDCustomType(IDiaSymbol* Symbol,DWORD* ReleaseFlags=NULL,SDTYPE** pTypeRetrun=NULL);
	DWORD MakeSDManagedType(IDiaSymbol* Symbol,DWORD* ReleaseFlags=NULL,SDTYPE** pTypeRetrun=NULL);
	DWORD MakeSDEnumType(IDiaSymbol* Symbol,DWORD* ReleaseFlags=NULL,SDTYPE** pTypeRetrun=NULL); 
	DWORD MakeSDThunk(IDiaSymbol* Symbol,DWORD* ReleaseFlags=NULL,SDTYPE** pTypeRetrun=NULL); 
	DWORD MakeSDBaseClassType(IDiaSymbol* Symbol,DWORD* ReleaseFlags=NULL,SDTYPE** pTypeRetrun=NULL);	
	DWORD MakeSDPublicSymbol(IDiaSymbol* Symbol,DWORD* ReleaseFlags=NULL,SDTYPE** pTypeRetrun=NULL);
	DWORD MakeSDBlock(IDiaSymbol *Symbol,list<DWORD>* BlockList=NULL);
	DWORD MakeSDVTable(IDiaSymbol* Symbol,DWORD* ReleaseFlags=NULL,SDTYPE** pTypeRetrun=NULL);
	//释放内存的函数
	void ReleaseSDType();
	//数据项
	DWORD MakeSDDataTagType(IDiaSymbol* Symbol,DWORD *ReleaseFlags=NULL,SDTYPE** pTypeRetrun=NULL);
	DWORD MakeSDFunction(IDiaSymbol* Symbol,DWORD *ReleaseFlags=NULL,SDTYPE** pTypeRetrun=NULL);
	//帮助函数
	bool SetUDTDataItem(SDUDTDATAITEM* UdtDataItem,IDiaSymbol* Symbol);
	WCHAR* GetSDSymbolName(SDTYPE* pType,WCHAR *NameBuffer,DWORD *BufferLength,DWORD* RetureLength=NULL);
	WCHAR* GetSDSymbolName(DWORD SymbolId,WCHAR *NameBuffer,DWORD *BufferLength);
	char *GetSDSymbolName(DWORD SymbolId);
	SDTYPE* GetSDTypeBySymbolID(DWORD SymbolID);
	SDUDTDATAITEM* GetSDDateTypeBySymbolID(DWORD DataId);
	char* GetFuncParamBegin(char* FunctionPointerName);
	char* GetArrayIndexBegin(char* pArrayName);
	char* GetFunctionName(IN PSDFUNCTIONITEM pFuncItem,OUT char* Buffer,IN DWORD BufferLen);
	char* GetUDTDataMemberName(IN DWORD DataID,OUT CStrA& NameBuffer,DWORD& dwOffset,DWORD& dwLocation,OUT DWORD& dwDataLen);
	char* GetUDTFunctionMemberName(DWORD FuncID,OUT CStrA& NameBuffer);
	bool IsFunctionPointer(DWORD dwTypeID);
	bool IsFunctionPointer(PSDTYPE pType);
	bool IsFunctionPointer(PSDTYPE_INFILE  SDTypeInfile);
	bool IsUnnamedSDType(char *name);	
	bool ModifyVTableName(char *Name);

	bool GetPEFileTimeDateStamp(IN const char* pPEFileName,OUT DWORD *TimeDateStamp,OUT DWORD* PECheckSum);
	PSDFUNCTIONITEM GetFunctionItemByID(IN DWORD FuncID);
	bool DumpSymTagPublicSymbol(IDiaSymbol* Symbol,HANDLE pItem=NULL);
	WCHAR *GetSymbolName(IN IDiaSymbol* Symbol,IN DWORD NameMaxLen,OUT WCHAR *Name);
	WCHAR *GetSymbolTypeName(IN IDiaSymbol* Symbol,IN DWORD NameMaxLen,OUT WCHAR *Name);
	bool CheckSymbolSymTagType(IDiaSymbol *Symbol,enum SymTagEnum TagType);
	bool OpenPdbFile(PCSTR filename,  IDiaDataSource** m_DiaDataSource, IDiaSession** m_DiaSession,  IDiaSymbol** m_GlobalScopeSymbol,OUT bool* IsPDBFile=NULL); 
	void ClosePdbFile();
	HRESULT NoRegCoCreate(PCSTR dllName,REFCLSID rclsid,REFIID riid,void **ppv);
	bool IsSymbolFile(PCSTR pFileName);
	bool GetPDBFileName(char* pSymbolFileName,char* pPDBFileName,DWORD* BufferLen=NULL);
	bool GetPEFileFullName(PCSTR FileName,char* pPEFileFullName,DWORD* BufferLen);
	bool TestFunction();
	bool LoadPESym(PCSTR wFileName);
	bool GetArrayList(IDiaSymbol* Symbol,ARRAY_DIA_SYMBOL_LIST* ArrayList);

	PFN_PROGRESS_SET_RANGE m_pfnSetRange;
	PFN_PROGRESS_SET_POS m_pfnSetPos;
	int m_ProgressStep;

	SYMBOL_ID_MAP m_TempSymbolID;
	BASE_TYPE_ID_MAP m_BaseTypeID;
	STATIC_DATA_MAP m_StaticDataMap;
	STRING_TO_ID_MAP m_String2IDMap;
	THIS_OBJECT_PTR_LIST m_ThisObjectPtrList;
	DATA_TAG_VECTOR m_DataTagVector;
	map <DWORD,SDTYPE*>m_ThunkIDMap;
	FUNCTION_ID_MAP m_FuntionID;
	ID_FUNCTION_MAP m_IDFuntionMap;
	SYMBOL_ID_MAP m_UDTSymbolID;
	SYMBOL_ID_MAP m_PointerID;
	SYMBOL_ID_MAP m_ReferenceID;
	SD_SYMBOL_LIST m_FuncSymbolList;
	SD_SYMBOL_LIST m_TypeDefList;
	SD_SYMBOL_LIST m_BaseClassList;
	list<DWORD> m_FunctionRavList;
	SD_SYMBOL_LIST m_EnumList;
	SD_SYMBOL_LIST m_ArrayList;
	SD_SYMBOL_LIST m_UnnamedUdtList;
	ID_TO_SOURCE_FILE_NAME_MAP m_IdToSourceFileNameMap;
	ID_TO_COMPILAND_NAME_MAP m_IdToCompilandMap;
	SYMBOL_ID_MAP::iterator m_TempSymbolIDIter;

	DWORD m_CurrentSymbolIndex;
	DWORD m_CurrentDataSymbolIndex;
	DWORD m_CurrentCompilandIndex;
	DWORD m_CurrentFunctionSymbolIndex;
	DWORD m_StringNameID;//=0;
	bool m_StringName;//=false;
	ID_TO_SYMBOL_MAP m_IDToSymbolMap;
	ID_TO_SYMBOL_MAP::iterator m_IDToSymbolMapIter;
	//SDSymbolList m_SymbolList;
	SD_SYMBOL_MAP m_SymbolList;
	char* m_StringTable;
	HANDLE m_hFile;
	DWORD m_FileOffset;
	DWORD m_StringTableOffset;
	DWORD m_StringIndex;
	DWORD m_CurrentSourceFileIndex;
	vector <DWORD>m_StringIDVector;
	LINE_LIST m_TotalLineNumber;
	PUBLIC_SYMBOL_MAP m_PublicSymbolList;
	PUBLIC_SYMBOL_MAP  m_VTablePublicSymbolList;
	DWORD m_CurrentStringTableMaxLen;
	DWORD m_StringTableBlockBeginOffset;
	DUMP_STRING_LOCK_LIST m_StringDumpBlockList;

	TYPE_DEPENDENCIES_LIST m_TypeDependenciesList;

	ID_TO_FUNCTION_SYMBOL_MAP m_IDToFunctionSymbolMap;
	list<STIMPORTMODULENAME> m_ImportModuleNameList;
	ofstream* m_HeaderOutStream;
	char * m_PEFileName;
	char * m_PDBFileName;

	char* GetSDSymbolName(PSDTYPE pType,OUT char *NameBuffer,INOUT int *BufferLength);
	char* GetSDSymbolName(IN PSDTYPE_INFILE pType,OUT char *NameBuffer,INOUT int *BufferLength);
	char* GetSDSymbolName(IN DWORD SymbolId,OUT char *NameBuffer,INOUT int *BufferLength);
	char* GetFunctionName(IN PSDFUNCTIONITEM pFuncItem,OUT char* NameBuffer,INOUT int* BufferLength);
	PSDFUNCTIONITEM GetSDFunctionByID(DWORD FunctionId);
	static SDCALLCONVENTIONPAIR m_CallConvention[24];
	static char* GetCallConventionName(DWORD dwType);
	void InitDependencies();
	bool IsUnnamedUDT(DWORD dwTypeID);
	void ReleaseDependencies();
	bool MakeUDTDependencies(PSDTYPE pType);
	list<DWORD> m_OutputTypeList;
	void GetDataMemberFullName(IN DWORD DataID,bool HasParentName=false);
	bool DumpSDUDTTypeToHeaderFile(DWORD TypeID,CStrA& OutBuffer);
	bool GetDataBitFieldInfo(IN DWORD DataID,OUT DWORD& TypeID,OUT DWORD& BitFieldCount,OUT DWORD& TypeLen);/* 获得位域型变量的一些信息 */ 
	bool GetUDTDataOffsetAndLength(IN DWORD DataID,OUT DWORD& Offset,OUT DWORD& DataLen);/* udt 数据成员的位移和长度 */ \
	bool IsAllBitField(MEMINFOLIST& pList,DWORD& BitFieldCount,DWORD& BitFieldBegin,DWORD& BitFieldEnd); /* 判断给定的一个UDT 类型的成员列表中是否全是位域类型的成员 */
	void InitUnameUDT(SDTYPE_INFILE* SDTypeInfile,MEMINFOLIST& DataList,UNIONMEMBERMAP& UnionMemberMap,  UNIONHELPLIST& HelpList);
	DWORD HaveNestedUnameUnion(DWORD Offset,UNIONMEMBERMAP& UnionMemberMap);//判断是否有嵌套的 未命名的 UDT
	bool HaveNestedUnameStruct(DWORD Offset,UNIONMEMBERMAP& UnionMemberMap,MEMINFOLIST& DataList,UNIONHELPLIST& HelpList,DWORD& LastIndex);
	void InitUnameUDT(SDTYPEIDS TypeIDs, DWORD Offset,MEMINFOLIST& DataList,UNIONMEMBERMAP& UnionMemberMap,  UNIONHELPLIST& HelpList,OFFSETMAP& Finish,bool bFirst);
};
DWORD GetBaseTypeIdByName(char*Name);

#endif /* _SOURCEDEBUG_H_ */