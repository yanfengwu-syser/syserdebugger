#include "stdafx.h"
#include "NtstatStr.h"

NTSTATUS_STR gNtstatusTable[]=
{
		   {"STATUS_WAIT_0"    ,"STATUS_WAIT_0",0x00000000L},
           {"STATUS_WAIT_1"    ,"STATUS_WAIT_1",0x00000001L},
           {"STATUS_WAIT_2"    ,"STATUS_WAIT_2",0x00000002L},
           {"STATUS_WAIT_3"    ,"STATUS_WAIT_3",0x00000003L},
           {"STATUS_WAIT_63"    ,"STATUS_WAIT_63",0x0000003FL},
           {"The success status codes 128 - 191 are reserved for wait completion"
"status with an abandoned mutant object."    ,"STATUS_ABANDONED",0x00000080L},
           {"STATUS_ABANDONED_WAIT_0"    ,"STATUS_ABANDONED_WAIT_0",0x00000080L},
           {"STATUS_ABANDONED_WAIT_63"    ,"STATUS_ABANDONED_WAIT_63",0x000000BFL},
           {"STATUS_USER_APC"    ,"STATUS_USER_APC",0x000000C0L},
           {"STATUS_KERNEL_APC"    ,"STATUS_KERNEL_APC",0x00000100L},
           {"STATUS_ALERTED"    ,"STATUS_ALERTED",0x00000101L},
           {"STATUS_TIMEOUT"    ,"STATUS_TIMEOUT",0x00000102L},
           {"The operation that was requested is pending completion."    ,"STATUS_PENDING",0x00000103L},
           {"A reparse should be performed by the Object Manager since the name of the file resulted in a symbolic link."    ,"STATUS_REPARSE",0x00000104L},
           {"Returned by enumeration APIs to indicate more information is available to successive calls."    ,"STATUS_MORE_ENTRIES",0x00000105L},
           {"Indicates not all privileges referenced are assigned to the caller."
"This allows, for example, all privileges to be disabled without having to know exactly which privileges are assigned."    ,"STATUS_NOT_ALL_ASSIGNED",0x00000106L},
           {"Some of the information to be translated has not been translated."    ,"STATUS_SOME_NOT_MAPPED",0x00000107L},
           {"An open/create operation completed while an oplock break is underway."    ,"STATUS_OPLOCK_BREAK_IN_PROGRESS",0x00000108L},
           {"A new volume has been mounted by a file system."    ,"STATUS_VOLUME_MOUNTED",0x00000109L},
           {"This success level status indicates that the transaction state already exists for the registry sub-tree, but that a transaction commit was previously aborted."
"The commit has now been completed."    ,"STATUS_RXACT_COMMITTED",0x0000010AL},
           {"This indicates that a notify change request has been completed due to closing the handle which made the notify change request."    ,"STATUS_NOTIFY_CLEANUP",0x0000010BL},
           {"This indicates that a notify change request is being completed and that the information is not being returned in the caller's buffer."
"The caller now needs to enumerate the files to find the changes."    ,"STATUS_NOTIFY_ENUM_DIR",0x0000010CL},
           {"{No Quotas}"
"No system quota limits are specifically set for this account."    ,"STATUS_NO_QUOTAS_FOR_ACCOUNT",0x0000010DL},
           {"{Connect Failure on Primary Transport}"
"An attempt was made to connect to the remote server %hs on the primary transport, but the connection failed."
"The computer WAS able to connect on a secondary transport."    ,"STATUS_PRIMARY_TRANSPORT_CONNECT_FAILED",0x0000010EL},
           {"Page fault was a transition fault."    ,"STATUS_PAGE_FAULT_TRANSITION",0x00000110L},
           {"Page fault was a demand zero fault."    ,"STATUS_PAGE_FAULT_DEMAND_ZERO",0x00000111L},
           {"Page fault was a demand zero fault."    ,"STATUS_PAGE_FAULT_COPY_ON_WRITE",0x00000112L},
           {"Page fault was a demand zero fault."    ,"STATUS_PAGE_FAULT_GUARD_PAGE",0x00000113L},
           {"Page fault was satisfied by reading from a secondary storage device."    ,"STATUS_PAGE_FAULT_PAGING_FILE",0x00000114L},
           {"Cached page was locked during operation."    ,"STATUS_CACHE_PAGE_LOCKED",0x00000115L},
           {"Crash dump exists in paging file."    ,"STATUS_CRASH_DUMP",0x00000116L},
           {"Specified buffer contains all zeros."    ,"STATUS_BUFFER_ALL_ZEROS",0x00000117L},
           {"A reparse should be performed by the Object Manager since the name of the file resulted in a symbolic link."    ,"STATUS_REPARSE_OBJECT",0x00000118L},
           {"The device has succeeded a query-stop and its resource requirements have changed."    ,"STATUS_RESOURCE_REQUIREMENTS_CHANGED",0x00000119L},
           {"The translator has translated these resources into the global space and no further translations should be performed."    ,"STATUS_TRANSLATION_COMPLETE",0x00000120L},
           {"The directory service evaluated group memberships locally, as it was unable to contact a global catalog server."    ,"STATUS_DS_MEMBERSHIP_EVALUATED_LOCALLY",0x00000121L},
           {"A process being terminated has no threads to terminate."    ,"STATUS_NOTHING_TO_TERMINATE",0x00000122L},
           {"The specified process is not part of a job."    ,"STATUS_PROCESS_NOT_IN_JOB",0x00000123L},
           {"The specified process is part of a job."    ,"STATUS_PROCESS_IN_JOB",0x00000124L},
           {"{Volume Shadow Copy Service}"
"The system is now ready for hibernation."    ,"STATUS_VOLSNAP_HIBERNATE_READY",0x00000125L},
           {"A file system or file system filter driver has successfully completed an FsFilter operation."    ,"STATUS_FSFILTER_OP_COMPLETED_SUCCESSFULLY",0x00000126L},
           {"Debugger handled exception"    ,"DBG_EXCEPTION_HANDLED",0x00010001L},
           {"Debugger continued"    ,"DBG_CONTINUE",0x00010002L},
           {"{Object Exists}"
"An attempt was made to create an object and the object name already existed."    ,"STATUS_OBJECT_NAME_EXISTS",0x40000000L},
           {"{Thread Suspended}"
"A thread termination occurred while the thread was suspended. The thread was resumed, and termination proceeded."    ,"STATUS_THREAD_WAS_SUSPENDED",0x40000001L},
           {"{Working Set Range Error}"
"An attempt was made to set the working set minimum or maximum to values which are outside of the allowable range."    ,"STATUS_WORKING_SET_LIMIT_RANGE",0x40000002L},
           {"{Image Relocated}"
"An image file could not be mapped at the address specified in the image file. Local fixups must be performed on this image."    ,"STATUS_IMAGE_NOT_AT_BASE",0x40000003L},
           {"This informational level status indicates that a specified registry sub-tree transaction state did not yet exist and had to be created."    ,"STATUS_RXACT_STATE_CREATED",0x40000004L},
           {"{Segment Load}"
"A virtual DOS machine (VDM) is loading, unloading, or moving an MS-DOS or Win16 program segment image."
"An exception is raised so a debugger can load, unload or track symbols and breakpoints within these 16-bit segments."    ,"STATUS_SEGMENT_NOTIFICATION",0x40000005L},
           {"{Local Session Key}"
"A user session key was requested for a local RPC connection. The session key returned is a constant value and not unique to this connection."    ,"STATUS_LOCAL_USER_SESSION_KEY",0x40000006L},
           {"{Invalid Current Directory}"
"The process cannot switch to the startup current directory %hs."
"Select OK to set current directory to %hs, or select CANCEL to exit."    ,"STATUS_BAD_CURRENT_DIRECTORY",0x40000007L},
           {"{Serial IOCTL Complete}"
"A serial I/O operation was completed by another write to a serial port."
"(The IOCTL_SERIAL_XOFF_COUNTER reached zero.)"    ,"STATUS_SERIAL_MORE_WRITES",0x40000008L},
           {"{Registry Recovery}"
"One of the files containing the system's Registry data had to be recovered by use of a log or alternate copy."
"The recovery was successful."    ,"STATUS_REGISTRY_RECOVERED",0x40000009L},
           {"{Redundant Read}"
"To satisfy a read request, the NT fault-tolerant file system successfully read the requested data from a redundant copy."
"This was done because the file system encountered a failure on a member of the fault-tolerant volume, but was unable to reassign the failing area of the device."    ,"STATUS_FT_READ_RECOVERY_FROM_BACKUP",0x4000000AL},
           {"{Redundant Write}"
"To satisfy a write request, the NT fault-tolerant file system successfully wrote a redundant copy of the information."
"This was done because the file system encountered a failure on a member of the fault-tolerant volume, but was not able to reassign the failing area of the device."    ,"STATUS_FT_WRITE_RECOVERY",0x4000000BL},
           {"{Serial IOCTL Timeout}"
"A serial I/O operation completed because the time-out period expired."
"(The IOCTL_SERIAL_XOFF_COUNTER had not reached zero.)"    ,"STATUS_SERIAL_COUNTER_TIMEOUT",0x4000000CL},
           {"{Password Too Complex}"
"The Windows password is too complex to be converted to a LAN Manager password."
"The LAN Manager password returned is a NULL string."    ,"STATUS_NULL_LM_PASSWORD",0x4000000DL},
           {"{Machine Type Mismatch}"
"The image file %hs is valid, but is for a machine type other than the current machine. Select OK to continue, or CANCEL to fail the DLL load."    ,"STATUS_IMAGE_MACHINE_TYPE_MISMATCH",0x4000000EL},
           {"{Partial Data Received}"
"The network transport returned partial data to its client. The remaining data will be sent later."    ,"STATUS_RECEIVE_PARTIAL",0x4000000FL},
           {"{Expedited Data Received}"
"The network transport returned data to its client that was marked as expedited by the remote system."    ,"STATUS_RECEIVE_EXPEDITED",0x40000010L},
           {"{Partial Expedited Data Received}"
"The network transport returned partial data to its client and this data was marked as expedited by the remote system. The remaining data will be sent later."    ,"STATUS_RECEIVE_PARTIAL_EXPEDITED",0x40000011L},
           {"{TDI Event Done}"
"The TDI indication has completed successfully."    ,"STATUS_EVENT_DONE",0x40000012L},
           {"{TDI Event Pending}"
"The TDI indication has entered the pending state."    ,"STATUS_EVENT_PENDING",0x40000013L},
           {"Checking file system on %wZ"    ,"STATUS_CHECKING_FILE_SYSTEM",0x40000014L},
           {"{Fatal Application Exit}"
"%hs"    ,"STATUS_FATAL_APP_EXIT",0x40000015L},
           {"The specified registry key is referenced by a predefined handle."    ,"STATUS_PREDEFINED_HANDLE",0x40000016L},
           {"{Page Unlocked}"
"The page protection of a locked page was changed to 'No Access' and the page was unlocked from memory and from the process."    ,"STATUS_WAS_UNLOCKED",0x40000017L},
           {"%hs"    ,"STATUS_SERVICE_NOTIFICATION",0x40000018L},
           {"{Page Locked}"
"One of the pages to lock was already locked."    ,"STATUS_WAS_LOCKED",0x40000019L},
           {"Application popup: %1 : %2"    ,"STATUS_LOG_HARD_ERROR",0x4000001AL},
           {"STATUS_ALREADY_WIN32"    ,"STATUS_ALREADY_WIN32",0x4000001BL},
           {"Exception status code used by Win32 x86 emulation subsystem."    ,"STATUS_WX86_UNSIMULATE",0x4000001CL},
           {"Exception status code used by Win32 x86 emulation subsystem."    ,"STATUS_WX86_CONTINUE",0x4000001DL},
           {"Exception status code used by Win32 x86 emulation subsystem."    ,"STATUS_WX86_SINGLE_STEP",0x4000001EL},
           {"Exception status code used by Win32 x86 emulation subsystem."    ,"STATUS_WX86_BREAKPOINT",0x4000001FL},
           {"Exception status code used by Win32 x86 emulation subsystem."    ,"STATUS_WX86_EXCEPTION_CONTINUE",0x40000020L},
           {"Exception status code used by Win32 x86 emulation subsystem."    ,"STATUS_WX86_EXCEPTION_LASTCHANCE",0x40000021L},
           {"Exception status code used by Win32 x86 emulation subsystem."    ,"STATUS_WX86_EXCEPTION_CHAIN",0x40000022L},
           {"{Machine Type Mismatch}"
"The image file %hs is valid, but is for a machine type other than the current machine."    ,"STATUS_IMAGE_MACHINE_TYPE_MISMATCH_EXE",0x40000023L},
           {"A yield execution was performed and no thread was available to run."    ,"STATUS_NO_YIELD_PERFORMED",0x40000024L},
           {"The resumable flag to a timer API was ignored."    ,"STATUS_TIMER_RESUME_IGNORED",0x40000025L},
           {"The arbiter has deferred arbitration of these resources to its parent"    ,"STATUS_ARBITRATION_UNHANDLED",0x40000026L},
           {"The device \"%hs\" has detected a CardBus card in its slot, but the firmware on this system is not configured to allow the CardBus controller to be run in CardBus mode."
"The operating system will currently accept only 16-bit (R2) pc-cards on this controller."    ,"STATUS_CARDBUS_NOT_SUPPORTED",0x40000027L},
           {"Exception status code used by Win32 x86 emulation subsystem."    ,"STATUS_WX86_CREATEWX86TIB",0x40000028L},
           {"The CPUs in this multiprocessor system are not all the same revision level.  To use all processors the operating system restricts itself to the features of the least capable processor in the system.  Should problems occur with this system, contact"
"the CPU manufacturer to see if this mix of processors is supported."    ,"STATUS_MP_PROCESSOR_MISMATCH",0x40000029L},
           {"The system was put into hibernation."    ,"STATUS_HIBERNATED",0x4000002AL},
           {"The system was resumed from hibernation."    ,"STATUS_RESUME_HIBERNATION",0x4000002BL},
           {"Windows has detected that the system firmware (BIOS) was updated [previous firmware date = %2, current firmware date %3]."    ,"STATUS_FIRMWARE_UPDATED",0x4000002CL},
           {"A device driver is leaking locked I/O pages causing system degradation.  The system has automatically enabled tracking code in order to try and catch the culprit."    ,"STATUS_DRIVERS_LEAKING_LOCKED_PAGES",0x4000002DL},
           {"Debugger will reply later."    ,"DBG_REPLY_LATER",0x40010001L},
           {"Debugger can not provide handle."    ,"DBG_UNABLE_TO_PROVIDE_HANDLE",0x40010002L},
           {"Debugger terminated thread."    ,"DBG_TERMINATE_THREAD",0x40010003L},
           {"Debugger terminated process."    ,"DBG_TERMINATE_PROCESS",0x40010004L},
           {"Debugger got control C."    ,"DBG_CONTROL_C",0x40010005L},
           {"Debugger printed exception on control C."    ,"DBG_PRINTEXCEPTION_C",0x40010006L},
           {"Debugger received RIP exception."    ,"DBG_RIPEXCEPTION",0x40010007L},
           {"Debugger received control break."    ,"DBG_CONTROL_BREAK",0x40010008L},
           {"Debugger command communication exception."    ,"DBG_COMMAND_EXCEPTION",0x40010009L},
           {"{EXCEPTION}"
"Guard Page Exception"
"A page of memory that marks the end of a data structure, such as a stack or an array, has been accessed."    ,"STATUS_GUARD_PAGE_VIOLATION",0x80000001L},
           {"{EXCEPTION}"
"Alignment Fault"
"A datatype misalignment was detected in a load or store instruction."    ,"STATUS_DATATYPE_MISALIGNMENT",0x80000002L},
           {"{EXCEPTION}"
"Breakpoint"
"A breakpoint has been reached."    ,"STATUS_BREAKPOINT",0x80000003L},
           {"{EXCEPTION}"
"Single Step"
"A single step or trace operation has just been completed."    ,"STATUS_SINGLE_STEP",0x80000004L},
           {"{Buffer Overflow}"
"The data was too large to fit into the specified buffer."    ,"STATUS_BUFFER_OVERFLOW",0x80000005L},
           {"{No More Files}"
"No more files were found which match the file specification."    ,"STATUS_NO_MORE_FILES",0x80000006L},
           {"{Kernel Debugger Awakened}"
"the system debugger was awakened by an interrupt."    ,"STATUS_WAKE_SYSTEM_DEBUGGER",0x80000007L},
           {"{Handles Closed}"
"Handles to objects have been automatically closed as a result of the requested operation."    ,"STATUS_HANDLES_CLOSED",0x8000000AL},
           {"{Non-Inheritable ACL}"
"An access control list (ACL},"    ,"STATUS_NO_INHERITANCE",0x8000000BL},
           {"{GUID Substitution}"
"During the translation of a global identifier (GUID) to a Windows security ID (SID), no administratively-defined GUID prefix was found."
"A substitute prefix was used, which will not compromise system security."
"However, this may provide a more restrictive access than intended."    ,"STATUS_GUID_SUBSTITUTION_MADE",0x8000000CL},
           {"{Partial Copy}"
"Due to protection conflicts not all the requested bytes could be copied."    ,"STATUS_PARTIAL_COPY",0x8000000DL},
           {"{Out of Paper}"
"The printer is out of paper."    ,"STATUS_DEVICE_PAPER_EMPTY",0x8000000EL},
           {"{Device Power Is Off}"
"The printer power has been turned off."    ,"STATUS_DEVICE_POWERED_OFF",0x8000000FL},
           {"{Device Offline}"
"The printer has been taken offline."    ,"STATUS_DEVICE_OFF_LINE",0x80000010L},
           {"{Device Busy}"
"The device is currently busy."    ,"STATUS_DEVICE_BUSY",0x80000011L},
           {"{No More EAs}"
"No more extended attributes (EAs) were found for the file."    ,"STATUS_NO_MORE_EAS",0x80000012L},
           {"{Illegal EA}"
"The specified extended attribute (EA) name contains at least one illegal character."    ,"STATUS_INVALID_EA_NAME",0x80000013L},
           {"{Inconsistent EA List}"
"The extended attribute (EA) list is inconsistent."    ,"STATUS_EA_LIST_INCONSISTENT",0x80000014L},
           {"{Invalid EA Flag}"
"An invalid extended attribute (EA) flag was set."    ,"STATUS_INVALID_EA_FLAG",0x80000015L},
           {"{Verifying Disk}"
"The media has changed and a verify operation is in progress so no reads or writes may be performed to the device, except those used in the verify operation."    ,"STATUS_VERIFY_REQUIRED",0x80000016L},
           {"{Too Much Information}"
"The specified access control list (ACL},"    ,"STATUS_EXTRANEOUS_INFORMATION",0x80000017L},
           {"This warning level status indicates that the transaction state already exists for the registry sub-tree, but that a transaction commit was previously aborted."
"The commit has NOT been completed, but has not been rolled back either (so it may still be committed if desired)."    ,"STATUS_RXACT_COMMIT_NECESSARY",0x80000018L},
           {"{No More Entries}"
"No more entries are available from an enumeration operation."    ,"STATUS_NO_MORE_ENTRIES",0x8000001AL},
           {"{Filemark Found}"
"A filemark was detected."    ,"STATUS_FILEMARK_DETECTED",0x8000001BL},
           {"{Media Changed}"
"The media may have changed."    ,"STATUS_MEDIA_CHANGED",0x8000001CL},
           {"{I/O Bus Reset}"
"An I/O bus reset was detected."    ,"STATUS_BUS_RESET",0x8000001DL},
           {"{End of Media}"
"The end of the media was encountered."    ,"STATUS_END_OF_MEDIA",0x8000001EL},
           {"Beginning of tape or partition has been detected."    ,"STATUS_BEGINNING_OF_MEDIA",0x8000001FL},
           {"{Media Changed}"
"The media may have changed."    ,"STATUS_MEDIA_CHECK",0x80000020L},
           {"A tape access reached a setmark."    ,"STATUS_SETMARK_DETECTED",0x80000021L},
           {"During a tape access, the end of the data written is reached."    ,"STATUS_NO_DATA_DETECTED",0x80000022L},
           {"The redirector is in use and cannot be unloaded."    ,"STATUS_REDIRECTOR_HAS_OPEN_HANDLES",0x80000023L},
           {"The server is in use and cannot be unloaded."    ,"STATUS_SERVER_HAS_OPEN_HANDLES",0x80000024L},
           {"The specified connection has already been disconnected."    ,"STATUS_ALREADY_DISCONNECTED",0x80000025L},
           {"A long jump has been executed."    ,"STATUS_LONGJUMP",0x80000026L},
           {"A cleaner cartridge is present in the tape library."    ,"STATUS_CLEANER_CARTRIDGE_INSTALLED",0x80000027L},
           {"The Plug and Play query operation was not successful."    ,"STATUS_PLUGPLAY_QUERY_VETOED",0x80000028L},
           {"A frame consolidation has been executed."    ,"STATUS_UNWIND_CONSOLIDATE",0x80000029L},
           {"{Registry Hive Recovered}"
"Registry hive (file):"
"%hs"
"was corrupted and it has been recovered. Some data might have been lost."    ,"STATUS_REGISTRY_HIVE_RECOVERED",0x8000002AL},
           {"The application is attempting to run executable code from the module %hs.  This may be insecure.  An alternative, %hs, is available.  Should the application use the secure module %hs?"    ,"STATUS_DLL_MIGHT_BE_INSECURE",0x8000002BL},
           {"The application is loading executable code from the module %hs.  This is secure, but may be incompatible with previous releases of the operating system.  An alternative, %hs, is available.  Should the application use the secure module %hs?"    ,"STATUS_DLL_MIGHT_BE_INCOMPATIBLE",0x8000002CL},
           {"Debugger did not handle the exception."    ,"DBG_EXCEPTION_NOT_HANDLED",0x80010001L},
           {"The cluster node is already up."    ,"STATUS_CLUSTER_NODE_ALREADY_UP",0x80130001L},
           {"The cluster node is already down."    ,"STATUS_CLUSTER_NODE_ALREADY_DOWN",0x80130002L},
           {"The cluster network is already online."    ,"STATUS_CLUSTER_NETWORK_ALREADY_ONLINE",0x80130003L},
           {"The cluster network is already offline."    ,"STATUS_CLUSTER_NETWORK_ALREADY_OFFLINE",0x80130004L},
           {"The cluster node is already a member of the cluster."    ,"STATUS_CLUSTER_NODE_ALREADY_MEMBER",0x80130005L},
           {"{Operation Failed}"
"The requested operation was unsuccessful."    ,"STATUS_UNSUCCESSFUL",0xC0000001L},
           {"{Not Implemented}"
"The requested operation is not implemented."    ,"STATUS_NOT_IMPLEMENTED",0xC0000002L},
           {"{Invalid Parameter}"
"The specified information class is not a valid information class for the specified object."    ,"STATUS_INVALID_INFO_CLASS",0xC0000003L},
           {"The specified information record length does not match the length required for the specified information class."    ,"STATUS_INFO_LENGTH_MISMATCH",0xC0000004L},
           {"The instruction at \"0x%08lx\" referenced memory at \"0x%08lx\". The memory could not be \"%s\"."    ,"STATUS_ACCESS_VIOLATION",0xC0000005L},
           {"The instruction at \"0x%08lx\" referenced memory at \"0x%08lx\". The required data was not placed into memory because of an I/O error status of \"0x%08lx\"."    ,"STATUS_IN_PAGE_ERROR",0xC0000006L},
           {"The pagefile quota for the process has been exhausted."    ,"STATUS_PAGEFILE_QUOTA",0xC0000007L},
           {"An invalid HANDLE was specified."    ,"STATUS_INVALID_HANDLE",0xC0000008L},
           {"An invalid initial stack was specified in a call to NtCreateThread."    ,"STATUS_BAD_INITIAL_STACK",0xC0000009L},
           {"An invalid initial start address was specified in a call to NtCreateThread."    ,"STATUS_BAD_INITIAL_PC",0xC000000AL},
           {"An invalid Client ID was specified."    ,"STATUS_INVALID_CID",0xC000000BL},
           {"An attempt was made to cancel or set a timer that has an associated APC and the subject thread is not the thread that originally set the timer with an associated APC routine."    ,"STATUS_TIMER_NOT_CANCELED",0xC000000CL},
           {"An invalid parameter was passed to a service or function."    ,"STATUS_INVALID_PARAMETER",0xC000000DL},
           {"A device which does not exist was specified."    ,"STATUS_NO_SUCH_DEVICE",0xC000000EL},
           {"{File Not Found}"
"The file %hs does not exist."    ,"STATUS_NO_SUCH_FILE",0xC000000FL},
           {"The specified request is not a valid operation for the target device."    ,"STATUS_INVALID_DEVICE_REQUEST",0xC0000010L},
           {"The end-of-file marker has been reached. There is no valid data in the file beyond this marker."    ,"STATUS_END_OF_FILE",0xC0000011L},
           {"{Wrong Volume}"
"The wrong volume is in the drive."
"Please insert volume %hs into drive %hs."    ,"STATUS_WRONG_VOLUME",0xC0000012L},
           {"{No Disk}"
"There is no disk in the drive."
"Please insert a disk into drive %hs."    ,"STATUS_NO_MEDIA_IN_DEVICE",0xC0000013L},
           {"{Unknown Disk Format}"
"The disk in drive %hs is not formatted properly."
"Please check the disk, and reformat if necessary."    ,"STATUS_UNRECOGNIZED_MEDIA",0xC0000014L},
           {"{Sector Not Found}"
"The specified sector does not exist."    ,"STATUS_NONEXISTENT_SECTOR",0xC0000015L},
           {"{Still Busy}"
"The specified I/O request packet (IRP) cannot be disposed of because the I/O operation is not complete."    ,"STATUS_MORE_PROCESSING_REQUIRED",0xC0000016L},
           {"{Not Enough Quota}"
"Not enough virtual memory or paging file quota is available to complete the specified operation."    ,"STATUS_NO_MEMORY",0xC0000017L},
           {"{Conflicting Address Range}"
"The specified address range conflicts with the address space."    ,"STATUS_CONFLICTING_ADDRESSES",0xC0000018L},
           {"Address range to unmap is not a mapped view."    ,"STATUS_NOT_MAPPED_VIEW",0xC0000019L},
           {"Virtual memory cannot be freed."    ,"STATUS_UNABLE_TO_FREE_VM",0xC000001AL},
           {"Specified section cannot be deleted."    ,"STATUS_UNABLE_TO_DELETE_SECTION",0xC000001BL},
           {"An invalid system service was specified in a system service call."    ,"STATUS_INVALID_SYSTEM_SERVICE",0xC000001CL},
           {"{EXCEPTION}"
"Illegal Instruction"
"An attempt was made to execute an illegal instruction."    ,"STATUS_ILLEGAL_INSTRUCTION",0xC000001DL},
           {"{Invalid Lock Sequence}"
"An attempt was made to execute an invalid lock sequence."    ,"STATUS_INVALID_LOCK_SEQUENCE",0xC000001EL},
           {"{Invalid Mapping}"
"An attempt was made to create a view for a section which is bigger than the section."    ,"STATUS_INVALID_VIEW_SIZE",0xC000001FL},
           {"{Bad File}"
"The attributes of the specified mapping file for a section of memory cannot be read."    ,"STATUS_INVALID_FILE_FOR_SECTION",0xC0000020L},
           {"{Already Committed}"
"The specified address range is already committed."    ,"STATUS_ALREADY_COMMITTED",0xC0000021L},
           {"{Access Denied}"
"A process has requested access to an object, but has not been granted those access rights."    ,"STATUS_ACCESS_DENIED",0xC0000022L},
           {"{Buffer Too Small}"
"The buffer is too small to contain the entry. No information has been written to the buffer."    ,"STATUS_BUFFER_TOO_SMALL",0xC0000023L},
           {"{Wrong Type}"
"There is a mismatch between the type of object required by the requested operation and the type of object that is specified in the request."    ,"STATUS_OBJECT_TYPE_MISMATCH",0xC0000024L},
           {"{EXCEPTION}"
"Cannot Continue"
"Windows cannot continue from this exception."    ,"STATUS_NONCONTINUABLE_EXCEPTION",0xC0000025L},
           {"An invalid exception disposition was returned by an exception handler."    ,"STATUS_INVALID_DISPOSITION",0xC0000026L},
           {"Unwind exception code."    ,"STATUS_UNWIND",0xC0000027L},
           {"An invalid or unaligned stack was encountered during an unwind operation."    ,"STATUS_BAD_STACK",0xC0000028L},
           {"An invalid unwind target was encountered during an unwind operation."    ,"STATUS_INVALID_UNWIND_TARGET",0xC0000029L},
           {"An attempt was made to unlock a page of memory which was not locked."    ,"STATUS_NOT_LOCKED",0xC000002AL},
           {"Device parity error on I/O operation."    ,"STATUS_PARITY_ERROR",0xC000002BL},
           {"An attempt was made to decommit uncommitted virtual memory."    ,"STATUS_UNABLE_TO_DECOMMIT_VM",0xC000002CL},
           {"An attempt was made to change the attributes on memory that has not been committed."    ,"STATUS_NOT_COMMITTED",0xC000002DL},
           {"Invalid Object Attributes specified to NtCreatePort or invalid Port Attributes specified to NtConnectPort"    ,"STATUS_INVALID_PORT_ATTRIBUTES",0xC000002EL},
           {"Length of message passed to NtRequestPort or NtRequestWaitReplyPort was longer than the maximum message allowed by the port."    ,"STATUS_PORT_MESSAGE_TOO_LONG",0xC000002FL},
           {"An invalid combination of parameters was specified."    ,"STATUS_INVALID_PARAMETER_MIX",0xC0000030L},
           {"An attempt was made to lower a quota limit below the current usage."    ,"STATUS_INVALID_QUOTA_LOWER",0xC0000031L},
           {"{Corrupt Disk}"
"The file system structure on the disk is corrupt and unusable."
"Please run the Chkdsk utility on the volume %hs."    ,"STATUS_DISK_CORRUPT_ERROR",0xC0000032L},
           {"Object Name invalid."    ,"STATUS_OBJECT_NAME_INVALID",0xC0000033L},
           {"Object Name not found."    ,"STATUS_OBJECT_NAME_NOT_FOUND",0xC0000034L},
           {"Object Name already exists."    ,"STATUS_OBJECT_NAME_COLLISION",0xC0000035L},
           {"Attempt to send a message to a disconnected communication port."    ,"STATUS_PORT_DISCONNECTED",0xC0000037L},
           {"An attempt was made to attach to a device that was already attached to another device."    ,"STATUS_DEVICE_ALREADY_ATTACHED",0xC0000038L},
           {"Object Path Component was not a directory object."    ,"STATUS_OBJECT_PATH_INVALID",0xC0000039L},
           {"{Path Not Found}"
"The path %hs does not exist."    ,"STATUS_OBJECT_PATH_NOT_FOUND",0xC000003AL},
           {"Object Path Component was not a directory object."    ,"STATUS_OBJECT_PATH_SYNTAX_BAD",0xC000003BL},
           {"{Data Overrun}"
"A data overrun error occurred."    ,"STATUS_DATA_OVERRUN",0xC000003CL},
           {"{Data Late}"
"A data late error occurred."    ,"STATUS_DATA_LATE_ERROR",0xC000003DL},
           {"{Data Error}"
"An error in reading or writing data occurred."    ,"STATUS_DATA_ERROR",0xC000003EL},
           {"{Bad CRC}"
"A cyclic redundancy check (CRC) checksum error occurred."    ,"STATUS_CRC_ERROR",0xC000003FL},
           {"{Section Too Large}"
"The specified section is too big to map the file."    ,"STATUS_SECTION_TOO_BIG",0xC0000040L},
           {"The NtConnectPort request is refused."    ,"STATUS_PORT_CONNECTION_REFUSED",0xC0000041L},
           {"The type of port handle is invalid for the operation requested."    ,"STATUS_INVALID_PORT_HANDLE",0xC0000042L},
           {"A file cannot be opened because the share access flags are incompatible."    ,"STATUS_SHARING_VIOLATION",0xC0000043L},
           {"Insufficient quota exists to complete the operation"    ,"STATUS_QUOTA_EXCEEDED",0xC0000044L},
           {"The specified page protection was not valid."    ,"STATUS_INVALID_PAGE_PROTECTION",0xC0000045L},
           {"An attempt to release a mutant object was made by a thread that was not the owner of the mutant object."    ,"STATUS_MUTANT_NOT_OWNED",0xC0000046L},
           {"An attempt was made to release a semaphore such that its maximum count would have been exceeded."    ,"STATUS_SEMAPHORE_LIMIT_EXCEEDED",0xC0000047L},
           {"An attempt to set a processes DebugPort or ExceptionPort was made, but a port already exists in the process or"
"an attempt to set a file's CompletionPort made, but a port was already set in the file."    ,"STATUS_PORT_ALREADY_SET",0xC0000048L},
           {"An attempt was made to query image information on a section which does not map an image."    ,"STATUS_SECTION_NOT_IMAGE",0xC0000049L},
           {"An attempt was made to suspend a thread whose suspend count was at its maximum."    ,"STATUS_SUSPEND_COUNT_EXCEEDED",0xC000004AL},
           {"An attempt was made to suspend a thread that has begun termination."    ,"STATUS_THREAD_IS_TERMINATING",0xC000004BL},
           {"An attempt was made to set the working set limit to an invalid value (minimum greater than maximum, etc)."    ,"STATUS_BAD_WORKING_SET_LIMIT",0xC000004CL},
           {"A section was created to map a file which is not compatible to an already existing section which maps the same file."    ,"STATUS_INCOMPATIBLE_FILE_MAP",0xC000004DL},
           {"A view to a section specifies a protection which is incompatible with the initial view's protection."    ,"STATUS_SECTION_PROTECTION",0xC000004EL},
           {"An operation involving EAs failed because the file system does not support EAs."    ,"STATUS_EAS_NOT_SUPPORTED",0xC000004FL},
           {"An EA operation failed because EA set is too large."    ,"STATUS_EA_TOO_LARGE",0xC0000050L},
           {"An EA operation failed because the name or EA index is invalid."    ,"STATUS_NONEXISTENT_EA_ENTRY",0xC0000051L},
           {"The file for which EAs were requested has no EAs."    ,"STATUS_NO_EAS_ON_FILE",0xC0000052L},
           {"The EA is corrupt and non-readable."    ,"STATUS_EA_CORRUPT_ERROR",0xC0000053L},
           {"A requested read/write cannot be granted due to a conflicting file lock."    ,"STATUS_FILE_LOCK_CONFLICT",0xC0000054L},
           {"A requested file lock cannot be granted due to other existing locks."    ,"STATUS_LOCK_NOT_GRANTED",0xC0000055L},
           {"A non close operation has been requested of a file object with a delete pending."    ,"STATUS_DELETE_PENDING",0xC0000056L},
           {"An attempt was made to set the control attribute on a file. This attribute is not supported in the target file system."    ,"STATUS_CTL_FILE_NOT_SUPPORTED",0xC0000057L},
           {"Indicates a revision number encountered or specified is not one known by the service. It may be a more recent revision than the service is aware of."    ,"STATUS_UNKNOWN_REVISION",0xC0000058L},
           {"Indicates two revision levels are incompatible."    ,"STATUS_REVISION_MISMATCH",0xC0000059L},
           {"Indicates a particular Security ID may not be assigned as the owner of an object."    ,"STATUS_INVALID_OWNER",0xC000005AL},
           {"Indicates a particular Security ID may not be assigned as the primary group of an object."    ,"STATUS_INVALID_PRIMARY_GROUP",0xC000005BL},
           {"An attempt has been made to operate on an impersonation token by a thread that is not currently impersonating a client."    ,"STATUS_NO_IMPERSONATION_TOKEN",0xC000005CL},
           {"A mandatory group may not be disabled."    ,"STATUS_CANT_DISABLE_MANDATORY",0xC000005DL},
           {"There are currently no logon servers available to service the logon request."    ,"STATUS_NO_LOGON_SERVERS",0xC000005EL},
           {"A specified logon session does not exist. It may already have been terminated."    ,"STATUS_NO_SUCH_LOGON_SESSION",0xC000005FL},
           {"A specified privilege does not exist."    ,"STATUS_NO_SUCH_PRIVILEGE",0xC0000060L},
           {"A required privilege is not held by the client."    ,"STATUS_PRIVILEGE_NOT_HELD",0xC0000061L},
           {"The name provided is not a properly formed account name."    ,"STATUS_INVALID_ACCOUNT_NAME",0xC0000062L},
           {"The specified user already exists."    ,"STATUS_USER_EXISTS",0xC0000063L},
           {"The specified user does not exist."    ,"STATUS_NO_SUCH_USER",0xC0000064L},
           {"The specified group already exists."    ,"STATUS_GROUP_EXISTS",0xC0000065L},
           {"The specified group does not exist."    ,"STATUS_NO_SUCH_GROUP",0xC0000066L},
           {"The specified user account is already in the specified group account."
"Also used to indicate a group cannot be deleted because it contains a member."    ,"STATUS_MEMBER_IN_GROUP",0xC0000067L},
           {"The specified user account is not a member of the specified group account."    ,"STATUS_MEMBER_NOT_IN_GROUP",0xC0000068L},
           {"Indicates the requested operation would disable or delete the last remaining administration account."
"This is not allowed to prevent creating a situation in which the system cannot be administrated."    ,"STATUS_LAST_ADMIN",0xC0000069L},
           {"When trying to update a password, this return status indicates that the value provided as the current password is not correct."    ,"STATUS_WRONG_PASSWORD",0xC000006AL},
           {"When trying to update a password, this return status indicates that the value provided for the new password contains values that are not allowed in passwords."    ,"STATUS_ILL_FORMED_PASSWORD",0xC000006BL},
           {"When trying to update a password, this status indicates that some password update rule has been violated. For example, the password may not meet length criteria."    ,"STATUS_PASSWORD_RESTRICTION",0xC000006CL},
           {"The attempted logon is invalid. This is either due to a bad username or authentication information."    ,"STATUS_LOGON_FAILURE",0xC000006DL},
           {"Indicates a referenced user name and authentication information are valid, but some user account restriction has prevented successful authentication (such as time-of-day restrictions)."    ,"STATUS_ACCOUNT_RESTRICTION",0xC000006EL},
           {"The user account has time restrictions and may not be logged onto at this time."    ,"STATUS_INVALID_LOGON_HOURS",0xC000006FL},
           {"The user account is restricted such that it may not be used to log on from the source workstation."    ,"STATUS_INVALID_WORKSTATION",0xC0000070L},
           {"The user account's password has expired."    ,"STATUS_PASSWORD_EXPIRED",0xC0000071L},
           {"The referenced account is currently disabled and may not be logged on to."    ,"STATUS_ACCOUNT_DISABLED",0xC0000072L},
           {"None of the information to be translated has been translated."    ,"STATUS_NONE_MAPPED",0xC0000073L},
           {"The number of LUIDs requested may not be allocated with a single allocation."    ,"STATUS_TOO_MANY_LUIDS_REQUESTED",0xC0000074L},
           {"Indicates there are no more LUIDs to allocate."    ,"STATUS_LUIDS_EXHAUSTED",0xC0000075L},
           {"Indicates the sub-authority value is invalid for the particular use."    ,"STATUS_INVALID_SUB_AUTHORITY",0xC0000076L},
           {"Indicates the ACL structure is not valid."    ,"STATUS_INVALID_ACL",0xC0000077L},
           {"Indicates the SID structure is not valid."    ,"STATUS_INVALID_SID",0xC0000078L},
           {"Indicates the SECURITY_DESCRIPTOR structure is not valid."    ,"STATUS_INVALID_SECURITY_DESCR",0xC0000079L},
           {"Indicates the specified procedure address cannot be found in the DLL."    ,"STATUS_PROCEDURE_NOT_FOUND",0xC000007AL},
           {"{Bad Image}"
"The application or DLL %hs is not a valid Windows image. Please check this against your installation diskette."    ,"STATUS_INVALID_IMAGE_FORMAT",0xC000007BL},
           {"An attempt was made to reference a token that doesn't exist."
"This is typically done by referencing the token associated with a thread when the thread is not impersonating a client."    ,"STATUS_NO_TOKEN",0xC000007CL},
           {"Indicates that an attempt to build either an inherited ACL or ACE was not successful."
"This can be caused by a number of things. One of the more probable causes is the replacement of a CreatorId with an SID that didn't fit into the ACE or ACL."    ,"STATUS_BAD_INHERITANCE_ACL",0xC000007DL},
           {"The range specified in NtUnlockFile was not locked."    ,"STATUS_RANGE_NOT_LOCKED",0xC000007EL},
           {"An operation failed because the disk was full."    ,"STATUS_DISK_FULL",0xC000007FL},
           {"The GUID allocation server is [already] disabled at the moment."    ,"STATUS_SERVER_DISABLED",0xC0000080L},
           {"The GUID allocation server is [already] enabled at the moment."    ,"STATUS_SERVER_NOT_DISABLED",0xC0000081L},
           {"Too many GUIDs were requested from the allocation server at once."    ,"STATUS_TOO_MANY_GUIDS_REQUESTED",0xC0000082L},
           {"The GUIDs could not be allocated because the Authority Agent was exhausted."    ,"STATUS_GUIDS_EXHAUSTED",0xC0000083L},
           {"The value provided was an invalid value for an identifier authority."    ,"STATUS_INVALID_ID_AUTHORITY",0xC0000084L},
           {"There are no more authority agent values available for the given identifier authority value."    ,"STATUS_AGENTS_EXHAUSTED",0xC0000085L},
           {"An invalid volume label has been specified."    ,"STATUS_INVALID_VOLUME_LABEL",0xC0000086L},
           {"A mapped section could not be extended."    ,"STATUS_SECTION_NOT_EXTENDED",0xC0000087L},
           {"Specified section to flush does not map a data file."    ,"STATUS_NOT_MAPPED_DATA",0xC0000088L},
           {"Indicates the specified image file did not contain a resource section."    ,"STATUS_RESOURCE_DATA_NOT_FOUND",0xC0000089L},
           {"Indicates the specified resource type cannot be found in the image file."    ,"STATUS_RESOURCE_TYPE_NOT_FOUND",0xC000008AL},
           {"Indicates the specified resource name cannot be found in the image file."    ,"STATUS_RESOURCE_NAME_NOT_FOUND",0xC000008BL},
           {"{EXCEPTION}"
"Array bounds exceeded."    ,"STATUS_ARRAY_BOUNDS_EXCEEDED",0xC000008CL},
           {"{EXCEPTION}"
"Floating-point denormal operand."    ,"STATUS_FLOAT_DENORMAL_OPERAND",0xC000008DL},
           {"{EXCEPTION}"
"Floating-point division by zero."    ,"STATUS_FLOAT_DIVIDE_BY_ZERO",0xC000008EL},
           {"{EXCEPTION}"
"Floating-point inexact result."    ,"STATUS_FLOAT_INEXACT_RESULT",0xC000008FL},
           {"{EXCEPTION}"
"Floating-point invalid operation."    ,"STATUS_FLOAT_INVALID_OPERATION",0xC0000090L},
           {"{EXCEPTION}"
"Floating-point overflow."    ,"STATUS_FLOAT_OVERFLOW",0xC0000091L},
           {"{EXCEPTION}"
"Floating-point stack check."    ,"STATUS_FLOAT_STACK_CHECK",0xC0000092L},
           {"{EXCEPTION}"
"Floating-point underflow."    ,"STATUS_FLOAT_UNDERFLOW",0xC0000093L},
           {"{EXCEPTION}"
"Integer division by zero."    ,"STATUS_INTEGER_DIVIDE_BY_ZERO",0xC0000094L},
           {"{EXCEPTION}"
"Integer overflow."    ,"STATUS_INTEGER_OVERFLOW",0xC0000095L},
           {"{EXCEPTION}"
"Privileged instruction."    ,"STATUS_PRIVILEGED_INSTRUCTION",0xC0000096L},
           {"An attempt was made to install more paging files than the system supports."    ,"STATUS_TOO_MANY_PAGING_FILES",0xC0000097L},
           {"The volume for a file has been externally altered such that the opened file is no longer valid."    ,"STATUS_FILE_INVALID",0xC0000098L},
           {"When a block of memory is allotted for future updates, such as the memory allocated to hold discretionary access control and primary group information, successive updates may exceed the amount of memory originally allotted."
"Since quota may already have been charged to several processes which have handles to the object, it is not reasonable to alter the size of the allocated memory."
"Instead, a request that requires more memory than has been allotted must fail and the STATUS_ALLOTED_SPACE_EXCEEDED error returned."    ,"STATUS_ALLOTTED_SPACE_EXCEEDED",0xC0000099L},
           {"Insufficient system resources exist to complete the API."    ,"STATUS_INSUFFICIENT_RESOURCES",0xC000009AL},
           {"An attempt has been made to open a DFS exit path control file."    ,"STATUS_DFS_EXIT_PATH_FOUND",0xC000009BL},
           {"STATUS_DEVICE_DATA_ERROR"    ,"STATUS_DEVICE_DATA_ERROR",0xC000009CL},
           {"STATUS_DEVICE_NOT_CONNECTED"    ,"STATUS_DEVICE_NOT_CONNECTED",0xC000009DL},
           {"STATUS_DEVICE_POWER_FAILURE"    ,"STATUS_DEVICE_POWER_FAILURE",0xC000009EL},
           {"Virtual memory cannot be freed as base address is not the base of the region and a region size of zero was specified."    ,"STATUS_FREE_VM_NOT_AT_BASE",0xC000009FL},
           {"An attempt was made to free virtual memory which is not allocated."    ,"STATUS_MEMORY_NOT_ALLOCATED",0xC00000A0L},
           {"The working set is not big enough to allow the requested pages to be locked."    ,"STATUS_WORKING_SET_QUOTA",0xC00000A1L},
           {"{Write Protect Error}"
"The disk cannot be written to because it is write protected."
"Please remove the write protection from the volume %hs in drive %hs."    ,"STATUS_MEDIA_WRITE_PROTECTED",0xC00000A2L},
           {"{Drive Not Ready}"
"The drive is not ready for use; its door may be open."
"Please check drive %hs and make sure that a disk is inserted and that the drive door is closed."    ,"STATUS_DEVICE_NOT_READY",0xC00000A3L},
           {"The specified attributes are invalid, or incompatible with the attributes for the group as a whole."    ,"STATUS_INVALID_GROUP_ATTRIBUTES",0xC00000A4L},
           {"A specified impersonation level is invalid."
"Also used to indicate a required impersonation level was not provided."    ,"STATUS_BAD_IMPERSONATION_LEVEL",0xC00000A5L},
           {"An attempt was made to open an Anonymous level token."
"Anonymous tokens may not be opened."    ,"STATUS_CANT_OPEN_ANONYMOUS",0xC00000A6L},
           {"The validation information class requested was invalid."    ,"STATUS_BAD_VALIDATION_CLASS",0xC00000A7L},
           {"The type of a token object is inappropriate for its attempted use."    ,"STATUS_BAD_TOKEN_TYPE",0xC00000A8L},
           {"The type of a token object is inappropriate for its attempted use."    ,"STATUS_BAD_MASTER_BOOT_RECORD",0xC00000A9L},
           {"An attempt was made to execute an instruction at an unaligned address and the host system does not support unaligned instruction references."    ,"STATUS_INSTRUCTION_MISALIGNMENT",0xC00000AAL},
           {"The maximum named pipe instance count has been reached."    ,"STATUS_INSTANCE_NOT_AVAILABLE",0xC00000ABL},
           {"An instance of a named pipe cannot be found in the listening state."    ,"STATUS_PIPE_NOT_AVAILABLE",0xC00000ACL},
           {"The named pipe is not in the connected or closing state."    ,"STATUS_INVALID_PIPE_STATE",0xC00000ADL},
           {"The specified pipe is set to complete operations and there are current I/O operations queued so it cannot be changed to queue operations."    ,"STATUS_PIPE_BUSY",0xC00000AEL},
           {"The specified handle is not open to the server end of the named pipe."    ,"STATUS_ILLEGAL_FUNCTION",0xC00000AFL},
           {"The specified named pipe is in the disconnected state."    ,"STATUS_PIPE_DISCONNECTED",0xC00000B0L},
           {"The specified named pipe is in the closing state."    ,"STATUS_PIPE_CLOSING",0xC00000B1L},
           {"The specified named pipe is in the connected state."    ,"STATUS_PIPE_CONNECTED",0xC00000B2L},
           {"The specified named pipe is in the listening state."    ,"STATUS_PIPE_LISTENING",0xC00000B3L},
           {"The specified named pipe is not in message mode."    ,"STATUS_INVALID_READ_MODE",0xC00000B4L},
           {"{Device Timeout}"
"The specified I/O operation on %hs was not completed before the time-out period expired."    ,"STATUS_IO_TIMEOUT",0xC00000B5L},
           {"The specified file has been closed by another process."    ,"STATUS_FILE_FORCED_CLOSED",0xC00000B6L},
           {"Profiling not started."    ,"STATUS_PROFILING_NOT_STARTED",0xC00000B7L},
           {"Profiling not stopped."    ,"STATUS_PROFILING_NOT_STOPPED",0xC00000B8L},
           {"The passed ACL did not contain the minimum required information."    ,"STATUS_COULD_NOT_INTERPRET",0xC00000B9L},
           {"The file that was specified as a target is a directory and the caller specified that it could be anything but a directory."    ,"STATUS_FILE_IS_A_DIRECTORY",0xC00000BAL},
           {"The request is not supported."    ,"STATUS_NOT_SUPPORTED",0xC00000BBL},
           {"This remote computer is not listening."    ,"STATUS_REMOTE_NOT_LISTENING",0xC00000BCL},
           {"A duplicate name exists on the network."    ,"STATUS_DUPLICATE_NAME",0xC00000BDL},
           {"The network path cannot be located."    ,"STATUS_BAD_NETWORK_PATH",0xC00000BEL},
           {"The network is busy."    ,"STATUS_NETWORK_BUSY",0xC00000BFL},
           {"This device does not exist."    ,"STATUS_DEVICE_DOES_NOT_EXIST",0xC00000C0L},
           {"The network BIOS command limit has been reached."    ,"STATUS_TOO_MANY_COMMANDS",0xC00000C1L},
           {"An I/O adapter hardware error has occurred."    ,"STATUS_ADAPTER_HARDWARE_ERROR",0xC00000C2L},
           {"The network responded incorrectly."    ,"STATUS_INVALID_NETWORK_RESPONSE",0xC00000C3L},
           {"An unexpected network error occurred."    ,"STATUS_UNEXPECTED_NETWORK_ERROR",0xC00000C4L},
           {"The remote adapter is not compatible."    ,"STATUS_BAD_REMOTE_ADAPTER",0xC00000C5L},
           {"The printer queue is full."    ,"STATUS_PRINT_QUEUE_FULL",0xC00000C6L},
           {"Space to store the file waiting to be printed is not available on the server."    ,"STATUS_NO_SPOOL_SPACE",0xC00000C7L},
           {"The requested print file has been canceled."    ,"STATUS_PRINT_CANCELLED",0xC00000C8L},
           {"The network name was deleted."    ,"STATUS_NETWORK_NAME_DELETED",0xC00000C9L},
           {"Network access is denied."    ,"STATUS_NETWORK_ACCESS_DENIED",0xC00000CAL},
           {"{Incorrect Network Resource Type}"
"The specified device type (LPT, for example) conflicts with the actual device type on the remote resource."    ,"STATUS_BAD_DEVICE_TYPE",0xC00000CBL},
           {"{Network Name Not Found}"
"The specified share name cannot be found on the remote server."    ,"STATUS_BAD_NETWORK_NAME",0xC00000CCL},
           {"The name limit for the local computer network adapter card was exceeded."    ,"STATUS_TOO_MANY_NAMES",0xC00000CDL},
           {"The network BIOS session limit was exceeded."    ,"STATUS_TOO_MANY_SESSIONS",0xC00000CEL},
           {"File sharing has been temporarily paused."    ,"STATUS_SHARING_PAUSED",0xC00000CFL},
           {"No more connections can be made to this remote computer at this time because there are already as many connections as the computer can accept."    ,"STATUS_REQUEST_NOT_ACCEPTED",0xC00000D0L},
           {"Print or disk redirection is temporarily paused."    ,"STATUS_REDIRECTOR_PAUSED",0xC00000D1L},
           {"A network data fault occurred."    ,"STATUS_NET_WRITE_FAULT",0xC00000D2L},
           {"The number of active profiling objects is at the maximum and no more may be started."    ,"STATUS_PROFILING_AT_LIMIT",0xC00000D3L},
           {"{Incorrect Volume}"
"The target file of a rename request is located on a different device than the source of the rename request."    ,"STATUS_NOT_SAME_DEVICE",0xC00000D4L},
           {"The file specified has been renamed and thus cannot be modified."    ,"STATUS_FILE_RENAMED",0xC00000D5L},
           {"{Network Request Timeout}"
"The session with a remote server has been disconnected because the time-out interval for a request has expired."    ,"STATUS_VIRTUAL_CIRCUIT_CLOSED",0xC00000D6L},
           {"Indicates an attempt was made to operate on the security of an object that does not have security associated with it."    ,"STATUS_NO_SECURITY_ON_OBJECT",0xC00000D7L},
           {"Used to indicate that an operation cannot continue without blocking for I/O."    ,"STATUS_CANT_WAIT",0xC00000D8L},
           {"Used to indicate that a read operation was done on an empty pipe."    ,"STATUS_PIPE_EMPTY",0xC00000D9L},
           {"Configuration information could not be read from the domain controller, either because the machine is unavailable, or access has been denied."    ,"STATUS_CANT_ACCESS_DOMAIN_INFO",0xC00000DAL},
           {"Indicates that a thread attempted to terminate itself by default (called NtTerminateThread with NULL},"    ,"STATUS_CANT_TERMINATE_SELF",0xC00000DBL},
           {"Indicates the Sam Server was in the wrong state to perform the desired operation."    ,"STATUS_INVALID_SERVER_STATE",0xC00000DCL},
           {"Indicates the Domain was in the wrong state to perform the desired operation."    ,"STATUS_INVALID_DOMAIN_STATE",0xC00000DDL},
           {"This operation is only allowed for the Primary Domain Controller of the domain."    ,"STATUS_INVALID_DOMAIN_ROLE",0xC00000DEL},
           {"The specified Domain did not exist."    ,"STATUS_NO_SUCH_DOMAIN",0xC00000DFL},
           {"The specified Domain already exists."    ,"STATUS_DOMAIN_EXISTS",0xC00000E0L},
           {"An attempt was made to exceed the limit on the number of domains per server for this release."    ,"STATUS_DOMAIN_LIMIT_EXCEEDED",0xC00000E1L},
           {"Error status returned when oplock request is denied."    ,"STATUS_OPLOCK_NOT_GRANTED",0xC00000E2L},
           {"Error status returned when an invalid oplock acknowledgment is received by a file system."    ,"STATUS_INVALID_OPLOCK_PROTOCOL",0xC00000E3L},
           {"This error indicates that the requested operation cannot be completed due to a catastrophic media failure or on-disk data structure corruption."    ,"STATUS_INTERNAL_DB_CORRUPTION",0xC00000E4L},
           {"An internal error occurred."    ,"STATUS_INTERNAL_ERROR",0xC00000E5L},
           {"Indicates generic access types were contained in an access mask which should already be mapped to non-generic access types."    ,"STATUS_GENERIC_NOT_MAPPED",0xC00000E6L},
           {"Indicates a security descriptor is not in the necessary format (absolute or self-relative)."    ,"STATUS_BAD_DESCRIPTOR_FORMAT",0xC00000E7L},
           {"An access to a user buffer failed at an \"expected\" point in time."
"This code is defined since the caller does not want to accept STATUS_ACCESS_VIOLATION in its filter."    ,"STATUS_INVALID_USER_BUFFER",0xC00000E8L},
           {"If an I/O error is returned which is not defined in the standard FsRtl filter, it is converted to the following error which is guaranteed to be in the filter."
"In this case information is lost, however, the filter correctly handles the exception."    ,"STATUS_UNEXPECTED_IO_ERROR",0xC00000E9L},
           {"If an MM error is returned which is not defined in the standard FsRtl filter, it is converted to one of the following errors which is guaranteed to be in the filter."
"In this case information is lost, however, the filter correctly handles the exception."    ,"STATUS_UNEXPECTED_MM_CREATE_ERR",0xC00000EAL},
           {"If an MM error is returned which is not defined in the standard FsRtl filter, it is converted to one of the following errors which is guaranteed to be in the filter."
"In this case information is lost, however, the filter correctly handles the exception."    ,"STATUS_UNEXPECTED_MM_MAP_ERROR",0xC00000EBL},
           {"If an MM error is returned which is not defined in the standard FsRtl filter, it is converted to one of the following errors which is guaranteed to be in the filter."
"In this case information is lost, however, the filter correctly handles the exception."    ,"STATUS_UNEXPECTED_MM_EXTEND_ERR",0xC00000ECL},
           {"The requested action is restricted for use by logon processes only. The calling process has not registered as a logon process."    ,"STATUS_NOT_LOGON_PROCESS",0xC00000EDL},
           {"An attempt has been made to start a new session manager or LSA logon session with an ID that is already in use."    ,"STATUS_LOGON_SESSION_EXISTS",0xC00000EEL},
           {"An invalid parameter was passed to a service or function as the first argument."    ,"STATUS_INVALID_PARAMETER_1",0xC00000EFL},
           {"An invalid parameter was passed to a service or function as the second argument."    ,"STATUS_INVALID_PARAMETER_2",0xC00000F0L},
           {"An invalid parameter was passed to a service or function as the third argument."    ,"STATUS_INVALID_PARAMETER_3",0xC00000F1L},
           {"An invalid parameter was passed to a service or function as the fourth argument."    ,"STATUS_INVALID_PARAMETER_4",0xC00000F2L},
           {"An invalid parameter was passed to a service or function as the fifth argument."    ,"STATUS_INVALID_PARAMETER_5",0xC00000F3L},
           {"An invalid parameter was passed to a service or function as the sixth argument."    ,"STATUS_INVALID_PARAMETER_6",0xC00000F4L},
           {"An invalid parameter was passed to a service or function as the seventh argument."    ,"STATUS_INVALID_PARAMETER_7",0xC00000F5L},
           {"An invalid parameter was passed to a service or function as the eighth argument."    ,"STATUS_INVALID_PARAMETER_8",0xC00000F6L},
           {"An invalid parameter was passed to a service or function as the ninth argument."    ,"STATUS_INVALID_PARAMETER_9",0xC00000F7L},
           {"An invalid parameter was passed to a service or function as the tenth argument."    ,"STATUS_INVALID_PARAMETER_10",0xC00000F8L},
           {"An invalid parameter was passed to a service or function as the eleventh argument."    ,"STATUS_INVALID_PARAMETER_11",0xC00000F9L},
           {"An invalid parameter was passed to a service or function as the twelfth argument."    ,"STATUS_INVALID_PARAMETER_12",0xC00000FAL},
           {"An attempt was made to access a network file, but the network software was not yet started."    ,"STATUS_REDIRECTOR_NOT_STARTED",0xC00000FBL},
           {"An attempt was made to start the redirector, but the redirector has already been started."    ,"STATUS_REDIRECTOR_STARTED",0xC00000FCL},
           {"A new guard page for the stack cannot be created."    ,"STATUS_STACK_OVERFLOW",0xC00000FDL},
           {"A specified authentication package is unknown."    ,"STATUS_NO_SUCH_PACKAGE",0xC00000FEL},
           {"A malformed function table was encountered during an unwind operation."    ,"STATUS_BAD_FUNCTION_TABLE",0xC00000FFL},
           {"Indicates the specified environment variable name was not found in the specified environment block."    ,"STATUS_VARIABLE_NOT_FOUND",0xC0000100L},
           {"Indicates that the directory trying to be deleted is not empty."    ,"STATUS_DIRECTORY_NOT_EMPTY",0xC0000101L},
           {"{Corrupt File}"
"The file or directory %hs is corrupt and unreadable."
"Please run the Chkdsk utility."    ,"STATUS_FILE_CORRUPT_ERROR",0xC0000102L},
           {"A requested opened file is not a directory."    ,"STATUS_NOT_A_DIRECTORY",0xC0000103L},
           {"The logon session is not in a state that is consistent with the requested operation."    ,"STATUS_BAD_LOGON_SESSION_STATE",0xC0000104L},
           {"An internal LSA error has occurred. An authentication package has requested the creation of a Logon Session but the ID of an already existing Logon Session has been specified."    ,"STATUS_LOGON_SESSION_COLLISION",0xC0000105L},
           {"A specified name string is too long for its intended use."    ,"STATUS_NAME_TOO_LONG",0xC0000106L},
           {"The user attempted to force close the files on a redirected drive, but there were opened files on the drive, and the user did not specify a sufficient level of force."    ,"STATUS_FILES_OPEN",0xC0000107L},
           {"The user attempted to force close the files on a redirected drive, but there were opened directories on the drive, and the user did not specify a sufficient level of force."    ,"STATUS_CONNECTION_IN_USE",0xC0000108L},
           {"RtlFindMessage could not locate the requested message ID in the message table resource."    ,"STATUS_MESSAGE_NOT_FOUND",0xC0000109L},
           {"An attempt was made to duplicate an object handle into or out of an exiting process."    ,"STATUS_PROCESS_IS_TERMINATING",0xC000010AL},
           {"Indicates an invalid value has been provided for the LogonType requested."    ,"STATUS_INVALID_LOGON_TYPE",0xC000010BL},
           {"Indicates that an attempt was made to assign protection to a file system file or directory and one of the SIDs in the security descriptor could not be translated into a GUID that could be stored by the file system."
"This causes the protection attempt to fail, which may cause a file creation attempt to fail."    ,"STATUS_NO_GUID_TRANSLATION",0xC000010CL},
           {"Indicates that an attempt has been made to impersonate via a named pipe that has not yet been read from."    ,"STATUS_CANNOT_IMPERSONATE",0xC000010DL},
           {"Indicates that the specified image is already loaded."    ,"STATUS_IMAGE_ALREADY_LOADED",0xC000010EL},
           {"STATUS_ABIOS_NOT_PRESENT"    ,"STATUS_ABIOS_NOT_PRESENT",0xC000010FL},
           {"STATUS_ABIOS_LID_NOT_EXIST"    ,"STATUS_ABIOS_LID_NOT_EXIST",0xC0000110L},
           {"STATUS_ABIOS_LID_ALREADY_OWNED"    ,"STATUS_ABIOS_LID_ALREADY_OWNED",0xC0000111L},
           {"STATUS_ABIOS_NOT_LID_OWNER"    ,"STATUS_ABIOS_NOT_LID_OWNER",0xC0000112L},
           {"STATUS_ABIOS_INVALID_COMMAND"    ,"STATUS_ABIOS_INVALID_COMMAND",0xC0000113L},
           {"STATUS_ABIOS_INVALID_LID"    ,"STATUS_ABIOS_INVALID_LID",0xC0000114L},
           {"STATUS_ABIOS_SELECTOR_NOT_AVAILABLE"    ,"STATUS_ABIOS_SELECTOR_NOT_AVAILABLE",0xC0000115L},
           {"STATUS_ABIOS_INVALID_SELECTOR"    ,"STATUS_ABIOS_INVALID_SELECTOR",0xC0000116L},
           {"Indicates that an attempt was made to change the size of the LDT for a process that has no LDT."    ,"STATUS_NO_LDT",0xC0000117L},
           {"Indicates that an attempt was made to grow an LDT by setting its size, or that the size was not an even number of selectors."    ,"STATUS_INVALID_LDT_SIZE",0xC0000118L},
           {"Indicates that the starting value for the LDT information was not an integral multiple of the selector size."    ,"STATUS_INVALID_LDT_OFFSET",0xC0000119L},
           {"Indicates that the user supplied an invalid descriptor when trying to set up Ldt descriptors."    ,"STATUS_INVALID_LDT_DESCRIPTOR",0xC000011AL},
           {"The specified image file did not have the correct format. It appears to be NE format."    ,"STATUS_INVALID_IMAGE_NE_FORMAT",0xC000011BL},
           {"Indicates that the transaction state of a registry sub-tree is incompatible with the requested operation."
"For example, a request has been made to start a new transaction with one already in progress,"
"or a request has been made to apply a transaction when one is not currently in progress."    ,"STATUS_RXACT_INVALID_STATE",0xC000011CL},
           {"Indicates an error has occurred during a registry transaction commit."
"The database has been left in an unknown, but probably inconsistent, state."
"The state of the registry transaction is left as COMMITTING."    ,"STATUS_RXACT_COMMIT_FAILURE",0xC000011DL},
           {"An attempt was made to map a file of size zero with the maximum size specified as zero."    ,"STATUS_MAPPED_FILE_SIZE_ZERO",0xC000011EL},
           {"Too many files are opened on a remote server."
"This error should only be returned by the Windows redirector on a remote drive."    ,"STATUS_TOO_MANY_OPENED_FILES",0xC000011FL},
           {"The I/O request was canceled."    ,"STATUS_CANCELLED",0xC0000120L},
           {"An attempt has been made to remove a file or directory that cannot be deleted."    ,"STATUS_CANNOT_DELETE",0xC0000121L},
           {"Indicates a name specified as a remote computer name is syntactically invalid."    ,"STATUS_INVALID_COMPUTER_NAME",0xC0000122L},
           {"An I/O request other than close was performed on a file after it has been deleted,"
"which can only happen to a request which did not complete before the last handle was closed via NtClose."    ,"STATUS_FILE_DELETED",0xC0000123L},
           {"Indicates an operation has been attempted on a built-in (speciaL},"
"For example, built-in accounts cannot be deleted."    ,"STATUS_SPECIAL_ACCOUNT",0xC0000124L},
           {"The operation requested may not be performed on the specified group because it is a built-in special group."    ,"STATUS_SPECIAL_GROUP",0xC0000125L},
           {"The operation requested may not be performed on the specified user because it is a built-in special user."    ,"STATUS_SPECIAL_USER",0xC0000126L},
           {"Indicates a member cannot be removed from a group because the group is currently the member's primary group."    ,"STATUS_MEMBERS_PRIMARY_GROUP",0xC0000127L},
           {"An I/O request other than close and several other special case operations was attempted using a file object that had already been closed."    ,"STATUS_FILE_CLOSED",0xC0000128L},
           {"Indicates a process has too many threads to perform the requested action. For example, assignment of a primary token may only be performed when a process has zero or one threads."    ,"STATUS_TOO_MANY_THREADS",0xC0000129L},
           {"An attempt was made to operate on a thread within a specific process, but the thread specified is not in the process specified."    ,"STATUS_THREAD_NOT_IN_PROCESS",0xC000012AL},
           {"An attempt was made to establish a token for use as a primary token but the token is already in use. A token can only be the primary token of one process at a time."    ,"STATUS_TOKEN_ALREADY_IN_USE",0xC000012BL},
           {"Page file quota was exceeded."    ,"STATUS_PAGEFILE_QUOTA_EXCEEDED",0xC000012CL},
           {"{Out of Virtual Memory}"
"Your system is low on virtual memory. To ensure that Windows runs properly, increase the size of your virtual memory paging file. For more information, see Help."    ,"STATUS_COMMITMENT_LIMIT",0xC000012DL},
           {"The specified image file did not have the correct format, it appears to be LE format."    ,"STATUS_INVALID_IMAGE_LE_FORMAT",0xC000012EL},
           {"The specified image file did not have the correct format, it did not have an initial MZ."    ,"STATUS_INVALID_IMAGE_NOT_MZ",0xC000012FL},
           {"The specified image file did not have the correct format, it did not have a proper e_lfarlc in the MZ header."    ,"STATUS_INVALID_IMAGE_PROTECT",0xC0000130L},
           {"The specified image file did not have the correct format, it appears to be a 16-bit Windows image."    ,"STATUS_INVALID_IMAGE_WIN_16",0xC0000131L},
           {"The Netlogon service cannot start because another Netlogon service running in the domain conflicts with the specified role."    ,"STATUS_LOGON_SERVER_CONFLICT",0xC0000132L},
           {"The time at the Primary Domain Controller is different than the time at the Backup Domain Controller or member server by too large an amount."    ,"STATUS_TIME_DIFFERENCE_AT_DC",0xC0000133L},
           {"The SAM database on a Windows Server is significantly out of synchronization with the copy on the Domain Controller. A complete synchronization is required."    ,"STATUS_SYNCHRONIZATION_REQUIRED",0xC0000134L},
           {"{Unable To Locate Component}"
"This application has failed to start because %hs was not found. Re-installing the application may fix this problem."    ,"STATUS_DLL_NOT_FOUND",0xC0000135L},
           {"The NtCreateFile API failed. This error should never be returned to an application, it is a place holder for the Windows Lan Manager Redirector to use in its internal error mapping routines."    ,"STATUS_OPEN_FAILED",0xC0000136L},
           {"{Privilege Failed}"
"The I/O permissions for the process could not be changed."    ,"STATUS_IO_PRIVILEGE_FAILED",0xC0000137L},
           {"{Ordinal Not Found}"
"The ordinal %ld could not be located in the dynamic link library %hs."    ,"STATUS_ORDINAL_NOT_FOUND",0xC0000138L},
           {"{Entry Point Not Found}"
"The procedure entry point %hs could not be located in the dynamic link library %hs."    ,"STATUS_ENTRYPOINT_NOT_FOUND",0xC0000139L},
           {"{Application Exit by CTRL+C}"
"The application terminated as a result of a CTRL+C."    ,"STATUS_CONTROL_C_EXIT",0xC000013AL},
           {"{Virtual Circuit Closed}"
"The network transport on your computer has closed a network connection. There may or may not be I/O requests outstanding."    ,"STATUS_LOCAL_DISCONNECT",0xC000013BL},
           {"{Virtual Circuit Closed}"
"The network transport on a remote computer has closed a network connection. There may or may not be I/O requests outstanding."    ,"STATUS_REMOTE_DISCONNECT",0xC000013CL},
           {"{Insufficient Resources on Remote Computer}"
"The remote computer has insufficient resources to complete the network request. For instance, there may not be enough memory available on the remote computer to carry out the request at this time."    ,"STATUS_REMOTE_RESOURCES",0xC000013DL},
           {"{Virtual Circuit Closed}"
"An existing connection (virtual circuit) has been broken at the remote computer. There is probably something wrong with the network software protocol or the network hardware on the remote computer."    ,"STATUS_LINK_FAILED",0xC000013EL},
           {"{Virtual Circuit Closed}"
"The network transport on your computer has closed a network connection because it had to wait too long for a response from the remote computer."    ,"STATUS_LINK_TIMEOUT",0xC000013FL},
           {"The connection handle given to the transport was invalid."    ,"STATUS_INVALID_CONNECTION",0xC0000140L},
           {"The address handle given to the transport was invalid."    ,"STATUS_INVALID_ADDRESS",0xC0000141L},
           {"{DLL Initialization Failed}"
"Initialization of the dynamic link library %hs failed. The process is terminating abnormally."    ,"STATUS_DLL_INIT_FAILED",0xC0000142L},
           {"{Missing System File}"
"The required system file %hs is bad or missing."    ,"STATUS_MISSING_SYSTEMFILE",0xC0000143L},
           {"{Application Error}"
"The exception %s (0x%08lx) occurred in the application at location 0x%08lx."    ,"STATUS_UNHANDLED_EXCEPTION",0xC0000144L},
           {"{Application Error}"
"The application failed to initialize properly (0x%lx). Click on OK to terminate the application."    ,"STATUS_APP_INIT_FAILURE",0xC0000145L},
           {"{Unable to Create Paging File}"
"The creation of the paging file %hs failed (%lx). The requested size was %ld."    ,"STATUS_PAGEFILE_CREATE_FAILED",0xC0000146L},
           {"{No Paging File Specified}"
"No paging file was specified in the system configuration."    ,"STATUS_NO_PAGEFILE",0xC0000147L},
           {"{Incorrect System Call Level}"
"An invalid level was passed into the specified system call."    ,"STATUS_INVALID_LEVEL",0xC0000148L},
           {"{Incorrect Password to LAN Manager Server}"
"You specified an incorrect password to a LAN Manager 2.x or MS-NET server."    ,"STATUS_WRONG_PASSWORD_CORE",0xC0000149L},
           {"{EXCEPTION}"
"A real-mode application issued a floating-point instruction and floating-point hardware is not present."    ,"STATUS_ILLEGAL_FLOAT_CONTEXT",0xC000014AL},
           {"The pipe operation has failed because the other end of the pipe has been closed."    ,"STATUS_PIPE_BROKEN",0xC000014BL},
           {"{The Registry Is Corrupt}"
"The structure of one of the files that contains Registry data is corrupt, or the image of the file in memory is corrupt, or the file could not be recovered because the alternate copy or log was absent or corrupt."    ,"STATUS_REGISTRY_CORRUPT",0xC000014CL},
           {"An I/O operation initiated by the Registry failed unrecoverably."
"The Registry could not read in, or write out, or flush, one of the files that contain the system's image of the Registry."    ,"STATUS_REGISTRY_IO_FAILED",0xC000014DL},
           {"An event pair synchronization operation was performed using the thread specific client/server event pair object, but no event pair object was associated with the thread."    ,"STATUS_NO_EVENT_PAIR",0xC000014EL},
           {"The volume does not contain a recognized file system."
"Please make sure that all required file system drivers are loaded and that the volume is not corrupt."    ,"STATUS_UNRECOGNIZED_VOLUME",0xC000014FL},
           {"No serial device was successfully initialized. The serial driver will unload."    ,"STATUS_SERIAL_NO_DEVICE_INITED",0xC0000150L},
           {"The specified local group does not exist."    ,"STATUS_NO_SUCH_ALIAS",0xC0000151L},
           {"The specified account name is not a member of the local group."    ,"STATUS_MEMBER_NOT_IN_ALIAS",0xC0000152L},
           {"The specified account name is already a member of the local group."    ,"STATUS_MEMBER_IN_ALIAS",0xC0000153L},
           {"The specified local group already exists."    ,"STATUS_ALIAS_EXISTS",0xC0000154L},
           {"A requested type of logon (e.g., Interactive, Network, Service) is not granted by the target system's local security policy."
"Please ask the system administrator to grant the necessary form of logon."    ,"STATUS_LOGON_NOT_GRANTED",0xC0000155L},
           {"The maximum number of secrets that may be stored in a single system has been exceeded. The length and number of secrets is limited to satisfy United States State Department export restrictions."    ,"STATUS_TOO_MANY_SECRETS",0xC0000156L},
           {"The length of a secret exceeds the maximum length allowed. The length and number of secrets is limited to satisfy United States State Department export restrictions."    ,"STATUS_SECRET_TOO_LONG",0xC0000157L},
           {"The Local Security Authority (LSA) database contains an internal inconsistency."    ,"STATUS_INTERNAL_DB_ERROR",0xC0000158L},
           {"The requested operation cannot be performed in fullscreen mode."    ,"STATUS_FULLSCREEN_MODE",0xC0000159L},
           {"During a logon attempt, the user's security context accumulated too many security IDs. This is a very unusual situation."
"Remove the user from some global or local groups to reduce the number of security ids to incorporate into the security context."    ,"STATUS_TOO_MANY_CONTEXT_IDS",0xC000015AL},
           {"A user has requested a type of logon (e.g., interactive or network) that has not been granted. An administrator has control over who may logon interactively and through the network."    ,"STATUS_LOGON_TYPE_NOT_GRANTED",0xC000015BL},
           {"The system has attempted to load or restore a file into the registry, and the specified file is not in the format of a registry file."    ,"STATUS_NOT_REGISTRY_FILE",0xC000015CL},
           {"An attempt was made to change a user password in the security account manager without providing the necessary Windows cross-encrypted password."    ,"STATUS_NT_CROSS_ENCRYPTION_REQUIRED",0xC000015DL},
           {"A Windows Server has an incorrect configuration."    ,"STATUS_DOMAIN_CTRLR_CONFIG_ERROR",0xC000015EL},
           {"An attempt was made to explicitly access the secondary copy of information via a device control to the Fault Tolerance driver and the secondary copy is not present in the system."    ,"STATUS_FT_MISSING_MEMBER",0xC000015FL},
           {"A configuration registry node representing a driver service entry was ill-formed and did not contain required value entries."    ,"STATUS_ILL_FORMED_SERVICE_ENTRY",0xC0000160L},
           {"An illegal character was encountered. For a multi-byte character set this includes a lead byte without a succeeding trail byte. For the Unicode character set this includes the characters 0xFFFF and 0xFFFE."    ,"STATUS_ILLEGAL_CHARACTER",0xC0000161L},
           {"No mapping for the Unicode character exists in the target multi-byte code page."    ,"STATUS_UNMAPPABLE_CHARACTER",0xC0000162L},
           {"The Unicode character is not defined in the Unicode character set installed on the system."    ,"STATUS_UNDEFINED_CHARACTER",0xC0000163L},
           {"The paging file cannot be created on a floppy diskette."    ,"STATUS_FLOPPY_VOLUME",0xC0000164L},
           {"{Floppy Disk Error}"
"While accessing a floppy disk, an ID address mark was not found."    ,"STATUS_FLOPPY_ID_MARK_NOT_FOUND",0xC0000165L},
           {"{Floppy Disk Error}"
"While accessing a floppy disk, the track address from the sector ID field was found to be different than the track address maintained by the controller."    ,"STATUS_FLOPPY_WRONG_CYLINDER",0xC0000166L},
           {"{Floppy Disk Error}"
"The floppy disk controller reported an error that is not recognized by the floppy disk driver."    ,"STATUS_FLOPPY_UNKNOWN_ERROR",0xC0000167L},
           {"{Floppy Disk Error}"
"While accessing a floppy-disk, the controller returned inconsistent results via its registers."    ,"STATUS_FLOPPY_BAD_REGISTERS",0xC0000168L},
           {"{Hard Disk Error}"
"While accessing the hard disk, a recalibrate operation failed, even after retries."    ,"STATUS_DISK_RECALIBRATE_FAILED",0xC0000169L},
           {"{Hard Disk Error}"
"While accessing the hard disk, a disk operation failed even after retries."    ,"STATUS_DISK_OPERATION_FAILED",0xC000016AL},
           {"{Hard Disk Error}"
"While accessing the hard disk, a disk controller reset was needed, but even that failed."    ,"STATUS_DISK_RESET_FAILED",0xC000016BL},
           {"An attempt was made to open a device that was sharing an IRQ with other devices."
"At least one other device that uses that IRQ was already opened."
"Two concurrent opens of devices that share an IRQ and only work via interrupts is not supported for the particular bus type that the devices use."    ,"STATUS_SHARED_IRQ_BUSY",0xC000016CL},
           {"{FT Orphaning}"
"A disk that is part of a fault-tolerant volume can no longer be accessed."    ,"STATUS_FT_ORPHANING",0xC000016DL},
           {"The system bios failed to connect a system interrupt to the device or bus for"
"which the device is connected."    ,"STATUS_BIOS_FAILED_TO_CONNECT_INTERRUPT",0xC000016EL},
           {"Tape could not be partitioned."    ,"STATUS_PARTITION_FAILURE",0xC0000172L},
           {"When accessing a new tape of a multivolume partition, the current blocksize is incorrect."    ,"STATUS_INVALID_BLOCK_LENGTH",0xC0000173L},
           {"Tape partition information could not be found when loading a tape."    ,"STATUS_DEVICE_NOT_PARTITIONED",0xC0000174L},
           {"Attempt to lock the eject media mechanism fails."    ,"STATUS_UNABLE_TO_LOCK_MEDIA",0xC0000175L},
           {"Unload media fails."    ,"STATUS_UNABLE_TO_UNLOAD_MEDIA",0xC0000176L},
           {"Physical end of tape was detected."    ,"STATUS_EOM_OVERFLOW",0xC0000177L},
           {"{No Media}"
"There is no media in the drive."
"Please insert media into drive %hs."    ,"STATUS_NO_MEDIA",0xC0000178L},
           {"A member could not be added to or removed from the local group because the member does not exist."    ,"STATUS_NO_SUCH_MEMBER",0xC000017AL},
           {"A new member could not be added to a local group because the member has the wrong account type."    ,"STATUS_INVALID_MEMBER",0xC000017BL},
           {"Illegal operation attempted on a registry key which has been marked for deletion."    ,"STATUS_KEY_DELETED",0xC000017CL},
           {"System could not allocate required space in a registry log."    ,"STATUS_NO_LOG_SPACE",0xC000017DL},
           {"Too many Sids have been specified."    ,"STATUS_TOO_MANY_SIDS",0xC000017EL},
           {"An attempt was made to change a user password in the security account manager without providing the necessary LM cross-encrypted password."    ,"STATUS_LM_CROSS_ENCRYPTION_REQUIRED",0xC000017FL},
           {"An attempt was made to create a symbolic link in a registry key that already has subkeys or values."    ,"STATUS_KEY_HAS_CHILDREN",0xC0000180L},
           {"An attempt was made to create a Stable subkey under a Volatile parent key."    ,"STATUS_CHILD_MUST_BE_VOLATILE",0xC0000181L},
           {"The I/O device is configured incorrectly or the configuration parameters to the driver are incorrect."    ,"STATUS_DEVICE_CONFIGURATION_ERROR",0xC0000182L},
           {"An error was detected between two drivers or within an I/O driver."    ,"STATUS_DRIVER_INTERNAL_ERROR",0xC0000183L},
           {"The device is not in a valid state to perform this request."    ,"STATUS_INVALID_DEVICE_STATE",0xC0000184L},
           {"The I/O device reported an I/O error."    ,"STATUS_IO_DEVICE_ERROR",0xC0000185L},
           {"A protocol error was detected between the driver and the device."    ,"STATUS_DEVICE_PROTOCOL_ERROR",0xC0000186L},
           {"This operation is only allowed for the Primary Domain Controller of the domain."    ,"STATUS_BACKUP_CONTROLLER",0xC0000187L},
           {"Log file space is insufficient to support this operation."    ,"STATUS_LOG_FILE_FULL",0xC0000188L},
           {"A write operation was attempted to a volume after it was dismounted."    ,"STATUS_TOO_LATE",0xC0000189L},
           {"The workstation does not have a trust secret for the primary domain in the local LSA database."    ,"STATUS_NO_TRUST_LSA_SECRET",0xC000018AL},
           {"The SAM database on the Windows Server does not have a computer account for this workstation trust relationship."    ,"STATUS_NO_TRUST_SAM_ACCOUNT",0xC000018BL},
           {"The logon request failed because the trust relationship between the primary domain and the trusted domain failed."    ,"STATUS_TRUSTED_DOMAIN_FAILURE",0xC000018CL},
           {"The logon request failed because the trust relationship between this workstation and the primary domain failed."    ,"STATUS_TRUSTED_RELATIONSHIP_FAILURE",0xC000018DL},
           {"The Eventlog log file is corrupt."    ,"STATUS_EVENTLOG_FILE_CORRUPT",0xC000018EL},
           {"No Eventlog log file could be opened. The Eventlog service did not start."    ,"STATUS_EVENTLOG_CANT_START",0xC000018FL},
           {"The network logon failed. This may be because the validation authority can't be reached."    ,"STATUS_TRUST_FAILURE",0xC0000190L},
           {"An attempt was made to acquire a mutant such that its maximum count would have been exceeded."    ,"STATUS_MUTANT_LIMIT_EXCEEDED",0xC0000191L},
           {"An attempt was made to logon, but the netlogon service was not started."    ,"STATUS_NETLOGON_NOT_STARTED",0xC0000192L},
           {"The user's account has expired."    ,"STATUS_ACCOUNT_EXPIRED",0xC0000193L},
           {"{EXCEPTION}"
"Possible deadlock condition."    ,"STATUS_POSSIBLE_DEADLOCK",0xC0000194L},
           {"Multiple connections to a server or shared resource by the same user, using more than one user name, are not allowed. Disconnect all previous connections to the server or shared resource and try again."    ,"STATUS_NETWORK_CREDENTIAL_CONFLICT",0xC0000195L},
           {"An attempt was made to establish a session to a network server, but there are already too many sessions established to that server."    ,"STATUS_REMOTE_SESSION_LIMIT",0xC0000196L},
           {"The log file has changed between reads."    ,"STATUS_EVENTLOG_FILE_CHANGED",0xC0000197L},
           {"The account used is an Interdomain Trust account. Use your global user account or local user account to access this server."    ,"STATUS_NOLOGON_INTERDOMAIN_TRUST_ACCOUNT",0xC0000198L},
           {"The account used is a Computer Account. Use your global user account or local user account to access this server."    ,"STATUS_NOLOGON_WORKSTATION_TRUST_ACCOUNT",0xC0000199L},
           {"The account used is an Server Trust account. Use your global user account or local user account to access this server."    ,"STATUS_NOLOGON_SERVER_TRUST_ACCOUNT",0xC000019AL},
           {"The name or SID of the domain specified is inconsistent with the trust information for that domain."    ,"STATUS_DOMAIN_TRUST_INCONSISTENT",0xC000019BL},
           {"A volume has been accessed for which a file system driver is required that has not yet been loaded."    ,"STATUS_FS_DRIVER_REQUIRED",0xC000019CL},
           {"There is no user session key for the specified logon session."    ,"STATUS_NO_USER_SESSION_KEY",0xC0000202L},
           {"The remote user session has been deleted."    ,"STATUS_USER_SESSION_DELETED",0xC0000203L},
           {"Indicates the specified resource language ID cannot be found in the"
"image file."    ,"STATUS_RESOURCE_LANG_NOT_FOUND",0xC0000204L},
           {"Insufficient server resources exist to complete the request."    ,"STATUS_INSUFF_SERVER_RESOURCES",0xC0000205L},
           {"The size of the buffer is invalid for the specified operation."    ,"STATUS_INVALID_BUFFER_SIZE",0xC0000206L},
           {"The transport rejected the network address specified as invalid."    ,"STATUS_INVALID_ADDRESS_COMPONENT",0xC0000207L},
           {"The transport rejected the network address specified due to an invalid use of a wildcard."    ,"STATUS_INVALID_ADDRESS_WILDCARD",0xC0000208L},
           {"The transport address could not be opened because all the available addresses are in use."    ,"STATUS_TOO_MANY_ADDRESSES",0xC0000209L},
           {"The transport address could not be opened because it already exists."    ,"STATUS_ADDRESS_ALREADY_EXISTS",0xC000020AL},
           {"The transport address is now closed."    ,"STATUS_ADDRESS_CLOSED",0xC000020BL},
           {"The transport connection is now disconnected."    ,"STATUS_CONNECTION_DISCONNECTED",0xC000020CL},
           {"The transport connection has been reset."    ,"STATUS_CONNECTION_RESET",0xC000020DL},
           {"The transport cannot dynamically acquire any more nodes."    ,"STATUS_TOO_MANY_NODES",0xC000020EL},
           {"The transport aborted a pending transaction."    ,"STATUS_TRANSACTION_ABORTED",0xC000020FL},
           {"The transport timed out a request waiting for a response."    ,"STATUS_TRANSACTION_TIMED_OUT",0xC0000210L},
           {"The transport did not receive a release for a pending response."    ,"STATUS_TRANSACTION_NO_RELEASE",0xC0000211L},
           {"The transport did not find a transaction matching the specific"
"token."    ,"STATUS_TRANSACTION_NO_MATCH",0xC0000212L},
           {"The transport had previously responded to a transaction request."    ,"STATUS_TRANSACTION_RESPONDED",0xC0000213L},
           {"The transport does not recognized the transaction request identifier specified."    ,"STATUS_TRANSACTION_INVALID_ID",0xC0000214L},
           {"The transport does not recognize the transaction request type specified."    ,"STATUS_TRANSACTION_INVALID_TYPE",0xC0000215L},
           {"The transport can only process the specified request on the server side of a session."    ,"STATUS_NOT_SERVER_SESSION",0xC0000216L},
           {"The transport can only process the specified request on the client side of a session."    ,"STATUS_NOT_CLIENT_SESSION",0xC0000217L},
           {"{Registry File Failure}"
"The registry cannot load the hive (file):"
"%hs"
"or its log or alternate."
"It is corrupt, absent, or not writable."    ,"STATUS_CANNOT_LOAD_REGISTRY_FILE",0xC0000218L},
           {"{Unexpected Failure in DebugActiveProcess}"
"An unexpected failure occurred while processing a DebugActiveProcess API request. You may choose OK to terminate the process, or Cancel to ignore the error."    ,"STATUS_DEBUG_ATTACH_FAILED",0xC0000219L},
           {"{Fatal System Error}"
"The %hs system process terminated unexpectedly with a status of 0x%08x (0x%08x 0x%08x)."
"The system has been shut down."    ,"STATUS_SYSTEM_PROCESS_TERMINATED",0xC000021AL},
           {"{Data Not Accepted}"
"The TDI client could not handle the data received during an indication."    ,"STATUS_DATA_NOT_ACCEPTED",0xC000021BL},
           {"{Unable to Retrieve Browser Server List}"
"The list of servers for this workgroup is not currently available."    ,"STATUS_NO_BROWSER_SERVERS_FOUND",0xC000021CL},
           {"NTVDM encountered a hard error."    ,"STATUS_VDM_HARD_ERROR",0xC000021DL},
           {"{Cancel Timeout}"
"The driver %hs failed to complete a cancelled I/O request in the allotted time."    ,"STATUS_DRIVER_CANCEL_TIMEOUT",0xC000021EL},
           {"{Reply Message Mismatch}"
"An attempt was made to reply to an LPC message, but the thread specified by the client ID in the message was not waiting on that message."    ,"STATUS_REPLY_MESSAGE_MISMATCH",0xC000021FL},
           {"{Mapped View Alignment Incorrect}"
"An attempt was made to map a view of a file, but either the specified base address or the offset into the file were not aligned on the proper allocation granularity."    ,"STATUS_MAPPED_ALIGNMENT",0xC0000220L},
           {"{Bad Image Checksum}"
"The image %hs is possibly corrupt. The header checksum does not match the computed checksum."    ,"STATUS_IMAGE_CHECKSUM_MISMATCH",0xC0000221L},
           {"{Delayed Write Failed}"
"Windows was unable to save all the data for the file %hs. The data has been lost."
"This error may be caused by a failure of your computer hardware or network connection. Please try to save this file elsewhere."    ,"STATUS_LOST_WRITEBEHIND_DATA",0xC0000222L},
           {"The parameter(s) passed to the server in the client/server shared memory window were invalid. Too much data may have been put in the shared memory window."    ,"STATUS_CLIENT_SERVER_PARAMETERS_INVALID",0xC0000223L},
           {"The user's password must be changed before logging on the first time."    ,"STATUS_PASSWORD_MUST_CHANGE",0xC0000224L},
           {"The object was not found."    ,"STATUS_NOT_FOUND",0xC0000225L},
           {"The stream is not a tiny stream."    ,"STATUS_NOT_TINY_STREAM",0xC0000226L},
           {"A transaction recover failed."    ,"STATUS_RECOVERY_FAILURE",0xC0000227L},
           {"The request must be handled by the stack overflow code."    ,"STATUS_STACK_OVERFLOW_READ",0xC0000228L},
           {"A consistency check failed."    ,"STATUS_FAIL_CHECK",0xC0000229L},
           {"The attempt to insert the ID in the index failed because the ID is already in the index."    ,"STATUS_DUPLICATE_OBJECTID",0xC000022AL},
           {"The attempt to set the object's ID failed because the object already has an ID."    ,"STATUS_OBJECTID_EXISTS",0xC000022BL},
           {"Internal OFS status codes indicating how an allocation operation is handled. Either it is retried after the containing onode is moved or the extent stream is converted to a large stream."    ,"STATUS_CONVERT_TO_LARGE",0xC000022CL},
           {"The request needs to be retried."    ,"STATUS_RETRY",0xC000022DL},
           {"The attempt to find the object found an object matching by ID on the volume but it is out of the scope of the handle used for the operation."    ,"STATUS_FOUND_OUT_OF_SCOPE",0xC000022EL},
           {"The bucket array must be grown. Retry transaction after doing so."    ,"STATUS_ALLOCATE_BUCKET",0xC000022FL},
           {"The property set specified does not exist on the object."    ,"STATUS_PROPSET_NOT_FOUND",0xC0000230L},
           {"The user/kernel marshalling buffer has overflowed."    ,"STATUS_MARSHALL_OVERFLOW",0xC0000231L},
           {"The supplied variant structure contains invalid data."    ,"STATUS_INVALID_VARIANT",0xC0000232L},
           {"Could not find a domain controller for this domain."    ,"STATUS_DOMAIN_CONTROLLER_NOT_FOUND",0xC0000233L},
           {"The user account has been automatically locked because too many invalid logon attempts or password change attempts have been requested."    ,"STATUS_ACCOUNT_LOCKED_OUT",0xC0000234L},
           {"NtClose was called on a handle that was protected from close via NtSetInformationObject."    ,"STATUS_HANDLE_NOT_CLOSABLE",0xC0000235L},
           {"The transport connection attempt was refused by the remote system."    ,"STATUS_CONNECTION_REFUSED",0xC0000236L},
           {"The transport connection was gracefully closed."    ,"STATUS_GRACEFUL_DISCONNECT",0xC0000237L},
           {"The transport endpoint already has an address associated with it."    ,"STATUS_ADDRESS_ALREADY_ASSOCIATED",0xC0000238L},
           {"An address has not yet been associated with the transport endpoint."    ,"STATUS_ADDRESS_NOT_ASSOCIATED",0xC0000239L},
           {"An operation was attempted on a nonexistent transport connection."    ,"STATUS_CONNECTION_INVALID",0xC000023AL},
           {"An invalid operation was attempted on an active transport connection."    ,"STATUS_CONNECTION_ACTIVE",0xC000023BL},
           {"The remote network is not reachable by the transport."    ,"STATUS_NETWORK_UNREACHABLE",0xC000023CL},
           {"The remote system is not reachable by the transport."    ,"STATUS_HOST_UNREACHABLE",0xC000023DL},
           {"The remote system does not support the transport protocol."    ,"STATUS_PROTOCOL_UNREACHABLE",0xC000023EL},
           {"No service is operating at the destination port of the transport on the remote system."    ,"STATUS_PORT_UNREACHABLE",0xC000023FL},
           {"The request was aborted."    ,"STATUS_REQUEST_ABORTED",0xC0000240L},
           {"The transport connection was aborted by the local system."    ,"STATUS_CONNECTION_ABORTED",0xC0000241L},
           {"The specified buffer contains ill-formed data."    ,"STATUS_BAD_COMPRESSION_BUFFER",0xC0000242L},
           {"The requested operation cannot be performed on a file with a user mapped section open."    ,"STATUS_USER_MAPPED_FILE",0xC0000243L},
           {"{Audit Failed}"
"An attempt to generate a security audit failed."    ,"STATUS_AUDIT_FAILED",0xC0000244L},
           {"The timer resolution was not previously set by the current process."    ,"STATUS_TIMER_RESOLUTION_NOT_SET",0xC0000245L},
           {"A connection to the server could not be made because the limit on the number of concurrent connections for this account has been reached."    ,"STATUS_CONNECTION_COUNT_LIMIT",0xC0000246L},
           {"Attempting to login during an unauthorized time of day for this account."    ,"STATUS_LOGIN_TIME_RESTRICTION",0xC0000247L},
           {"The account is not authorized to login from this station."    ,"STATUS_LOGIN_WKSTA_RESTRICTION",0xC0000248L},
           {"{UP/MP Image Mismatch}"
"The image %hs has been modified for use on a uniprocessor system, but you are running it on a multiprocessor machine."
"Please reinstall the image file."    ,"STATUS_IMAGE_MP_UP_MISMATCH",0xC0000249L},
           {"There is insufficient account information to log you on."    ,"STATUS_INSUFFICIENT_LOGON_INFO",0xC0000250L},
           {"{Invalid DLL Entrypoint}"
"The dynamic link library %hs is not written correctly. The stack pointer has been left in an inconsistent state."
"The entrypoint should be declared as WINAPI or STDCALL. Select YES to fail the DLL load. Select NO to continue execution. Selecting NO may cause the application to operate incorrectly."    ,"STATUS_BAD_DLL_ENTRYPOINT",0xC0000251L},
           {"{Invalid Service Callback Entrypoint}"
"The %hs service is not written correctly. The stack pointer has been left in an inconsistent state."
"The callback entrypoint should be declared as WINAPI or STDCALL. Selecting OK will cause the service to continue operation. However, the service process may operate incorrectly."    ,"STATUS_BAD_SERVICE_ENTRYPOINT",0xC0000252L},
           {"The server received the messages but did not send a reply."    ,"STATUS_LPC_REPLY_LOST",0xC0000253L},
           {"There is an IP address conflict with another system on the network"    ,"STATUS_IP_ADDRESS_CONFLICT1",0xC0000254L},
           {"There is an IP address conflict with another system on the network"    ,"STATUS_IP_ADDRESS_CONFLICT2",0xC0000255L},
           {"{Low On Registry Space}"
"The system has reached the maximum size allowed for the system part of the registry.  Additional storage requests will be ignored."    ,"STATUS_REGISTRY_QUOTA_LIMIT",0xC0000256L},
           {"The contacted server does not support the indicated part of the DFS namespace."    ,"STATUS_PATH_NOT_COVERED",0xC0000257L},
           {"A callback return system service cannot be executed when no callback is active."    ,"STATUS_NO_CALLBACK_ACTIVE",0xC0000258L},
           {"The service being accessed is licensed for a particular number of connections."
"No more connections can be made to the service at this time because there are already as many connections as the service can accept."    ,"STATUS_LICENSE_QUOTA_EXCEEDED",0xC0000259L},
           {"The password provided is too short to meet the policy of your user account."
"Please choose a longer password."    ,"STATUS_PWD_TOO_SHORT",0xC000025AL},
           {"The policy of your user account does not allow you to change passwords too frequently."
"This is done to prevent users from changing back to a familiar, but potentially discovered, password."
"If you feel your password has been compromised then please contact your administrator immediately to have a new one assigned."    ,"STATUS_PWD_TOO_RECENT",0xC000025BL},
           {"You have attempted to change your password to one that you have used in the past."
"The policy of your user account does not allow this. Please select a password that you have not previously used."    ,"STATUS_PWD_HISTORY_CONFLICT",0xC000025CL},
           {"You have attempted to load a legacy device driver while its device instance had been disabled."    ,"STATUS_PLUGPLAY_NO_DEVICE",0xC000025EL},
           {"The specified compression format is unsupported."    ,"STATUS_UNSUPPORTED_COMPRESSION",0xC000025FL},
           {"The specified hardware profile configuration is invalid."    ,"STATUS_INVALID_HW_PROFILE",0xC0000260L},
           {"The specified Plug and Play registry device path is invalid."    ,"STATUS_INVALID_PLUGPLAY_DEVICE_PATH",0xC0000261L},
           {"{Driver Entry Point Not Found}"
"The %hs device driver could not locate the ordinal %ld in driver %hs."    ,"STATUS_DRIVER_ORDINAL_NOT_FOUND",0xC0000262L},
           {"{Driver Entry Point Not Found}"
"The %hs device driver could not locate the entry point %hs in driver %hs."    ,"STATUS_DRIVER_ENTRYPOINT_NOT_FOUND",0xC0000263L},
           {"{Application Error}"
"The application attempted to release a resource it did not own. Click on OK to terminate the application."    ,"STATUS_RESOURCE_NOT_OWNED",0xC0000264L},
           {"An attempt was made to create more links on a file than the file system supports."    ,"STATUS_TOO_MANY_LINKS",0xC0000265L},
           {"The specified quota list is internally inconsistent with its descriptor."    ,"STATUS_QUOTA_LIST_INCONSISTENT",0xC0000266L},
           {"The specified file has been relocated to offline storage."    ,"STATUS_FILE_IS_OFFLINE",0xC0000267L},
           {"{Windows Evaluation Notification}"
"The evaluation period for this installation of Windows has expired. This system will shutdown in 1 hour. To restore access to this installation of Windows, please upgrade this installation using a licensed distribution of this product."    ,"STATUS_EVALUATION_EXPIRATION",0xC0000268L},
           {"{Illegal System DLL Relocation}"
"The system DLL %hs was relocated in memory. The application will not run properly."
"The relocation occurred because the DLL %hs occupied an address range reserved for Windows system DLLs. The vendor supplying the DLL should be contacted for a new DLL."    ,"STATUS_ILLEGAL_DLL_RELOCATION",0xC0000269L},
           {"{License Violation}"
"The system has detected tampering with your registered product type. This is a violation of your software license. Tampering with product type is not permitted."    ,"STATUS_LICENSE_VIOLATION",0xC000026AL},
           {"{DLL Initialization Failed}"
"The application failed to initialize because the window station is shutting down."    ,"STATUS_DLL_INIT_FAILED_LOGOFF",0xC000026BL},
           {"{Unable to Load Device Driver}"
"%hs device driver could not be loaded."
"Error Status was 0x%x"    ,"STATUS_DRIVER_UNABLE_TO_LOAD",0xC000026CL},
           {"DFS is unavailable on the contacted server."    ,"STATUS_DFS_UNAVAILABLE",0xC000026DL},
           {"An operation was attempted to a volume after it was dismounted."    ,"STATUS_VOLUME_DISMOUNTED",0xC000026EL},
           {"An internal error occurred in the Win32 x86 emulation subsystem."    ,"STATUS_WX86_INTERNAL_ERROR",0xC000026FL},
           {"Win32 x86 emulation subsystem Floating-point stack check."    ,"STATUS_WX86_FLOAT_STACK_CHECK",0xC0000270L},
           {"The validation process needs to continue on to the next step."    ,"STATUS_VALIDATE_CONTINUE",0xC0000271L},
           {"There was no match for the specified key in the index."    ,"STATUS_NO_MATCH",0xC0000272L},
           {"There are no more matches for the current index enumeration."    ,"STATUS_NO_MORE_MATCHES",0xC0000273L},
           {"The NTFS file or directory is not a reparse point."    ,"STATUS_NOT_A_REPARSE_POINT",0xC0000275L},
           {"The Windows I/O reparse tag passed for the NTFS reparse point is invalid."    ,"STATUS_IO_REPARSE_TAG_INVALID",0xC0000276L},
           {"The Windows I/O reparse tag does not match the one present in the NTFS reparse point."    ,"STATUS_IO_REPARSE_TAG_MISMATCH",0xC0000277L},
           {"The user data passed for the NTFS reparse point is invalid."    ,"STATUS_IO_REPARSE_DATA_INVALID",0xC0000278L},
           {"The layered file system driver for this IO tag did not handle it when needed."    ,"STATUS_IO_REPARSE_TAG_NOT_HANDLED",0xC0000279L},
           {"The NTFS symbolic link could not be resolved even though the initial file name is valid."    ,"STATUS_REPARSE_POINT_NOT_RESOLVED",0xC0000280L},
           {"The NTFS directory is a reparse point."    ,"STATUS_DIRECTORY_IS_A_REPARSE_POINT",0xC0000281L},
           {"The range could not be added to the range list because of a conflict."    ,"STATUS_RANGE_LIST_CONFLICT",0xC0000282L},
           {"The specified medium changer source element contains no media."    ,"STATUS_SOURCE_ELEMENT_EMPTY",0xC0000283L},
           {"The specified medium changer destination element already contains media."    ,"STATUS_DESTINATION_ELEMENT_FULL",0xC0000284L},
           {"The specified medium changer element does not exist."    ,"STATUS_ILLEGAL_ELEMENT_ADDRESS",0xC0000285L},
           {"The specified element is contained within a magazine that is no longer present."    ,"STATUS_MAGAZINE_NOT_PRESENT",0xC0000286L},
           {"The device requires reinitialization due to hardware errors."    ,"STATUS_REINITIALIZATION_NEEDED",0xC0000287L},
           {"The device has indicated that cleaning is necessary."    ,"STATUS_DEVICE_REQUIRES_CLEANING",0x80000288L},
           {"The device has indicated that it's door is open. Further operations require it closed and secured."    ,"STATUS_DEVICE_DOOR_OPEN",0x80000289L},
           {"The file encryption attempt failed."    ,"STATUS_ENCRYPTION_FAILED",0xC000028AL},
           {"The file decryption attempt failed."    ,"STATUS_DECRYPTION_FAILED",0xC000028BL},
           {"The specified range could not be found in the range list."    ,"STATUS_RANGE_NOT_FOUND",0xC000028CL},
           {"There is no encryption recovery policy configured for this system."    ,"STATUS_NO_RECOVERY_POLICY",0xC000028DL},
           {"The required encryption driver is not loaded for this system."    ,"STATUS_NO_EFS",0xC000028EL},
           {"The file was encrypted with a different encryption driver than is currently loaded."    ,"STATUS_WRONG_EFS",0xC000028FL},
           {"There are no EFS keys defined for the user."    ,"STATUS_NO_USER_KEYS",0xC0000290L},
           {"The specified file is not encrypted."    ,"STATUS_FILE_NOT_ENCRYPTED",0xC0000291L},
           {"The specified file is not in the defined EFS export format."    ,"STATUS_NOT_EXPORT_FORMAT",0xC0000292L},
           {"The specified file is encrypted and the user does not have the ability to decrypt it."    ,"STATUS_FILE_ENCRYPTED",0xC0000293L},
           {"The system has awoken"    ,"STATUS_WAKE_SYSTEM",0x40000294L},
           {"The guid passed was not recognized as valid by a WMI data provider."    ,"STATUS_WMI_GUID_NOT_FOUND",0xC0000295L},
           {"The instance name passed was not recognized as valid by a WMI data provider."    ,"STATUS_WMI_INSTANCE_NOT_FOUND",0xC0000296L},
           {"The data item id passed was not recognized as valid by a WMI data provider."    ,"STATUS_WMI_ITEMID_NOT_FOUND",0xC0000297L},
           {"The WMI request could not be completed and should be retried."    ,"STATUS_WMI_TRY_AGAIN",0xC0000298L},
           {"The policy object is shared and can only be modified at the root"    ,"STATUS_SHARED_POLICY",0xC0000299L},
           {"The policy object does not exist when it should"    ,"STATUS_POLICY_OBJECT_NOT_FOUND",0xC000029AL},
           {"The requested policy information only lives in the Ds"    ,"STATUS_POLICY_ONLY_IN_DS",0xC000029BL},
           {"The volume must be upgraded to enable this feature"    ,"STATUS_VOLUME_NOT_UPGRADED",0xC000029CL},
           {"The remote storage service is not operational at this time."    ,"STATUS_REMOTE_STORAGE_NOT_ACTIVE",0xC000029DL},
           {"The remote storage service encountered a media error."    ,"STATUS_REMOTE_STORAGE_MEDIA_ERROR",0xC000029EL},
           {"The tracking (workstation) service is not running."    ,"STATUS_NO_TRACKING_SERVICE",0xC000029FL},
           {"The server process is running under a SID different than that required by client."    ,"STATUS_SERVER_SID_MISMATCH",0xC00002A0L},
           {"The specified directory service attribute or value does not exist."    ,"STATUS_DS_NO_ATTRIBUTE_OR_VALUE",0xC00002A1L},
           {"The attribute syntax specified to the directory service is invalid."    ,"STATUS_DS_INVALID_ATTRIBUTE_SYNTAX",0xC00002A2L},
           {"The attribute type specified to the directory service is not defined."    ,"STATUS_DS_ATTRIBUTE_TYPE_UNDEFINED",0xC00002A3L},
           {"The specified directory service attribute or value already exists."    ,"STATUS_DS_ATTRIBUTE_OR_VALUE_EXISTS",0xC00002A4L},
           {"The directory service is busy."    ,"STATUS_DS_BUSY",0xC00002A5L},
           {"The directory service is not available."    ,"STATUS_DS_UNAVAILABLE",0xC00002A6L},
           {"The directory service was unable to allocate a relative identifier."    ,"STATUS_DS_NO_RIDS_ALLOCATED",0xC00002A7L},
           {"The directory service has exhausted the pool of relative identifiers."    ,"STATUS_DS_NO_MORE_RIDS",0xC00002A8L},
           {"The requested operation could not be performed because the directory service is not the master for that type of operation."    ,"STATUS_DS_INCORRECT_ROLE_OWNER",0xC00002A9L},
           {"The directory service was unable to initialize the subsystem that allocates relative identifiers."    ,"STATUS_DS_RIDMGR_INIT_ERROR",0xC00002AAL},
           {"The requested operation did not satisfy one or more constraints associated with the class of the object."    ,"STATUS_DS_OBJ_CLASS_VIOLATION",0xC00002ABL},
           {"The directory service can perform the requested operation only on a leaf object."    ,"STATUS_DS_CANT_ON_NON_LEAF",0xC00002ACL},
           {"The directory service cannot perform the requested operation on the Relatively Defined Name (RDN) attribute of an object."    ,"STATUS_DS_CANT_ON_RDN",0xC00002ADL},
           {"The directory service detected an attempt to modify the object class of an object."    ,"STATUS_DS_CANT_MOD_OBJ_CLASS",0xC00002AEL},
           {"An error occurred while performing a cross domain move operation."    ,"STATUS_DS_CROSS_DOM_MOVE_FAILED",0xC00002AFL},
           {"Unable to Contact the Global Catalog Server."    ,"STATUS_DS_GC_NOT_AVAILABLE",0xC00002B0L},
           {"The requested operation requires a directory service, and none was available."    ,"STATUS_DIRECTORY_SERVICE_REQUIRED",0xC00002B1L},
           {"The reparse attribute cannot be set as it is incompatible with an existing attribute."    ,"STATUS_REPARSE_ATTRIBUTE_CONFLICT",0xC00002B2L},
           {"A group marked use for deny only  can not be enabled."    ,"STATUS_CANT_ENABLE_DENY_ONLY",0xC00002B3L},
           {"{EXCEPTION}"
"Multiple floating point faults."    ,"STATUS_FLOAT_MULTIPLE_FAULTS",0xC00002B4L},
           {"{EXCEPTION}"
"Multiple floating point traps."    ,"STATUS_FLOAT_MULTIPLE_TRAPS",0xC00002B5L},
           {"The device has been removed."    ,"STATUS_DEVICE_REMOVED",0xC00002B6L},
           {"The volume change journal is being deleted."    ,"STATUS_JOURNAL_DELETE_IN_PROGRESS",0xC00002B7L},
           {"The volume change journal is not active."    ,"STATUS_JOURNAL_NOT_ACTIVE",0xC00002B8L},
           {"The requested interface is not supported."    ,"STATUS_NOINTERFACE",0xC00002B9L},
           {"A directory service resource limit has been exceeded."    ,"STATUS_DS_ADMIN_LIMIT_EXCEEDED",0xC00002C1L},
           {"{System Standby Failed}"
"The driver %hs does not support standby mode. Updating this driver may allow the system to go to standby mode."    ,"STATUS_DRIVER_FAILED_SLEEP",0xC00002C2L},
           {"Mutual Authentication failed. The server's password is out of date at the domain controller."    ,"STATUS_MUTUAL_AUTHENTICATION_FAILED",0xC00002C3L},
           {"The system file %1 has become corrupt and has been replaced."    ,"STATUS_CORRUPT_SYSTEM_FILE",0xC00002C4L},
           {"{EXCEPTION}"
"Alignment Error"
"A datatype misalignment error was detected in a load or store instruction."    ,"STATUS_DATATYPE_MISALIGNMENT_ERROR",0xC00002C5L},
           {"The WMI data item or data block is read only."    ,"STATUS_WMI_READ_ONLY",0xC00002C6L},
           {"The WMI data item or data block could not be changed."    ,"STATUS_WMI_SET_FAILURE",0xC00002C7L},
           {"{Virtual Memory Minimum Too Low}"
"Your system is low on virtual memory. Windows is increasing the size of your virtual memory paging file."
"During this process, memory requests for some applications may be denied. For more information, see Help."    ,"STATUS_COMMITMENT_MINIMUM",0xC00002C8L},
           {"{EXCEPTION}"
"Register NaT consumption faults."
"A NaT value is consumed on a non speculative instruction."    ,"STATUS_REG_NAT_CONSUMPTION",0xC00002C9L},
           {"The medium changer's transport element contains media, which is causing the operation to fail."    ,"STATUS_TRANSPORT_FULL",0xC00002CAL},
           {"Security Accounts Manager initialization failed because of the following error:"
"%hs"
"Error Status: 0x%x."
"Please click OK to shutdown this system and reboot into Directory Services Restore Mode, check the event log for more detailed information."    ,"STATUS_DS_SAM_INIT_FAILURE",0xC00002CBL},
           {"This operation is supported only when you are connected to the server."    ,"STATUS_ONLY_IF_CONNECTED",0xC00002CCL},
           {"Only an administrator can modify the membership list of an administrative group."    ,"STATUS_DS_SENSITIVE_GROUP_VIOLATION",0xC00002CDL},
           {"A device was removed so enumeration must be restarted."    ,"STATUS_PNP_RESTART_ENUMERATION",0xC00002CEL},
           {"The journal entry has been deleted from the journal."    ,"STATUS_JOURNAL_ENTRY_DELETED",0xC00002CFL},
           {"Cannot change the primary group ID of a domain controller account."    ,"STATUS_DS_CANT_MOD_PRIMARYGROUPID",0xC00002D0L},
           {"{Fatal System Error}"
"The system image %s is not properly signed."
"The file has been replaced with the signed file."
"The system has been shut down."    ,"STATUS_SYSTEM_IMAGE_BAD_SIGNATURE",0xC00002D1L},
           {"Device will not start without a reboot."    ,"STATUS_PNP_REBOOT_REQUIRED",0xC00002D2L},
           {"Current device power state cannot support this request."    ,"STATUS_POWER_STATE_INVALID",0xC00002D3L},
           {"The specified group type is invalid."    ,"STATUS_DS_INVALID_GROUP_TYPE",0xC00002D4L},
           {"In mixed domain no nesting of global group if group is security enabled."    ,"STATUS_DS_NO_NEST_GLOBALGROUP_IN_MIXEDDOMAIN",0xC00002D5L},
           {"In mixed domain, cannot nest local groups with other local groups, if the group is security enabled."    ,"STATUS_DS_NO_NEST_LOCALGROUP_IN_MIXEDDOMAIN",0xC00002D6L},
           {"A global group cannot have a local group as a member."    ,"STATUS_DS_GLOBAL_CANT_HAVE_LOCAL_MEMBER",0xC00002D7L},
           {"A global group cannot have a universal group as a member."    ,"STATUS_DS_GLOBAL_CANT_HAVE_UNIVERSAL_MEMBER",0xC00002D8L},
           {"A universal group cannot have a local group as a member."    ,"STATUS_DS_UNIVERSAL_CANT_HAVE_LOCAL_MEMBER",0xC00002D9L},
           {"A global group cannot have a cross domain member."    ,"STATUS_DS_GLOBAL_CANT_HAVE_CROSSDOMAIN_MEMBER",0xC00002DAL},
           {"A local group cannot have another cross domain local group as a member."    ,"STATUS_DS_LOCAL_CANT_HAVE_CROSSDOMAIN_LOCAL_MEMBER",0xC00002DBL},
           {"Can not change to security disabled group because of having primary members in this group."    ,"STATUS_DS_HAVE_PRIMARY_MEMBERS",0xC00002DCL},
           {"The WMI operation is not supported by the data block or method."    ,"STATUS_WMI_NOT_SUPPORTED",0xC00002DDL},
           {"There is not enough power to complete the requested operation."    ,"STATUS_INSUFFICIENT_POWER",0xC00002DEL},
           {"Security Account Manager needs to get the boot password."    ,"STATUS_SAM_NEED_BOOTKEY_PASSWORD",0xC00002DFL},
           {"Security Account Manager needs to get the boot key from floppy disk."    ,"STATUS_SAM_NEED_BOOTKEY_FLOPPY",0xC00002E0L},
           {"Directory Service can not start."    ,"STATUS_DS_CANT_START",0xC00002E1L},
           {"Directory Services could not start because of the following error:"
"%hs"
"Error Status: 0x%x."
"Please click OK to shutdown this system and reboot into Directory Services Restore Mode, check the event log for more detailed information."    ,"STATUS_DS_INIT_FAILURE",0xC00002E2L},
           {"Security Accounts Manager initialization failed because of the following error:"
"%hs"
"Error Status: 0x%x."
"Please click OK to shutdown this system and reboot into Safe Mode, check the event log for more detailed information."    ,"STATUS_SAM_INIT_FAILURE",0xC00002E3L},
           {"The requested operation can be performed only on a global catalog server."    ,"STATUS_DS_GC_REQUIRED",0xC00002E4L},
           {"A local group can only be a member of other local groups in the same domain."    ,"STATUS_DS_LOCAL_MEMBER_OF_LOCAL_ONLY",0xC00002E5L},
           {"Foreign security principals cannot be members of universal groups."    ,"STATUS_DS_NO_FPO_IN_UNIVERSAL_GROUPS",0xC00002E6L},
           {"Your computer could not be joined to the domain. You have exceeded the maximum number of computer accounts you are allowed to create in this domain. Contact your system administrator to have this limit reset or increased."    ,"STATUS_DS_MACHINE_ACCOUNT_QUOTA_EXCEEDED",0xC00002E7L},
           {"STATUS_MULTIPLE_FAULT_VIOLATION"    ,"STATUS_MULTIPLE_FAULT_VIOLATION",0xC00002E8L},
           {"This operation can not be performed on the current domain."    ,"STATUS_CURRENT_DOMAIN_NOT_ALLOWED",0xC00002E9L},
           {"The directory or file cannot be created."    ,"STATUS_CANNOT_MAKE",0xC00002EAL},
           {"The system is in the process of shutting down."    ,"STATUS_SYSTEM_SHUTDOWN",0xC00002EBL},
           {"Directory Services could not start because of the following error:"
"%hs"
"Error Status: 0x%x."
"Please click OK to shutdown the system. You can use the recovery console to diagnose the system further."    ,"STATUS_DS_INIT_FAILURE_CONSOLE",0xC00002ECL},
           {"Security Accounts Manager initialization failed because of the following error:"
"%hs"
"Error Status: 0x%x."
"Please click OK to shutdown the system. You can use the recovery console to diagnose the system further."    ,"STATUS_DS_SAM_INIT_FAILURE_CONSOLE",0xC00002EDL},
           {"A security context was deleted before the context was completed.  This is considered a logon failure."    ,"STATUS_UNFINISHED_CONTEXT_DELETED",0xC00002EEL},
           {"The client is trying to negotiate a context and the server requires user-to-user but didn't send a TGT reply."    ,"STATUS_NO_TGT_REPLY",0xC00002EFL},
           {"An object ID was not found in the file."    ,"STATUS_OBJECTID_NOT_FOUND",0xC00002F0L},
           {"Unable to accomplish the requested task because the local machine does not have any IP addresses."    ,"STATUS_NO_IP_ADDRESSES",0xC00002F1L},
           {"The supplied credential handle does not match the credential associated with the security context."    ,"STATUS_WRONG_CREDENTIAL_HANDLE",0xC00002F2L},
           {"The crypto system or checksum function is invalid because a required function is unavailable."    ,"STATUS_CRYPTO_SYSTEM_INVALID",0xC00002F3L},
           {"The number of maximum ticket referrals has been exceeded."    ,"STATUS_MAX_REFERRALS_EXCEEDED",0xC00002F4L},
           {"The local machine must be a Kerberos KDC (domain controller) and it is not."    ,"STATUS_MUST_BE_KDC",0xC00002F5L},
           {"The other end of the security negotiation is requires strong crypto but it is not supported on the local machine."    ,"STATUS_STRONG_CRYPTO_NOT_SUPPORTED",0xC00002F6L},
           {"The KDC reply contained more than one principal name."    ,"STATUS_TOO_MANY_PRINCIPALS",0xC00002F7L},
           {"Expected to find PA data for a hint of what etype to use, but it was not found."    ,"STATUS_NO_PA_DATA",0xC00002F8L},
           {"The client certificate does not contain a valid UPN, or does not match the client name "
"in the logon request.  Please contact your administrator."    ,"STATUS_PKINIT_NAME_MISMATCH",0xC00002F9L},
           {"Smartcard logon is required and was not used."    ,"STATUS_SMARTCARD_LOGON_REQUIRED",0xC00002FAL},
           {"An invalid request was sent to the KDC."    ,"STATUS_KDC_INVALID_REQUEST",0xC00002FBL},
           {"The KDC was unable to generate a referral for the service requested."    ,"STATUS_KDC_UNABLE_TO_REFER",0xC00002FCL},
           {"The encryption type requested is not supported by the KDC."    ,"STATUS_KDC_UNKNOWN_ETYPE",0xC00002FDL},
           {"A system shutdown is in progress."    ,"STATUS_SHUTDOWN_IN_PROGRESS",0xC00002FEL},
           {"The server machine is shutting down."    ,"STATUS_SERVER_SHUTDOWN_IN_PROGRESS",0xC00002FFL},
           {"This operation is not supported on a computer running Windows Server 2003 for Small Business Server"    ,"STATUS_NOT_SUPPORTED_ON_SBS",0xC0000300L},
           {"The WMI GUID is no longer available"    ,"STATUS_WMI_GUID_DISCONNECTED",0xC0000301L},
           {"Collection or events for the WMI GUID is already disabled."    ,"STATUS_WMI_ALREADY_DISABLED",0xC0000302L},
           {"Collection or events for the WMI GUID is already enabled."    ,"STATUS_WMI_ALREADY_ENABLED",0xC0000303L},
           {"The Master File Table on the volume is too fragmented to complete this operation."    ,"STATUS_MFT_TOO_FRAGMENTED",0xC0000304L},
           {"Copy protection failure."    ,"STATUS_COPY_PROTECTION_FAILURE",0xC0000305L},
           {"Copy protection error - DVD CSS Authentication failed."    ,"STATUS_CSS_AUTHENTICATION_FAILURE",0xC0000306L},
           {"Copy protection error - The given sector does not contain a valid key."    ,"STATUS_CSS_KEY_NOT_PRESENT",0xC0000307L},
           {"Copy protection error - DVD session key not established."    ,"STATUS_CSS_KEY_NOT_ESTABLISHED",0xC0000308L},
           {"Copy protection error - The read failed because the sector is encrypted."    ,"STATUS_CSS_SCRAMBLED_SECTOR",0xC0000309L},
           {"Copy protection error - The given DVD's region does not correspond to the"
"region setting of the drive."    ,"STATUS_CSS_REGION_MISMATCH",0xC000030AL},
           {"Copy protection error - The drive's region setting may be permanent."    ,"STATUS_CSS_RESETS_EXHAUSTED",0xC000030BL},
           {"The kerberos protocol encountered an error while validating the KDC certificate during smartcard Logon.  There"
"is more information in the system event log."    ,"STATUS_PKINIT_FAILURE",0xC0000320L},
           {"The kerberos protocol encountered an error while attempting to utilize the smartcard subsystem."    ,"STATUS_SMARTCARD_SUBSYSTEM_FAILURE",0xC0000321L},
           {"The target server does not have acceptable kerberos credentials."    ,"STATUS_NO_KERB_KEY",0xC0000322L},
           {"The transport determined that the remote system is down."    ,"STATUS_HOST_DOWN",0xC0000350L},
           {"An unsupported preauthentication mechanism was presented to the kerberos package."    ,"STATUS_UNSUPPORTED_PREAUTH",0xC0000351L},
           {"The encryption algorithm used on the source file needs a bigger key buffer than the one used on the destination file."    ,"STATUS_EFS_ALG_BLOB_TOO_BIG",0xC0000352L},
           {"An attempt to remove a processes DebugPort was made, but a port was not already associated with the process."    ,"STATUS_PORT_NOT_SET",0xC0000353L},
           {"An attempt to do an operation on a debug port failed because the port is in the process of being deleted."    ,"STATUS_DEBUGGER_INACTIVE",0xC0000354L},
           {"This version of Windows is not compatible with the behavior version of directory forest, domain or domain controller."    ,"STATUS_DS_VERSION_CHECK_FAILURE",0xC0000355L},
           {"The specified event is currently not being audited."    ,"STATUS_AUDITING_DISABLED",0xC0000356L},
           {"The machine account was created pre-NT4.  The account needs to be recreated."    ,"STATUS_PRENT4_MACHINE_ACCOUNT",0xC0000357L},
           {"A account group can not have a universal group as a member."    ,"STATUS_DS_AG_CANT_HAVE_UNIVERSAL_MEMBER",0xC0000358L},
           {"The specified image file did not have the correct format, it appears to be a 32-bit Windows image."    ,"STATUS_INVALID_IMAGE_WIN_32",0xC0000359L},
           {"The specified image file did not have the correct format, it appears to be a 64-bit Windows image."    ,"STATUS_INVALID_IMAGE_WIN_64",0xC000035AL},
           {"Client's supplied SSPI channel bindings were incorrect."    ,"STATUS_BAD_BINDINGS",0xC000035BL},
           {"The client's session has expired, so the client must reauthenticate to continue accessing the remote resources."    ,"STATUS_NETWORK_SESSION_EXPIRED",0xC000035CL},
           {"AppHelp dialog canceled thus preventing the application from starting."    ,"STATUS_APPHELP_BLOCK",0xC000035DL},
           {"The SID filtering operation removed all SIDs."    ,"STATUS_ALL_SIDS_FILTERED",0xC000035EL},
           {"The driver was not loaded because the system is booting into safe mode."    ,"STATUS_NOT_SAFE_MODE_DRIVER",0xC000035FL},
           {"Access to %1 has been restricted by your Administrator by the default software restriction policy level."    ,"STATUS_ACCESS_DISABLED_BY_POLICY_DEFAULT",0xC0000361L},
           {"Access to %1 has been restricted by your Administrator by location with policy rule %2 placed on path %3"    ,"STATUS_ACCESS_DISABLED_BY_POLICY_PATH",0xC0000362L},
           {"Access to %1 has been restricted by your Administrator by software publisher policy."    ,"STATUS_ACCESS_DISABLED_BY_POLICY_PUBLISHER",0xC0000363L},
           {"Access to %1 has been restricted by your Administrator by policy rule %2."    ,"STATUS_ACCESS_DISABLED_BY_POLICY_OTHER",0xC0000364L},
           {"The driver was not loaded because it failed it's initialization call."    ,"STATUS_FAILED_DRIVER_ENTRY",0xC0000365L},
           {"The \"%hs\" encountered an error while applying power or reading the device configuration."
"This may be caused by a failure of your hardware or by a poor connection."    ,"STATUS_DEVICE_ENUMERATION_ERROR",0xC0000366L},
           {"An operation is blocked waiting for an oplock."    ,"STATUS_WAIT_FOR_OPLOCK",0x00000367L},
           {"The create operation failed because the name contained at least one mount point which resolves to a volume to which the specified device object is not attached."    ,"STATUS_MOUNT_POINT_NOT_RESOLVED",0xC0000368L},
           {"The device object parameter is either not a valid device object or is not attached to the volume specified by the file name."    ,"STATUS_INVALID_DEVICE_OBJECT_PARAMETER",0xC0000369L},
           {"A Machine Check Error has occurred. Please check the system eventlog for additional information."    ,"STATUS_MCA_OCCURED",0xC000036AL},
           {"Driver %2 has been blocked from loading."    ,"STATUS_DRIVER_BLOCKED_CRITICAL",0xC000036BL},
           {"Driver %2 has been blocked from loading."    ,"STATUS_DRIVER_BLOCKED",0xC000036CL},
           {"There was error [%2] processing the driver database."    ,"STATUS_DRIVER_DATABASE_ERROR",0xC000036DL},
           {"System hive size has exceeded its limit."    ,"STATUS_SYSTEM_HIVE_TOO_LARGE",0xC000036EL},
           {"A dynamic link library (DLL},"    ,"STATUS_INVALID_IMPORT_OF_NON_DLL",0xC000036FL},
           {"The Directory Service is shuting down."    ,"STATUS_DS_SHUTTING_DOWN",0x40000370L},
           {"An incorrect PIN was presented to the smart card"    ,"STATUS_SMARTCARD_WRONG_PIN",0xC0000380L},
           {"The smart card is blocked"    ,"STATUS_SMARTCARD_CARD_BLOCKED",0xC0000381L},
           {"No PIN was presented to the smart card"    ,"STATUS_SMARTCARD_CARD_NOT_AUTHENTICATED",0xC0000382L},
           {"No smart card available"    ,"STATUS_SMARTCARD_NO_CARD",0xC0000383L},
           {"The requested key container does not exist on the smart card"    ,"STATUS_SMARTCARD_NO_KEY_CONTAINER",0xC0000384L},
           {"The requested certificate does not exist on the smart card"    ,"STATUS_SMARTCARD_NO_CERTIFICATE",0xC0000385L},
           {"The requested keyset does not exist"    ,"STATUS_SMARTCARD_NO_KEYSET",0xC0000386L},
           {"A communication error with the smart card has been detected."    ,"STATUS_SMARTCARD_IO_ERROR",0xC0000387L},
           {"The system detected a possible attempt to compromise security. Please ensure that you can contact the server that authenticated you."    ,"STATUS_DOWNGRADE_DETECTED",0xC0000388L},
           {"The smartcard certificate used for authentication has been revoked."
"Please contact your system administrator.  There may be additional information in the"
"event log."    ,"STATUS_SMARTCARD_CERT_REVOKED",0xC0000389L},
           {"An untrusted certificate authority was detected While processing the"
"smartcard certificate used for authentication.  Please contact your system"
"administrator."    ,"STATUS_ISSUING_CA_UNTRUSTED",0xC000038AL},
           {"The revocation status of the smartcard certificate used for"
"authentication could not be determined. Please contact your system administrator."    ,"STATUS_REVOCATION_OFFLINE_C",0xC000038BL},
           {"The smartcard certificate used for authentication was not trusted.  Please"
"contact your system administrator."    ,"STATUS_PKINIT_CLIENT_FAILURE",0xC000038CL},
           {"The smartcard certificate used for authentication has expired.  Please"
"contact your system administrator."    ,"STATUS_SMARTCARD_CERT_EXPIRED",0xC000038DL},
           {"The driver could not be loaded because a previous version of the driver is still in memory."    ,"STATUS_DRIVER_FAILED_PRIOR_UNLOAD",0xC000038EL},
           {"The smartcard provider could not perform the action since the context was acquired as silent."    ,"STATUS_SMARTCARD_SILENT_CONTEXT",0xC000038FL},
           {"The current user's delegated trust creation quota has been exceeded."    ,"STATUS_PER_USER_TRUST_QUOTA_EXCEEDED",0xC0000401L},
           {"The total delegated trust creation quota has been exceeded."    ,"STATUS_ALL_USER_TRUST_QUOTA_EXCEEDED",0xC0000402L},
           {"The current user's delegated trust deletion quota has been exceeded."    ,"STATUS_USER_DELETE_TRUST_QUOTA_EXCEEDED",0xC0000403L},
           {"The requested name already exists as a unique identifier."    ,"STATUS_DS_NAME_NOT_UNIQUE",0xC0000404L},
           {"The requested object has a non-unique identifier and cannot be retrieved."    ,"STATUS_DS_DUPLICATE_ID_FOUND",0xC0000405L},
           {"The group cannot be converted due to attribute restrictions on the requested group type."    ,"STATUS_DS_GROUP_CONVERSION_ERROR",0xC0000406L},
           {"{Volume Shadow Copy Service}"
"Please wait while the Volume Shadow Copy Service prepares volume %hs for hibernation."    ,"STATUS_VOLSNAP_PREPARE_HIBERNATE",0xC0000407L},
           {"Kerberos sub-protocol User2User is required."    ,"STATUS_USER2USER_REQUIRED",0xC0000408L},
           {"The system detected an overrun of a stack-based buffer in this application.  This"
"overrun could potentially allow a malicious user to gain control of this application."    ,"STATUS_STACK_BUFFER_OVERRUN",0xC0000409L},
           {"The Kerberos subsystem encountered an error.  A service for user protocol request was made "
"against a domain controller which does not support service for user."    ,"STATUS_NO_S4U_PROT_SUPPORT",0xC000040AL},
           {"An attempt was made by this server to make a Kerberos constrained delegation request for a target"
"outside of the server's realm.  This is not supported, and indicates a misconfiguration on this"
"server's allowed to delegate to list.  Please contact your administrator."    ,"STATUS_CROSSREALM_DELEGATION_FAILURE",0xC000040BL},
           {"The revocation status of the domain controller certificate used for smartcard"
"authentication could not be determined.  There is additional information in the system event"
"log. Please contact your system administrator."    ,"STATUS_REVOCATION_OFFLINE_KDC",0xC000040CL},
           {"An untrusted certificate authority was detected while processing the"
"domain controller certificate used for authentication.  There is additional information in"
"the system event log.  Please contact your system administrator."    ,"STATUS_ISSUING_CA_UNTRUSTED_KDC",0xC000040DL},
           {"The domain controller certificate used for smartcard logon has expired."
"Please contact your system administrator with the contents of your system event log."    ,"STATUS_KDC_CERT_EXPIRED",0xC000040EL},
           {"The domain controller certificate used for smartcard logon has been revoked."
"Please contact your system administrator with the contents of your system event log."    ,"STATUS_KDC_CERT_REVOKED",0xC000040FL},
           {"Data present in one of the parameters is more than the function can operate on."    ,"STATUS_PARAMETER_QUOTA_EXCEEDED",0xC0000410L},
           {"The system has failed to hibernate (The error code is %hs).  Hibernation will be disabled until the system is restarted."    ,"STATUS_HIBERNATION_FAILURE",0xC0000411L},
           {"An attempt to delay-load a .dll or get a function address in a delay-loaded .dll failed."    ,"STATUS_DELAY_LOAD_FAILED",0xC0000412L},
           {"Logon Failure: The machine you are logging onto is protected by an authentication firewall.  The specified account is not allowed to authenticate to the machine."    ,"STATUS_AUTHENTICATION_FIREWALL_FAILED",0xC0000413L},
           {"%hs is a 16-bit application. You do not have permissions to execute 16-bit applications. Check your permissions with your system administrator."    ,"STATUS_VDM_DISALLOWED",0xC0000414L},
           {"{Display Driver Stopped Responding}"
"The %hs display driver has stopped working normally.  Save your work and reboot the system to restore full display functionality."
"The next time you reboot the machine a dialog will be displayed giving you a chance to report this failure to Microsoft."    ,"STATUS_HUNG_DISPLAY_DRIVER_THREAD",0xC0000415L},
			{"An assertion failure has occurred."    ,"STATUS_ASSERTION_FAILURE",0xC0000420L},
			{ "An exception has occurred in a user mode callback and the kernel callback frame should be removed."
    ,"STATUS_CALLBACK_POP_STACK",0xC0000423L},
           {"The attempted write operation encountered a write already in progress for some portion of the range."    ,"STATUS_ENCOUNTERED_WRITE_IN_PROGRESS",0xC0000433L},
           {"WOW Assertion Error."    ,"STATUS_WOW_ASSERTION",0xC0009898L},
           {"Debugger did not perform a state change."    ,"DBG_NO_STATE_CHANGE",0xC0010001L},
           {"Debugger has found the application is not idle."    ,"DBG_APP_NOT_IDLE",0xC0010002L},
           {"The string binding is invalid."    ,"RPC_NT_INVALID_STRING_BINDING",0xC0020001L},
           {"The binding handle is not the correct type."    ,"RPC_NT_WRONG_KIND_OF_BINDING",0xC0020002L},
           {"The binding handle is invalid."    ,"RPC_NT_INVALID_BINDING",0xC0020003L},
           {"The RPC protocol sequence is not supported."    ,"RPC_NT_PROTSEQ_NOT_SUPPORTED",0xC0020004L},
           {"The RPC protocol sequence is invalid."    ,"RPC_NT_INVALID_RPC_PROTSEQ",0xC0020005L},
           {"The string UUID is invalid."    ,"RPC_NT_INVALID_STRING_UUID",0xC0020006L},
           {"The endpoint format is invalid."    ,"RPC_NT_INVALID_ENDPOINT_FORMAT",0xC0020007L},
           {"The network address is invalid."    ,"RPC_NT_INVALID_NET_ADDR",0xC0020008L},
           {"No endpoint was found."    ,"RPC_NT_NO_ENDPOINT_FOUND",0xC0020009L},
           {"The timeout value is invalid."    ,"RPC_NT_INVALID_TIMEOUT",0xC002000AL},
           {"The object UUID was not found."    ,"RPC_NT_OBJECT_NOT_FOUND",0xC002000BL},
           {"The object UUID has already been registered."    ,"RPC_NT_ALREADY_REGISTERED",0xC002000CL},
           {"The type UUID has already been registered."    ,"RPC_NT_TYPE_ALREADY_REGISTERED",0xC002000DL},
           {"The RPC server is already listening."    ,"RPC_NT_ALREADY_LISTENING",0xC002000EL},
           {"No protocol sequences have been registered."    ,"RPC_NT_NO_PROTSEQS_REGISTERED",0xC002000FL},
           {"The RPC server is not listening."    ,"RPC_NT_NOT_LISTENING",0xC0020010L},
           {"The manager type is unknown."    ,"RPC_NT_UNKNOWN_MGR_TYPE",0xC0020011L},
           {"The interface is unknown."    ,"RPC_NT_UNKNOWN_IF",0xC0020012L},
           {"There are no bindings."    ,"RPC_NT_NO_BINDINGS",0xC0020013L},
           {"There are no protocol sequences."    ,"RPC_NT_NO_PROTSEQS",0xC0020014L},
           {"The endpoint cannot be created."    ,"RPC_NT_CANT_CREATE_ENDPOINT",0xC0020015L},
           {"Not enough resources are available to complete this operation."    ,"RPC_NT_OUT_OF_RESOURCES",0xC0020016L},
           {"The RPC server is unavailable."    ,"RPC_NT_SERVER_UNAVAILABLE",0xC0020017L},
           {"The RPC server is too busy to complete this operation."    ,"RPC_NT_SERVER_TOO_BUSY",0xC0020018L},
           {"The network options are invalid."    ,"RPC_NT_INVALID_NETWORK_OPTIONS",0xC0020019L},
           {"There are no remote procedure calls active on this thread."    ,"RPC_NT_NO_CALL_ACTIVE",0xC002001AL},
           {"The remote procedure call failed."    ,"RPC_NT_CALL_FAILED",0xC002001BL},
           {"The remote procedure call failed and did not execute."    ,"RPC_NT_CALL_FAILED_DNE",0xC002001CL},
           {"An RPC protocol error occurred."    ,"RPC_NT_PROTOCOL_ERROR",0xC002001DL},
           {"The transfer syntax is not supported by the RPC server."    ,"RPC_NT_UNSUPPORTED_TRANS_SYN",0xC002001FL},
           {"The type UUID is not supported."    ,"RPC_NT_UNSUPPORTED_TYPE",0xC0020021L},
           {"The tag is invalid."    ,"RPC_NT_INVALID_TAG",0xC0020022L},
           {"The array bounds are invalid."    ,"RPC_NT_INVALID_BOUND",0xC0020023L},
           {"The binding does not contain an entry name."    ,"RPC_NT_NO_ENTRY_NAME",0xC0020024L},
           {"The name syntax is invalid."    ,"RPC_NT_INVALID_NAME_SYNTAX",0xC0020025L},
           {"The name syntax is not supported."    ,"RPC_NT_UNSUPPORTED_NAME_SYNTAX",0xC0020026L},
           {"No network address is available to use to construct a UUID."    ,"RPC_NT_UUID_NO_ADDRESS",0xC0020028L},
           {"The endpoint is a duplicate."    ,"RPC_NT_DUPLICATE_ENDPOINT",0xC0020029L},
           {"The authentication type is unknown."    ,"RPC_NT_UNKNOWN_AUTHN_TYPE",0xC002002AL},
           {"The maximum number of calls is too small."    ,"RPC_NT_MAX_CALLS_TOO_SMALL",0xC002002BL},
           {"The string is too long."    ,"RPC_NT_STRING_TOO_LONG",0xC002002CL},
           {"The RPC protocol sequence was not found."    ,"RPC_NT_PROTSEQ_NOT_FOUND",0xC002002DL},
           {"The procedure number is out of range."    ,"RPC_NT_PROCNUM_OUT_OF_RANGE",0xC002002EL},
           {"The binding does not contain any authentication information."    ,"RPC_NT_BINDING_HAS_NO_AUTH",0xC002002FL},
           {"The authentication service is unknown."    ,"RPC_NT_UNKNOWN_AUTHN_SERVICE",0xC0020030L},
           {"The authentication level is unknown."    ,"RPC_NT_UNKNOWN_AUTHN_LEVEL",0xC0020031L},
           {"The security context is invalid."    ,"RPC_NT_INVALID_AUTH_IDENTITY",0xC0020032L},
           {"The authorization service is unknown."    ,"RPC_NT_UNKNOWN_AUTHZ_SERVICE",0xC0020033L},
           {"The entry is invalid."    ,"EPT_NT_INVALID_ENTRY",0xC0020034L},
           {"The operation cannot be performed."    ,"EPT_NT_CANT_PERFORM_OP",0xC0020035L},
           {"There are no more endpoints available from the endpoint mapper."    ,"EPT_NT_NOT_REGISTERED",0xC0020036L},
           {"No interfaces have been exported."    ,"RPC_NT_NOTHING_TO_EXPORT",0xC0020037L},
           {"The entry name is incomplete."    ,"RPC_NT_INCOMPLETE_NAME",0xC0020038L},
           {"The version option is invalid."    ,"RPC_NT_INVALID_VERS_OPTION",0xC0020039L},
           {"There are no more members."    ,"RPC_NT_NO_MORE_MEMBERS",0xC002003AL},
           {"There is nothing to unexport."    ,"RPC_NT_NOT_ALL_OBJS_UNEXPORTED",0xC002003BL},
           {"The interface was not found."    ,"RPC_NT_INTERFACE_NOT_FOUND",0xC002003CL},
           {"The entry already exists."    ,"RPC_NT_ENTRY_ALREADY_EXISTS",0xC002003DL},
           {"The entry is not found."    ,"RPC_NT_ENTRY_NOT_FOUND",0xC002003EL},
           {"The name service is unavailable."    ,"RPC_NT_NAME_SERVICE_UNAVAILABLE",0xC002003FL},
           {"The network address family is invalid."    ,"RPC_NT_INVALID_NAF_ID",0xC0020040L},
           {"The requested operation is not supported."    ,"RPC_NT_CANNOT_SUPPORT",0xC0020041L},
           {"No security context is available to allow impersonation."    ,"RPC_NT_NO_CONTEXT_AVAILABLE",0xC0020042L},
           {"An internal error occurred in RPC."    ,"RPC_NT_INTERNAL_ERROR",0xC0020043L},
           {"The RPC server attempted an integer divide by zero."    ,"RPC_NT_ZERO_DIVIDE",0xC0020044L},
           {"An addressing error occurred in the RPC server."    ,"RPC_NT_ADDRESS_ERROR",0xC0020045L},
           {"A floating point operation at the RPC server caused a divide by zero."    ,"RPC_NT_FP_DIV_ZERO",0xC0020046L},
           {"A floating point underflow occurred at the RPC server."    ,"RPC_NT_FP_UNDERFLOW",0xC0020047L},
           {"A floating point overflow occurred at the RPC server."    ,"RPC_NT_FP_OVERFLOW",0xC0020048L},
           {"The list of RPC servers available for auto-handle binding has been exhausted."    ,"RPC_NT_NO_MORE_ENTRIES",0xC0030001L},
           {"The file designated by DCERPCCHARTRANS cannot be opened."    ,"RPC_NT_SS_CHAR_TRANS_OPEN_FAIL",0xC0030002L},
           {"The file containing the character translation table has fewer than 512 bytes."    ,"RPC_NT_SS_CHAR_TRANS_SHORT_FILE",0xC0030003L},
           {"A null context handle is passed as an [in] parameter."    ,"RPC_NT_SS_IN_NULL_CONTEXT",0xC0030004L},
           {"The context handle does not match any known context handles."    ,"RPC_NT_SS_CONTEXT_MISMATCH",0xC0030005L},
           {"The context handle changed during a call."    ,"RPC_NT_SS_CONTEXT_DAMAGED",0xC0030006L},
           {"The binding handles passed to a remote procedure call do not match."    ,"RPC_NT_SS_HANDLES_MISMATCH",0xC0030007L},
           {"The stub is unable to get the call handle."    ,"RPC_NT_SS_CANNOT_GET_CALL_HANDLE",0xC0030008L},
           {"A null reference pointer was passed to the stub."    ,"RPC_NT_NULL_REF_POINTER",0xC0030009L},
           {"The enumeration value is out of range."    ,"RPC_NT_ENUM_VALUE_OUT_OF_RANGE",0xC003000AL},
           {"The byte count is too small."    ,"RPC_NT_BYTE_COUNT_TOO_SMALL",0xC003000BL},
           {"The stub received bad data."    ,"RPC_NT_BAD_STUB_DATA",0xC003000CL},
           {"A remote procedure call is already in progress for this thread."    ,"RPC_NT_CALL_IN_PROGRESS",0xC0020049L},
           {"There are no more bindings."    ,"RPC_NT_NO_MORE_BINDINGS",0xC002004AL},
           {"The group member was not found."    ,"RPC_NT_GROUP_MEMBER_NOT_FOUND",0xC002004BL},
           {"The endpoint mapper database entry could not be created."    ,"EPT_NT_CANT_CREATE",0xC002004CL},
           {"The object UUID is the nil UUID."    ,"RPC_NT_INVALID_OBJECT",0xC002004DL},
           {"No interfaces have been registered."    ,"RPC_NT_NO_INTERFACES",0xC002004FL},
           {"The remote procedure call was cancelled."    ,"RPC_NT_CALL_CANCELLED",0xC0020050L},
           {"The binding handle does not contain all required information."    ,"RPC_NT_BINDING_INCOMPLETE",0xC0020051L},
           {"A communications failure occurred during a remote procedure call."    ,"RPC_NT_COMM_FAILURE",0xC0020052L},
           {"The requested authentication level is not supported."    ,"RPC_NT_UNSUPPORTED_AUTHN_LEVEL",0xC0020053L},
           {"No principal name registered."    ,"RPC_NT_NO_PRINC_NAME",0xC0020054L},
           {"The error specified is not a valid Windows RPC error code."    ,"RPC_NT_NOT_RPC_ERROR",0xC0020055L},
           {"A UUID that is valid only on this computer has been allocated."    ,"RPC_NT_UUID_LOCAL_ONLY",0x40020056L},
           {"A security package specific error occurred."    ,"RPC_NT_SEC_PKG_ERROR",0xC0020057L},
           {"Thread is not cancelled."    ,"RPC_NT_NOT_CANCELLED",0xC0020058L},
           {"Invalid operation on the encoding/decoding handle."    ,"RPC_NT_INVALID_ES_ACTION",0xC0030059L},
           {"Incompatible version of the serializing package."    ,"RPC_NT_WRONG_ES_VERSION",0xC003005AL},
           {"Incompatible version of the RPC stub."    ,"RPC_NT_WRONG_STUB_VERSION",0xC003005BL},
           {"The RPC pipe object is invalid or corrupted."    ,"RPC_NT_INVALID_PIPE_OBJECT",0xC003005CL},
           {"An invalid operation was attempted on an RPC pipe object."    ,"RPC_NT_INVALID_PIPE_OPERATION",0xC003005DL},
           {"Unsupported RPC pipe version."    ,"RPC_NT_WRONG_PIPE_VERSION",0xC003005EL},
           {"The RPC pipe object has already been closed."    ,"RPC_NT_PIPE_CLOSED",0xC003005FL},
           {"The RPC call completed before all pipes were processed."    ,"RPC_NT_PIPE_DISCIPLINE_ERROR",0xC0030060L},
           {"No more data is available from the RPC pipe."    ,"RPC_NT_PIPE_EMPTY",0xC0030061L},
           {"Invalid asynchronous remote procedure call handle."    ,"RPC_NT_INVALID_ASYNC_HANDLE",0xC0020062L},
           {"Invalid asynchronous RPC call handle for this operation."    ,"RPC_NT_INVALID_ASYNC_CALL",0xC0020063L},
           {"Some data remains to be sent in the request buffer."    ,"RPC_NT_SEND_INCOMPLETE",0x400200AFL},
           {"An attempt was made to run an invalid AML opcode"    ,"STATUS_ACPI_INVALID_OPCODE",0xC0140001L},
           {"The AML Interpreter Stack has overflowed"    ,"STATUS_ACPI_STACK_OVERFLOW",0xC0140002L},
           {"An inconsistent state has occurred"    ,"STATUS_ACPI_ASSERT_FAILED",0xC0140003L},
           {"An attempt was made to access an array outside of its bounds"    ,"STATUS_ACPI_INVALID_INDEX",0xC0140004L},
           {"A required argument was not specified"    ,"STATUS_ACPI_INVALID_ARGUMENT",0xC0140005L},
           {"A fatal error has occurred"    ,"STATUS_ACPI_FATAL",0xC0140006L},
           {"An invalid SuperName was specified"    ,"STATUS_ACPI_INVALID_SUPERNAME",0xC0140007L},
           {"An argument with an incorrect type was specified"    ,"STATUS_ACPI_INVALID_ARGTYPE",0xC0140008L},
           {"An object with an incorrect type was specified"    ,"STATUS_ACPI_INVALID_OBJTYPE",0xC0140009L},
           {"A target with an incorrect type was specified"    ,"STATUS_ACPI_INVALID_TARGETTYPE",0xC014000AL},
           {"An incorrect number of arguments were specified"    ,"STATUS_ACPI_INCORRECT_ARGUMENT_COUNT",0xC014000BL},
           {"An address failed to translate"    ,"STATUS_ACPI_ADDRESS_NOT_MAPPED",0xC014000CL},
           {"An incorrect event type was specified"    ,"STATUS_ACPI_INVALID_EVENTTYPE",0xC014000DL},
           {"A handler for the target already exists"    ,"STATUS_ACPI_HANDLER_COLLISION",0xC014000EL},
           {"Invalid data for the target was specified"    ,"STATUS_ACPI_INVALID_DATA",0xC014000FL},
           {"An invalid region for the target was specified"    ,"STATUS_ACPI_INVALID_REGION",0xC0140010L},
           {"An attempt was made to access a field outside of the defined range"    ,"STATUS_ACPI_INVALID_ACCESS_SIZE",0xC0140011L},
           {"The Global system lock could not be acquired"    ,"STATUS_ACPI_ACQUIRE_GLOBAL_LOCK",0xC0140012L},
           {"An attempt was made to reinitialize the ACPI subsystem"    ,"STATUS_ACPI_ALREADY_INITIALIZED",0xC0140013L},
           {"The ACPI subsystem has not been initialized"    ,"STATUS_ACPI_NOT_INITIALIZED",0xC0140014L},
           {"An incorrect mutex was specified"    ,"STATUS_ACPI_INVALID_MUTEX_LEVEL",0xC0140015L},
           {"The mutex is not currently owned"    ,"STATUS_ACPI_MUTEX_NOT_OWNED",0xC0140016L},
           {"An attempt was made to access the mutex by a process that was not the owner"    ,"STATUS_ACPI_MUTEX_NOT_OWNER",0xC0140017L},
           {"An error occurred during an access to Region Space"    ,"STATUS_ACPI_RS_ACCESS",0xC0140018L},
           {"An attempt was made to use an incorrect table"    ,"STATUS_ACPI_INVALID_TABLE",0xC0140019L},
           {"The registration of an ACPI event failed"    ,"STATUS_ACPI_REG_HANDLER_FAILED",0xC0140020L},
           {"An ACPI Power Object failed to transition state"    ,"STATUS_ACPI_POWER_REQUEST_FAILED",0xC0140021L},
           {"Session name %1 is invalid."    ,"STATUS_CTX_WINSTATION_NAME_INVALID",0xC00A0001L},
           {"The protocol driver %1 is invalid."    ,"STATUS_CTX_INVALID_PD",0xC00A0002L},
           {"The protocol driver %1 was not found in the system path."    ,"STATUS_CTX_PD_NOT_FOUND",0xC00A0003L},
           {"The Client Drive Mapping Service Has Connected on Terminal Connection."    ,"STATUS_CTX_CDM_CONNECT",0x400A0004L},
           {"The Client Drive Mapping Service Has Disconnected on Terminal Connection."    ,"STATUS_CTX_CDM_DISCONNECT",0x400A0005L},
           {"A close operation is pending on the Terminal Connection."    ,"STATUS_CTX_CLOSE_PENDING",0xC00A0006L},
           {"There are no free output buffers available."    ,"STATUS_CTX_NO_OUTBUF",0xC00A0007L},
           {"The MODEM.INF file was not found."    ,"STATUS_CTX_MODEM_INF_NOT_FOUND",0xC00A0008L},
           {"The modem (%1) was not found in MODEM.INF."    ,"STATUS_CTX_INVALID_MODEMNAME",0xC00A0009L},
           {"The modem did not accept the command sent to it."
"Verify the configured modem name matches the attached modem."    ,"STATUS_CTX_RESPONSE_ERROR",0xC00A000AL},
           {"The modem did not respond to the command sent to it."
"Verify the modem is properly cabled and powered on."    ,"STATUS_CTX_MODEM_RESPONSE_TIMEOUT",0xC00A000BL},
           {"Carrier detect has failed or carrier has been dropped due to disconnect."    ,"STATUS_CTX_MODEM_RESPONSE_NO_CARRIER",0xC00A000CL},
           {"Dial tone not detected within required time."
"Verify phone cable is properly attached and functional."    ,"STATUS_CTX_MODEM_RESPONSE_NO_DIALTONE",0xC00A000DL},
           {"Busy signal detected at remote site on callback."    ,"STATUS_CTX_MODEM_RESPONSE_BUSY",0xC00A000EL},
           {"Voice detected at remote site on callback."    ,"STATUS_CTX_MODEM_RESPONSE_VOICE",0xC00A000FL},
           {"Transport driver error"    ,"STATUS_CTX_TD_ERROR",0xC00A0010L},
           {"The client you are using is not licensed to use this system. Your logon request is denied."    ,"STATUS_CTX_LICENSE_CLIENT_INVALID",0xC00A0012L},
           {"The system has reached its licensed logon limit."
"Please try again later."    ,"STATUS_CTX_LICENSE_NOT_AVAILABLE",0xC00A0013L},
           {"The system license has expired. Your logon request is denied."    ,"STATUS_CTX_LICENSE_EXPIRED",0xC00A0014L},
           {"The specified session cannot be found."    ,"STATUS_CTX_WINSTATION_NOT_FOUND",0xC00A0015L},
           {"The specified session name is already in use."    ,"STATUS_CTX_WINSTATION_NAME_COLLISION",0xC00A0016L},
           {"The requested operation cannot be completed because the Terminal Connection is currently busy processing a connect, disconnect, reset, or delete operation."    ,"STATUS_CTX_WINSTATION_BUSY",0xC00A0017L},
           {"An attempt has been made to connect to a session whose video mode is not supported by the current client."    ,"STATUS_CTX_BAD_VIDEO_MODE",0xC00A0018L},
           {"The application attempted to enable DOS graphics mode."
"DOS graphics mode is not supported."    ,"STATUS_CTX_GRAPHICS_INVALID",0xC00A0022L},
           {"The requested operation can be performed only on the system console."
"This is most often the result of a driver or system DLL requiring direct console access."    ,"STATUS_CTX_NOT_CONSOLE",0xC00A0024L},
           {"The client failed to respond to the server connect message."    ,"STATUS_CTX_CLIENT_QUERY_TIMEOUT",0xC00A0026L},
           {"Disconnecting the console session is not supported."    ,"STATUS_CTX_CONSOLE_DISCONNECT",0xC00A0027L},
           {"Reconnecting a disconnected session to the console is not supported."    ,"STATUS_CTX_CONSOLE_CONNECT",0xC00A0028L},
           {"The request to control another session remotely was denied."    ,"STATUS_CTX_SHADOW_DENIED",0xC00A002AL},
           {"A process has requested access to a session, but has not been granted those access rights."    ,"STATUS_CTX_WINSTATION_ACCESS_DENIED",0xC00A002BL},
           {"The Terminal Connection driver %1 is invalid."    ,"STATUS_CTX_INVALID_WD",0xC00A002EL},
           {"The Terminal Connection driver %1 was not found in the system path."    ,"STATUS_CTX_WD_NOT_FOUND",0xC00A002FL},
           {"The requested session cannot be controlled remotely."
"You cannot control your own session, a session that is trying to control your session,"
"a session that has no user logged on, nor control other sessions from the console."    ,"STATUS_CTX_SHADOW_INVALID",0xC00A0030L},
           {"The requested session is not configured to allow remote control."    ,"STATUS_CTX_SHADOW_DISABLED",0xC00A0031L},
           {"The RDP protocol component %2 detected an error in the protocol stream and has disconnected the client."    ,"STATUS_RDP_PROTOCOL_ERROR",0xC00A0032L},
           {"Your request to connect to this Terminal server has been rejected."
"Your Terminal Server Client license number has not been entered for this copy of the Terminal Client."
"Please call your system administrator for help in entering a valid, unique license number for this Terminal Server Client."
"Click OK to continue."    ,"STATUS_CTX_CLIENT_LICENSE_NOT_SET",0xC00A0033L},
           {"Your request to connect to this Terminal server has been rejected."
"Your Terminal Server Client license number is currently being used by another user."
"Please call your system administrator to obtain a new copy of the Terminal Server Client with a valid, unique license number."
"Click OK to continue."    ,"STATUS_CTX_CLIENT_LICENSE_IN_USE",0xC00A0034L},
           {"The remote control of the console was terminated because the display mode was changed. Changing the display mode in a remote control session is not supported."    ,"STATUS_CTX_SHADOW_ENDED_BY_MODE_CHANGE",0xC00A0035L},
           {"Remote control could not be terminated because the specified session is not currently being remotely controlled."    ,"STATUS_CTX_SHADOW_NOT_RUNNING",0xC00A0036L},
           {"A device is missing in the system BIOS MPS table. This device will not be used."
"Please contact your system vendor for system BIOS update."    ,"STATUS_PNP_BAD_MPS_TABLE",0xC0040035L},
           {"A translator failed to translate resources."    ,"STATUS_PNP_TRANSLATION_FAILED",0xC0040036L},
           {"A IRQ translator failed to translate resources."    ,"STATUS_PNP_IRQ_TRANSLATION_FAILED",0xC0040037L},
           {"Driver %2 returned invalid ID for a child device (%3)."    ,"STATUS_PNP_INVALID_ID",0xC0040038L},
           {"The requested section is not present in the activation context."    ,"STATUS_SXS_SECTION_NOT_FOUND",0xC0150001L},
           {"Windows was not able to process the application binding information."
"Please refer to your System Event Log for further information."    ,"STATUS_SXS_CANT_GEN_ACTCTX",0xC0150002L},
           {"The application binding data format is invalid."    ,"STATUS_SXS_INVALID_ACTCTXDATA_FORMAT",0xC0150003L},
           {"The referenced assembly is not installed on your system."    ,"STATUS_SXS_ASSEMBLY_NOT_FOUND",0xC0150004L},
           {"The manifest file does not begin with the required tag and format information."    ,"STATUS_SXS_MANIFEST_FORMAT_ERROR",0xC0150005L},
           {"The manifest file contains one or more syntax errors."    ,"STATUS_SXS_MANIFEST_PARSE_ERROR",0xC0150006L},
           {"The application attempted to activate a disabled activation context."    ,"STATUS_SXS_ACTIVATION_CONTEXT_DISABLED",0xC0150007L},
           {"The requested lookup key was not found in any active activation context."    ,"STATUS_SXS_KEY_NOT_FOUND",0xC0150008L},
           {"A component version required by the application conflicts with another component version already active."    ,"STATUS_SXS_VERSION_CONFLICT",0xC0150009L},
           {"The type requested activation context section does not match the query API used."    ,"STATUS_SXS_WRONG_SECTION_TYPE",0xC015000AL},
           {"Lack of system resources has required isolated activation to be disabled for the current thread of execution."    ,"STATUS_SXS_THREAD_QUERIES_DISABLED",0xC015000BL},
           {"The referenced assembly could not be found."    ,"STATUS_SXS_ASSEMBLY_MISSING",0xC015000CL},
           {"A kernel mode component is releasing a reference on an activation context."    ,"STATUS_SXS_RELEASE_ACTIVATION_CONTEXT",0x4015000DL},
           {"An attempt to set the process default activation context failed because the process default activation context was already set."    ,"STATUS_SXS_PROCESS_DEFAULT_ALREADY_SET",0xC015000EL},
           {"The activation context being deactivated is not the most recently activated one."    ,"STATUS_SXS_EARLY_DEACTIVATION",0xC015000FL},
           {"The activation context being deactivated is not active for the current thread of execution."    ,"STATUS_SXS_INVALID_DEACTIVATION",0xC0150010L},
           {"The activation context being deactivated has already been deactivated."    ,"STATUS_SXS_MULTIPLE_DEACTIVATION",0xC0150011L},
           {"The activation context of system default assembly could not be generated."    ,"STATUS_SXS_SYSTEM_DEFAULT_ACTIVATION_CONTEXT_EMPTY",0xC0150012L},
           {"A component used by the isolation facility has requested to terminate the process."    ,"STATUS_SXS_PROCESS_TERMINATION_REQUESTED",0xC0150013L},
           {"The activation context activation stack for the running thread of execution is corrupt."    ,"STATUS_SXS_CORRUPT_ACTIVATION_STACK",0xC0150014L},
           {"The application isolation metadata for this process or thread has become corrupt."    ,"STATUS_SXS_CORRUPTION",0xC0150015L},
           {"The cluster node is not valid."    ,"STATUS_CLUSTER_INVALID_NODE",0xC0130001L},
           {"The cluster node already exists."    ,"STATUS_CLUSTER_NODE_EXISTS",0xC0130002L},
           {"A node is in the process of joining the cluster."    ,"STATUS_CLUSTER_JOIN_IN_PROGRESS",0xC0130003L},
           {"The cluster node was not found."    ,"STATUS_CLUSTER_NODE_NOT_FOUND",0xC0130004L},
           {"The cluster local node information was not found."    ,"STATUS_CLUSTER_LOCAL_NODE_NOT_FOUND",0xC0130005L},
           {"The cluster network already exists."    ,"STATUS_CLUSTER_NETWORK_EXISTS",0xC0130006L},
           {"The cluster network was not found."    ,"STATUS_CLUSTER_NETWORK_NOT_FOUND",0xC0130007L},
           {"The cluster network interface already exists."    ,"STATUS_CLUSTER_NETINTERFACE_EXISTS",0xC0130008L},
           {"The cluster network interface was not found."    ,"STATUS_CLUSTER_NETINTERFACE_NOT_FOUND",0xC0130009L},
           {"The cluster request is not valid for this object."    ,"STATUS_CLUSTER_INVALID_REQUEST",0xC013000AL},
           {"The cluster network provider is not valid."    ,"STATUS_CLUSTER_INVALID_NETWORK_PROVIDER",0xC013000BL},
           {"The cluster node is down."    ,"STATUS_CLUSTER_NODE_DOWN",0xC013000CL},
           {"The cluster node is not reachable."    ,"STATUS_CLUSTER_NODE_UNREACHABLE",0xC013000DL},
           {"The cluster node is not a member of the cluster."    ,"STATUS_CLUSTER_NODE_NOT_MEMBER",0xC013000EL},
           {"A cluster join operation is not in progress."    ,"STATUS_CLUSTER_JOIN_NOT_IN_PROGRESS",0xC013000FL},
           {"The cluster network is not valid."    ,"STATUS_CLUSTER_INVALID_NETWORK",0xC0130010L},
           {"No network adapters are available."    ,"STATUS_CLUSTER_NO_NET_ADAPTERS",0xC0130011L},
           {"The cluster node is up."    ,"STATUS_CLUSTER_NODE_UP",0xC0130012L},
           {"The cluster node is paused."    ,"STATUS_CLUSTER_NODE_PAUSED",0xC0130013L},
           {"The cluster node is not paused."    ,"STATUS_CLUSTER_NODE_NOT_PAUSED",0xC0130014L},
           {"No cluster security context is available."    ,"STATUS_CLUSTER_NO_SECURITY_CONTEXT",0xC0130015L},
           {"The cluster network is not configured for internal cluster communication."    ,"STATUS_CLUSTER_NETWORK_NOT_INTERNAL",0xC0130016L},
           {"The cluster node has been poisoned."    ,"STATUS_CLUSTER_POISONED",0xC0130017L},
           {"Log service found an invalid log sector."    ,"STATUS_LOG_SECTOR_INVALID",0xC01A0001L},
           {"Log service encountered a log sector with invalid block parity."    ,"STATUS_LOG_SECTOR_PARITY_INVALID",0xC01A0002L},
           {"Log service encountered a remapped log sector."    ,"STATUS_LOG_SECTOR_REMAPPED",0xC01A0003L},
           {"Log service encountered a partial or incomplete log block."    ,"STATUS_LOG_BLOCK_INCOMPLETE",0xC01A0004L},
           {"Log service encountered an attempt access data outside the active log range."    ,"STATUS_LOG_INVALID_RANGE",0xC01A0005L},
           {"Log service user log marshalling buffers are exhausted."    ,"STATUS_LOG_BLOCKS_EXHAUSTED",0xC01A0006L},
           {"Log service encountered an attempt read from a marshalling area with an invalid read context."    ,"STATUS_LOG_READ_CONTEXT_INVALID",0xC01A0007L},
           {"Log service encountered an invalid log restart area."    ,"STATUS_LOG_RESTART_INVALID",0xC01A0008L},
           {"Log service encountered an invalid log block version."    ,"STATUS_LOG_BLOCK_VERSION",0xC01A0009L},
           {"Log service encountered an invalid log block."    ,"STATUS_LOG_BLOCK_INVALID",0xC01A000AL},
           {"Log service encountered an attempt to read the log with an invalid read mode."    ,"STATUS_LOG_READ_MODE_INVALID",0xC01A000BL},
           {"Log service encountered a log stream with no restart area."    ,"STATUS_LOG_NO_RESTART",0x401A000CL},
           {"Log service encountered a corrupted metadata file."    ,"STATUS_LOG_METADATA_CORRUPT",0xC01A000DL},
           {"Log service encountered a metadata file that could not be created by the log file system."    ,"STATUS_LOG_METADATA_INVALID",0xC01A000EL},
           {"Log service encountered a metadata file with inconsistent data."    ,"STATUS_LOG_METADATA_INCONSISTENT",0xC01A000FL},
           {"Log service encountered an attempt to erroneously allocate or dispose reservation space."    ,"STATUS_LOG_RESERVATION_INVALID",0xC01A0010L},
           {"Log service cannot delete log file or file system container."    ,"STATUS_LOG_CANT_DELETE",0xC01A0011L},
           {"Log service has reached the maximum allowable containers allocated to a log file."    ,"STATUS_LOG_CONTAINER_LIMIT_EXCEEDED",0xC01A0012L},
           {"Log service has attempted to read or write backwards past the start of the log."    ,"STATUS_LOG_START_OF_LOG",0xC01A0013L},
           {"Log policy could not be installed because a policy of the same type is already present."    ,"STATUS_LOG_POLICY_ALREADY_INSTALLED",0xC01A0014L},
           {"Log policy in question was not installed at the time of the request."    ,"STATUS_LOG_POLICY_NOT_INSTALLED",0xC01A0015L},
           {"The installed set of policies on the log is invalid."    ,"STATUS_LOG_POLICY_INVALID",0xC01A0016L},
           {"A policy on the log in question prevented the operation from completing."    ,"STATUS_LOG_POLICY_CONFLICT",0xC01A0017L},
           {"Log space cannot be reclaimed because the log is pinned by the archive tail."    ,"STATUS_LOG_PINNED_ARCHIVE_TAIL",0xC01A0018L},
           {"Log record is not a record in the log file."    ,"STATUS_LOG_RECORD_NONEXISTENT",0xC01A0019L},
           {"Number of reserved log records or the adjustment of the number of reserved log records is invalid."    ,"STATUS_LOG_RECORDS_RESERVED_INVALID",0xC01A001AL},
           {"Reserved log space or the adjustment of the log space is invalid."    ,"STATUS_LOG_SPACE_RESERVED_INVALID",0xC01A001BL},
           {"A new or existing archive tail or base of the active log is invalid."    ,"STATUS_LOG_TAIL_INVALID",0xC01A001CL},
           {"Log space is exhausted."    ,"STATUS_LOG_FULL",0xC01A001DL},
           {"The log could not be set to the requested size."    ,"STATUS_COULD_NOT_RESIZE_LOG",0x80190009L},
           {NULL,NULL,0},
};


