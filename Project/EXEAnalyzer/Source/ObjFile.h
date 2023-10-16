#ifndef _OBJ_FILE_H_
#define _OBJ_FILE_H_

#define IMAGE_FILE_MACHINE_UNKNOWN           0
#define IMAGE_FILE_MACHINE_I386              0x014c  // Intel 386.
#define IMAGE_FILE_MACHINE_R3000             0x0162  // MIPS little-endian, 0x160 big-endian
#define IMAGE_FILE_MACHINE_R4000             0x0166  // MIPS little-endian
#define IMAGE_FILE_MACHINE_R10000            0x0168  // MIPS little-endian
#define IMAGE_FILE_MACHINE_WCEMIPSV2         0x0169  // MIPS little-endian WCE v2
#define IMAGE_FILE_MACHINE_ALPHA             0x0184  // Alpha_AXP
#define IMAGE_FILE_MACHINE_POWERPC           0x01F0  // IBM PowerPC Little-Endian
#define IMAGE_FILE_MACHINE_SH3               0x01a2  // SH3 little-endian
#define IMAGE_FILE_MACHINE_SH3E              0x01a4  // SH3E little-endian
#define IMAGE_FILE_MACHINE_SH4               0x01a6  // SH4 little-endian
#define IMAGE_FILE_MACHINE_ARM               0x01c0  // ARM Little-Endian
#define IMAGE_FILE_MACHINE_THUMB             0x01c2
#define IMAGE_FILE_MACHINE_IA64              0x0200  // Intel 64
#define IMAGE_FILE_MACHINE_MIPS16            0x0266  // MIPS
#define IMAGE_FILE_MACHINE_MIPSFPU           0x0366  // MIPS
#define IMAGE_FILE_MACHINE_MIPSFPU16         0x0466  // MIPS
#define IMAGE_FILE_MACHINE_ALPHA64           0x0284  // ALPHA64
#define IMAGE_FILE_MACHINE_AXP64             IMAGE_FILE_MACHINE_ALPHA64
//////////////////////////////////////////////////////////////
//Sym type
//////////////////////////////////////////////////////////////
#define IMAGE_SYM_TYPE_NULL                 0x0000  // no type.
#define IMAGE_SYM_TYPE_VOID                 0x0001  //
#define IMAGE_SYM_TYPE_CHAR                 0x0002  // type character.
#define IMAGE_SYM_TYPE_SHORT                0x0003  // type short integer.
#define IMAGE_SYM_TYPE_INT                  0x0004  //
#define IMAGE_SYM_TYPE_LONG                 0x0005  //
#define IMAGE_SYM_TYPE_FLOAT                0x0006  //
#define IMAGE_SYM_TYPE_DOUBLE               0x0007  //
#define IMAGE_SYM_TYPE_STRUCT               0x0008  //
#define IMAGE_SYM_TYPE_UNION                0x0009  //
#define IMAGE_SYM_TYPE_ENUM                 0x000A  // enumeration.
#define IMAGE_SYM_TYPE_MOE                  0x000B  // member of enumeration.
#define IMAGE_SYM_TYPE_BYTE                 0x000C  //
#define IMAGE_SYM_TYPE_WORD                 0x000D  //
#define IMAGE_SYM_TYPE_UINT                 0x000E  //
#define IMAGE_SYM_TYPE_DWORD                0x000F  //
#define IMAGE_SYM_TYPE_PCODE                0x8000  //

#define IMAGE_SYM_DTYPE_NULL                0       // no derived type.
#define IMAGE_SYM_DTYPE_POINTER             1       // pointer.
#define IMAGE_SYM_DTYPE_FUNCTION            2       // function.
#define IMAGE_SYM_DTYPE_ARRAY               3       // array.
//////////////////////////////////////////////////////////////
// Storage classes.
//////////////////////////////////////////////////////////////
#define IMAGE_SYM_CLASS_END_OF_FUNCTION     (BYTE )-1
#define IMAGE_SYM_CLASS_NULL                0x0000
#define IMAGE_SYM_CLASS_AUTOMATIC           0x0001
#define IMAGE_SYM_CLASS_EXTERNAL            0x0002
#define IMAGE_SYM_CLASS_STATIC              0x0003
#define IMAGE_SYM_CLASS_REGISTER            0x0004
#define IMAGE_SYM_CLASS_EXTERNAL_DEF        0x0005
#define IMAGE_SYM_CLASS_LABEL               0x0006
#define IMAGE_SYM_CLASS_UNDEFINED_LABEL     0x0007
#define IMAGE_SYM_CLASS_MEMBER_OF_STRUCT    0x0008
#define IMAGE_SYM_CLASS_ARGUMENT            0x0009
#define IMAGE_SYM_CLASS_STRUCT_TAG          0x000A
#define IMAGE_SYM_CLASS_MEMBER_OF_UNION     0x000B
#define IMAGE_SYM_CLASS_UNION_TAG           0x000C
#define IMAGE_SYM_CLASS_TYPE_DEFINITION     0x000D
#define IMAGE_SYM_CLASS_UNDEFINED_STATIC    0x000E
#define IMAGE_SYM_CLASS_ENUM_TAG            0x000F
#define IMAGE_SYM_CLASS_MEMBER_OF_ENUM      0x0010
#define IMAGE_SYM_CLASS_REGISTER_PARAM      0x0011
#define IMAGE_SYM_CLASS_BIT_FIELD           0x0012
#define IMAGE_SYM_CLASS_FAR_EXTERNAL        0x0044  //
#define IMAGE_SYM_CLASS_BLOCK               0x0064
#define IMAGE_SYM_CLASS_FUNCTION            0x0065
#define IMAGE_SYM_CLASS_END_OF_STRUCT       0x0066
#define IMAGE_SYM_CLASS_FILE                0x0067
#define IMAGE_SYM_CLASS_SECTION             0x0068
#define IMAGE_SYM_CLASS_WEAK_EXTERNAL       0x0069
#define IMAGE_SYM_CLASS_CLR_TOKEN           0x006B
//////////////////////////////////////////////////////////////
// Section Number Values
//////////////////////////////////////////////////////////////
/*
#define IMAGE_SYM_UNDEFINED					0
#define IMAGE_SYM_ABSOLUTE					-1
#define IMAGE_SYM_DEBUG						-2
*/
#include <pshpack1.h>
struct OBJ_IMAGE_FILE_HEADER
{
	WORD    Machine;
	WORD    NumberOfSections;
	DWORD   TimeDateStamp;
	DWORD   PointerToSymbolTable;
	DWORD   NumberOfSymbols;
	WORD    SizeOfOptionalHeader;
	WORD    Characteristics;
};

typedef struct _OBJ_LINENUMBER
{
	union
	{
		DWORD SymbolTableIndex;
		DWORD VirtualAddress;
	}Type;
	WORD Linenumber;
}OBJ_LINENUMBER,*POBJ_LINENUMBER;
typedef struct _OBJ_RELOCATION_ITEM
{
	 DWORD VirtualAddress;
	 DWORD SymbolTableIndex;
	 WORD  Type;
}OBJ_RELOCATION_ITEM,*POBJ_RELOCATION_ITEM;
struct OBJ_IMAGE_SYMBOL
{
	union
	{
		BYTE    ShortName[8];
		struct
		{
			DWORD   Short;     // if 0, use LongName
			DWORD   Long;      // offset into string table
		} Name;
		DWORD   LongName[2];    // PBYTE [2]
	} N;
	DWORD   Value;
	short	SectionNumber;
	WORD    Type;
	BYTE    StorageClass;
	BYTE    NumberOfAuxSymbols;
};

#define IMAGE_SIZEOF_SHORT_NAME 8

struct OBJ_SECTION
{
	BYTE    Name[IMAGE_SIZEOF_SHORT_NAME];
	union
	{
		DWORD   PhysicalAddress;
		DWORD   VirtualSize;
	}Misc;
	DWORD   VirtualAddress;
	DWORD   SizeOfRawData;
	DWORD   PointerToRawData;
	DWORD   PointerToRelocations;
	DWORD   PointerToLinenumbers;
	WORD    NumberOfRelocations;
	WORD    NumberOfLinenumbers;
	DWORD   Characteristics;
};



#define IMAGE_SIZEOF_SYMBOL 18

union OBJ_IMAGE_AUX_SYMBOL
{
	struct 
	{
		DWORD  TagIndex;                      // struct, union, or enum tag index
		union
		{
			struct
			{
				WORD    Linenumber;             // declaration line number
				WORD    Size;                   // size of struct, union, or enum
			} LnSz;
			DWORD    TotalSize;
		} Misc;
		union
		{
			struct 
			{                            // if ISFCN, tag, or .bb
				DWORD    PointerToLinenumber;
				DWORD    PointerToNextFunction;
			} Function;
			struct
			{                            // if ISARY, up to 4 dimen.
				WORD     Dimension[4];
			} Array;
		} FcnAry;
		WORD    TvIndex;                        // tv index
	} Sym;
	struct 
	{
		DWORD Unused;
		WORD Linenumber;
		BYTE Unused1[6];
		DWORD PointerToNextFunction;
		WORD Unused2;
	}bf;
	struct 
	{
		DWORD Unused;
		WORD Linenumber;
		BYTE Unused1[6];
		DWORD Unused3;
		WORD Unused2;
	}ef;
	struct 
	{
		DWORD Unused;
		WORD Linenumber;
		BYTE Unused1[6];
		DWORD PointerToNextFunction;
		WORD Unused2;
	}lf;
	struct {
		DWORD TagIndex;
		DWORD Characteristics;
		BYTE Unused[10];
	}WeakExternals;
	struct 
	{
		BYTE    Name[IMAGE_SIZEOF_SYMBOL];
	} File;
	struct
	{
		DWORD   Length;                         // section length
		WORD    NumberOfRelocations;            // number of relocation entries
		WORD    NumberOfLinenumbers;            // number of line numbers
		DWORD   CheckSum;                       // checksum for communal
		SHORT   Number;                         // section number to associate with
		BYTE    Selection;                      // communal selection type
	}Section;
};

struct OBJ_IMAGE_LINENUMBER
{
	union
	{
		DWORD   SymbolTableIndex;               // Symbol table index of function name if Linenumber is 0.
		DWORD   VirtualAddress;                 // Virtual address of line number.
	} Type;
	WORD    Linenumber;                         // Line number.
};

#define IMAGE_SIZEOF_SYMBOL                 18
#define IMAGE_SIZEOF_AUX_SYMBOL             18
#define IMAGE_SIZEOF_LINENUMBER              6

struct OBJ_FUNC
{
	CStrA	FuncName;
	DWORD		FilePos;
	DWORD		Size;
};
#include <poppack.h>

typedef TList<OBJ_FUNC>	TObjFuncList;

class CObjFile : public CImageFile
{
public:
	CObjFile();
	~CObjFile();
public:
	bool	Open(PCSTR FileName,HANDLE*pHandleOpen = NULL);
	void	Close();
	void	AddFunction(OBJ_IMAGE_SYMBOL*ObjSym);
public:
	BYTE* m_FileBody;
	OBJ_IMAGE_FILE_HEADER	m_ObjHead;
	OBJ_SECTION*m_Section;
	int	m_SectCount;
	int	m_FuncCount;
	TObjFuncList	m_FuncList;
	OBJ_IMAGE_SYMBOL*m_ObjSymAry;
	char*m_StrTabBuf;
	static DWORD m_ObjMachineSign[];
	char* GetSectionName(int SectionIndex);
	char* GetSymbolName(OBJ_IMAGE_SYMBOL* Sym);
	char* GetSymbolNameByIndex(DWORD Index);

};


#endif
