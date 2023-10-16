struct LIST_ENTRY64 /* sizeof 00000010 16 */
{
/* off 0x0000 */	unsigned __int64	Flink;
/* off 0x0008 */	unsigned __int64	Blink;
};
struct LIST_ENTRY32 /* sizeof 00000008 8 */
{
/* off 0x0000 */	unsigned long	Flink;
/* off 0x0004 */	unsigned long	Blink;
};
struct _LIST_ENTRY /* sizeof 00000008 8 */
{
/* off 0x0000 */	struct _LIST_ENTRY*	Flink;
/* off 0x0004 */	struct _LIST_ENTRY*	Blink;
};
struct _IMAGE_FILE_HEADER /* sizeof 00000014 20 */
{
/* off 0x0000 */	unsigned short	Machine;
/* off 0x0002 */	unsigned short	NumberOfSections;
/* off 0x0004 */	unsigned long	TimeDateStamp;
/* off 0x0008 */	unsigned long	PointerToSymbolTable;
/* off 0x000c */	unsigned long	NumberOfSymbols;
/* off 0x0010 */	unsigned short	SizeOfOptionalHeader;
/* off 0x0012 */	unsigned short	Characteristics;
};
struct _IMAGE_DATA_DIRECTORY /* sizeof 00000008 8 */
{
/* off 0x0000 */	unsigned long	VirtualAddress;
/* off 0x0004 */	unsigned long	Size;
};
struct _IMAGE_OPTIONAL_HEADER /* sizeof 000000e0 224 */
{
/* off 0x0000 */	unsigned short	Magic;
/* off 0x0002 */	unsigned char	MajorLinkerVersion;
/* off 0x0003 */	unsigned char	MinorLinkerVersion;
/* off 0x0004 */	unsigned long	SizeOfCode;
/* off 0x0008 */	unsigned long	SizeOfInitializedData;
/* off 0x000c */	unsigned long	SizeOfUninitializedData;
/* off 0x0010 */	unsigned long	AddressOfEntryPoint;
/* off 0x0014 */	unsigned long	BaseOfCode;
/* off 0x0018 */	unsigned long	BaseOfData;
/* off 0x001c */	unsigned long	ImageBase;
/* off 0x0020 */	unsigned long	SectionAlignment;
/* off 0x0024 */	unsigned long	FileAlignment;
/* off 0x0028 */	unsigned short	MajorOperatingSystemVersion;
/* off 0x002a */	unsigned short	MinorOperatingSystemVersion;
/* off 0x002c */	unsigned short	MajorImageVersion;
/* off 0x002e */	unsigned short	MinorImageVersion;
/* off 0x0030 */	unsigned short	MajorSubsystemVersion;
/* off 0x0032 */	unsigned short	MinorSubsystemVersion;
/* off 0x0034 */	unsigned long	Win32VersionValue;
/* off 0x0038 */	unsigned long	SizeOfImage;
/* off 0x003c */	unsigned long	SizeOfHeaders;
/* off 0x0040 */	unsigned long	CheckSum;
/* off 0x0044 */	unsigned short	Subsystem;
/* off 0x0046 */	unsigned short	DllCharacteristics;
/* off 0x0048 */	unsigned long	SizeOfStackReserve;
/* off 0x004c */	unsigned long	SizeOfStackCommit;
/* off 0x0050 */	unsigned long	SizeOfHeapReserve;
/* off 0x0054 */	unsigned long	SizeOfHeapCommit;
/* off 0x0058 */	unsigned long	LoaderFlags;
/* off 0x005c */	unsigned long	NumberOfRvaAndSizes;
/* off 0x0060 */	struct _IMAGE_DATA_DIRECTORY DataDirectory[16];
};
struct _IMAGE_NT_HEADERS /* sizeof 000000f8 248 */
{
/* off 0x0000 */	unsigned long	Signature;
/* off 0x0004 */	struct _IMAGE_FILE_HEADER	FileHeader;
/* off 0x0018 */	struct _IMAGE_OPTIONAL_HEADER	OptionalHeader;
};
struct __unnamed /* sizeof 00000008 8 */
{
/* off 0x0000 */	unsigned long	LowPart;
/* off 0x0004 */	long	HighPart;
};
union _LARGE_INTEGER /* sizeof 00000008 8 */
{
struct
{
/* off 0x0000 */	unsigned long	LowPart;
/* off 0x0004 */	long	HighPart;
};
/* off 0x0000 */	struct __unnamed	u;
/* off 0x0000 */	__int64	QuadPart;
};
union _ULARGE_INTEGER /* sizeof 00000008 8 */
{
struct
{
/* off 0x0000 */	unsigned long	LowPart;
/* off 0x0004 */	unsigned long	HighPart;
};
/* off 0x0000 */	struct __unnamed	u;
/* off 0x0000 */	unsigned __int64	QuadPart;
};
struct _LUID /* sizeof 00000008 8 */
{
/* off 0x0000 */	unsigned long	LowPart;
/* off 0x0004 */	long	HighPart;
};
struct _KAPC /* sizeof 00000030 48 */
{
/* off 0x0000 */	short	Type;
/* off 0x0002 */	short	Size;
/* off 0x0004 */	unsigned long	Spare0;
/* off 0x0008 */	struct _KTHREAD*	Thread;
/* off 0x000c */	struct _LIST_ENTRY	ApcListEntry;
/* off 0x0014 */	void( __cdecl *KernelRoutine)(struct _KAPC*,void( __cdecl **)(void*,void*,void*),void**,void**,void**);
/* off 0x0018 */	void( __cdecl *RundownRoutine)(struct _KAPC*);
/* off 0x001c */	void( __cdecl *NormalRoutine)(void*,void*,void*);
/* off 0x0020 */	void*	NormalContext;
/* off 0x0024 */	void*	SystemArgument1;
/* off 0x0028 */	void*	SystemArgument2;
/* off 0x002c */	char	ApcStateIndex;
/* off 0x002d */	char	ApcMode;
/* off 0x002e */	unsigned char	Inserted;
};
struct _DISPATCHER_HEADER /* sizeof 00000010 16 */
{
/* off 0x0000 */	unsigned char	Type;
/* off 0x0001 */	unsigned char	Absolute;
/* off 0x0002 */	unsigned char	Size;
/* off 0x0003 */	unsigned char	Inserted;
/* off 0x0004 */	long	SignalState;
/* off 0x0008 */	struct _LIST_ENTRY	WaitListHead;
};
struct _KAPC_STATE /* sizeof 00000018 24 */
{
/* off 0x0000 */	struct _LIST_ENTRY ApcListHead[2];
/* off 0x0010 */	struct _KPROCESS*	Process;
/* off 0x0014 */	unsigned char	KernelApcInProgress;
/* off 0x0015 */	unsigned char	KernelApcPending;
/* off 0x0016 */	unsigned char	UserApcPending;
};
struct _SINGLE_LIST_ENTRY /* sizeof 00000004 4 */
{
/* off 0x0000 */	struct _SINGLE_LIST_ENTRY*	Next;
};
struct _KWAIT_BLOCK /* sizeof 00000018 24 */
{
/* off 0x0000 */	struct _LIST_ENTRY	WaitListEntry;
/* off 0x0008 */	struct _KTHREAD*	Thread;
/* off 0x000c */	void*	Object;
/* off 0x0010 */	struct _KWAIT_BLOCK*	NextWaitBlock;
/* off 0x0014 */	unsigned short	WaitKey;
/* off 0x0016 */	unsigned short	WaitType;
};
struct _KTIMER /* sizeof 00000028 40 */
{
/* off 0x0000 */	struct _DISPATCHER_HEADER	Header;
/* off 0x0010 */	union _ULARGE_INTEGER	DueTime;
/* off 0x0018 */	struct _LIST_ENTRY	TimerListEntry;
/* off 0x0020 */	struct _KDPC*	Dpc;
/* off 0x0024 */	long	Period;
};
struct _KSEMAPHORE /* sizeof 00000014 20 */
{
/* off 0x0000 */	struct _DISPATCHER_HEADER	Header;
/* off 0x0010 */	long	Limit;
};
struct _KTHREAD /* sizeof 000001c0 448 */
{
/* off 0x0000 */	struct _DISPATCHER_HEADER	Header;
/* off 0x0010 */	struct _LIST_ENTRY	MutantListHead;
/* off 0x0018 */	void*	InitialStack;
/* off 0x001c */	void*	StackLimit;
/* off 0x0020 */	void*	Teb;
/* off 0x0024 */	void*	TlsArray;
/* off 0x0028 */	void*	KernelStack;
/* off 0x002c */	unsigned char	DebugActive;
/* off 0x002d */	unsigned char	State;
/* off 0x002e */	unsigned char Alerted[2];
/* off 0x0030 */	unsigned char	Iopl;
/* off 0x0031 */	unsigned char	NpxState;
/* off 0x0032 */	char	Saturation;
/* off 0x0033 */	char	Priority;
/* off 0x0034 */	struct _KAPC_STATE	ApcState;
/* off 0x004c */	unsigned long	ContextSwitches;
/* off 0x0050 */	unsigned char	IdleSwapBlock;
/* off 0x0051 */	unsigned char Spare0[3];
/* off 0x0054 */	long	WaitStatus;
/* off 0x0058 */	unsigned char	WaitIrql;
/* off 0x0059 */	char	WaitMode;
/* off 0x005a */	unsigned char	WaitNext;
/* off 0x005b */	unsigned char	WaitReason;
/* off 0x005c */	struct _KWAIT_BLOCK*	WaitBlockList;
union
{
/* off 0x0060 */	struct _LIST_ENTRY	WaitListEntry;
/* off 0x0060 */	struct _SINGLE_LIST_ENTRY	SwapListEntry;
};
/* off 0x0068 */	unsigned long	WaitTime;
/* off 0x006c */	char	BasePriority;
/* off 0x006d */	unsigned char	DecrementCount;
/* off 0x006e */	char	PriorityDecrement;
/* off 0x006f */	char	Quantum;
/* off 0x0070 */	struct _KWAIT_BLOCK WaitBlock[4];
/* off 0x00d0 */	void*	LegoData;
/* off 0x00d4 */	unsigned long	KernelApcDisable;
/* off 0x00d8 */	unsigned long	UserAffinity;
/* off 0x00dc */	unsigned char	SystemAffinityActive;
/* off 0x00dd */	unsigned char	PowerState;
/* off 0x00de */	unsigned char	NpxIrql;
/* off 0x00df */	unsigned char	InitialNode;
/* off 0x00e0 */	void*	ServiceTable;
/* off 0x00e4 */	struct _KQUEUE*	Queue;
/* off 0x00e8 */	unsigned long	ApcQueueLock;
/* off 0x00f0 */	struct _KTIMER	Timer;
/* off 0x0118 */	struct _LIST_ENTRY	QueueListEntry;
/* off 0x0120 */	unsigned long	SoftAffinity;
/* off 0x0124 */	unsigned long	Affinity;
/* off 0x0128 */	unsigned char	Preempted;
/* off 0x0129 */	unsigned char	ProcessReadyQueue;
/* off 0x012a */	unsigned char	KernelStackResident;
/* off 0x012b */	unsigned char	NextProcessor;
/* off 0x012c */	void*	CallbackStack;
/* off 0x0130 */	void*	Win32Thread;
/* off 0x0134 */	struct _KTRAP_FRAME*	TrapFrame;
/* off 0x0138 */	struct _KAPC_STATE* ApcStatePointer[2];
/* off 0x0140 */	char	PreviousMode;
/* off 0x0141 */	unsigned char	EnableStackSwap;
/* off 0x0142 */	unsigned char	LargeStack;
/* off 0x0143 */	unsigned char	ResourceIndex;
/* off 0x0144 */	unsigned long	KernelTime;
/* off 0x0148 */	unsigned long	UserTime;
/* off 0x014c */	struct _KAPC_STATE	SavedApcState;
/* off 0x0164 */	unsigned char	Alertable;
/* off 0x0165 */	unsigned char	ApcStateIndex;
/* off 0x0166 */	unsigned char	ApcQueueable;
/* off 0x0167 */	unsigned char	AutoAlignment;
/* off 0x0168 */	void*	StackBase;
/* off 0x016c */	struct _KAPC	SuspendApc;
/* off 0x019c */	struct _KSEMAPHORE	SuspendSemaphore;
/* off 0x01b0 */	struct _LIST_ENTRY	ThreadListEntry;
/* off 0x01b8 */	char	FreezeCount;
/* off 0x01b9 */	char	SuspendCount;
/* off 0x01ba */	unsigned char	IdealProcessor;
/* off 0x01bb */	unsigned char	DisableBoost;
};
struct _KGDTENTRY /* sizeof 00000008 8 */
{
/* off 0x0000 */	unsigned short	LimitLow;
/* off 0x0002 */	unsigned short	BaseLow;
/* off 0x0004 */	struct __unnamed	HighWord;
};
struct _KIDTENTRY /* sizeof 00000008 8 */
{
/* off 0x0000 */	unsigned short	Offset;
/* off 0x0002 */	unsigned short	Selector;
/* off 0x0004 */	unsigned short	Access;
/* off 0x0006 */	unsigned short	ExtendedOffset;
};
struct _KEXECUTE_OPTIONS /* sizeof 00000001 1 */
{
/* off 0x0000 */	unsigned char	ExecuteDisable:1	 /* start bit 0 */;
/* off 0x0000 */	unsigned char	ExecuteEnable:1	 /* start bit 1 */;
/* off 0x0000 */	unsigned char	DisableThunkEmulation:1	 /* start bit 2 */;
/* off 0x0000 */	unsigned char	Permanent:1	 /* start bit 3 */;
/* off 0x0000 */	unsigned char	ExecuteDispatchEnable:1	 /* start bit 4 */;
/* off 0x0000 */	unsigned char	ImageDispatchEnable:1	 /* start bit 5 */;
/* off 0x0000 */	unsigned char	Spare:2	 /* start bit 6 */;
};
struct _KPROCESS /* sizeof 0000006c 108 */
{
/* off 0x0000 */	struct _DISPATCHER_HEADER	Header;
/* off 0x0010 */	struct _LIST_ENTRY	ProfileListHead;
/* off 0x0018 */	unsigned long DirectoryTableBase[2];
/* off 0x0020 */	struct _KGDTENTRY	LdtDescriptor;
/* off 0x0028 */	struct _KIDTENTRY	Int21Descriptor;
/* off 0x0030 */	unsigned short	IopmOffset;
/* off 0x0032 */	unsigned char	Iopl;
/* off 0x0033 */	unsigned char	Unused;
/* off 0x0034 */	unsigned long	ActiveProcessors;
/* off 0x0038 */	unsigned long	KernelTime;
/* off 0x003c */	unsigned long	UserTime;
/* off 0x0040 */	struct _LIST_ENTRY	ReadyListHead;
/* off 0x0048 */	struct _SINGLE_LIST_ENTRY	SwapListEntry;
/* off 0x004c */	void*	VdmTrapcHandler;
/* off 0x0050 */	struct _LIST_ENTRY	ThreadListHead;
/* off 0x0058 */	unsigned long	ProcessLock;
/* off 0x005c */	unsigned long	Affinity;
/* off 0x0060 */	unsigned short	StackCount;
/* off 0x0062 */	char	BasePriority;
/* off 0x0063 */	char	ThreadQuantum;
/* off 0x0064 */	unsigned char	AutoAlignment;
/* off 0x0065 */	unsigned char	State;
/* off 0x0066 */	unsigned char	ThreadSeed;
/* off 0x0067 */	unsigned char	DisableBoost;
/* off 0x0068 */	unsigned char	PowerState;
/* off 0x0069 */	unsigned char	DisableQuantum;
/* off 0x006a */	unsigned char	IdealNode;
union
{
/* off 0x006b */	struct _KEXECUTE_OPTIONS	Flags;
/* off 0x006b */	unsigned char	ExecuteOptions;
};
};
struct _KQUEUE /* sizeof 00000028 40 */
{
/* off 0x0000 */	struct _DISPATCHER_HEADER	Header;
/* off 0x0010 */	struct _LIST_ENTRY	EntryListHead;
/* off 0x0018 */	unsigned long	CurrentCount;
/* off 0x001c */	unsigned long	MaximumCount;
/* off 0x0020 */	struct _LIST_ENTRY	ThreadListHead;
};
struct _KDPC /* sizeof 00000020 32 */
{
/* off 0x0000 */	short	Type;
/* off 0x0002 */	unsigned char	Number;
/* off 0x0003 */	unsigned char	Importance;
/* off 0x0004 */	struct _LIST_ENTRY	DpcListEntry;
/* off 0x000c */	void( __cdecl *DeferredRoutine)(struct _KDPC*,void*,void*,void*);
/* off 0x0010 */	void*	DeferredContext;
/* off 0x0014 */	void*	SystemArgument1;
/* off 0x0018 */	void*	SystemArgument2;
/* off 0x001c */	unsigned long*	Lock;
};
struct _KTRAP_FRAME /* sizeof 0000008c 140 */
{
/* off 0x0000 */	unsigned long	DbgEbp;
/* off 0x0004 */	unsigned long	DbgEip;
/* off 0x0008 */	unsigned long	DbgArgMark;
/* off 0x000c */	unsigned long	DbgArgPointer;
/* off 0x0010 */	unsigned long	TempSegCs;
/* off 0x0014 */	unsigned long	TempEsp;
/* off 0x0018 */	unsigned long	Dr0;
/* off 0x001c */	unsigned long	Dr1;
/* off 0x0020 */	unsigned long	Dr2;
/* off 0x0024 */	unsigned long	Dr3;
/* off 0x0028 */	unsigned long	Dr6;
/* off 0x002c */	unsigned long	Dr7;
/* off 0x0030 */	unsigned long	SegGs;
/* off 0x0034 */	unsigned long	SegEs;
/* off 0x0038 */	unsigned long	SegDs;
/* off 0x003c */	unsigned long	Edx;
/* off 0x0040 */	unsigned long	Ecx;
/* off 0x0044 */	unsigned long	Eax;
/* off 0x0048 */	unsigned long	PreviousPreviousMode;
/* off 0x004c */	struct _EXCEPTION_REGISTRATION_RECORD*	ExceptionList;
/* off 0x0050 */	unsigned long	SegFs;
/* off 0x0054 */	unsigned long	Edi;
/* off 0x0058 */	unsigned long	Esi;
/* off 0x005c */	unsigned long	Ebx;
/* off 0x0060 */	unsigned long	Ebp;
/* off 0x0064 */	unsigned long	ErrCode;
/* off 0x0068 */	unsigned long	Eip;
/* off 0x006c */	unsigned long	SegCs;
/* off 0x0070 */	unsigned long	EFlags;
/* off 0x0074 */	unsigned long	HardwareEsp;
/* off 0x0078 */	unsigned long	HardwareSegSs;
/* off 0x007c */	unsigned long	V86Es;
/* off 0x0080 */	unsigned long	V86Ds;
/* off 0x0084 */	unsigned long	V86Fs;
/* off 0x0088 */	unsigned long	V86Gs;
};
struct _EXCEPTION_REGISTRATION_RECORD /* sizeof 00000008 8 */
{
/* off 0x0000 */	struct _EXCEPTION_REGISTRATION_RECORD*	Next;
/* off 0x0004 */	enum _EXCEPTION_DISPOSITION( __cdecl *Handler)(struct _EXCEPTION_RECORD*,void*,struct _CONTEXT*,void*);
};
enum _EXCEPTION_DISPOSITION
{
	ExceptionContinueExecution	=0x00000000	,//0
	ExceptionContinueSearch	=0x00000001	,//0
	ExceptionNestedException	=0x00000002	,//0
	ExceptionCollidedUnwind	=0x00000003	,//0
};
struct _EXCEPTION_RECORD /* sizeof 00000050 80 */
{
/* off 0x0000 */	long	ExceptionCode;
/* off 0x0004 */	unsigned long	ExceptionFlags;
/* off 0x0008 */	struct _EXCEPTION_RECORD*	ExceptionRecord;
/* off 0x000c */	void*	ExceptionAddress;
/* off 0x0010 */	unsigned long	NumberParameters;
/* off 0x0014 */	unsigned long ExceptionInformation[15];
};
struct _FLOATING_SAVE_AREA /* sizeof 00000070 112 */
{
/* off 0x0000 */	unsigned long	ControlWord;
/* off 0x0004 */	unsigned long	StatusWord;
/* off 0x0008 */	unsigned long	TagWord;
/* off 0x000c */	unsigned long	ErrorOffset;
/* off 0x0010 */	unsigned long	ErrorSelector;
/* off 0x0014 */	unsigned long	DataOffset;
/* off 0x0018 */	unsigned long	DataSelector;
/* off 0x001c */	unsigned char RegisterArea[80];
/* off 0x006c */	unsigned long	Cr0NpxState;
};
struct _CONTEXT /* sizeof 000002cc 716 */
{
/* off 0x0000 */	unsigned long	ContextFlags;
/* off 0x0004 */	unsigned long	Dr0;
/* off 0x0008 */	unsigned long	Dr1;
/* off 0x000c */	unsigned long	Dr2;
/* off 0x0010 */	unsigned long	Dr3;
/* off 0x0014 */	unsigned long	Dr6;
/* off 0x0018 */	unsigned long	Dr7;
/* off 0x001c */	struct _FLOATING_SAVE_AREA	FloatSave;
/* off 0x008c */	unsigned long	SegGs;
/* off 0x0090 */	unsigned long	SegFs;
/* off 0x0094 */	unsigned long	SegEs;
/* off 0x0098 */	unsigned long	SegDs;
/* off 0x009c */	unsigned long	Edi;
/* off 0x00a0 */	unsigned long	Esi;
/* off 0x00a4 */	unsigned long	Ebx;
/* off 0x00a8 */	unsigned long	Edx;
/* off 0x00ac */	unsigned long	Ecx;
/* off 0x00b0 */	unsigned long	Eax;
/* off 0x00b4 */	unsigned long	Ebp;
/* off 0x00b8 */	unsigned long	Eip;
/* off 0x00bc */	unsigned long	SegCs;
/* off 0x00c0 */	unsigned long	EFlags;
/* off 0x00c4 */	unsigned long	Esp;
/* off 0x00c8 */	unsigned long	SegSs;
/* off 0x00cc */	unsigned char ExtendedRegisters[512];
};
enum _KSPIN_LOCK_QUEUE_NUMBER
{
	LockQueueDispatcherLock	=0x00000000	,//0
	LockQueueContextSwapLock	=0x00000001	,//0
	LockQueuePfnLock	=0x00000002	,//0
	LockQueueSystemSpaceLock	=0x00000003	,//0
	LockQueueVacbLock	=0x00000004	,//0
	LockQueueMasterLock	=0x00000005	,//0
	LockQueueNonPagedPoolLock	=0x00000006	,//0
	LockQueueIoCancelLock	=0x00000007	,//0
	LockQueueWorkQueueLock	=0x00000008	,//0
	LockQueueIoVpbLock	=0x00000009	,//0
	LockQueueIoDatabaseLock	=0x0000000a	,//0
	LockQueueIoCompletionLock	=0x0000000b	,//0
	LockQueueNtfsStructLock	=0x0000000c	,//0
	LockQueueAfdWorkQueueLock	=0x0000000d	,//0
	LockQueueBcbLock	=0x0000000e	,//0
	LockQueueMaximumLock	=0x0000000f	,//0
};
struct _DESCRIPTOR /* sizeof 00000008 8 */
{
/* off 0x0000 */	unsigned short	Pad;
/* off 0x0002 */	unsigned short	Limit;
/* off 0x0004 */	unsigned long	Base;
};
struct _KSPECIAL_REGISTERS /* sizeof 00000054 84 */
{
/* off 0x0000 */	unsigned long	Cr0;
/* off 0x0004 */	unsigned long	Cr2;
/* off 0x0008 */	unsigned long	Cr3;
/* off 0x000c */	unsigned long	Cr4;
/* off 0x0010 */	unsigned long	KernelDr0;
/* off 0x0014 */	unsigned long	KernelDr1;
/* off 0x0018 */	unsigned long	KernelDr2;
/* off 0x001c */	unsigned long	KernelDr3;
/* off 0x0020 */	unsigned long	KernelDr6;
/* off 0x0024 */	unsigned long	KernelDr7;
/* off 0x0028 */	struct _DESCRIPTOR	Gdtr;
/* off 0x0030 */	struct _DESCRIPTOR	Idtr;
/* off 0x0038 */	unsigned short	Tr;
/* off 0x003a */	unsigned short	Ldtr;
/* off 0x003c */	unsigned long Reserved[6];
};
struct _KPROCESSOR_STATE /* sizeof 00000320 800 */
{
/* off 0x0000 */	struct _CONTEXT	ContextFrame;
/* off 0x02cc */	struct _KSPECIAL_REGISTERS	SpecialRegisters;
};
struct _KSPIN_LOCK_QUEUE /* sizeof 00000008 8 */
{
/* off 0x0000 */	struct _KSPIN_LOCK_QUEUE*	Next;
/* off 0x0004 */	unsigned long*	Lock;
};
struct _PP_LOOKASIDE_LIST /* sizeof 00000008 8 */
{
/* off 0x0000 */	struct _GENERAL_LOOKASIDE*	P;
/* off 0x0004 */	struct _GENERAL_LOOKASIDE*	L;
};
struct _FX_SAVE_AREA /* sizeof 00000210 528 */
{
/* off 0x0000 */	struct __unnamed	U;
/* off 0x0208 */	unsigned long	NpxSavedCpu;
/* off 0x020c */	unsigned long	Cr0NpxState;
};
struct PROCESSOR_IDLE_TIMES /* sizeof 00000020 32 */
{
/* off 0x0000 */	unsigned __int64	StartTime;
/* off 0x0008 */	unsigned __int64	EndTime;
/* off 0x0010 */	unsigned long IdleHandlerReserved[4];
};
struct _PROCESSOR_POWER_STATE /* sizeof 00000120 288 */
{
/* off 0x0000 */	void( __fastcall *IdleFunction)(struct _PROCESSOR_POWER_STATE*);
/* off 0x0004 */	unsigned long	Idle0KernelTimeLimit;
/* off 0x0008 */	unsigned long	Idle0LastTime;
/* off 0x000c */	void*	IdleHandlers;
/* off 0x0010 */	void*	IdleState;
/* off 0x0014 */	unsigned long	IdleHandlersCount;
/* off 0x0018 */	unsigned __int64	LastCheck;
/* off 0x0020 */	struct PROCESSOR_IDLE_TIMES	IdleTimes;
/* off 0x0040 */	unsigned long	IdleTime1;
/* off 0x0044 */	unsigned long	PromotionCheck;
/* off 0x0048 */	unsigned long	IdleTime2;
/* off 0x004c */	unsigned char	CurrentThrottle;
/* off 0x004d */	unsigned char	ThermalThrottleLimit;
/* off 0x004e */	unsigned char	CurrentThrottleIndex;
/* off 0x004f */	unsigned char	ThermalThrottleIndex;
/* off 0x0050 */	unsigned long	LastKernelUserTime;
/* off 0x0054 */	unsigned long	LastIdleThreadKernelTime;
/* off 0x0058 */	unsigned long	PackageIdleStartTime;
/* off 0x005c */	unsigned long	PackageIdleTime;
/* off 0x0060 */	unsigned long	DebugCount;
/* off 0x0064 */	unsigned long	LastSysTime;
/* off 0x0068 */	unsigned __int64 TotalIdleStateTime[3];
/* off 0x0080 */	unsigned long TotalIdleTransitions[3];
/* off 0x0090 */	unsigned __int64	PreviousC3StateTime;
/* off 0x0098 */	unsigned char	KneeThrottleIndex;
/* off 0x0099 */	unsigned char	ThrottleLimitIndex;
/* off 0x009a */	unsigned char	PerfStatesCount;
/* off 0x009b */	unsigned char	ProcessorMinThrottle;
/* off 0x009c */	unsigned char	ProcessorMaxThrottle;
/* off 0x009d */	unsigned char	EnableIdleAccounting;
/* off 0x009e */	unsigned char	LastC3Percentage;
/* off 0x009f */	unsigned char	LastAdjustedBusyPercentage;
/* off 0x00a0 */	unsigned long	PromotionCount;
/* off 0x00a4 */	unsigned long	DemotionCount;
/* off 0x00a8 */	unsigned long	ErrorCount;
/* off 0x00ac */	unsigned long	RetryCount;
/* off 0x00b0 */	unsigned long	Flags;
/* off 0x00b8 */	union _LARGE_INTEGER	PerfCounterFrequency;
/* off 0x00c0 */	unsigned long	PerfTickCount;
/* off 0x00c8 */	struct _KTIMER	PerfTimer;
/* off 0x00f0 */	struct _KDPC	PerfDpc;
/* off 0x0110 */	struct PROCESSOR_PERF_STATE*	PerfStates;
/* off 0x0114 */	long( __fastcall *PerfSetThrottle)(unsigned char);
/* off 0x0118 */	unsigned long	LastC3KernelUserTime;
/* off 0x011c */	unsigned long	LastPackageIdleTime;
};
struct _KPRCB /* sizeof 00000c50 3152 */
{
/* off 0x0000 */	unsigned short	MinorVersion;
/* off 0x0002 */	unsigned short	MajorVersion;
/* off 0x0004 */	struct _KTHREAD*	CurrentThread;
/* off 0x0008 */	struct _KTHREAD*	NextThread;
/* off 0x000c */	struct _KTHREAD*	IdleThread;
/* off 0x0010 */	char	Number;
/* off 0x0011 */	char	Reserved;
/* off 0x0012 */	unsigned short	BuildType;
/* off 0x0014 */	unsigned long	SetMember;
/* off 0x0018 */	char	CpuType;
/* off 0x0019 */	char	CpuID;
/* off 0x001a */	unsigned short	CpuStep;
/* off 0x001c */	struct _KPROCESSOR_STATE	ProcessorState;
/* off 0x033c */	unsigned long KernelReserved[16];
/* off 0x037c */	unsigned long HalReserved[16];
/* off 0x03bc */	unsigned char PrcbPad0[92];
/* off 0x0418 */	struct _KSPIN_LOCK_QUEUE LockQueue[16];
/* off 0x0498 */	unsigned char PrcbPad1[8];
/* off 0x04a0 */	struct _KTHREAD*	NpxThread;
/* off 0x04a4 */	unsigned long	InterruptCount;
/* off 0x04a8 */	unsigned long	KernelTime;
/* off 0x04ac */	unsigned long	UserTime;
/* off 0x04b0 */	unsigned long	DpcTime;
/* off 0x04b4 */	unsigned long	DebugDpcTime;
/* off 0x04b8 */	unsigned long	InterruptTime;
/* off 0x04bc */	unsigned long	AdjustDpcThreshold;
/* off 0x04c0 */	unsigned long	PageColor;
/* off 0x04c4 */	unsigned long	SkipTick;
/* off 0x04c8 */	unsigned char	MultiThreadSetBusy;
/* off 0x04c9 */	unsigned char Spare2[3];
/* off 0x04cc */	struct _KNODE*	ParentNode;
/* off 0x04d0 */	unsigned long	MultiThreadProcessorSet;
/* off 0x04d4 */	struct _KPRCB*	MultiThreadSetMaster;
/* off 0x04d8 */	unsigned long ThreadStartCount[2];
/* off 0x04e0 */	unsigned long	CcFastReadNoWait;
/* off 0x04e4 */	unsigned long	CcFastReadWait;
/* off 0x04e8 */	unsigned long	CcFastReadNotPossible;
/* off 0x04ec */	unsigned long	CcCopyReadNoWait;
/* off 0x04f0 */	unsigned long	CcCopyReadWait;
/* off 0x04f4 */	unsigned long	CcCopyReadNoWaitMiss;
/* off 0x04f8 */	unsigned long	KeAlignmentFixupCount;
/* off 0x04fc */	unsigned long	KeContextSwitches;
/* off 0x0500 */	unsigned long	KeDcacheFlushCount;
/* off 0x0504 */	unsigned long	KeExceptionDispatchCount;
/* off 0x0508 */	unsigned long	KeFirstLevelTbFills;
/* off 0x050c */	unsigned long	KeFloatingEmulationCount;
/* off 0x0510 */	unsigned long	KeIcacheFlushCount;
/* off 0x0514 */	unsigned long	KeSecondLevelTbFills;
/* off 0x0518 */	unsigned long	KeSystemCalls;
/* off 0x051c */	unsigned long SpareCounter0[1];
/* off 0x0520 */	struct _PP_LOOKASIDE_LIST PPLookasideList[16];
/* off 0x05a0 */	struct _PP_LOOKASIDE_LIST PPNPagedLookasideList[32];
/* off 0x06a0 */	struct _PP_LOOKASIDE_LIST PPPagedLookasideList[32];
/* off 0x07a0 */	unsigned long	PacketBarrier;
/* off 0x07a4 */	unsigned long	ReverseStall;
/* off 0x07a8 */	void*	IpiFrame;
/* off 0x07ac */	unsigned char PrcbPad2[52];
/* off 0x07e0 */	void* CurrentPacket[3];
/* off 0x07ec */	unsigned long	TargetSet;
/* off 0x07f0 */	void( __cdecl *WorkerRoutine)(void*,void*,void*,void*);
/* off 0x07f4 */	unsigned long	IpiFrozen;
/* off 0x07f8 */	unsigned char PrcbPad3[40];
/* off 0x0820 */	unsigned long	RequestSummary;
/* off 0x0824 */	struct _KPRCB*	SignalDone;
/* off 0x0828 */	unsigned char PrcbPad4[56];
/* off 0x0860 */	struct _LIST_ENTRY	DpcListHead;
/* off 0x0868 */	void*	DpcStack;
/* off 0x086c */	unsigned long	DpcCount;
/* off 0x0870 */	unsigned long	DpcQueueDepth;
/* off 0x0874 */	unsigned long	DpcRoutineActive;
/* off 0x0878 */	unsigned long	DpcInterruptRequested;
/* off 0x087c */	unsigned long	DpcLastCount;
/* off 0x0880 */	unsigned long	DpcRequestRate;
/* off 0x0884 */	unsigned long	MaximumDpcQueueDepth;
/* off 0x0888 */	unsigned long	MinimumDpcRate;
/* off 0x088c */	unsigned long	QuantumEnd;
/* off 0x0890 */	unsigned char PrcbPad5[16];
/* off 0x08a0 */	unsigned long	DpcLock;
/* off 0x08a4 */	unsigned char PrcbPad6[28];
/* off 0x08c0 */	struct _KDPC	CallDpc;
/* off 0x08e0 */	void*	ChainedInterruptList;
/* off 0x08e4 */	long	LookasideIrpFloat;
/* off 0x08e8 */	unsigned long SpareFields0[6];
/* off 0x0900 */	unsigned char VendorString[13];
/* off 0x090d */	unsigned char	InitialApicId;
/* off 0x090e */	unsigned char	LogicalProcessorsPerPhysicalProcessor;
/* off 0x0910 */	unsigned long	MHz;
/* off 0x0914 */	unsigned long	FeatureBits;
/* off 0x0918 */	union _LARGE_INTEGER	UpdateSignature;
/* off 0x0920 */	struct _FX_SAVE_AREA	NpxSaveArea;
/* off 0x0b30 */	struct _PROCESSOR_POWER_STATE	PowerState;
};
union _SLIST_HEADER /* sizeof 00000008 8 */
{
/* off 0x0000 */	unsigned __int64	Alignment;
struct
{
/* off 0x0000 */	struct _SINGLE_LIST_ENTRY	Next;
/* off 0x0004 */	unsigned short	Depth;
/* off 0x0006 */	unsigned short	Sequence;
};
};
struct _flags /* sizeof 00000001 1 */
{
/* off 0x0000 */	unsigned char	Removable;
};
struct _KNODE /* sizeof 00000030 48 */
{
/* off 0x0000 */	unsigned long	ProcessorMask;
/* off 0x0004 */	unsigned long	Color;
/* off 0x0008 */	unsigned long	MmShiftedColor;
/* off 0x000c */	unsigned long FreeCount[2];
/* off 0x0018 */	union _SLIST_HEADER	DeadStackList;
/* off 0x0020 */	union _SLIST_HEADER	PfnDereferenceSListHead;
/* off 0x0028 */	struct _SINGLE_LIST_ENTRY*	PfnDeferredList;
/* off 0x002c */	unsigned char	Seed;
/* off 0x002d */	struct _flags	Flags;
};
struct _GENERAL_LOOKASIDE /* sizeof 00000080 128 */
{
/* off 0x0000 */	union _SLIST_HEADER	ListHead;
/* off 0x0008 */	unsigned short	Depth;
/* off 0x000a */	unsigned short	MaximumDepth;
/* off 0x000c */	unsigned long	TotalAllocates;
union
{
/* off 0x0010 */	unsigned long	AllocateMisses;
/* off 0x0010 */	unsigned long	AllocateHits;
};
/* off 0x0014 */	unsigned long	TotalFrees;
union
{
/* off 0x0018 */	unsigned long	FreeMisses;
/* off 0x0018 */	unsigned long	FreeHits;
};
/* off 0x001c */	enum _POOL_TYPE	Type;
/* off 0x0020 */	unsigned long	Tag;
/* off 0x0024 */	unsigned long	Size;
/* off 0x0028 */	void*( __cdecl *Allocate)(enum _POOL_TYPE,unsigned long,unsigned long);
/* off 0x002c */	void( __cdecl *Free)(void*);
/* off 0x0030 */	struct _LIST_ENTRY	ListEntry;
/* off 0x0038 */	unsigned long	LastTotalAllocates;
union
{
/* off 0x003c */	unsigned long	LastAllocateMisses;
/* off 0x003c */	unsigned long	LastAllocateHits;
};
/* off 0x0040 */	unsigned long Future[2];
};
enum _POOL_TYPE
{
	NonPagedPool	=0x00000000	,//0
	PagedPool	=0x00000001	,//0
	NonPagedPoolMustSucceed	=0x00000002	,//0
	DontUseThisType	=0x00000003	,//0
	NonPagedPoolCacheAligned	=0x00000004	,//0
	PagedPoolCacheAligned	=0x00000005	,//0
	NonPagedPoolCacheAlignedMustS	=0x00000006	,//0
	MaxPoolType	=0x00000007	,//0
	NonPagedPoolSession	=0x00000020	,//0
	PagedPoolSession	=0x00000021	,//0
	NonPagedPoolMustSucceedSession	=0x00000022	,//0
	DontUseThisTypeSession	=0x00000023	,//0
	NonPagedPoolCacheAlignedSession	=0x00000024	,//0
	PagedPoolCacheAlignedSession	=0x00000025	,//0
	NonPagedPoolCacheAlignedMustSSession	=0x00000026	,//0
};
struct PROCESSOR_PERF_STATE /* sizeof 00000020 32 */
{
/* off 0x0000 */	unsigned char	PercentFrequency;
/* off 0x0001 */	unsigned char	MinCapacity;
/* off 0x0002 */	unsigned short	Power;
/* off 0x0004 */	unsigned char	IncreaseLevel;
/* off 0x0005 */	unsigned char	DecreaseLevel;
/* off 0x0006 */	unsigned short	Flags;
/* off 0x0008 */	unsigned long	IncreaseTime;
/* off 0x000c */	unsigned long	DecreaseTime;
/* off 0x0010 */	unsigned long	IncreaseCount;
/* off 0x0014 */	unsigned long	DecreaseCount;
/* off 0x0018 */	unsigned __int64	PerformanceTime;
};
struct _NPAGED_LOOKASIDE_LIST /* sizeof 00000100 256 */
{
/* off 0x0000 */	struct _GENERAL_LOOKASIDE	L;
/* off 0x0080 */	unsigned long	Lock__ObsoleteButDoNotDelete;
};
struct _KEVENT /* sizeof 00000010 16 */
{
/* off 0x0000 */	struct _DISPATCHER_HEADER	Header;
};
struct _FAST_MUTEX /* sizeof 00000020 32 */
{
/* off 0x0000 */	long	Count;
/* off 0x0004 */	struct _KTHREAD*	Owner;
/* off 0x0008 */	unsigned long	Contention;
/* off 0x000c */	struct _KEVENT	Event;
/* off 0x001c */	unsigned long	OldIrql;
};
struct _PAGED_LOOKASIDE_LIST /* sizeof 00000100 256 */
{
/* off 0x0000 */	struct _GENERAL_LOOKASIDE	L;
/* off 0x0080 */	struct _FAST_MUTEX	Lock__ObsoleteButDoNotDelete;
};
enum _PP_NPAGED_LOOKASIDE_NUMBER
{
	LookasideSmallIrpList	=0x00000000	,//0
	LookasideLargeIrpList	=0x00000001	,//0
	LookasideMdlList	=0x00000002	,//0
	LookasideCreateInfoList	=0x00000003	,//0
	LookasideNameBufferList	=0x00000004	,//0
	LookasideTwilightList	=0x00000005	,//0
	LookasideCompletionList	=0x00000006	,//0
	LookasideMaximumList	=0x00000007	,//0
};
struct _EX_RUNDOWN_REF /* sizeof 00000004 4 */
{
union
{
/* off 0x0000 */	unsigned long	Count;
/* off 0x0000 */	void*	Ptr;
};
};
struct _EX_FAST_REF /* sizeof 00000004 4 */
{
union
{
/* off 0x0000 */	void*	Object;
/* off 0x0000 */	unsigned long	RefCnt:3	 /* start bit 0 */;
/* off 0x0000 */	unsigned long	Value;
};
};
struct _EX_PUSH_LOCK /* sizeof 00000004 4 */
{
union
{
struct
{
/* off 0x0000 */	unsigned long	Waiting:1	 /* start bit 0 */;
/* off 0x0000 */	unsigned long	Exclusive:1	 /* start bit 1 */;
/* off 0x0000 */	unsigned long	Shared:30	 /* start bit 2 */;
};
/* off 0x0000 */	unsigned long	Value;
/* off 0x0000 */	void*	Ptr;
};
};
struct _EX_PUSH_LOCK_WAIT_BLOCK /* sizeof 0000001c 28 */
{
/* off 0x0000 */	struct _KEVENT	WakeEvent;
/* off 0x0010 */	struct _EX_PUSH_LOCK_WAIT_BLOCK*	Next;
/* off 0x0014 */	unsigned long	ShareCount;
/* off 0x0018 */	unsigned char	Exclusive;
};
struct _EX_PUSH_LOCK_CACHE_AWARE /* sizeof 00000080 128 */
{
/* off 0x0000 */	struct _EX_PUSH_LOCK* Locks[32];
};
struct _CLIENT_ID /* sizeof 00000008 8 */
{
/* off 0x0000 */	void*	UniqueProcess;
/* off 0x0004 */	void*	UniqueThread;
};
struct _ETHREAD /* sizeof 00000258 600 */
{
/* off 0x0000 */	struct _KTHREAD	Tcb;
union
{
/* off 0x01c0 */	union _LARGE_INTEGER	CreateTime;
struct
{
/* off 0x01c0 */	unsigned int	NestedFaultCount:2	 /* start bit 0 */;
/* off 0x01c0 */	unsigned int	ApcNeeded:1	 /* start bit 2 */;
};
};
union
{
/* off 0x01c8 */	union _LARGE_INTEGER	ExitTime;
/* off 0x01c8 */	struct _LIST_ENTRY	LpcReplyChain;
/* off 0x01c8 */	struct _LIST_ENTRY	KeyedWaitChain;
};
union
{
/* off 0x01d0 */	long	ExitStatus;
/* off 0x01d0 */	void*	OfsChain;
};
/* off 0x01d4 */	struct _LIST_ENTRY	PostBlockList;
union
{
/* off 0x01dc */	struct _TERMINATION_PORT*	TerminationPort;
/* off 0x01dc */	struct _ETHREAD*	ReaperLink;
/* off 0x01dc */	void*	KeyedWaitValue;
};
/* off 0x01e0 */	unsigned long	ActiveTimerListLock;
/* off 0x01e4 */	struct _LIST_ENTRY	ActiveTimerListHead;
/* off 0x01ec */	struct _CLIENT_ID	Cid;
union
{
/* off 0x01f4 */	struct _KSEMAPHORE	LpcReplySemaphore;
/* off 0x01f4 */	struct _KSEMAPHORE	KeyedWaitSemaphore;
};
union
{
/* off 0x0208 */	void*	LpcReplyMessage;
/* off 0x0208 */	void*	LpcWaitingOnPort;
};
/* off 0x020c */	struct _PS_IMPERSONATION_INFORMATION*	ImpersonationInfo;
/* off 0x0210 */	struct _LIST_ENTRY	IrpList;
/* off 0x0218 */	unsigned long	TopLevelIrp;
/* off 0x021c */	struct _DEVICE_OBJECT*	DeviceToVerify;
/* off 0x0220 */	struct _EPROCESS*	ThreadsProcess;
/* off 0x0224 */	void*	StartAddress;
union
{
/* off 0x0228 */	void*	Win32StartAddress;
/* off 0x0228 */	unsigned long	LpcReceivedMessageId;
};
/* off 0x022c */	struct _LIST_ENTRY	ThreadListEntry;
/* off 0x0234 */	struct _EX_RUNDOWN_REF	RundownProtect;
/* off 0x0238 */	struct _EX_PUSH_LOCK	ThreadLock;
/* off 0x023c */	unsigned long	LpcReplyMessageId;
/* off 0x0240 */	unsigned long	ReadClusterSize;
/* off 0x0244 */	unsigned long	GrantedAccess;
union
{
/* off 0x0248 */	unsigned long	CrossThreadFlags;
struct
{
/* off 0x0248 */	unsigned long	Terminated:1	 /* start bit 0 */;
/* off 0x0248 */	unsigned long	DeadThread:1	 /* start bit 1 */;
/* off 0x0248 */	unsigned long	HideFromDebugger:1	 /* start bit 2 */;
/* off 0x0248 */	unsigned long	ActiveImpersonationInfo:1	 /* start bit 3 */;
/* off 0x0248 */	unsigned long	SystemThread:1	 /* start bit 4 */;
/* off 0x0248 */	unsigned long	HardErrorsAreDisabled:1	 /* start bit 5 */;
/* off 0x0248 */	unsigned long	BreakOnTermination:1	 /* start bit 6 */;
/* off 0x0248 */	unsigned long	SkipCreationMsg:1	 /* start bit 7 */;
/* off 0x0248 */	unsigned long	SkipTerminationMsg:1	 /* start bit 8 */;
};
};
union
{
/* off 0x024c */	unsigned long	SameThreadPassiveFlags;
struct
{
/* off 0x024c */	unsigned long	ActiveExWorker:1	 /* start bit 0 */;
/* off 0x024c */	unsigned long	ExWorkerCanWaitUser:1	 /* start bit 1 */;
/* off 0x024c */	unsigned long	MemoryMaker:1	 /* start bit 2 */;
};
};
union
{
/* off 0x0250 */	unsigned long	SameThreadApcFlags;
struct
{
/* off 0x0250 */	unsigned char	LpcReceivedMsgIdValid:1	 /* start bit 0 */;
/* off 0x0250 */	unsigned char	LpcExitThreadCalled:1	 /* start bit 1 */;
/* off 0x0250 */	unsigned char	AddressSpaceOwner:1	 /* start bit 2 */;
};
};
/* off 0x0254 */	unsigned char	ForwardClusterOnly;
/* off 0x0255 */	unsigned char	DisablePageFaultClustering;
};
struct _TERMINATION_PORT /* sizeof 00000008 8 */
{
/* off 0x0000 */	struct _TERMINATION_PORT*	Next;
/* off 0x0004 */	void*	Port;
};
struct _PS_IMPERSONATION_INFORMATION /* sizeof 0000000c 12 */
{
/* off 0x0000 */	void*	Token;
/* off 0x0004 */	unsigned char	CopyOnOpen;
/* off 0x0005 */	unsigned char	EffectiveOnly;
/* off 0x0008 */	enum _SECURITY_IMPERSONATION_LEVEL	ImpersonationLevel;
};
enum _SECURITY_IMPERSONATION_LEVEL
{
	SecurityAnonymous	=0x00000000	,//0
	SecurityIdentification	=0x00000001	,//0
	SecurityImpersonation	=0x00000002	,//0
	SecurityDelegation	=0x00000003	,//0
};
struct _KDEVICE_QUEUE /* sizeof 00000014 20 */
{
/* off 0x0000 */	short	Type;
/* off 0x0002 */	short	Size;
/* off 0x0004 */	struct _LIST_ENTRY	DeviceListHead;
/* off 0x000c */	unsigned long	Lock;
/* off 0x0010 */	unsigned char	Busy;
};
struct _DEVICE_OBJECT /* sizeof 000000b8 184 */
{
/* off 0x0000 */	short	Type;
/* off 0x0002 */	unsigned short	Size;
/* off 0x0004 */	long	ReferenceCount;
/* off 0x0008 */	struct _DRIVER_OBJECT*	DriverObject;
/* off 0x000c */	struct _DEVICE_OBJECT*	NextDevice;
/* off 0x0010 */	struct _DEVICE_OBJECT*	AttachedDevice;
/* off 0x0014 */	struct _IRP*	CurrentIrp;
/* off 0x0018 */	struct _IO_TIMER*	Timer;
/* off 0x001c */	unsigned long	Flags;
/* off 0x0020 */	unsigned long	Characteristics;
/* off 0x0024 */	struct _VPB*	Vpb;
/* off 0x0028 */	void*	DeviceExtension;
/* off 0x002c */	unsigned long	DeviceType;
/* off 0x0030 */	char	StackSize;
/* off 0x0034 */	struct __unnamed	Queue;
/* off 0x005c */	unsigned long	AlignmentRequirement;
/* off 0x0060 */	struct _KDEVICE_QUEUE	DeviceQueue;
/* off 0x0074 */	struct _KDPC	Dpc;
/* off 0x0094 */	unsigned long	ActiveThreadCount;
/* off 0x0098 */	void*	SecurityDescriptor;
/* off 0x009c */	struct _KEVENT	DeviceLock;
/* off 0x00ac */	unsigned short	SectorSize;
/* off 0x00ae */	unsigned short	Spare1;
/* off 0x00b0 */	struct _DEVOBJ_EXTENSION*	DeviceObjectExtension;
/* off 0x00b4 */	void*	Reserved;
};
struct _UNICODE_STRING /* sizeof 00000008 8 */
{
/* off 0x0000 */	unsigned short	Length;
/* off 0x0002 */	unsigned short	MaximumLength;
/* off 0x0004 */	unsigned short*	Buffer;
};
struct _DRIVER_OBJECT /* sizeof 000000a8 168 */
{
/* off 0x0000 */	short	Type;
/* off 0x0002 */	short	Size;
/* off 0x0004 */	struct _DEVICE_OBJECT*	DeviceObject;
/* off 0x0008 */	unsigned long	Flags;
/* off 0x000c */	void*	DriverStart;
/* off 0x0010 */	unsigned long	DriverSize;
/* off 0x0014 */	void*	DriverSection;
/* off 0x0018 */	struct _DRIVER_EXTENSION*	DriverExtension;
/* off 0x001c */	struct _UNICODE_STRING	DriverName;
/* off 0x0024 */	struct _UNICODE_STRING*	HardwareDatabase;
/* off 0x0028 */	struct _FAST_IO_DISPATCH*	FastIoDispatch;
/* off 0x002c */	long( __cdecl *DriverInit)(struct _DRIVER_OBJECT*,struct _UNICODE_STRING*);
/* off 0x0030 */	void( __cdecl *DriverStartIo)(struct _DEVICE_OBJECT*,struct _IRP*);
/* off 0x0034 */	void( __cdecl *DriverUnload)(struct _DRIVER_OBJECT*);
/* off 0x0038 */	long( __cdecl * MajorFunction[28])(struct _DEVICE_OBJECT*,struct _IRP*);
};
struct _DRIVER_EXTENSION /* sizeof 0000001c 28 */
{
/* off 0x0000 */	struct _DRIVER_OBJECT*	DriverObject;
/* off 0x0004 */	long( __cdecl *AddDevice)(struct _DRIVER_OBJECT*,struct _DEVICE_OBJECT*);
/* off 0x0008 */	unsigned long	Count;
/* off 0x000c */	struct _UNICODE_STRING	ServiceKeyName;
/* off 0x0014 */	struct _IO_CLIENT_EXTENSION*	ClientDriverExtension;
/* off 0x0018 */	struct _FS_FILTER_CALLBACKS*	FsFilterCallbacks;
};
struct _IO_CLIENT_EXTENSION /* sizeof 00000008 8 */
{
/* off 0x0000 */	struct _IO_CLIENT_EXTENSION*	NextExtension;
/* off 0x0004 */	void*	ClientIdentificationAddress;
};
struct _FS_FILTER_CALLBACKS /* sizeof 00000038 56 */
{
/* off 0x0000 */	unsigned long	SizeOfFsFilterCallbacks;
/* off 0x0004 */	unsigned long	Reserved;
/* off 0x0008 */	long( __cdecl *PreAcquireForSectionSynchronization)(struct _FS_FILTER_CALLBACK_DATA*,void**);
/* off 0x000c */	void( __cdecl *PostAcquireForSectionSynchronization)(struct _FS_FILTER_CALLBACK_DATA*,long,void*);
/* off 0x0010 */	long( __cdecl *PreReleaseForSectionSynchronization)(struct _FS_FILTER_CALLBACK_DATA*,void**);
/* off 0x0014 */	void( __cdecl *PostReleaseForSectionSynchronization)(struct _FS_FILTER_CALLBACK_DATA*,long,void*);
/* off 0x0018 */	long( __cdecl *PreAcquireForCcFlush)(struct _FS_FILTER_CALLBACK_DATA*,void**);
/* off 0x001c */	void( __cdecl *PostAcquireForCcFlush)(struct _FS_FILTER_CALLBACK_DATA*,long,void*);
/* off 0x0020 */	long( __cdecl *PreReleaseForCcFlush)(struct _FS_FILTER_CALLBACK_DATA*,void**);
/* off 0x0024 */	void( __cdecl *PostReleaseForCcFlush)(struct _FS_FILTER_CALLBACK_DATA*,long,void*);
/* off 0x0028 */	long( __cdecl *PreAcquireForModifiedPageWriter)(struct _FS_FILTER_CALLBACK_DATA*,void**);
/* off 0x002c */	void( __cdecl *PostAcquireForModifiedPageWriter)(struct _FS_FILTER_CALLBACK_DATA*,long,void*);
/* off 0x0030 */	long( __cdecl *PreReleaseForModifiedPageWriter)(struct _FS_FILTER_CALLBACK_DATA*,void**);
/* off 0x0034 */	void( __cdecl *PostReleaseForModifiedPageWriter)(struct _FS_FILTER_CALLBACK_DATA*,long,void*);
};
union _FS_FILTER_PARAMETERS /* sizeof 00000014 20 */
{
/* off 0x0000 */	struct __unnamed	AcquireForModifiedPageWriter;
/* off 0x0000 */	struct __unnamed	ReleaseForModifiedPageWriter;
/* off 0x0000 */	struct __unnamed	AcquireForSectionSynchronization;
/* off 0x0000 */	struct __unnamed	Others;
};
struct _FS_FILTER_CALLBACK_DATA /* sizeof 00000024 36 */
{
/* off 0x0000 */	unsigned long	SizeOfFsFilterCallbackData;
/* off 0x0004 */	unsigned char	Operation;
/* off 0x0005 */	unsigned char	Reserved;
/* off 0x0008 */	struct _DEVICE_OBJECT*	DeviceObject;
/* off 0x000c */	struct _FILE_OBJECT*	FileObject;
/* off 0x0010 */	union _FS_FILTER_PARAMETERS	Parameters;
};
struct _FILE_OBJECT /* sizeof 00000070 112 */
{
/* off 0x0000 */	short	Type;
/* off 0x0002 */	short	Size;
/* off 0x0004 */	struct _DEVICE_OBJECT*	DeviceObject;
/* off 0x0008 */	struct _VPB*	Vpb;
/* off 0x000c */	void*	FsContext;
/* off 0x0010 */	void*	FsContext2;
/* off 0x0014 */	struct _SECTION_OBJECT_POINTERS*	SectionObjectPointer;
/* off 0x0018 */	void*	PrivateCacheMap;
/* off 0x001c */	long	FinalStatus;
/* off 0x0020 */	struct _FILE_OBJECT*	RelatedFileObject;
/* off 0x0024 */	unsigned char	LockOperation;
/* off 0x0025 */	unsigned char	DeletePending;
/* off 0x0026 */	unsigned char	ReadAccess;
/* off 0x0027 */	unsigned char	WriteAccess;
/* off 0x0028 */	unsigned char	DeleteAccess;
/* off 0x0029 */	unsigned char	SharedRead;
/* off 0x002a */	unsigned char	SharedWrite;
/* off 0x002b */	unsigned char	SharedDelete;
/* off 0x002c */	unsigned long	Flags;
/* off 0x0030 */	struct _UNICODE_STRING	FileName;
/* off 0x0038 */	union _LARGE_INTEGER	CurrentByteOffset;
/* off 0x0040 */	unsigned long	Waiters;
/* off 0x0044 */	unsigned long	Busy;
/* off 0x0048 */	void*	LastLock;
/* off 0x004c */	struct _KEVENT	Lock;
/* off 0x005c */	struct _KEVENT	Event;
/* off 0x006c */	struct _IO_COMPLETION_CONTEXT*	CompletionContext;
};
struct _VPB /* sizeof 00000058 88 */
{
/* off 0x0000 */	short	Type;
/* off 0x0002 */	short	Size;
/* off 0x0004 */	unsigned short	Flags;
/* off 0x0006 */	unsigned short	VolumeLabelLength;
/* off 0x0008 */	struct _DEVICE_OBJECT*	DeviceObject;
/* off 0x000c */	struct _DEVICE_OBJECT*	RealDevice;
/* off 0x0010 */	unsigned long	SerialNumber;
/* off 0x0014 */	unsigned long	ReferenceCount;
/* off 0x0018 */	unsigned short VolumeLabel[32];
};
struct _SECTION_OBJECT_POINTERS /* sizeof 0000000c 12 */
{
/* off 0x0000 */	void*	DataSectionObject;
/* off 0x0004 */	void*	SharedCacheMap;
/* off 0x0008 */	void*	ImageSectionObject;
};
struct _IO_COMPLETION_CONTEXT /* sizeof 00000008 8 */
{
/* off 0x0000 */	void*	Port;
/* off 0x0004 */	void*	Key;
};
struct _FAST_IO_DISPATCH /* sizeof 00000070 112 */
{
/* off 0x0000 */	unsigned long	SizeOfFastIoDispatch;
/* off 0x0004 */	unsigned char( __cdecl *FastIoCheckIfPossible)(struct _FILE_OBJECT*,union _LARGE_INTEGER*,unsigned long,unsigned char,unsigned long,unsigned char,struct _IO_STATUS_BLOCK*,struct _DEVICE_OBJECT*);
/* off 0x0008 */	unsigned char( __cdecl *FastIoRead)(struct _FILE_OBJECT*,union _LARGE_INTEGER*,unsigned long,unsigned char,unsigned long,void*,struct _IO_STATUS_BLOCK*,struct _DEVICE_OBJECT*);
/* off 0x000c */	unsigned char( __cdecl *FastIoWrite)(struct _FILE_OBJECT*,union _LARGE_INTEGER*,unsigned long,unsigned char,unsigned long,void*,struct _IO_STATUS_BLOCK*,struct _DEVICE_OBJECT*);
/* off 0x0010 */	unsigned char( __cdecl *FastIoQueryBasicInfo)(struct _FILE_OBJECT*,unsigned char,struct _FILE_BASIC_INFORMATION*,struct _IO_STATUS_BLOCK*,struct _DEVICE_OBJECT*);
/* off 0x0014 */	unsigned char( __cdecl *FastIoQueryStandardInfo)(struct _FILE_OBJECT*,unsigned char,struct _FILE_STANDARD_INFORMATION*,struct _IO_STATUS_BLOCK*,struct _DEVICE_OBJECT*);
/* off 0x0018 */	unsigned char( __cdecl *FastIoLock)(struct _FILE_OBJECT*,union _LARGE_INTEGER*,union _LARGE_INTEGER*,struct _EPROCESS*,unsigned long,unsigned char,unsigned char,struct _IO_STATUS_BLOCK*,struct _DEVICE_OBJECT*);
/* off 0x001c */	unsigned char( __cdecl *FastIoUnlockSingle)(struct _FILE_OBJECT*,union _LARGE_INTEGER*,union _LARGE_INTEGER*,struct _EPROCESS*,unsigned long,struct _IO_STATUS_BLOCK*,struct _DEVICE_OBJECT*);
/* off 0x0020 */	unsigned char( __cdecl *FastIoUnlockAll)(struct _FILE_OBJECT*,struct _EPROCESS*,struct _IO_STATUS_BLOCK*,struct _DEVICE_OBJECT*);
/* off 0x0024 */	unsigned char( __cdecl *FastIoUnlockAllByKey)(struct _FILE_OBJECT*,void*,unsigned long,struct _IO_STATUS_BLOCK*,struct _DEVICE_OBJECT*);
/* off 0x0028 */	unsigned char( __cdecl *FastIoDeviceControl)(struct _FILE_OBJECT*,unsigned char,void*,unsigned long,void*,unsigned long,unsigned long,struct _IO_STATUS_BLOCK*,struct _DEVICE_OBJECT*);
/* off 0x002c */	void( __cdecl *AcquireFileForNtCreateSection)(struct _FILE_OBJECT*);
/* off 0x0030 */	void( __cdecl *ReleaseFileForNtCreateSection)(struct _FILE_OBJECT*);
/* off 0x0034 */	void( __cdecl *FastIoDetachDevice)(struct _DEVICE_OBJECT*,struct _DEVICE_OBJECT*);
/* off 0x0038 */	unsigned char( __cdecl *FastIoQueryNetworkOpenInfo)(struct _FILE_OBJECT*,unsigned char,struct _FILE_NETWORK_OPEN_INFORMATION*,struct _IO_STATUS_BLOCK*,struct _DEVICE_OBJECT*);
/* off 0x003c */	long( __cdecl *AcquireForModWrite)(struct _FILE_OBJECT*,union _LARGE_INTEGER*,struct _ERESOURCE**,struct _DEVICE_OBJECT*);
/* off 0x0040 */	unsigned char( __cdecl *MdlRead)(struct _FILE_OBJECT*,union _LARGE_INTEGER*,unsigned long,unsigned long,struct _MDL**,struct _IO_STATUS_BLOCK*,struct _DEVICE_OBJECT*);
/* off 0x0044 */	unsigned char( __cdecl *MdlReadComplete)(struct _FILE_OBJECT*,struct _MDL*,struct _DEVICE_OBJECT*);
/* off 0x0048 */	unsigned char( __cdecl *PrepareMdlWrite)(struct _FILE_OBJECT*,union _LARGE_INTEGER*,unsigned long,unsigned long,struct _MDL**,struct _IO_STATUS_BLOCK*,struct _DEVICE_OBJECT*);
/* off 0x004c */	unsigned char( __cdecl *MdlWriteComplete)(struct _FILE_OBJECT*,union _LARGE_INTEGER*,struct _MDL*,struct _DEVICE_OBJECT*);
/* off 0x0050 */	unsigned char( __cdecl *FastIoReadCompressed)(struct _FILE_OBJECT*,union _LARGE_INTEGER*,unsigned long,unsigned long,void*,struct _MDL**,struct _IO_STATUS_BLOCK*,struct _COMPRESSED_DATA_INFO*,unsigned long,struct _DEVICE_OBJECT*);
/* off 0x0054 */	unsigned char( __cdecl *FastIoWriteCompressed)(struct _FILE_OBJECT*,union _LARGE_INTEGER*,unsigned long,unsigned long,void*,struct _MDL**,struct _IO_STATUS_BLOCK*,struct _COMPRESSED_DATA_INFO*,unsigned long,struct _DEVICE_OBJECT*);
/* off 0x0058 */	unsigned char( __cdecl *MdlReadCompleteCompressed)(struct _FILE_OBJECT*,struct _MDL*,struct _DEVICE_OBJECT*);
/* off 0x005c */	unsigned char( __cdecl *MdlWriteCompleteCompressed)(struct _FILE_OBJECT*,union _LARGE_INTEGER*,struct _MDL*,struct _DEVICE_OBJECT*);
/* off 0x0060 */	unsigned char( __cdecl *FastIoQueryOpen)(struct _IRP*,struct _FILE_NETWORK_OPEN_INFORMATION*,struct _DEVICE_OBJECT*);
/* off 0x0064 */	long( __cdecl *ReleaseForModWrite)(struct _FILE_OBJECT*,struct _ERESOURCE*,struct _DEVICE_OBJECT*);
/* off 0x0068 */	long( __cdecl *AcquireForCcFlush)(struct _FILE_OBJECT*,struct _DEVICE_OBJECT*);
/* off 0x006c */	long( __cdecl *ReleaseForCcFlush)(struct _FILE_OBJECT*,struct _DEVICE_OBJECT*);
};
struct _IO_STATUS_BLOCK /* sizeof 00000008 8 */
{
union
{
/* off 0x0000 */	long	Status;
/* off 0x0000 */	void*	Pointer;
};
/* off 0x0004 */	unsigned long	Information;
};
struct _FILE_BASIC_INFORMATION /* sizeof 00000028 40 */
{
/* off 0x0000 */	union _LARGE_INTEGER	CreationTime;
/* off 0x0008 */	union _LARGE_INTEGER	LastAccessTime;
/* off 0x0010 */	union _LARGE_INTEGER	LastWriteTime;
/* off 0x0018 */	union _LARGE_INTEGER	ChangeTime;
/* off 0x0020 */	unsigned long	FileAttributes;
};
struct _FILE_STANDARD_INFORMATION /* sizeof 00000018 24 */
{
/* off 0x0000 */	union _LARGE_INTEGER	AllocationSize;
/* off 0x0008 */	union _LARGE_INTEGER	EndOfFile;
/* off 0x0010 */	unsigned long	NumberOfLinks;
/* off 0x0014 */	unsigned char	DeletePending;
/* off 0x0015 */	unsigned char	Directory;
};
struct _HARDWARE_PTE /* sizeof 00000004 4 */
{
/* off 0x0000 */	unsigned long	Valid:1	 /* start bit 0 */;
/* off 0x0000 */	unsigned long	Write:1	 /* start bit 1 */;
/* off 0x0000 */	unsigned long	Owner:1	 /* start bit 2 */;
/* off 0x0000 */	unsigned long	WriteThrough:1	 /* start bit 3 */;
/* off 0x0000 */	unsigned long	CacheDisable:1	 /* start bit 4 */;
/* off 0x0000 */	unsigned long	Accessed:1	 /* start bit 5 */;
/* off 0x0000 */	unsigned long	Dirty:1	 /* start bit 6 */;
/* off 0x0000 */	unsigned long	LargePage:1	 /* start bit 7 */;
/* off 0x0000 */	unsigned long	Global:1	 /* start bit 8 */;
/* off 0x0000 */	unsigned long	CopyOnWrite:1	 /* start bit 9 */;
/* off 0x0000 */	unsigned long	Prototype:1	 /* start bit 10 */;
/* off 0x0000 */	unsigned long	reserved:1	 /* start bit 11 */;
/* off 0x0000 */	unsigned long	PageFrameNumber:20	 /* start bit 12 */;
};
struct _SE_AUDIT_PROCESS_CREATION_INFO /* sizeof 00000004 4 */
{
/* off 0x0000 */	struct _OBJECT_NAME_INFORMATION*	ImageFileName;
};
struct _MMSUPPORT_FLAGS /* sizeof 00000004 4 */
{
/* off 0x0000 */	unsigned int	SessionSpace:1	 /* start bit 0 */;
/* off 0x0000 */	unsigned int	BeingTrimmed:1	 /* start bit 1 */;
/* off 0x0000 */	unsigned int	SessionLeader:1	 /* start bit 2 */;
/* off 0x0000 */	unsigned int	TrimHard:1	 /* start bit 3 */;
/* off 0x0000 */	unsigned int	WorkingSetHard:1	 /* start bit 4 */;
/* off 0x0000 */	unsigned int	AddressSpaceBeingDeleted:1	 /* start bit 5 */;
/* off 0x0000 */	unsigned int	Available:10	 /* start bit 6 */;
/* off 0x0000 */	unsigned int	AllowWorkingSetAdjustment:8	 /* start bit 16 */;
/* off 0x0000 */	unsigned int	MemoryPriority:8	 /* start bit 24 */;
};
struct _MMSUPPORT /* sizeof 00000040 64 */
{
/* off 0x0000 */	union _LARGE_INTEGER	LastTrimTime;
/* off 0x0008 */	struct _MMSUPPORT_FLAGS	Flags;
/* off 0x000c */	unsigned long	PageFaultCount;
/* off 0x0010 */	unsigned long	PeakWorkingSetSize;
/* off 0x0014 */	unsigned long	WorkingSetSize;
/* off 0x0018 */	unsigned long	MinimumWorkingSetSize;
/* off 0x001c */	unsigned long	MaximumWorkingSetSize;
/* off 0x0020 */	struct _MMWSL*	VmWorkingSetList;
/* off 0x0024 */	struct _LIST_ENTRY	WorkingSetExpansionLinks;
/* off 0x002c */	unsigned long	Claim;
/* off 0x0030 */	unsigned long	NextEstimationSlot;
/* off 0x0034 */	unsigned long	NextAgingSlot;
/* off 0x0038 */	unsigned long	EstimatedAvailable;
/* off 0x003c */	unsigned long	GrowthSinceLastEstimate;
};
struct _EPROCESS /* sizeof 00000260 608 */
{
/* off 0x0000 */	struct _KPROCESS	Pcb;
/* off 0x006c */	struct _EX_PUSH_LOCK	ProcessLock;
/* off 0x0070 */	union _LARGE_INTEGER	CreateTime;
/* off 0x0078 */	union _LARGE_INTEGER	ExitTime;
/* off 0x0080 */	struct _EX_RUNDOWN_REF	RundownProtect;
/* off 0x0084 */	void*	UniqueProcessId;
/* off 0x0088 */	struct _LIST_ENTRY	ActiveProcessLinks;
/* off 0x0090 */	unsigned long QuotaUsage[3];
/* off 0x009c */	unsigned long QuotaPeak[3];
/* off 0x00a8 */	unsigned long	CommitCharge;
/* off 0x00ac */	unsigned long	PeakVirtualSize;
/* off 0x00b0 */	unsigned long	VirtualSize;
/* off 0x00b4 */	struct _LIST_ENTRY	SessionProcessLinks;
/* off 0x00bc */	void*	DebugPort;
/* off 0x00c0 */	void*	ExceptionPort;
/* off 0x00c4 */	struct _HANDLE_TABLE*	ObjectTable;
/* off 0x00c8 */	struct _EX_FAST_REF	Token;
/* off 0x00cc */	struct _FAST_MUTEX	WorkingSetLock;
/* off 0x00ec */	unsigned long	WorkingSetPage;
/* off 0x00f0 */	struct _FAST_MUTEX	AddressCreationLock;
/* off 0x0110 */	unsigned long	HyperSpaceLock;
/* off 0x0114 */	struct _ETHREAD*	ForkInProgress;
/* off 0x0118 */	unsigned long	HardwareTrigger;
/* off 0x011c */	void*	VadRoot;
/* off 0x0120 */	void*	VadHint;
/* off 0x0124 */	void*	CloneRoot;
/* off 0x0128 */	unsigned long	NumberOfPrivatePages;
/* off 0x012c */	unsigned long	NumberOfLockedPages;
/* off 0x0130 */	void*	Win32Process;
/* off 0x0134 */	struct _EJOB*	Job;
/* off 0x0138 */	void*	SectionObject;
/* off 0x013c */	void*	SectionBaseAddress;
/* off 0x0140 */	struct _EPROCESS_QUOTA_BLOCK*	QuotaBlock;
/* off 0x0144 */	struct _PAGEFAULT_HISTORY*	WorkingSetWatch;
/* off 0x0148 */	void*	Win32WindowStation;
/* off 0x014c */	void*	InheritedFromUniqueProcessId;
/* off 0x0150 */	void*	LdtInformation;
/* off 0x0154 */	void*	VadFreeHint;
/* off 0x0158 */	void*	VdmObjects;
/* off 0x015c */	void*	DeviceMap;
/* off 0x0160 */	struct _LIST_ENTRY	PhysicalVadList;
union
{
/* off 0x0168 */	struct _HARDWARE_PTE	PageDirectoryPte;
/* off 0x0168 */	unsigned __int64	Filler;
};
/* off 0x0170 */	void*	Session;
/* off 0x0174 */	unsigned char ImageFileName[16];
/* off 0x0184 */	struct _LIST_ENTRY	JobLinks;
/* off 0x018c */	void*	LockedPagesList;
/* off 0x0190 */	struct _LIST_ENTRY	ThreadListHead;
/* off 0x0198 */	void*	SecurityPort;
/* off 0x019c */	void*	PaeTop;
/* off 0x01a0 */	unsigned long	ActiveThreads;
/* off 0x01a4 */	unsigned long	GrantedAccess;
/* off 0x01a8 */	unsigned long	DefaultHardErrorProcessing;
/* off 0x01ac */	long	LastThreadExitStatus;
/* off 0x01b0 */	struct _PEB*	Peb;
/* off 0x01b4 */	struct _EX_FAST_REF	PrefetchTrace;
/* off 0x01b8 */	union _LARGE_INTEGER	ReadOperationCount;
/* off 0x01c0 */	union _LARGE_INTEGER	WriteOperationCount;
/* off 0x01c8 */	union _LARGE_INTEGER	OtherOperationCount;
/* off 0x01d0 */	union _LARGE_INTEGER	ReadTransferCount;
/* off 0x01d8 */	union _LARGE_INTEGER	WriteTransferCount;
/* off 0x01e0 */	union _LARGE_INTEGER	OtherTransferCount;
/* off 0x01e8 */	unsigned long	CommitChargeLimit;
/* off 0x01ec */	unsigned long	CommitChargePeak;
/* off 0x01f0 */	void*	AweInfo;
/* off 0x01f4 */	struct _SE_AUDIT_PROCESS_CREATION_INFO	SeAuditProcessCreationInfo;
/* off 0x01f8 */	struct _MMSUPPORT	Vm;
/* off 0x0238 */	unsigned long	LastFaultCount;
/* off 0x023c */	unsigned long	ModifiedPageCount;
/* off 0x0240 */	unsigned long	NumberOfVads;
/* off 0x0244 */	unsigned long	JobStatus;
union
{
/* off 0x0248 */	unsigned long	Flags;
struct
{
/* off 0x0248 */	unsigned long	CreateReported:1	 /* start bit 0 */;
/* off 0x0248 */	unsigned long	NoDebugInherit:1	 /* start bit 1 */;
/* off 0x0248 */	unsigned long	ProcessExiting:1	 /* start bit 2 */;
/* off 0x0248 */	unsigned long	ProcessDelete:1	 /* start bit 3 */;
/* off 0x0248 */	unsigned long	Wow64SplitPages:1	 /* start bit 4 */;
/* off 0x0248 */	unsigned long	VmDeleted:1	 /* start bit 5 */;
/* off 0x0248 */	unsigned long	OutswapEnabled:1	 /* start bit 6 */;
/* off 0x0248 */	unsigned long	Outswapped:1	 /* start bit 7 */;
/* off 0x0248 */	unsigned long	ForkFailed:1	 /* start bit 8 */;
/* off 0x0248 */	unsigned long	HasPhysicalVad:1	 /* start bit 9 */;
/* off 0x0248 */	unsigned long	AddressSpaceInitialized:2	 /* start bit 10 */;
/* off 0x0248 */	unsigned long	SetTimerResolution:1	 /* start bit 12 */;
/* off 0x0248 */	unsigned long	BreakOnTermination:1	 /* start bit 13 */;
/* off 0x0248 */	unsigned long	SessionCreationUnderway:1	 /* start bit 14 */;
/* off 0x0248 */	unsigned long	WriteWatch:1	 /* start bit 15 */;
/* off 0x0248 */	unsigned long	ProcessInSession:1	 /* start bit 16 */;
/* off 0x0248 */	unsigned long	OverrideAddressSpace:1	 /* start bit 17 */;
/* off 0x0248 */	unsigned long	HasAddressSpace:1	 /* start bit 18 */;
/* off 0x0248 */	unsigned long	LaunchPrefetched:1	 /* start bit 19 */;
/* off 0x0248 */	unsigned long	InjectInpageErrors:1	 /* start bit 20 */;
/* off 0x0248 */	unsigned long	VmTopDown:1	 /* start bit 21 */;
/* off 0x0248 */	unsigned long	Unused3:1	 /* start bit 22 */;
/* off 0x0248 */	unsigned long	Unused4:1	 /* start bit 23 */;
/* off 0x0248 */	unsigned long	VdmAllowed:1	 /* start bit 24 */;
/* off 0x0248 */	unsigned long	Unused:5	 /* start bit 25 */;
/* off 0x0248 */	unsigned long	Unused1:1	 /* start bit 30 */;
/* off 0x0248 */	unsigned long	Unused2:1	 /* start bit 31 */;
};
};
/* off 0x024c */	long	ExitStatus;
/* off 0x0250 */	unsigned short	NextPageColor;
union
{
struct
{
/* off 0x0252 */	unsigned char	SubSystemMinorVersion;
/* off 0x0253 */	unsigned char	SubSystemMajorVersion;
};
struct
{
/* off 0x0252 */	unsigned short	SubSystemVersion;
};
};
/* off 0x0254 */	unsigned char	PriorityClass;
/* off 0x0255 */	unsigned char	WorkingSetAcquiredUnsafe;
/* off 0x0258 */	unsigned long	Cookie;
};
struct _HANDLE_TABLE /* sizeof 00000044 68 */
{
/* off 0x0000 */	unsigned long	TableCode;
/* off 0x0004 */	struct _EPROCESS*	QuotaProcess;
/* off 0x0008 */	void*	UniqueProcessId;
/* off 0x000c */	struct _EX_PUSH_LOCK HandleTableLock[4];
/* off 0x001c */	struct _LIST_ENTRY	HandleTableList;
/* off 0x0024 */	struct _EX_PUSH_LOCK	HandleContentionEvent;
/* off 0x0028 */	struct _HANDLE_TRACE_DEBUG_INFO*	DebugInfo;
/* off 0x002c */	long	ExtraInfoPages;
/* off 0x0030 */	unsigned long	FirstFree;
/* off 0x0034 */	unsigned long	LastFree;
/* off 0x0038 */	unsigned long	NextHandleNeedingPool;
/* off 0x003c */	long	HandleCount;
union
{
/* off 0x0040 */	unsigned long	Flags;
/* off 0x0040 */	unsigned char	StrictFIFO:1	 /* start bit 0 */;
};
};
struct _HANDLE_TRACE_DB_ENTRY /* sizeof 00000050 80 */
{
/* off 0x0000 */	struct _CLIENT_ID	ClientId;
/* off 0x0008 */	void*	Handle;
/* off 0x000c */	unsigned long	Type;
/* off 0x0010 */	void* StackTrace[16];
};
struct _HANDLE_TRACE_DEBUG_INFO /* sizeof 00050004 327684 */
{
/* off 0x0000 */	unsigned long	CurrentStackIndex;
/* off 0x0004 */	struct _HANDLE_TRACE_DB_ENTRY TraceDb[4096];
};
struct _OWNER_ENTRY /* sizeof 00000008 8 */
{
/* off 0x0000 */	unsigned long	OwnerThread;
union
{
/* off 0x0004 */	long	OwnerCount;
/* off 0x0004 */	unsigned long	TableSize;
};
};
struct _ERESOURCE /* sizeof 00000038 56 */
{
/* off 0x0000 */	struct _LIST_ENTRY	SystemResourcesList;
/* off 0x0008 */	struct _OWNER_ENTRY*	OwnerTable;
/* off 0x000c */	short	ActiveCount;
/* off 0x000e */	unsigned short	Flag;
/* off 0x0010 */	struct _KSEMAPHORE*	SharedWaiters;
/* off 0x0014 */	struct _KEVENT*	ExclusiveWaiters;
/* off 0x0018 */	struct _OWNER_ENTRY OwnerThreads[2];
/* off 0x0028 */	unsigned long	ContentionCount;
/* off 0x002c */	unsigned short	NumberOfSharedWaiters;
/* off 0x002e */	unsigned short	NumberOfExclusiveWaiters;
union
{
/* off 0x0030 */	void*	Address;
/* off 0x0030 */	unsigned long	CreatorBackTraceIndex;
};
/* off 0x0034 */	unsigned long	SpinLock;
};
struct _IO_COUNTERS /* sizeof 00000030 48 */
{
/* off 0x0000 */	unsigned __int64	ReadOperationCount;
/* off 0x0008 */	unsigned __int64	WriteOperationCount;
/* off 0x0010 */	unsigned __int64	OtherOperationCount;
/* off 0x0018 */	unsigned __int64	ReadTransferCount;
/* off 0x0020 */	unsigned __int64	WriteTransferCount;
/* off 0x0028 */	unsigned __int64	OtherTransferCount;
};
struct _EJOB /* sizeof 00000180 384 */
{
/* off 0x0000 */	struct _KEVENT	Event;
/* off 0x0010 */	struct _LIST_ENTRY	JobLinks;
/* off 0x0018 */	struct _LIST_ENTRY	ProcessListHead;
/* off 0x0020 */	struct _ERESOURCE	JobLock;
/* off 0x0058 */	union _LARGE_INTEGER	TotalUserTime;
/* off 0x0060 */	union _LARGE_INTEGER	TotalKernelTime;
/* off 0x0068 */	union _LARGE_INTEGER	ThisPeriodTotalUserTime;
/* off 0x0070 */	union _LARGE_INTEGER	ThisPeriodTotalKernelTime;
/* off 0x0078 */	unsigned long	TotalPageFaultCount;
/* off 0x007c */	unsigned long	TotalProcesses;
/* off 0x0080 */	unsigned long	ActiveProcesses;
/* off 0x0084 */	unsigned long	TotalTerminatedProcesses;
/* off 0x0088 */	union _LARGE_INTEGER	PerProcessUserTimeLimit;
/* off 0x0090 */	union _LARGE_INTEGER	PerJobUserTimeLimit;
/* off 0x0098 */	unsigned long	LimitFlags;
/* off 0x009c */	unsigned long	MinimumWorkingSetSize;
/* off 0x00a0 */	unsigned long	MaximumWorkingSetSize;
/* off 0x00a4 */	unsigned long	ActiveProcessLimit;
/* off 0x00a8 */	unsigned long	Affinity;
/* off 0x00ac */	unsigned char	PriorityClass;
/* off 0x00b0 */	unsigned long	UIRestrictionsClass;
/* off 0x00b4 */	unsigned long	SecurityLimitFlags;
/* off 0x00b8 */	void*	Token;
/* off 0x00bc */	struct _PS_JOB_TOKEN_FILTER*	Filter;
/* off 0x00c0 */	unsigned long	EndOfJobTimeAction;
/* off 0x00c4 */	void*	CompletionPort;
/* off 0x00c8 */	void*	CompletionKey;
/* off 0x00cc */	unsigned long	SessionId;
/* off 0x00d0 */	unsigned long	SchedulingClass;
/* off 0x00d8 */	unsigned __int64	ReadOperationCount;
/* off 0x00e0 */	unsigned __int64	WriteOperationCount;
/* off 0x00e8 */	unsigned __int64	OtherOperationCount;
/* off 0x00f0 */	unsigned __int64	ReadTransferCount;
/* off 0x00f8 */	unsigned __int64	WriteTransferCount;
/* off 0x0100 */	unsigned __int64	OtherTransferCount;
/* off 0x0108 */	struct _IO_COUNTERS	IoInfo;
/* off 0x0138 */	unsigned long	ProcessMemoryLimit;
/* off 0x013c */	unsigned long	JobMemoryLimit;
/* off 0x0140 */	unsigned long	PeakProcessMemoryUsed;
/* off 0x0144 */	unsigned long	PeakJobMemoryUsed;
/* off 0x0148 */	unsigned long	CurrentJobMemoryUsed;
/* off 0x014c */	struct _FAST_MUTEX	MemoryLimitsLock;
/* off 0x016c */	struct _LIST_ENTRY	JobSetLinks;
/* off 0x0174 */	unsigned long	MemberLevel;
/* off 0x0178 */	unsigned long	JobFlags;
};
struct _PS_JOB_TOKEN_FILTER /* sizeof 00000024 36 */
{
/* off 0x0000 */	unsigned long	CapturedSidCount;
/* off 0x0004 */	struct _SID_AND_ATTRIBUTES*	CapturedSids;
/* off 0x0008 */	unsigned long	CapturedSidsLength;
/* off 0x000c */	unsigned long	CapturedGroupCount;
/* off 0x0010 */	struct _SID_AND_ATTRIBUTES*	CapturedGroups;
/* off 0x0014 */	unsigned long	CapturedGroupsLength;
/* off 0x0018 */	unsigned long	CapturedPrivilegeCount;
/* off 0x001c */	struct _LUID_AND_ATTRIBUTES*	CapturedPrivileges;
/* off 0x0020 */	unsigned long	CapturedPrivilegesLength;
};
struct _SID_AND_ATTRIBUTES /* sizeof 00000008 8 */
{
/* off 0x0000 */	void*	Sid;
/* off 0x0004 */	unsigned long	Attributes;
};
struct _LUID_AND_ATTRIBUTES /* sizeof 0000000c 12 */
{
/* off 0x0000 */	struct _LUID	Luid;
/* off 0x0008 */	unsigned long	Attributes;
};
struct _EPROCESS_QUOTA_ENTRY /* sizeof 00000010 16 */
{
/* off 0x0000 */	unsigned long	Usage;
/* off 0x0004 */	unsigned long	Limit;
/* off 0x0008 */	unsigned long	Peak;
/* off 0x000c */	unsigned long	Return;
};
struct _EPROCESS_QUOTA_BLOCK /* sizeof 00000040 64 */
{
/* off 0x0000 */	struct _EPROCESS_QUOTA_ENTRY QuotaEntry[3];
/* off 0x0030 */	struct _LIST_ENTRY	QuotaList;
/* off 0x0038 */	unsigned long	ReferenceCount;
/* off 0x003c */	unsigned long	ProcessCount;
};
struct _PROCESS_WS_WATCH_INFORMATION /* sizeof 00000008 8 */
{
/* off 0x0000 */	void*	FaultingPc;
/* off 0x0004 */	void*	FaultingVa;
};
struct _PAGEFAULT_HISTORY /* sizeof 00000018 24 */
{
/* off 0x0000 */	unsigned long	CurrentIndex;
/* off 0x0004 */	unsigned long	MaxIndex;
/* off 0x0008 */	unsigned long	SpinLock;
/* off 0x000c */	void*	Reserved;
/* off 0x0010 */	struct _PROCESS_WS_WATCH_INFORMATION WatchInfo[1];
};
struct _PEB /* sizeof 00000210 528 */
{
/* off 0x0000 */	unsigned char	InheritedAddressSpace;
/* off 0x0001 */	unsigned char	ReadImageFileExecOptions;
/* off 0x0002 */	unsigned char	BeingDebugged;
/* off 0x0003 */	unsigned char	SpareBool;
/* off 0x0004 */	void*	Mutant;
/* off 0x0008 */	void*	ImageBaseAddress;
/* off 0x000c */	struct _PEB_LDR_DATA*	Ldr;
/* off 0x0010 */	struct _RTL_USER_PROCESS_PARAMETERS*	ProcessParameters;
/* off 0x0014 */	void*	SubSystemData;
/* off 0x0018 */	void*	ProcessHeap;
/* off 0x001c */	struct _RTL_CRITICAL_SECTION*	FastPebLock;
/* off 0x0020 */	void*	FastPebLockRoutine;
/* off 0x0024 */	void*	FastPebUnlockRoutine;
/* off 0x0028 */	unsigned long	EnvironmentUpdateCount;
/* off 0x002c */	void*	KernelCallbackTable;
/* off 0x0030 */	unsigned long SystemReserved[1];
/* off 0x0034 */	unsigned long	AtlThunkSListPtr32;
/* off 0x0038 */	struct _PEB_FREE_BLOCK*	FreeList;
/* off 0x003c */	unsigned long	TlsExpansionCounter;
/* off 0x0040 */	void*	TlsBitmap;
/* off 0x0044 */	unsigned long TlsBitmapBits[2];
/* off 0x004c */	void*	ReadOnlySharedMemoryBase;
/* off 0x0050 */	void*	ReadOnlySharedMemoryHeap;
/* off 0x0054 */	void**	ReadOnlyStaticServerData;
/* off 0x0058 */	void*	AnsiCodePageData;
/* off 0x005c */	void*	OemCodePageData;
/* off 0x0060 */	void*	UnicodeCaseTableData;
/* off 0x0064 */	unsigned long	NumberOfProcessors;
/* off 0x0068 */	unsigned long	NtGlobalFlag;
/* off 0x0070 */	union _LARGE_INTEGER	CriticalSectionTimeout;
/* off 0x0078 */	unsigned long	HeapSegmentReserve;
/* off 0x007c */	unsigned long	HeapSegmentCommit;
/* off 0x0080 */	unsigned long	HeapDeCommitTotalFreeThreshold;
/* off 0x0084 */	unsigned long	HeapDeCommitFreeBlockThreshold;
/* off 0x0088 */	unsigned long	NumberOfHeaps;
/* off 0x008c */	unsigned long	MaximumNumberOfHeaps;
/* off 0x0090 */	void**	ProcessHeaps;
/* off 0x0094 */	void*	GdiSharedHandleTable;
/* off 0x0098 */	void*	ProcessStarterHelper;
/* off 0x009c */	unsigned long	GdiDCAttributeList;
/* off 0x00a0 */	void*	LoaderLock;
/* off 0x00a4 */	unsigned long	OSMajorVersion;
/* off 0x00a8 */	unsigned long	OSMinorVersion;
/* off 0x00ac */	unsigned short	OSBuildNumber;
/* off 0x00ae */	unsigned short	OSCSDVersion;
/* off 0x00b0 */	unsigned long	OSPlatformId;
/* off 0x00b4 */	unsigned long	ImageSubsystem;
/* off 0x00b8 */	unsigned long	ImageSubsystemMajorVersion;
/* off 0x00bc */	unsigned long	ImageSubsystemMinorVersion;
/* off 0x00c0 */	unsigned long	ImageProcessAffinityMask;
/* off 0x00c4 */	unsigned long GdiHandleBuffer[34];
/* off 0x014c */	void( __cdecl *PostProcessInitRoutine)();
/* off 0x0150 */	void*	TlsExpansionBitmap;
/* off 0x0154 */	unsigned long TlsExpansionBitmapBits[32];
/* off 0x01d4 */	unsigned long	SessionId;
/* off 0x01d8 */	union _ULARGE_INTEGER	AppCompatFlags;
/* off 0x01e0 */	union _ULARGE_INTEGER	AppCompatFlagsUser;
/* off 0x01e8 */	void*	pShimData;
/* off 0x01ec */	void*	AppCompatInfo;
/* off 0x01f0 */	struct _UNICODE_STRING	CSDVersion;
/* off 0x01f8 */	void*	ActivationContextData;
/* off 0x01fc */	void*	ProcessAssemblyStorageMap;
/* off 0x0200 */	void*	SystemDefaultActivationContextData;
/* off 0x0204 */	void*	SystemAssemblyStorageMap;
/* off 0x0208 */	unsigned long	MinimumStackCommit;
};
struct _PEB_LDR_DATA /* sizeof 00000028 40 */
{
/* off 0x0000 */	unsigned long	Length;
/* off 0x0004 */	unsigned char	Initialized;
/* off 0x0008 */	void*	SsHandle;
/* off 0x000c */	struct _LIST_ENTRY	InLoadOrderModuleList;
/* off 0x0014 */	struct _LIST_ENTRY	InMemoryOrderModuleList;
/* off 0x001c */	struct _LIST_ENTRY	InInitializationOrderModuleList;
/* off 0x0024 */	void*	EntryInProgress;
};
struct _CURDIR /* sizeof 0000000c 12 */
{
/* off 0x0000 */	struct _UNICODE_STRING	DosPath;
/* off 0x0008 */	void*	Handle;
};
struct _STRING /* sizeof 00000008 8 */
{
/* off 0x0000 */	unsigned short	Length;
/* off 0x0002 */	unsigned short	MaximumLength;
/* off 0x0004 */	char*	Buffer;
};
struct _RTL_DRIVE_LETTER_CURDIR /* sizeof 00000010 16 */
{
/* off 0x0000 */	unsigned short	Flags;
/* off 0x0002 */	unsigned short	Length;
/* off 0x0004 */	unsigned long	TimeStamp;
/* off 0x0008 */	struct _STRING	DosPath;
};
struct _RTL_USER_PROCESS_PARAMETERS /* sizeof 00000290 656 */
{
/* off 0x0000 */	unsigned long	MaximumLength;
/* off 0x0004 */	unsigned long	Length;
/* off 0x0008 */	unsigned long	Flags;
/* off 0x000c */	unsigned long	DebugFlags;
/* off 0x0010 */	void*	ConsoleHandle;
/* off 0x0014 */	unsigned long	ConsoleFlags;
/* off 0x0018 */	void*	StandardInput;
/* off 0x001c */	void*	StandardOutput;
/* off 0x0020 */	void*	StandardError;
/* off 0x0024 */	struct _CURDIR	CurrentDirectory;
/* off 0x0030 */	struct _UNICODE_STRING	DllPath;
/* off 0x0038 */	struct _UNICODE_STRING	ImagePathName;
/* off 0x0040 */	struct _UNICODE_STRING	CommandLine;
/* off 0x0048 */	void*	Environment;
/* off 0x004c */	unsigned long	StartingX;
/* off 0x0050 */	unsigned long	StartingY;
/* off 0x0054 */	unsigned long	CountX;
/* off 0x0058 */	unsigned long	CountY;
/* off 0x005c */	unsigned long	CountCharsX;
/* off 0x0060 */	unsigned long	CountCharsY;
/* off 0x0064 */	unsigned long	FillAttribute;
/* off 0x0068 */	unsigned long	WindowFlags;
/* off 0x006c */	unsigned long	ShowWindowFlags;
/* off 0x0070 */	struct _UNICODE_STRING	WindowTitle;
/* off 0x0078 */	struct _UNICODE_STRING	DesktopInfo;
/* off 0x0080 */	struct _UNICODE_STRING	ShellInfo;
/* off 0x0088 */	struct _UNICODE_STRING	RuntimeData;
/* off 0x0090 */	struct _RTL_DRIVE_LETTER_CURDIR CurrentDirectores[32];
};
struct _RTL_CRITICAL_SECTION /* sizeof 00000018 24 */
{
/* off 0x0000 */	struct _RTL_CRITICAL_SECTION_DEBUG*	DebugInfo;
/* off 0x0004 */	long	LockCount;
/* off 0x0008 */	long	RecursionCount;
/* off 0x000c */	void*	OwningThread;
/* off 0x0010 */	void*	LockSemaphore;
/* off 0x0014 */	unsigned long	SpinCount;
};
struct _RTL_CRITICAL_SECTION_DEBUG /* sizeof 00000020 32 */
{
/* off 0x0000 */	unsigned short	Type;
/* off 0x0002 */	unsigned short	CreatorBackTraceIndex;
/* off 0x0004 */	struct _RTL_CRITICAL_SECTION*	CriticalSection;
/* off 0x0008 */	struct _LIST_ENTRY	ProcessLocksList;
/* off 0x0010 */	unsigned long	EntryCount;
/* off 0x0014 */	unsigned long	ContentionCount;
/* off 0x0018 */	unsigned long Spare[2];
};
struct _PEB_FREE_BLOCK /* sizeof 00000008 8 */
{
/* off 0x0000 */	struct _PEB_FREE_BLOCK*	Next;
/* off 0x0004 */	unsigned long	Size;
};
struct _OBJECT_NAME_INFORMATION /* sizeof 00000008 8 */
{
/* off 0x0000 */	struct _UNICODE_STRING	Name;
};
struct _MMWSL /* sizeof 0000069c 1692 */
{
/* off 0x0000 */	unsigned long	Quota;
/* off 0x0004 */	unsigned long	FirstFree;
/* off 0x0008 */	unsigned long	FirstDynamic;
/* off 0x000c */	unsigned long	LastEntry;
/* off 0x0010 */	unsigned long	NextSlot;
/* off 0x0014 */	struct _MMWSLE*	Wsle;
/* off 0x0018 */	unsigned long	LastInitializedWsle;
/* off 0x001c */	unsigned long	NonDirectCount;
/* off 0x0020 */	struct _MMWSLE_HASH*	HashTable;
/* off 0x0024 */	unsigned long	HashTableSize;
/* off 0x0028 */	unsigned long	NumberOfCommittedPageTables;
/* off 0x002c */	void*	HashTableStart;
/* off 0x0030 */	void*	HighestPermittedHashAddress;
/* off 0x0034 */	unsigned long	NumberOfImageWaiters;
/* off 0x0038 */	unsigned long	VadBitMapHint;
/* off 0x003c */	unsigned short UsedPageTableEntries[768];
/* off 0x063c */	unsigned long CommittedPageTables[24];
};
struct _MMWSLE /* sizeof 00000004 4 */
{
/* off 0x0000 */	struct __unnamed	u1;
};
struct _MMWSLE_HASH /* sizeof 00000008 8 */
{
/* off 0x0000 */	void*	Key;
/* off 0x0004 */	unsigned long	Index;
};
struct _FILE_NETWORK_OPEN_INFORMATION /* sizeof 00000038 56 */
{
/* off 0x0000 */	union _LARGE_INTEGER	CreationTime;
/* off 0x0008 */	union _LARGE_INTEGER	LastAccessTime;
/* off 0x0010 */	union _LARGE_INTEGER	LastWriteTime;
/* off 0x0018 */	union _LARGE_INTEGER	ChangeTime;
/* off 0x0020 */	union _LARGE_INTEGER	AllocationSize;
/* off 0x0028 */	union _LARGE_INTEGER	EndOfFile;
/* off 0x0030 */	unsigned long	FileAttributes;
};
struct _MDL /* sizeof 0000001c 28 */
{
/* off 0x0000 */	struct _MDL*	Next;
/* off 0x0004 */	short	Size;
/* off 0x0006 */	short	MdlFlags;
/* off 0x0008 */	struct _EPROCESS*	Process;
/* off 0x000c */	void*	MappedSystemVa;
/* off 0x0010 */	void*	StartVa;
/* off 0x0014 */	unsigned long	ByteCount;
/* off 0x0018 */	unsigned long	ByteOffset;
};
struct _COMPRESSED_DATA_INFO /* sizeof 0000000c 12 */
{
/* off 0x0000 */	unsigned short	CompressionFormatAndEngine;
/* off 0x0002 */	unsigned char	CompressionUnitShift;
/* off 0x0003 */	unsigned char	ChunkShift;
/* off 0x0004 */	unsigned char	ClusterShift;
/* off 0x0005 */	unsigned char	Reserved;
/* off 0x0006 */	unsigned short	NumberOfChunks;
/* off 0x0008 */	unsigned long CompressedChunkSizes[1];
};
struct _IRP /* sizeof 00000070 112 */
{
/* off 0x0000 */	short	Type;
/* off 0x0002 */	unsigned short	Size;
/* off 0x0004 */	struct _MDL*	MdlAddress;
/* off 0x0008 */	unsigned long	Flags;
/* off 0x000c */	struct __unnamed	AssociatedIrp;
/* off 0x0010 */	struct _LIST_ENTRY	ThreadListEntry;
/* off 0x0018 */	struct _IO_STATUS_BLOCK	IoStatus;
/* off 0x0020 */	char	RequestorMode;
/* off 0x0021 */	unsigned char	PendingReturned;
/* off 0x0022 */	char	StackCount;
/* off 0x0023 */	char	CurrentLocation;
/* off 0x0024 */	unsigned char	Cancel;
/* off 0x0025 */	unsigned char	CancelIrql;
/* off 0x0026 */	char	ApcEnvironment;
/* off 0x0027 */	unsigned char	AllocationFlags;
/* off 0x0028 */	struct _IO_STATUS_BLOCK*	UserIosb;
/* off 0x002c */	struct _KEVENT*	UserEvent;
/* off 0x0030 */	struct __unnamed	Overlay;
/* off 0x0038 */	void( __cdecl *CancelRoutine)(struct _DEVICE_OBJECT*,struct _IRP*);
/* off 0x003c */	void*	UserBuffer;
/* off 0x0040 */	struct __unnamed	Tail;
};
struct _IO_TIMER /* sizeof 00000018 24 */
{
/* off 0x0000 */	short	Type;
/* off 0x0002 */	short	TimerFlag;
/* off 0x0004 */	struct _LIST_ENTRY	TimerList;
/* off 0x000c */	void( __cdecl *TimerRoutine)(struct _DEVICE_OBJECT*,void*);
/* off 0x0010 */	void*	Context;
/* off 0x0014 */	struct _DEVICE_OBJECT*	DeviceObject;
};
struct _DEVOBJ_EXTENSION /* sizeof 0000002c 44 */
{
/* off 0x0000 */	short	Type;
/* off 0x0002 */	unsigned short	Size;
/* off 0x0004 */	struct _DEVICE_OBJECT*	DeviceObject;
/* off 0x0008 */	unsigned long	PowerFlags;
/* off 0x000c */	struct _DEVICE_OBJECT_POWER_EXTENSION*	Dope;
/* off 0x0010 */	unsigned long	ExtensionFlags;
/* off 0x0014 */	void*	DeviceNode;
/* off 0x0018 */	struct _DEVICE_OBJECT*	AttachedTo;
/* off 0x001c */	long	StartIoCount;
/* off 0x0020 */	long	StartIoKey;
/* off 0x0024 */	unsigned long	StartIoFlags;
/* off 0x0028 */	struct _VPB*	Vpb;
};
struct _POWER_CHANNEL_SUMMARY /* sizeof 00000014 20 */
{
/* off 0x0000 */	unsigned long	Signature;
/* off 0x0004 */	unsigned long	TotalCount;
/* off 0x0008 */	unsigned long	D0Count;
/* off 0x000c */	struct _LIST_ENTRY	NotifyList;
};
struct _DEVICE_OBJECT_POWER_EXTENSION /* sizeof 0000004c 76 */
{
/* off 0x0000 */	unsigned long	IdleCount;
/* off 0x0004 */	unsigned long	ConservationIdleTime;
/* off 0x0008 */	unsigned long	PerformanceIdleTime;
/* off 0x000c */	struct _DEVICE_OBJECT*	DeviceObject;
/* off 0x0010 */	struct _LIST_ENTRY	IdleList;
/* off 0x0018 */	unsigned char	DeviceType;
/* off 0x001c */	enum _DEVICE_POWER_STATE	State;
/* off 0x0020 */	struct _LIST_ENTRY	NotifySourceList;
/* off 0x0028 */	struct _LIST_ENTRY	NotifyTargetList;
/* off 0x0030 */	struct _POWER_CHANNEL_SUMMARY	PowerChannelSummary;
/* off 0x0044 */	struct _LIST_ENTRY	Volume;
};
enum _DEVICE_POWER_STATE
{
	PowerDeviceUnspecified	=0x00000000	,//0
	PowerDeviceD0	=0x00000001	,//0
	PowerDeviceD1	=0x00000002	,//0
	PowerDeviceD2	=0x00000003	,//0
	PowerDeviceD3	=0x00000004	,//0
	PowerDeviceMaximum	=0x00000005	,//0
};
struct _OBJECT_ATTRIBUTES /* sizeof 00000018 24 */
{
/* off 0x0000 */	unsigned long	Length;
/* off 0x0004 */	void*	RootDirectory;
/* off 0x0008 */	struct _UNICODE_STRING*	ObjectName;
/* off 0x000c */	unsigned long	Attributes;
/* off 0x0010 */	void*	SecurityDescriptor;
/* off 0x0014 */	void*	SecurityQualityOfService;
};
struct _GENERIC_MAPPING /* sizeof 00000010 16 */
{
/* off 0x0000 */	unsigned long	GenericRead;
/* off 0x0004 */	unsigned long	GenericWrite;
/* off 0x0008 */	unsigned long	GenericExecute;
/* off 0x000c */	unsigned long	GenericAll;
};
struct _OBJECT_TYPE_INITIALIZER /* sizeof 0000004c 76 */
{
/* off 0x0000 */	unsigned short	Length;
/* off 0x0002 */	unsigned char	UseDefaultObject;
/* off 0x0003 */	unsigned char	CaseInsensitive;
/* off 0x0004 */	unsigned long	InvalidAttributes;
/* off 0x0008 */	struct _GENERIC_MAPPING	GenericMapping;
/* off 0x0018 */	unsigned long	ValidAccessMask;
/* off 0x001c */	unsigned char	SecurityRequired;
/* off 0x001d */	unsigned char	MaintainHandleCount;
/* off 0x001e */	unsigned char	MaintainTypeList;
/* off 0x0020 */	enum _POOL_TYPE	PoolType;
/* off 0x0024 */	unsigned long	DefaultPagedPoolCharge;
/* off 0x0028 */	unsigned long	DefaultNonPagedPoolCharge;
/* off 0x002c */	void( __cdecl *DumpProcedure)(void*,struct _OBJECT_DUMP_CONTROL*);
/* off 0x0030 */	long( __cdecl *OpenProcedure)(enum _OB_OPEN_REASON,struct _EPROCESS*,void*,unsigned long,unsigned long);
/* off 0x0034 */	void( __cdecl *CloseProcedure)(struct _EPROCESS*,void*,unsigned long,unsigned long,unsigned long);
/* off 0x0038 */	void( __cdecl *DeleteProcedure)(void*);
/* off 0x003c */	long( __cdecl *ParseProcedure)(void*,void*,struct _ACCESS_STATE*,char,unsigned long,struct _UNICODE_STRING*,struct _UNICODE_STRING*,void*,struct _SECURITY_QUALITY_OF_SERVICE*,void**);
/* off 0x0040 */	long( __cdecl *SecurityProcedure)(void*,enum _SECURITY_OPERATION_CODE,unsigned long*,void*,unsigned long*,void**,enum _POOL_TYPE,struct _GENERIC_MAPPING*);
/* off 0x0044 */	long( __cdecl *QueryNameProcedure)(void*,unsigned char,struct _OBJECT_NAME_INFORMATION*,unsigned long,unsigned long*);
/* off 0x0048 */	unsigned char( __cdecl *OkayToCloseProcedure)(struct _EPROCESS*,void*,void*,char);
};
struct _OBJECT_TYPE /* sizeof 00000190 400 */
{
/* off 0x0000 */	struct _ERESOURCE	Mutex;
/* off 0x0038 */	struct _LIST_ENTRY	TypeList;
/* off 0x0040 */	struct _UNICODE_STRING	Name;
/* off 0x0048 */	void*	DefaultObject;
/* off 0x004c */	unsigned long	Index;
/* off 0x0050 */	unsigned long	TotalNumberOfObjects;
/* off 0x0054 */	unsigned long	TotalNumberOfHandles;
/* off 0x0058 */	unsigned long	HighWaterNumberOfObjects;
/* off 0x005c */	unsigned long	HighWaterNumberOfHandles;
/* off 0x0060 */	struct _OBJECT_TYPE_INITIALIZER	TypeInfo;
/* off 0x00ac */	unsigned long	Key;
/* off 0x00b0 */	struct _ERESOURCE ObjectLocks[4];
};
struct _OBJECT_DUMP_CONTROL /* sizeof 00000008 8 */
{
/* off 0x0000 */	void*	Stream;
/* off 0x0004 */	unsigned long	Detail;
};
enum _OB_OPEN_REASON
{
	ObCreateHandle	=0x00000000	,//0
	ObOpenHandle	=0x00000001	,//0
	ObDuplicateHandle	=0x00000002	,//0
	ObInheritHandle	=0x00000003	,//0
	ObMaxOpenReason	=0x00000004	,//0
};
struct _SECURITY_SUBJECT_CONTEXT /* sizeof 00000010 16 */
{
/* off 0x0000 */	void*	ClientToken;
/* off 0x0004 */	enum _SECURITY_IMPERSONATION_LEVEL	ImpersonationLevel;
/* off 0x0008 */	void*	PrimaryToken;
/* off 0x000c */	void*	ProcessAuditId;
};
struct _ACCESS_STATE /* sizeof 00000074 116 */
{
/* off 0x0000 */	struct _LUID	OperationID;
/* off 0x0008 */	unsigned char	SecurityEvaluated;
/* off 0x0009 */	unsigned char	GenerateAudit;
/* off 0x000a */	unsigned char	GenerateOnClose;
/* off 0x000b */	unsigned char	PrivilegesAllocated;
/* off 0x000c */	unsigned long	Flags;
/* off 0x0010 */	unsigned long	RemainingDesiredAccess;
/* off 0x0014 */	unsigned long	PreviouslyGrantedAccess;
/* off 0x0018 */	unsigned long	OriginalDesiredAccess;
/* off 0x001c */	struct _SECURITY_SUBJECT_CONTEXT	SubjectSecurityContext;
/* off 0x002c */	void*	SecurityDescriptor;
/* off 0x0030 */	void*	AuxData;
/* off 0x0034 */	struct __unnamed	Privileges;
/* off 0x0060 */	unsigned char	AuditPrivileges;
/* off 0x0064 */	struct _UNICODE_STRING	ObjectName;
/* off 0x006c */	struct _UNICODE_STRING	ObjectTypeName;
};
struct _SECURITY_QUALITY_OF_SERVICE /* sizeof 0000000c 12 */
{
/* off 0x0000 */	unsigned long	Length;
/* off 0x0004 */	enum _SECURITY_IMPERSONATION_LEVEL	ImpersonationLevel;
/* off 0x0008 */	unsigned char	ContextTrackingMode;
/* off 0x0009 */	unsigned char	EffectiveOnly;
};
enum _SECURITY_OPERATION_CODE
{
	SetSecurityDescriptor	=0x00000000	,//0
	QuerySecurityDescriptor	=0x00000001	,//0
	DeleteSecurityDescriptor	=0x00000002	,//0
	AssignSecurityDescriptor	=0x00000003	,//0
};
struct _OBJECT_HANDLE_INFORMATION /* sizeof 00000008 8 */
{
/* off 0x0000 */	unsigned long	HandleAttributes;
/* off 0x0004 */	unsigned long	GrantedAccess;
};
struct _FNSAVE_FORMAT /* sizeof 0000006c 108 */
{
/* off 0x0000 */	unsigned long	ControlWord;
/* off 0x0004 */	unsigned long	StatusWord;
/* off 0x0008 */	unsigned long	TagWord;
/* off 0x000c */	unsigned long	ErrorOffset;
/* off 0x0010 */	unsigned long	ErrorSelector;
/* off 0x0014 */	unsigned long	DataOffset;
/* off 0x0018 */	unsigned long	DataSelector;
/* off 0x001c */	unsigned char RegisterArea[80];
};
struct _FXSAVE_FORMAT /* sizeof 00000208 520 */
{
/* off 0x0000 */	unsigned short	ControlWord;
/* off 0x0002 */	unsigned short	StatusWord;
/* off 0x0004 */	unsigned short	TagWord;
/* off 0x0006 */	unsigned short	ErrorOpcode;
/* off 0x0008 */	unsigned long	ErrorOffset;
/* off 0x000c */	unsigned long	ErrorSelector;
/* off 0x0010 */	unsigned long	DataOffset;
/* off 0x0014 */	unsigned long	DataSelector;
/* off 0x0018 */	unsigned long	MXCsr;
/* off 0x001c */	unsigned long	MXCsrMask;
/* off 0x0020 */	unsigned char RegisterArea[128];
/* off 0x00a0 */	unsigned char Reserved3[128];
/* off 0x0120 */	unsigned char Reserved4[224];
/* off 0x0200 */	unsigned char Align16Byte[8];
};
enum _MEMORY_CACHING_TYPE
{
	MmNonCached	=0x00000000	,//0
	MmCached	=0x00000001	,//0
	MmWriteCombined	=0x00000002	,//0
	MmHardwareCoherentCached	=0x00000003	,//0
	MmNonCachedUnordered	=0x00000004	,//0
	MmUSWCCached	=0x00000005	,//0
	MmMaximumCacheType	=0x00000006	,//0
};
enum _MI_PFN_CACHE_ATTRIBUTE
{
	MiNonCached	=0x00000000	,//0
	MiCached	=0x00000001	,//0
	MiWriteCombined	=0x00000002	,//0
	MiNotMapped	=0x00000003	,//0
};
struct _EXCEPTION_RECORD64 /* sizeof 00000098 152 */
{
/* off 0x0000 */	long	ExceptionCode;
/* off 0x0004 */	unsigned long	ExceptionFlags;
/* off 0x0008 */	unsigned __int64	ExceptionRecord;
/* off 0x0010 */	unsigned __int64	ExceptionAddress;
/* off 0x0018 */	unsigned long	NumberParameters;
/* off 0x001c */	unsigned long	__unusedAlignment;
/* off 0x0020 */	unsigned __int64 ExceptionInformation[15];
};
struct _EXCEPTION_RECORD32 /* sizeof 00000050 80 */
{
/* off 0x0000 */	long	ExceptionCode;
/* off 0x0004 */	unsigned long	ExceptionFlags;
/* off 0x0008 */	unsigned long	ExceptionRecord;
/* off 0x000c */	unsigned long	ExceptionAddress;
/* off 0x0010 */	unsigned long	NumberParameters;
/* off 0x0014 */	unsigned long ExceptionInformation[15];
};
struct _DBGKM_EXCEPTION64 /* sizeof 000000a0 160 */
{
/* off 0x0000 */	struct _EXCEPTION_RECORD64	ExceptionRecord;
/* off 0x0098 */	unsigned long	FirstChance;
};
struct _DBGKM_EXCEPTION32 /* sizeof 00000054 84 */
{
/* off 0x0000 */	struct _EXCEPTION_RECORD32	ExceptionRecord;
/* off 0x0050 */	unsigned long	FirstChance;
};
struct _DBGKD_LOAD_SYMBOLS64 /* sizeof 00000028 40 */
{
/* off 0x0000 */	unsigned long	PathNameLength;
/* off 0x0008 */	unsigned __int64	BaseOfDll;
/* off 0x0010 */	unsigned __int64	ProcessId;
/* off 0x0018 */	unsigned long	CheckSum;
/* off 0x001c */	unsigned long	SizeOfImage;
/* off 0x0020 */	unsigned char	UnloadSymbols;
};
struct _DBGKD_LOAD_SYMBOLS32 /* sizeof 00000018 24 */
{
/* off 0x0000 */	unsigned long	PathNameLength;
/* off 0x0004 */	unsigned long	BaseOfDll;
/* off 0x0008 */	unsigned long	ProcessId;
/* off 0x000c */	unsigned long	CheckSum;
/* off 0x0010 */	unsigned long	SizeOfImage;
/* off 0x0014 */	unsigned char	UnloadSymbols;
};
struct _DBGKD_READ_MEMORY64 /* sizeof 00000010 16 */
{
/* off 0x0000 */	unsigned __int64	TargetBaseAddress;
/* off 0x0008 */	unsigned long	TransferCount;
/* off 0x000c */	unsigned long	ActualBytesRead;
};
struct _DBGKD_READ_MEMORY32 /* sizeof 0000000c 12 */
{
/* off 0x0000 */	unsigned long	TargetBaseAddress;
/* off 0x0004 */	unsigned long	TransferCount;
/* off 0x0008 */	unsigned long	ActualBytesRead;
};
struct _DBGKD_WRITE_MEMORY64 /* sizeof 00000010 16 */
{
/* off 0x0000 */	unsigned __int64	TargetBaseAddress;
/* off 0x0008 */	unsigned long	TransferCount;
/* off 0x000c */	unsigned long	ActualBytesWritten;
};
struct _DBGKD_WRITE_MEMORY32 /* sizeof 0000000c 12 */
{
/* off 0x0000 */	unsigned long	TargetBaseAddress;
/* off 0x0004 */	unsigned long	TransferCount;
/* off 0x0008 */	unsigned long	ActualBytesWritten;
};
struct _DBGKD_WRITE_BREAKPOINT64 /* sizeof 00000010 16 */
{
/* off 0x0000 */	unsigned __int64	BreakPointAddress;
/* off 0x0008 */	unsigned long	BreakPointHandle;
};
struct _DBGKD_WRITE_BREAKPOINT32 /* sizeof 00000008 8 */
{
/* off 0x0000 */	unsigned long	BreakPointAddress;
/* off 0x0004 */	unsigned long	BreakPointHandle;
};
struct _DBGKD_READ_WRITE_IO64 /* sizeof 00000010 16 */
{
/* off 0x0000 */	unsigned __int64	IoAddress;
/* off 0x0008 */	unsigned long	DataSize;
/* off 0x000c */	unsigned long	DataValue;
};
struct _DBGKD_READ_WRITE_IO32 /* sizeof 0000000c 12 */
{
/* off 0x0000 */	unsigned long	DataSize;
/* off 0x0004 */	unsigned long	IoAddress;
/* off 0x0008 */	unsigned long	DataValue;
};
struct _DBGKD_READ_WRITE_IO_EXTENDED64 /* sizeof 00000020 32 */
{
/* off 0x0000 */	unsigned long	DataSize;
/* off 0x0004 */	unsigned long	InterfaceType;
/* off 0x0008 */	unsigned long	BusNumber;
/* off 0x000c */	unsigned long	AddressSpace;
/* off 0x0010 */	unsigned __int64	IoAddress;
/* off 0x0018 */	unsigned long	DataValue;
};
struct _DBGKD_READ_WRITE_IO_EXTENDED32 /* sizeof 00000018 24 */
{
/* off 0x0000 */	unsigned long	DataSize;
/* off 0x0004 */	unsigned long	InterfaceType;
/* off 0x0008 */	unsigned long	BusNumber;
/* off 0x000c */	unsigned long	AddressSpace;
/* off 0x0010 */	unsigned long	IoAddress;
/* off 0x0014 */	unsigned long	DataValue;
};
struct _DBGKD_SET_SPECIAL_CALL32 /* sizeof 00000004 4 */
{
/* off 0x0000 */	unsigned long	SpecialCall;
};
struct _DBGKD_SET_SPECIAL_CALL64 /* sizeof 00000008 8 */
{
/* off 0x0000 */	unsigned __int64	SpecialCall;
};
struct _DBGKD_SET_INTERNAL_BREAKPOINT32 /* sizeof 00000008 8 */
{
/* off 0x0000 */	unsigned long	BreakpointAddress;
/* off 0x0004 */	unsigned long	Flags;
};
struct _DBGKD_SET_INTERNAL_BREAKPOINT64 /* sizeof 00000010 16 */
{
/* off 0x0000 */	unsigned __int64	BreakpointAddress;
/* off 0x0008 */	unsigned long	Flags;
};
struct _DBGKD_GET_INTERNAL_BREAKPOINT64 /* sizeof 00000020 32 */
{
/* off 0x0000 */	unsigned __int64	BreakpointAddress;
/* off 0x0008 */	unsigned long	Flags;
/* off 0x000c */	unsigned long	Calls;
/* off 0x0010 */	unsigned long	MaxCallsPerPeriod;
/* off 0x0014 */	unsigned long	MinInstructions;
/* off 0x0018 */	unsigned long	MaxInstructions;
/* off 0x001c */	unsigned long	TotalInstructions;
};
struct _DBGKD_GET_INTERNAL_BREAKPOINT32 /* sizeof 0000001c 28 */
{
/* off 0x0000 */	unsigned long	BreakpointAddress;
/* off 0x0004 */	unsigned long	Flags;
/* off 0x0008 */	unsigned long	Calls;
/* off 0x000c */	unsigned long	MaxCallsPerPeriod;
/* off 0x0010 */	unsigned long	MinInstructions;
/* off 0x0014 */	unsigned long	MaxInstructions;
/* off 0x0018 */	unsigned long	TotalInstructions;
};
struct _DBGKD_MANIPULATE_STATE64 /* sizeof 00000038 56 */
{
/* off 0x0000 */	unsigned long	ApiNumber;
/* off 0x0004 */	unsigned short	ProcessorLevel;
/* off 0x0006 */	unsigned short	Processor;
/* off 0x0008 */	long	ReturnStatus;
/* off 0x0010 */	struct __unnamed	u;
};
struct _DBGKD_GET_CONTEXT /* sizeof 00000004 4 */
{
/* off 0x0000 */	unsigned long	Unused;
};
struct _DBGKD_SET_CONTEXT /* sizeof 00000004 4 */
{
/* off 0x0000 */	unsigned long	ContextFlags;
};
struct _DBGKD_RESTORE_BREAKPOINT /* sizeof 00000004 4 */
{
/* off 0x0000 */	unsigned long	BreakPointHandle;
};
struct _DBGKD_CONTINUE /* sizeof 00000004 4 */
{
/* off 0x0000 */	long	ContinueStatus;
};
struct _X86_DBGKD_CONTROL_SET /* sizeof 00000010 16 */
{
/* off 0x0000 */	unsigned long	TraceFlag;
/* off 0x0004 */	unsigned long	Dr7;
/* off 0x0008 */	unsigned long	CurrentSymbolStart;
/* off 0x000c */	unsigned long	CurrentSymbolEnd;
};
struct _IA64_DBGKD_CONTROL_SET /* sizeof 00000014 20 */
{
/* off 0x0000 */	unsigned long	Continue;
/* off 0x0004 */	unsigned __int64	CurrentSymbolStart;
/* off 0x000c */	unsigned __int64	CurrentSymbolEnd;
};
struct _AMD64_DBGKD_CONTROL_SET /* sizeof 0000001c 28 */
{
/* off 0x0000 */	unsigned long	TraceFlag;
/* off 0x0004 */	unsigned __int64	Dr7;
/* off 0x000c */	unsigned __int64	CurrentSymbolStart;
/* off 0x0014 */	unsigned __int64	CurrentSymbolEnd;
};
struct _DBGKD_ANY_CONTROL_SET /* sizeof 0000001c 28 */
{
union
{
/* off 0x0000 */	struct _X86_DBGKD_CONTROL_SET	X86ControlSet;
/* off 0x0000 */	unsigned long	AlphaControlSet;
/* off 0x0000 */	struct _IA64_DBGKD_CONTROL_SET	IA64ControlSet;
/* off 0x0000 */	struct _AMD64_DBGKD_CONTROL_SET	Amd64ControlSet;
};
};
struct _DBGKD_CONTINUE2 /* sizeof 00000020 32 */
{
/* off 0x0000 */	long	ContinueStatus;
union
{
/* off 0x0004 */	struct _X86_DBGKD_CONTROL_SET	ControlSet;
/* off 0x0004 */	struct _DBGKD_ANY_CONTROL_SET	AnyControlSet;
};
};
struct _DBGKD_QUERY_SPECIAL_CALLS /* sizeof 00000004 4 */
{
/* off 0x0000 */	unsigned long	NumberOfSpecialCalls;
};
struct _DBGKD_GET_VERSION64 /* sizeof 00000028 40 */
{
/* off 0x0000 */	unsigned short	MajorVersion;
/* off 0x0002 */	unsigned short	MinorVersion;
/* off 0x0004 */	unsigned short	ProtocolVersion;
/* off 0x0006 */	unsigned short	Flags;
/* off 0x0008 */	unsigned short	MachineType;
/* off 0x000a */	unsigned char	MaxPacketType;
/* off 0x000b */	unsigned char	MaxStateChange;
/* off 0x000c */	unsigned char	MaxManipulate;
/* off 0x000d */	unsigned char	Simulation;
/* off 0x000e */	unsigned short Unused[1];
/* off 0x0010 */	unsigned __int64	KernBase;
/* off 0x0018 */	unsigned __int64	PsLoadedModuleList;
/* off 0x0020 */	unsigned __int64	DebuggerDataList;
};
struct _DBGKD_BREAKPOINTEX /* sizeof 00000008 8 */
{
/* off 0x0000 */	unsigned long	BreakPointCount;
/* off 0x0004 */	long	ContinueStatus;
};
struct _DBGKD_READ_WRITE_MSR /* sizeof 0000000c 12 */
{
/* off 0x0000 */	unsigned long	Msr;
/* off 0x0004 */	unsigned long	DataValueLow;
/* off 0x0008 */	unsigned long	DataValueHigh;
};
struct _DBGKD_SEARCH_MEMORY /* sizeof 00000018 24 */
{
union
{
/* off 0x0000 */	unsigned __int64	SearchAddress;
/* off 0x0000 */	unsigned __int64	FoundAddress;
};
/* off 0x0008 */	unsigned __int64	SearchLength;
/* off 0x0010 */	unsigned long	PatternLength;
};
struct _DBGKD_GET_SET_BUS_DATA /* sizeof 00000014 20 */
{
/* off 0x0000 */	unsigned long	BusDataType;
/* off 0x0004 */	unsigned long	BusNumber;
/* off 0x0008 */	unsigned long	SlotNumber;
/* off 0x000c */	unsigned long	Offset;
/* off 0x0010 */	unsigned long	Length;
};
struct _DBGKD_FILL_MEMORY /* sizeof 00000010 16 */
{
/* off 0x0000 */	unsigned __int64	Address;
/* off 0x0008 */	unsigned long	Length;
/* off 0x000c */	unsigned short	Flags;
/* off 0x000e */	unsigned short	PatternLength;
};
struct _DBGKD_QUERY_MEMORY /* sizeof 00000018 24 */
{
/* off 0x0000 */	unsigned __int64	Address;
/* off 0x0008 */	unsigned __int64	Reserved;
/* off 0x0010 */	unsigned long	AddressSpace;
/* off 0x0014 */	unsigned long	Flags;
};
struct _DBGKD_MANIPULATE_STATE32 /* sizeof 00000034 52 */
{
/* off 0x0000 */	unsigned long	ApiNumber;
/* off 0x0004 */	unsigned short	ProcessorLevel;
/* off 0x0006 */	unsigned short	Processor;
/* off 0x0008 */	long	ReturnStatus;
/* off 0x000c */	struct __unnamed	u;
};
struct _DBGKD_GET_VERSION32 /* sizeof 00000028 40 */
{
/* off 0x0000 */	unsigned short	MajorVersion;
/* off 0x0002 */	unsigned short	MinorVersion;
/* off 0x0004 */	unsigned short	ProtocolVersion;
/* off 0x0006 */	unsigned short	Flags;
/* off 0x0008 */	unsigned long	KernBase;
/* off 0x000c */	unsigned long	PsLoadedModuleList;
/* off 0x0010 */	unsigned short	MachineType;
/* off 0x0012 */	unsigned short	ThCallbackStack;
/* off 0x0014 */	unsigned short	NextCallback;
/* off 0x0016 */	unsigned short	FramePointer;
/* off 0x0018 */	unsigned long	KiCallUserMode;
/* off 0x001c */	unsigned long	KeUserCallbackDispatcher;
/* off 0x0020 */	unsigned long	BreakpointWithStatus;
/* off 0x0024 */	unsigned long	DebuggerDataList;
};
struct _VACB /* sizeof 00000018 24 */
{
/* off 0x0000 */	void*	BaseAddress;
/* off 0x0004 */	struct _SHARED_CACHE_MAP*	SharedCacheMap;
/* off 0x0008 */	struct __unnamed	Overlay;
/* off 0x0010 */	struct _LIST_ENTRY	LruList;
};
struct _PRIVATE_CACHE_MAP_FLAGS /* sizeof 00000004 4 */
{
/* off 0x0000 */	unsigned long	DontUse:16	 /* start bit 0 */;
/* off 0x0000 */	unsigned long	ReadAheadActive:1	 /* start bit 16 */;
/* off 0x0000 */	unsigned long	ReadAheadEnabled:1	 /* start bit 17 */;
/* off 0x0000 */	unsigned long	Available:14	 /* start bit 18 */;
};
struct _PRIVATE_CACHE_MAP /* sizeof 00000058 88 */
{
union
{
/* off 0x0000 */	short	NodeTypeCode;
/* off 0x0000 */	struct _PRIVATE_CACHE_MAP_FLAGS	Flags;
/* off 0x0000 */	unsigned long	UlongFlags;
};
/* off 0x0004 */	unsigned long	ReadAheadMask;
/* off 0x0008 */	struct _FILE_OBJECT*	FileObject;
/* off 0x0010 */	union _LARGE_INTEGER	FileOffset1;
/* off 0x0018 */	union _LARGE_INTEGER	BeyondLastByte1;
/* off 0x0020 */	union _LARGE_INTEGER	FileOffset2;
/* off 0x0028 */	union _LARGE_INTEGER	BeyondLastByte2;
/* off 0x0030 */	union _LARGE_INTEGER ReadAheadOffset[2];
/* off 0x0040 */	unsigned long ReadAheadLength[2];
/* off 0x0048 */	unsigned long	ReadAheadSpinLock;
/* off 0x004c */	struct _LIST_ENTRY	PrivateLinks;
};
struct _SHARED_CACHE_MAP /* sizeof 00000130 304 */
{
/* off 0x0000 */	short	NodeTypeCode;
/* off 0x0002 */	short	NodeByteSize;
/* off 0x0004 */	unsigned long	OpenCount;
/* off 0x0008 */	union _LARGE_INTEGER	FileSize;
/* off 0x0010 */	struct _LIST_ENTRY	BcbList;
/* off 0x0018 */	union _LARGE_INTEGER	SectionSize;
/* off 0x0020 */	union _LARGE_INTEGER	ValidDataLength;
/* off 0x0028 */	union _LARGE_INTEGER	ValidDataGoal;
/* off 0x0030 */	struct _VACB* InitialVacbs[4];
/* off 0x0040 */	struct _VACB**	Vacbs;
/* off 0x0044 */	struct _FILE_OBJECT*	FileObject;
/* off 0x0048 */	struct _VACB*	ActiveVacb;
/* off 0x004c */	void*	NeedToZero;
/* off 0x0050 */	unsigned long	ActivePage;
/* off 0x0054 */	unsigned long	NeedToZeroPage;
/* off 0x0058 */	unsigned long	ActiveVacbSpinLock;
/* off 0x005c */	unsigned long	VacbActiveCount;
/* off 0x0060 */	unsigned long	DirtyPages;
/* off 0x0064 */	struct _LIST_ENTRY	SharedCacheMapLinks;
/* off 0x006c */	unsigned long	Flags;
/* off 0x0070 */	long	Status;
/* off 0x0074 */	struct _MBCB*	Mbcb;
/* off 0x0078 */	void*	Section;
/* off 0x007c */	struct _KEVENT*	CreateEvent;
/* off 0x0080 */	struct _KEVENT*	WaitOnActiveCount;
/* off 0x0084 */	unsigned long	PagesToWrite;
/* off 0x0088 */	__int64	BeyondLastFlush;
/* off 0x0090 */	struct _CACHE_MANAGER_CALLBACKS*	Callbacks;
/* off 0x0094 */	void*	LazyWriteContext;
/* off 0x0098 */	struct _LIST_ENTRY	PrivateList;
/* off 0x00a0 */	void*	LogHandle;
/* off 0x00a4 */	void( __cdecl *FlushToLsnRoutine)(void*,union _LARGE_INTEGER);
/* off 0x00a8 */	unsigned long	DirtyPageThreshold;
/* off 0x00ac */	unsigned long	LazyWritePassCount;
/* off 0x00b0 */	struct _CACHE_UNINITIALIZE_EVENT*	UninitializeEvent;
/* off 0x00b4 */	struct _VACB*	NeedToZeroVacb;
/* off 0x00b8 */	unsigned long	BcbSpinLock;
/* off 0x00bc */	void*	Reserved;
/* off 0x00c0 */	struct _KEVENT	Event;
/* off 0x00d0 */	struct _EX_PUSH_LOCK	VacbPushLock;
/* off 0x00d8 */	struct _PRIVATE_CACHE_MAP	PrivateCacheMap;
};
struct _BITMAP_RANGE /* sizeof 00000020 32 */
{
/* off 0x0000 */	struct _LIST_ENTRY	Links;
/* off 0x0008 */	__int64	BasePage;
/* off 0x0010 */	unsigned long	FirstDirtyPage;
/* off 0x0014 */	unsigned long	LastDirtyPage;
/* off 0x0018 */	unsigned long	DirtyPages;
/* off 0x001c */	unsigned long*	Bitmap;
};
struct _MBCB /* sizeof 00000080 128 */
{
/* off 0x0000 */	short	NodeTypeCode;
/* off 0x0002 */	short	NodeIsInZone;
/* off 0x0004 */	unsigned long	PagesToWrite;
/* off 0x0008 */	unsigned long	DirtyPages;
/* off 0x000c */	unsigned long	Reserved;
/* off 0x0010 */	struct _LIST_ENTRY	BitmapRanges;
/* off 0x0018 */	__int64	ResumeWritePage;
/* off 0x0020 */	struct _BITMAP_RANGE	BitmapRange1;
/* off 0x0040 */	struct _BITMAP_RANGE	BitmapRange2;
/* off 0x0060 */	struct _BITMAP_RANGE	BitmapRange3;
};
struct _CACHE_MANAGER_CALLBACKS /* sizeof 00000010 16 */
{
/* off 0x0000 */	unsigned char( __cdecl *AcquireForLazyWrite)(void*,unsigned char);
/* off 0x0004 */	void( __cdecl *ReleaseFromLazyWrite)(void*);
/* off 0x0008 */	unsigned char( __cdecl *AcquireForReadAhead)(void*,unsigned char);
/* off 0x000c */	void( __cdecl *ReleaseFromReadAhead)(void*);
};
struct _CACHE_UNINITIALIZE_EVENT /* sizeof 00000014 20 */
{
/* off 0x0000 */	struct _CACHE_UNINITIALIZE_EVENT*	Next;
/* off 0x0004 */	struct _KEVENT	Event;
};
struct _VACB_LEVEL_REFERENCE /* sizeof 00000008 8 */
{
/* off 0x0000 */	long	Reference;
/* off 0x0004 */	long	SpecialReference;
};
struct _HEAP_ENTRY /* sizeof 00000008 8 */
{
union
{
struct
{
/* off 0x0000 */	unsigned short	Size;
/* off 0x0002 */	unsigned short	PreviousSize;
};
struct
{
/* off 0x0000 */	void*	SubSegmentCode;
};
};
/* off 0x0004 */	unsigned char	SmallTagIndex;
/* off 0x0005 */	unsigned char	Flags;
/* off 0x0006 */	unsigned char	UnusedBytes;
/* off 0x0007 */	unsigned char	SegmentIndex;
};
struct _HEAP /* sizeof 00000588 1416 */
{
/* off 0x0000 */	struct _HEAP_ENTRY	Entry;
/* off 0x0008 */	unsigned long	Signature;
/* off 0x000c */	unsigned long	Flags;
/* off 0x0010 */	unsigned long	ForceFlags;
/* off 0x0014 */	unsigned long	VirtualMemoryThreshold;
/* off 0x0018 */	unsigned long	SegmentReserve;
/* off 0x001c */	unsigned long	SegmentCommit;
/* off 0x0020 */	unsigned long	DeCommitFreeBlockThreshold;
/* off 0x0024 */	unsigned long	DeCommitTotalFreeThreshold;
/* off 0x0028 */	unsigned long	TotalFreeSize;
/* off 0x002c */	unsigned long	MaximumAllocationSize;
/* off 0x0030 */	unsigned short	ProcessHeapsListIndex;
/* off 0x0032 */	unsigned short	HeaderValidateLength;
/* off 0x0034 */	void*	HeaderValidateCopy;
/* off 0x0038 */	unsigned short	NextAvailableTagIndex;
/* off 0x003a */	unsigned short	MaximumTagIndex;
/* off 0x003c */	struct _HEAP_TAG_ENTRY*	TagEntries;
/* off 0x0040 */	struct _HEAP_UCR_SEGMENT*	UCRSegments;
/* off 0x0044 */	struct _HEAP_UNCOMMMTTED_RANGE*	UnusedUnCommittedRanges;
/* off 0x0048 */	unsigned long	AlignRound;
/* off 0x004c */	unsigned long	AlignMask;
/* off 0x0050 */	struct _LIST_ENTRY	VirtualAllocdBlocks;
/* off 0x0058 */	struct _HEAP_SEGMENT* Segments[64];
/* off 0x0158 */	struct __unnamed	u;
/* off 0x0168 */	struct __unnamed	u2;
/* off 0x016a */	unsigned short	AllocatorBackTraceIndex;
/* off 0x016c */	unsigned long	NonDedicatedListLength;
/* off 0x0170 */	void*	LargeBlocksIndex;
/* off 0x0174 */	struct _HEAP_PSEUDO_TAG_ENTRY*	PseudoTagEntries;
/* off 0x0178 */	struct _LIST_ENTRY FreeLists[128];
/* off 0x0578 */	struct _HEAP_LOCK*	LockVariable;
/* off 0x057c */	long( __stdcall *CommitRoutine)(void*,void**,unsigned long*);
/* off 0x0580 */	void*	FrontEndHeap;
/* off 0x0584 */	unsigned short	FrontHeapLockCount;
/* off 0x0586 */	unsigned char	FrontEndHeapType;
/* off 0x0587 */	unsigned char	LastSegmentIndex;
};
struct _HEAP_TAG_ENTRY /* sizeof 00000040 64 */
{
/* off 0x0000 */	unsigned long	Allocs;
/* off 0x0004 */	unsigned long	Frees;
/* off 0x0008 */	unsigned long	Size;
/* off 0x000c */	unsigned short	TagIndex;
/* off 0x000e */	unsigned short	CreatorBackTraceIndex;
/* off 0x0010 */	unsigned short TagName[24];
};
struct _HEAP_UCR_SEGMENT /* sizeof 00000010 16 */
{
/* off 0x0000 */	struct _HEAP_UCR_SEGMENT*	Next;
/* off 0x0004 */	unsigned long	ReservedSize;
/* off 0x0008 */	unsigned long	CommittedSize;
/* off 0x000c */	unsigned long	filler;
};
struct _HEAP_UNCOMMMTTED_RANGE /* sizeof 00000010 16 */
{
/* off 0x0000 */	struct _HEAP_UNCOMMMTTED_RANGE*	Next;
/* off 0x0004 */	unsigned long	Address;
/* off 0x0008 */	unsigned long	Size;
/* off 0x000c */	unsigned long	filler;
};
struct _HEAP_SEGMENT /* sizeof 0000003c 60 */
{
/* off 0x0000 */	struct _HEAP_ENTRY	Entry;
/* off 0x0008 */	unsigned long	Signature;
/* off 0x000c */	unsigned long	Flags;
/* off 0x0010 */	struct _HEAP*	Heap;
/* off 0x0014 */	unsigned long	LargestUnCommittedRange;
/* off 0x0018 */	void*	BaseAddress;
/* off 0x001c */	unsigned long	NumberOfPages;
/* off 0x0020 */	struct _HEAP_ENTRY*	FirstEntry;
/* off 0x0024 */	struct _HEAP_ENTRY*	LastValidEntry;
/* off 0x0028 */	unsigned long	NumberOfUnCommittedPages;
/* off 0x002c */	unsigned long	NumberOfUnCommittedRanges;
/* off 0x0030 */	struct _HEAP_UNCOMMMTTED_RANGE*	UnCommittedRanges;
/* off 0x0034 */	unsigned short	AllocatorBackTraceIndex;
/* off 0x0036 */	unsigned short	Reserved;
/* off 0x0038 */	struct _HEAP_ENTRY*	LastEntryInSegment;
};
struct _HEAP_PSEUDO_TAG_ENTRY /* sizeof 0000000c 12 */
{
/* off 0x0000 */	unsigned long	Allocs;
/* off 0x0004 */	unsigned long	Frees;
/* off 0x0008 */	unsigned long	Size;
};
struct _HEAP_LOCK /* sizeof 00000038 56 */
{
/* off 0x0000 */	struct __unnamed	Lock;
};
struct _INTERLOCK_SEQ /* sizeof 00000008 8 */
{
union
{
struct
{
/* off 0x0000 */	unsigned short	Depth;
/* off 0x0002 */	unsigned short	FreeEntryOffset;
};
struct
{
/* off 0x0000 */	unsigned long	OffsetAndDepth;
/* off 0x0004 */	unsigned long	Sequence;
};
/* off 0x0000 */	__int64	Exchg;
};
};
struct _HEAP_SUBSEGMENT /* sizeof 00000020 32 */
{
/* off 0x0000 */	void*	Bucket;
/* off 0x0004 */	struct _HEAP_USERDATA_HEADER*	UserBlocks;
/* off 0x0008 */	struct _INTERLOCK_SEQ	AggregateExchg;
union
{
struct
{
/* off 0x0010 */	unsigned short	BlockSize;
/* off 0x0012 */	unsigned short	FreeThreshold;
/* off 0x0014 */	unsigned short	BlockCount;
/* off 0x0016 */	unsigned char	SizeIndex;
/* off 0x0017 */	unsigned char	AffinityIndex;
};
struct
{
/* off 0x0010 */	unsigned long Alignment[2];
};
};
/* off 0x0018 */	struct _SINGLE_LIST_ENTRY	SFreeListEntry;
/* off 0x001c */	unsigned long	Lock;
};
struct _HEAP_USERDATA_HEADER /* sizeof 00000010 16 */
{
union
{
/* off 0x0000 */	struct _SINGLE_LIST_ENTRY	SFreeListEntry;
/* off 0x0000 */	struct _HEAP_SUBSEGMENT*	SubSegment;
};
/* off 0x0004 */	void*	HeapHandle;
/* off 0x0008 */	unsigned long	SizeIndex;
/* off 0x000c */	unsigned long	Signature;
};
struct _HMAP_ENTRY /* sizeof 00000010 16 */
{
/* off 0x0000 */	unsigned long	BlockAddress;
/* off 0x0004 */	unsigned long	BinAddress;
/* off 0x0008 */	struct _CM_VIEW_OF_FILE*	CmView;
/* off 0x000c */	unsigned long	MemAlloc;
};
struct _HMAP_TABLE /* sizeof 00002000 8192 */
{
/* off 0x0000 */	struct _HMAP_ENTRY Table[512];
};
struct _CM_VIEW_OF_FILE /* sizeof 00000024 36 */
{
/* off 0x0000 */	struct _LIST_ENTRY	LRUViewList;
/* off 0x0008 */	struct _LIST_ENTRY	PinViewList;
/* off 0x0010 */	unsigned long	FileOffset;
/* off 0x0014 */	unsigned long	Size;
/* off 0x0018 */	unsigned long*	ViewAddress;
/* off 0x001c */	void*	Bcb;
/* off 0x0020 */	unsigned long	UseCount;
};
struct _OBJECT_SYMBOLIC_LINK /* sizeof 00000020 32 */
{
/* off 0x0000 */	union _LARGE_INTEGER	CreationTime;
/* off 0x0008 */	struct _UNICODE_STRING	LinkTarget;
/* off 0x0010 */	struct _UNICODE_STRING	LinkTargetRemaining;
/* off 0x0018 */	void*	LinkTargetObject;
/* off 0x001c */	unsigned long	DosDeviceDriveIndex;
};
struct _POOL_HEADER /* sizeof 00000008 8 */
{
union
{
struct
{
/* off 0x0000 */	unsigned short	PreviousSize:9	 /* start bit 0 */;
struct
{
/* off 0x0000 */	unsigned short	PoolIndex:7	 /* start bit 9 */;
};
/* off 0x0002 */	unsigned short	BlockSize:9	 /* start bit 0 */;
/* off 0x0002 */	unsigned short	PoolType:7	 /* start bit 9 */;
};
struct
{
/* off 0x0000 */	unsigned long	Ulong1;
};
};
union
{
/* off 0x0004 */	struct _EPROCESS*	ProcessBilled;
/* off 0x0004 */	unsigned long	PoolTag;
struct
{
/* off 0x0004 */	unsigned short	AllocatorBackTraceIndex;
/* off 0x0006 */	unsigned short	PoolTagHash;
};
};
};
struct _POOL_BLOCK_HEAD /* sizeof 00000010 16 */
{
/* off 0x0000 */	struct _POOL_HEADER	Header;
/* off 0x0008 */	struct _LIST_ENTRY	List;
};
struct _LDR_DATA_TABLE_ENTRY /* sizeof 00000050 80 */
{
/* off 0x0000 */	struct _LIST_ENTRY	InLoadOrderLinks;
/* off 0x0008 */	struct _LIST_ENTRY	InMemoryOrderLinks;
/* off 0x0010 */	struct _LIST_ENTRY	InInitializationOrderLinks;
/* off 0x0018 */	void*	DllBase;
/* off 0x001c */	void*	EntryPoint;
/* off 0x0020 */	unsigned long	SizeOfImage;
/* off 0x0024 */	struct _UNICODE_STRING	FullDllName;
/* off 0x002c */	struct _UNICODE_STRING	BaseDllName;
/* off 0x0034 */	unsigned long	Flags;
/* off 0x0038 */	unsigned short	LoadCount;
/* off 0x003a */	unsigned short	TlsIndex;
union
{
/* off 0x003c */	struct _LIST_ENTRY	HashLinks;
struct
{
/* off 0x003c */	void*	SectionPointer;
/* off 0x0040 */	unsigned long	CheckSum;
};
};
union
{
/* off 0x0044 */	unsigned long	TimeDateStamp;
/* off 0x0044 */	void*	LoadedImports;
};
/* off 0x0048 */	void*	EntryPointActivationContext;
/* off 0x004c */	void*	PatchInformation;
};
struct _VI_DEADLOCK_GLOBALS /* sizeof 00000110 272 */
{
/* off 0x0000 */	unsigned long Nodes[2];
/* off 0x0008 */	unsigned long Resources[2];
/* off 0x0010 */	unsigned long Threads[2];
/* off 0x0018 */	__int64	TimeAcquire;
/* off 0x0020 */	__int64	TimeRelease;
/* off 0x0028 */	unsigned long	BytesAllocated;
/* off 0x002c */	struct _LIST_ENTRY*	ResourceDatabase;
/* off 0x0030 */	struct _LIST_ENTRY*	ThreadDatabase;
/* off 0x0034 */	unsigned long	AllocationFailures;
/* off 0x0038 */	unsigned long	NodesTrimmedBasedOnAge;
/* off 0x003c */	unsigned long	NodesTrimmedBasedOnCount;
/* off 0x0040 */	unsigned long	NodesSearched;
/* off 0x0044 */	unsigned long	MaxNodesSearched;
/* off 0x0048 */	unsigned long	SequenceNumber;
/* off 0x004c */	unsigned long	RecursionDepthLimit;
/* off 0x0050 */	unsigned long	SearchedNodesLimit;
/* off 0x0054 */	unsigned long	DepthLimitHits;
/* off 0x0058 */	unsigned long	SearchLimitHits;
/* off 0x005c */	unsigned long	ABC_ACB_Skipped;
/* off 0x0060 */	struct _LIST_ENTRY	FreeResourceList;
/* off 0x0068 */	struct _LIST_ENTRY	FreeThreadList;
/* off 0x0070 */	struct _LIST_ENTRY	FreeNodeList;
/* off 0x0078 */	unsigned long	FreeResourceCount;
/* off 0x007c */	unsigned long	FreeThreadCount;
/* off 0x0080 */	unsigned long	FreeNodeCount;
/* off 0x0084 */	void*	Instigator;
/* off 0x0088 */	unsigned long	NumberOfParticipants;
/* off 0x008c */	struct _VI_DEADLOCK_NODE* Participant[32];
/* off 0x010c */	unsigned long	CacheReductionInProgress;
};
struct _VI_DEADLOCK_NODE /* sizeof 00000068 104 */
{
/* off 0x0000 */	struct _VI_DEADLOCK_NODE*	Parent;
/* off 0x0004 */	struct _LIST_ENTRY	ChildrenList;
/* off 0x000c */	struct _LIST_ENTRY	SiblingsList;
union
{
/* off 0x0014 */	struct _LIST_ENTRY	ResourceList;
/* off 0x0014 */	struct _LIST_ENTRY	FreeListEntry;
};
/* off 0x001c */	struct _VI_DEADLOCK_RESOURCE*	Root;
/* off 0x0020 */	struct _VI_DEADLOCK_THREAD*	ThreadEntry;
/* off 0x0024 */	unsigned long	Active:1	 /* start bit 0 */;
/* off 0x0024 */	unsigned long	OnlyTryAcquireUsed:1	 /* start bit 1 */;
/* off 0x0024 */	unsigned long	SequenceNumber:30	 /* start bit 2 */;
/* off 0x0028 */	void* StackTrace[8];
/* off 0x0048 */	void* ParentStackTrace[8];
};
struct _VI_DEADLOCK_RESOURCE /* sizeof 00000080 128 */
{
/* off 0x0000 */	enum _VI_DEADLOCK_RESOURCE_TYPE	Type;
/* off 0x0004 */	unsigned long	NodeCount:16	 /* start bit 0 */;
/* off 0x0004 */	unsigned long	RecursionCount:16	 /* start bit 16 */;
/* off 0x0008 */	void*	ResourceAddress;
/* off 0x000c */	struct _VI_DEADLOCK_THREAD*	ThreadOwner;
/* off 0x0010 */	struct _LIST_ENTRY	ResourceList;
union
{
/* off 0x0018 */	struct _LIST_ENTRY	HashChainList;
/* off 0x0018 */	struct _LIST_ENTRY	FreeListEntry;
};
/* off 0x0020 */	void* StackTrace[8];
/* off 0x0040 */	void* LastAcquireTrace[8];
/* off 0x0060 */	void* LastReleaseTrace[8];
};
enum _VI_DEADLOCK_RESOURCE_TYPE
{
	VfDeadlockUnknown	=0x00000000	,//0
	VfDeadlockMutex	=0x00000001	,//0
	VfDeadlockFastMutex	=0x00000002	,//0
	VfDeadlockFastMutexUnsafe	=0x00000003	,//0
	VfDeadlockSpinLock	=0x00000004	,//0
	VfDeadlockQueuedSpinLock	=0x00000005	,//0
	VfDeadlockTypeMaximum	=0x00000006	,//0
};
struct _VI_DEADLOCK_THREAD /* sizeof 0000001c 28 */
{
/* off 0x0000 */	struct _KTHREAD*	Thread;
/* off 0x0004 */	struct _VI_DEADLOCK_NODE*	CurrentSpinNode;
/* off 0x0008 */	struct _VI_DEADLOCK_NODE*	CurrentOtherNode;
union
{
/* off 0x000c */	struct _LIST_ENTRY	ListEntry;
/* off 0x000c */	struct _LIST_ENTRY	FreeListEntry;
};
/* off 0x0014 */	unsigned long	NodeCount;
/* off 0x0018 */	unsigned long	PagingCount;
};
enum _PF_SCENARIO_TYPE
{
	PfApplicationLaunchScenarioType	=0x00000000	,//0
	PfSystemBootScenarioType	=0x00000001	,//0
	PfMaxScenarioType	=0x00000002	,//0
};
struct _THERMAL_INFORMATION /* sizeof 0000004c 76 */
{
/* off 0x0000 */	unsigned long	ThermalStamp;
/* off 0x0004 */	unsigned long	ThermalConstant1;
/* off 0x0008 */	unsigned long	ThermalConstant2;
/* off 0x000c */	unsigned long	Processors;
/* off 0x0010 */	unsigned long	SamplingPeriod;
/* off 0x0014 */	unsigned long	CurrentTemperature;
/* off 0x0018 */	unsigned long	PassiveTripPoint;
/* off 0x001c */	unsigned long	CriticalTripPoint;
/* off 0x0020 */	unsigned char	ActiveTripPointCount;
/* off 0x0024 */	unsigned long ActiveTripPoint[10];
};
struct _SECTION_OBJECT /* sizeof 00000018 24 */
{
/* off 0x0000 */	void*	StartingVa;
/* off 0x0004 */	void*	EndingVa;
/* off 0x0008 */	void*	Parent;
/* off 0x000c */	void*	LeftChild;
/* off 0x0010 */	void*	RightChild;
/* off 0x0014 */	struct _SEGMENT_OBJECT*	Segment;
};
struct _SEGMENT_OBJECT /* sizeof 00000030 48 */
{
/* off 0x0000 */	void*	BaseAddress;
/* off 0x0004 */	unsigned long	TotalNumberOfPtes;
/* off 0x0008 */	union _LARGE_INTEGER	SizeOfSegment;
/* off 0x0010 */	unsigned long	NonExtendedPtes;
/* off 0x0014 */	unsigned long	ImageCommitment;
/* off 0x0018 */	struct _CONTROL_AREA*	ControlArea;
/* off 0x001c */	struct _SUBSECTION*	Subsection;
/* off 0x0020 */	struct _LARGE_CONTROL_AREA*	LargeControlArea;
/* off 0x0024 */	struct _MMSECTION_FLAGS*	MmSectionFlags;
/* off 0x0028 */	struct _MMSUBSECTION_FLAGS*	MmSubSectionFlags;
};
struct _CONTROL_AREA /* sizeof 00000030 48 */
{
/* off 0x0000 */	struct _SEGMENT*	Segment;
/* off 0x0004 */	struct _LIST_ENTRY	DereferenceList;
/* off 0x000c */	unsigned long	NumberOfSectionReferences;
/* off 0x0010 */	unsigned long	NumberOfPfnReferences;
/* off 0x0014 */	unsigned long	NumberOfMappedViews;
/* off 0x0018 */	unsigned short	NumberOfSubsections;
/* off 0x001a */	unsigned short	FlushInProgressCount;
/* off 0x001c */	unsigned long	NumberOfUserReferences;
/* off 0x0020 */	struct __unnamed	u;
/* off 0x0024 */	struct _FILE_OBJECT*	FilePointer;
/* off 0x0028 */	struct _EVENT_COUNTER*	WaitingForDeletion;
/* off 0x002c */	unsigned short	ModifiedWriteCount;
/* off 0x002e */	unsigned short	NumberOfSystemCacheViews;
};
struct _MMPTE /* sizeof 00000004 4 */
{
/* off 0x0000 */	struct __unnamed	u;
};
struct _SEGMENT /* sizeof 00000040 64 */
{
/* off 0x0000 */	struct _CONTROL_AREA*	ControlArea;
/* off 0x0004 */	unsigned long	TotalNumberOfPtes;
/* off 0x0008 */	unsigned long	NonExtendedPtes;
/* off 0x000c */	unsigned long	WritableUserReferences;
/* off 0x0010 */	unsigned __int64	SizeOfSegment;
/* off 0x0018 */	struct _MMPTE	SegmentPteTemplate;
/* off 0x001c */	unsigned long	NumberOfCommittedPages;
/* off 0x0020 */	struct _MMEXTEND_INFO*	ExtendInfo;
/* off 0x0024 */	void*	SystemImageBase;
/* off 0x0028 */	void*	BasedAddress;
/* off 0x002c */	struct __unnamed	u1;
/* off 0x0030 */	struct __unnamed	u2;
/* off 0x0034 */	struct _MMPTE*	PrototypePte;
/* off 0x0038 */	struct _MMPTE ThePtes[1];
};
struct _MMEXTEND_INFO /* sizeof 00000010 16 */
{
/* off 0x0000 */	unsigned __int64	CommittedSize;
/* off 0x0008 */	unsigned long	ReferenceCount;
};
struct _EVENT_COUNTER /* sizeof 00000018 24 */
{
/* off 0x0000 */	struct _SINGLE_LIST_ENTRY	ListEntry;
/* off 0x0004 */	unsigned long	RefCount;
/* off 0x0008 */	struct _KEVENT	Event;
};
struct _SUBSECTION /* sizeof 00000020 32 */
{
/* off 0x0000 */	struct _CONTROL_AREA*	ControlArea;
/* off 0x0004 */	struct __unnamed	u;
/* off 0x0008 */	unsigned long	StartingSector;
/* off 0x000c */	unsigned long	NumberOfFullSectors;
/* off 0x0010 */	struct _MMPTE*	SubsectionBase;
/* off 0x0014 */	unsigned long	UnusedPtes;
/* off 0x0018 */	unsigned long	PtesInSubsection;
/* off 0x001c */	struct _SUBSECTION*	NextSubsection;
};
struct _LARGE_CONTROL_AREA /* sizeof 00000040 64 */
{
/* off 0x0000 */	struct _SEGMENT*	Segment;
/* off 0x0004 */	struct _LIST_ENTRY	DereferenceList;
/* off 0x000c */	unsigned long	NumberOfSectionReferences;
/* off 0x0010 */	unsigned long	NumberOfPfnReferences;
/* off 0x0014 */	unsigned long	NumberOfMappedViews;
/* off 0x0018 */	unsigned short	NumberOfSubsections;
/* off 0x001a */	unsigned short	FlushInProgressCount;
/* off 0x001c */	unsigned long	NumberOfUserReferences;
/* off 0x0020 */	struct __unnamed	u;
/* off 0x0024 */	struct _FILE_OBJECT*	FilePointer;
/* off 0x0028 */	struct _EVENT_COUNTER*	WaitingForDeletion;
/* off 0x002c */	unsigned short	ModifiedWriteCount;
/* off 0x002e */	unsigned short	NumberOfSystemCacheViews;
/* off 0x0030 */	unsigned long	StartingFrame;
/* off 0x0034 */	struct _LIST_ENTRY	UserGlobalList;
/* off 0x003c */	unsigned long	SessionId;
};
struct _MMSECTION_FLAGS /* sizeof 00000004 4 */
{
/* off 0x0000 */	unsigned int	BeingDeleted:1	 /* start bit 0 */;
/* off 0x0000 */	unsigned int	BeingCreated:1	 /* start bit 1 */;
/* off 0x0000 */	unsigned int	BeingPurged:1	 /* start bit 2 */;
/* off 0x0000 */	unsigned int	NoModifiedWriting:1	 /* start bit 3 */;
/* off 0x0000 */	unsigned int	FailAllIo:1	 /* start bit 4 */;
/* off 0x0000 */	unsigned int	Image:1	 /* start bit 5 */;
/* off 0x0000 */	unsigned int	Based:1	 /* start bit 6 */;
/* off 0x0000 */	unsigned int	File:1	 /* start bit 7 */;
/* off 0x0000 */	unsigned int	Networked:1	 /* start bit 8 */;
/* off 0x0000 */	unsigned int	NoCache:1	 /* start bit 9 */;
/* off 0x0000 */	unsigned int	PhysicalMemory:1	 /* start bit 10 */;
/* off 0x0000 */	unsigned int	CopyOnWrite:1	 /* start bit 11 */;
/* off 0x0000 */	unsigned int	Reserve:1	 /* start bit 12 */;
/* off 0x0000 */	unsigned int	Commit:1	 /* start bit 13 */;
/* off 0x0000 */	unsigned int	FloppyMedia:1	 /* start bit 14 */;
/* off 0x0000 */	unsigned int	WasPurged:1	 /* start bit 15 */;
/* off 0x0000 */	unsigned int	UserReference:1	 /* start bit 16 */;
/* off 0x0000 */	unsigned int	GlobalMemory:1	 /* start bit 17 */;
/* off 0x0000 */	unsigned int	DeleteOnClose:1	 /* start bit 18 */;
/* off 0x0000 */	unsigned int	FilePointerNull:1	 /* start bit 19 */;
/* off 0x0000 */	unsigned int	DebugSymbolsLoaded:1	 /* start bit 20 */;
/* off 0x0000 */	unsigned int	SetMappedFileIoComplete:1	 /* start bit 21 */;
/* off 0x0000 */	unsigned int	CollidedFlush:1	 /* start bit 22 */;
/* off 0x0000 */	unsigned int	NoChange:1	 /* start bit 23 */;
/* off 0x0000 */	unsigned int	HadUserReference:1	 /* start bit 24 */;
/* off 0x0000 */	unsigned int	ImageMappedInSystemSpace:1	 /* start bit 25 */;
/* off 0x0000 */	unsigned int	UserWritable:1	 /* start bit 26 */;
/* off 0x0000 */	unsigned int	Accessed:1	 /* start bit 27 */;
/* off 0x0000 */	unsigned int	GlobalOnlyPerSession:1	 /* start bit 28 */;
/* off 0x0000 */	unsigned int	Rom:1	 /* start bit 29 */;
/* off 0x0000 */	unsigned int	filler:2	 /* start bit 30 */;
};
struct _MMSUBSECTION_FLAGS /* sizeof 00000004 4 */
{
/* off 0x0000 */	unsigned int	ReadOnly:1	 /* start bit 0 */;
/* off 0x0000 */	unsigned int	ReadWrite:1	 /* start bit 1 */;
/* off 0x0000 */	unsigned int	SubsectionStatic:1	 /* start bit 2 */;
/* off 0x0000 */	unsigned int	GlobalMemory:1	 /* start bit 3 */;
/* off 0x0000 */	unsigned int	Protection:5	 /* start bit 4 */;
/* off 0x0000 */	unsigned int	LargePages:1	 /* start bit 9 */;
/* off 0x0000 */	unsigned int	StartingSector4132:10	 /* start bit 10 */;
/* off 0x0000 */	unsigned int	SectorEndOffset:12	 /* start bit 20 */;
};
union _POWER_STATE /* sizeof 00000004 4 */
{
/* off 0x0000 */	enum _SYSTEM_POWER_STATE	SystemState;
/* off 0x0000 */	enum _DEVICE_POWER_STATE	DeviceState;
};
enum _SYSTEM_POWER_STATE
{
	PowerSystemUnspecified	=0x00000000	,//0
	PowerSystemWorking	=0x00000001	,//0
	PowerSystemSleeping1	=0x00000002	,//0
	PowerSystemSleeping2	=0x00000003	,//0
	PowerSystemSleeping3	=0x00000004	,//0
	PowerSystemHibernate	=0x00000005	,//0
	PowerSystemShutdown	=0x00000006	,//0
	PowerSystemMaximum	=0x00000007	,//0
};
union EX_QUEUE_WORKER_INFO /* sizeof 00000004 4 */
{
struct
{
/* off 0x0000 */	unsigned long	QueueDisabled:1	 /* start bit 0 */;
/* off 0x0000 */	unsigned long	MakeThreadsAsNecessary:1	 /* start bit 1 */;
/* off 0x0000 */	unsigned long	WaitMode:1	 /* start bit 2 */;
/* off 0x0000 */	unsigned long	WorkerCount:29	 /* start bit 3 */;
};
/* off 0x0000 */	long	QueueWorkerInfo;
};
struct _EX_WORK_QUEUE /* sizeof 0000003c 60 */
{
/* off 0x0000 */	struct _KQUEUE	WorkerQueue;
/* off 0x0028 */	unsigned long	DynamicThreadCount;
/* off 0x002c */	unsigned long	WorkItemsProcessed;
/* off 0x0030 */	unsigned long	WorkItemsProcessedLastPass;
/* off 0x0034 */	unsigned long	QueueDepthLastPass;
/* off 0x0038 */	union EX_QUEUE_WORKER_INFO	Info;
};
struct _MM_DRIVER_VERIFIER_DATA /* sizeof 00000070 112 */
{
/* off 0x0000 */	unsigned long	Level;
/* off 0x0004 */	unsigned long	RaiseIrqls;
/* off 0x0008 */	unsigned long	AcquireSpinLocks;
/* off 0x000c */	unsigned long	SynchronizeExecutions;
/* off 0x0010 */	unsigned long	AllocationsAttempted;
/* off 0x0014 */	unsigned long	AllocationsSucceeded;
/* off 0x0018 */	unsigned long	AllocationsSucceededSpecialPool;
/* off 0x001c */	unsigned long	AllocationsWithNoTag;
/* off 0x0020 */	unsigned long	TrimRequests;
/* off 0x0024 */	unsigned long	Trims;
/* off 0x0028 */	unsigned long	AllocationsFailed;
/* off 0x002c */	unsigned long	AllocationsFailedDeliberately;
/* off 0x0030 */	unsigned long	Loads;
/* off 0x0034 */	unsigned long	Unloads;
/* off 0x0038 */	unsigned long	UnTrackedPool;
/* off 0x003c */	unsigned long	UserTrims;
/* off 0x0040 */	unsigned long	CurrentPagedPoolAllocations;
/* off 0x0044 */	unsigned long	CurrentNonPagedPoolAllocations;
/* off 0x0048 */	unsigned long	PeakPagedPoolAllocations;
/* off 0x004c */	unsigned long	PeakNonPagedPoolAllocations;
/* off 0x0050 */	unsigned long	PagedBytes;
/* off 0x0054 */	unsigned long	NonPagedBytes;
/* off 0x0058 */	unsigned long	PeakPagedBytes;
/* off 0x005c */	unsigned long	PeakNonPagedBytes;
/* off 0x0060 */	unsigned long	BurstAllocationsFailedDeliberately;
/* off 0x0064 */	unsigned long	SessionTrims;
/* off 0x0068 */	unsigned long Reserved[2];
};
struct _CALL_HASH_ENTRY /* sizeof 00000014 20 */
{
/* off 0x0000 */	struct _LIST_ENTRY	ListEntry;
/* off 0x0008 */	void*	CallersAddress;
/* off 0x000c */	void*	CallersCaller;
/* off 0x0010 */	unsigned long	CallCount;
};
struct _KLOCK_QUEUE_HANDLE /* sizeof 0000000c 12 */
{
/* off 0x0000 */	struct _KSPIN_LOCK_QUEUE	LockQueue;
/* off 0x0008 */	unsigned char	OldIrql;
};
enum _MMLISTS
{
	ZeroedPageList	=0x00000000	,//0
	FreePageList	=0x00000001	,//0
	StandbyPageList	=0x00000002	,//0
	ModifiedPageList	=0x00000003	,//0
	ModifiedNoWritePageList	=0x00000004	,//0
	BadPageList	=0x00000005	,//0
	ActiveAndValid	=0x00000006	,//0
	TransitionPage	=0x00000007	,//0
};
struct _DEFERRED_WRITE /* sizeof 00000028 40 */
{
/* off 0x0000 */	short	NodeTypeCode;
/* off 0x0002 */	short	NodeByteSize;
/* off 0x0004 */	struct _FILE_OBJECT*	FileObject;
/* off 0x0008 */	unsigned long	BytesToWrite;
/* off 0x000c */	struct _LIST_ENTRY	DeferredWriteLinks;
/* off 0x0014 */	struct _KEVENT*	Event;
/* off 0x0018 */	void( __cdecl *PostRoutine)(void*,void*);
/* off 0x001c */	void*	Context1;
/* off 0x0020 */	void*	Context2;
/* off 0x0024 */	unsigned char	LimitModifiedPages;
};
struct _HIVE_LIST_ENTRY /* sizeof 00000018 24 */
{
/* off 0x0000 */	unsigned short*	Name;
/* off 0x0004 */	unsigned short*	BaseName;
/* off 0x0008 */	struct _CMHIVE*	CmHive;
/* off 0x000c */	unsigned long	Flags;
/* off 0x0010 */	struct _CMHIVE*	CmHive2;
/* off 0x0014 */	unsigned char	ThreadFinished;
/* off 0x0015 */	unsigned char	ThreadStarted;
/* off 0x0016 */	unsigned char	Allocate;
};
struct _RTL_BITMAP /* sizeof 00000008 8 */
{
/* off 0x0000 */	unsigned long	SizeOfBitMap;
/* off 0x0004 */	unsigned long*	Buffer;
};
struct _DUAL /* sizeof 000000dc 220 */
{
/* off 0x0000 */	unsigned long	Length;
/* off 0x0004 */	struct _HMAP_DIRECTORY*	Map;
/* off 0x0008 */	struct _HMAP_TABLE*	SmallDir;
/* off 0x000c */	unsigned long	Guard;
/* off 0x0010 */	struct _RTL_BITMAP FreeDisplay[24];
/* off 0x00d0 */	unsigned long	FreeSummary;
/* off 0x00d4 */	struct _LIST_ENTRY	FreeBins;
};
struct _HHIVE /* sizeof 00000210 528 */
{
/* off 0x0000 */	unsigned long	Signature;
/* off 0x0004 */	struct _CELL_DATA*( __cdecl *GetCellRoutine)(struct _HHIVE*,unsigned long);
/* off 0x0008 */	void( __cdecl *ReleaseCellRoutine)(struct _HHIVE*,unsigned long);
/* off 0x000c */	void*( __cdecl *Allocate)(unsigned long,unsigned char,unsigned long);
/* off 0x0010 */	void( __cdecl *Free)(void*,unsigned long);
/* off 0x0014 */	unsigned char( __cdecl *FileSetSize)(struct _HHIVE*,unsigned long,unsigned long,unsigned long);
/* off 0x0018 */	unsigned char( __cdecl *FileWrite)(struct _HHIVE*,unsigned long,struct CMP_OFFSET_ARRAY*,unsigned long,unsigned long*);
/* off 0x001c */	unsigned char( __cdecl *FileRead)(struct _HHIVE*,unsigned long,unsigned long*,void*,unsigned long);
/* off 0x0020 */	unsigned char( __cdecl *FileFlush)(struct _HHIVE*,unsigned long,union _LARGE_INTEGER*,unsigned long);
/* off 0x0024 */	struct _HBASE_BLOCK*	BaseBlock;
/* off 0x0028 */	struct _RTL_BITMAP	DirtyVector;
/* off 0x0030 */	unsigned long	DirtyCount;
/* off 0x0034 */	unsigned long	DirtyAlloc;
/* off 0x0038 */	unsigned char	RealWrites;
/* off 0x003c */	unsigned long	Cluster;
/* off 0x0040 */	unsigned char	Flat;
/* off 0x0041 */	unsigned char	ReadOnly;
/* off 0x0042 */	unsigned char	Log;
/* off 0x0044 */	unsigned long	HiveFlags;
/* off 0x0048 */	unsigned long	LogSize;
/* off 0x004c */	unsigned long	RefreshCount;
/* off 0x0050 */	unsigned long	StorageTypeCount;
/* off 0x0054 */	unsigned long	Version;
/* off 0x0058 */	struct _DUAL Storage[2];
};
struct _CMHIVE /* sizeof 0000049c 1180 */
{
/* off 0x0000 */	struct _HHIVE	Hive;
/* off 0x0210 */	void* FileHandles[3];
/* off 0x021c */	struct _LIST_ENTRY	NotifyList;
/* off 0x0224 */	struct _LIST_ENTRY	HiveList;
/* off 0x022c */	struct _FAST_MUTEX*	HiveLock;
/* off 0x0230 */	struct _FAST_MUTEX*	ViewLock;
/* off 0x0234 */	struct _LIST_ENTRY	LRUViewListHead;
/* off 0x023c */	struct _LIST_ENTRY	PinViewListHead;
/* off 0x0244 */	struct _FILE_OBJECT*	FileObject;
/* off 0x0248 */	struct _UNICODE_STRING	FileFullPath;
/* off 0x0250 */	struct _UNICODE_STRING	FileUserName;
/* off 0x0258 */	unsigned short	MappedViews;
/* off 0x025a */	unsigned short	PinnedViews;
/* off 0x025c */	unsigned long	UseCount;
/* off 0x0260 */	unsigned long	SecurityCount;
/* off 0x0264 */	unsigned long	SecurityCacheSize;
/* off 0x0268 */	long	SecurityHitHint;
/* off 0x026c */	struct _CM_KEY_SECURITY_CACHE_ENTRY*	SecurityCache;
/* off 0x0270 */	struct _LIST_ENTRY SecurityHash[64];
/* off 0x0470 */	struct _KEVENT*	UnloadEvent;
/* off 0x0474 */	struct _CM_KEY_CONTROL_BLOCK*	RootKcb;
/* off 0x0478 */	unsigned char	Frozen;
/* off 0x047c */	struct _WORK_QUEUE_ITEM*	UnloadWorkItem;
/* off 0x0480 */	unsigned char	GrowOnlyMode;
/* off 0x0484 */	unsigned long	GrowOffset;
/* off 0x0488 */	struct _LIST_ENTRY	KcbConvertListHead;
/* off 0x0490 */	struct _LIST_ENTRY	KnodeConvertListHead;
/* off 0x0498 */	struct _CM_CELL_REMAP_BLOCK*	CellRemapArray;
};
struct _CHILD_LIST /* sizeof 00000008 8 */
{
/* off 0x0000 */	unsigned long	Count;
/* off 0x0004 */	unsigned long	List;
};
struct _CM_KEY_REFERENCE /* sizeof 00000008 8 */
{
/* off 0x0000 */	unsigned long	KeyCell;
/* off 0x0004 */	struct _HHIVE*	KeyHive;
};
struct _CM_KEY_NODE /* sizeof 00000050 80 */
{
/* off 0x0000 */	unsigned short	Signature;
/* off 0x0002 */	unsigned short	Flags;
/* off 0x0004 */	union _LARGE_INTEGER	LastWriteTime;
/* off 0x000c */	unsigned long	Spare;
/* off 0x0010 */	unsigned long	Parent;
/* off 0x0014 */	unsigned long SubKeyCounts[2];
union
{
struct
{
/* off 0x001c */	unsigned long SubKeyLists[2];
/* off 0x0024 */	struct _CHILD_LIST	ValueList;
};
struct
{
/* off 0x001c */	struct _CM_KEY_REFERENCE	ChildHiveReference;
};
};
/* off 0x002c */	unsigned long	Security;
/* off 0x0030 */	unsigned long	Class;
/* off 0x0034 */	unsigned long	MaxNameLen;
/* off 0x0038 */	unsigned long	MaxClassLen;
/* off 0x003c */	unsigned long	MaxValueNameLen;
/* off 0x0040 */	unsigned long	MaxValueDataLen;
/* off 0x0044 */	unsigned long	WorkVar;
/* off 0x0048 */	unsigned short	NameLength;
/* off 0x004a */	unsigned short	ClassLength;
/* off 0x004c */	unsigned short Name[1];
};
struct _CM_KEY_VALUE /* sizeof 00000018 24 */
{
/* off 0x0000 */	unsigned short	Signature;
/* off 0x0002 */	unsigned short	NameLength;
/* off 0x0004 */	unsigned long	DataLength;
/* off 0x0008 */	unsigned long	Data;
/* off 0x000c */	unsigned long	Type;
/* off 0x0010 */	unsigned short	Flags;
/* off 0x0012 */	unsigned short	Spare;
/* off 0x0014 */	unsigned short Name[1];
};
struct _SECURITY_DESCRIPTOR_RELATIVE /* sizeof 00000014 20 */
{
/* off 0x0000 */	unsigned char	Revision;
/* off 0x0001 */	unsigned char	Sbz1;
/* off 0x0002 */	unsigned short	Control;
/* off 0x0004 */	unsigned long	Owner;
/* off 0x0008 */	unsigned long	Group;
/* off 0x000c */	unsigned long	Sacl;
/* off 0x0010 */	unsigned long	Dacl;
};
struct _CM_KEY_SECURITY /* sizeof 00000028 40 */
{
/* off 0x0000 */	unsigned short	Signature;
/* off 0x0002 */	unsigned short	Reserved;
/* off 0x0004 */	unsigned long	Flink;
/* off 0x0008 */	unsigned long	Blink;
/* off 0x000c */	unsigned long	ReferenceCount;
/* off 0x0010 */	unsigned long	DescriptorLength;
/* off 0x0014 */	struct _SECURITY_DESCRIPTOR_RELATIVE	Descriptor;
};
struct _CM_KEY_INDEX /* sizeof 00000008 8 */
{
/* off 0x0000 */	unsigned short	Signature;
/* off 0x0002 */	unsigned short	Count;
/* off 0x0004 */	unsigned long List[1];
};
struct _CM_BIG_DATA /* sizeof 00000008 8 */
{
/* off 0x0000 */	unsigned short	Signature;
/* off 0x0002 */	unsigned short	Count;
/* off 0x0004 */	unsigned long	List;
};
union _u /* sizeof 00000050 80 */
{
/* off 0x0000 */	struct _CM_KEY_NODE	KeyNode;
/* off 0x0000 */	struct _CM_KEY_VALUE	KeyValue;
/* off 0x0000 */	struct _CM_KEY_SECURITY	KeySecurity;
/* off 0x0000 */	struct _CM_KEY_INDEX	KeyIndex;
/* off 0x0000 */	struct _CM_BIG_DATA	ValueData;
/* off 0x0000 */	unsigned long KeyList[1];
/* off 0x0000 */	unsigned short KeyString[1];
};
struct _CELL_DATA /* sizeof 00000050 80 */
{
/* off 0x0000 */	union _u	u;
};
struct CMP_OFFSET_ARRAY /* sizeof 0000000c 12 */
{
/* off 0x0000 */	unsigned long	FileOffset;
/* off 0x0004 */	void*	DataBuffer;
/* off 0x0008 */	unsigned long	DataLength;
};
struct _HBASE_BLOCK /* sizeof 00001000 4096 */
{
/* off 0x0000 */	unsigned long	Signature;
/* off 0x0004 */	unsigned long	Sequence1;
/* off 0x0008 */	unsigned long	Sequence2;
/* off 0x000c */	union _LARGE_INTEGER	TimeStamp;
/* off 0x0014 */	unsigned long	Major;
/* off 0x0018 */	unsigned long	Minor;
/* off 0x001c */	unsigned long	Type;
/* off 0x0020 */	unsigned long	Format;
/* off 0x0024 */	unsigned long	RootCell;
/* off 0x0028 */	unsigned long	Length;
/* off 0x002c */	unsigned long	Cluster;
/* off 0x0030 */	unsigned char FileName[64];
/* off 0x0070 */	unsigned long Reserved1[99];
/* off 0x01fc */	unsigned long	CheckSum;
/* off 0x0200 */	unsigned long Reserved2[894];
/* off 0x0ff8 */	unsigned long	BootType;
/* off 0x0ffc */	unsigned long	BootRecover;
};
struct _HMAP_DIRECTORY /* sizeof 00001000 4096 */
{
/* off 0x0000 */	struct _HMAP_TABLE* Directory[1024];
};
struct _CM_KEY_SECURITY_CACHE_ENTRY /* sizeof 00000008 8 */
{
/* off 0x0000 */	unsigned long	Cell;
/* off 0x0004 */	struct _CM_KEY_SECURITY_CACHE*	CachedSecurity;
};
struct _CM_KEY_SECURITY_CACHE /* sizeof 00000028 40 */
{
/* off 0x0000 */	unsigned long	Cell;
/* off 0x0004 */	unsigned long	ConvKey;
/* off 0x0008 */	struct _LIST_ENTRY	List;
/* off 0x0010 */	unsigned long	DescriptorLength;
/* off 0x0014 */	struct _SECURITY_DESCRIPTOR_RELATIVE	Descriptor;
};
struct _CM_KEY_HASH /* sizeof 00000010 16 */
{
/* off 0x0000 */	unsigned long	ConvKey;
/* off 0x0004 */	struct _CM_KEY_HASH*	NextHash;
/* off 0x0008 */	struct _HHIVE*	KeyHive;
/* off 0x000c */	unsigned long	KeyCell;
};
struct _CACHED_CHILD_LIST /* sizeof 00000008 8 */
{
/* off 0x0000 */	unsigned long	Count;
union
{
/* off 0x0004 */	unsigned long	ValueList;
/* off 0x0004 */	struct _CM_KEY_CONTROL_BLOCK*	RealKcb;
};
};
struct _CM_KEY_CONTROL_BLOCK /* sizeof 00000048 72 */
{
/* off 0x0000 */	unsigned short	RefCount;
/* off 0x0002 */	unsigned short	Flags;
/* off 0x0004 */	unsigned long	ExtFlags:8	 /* start bit 0 */;
/* off 0x0004 */	unsigned long	PrivateAlloc:1	 /* start bit 8 */;
/* off 0x0004 */	unsigned long	Delete:1	 /* start bit 9 */;
/* off 0x0004 */	unsigned long	DelayedCloseIndex:12	 /* start bit 10 */;
/* off 0x0004 */	unsigned long	TotalLevels:10	 /* start bit 22 */;
union
{
/* off 0x0008 */	struct _CM_KEY_HASH	KeyHash;
struct
{
/* off 0x0008 */	unsigned long	ConvKey;
/* off 0x000c */	struct _CM_KEY_HASH*	NextHash;
/* off 0x0010 */	struct _HHIVE*	KeyHive;
/* off 0x0014 */	unsigned long	KeyCell;
};
};
/* off 0x0018 */	struct _CM_KEY_CONTROL_BLOCK*	ParentKcb;
/* off 0x001c */	struct _CM_NAME_CONTROL_BLOCK*	NameBlock;
/* off 0x0020 */	struct _CM_KEY_SECURITY_CACHE*	CachedSecurity;
/* off 0x0024 */	struct _CACHED_CHILD_LIST	ValueCache;
union
{
/* off 0x002c */	struct _CM_INDEX_HINT_BLOCK*	IndexHint;
/* off 0x002c */	unsigned long	HashKey;
/* off 0x002c */	unsigned long	SubKeyCount;
};
union
{
/* off 0x0030 */	struct _LIST_ENTRY	KeyBodyListHead;
/* off 0x0030 */	struct _LIST_ENTRY	FreeListEntry;
};
/* off 0x0038 */	union _LARGE_INTEGER	KcbLastWriteTime;
/* off 0x0040 */	unsigned short	KcbMaxNameLen;
/* off 0x0042 */	unsigned short	KcbMaxValueNameLen;
/* off 0x0044 */	unsigned long	KcbMaxValueDataLen;
};
struct _CM_NAME_HASH /* sizeof 0000000c 12 */
{
/* off 0x0000 */	unsigned long	ConvKey;
/* off 0x0004 */	struct _CM_NAME_HASH*	NextHash;
/* off 0x0008 */	unsigned short	NameLength;
/* off 0x000a */	unsigned short Name[1];
};
struct _CM_NAME_CONTROL_BLOCK /* sizeof 00000010 16 */
{
/* off 0x0000 */	unsigned char	Compressed;
/* off 0x0002 */	unsigned short	RefCount;
union
{
/* off 0x0004 */	struct _CM_NAME_HASH	NameHash;
struct
{
/* off 0x0004 */	unsigned long	ConvKey;
/* off 0x0008 */	struct _CM_KEY_HASH*	NextHash;
/* off 0x000c */	unsigned short	NameLength;
/* off 0x000e */	unsigned short Name[1];
};
};
};
struct _CM_INDEX_HINT_BLOCK /* sizeof 00000008 8 */
{
/* off 0x0000 */	unsigned long	Count;
/* off 0x0004 */	unsigned long HashKey[1];
};
struct _WORK_QUEUE_ITEM /* sizeof 00000010 16 */
{
/* off 0x0000 */	struct _LIST_ENTRY	List;
/* off 0x0008 */	void( __cdecl *WorkerRoutine)(void*);
/* off 0x000c */	void*	Parameter;
};
struct _CM_CELL_REMAP_BLOCK /* sizeof 00000008 8 */
{
/* off 0x0000 */	unsigned long	OldCell;
/* off 0x0004 */	unsigned long	NewCell;
};
struct _DEVICE_NODE /* sizeof 00000118 280 */
{
/* off 0x0000 */	struct _DEVICE_NODE*	Sibling;
/* off 0x0004 */	struct _DEVICE_NODE*	Child;
/* off 0x0008 */	struct _DEVICE_NODE*	Parent;
/* off 0x000c */	struct _DEVICE_NODE*	LastChild;
/* off 0x0010 */	unsigned long	Level;
/* off 0x0014 */	struct _PO_DEVICE_NOTIFY*	Notify;
/* off 0x0018 */	enum _PNP_DEVNODE_STATE	State;
/* off 0x001c */	enum _PNP_DEVNODE_STATE	PreviousState;
/* off 0x0020 */	enum _PNP_DEVNODE_STATE StateHistory[20];
/* off 0x0070 */	unsigned long	StateHistoryEntry;
/* off 0x0074 */	long	CompletionStatus;
/* off 0x0078 */	struct _IRP*	PendingIrp;
/* off 0x007c */	unsigned long	Flags;
/* off 0x0080 */	unsigned long	UserFlags;
/* off 0x0084 */	unsigned long	Problem;
/* off 0x0088 */	struct _DEVICE_OBJECT*	PhysicalDeviceObject;
/* off 0x008c */	struct _CM_RESOURCE_LIST*	ResourceList;
/* off 0x0090 */	struct _CM_RESOURCE_LIST*	ResourceListTranslated;
/* off 0x0094 */	struct _UNICODE_STRING	InstancePath;
/* off 0x009c */	struct _UNICODE_STRING	ServiceName;
/* off 0x00a4 */	struct _DEVICE_OBJECT*	DuplicatePDO;
/* off 0x00a8 */	struct _IO_RESOURCE_REQUIREMENTS_LIST*	ResourceRequirements;
/* off 0x00ac */	enum _INTERFACE_TYPE	InterfaceType;
/* off 0x00b0 */	unsigned long	BusNumber;
/* off 0x00b4 */	enum _INTERFACE_TYPE	ChildInterfaceType;
/* off 0x00b8 */	unsigned long	ChildBusNumber;
/* off 0x00bc */	unsigned short	ChildBusTypeIndex;
/* off 0x00be */	unsigned char	RemovalPolicy;
/* off 0x00bf */	unsigned char	HardwareRemovalPolicy;
/* off 0x00c0 */	struct _LIST_ENTRY	TargetDeviceNotify;
/* off 0x00c8 */	struct _LIST_ENTRY	DeviceArbiterList;
/* off 0x00d0 */	struct _LIST_ENTRY	DeviceTranslatorList;
/* off 0x00d8 */	unsigned short	NoTranslatorMask;
/* off 0x00da */	unsigned short	QueryTranslatorMask;
/* off 0x00dc */	unsigned short	NoArbiterMask;
/* off 0x00de */	unsigned short	QueryArbiterMask;
/* off 0x00e0 */	struct __unnamed	OverUsed1;
/* off 0x00e4 */	struct __unnamed	OverUsed2;
/* off 0x00e8 */	struct _CM_RESOURCE_LIST*	BootResources;
/* off 0x00ec */	unsigned long	CapabilityFlags;
/* off 0x00f0 */	struct __unnamed	DockInfo;
/* off 0x0100 */	unsigned long	DisableableDepends;
/* off 0x0104 */	struct _LIST_ENTRY	PendedSetInterfaceState;
/* off 0x010c */	struct _LIST_ENTRY	LegacyBusListEntry;
/* off 0x0114 */	unsigned long	DriverUnloadRetryCount;
};
struct _PO_DEVICE_NOTIFY /* sizeof 00000028 40 */
{
/* off 0x0000 */	struct _LIST_ENTRY	Link;
/* off 0x0008 */	struct _DEVICE_OBJECT*	TargetDevice;
/* off 0x000c */	unsigned char	WakeNeeded;
/* off 0x000d */	unsigned char	OrderLevel;
/* off 0x0010 */	struct _DEVICE_OBJECT*	DeviceObject;
/* off 0x0014 */	void*	Node;
/* off 0x0018 */	unsigned short*	DeviceName;
/* off 0x001c */	unsigned short*	DriverName;
/* off 0x0020 */	unsigned long	ChildCount;
/* off 0x0024 */	unsigned long	ActiveChild;
};
enum _PNP_DEVNODE_STATE
{
	DeviceNodeUnspecified	=0x00000300	,//0
	DeviceNodeUninitialized	=0x00000301	,//0
	DeviceNodeInitialized	=0x00000302	,//0
	DeviceNodeDriversAdded	=0x00000303	,//0
	DeviceNodeResourcesAssigned	=0x00000304	,//0
	DeviceNodeStartPending	=0x00000305	,//0
	DeviceNodeStartCompletion	=0x00000306	,//0
	DeviceNodeStartPostWork	=0x00000307	,//0
	DeviceNodeStarted	=0x00000308	,//0
	DeviceNodeQueryStopped	=0x00000309	,//0
	DeviceNodeStopped	=0x0000030a	,//0
	DeviceNodeRestartCompletion	=0x0000030b	,//0
	DeviceNodeEnumeratePending	=0x0000030c	,//0
	DeviceNodeEnumerateCompletion	=0x0000030d	,//0
	DeviceNodeAwaitingQueuedDeletion	=0x0000030e	,//0
	DeviceNodeAwaitingQueuedRemoval	=0x0000030f	,//0
	DeviceNodeQueryRemoved	=0x00000310	,//0
	DeviceNodeRemovePendingCloses	=0x00000311	,//0
	DeviceNodeRemoved	=0x00000312	,//0
	DeviceNodeDeletePendingCloses	=0x00000313	,//0
	DeviceNodeDeleted	=0x00000314	,//0
};
struct _CM_PARTIAL_RESOURCE_DESCRIPTOR /* sizeof 00000010 16 */
{
/* off 0x0000 */	unsigned char	Type;
/* off 0x0001 */	unsigned char	ShareDisposition;
/* off 0x0002 */	unsigned short	Flags;
/* off 0x0004 */	struct __unnamed	u;
};
struct _CM_PARTIAL_RESOURCE_LIST /* sizeof 00000018 24 */
{
/* off 0x0000 */	unsigned short	Version;
/* off 0x0002 */	unsigned short	Revision;
/* off 0x0004 */	unsigned long	Count;
/* off 0x0008 */	struct _CM_PARTIAL_RESOURCE_DESCRIPTOR PartialDescriptors[1];
};
struct _CM_FULL_RESOURCE_DESCRIPTOR /* sizeof 00000020 32 */
{
/* off 0x0000 */	enum _INTERFACE_TYPE	InterfaceType;
/* off 0x0004 */	unsigned long	BusNumber;
/* off 0x0008 */	struct _CM_PARTIAL_RESOURCE_LIST	PartialResourceList;
};
struct _CM_RESOURCE_LIST /* sizeof 00000024 36 */
{
/* off 0x0000 */	unsigned long	Count;
/* off 0x0004 */	struct _CM_FULL_RESOURCE_DESCRIPTOR List[1];
};
enum _INTERFACE_TYPE
{
	InterfaceTypeUndefined	=0xffffffff	,//-1
	Internal	=0x00000000	,//0
	Isa	=0x00000001	,//0
	Eisa	=0x00000002	,//0
	MicroChannel	=0x00000003	,//0
	TurboChannel	=0x00000004	,//0
	PCIBus	=0x00000005	,//0
	VMEBus	=0x00000006	,//0
	NuBus	=0x00000007	,//0
	PCMCIABus	=0x00000008	,//0
	CBus	=0x00000009	,//0
	MPIBus	=0x0000000a	,//0
	MPSABus	=0x0000000b	,//0
	ProcessorInternal	=0x0000000c	,//0
	InternalPowerBus	=0x0000000d	,//0
	PNPISABus	=0x0000000e	,//0
	PNPBus	=0x0000000f	,//0
	MaximumInterfaceType	=0x00000010	,//0
};
struct _IO_RESOURCE_DESCRIPTOR /* sizeof 00000020 32 */
{
/* off 0x0000 */	unsigned char	Option;
/* off 0x0001 */	unsigned char	Type;
/* off 0x0002 */	unsigned char	ShareDisposition;
/* off 0x0003 */	unsigned char	Spare1;
/* off 0x0004 */	unsigned short	Flags;
/* off 0x0006 */	unsigned short	Spare2;
/* off 0x0008 */	struct __unnamed	u;
};
struct _IO_RESOURCE_LIST /* sizeof 00000028 40 */
{
/* off 0x0000 */	unsigned short	Version;
/* off 0x0002 */	unsigned short	Revision;
/* off 0x0004 */	unsigned long	Count;
/* off 0x0008 */	struct _IO_RESOURCE_DESCRIPTOR Descriptors[1];
};
struct _IO_RESOURCE_REQUIREMENTS_LIST /* sizeof 00000048 72 */
{
/* off 0x0000 */	unsigned long	ListSize;
/* off 0x0004 */	enum _INTERFACE_TYPE	InterfaceType;
/* off 0x0008 */	unsigned long	BusNumber;
/* off 0x000c */	unsigned long	SlotNumber;
/* off 0x0010 */	unsigned long Reserved[3];
/* off 0x001c */	unsigned long	AlternativeLists;
/* off 0x0020 */	struct _IO_RESOURCE_LIST List[1];
};
struct _DEVICE_RELATIONS /* sizeof 00000008 8 */
{
/* off 0x0000 */	unsigned long	Count;
/* off 0x0004 */	struct _DEVICE_OBJECT* Objects[1];
};
enum PROFILE_STATUS
{
	DOCK_NOTDOCKDEVICE	=0x00000000	,//0
	DOCK_QUIESCENT	=0x00000001	,//0
	DOCK_ARRIVING	=0x00000002	,//0
	DOCK_DEPARTING	=0x00000003	,//0
	DOCK_EJECTIRP_COMPLETED	=0x00000004	,//0
};
struct _NT_TIB /* sizeof 0000001c 28 */
{
/* off 0x0000 */	struct _EXCEPTION_REGISTRATION_RECORD*	ExceptionList;
/* off 0x0004 */	void*	StackBase;
/* off 0x0008 */	void*	StackLimit;
/* off 0x000c */	void*	SubSystemTib;
union
{
/* off 0x0010 */	void*	FiberData;
/* off 0x0010 */	unsigned long	Version;
};
/* off 0x0014 */	void*	ArbitraryUserPointer;
/* off 0x0018 */	struct _NT_TIB*	Self;
};
struct _KPCR /* sizeof 00000d70 3440 */
{
/* off 0x0000 */	struct _NT_TIB	NtTib;
/* off 0x001c */	struct _KPCR*	SelfPcr;
/* off 0x0020 */	struct _KPRCB*	Prcb;
/* off 0x0024 */	unsigned char	Irql;
/* off 0x0028 */	unsigned long	IRR;
/* off 0x002c */	unsigned long	IrrActive;
/* off 0x0030 */	unsigned long	IDR;
/* off 0x0034 */	void*	KdVersionBlock;
/* off 0x0038 */	struct _KIDTENTRY*	IDT;
/* off 0x003c */	struct _KGDTENTRY*	GDT;
/* off 0x0040 */	struct _KTSS*	TSS;
/* off 0x0044 */	unsigned short	MajorVersion;
/* off 0x0046 */	unsigned short	MinorVersion;
/* off 0x0048 */	unsigned long	SetMember;
/* off 0x004c */	unsigned long	StallScaleFactor;
/* off 0x0050 */	unsigned char	DebugActive;
/* off 0x0051 */	unsigned char	Number;
/* off 0x0052 */	unsigned char	Spare0;
/* off 0x0053 */	unsigned char	SecondLevelCacheAssociativity;
/* off 0x0054 */	unsigned long	VdmAlert;
/* off 0x0058 */	unsigned long KernelReserved[14];
/* off 0x0090 */	unsigned long	SecondLevelCacheSize;
/* off 0x0094 */	unsigned long HalReserved[16];
/* off 0x00d4 */	unsigned long	InterruptMode;
/* off 0x00d8 */	unsigned char	Spare1;
/* off 0x00dc */	unsigned long KernelReserved2[17];
/* off 0x0120 */	struct _KPRCB	PrcbData;
};
struct _KiIoAccessMap /* sizeof 00002024 8228 */
{
/* off 0x0000 */	unsigned char DirectionMap[32];
/* off 0x0020 */	unsigned char IoMap[8196];
};
struct _KTSS /* sizeof 000020ac 8364 */
{
/* off 0x0000 */	unsigned short	Backlink;
/* off 0x0002 */	unsigned short	Reserved0;
/* off 0x0004 */	unsigned long	Esp0;
/* off 0x0008 */	unsigned short	Ss0;
/* off 0x000a */	unsigned short	Reserved1;
/* off 0x000c */	unsigned long NotUsed1[4];
/* off 0x001c */	unsigned long	CR3;
/* off 0x0020 */	unsigned long	Eip;
/* off 0x0024 */	unsigned long	EFlags;
/* off 0x0028 */	unsigned long	Eax;
/* off 0x002c */	unsigned long	Ecx;
/* off 0x0030 */	unsigned long	Edx;
/* off 0x0034 */	unsigned long	Ebx;
/* off 0x0038 */	unsigned long	Esp;
/* off 0x003c */	unsigned long	Ebp;
/* off 0x0040 */	unsigned long	Esi;
/* off 0x0044 */	unsigned long	Edi;
/* off 0x0048 */	unsigned short	Es;
/* off 0x004a */	unsigned short	Reserved2;
/* off 0x004c */	unsigned short	Cs;
/* off 0x004e */	unsigned short	Reserved3;
/* off 0x0050 */	unsigned short	Ss;
/* off 0x0052 */	unsigned short	Reserved4;
/* off 0x0054 */	unsigned short	Ds;
/* off 0x0056 */	unsigned short	Reserved5;
/* off 0x0058 */	unsigned short	Fs;
/* off 0x005a */	unsigned short	Reserved6;
/* off 0x005c */	unsigned short	Gs;
/* off 0x005e */	unsigned short	Reserved7;
/* off 0x0060 */	unsigned short	LDT;
/* off 0x0062 */	unsigned short	Reserved8;
/* off 0x0064 */	unsigned short	Flags;
/* off 0x0066 */	unsigned short	IoMapBase;
/* off 0x0068 */	struct _KiIoAccessMap IoMaps[1];
/* off 0x208c */	unsigned char IntDirectionMap[32];
};
struct _MMCOLOR_TABLES /* sizeof 0000000c 12 */
{
/* off 0x0000 */	unsigned long	Flink;
/* off 0x0004 */	void*	Blink;
/* off 0x0008 */	unsigned long	Count;
};
struct _PHYSICAL_MEMORY_RUN /* sizeof 00000008 8 */
{
/* off 0x0000 */	unsigned long	BasePage;
/* off 0x0004 */	unsigned long	PageCount;
};
struct _MM_PAGED_POOL_INFO /* sizeof 00000024 36 */
{
/* off 0x0000 */	struct _RTL_BITMAP*	PagedPoolAllocationMap;
/* off 0x0004 */	struct _RTL_BITMAP*	EndOfPagedPoolBitmap;
/* off 0x0008 */	struct _RTL_BITMAP*	PagedPoolLargeSessionAllocationMap;
/* off 0x000c */	struct _MMPTE*	FirstPteForPagedPool;
/* off 0x0010 */	struct _MMPTE*	LastPteForPagedPool;
/* off 0x0014 */	struct _MMPTE*	NextPdeForPagedPoolExpansion;
/* off 0x0018 */	unsigned long	PagedPoolHint;
/* off 0x001c */	unsigned long	PagedPoolCommit;
/* off 0x0020 */	unsigned long	AllocatedPagedPool;
};
struct _MMSESSION /* sizeof 0000003c 60 */
{
/* off 0x0000 */	struct _FAST_MUTEX	SystemSpaceViewLock;
/* off 0x0020 */	struct _FAST_MUTEX*	SystemSpaceViewLockPointer;
/* off 0x0024 */	char*	SystemSpaceViewStart;
/* off 0x0028 */	struct _MMVIEW*	SystemSpaceViewTable;
/* off 0x002c */	unsigned long	SystemSpaceHashSize;
/* off 0x0030 */	unsigned long	SystemSpaceHashEntries;
/* off 0x0034 */	unsigned long	SystemSpaceHashKey;
/* off 0x0038 */	struct _RTL_BITMAP*	SystemSpaceBitMap;
};
struct _POOL_DESCRIPTOR /* sizeof 00001028 4136 */
{
/* off 0x0000 */	enum _POOL_TYPE	PoolType;
/* off 0x0004 */	unsigned long	PoolIndex;
/* off 0x0008 */	unsigned long	RunningAllocs;
/* off 0x000c */	unsigned long	RunningDeAllocs;
/* off 0x0010 */	unsigned long	TotalPages;
/* off 0x0014 */	unsigned long	TotalBigPages;
/* off 0x0018 */	unsigned long	Threshold;
/* off 0x001c */	void*	LockAddress;
/* off 0x0020 */	void*	PendingFrees;
/* off 0x0024 */	long	PendingFreeDepth;
/* off 0x0028 */	struct _LIST_ENTRY ListHeads[512];
};
struct _MM_SESSION_SPACE /* sizeof 00001278 4728 */
{
/* off 0x0000 */	unsigned long	ReferenceCount;
/* off 0x0004 */	struct __unnamed	u;
/* off 0x0008 */	unsigned long	SessionId;
/* off 0x000c */	unsigned long	SessionPageDirectoryIndex;
/* off 0x0010 */	struct _MM_SESSION_SPACE*	GlobalVirtualAddress;
/* off 0x0014 */	struct _LIST_ENTRY	ProcessList;
/* off 0x001c */	unsigned long	NonPagedPoolBytes;
/* off 0x0020 */	unsigned long	PagedPoolBytes;
/* off 0x0024 */	unsigned long	NonPagedPoolAllocations;
/* off 0x0028 */	unsigned long	PagedPoolAllocations;
/* off 0x002c */	unsigned long	NonPagablePages;
/* off 0x0030 */	unsigned long	CommittedPages;
/* off 0x0038 */	union _LARGE_INTEGER	LastProcessSwappedOutTime;
/* off 0x0040 */	struct _MMPTE*	PageTables;
/* off 0x0044 */	struct _FAST_MUTEX	PagedPoolMutex;
/* off 0x0064 */	void*	PagedPoolStart;
/* off 0x0068 */	void*	PagedPoolEnd;
/* off 0x006c */	struct _MMPTE*	PagedPoolBasePde;
/* off 0x0070 */	struct _MM_PAGED_POOL_INFO	PagedPoolInfo;
/* off 0x0094 */	unsigned long	Color;
/* off 0x0098 */	unsigned long	ProcessOutSwapCount;
/* off 0x009c */	struct _LIST_ENTRY	ImageList;
/* off 0x00a4 */	struct _MMPTE*	GlobalPteEntry;
/* off 0x00a8 */	unsigned long	CopyOnWriteCount;
/* off 0x00ac */	unsigned long SessionPoolAllocationFailures[4];
/* off 0x00bc */	unsigned long	AttachCount;
/* off 0x00c0 */	struct _KEVENT	AttachEvent;
/* off 0x00d0 */	struct _EPROCESS*	LastProcess;
/* off 0x00d8 */	struct _MMSUPPORT	Vm;
/* off 0x0118 */	struct _MMWSLE*	Wsle;
/* off 0x011c */	struct _ERESOURCE	WsLock;
/* off 0x0154 */	struct _LIST_ENTRY	WsListEntry;
/* off 0x015c */	struct _MMSESSION	Session;
/* off 0x0198 */	struct _DRIVER_OBJECT	Win32KDriverObject;
/* off 0x0240 */	struct _ETHREAD*	WorkingSetLockOwner;
/* off 0x0244 */	struct _POOL_DESCRIPTOR	PagedPool;
/* off 0x126c */	long	ProcessReferenceToSession;
/* off 0x1270 */	unsigned long	LocaleId;
};
struct _MMVIEW /* sizeof 00000008 8 */
{
/* off 0x0000 */	unsigned long	Entry;
/* off 0x0004 */	struct _CONTROL_AREA*	ControlArea;
};
struct _MM_SESSION_SPACE_FLAGS /* sizeof 00000004 4 */
{
/* off 0x0000 */	unsigned long	Initialized:1	 /* start bit 0 */;
/* off 0x0000 */	unsigned long	Filler0:3	 /* start bit 1 */;
/* off 0x0000 */	unsigned long	HasWsLock:1	 /* start bit 4 */;
/* off 0x0000 */	unsigned long	DeletePending:1	 /* start bit 5 */;
/* off 0x0000 */	unsigned long	Filler:26	 /* start bit 6 */;
};
struct _HEAP_FREE_ENTRY /* sizeof 00000010 16 */
{
union
{
struct
{
/* off 0x0000 */	unsigned short	Size;
/* off 0x0002 */	unsigned short	PreviousSize;
};
struct
{
/* off 0x0000 */	void*	SubSegmentCode;
};
};
/* off 0x0004 */	unsigned char	SmallTagIndex;
/* off 0x0005 */	unsigned char	Flags;
/* off 0x0006 */	unsigned char	UnusedBytes;
/* off 0x0007 */	unsigned char	SegmentIndex;
/* off 0x0008 */	struct _LIST_ENTRY	FreeList;
};
struct _MMPTE_HARDWARE /* sizeof 00000004 4 */
{
/* off 0x0000 */	unsigned long	Valid:1	 /* start bit 0 */;
/* off 0x0000 */	unsigned long	Writable:1	 /* start bit 1 */;
/* off 0x0000 */	unsigned long	Owner:1	 /* start bit 2 */;
/* off 0x0000 */	unsigned long	WriteThrough:1	 /* start bit 3 */;
/* off 0x0000 */	unsigned long	CacheDisable:1	 /* start bit 4 */;
/* off 0x0000 */	unsigned long	Accessed:1	 /* start bit 5 */;
/* off 0x0000 */	unsigned long	Dirty:1	 /* start bit 6 */;
/* off 0x0000 */	unsigned long	LargePage:1	 /* start bit 7 */;
/* off 0x0000 */	unsigned long	Global:1	 /* start bit 8 */;
/* off 0x0000 */	unsigned long	CopyOnWrite:1	 /* start bit 9 */;
/* off 0x0000 */	unsigned long	Prototype:1	 /* start bit 10 */;
/* off 0x0000 */	unsigned long	Write:1	 /* start bit 11 */;
/* off 0x0000 */	unsigned long	PageFrameNumber:20	 /* start bit 12 */;
};
struct _MMPTE_PROTOTYPE /* sizeof 00000004 4 */
{
/* off 0x0000 */	unsigned long	Valid:1	 /* start bit 0 */;
/* off 0x0000 */	unsigned long	ProtoAddressLow:7	 /* start bit 1 */;
/* off 0x0000 */	unsigned long	ReadOnly:1	 /* start bit 8 */;
/* off 0x0000 */	unsigned long	WhichPool:1	 /* start bit 9 */;
/* off 0x0000 */	unsigned long	Prototype:1	 /* start bit 10 */;
/* off 0x0000 */	unsigned long	ProtoAddressHigh:21	 /* start bit 11 */;
};
struct _MMPTE_SOFTWARE /* sizeof 00000004 4 */
{
/* off 0x0000 */	unsigned long	Valid:1	 /* start bit 0 */;
/* off 0x0000 */	unsigned long	PageFileLow:4	 /* start bit 1 */;
/* off 0x0000 */	unsigned long	Protection:5	 /* start bit 5 */;
/* off 0x0000 */	unsigned long	Prototype:1	 /* start bit 10 */;
/* off 0x0000 */	unsigned long	Transition:1	 /* start bit 11 */;
/* off 0x0000 */	unsigned long	PageFileHigh:20	 /* start bit 12 */;
};
struct _MMPTE_TRANSITION /* sizeof 00000004 4 */
{
/* off 0x0000 */	unsigned long	Valid:1	 /* start bit 0 */;
/* off 0x0000 */	unsigned long	Write:1	 /* start bit 1 */;
/* off 0x0000 */	unsigned long	Owner:1	 /* start bit 2 */;
/* off 0x0000 */	unsigned long	WriteThrough:1	 /* start bit 3 */;
/* off 0x0000 */	unsigned long	CacheDisable:1	 /* start bit 4 */;
/* off 0x0000 */	unsigned long	Protection:5	 /* start bit 5 */;
/* off 0x0000 */	unsigned long	Prototype:1	 /* start bit 10 */;
/* off 0x0000 */	unsigned long	Transition:1	 /* start bit 11 */;
/* off 0x0000 */	unsigned long	PageFrameNumber:20	 /* start bit 12 */;
};
struct _MMPTE_SUBSECTION /* sizeof 00000004 4 */
{
/* off 0x0000 */	unsigned long	Valid:1	 /* start bit 0 */;
/* off 0x0000 */	unsigned long	SubsectionAddressLow:4	 /* start bit 1 */;
/* off 0x0000 */	unsigned long	Protection:5	 /* start bit 5 */;
/* off 0x0000 */	unsigned long	Prototype:1	 /* start bit 10 */;
/* off 0x0000 */	unsigned long	SubsectionAddressHigh:20	 /* start bit 11 */;
/* off 0x0000 */	unsigned long	WhichPool:1	 /* start bit 31 */;
};
struct _MMPTE_LIST /* sizeof 00000004 4 */
{
/* off 0x0000 */	unsigned long	Valid:1	 /* start bit 0 */;
/* off 0x0000 */	unsigned long	OneEntry:1	 /* start bit 1 */;
/* off 0x0000 */	unsigned long	filler0:8	 /* start bit 2 */;
/* off 0x0000 */	unsigned long	Prototype:1	 /* start bit 10 */;
/* off 0x0000 */	unsigned long	filler1:1	 /* start bit 11 */;
/* off 0x0000 */	unsigned long	NextEntry:20	 /* start bit 12 */;
};
struct _CM_CACHED_VALUE_INDEX /* sizeof 00000054 84 */
{
/* off 0x0000 */	unsigned long	CellIndex;
/* off 0x0004 */	struct __unnamed	Data;
};
struct POWER_ACTION_POLICY /* sizeof 0000000c 12 */
{
/* off 0x0000 */	enum POWER_ACTION	Action;
/* off 0x0004 */	unsigned long	Flags;
/* off 0x0008 */	unsigned long	EventCode;
};
struct SYSTEM_POWER_LEVEL /* sizeof 00000018 24 */
{
/* off 0x0000 */	unsigned char	Enable;
/* off 0x0001 */	unsigned char Spare[3];
/* off 0x0004 */	unsigned long	BatteryLevel;
/* off 0x0008 */	struct POWER_ACTION_POLICY	PowerPolicy;
/* off 0x0014 */	enum _SYSTEM_POWER_STATE	MinSystemState;
};
struct _SYSTEM_POWER_POLICY /* sizeof 000000e8 232 */
{
/* off 0x0000 */	unsigned long	Revision;
/* off 0x0004 */	struct POWER_ACTION_POLICY	PowerButton;
/* off 0x0010 */	struct POWER_ACTION_POLICY	SleepButton;
/* off 0x001c */	struct POWER_ACTION_POLICY	LidClose;
/* off 0x0028 */	enum _SYSTEM_POWER_STATE	LidOpenWake;
/* off 0x002c */	unsigned long	Reserved;
/* off 0x0030 */	struct POWER_ACTION_POLICY	Idle;
/* off 0x003c */	unsigned long	IdleTimeout;
/* off 0x0040 */	unsigned char	IdleSensitivity;
/* off 0x0041 */	unsigned char	DynamicThrottle;
/* off 0x0042 */	unsigned char Spare2[2];
/* off 0x0044 */	enum _SYSTEM_POWER_STATE	MinSleep;
/* off 0x0048 */	enum _SYSTEM_POWER_STATE	MaxSleep;
/* off 0x004c */	enum _SYSTEM_POWER_STATE	ReducedLatencySleep;
/* off 0x0050 */	unsigned long	WinLogonFlags;
/* off 0x0054 */	unsigned long	Spare3;
/* off 0x0058 */	unsigned long	DozeS4Timeout;
/* off 0x005c */	unsigned long	BroadcastCapacityResolution;
/* off 0x0060 */	struct SYSTEM_POWER_LEVEL DischargePolicy[4];
/* off 0x00c0 */	unsigned long	VideoTimeout;
/* off 0x00c4 */	unsigned char	VideoDimDisplay;
/* off 0x00c8 */	unsigned long VideoReserved[3];
/* off 0x00d4 */	unsigned long	SpindownTimeout;
/* off 0x00d8 */	unsigned char	OptimizeForPower;
/* off 0x00d9 */	unsigned char	FanThrottleTolerance;
/* off 0x00da */	unsigned char	ForcedThrottle;
/* off 0x00db */	unsigned char	MinThrottle;
/* off 0x00dc */	struct POWER_ACTION_POLICY	OverThrottled;
};
enum POWER_ACTION
{
	PowerActionNone	=0x00000000	,//0
	PowerActionReserved	=0x00000001	,//0
	PowerActionSleep	=0x00000002	,//0
	PowerActionHibernate	=0x00000003	,//0
	PowerActionShutdown	=0x00000004	,//0
	PowerActionShutdownReset	=0x00000005	,//0
	PowerActionShutdownOff	=0x00000006	,//0
	PowerActionWarmEject	=0x00000007	,//0
};
enum LSA_FOREST_TRUST_RECORD_TYPE
{
	ForestTrustTopLevelName	=0x00000000	,//0
	ForestTrustTopLevelNameEx	=0x00000001	,//0
	ForestTrustDomainInfo	=0x00000002	,//0
	ForestTrustRecordTypeLast	=0x00000002	,//0
};
struct _POP_ACTION_TRIGGER /* sizeof 0000000c 12 */
{
/* off 0x0000 */	enum POP_POLICY_DEVICE_TYPE	Type;
/* off 0x0004 */	unsigned char	Flags;
/* off 0x0005 */	unsigned char Spare[3];
union
{
/* off 0x0008 */	struct __unnamed	Battery;
/* off 0x0008 */	struct _POP_TRIGGER_WAIT*	Wait;
};
};
struct _POP_THERMAL_ZONE /* sizeof 000000d0 208 */
{
/* off 0x0000 */	struct _LIST_ENTRY	Link;
/* off 0x0008 */	unsigned char	State;
/* off 0x0009 */	unsigned char	Flags;
/* off 0x000a */	unsigned char	Mode;
/* off 0x000b */	unsigned char	PendingMode;
/* off 0x000c */	unsigned char	ActivePoint;
/* off 0x000d */	unsigned char	PendingActivePoint;
/* off 0x0010 */	long	Throttle;
/* off 0x0018 */	unsigned __int64	LastTime;
/* off 0x0020 */	unsigned long	SampleRate;
/* off 0x0024 */	unsigned long	LastTemp;
/* off 0x0028 */	struct _KTIMER	PassiveTimer;
/* off 0x0050 */	struct _KDPC	PassiveDpc;
/* off 0x0070 */	struct _POP_ACTION_TRIGGER	OverThrottled;
/* off 0x007c */	struct _IRP*	Irp;
/* off 0x0080 */	struct _THERMAL_INFORMATION	Info;
};
enum POP_POLICY_DEVICE_TYPE
{
	PolicyDeviceSystemButton	=0x00000000	,//0
	PolicyDeviceThermalZone	=0x00000001	,//0
	PolicyDeviceBattery	=0x00000002	,//0
	PolicyInitiatePowerActionAPI	=0x00000003	,//0
	PolicySetPowerStateAPI	=0x00000004	,//0
	PolicyImmediateDozeS4	=0x00000005	,//0
	PolicySystemIdle	=0x00000006	,//0
};
struct _POP_TRIGGER_WAIT /* sizeof 00000020 32 */
{
/* off 0x0000 */	struct _KEVENT	Event;
/* off 0x0010 */	long	Status;
/* off 0x0014 */	struct _LIST_ENTRY	Link;
/* off 0x001c */	struct _POP_ACTION_TRIGGER*	Trigger;
};
struct _PROCESSOR_POWER_POLICY_INFO /* sizeof 00000014 20 */
{
/* off 0x0000 */	unsigned long	TimeCheck;
/* off 0x0004 */	unsigned long	DemoteLimit;
/* off 0x0008 */	unsigned long	PromoteLimit;
/* off 0x000c */	unsigned char	DemotePercent;
/* off 0x000d */	unsigned char	PromotePercent;
/* off 0x000e */	unsigned char Spare[2];
/* off 0x0010 */	unsigned long	AllowDemotion:1	 /* start bit 0 */;
/* off 0x0010 */	unsigned long	AllowPromotion:1	 /* start bit 1 */;
/* off 0x0010 */	unsigned long	Reserved:30	 /* start bit 2 */;
};
struct _PROCESSOR_POWER_POLICY /* sizeof 0000004c 76 */
{
/* off 0x0000 */	unsigned long	Revision;
/* off 0x0004 */	unsigned char	DynamicThrottle;
/* off 0x0005 */	unsigned char Spare[3];
/* off 0x0008 */	unsigned long	DisableCStates:1	 /* start bit 0 */;
/* off 0x0008 */	unsigned long	Reserved:31	 /* start bit 1 */;
/* off 0x000c */	unsigned long	PolicyCount;
/* off 0x0010 */	struct _PROCESSOR_POWER_POLICY_INFO Policy[3];
};
struct _IMAGE_DOS_HEADER /* sizeof 00000040 64 */
{
/* off 0x0000 */	unsigned short	e_magic;
/* off 0x0002 */	unsigned short	e_cblp;
/* off 0x0004 */	unsigned short	e_cp;
/* off 0x0006 */	unsigned short	e_crlc;
/* off 0x0008 */	unsigned short	e_cparhdr;
/* off 0x000a */	unsigned short	e_minalloc;
/* off 0x000c */	unsigned short	e_maxalloc;
/* off 0x000e */	unsigned short	e_ss;
/* off 0x0010 */	unsigned short	e_sp;
/* off 0x0012 */	unsigned short	e_csum;
/* off 0x0014 */	unsigned short	e_ip;
/* off 0x0016 */	unsigned short	e_cs;
/* off 0x0018 */	unsigned short	e_lfarlc;
/* off 0x001a */	unsigned short	e_ovno;
/* off 0x001c */	unsigned short e_res[4];
/* off 0x0024 */	unsigned short	e_oemid;
/* off 0x0026 */	unsigned short	e_oeminfo;
/* off 0x0028 */	unsigned short e_res2[10];
/* off 0x003c */	long	e_lfanew;
};
struct _HEAP_ENTRY_EXTRA /* sizeof 00000008 8 */
{
union
{
struct
{
/* off 0x0000 */	unsigned short	AllocatorBackTraceIndex;
/* off 0x0002 */	unsigned short	TagIndex;
/* off 0x0004 */	unsigned long	Settable;
};
/* off 0x0000 */	unsigned __int64	ZeroInit;
};
};
struct _HEAP_VIRTUAL_ALLOC_ENTRY /* sizeof 00000020 32 */
{
/* off 0x0000 */	struct _LIST_ENTRY	Entry;
/* off 0x0008 */	struct _HEAP_ENTRY_EXTRA	ExtraStuff;
/* off 0x0010 */	unsigned long	CommitSize;
/* off 0x0014 */	unsigned long	ReserveSize;
/* off 0x0018 */	struct _HEAP_ENTRY	BusyBlock;
};
struct _RTL_HANDLE_TABLE /* sizeof 00000020 32 */
{
/* off 0x0000 */	unsigned long	MaximumNumberOfHandles;
/* off 0x0004 */	unsigned long	SizeOfHandleTableEntry;
/* off 0x0008 */	unsigned long Reserved[2];
/* off 0x0010 */	struct _RTL_HANDLE_TABLE_ENTRY*	FreeHandles;
/* off 0x0014 */	struct _RTL_HANDLE_TABLE_ENTRY*	CommittedHandles;
/* off 0x0018 */	struct _RTL_HANDLE_TABLE_ENTRY*	UnCommittedHandles;
/* off 0x001c */	struct _RTL_HANDLE_TABLE_ENTRY*	MaxReservedHandles;
};
struct _RTL_ATOM_TABLE /* sizeof 00000044 68 */
{
/* off 0x0000 */	unsigned long	Signature;
/* off 0x0004 */	struct _RTL_CRITICAL_SECTION	CriticalSection;
/* off 0x001c */	struct _RTL_HANDLE_TABLE	RtlHandleTable;
/* off 0x003c */	unsigned long	NumberOfBuckets;
/* off 0x0040 */	struct _RTL_ATOM_TABLE_ENTRY* Buckets[1];
};
struct _RTL_HANDLE_TABLE_ENTRY /* sizeof 00000004 4 */
{
union
{
/* off 0x0000 */	unsigned long	Flags;
/* off 0x0000 */	struct _RTL_HANDLE_TABLE_ENTRY*	NextFree;
};
};
struct _RTL_ATOM_TABLE_ENTRY /* sizeof 00000010 16 */
{
/* off 0x0000 */	struct _RTL_ATOM_TABLE_ENTRY*	HashLink;
/* off 0x0004 */	unsigned short	HandleIndex;
/* off 0x0006 */	unsigned short	Atom;
/* off 0x0008 */	unsigned short	ReferenceCount;
/* off 0x000a */	unsigned char	Flags;
/* off 0x000b */	unsigned char	NameLength;
/* off 0x000c */	unsigned short Name[1];
};
struct _IMAGE_ROM_OPTIONAL_HEADER /* sizeof 00000038 56 */
{
/* off 0x0000 */	unsigned short	Magic;
/* off 0x0002 */	unsigned char	MajorLinkerVersion;
/* off 0x0003 */	unsigned char	MinorLinkerVersion;
/* off 0x0004 */	unsigned long	SizeOfCode;
/* off 0x0008 */	unsigned long	SizeOfInitializedData;
/* off 0x000c */	unsigned long	SizeOfUninitializedData;
/* off 0x0010 */	unsigned long	AddressOfEntryPoint;
/* off 0x0014 */	unsigned long	BaseOfCode;
/* off 0x0018 */	unsigned long	BaseOfData;
/* off 0x001c */	unsigned long	BaseOfBss;
/* off 0x0020 */	unsigned long	GprMask;
/* off 0x0024 */	unsigned long CprMask[4];
/* off 0x0034 */	unsigned long	GpValue;
};
enum _KWAIT_REASON
{
	Executive	=0x00000000	,//0
	FreePage	=0x00000001	,//0
	PageIn	=0x00000002	,//0
	PoolAllocation	=0x00000003	,//0
	DelayExecution	=0x00000004	,//0
	Suspended	=0x00000005	,//0
	UserRequest	=0x00000006	,//0
	WrExecutive	=0x00000007	,//0
	WrFreePage	=0x00000008	,//0
	WrPageIn	=0x00000009	,//0
	WrPoolAllocation	=0x0000000a	,//0
	WrDelayExecution	=0x0000000b	,//0
	WrSuspended	=0x0000000c	,//0
	WrUserRequest	=0x0000000d	,//0
	WrEventPair	=0x0000000e	,//0
	WrQueue	=0x0000000f	,//0
	WrLpcReceive	=0x00000010	,//0
	WrLpcReply	=0x00000011	,//0
	WrVirtualMemory	=0x00000012	,//0
	WrPageOut	=0x00000013	,//0
	WrRendezvous	=0x00000014	,//0
	Spare2	=0x00000015	,//0
	Spare3	=0x00000016	,//0
	Spare4	=0x00000017	,//0
	Spare5	=0x00000018	,//0
	Spare6	=0x00000019	,//0
	WrKernel	=0x0000001a	,//0
	MaximumWaitReason	=0x0000001b	,//0
};
struct _KDEVICE_QUEUE_ENTRY /* sizeof 00000010 16 */
{
/* off 0x0000 */	struct _LIST_ENTRY	DeviceListEntry;
/* off 0x0008 */	unsigned long	SortKey;
/* off 0x000c */	unsigned char	Inserted;
};
struct _WAIT_CONTEXT_BLOCK /* sizeof 00000028 40 */
{
/* off 0x0000 */	struct _KDEVICE_QUEUE_ENTRY	WaitQueueEntry;
/* off 0x0010 */	enum _IO_ALLOCATION_ACTION( __cdecl *DeviceRoutine)(struct _DEVICE_OBJECT*,struct _IRP*,void*,void*);
/* off 0x0014 */	void*	DeviceContext;
/* off 0x0018 */	unsigned long	NumberOfMapRegisters;
/* off 0x001c */	void*	DeviceObject;
/* off 0x0020 */	void*	CurrentIrp;
/* off 0x0024 */	struct _KDPC*	BufferChainingDpc;
};
enum _IO_ALLOCATION_ACTION
{
	KeepObject	=0x00000001	,//0
	DeallocateObject	=0x00000002	,//0
	DeallocateObjectKeepRegisters	=0x00000003	,//0
};
struct _KSYSTEM_TIME /* sizeof 0000000c 12 */
{
/* off 0x0000 */	unsigned long	LowPart;
/* off 0x0004 */	long	High1Time;
/* off 0x0008 */	long	High2Time;
};
struct _KUSER_SHARED_DATA /* sizeof 00000338 824 */
{
/* off 0x0000 */	unsigned long	TickCountLow;
/* off 0x0004 */	unsigned long	TickCountMultiplier;
/* off 0x0008 */	struct _KSYSTEM_TIME	InterruptTime;
/* off 0x0014 */	struct _KSYSTEM_TIME	SystemTime;
/* off 0x0020 */	struct _KSYSTEM_TIME	TimeZoneBias;
/* off 0x002c */	unsigned short	ImageNumberLow;
/* off 0x002e */	unsigned short	ImageNumberHigh;
/* off 0x0030 */	unsigned short NtSystemRoot[260];
/* off 0x0238 */	unsigned long	MaxStackTraceDepth;
/* off 0x023c */	unsigned long	CryptoExponent;
/* off 0x0240 */	unsigned long	TimeZoneId;
/* off 0x0244 */	unsigned long Reserved2[8];
/* off 0x0264 */	enum _NT_PRODUCT_TYPE	NtProductType;
/* off 0x0268 */	unsigned char	ProductTypeIsValid;
/* off 0x026c */	unsigned long	NtMajorVersion;
/* off 0x0270 */	unsigned long	NtMinorVersion;
/* off 0x0274 */	unsigned char ProcessorFeatures[64];
/* off 0x02b4 */	unsigned long	Reserved1;
/* off 0x02b8 */	unsigned long	Reserved3;
/* off 0x02bc */	unsigned long	TimeSlip;
/* off 0x02c0 */	enum _ALTERNATIVE_ARCHITECTURE_TYPE	AlternativeArchitecture;
/* off 0x02c8 */	union _LARGE_INTEGER	SystemExpirationDate;
/* off 0x02d0 */	unsigned long	SuiteMask;
/* off 0x02d4 */	unsigned char	KdDebuggerEnabled;
/* off 0x02d5 */	unsigned char	NXSupportPolicy;
/* off 0x02d8 */	unsigned long	ActiveConsoleId;
/* off 0x02dc */	unsigned long	DismountCount;
/* off 0x02e0 */	unsigned long	ComPlusPackage;
/* off 0x02e4 */	unsigned long	LastSystemRITEventTickCount;
/* off 0x02e8 */	unsigned long	NumberOfPhysicalPages;
/* off 0x02ec */	unsigned char	SafeBootMode;
/* off 0x02f0 */	unsigned long	TraceLogging;
/* off 0x02f8 */	unsigned __int64	TestRetInstruction;
/* off 0x0300 */	unsigned long	SystemCall;
/* off 0x0304 */	unsigned long	SystemCallReturn;
/* off 0x0308 */	unsigned __int64 SystemCallPad[3];
union
{
/* off 0x0320 */	struct _KSYSTEM_TIME	TickCount;
/* off 0x0320 */	unsigned __int64	TickCountQuad;
};
/* off 0x0330 */	unsigned long	Cookie;
};
enum _NT_PRODUCT_TYPE
{
	NtProductWinNt	=0x00000001	,//0
	NtProductLanManNt	=0x00000002	,//0
	NtProductServer	=0x00000003	,//0
};
enum _ALTERNATIVE_ARCHITECTURE_TYPE
{
	StandardDesign	=0x00000000	,//0
	NEC98x86	=0x00000001	,//0
	EndAlternatives	=0x00000002	,//0
};
struct _MMVAD_LONG /* sizeof 00000034 52 */
{
/* off 0x0000 */	unsigned long	StartingVpn;
/* off 0x0004 */	unsigned long	EndingVpn;
/* off 0x0008 */	struct _MMVAD*	Parent;
/* off 0x000c */	struct _MMVAD*	LeftChild;
/* off 0x0010 */	struct _MMVAD*	RightChild;
/* off 0x0014 */	struct __unnamed	u;
/* off 0x0018 */	struct _CONTROL_AREA*	ControlArea;
/* off 0x001c */	struct _MMPTE*	FirstPrototypePte;
/* off 0x0020 */	struct _MMPTE*	LastContiguousPte;
/* off 0x0024 */	struct __unnamed	u2;
/* off 0x0028 */	struct __unnamed	u3;
/* off 0x0030 */	struct __unnamed	u4;
};
struct _MMVAD /* sizeof 00000028 40 */
{
/* off 0x0000 */	unsigned long	StartingVpn;
/* off 0x0004 */	unsigned long	EndingVpn;
/* off 0x0008 */	struct _MMVAD*	Parent;
/* off 0x000c */	struct _MMVAD*	LeftChild;
/* off 0x0010 */	struct _MMVAD*	RightChild;
/* off 0x0014 */	struct __unnamed	u;
/* off 0x0018 */	struct _CONTROL_AREA*	ControlArea;
/* off 0x001c */	struct _MMPTE*	FirstPrototypePte;
/* off 0x0020 */	struct _MMPTE*	LastContiguousPte;
/* off 0x0024 */	struct __unnamed	u2;
};
struct _MMVAD_FLAGS /* sizeof 00000004 4 */
{
/* off 0x0000 */	unsigned long	CommitCharge:19	 /* start bit 0 */;
/* off 0x0000 */	unsigned long	PhysicalMapping:1	 /* start bit 19 */;
/* off 0x0000 */	unsigned long	ImageMap:1	 /* start bit 20 */;
/* off 0x0000 */	unsigned long	UserPhysicalPages:1	 /* start bit 21 */;
/* off 0x0000 */	unsigned long	NoChange:1	 /* start bit 22 */;
/* off 0x0000 */	unsigned long	WriteWatch:1	 /* start bit 23 */;
/* off 0x0000 */	unsigned long	Protection:5	 /* start bit 24 */;
/* off 0x0000 */	unsigned long	LargePages:1	 /* start bit 29 */;
/* off 0x0000 */	unsigned long	MemCommit:1	 /* start bit 30 */;
/* off 0x0000 */	unsigned long	PrivateMemory:1	 /* start bit 31 */;
};
struct _MMVAD_FLAGS2 /* sizeof 00000004 4 */
{
/* off 0x0000 */	unsigned int	FileOffset:24	 /* start bit 0 */;
/* off 0x0000 */	unsigned int	SecNoChange:1	 /* start bit 24 */;
/* off 0x0000 */	unsigned int	OneSecured:1	 /* start bit 25 */;
/* off 0x0000 */	unsigned int	MultipleSecured:1	 /* start bit 26 */;
/* off 0x0000 */	unsigned int	ReadOnly:1	 /* start bit 27 */;
/* off 0x0000 */	unsigned int	LongVad:1	 /* start bit 28 */;
/* off 0x0000 */	unsigned int	ExtendableFile:1	 /* start bit 29 */;
/* off 0x0000 */	unsigned int	Inherit:1	 /* start bit 30 */;
/* off 0x0000 */	unsigned int	CopyOnWrite:1	 /* start bit 31 */;
};
struct _MMADDRESS_LIST /* sizeof 00000008 8 */
{
/* off 0x0000 */	unsigned long	StartVpn;
/* off 0x0004 */	unsigned long	EndVpn;
};
struct _MMBANKED_SECTION /* sizeof 00000020 32 */
{
/* off 0x0000 */	unsigned long	BasePhysicalPage;
/* off 0x0004 */	struct _MMPTE*	BasedPte;
/* off 0x0008 */	unsigned long	BankSize;
/* off 0x000c */	unsigned long	BankShift;
/* off 0x0010 */	void( __cdecl *BankedRoutine)(unsigned long,unsigned long,void*);
/* off 0x0014 */	void*	Context;
/* off 0x0018 */	struct _MMPTE*	CurrentMappedPte;
/* off 0x001c */	struct _MMPTE BankTemplate[1];
};
enum _MEMORY_CACHING_TYPE_ORIG
{
	MmFrameBufferCached	=0x00000002	,//0
};
struct _POOL_TRACKER_BIG_PAGES /* sizeof 0000000c 12 */
{
/* off 0x0000 */	void*	Va;
/* off 0x0004 */	unsigned long	Key;
/* off 0x0008 */	unsigned long	NumberOfPages;
};
struct _PCI_SLOT_NUMBER /* sizeof 00000004 4 */
{
/* off 0x0000 */	struct __unnamed	u;
};
struct PCI_POWER_STATE /* sizeof 00000040 64 */
{
/* off 0x0000 */	enum _SYSTEM_POWER_STATE	CurrentSystemState;
/* off 0x0004 */	enum _DEVICE_POWER_STATE	CurrentDeviceState;
/* off 0x0008 */	enum _SYSTEM_POWER_STATE	SystemWakeLevel;
/* off 0x000c */	enum _DEVICE_POWER_STATE	DeviceWakeLevel;
/* off 0x0010 */	enum _DEVICE_POWER_STATE SystemStateMapping[7];
/* off 0x002c */	struct _IRP*	WaitWakeIrp;
/* off 0x0030 */	void( __cdecl *SavedCancelRoutine)(struct _DEVICE_OBJECT*,struct _IRP*);
/* off 0x0034 */	long	Paging;
/* off 0x0038 */	long	Hibernate;
/* off 0x003c */	long	CrashDump;
};
union PCI_HEADER_TYPE_DEPENDENT /* sizeof 00000004 4 */
{
/* off 0x0000 */	struct __unnamed	type0;
/* off 0x0000 */	struct __unnamed	type1;
/* off 0x0000 */	struct __unnamed	type2;
};
struct _PCI_LOCK /* sizeof 00000008 8 */
{
/* off 0x0000 */	unsigned long	Atom;
/* off 0x0004 */	unsigned char	OldIrql;
};
struct _PM_SUPPORT /* sizeof 00000001 1 */
{
/* off 0x0000 */	unsigned char	Rsvd2:1	 /* start bit 0 */;
/* off 0x0000 */	unsigned char	D1:1	 /* start bit 1 */;
/* off 0x0000 */	unsigned char	D2:1	 /* start bit 2 */;
/* off 0x0000 */	unsigned char	PMED0:1	 /* start bit 3 */;
/* off 0x0000 */	unsigned char	PMED1:1	 /* start bit 4 */;
/* off 0x0000 */	unsigned char	PMED2:1	 /* start bit 5 */;
/* off 0x0000 */	unsigned char	PMED3Hot:1	 /* start bit 6 */;
/* off 0x0000 */	unsigned char	PMED3Cold:1	 /* start bit 7 */;
};
struct _PCI_PMC /* sizeof 00000002 2 */
{
/* off 0x0000 */	unsigned char	Version:3	 /* start bit 0 */;
/* off 0x0000 */	unsigned char	PMEClock:1	 /* start bit 3 */;
/* off 0x0000 */	unsigned char	Rsvd1:1	 /* start bit 4 */;
/* off 0x0000 */	unsigned char	DeviceSpecificInitialization:1	 /* start bit 5 */;
/* off 0x0000 */	unsigned char	Rsvd2:2	 /* start bit 6 */;
/* off 0x0001 */	struct _PM_SUPPORT	Support;
};
struct _PCI_PDO_EXTENSION /* sizeof 000000c8 200 */
{
/* off 0x0000 */	struct _PCI_PDO_EXTENSION*	Next;
/* off 0x0004 */	enum PCI_SIGNATURE	ExtensionType;
/* off 0x0008 */	struct _PCI_MJ_DISPATCH_TABLE*	IrpDispatchTable;
/* off 0x000c */	unsigned char	DeviceState;
/* off 0x000d */	unsigned char	TentativeNextState;
/* off 0x0010 */	struct _KEVENT	SecondaryExtLock;
/* off 0x0020 */	struct _PCI_SLOT_NUMBER	Slot;
/* off 0x0024 */	struct _DEVICE_OBJECT*	PhysicalDeviceObject;
/* off 0x0028 */	struct _PCI_FDO_EXTENSION*	ParentFdoExtension;
/* off 0x002c */	struct _SINGLE_LIST_ENTRY	SecondaryExtension;
/* off 0x0030 */	unsigned long	BusInterfaceReferenceCount;
/* off 0x0034 */	unsigned long	AgpInterfaceReferenceCount;
/* off 0x0038 */	unsigned short	VendorId;
/* off 0x003a */	unsigned short	DeviceId;
/* off 0x003c */	unsigned short	SubsystemVendorId;
/* off 0x003e */	unsigned short	SubsystemId;
/* off 0x0040 */	unsigned char	RevisionId;
/* off 0x0041 */	unsigned char	ProgIf;
/* off 0x0042 */	unsigned char	SubClass;
/* off 0x0043 */	unsigned char	BaseClass;
/* off 0x0044 */	unsigned char	AdditionalResourceCount;
/* off 0x0045 */	unsigned char	AdjustedInterruptLine;
/* off 0x0046 */	unsigned char	InterruptPin;
/* off 0x0047 */	unsigned char	RawInterruptLine;
/* off 0x0048 */	unsigned char	CapabilitiesPtr;
/* off 0x0049 */	unsigned char	SavedLatencyTimer;
/* off 0x004a */	unsigned char	SavedCacheLineSize;
/* off 0x004b */	unsigned char	HeaderType;
/* off 0x004c */	unsigned char	NotPresent;
/* off 0x004d */	unsigned char	ReportedMissing;
/* off 0x004e */	unsigned char	ExpectedWritebackFailure;
/* off 0x004f */	unsigned char	NoTouchPmeEnable;
/* off 0x0050 */	unsigned char	LegacyDriver;
/* off 0x0051 */	unsigned char	UpdateHardware;
/* off 0x0052 */	unsigned char	MovedDevice;
/* off 0x0053 */	unsigned char	DisablePowerDown;
/* off 0x0054 */	unsigned char	NeedsHotPlugConfiguration;
/* off 0x0055 */	unsigned char	SwitchedIDEToNativeMode;
/* off 0x0056 */	unsigned char	BIOSAllowsIDESwitchToNativeMode;
/* off 0x0057 */	unsigned char	IoSpaceUnderNativeIdeControl;
/* off 0x0058 */	unsigned char	OnDebugPath;
/* off 0x005c */	struct PCI_POWER_STATE	PowerState;
/* off 0x009c */	union PCI_HEADER_TYPE_DEPENDENT	Dependent;
/* off 0x00a0 */	unsigned __int64	HackFlags;
/* off 0x00a8 */	struct PCI_FUNCTION_RESOURCES*	Resources;
/* off 0x00ac */	struct _PCI_FDO_EXTENSION*	BridgeFdoExtension;
/* off 0x00b0 */	struct _PCI_PDO_EXTENSION*	NextBridge;
/* off 0x00b4 */	struct _PCI_PDO_EXTENSION*	NextHashEntry;
/* off 0x00b8 */	struct _PCI_LOCK	Lock;
/* off 0x00c0 */	struct _PCI_PMC	PowerCapabilities;
/* off 0x00c2 */	unsigned char	TargetAgpCapabilityId;
/* off 0x00c4 */	unsigned short	CommandEnables;
/* off 0x00c6 */	unsigned short	InitialCommand;
};
enum PCI_SIGNATURE
{
	PciPdoExtensionType	=0x69635030	,//0
	PciFdoExtensionType	=0x69635031	,//0
	PciArb_Io	=0x69635032	,//0
	PciArb_Memory	=0x69635033	,//0
	PciArb_Interrupt	=0x69635034	,//0
	PciArb_BusNumber	=0x69635035	,//0
	PciTrans_Interrupt	=0x69635036	,//0
	PciInterface_BusHandler	=0x69635037	,//0
	PciInterface_IntRouteHandler	=0x69635038	,//0
	PciInterface_PciCb	=0x69635039	,//0
	PciInterface_LegacyDeviceDetection	=0x6963503a	,//0
	PciInterface_PmeHandler	=0x6963503b	,//0
	PciInterface_DevicePresent	=0x6963503c	,//0
	PciInterface_NativeIde	=0x6963503d	,//0
	PciInterface_AgpTarget	=0x6963503e	,//0
};
struct _PCI_MJ_DISPATCH_TABLE /* sizeof 00000020 32 */
{
/* off 0x0000 */	unsigned long	PnpIrpMaximumMinorFunction;
/* off 0x0004 */	struct _PCI_MN_DISPATCH_TABLE*	PnpIrpDispatchTable;
/* off 0x0008 */	unsigned long	PowerIrpMaximumMinorFunction;
/* off 0x000c */	struct _PCI_MN_DISPATCH_TABLE*	PowerIrpDispatchTable;
/* off 0x0010 */	enum _PCI_DISPATCH_STYLE	SystemControlIrpDispatchStyle;
/* off 0x0014 */	long( __cdecl *SystemControlIrpDispatchFunction)(struct _IRP*,struct _IO_STACK_LOCATION*,struct _PCI_COMMON_EXTENSION*);
/* off 0x0018 */	enum _PCI_DISPATCH_STYLE	OtherIrpDispatchStyle;
/* off 0x001c */	long( __cdecl *OtherIrpDispatchFunction)(struct _IRP*,struct _IO_STACK_LOCATION*,struct _PCI_COMMON_EXTENSION*);
};
struct _PCI_MN_DISPATCH_TABLE /* sizeof 00000008 8 */
{
/* off 0x0000 */	enum _PCI_DISPATCH_STYLE	DispatchStyle;
/* off 0x0004 */	long( __cdecl *DispatchFunction)(struct _IRP*,struct _IO_STACK_LOCATION*,struct _PCI_COMMON_EXTENSION*);
};
enum _PCI_DISPATCH_STYLE
{
	IRP_COMPLETE	=0x00000000	,//0
	IRP_DOWNWARD	=0x00000001	,//0
	IRP_UPWARD	=0x00000002	,//0
	IRP_DISPATCH	=0x00000003	,//0
};
struct _IO_STACK_LOCATION /* sizeof 00000024 36 */
{
/* off 0x0000 */	unsigned char	MajorFunction;
/* off 0x0001 */	unsigned char	MinorFunction;
/* off 0x0002 */	unsigned char	Flags;
/* off 0x0003 */	unsigned char	Control;
/* off 0x0004 */	struct __unnamed	Parameters;
/* off 0x0014 */	struct _DEVICE_OBJECT*	DeviceObject;
/* off 0x0018 */	struct _FILE_OBJECT*	FileObject;
/* off 0x001c */	long( __cdecl *CompletionRoutine)(struct _DEVICE_OBJECT*,struct _IRP*,void*);
/* off 0x0020 */	void*	Context;
};
struct _PCI_COMMON_EXTENSION /* sizeof 00000020 32 */
{
/* off 0x0000 */	void*	Next;
/* off 0x0004 */	enum PCI_SIGNATURE	ExtensionType;
/* off 0x0008 */	struct _PCI_MJ_DISPATCH_TABLE*	IrpDispatchTable;
/* off 0x000c */	unsigned char	DeviceState;
/* off 0x000d */	unsigned char	TentativeNextState;
/* off 0x0010 */	struct _KEVENT	SecondaryExtLock;
};
struct _PCI_FDO_EXTENSION /* sizeof 000000c0 192 */
{
/* off 0x0000 */	struct _SINGLE_LIST_ENTRY	List;
/* off 0x0004 */	enum PCI_SIGNATURE	ExtensionType;
/* off 0x0008 */	struct _PCI_MJ_DISPATCH_TABLE*	IrpDispatchTable;
/* off 0x000c */	unsigned char	DeviceState;
/* off 0x000d */	unsigned char	TentativeNextState;
/* off 0x0010 */	struct _KEVENT	SecondaryExtLock;
/* off 0x0020 */	struct _DEVICE_OBJECT*	PhysicalDeviceObject;
/* off 0x0024 */	struct _DEVICE_OBJECT*	FunctionalDeviceObject;
/* off 0x0028 */	struct _DEVICE_OBJECT*	AttachedDeviceObject;
/* off 0x002c */	struct _KEVENT	ChildListLock;
/* off 0x003c */	struct _PCI_PDO_EXTENSION*	ChildPdoList;
/* off 0x0040 */	struct _PCI_FDO_EXTENSION*	BusRootFdoExtension;
/* off 0x0044 */	struct _PCI_FDO_EXTENSION*	ParentFdoExtension;
/* off 0x0048 */	struct _PCI_PDO_EXTENSION*	ChildBridgePdoList;
/* off 0x004c */	struct _PCI_BUS_INTERFACE_STANDARD*	PciBusInterface;
/* off 0x0050 */	unsigned char	MaxSubordinateBus;
/* off 0x0054 */	struct _BUS_HANDLER*	BusHandler;
/* off 0x0058 */	unsigned char	BaseBus;
/* off 0x0059 */	unsigned char	Fake;
/* off 0x005a */	unsigned char	ChildDelete;
/* off 0x005b */	unsigned char	Scanned;
/* off 0x005c */	unsigned char	ArbitersInitialized;
/* off 0x005d */	unsigned char	BrokenVideoHackApplied;
/* off 0x005e */	unsigned char	Hibernated;
/* off 0x0060 */	struct PCI_POWER_STATE	PowerState;
/* off 0x00a0 */	struct _SINGLE_LIST_ENTRY	SecondaryExtension;
/* off 0x00a4 */	unsigned long	ChildWaitWakeCount;
/* off 0x00a8 */	struct _PCI_COMMON_CONFIG*	PreservedConfig;
/* off 0x00ac */	struct _PCI_LOCK	Lock;
/* off 0x00b4 */	struct __unnamed	HotPlugParameters;
/* off 0x00bc */	unsigned long	BusHackFlags;
};
struct _PCI_BUS_INTERFACE_STANDARD /* sizeof 00000020 32 */
{
/* off 0x0000 */	unsigned short	Size;
/* off 0x0002 */	unsigned short	Version;
/* off 0x0004 */	void*	Context;
/* off 0x0008 */	void( __cdecl *InterfaceReference)(void*);
/* off 0x000c */	void( __cdecl *InterfaceDereference)(void*);
/* off 0x0010 */	unsigned long( __cdecl *ReadConfig)(void*,unsigned char,unsigned long,void*,unsigned long,unsigned long);
/* off 0x0014 */	unsigned long( __cdecl *WriteConfig)(void*,unsigned char,unsigned long,void*,unsigned long,unsigned long);
/* off 0x0018 */	void( __cdecl *PinToLine)(void*,struct _PCI_COMMON_CONFIG*);
/* off 0x001c */	void( __cdecl *LineToPin)(void*,struct _PCI_COMMON_CONFIG*,struct _PCI_COMMON_CONFIG*);
};
struct _PCI_COMMON_CONFIG /* sizeof 00000100 256 */
{
/* off 0x0000 */	unsigned short	VendorID;
/* off 0x0002 */	unsigned short	DeviceID;
/* off 0x0004 */	unsigned short	Command;
/* off 0x0006 */	unsigned short	Status;
/* off 0x0008 */	unsigned char	RevisionID;
/* off 0x0009 */	unsigned char	ProgIf;
/* off 0x000a */	unsigned char	SubClass;
/* off 0x000b */	unsigned char	BaseClass;
/* off 0x000c */	unsigned char	CacheLineSize;
/* off 0x000d */	unsigned char	LatencyTimer;
/* off 0x000e */	unsigned char	HeaderType;
/* off 0x000f */	unsigned char	BIST;
/* off 0x0010 */	struct __unnamed	u;
/* off 0x0040 */	unsigned char DeviceSpecific[192];
};
struct _BUS_HANDLER /* sizeof 0000006c 108 */
{
/* off 0x0000 */	unsigned long	Version;
/* off 0x0004 */	enum _INTERFACE_TYPE	InterfaceType;
/* off 0x0008 */	enum _BUS_DATA_TYPE	ConfigurationType;
/* off 0x000c */	unsigned long	BusNumber;
/* off 0x0010 */	struct _DEVICE_OBJECT*	DeviceObject;
/* off 0x0014 */	struct _BUS_HANDLER*	ParentHandler;
/* off 0x0018 */	void*	BusData;
/* off 0x001c */	unsigned long	DeviceControlExtensionSize;
/* off 0x0020 */	struct _SUPPORTED_RANGES*	BusAddresses;
/* off 0x0024 */	unsigned long Reserved[4];
/* off 0x0034 */	unsigned long( __cdecl *GetBusData)(struct _BUS_HANDLER*,struct _BUS_HANDLER*,unsigned long,void*,unsigned long,unsigned long);
/* off 0x0038 */	unsigned long( __cdecl *SetBusData)(struct _BUS_HANDLER*,struct _BUS_HANDLER*,unsigned long,void*,unsigned long,unsigned long);
/* off 0x003c */	long( __cdecl *AdjustResourceList)(struct _BUS_HANDLER*,struct _BUS_HANDLER*,struct _IO_RESOURCE_REQUIREMENTS_LIST**);
/* off 0x0040 */	long( __cdecl *AssignSlotResources)(struct _BUS_HANDLER*,struct _BUS_HANDLER*,struct _UNICODE_STRING*,struct _UNICODE_STRING*,struct _DRIVER_OBJECT*,struct _DEVICE_OBJECT*,unsigned long,struct _CM_RESOURCE_LIST**);
/* off 0x0044 */	unsigned long( __cdecl *GetInterruptVector)(struct _BUS_HANDLER*,struct _BUS_HANDLER*,unsigned long,unsigned long,unsigned char*,unsigned long*);
/* off 0x0048 */	unsigned char( __cdecl *TranslateBusAddress)(struct _BUS_HANDLER*,struct _BUS_HANDLER*,union _LARGE_INTEGER,unsigned long*,union _LARGE_INTEGER*);
/* off 0x004c */	void*	Spare1;
/* off 0x0050 */	void*	Spare2;
/* off 0x0054 */	void*	Spare3;
/* off 0x0058 */	void*	Spare4;
/* off 0x005c */	void*	Spare5;
/* off 0x0060 */	void*	Spare6;
/* off 0x0064 */	void*	Spare7;
/* off 0x0068 */	void*	Spare8;
};
enum _BUS_DATA_TYPE
{
	ConfigurationSpaceUndefined	=0xffffffff	,//-1
	Cmos	=0x00000000	,//0
	EisaConfiguration	=0x00000001	,//0
	Pos	=0x00000002	,//0
	CbusConfiguration	=0x00000003	,//0
	PCIConfiguration	=0x00000004	,//0
	VMEConfiguration	=0x00000005	,//0
	NuBusConfiguration	=0x00000006	,//0
	PCMCIAConfiguration	=0x00000007	,//0
	MPIConfiguration	=0x00000008	,//0
	MPSAConfiguration	=0x00000009	,//0
	PNPISAConfiguration	=0x0000000a	,//0
	SgiInternalConfiguration	=0x0000000b	,//0
	MaximumBusDataType	=0x0000000c	,//0
};
struct _SUPPORTED_RANGE /* sizeof 00000020 32 */
{
/* off 0x0000 */	struct _SUPPORTED_RANGE*	Next;
/* off 0x0004 */	unsigned long	SystemAddressSpace;
/* off 0x0008 */	__int64	SystemBase;
/* off 0x0010 */	__int64	Base;
/* off 0x0018 */	__int64	Limit;
};
struct _SUPPORTED_RANGES /* sizeof 000000a0 160 */
{
/* off 0x0000 */	unsigned short	Version;
/* off 0x0002 */	unsigned char	Sorted;
/* off 0x0003 */	unsigned char	Reserved;
/* off 0x0004 */	unsigned long	NoIO;
/* off 0x0008 */	struct _SUPPORTED_RANGE	IO;
/* off 0x0028 */	unsigned long	NoMemory;
/* off 0x0030 */	struct _SUPPORTED_RANGE	Memory;
/* off 0x0050 */	unsigned long	NoPrefetchMemory;
/* off 0x0058 */	struct _SUPPORTED_RANGE	PrefetchMemory;
/* off 0x0078 */	unsigned long	NoDma;
/* off 0x0080 */	struct _SUPPORTED_RANGE	Dma;
};
struct PCI_FUNCTION_RESOURCES /* sizeof 00000150 336 */
{
/* off 0x0000 */	struct _IO_RESOURCE_DESCRIPTOR Limit[7];
/* off 0x00e0 */	struct _CM_PARTIAL_RESOURCE_DESCRIPTOR Current[7];
};
struct _QUAD /* sizeof 00000008 8 */
{
/* off 0x0000 */	double	DoNotUseThisField;
};
struct _OBJECT_HEADER /* sizeof 00000020 32 */
{
/* off 0x0000 */	long	PointerCount;
union
{
/* off 0x0004 */	long	HandleCount;
/* off 0x0004 */	void*	NextToFree;
};
/* off 0x0008 */	struct _OBJECT_TYPE*	Type;
/* off 0x000c */	unsigned char	NameInfoOffset;
/* off 0x000d */	unsigned char	HandleInfoOffset;
/* off 0x000e */	unsigned char	QuotaInfoOffset;
/* off 0x000f */	unsigned char	Flags;
union
{
/* off 0x0010 */	struct _OBJECT_CREATE_INFORMATION*	ObjectCreateInfo;
/* off 0x0010 */	void*	QuotaBlockCharged;
};
/* off 0x0014 */	void*	SecurityDescriptor;
/* off 0x0018 */	struct _QUAD	Body;
};
struct _OBJECT_CREATE_INFORMATION /* sizeof 00000030 48 */
{
/* off 0x0000 */	unsigned long	Attributes;
/* off 0x0004 */	void*	RootDirectory;
/* off 0x0008 */	void*	ParseContext;
/* off 0x000c */	char	ProbeMode;
/* off 0x0010 */	unsigned long	PagedPoolCharge;
/* off 0x0014 */	unsigned long	NonPagedPoolCharge;
/* off 0x0018 */	unsigned long	SecurityDescriptorCharge;
/* off 0x001c */	void*	SecurityDescriptor;
/* off 0x0020 */	struct _SECURITY_QUALITY_OF_SERVICE*	SecurityQos;
/* off 0x0024 */	struct _SECURITY_QUALITY_OF_SERVICE	SecurityQualityOfService;
};
struct _SECURITY_DESCRIPTOR /* sizeof 00000014 20 */
{
/* off 0x0000 */	unsigned char	Revision;
/* off 0x0001 */	unsigned char	Sbz1;
/* off 0x0002 */	unsigned short	Control;
/* off 0x0004 */	void*	Owner;
/* off 0x0008 */	void*	Group;
/* off 0x000c */	struct _ACL*	Sacl;
/* off 0x0010 */	struct _ACL*	Dacl;
};
struct _ACL /* sizeof 00000008 8 */
{
/* off 0x0000 */	unsigned char	AclRevision;
/* off 0x0001 */	unsigned char	Sbz1;
/* off 0x0002 */	unsigned short	AclSize;
/* off 0x0004 */	unsigned short	AceCount;
/* off 0x0006 */	unsigned short	Sbz2;
};
struct _RTLP_RANGE_LIST_ENTRY /* sizeof 00000028 40 */
{
/* off 0x0000 */	unsigned __int64	Start;
/* off 0x0008 */	unsigned __int64	End;
union
{
/* off 0x0010 */	struct __unnamed	Allocated;
/* off 0x0010 */	struct __unnamed	Merged;
};
/* off 0x0018 */	unsigned char	Attributes;
/* off 0x0019 */	unsigned char	PublicFlags;
/* off 0x001a */	unsigned short	PrivateFlags;
/* off 0x001c */	struct _LIST_ENTRY	ListEntry;
};
struct _OBJECT_HEADER_CREATOR_INFO /* sizeof 00000010 16 */
{
/* off 0x0000 */	struct _LIST_ENTRY	TypeList;
/* off 0x0008 */	void*	CreatorUniqueProcess;
/* off 0x000c */	unsigned short	CreatorBackTraceIndex;
/* off 0x000e */	unsigned short	Reserved;
};
struct _HEAP_STOP_ON_TAG /* sizeof 00000004 4 */
{
union
{
/* off 0x0000 */	unsigned long	HeapAndTagIndex;
struct
{
/* off 0x0000 */	unsigned short	TagIndex;
/* off 0x0002 */	unsigned short	HeapIndex;
};
};
};
struct _HEAP_STOP_ON_VALUES /* sizeof 00000018 24 */
{
/* off 0x0000 */	unsigned long	AllocAddress;
/* off 0x0004 */	struct _HEAP_STOP_ON_TAG	AllocTag;
/* off 0x0008 */	unsigned long	ReAllocAddress;
/* off 0x000c */	struct _HEAP_STOP_ON_TAG	ReAllocTag;
/* off 0x0010 */	unsigned long	FreeAddress;
/* off 0x0014 */	struct _HEAP_STOP_ON_TAG	FreeTag;
};
enum _MODE
{
	KernelMode	=0x00000000	,//0
	UserMode	=0x00000001	,//0
	MaximumMode	=0x00000002	,//0
};
struct _PI_RESOURCE_ARBITER_ENTRY /* sizeof 00000038 56 */
{
/* off 0x0000 */	struct _LIST_ENTRY	DeviceArbiterList;
/* off 0x0008 */	unsigned char	ResourceType;
/* off 0x000c */	struct _ARBITER_INTERFACE*	ArbiterInterface;
/* off 0x0010 */	unsigned long	Level;
/* off 0x0014 */	struct _LIST_ENTRY	ResourceList;
/* off 0x001c */	struct _LIST_ENTRY	BestResourceList;
/* off 0x0024 */	struct _LIST_ENTRY	BestConfig;
/* off 0x002c */	struct _LIST_ENTRY	ActiveArbiterList;
/* off 0x0034 */	unsigned char	State;
/* off 0x0035 */	unsigned char	ResourcesChanged;
};
struct _ARBITER_INTERFACE /* sizeof 00000018 24 */
{
/* off 0x0000 */	unsigned short	Size;
/* off 0x0002 */	unsigned short	Version;
/* off 0x0004 */	void*	Context;
/* off 0x0008 */	void( __cdecl *InterfaceReference)(void*);
/* off 0x000c */	void( __cdecl *InterfaceDereference)(void*);
/* off 0x0010 */	long( __cdecl *ArbiterHandler)(void*,enum _ARBITER_ACTION,struct _ARBITER_PARAMETERS*);
/* off 0x0014 */	unsigned long	Flags;
};
enum _ARBITER_ACTION
{
	ArbiterActionTestAllocation	=0x00000000	,//0
	ArbiterActionRetestAllocation	=0x00000001	,//0
	ArbiterActionCommitAllocation	=0x00000002	,//0
	ArbiterActionRollbackAllocation	=0x00000003	,//0
	ArbiterActionQueryAllocatedResources	=0x00000004	,//0
	ArbiterActionWriteReservedResources	=0x00000005	,//0
	ArbiterActionQueryConflict	=0x00000006	,//0
	ArbiterActionQueryArbitrate	=0x00000007	,//0
	ArbiterActionAddReserved	=0x00000008	,//0
	ArbiterActionBootAllocation	=0x00000009	,//0
};
struct _ARBITER_PARAMETERS /* sizeof 00000010 16 */
{
/* off 0x0000 */	struct __unnamed	Parameters;
};
struct _IMAGE_SECTION_HEADER /* sizeof 00000028 40 */
{
/* off 0x0000 */	unsigned char Name[8];
/* off 0x0008 */	struct __unnamed	Misc;
/* off 0x000c */	unsigned long	VirtualAddress;
/* off 0x0010 */	unsigned long	SizeOfRawData;
/* off 0x0014 */	unsigned long	PointerToRawData;
/* off 0x0018 */	unsigned long	PointerToRelocations;
/* off 0x001c */	unsigned long	PointerToLinenumbers;
/* off 0x0020 */	unsigned short	NumberOfRelocations;
/* off 0x0022 */	unsigned short	NumberOfLinenumbers;
/* off 0x0024 */	unsigned long	Characteristics;
};
struct _ETIMER /* sizeof 00000098 152 */
{
/* off 0x0000 */	struct _KTIMER	KeTimer;
/* off 0x0028 */	struct _KAPC	TimerApc;
/* off 0x0058 */	struct _KDPC	TimerDpc;
/* off 0x0078 */	struct _LIST_ENTRY	ActiveTimerListEntry;
/* off 0x0080 */	unsigned long	Lock;
/* off 0x0084 */	long	Period;
/* off 0x0088 */	unsigned char	ApcAssociated;
/* off 0x0089 */	unsigned char	WakeTimer;
/* off 0x008c */	struct _LIST_ENTRY	WakeTimerListEntry;
};
enum _POLICY_AUDIT_EVENT_TYPE
{
	AuditCategorySystem	=0x00000000	,//0
	AuditCategoryLogon	=0x00000001	,//0
	AuditCategoryObjectAccess	=0x00000002	,//0
	AuditCategoryPrivilegeUse	=0x00000003	,//0
	AuditCategoryDetailedTracking	=0x00000004	,//0
	AuditCategoryPolicyChange	=0x00000005	,//0
	AuditCategoryAccountManagement	=0x00000006	,//0
	AuditCategoryDirectoryServiceAccess	=0x00000007	,//0
	AuditCategoryAccountLogon	=0x00000008	,//0
};
struct _MMWSLENTRY /* sizeof 00000004 4 */
{
/* off 0x0000 */	unsigned long	Valid:1	 /* start bit 0 */;
/* off 0x0000 */	unsigned long	LockedInWs:1	 /* start bit 1 */;
/* off 0x0000 */	unsigned long	LockedInMemory:1	 /* start bit 2 */;
/* off 0x0000 */	unsigned long	Protection:5	 /* start bit 3 */;
/* off 0x0000 */	unsigned long	Hashed:1	 /* start bit 8 */;
/* off 0x0000 */	unsigned long	Direct:1	 /* start bit 9 */;
/* off 0x0000 */	unsigned long	Age:2	 /* start bit 10 */;
/* off 0x0000 */	unsigned long	VirtualPageNumber:20	 /* start bit 12 */;
};
struct _EXCEPTION_POINTERS /* sizeof 00000008 8 */
{
/* off 0x0000 */	struct _EXCEPTION_RECORD*	ExceptionRecord;
/* off 0x0004 */	struct _CONTEXT*	ContextRecord;
};
struct _MMPFNLIST /* sizeof 00000010 16 */
{
/* off 0x0000 */	unsigned long	Total;
/* off 0x0004 */	enum _MMLISTS	ListName;
/* off 0x0008 */	unsigned long	Flink;
/* off 0x000c */	unsigned long	Blink;
};
struct _OBJECT_HEADER_NAME_INFO /* sizeof 00000010 16 */
{
/* off 0x0000 */	struct _OBJECT_DIRECTORY*	Directory;
/* off 0x0004 */	struct _UNICODE_STRING	Name;
/* off 0x000c */	unsigned long	QueryReferences;
};
struct _OBJECT_DIRECTORY /* sizeof 000000a4 164 */
{
/* off 0x0000 */	struct _OBJECT_DIRECTORY_ENTRY* HashBuckets[37];
/* off 0x0094 */	struct _EX_PUSH_LOCK	Lock;
/* off 0x0098 */	struct _DEVICE_MAP*	DeviceMap;
/* off 0x009c */	unsigned long	SessionId;
/* off 0x00a0 */	unsigned short	Reserved;
/* off 0x00a2 */	unsigned short	SymbolicLinkUsageCount;
};
struct _OBJECT_DIRECTORY_ENTRY /* sizeof 00000008 8 */
{
/* off 0x0000 */	struct _OBJECT_DIRECTORY_ENTRY*	ChainLink;
/* off 0x0004 */	void*	Object;
};
struct _DEVICE_MAP /* sizeof 00000030 48 */
{
/* off 0x0000 */	struct _OBJECT_DIRECTORY*	DosDevicesDirectory;
/* off 0x0004 */	struct _OBJECT_DIRECTORY*	GlobalDosDevicesDirectory;
/* off 0x0008 */	unsigned long	ReferenceCount;
/* off 0x000c */	unsigned long	DriveMap;
/* off 0x0010 */	unsigned char DriveType[32];
};
struct _KINTERRUPT /* sizeof 000001e4 484 */
{
/* off 0x0000 */	short	Type;
/* off 0x0002 */	short	Size;
/* off 0x0004 */	struct _LIST_ENTRY	InterruptListEntry;
/* off 0x000c */	unsigned char( __cdecl *ServiceRoutine)(struct _KINTERRUPT*,void*);
/* off 0x0010 */	void*	ServiceContext;
/* off 0x0014 */	unsigned long	SpinLock;
/* off 0x0018 */	unsigned long	TickCount;
/* off 0x001c */	unsigned long*	ActualLock;
/* off 0x0020 */	void( __cdecl *DispatchAddress)();
/* off 0x0024 */	unsigned long	Vector;
/* off 0x0028 */	unsigned char	Irql;
/* off 0x0029 */	unsigned char	SynchronizeIrql;
/* off 0x002a */	unsigned char	FloatingSave;
/* off 0x002b */	unsigned char	Connected;
/* off 0x002c */	char	Number;
/* off 0x002d */	unsigned char	ShareVector;
/* off 0x0030 */	enum _KINTERRUPT_MODE	Mode;
/* off 0x0034 */	unsigned long	ServiceCount;
/* off 0x0038 */	unsigned long	DispatchCount;
/* off 0x003c */	unsigned long DispatchCode[106];
};
enum _KINTERRUPT_MODE
{
	LevelSensitive	=0x00000000	,//0
	Latched	=0x00000001	,//0
};
struct PCI_SECONDARY_EXTENSION /* sizeof 0000000c 12 */
{
/* off 0x0000 */	struct _SINGLE_LIST_ENTRY	List;
/* off 0x0004 */	enum PCI_SIGNATURE	ExtensionType;
/* off 0x0008 */	void( __cdecl *Destructor)(void*);
};
struct _ARBITER_ORDERING_LIST /* sizeof 00000008 8 */
{
/* off 0x0000 */	unsigned short	Count;
/* off 0x0002 */	unsigned short	Maximum;
/* off 0x0004 */	struct _ARBITER_ORDERING*	Orderings;
};
struct _ARBITER_INSTANCE /* sizeof 0000009c 156 */
{
/* off 0x0000 */	unsigned long	Signature;
/* off 0x0004 */	struct _KEVENT*	MutexEvent;
/* off 0x0008 */	unsigned short*	Name;
/* off 0x000c */	int	ResourceType;
/* off 0x0010 */	struct _RTL_RANGE_LIST*	Allocation;
/* off 0x0014 */	struct _RTL_RANGE_LIST*	PossibleAllocation;
/* off 0x0018 */	struct _ARBITER_ORDERING_LIST	OrderingList;
/* off 0x0020 */	struct _ARBITER_ORDERING_LIST	ReservedList;
/* off 0x0028 */	long	ReferenceCount;
/* off 0x002c */	struct _ARBITER_INTERFACE*	Interface;
/* off 0x0030 */	unsigned long	AllocationStackMaxSize;
/* off 0x0034 */	struct _ARBITER_ALLOCATION_STATE*	AllocationStack;
/* off 0x0038 */	long( __cdecl *UnpackRequirement)(struct _IO_RESOURCE_DESCRIPTOR*,unsigned __int64*,unsigned __int64*,unsigned long*,unsigned long*);
/* off 0x003c */	long( __cdecl *PackResource)(struct _IO_RESOURCE_DESCRIPTOR*,unsigned __int64,struct _CM_PARTIAL_RESOURCE_DESCRIPTOR*);
/* off 0x0040 */	long( __cdecl *UnpackResource)(struct _CM_PARTIAL_RESOURCE_DESCRIPTOR*,unsigned __int64*,unsigned long*);
/* off 0x0044 */	long( __cdecl *ScoreRequirement)(struct _IO_RESOURCE_DESCRIPTOR*);
/* off 0x0048 */	long( __cdecl *TestAllocation)(struct _ARBITER_INSTANCE*,struct _LIST_ENTRY*);
/* off 0x004c */	long( __cdecl *RetestAllocation)(struct _ARBITER_INSTANCE*,struct _LIST_ENTRY*);
/* off 0x0050 */	long( __cdecl *CommitAllocation)(struct _ARBITER_INSTANCE*);
/* off 0x0054 */	long( __cdecl *RollbackAllocation)(struct _ARBITER_INSTANCE*);
/* off 0x0058 */	long( __cdecl *BootAllocation)(struct _ARBITER_INSTANCE*,struct _LIST_ENTRY*);
/* off 0x005c */	long( __cdecl *QueryArbitrate)(struct _ARBITER_INSTANCE*,struct _LIST_ENTRY*);
/* off 0x0060 */	long( __cdecl *QueryConflict)(struct _ARBITER_INSTANCE*,struct _DEVICE_OBJECT*,struct _IO_RESOURCE_DESCRIPTOR*,unsigned long*,struct _ARBITER_CONFLICT_INFO**);
/* off 0x0064 */	long( __cdecl *AddReserved)(struct _ARBITER_INSTANCE*,struct _IO_RESOURCE_DESCRIPTOR*,struct _CM_PARTIAL_RESOURCE_DESCRIPTOR*);
/* off 0x0068 */	long( __cdecl *StartArbiter)(struct _ARBITER_INSTANCE*,struct _CM_RESOURCE_LIST*);
/* off 0x006c */	long( __cdecl *PreprocessEntry)(struct _ARBITER_INSTANCE*,struct _ARBITER_ALLOCATION_STATE*);
/* off 0x0070 */	long( __cdecl *AllocateEntry)(struct _ARBITER_INSTANCE*,struct _ARBITER_ALLOCATION_STATE*);
/* off 0x0074 */	unsigned char( __cdecl *GetNextAllocationRange)(struct _ARBITER_INSTANCE*,struct _ARBITER_ALLOCATION_STATE*);
/* off 0x0078 */	unsigned char( __cdecl *FindSuitableRange)(struct _ARBITER_INSTANCE*,struct _ARBITER_ALLOCATION_STATE*);
/* off 0x007c */	void( __cdecl *AddAllocation)(struct _ARBITER_INSTANCE*,struct _ARBITER_ALLOCATION_STATE*);
/* off 0x0080 */	void( __cdecl *BacktrackAllocation)(struct _ARBITER_INSTANCE*,struct _ARBITER_ALLOCATION_STATE*);
/* off 0x0084 */	unsigned char( __cdecl *OverrideConflict)(struct _ARBITER_INSTANCE*,struct _ARBITER_ALLOCATION_STATE*);
/* off 0x0088 */	unsigned char	TransactionInProgress;
/* off 0x008c */	void*	Extension;
/* off 0x0090 */	struct _DEVICE_OBJECT*	BusDeviceObject;
/* off 0x0094 */	void*	ConflictCallbackContext;
/* off 0x0098 */	unsigned char( __cdecl *ConflictCallback)(void*,struct _RTL_RANGE*);
};
struct _PCI_ARBITER_INSTANCE /* sizeof 000000e0 224 */
{
/* off 0x0000 */	struct PCI_SECONDARY_EXTENSION	Header;
/* off 0x000c */	struct _PCI_INTERFACE*	Interface;
/* off 0x0010 */	struct _PCI_FDO_EXTENSION*	BusFdoExtension;
/* off 0x0014 */	unsigned short InstanceName[24];
/* off 0x0044 */	struct _ARBITER_INSTANCE	CommonInstance;
};
struct _PCI_INTERFACE /* sizeof 0000001c 28 */
{
/* off 0x0000 */	struct _GUID*	InterfaceType;
/* off 0x0004 */	unsigned short	MinSize;
/* off 0x0006 */	unsigned short	MinVersion;
/* off 0x0008 */	unsigned short	MaxVersion;
/* off 0x000a */	unsigned short	Flags;
/* off 0x000c */	long	ReferenceCount;
/* off 0x0010 */	enum PCI_SIGNATURE	Signature;
/* off 0x0014 */	long( __cdecl *Constructor)(void*,void*,void*,unsigned short,unsigned short,struct _INTERFACE*);
/* off 0x0018 */	long( __cdecl *Initializer)(struct _PCI_ARBITER_INSTANCE*);
};
struct _GUID /* sizeof 00000010 16 */
{
/* off 0x0000 */	unsigned long	Data1;
/* off 0x0004 */	unsigned short	Data2;
/* off 0x0006 */	unsigned short	Data3;
/* off 0x0008 */	unsigned char Data4[8];
};
struct _INTERFACE /* sizeof 00000010 16 */
{
/* off 0x0000 */	unsigned short	Size;
/* off 0x0002 */	unsigned short	Version;
/* off 0x0004 */	void*	Context;
/* off 0x0008 */	void( __cdecl *InterfaceReference)(void*);
/* off 0x000c */	void( __cdecl *InterfaceDereference)(void*);
};
struct _RTL_RANGE_LIST /* sizeof 00000014 20 */
{
/* off 0x0000 */	struct _LIST_ENTRY	ListHead;
/* off 0x0008 */	unsigned long	Flags;
/* off 0x000c */	unsigned long	Count;
/* off 0x0010 */	unsigned long	Stamp;
};
struct _ARBITER_ORDERING /* sizeof 00000010 16 */
{
/* off 0x0000 */	unsigned __int64	Start;
/* off 0x0008 */	unsigned __int64	End;
};
struct _ARBITER_ALLOCATION_STATE /* sizeof 00000038 56 */
{
/* off 0x0000 */	unsigned __int64	Start;
/* off 0x0008 */	unsigned __int64	End;
/* off 0x0010 */	unsigned __int64	CurrentMinimum;
/* off 0x0018 */	unsigned __int64	CurrentMaximum;
/* off 0x0020 */	struct _ARBITER_LIST_ENTRY*	Entry;
/* off 0x0024 */	struct _ARBITER_ALTERNATIVE*	CurrentAlternative;
/* off 0x0028 */	unsigned long	AlternativeCount;
/* off 0x002c */	struct _ARBITER_ALTERNATIVE*	Alternatives;
/* off 0x0030 */	unsigned short	Flags;
/* off 0x0032 */	unsigned char	RangeAttributes;
/* off 0x0033 */	unsigned char	RangeAvailableAttributes;
/* off 0x0034 */	unsigned long	WorkSpace;
};
struct _ARBITER_LIST_ENTRY /* sizeof 00000038 56 */
{
/* off 0x0000 */	struct _LIST_ENTRY	ListEntry;
/* off 0x0008 */	unsigned long	AlternativeCount;
/* off 0x000c */	struct _IO_RESOURCE_DESCRIPTOR*	Alternatives;
/* off 0x0010 */	struct _DEVICE_OBJECT*	PhysicalDeviceObject;
/* off 0x0014 */	enum _ARBITER_REQUEST_SOURCE	RequestSource;
/* off 0x0018 */	unsigned long	Flags;
/* off 0x001c */	long	WorkSpace;
/* off 0x0020 */	enum _INTERFACE_TYPE	InterfaceType;
/* off 0x0024 */	unsigned long	SlotNumber;
/* off 0x0028 */	unsigned long	BusNumber;
/* off 0x002c */	struct _CM_PARTIAL_RESOURCE_DESCRIPTOR*	Assignment;
/* off 0x0030 */	struct _IO_RESOURCE_DESCRIPTOR*	SelectedAlternative;
/* off 0x0034 */	enum _ARBITER_RESULT	Result;
};
enum _ARBITER_REQUEST_SOURCE
{
	ArbiterRequestUndefined	=0xffffffff	,//-1
	ArbiterRequestLegacyReported	=0x00000000	,//0
	ArbiterRequestHalReported	=0x00000001	,//0
	ArbiterRequestLegacyAssigned	=0x00000002	,//0
	ArbiterRequestPnpDetected	=0x00000003	,//0
	ArbiterRequestPnpEnumerated	=0x00000004	,//0
};
enum _ARBITER_RESULT
{
	ArbiterResultUndefined	=0xffffffff	,//-1
	ArbiterResultSuccess	=0x00000000	,//0
	ArbiterResultExternalConflict	=0x00000001	,//0
	ArbiterResultNullRequest	=0x00000002	,//0
};
struct _ARBITER_ALTERNATIVE /* sizeof 00000030 48 */
{
/* off 0x0000 */	unsigned __int64	Minimum;
/* off 0x0008 */	unsigned __int64	Maximum;
/* off 0x0010 */	unsigned long	Length;
/* off 0x0014 */	unsigned long	Alignment;
/* off 0x0018 */	long	Priority;
/* off 0x001c */	unsigned long	Flags;
/* off 0x0020 */	struct _IO_RESOURCE_DESCRIPTOR*	Descriptor;
/* off 0x0024 */	unsigned long Reserved[3];
};
struct _ARBITER_CONFLICT_INFO /* sizeof 00000018 24 */
{
/* off 0x0000 */	struct _DEVICE_OBJECT*	OwningObject;
/* off 0x0008 */	unsigned __int64	Start;
/* off 0x0010 */	unsigned __int64	End;
};
struct _RTL_RANGE /* sizeof 00000020 32 */
{
/* off 0x0000 */	unsigned __int64	Start;
/* off 0x0008 */	unsigned __int64	End;
/* off 0x0010 */	void*	UserData;
/* off 0x0014 */	void*	Owner;
/* off 0x0018 */	unsigned char	Attributes;
/* off 0x0019 */	unsigned char	Flags;
};
struct _MMPAGING_FILE /* sizeof 00000044 68 */
{
/* off 0x0000 */	unsigned long	Size;
/* off 0x0004 */	unsigned long	MaximumSize;
/* off 0x0008 */	unsigned long	MinimumSize;
/* off 0x000c */	unsigned long	FreeSpace;
/* off 0x0010 */	unsigned long	CurrentUsage;
/* off 0x0014 */	unsigned long	PeakUsage;
/* off 0x0018 */	unsigned long	Hint;
/* off 0x001c */	unsigned long	HighestPage;
/* off 0x0020 */	struct _MMMOD_WRITER_MDL_ENTRY* Entry[2];
/* off 0x0028 */	struct _RTL_BITMAP*	Bitmap;
/* off 0x002c */	struct _FILE_OBJECT*	File;
/* off 0x0030 */	struct _UNICODE_STRING	PageFileName;
/* off 0x0038 */	unsigned long	PageFileNumber;
/* off 0x003c */	unsigned char	Extended;
/* off 0x003d */	unsigned char	HintSetToZero;
/* off 0x003e */	unsigned char	BootPartition;
/* off 0x0040 */	void*	FileHandle;
};
struct _MMMOD_WRITER_MDL_ENTRY /* sizeof 00000058 88 */
{
/* off 0x0000 */	struct _LIST_ENTRY	Links;
/* off 0x0008 */	union _LARGE_INTEGER	WriteOffset;
/* off 0x0010 */	struct __unnamed	u;
/* off 0x0018 */	struct _IRP*	Irp;
/* off 0x001c */	unsigned long	LastPageToWrite;
/* off 0x0020 */	struct _MMMOD_WRITER_LISTHEAD*	PagingListHead;
/* off 0x0024 */	struct _LIST_ENTRY*	CurrentList;
/* off 0x0028 */	struct _MMPAGING_FILE*	PagingFile;
/* off 0x002c */	struct _FILE_OBJECT*	File;
/* off 0x0030 */	struct _CONTROL_AREA*	ControlArea;
/* off 0x0034 */	struct _ERESOURCE*	FileResource;
/* off 0x0038 */	struct _MDL	Mdl;
/* off 0x0054 */	unsigned long Page[1];
};
struct _MMMOD_WRITER_LISTHEAD /* sizeof 00000018 24 */
{
/* off 0x0000 */	struct _LIST_ENTRY	ListHead;
/* off 0x0008 */	struct _KEVENT	Event;
};
struct _BUS_EXTENSION_LIST /* sizeof 00000008 8 */
{
/* off 0x0000 */	void*	Next;
/* off 0x0004 */	struct _PI_BUS_EXTENSION*	BusExtension;
};
struct _PI_BUS_EXTENSION /* sizeof 00000044 68 */
{
/* off 0x0000 */	unsigned long	Flags;
/* off 0x0004 */	unsigned long	NumberCSNs;
/* off 0x0008 */	unsigned char*	ReadDataPort;
/* off 0x000c */	unsigned char	DataPortMapped;
/* off 0x0010 */	unsigned char*	AddressPort;
/* off 0x0014 */	unsigned char	AddrPortMapped;
/* off 0x0018 */	unsigned char*	CommandPort;
/* off 0x001c */	unsigned char	CmdPortMapped;
/* off 0x0020 */	unsigned long	NextSlotNumber;
/* off 0x0024 */	struct _SINGLE_LIST_ENTRY	DeviceList;
/* off 0x0028 */	struct _SINGLE_LIST_ENTRY	CardList;
/* off 0x002c */	struct _DEVICE_OBJECT*	PhysicalBusDevice;
/* off 0x0030 */	struct _DEVICE_OBJECT*	FunctionalBusDevice;
/* off 0x0034 */	struct _DEVICE_OBJECT*	AttachedDevice;
/* off 0x0038 */	unsigned long	BusNumber;
/* off 0x003c */	enum _SYSTEM_POWER_STATE	SystemPowerState;
/* off 0x0040 */	enum _DEVICE_POWER_STATE	DevicePowerState;
};
enum ReplacesCorHdrNumericDefines
{
	COMIMAGE_FLAGS_ILONLY	=0x00000001	,//0
	COMIMAGE_FLAGS_32BITREQUIRED	=0x00000002	,//0
	COMIMAGE_FLAGS_IL_LIBRARY	=0x00000004	,//0
	COMIMAGE_FLAGS_STRONGNAMESIGNED	=0x00000008	,//0
	COMIMAGE_FLAGS_TRACKDEBUGDATA	=0x00010000	,//0
	COR_VERSION_MAJOR_V2	=0x00000002	,//0
	COR_VERSION_MAJOR	=0x00000002	,//0
	COR_VERSION_MINOR	=0x00000000	,//0
	COR_DELETED_NAME_LENGTH	=0x00000008	,//0
	COR_VTABLEGAP_NAME_LENGTH	=0x00000008	,//0
	NATIVE_TYPE_MAX_CB	=0x00000001	,//0
	COR_ILMETHOD_SECT_SMALL_MAX_DATASIZE	=0x000000ff	,//0
	IMAGE_COR_MIH_METHODRVA	=0x00000001	,//0
	IMAGE_COR_MIH_EHRVA	=0x00000002	,//0
	IMAGE_COR_MIH_BASICBLOCK	=0x00000008	,//0
	COR_VTABLE_32BIT	=0x00000001	,//0
	COR_VTABLE_64BIT	=0x00000002	,//0
	COR_VTABLE_FROM_UNMANAGED	=0x00000004	,//0
	COR_VTABLE_CALL_MOST_DERIVED	=0x00000010	,//0
	IMAGE_COR_EATJ_THUNK_SIZE	=0x00000020	,//0
	MAX_CLASS_NAME	=0x00000400	,//0
	MAX_PACKAGE_NAME	=0x00000400	,//0
};
enum _MEMORY_TYPE
{
	MemoryExceptionBlock	=0x00000000	,//0
	MemorySystemBlock	=0x00000001	,//0
	MemoryFree	=0x00000002	,//0
	MemoryBad	=0x00000003	,//0
	MemoryLoadedProgram	=0x00000004	,//0
	MemoryFirmwareTemporary	=0x00000005	,//0
	MemoryFirmwarePermanent	=0x00000006	,//0
	MemoryFreeContiguous	=0x00000007	,//0
	MemorySpecialMemory	=0x00000008	,//0
	MemoryMaximum	=0x00000009	,//0
};
struct _HEAP_LOOKASIDE /* sizeof 00000030 48 */
{
/* off 0x0000 */	union _SLIST_HEADER	ListHead;
/* off 0x0008 */	unsigned short	Depth;
/* off 0x000a */	unsigned short	MaximumDepth;
/* off 0x000c */	unsigned long	TotalAllocates;
/* off 0x0010 */	unsigned long	AllocateMisses;
/* off 0x0014 */	unsigned long	TotalFrees;
/* off 0x0018 */	unsigned long	FreeMisses;
/* off 0x001c */	unsigned long	LastTotalAllocates;
/* off 0x0020 */	unsigned long	LastAllocateMisses;
/* off 0x0024 */	unsigned long Counters[2];
};
struct _CALL_PERFORMANCE_DATA /* sizeof 00000204 516 */
{
/* off 0x0000 */	unsigned long	SpinLock;
/* off 0x0004 */	struct _LIST_ENTRY HashTable[64];
};
struct _KMUTANT /* sizeof 00000020 32 */
{
/* off 0x0000 */	struct _DISPATCHER_HEADER	Header;
/* off 0x0010 */	struct _LIST_ENTRY	MutantListEntry;
/* off 0x0018 */	struct _KTHREAD*	OwnerThread;
/* off 0x001c */	unsigned char	Abandoned;
/* off 0x001d */	unsigned char	ApcDisable;
};
struct _SECTION_IMAGE_INFORMATION /* sizeof 00000030 48 */
{
/* off 0x0000 */	void*	TransferAddress;
/* off 0x0004 */	unsigned long	ZeroBits;
/* off 0x0008 */	unsigned long	MaximumStackSize;
/* off 0x000c */	unsigned long	CommittedStackSize;
/* off 0x0010 */	unsigned long	SubSystemType;
union
{
struct
{
/* off 0x0014 */	unsigned short	SubSystemMinorVersion;
/* off 0x0016 */	unsigned short	SubSystemMajorVersion;
};
struct
{
/* off 0x0014 */	unsigned long	SubSystemVersion;
};
};
/* off 0x0018 */	unsigned long	GpValue;
/* off 0x001c */	unsigned short	ImageCharacteristics;
/* off 0x001e */	unsigned short	DllCharacteristics;
/* off 0x0020 */	unsigned short	Machine;
/* off 0x0022 */	unsigned char	ImageContainsCode;
/* off 0x0023 */	unsigned char	Spare1;
/* off 0x0024 */	unsigned long	LoaderFlags;
/* off 0x0028 */	unsigned long	ImageFileSize;
/* off 0x002c */	unsigned long Reserved[1];
};
struct _POP_IDLE_HANDLER /* sizeof 00000020 32 */
{
/* off 0x0000 */	unsigned long	Latency;
/* off 0x0004 */	unsigned long	TimeCheck;
/* off 0x0008 */	unsigned long	DemoteLimit;
/* off 0x000c */	unsigned long	PromoteLimit;
/* off 0x0010 */	unsigned long	PromoteCount;
/* off 0x0014 */	unsigned char	Demote;
/* off 0x0015 */	unsigned char	Promote;
/* off 0x0016 */	unsigned char	PromotePercent;
/* off 0x0017 */	unsigned char	DemotePercent;
/* off 0x0018 */	unsigned char	State;
/* off 0x0019 */	unsigned char Spare[3];
/* off 0x001c */	unsigned char( __fastcall *IdleFunction)(struct PROCESSOR_IDLE_TIMES*);
};
struct BATTERY_REPORTING_SCALE /* sizeof 00000008 8 */
{
/* off 0x0000 */	unsigned long	Granularity;
/* off 0x0004 */	unsigned long	Capacity;
};
struct SYSTEM_POWER_CAPABILITIES /* sizeof 0000004c 76 */
{
/* off 0x0000 */	unsigned char	PowerButtonPresent;
/* off 0x0001 */	unsigned char	SleepButtonPresent;
/* off 0x0002 */	unsigned char	LidPresent;
/* off 0x0003 */	unsigned char	SystemS1;
/* off 0x0004 */	unsigned char	SystemS2;
/* off 0x0005 */	unsigned char	SystemS3;
/* off 0x0006 */	unsigned char	SystemS4;
/* off 0x0007 */	unsigned char	SystemS5;
/* off 0x0008 */	unsigned char	HiberFilePresent;
/* off 0x0009 */	unsigned char	FullWake;
/* off 0x000a */	unsigned char	VideoDimPresent;
/* off 0x000b */	unsigned char	ApmPresent;
/* off 0x000c */	unsigned char	UpsPresent;
/* off 0x000d */	unsigned char	ThermalControl;
/* off 0x000e */	unsigned char	ProcessorThrottle;
/* off 0x000f */	unsigned char	ProcessorMinThrottle;
/* off 0x0010 */	unsigned char	ProcessorMaxThrottle;
/* off 0x0011 */	unsigned char spare2[4];
/* off 0x0015 */	unsigned char	DiskSpinDown;
/* off 0x0016 */	unsigned char spare3[8];
/* off 0x001e */	unsigned char	SystemBatteriesPresent;
/* off 0x001f */	unsigned char	BatteriesAreShortTerm;
/* off 0x0020 */	struct BATTERY_REPORTING_SCALE BatteryScale[3];
/* off 0x0038 */	enum _SYSTEM_POWER_STATE	AcOnLineWake;
/* off 0x003c */	enum _SYSTEM_POWER_STATE	SoftLidWake;
/* off 0x0040 */	enum _SYSTEM_POWER_STATE	RtcWake;
/* off 0x0044 */	enum _SYSTEM_POWER_STATE	MinDeviceWakeState;
/* off 0x0048 */	enum _SYSTEM_POWER_STATE	DefaultLowLatencyWake;
};
struct _TOKEN_SOURCE /* sizeof 00000010 16 */
{
/* off 0x0000 */	char SourceName[8];
/* off 0x0008 */	struct _LUID	SourceIdentifier;
};
struct _SEP_AUDIT_POLICY_CATEGORIES /* sizeof 00000008 8 */
{
/* off 0x0000 */	unsigned long	System:4	 /* start bit 0 */;
/* off 0x0000 */	unsigned long	Logon:4	 /* start bit 4 */;
/* off 0x0000 */	unsigned long	ObjectAccess:4	 /* start bit 8 */;
/* off 0x0000 */	unsigned long	PrivilegeUse:4	 /* start bit 12 */;
/* off 0x0000 */	unsigned long	DetailedTracking:4	 /* start bit 16 */;
/* off 0x0000 */	unsigned long	PolicyChange:4	 /* start bit 20 */;
/* off 0x0000 */	unsigned long	AccountManagement:4	 /* start bit 24 */;
/* off 0x0000 */	unsigned long	DirectoryServiceAccess:4	 /* start bit 28 */;
/* off 0x0004 */	unsigned long	AccountLogon:4	 /* start bit 0 */;
};
struct _SEP_AUDIT_POLICY_OVERLAY /* sizeof 00000008 8 */
{
/* off 0x0000 */	unsigned __int64	PolicyBits:36	 /* start bit 0 */;
/* off 0x0000 */	unsigned __int64	SetBit:1	 /* start bit 36 */;
};
struct _SEP_AUDIT_POLICY /* sizeof 00000008 8 */
{
union
{
/* off 0x0000 */	struct _SEP_AUDIT_POLICY_CATEGORIES	PolicyElements;
/* off 0x0000 */	struct _SEP_AUDIT_POLICY_OVERLAY	PolicyOverlay;
/* off 0x0000 */	unsigned __int64	Overlay;
};
};
struct _TOKEN /* sizeof 000000a8 168 */
{
/* off 0x0000 */	struct _TOKEN_SOURCE	TokenSource;
/* off 0x0010 */	struct _LUID	TokenId;
/* off 0x0018 */	struct _LUID	AuthenticationId;
/* off 0x0020 */	struct _LUID	ParentTokenId;
/* off 0x0028 */	union _LARGE_INTEGER	ExpirationTime;
/* off 0x0030 */	struct _ERESOURCE*	TokenLock;
/* off 0x0038 */	struct _SEP_AUDIT_POLICY	AuditPolicy;
/* off 0x0040 */	struct _LUID	ModifiedId;
/* off 0x0048 */	unsigned long	SessionId;
/* off 0x004c */	unsigned long	UserAndGroupCount;
/* off 0x0050 */	unsigned long	RestrictedSidCount;
/* off 0x0054 */	unsigned long	PrivilegeCount;
/* off 0x0058 */	unsigned long	VariableLength;
/* off 0x005c */	unsigned long	DynamicCharged;
/* off 0x0060 */	unsigned long	DynamicAvailable;
/* off 0x0064 */	unsigned long	DefaultOwnerIndex;
/* off 0x0068 */	struct _SID_AND_ATTRIBUTES*	UserAndGroups;
/* off 0x006c */	struct _SID_AND_ATTRIBUTES*	RestrictedSids;
/* off 0x0070 */	void*	PrimaryGroup;
/* off 0x0074 */	struct _LUID_AND_ATTRIBUTES*	Privileges;
/* off 0x0078 */	unsigned long*	DynamicPart;
/* off 0x007c */	struct _ACL*	DefaultDacl;
/* off 0x0080 */	enum _TOKEN_TYPE	TokenType;
/* off 0x0084 */	enum _SECURITY_IMPERSONATION_LEVEL	ImpersonationLevel;
/* off 0x0088 */	unsigned long	TokenFlags;
/* off 0x008c */	unsigned char	TokenInUse;
/* off 0x0090 */	struct _SECURITY_TOKEN_PROXY_DATA*	ProxyData;
/* off 0x0094 */	struct _SECURITY_TOKEN_AUDIT_DATA*	AuditData;
/* off 0x0098 */	struct _LUID	OriginatingLogonSession;
/* off 0x00a0 */	unsigned long	VariablePart;
};
enum _TOKEN_TYPE
{
	TokenPrimary	=0x00000001	,//0
	TokenImpersonation	=0x00000002	,//0
};
struct _SECURITY_TOKEN_PROXY_DATA /* sizeof 00000018 24 */
{
/* off 0x0000 */	unsigned long	Length;
/* off 0x0004 */	enum _PROXY_CLASS	ProxyClass;
/* off 0x0008 */	struct _UNICODE_STRING	PathInfo;
/* off 0x0010 */	unsigned long	ContainerMask;
/* off 0x0014 */	unsigned long	ObjectMask;
};
enum _PROXY_CLASS
{
	ProxyFull	=0x00000000	,//0
	ProxyService	=0x00000001	,//0
	ProxyTree	=0x00000002	,//0
	ProxyDirectory	=0x00000003	,//0
};
struct _SECURITY_TOKEN_AUDIT_DATA /* sizeof 0000000c 12 */
{
/* off 0x0000 */	unsigned long	Length;
/* off 0x0004 */	unsigned long	GrantMask;
/* off 0x0008 */	unsigned long	DenyMask;
};
struct _ACTIVATION_CONTEXT_STACK /* sizeof 00000014 20 */
{
/* off 0x0000 */	unsigned long	Flags;
/* off 0x0004 */	unsigned long	NextCookieSequenceNumber;
/* off 0x0008 */	void*	ActiveFrame;
/* off 0x000c */	struct _LIST_ENTRY	FrameListCache;
};
struct _GDI_TEB_BATCH /* sizeof 000004e0 1248 */
{
/* off 0x0000 */	unsigned long	Offset;
/* off 0x0004 */	unsigned long	HDC;
/* off 0x0008 */	unsigned long Buffer[310];
};
struct _Wx86ThreadState /* sizeof 0000000c 12 */
{
/* off 0x0000 */	unsigned long*	CallBx86Eip;
/* off 0x0004 */	void*	DeallocationCpu;
/* off 0x0008 */	unsigned char	UseKnownWx86Dll;
/* off 0x0009 */	char	OleStubInvoked;
};
struct _TEB /* sizeof 00000fb8 4024 */
{
/* off 0x0000 */	struct _NT_TIB	NtTib;
/* off 0x001c */	void*	EnvironmentPointer;
/* off 0x0020 */	struct _CLIENT_ID	ClientId;
/* off 0x0028 */	void*	ActiveRpcHandle;
/* off 0x002c */	void*	ThreadLocalStoragePointer;
/* off 0x0030 */	struct _PEB*	ProcessEnvironmentBlock;
/* off 0x0034 */	unsigned long	LastErrorValue;
/* off 0x0038 */	unsigned long	CountOfOwnedCriticalSections;
/* off 0x003c */	void*	CsrClientThread;
/* off 0x0040 */	void*	Win32ThreadInfo;
/* off 0x0044 */	unsigned long User32Reserved[26];
/* off 0x00ac */	unsigned long UserReserved[5];
/* off 0x00c0 */	void*	WOW32Reserved;
/* off 0x00c4 */	unsigned long	CurrentLocale;
/* off 0x00c8 */	unsigned long	FpSoftwareStatusRegister;
/* off 0x00cc */	void* SystemReserved1[54];
/* off 0x01a4 */	long	ExceptionCode;
/* off 0x01a8 */	struct _ACTIVATION_CONTEXT_STACK	ActivationContextStack;
/* off 0x01bc */	unsigned char SpareBytes1[24];
/* off 0x01d4 */	struct _GDI_TEB_BATCH	GdiTebBatch;
/* off 0x06b4 */	struct _CLIENT_ID	RealClientId;
/* off 0x06bc */	void*	GdiCachedProcessHandle;
/* off 0x06c0 */	unsigned long	GdiClientPID;
/* off 0x06c4 */	unsigned long	GdiClientTID;
/* off 0x06c8 */	void*	GdiThreadLocalInfo;
/* off 0x06cc */	unsigned long Win32ClientInfo[62];
/* off 0x07c4 */	void* glDispatchTable[233];
/* off 0x0b68 */	unsigned long glReserved1[29];
/* off 0x0bdc */	void*	glReserved2;
/* off 0x0be0 */	void*	glSectionInfo;
/* off 0x0be4 */	void*	glSection;
/* off 0x0be8 */	void*	glTable;
/* off 0x0bec */	void*	glCurrentRC;
/* off 0x0bf0 */	void*	glContext;
/* off 0x0bf4 */	unsigned long	LastStatusValue;
/* off 0x0bf8 */	struct _UNICODE_STRING	StaticUnicodeString;
/* off 0x0c00 */	unsigned short StaticUnicodeBuffer[261];
/* off 0x0e0c */	void*	DeallocationStack;
/* off 0x0e10 */	void* TlsSlots[64];
/* off 0x0f10 */	struct _LIST_ENTRY	TlsLinks;
/* off 0x0f18 */	void*	Vdm;
/* off 0x0f1c */	void*	ReservedForNtRpc;
/* off 0x0f20 */	void* DbgSsReserved[2];
/* off 0x0f28 */	unsigned long	HardErrorsAreDisabled;
/* off 0x0f2c */	void* Instrumentation[16];
/* off 0x0f6c */	void*	WinSockData;
/* off 0x0f70 */	unsigned long	GdiBatchCount;
/* off 0x0f74 */	unsigned char	InDbgPrint;
/* off 0x0f75 */	unsigned char	FreeStackOnTermination;
/* off 0x0f76 */	unsigned char	HasFiberData;
/* off 0x0f77 */	unsigned char	IdealProcessor;
/* off 0x0f78 */	unsigned long	Spare3;
/* off 0x0f7c */	void*	ReservedForPerf;
/* off 0x0f80 */	void*	ReservedForOle;
/* off 0x0f84 */	unsigned long	WaitingOnLoaderLock;
/* off 0x0f88 */	struct _Wx86ThreadState	Wx86Thread;
/* off 0x0f94 */	void**	TlsExpansionSlots;
/* off 0x0f98 */	unsigned long	ImpersonationLocale;
/* off 0x0f9c */	unsigned long	IsImpersonating;
/* off 0x0fa0 */	void*	NlsCache;
/* off 0x0fa4 */	void*	pShimData;
/* off 0x0fa8 */	unsigned long	HeapVirtualAffinity;
/* off 0x0fac */	void*	CurrentTransactionHandle;
/* off 0x0fb0 */	struct _TEB_ACTIVE_FRAME*	ActiveFrame;
/* off 0x0fb4 */	unsigned char	SafeThunkCall;
/* off 0x0fb5 */	unsigned char BooleanSpare[3];
};
struct _TEB_ACTIVE_FRAME /* sizeof 0000000c 12 */
{
/* off 0x0000 */	unsigned long	Flags;
/* off 0x0004 */	struct _TEB_ACTIVE_FRAME*	Previous;
/* off 0x0008 */	struct _TEB_ACTIVE_FRAME_CONTEXT*	Context;
};
struct _TEB_ACTIVE_FRAME_CONTEXT /* sizeof 00000008 8 */
{
/* off 0x0000 */	unsigned long	Flags;
/* off 0x0004 */	char*	FrameName;
};
struct _PCI_HEADER_TYPE_0 /* sizeof 00000030 48 */
{
/* off 0x0000 */	unsigned long BaseAddresses[6];
/* off 0x0018 */	unsigned long	CIS;
/* off 0x001c */	unsigned short	SubVendorID;
/* off 0x001e */	unsigned short	SubSystemID;
/* off 0x0020 */	unsigned long	ROMBaseAddress;
/* off 0x0024 */	unsigned char	CapabilitiesPtr;
/* off 0x0025 */	unsigned char Reserved1[3];
/* off 0x0028 */	unsigned long	Reserved2;
/* off 0x002c */	unsigned char	InterruptLine;
/* off 0x002d */	unsigned char	InterruptPin;
/* off 0x002e */	unsigned char	MinimumGrant;
/* off 0x002f */	unsigned char	MaximumLatency;
};
struct _PCI_HEADER_TYPE_1 /* sizeof 00000030 48 */
{
/* off 0x0000 */	unsigned long BaseAddresses[2];
/* off 0x0008 */	unsigned char	PrimaryBus;
/* off 0x0009 */	unsigned char	SecondaryBus;
/* off 0x000a */	unsigned char	SubordinateBus;
/* off 0x000b */	unsigned char	SecondaryLatency;
/* off 0x000c */	unsigned char	IOBase;
/* off 0x000d */	unsigned char	IOLimit;
/* off 0x000e */	unsigned short	SecondaryStatus;
/* off 0x0010 */	unsigned short	MemoryBase;
/* off 0x0012 */	unsigned short	MemoryLimit;
/* off 0x0014 */	unsigned short	PrefetchBase;
/* off 0x0016 */	unsigned short	PrefetchLimit;
/* off 0x0018 */	unsigned long	PrefetchBaseUpper32;
/* off 0x001c */	unsigned long	PrefetchLimitUpper32;
/* off 0x0020 */	unsigned short	IOBaseUpper16;
/* off 0x0022 */	unsigned short	IOLimitUpper16;
/* off 0x0024 */	unsigned char	CapabilitiesPtr;
/* off 0x0025 */	unsigned char Reserved1[3];
/* off 0x0028 */	unsigned long	ROMBaseAddress;
/* off 0x002c */	unsigned char	InterruptLine;
/* off 0x002d */	unsigned char	InterruptPin;
/* off 0x002e */	unsigned short	BridgeControl;
};
struct _PCI_HEADER_TYPE_2 /* sizeof 00000030 48 */
{
/* off 0x0000 */	unsigned long	SocketRegistersBaseAddress;
/* off 0x0004 */	unsigned char	CapabilitiesPtr;
/* off 0x0005 */	unsigned char	Reserved;
/* off 0x0006 */	unsigned short	SecondaryStatus;
/* off 0x0008 */	unsigned char	PrimaryBus;
/* off 0x0009 */	unsigned char	SecondaryBus;
/* off 0x000a */	unsigned char	SubordinateBus;
/* off 0x000b */	unsigned char	SecondaryLatency;
/* off 0x000c */	struct __unnamed Range[4];
/* off 0x002c */	unsigned char	InterruptLine;
/* off 0x002d */	unsigned char	InterruptPin;
/* off 0x002e */	unsigned short	BridgeControl;
};
struct _HEAP_FREE_ENTRY_EXTRA /* sizeof 00000004 4 */
{
/* off 0x0000 */	unsigned short	TagIndex;
/* off 0x0002 */	unsigned short	FreeBackTraceIndex;
};
struct _POOL_TRACKER_TABLE /* sizeof 0000001c 28 */
{
/* off 0x0000 */	unsigned long	Key;
/* off 0x0004 */	unsigned long	NonPagedAllocs;
/* off 0x0008 */	unsigned long	NonPagedFrees;
/* off 0x000c */	unsigned long	NonPagedBytes;
/* off 0x0010 */	unsigned long	PagedAllocs;
/* off 0x0014 */	unsigned long	PagedFrees;
/* off 0x0018 */	unsigned long	PagedBytes;
};
enum _PS_QUOTA_TYPE
{
	PsNonPagedPool	=0x00000000	,//0
	PsPagedPool	=0x00000001	,//0
	PsPageFile	=0x00000002	,//0
	PsQuotaTypes	=0x00000003	,//0
};
struct _PHYSICAL_MEMORY_DESCRIPTOR /* sizeof 00000010 16 */
{
/* off 0x0000 */	unsigned long	NumberOfRuns;
/* off 0x0004 */	unsigned long	NumberOfPages;
/* off 0x0008 */	struct _PHYSICAL_MEMORY_RUN Run[1];
};
struct _IMAGE_DEBUG_DIRECTORY /* sizeof 0000001c 28 */
{
/* off 0x0000 */	unsigned long	Characteristics;
/* off 0x0004 */	unsigned long	TimeDateStamp;
/* off 0x0008 */	unsigned short	MajorVersion;
/* off 0x000a */	unsigned short	MinorVersion;
/* off 0x000c */	unsigned long	Type;
/* off 0x0010 */	unsigned long	SizeOfData;
/* off 0x0014 */	unsigned long	AddressOfRawData;
/* off 0x0018 */	unsigned long	PointerToRawData;
};
struct _POP_POWER_ACTION /* sizeof 00000040 64 */
{
/* off 0x0000 */	unsigned char	Updates;
/* off 0x0001 */	unsigned char	State;
/* off 0x0002 */	unsigned char	Shutdown;
/* off 0x0004 */	enum POWER_ACTION	Action;
/* off 0x0008 */	enum _SYSTEM_POWER_STATE	LightestState;
/* off 0x000c */	unsigned long	Flags;
/* off 0x0010 */	long	Status;
/* off 0x0014 */	unsigned char	IrpMinor;
/* off 0x0018 */	enum _SYSTEM_POWER_STATE	SystemState;
/* off 0x001c */	enum _SYSTEM_POWER_STATE	NextSystemState;
/* off 0x0020 */	struct _POP_SHUTDOWN_BUG_CHECK*	ShutdownBugCode;
/* off 0x0024 */	struct _POP_DEVICE_SYS_STATE*	DevState;
/* off 0x0028 */	struct _POP_HIBER_CONTEXT*	HiberContext;
/* off 0x002c */	enum _SYSTEM_POWER_STATE	LastWakeState;
/* off 0x0030 */	unsigned __int64	WakeTime;
/* off 0x0038 */	unsigned __int64	SleepTime;
};
struct _POP_SHUTDOWN_BUG_CHECK /* sizeof 00000014 20 */
{
/* off 0x0000 */	unsigned long	Code;
/* off 0x0004 */	unsigned long	Parameter1;
/* off 0x0008 */	unsigned long	Parameter2;
/* off 0x000c */	unsigned long	Parameter3;
/* off 0x0010 */	unsigned long	Parameter4;
};
struct _PO_NOTIFY_ORDER_LEVEL /* sizeof 00000048 72 */
{
/* off 0x0000 */	struct _KEVENT	LevelReady;
/* off 0x0010 */	unsigned long	DeviceCount;
/* off 0x0014 */	unsigned long	ActiveCount;
/* off 0x0018 */	struct _LIST_ENTRY	WaitSleep;
/* off 0x0020 */	struct _LIST_ENTRY	ReadySleep;
/* off 0x0028 */	struct _LIST_ENTRY	Pending;
/* off 0x0030 */	struct _LIST_ENTRY	Complete;
/* off 0x0038 */	struct _LIST_ENTRY	ReadyS0;
/* off 0x0040 */	struct _LIST_ENTRY	WaitS0;
};
struct _PO_DEVICE_NOTIFY_ORDER /* sizeof 00000248 584 */
{
/* off 0x0000 */	unsigned long	DevNodeSequence;
/* off 0x0004 */	struct _DEVICE_OBJECT**	WarmEjectPdoPointer;
/* off 0x0008 */	struct _PO_NOTIFY_ORDER_LEVEL OrderLevel[8];
};
struct _POP_DEVICE_POWER_IRP /* sizeof 0000002c 44 */
{
/* off 0x0000 */	struct _SINGLE_LIST_ENTRY	Free;
/* off 0x0004 */	struct _IRP*	Irp;
/* off 0x0008 */	struct _PO_DEVICE_NOTIFY*	Notify;
/* off 0x000c */	struct _LIST_ENTRY	Pending;
/* off 0x0014 */	struct _LIST_ENTRY	Complete;
/* off 0x001c */	struct _LIST_ENTRY	Abort;
/* off 0x0024 */	struct _LIST_ENTRY	Failed;
};
struct _POP_DEVICE_SYS_STATE /* sizeof 00000620 1568 */
{
/* off 0x0000 */	unsigned char	IrpMinor;
/* off 0x0004 */	enum _SYSTEM_POWER_STATE	SystemState;
/* off 0x0008 */	struct _KEVENT	Event;
/* off 0x0018 */	unsigned long	SpinLock;
/* off 0x001c */	struct _KTHREAD*	Thread;
/* off 0x0020 */	unsigned char	GetNewDeviceList;
/* off 0x0024 */	struct _PO_DEVICE_NOTIFY_ORDER	Order;
/* off 0x026c */	long	Status;
/* off 0x0270 */	struct _DEVICE_OBJECT*	FailedDevice;
/* off 0x0274 */	unsigned char	Waking;
/* off 0x0275 */	unsigned char	Cancelled;
/* off 0x0276 */	unsigned char	IgnoreErrors;
/* off 0x0277 */	unsigned char	IgnoreNotImplemented;
/* off 0x0278 */	unsigned char	WaitAny;
/* off 0x0279 */	unsigned char	WaitAll;
/* off 0x027c */	struct _LIST_ENTRY	PresentIrpQueue;
/* off 0x0284 */	struct _POP_DEVICE_POWER_IRP	Head;
/* off 0x02b0 */	struct _POP_DEVICE_POWER_IRP PowerIrpState[20];
};
struct _PO_HIBER_PERF /* sizeof 00000048 72 */
{
/* off 0x0000 */	unsigned __int64	IoTicks;
/* off 0x0008 */	unsigned __int64	InitTicks;
/* off 0x0010 */	unsigned __int64	CopyTicks;
/* off 0x0018 */	unsigned __int64	StartCount;
/* off 0x0020 */	unsigned long	ElapsedTime;
/* off 0x0024 */	unsigned long	IoTime;
/* off 0x0028 */	unsigned long	CopyTime;
/* off 0x002c */	unsigned long	InitTime;
/* off 0x0030 */	unsigned long	PagesWritten;
/* off 0x0034 */	unsigned long	PagesProcessed;
/* off 0x0038 */	unsigned long	BytesCopied;
/* off 0x003c */	unsigned long	DumpCount;
/* off 0x0040 */	unsigned long	FileRuns;
};
struct _POP_HIBER_CONTEXT /* sizeof 000000e0 224 */
{
/* off 0x0000 */	unsigned char	WriteToFile;
/* off 0x0001 */	unsigned char	ReserveLoaderMemory;
/* off 0x0002 */	unsigned char	ReserveFreeMemory;
/* off 0x0003 */	unsigned char	VerifyOnWake;
/* off 0x0004 */	unsigned char	Reset;
/* off 0x0005 */	unsigned char	HiberFlags;
/* off 0x0006 */	unsigned char	LinkFile;
/* off 0x0008 */	void*	LinkFileHandle;
/* off 0x000c */	unsigned long	Lock;
/* off 0x0010 */	unsigned char	MapFrozen;
/* off 0x0014 */	struct _RTL_BITMAP	MemoryMap;
/* off 0x001c */	struct _LIST_ENTRY	ClonedRanges;
/* off 0x0024 */	unsigned long	ClonedRangeCount;
/* off 0x0028 */	struct _LIST_ENTRY*	NextCloneRange;
/* off 0x002c */	unsigned long	NextPreserve;
/* off 0x0030 */	struct _MDL*	LoaderMdl;
/* off 0x0034 */	struct _MDL*	Clones;
/* off 0x0038 */	unsigned char*	NextClone;
/* off 0x003c */	unsigned long	NoClones;
/* off 0x0040 */	struct _MDL*	Spares;
/* off 0x0048 */	unsigned __int64	PagesOut;
/* off 0x0050 */	void*	IoPage;
/* off 0x0054 */	void*	CurrentMcb;
/* off 0x0058 */	struct _DUMP_STACK_CONTEXT*	DumpStack;
/* off 0x005c */	struct _KPROCESSOR_STATE*	WakeState;
/* off 0x0060 */	unsigned long	NoRanges;
/* off 0x0064 */	unsigned long	HiberVa;
/* off 0x0068 */	union _LARGE_INTEGER	HiberPte;
/* off 0x0070 */	long	Status;
/* off 0x0074 */	struct PO_MEMORY_IMAGE*	MemoryImage;
/* off 0x0078 */	struct _PO_MEMORY_RANGE_ARRAY*	TableHead;
/* off 0x007c */	unsigned char*	CompressionWorkspace;
/* off 0x0080 */	unsigned char*	CompressedWriteBuffer;
/* off 0x0084 */	unsigned long*	PerformanceStats;
/* off 0x0088 */	void*	CompressionBlock;
/* off 0x008c */	void*	DmaIO;
/* off 0x0090 */	void*	TemporaryHeap;
/* off 0x0098 */	struct _PO_HIBER_PERF	PerfInfo;
};
struct _DUMP_INITIALIZATION_CONTEXT /* sizeof 00000070 112 */
{
/* off 0x0000 */	unsigned long	Length;
/* off 0x0004 */	unsigned long	Reserved;
/* off 0x0008 */	void*	MemoryBlock;
/* off 0x000c */	void* CommonBuffer[2];
/* off 0x0018 */	union _LARGE_INTEGER PhysicalAddress[2];
/* off 0x0028 */	void( __cdecl *StallRoutine)(unsigned long);
/* off 0x002c */	unsigned char( __cdecl *OpenRoutine)(union _LARGE_INTEGER);
/* off 0x0030 */	long( __cdecl *WriteRoutine)(union _LARGE_INTEGER*,struct _MDL*);
/* off 0x0034 */	void( __cdecl *FinishRoutine)();
/* off 0x0038 */	struct _ADAPTER_OBJECT*	AdapterObject;
/* off 0x003c */	void*	MappedRegisterBase;
/* off 0x0040 */	void*	PortConfiguration;
/* off 0x0044 */	unsigned char	CrashDump;
/* off 0x0048 */	unsigned long	MaximumTransferSize;
/* off 0x004c */	unsigned long	CommonBufferSize;
/* off 0x0050 */	void*	TargetAddress;
/* off 0x0054 */	long( __cdecl *WritePendingRoutine)(long,union _LARGE_INTEGER*,struct _MDL*,void*);
/* off 0x0058 */	unsigned long	PartitionStyle;
/* off 0x005c */	struct __unnamed	DiskInfo;
};
struct _DUMP_STACK_CONTEXT /* sizeof 000000b0 176 */
{
/* off 0x0000 */	struct _DUMP_INITIALIZATION_CONTEXT	Init;
/* off 0x0070 */	union _LARGE_INTEGER	PartitionOffset;
/* off 0x0078 */	void*	DumpPointers;
/* off 0x007c */	unsigned long	PointersLength;
/* off 0x0080 */	unsigned short*	ModulePrefix;
/* off 0x0084 */	struct _LIST_ENTRY	DriverList;
/* off 0x008c */	struct _STRING	InitMsg;
/* off 0x0094 */	struct _STRING	ProgMsg;
/* off 0x009c */	struct _STRING	DoneMsg;
/* off 0x00a4 */	void*	FileObject;
/* off 0x00a8 */	enum _DEVICE_USAGE_NOTIFICATION_TYPE	UsageType;
};
struct _ADAPTER_OBJECT /* sizeof 00000000 0 */
{
};
enum _DEVICE_USAGE_NOTIFICATION_TYPE
{
	DeviceUsageTypeUndefined	=0x00000000	,//0
	DeviceUsageTypePaging	=0x00000001	,//0
	DeviceUsageTypeHibernation	=0x00000002	,//0
	DeviceUsageTypeDumpFile	=0x00000003	,//0
};
struct PO_MEMORY_IMAGE /* sizeof 000000a8 168 */
{
/* off 0x0000 */	unsigned long	Signature;
/* off 0x0004 */	unsigned long	Version;
/* off 0x0008 */	unsigned long	CheckSum;
/* off 0x000c */	unsigned long	LengthSelf;
/* off 0x0010 */	unsigned long	PageSelf;
/* off 0x0014 */	unsigned long	PageSize;
/* off 0x0018 */	unsigned long	ImageType;
/* off 0x0020 */	union _LARGE_INTEGER	SystemTime;
/* off 0x0028 */	unsigned __int64	InterruptTime;
/* off 0x0030 */	unsigned long	FeatureFlags;
/* off 0x0034 */	unsigned char	HiberFlags;
/* off 0x0035 */	unsigned char spare[3];
/* off 0x0038 */	unsigned long	NoHiberPtes;
/* off 0x003c */	unsigned long	HiberVa;
/* off 0x0040 */	union _LARGE_INTEGER	HiberPte;
/* off 0x0048 */	unsigned long	NoFreePages;
/* off 0x004c */	unsigned long	FreeMapCheck;
/* off 0x0050 */	unsigned long	WakeCheck;
/* off 0x0054 */	unsigned long	TotalPages;
/* off 0x0058 */	unsigned long	FirstTablePage;
/* off 0x005c */	unsigned long	LastFilePage;
/* off 0x0060 */	struct _PO_HIBER_PERF	PerfInfo;
};
struct _PO_MEMORY_RANGE_ARRAY /* sizeof 00000010 16 */
{
union
{
/* off 0x0000 */	struct __unnamed	Range;
/* off 0x0000 */	struct __unnamed	Link;
};
};
struct _PORT_MESSAGE /* sizeof 00000018 24 */
{
/* off 0x0000 */	struct __unnamed	u1;
/* off 0x0004 */	struct __unnamed	u2;
union
{
/* off 0x0008 */	struct _CLIENT_ID	ClientId;
/* off 0x0008 */	double	DoNotUseThisField;
};
/* off 0x0010 */	unsigned long	MessageId;
union
{
/* off 0x0014 */	unsigned long	ClientViewSize;
/* off 0x0014 */	unsigned long	CallbackId;
};
};
struct _LPCP_MESSAGE /* sizeof 00000030 48 */
{
union
{
/* off 0x0000 */	struct _LIST_ENTRY	Entry;
struct
{
/* off 0x0000 */	struct _SINGLE_LIST_ENTRY	FreeEntry;
/* off 0x0004 */	unsigned long	Reserved0;
};
};
/* off 0x0008 */	void*	SenderPort;
/* off 0x000c */	struct _ETHREAD*	RepliedToThread;
/* off 0x0010 */	void*	PortContext;
/* off 0x0018 */	struct _PORT_MESSAGE	Request;
};
struct _MMVAD_SHORT /* sizeof 00000018 24 */
{
/* off 0x0000 */	unsigned long	StartingVpn;
/* off 0x0004 */	unsigned long	EndingVpn;
/* off 0x0008 */	struct _MMVAD*	Parent;
/* off 0x000c */	struct _MMVAD*	LeftChild;
/* off 0x0010 */	struct _MMVAD*	RightChild;
/* off 0x0014 */	struct __unnamed	u;
};
struct _INITIAL_PRIVILEGE_SET /* sizeof 0000002c 44 */
{
/* off 0x0000 */	unsigned long	PrivilegeCount;
/* off 0x0004 */	unsigned long	Control;
/* off 0x0008 */	struct _LUID_AND_ATTRIBUTES Privilege[3];
};
struct _PRIVILEGE_SET /* sizeof 00000014 20 */
{
/* off 0x0000 */	unsigned long	PrivilegeCount;
/* off 0x0004 */	unsigned long	Control;
/* off 0x0008 */	struct _LUID_AND_ATTRIBUTES Privilege[1];
};
struct _PLUGPLAY_EVENT_BLOCK /* sizeof 00000038 56 */
{
/* off 0x0000 */	struct _GUID	EventGuid;
/* off 0x0010 */	enum _PLUGPLAY_EVENT_CATEGORY	EventCategory;
/* off 0x0014 */	unsigned long*	Result;
/* off 0x0018 */	unsigned long	Flags;
/* off 0x001c */	unsigned long	TotalSize;
/* off 0x0020 */	void*	DeviceObject;
/* off 0x0024 */	struct __unnamed	u;
};
struct _PNP_DEVICE_EVENT_ENTRY /* sizeof 00000058 88 */
{
/* off 0x0000 */	struct _LIST_ENTRY	ListEntry;
/* off 0x0008 */	unsigned long	Argument;
/* off 0x000c */	struct _KEVENT*	CallerEvent;
/* off 0x0010 */	void( __cdecl *Callback)(void*);
/* off 0x0014 */	void*	Context;
/* off 0x0018 */	enum _PNP_VETO_TYPE*	VetoType;
/* off 0x001c */	struct _UNICODE_STRING*	VetoName;
/* off 0x0020 */	struct _PLUGPLAY_EVENT_BLOCK	Data;
};
enum _PNP_VETO_TYPE
{
	PNP_VetoTypeUnknown	=0x00000000	,//0
	PNP_VetoLegacyDevice	=0x00000001	,//0
	PNP_VetoPendingClose	=0x00000002	,//0
	PNP_VetoWindowsApp	=0x00000003	,//0
	PNP_VetoWindowsService	=0x00000004	,//0
	PNP_VetoOutstandingOpen	=0x00000005	,//0
	PNP_VetoDevice	=0x00000006	,//0
	PNP_VetoDriver	=0x00000007	,//0
	PNP_VetoIllegalDeviceRequest	=0x00000008	,//0
	PNP_VetoInsufficientPower	=0x00000009	,//0
	PNP_VetoNonDisableable	=0x0000000a	,//0
	PNP_VetoLegacyDriver	=0x0000000b	,//0
	PNP_VetoInsufficientRights	=0x0000000c	,//0
};
enum _PLUGPLAY_EVENT_CATEGORY
{
	HardwareProfileChangeEvent	=0x00000000	,//0
	TargetDeviceChangeEvent	=0x00000001	,//0
	DeviceClassChangeEvent	=0x00000002	,//0
	CustomDeviceEvent	=0x00000003	,//0
	DeviceInstallEvent	=0x00000004	,//0
	DeviceArrivalEvent	=0x00000005	,//0
	PowerEvent	=0x00000006	,//0
	VetoEvent	=0x00000007	,//0
	BlockedDriverEvent	=0x00000008	,//0
	MaxPlugEventCategory	=0x00000009	,//0
};
struct _PNP_DEVICE_EVENT_LIST /* sizeof 0000004c 76 */
{
/* off 0x0000 */	long	Status;
/* off 0x0004 */	struct _KMUTANT	EventQueueMutex;
/* off 0x0024 */	struct _FAST_MUTEX	Lock;
/* off 0x0044 */	struct _LIST_ENTRY	List;
};
enum _MMSYSTEM_PTE_POOL_TYPE
{
	SystemPteSpace	=0x00000000	,//0
	NonPagedPoolExpansion	=0x00000001	,//0
	MaximumPtePoolTypes	=0x00000002	,//0
};
struct _MMPFN /* sizeof 00000018 24 */
{
/* off 0x0000 */	struct __unnamed	u1;
/* off 0x0004 */	struct _MMPTE*	PteAddress;
/* off 0x0008 */	struct __unnamed	u2;
/* off 0x000c */	struct __unnamed	u3;
/* off 0x0010 */	struct _MMPTE	OriginalPte;
/* off 0x0014 */	struct __unnamed	u4;
};
struct _MMPFNENTRY /* sizeof 00000004 4 */
{
/* off 0x0000 */	unsigned long	Modified:1	 /* start bit 0 */;
/* off 0x0000 */	unsigned long	ReadInProgress:1	 /* start bit 1 */;
/* off 0x0000 */	unsigned long	WriteInProgress:1	 /* start bit 2 */;
/* off 0x0000 */	unsigned long	PrototypePte:1	 /* start bit 3 */;
/* off 0x0000 */	unsigned long	PageColor:3	 /* start bit 4 */;
/* off 0x0000 */	unsigned long	ParityError:1	 /* start bit 7 */;
/* off 0x0000 */	unsigned long	PageLocation:3	 /* start bit 8 */;
/* off 0x0000 */	unsigned long	RemovalRequested:1	 /* start bit 11 */;
/* off 0x0000 */	unsigned long	CacheAttribute:2	 /* start bit 12 */;
/* off 0x0000 */	unsigned long	Rom:1	 /* start bit 14 */;
/* off 0x0000 */	unsigned long	LockCharged:1	 /* start bit 15 */;
/* off 0x0000 */	unsigned long	DontUse:16	 /* start bit 16 */;
};
struct _HANDLE_TABLE_ENTRY /* sizeof 00000008 8 */
{
union
{
/* off 0x0000 */	void*	Object;
/* off 0x0000 */	unsigned long	ObAttributes;
/* off 0x0000 */	struct _HANDLE_TABLE_ENTRY_INFO*	InfoTable;
/* off 0x0000 */	unsigned long	Value;
};
union
{
/* off 0x0004 */	unsigned long	GrantedAccess;
struct
{
/* off 0x0004 */	unsigned short	GrantedAccessIndex;
/* off 0x0006 */	unsigned short	CreatorBackTraceIndex;
};
/* off 0x0004 */	long	NextFreeTableEntry;
};
};
struct _HANDLE_TABLE_ENTRY_INFO /* sizeof 00000004 4 */
{
/* off 0x0000 */	unsigned long	AuditMask;
};
struct _LPCP_PORT_QUEUE /* sizeof 00000010 16 */
{
/* off 0x0000 */	struct _LPCP_NONPAGED_PORT_QUEUE*	NonPagedPortQueue;
/* off 0x0004 */	struct _KSEMAPHORE*	Semaphore;
/* off 0x0008 */	struct _LIST_ENTRY	ReceiveHead;
};
struct _TOKEN_CONTROL /* sizeof 00000028 40 */
{
/* off 0x0000 */	struct _LUID	TokenId;
/* off 0x0008 */	struct _LUID	AuthenticationId;
/* off 0x0010 */	struct _LUID	ModifiedId;
/* off 0x0018 */	struct _TOKEN_SOURCE	TokenSource;
};
struct _SECURITY_CLIENT_CONTEXT /* sizeof 0000003c 60 */
{
/* off 0x0000 */	struct _SECURITY_QUALITY_OF_SERVICE	SecurityQos;
/* off 0x000c */	void*	ClientToken;
/* off 0x0010 */	unsigned char	DirectlyAccessClientToken;
/* off 0x0011 */	unsigned char	DirectAccessEffectiveOnly;
/* off 0x0012 */	unsigned char	ServerIsRemote;
/* off 0x0014 */	struct _TOKEN_CONTROL	ClientTokenControl;
};
struct _LPCP_PORT_OBJECT /* sizeof 000000a4 164 */
{
/* off 0x0000 */	struct _LPCP_PORT_OBJECT*	ConnectionPort;
/* off 0x0004 */	struct _LPCP_PORT_OBJECT*	ConnectedPort;
/* off 0x0008 */	struct _LPCP_PORT_QUEUE	MsgQueue;
/* off 0x0018 */	struct _CLIENT_ID	Creator;
/* off 0x0020 */	void*	ClientSectionBase;
/* off 0x0024 */	void*	ServerSectionBase;
/* off 0x0028 */	void*	PortContext;
/* off 0x002c */	struct _ETHREAD*	ClientThread;
/* off 0x0030 */	struct _SECURITY_QUALITY_OF_SERVICE	SecurityQos;
/* off 0x003c */	struct _SECURITY_CLIENT_CONTEXT	StaticSecurity;
/* off 0x0078 */	struct _LIST_ENTRY	LpcReplyChainHead;
/* off 0x0080 */	struct _LIST_ENTRY	LpcDataInfoChainHead;
union
{
/* off 0x0088 */	struct _EPROCESS*	ServerProcess;
/* off 0x0088 */	struct _EPROCESS*	MappingProcess;
};
/* off 0x008c */	unsigned short	MaxMessageLength;
/* off 0x008e */	unsigned short	MaxConnectionInfoLength;
/* off 0x0090 */	unsigned long	Flags;
/* off 0x0094 */	struct _KEVENT	WaitEvent;
};
struct _LPCP_NONPAGED_PORT_QUEUE /* sizeof 00000018 24 */
{
/* off 0x0000 */	struct _KSEMAPHORE	Semaphore;
/* off 0x0014 */	struct _LPCP_PORT_OBJECT*	BackPointer;
};
struct _POOL_HACKER /* sizeof 00000028 40 */
{
/* off 0x0000 */	struct _POOL_HEADER	Header;
/* off 0x0008 */	unsigned long Contents[8];
};
struct _IO_SECURITY_CONTEXT /* sizeof 00000010 16 */
{
/* off 0x0000 */	struct _SECURITY_QUALITY_OF_SERVICE*	SecurityQos;
/* off 0x0004 */	struct _ACCESS_STATE*	AccessState;
/* off 0x0008 */	unsigned long	DesiredAccess;
/* off 0x000c */	unsigned long	FullCreateOptions;
};
struct _NAMED_PIPE_CREATE_PARAMETERS /* sizeof 00000028 40 */
{
/* off 0x0000 */	unsigned long	NamedPipeType;
/* off 0x0004 */	unsigned long	ReadMode;
/* off 0x0008 */	unsigned long	CompletionMode;
/* off 0x000c */	unsigned long	MaximumInstances;
/* off 0x0010 */	unsigned long	InboundQuota;
/* off 0x0014 */	unsigned long	OutboundQuota;
/* off 0x0018 */	union _LARGE_INTEGER	DefaultTimeout;
/* off 0x0020 */	unsigned char	TimeoutSpecified;
};
struct _MAILSLOT_CREATE_PARAMETERS /* sizeof 00000018 24 */
{
/* off 0x0000 */	unsigned long	MailslotQuota;
/* off 0x0004 */	unsigned long	MaximumMessageSize;
/* off 0x0008 */	union _LARGE_INTEGER	ReadTimeout;
/* off 0x0010 */	unsigned char	TimeoutSpecified;
};
enum _FILE_INFORMATION_CLASS
{
	FileDirectoryInformation	=0x00000001	,//0
	FileFullDirectoryInformation	=0x00000002	,//0
	FileBothDirectoryInformation	=0x00000003	,//0
	FileBasicInformation	=0x00000004	,//0
	FileStandardInformation	=0x00000005	,//0
	FileInternalInformation	=0x00000006	,//0
	FileEaInformation	=0x00000007	,//0
	FileAccessInformation	=0x00000008	,//0
	FileNameInformation	=0x00000009	,//0
	FileRenameInformation	=0x0000000a	,//0
	FileLinkInformation	=0x0000000b	,//0
	FileNamesInformation	=0x0000000c	,//0
	FileDispositionInformation	=0x0000000d	,//0
	FilePositionInformation	=0x0000000e	,//0
	FileFullEaInformation	=0x0000000f	,//0
	FileModeInformation	=0x00000010	,//0
	FileAlignmentInformation	=0x00000011	,//0
	FileAllInformation	=0x00000012	,//0
	FileAllocationInformation	=0x00000013	,//0
	FileEndOfFileInformation	=0x00000014	,//0
	FileAlternateNameInformation	=0x00000015	,//0
	FileStreamInformation	=0x00000016	,//0
	FilePipeInformation	=0x00000017	,//0
	FilePipeLocalInformation	=0x00000018	,//0
	FilePipeRemoteInformation	=0x00000019	,//0
	FileMailslotQueryInformation	=0x0000001a	,//0
	FileMailslotSetInformation	=0x0000001b	,//0
	FileCompressionInformation	=0x0000001c	,//0
	FileObjectIdInformation	=0x0000001d	,//0
	FileCompletionInformation	=0x0000001e	,//0
	FileMoveClusterInformation	=0x0000001f	,//0
	FileQuotaInformation	=0x00000020	,//0
	FileReparsePointInformation	=0x00000021	,//0
	FileNetworkOpenInformation	=0x00000022	,//0
	FileAttributeTagInformation	=0x00000023	,//0
	FileTrackingInformation	=0x00000024	,//0
	FileIdBothDirectoryInformation	=0x00000025	,//0
	FileIdFullDirectoryInformation	=0x00000026	,//0
	FileValidDataLengthInformation	=0x00000027	,//0
	FileShortNameInformation	=0x00000028	,//0
	FileMaximumInformation	=0x00000029	,//0
};
enum _FSINFOCLASS
{
	FileFsVolumeInformation	=0x00000001	,//0
	FileFsLabelInformation	=0x00000002	,//0
	FileFsSizeInformation	=0x00000003	,//0
	FileFsDeviceInformation	=0x00000004	,//0
	FileFsAttributeInformation	=0x00000005	,//0
	FileFsControlInformation	=0x00000006	,//0
	FileFsFullSizeInformation	=0x00000007	,//0
	FileFsObjectIdInformation	=0x00000008	,//0
	FileFsDriverPathInformation	=0x00000009	,//0
	FileFsMaximumInformation	=0x0000000a	,//0
};
struct _SCSI_REQUEST_BLOCK /* sizeof 00000000 0 */
{
};
struct _SID_IDENTIFIER_AUTHORITY /* sizeof 00000006 6 */
{
/* off 0x0000 */	unsigned char Value[6];
};
struct _SID /* sizeof 0000000c 12 */
{
/* off 0x0000 */	unsigned char	Revision;
/* off 0x0001 */	unsigned char	SubAuthorityCount;
/* off 0x0002 */	struct _SID_IDENTIFIER_AUTHORITY	IdentifierAuthority;
/* off 0x0008 */	unsigned long SubAuthority[1];
};
struct _FILE_GET_QUOTA_INFORMATION /* sizeof 00000014 20 */
{
/* off 0x0000 */	unsigned long	NextEntryOffset;
/* off 0x0004 */	unsigned long	SidLength;
/* off 0x0008 */	struct _SID	Sid;
};
enum _DEVICE_RELATION_TYPE
{
	BusRelations	=0x00000000	,//0
	EjectionRelations	=0x00000001	,//0
	PowerRelations	=0x00000002	,//0
	RemovalRelations	=0x00000003	,//0
	TargetDeviceRelation	=0x00000004	,//0
	SingleBusRelations	=0x00000005	,//0
};
struct _DEVICE_CAPABILITIES /* sizeof 00000040 64 */
{
/* off 0x0000 */	unsigned short	Size;
/* off 0x0002 */	unsigned short	Version;
/* off 0x0004 */	unsigned long	DeviceD1:1	 /* start bit 0 */;
/* off 0x0004 */	unsigned long	DeviceD2:1	 /* start bit 1 */;
/* off 0x0004 */	unsigned long	LockSupported:1	 /* start bit 2 */;
/* off 0x0004 */	unsigned long	EjectSupported:1	 /* start bit 3 */;
/* off 0x0004 */	unsigned long	Removable:1	 /* start bit 4 */;
/* off 0x0004 */	unsigned long	DockDevice:1	 /* start bit 5 */;
/* off 0x0004 */	unsigned long	UniqueID:1	 /* start bit 6 */;
/* off 0x0004 */	unsigned long	SilentInstall:1	 /* start bit 7 */;
/* off 0x0004 */	unsigned long	RawDeviceOK:1	 /* start bit 8 */;
/* off 0x0004 */	unsigned long	SurpriseRemovalOK:1	 /* start bit 9 */;
/* off 0x0004 */	unsigned long	WakeFromD0:1	 /* start bit 10 */;
/* off 0x0004 */	unsigned long	WakeFromD1:1	 /* start bit 11 */;
/* off 0x0004 */	unsigned long	WakeFromD2:1	 /* start bit 12 */;
/* off 0x0004 */	unsigned long	WakeFromD3:1	 /* start bit 13 */;
/* off 0x0004 */	unsigned long	HardwareDisabled:1	 /* start bit 14 */;
/* off 0x0004 */	unsigned long	NonDynamic:1	 /* start bit 15 */;
/* off 0x0004 */	unsigned long	WarmEjectSupported:1	 /* start bit 16 */;
/* off 0x0004 */	unsigned long	NoDisplayInUI:1	 /* start bit 17 */;
/* off 0x0004 */	unsigned long	Reserved:14	 /* start bit 18 */;
/* off 0x0008 */	unsigned long	Address;
/* off 0x000c */	unsigned long	UINumber;
/* off 0x0010 */	enum _DEVICE_POWER_STATE DeviceState[7];
/* off 0x002c */	enum _SYSTEM_POWER_STATE	SystemWake;
/* off 0x0030 */	enum _DEVICE_POWER_STATE	DeviceWake;
/* off 0x0034 */	unsigned long	D1Latency;
/* off 0x0038 */	unsigned long	D2Latency;
/* off 0x003c */	unsigned long	D3Latency;
};
enum BUS_QUERY_ID_TYPE
{
	BusQueryDeviceID	=0x00000000	,//0
	BusQueryHardwareIDs	=0x00000001	,//0
	BusQueryCompatibleIDs	=0x00000002	,//0
	BusQueryInstanceID	=0x00000003	,//0
	BusQueryDeviceSerialNumber	=0x00000004	,//0
};
enum DEVICE_TEXT_TYPE
{
	DeviceTextDescription	=0x00000000	,//0
	DeviceTextLocationInformation	=0x00000001	,//0
};
struct _POWER_SEQUENCE /* sizeof 0000000c 12 */
{
/* off 0x0000 */	unsigned long	SequenceD1;
/* off 0x0004 */	unsigned long	SequenceD2;
/* off 0x0008 */	unsigned long	SequenceD3;
};
enum _POWER_STATE_TYPE
{
	SystemPowerState	=0x00000000	,//0
	DevicePowerState	=0x00000001	,//0
};
struct _MI_VERIFIER_POOL_HEADER /* sizeof 00000008 8 */
{
/* off 0x0000 */	unsigned long	ListIndex;
/* off 0x0004 */	struct _MI_VERIFIER_DRIVER_ENTRY*	Verifier;
};
struct _MI_VERIFIER_DRIVER_ENTRY /* sizeof 00000060 96 */
{
/* off 0x0000 */	struct _LIST_ENTRY	Links;
/* off 0x0008 */	unsigned long	Loads;
/* off 0x000c */	unsigned long	Unloads;
/* off 0x0010 */	struct _UNICODE_STRING	BaseName;
/* off 0x0018 */	void*	StartAddress;
/* off 0x001c */	void*	EndAddress;
/* off 0x0020 */	unsigned long	Flags;
/* off 0x0024 */	unsigned long	Signature;
/* off 0x0028 */	unsigned long	Reserved;
/* off 0x002c */	unsigned long	VerifierPoolLock;
/* off 0x0030 */	struct _VI_POOL_ENTRY*	PoolHash;
/* off 0x0034 */	unsigned long	PoolHashSize;
/* off 0x0038 */	unsigned long	PoolHashFree;
/* off 0x003c */	unsigned long	PoolHashReserved;
/* off 0x0040 */	unsigned long	CurrentPagedPoolAllocations;
/* off 0x0044 */	unsigned long	CurrentNonPagedPoolAllocations;
/* off 0x0048 */	unsigned long	PeakPagedPoolAllocations;
/* off 0x004c */	unsigned long	PeakNonPagedPoolAllocations;
/* off 0x0050 */	unsigned long	PagedBytes;
/* off 0x0054 */	unsigned long	NonPagedBytes;
/* off 0x0058 */	unsigned long	PeakPagedBytes;
/* off 0x005c */	unsigned long	PeakNonPagedBytes;
};
struct _VI_POOL_ENTRY_INUSE /* sizeof 00000010 16 */
{
/* off 0x0000 */	void*	VirtualAddress;
/* off 0x0004 */	void*	CallingAddress;
/* off 0x0008 */	unsigned long	NumberOfBytes;
/* off 0x000c */	unsigned long	Tag;
};
struct _VI_POOL_ENTRY /* sizeof 00000010 16 */
{
union
{
/* off 0x0000 */	struct _VI_POOL_ENTRY_INUSE	InUse;
/* off 0x0000 */	unsigned long	FreeListNext;
};
};
struct _CM_KEY_BODY /* sizeof 00000044 68 */
{
/* off 0x0000 */	unsigned long	Type;
/* off 0x0004 */	struct _CM_KEY_CONTROL_BLOCK*	KeyControlBlock;
/* off 0x0008 */	struct _CM_NOTIFY_BLOCK*	NotifyBlock;
/* off 0x000c */	void*	ProcessID;
/* off 0x0010 */	unsigned long	Callers;
/* off 0x0014 */	void* CallerAddress[10];
/* off 0x003c */	struct _LIST_ENTRY	KeyBodyList;
};
struct _CM_NOTIFY_BLOCK /* sizeof 0000002c 44 */
{
/* off 0x0000 */	struct _LIST_ENTRY	HiveList;
/* off 0x0008 */	struct _LIST_ENTRY	PostList;
/* off 0x0010 */	struct _CM_KEY_CONTROL_BLOCK*	KeyControlBlock;
/* off 0x0014 */	struct _CM_KEY_BODY*	KeyBody;
/* off 0x0018 */	unsigned long	Filter:30	 /* start bit 0 */;
/* off 0x0018 */	unsigned long	WatchTree:1	 /* start bit 30 */;
/* off 0x0018 */	unsigned long	NotifyPending:1	 /* start bit 31 */;
/* off 0x001c */	struct _SECURITY_SUBJECT_CONTEXT	SubjectContext;
};
enum _FS_FILTER_SECTION_SYNC_TYPE
{
	SyncTypeOther	=0x00000000	,//0
	SyncTypeCreateSection	=0x00000001	,//0
};
struct _MMFREE_POOL_ENTRY /* sizeof 00000014 20 */
{
/* off 0x0000 */	struct _LIST_ENTRY	List;
/* off 0x0008 */	unsigned long	Size;
/* off 0x000c */	unsigned long	Signature;
/* off 0x0010 */	struct _MMFREE_POOL_ENTRY*	Owner;
};
struct _SYSPTES_HEADER /* sizeof 0000000c 12 */
{
/* off 0x0000 */	struct _LIST_ENTRY	ListHead;
/* off 0x0008 */	unsigned long	Count;
};
