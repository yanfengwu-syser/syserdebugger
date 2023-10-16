#ifndef _OBJECTDIRECTORY_H_
#define _OBJECTDIRECTORY_H_



typedef struct _OBJECT_DIRECTORY_ENTRY
{
	/*000*/ struct _OBJECT_DIRECTORY_ENTRY *NextEntry;
	/*004*/ POBJECT             Object;
	/*008*/ }
	OBJECT_DIRECTORY_ENTRY,
		* POBJECT_DIRECTORY_ENTRY,
		**PPOBJECT_DIRECTORY_ENTRY;

	// -----------------------------------------------------------------

#define OBJECT_HASH_TABLE_SIZE 37

typedef struct _OBJECT_DIRECTORY
{
	/*000*/ POBJECT_DIRECTORY_ENTRY HashTable [OBJECT_HASH_TABLE_SIZE];
	/*094*/ POBJECT_DIRECTORY_ENTRY CurrentEntry;
	/*098*/ BOOLEAN         CurrentEntryValid;
	/*099*/ BYTE          Reserved1;
	/*09A*/ WORD          Reserved2;
	/*09C*/ DWORD          Reserved3;
	/*0A0*/ }
	OBJECT_DIRECTORY,
		* POBJECT_DIRECTORY,
		**PPOBJECT_DIRECTORY;
	/*
typedef struct _LIST_ENTRY {
		struct _LIST_ENTRY *Flink;
		struct _LIST_ENTRY *Blink;
	} LIST_ENTRY, *PLIST_ENTRY, *RESTRICTED_POINTER PRLIST_ENTRY;
*/
typedef struct _OBJECT_CREATOR_INFO
{
	/*000*/ LIST_ENTRY ObjectList;   // OBJECT_CREATOR_INFO
	/*008*/ HANDLE   UniqueProcessId;
	/*00C*/ WORD    Reserved1;
	/*00E*/ WORD    Reserved2;
	/*010*/ }
	OBJECT_CREATOR_INFO,
		* POBJECT_CREATOR_INFO,
		**PPOBJECT_CREATOR_INFO;
	typedef struct _QUOTA_BLOCK
	{
		/*000*/ DWORD Flags;
		/*004*/ DWORD ChargeCount;
		/*008*/ DWORD PeakPoolUsage [2]; // NonPagedPool, PagedPool
		/*010*/ DWORD PoolUsage   [2]; // NonPagedPool, PagedPool
		/*018*/ DWORD PoolQuota   [2]; // NonPagedPool, PagedPool
		/*020*/ }
		QUOTA_BLOCK,
			* PQUOTA_BLOCK,
			**PPQUOTA_BLOCK;
#define OB_FLAG_CREATE_INFO			0x01 // has OBJECT_CREATE_INFO
#define OB_FLAG_KERNEL_MODE			0x02 // created by kernel
#define OB_FLAG_CREATOR_INFO		0x04 // has OBJECT_CREATOR_INFO
#define OB_FLAG_EXCLUSIVE			0x08 // OBJ_EXCLUSIVE
#define OB_FLAG_PERMANENT			0x10 // OBJ_PERMANENT
#define OB_FLAG_SECURITY			0x20 // has security descriptor
#define OB_FLAG_SINGLE_PROCESS		0x40 // no HandleDBList
typedef struct _OBJECT_HEADER
{
	/*000*/ DWORD    PointerCount;    // number of references
	/*004*/ DWORD    HandleCount;    // number of open handles
	/*008*/ POBJECT_TYPE ObjectType;
	/*00C*/ BYTE     NameOffset;     // -> OBJECT_NAME
	/*00D*/ BYTE     HandleDBOffset;   // -> OBJECT_HANDLE_DB
	/*00E*/ BYTE     QuotaChargesOffset; // -> OBJECT_QUOTA_CHARGES
	/*00F*/ BYTE     ObjectFlags;    // OB_FLAG_*
	/*010*/ union
	{ // OB_FLAG_CREATE_INFO ? ObjectCreateInfo : QuotaBlock
		/*010*/   PQUOTA_BLOCK    QuotaBlock;
		/*010*/   POBJECT_CREATOR_INFO ObjectCreateInfo;
		/*014*/   };
		/*014*/ PSECURITY_DESCRIPTOR SecurityDescriptor;
		/*018*/ }
		OBJECT_HEADER,
			* POBJECT_HEADER,
			**PPOBJECT_HEADER;



typedef struct _OBJECT_NAME
{
	/*000*/ POBJECT_DIRECTORY Directory;
	/*004*/ UNICODE_STRING  Name;
	/*00C*/ DWORD       Reserved;
	/*010*/ }
	OBJECT_NAME,
		* POBJECT_NAME,
		**PPOBJECT_NAME;

typedef struct _OBJECT_HANDLE_DB
{
	/*000*/ union
	{
		/*000*/   struct _EPROCESS       *Process;
		/*000*/   struct _OBJECT_HANDLE_DB_LIST *HandleDBList;
		/*004*/   };
		/*004*/ DWORD HandleCount;
		/*008*/ }
		OBJECT_HANDLE_DB,
			* POBJECT_HANDLE_DB,
			**PPOBJECT_HANDLE_DB;

#define OBJECT_HANDLE_DB_ 	sizeof (OBJECT_HANDLE_DB)

				// -----------------------------------------------------------------

typedef struct _OBJECT_HANDLE_DB_LIST
{
	/*000*/ DWORD      Count;
	/*004*/ OBJECT_HANDLE_DB Entries [1];
	/*???*/ }
	OBJECT_HANDLE_DB_LIST,
		* POBJECT_HANDLE_DB_LIST,
		**PPOBJECT_HANDLE_DB_LIST;

#define OBJECT_HANDLE_DB_LIST_ 		sizeof (OBJECT_HANDLE_DB_LIST)


#define OB_SECURITY_CHARGE 0x00000800

typedef struct _OBJECT_QUOTA_CHARGES
{
	/*000*/ DWORD PagedPoolCharge;
	/*004*/ DWORD NonPagedPoolCharge;
	/*008*/ DWORD SecurityCharge;
	/*00C*/ DWORD Reserved;
	/*010*/ }
	OBJECT_QUOTA_CHARGES,
		* POBJECT_QUOTA_CHARGES,
		**PPOBJECT_QUOTA_CHARGES;//If the OB_FLAG_CREATE_INFO bit of the ObjectFlags in the OBJECT_HEADER is zero, the QuotaBlock member points to a QUOTA_BLOCK structure (Listing 6) that contains statistical information about the current resource usage of the object.

	




typedef struct stObjectPointer{
	struct stObjectPointer *Next;
	DWORD	ObjectHandle;
}ObjectPointer,*PObjectPointer;
typedef struct stObjectDirectoryPointerTable
{
	PObjectPointer Pointer[0x25];
}ObjectDirectoryPointerTable,*PObjectDirectoryPointerTable;

typedef struct stObjFindData{
	union {
		PObjectDirectoryPointerTable ObjectDirectoryTablePointer;
		DWORD	ObjectHandle;
	};	
	DWORD	DirectoryItemIndex;
	DWORD	ReturnObjectHandle;
	PObjectPointer NextObjectPointer;
}OBJFINDDATA;

typedef enum{
	DIRECTORY_OBJECT_TYPE,
	MUTANT_OBJECT_TYPE,
	THREAD_OBJECT_TYPE,
	CONTROLLER_OBJECT_TYPE,
	PROFILE_OBJECT_TYPE,
	EVENT_OBJECT_TYPE,
	TYPE_OBJECT_TYPE,
	SECTION_OBJECT_TYPE,
	EVENTPAIR_OBJECT_TYPE,
	SYMBOLICLINK_OBJECT_TYPE,
	TIMER_OBJECT_TYPE,
	FILE_OBJECT_TYPE,
	DRIVER_OBJECT_TYPE,
	DEVICE_OBJECT_TYPE,
	TOKEN_OBJECT_TYPE,
	IOCOMPLETION_OBJECT_TYPE,
	PROCESS_OBJECT_TYPE,
	ADAPTER_OBJECT_TYPE,
	KEY_OBJECT_TYPE,
	PORT_OBJECT_TYPE,
	SEMAPHORE_OBJECT_TYPE,
	MAX_OBJECT_TYPE,
}OBJECT_TYPE_ID;
#define OBJECT_ROOT_DIRECTORY L"\\"
typedef bool (*ObjectOperatorCallBack)(DWORD,WISP_CHAR**);
bool InitObjectDirectory();
extern DWORD dwObjectRootDirectory;
extern DWORD dwListObjectCounter;
bool GetObjectTypeName(DWORD ObjectHandle,WCHAR *TypeName);
bool GetObjectName(DWORD ObjectHandle,WCHAR* ObjectName);
DWORD GetObjectRootDirectoryHandle();
DWORD GetObjectDirectoryHandleByName(WISP_CHAR * DirectoryName,DWORD dwParentDirectoryHandle=0);
DWORD GetObjectTypeID(DWORD ObjectHandle);
DWORD GetChildObjectHandleByName(WISP_CHAR * DirectoryName,DWORD dwParentDirectoryHandle);
bool FindFirstObject(WISP_CHAR *ObjectName,OBJFINDDATA &FindData);
bool FindNextObject(OBJFINDDATA &FindData);
bool IsDirectoryObjectType(DWORD ObjectHandle);
DWORD GetObjectHeader(DWORD ObjectHandle);
bool ListObject(OBJFINDDATA &FindData,DWORD ObjectType,ObjectOperatorCallBack CallBack,WISP_CHAR **Name=NULL);
bool GetFileObjectName(FILE_OBJECT* FileObject,WCHAR* ObjectName,DWORD dwBufferLen);
#endif /* _OBJECTDIRECTORY_H_ */

