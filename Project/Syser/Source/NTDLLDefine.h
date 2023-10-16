#ifndef _NTDLL_DEFINE_H_
#define _NTDLL_DEFINE_H_

#define STATUS_INFO_LENGTH_MISMATCH      ((NTSTATUS)0xC0000004L)

#ifndef CONST
#define CONST               const
#endif

#define InitializeObjectAttributes( p, n, a, r, s ) { \
	(p)->Length = sizeof( OBJECT_ATTRIBUTES );          \
	(p)->RootDirectory = r;                             \
	(p)->Attributes = a;                                \
	(p)->ObjectName = n;                                \
	(p)->SecurityDescriptor = s;                        \
	(p)->SecurityQualityOfService = NULL;               \
} 

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
typedef struct _UNICODE_STRING {
	USHORT Length;
	USHORT MaximumLength;
	PWSTR  Buffer;
} UNICODE_STRING;
typedef UNICODE_STRING *PUNICODE_STRING;
typedef struct _OBJECT_ATTRIBUTES {
	ULONG Length;
	HANDLE RootDirectory;
	PUNICODE_STRING ObjectName;
	ULONG Attributes;
	PVOID SecurityDescriptor;        // Points to type SECURITY_DESCRIPTOR
	PVOID SecurityQualityOfService;  // Points to type SECURITY_QUALITY_OF_SERVICE
} OBJECT_ATTRIBUTES;
typedef OBJECT_ATTRIBUTES *POBJECT_ATTRIBUTES;
typedef CONST OBJECT_ATTRIBUTES *PCOBJECT_ATTRIBUTES;

typedef LONG NTSTATUS;
typedef ULONG ACCESS_MASK;
typedef ACCESS_MASK *PACCESS_MASK;
typedef struct _IO_STATUS_BLOCK {
	union {
		NTSTATUS Status;
		PVOID Pointer;
	};

	ULONG_PTR Information;
} IO_STATUS_BLOCK, *PIO_STATUS_BLOCK;

#define OBJ_INHERIT             0x00000002L
#define OBJ_PERMANENT           0x00000010L
#define OBJ_EXCLUSIVE           0x00000020L
#define OBJ_CASE_INSENSITIVE    0x00000040L
#define OBJ_OPENIF              0x00000080L
#define OBJ_OPENLINK            0x00000100L
#define OBJ_KERNEL_HANDLE       0x00000200L
#define OBJ_FORCE_ACCESS_CHECK  0x00000400L
#define OBJ_VALID_ATTRIBUTES    0x000007F2L

#define OBJ_CASE_INSENSITIVE    0x00000040L
typedef struct _SYSTEM_HANDLE_INFORMATION{
	ULONG ProcessId;
	UCHAR ObjectTypeNumber;
	UCHAR Flags;
	USHORT Handle;
	PVOID Object;
	ACCESS_MASK GrantedAccess;
}SYSTEM_HANDLE_INFORMATION,*PSYSTEM_HANDLE_INFORMATION;

typedef struct _SYSTEM_HANDLE_LIST
{
	DWORD Counter;
	SYSTEM_HANDLE_INFORMATION Handle[1];
}SYSTEM_HANDLE_LIST,*PSYSTEM_HANDLE_LIST;

typedef enum _OBJECT_INFORMATION_CLASS
{
	ObjectBasicInformation,
	ObjectNameInformation,
	ObjectTypeInformation,
	ObjectAllTypesInformation,
	ObjectHandleInformation,
}OBJECT_INFORMATION_CLASS;
typedef struct _OBJECT_NAME_INFORMATION
{
	UNICODE_STRING Name;
}OBJECT_NAME_INFORMATION,*POBJECT_NAME_INFORMATION;

typedef struct _DIRECTORY_BASIC_INFORMATION 
{
	UNICODE_STRING ObjectName;
	UNICODE_STRING ObjectTypeName;
} DIRECTORY_BASIC_INFORMATION, *PDIRECTORY_BASIC_INFORMATION;

typedef NTSYSAPI NTSTATUS (NTAPI *PZWOPENFILE)(
										OUT PHANDLE  FileHandle,
										IN ACCESS_MASK  DesiredAccess,
										IN POBJECT_ATTRIBUTES  ObjectAttributes,
										OUT PIO_STATUS_BLOCK  IoStatusBlock,
										IN ULONG  ShareAccess,
										IN ULONG  OpenOptions
										);
typedef NTSYSAPI NTSTATUS (NTAPI *PZWOPENSECTION)(
										OUT PHANDLE  SectionHandle,
										IN ACCESS_MASK  DesiredAccess,
										IN POBJECT_ATTRIBUTES  ObjectAttributes
										);
typedef NTSYSAPI NTSTATUS (NTAPI *PZWCLOSE)(
										IN HANDLE  Handle
										);
typedef NTSYSAPI NTSTATUS (NTAPI *PZWQUERYSYSTEMINFORMATION)(
										SYSTEMINFOCLASS sic,
										PVOID pData,
										DWORD dSize,
										PDWORD pdSize
										);
typedef NTSYSAPI VOID (NTAPI *PRTLINITUNICODESTRING)(
										PUNICODE_STRING DestinationString,
										PCWSTR SourceString
										);

typedef NTSYSAPI NTSTATUS (NTAPI *PZWQUERYOBJECT)(
										IN HANDLE ObjectHandle,
										IN OBJECT_INFORMATION_CLASS ObjectInformationClass,
										OUT PVOID ObjectInformation,
										IN ULONG ObjectInformationLength,
										OUT PULONG ReturnLength
										);

typedef NTSYSAPI NTSTATUS (NTAPI * PZWCREATEDIRECTORYOBJECT)(
						OUT PHANDLE DirectoryHandle,
						IN ACCESS_MASK DesiredAccess,
						IN POBJECT_ATTRIBUTES ObjectAttributes
						);
typedef NTSYSAPI NTSTATUS (NTAPI * PZWOPENDIRECTORYOBJECT)(
					  OUT PHANDLE DirectoryHandle,
					  IN ACCESS_MASK DesiredAccess,
					  IN POBJECT_ATTRIBUTES ObjectAttributes
					  );

typedef NTSYSAPI NTSTATUS (NTAPI * PZWQUERYDIRECTORYOBJECT)(
					   IN HANDLE DirectoryHandle,
					   OUT PVOID Buffer,
					   IN ULONG BufferLength,
					   IN BOOLEAN ReturnSingleEntry,
					   IN BOOLEAN RestartScan,
					   IN OUT PULONG Context,
					   OUT PULONG ReturnLength OPTIONAL
					   );
typedef NTSYSAPI NTSTATUS (NTAPI * PZWOPENSYMBOLICLINKOBJECT)(
						 OUT PHANDLE SymbolicLinkHandle,
						 IN ACCESS_MASK DesiredAccess,
						 IN POBJECT_ATTRIBUTES ObjectAttributes
						 );
typedef NTSYSAPI NTSTATUS (NTAPI * PZWQUERYSYMBOLICLINKOBJECT)(
						  IN HANDLE SymbolicLinkHandle,
						  IN OUT PUNICODE_STRING TargetName,
						  OUT PULONG ReturnLength OPTIONAL
						  );
typedef NTSYSAPI NTSTATUS (NTAPI *PZWCREATESYMBOLICLINKOBJECT)(
						   OUT PHANDLE SymbolicLinkHandle,
						   IN ACCESS_MASK DesiredAccess,
						   IN POBJECT_ATTRIBUTES ObjectAttributes,
						   IN PUNICODE_STRING TargetName
						   );
#define DIRECTORY_QUERY                 (0x0001)
#define DIRECTORY_TRAVERSE              (0x0002)
#define DIRECTORY_CREATE_OBJECT         (0x0004)
#define DIRECTORY_CREATE_SUBDIRECTORY   (0x0008)

#define DIRECTORY_ALL_ACCESS (STANDARD_RIGHTS_REQUIRED | 0xF)

#define SYMBOLIC_LINK_QUERY (0x0001)

#define SYMBOLIC_LINK_ALL_ACCESS (STANDARD_RIGHTS_REQUIRED | 0x1)

typedef struct _FINDDATABUF
{

	DIRECTORY_BASIC_INFORMATION DirectoryBaseInfo;
	WCHAR Buffer[4096];
}FINDDATABUF,*PFINDDATABUF;
typedef struct _FIND_OBJECT_DATA
{
	WCHAR Name[260];
	WCHAR* CurrentDirName;
	HANDLE FindHandle;
	ULONG Context;
	PFINDDATABUF FindDataBuffer;
	ULONG NameMaxLen;
}FIND_OBJECT_DATA,*PFIND_OBJECT_DATA;
#endif /* _NTDLL_DEFINE_H_ */
