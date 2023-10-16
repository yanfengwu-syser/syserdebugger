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
union _ULARGE_INTEGER /* sizeof 00000008 8 */
{
struct
{
/* off 0x0000 */	unsigned long	LowPart;
/* off 0x0004 */	unsigned long	HighPart;
};
/* off 0x0000 */	
	struct  /* sizeof 00000008 8 */
	{
	/* off 0x0000 */	unsigned long	LowPart;
	/* off 0x0004 */	unsigned long	HighPart;
	}	u;
/* off 0x0000 */	unsigned __int64	QuadPart;
};
union _LARGE_INTEGER /* sizeof 00000008 8 */
{
struct
{
/* off 0x0000 */	unsigned long	LowPart;
/* off 0x0004 */	long	HighPart;
};
/* off 0x0000 */	
	struct  /* sizeof 00000008 8 */
	{
	/* off 0x0000 */	unsigned long	LowPart;
	/* off 0x0004 */	long	HighPart;
	}	u;
/* off 0x0000 */	__int64	QuadPart;
};
struct _TP_CALLBACK_ENVIRON /* sizeof 00000020 32 */
{
/* off 0x0000 */	unsigned long	Version;
/* off 0x0004 */	struct _TP_POOL*	Pool;
/* off 0x0008 */	struct _TP_CLEANUP_GROUP*	CleanupGroup;
/* off 0x000c */	void( __stdcall *CleanupGroupCancelCallback)(void*,void*);
/* off 0x0010 */	void*	RaceDll;
/* off 0x0014 */	struct _ACTIVATION_CONTEXT*	ActivationContext;
/* off 0x0018 */	void( __stdcall *FinalizationCallback)(struct _TP_CALLBACK_INSTANCE*,void*);
/* off 0x001c */	
	union  /* sizeof 00000004 4 */
	{
	/* off 0x0000 */	unsigned long	Flags;
	/* off 0x0000 */	
		struct  /* sizeof 00000004 4 */
		{
		/* off 0x0000 */	unsigned long	LongFunction:1	 /* start bit 0 */;
		/* off 0x0000 */	unsigned long	Private:31	 /* start bit 1 */;
		}	s;
	}	u;
};
struct _TP_POOL /* sizeof 00000000 0 */
{
};
struct _TP_CLEANUP_GROUP /* sizeof 00000000 0 */
{
};
struct _ACTIVATION_CONTEXT /* sizeof 00000000 0 */
{
};
struct _TP_CALLBACK_INSTANCE /* sizeof 00000000 0 */
{
};
struct _TP_TASK_CALLBACKS /* sizeof 00000008 8 */
{
/* off 0x0000 */	void( __stdcall *ExecuteCallback)(struct _TP_CALLBACK_INSTANCE*,struct _TP_TASK*);
/* off 0x0004 */	void( __stdcall *Unposted)(struct _TP_TASK*,struct _TP_POOL*);
};
struct _TP_TASK /* sizeof 00000004 4 */
{
/* off 0x0000 */	struct _TP_TASK_CALLBACKS*	Callbacks;
};
struct _TP_DIRECT /* sizeof 00000004 4 */
{
/* off 0x0000 */	void( __stdcall *Callback)(struct _TP_CALLBACK_INSTANCE*,struct _TP_DIRECT*,void*,struct _IO_STATUS_BLOCK*);
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
struct _LIST_ENTRY /* sizeof 00000008 8 */
{
/* off 0x0000 */	struct _LIST_ENTRY*	Flink;
/* off 0x0004 */	struct _LIST_ENTRY*	Blink;
};
struct _SINGLE_LIST_ENTRY /* sizeof 00000004 4 */
{
/* off 0x0000 */	struct _SINGLE_LIST_ENTRY*	Next;
};
struct _UNICODE_STRING /* sizeof 00000008 8 */
{
/* off 0x0000 */	unsigned short	Length;
/* off 0x0002 */	unsigned short	MaximumLength;
/* off 0x0004 */	unsigned short*	Buffer;
};
struct _STRING /* sizeof 00000008 8 */
{
/* off 0x0000 */	unsigned short	Length;
/* off 0x0002 */	unsigned short	MaximumLength;
/* off 0x0004 */	char*	Buffer;
};
struct _LUID /* sizeof 00000008 8 */
{
/* off 0x0000 */	unsigned long	LowPart;
/* off 0x0004 */	long	HighPart;
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
struct _GENERAL_LOOKASIDE_POOL /* sizeof 00000048 72 */
{
union
{
/* off 0x0000 */	union _SLIST_HEADER	ListHead;
/* off 0x0000 */	struct _SINGLE_LIST_ENTRY	SingleListHead;
};
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
union
{
/* off 0x0028 */	void*( __stdcall *AllocateEx)(enum _POOL_TYPE,unsigned long,unsigned long,struct _LOOKASIDE_LIST_EX*);
/* off 0x0028 */	void*( __stdcall *Allocate)(enum _POOL_TYPE,unsigned long,unsigned long);
};
union
{
/* off 0x002c */	void( __stdcall *FreeEx)(void*,struct _LOOKASIDE_LIST_EX*);
/* off 0x002c */	void( __stdcall *Free)(void*);
};
/* off 0x0030 */	struct _LIST_ENTRY	ListEntry;
/* off 0x0038 */	unsigned long	LastTotalAllocates;
union
{
/* off 0x003c */	unsigned long	LastAllocateMisses;
/* off 0x003c */	unsigned long	LastAllocateHits;
};
/* off 0x0040 */	unsigned long Future[2];
};
struct _KDPC_DATA /* sizeof 00000014 20 */
{
/* off 0x0000 */	struct _LIST_ENTRY	DpcListHead;
/* off 0x0008 */	unsigned long	DpcLock;
/* off 0x000c */	long	DpcQueueDepth;
/* off 0x0010 */	unsigned long	DpcCount;
};
struct _DISPATCHER_HEADER /* sizeof 00000010 16 */
{
union
{
struct
{
/* off 0x0000 */	unsigned char	Type;
union
{
/* off 0x0001 */	unsigned char	Abandoned;
/* off 0x0001 */	unsigned char	Absolute;
/* off 0x0001 */	unsigned char	NpxIrql;
/* off 0x0001 */	unsigned char	Signalling;
};
union
{
/* off 0x0002 */	unsigned char	Size;
/* off 0x0002 */	unsigned char	Hand;
};
union
{
/* off 0x0003 */	unsigned char	Inserted;
/* off 0x0003 */	unsigned char	DebugActive;
/* off 0x0003 */	unsigned char	DpcActive;
};
struct
{
};
/* off 0x0000 */	long	Lock;
};
};
/* off 0x0004 */	long	SignalState;
/* off 0x0008 */	struct _LIST_ENTRY	WaitListHead;
};
struct _KEVENT /* sizeof 00000010 16 */
{
/* off 0x0000 */	struct _DISPATCHER_HEADER	Header;
};
struct _KDPC /* sizeof 00000020 32 */
{
/* off 0x0000 */	unsigned char	Type;
/* off 0x0001 */	unsigned char	Importance;
/* off 0x0002 */	unsigned short	Number;
/* off 0x0004 */	struct _LIST_ENTRY	DpcListEntry;
/* off 0x000c */	void( __stdcall *DeferredRoutine)(struct _KDPC*,void*,void*,void*);
/* off 0x0010 */	void*	DeferredContext;
/* off 0x0014 */	void*	SystemArgument1;
/* off 0x0018 */	void*	SystemArgument2;
/* off 0x001c */	void*	DpcData;
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
struct _FX_SAVE_AREA /* sizeof 00000210 528 */
{
/* off 0x0000 */	
	union  /* sizeof 00000208 520 */
	{
	/* off 0x0000 */	struct _FNSAVE_FORMAT	FnArea;
	/* off 0x0000 */	struct _FXSAVE_FORMAT	FxArea;
	}	U;
/* off 0x0208 */	unsigned long	NpxSavedCpu;
/* off 0x020c */	unsigned long	Cr0NpxState;
};
struct _KTIMER /* sizeof 00000028 40 */
{
/* off 0x0000 */	struct _DISPATCHER_HEADER	Header;
/* off 0x0010 */	union _ULARGE_INTEGER	DueTime;
/* off 0x0018 */	struct _LIST_ENTRY	TimerListEntry;
/* off 0x0020 */	struct _KDPC*	Dpc;
/* off 0x0024 */	long	Period;
};
struct _PROCESSOR_POWER_STATE /* sizeof 000000c8 200 */
{
/* off 0x0000 */	struct _PPM_IDLE_STATES*	IdleStates;
/* off 0x0008 */	unsigned __int64	LastTimeCheck;
/* off 0x0010 */	unsigned __int64	IdleTimeAccumulated;
union
{
/* off 0x0018 */	
	struct  /* sizeof 00000008 8 */
	{
	/* off 0x0000 */	unsigned __int64	IdleTransitionTime;
	}	Native;
/* off 0x0018 */	
	struct  /* sizeof 00000008 8 */
	{
	/* off 0x0000 */	unsigned __int64	LastIdleCheck;
	}	Hv;
};
/* off 0x0020 */	struct PPM_IDLE_ACCOUNTING*	IdleAccounting;
/* off 0x0024 */	struct _PPM_PERF_STATES*	PerfStates;
/* off 0x0028 */	unsigned long	LastKernelUserTime;
/* off 0x002c */	unsigned long	LastIdleThreadKTime;
/* off 0x0030 */	unsigned __int64	LastGlobalTimeHv;
/* off 0x0038 */	unsigned __int64	LastProcessorTimeHv;
/* off 0x0040 */	unsigned char	ThermalConstraint;
/* off 0x0041 */	unsigned char	LastBusyPercentage;
/* off 0x0042 */	
	union  /* sizeof 00000002 2 */
	{
	/* off 0x0000 */	unsigned short	AsUSHORT;
	struct
	{
	/* off 0x0000 */	unsigned short	PStateDomain:1	 /* start bit 0 */;
	/* off 0x0000 */	unsigned short	PStateDomainIdleAccounting:1	 /* start bit 1 */;
	/* off 0x0000 */	unsigned short	Reserved:14	 /* start bit 2 */;
	};
	}	Flags;
/* off 0x0048 */	struct _KTIMER	PerfTimer;
/* off 0x0070 */	struct _KDPC	PerfDpc;
/* off 0x0090 */	unsigned long	LastSysTime;
/* off 0x0094 */	struct _KPRCB*	PStateMaster;
/* off 0x0098 */	unsigned long	PStateSet;
/* off 0x009c */	unsigned long	CurrentPState;
/* off 0x00a0 */	unsigned long	DesiredPState;
/* off 0x00a4 */	unsigned long	PStateIdleStartTime;
/* off 0x00a8 */	unsigned long	PStateIdleTime;
/* off 0x00ac */	unsigned long	LastPStateIdleTime;
/* off 0x00b0 */	unsigned long	PStateStartTime;
/* off 0x00b4 */	unsigned long	DiaIndex;
/* off 0x00b8 */	unsigned long	Reserved0;
/* off 0x00bc */	unsigned long	WmiDispatchPtr;
/* off 0x00c0 */	long	WmiInterfaceEnabled;
};
struct _CACHE_DESCRIPTOR /* sizeof 0000000c 12 */
{
/* off 0x0000 */	unsigned char	Level;
/* off 0x0001 */	unsigned char	Associativity;
/* off 0x0002 */	unsigned short	LineSize;
/* off 0x0004 */	unsigned long	Size;
/* off 0x0008 */	enum _PROCESSOR_CACHE_TYPE	Type;
};
struct _KPRCB /* sizeof 00002008 8200 */
{
/* off 0x0000 */	unsigned short	MinorVersion;
/* off 0x0002 */	unsigned short	MajorVersion;
/* off 0x0004 */	struct _KTHREAD*	CurrentThread;
/* off 0x0008 */	struct _KTHREAD*	NextThread;
/* off 0x000c */	struct _KTHREAD*	IdleThread;
/* off 0x0010 */	unsigned char	Number;
/* off 0x0011 */	unsigned char	NestingLevel;
/* off 0x0012 */	unsigned short	BuildType;
/* off 0x0014 */	unsigned long	SetMember;
/* off 0x0018 */	char	CpuType;
/* off 0x0019 */	char	CpuID;
union
{
/* off 0x001a */	unsigned short	CpuStep;
struct
{
/* off 0x001a */	unsigned char	CpuStepping;
/* off 0x001b */	unsigned char	CpuModel;
};
};
/* off 0x001c */	struct _KPROCESSOR_STATE	ProcessorState;
/* off 0x033c */	unsigned long KernelReserved[16];
/* off 0x037c */	unsigned long HalReserved[16];
/* off 0x03bc */	unsigned long	CFlushSize;
/* off 0x03c0 */	unsigned char	CoresPerPhysicalProcessor;
/* off 0x03c1 */	unsigned char	LogicalProcessorsPerCore;
/* off 0x03c2 */	unsigned char PrcbPad0[2];
/* off 0x03c4 */	unsigned long	MHz;
/* off 0x03c8 */	unsigned char PrcbPad1[80];
/* off 0x0418 */	struct _KSPIN_LOCK_QUEUE LockQueue[49];
/* off 0x05a0 */	struct _KTHREAD*	NpxThread;
/* off 0x05a4 */	unsigned long	InterruptCount;
/* off 0x05a8 */	unsigned long	KernelTime;
/* off 0x05ac */	unsigned long	UserTime;
/* off 0x05b0 */	unsigned long	DpcTime;
/* off 0x05b4 */	unsigned long	DpcTimeCount;
/* off 0x05b8 */	unsigned long	InterruptTime;
/* off 0x05bc */	unsigned long	AdjustDpcThreshold;
/* off 0x05c0 */	unsigned long	PageColor;
/* off 0x05c4 */	unsigned char	SkipTick;
/* off 0x05c5 */	unsigned char	DebuggerSavedIRQL;
/* off 0x05c6 */	unsigned char	NodeColor;
/* off 0x05c7 */	unsigned char	PollSlot;
/* off 0x05c8 */	unsigned long	NodeShiftedColor;
/* off 0x05cc */	struct _KNODE*	ParentNode;
/* off 0x05d0 */	unsigned long	MultiThreadProcessorSet;
/* off 0x05d4 */	struct _KPRCB*	MultiThreadSetMaster;
/* off 0x05d8 */	unsigned long	SecondaryColorMask;
/* off 0x05dc */	unsigned long	DpcTimeLimit;
/* off 0x05e0 */	unsigned long	CcFastReadNoWait;
/* off 0x05e4 */	unsigned long	CcFastReadWait;
/* off 0x05e8 */	unsigned long	CcFastReadNotPossible;
/* off 0x05ec */	unsigned long	CcCopyReadNoWait;
/* off 0x05f0 */	unsigned long	CcCopyReadWait;
/* off 0x05f4 */	unsigned long	CcCopyReadNoWaitMiss;
/* off 0x05f8 */	long	MmSpinLockOrdering;
/* off 0x05fc */	long	IoReadOperationCount;
/* off 0x0600 */	long	IoWriteOperationCount;
/* off 0x0604 */	long	IoOtherOperationCount;
/* off 0x0608 */	union _LARGE_INTEGER	IoReadTransferCount;
/* off 0x0610 */	union _LARGE_INTEGER	IoWriteTransferCount;
/* off 0x0618 */	union _LARGE_INTEGER	IoOtherTransferCount;
/* off 0x0620 */	unsigned long	CcFastMdlReadNoWait;
/* off 0x0624 */	unsigned long	CcFastMdlReadWait;
/* off 0x0628 */	unsigned long	CcFastMdlReadNotPossible;
/* off 0x062c */	unsigned long	CcMapDataNoWait;
/* off 0x0630 */	unsigned long	CcMapDataWait;
/* off 0x0634 */	unsigned long	CcPinMappedDataCount;
/* off 0x0638 */	unsigned long	CcPinReadNoWait;
/* off 0x063c */	unsigned long	CcPinReadWait;
/* off 0x0640 */	unsigned long	CcMdlReadNoWait;
/* off 0x0644 */	unsigned long	CcMdlReadWait;
/* off 0x0648 */	unsigned long	CcLazyWriteHotSpots;
/* off 0x064c */	unsigned long	CcLazyWriteIos;
/* off 0x0650 */	unsigned long	CcLazyWritePages;
/* off 0x0654 */	unsigned long	CcDataFlushes;
/* off 0x0658 */	unsigned long	CcDataPages;
/* off 0x065c */	unsigned long	CcLostDelayedWrites;
/* off 0x0660 */	unsigned long	CcFastReadResourceMiss;
/* off 0x0664 */	unsigned long	CcCopyReadWaitMiss;
/* off 0x0668 */	unsigned long	CcFastMdlReadResourceMiss;
/* off 0x066c */	unsigned long	CcMapDataNoWaitMiss;
/* off 0x0670 */	unsigned long	CcMapDataWaitMiss;
/* off 0x0674 */	unsigned long	CcPinReadNoWaitMiss;
/* off 0x0678 */	unsigned long	CcPinReadWaitMiss;
/* off 0x067c */	unsigned long	CcMdlReadNoWaitMiss;
/* off 0x0680 */	unsigned long	CcMdlReadWaitMiss;
/* off 0x0684 */	unsigned long	CcReadAheadIos;
/* off 0x0688 */	unsigned long	KeAlignmentFixupCount;
/* off 0x068c */	unsigned long	KeExceptionDispatchCount;
/* off 0x0690 */	unsigned long	KeSystemCalls;
/* off 0x0694 */	unsigned long PrcbPad2[3];
/* off 0x06a0 */	struct _PP_LOOKASIDE_LIST PPLookasideList[16];
/* off 0x0720 */	struct _GENERAL_LOOKASIDE_POOL PPNPagedLookasideList[32];
/* off 0x1020 */	struct _GENERAL_LOOKASIDE_POOL PPPagedLookasideList[32];
/* off 0x1920 */	unsigned long	PacketBarrier;
/* off 0x1924 */	long	ReverseStall;
/* off 0x1928 */	void*	IpiFrame;
/* off 0x192c */	unsigned char PrcbPad3[52];
/* off 0x1960 */	void* CurrentPacket[3];
/* off 0x196c */	unsigned long	TargetSet;
/* off 0x1970 */	void( __stdcall *WorkerRoutine)(void*,void*,void*,void*);
/* off 0x1974 */	unsigned long	IpiFrozen;
/* off 0x1978 */	unsigned char PrcbPad4[40];
/* off 0x19a0 */	unsigned long	RequestSummary;
/* off 0x19a4 */	struct _KPRCB*	SignalDone;
/* off 0x19a8 */	unsigned char PrcbPad5[56];
/* off 0x19e0 */	struct _KDPC_DATA DpcData[2];
/* off 0x1a08 */	void*	DpcStack;
/* off 0x1a0c */	long	MaximumDpcQueueDepth;
/* off 0x1a10 */	unsigned long	DpcRequestRate;
/* off 0x1a14 */	unsigned long	MinimumDpcRate;
/* off 0x1a18 */	unsigned char	DpcInterruptRequested;
/* off 0x1a19 */	unsigned char	DpcThreadRequested;
/* off 0x1a1a */	unsigned char	DpcRoutineActive;
/* off 0x1a1b */	unsigned char	DpcThreadActive;
/* off 0x1a1c */	unsigned long	PrcbLock;
/* off 0x1a20 */	unsigned long	DpcLastCount;
/* off 0x1a24 */	unsigned long	TimerHand;
/* off 0x1a28 */	unsigned long	TimerRequest;
/* off 0x1a2c */	void*	PrcbPad41;
/* off 0x1a30 */	struct _KEVENT	DpcEvent;
/* off 0x1a40 */	unsigned char	ThreadDpcEnable;
/* off 0x1a41 */	unsigned char	QuantumEnd;
/* off 0x1a42 */	unsigned char	PrcbPad50;
/* off 0x1a43 */	unsigned char	IdleSchedule;
/* off 0x1a44 */	long	DpcSetEventRequest;
/* off 0x1a48 */	long	Sleeping;
/* off 0x1a4c */	unsigned long	PeriodicCount;
/* off 0x1a50 */	unsigned long	PeriodicBias;
/* off 0x1a54 */	unsigned char PrcbPad51[6];
/* off 0x1a5c */	long	TickOffset;
/* off 0x1a60 */	struct _KDPC	CallDpc;
/* off 0x1a80 */	long	ClockKeepAlive;
/* off 0x1a84 */	unsigned char	ClockCheckSlot;
/* off 0x1a85 */	unsigned char	ClockPollCycle;
/* off 0x1a86 */	unsigned char PrcbPad6[2];
/* off 0x1a88 */	long	DpcWatchdogPeriod;
/* off 0x1a8c */	long	DpcWatchdogCount;
/* off 0x1a90 */	long	ThreadWatchdogPeriod;
/* off 0x1a94 */	long	ThreadWatchdogCount;
/* off 0x1a98 */	unsigned long PrcbPad70[2];
/* off 0x1aa0 */	struct _LIST_ENTRY	WaitListHead;
/* off 0x1aa8 */	unsigned long	WaitLock;
/* off 0x1aac */	unsigned long	ReadySummary;
/* off 0x1ab0 */	unsigned long	QueueIndex;
/* off 0x1ab4 */	struct _SINGLE_LIST_ENTRY	DeferredReadyListHead;
/* off 0x1ab8 */	unsigned __int64	StartCycles;
/* off 0x1ac0 */	unsigned __int64	CycleTime;
/* off 0x1ac8 */	unsigned __int64 PrcbPad71[3];
/* off 0x1ae0 */	struct _LIST_ENTRY DispatcherReadyListHead[32];
/* off 0x1be0 */	void*	ChainedInterruptList;
/* off 0x1be4 */	long	LookasideIrpFloat;
/* off 0x1be8 */	long	MmPageFaultCount;
/* off 0x1bec */	long	MmCopyOnWriteCount;
/* off 0x1bf0 */	long	MmTransitionCount;
/* off 0x1bf4 */	long	MmCacheTransitionCount;
/* off 0x1bf8 */	long	MmDemandZeroCount;
/* off 0x1bfc */	long	MmPageReadCount;
/* off 0x1c00 */	long	MmPageReadIoCount;
/* off 0x1c04 */	long	MmCacheReadCount;
/* off 0x1c08 */	long	MmCacheIoCount;
/* off 0x1c0c */	long	MmDirtyPagesWriteCount;
/* off 0x1c10 */	long	MmDirtyWriteIoCount;
/* off 0x1c14 */	long	MmMappedPagesWriteCount;
/* off 0x1c18 */	long	MmMappedWriteIoCount;
/* off 0x1c1c */	unsigned long	CachedCommit;
/* off 0x1c20 */	unsigned long	CachedResidentAvailable;
/* off 0x1c24 */	void*	HyperPte;
/* off 0x1c28 */	unsigned char	CpuVendor;
/* off 0x1c29 */	unsigned char PrcbPad8[3];
/* off 0x1c2c */	unsigned char VendorString[13];
/* off 0x1c39 */	unsigned char	InitialApicId;
/* off 0x1c3a */	unsigned char	LogicalProcessorsPerPhysicalProcessor;
/* off 0x1c3b */	unsigned char PrcbPad9[5];
/* off 0x1c40 */	unsigned long	FeatureBits;
/* off 0x1c48 */	union _LARGE_INTEGER	UpdateSignature;
/* off 0x1c50 */	unsigned __int64	IsrTime;
/* off 0x1c58 */	unsigned __int64	SpareField1;
/* off 0x1c60 */	struct _FX_SAVE_AREA	NpxSaveArea;
/* off 0x1e70 */	struct _PROCESSOR_POWER_STATE	PowerState;
/* off 0x1f38 */	struct _KDPC	DpcWatchdogDpc;
/* off 0x1f58 */	struct _KTIMER	DpcWatchdogTimer;
/* off 0x1f80 */	void*	WheaInfo;
/* off 0x1f84 */	void*	EtwSupport;
/* off 0x1f88 */	union _SLIST_HEADER	InterruptObjectPool;
/* off 0x1f90 */	union _SLIST_HEADER	HypercallPageList;
/* off 0x1f98 */	void*	HypercallPageVirtual;
/* off 0x1f9c */	void*	VirtualApicAssist;
/* off 0x1fa0 */	unsigned __int64*	StatisticsPage;
/* off 0x1fa4 */	void*	RateControl;
/* off 0x1fa8 */	struct _CACHE_DESCRIPTOR Cache[5];
/* off 0x1fe4 */	unsigned long	CacheCount;
/* off 0x1fe8 */	unsigned long CacheProcessorMask[5];
/* off 0x1ffc */	unsigned long	PackageProcessorSet;
/* off 0x2000 */	unsigned long	CoreProcessorSet;
};
struct _KAPC_STATE /* sizeof 00000018 24 */
{
/* off 0x0000 */	struct _LIST_ENTRY ApcListHead[2];
/* off 0x0010 */	struct _KPROCESS*	Process;
/* off 0x0014 */	unsigned char	KernelApcInProgress;
/* off 0x0015 */	unsigned char	KernelApcPending;
/* off 0x0016 */	unsigned char	UserApcPending;
};
struct _KWAIT_BLOCK /* sizeof 00000018 24 */
{
/* off 0x0000 */	struct _LIST_ENTRY	WaitListEntry;
/* off 0x0008 */	struct _KTHREAD*	Thread;
/* off 0x000c */	void*	Object;
/* off 0x0010 */	struct _KWAIT_BLOCK*	NextWaitBlock;
/* off 0x0014 */	unsigned short	WaitKey;
/* off 0x0016 */	unsigned char	WaitType;
/* off 0x0017 */	unsigned char	SpareByte;
};
struct _KAPC /* sizeof 00000030 48 */
{
/* off 0x0000 */	unsigned char	Type;
/* off 0x0001 */	unsigned char	SpareByte0;
/* off 0x0002 */	unsigned char	Size;
/* off 0x0003 */	unsigned char	SpareByte1;
/* off 0x0004 */	unsigned long	SpareLong0;
/* off 0x0008 */	struct _KTHREAD*	Thread;
/* off 0x000c */	struct _LIST_ENTRY	ApcListEntry;
/* off 0x0014 */	void( __stdcall *KernelRoutine)(struct _KAPC*,void( __stdcall **)(void*,void*,void*),void**,void**,void**);
/* off 0x0018 */	void( __stdcall *RundownRoutine)(struct _KAPC*);
/* off 0x001c */	void( __stdcall *NormalRoutine)(void*,void*,void*);
/* off 0x0020 */	void*	NormalContext;
/* off 0x0024 */	void*	SystemArgument1;
/* off 0x0028 */	void*	SystemArgument2;
/* off 0x002c */	char	ApcStateIndex;
/* off 0x002d */	char	ApcMode;
/* off 0x002e */	unsigned char	Inserted;
};
struct _KSEMAPHORE /* sizeof 00000014 20 */
{
/* off 0x0000 */	struct _DISPATCHER_HEADER	Header;
/* off 0x0010 */	long	Limit;
};
struct _KTHREAD /* sizeof 000001e0 480 */
{
/* off 0x0000 */	struct _DISPATCHER_HEADER	Header;
/* off 0x0010 */	unsigned __int64	CycleTime;
/* off 0x0018 */	unsigned long	HighCycleTime;
/* off 0x0020 */	unsigned __int64	QuantumTarget;
/* off 0x0028 */	void*	InitialStack;
/* off 0x002c */	void*	StackLimit;
/* off 0x0030 */	void*	KernelStack;
/* off 0x0034 */	unsigned long	ThreadLock;
union
{
/* off 0x0038 */	struct _KAPC_STATE	ApcState;
struct
{
/* off 0x0038 */	unsigned char ApcStateFill[23];
/* off 0x004f */	char	Priority;
};
};
/* off 0x0050 */	unsigned short	NextProcessor;
/* off 0x0052 */	unsigned short	DeferredProcessor;
/* off 0x0054 */	unsigned long	ApcQueueLock;
/* off 0x0058 */	unsigned long	ContextSwitches;
/* off 0x005c */	unsigned char	State;
/* off 0x005d */	unsigned char	NpxState;
/* off 0x005e */	unsigned char	WaitIrql;
/* off 0x005f */	char	WaitMode;
/* off 0x0060 */	long	WaitStatus;
union
{
/* off 0x0064 */	struct _KWAIT_BLOCK*	WaitBlockList;
/* off 0x0064 */	struct _KGATE*	GateObject;
};
union
{
struct
{
/* off 0x0068 */	unsigned long	KernelStackResident:1	 /* start bit 0 */;
/* off 0x0068 */	unsigned long	ReadyTransition:1	 /* start bit 1 */;
/* off 0x0068 */	unsigned long	ProcessReadyQueue:1	 /* start bit 2 */;
/* off 0x0068 */	unsigned long	WaitNext:1	 /* start bit 3 */;
/* off 0x0068 */	unsigned long	SystemAffinityActive:1	 /* start bit 4 */;
/* off 0x0068 */	unsigned long	Alertable:1	 /* start bit 5 */;
/* off 0x0068 */	unsigned long	GdiFlushActive:1	 /* start bit 6 */;
/* off 0x0068 */	unsigned long	UserStackWalkActive:1	 /* start bit 7 */;
/* off 0x0068 */	unsigned long	Reserved:24	 /* start bit 8 */;
};
/* off 0x0068 */	long	MiscFlags;
};
/* off 0x006c */	unsigned char	WaitReason;
/* off 0x006d */	unsigned char	SwapBusy;
/* off 0x006e */	unsigned char Alerted[2];
union
{
/* off 0x0070 */	struct _LIST_ENTRY	WaitListEntry;
/* off 0x0070 */	struct _SINGLE_LIST_ENTRY	SwapListEntry;
};
/* off 0x0078 */	struct _KQUEUE*	Queue;
/* off 0x007c */	unsigned long	WaitTime;
union
{
struct
{
/* off 0x0080 */	short	KernelApcDisable;
/* off 0x0082 */	short	SpecialApcDisable;
};
struct
{
/* off 0x0080 */	unsigned long	CombinedApcDisable;
};
};
/* off 0x0084 */	void*	Teb;
union
{
/* off 0x0088 */	struct _KTIMER	Timer;
/* off 0x0088 */	unsigned char TimerFill[40];
};
union
{
struct
{
/* off 0x00b0 */	unsigned long	AutoAlignment:1	 /* start bit 0 */;
/* off 0x00b0 */	unsigned long	DisableBoost:1	 /* start bit 1 */;
/* off 0x00b0 */	unsigned long	EtwStackTraceApc1Inserted:1	 /* start bit 2 */;
/* off 0x00b0 */	unsigned long	EtwStackTraceApc2Inserted:1	 /* start bit 3 */;
/* off 0x00b0 */	unsigned long	CycleChargePending:1	 /* start bit 4 */;
/* off 0x00b0 */	unsigned long	CalloutActive:1	 /* start bit 5 */;
/* off 0x00b0 */	unsigned long	ApcQueueable:1	 /* start bit 6 */;
/* off 0x00b0 */	unsigned long	EnableStackSwap:1	 /* start bit 7 */;
/* off 0x00b0 */	unsigned long	GuiThread:1	 /* start bit 8 */;
/* off 0x00b0 */	unsigned long	ReservedFlags:23	 /* start bit 9 */;
};
/* off 0x00b0 */	long	ThreadFlags;
};
union
{
/* off 0x00b8 */	struct _KWAIT_BLOCK WaitBlock[4];
struct
{
/* off 0x00b8 */	unsigned char WaitBlockFill0[23];
/* off 0x00cf */	unsigned char	IdealProcessor;
};
struct
{
/* off 0x00b8 */	unsigned char WaitBlockFill1[47];
/* off 0x00e7 */	char	PreviousMode;
};
struct
{
/* off 0x00b8 */	unsigned char WaitBlockFill2[71];
/* off 0x00ff */	unsigned char	ResourceIndex;
};
struct
{
/* off 0x00b8 */	unsigned char WaitBlockFill3[95];
/* off 0x0117 */	unsigned char	LargeStack;
};
};
/* off 0x0118 */	struct _LIST_ENTRY	QueueListEntry;
/* off 0x0120 */	struct _KTRAP_FRAME*	TrapFrame;
/* off 0x0124 */	void*	FirstArgument;
union
{
/* off 0x0128 */	void*	CallbackStack;
/* off 0x0128 */	unsigned long	CallbackDepth;
};
/* off 0x012c */	void*	ServiceTable;
/* off 0x0130 */	unsigned char	ApcStateIndex;
/* off 0x0131 */	char	BasePriority;
/* off 0x0132 */	char	PriorityDecrement;
/* off 0x0133 */	unsigned char	Preempted;
/* off 0x0134 */	unsigned char	AdjustReason;
/* off 0x0135 */	char	AdjustIncrement;
/* off 0x0136 */	unsigned char	Spare01;
/* off 0x0137 */	char	Saturation;
/* off 0x0138 */	unsigned long	SystemCallNumber;
/* off 0x013c */	unsigned long	FreezeCount;
/* off 0x0140 */	unsigned long	UserAffinity;
/* off 0x0144 */	struct _KPROCESS*	Process;
/* off 0x0148 */	unsigned long	Affinity;
/* off 0x014c */	struct _KAPC_STATE* ApcStatePointer[2];
union
{
/* off 0x0154 */	struct _KAPC_STATE	SavedApcState;
struct
{
/* off 0x0154 */	unsigned char SavedApcStateFill[23];
/* off 0x016b */	unsigned char	Spare02;
};
};
/* off 0x016c */	char	SuspendCount;
/* off 0x016d */	unsigned char	UserIdealProcessor;
/* off 0x016e */	unsigned char	Spare03;
/* off 0x016f */	unsigned char	OtherPlatformFill;
/* off 0x0170 */	void*	Win32Thread;
/* off 0x0174 */	void*	StackBase;
union
{
/* off 0x0178 */	struct _KAPC	SuspendApc;
struct
{
/* off 0x0178 */	unsigned char SuspendApcFill0[1];
/* off 0x0179 */	char	Spare04;
};
struct
{
/* off 0x0178 */	unsigned char SuspendApcFill1[3];
/* off 0x017b */	unsigned char	QuantumReset;
};
struct
{
/* off 0x0178 */	unsigned char SuspendApcFill2[4];
/* off 0x017c */	unsigned long	KernelTime;
};
struct
{
/* off 0x0178 */	unsigned char SuspendApcFill3[36];
/* off 0x019c */	struct _KPRCB*	WaitPrcb;
};
struct
{
/* off 0x0178 */	unsigned char SuspendApcFill4[40];
/* off 0x01a0 */	void*	LegoData;
};
struct
{
/* off 0x0178 */	unsigned char SuspendApcFill5[47];
/* off 0x01a7 */	unsigned char	PowerState;
};
};
/* off 0x01a8 */	unsigned long	UserTime;
union
{
/* off 0x01ac */	struct _KSEMAPHORE	SuspendSemaphore;
/* off 0x01ac */	unsigned char SuspendSemaphorefill[20];
};
/* off 0x01c0 */	unsigned long	SListFaultCount;
/* off 0x01c4 */	struct _LIST_ENTRY	ThreadListEntry;
/* off 0x01cc */	struct _LIST_ENTRY	MutantListHead;
/* off 0x01d4 */	void*	SListFaultAddress;
/* off 0x01d8 */	void*	MdlForLockedTeb;
};
struct _KGDTENTRY /* sizeof 00000008 8 */
{
/* off 0x0000 */	unsigned short	LimitLow;
/* off 0x0002 */	unsigned short	BaseLow;
/* off 0x0004 */	
	union  /* sizeof 00000004 4 */
	{
	/* off 0x0000 */	
		struct  /* sizeof 00000004 4 */
		{
		/* off 0x0000 */	unsigned char	BaseMid;
		/* off 0x0001 */	unsigned char	Flags1;
		/* off 0x0002 */	unsigned char	Flags2;
		/* off 0x0003 */	unsigned char	BaseHi;
		}	Bytes;
	/* off 0x0000 */	
		struct  /* sizeof 00000004 4 */
		{
		/* off 0x0000 */	unsigned long	BaseMid:8	 /* start bit 0 */;
		/* off 0x0000 */	unsigned long	Type:5	 /* start bit 8 */;
		/* off 0x0000 */	unsigned long	Dpl:2	 /* start bit 13 */;
		/* off 0x0000 */	unsigned long	Pres:1	 /* start bit 15 */;
		/* off 0x0000 */	unsigned long	LimitHi:4	 /* start bit 16 */;
		/* off 0x0000 */	unsigned long	Sys:1	 /* start bit 20 */;
		/* off 0x0000 */	unsigned long	Reserved_0:1	 /* start bit 21 */;
		/* off 0x0000 */	unsigned long	Default_Big:1	 /* start bit 22 */;
		/* off 0x0000 */	unsigned long	Granularity:1	 /* start bit 23 */;
		/* off 0x0000 */	unsigned long	BaseHi:8	 /* start bit 24 */;
		}	Bits;
	}	HighWord;
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
/* off 0x0000 */	unsigned char	DisableExceptionChainValidation:1	 /* start bit 6 */;
/* off 0x0000 */	unsigned char	Spare:1	 /* start bit 7 */;
};
struct _KPROCESS /* sizeof 00000080 128 */
{
/* off 0x0000 */	struct _DISPATCHER_HEADER	Header;
/* off 0x0010 */	struct _LIST_ENTRY	ProfileListHead;
/* off 0x0018 */	unsigned long	DirectoryTableBase;
/* off 0x001c */	unsigned long	Unused0;
/* off 0x0020 */	struct _KGDTENTRY	LdtDescriptor;
/* off 0x0028 */	struct _KIDTENTRY	Int21Descriptor;
/* off 0x0030 */	unsigned short	IopmOffset;
/* off 0x0032 */	unsigned char	Unused1;
/* off 0x0033 */	unsigned char	Unused2;
/* off 0x0034 */	unsigned long	ActiveProcessors;
/* off 0x0038 */	unsigned long	KernelTime;
/* off 0x003c */	unsigned long	UserTime;
/* off 0x0040 */	struct _LIST_ENTRY	ReadyListHead;
/* off 0x0048 */	struct _SINGLE_LIST_ENTRY	SwapListEntry;
/* off 0x004c */	void*	VdmTrapcHandler;
/* off 0x0050 */	struct _LIST_ENTRY	ThreadListHead;
/* off 0x0058 */	unsigned long	ProcessLock;
/* off 0x005c */	unsigned long	Affinity;
union
{
struct
{
/* off 0x0060 */	long	AutoAlignment:1	 /* start bit 0 */;
/* off 0x0060 */	long	DisableBoost:1	 /* start bit 1 */;
/* off 0x0060 */	long	DisableQuantum:1	 /* start bit 2 */;
/* off 0x0060 */	long	ReservedFlags:29	 /* start bit 3 */;
};
/* off 0x0060 */	long	ProcessFlags;
};
/* off 0x0064 */	char	BasePriority;
/* off 0x0065 */	char	QuantumReset;
/* off 0x0066 */	unsigned char	State;
/* off 0x0067 */	unsigned char	ThreadSeed;
/* off 0x0068 */	unsigned char	PowerState;
/* off 0x0069 */	unsigned char	IdealNode;
/* off 0x006a */	unsigned char	Visited;
union
{
/* off 0x006b */	struct _KEXECUTE_OPTIONS	Flags;
/* off 0x006b */	unsigned char	ExecuteOptions;
};
/* off 0x006c */	unsigned long	StackCount;
/* off 0x0070 */	struct _LIST_ENTRY	ProcessListEntry;
/* off 0x0078 */	unsigned __int64	CycleTime;
};
struct _KGATE /* sizeof 00000010 16 */
{
/* off 0x0000 */	struct _DISPATCHER_HEADER	Header;
};
struct _KQUEUE /* sizeof 00000028 40 */
{
/* off 0x0000 */	struct _DISPATCHER_HEADER	Header;
/* off 0x0010 */	struct _LIST_ENTRY	EntryListHead;
/* off 0x0018 */	unsigned long	CurrentCount;
/* off 0x001c */	unsigned long	MaximumCount;
/* off 0x0020 */	struct _LIST_ENTRY	ThreadListHead;
};
struct _KTRAP_FRAME /* sizeof 0000008c 140 */
{
/* off 0x0000 */	unsigned long	DbgEbp;
/* off 0x0004 */	unsigned long	DbgEip;
/* off 0x0008 */	unsigned long	DbgArgMark;
/* off 0x000c */	unsigned long	DbgArgPointer;
/* off 0x0010 */	unsigned short	TempSegCs;
/* off 0x0012 */	unsigned char	Logging;
/* off 0x0013 */	unsigned char	Reserved;
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
/* off 0x0004 */	enum _EXCEPTION_DISPOSITION( __stdcall *Handler)(struct _EXCEPTION_RECORD*,void*,struct _CONTEXT*,void*);
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
struct _flags /* sizeof 00000001 1 */
{
/* off 0x0000 */	unsigned char	Removable:1	 /* start bit 0 */;
/* off 0x0000 */	unsigned char	Fill:7	 /* start bit 1 */;
};
struct _CACHED_KSTACK_LIST /* sizeof 00000018 24 */
{
/* off 0x0000 */	union _SLIST_HEADER	SListHead;
/* off 0x0008 */	long	MinimumFree;
/* off 0x000c */	unsigned long	Misses;
/* off 0x0010 */	unsigned long	MissesLast;
};
struct _KNODE /* sizeof 00000080 128 */
{
/* off 0x0000 */	union _SLIST_HEADER	PagedPoolSListHead;
/* off 0x0008 */	union _SLIST_HEADER NonPagedPoolSListHead[3];
/* off 0x0020 */	union _SLIST_HEADER	PfnDereferenceSListHead;
/* off 0x0028 */	unsigned long	ProcessorMask;
/* off 0x002c */	unsigned char	Color;
/* off 0x002d */	unsigned char	Seed;
/* off 0x002e */	unsigned char	NodeNumber;
/* off 0x002f */	struct _flags	Flags;
/* off 0x0030 */	unsigned long	MmShiftedColor;
/* off 0x0034 */	unsigned long FreeCount[2];
/* off 0x003c */	struct _SINGLE_LIST_ENTRY*	PfnDeferredList;
/* off 0x0040 */	struct _CACHED_KSTACK_LIST	CachedKernelStacks;
};
struct _GENERAL_LOOKASIDE /* sizeof 00000080 128 */
{
union
{
/* off 0x0000 */	union _SLIST_HEADER	ListHead;
/* off 0x0000 */	struct _SINGLE_LIST_ENTRY	SingleListHead;
};
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
union
{
/* off 0x0028 */	void*( __stdcall *AllocateEx)(enum _POOL_TYPE,unsigned long,unsigned long,struct _LOOKASIDE_LIST_EX*);
/* off 0x0028 */	void*( __stdcall *Allocate)(enum _POOL_TYPE,unsigned long,unsigned long);
};
union
{
/* off 0x002c */	void( __stdcall *FreeEx)(void*,struct _LOOKASIDE_LIST_EX*);
/* off 0x002c */	void( __stdcall *Free)(void*);
};
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
struct _LOOKASIDE_LIST_EX /* sizeof 00000048 72 */
{
/* off 0x0000 */	struct _GENERAL_LOOKASIDE_POOL	L;
};
struct _PPM_IDLE_STATE /* sizeof 00000020 32 */
{
/* off 0x0000 */	long( __fastcall *IdleHandler)(void*,unsigned long);
/* off 0x0004 */	void*	Context;
/* off 0x0008 */	unsigned long	Latency;
/* off 0x000c */	unsigned long	Power;
/* off 0x0010 */	unsigned long	TimeCheck;
/* off 0x0014 */	unsigned long	StateFlags;
/* off 0x0018 */	unsigned char	PromotePercent;
/* off 0x0019 */	unsigned char	DemotePercent;
/* off 0x001a */	unsigned char	PromotePercentBase;
/* off 0x001b */	unsigned char	DemotePercentBase;
/* off 0x001c */	unsigned char	StateType;
};
struct _PPM_IDLE_STATES /* sizeof 0000003c 60 */
{
/* off 0x0000 */	unsigned long	Type;
/* off 0x0004 */	unsigned long	Count;
/* off 0x0008 */	
	union  /* sizeof 00000004 4 */
	{
	/* off 0x0000 */	unsigned long	AsULONG;
	struct
	{
	/* off 0x0000 */	unsigned long	AllowScaling:1	 /* start bit 0 */;
	/* off 0x0000 */	unsigned long	Disabled:1	 /* start bit 1 */;
	/* off 0x0000 */	unsigned long	Hypervisor:2	 /* start bit 2 */;
	/* off 0x0000 */	unsigned long	HvMaxCState:4	 /* start bit 4 */;
	/* off 0x0000 */	unsigned long	Reserved:24	 /* start bit 8 */;
	};
	}	Flags;
/* off 0x000c */	unsigned long	TargetState;
/* off 0x0010 */	unsigned long	ActualState;
/* off 0x0014 */	unsigned long	OldState;
/* off 0x0018 */	unsigned long	TargetProcessors;
/* off 0x001c */	struct _PPM_IDLE_STATE State[1];
};
struct PPM_IDLE_STATE_ACCOUNTING /* sizeof 00000030 48 */
{
/* off 0x0000 */	unsigned long	IdleTransitions;
/* off 0x0004 */	unsigned long	FailedTransitions;
/* off 0x0008 */	unsigned long	InvalidBucketIndex;
/* off 0x0010 */	unsigned __int64	TotalTime;
/* off 0x0018 */	unsigned long IdleTimeBuckets[6];
};
struct PPM_IDLE_ACCOUNTING /* sizeof 00000048 72 */
{
/* off 0x0000 */	unsigned long	StateCount;
/* off 0x0004 */	unsigned long	TotalTransitions;
/* off 0x0008 */	unsigned long	ResetCount;
/* off 0x0010 */	unsigned __int64	StartTime;
/* off 0x0018 */	struct PPM_IDLE_STATE_ACCOUNTING State[1];
};
struct _PPM_PERF_STATE /* sizeof 00000028 40 */
{
/* off 0x0000 */	unsigned long	Frequency;
/* off 0x0004 */	unsigned long	Power;
/* off 0x0008 */	unsigned char	PercentFrequency;
/* off 0x0009 */	unsigned char	IncreaseLevel;
/* off 0x000a */	unsigned char	DecreaseLevel;
/* off 0x000b */	unsigned char	Type;
/* off 0x0010 */	unsigned __int64	Control;
/* off 0x0018 */	unsigned __int64	Status;
/* off 0x0020 */	unsigned long	TotalHitCount;
/* off 0x0024 */	unsigned long	DesiredCount;
};
struct _PPM_PERF_STATES /* sizeof 00000078 120 */
{
/* off 0x0000 */	unsigned long	Count;
/* off 0x0004 */	unsigned long	MaxFrequency;
/* off 0x0008 */	unsigned long	PStateCap;
/* off 0x000c */	unsigned long	TStateCap;
/* off 0x0010 */	unsigned long	MaxPerfState;
/* off 0x0014 */	unsigned long	MinPerfState;
/* off 0x0018 */	unsigned long	LowestPState;
/* off 0x001c */	unsigned long	IncreaseTime;
/* off 0x0020 */	unsigned long	DecreaseTime;
/* off 0x0024 */	unsigned char	BusyAdjThreshold;
/* off 0x0025 */	unsigned char	Reserved;
/* off 0x0026 */	unsigned char	ThrottleStatesOnly;
/* off 0x0027 */	unsigned char	PolicyType;
/* off 0x0028 */	unsigned long	TimerInterval;
/* off 0x002c */	
	union  /* sizeof 00000004 4 */
	{
	/* off 0x0000 */	unsigned long	AsULONG;
	struct
	{
	/* off 0x0000 */	unsigned long	UsingHypervisor:1	 /* start bit 0 */;
	/* off 0x0000 */	unsigned long	NoDomainAccounting:1	 /* start bit 1 */;
	/* off 0x0000 */	unsigned long	IncreasePolicy:2	 /* start bit 2 */;
	/* off 0x0000 */	unsigned long	DecreasePolicy:2	 /* start bit 4 */;
	/* off 0x0000 */	unsigned long	Reserved:26	 /* start bit 6 */;
	};
	}	Flags;
/* off 0x0030 */	unsigned long	TargetProcessors;
/* off 0x0034 */	long( __fastcall *PStateHandler)(unsigned long,unsigned __int64,unsigned __int64);
/* off 0x0038 */	unsigned long	PStateContext;
/* off 0x003c */	long( __fastcall *TStateHandler)(unsigned long,unsigned __int64,unsigned __int64);
/* off 0x0040 */	unsigned long	TStateContext;
/* off 0x0044 */	unsigned long( __fastcall *FeedbackHandler)(unsigned char);
/* off 0x0048 */	struct _PPM_DIA_STATS*	DiaStats;
/* off 0x004c */	unsigned long	DiaStatsCount;
/* off 0x0050 */	struct _PPM_PERF_STATE State[1];
};
struct _PPM_DIA_STATS /* sizeof 0000000c 12 */
{
/* off 0x0000 */	unsigned long	PerfLevel;
/* off 0x0004 */	unsigned long	IdleTime;
/* off 0x0008 */	unsigned long	TimeInterval;
};
enum _PROCESSOR_CACHE_TYPE
{
	CacheUnified	=0x00000000	,//0
	CacheInstruction	=0x00000001	,//0
	CacheData	=0x00000002	,//0
	CacheTrace	=0x00000003	,//0
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
struct _KPCR /* sizeof 00002128 8488 */
{
union
{
/* off 0x0000 */	struct _NT_TIB	NtTib;
struct
{
/* off 0x0000 */	struct _EXCEPTION_REGISTRATION_RECORD*	Used_ExceptionList;
/* off 0x0004 */	void*	Used_StackBase;
/* off 0x0008 */	void*	Spare2;
/* off 0x000c */	void*	TssCopy;
/* off 0x0010 */	unsigned long	ContextSwitches;
/* off 0x0014 */	unsigned long	SetMemberCopy;
/* off 0x0018 */	void*	Used_Self;
};
};
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
/* off 0x0050 */	unsigned char	SpareUnused;
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
enum _KSPIN_LOCK_QUEUE_NUMBER
{
	LockQueueDispatcherLock	=0x00000000	,//0
	LockQueueExpansionLock	=0x00000001	,//0
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
	LockQueueMmNonPagedPoolLock	=0x0000000f	,//0
	LockQueueUnusedSpare16	=0x00000010	,//0
	LockQueueTimerTableLock	=0x00000011	,//0
	LockQueueMaximumLock	=0x00000031	,//0
};
enum _EVENT_TYPE
{
	NotificationEvent	=0x00000000	,//0
	SynchronizationEvent	=0x00000001	,//0
};
struct _FAST_MUTEX /* sizeof 00000020 32 */
{
/* off 0x0000 */	long	Count;
/* off 0x0004 */	struct _KTHREAD*	Owner;
/* off 0x0008 */	unsigned long	Contention;
/* off 0x000c */	struct _KEVENT	Gate;
/* off 0x001c */	unsigned long	OldIrql;
};
struct _NPAGED_LOOKASIDE_LIST /* sizeof 000000c0 192 */
{
/* off 0x0000 */	struct _GENERAL_LOOKASIDE	L;
/* off 0x0080 */	unsigned long	Lock__ObsoleteButDoNotDelete;
};
struct _PAGED_LOOKASIDE_LIST /* sizeof 000000c0 192 */
{
/* off 0x0000 */	struct _GENERAL_LOOKASIDE	L;
/* off 0x0080 */	struct _FAST_MUTEX	Lock__ObsoleteButDoNotDelete;
};
struct _QUAD /* sizeof 00000008 8 */
{
union
{
/* off 0x0000 */	__int64	UseThisFieldToCopy;
/* off 0x0000 */	double	DoNotUseThisField;
};
};
struct _EX_PUSH_LOCK /* sizeof 00000004 4 */
{
union
{
struct
{
/* off 0x0000 */	unsigned long	Locked:1	 /* start bit 0 */;
/* off 0x0000 */	unsigned long	Waiting:1	 /* start bit 1 */;
/* off 0x0000 */	unsigned long	Waking:1	 /* start bit 2 */;
/* off 0x0000 */	unsigned long	MultipleShared:1	 /* start bit 3 */;
/* off 0x0000 */	unsigned long	Shared:28	 /* start bit 4 */;
};
/* off 0x0000 */	unsigned long	Value;
/* off 0x0000 */	void*	Ptr;
};
};
struct _EX_PUSH_LOCK_CACHE_AWARE /* sizeof 00000080 128 */
{
/* off 0x0000 */	struct _EX_PUSH_LOCK* Locks[32];
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
	LookasideScratchBufferList	=0x00000007	,//0
	LookasideMaximumList	=0x00000008	,//0
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
struct _EX_PUSH_LOCK_WAIT_BLOCK /* sizeof 00000030 48 */
{
union
{
/* off 0x0000 */	struct _KGATE	WakeGate;
/* off 0x0000 */	struct _KEVENT	WakeEvent;
};
/* off 0x0010 */	struct _EX_PUSH_LOCK_WAIT_BLOCK*	Next;
/* off 0x0014 */	struct _EX_PUSH_LOCK_WAIT_BLOCK*	Last;
/* off 0x0018 */	struct _EX_PUSH_LOCK_WAIT_BLOCK*	Previous;
/* off 0x001c */	long	ShareCount;
/* off 0x0020 */	long	Flags;
};
struct _CLIENT_ID /* sizeof 00000008 8 */
{
/* off 0x0000 */	void*	UniqueProcess;
/* off 0x0004 */	void*	UniqueThread;
};
union _PS_CLIENT_SECURITY_CONTEXT /* sizeof 00000004 4 */
{
/* off 0x0000 */	unsigned long	ImpersonationData;
/* off 0x0000 */	void*	ImpersonationToken;
struct
{
/* off 0x0000 */	unsigned long	ImpersonationLevel:2	 /* start bit 0 */;
/* off 0x0000 */	unsigned long	EffectiveOnly:1	 /* start bit 2 */;
};
};
struct _EX_RUNDOWN_REF /* sizeof 00000004 4 */
{
union
{
/* off 0x0000 */	unsigned long	Count;
/* off 0x0000 */	void*	Ptr;
};
};
struct _ETHREAD /* sizeof 00000288 648 */
{
/* off 0x0000 */	struct _KTHREAD	Tcb;
/* off 0x01e0 */	union _LARGE_INTEGER	CreateTime;
union
{
/* off 0x01e8 */	union _LARGE_INTEGER	ExitTime;
/* off 0x01e8 */	struct _LIST_ENTRY	KeyedWaitChain;
};
union
{
/* off 0x01f0 */	long	ExitStatus;
/* off 0x01f0 */	void*	OfsChain;
};
union
{
/* off 0x01f4 */	struct _LIST_ENTRY	PostBlockList;
struct
{
/* off 0x01f4 */	void*	ForwardLinkShadow;
/* off 0x01f8 */	void*	StartAddress;
};
};
union
{
/* off 0x01fc */	struct _TERMINATION_PORT*	TerminationPort;
/* off 0x01fc */	struct _ETHREAD*	ReaperLink;
/* off 0x01fc */	void*	KeyedWaitValue;
/* off 0x01fc */	void*	Win32StartParameter;
};
/* off 0x0200 */	unsigned long	ActiveTimerListLock;
/* off 0x0204 */	struct _LIST_ENTRY	ActiveTimerListHead;
/* off 0x020c */	struct _CLIENT_ID	Cid;
union
{
/* off 0x0214 */	struct _KSEMAPHORE	KeyedWaitSemaphore;
/* off 0x0214 */	struct _KSEMAPHORE	AlpcWaitSemaphore;
};
/* off 0x0228 */	union _PS_CLIENT_SECURITY_CONTEXT	ClientSecurity;
/* off 0x022c */	struct _LIST_ENTRY	IrpList;
/* off 0x0234 */	unsigned long	TopLevelIrp;
/* off 0x0238 */	struct _DEVICE_OBJECT*	DeviceToVerify;
/* off 0x023c */	union _PSP_RATE_APC*	RateControlApc;
/* off 0x0240 */	void*	Win32StartAddress;
/* off 0x0244 */	void*	SparePtr0;
/* off 0x0248 */	struct _LIST_ENTRY	ThreadListEntry;
/* off 0x0250 */	struct _EX_RUNDOWN_REF	RundownProtect;
/* off 0x0254 */	struct _EX_PUSH_LOCK	ThreadLock;
/* off 0x0258 */	unsigned long	ReadClusterSize;
/* off 0x025c */	long	MmLockOrdering;
union
{
/* off 0x0260 */	unsigned long	CrossThreadFlags;
struct
{
/* off 0x0260 */	unsigned long	Terminated:1	 /* start bit 0 */;
/* off 0x0260 */	unsigned long	ThreadInserted:1	 /* start bit 1 */;
/* off 0x0260 */	unsigned long	HideFromDebugger:1	 /* start bit 2 */;
/* off 0x0260 */	unsigned long	ActiveImpersonationInfo:1	 /* start bit 3 */;
/* off 0x0260 */	unsigned long	SystemThread:1	 /* start bit 4 */;
/* off 0x0260 */	unsigned long	HardErrorsAreDisabled:1	 /* start bit 5 */;
/* off 0x0260 */	unsigned long	BreakOnTermination:1	 /* start bit 6 */;
/* off 0x0260 */	unsigned long	SkipCreationMsg:1	 /* start bit 7 */;
/* off 0x0260 */	unsigned long	SkipTerminationMsg:1	 /* start bit 8 */;
/* off 0x0260 */	unsigned long	CopyTokenOnOpen:1	 /* start bit 9 */;
/* off 0x0260 */	unsigned long	ThreadIoPriority:3	 /* start bit 10 */;
/* off 0x0260 */	unsigned long	ThreadPagePriority:3	 /* start bit 13 */;
/* off 0x0260 */	unsigned long	RundownFail:1	 /* start bit 16 */;
};
};
union
{
/* off 0x0264 */	unsigned long	SameThreadPassiveFlags;
struct
{
/* off 0x0264 */	unsigned long	ActiveExWorker:1	 /* start bit 0 */;
/* off 0x0264 */	unsigned long	ExWorkerCanWaitUser:1	 /* start bit 1 */;
/* off 0x0264 */	unsigned long	MemoryMaker:1	 /* start bit 2 */;
/* off 0x0264 */	unsigned long	ClonedThread:1	 /* start bit 3 */;
/* off 0x0264 */	unsigned long	KeyedEventInUse:1	 /* start bit 4 */;
/* off 0x0264 */	unsigned long	RateApcState:2	 /* start bit 5 */;
/* off 0x0264 */	unsigned long	SelfTerminate:1	 /* start bit 7 */;
};
};
union
{
/* off 0x0268 */	unsigned long	SameThreadApcFlags;
struct
{
/* off 0x0268 */	unsigned char	Spare:1	 /* start bit 0 */;
/* off 0x0268 */	unsigned char	StartAddressInvalid:1	 /* start bit 1 */;
/* off 0x0268 */	unsigned char	EtwPageFaultCalloutActive:1	 /* start bit 2 */;
/* off 0x0268 */	unsigned char	OwnsProcessWorkingSetExclusive:1	 /* start bit 3 */;
/* off 0x0268 */	unsigned char	OwnsProcessWorkingSetShared:1	 /* start bit 4 */;
/* off 0x0268 */	unsigned char	OwnsSystemWorkingSetExclusive:1	 /* start bit 5 */;
/* off 0x0268 */	unsigned char	OwnsSystemWorkingSetShared:1	 /* start bit 6 */;
struct
{
/* off 0x0268 */	unsigned char	OwnsSessionWorkingSetExclusive:1	 /* start bit 7 */;
};
/* off 0x0269 */	unsigned char	OwnsSessionWorkingSetShared:1	 /* start bit 0 */;
/* off 0x0269 */	unsigned char	OwnsProcessAddressSpaceExclusive:1	 /* start bit 1 */;
/* off 0x0269 */	unsigned char	OwnsProcessAddressSpaceShared:1	 /* start bit 2 */;
/* off 0x0269 */	unsigned char	SuppressSymbolLoad:1	 /* start bit 3 */;
/* off 0x0269 */	unsigned char	Prefetching:1	 /* start bit 4 */;
/* off 0x0269 */	unsigned char	OwnsDynamicMemoryShared:1	 /* start bit 5 */;
/* off 0x0269 */	unsigned char	OwnsChangeControlAreaExclusive:1	 /* start bit 6 */;
/* off 0x0269 */	unsigned char	OwnsChangeControlAreaShared:1	 /* start bit 7 */;
/* off 0x026a */	unsigned char	Spare1:8	 /* start bit 0 */;
/* off 0x026b */	unsigned char	PriorityRegionActive;
};
};
/* off 0x026c */	unsigned char	CacheManagerActive;
/* off 0x026d */	unsigned char	DisablePageFaultClustering;
/* off 0x026e */	unsigned char	ActiveFaultCount;
/* off 0x0270 */	unsigned long	AlpcMessageId;
union
{
/* off 0x0274 */	void*	AlpcMessage;
/* off 0x0274 */	unsigned long	AlpcReceiveAttributeSet;
};
/* off 0x0278 */	struct _LIST_ENTRY	AlpcWaitListEntry;
/* off 0x0280 */	unsigned long	CacheManagerCount;
};
struct _TERMINATION_PORT /* sizeof 00000008 8 */
{
/* off 0x0000 */	struct _TERMINATION_PORT*	Next;
/* off 0x0004 */	void*	Port;
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
/* off 0x0010 */	enum _IO_ALLOCATION_ACTION( __stdcall *DeviceRoutine)(struct _DEVICE_OBJECT*,struct _IRP*,void*,void*);
/* off 0x0014 */	void*	DeviceContext;
/* off 0x0018 */	unsigned long	NumberOfMapRegisters;
/* off 0x001c */	void*	DeviceObject;
/* off 0x0020 */	void*	CurrentIrp;
/* off 0x0024 */	struct _KDPC*	BufferChainingDpc;
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
/* off 0x0034 */	
	union  /* sizeof 00000028 40 */
	{
	/* off 0x0000 */	struct _LIST_ENTRY	ListEntry;
	/* off 0x0000 */	struct _WAIT_CONTEXT_BLOCK	Wcb;
	}	Queue;
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
/* off 0x002c */	long( __stdcall *DriverInit)(struct _DRIVER_OBJECT*,struct _UNICODE_STRING*);
/* off 0x0030 */	void( __stdcall *DriverStartIo)(struct _DEVICE_OBJECT*,struct _IRP*);
/* off 0x0034 */	void( __stdcall *DriverUnload)(struct _DRIVER_OBJECT*);
/* off 0x0038 */	long( __stdcall * MajorFunction[28])(struct _DEVICE_OBJECT*,struct _IRP*);
};
struct _DRIVER_EXTENSION /* sizeof 0000001c 28 */
{
/* off 0x0000 */	struct _DRIVER_OBJECT*	DriverObject;
/* off 0x0004 */	long( __stdcall *AddDevice)(struct _DRIVER_OBJECT*,struct _DEVICE_OBJECT*);
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
/* off 0x0008 */	long( __stdcall *PreAcquireForSectionSynchronization)(struct _FS_FILTER_CALLBACK_DATA*,void**);
/* off 0x000c */	void( __stdcall *PostAcquireForSectionSynchronization)(struct _FS_FILTER_CALLBACK_DATA*,long,void*);
/* off 0x0010 */	long( __stdcall *PreReleaseForSectionSynchronization)(struct _FS_FILTER_CALLBACK_DATA*,void**);
/* off 0x0014 */	void( __stdcall *PostReleaseForSectionSynchronization)(struct _FS_FILTER_CALLBACK_DATA*,long,void*);
/* off 0x0018 */	long( __stdcall *PreAcquireForCcFlush)(struct _FS_FILTER_CALLBACK_DATA*,void**);
/* off 0x001c */	void( __stdcall *PostAcquireForCcFlush)(struct _FS_FILTER_CALLBACK_DATA*,long,void*);
/* off 0x0020 */	long( __stdcall *PreReleaseForCcFlush)(struct _FS_FILTER_CALLBACK_DATA*,void**);
/* off 0x0024 */	void( __stdcall *PostReleaseForCcFlush)(struct _FS_FILTER_CALLBACK_DATA*,long,void*);
/* off 0x0028 */	long( __stdcall *PreAcquireForModifiedPageWriter)(struct _FS_FILTER_CALLBACK_DATA*,void**);
/* off 0x002c */	void( __stdcall *PostAcquireForModifiedPageWriter)(struct _FS_FILTER_CALLBACK_DATA*,long,void*);
/* off 0x0030 */	long( __stdcall *PreReleaseForModifiedPageWriter)(struct _FS_FILTER_CALLBACK_DATA*,void**);
/* off 0x0034 */	void( __stdcall *PostReleaseForModifiedPageWriter)(struct _FS_FILTER_CALLBACK_DATA*,long,void*);
};
union _FS_FILTER_PARAMETERS /* sizeof 00000014 20 */
{
/* off 0x0000 */	
	struct  /* sizeof 00000008 8 */
	{
	/* off 0x0000 */	union _LARGE_INTEGER*	EndingOffset;
	/* off 0x0004 */	struct _ERESOURCE**	ResourceToRelease;
	}	AcquireForModifiedPageWriter;
/* off 0x0000 */	
	struct  /* sizeof 00000004 4 */
	{
	/* off 0x0000 */	struct _ERESOURCE*	ResourceToRelease;
	}	ReleaseForModifiedPageWriter;
/* off 0x0000 */	
	struct  /* sizeof 00000008 8 */
	{
	/* off 0x0000 */	enum _FS_FILTER_SECTION_SYNC_TYPE	SyncType;
	/* off 0x0004 */	unsigned long	PageProtection;
	}	AcquireForSectionSynchronization;
/* off 0x0000 */	
	struct  /* sizeof 00000008 8 */
	{
	/* off 0x0000 */	enum _FS_FILTER_STREAM_FO_NOTIFICATION_TYPE	NotificationType;
	/* off 0x0004 */	unsigned char	SafeToRecurse;
	}	NotifyStreamFileObject;
/* off 0x0000 */	
	struct  /* sizeof 00000014 20 */
	{
	/* off 0x0000 */	void*	Argument1;
	/* off 0x0004 */	void*	Argument2;
	/* off 0x0008 */	void*	Argument3;
	/* off 0x000c */	void*	Argument4;
	/* off 0x0010 */	void*	Argument5;
	}	Others;
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
struct _FILE_OBJECT /* sizeof 00000080 128 */
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
/* off 0x0070 */	unsigned long	IrpListLock;
/* off 0x0074 */	struct _LIST_ENTRY	IrpList;
/* off 0x007c */	void*	FileObjectExtension;
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
/* off 0x0018 */	wchar VolumeLabel[32];
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
/* off 0x0018 */	struct _OWNER_ENTRY	OwnerEntry;
/* off 0x0020 */	unsigned long	ActiveEntries;
/* off 0x0024 */	unsigned long	ContentionCount;
/* off 0x0028 */	unsigned long	NumberOfSharedWaiters;
/* off 0x002c */	unsigned long	NumberOfExclusiveWaiters;
union
{
/* off 0x0030 */	void*	Address;
/* off 0x0030 */	unsigned long	CreatorBackTraceIndex;
};
/* off 0x0034 */	unsigned long	SpinLock;
};
enum _FS_FILTER_SECTION_SYNC_TYPE
{
	SyncTypeOther	=0x00000000	,//0
	SyncTypeCreateSection	=0x00000001	,//0
};
enum _FS_FILTER_STREAM_FO_NOTIFICATION_TYPE
{
	NotifyTypeCreate	=0x00000000	,//0
	NotifyTypeRetired	=0x00000001	,//0
};
struct _FAST_IO_DISPATCH /* sizeof 00000070 112 */
{
/* off 0x0000 */	unsigned long	SizeOfFastIoDispatch;
/* off 0x0004 */	unsigned char( __stdcall *FastIoCheckIfPossible)(struct _FILE_OBJECT*,union _LARGE_INTEGER*,unsigned long,unsigned char,unsigned long,unsigned char,struct _IO_STATUS_BLOCK*,struct _DEVICE_OBJECT*);
/* off 0x0008 */	unsigned char( __stdcall *FastIoRead)(struct _FILE_OBJECT*,union _LARGE_INTEGER*,unsigned long,unsigned char,unsigned long,void*,struct _IO_STATUS_BLOCK*,struct _DEVICE_OBJECT*);
/* off 0x000c */	unsigned char( __stdcall *FastIoWrite)(struct _FILE_OBJECT*,union _LARGE_INTEGER*,unsigned long,unsigned char,unsigned long,void*,struct _IO_STATUS_BLOCK*,struct _DEVICE_OBJECT*);
/* off 0x0010 */	unsigned char( __stdcall *FastIoQueryBasicInfo)(struct _FILE_OBJECT*,unsigned char,struct _FILE_BASIC_INFORMATION*,struct _IO_STATUS_BLOCK*,struct _DEVICE_OBJECT*);
/* off 0x0014 */	unsigned char( __stdcall *FastIoQueryStandardInfo)(struct _FILE_OBJECT*,unsigned char,struct _FILE_STANDARD_INFORMATION*,struct _IO_STATUS_BLOCK*,struct _DEVICE_OBJECT*);
/* off 0x0018 */	unsigned char( __stdcall *FastIoLock)(struct _FILE_OBJECT*,union _LARGE_INTEGER*,union _LARGE_INTEGER*,struct _EPROCESS*,unsigned long,unsigned char,unsigned char,struct _IO_STATUS_BLOCK*,struct _DEVICE_OBJECT*);
/* off 0x001c */	unsigned char( __stdcall *FastIoUnlockSingle)(struct _FILE_OBJECT*,union _LARGE_INTEGER*,union _LARGE_INTEGER*,struct _EPROCESS*,unsigned long,struct _IO_STATUS_BLOCK*,struct _DEVICE_OBJECT*);
/* off 0x0020 */	unsigned char( __stdcall *FastIoUnlockAll)(struct _FILE_OBJECT*,struct _EPROCESS*,struct _IO_STATUS_BLOCK*,struct _DEVICE_OBJECT*);
/* off 0x0024 */	unsigned char( __stdcall *FastIoUnlockAllByKey)(struct _FILE_OBJECT*,void*,unsigned long,struct _IO_STATUS_BLOCK*,struct _DEVICE_OBJECT*);
/* off 0x0028 */	unsigned char( __stdcall *FastIoDeviceControl)(struct _FILE_OBJECT*,unsigned char,void*,unsigned long,void*,unsigned long,unsigned long,struct _IO_STATUS_BLOCK*,struct _DEVICE_OBJECT*);
/* off 0x002c */	void( __stdcall *AcquireFileForNtCreateSection)(struct _FILE_OBJECT*);
/* off 0x0030 */	void( __stdcall *ReleaseFileForNtCreateSection)(struct _FILE_OBJECT*);
/* off 0x0034 */	void( __stdcall *FastIoDetachDevice)(struct _DEVICE_OBJECT*,struct _DEVICE_OBJECT*);
/* off 0x0038 */	unsigned char( __stdcall *FastIoQueryNetworkOpenInfo)(struct _FILE_OBJECT*,unsigned char,struct _FILE_NETWORK_OPEN_INFORMATION*,struct _IO_STATUS_BLOCK*,struct _DEVICE_OBJECT*);
/* off 0x003c */	long( __stdcall *AcquireForModWrite)(struct _FILE_OBJECT*,union _LARGE_INTEGER*,struct _ERESOURCE**,struct _DEVICE_OBJECT*);
/* off 0x0040 */	unsigned char( __stdcall *MdlRead)(struct _FILE_OBJECT*,union _LARGE_INTEGER*,unsigned long,unsigned long,struct _MDL**,struct _IO_STATUS_BLOCK*,struct _DEVICE_OBJECT*);
/* off 0x0044 */	unsigned char( __stdcall *MdlReadComplete)(struct _FILE_OBJECT*,struct _MDL*,struct _DEVICE_OBJECT*);
/* off 0x0048 */	unsigned char( __stdcall *PrepareMdlWrite)(struct _FILE_OBJECT*,union _LARGE_INTEGER*,unsigned long,unsigned long,struct _MDL**,struct _IO_STATUS_BLOCK*,struct _DEVICE_OBJECT*);
/* off 0x004c */	unsigned char( __stdcall *MdlWriteComplete)(struct _FILE_OBJECT*,union _LARGE_INTEGER*,struct _MDL*,struct _DEVICE_OBJECT*);
/* off 0x0050 */	unsigned char( __stdcall *FastIoReadCompressed)(struct _FILE_OBJECT*,union _LARGE_INTEGER*,unsigned long,unsigned long,void*,struct _MDL**,struct _IO_STATUS_BLOCK*,struct _COMPRESSED_DATA_INFO*,unsigned long,struct _DEVICE_OBJECT*);
/* off 0x0054 */	unsigned char( __stdcall *FastIoWriteCompressed)(struct _FILE_OBJECT*,union _LARGE_INTEGER*,unsigned long,unsigned long,void*,struct _MDL**,struct _IO_STATUS_BLOCK*,struct _COMPRESSED_DATA_INFO*,unsigned long,struct _DEVICE_OBJECT*);
/* off 0x0058 */	unsigned char( __stdcall *MdlReadCompleteCompressed)(struct _FILE_OBJECT*,struct _MDL*,struct _DEVICE_OBJECT*);
/* off 0x005c */	unsigned char( __stdcall *MdlWriteCompleteCompressed)(struct _FILE_OBJECT*,union _LARGE_INTEGER*,struct _MDL*,struct _DEVICE_OBJECT*);
/* off 0x0060 */	unsigned char( __stdcall *FastIoQueryOpen)(struct _IRP*,struct _FILE_NETWORK_OPEN_INFORMATION*,struct _DEVICE_OBJECT*);
/* off 0x0064 */	long( __stdcall *ReleaseForModWrite)(struct _FILE_OBJECT*,struct _ERESOURCE*,struct _DEVICE_OBJECT*);
/* off 0x0068 */	long( __stdcall *AcquireForCcFlush)(struct _FILE_OBJECT*,struct _DEVICE_OBJECT*);
/* off 0x006c */	long( __stdcall *ReleaseForCcFlush)(struct _FILE_OBJECT*,struct _DEVICE_OBJECT*);
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
/* off 0x0000 */	unsigned char	SessionSpace:1	 /* start bit 0 */;
/* off 0x0000 */	unsigned char	ModwriterAttached:1	 /* start bit 1 */;
/* off 0x0000 */	unsigned char	TrimHard:1	 /* start bit 2 */;
/* off 0x0000 */	unsigned char	MaximumWorkingSetHard:1	 /* start bit 3 */;
/* off 0x0000 */	unsigned char	ForceTrim:1	 /* start bit 4 */;
/* off 0x0000 */	unsigned char	MinimumWorkingSetHard:1	 /* start bit 5 */;
/* off 0x0000 */	unsigned char	SessionMaster:1	 /* start bit 6 */;
/* off 0x0000 */	unsigned char	TrimmerAttached:1	 /* start bit 7 */;
/* off 0x0001 */	unsigned char	TrimmerDetaching:1	 /* start bit 0 */;
/* off 0x0001 */	unsigned char	Reserved:3	 /* start bit 1 */;
/* off 0x0001 */	unsigned char	PageStealers:4	 /* start bit 4 */;
/* off 0x0002 */	unsigned char	MemoryPriority:8	 /* start bit 0 */;
/* off 0x0003 */	unsigned char	WsleDeleted:1	 /* start bit 0 */;
/* off 0x0003 */	unsigned char	VmExiting:1	 /* start bit 1 */;
/* off 0x0003 */	unsigned char	ExpansionFailed:1	 /* start bit 2 */;
/* off 0x0003 */	unsigned char	Available:5	 /* start bit 3 */;
};
struct _MMSUPPORT /* sizeof 00000048 72 */
{
/* off 0x0000 */	struct _LIST_ENTRY	WorkingSetExpansionLinks;
/* off 0x0008 */	unsigned short	LastTrimStamp;
/* off 0x000a */	unsigned short	NextPageColor;
/* off 0x000c */	struct _MMSUPPORT_FLAGS	Flags;
/* off 0x0010 */	unsigned long	PageFaultCount;
/* off 0x0014 */	unsigned long	PeakWorkingSetSize;
/* off 0x0018 */	unsigned long	ChargedWslePages;
/* off 0x001c */	unsigned long	MinimumWorkingSetSize;
/* off 0x0020 */	unsigned long	MaximumWorkingSetSize;
/* off 0x0024 */	struct _MMWSL*	VmWorkingSetList;
/* off 0x0028 */	unsigned long	Claim;
/* off 0x002c */	unsigned long	ActualWslePages;
/* off 0x0030 */	unsigned long	WorkingSetPrivateSize;
/* off 0x0034 */	unsigned long	WorkingSetSizeOverhead;
/* off 0x0038 */	unsigned long	WorkingSetSize;
/* off 0x003c */	struct _KGATE*	ExitGate;
/* off 0x0040 */	struct _EX_PUSH_LOCK	WorkingSetMutex;
/* off 0x0044 */	void*	AccessLog;
};
struct _MMADDRESS_NODE /* sizeof 00000014 20 */
{
/* off 0x0000 */	
	union  /* sizeof 00000004 4 */
	{
	/* off 0x0000 */	long	Balance:2	 /* start bit 0 */;
	/* off 0x0000 */	struct _MMADDRESS_NODE*	Parent;
	}	u1;
/* off 0x0004 */	struct _MMADDRESS_NODE*	LeftChild;
/* off 0x0008 */	struct _MMADDRESS_NODE*	RightChild;
/* off 0x000c */	unsigned long	StartingVpn;
/* off 0x0010 */	unsigned long	EndingVpn;
};
struct _MM_AVL_TABLE /* sizeof 00000020 32 */
{
/* off 0x0000 */	struct _MMADDRESS_NODE	BalancedRoot;
/* off 0x0014 */	unsigned long	DepthOfTree:5	 /* start bit 0 */;
/* off 0x0014 */	unsigned long	Unused:3	 /* start bit 5 */;
/* off 0x0014 */	unsigned long	NumberGenericTableElements:24	 /* start bit 8 */;
/* off 0x0018 */	void*	NodeHint;
/* off 0x001c */	void*	NodeFreeHint;
};
struct _ALPC_PROCESS_CONTEXT /* sizeof 00000010 16 */
{
/* off 0x0000 */	struct _EX_PUSH_LOCK	Lock;
/* off 0x0004 */	struct _LIST_ENTRY	ViewListHead;
/* off 0x000c */	unsigned long	PagedPoolQuotaCache;
};
struct _EPROCESS /* sizeof 00000270 624 */
{
/* off 0x0000 */	struct _KPROCESS	Pcb;
/* off 0x0080 */	struct _EX_PUSH_LOCK	ProcessLock;
/* off 0x0088 */	union _LARGE_INTEGER	CreateTime;
/* off 0x0090 */	union _LARGE_INTEGER	ExitTime;
/* off 0x0098 */	struct _EX_RUNDOWN_REF	RundownProtect;
/* off 0x009c */	void*	UniqueProcessId;
/* off 0x00a0 */	struct _LIST_ENTRY	ActiveProcessLinks;
/* off 0x00a8 */	unsigned long QuotaUsage[3];
/* off 0x00b4 */	unsigned long QuotaPeak[3];
/* off 0x00c0 */	unsigned long	CommitCharge;
/* off 0x00c4 */	unsigned long	PeakVirtualSize;
/* off 0x00c8 */	unsigned long	VirtualSize;
/* off 0x00cc */	struct _LIST_ENTRY	SessionProcessLinks;
/* off 0x00d4 */	void*	DebugPort;
union
{
/* off 0x00d8 */	void*	ExceptionPortData;
/* off 0x00d8 */	unsigned long	ExceptionPortValue;
/* off 0x00d8 */	unsigned long	ExceptionPortState:3	 /* start bit 0 */;
};
/* off 0x00dc */	struct _HANDLE_TABLE*	ObjectTable;
/* off 0x00e0 */	struct _EX_FAST_REF	Token;
/* off 0x00e4 */	unsigned long	WorkingSetPage;
/* off 0x00e8 */	struct _EX_PUSH_LOCK	AddressCreationLock;
/* off 0x00ec */	struct _ETHREAD*	RotateInProgress;
/* off 0x00f0 */	struct _ETHREAD*	ForkInProgress;
/* off 0x00f4 */	unsigned long	HardwareTrigger;
/* off 0x00f8 */	struct _MM_AVL_TABLE*	PhysicalVadRoot;
/* off 0x00fc */	void*	CloneRoot;
/* off 0x0100 */	unsigned long	NumberOfPrivatePages;
/* off 0x0104 */	unsigned long	NumberOfLockedPages;
/* off 0x0108 */	void*	Win32Process;
/* off 0x010c */	struct _EJOB*	Job;
/* off 0x0110 */	void*	SectionObject;
/* off 0x0114 */	void*	SectionBaseAddress;
/* off 0x0118 */	struct _EPROCESS_QUOTA_BLOCK*	QuotaBlock;
/* off 0x011c */	struct _PAGEFAULT_HISTORY*	WorkingSetWatch;
/* off 0x0120 */	void*	Win32WindowStation;
/* off 0x0124 */	void*	InheritedFromUniqueProcessId;
/* off 0x0128 */	void*	LdtInformation;
/* off 0x012c */	void*	Spare;
/* off 0x0130 */	void*	VdmObjects;
/* off 0x0134 */	void*	DeviceMap;
/* off 0x0138 */	void*	EtwDataSource;
/* off 0x013c */	void*	FreeTebHint;
union
{
/* off 0x0140 */	struct _HARDWARE_PTE	PageDirectoryPte;
/* off 0x0140 */	unsigned __int64	Filler;
};
/* off 0x0148 */	void*	Session;
/* off 0x014c */	unsigned char ImageFileName[16];
/* off 0x015c */	struct _LIST_ENTRY	JobLinks;
/* off 0x0164 */	void*	LockedPagesList;
/* off 0x0168 */	struct _LIST_ENTRY	ThreadListHead;
/* off 0x0170 */	void*	SecurityPort;
/* off 0x0174 */	void*	PaeTop;
/* off 0x0178 */	unsigned long	ActiveThreads;
/* off 0x017c */	unsigned long	ImagePathHash;
/* off 0x0180 */	unsigned long	DefaultHardErrorProcessing;
/* off 0x0184 */	long	LastThreadExitStatus;
/* off 0x0188 */	struct _PEB*	Peb;
/* off 0x018c */	struct _EX_FAST_REF	PrefetchTrace;
/* off 0x0190 */	union _LARGE_INTEGER	ReadOperationCount;
/* off 0x0198 */	union _LARGE_INTEGER	WriteOperationCount;
/* off 0x01a0 */	union _LARGE_INTEGER	OtherOperationCount;
/* off 0x01a8 */	union _LARGE_INTEGER	ReadTransferCount;
/* off 0x01b0 */	union _LARGE_INTEGER	WriteTransferCount;
/* off 0x01b8 */	union _LARGE_INTEGER	OtherTransferCount;
/* off 0x01c0 */	unsigned long	CommitChargeLimit;
/* off 0x01c4 */	unsigned long	CommitChargePeak;
/* off 0x01c8 */	void*	AweInfo;
/* off 0x01cc */	struct _SE_AUDIT_PROCESS_CREATION_INFO	SeAuditProcessCreationInfo;
/* off 0x01d0 */	struct _MMSUPPORT	Vm;
/* off 0x0218 */	struct _LIST_ENTRY	MmProcessLinks;
/* off 0x0220 */	unsigned long	ModifiedPageCount;
union
{
/* off 0x0224 */	unsigned long	Flags2;
struct
{
/* off 0x0224 */	unsigned long	JobNotReallyActive:1	 /* start bit 0 */;
/* off 0x0224 */	unsigned long	AccountingFolded:1	 /* start bit 1 */;
/* off 0x0224 */	unsigned long	NewProcessReported:1	 /* start bit 2 */;
/* off 0x0224 */	unsigned long	ExitProcessReported:1	 /* start bit 3 */;
/* off 0x0224 */	unsigned long	ReportCommitChanges:1	 /* start bit 4 */;
/* off 0x0224 */	unsigned long	LastReportMemory:1	 /* start bit 5 */;
/* off 0x0224 */	unsigned long	ReportPhysicalPageChanges:1	 /* start bit 6 */;
/* off 0x0224 */	unsigned long	HandleTableRundown:1	 /* start bit 7 */;
/* off 0x0224 */	unsigned long	NeedsHandleRundown:1	 /* start bit 8 */;
/* off 0x0224 */	unsigned long	RefTraceEnabled:1	 /* start bit 9 */;
/* off 0x0224 */	unsigned long	NumaAware:1	 /* start bit 10 */;
/* off 0x0224 */	unsigned long	ProtectedProcess:1	 /* start bit 11 */;
/* off 0x0224 */	unsigned long	DefaultPagePriority:3	 /* start bit 12 */;
/* off 0x0224 */	unsigned long	PrimaryTokenFrozen:1	 /* start bit 15 */;
/* off 0x0224 */	unsigned long	ProcessVerifierTarget:1	 /* start bit 16 */;
/* off 0x0224 */	unsigned long	StackRandomizationDisabled:1	 /* start bit 17 */;
/* off 0x0224 */	unsigned long	AffinityPermanent:1	 /* start bit 18 */;
/* off 0x0224 */	unsigned long	AffinityUpdateEnable:1	 /* start bit 19 */;
/* off 0x0224 */	unsigned long	CrossSessionCreate:1	 /* start bit 20 */;
};
};
union
{
/* off 0x0228 */	unsigned long	Flags;
struct
{
/* off 0x0228 */	unsigned long	CreateReported:1	 /* start bit 0 */;
/* off 0x0228 */	unsigned long	NoDebugInherit:1	 /* start bit 1 */;
/* off 0x0228 */	unsigned long	ProcessExiting:1	 /* start bit 2 */;
/* off 0x0228 */	unsigned long	ProcessDelete:1	 /* start bit 3 */;
/* off 0x0228 */	unsigned long	Wow64SplitPages:1	 /* start bit 4 */;
/* off 0x0228 */	unsigned long	VmDeleted:1	 /* start bit 5 */;
/* off 0x0228 */	unsigned long	OutswapEnabled:1	 /* start bit 6 */;
/* off 0x0228 */	unsigned long	Outswapped:1	 /* start bit 7 */;
/* off 0x0228 */	unsigned long	ForkFailed:1	 /* start bit 8 */;
/* off 0x0228 */	unsigned long	Wow64VaSpace4Gb:1	 /* start bit 9 */;
/* off 0x0228 */	unsigned long	AddressSpaceInitialized:2	 /* start bit 10 */;
/* off 0x0228 */	unsigned long	SetTimerResolution:1	 /* start bit 12 */;
/* off 0x0228 */	unsigned long	BreakOnTermination:1	 /* start bit 13 */;
/* off 0x0228 */	unsigned long	DeprioritizeViews:1	 /* start bit 14 */;
/* off 0x0228 */	unsigned long	WriteWatch:1	 /* start bit 15 */;
/* off 0x0228 */	unsigned long	ProcessInSession:1	 /* start bit 16 */;
/* off 0x0228 */	unsigned long	OverrideAddressSpace:1	 /* start bit 17 */;
/* off 0x0228 */	unsigned long	HasAddressSpace:1	 /* start bit 18 */;
/* off 0x0228 */	unsigned long	LaunchPrefetched:1	 /* start bit 19 */;
/* off 0x0228 */	unsigned long	InjectInpageErrors:1	 /* start bit 20 */;
/* off 0x0228 */	unsigned long	VmTopDown:1	 /* start bit 21 */;
/* off 0x0228 */	unsigned long	ImageNotifyDone:1	 /* start bit 22 */;
/* off 0x0228 */	unsigned long	PdeUpdateNeeded:1	 /* start bit 23 */;
/* off 0x0228 */	unsigned long	VdmAllowed:1	 /* start bit 24 */;
/* off 0x0228 */	unsigned long	SmapAllowed:1	 /* start bit 25 */;
/* off 0x0228 */	unsigned long	ProcessInserted:1	 /* start bit 26 */;
/* off 0x0228 */	unsigned long	DefaultIoPriority:3	 /* start bit 27 */;
/* off 0x0228 */	unsigned long	ProcessSelfDelete:1	 /* start bit 30 */;
/* off 0x0228 */	unsigned long	SpareProcessFlags:1	 /* start bit 31 */;
};
};
/* off 0x022c */	long	ExitStatus;
/* off 0x0230 */	unsigned short	Spare7;
union
{
struct
{
/* off 0x0232 */	unsigned char	SubSystemMinorVersion;
/* off 0x0233 */	unsigned char	SubSystemMajorVersion;
};
struct
{
/* off 0x0232 */	unsigned short	SubSystemVersion;
};
};
/* off 0x0234 */	unsigned char	PriorityClass;
/* off 0x0238 */	struct _MM_AVL_TABLE	VadRoot;
/* off 0x0258 */	unsigned long	Cookie;
/* off 0x025c */	struct _ALPC_PROCESS_CONTEXT	AlpcContext;
};
struct _HANDLE_TABLE /* sizeof 00000038 56 */
{
/* off 0x0000 */	unsigned long	TableCode;
/* off 0x0004 */	struct _EPROCESS*	QuotaProcess;
/* off 0x0008 */	void*	UniqueProcessId;
/* off 0x000c */	struct _EX_PUSH_LOCK	HandleLock;
/* off 0x0010 */	struct _LIST_ENTRY	HandleTableList;
/* off 0x0018 */	struct _EX_PUSH_LOCK	HandleContentionEvent;
/* off 0x001c */	struct _HANDLE_TRACE_DEBUG_INFO*	DebugInfo;
/* off 0x0020 */	long	ExtraInfoPages;
union
{
/* off 0x0024 */	unsigned long	Flags;
/* off 0x0024 */	unsigned char	StrictFIFO:1	 /* start bit 0 */;
};
/* off 0x0028 */	long	FirstFreeHandle;
/* off 0x002c */	struct _HANDLE_TABLE_ENTRY*	LastFreeHandleEntry;
/* off 0x0030 */	long	HandleCount;
/* off 0x0034 */	unsigned long	NextHandleNeedingPool;
};
struct _HANDLE_TRACE_DB_ENTRY /* sizeof 00000050 80 */
{
/* off 0x0000 */	struct _CLIENT_ID	ClientId;
/* off 0x0008 */	void*	Handle;
/* off 0x000c */	unsigned long	Type;
/* off 0x0010 */	void* StackTrace[16];
};
struct _HANDLE_TRACE_DEBUG_INFO /* sizeof 00000080 128 */
{
/* off 0x0000 */	long	RefCount;
/* off 0x0004 */	unsigned long	TableSize;
/* off 0x0008 */	unsigned long	BitMaskFlags;
/* off 0x000c */	struct _FAST_MUTEX	CloseCompactionLock;
/* off 0x002c */	unsigned long	CurrentStackIndex;
/* off 0x0030 */	struct _HANDLE_TRACE_DB_ENTRY TraceDb[1];
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
struct _EJOB /* sizeof 00000128 296 */
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
/* off 0x00b0 */	struct _JOB_ACCESS_STATE*	AccessState;
/* off 0x00b4 */	unsigned long	UIRestrictionsClass;
/* off 0x00b8 */	unsigned long	EndOfJobTimeAction;
/* off 0x00bc */	void*	CompletionPort;
/* off 0x00c0 */	void*	CompletionKey;
/* off 0x00c4 */	unsigned long	SessionId;
/* off 0x00c8 */	unsigned long	SchedulingClass;
/* off 0x00d0 */	unsigned __int64	ReadOperationCount;
/* off 0x00d8 */	unsigned __int64	WriteOperationCount;
/* off 0x00e0 */	unsigned __int64	OtherOperationCount;
/* off 0x00e8 */	unsigned __int64	ReadTransferCount;
/* off 0x00f0 */	unsigned __int64	WriteTransferCount;
/* off 0x00f8 */	unsigned __int64	OtherTransferCount;
/* off 0x0100 */	unsigned long	ProcessMemoryLimit;
/* off 0x0104 */	unsigned long	JobMemoryLimit;
/* off 0x0108 */	unsigned long	PeakProcessMemoryUsed;
/* off 0x010c */	unsigned long	PeakJobMemoryUsed;
/* off 0x0110 */	unsigned long	CurrentJobMemoryUsed;
/* off 0x0114 */	struct _EX_PUSH_LOCK	MemoryLimitsLock;
/* off 0x0118 */	struct _LIST_ENTRY	JobSetLinks;
/* off 0x0120 */	unsigned long	MemberLevel;
/* off 0x0124 */	unsigned long	JobFlags;
};
struct _JOB_ACCESS_STATE /* sizeof 00000000 0 */
{
};
struct _EPROCESS_QUOTA_BLOCK /* sizeof 00000000 0 */
{
};
struct _PAGEFAULT_HISTORY /* sizeof 00000000 0 */
{
};
struct _PEB /* sizeof 00000238 568 */
{
/* off 0x0000 */	unsigned char	InheritedAddressSpace;
/* off 0x0001 */	unsigned char	ReadImageFileExecOptions;
/* off 0x0002 */	unsigned char	BeingDebugged;
union
{
/* off 0x0003 */	unsigned char	BitField;
struct
{
/* off 0x0003 */	unsigned char	ImageUsesLargePages:1	 /* start bit 0 */;
/* off 0x0003 */	unsigned char	IsProtectedProcess:1	 /* start bit 1 */;
/* off 0x0003 */	unsigned char	IsLegacyProcess:1	 /* start bit 2 */;
/* off 0x0003 */	unsigned char	IsImageDynamicallyRelocated:1	 /* start bit 3 */;
/* off 0x0003 */	unsigned char	SkipPatchingUser32Forwarders:1	 /* start bit 4 */;
/* off 0x0003 */	unsigned char	SpareBits:3	 /* start bit 5 */;
};
};
/* off 0x0004 */	void*	Mutant;
/* off 0x0008 */	void*	ImageBaseAddress;
/* off 0x000c */	struct _PEB_LDR_DATA*	Ldr;
/* off 0x0010 */	struct _RTL_USER_PROCESS_PARAMETERS*	ProcessParameters;
/* off 0x0014 */	void*	SubSystemData;
/* off 0x0018 */	void*	ProcessHeap;
/* off 0x001c */	struct _RTL_CRITICAL_SECTION*	FastPebLock;
/* off 0x0020 */	void*	AtlThunkSListPtr;
/* off 0x0024 */	void*	IFEOKey;
union
{
/* off 0x0028 */	unsigned long	CrossProcessFlags;
struct
{
/* off 0x0028 */	unsigned long	ProcessInJob:1	 /* start bit 0 */;
/* off 0x0028 */	unsigned long	ProcessInitializing:1	 /* start bit 1 */;
/* off 0x0028 */	unsigned long	ProcessUsingVEH:1	 /* start bit 2 */;
/* off 0x0028 */	unsigned long	ProcessUsingVCH:1	 /* start bit 3 */;
/* off 0x0028 */	unsigned long	ReservedBits0:28	 /* start bit 4 */;
};
};
union
{
/* off 0x002c */	void*	KernelCallbackTable;
/* off 0x002c */	void*	UserSharedInfoPtr;
};
/* off 0x0030 */	unsigned long SystemReserved[1];
/* off 0x0034 */	unsigned long	SpareUlong;
/* off 0x0038 */	unsigned long	SparePebPtr0;
/* off 0x003c */	unsigned long	TlsExpansionCounter;
/* off 0x0040 */	void*	TlsBitmap;
/* off 0x0044 */	unsigned long TlsBitmapBits[2];
/* off 0x004c */	void*	ReadOnlySharedMemoryBase;
/* off 0x0050 */	void*	HotpatchInformation;
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
/* off 0x00a0 */	struct _RTL_CRITICAL_SECTION*	LoaderLock;
/* off 0x00a4 */	unsigned long	OSMajorVersion;
/* off 0x00a8 */	unsigned long	OSMinorVersion;
/* off 0x00ac */	unsigned short	OSBuildNumber;
/* off 0x00ae */	unsigned short	OSCSDVersion;
/* off 0x00b0 */	unsigned long	OSPlatformId;
/* off 0x00b4 */	unsigned long	ImageSubsystem;
/* off 0x00b8 */	unsigned long	ImageSubsystemMajorVersion;
/* off 0x00bc */	unsigned long	ImageSubsystemMinorVersion;
/* off 0x00c0 */	unsigned long	ActiveProcessAffinityMask;
/* off 0x00c4 */	unsigned long GdiHandleBuffer[34];
/* off 0x014c */	void( __stdcall *PostProcessInitRoutine)();
/* off 0x0150 */	void*	TlsExpansionBitmap;
/* off 0x0154 */	unsigned long TlsExpansionBitmapBits[32];
/* off 0x01d4 */	unsigned long	SessionId;
/* off 0x01d8 */	union _ULARGE_INTEGER	AppCompatFlags;
/* off 0x01e0 */	union _ULARGE_INTEGER	AppCompatFlagsUser;
/* off 0x01e8 */	void*	pShimData;
/* off 0x01ec */	void*	AppCompatInfo;
/* off 0x01f0 */	struct _UNICODE_STRING	CSDVersion;
/* off 0x01f8 */	struct _ACTIVATION_CONTEXT_DATA*	ActivationContextData;
/* off 0x01fc */	struct _ASSEMBLY_STORAGE_MAP*	ProcessAssemblyStorageMap;
/* off 0x0200 */	struct _ACTIVATION_CONTEXT_DATA*	SystemDefaultActivationContextData;
/* off 0x0204 */	struct _ASSEMBLY_STORAGE_MAP*	SystemAssemblyStorageMap;
/* off 0x0208 */	unsigned long	MinimumStackCommit;
/* off 0x020c */	struct _FLS_CALLBACK_INFO*	FlsCallback;
/* off 0x0210 */	struct _LIST_ENTRY	FlsListHead;
/* off 0x0218 */	void*	FlsBitmap;
/* off 0x021c */	unsigned long FlsBitmapBits[4];
/* off 0x022c */	unsigned long	FlsHighIndex;
/* off 0x0230 */	void*	WerRegistrationData;
/* off 0x0234 */	void*	WerShipAssertPtr;
};
struct _PEB_LDR_DATA /* sizeof 00000030 48 */
{
/* off 0x0000 */	unsigned long	Length;
/* off 0x0004 */	unsigned char	Initialized;
/* off 0x0008 */	void*	SsHandle;
/* off 0x000c */	struct _LIST_ENTRY	InLoadOrderModuleList;
/* off 0x0014 */	struct _LIST_ENTRY	InMemoryOrderModuleList;
/* off 0x001c */	struct _LIST_ENTRY	InInitializationOrderModuleList;
/* off 0x0024 */	void*	EntryInProgress;
/* off 0x0028 */	unsigned char	ShutdownInProgress;
/* off 0x002c */	void*	ShutdownThreadId;
};
struct _CURDIR /* sizeof 0000000c 12 */
{
/* off 0x0000 */	struct _UNICODE_STRING	DosPath;
/* off 0x0008 */	void*	Handle;
};
struct _RTL_DRIVE_LETTER_CURDIR /* sizeof 00000010 16 */
{
/* off 0x0000 */	unsigned short	Flags;
/* off 0x0002 */	unsigned short	Length;
/* off 0x0004 */	unsigned long	TimeStamp;
/* off 0x0008 */	struct _STRING	DosPath;
};
struct _RTL_USER_PROCESS_PARAMETERS /* sizeof 00000294 660 */
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
/* off 0x0290 */	unsigned long	EnvironmentSize;
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
/* off 0x0018 */	unsigned long	Flags;
/* off 0x001c */	unsigned short	CreatorBackTraceIndexHigh;
/* off 0x001e */	unsigned short	SpareUSHORT;
};
struct _ACTIVATION_CONTEXT_DATA /* sizeof 00000000 0 */
{
};
struct _ASSEMBLY_STORAGE_MAP /* sizeof 00000000 0 */
{
};
struct _FLS_CALLBACK_INFO /* sizeof 00000000 0 */
{
};
struct _OBJECT_NAME_INFORMATION /* sizeof 00000008 8 */
{
/* off 0x0000 */	struct _UNICODE_STRING	Name;
};
struct _MMWSL /* sizeof 000006b8 1720 */
{
/* off 0x0000 */	unsigned long	FirstFree;
/* off 0x0004 */	unsigned long	FirstDynamic;
/* off 0x0008 */	unsigned long	LastEntry;
/* off 0x000c */	unsigned long	NextSlot;
/* off 0x0010 */	struct _MMWSLE*	Wsle;
/* off 0x0014 */	void*	LowestPagableAddress;
/* off 0x0018 */	unsigned long	LastInitializedWsle;
/* off 0x001c */	unsigned long	NextEstimationSlot;
/* off 0x0020 */	unsigned long	NextAgingSlot;
/* off 0x0024 */	unsigned long	EstimatedAvailable;
/* off 0x0028 */	unsigned long	GrowthSinceLastEstimate;
/* off 0x002c */	unsigned long	NumberOfCommittedPageTables;
/* off 0x0030 */	unsigned long	VadBitMapHint;
/* off 0x0034 */	unsigned long	NonDirectCount;
/* off 0x0038 */	unsigned long	LastVadBit;
/* off 0x003c */	unsigned long	MaximumLastVadBit;
/* off 0x0040 */	unsigned long	LastAllocationSizeHint;
/* off 0x0044 */	unsigned long	LastAllocationSize;
/* off 0x0048 */	struct _MMWSLE_NONDIRECT_HASH*	NonDirectHash;
/* off 0x004c */	struct _MMWSLE_HASH*	HashTableStart;
/* off 0x0050 */	struct _MMWSLE_HASH*	HighestPermittedHashAddress;
/* off 0x0054 */	void*	HighestUserAddress;
/* off 0x0058 */	unsigned short UsedPageTableEntries[768];
/* off 0x0658 */	unsigned long CommittedPageTables[24];
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
struct _MMWSLE_FREE_ENTRY /* sizeof 00000004 4 */
{
/* off 0x0000 */	unsigned long	MustBeZero:1	 /* start bit 0 */;
/* off 0x0000 */	unsigned long	PreviousFree:11	 /* start bit 1 */;
/* off 0x0000 */	unsigned long	NextFree:20	 /* start bit 12 */;
};
struct _MMWSLE /* sizeof 00000004 4 */
{
/* off 0x0000 */	
	union  /* sizeof 00000004 4 */
	{
	/* off 0x0000 */	void*	VirtualAddress;
	/* off 0x0000 */	unsigned long	Long;
	/* off 0x0000 */	struct _MMWSLENTRY	e1;
	/* off 0x0000 */	struct _MMWSLE_FREE_ENTRY	e2;
	}	u1;
};
struct _MMWSLE_NONDIRECT_HASH /* sizeof 00000008 8 */
{
/* off 0x0000 */	void*	Key;
/* off 0x0004 */	unsigned long	Index;
};
struct _MMWSLE_HASH /* sizeof 00000004 4 */
{
/* off 0x0000 */	unsigned long	Index;
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
/* off 0x000c */	
	union  /* sizeof 00000004 4 */
	{
	/* off 0x0000 */	struct _IRP*	MasterIrp;
	/* off 0x0000 */	long	IrpCount;
	/* off 0x0000 */	void*	SystemBuffer;
	}	AssociatedIrp;
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
/* off 0x0030 */	
	union  /* sizeof 00000008 8 */
	{
	/* off 0x0000 */	
		struct  /* sizeof 00000008 8 */
		{
		union
		{
		/* off 0x0000 */	void( __stdcall *UserApcRoutine)(void*,struct _IO_STATUS_BLOCK*,unsigned long);
		/* off 0x0000 */	void*	IssuingProcess;
		};
		/* off 0x0004 */	void*	UserApcContext;
		}	AsynchronousParameters;
	/* off 0x0000 */	union _LARGE_INTEGER	AllocationSize;
	}	Overlay;
/* off 0x0038 */	void( __stdcall *CancelRoutine)(struct _DEVICE_OBJECT*,struct _IRP*);
/* off 0x003c */	void*	UserBuffer;
/* off 0x0040 */	
	union  /* sizeof 00000030 48 */
	{
	/* off 0x0000 */	
		struct  /* sizeof 00000028 40 */
		{
		union
		{
		/* off 0x0000 */	struct _KDEVICE_QUEUE_ENTRY	DeviceQueueEntry;
		/* off 0x0000 */	void* DriverContext[4];
		};
		/* off 0x0010 */	struct _ETHREAD*	Thread;
		/* off 0x0014 */	char*	AuxiliaryBuffer;
		/* off 0x0018 */	struct _LIST_ENTRY	ListEntry;
		union
		{
		/* off 0x0020 */	struct _IO_STACK_LOCATION*	CurrentStackLocation;
		/* off 0x0020 */	unsigned long	PacketType;
		};
		/* off 0x0024 */	struct _FILE_OBJECT*	OriginalFileObject;
		}	Overlay;
	/* off 0x0000 */	struct _KAPC	Apc;
	/* off 0x0000 */	void*	CompletionKey;
	}	Tail;
};
struct _SYSTEM_POWER_STATE_CONTEXT /* sizeof 00000004 4 */
{
union
{
struct
{
/* off 0x0000 */	unsigned long	Reserved1:8	 /* start bit 0 */;
/* off 0x0000 */	unsigned long	TargetSystemState:4	 /* start bit 8 */;
/* off 0x0000 */	unsigned long	EffectiveSystemState:4	 /* start bit 12 */;
/* off 0x0000 */	unsigned long	CurrentSystemState:4	 /* start bit 16 */;
/* off 0x0000 */	unsigned long	IgnoreHibernationPath:1	 /* start bit 20 */;
/* off 0x0000 */	unsigned long	PseudoTransition:1	 /* start bit 21 */;
/* off 0x0000 */	unsigned long	Reserved2:10	 /* start bit 22 */;
};
/* off 0x0000 */	unsigned long	ContextAsUlong;
};
};
union _POWER_STATE /* sizeof 00000004 4 */
{
/* off 0x0000 */	enum _SYSTEM_POWER_STATE	SystemState;
/* off 0x0000 */	enum _DEVICE_POWER_STATE	DeviceState;
};
struct _IO_STACK_LOCATION /* sizeof 00000024 36 */
{
/* off 0x0000 */	unsigned char	MajorFunction;
/* off 0x0001 */	unsigned char	MinorFunction;
/* off 0x0002 */	unsigned char	Flags;
/* off 0x0003 */	unsigned char	Control;
/* off 0x0004 */	
	union  /* sizeof 00000010 16 */
	{
	/* off 0x0000 */	
		struct  /* sizeof 00000010 16 */
		{
		/* off 0x0000 */	struct _IO_SECURITY_CONTEXT*	SecurityContext;
		/* off 0x0004 */	unsigned long	Options;
		/* off 0x0008 */	unsigned short	FileAttributes;
		/* off 0x000a */	unsigned short	ShareAccess;
		/* off 0x000c */	unsigned long	EaLength;
		}	Create;
	/* off 0x0000 */	
		struct  /* sizeof 00000010 16 */
		{
		/* off 0x0000 */	struct _IO_SECURITY_CONTEXT*	SecurityContext;
		/* off 0x0004 */	unsigned long	Options;
		/* off 0x0008 */	unsigned short	Reserved;
		/* off 0x000a */	unsigned short	ShareAccess;
		/* off 0x000c */	struct _NAMED_PIPE_CREATE_PARAMETERS*	Parameters;
		}	CreatePipe;
	/* off 0x0000 */	
		struct  /* sizeof 00000010 16 */
		{
		/* off 0x0000 */	struct _IO_SECURITY_CONTEXT*	SecurityContext;
		/* off 0x0004 */	unsigned long	Options;
		/* off 0x0008 */	unsigned short	Reserved;
		/* off 0x000a */	unsigned short	ShareAccess;
		/* off 0x000c */	struct _MAILSLOT_CREATE_PARAMETERS*	Parameters;
		}	CreateMailslot;
	/* off 0x0000 */	
		struct  /* sizeof 00000010 16 */
		{
		/* off 0x0000 */	unsigned long	Length;
		/* off 0x0004 */	unsigned long	Key;
		/* off 0x0008 */	union _LARGE_INTEGER	ByteOffset;
		}	Read;
	/* off 0x0000 */	
		struct  /* sizeof 00000010 16 */
		{
		/* off 0x0000 */	unsigned long	Length;
		/* off 0x0004 */	unsigned long	Key;
		/* off 0x0008 */	union _LARGE_INTEGER	ByteOffset;
		}	Write;
	/* off 0x0000 */	
		struct  /* sizeof 00000010 16 */
		{
		/* off 0x0000 */	unsigned long	Length;
		/* off 0x0004 */	struct _UNICODE_STRING*	FileName;
		/* off 0x0008 */	enum _FILE_INFORMATION_CLASS	FileInformationClass;
		/* off 0x000c */	unsigned long	FileIndex;
		}	QueryDirectory;
	/* off 0x0000 */	
		struct  /* sizeof 00000008 8 */
		{
		/* off 0x0000 */	unsigned long	Length;
		/* off 0x0004 */	unsigned long	CompletionFilter;
		}	NotifyDirectory;
	/* off 0x0000 */	
		struct  /* sizeof 00000008 8 */
		{
		/* off 0x0000 */	unsigned long	Length;
		/* off 0x0004 */	enum _FILE_INFORMATION_CLASS	FileInformationClass;
		}	QueryFile;
	/* off 0x0000 */	
		struct  /* sizeof 00000010 16 */
		{
		/* off 0x0000 */	unsigned long	Length;
		/* off 0x0004 */	enum _FILE_INFORMATION_CLASS	FileInformationClass;
		/* off 0x0008 */	struct _FILE_OBJECT*	FileObject;
		union
		{
		struct
		{
		/* off 0x000c */	unsigned char	ReplaceIfExists;
		/* off 0x000d */	unsigned char	AdvanceOnly;
		};
		/* off 0x000c */	unsigned long	ClusterCount;
		/* off 0x000c */	void*	DeleteHandle;
		};
		}	SetFile;
	/* off 0x0000 */	
		struct  /* sizeof 00000010 16 */
		{
		/* off 0x0000 */	unsigned long	Length;
		/* off 0x0004 */	void*	EaList;
		/* off 0x0008 */	unsigned long	EaListLength;
		/* off 0x000c */	unsigned long	EaIndex;
		}	QueryEa;
	/* off 0x0000 */	
		struct  /* sizeof 00000004 4 */
		{
		/* off 0x0000 */	unsigned long	Length;
		}	SetEa;
	/* off 0x0000 */	
		struct  /* sizeof 00000008 8 */
		{
		/* off 0x0000 */	unsigned long	Length;
		/* off 0x0004 */	enum _FSINFOCLASS	FsInformationClass;
		}	QueryVolume;
	/* off 0x0000 */	
		struct  /* sizeof 00000008 8 */
		{
		/* off 0x0000 */	unsigned long	Length;
		/* off 0x0004 */	enum _FSINFOCLASS	FsInformationClass;
		}	SetVolume;
	/* off 0x0000 */	
		struct  /* sizeof 00000010 16 */
		{
		/* off 0x0000 */	unsigned long	OutputBufferLength;
		/* off 0x0004 */	unsigned long	InputBufferLength;
		/* off 0x0008 */	unsigned long	FsControlCode;
		/* off 0x000c */	void*	Type3InputBuffer;
		}	FileSystemControl;
	/* off 0x0000 */	
		struct  /* sizeof 00000010 16 */
		{
		/* off 0x0000 */	union _LARGE_INTEGER*	Length;
		/* off 0x0004 */	unsigned long	Key;
		/* off 0x0008 */	union _LARGE_INTEGER	ByteOffset;
		}	LockControl;
	/* off 0x0000 */	
		struct  /* sizeof 00000010 16 */
		{
		/* off 0x0000 */	unsigned long	OutputBufferLength;
		/* off 0x0004 */	unsigned long	InputBufferLength;
		/* off 0x0008 */	unsigned long	IoControlCode;
		/* off 0x000c */	void*	Type3InputBuffer;
		}	DeviceIoControl;
	/* off 0x0000 */	
		struct  /* sizeof 00000008 8 */
		{
		/* off 0x0000 */	unsigned long	SecurityInformation;
		/* off 0x0004 */	unsigned long	Length;
		}	QuerySecurity;
	/* off 0x0000 */	
		struct  /* sizeof 00000008 8 */
		{
		/* off 0x0000 */	unsigned long	SecurityInformation;
		/* off 0x0004 */	void*	SecurityDescriptor;
		}	SetSecurity;
	/* off 0x0000 */	
		struct  /* sizeof 00000008 8 */
		{
		/* off 0x0000 */	struct _VPB*	Vpb;
		/* off 0x0004 */	struct _DEVICE_OBJECT*	DeviceObject;
		}	MountVolume;
	/* off 0x0000 */	
		struct  /* sizeof 00000008 8 */
		{
		/* off 0x0000 */	struct _VPB*	Vpb;
		/* off 0x0004 */	struct _DEVICE_OBJECT*	DeviceObject;
		}	VerifyVolume;
	/* off 0x0000 */	
		struct  /* sizeof 00000004 4 */
		{
		/* off 0x0000 */	struct _SCSI_REQUEST_BLOCK*	Srb;
		}	Scsi;
	/* off 0x0000 */	
		struct  /* sizeof 00000010 16 */
		{
		/* off 0x0000 */	unsigned long	Length;
		/* off 0x0004 */	void*	StartSid;
		/* off 0x0008 */	struct _FILE_GET_QUOTA_INFORMATION*	SidList;
		/* off 0x000c */	unsigned long	SidListLength;
		}	QueryQuota;
	/* off 0x0000 */	
		struct  /* sizeof 00000004 4 */
		{
		/* off 0x0000 */	unsigned long	Length;
		}	SetQuota;
	/* off 0x0000 */	
		struct  /* sizeof 00000004 4 */
		{
		/* off 0x0000 */	enum _DEVICE_RELATION_TYPE	Type;
		}	QueryDeviceRelations;
	/* off 0x0000 */	
		struct  /* sizeof 00000010 16 */
		{
		/* off 0x0000 */	struct _GUID*	InterfaceType;
		/* off 0x0004 */	unsigned short	Size;
		/* off 0x0006 */	unsigned short	Version;
		/* off 0x0008 */	struct _INTERFACE*	Interface;
		/* off 0x000c */	void*	InterfaceSpecificData;
		}	QueryInterface;
	/* off 0x0000 */	
		struct  /* sizeof 00000004 4 */
		{
		/* off 0x0000 */	struct _DEVICE_CAPABILITIES*	Capabilities;
		}	DeviceCapabilities;
	/* off 0x0000 */	
		struct  /* sizeof 00000004 4 */
		{
		/* off 0x0000 */	struct _IO_RESOURCE_REQUIREMENTS_LIST*	IoResourceRequirementList;
		}	FilterResourceRequirements;
	/* off 0x0000 */	
		struct  /* sizeof 00000010 16 */
		{
		/* off 0x0000 */	unsigned long	WhichSpace;
		/* off 0x0004 */	void*	Buffer;
		/* off 0x0008 */	unsigned long	Offset;
		/* off 0x000c */	unsigned long	Length;
		}	ReadWriteConfig;
	/* off 0x0000 */	
		struct  /* sizeof 00000001 1 */
		{
		/* off 0x0000 */	unsigned char	Lock;
		}	SetLock;
	/* off 0x0000 */	
		struct  /* sizeof 00000004 4 */
		{
		/* off 0x0000 */	enum BUS_QUERY_ID_TYPE	IdType;
		}	QueryId;
	/* off 0x0000 */	
		struct  /* sizeof 00000008 8 */
		{
		/* off 0x0000 */	enum DEVICE_TEXT_TYPE	DeviceTextType;
		/* off 0x0004 */	unsigned long	LocaleId;
		}	QueryDeviceText;
	/* off 0x0000 */	
		struct  /* sizeof 00000008 8 */
		{
		/* off 0x0000 */	unsigned char	InPath;
		/* off 0x0001 */	unsigned char Reserved[3];
		/* off 0x0004 */	enum _DEVICE_USAGE_NOTIFICATION_TYPE	Type;
		}	UsageNotification;
	/* off 0x0000 */	
		struct  /* sizeof 00000004 4 */
		{
		/* off 0x0000 */	enum _SYSTEM_POWER_STATE	PowerState;
		}	WaitWake;
	/* off 0x0000 */	
		struct  /* sizeof 00000004 4 */
		{
		/* off 0x0000 */	struct _POWER_SEQUENCE*	PowerSequence;
		}	PowerSequence;
	/* off 0x0000 */	
		struct  /* sizeof 00000010 16 */
		{
		union
		{
		/* off 0x0000 */	unsigned long	SystemContext;
		/* off 0x0000 */	struct _SYSTEM_POWER_STATE_CONTEXT	SystemPowerStateContext;
		};
		/* off 0x0004 */	enum _POWER_STATE_TYPE	Type;
		/* off 0x0008 */	union _POWER_STATE	State;
		/* off 0x000c */	enum POWER_ACTION	ShutdownType;
		}	Power;
	/* off 0x0000 */	
		struct  /* sizeof 00000008 8 */
		{
		/* off 0x0000 */	struct _CM_RESOURCE_LIST*	AllocatedResources;
		/* off 0x0004 */	struct _CM_RESOURCE_LIST*	AllocatedResourcesTranslated;
		}	StartDevice;
	/* off 0x0000 */	
		struct  /* sizeof 00000010 16 */
		{
		/* off 0x0000 */	unsigned long	ProviderId;
		/* off 0x0004 */	void*	DataPath;
		/* off 0x0008 */	unsigned long	BufferSize;
		/* off 0x000c */	void*	Buffer;
		}	WMI;
	/* off 0x0000 */	
		struct  /* sizeof 00000010 16 */
		{
		/* off 0x0000 */	void*	Argument1;
		/* off 0x0004 */	void*	Argument2;
		/* off 0x0008 */	void*	Argument3;
		/* off 0x000c */	void*	Argument4;
		}	Others;
	}	Parameters;
/* off 0x0014 */	struct _DEVICE_OBJECT*	DeviceObject;
/* off 0x0018 */	struct _FILE_OBJECT*	FileObject;
/* off 0x001c */	long( __stdcall *CompletionRoutine)(struct _DEVICE_OBJECT*,struct _IRP*,void*);
/* off 0x0020 */	void*	Context;
};
struct _IO_SECURITY_CONTEXT /* sizeof 00000010 16 */
{
/* off 0x0000 */	struct _SECURITY_QUALITY_OF_SERVICE*	SecurityQos;
/* off 0x0004 */	struct _ACCESS_STATE*	AccessState;
/* off 0x0008 */	unsigned long	DesiredAccess;
/* off 0x000c */	unsigned long	FullCreateOptions;
};
struct _SECURITY_QUALITY_OF_SERVICE /* sizeof 0000000c 12 */
{
/* off 0x0000 */	unsigned long	Length;
/* off 0x0004 */	enum _SECURITY_IMPERSONATION_LEVEL	ImpersonationLevel;
/* off 0x0008 */	unsigned char	ContextTrackingMode;
/* off 0x0009 */	unsigned char	EffectiveOnly;
};
enum _SECURITY_IMPERSONATION_LEVEL
{
	SecurityAnonymous	=0x00000000	,//0
	SecurityIdentification	=0x00000001	,//0
	SecurityImpersonation	=0x00000002	,//0
	SecurityDelegation	=0x00000003	,//0
};
struct _SECURITY_SUBJECT_CONTEXT /* sizeof 00000010 16 */
{
/* off 0x0000 */	void*	ClientToken;
/* off 0x0004 */	enum _SECURITY_IMPERSONATION_LEVEL	ImpersonationLevel;
/* off 0x0008 */	void*	PrimaryToken;
/* off 0x000c */	void*	ProcessAuditId;
};
struct _LUID_AND_ATTRIBUTES /* sizeof 0000000c 12 */
{
/* off 0x0000 */	struct _LUID	Luid;
/* off 0x0008 */	unsigned long	Attributes;
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
/* off 0x0034 */	
	union  /* sizeof 0000002c 44 */
	{
	/* off 0x0000 */	struct _INITIAL_PRIVILEGE_SET	InitialPrivilegeSet;
	/* off 0x0000 */	struct _PRIVILEGE_SET	PrivilegeSet;
	}	Privileges;
/* off 0x0060 */	unsigned char	AuditPrivileges;
/* off 0x0064 */	struct _UNICODE_STRING	ObjectName;
/* off 0x006c */	struct _UNICODE_STRING	ObjectTypeName;
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
	FileIoCompletionNotificationInformation	=0x00000029	,//0
	FileIoStatusBlockRangeInformation	=0x0000002a	,//0
	FileIoPriorityHintInformation	=0x0000002b	,//0
	FileSfioReserveInformation	=0x0000002c	,//0
	FileSfioVolumeInformation	=0x0000002d	,//0
	FileHardLinkInformation	=0x0000002e	,//0
	FileProcessIdsUsingFileInformation	=0x0000002f	,//0
	FileNormalizedNameInformation	=0x00000030	,//0
	FileNetworkPhysicalNameInformation	=0x00000031	,//0
	FileIdGlobalTxDirectoryInformation	=0x00000032	,//0
	FileMaximumInformation	=0x00000033	,//0
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
	FileFsVolumeFlagsInformation	=0x0000000a	,//0
	FileFsMaximumInformation	=0x0000000b	,//0
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
/* off 0x0008 */	void( __stdcall *InterfaceReference)(void*);
/* off 0x000c */	void( __stdcall *InterfaceDereference)(void*);
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
enum _DEVICE_POWER_STATE
{
	PowerDeviceUnspecified	=0x00000000	,//0
	PowerDeviceD0	=0x00000001	,//0
	PowerDeviceD1	=0x00000002	,//0
	PowerDeviceD2	=0x00000003	,//0
	PowerDeviceD3	=0x00000004	,//0
	PowerDeviceMaximum	=0x00000005	,//0
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
struct _IO_RESOURCE_DESCRIPTOR /* sizeof 00000020 32 */
{
/* off 0x0000 */	unsigned char	Option;
/* off 0x0001 */	unsigned char	Type;
/* off 0x0002 */	unsigned char	ShareDisposition;
/* off 0x0003 */	unsigned char	Spare1;
/* off 0x0004 */	unsigned short	Flags;
/* off 0x0006 */	unsigned short	Spare2;
/* off 0x0008 */	
	union  /* sizeof 00000018 24 */
	{
	/* off 0x0000 */	
		struct  /* sizeof 00000018 24 */
		{
		/* off 0x0000 */	unsigned long	Length;
		/* off 0x0004 */	unsigned long	Alignment;
		/* off 0x0008 */	union _LARGE_INTEGER	MinimumAddress;
		/* off 0x0010 */	union _LARGE_INTEGER	MaximumAddress;
		}	Port;
	/* off 0x0000 */	
		struct  /* sizeof 00000018 24 */
		{
		/* off 0x0000 */	unsigned long	Length;
		/* off 0x0004 */	unsigned long	Alignment;
		/* off 0x0008 */	union _LARGE_INTEGER	MinimumAddress;
		/* off 0x0010 */	union _LARGE_INTEGER	MaximumAddress;
		}	Memory;
	/* off 0x0000 */	
		struct  /* sizeof 00000014 20 */
		{
		/* off 0x0000 */	unsigned long	MinimumVector;
		/* off 0x0004 */	unsigned long	MaximumVector;
		/* off 0x0008 */	enum _IRQ_DEVICE_POLICY	AffinityPolicy;
		/* off 0x000c */	enum _IRQ_PRIORITY	PriorityPolicy;
		/* off 0x0010 */	unsigned long	TargetedProcessors;
		}	Interrupt;
	/* off 0x0000 */	
		struct  /* sizeof 00000008 8 */
		{
		/* off 0x0000 */	unsigned long	MinimumChannel;
		/* off 0x0004 */	unsigned long	MaximumChannel;
		}	Dma;
	/* off 0x0000 */	
		struct  /* sizeof 00000018 24 */
		{
		/* off 0x0000 */	unsigned long	Length;
		/* off 0x0004 */	unsigned long	Alignment;
		/* off 0x0008 */	union _LARGE_INTEGER	MinimumAddress;
		/* off 0x0010 */	union _LARGE_INTEGER	MaximumAddress;
		}	Generic;
	/* off 0x0000 */	
		struct  /* sizeof 0000000c 12 */
		{
		/* off 0x0000 */	unsigned long Data[3];
		}	DevicePrivate;
	/* off 0x0000 */	
		struct  /* sizeof 00000010 16 */
		{
		/* off 0x0000 */	unsigned long	Length;
		/* off 0x0004 */	unsigned long	MinBusNumber;
		/* off 0x0008 */	unsigned long	MaxBusNumber;
		/* off 0x000c */	unsigned long	Reserved;
		}	BusNumber;
	/* off 0x0000 */	
		struct  /* sizeof 0000000c 12 */
		{
		/* off 0x0000 */	unsigned long	Priority;
		/* off 0x0004 */	unsigned long	Reserved1;
		/* off 0x0008 */	unsigned long	Reserved2;
		}	ConfigData;
	/* off 0x0000 */	
		struct  /* sizeof 00000018 24 */
		{
		/* off 0x0000 */	unsigned long	Length40;
		/* off 0x0004 */	unsigned long	Alignment40;
		/* off 0x0008 */	union _LARGE_INTEGER	MinimumAddress;
		/* off 0x0010 */	union _LARGE_INTEGER	MaximumAddress;
		}	Memory40;
	/* off 0x0000 */	
		struct  /* sizeof 00000018 24 */
		{
		/* off 0x0000 */	unsigned long	Length48;
		/* off 0x0004 */	unsigned long	Alignment48;
		/* off 0x0008 */	union _LARGE_INTEGER	MinimumAddress;
		/* off 0x0010 */	union _LARGE_INTEGER	MaximumAddress;
		}	Memory48;
	/* off 0x0000 */	
		struct  /* sizeof 00000018 24 */
		{
		/* off 0x0000 */	unsigned long	Length64;
		/* off 0x0004 */	unsigned long	Alignment64;
		/* off 0x0008 */	union _LARGE_INTEGER	MinimumAddress;
		/* off 0x0010 */	union _LARGE_INTEGER	MaximumAddress;
		}	Memory64;
	}	u;
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
	Vmcs	=0x00000010	,//0
	MaximumInterfaceType	=0x00000011	,//0
};
enum _IRQ_DEVICE_POLICY
{
	IrqPolicyMachineDefault	=0x00000000	,//0
	IrqPolicyAllCloseProcessors	=0x00000001	,//0
	IrqPolicyOneCloseProcessor	=0x00000002	,//0
	IrqPolicyAllProcessorsInMachine	=0x00000003	,//0
	IrqPolicySpecifiedProcessors	=0x00000004	,//0
	IrqPolicySpreadMessagesAcrossAllProcessors	=0x00000005	,//0
};
enum _IRQ_PRIORITY
{
	IrqPriorityUndefined	=0x00000000	,//0
	IrqPriorityLow	=0x00000001	,//0
	IrqPriorityNormal	=0x00000002	,//0
	IrqPriorityHigh	=0x00000003	,//0
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
enum _DEVICE_USAGE_NOTIFICATION_TYPE
{
	DeviceUsageTypeUndefined	=0x00000000	,//0
	DeviceUsageTypePaging	=0x00000001	,//0
	DeviceUsageTypeHibernation	=0x00000002	,//0
	DeviceUsageTypeDumpFile	=0x00000003	,//0
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
struct _CM_PARTIAL_RESOURCE_DESCRIPTOR /* sizeof 00000010 16 */
{
/* off 0x0000 */	unsigned char	Type;
/* off 0x0001 */	unsigned char	ShareDisposition;
/* off 0x0002 */	unsigned short	Flags;
/* off 0x0004 */	
	union  /* sizeof 0000000c 12 */
	{
	/* off 0x0000 */	
		struct  /* sizeof 0000000c 12 */
		{
		/* off 0x0000 */	union _LARGE_INTEGER	Start;
		/* off 0x0008 */	unsigned long	Length;
		}	Generic;
	/* off 0x0000 */	
		struct  /* sizeof 0000000c 12 */
		{
		/* off 0x0000 */	union _LARGE_INTEGER	Start;
		/* off 0x0008 */	unsigned long	Length;
		}	Port;
	/* off 0x0000 */	
		struct  /* sizeof 0000000c 12 */
		{
		/* off 0x0000 */	unsigned long	Level;
		/* off 0x0004 */	unsigned long	Vector;
		/* off 0x0008 */	unsigned long	Affinity;
		}	Interrupt;
	/* off 0x0000 */	
		struct  /* sizeof 0000000c 12 */
		{
		union
		{
		/* off 0x0000 */	
			struct  /* sizeof 0000000c 12 */
			{
			/* off 0x0000 */	unsigned short	Reserved;
			/* off 0x0002 */	unsigned short	MessageCount;
			/* off 0x0004 */	unsigned long	Vector;
			/* off 0x0008 */	unsigned long	Affinity;
			}	Raw;
		/* off 0x0000 */	
			struct  /* sizeof 0000000c 12 */
			{
			/* off 0x0000 */	unsigned long	Level;
			/* off 0x0004 */	unsigned long	Vector;
			/* off 0x0008 */	unsigned long	Affinity;
			}	Translated;
		};
		}	MessageInterrupt;
	/* off 0x0000 */	
		struct  /* sizeof 0000000c 12 */
		{
		/* off 0x0000 */	union _LARGE_INTEGER	Start;
		/* off 0x0008 */	unsigned long	Length;
		}	Memory;
	/* off 0x0000 */	
		struct  /* sizeof 0000000c 12 */
		{
		/* off 0x0000 */	unsigned long	Channel;
		/* off 0x0004 */	unsigned long	Port;
		/* off 0x0008 */	unsigned long	Reserved1;
		}	Dma;
	/* off 0x0000 */	
		struct  /* sizeof 0000000c 12 */
		{
		/* off 0x0000 */	unsigned long Data[3];
		}	DevicePrivate;
	/* off 0x0000 */	
		struct  /* sizeof 0000000c 12 */
		{
		/* off 0x0000 */	unsigned long	Start;
		/* off 0x0004 */	unsigned long	Length;
		/* off 0x0008 */	unsigned long	Reserved;
		}	BusNumber;
	/* off 0x0000 */	
		struct  /* sizeof 0000000c 12 */
		{
		/* off 0x0000 */	unsigned long	DataSize;
		/* off 0x0004 */	unsigned long	Reserved1;
		/* off 0x0008 */	unsigned long	Reserved2;
		}	DeviceSpecificData;
	/* off 0x0000 */	
		struct  /* sizeof 0000000c 12 */
		{
		/* off 0x0000 */	union _LARGE_INTEGER	Start;
		/* off 0x0008 */	unsigned long	Length40;
		}	Memory40;
	/* off 0x0000 */	
		struct  /* sizeof 0000000c 12 */
		{
		/* off 0x0000 */	union _LARGE_INTEGER	Start;
		/* off 0x0008 */	unsigned long	Length48;
		}	Memory48;
	/* off 0x0000 */	
		struct  /* sizeof 0000000c 12 */
		{
		/* off 0x0000 */	union _LARGE_INTEGER	Start;
		/* off 0x0008 */	unsigned long	Length64;
		}	Memory64;
	}	u;
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
struct _IO_TIMER /* sizeof 00000018 24 */
{
/* off 0x0000 */	short	Type;
/* off 0x0002 */	short	TimerFlag;
/* off 0x0004 */	struct _LIST_ENTRY	TimerList;
/* off 0x000c */	void( __stdcall *TimerRoutine)(struct _DEVICE_OBJECT*,void*);
/* off 0x0010 */	void*	Context;
/* off 0x0014 */	struct _DEVICE_OBJECT*	DeviceObject;
};
enum _IO_ALLOCATION_ACTION
{
	KeepObject	=0x00000001	,//0
	DeallocateObject	=0x00000002	,//0
	DeallocateObjectKeepRegisters	=0x00000003	,//0
};
struct _DEVOBJ_EXTENSION /* sizeof 0000003c 60 */
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
/* off 0x002c */	struct _LIST_ENTRY	DependentList;
/* off 0x0034 */	struct _LIST_ENTRY	ProviderList;
};
struct _POWER_CHANNEL_SUMMARY /* sizeof 00000014 20 */
{
/* off 0x0000 */	unsigned long	Signature;
/* off 0x0004 */	unsigned long	TotalCount;
/* off 0x0008 */	unsigned long	D0Count;
/* off 0x000c */	struct _LIST_ENTRY	NotifyList;
};
struct _DEVICE_OBJECT_POWER_EXTENSION /* sizeof 00000060 96 */
{
/* off 0x0000 */	unsigned long	IdleCount;
/* off 0x0004 */	unsigned long	BusyCount;
/* off 0x0008 */	unsigned long	TotalBusyCount;
/* off 0x000c */	unsigned long	ConservationIdleTime;
/* off 0x0010 */	unsigned long	PerformanceIdleTime;
/* off 0x0014 */	struct _DEVICE_OBJECT*	DeviceObject;
/* off 0x0018 */	struct _LIST_ENTRY	IdleList;
/* off 0x0020 */	unsigned char	DeviceType;
/* off 0x0024 */	enum _DEVICE_POWER_STATE	IdleState;
/* off 0x0028 */	enum _DEVICE_POWER_STATE	CurrentState;
/* off 0x002c */	struct _LIST_ENTRY	NotifySourceList;
/* off 0x0034 */	struct _LIST_ENTRY	NotifyTargetList;
/* off 0x003c */	struct _POWER_CHANNEL_SUMMARY	PowerChannelSummary;
/* off 0x0050 */	struct _LIST_ENTRY	Volume;
/* off 0x0058 */	
	union  /* sizeof 00000008 8 */
	{
	/* off 0x0000 */	
		struct  /* sizeof 00000008 8 */
		{
		/* off 0x0000 */	unsigned long	IdleTime;
		/* off 0x0004 */	unsigned long	NonIdleTime;
		}	Disk;
	}	Specific;
};
union _PSP_RATE_APC /* sizeof 00000000 0 */
{
};
enum _IO_PRIORITY_HINT
{
	IoPriorityVeryLow	=0x00000000	,//0
	IoPriorityLow	=0x00000001	,//0
	IoPriorityNormal	=0x00000002	,//0
	IoPriorityHigh	=0x00000003	,//0
	IoPriorityCritical	=0x00000004	,//0
	MaxIoPriorityTypes	=0x00000005	,//0
};
struct _IO_DRIVER_CREATE_CONTEXT /* sizeof 00000010 16 */
{
/* off 0x0000 */	short	Size;
/* off 0x0004 */	struct _ECP_LIST*	ExtraCreateParameter;
/* off 0x0008 */	void*	DeviceObjectHint;
/* off 0x000c */	struct _TXN_PARAMETER_BLOCK*	TxnParameters;
};
struct _ECP_LIST /* sizeof 00000000 0 */
{
};
struct _TXN_PARAMETER_BLOCK /* sizeof 00000008 8 */
{
/* off 0x0000 */	unsigned short	Length;
/* off 0x0002 */	unsigned short	TxFsContext;
/* off 0x0004 */	void*	TransactionObject;
};
struct _IO_PRIORITY_INFO /* sizeof 00000010 16 */
{
/* off 0x0000 */	unsigned long	Size;
/* off 0x0004 */	unsigned long	ThreadPriority;
/* off 0x0008 */	unsigned long	PagePriority;
/* off 0x000c */	enum _IO_PRIORITY_HINT	IoPriority;
};
struct _GENERIC_MAPPING /* sizeof 00000010 16 */
{
/* off 0x0000 */	unsigned long	GenericRead;
/* off 0x0004 */	unsigned long	GenericWrite;
/* off 0x0008 */	unsigned long	GenericExecute;
/* off 0x000c */	unsigned long	GenericAll;
};
struct _OBJECT_TYPE_INITIALIZER /* sizeof 00000050 80 */
{
/* off 0x0000 */	unsigned short	Length;
union
{
/* off 0x0002 */	unsigned char	ObjectTypeFlags;
struct
{
/* off 0x0002 */	unsigned char	CaseInsensitive:1	 /* start bit 0 */;
/* off 0x0002 */	unsigned char	UnnamedObjectsOnly:1	 /* start bit 1 */;
/* off 0x0002 */	unsigned char	UseDefaultObject:1	 /* start bit 2 */;
/* off 0x0002 */	unsigned char	SecurityRequired:1	 /* start bit 3 */;
/* off 0x0002 */	unsigned char	MaintainHandleCount:1	 /* start bit 4 */;
/* off 0x0002 */	unsigned char	MaintainTypeList:1	 /* start bit 5 */;
/* off 0x0002 */	unsigned char	SupportsObjectCallbacks:1	 /* start bit 6 */;
};
};
/* off 0x0004 */	unsigned long	ObjectTypeCode;
/* off 0x0008 */	unsigned long	InvalidAttributes;
/* off 0x000c */	struct _GENERIC_MAPPING	GenericMapping;
/* off 0x001c */	unsigned long	ValidAccessMask;
/* off 0x0020 */	unsigned long	RetainAccess;
/* off 0x0024 */	enum _POOL_TYPE	PoolType;
/* off 0x0028 */	unsigned long	DefaultPagedPoolCharge;
/* off 0x002c */	unsigned long	DefaultNonPagedPoolCharge;
/* off 0x0030 */	void( __stdcall *DumpProcedure)(void*,struct _OBJECT_DUMP_CONTROL*);
/* off 0x0034 */	long( __stdcall *OpenProcedure)(enum _OB_OPEN_REASON,char,struct _EPROCESS*,void*,unsigned long*,unsigned long);
/* off 0x0038 */	void( __stdcall *CloseProcedure)(struct _EPROCESS*,void*,unsigned long,unsigned long,unsigned long);
/* off 0x003c */	void( __stdcall *DeleteProcedure)(void*);
/* off 0x0040 */	long( __stdcall *ParseProcedure)(void*,void*,struct _ACCESS_STATE*,char,unsigned long,struct _UNICODE_STRING*,struct _UNICODE_STRING*,void*,struct _SECURITY_QUALITY_OF_SERVICE*,void**);
/* off 0x0044 */	long( __stdcall *SecurityProcedure)(void*,enum _SECURITY_OPERATION_CODE,unsigned long*,void*,unsigned long*,void**,enum _POOL_TYPE,struct _GENERIC_MAPPING*,char);
/* off 0x0048 */	long( __stdcall *QueryNameProcedure)(void*,unsigned char,struct _OBJECT_NAME_INFORMATION*,unsigned long,unsigned long*,char);
/* off 0x004c */	unsigned char( __stdcall *OkayToCloseProcedure)(struct _EPROCESS*,void*,void*,char);
};
struct _OBJECT_TYPE /* sizeof 00000140 320 */
{
/* off 0x0000 */	struct _LIST_ENTRY	TypeList;
/* off 0x0008 */	struct _UNICODE_STRING	Name;
/* off 0x0010 */	void*	DefaultObject;
/* off 0x0014 */	unsigned long	Index;
/* off 0x0018 */	unsigned long	TotalNumberOfObjects;
/* off 0x001c */	unsigned long	TotalNumberOfHandles;
/* off 0x0020 */	unsigned long	HighWaterNumberOfObjects;
/* off 0x0024 */	unsigned long	HighWaterNumberOfHandles;
/* off 0x0028 */	struct _OBJECT_TYPE_INITIALIZER	TypeInfo;
/* off 0x0078 */	struct _ERESOURCE	Mutex;
/* off 0x00b0 */	struct _EX_PUSH_LOCK	TypeLock;
/* off 0x00b4 */	unsigned long	Key;
/* off 0x00b8 */	struct _EX_PUSH_LOCK ObjectLocks[32];
/* off 0x0138 */	struct _LIST_ENTRY	CallbackList;
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
enum _SECURITY_OPERATION_CODE
{
	SetSecurityDescriptor	=0x00000000	,//0
	QuerySecurityDescriptor	=0x00000001	,//0
	DeleteSecurityDescriptor	=0x00000002	,//0
	AssignSecurityDescriptor	=0x00000003	,//0
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
struct _OBJECT_HANDLE_INFORMATION /* sizeof 00000008 8 */
{
/* off 0x0000 */	unsigned long	HandleAttributes;
/* off 0x0004 */	unsigned long	GrantedAccess;
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
struct _OBJECT_HEADER_QUOTA_INFO /* sizeof 00000010 16 */
{
/* off 0x0000 */	unsigned long	PagedPoolCharge;
/* off 0x0004 */	unsigned long	NonPagedPoolCharge;
/* off 0x0008 */	unsigned long	SecurityDescriptorCharge;
/* off 0x000c */	struct _EPROCESS*	ExclusiveProcess;
};
struct _OBJECT_HANDLE_COUNT_ENTRY /* sizeof 00000008 8 */
{
/* off 0x0000 */	struct _EPROCESS*	Process;
/* off 0x0004 */	unsigned long	HandleCount:24	 /* start bit 0 */;
/* off 0x0004 */	unsigned long	LockCount:8	 /* start bit 24 */;
};
struct _OBJECT_HEADER_HANDLE_INFO /* sizeof 00000008 8 */
{
union
{
/* off 0x0000 */	struct _OBJECT_HANDLE_COUNT_DATABASE*	HandleCountDataBase;
/* off 0x0000 */	struct _OBJECT_HANDLE_COUNT_ENTRY	SingleEntry;
};
};
struct _OBJECT_HANDLE_COUNT_DATABASE /* sizeof 0000000c 12 */
{
/* off 0x0000 */	unsigned long	CountEntries;
/* off 0x0004 */	struct _OBJECT_HANDLE_COUNT_ENTRY HandleCountEntries[1];
};
struct _OBJECT_HEADER_NAME_INFO /* sizeof 00000010 16 */
{
/* off 0x0000 */	struct _OBJECT_DIRECTORY*	Directory;
/* off 0x0004 */	struct _UNICODE_STRING	Name;
/* off 0x000c */	unsigned long	QueryReferences;
};
struct _OBJECT_DIRECTORY /* sizeof 000000a8 168 */
{
/* off 0x0000 */	struct _OBJECT_DIRECTORY_ENTRY* HashBuckets[37];
/* off 0x0094 */	struct _EX_PUSH_LOCK	Lock;
/* off 0x0098 */	struct _DEVICE_MAP*	DeviceMap;
/* off 0x009c */	unsigned long	SessionId;
/* off 0x00a0 */	void*	NamespaceEntry;
/* off 0x00a4 */	unsigned long	Flags;
};
struct _OBJECT_DIRECTORY_ENTRY /* sizeof 0000000c 12 */
{
/* off 0x0000 */	struct _OBJECT_DIRECTORY_ENTRY*	ChainLink;
/* off 0x0004 */	void*	Object;
/* off 0x0008 */	unsigned long	HashValue;
};
struct _DEVICE_MAP /* sizeof 00000034 52 */
{
/* off 0x0000 */	struct _OBJECT_DIRECTORY*	DosDevicesDirectory;
/* off 0x0004 */	struct _OBJECT_DIRECTORY*	GlobalDosDevicesDirectory;
/* off 0x0008 */	void*	DosDevicesDirectoryHandle;
/* off 0x000c */	unsigned long	ReferenceCount;
/* off 0x0010 */	unsigned long	DriveMap;
/* off 0x0014 */	unsigned char DriveType[32];
};
struct _OBJECT_HEADER_CREATOR_INFO /* sizeof 00000010 16 */
{
/* off 0x0000 */	struct _LIST_ENTRY	TypeList;
/* off 0x0008 */	void*	CreatorUniqueProcess;
/* off 0x000c */	unsigned short	CreatorBackTraceIndex;
/* off 0x000e */	unsigned short	Reserved;
};
struct _EVENT_DATA_DESCRIPTOR /* sizeof 00000010 16 */
{
/* off 0x0000 */	unsigned __int64	Ptr;
/* off 0x0008 */	unsigned long	Size;
/* off 0x000c */	unsigned long	Reserved;
};
struct _EVENT_DESCRIPTOR /* sizeof 00000010 16 */
{
/* off 0x0000 */	unsigned short	Id;
/* off 0x0002 */	unsigned char	Version;
/* off 0x0003 */	unsigned char	Channel;
/* off 0x0004 */	unsigned char	Level;
/* off 0x0005 */	unsigned char	Opcode;
/* off 0x0006 */	unsigned short	Task;
/* off 0x0008 */	unsigned __int64	Keyword;
};
struct _PERFINFO_GROUPMASK /* sizeof 00000020 32 */
{
/* off 0x0000 */	unsigned long Masks[8];
};
struct _MM_PAGE_ACCESS_INFO_HEADER /* sizeof 00000038 56 */
{
/* off 0x0000 */	struct _SINGLE_LIST_ENTRY	Link;
/* off 0x0004 */	enum _MM_PAGE_ACCESS_TYPE	Type;
union
{
/* off 0x0008 */	unsigned long	EmptySequenceNumber;
/* off 0x0008 */	unsigned long	CurrentFileIndex;
};
/* off 0x0010 */	unsigned __int64	CreateTime;
union
{
/* off 0x0018 */	unsigned __int64	EmptyTime;
/* off 0x0018 */	struct _MM_PAGE_ACCESS_INFO*	TempEntry;
};
union
{
struct
{
/* off 0x0020 */	struct _MM_PAGE_ACCESS_INFO*	PageEntry;
union
{
struct
{
/* off 0x0024 */	unsigned long*	FileEntry;
/* off 0x0028 */	unsigned long*	FirstFileEntry;
/* off 0x002c */	struct _EPROCESS*	Process;
/* off 0x0030 */	unsigned long	SessionId;
};
struct
{
/* off 0x0020 */	unsigned long*	PageFrameEntry;
};
/* off 0x0024 */	unsigned long*	LastPageFrameEntry;
};
};
};
};
enum _MM_PAGE_ACCESS_TYPE
{
	MmPteAccessType	=0x00000000	,//0
	MmCcReadAheadType	=0x00000001	,//0
	MmPfnRepurposeType	=0x00000002	,//0
	MmMaximumPageAccessType	=0x00000003	,//0
};
union _MM_PAGE_ACCESS_INFO_FLAGS /* sizeof 00000004 4 */
{
/* off 0x0000 */	
	struct  /* sizeof 00000004 4 */
	{
	/* off 0x0000 */	unsigned long	FilePointerIndex:9	 /* start bit 0 */;
	/* off 0x0000 */	unsigned long	HardFault:1	 /* start bit 9 */;
	/* off 0x0000 */	unsigned long	Image:1	 /* start bit 10 */;
	/* off 0x0000 */	unsigned long	Spare0:1	 /* start bit 11 */;
	}	File;
/* off 0x0000 */	
	struct  /* sizeof 00000004 4 */
	{
	/* off 0x0000 */	unsigned long	FilePointerIndex:9	 /* start bit 0 */;
	/* off 0x0000 */	unsigned long	HardFault:1	 /* start bit 9 */;
	/* off 0x0000 */	unsigned long	Spare1:2	 /* start bit 10 */;
	}	Private;
};
struct _MM_PAGE_ACCESS_INFO /* sizeof 00000008 8 */
{
union
{
/* off 0x0000 */	union _MM_PAGE_ACCESS_INFO_FLAGS	Flags;
/* off 0x0000 */	unsigned __int64	FileOffset;
/* off 0x0000 */	void*	VirtualAddress;
struct
{
/* off 0x0000 */	unsigned long	DontUse0:3	 /* start bit 0 */;
/* off 0x0000 */	unsigned long	Spare0:29	 /* start bit 3 */;
};
};
/* off 0x0004 */	void*	PointerProtoPte;
};
struct _ETW_KERNEL_TRACE_TIMESTAMP /* sizeof 00000010 16 */
{
/* off 0x0000 */	union _LARGE_INTEGER KernelTraceTimeStamp[2];
};
struct _PERFINFO_HARDPAGEFAULT_INFORMATION /* sizeof 00000018 24 */
{
/* off 0x0000 */	union _LARGE_INTEGER	ReadOffset;
/* off 0x0008 */	void*	VirtualAddress;
/* off 0x000c */	void*	FileObject;
/* off 0x0010 */	unsigned long	ThreadId;
/* off 0x0014 */	unsigned long	ByteCount;
};
struct _PF_HARD_FAULT_INFO /* sizeof 00000030 48 */
{
/* off 0x0000 */	struct _ETW_KERNEL_TRACE_TIMESTAMP	KernelTimeStamp;
/* off 0x0010 */	struct _PERFINFO_HARDPAGEFAULT_INFORMATION	HardFaultEvent;
/* off 0x0028 */	union _LARGE_INTEGER	IoTimeInTicks;
};
enum _PF_FILE_ACCESS_TYPE
{
	PfFileAccessTypeRead	=0x00000000	,//0
	PfFileAccessTypeWrite	=0x00000001	,//0
	PfFileAccessTypeMax	=0x00000002	,//0
};
union _WHEA_REVISION /* sizeof 00000002 2 */
{
struct
{
/* off 0x0000 */	unsigned char	MinorRevision;
/* off 0x0001 */	unsigned char	MajorRevision;
};
/* off 0x0000 */	unsigned short	AsUSHORT;
};
union _WHEA_ERROR_RECORD_HEADER_VALIDBITS /* sizeof 00000004 4 */
{
struct
{
/* off 0x0000 */	unsigned long	Timestamp:1	 /* start bit 0 */;
/* off 0x0000 */	unsigned long	PlatformId:1	 /* start bit 1 */;
/* off 0x0000 */	unsigned long	PartitionId:1	 /* start bit 2 */;
/* off 0x0000 */	unsigned long	Reserved:29	 /* start bit 3 */;
};
/* off 0x0000 */	unsigned long	AsULONG;
};
union _WHEA_TIMESTAMP /* sizeof 00000008 8 */
{
struct
{
/* off 0x0000 */	unsigned __int64	Seconds:8	 /* start bit 0 */;
/* off 0x0000 */	unsigned __int64	Minutes:8	 /* start bit 8 */;
/* off 0x0000 */	unsigned __int64	Hours:8	 /* start bit 16 */;
/* off 0x0000 */	unsigned __int64	Reserved:8	 /* start bit 24 */;
/* off 0x0000 */	unsigned __int64	Day:8	 /* start bit 32 */;
/* off 0x0000 */	unsigned __int64	Month:8	 /* start bit 40 */;
/* off 0x0000 */	unsigned __int64	Year:8	 /* start bit 48 */;
/* off 0x0000 */	unsigned __int64	Century:8	 /* start bit 56 */;
};
/* off 0x0000 */	union _LARGE_INTEGER	AsLARGE_INTEGER;
};
union _WHEA_ERROR_RECORD_HEADER_FLAGS /* sizeof 00000004 4 */
{
struct
{
/* off 0x0000 */	unsigned long	Recovered:1	 /* start bit 0 */;
/* off 0x0000 */	unsigned long	PreviousError:1	 /* start bit 1 */;
/* off 0x0000 */	unsigned long	Simulated:1	 /* start bit 2 */;
/* off 0x0000 */	unsigned long	Reserved:29	 /* start bit 3 */;
};
/* off 0x0000 */	unsigned long	AsULONG;
};
union _WHEA_PERSISTENCE_INFO /* sizeof 00000008 8 */
{
struct
{
/* off 0x0000 */	unsigned __int64	Signature:16	 /* start bit 0 */;
/* off 0x0000 */	unsigned __int64	Length:24	 /* start bit 16 */;
/* off 0x0000 */	unsigned __int64	Identifier:16	 /* start bit 40 */;
/* off 0x0000 */	unsigned __int64	Attributes:2	 /* start bit 56 */;
/* off 0x0000 */	unsigned __int64	DoNotLog:1	 /* start bit 58 */;
/* off 0x0000 */	unsigned __int64	Reserved:5	 /* start bit 59 */;
};
/* off 0x0000 */	unsigned __int64	AsULONGLONG;
};
struct _WHEA_ERROR_RECORD_HEADER /* sizeof 00000080 128 */
{
/* off 0x0000 */	unsigned long	Signature;
/* off 0x0004 */	union _WHEA_REVISION	Revision;
/* off 0x0006 */	unsigned long	SignatureEnd;
/* off 0x000a */	unsigned short	SectionCount;
/* off 0x000c */	enum _WHEA_ERROR_SEVERITY	Severity;
/* off 0x0010 */	union _WHEA_ERROR_RECORD_HEADER_VALIDBITS	ValidBits;
/* off 0x0014 */	unsigned long	Length;
/* off 0x0018 */	union _WHEA_TIMESTAMP	Timestamp;
/* off 0x0020 */	struct _GUID	PlatformId;
/* off 0x0030 */	struct _GUID	PartitionId;
/* off 0x0040 */	struct _GUID	CreatorId;
/* off 0x0050 */	struct _GUID	NotifyType;
/* off 0x0060 */	unsigned __int64	RecordId;
/* off 0x0068 */	union _WHEA_ERROR_RECORD_HEADER_FLAGS	Flags;
/* off 0x006c */	union _WHEA_PERSISTENCE_INFO	PersistenceInfo;
/* off 0x0074 */	unsigned char Reserved[12];
};
union _WHEA_ERROR_RECORD_SECTION_DESCRIPTOR_VALIDBITS /* sizeof 00000001 1 */
{
struct
{
/* off 0x0000 */	unsigned char	FRUId:1	 /* start bit 0 */;
/* off 0x0000 */	unsigned char	FRUText:1	 /* start bit 1 */;
/* off 0x0000 */	unsigned char	Reserved:6	 /* start bit 2 */;
};
/* off 0x0000 */	unsigned char	AsUCHAR;
};
union _WHEA_ERROR_RECORD_SECTION_DESCRIPTOR_FLAGS /* sizeof 00000004 4 */
{
struct
{
/* off 0x0000 */	unsigned long	Primary:1	 /* start bit 0 */;
/* off 0x0000 */	unsigned long	ContainmentWarning:1	 /* start bit 1 */;
/* off 0x0000 */	unsigned long	Reset:1	 /* start bit 2 */;
/* off 0x0000 */	unsigned long	ThresholdExceeded:1	 /* start bit 3 */;
/* off 0x0000 */	unsigned long	ResourceNotAvailable:1	 /* start bit 4 */;
/* off 0x0000 */	unsigned long	LatentError:1	 /* start bit 5 */;
/* off 0x0000 */	unsigned long	Reserved:26	 /* start bit 6 */;
};
/* off 0x0000 */	unsigned long	AsULONG;
};
struct _WHEA_ERROR_RECORD_SECTION_DESCRIPTOR /* sizeof 00000048 72 */
{
/* off 0x0000 */	unsigned long	SectionOffset;
/* off 0x0004 */	unsigned long	SectionLength;
/* off 0x0008 */	union _WHEA_REVISION	Revision;
/* off 0x000a */	union _WHEA_ERROR_RECORD_SECTION_DESCRIPTOR_VALIDBITS	ValidBits;
/* off 0x000b */	unsigned char	Reserved;
/* off 0x000c */	union _WHEA_ERROR_RECORD_SECTION_DESCRIPTOR_FLAGS	Flags;
/* off 0x0010 */	struct _GUID	SectionType;
/* off 0x0020 */	struct _GUID	FRUId;
/* off 0x0030 */	enum _WHEA_ERROR_SEVERITY	SectionSeverity;
/* off 0x0034 */	char FRUText[20];
};
struct _WHEA_ERROR_RECORD /* sizeof 000000c8 200 */
{
/* off 0x0000 */	struct _WHEA_ERROR_RECORD_HEADER	Header;
/* off 0x0080 */	struct _WHEA_ERROR_RECORD_SECTION_DESCRIPTOR SectionDescriptor[1];
};
enum _WHEA_ERROR_SEVERITY
{
	WheaErrSevRecoverable	=0x00000000	,//0
	WheaErrSevFatal	=0x00000001	,//0
	WheaErrSevCorrected	=0x00000002	,//0
	WheaErrSevNone	=0x00000003	,//0
};
union _WHEA_ERROR_PACKET_FLAGS /* sizeof 00000004 4 */
{
struct
{
/* off 0x0000 */	unsigned long	PreviousError:1	 /* start bit 0 */;
/* off 0x0000 */	unsigned long	CpuValid:1	 /* start bit 1 */;
/* off 0x0000 */	unsigned long	HypervisorError:1	 /* start bit 2 */;
/* off 0x0000 */	unsigned long	Simulated:1	 /* start bit 3 */;
/* off 0x0000 */	unsigned long	Reserved:28	 /* start bit 4 */;
};
/* off 0x0000 */	unsigned long	AsULONG;
};
union _WHEA_GENERIC_PROCESSOR_ERROR_VALIDBITS /* sizeof 00000008 8 */
{
struct
{
/* off 0x0000 */	unsigned __int64	ProcessorType:1	 /* start bit 0 */;
/* off 0x0000 */	unsigned __int64	InstructionSet:1	 /* start bit 1 */;
/* off 0x0000 */	unsigned __int64	ErrorType:1	 /* start bit 2 */;
/* off 0x0000 */	unsigned __int64	Operation:1	 /* start bit 3 */;
/* off 0x0000 */	unsigned __int64	Flags:1	 /* start bit 4 */;
/* off 0x0000 */	unsigned __int64	Level:1	 /* start bit 5 */;
/* off 0x0000 */	unsigned __int64	CPUVersion:1	 /* start bit 6 */;
/* off 0x0000 */	unsigned __int64	CPUBrandString:1	 /* start bit 7 */;
/* off 0x0000 */	unsigned __int64	ProcessorId:1	 /* start bit 8 */;
/* off 0x0000 */	unsigned __int64	TargetAddress:1	 /* start bit 9 */;
/* off 0x0000 */	unsigned __int64	RequesterId:1	 /* start bit 10 */;
/* off 0x0000 */	unsigned __int64	ResponderId:1	 /* start bit 11 */;
/* off 0x0000 */	unsigned __int64	InstructionPointer:1	 /* start bit 12 */;
/* off 0x0000 */	unsigned __int64	Reserved:51	 /* start bit 13 */;
};
/* off 0x0000 */	unsigned __int64	ValidBits;
};
struct _WHEA_GENERIC_PROCESSOR_ERROR /* sizeof 000000c0 192 */
{
/* off 0x0000 */	union _WHEA_GENERIC_PROCESSOR_ERROR_VALIDBITS	ValidBits;
/* off 0x0008 */	unsigned char	ProcessorType;
/* off 0x0009 */	unsigned char	InstructionSet;
/* off 0x000a */	unsigned char	ErrorType;
/* off 0x000b */	unsigned char	Operation;
/* off 0x000c */	unsigned char	Flags;
/* off 0x000d */	unsigned char	Level;
/* off 0x000e */	unsigned short	Reserved;
/* off 0x0010 */	unsigned __int64	CPUVersion;
/* off 0x0018 */	unsigned char CPUBrandString[128];
/* off 0x0098 */	unsigned __int64	ProcessorId;
/* off 0x00a0 */	unsigned __int64	TargetAddress;
/* off 0x00a8 */	unsigned __int64	RequesterId;
/* off 0x00b0 */	unsigned __int64	ResponderId;
/* off 0x00b8 */	unsigned __int64	InstructionPointer;
};
union _WHEA_MEMORY_ERROR_VALIDBITS /* sizeof 00000008 8 */
{
struct
{
/* off 0x0000 */	unsigned __int64	ErrorStatus:1	 /* start bit 0 */;
/* off 0x0000 */	unsigned __int64	PhysicalAddress:1	 /* start bit 1 */;
/* off 0x0000 */	unsigned __int64	PhysicalAddressMask:1	 /* start bit 2 */;
/* off 0x0000 */	unsigned __int64	Node:1	 /* start bit 3 */;
/* off 0x0000 */	unsigned __int64	Card:1	 /* start bit 4 */;
/* off 0x0000 */	unsigned __int64	Module:1	 /* start bit 5 */;
/* off 0x0000 */	unsigned __int64	Bank:1	 /* start bit 6 */;
/* off 0x0000 */	unsigned __int64	Device:1	 /* start bit 7 */;
/* off 0x0000 */	unsigned __int64	Row:1	 /* start bit 8 */;
/* off 0x0000 */	unsigned __int64	Column:1	 /* start bit 9 */;
/* off 0x0000 */	unsigned __int64	BitPosition:1	 /* start bit 10 */;
/* off 0x0000 */	unsigned __int64	RequesterId:1	 /* start bit 11 */;
/* off 0x0000 */	unsigned __int64	ResponderId:1	 /* start bit 12 */;
/* off 0x0000 */	unsigned __int64	TargetId:1	 /* start bit 13 */;
/* off 0x0000 */	unsigned __int64	ErrorType:1	 /* start bit 14 */;
/* off 0x0000 */	unsigned __int64	Reserved:49	 /* start bit 15 */;
};
/* off 0x0000 */	unsigned __int64	ValidBits;
};
union _WHEA_ERROR_STATUS /* sizeof 00000008 8 */
{
/* off 0x0000 */	unsigned __int64	ErrorStatus;
struct
{
/* off 0x0000 */	unsigned __int64	Reserved1:8	 /* start bit 0 */;
/* off 0x0000 */	unsigned __int64	ErrorType:8	 /* start bit 8 */;
/* off 0x0000 */	unsigned __int64	Address:1	 /* start bit 16 */;
/* off 0x0000 */	unsigned __int64	Control:1	 /* start bit 17 */;
/* off 0x0000 */	unsigned __int64	Data:1	 /* start bit 18 */;
/* off 0x0000 */	unsigned __int64	Responder:1	 /* start bit 19 */;
/* off 0x0000 */	unsigned __int64	Requester:1	 /* start bit 20 */;
/* off 0x0000 */	unsigned __int64	FirstError:1	 /* start bit 21 */;
/* off 0x0000 */	unsigned __int64	Overflow:1	 /* start bit 22 */;
/* off 0x0000 */	unsigned __int64	Reserved2:41	 /* start bit 23 */;
};
};
struct _WHEA_MEMORY_ERROR /* sizeof 00000049 73 */
{
/* off 0x0000 */	union _WHEA_MEMORY_ERROR_VALIDBITS	ValidBits;
/* off 0x0008 */	union _WHEA_ERROR_STATUS	ErrorStatus;
/* off 0x0010 */	unsigned __int64	PhysicalAddress;
/* off 0x0018 */	unsigned __int64	PhysicalAddressMask;
/* off 0x0020 */	unsigned short	Node;
/* off 0x0022 */	unsigned short	Card;
/* off 0x0024 */	unsigned short	Module;
/* off 0x0026 */	unsigned short	Bank;
/* off 0x0028 */	unsigned short	Device;
/* off 0x002a */	unsigned short	Row;
/* off 0x002c */	unsigned short	Column;
/* off 0x002e */	unsigned short	BitPosition;
/* off 0x0030 */	unsigned __int64	RequesterId;
/* off 0x0038 */	unsigned __int64	ResponderId;
/* off 0x0040 */	unsigned __int64	TargetId;
/* off 0x0048 */	unsigned char	ErrorType;
};
union _WHEA_NMI_ERROR_FLAGS /* sizeof 00000004 4 */
{
struct
{
/* off 0x0000 */	unsigned long	HypervisorError:1	 /* start bit 0 */;
/* off 0x0000 */	unsigned long	Reserved:31	 /* start bit 1 */;
};
/* off 0x0000 */	unsigned long	AsULONG;
};
struct _WHEA_NMI_ERROR /* sizeof 0000000c 12 */
{
/* off 0x0000 */	unsigned char Data[8];
/* off 0x0008 */	union _WHEA_NMI_ERROR_FLAGS	Flags;
};
union _WHEA_PCIEXPRESS_ERROR_VALIDBITS /* sizeof 00000008 8 */
{
struct
{
/* off 0x0000 */	unsigned __int64	PortType:1	 /* start bit 0 */;
/* off 0x0000 */	unsigned __int64	Version:1	 /* start bit 1 */;
/* off 0x0000 */	unsigned __int64	CommandStatus:1	 /* start bit 2 */;
/* off 0x0000 */	unsigned __int64	DeviceId:1	 /* start bit 3 */;
/* off 0x0000 */	unsigned __int64	DeviceSerialNumber:1	 /* start bit 4 */;
/* off 0x0000 */	unsigned __int64	BridgeControlStatus:1	 /* start bit 5 */;
/* off 0x0000 */	unsigned __int64	ExpressCapability:1	 /* start bit 6 */;
/* off 0x0000 */	unsigned __int64	AerInfo:1	 /* start bit 7 */;
/* off 0x0000 */	unsigned __int64	Reserved:56	 /* start bit 8 */;
};
/* off 0x0000 */	unsigned __int64	ValidBits;
};
union _WHEA_PCIEXPRESS_VERSION /* sizeof 00000004 4 */
{
struct
{
/* off 0x0000 */	unsigned char	MinorVersion;
/* off 0x0001 */	unsigned char	MajorVersion;
/* off 0x0002 */	unsigned short	Reserved;
};
/* off 0x0000 */	unsigned long	AsULONG;
};
union _WHEA_PCIEXPRESS_COMMAND_STATUS /* sizeof 00000004 4 */
{
struct
{
/* off 0x0000 */	unsigned short	Command;
/* off 0x0002 */	unsigned short	Status;
};
/* off 0x0000 */	unsigned long	AsULONG;
};
struct _WHEA_PCIEXPRESS_DEVICE_ID /* sizeof 00000010 16 */
{
/* off 0x0000 */	unsigned short	VendorID;
/* off 0x0002 */	unsigned short	DeviceID;
/* off 0x0004 */	unsigned long	ClassCode:24	 /* start bit 0 */;
/* off 0x0004 */	unsigned long	FunctionNumber:8	 /* start bit 24 */;
/* off 0x0008 */	unsigned long	DeviceNumber:8	 /* start bit 0 */;
/* off 0x0008 */	unsigned long	Segment:16	 /* start bit 8 */;
/* off 0x0008 */	unsigned long	PrimaryBusNumber:8	 /* start bit 24 */;
/* off 0x000c */	unsigned long	SecondaryBusNumber:8	 /* start bit 0 */;
/* off 0x000c */	unsigned long	Reserved1:2	 /* start bit 8 */;
/* off 0x000c */	unsigned long	SlotNumber:14	 /* start bit 10 */;
/* off 0x000c */	unsigned long	Reserved2:8	 /* start bit 24 */;
};
union _WHEA_PCIEXPRESS_BRIDGE_CONTROL_STATUS /* sizeof 00000004 4 */
{
struct
{
/* off 0x0000 */	unsigned short	BridgeSecondaryStatus;
/* off 0x0002 */	unsigned short	BridgeControl;
};
/* off 0x0000 */	unsigned long	AsULONG;
};
struct _WHEA_PCIEXPRESS_ERROR /* sizeof 000000d0 208 */
{
/* off 0x0000 */	union _WHEA_PCIEXPRESS_ERROR_VALIDBITS	ValidBits;
/* off 0x0008 */	enum WHEA_PCIEXPRESS_DEVICE_TYPE	PortType;
/* off 0x000c */	union _WHEA_PCIEXPRESS_VERSION	Version;
/* off 0x0010 */	union _WHEA_PCIEXPRESS_COMMAND_STATUS	CommandStatus;
/* off 0x0014 */	unsigned long	Reserved;
/* off 0x0018 */	struct _WHEA_PCIEXPRESS_DEVICE_ID	DeviceId;
/* off 0x0028 */	unsigned __int64	DeviceSerialNumber;
/* off 0x0030 */	union _WHEA_PCIEXPRESS_BRIDGE_CONTROL_STATUS	BridgeControlStatus;
/* off 0x0034 */	unsigned char ExpressCapability[60];
/* off 0x0070 */	unsigned char AerInfo[96];
};
union _WHEA_PCIXBUS_ERROR_VALIDBITS /* sizeof 00000008 8 */
{
struct
{
/* off 0x0000 */	unsigned __int64	ErrorStatus:1	 /* start bit 0 */;
/* off 0x0000 */	unsigned __int64	ErrorType:1	 /* start bit 1 */;
/* off 0x0000 */	unsigned __int64	BusId:1	 /* start bit 2 */;
/* off 0x0000 */	unsigned __int64	BusAddress:1	 /* start bit 3 */;
/* off 0x0000 */	unsigned __int64	BusData:1	 /* start bit 4 */;
/* off 0x0000 */	unsigned __int64	BusCommand:1	 /* start bit 5 */;
/* off 0x0000 */	unsigned __int64	RequesterId:1	 /* start bit 6 */;
/* off 0x0000 */	unsigned __int64	CompleterId:1	 /* start bit 7 */;
/* off 0x0000 */	unsigned __int64	TargetId:1	 /* start bit 8 */;
/* off 0x0000 */	unsigned __int64	Reserved:55	 /* start bit 9 */;
};
/* off 0x0000 */	unsigned __int64	ValidBits;
};
union _WHEA_PCIXBUS_ID /* sizeof 00000002 2 */
{
struct
{
/* off 0x0000 */	unsigned char	BusNumber;
/* off 0x0001 */	unsigned char	BusSegment;
};
/* off 0x0000 */	unsigned short	AsUSHORT;
};
union _WHEA_PCIXBUS_COMMAND /* sizeof 00000008 8 */
{
struct
{
/* off 0x0000 */	unsigned __int64	Command:56	 /* start bit 0 */;
/* off 0x0000 */	unsigned __int64	PCIXCommand:1	 /* start bit 56 */;
/* off 0x0000 */	unsigned __int64	Reserved:7	 /* start bit 57 */;
};
/* off 0x0000 */	unsigned __int64	AsULONGLONG;
};
struct _WHEA_PCIXBUS_ERROR /* sizeof 00000048 72 */
{
/* off 0x0000 */	union _WHEA_PCIXBUS_ERROR_VALIDBITS	ValidBits;
/* off 0x0008 */	union _WHEA_ERROR_STATUS	ErrorStatus;
/* off 0x0010 */	unsigned short	ErrorType;
/* off 0x0012 */	union _WHEA_PCIXBUS_ID	BusId;
/* off 0x0014 */	unsigned long	Reserved;
/* off 0x0018 */	unsigned __int64	BusAddress;
/* off 0x0020 */	unsigned __int64	BusData;
/* off 0x0028 */	union _WHEA_PCIXBUS_COMMAND	BusCommand;
/* off 0x0030 */	unsigned __int64	RequesterId;
/* off 0x0038 */	unsigned __int64	CompleterId;
/* off 0x0040 */	unsigned __int64	TargetId;
};
union _WHEA_PCIXDEVICE_ERROR_VALIDBITS /* sizeof 00000008 8 */
{
struct
{
/* off 0x0000 */	unsigned __int64	ErrorStatus:1	 /* start bit 0 */;
/* off 0x0000 */	unsigned __int64	IdInfo:1	 /* start bit 1 */;
/* off 0x0000 */	unsigned __int64	MemoryNumber:1	 /* start bit 2 */;
/* off 0x0000 */	unsigned __int64	IoNumber:1	 /* start bit 3 */;
/* off 0x0000 */	unsigned __int64	RegisterDataPairs:1	 /* start bit 4 */;
/* off 0x0000 */	unsigned __int64	Reserved:59	 /* start bit 5 */;
};
/* off 0x0000 */	unsigned __int64	ValidBits;
};
struct _WHEA_PCIXDEVICE_ID /* sizeof 00000010 16 */
{
/* off 0x0000 */	unsigned short	VendorId;
/* off 0x0002 */	unsigned short	DeviceId;
/* off 0x0004 */	unsigned long	ClassCode:24	 /* start bit 0 */;
/* off 0x0004 */	unsigned long	FunctionNumber:8	 /* start bit 24 */;
/* off 0x0008 */	unsigned long	DeviceNumber:8	 /* start bit 0 */;
/* off 0x0008 */	unsigned long	BusNumber:8	 /* start bit 8 */;
/* off 0x0008 */	unsigned long	SegmentNumber:8	 /* start bit 16 */;
/* off 0x0008 */	unsigned long	Reserved1:8	 /* start bit 24 */;
/* off 0x000c */	unsigned long	Reserved2;
};
struct WHEA_PCIXDEVICE_REGISTER_PAIR /* sizeof 00000010 16 */
{
/* off 0x0000 */	unsigned __int64	Register;
/* off 0x0008 */	unsigned __int64	Data;
};
struct _WHEA_PCIXDEVICE_ERROR /* sizeof 00000068 104 */
{
/* off 0x0000 */	union _WHEA_PCIXDEVICE_ERROR_VALIDBITS	ValidBits;
/* off 0x0008 */	union _WHEA_ERROR_STATUS	ErrorStatus;
/* off 0x0010 */	struct _WHEA_PCIXDEVICE_ID	IdInfo;
/* off 0x0020 */	unsigned long	MemoryNumber;
/* off 0x0024 */	unsigned long	IoNumber;
/* off 0x0028 */	struct WHEA_PCIXDEVICE_REGISTER_PAIR RegisterDataPairs[4];
};
struct _WHEA_ERROR_PACKET /* sizeof 00000119 281 */
{
/* off 0x0000 */	unsigned long	Signature;
/* off 0x0004 */	union _WHEA_ERROR_PACKET_FLAGS	Flags;
/* off 0x0008 */	unsigned long	Size;
/* off 0x000c */	unsigned long	RawDataLength;
/* off 0x0010 */	unsigned __int64	Reserved1;
/* off 0x0018 */	unsigned __int64	Context;
/* off 0x0020 */	enum _WHEA_ERROR_TYPE	ErrorType;
/* off 0x0024 */	enum _WHEA_ERROR_SEVERITY	ErrorSeverity;
/* off 0x0028 */	unsigned long	ErrorSourceId;
/* off 0x002c */	enum _WHEA_ERROR_SOURCE_TYPE	ErrorSourceType;
/* off 0x0030 */	unsigned long	Reserved2;
/* off 0x0034 */	unsigned long	Version;
/* off 0x0038 */	unsigned __int64	Cpu;
/* off 0x0040 */	
	union  /* sizeof 000000d0 208 */
	{
	/* off 0x0000 */	struct _WHEA_GENERIC_PROCESSOR_ERROR	ProcessorError;
	/* off 0x0000 */	struct _WHEA_MEMORY_ERROR	MemoryError;
	/* off 0x0000 */	struct _WHEA_NMI_ERROR	NmiError;
	/* off 0x0000 */	struct _WHEA_PCIEXPRESS_ERROR	PciExpressError;
	/* off 0x0000 */	struct _WHEA_PCIXBUS_ERROR	PciXBusError;
	/* off 0x0000 */	struct _WHEA_PCIXDEVICE_ERROR	PciXDeviceError;
	}	u;
/* off 0x0110 */	enum _WHEA_RAW_DATA_FORMAT	RawDataFormat;
/* off 0x0114 */	unsigned long	RawDataOffset;
/* off 0x0118 */	unsigned char RawData[1];
};
enum _WHEA_ERROR_TYPE
{
	WheaErrTypeProcessor	=0x00000000	,//0
	WheaErrTypeMemory	=0x00000001	,//0
	WheaErrTypePCIExpress	=0x00000002	,//0
	WheaErrTypeNMI	=0x00000003	,//0
	WheaErrTypePCIXBus	=0x00000004	,//0
	WheaErrTypePCIXDevice	=0x00000005	,//0
	WheaErrTypeGeneric	=0x00000006	,//0
};
enum _WHEA_ERROR_SOURCE_TYPE
{
	WheaErrSrcTypeMCE	=0x00000000	,//0
	WheaErrSrcTypeCMC	=0x00000001	,//0
	WheaErrSrcTypeCPE	=0x00000002	,//0
	WheaErrSrcTypeNMI	=0x00000003	,//0
	WheaErrSrcTypePCIe	=0x00000004	,//0
	WheaErrSrcTypeGeneric	=0x00000005	,//0
	WheaErrSrcTypeINIT	=0x00000006	,//0
	WheaErrSrcTypeBOOT	=0x00000007	,//0
	WheaErrSrcTypeSCIGeneric	=0x00000008	,//0
	WheaErrSrcTypeIPFMCA	=0x00000009	,//0
	WheaErrSrcTypeIPFCMC	=0x0000000a	,//0
	WheaErrSrcTypeIPFCPE	=0x0000000b	,//0
	WheaErrSrcTypeMax	=0x0000000c	,//0
};
enum WHEA_PCIEXPRESS_DEVICE_TYPE
{
	WheaPciExpressEndpoint	=0x00000000	,//0
	WheaPciExpressLegacyEndpoint	=0x00000001	,//0
	WheaPciExpressRootPort	=0x00000004	,//0
	WheaPciExpressUpstreamSwitchPort	=0x00000005	,//0
	WheaPciExpressDownstreamSwitchPort	=0x00000006	,//0
	WheaPciExpressToPciXBridge	=0x00000007	,//0
	WheaPciXToExpressBridge	=0x00000008	,//0
	WheaPciExpressRootComplexIntegratedEndpoint	=0x00000009	,//0
	WheaPciExpressRootComplexEventCollector	=0x0000000a	,//0
};
enum _WHEA_RAW_DATA_FORMAT
{
	WheaRawDataFormatIPFSalRecord	=0x00000000	,//0
	WheaRawDataFormatIA32MCA	=0x00000001	,//0
	WheaRawDataFormatIntel64MCA	=0x00000002	,//0
	WheaRawDataFormatAMD64MCA	=0x00000003	,//0
	WheaRawDataFormatMemory	=0x00000004	,//0
	WheaRawDataFormatPCIExpress	=0x00000005	,//0
	WheaRawDataFormatNMIPort	=0x00000006	,//0
	WheaRawDataFormatPCIXBus	=0x00000007	,//0
	WheaRawDataFormatPCIXDevice	=0x00000008	,//0
	WheaRawDataFormatGeneric	=0x00000009	,//0
	WheaRawDataFormatMax	=0x0000000a	,//0
};
struct _iobuf /* sizeof 00000020 32 */
{
/* off 0x0000 */	char*	_ptr;
/* off 0x0004 */	int	_cnt;
/* off 0x0008 */	char*	_base;
/* off 0x000c */	int	_flag;
/* off 0x0010 */	int	_file;
/* off 0x0014 */	int	_charbuf;
/* off 0x0018 */	int	_bufsiz;
/* off 0x001c */	char*	_tmpfname;
};
struct _MMPTE_HARDWARE /* sizeof 00000004 4 */
{
/* off 0x0000 */	unsigned long	Valid:1	 /* start bit 0 */;
/* off 0x0000 */	unsigned long	Dirty1:1	 /* start bit 1 */;
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
/* off 0x0000 */	unsigned long	ProtoAddressLow:8	 /* start bit 1 */;
/* off 0x0000 */	unsigned long	ReadOnly:1	 /* start bit 9 */;
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
struct _MMPTE_TIMESTAMP /* sizeof 00000004 4 */
{
/* off 0x0000 */	unsigned long	MustBeZero:1	 /* start bit 0 */;
/* off 0x0000 */	unsigned long	PageFileLow:4	 /* start bit 1 */;
/* off 0x0000 */	unsigned long	Protection:5	 /* start bit 5 */;
/* off 0x0000 */	unsigned long	Prototype:1	 /* start bit 10 */;
/* off 0x0000 */	unsigned long	Transition:1	 /* start bit 11 */;
/* off 0x0000 */	unsigned long	GlobalTimeStamp:20	 /* start bit 12 */;
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
/* off 0x0000 */	unsigned long	SubsectionAddressLow:9	 /* start bit 1 */;
/* off 0x0000 */	unsigned long	Prototype:1	 /* start bit 10 */;
/* off 0x0000 */	unsigned long	SubsectionAddressHigh:21	 /* start bit 11 */;
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
struct _MMPTE /* sizeof 00000004 4 */
{
/* off 0x0000 */	
	union  /* sizeof 00000004 4 */
	{
	/* off 0x0000 */	unsigned long	Long;
	/* off 0x0000 */	unsigned long	VolatileLong;
	/* off 0x0000 */	struct _HARDWARE_PTE	Flush;
	/* off 0x0000 */	struct _MMPTE_HARDWARE	Hard;
	/* off 0x0000 */	struct _MMPTE_PROTOTYPE	Proto;
	/* off 0x0000 */	struct _MMPTE_SOFTWARE	Soft;
	/* off 0x0000 */	struct _MMPTE_TIMESTAMP	TimeStamp;
	/* off 0x0000 */	struct _MMPTE_TRANSITION	Trans;
	/* off 0x0000 */	struct _MMPTE_SUBSECTION	Subsect;
	/* off 0x0000 */	struct _MMPTE_LIST	List;
	}	u;
};
struct _I386_LOADER_BLOCK /* sizeof 0000000c 12 */
{
/* off 0x0000 */	void*	CommonDataArea;
/* off 0x0004 */	unsigned long	MachineType;
/* off 0x0008 */	unsigned long	VirtualBias;
};
struct _ALPHA_LOADER_BLOCK /* sizeof 00000004 4 */
{
/* off 0x0000 */	unsigned long	PlaceHolder;
};
struct _IA64_LOADER_BLOCK /* sizeof 00000004 4 */
{
/* off 0x0000 */	unsigned long	PlaceHolder;
};
struct _EFI_FIRMWARE_INFORMATION /* sizeof 00000010 16 */
{
/* off 0x0000 */	unsigned long	FirmwareVersion;
/* off 0x0004 */	struct _VIRTUAL_EFI_RUNTIME_SERVICES*	VirtualEfiRuntimeServices;
/* off 0x0008 */	long	SetVirtualAddressMapStatus;
/* off 0x000c */	unsigned long	MissedMappingsCount;
};
struct _PCAT_FIRMWARE_INFORMATION /* sizeof 00000004 4 */
{
/* off 0x0000 */	unsigned long	PlaceHolder;
};
struct _FIRMWARE_INFORMATION_LOADER_BLOCK /* sizeof 00000014 20 */
{
/* off 0x0000 */	unsigned long	FirmwareTypeEfi:1	 /* start bit 0 */;
/* off 0x0000 */	unsigned long	Reserved:31	 /* start bit 1 */;
/* off 0x0004 */	
	union  /* sizeof 00000010 16 */
	{
	/* off 0x0000 */	struct _EFI_FIRMWARE_INFORMATION	EfiInformation;
	/* off 0x0000 */	struct _PCAT_FIRMWARE_INFORMATION	PcatInformation;
	}	u;
};
struct _LOADER_PARAMETER_BLOCK /* sizeof 0000007c 124 */
{
/* off 0x0000 */	struct _LIST_ENTRY	LoadOrderListHead;
/* off 0x0008 */	struct _LIST_ENTRY	MemoryDescriptorListHead;
/* off 0x0010 */	struct _LIST_ENTRY	BootDriverListHead;
/* off 0x0018 */	unsigned long	KernelStack;
/* off 0x001c */	unsigned long	Prcb;
/* off 0x0020 */	unsigned long	Process;
/* off 0x0024 */	unsigned long	Thread;
/* off 0x0028 */	unsigned long	RegistryLength;
/* off 0x002c */	void*	RegistryBase;
/* off 0x0030 */	struct _CONFIGURATION_COMPONENT_DATA*	ConfigurationRoot;
/* off 0x0034 */	char*	ArcBootDeviceName;
/* off 0x0038 */	char*	ArcHalDeviceName;
/* off 0x003c */	char*	NtBootPathName;
/* off 0x0040 */	char*	NtHalPathName;
/* off 0x0044 */	char*	LoadOptions;
/* off 0x0048 */	struct _NLS_DATA_BLOCK*	NlsData;
/* off 0x004c */	struct _ARC_DISK_INFORMATION*	ArcDiskInformation;
/* off 0x0050 */	void*	OemFontFile;
/* off 0x0054 */	struct _SETUP_LOADER_BLOCK*	SetupLoaderBlock;
/* off 0x0058 */	struct _LOADER_PARAMETER_EXTENSION*	Extension;
/* off 0x005c */	
	union  /* sizeof 0000000c 12 */
	{
	/* off 0x0000 */	struct _I386_LOADER_BLOCK	I386;
	/* off 0x0000 */	struct _ALPHA_LOADER_BLOCK	Alpha;
	/* off 0x0000 */	struct _IA64_LOADER_BLOCK	Ia64;
	}	u;
/* off 0x0068 */	struct _FIRMWARE_INFORMATION_LOADER_BLOCK	FirmwareInformation;
};
struct _DEVICE_FLAGS /* sizeof 00000004 4 */
{
/* off 0x0000 */	unsigned long	Failed:1	 /* start bit 0 */;
/* off 0x0000 */	unsigned long	ReadOnly:1	 /* start bit 1 */;
/* off 0x0000 */	unsigned long	Removable:1	 /* start bit 2 */;
/* off 0x0000 */	unsigned long	ConsoleIn:1	 /* start bit 3 */;
/* off 0x0000 */	unsigned long	ConsoleOut:1	 /* start bit 4 */;
/* off 0x0000 */	unsigned long	Input:1	 /* start bit 5 */;
/* off 0x0000 */	unsigned long	Output:1	 /* start bit 6 */;
};
struct _CONFIGURATION_COMPONENT /* sizeof 00000024 36 */
{
/* off 0x0000 */	enum _CONFIGURATION_CLASS	Class;
/* off 0x0004 */	enum _CONFIGURATION_TYPE	Type;
/* off 0x0008 */	struct _DEVICE_FLAGS	Flags;
/* off 0x000c */	unsigned short	Version;
/* off 0x000e */	unsigned short	Revision;
/* off 0x0010 */	unsigned long	Key;
/* off 0x0014 */	unsigned long	AffinityMask;
/* off 0x0018 */	unsigned long	ConfigurationDataLength;
/* off 0x001c */	unsigned long	IdentifierLength;
/* off 0x0020 */	char*	Identifier;
};
struct _CONFIGURATION_COMPONENT_DATA /* sizeof 00000034 52 */
{
/* off 0x0000 */	struct _CONFIGURATION_COMPONENT_DATA*	Parent;
/* off 0x0004 */	struct _CONFIGURATION_COMPONENT_DATA*	Child;
/* off 0x0008 */	struct _CONFIGURATION_COMPONENT_DATA*	Sibling;
/* off 0x000c */	struct _CONFIGURATION_COMPONENT	ComponentEntry;
/* off 0x0030 */	void*	ConfigurationData;
};
enum _CONFIGURATION_CLASS
{
	SystemClass	=0x00000000	,//0
	ProcessorClass	=0x00000001	,//0
	CacheClass	=0x00000002	,//0
	AdapterClass	=0x00000003	,//0
	ControllerClass	=0x00000004	,//0
	PeripheralClass	=0x00000005	,//0
	MemoryClass	=0x00000006	,//0
	MaximumClass	=0x00000007	,//0
};
enum _CONFIGURATION_TYPE
{
	ArcSystem	=0x00000000	,//0
	CentralProcessor	=0x00000001	,//0
	FloatingPointProcessor	=0x00000002	,//0
	PrimaryIcache	=0x00000003	,//0
	PrimaryDcache	=0x00000004	,//0
	SecondaryIcache	=0x00000005	,//0
	SecondaryDcache	=0x00000006	,//0
	SecondaryCache	=0x00000007	,//0
	EisaAdapter	=0x00000008	,//0
	TcAdapter	=0x00000009	,//0
	ScsiAdapter	=0x0000000a	,//0
	DtiAdapter	=0x0000000b	,//0
	MultiFunctionAdapter	=0x0000000c	,//0
	DiskController	=0x0000000d	,//0
	TapeController	=0x0000000e	,//0
	CdromController	=0x0000000f	,//0
	WormController	=0x00000010	,//0
	SerialController	=0x00000011	,//0
	NetworkController	=0x00000012	,//0
	DisplayController	=0x00000013	,//0
	ParallelController	=0x00000014	,//0
	PointerController	=0x00000015	,//0
	KeyboardController	=0x00000016	,//0
	AudioController	=0x00000017	,//0
	OtherController	=0x00000018	,//0
	DiskPeripheral	=0x00000019	,//0
	FloppyDiskPeripheral	=0x0000001a	,//0
	TapePeripheral	=0x0000001b	,//0
	ModemPeripheral	=0x0000001c	,//0
	MonitorPeripheral	=0x0000001d	,//0
	PrinterPeripheral	=0x0000001e	,//0
	PointerPeripheral	=0x0000001f	,//0
	KeyboardPeripheral	=0x00000020	,//0
	TerminalPeripheral	=0x00000021	,//0
	OtherPeripheral	=0x00000022	,//0
	LinePeripheral	=0x00000023	,//0
	NetworkPeripheral	=0x00000024	,//0
	SystemMemory	=0x00000025	,//0
	DockingInformation	=0x00000026	,//0
	RealModeIrqRoutingTable	=0x00000027	,//0
	RealModePCIEnumeration	=0x00000028	,//0
	MaximumType	=0x00000029	,//0
};
struct _NLS_DATA_BLOCK /* sizeof 0000000c 12 */
{
/* off 0x0000 */	void*	AnsiCodePageData;
/* off 0x0004 */	void*	OemCodePageData;
/* off 0x0008 */	void*	UnicodeCaseTableData;
};
struct _ARC_DISK_INFORMATION /* sizeof 00000008 8 */
{
/* off 0x0000 */	struct _LIST_ENTRY	DiskSignatures;
};
struct _SETUP_LOADER_BLOCK /* sizeof 00000000 0 */
{
};
struct _PROFILE_PARAMETER_BLOCK /* sizeof 00000010 16 */
{
/* off 0x0000 */	unsigned short	Status;
/* off 0x0002 */	unsigned short	Reserved;
/* off 0x0004 */	unsigned short	DockingState;
/* off 0x0006 */	unsigned short	Capabilities;
/* off 0x0008 */	unsigned long	DockID;
/* off 0x000c */	unsigned long	SerialNumber;
};
struct _LOADER_PARAMETER_EXTENSION /* sizeof 00000084 132 */
{
/* off 0x0000 */	unsigned long	Size;
/* off 0x0004 */	struct _PROFILE_PARAMETER_BLOCK	Profile;
/* off 0x0014 */	unsigned long	MajorVersion;
/* off 0x0018 */	unsigned long	MinorVersion;
/* off 0x001c */	void*	EmInfFileImage;
/* off 0x0020 */	unsigned long	EmInfFileSize;
/* off 0x0024 */	void*	TriageDumpBlock;
/* off 0x0028 */	unsigned long	LoaderPagesSpanned;
/* off 0x002c */	struct _HEADLESS_LOADER_BLOCK*	HeadlessLoaderBlock;
/* off 0x0030 */	struct _SMBIOS_TABLE_HEADER*	SMBiosEPSHeader;
/* off 0x0034 */	void*	DrvDBImage;
/* off 0x0038 */	unsigned long	DrvDBSize;
/* off 0x003c */	struct _NETWORK_LOADER_BLOCK*	NetworkLoaderBlock;
/* off 0x0040 */	unsigned char*	HalpIRQLToTPR;
/* off 0x0044 */	unsigned char*	HalpVectorToIRQL;
/* off 0x0048 */	struct _LIST_ENTRY	FirmwareDescriptorListHead;
/* off 0x0050 */	void*	AcpiTable;
/* off 0x0054 */	unsigned long	AcpiTableSize;
/* off 0x0058 */	unsigned long	BootViaWinload:1	 /* start bit 0 */;
/* off 0x0058 */	unsigned long	Reserved:31	 /* start bit 1 */;
/* off 0x005c */	struct _LOADER_PERFORMANCE_DATA*	LoaderPerformanceData;
/* off 0x0060 */	struct _LIST_ENTRY	BootApplicationPersistentData;
/* off 0x0068 */	void*	WmdTestResult;
/* off 0x006c */	struct _GUID	BootIdentifier;
/* off 0x007c */	unsigned long	ResumePages;
/* off 0x0080 */	void*	DumpHeader;
};
struct _HEADLESS_LOADER_BLOCK /* sizeof 00000034 52 */
{
/* off 0x0000 */	unsigned char	UsedBiosSettings;
/* off 0x0001 */	unsigned char	DataBits;
/* off 0x0002 */	unsigned char	StopBits;
/* off 0x0003 */	unsigned char	Parity;
/* off 0x0004 */	unsigned long	BaudRate;
/* off 0x0008 */	unsigned long	PortNumber;
/* off 0x000c */	unsigned char*	PortAddress;
/* off 0x0010 */	unsigned short	PciDeviceId;
/* off 0x0012 */	unsigned short	PciVendorId;
/* off 0x0014 */	unsigned char	PciBusNumber;
/* off 0x0016 */	unsigned short	PciBusSegment;
/* off 0x0018 */	unsigned char	PciSlotNumber;
/* off 0x0019 */	unsigned char	PciFunctionNumber;
/* off 0x001c */	unsigned long	PciFlags;
/* off 0x0020 */	struct _GUID	SystemGUID;
/* off 0x0030 */	unsigned char	IsMMIODevice;
/* off 0x0031 */	unsigned char	TerminalType;
};
struct _SMBIOS_TABLE_HEADER /* sizeof 00000000 0 */
{
};
struct _NETWORK_LOADER_BLOCK /* sizeof 00000010 16 */
{
/* off 0x0000 */	unsigned char*	DHCPServerACK;
/* off 0x0004 */	unsigned long	DHCPServerACKLength;
/* off 0x0008 */	unsigned char*	BootServerReplyPacket;
/* off 0x000c */	unsigned long	BootServerReplyPacketLength;
};
struct _LOADER_PERFORMANCE_DATA /* sizeof 00000010 16 */
{
/* off 0x0000 */	unsigned __int64	StartTime;
/* off 0x0008 */	unsigned __int64	EndTime;
};
struct _VIRTUAL_EFI_RUNTIME_SERVICES /* sizeof 00000038 56 */
{
/* off 0x0000 */	unsigned long	GetTime;
/* off 0x0004 */	unsigned long	SetTime;
/* off 0x0008 */	unsigned long	GetWakeupTime;
/* off 0x000c */	unsigned long	SetWakeupTime;
/* off 0x0010 */	unsigned long	SetVirtualAddressMap;
/* off 0x0014 */	unsigned long	ConvertPointer;
/* off 0x0018 */	unsigned long	GetVariable;
/* off 0x001c */	unsigned long	GetNextVariableName;
/* off 0x0020 */	unsigned long	SetVariable;
/* off 0x0024 */	unsigned long	GetNextHighMonotonicCount;
/* off 0x0028 */	unsigned long	ResetSystem;
/* off 0x002c */	unsigned long	UpdateCapsule;
/* off 0x0030 */	unsigned long	QueryCapsuleCapabilities;
/* off 0x0034 */	unsigned long	QueryVariableInfo;
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
struct _MMPTE_FLUSH_LIST /* sizeof 0000008c 140 */
{
/* off 0x0000 */	unsigned long	Count;
/* off 0x0004 */	unsigned long	MaximumCount;
/* off 0x0008 */	void* FlushVa[33];
};
struct _MI_COLOR_BASE /* sizeof 00000008 8 */
{
/* off 0x0000 */	unsigned short*	ColorPointer;
/* off 0x0004 */	unsigned short	ColorMask;
/* off 0x0006 */	unsigned short	ColorNode;
};
struct _MMPFNENTRY /* sizeof 00000002 2 */
{
/* off 0x0000 */	unsigned char	PageLocation:3	 /* start bit 0 */;
/* off 0x0000 */	unsigned char	WriteInProgress:1	 /* start bit 3 */;
/* off 0x0000 */	unsigned char	Modified:1	 /* start bit 4 */;
/* off 0x0000 */	unsigned char	ReadInProgress:1	 /* start bit 5 */;
/* off 0x0000 */	unsigned char	CacheAttribute:2	 /* start bit 6 */;
/* off 0x0001 */	unsigned char	Priority:3	 /* start bit 0 */;
/* off 0x0001 */	unsigned char	Rom:1	 /* start bit 3 */;
/* off 0x0001 */	unsigned char	InPageError:1	 /* start bit 4 */;
/* off 0x0001 */	unsigned char	KernelStack:1	 /* start bit 5 */;
/* off 0x0001 */	unsigned char	RemovalRequested:1	 /* start bit 6 */;
/* off 0x0001 */	unsigned char	ParityError:1	 /* start bit 7 */;
};
struct _MMPFN /* sizeof 00000018 24 */
{
/* off 0x0000 */	
	union  /* sizeof 00000004 4 */
	{
	/* off 0x0000 */	unsigned long	Flink;
	/* off 0x0000 */	unsigned long	WsIndex;
	/* off 0x0000 */	struct _KEVENT*	Event;
	/* off 0x0000 */	void*	Next;
	/* off 0x0000 */	void*	VolatileNext;
	/* off 0x0000 */	struct _KTHREAD*	KernelStackOwner;
	/* off 0x0000 */	struct _SINGLE_LIST_ENTRY	NextStackPfn;
	}	u1;
/* off 0x0004 */	
	union  /* sizeof 00000004 4 */
	{
	/* off 0x0000 */	unsigned long	Blink;
	/* off 0x0000 */	struct _MMPTE*	ImageProtoPte;
	/* off 0x0000 */	unsigned long	ShareCount;
	}	u2;
union
{
/* off 0x0008 */	struct _MMPTE*	PteAddress;
/* off 0x0008 */	void*	VolatilePteAddress;
};
/* off 0x000c */	
	union  /* sizeof 00000004 4 */
	{
	struct
	{
	/* off 0x0000 */	unsigned short	ReferenceCount;
	/* off 0x0002 */	struct _MMPFNENTRY	e1;
	};
	/* off 0x0000 */	
		struct  /* sizeof 00000004 4 */
		{
		union
		{
		/* off 0x0000 */	unsigned short	ReferenceCount;
		/* off 0x0000 */	short	VolatileReferenceCount;
		};
		/* off 0x0002 */	unsigned short	ShortFlags;
		}	e2;
	/* off 0x0000 */	
		struct  /* sizeof 00000004 4 */
		{
		/* off 0x0000 */	unsigned short	ReferenceCount;
		/* off 0x0002 */	unsigned char	ByteFlags;
		/* off 0x0003 */	unsigned char	InterlockedByteFlags;
		}	e3;
	}	u3;
union
{
/* off 0x0010 */	struct _MMPTE	OriginalPte;
/* off 0x0010 */	long	AweReferenceCount;
};
/* off 0x0014 */	
	union  /* sizeof 00000004 4 */
	{
	/* off 0x0000 */	unsigned long	PteFrame:25	 /* start bit 0 */;
	/* off 0x0000 */	unsigned long	PfnImageVerified:1	 /* start bit 25 */;
	/* off 0x0000 */	unsigned long	AweAllocation:1	 /* start bit 26 */;
	/* off 0x0000 */	unsigned long	PrototypePte:1	 /* start bit 27 */;
	/* off 0x0000 */	unsigned long	PageColor:4	 /* start bit 28 */;
	}	u4;
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
/* off 0x0000 */	unsigned int	Rom:1	 /* start bit 9 */;
/* off 0x0000 */	unsigned int	PhysicalMemory:1	 /* start bit 10 */;
/* off 0x0000 */	unsigned int	CopyOnWrite:1	 /* start bit 11 */;
/* off 0x0000 */	unsigned int	Reserve:1	 /* start bit 12 */;
/* off 0x0000 */	unsigned int	Commit:1	 /* start bit 13 */;
/* off 0x0000 */	unsigned int	Accessed:1	 /* start bit 14 */;
/* off 0x0000 */	unsigned int	WasPurged:1	 /* start bit 15 */;
/* off 0x0000 */	unsigned int	UserReference:1	 /* start bit 16 */;
/* off 0x0000 */	unsigned int	GlobalMemory:1	 /* start bit 17 */;
/* off 0x0000 */	unsigned int	DeleteOnClose:1	 /* start bit 18 */;
/* off 0x0000 */	unsigned int	FilePointerNull:1	 /* start bit 19 */;
/* off 0x0000 */	unsigned int	GlobalOnlyPerSession:1	 /* start bit 20 */;
/* off 0x0000 */	unsigned int	SetMappedFileIoComplete:1	 /* start bit 21 */;
/* off 0x0000 */	unsigned int	CollidedFlush:1	 /* start bit 22 */;
/* off 0x0000 */	unsigned int	NoChange:1	 /* start bit 23 */;
/* off 0x0000 */	unsigned int	Spare:1	 /* start bit 24 */;
/* off 0x0000 */	unsigned int	UserWritable:1	 /* start bit 25 */;
/* off 0x0000 */	unsigned int	PreferredNode:6	 /* start bit 26 */;
};
struct _CONTROL_AREA /* sizeof 00000048 72 */
{
/* off 0x0000 */	struct _SEGMENT*	Segment;
/* off 0x0004 */	struct _LIST_ENTRY	DereferenceList;
/* off 0x000c */	unsigned long	NumberOfSectionReferences;
/* off 0x0010 */	unsigned long	NumberOfPfnReferences;
/* off 0x0014 */	unsigned long	NumberOfMappedViews;
/* off 0x0018 */	unsigned long	NumberOfUserReferences;
/* off 0x001c */	
	union  /* sizeof 00000004 4 */
	{
	/* off 0x0000 */	unsigned long	LongFlags;
	/* off 0x0000 */	struct _MMSECTION_FLAGS	Flags;
	}	u;
/* off 0x0020 */	
	union  /* sizeof 00000004 4 */
	{
	/* off 0x0000 */	
		struct  /* sizeof 00000004 4 */
		{
		/* off 0x0000 */	unsigned short	ModifiedWriteCount;
		/* off 0x0002 */	unsigned short	FlushInProgressCount;
		}	e2;
	}	u1;
/* off 0x0024 */	struct _EX_FAST_REF	FilePointer;
/* off 0x0028 */	long	ControlAreaLock;
/* off 0x002c */	unsigned long	StartingFrame;
/* off 0x0030 */	struct _MI_SECTION_CREATION_GATE*	WaitingForDeletion;
/* off 0x0034 */	
	union  /* sizeof 0000000c 12 */
	{
	/* off 0x0000 */	
		struct  /* sizeof 0000000c 12 */
		{
		union
		{
		/* off 0x0000 */	unsigned long	NumberOfSystemCacheViews;
		/* off 0x0000 */	unsigned long	ImageRelocationStartBit;
		};
		union
		{
		/* off 0x0004 */	long	WritableUserReferences;
		struct
		{
		/* off 0x0004 */	unsigned long	ImageRelocationSizeIn64k:16	 /* start bit 0 */;
		/* off 0x0004 */	unsigned long	Unused:14	 /* start bit 16 */;
		/* off 0x0004 */	unsigned long	BitMap64:1	 /* start bit 30 */;
		/* off 0x0004 */	unsigned long	ImageActive:1	 /* start bit 31 */;
		};
		};
		union
		{
		/* off 0x0008 */	struct _MM_SUBSECTION_AVL_TABLE*	SubsectionRoot;
		/* off 0x0008 */	struct _MI_IMAGE_SECURITY_REFERENCE*	SeImageStub;
		};
		}	e2;
	}	u2;
/* off 0x0040 */	__int64	LockedPages;
};
struct _SEGMENT_FLAGS /* sizeof 00000004 4 */
{
/* off 0x0000 */	unsigned long	TotalNumberOfPtes4132:10	 /* start bit 0 */;
/* off 0x0000 */	unsigned long	ExtraSharedWowSubsections:1	 /* start bit 10 */;
/* off 0x0000 */	unsigned long	LargePages:1	 /* start bit 11 */;
/* off 0x0000 */	unsigned long	WatchProto:1	 /* start bit 12 */;
/* off 0x0000 */	unsigned long	DebugSymbolsLoaded:1	 /* start bit 13 */;
/* off 0x0000 */	unsigned long	WriteCombined:1	 /* start bit 14 */;
/* off 0x0000 */	unsigned long	NoCache:1	 /* start bit 15 */;
/* off 0x0000 */	unsigned long	FloppyMedia:1	 /* start bit 16 */;
/* off 0x0000 */	unsigned long	DefaultProtectionMask:5	 /* start bit 17 */;
/* off 0x0000 */	unsigned long	ContainsPxeSubsection:1	 /* start bit 22 */;
/* off 0x0000 */	unsigned long	Binary32:1	 /* start bit 23 */;
/* off 0x0000 */	unsigned long	Spare:8	 /* start bit 24 */;
};
struct _SEGMENT /* sizeof 00000030 48 */
{
/* off 0x0000 */	struct _CONTROL_AREA*	ControlArea;
/* off 0x0004 */	unsigned long	TotalNumberOfPtes;
/* off 0x0008 */	struct _SEGMENT_FLAGS	SegmentFlags;
/* off 0x000c */	unsigned long	NumberOfCommittedPages;
/* off 0x0010 */	unsigned __int64	SizeOfSegment;
union
{
/* off 0x0018 */	struct _MMEXTEND_INFO*	ExtendInfo;
/* off 0x0018 */	void*	BasedAddress;
};
/* off 0x001c */	struct _EX_PUSH_LOCK	SegmentLock;
/* off 0x0020 */	
	union  /* sizeof 00000004 4 */
	{
	/* off 0x0000 */	unsigned long	ImageCommitment;
	/* off 0x0000 */	struct _EPROCESS*	CreatingProcess;
	}	u1;
/* off 0x0024 */	
	union  /* sizeof 00000004 4 */
	{
	/* off 0x0000 */	struct _MI_SECTION_IMAGE_INFORMATION*	ImageInformation;
	/* off 0x0000 */	void*	FirstMappedVa;
	}	u2;
/* off 0x0028 */	struct _MMPTE*	PrototypePte;
/* off 0x002c */	struct _MMPTE ThePtes[1];
};
struct _MMEXTEND_INFO /* sizeof 00000010 16 */
{
/* off 0x0000 */	unsigned __int64	CommittedSize;
/* off 0x0008 */	unsigned long	ReferenceCount;
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
union
{
/* off 0x0023 */	unsigned char	ImageFlags;
struct
{
/* off 0x0023 */	unsigned char	ComPlusNativeReady:1	 /* start bit 0 */;
/* off 0x0023 */	unsigned char	ComPlusILOnly:1	 /* start bit 1 */;
/* off 0x0023 */	unsigned char	ImageDynamicallyRelocated:1	 /* start bit 2 */;
/* off 0x0023 */	unsigned char	ImageMappedFlat:1	 /* start bit 3 */;
/* off 0x0023 */	unsigned char	Reserved:4	 /* start bit 4 */;
};
};
/* off 0x0024 */	unsigned long	LoaderFlags;
/* off 0x0028 */	unsigned long	ImageFileSize;
/* off 0x002c */	unsigned long	CheckSum;
};
struct _MI_EXTRA_IMAGE_INFORMATION /* sizeof 00000008 8 */
{
/* off 0x0000 */	unsigned long	SizeOfHeaders;
/* off 0x0004 */	void*	ImageMerge;
};
struct _MI_SECTION_IMAGE_INFORMATION /* sizeof 00000038 56 */
{
/* off 0x0000 */	struct _SECTION_IMAGE_INFORMATION	ExportedImageInformation;
/* off 0x0030 */	struct _MI_EXTRA_IMAGE_INFORMATION	InternalImageInformation;
};
struct _MI_SECTION_CREATION_GATE /* sizeof 00000014 20 */
{
/* off 0x0000 */	struct _MI_SECTION_CREATION_GATE*	Next;
/* off 0x0004 */	struct _KGATE	Gate;
};
struct _MMSUBSECTION_FLAGS /* sizeof 00000004 4 */
{
/* off 0x0000 */	unsigned short	SubsectionAccessed:1	 /* start bit 0 */;
/* off 0x0000 */	unsigned short	Protection:5	 /* start bit 1 */;
/* off 0x0000 */	unsigned short	StartingSector4132:10	 /* start bit 6 */;
/* off 0x0002 */	unsigned short	SubsectionStatic:1	 /* start bit 0 */;
/* off 0x0002 */	unsigned short	GlobalMemory:1	 /* start bit 1 */;
/* off 0x0002 */	unsigned short	DirtyPages:1	 /* start bit 2 */;
/* off 0x0002 */	unsigned short	Spare:1	 /* start bit 3 */;
/* off 0x0002 */	unsigned short	SectorEndOffset:12	 /* start bit 4 */;
};
struct _MMSUBSECTION_NODE /* sizeof 00000018 24 */
{
/* off 0x0000 */	
	union  /* sizeof 00000004 4 */
	{
	/* off 0x0000 */	unsigned long	LongFlags;
	/* off 0x0000 */	struct _MMSUBSECTION_FLAGS	SubsectionFlags;
	}	u;
/* off 0x0004 */	unsigned long	StartingSector;
/* off 0x0008 */	unsigned long	NumberOfFullSectors;
/* off 0x000c */	
	union  /* sizeof 00000004 4 */
	{
	/* off 0x0000 */	long	Balance:2	 /* start bit 0 */;
	/* off 0x0000 */	struct _MMSUBSECTION_NODE*	Parent;
	}	u1;
/* off 0x0010 */	struct _MMSUBSECTION_NODE*	LeftChild;
/* off 0x0014 */	struct _MMSUBSECTION_NODE*	RightChild;
};
struct _MM_SUBSECTION_AVL_TABLE /* sizeof 00000020 32 */
{
/* off 0x0000 */	struct _MMSUBSECTION_NODE	BalancedRoot;
/* off 0x0018 */	unsigned long	DepthOfTree:5	 /* start bit 0 */;
/* off 0x0018 */	unsigned long	Unused:3	 /* start bit 5 */;
/* off 0x0018 */	unsigned long	NumberGenericTableElements:24	 /* start bit 8 */;
/* off 0x001c */	void*	NodeHint;
};
struct _IMAGE_SECURITY_CONTEXT /* sizeof 00000004 4 */
{
union
{
/* off 0x0000 */	void*	PageHashes;
/* off 0x0000 */	unsigned long	Value;
struct
{
/* off 0x0000 */	unsigned long	SecurityBeingCreated:1	 /* start bit 0 */;
/* off 0x0000 */	unsigned long	SecurityMandatory:1	 /* start bit 1 */;
/* off 0x0000 */	unsigned long	Unused:1	 /* start bit 2 */;
/* off 0x0000 */	unsigned long	PageHashPointer:29	 /* start bit 3 */;
};
};
};
struct _MI_IMAGE_SECURITY_REFERENCE /* sizeof 0000000c 12 */
{
/* off 0x0000 */	struct _IMAGE_SECURITY_CONTEXT	SecurityContext;
/* off 0x0004 */	void*	DynamicRelocations;
/* off 0x0008 */	long	ReferenceCount;
};
struct _MMPAGING_FILE /* sizeof 00000050 80 */
{
/* off 0x0000 */	unsigned long	Size;
/* off 0x0004 */	unsigned long	MaximumSize;
/* off 0x0008 */	unsigned long	MinimumSize;
/* off 0x000c */	unsigned long	FreeSpace;
/* off 0x0010 */	unsigned long	PeakUsage;
/* off 0x0014 */	unsigned long	HighestPage;
/* off 0x0018 */	struct _FILE_OBJECT*	File;
/* off 0x001c */	struct _MMMOD_WRITER_MDL_ENTRY* Entry[2];
/* off 0x0024 */	struct _UNICODE_STRING	PageFileName;
/* off 0x002c */	struct _RTL_BITMAP*	Bitmap;
/* off 0x0030 */	unsigned long	BitmapHint;
/* off 0x0034 */	unsigned long	LastAllocationSize;
/* off 0x0038 */	unsigned short	PageFileNumber:4	 /* start bit 0 */;
/* off 0x0038 */	unsigned short	BootPartition:1	 /* start bit 4 */;
/* off 0x0038 */	unsigned short	Spare0:11	 /* start bit 5 */;
/* off 0x003a */	unsigned short	AdriftMdls:1	 /* start bit 0 */;
/* off 0x003a */	unsigned short	Spare1:15	 /* start bit 1 */;
/* off 0x003c */	void*	FileHandle;
/* off 0x0040 */	union _SLIST_HEADER	AvailableList;
/* off 0x0048 */	union _SLIST_HEADER	NeedProcessingList;
};
struct _MMMOD_WRITER_MDL_ENTRY /* sizeof 00000060 96 */
{
/* off 0x0000 */	struct _LIST_ENTRY	Links;
/* off 0x0008 */	
	union  /* sizeof 00000008 8 */
	{
	/* off 0x0000 */	struct _IO_STATUS_BLOCK	IoStatus;
	}	u;
/* off 0x0010 */	struct _IRP*	Irp;
/* off 0x0014 */	
	union  /* sizeof 00000004 4 */
	{
	/* off 0x0000 */	unsigned long	KeepForever;
	}	u1;
/* off 0x0018 */	struct _MMPAGING_FILE*	PagingFile;
/* off 0x001c */	struct _FILE_OBJECT*	File;
/* off 0x0020 */	struct _CONTROL_AREA*	ControlArea;
/* off 0x0024 */	struct _ERESOURCE*	FileResource;
/* off 0x0028 */	union _LARGE_INTEGER	WriteOffset;
/* off 0x0030 */	union _LARGE_INTEGER	IssueTime;
/* off 0x0038 */	struct _MDL*	PointerMdl;
/* off 0x003c */	struct _MDL	Mdl;
/* off 0x0058 */	unsigned long Page[1];
};
struct _RTL_BITMAP /* sizeof 00000008 8 */
{
/* off 0x0000 */	unsigned long	SizeOfBitMap;
/* off 0x0004 */	unsigned long*	Buffer;
};
struct _MMPAGING_FILE_FREE_ENTRY /* sizeof 00000008 8 */
{
/* off 0x0000 */	struct _SINGLE_LIST_ENTRY	ListEntry;
/* off 0x0004 */	unsigned long	FreeBit;
};
struct _MMVAD_FLAGS /* sizeof 00000004 4 */
{
/* off 0x0000 */	unsigned long	CommitCharge:19	 /* start bit 0 */;
/* off 0x0000 */	unsigned long	NoChange:1	 /* start bit 19 */;
/* off 0x0000 */	unsigned long	VadType:3	 /* start bit 20 */;
/* off 0x0000 */	unsigned long	MemCommit:1	 /* start bit 23 */;
/* off 0x0000 */	unsigned long	Protection:5	 /* start bit 24 */;
/* off 0x0000 */	unsigned long	Spare:2	 /* start bit 29 */;
/* off 0x0000 */	unsigned long	PrivateMemory:1	 /* start bit 31 */;
};
struct _MMVAD_FLAGS3 /* sizeof 00000004 4 */
{
/* off 0x0000 */	unsigned long	PreferredNode:6	 /* start bit 0 */;
/* off 0x0000 */	unsigned long	Teb:1	 /* start bit 6 */;
/* off 0x0000 */	unsigned long	Spare:1	 /* start bit 7 */;
/* off 0x0000 */	unsigned long	SequentialAccess:1	 /* start bit 8 */;
/* off 0x0000 */	unsigned long	LastSequentialTrim:15	 /* start bit 9 */;
/* off 0x0000 */	unsigned long	Spare2:8	 /* start bit 24 */;
};
struct _MMVAD_SHORT /* sizeof 00000020 32 */
{
/* off 0x0000 */	
	union  /* sizeof 00000004 4 */
	{
	/* off 0x0000 */	long	Balance:2	 /* start bit 0 */;
	/* off 0x0000 */	struct _MMVAD*	Parent;
	}	u1;
/* off 0x0004 */	struct _MMVAD*	LeftChild;
/* off 0x0008 */	struct _MMVAD*	RightChild;
/* off 0x000c */	unsigned long	StartingVpn;
/* off 0x0010 */	unsigned long	EndingVpn;
/* off 0x0014 */	
	union  /* sizeof 00000004 4 */
	{
	/* off 0x0000 */	unsigned long	LongFlags;
	/* off 0x0000 */	struct _MMVAD_FLAGS	VadFlags;
	}	u;
/* off 0x0018 */	struct _EX_PUSH_LOCK	PushLock;
/* off 0x001c */	
	union  /* sizeof 00000004 4 */
	{
	/* off 0x0000 */	unsigned long	LongFlags3;
	/* off 0x0000 */	struct _MMVAD_FLAGS3	VadFlags3;
	}	u5;
};
struct _MMVAD_FLAGS2 /* sizeof 00000004 4 */
{
/* off 0x0000 */	unsigned int	FileOffset:24	 /* start bit 0 */;
/* off 0x0000 */	unsigned int	SecNoChange:1	 /* start bit 24 */;
/* off 0x0000 */	unsigned int	OneSecured:1	 /* start bit 25 */;
/* off 0x0000 */	unsigned int	MultipleSecured:1	 /* start bit 26 */;
/* off 0x0000 */	unsigned int	Spare:1	 /* start bit 27 */;
/* off 0x0000 */	unsigned int	LongVad:1	 /* start bit 28 */;
/* off 0x0000 */	unsigned int	ExtendableFile:1	 /* start bit 29 */;
/* off 0x0000 */	unsigned int	Inherit:1	 /* start bit 30 */;
/* off 0x0000 */	unsigned int	CopyOnWrite:1	 /* start bit 31 */;
};
struct _MMVAD /* sizeof 00000030 48 */
{
/* off 0x0000 */	
	union  /* sizeof 00000004 4 */
	{
	/* off 0x0000 */	long	Balance:2	 /* start bit 0 */;
	/* off 0x0000 */	struct _MMVAD*	Parent;
	}	u1;
/* off 0x0004 */	struct _MMVAD*	LeftChild;
/* off 0x0008 */	struct _MMVAD*	RightChild;
/* off 0x000c */	unsigned long	StartingVpn;
/* off 0x0010 */	unsigned long	EndingVpn;
/* off 0x0014 */	
	union  /* sizeof 00000004 4 */
	{
	/* off 0x0000 */	unsigned long	LongFlags;
	/* off 0x0000 */	struct _MMVAD_FLAGS	VadFlags;
	}	u;
/* off 0x0018 */	struct _EX_PUSH_LOCK	PushLock;
/* off 0x001c */	
	union  /* sizeof 00000004 4 */
	{
	/* off 0x0000 */	unsigned long	LongFlags3;
	/* off 0x0000 */	struct _MMVAD_FLAGS3	VadFlags3;
	}	u5;
/* off 0x0020 */	
	union  /* sizeof 00000004 4 */
	{
	/* off 0x0000 */	unsigned long	LongFlags2;
	/* off 0x0000 */	struct _MMVAD_FLAGS2	VadFlags2;
	}	u2;
union
{
/* off 0x0024 */	struct _SUBSECTION*	Subsection;
/* off 0x0024 */	struct _MSUBSECTION*	MappedSubsection;
};
/* off 0x0028 */	struct _MMPTE*	FirstPrototypePte;
/* off 0x002c */	struct _MMPTE*	LastContiguousPte;
};
struct _SUBSECTION /* sizeof 00000020 32 */
{
/* off 0x0000 */	struct _CONTROL_AREA*	ControlArea;
/* off 0x0004 */	struct _MMPTE*	SubsectionBase;
/* off 0x0008 */	struct _SUBSECTION*	NextSubsection;
/* off 0x000c */	unsigned long	PtesInSubsection;
union
{
/* off 0x0010 */	unsigned long	UnusedPtes;
/* off 0x0010 */	struct _MM_AVL_TABLE*	GlobalPerSessionHead;
};
/* off 0x0014 */	
	union  /* sizeof 00000004 4 */
	{
	/* off 0x0000 */	unsigned long	LongFlags;
	/* off 0x0000 */	struct _MMSUBSECTION_FLAGS	SubsectionFlags;
	}	u;
/* off 0x0018 */	unsigned long	StartingSector;
/* off 0x001c */	unsigned long	NumberOfFullSectors;
};
struct _MSUBSECTION /* sizeof 00000038 56 */
{
/* off 0x0000 */	struct _CONTROL_AREA*	ControlArea;
/* off 0x0004 */	struct _MMPTE*	SubsectionBase;
union
{
/* off 0x0008 */	struct _SUBSECTION*	NextSubsection;
/* off 0x0008 */	struct _MSUBSECTION*	NextMappedSubsection;
};
/* off 0x000c */	unsigned long	PtesInSubsection;
union
{
/* off 0x0010 */	unsigned long	UnusedPtes;
/* off 0x0010 */	struct _MM_AVL_TABLE*	GlobalPerSessionHead;
};
/* off 0x0014 */	
	union  /* sizeof 00000004 4 */
	{
	/* off 0x0000 */	unsigned long	LongFlags;
	/* off 0x0000 */	struct _MMSUBSECTION_FLAGS	SubsectionFlags;
	}	u;
/* off 0x0018 */	unsigned long	StartingSector;
/* off 0x001c */	unsigned long	NumberOfFullSectors;
/* off 0x0020 */	
	union  /* sizeof 00000004 4 */
	{
	/* off 0x0000 */	long	Balance:2	 /* start bit 0 */;
	/* off 0x0000 */	struct _MMSUBSECTION_NODE*	Parent;
	}	u1;
/* off 0x0024 */	struct _MMSUBSECTION_NODE*	LeftChild;
/* off 0x0028 */	struct _MMSUBSECTION_NODE*	RightChild;
/* off 0x002c */	struct _LIST_ENTRY	DereferenceList;
/* off 0x0034 */	unsigned long	NumberOfMappedViews;
};
struct _MI_PER_SESSION_PROTOS /* sizeof 0000001c 28 */
{
/* off 0x0000 */	
	union  /* sizeof 00000004 4 */
	{
	/* off 0x0000 */	long	Balance:2	 /* start bit 0 */;
	/* off 0x0000 */	struct _MMADDRESS_NODE*	Parent;
	/* off 0x0000 */	struct _MI_PER_SESSION_PROTOS*	NextToFree;
	}	u1;
/* off 0x0004 */	struct _MMADDRESS_NODE*	LeftChild;
/* off 0x0008 */	struct _MMADDRESS_NODE*	RightChild;
union
{
/* off 0x000c */	unsigned long	SessionId;
/* off 0x000c */	unsigned long	StartingVpn;
/* off 0x000c */	struct _SUBSECTION*	Subsection;
};
/* off 0x0010 */	unsigned long	EndingVpn;
/* off 0x0014 */	struct _MMPTE*	SubsectionBase;
/* off 0x0018 */	
	union  /* sizeof 00000004 4 */
	{
	/* off 0x0000 */	unsigned long	ReferenceCount;
	/* off 0x0000 */	unsigned long	NumberOfPtesToFree;
	}	u2;
};
enum _IO_PAGING_PRIORITY
{
	IoPagingPriorityInvalid	=0x00000000	,//0
	IoPagingPriorityNormal	=0x00000001	,//0
	IoPagingPriorityHigh	=0x00000002	,//0
	IoPagingPriorityReserved1	=0x00000003	,//0
	IoPagingPriorityReserved2	=0x00000004	,//0
};
struct _MI_PAGEFILE_TRACES /* sizeof 00000040 64 */
{
/* off 0x0000 */	long	Status;
/* off 0x0004 */	unsigned char	Priority;
/* off 0x0005 */	unsigned char	IrpPriority;
/* off 0x0008 */	union _LARGE_INTEGER	CurrentTime;
/* off 0x0010 */	unsigned long	AvailablePages;
/* off 0x0014 */	unsigned long	ModifiedPagesTotal;
/* off 0x0018 */	unsigned long	ModifiedPagefilePages;
/* off 0x001c */	unsigned long	ModifiedNoWritePages;
/* off 0x0020 */	
	struct  /* sizeof 00000020 32 */
	{
	/* off 0x0000 */	struct _MDL	Mdl;
	/* off 0x001c */	unsigned long Page[1];
	}	MdlHack;
};
struct _FREE_DISPLAY /* sizeof 0000000c 12 */
{
/* off 0x0000 */	unsigned long	RealVectorSize;
/* off 0x0004 */	struct _RTL_BITMAP	Display;
};
struct _DUAL /* sizeof 0000013c 316 */
{
/* off 0x0000 */	unsigned long	Length;
/* off 0x0004 */	struct _HMAP_DIRECTORY*	Map;
/* off 0x0008 */	struct _HMAP_TABLE*	SmallDir;
/* off 0x000c */	unsigned long	Guard;
/* off 0x0010 */	struct _FREE_DISPLAY FreeDisplay[24];
/* off 0x0130 */	unsigned long	FreeSummary;
/* off 0x0134 */	struct _LIST_ENTRY	FreeBins;
};
struct _HHIVE /* sizeof 000002e8 744 */
{
/* off 0x0000 */	unsigned long	Signature;
/* off 0x0004 */	struct _CELL_DATA*( __stdcall *GetCellRoutine)(struct _HHIVE*,unsigned long);
/* off 0x0008 */	void( __stdcall *ReleaseCellRoutine)(struct _HHIVE*,unsigned long);
/* off 0x000c */	void*( __stdcall *Allocate)(unsigned long,unsigned char,unsigned long);
/* off 0x0010 */	void( __stdcall *Free)(void*,unsigned long);
/* off 0x0014 */	unsigned char( __stdcall *FileSetSize)(struct _HHIVE*,unsigned long,unsigned long,unsigned long);
/* off 0x0018 */	unsigned char( __stdcall *FileWrite)(struct _HHIVE*,unsigned long,struct CMP_OFFSET_ARRAY*,unsigned long,unsigned long*);
/* off 0x001c */	unsigned char( __stdcall *FileRead)(struct _HHIVE*,unsigned long,unsigned long*,void*,unsigned long);
/* off 0x0020 */	unsigned char( __stdcall *FileFlush)(struct _HHIVE*,unsigned long,union _LARGE_INTEGER*,unsigned long);
/* off 0x0024 */	struct _HBASE_BLOCK*	BaseBlock;
/* off 0x0028 */	struct _RTL_BITMAP	DirtyVector;
/* off 0x0030 */	unsigned long	DirtyCount;
/* off 0x0034 */	unsigned long	DirtyAlloc;
/* off 0x0038 */	unsigned long	BaseBlockAlloc;
/* off 0x003c */	unsigned long	Cluster;
/* off 0x0040 */	unsigned char	Flat;
/* off 0x0041 */	unsigned char	ReadOnly;
/* off 0x0042 */	unsigned char	DirtyFlag;
/* off 0x0044 */	unsigned long	HvBinHeadersUse;
/* off 0x0048 */	unsigned long	HvFreeCellsUse;
/* off 0x004c */	unsigned long	HvUsedCellsUse;
/* off 0x0050 */	unsigned long	CmUsedCellsUse;
/* off 0x0054 */	unsigned long	HiveFlags;
/* off 0x0058 */	unsigned long	CurrentLog;
/* off 0x005c */	unsigned long LogSize[2];
/* off 0x0064 */	unsigned long	RefreshCount;
/* off 0x0068 */	unsigned long	StorageTypeCount;
/* off 0x006c */	unsigned long	Version;
/* off 0x0070 */	struct _DUAL Storage[2];
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
/* off 0x0034 */	unsigned long	MaxNameLen:16	 /* start bit 0 */;
/* off 0x0034 */	unsigned long	UserFlags:4	 /* start bit 16 */;
/* off 0x0034 */	unsigned long	VirtControlFlags:4	 /* start bit 20 */;
/* off 0x0034 */	unsigned long	Debug:8	 /* start bit 24 */;
/* off 0x0038 */	unsigned long	MaxClassLen;
/* off 0x003c */	unsigned long	MaxValueNameLen;
/* off 0x0040 */	unsigned long	MaxValueDataLen;
/* off 0x0044 */	unsigned long	WorkVar;
/* off 0x0048 */	unsigned short	NameLength;
/* off 0x004a */	unsigned short	ClassLength;
/* off 0x004c */	wchar Name[1];
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
/* off 0x0014 */	wchar Name[1];
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
/* off 0x0000 */	wchar KeyString[1];
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
/* off 0x0070 */	struct _GUID	RmId;
/* off 0x0080 */	struct _GUID	LogId;
/* off 0x0090 */	unsigned long	Flags;
/* off 0x0094 */	struct _GUID	TmId;
/* off 0x00a4 */	unsigned long	GuidSignature;
/* off 0x00a8 */	unsigned long Reserved1[85];
/* off 0x01fc */	unsigned long	CheckSum;
/* off 0x0200 */	unsigned long Reserved2[882];
/* off 0x0fc8 */	struct _GUID	ThawTmId;
/* off 0x0fd8 */	struct _GUID	ThawRmId;
/* off 0x0fe8 */	struct _GUID	ThawLogId;
/* off 0x0ff8 */	unsigned long	BootType;
/* off 0x0ffc */	unsigned long	BootRecover;
};
struct _HMAP_DIRECTORY /* sizeof 00001000 4096 */
{
/* off 0x0000 */	struct _HMAP_TABLE* Directory[1024];
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
struct _CM_VIEW_OF_FILE /* sizeof 00000030 48 */
{
/* off 0x0000 */	struct _LIST_ENTRY	MappedViewLinks;
/* off 0x0008 */	struct _LIST_ENTRY	PinnedViewLinks;
/* off 0x0010 */	struct _LIST_ENTRY	FlushedViewLinks;
/* off 0x0018 */	struct _CMHIVE*	CmHive;
/* off 0x001c */	void*	Bcb;
/* off 0x0020 */	void*	ViewAddress;
/* off 0x0024 */	unsigned long	FileOffset;
/* off 0x0028 */	unsigned long	Size;
/* off 0x002c */	unsigned long	UseCount;
};
struct _CMHIVE /* sizeof 000005e0 1504 */
{
/* off 0x0000 */	struct _HHIVE	Hive;
/* off 0x02e8 */	void* FileHandles[6];
/* off 0x0300 */	struct _LIST_ENTRY	NotifyList;
/* off 0x0308 */	struct _LIST_ENTRY	HiveList;
/* off 0x0310 */	struct _FAST_MUTEX*	HiveLock;
/* off 0x0314 */	struct _EX_PUSH_LOCK	ViewLock;
/* off 0x0318 */	struct _KTHREAD*	ViewLockOwner;
/* off 0x031c */	unsigned long	ViewLockLast;
/* off 0x0320 */	unsigned long	ViewUnLockLast;
/* off 0x0324 */	struct _FAST_MUTEX*	WriterLock;
/* off 0x0328 */	struct _EX_PUSH_LOCK	FlusherLock;
/* off 0x032c */	struct _EX_PUSH_LOCK	SecurityLock;
/* off 0x0330 */	struct _LIST_ENTRY	MappedViewList;
/* off 0x0338 */	struct _LIST_ENTRY	PinnedViewList;
/* off 0x0340 */	struct _LIST_ENTRY	FlushedViewList;
/* off 0x0348 */	unsigned short	MappedViewCount;
/* off 0x034a */	unsigned short	PinnedViewCount;
/* off 0x034c */	unsigned long	UseCount;
/* off 0x0350 */	unsigned long	ViewsPerHive;
/* off 0x0354 */	struct _FILE_OBJECT*	FileObject;
/* off 0x0358 */	unsigned long	LastShrinkHiveSize;
/* off 0x0360 */	union _LARGE_INTEGER	ActualFileSize;
/* off 0x0368 */	struct _UNICODE_STRING	FileFullPath;
/* off 0x0370 */	struct _UNICODE_STRING	FileUserName;
/* off 0x0378 */	struct _UNICODE_STRING	HiveRootPath;
/* off 0x0380 */	unsigned long	SecurityCount;
/* off 0x0384 */	unsigned long	SecurityCacheSize;
/* off 0x0388 */	long	SecurityHitHint;
/* off 0x038c */	struct _CM_KEY_SECURITY_CACHE_ENTRY*	SecurityCache;
/* off 0x0390 */	struct _LIST_ENTRY SecurityHash[64];
/* off 0x0590 */	unsigned long	UnloadEventCount;
/* off 0x0594 */	struct _KEVENT**	UnloadEventArray;
/* off 0x0598 */	struct _CM_KEY_CONTROL_BLOCK*	RootKcb;
/* off 0x059c */	unsigned char	Frozen;
/* off 0x05a0 */	struct _CM_WORKITEM*	UnloadWorkItem;
/* off 0x05a4 */	unsigned char	GrowOnlyMode;
/* off 0x05a8 */	unsigned long	GrowOffset;
/* off 0x05ac */	struct _LIST_ENTRY	KcbConvertListHead;
/* off 0x05b4 */	struct _LIST_ENTRY	KnodeConvertListHead;
/* off 0x05bc */	struct _CM_CELL_REMAP_BLOCK*	CellRemapArray;
/* off 0x05c0 */	unsigned long	Flags;
/* off 0x05c4 */	struct _LIST_ENTRY	TrustClassEntry;
/* off 0x05cc */	unsigned long	FlushCount;
/* off 0x05d0 */	struct _CM_RM*	CmRm;
/* off 0x05d4 */	unsigned long	CmRmInitFailPoint;
/* off 0x05d8 */	long	CmRmInitFailStatus;
/* off 0x05dc */	struct _KTHREAD*	CreatorOwner;
};
struct _CM_KEY_SECURITY_CACHE_ENTRY /* sizeof 00000008 8 */
{
/* off 0x0000 */	unsigned long	Cell;
/* off 0x0004 */	struct _CM_KEY_SECURITY_CACHE*	CachedSecurity;
};
struct _CM_KEY_SECURITY_CACHE /* sizeof 0000002c 44 */
{
/* off 0x0000 */	unsigned long	Cell;
/* off 0x0004 */	unsigned long	ConvKey;
/* off 0x0008 */	struct _LIST_ENTRY	List;
/* off 0x0010 */	unsigned long	DescriptorLength;
/* off 0x0014 */	unsigned long	RealRefCount;
/* off 0x0018 */	struct _SECURITY_DESCRIPTOR_RELATIVE	Descriptor;
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
struct _CM_INTENT_LOCK /* sizeof 00000008 8 */
{
/* off 0x0000 */	unsigned long	OwnerCount;
/* off 0x0004 */	struct _CM_KCB_UOW**	OwnerTable;
};
struct _CM_KEY_CONTROL_BLOCK /* sizeof 00000090 144 */
{
/* off 0x0000 */	unsigned long	RefCount;
/* off 0x0004 */	unsigned long	ExtFlags:9	 /* start bit 0 */;
/* off 0x0004 */	unsigned long	PrivateAlloc:1	 /* start bit 9 */;
/* off 0x0004 */	unsigned long	Delete:1	 /* start bit 10 */;
/* off 0x0004 */	unsigned long	DelayedCloseIndex:11	 /* start bit 11 */;
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
/* off 0x0038 */	struct _CM_KEY_BODY* KeyBodyArray[4];
/* off 0x0048 */	void*	DelayCloseEntry;
/* off 0x0050 */	union _LARGE_INTEGER	KcbLastWriteTime;
/* off 0x0058 */	unsigned short	KcbMaxNameLen;
/* off 0x005a */	unsigned short	KcbMaxValueNameLen;
/* off 0x005c */	unsigned long	KcbMaxValueDataLen;
/* off 0x0060 */	unsigned long	KcbUserFlags:4	 /* start bit 0 */;
/* off 0x0060 */	unsigned long	KcbVirtControlFlags:4	 /* start bit 4 */;
/* off 0x0060 */	unsigned long	KcbDebug:8	 /* start bit 8 */;
/* off 0x0060 */	unsigned long	Flags:16	 /* start bit 16 */;
/* off 0x0064 */	struct _LIST_ENTRY	KCBUoWListHead;
/* off 0x006c */	struct _CM_TRANS*	TransKCBOwner;
/* off 0x0070 */	struct _CM_INTENT_LOCK	KCBLock;
/* off 0x0078 */	struct _CM_INTENT_LOCK	KeyLock;
/* off 0x0080 */	struct _CHILD_LIST	TransValueCache;
/* off 0x0088 */	struct _CM_TRANS*	TransValueListOwner;
/* off 0x008c */	struct _UNICODE_STRING*	FullKCBName;
};
struct _CM_NAME_HASH /* sizeof 0000000c 12 */
{
/* off 0x0000 */	unsigned long	ConvKey;
/* off 0x0004 */	struct _CM_NAME_HASH*	NextHash;
/* off 0x0008 */	unsigned short	NameLength;
/* off 0x000a */	wchar Name[1];
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
/* off 0x000e */	wchar Name[1];
};
};
};
struct _CM_INDEX_HINT_BLOCK /* sizeof 00000008 8 */
{
/* off 0x0000 */	unsigned long	Count;
/* off 0x0004 */	unsigned long HashKey[1];
};
struct _CM_KEY_BODY /* sizeof 0000002c 44 */
{
/* off 0x0000 */	unsigned long	Type;
/* off 0x0004 */	struct _CM_KEY_CONTROL_BLOCK*	KeyControlBlock;
/* off 0x0008 */	struct _CM_NOTIFY_BLOCK*	NotifyBlock;
/* off 0x000c */	void*	ProcessID;
/* off 0x0010 */	struct _LIST_ENTRY	KeyBodyList;
/* off 0x0018 */	unsigned long	Flags;
/* off 0x001c */	void*	KtmTrans;
/* off 0x0020 */	struct _GUID*	KtmUow;
/* off 0x0024 */	struct _LIST_ENTRY	ContextListHead;
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
struct _CM_TRANS /* sizeof 00000068 104 */
{
/* off 0x0000 */	struct _LIST_ENTRY	TransactionListEntry;
/* off 0x0008 */	struct _LIST_ENTRY	KCBUoWListHead;
/* off 0x0010 */	struct _LIST_ENTRY	LazyCommitListEntry;
/* off 0x0018 */	void*	KtmTrans;
/* off 0x001c */	struct _CM_RM*	CmRm;
/* off 0x0020 */	struct _KENLISTMENT*	KtmEnlistmentObject;
/* off 0x0024 */	void*	KtmEnlistmentHandle;
/* off 0x0028 */	struct _GUID	KtmUow;
/* off 0x0038 */	unsigned __int64	StartLsn;
/* off 0x0040 */	unsigned long	TransState;
/* off 0x0044 */	unsigned long	HiveCount;
/* off 0x0048 */	struct _CMHIVE* HiveArray[8];
};
struct _CM_RM /* sizeof 00000058 88 */
{
/* off 0x0000 */	struct _LIST_ENTRY	RmListEntry;
/* off 0x0008 */	struct _LIST_ENTRY	TransactionListHead;
/* off 0x0010 */	void*	TmHandle;
/* off 0x0014 */	void*	Tm;
/* off 0x0018 */	void*	RmHandle;
/* off 0x001c */	void*	KtmRm;
/* off 0x0020 */	unsigned long	RefCount;
/* off 0x0024 */	unsigned long	ContainerNum;
/* off 0x0028 */	unsigned __int64	ContainerSize;
/* off 0x0030 */	struct _CMHIVE*	CmHive;
/* off 0x0034 */	void*	LogFileObject;
/* off 0x0038 */	void*	MarshallingContext;
/* off 0x003c */	unsigned long	RmFlags;
/* off 0x0040 */	long	LogStartStatus1;
/* off 0x0044 */	long	LogStartStatus2;
/* off 0x0048 */	unsigned __int64	BaseLsn;
/* off 0x0050 */	struct _ERESOURCE*	RmLock;
};
struct _RTL_BALANCED_LINKS /* sizeof 00000010 16 */
{
/* off 0x0000 */	struct _RTL_BALANCED_LINKS*	Parent;
/* off 0x0004 */	struct _RTL_BALANCED_LINKS*	LeftChild;
/* off 0x0008 */	struct _RTL_BALANCED_LINKS*	RightChild;
/* off 0x000c */	char	Balance;
/* off 0x000d */	unsigned char Reserved[3];
};
struct _KTMOBJECT_NAMESPACE_LINK /* sizeof 00000014 20 */
{
/* off 0x0000 */	struct _RTL_BALANCED_LINKS	Links;
/* off 0x0010 */	unsigned char	Expired;
};
struct _KMUTANT /* sizeof 00000020 32 */
{
/* off 0x0000 */	struct _DISPATCHER_HEADER	Header;
/* off 0x0010 */	struct _LIST_ENTRY	MutantListEntry;
/* off 0x0018 */	struct _KTHREAD*	OwnerThread;
/* off 0x001c */	unsigned char	Abandoned;
/* off 0x001d */	unsigned char	ApcDisable;
};
struct _KENLISTMENT_HISTORY /* sizeof 00000008 8 */
{
/* off 0x0000 */	unsigned long	Notification;
/* off 0x0004 */	enum _KENLISTMENT_STATE	NewState;
};
struct _KENLISTMENT /* sizeof 00000168 360 */
{
/* off 0x0000 */	unsigned long	cookie;
/* off 0x0004 */	struct _KTMOBJECT_NAMESPACE_LINK	NamespaceLink;
/* off 0x0018 */	struct _GUID	EnlistmentId;
/* off 0x0028 */	struct _KMUTANT	Mutex;
/* off 0x0048 */	struct _LIST_ENTRY	NextSameTx;
/* off 0x0050 */	struct _LIST_ENTRY	NextSameRm;
/* off 0x0058 */	struct _KRESOURCEMANAGER*	ResourceManager;
/* off 0x005c */	struct _KTRANSACTION*	Transaction;
/* off 0x0060 */	enum _KENLISTMENT_STATE	State;
/* off 0x0064 */	unsigned long	Flags;
/* off 0x0068 */	unsigned long	NotificationMask;
/* off 0x006c */	void*	Key;
/* off 0x0070 */	unsigned long	KeyRefCount;
/* off 0x0074 */	void*	RecoveryInformation;
/* off 0x0078 */	unsigned long	RecoveryInformationLength;
/* off 0x007c */	void*	DynamicNameInformation;
/* off 0x0080 */	unsigned long	DynamicNameInformationLength;
/* off 0x0084 */	struct _KTMNOTIFICATION_PACKET*	FinalNotification;
/* off 0x0088 */	struct _KENLISTMENT*	SupSubEnlistment;
/* off 0x008c */	void*	SupSubEnlHandle;
/* off 0x0090 */	void*	SubordinateTxHandle;
/* off 0x0094 */	struct _GUID	CrmEnlistmentEnId;
/* off 0x00a4 */	struct _GUID	CrmEnlistmentTmId;
/* off 0x00b4 */	struct _GUID	CrmEnlistmentRmId;
/* off 0x00c4 */	unsigned long	NextHistory;
/* off 0x00c8 */	struct _KENLISTMENT_HISTORY History[20];
};
struct _RTL_AVL_TABLE /* sizeof 00000038 56 */
{
/* off 0x0000 */	struct _RTL_BALANCED_LINKS	BalancedRoot;
/* off 0x0010 */	void*	OrderedPointer;
/* off 0x0014 */	unsigned long	WhichOrderedElement;
/* off 0x0018 */	unsigned long	NumberGenericTableElements;
/* off 0x001c */	unsigned long	DepthOfTree;
/* off 0x0020 */	struct _RTL_BALANCED_LINKS*	RestartKey;
/* off 0x0024 */	unsigned long	DeleteCount;
/* off 0x0028 */	enum _RTL_GENERIC_COMPARE_RESULTS( __stdcall *CompareRoutine)(struct _RTL_AVL_TABLE*,void*,void*);
/* off 0x002c */	void*( __stdcall *AllocateRoutine)(struct _RTL_AVL_TABLE*,unsigned long);
/* off 0x0030 */	void( __stdcall *FreeRoutine)(struct _RTL_AVL_TABLE*,void*);
/* off 0x0034 */	void*	TableContext;
};
struct _KTMOBJECT_NAMESPACE /* sizeof 00000060 96 */
{
/* off 0x0000 */	struct _RTL_AVL_TABLE	Table;
/* off 0x0038 */	struct _KMUTANT	Mutex;
/* off 0x0058 */	unsigned short	LinksOffset;
/* off 0x005a */	unsigned short	GuidOffset;
/* off 0x005c */	unsigned char	Expired;
};
struct _KRESOURCEMANAGER_COMPLETION_BINDING /* sizeof 00000014 20 */
{
/* off 0x0000 */	struct _LIST_ENTRY	NotificationListHead;
/* off 0x0008 */	void*	Port;
/* off 0x000c */	unsigned long	Key;
/* off 0x0010 */	struct _EPROCESS*	BindingProcess;
};
struct _KRESOURCEMANAGER /* sizeof 00000154 340 */
{
/* off 0x0000 */	struct _KEVENT	NotificationAvailable;
/* off 0x0010 */	unsigned long	cookie;
/* off 0x0014 */	enum _KRESOURCEMANAGER_STATE	State;
/* off 0x0018 */	unsigned long	Flags;
/* off 0x001c */	struct _KMUTANT	Mutex;
/* off 0x003c */	struct _KTMOBJECT_NAMESPACE_LINK	NamespaceLink;
/* off 0x0050 */	struct _GUID	RmId;
/* off 0x0060 */	struct _KQUEUE	NotificationQueue;
/* off 0x0088 */	struct _KMUTANT	NotificationMutex;
/* off 0x00a8 */	struct _LIST_ENTRY	EnlistmentHead;
/* off 0x00b0 */	unsigned long	EnlistmentCount;
/* off 0x00b4 */	long( __stdcall *NotificationRoutine)(struct _KENLISTMENT*,void*,void*,unsigned long,union _LARGE_INTEGER*,unsigned long,void*);
/* off 0x00b8 */	void*	Key;
/* off 0x00bc */	struct _LIST_ENTRY	ProtocolListHead;
/* off 0x00c4 */	struct _LIST_ENTRY	PendingPropReqListHead;
/* off 0x00cc */	struct _LIST_ENTRY	CRMListEntry;
/* off 0x00d4 */	struct _KTM*	Tm;
/* off 0x00d8 */	struct _UNICODE_STRING	Description;
/* off 0x00e0 */	struct _KTMOBJECT_NAMESPACE	Enlistments;
/* off 0x0140 */	struct _KRESOURCEMANAGER_COMPLETION_BINDING	CompletionBinding;
};
enum _KRESOURCEMANAGER_STATE
{
	KResourceManagerUninitialized	=0x00000000	,//0
	KResourceManagerOffline	=0x00000001	,//0
	KResourceManagerOnline	=0x00000002	,//0
};
union _CLS_LSN /* sizeof 00000008 8 */
{
/* off 0x0000 */	
	struct  /* sizeof 00000008 8 */
	{
	/* off 0x0000 */	unsigned int	idxRecord;
	/* off 0x0004 */	unsigned long	cidContainer;
	}	offset;
/* off 0x0000 */	unsigned __int64	ullOffset;
};
struct _WORK_QUEUE_ITEM /* sizeof 00000010 16 */
{
/* off 0x0000 */	struct _LIST_ENTRY	List;
/* off 0x0008 */	void( __stdcall *WorkerRoutine)(void*);
/* off 0x000c */	void*	Parameter;
};
struct _KTM /* sizeof 00000228 552 */
{
/* off 0x0000 */	unsigned long	cookie;
/* off 0x0004 */	struct _KMUTANT	Mutex;
/* off 0x0024 */	enum KTM_STATE	State;
/* off 0x0028 */	struct _KTMOBJECT_NAMESPACE_LINK	NamespaceLink;
/* off 0x003c */	struct _GUID	TmIdentity;
/* off 0x004c */	unsigned long	Flags;
/* off 0x0050 */	unsigned long	VolatileFlags;
/* off 0x0054 */	struct _UNICODE_STRING	LogFileName;
/* off 0x005c */	struct _FILE_OBJECT*	LogFileObject;
/* off 0x0060 */	void*	MarshallingContext;
/* off 0x0064 */	void*	LogManagementContext;
/* off 0x0068 */	struct _KTMOBJECT_NAMESPACE	Transactions;
/* off 0x00c8 */	struct _KTMOBJECT_NAMESPACE	ResourceManagers;
/* off 0x0128 */	struct _KMUTANT	LsnOrderedMutex;
/* off 0x0148 */	struct _LIST_ENTRY	LsnOrderedList;
/* off 0x0150 */	union _LARGE_INTEGER	CommitVirtualClock;
/* off 0x0158 */	struct _FAST_MUTEX	CommitVirtualClockMutex;
/* off 0x0178 */	union _CLS_LSN	BaseLsn;
/* off 0x0180 */	union _CLS_LSN	CurrentReadLsn;
/* off 0x0188 */	union _CLS_LSN	LastRecoveredLsn;
/* off 0x0190 */	void*	TmRmHandle;
/* off 0x0194 */	struct _KRESOURCEMANAGER*	TmRm;
/* off 0x0198 */	struct _KEVENT	LogFullNotifyEvent;
/* off 0x01a8 */	struct _WORK_QUEUE_ITEM	CheckpointWorkItem;
/* off 0x01b8 */	union _CLS_LSN	CheckpointTargetLsn;
/* off 0x01c0 */	struct _WORK_QUEUE_ITEM	LogFullCompletedWorkItem;
/* off 0x01d0 */	struct _ERESOURCE	LogWriteResource;
/* off 0x0208 */	unsigned long	LogFlags;
/* off 0x020c */	long	LogFullStatus;
/* off 0x0210 */	long	RecoveryStatus;
/* off 0x0218 */	union _CLS_LSN	LastCheckBaseLsn;
/* off 0x0220 */	struct _LIST_ENTRY	RestartOrderedList;
};
enum KTM_STATE
{
	KKtmUninitialized	=0x00000000	,//0
	KKtmInitialized	=0x00000001	,//0
	KKtmRecovering	=0x00000002	,//0
	KKtmOnline	=0x00000003	,//0
	KKtmRecoveryFailed	=0x00000004	,//0
	KKtmOffline	=0x00000005	,//0
};
enum _RTL_GENERIC_COMPARE_RESULTS
{
	GenericLessThan	=0x00000000	,//0
	GenericGreaterThan	=0x00000001	,//0
	GenericEqual	=0x00000002	,//0
};
struct _KTRANSACTION_HISTORY /* sizeof 00000008 8 */
{
/* off 0x0000 */	enum <unnamed-tag>	RecordType;
/* off 0x0004 */	unsigned long	Payload;
};
struct _KTRANSACTION /* sizeof 000001e0 480 */
{
/* off 0x0000 */	struct _KEVENT	OutcomeEvent;
/* off 0x0010 */	unsigned long	cookie;
/* off 0x0014 */	struct _KMUTANT	Mutex;
/* off 0x0034 */	struct _KTRANSACTION*	TreeTx;
/* off 0x0038 */	struct _KTMOBJECT_NAMESPACE_LINK	GlobalNamespaceLink;
/* off 0x004c */	struct _KTMOBJECT_NAMESPACE_LINK	TmNamespaceLink;
/* off 0x0060 */	struct _GUID	UOW;
/* off 0x0070 */	enum _KTRANSACTION_STATE	State;
/* off 0x0074 */	unsigned long	Flags;
/* off 0x0078 */	struct _LIST_ENTRY	EnlistmentHead;
/* off 0x0080 */	unsigned long	EnlistmentCount;
/* off 0x0084 */	unsigned long	RecoverableEnlistmentCount;
/* off 0x0088 */	unsigned long	PrePrepareRequiredEnlistmentCount;
/* off 0x008c */	unsigned long	PrepareRequiredEnlistmentCount;
/* off 0x0090 */	unsigned long	OutcomeRequiredEnlistmentCount;
/* off 0x0094 */	unsigned long	PendingResponses;
/* off 0x0098 */	struct _KENLISTMENT*	SuperiorEnlistment;
/* off 0x00a0 */	union _CLS_LSN	LastLsn;
/* off 0x00a8 */	struct _LIST_ENTRY	PromotedEntry;
/* off 0x00b0 */	struct _KTRANSACTION*	PromoterTransaction;
/* off 0x00b4 */	void*	PromotePropagation;
/* off 0x00b8 */	unsigned long	IsolationLevel;
/* off 0x00bc */	unsigned long	IsolationFlags;
/* off 0x00c0 */	union _LARGE_INTEGER	Timeout;
/* off 0x00c8 */	struct _UNICODE_STRING	Description;
/* off 0x00d0 */	struct _KTHREAD*	RollbackThread;
/* off 0x00d4 */	struct _WORK_QUEUE_ITEM	RollbackWorkItem;
/* off 0x00e4 */	struct _KDPC	RollbackDpc;
/* off 0x0108 */	struct _KTIMER	RollbackTimer;
/* off 0x0130 */	struct _LIST_ENTRY	LsnOrderedEntry;
/* off 0x0138 */	enum _KTRANSACTION_OUTCOME	Outcome;
/* off 0x013c */	struct _KTM*	Tm;
/* off 0x0140 */	__int64	CommitReservation;
/* off 0x0148 */	struct _KTRANSACTION_HISTORY TransactionHistory[10];
/* off 0x0198 */	unsigned long	TransactionHistoryCount;
/* off 0x019c */	void*	DTCPrivateInformation;
/* off 0x01a0 */	unsigned long	DTCPrivateInformationLength;
/* off 0x01a4 */	struct _KMUTANT	DTCPrivateInformationMutex;
/* off 0x01c4 */	void*	PromotedTxSelfHandle;
/* off 0x01c8 */	unsigned long	PendingPromotionCount;
/* off 0x01cc */	struct _KEVENT	PromotionCompletedEvent;
};
enum _KTRANSACTION_STATE
{
	KTransactionUninitialized	=0x00000000	,//0
	KTransactionActive	=0x00000001	,//0
	KTransactionPreparing	=0x00000002	,//0
	KTransactionPrepared	=0x00000003	,//0
	KTransactionInDoubt	=0x00000004	,//0
	KTransactionCommitted	=0x00000005	,//0
	KTransactionAborted	=0x00000006	,//0
	KTransactionDelegated	=0x00000007	,//0
	KTransactionPrePreparing	=0x00000008	,//0
	KTransactionForgotten	=0x00000009	,//0
	KTransactionRecovering	=0x0000000a	,//0
	KTransactionPrePrepared	=0x0000000b	,//0
};
enum _KTRANSACTION_OUTCOME
{
	KTxOutcomeUninitialized	=0x00000000	,//0
	KTxOutcomeUndetermined	=0x00000001	,//0
	KTxOutcomeCommitted	=0x00000002	,//0
	KTxOutcomeAborted	=0x00000003	,//0
	KTxOutcomeUnavailable	=0x00000004	,//0
};
enum <unnamed-tag>
{
	KTMOH_CommitTransaction_Result	=0x00000001	,//0
	KTMOH_RollbackTransaction_Result	=0x00000002	,//0
};
enum _KENLISTMENT_STATE
{
	KEnlistmentUninitialized	=0x00000000	,//0
	KEnlistmentActive	=0x00000100	,//0
	KEnlistmentPreparing	=0x00000101	,//0
	KEnlistmentPrepared	=0x00000102	,//0
	KEnlistmentInDoubt	=0x00000103	,//0
	KEnlistmentCommitted	=0x00000104	,//0
	KEnlistmentCommittedNotify	=0x00000105	,//0
	KEnlistmentCommitRequested	=0x00000106	,//0
	KEnlistmentAborted	=0x00000107	,//0
	KEnlistmentDelegated	=0x00000108	,//0
	KEnlistmentDelegatedDisconnected	=0x00000109	,//0
	KEnlistmentPrePreparing	=0x0000010a	,//0
	KEnlistmentForgotten	=0x0000010b	,//0
	KEnlistmentRecovering	=0x0000010c	,//0
	KEnlistmentAborting	=0x0000010d	,//0
	KEnlistmentReadOnly	=0x0000010e	,//0
	KEnlistmentOutcomeUnavailable	=0x0000010f	,//0
	KEnlistmentOffline	=0x00000110	,//0
	KEnlistmentPrePrepared	=0x00000111	,//0
	KEnlistmentInitialized	=0x00000112	,//0
};
struct _KTMNOTIFICATION_PACKET /* sizeof 00000000 0 */
{
};
struct _CM_KCB_UOW /* sizeof 00000038 56 */
{
/* off 0x0000 */	struct _LIST_ENTRY	TransactionListEntry;
/* off 0x0008 */	struct _CM_INTENT_LOCK*	KCBLock;
/* off 0x000c */	struct _CM_INTENT_LOCK*	KeyLock;
/* off 0x0010 */	struct _LIST_ENTRY	KCBListEntry;
/* off 0x0018 */	struct _CM_KEY_CONTROL_BLOCK*	KeyControlBlock;
/* off 0x001c */	struct _CM_TRANS*	Transaction;
/* off 0x0020 */	unsigned long	UoWState;
/* off 0x0024 */	enum UoWActionType	ActionType;
/* off 0x0028 */	enum HSTORAGE_TYPE	StorageType;
union
{
/* off 0x0030 */	struct _CM_KEY_CONTROL_BLOCK*	ChildKCB;
/* off 0x0030 */	unsigned long	VolatileKeyCell;
struct
{
/* off 0x0030 */	unsigned long	OldValueCell;
union
{
struct
{
/* off 0x0034 */	unsigned long	NewValueCell;
};
/* off 0x0030 */	unsigned long	UserFlags;
/* off 0x0030 */	union _LARGE_INTEGER	LastWriteTime;
/* off 0x0030 */	unsigned long	TxSecurityCell;
struct
{
/* off 0x0030 */	struct _CM_KEY_CONTROL_BLOCK*	OldChildKCB;
};
struct
{
/* off 0x0034 */	struct _CM_KEY_CONTROL_BLOCK*	NewChildKCB;
};
struct
{
/* off 0x0030 */	struct _CM_KEY_CONTROL_BLOCK*	OtherChildKCB;
};
/* off 0x0034 */	unsigned long	ThisVolatileKeyCell;
};
};
};
};
enum UoWActionType
{
	UoWAddThisKey	=0x00000000	,//0
	UoWAddChildKey	=0x00000001	,//0
	UoWDeleteThisKey	=0x00000002	,//0
	UoWDeleteChildKey	=0x00000003	,//0
	UoWSetValueNew	=0x00000004	,//0
	UoWSetValueExisting	=0x00000005	,//0
	UoWDeleteValue	=0x00000006	,//0
	UoWSetKeyUserFlags	=0x00000007	,//0
	UoWSetLastWriteTime	=0x00000008	,//0
	UoWSetSecurityDescriptor	=0x00000009	,//0
	UoWRenameSubKey	=0x0000000a	,//0
	UoWRenameOldSubKey	=0x0000000b	,//0
	UoWRenameNewSubKey	=0x0000000c	,//0
	UoWIsolation	=0x0000000d	,//0
	UoWInvalid	=0x0000000e	,//0
};
enum HSTORAGE_TYPE
{
	Stable	=0x00000000	,//0
	Volatile	=0x00000001	,//0
	InvalidStorage	=0x00000002	,//0
};
struct _CM_WORKITEM /* sizeof 00000010 16 */
{
/* off 0x0000 */	struct _LIST_ENTRY	ListEntry;
/* off 0x0008 */	void( __stdcall *WorkerRoutine)(void*);
/* off 0x000c */	void*	Parameter;
};
struct _CM_CELL_REMAP_BLOCK /* sizeof 00000008 8 */
{
/* off 0x0000 */	unsigned long	OldCell;
/* off 0x0004 */	unsigned long	NewCell;
};
struct _GDI_TEB_BATCH /* sizeof 000004e0 1248 */
{
/* off 0x0000 */	unsigned long	Offset;
/* off 0x0004 */	unsigned long	HDC;
/* off 0x0008 */	unsigned long Buffer[310];
};
struct _TEB /* sizeof 00000ff8 4088 */
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
/* off 0x01a8 */	struct _ACTIVATION_CONTEXT_STACK*	ActivationContextStackPointer;
/* off 0x01ac */	unsigned char SpareBytes1[36];
/* off 0x01d0 */	unsigned long	TxFsContext;
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
/* off 0x0c00 */	wchar StaticUnicodeBuffer[261];
/* off 0x0e0c */	void*	DeallocationStack;
/* off 0x0e10 */	void* TlsSlots[64];
/* off 0x0f10 */	struct _LIST_ENTRY	TlsLinks;
/* off 0x0f18 */	void*	Vdm;
/* off 0x0f1c */	void*	ReservedForNtRpc;
/* off 0x0f20 */	void* DbgSsReserved[2];
/* off 0x0f28 */	unsigned long	HardErrorMode;
/* off 0x0f2c */	void* Instrumentation[9];
/* off 0x0f50 */	struct _GUID	ActivityId;
/* off 0x0f60 */	void*	SubProcessTag;
/* off 0x0f64 */	void*	EtwLocalData;
/* off 0x0f68 */	void*	EtwTraceData;
/* off 0x0f6c */	void*	WinSockData;
/* off 0x0f70 */	unsigned long	GdiBatchCount;
/* off 0x0f74 */	unsigned char	SpareBool0;
/* off 0x0f75 */	unsigned char	SpareBool1;
/* off 0x0f76 */	unsigned char	SpareBool2;
/* off 0x0f77 */	unsigned char	IdealProcessor;
/* off 0x0f78 */	unsigned long	GuaranteedStackBytes;
/* off 0x0f7c */	void*	ReservedForPerf;
/* off 0x0f80 */	void*	ReservedForOle;
/* off 0x0f84 */	unsigned long	WaitingOnLoaderLock;
/* off 0x0f88 */	void*	SavedPriorityState;
/* off 0x0f8c */	unsigned long	SoftPatchPtr1;
/* off 0x0f90 */	void*	ThreadPoolData;
/* off 0x0f94 */	void**	TlsExpansionSlots;
/* off 0x0f98 */	unsigned long	ImpersonationLocale;
/* off 0x0f9c */	unsigned long	IsImpersonating;
/* off 0x0fa0 */	void*	NlsCache;
/* off 0x0fa4 */	void*	pShimData;
/* off 0x0fa8 */	unsigned long	HeapVirtualAffinity;
/* off 0x0fac */	void*	CurrentTransactionHandle;
/* off 0x0fb0 */	struct _TEB_ACTIVE_FRAME*	ActiveFrame;
/* off 0x0fb4 */	void*	FlsData;
/* off 0x0fb8 */	void*	PreferredLanguages;
/* off 0x0fbc */	void*	UserPrefLanguages;
/* off 0x0fc0 */	void*	MergedPrefLanguages;
/* off 0x0fc4 */	unsigned long	MuiImpersonation;
union
{
/* off 0x0fc8 */	unsigned short	CrossTebFlags;
/* off 0x0fc8 */	unsigned short	SpareCrossTebBits:16	 /* start bit 0 */;
};
union
{
/* off 0x0fca */	unsigned short	SameTebFlags;
struct
{
/* off 0x0fca */	unsigned short	DbgSafeThunkCall:1	 /* start bit 0 */;
/* off 0x0fca */	unsigned short	DbgInDebugPrint:1	 /* start bit 1 */;
/* off 0x0fca */	unsigned short	DbgHasFiberData:1	 /* start bit 2 */;
/* off 0x0fca */	unsigned short	DbgSkipThreadAttach:1	 /* start bit 3 */;
/* off 0x0fca */	unsigned short	DbgWerInShipAssertCode:1	 /* start bit 4 */;
/* off 0x0fca */	unsigned short	DbgRanProcessInit:1	 /* start bit 5 */;
/* off 0x0fca */	unsigned short	DbgClonedThread:1	 /* start bit 6 */;
/* off 0x0fca */	unsigned short	DbgSuppressDebugMsg:1	 /* start bit 7 */;
/* off 0x0fca */	unsigned short	RtlDisableUserStackWalk:1	 /* start bit 8 */;
/* off 0x0fca */	unsigned short	RtlExceptionAttached:1	 /* start bit 9 */;
/* off 0x0fca */	unsigned short	SpareSameTebBits:6	 /* start bit 10 */;
};
};
/* off 0x0fcc */	void*	TxnScopeEnterCallback;
/* off 0x0fd0 */	void*	TxnScopeExitCallback;
/* off 0x0fd4 */	void*	TxnScopeContext;
/* off 0x0fd8 */	unsigned long	LockCount;
/* off 0x0fdc */	unsigned long	ProcessRundown;
/* off 0x0fe0 */	unsigned __int64	LastSwitchTime;
/* off 0x0fe8 */	unsigned __int64	TotalSwitchOutTime;
/* off 0x0ff0 */	union _LARGE_INTEGER	WaitReasonBitMap;
};
struct _ACTIVATION_CONTEXT_STACK /* sizeof 00000018 24 */
{
/* off 0x0000 */	struct _RTL_ACTIVATION_CONTEXT_STACK_FRAME*	ActiveFrame;
/* off 0x0004 */	struct _LIST_ENTRY	FrameListCache;
/* off 0x000c */	unsigned long	Flags;
/* off 0x0010 */	unsigned long	NextCookieSequenceNumber;
/* off 0x0014 */	unsigned long	StackId;
};
struct _RTL_ACTIVATION_CONTEXT_STACK_FRAME /* sizeof 0000000c 12 */
{
/* off 0x0000 */	struct _RTL_ACTIVATION_CONTEXT_STACK_FRAME*	Previous;
/* off 0x0004 */	struct _ACTIVATION_CONTEXT*	ActivationContext;
/* off 0x0008 */	unsigned long	Flags;
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
struct _KLOCK_QUEUE_HANDLE /* sizeof 0000000c 12 */
{
/* off 0x0000 */	struct _KSPIN_LOCK_QUEUE	LockQueue;
/* off 0x0008 */	unsigned char	OldIrql;
};
struct _KTIMER_TABLE_ENTRY /* sizeof 00000010 16 */
{
/* off 0x0000 */	struct _LIST_ENTRY	Entry;
/* off 0x0008 */	union _ULARGE_INTEGER	Time;
};
struct _KERNEL_STACK_SEGMENT /* sizeof 00000014 20 */
{
/* off 0x0000 */	unsigned long	StackBase;
/* off 0x0004 */	unsigned long	StackLimit;
/* off 0x0008 */	unsigned long	KernelStack;
/* off 0x000c */	unsigned long	InitialStack;
/* off 0x0010 */	unsigned long	ActualLimit;
};
struct _KERNEL_STACK_CONTROL /* sizeof 0000001c 28 */
{
union
{
/* off 0x0000 */	struct _KTRAP_FRAME*	PreviousTrapFrame;
/* off 0x0000 */	void*	PreviousExceptionList;
};
union
{
/* off 0x0004 */	unsigned long	StackControlFlags;
struct
{
/* off 0x0004 */	unsigned long	PreviousLargeStack:1	 /* start bit 0 */;
/* off 0x0004 */	unsigned long	PreviousSegmentsPresent:1	 /* start bit 1 */;
/* off 0x0004 */	unsigned long	ExpandCalloutStack:1	 /* start bit 2 */;
};
};
/* off 0x0008 */	struct _KERNEL_STACK_SEGMENT	Previous;
};
struct _PNP_DEVICE_COMPLETION_QUEUE /* sizeof 0000002c 44 */
{
/* off 0x0000 */	unsigned long	SpinLock;
/* off 0x0004 */	unsigned long	DispatchedCount;
/* off 0x0008 */	struct _LIST_ENTRY	DispatchedList;
/* off 0x0010 */	struct _KSEMAPHORE	CompletedSemaphore;
/* off 0x0024 */	struct _LIST_ENTRY	CompletedList;
};
struct _PO_DEVICE_NOTIFY /* sizeof 00000024 36 */
{
/* off 0x0000 */	struct _LIST_ENTRY	Link;
/* off 0x0008 */	struct _DEVICE_OBJECT*	TargetDevice;
/* off 0x000c */	unsigned char	OrderLevel;
/* off 0x0010 */	struct _DEVICE_OBJECT*	DeviceObject;
/* off 0x0014 */	unsigned short*	DeviceName;
/* off 0x0018 */	unsigned short*	DriverName;
/* off 0x001c */	unsigned long	ChildCount;
/* off 0x0020 */	unsigned long	ActiveChild;
};
struct _PO_IRP_QUEUE /* sizeof 00000008 8 */
{
/* off 0x0000 */	struct _IRP*	CurrentIrp;
/* off 0x0004 */	struct _IRP*	PendingIrpList;
};
struct _PO_IRP_MANAGER /* sizeof 00000010 16 */
{
/* off 0x0000 */	struct _PO_IRP_QUEUE	DeviceIrpQueue;
/* off 0x0008 */	struct _PO_IRP_QUEUE	SystemIrpQueue;
};
struct _DEVICE_NODE /* sizeof 00000158 344 */
{
/* off 0x0000 */	struct _DEVICE_NODE*	Sibling;
/* off 0x0004 */	struct _DEVICE_NODE*	Child;
/* off 0x0008 */	struct _DEVICE_NODE*	Parent;
/* off 0x000c */	struct _DEVICE_NODE*	LastChild;
/* off 0x0010 */	unsigned long	Level;
/* off 0x0014 */	struct _PO_DEVICE_NOTIFY	Notify;
/* off 0x0038 */	struct _PO_IRP_MANAGER	PoIrpManager;
/* off 0x0048 */	enum _PNP_DEVNODE_STATE	State;
/* off 0x004c */	enum _PNP_DEVNODE_STATE	PreviousState;
/* off 0x0050 */	enum _PNP_DEVNODE_STATE StateHistory[20];
/* off 0x00a0 */	unsigned long	StateHistoryEntry;
/* off 0x00a4 */	long	CompletionStatus;
/* off 0x00a8 */	struct _IRP*	PendingIrp;
/* off 0x00ac */	unsigned long	Flags;
/* off 0x00b0 */	unsigned long	UserFlags;
/* off 0x00b4 */	unsigned long	Problem;
/* off 0x00b8 */	struct _DEVICE_OBJECT*	PhysicalDeviceObject;
/* off 0x00bc */	struct _CM_RESOURCE_LIST*	ResourceList;
/* off 0x00c0 */	struct _CM_RESOURCE_LIST*	ResourceListTranslated;
/* off 0x00c4 */	struct _UNICODE_STRING	InstancePath;
/* off 0x00cc */	struct _UNICODE_STRING	ServiceName;
/* off 0x00d4 */	struct _DEVICE_OBJECT*	DuplicatePDO;
/* off 0x00d8 */	struct _IO_RESOURCE_REQUIREMENTS_LIST*	ResourceRequirements;
/* off 0x00dc */	enum _INTERFACE_TYPE	InterfaceType;
/* off 0x00e0 */	unsigned long	BusNumber;
/* off 0x00e4 */	enum _INTERFACE_TYPE	ChildInterfaceType;
/* off 0x00e8 */	unsigned long	ChildBusNumber;
/* off 0x00ec */	unsigned short	ChildBusTypeIndex;
/* off 0x00ee */	unsigned char	RemovalPolicy;
/* off 0x00ef */	unsigned char	HardwareRemovalPolicy;
/* off 0x00f0 */	struct _LIST_ENTRY	TargetDeviceNotify;
/* off 0x00f8 */	struct _LIST_ENTRY	DeviceArbiterList;
/* off 0x0100 */	struct _LIST_ENTRY	DeviceTranslatorList;
/* off 0x0108 */	unsigned short	NoTranslatorMask;
/* off 0x010a */	unsigned short	QueryTranslatorMask;
/* off 0x010c */	unsigned short	NoArbiterMask;
/* off 0x010e */	unsigned short	QueryArbiterMask;
/* off 0x0110 */	
	union  /* sizeof 00000004 4 */
	{
	/* off 0x0000 */	struct _DEVICE_NODE*	LegacyDeviceNode;
	/* off 0x0000 */	struct _DEVICE_RELATIONS*	PendingDeviceRelations;
	/* off 0x0000 */	void*	Information;
	}	OverUsed1;
/* off 0x0114 */	
	union  /* sizeof 00000004 4 */
	{
	/* off 0x0000 */	struct _DEVICE_NODE*	NextResourceDeviceNode;
	}	OverUsed2;
/* off 0x0118 */	struct _CM_RESOURCE_LIST*	BootResources;
/* off 0x011c */	struct _CM_RESOURCE_LIST*	BootResourcesTranslated;
/* off 0x0120 */	unsigned long	CapabilityFlags;
/* off 0x0124 */	
	struct  /* sizeof 00000010 16 */
	{
	/* off 0x0000 */	enum PROFILE_STATUS	DockStatus;
	/* off 0x0004 */	struct _LIST_ENTRY	ListEntry;
	/* off 0x000c */	unsigned short*	SerialNumber;
	}	DockInfo;
/* off 0x0134 */	unsigned long	DisableableDepends;
/* off 0x0138 */	struct _LIST_ENTRY	PendedSetInterfaceState;
/* off 0x0140 */	struct _LIST_ENTRY	LegacyBusListEntry;
/* off 0x0148 */	unsigned long	DriverUnloadRetryCount;
/* off 0x014c */	struct _DEVICE_NODE*	PreviousParent;
/* off 0x0150 */	unsigned long	DeletedChildren;
/* off 0x0154 */	unsigned long	NumaNodeIndex;
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
	MaxDeviceNodeState	=0x00000315	,//0
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
struct _PNP_ASSIGN_RESOURCES_CONTEXT /* sizeof 0000000c 12 */
{
/* off 0x0000 */	unsigned long	IncludeFailedDevices;
/* off 0x0004 */	unsigned long	DeviceCount;
/* off 0x0008 */	struct _DEVICE_OBJECT* DeviceList[1];
};
struct _PNP_RESOURCE_REQUEST /* sizeof 00000028 40 */
{
/* off 0x0000 */	struct _DEVICE_OBJECT*	PhysicalDevice;
/* off 0x0004 */	unsigned long	Flags;
/* off 0x0008 */	enum _ARBITER_REQUEST_SOURCE	AllocationType;
/* off 0x000c */	unsigned long	Priority;
/* off 0x0010 */	unsigned long	Position;
/* off 0x0014 */	struct _IO_RESOURCE_REQUIREMENTS_LIST*	ResourceRequirements;
/* off 0x0018 */	void*	ReqList;
/* off 0x001c */	struct _CM_RESOURCE_LIST*	ResourceAssignment;
/* off 0x0020 */	struct _CM_RESOURCE_LIST*	TranslatedResourceAssignment;
/* off 0x0024 */	long	Status;
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
struct _ARM_DBGKD_CONTROL_SET /* sizeof 0000000c 12 */
{
/* off 0x0000 */	unsigned long	Continue;
/* off 0x0004 */	unsigned long	CurrentSymbolStart;
/* off 0x0008 */	unsigned long	CurrentSymbolEnd;
};
struct _DBGKD_ANY_CONTROL_SET /* sizeof 0000001c 28 */
{
union
{
/* off 0x0000 */	struct _X86_DBGKD_CONTROL_SET	X86ControlSet;
/* off 0x0000 */	unsigned long	AlphaControlSet;
/* off 0x0000 */	struct _IA64_DBGKD_CONTROL_SET	IA64ControlSet;
/* off 0x0000 */	struct _AMD64_DBGKD_CONTROL_SET	Amd64ControlSet;
/* off 0x0000 */	struct _ARM_DBGKD_CONTROL_SET	ArmControlSet;
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
/* off 0x0004 */	unsigned char	ProtocolVersion;
/* off 0x0005 */	unsigned char	KdSecondaryVersion;
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
struct _DBGKD_SWITCH_PARTITION /* sizeof 00000004 4 */
{
/* off 0x0000 */	unsigned long	Partition;
};
struct _DBGKD_MANIPULATE_STATE64 /* sizeof 00000038 56 */
{
/* off 0x0000 */	unsigned long	ApiNumber;
/* off 0x0004 */	unsigned short	ProcessorLevel;
/* off 0x0006 */	unsigned short	Processor;
/* off 0x0008 */	long	ReturnStatus;
/* off 0x0010 */	
	union  /* sizeof 00000028 40 */
	{
	/* off 0x0000 */	struct _DBGKD_READ_MEMORY64	ReadMemory;
	/* off 0x0000 */	struct _DBGKD_WRITE_MEMORY64	WriteMemory;
	/* off 0x0000 */	struct _DBGKD_GET_CONTEXT	GetContext;
	/* off 0x0000 */	struct _DBGKD_SET_CONTEXT	SetContext;
	/* off 0x0000 */	struct _DBGKD_WRITE_BREAKPOINT64	WriteBreakPoint;
	/* off 0x0000 */	struct _DBGKD_RESTORE_BREAKPOINT	RestoreBreakPoint;
	/* off 0x0000 */	struct _DBGKD_CONTINUE	Continue;
	/* off 0x0000 */	struct _DBGKD_CONTINUE2	Continue2;
	/* off 0x0000 */	struct _DBGKD_READ_WRITE_IO64	ReadWriteIo;
	/* off 0x0000 */	struct _DBGKD_READ_WRITE_IO_EXTENDED64	ReadWriteIoExtended;
	/* off 0x0000 */	struct _DBGKD_QUERY_SPECIAL_CALLS	QuerySpecialCalls;
	/* off 0x0000 */	struct _DBGKD_SET_SPECIAL_CALL64	SetSpecialCall;
	/* off 0x0000 */	struct _DBGKD_SET_INTERNAL_BREAKPOINT64	SetInternalBreakpoint;
	/* off 0x0000 */	struct _DBGKD_GET_INTERNAL_BREAKPOINT64	GetInternalBreakpoint;
	/* off 0x0000 */	struct _DBGKD_GET_VERSION64	GetVersion64;
	/* off 0x0000 */	struct _DBGKD_BREAKPOINTEX	BreakPointEx;
	/* off 0x0000 */	struct _DBGKD_READ_WRITE_MSR	ReadWriteMsr;
	/* off 0x0000 */	struct _DBGKD_SEARCH_MEMORY	SearchMemory;
	/* off 0x0000 */	struct _DBGKD_GET_SET_BUS_DATA	GetSetBusData;
	/* off 0x0000 */	struct _DBGKD_FILL_MEMORY	FillMemory;
	/* off 0x0000 */	struct _DBGKD_QUERY_MEMORY	QueryMemory;
	/* off 0x0000 */	struct _DBGKD_SWITCH_PARTITION	SwitchPartition;
	}	u;
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
struct _DBGKD_MANIPULATE_STATE32 /* sizeof 00000034 52 */
{
/* off 0x0000 */	unsigned long	ApiNumber;
/* off 0x0004 */	unsigned short	ProcessorLevel;
/* off 0x0006 */	unsigned short	Processor;
/* off 0x0008 */	long	ReturnStatus;
/* off 0x000c */	
	union  /* sizeof 00000028 40 */
	{
	/* off 0x0000 */	struct _DBGKD_READ_MEMORY32	ReadMemory;
	/* off 0x0000 */	struct _DBGKD_WRITE_MEMORY32	WriteMemory;
	/* off 0x0000 */	struct _DBGKD_READ_MEMORY64	ReadMemory64;
	/* off 0x0000 */	struct _DBGKD_WRITE_MEMORY64	WriteMemory64;
	/* off 0x0000 */	struct _DBGKD_GET_CONTEXT	GetContext;
	/* off 0x0000 */	struct _DBGKD_SET_CONTEXT	SetContext;
	/* off 0x0000 */	struct _DBGKD_WRITE_BREAKPOINT32	WriteBreakPoint;
	/* off 0x0000 */	struct _DBGKD_RESTORE_BREAKPOINT	RestoreBreakPoint;
	/* off 0x0000 */	struct _DBGKD_CONTINUE	Continue;
	/* off 0x0000 */	struct _DBGKD_CONTINUE2	Continue2;
	/* off 0x0000 */	struct _DBGKD_READ_WRITE_IO32	ReadWriteIo;
	/* off 0x0000 */	struct _DBGKD_READ_WRITE_IO_EXTENDED32	ReadWriteIoExtended;
	/* off 0x0000 */	struct _DBGKD_QUERY_SPECIAL_CALLS	QuerySpecialCalls;
	/* off 0x0000 */	struct _DBGKD_SET_SPECIAL_CALL32	SetSpecialCall;
	/* off 0x0000 */	struct _DBGKD_SET_INTERNAL_BREAKPOINT32	SetInternalBreakpoint;
	/* off 0x0000 */	struct _DBGKD_GET_INTERNAL_BREAKPOINT32	GetInternalBreakpoint;
	/* off 0x0000 */	struct _DBGKD_GET_VERSION32	GetVersion32;
	/* off 0x0000 */	struct _DBGKD_BREAKPOINTEX	BreakPointEx;
	/* off 0x0000 */	struct _DBGKD_READ_WRITE_MSR	ReadWriteMsr;
	/* off 0x0000 */	struct _DBGKD_SEARCH_MEMORY	SearchMemory;
	}	u;
};
struct _POP_CPU_INFO /* sizeof 00000010 16 */
{
/* off 0x0000 */	unsigned long	Eax;
/* off 0x0004 */	unsigned long	Ebx;
/* off 0x0008 */	unsigned long	Ecx;
/* off 0x000c */	unsigned long	Edx;
};
struct _VOLUME_CACHE_MAP /* sizeof 00000018 24 */
{
/* off 0x0000 */	short	NodeTypeCode;
/* off 0x0002 */	short	NodeByteCode;
/* off 0x0004 */	unsigned long	UseCount;
/* off 0x0008 */	struct _DEVICE_OBJECT*	DeviceObject;
/* off 0x000c */	struct _LIST_ENTRY	VolumeCacheMapLinks;
/* off 0x0014 */	unsigned long	Flags;
};
struct _PRIVATE_CACHE_MAP_FLAGS /* sizeof 00000004 4 */
{
/* off 0x0000 */	unsigned long	DontUse:16	 /* start bit 0 */;
/* off 0x0000 */	unsigned long	ReadAheadActive:1	 /* start bit 16 */;
/* off 0x0000 */	unsigned long	ReadAheadEnabled:1	 /* start bit 17 */;
/* off 0x0000 */	unsigned long	PagePriority:3	 /* start bit 18 */;
/* off 0x0000 */	unsigned long	Available:11	 /* start bit 21 */;
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
/* off 0x0054 */	void*	ReadAheadWorkItem;
};
struct _SHARED_CACHE_MAP /* sizeof 00000140 320 */
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
/* off 0x0044 */	struct _EX_FAST_REF	FileObjectFastRef;
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
/* off 0x00a4 */	void( __stdcall *FlushToLsnRoutine)(void*,union _LARGE_INTEGER);
/* off 0x00a8 */	unsigned long	DirtyPageThreshold;
/* off 0x00ac */	unsigned long	LazyWritePassCount;
/* off 0x00b0 */	struct _CACHE_UNINITIALIZE_EVENT*	UninitializeEvent;
/* off 0x00b4 */	struct _VACB*	NeedToZeroVacb;
/* off 0x00b8 */	unsigned long	BcbSpinLock;
/* off 0x00bc */	void*	Reserved;
/* off 0x00c0 */	struct _KEVENT	Event;
/* off 0x00d0 */	union _LARGE_INTEGER	HighWaterMappingOffset;
/* off 0x00d8 */	struct _PRIVATE_CACHE_MAP	PrivateCacheMap;
/* off 0x0130 */	void*	WriteBehindWorkQueueEntry;
/* off 0x0134 */	struct _VOLUME_CACHE_MAP*	VolumeCacheMap;
/* off 0x0138 */	unsigned long	ProcImagePathHash;
/* off 0x013c */	unsigned long	MappedWritesInProgress;
};
struct _VACB /* sizeof 00000020 32 */
{
/* off 0x0000 */	void*	BaseAddress;
/* off 0x0004 */	struct _SHARED_CACHE_MAP*	SharedCacheMap;
/* off 0x0008 */	
	union  /* sizeof 00000008 8 */
	{
	/* off 0x0000 */	union _LARGE_INTEGER	FileOffset;
	/* off 0x0000 */	unsigned short	ActiveCount;
	}	Overlay;
/* off 0x0010 */	struct _LIST_ENTRY	LruList;
/* off 0x0018 */	struct _VACB_ARRAY_HEADER*	ArrayHead;
};
struct _VACB_ARRAY_HEADER /* sizeof 00000010 16 */
{
/* off 0x0000 */	struct _LIST_ENTRY	Links;
/* off 0x0008 */	unsigned long	MappingCount;
/* off 0x000c */	unsigned long	Reserved;
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
/* off 0x0000 */	unsigned char( __stdcall *AcquireForLazyWrite)(void*,unsigned char);
/* off 0x0004 */	void( __stdcall *ReleaseFromLazyWrite)(void*);
/* off 0x0008 */	unsigned char( __stdcall *AcquireForReadAhead)(void*,unsigned char);
/* off 0x000c */	void( __stdcall *ReleaseFromReadAhead)(void*);
};
struct _CACHE_UNINITIALIZE_EVENT /* sizeof 00000014 20 */
{
/* off 0x0000 */	struct _CACHE_UNINITIALIZE_EVENT*	Next;
/* off 0x0004 */	struct _KEVENT	Event;
};
struct _WORK_QUEUE_ENTRY /* sizeof 00000018 24 */
{
/* off 0x0000 */	struct _LIST_ENTRY	WorkQueueLinks;
/* off 0x0008 */	struct _LIST_ENTRY	CoalescedWorkQueueLinks;
/* off 0x0010 */	
	union  /* sizeof 00000004 4 */
	{
	/* off 0x0000 */	
		struct  /* sizeof 00000004 4 */
		{
		/* off 0x0000 */	struct _FILE_OBJECT*	FileObject;
		}	Read;
	/* off 0x0000 */	
		struct  /* sizeof 00000004 4 */
		{
		/* off 0x0000 */	struct _SHARED_CACHE_MAP*	SharedCacheMap;
		}	Write;
	/* off 0x0000 */	
		struct  /* sizeof 00000004 4 */
		{
		/* off 0x0000 */	struct _KEVENT*	Event;
		}	Event;
	/* off 0x0000 */	
		struct  /* sizeof 00000004 4 */
		{
		/* off 0x0000 */	unsigned long	Reason;
		}	Notification;
	}	Parameters;
/* off 0x0014 */	unsigned char	Function;
};
struct _VACB_LEVEL_REFERENCE /* sizeof 00000008 8 */
{
/* off 0x0000 */	long	Reference;
/* off 0x0004 */	long	SpecialReference;
};
struct _HEAP_LIST_LOOKUP /* sizeof 00000024 36 */
{
/* off 0x0000 */	struct _HEAP_LIST_LOOKUP*	ExtendedLookup;
/* off 0x0004 */	unsigned long	ArraySize;
/* off 0x0008 */	unsigned long	ExtraItem;
/* off 0x000c */	unsigned long	ItemCount;
/* off 0x0010 */	unsigned long	OutOfRangeItems;
/* off 0x0014 */	unsigned long	BaseIndex;
/* off 0x0018 */	struct _LIST_ENTRY*	ListHead;
/* off 0x001c */	unsigned long*	ListsInUseUlong;
/* off 0x0020 */	struct _LIST_ENTRY**	ListHints;
};
struct _HEAP_ENTRY /* sizeof 00000008 8 */
{
union
{
struct
{
/* off 0x0000 */	unsigned short	Size;
union
{
struct
{
/* off 0x0002 */	unsigned char	Flags;
/* off 0x0003 */	unsigned char	SmallTagIndex;
};
struct
{
/* off 0x0000 */	void*	SubSegmentCode;
union
{
struct
{
/* off 0x0004 */	unsigned short	PreviousSize;
union
{
/* off 0x0006 */	unsigned char	SegmentOffset;
struct
{
/* off 0x0006 */	unsigned char	LFHFlags;
union
{
struct
{
/* off 0x0007 */	unsigned char	UnusedBytes;
};
struct
{
/* off 0x0000 */	unsigned short	FunctionIndex;
};
struct
{
/* off 0x0002 */	unsigned short	ContextValue;
};
};
};
struct
{
/* off 0x0000 */	unsigned long	InterceptorValue;
};
struct
{
/* off 0x0004 */	unsigned short	UnusedBytesLength;
};
struct
{
/* off 0x0006 */	unsigned char	EntryOffset;
};
struct
{
/* off 0x0007 */	unsigned char	ExtendedBlockSignature;
};
struct
{
/* off 0x0000 */	unsigned long	Code1;
};
struct
{
/* off 0x0004 */	unsigned short	Code2;
};
};
};
struct
{
/* off 0x0006 */	unsigned char	Code3;
};
};
};
struct
{
/* off 0x0007 */	unsigned char	Code4;
};
};
};
/* off 0x0000 */	unsigned __int64	AgregateCode;
};
};
struct _HEAP_COUNTERS /* sizeof 00000048 72 */
{
/* off 0x0000 */	unsigned long	TotalMemoryReserved;
/* off 0x0004 */	unsigned long	TotalMemoryCommitted;
/* off 0x0008 */	unsigned long	TotalMemoryLargeUCR;
/* off 0x000c */	unsigned long	TotalSizeInVirtualBlocks;
/* off 0x0010 */	unsigned long	TotalSegments;
/* off 0x0014 */	unsigned long	TotalUCRs;
/* off 0x0018 */	unsigned long	CommittOps;
/* off 0x001c */	unsigned long	DeCommitOps;
/* off 0x0020 */	unsigned long	LockAcquires;
/* off 0x0024 */	unsigned long	LockCollisions;
/* off 0x0028 */	unsigned long	CommitRate;
/* off 0x002c */	unsigned long	DecommittRate;
/* off 0x0030 */	unsigned long	CommitFailures;
/* off 0x0034 */	unsigned long	InBlockCommitFailures;
/* off 0x0038 */	unsigned long	CompactHeapCalls;
/* off 0x003c */	unsigned long	CompactedUCRs;
/* off 0x0040 */	unsigned long	InBlockDeccommits;
/* off 0x0044 */	unsigned long	InBlockDeccomitSize;
};
struct _HEAP_TUNING_PARAMETERS /* sizeof 00000008 8 */
{
/* off 0x0000 */	unsigned long	CommittThresholdShift;
/* off 0x0004 */	unsigned long	MaxPreCommittThreshold;
};
struct _HEAP /* sizeof 00000130 304 */
{
/* off 0x0000 */	struct _HEAP_ENTRY	Entry;
/* off 0x0008 */	unsigned long	SegmentSignature;
/* off 0x000c */	unsigned long	SegmentFlags;
/* off 0x0010 */	struct _LIST_ENTRY	SegmentListEntry;
/* off 0x0018 */	struct _HEAP*	Heap;
/* off 0x001c */	void*	BaseAddress;
/* off 0x0020 */	unsigned long	NumberOfPages;
/* off 0x0024 */	struct _HEAP_ENTRY*	FirstEntry;
/* off 0x0028 */	struct _HEAP_ENTRY*	LastValidEntry;
/* off 0x002c */	unsigned long	NumberOfUnCommittedPages;
/* off 0x0030 */	unsigned long	NumberOfUnCommittedRanges;
/* off 0x0034 */	unsigned short	SegmentAllocatorBackTraceIndex;
/* off 0x0036 */	unsigned short	Reserved;
/* off 0x0038 */	struct _LIST_ENTRY	UCRSegmentList;
/* off 0x0040 */	unsigned long	Flags;
/* off 0x0044 */	unsigned long	ForceFlags;
/* off 0x0048 */	unsigned long	CompatibilityFlags;
/* off 0x004c */	unsigned long	EncodeFlagMask;
/* off 0x0050 */	struct _HEAP_ENTRY	Encoding;
/* off 0x0058 */	unsigned long	PointerKey;
/* off 0x005c */	unsigned long	Interceptor;
/* off 0x0060 */	unsigned long	VirtualMemoryThreshold;
/* off 0x0064 */	unsigned long	Signature;
/* off 0x0068 */	unsigned long	SegmentReserve;
/* off 0x006c */	unsigned long	SegmentCommit;
/* off 0x0070 */	unsigned long	DeCommitFreeBlockThreshold;
/* off 0x0074 */	unsigned long	DeCommitTotalFreeThreshold;
/* off 0x0078 */	unsigned long	TotalFreeSize;
/* off 0x007c */	unsigned long	MaximumAllocationSize;
/* off 0x0080 */	unsigned short	ProcessHeapsListIndex;
/* off 0x0082 */	unsigned short	HeaderValidateLength;
/* off 0x0084 */	void*	HeaderValidateCopy;
/* off 0x0088 */	unsigned short	NextAvailableTagIndex;
/* off 0x008a */	unsigned short	MaximumTagIndex;
/* off 0x008c */	struct _HEAP_TAG_ENTRY*	TagEntries;
/* off 0x0090 */	struct _LIST_ENTRY	UCRList;
/* off 0x0098 */	unsigned long	AlignRound;
/* off 0x009c */	unsigned long	AlignMask;
/* off 0x00a0 */	struct _LIST_ENTRY	VirtualAllocdBlocks;
/* off 0x00a8 */	struct _LIST_ENTRY	SegmentList;
/* off 0x00b0 */	unsigned short	AllocatorBackTraceIndex;
/* off 0x00b4 */	unsigned long	NonDedicatedListLength;
/* off 0x00b8 */	void*	BlocksIndex;
/* off 0x00bc */	void*	UCRIndex;
/* off 0x00c0 */	struct _HEAP_PSEUDO_TAG_ENTRY*	PseudoTagEntries;
/* off 0x00c4 */	struct _LIST_ENTRY	FreeLists;
/* off 0x00cc */	struct _HEAP_LOCK*	LockVariable;
/* off 0x00d0 */	long( __stdcall *CommitRoutine)(void*,void**,unsigned long*);
/* off 0x00d4 */	void*	FrontEndHeap;
/* off 0x00d8 */	unsigned short	FrontHeapLockCount;
/* off 0x00da */	unsigned char	FrontEndHeapType;
/* off 0x00dc */	struct _HEAP_COUNTERS	Counters;
/* off 0x0124 */	struct _HEAP_TUNING_PARAMETERS	TuningParameters;
};
struct _HEAP_TAG_ENTRY /* sizeof 00000040 64 */
{
/* off 0x0000 */	unsigned long	Allocs;
/* off 0x0004 */	unsigned long	Frees;
/* off 0x0008 */	unsigned long	Size;
/* off 0x000c */	unsigned short	TagIndex;
/* off 0x000e */	unsigned short	CreatorBackTraceIndex;
/* off 0x0010 */	wchar TagName[24];
};
struct _HEAP_PSEUDO_TAG_ENTRY /* sizeof 0000000c 12 */
{
/* off 0x0000 */	unsigned long	Allocs;
/* off 0x0004 */	unsigned long	Frees;
/* off 0x0008 */	unsigned long	Size;
};
struct _HEAP_LOCK /* sizeof 00000018 24 */
{
/* off 0x0000 */	
	union  /* sizeof 00000018 24 */
	{
	/* off 0x0000 */	struct _RTL_CRITICAL_SECTION	CriticalSection;
	}	Lock;
};
struct _HEAP_SEGMENT /* sizeof 00000040 64 */
{
/* off 0x0000 */	struct _HEAP_ENTRY	Entry;
/* off 0x0008 */	unsigned long	SegmentSignature;
/* off 0x000c */	unsigned long	SegmentFlags;
/* off 0x0010 */	struct _LIST_ENTRY	SegmentListEntry;
/* off 0x0018 */	struct _HEAP*	Heap;
/* off 0x001c */	void*	BaseAddress;
/* off 0x0020 */	unsigned long	NumberOfPages;
/* off 0x0024 */	struct _HEAP_ENTRY*	FirstEntry;
/* off 0x0028 */	struct _HEAP_ENTRY*	LastValidEntry;
/* off 0x002c */	unsigned long	NumberOfUnCommittedPages;
/* off 0x0030 */	unsigned long	NumberOfUnCommittedRanges;
/* off 0x0034 */	unsigned short	SegmentAllocatorBackTraceIndex;
/* off 0x0036 */	unsigned short	Reserved;
/* off 0x0038 */	struct _LIST_ENTRY	UCRSegmentList;
};
struct _HEAP_FREE_ENTRY /* sizeof 00000010 16 */
{
union
{
struct
{
/* off 0x0000 */	unsigned short	Size;
union
{
struct
{
/* off 0x0002 */	unsigned char	Flags;
/* off 0x0003 */	unsigned char	SmallTagIndex;
};
struct
{
/* off 0x0000 */	void*	SubSegmentCode;
union
{
struct
{
/* off 0x0004 */	unsigned short	PreviousSize;
union
{
/* off 0x0006 */	unsigned char	SegmentOffset;
struct
{
/* off 0x0006 */	unsigned char	LFHFlags;
union
{
struct
{
/* off 0x0007 */	unsigned char	UnusedBytes;
};
struct
{
/* off 0x0000 */	unsigned short	FunctionIndex;
};
struct
{
/* off 0x0002 */	unsigned short	ContextValue;
};
};
};
struct
{
/* off 0x0000 */	unsigned long	InterceptorValue;
};
struct
{
/* off 0x0004 */	unsigned short	UnusedBytesLength;
};
struct
{
/* off 0x0006 */	unsigned char	EntryOffset;
};
struct
{
/* off 0x0007 */	unsigned char	ExtendedBlockSignature;
};
struct
{
/* off 0x0000 */	unsigned long	Code1;
};
struct
{
/* off 0x0004 */	unsigned short	Code2;
};
};
};
struct
{
/* off 0x0006 */	unsigned char	Code3;
};
};
};
struct
{
/* off 0x0007 */	unsigned char	Code4;
};
struct
{
};
};
/* off 0x0000 */	unsigned __int64	AgregateCode;
};
};
/* off 0x0008 */	struct _LIST_ENTRY	FreeList;
};
enum _HEAP_FAILURE_TYPE
{
	heap_failure_internal	=0x00000000	,//0
	heap_failure_unknown	=0x00000001	,//0
	heap_failure_generic	=0x00000002	,//0
	heap_failure_entry_corruption	=0x00000003	,//0
	heap_failure_multiple_entries_corruption	=0x00000004	,//0
	heap_failure_virtual_block_corruption	=0x00000005	,//0
	heap_failure_buffer_overrun	=0x00000006	,//0
	heap_failure_buffer_underrun	=0x00000007	,//0
	heap_failure_block_not_busy	=0x00000008	,//0
	heap_failure_invalid_argument	=0x00000009	,//0
	heap_failure_usage_after_free	=0x0000000a	,//0
	heap_failure_cross_heap_operation	=0x0000000b	,//0
	heap_failure_freelists_corruption	=0x0000000c	,//0
	heap_failure_listentry_corruption	=0x0000000d	,//0
};
struct _LDR_DATA_TABLE_ENTRY /* sizeof 00000068 104 */
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
/* off 0x0048 */	struct _ACTIVATION_CONTEXT*	EntryPointActivationContext;
/* off 0x004c */	void*	PatchInformation;
/* off 0x0050 */	struct _LIST_ENTRY	ForwarderLinks;
/* off 0x0058 */	struct _LIST_ENTRY	ServiceTagLinks;
/* off 0x0060 */	struct _LIST_ENTRY	StaticLinks;
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
/* off 0x0000 */	struct _HEAP_LOCAL_SEGMENT_INFO*	LocalInfo;
/* off 0x0004 */	struct _HEAP_USERDATA_HEADER*	UserBlocks;
/* off 0x0008 */	struct _INTERLOCK_SEQ	AggregateExchg;
union
{
struct
{
/* off 0x0010 */	unsigned short	BlockSize;
/* off 0x0012 */	unsigned short	Flags;
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
struct _HEAP_LOCAL_SEGMENT_INFO /* sizeof 00000000 0 */
{
};
struct _HEAP_USERDATA_HEADER /* sizeof 00000010 16 */
{
union
{
/* off 0x0000 */	struct _SINGLE_LIST_ENTRY	SFreeListEntry;
/* off 0x0000 */	struct _HEAP_SUBSEGMENT*	SubSegment;
};
/* off 0x0004 */	void*	Reserved;
/* off 0x0008 */	unsigned long	SizeIndex;
/* off 0x000c */	unsigned long	Signature;
};
struct _ETW_SYSTEMTIME /* sizeof 00000010 16 */
{
/* off 0x0000 */	unsigned short	Year;
/* off 0x0002 */	unsigned short	Month;
/* off 0x0004 */	unsigned short	DayOfWeek;
/* off 0x0006 */	unsigned short	Day;
/* off 0x0008 */	unsigned short	Hour;
/* off 0x000a */	unsigned short	Minute;
/* off 0x000c */	unsigned short	Second;
/* off 0x000e */	unsigned short	Milliseconds;
};
struct _TIME_FIELDS /* sizeof 00000010 16 */
{
/* off 0x0000 */	short	Year;
/* off 0x0002 */	short	Month;
/* off 0x0004 */	short	Day;
/* off 0x0006 */	short	Hour;
/* off 0x0008 */	short	Minute;
/* off 0x000a */	short	Second;
/* off 0x000c */	short	Milliseconds;
/* off 0x000e */	short	Weekday;
};
struct _ETW_REF_CLOCK /* sizeof 00000010 16 */
{
/* off 0x0000 */	union _LARGE_INTEGER	StartTime;
/* off 0x0008 */	union _LARGE_INTEGER	StartPerfClock;
};
struct _TOKEN_SOURCE /* sizeof 00000010 16 */
{
/* off 0x0000 */	char SourceName[8];
/* off 0x0008 */	struct _LUID	SourceIdentifier;
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
struct _WNODE_HEADER /* sizeof 00000030 48 */
{
/* off 0x0000 */	unsigned long	BufferSize;
/* off 0x0004 */	unsigned long	ProviderId;
union
{
/* off 0x0008 */	unsigned __int64	HistoricalContext;
struct
{
/* off 0x0008 */	unsigned long	Version;
/* off 0x000c */	unsigned long	Linkage;
};
};
union
{
/* off 0x0010 */	unsigned long	CountLost;
/* off 0x0010 */	void*	KernelHandle;
/* off 0x0010 */	union _LARGE_INTEGER	TimeStamp;
};
/* off 0x0018 */	struct _GUID	Guid;
/* off 0x0028 */	unsigned long	ClientContext;
/* off 0x002c */	unsigned long	Flags;
};
struct _ETW_BUFFER_CONTEXT /* sizeof 00000004 4 */
{
/* off 0x0000 */	unsigned char	ProcessorNumber;
/* off 0x0001 */	unsigned char	Alignment;
/* off 0x0002 */	unsigned short	LoggerId;
};
struct _WMI_BUFFER_HEADER /* sizeof 00000048 72 */
{
union
{
/* off 0x0000 */	struct _WNODE_HEADER	Wnode;
struct
{
/* off 0x0000 */	unsigned long	BufferSize;
/* off 0x0004 */	unsigned long	SavedOffset;
/* off 0x0008 */	unsigned long	CurrentOffset;
/* off 0x000c */	long	ReferenceCount;
union
{
/* off 0x0010 */	union _LARGE_INTEGER	TimeStamp;
/* off 0x0010 */	union _LARGE_INTEGER	StartPerfClock;
};
/* off 0x0018 */	__int64	SequenceNumber;
union
{
/* off 0x0020 */	unsigned long Padding0[2];
/* off 0x0020 */	struct _SINGLE_LIST_ENTRY	SlistEntry;
/* off 0x0020 */	struct _WMI_BUFFER_HEADER*	NextBuffer;
};
/* off 0x0028 */	struct _ETW_BUFFER_CONTEXT	ClientContext;
union
{
/* off 0x002c */	enum _ETW_BUFFER_STATE	State;
/* off 0x002c */	unsigned long	Flags;
};
};
};
/* off 0x0030 */	unsigned long	Offset;
/* off 0x0034 */	unsigned short	BufferFlag;
/* off 0x0036 */	unsigned short	BufferType;
union
{
/* off 0x0038 */	unsigned long Padding1[4];
/* off 0x0038 */	union _LARGE_INTEGER	StartTime;
/* off 0x0038 */	struct _LIST_ENTRY	Entry;
struct
{
/* off 0x0038 */	void*	Padding2;
union
{
struct
{
/* off 0x003c */	struct _SINGLE_LIST_ENTRY	GlobalEntry;
};
struct
{
/* off 0x0038 */	void*	Pointer0;
};
/* off 0x003c */	void*	Pointer1;
};
};
};
};
struct _WMI_LOGGER_CONTEXT /* sizeof 00000280 640 */
{
/* off 0x0000 */	union _LARGE_INTEGER	StartTime;
/* off 0x0008 */	void*	LogFileHandle;
/* off 0x000c */	struct _ETHREAD*	LoggerThread;
/* off 0x0010 */	long	LoggerStatus;
/* off 0x0014 */	unsigned long	LoggerId;
/* off 0x0018 */	void*	NBQHead;
/* off 0x001c */	void*	OverflowNBQHead;
/* off 0x0020 */	union _SLIST_HEADER	QueueBlockFreeList;
/* off 0x0028 */	union _SLIST_HEADER	GlobalList;
/* off 0x0030 */	struct _WMI_BUFFER_HEADER*	BatchedBufferList;
/* off 0x0034 */	struct _UNICODE_STRING	LoggerName;
/* off 0x003c */	struct _UNICODE_STRING	LogFileName;
/* off 0x0044 */	struct _UNICODE_STRING	LogFilePattern;
/* off 0x004c */	struct _UNICODE_STRING	NewLogFileName;
/* off 0x0054 */	unsigned long	ClockType;
/* off 0x0058 */	long	CollectionOn;
/* off 0x005c */	unsigned long	MaximumFileSize;
/* off 0x0060 */	unsigned long	LoggerMode;
/* off 0x0064 */	unsigned long	LastFlushedBuffer;
/* off 0x0068 */	unsigned long	FlushTimer;
/* off 0x006c */	unsigned long	FlushThreshold;
/* off 0x0070 */	union _LARGE_INTEGER	ByteOffset;
/* off 0x0078 */	union _LARGE_INTEGER	FlushTimeStamp;
/* off 0x0080 */	unsigned long	MinimumBuffers;
/* off 0x0084 */	long	BuffersAvailable;
/* off 0x0088 */	long	NumberOfBuffers;
/* off 0x008c */	unsigned long	MaximumBuffers;
/* off 0x0090 */	unsigned long	EventsLost;
/* off 0x0094 */	unsigned long	BuffersWritten;
/* off 0x0098 */	unsigned long	LogBuffersLost;
/* off 0x009c */	unsigned long	RealTimeBuffersDelivered;
/* off 0x00a0 */	unsigned long	RealTimeBuffersLost;
/* off 0x00a4 */	unsigned long	BufferSize;
/* off 0x00a8 */	unsigned long	MaximumEventSize;
/* off 0x00ac */	long*	SequencePtr;
/* off 0x00b0 */	unsigned long	LocalSequence;
/* off 0x00b4 */	struct _GUID	InstanceGuid;
/* off 0x00c4 */	__int64( __stdcall *GetCpuClock)();
/* off 0x00c8 */	long	FileCounter;
/* off 0x00cc */	void( __stdcall *BufferCallback)(struct _WMI_BUFFER_HEADER*,void*);
/* off 0x00d0 */	enum _POOL_TYPE	PoolType;
/* off 0x00d8 */	struct _ETW_REF_CLOCK	ReferenceTime;
/* off 0x00e8 */	unsigned char	RealtimeLoggerContextFreed;
/* off 0x00ec */	struct _LIST_ENTRY	Consumers;
/* off 0x00f4 */	unsigned long	NumConsumers;
/* off 0x00f8 */	struct _LIST_ENTRY	Connecting;
/* off 0x0100 */	unsigned char	NewConsumer;
/* off 0x0104 */	void*	RealtimeLogfileHandle;
/* off 0x0108 */	struct _UNICODE_STRING	RealtimeLogfileName;
/* off 0x0110 */	union _LARGE_INTEGER	RealtimeWriteOffset;
/* off 0x0118 */	union _LARGE_INTEGER	RealtimeReadOffset;
/* off 0x0120 */	union _LARGE_INTEGER	RealtimeLogfileSize;
/* off 0x0128 */	unsigned __int64	RealtimeLogfileUsage;
/* off 0x0130 */	unsigned __int64	RealtimeMaximumFileSize;
/* off 0x0138 */	unsigned long	RealtimeBuffersSaved;
/* off 0x0140 */	struct _ETW_REF_CLOCK	RealtimeReferenceTime;
/* off 0x0150 */	unsigned long	RealtimeDisconnectProcessId;
/* off 0x0154 */	unsigned long	RealtimeDisconnectConsumerId;
/* off 0x0158 */	enum _ETW_RT_EVENT_LOSS	NewRTEventsLost;
/* off 0x015c */	struct _KEVENT	LoggerEvent;
/* off 0x016c */	struct _KEVENT	FlushEvent;
/* off 0x017c */	struct _KDPC	FlushDpc;
/* off 0x019c */	struct _KMUTANT	LoggerMutex;
/* off 0x01bc */	struct _EX_PUSH_LOCK	LoggerLock;
/* off 0x01c0 */	struct _SECURITY_CLIENT_CONTEXT	ClientSecurityContext;
/* off 0x01fc */	struct _EX_FAST_REF	SecurityDescriptor;
/* off 0x0200 */	struct _WMI_BUFFER_HEADER	DummyBufferForMarker;
/* off 0x0248 */	__int64	BufferSequenceNumber;
/* off 0x0250 */	long	AcceptNewEvents;
union
{
/* off 0x0254 */	unsigned long	Flags;
struct
{
/* off 0x0254 */	unsigned long	Persistent:1	 /* start bit 0 */;
/* off 0x0254 */	unsigned long	AutoLogger:1	 /* start bit 1 */;
/* off 0x0254 */	unsigned long	FsReady:1	 /* start bit 2 */;
/* off 0x0254 */	unsigned long	RealTime:1	 /* start bit 3 */;
/* off 0x0254 */	unsigned long	Wow:1	 /* start bit 4 */;
/* off 0x0254 */	unsigned long	KernelTrace:1	 /* start bit 5 */;
/* off 0x0254 */	unsigned long	NoMoreEnable:1	 /* start bit 6 */;
};
};
union
{
/* off 0x0258 */	unsigned long	RequestFlag;
struct
{
/* off 0x0258 */	unsigned long	RequestNewFie:1	 /* start bit 0 */;
/* off 0x0258 */	unsigned long	RequestUpdateFile:1	 /* start bit 1 */;
/* off 0x0258 */	unsigned long	RequestFlush:1	 /* start bit 2 */;
/* off 0x0258 */	unsigned long	RequestDisableRealtime:1	 /* start bit 3 */;
/* off 0x0258 */	unsigned long	RequestDisconnectConsumer:1	 /* start bit 4 */;
};
};
/* off 0x025c */	unsigned short	StackTraceFilterHookCount;
/* off 0x025e */	unsigned short StackTraceFilter[16];
};
enum _ETW_BUFFER_STATE
{
	EtwBufferStateFree	=0x00000000	,//0
	EtwBufferStateGeneralLogging	=0x00000001	,//0
	EtwBufferStateCSwitch	=0x00000002	,//0
	EtwBufferStateFlush	=0x00000003	,//0
	EtwBufferStateMaximum	=0x00000004	,//0
};
enum _ETW_RT_EVENT_LOSS
{
	EtwRtEventNoLoss	=0x00000000	,//0
	EtwRtEventLost	=0x00000001	,//0
	EtwRtBufferLost	=0x00000002	,//0
	EtwRtBackupLost	=0x00000003	,//0
	EtwRtEventLossMax	=0x00000004	,//0
};
struct _WMI_TRACE_PACKET /* sizeof 00000004 4 */
{
/* off 0x0000 */	unsigned short	Size;
union
{
/* off 0x0002 */	unsigned short	HookId;
struct
{
/* off 0x0002 */	unsigned char	Type;
/* off 0x0003 */	unsigned char	Group;
};
};
};
struct _SYSTEM_TRACE_HEADER /* sizeof 00000020 32 */
{
union
{
/* off 0x0000 */	unsigned long	Marker;
struct
{
/* off 0x0000 */	unsigned short	Version;
/* off 0x0002 */	unsigned char	HeaderType;
/* off 0x0003 */	unsigned char	Flags;
};
};
union
{
/* off 0x0004 */	unsigned long	Header;
/* off 0x0004 */	struct _WMI_TRACE_PACKET	Packet;
};
/* off 0x0008 */	unsigned long	ThreadId;
/* off 0x000c */	unsigned long	ProcessId;
/* off 0x0010 */	union _LARGE_INTEGER	SystemTime;
/* off 0x0018 */	unsigned long	KernelTime;
/* off 0x001c */	unsigned long	UserTime;
};
struct _PERFINFO_TRACE_HEADER /* sizeof 00000018 24 */
{
union
{
/* off 0x0000 */	unsigned long	Marker;
struct
{
/* off 0x0000 */	unsigned short	Version;
/* off 0x0002 */	unsigned char	HeaderType;
/* off 0x0003 */	unsigned char	Flags;
};
};
union
{
/* off 0x0004 */	unsigned long	Header;
/* off 0x0004 */	struct _WMI_TRACE_PACKET	Packet;
};
union
{
/* off 0x0008 */	unsigned __int64	TS;
/* off 0x0008 */	union _LARGE_INTEGER	SystemTime;
};
/* off 0x0010 */	unsigned char Data[1];
};
enum _ETW_GUID_TYPE
{
	EtwTraceGuidType	=0x00000000	,//0
	EtwNotificationGuidType	=0x00000001	,//0
	EtwGuidTypeMax	=0x00000002	,//0
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
	WrCalloutStack	=0x00000019	,//0
	WrKernel	=0x0000001a	,//0
	WrResource	=0x0000001b	,//0
	WrPushLock	=0x0000001c	,//0
	WrMutex	=0x0000001d	,//0
	WrQuantumEnd	=0x0000001e	,//0
	WrDispatchInt	=0x0000001f	,//0
	WrPreempted	=0x00000020	,//0
	WrYieldExecution	=0x00000021	,//0
	WrFastMutex	=0x00000022	,//0
	WrGuardedMutex	=0x00000023	,//0
	WrRundown	=0x00000024	,//0
	MaximumWaitReason	=0x00000025	,//0
};
struct _ETW_LAST_ENABLE_INFO /* sizeof 00000010 16 */
{
/* off 0x0000 */	union _LARGE_INTEGER	EnableFlags;
/* off 0x0008 */	unsigned short	LoggerId;
/* off 0x000a */	unsigned char	Level;
/* off 0x000b */	unsigned char	Enabled:1	 /* start bit 0 */;
/* off 0x000b */	unsigned char	InternalFlag:7	 /* start bit 1 */;
};
struct _TRACE_ENABLE_CONTEXT /* sizeof 00000008 8 */
{
/* off 0x0000 */	unsigned short	LoggerId;
/* off 0x0002 */	unsigned char	Level;
/* off 0x0003 */	unsigned char	InternalFlag;
/* off 0x0004 */	unsigned long	EnableFlags;
};
struct _TRACE_ENABLE_CONTEXT_EX /* sizeof 00000010 16 */
{
/* off 0x0000 */	unsigned short	LoggerId;
/* off 0x0002 */	unsigned char	Level;
/* off 0x0003 */	unsigned char	InternalFlag;
/* off 0x0004 */	unsigned long	EnableFlags;
/* off 0x0008 */	unsigned long	EnableFlagsHigh;
/* off 0x000c */	unsigned long	Reserved;
};
struct _TRACE_ENABLE_INFO /* sizeof 00000020 32 */
{
/* off 0x0000 */	unsigned long	IsEnabled;
/* off 0x0004 */	unsigned char	Level;
/* off 0x0005 */	unsigned char	Reserved1;
/* off 0x0006 */	unsigned short	LoggerId;
/* off 0x0008 */	unsigned long	EnableProperty;
/* off 0x000c */	unsigned long	Reserved2;
/* off 0x0010 */	unsigned __int64	MatchAnyKeyword;
/* off 0x0018 */	unsigned __int64	MatchAllKeyword;
};
struct _ETW_GUID_ENTRY /* sizeof 00000158 344 */
{
/* off 0x0000 */	struct _LIST_ENTRY	GuidList;
/* off 0x0008 */	long	RefCount;
/* off 0x000c */	struct _GUID	Guid;
/* off 0x001c */	struct _LIST_ENTRY	RegListHead;
/* off 0x0024 */	void*	SecurityDescriptor;
/* off 0x0028 */	struct _ETW_LAST_ENABLE_INFO	LastEnable;
/* off 0x0038 */	struct _TRACE_ENABLE_INFO	ProviderEnableInfo;
/* off 0x0058 */	struct _TRACE_ENABLE_INFO EnableInfo[8];
};
struct _PORT_MESSAGE /* sizeof 00000018 24 */
{
/* off 0x0000 */	
	union  /* sizeof 00000004 4 */
	{
	/* off 0x0000 */	
		struct  /* sizeof 00000004 4 */
		{
		/* off 0x0000 */	short	DataLength;
		/* off 0x0002 */	short	TotalLength;
		}	s1;
	/* off 0x0000 */	unsigned long	Length;
	}	u1;
/* off 0x0004 */	
	union  /* sizeof 00000004 4 */
	{
	/* off 0x0000 */	
		struct  /* sizeof 00000004 4 */
		{
		/* off 0x0000 */	short	Type;
		/* off 0x0002 */	short	DataInfoOffset;
		}	s2;
	/* off 0x0000 */	unsigned long	ZeroInit;
	}	u2;
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
struct _BLOB_TYPE /* sizeof 00000024 36 */
{
/* off 0x0000 */	enum _BLOB_ID	ResourceId;
/* off 0x0004 */	unsigned long	PoolTag;
/* off 0x0008 */	unsigned long	Flags;
/* off 0x000c */	unsigned long	CreatedObjects;
/* off 0x0010 */	unsigned long	DeletedObjects;
/* off 0x0014 */	void( __stdcall *DeleteProcedure)(void*);
/* off 0x0018 */	long( __stdcall *DestroyProcedure)(void*);
/* off 0x001c */	unsigned long	UsualSize;
/* off 0x0020 */	unsigned long	LookasideIndex;
};
enum _BLOB_ID
{
	BLOB_TYPE_UNKNOWN	=0x00000000	,//0
	BLOB_TYPE_CONNECTION_INFO	=0x00000001	,//0
	BLOB_TYPE_MESSAGE	=0x00000002	,//0
	BLOB_TYPE_SECURITY_CONTEXT	=0x00000003	,//0
	BLOB_TYPE_SECTION	=0x00000004	,//0
	BLOB_TYPE_REGION	=0x00000005	,//0
	BLOB_TYPE_VIEW	=0x00000006	,//0
	BLOB_TYPE_RESERVE	=0x00000007	,//0
	BLOB_TYPE_DIRECT_TRANSFER	=0x00000008	,//0
	BLOB_TYPE_HANDLE_DATA	=0x00000009	,//0
	BLOB_TYPE_MAX_ID	=0x0000000a	,//0
};
struct _ALPC_HANDLE_ENTRY /* sizeof 00000004 4 */
{
/* off 0x0000 */	void*	Object;
};
struct _BLOB /* sizeof 00000018 24 */
{
union
{
/* off 0x0000 */	struct _LIST_ENTRY	ResourceList;
/* off 0x0000 */	struct _SINGLE_LIST_ENTRY	FreeListEntry;
};
/* off 0x0008 */	
	union  /* sizeof 00000001 1 */
	{
	/* off 0x0000 */	
		struct  /* sizeof 00000001 1 */
		{
		/* off 0x0000 */	unsigned char	ReferenceCache:1	 /* start bit 0 */;
		/* off 0x0000 */	unsigned char	Lookaside:1	 /* start bit 1 */;
		/* off 0x0000 */	unsigned char	Initializing:1	 /* start bit 2 */;
		/* off 0x0000 */	unsigned char	Deleted:1	 /* start bit 3 */;
		}	s1;
	/* off 0x0000 */	unsigned char	Flags;
	}	u1;
/* off 0x0009 */	unsigned char	ResourceId;
/* off 0x000a */	short	CachedReferences;
/* off 0x000c */	long	ReferenceCount;
/* off 0x0010 */	struct _EX_PUSH_LOCK	Lock;
/* off 0x0014 */	unsigned long	Pad;
};
struct _KALPC_SECTION /* sizeof 00000028 40 */
{
/* off 0x0000 */	
	union  /* sizeof 00000004 4 */
	{
	/* off 0x0000 */	
		struct  /* sizeof 00000004 4 */
		{
		/* off 0x0000 */	unsigned long	Internal:1	 /* start bit 0 */;
		/* off 0x0000 */	unsigned long	Secure:1	 /* start bit 1 */;
		}	s1;
	}	u1;
/* off 0x0004 */	void*	SectionObject;
/* off 0x0008 */	unsigned long	Size;
/* off 0x000c */	struct _ALPC_HANDLE_TABLE*	HandleTable;
/* off 0x0010 */	void*	SectionHandle;
/* off 0x0014 */	struct _EPROCESS*	OwnerProcess;
/* off 0x0018 */	struct _ALPC_PORT*	OwnerPort;
/* off 0x001c */	unsigned long	NumberOfRegions;
/* off 0x0020 */	struct _LIST_ENTRY	RegionListHead;
};
struct _ALPC_HANDLE_TABLE /* sizeof 00000010 16 */
{
/* off 0x0000 */	unsigned long	Flags;
/* off 0x0004 */	struct _ALPC_HANDLE_ENTRY*	Handles;
/* off 0x0008 */	unsigned long	TotalHandles;
/* off 0x000c */	struct _EX_PUSH_LOCK	Lock;
};
struct _ALPC_PORT_ATTRIBUTES /* sizeof 0000002c 44 */
{
/* off 0x0000 */	unsigned long	Flags;
/* off 0x0004 */	struct _SECURITY_QUALITY_OF_SERVICE	SecurityQos;
/* off 0x0010 */	unsigned long	MaxMessageLength;
/* off 0x0014 */	unsigned long	MemoryBandwidth;
/* off 0x0018 */	unsigned long	MaxPoolUsage;
/* off 0x001c */	unsigned long	MaxSectionSize;
/* off 0x0020 */	unsigned long	MaxViewSize;
/* off 0x0024 */	unsigned long	MaxTotalSectionSize;
/* off 0x0028 */	unsigned long	DupObjectTypes;
};
struct _ALPC_PORT /* sizeof 000000f4 244 */
{
/* off 0x0000 */	struct _LIST_ENTRY	PortListEntry;
/* off 0x0008 */	struct _ALPC_COMMUNICATION_INFO*	CommunicationInfo;
/* off 0x000c */	struct _EPROCESS*	OwnerProcess;
/* off 0x0010 */	unsigned long	SequenceNo;
/* off 0x0014 */	void*	CompletionPort;
/* off 0x0018 */	void*	CompletionKey;
/* off 0x001c */	struct _ALPC_COMPLETION_PACKET_LOOKASIDE*	CompletionPacketLookaside;
/* off 0x0020 */	void*	PortContext;
/* off 0x0024 */	struct _SECURITY_CLIENT_CONTEXT	StaticSecurity;
/* off 0x0060 */	struct _LIST_ENTRY	MainQueue;
/* off 0x0068 */	struct _LIST_ENTRY	PendingQueue;
/* off 0x0070 */	struct _LIST_ENTRY	LargeMessageQueue;
/* off 0x0078 */	struct _LIST_ENTRY	WaitQueue;
union
{
/* off 0x0080 */	struct _KSEMAPHORE*	Semaphore;
/* off 0x0080 */	struct _KEVENT*	DummyEvent;
};
/* off 0x0084 */	struct _EX_PUSH_LOCK	Lock;
/* off 0x0088 */	struct _ALPC_PORT_ATTRIBUTES	PortAttributes;
/* off 0x00b4 */	struct _EX_PUSH_LOCK	ResourceListLock;
/* off 0x00b8 */	struct _LIST_ENTRY	ResourceListHead;
/* off 0x00c0 */	struct _ALPC_COMPLETION_LIST*	CompletionList;
/* off 0x00c4 */	struct _ALPC_MESSAGE_ZONE*	MessageZone;
/* off 0x00c8 */	struct _LIST_ENTRY	CanceledQueue;
/* off 0x00d0 */	
	union  /* sizeof 00000004 4 */
	{
	/* off 0x0000 */	
		struct  /* sizeof 00000004 4 */
		{
		/* off 0x0000 */	unsigned long	Initialized:1	 /* start bit 0 */;
		/* off 0x0000 */	unsigned long	Type:2	 /* start bit 1 */;
		/* off 0x0000 */	unsigned long	ConnectionPending:1	 /* start bit 3 */;
		/* off 0x0000 */	unsigned long	ConnectionRefused:1	 /* start bit 4 */;
		/* off 0x0000 */	unsigned long	Disconnected:1	 /* start bit 5 */;
		/* off 0x0000 */	unsigned long	Closed:1	 /* start bit 6 */;
		/* off 0x0000 */	unsigned long	NoFlushOnClose:1	 /* start bit 7 */;
		/* off 0x0000 */	unsigned long	ReturnExtendedInfo:1	 /* start bit 8 */;
		/* off 0x0000 */	unsigned long	Waitable:1	 /* start bit 9 */;
		/* off 0x0000 */	unsigned long	DynamicSecurity:1	 /* start bit 10 */;
		/* off 0x0000 */	unsigned long	Wow64CompletionList:1	 /* start bit 11 */;
		/* off 0x0000 */	unsigned long	Lpc:1	 /* start bit 12 */;
		/* off 0x0000 */	unsigned long	LpcToLpc:1	 /* start bit 13 */;
		/* off 0x0000 */	unsigned long	HasCompletionList:1	 /* start bit 14 */;
		/* off 0x0000 */	unsigned long	HadCompletionList:1	 /* start bit 15 */;
		}	s1;
	/* off 0x0000 */	unsigned long	State;
	}	u1;
/* off 0x00d4 */	struct _ALPC_PORT*	TargetQueuePort;
/* off 0x00d8 */	struct _ALPC_PORT*	TargetSequencePort;
/* off 0x00dc */	struct _KALPC_MESSAGE*	Message;
/* off 0x00e0 */	unsigned long	MainQueueLength;
/* off 0x00e4 */	unsigned long	PendingQueueLength;
/* off 0x00e8 */	unsigned long	LargeMessageQueueLength;
/* off 0x00ec */	unsigned long	CanceledQueueLength;
/* off 0x00f0 */	unsigned long	WaitQueueLength;
};
struct _ALPC_COMMUNICATION_INFO /* sizeof 00000024 36 */
{
/* off 0x0000 */	struct _ALPC_PORT*	ConnectionPort;
/* off 0x0004 */	struct _ALPC_PORT*	ServerCommunicationPort;
/* off 0x0008 */	struct _ALPC_PORT*	ClientCommunicationPort;
/* off 0x000c */	struct _LIST_ENTRY	CommunicationList;
/* off 0x0014 */	struct _ALPC_HANDLE_TABLE	HandleTable;
};
struct _ALPC_COMPLETION_PACKET_LOOKASIDE_ENTRY /* sizeof 0000000c 12 */
{
/* off 0x0000 */	struct _SINGLE_LIST_ENTRY	ListEntry;
/* off 0x0004 */	void*	Packet;
/* off 0x0008 */	struct _ALPC_COMPLETION_PACKET_LOOKASIDE*	Lookaside;
};
struct _ALPC_COMPLETION_PACKET_LOOKASIDE /* sizeof 00000024 36 */
{
/* off 0x0000 */	unsigned long	Lock;
/* off 0x0004 */	unsigned long	Size;
/* off 0x0008 */	unsigned long	ActiveCount;
/* off 0x000c */	unsigned long	PendingNullCount;
/* off 0x0010 */	unsigned long	PendingCheckCompletionListCount;
/* off 0x0014 */	unsigned long	PendingDelete;
/* off 0x0018 */	struct _SINGLE_LIST_ENTRY	FreeListHead;
/* off 0x001c */	void*	CompletionPort;
/* off 0x0020 */	void*	CompletionKey;
/* off 0x0024 */	struct _ALPC_COMPLETION_PACKET_LOOKASIDE_ENTRY Entry[0];
};
struct _ALPC_COMPLETION_LIST /* sizeof 00000054 84 */
{
/* off 0x0000 */	struct _LIST_ENTRY	Entry;
/* off 0x0008 */	struct _EPROCESS*	OwnerProcess;
/* off 0x000c */	struct _MDL*	Mdl;
/* off 0x0010 */	void*	UserVa;
/* off 0x0014 */	void*	UserLimit;
/* off 0x0018 */	void*	DataUserVa;
/* off 0x001c */	void*	SystemVa;
/* off 0x0020 */	unsigned long	TotalSize;
/* off 0x0024 */	struct _ALPC_COMPLETION_LIST_HEADER*	Header;
/* off 0x0028 */	void*	List;
/* off 0x002c */	unsigned long	ListSize;
/* off 0x0030 */	void*	Bitmap;
/* off 0x0034 */	unsigned long	BitmapSize;
/* off 0x0038 */	void*	Data;
/* off 0x003c */	unsigned long	DataSize;
/* off 0x0040 */	unsigned long	BitmapLimit;
/* off 0x0044 */	unsigned long	BitmapNextHint;
/* off 0x0048 */	unsigned long	ConcurrencyCount;
/* off 0x004c */	unsigned long	AttributeFlags;
/* off 0x0050 */	unsigned long	AttributeSize;
};
struct _ALPC_COMPLETION_LIST_STATE /* sizeof 00000008 8 */
{
/* off 0x0000 */	
	union  /* sizeof 00000008 8 */
	{
	/* off 0x0000 */	
		struct  /* sizeof 00000008 8 */
		{
		/* off 0x0000 */	unsigned __int64	Head:24	 /* start bit 0 */;
		/* off 0x0000 */	unsigned __int64	Tail:24	 /* start bit 24 */;
		/* off 0x0000 */	unsigned __int64	ActiveThreadCount:16	 /* start bit 48 */;
		}	s1;
	/* off 0x0000 */	unsigned __int64	Value;
	}	u1;
};
struct _RTL_SRWLOCK /* sizeof 00000004 4 */
{
union
{
struct
{
/* off 0x0000 */	unsigned long	Locked:1	 /* start bit 0 */;
/* off 0x0000 */	unsigned long	Waiting:1	 /* start bit 1 */;
/* off 0x0000 */	unsigned long	Waking:1	 /* start bit 2 */;
/* off 0x0000 */	unsigned long	MultipleShared:1	 /* start bit 3 */;
/* off 0x0000 */	unsigned long	Shared:28	 /* start bit 4 */;
};
/* off 0x0000 */	unsigned long	Value;
/* off 0x0000 */	void*	Ptr;
};
};
struct _ALPC_COMPLETION_LIST_HEADER /* sizeof 00000300 768 */
{
/* off 0x0000 */	unsigned __int64	StartMagic;
/* off 0x0008 */	unsigned long	TotalSize;
/* off 0x000c */	unsigned long	ListOffset;
/* off 0x0010 */	unsigned long	ListSize;
/* off 0x0014 */	unsigned long	BitmapOffset;
/* off 0x0018 */	unsigned long	BitmapSize;
/* off 0x001c */	unsigned long	DataOffset;
/* off 0x0020 */	unsigned long	DataSize;
/* off 0x0024 */	unsigned long	AttributeFlags;
/* off 0x0028 */	unsigned long	AttributeSize;
/* off 0x0080 */	struct _ALPC_COMPLETION_LIST_STATE	State;
/* off 0x0088 */	unsigned long	LastMessageId;
/* off 0x008c */	unsigned long	LastCallbackId;
/* off 0x0100 */	unsigned long	PostCount;
/* off 0x0180 */	unsigned long	ReturnCount;
/* off 0x0200 */	unsigned long	LogSequenceNumber;
/* off 0x0280 */	struct _RTL_SRWLOCK	UserLock;
/* off 0x0288 */	unsigned __int64	EndMagic;
};
struct _ALPC_MESSAGE_ZONE /* sizeof 00000018 24 */
{
/* off 0x0000 */	struct _MDL*	Mdl;
/* off 0x0004 */	void*	UserVa;
/* off 0x0008 */	void*	UserLimit;
/* off 0x000c */	void*	SystemVa;
/* off 0x0010 */	void*	SystemLimit;
/* off 0x0014 */	unsigned long	Size;
};
struct _KALPC_MESSAGE_ATTRIBUTES /* sizeof 0000001c 28 */
{
/* off 0x0000 */	void*	ClientContext;
/* off 0x0004 */	void*	ServerContext;
/* off 0x0008 */	void*	PortContext;
/* off 0x000c */	void*	CancelPortContext;
/* off 0x0010 */	struct _KALPC_SECURITY_DATA*	SecurityData;
/* off 0x0014 */	struct _KALPC_VIEW*	View;
/* off 0x0018 */	struct _KALPC_HANDLE_DATA*	HandleData;
};
struct _KALPC_MESSAGE /* sizeof 00000090 144 */
{
/* off 0x0000 */	struct _LIST_ENTRY	Entry;
/* off 0x0008 */	void*	ExtensionBuffer;
/* off 0x000c */	unsigned long	ExtensionBufferSize;
union
{
/* off 0x0010 */	struct _EPROCESS*	QuotaProcess;
/* off 0x0010 */	void*	QuotaBlock;
};
/* off 0x0014 */	long	SequenceNo;
/* off 0x0018 */	
	union  /* sizeof 00000004 4 */
	{
	/* off 0x0000 */	
		struct  /* sizeof 00000004 4 */
		{
		/* off 0x0000 */	unsigned long	QueueType:2	 /* start bit 0 */;
		/* off 0x0000 */	unsigned long	QueuePortType:4	 /* start bit 2 */;
		/* off 0x0000 */	unsigned long	Canceled:1	 /* start bit 6 */;
		/* off 0x0000 */	unsigned long	Ready:1	 /* start bit 7 */;
		/* off 0x0000 */	unsigned long	ReleaseMessage:1	 /* start bit 8 */;
		/* off 0x0000 */	unsigned long	SharedQuota:1	 /* start bit 9 */;
		/* off 0x0000 */	unsigned long	ReplyWaitReply:1	 /* start bit 10 */;
		/* off 0x0000 */	unsigned long	OwnerPortReference:1	 /* start bit 11 */;
		/* off 0x0000 */	unsigned long	ReserveReference:1	 /* start bit 12 */;
		/* off 0x0000 */	unsigned long	ReceiverReference:1	 /* start bit 13 */;
		}	s1;
	/* off 0x0000 */	unsigned long	State;
	}	u1;
/* off 0x001c */	struct _ALPC_PORT*	CancelSequencePort;
/* off 0x0020 */	struct _ALPC_PORT*	CancelQueuePort;
/* off 0x0024 */	long	CancelSequenceNo;
/* off 0x0028 */	struct _LIST_ENTRY	CancelListEntry;
/* off 0x0030 */	struct _ETHREAD*	WaitingThread;
/* off 0x0034 */	struct _KALPC_RESERVE*	Reserve;
/* off 0x0038 */	struct _ALPC_PORT*	PortQueue;
/* off 0x003c */	struct _ALPC_PORT*	OwnerPort;
/* off 0x0040 */	struct _HANDLE_TABLE_ENTRY*	UniqueTableEntry;
/* off 0x0044 */	struct _KALPC_MESSAGE_ATTRIBUTES	MessageAttributes;
/* off 0x0060 */	void*	DataUserVa;
/* off 0x0064 */	void*	DataSystemVa;
/* off 0x0068 */	struct _ALPC_COMMUNICATION_INFO*	CommunicationInfo;
/* off 0x006c */	struct _ALPC_PORT*	ConnectionPort;
/* off 0x0070 */	struct _ETHREAD*	ServerThread;
/* off 0x0078 */	struct _PORT_MESSAGE	PortMessage;
};
struct _KALPC_RESERVE /* sizeof 00000014 20 */
{
/* off 0x0000 */	struct _ALPC_PORT*	OwnerPort;
/* off 0x0004 */	struct _ALPC_HANDLE_TABLE*	HandleTable;
/* off 0x0008 */	void*	Handle;
/* off 0x000c */	struct _KALPC_MESSAGE*	Message;
/* off 0x0010 */	long	Active;
};
struct _KALPC_SECURITY_DATA /* sizeof 00000050 80 */
{
/* off 0x0000 */	struct _ALPC_HANDLE_TABLE*	HandleTable;
/* off 0x0004 */	void*	ContextHandle;
/* off 0x0008 */	struct _EPROCESS*	OwningProcess;
/* off 0x000c */	struct _ALPC_PORT*	OwnerPort;
/* off 0x0010 */	struct _SECURITY_CLIENT_CONTEXT	DynamicSecurity;
/* off 0x004c */	
	union  /* sizeof 00000004 4 */
	{
	/* off 0x0000 */	
		struct  /* sizeof 00000004 4 */
		{
		/* off 0x0000 */	unsigned long	Revoked:1	 /* start bit 0 */;
		/* off 0x0000 */	unsigned long	Impersonated:1	 /* start bit 1 */;
		}	s1;
	}	u1;
};
struct _KALPC_VIEW /* sizeof 00000034 52 */
{
/* off 0x0000 */	struct _LIST_ENTRY	ViewListEntry;
/* off 0x0008 */	
	union  /* sizeof 00000004 4 */
	{
	/* off 0x0000 */	
		struct  /* sizeof 00000004 4 */
		{
		/* off 0x0000 */	unsigned long	WriteAccess:1	 /* start bit 0 */;
		/* off 0x0000 */	unsigned long	AutoRelease:1	 /* start bit 1 */;
		/* off 0x0000 */	unsigned long	ForceUnlink:1	 /* start bit 2 */;
		}	s1;
	}	u1;
/* off 0x000c */	struct _KALPC_REGION*	Region;
/* off 0x0010 */	struct _ALPC_PORT*	OwnerPort;
/* off 0x0014 */	struct _EPROCESS*	OwnerProcess;
/* off 0x0018 */	void*	Address;
/* off 0x001c */	unsigned long	Size;
/* off 0x0020 */	void*	SecureViewHandle;
/* off 0x0024 */	void*	WriteAccessHandle;
/* off 0x0028 */	unsigned long	NumberOfOwnerMessages;
/* off 0x002c */	struct _LIST_ENTRY	ProcessViewListEntry;
};
struct _KALPC_REGION /* sizeof 00000030 48 */
{
/* off 0x0000 */	
	union  /* sizeof 00000004 4 */
	{
	/* off 0x0000 */	
		struct  /* sizeof 00000004 4 */
		{
		/* off 0x0000 */	unsigned long	Secure:1	 /* start bit 0 */;
		}	s1;
	}	u1;
/* off 0x0004 */	struct _LIST_ENTRY	RegionListEntry;
/* off 0x000c */	struct _KALPC_SECTION*	Section;
/* off 0x0010 */	unsigned long	Offset;
/* off 0x0014 */	unsigned long	Size;
/* off 0x0018 */	unsigned long	ViewSize;
/* off 0x001c */	struct _KALPC_VIEW*	ReadOnlyView;
/* off 0x0020 */	struct _KALPC_VIEW*	ReadWriteView;
/* off 0x0024 */	unsigned long	NumberOfViews;
/* off 0x0028 */	struct _LIST_ENTRY	ViewListHead;
};
struct _KALPC_HANDLE_DATA /* sizeof 0000000c 12 */
{
/* off 0x0000 */	unsigned long	Flags;
/* off 0x0004 */	unsigned long	ObjectType;
/* off 0x0008 */	struct _OB_DUPLICATE_OBJECT_STATE*	DuplicateContext;
};
struct _OB_DUPLICATE_OBJECT_STATE /* sizeof 0000001c 28 */
{
/* off 0x0000 */	struct _EPROCESS*	SourceProcess;
/* off 0x0004 */	void*	SourceHandle;
/* off 0x0008 */	void*	Object;
/* off 0x000c */	struct _OBJECT_TYPE*	ObjectType;
/* off 0x0010 */	unsigned long	TargetAccess;
/* off 0x0014 */	struct _HANDLE_TABLE_ENTRY_INFO	ObjectInfo;
/* off 0x0018 */	unsigned long	HandleAttributes;
};
struct _REMOTE_PORT_VIEW /* sizeof 0000000c 12 */
{
/* off 0x0000 */	unsigned long	Length;
/* off 0x0004 */	unsigned long	ViewSize;
/* off 0x0008 */	void*	ViewBase;
};
struct _ALPC_DISPATCH_CONTEXT /* sizeof 00000020 32 */
{
/* off 0x0000 */	struct _ALPC_PORT*	PortObject;
/* off 0x0004 */	struct _KALPC_MESSAGE*	Message;
/* off 0x0008 */	struct _ALPC_COMMUNICATION_INFO*	CommunicationInfo;
/* off 0x000c */	unsigned long	Flags;
/* off 0x0010 */	struct _ETHREAD*	TargetThread;
/* off 0x0014 */	struct _ALPC_PORT*	TargetPort;
/* off 0x0018 */	unsigned short	TotalLength;
/* off 0x001a */	unsigned short	Type;
/* off 0x001c */	unsigned short	DataInfoOffset;
};
struct _ALPC_MESSAGE_ATTRIBUTES /* sizeof 00000008 8 */
{
/* off 0x0000 */	unsigned long	AllocatedAttributes;
/* off 0x0004 */	unsigned long	ValidAttributes;
};
struct _SEP_TOKEN_PRIVILEGES /* sizeof 00000018 24 */
{
/* off 0x0000 */	unsigned __int64	Present;
/* off 0x0008 */	unsigned __int64	Enabled;
/* off 0x0010 */	unsigned __int64	EnabledByDefault;
};
struct _TOKEN_AUDIT_POLICY /* sizeof 0000001b 27 */
{
/* off 0x0000 */	unsigned char PerUserPolicy[27];
};
struct _SEP_AUDIT_POLICY /* sizeof 0000001c 28 */
{
/* off 0x0000 */	struct _TOKEN_AUDIT_POLICY	AdtTokenPolicy;
/* off 0x001b */	unsigned char	PolicySetStatus;
};
struct _SID_AND_ATTRIBUTES_HASH /* sizeof 00000088 136 */
{
/* off 0x0000 */	unsigned long	SidCount;
/* off 0x0004 */	struct _SID_AND_ATTRIBUTES*	SidAttr;
/* off 0x0008 */	unsigned long Hash[32];
};
struct _TOKEN /* sizeof 000001e8 488 */
{
/* off 0x0000 */	struct _TOKEN_SOURCE	TokenSource;
/* off 0x0010 */	struct _LUID	TokenId;
/* off 0x0018 */	struct _LUID	AuthenticationId;
/* off 0x0020 */	struct _LUID	ParentTokenId;
/* off 0x0028 */	union _LARGE_INTEGER	ExpirationTime;
/* off 0x0030 */	struct _ERESOURCE*	TokenLock;
/* off 0x0034 */	struct _LUID	ModifiedId;
/* off 0x0040 */	struct _SEP_TOKEN_PRIVILEGES	Privileges;
/* off 0x0058 */	struct _SEP_AUDIT_POLICY	AuditPolicy;
/* off 0x0074 */	unsigned long	SessionId;
/* off 0x0078 */	unsigned long	UserAndGroupCount;
/* off 0x007c */	unsigned long	RestrictedSidCount;
/* off 0x0080 */	unsigned long	VariableLength;
/* off 0x0084 */	unsigned long	DynamicCharged;
/* off 0x0088 */	unsigned long	DynamicAvailable;
/* off 0x008c */	unsigned long	DefaultOwnerIndex;
/* off 0x0090 */	struct _SID_AND_ATTRIBUTES*	UserAndGroups;
/* off 0x0094 */	struct _SID_AND_ATTRIBUTES*	RestrictedSids;
/* off 0x0098 */	void*	PrimaryGroup;
/* off 0x009c */	unsigned long*	DynamicPart;
/* off 0x00a0 */	struct _ACL*	DefaultDacl;
/* off 0x00a4 */	enum _TOKEN_TYPE	TokenType;
/* off 0x00a8 */	enum _SECURITY_IMPERSONATION_LEVEL	ImpersonationLevel;
/* off 0x00ac */	unsigned long	TokenFlags;
/* off 0x00b0 */	unsigned char	TokenInUse;
/* off 0x00b4 */	unsigned long	IntegrityLevelIndex;
/* off 0x00b8 */	unsigned long	MandatoryPolicy;
/* off 0x00bc */	struct _SECURITY_TOKEN_PROXY_DATA*	ProxyData;
/* off 0x00c0 */	struct _SECURITY_TOKEN_AUDIT_DATA*	AuditData;
/* off 0x00c4 */	struct _SEP_LOGON_SESSION_REFERENCES*	LogonSession;
/* off 0x00c8 */	struct _LUID	OriginatingLogonSession;
/* off 0x00d0 */	struct _SID_AND_ATTRIBUTES_HASH	SidHash;
/* off 0x0158 */	struct _SID_AND_ATTRIBUTES_HASH	RestrictedSidHash;
/* off 0x01e0 */	unsigned long	VariablePart;
};
struct _SID_AND_ATTRIBUTES /* sizeof 00000008 8 */
{
/* off 0x0000 */	void*	Sid;
/* off 0x0004 */	unsigned long	Attributes;
};
struct _ACL /* sizeof 00000008 8 */
{
/* off 0x0000 */	unsigned char	AclRevision;
/* off 0x0001 */	unsigned char	Sbz1;
/* off 0x0002 */	unsigned short	AclSize;
/* off 0x0004 */	unsigned short	AceCount;
/* off 0x0006 */	unsigned short	Sbz2;
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
struct _SEP_LOGON_SESSION_REFERENCES /* sizeof 00000034 52 */
{
/* off 0x0000 */	struct _SEP_LOGON_SESSION_REFERENCES*	Next;
/* off 0x0004 */	struct _LUID	LogonId;
/* off 0x000c */	struct _LUID	BuddyLogonId;
/* off 0x0014 */	unsigned long	ReferenceCount;
/* off 0x0018 */	unsigned long	Flags;
/* off 0x001c */	struct _DEVICE_MAP*	pDeviceMap;
/* off 0x0020 */	void*	Token;
/* off 0x0024 */	struct _UNICODE_STRING	AccountName;
/* off 0x002c */	struct _UNICODE_STRING	AuthorityName;
};
struct _OBP_LOOKUP_CONTEXT /* sizeof 00000014 20 */
{
/* off 0x0000 */	struct _OBJECT_DIRECTORY*	Directory;
/* off 0x0004 */	void*	Object;
/* off 0x0008 */	unsigned long	HashValue;
/* off 0x000c */	unsigned short	HashIndex;
/* off 0x000e */	unsigned char	DirectoryLocked;
/* off 0x0010 */	unsigned long	LockStateSignature;
};
struct _MI_VERIFIER_POOL_HEADER /* sizeof 00000004 4 */
{
/* off 0x0000 */	struct _VI_POOL_ENTRY*	VerifierPoolEntry;
};
struct _VI_POOL_PAGE_HEADER /* sizeof 0000000c 12 */
{
/* off 0x0000 */	struct _SINGLE_LIST_ENTRY*	NextPage;
/* off 0x0004 */	void*	VerifierEntry;
/* off 0x0008 */	unsigned long	Signature;
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
/* off 0x0000 */	struct _VI_POOL_PAGE_HEADER	PageHeader;
/* off 0x0000 */	struct _VI_POOL_ENTRY_INUSE	InUse;
/* off 0x0000 */	struct _SINGLE_LIST_ENTRY*	NextFree;
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
struct _SYSPTES_HEADER /* sizeof 00000014 20 */
{
/* off 0x0000 */	struct _LIST_ENTRY	ListHead;
/* off 0x0008 */	unsigned long	Count;
/* off 0x000c */	unsigned long	NumberOfEntries;
/* off 0x0010 */	unsigned long	NumberOfEntriesPeak;
};
struct _DEVPROPKEY /* sizeof 00000014 20 */
{
/* off 0x0000 */	struct _GUID	fmtid;
/* off 0x0010 */	unsigned long	pid;
};
enum _WAIT_TYPE
{
	WaitAll	=0x00000000	,//0
	WaitAny	=0x00000001	,//0
};
struct _POOL_TRACKER_BIG_PAGES /* sizeof 00000010 16 */
{
/* off 0x0000 */	void*	Va;
/* off 0x0004 */	unsigned long	Key;
/* off 0x0008 */	unsigned long	PoolType;
/* off 0x000c */	unsigned long	NumberOfBytes;
};
struct _VI_CANCEL_GLOBALS /* sizeof 0000006c 108 */
{
/* off 0x0000 */	unsigned long	CancelLock;
/* off 0x0004 */	unsigned long	IssueLock;
/* off 0x0008 */	long Counters[25];
};
struct _THERMAL_INFORMATION_EX /* sizeof 00000050 80 */
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
/* off 0x004c */	unsigned long	S4TransitionTripPoint;
};
struct _VI_VERIFIER_ISSUE /* sizeof 00000010 16 */
{
/* off 0x0000 */	unsigned long	IssueType;
/* off 0x0004 */	void*	Address;
/* off 0x0008 */	unsigned long Parameters[2];
};
struct _EXCEPTION_POINTERS /* sizeof 00000008 8 */
{
/* off 0x0000 */	struct _EXCEPTION_RECORD*	ExceptionRecord;
/* off 0x0004 */	struct _CONTEXT*	ContextRecord;
};
struct _OBJECT_REF_STACK_INFO /* sizeof 00000008 8 */
{
/* off 0x0000 */	unsigned long	Sequence;
/* off 0x0004 */	unsigned short	Index;
/* off 0x0006 */	unsigned short	NumTraces;
};
struct _OBJECT_REF_INFO /* sizeof 0000001c 28 */
{
/* off 0x0000 */	struct _OBJECT_HEADER*	ObjectHeader;
/* off 0x0004 */	void*	NextRef;
/* off 0x0008 */	unsigned char ImageFileName[16];
/* off 0x0018 */	unsigned short	NextPos;
/* off 0x001a */	unsigned short	MaxStacks;
/* off 0x001c */	struct _OBJECT_REF_STACK_INFO StackInfo[0];
};
struct _MMSECURE_FLAGS /* sizeof 00000004 4 */
{
/* off 0x0000 */	unsigned long	ReadOnly:1	 /* start bit 0 */;
/* off 0x0000 */	unsigned long	NoWrite:1	 /* start bit 1 */;
/* off 0x0000 */	unsigned long	Spare:10	 /* start bit 2 */;
};
struct _MMADDRESS_LIST /* sizeof 00000008 8 */
{
/* off 0x0000 */	
	union  /* sizeof 00000004 4 */
	{
	/* off 0x0000 */	struct _MMSECURE_FLAGS	Flags;
	/* off 0x0000 */	void*	StartVa;
	}	u1;
/* off 0x0004 */	void*	EndVa;
};
struct _MMVAD_LONG /* sizeof 0000003c 60 */
{
/* off 0x0000 */	
	union  /* sizeof 00000004 4 */
	{
	/* off 0x0000 */	long	Balance:2	 /* start bit 0 */;
	/* off 0x0000 */	struct _MMVAD*	Parent;
	}	u1;
/* off 0x0004 */	struct _MMVAD*	LeftChild;
/* off 0x0008 */	struct _MMVAD*	RightChild;
/* off 0x000c */	unsigned long	StartingVpn;
/* off 0x0010 */	unsigned long	EndingVpn;
/* off 0x0014 */	
	union  /* sizeof 00000004 4 */
	{
	/* off 0x0000 */	unsigned long	LongFlags;
	/* off 0x0000 */	struct _MMVAD_FLAGS	VadFlags;
	}	u;
/* off 0x0018 */	struct _EX_PUSH_LOCK	PushLock;
/* off 0x001c */	
	union  /* sizeof 00000004 4 */
	{
	/* off 0x0000 */	unsigned long	LongFlags3;
	/* off 0x0000 */	struct _MMVAD_FLAGS3	VadFlags3;
	}	u5;
/* off 0x0020 */	
	union  /* sizeof 00000004 4 */
	{
	/* off 0x0000 */	unsigned long	LongFlags2;
	/* off 0x0000 */	struct _MMVAD_FLAGS2	VadFlags2;
	}	u2;
/* off 0x0024 */	struct _SUBSECTION*	Subsection;
/* off 0x0028 */	struct _MMPTE*	FirstPrototypePte;
/* off 0x002c */	struct _MMPTE*	LastContiguousPte;
/* off 0x0030 */	
	union  /* sizeof 00000008 8 */
	{
	/* off 0x0000 */	struct _LIST_ENTRY	List;
	/* off 0x0000 */	struct _MMADDRESS_LIST	Secured;
	}	u3;
/* off 0x0038 */	
	union  /* sizeof 00000004 4 */
	{
	/* off 0x0000 */	struct _MMBANKED_SECTION*	Banked;
	/* off 0x0000 */	struct _MMEXTEND_INFO*	ExtendedInfo;
	}	u4;
};
struct _MMBANKED_SECTION /* sizeof 00000020 32 */
{
/* off 0x0000 */	unsigned long	BasePhysicalPage;
/* off 0x0004 */	struct _MMPTE*	BasedPte;
/* off 0x0008 */	unsigned long	BankSize;
/* off 0x000c */	unsigned long	BankShift;
/* off 0x0010 */	void( __stdcall *BankedRoutine)(unsigned long,unsigned long,void*);
/* off 0x0014 */	void*	Context;
/* off 0x0018 */	struct _MMPTE*	CurrentMappedPte;
/* off 0x001c */	struct _MMPTE BankTemplate[1];
};
struct _HEAP_UCR_DESCRIPTOR /* sizeof 00000018 24 */
{
/* off 0x0000 */	struct _LIST_ENTRY	ListEntry;
/* off 0x0008 */	struct _LIST_ENTRY	SegmentEntry;
/* off 0x0010 */	void*	Address;
/* off 0x0014 */	unsigned long	Size;
};
struct _POOL_DESCRIPTOR /* sizeof 00001034 4148 */
{
/* off 0x0000 */	enum _POOL_TYPE	PoolType;
/* off 0x0004 */	unsigned long	PoolIndex;
/* off 0x0008 */	long	RunningAllocs;
/* off 0x000c */	long	RunningDeAllocs;
/* off 0x0010 */	long	TotalPages;
/* off 0x0014 */	long	TotalBigPages;
/* off 0x0018 */	unsigned long	Threshold;
/* off 0x001c */	void*	LockAddress;
/* off 0x0020 */	void**	PendingFrees;
/* off 0x0024 */	long	ThreadsProcessingDeferrals;
/* off 0x0028 */	long	PendingFreeDepth;
/* off 0x002c */	unsigned long	TotalBytes;
/* off 0x0030 */	unsigned long	Spare0;
/* off 0x0034 */	struct _LIST_ENTRY ListHeads[512];
};
struct _KINTERRUPT /* sizeof 00000270 624 */
{
/* off 0x0000 */	short	Type;
/* off 0x0002 */	short	Size;
/* off 0x0004 */	struct _LIST_ENTRY	InterruptListEntry;
/* off 0x000c */	unsigned char( __stdcall *ServiceRoutine)(struct _KINTERRUPT*,void*);
/* off 0x0010 */	unsigned char( __stdcall *MessageServiceRoutine)(struct _KINTERRUPT*,void*,unsigned long);
/* off 0x0014 */	unsigned long	MessageIndex;
/* off 0x0018 */	void*	ServiceContext;
/* off 0x001c */	unsigned long	SpinLock;
/* off 0x0020 */	unsigned long	TickCount;
/* off 0x0024 */	unsigned long*	ActualLock;
/* off 0x0028 */	void( __stdcall *DispatchAddress)();
/* off 0x002c */	unsigned long	Vector;
/* off 0x0030 */	unsigned char	Irql;
/* off 0x0031 */	unsigned char	SynchronizeIrql;
/* off 0x0032 */	unsigned char	FloatingSave;
/* off 0x0033 */	unsigned char	Connected;
/* off 0x0034 */	char	Number;
/* off 0x0035 */	unsigned char	ShareVector;
/* off 0x0038 */	enum _KINTERRUPT_MODE	Mode;
/* off 0x003c */	enum _KINTERRUPT_POLARITY	Polarity;
/* off 0x0040 */	unsigned long	ServiceCount;
/* off 0x0044 */	unsigned long	DispatchCount;
/* off 0x0048 */	unsigned __int64	Rsvd1;
/* off 0x0050 */	unsigned long DispatchCode[135];
};
enum _KINTERRUPT_MODE
{
	LevelSensitive	=0x00000000	,//0
	Latched	=0x00000001	,//0
};
enum _KINTERRUPT_POLARITY
{
	InterruptPolarityUnknown	=0x00000000	,//0
	InterruptActiveHigh	=0x00000001	,//0
	InterruptActiveLow	=0x00000002	,//0
};
struct _HIVE_LIST_ENTRY /* sizeof 00000020 32 */
{
/* off 0x0000 */	unsigned short*	FileName;
/* off 0x0004 */	unsigned short*	BaseName;
/* off 0x0008 */	unsigned short*	RegRootName;
/* off 0x000c */	struct _CMHIVE*	CmHive;
/* off 0x0010 */	unsigned long	HHiveFlags;
/* off 0x0014 */	unsigned long	CmHiveFlags;
/* off 0x0018 */	struct _CMHIVE*	CmHive2;
/* off 0x001c */	unsigned char	ThreadFinished;
/* off 0x001d */	unsigned char	ThreadStarted;
/* off 0x001e */	unsigned char	Allocate;
/* off 0x001f */	unsigned char	WinPERequired;
};
struct _IOV_FORCED_PENDING_TRACE /* sizeof 00000100 256 */
{
/* off 0x0000 */	struct _IRP*	Irp;
/* off 0x0004 */	void* StackTrace[63];
};
struct _LAZY_WRITER /* sizeof 00000058 88 */
{
/* off 0x0000 */	struct _LIST_ENTRY	WorkQueue;
/* off 0x0008 */	struct _KDPC	ScanDpc;
/* off 0x0028 */	struct _KTIMER	ScanTimer;
/* off 0x0050 */	unsigned char	ScanActive;
/* off 0x0051 */	unsigned char	OtherWork;
/* off 0x0052 */	unsigned char	PendingTeardown;
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
struct _PI_BUS_EXTENSION /* sizeof 00000044 68 */
{
/* off 0x0000 */	unsigned long	Flags;
/* off 0x0004 */	unsigned char	NumberCSNs;
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
enum _PS_RESOURCE_TYPE
{
	PsResourceNonPagedPool	=0x00000000	,//0
	PsResourcePagedPool	=0x00000001	,//0
	PsResourcePageFile	=0x00000002	,//0
	PsResourceWorkingSet	=0x00000003	,//0
	PsResourceCpuRate	=0x00000004	,//0
	PsResourceMax	=0x00000005	,//0
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
struct _CALL_HASH_ENTRY /* sizeof 00000014 20 */
{
/* off 0x0000 */	struct _LIST_ENTRY	ListEntry;
/* off 0x0008 */	void*	CallersAddress;
/* off 0x000c */	void*	CallersCaller;
/* off 0x0010 */	unsigned long	CallCount;
};
enum _DPFLTR_TYPE
{
	DPFLTR_SYSTEM_ID	=0x00000000	,//0
	DPFLTR_SMSS_ID	=0x00000001	,//0
	DPFLTR_SETUP_ID	=0x00000002	,//0
	DPFLTR_NTFS_ID	=0x00000003	,//0
	DPFLTR_FSTUB_ID	=0x00000004	,//0
	DPFLTR_CRASHDUMP_ID	=0x00000005	,//0
	DPFLTR_CDAUDIO_ID	=0x00000006	,//0
	DPFLTR_CDROM_ID	=0x00000007	,//0
	DPFLTR_CLASSPNP_ID	=0x00000008	,//0
	DPFLTR_DISK_ID	=0x00000009	,//0
	DPFLTR_REDBOOK_ID	=0x0000000a	,//0
	DPFLTR_STORPROP_ID	=0x0000000b	,//0
	DPFLTR_SCSIPORT_ID	=0x0000000c	,//0
	DPFLTR_SCSIMINIPORT_ID	=0x0000000d	,//0
	DPFLTR_CONFIG_ID	=0x0000000e	,//0
	DPFLTR_I8042PRT_ID	=0x0000000f	,//0
	DPFLTR_SERMOUSE_ID	=0x00000010	,//0
	DPFLTR_LSERMOUS_ID	=0x00000011	,//0
	DPFLTR_KBDHID_ID	=0x00000012	,//0
	DPFLTR_MOUHID_ID	=0x00000013	,//0
	DPFLTR_KBDCLASS_ID	=0x00000014	,//0
	DPFLTR_MOUCLASS_ID	=0x00000015	,//0
	DPFLTR_TWOTRACK_ID	=0x00000016	,//0
	DPFLTR_WMILIB_ID	=0x00000017	,//0
	DPFLTR_ACPI_ID	=0x00000018	,//0
	DPFLTR_AMLI_ID	=0x00000019	,//0
	DPFLTR_HALIA64_ID	=0x0000001a	,//0
	DPFLTR_VIDEO_ID	=0x0000001b	,//0
	DPFLTR_SVCHOST_ID	=0x0000001c	,//0
	DPFLTR_VIDEOPRT_ID	=0x0000001d	,//0
	DPFLTR_TCPIP_ID	=0x0000001e	,//0
	DPFLTR_DMSYNTH_ID	=0x0000001f	,//0
	DPFLTR_NTOSPNP_ID	=0x00000020	,//0
	DPFLTR_FASTFAT_ID	=0x00000021	,//0
	DPFLTR_SAMSS_ID	=0x00000022	,//0
	DPFLTR_PNPMGR_ID	=0x00000023	,//0
	DPFLTR_NETAPI_ID	=0x00000024	,//0
	DPFLTR_SCSERVER_ID	=0x00000025	,//0
	DPFLTR_SCCLIENT_ID	=0x00000026	,//0
	DPFLTR_SERIAL_ID	=0x00000027	,//0
	DPFLTR_SERENUM_ID	=0x00000028	,//0
	DPFLTR_UHCD_ID	=0x00000029	,//0
	DPFLTR_RPCPROXY_ID	=0x0000002a	,//0
	DPFLTR_AUTOCHK_ID	=0x0000002b	,//0
	DPFLTR_DCOMSS_ID	=0x0000002c	,//0
	DPFLTR_UNIMODEM_ID	=0x0000002d	,//0
	DPFLTR_SIS_ID	=0x0000002e	,//0
	DPFLTR_FLTMGR_ID	=0x0000002f	,//0
	DPFLTR_WMICORE_ID	=0x00000030	,//0
	DPFLTR_BURNENG_ID	=0x00000031	,//0
	DPFLTR_IMAPI_ID	=0x00000032	,//0
	DPFLTR_SXS_ID	=0x00000033	,//0
	DPFLTR_FUSION_ID	=0x00000034	,//0
	DPFLTR_IDLETASK_ID	=0x00000035	,//0
	DPFLTR_SOFTPCI_ID	=0x00000036	,//0
	DPFLTR_TAPE_ID	=0x00000037	,//0
	DPFLTR_MCHGR_ID	=0x00000038	,//0
	DPFLTR_IDEP_ID	=0x00000039	,//0
	DPFLTR_PCIIDE_ID	=0x0000003a	,//0
	DPFLTR_FLOPPY_ID	=0x0000003b	,//0
	DPFLTR_FDC_ID	=0x0000003c	,//0
	DPFLTR_TERMSRV_ID	=0x0000003d	,//0
	DPFLTR_W32TIME_ID	=0x0000003e	,//0
	DPFLTR_PREFETCHER_ID	=0x0000003f	,//0
	DPFLTR_RSFILTER_ID	=0x00000040	,//0
	DPFLTR_FCPORT_ID	=0x00000041	,//0
	DPFLTR_PCI_ID	=0x00000042	,//0
	DPFLTR_DMIO_ID	=0x00000043	,//0
	DPFLTR_DMCONFIG_ID	=0x00000044	,//0
	DPFLTR_DMADMIN_ID	=0x00000045	,//0
	DPFLTR_WSOCKTRANSPORT_ID	=0x00000046	,//0
	DPFLTR_VSS_ID	=0x00000047	,//0
	DPFLTR_PNPMEM_ID	=0x00000048	,//0
	DPFLTR_PROCESSOR_ID	=0x00000049	,//0
	DPFLTR_DMSERVER_ID	=0x0000004a	,//0
	DPFLTR_SR_ID	=0x0000004b	,//0
	DPFLTR_INFINIBAND_ID	=0x0000004c	,//0
	DPFLTR_IHVDRIVER_ID	=0x0000004d	,//0
	DPFLTR_IHVVIDEO_ID	=0x0000004e	,//0
	DPFLTR_IHVAUDIO_ID	=0x0000004f	,//0
	DPFLTR_IHVNETWORK_ID	=0x00000050	,//0
	DPFLTR_IHVSTREAMING_ID	=0x00000051	,//0
	DPFLTR_IHVBUS_ID	=0x00000052	,//0
	DPFLTR_HPS_ID	=0x00000053	,//0
	DPFLTR_RTLTHREADPOOL_ID	=0x00000054	,//0
	DPFLTR_LDR_ID	=0x00000055	,//0
	DPFLTR_TCPIP6_ID	=0x00000056	,//0
	DPFLTR_ISAPNP_ID	=0x00000057	,//0
	DPFLTR_SHPC_ID	=0x00000058	,//0
	DPFLTR_STORPORT_ID	=0x00000059	,//0
	DPFLTR_STORMINIPORT_ID	=0x0000005a	,//0
	DPFLTR_PRINTSPOOLER_ID	=0x0000005b	,//0
	DPFLTR_VSSDYNDISK_ID	=0x0000005c	,//0
	DPFLTR_VERIFIER_ID	=0x0000005d	,//0
	DPFLTR_VDS_ID	=0x0000005e	,//0
	DPFLTR_VDSBAS_ID	=0x0000005f	,//0
	DPFLTR_VDSDYN_ID	=0x00000060	,//0
	DPFLTR_VDSDYNDR_ID	=0x00000061	,//0
	DPFLTR_VDSLDR_ID	=0x00000062	,//0
	DPFLTR_VDSUTIL_ID	=0x00000063	,//0
	DPFLTR_DFRGIFC_ID	=0x00000064	,//0
	DPFLTR_DEFAULT_ID	=0x00000065	,//0
	DPFLTR_MM_ID	=0x00000066	,//0
	DPFLTR_DFSC_ID	=0x00000067	,//0
	DPFLTR_WOW64_ID	=0x00000068	,//0
	DPFLTR_ALPC_ID	=0x00000069	,//0
	DPFLTR_WDI_ID	=0x0000006a	,//0
	DPFLTR_PERFLIB_ID	=0x0000006b	,//0
	DPFLTR_KTM_ID	=0x0000006c	,//0
	DPFLTR_IOSTRESS_ID	=0x0000006d	,//0
	DPFLTR_HEAP_ID	=0x0000006e	,//0
	DPFLTR_WHEA_ID	=0x0000006f	,//0
	DPFLTR_USERGDI_ID	=0x00000070	,//0
	DPFLTR_MMCSS_ID	=0x00000071	,//0
	DPFLTR_TPM_ID	=0x00000072	,//0
	DPFLTR_THREADORDER_ID	=0x00000073	,//0
	DPFLTR_ENVIRON_ID	=0x00000074	,//0
	DPFLTR_EMS_ID	=0x00000075	,//0
	DPFLTR_WDT_ID	=0x00000076	,//0
	DPFLTR_FVEVOL_ID	=0x00000077	,//0
	DPFLTR_NDIS_ID	=0x00000078	,//0
	DPFLTR_NVCTRACE_ID	=0x00000079	,//0
	DPFLTR_LUAFV_ID	=0x0000007a	,//0
	DPFLTR_APPCOMPAT_ID	=0x0000007b	,//0
	DPFLTR_USBSTOR_ID	=0x0000007c	,//0
	DPFLTR_SBP2PORT_ID	=0x0000007d	,//0
	DPFLTR_COVERAGE_ID	=0x0000007e	,//0
	DPFLTR_CACHEMGR_ID	=0x0000007f	,//0
	DPFLTR_MOUNTMGR_ID	=0x00000080	,//0
	DPFLTR_CFR_ID	=0x00000081	,//0
	DPFLTR_TXF_ID	=0x00000082	,//0
	DPFLTR_KSECDD_ID	=0x00000083	,//0
	DPFLTR_FLTREGRESS_ID	=0x00000084	,//0
	DPFLTR_MPIO_ID	=0x00000085	,//0
	DPFLTR_MSDSM_ID	=0x00000086	,//0
	DPFLTR_UDFS_ID	=0x00000087	,//0
	DPFLTR_PSHED_ID	=0x00000088	,//0
	DPFLTR_STORVSP_ID	=0x00000089	,//0
	DPFLTR_EXFAT_ID	=0x0000008a	,//0
	DPFLTR_ENDOFTABLE_ID	=0x0000008b	,//0
};
struct _VF_TRACKER_STAMP /* sizeof 00000008 8 */
{
/* off 0x0000 */	void*	Thread;
/* off 0x0004 */	unsigned char	Flags:8	 /* start bit 0 */;
/* off 0x0005 */	unsigned char	OldIrql:8	 /* start bit 0 */;
/* off 0x0006 */	unsigned char	NewIrql:8	 /* start bit 0 */;
/* off 0x0007 */	unsigned char	Processor:8	 /* start bit 0 */;
};
struct _VI_TRACK_IRQL /* sizeof 00000020 32 */
{
/* off 0x0000 */	void*	Thread;
/* off 0x0004 */	unsigned char	OldIrql;
/* off 0x0005 */	unsigned char	NewIrql;
/* off 0x0006 */	unsigned char	Processor;
/* off 0x0008 */	unsigned long	TickCount;
/* off 0x000c */	void* StackTrace[5];
};
enum _MM_PREEMPTIVE_TRIMS
{
	MmPreemptForNonPaged	=0x00000000	,//0
	MmPreemptForPaged	=0x00000001	,//0
	MmPreemptForNonPagedPriority	=0x00000002	,//0
	MmPreemptForPagedPriority	=0x00000003	,//0
	MmMaximumPreempt	=0x00000004	,//0
};
struct _POOL_TRACKER_TABLE /* sizeof 0000001c 28 */
{
/* off 0x0000 */	long	Key;
/* off 0x0004 */	long	NonPagedAllocs;
/* off 0x0008 */	long	NonPagedFrees;
/* off 0x000c */	unsigned long	NonPagedBytes;
/* off 0x0010 */	unsigned long	PagedAllocs;
/* off 0x0014 */	unsigned long	PagedFrees;
/* off 0x0018 */	unsigned long	PagedBytes;
};
struct _SEGMENT_OBJECT /* sizeof 00000028 40 */
{
/* off 0x0000 */	void*	BaseAddress;
/* off 0x0004 */	unsigned long	TotalNumberOfPtes;
/* off 0x0008 */	union _LARGE_INTEGER	SizeOfSegment;
/* off 0x0010 */	unsigned long	NonExtendedPtes;
/* off 0x0014 */	unsigned long	ImageCommitment;
/* off 0x0018 */	struct _CONTROL_AREA*	ControlArea;
/* off 0x001c */	struct _SUBSECTION*	Subsection;
/* off 0x0020 */	struct _MMSECTION_FLAGS*	MmSectionFlags;
/* off 0x0024 */	struct _MMSUBSECTION_FLAGS*	MmSubSectionFlags;
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
enum LSA_FOREST_TRUST_RECORD_TYPE
{
	ForestTrustTopLevelName	=0x00000000	,//0
	ForestTrustTopLevelNameEx	=0x00000001	,//0
	ForestTrustDomainInfo	=0x00000002	,//0
	ForestTrustRecordTypeLast	=0x00000002	,//0
};
enum SYSTEM_POWER_CONDITION
{
	PoAc	=0x00000000	,//0
	PoDc	=0x00000001	,//0
	PoHot	=0x00000002	,//0
	PoConditionMaximum	=0x00000003	,//0
};
struct _KSYSTEM_TIME /* sizeof 0000000c 12 */
{
/* off 0x0000 */	unsigned long	LowPart;
/* off 0x0004 */	long	High1Time;
/* off 0x0008 */	long	High2Time;
};
struct _MEMORY_ALLOCATION_DESCRIPTOR /* sizeof 00000014 20 */
{
/* off 0x0000 */	struct _LIST_ENTRY	ListEntry;
/* off 0x0008 */	enum _TYPE_OF_MEMORY	MemoryType;
/* off 0x000c */	unsigned long	BasePage;
/* off 0x0010 */	unsigned long	PageCount;
};
enum _TYPE_OF_MEMORY
{
	LoaderExceptionBlock	=0x00000000	,//0
	LoaderSystemBlock	=0x00000001	,//0
	LoaderFree	=0x00000002	,//0
	LoaderBad	=0x00000003	,//0
	LoaderLoadedProgram	=0x00000004	,//0
	LoaderFirmwareTemporary	=0x00000005	,//0
	LoaderFirmwarePermanent	=0x00000006	,//0
	LoaderOsloaderHeap	=0x00000007	,//0
	LoaderOsloaderStack	=0x00000008	,//0
	LoaderSystemCode	=0x00000009	,//0
	LoaderHalCode	=0x0000000a	,//0
	LoaderBootDriver	=0x0000000b	,//0
	LoaderConsoleInDriver	=0x0000000c	,//0
	LoaderConsoleOutDriver	=0x0000000d	,//0
	LoaderStartupDpcStack	=0x0000000e	,//0
	LoaderStartupKernelStack	=0x0000000f	,//0
	LoaderStartupPanicStack	=0x00000010	,//0
	LoaderStartupPcrPage	=0x00000011	,//0
	LoaderStartupPdrPage	=0x00000012	,//0
	LoaderRegistryData	=0x00000013	,//0
	LoaderMemoryData	=0x00000014	,//0
	LoaderNlsData	=0x00000015	,//0
	LoaderSpecialMemory	=0x00000016	,//0
	LoaderBBTMemory	=0x00000017	,//0
	LoaderReserve	=0x00000018	,//0
	LoaderXIPRom	=0x00000019	,//0
	LoaderHALCachedMemory	=0x0000001a	,//0
	LoaderLargePageFiller	=0x0000001b	,//0
	LoaderErrorLogMemory	=0x0000001c	,//0
	LoaderMaximum	=0x0000001d	,//0
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
struct _MAPPED_FILE_SEGMENT /* sizeof 00000028 40 */
{
/* off 0x0000 */	struct _CONTROL_AREA*	ControlArea;
/* off 0x0004 */	unsigned long	TotalNumberOfPtes;
/* off 0x0008 */	struct _SEGMENT_FLAGS	SegmentFlags;
/* off 0x000c */	unsigned long	NumberOfCommittedPages;
/* off 0x0010 */	unsigned __int64	SizeOfSegment;
union
{
/* off 0x0018 */	struct _MMEXTEND_INFO*	ExtendInfo;
/* off 0x0018 */	void*	BasedAddress;
};
/* off 0x001c */	struct _EX_PUSH_LOCK	SegmentLock;
/* off 0x0020 */	struct _MSUBSECTION*	LastSubsectionHint;
};
struct _VI_FAULT_TRACE /* sizeof 00000024 36 */
{
/* off 0x0000 */	struct _ETHREAD*	Thread;
/* off 0x0004 */	void* StackTrace[8];
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
enum _VI_CNT_INDEX_TYPE
{
	VF_CNT_IRPS_TOTAL_COUNT	=0x00000000	,//0
	VF_CNT_IRPS_NOT_A_TARGET	=0x00000001	,//0
	VF_CNT_IRPS_KMODE	=0x00000002	,//0
	VF_CNT_IRPS_SKIP_FLAGS	=0x00000003	,//0
	VF_CNT_IRPS_ALREADY_HOOKED	=0x00000004	,//0
	VF_CNT_IRPS_WILL_ATTEMPT_CANCEL	=0x00000005	,//0
	VF_CNT_IRPS_WILL_NOT_CANCEL	=0x00000006	,//0
	VF_CNT_REAL_RACE_FOR_COMPLETION	=0x00000007	,//0
	VF_CNT_IRPS_COMPLETED_BY_DRIVER	=0x00000008	,//0
	VF_CNT_IRPS_COMPLETED_BY_CANCEL	=0x00000009	,//0
	VF_CNT_IRPS_NO_CANCEL_ROUTINE	=0x0000000a	,//0
	VF_CNT_IRPS_CANCEL_RETURNED_TRUE	=0x0000000b	,//0
	VF_CNT_IRPS_CANCEL_RETURNED_FALSE	=0x0000000c	,//0
	VF_CNT_IRP_CANCEL_ROUTINE_NO_CHECK	=0x0000000d	,//0
	VF_CNT_IRP_CANCEL_ROUTINE_NEVER	=0x0000000e	,//0
	VF_CNT_IRP_CANCEL_ROUTINE_SOMETIMES	=0x0000000f	,//0
	VF_CNT_EXTRA_ALLOCS	=0x00000010	,//0
	VF_CNT_EXTRA_FREES	=0x00000011	,//0
	VF_CNT_CALLS_TO_TIMER_DPC	=0x00000012	,//0
	VF_CNT_CALLS_TO_CANCEL_WORKER	=0x00000013	,//0
	VF_CNT_FREE_FROM_CANCEL_ROUTINE	=0x00000014	,//0
	VF_CNT_FREE_FROM_COMPLETION_ROUTINE	=0x00000015	,//0
	VF_CNT_ISSUES_LOGGED	=0x00000016	,//0
	VF_CNT_CANCEL_AND_COMPLETE_DIFFERENT_THREADS	=0x00000017	,//0
	VF_CNT_IRPS_TOO_MANY_UNDER_WATCH	=0x00000018	,//0
	VF_CNT_MAX_INDEX	=0x00000019	,//0
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
struct _ARBITER_ORDERING_LIST /* sizeof 00000008 8 */
{
/* off 0x0000 */	unsigned short	Count;
/* off 0x0002 */	unsigned short	Maximum;
/* off 0x0004 */	struct _ARBITER_ORDERING*	Orderings;
};
struct _ARBITER_INSTANCE /* sizeof 000005ec 1516 */
{
/* off 0x0000 */	unsigned long	Signature;
/* off 0x0004 */	struct _KEVENT*	MutexEvent;
/* off 0x0008 */	unsigned short*	Name;
/* off 0x000c */	unsigned short*	OrderingName;
/* off 0x0010 */	int	ResourceType;
/* off 0x0014 */	struct _RTL_RANGE_LIST*	Allocation;
/* off 0x0018 */	struct _RTL_RANGE_LIST*	PossibleAllocation;
/* off 0x001c */	struct _ARBITER_ORDERING_LIST	OrderingList;
/* off 0x0024 */	struct _ARBITER_ORDERING_LIST	ReservedList;
/* off 0x002c */	long	ReferenceCount;
/* off 0x0030 */	struct _ARBITER_INTERFACE*	Interface;
/* off 0x0034 */	unsigned long	AllocationStackMaxSize;
/* off 0x0038 */	struct _ARBITER_ALLOCATION_STATE*	AllocationStack;
/* off 0x003c */	long( __stdcall *UnpackRequirement)(struct _IO_RESOURCE_DESCRIPTOR*,unsigned __int64*,unsigned __int64*,unsigned __int64*,unsigned __int64*);
/* off 0x0040 */	long( __stdcall *PackResource)(struct _IO_RESOURCE_DESCRIPTOR*,unsigned __int64,struct _CM_PARTIAL_RESOURCE_DESCRIPTOR*);
/* off 0x0044 */	long( __stdcall *UnpackResource)(struct _CM_PARTIAL_RESOURCE_DESCRIPTOR*,unsigned __int64*,unsigned __int64*);
/* off 0x0048 */	long( __stdcall *ScoreRequirement)(struct _IO_RESOURCE_DESCRIPTOR*);
/* off 0x004c */	long( __stdcall *TestAllocation)(struct _ARBITER_INSTANCE*,struct _ARBITER_TEST_ALLOCATION_PARAMETERS*);
/* off 0x0050 */	long( __stdcall *RetestAllocation)(struct _ARBITER_INSTANCE*,struct _ARBITER_RETEST_ALLOCATION_PARAMETERS*);
/* off 0x0054 */	long( __stdcall *CommitAllocation)(struct _ARBITER_INSTANCE*);
/* off 0x0058 */	long( __stdcall *RollbackAllocation)(struct _ARBITER_INSTANCE*);
/* off 0x005c */	long( __stdcall *BootAllocation)(struct _ARBITER_INSTANCE*,struct _ARBITER_BOOT_ALLOCATION_PARAMETERS*);
/* off 0x0060 */	long( __stdcall *QueryArbitrate)(struct _ARBITER_INSTANCE*,struct _ARBITER_QUERY_ARBITRATE_PARAMETERS*);
/* off 0x0064 */	long( __stdcall *QueryConflict)(struct _ARBITER_INSTANCE*,struct _ARBITER_QUERY_CONFLICT_PARAMETERS*);
/* off 0x0068 */	long( __stdcall *AddReserved)(struct _ARBITER_INSTANCE*,struct _ARBITER_ADD_RESERVED_PARAMETERS*);
/* off 0x006c */	long( __stdcall *StartArbiter)(struct _ARBITER_INSTANCE*,struct _CM_RESOURCE_LIST*);
/* off 0x0070 */	long( __stdcall *PreprocessEntry)(struct _ARBITER_INSTANCE*,struct _ARBITER_ALLOCATION_STATE*);
/* off 0x0074 */	long( __stdcall *AllocateEntry)(struct _ARBITER_INSTANCE*,struct _ARBITER_ALLOCATION_STATE*);
/* off 0x0078 */	unsigned char( __stdcall *GetNextAllocationRange)(struct _ARBITER_INSTANCE*,struct _ARBITER_ALLOCATION_STATE*);
/* off 0x007c */	unsigned char( __stdcall *FindSuitableRange)(struct _ARBITER_INSTANCE*,struct _ARBITER_ALLOCATION_STATE*);
/* off 0x0080 */	void( __stdcall *AddAllocation)(struct _ARBITER_INSTANCE*,struct _ARBITER_ALLOCATION_STATE*);
/* off 0x0084 */	void( __stdcall *BacktrackAllocation)(struct _ARBITER_INSTANCE*,struct _ARBITER_ALLOCATION_STATE*);
/* off 0x0088 */	unsigned char( __stdcall *OverrideConflict)(struct _ARBITER_INSTANCE*,struct _ARBITER_ALLOCATION_STATE*);
/* off 0x008c */	long( __stdcall *InitializeRangeList)(struct _ARBITER_INSTANCE*,unsigned long,struct _CM_PARTIAL_RESOURCE_DESCRIPTOR*,struct _RTL_RANGE_LIST*);
/* off 0x0090 */	unsigned char	TransactionInProgress;
/* off 0x0094 */	struct _KEVENT*	TransactionEvent;
/* off 0x0098 */	void*	Extension;
/* off 0x009c */	struct _DEVICE_OBJECT*	BusDeviceObject;
/* off 0x00a0 */	void*	ConflictCallbackContext;
/* off 0x00a4 */	unsigned char( __stdcall *ConflictCallback)(void*,struct _RTL_RANGE*);
/* off 0x00a8 */	wchar PdoDescriptionString[336];
/* off 0x0348 */	char PdoSymbolicNameString[672];
/* off 0x05e8 */	wchar PdoAddressString[1];
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
struct _ARBITER_INTERFACE /* sizeof 00000018 24 */
{
/* off 0x0000 */	unsigned short	Size;
/* off 0x0002 */	unsigned short	Version;
/* off 0x0004 */	void*	Context;
/* off 0x0008 */	void( __stdcall *InterfaceReference)(void*);
/* off 0x000c */	void( __stdcall *InterfaceDereference)(void*);
/* off 0x0010 */	long( __stdcall *ArbiterHandler)(void*,enum _ARBITER_ACTION,struct _ARBITER_PARAMETERS*);
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
struct _ARBITER_TEST_ALLOCATION_PARAMETERS /* sizeof 0000000c 12 */
{
/* off 0x0000 */	struct _LIST_ENTRY*	ArbitrationList;
/* off 0x0004 */	unsigned long	AllocateFromCount;
/* off 0x0008 */	struct _CM_PARTIAL_RESOURCE_DESCRIPTOR*	AllocateFrom;
};
struct _ARBITER_RETEST_ALLOCATION_PARAMETERS /* sizeof 0000000c 12 */
{
/* off 0x0000 */	struct _LIST_ENTRY*	ArbitrationList;
/* off 0x0004 */	unsigned long	AllocateFromCount;
/* off 0x0008 */	struct _CM_PARTIAL_RESOURCE_DESCRIPTOR*	AllocateFrom;
};
struct _ARBITER_BOOT_ALLOCATION_PARAMETERS /* sizeof 00000004 4 */
{
/* off 0x0000 */	struct _LIST_ENTRY*	ArbitrationList;
};
struct _ARBITER_QUERY_ALLOCATED_RESOURCES_PARAMETERS /* sizeof 00000004 4 */
{
/* off 0x0000 */	struct _CM_PARTIAL_RESOURCE_LIST**	AllocatedResources;
};
struct _ARBITER_QUERY_CONFLICT_PARAMETERS /* sizeof 00000010 16 */
{
/* off 0x0000 */	struct _DEVICE_OBJECT*	PhysicalDeviceObject;
/* off 0x0004 */	struct _IO_RESOURCE_DESCRIPTOR*	ConflictingResource;
/* off 0x0008 */	unsigned long*	ConflictCount;
/* off 0x000c */	struct _ARBITER_CONFLICT_INFO**	Conflicts;
};
struct _ARBITER_QUERY_ARBITRATE_PARAMETERS /* sizeof 00000004 4 */
{
/* off 0x0000 */	struct _LIST_ENTRY*	ArbitrationList;
};
struct _ARBITER_ADD_RESERVED_PARAMETERS /* sizeof 00000004 4 */
{
/* off 0x0000 */	struct _DEVICE_OBJECT*	ReserveDevice;
};
struct _ARBITER_PARAMETERS /* sizeof 00000010 16 */
{
/* off 0x0000 */	
	union  /* sizeof 00000010 16 */
	{
	/* off 0x0000 */	struct _ARBITER_TEST_ALLOCATION_PARAMETERS	TestAllocation;
	/* off 0x0000 */	struct _ARBITER_RETEST_ALLOCATION_PARAMETERS	RetestAllocation;
	/* off 0x0000 */	struct _ARBITER_BOOT_ALLOCATION_PARAMETERS	BootAllocation;
	/* off 0x0000 */	struct _ARBITER_QUERY_ALLOCATED_RESOURCES_PARAMETERS	QueryAllocatedResources;
	/* off 0x0000 */	struct _ARBITER_QUERY_CONFLICT_PARAMETERS	QueryConflict;
	/* off 0x0000 */	struct _ARBITER_QUERY_ARBITRATE_PARAMETERS	QueryArbitrate;
	/* off 0x0000 */	struct _ARBITER_ADD_RESERVED_PARAMETERS	AddReserved;
	}	Parameters;
};
struct _ARBITER_CONFLICT_INFO /* sizeof 00000018 24 */
{
/* off 0x0000 */	struct _DEVICE_OBJECT*	OwningObject;
/* off 0x0008 */	unsigned __int64	Start;
/* off 0x0010 */	unsigned __int64	End;
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
enum _ARBITER_RESULT
{
	ArbiterResultUndefined	=0xffffffff	,//-1
	ArbiterResultSuccess	=0x00000000	,//0
	ArbiterResultExternalConflict	=0x00000001	,//0
	ArbiterResultNullRequest	=0x00000002	,//0
};
struct _ARBITER_ALTERNATIVE /* sizeof 00000038 56 */
{
/* off 0x0000 */	unsigned __int64	Minimum;
/* off 0x0008 */	unsigned __int64	Maximum;
/* off 0x0010 */	unsigned __int64	Length;
/* off 0x0018 */	unsigned __int64	Alignment;
/* off 0x0020 */	long	Priority;
/* off 0x0024 */	unsigned long	Flags;
/* off 0x0028 */	struct _IO_RESOURCE_DESCRIPTOR*	Descriptor;
/* off 0x002c */	unsigned long Reserved[3];
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
struct _KGUARDED_MUTEX /* sizeof 00000020 32 */
{
/* off 0x0000 */	long	Count;
/* off 0x0004 */	struct _KTHREAD*	Owner;
/* off 0x0008 */	unsigned long	Contention;
/* off 0x000c */	struct _KGATE	Gate;
union
{
struct
{
/* off 0x001c */	short	KernelApcDisable;
/* off 0x001e */	short	SpecialApcDisable;
};
/* off 0x001c */	unsigned long	CombinedApcDisable;
};
};
struct _POP_ACTION_TRIGGER /* sizeof 00000010 16 */
{
/* off 0x0000 */	enum POP_POLICY_DEVICE_TYPE	Type;
/* off 0x0004 */	unsigned long	Flags;
/* off 0x0008 */	struct _POP_TRIGGER_WAIT*	Wait;
union
{
/* off 0x000c */	
	struct  /* sizeof 00000004 4 */
	{
	/* off 0x0000 */	unsigned long	Level;
	}	Battery;
/* off 0x000c */	
	struct  /* sizeof 00000004 4 */
	{
	/* off 0x0000 */	unsigned long	Type;
	}	Button;
};
};
struct _POP_THERMAL_ZONE /* sizeof 000000d8 216 */
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
/* off 0x0080 */	struct _IRP*	Irp;
/* off 0x0084 */	struct _THERMAL_INFORMATION_EX	Info;
};
enum POP_POLICY_DEVICE_TYPE
{
	PolicyDeviceSystemButton	=0x00000000	,//0
	PolicyDeviceThermalZone	=0x00000001	,//0
	PolicyDeviceBattery	=0x00000002	,//0
	PolicyDeviceMemory	=0x00000003	,//0
	PolicyInitiatePowerActionAPI	=0x00000004	,//0
	PolicySetPowerStateAPI	=0x00000005	,//0
	PolicyImmediateDozeS4	=0x00000006	,//0
	PolicySystemIdle	=0x00000007	,//0
	PolicyDeviceMax	=0x00000008	,//0
};
struct _POP_TRIGGER_WAIT /* sizeof 00000020 32 */
{
/* off 0x0000 */	struct _KEVENT	Event;
/* off 0x0010 */	long	Status;
/* off 0x0014 */	struct _LIST_ENTRY	Link;
/* off 0x001c */	struct _POP_ACTION_TRIGGER*	Trigger;
};
enum _MI_SYSTEM_VA_TYPE
{
	MiVaUnused	=0x00000000	,//0
	MiVaSessionSpace	=0x00000001	,//0
	MiVaProcessSpace	=0x00000002	,//0
	MiVaBootLoaded	=0x00000003	,//0
	MiVaPfnDatabase	=0x00000004	,//0
	MiVaNonPagedPool	=0x00000005	,//0
	MiVaPagedPool	=0x00000006	,//0
	MiVaSpecialPool	=0x00000007	,//0
	MiVaSystemCache	=0x00000008	,//0
	MiVaSystemPtes	=0x00000009	,//0
	MiVaHal	=0x0000000a	,//0
	MiVaSessionGlobalSpace	=0x0000000b	,//0
	MiVaDriverImages	=0x0000000c	,//0
	MiVaMaximumType	=0x0000000d	,//0
};
struct _POOL_HACKER /* sizeof 00000028 40 */
{
/* off 0x0000 */	struct _POOL_HEADER	Header;
/* off 0x0008 */	unsigned long Contents[8];
};
struct _VF_BTS_DATA_MANAGEMENT_AREA /* sizeof 00000034 52 */
{
/* off 0x0000 */	void*	BTSBufferBase;
/* off 0x0004 */	void*	BTSIndex;
/* off 0x0008 */	void*	BTSMax;
/* off 0x000c */	void*	BTSInterruptThreshold;
/* off 0x0010 */	void*	PEBSBufferBase;
/* off 0x0014 */	void*	PEBSIndex;
/* off 0x0018 */	void*	PEBSMax;
/* off 0x001c */	void*	PEBSInterruptThreshold;
/* off 0x0020 */	void* PEBSCounterReset[2];
/* off 0x0028 */	char Reserved[12];
};
struct PROCESSOR_PERFSTATE_POLICY /* sizeof 0000001c 28 */
{
/* off 0x0000 */	unsigned long	Revision;
/* off 0x0004 */	unsigned char	MaxThrottle;
/* off 0x0005 */	unsigned char	MinThrottle;
/* off 0x0006 */	unsigned char	BusyAdjThreshold;
union
{
/* off 0x0007 */	unsigned char	Spare;
/* off 0x0007 */	
	union  /* sizeof 00000001 1 */
	{
	/* off 0x0000 */	unsigned char	AsUCHAR;
	struct
	{
	/* off 0x0000 */	unsigned char	NoDomainAccounting:1	 /* start bit 0 */;
	/* off 0x0000 */	unsigned char	IncreasePolicy:2	 /* start bit 1 */;
	/* off 0x0000 */	unsigned char	DecreasePolicy:2	 /* start bit 3 */;
	/* off 0x0000 */	unsigned char	Reserved:3	 /* start bit 5 */;
	};
	}	Flags;
};
/* off 0x0008 */	unsigned long	TimeCheck;
/* off 0x000c */	unsigned long	IncreaseTime;
/* off 0x0010 */	unsigned long	DecreaseTime;
/* off 0x0014 */	unsigned long	IncreasePercent;
/* off 0x0018 */	unsigned long	DecreasePercent;
};
struct _BUS_EXTENSION_LIST /* sizeof 00000008 8 */
{
/* off 0x0000 */	void*	Next;
/* off 0x0004 */	struct _PI_BUS_EXTENSION*	BusExtension;
};
enum _MM_POOL_TYPES
{
	MmNonPagedPool	=0x00000000	,//0
	MmPagedPool	=0x00000001	,//0
	MmSessionPagedPool	=0x00000002	,//0
	MmMaximumPoolType	=0x00000003	,//0
};
enum _PCI_HOTPLUG_SLOT_INTERRUPT
{
	SlotInterruptPresenceDetect	=0x00000000	,//0
	SlotInterruptLatchChange	=0x00000001	,//0
	SlotInterruptAttentionButton	=0x00000002	,//0
	SlotInterruptLinkStateChange	=0x00000003	,//0
	SlotInterruptPowerFault	=0x00000004	,//0
	SlotInterruptMaximum	=0x00000007	,//0
};
enum _MEMORY_CACHING_TYPE_ORIG
{
	MmFrameBufferCached	=0x00000002	,//0
};
struct _PF_KERNEL_GLOBALS /* sizeof 00000040 64 */
{
/* off 0x0000 */	unsigned __int64	AccessBufferAgeThreshold;
/* off 0x0008 */	struct _EX_RUNDOWN_REF	AccessBufferRef;
/* off 0x000c */	struct _KEVENT	AccessBufferExistsEvent;
/* off 0x001c */	unsigned long	AccessBufferMax;
/* off 0x0020 */	union _SLIST_HEADER	AccessBufferList;
/* off 0x0028 */	long	StreamSequenceNumber;
/* off 0x002c */	unsigned long	Flags;
/* off 0x0030 */	long	ScenarioPrefetchCount;
};
struct _IMAGE_SECTION_HEADER /* sizeof 00000028 40 */
{
/* off 0x0000 */	unsigned char Name[8];
/* off 0x0008 */	
	union  /* sizeof 00000004 4 */
	{
	/* off 0x0000 */	unsigned long	PhysicalAddress;
	/* off 0x0000 */	unsigned long	VirtualSize;
	}	Misc;
/* off 0x000c */	unsigned long	VirtualAddress;
/* off 0x0010 */	unsigned long	SizeOfRawData;
/* off 0x0014 */	unsigned long	PointerToRawData;
/* off 0x0018 */	unsigned long	PointerToRelocations;
/* off 0x001c */	unsigned long	PointerToLinenumbers;
/* off 0x0020 */	unsigned short	NumberOfRelocations;
/* off 0x0022 */	unsigned short	NumberOfLinenumbers;
/* off 0x0024 */	unsigned long	Characteristics;
};
enum _MM_POOL_PRIORITIES
{
	MmHighPriority	=0x00000000	,//0
	MmNormalPriority	=0x00000001	,//0
	MmLowPriority	=0x00000002	,//0
	MmMaximumPoolPriority	=0x00000003	,//0
};
struct _KUSER_SHARED_DATA /* sizeof 000003b8 952 */
{
/* off 0x0000 */	unsigned long	TickCountLowDeprecated;
/* off 0x0004 */	unsigned long	TickCountMultiplier;
/* off 0x0008 */	struct _KSYSTEM_TIME	InterruptTime;
/* off 0x0014 */	struct _KSYSTEM_TIME	SystemTime;
/* off 0x0020 */	struct _KSYSTEM_TIME	TimeZoneBias;
/* off 0x002c */	unsigned short	ImageNumberLow;
/* off 0x002e */	unsigned short	ImageNumberHigh;
/* off 0x0030 */	wchar NtSystemRoot[260];
/* off 0x0238 */	unsigned long	MaxStackTraceDepth;
/* off 0x023c */	unsigned long	CryptoExponent;
/* off 0x0240 */	unsigned long	TimeZoneId;
/* off 0x0244 */	unsigned long	LargePageMinimum;
/* off 0x0248 */	unsigned long Reserved2[7];
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
union
{
/* off 0x02f0 */	unsigned long	SharedDataFlags;
struct
{
/* off 0x02f0 */	unsigned long	DbgErrorPortPresent:1	 /* start bit 0 */;
/* off 0x02f0 */	unsigned long	DbgElevationEnabled:1	 /* start bit 1 */;
/* off 0x02f0 */	unsigned long	DbgVirtEnabled:1	 /* start bit 2 */;
/* off 0x02f0 */	unsigned long	DbgInstallerDetectEnabled:1	 /* start bit 3 */;
/* off 0x02f0 */	unsigned long	DbgSystemDllRelocated:1	 /* start bit 4 */;
/* off 0x02f0 */	unsigned long	DbgDynProcessorEnabled:1	 /* start bit 5 */;
/* off 0x02f0 */	unsigned long	DbgSEHValidationEnabled:1	 /* start bit 6 */;
/* off 0x02f0 */	unsigned long	SpareBits:25	 /* start bit 7 */;
};
};
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
/* off 0x0338 */	__int64	ConsoleSessionForegroundProcessId;
/* off 0x0340 */	unsigned long Wow64SharedInformation[16];
/* off 0x0380 */	unsigned short UserModeGlobalLogger[8];
/* off 0x0390 */	unsigned long HeapTracingPid[2];
/* off 0x0398 */	unsigned long CritSecTracingPid[2];
/* off 0x03a0 */	unsigned long	ImageFileExecutionOptions;
/* off 0x03a4 */	unsigned long	LangGenerationCount;
union
{
/* off 0x03a8 */	unsigned __int64	AffinityPad;
/* off 0x03a8 */	unsigned long	ActiveProcessorAffinity;
};
/* off 0x03b0 */	unsigned __int64	InterruptTimeBias;
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
struct _CM_CACHED_VALUE_INDEX /* sizeof 00000054 84 */
{
/* off 0x0000 */	unsigned long	CellIndex;
/* off 0x0004 */	
	union  /* sizeof 00000050 80 */
	{
	/* off 0x0000 */	struct _CELL_DATA	CellData;
	/* off 0x0000 */	unsigned long List[1];
	}	Data;
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
enum _MODE
{
	KernelMode	=0x00000000	,//0
	UserMode	=0x00000001	,//0
	MaximumMode	=0x00000002	,//0
};
struct _HEAP_DEBUGGING_INFORMATION /* sizeof 0000001c 28 */
{
/* off 0x0000 */	void*	InterceptorFunction;
/* off 0x0004 */	unsigned short	InterceptorValue;
/* off 0x0008 */	unsigned long	ExtendedOptions;
/* off 0x000c */	unsigned long	StackTraceDepth;
/* off 0x0010 */	unsigned long	MinTotalBlockSize;
/* off 0x0014 */	unsigned long	MaxTotalBlockSize;
/* off 0x0018 */	long( __stdcall *HeapLeakEnumerationRoutine)(long,void*,void*,unsigned long,unsigned long,void*);
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
struct _SECTION_OBJECT /* sizeof 00000018 24 */
{
/* off 0x0000 */	void*	StartingVa;
/* off 0x0004 */	void*	EndingVa;
/* off 0x0008 */	void*	Parent;
/* off 0x000c */	void*	LeftChild;
/* off 0x0010 */	void*	RightChild;
/* off 0x0014 */	struct _SEGMENT_OBJECT*	Segment;
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
/* off 0x000c */	wchar Name[1];
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
/* off 0x0011 */	unsigned char	FastSystemS4;
/* off 0x0012 */	unsigned char spare2[3];
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
struct _POP_POWER_ACTION /* sizeof 000000a0 160 */
{
/* off 0x0000 */	unsigned char	Updates;
/* off 0x0001 */	unsigned char	State;
/* off 0x0002 */	unsigned char	Shutdown;
/* off 0x0004 */	enum POWER_ACTION	Action;
/* off 0x0008 */	enum _SYSTEM_POWER_STATE	LightestState;
/* off 0x000c */	unsigned long	Flags;
/* off 0x0010 */	long	Status;
/* off 0x0014 */	enum POP_POLICY_DEVICE_TYPE	DeviceType;
/* off 0x0018 */	unsigned long	DeviceTypeFlags;
/* off 0x001c */	unsigned char	IrpMinor;
/* off 0x001d */	unsigned char	Waking;
/* off 0x0020 */	enum _SYSTEM_POWER_STATE	SystemState;
/* off 0x0024 */	enum _SYSTEM_POWER_STATE	NextSystemState;
/* off 0x0028 */	enum _SYSTEM_POWER_STATE	EffectiveSystemState;
/* off 0x002c */	enum _SYSTEM_POWER_STATE	CurrentSystemState;
/* off 0x0030 */	struct _POP_SHUTDOWN_BUG_CHECK*	ShutdownBugCode;
/* off 0x0034 */	struct _POP_DEVICE_SYS_STATE*	DevState;
/* off 0x0038 */	struct _POP_DISPLAY_RESUME_CONTEXT*	DisplayResumeContext;
/* off 0x003c */	struct _POP_HIBER_CONTEXT*	HiberContext;
/* off 0x0040 */	unsigned __int64	WakeTime;
/* off 0x0048 */	unsigned __int64	SleepTime;
/* off 0x0050 */	struct SYSTEM_POWER_CAPABILITIES	FilteredCapabilities;
};
struct _POP_SHUTDOWN_BUG_CHECK /* sizeof 00000020 32 */
{
/* off 0x0000 */	void*	ThreadHandle;
/* off 0x0004 */	void*	ThreadId;
/* off 0x0008 */	void*	ProcessId;
/* off 0x000c */	unsigned long	Code;
/* off 0x0010 */	unsigned long	Parameter1;
/* off 0x0014 */	unsigned long	Parameter2;
/* off 0x0018 */	unsigned long	Parameter3;
/* off 0x001c */	unsigned long	Parameter4;
};
struct _PO_NOTIFY_ORDER_LEVEL /* sizeof 00000028 40 */
{
/* off 0x0000 */	unsigned long	DeviceCount;
/* off 0x0004 */	unsigned long	ActiveCount;
/* off 0x0008 */	struct _LIST_ENTRY	WaitSleep;
/* off 0x0010 */	struct _LIST_ENTRY	ReadySleep;
/* off 0x0018 */	struct _LIST_ENTRY	ReadyS0;
/* off 0x0020 */	struct _LIST_ENTRY	WaitS0;
};
struct _PO_DEVICE_NOTIFY_ORDER /* sizeof 00000148 328 */
{
/* off 0x0000 */	unsigned char	Locked;
/* off 0x0004 */	struct _DEVICE_OBJECT**	WarmEjectPdoPointer;
/* off 0x0008 */	struct _PO_NOTIFY_ORDER_LEVEL OrderLevel[8];
};
struct _POP_DEVICE_SYS_STATE /* sizeof 00000188 392 */
{
/* off 0x0000 */	unsigned char	IrpMinor;
/* off 0x0004 */	enum _SYSTEM_POWER_STATE	SystemState;
/* off 0x0008 */	unsigned long	SpinLock;
/* off 0x000c */	struct _KTHREAD*	Thread;
/* off 0x0010 */	struct _KEVENT*	AbortEvent;
/* off 0x0014 */	struct _KSEMAPHORE*	ReadySemaphore;
/* off 0x0018 */	struct _KSEMAPHORE*	FinishedSemaphore;
/* off 0x001c */	unsigned char	GetNewDeviceList;
/* off 0x0020 */	struct _PO_DEVICE_NOTIFY_ORDER	Order;
/* off 0x0168 */	long	NotifyGdiLevelForPowerOn;
/* off 0x016c */	long	NotifyGdiLevelForResumeUI;
/* off 0x0170 */	struct _LIST_ENTRY	Pending;
/* off 0x0178 */	long	Status;
/* off 0x017c */	struct _DEVICE_OBJECT*	FailedDevice;
/* off 0x0180 */	unsigned char	Waking;
/* off 0x0181 */	unsigned char	Cancelled;
/* off 0x0182 */	unsigned char	IgnoreErrors;
/* off 0x0183 */	unsigned char	IgnoreNotImplemented;
/* off 0x0184 */	unsigned char	TimeRefreshLockAcquired;
};
struct _POP_DISPLAY_RESUME_CONTEXT /* sizeof 00000050 80 */
{
/* off 0x0000 */	struct _WORK_QUEUE_ITEM	WorkItem;
/* off 0x0010 */	struct _ETHREAD*	WorkerThread;
/* off 0x0014 */	struct _KEVENT	PrepareUIEvent;
/* off 0x0024 */	struct _KEVENT	PowerOnEvent;
/* off 0x0034 */	struct _KEVENT	DoneEvent;
/* off 0x0044 */	unsigned long	WorkerQueued;
/* off 0x0048 */	unsigned long	WorkerAbort;
/* off 0x004c */	unsigned long	NoResumeUI;
};
struct _PO_HIBER_PERF /* sizeof 00000060 96 */
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
/* off 0x0048 */	unsigned __int64	ResumeAppStartTime;
/* off 0x0050 */	unsigned __int64	ResumeAppEndTime;
/* off 0x0058 */	unsigned __int64	HiberFileResumeTime;
};
struct _POP_HIBER_CONTEXT /* sizeof 00000100 256 */
{
/* off 0x0000 */	unsigned char	WriteToFile;
/* off 0x0001 */	unsigned char	ReserveLoaderMemory;
/* off 0x0002 */	unsigned char	ReserveFreeMemory;
/* off 0x0003 */	unsigned char	VerifyOnWake;
/* off 0x0004 */	unsigned char	Reset;
/* off 0x0005 */	unsigned char	HiberFlags;
/* off 0x0006 */	unsigned char	WroteHiberFile;
/* off 0x0008 */	unsigned long	Lock;
/* off 0x000c */	unsigned char	MapFrozen;
/* off 0x0010 */	struct _RTL_BITMAP	MemoryMap;
/* off 0x0018 */	struct _RTL_BITMAP	DiscardedMemoryPages;
/* off 0x0020 */	struct _LIST_ENTRY	ClonedRanges;
/* off 0x0028 */	unsigned long	ClonedRangeCount;
/* off 0x002c */	struct _LIST_ENTRY*	NextCloneRange;
/* off 0x0030 */	unsigned long	NextPreserve;
/* off 0x0034 */	struct _MDL*	LoaderMdl;
/* off 0x0038 */	struct _MDL*	AllocatedMdl;
/* off 0x0040 */	unsigned __int64	PagesOut;
/* off 0x0048 */	void*	IoPages;
/* off 0x004c */	unsigned long	IoPagesCount;
/* off 0x0050 */	void*	CurrentMcb;
/* off 0x0054 */	struct _DUMP_STACK_CONTEXT*	DumpStack;
/* off 0x0058 */	struct _KPROCESSOR_STATE*	WakeState;
/* off 0x005c */	unsigned long	HiberVa;
/* off 0x0060 */	union _LARGE_INTEGER	HiberPte;
/* off 0x0068 */	long	Status;
/* off 0x006c */	struct PO_MEMORY_IMAGE*	MemoryImage;
/* off 0x0070 */	struct _PO_MEMORY_RANGE_TABLE*	TableHead;
/* off 0x0074 */	unsigned char*	CompressionWorkspace;
/* off 0x0078 */	unsigned char*	CompressedWriteBuffer;
/* off 0x007c */	unsigned long*	PerformanceStats;
/* off 0x0080 */	void*	CompressionBlock;
/* off 0x0084 */	void*	DmaIO;
/* off 0x0088 */	void*	TemporaryHeap;
/* off 0x0090 */	struct _PO_HIBER_PERF	PerfInfo;
/* off 0x00f0 */	struct _MDL*	BootLoaderLogMdl;
/* off 0x00f4 */	struct _MDL*	FirmwareRuntimeInformationMdl;
/* off 0x00f8 */	void*	ResumeContext;
/* off 0x00fc */	unsigned long	ResumeContextPages;
};
struct _DUMP_INITIALIZATION_CONTEXT /* sizeof 00000070 112 */
{
/* off 0x0000 */	unsigned long	Length;
/* off 0x0004 */	unsigned long	Reserved;
/* off 0x0008 */	void*	MemoryBlock;
/* off 0x000c */	void* CommonBuffer[2];
/* off 0x0018 */	union _LARGE_INTEGER PhysicalAddress[2];
/* off 0x0028 */	void( __stdcall *StallRoutine)(unsigned long);
/* off 0x002c */	unsigned char( __stdcall *OpenRoutine)(union _LARGE_INTEGER);
/* off 0x0030 */	long( __stdcall *WriteRoutine)(union _LARGE_INTEGER*,struct _MDL*);
/* off 0x0034 */	void( __stdcall *FinishRoutine)();
/* off 0x0038 */	struct _ADAPTER_OBJECT*	AdapterObject;
/* off 0x003c */	void*	MappedRegisterBase;
/* off 0x0040 */	void*	PortConfiguration;
/* off 0x0044 */	unsigned char	CrashDump;
/* off 0x0048 */	unsigned long	MaximumTransferSize;
/* off 0x004c */	unsigned long	CommonBufferSize;
/* off 0x0050 */	void*	TargetAddress;
/* off 0x0054 */	long( __stdcall *WritePendingRoutine)(long,union _LARGE_INTEGER*,struct _MDL*,void*);
/* off 0x0058 */	unsigned long	PartitionStyle;
/* off 0x005c */	
	union  /* sizeof 00000010 16 */
	{
	/* off 0x0000 */	
		struct  /* sizeof 00000008 8 */
		{
		/* off 0x0000 */	unsigned long	Signature;
		/* off 0x0004 */	unsigned long	CheckSum;
		}	Mbr;
	/* off 0x0000 */	
		struct  /* sizeof 00000010 16 */
		{
		/* off 0x0000 */	struct _GUID	DiskId;
		}	Gpt;
	}	DiskInfo;
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
struct PO_MEMORY_IMAGE /* sizeof 000000f0 240 */
{
/* off 0x0000 */	unsigned long	Signature;
/* off 0x0004 */	unsigned long	ImageType;
/* off 0x0008 */	unsigned long	CheckSum;
/* off 0x000c */	unsigned long	LengthSelf;
/* off 0x0010 */	unsigned long	PageSelf;
/* off 0x0014 */	unsigned long	PageSize;
/* off 0x0018 */	union _LARGE_INTEGER	SystemTime;
/* off 0x0020 */	unsigned __int64	InterruptTime;
/* off 0x0028 */	unsigned long	FeatureFlags;
/* off 0x002c */	unsigned char	HiberFlags;
/* off 0x002d */	unsigned char spare[3];
/* off 0x0030 */	unsigned long	NoHiberPtes;
/* off 0x0034 */	unsigned long	HiberVa;
/* off 0x0038 */	union _LARGE_INTEGER	HiberPte;
/* off 0x0040 */	unsigned long	NoFreePages;
/* off 0x0044 */	unsigned long	FreeMapCheck;
/* off 0x0048 */	unsigned long	WakeCheck;
/* off 0x004c */	unsigned long	TotalPages;
/* off 0x0050 */	unsigned long	FirstTablePage;
/* off 0x0058 */	struct _PO_HIBER_PERF	PerfInfo;
/* off 0x00b8 */	unsigned long	FirmwareRuntimeInformationPages;
/* off 0x00bc */	unsigned long FirmwareRuntimeInformation[1];
/* off 0x00c0 */	unsigned long	NoBootLoaderLogPages;
/* off 0x00c4 */	unsigned long BootLoaderLogPages[8];
/* off 0x00e4 */	unsigned long	NotUsed;
/* off 0x00e8 */	unsigned long	ResumeContextCheck;
/* off 0x00ec */	unsigned long	ResumeContextPages;
};
struct _PO_MEMORY_RANGE /* sizeof 00000008 8 */
{
/* off 0x0000 */	unsigned long	StartPage;
/* off 0x0004 */	unsigned long	EndPage;
};
struct _PO_MEMORY_RANGE_TABLE /* sizeof 00000014 20 */
{
/* off 0x0000 */	struct _PO_MEMORY_RANGE_TABLE*	Next;
/* off 0x0004 */	unsigned long	NextTable;
/* off 0x0008 */	unsigned long	EntryCount;
/* off 0x000c */	struct _PO_MEMORY_RANGE Range[1];
};
enum _KOBJECTS
{
	EventNotificationObject	=0x00000000	,//0
	EventSynchronizationObject	=0x00000001	,//0
	MutantObject	=0x00000002	,//0
	ProcessObject	=0x00000003	,//0
	QueueObject	=0x00000004	,//0
	SemaphoreObject	=0x00000005	,//0
	ThreadObject	=0x00000006	,//0
	GateObject	=0x00000007	,//0
	TimerNotificationObject	=0x00000008	,//0
	TimerSynchronizationObject	=0x00000009	,//0
	Spare2Object	=0x0000000a	,//0
	Spare3Object	=0x0000000b	,//0
	Spare4Object	=0x0000000c	,//0
	Spare5Object	=0x0000000d	,//0
	Spare6Object	=0x0000000e	,//0
	Spare7Object	=0x0000000f	,//0
	Spare8Object	=0x00000010	,//0
	Spare9Object	=0x00000011	,//0
	ApcObject	=0x00000012	,//0
	DpcObject	=0x00000013	,//0
	DeviceQueueObject	=0x00000014	,//0
	EventPairObject	=0x00000015	,//0
	InterruptObject	=0x00000016	,//0
	ProfileObject	=0x00000017	,//0
	ThreadedDpcObject	=0x00000018	,//0
	MaximumKernelObject	=0x00000019	,//0
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
struct _PI_RESOURCE_ARBITER_ENTRY /* sizeof 00000038 56 */
{
/* off 0x0000 */	struct _LIST_ENTRY	DeviceArbiterList;
/* off 0x0008 */	unsigned char	ResourceType;
/* off 0x000c */	struct _ARBITER_INTERFACE*	ArbiterInterface;
/* off 0x0010 */	struct _DEVICE_NODE*	DeviceNode;
/* off 0x0014 */	struct _LIST_ENTRY	ResourceList;
/* off 0x001c */	struct _LIST_ENTRY	BestResourceList;
/* off 0x0024 */	struct _LIST_ENTRY	BestConfig;
/* off 0x002c */	struct _LIST_ENTRY	ActiveArbiterList;
/* off 0x0034 */	unsigned char	State;
/* off 0x0035 */	unsigned char	ResourcesChanged;
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
struct _PHYSICAL_MEMORY_RUN /* sizeof 00000008 8 */
{
/* off 0x0000 */	unsigned long	BasePage;
/* off 0x0004 */	unsigned long	PageCount;
};
struct _MI_VERIFIER_DRIVER_ENTRY /* sizeof 00000058 88 */
{
/* off 0x0000 */	struct _LIST_ENTRY	Links;
/* off 0x0008 */	unsigned long	Loads;
/* off 0x000c */	unsigned long	Unloads;
/* off 0x0010 */	struct _UNICODE_STRING	BaseName;
/* off 0x0018 */	void*	StartAddress;
/* off 0x001c */	void*	EndAddress;
/* off 0x0020 */	unsigned long	Flags;
/* off 0x0024 */	unsigned long	Signature;
/* off 0x0028 */	union _SLIST_HEADER	PoolPageHeaders;
/* off 0x0030 */	union _SLIST_HEADER	PoolTrackers;
/* off 0x0038 */	unsigned long	CurrentPagedPoolAllocations;
/* off 0x003c */	unsigned long	CurrentNonPagedPoolAllocations;
/* off 0x0040 */	unsigned long	PeakPagedPoolAllocations;
/* off 0x0044 */	unsigned long	PeakNonPagedPoolAllocations;
/* off 0x0048 */	unsigned long	PagedBytes;
/* off 0x004c */	unsigned long	NonPagedBytes;
/* off 0x0050 */	unsigned long	PeakPagedBytes;
/* off 0x0054 */	unsigned long	PeakNonPagedBytes;
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
struct _ETW_PROVIDER_TABLE_ENTRY /* sizeof 00000010 16 */
{
/* off 0x0000 */	long	RefCount;
/* off 0x0004 */	enum _ETW_PROVIDER_STATE	State;
/* off 0x0008 */	struct _ETW_REG_ENTRY*	RegEntry;
/* off 0x000c */	void*	Caller;
};
enum _ETW_PROVIDER_STATE
{
	EtwProviderStateFree	=0x00000000	,//0
	EtwProviderStateTransition	=0x00000001	,//0
	EtwProviderStateActive	=0x00000002	,//0
	EtwProviderStateMax	=0x00000003	,//0
};
struct _ETW_REG_ENTRY /* sizeof 0000002c 44 */
{
/* off 0x0000 */	struct _LIST_ENTRY	RegList;
/* off 0x0008 */	struct _ETW_GUID_ENTRY*	GuidEntry;
/* off 0x000c */	unsigned short	Index;
/* off 0x000e */	unsigned short	Flags;
/* off 0x0010 */	unsigned char	EnableMask;
union
{
/* off 0x0014 */	struct _ETW_REPLY_QUEUE*	ReplyQueue;
/* off 0x0014 */	struct _ETW_REG_ENTRY* ReplySlot[4];
};
union
{
/* off 0x0024 */	struct _EPROCESS*	Process;
/* off 0x0024 */	void*	Callback;
};
/* off 0x0028 */	void*	CallbackContext;
};
struct _ETW_REPLY_QUEUE /* sizeof 0000002c 44 */
{
/* off 0x0000 */	struct _KQUEUE	Queue;
/* off 0x0028 */	long	EventsLost;
};
struct _VF_POOL_TRACE /* sizeof 00000040 64 */
{
/* off 0x0000 */	void*	Address;
/* off 0x0004 */	unsigned long	Size;
/* off 0x0008 */	struct _ETHREAD*	Thread;
/* off 0x000c */	void* StackTrace[13];
};
struct _MM_SESSION_SPACE_FLAGS /* sizeof 00000004 4 */
{
/* off 0x0000 */	unsigned long	Initialized:1	 /* start bit 0 */;
/* off 0x0000 */	unsigned long	DeletePending:1	 /* start bit 1 */;
/* off 0x0000 */	unsigned long	PoolInitialized:1	 /* start bit 2 */;
/* off 0x0000 */	unsigned long	DynamicVaInitialized:1	 /* start bit 3 */;
/* off 0x0000 */	unsigned long	WsInitialized:1	 /* start bit 4 */;
/* off 0x0000 */	unsigned long	PoolDestroyed:1	 /* start bit 5 */;
/* off 0x0000 */	unsigned long	ObjectInitialized:1	 /* start bit 6 */;
/* off 0x0000 */	unsigned long	Filler:25	 /* start bit 7 */;
};
struct _MMSESSION /* sizeof 00000038 56 */
{
/* off 0x0000 */	struct _KGUARDED_MUTEX	SystemSpaceViewLock;
/* off 0x0020 */	struct _KGUARDED_MUTEX*	SystemSpaceViewLockPointer;
/* off 0x0024 */	struct _MMVIEW*	SystemSpaceViewTable;
/* off 0x0028 */	unsigned long	SystemSpaceHashSize;
/* off 0x002c */	unsigned long	SystemSpaceHashEntries;
/* off 0x0030 */	unsigned long	SystemSpaceHashKey;
/* off 0x0034 */	unsigned long	BitmapFailures;
};
struct _MM_PAGED_POOL_INFO /* sizeof 00000038 56 */
{
/* off 0x0000 */	struct _KGUARDED_MUTEX	Mutex;
/* off 0x0020 */	struct _RTL_BITMAP	PagedPoolAllocationMap;
/* off 0x0028 */	struct _MMPTE*	FirstPteForPagedPool;
/* off 0x002c */	unsigned long	PagedPoolHint;
/* off 0x0030 */	unsigned long	PagedPoolCommit;
/* off 0x0034 */	unsigned long	AllocatedPagedPool;
};
struct _MI_SPECIAL_POOL /* sizeof 00000018 24 */
{
/* off 0x0000 */	struct _MMPTE*	PteBase;
/* off 0x0004 */	struct _MMPTE	FreePteHead;
/* off 0x0008 */	struct _MMPTE	FreePteTail;
/* off 0x000c */	long	PagesInUse;
/* off 0x0010 */	struct _RTL_BITMAP	SpecialPoolPdes;
};
struct _MI_SYSTEM_PTE_TYPE /* sizeof 0000002c 44 */
{
/* off 0x0000 */	struct _RTL_BITMAP	Bitmap;
/* off 0x0008 */	unsigned long	Hint;
/* off 0x000c */	struct _MMPTE*	BasePte;
/* off 0x0010 */	unsigned long*	FailureCount;
/* off 0x0014 */	struct _MMSUPPORT*	Vm;
/* off 0x0018 */	long	TotalSystemPtes;
/* off 0x001c */	long	TotalFreeSystemPtes;
/* off 0x0020 */	long	CachedPteCount;
/* off 0x0024 */	unsigned long	PteFailures;
/* off 0x0028 */	struct _KGUARDED_MUTEX*	GlobalMutex;
};
struct _MM_SESSION_SPACE /* sizeof 00001ec0 7872 */
{
/* off 0x0000 */	long	ReferenceCount;
/* off 0x0004 */	
	union  /* sizeof 00000004 4 */
	{
	/* off 0x0000 */	unsigned long	LongFlags;
	/* off 0x0000 */	struct _MM_SESSION_SPACE_FLAGS	Flags;
	}	u;
/* off 0x0008 */	unsigned long	SessionId;
/* off 0x000c */	long	ProcessReferenceToSession;
/* off 0x0010 */	struct _LIST_ENTRY	ProcessList;
/* off 0x0018 */	union _LARGE_INTEGER	LastProcessSwappedOutTime;
/* off 0x0020 */	unsigned long	SessionPageDirectoryIndex;
/* off 0x0024 */	unsigned long	NonPagablePages;
/* off 0x0028 */	unsigned long	CommittedPages;
/* off 0x002c */	void*	PagedPoolStart;
/* off 0x0030 */	void*	PagedPoolEnd;
/* off 0x0034 */	void*	SessionObject;
/* off 0x0038 */	void*	SessionObjectHandle;
/* off 0x003c */	long	ResidentProcessCount;
/* off 0x0040 */	long	ImageLoadingCount;
/* off 0x0044 */	unsigned long SessionPoolAllocationFailures[4];
/* off 0x0054 */	struct _LIST_ENTRY	ImageList;
/* off 0x005c */	unsigned long	LocaleId;
/* off 0x0060 */	unsigned long	AttachCount;
/* off 0x0064 */	struct _KGATE	AttachGate;
/* off 0x0074 */	struct _LIST_ENTRY	WsListEntry;
/* off 0x0080 */	struct _GENERAL_LOOKASIDE Lookaside[25];
/* off 0x0d00 */	struct _MMSESSION	Session;
/* off 0x0d38 */	struct _MM_PAGED_POOL_INFO	PagedPoolInfo;
/* off 0x0d70 */	struct _MMSUPPORT	Vm;
/* off 0x0db8 */	struct _MMWSLE*	Wsle;
/* off 0x0dbc */	void( __stdcall *DriverUnload)(struct _DRIVER_OBJECT*);
/* off 0x0dc0 */	struct _POOL_DESCRIPTOR	PagedPool;
/* off 0x1df4 */	struct _MMPTE*	PageTables;
/* off 0x1df8 */	struct _MI_SPECIAL_POOL	SpecialPool;
/* off 0x1e10 */	struct _KGUARDED_MUTEX	SessionPteLock;
/* off 0x1e30 */	long	PoolBigEntriesInUse;
/* off 0x1e34 */	unsigned long	PagedPoolPdeCount;
/* off 0x1e38 */	unsigned long	SpecialPoolPdeCount;
/* off 0x1e3c */	unsigned long	DynamicSessionPdeCount;
/* off 0x1e40 */	struct _MI_SYSTEM_PTE_TYPE	SystemPteInfo;
/* off 0x1e6c */	void*	PoolTrackTableExpansion;
/* off 0x1e70 */	unsigned long	PoolTrackTableExpansionSize;
/* off 0x1e74 */	void*	PoolTrackBigPages;
/* off 0x1e78 */	unsigned long	PoolTrackBigPagesSize;
/* off 0x1e7c */	struct _RTL_BITMAP	SessionPoolPdes;
};
struct _MMVIEW /* sizeof 00000008 8 */
{
/* off 0x0000 */	unsigned long	Entry;
union
{
/* off 0x0004 */	unsigned long	Writable:1	 /* start bit 0 */;
/* off 0x0004 */	struct _CONTROL_AREA*	ControlArea;
};
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
	VfDeadlockMutexAbandoned	=0x00000002	,//0
	VfDeadlockFastMutex	=0x00000003	,//0
	VfDeadlockFastMutexUnsafe	=0x00000004	,//0
	VfDeadlockSpinLock	=0x00000005	,//0
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
struct _VI_DEADLOCK_NODE /* sizeof 0000006c 108 */
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
/* off 0x0024 */	
	union  /* sizeof 00000004 4 */
	{
	struct
	{
	/* off 0x0000 */	unsigned long	Active:1	 /* start bit 0 */;
	/* off 0x0000 */	unsigned long	OnlyTryAcquireUsed:1	 /* start bit 1 */;
	/* off 0x0000 */	unsigned long	ReleasedOutOfOrder:1	 /* start bit 2 */;
	/* off 0x0000 */	unsigned long	SequenceNumber:29	 /* start bit 3 */;
	};
	/* off 0x0000 */	unsigned long	Whole;
	}	u1;
/* off 0x0028 */	long	ChildrenCount;
/* off 0x002c */	void* StackTrace[8];
/* off 0x004c */	void* ParentStackTrace[8];
};
enum ReplacesCorHdrNumericDefines
{
	COMIMAGE_FLAGS_ILONLY	=0x00000001	,//0
	COMIMAGE_FLAGS_32BITREQUIRED	=0x00000002	,//0
	COMIMAGE_FLAGS_IL_LIBRARY	=0x00000004	,//0
	COMIMAGE_FLAGS_STRONGNAMESIGNED	=0x00000008	,//0
	COMIMAGE_FLAGS_NATIVE_ENTRYPOINT	=0x00000010	,//0
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
	COR_VTABLE_FROM_UNMANAGED_RETAIN_APPDOMAIN	=0x00000008	,//0
	COR_VTABLE_CALL_MOST_DERIVED	=0x00000010	,//0
	IMAGE_COR_EATJ_THUNK_SIZE	=0x00000020	,//0
	MAX_CLASS_NAME	=0x00000400	,//0
	MAX_PACKAGE_NAME	=0x00000400	,//0
};
struct _PHYSICAL_MEMORY_DESCRIPTOR /* sizeof 00000010 16 */
{
/* off 0x0000 */	unsigned long	NumberOfRuns;
/* off 0x0004 */	unsigned long	NumberOfPages;
/* off 0x0008 */	struct _PHYSICAL_MEMORY_RUN Run[1];
};
struct _PNP_DEVICE_EVENT_LIST /* sizeof 0000004c 76 */
{
/* off 0x0000 */	long	Status;
/* off 0x0004 */	struct _KMUTANT	EventQueueMutex;
/* off 0x0024 */	struct _KGUARDED_MUTEX	Lock;
/* off 0x0044 */	struct _LIST_ENTRY	List;
};
struct _RTLP_RANGE_LIST_ENTRY /* sizeof 00000028 40 */
{
/* off 0x0000 */	unsigned __int64	Start;
/* off 0x0008 */	unsigned __int64	End;
union
{
/* off 0x0010 */	
	struct  /* sizeof 00000008 8 */
	{
	/* off 0x0000 */	void*	UserData;
	/* off 0x0004 */	void*	Owner;
	}	Allocated;
/* off 0x0010 */	
	struct  /* sizeof 00000008 8 */
	{
	/* off 0x0000 */	struct _LIST_ENTRY	ListHead;
	}	Merged;
};
/* off 0x0018 */	unsigned char	Attributes;
/* off 0x0019 */	unsigned char	PublicFlags;
/* off 0x001a */	unsigned short	PrivateFlags;
/* off 0x001c */	struct _LIST_ENTRY	ListEntry;
};
struct PROCESSOR_IDLESTATE_INFO /* sizeof 00000008 8 */
{
/* off 0x0000 */	unsigned long	TimeCheck;
/* off 0x0004 */	unsigned char	DemotePercent;
/* off 0x0005 */	unsigned char	PromotePercent;
/* off 0x0006 */	unsigned char Spare[2];
};
struct PROCESSOR_IDLESTATE_POLICY /* sizeof 00000020 32 */
{
/* off 0x0000 */	unsigned short	Revision;
/* off 0x0002 */	
	union  /* sizeof 00000002 2 */
	{
	/* off 0x0000 */	unsigned short	AsUSHORT;
	struct
	{
	/* off 0x0000 */	unsigned short	AllowScaling:1	 /* start bit 0 */;
	/* off 0x0000 */	unsigned short	Disabled:1	 /* start bit 1 */;
	/* off 0x0000 */	unsigned short	Reserved:14	 /* start bit 2 */;
	};
	}	Flags;
/* off 0x0004 */	unsigned long	PolicyCount;
/* off 0x0008 */	struct PROCESSOR_IDLESTATE_INFO Policy[3];
};
struct _PTE_TRACKER /* sizeof 00000030 48 */
{
/* off 0x0000 */	struct _LIST_ENTRY	ListEntry;
/* off 0x0008 */	struct _MDL*	Mdl;
/* off 0x000c */	unsigned long	Count;
/* off 0x0010 */	void*	SystemVa;
/* off 0x0014 */	void*	StartVa;
/* off 0x0018 */	unsigned long	Offset;
/* off 0x001c */	unsigned long	Length;
/* off 0x0020 */	unsigned long	Page;
/* off 0x0024 */	unsigned long	IoMapping:1	 /* start bit 0 */;
/* off 0x0024 */	unsigned long	Matched:1	 /* start bit 1 */;
/* off 0x0024 */	unsigned long	CacheAttribute:2	 /* start bit 2 */;
/* off 0x0024 */	unsigned long	Spare:28	 /* start bit 4 */;
/* off 0x0028 */	void*	CallingAddress;
/* off 0x002c */	void*	CallersCaller;
};
struct _MMPFNLIST /* sizeof 00000010 16 */
{
/* off 0x0000 */	unsigned long	Total;
/* off 0x0004 */	enum _MMLISTS	ListName;
/* off 0x0008 */	unsigned long	Flink;
/* off 0x000c */	unsigned long	Blink;
};
enum _MI_VAD_TYPE
{
	VadNone	=0x00000000	,//0
	VadDevicePhysicalMemory	=0x00000001	,//0
	VadImageMap	=0x00000002	,//0
	VadAwe	=0x00000003	,//0
	VadWriteWatch	=0x00000004	,//0
	VadLargePages	=0x00000005	,//0
	VadRotatePhysical	=0x00000006	,//0
	VadLargePageSection	=0x00000007	,//0
};
struct _LPCP_PORT_QUEUE /* sizeof 00000010 16 */
{
/* off 0x0000 */	struct _LPCP_NONPAGED_PORT_QUEUE*	NonPagedPortQueue;
/* off 0x0004 */	struct _KSEMAPHORE*	Semaphore;
/* off 0x0008 */	struct _LIST_ENTRY	ReceiveHead;
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
enum _KTHREAD_STATE
{
	Initialized	=0x00000000	,//0
	Ready	=0x00000001	,//0
	Running	=0x00000002	,//0
	Standby	=0x00000003	,//0
	Terminated	=0x00000004	,//0
	Waiting	=0x00000005	,//0
	Transition	=0x00000006	,//0
	DeferredReady	=0x00000007	,//0
	GateWait	=0x00000008	,//0
};
enum _OBJECT_INFORMATION_CLASS
{
	ObjectBasicInformation	=0x00000000	,//0
	ObjectNameInformation	=0x00000001	,//0
	ObjectTypeInformation	=0x00000002	,//0
	ObjectTypesInformation	=0x00000003	,//0
	ObjectHandleFlagInformation	=0x00000004	,//0
	ObjectSessionInformation	=0x00000005	,//0
	MaxObjectInfoClass	=0x00000006	,//0
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
struct _SHARED_CACHE_MAP_LIST_CURSOR /* sizeof 0000000c 12 */
{
/* off 0x0000 */	struct _LIST_ENTRY	SharedCacheMapLinks;
/* off 0x0008 */	unsigned long	Flags;
};
enum _MM_POOL_FAILURE_REASONS
{
	MmNonPagedNoPtes	=0x00000000	,//0
	MmPriorityTooLow	=0x00000001	,//0
	MmNonPagedNoPagesAvailable	=0x00000002	,//0
	MmPagedNoPtes	=0x00000003	,//0
	MmSessionPagedNoPtes	=0x00000004	,//0
	MmPagedNoPagesAvailable	=0x00000005	,//0
	MmSessionPagedNoPagesAvailable	=0x00000006	,//0
	MmPagedNoCommit	=0x00000007	,//0
	MmSessionPagedNoCommit	=0x00000008	,//0
	MmNonPagedNoResidentAvailable	=0x00000009	,//0
	MmNonPagedNoCommit	=0x0000000a	,//0
	MmMaximumFailureReason	=0x0000000b	,//0
};
struct _MM_DRIVER_VERIFIER_DATA /* sizeof 00000078 120 */
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
/* off 0x0068 */	unsigned long	OptionChanges;
/* off 0x006c */	unsigned long	VerifyMode;
/* off 0x0070 */	struct _UNICODE_STRING	PreviousBucketName;
};
struct _HEAP_FREE_ENTRY_EXTRA /* sizeof 00000004 4 */
{
/* off 0x0000 */	unsigned short	TagIndex;
/* off 0x0002 */	unsigned short	FreeBackTraceIndex;
};
struct _VI_DEADLOCK_ADDRESS_RANGE /* sizeof 00000008 8 */
{
/* off 0x0000 */	unsigned char*	Start;
/* off 0x0004 */	unsigned char*	End;
};
struct _VI_DEADLOCK_GLOBALS /* sizeof 000040e0 16608 */
{
/* off 0x0000 */	__int64	TimeAcquire;
/* off 0x0008 */	__int64	TimeRelease;
/* off 0x0010 */	struct _LIST_ENTRY*	ResourceDatabase;
/* off 0x0014 */	unsigned long	ResourceDatabaseCount;
/* off 0x0018 */	struct _VI_DEADLOCK_ADDRESS_RANGE ResourceAddressRange[1023];
/* off 0x2010 */	struct _LIST_ENTRY*	ThreadDatabase;
/* off 0x2014 */	unsigned long	ThreadDatabaseCount;
/* off 0x2018 */	struct _VI_DEADLOCK_ADDRESS_RANGE ThreadAddressRange[1023];
/* off 0x4010 */	unsigned long	AllocationFailures;
/* off 0x4014 */	unsigned long	NodesTrimmedBasedOnAge;
/* off 0x4018 */	unsigned long	NodesTrimmedBasedOnCount;
/* off 0x401c */	unsigned long	NodesSearched;
/* off 0x4020 */	unsigned long	MaxNodesSearched;
/* off 0x4024 */	unsigned long	SequenceNumber;
/* off 0x4028 */	unsigned long	RecursionDepthLimit;
/* off 0x402c */	unsigned long	SearchedNodesLimit;
/* off 0x4030 */	unsigned long	DepthLimitHits;
/* off 0x4034 */	unsigned long	SearchLimitHits;
/* off 0x4038 */	unsigned long	ABC_ACB_Skipped;
/* off 0x403c */	unsigned long	OutOfOrderReleases;
/* off 0x4040 */	unsigned long	NodesReleasedOutOfOrder;
/* off 0x4044 */	unsigned long	TotalReleases;
/* off 0x4048 */	unsigned long	RootNodesDeleted;
/* off 0x404c */	unsigned long	ForgetHistoryCounter;
/* off 0x4050 */	void*	Instigator;
/* off 0x4054 */	unsigned long	NumberOfParticipants;
/* off 0x4058 */	struct _VI_DEADLOCK_NODE* Participant[32];
/* off 0x40d8 */	long	ChildrenCountWatermark;
};
struct _PLUGPLAY_EVENT_BLOCK /* sizeof 00000040 64 */
{
/* off 0x0000 */	struct _GUID	EventGuid;
/* off 0x0010 */	enum _PLUGPLAY_EVENT_CATEGORY	EventCategory;
/* off 0x0014 */	unsigned long*	Result;
/* off 0x0018 */	unsigned long	Flags;
/* off 0x001c */	unsigned long	TotalSize;
/* off 0x0020 */	void*	DeviceObject;
/* off 0x0024 */	
	union  /* sizeof 0000001c 28 */
	{
	/* off 0x0000 */	
		struct  /* sizeof 00000014 20 */
		{
		/* off 0x0000 */	struct _GUID	ClassGuid;
		/* off 0x0010 */	wchar SymbolicLinkName[1];
		}	DeviceClass;
	/* off 0x0000 */	
		struct  /* sizeof 00000002 2 */
		{
		/* off 0x0000 */	wchar DeviceIds[1];
		}	TargetDevice;
	/* off 0x0000 */	
		struct  /* sizeof 00000002 2 */
		{
		/* off 0x0000 */	wchar DeviceId[1];
		}	InstallDevice;
	/* off 0x0000 */	
		struct  /* sizeof 00000008 8 */
		{
		/* off 0x0000 */	void*	NotificationStructure;
		/* off 0x0004 */	wchar DeviceIds[1];
		}	CustomNotification;
	/* off 0x0000 */	
		struct  /* sizeof 00000004 4 */
		{
		/* off 0x0000 */	void*	Notification;
		}	ProfileNotification;
	/* off 0x0000 */	
		struct  /* sizeof 00000008 8 */
		{
		/* off 0x0000 */	unsigned long	NotificationCode;
		/* off 0x0004 */	unsigned long	NotificationData;
		}	PowerNotification;
	/* off 0x0000 */	
		struct  /* sizeof 00000008 8 */
		{
		/* off 0x0000 */	enum _PNP_VETO_TYPE	VetoType;
		/* off 0x0004 */	wchar DeviceIdVetoNameBuffer[1];
		}	VetoNotification;
	/* off 0x0000 */	
		struct  /* sizeof 00000010 16 */
		{
		/* off 0x0000 */	struct _GUID	BlockedDriverGuid;
		}	BlockedDriverNotification;
	/* off 0x0000 */	
		struct  /* sizeof 00000002 2 */
		{
		/* off 0x0000 */	wchar ParentId[1];
		}	InvalidIDNotification;
	/* off 0x0000 */	
		struct  /* sizeof 0000001c 28 */
		{
		/* off 0x0000 */	struct _GUID	PowerSettingGuid;
		/* off 0x0010 */	unsigned char	PowerSettingChanged;
		/* off 0x0014 */	unsigned long	DataLength;
		/* off 0x0018 */	unsigned char Data[1];
		}	PowerSettingNotification;
	}	u;
};
struct _PNP_DEVICE_EVENT_ENTRY /* sizeof 00000060 96 */
{
/* off 0x0000 */	struct _LIST_ENTRY	ListEntry;
/* off 0x0008 */	unsigned long	Argument;
/* off 0x000c */	struct _KEVENT*	CallerEvent;
/* off 0x0010 */	void( __stdcall *Callback)(void*);
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
	InvalidIDEvent	=0x00000009	,//0
	PowerSettingChange	=0x0000000a	,//0
	MaxPlugEventCategory	=0x0000000b	,//0
};
struct _VF_BTS_RECORD /* sizeof 0000000c 12 */
{
/* off 0x0000 */	void*	JumpedFrom;
/* off 0x0004 */	void*	JumpedTo;
/* off 0x0008 */	unsigned long	Unused1:3	 /* start bit 0 */;
/* off 0x0008 */	unsigned long	Predicted:4	 /* start bit 3 */;
/* off 0x0008 */	unsigned long	Unused2:25	 /* start bit 7 */;
};
enum _WOW64_SHARED_INFORMATION
{
	SharedNtdll32LdrInitializeThunk	=0x00000000	,//0
	SharedNtdll32KiUserExceptionDispatcher	=0x00000001	,//0
	SharedNtdll32KiUserApcDispatcher	=0x00000002	,//0
	SharedNtdll32KiUserCallbackDispatcher	=0x00000003	,//0
	SharedNtdll32LdrHotPatchRoutine	=0x00000004	,//0
	SharedNtdll32ExpInterlockedPopEntrySListFault	=0x00000005	,//0
	SharedNtdll32ExpInterlockedPopEntrySListResume	=0x00000006	,//0
	SharedNtdll32ExpInterlockedPopEntrySListEnd	=0x00000007	,//0
	SharedNtdll32RtlUserThreadStart	=0x00000008	,//0
	SharedNtdll32pQueryProcessDebugInformationRemote	=0x00000009	,//0
	SharedNtdll32EtwpNotificationThread	=0x0000000a	,//0
	SharedNtdll32BaseAddress	=0x0000000b	,//0
	Wow64SharedPageEntriesCount	=0x0000000c	,//0
};
enum _REG_NOTIFY_CLASS
{
	RegNtDeleteKey	=0x00000000	,//0
	RegNtPreDeleteKey	=0x00000000	,//0
	RegNtSetValueKey	=0x00000001	,//0
	RegNtPreSetValueKey	=0x00000001	,//0
	RegNtDeleteValueKey	=0x00000002	,//0
	RegNtPreDeleteValueKey	=0x00000002	,//0
	RegNtSetInformationKey	=0x00000003	,//0
	RegNtPreSetInformationKey	=0x00000003	,//0
	RegNtRenameKey	=0x00000004	,//0
	RegNtPreRenameKey	=0x00000004	,//0
	RegNtEnumerateKey	=0x00000005	,//0
	RegNtPreEnumerateKey	=0x00000005	,//0
	RegNtEnumerateValueKey	=0x00000006	,//0
	RegNtPreEnumerateValueKey	=0x00000006	,//0
	RegNtQueryKey	=0x00000007	,//0
	RegNtPreQueryKey	=0x00000007	,//0
	RegNtQueryValueKey	=0x00000008	,//0
	RegNtPreQueryValueKey	=0x00000008	,//0
	RegNtQueryMultipleValueKey	=0x00000009	,//0
	RegNtPreQueryMultipleValueKey	=0x00000009	,//0
	RegNtPreCreateKey	=0x0000000a	,//0
	RegNtPostCreateKey	=0x0000000b	,//0
	RegNtPreOpenKey	=0x0000000c	,//0
	RegNtPostOpenKey	=0x0000000d	,//0
	RegNtKeyHandleClose	=0x0000000e	,//0
	RegNtPreKeyHandleClose	=0x0000000e	,//0
	RegNtPostDeleteKey	=0x0000000f	,//0
	RegNtPostSetValueKey	=0x00000010	,//0
	RegNtPostDeleteValueKey	=0x00000011	,//0
	RegNtPostSetInformationKey	=0x00000012	,//0
	RegNtPostRenameKey	=0x00000013	,//0
	RegNtPostEnumerateKey	=0x00000014	,//0
	RegNtPostEnumerateValueKey	=0x00000015	,//0
	RegNtPostQueryKey	=0x00000016	,//0
	RegNtPostQueryValueKey	=0x00000017	,//0
	RegNtPostQueryMultipleValueKey	=0x00000018	,//0
	RegNtPostKeyHandleClose	=0x00000019	,//0
	RegNtPreCreateKeyEx	=0x0000001a	,//0
	RegNtPostCreateKeyEx	=0x0000001b	,//0
	RegNtPreOpenKeyEx	=0x0000001c	,//0
	RegNtPostOpenKeyEx	=0x0000001d	,//0
	RegNtPreFlushKey	=0x0000001e	,//0
	RegNtPostFlushKey	=0x0000001f	,//0
	RegNtPreLoadKey	=0x00000020	,//0
	RegNtPostLoadKey	=0x00000021	,//0
	RegNtPreUnLoadKey	=0x00000022	,//0
	RegNtPostUnLoadKey	=0x00000023	,//0
	RegNtPreQueryKeySecurity	=0x00000024	,//0
	RegNtPostQueryKeySecurity	=0x00000025	,//0
	RegNtPreSetKeySecurity	=0x00000026	,//0
	RegNtPostSetKeySecurity	=0x00000027	,//0
	RegNtCallbackObjectContextCleanup	=0x00000028	,//0
	RegNtPreRestoreKey	=0x00000029	,//0
	RegNtPostRestoreKey	=0x0000002a	,//0
	RegNtPreSaveKey	=0x0000002b	,//0
	RegNtPostSaveKey	=0x0000002c	,//0
	RegNtPreReplaceKey	=0x0000002d	,//0
	RegNtPostReplaceKey	=0x0000002e	,//0
	MaxRegNtNotifyClass	=0x0000002f	,//0
};
struct _OBJECT_SYMBOLIC_LINK /* sizeof 00000020 32 */
{
/* off 0x0000 */	union _LARGE_INTEGER	CreationTime;
/* off 0x0008 */	struct _UNICODE_STRING	LinkTarget;
/* off 0x0010 */	struct _UNICODE_STRING	LinkTargetRemaining;
/* off 0x0018 */	void*	LinkTargetObject;
/* off 0x001c */	unsigned long	DosDeviceDriveIndex;
};
struct _VF_TRACKER /* sizeof 00000010 16 */
{
/* off 0x0000 */	unsigned long	TrackerFlags;
/* off 0x0004 */	unsigned long	TrackerSize;
/* off 0x0008 */	unsigned long	TrackerIndex;
/* off 0x000c */	unsigned long	TraceDepth;
};
struct _CALL_PERFORMANCE_DATA /* sizeof 00000204 516 */
{
/* off 0x0000 */	unsigned long	SpinLock;
/* off 0x0004 */	struct _LIST_ENTRY HashTable[64];
};
enum _MI_DYNAMIC_MEMORY_LOCKTYPE
{
	AlreadyHeld	=0x00000000	,//0
	AcquiredShared	=0x00000001	,//0
	UseSpinLock	=0x00000002	,//0
	UseSpinLockRaiseIrql	=0x00000003	,//0
};
struct _STACK_TABLE /* sizeof 00008040 32832 */
{
/* off 0x0000 */	unsigned short	NumStackTraces;
/* off 0x0002 */	unsigned short	TraceCapacity;
/* off 0x0004 */	struct _OBJECT_REF_TRACE* StackTrace[16];
/* off 0x0044 */	unsigned short StackTableHash[16381];
};
struct _OBJECT_REF_TRACE /* sizeof 00000040 64 */
{
/* off 0x0000 */	void* StackTrace[16];
};
struct _DEFERRED_WRITE /* sizeof 00000028 40 */
{
/* off 0x0000 */	short	NodeTypeCode;
/* off 0x0002 */	short	NodeByteSize;
/* off 0x0004 */	struct _FILE_OBJECT*	FileObject;
/* off 0x0008 */	unsigned long	BytesToWrite;
/* off 0x000c */	struct _LIST_ENTRY	DeferredWriteLinks;
/* off 0x0014 */	struct _KEVENT*	Event;
/* off 0x0018 */	void( __stdcall *PostRoutine)(void*,void*);
/* off 0x001c */	void*	Context1;
/* off 0x0020 */	void*	Context2;
/* off 0x0024 */	unsigned char	LimitModifiedPages;
};
