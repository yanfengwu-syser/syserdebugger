#include "stdafx.h"
#include "Syser.h"

bool bShowCommandTitle;
bool bShowDebugInfo;

int objdir_command(int argc, WCHAR *argv[],PCWSTR szCommandLine,CSyser*pSyser)
{
	WISP_CHAR TypeName[65],ObjectName[65];
	OBJFINDDATA FindData;
	DWORD dwObjectCounter;
	DWORD dwDir;
	PWSTR pCmdLine;
	DWORD ObjectHeader;
	bool	bTitle = false;
	dwDir=dwObjectRootDirectory;
	dwObjectCounter=0;

	if(argc>2)//有可能对象名中间带空
	{
		pCmdLine=TStrIStr(szCommandLine,"objdir");
		if(pCmdLine==NULL)
			argc=1;
		else
		{
			pCmdLine+=6;
			while(*pCmdLine==' ' || *pCmdLine=='\t')
				pCmdLine++;
			argv[1]=pCmdLine;
		}

		argc=2;
	}

	if(argc==2)
	{			
		dwDir = GetObjectDirectoryHandleByName(argv[1]);
		if(dwDir==0)
		{
			if(CALCEXP(argv[1],&ObjectHeader)==FALSE)
				return 1;
			dwDir=ObjectHeader;
		}
	}
	if(IsDirectoryObjectType(dwDir))
	{
		FindData.ObjectHandle=dwDir;
		FindData.NextObjectPointer=NULL;
		FindData.DirectoryItemIndex=0;
		while(FindNextObject(FindData))
		{
			if(bTitle==false)
			{
				OUTPUT(WSTR("Object   ObjHdr   %-40s%-20s\n"),WSTR("Name"),WSTR("Type"));
				bTitle=true;
			}
			dwObjectCounter++;
			GetObjectTypeName(FindData.ReturnObjectHandle,TypeName);	
			GetObjectName(FindData.ReturnObjectHandle,ObjectName);
			ObjectHeader = GetObjectHeader(FindData.ReturnObjectHandle);
			OUTPUT(WSTR("%08x %08x %-40s%-20s\n"),FindData.ReturnObjectHandle, ObjectHeader,ObjectName,TypeName);
		}
		OUTPUT(WSTR("%d Object(s)" ),dwObjectCounter);
		return 0;
	}
	else
	{
		OUTPUT(WSTR("Object   ObjHdr   %-40s%-20s\n"),WSTR("Name"),WSTR("Type"));
		GetObjectTypeName(dwDir,TypeName);	
		GetObjectName(dwDir,ObjectName);
		ObjectHeader = GetObjectHeader(dwDir);
		OUTPUT(WSTR("%08x %08x %-40s%-20s\n"),dwDir,ObjectHeader,ObjectName,TypeName);
	}
	return 0;
}


bool DeviceCommandCallBack(DWORD ObjectHandle,WISP_CHAR**Name)
{
	WISP_CHAR ObjectName[65];
	WISP_CHAR DisplayFormat[]=WSTR("%08X %08X %08X %08X %08X %08X %s\n");
	bool bFound=false;
	PDEVICE_OBJECT DeviceObject;
	DWORD          dwValue;

	if(bShowCommandTitle)
	{
		OUTPUT(WSTR("RefCnt   DrvObj   NextDev  AttDev   CurIrp   DevExten Name\n"));
		bShowCommandTitle=false;
	}			
	DeviceObject=*(PDEVICE_OBJECT*)&ObjectHandle;
	GetObjectName(ObjectHandle,ObjectName);	
	if(Name)
	{
		if( USHexStrToNum(Name[0], &dwValue) )
		{
			if(dwValue == (DWORD)DeviceObject)
			     bFound=true;
		}
		else
		{
			if(TIMatchWithPattern(Name[0], ObjectName))
			{
				bFound=true;
			}
		}
		if(bFound==false)
			return true;
	}
	dwListObjectCounter++;
	OUTPUT(DisplayFormat,
		DeviceObject->ReferenceCount,
		DeviceObject->DriverObject,
		DeviceObject->NextDevice,
		DeviceObject->AttachedDevice,
		DeviceObject->CurrentIrp,
		DeviceObject->DeviceExtension,
		ObjectName
		);
	if(bFound)
	{
		if( TStrChr(Name[0], WISP_CHAR('*')) || TStrChr(Name[0], WISP_CHAR('?')) )
			return true;
		WISP_CHAR* DeviceTypeName[]=
		{
			WSTR(""),
			WSTR("FILE_DEVICE_BEEP"),
			WSTR("FILE_DEVICE_CD_ROM"),
			WSTR("FILE_DEVICE_CD_ROM_FILE_SYSTEM"),			
			WSTR("FILE_DEVICE_CONTROLLER"),
			WSTR("FILE_DEVICE_DATALINK"),
			WSTR("FILE_DEVICE_DFS"),
			WSTR("FILE_DEVICE_DISK"),
			WSTR("FILE_DEVICE_DISK_FILE_SYSTEM"),
			WSTR("FILE_DEVICE_FILE_SYSTEM"),
			WSTR("FILE_DEVICE_INPORT_PORT"),
			WSTR("FILE_DEVICE_KEYBOARD"),
			WSTR("FILE_DEVICE_MAILSLOT"),
			WSTR("FILE_DEVICE_MIDI_IN"),
			WSTR("FILE_DEVICE_MIDI_OUT"),
			WSTR("FILE_DEVICE_MOUSE"),
			WSTR("FILE_DEVICE_MULTI_UNC_PROVIDER"),
			WSTR("FILE_DEVICE_NAMED_PIPE"),
			WSTR("FILE_DEVICE_NETWORK"),
			WSTR("FILE_DEVICE_NETWORK_BROWSER"),
			WSTR("FILE_DEVICE_NETWORK_FILE_SYSTEM"),
			WSTR("FILE_DEVICE_NULL"),
			WSTR("FILE_DEVICE_PARALLEL_PORT"),
			WSTR("FILE_DEVICE_PHYSICAL_NETCARD"),
			WSTR("FILE_DEVICE_PRINTER"),
			WSTR("FILE_DEVICE_SCANNER"),
			WSTR("FILE_DEVICE_SERIAL_MOUSE_PORT"),
			WSTR("FILE_DEVICE_SERIAL_PORT"),
			WSTR("FILE_DEVICE_SCREEN"),
			WSTR("FILE_DEVICE_SOUND"),
			WSTR("FILE_DEVICE_STREAMS"),
			WSTR("FILE_DEVICE_TAPE"),
			WSTR("FILE_DEVICE_TAPE_FILE_SYSTEM"),
			WSTR("FILE_DEVICE_TRANSPORT"),
			WSTR("FILE_DEVICE_UNKNOWN"),
			WSTR("FILE_DEVICE_VIDEO"),
			WSTR("FILE_DEVICE_VIRTUAL_DISK"),
			WSTR("FILE_DEVICE_WAVE_IN"),
			WSTR("FILE_DEVICE_WAVE_OUT"),
			WSTR("FILE_DEVICE_8042_PORT"),
			WSTR("FILE_DEVICE_NETWORK_REDIRECTOR"),
			WSTR("FILE_DEVICE_BATTERY"),
			WSTR("FILE_DEVICE_BUS_EXTENDER"),
			WSTR("FILE_DEVICE_MODEM"),
			WSTR("FILE_DEVICE_VDM"),
			WSTR("FILE_DEVICE_MASS_STORAGE"),
			WSTR("FILE_DEVICE_SMB"),
			WSTR("FILE_DEVICE_KS"),
			WSTR("FILE_DEVICE_CHANGER"),
			WSTR("FILE_DEVICE_SMARTCARD"),
			WSTR("FILE_DEVICE_ACPI"),
			WSTR("FILE_DEVICE_DVD"),
			WSTR("FILE_DEVICE_FULLSCREEN_VIDEO"),
			WSTR("FILE_DEVICE_DFS_FILE_SYSTEM"),
			WSTR("FILE_DEVICE_DFS_VOLUME"),
			WSTR("FILE_DEVICE_SERENUM"),
			WSTR("FILE_DEVICE_TERMSRV"),
			WSTR("FILE_DEVICE_KSEC"),
			WSTR("FILE_DEVICE_FIPS"),
			NULL,
		};




		WISP_CHAR FileAligment[30]=WSTR("");		
		OUTPUT(WSTR("%-20s : %08x\n"),WSTR("Timer*"),DeviceObject->Timer);
		OUTPUT(WSTR("%-20s : %08x\n"),WSTR("Flags"),DeviceObject->Flags);
		if(DeviceObject->Flags&DO_VERIFY_VOLUME)
			OUTPUT(WSTR("%-20s : %-8s %s\n"),WSTR(""),WSTR(""),WSTR("DO_VERIFY_VOLUME"));
		if(DeviceObject->Flags&DO_BUFFERED_IO)
			OUTPUT(WSTR("%-20s : %-8s %s\n"),WSTR(""),WSTR(""),WSTR("DO_BUFFERED_IO"));
		if(DeviceObject->Flags&DO_DIRECT_IO)
			OUTPUT(WSTR("%-20s : %-8s %s\n"),WSTR(""),WSTR(""),WSTR("DO_DIRECT_IO"));
		if(DeviceObject->Flags&DO_EXCLUSIVE)
			OUTPUT(WSTR("%-20s : %-8s %s\n"),WSTR(""),WSTR(""),WSTR("DO_EXCLUSIVE"));
		if(DeviceObject->Flags&DO_MAP_IO_BUFFER)
			OUTPUT(WSTR("%-20s : %-8s %s\n"),WSTR(""),WSTR(""),WSTR("DO_MAP_IO_BUFFER"));
		if(DeviceObject->Flags&DO_DEVICE_HAS_NAME)
			OUTPUT(WSTR("%-20s : %-8s %s\n"),WSTR(""),WSTR(""),WSTR("DO_DEVICE_HAS_NAME"));
		if(DeviceObject->Flags&DO_DEVICE_INITIALIZING)	
			OUTPUT(WSTR("%-20s : %-8s %s\n"),WSTR(""),WSTR(""),WSTR("DO_DEVICE_INITIALIZING"));
		if(DeviceObject->Flags&DO_SYSTEM_BOOT_PARTITION)	
			OUTPUT(WSTR("%-20s : %-8s %s\n"),WSTR(""),WSTR(""),WSTR("DO_SYSTEM_BOOT_PARTITION"));
		if(DeviceObject->Flags&DO_LONG_TERM_REQUESTS)
			OUTPUT(WSTR("%-20s : %-8s %s\n"),WSTR(""),WSTR(""),WSTR("DO_LONG_TERM_REQUESTS"));
		if(DeviceObject->Flags&DO_NEVER_LAST_DEVICE)
			OUTPUT(WSTR("%-20s : %-8s %s\n"),WSTR(""),WSTR(""),WSTR("DO_NEVER_LAST_DEVICE"));
		if(DeviceObject->Flags&DO_SHUTDOWN_REGISTERED)
			OUTPUT(WSTR("%-20s : %-8s %s\n"),WSTR(""),WSTR(""),WSTR("DO_SHUTDOWN_REGISTERED"));
		if(DeviceObject->Flags&DO_BUS_ENUMERATED_DEVICE)
			OUTPUT(WSTR("%-20s : %-8s %s\n"),WSTR(""),WSTR(""),WSTR("DO_BUS_ENUMERATED_DEVICE"));
		if(DeviceObject->Flags&DO_POWER_PAGABLE)
			OUTPUT(WSTR("%-20s : %-8s %s\n"),WSTR(""),WSTR(""),WSTR("DO_POWER_PAGABLE"));
		if(DeviceObject->Flags&DO_POWER_INRUSH)
			OUTPUT(WSTR("%-20s : %-8s %s\n"),WSTR(""),WSTR(""),WSTR("DO_POWER_INRUSH"));
		if(DeviceObject->Flags&DO_LOW_PRIORITY_FILESYSTEM)	
			OUTPUT(WSTR("%-20s : %-8s %s\n"),WSTR(""),WSTR(""),WSTR("DO_LOW_PRIORITY_FILESYSTEM"));
		OUTPUT(WSTR("%-20s : %08x\n"),WSTR("Characteristics"),DeviceObject->Characteristics);
		OUTPUT(WSTR("%-20s : %08x\n"),WSTR("Vpb*"),DeviceObject->Vpb);		
		WISP_CHAR* NameDeviceType;
		if(DeviceObject->DeviceType>sizeof(DeviceTypeName)/sizeof(DeviceTypeName[0]))
			NameDeviceType=DeviceTypeName[0];
		else
			NameDeviceType=DeviceTypeName[DeviceObject->DeviceType];
		OUTPUT(WSTR("%-20s : %-8x %s\n"),WSTR("Device Type"),DeviceObject->DeviceType,NameDeviceType);
		OUTPUT(WSTR("%-20s : %d\n"),WSTR("StackSize"),DeviceObject->StackSize);
		OUTPUT(WSTR("%-20s : %08x\n"),WSTR("&Queue"),&DeviceObject->Queue);
		
		switch(DeviceObject->AlignmentRequirement) {
		case FILE_BYTE_ALIGNMENT:
			TSPrintf(FileAligment,WSTR("FILE_BYTE_ALIGNMENT\n"));
			break;
		case FILE_WORD_ALIGNMENT:
			TSPrintf(FileAligment,WSTR("FILE_WORD_ALIGNMENT\n"));
			break;
		case FILE_LONG_ALIGNMENT:
			TSPrintf(FileAligment,WSTR("FILE_LONG_ALIGNMENT\n"));
			break;
		case FILE_QUAD_ALIGNMENT:
			TSPrintf(FileAligment,WSTR("FILE_QUAD_ALIGNMENT\n"));
			break;
		case FILE_OCTA_ALIGNMENT:
			TSPrintf(FileAligment,WSTR("FILE_OCTA_ALIGNMENT\n"));
			break;
		case FILE_32_BYTE_ALIGNMENT:
			TSPrintf(FileAligment,WSTR("FILE_32_BYTE_ALIGNMENT\n"));
			break;
		case FILE_64_BYTE_ALIGNMENT:
			TSPrintf(FileAligment,WSTR("FILE_64_BYTE_ALIGNMENT\n"));
			break;
		case FILE_128_BYTE_ALIGNMENT:
			TSPrintf(FileAligment,WSTR("FILE_128_BYTE_ALIGNMENT\n"));
			break;
		case FILE_256_BYTE_ALIGNMENT:
			TSPrintf(FileAligment,WSTR("FILE_256_BYTE_ALIGNMENT\n"));
			break;
		case FILE_512_BYTE_ALIGNMENT:
			TSPrintf(FileAligment,WSTR("FILE_512_BYTE_ALIGNMENT\n"));
			break;		
		}
		OUTPUT(WSTR("%-20s : %08x %s\n"),WSTR("AlignmentRequirement"),DeviceObject->AlignmentRequirement,FileAligment);
		OUTPUT(WSTR("%-20s : %08x\n"),WSTR("&DeviceQueue"),&DeviceObject->DeviceQueue);
		OUTPUT(WSTR("%-20s : %08x\n"),WSTR("&Dpc"),&DeviceObject->Dpc);
		OUTPUT(WSTR("%-20s : %d\n"),WSTR("ActiveThreadCount"),DeviceObject->ActiveThreadCount);
		OUTPUT(WSTR("%-20s : %08x\n"),WSTR("SecurityDescriptor*"),DeviceObject->SecurityDescriptor);
		OUTPUT(WSTR("%-20s : %08x\n"),WSTR("&DeviceLock"),&DeviceObject->DeviceLock);
		OUTPUT(WSTR("%-20s : %04x\n"),WSTR("SectorSize"),DeviceObject->SectorSize);
		OUTPUT(WSTR("%-20s : %04x\n"),WSTR("Spare1"),DeviceObject->Spare1);
		OUTPUT(WSTR("%-20s : %08x\n"),WSTR("DeviceObjectExtn*"),DeviceObject->DeviceObjectExtension);
		OUTPUT(WSTR("%-20s : %08x\n"),WSTR("Reserved*"),DeviceObject->Reserved);
	}	
	return true;
}

int device_command(int argc, WCHAR *argv[],PCWSTR szCommandLine,CSyser*pSyser)
{
	OBJFINDDATA FindData;
	bShowCommandTitle = true;
	dwListObjectCounter=0;
	if(argc==1)
		argv=NULL;
	else if(argc==2)
	{
		argv[0]=argv[1];
		argv[1]=NULL;
	}
	else
	{
		OUTPUT(WSTR("DEVICE [device-name | pdevice-object]\n"));	
		return 0;
//		for(int i=1;i < argc;i++)	
//			argv[i-1]=argv[i];		
//		argv[argc-1]=NULL;
	}
	FindFirstObject(NULL,FindData);
	ListObject(FindData,DEVICE_OBJECT_TYPE,DeviceCommandCallBack,argv);
	if(dwListObjectCounter)
		OUTPUT(WSTR("%d Object (s)\n"),dwListObjectCounter);	
	return 0;
}

//fix to the follow line for support UNC name and pdriver-object, by AllenZhang
//
bool DriverCommandCallBack(DWORD ObjectHandle,WISP_CHAR**Name)
{
	WISP_CHAR ObjectName[65];
	WISP_CHAR DisplayFormat[]=WSTR("%08X %08X %08X %08X %08X %08X %08X %s\n");
	bool bFound=false;
	PDRIVER_OBJECT DriverObject;
	DWORD          dwValue;

	DriverObject = *(PDRIVER_OBJECT*)&ObjectHandle;
	if(bShowCommandTitle)
	{
		OUTPUT(WSTR("Start    Size     DrvSect  pDrvExt  DrvInit  DrvStaIO DrvUnld  Name\n"));
		bShowCommandTitle=false;
//		bShowDebugInfo = 0;
	}	
	GetObjectName(ObjectHandle,ObjectName);	
	if(Name)
	{		
		if( USHexStrToNum(Name[0], &dwValue) )
		{
//			if(0 == bShowDebugInfo)
//			{
//				OUTPUT(WSTR("Input is(%s), dwDriverObject(%08X)\n"), Name[0], dwValue);
//				bShowDebugInfo = 1;
//			}
			if(dwValue == (DWORD)DriverObject->DriverSection)
			     bFound=true;
		}
		else
		{
			if(TIMatchWithPattern(Name[0], ObjectName))
			{
				bFound=true;
			}
		}
		if(bFound==false)
			return true;
	}
	dwListObjectCounter++;
	OUTPUT(DisplayFormat,
		DriverObject->DriverStart,
		DriverObject->DriverSize,
		DriverObject->DriverSection,
		DriverObject->DriverExtension,
		DriverObject->DriverInit,
		DriverObject->DriverStartIo,
		DriverObject->DriverUnload,
		ObjectName
		);
	if(bFound)
	{
		// add by allenzhang filter the UNC name
		if( TStrChr(Name[0], WISP_CHAR('*')) || TStrChr(Name[0], WISP_CHAR('?')) )
			return true;
		// add end
		OUTPUT(WSTR("%-16s : %08x\n"),WSTR("AddDevice"),0);
		OUTPUT(WSTR("%-16s : %08x\n"),WSTR("DeviceObject*"),DriverObject->DeviceObject);
		OUTPUT(WSTR("%-16s : %08x\n"),WSTR("Flags"),DriverObject->Flags);
		if(DriverObject->Flags&DRVO_UNLOAD_INVOKED)
			OUTPUT(WSTR("%-16s : %-8s %s\n"),WSTR(""),WSTR(""),WSTR("DRVO_UNLOAD_INVOKED"));
		if(DriverObject->Flags&DRVO_LEGACY_DRIVER)
			OUTPUT(WSTR("%-16s : %-8s %s\n"),WSTR(""),WSTR(""),WSTR("DRVO_LEGACY_DRIVER"));
		if(DriverObject->Flags&DRVO_BUILTIN_DRIVER)
			OUTPUT(WSTR("%-16s : %-8s %s\n"),WSTR(""),WSTR(""),WSTR("DRVO_BUILTIN_DRIVER"));
		if(DriverObject->Flags&DRVO_REINIT_REGISTERED)
			OUTPUT(WSTR("%-16s : %-8s %s\n"),WSTR(""),WSTR(""),WSTR("DRVO_REINIT_REGISTERED"));
		if(DriverObject->Flags&DRVO_INITIALIZED)
			OUTPUT(WSTR("%-16s : %-8s %s\n"),WSTR(""),WSTR(""),WSTR("DRVO_INITIALIZED"));
		if(DriverObject->Flags&DRVO_BOOTREINIT_REGISTERED)
			OUTPUT(WSTR("%-16s : %-8s %s\n"),WSTR(""),WSTR(""),WSTR("DRVO_BOOTREINIT_REGISTERED"));
		if(DriverObject->Flags&DRVO_LEGACY_RESOURCES)	
			OUTPUT(WSTR("%-16s : %-8s %s\n"),WSTR(""),WSTR(""),WSTR("DRVO_LEGACY_RESOURCES"));


		OUTPUT(WSTR("%-16s : %s\n"),WSTR("HardwareDatabase"),DriverObject->HardwareDatabase->Buffer);
		OUTPUT(WSTR("%-16s : %08x\n"),WSTR("FastIoDispatch*"),DriverObject->FastIoDispatch);
		WISP_CHAR* MJ_NAME[]=
		{
			WSTR("IRP_MJ_CREATE"),
			WSTR("IRP_MJ_CREATE_NAMED_PIPE"),
			WSTR("IRP_MJ_CLOSE"),
			WSTR("IRP_MJ_READ"),
			WSTR("IRP_MJ_WRITE"),
			WSTR("IRP_MJ_QUERY_INFORMATION"),
			WSTR("IRP_MJ_SET_INFORMATION"),
			WSTR("IRP_MJ_QUERY_EA"),
			WSTR("IRP_MJ_SET_EA"),
			WSTR("IRP_MJ_FLUSH_BUFFERS"),
			WSTR("IRP_MJ_QUERY_VOLUME_INFORMATION"),
			WSTR("IRP_MJ_SET_VOLUME_INFORMATION"),
			WSTR("IRP_MJ_DIRECTORY_CONTROL"),
			WSTR("IRP_MJ_FILE_SYSTEM_CONTROL"),
			WSTR("IRP_MJ_DEVICE_CONTROL"),
			WSTR("IRP_MJ_INTERNAL_DEVICE_CONTROL"),
			WSTR("IRP_MJ_SHUTDOWN"),
			WSTR("IRP_MJ_LOCK_CONTROL"),
			WSTR("IRP_MJ_CLEANUP"),
			WSTR("IRP_MJ_CREATE_MAILSLOT"),
			WSTR("IRP_MJ_QUERY_SECURITY"),
			WSTR("IRP_MJ_SET_SECURITY"),
			WSTR("IRP_MJ_POWER"),
			WSTR("IRP_MJ_SYSTEM_CONTROL"),
			WSTR("IRP_MJ_DEVICE_CHANGE"),
			WSTR("IRP_MJ_QUERY_QUOTA"),
			WSTR("IRP_MJ_SET_QUOTA"),
			WSTR("IRP_MJ_PNP"),
			WSTR("IRP_MJ_PNP_POWER"),
			NULL,	
		};
		
		DWORD tmpvar,tmp1var;
		tmp1var=*(DWORD*) &DriverObject->DriverStart;
		for(int i = 0; i <= IRP_MJ_MAXIMUM_FUNCTION;i++)
		{
			tmpvar=*(DWORD*) &DriverObject->MajorFunction[i];
			if(tmpvar>tmp1var && tmpvar<tmp1var+DriverObject->DriverSize)
				OUTPUT(WSTR("%-35s at 8:%08x\n"),MJ_NAME[i],tmpvar);
			else
			{
				if(tmpvar!=(DWORD)gDefaultPDriverDispatch)
				{
					OUTPUT(WSTR("%<b>%-35s at 8:%08x\n"),MJ_NAME[i],tmpvar);
				}
			}
		}		
	}
	return true;
}

int driver_command(int argc, WCHAR *argv[],PCWSTR szCommandLine,CSyser*pSyser)
{
	OBJFINDDATA FindData;
	bShowCommandTitle=true;
	dwListObjectCounter=0;
	if(argc==1)
		argv=NULL;
	else if(argc==2)
	{
		argv[0]=argv[1];
		argv[1]=NULL;
	}
	else
	{
		OUTPUT(WSTR("DRIVER [driver-name | pdriver-object] Object\n"));	
		return 0;
	}	
	FindFirstObject(NULL,FindData);
	ListObject(FindData,DRIVER_OBJECT_TYPE,DriverCommandCallBack,argv);
	if(dwListObjectCounter)
		OUTPUT(WSTR("%d Object (s)\n"),dwListObjectCounter);	
	return 0;
}

int apc_command(int argc, WCHAR *argv[],PCWSTR szCommandLine,CSyser*pSyser)
{
	OUTPUT(WSTR("Function not implemented\n"));
	return 0;
}

bool KmutexCommandCallBack(DWORD ObjectHandle,WISP_CHAR**Name)
{
	WISP_CHAR ObjectName[65];
	WISP_CHAR DisplayFormat[]=WSTR("%08X %s %8x(%3x) %s %x  %s\n");
	PKMUTANT KMutantObject;

	if(bShowCommandTitle)
	{
		OUTPUT(WSTR("Address  State     Own.KTEB(PIT) Aban APC  Name\n"));
		bShowCommandTitle=false;
	}
	KMutantObject = *(PKMUTANT*)&ObjectHandle;
	dwListObjectCounter++;
	GetObjectName(ObjectHandle,ObjectName);
	OUTPUT(DisplayFormat,ObjectHandle,KMutantObject->Header.SignalState?WSTR("Signalled"):WSTR("Clear    "),KMutantObject->OwnerThread,0,KMutantObject->Abandoned?WSTR("Y  "):WSTR("N  "),KMutantObject->ApcDisable,ObjectName);
	return true;
}

int kmutex_command(int argc, WCHAR *argv[],PCWSTR szCommandLine,CSyser*pSyser)
{
	OBJFINDDATA FindData;
	bShowCommandTitle = true;
	dwListObjectCounter=0;
	if(argc==1)
		argv=NULL;
	else
	{
		for(int i=1;i < argc;i++)	
			argv[i-1]=argv[i];		
		argv[argc-1]=NULL;
	}
	FindFirstObject(NULL,FindData);
	ListObject(FindData,MUTANT_OBJECT_TYPE,KmutexCommandCallBack,argv);
	OUTPUT(WSTR("%d Object (s)\n"),dwListObjectCounter);
	return 0;
}

bool KeventCommandCallBack(DWORD ObjectHandle,WISP_CHAR**Name)
{
	WISP_CHAR ObjectName[65];
	WISP_CHAR DisplayFormat[]=WSTR("%08X %s %s %s\n");
	WISP_CHAR *EventType[] ={ WSTR("Notification"),WSTR("Kernel      "),WSTR("Unknown      "),};
	PKEVENT KEventObject;
	BYTE EventTypeId;

	if(bShowCommandTitle)
	{
		OUTPUT(WSTR("Address  Type         State     Name\n"));
		bShowCommandTitle=false;
	}
	KEventObject = *(PKEVENT*)&ObjectHandle;
	dwListObjectCounter++;
	GetObjectName(ObjectHandle,ObjectName);
	EventTypeId = ReadByteDefaultValue(*(DWORD**)&ObjectHandle,0xff);
	if(EventTypeId != ReadByteDefaultValue(*(DWORD**)&ObjectHandle,0xf0))
		EventTypeId=2;
	if(EventTypeId>2)
		EventTypeId=2;
	OUTPUT(DisplayFormat,ObjectHandle,EventType[EventTypeId],KEventObject->Header.SignalState?WSTR("Signalled"):WSTR("Clear    "),ObjectName);
	return true;
}
int kevent_command(int argc, WCHAR *argv[],PCWSTR szCommandLine,CSyser*pSyser)
{
	OBJFINDDATA FindData;
	bShowCommandTitle = true;
	dwListObjectCounter=0;
	if(argc==1)
		argv=NULL;
	else
	{
		for(int i=1;i < argc;i++)	
			argv[i-1]=argv[i];		
		argv[argc-1]=NULL;
	}
	FindFirstObject(NULL,FindData);
	ListObject(FindData,EVENT_OBJECT_TYPE,KeventCommandCallBack,argv);
	OUTPUT(WSTR("%d Object (s)"),dwListObjectCounter);
	return 0;
}
bool KsemCommandCallBack(DWORD ObjectHandle,WISP_CHAR**Name)
{
	WISP_CHAR ObjectName[65];
	WISP_CHAR DisplayFormat[]=WSTR("%08X %08X %s %s\n");		
	PKSEMAPHORE KSemaphoreObject;
	
	if(bShowCommandTitle)
	{
		OUTPUT(WSTR("Address  Limit    State     Name\n"));
		bShowCommandTitle=false;
	}
	KSemaphoreObject = *(PKSEMAPHORE*)&ObjectHandle;
	dwListObjectCounter++;		
	GetObjectName(ObjectHandle,ObjectName);		
	OUTPUT(DisplayFormat,ObjectHandle,KSemaphoreObject->Limit,KSemaphoreObject->Header.SignalState?WSTR("Signalled"):WSTR("Clear    "),ObjectName);
	return true;	
}
int ksem_command(int argc, WCHAR *argv[],PCWSTR szCommandLine,CSyser*pSyser)
{
	OBJFINDDATA FindData;
	bShowCommandTitle = true;
	dwListObjectCounter=0;
	if(argc==1)
		argv=NULL;
	else
	{
		for(int i=1;i < argc;i++)	
			argv[i-1]=argv[i];		
		argv[argc-1]=NULL;
	}
	FindFirstObject(NULL,FindData);
	ListObject(FindData,SEMAPHORE_OBJECT_TYPE,KsemCommandCallBack,argv);
	OUTPUT(WSTR("%d Object (s)\n"),dwListObjectCounter);
	return 0;
}
