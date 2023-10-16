#include "StdAfx.h"
#include "SysBoot.h"
#include "VideoHook.h"
#include "ScrOutput.h"
#include "PromptQuit.h"

SYSER_BOOT_DEVICE_EXTENSION*gpDevExt;
CSyserFrameBufferMap*gpFrameBufferMap;
SYSER_FRAME_BUFFER CurentFrameBuffer;

void WindowsModeChange(int Width,int Height,int Bpp,void*FrameBuffer,int Pitch)
{
	if(FrameBuffer)
	{
		int Size = Pitch*Height;
		for(int Off = 0;Off<Size;Off+=MP_SIZE)
		{
			if(MmIsAddressValid((BYTE*)FrameBuffer+Off)==false)
			{
				if(gbDbgMsg)
					DbgPrint("SyserBoot : Invalid FrameBuf [%08X] ,Invalid Address [%08X]\n",FrameBuffer,(BYTE*)FrameBuffer+Off);
				return;
			}
		}
	}

	CurentFrameBuffer.Width = Width;
	CurentFrameBuffer.Height = Height;
	CurentFrameBuffer.Bpp = Bpp;
	CurentFrameBuffer.LineDistance = Pitch;
	CurentFrameBuffer.Buffer = FrameBuffer;

	SwitchDrawPixel(Bpp);
	if(gpDevExt->pfnFrameModeChange)
		gpDevExt->pfnFrameModeChange(Width,Height,Bpp,FrameBuffer,Pitch,0);
}

void WindowsFilp(void*FrameBuffer)
{
	CurentFrameBuffer.Buffer = FrameBuffer;	
	if(gpDevExt->pfnFrameBufferFlip)
		gpDevExt->pfnFrameBufferFlip(FrameBuffer);
}

void GetDbgMsgState()
{
	DWORD Value;
	RTL_QUERY_REGISTRY_TABLE RegTable[2];
	/////////////////////////////////////////////////////////////////////////////////////////
	ZeroMemory(RegTable,sizeof(RegTable));
	RegTable[0].Flags = RTL_QUERY_REGISTRY_DIRECT | RTL_QUERY_REGISTRY_REQUIRED;
	RegTable[0].Name = WSTR("DbgMsg");
	RegTable[0].EntryContext = &Value;
	if(!NT_SUCCESS(RtlQueryRegistryValues(RTL_REGISTRY_SERVICES,WSTR("SyserBoot"),RegTable,NULL,NULL)))
		Value = 0;
	gbDbgMsg = Value!=0;
	/////////////////////////////////////////////////////////////////////////////////////////
	ZeroMemory(RegTable,sizeof(RegTable));
	RegTable[0].Flags = RTL_QUERY_REGISTRY_DIRECT | RTL_QUERY_REGISTRY_REQUIRED;
	RegTable[0].Name = WSTR("Disabled");
	RegTable[0].EntryContext = &Value;
	if(!NT_SUCCESS(RtlQueryRegistryValues(RTL_REGISTRY_SERVICES,WSTR("SyserBoot"),RegTable,NULL,NULL)))
		Value = 0;
	gbDisabled = Value!=0;
	/////////////////////////////////////////////////////////////////////////////////////////
	ZeroMemory(RegTable,sizeof(RegTable));
	RegTable[0].Flags = RTL_QUERY_REGISTRY_DIRECT | RTL_QUERY_REGISTRY_REQUIRED;
	RegTable[0].Name = WSTR("FlipDbgMsg");
	RegTable[0].EntryContext = &Value;
	if(!NT_SUCCESS(RtlQueryRegistryValues(RTL_REGISTRY_SERVICES,WSTR("SyserBoot"),RegTable,NULL,NULL)))
		Value = 0;
	gbFlipDbgMsg = Value!=0;
}

void LoadImageHookProc(IN PUNICODE_STRING  FullImageName,IN HANDLE  ProcessId,IN PIMAGE_INFO  ImageInfo)
{
	if(gpDevExt && gpDevExt->pfnLoadImageNotifyRoutine)
		gpDevExt->pfnLoadImageNotifyRoutine(FullImageName,ProcessId,ImageInfo);
}

void SyserBootUnload(IN PDRIVER_OBJECT DriverObject)
{
	UNICODE_STRING UnicodeName;
	SafeDelete(gpFrameBufferMap);
	IoDeleteDevice(DriverObject->DeviceObject);
	RtlInitUnicodeString(&UnicodeName,SYSER_BOOT_LINK_NAME);
	IoDeleteSymbolicLink(&UnicodeName);
	UnhookZwSetSystemInformation();
	UnhookZwLoadDriver();
	RtlInitUnicodeString(&UnicodeName,WSTR("PsRemoveLoadImageNotifyRoutine"));
	NTSTATUS (*PsRemoveLoadImageNotifyRoutine)(IN PLOAD_IMAGE_NOTIFY_ROUTINE);
	(PVOID&)PsRemoveLoadImageNotifyRoutine=MmGetSystemRoutineAddress(&UnicodeName);
	if(PsRemoveLoadImageNotifyRoutine)
		PsRemoveLoadImageNotifyRoutine(LoadImageHookProc);
}

NTSTATUS MJFunction(IN PDEVICE_OBJECT DeviceObject,IN PIRP  Irp)
{
	Irp->IoStatus.Information=0;
	Irp->IoStatus.Status=STATUS_SUCCESS;
	IoCompleteRequest(Irp,IO_NO_INCREMENT);
	return STATUS_SUCCESS;
}

NTSTATUS SyserBootDeviceCreate(IN PDEVICE_OBJECT DeviceObject,IN PIRP Irp)
{
	UNICODE_STRING Name;
	Irp->IoStatus.Status = STATUS_SUCCESS;
	Irp->IoStatus.Information = FILE_OPENED;
	IoCompleteRequest(Irp,IO_NO_INCREMENT);
	return STATUS_SUCCESS;
}

NTSTATUS SyserBootDeviceClose(IN PDEVICE_OBJECT DeviceObject,IN PIRP Irp)
{
	Irp->IoStatus.Status = STATUS_SUCCESS;
	Irp->IoStatus.Information = FILE_OPENED;
	IoCompleteRequest(Irp,IO_NO_INCREMENT);
	return STATUS_SUCCESS;
}

NTSTATUS SyserBootDeviceControl(IN PDEVICE_OBJECT DeviceObject,IN PIRP Irp)
{
	NTSTATUS Status;
	PIO_STACK_LOCATION  IOStack;
	IOStack = IoGetCurrentIrpStackLocation(Irp);
	Status = STATUS_SUCCESS;
	Irp->IoStatus.Information=0;
	switch(IOStack->Parameters.DeviceIoControl.IoControlCode)
	{
	case IOCTL_SYSER_BOOT_GET_FRAME_BUFFER:
		if(IOStack->Parameters.DeviceIoControl.OutputBufferLength<sizeof(SYSER_FRAME_BUFFER))
		{
			Status = STATUS_BUFFER_TOO_SMALL;
			break;
		}
		memcpy(Irp->AssociatedIrp.SystemBuffer,&CurentFrameBuffer,sizeof(SYSER_FRAME_BUFFER));
		Irp->IoStatus.Information = sizeof(SYSER_FRAME_BUFFER);
		break;
	}
	Irp->IoStatus.Status = Status;
	IoCompleteRequest(Irp, IO_NO_INCREMENT);
	return Status;
}

/////////////////////////////////////////////////////////////////////////////////////////
//³ÌÐòÈë¿Ú
/////////////////////////////////////////////////////////////////////////////////////////
#define SCAN_CODE_NO_KEY	0x0
#define SCAN_CODE_ESC_KEY	0x1

NTSTATUS DriverEntry(IN PDRIVER_OBJECT DriverObject,IN PUNICODE_STRING RegistryPath)
{
	UNICODE_STRING      DeviceName,SymbolicLinkName;
	NTSTATUS            status;
	PDEVICE_OBJECT      DeviceObject;
	SYSER_BOOT_DEVICE_EXTENSION*DeviceExtension;
	int RetValue = PromptQuit("             Press \"ESC\" to cancel loading Syser Boot Module           ");
	if(RetValue==SCAN_CODE_ESC_KEY)
		return STATUS_UNSUCCESSFUL;
	RtlInitUnicodeString(&DeviceName,WSTR("\\Device\\SyserBoot"));
	status = IoCreateDevice(DriverObject,sizeof(SYSER_BOOT_DEVICE_EXTENSION),&DeviceName,FILE_DEVICE_VIDEO,0,TRUE,&DeviceObject);
	if(!NT_SUCCESS(status))
		return status;

	DeviceObject->Flags |= METHOD_BUFFERED;
	DeviceObject->Flags &= ~DO_DEVICE_INITIALIZING;
	RtlInitUnicodeString(&SymbolicLinkName,SYSER_BOOT_LINK_NAME);
	IoCreateSymbolicLink(&SymbolicLinkName,&DeviceName);

	STZeroMemory(CurentFrameBuffer);
	gpDevExt = (SYSER_BOOT_DEVICE_EXTENSION*)DeviceObject->DeviceExtension;
	ZeroMemory(gpDevExt,sizeof(SYSER_BOOT_DEVICE_EXTENSION));
	gpDevExt->cbSize = sizeof(SYSER_BOOT_DEVICE_EXTENSION);
	gpDevExt->Version = SYSER_BOOT_VER;
	gpDevExt->pfnScrPrint = ScrPrint;
	gpFrameBufferMap = new CSyserFrameBufferMap;
	GetDbgMsgState();
	__try
	{
		if(gbDisabled)
		{
			DbgPrint("SyserBoot : Video Hook is disabled!\n");
		}
		else
		{
			HookZwSetSystemInformation();
			HookZwLoadDriver();
		}
	}
	__except(EXCEPTION_EXECUTE_HANDLER)
	{
		::DbgPrint("SyserBoot : Exception\n");
	}
	for(DWORD FunCount=0;FunCount<IRP_MJ_MAXIMUM_FUNCTION;FunCount++)
		DriverObject->MajorFunction[FunCount]=MJFunction;

	DriverObject->MajorFunction[IRP_MJ_CREATE]			= SyserBootDeviceCreate;
	DriverObject->MajorFunction[IRP_MJ_CLOSE]			= SyserBootDeviceClose;
	DriverObject->MajorFunction[IRP_MJ_DEVICE_CONTROL]	= SyserBootDeviceControl;

	DriverObject->DriverUnload = SyserBootUnload;
	PsSetLoadImageNotifyRoutine(LoadImageHookProc);
	return STATUS_SUCCESS;
}

