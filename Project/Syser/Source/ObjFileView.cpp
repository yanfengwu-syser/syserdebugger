#include "stdafx.h"
#include "ObjFileView.h"
#include "../../SyserApp/Source/NoPDBSymbol.h"


STFLAGSARRAY CObjFileView::X86X87RegisterArray[]={
{"none",0 ,"none"},
{"AL",1 ,"AL"},
{"CL",2 ,"CL"},
{"DL",3 ,"DL"},
{"BL",4 ,"BL"},
{"AH",5 ,"AH"},
{"CH",6 ,"CH"},
{"DH",7 ,"DH"},
{"BH",8 ,"BH"},
{"AX",9 ,"AX"},
{"CX",10 ,"CX"},
{"DX",11 ,"DX"},
{"BX",12 ,"BX"},
{"SP",13 ,"SP"},
{"BP",14 ,"BP"},
{"SI",15 ,"SI"},
{"DI",16 ,"DI"},
{"EAX",17 ,"EAX"},
{"ECX",18 ,"ECX"},
{"EDX",19 ,"EDX"},
{"EBX",20 ,"EBX"},
{"ESP",21 ,"ESP"},
{"EBP",22 ,"EBP"},
{"ESI",23 ,"ESI"},
{"EDI",24 ,"EDI"},
{"ES",25 ,"ES"},
{"CS",26 ,"CS"},
{"SS",27 ,"SS"},
{"DS",28 ,"DS"},
{"FS",29 ,"FS"},
{"GS",30 ,"GS"},
{"IP",31 ,"IP"},
{"FLAGS",32 ,"FLAGS"},
{"EIP",33 ,"EIP"},
{"EFLAGS",34 ,"EFLAGS"},
{"TEMP",40 ,"TEMP"},
{"TEMPH",41 ,"TEMPH"},
{"QUOTE",42 ,"QUOTE"},
{"Reserved",43 ,"Reserved"},
{"Reserved",44 ,"Reserved"},
{"Reserved",45 ,"Reserved"},
{"Reserved",46 ,"Reserved"},
{"Reserved",47 ,"Reserved"},
{"CR0",80 ,"CR0"},
{"CR1",81 ,"CR1"},
{"CR2",82 ,"CR2"},
{"CR3",83 ,"CR3"},
{"DR0",90 ,"DR0"},
{"DR1",91 ,"DR1"},
{"DR2",92 ,"DR2"},
{"DR3",93 ,"DR3"},
{"DR4",94 ,"DR4"},
{"DR5",95 ,"DR5"},
{"DR6",96 ,"DR6"},
{"DR7",97 ,"DR7"},
{"ST(0)",128 ,"ST(0)"},
{"ST(2)",130 ,"ST(2)"},
{"ST(3)",131 ,"ST(3)"},
{"ST(4)",132 ,"ST(4)"},
{"ST(5)",133 ,"ST(5)"},
{"ST(6)",134 ,"ST(6)"},
{"ST(7)",135 ,"ST(7)"},
{"CONTROL",136 ,"CONTROL"},
{"STATUS",137 ,"STATUS"},
{"TAG",138 ,"TAG"},
{"FPIP",139 ,"FPIP"},
{"FPCS",140 ,"FPCS"},
{"FPDO",141 ,"FPDO"},
{"FPDS",142 ,"FPDS"},
{"ISEM",143 ,"ISEM"},
{"FPEIP",144 ,"FPEIP"},
{"FPEDO",145 ,"FPEDO"},
};

STFLAGSARRAY CObjFileView::COMPILE_LanguageArray[]={
{"C",0 ,"C"},
{"C++",1 ,"C++"},
{"Fortran",2 ,"Fortran"},
{"Masm",3 ,"Masm"},
{"Pascal",4 ,"Pascal"},
{"Basic",5 ,"Basic"},
{"Cobol",6 ,"Cobol"},
};
STFLAGSARRAY CObjFileView::COMPILE_machineArray[]={
{"Intel 8080", 0x00 ,"Intel 8080"},
{"Intel 8086", 0x01 ,"Intel 8086"},
{"Intel 80286", 0x02 ,"Intel 80286"},
{"Intel 80386", 0x03 ,"Intel 80386"},
{"Intel 80486", 0x04 ,"Intel 80486"},
{"Intel Pentium", 0x05 ,"Intel Pentium"},
{"Intel Pentium Pro", 0x06 ,"Intel Pentium Pro"},
{"MIPS R4000", 0x10 ,"MIPS R4000"},
{"Reserved for future MIPS processor", 0x11 ,"Reserved for future MIPS processor"},
{"Reserved for future MIPS processor", 0x12 ,"Reserved for future MIPS processor"},
{"MC68000", 0x20 ,"MC68000"},
{"MC68010", 0x21 ,"MC68010"},
{"MC68020", 0x22 ,"MC68020"},
{"MC68030", 0x23 ,"MC68030"},
{"MC68040", 0x24 ,"MC68040"},
{"DEC Alpha", 0x30 ,"DEC Alpha"},
{"PPC601", 0x40 ,"PPC601"},
{"PPC603", 0x41 ,"PPC603"},
{"PPC604", 0x42 ,"PPC604"},
{"PPC620", 0x43 ,"PPC620"},
};
STFLAGSARRAY CObjFileView::MachineTypeArray[]={
{"IMAGE_FILE_MACHINE_UNKNOWN", 0x0 ,"Contents assumed to be applicable to any machine type. "},
{"IMAGE_FILE_MACHINE_ALPHA", 0x184 ,"Alpha AXP?. "},
{"IMAGE_FILE_MACHINE_ARM", 0x1c0 ,""},
{"IMAGE_FILE_MACHINE_ALPHA64", 0x284 ,"Alpha AXP? 64-bit. "},
{"IMAGE_FILE_MACHINE_I386", 0x14c ,"Intel 386 or later, and compatible processors. "},
{"IMAGE_FILE_MACHINE_IA64", 0x200 ,"Intel IA64? "},
{"IMAGE_FILE_MACHINE_M68K", 0x268 ,"Motorola 68000 series. "},
{"IMAGE_FILE_MACHINE_MIPS16", 0x266 ,""},
{"IMAGE_FILE_MACHINE_MIPSFPU", 0x366 ,"MIPS with FPU "},
{"IMAGE_FILE_MACHINE_MIPSFPU16", 0x466 ,"MIPS16 with FPU "},
{"IMAGE_FILE_MACHINE_POWERPC", 0x1f0 ,"Power PC, little endian. "},
{"IMAGE_FILE_MACHINE_R3000", 0x162 ,""},  
{"IMAGE_FILE_MACHINE_R4000", 0x166 ,"MIPS? little endian. "},
{"IMAGE_FILE_MACHINE_R10000", 0x168 ,""},
{"IMAGE_FILE_MACHINE_SH3", 0x1a2 ,"Hitachi SH3 "},
{"IMAGE_FILE_MACHINE_SH4", 0x1a6 ,"Hitachi SH4 "},
{"IMAGE_FILE_MACHINE_THUMB", 0x1c2,""},
};

STFLAGSARRAY CObjFileView::FileHeaderCharacteristicsArray[]={
{"IMAGE_FILE_RELOCS_STRIPPED", 0x0001 ,"Image only, Windows CE, Windows NT and above. Indicates that the file does not contain base relocations and must therefore be loaded at its preferred base address. If the base address is not available, the loader reports an error. Operating systems running on top of MS-DOS (Win32s?) are generally not able to use the preferred base address and so cannot run these images. However, beginning with version 4.0, Windows will use an application's preferred base address. The default behavior of the linker is to strip base relocations from EXEs. "},
{"IMAGE_FILE_EXECUTABLE_IMAGE", 0x0002 ,"Image only. Indicates that the image file is valid and can be run. If this flag is not set, it generally indicates a linker error. "},
{"IMAGE_FILE_LINE_NUMS_STRIPPED", 0x0004 ,"COFF line numbers have been removed. "},
{"IMAGE_FILE_LOCAL_SYMS_STRIPPED", 0x0008 ,"COFF symbol table entries for local symbols have been removed. "},
{"IMAGE_FILE_AGGRESSIVE_WS_TRIM", 0x0010 ,"Aggressively trim working set. "},
{"IMAGE_FILE_LARGE_ADDRESS_AWARE", 0x0020 ,"App can handle > 2gb addresses. "},
{"IMAGE_FILE_16BIT_MACHINE", 0x0040 ,"Use of this flag is reserved for future use. "},
{"IMAGE_FILE_BYTES_REVERSED_LO", 0x0080 ,"Little endian: LSB precedes MSB in memory. "},
{"IMAGE_FILE_32BIT_MACHINE", 0x0100 ,"Machine based on 32-bit-word architecture. "},
{"IMAGE_FILE_DEBUG_STRIPPED", 0x0200 ,"Debugging information removed from image file. "},
{"IMAGE_FILE_REMOVABLE_RUN_FROM_SWAP", 0x0400 ,"If image is on removable media, copy and run from swap file. "},
{"IMAGE_FILE_SYSTEM", 0x1000 ,"The image file is a system file, not a user program. "},
{"IMAGE_FILE_DLL", 0x2000 ,"The image file is a dynamic-link library (DLL). Such files are considered executable files for almost all purposes, although they cannot be directly run. "},
{"IMAGE_FILE_UP_SYSTEM_ONLY", 0x4000 ,"File should be run only on a UP machine. "},
{"IMAGE_FILE_BYTES_REVERSED_HI", 0x8000 ,"Big endian: MSB precedes LSB in memory. "},
};
STFLAGSARRAY CObjFileView::RleFlagsArray[]={
{"IMAGE_REL_I386_ABSOLUTE", 0x0000 ,"This relocation is ignored. "},
{"IMAGE_REL_I386_DIR16", 0x0001 ,"Not supported. "},
{"IMAGE_REL_I386_REL16", 0x0002 ,"Not supported. "},
{"IMAGE_REL_I386_DIR32", 0x0006 ,"The target¡¯s 32-bit virtual address. "},
{"IMAGE_REL_I386_DIR32NB", 0x0007 ,"The target¡¯s 32-bit relative virtual address. "},
{"IMAGE_REL_I386_SEG12", 0x0009 ,"Not supported. "},
{"IMAGE_REL_I386_SECTION", 0x000A ,"The 16-bit-section index of the section containing the target. This is used to support debugging information. "},
{"IMAGE_REL_I386_SECREL", 0x000B ,"The 32-bit offset of the target from the beginning of its section. This is used to support debugging information as well as static thread local storage. "},
{"IMAGE_REL_I386_REL32", 0x0014 ,"The 32-bit relative displacement to the target. This supports the x86 relative branch and call instructions. "},
};
STFLAGSARRAY CObjFileView::FlagsArray[]={
{"IMAGE_SCN_TYPE_REG", 0x00000000 ,"Reserved for future use. "},
{"IMAGE_SCN_TYPE_DSECT", 0x00000001 ,"Reserved for future use. "},
{"IMAGE_SCN_TYPE_NOLOAD", 0x00000002 ,"Reserved for future use. "},
{"IMAGE_SCN_TYPE_GROUP", 0x00000004 ,"Reserved for future use. "},
{"IMAGE_SCN_TYPE_NO_PAD", 0x00000008 ,"Section should not be padded to next boundary. This is obsolete and replaced by IMAGE_SCN_ALIGN_1BYTES. This is valid for object files only. "},
{"IMAGE_SCN_TYPE_COPY", 0x00000010 ,"Reserved for future use. "},
{"IMAGE_SCN_CNT_CODE", 0x00000020 ,"Section contains executable code. "},
{"IMAGE_SCN_CNT_INITIALIZED_DATA", 0x00000040 ,"Section contains initialized data. "},
{"IMAGE_SCN_CNT_UNINITIALIZED_DATA", 0x00000080 ,"Section contains uninitialized data. "},
{"IMAGE_SCN_LNK_OTHER", 0x00000100 ,"Reserved for future use. "},
{"IMAGE_SCN_LNK_INFO", 0x00000200 ,"Section contains comments or other information. The .drectve section has this type. This is valid for object files only. "},
{"IMAGE_SCN_TYPE_OVER", 0x00000400 ,"Reserved for future use. "},
{"IMAGE_SCN_LNK_REMOVE", 0x00000800 ,"Section will not become part of the image. This is valid for object files only. "},
{"IMAGE_SCN_LNK_COMDAT", 0x00001000 ,"Section contains COMDAT data. See Section 5.5.6, ¡°COMDAT Sections,¡± for more information. This is valid for object files only. "},
{"IMAGE_SCN_MEM_FARDATA", 0x00008000 ,"Reserved for future use. "},
{"IMAGE_SCN_MEM_PURGEABLE", 0x00020000 ,"Reserved for future use. "}, 
{"IMAGE_SCN_MEM_16BIT", 0x00020000 ,"Reserved for future use. "},
{"IMAGE_SCN_MEM_LOCKED", 0x00040000 ,"Reserved for future use. "},
{"IMAGE_SCN_MEM_PRELOAD", 0x00080000 ,"Reserved for future use. "},
{"IMAGE_SCN_LNK_NRELOC_OVFL", 0x01000000 ,"Section contains extended relocations. "},
{"IMAGE_SCN_MEM_DISCARDABLE", 0x02000000 ,"Section can be discarded as needed. "},
{"IMAGE_SCN_MEM_NOT_CACHED", 0x04000000 ,"Section cannot be cached. "},
{"IMAGE_SCN_MEM_NOT_PAGED", 0x08000000 ,"Section is not pageable. "},
{"IMAGE_SCN_MEM_SHARED", 0x10000000 ,"Section can be shared in memory. "},
{"IMAGE_SCN_MEM_EXECUTE", 0x20000000 ,"Section can be executed as code. "},
{"IMAGE_SCN_MEM_READ", 0x40000000 ,"Section can be read. "},
{"IMAGE_SCN_MEM_WRITE", 0x80000000 ,"Section can be written to. "},
{"IMAGE_SCN_ALIGN_1BYTES", 0x00100000 ,"Align data on a 1-byte boundary. This is valid for object files only. "},
{"IMAGE_SCN_ALIGN_2BYTES", 0x00200000 ,"Align data on a 2-byte boundary. This is valid for object files only. "},
{"IMAGE_SCN_ALIGN_4BYTES", 0x00300000 ,"Align data on a 4-byte boundary. This is valid for object files only. "},
{"IMAGE_SCN_ALIGN_8BYTES", 0x00400000 ,"Align data on a 8-byte boundary. This is valid for object files only. "},
{"IMAGE_SCN_ALIGN_16BYTES", 0x00500000 ,"Align data on a 16-byte boundary. This is valid for object files only. "},
{"IMAGE_SCN_ALIGN_32BYTES", 0x00600000 ,"Align data on a 32-byte boundary. This is valid for object files only. "},
{"IMAGE_SCN_ALIGN_64BYTES", 0x00700000 ,"Align data on a 64-byte boundary. This is valid for object files only. "},
{"IMAGE_SCN_ALIGN_128BYTES", 0x00800000 ,"Align data on a 128-byte boundary. This is valid for object files only. "},
{"IMAGE_SCN_ALIGN_256BYTES", 0x00900000 ,"Align data on a 256-byte boundary. This is valid for object files only. "},
{"IMAGE_SCN_ALIGN_512BYTES", 0x00A00000 ,"Align data on a 512-byte boundary. This is valid for object files only. "},
{"IMAGE_SCN_ALIGN_1024BYTES", 0x00B00000 ,"Align data on a 1024-byte boundary. This is valid for object files only. "},
{"IMAGE_SCN_ALIGN_2048BYTES", 0x00C00000 ,"Align data on a 2048-byte boundary. This is valid for object files only. "},
{"IMAGE_SCN_ALIGN_4096BYTES", 0x00D00000 ,"Align data on a 4096-byte boundary. This is valid for object files only. "},
{"IMAGE_SCN_ALIGN_8192BYTES", 0x00E00000 ,"Align data on a 8192-byte boundary. This is valid for object files only. "},

};
STFLAGSARRAY CObjFileView::SymBaseTypeArray[]={
{"IMAGE_SYM_TYPE_NULL", 0 ,"No type information or unknown base type. Microsoft tools use this setting.  "},
{"IMAGE_SYM_TYPE_VOID", 1 ,"No valid type; used with void pointers and functions. "},
{"IMAGE_SYM_TYPE_CHAR", 2 ,"Character (signed byte). "},
{"IMAGE_SYM_TYPE_SHORT", 3 ,"Two-byte signed integer. "},
{"IMAGE_SYM_TYPE_INT", 4 ,"Natural integer type (normally four bytes in Windows NT). "},
{"IMAGE_SYM_TYPE_LONG", 5 ,"Four-byte signed integer. "},
{"IMAGE_SYM_TYPE_FLOAT", 6 ,"Four-byte floating-point number. "},
{"IMAGE_SYM_TYPE_DOUBLE", 7 ,"Eight-byte floating-point number. "},
{"IMAGE_SYM_TYPE_STRUCT", 8 ,"Structure. "},
{"IMAGE_SYM_TYPE_UNION", 9 ,"Union. "},
{"IMAGE_SYM_TYPE_ENUM", 10 ,"Enumerated type. "},
{"IMAGE_SYM_TYPE_MOE", 11 ,"Member of enumeration (a specific value). "},
{"IMAGE_SYM_TYPE_BYTE", 12 ,"Byte; unsigned one-byte integer. "},
{"IMAGE_SYM_TYPE_WORD", 13 ,"Word; unsigned two-byte integer. "},
{"IMAGE_SYM_TYPE_UINT", 14 ,"Unsigned integer of natural size (normally, four bytes). "},
{"IMAGE_SYM_TYPE_DWORD", 15 ,"Unsigned four-byte integer."}, 
};
STFLAGSARRAY CObjFileView::SymComplexTypeArray[]={
{"IMAGE_SYM_DTYPE_NULL", 0 ,"No derived type; the symbol is a simple scalar variable.  "},
{"IMAGE_SYM_DTYPE_POINTER", 1 ,"Pointer to base type. "},
{"IMAGE_SYM_DTYPE_FUNCTION", 2 ,"Function returning base type. "},
{"IMAGE_SYM_DTYPE_ARRAY", 3 ,"Array of base type. "},
};
#if 0
enum{
IMAGE_SYM_CLASS_END_OF_FUNCTION= -1,// (0xFF) Special symbol representing end of function, for debugging purposes. 
IMAGE_SYM_CLASS_NULL= 0,// No storage class assigned. 
IMAGE_SYM_CLASS_AUTOMATIC= 1,// Automatic (stack) variable. The Value field specifies stack frame offset. 
IMAGE_SYM_CLASS_EXTERNAL= 2,// Used by Microsoft tools for external symbols. The Value field indicates the size if the section number is IMAGE_SYM_UNDEFINED (0). If the section number is not 0, then the Value field specifies the offset within the section. 
IMAGE_SYM_CLASS_STATIC= 3,// The Value field specifies the offset of the symbol within the section. If the Value is 0, then the symbol represents a section name. 
IMAGE_SYM_CLASS_REGISTER= 4,// Register variable. The Value field specifies register number. 
IMAGE_SYM_CLASS_EXTERNAL_DEF= 5,// Symbol is defined externally. 
IMAGE_SYM_CLASS_LABEL= 6,// Code label defined within the module. The Value field specifies the offset of the symbol within the section. 
IMAGE_SYM_CLASS_UNDEFINED_LABEL= 7,// Reference to a code label not defined. 
IMAGE_SYM_CLASS_MEMBER_OF_STRUCT= 8,// Structure member. The Value field specifies nth member. 
IMAGE_SYM_CLASS_ARGUMENT= 9,// Formal argument (parameter)of a function. The Value field specifies nth argument. 
IMAGE_SYM_CLASS_STRUCT_TAG= 10,// Structure tag-name entry. 
IMAGE_SYM_CLASS_MEMBER_OF_UNION= 11,// Union member. The Value field specifies nth member. 
IMAGE_SYM_CLASS_UNION_TAG= 12,// Union tag-name entry. 
IMAGE_SYM_CLASS_TYPE_DEFINITION= 13,// Typedef entry. 
IMAGE_SYM_CLASS_UNDEFINED_STATIC= 14,// Static data declaration. 
IMAGE_SYM_CLASS_ENUM_TAG= 15,// Enumerated type tagname entry. 
IMAGE_SYM_CLASS_MEMBER_OF_ENUM= 16,// Member of enumeration. Value specifies nth member. 
IMAGE_SYM_CLASS_REGISTER_PARAM= 17,// Register parameter. 
IMAGE_SYM_CLASS_BIT_FIELD= 18,// Bit-field reference. Value specifies nth bit in the bit field. 
IMAGE_SYM_CLASS_BLOCK= 100,// A .bb (beginning of block) or .eb (end of block) record. Value is the relocatable address of the code location. 
IMAGE_SYM_CLASS_FUNCTION= 101,// Used by Microsoft tools for symbol records that define the extent of a function: begin function (named .bf), end function (.ef), and lines in function (.lf). For .lf records, Value gives the number of source lines in the function. For .ef records, Value gives the size of function code. 
IMAGE_SYM_CLASS_END_OF_STRUCT= 102,// End of structure entry. 
IMAGE_SYM_CLASS_FILE= 103,// Used by Microsoft tools, as well as traditional COFF format, for the source-file symbol record. The symbol is followed by auxiliary records that name the file. 
IMAGE_SYM_CLASS_SECTION= 104,// Definition of a section (Microsoft tools use STATIC storage class instead). 
IMAGE_SYM_CLASS_WEAK_EXTERNAL= 105,// Weak external. See Section 5.5.3, ¡°Auxiliary Format 3: Weak Externals,¡± for more information. 
};
#endif
STFLAGSARRAY CObjFileView::SymStorageClassArray[]={
{"IMAGE_SYM_CLASS_END_OF_FUNCTION", -1," (0xFF) Special symbol representing end of function, for debugging purposes. "},
{"IMAGE_SYM_CLASS_NULL", 0 ,"No storage class assigned. "},
{"IMAGE_SYM_CLASS_AUTOMATIC", 1 ,"Automatic (stack) variable. The Value field specifies stack frame offset. "},
{"IMAGE_SYM_CLASS_EXTERNAL", 2 ,"Used by Microsoft tools for external symbols. The Value field indicates the size if the section number is IMAGE_SYM_UNDEFINED (0). If the section number is not 0, then the Value field specifies the offset within the section. "},
{"IMAGE_SYM_CLASS_STATIC", 3 ,"The Value field specifies the offset of the symbol within the section. If the Value is 0, then the symbol represents a section name. "},
{"IMAGE_SYM_CLASS_REGISTER", 4 ,"Register variable. The Value field specifies register number. "},
{"IMAGE_SYM_CLASS_EXTERNAL_DEF", 5 ,"Symbol is defined externally. "},
{"IMAGE_SYM_CLASS_LABEL", 6 ,"Code label defined within the module. The Value field specifies the offset of the symbol within the section. "},
{"IMAGE_SYM_CLASS_UNDEFINED_LABEL", 7 ,"Reference to a code label not defined. "},
{"IMAGE_SYM_CLASS_MEMBER_OF_STRUCT", 8 ,"Structure member. The Value field specifies nth member. "},
{"IMAGE_SYM_CLASS_ARGUMENT", 9 ,"Formal argument (parameter)of a function. The Value field specifies nth argument. "},
{"IMAGE_SYM_CLASS_STRUCT_TAG", 10 ,"Structure tag-name entry. "},
{"IMAGE_SYM_CLASS_MEMBER_OF_UNION", 11 ,"Union member. The Value field specifies nth member. "},
{"IMAGE_SYM_CLASS_UNION_TAG", 12 ,"Union tag-name entry. "},
{"IMAGE_SYM_CLASS_TYPE_DEFINITION", 13 ,"Typedef entry. "},
{"IMAGE_SYM_CLASS_UNDEFINED_STATIC", 14 ,"Static data declaration. "},
{"IMAGE_SYM_CLASS_ENUM_TAG", 15 ,"Enumerated type tagname entry. "},
{"IMAGE_SYM_CLASS_MEMBER_OF_ENUM", 16 ,"Member of enumeration. Value specifies nth member. "},
{"IMAGE_SYM_CLASS_REGISTER_PARAM", 17 ,"Register parameter. "},
{"IMAGE_SYM_CLASS_BIT_FIELD", 18 ,"Bit-field reference. Value specifies nth bit in the bit field. "},
{"IMAGE_SYM_CLASS_BLOCK", 100 ,"A .bb (beginning of block) or .eb (end of block) record. Value is the relocatable address of the code location. "},
{"IMAGE_SYM_CLASS_FUNCTION", 101 ,"Used by Microsoft tools for symbol records that define the extent of a function: begin function (named .bf), end function (.ef), and lines in function (.lf). For .lf records, Value gives the number of source lines in the function. For .ef records, Value gives the size of function code. "},
{"IMAGE_SYM_CLASS_END_OF_STRUCT", 102 ,"End of structure entry. "},
{"IMAGE_SYM_CLASS_FILE", 103 ,"Used by Microsoft tools, as well as traditional COFF format, for the source-file symbol record. The symbol is followed by auxiliary records that name the file. "},
{"IMAGE_SYM_CLASS_SECTION", 104 ,"Definition of a section (Microsoft tools use STATIC storage class instead). "},
{"IMAGE_SYM_CLASS_WEAK_EXTERNAL", 105 ,"Weak external. See Section 5.5.3, ¡°Auxiliary Format 3: Weak Externals,¡± for more information. "},
};
WISP_MSG_MAP_BEGIN(CObjFileView)
//WISP_MSG_MAP(WISP_WM_KEY_EVENT,OnKeyEvent)
WISP_MSG_MAP(WISP_WM_CREATE,OnCreate)
WISP_MSG_MAP(WISP_WM_DESTROY,OnDestroy)
//WISP_MSG_MAP(WISP_WM_RECALCLAYOUT,OnRecalcLayout)
WISP_MSG_MAP_ON_COMMAND
WISP_MSG_MAP_ON_EVENT
WISP_MSG_MAP_END(CWispList) 

WISP_MSG_EVENT_MAP_BEGIN(CObjFileView)
//WISP_MSG_EVENT_MAP(EVENT_ID_TYPEVIEWERWND_HEX_DISPLAY,OnHexDisplayEvent)
//WISP_MSG_EVENT_MAP(EVENT_ID_TYPEVIEWERWND_DELETE_WATCH,OnDeleteWatchEvent)
WISP_MSG_EVENT_MAP_END

WISP_MSG_CMD_MAP_BEGIN(CObjFileView)
//WISP_MSG_EVENT_MAP(EVENT_ID_TYPEVIEWERWND_HEX_DISPLAY,OnHexDisplayEvent)
//WISP_MSG_EVENT_MAP(EVENT_ID_TYPEVIEWERWND_DELETE_WATCH,OnDeleteWatchEvent)
WISP_MSG_CMD_MAP_END
CObjFileView::CObjFileView()
{
}
CObjFileView::~CObjFileView()
{
}

bool CObjFileView::OnCreate(IN WISP_MSG* pMsg)
{
	HANDLE hItem,hSubItem,hNextItem,hOldItem;
	DWORD Characteristics;
	CNoPDBSymbol NoPDBSymbol;
	char NameSymBuf[256];
	NoPDBSymbol.Init();
	//D:\Prg\syser\Project\Win32\Syser\Debug
	//m_ObjFile.Open("D:\\Prg\\syser\\Project\\Win32\\Syser\\Debug\\addtypeviewerdlg.obj");

	//m_ObjFile.Open("D:\\Prg\\syser\\Source\\Syser\\objchk_wxp_x86\\i386\\addtypeviewerdlg.obj");
	//m_ObjFile.Open("D:\\temp\\Debug\\stdafx.obj");
	//m_ObjFile.Open("D:\\temp\\Debug\\nnnView.obj");
	m_ObjFile.Open("D:\\delete\\Debug\\main.obj");
	InsertColumn(WSTR("Name"),200);
	InsertColumn(WSTR("Value"),100);
	InsertColumn(WSTR("Type"),100);
	InsertColumn(WSTR("Offset"),5);
	char *SectionName;
	int i,j,k;
	POBJ_RELOCATION_ITEM pRel;
	POBJ_LINENUMBER pLineNum;
	bool FirstSymbolSection=true;
	char* SymbolName;
	char RelName[20];
//	WCHAR WName[100];
	DWORD Size;
	//OBJ_SECTION*m_Section;
	//int	m_SectCount;
	hItem = InsertItemA("FILE_HEADER");

	hSubItem = InsertItemA("Machine",hItem);
	SetItemNum(hSubItem,1,m_ObjFile.m_ObjHead.Machine,WSTR("%08x"));
	hSubItem = InsertItemA("NumberOfSections",hItem);
	SetItemNum(hSubItem,1,m_ObjFile.m_ObjHead.NumberOfSections,WSTR("%d"));
	hSubItem = InsertItemA("TimeDateStamp",hItem);
	SetItemNum(hSubItem,1,m_ObjFile.m_ObjHead.TimeDateStamp,WSTR("%08x"));
	hSubItem = InsertItemA("PointerToSymbolTable",hItem);
	SetItemNum(hSubItem,1,m_ObjFile.m_ObjHead.PointerToSymbolTable,WSTR("%d"));
	hSubItem = InsertItemA("NumberOfSymbols",hItem);
	SetItemNum(hSubItem,1,m_ObjFile.m_ObjHead.NumberOfSymbols,WSTR("%08x"));
	hSubItem = InsertItemA("SizeOfOptionalHeader",hItem);
	SetItemNum(hSubItem,1,m_ObjFile.m_ObjHead.SizeOfOptionalHeader,WSTR("%d"));
	hSubItem = InsertItemA("Characteristics",hItem);
	SetItemNum(hSubItem,1,m_ObjFile.m_ObjHead.Characteristics,WSTR("%08x"));
	for(i = 0; i < sizeof(FileHeaderCharacteristicsArray)/sizeof(FileHeaderCharacteristicsArray[0]);i++)
	{
		if(m_ObjFile.m_ObjHead.Characteristics&FileHeaderCharacteristicsArray[i].FlagsValue)
		{
			hNextItem = InsertItemA(FileHeaderCharacteristicsArray[i].FlagsName,hSubItem);
			SetItemNum(hNextItem,1,FileHeaderCharacteristicsArray[i].FlagsValue,WSTR("%08x"));
		}
	}
	for(i = 0; i < m_ObjFile.m_SectCount; i++)
	{
		SectionName = m_ObjFile.GetSectionName(i);
		if(SectionName)
		{
			hItem = InsertItemA(SectionName);
			hSubItem = InsertItemA("VirtualSize",hItem);
			SetItemNum(hSubItem,1,m_ObjFile.m_Section[i].Misc.VirtualSize,WSTR("%08x"));
			hSubItem = InsertItemA("VirtualAddress",hItem);
			SetItemNum(hSubItem,1,m_ObjFile.m_Section[i].VirtualAddress,WSTR("%08x"));
			hSubItem = InsertItemA("SizeOfRawData",hItem);
			SetItemNum(hSubItem,1,m_ObjFile.m_Section[i].SizeOfRawData,WSTR("%08x"));
			hSubItem = InsertItemA("PointerToRawData",hItem);
			SetItemNum(hSubItem,1,m_ObjFile.m_Section[i].PointerToRawData,WSTR("%08x"));
			hSubItem = InsertItemA("PointerToRelocations",hItem);
			
			SetItemNum(hSubItem,1,m_ObjFile.m_Section[i].PointerToRelocations,WSTR("%08x"));
			if(m_ObjFile.m_Section[i].PointerToRelocations&&m_ObjFile.m_Section[i].NumberOfRelocations)
			{
				Size = sizeof(OBJ_RELOCATION_ITEM)*m_ObjFile.m_Section[i].NumberOfRelocations;
				pRel = new OBJ_RELOCATION_ITEM[m_ObjFile.m_Section[i].NumberOfRelocations];
				m_ObjFile.ReadFile(m_ObjFile.m_Section[i].PointerToRelocations,pRel,Size);
				for(k = 0; k < m_ObjFile.m_Section[i].NumberOfRelocations;k++)
				{
					TSPrintf(RelName,"Rel[%d]",k);
					hOldItem = InsertItemA(RelName,hSubItem);
					hNextItem = InsertItemA("VirtualAddress",hOldItem);
					SetItemNum(hNextItem,1,pRel[k].VirtualAddress);
					hNextItem = InsertItemA("SymbolTableIndex",hOldItem);
					SetItemNum(hNextItem,1,pRel[k].SymbolTableIndex);
					SymbolName = m_ObjFile.GetSymbolNameByIndex(pRel[k].SymbolTableIndex);
					if(SymbolName)
					{
						if(NoPDBSymbol.m_UnDecorateSymbolName(SymbolName,NameSymBuf,sizeof(NameSymBuf),0))
							InsertItemA(NameSymBuf,hNextItem);
						else
							InsertItemA(SymbolName,hNextItem);
						delete []SymbolName;
					}
					hNextItem = InsertItemA("Type",hOldItem);
					SetItemNum(hNextItem,1,pRel[k].Type);
					for(int p = 0; p < sizeof(RleFlagsArray)/sizeof(RleFlagsArray[0]);p++)
					{
						if(pRel[k].Type==RleFlagsArray[p].FlagsValue)
						{
							//TStrCpy(WName,RleFlagsArray[p].FlagsName);
							SetItemTextA(hNextItem,1,RleFlagsArray[p].FlagsName);
							//hChildItem = InsertItemA(RleFlagsArray[p].FlagsName,hNextItem);
							//SetItemNum(hChildItem,1,RleFlagsArray[p].FlagsValue,WSTR("%08x"));
						}
					}

				}
				delete []pRel;
			}
			hSubItem = InsertItemA("PointerToLinenumbers",hItem);
			SetItemNum(hSubItem,1,m_ObjFile.m_Section[i].PointerToLinenumbers,WSTR("%08x"));
			if(m_ObjFile.m_Section[i].PointerToLinenumbers&&m_ObjFile.m_Section[i].NumberOfLinenumbers)
			{
				Size = sizeof(OBJ_LINENUMBER)*m_ObjFile.m_Section[i].NumberOfLinenumbers;
				pLineNum = new OBJ_LINENUMBER[m_ObjFile.m_Section[i].NumberOfLinenumbers];
				m_ObjFile.ReadFile(m_ObjFile.m_Section[i].PointerToLinenumbers,pLineNum,Size);
				for(k = 0; k < m_ObjFile.m_Section[i].NumberOfLinenumbers;k++)
				{
					TSPrintf(RelName,"Line[%d]",k);
					hOldItem = InsertItemA(RelName,hSubItem);
					if(pLineNum[k].Linenumber==0)
					{
						hNextItem = InsertItemA("SymbolTableIndex",hOldItem);
						SymbolName = m_ObjFile.GetSymbolNameByIndex(pLineNum[k].Type.SymbolTableIndex);
						if(SymbolName)
						{
							if(NoPDBSymbol.m_UnDecorateSymbolName(SymbolName,NameSymBuf,sizeof(NameSymBuf),0))
								InsertItemA(NameSymBuf,hNextItem);
							else
								InsertItemA(SymbolName,hNextItem);
							delete []SymbolName;
						}
					}
					else
						hNextItem = InsertItemA("VirtualAddress",hOldItem);
					SetItemNum(hNextItem,1,pLineNum[k].Type.VirtualAddress);
					hNextItem = InsertItemA("Linenumber",hOldItem);
					SetItemNum(hNextItem,1,pLineNum[k].Linenumber);
				}
				delete []pLineNum;
			}
			hSubItem = InsertItemA("NumberOfRelocations",hItem);
			SetItemNum(hSubItem,1,m_ObjFile.m_Section[i].NumberOfRelocations,WSTR("%08x"));
			hSubItem = InsertItemA("NumberOfLinenumbers",hItem);
			SetItemNum(hSubItem,1,m_ObjFile.m_Section[i].NumberOfLinenumbers,WSTR("%08x"));
			hSubItem = InsertItemA("Characteristics",hItem);
			Characteristics = m_ObjFile.m_Section[i].Characteristics;
			SetItemNum(hSubItem,1,Characteristics,WSTR("%08x"));
			for(j = 0; j < 27; j++)
			{
				if(Characteristics&FlagsArray[j].FlagsValue)
				{
					hNextItem = InsertItemA(FlagsArray[j].FlagsName,hSubItem);
					SetItemNum(hNextItem,1,FlagsArray[j].FlagsValue,WSTR("%08x"));
				}
			}
			for(j=27;j<sizeof(FlagsArray)/sizeof(FlagsArray[0]);j++)
			{
				if((Characteristics&0xf00000)==FlagsArray[j].FlagsValue)
				{
					hNextItem = InsertItemA(FlagsArray[j].FlagsName,hSubItem);
					SetItemNum(hNextItem,1,FlagsArray[j].FlagsValue,WSTR("%08x"));
				}
			}
			if(TStrCmp(SectionName,".debug$S")==0||TStrCmp(SectionName,".debug$P")==0)
			{
				AnalyserSymbolSection(hItem,&m_ObjFile.m_Section[i],FirstSymbolSection);
				FirstSymbolSection=false;
			}else if(TStrCmp(SectionName,".debug$T")==0)
			{
				AnalyserTypeSection(hItem,&m_ObjFile.m_Section[i],true);
			}
		}
	}
	hItem = InsertItemA("Symbols");
	WORD symtype;
	char TempChar='\0';
	char* NameFull;
	for(i=0;(unsigned int)i<m_ObjFile.m_ObjHead.NumberOfSymbols;i++)
	{
		TSPrintf(RelName,"Sym[%d]",i);
		hNextItem = InsertItemA(RelName,hItem);		
		SymbolName = m_ObjFile.GetSymbolNameByIndex(i);
		hSubItem = InsertItemA("Name",hNextItem);
		if(SymbolName)
		{
			if(NoPDBSymbol.m_UnDecorateSymbolName(SymbolName,NameSymBuf,sizeof(NameSymBuf),0))
				SetItemTextA(hSubItem,1,NameSymBuf);
			else
				SetItemTextA(hSubItem,1,SymbolName);
			NameFull=SymbolName;
		}
		else
		{
			NameFull=&TempChar;
		}
		hSubItem = InsertItemA("Value",hNextItem);
		SetItemNum(hSubItem,1,m_ObjFile.m_ObjSymAry[i].Value);
		symtype = m_ObjFile.m_ObjSymAry[i].Type&0xff;
		if(symtype<sizeof(SymBaseTypeArray)/sizeof(SymBaseTypeArray[0]))
		{
			InsertItemA(SymBaseTypeArray[symtype].FlagsName,hNextItem);
		}
		symtype = (m_ObjFile.m_ObjSymAry[i].Type&0xff00)>>8;
		if(symtype<sizeof(SymComplexTypeArray)/sizeof(SymComplexTypeArray[0]))
		{
			InsertItemA(SymComplexTypeArray[symtype].FlagsName,hNextItem);
		}
		hSubItem = InsertItemA("SectionNumber",hNextItem);	
		switch(m_ObjFile.m_ObjSymAry[i].SectionNumber)
		{
		case 0:
			SetItemTextA(hSubItem,1,"IMAGE_SYM_UNDEFINED");
			break;
		case -1:
			SetItemTextA(hSubItem,1,"IMAGE_SYM_ABSOLUTE");
			break;
		case -2:
			SetItemTextA(hSubItem,1,"IMAGE_SYM_DEBUG");
			break;
		default:
		SetItemNum(hSubItem,1,m_ObjFile.m_ObjSymAry[i].SectionNumber);
		}
		for(k = 0; k < sizeof(SymStorageClassArray)/sizeof(SymStorageClassArray[0]);k++)
		{
			if(m_ObjFile.m_ObjSymAry[i].StorageClass==SymStorageClassArray[k].FlagsValue)
			{
				hSubItem = InsertItemA("StorageClass",hNextItem);
				SetItemTextA(hSubItem,1,SymStorageClassArray[k].FlagsName);
			}
		}
		hSubItem = InsertItemA("NumberOfAuxSymbols",hNextItem);
		SetItemNum(hSubItem,1,m_ObjFile.m_ObjSymAry[i].NumberOfAuxSymbols);
		if(m_ObjFile.m_ObjSymAry[i].NumberOfAuxSymbols
			&&m_ObjFile.m_ObjSymAry[i].StorageClass==IMAGE_SYM_CLASS_EXTERNAL//IMAGE_SYM_CLASS_EXTERNAL
			&&m_ObjFile.m_ObjSymAry[i].Type==0x20
			&&m_ObjFile.m_ObjSymAry[i].SectionNumber>0)
		{
			OBJ_IMAGE_AUX_SYMBOL* AuxFuncDefine=(OBJ_IMAGE_AUX_SYMBOL*)&m_ObjFile.m_ObjSymAry[i+1];
			hNextItem = InsertItemA("Function Definitions",hNextItem);
			hSubItem = InsertItemA("TagIndex",hNextItem);
			SetItemNum(hSubItem,1,AuxFuncDefine->Sym.TagIndex);
			hSubItem = InsertItemA("TotalSize",hNextItem);
			SetItemNum(hSubItem,1,AuxFuncDefine->Sym.Misc.TotalSize);
			hSubItem = InsertItemA("PointerToLinenumber",hNextItem);
			SetItemNum(hSubItem,1,AuxFuncDefine->Sym.FcnAry.Function.PointerToLinenumber);
			hSubItem = InsertItemA("PointerToNextFunction",hNextItem);
			SetItemNum(hSubItem,1,AuxFuncDefine->Sym.FcnAry.Function.PointerToNextFunction);
			hSubItem = InsertItemA("Unused.",hNextItem);
		}
		if(m_ObjFile.m_ObjSymAry[i].NumberOfAuxSymbols
			&&m_ObjFile.m_ObjSymAry[i].StorageClass==101)
		{
			OBJ_IMAGE_AUX_SYMBOL* AuxFuncDefine=(OBJ_IMAGE_AUX_SYMBOL*)&m_ObjFile.m_ObjSymAry[i+1];
			if(TStrCmp(NameFull,".bf")==0)
			{
				hNextItem = InsertItemA(".bf Auxiliary",hNextItem);
				hSubItem = InsertItemA("Unused",hNextItem);
				SetItemNum(hSubItem,1,AuxFuncDefine->bf.Unused);
				hSubItem = InsertItemA("Linenumber",hNextItem);
				SetItemNum(hSubItem,1,AuxFuncDefine->bf.Linenumber,WSTR("%d"));
				hSubItem = InsertItemA("Unused1",hNextItem);
				//SetItemNum(hSubItem,1,AuxFuncDefine->bf.Unused);
				hSubItem = InsertItemA("PointerToNextFunction",hNextItem);
				SetItemNum(hSubItem,1,AuxFuncDefine->bf.PointerToNextFunction);
				hSubItem = InsertItemA("Unused2",hNextItem);
				SetItemNum(hSubItem,1,AuxFuncDefine->bf.Unused2);
			}else if(TStrCmp(NameFull,".lf")==0)
			{
				hNextItem = InsertItemA(".lf Auxiliary",hNextItem);
				hSubItem = InsertItemA("Unused",hNextItem);
				SetItemNum(hSubItem,1,AuxFuncDefine->bf.Unused);
				hSubItem = InsertItemA("Linenumber",hNextItem);
				SetItemNum(hSubItem,1,AuxFuncDefine->bf.Linenumber,WSTR("%d"));
				hSubItem = InsertItemA("Unused1",hNextItem);
				//SetItemNum(hSubItem,1,AuxFuncDefine->bf.Unused);
				hSubItem = InsertItemA("PointerToNextFunction",hNextItem);
				SetItemNum(hSubItem,1,AuxFuncDefine->bf.PointerToNextFunction);
				hSubItem = InsertItemA("Unused2",hNextItem);
				SetItemNum(hSubItem,1,AuxFuncDefine->bf.Unused2);
			}else if(TStrCmp(NameFull,".ef")==0)
			{
				hNextItem = InsertItemA(".ef Auxiliary",hNextItem);
				hSubItem = InsertItemA("Unused",hNextItem);
				SetItemNum(hSubItem,1,AuxFuncDefine->bf.Unused);
				hSubItem = InsertItemA("Linenumber",hNextItem);
				SetItemNum(hSubItem,1,AuxFuncDefine->bf.Linenumber,WSTR("%d"));
				hSubItem = InsertItemA("Unused1",hNextItem);
				//SetItemNum(hSubItem,1,AuxFuncDefine->bf.Unused);
				hSubItem = InsertItemA("PointerToNextFunction",hNextItem);
				SetItemNum(hSubItem,1,AuxFuncDefine->bf.PointerToNextFunction);
				hSubItem = InsertItemA("Unused2",hNextItem);
				SetItemNum(hSubItem,1,AuxFuncDefine->bf.Unused2);
			}
		}
		if(m_ObjFile.m_ObjSymAry[i].NumberOfAuxSymbols
			&&m_ObjFile.m_ObjSymAry[i].StorageClass==IMAGE_SYM_CLASS_FILE)
		{
			if(TStrCmp(NameFull,".file")==0)
			{
				OBJ_IMAGE_AUX_SYMBOL* AuxFuncDefine=(OBJ_IMAGE_AUX_SYMBOL*)&m_ObjFile.m_ObjSymAry[i+1];
				hNextItem = InsertItemA(".file Auxiliary",hNextItem);
				InsertItemA((const char*)AuxFuncDefine->File.Name,hNextItem);
			}
		}
		if(m_ObjFile.m_ObjSymAry[i].NumberOfAuxSymbols
			&&m_ObjFile.m_ObjSymAry[i].StorageClass==IMAGE_SYM_CLASS_WEAK_EXTERNAL
			&&m_ObjFile.m_ObjSymAry[i].SectionNumber==0
			&&m_ObjFile.m_ObjSymAry[i].Value==0)
		{
			OBJ_IMAGE_AUX_SYMBOL* AuxFuncDefine=(OBJ_IMAGE_AUX_SYMBOL*)&m_ObjFile.m_ObjSymAry[i+1];
			hNextItem = InsertItemA("Weak Externals Auxiliary",hNextItem);
			hSubItem = InsertItemA("TagIndex",hNextItem);
			SetItemNum(hSubItem,1,AuxFuncDefine->WeakExternals.TagIndex);
			hSubItem = InsertItemA("Characteristics ",hNextItem);
			SetItemNum(hSubItem,1,AuxFuncDefine->WeakExternals.Characteristics);
		}
		i += m_ObjFile.m_ObjSymAry[i].NumberOfAuxSymbols;
		if(SymbolName)
			delete []SymbolName;
	}
	NoPDBSymbol.Release();
	return true;
}

bool CObjFileView::OnDestroy(IN WISP_MSG* pMsg)
{
	m_ObjFile.Close();
	return true;
}
bool CObjFileView::AnalyserSymbolSection(HANDLE hItem,OBJ_SECTION* ObjSection,bool FirstSymbolSection)
{
	char NameBuf[256];
	int i;
	BYTE *pStart;
	char BufName[20];
	SYMRECORD* SymRecord;
	DWORD Index = 0;
	HANDLE hNextItem,hSubItem,hRootItem;
	DWORD Counter=0;
	if(FirstSymbolSection)
		Counter=4;
	pStart = &m_ObjFile.m_FileBody[ObjSection->PointerToRawData+Counter];
	SymRecord = (SYMRECORD*)pStart;
	while(Counter<ObjSection->SizeOfRawData)
	{
		TSPrintf(BufName,"Sym[%d]",Index);
		hRootItem = hSubItem = InsertItemA(BufName,hItem);
		hNextItem = InsertItemA("Size",hSubItem);
		SetItemNum(hNextItem,1,SymRecord->Length);
		hNextItem = InsertItemA("Type",hSubItem);
		SetItemNum(hNextItem,1,SymRecord->u1.Type);
		switch(SymRecord->u1.Type)
		{
		case SYM_S_COMPILE:
			{
				SetItemTextA(hRootItem,1,"SYM_S_COMPILE");
				hNextItem = InsertItemA("Machine",hSubItem);
				for(i =0;i < sizeof(COMPILE_machineArray)/sizeof(COMPILE_machineArray[0]);i++)
				{
					if(SymRecord->u.S_COMPILE.Machine==COMPILE_machineArray[i].FlagsValue)
						SetItemTextA(hNextItem,1,COMPILE_machineArray[i].FlagsName);
				}
				hNextItem = InsertItemA("Language",hSubItem);
				bool bFind=false;
				for(i = 0;i<sizeof(COMPILE_LanguageArray)/sizeof(COMPILE_LanguageArray[0]);i++)
				{
					if(SymRecord->u.S_COMPILE.flags[0]==COMPILE_LanguageArray[i].FlagsValue)
					{
						bFind=true;
						SetItemTextA(hNextItem,1,COMPILE_LanguageArray[i].FlagsName);
					}
				}
				WORD TempFlags=*(WORD*)&SymRecord->u.S_COMPILE.flags[1];
				hNextItem = InsertItemA("PCodePresent",hSubItem);
				SetItemNum(hNextItem,1,TempFlags&1);
				hNextItem = InsertItemA("FloatPrecision",hSubItem);
				SetItemNum(hNextItem,1,(TempFlags>>1)&3);
				hNextItem = InsertItemA("FloatPackage",hSubItem);
				SetItemNum(hNextItem,1,(TempFlags>>3)&3);
				hNextItem = InsertItemA("AmbientData",hSubItem);
				SetItemNum(hNextItem,1,(TempFlags>>5)&7);
				hNextItem = InsertItemA("AmbientCode",hSubItem);
				SetItemNum(hNextItem,1,(TempFlags>>8)&7);
				hNextItem = InsertItemA("Mode32",hSubItem);
				SetItemNum(hNextItem,1,(TempFlags>>11)&1);
				TStrCpyLimit(NameBuf,&SymRecord->u.S_COMPILE.version[1],SymRecord->u.S_COMPILE.version[0]+1);
				hNextItem = InsertItemA("SymName",hSubItem);
				SetItemTextA(hNextItem,1,NameBuf);
			}
			break;
		case SYM_S_REGISTER:
			{
				SetItemTextA(hRootItem,1,"SYM_S_REGISTER");
				hNextItem = InsertItemA("TypeIndex",hSubItem);
				SetItemNum(hNextItem,1,SymRecord->u.S_REGISTER.TypeIndex);
				for(i = 0;i < sizeof(X86X87RegisterArray)/sizeof(X86X87RegisterArray[0]);i++)
				{
					if(SymRecord->u.S_REGISTER.Register==X86X87RegisterArray[i].FlagsValue)
					{
						hNextItem = InsertItemA("Register",hSubItem);
						SetItemTextA(hNextItem,1,X86X87RegisterArray[i].FlagsName);
					}
				}
				TStrCpyLimit(NameBuf,&SymRecord->u.S_REGISTER.Name[1],SymRecord->u.S_REGISTER.Name[0]+1);
				hNextItem = InsertItemA("SymName",hSubItem);
				SetItemTextA(hNextItem,1,NameBuf);
			}
			break;
		case SYM_S_BPREL32:
			{
				SetItemTextA(hRootItem,1,"SYM_S_BPREL32");
				hNextItem = InsertItemA("TypeIndex",hSubItem);
				SetItemNum(hNextItem,1,SymRecord->u.S_BPREL32.TypeIndex);
				hNextItem = InsertItemA("Offset",hSubItem);
				SetItemNum(hNextItem,1,SymRecord->u.S_BPREL32.Offset);
				TStrCpyLimit(NameBuf,&SymRecord->u.S_BPREL32.Name[1],SymRecord->u.S_BPREL32.Name[0]+1);
				hNextItem = InsertItemA("SymName",hSubItem);
				SetItemTextA(hNextItem,1,NameBuf);
			}			
			break;
		case SYM_S_LPROC32:
			{
				SetItemTextA(hRootItem,1,"SYM_S_LPROC32");
				hNextItem = InsertItemA("pParent",hSubItem);
				SetItemNum(hNextItem,1,SymRecord->u.S_GPROC32.pParent);
				hNextItem = InsertItemA("pEnd",hSubItem);
				SetItemNum(hNextItem,1,SymRecord->u.S_GPROC32.pEnd);
				hNextItem = InsertItemA("pNext",hSubItem);
				SetItemNum(hNextItem,1,SymRecord->u.S_GPROC32.pNext);
				hNextItem = InsertItemA("ProcLength",hSubItem);
				SetItemNum(hNextItem,1,SymRecord->u.S_GPROC32.ProcLength);
				hNextItem = InsertItemA("DebugStart",hSubItem);
				SetItemNum(hNextItem,1,SymRecord->u.S_GPROC32.DebugStart);
				hNextItem = InsertItemA("DebugEnd",hSubItem);
				SetItemNum(hNextItem,1,SymRecord->u.S_GPROC32.DebugEnd);
				hNextItem = InsertItemA("ProcType",hSubItem);
				SetItemNum(hNextItem,1,SymRecord->u.S_GPROC32.ProcType);
				hNextItem = InsertItemA("Offset",hSubItem);
				SetItemNum(hNextItem,1,SymRecord->u.S_GPROC32.Offset);
				hNextItem = InsertItemA("Segment",hSubItem);
				SetItemNum(hNextItem,1,SymRecord->u.S_GPROC32.Segment);
				hNextItem = InsertItemA("Flags",hSubItem);
				SetItemNum(hNextItem,1,SymRecord->u.S_GPROC32.Flags);
				TStrCpyLimit(NameBuf,&SymRecord->u.S_GPROC32.Name[1],SymRecord->u.S_GPROC32.Name[0]+1);
				hNextItem = InsertItemA("SymName",hSubItem);
				SetItemTextA(hNextItem,1,NameBuf);
			}
			break;
		case SYM_S_GPROC32:
			{
				SetItemTextA(hRootItem,1,"SYM_S_GPROC32");
				hNextItem = InsertItemA("pParent",hSubItem);
				SetItemNum(hNextItem,1,SymRecord->u.S_GPROC32.pParent);
				hNextItem = InsertItemA("pEnd",hSubItem);
				SetItemNum(hNextItem,1,SymRecord->u.S_GPROC32.pEnd);
				hNextItem = InsertItemA("pNext",hSubItem);
				SetItemNum(hNextItem,1,SymRecord->u.S_GPROC32.pNext);
				hNextItem = InsertItemA("ProcLength",hSubItem);
				SetItemNum(hNextItem,1,SymRecord->u.S_GPROC32.ProcLength);
				hNextItem = InsertItemA("DebugStart",hSubItem);
				SetItemNum(hNextItem,1,SymRecord->u.S_GPROC32.DebugStart);
				hNextItem = InsertItemA("DebugEnd",hSubItem);
				SetItemNum(hNextItem,1,SymRecord->u.S_GPROC32.DebugEnd);
				hNextItem = InsertItemA("ProcType",hSubItem);
				SetItemNum(hNextItem,1,SymRecord->u.S_GPROC32.ProcType);
				hNextItem = InsertItemA("Offset",hSubItem);
				SetItemNum(hNextItem,1,SymRecord->u.S_GPROC32.Offset);
				hNextItem = InsertItemA("Segment",hSubItem);
				SetItemNum(hNextItem,1,SymRecord->u.S_GPROC32.Segment);
				hNextItem = InsertItemA("Flags",hSubItem);
				SetItemNum(hNextItem,1,SymRecord->u.S_GPROC32.Flags);
				TStrCpyLimit(NameBuf,&SymRecord->u.S_GPROC32.Name[1],SymRecord->u.S_GPROC32.Name[0]+1);
				hNextItem = InsertItemA("SymName",hSubItem);
				SetItemTextA(hNextItem,1,NameBuf);
			}
			break;
		case SYM_S_GDATA32:
			SetItemTextA(hRootItem,1,"SYM_S_GDATA32");
			hNextItem = InsertItemA("TypeIndex",hSubItem);
			SetItemNum(hNextItem,1,SymRecord->u.S_LDATA32.TypeIndex);
			hNextItem = InsertItemA("Offset",hSubItem);
			SetItemNum(hNextItem,1,SymRecord->u.S_LDATA32.Offset);
			hNextItem = InsertItemA("Segment",hSubItem);
			SetItemNum(hNextItem,1,SymRecord->u.S_LDATA32.Segment);
			TStrCpyLimit(NameBuf,&SymRecord->u.S_LDATA32.Name[1],SymRecord->u.S_LDATA32.Name[0]+1);
			hNextItem = InsertItemA("SymName",hSubItem);
			SetItemTextA(hNextItem,1,NameBuf);
			break;
		case SYM_S_LDATA32:
			SetItemTextA(hRootItem,1,"SYM_S_LDATA32");
			hNextItem = InsertItemA("TypeIndex",hSubItem);
			SetItemNum(hNextItem,1,SymRecord->u.S_LDATA32.TypeIndex);
			hNextItem = InsertItemA("Offset",hSubItem);
			SetItemNum(hNextItem,1,SymRecord->u.S_LDATA32.Offset);
			hNextItem = InsertItemA("Segment",hSubItem);
			SetItemNum(hNextItem,1,SymRecord->u.S_LDATA32.Segment);
			TStrCpyLimit(NameBuf,&SymRecord->u.S_LDATA32.Name[1],SymRecord->u.S_LDATA32.Name[0]+1);
			hNextItem = InsertItemA("SymName",hSubItem);
			SetItemTextA(hNextItem,1,NameBuf);
			break;
		case SYM_S_LABEL32:
			SetItemTextA(hRootItem,1,"SYM_S_LABEL32");
			hNextItem = InsertItemA("Offset",hSubItem);
			SetItemNum(hNextItem,1,SymRecord->u.S_LABEL32.Offset);
			hNextItem = InsertItemA("Segment",hSubItem);
			SetItemNum(hNextItem,1,SymRecord->u.S_LABEL32.Segment);
			hNextItem = InsertItemA("Flags",hSubItem);
			SetItemNum(hNextItem,1,SymRecord->u.S_LABEL32.Flags);
			TStrCpyLimit(NameBuf,&SymRecord->u.S_LABEL32.Name[1],SymRecord->u.S_LABEL32.Name[0]+1);
			hNextItem = InsertItemA("SymName",hSubItem);
			SetItemTextA(hNextItem,1,NameBuf);
			break;
		case SYM_S_UDT:
			SetItemTextA(hRootItem,1,"SYM_S_UDT");
			hNextItem = InsertItemA("TypeIndex",hSubItem);
			SetItemNum(hNextItem,1,SymRecord->u.S_UDT.TypeIndex);
			TStrCpyLimit(NameBuf,&SymRecord->u.S_UDT.Name[1],SymRecord->u.S_UDT.Name[0]+1);
			hNextItem = InsertItemA("SymName",hSubItem);
			SetItemTextA(hNextItem,1,NameBuf);
			break;
		case SYM_S_CONSTANT:
			{
				SetItemTextA(hRootItem,1,"SYM_S_CONSTANT");
				hNextItem = InsertItemA("TypeIndex",hSubItem);
				SetItemNum(hNextItem,1,SymRecord->u.S_CONSTANT.TypeIndex);
				if(SymRecord->u.S_CONSTANT.Value<0x8000)
				{
					hNextItem = InsertItemA("Value",hSubItem);
					SetItemNum(hNextItem,1,SymRecord->u.S_CONSTANT.Value);
					TStrCpyLimit(NameBuf,&SymRecord->u.S_CONSTANT.Name[1],SymRecord->u.S_CONSTANT.Name[0]+1);
					hNextItem = InsertItemA("SymName",hSubItem);
					SetItemTextA(hNextItem,1,NameBuf);
				}
				else
				{
					hNextItem = InsertItemA("Value",hSubItem);
					int NameOffset=0;
					switch(SymRecord->u.S_CONSTANT.Value)
					{						
					case LF_CHAR		:
						NameOffset=1;SetItemNum(hNextItem,1,SymRecord->u.S_CONSTANT.Name[0]);break;
					case LF_SHORT		:
						NameOffset=2;SetItemNum(hNextItem,1,*(short*)&SymRecord->u.S_CONSTANT.Name[0]);break;
					case LF_USHORT		:
						NameOffset=2;SetItemNum(hNextItem,1,*(unsigned short*)&SymRecord->u.S_CONSTANT.Name[0]);break;
					case LF_LONG		:
						NameOffset=4;SetItemNum(hNextItem,1,*(long*)&SymRecord->u.S_CONSTANT.Name[0]);break;
					case LF_ULONG		:
						NameOffset=4;SetItemNum(hNextItem,1,*(unsigned long*)&SymRecord->u.S_CONSTANT.Name[0]);break;
					case LF_REAL32		:
						NameOffset=4;break;
					case LF_REAL64		:
						NameOffset=8;break;
					case LF_REAL80		:
						NameOffset=10;break;
					case LF_REAL128		:
						NameOffset=16;break;
						break;
					case LF_QUADWORD	:
						NameOffset=8;SetItemNum(hNextItem,1,*(UINT*)&SymRecord->u.S_CONSTANT.Name[0]);break;
					case LF_UQUADWORD	:
						NameOffset=8;SetItemNum(hNextItem,1,*(UINT*)&SymRecord->u.S_CONSTANT.Name[0]);break;
					case LF_REAL48		:
						NameOffset=16;break;
					case LF_COMPLEX32	:
						NameOffset=8;break;
					case LF_COMPLEX64	:
						NameOffset=16;break;
					case LF_COMPLEX80	:
						NameOffset=20;break;
					case LF_COMPLEX128	:
						NameOffset=32;break;
					case LF_VARSTRING	:
						NameOffset = *(unsigned short*)&SymRecord->u.S_CONSTANT.Name[0]+2;break;
						break;
					}
					TStrCpyLimit(NameBuf,&SymRecord->u.S_CONSTANT.Name[NameOffset+1],SymRecord->u.S_CONSTANT.Name[NameOffset]+1);
					hNextItem = InsertItemA("SymName",hSubItem);
					SetItemTextA(hNextItem,1,NameBuf);
				}
			}
			break;
		}
		Counter+=2;
		Counter+=SymRecord->Length;
		SymRecord=(SYMRECORD*)&SymRecord->u1.Start[SymRecord->Length];
		Index++;
	}
	return true;
}
bool CObjFileView::AnalyserTypeSection(HANDLE hItem,OBJ_SECTION* ObjSection,bool FirstTypeSection)
{
	char NameBuf[256];
//	int j;
	BYTE *pStart;
	char BufName[20];
	TYPERECORD* TypeRecord;
	DWORD Index = 0x1000;
	HANDLE hNextItem,hSubItem,hRootItem;
	DWORD Counter=0;
	if(FirstTypeSection)
		Counter=4;
	pStart = &m_ObjFile.m_FileBody[ObjSection->PointerToRawData+Counter];
	TypeRecord = (TYPERECORD*)pStart;
	while(Counter<ObjSection->SizeOfRawData)
	{
		TSPrintf(BufName,"Type[%x]",Index);
		hRootItem = hSubItem = InsertItemA(BufName,hItem);
		hNextItem = InsertItemA("Size",hSubItem);
		SetItemNum(hNextItem,1,TypeRecord->Length);
		hNextItem = InsertItemA("Type",hSubItem);
		SetItemNum(hNextItem,1,TypeRecord->u1.Type);
		switch(TypeRecord->u1.Type)
		{
		case LF_CLASS:
			{
				int NameOffset=0;
				SetItemTextA(hRootItem,1,"LF_CLASS");
				hNextItem = InsertItemA("Count",hSubItem);
				SetItemNum(hNextItem,1,TypeRecord->u.LF_CLASS.Count);
				hNextItem = InsertItemA("property",hSubItem);
				SetItemNum(hNextItem,1,TypeRecord->u.LF_CLASS.property);
				hNextItem = InsertItemA("@field",hSubItem);
				SetItemNum(hNextItem,1,TypeRecord->u.LF_CLASS.field);
				hNextItem = InsertItemA("@dList",hSubItem);
				SetItemNum(hNextItem,1,TypeRecord->u.LF_CLASS.dList);
				hNextItem = InsertItemA("@vshape",hSubItem);
				SetItemNum(hNextItem,1,TypeRecord->u.LF_CLASS.vshape);
				if(TypeRecord->u.LF_CLASS.u.Length.Number<0x8000)
				{
					hNextItem = InsertItemA("length",hSubItem);
					SetItemNum(hNextItem,1,TypeRecord->u.LF_CLASS.u.Length.Number);
					NameOffset=2;
					TStrCpyLimit(NameBuf,&TypeRecord->u.LF_CLASS.u.Name[NameOffset+1],TypeRecord->u.LF_CLASS.u.Name[NameOffset]+1);
					hNextItem = InsertItemA("TypeName",hSubItem);
					SetItemTextA(hNextItem,1,NameBuf);
				}
			}
			
			break;
		case LF_STRUCTURE:
			SetItemTextA(hRootItem,1,"LF_STRUCTURE");
			break;
		case LF_UNION:
			SetItemTextA(hRootItem,1,"LF_UNION");
			break;
		case LF_ENUMERATE:
			SetItemTextA(hRootItem,1,"LF_ENUMERATE");
			break;
		case LF_ARRAY:
			SetItemTextA(hRootItem,1,"LF_ARRAY");
			break;
		case LF_ARGLIST:
			SetItemTextA(hRootItem,1,"LF_ARGLIST");
			break;
		case LF_FIELDLIST:
			SetItemTextA(hRootItem,1,"LF_FIELDLIST");
			break;
		case LF_LABEL:
			SetItemTextA(hRootItem,1,"LF_LABEL");
			break;
		case LF_PRECOMP:
			SetItemTextA(hRootItem,1,"LF_PRECOMP");
			break;
		case LF_MEMBERMODIFY:
			SetItemTextA(hRootItem,1,"LF_MEMBERMODIFY");
			break;
		case LF_POINTER:
			{
				SetItemTextA(hRootItem,1,"LF_POINTER");
				hNextItem = InsertItemA("TypeIndex",hSubItem);
				SetItemNum(hNextItem,1,TypeRecord->u.LF_POINTER.TypeIndex);
				hNextItem = InsertItemA("ptrtype",hSubItem);
				switch(TypeRecord->u.LF_POINTER.ptrtype)
				{
				case 0:	SetItemTextA(hNextItem,1,"Near");break;
				case 1:SetItemTextA(hNextItem,1,"Far");break;
				case 2:SetItemTextA(hNextItem,1,"Huge");break;
				case 3:SetItemTextA(hNextItem,1,"Based on segment");break;
				case 4:SetItemTextA(hNextItem,1,"Based on value");break;
				case 5:SetItemTextA(hNextItem,1,"Based on segment of value");break;
				case 6:SetItemTextA(hNextItem,1,"Based on address of symbol");break;
				case 7:SetItemTextA(hNextItem,1,"Based on segment of symbol address");break;
				case 8:SetItemTextA(hNextItem,1,"Based on type");break;
				case 9:SetItemTextA(hNextItem,1,"Based on self");break;
				case 10:SetItemTextA(hNextItem,1,"Near 32 bit pointer");break;
				case 11:SetItemTextA(hNextItem,1,"Far 32 bit pointer");break;
				case 12:SetItemTextA(hNextItem,1,"64 bit pointer");break;
				default:
					if(TypeRecord->u.LF_POINTER.ptrtype>=13&&TypeRecord->u.LF_POINTER.ptrtype<=31)
						SetItemTextA(hNextItem,1,"Reserved");
				}
				hNextItem = InsertItemA("ptrmode",hSubItem);
				switch(TypeRecord->u.LF_POINTER.ptrmode)
				{
				case 0:	SetItemTextA(hNextItem,1,"Pointer");break;
				case 1:SetItemTextA(hNextItem,1,"Reference");break;
				case 2:SetItemTextA(hNextItem,1,"Pointer to data member");break;
				case 3:SetItemTextA(hNextItem,1,"Pointer to method");break;
				default:
					if(TypeRecord->u.LF_POINTER.ptrmode>=4&&TypeRecord->u.LF_POINTER.ptrmode<=7)
						SetItemTextA(hNextItem,1,"Reserved");
				}
				hNextItem = InsertItemA("isflat32",hSubItem);
				SetItemNum(hNextItem,1,TypeRecord->u.LF_POINTER.isflat32);
				hNextItem = InsertItemA("volatile",hSubItem);
				SetItemNum(hNextItem,1,TypeRecord->u.LF_POINTER.volatileType);
				hNextItem = InsertItemA("const",hSubItem);
				SetItemNum(hNextItem,1,TypeRecord->u.LF_POINTER.constType);
				hNextItem = InsertItemA("unaligned ",hSubItem);
				SetItemNum(hNextItem,1,TypeRecord->u.LF_POINTER.unaligned);
				hNextItem = InsertItemA("restrict",hSubItem);
				SetItemNum(hNextItem,1,TypeRecord->u.LF_POINTER.restrict);
				hNextItem = InsertItemA("unused",hSubItem);
				SetItemNum(hNextItem,1,TypeRecord->u.LF_POINTER.unused);
			}
			
			break;
		case LF_PROCEDURE:
			SetItemTextA(hRootItem,1,"LF_PROCEDURE");
			break;
		case LF_MFUNCTION:
			SetItemTextA(hRootItem,1,"LF_MFUNCTION");
			hNextItem = InsertItemA("Rvtype",hSubItem);
			SetItemNum(hNextItem,1,TypeRecord->u.LF_MFUNCTION.Rvtype);
			hNextItem = InsertItemA("Class",hSubItem);
			SetItemNum(hNextItem,1,TypeRecord->u.LF_MFUNCTION.Class);
			hNextItem = InsertItemA("This",hSubItem);
			SetItemNum(hNextItem,1,TypeRecord->u.LF_MFUNCTION.This);
			hNextItem = InsertItemA("Call",hSubItem);
			SetItemNum(hNextItem,1,TypeRecord->u.LF_MFUNCTION.Call);
			hNextItem = InsertItemA("Res",hSubItem);
			SetItemNum(hNextItem,1,TypeRecord->u.LF_MFUNCTION.Res);
			hNextItem = InsertItemA("Parms",hSubItem);
			SetItemNum(hNextItem,1,TypeRecord->u.LF_MFUNCTION.Parms);
			hNextItem = InsertItemA("Arglist",hSubItem);
			SetItemNum(hNextItem,1,TypeRecord->u.LF_MFUNCTION.Arglist);
			hNextItem = InsertItemA("Thisadjust",hSubItem);
			SetItemNum(hNextItem,1,TypeRecord->u.LF_MFUNCTION.Thisadjust);
			break;
		case LF_VTSHAPE:
			SetItemTextA(hRootItem,1,"LF_VTSHAPE");
			break;
		case LF_MODIFIER:
			SetItemTextA(hRootItem,1,"LF_MODIFIER");
			hNextItem = InsertItemA("Index",hSubItem);
			SetItemNum(hNextItem,1,TypeRecord->u.LF_MODIFIER.TypeIndex);
			hNextItem = InsertItemA("Attribute",hSubItem);
			SetItemNum(hNextItem,1,TypeRecord->u.LF_MODIFIER.Attribute);
			break;
		}
		Counter+=2;
		Counter+=TypeRecord->Length;
		TypeRecord=(TYPERECORD*)&TypeRecord->u1.Start[TypeRecord->Length];
		Index++;
	}
	return true;
}