#ifndef	_PEFILE_H_
#define _PEFILE_H_

//////////////////////////////////////////////////////////////////
//安全限制
//////////////////////////////////////////////////////////////////
#define MAX_PE_DATA_DIR					0x10
#define MAX_PE_SECTION					0x80
#define MAX_PE_IMAGESIZE				0x1000000
#define MAX_PE_BUFFER_SIZE				0xFFFF
#define MAX_PE_TLS_DATA_SIZE			0x10000
#define MAX_PE_IMPORT_MODULE			0x100
#define MAX_PE_FUNC_PER_IMPORT_MODULE	0x1000
#define MAX_PE_RES_DIR					0x400
#define MAX_PE_RES_PER_TYPE				0x1000
#define MAX_PE_FUNC_SIZE				0xFFFF
#define MAX_PE_SIZE_SIZE				0x1000

#define MAX_PE_TLS_BLOCK				0x1000
#define MAX_PE_TLS_CALLBACK				0x200
#define MAX_PE_BASE_RELOC_PAGE			0x1000
#define MAX_PE_BASE_RELOC_PER_PAGE		0x400

#define PE_MAX_SECTION_ALIGN			0x10000
#define PE_MAX_FILE_ALIGN				0x2000

#define PE_DEFAULT_SECTION_ALIGN		0x1000
#define PE_DEFAULT_FILE_ALIGN			0x200

#define INVALID_RES_TYPE				0xFFFFFFFF

#define PE_OPEN_EXE						0x00000001
#define PE_OPEN_DLL						0x00000002
#define PE_OPEN_SYS						0x00000004
#define PE_OPEN_NON_I386				0x00000008
#define PE_OPEN_NO_IMPORT				0x00000010
#define PE_OPEN_NO_EXPORT				0x00000020
#define PE_OPEN_NO_IMPORT_STRING		0x00000040

#define PE_OPEN_ALL						(PE_OPEN_EXE|PE_OPEN_DLL|PE_OPEN_SYS)

enum
{
	PE_ERROR_SUCCESS = 0,
	PE_ERROR_SIGN,
	PE_ERROR_SECTION,
	PE_ERROR_MODULE_TYPE,
	PE_ERROR_HEAD
};

#define IMAGE_SCN_CNT_CODE						0x00000020  // Section contains code.
#define IMAGE_SCN_CNT_INITIALIZED_DATA			0x00000040  // Section contains initialized data.
#define IMAGE_SCN_CNT_UNINITIALIZED_DATA		0x00000080  // Section contains uninitialized data.
#define IMAGE_SCN_MEM_EXECUTE					0x20000000  // Section is executable.
#define IMAGE_SCN_MEM_READ						0x40000000  // Section is readable.
#define IMAGE_SCN_MEM_WRITE						0x80000000  // Section is writeable.
#define IMAGE_SCN_ALL_ATTRIB					0xE0000060
//
// I386 relocation types.
//
#define IMAGE_REL_I386_ABSOLUTE         0x0000  // Reference is absolute, no relocation is necessary
#define IMAGE_REL_I386_DIR16            0x0001  // Direct 16-bit reference to the symbols virtual address
#define IMAGE_REL_I386_REL16            0x0002  // PC-relative 16-bit reference to the symbols virtual address
#define IMAGE_REL_I386_DIR32            0x0006  // Direct 32-bit reference to the symbols virtual address
#define IMAGE_REL_I386_DIR32NB          0x0007  // Direct 32-bit reference to the symbols virtual address, base not included
#define IMAGE_REL_I386_SEG12            0x0009  // Direct 16-bit reference to the segment-selector bits of a 32-bit virtual address
#define IMAGE_REL_I386_SECTION          0x000A
#define IMAGE_REL_I386_SECREL           0x000B
#define IMAGE_REL_I386_REL32            0x0014  // PC-relative 32-bit reference to the symbols virtual address

struct PE_SECTION
{
	CHAR   Name[8];                   //0x00
	DWORD  VirtualSize;               //0x08
	DWORD  VirtualAddress;            //0x0C
	DWORD  SizeOfRawData;             //0x10
	DWORD  PointerToRawData;          //0x14
	DWORD  PointerToRelocations;      //0x18
	DWORD  PointerToLinenumbers;      //0x1C
	WORD   NumberOfRelocations;       //0x20
	WORD   NumberOfLinenumbers;	      //0x22
	DWORD  Characteristics;           //0x24
}ST_PACK_ONE_BYTE;

typedef struct _PE_DATA_DIR
{
    DWORD   VirtualAddress;
    DWORD   Size;
}PE_DATA_DIR,*PPE_DATA_DIR;

typedef struct _PE_DEBUG_DIRECTORY 
{  
	DWORD Characteristics;  
	DWORD TimeDateStamp; 
	WORD MajorVersion;  
	WORD MinorVersion;  
	DWORD Type;  
	DWORD SizeOfData;  
	DWORD AddressOfRawData;  
	DWORD PointerToRawData;
} PE_DEBUG_DIRECTORY, *PPE_DEBUG_DIRECTORY;

#define IMAGE_DEBUG_MISC_EXENAME    1

typedef struct _PE_DEBUG_MISC
{
	DWORD	DataType;               // type of misc data, see defines
	DWORD	Length;                 // total length of record, rounded to four
	// byte multiple.
	BYTE	Unicode;                // TRUE if data is unicode string
	BYTE	Reserved[ 3 ];
	BYTE	Data[ 260 ];            // Actual data
} PE_DEBUG_MISC, *PPE_DEBUG_MISC;

typedef struct _PE_DEBUG_CODEVIEW
{
	DWORD  Signature;                  //0x00  NB10标志，必须是0x3031
	DWORD  Reserved;                 // total length of record, rounded to four
	// byte multiple.
	DWORD  TimeDateStamp;              //0x08
	DWORD  Age;
	BYTE   Name[ 260 ];              // Actual data
} PE_DEBUG_CODEVIEW, *PPE_DEBUG_CODEVIEW;

typedef struct _PD_DEBUG_PDB
{
	DWORD  Signature;
    union
	{
        ULONG   Data1;
        USHORT  Data2;
        USHORT  Data3;
        UCHAR   Data4[8];
    }Guid;
	DWORD Reserved;
	DWORD Reserved1;
	DWORD Age;
	BYTE Name[780];
}PE_DEBUG_PDB,*PPE_DEBUG_PDB;

struct EXPORT_DESCR
{
    DWORD   Characteristics;		//0x00
    DWORD   TimeDateStamp;			//0x04
    WORD    MajorVersion;			//0x08
    WORD    MinorVersion;			//0x0A
    DWORD   Name;					//0x0C
    DWORD   Base;					//0x10
    DWORD   NumberOfFunctions;		//0x14
    DWORD   NumberOfNames;			//0x18
    DWORD   AddressOfFunctions;     //0x1C	 RVA from base of image
    DWORD   AddressOfNames;         //0x20	 RVA from base of image
    DWORD   AddressOfNameOrdinals;  //0x24	 RVA from base of image
}ST_PACK_ONE_BYTE;

struct IMPORT_DESCR
{
    union
	{
        DWORD   Characteristics;
        DWORD   OriginalFirstThunk;
    };
    DWORD   TimeDateStamp;
    DWORD   ForwarderChain;
    DWORD   Name;
    DWORD   FirstThunk;
};

struct EXPORT_FUNC
{
    char	FuncName[MAX_NAME_LEN];
	DWORD	Address;
	DWORD	FuncOrd;
	DWORD	ThunkAddr;
};

struct IMPORT_FUNC
{
    char	FuncName[MAX_NAME_LEN];
	DWORD	NameAddr;
	DWORD	ThunkAddr;
	DWORD	Address;
	DWORD	FuncOrd;
	bool	bUseOrd;
};

struct IMPORT_MODULE
{
    CHAR	ModuleName[MAX_NAME_LEN];
	CHAR	FileName[MAX_NAME_LEN];
	IMPORT_FUNC*FuncList;
	int		FuncCount;
	DWORD	Address;
};

// Subsystem Values
#define IMAGE_SUBSYSTEM_UNKNOWN              0   // Unknown subsystem.
#define IMAGE_SUBSYSTEM_NATIVE               1   // Image doesn't require a subsystem.
#define IMAGE_SUBSYSTEM_WINDOWS_GUI          2   // Image runs in the Windows GUI subsystem.
#define IMAGE_SUBSYSTEM_WINDOWS_CUI          3   // Image runs in the Windows character subsystem.
#define IMAGE_SUBSYSTEM_OS2_CUI              5   // image runs in the OS/2 character subsystem.
#define IMAGE_SUBSYSTEM_POSIX_CUI            7   // image runs in the Posix character subsystem.
#define IMAGE_SUBSYSTEM_NATIVE_WINDOWS       8   // image is a native Win9x driver.
#define IMAGE_SUBSYSTEM_WINDOWS_CE_GUI       9   // Image runs in the Windows CE subsystem.
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

#define PE_HEAD_SIGNATURE			((0<<24)+(0<<16)+('E'<<8)+('P'))
struct PE_HEAD
{
	DWORD  Signature;                  //0x00  PE标志，必须是0x00004550
	WORD   Machine;                    //0x04
	WORD   NumberOfSections;           //0x06
	DWORD  TimeDateStamp;              //0x08
	DWORD  PointerToSymbolTable;       //0x0C
	DWORD  NumberOfSymbols;            //0x10
	WORD   SizeOfOptionalHeader;       //0x14
	WORD   Characteristics;            //0x16
	WORD   Magic;                      //0x18
	BYTE   MajorLinkerVersion;         //0x1A
	BYTE   MinorLinkerVersion;         //0x1B
	DWORD  SizeOfCode;                 //0x1C
	DWORD  SizeOfInitializedData;      //0x20
	DWORD  SizeOfUninitializedData;    //0x24
	DWORD  AddressOfEntryPoint;        //0x28
	DWORD  BaseOfCode;                 //0x2C
	DWORD  BaseOfData;                 //0x30
	DWORD  ImageBase;                  //0x34
	DWORD  SectionAlignment;           //0x38
	DWORD  FileAlignment;              //0x3C
	WORD   MajorOperatingSystemVersion;//0x40
	WORD   MinorOperatingSystemVersion;//0x42
	WORD   MajorImageVersion;          //0x44
	WORD   MinorImageVersion;          //0x46
	WORD   MajorSubsystemVersion;      //0x48
	WORD   MinorSubsystemVersion;      //0x4A
	DWORD  Win32VersionValue;          //0x4C
	DWORD  SizeOfImage;                //0x50
	DWORD  SizeOfHeaders;              //0x54
	DWORD  CheckSum;                   //0x58
	WORD   Subsystem;                  //0x5C
	WORD   DllCharacteristics;         //0x5E
	DWORD  SizeOfStackReserve;         //0x60
	DWORD  SizeOfStackCommit;          //0x64
	DWORD  SizeOfHeapReserve;          //0x68
	DWORD  SizeOfHeapCommit;           //0x6C
	DWORD  LoaderFlags;                //0x70
	DWORD  NumberOfRvaAndSizes;        //0x74
	PE_DATA_DIR DataDirectory[MAX_PE_DATA_DIR];//0x78
}ST_PACK_ONE_BYTE;

struct IMAGE_BASE_RELOC
{
    DWORD   VirtualAddress;
    DWORD   BlockSize;
};

struct RESOURCE_DIRECTORY
{
    DWORD   Characteristics;
    DWORD   TimeDateStamp;
    WORD    MajorVersion;
    WORD    MinorVersion;
    WORD    NumberOfNamedEntries;
    WORD    NumberOfIdEntries;
	//IMAGE_RESOURCE_DIRECTORY_ENTRY DirectoryEntries[];
}ST_PACK_ONE_BYTE;

struct TLS_DIRECTORY32
{
    DWORD   StartAddressOfRawData;
    DWORD   EndAddressOfRawData;
    DWORD   AddressOfIndex;             // PDWORD
    DWORD   AddressOfCallBacks;         // PIMAGE_TLS_CALLBACK *
    DWORD   SizeOfZeroFill;
    DWORD   Characteristics;
};

#define IMAGE_RESOURCE_NAME_IS_STRING        0x80000000
#define IMAGE_RESOURCE_DATA_IS_DIRECTORY     0x80000000

struct RESOURCE_DIRECTORY_ENTRY
{
    DWORD   Name;
	DWORD   OffsetToData;
};

struct RESOURCE_DIRECTORY_STRING
{
    WORD    Length;
    CHAR    NameString[1];
};

struct RESOURCE_DATA_ENTRY
{
    DWORD   OffsetToData;
    DWORD   Size;
    DWORD   CodePage;
    DWORD   Reserved;
};

struct RES_DATA
{
	DWORD CodePage;
	DWORD ID;
	WORD IDName[MAX_NAME_LEN];
	DWORD BufferAddr;
	DWORD Size;
};

struct RES_DIR
{
	DWORD Type;
	WORD TypeName[MAX_NAME_LEN];
	int   ResCount;
	RES_DATA* ResDataDir;
};

struct BASE_RELOC
{
	DWORD VirtualAddr;
	DWORD Count;
	WORD* TypeOffset;
};

#define IMAGE_DIRECTORY_ENTRY_EXPORT			0   // Export Directory
#define IMAGE_DIRECTORY_ENTRY_IMPORT			1   // Import Directory
#define IMAGE_DIRECTORY_ENTRY_RESOURCE			2   // Resource Directory
#define IMAGE_DIRECTORY_ENTRY_EXCEPTION			3   // Exception Directory
#define IMAGE_DIRECTORY_ENTRY_SECURITY			4   // Security Directory
#define IMAGE_DIRECTORY_ENTRY_BASERELOC			5   // Base Relocation Table
#define IMAGE_DIRECTORY_ENTRY_DEBUG				6   // Debug Directory
#define IMAGE_DIRECTORY_ENTRY_COPYRIGHT			7   // (X86 usage)
#define IMAGE_DIRECTORY_ENTRY_ARCHITECTURE		7   // Architecture Specific Data
#define IMAGE_DIRECTORY_ENTRY_GLOBALPTR			8   // RVA of GP
#define IMAGE_DIRECTORY_ENTRY_TLS				9   // TLS Directory
#define IMAGE_DIRECTORY_ENTRY_LOAD_CONFIG		10   // Load Configuration Directory
#define IMAGE_DIRECTORY_ENTRY_BOUND_IMPORT		11   // Bound Import Directory in headers
#define IMAGE_DIRECTORY_ENTRY_IAT				12   // Import Address Table
#define IMAGE_DIRECTORY_ENTRY_DELAY_IMPORT		13   // Delay Load Import Descriptors
#define IMAGE_DIRECTORY_ENTRY_COM_DESCRIPTOR	14   // COM Runtime descriptor

#define IMAGE_FILE_RELOCS_STRIPPED				0x0001  // Relocation info stripped from file.
#define IMAGE_FILE_EXECUTABLE_IMAGE				0x0002  // File is executable  (i.e. no unresolved externel references).
#define IMAGE_FILE_LINE_NUMS_STRIPPED			0x0004  // Line nunbers stripped from file.
#define IMAGE_FILE_LOCAL_SYMS_STRIPPED			0x0008  // Local symbols stripped from file.
#define IMAGE_FILE_AGGRESIVE_WS_TRIM			0x0010  // Agressively trim working set
#define IMAGE_FILE_LARGE_ADDRESS_AWARE			0x0020  // App can handle >2gb addresses
#define IMAGE_FILE_BYTES_REVERSED_LO			0x0080  // Bytes of machine word are reversed.
#define IMAGE_FILE_32BIT_MACHINE				0x0100  // 32 bit word machine.
#define IMAGE_FILE_DEBUG_STRIPPED				0x0200  // Debugging info stripped from file in .DBG file
#define IMAGE_FILE_REMOVABLE_RUN_FROM_SWAP		0x0400  // If Image is on removable media, copy and run from the swap file.
#define IMAGE_FILE_NET_RUN_FROM_SWAP			0x0800  // If Image is on Net, copy and run from the swap file.
#define IMAGE_FILE_SYSTEM						0x1000  // System File.
#define IMAGE_FILE_DLL							0x2000  // File is a DLL.
#define IMAGE_FILE_UP_SYSTEM_ONLY				0x4000  // File should only be run on a UP machine
#define IMAGE_FILE_BYTES_REVERSED_HI			0x8000  // Bytes of machine word are reversed.
#define RES_TYPE_CURSOR							1
#define RES_TYPE_BITMAP							2
#define RES_TYPE_ICON							3
#define RES_TYPE_MENU							4
#define RES_TYPE_DIALOG							5
#define RES_TYPE_STRING							6
#define RES_TYPE_FONTDIR						7
#define RES_TYPE_FONT							8
#define RES_TYPE_ACCELERATOR					9
#define RES_TYPE_RCDATA							10
#define RES_TYPE_MESSAGETABLE					11
#define RES_TYPE_GROUP_CURSOR					RES_TYPE_CURSOR + DIFFERENCE
#define RES_TYPE_GROUP_ICON						RES_TYPE_ICON + DIFFERENCE
#define RES_TYPE_VERSION						16
#define RES_TYPE_DLGINCLUDE						17
#define RES_TYPE_HTML							23

class CPEFile : public CImageFile
{
public:
	CPEFile();
////文件相关函数//////////////////////////////////////////////////////
    bool    MapToFile(IN DWORD MemAddr,OUT DWORD*pPhysAddr = NULL,IN bool bImageBase = TRUE);
    bool    MapToMemory(IN DWORD PhyOff,OUT DWORD*pMemAddr = NULL,IN bool bImageBase = TRUE);
public:
	bool	Open(PCSTR FileName,HANDLE*pHandleOpen = NULL);
	void	Close();
	ULSIZE	ReadImageMemory(ULPOS Address,void*Buffer,ULSIZE Size);
	ULSIZE	WriteImageMemory(ULPOS Address,void*Buffer,ULSIZE Size);
	bool	LoadPage(ULPOS Address,void*Buffer);
	DWORD	GetPageAttribute(ULPOS Address);
public:
	////////////////////////////////////////////////////////
	//PE
	////////////////////////////////////////////////////////
	bool	Check();
	void	RelocLoad(IN ULPOS BaseAddr = 0);
	bool	IsRelocArea(ULPOS RVALow,ULPOS RVAHigh);
	bool	IsImportThunkArea(ULPOS RVALow,ULPOS RVAHigh);
	bool	GetImportThunkArea(ULPOS*pRVALow,ULPOS*pRVAHigh);
	void	GetBaseReloc();
	void	GetImportModule();
	IMPORT_MODULE*GetImportModule(PCSTR ModuleName);
	IMPORT_FUNC*GetImportFunc(IMPORT_MODULE*pModule,PCSTR FuncName);
	IMPORT_FUNC*GetImportModuleFunc(PCSTR ModuleName,PCSTR FuncName);
	bool	GetDataDirectory(IN int Index,OUT PPE_DATA_DIR DataDirectory)const;
	void	GetExportFunc();
	void	GetTLS();
	void	GetResource();
	DWORD	GetExportFunc(IN PCSTR FuncName,int*pIndex=NULL);
	DWORD	GetExportFunc(IN DWORD FuncOrd);
	int		GetLastPhyPosSection();		//得到物理地址最大的那个段
	int		GetLastMemAddrSection();	//得到虚拟地址最大的那个段
	int		GetFirstPhyPosSection();	//得到物理地址最小的那个段
	int		GetFirstMemAddrSection();	//得到虚拟地址最小的那个段
    bool	GetSectionIndex(IN DWORD Address,OUT int*pIndex);
	/////////////////////////////////////////////////////////////
	//资源
	/////////////////////////////////////////////////////////////
	int		LoadStringW(DWORD StrID,PWORD szBuffer,int MaxLen);
	int		LoadStringA(DWORD StrID,PSTR szBuffer,int MaxLen);
	RES_DATA*FindResource(const PWORD szResID,DWORD ResID,const PWORD szType,DWORD Type);
public:
	UINT	m_OpenMode;
	UINT	m_ErrorCode;
	ULPOS	m_PEOff;
	PE_SECTION*m_Section;
	int		m_SectCount;
	PE_HEAD	m_PEHead;
	IMPORT_MODULE*	m_ImportModule;	//导入模块
	int			m_ImportModuleCount;//导入模块个数
	EXPORT_FUNC*m_ExportFunc;		//导出函数
	int			m_ExportFuncCount;	//导出函数个数
	RES_DIR*	m_ResDir;			//资源目录
	int			m_ResDirCount;		//资源目录个数
	BASE_RELOC*	m_BaseReloc;		//重定位目录
	int			m_BaseRelocCount;	//重定位目录个数
	/////////////////////////////////////////////////////
	//局部线性存储
	/////////////////////////////////////////////////////
	BYTE*		m_TLSData;			//TLS初始化数组
	int			m_TLSDataSize;		//TLS索引个数
	DWORD		m_AddressOfTLSIndex;//TLS索引地址
	DWORD*		m_TLSCallBackFuncs; //TLS回调函数
	int			m_TLSCallBackCount; //TLS回调函数个数
};


class  CMemPEFile : public CPEFile
{
public:
	bool	Open(ULPOS ModuleBase,UINT OpenMode,IN RWProc RMFunc,IN void*RMObj);
};

#endif


