#ifndef _OBJFILEVIEW_H_
#define _OBJFILEVIEW_H_
typedef struct _STFLAGSARRAY
{
	char* FlagsName;
	DWORD FlagsValue;
	char* Description;
}STFLAGSARRAY;
enum{
	
	LF_MODIFIER		=0x1001,
	LF_POINTER		=0x1002,
	LF_ARRAY		=0x1003,
	LF_CLASS		=0x1004,
	LF_STRUCTURE	=0x1005,
	LF_UNION		=0x1006,
	LF_ENUM			=0x1007,
	LF_PROCEDURE	=0x1008,
	LF_MFUNCTION	=0x1009,
	LF_VTSHAPE		=0x000a,
	LF_COBOL0		=0x100a,
	LF_COBOL1		=0x000c,
	LF_BARRAY		=0x100b,
	LF_LABEL		=0x000e,
	LF_NULL			=0x000f,
	LF_NOTTRAN		=0x0010,
	LF_DIMARRAY		=0x100c,
	LF_VFTPATH		=0x100d,
	LF_PRECOMP		=0x100e,
	LF_ENDPRECOMP	=0x0014,
	LF_OEM			=0x100f,
	LF_TYPESERVER	=0x0016,
	LF_SKIP			=0x1200,
	LF_ARGLIST		=0x1201,
	LF_DEFARG		=0x1202,
	LF_FIELDLIST	=0x1203,
	LF_DERIVED		=0x1204,
	LF_BITFIELD		=0x1205,
	LF_METHODLIST	=0x1206,
	LF_DIMCONU		=0x1207,
	LF_DIMCONLU		=0x1208,
	LF_DIMVARU		=0x1209,
	LF_DIMVARLU		=0x120a,
	LF_REFSYM		=0x120c,
	LF_BCLASS		=0x1400,
	LF_VBCLASS		=0x1401,
	LF_IVBCLASS		=0x1402,
	LF_ENUMERATE	=0x0403,
	LF_FRIENDFCN	=0x1403,
	LF_INDEX		=0x1404,
	LF_MEMBER		=0x1405,
	LF_STMEMBER		=0x1406,
	LF_METHOD		=0x1407,
	LF_NESTTYPE		=0x1408,
	LF_VFUNCTAB		=0x1409,
	LF_FRIENDCLS	=0x140a,
	LF_ONEMETHOD	=0x140b,
	LF_VFUNCOFF		=0x140c,
	LF_NESTTYPEEX	=0x140d,
	LF_MEMBERMODIFY	=0x140e,
		
	LF_CHAR			=0x8000,
	LF_SHORT		=0x8001,
	LF_USHORT		=0x8002,
	LF_LONG			=0x8003,
	LF_ULONG		=0x8004,
	LF_REAL32		=0x8005,
	LF_REAL64		=0x8006,
	LF_REAL80		=0x8007,
	LF_REAL128		=0x8008,
	LF_QUADWORD		=0x8009,
	LF_UQUADWORD	=0x800a,
	LF_REAL48		=0x800b,
	LF_COMPLEX32	=0x800c,
	LF_COMPLEX64	=0x800d,
	LF_COMPLEX80	=0x800e,
	LF_COMPLEX128	=0x800f,
	LF_VARSTRING	=0x8010,
	LF_PAD0=0xf0,
	LF_PAD1=0xf1,
	LF_PAD2=0xf2,
	LF_PAD3=0xf3,
	LF_PAD4=0xf4,
	LF_PAD5=0xf5,
	LF_PAD6=0xf6,
	LF_PAD7=0xf7,
	LF_PAD8=0xf8,
	LF_PAD9=0xf9,
	LF_PADA=0xfa,
	LF_PADB=0xfb,
	LF_PADC=0xfc,
	LF_PADD=0xfd,
	LF_PADE=0xfe,
	LF_PADF=0xff,
};
enum
{
	SYM_S_COMPILE=0x1,
	SYM_S_REGISTER=0x1001,
	SYM_S_BPREL32=0x1006,
	SYM_S_LPROC32=0x100a,
	SYM_S_GPROC32=0x100b,
	SYM_S_LDATA32=0x1007,
	SYM_S_GDATA32=0x1008,
	SYM_S_LABEL32=0x209,
	SYM_S_UDT=0x1003,
	SYM_S_CONSTANT=0x1002,
};
enum
{
	TYPE_S_COMPILE=0x1,
	TYPE_S_REGISTER=0x1001,
	TYPE_S_BPREL32=0x1006,
	TYPE_S_LPROC32=0x100a,
	TYPE_S_GPROC32=0x100b,
	TYPE_S_LDATA32=0x1007,
	TYPE_S_GDATA32=0x1008,
	TYPE_S_LABEL32=0x209,
	TYPE_S_UDT=0x1003,
	TYPE_S_CONSTANT=0x1002,
};
#include <pshpack1.h>
typedef struct _SymRecord{
	WORD Length;
	union{
		WORD Type;
		BYTE Start[2];
	}u1;
	
	union{
		struct {
			BYTE Machine;
			BYTE flags[3];
			BYTE version[1];
		}S_COMPILE;
		struct {
			DWORD SymOff;
			WORD Segment;
		}S_SSEARCH ;
		struct {
			
		}S_END ;
		struct {
			BYTE SkipData[1];
		}S_SKIP ;
		struct {

		}S_CVRESERVE;
		struct {
			DWORD Signature;
			BYTE Name[1];
		}S_OBJNAME;
		struct {

		}S_ENDARG;
		struct {

		}S_COBOLUDT;
		struct {

		}S_MANYREG;
		struct {

		}S_RETURN ;
		struct {

		}S_ENTRYTHIS ;
		struct {
			DWORD TypeIndex;
			WORD Register;
			BYTE Name[1];
		}S_REGISTER ;
		struct {
			DWORD TypeIndex;
			WORD Value;
			BYTE Name[1];
		}S_CONSTANT ;
		struct {
			DWORD TypeIndex;
			BYTE Name[1];
		}S_UDT;
		struct {

		}S_COBOLUDT1 ;
		struct {

		}S_MANYREG1 ;
		struct {
			int Offset;
			DWORD TypeIndex;
			BYTE Name[1];
		}S_BPREL32 ;
		struct {
			DWORD TypeIndex;
			DWORD Offset;
			WORD Segment;
			BYTE Name[1];
		}S_LDATA32 ;
		struct {
			DWORD TypeIndex;
			DWORD Offset;
			WORD Segment;
			BYTE Name[1];
		}S_GDATA32 ;
		struct {

		}S_PUB32 ;
		struct {
			DWORD pParent;
			DWORD pEnd;
			DWORD pNext;
			DWORD ProcLength;
			DWORD DebugStart;
			DWORD DebugEnd;
			DWORD ProcType;
			DWORD Offset;
			WORD Segment;
			BYTE Flags;
			BYTE Name[1];
		}S_LPROC32 ;
		struct {
			DWORD pParent;
			DWORD pEnd;
			DWORD pNext;
			DWORD ProcLength;
			DWORD DebugStart;
			DWORD DebugEnd;
			DWORD ProcType;
			DWORD Offset;
			WORD Segment;
			BYTE Flags;
			BYTE Name[1];
		}S_GPROC32 ;
		struct {

		}S_THUNK32 ;
		struct {

		}S_BLOCK32 ;
		struct {

		}S_WITH32 ;
		struct {
			DWORD Offset;
			WORD Segment;
			BYTE Flags;
			BYTE Name[1];
		}S_LABEL32 ;
		struct {

		}S_CEXMODEL32 ;
		struct {

		}S_VFTTABLE32 ;
		struct {

		}S_REGREL32 ;
		struct {

		}S_LTHREAD32 ;
		struct {

		}S_GTHREAD32 ;
		struct {

		}S_LPROCMIPS ;
		struct {

		}S_GPROCMIPS ;
		struct {

		}S_PROCREF ;
		struct {

		}S_DATAREF ;
		struct {

		}S_ALIGN ;
	}u;
}SYMRECORD;
typedef union _LeafNumbers
{
	WORD NumbersType;
	WORD Number;
	BYTE Value[1];
}LeafNumbers;

typedef struct _TypeRecord{
	WORD Length;
	union{
		WORD Type;
		BYTE Start[2];
	}u1;

	union{
		struct {
			WORD Count;
			WORD property;
			DWORD field;
			DWORD dList;
			DWORD vshape;
			union{
				LeafNumbers Length;
				BYTE Name[1];
			}u;
		}LF_CLASS;
		struct {
			DWORD TypeIndex;
			WORD Attribute;
		}LF_MODIFIER ;
		struct {
		DWORD	Rvtype;
		DWORD	Class;
		DWORD	This;
		BYTE	Call;
		BYTE	Res;
		WORD Parms;
		DWORD Arglist;
		DWORD Thisadjust;
		}LF_MFUNCTION ;
		struct {
			DWORD TypeIndex;
			union{
			DWORD Attribute;
			DWORD ptrtype:5;
			DWORD ptrmode:3;
			DWORD isflat32:1;
			DWORD volatileType:1;
			DWORD constType:1;
			DWORD unaligned:1;
			DWORD restrict:1;
			DWORD unused:19;
			};
			BYTE variant[1];
		}LF_POINTER ;
		struct {

		}S_CVRESERVE;
		struct {
			DWORD Signature;
			BYTE Name[1];
		}S_OBJNAME;
		struct {

		}S_ENDARG;
		struct {

		}S_COBOLUDT;
		struct {

		}S_MANYREG;
		struct {

		}S_RETURN ;
		struct {

		}S_ENTRYTHIS ;
		struct {
			DWORD TypeIndex;
			WORD Register;
			BYTE Name[1];
		}S_REGISTER ;
		struct {
			DWORD TypeIndex;
			WORD Value;
			BYTE Name[1];
		}S_CONSTANT ;
		struct {
			DWORD TypeIndex;
			BYTE Name[1];
		}S_UDT;
		struct {

		}S_COBOLUDT1 ;
		struct {

		}S_MANYREG1 ;
		struct {
			int Offset;
			DWORD TypeIndex;
			BYTE Name[1];
		}S_BPREL32 ;
		struct {
			DWORD TypeIndex;
			DWORD Offset;
			WORD Segment;
			BYTE Name[1];
		}S_LDATA32 ;
		struct {
			DWORD TypeIndex;
			DWORD Offset;
			WORD Segment;
			BYTE Name[1];
		}S_GDATA32 ;
		struct {

		}S_PUB32 ;
		struct {
			DWORD pParent;
			DWORD pEnd;
			DWORD pNext;
			DWORD ProcLength;
			DWORD DebugStart;
			DWORD DebugEnd;
			DWORD ProcType;
			DWORD Offset;
			WORD Segment;
			BYTE Flags;
			BYTE Name[1];
		}S_LPROC32 ;
		struct {
			DWORD pParent;
			DWORD pEnd;
			DWORD pNext;
			DWORD ProcLength;
			DWORD DebugStart;
			DWORD DebugEnd;
			DWORD ProcType;
			DWORD Offset;
			WORD Segment;
			BYTE Flags;
			BYTE Name[1];
		}S_GPROC32 ;
		struct {

		}S_THUNK32 ;
		struct {

		}S_BLOCK32 ;
		struct {

		}S_WITH32 ;
		struct {
			DWORD Offset;
			WORD Segment;
			BYTE Flags;
			BYTE Name[1];
		}S_LABEL32 ;
		struct {

		}S_CEXMODEL32 ;
		struct {

		}S_VFTTABLE32 ;
		struct {

		}S_REGREL32 ;
		struct {

		}S_LTHREAD32 ;
		struct {

		}S_GTHREAD32 ;
		struct {

		}S_LPROCMIPS ;
		struct {

		}S_GPROCMIPS ;
		struct {

		}S_PROCREF ;
		struct {

		}S_DATAREF ;
		struct {

		}S_ALIGN ;
	}u;
}TYPERECORD;
#include <poppack.h>
class CObjFileView:public CWispList
{
public:
	CObjFileView();
	~CObjFileView();
	DECLARE_WISP_MSG_MAP
	DECLARE_WISP_MSG(OnCreate);
	DECLARE_WISP_MSG(OnDestroy);
	DECLARE_WISP_MSG_EVENT_MAP
	DECLARE_WISP_MSG_EVENT(OnHexDisplayEvent)
	DECLARE_WISP_MSG_EVENT(OnDeleteWatchEvent)
	DECLARE_WISP_MSG_EVENT(OnEventShowData)
	DECLARE_WISP_MSG_CMD_MAP
	DECLARE_WISP_MSG_CMD(OnViewerCmd)
	CObjFile m_ObjFile;
	static STFLAGSARRAY FlagsArray[];
	static STFLAGSARRAY RleFlagsArray[];	
	static STFLAGSARRAY MachineTypeArray[];
	static STFLAGSARRAY SymBaseTypeArray[];
	static STFLAGSARRAY SymComplexTypeArray[];
	static STFLAGSARRAY SymStorageClassArray[];
	static STFLAGSARRAY COMPILE_machineArray[];
	static STFLAGSARRAY COMPILE_LanguageArray[];
	static STFLAGSARRAY X86X87RegisterArray[];
	static STFLAGSARRAY FileHeaderCharacteristicsArray[];
	bool AnalyserSymbolSection(HANDLE hItem,OBJ_SECTION* ObjSection,bool FirstSymbolSection);
	bool AnalyserTypeSection(HANDLE hItem,OBJ_SECTION* ObjSection,bool FirstTypeSection);
};
#endif