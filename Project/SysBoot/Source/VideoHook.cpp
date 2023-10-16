#include "StdAfx.h"
#include "SysBoot.h"
#include "VideoHook.h"
#include "VistaVideoHook.h"
#include "ScrOutput.h"
#include "PromptQuit.h"

extern "C"	SERVICETABLE*	KeServiceDescriptorTable;

SYSER_FRAME_BUFFER*	pPrevFrameBuffer=NULL;

PFN_DrvGetDirectDrawInfo	OldDrvGetDirectDrawInfo;
PFN_DrvEnableDirectDraw		OldDrvEnableDirectDraw;
PFN_DrvEnableDriver			OldDrvEnableDriver;
PFN_DrvEnablePDEV			OldDrvEnablePDEV;
PFN_DrvDisablePDEV			OldDrvDisablePDEV;
PFN_DrvEnableSurface		OldDrvEnableSurface;
PDD_SURFCB_FLIP				OldDdFlip;
PDD_SURFCB_LOCK				OldDdLock;
PFN_DrvNotify				OldDrvNotify;
PDRIVER_DISPATCH			OldDXGKrnlDispatchInternalDeviceControl;

int	ZwSetSystemInfoIndex = -1;
FPN_ZwSetSystemInformation	OldZwSetSystemInformation = NULL;

int	ZwLoadDriverIndex = -1;
PFN_ZwLoadDriver			OldZwLoadDriver = NULL;

WCHAR	szDispModuleName[MAX_FN_LEN]=WSTR("");
bool	gbDisabled = false;
bool	gbDbgMsg = false;
bool	gbFlipDbgMsg = false;
DWORD	CR0Backup=0;

void ClrCR0WP()
{
	ULONG TmpValue=0xfffeffff;
	if(CR0Backup&0x80000000)
	{
		__asm
		{
			push eax
				mov eax,cr0 
				and eax,TmpValue 
				mov cr0,eax
				pop eax 
		}
		return;
	}
	__asm
	{
		mov eax,cr0
			mov CR0Backup,eax
			and eax,TmpValue
			mov cr0,eax
	}
}

void RestoreCR0()
{
	if(CR0Backup&0x80000000)
	{	
		_asm
		{
			mov eax,CR0Backup
				mov cr0,eax
		}
		CR0Backup=0;
	}
}

bool GetDisplayDriverName()
{
	WCHAR szBuffer[MAX_FN_LEN];
	UNICODE_STRING UnicodeString;
	RTL_QUERY_REGISTRY_TABLE RegTable[2];
	*szBuffer=0;
	ZeroMemory(RegTable,sizeof(RegTable));
	UnicodeString.Length=0;
	UnicodeString.MaximumLength=sizeof(szBuffer);
	UnicodeString.Buffer=szBuffer;
	RegTable[0].Flags = RTL_QUERY_REGISTRY_DIRECT | RTL_QUERY_REGISTRY_REQUIRED | RTL_QUERY_REGISTRY_NOEXPAND;
	RegTable[0].Name = WSTR("\\Device\\Video0");
	RegTable[0].EntryContext = &UnicodeString;
	if(!NT_SUCCESS(RtlQueryRegistryValues(RTL_REGISTRY_DEVICEMAP,WSTR("VIDEO"),RegTable,NULL,NULL)))
		return false;
	*szDispModuleName=0;
	ZeroMemory(RegTable,sizeof(RegTable));
	UnicodeString.Length=0;
	UnicodeString.MaximumLength=MAX_FN_LEN*sizeof(WCHAR);
	UnicodeString.Buffer=szDispModuleName;
	RegTable[0].Flags = RTL_QUERY_REGISTRY_DIRECT | RTL_QUERY_REGISTRY_REQUIRED | RTL_QUERY_REGISTRY_NOEXPAND;
	RegTable[0].Name = WSTR("InstalledDisplayDrivers");
	RegTable[0].EntryContext = &UnicodeString;
	if(!NT_SUCCESS(RtlQueryRegistryValues(RTL_REGISTRY_ABSOLUTE,szBuffer,RegTable,NULL,NULL)))
		return false;
	TStrCat(szDispModuleName,WSTR(".dll"));
	if(gbDbgMsg)
		::DbgPrint("SyserBoot : InstalledDisplayDrivers %ws\n",szDispModuleName);
	return	true;
}

DWORD WINAPI NewDdFlip(PDD_FLIPDATA pFlipData)
{
	DWORD Result;
	if(gpDevExt->pfnFrameBufferFlip==NULL)
		return OldDdFlip(pFlipData);
	gpDevExt->bDisabled = true;
	CSyserFrameBufferMap::IT Iter = gpFrameBufferMap->Find((DHPDEV)pFlipData->lpDD->dhpdev);
	if(Iter.IsExist())
	{
		if(	Iter->Width == pFlipData->lpSurfTarg->lpGbl->wWidth && Iter->Height == pFlipData->lpSurfTarg->lpGbl->wHeight &&
			Iter->Bpp == pFlipData->lpSurfTarg->lpGbl->ddpfSurface.dwRGBBitCount && Iter->LineDistance == pFlipData->lpSurfTarg->lpGbl->lPitch)
		{
			if((DWORD)pFlipData->lpSurfTarg->lpGbl->fpVidMem > 0x80000000)
				Iter->Buffer=(void*)pFlipData->lpSurfTarg->lpGbl->fpVidMem;
			else
				Iter->Buffer=RT_PVOID(Iter->BaseBuffer,(DWORD)pFlipData->lpSurfTarg->lpGbl->fpVidMem);
			WindowsFilp(Iter->Buffer);
			if(gbFlipDbgMsg)
				::DbgPrint("SysBoot : NewFlip BaseFrameBuffer = 0x%08X , FrameBuffer = 0x%08X !\n",Iter->BaseBuffer,Iter->Buffer);
		}
	}
	Result = OldDdFlip(pFlipData);
	if(gpDevExt->bDisabled==false)
	{
		if(gpDevExt->pfnSyserActive)
			gpDevExt->pfnSyserActive();
	}
	else
		gpDevExt->bDisabled = false;
	return Result;
}

DWORD WINAPI NewDdLock(PDD_LOCKDATA  lpLock)
{
	DWORD Result = OldDdLock(lpLock);
	if(gbDbgMsg)
	{
	}
	return Result;
}

BOOL WINAPI NewDrvEnableDirectDraw(DHPDEV dhpdev,DD_CALLBACKS*pCallBacks,DD_SURFACECALLBACKS*pSurfaceCallBacks,DD_PALETTECALLBACKS*pPaletteCallBacks)
{
	BOOL Result;
	Result = OldDrvEnableDirectDraw(dhpdev,pCallBacks,pSurfaceCallBacks,pPaletteCallBacks);
	if(Result==FALSE)
		return FALSE;
	CSyserFrameBufferMap::IT Iter = gpFrameBufferMap->Find(dhpdev);
	if(Iter!=gpFrameBufferMap->End())
	{
		if(gbDbgMsg)
		{
			::DbgPrint("SyserBoot : NewDrvEnableDirectDraw dhpdev = %08X [ Width = %d , Height = %d , Bpp = %d Buffer = 0x%08X , BaseBuffer = 0x%08X ]\n",
			dhpdev,Iter->Width,Iter->Height,Iter->Bpp,Iter->Buffer,Iter->BaseBuffer);
		}
		pPrevFrameBuffer = gpDevExt->pCurFrameBuffer;
		gpDevExt->pCurFrameBuffer = &(*Iter);
		WindowsModeChange(Iter->Width,Iter->Height,Iter->Bpp,Iter->Buffer,Iter->LineDistance);
	}
	OldDdFlip = pSurfaceCallBacks->Flip;
	pSurfaceCallBacks->Flip = NewDdFlip;
	//OldDdLock = pSurfaceCallBacks->Lock;
	//pSurfaceCallBacks->Lock = NewDdLock;
	return Result;
}

DHPDEV WINAPI NewDrvEnablePDEV(DEVMODEW*pdm,LPWSTR pwszLogAddress,ULONG cPat,HSURF*phsurfPatterns,ULONG cjCaps,GDIINFO*pdevcaps,ULONG cjDevInfo,DEVINFO*pdi,HDEV hdev,LPWSTR pwszDeviceName,HANDLE hDriver)
{
	DHPDEV Result;
	GetDbgMsgState();
	Result=OldDrvEnablePDEV(pdm,pwszLogAddress,cPat,phsurfPatterns,cjCaps,pdevcaps,cjDevInfo,pdi,hdev,pwszDeviceName,hDriver);
	if(Result==NULL)
		return NULL;
	gpFrameBufferMap->InsertUnique(Result);
	if(gbDbgMsg)
		::DbgPrint("SyserBoot : NewDrvEnablePDEV dhpdev = 0x%08X , Mode List Count =%d\n",Result,gpFrameBufferMap->Count());
	return Result;
}

BOOL WINAPI NewDrvGetDirectDrawInfo(DHPDEV dhpdev,DD_HALINFO*pHalInfo,DWORD*pdwNumHeaps,VIDEOMEMORY*pvmList,DWORD*pdwNumFourCCCodes,DWORD*pdwFourCC)
{
	BOOL Result;
	Result=OldDrvGetDirectDrawInfo(dhpdev,pHalInfo,pdwNumHeaps,pvmList,pdwNumFourCCCodes,pdwFourCC);
	if(Result==FALSE)
		return FALSE;
	CSyserFrameBufferMap::IT Iter = gpFrameBufferMap->Find(dhpdev);
	if(Iter!=gpFrameBufferMap->End())
	{
		Iter->Width=pHalInfo->vmiData.dwDisplayWidth;
		Iter->Height=pHalInfo->vmiData.dwDisplayHeight;
		Iter->Bpp=pHalInfo->vmiData.ddpfDisplay.dwRGBBitCount;
		Iter->LineDistance = pHalInfo->vmiData.lDisplayPitch;
		Iter->BaseBuffer=RT_PVOID(pHalInfo->vmiData.pvPrimary,-(int)pHalInfo->vmiData.fpPrimary);
		Iter->Buffer=pHalInfo->vmiData.pvPrimary;
		if(pPrevFrameBuffer==NULL)
		{
			pPrevFrameBuffer = &(*Iter);
			gpDevExt->pCurFrameBuffer = pPrevFrameBuffer;
			WindowsModeChange(Iter->Width,Iter->Height,Iter->Bpp,Iter->Buffer,Iter->LineDistance);
		}
	}
	if(gbDbgMsg)
		DbgPrint("SyserBoot : NewDrvGetDirectDrawInfo Fill FrameBuffer Info\n");
	return Result;
}

void WINAPI NewDrvDisablePDEV(DHPDEV dhpdev)
{
	CSyserFrameBufferMap::IT Iter = gpFrameBufferMap->Find(dhpdev);
	if(Iter!=gpFrameBufferMap->End())
	{
		if(gpDevExt->pCurFrameBuffer == &(*Iter) && gpDevExt->pCurFrameBuffer != pPrevFrameBuffer)
		{
			gpDevExt->pCurFrameBuffer = pPrevFrameBuffer;
			WindowsModeChange(	gpDevExt->pCurFrameBuffer->Width,
								gpDevExt->pCurFrameBuffer->Height,
								gpDevExt->pCurFrameBuffer->Bpp,
								gpDevExt->pCurFrameBuffer->Buffer,
								gpDevExt->pCurFrameBuffer->LineDistance);
		}
		gpFrameBufferMap->Remove(Iter);
	}
	if(gbDbgMsg)
		::DbgPrint("SyserBoot : NewDrvDisablePDEV dhpdev = 0x%08X\n",dhpdev);
	OldDrvDisablePDEV(dhpdev);
}

HSURF WINAPI NewDrvEnableSurface(DHPDEV dhpdev)
{
	HSURF Result = OldDrvEnableSurface(dhpdev);
	if(gbDbgMsg)
		::DbgPrint("SyserBoot : NewDrvEnableSurface dhpdev = 0x%08X\n",dhpdev);
	return Result;
}

BOOL WINAPI NewDrvEnableDriver(ULONG iEngineVersion,ULONG cj,DRVENABLEDATA*pded)
{
	BOOL Result = OldDrvEnableDriver(iEngineVersion,cj,pded);
	if(Result==FALSE)
		return FALSE;
	for(ULONG n=0;n<pded->c;n++)
	{
		switch(pded->pdrvfn[n].iFunc)
		{
		case INDEX_DrvGetDirectDrawInfo:
			if(pded->pdrvfn[n].pfn!=(PFN)NewDrvGetDirectDrawInfo)
			{
				if(gbDbgMsg)
					::DbgPrint("SyserBoot : Hook DrvGetDirectDrawInfo\n");
				OldDrvGetDirectDrawInfo = (PFN_DrvGetDirectDrawInfo)pded->pdrvfn[n].pfn;
				pded->pdrvfn[n].pfn = (PFN)NewDrvGetDirectDrawInfo;
			}
			break;
		case INDEX_DrvEnableDirectDraw:
			if(pded->pdrvfn[n].pfn!=(PFN)NewDrvEnableDirectDraw)
			{
				if(gbDbgMsg)
					::DbgPrint("SyserBoot : Hook DrvEnableDirectDraw\n");
				OldDrvEnableDirectDraw = (PFN_DrvEnableDirectDraw)pded->pdrvfn[n].pfn;
				pded->pdrvfn[n].pfn = (PFN)NewDrvEnableDirectDraw;
			}
			break;
		case INDEX_DrvEnablePDEV:
			if(pded->pdrvfn[n].pfn!=(PFN)NewDrvEnablePDEV)
			{
				if(gbDbgMsg)
					::DbgPrint("SyserBoot : Hook DrvEnablePDEV\n");
				OldDrvEnablePDEV = (PFN_DrvEnablePDEV)pded->pdrvfn[n].pfn;
				pded->pdrvfn[n].pfn = (PFN)NewDrvEnablePDEV;
			}
			break;
		case INDEX_DrvDisablePDEV:
			if(pded->pdrvfn[n].pfn!=(PFN)NewDrvDisablePDEV)
			{
				if(gbDbgMsg)
					::DbgPrint("SyserBoot : Hook DrvDisablePDEV\n");
				OldDrvDisablePDEV = (PFN_DrvDisablePDEV)pded->pdrvfn[n].pfn;
				pded->pdrvfn[n].pfn = (PFN)NewDrvDisablePDEV;
			}
			break;
		case INDEX_DrvEnableSurface:
			if(pded->pdrvfn[n].pfn!=(PFN)NewDrvEnableSurface)
			{
				if(gbDbgMsg)
					::DbgPrint("SyserBoot : Hook DrvEnableSurface\n");
				OldDrvEnableSurface = (PFN_DrvEnableSurface)pded->pdrvfn[n].pfn;
				pded->pdrvfn[n].pfn = (PFN)NewDrvEnableSurface;
			}
			break;
		}
	}
	return Result;
}

DWORD APIENTRY NewZwSetSystemInformation(DWORD FunctionNo,void*Informat,DWORD Size)
{
	WCHAR szFileName[MAX_FN_LEN];
	DWORD Result;
	if(FunctionNo!=0x1A)//SystemLoadDriver
		return OldZwSetSystemInformation(FunctionNo,Informat,Size);		
	Result=OldZwSetSystemInformation(FunctionNo,Informat,Size);
	if(Result==STATUS_SUCCESS)
	{
		if(*szDispModuleName==0)
			GetDisplayDriverName();
		__try
		{
			UnicodeStrCpy(szFileName,((PUNICODE_STRING)Informat),MAX_FN_LEN);
		}
		__except(EXCEPTION_EXECUTE_HANDLER)
		{
			*szFileName=0;
			::DbgPrint("SyserBoot : Exception in NewZwSetSystemInformation UnicodeStrCpy\n");
		}
		if(gbDbgMsg)
			::DbgPrint("SyserBoot : ZwSetSystemInformattion %ws\n",szFileName);
		if(*szFileName && *szDispModuleName && TStrICmp(szDispModuleName,TGetFileName(szFileName))==0)
		{
			void**Address;
			Address=(void**)Informat;
			if(Address[4]!=NULL && Address[4]!=(void*)NewDrvEnableDriver)
			{
				OldDrvEnableDriver=(PFN_DrvEnableDriver)Address[4];
				Address[4]=(void*)NewDrvEnableDriver;
			}
		}
	}
	return Result;
}

NTSTATUS APIENTRY NewDXGKrnlDispatchInternalDeviceControl(IN PDEVICE_OBJECT  DeviceObject,IN PIRP  Irp)
{
	int Length;
	PVOID Buffer;
	ULONG IoControlCode;
	PIO_STACK_LOCATION  IOStack;
	NTSTATUS Status;
	IOStack = IoGetCurrentIrpStackLocation(Irp);
	Buffer = Irp->UserBuffer;
	Length = IOStack->Parameters.DeviceIoControl.OutputBufferLength;
	IoControlCode = IOStack->Parameters.DeviceIoControl.IoControlCode;
	Status = OldDXGKrnlDispatchInternalDeviceControl(DeviceObject,Irp);
	if(IoControlCode == 0x0023003F && Length == 4 && Buffer)//DXGKrnlµÄDxgkInitialize
	{
		OldDxgkInitialize = *(PFN_DxgkInitialize*)Buffer;
		*(PFN_DxgkInitialize*)Buffer = NewDxgkInitialize;
		if(gbDbgMsg)
			::DbgPrint("SyserBoot : DXGKrnl->DxgkInitialize = %08X\n",OldDxgkInitialize);
	}
	return Status;
}

NTSTATUS APIENTRY NewZwLoadDriver(IN PUNICODE_STRING DriverServiceName)
{
	NTSTATUS Status = OldZwLoadDriver(DriverServiceName);
	if(Status != STATUS_SUCCESS || DriverServiceName==NULL)
		return Status;
	if(TMemICmp(WSTR("\\Registry\\Machine\\System\\CurrentControlSet\\Services\\DXGKrnl"),DriverServiceName->Buffer,DriverServiceName->Length/2))
		return Status;
	PDEVICE_OBJECT DeviceObject;
	PFILE_OBJECT FileObject;
	UNICODE_STRING UnicodeName;
	RtlInitUnicodeString(&UnicodeName,WSTR("\\Device\\DXGKrnl"));
	if(!NT_SUCCESS(IoGetDeviceObjectPointer(&UnicodeName,FILE_READ_DATA,&FileObject,&DeviceObject)))
	{
		if(gbDbgMsg)
			::DbgPrint("SyserBoot : Fail to get \\Device\\DXGKrnl\n");
		return Status;
	}
	ObDereferenceObject(FileObject);
	if(gbDbgMsg)
	{
		::DbgPrint("SyserBoot : DXGKrnl->DriverObject = %08X\n",DeviceObject->DriverObject);
		::DbgPrint("SyserBoot : DXGKrnl->DriverObject->MajorFunction[IRP_MJ_INTERNAL_DEVICE_CONTROL] = %08X\n",DeviceObject->DriverObject->MajorFunction[IRP_MJ_INTERNAL_DEVICE_CONTROL]);
	}
	if(DeviceObject->DriverObject->MajorFunction[IRP_MJ_INTERNAL_DEVICE_CONTROL]!=NewDXGKrnlDispatchInternalDeviceControl)
	{
		OldDXGKrnlDispatchInternalDeviceControl = DeviceObject->DriverObject->MajorFunction[IRP_MJ_INTERNAL_DEVICE_CONTROL];
		DeviceObject->DriverObject->MajorFunction[IRP_MJ_INTERNAL_DEVICE_CONTROL] = NewDXGKrnlDispatchInternalDeviceControl;
	}
	return Status;
}

bool HookZwSetSystemInformation()
{
	UNICODE_STRING NtApiName;
	BYTE* ZwSetSystemInformationFunc;
	RtlInitUnicodeString(&NtApiName,WSTR("ZwSetSystemInformation"));
	ZwSetSystemInformationFunc=(BYTE*)MmGetSystemRoutineAddress(&NtApiName);
	if(ZwSetSystemInformationFunc==0||*ZwSetSystemInformationFunc!=0xB8)
	{
		::DbgPrint("SyserBoot : Fail to hook ZwSetSystemInformation\n");
		return false;
	}
	ZwSetSystemInfoIndex = *(DWORD*)(ZwSetSystemInformationFunc+1);
	OldZwSetSystemInformation=(FPN_ZwSetSystemInformation) KeServiceDescriptorTable->ServiceTable[ZwSetSystemInfoIndex];
	ClrCR0WP();
	KeServiceDescriptorTable->ServiceTable[ZwSetSystemInfoIndex]=NewZwSetSystemInformation;
	RestoreCR0();
	if(gbDbgMsg)
		::DbgPrint("SyserBoot : ZwSetSystemInformation hook Success !\n");
	return true;
}

void UnhookZwSetSystemInformation()
{
	if(ZwSetSystemInfoIndex<0 || KeServiceDescriptorTable->ServiceTable[ZwSetSystemInfoIndex]!=NewZwSetSystemInformation)
		return;
	KeServiceDescriptorTable->ServiceTable[ZwSetSystemInfoIndex]=OldZwSetSystemInformation;
	if(gbDbgMsg)
		::DbgPrint("SyserBoot : ZwSetSystemInformation Unhook Success !\n");
}

bool HookZwLoadDriver()
{
	ULPOS ModuleBase;
	UNICODE_STRING NtApiName;
	BYTE* ZwLoadDriverFunc;
	RtlInitUnicodeString(&NtApiName,WSTR("ZwLoadDriver"));
	ZwLoadDriverFunc=(BYTE*)MmGetSystemRoutineAddress(&NtApiName);
	if(ZwLoadDriverFunc==0||*ZwLoadDriverFunc!=0xB8)
	{
		::DbgPrint("SyserBoot : Fail to hook ZwLoadDriver\n");
		return false;
	}
	ZwLoadDriverIndex = *(DWORD*)(ZwLoadDriverFunc+1);
	OldZwLoadDriver=(PFN_ZwLoadDriver)KeServiceDescriptorTable->ServiceTable[ZwLoadDriverIndex];
	ClrCR0WP();
	KeServiceDescriptorTable->ServiceTable[ZwLoadDriverIndex]=NewZwLoadDriver;
	RestoreCR0();
	if(gbDbgMsg)
		::DbgPrint("SyserBoot : ZwLoadDriver Hook Success !\n");
	return true;
}

void UnhookZwLoadDriver()
{
	if(ZwLoadDriverIndex<0 || KeServiceDescriptorTable->ServiceTable[ZwLoadDriverIndex]!=NewZwLoadDriver)
		return;
	KeServiceDescriptorTable->ServiceTable[ZwLoadDriverIndex]=OldZwLoadDriver;
	if(gbDbgMsg)
		::DbgPrint("SyserBoot : ZwLoadDriver Unhook Success !\n");
}
