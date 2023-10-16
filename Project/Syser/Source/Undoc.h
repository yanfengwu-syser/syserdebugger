// My header which contains undocumented structures & function prototypes
// used in BS
//
// Some structs are taken from Bo Branten's ntifs.h, some from NTOSKRNL.PDB for
// Whistler build 2462 (this build contain type info in them), and other sources

#ifndef __UNDOC_ 
#define __UNDOC_


#ifdef __cplusplus
extern "C"  {
#endif

typedef unsigned long DWORD, *PDWORD;
typedef unsigned short WORD, *PWORD;
typedef unsigned char BYTE, *PBYTE;

typedef struct _KTHREAD *PKTHREAD, *PRKTHREAD;
typedef struct _KPROCESS *PKPROCESS ,*PRKPROCESS;
typedef struct _PEB *PPEB;
typedef struct _KINTERRUPT *PKINTERRUPT;
typedef struct _IO_TIMER *PIO_TIMER;
typedef struct _OBJECT_TYPE *POBJECT_TYPE;
typedef struct _CALLBACK_OBJECT *PCALLBACK_OBJECT;
typedef struct _DEVICE_HANDLER_OBJECT *PDEVICE_HANDLER_OBJECT;
typedef struct _BUS_HANDLER *PBUS_HANDLER;

#define ACCESS_ALLOWED_ACE_TYPE         (0x0)
#define ACCESS_DENIED_ACE_TYPE          (0x1)
#define SYSTEM_AUDIT_ACE_TYPE           (0x2)
#define SYSTEM_ALARM_ACE_TYPE           (0x3)

#define ANSI_DOS_STAR                   ('<')
#define ANSI_DOS_QM                     ('>')
#define ANSI_DOS_DOT                    ('"')

#define DOS_STAR                        (L'<')
#define DOS_QM                          (L'>')
#define DOS_DOT                         (L'"')

#define FILE_ACTION_ADDED               0x00000001
#define FILE_ACTION_REMOVED             0x00000002
#define FILE_ACTION_MODIFIED            0x00000003
#define FILE_ACTION_RENAMED_OLD_NAME    0x00000004
#define FILE_ACTION_RENAMED_NEW_NAME    0x00000005
#define FILE_ACTION_ADDED_STREAM        0x00000006
#define FILE_ACTION_REMOVED_STREAM      0x00000007
#define FILE_ACTION_MODIFIED_STREAM     0x00000008

#define FILE_EA_TYPE_BINARY             0xfffe
#define FILE_EA_TYPE_ASCII              0xfffd
#define FILE_EA_TYPE_BITMAP             0xfffb
#define FILE_EA_TYPE_METAFILE           0xfffa
#define FILE_EA_TYPE_ICON               0xfff9
#define FILE_EA_TYPE_EA                 0xffee
#define FILE_EA_TYPE_MVMT               0xffdf
#define FILE_EA_TYPE_MVST               0xffde
#define FILE_EA_TYPE_ASN1               0xffdd
#define FILE_EA_TYPE_FAMILY_IDS         0xff01

#define FILE_NEED_EA                    0x00000080

#define FILE_NOTIFY_CHANGE_FILE_NAME    0x00000001
#define FILE_NOTIFY_CHANGE_DIR_NAME     0x00000002
#define FILE_NOTIFY_CHANGE_NAME         0x00000003
#define FILE_NOTIFY_CHANGE_ATTRIBUTES   0x00000004
#define FILE_NOTIFY_CHANGE_SIZE         0x00000008
#define FILE_NOTIFY_CHANGE_LAST_WRITE   0x00000010
#define FILE_NOTIFY_CHANGE_LAST_ACCESS  0x00000020
#define FILE_NOTIFY_CHANGE_CREATION     0x00000040
#define FILE_NOTIFY_CHANGE_EA           0x00000080
#define FILE_NOTIFY_CHANGE_SECURITY     0x00000100
#define FILE_NOTIFY_CHANGE_STREAM_NAME  0x00000200
#define FILE_NOTIFY_CHANGE_STREAM_SIZE  0x00000400
#define FILE_NOTIFY_CHANGE_STREAM_WRITE 0x00000800
#define FILE_NOTIFY_VALID_MASK          0x00000fff

#define FILE_OPLOCK_BROKEN_TO_LEVEL_2   0x00000007
#define FILE_OPLOCK_BROKEN_TO_NONE      0x00000008

#define FILE_OPBATCH_BREAK_UNDERWAY     0x00000009

#define FILE_CASE_SENSITIVE_SEARCH      0x00000001
#define FILE_CASE_PRESERVED_NAMES       0x00000002
#define FILE_UNICODE_ON_DISK            0x00000004
#define FILE_PERSISTENT_ACLS            0x00000008
#define FILE_FILE_COMPRESSION           0x00000010
#define FILE_VOLUME_IS_COMPRESSED       0x00008000

#define FILE_PIPE_BYTE_STREAM_TYPE      0x00000000
#define FILE_PIPE_MESSAGE_TYPE          0x00000001

#define FILE_PIPE_BYTE_STREAM_MODE      0x00000000
#define FILE_PIPE_MESSAGE_MODE          0x00000001

#define FILE_PIPE_QUEUE_OPERATION       0x00000000
#define FILE_PIPE_COMPLETE_OPERATION    0x00000001

#define FILE_PIPE_INBOUND               0x00000000
#define FILE_PIPE_OUTBOUND              0x00000001
#define FILE_PIPE_FULL_DUPLEX           0x00000002

#define FILE_PIPE_DISCONNECTED_STATE    0x00000001
#define FILE_PIPE_LISTENING_STATE       0x00000002
#define FILE_PIPE_CONNECTED_STATE       0x00000003
#define FILE_PIPE_CLOSING_STATE         0x00000004

#define FILE_PIPE_CLIENT_END            0x00000000
#define FILE_PIPE_SERVER_END            0x00000001

#define FILE_PIPE_READ_DATA             0x00000000
#define FILE_PIPE_WRITE_SPACE           0x00000001

#define FILE_STORAGE_TYPE_SPECIFIED             0x00000041  // FILE_DIRECTORY_FILE | FILE_NON_DIRECTORY_FILE
#define FILE_STORAGE_TYPE_DEFAULT               (StorageTypeDefault << FILE_STORAGE_TYPE_SHIFT)
#define FILE_STORAGE_TYPE_DIRECTORY             (StorageTypeDirectory << FILE_STORAGE_TYPE_SHIFT)
#define FILE_STORAGE_TYPE_FILE                  (StorageTypeFile << FILE_STORAGE_TYPE_SHIFT)
#define FILE_STORAGE_TYPE_DOCFILE               (StorageTypeDocfile << FILE_STORAGE_TYPE_SHIFT)
#define FILE_STORAGE_TYPE_JUNCTION_POINT        (StorageTypeJunctionPoint << FILE_STORAGE_TYPE_SHIFT)
#define FILE_STORAGE_TYPE_CATALOG               (StorageTypeCatalog << FILE_STORAGE_TYPE_SHIFT)
#define FILE_STORAGE_TYPE_STRUCTURED_STORAGE    (StorageTypeStructuredStorage << FILE_STORAGE_TYPE_SHIFT)
#define FILE_STORAGE_TYPE_EMBEDDING             (StorageTypeEmbedding << FILE_STORAGE_TYPE_SHIFT)
#define FILE_STORAGE_TYPE_STREAM                (StorageTypeStream << FILE_STORAGE_TYPE_SHIFT)
#define FILE_MINIMUM_STORAGE_TYPE               FILE_STORAGE_TYPE_DEFAULT
#define FILE_MAXIMUM_STORAGE_TYPE               FILE_STORAGE_TYPE_STREAM
#define FILE_STORAGE_TYPE_MASK                  0x000f0000
#define FILE_STORAGE_TYPE_SHIFT                 16

#define FILE_VC_QUOTA_NONE              0x00000000
#define FILE_VC_QUOTA_TRACK             0x00000001
#define FILE_VC_QUOTA_ENFORCE           0x00000002
#define FILE_VC_QUOTA_MASK              0x00000003

#define FILE_VC_QUOTAS_LOG_VIOLATIONS   0x00000004
#define FILE_VC_CONTENT_INDEX_DISABLED  0x00000008

#define FILE_VC_LOG_QUOTA_THRESHOLD     0x00000010
#define FILE_VC_LOG_QUOTA_LIMIT         0x00000020
#define FILE_VC_LOG_VOLUME_THRESHOLD    0x00000040
#define FILE_VC_LOG_VOLUME_LIMIT        0x00000080

#define FILE_VC_QUOTAS_INCOMPLETE       0x00000100
#define FILE_VC_QUOTAS_REBUILDING       0x00000200

#define FILE_VC_VALID_MASK              0x000003ff

#define FSRTL_FLAG_ACQUIRE_MAIN_RSRC_EX (0x08)
#define FSRTL_FLAG_ACQUIRE_MAIN_RSRC_SH (0x10)

#define FSRTL_FSP_TOP_LEVEL_IRP         (0x01)
#define FSRTL_CACHE_TOP_LEVEL_IRP       (0x02)
#define FSRTL_MOD_WRITE_TOP_LEVEL_IRP   (0x03)
#define FSRTL_FAST_IO_TOP_LEVEL_IRP     (0x04)
#define FSRTL_MAX_TOP_LEVEL_IRP_FLAG    (0x04)

#define FSRTL_WILD_CHARACTER            0x08

#define IO_CHECK_CREATE_PARAMETERS      0x0200
#define IO_ATTACH_DEVICE                0x0400

#define IO_ATTACH_DEVICE_API            0x80000000

#define IO_COMPLETION_QUERY_STATE       0x0001
#define IO_COMPLETION_MODIFY_STATE      0x0002
#define IO_COMPLETION_ALL_ACCESS        (STANDARD_RIGHTS_REQUIRED|SYNCHRONIZE|0x3)

#define IO_TYPE_APC                     18
#define IO_TYPE_DPC                     19
#define IO_TYPE_DEVICE_QUEUE            20
#define IO_TYPE_EVENT_PAIR              21
#define IO_TYPE_INTERRUPT               22
#define IO_TYPE_PROFILE                 23

#define LPC_REQUEST                     0x0001
#define LPC_REPLY                       0x0002
#define LPC_DATAGRAM                    0x0003
#define LPC_LOST_REPLY                  0x0004
#define LPC_PORT_CLOSED                 0x0005
#define LPC_CLIENT_DIED                 0x0006
#define LPC_EXCEPTION                   0x0007
#define LPC_DEBUG_EVENT                 0x0008
#define LPC_ERROR_EVENT                 0x0009
#define LPC_CONNECTION_REQUEST          0x000A

#define MAILSLOT_CLASS_FIRSTCLASS       1
#define MAILSLOT_CLASS_SECONDCLASS      2

#define MAILSLOT_SIZE_AUTO              0

#define MAP_PROCESS                     1L
#define MAP_SYSTEM                      2L

#define MEM_DOS_LIM                     0x40000000
#define MEM_IMAGE                       SEC_IMAGE

#define OB_TYPE_TYPE                    1
#define OB_TYPE_DIRECTORY               2
#define OB_TYPE_SYMBOLIC_LINK           3
#define OB_TYPE_TOKEN                   4
#define OB_TYPE_PROCESS                 5
#define OB_TYPE_THREAD                  6
#define OB_TYPE_EVENT                   7
#define OB_TYPE_EVENT_PAIR              8
#define OB_TYPE_MUTANT                  9
#define OB_TYPE_SEMAPHORE               10
#define OB_TYPE_TIMER                   11
#define OB_TYPE_PROFILE                 12
#define OB_TYPE_WINDOW_STATION          13
#define OB_TYPE_DESKTOP                 14
#define OB_TYPE_SECTION                 15
#define OB_TYPE_KEY                     16
#define OB_TYPE_PORT                    17
#define OB_TYPE_ADAPTER                 18
#define OB_TYPE_CONTROLLER              19
#define OB_TYPE_DEVICE                  20
#define OB_TYPE_DRIVER                  21
#define OB_TYPE_IO_COMPLETION           22
#define OB_TYPE_FILE                    23

#define PORT_CONNECT                    0x0001
#define PORT_ALL_ACCESS                 (STANDARD_RIGHTS_ALL |\
                                         PORT_CONNECT)

#define SEC_BASED                       0x00200000
#define SEC_NO_CHANGE                   0x00400000
#define SEC_FILE                        0x00800000
#define SEC_IMAGE                       0x01000000
//#define SEC_COMMIT                      0x08000000
#define SEC_NOCACHE                     0x10000000

#define SECURITY_WORLD_SID_AUTHORITY    {0,0,0,0,0,1}
#define SECURITY_WORLD_RID              (0x00000000L)

#define THREAD_STATE_INITIALIZED        0
#define THREAD_STATE_READY              1
#define THREAD_STATE_RUNNING            2
#define THREAD_STATE_STANDBY            3
#define THREAD_STATE_TERMINATED         4
#define THREAD_STATE_WAIT               5
#define THREAD_STATE_TRANSITION         6
#define THREAD_STATE_UNKNOWN            7

#define TOKEN_ASSIGN_PRIMARY            (0x0001)
#define TOKEN_DUPLICATE                 (0x0002)
#define TOKEN_IMPERSONATE               (0x0004)
#define TOKEN_QUERY                     (0x0008)
#define TOKEN_QUERY_SOURCE              (0x0010)
#define TOKEN_ADJUST_PRIVILEGES         (0x0020)
#define TOKEN_ADJUST_GROUPS             (0x0040)
#define TOKEN_ADJUST_DEFAULT            (0x0080)

#define TOKEN_ALL_ACCESS (STANDARD_RIGHTS_REQUIRED |\
                          TOKEN_ASSIGN_PRIMARY     |\
                          TOKEN_DUPLICATE          |\
                          TOKEN_IMPERSONATE        |\
                          TOKEN_QUERY              |\
                          TOKEN_QUERY_SOURCE       |\
                          TOKEN_ADJUST_PRIVILEGES  |\
                          TOKEN_ADJUST_GROUPS      |\
                          TOKEN_ADJUST_DEFAULT)

#define TOKEN_READ       (STANDARD_RIGHTS_READ     |\
                          TOKEN_QUERY)

#define TOKEN_WRITE      (STANDARD_RIGHTS_WRITE    |\
                          TOKEN_ADJUST_PRIVILEGES  |\
                          TOKEN_ADJUST_GROUPS      |\
                          TOKEN_ADJUST_DEFAULT)

#define TOKEN_EXECUTE    (STANDARD_RIGHTS_EXECUTE)

#define TOKEN_SOURCE_LENGTH 8

#define FSCTL_GET_VOLUME_INFORMATION    0x90064
#define FSCTL_READ_MFT_RECORD           0x90068

#define FSCTL_MAILSLOT_PEEK             CTL_CODE(FILE_DEVICE_MAILSLOT, 0, METHOD_NEITHER, FILE_READ_DATA)

#define FSCTL_PIPE_ASSIGN_EVENT         CTL_CODE(FILE_DEVICE_NAMED_PIPE, 0, METHOD_BUFFERED, FILE_ANY_ACCESS)
#define FSCTL_PIPE_DISCONNECT           CTL_CODE(FILE_DEVICE_NAMED_PIPE, 1, METHOD_BUFFERED, FILE_ANY_ACCESS)
#define FSCTL_PIPE_LISTEN               CTL_CODE(FILE_DEVICE_NAMED_PIPE, 2, METHOD_BUFFERED, FILE_ANY_ACCESS)
#define FSCTL_PIPE_PEEK                 CTL_CODE(FILE_DEVICE_NAMED_PIPE, 3, METHOD_BUFFERED, FILE_READ_DATA)
#define FSCTL_PIPE_QUERY_EVENT          CTL_CODE(FILE_DEVICE_NAMED_PIPE, 4, METHOD_BUFFERED, FILE_ANY_ACCESS)
#define FSCTL_PIPE_TRANSCEIVE           CTL_CODE(FILE_DEVICE_NAMED_PIPE, 5, METHOD_NEITHER,  FILE_READ_DATA | FILE_WRITE_DATA)
#define FSCTL_PIPE_WAIT                 CTL_CODE(FILE_DEVICE_NAMED_PIPE, 6, METHOD_BUFFERED, FILE_ANY_ACCESS)
#define FSCTL_PIPE_IMPERSONATE          CTL_CODE(FILE_DEVICE_NAMED_PIPE, 7, METHOD_BUFFERED, FILE_ANY_ACCESS)
#define FSCTL_PIPE_SET_CLIENT_PROCESS   CTL_CODE(FILE_DEVICE_NAMED_PIPE, 8, METHOD_BUFFERED, FILE_ANY_ACCESS)
#define FSCTL_PIPE_QUERY_CLIENT_PROCESS CTL_CODE(FILE_DEVICE_NAMED_PIPE, 9, METHOD_BUFFERED, FILE_ANY_ACCESS)

#define FSCTL_PIPE_INTERNAL_READ        CTL_CODE(FILE_DEVICE_NAMED_PIPE, 2045, METHOD_BUFFERED, FILE_READ_DATA)
#define FSCTL_PIPE_INTERNAL_WRITE       CTL_CODE(FILE_DEVICE_NAMED_PIPE, 2046, METHOD_BUFFERED, FILE_WRITE_DATA)
#define FSCTL_PIPE_INTERNAL_TRANSCEIVE  CTL_CODE(FILE_DEVICE_NAMED_PIPE, 2047, METHOD_NEITHER, FILE_READ_DATA | FILE_WRITE_DATA)
#define FSCTL_PIPE_INTERNAL_READ_OVFLOW CTL_CODE(FILE_DEVICE_NAMED_PIPE, 2048, METHOD_BUFFERED, FILE_READ_DATA)

#define IOCTL_REDIR_QUERY_PATH          CTL_CODE(FILE_DEVICE_NETWORK_FILE_SYSTEM, 99, METHOD_NEITHER, FILE_ANY_ACCESS)

typedef PVOID PNOTIFY_SYNC;
typedef PVOID POBJECT;
typedef PVOID PPS_IMPERSONATION_INFO;
typedef PVOID PSECURITY_CLIENT_CONTEXT;

typedef struct _EPROCESS_QUOTA_BLOCK        *PEPROCESS_QUOTA_BLOCK;
typedef struct _HANDLE_TABLE                *PHANDLE_TABLE;
typedef struct _KEVENT_PAIR                 *PKEVENT_PAIR;
typedef struct _LPC_MESSAGE                 *PLPC_MESSAGE;
typedef struct _MMWSL                       *PMMWSL;
typedef struct _PEB                         *PPEB;
typedef struct _SERVICE_DESCRIPTOR_TABLE    *PSERVICE_DESCRIPTOR_TABLE;
typedef struct _TEB                         *PTEB;

typedef struct _SYSTEM_QUERY_TIME_ADJUSTMENT
{
	ULONG TimeAdjustment;
	ULONG MaximumIncrement;
	BOOLEAN TimeSynchronization;
}SYSTEM_QUERY_TIME_ADJUSTMENT,*PSYSTEM_QUERY_TIME_ADJUSTMENT;


typedef enum _FAST_IO_POSSIBLE {
    FastIoIsPossible,
    FastIoIsNotPossible,
    FastIoIsQuestionable
} FAST_IO_POSSIBLE;

typedef enum _FILE_STORAGE_TYPE {
    StorageTypeDefault = 1,
    StorageTypeDirectory,
    StorageTypeFile,
    StorageTypeJunctionPoint,
    StorageTypeCatalog,
    StorageTypeStructuredStorage,
    StorageTypeEmbedding,
    StorageTypeStream
} FILE_STORAGE_TYPE;

typedef enum _IO_COMPLETION_INFORMATION_CLASS {
    IoCompletionBasicInformation
} IO_COMPLETION_INFORMATION_CLASS;

typedef enum _MMFLUSH_TYPE {
    MmFlushForDelete,
    MmFlushForWrite
} MMFLUSH_TYPE;

typedef enum _OBJECT_INFO_CLASS {
    ObjectBasicInfo,
    ObjectNameInfo,
    ObjectTypeInfo,
    ObjectAllTypesInfo,
    ObjectProtectionInfo
} OBJECT_INFO_CLASS;

typedef enum _PORT_INFORMATION_CLASS {
    PortNoInformation
} PORT_INFORMATION_CLASS;

typedef enum _SID_NAME_USE {
    SidTypeUser = 1,
    SidTypeGroup,
    SidTypeDomain,
    SidTypeAlias,
    SidTypeWellKnownGroup,
    SidTypeDeletedAccount,
    SidTypeInvalid,
    SidTypeUnknown
} SID_NAME_USE;

typedef enum _TOKEN_INFORMATION_CLASS {
    TokenUser = 1,
    TokenGroups,
    TokenPrivileges,
    TokenOwner,
    TokenPrimaryGroup,
    TokenDefaultDacl,
    TokenSource,
    TokenType,
    TokenImpersonationLevel,
    TokenStatistics,
    TokenRestrictedSids
} TOKEN_INFORMATION_CLASS;

typedef enum _TOKEN_TYPE {
    TokenPrimary = 1,
    TokenImpersonation
} TOKEN_TYPE;

typedef struct _HARDWARE_PTE {
    ULONG Valid             : 1;
    ULONG Write             : 1;
    ULONG Owner             : 1;
    ULONG WriteThrough      : 1;
    ULONG CacheDisable      : 1;
    ULONG Accessed          : 1;
    ULONG Dirty             : 1;
    ULONG LargePage         : 1;
    ULONG Global            : 1;
    ULONG CopyOnWrite       : 1;
    ULONG Prototype         : 1;
    ULONG Reserved          : 1;
    ULONG PageFrameNumber   : 20;
} HARDWARE_PTE, *PHARDWARE_PTE;

typedef struct _KAPC_STATE {
    LIST_ENTRY  ApcListHead[2];
    PEPROCESS   Process;
    BOOLEAN     KernelApcInProgress;
    BOOLEAN     KernelApcPending;
    BOOLEAN     UserApcPending;
} KAPC_STATE, *PKAPC_STATE;


typedef struct _KTRAP_FRAME
{
    DWORD DbgEbp;
    DWORD DbgEip;
    DWORD DbgArgMark;
    DWORD DbgArgPointer;
    DWORD TempSegCs;
    DWORD TempEsp;
    DWORD Dr0;
    DWORD Dr1;
    DWORD Dr2;
    DWORD Dr3;
    DWORD Dr6;
    DWORD Dr7;
    DWORD SegGs;
    DWORD SegEs;
    DWORD SegDs;
    DWORD Edx;
    DWORD Ecx;
    DWORD Eax;
    DWORD PreviousPreviousMode;
    struct _EXCEPTION_REGISTRATION_RECORD* ExceptionList;
    DWORD SegFs;
    DWORD Edi;
    DWORD Esi;
    DWORD Ebx;
    DWORD Ebp;
    DWORD ErrCode;
    DWORD Eip;
    DWORD SegCs;
    DWORD EFlags;
    DWORD HardwareEsp;
    DWORD HardwareSegSs;
    DWORD V86Es;
    DWORD V86Ds;
    DWORD V86Fs;
    DWORD V86Gs;
} KTRAP_FRAME;

typedef struct _KPROCESS {
    DISPATCHER_HEADER   Header;
    LIST_ENTRY          ProfileListHead;
    UCHAR               DirectoryTableBase[8];
    UCHAR               LdtDescriptor[8];
    UCHAR               Int21Descriptor[8];
    USHORT              IopmOffset;
    UCHAR               Iopl;
    UCHAR               VdmFlag;
    ULONG               ActiveProcessors;
    ULONG               KernelTime;
    ULONG               UserTime;
    LIST_ENTRY          ReadyListHead;  
    LIST_ENTRY          SwapListEntry;
    LIST_ENTRY          ThreadListHead;
    KSPIN_LOCK          ProcessLock;
    KAFFINITY           Affinity;
    USHORT              StackCount;
    UCHAR               BasePriority;
    UCHAR               ThreadQuantum;
    BOOLEAN             AutoAlignment;
    UCHAR               State;
    UCHAR               ThreadSeed;
    BOOLEAN             DisableBoost;
} KPROCESS, *PKPROCESS;

typedef struct _KTHREAD {
    DISPATCHER_HEADER           Header;
    LIST_ENTRY                  MutantListHead;
    PVOID                       InitialStack;
    PVOID                       StackLimit;
    PTEB                        Teb;
    PVOID                       TlsArray;
    PVOID                       KernelStack;
    BOOLEAN                     DebugActive;
    UCHAR                       State;
    USHORT                      Alerted;
    UCHAR                       Iopl;
    UCHAR                       NpxState;
    UCHAR                       Saturation;
    UCHAR                       Priority;
    KAPC_STATE                  ApcState;
    ULONG                       ContextSwitches;
    NTSTATUS                    WaitStatus;
    UCHAR                       WaitIrql;
    UCHAR                       WaitMode;
    UCHAR                       WaitNext;
    UCHAR                       WaitReason;
    PVOID                       WaitBlockList;
    LIST_ENTRY                  WaitListEntry;
    ULONG                       WaitTime;
    UCHAR                       BasePriority;
    UCHAR                       DecrementCount;
    UCHAR                       PriorityDecrement;
    UCHAR                       Quantum;
    KWAIT_BLOCK                 WaitBlock[4];
    ULONG                       LegoData;
    ULONG                       KernelApcDisable;
    ULONG                       UserAffinity;
    BOOLEAN                     SystemAffinityActive;
    UCHAR                       Pad[3];
    PSERVICE_DESCRIPTOR_TABLE   ServiceDescriptorTable;
    PVOID                       Queue;
    KSPIN_LOCK                  ApcQueueLock;
    KTIMER                      Timer;
    LIST_ENTRY                  QueueListEntry;
    ULONG                       Affinity;
    BOOLEAN                     Preempted;
    BOOLEAN                     ProcessReadyQueue;
    BOOLEAN                     KernelStackResident;
    UCHAR                       NextProcessor;
    PVOID                       CallbackStack;
    PVOID                       Win32Thread;
    KTRAP_FRAME					*TrapFrame;
    PVOID                       ApcStatePointer[2];
    BOOLEAN                     EnableStackSwap;
    BOOLEAN                     LargeStack;
    UCHAR                       ResourceIndex;
    UCHAR                       PreviousMode;
    ULONG                       KernelTime;
    ULONG                       UserTime;
    KAPC_STATE                  SavedApcState;
    BOOLEAN                     Alertable;
    UCHAR                       ApcStateIndex;
    BOOLEAN                     ApcQueueable;
    BOOLEAN                     AutoAlignment;
    PVOID                       StackBase;
    KAPC                        SuspendApc;
    KSEMAPHORE                  SuspendSemaphore;
    LIST_ENTRY                  ThreadListEntry;
    UCHAR                       FreezeCount;
    UCHAR                       SuspendCount;
    UCHAR                       IdealProcessor;
    BOOLEAN                     DisableBoost;
} KTHREAD, *PKTHREAD;

typedef struct _MMSUPPORT {
    LARGE_INTEGER   LastTrimTime;
    ULONG           LastTrimFaultCount;
    ULONG           PageFaultCount;
    ULONG           PeakWorkingSetSize;
    ULONG           WorkingSetSize;
    ULONG           MinimumWorkingSetSize;
    ULONG           MaximumWorkingSetSize;
    PMMWSL          VmWorkingSetList;
    LIST_ENTRY      WorkingSetExpansionLinks;
    BOOLEAN         AllowWorkingSetAdjustment;
    BOOLEAN         AddressSpaceBeingDeleted;
    UCHAR           ForegroundSwitchCount;
    UCHAR           MemoryPriority;
} MMSUPPORT, *PMMSUPPORT;

typedef struct _SID_IDENTIFIER_AUTHORITY {
    UCHAR Value[6];
} SID_IDENTIFIER_AUTHORITY, *PSID_IDENTIFIER_AUTHORITY;

typedef struct _SID {
    UCHAR                       Revision;
    UCHAR                       SubAuthorityCount;
    SID_IDENTIFIER_AUTHORITY    IdentifierAuthority;
    ULONG                       SubAuthority[1];
} SID, *PREAL_SID;

typedef struct _BITMAP_DESCRIPTOR {
    ULONGLONG   StartLcn;
    ULONGLONG   ClustersToEndOfVol;
    UCHAR       Map[1];
} BITMAP_DESCRIPTOR, *PBITMAP_DESCRIPTOR; 

typedef struct _CACHE_UNINITIALIZE_EVENT {
    struct _CACHE_UNINITIALIZE_EVENT    *Next;
    KEVENT                              Event;
} CACHE_UNINITIALIZE_EVENT, *PCACHE_UNINITIALIZE_EVENT;

typedef struct _CC_FILE_SIZES {
    LARGE_INTEGER AllocationSize;
    LARGE_INTEGER FileSize;
    LARGE_INTEGER ValidDataLength;
} CC_FILE_SIZES, *PCC_FILE_SIZES;

typedef struct _EPROCESS {
    KPROCESS                        Pcb;
    NTSTATUS                        ExitStatus;
    KEVENT                          LockEvent;
    ULONG                           LockCount;
    LARGE_INTEGER                   CreateTime;
    LARGE_INTEGER                   ExitTime;
    PKTHREAD                        LockOwner;
    ULONG                           UniqueProcessId;
    LIST_ENTRY                      ActiveProcessLinks;
    ULONGLONG                       QuotaPeakPoolUsage;
    ULONGLONG                       QuotaPoolUsage;
    ULONG                           PagefileUsage;
    ULONG                           CommitCharge;
    ULONG                           PeakPagefileUsage;
    ULONG                           PeakVirtualSize;
    ULONGLONG                       VirtualSize;
    MMSUPPORT                       Vm;
    ULONG                           LastProtoPteFault;
    ULONG                           DebugPort;
    ULONG                           ExceptionPort;
    PHANDLE_TABLE                   ObjectTable;
    PACCESS_TOKEN                   Token;
    KMUTEX                          WorkingSetLock;
    ULONG                           WorkingSetPage;
    BOOLEAN                         ProcessOutswapEnabled;
    BOOLEAN                         ProcessOutswapped;
    BOOLEAN                         AddressSpaceInitialized;
    BOOLEAN                         AddressSpaceDeleted;
    KMUTEX                          AddressCreationLock;
    KSPIN_LOCK                      HyperSpaceLock;
    PETHREAD                        ForkInProgress;
    USHORT                          VmOperation;
    BOOLEAN                         ForkWasSuccessful;
    UCHAR                           MmAgressiveWsTrimMask;
    PKEVENT                         VmOperationEvent;
    HARDWARE_PTE                    PageDirectoryPte;
    ULONG                           LastFaultCount;
    ULONG                           ModifiedPageCount;
    PVOID                           VadRoot;
    PVOID                           VadHint;
    ULONG                           CloneRoot;
    ULONG                           NumberOfPrivatePages;
    ULONG                           NumberOfLockedPages;
    USHORT                          NextPageColor;
    BOOLEAN                         ExitProcessCalled;
    BOOLEAN                         CreateProcessReported;
    HANDLE                          SectionHandle;
    PPEB                            Peb;
    PVOID                           SectionBaseAddress;
    PEPROCESS_QUOTA_BLOCK           QuotaBlock;
    NTSTATUS                        LastThreadExitStatus;
    PPROCESS_WS_WATCH_INFORMATION   WorkingSetWatch;
    HANDLE                          Win32WindowStation;
    HANDLE                          InheritedFromUniqueProcessId;
    ACCESS_MASK                     GrantedAccess;
    ULONG                           DefaultHardErrorProcessing;
    PVOID                           LdtInformation;
    PVOID                           VadFreeHint;
    PVOID                           VdmObjects;
    KMUTANT                         ProcessMutant;
    UCHAR                           ImageFileName[16];
    ULONG                           VmTrimFaultValue;
    UCHAR                           SetTimerResolution;
    UCHAR                           PriorityClass;
    UCHAR                           SubSystemMinorVersion;
    UCHAR                           SubSystemMajorVersion;
    PVOID                           Win32Process;
} EPROCESS, *PEPROCESS;


typedef struct _MMVad{
	DWORD							StartingVpn;
	DWORD							EndingVpn;
	struct _MMVad*					Parent;
	struct _MMVad*					LeftChild;
	struct _MMVad*					RightChild;
	struct {
		DWORD						CommitCharge:19;
		DWORD						PhysicalMapping:1;
		DWORD						ImageMap:1;
		DWORD						UserPhysicalPages:1;
		DWORD						NoChange:1;
		DWORD						WriteWatch:1;
		DWORD						Protection:5;
		DWORD						LargePages:1;
		DWORD						MemCommit:1;
		DWORD						PrivateMemory:1;
	}u;
	PVOID							ControlArea;
	DWORD							FirstPrototypePte;
	DWORD							LastContiguousPte;
	struct  {
		DWORD						FileOffset:24;
		DWORD						SecNoChange:1;
		DWORD						OneSecured:1;
		DWORD						MultipleSecured:1;
		DWORD						ReadOnly:1;
		DWORD						LongVad:1;
		DWORD						ExtendableFile:1;
		DWORD						Inherit:1;
		DWORD						CopyOnWrite:1;		
	}u2;
}MMVad,*PMMVad;

typedef struct _ETHREAD {
    KTHREAD                 Tcb;
    LARGE_INTEGER           CreateTime;
    LARGE_INTEGER           ExitTime;
    NTSTATUS                ExitStatus;
    LIST_ENTRY              PostBlockList;
    LIST_ENTRY              TerminationPortList;
    KSPIN_LOCK              ActiveTimerListLock;
    LIST_ENTRY              ActiveTimerListHead;
    CLIENT_ID               Cid;
    KSEMAPHORE              LpcReplySemaphore;
    PLPC_MESSAGE            LpcReplyMessage;
    ULONG                   LpcReplyMessageId;
    ULONG                   PerformanceCountLow;
    PPS_IMPERSONATION_INFO  ImpersonationInfo;
    LIST_ENTRY              IrpList;
    PVOID                   TopLevelIrp;
    PVOID                   DeviceToVerify;
    ULONG                   ReadClusterSize;
    BOOLEAN                 ForwardClusterOnly;
    BOOLEAN                 DisablePageFaultClustering;
    BOOLEAN                 DeadThread;
    BOOLEAN                 HasTerminated;
    PKEVENT_PAIR            EventPair;
    ACCESS_MASK             GrantedAccess;
    PEPROCESS               ThreadsProcess;
    PKSTART_ROUTINE         StartAddress;
    PVOID                   Win32StartAddress;
    BOOLEAN                 LpcExitThreadCalled;
    BOOLEAN                 HardErrorsAreDisabled;
    BOOLEAN                 LpcReceivedMsgIdValid;
    BOOLEAN                 ActiveImpersonationInfo;
    ULONG                   PerformanceCountHigh;
} ETHREAD, *PETHREAD;

/*
 * When needing these parameters cast your PIO_STACK_LOCATION to
 * PEXTENDED_IO_STACK_LOCATION
 */
#if !defined(_ALPHA_)
#include <pshpack4.h>
#endif
typedef struct _EXTENDED_IO_STACK_LOCATION {

    /* Included for padding */
    UCHAR MajorFunction;
    UCHAR MinorFunction;
    UCHAR Flags;
    UCHAR Control;

    union {

        struct {
            ULONG                   OutputBufferLength;
            ULONG                   InputBufferLength;
            ULONG                   FsControlCode;
            PVOID                   Type3InputBuffer;
        } FileSystemControl;

        struct {
            PLARGE_INTEGER          Length;
            ULONG                   Key;
            LARGE_INTEGER           ByteOffset;
        } LockControl;

        struct {
            ULONG                   Length;
            ULONG                   CompletionFilter;
        } NotifyDirectory;

        struct {
            ULONG                   Length;
            PUNICODE_STRING         FileName;
            FILE_INFORMATION_CLASS  FileInformationClass;
            ULONG                   FileIndex;
        } QueryDirectory;

        struct {
            ULONG                   Length;
            PVOID                   EaList;
            ULONG                   EaListLength;
            ULONG                   EaaIndex;
        } QueryEa;

        struct {
            ULONG                   Length;
            FS_INFORMATION_CLASS    FsInformationClass;
        } SetVolume;

    } Parameters;

} EXTENDED_IO_STACK_LOCATION, *PEXTENDED_IO_STACK_LOCATION;
#if !defined(_ALPHA_)
#include <poppack.h>
#endif

typedef struct _FILE_ACCESS_INFORMATION {
    ACCESS_MASK AccessFlags;
} FILE_ACCESS_INFORMATION, *PFILE_ACCESS_INFORMATION;

typedef struct _FILE_ALLOCATION_INFORMATION {
    LARGE_INTEGER AllocationSize;
} FILE_ALLOCATION_INFORMATION, *PFILE_ALLOCATION_INFORMATION;

typedef struct _FILE_BOTH_DIR_INFORMATION {
    ULONG           NextEntryOffset;
    ULONG           FileIndex;
    LARGE_INTEGER   CreationTime;
    LARGE_INTEGER   LastAccessTime;
    LARGE_INTEGER   LastWriteTime;
    LARGE_INTEGER   ChangeTime;
    LARGE_INTEGER   EndOfFile;
    LARGE_INTEGER   AllocationSize;
    ULONG           FileAttributes;
    ULONG           FileNameLength;
    ULONG           EaSize;
    CCHAR           ShortNameLength;
    WCHAR           ShortName[12];
    WCHAR           FileName[1];
} FILE_BOTH_DIR_INFORMATION, *PFILE_BOTH_DIR_INFORMATION;

typedef struct _FILE_COMPLETION_INFORMATION {
    HANDLE  Port;
    ULONG   Key;
} FILE_COMPLETION_INFORMATION, *PFILE_COMPLETION_INFORMATION;

typedef struct _FILE_COMPRESSION_INFORMATION {
    LARGE_INTEGER   CompressedFileSize;
    USHORT          CompressionFormat;
    UCHAR           CompressionUnitShift;
    UCHAR           ChunkShift;
    UCHAR           ClusterShift;
    UCHAR           Reserved[3];
} FILE_COMPRESSION_INFORMATION, *PFILE_COMPRESSION_INFORMATION;

typedef struct _FILE_COPY_ON_WRITE_INFORMATION {
    BOOLEAN ReplaceIfExists;
    HANDLE  RootDirectory;
    ULONG   FileNameLength;
    WCHAR   FileName[1];
} FILE_COPY_ON_WRITE_INFORMATION, *PFILE_COPY_ON_WRITE_INFORMATION;

typedef struct _FILE_DIRECTORY_INFORMATION {
    ULONG           NextEntryOffset;
    ULONG           FileIndex;
    LARGE_INTEGER   CreationTime;
    LARGE_INTEGER   LastAccessTime;
    LARGE_INTEGER   LastWriteTime;
    LARGE_INTEGER   ChangeTime;
    LARGE_INTEGER   EndOfFile;
    LARGE_INTEGER   AllocationSize;
    ULONG           FileAttributes;
    ULONG           FileNameLength;
    WCHAR           FileName[1];
} FILE_DIRECTORY_INFORMATION, *PFILE_DIRECTORY_INFORMATION;

typedef struct _FILE_EA_INFORMATION {
    ULONG EaSize;
} FILE_EA_INFORMATION, *PFILE_EA_INFORMATION;

typedef struct _FILE_FS_ATTRIBUTE_INFORMATION {
    ULONG   FileSystemAttributes;
    LONG    MaximumComponentNameLength;
    ULONG   FileSystemNameLength;
    WCHAR   FileSystemName[1];
} FILE_FS_ATTRIBUTE_INFORMATION, *PFILE_FS_ATTRIBUTE_INFORMATION;

typedef struct _FILE_FS_CONTROL_INFORMATION {
    LARGE_INTEGER   FreeSpaceStartFiltering;
    LARGE_INTEGER   FreeSpaceThreshold;
    LARGE_INTEGER   FreeSpaceStopFiltering;
    LARGE_INTEGER   DefaultQuotaThreshold;
    LARGE_INTEGER   DefaultQuotaLimit;
    ULONG           FileSystemControlFlags;
} FILE_FS_CONTROL_INFORMATION, *PFILE_FS_CONTROL_INFORMATION;

// typedef struct _FILE_FS_LABEL_INFORMATION {
//     ULONG VolumeLabelLength;
//     WCHAR VolumeLabel[1];
// } FILE_FS_LABEL_INFORMATION, *PFILE_FS_LABEL_INFORMATION;

// typedef struct _FILE_FS_SIZE_INFORMATION {
//     LARGE_INTEGER   TotalAllocationUnits;
//     LARGE_INTEGER   AvailableAllocationUnits;
//     ULONG           SectorsPerAllocationUnit;
//     ULONG           BytesPerSector;
// } FILE_FS_SIZE_INFORMATION, *PFILE_FS_SIZE_INFORMATION;

// typedef struct _FILE_FS_VOLUME_INFORMATION {
//     LARGE_INTEGER   VolumeCreationTime;
//     ULONG           VolumeSerialNumber;
//     ULONG           VolumeLabelLength;
//     BOOLEAN         SupportsObjects;
//     WCHAR           VolumeLabel[1];
// } FILE_FS_VOLUME_INFORMATION, *PFILE_FS_VOLUME_INFORMATION;

typedef struct _FILE_FULL_DIR_INFORMATION {
    ULONG           NextEntryOffset;
    ULONG           FileIndex;
    LARGE_INTEGER   CreationTime;
    LARGE_INTEGER   LastAccessTime;
    LARGE_INTEGER   LastWriteTime;
    LARGE_INTEGER   ChangeTime;
    LARGE_INTEGER   EndOfFile;
    LARGE_INTEGER   AllocationSize;
    ULONG           FileAttributes;
    ULONG           FileNameLength;
    ULONG           EaSize;
    WCHAR           FileName[1];
} FILE_FULL_DIR_INFORMATION, *PFILE_FULL_DIR_INFORMATION;

typedef struct _FILE_GET_EA_INFORMATION {
    ULONG   NextEntryOffset;
    UCHAR   EaNameLength;
    CHAR    EaName[1];
} FILE_GET_EA_INFORMATION, *PFILE_GET_EA_INFORMATION;

typedef struct _FILE_GET_QUOTA_INFORMATION {
    ULONG   NextEntryOffset;
    ULONG   SidLength;
    SID     Sid;
} FILE_GET_QUOTA_INFORMATION, *PFILE_GET_QUOTA_INFORMATION;

typedef struct _FILE_INTERNAL_INFORMATION {
    LARGE_INTEGER IndexNumber;
} FILE_INTERNAL_INFORMATION, *PFILE_INTERNAL_INFORMATION;

typedef struct _FILE_LINK_INFORMATION {
    BOOLEAN ReplaceIfExists;
    HANDLE  RootDirectory;
    ULONG   FileNameLength;
    WCHAR   FileName[1];
} FILE_LINK_INFORMATION, *PFILE_LINK_INFORMATION;

typedef struct _FILE_LOCK_ANCHOR {
    LIST_ENTRY GrantedFileLockList;
    LIST_ENTRY PendingFileLockList;
} FILE_LOCK_ANCHOR, *PFILE_LOCK_ANCHOR;

typedef struct _FILE_MAILSLOT_PEEK_BUFFER {
    ULONG ReadDataAvailable;
    ULONG NumberOfMessages;
    ULONG MessageLength;
} FILE_MAILSLOT_PEEK_BUFFER, *PFILE_MAILSLOT_PEEK_BUFFER;

typedef struct _FILE_MAILSLOT_QUERY_INFORMATION {
    ULONG           MaximumMessageSize;
    ULONG           MailslotQuota;
    ULONG           NextMessageSize;
    ULONG           MessagesAvailable;
    LARGE_INTEGER   ReadTimeout;
} FILE_MAILSLOT_QUERY_INFORMATION, *PFILE_MAILSLOT_QUERY_INFORMATION;

typedef struct _FILE_MAILSLOT_SET_INFORMATION {
    PLARGE_INTEGER ReadTimeout;
} FILE_MAILSLOT_SET_INFORMATION, *PFILE_MAILSLOT_SET_INFORMATION;

typedef struct _FILE_MODE_INFORMATION {
    ULONG Mode;
} FILE_MODE_INFORMATION, *PFILE_MODE_INFORMATION;

// This structure is included in the Windows 2000 DDK but is missing in the
// Windows NT 4.0 DDK
#if (_WIN32_WINNT < 0x0500)
typedef struct _FILE_NAME_INFORMATION {
    ULONG FileNameLength;
    WCHAR FileName[1];
} FILE_NAME_INFORMATION, *PFILE_NAME_INFORMATION;
#endif // (_WIN32_WINNT < 0x0500)

typedef struct _FILE_ALL_INFORMATION {
    FILE_BASIC_INFORMATION      BasicInformation;
    FILE_STANDARD_INFORMATION   StandardInformation;
    FILE_INTERNAL_INFORMATION   InternalInformation;
    FILE_EA_INFORMATION         EaInformation;
    FILE_ACCESS_INFORMATION     AccessInformation;
    FILE_POSITION_INFORMATION   PositionInformation;
    FILE_MODE_INFORMATION       ModeInformation;
    FILE_ALIGNMENT_INFORMATION  AlignmentInformation;
    FILE_NAME_INFORMATION       NameInformation;
} FILE_ALL_INFORMATION, *PFILE_ALL_INFORMATION;

typedef struct _FILE_NAMES_INFORMATION {
    ULONG NextEntryOffset;
    ULONG FileIndex;
    ULONG FileNameLength;
    WCHAR FileName[1];
} FILE_NAMES_INFORMATION, *PFILE_NAMES_INFORMATION;

typedef struct _FILE_NOTIFY_INFORMATION {
    ULONG NextEntryOffset;
    ULONG Action;
    ULONG FileNameLength;
    WCHAR FileName[1];
} FILE_NOTIFY_INFORMATION, *PFILE_NOTIFY_INFORMATION;

typedef struct _FILE_OBJECTID_INFORMATION {
    OBJECTID ObjectId;
} FILE_OBJECTID_INFORMATION, *PFILE_OBJECTID_INFORMATION;

typedef struct _FILE_OLE_CLASSID_INFORMATION {
    GUID ClassId;
} FILE_OLE_CLASSID_INFORMATION, *PFILE_OLE_CLASSID_INFORMATION;

typedef struct _FILE_OLE_ALL_INFORMATION {
    FILE_BASIC_INFORMATION          BasicInformation;
    FILE_STANDARD_INFORMATION       StandardInformation;
    FILE_INTERNAL_INFORMATION       InternalInformation;
    FILE_EA_INFORMATION             EaInformation;
    FILE_ACCESS_INFORMATION         AccessInformation;
    FILE_POSITION_INFORMATION       PositionInformation;
    FILE_MODE_INFORMATION           ModeInformation;
    FILE_ALIGNMENT_INFORMATION      AlignmentInformation;
    USN                             LastChangeUsn;
    USN                             ReplicationUsn;
    LARGE_INTEGER                   SecurityChangeTime;
    FILE_OLE_CLASSID_INFORMATION    OleClassIdInformation;
    FILE_OBJECTID_INFORMATION       ObjectIdInformation;
    FILE_STORAGE_TYPE               StorageType;
    ULONG                           OleStateBits;
    ULONG                           OleId;
    ULONG                           NumberOfStreamReferences;
    ULONG                           StreamIndex;
    ULONG                           SecurityId;
    BOOLEAN                         ContentIndexDisable;
    BOOLEAN                         InheritContentIndexDisable;
    FILE_NAME_INFORMATION           NameInformation;
} FILE_OLE_ALL_INFORMATION, *PFILE_OLE_ALL_INFORMATION;

typedef struct _FILE_OLE_DIR_INFORMATION {
    ULONG               NextEntryOffset;
    ULONG               FileIndex;
    LARGE_INTEGER       CreationTime;
    LARGE_INTEGER       LastAccessTime;
    LARGE_INTEGER       LastWriteTime;
    LARGE_INTEGER       ChangeTime;
    LARGE_INTEGER       EndOfFile;
    LARGE_INTEGER       AllocationSize;
    ULONG               FileAttributes;
    ULONG               FileNameLength;
    FILE_STORAGE_TYPE   StorageType;
    GUID                OleClassId;
    ULONG               OleStateBits;
    BOOLEAN             ContentIndexDisable;
    BOOLEAN             InheritContentIndexDisable;
    WCHAR               FileName[1];
} FILE_OLE_DIR_INFORMATION, *PFILE_OLE_DIR_INFORMATION;

typedef struct _FILE_OLE_INFORMATION {
    LARGE_INTEGER                   SecurityChangeTime;
    FILE_OLE_CLASSID_INFORMATION    OleClassIdInformation;
    FILE_OBJECTID_INFORMATION       ObjectIdInformation;
    FILE_STORAGE_TYPE               StorageType;
    ULONG                           OleStateBits;
    BOOLEAN                         ContentIndexDisable;
    BOOLEAN                         InheritContentIndexDisable;
} FILE_OLE_INFORMATION, *PFILE_OLE_INFORMATION;

typedef struct _FILE_OLE_STATE_BITS_INFORMATION {
    ULONG StateBits;
    ULONG StateBitsMask;
} FILE_OLE_STATE_BITS_INFORMATION, *PFILE_OLE_STATE_BITS_INFORMATION;

typedef struct _FILE_PIPE_ASSIGN_EVENT_BUFFER {
    HANDLE  EventHandle;
    ULONG   KeyValue;
} FILE_PIPE_ASSIGN_EVENT_BUFFER, *PFILE_PIPE_ASSIGN_EVENT_BUFFER;

typedef struct _FILE_PIPE_CLIENT_PROCESS_BUFFER {
    PVOID ClientSession;
    PVOID ClientProcess;
} FILE_PIPE_CLIENT_PROCESS_BUFFER, *PFILE_PIPE_CLIENT_PROCESS_BUFFER;

typedef struct _FILE_PIPE_EVENT_BUFFER {
    ULONG NamedPipeState;
    ULONG EntryType;
    ULONG ByteCount;
    ULONG KeyValue;
    ULONG NumberRequests;
} FILE_PIPE_EVENT_BUFFER, *PFILE_PIPE_EVENT_BUFFER;

typedef struct _FILE_PIPE_INFORMATION {
    ULONG ReadMode;
    ULONG CompletionMode;
} FILE_PIPE_INFORMATION, *PFILE_PIPE_INFORMATION;

typedef struct _FILE_PIPE_LOCAL_INFORMATION {
    ULONG NamedPipeType;
    ULONG NamedPipeConfiguration;
    ULONG MaximumInstances;
    ULONG CurrentInstances;
    ULONG InboundQuota;
    ULONG ReadDataAvailable;
    ULONG OutboundQuota;
    ULONG WriteQuotaAvailable;
    ULONG NamedPipeState;
    ULONG NamedPipeEnd;
} FILE_PIPE_LOCAL_INFORMATION, *PFILE_PIPE_LOCAL_INFORMATION;

typedef struct _FILE_PIPE_PEEK_BUFFER {
    ULONG   NamedPipeState;
    ULONG   ReadDataAvailable;
    ULONG   NumberOfMessages;
    ULONG   MessageLength;
    CHAR    Data[1];
} FILE_PIPE_PEEK_BUFFER, *PFILE_PIPE_PEEK_BUFFER;

typedef struct _FILE_PIPE_REMOTE_INFORMATION {
    LARGE_INTEGER   CollectDataTime;
    ULONG           MaximumCollectionCount;
} FILE_PIPE_REMOTE_INFORMATION, *PFILE_PIPE_REMOTE_INFORMATION;

typedef struct _FILE_PIPE_WAIT_FOR_BUFFER {
    LARGE_INTEGER   Timeout;
    ULONG           NameLength;
    BOOLEAN         TimeoutSpecified;
    WCHAR           Name[1];
} FILE_PIPE_WAIT_FOR_BUFFER, *PFILE_PIPE_WAIT_FOR_BUFFER;

typedef struct _FILE_QUOTA_INFORMATION {
    ULONG           NextEntryOffset;
    ULONG           SidLength;
    LARGE_INTEGER   ChangeTime;
    LARGE_INTEGER   QuotaUsed;
    LARGE_INTEGER   QuotaThreshold;
    LARGE_INTEGER   QuotaLimit;
    SID             Sid;
} FILE_QUOTA_INFORMATION, *PFILE_QUOTA_INFORMATION;

typedef struct _FILE_RENAME_INFORMATION {
    BOOLEAN ReplaceIfExists;
    HANDLE  RootDirectory;
    ULONG   FileNameLength;
    WCHAR   FileName[1];
} FILE_RENAME_INFORMATION, *PFILE_RENAME_INFORMATION;

typedef struct _FILE_STREAM_INFORMATION {
    ULONG           NextEntryOffset;
    ULONG           StreamNameLength;
    LARGE_INTEGER   StreamSize;
    LARGE_INTEGER   StreamAllocationSize;
    WCHAR           StreamName[1];
} FILE_STREAM_INFORMATION, *PFILE_STREAM_INFORMATION;

typedef struct _FSRTL_COMMON_FCB_HEADER {
    CSHORT          NodeTypeCode;
    CSHORT          NodeByteSize;
    UCHAR           Flags;
    UCHAR           IsFastIoPossible;
#if (_WIN32_WINNT >= 0x0400)
    UCHAR           Flags2;
    UCHAR           Reserved;
#endif // (_WIN32_WINNT >= 0x0400)
    PERESOURCE      Resource;
    PERESOURCE      PagingIoResource;
    LARGE_INTEGER   AllocationSize;
    LARGE_INTEGER   FileSize;
    LARGE_INTEGER   ValidDataLength;
} FSRTL_COMMON_FCB_HEADER, *PFSRTL_COMMON_FCB_HEADER;

typedef struct _GENERATE_NAME_CONTEXT {
    USHORT  Checksum;
    BOOLEAN CheckSumInserted;
    UCHAR   NameLength;
    WCHAR   NameBuffer[8];
    ULONG   ExtensionLength;
    WCHAR   ExtensionBuffer[4];
    ULONG   LastIndexValue;
} GENERATE_NAME_CONTEXT, *PGENERATE_NAME_CONTEXT;

typedef struct _MAPPING_PAIR {
    ULONGLONG Vcn;
    ULONGLONG Lcn;
} MAPPING_PAIR, *PMAPPING_PAIR;

typedef struct _GET_RETRIEVAL_DESCRIPTOR {
    ULONG           NumberOfPairs;
    ULONGLONG       StartVcn;
    MAPPING_PAIR    Pair[1];
} GET_RETRIEVAL_DESCRIPTOR, *PGET_RETRIEVAL_DESCRIPTOR;


typedef struct _IO_COMPLETION_BASIC_INFORMATION {
    LONG Depth;
} IO_COMPLETION_BASIC_INFORMATION, *PIO_COMPLETION_BASIC_INFORMATION;

typedef struct _KEVENT_PAIR {
    USHORT Type;
    USHORT Size;
    KEVENT Event1;
    KEVENT Event2;
} KEVENT_PAIR, *PKEVENT_PAIR;

typedef struct _KQUEUE {
    DISPATCHER_HEADER   Header;
    LIST_ENTRY          EntryListHead;
    ULONG               CurrentCount;
    ULONG               MaximumCount;
    LIST_ENTRY          ThreadListHead;
} KQUEUE, *PKQUEUE;

typedef struct _LPC_MESSAGE {
    USHORT      DataLength;
    USHORT      Length;
    USHORT      MessageType;
    USHORT      DataInfoOffset;
    CLIENT_ID   ClientId;
    ULONG       MessageId;
    ULONG       CallbackId;
} LPC_MESSAGE, *PLPC_MESSAGE;

typedef struct _LPC_OTHER_SIDE_MEMORY {
    ULONG Length;
    ULONG ViewSize;
    PVOID ViewBase;
} LPC_OTHER_SIDE_MEMORY, *PLPC_OTHER_SIDE_MEMORY;

typedef struct _LPC_THIS_SIDE_MEMORY {
    ULONG   Length;
    HANDLE  SectionHandle;
    ULONG   OffsetInSection;
    ULONG   ViewSize;
    PVOID   ViewBase;
    PVOID   OtherSideViewBase;
} LPC_THIS_SIDE_MEMORY, *PLPC_THIS_SIDE_MEMORY;

typedef struct _MOVEFILE_DESCRIPTOR {
     HANDLE         FileHandle; 
     ULONG          Reserved;   
     LARGE_INTEGER  StartVcn; 
     LARGE_INTEGER  TargetLcn;
     ULONG          NumVcns; 
     ULONG          Reserved1;  
} MOVEFILE_DESCRIPTOR, *PMOVEFILE_DESCRIPTOR;

typedef struct _OBJECT_BASIC_INFO {
    UCHAR Unknown1[8];
    ULONG HandleCount;
    ULONG ReferenceCount;
    ULONG PagedQuota;
    ULONG NonPagedQuota;
    UCHAR Unknown2[32];
} OBJECT_BASIC_INFO, *POBJECT_BASIC_INFO;

typedef struct _OBJECT_NAME_INFO {
    UNICODE_STRING  ObjectName;
    WCHAR           ObjectNameBuffer[1];
} OBJECT_NAME_INFO, *POBJECT_NAME_INFO;

typedef struct _OBJECT_PROTECTION_INFO {
    BOOLEAN Inherit;
    BOOLEAN ProtectHandle;
} OBJECT_PROTECTION_INFO, *POBJECT_PROTECTION_INFO;

typedef struct _OBJECT_TYPE {
    ERESOURCE               Mutex;
    LIST_ENTRY              TypeList;
    UNICODE_STRING          Name;
    LONG                    DefaultObject;
    ULONG                   Index;
    ULONG                   TotalNumberOfObjects;
    ULONG                   TotalNumberOfHandles;
    ULONG                   HighWaterNumberOfObjects;
    ULONG                   HighWaterNumberOfHandles;
    //OBJECT_TYPE_INITIALIZER TypeInfo;
    ULONG                   Key;
} OBJECT_TYPE, *POBJECT_TYPE;

typedef struct _OBJECT_TYPE_INFO {
    UNICODE_STRING  ObjectTypeName;
    UCHAR           Unknown[0x58];
    WCHAR           ObjectTypeNameBuffer[1];
} OBJECT_TYPE_INFO, *POBJECT_TYPE_INFO;

typedef struct _OBJECT_ALL_TYPES_INFO {
    ULONG               NumberOfObjectTypes;
    OBJECT_TYPE_INFO    ObjectsTypeInfo[1];
} OBJECT_ALL_TYPES_INFO, *POBJECT_ALL_TYPES_INFO;

typedef struct _PATHNAME_BUFFER {
    ULONG PathNameLength;
    WCHAR Name[1];
} PATHNAME_BUFFER, *PPATHNAME_BUFFER;

typedef struct _PUBLIC_BCB {
    CSHORT          NodeTypeCode;
    CSHORT          NodeByteSize;
    ULONG           MappedLength;
    LARGE_INTEGER   MappedFileOffset;
} PUBLIC_BCB, *PPUBLIC_BCB;

typedef struct _QUERY_PATH_REQUEST {
    ULONG                   PathNameLength;
    PIO_SECURITY_CONTEXT    SecurityContext;
    WCHAR                   FilePathName[1];
} QUERY_PATH_REQUEST, *PQUERY_PATH_REQUEST;

typedef struct _QUERY_PATH_RESPONSE {
    ULONG LengthAccepted;
} QUERY_PATH_RESPONSE, *PQUERY_PATH_RESPONSE;

typedef struct _RETRIEVAL_POINTERS_BUFFER {
    ULONG               ExtentCount;
    LARGE_INTEGER       StartingVcn;
    struct {
        LARGE_INTEGER   NextVcn;
        LARGE_INTEGER   Lcn;
    } Extents[1];
} RETRIEVAL_POINTERS_BUFFER, *PRETRIEVAL_POINTERS_BUFFER;

typedef struct _SERVICE_DESCRIPTOR_TABLE {
    PVOID   ServiceTable;
    PULONG  CounterTable;
    ULONG   TableSize;
    PUCHAR  ArgumentTable;
} SERVICE_DESCRIPTOR_TABLE, *PSERVICE_DESCRIPTOR_TABLE;

typedef struct _SID_AND_ATTRIBUTES {
    PSID    Sid;
    ULONG   Attributes;
} SID_AND_ATTRIBUTES, *PSID_AND_ATTRIBUTES;

typedef struct _STARTING_VCN_INPUT_BUFFER {
    LARGE_INTEGER StartingVcn;
} STARTING_VCN_INPUT_BUFFER, *PSTARTING_VCN_INPUT_BUFFER;

typedef struct _TOKEN_SOURCE {
    CCHAR   SourceName[TOKEN_SOURCE_LENGTH];
    LUID    SourceIdentifier;
} TOKEN_SOURCE, *PTOKEN_SOURCE;

typedef struct _TOKEN_CONTROL {
    LUID            TokenId;
    LUID            AuthenticationId;
    LUID            ModifiedId;
    TOKEN_SOURCE    TokenSource;
} TOKEN_CONTROL, *PTOKEN_CONTROL;

typedef struct _TOKEN_DEFAULT_DACL {
    PACL DefaultDacl;
} TOKEN_DEFAULT_DACL, *PTOKEN_DEFAULT_DACL;


typedef struct _TOKEN_OWNER {
    PSID Owner;
} TOKEN_OWNER, *PTOKEN_OWNER;

typedef struct _TOKEN_PRIMARY_GROUP {
    PSID PrimaryGroup;
} TOKEN_PRIMARY_GROUP, *PTOKEN_PRIMARY_GROUP;


typedef struct _TOKEN_STATISTICS {
    LUID                            TokenId;
    LUID                            AuthenticationId;
    LARGE_INTEGER                   ExpirationTime;
    TOKEN_TYPE                      TokenType;
    SECURITY_IMPERSONATION_LEVEL    ImpersonationLevel;
    ULONG                           DynamicCharged;
    ULONG                           DynamicAvailable;
    ULONG                           GroupCount;
    ULONG                           PrivilegeCount;
    LUID                            ModifiedId;
} TOKEN_STATISTICS, *PTOKEN_STATISTICS;

typedef struct _TOKEN_USER {
    SID_AND_ATTRIBUTES User;
} TOKEN_USER, *PTOKEN_USER;

NTKERNELAPI
BOOLEAN
CcCanIWrite (
    IN PFILE_OBJECT FileObject,
    IN ULONG        BytesToWrite,
    IN BOOLEAN      Wait,
    IN BOOLEAN      Retrying
);

NTKERNELAPI
BOOLEAN
CcCopyRead (
    IN PFILE_OBJECT         FileObject,
    IN PLARGE_INTEGER       FileOffset,
    IN ULONG                Length,
    IN BOOLEAN              Wait,
    OUT PVOID               Buffer,
    OUT PIO_STATUS_BLOCK    IoStatus
);

NTKERNELAPI
BOOLEAN
CcCopyWrite (
    IN PFILE_OBJECT     FileObject,
    IN PLARGE_INTEGER   FileOffset,
    IN ULONG            Length,
    IN BOOLEAN          Wait,
    IN PVOID            Buffer
);

typedef VOID (*PCC_POST_DEFERRED_WRITE) (
    IN PVOID Context1,
    IN PVOID Context2
);

NTKERNELAPI
VOID
CcDeferWrite (
    IN PFILE_OBJECT             FileObject,
    IN PCC_POST_DEFERRED_WRITE  PostRoutine,
    IN PVOID                    Context1,
    IN PVOID                    Context2,
    IN ULONG                    BytesToWrite,
    IN BOOLEAN                  Retrying
);

NTKERNELAPI
VOID
CcFastCopyRead (
    IN PFILE_OBJECT         FileObject,
    IN ULONG                FileOffset,
    IN ULONG                Length,
    IN ULONG                PageCount,
    OUT PVOID               Buffer,
    OUT PIO_STATUS_BLOCK    IoStatus
);

NTKERNELAPI
VOID
CcFastCopyWrite (
    IN PFILE_OBJECT FileObject,
    IN ULONG        FileOffset,
    IN ULONG        Length,
    IN PVOID        Buffer
);

NTKERNELAPI
VOID
CcFlushCache (
    IN PSECTION_OBJECT_POINTERS SectionObjectPointer,
    IN PLARGE_INTEGER           FileOffset OPTIONAL,
    IN ULONG                    Length,
    OUT PIO_STATUS_BLOCK        IoStatus OPTIONAL
);

typedef VOID (*PDIRTY_PAGE_ROUTINE) (
    IN PFILE_OBJECT     FileObject,
    IN PLARGE_INTEGER   FileOffset,
    IN ULONG            Length,
    IN PLARGE_INTEGER   OldestLsn,
    IN PLARGE_INTEGER   NewestLsn,
    IN PVOID            Context1,
    IN PVOID            Context2
);

NTKERNELAPI
LARGE_INTEGER
CcGetDirtyPages (
    IN PVOID                LogHandle,
    IN PDIRTY_PAGE_ROUTINE  DirtyPageRoutine,
    IN PVOID                Context1,
    IN PVOID                Context2
);

NTKERNELAPI
PFILE_OBJECT
CcGetFileObjectFromBcb (
    IN PVOID Bcb
);

NTKERNELAPI
PFILE_OBJECT
CcGetFileObjectFromSectionPtrs (
    IN PSECTION_OBJECT_POINTERS SectionObjectPointer
);

NTKERNELAPI
LARGE_INTEGER
CcGetLsnForFileObject (
    IN PFILE_OBJECT     FileObject,
    OUT PLARGE_INTEGER  OldestLsn OPTIONAL
);

typedef BOOLEAN (*PACQUIRE_FOR_LAZY_WRITE) (
    IN PVOID    Context,
    IN BOOLEAN  Wait
);

typedef VOID (*PRELEASE_FROM_LAZY_WRITE) (
    IN PVOID Context
);

typedef BOOLEAN (*PACQUIRE_FOR_READ_AHEAD) (
    IN PVOID    Context,
    IN BOOLEAN  Wait
);

typedef VOID (*PRELEASE_FROM_READ_AHEAD) (
    IN PVOID Context
);

typedef struct _CACHE_MANAGER_CALLBACKS {
    PACQUIRE_FOR_LAZY_WRITE     AcquireForLazyWrite;
    PRELEASE_FROM_LAZY_WRITE    ReleaseFromLazyWrite;
    PACQUIRE_FOR_READ_AHEAD     AcquireForReadAhead;
    PRELEASE_FROM_READ_AHEAD    ReleaseFromReadAhead;
} CACHE_MANAGER_CALLBACKS, *PCACHE_MANAGER_CALLBACKS;


typedef struct _PEB_LDR_DATA {
    ULONG Length;
    BOOLEAN Initialized;
    HANDLE SsHandle;
    LIST_ENTRY InLoadOrderModuleList;
    LIST_ENTRY InMemoryOrderModuleList;
    LIST_ENTRY InInitializationOrderModuleList;
} PEB_LDR_DATA, *PPEB_LDR_DATA;

#include <pshpack1.h>
typedef struct _LDR_DATA_TABLE_ENTRY
{
    struct _LIST_ENTRY InLoadOrderLinks;
    struct _LIST_ENTRY InMemoryOrderLinks;
    struct _LIST_ENTRY InInitializationOrderLinks;
    void* DllBase;
    void* EntryPoint;
    DWORD SizeOfImage;
    struct _UNICODE_STRING FullDllName;
    struct _UNICODE_STRING BaseDllName;
    DWORD Flags;
    WORD LoadCount;
    WORD TlsIndex;
    struct _LIST_ENTRY HashLinks;
    void* SectionPointer;
    DWORD CheckSum;
    DWORD TimeDateStamp;
    void* LoadedImports;
    void* EntryPointActivationContext;
} LDR_DATA_TABLE_ENTRY;

#include <poppack.h>

typedef struct _PEB_FREE_BLOCK {
    struct _PEB_FREE_BLOCK *Next;
    ULONG Size;
} PEB_FREE_BLOCK, *PPEB_FREE_BLOCK;


struct _CURDIR
{
    struct _UNICODE_STRING DosPath;
    void* Handle;
};

struct _RTL_DRIVE_LETTER_CURDIR
{
    WORD Flags;
    WORD Length;
    DWORD TimeStamp;
    struct _STRING DosPath;
};


struct _RTL_USER_PROCESS_PARAMETERS
{
    DWORD MaximumLength;
    DWORD Length;
    DWORD Flags;
    DWORD DebugFlags;
    void* ConsoleHandle;
    DWORD ConsoleFlags;
    void* StandardInput;
    void* StandardOutput;
    void* StandardError;
    struct _CURDIR CurrentDirectory;
    struct _UNICODE_STRING DllPath;
    struct _UNICODE_STRING ImagePathName;
    struct _UNICODE_STRING CommandLine;
    void* Environment;
    DWORD StartingX;
    DWORD StartingY;
    DWORD CountX;
    DWORD CountY;
    DWORD CountCharsX;
    DWORD CountCharsY;
    DWORD FillAttribute;
    DWORD WindowFlags;
    DWORD ShowWindowFlags;
    struct _UNICODE_STRING WindowTitle;
    struct _UNICODE_STRING DesktopInfo;
    struct _UNICODE_STRING ShellInfo;
    struct _UNICODE_STRING RuntimeData;
    struct _RTL_DRIVE_LETTER_CURDIR CurrentDirectores[32];
};

#include <pshpack1.h>
typedef struct _PEB
{
    BYTE InheritedAddressSpace;
    BYTE ReadImageFileExecOptions;
    BYTE BeingDebugged;
    BYTE SpareBool;
    void* Mutant;
    void* ImageBaseAddress;
    struct _PEB_LDR_DATA* Ldr;
    struct _RTL_USER_PROCESS_PARAMETERS* ProcessParameters;
    void* SubSystemData;
    void* ProcessHeap;
    void* FastPebLock;
    void* FastPebLockRoutine;
    void* FastPebUnlockRoutine;
    DWORD EnvironmentUpdateCount;
    void* KernelCallbackTable;
    DWORD SystemReserved[2];
    struct _PEB_FREE_BLOCK* FreeList;
    DWORD TlsExpansionCounter;
    void* TlsBitmap;
    DWORD TlsBitmapBits[2];
    void* ReadOnlySharedMemoryBase;
    void* ReadOnlySharedMemoryHeap;
    void** ReadOnlyStaticServerData;
    void* AnsiCodePageData;
    void* OemCodePageData;
    void* UnicodeCaseTableData;
    DWORD NumberOfProcessors;
    DWORD NtGlobalFlag;
    LARGE_INTEGER CriticalSectionTimeout;
    DWORD HeapSegmentReserve;
    DWORD HeapSegmentCommit;
    DWORD HeapDeCommitTotalFreeThreshold;
    DWORD HeapDeCommitFreeBlockThreshold;
    DWORD NumberOfHeaps;
    DWORD MaximumNumberOfHeaps;
    void** ProcessHeaps;
    void* GdiSharedHandleTable;
    void* ProcessStarterHelper;
    DWORD GdiDCAttributeList;
    void* LoaderLock;
    DWORD OSMajorVersion;
    DWORD OSMinorVersion;
    WORD OSBuildNumber;
    WORD OSCSDVersion;
    DWORD OSPlatformId;
    DWORD ImageSubsystem;
    DWORD ImageSubsystemMajorVersion;
    DWORD ImageSubsystemMinorVersion;
    DWORD ImageProcessAffinityMask;
    DWORD GdiHandleBuffer[34];
    void* PostProcessInitRoutine;
    void* TlsExpansionBitmap;
    DWORD TlsExpansionBitmapBits[32];
    DWORD SessionId;
    ULARGE_INTEGER AppCompatFlags;
    void* pShimData;
    void* AppCompatInfo;
    UNICODE_STRING CSDVersion;
    void* ActivationContextData;
    void* ProcessAssemblyStorageMap;
    void* SystemDefaultActivationContextData;
    void* SystemAssemblyStorageMap;
    DWORD MinimumStackCommit;
} PEB;

#include <poppack.h>


NTSYSAPI
PVOID
NTAPI
RtlImageDirectoryEntryToData(
    PVOID BaseOfImage,
    BOOLEAN MappedAsImage,
    USHORT DirectoryEntry,
    PULONG Size
    );


//  GDT selectors - These defines are R0 selector numbers, which means
//                  they happen to match the byte offset relative to
//                  the base of the GDT.
//

#define KGDT_NULL       0
#define KGDT_R0_CODE    8
#define KGDT_R0_DATA    16
#define KGDT_R3_CODE    24
#define KGDT_R3_DATA    32
#define KGDT_TSS        40
#define KGDT_R0_PCR     48
#define KGDT_R3_TEB     56
#define KGDT_VDM_TILE   64
#define KGDT_LDT        72
#define KGDT_DF_TSS     80
#define KGDT_NMI_TSS    88

//
// Exception Registration structure
//

typedef struct _EXCEPTION_REGISTRATION_RECORD {
    struct _EXCEPTION_REGISTRATION_RECORD *Next;
    PEXCEPTION_ROUTINE Handler;
} EXCEPTION_REGISTRATION_RECORD;

typedef EXCEPTION_REGISTRATION_RECORD *PEXCEPTION_REGISTRATION_RECORD;


//typedef LARGE_INTEGER   QWORD;

// =================================================================
// SYSTEM INFO CLASSES
// =================================================================

typedef enum _SYSTEMINFOCLASS
    {
    SystemBasicInformation,             // 0x002C
    SystemProcessorInformation,         // 0x000C
    SystemPerformanceInformation,       // 0x0138
    SystemTimeInformation,              // 0x0020
    SystemPathInformation,              // not implemented
    SystemProcessInformation,           // 0x00C8+ per process
    SystemCallInformation,              // 0x0018 + (n * 0x0004)
    SystemConfigurationInformation,     // 0x0018
    SystemProcessorCounters,            // 0x0030 per cpu
    SystemGlobalFlag,                   // 0x0004
    SystemInfo10,                       // not implemented
    SystemModuleInformation,            // 0x0004 + (n * 0x011C)
    SystemLockInformation,              // 0x0004 + (n * 0x0024)
    SystemInfo13,                       // not implemented
    SystemPagedPoolInformation,         // checked build only
    SystemNonPagedPoolInformation,      // checked build only
    SystemHandleInformation,            // 0x0004  + (n * 0x0010)
    SystemObjectInformation,            // 0x0038+ + (n * 0x0030+)
    SystemPageFileInformation,          // 0x0018+ per page file
    SystemInstemulInformation,          // 0x0088
    SystemInfo20,                       // invalid info class
    SystemCacheInformation,             // 0x0024
    SystemPoolTagInformation,           // 0x0004 + (n * 0x001C)
    SystemInfo23,                       // 0x0000, or 0x0018 per cpu
    SystemDpcInformation,               // 0x0014
    SystemInfo25,                       // checked build only
    SystemLoadDriver,                   // 0x0018, set mode only
    SystemUnloadDriver,                 // 0x0004, set mode only
    SystemTimeAdjustmentInformation,    // 0x000C, 0x0008 writeable
    SystemInfo29,                       // checked build only
    SystemInfo30,                       // checked build only
    SystemInfo31,                       // checked build only
    SystemCrashDumpInformation,         // 0x0004
    SystemInfo33,                       // 0x0010
    SystemCrashDumpStateInformation,    // 0x0004
    SystemDebuggerInformation,          // 0x0002
    SystemThreadSwitchInformation,      // 0x0030
    SystemRegistryQuotaInformation,     // 0x000C
    SystemAddDriver,                    // 0x0008, set mode only
    SystemPrioritySeparationInformation,// 0x0004, set mode only
    SystemInfo40,                       // not implemented
    SystemInfo41,                       // not implemented
    SystemInfo42,                       // invalid info class
    SystemInfo43,                       // invalid info class
    SystemTimeZoneInformation,          // 0x00AC
    SystemLookasideInformation,         // n * 0x0020
    MaxSystemInfoClass
    }
    SYSTEMINFOCLASS, *PSYSTEMINFOCLASS, **PPSYSTEMINFOCLASS;

// =================================================================
// SYSTEM INFO STRUCTURES
// =================================================================
// 00: SystemBasicInformation

typedef struct _SYSTEM_BASIC_INFORMATION
    {
    DWORD d00;                      // 0
    DWORD dKeMaximumIncrement;      // x86: 0x0002625A or 0x00018730
    DWORD dPageSize;                // bytes
    DWORD dMmNumberOfPhysicalPages;
    DWORD dMmLowestPhysicalPage;
    DWORD dMmHighestPhysicalPage;
    DWORD dAllocationGranularity;   // bytes
    PVOID pLowestUserAddress;
    PVOID pMmHighestUserAddress;
    DWORD dKeActiveProcessors;
    BYTE  bKeNumberProcessors;
    BYTE  bReserved01;
    WORD  wReserved02;
    }
        SYSTEM_BASIC_INFORMATION,
     * PSYSTEM_BASIC_INFORMATION,
    **PPSYSTEM_BASIC_INFORMATION;

#define SYSTEM_BASIC_INFORMATION_ \
        sizeof (SYSTEM_BASIC_INFORMATION)

// -----------------------------------------------------------------
// 01: SystemProcessorInformation

typedef struct _SYSTEM_PROCESSOR_INFORMATION
    {
    WORD  wKeProcessorArchitecture; // 0=x86, 1=MIPS, 2=ALPHA, 3=PPC
    WORD  wKeProcessorLevel;        // x86: family (5=Pentium)
    WORD  wKeProcessorRevision;     // Pentium: H=model, L=stepping
    WORD  w06;                      // 0
    DWORD dKeFeatureBits;
    }
        SYSTEM_PROCESSOR_INFORMATION,
     * PSYSTEM_PROCESSOR_INFORMATION,
    **PPSYSTEM_PROCESSOR_INFORMATION;

#define SYSTEM_PROCESSOR_INFORMATION_ \
        sizeof (SYSTEM_PROCESSOR_INFORMATION)

// -----------------------------------------------------------------
// 02: SystemPerformanceInformation

typedef struct _MM_INFO_COUNTERS
    {
    DWORD dPageFaults;
    DWORD d04;
    DWORD d08;
    DWORD d0C;
    DWORD d10;
    DWORD d14;
    DWORD d18;
    DWORD d1C;
    DWORD d20;
    DWORD d24;
    DWORD d28;
    DWORD d2C;
    DWORD d30;
    }
        MM_INFO_COUNTERS,
     * PMM_INFO_COUNTERS,
    **PPMM_INFO_COUNTERS;

#define MM_INFO_COUNTERS_ \
        sizeof (MM_INFO_COUNTERS)

// -----------------------------------------------------------------
// 03: SystemTimeInformation

typedef struct _SYSTEM_TIME_INFORMATION
    {
    QWORD qKeBootTime;          // relative to 01-01-1601
    QWORD qKeSystemTime;        // relative to 01-01-1601
    QWORD dExpTimeZoneBias;     // utc time = local time + bias
    DWORD dExpCurrentTimeZoneId;
    DWORD dReserved01;
    }
        SYSTEM_TIME_INFORMATION,
     * PSYSTEM_TIME_INFORMATION,
    **PPSYSTEM_TIME_INFORMATION;

#define SYSTEM_TIME_INFORMATION_ \
        sizeof (SYSTEM_TIME_INFORMATION)

// -----------------------------------------------------------------
// 04: SystemPathInformation (not implemented)

// -----------------------------------------------------------------
// 05: SystemProcessInformation
//     see ExpGetProcessInformation()
//     see also ExpCopyProcessInfo(), ExpCopyThreadInfo()

typedef struct _SYSTEM_THREAD
    {
    QWORD        qKernelTime;       // 100 nsec units
    QWORD        qUserTime;         // 100 nsec units
    QWORD        qCreateTime;       // relative to 01-01-1601
    DWORD        d18;
    PVOID        pStartAddress;
    CLIENT_ID    Cid;               // process/thread ids
    DWORD        dPriority;
    DWORD        dBasePriority;
    DWORD        dContextSwitches;
    DWORD        dThreadState;      // 2=running, 5=waiting
    KWAIT_REASON WaitReason;
    DWORD        dReserved01;
    }
        SYSTEM_THREAD,
     * PSYSTEM_THREAD,
    **PPSYSTEM_THREAD;

#define SYSTEM_THREAD_ \
        sizeof (SYSTEM_THREAD)

typedef struct _SYSTEM_THREAD_INFORMATION {
    LARGE_INTEGER KernelTime;
    LARGE_INTEGER UserTime;
    LARGE_INTEGER CreateTime;
    ULONG WaitTime;
    PVOID StartAddress;
    CLIENT_ID ClientId;
    KPRIORITY Priority;
    LONG BasePriority;
    ULONG ContextSwitches;
    ULONG ThreadState;
    ULONG WaitReason;
} SYSTEM_THREAD_INFORMATION, *PSYSTEM_THREAD_INFORMATION;

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

typedef struct __SYSTEM_PROCESS_INFORMATION
    {
    DWORD          dNext;           // relative offset
    DWORD          dThreadCount;
    DWORD          dReserved01;
    DWORD          dReserved02;
    DWORD          dReserved03;
    DWORD          dReserved04;
    DWORD          dReserved05;
    DWORD          dReserved06;
    QWORD          qCreateTime;     // relative to 01-01-1601
    QWORD          qUserTime;       // 100 nsec units
    QWORD          qKernelTime;     // 100 nsec units
    UNICODE_STRING usName;
    KPRIORITY      BasePriority;
    DWORD          dUniqueProcessId;
    DWORD          dInheritedFromUniqueProcessId;
    DWORD          dHandleCount;
    DWORD          dReserved07;
    DWORD          dReserved08;
    VM_COUNTERS    VmCounters;
    DWORD          dCommitCharge;   // bytes
    SYSTEM_THREAD  ast [1];
    }
        _SYSTEM_PROCESS_INFORMATION1,
     * _PSYSTEM_PROCESS_INFORMATION1,
    **_PPSYSTEM_PROCESS_INFORMATION1;

#define SYSTEM_PROCESS_INFORMATION_ \
        sizeof (SYSTEM_PROCESS_INFORMATION)

typedef struct _SYSTEM_PROCESS_INFORMATION {
    ULONG NextEntryOffset;
    ULONG NumberOfThreads;
    LARGE_INTEGER SpareLi1;
    LARGE_INTEGER SpareLi2;
    LARGE_INTEGER SpareLi3;
    LARGE_INTEGER CreateTime;
    LARGE_INTEGER UserTime;
    LARGE_INTEGER KernelTime;
    UNICODE_STRING ImageName;
    KPRIORITY BasePriority;
    HANDLE UniqueProcessId;
    HANDLE InheritedFromUniqueProcessId;
    ULONG HandleCount;
    ULONG SessionId;
    ULONG SpareUl3;
    SIZE_T PeakVirtualSize;
    SIZE_T VirtualSize;
    ULONG PageFaultCount;
    ULONG PeakWorkingSetSize;
    ULONG WorkingSetSize;
    SIZE_T QuotaPeakPagedPoolUsage;
    SIZE_T QuotaPagedPoolUsage;
    SIZE_T QuotaPeakNonPagedPoolUsage;
    SIZE_T QuotaNonPagedPoolUsage;
    SIZE_T PagefileUsage;
    SIZE_T PeakPagefileUsage;
    SIZE_T PrivatePageCount;
    SYSTEM_THREAD_INFORMATION ThreadInfo[1];
} SYSTEM_PROCESS_INFORMATION, *PSYSTEM_PROCESS_INFORMATION;


// -----------------------------------------------------------------
// 06: SystemCallInformation
//     see KeServiceDescriptorTable, KeServiceDescriptorTableShadow

typedef struct _SYSTEM_CALL_INFORMATION
    {
    DWORD dSize;                // bytes, including all entries
    DWORD dTables;              // 2 or 4, 0=ntoskrnl, 1=win32k
    DWORD adData [1];            // table sizes, table data
    }
        SYSTEM_CALL_INFORMATION,
     * PSYSTEM_CALL_INFORMATION,
    **PPSYSTEM_CALL_INFORMATION;

#define SYSTEM_CALL_INFORMATION_ \
        sizeof (SYSTEM_CALL_INFORMATION)

#define SYSTEM_CALL_INFORMATION_VALUES($psci) \
        (($psci)->adData + ($psci)->dTables)

// -----------------------------------------------------------------
// 07: SystemConfigurationInformation
//     see IoGetConfigurationInformation ()

typedef struct _SYSTEM_CONFIGURATION_INFORMATION
    {
    DWORD dDiskCount;
    DWORD dFloppyCount;
    DWORD dCDRomCount;
    DWORD dTapeCount;
    DWORD dSerialCount;         // com port with mouse not included
    DWORD dParallelCount;
    }
        SYSTEM_CONFIGURATION_INFORMATION,
     * PSYSTEM_CONFIGURATION_INFORMATION,
    **PPSYSTEM_CONFIGURATION_INFORMATION;

#define SYSTEM_CONFIGURATION_INFORMATION_ \
        sizeof (SYSTEM_CONFIGURATION_INFORMATION)

// -----------------------------------------------------------------
// 08: SystemProcessorCounters
//     see KiProcessorBlock

typedef struct _SYSTEM_PROCESSOR_COUNTERS
    {
    QWORD qProcessorTime;       // 100 nsec units
    QWORD qTotalTime;           // 100 nsec units
    QWORD qUserTime;            // 100 nsec units
    QWORD qDpcTime;             // 100 nsec units
    QWORD qInterruptTime;       // 100 nsec units
    DWORD dInterruptCount;
    DWORD dReserved01;
    }
        SYSTEM_PROCESSOR_COUNTERS,
     * PSYSTEM_PROCESSOR_COUNTERS,
    **PPSYSTEM_PROCESSOR_COUNTERS;

#define SYSTEM_PROCESSOR_COUNTERS_ \
        sizeof (SYSTEM_PROCESSOR_COUNTERS)

// -----------------------------------------------------------------
// 09: SystemGlobalFlag
//     see NtGlobalFlag

typedef struct _SYSTEM_GLOBAL_FLAG
    {
    DWORD dNtGlobalFlag;        // see Q147314, Q102985, Q105677
    }
        SYSTEM_GLOBAL_FLAG,
     * PSYSTEM_GLOBAL_FLAG,
    **PPSYSTEM_GLOBAL_FLAG;

#define SYSTEM_GLOBAL_FLAG_ \
        sizeof (SYSTEM_GLOBAL_FLAG)

// -----------------------------------------------------------------
// 10: SystemInfo10 (not implemented)

// -----------------------------------------------------------------
// 11: SystemModuleInformation
//     see ExpQueryModuleInformation

typedef struct _SYSTEM_MODULE
    {
    DWORD dReserved01;
    DWORD d04;
    PVOID pAddress;
    DWORD dSize;                // bytes
    DWORD dFlags;
    WORD  wId;                  // zero based
    WORD  wRank;                // 0 if not assigned
    WORD  w18;
    WORD  wNameOffset;
    BYTE  abName [MAXIMUM_FILENAME_LENGTH];
    }
        SYSTEM_MODULE,
     * PSYSTEM_MODULE,
    **PPSYSTEM_MODULE;

#define SYSTEM_MODULE_ \
        sizeof (SYSTEM_MODULE)

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

typedef struct _SYSTEM_MODULE_INFORMATION
    {
    DWORD         dCount;
    SYSTEM_MODULE aSM [1];
    }
        SYSTEM_MODULE_INFORMATION,
     * PSYSTEM_MODULE_INFORMATION,
    **PPSYSTEM_MODULE_INFORMATION;

#define SYSTEM_MODULE_INFORMATION_ \
        sizeof (SYSTEM_MODULE_INFORMATION)

NTSTATUS NTAPI
ZwQuerySystemInformation (SYSTEMINFOCLASS sic,
                          PVOID           pData,
                          DWORD           dSize,
                          PDWORD          pdSize);




struct _Wx86ThreadState
{
    DWORD* CallBx86Eip;
    void* DeallocationCpu;
    BYTE UseKnownWx86Dll;
    char OleStubInvoked;
};

typedef struct _ACTIVATION_CONTEXT_STACK
{
    DWORD Flags;
    void* ActiveFrame;
    struct _LIST_ENTRY FrameListCache;
    DWORD NextCookieSequenceNumber;
} ACTIVATION_CONTEXT_STACK;


typedef struct _GDI_TEB_BATCH
{
    DWORD Offset;
    DWORD HDC;
    DWORD Buffer[310];
} GDI_TEB_BATCH;


typedef struct _TEB
{
    NT_TIB NtTib;
    void* EnvironmentPointer;
    CLIENT_ID ClientId;
    void* ActiveRpcHandle;
    void* ThreadLocalStoragePointer;
    PEB* ProcessEnvironmentBlock;
    DWORD LastErrorValue;
    DWORD CountOfOwnedCriticalSections;
    void* CsrClientThread;
    void* Win32ThreadInfo;
    DWORD User32Reserved[26];
    DWORD UserReserved[5];
    void* WOW32Reserved;
    DWORD CurrentLocale;
    DWORD FpSoftwareStatusRegister;
    void* SystemReserved1[54];
    long ExceptionCode;
    BYTE SpareBytes1[44];
    GDI_TEB_BATCH GdiTebBatch;
    CLIENT_ID RealClientId;
    void* GdiCachedProcessHandle;
    DWORD GdiClientPID;
    DWORD GdiClientTID;
    void* GdiThreadLocalInfo;
    DWORD Win32ClientInfo[62];
    void* glDispatchTable[233];
    DWORD glReserved1[29];
    void* glReserved2;
    void* glSectionInfo;
    void* glSection;
    void* glTable;
    void* glCurrentRC;
    void* glContext;
    DWORD LastStatusValue;
    UNICODE_STRING StaticUnicodeString;
    WORD StaticUnicodeBuffer[261];
    void* DeallocationStack;
    void* TlsSlots[64];
    LIST_ENTRY TlsLinks;
    void* Vdm;
    void* ReservedForNtRpc;
    void* DbgSsReserved[2];
    DWORD HardErrorsAreDisabled;
    void* Instrumentation[16];
    void* WinSockData;
    DWORD GdiBatchCount;
    BYTE InDbgPrint;
    BYTE FreeStackOnTermination;
    BYTE HasFiberData;
    BYTE SpareB3;
    DWORD Spare3;
    void* ReservedForPerf;
    void* ReservedForOle;
    DWORD WaitingOnLoaderLock;
    struct _Wx86ThreadState Wx86Thread;
    void** TlsExpansionSlots;
    DWORD ImpersonationLocale;
    DWORD IsImpersonating;
    void* NlsCache;
    void* pShimData;
    ACTIVATION_CONTEXT_STACK ActivationContextStack;
} TEB;

NTKERNELAPI
VOID
KeAttachProcess (
    IN PRKPROCESS Process
    );

NTKERNELAPI
VOID
KeDetachProcess (
    VOID
    );

NTSYSAPI
NTSTATUS
NTAPI
ZwOpenDirectoryObject(
						OUT PHANDLE DirectoryHandle,
						IN ACCESS_MASK DesiredAccess,
						IN POBJECT_ATTRIBUTES ObjectAttributes
						);
NTSTATUS PsLookupProcessByProcessId(HANDLE ProcId, PEPROCESS* ppEP);

#ifdef __cplusplus
}
#endif


#endif __UNDOC_
