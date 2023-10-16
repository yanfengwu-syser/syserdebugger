#ifndef _INPUT_DRIVER_H_
#define _INPUT_DRIVER_H_

#define KEYBUFFERMAXLENGTH					0x200
#define FUNCKEYPRESS						1  //功能键被按下时  dwFuncKeyState 变量的值
#define FUNCKEYRELEASE						0 //功能键被释放时  dwFuncKeyState 变量的值
#define MOUSE_DATA_MAX						0x100
#define MOUSE_BEGINDATA_MAX					24
#define MOUSE_INTERRUPT_LEFT_PRESS			0x1
#define MOUSE_INTERRUPT_RIGHT_PRESS			0x2
#define MOUSE_INTERRUPT_MIDDLE_PRESS		0x4
#define MAX_WINDOWSKEYBUFFER_LENGTH			0x10
#define DISABLE_IOAPIC_HARDWARE_INTERRUPT	1
#define DEBUGKEYBORADEXIT					0


#define KEYBOARD_CAPS_LOCK					4
#define KEYBOARD_NUM_LOCK					2
#define KEYBOARD_SCROLL_LOCK				1

DWORD GetHardwareInterruptVectorNum(DWORD dwNum);

#ifdef __cplusplus
extern "C" {
#endif

extern bool gbInterruptInstalled;
extern DWORD UHCI_Number;// UHCI USB HOST CONTROL NUMBER
extern DWORD UHCIFrameBaseRegister[10];
extern bool bWRITE_PORT_UCHAR_PatchOK;
extern bool bREAD_PORT_UCHAR_PatchOK;
extern BYTE byteOrgWRITE_PORT_UCHARInstruction[];
extern BYTE byteOrgREAD_PORT_UCHARInstruction[];
extern DWORD dwKeyLedFlags;
extern DWORD dwWaitMouseCounter;
extern DWORD dwPhysical_0_LinesAddress;
extern DWORD OwnerPageDirItemAddress;
extern DWORD OwnerPageTabItemAddress;
extern bool bEscKeyStat;
extern bool bKeyLedCmd;
extern bool bKeyScrollLockStat;
extern bool bKeyNumLockStat;
extern bool bKeyCapsLockStat;
extern bool bKeyScrollLockStatInitOK;
extern bool bKeyNumLockStatInitOK;
extern bool bKeyCapsLockStatInitOK;
extern bool gbChangeDrmState;
extern bool gbKeyActiveMethod;
extern __int64 TscPerSec;

extern bool gTouchPad;
extern BYTE gTouchPadMode;

extern bool bKeytoSoftice;
extern bool bInt1HereStat;
extern bool bInt3HereStat;

typedef struct stSofticeIdFind
{
	DWORD dwIntNum1;
	DWORD dwIntNum1JmpOffset;					//softice 被加载时用	push OldWindowsHandleAddress
												//						jmp SofticeHandleAddress
												// 例如	jmp 的指令编码是 E98631f7ff 这里的 DWORD 就是 fff73186
	DWORD dwIntNum2;
	DWORD dwIntNum2JmpOffset;					//同上
	DWORD dwIntNum3;
	DWORD dwIntNum3JmpOffset;					//同上	
	DWORD dwIntNum1BaseOffset;					//该 dword 是 softice 的中断 1 的处理函数的地址相对于 softice 基地址的偏移
	DWORD dwActiveFunctionBaseOffset;			//softice 内部的激活函数相对于 softice 基地址的偏移
	DWORD dwActiveFlagsBaseOffset;				//softice 内部的激活的 byte 变量相对于 softice 基地址的偏移
}SOFTICEFINDDATA;


typedef struct _st_desc
{
	WORD wBaseAddrLow;
	WORD wSegmentSec;
	WORD wAttribture;
	WORD wBaseAddrHigh;
}ST_DESC;


//
//	需要跟common-x86.inc中的定义同步
//

typedef struct _KeyInterruptVariable{
	bool IsActive;								//0  代表没有进入操作模式 //1  进入了操作模式
	bool IsInsideActive;						//用来控制键盘中断的死循环结束
	DWORD dwFuncKeyState;						//功能键的状态，0代表功能键没有被按下，1代表功能键被按下
	DWORD dwOldKeyboardInterrupt;				//原始的键盘中断的入口地址
	UINT nCurrentKeyBufferIndex;				//键盘缓冲区的当前索引
	ST_DESC *timer;								//键盘的描述符的指针
	DWORD dwOldTimerInterrupt;
	ST_DESC *keyboard;							//键盘的描述符的指针
	ST_DESC *mouse;								//鼠标的描述符的指针
	WORD wSystemDataSegment;					//Windows 操作系统的 零环的数据段的选择子
	WORD wDSRegister;							// DS 积存器的原始值
	BYTE chFuncKeyScanCode;						//热键的扫描码    Ctrl 键的扫描码
	BYTE chSecondKeyScanCode;					//热键的扫描码    a 键的扫描码								
	BYTE IsSaveInterruptInformation;			//端口 21 和 A1 的值是否保存了，如果保存了则为 1；
	BYTE Interrupt8259Shield_1;					//端口 21 的值
	BYTE Interrupt8259Shield_2;					//端口 A1 的值
	BYTE chAltKeyState;							//ALT 键的状态。
	BYTE chAltKeyScanCode;						// ALT 键的扫描码
	BYTE chCurrentScanCode;						//当前的按键的 扫描码
	DWORD dwIOAPICLineAddress;
	DWORD dwIOAPICPhysAddress;
	DWORD dwLocalAPICPhysAddress;
	DWORD dwLocalAPICLineAddress;
	bool bIsUseAPIC;
	DWORD dwOldMouseInterrupt;	  
	bool bMouseResponseState;
	DWORD dwMouseDataIndex;
	BYTE chCurrentMouseData;
	DWORD dwLocalAPICTaskPriority;
	BYTE chPrveScanCode;
	BYTE chKeyBuffer[KEYBUFFERMAXLENGTH];			//键盘缓冲区

} KeyInterruptVariable;
extern bool gHasPS2Keyboard;
extern bool gHasPS2Mouse;
#ifdef CODE_OS_NT_DRV
extern SYSTEM_QUERY_TIME_ADJUSTMENT SystemTimeAdjustment;
#endif
extern DWORD dwInterruptF8Address;
extern DWORD dwInterruptF9Address;
extern DWORD dwInterruptFaAddress;
extern DWORD dwInterruptFbAddress;
extern DWORD dwInterruptFcAddress;
extern BYTE chWindowsKeyArray[];   //该缓冲区是用来模拟  READ_PORT_UCHAR 函数用的，
								//该缓冲区中的数据要在i8042prt.sys 驱动读端口60时来模拟真的 60端口
extern DWORD dwCurrentReadIndex;
extern DWORD dwCurrentWriteIndex;
extern DWORD dwCurrentWindowsKeyLen;
extern bool bIsMouseData;


extern DWORD dwWaitMouseInterrupt;
extern DWORD dwEflag;
extern KeyInterruptVariable stKeyGlobalVariable;
extern INT nTempVar;
extern BYTE *SoftIceActive;
extern BYTE NormalTable[2][0x80];
extern BYTE ExternTable[];
/*
extern BYTE ShiftKeyTable[];
extern BYTE AltKeyTable[];
extern BYTE CtrlKeyTable[];
extern BYTE CtrlAltKeyTable[];
*/
extern DWORD dwSofticeDriverBase;
extern DWORD dwRPUC;
extern bool bActiveSoftice;
extern DWORD dwRPUCLookup;
extern DWORD dwWPUCLookup;
extern DWORD dwWPUC;
extern DWORD dwTmpVar;
extern ST_DESC *dwTmpIdt;
extern DWORD gHardInt1Vector;
extern DWORD dwOldInterruptFA;
extern DWORD dwOldInterruptF8;
extern DWORD dwOldInterruptF9;
extern void (*pSofticeActivePointer)(void);

//extern stSerialMouse aSerialMouseData[];
UCHAR NEW_READ_PORT_UCHAR(IN DWORD Port);

//VOID SaveDSRegister(VOID);
//VOID StoreDSRegister(VOID);
void KeyboardInterruptService();
VOID SyserWaitKeyboardInputBufferEmpte(VOID);
VOID SyserWaitKeyboardOutPutBufferFull(VOID);
void SyserSimulateKeyboardInput(BYTE scancode,bool isDisableInterrupt = FALSE);
VOID	SyserWaitMouseStatus(VOID);


bool InstallAllInterrupt();
bool UninstallAllInterrupt();

//bool GetIOAPICBase();
void Delay();

//void MouseInterruptService();
VOID SyserWaitMouseInputBufferEmpte(VOID);
VOID SyserWaitMouseOutPutBufferFull(VOID);
bool IsMouseOutPutBufferFull();
void SyserCleanMouseOutPutBuffer();
void WriteMouseCommandPrefix(BYTE chCmd);
void WriteMouseCommandByte(BYTE chCmd);
bool SyserIsMouseOutPutBufferFull();
// void SaveEflag();
// void StoreEflag();
BYTE SyserReadMouseByte(VOID);
DWORD CalcPackageBeginOffset();
void InsertKeyboardBuffer(BYTE chScanCode);




DWORD CheckSofticeExist();

bool SendCommandTo60Port(BYTE byteCmd);//向端口 60 发送命令
void SetKeyboardPortState(bool bState);
bool SendCommandTo64Port(BYTE byteCmd);//向端口 64 发送命令
void SetKeyboardLEDState(DWORD bScrollLock,DWORD bNumLock,DWORD bCapsLock);
VOID SyserGetPortState(VOID);//在给键盘发送了命令以后该函数用来读取键盘的返回值
VOID SyserSimulateWindowsKeyboardInput(BYTE byteScanCode);
bool GetCurrentWindowLEDState(DWORD dwKeyIndex);
void NEW_WRITE_PORT_UCHAR(IN PUCHAR  Port, IN UCHAR  Value);
void PatchSystemWRITE_PORT_UCHAR(bool bIsPatch);
void PatchSystemREAD_PORT_UCHAR(bool bIsPatch);
//void SerialMouseInterruptService();
//bool CheckSerialMouse();
VOID SyserSyncMouseInterrupt(VOID);
extern bool bRightCtrlKey;


//void Interrupt_0xF9_Mouse_Service();
VOID SyserInterrupt_0xF8_Keyboard_Service(VOID);

#ifdef __cplusplus
}; // extern "C"
#endif


typedef struct _IMAGE_DATA_DIRECTORY {
	DWORD   VirtualAddress;
	DWORD   Size;
} IMAGE_DATA_DIRECTORY, *PIMAGE_DATA_DIRECTORY;
#define IMAGE_NUMBEROF_DIRECTORY_ENTRIES    16
typedef struct _IMAGE_DOS_HEADER {      // DOS .EXE header
	WORD   e_magic;                     // Magic number
	WORD   e_cblp;                      // Bytes on last page of file
	WORD   e_cp;                        // Pages in file
	WORD   e_crlc;                      // Relocations
	WORD   e_cparhdr;                   // Size of header in paragraphs
	WORD   e_minalloc;                  // Minimum extra paragraphs needed
	WORD   e_maxalloc;                  // Maximum extra paragraphs needed
	WORD   e_ss;                        // Initial (relative) SS value
	WORD   e_sp;                        // Initial SP value
	WORD   e_csum;                      // Checksum
	WORD   e_ip;                        // Initial IP value
	WORD   e_cs;                        // Initial (relative) CS value
	WORD   e_lfarlc;                    // File address of relocation table
	WORD   e_ovno;                      // Overlay number
	WORD   e_res[4];                    // Reserved words
	WORD   e_oemid;                     // OEM identifier (for e_oeminfo)
	WORD   e_oeminfo;                   // OEM information; e_oemid specific
	WORD   e_res2[10];                  // Reserved words
	LONG   e_lfanew;                    // File address of new exe header
} IMAGE_DOS_HEADER, *PIMAGE_DOS_HEADER;
typedef struct _IMAGE_FILE_HEADER {
	WORD    Machine;
	WORD    NumberOfSections;
	DWORD   TimeDateStamp;
	DWORD   PointerToSymbolTable;
	DWORD   NumberOfSymbols;
	WORD    SizeOfOptionalHeader;
	WORD    Characteristics;
} IMAGE_FILE_HEADER, *PIMAGE_FILE_HEADER;
typedef struct _IMAGE_OPTIONAL_HEADER {
	//
	// Standard fields.
	//

	WORD    Magic;
	BYTE    MajorLinkerVersion;
	BYTE    MinorLinkerVersion;
	DWORD   SizeOfCode;
	DWORD   SizeOfInitializedData;
	DWORD   SizeOfUninitializedData;
	DWORD   AddressOfEntryPoint;
	DWORD   BaseOfCode;
	DWORD   BaseOfData;

	//
	// NT additional fields.
	//

	DWORD   ImageBase;
	DWORD   SectionAlignment;
	DWORD   FileAlignment;
	WORD    MajorOperatingSystemVersion;
	WORD    MinorOperatingSystemVersion;
	WORD    MajorImageVersion;
	WORD    MinorImageVersion;
	WORD    MajorSubsystemVersion;
	WORD    MinorSubsystemVersion;
	DWORD   Win32VersionValue;
	DWORD   SizeOfImage;
	DWORD   SizeOfHeaders;
	DWORD   CheckSum;
	WORD    Subsystem;
	WORD    DllCharacteristics;
	DWORD   SizeOfStackReserve;
	DWORD   SizeOfStackCommit;
	DWORD   SizeOfHeapReserve;
	DWORD   SizeOfHeapCommit;
	DWORD   LoaderFlags;
	DWORD   NumberOfRvaAndSizes;
	IMAGE_DATA_DIRECTORY DataDirectory[IMAGE_NUMBEROF_DIRECTORY_ENTRIES];
} IMAGE_OPTIONAL_HEADER32, *PIMAGE_OPTIONAL_HEADER32;
typedef struct _IMAGE_OPTIONAL_HEADER64 {
	WORD        Magic;
	BYTE        MajorLinkerVersion;
	BYTE        MinorLinkerVersion;
	DWORD       SizeOfCode;
	DWORD       SizeOfInitializedData;
	DWORD       SizeOfUninitializedData;
	DWORD       AddressOfEntryPoint;
	DWORD       BaseOfCode;
	ULONGLONG   ImageBase;
	DWORD       SectionAlignment;
	DWORD       FileAlignment;
	WORD        MajorOperatingSystemVersion;
	WORD        MinorOperatingSystemVersion;
	WORD        MajorImageVersion;
	WORD        MinorImageVersion;
	WORD        MajorSubsystemVersion;
	WORD        MinorSubsystemVersion;
	DWORD       Win32VersionValue;
	DWORD       SizeOfImage;
	DWORD       SizeOfHeaders;
	DWORD       CheckSum;
	WORD        Subsystem;
	WORD        DllCharacteristics;
	ULONGLONG   SizeOfStackReserve;
	ULONGLONG   SizeOfStackCommit;
	ULONGLONG   SizeOfHeapReserve;
	ULONGLONG   SizeOfHeapCommit;
	DWORD       LoaderFlags;
	DWORD       NumberOfRvaAndSizes;
	IMAGE_DATA_DIRECTORY DataDirectory[IMAGE_NUMBEROF_DIRECTORY_ENTRIES];
} IMAGE_OPTIONAL_HEADER64, *PIMAGE_OPTIONAL_HEADER64;

#define IMAGE_DIRECTORY_ENTRY_EXPORT          0   // Export Directory
#define IMAGE_DIRECTORY_ENTRY_IMPORT          1   // Import Directory
#define IMAGE_DIRECTORY_ENTRY_RESOURCE        2   // Resource Directory
#define IMAGE_DIRECTORY_ENTRY_EXCEPTION       3   // Exception Directory
#define IMAGE_DIRECTORY_ENTRY_SECURITY        4   // Security Directory
#define IMAGE_DIRECTORY_ENTRY_BASERELOC       5   // Base Relocation Table
#define IMAGE_DIRECTORY_ENTRY_DEBUG           6   // Debug Directory
//      IMAGE_DIRECTORY_ENTRY_COPYRIGHT       7   // (X86 usage)
#define IMAGE_DIRECTORY_ENTRY_ARCHITECTURE    7   // Architecture Specific Data
#define IMAGE_DIRECTORY_ENTRY_GLOBALPTR       8   // RVA of GP
#define IMAGE_DIRECTORY_ENTRY_TLS             9   // TLS Directory
#define IMAGE_DIRECTORY_ENTRY_LOAD_CONFIG    10   // Load Configuration Directory
#define IMAGE_DIRECTORY_ENTRY_BOUND_IMPORT   11   // Bound Import Directory in headers
#define IMAGE_DIRECTORY_ENTRY_IAT            12   // Import Address Table
#define IMAGE_DIRECTORY_ENTRY_DELAY_IMPORT   13   // Delay Load Import Descriptors
#define IMAGE_DIRECTORY_ENTRY_COM_DESCRIPTOR 14   // COM Runtime descriptor
#define IMAGE_SIZEOF_ROM_OPTIONAL_HEADER      56
#define IMAGE_SIZEOF_STD_OPTIONAL_HEADER      28
#define IMAGE_SIZEOF_NT_OPTIONAL32_HEADER    224
#define IMAGE_SIZEOF_NT_OPTIONAL64_HEADER    240

#define IMAGE_NT_OPTIONAL_HDR32_MAGIC      0x10b
#define IMAGE_NT_OPTIONAL_HDR64_MAGIC      0x20b
#define IMAGE_ROM_OPTIONAL_HDR_MAGIC       0x107

#ifdef _WIN64
typedef IMAGE_OPTIONAL_HEADER64             IMAGE_OPTIONAL_HEADER;
typedef PIMAGE_OPTIONAL_HEADER64            PIMAGE_OPTIONAL_HEADER;
#define IMAGE_SIZEOF_NT_OPTIONAL_HEADER     IMAGE_SIZEOF_NT_OPTIONAL64_HEADER
#define IMAGE_NT_OPTIONAL_HDR_MAGIC         IMAGE_NT_OPTIONAL_HDR64_MAGIC
#else
typedef IMAGE_OPTIONAL_HEADER32             IMAGE_OPTIONAL_HEADER;
typedef PIMAGE_OPTIONAL_HEADER32            PIMAGE_OPTIONAL_HEADER;
#define IMAGE_SIZEOF_NT_OPTIONAL_HEADER     IMAGE_SIZEOF_NT_OPTIONAL32_HEADER
#define IMAGE_NT_OPTIONAL_HDR_MAGIC         IMAGE_NT_OPTIONAL_HDR32_MAGIC
#endif

typedef struct _IMAGE_NT_HEADERS64 {
	DWORD Signature;
	IMAGE_FILE_HEADER FileHeader;
	IMAGE_OPTIONAL_HEADER64 OptionalHeader;
} IMAGE_NT_HEADERS64, *PIMAGE_NT_HEADERS64;

typedef struct _IMAGE_NT_HEADERS {
	DWORD Signature;
	IMAGE_FILE_HEADER FileHeader;
	IMAGE_OPTIONAL_HEADER32 OptionalHeader;
} IMAGE_NT_HEADERS32, *PIMAGE_NT_HEADERS32;



#ifdef _WIN64
typedef IMAGE_NT_HEADERS64                  IMAGE_NT_HEADERS;
typedef PIMAGE_NT_HEADERS64                 PIMAGE_NT_HEADERS;
#else
typedef IMAGE_NT_HEADERS32                  IMAGE_NT_HEADERS;
typedef PIMAGE_NT_HEADERS32                 PIMAGE_NT_HEADERS;
#endif
#define IMAGE_SIZEOF_SHORT_NAME              8

typedef struct _IMAGE_SECTION_HEADER {
	BYTE    Name[IMAGE_SIZEOF_SHORT_NAME];
	union {
		DWORD   PhysicalAddress;
		DWORD   VirtualSize;
	} Misc;
	DWORD   VirtualAddress;
	DWORD   SizeOfRawData;
	DWORD   PointerToRawData;
	DWORD   PointerToRelocations;
	DWORD   PointerToLinenumbers;
	WORD    NumberOfRelocations;
	WORD    NumberOfLinenumbers;
	DWORD   Characteristics;
} IMAGE_SECTION_HEADER, *PIMAGE_SECTION_HEADER;

#define IMAGE_SIZEOF_SECTION_HEADER          40

typedef struct _IMAGE_IMPORT_DESCRIPTOR {
	union {
		DWORD   Characteristics;            // 0 for terminating null import descriptor
		DWORD   OriginalFirstThunk;         // RVA to original unbound IAT (PIMAGE_THUNK_DATA)
	};
	DWORD   TimeDateStamp;                  // 0 if not bound,
	// -1 if bound, and real date\time stamp
	//     in IMAGE_DIRECTORY_ENTRY_BOUND_IMPORT (new BIND)
	// O.W. date/time stamp of DLL bound to (Old BIND)

	DWORD   ForwarderChain;                 // -1 if no forwarders
	DWORD   Name;
	DWORD   FirstThunk;                     // RVA to IAT (if bound this IAT has actual addresses)
} IMAGE_IMPORT_DESCRIPTOR;
typedef IMAGE_IMPORT_DESCRIPTOR UNALIGNED *PIMAGE_IMPORT_DESCRIPTOR;

#ifdef __cplusplus
extern "C" {
#endif

DWORD GetWin32KServiceTable();
//bool MouseCommand(BYTE chCmd);
bool SyserClearI8042OutputBuffer();
bool SyserReadPort60(BYTE* ReturnValue,bool IsMouse);
bool SyserWaitI8042InputBufferEmpty(VOID);
bool SendMouseCommand(BYTE CommandByte);
extern DWORD MouseInterruptCount;

VOID SyserSimulateKeyboardInput(BYTE scancode,bool isInterrupt);
//bool CheckPS2Keyboard();
void InitPS2MouseDevice();
DWORD GetScanCode(DWORD WispVKCode);

#ifdef __cplusplus
}; // extern "C"
#endif

void TestTouchPad();


#endif