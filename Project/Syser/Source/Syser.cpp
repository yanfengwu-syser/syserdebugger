#include "StdAfx.h"
#include "Syser.h"
#include "ObjectDirectory.h"
#include "SyserConfig.h"
#include "VideoDriver.h"
#include "Interrupt2D.h"
#include "SyserSymAnalyzer.h"
#include "Mouse.h"
#include "syserdrivermc.h"
#include "Int0xe.h"
#include "VMWareSupport.h"
#include "VirtualPCSupport.h"
#include "OSProcessThread.h"

DWORD dwgErrorCode=0;

void*	CorrectVideoBuffer = NULL;
SIZE_T	CorrectVideoBufSize = 0;

DWORD* LoadCFGHotKey()
{
	DWORD* Buffer=new DWORD[0x10000/sizeof(DWORD)];
	int i,j,nRealLen;
	DWORD* pEndbuffer;
	if(Buffer==NULL)
		return NULL;
	pEndbuffer=Buffer;
	if(LoadSyserHotKeyDriver(WSTR("Syser"),WSTR("SyserHotKey.cfg"),Buffer,0x10000,&nRealLen)==false)
	{		
		pEndbuffer++;//skip crc
		pEndbuffer++;//skip total number
		for(i=0,j=0;gDefaultHotkeyInfo[i].KeyName;i++)
		{
			*pEndbuffer++=gDefaultHotkeyInfo[i].CommandID;
			*pEndbuffer++=1;
			*pEndbuffer++=gDefaultHotkeyInfo[i].FuncKeyCode;
			*pEndbuffer++=gDefaultHotkeyInfo[i].SecondKeyCode;
		}
		Buffer[1]=i;
		*pEndbuffer++=0;
		*pEndbuffer++=0;
		*pEndbuffer++=0;
		*pEndbuffer++=0;
		DbgPrint("Syser : Load Default HotKey configure ok!\n");
	}
	else
		DbgPrint("Syser : Load HotKey configure ok!\n");
	return Buffer;
}

void LoadCFGDriver()
{
	if(LoadSyserOptionDriver(WSTR("Syser"),WSTR("Syser.cfg"),&SyserOption,sizeof(SyserOption))==false)
	{
		if(SaveSyserOptionDriver(WSTR("Syser"),WSTR("Syser.cfg"),&OrgSyserOption,sizeof(OrgSyserOption)))
			::DbgPrint("Syser : Save default Syser.cfg\n");
		else
			::DbgPrint("Syser : Fail to save default Syser.cfg\n");
		SyserOption = OrgSyserOption;
		if(SyserOption.iKeyboardLayer != 0 && SyserOption.iKeyboardLayer != 1)//由于要用这个值做数组索引所以要检测合法性
			SyserOption.iKeyboardLayer = 0;
	}
}

void LoadColorCFGDriver()
{
	if(LoadSyserOptionDriver(WSTR("Syser"),WSTR("SyserColor.cfg"),&ColorOption,sizeof(ColorOption))==false)
	{
		if(SaveSyserOptionDriver(WSTR("Syser"),WSTR("SyserColor.cfg"),&OrgColorOption,sizeof(OrgColorOption)))
			::DbgPrint("Syser : Save default SyserColor.cfg\n");
		else
			::DbgPrint("Syser : Fail to save default SyserColor.cfg\n");
		ColorOption = OrgColorOption;
	}
}

bool EnterOnLoadSyserDriver()
{
	InitObjectDirectory();
	InitInterruptStub();
	LoadCFGDriver();
	LoadColorCFGDriver();
//////////////////////////////////////////////////////////////
//建立通用堆
	MIN_LIMIT(SyserOption.iHeapSizeM,MIN_MAIN_HEAP);
	MAX_LIMIT(SyserOption.iHeapSizeM,MAX_MAIN_HEAP);
	gMainHeapSize = SyserOption.iHeapSizeM*0x100000;
	char*testpt = new char;
	if(testpt==NULL)
	{
		::DbgPrint("Syser : Create Syser Heap Fail ()!\n");
		return false;
	}
	delete testpt;
//建立通用堆
//////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////
//建立屏幕堆
	int VideoHeapSize = (SyserOption.iMaxWndWidth*SyserOption.iMaxWndHeight*sizeof(COLORREF)+CHUNK_SIZE)*2;
	gpUserHeap[SYSER_SCREEN_HEAP] = new CFixedHeap;
	gpUserHeap[SYSER_SCREEN_HEAP]->Create(VideoHeapSize);
	gMaxUserHeapCount++;
//建立屏幕堆
//////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////
//建立原代码堆
	MIN_LIMIT(SyserOption.iSourceCodeHeapSizeM,MIN_SOURCE_CODE_HEAP);
	MAX_LIMIT(SyserOption.iSourceCodeHeapSizeM,MAX_SOURCE_CODE_HEAP);
	gpUserHeap[SYSER_SOURCE_DEBUG_HEAP] = new CFixedHeap;
	gMaxUserHeapCount++;

//建立原代码堆
//////////////////////////////////////////////////////////////
	SyserInitSystemSegmentRegister();
	if(InitMultiCPUInformation()==false)
	{
		::DbgPrint("Syser : Initialize CPU Information Error!\n");
		return false;
	}
	if(MapPhysical0()==false)
	{
		::DbgPrint("Syser : Map Physical Address 0 Error!\n");
	}
	InitCPUIDInfo();
	VMWareTest();
	VirtualPCTest();
	if(gInt0xeHook==false)
	{
		gInt0xeHook = InstallInterruptHandle(0xe,(VADDR32)SyserInt0eProc);
		gSyserInt0eAddress = GetCurrentCPUInterruptProcAddress(0xe);
	}
	if(InitPsActiveProcessHead()==false)
		::DbgPrint("Syser : Initialize PsActiveProcessHead error!");
	dwgErrorCode=6;
	return true;
}

void LeaveOnLoadSyserDriverFail(IN PDRIVER_OBJECT DriverObject)
{
	if(gInt0xeHook==true)
	{
		if(UninstallInterruptHandle(0xe))
			gInt0xeHook=false;
	}
	UnmapPhysical0();
	ReleaseCPUIDInfo();
	UNICODE_STRING SymbolicLinkName;
	RtlInitUnicodeString(&SymbolicLinkName,SYSER_LINK_NAME);
	if(DriverObject->DeviceObject)
	{
		IoDeleteDevice(DriverObject->DeviceObject);
		IoDeleteSymbolicLink(&SymbolicLinkName);
	}
	ReleaseMemoryAllocUserHeap();
	::DbgPrint("Syser : Fail to load syser driver!\n");
}

void LeaveOnLoadSyserDriverSuccess()
{
}

void OnUnloadSyserDriver()
{
	if(gInt0xeHook==true)
	{
		if(UninstallInterruptHandle(0xe))
			gInt0xeHook=false;
	}
	UnmapPhysical0();
	ReleaseCPUIDInfo();
	ReleaseMemoryAllocUserHeap();
}

NTSTATUS MJFunction(IN PDEVICE_OBJECT DeviceObject,IN PIRP  Irp)
{
	Irp->IoStatus.Status = STATUS_SUCCESS;
	IoCompleteRequest(Irp,IO_NO_INCREMENT);
	return STATUS_SUCCESS;
}

NTSTATUS SyserDeviceCreate(IN PDEVICE_OBJECT DeviceObject,IN PIRP Irp)
{
	UNICODE_STRING Name;
	Irp->IoStatus.Status = STATUS_SUCCESS;
	Irp->IoStatus.Information = FILE_OPENED;
	IoCompleteRequest(Irp,IO_NO_INCREMENT);
	return STATUS_SUCCESS;
}

NTSTATUS SyserDeviceClose(IN PDEVICE_OBJECT DeviceObject,IN PIRP Irp)
{
	Irp->IoStatus.Status = STATUS_SUCCESS;
	Irp->IoStatus.Information = FILE_OPENED;
	IoCompleteRequest(Irp,IO_NO_INCREMENT);
	return STATUS_SUCCESS;
}

NTSTATUS SyserShutDown(IN PDEVICE_OBJECT DeviceObject,IN PIRP Irp)
{
	if(gCPUNumbers>1)
	{//reset和关机挂了中断2有问题，ShutDown时先卸掉
		gpSyser->m_pDebugger->RemoveAllCodeBP();
		gpSyser->m_pDebugger->RemoveAllDataBP();
		UninstallInterruptHandle(0x2);
	}
	if(gpSyser)
	{
		if(gpSyserCfg->m_PS2MouseType!=dwMousePrePackageSize)
			gpSyserCfg->WriteDwordValue(PS2MOUSE_TYPE,dwMousePrePackageSize);
	}
	Irp->IoStatus.Status = STATUS_SUCCESS;
	IoCompleteRequest(Irp,IO_NO_INCREMENT);
	return STATUS_SUCCESS;
}

NTSTATUS SyserDeviceRead(IN PDEVICE_OBJECT DeviceObject,IN PIRP Irp)
{
	KIRQL OldIRQL;
	int	Size;
	PIO_STACK_LOCATION pCurStack;
	pCurStack = IoGetCurrentIrpStackLocation(Irp);
	Size = 0;
	Irp->IoStatus.Status = STATUS_SUCCESS;
	Irp->IoStatus.Information = Size;
	IoCompleteRequest(Irp,IO_NO_INCREMENT);
	return STATUS_SUCCESS;
}

void SyserDeviceControlDebugProcess(PIO_STACK_LOCATION IOStack,PIRP Irp)
{
	CDbgProcess*pProcess;
	SYSER_DEBUG_PROCESS*pSyserDbgProc;
	pSyserDbgProc = (SYSER_DEBUG_PROCESS*)Irp->AssociatedIrp.SystemBuffer;
	if(IOStack->Parameters.DeviceIoControl.InputBufferLength!=sizeof(SYSER_DEBUG_PROCESS)||Irp->AssociatedIrp.SystemBuffer==NULL)
	{
		Irp->IoStatus.Status = STATUS_INVALID_PARAMETER;
		return;
	}
	pProcess = gpSyser->m_SysInfo.GetProcess(pSyserDbgProc->ProcessID);
	if(pProcess==NULL)
	{
		::DbgPrint("Syser : Fail to set BP Invaild PID %04X\n",pSyserDbgProc->ProcessID);
		return;
	}
	gpSyser->m_SyserUI.InsertLoadBP(pSyserDbgProc->ExeFullPathName,BP_TYPE_DEBUG|BP_TYPE_ONCE,BP_STATE_ENABLE);
	CSDSModule*pSDSModule=gpSyser->m_SyserUI.LoadSDSModule(pSyserDbgProc->SymbolFileName);
	if(pSDSModule && (pSyserDbgProc->Style & SDP_AUTO_UNLOAD_SDS))
	{
		pSDSModule->m_ParentPID = pSyserDbgProc->ProcessID;
	}
}

void SyserDeviceControlLoadDriver(PIO_STACK_LOCATION IOStack,PIRP Irp)
{
	PSYSER_DEBUG_DRIVER pSyserDebugDriver;
	if(IOStack->Parameters.DeviceIoControl.InputBufferLength!=sizeof(SYSER_DEBUG_DRIVER)||Irp->AssociatedIrp.SystemBuffer==NULL)
	{
		Irp->IoStatus.Status = STATUS_INVALID_PARAMETER;
		return;
	}
	pSyserDebugDriver = (PSYSER_DEBUG_DRIVER)Irp->AssociatedIrp.SystemBuffer;
	pSyserDebugDriver->DriverPathName[sizeof(pSyserDebugDriver->DriverPathName)-1]=0;
	gpSyser->m_SyserUI.InsertLoadBP(pSyserDebugDriver->DriverPathName,BP_TYPE_DEBUG|BP_TYPE_ONCE,BP_STATE_ENABLE);
	pSyserDebugDriver->SymbolFileName[sizeof(pSyserDebugDriver->SymbolFileName)-1]=0;
	CSDSModule*pSDSModule=gpSyser->m_SyserUI.LoadSDSModule(pSyserDebugDriver->SymbolFileName);
	if(pSDSModule && (pSyserDebugDriver->Style & SDP_AUTO_UNLOAD_SDS))
		pSDSModule->m_ParentPID = gpSyser->m_pSysDebugger->m_PID;
}

void SyserDeviceControlLoadSDS(PIO_STACK_LOCATION IOStack,PIRP Irp)
{
	PSYSER_LOAD_SYMBOL_MODULE pLoadSymbolModule;
	if(IOStack->Parameters.DeviceIoControl.InputBufferLength!=sizeof(SYSER_LOAD_SYMBOL_MODULE)||Irp->AssociatedIrp.SystemBuffer==NULL)
	{
		Irp->IoStatus.Status = STATUS_INVALID_PARAMETER;
		return;
	}
	pLoadSymbolModule=(PSYSER_LOAD_SYMBOL_MODULE)Irp->AssociatedIrp.SystemBuffer;
	pLoadSymbolModule->SymbolModuleName[sizeof(pLoadSymbolModule->SymbolModuleName)-1]=0;
	gpSyser->m_SyserUI.LoadSDSModule(pLoadSymbolModule->SymbolModuleName);
}

void SyserDeviceControlUnloadSDS(PIO_STACK_LOCATION IOStack,PIRP Irp)
{
	PSYSER_UNLOAD_SYMBOL_MODULE pUnloadSymbolModule;
	if(IOStack->Parameters.DeviceIoControl.InputBufferLength!=sizeof(SYSER_UNLOAD_SYMBOL_MODULE)||Irp->AssociatedIrp.SystemBuffer==NULL)
	{
		Irp->IoStatus.Status = STATUS_INVALID_PARAMETER;
		return;
	}
	pUnloadSymbolModule = (PSYSER_UNLOAD_SYMBOL_MODULE)Irp->AssociatedIrp.SystemBuffer;
	pUnloadSymbolModule->SymbolModuleName[sizeof(pUnloadSymbolModule->SymbolModuleName)-1]=0;
	for(CSDSModuleMap::IT Iter = gpSyser->m_SyserUI.m_SDSModuleMap.Begin();Iter.IsExist();Iter++)
	{
		if(TStrICmp(pUnloadSymbolModule->SymbolModuleName,(PCSTR)Iter->m_SymbolFileName)==0)
		{
			gpSyser->m_SyserUI.UnloadSDSModule(&(*Iter));
			return;
		}
	}
}

void SyserDeviceControlLoadExportSymbol(PIO_STACK_LOCATION IOStack,PIRP Irp)
{
	CSymbolModule*pSymbolModule;
	CHAR szFileName[MAX_FN_LEN];
	char* pBuf;
	if(Irp->AssociatedIrp.SystemBuffer==NULL || IOStack->Parameters.DeviceIoControl.InputBufferLength==0)
	{
		Irp->IoStatus.Status = STATUS_INVALID_PARAMETER;
		return;
	}
	pBuf=(char*)Irp->AssociatedIrp.SystemBuffer;
	pBuf[IOStack->Parameters.DeviceIoControl.InputBufferLength-1]=0;	
	TStrCpy(szFileName,"\\??\\");
	TStrCpyLimit(&szFileName[4],pBuf,MAX_FN_LEN-4);
	if(pSymbolModule=gpSyser->m_SyserUI.LoadPESym(szFileName))
	{
		pSymbolModule->m_ReferenceCount++;//引用计数+1,保证不被释放
		DbgPrint("Syser : Load module export symbols %s\n",szFileName);
	}
	else
		DbgPrint("Syser : Fail to load module export symbols %s\n",szFileName);
}

void SyserDeviceControlLoadIDAMap(PIO_STACK_LOCATION IOStack,PIRP Irp)
{
	PSYSER_LOAD_IDA_MAPFILE pIDAMapFile;
	CSymbolModule*pSymbolModule;
	CHAR IDAMapFile[MAX_FN_LEN];
	CHAR ModuleName[MAX_FN_LEN];

	if(IOStack->Parameters.DeviceIoControl.InputBufferLength!=sizeof(SYSER_LOAD_IDA_MAPFILE) || Irp->AssociatedIrp.SystemBuffer==NULL)
	{
		Irp->IoStatus.Status = STATUS_INVALID_PARAMETER;
		return;
	}
	pIDAMapFile=(PSYSER_LOAD_IDA_MAPFILE)Irp->AssociatedIrp.SystemBuffer;
	pIDAMapFile->IDAMapFile[sizeof(pIDAMapFile->IDAMapFile)-1]=0;
	TStrCpy(IDAMapFile,"\\??\\");
	TStrCpyLimit(&IDAMapFile[4],pIDAMapFile->IDAMapFile,MAX_FN_LEN-4);
	TStrCpy(ModuleName,"\\??\\");
	pIDAMapFile->ModuleName[sizeof(pIDAMapFile->ModuleName)-1]=0;
	TStrCpyLimit(&ModuleName[4],pIDAMapFile->ModuleName,MAX_FN_LEN-4);
	if(pSymbolModule=gpSyser->m_SyserUI.LoadIDAMapFile(IDAMapFile,ModuleName))
	{
		pSymbolModule->m_ReferenceCount++;//引用计数+1,保证不被释放
		DbgPrint("Syser : Load module IDA Map file %s\n",IDAMapFile);
	}
	else
		DbgPrint("Syser : Fail to load module IDA Map file %s\n",IDAMapFile);
}

void SyserDeviceQuerySDS(PIO_STACK_LOCATION IOStack,PIRP Irp)
{
	PSYSER_QUER_SDS pSyserQuerSDS;
	bool bSDSLoadStat;
	if(IOStack->Parameters.DeviceIoControl.InputBufferLength!=sizeof(SYSER_QUER_SDS)||Irp->AssociatedIrp.SystemBuffer==NULL)
	{
		Irp->IoStatus.Status = STATUS_INVALID_PARAMETER;
		return;
	}
	pSyserQuerSDS = (PSYSER_QUER_SDS)Irp->AssociatedIrp.SystemBuffer;
	bSDSLoadStat = gpSyser->m_SyserUI.QuerySDS(pSyserQuerSDS);
	*(bool*)Irp->AssociatedIrp.SystemBuffer=bSDSLoadStat;
	Irp->IoStatus.Information=sizeof(bool);
	Irp->IoStatus.Status=STATUS_SUCCESS;
}

void SyserDeviceControlReloadConfig(PIO_STACK_LOCATION IOStack,PIRP Irp)
{
	if(gpSyser)
	{
		gpSyserCfg->LoadConfig();
		LoadCFGDriver();
		if(gpSyserCfg->m_MouseDoubleClickTimeInterval)
			gMaxDblClkInterval=gpSyserCfg->m_MouseDoubleClickTimeInterval;
		DbgPrint("Syser : Reload config!\n");
	}
}

void SyserDeviceControlReloadColorConfig(PIO_STACK_LOCATION IOStack,PIRP Irp)
{
	if(gpSyser)
	{
		LoadColorCFGDriver();
		DbgPrint("Syser : Reload color config!\n");
	}
}

void SyserDeviceControlCorrectVideoParam(PIO_STACK_LOCATION IOStack,PIRP Irp)
{
	if(gpSyser->m_RealFrameBuffer.Buffer && CorrectVideoBuffer==NULL)
		return;
	PEPROCESS Pr;
	SYSER_CORRECT_VIDEO_PARAM*pCorrectVideo;
	PHYSICAL_ADDRESS PhysAddress;
	pCorrectVideo = (SYSER_CORRECT_VIDEO_PARAM*)Irp->AssociatedIrp.SystemBuffer;
	if(IOStack->Parameters.DeviceIoControl.InputBufferLength!=sizeof(SYSER_CORRECT_VIDEO_PARAM))
	{
		Irp->IoStatus.Status = STATUS_INVALID_PARAMETER;
		return;
	}
	gpSyser->m_RealFrameBuffer.LineDistance = pCorrectVideo->Pitch;
	Pr=NULL;
	if(!NT_SUCCESS(PsLookupProcessByProcessId((HANDLE)pCorrectVideo->PID,&Pr)))
		return;
	KeAttachProcess((PRKPROCESS)Pr);
	PhysAddress = MmGetPhysicalAddress(pCorrectVideo->FrameBuffer);
	KeDetachProcess();
	ObDereferenceObject(Pr);
	if(PhysAddress.QuadPart)
	{
		if(CorrectVideoBuffer)
			MmUnmapIoSpace(CorrectVideoBuffer,CorrectVideoBufSize);
		CorrectVideoBufSize = pCorrectVideo->Pitch*pCorrectVideo->Height;
		CorrectVideoBuffer = MmMapIoSpace(PhysAddress,CorrectVideoBufSize,MmWriteCombined);
		::DbgPrint("Syser : PhysAddress = 0x%08X , Correct Video Buffer = 0x%08X\n",(DWORD)PhysAddress.QuadPart,CorrectVideoBuffer);
		::DbgPrint("Syser : Width = %08X , Height = %08X , Pitch = %08X\n",pCorrectVideo->Width,pCorrectVideo->Height,pCorrectVideo->Pitch);

		SyserFrameModeChange(pCorrectVideo->Width,pCorrectVideo->Height,pCorrectVideo->Bpp,CorrectVideoBuffer,pCorrectVideo->Pitch,0);
	}
	else
	{
		::DbgPrint("Syser : Fail to correct Video Buffer = 0x%08X PID[%04X]\n",pCorrectVideo->FrameBuffer,pCorrectVideo->PID);
	}
}


void SyserDeviceControlGetClipboard(PIO_STACK_LOCATION IOStack,PIRP Irp)
{
	char szBuffer[32];
	if(Irp->AssociatedIrp.SystemBuffer==NULL || IOStack->Parameters.DeviceIoControl.OutputBufferLength==0)
	{
		Irp->IoStatus.Status = STATUS_INVALID_PARAMETER;
		return;
	}
	int Length = UnicodeToAnsi(gpSyser->m_ClipboardString,(PSTR)Irp->AssociatedIrp.SystemBuffer,IOStack->Parameters.DeviceIoControl.OutputBufferLength);
	Irp->IoStatus.Information=Length+1;
	Irp->IoStatus.Status=STATUS_SUCCESS;
	TStrOmit((PCSTR)Irp->AssociatedIrp.SystemBuffer,szBuffer,20);
	DbgPrint("Syser : Send Clipboard [%s] to Loader\n",szBuffer);
}

void SyserDeviceControlSetClipboard(PIO_STACK_LOCATION IOStack,PIRP Irp)
{
	char szBuffer[32];
	char* pBuf;
	if(Irp->AssociatedIrp.SystemBuffer==NULL ||IOStack->Parameters.DeviceIoControl.InputBufferLength==0)
	{
		Irp->IoStatus.Status = STATUS_INVALID_PARAMETER;
		return;
	}
	pBuf=(char*)Irp->AssociatedIrp.SystemBuffer;
	pBuf[IOStack->Parameters.DeviceIoControl.InputBufferLength-1]=0;
	gpSyser->SetClipboardString((PCSTR)Irp->AssociatedIrp.SystemBuffer);
	TStrOmit((PCSTR)Irp->AssociatedIrp.SystemBuffer,szBuffer,20);
	DbgPrint("Syser : Update Clipboard [%s]\n",szBuffer);
}

void SyserDeviceControlScreenShot(PIO_STACK_LOCATION IOStack,PIRP Irp)
{
	CHAR* szBuffer;
	ULONG Length;
	if(Irp->AssociatedIrp.SystemBuffer==NULL||IOStack->Parameters.DeviceIoControl.InputBufferLength==0)
	{
		Irp->IoStatus.Status = STATUS_INVALID_PARAMETER;
		return;
	}
	szBuffer=(CHAR*)Irp->AssociatedIrp.SystemBuffer;
	szBuffer[IOStack->Parameters.DeviceIoControl.InputBufferLength-1]=0;

	if(gpSyser->SaveScreen(szBuffer))
		DbgPrint("Syser : Save ScreenShot to %s\n",szBuffer);
	else
		DbgPrint("Syser : Fail to save ScreenShot to %s\n",szBuffer);
}

void SyserDeviceSaveHistroys(PIO_STACK_LOCATION IOStack,PIRP Irp)
{
	CHAR szBuffer[MAX_FN_LEN];
	ULONG Length;
	if(Irp->AssociatedIrp.SystemBuffer==NULL)
	{
		Irp->IoStatus.Status = STATUS_INVALID_PARAMETER;
		return;
	}
	Length=IOStack->Parameters.DeviceIoControl.InputBufferLength+1;
	if(Length>MAX_FN_LEN-4)
		Length=MAX_FN_LEN-4;
	TStrCpy(szBuffer,"\\??\\");
	TStrCpyLimit(&szBuffer[4],(PCSTR)Irp->AssociatedIrp.SystemBuffer,Length);
	gpSyser->m_MainFrame.m_ConsoleWnd.SaveHistroys(szBuffer);
	DbgPrint("Syser : Save Histroys to %s\n",szBuffer);
}

void SyserDeviceSaveComments(PIO_STACK_LOCATION IOStack,PIRP Irp)
{
	gpSyser->m_SyserUI.SaveComment();
	DbgPrint("Syser : Save Comments\n");
}

NTSTATUS SyserDeviceControl(IN PDEVICE_OBJECT DeviceObject,IN PIRP Irp)
{
	NTSTATUS Status;
	PIO_STACK_LOCATION  IOStack;
	IOStack = IoGetCurrentIrpStackLocation(Irp);
	Irp->IoStatus.Status = STATUS_SUCCESS;	
	Irp->IoStatus.Information=0;
	switch(IOStack->Parameters.DeviceIoControl.IoControlCode)
	{
	case IOCTL_SYSER_DEBUG_PROCESS:
		SyserDeviceControlDebugProcess(IOStack,Irp);
		break;
	case IOCTL_SYSER_DEBUG_DRIVER:
		SyserDeviceControlLoadDriver(IOStack,Irp);
		break;
	case IOCTL_SYSER_SAVE_HISTROYS:
		SyserDeviceSaveHistroys(IOStack,Irp);
		break;
	case IOCTL_SYSER_SAVE_COMMENTS:
		SyserDeviceSaveComments(IOStack,Irp);
		break;
	case IOCTL_SYSER_LOAD_SDS:
		SyserDeviceControlLoadSDS(IOStack,Irp);
		break;
	case IOCTL_SYSER_UNLOAD_SDS:
		SyserDeviceControlUnloadSDS(IOStack,Irp);
		break;
	case IOCTL_SYSER_LOAD_EXPORT_SYMBOL:
		SyserDeviceControlLoadExportSymbol(IOStack,Irp);
		break;
	case IOCTL_SYSER_LOAD_IDA_MAPFILE:
		SyserDeviceControlLoadIDAMap(IOStack,Irp);
		break;
	case IOCTL_SYSER_QUERY_SDS:
		SyserDeviceQuerySDS(IOStack,Irp);
		break;
	case IOCTL_SYSER_RELOAD_CONFIG:
		SyserDeviceControlReloadConfig(IOStack,Irp);
		break;
	case IOCTL_SYSER_RELOAD_COLOR_CONFIG:
		SyserDeviceControlReloadColorConfig(IOStack,Irp);
		break;
	case IOCTL_SYSER_CORRECT_VIDEO_PARAM:
		SyserDeviceControlCorrectVideoParam(IOStack,Irp);
		break;
	case IOCTL_SYSER_GET_CLIP_BOARD:
		SyserDeviceControlGetClipboard(IOStack,Irp);
		break;
	case IOCTL_SYSER_SET_CLIP_BOARD:
		SyserDeviceControlSetClipboard(IOStack,Irp);
		break;
	case IOCTL_SYSER_SCREEN_SHOT:
		SyserDeviceControlScreenShot(IOStack,Irp);
		break;
	default:
		break;
	}
	Status=Irp->IoStatus.Status;
	IoCompleteRequest(Irp, IO_NO_INCREMENT);
	return Status;
}

void SyserUnload(IN PDRIVER_OBJECT DriverObject)
{
	UNICODE_STRING SymbolicLinkName;
	if(gSyserHotKeyDriverBuffer && gSyserHotKeyDriverLen)
	{
		SaveSyserHotKeyDriver(WSTR("Syser"),WSTR("SyserHotKey.cfg"),gSyserHotKeyDriverBuffer,gSyserHotKeyDriverLen);
	}
	if(gpSyser)
	{
		if(gpSyserCfg->m_PS2MouseType!=dwMousePrePackageSize)
			gpSyserCfg->WriteDwordValue(PS2MOUSE_TYPE,dwMousePrePackageSize);
		gpSyser->Release();
		//SafeDelete(gpSyser);
	}
	if(gpSyserCfg)
	{
		delete gpSyserCfg;
		gpSyserCfg = NULL;
	}
	RtlInitUnicodeString(&SymbolicLinkName,SYSER_LINK_NAME);
	IoDeleteSymbolicLink(&SymbolicLinkName);
	PDEVICE_OBJECT NextDeviceObject,DeviceObject;
	NextDeviceObject = DriverObject->DeviceObject;
	while(NextDeviceObject)
	{
		DeviceObject = NextDeviceObject;
		NextDeviceObject = NextDeviceObject->NextDevice;
		IoDeleteDevice(DeviceObject);
	}
	if(CorrectVideoBuffer)
		MmUnmapIoSpace(CorrectVideoBuffer,CorrectVideoBufSize);
	OnUnloadSyserDriver();
}

PDRIVER_DISPATCH gDefaultPDriverDispatch=NULL;
PDRIVER_OBJECT gDriverObject;

NTSTATUS DriverEntry(IN PDRIVER_OBJECT DriverObject,IN PUNICODE_STRING RegistryPath)
{
    UNICODE_STRING	DeviceName,SymbolicLinkName,Name;
	NTSTATUS		Status;
	gDriverObject=DriverObject;

		
	DriverObject->DriverUnload = SyserUnload;
	if(EnterOnLoadSyserDriver()==false)
	{
		LeaveOnLoadSyserDriverFail(DriverObject);
		return STATUS_UNSUCCESSFUL;
	} 
	gDefaultPDriverDispatch = DriverObject->MajorFunction[IRP_MJ_CREATE];

	for(int FunCount=0;FunCount<IRP_MJ_MAXIMUM_FUNCTION;FunCount++)
		DriverObject->MajorFunction[FunCount]=MJFunction;

	DriverObject->MajorFunction[IRP_MJ_CREATE]			= SyserDeviceCreate;
	DriverObject->MajorFunction[IRP_MJ_READ]			= SyserDeviceRead;
    DriverObject->MajorFunction[IRP_MJ_CLOSE]			= SyserDeviceClose;
    DriverObject->MajorFunction[IRP_MJ_DEVICE_CONTROL]	= SyserDeviceControl;
	DriverObject->MajorFunction[IRP_MJ_SHUTDOWN]		= SyserShutDown;

	gpSyserCfg = new CSyserConfig;
	if(gpSyserCfg==NULL)
	{
		LeaveOnLoadSyserDriverFail(NULL);
		return STATUS_UNSUCCESSFUL;
	}
	gpSyserCfg->SetDriverRegistryPath(RegistryPath);
	gpSyserCfg->LoadConfig();
	dwgErrorCode=7;
	gpSyser = new CSyser;
	if(gpSyser==NULL)
	{
		LeaveOnLoadSyserDriverFail(NULL);
		return STATUS_UNSUCCESSFUL;
	}
	if(gpSyserCfg->m_MouseDoubleClickTimeInterval)
		gMaxDblClkInterval=gpSyserCfg->m_MouseDoubleClickTimeInterval;
	gpSyser->m_DriverObject=DriverObject;
	gpSyser->m_DriverStartAddr=*(DWORD*)&DriverObject->DriverStart;
	gpSyser->m_DriverEndAddr=gpSyser->m_DriverStartAddr+DriverObject->DriverSize;
	InitTickCount();
	RtlInitUnicodeString(&DeviceName,SYSER_DEVICE_NAME);
	Status = IoCreateDevice(DriverObject,0,&DeviceName,FILE_DEVICE_UNKNOWN,0,FALSE,&gpSyser->m_DeviceObject);
	if(!NT_SUCCESS(Status))
	{
		gpSyser->Release();
		delete gpSyser;
		LeaveOnLoadSyserDriverFail(NULL);
		return Status;
	}
	gpSyser->m_DeviceObject->Flags |= DO_BUFFERED_IO;
	gpSyser->m_DeviceObject->Flags &= ~DO_DEVICE_INITIALIZING;
	RtlInitUnicodeString(&SymbolicLinkName,SYSER_LINK_NAME);
	IoCreateSymbolicLink(&SymbolicLinkName,&DeviceName);
	dwgErrorCode=0;
	if(gpSyser->Init()==false)
	{
		gpSyser->Release();
		delete gpSyser;
		gpSyser=NULL;
		LeaveOnLoadSyserDriverFail(DriverObject);
		return STATUS_UNSUCCESSFUL;
	}
	LeaveOnLoadSyserDriverSuccess();
	IoRegisterShutdownNotification(gpSyser->m_DeviceObject);
	
	return STATUS_SUCCESS;
}


NTSTATUS DllInitialize( IN PUNICODE_STRING pus )
{
	return STATUS_SUCCESS;
}

NTSTATUS DllUnload( )
{
	return STATUS_SUCCESS;
}

bool SyserErrorLog(VOID* IoObject,ULONG ErrorMsgID,UCHAR MajorFunctionCode,UCHAR RetryCount,ULONG IoControlCode,ULONG FinalStatus,WCHAR *String,WCHAR *String2,ULONGLONG DumpData1,ULONGLONG DumpData2)
{
	BYTE TmpPointer;
	DWORD Str1Len=0,Str2Len=0,EntrySize,DumpDataSize=0;
	PIO_ERROR_LOG_PACKET ErrorLogEntry;
	if(String)
		Str1Len = (TStrLen(String)+1)*sizeof(WCHAR);
	if(String2)
		Str2Len = (TStrLen(String2)+1)*sizeof(WCHAR);
	if(DumpData1)
		DumpDataSize+=sizeof(ULONGLONG);
	if(DumpData2)
		DumpDataSize+=sizeof(ULONGLONG);
	EntrySize = sizeof(IO_ERROR_LOG_PACKET)+DumpDataSize+Str1Len+Str2Len;
	ErrorLogEntry = (PIO_ERROR_LOG_PACKET)IoAllocateErrorLogEntry(IoObject,(UCHAR)EntrySize);
	if(ErrorLogEntry==NULL)
		return false;
	ErrorLogEntry->ErrorCode = ErrorMsgID;
	if(DumpDataSize)
	{
		ErrorLogEntry->DumpDataSize=(USHORT)DumpDataSize;
		memcpy(&ErrorLogEntry->DumpData[0],&DumpData1,sizeof(DumpData1));
		if(DumpData2)
			memcpy((UCHAR*)&ErrorLogEntry->DumpData[0]+sizeof(DumpData1),&DumpData2,sizeof(DumpData2));
	}
	ErrorLogEntry->NumberOfStrings=0;
	ErrorLogEntry->StringOffset=0;
	if(Str1Len)
	{
		ErrorLogEntry->NumberOfStrings++;
		ErrorLogEntry->StringOffset=(UCHAR*)&ErrorLogEntry->DumpData[0]+DumpDataSize-(UCHAR*)ErrorLogEntry;
		memcpy((UCHAR*)ErrorLogEntry+ErrorLogEntry->StringOffset,String,Str1Len);
	}
	if(Str2Len)
	{
		ErrorLogEntry->NumberOfStrings++;
		if(ErrorLogEntry->StringOffset==0)
			ErrorLogEntry->StringOffset=(UCHAR*)&ErrorLogEntry->DumpData[0]+DumpDataSize-(UCHAR*)ErrorLogEntry;
		memcpy((UCHAR*)ErrorLogEntry+ErrorLogEntry->StringOffset+Str1Len,String2,Str2Len);
	}
	ErrorLogEntry->FinalStatus =FinalStatus;
	ErrorLogEntry->SequenceNumber=0;
	ErrorLogEntry->IoControlCode=IoControlCode;
	ErrorLogEntry->DeviceOffset.QuadPart=0;
	ErrorLogEntry->EventCategory = 1;
	ErrorLogEntry->RetryCount=RetryCount;
	ErrorLogEntry->MajorFunctionCode =MajorFunctionCode;
	IoWriteErrorLogEntry(ErrorLogEntry);
	return true;
}

