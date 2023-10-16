#include "StdAfx.h"
#include "SysBoot.h"
#include "VistaVideoHook.h"


PFN_DxgkInitialize	OldDxgkInitialize;

PFN_DXGKDDI_SETVIDPNSOURCEVISIBILITY	OldDxgkDdiSetVidPnSourceVisibility;	//设置显示器回扫状态
PFN_DXGKDDI_SETVIDPNSOURCEADDRESS		OldDxgkDdiSetVidPnSourceAddress;	//设置回扫基地址
PFN_DXGKDDI_CREATEALLOCATION			OldDxgkDdiCreateAllocation;			//分配显存,存贮主面的详细信息
PFN_DXGKDDI_DESTROYALLOCATION			OldDxgkDdiDestroyAllocation;		//释放显存
PFN_DXGKDDI_PRESENT						OldDxgkDdiPresent;					//表面操作 BitBlt Flip等


struct VIDEO_FRAME_BUFFER_MAP_DESCR
{
	void*				VirtualAddress;
	PHYSICAL_ADDRESS	PhysicalAddress;
	SIZE_T				Length;
};

VIDEO_FRAME_BUFFER_MAP_DESCR PrimaryFrameBufferDescr;

bool AllocateFrameBufferMap(PHYSICAL_ADDRESS PhysicalAddress,SIZE_T Length,VIDEO_FRAME_BUFFER_MAP_DESCR*pDescr)
{
	KIRQL IRQL=KeGetCurrentIrql();
	if(IRQL!=PASSIVE_LEVEL)
	{
		if(gbDbgMsg)
			::DbgPrint("SyserBoot : AllocateFrameBufferMap IRQL = %08X\n",IRQL);
		pDescr->VirtualAddress = NULL;
		return false;
	}
	pDescr->VirtualAddress = MmMapIoSpace(PhysicalAddress,Length,MmWriteCombined);
	if(pDescr->VirtualAddress==NULL)
		return false;

	pDescr->PhysicalAddress = PhysicalAddress;
	pDescr->Length = Length;
	return true;
}

void ReleaseFrameBufferMap(VIDEO_FRAME_BUFFER_MAP_DESCR*pDescr)
{
	if(pDescr->VirtualAddress==NULL)
		return;
	KIRQL IRQL=KeGetCurrentIrql();
	if(IRQL!=PASSIVE_LEVEL)
	{
		if(gbDbgMsg)
			::DbgPrint("SysBoot : ReleaseFrameBufferMap IRQL = %08X\n",IRQL);
		return;
	}
	MmUnmapIoSpace(pDescr->VirtualAddress,pDescr->Length);
	ZeroMemory(pDescr,sizeof(VIDEO_FRAME_BUFFER_MAP_DESCR));
}

int D3dDdiFormatToDepth(D3DDDIFORMAT Format)
{
	switch(Format)
	{
	case D3DDDIFMT_R8G8B8:
		return 24;
	case D3DDDIFMT_A8R8G8B8:
	case D3DDDIFMT_X8R8G8B8:
	case D3DDDIFMT_A8B8G8R8:
	case D3DDDIFMT_X8B8G8R8:
		return 32;
	case D3DDDIFMT_R5G6B5:
	case D3DDDIFMT_X1R5G5B5:
	case D3DDDIFMT_A1R5G5B5:
		return 16;
	default:
		return 16;
	}
}

NTSTATUS APIENTRY NewDxgkDdiPresent(CONST HANDLE hContext,DXGKARG_PRESENT* pPresent)
{
	return OldDxgkDdiPresent(hContext,pPresent);
}

NTSTATUS APIENTRY NewDxgkDdiSetVidPnSourceVisibility(CONST HANDLE  hAdapter,CONST DXGKARG_SETVIDPNSOURCEVISIBILITY* pSetVidPnSourceVisibility)
{
	NTSTATUS Status = OldDxgkDdiSetVidPnSourceVisibility(hAdapter,pSetVidPnSourceVisibility);
	if(pSetVidPnSourceVisibility->Visible)
	{
		GetDbgMsgState();
		gpFrameBufferMap->Clear();
	}
	if(gbDbgMsg)
	{
		::DbgPrint("SyserBoot : DxgkDdiSetVidPnSourceVisibility %s\n",pSetVidPnSourceVisibility->Visible?"Visible":"Invisible");
	}
	return Status;
}

NTSTATUS APIENTRY NewDxgkDdiSetVidPnSourceAddress(CONST HANDLE  hAdapter,CONST DXGKARG_SETVIDPNSOURCEADDRESS*pSetVidPnSourceAddress)
{
	NTSTATUS Status = OldDxgkDdiSetVidPnSourceAddress(hAdapter,pSetVidPnSourceAddress);
	if(pSetVidPnSourceAddress->Flags.ModeChange)
	{
		CSyserFrameBufferMap::IT Iter = gpFrameBufferMap->Find(pSetVidPnSourceAddress->hAllocation);
		if(Iter.IsExist())
		{
			ReleaseFrameBufferMap(&PrimaryFrameBufferDescr);
			if(AllocateFrameBufferMap(pSetVidPnSourceAddress->PrimaryAddress,Iter->Height*Iter->LineDistance,&PrimaryFrameBufferDescr))
			{
				Iter->Buffer = Iter->BaseBuffer = PrimaryFrameBufferDescr.VirtualAddress;
				WindowsModeChange(Iter->Width,Iter->Height,Iter->Bpp,Iter->Buffer,Iter->LineDistance);
				gpDevExt->pCurFrameBuffer = &CurentFrameBuffer;
				if(gbDbgMsg)
				{
					::DbgPrint("SyserBoot : DxgkDdiSetVidPnSourceAddress hAllocation = %08X\n",pSetVidPnSourceAddress->hAllocation);
					::DbgPrint("            Mode Change %d X %d X %d Pitch %d PhysAddr[%08X] FrameBuffer[%08X]\n",
						Iter->Width,Iter->Height,Iter->Bpp,Iter->LineDistance,(DWORD)pSetVidPnSourceAddress->PrimaryAddress.QuadPart,Iter->Buffer);
				}
			}
			else
			{
				if(gbDbgMsg)
					::DbgPrint("SyserBoot : DxgkDdiSetVidPnSourceAddress fail to map PhysAddr 0x%08X\n",(DWORD)pSetVidPnSourceAddress->PrimaryAddress.QuadPart);
			}
		}
	}
	return Status;
}

bool IsVideoDeviceAlloc(DXGK_ALLOCATIONINFO* pAllocInfo)
{
	if(pAllocInfo->pAllocationUsageHint==NULL)
		return false;
	if(pAllocInfo->pAllocationUsageHint->v1.Pitch==0)
		return false;
	if(pAllocInfo->pAllocationUsageHint->v1.Width<640 || pAllocInfo->pAllocationUsageHint->v1.Height<480)
		return false;
	if(pAllocInfo->pAllocationUsageHint->v1.Pitch<=pAllocInfo->pAllocationUsageHint->v1.Width)
		return false;
	return true;
}

NTSTATUS NewDxgkDdiCreateAllocation(CONST HANDLE hAdapter,DXGKARG_CREATEALLOCATION*pCreateAllocation)
{
	DXGK_ALLOCATIONINFO* pAllocInfo;
	NTSTATUS Status = OldDxgkDdiCreateAllocation(hAdapter,pCreateAllocation);
	if(pCreateAllocation->pAllocationInfo==NULL||pCreateAllocation->NumAllocations==0||Status!=STATUS_SUCCESS)
		return Status;
	for(UINT n=0;n<pCreateAllocation->NumAllocations;n++)
	{
		pAllocInfo = &pCreateAllocation->pAllocationInfo[n];
		if(pAllocInfo->pAllocationUsageHint && IsVideoDeviceAlloc(pAllocInfo))
		{
			CSyserFrameBufferMap::IT Iter = gpFrameBufferMap->InsertUnique(pAllocInfo->hAllocation);
			if(Iter.IsExist())
			{
				Iter->Width = pAllocInfo->pAllocationUsageHint->v1.Width;
				Iter->Height = pAllocInfo->pAllocationUsageHint->v1.Height;
				Iter->Bpp = D3dDdiFormatToDepth(pAllocInfo->pAllocationUsageHint->v1.Format);
				Iter->LineDistance = pAllocInfo->pAllocationUsageHint->v1.Pitch;
				Iter->BaseBuffer = Iter->Buffer = 0;
				Iter->PixelFormat = 0;
				if(gbDbgMsg)
				{
					::DbgPrint("SyserBoot : CreateAllocation [%d] = %08X , %d X %d X %d ,Pitch = %d , D3DFormat = %d CreateFlag %X\n",
						gpFrameBufferMap->Count(),pAllocInfo->hAllocation,Iter->Width,Iter->Height,Iter->Bpp,Iter->LineDistance,
						pAllocInfo->pAllocationUsageHint->v1.Format,pAllocInfo->Flags.Value);
				}
			}
		}
	}
	return Status;
}

NTSTATUS APIENTRY NewDxgkDdiDestroyAllocation(CONST HANDLE  hAdapter,CONST DXGKARG_DESTROYALLOCATION*pDestroyAllocation)
{
	NTSTATUS Status = OldDxgkDdiDestroyAllocation(hAdapter,pDestroyAllocation);
	if(pDestroyAllocation->pAllocationList)
	{
		for(UINT n=0;n<pDestroyAllocation->NumAllocations;n++)
		{
			if(gpFrameBufferMap->Remove(pDestroyAllocation->pAllocationList[n])>0)
			{
				if(gbDbgMsg)
					::DbgPrint("SyserBoot : DestroyAllocation = %08X\n",pDestroyAllocation->pAllocationList[n]);
			}
		}
	}
	return Status;
}

NTSTATUS APIENTRY NewDxgkInitialize(IN PDRIVER_OBJECT DriverObject,IN PUNICODE_STRING RegistryPath,IN PDRIVER_INITIALIZATION_DATA DriverInitializationData)
{
	NTSTATUS Status;
	DRIVER_INITIALIZATION_DATA NewDriverInitializationData;
	NewDriverInitializationData = *DriverInitializationData;
	STZeroMemory(PrimaryFrameBufferDescr);
	gpFrameBufferMap->Clear();
	GetDbgMsgState();
	/////////////////////////////////////////////////////////////////////////////////////////////
	(PVOID&)OldDxgkDdiSetVidPnSourceAddress = NewDriverInitializationData.DxgkDdiSetVidPnSourceAddress;
	NewDriverInitializationData.DxgkDdiSetVidPnSourceAddress = NewDxgkDdiSetVidPnSourceAddress;
	/////////////////////////////////////////////////////////////////////////////////////////////
	(PVOID&)OldDxgkDdiCreateAllocation = NewDriverInitializationData.DxgkDdiCreateAllocation;
	NewDriverInitializationData.DxgkDdiCreateAllocation = NewDxgkDdiCreateAllocation;
	/////////////////////////////////////////////////////////////////////////////////////////////
	(PVOID&)OldDxgkDdiDestroyAllocation = NewDriverInitializationData.DxgkDdiDestroyAllocation;
	NewDriverInitializationData.DxgkDdiDestroyAllocation = NewDxgkDdiDestroyAllocation;
	/////////////////////////////////////////////////////////////////////////////////////////////
	(PVOID&)OldDxgkDdiSetVidPnSourceVisibility = NewDriverInitializationData.DxgkDdiSetVidPnSourceVisibility;
	NewDriverInitializationData.DxgkDdiSetVidPnSourceVisibility = NewDxgkDdiSetVidPnSourceVisibility;
	/////////////////////////////////////////////////////////////////////////////////////////////
	//(PVOID&)OldDxgkDdiPresent = NewDriverInitializationData.DxgkDdiPresent;
	//NewDriverInitializationData.DxgkDdiPresent = NewDxgkDdiPresent;
	return OldDxgkInitialize(DriverObject,RegistryPath,&NewDriverInitializationData);
}
