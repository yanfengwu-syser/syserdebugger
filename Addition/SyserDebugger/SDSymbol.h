#ifndef _SYSER_DEBUG_SYMBOLS_H_
#define _SYSER_DEBUG_SYMBOLS_H_

#define SECTION_ALIGN_SIZE (16)
typedef struct _SDBaseTypeName
{	
	DWORD Type;
	char *Name;
}SDBASETYPENAME;

extern SDBASETYPENAME BaseTypeNameStruct[27];

enum SDTYPEIDS 
{
	SD_BASIC = 0,
	SD_POINTER,
	SD_REFERENCE,
	SD_ARRAY,
	SD_MANAGED,
	SD_CUSTOM,
	SD_ENUMERATION,
	SD_STRUCT,
	SD_CLASS,
	SD_UNION,
	SD_TYPEDEF,
	SD_FUNCTIONTYPE,
	SD_UDT,
	SD_BASECLASS,
	SD_FRIEND,
	SD_VTABLE,
	SD_THUNK,	
	SD_FUNCTIONDATA,
	SD_DATA,
	SD_BLOCK,
	SD_MAX_TYPEIDS,
};
typedef struct stSDThunk
{
	union
	{
		char *Name;
		DWORD StringTableIndex;
	}uName;
	DWORD thunkOrdinal;
	DWORD Rva;
}SDTHUNK,*PSDTHUNK;
typedef struct _SDCallConventionPair
{
	DWORD Type;
	char* Name;
}SDCALLCONVENTIONPAIR,*PSDCALLCONVENTIONPAIR;
typedef struct stSDPublicSymbol 
{
	union
	{
		char *Name;
		DWORD StringTableIndex;
	}uName;
	union
	{
		char *Name;
		DWORD StringTableIndex;
	}UndecoratedName;
	DWORD Rva;
	DWORD Length;
	DWORD LocationType:16;
	DWORD IsString:1;
	DWORD IsUnicodeString:1;
	DWORD IsExportEntry:1;
	DWORD IsImportEntry:1;
	DWORD IsMangedCode:1;
	DWORD IsMsil:1;
	DWORD IsFunction:1;
	DWORD IsInCode:1;
	DWORD IsVftable:1;
	DWORD IsComVftable:1;
	bool operator ==(const struct stSDPublicSymbol dest)const
	{
		return Rva==dest.Rva;
	}
	bool operator <(const struct stSDPublicSymbol dest)const
	{
		return Rva<dest.Rva;
	}
}SDPUBLICSYMBOL,*PSDPUBLICSYMBOL;
typedef struct stSDVTable
{
	DWORD TypeIdParentUDT;
	DWORD NumbersEntriesVTable;
}SDVTABLE,*PSDVTABLE;
typedef struct stSDSegment
{
	DWORD SegmentNumber;
	DWORD Offset;
	DWORD Length;
	DWORD RVA;
	DWORD IsRead:1;
	DWORD IsWrite:1;
	DWORD IsExecute:1;
	DWORD SectionNumber;
	ULONGLONG VA;
}SDSEGMENT,*PSDSEGMENT;
typedef struct stSDUDTDataItem
{
	DWORD DataId;
	DWORD DataSize;
	union{
		char *Name;
		DWORD StringTableIndex;
	}uName	;
	DWORD TypeIdParentUDT;
	DWORD TypeId;
	DWORD IsConstType:1;
	DWORD IsVolatileType:1;
	DWORD Access:14;
	DWORD Location:8;
	DWORD KindData:8;
	union _VALUEUNION{		
		struct stLocIsStatic
		{
			DWORD Rva;
		}LOCISSTATIC;
		struct stLocIsTLS 
		{
			DWORD AddressSection; 
			DWORD AddressOffset;
		}LOCISTLS;
		struct stLocIsRegRel
		{
			DWORD Offset;
			DWORD Register;
		}LOCISREGREL;
		struct stLocIsThisRel
		{
			DWORD Offset;
		}LOCISTHISREL;
		struct stLocIsEnregistered 
		{
			DWORD Register;
		}LOCISENREGISTERED;
		struct stBitField
		{
			DWORD Position;
			DWORD Size;
			DWORD Offset;
		}LOCISBITFIELD;
		struct stLocIsLot 
		{
			DWORD Slot;
		}LOCISLOT;
		struct stLocIslRel
		{
			LONG Offset;
		}LOCISLREL;
		struct stLocInMetaData 
		{
			DWORD Token;
		}LOCINMETADATA;
		union stLocIsConstant
		{
			LONGLONG llValue;
			DWORD Value;
		}LOCISCONSTSNT;
		//82600235 - 38 21
	}u;
}SDUDTDATAITEM,*PSDUDTDATAITEM;

typedef struct stSDFunctionDataItem
{
	DWORD size;
	SDUDTDATAITEM DataItemArray[1];
}SDFUNCTIONDATAITEM,*PSDFUNCTIONDATAITEM;

typedef struct stSDBlock
{	
	DWORD Rva;
	DWORD Len;
	DWORD DataCounter;
	DWORD pDataMember[1];
}SDBLOCK,*PSDBLOCK;

typedef struct _stSDTYPE_INFILE
{
	DWORD		Size;			//该数据类型在自己的符号文件中占的字节长度
	DWORD		Id;				//唯一的一个ID	
	DWORD		TypeSize;       //该数据类型的长度。例如 如果是 int 数据类型则长度为  sizeof(int)		
	union{
		char	*Name;			//数据类型的名字，udt 类型可能没有名字。
		DWORD	StringTableIndex;	
	}uName;	
	SDTYPEIDS	Type;			//SD_BASIC SD_POINTER SD_REFERENCE SD_ARRAY SD_MANAGED SD_CUSTOM
	//SD_ENUMERATION SD_STRUCT SD_CLASS SD_UNION SD_TYPEDEF SD_FUNCTION  SD_UDT
}SDTYPE_INFILE,*PSDTYPE_INFILE;
typedef struct stSDType
{
	void		*Self;	
	void		*Symbol;
	SDTYPE_INFILE SDTypeInfile;
}SDTYPE,*PSDTYPE;
typedef struct stSDCustomType
{
}SDCUSTOMTYPE,*PSDCUSTOMTYPE;
typedef struct stManagedType
{
}SDMANAGEDTYPE,*PSDMANAGEDTYPE;
typedef struct stSDBaseType
{
	DWORD BaseTypeID;
}SDBASETYPE,*PSDBASETYPE;
typedef struct stSDFunctionType 
{	
	DWORD ArgsCount:16;
	DWORD CallingConvention:16;
	DWORD TypeIDThisPointer;
	DWORD TypeIDReturnValue;
	DWORD ThisAdjust;
	DWORD TypeIDArgs[1];
}SDFUNCTIONTYPE,*PSDFUNCTIONTYPE;
typedef struct stSDLabelItem
{
	union{
		char *Name;
		DWORD MemberNameInStringTableIndex;
	}uName;
	DWORD Rva;
}SDLABELITEM,*PSDLABELITEM;
typedef struct sdFunctionItem
{
	union{
		char *Name;
		DWORD MemberNameInStringTableIndex;
	}uName;	
	DWORD Location:16;
	DWORD Access:8;
	DWORD IsVirtual:1;	
	DWORD IsPure:1;
	DWORD IsIntro:1;
	DWORD IsThunk:1;
	DWORD IsSystemExceptionHandling:1;
	DWORD IsCplusplusExceptionHandling:1;
	DWORD VirtualBaseOffset;
	DWORD Rva;
	DWORD DebugStart;
	DWORD DebugEnd;
	DWORD Size;	
	DWORD ID;
	DWORD TypeID;				//这是函数的类型
	DWORD TypeIDReturnValue;	//这是函数返回值的类型
	DWORD TypeIDParentUDT;	
	DWORD DataCounter;
	union{
		DWORD *pDataMember;
		DWORD DataMemberOffset;
	}pData;
	DWORD BlockCounter;
	union{
		DWORD* pBlockTypeIdArray;
		DWORD BlockOffset;
	}pBlock;
	DWORD LabelCounter;
	union{
		SDLABELITEM* pLabelArray;
		DWORD LabelOffset;
	}pLabel;
}SDFUNCTIONITEM,*PSDFUNCTIONITEM;

typedef struct stSDUDTFriend
{
	SDTYPEIDS Type;
	DWORD TypdeId;
}SDUDTFRIEND,*PSDUDTFRIEND;
typedef struct stSDUDTVirtualTable
{
	DWORD VTableSize;
	DWORD VTableRVA;
	DWORD VTBaseClassTypeID;
}SDUDTVIRTUALTABLE,*PSDUDTVIRTUALTABLE;

typedef struct stSDUDTType
{		
	DWORD BaseClassCounter;
	DWORD FriendCounter;
	DWORD DataCounter;
	DWORD TypeIDParentUDT;
	DWORD IsConstructor:1;
	DWORD IsScoped:1;
	DWORD IsPacked:1;
	DWORD IsNested:1;
	DWORD HasNestedTypes:1;
	DWORD HasCastOperator:1;
	DWORD HasAssignmentOperator:1;
	DWORD HasOverloadedOperator:1;
	DWORD HasVirtualTable:1;
	DWORD IsNestedUnnamed:1;
	DWORD IsUnnamed:1;
	DWORD Reserved:9;
	DWORD VTableCount:12;
	//DWORD VTableSize;
	//DWORD VTableRVA;
	union{		
		PSDUDTVIRTUALTABLE pVTableMember;
		DWORD VTableMemberOffset;
	}pVTable;
	union{
		DWORD* pBaseClassMember;
		DWORD BaseClassMemberOffset;
	}pBaseClass;
	union{
		DWORD* pDataMember;
		DWORD DataMemberOffset;
	}pData;
	DWORD FunctionCounter;
	union{
		DWORD* pFunctionMember;
		DWORD FunctionMemberOffset;
	}pFunction;	
	union{
		DWORD* pFriendMember;
		DWORD FriendMemberOffset;
	}pFriend;
}SDUDTTYPE,SDSTRUCTTYPE,SDUNIONTYPE,SDCLASSTYPE,*PSDUDTTYPE,*PSDSTRUCTTYPE,*PSDUNIONTYPE,*PSDCLASSTYPE;
typedef struct stSDUDTBaseClass
{
	DWORD TypeID;
	DWORD TypeIDParent;
	DWORD Access:16;
	DWORD bIsIndirectBaseClass:1;
	DWORD bIsVirtual:1;
	LONG Offset;
	DWORD VirtualBasePointerOffset;
	DWORD VirtualBaseDispIndex;
}SDUDTBASECLASS,*PSDUDTBASECLASS;

typedef struct stSDPointerType
{
	DWORD PointerDepth;
	DWORD NextPointer;
	DWORD TypeID;	
}SDPOINTERTYPE,*PSDPOINTERTYPE;
typedef struct stSDReferenceType 
{
	DWORD TypeID;
}SDREFERENCETYPE,*PSDREFERENCETYPE;
typedef struct stSDTypedefType
{
	DWORD TypeID;
}SDTYPEDEFTYPE,*PSDTYPEDEFTYPE;
typedef struct stSDArrayIndex
{
	DWORD TypeIDIndex;
	DWORD Size;
}SDARRAYINDEX,*PSDARRAYINDEX;
typedef struct stSDArrayType
{
	DWORD DimensionsSize;
	DWORD NextArrayID;
	DWORD TypeIDElement;
	SDARRAYINDEX Dimensions[1];
}SDARRAYTYPE,*PSDARRAYTYPE;
typedef struct stEnumerationDataMember
{
	union{
		DWORD MemberNameInStringTableIndex;
		char *Name;
	}u;
	ULONGLONG Value;
}ENUMERATIONDATAMEMBER,*PENUMERATIONDATAMEMBER;

typedef struct stSDEnumerationType
{
	DWORD DataCount:30;
	DWORD IsNested:1;
	DWORD IsScoped:1;
	DWORD TypeID;
	ENUMERATIONDATAMEMBER EnumerationDataMember[1];
}SDENUMERATIONTYPE,*PSDENUMERATIONTYPE;



typedef struct stSDLine
{		
	DWORD Rva;
	DWORD Statement:1;
	DWORD CompilandId:15;
	DWORD FileID:16;
	DWORD LineNumber:16;
	DWORD Len:16;
	bool operator<(const struct stSDLine dest)
	{
		return Rva<dest.Rva;
	}
}SDLINE,*PSDLINE;
typedef struct stSDSourceFile
{	
	union{
		char *Name;
		DWORD MemberNameInStringTableIndex;
	}uName;	
	DWORD FileID;
	DWORD LinesNumber;	
	SDLINE  *pLines;
}SDSOURCEFILE,*PSDSOURCEFILE;

typedef struct stSDCompiland
{
	union{
		char *Name;
		DWORD MemberNameInStringTableIndex;
	}uName;	
	DWORD CompilandId;
	DWORD SourceFileCounter;
	DWORD MaxRva;
	DWORD MinRva;
	SDSOURCEFILE SourceFile[1];
}SDCOMPILAND,*PSDCOMPILAND;

typedef struct stSDSymbolDirectory
{
	DWORD Offset;
	DWORD Size;
}SDSYMBOLDIRECTORY;
typedef struct stSDImportTable
{
	union{
		char* Name;
		DWORD StringTableIndex;
	}uName;
	DWORD ImportEntryNum;
}SDIMPORTTABLE,*PSDIMPORTTABLE;
typedef struct stSDExportTable
{

}SDEXPORTTABLE,*PSDEXPORTTABLE;
typedef struct stSourceFileId
{
	DWORD FileID;
	union{
		char *Name;
		DWORD MemberNameInStringTableIndex;
	}uName;	
	DWORD OffsetAtFile;
	DWORD FileLen;
}SDSOURCEFILEID,*PSDSOURCEFILEID;
#define SYSER_DEBUG_SYMBOL_FILE_SIG ( ('S' << 24) + ('D' << 16) + ('S' << 8) + 'F' )
#define SYSER_DEBUG_SYMBOL_FILE_VER ( (0 << 24) + (0 << 16) + (1 << 8) + 10)
typedef struct stSDSymbolFileStruct
{
	DWORD Sig;										//offset 00		//"SDSF"    Syser Debug Symbol File
	DWORD Version;									//offset 04		//"0.0.0.1"	Version
	DWORD FileLen;									//offset 08		//该文件的文件长度
	DWORD SymbolTotalNum;							//offset 0c		//总的符号的数量
	union _UnionSymbolTable{
		DWORD SymbolTableOffset;
		PSDTYPE_INFILE SymbolTablePointer;
	}UnionSymbolTable;								//offset 10		//符号在文件中的偏移
	union _UnionSymbolIndexTable
	{	
		DWORD SymbolIndexTableOffset;				//offset 14		//符号偏移索引表在文件中的位置
		PSDTYPE_INFILE* SymbolIndexTablePointer;
	}UnionSymbolIndexTable;
	DWORD LineNumberCounter;						//offset 18		//行号的总数
	union _UnionLineNumber{
		DWORD LineNumberOffset;	
		PSDLINE pLineNumberTablePointer;
	}UnionLineNumber;								//offset 1c		//行号在文件中的偏移											
	//DWORD FileNameOffset;							//offset 20		//与该PDB文件相关的 可执行文件的名字
	DWORD StringTotalNum;							//offset 24		//字符串表中字符串的数量
	union _UnionStringIndexTable
	{
		DWORD StringIndexTableOffset;					//offset 28		//字符串索引表在文件中的位置
		char** 	StringIndexTablePointer;
	}UnionStringIndexTable;
	union _UnionStringTable
	{
		DWORD StringTableOffset;						//offset 2c		//字符串表在文件中的位置
		char*  StringTablePointer;
	}UnionStringTable;
	DWORD SourceFileCounter;						//offset 30		//该可执行文件相关的源代码文件的数量
	union _UnionSourceFileIDTable
	{
		DWORD SourceFileIDTableOffset;					//offset 34		//源代码文件结构在文件中的位置
		PSDSOURCEFILEID SourceFileIDTablePointer;
	}UnionSourceFileIDTable;
	DWORD PublicSymbolCounter;						//offset 38		//公用符号的索引树组中元素的数量
	union _UnionPublicSymbol
	{
		DWORD PublicSymbolOffset;						//offset 3c		//公用符号的索引树组在文件中的位置
		PSDPUBLICSYMBOL PublicSymbolPointer;
	}UnionPublicSymbol;
	union _UniosCompiland
	{
		DWORD CompilandOffset;							//offset 40		//
		PSDCOMPILAND CompilandPointer;
	}UniosCompiland;
	DWORD CompilandCounter;							//offset 44		//
	DWORD DataInformationNum;						//offset 48		//数据信息的数量
	union _UnionDataInformation
	{
		DWORD DataInformationOffset;					//offset 4c		//数据信息在文件中的位置
		PSDUDTDATAITEM DataInformationPointer;
	}UnionDataInformation;
	union _UnionDataInformationIndexTable
	{
		DWORD DataInformationIndexTableOffset;			//offset 50		//数据信息偏移索引表在文件中的位置
		PSDUDTDATAITEM* DataInformationIndexTablePointer;
	}UnionDataInformationIndexTable;
	DWORD FunctionSymbolNum;
	union _UnionFunctionSymbol
	{
		DWORD FunctionSymbolOffset;
		PSDFUNCTIONITEM FunctionSymbolPointer;
	}UnionFunctionSymbol;
	union _UnionFunctionSymbolIndexTable
	{
		DWORD FunctionSymbolIndexTableOffset;
		PSDFUNCTIONITEM* FunctionSymbolIndexTablePointer;
	}UnionFunctionSymbolIndexTable;
	union _UnionSourceFile
	{
		DWORD SourceFileOffset;						//offset 54     //原代码在文件中的开始位置
		char* SourceFilePointer;
	}UnionSourceFile;
	struct _UnionModuleID
	{
		DWORD TimeDateStamp;							//offset 58		//
		DWORD OrgPECheckSum;									//offset 5c		//该文件的效验和
	}ModuleID;
	
	DWORD SymbolDirectoryEntryNum;					//offset 60		//符号目录项的个数
	union UnionPEFileName{
		char* PEFileName;
		DWORD PEFileNameOffset;
	}uPEFileName;									//offset 64
	DWORD PEFileNameLen;							//offset 68
	union UnionPBDFileName{
		char* PDBFileName;
		DWORD PDBFileNameOffset;
	}uPDBFileName;									//offset 6c
	DWORD PDBFileNameLen;							//offset 70
	union UnionPEFileFullName{
		char* PEFileFullName;
		DWORD PEFileFullNameOffset;
	}uPEFileFullName;								//offset 74
	DWORD PEFileFullNameLen;						//offset 78
	DWORD CheckSum;	
	DWORD PackageSourceFileCounter;					//SDS中包含的实际的源代码文件个数
	SDSYMBOLDIRECTORY SymbolDirectory[SD_MAX_TYPEIDS];
}SDSYMBOLFILE,*PSDSYMBOLFILE;

#define SDSF_FILE_HEADER_SIZE (sizeof(SDSYMBOLFILE))
enum{
	btInt1=1*0x80,
	btInt2=2*0x80,
	btInt4=4*0x80,
	btInt8=8*0x80,
	btUint1=1*0x800,
	btUint2=2*0x800,
	btUint4=4*0x800,
	btUint8=8*0x800,
	btDouble=0x8000,
};
#endif /* _SYSER_DEBUG_SYMBOLS_H_ */
