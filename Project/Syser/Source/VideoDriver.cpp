#include "StdAfx.h"
#include "VideoDriver.h"
#include "Syser.h"
#include "VMWareSupport.h"
#include "VirtualPCSupport.h"

#ifdef __cplusplus
extern "C" {
#endif
SYSER_FRAME_BUFFER*		pCurFrameBuffer = NULL;
SYSER_FRAME_BUFFER*		pPrevFrameBuffer = NULL;
bool					bDisabled = false;

bool*	pbSyserDisabled = NULL;
PDRIVER_OBJECT VideoDriver;
PDEVICE_OBJECT DeviceObject;
PDEVICE_OBJECT Video0Device;

#ifdef __cplusplus
}; // extern "C"
#endif


void SyserFrameModeChange(int Width,int Height,int Bpp,void*FrameBuffer,int Pitch,UINT PixelFormat)
{
	if(	Width == gpSyser->m_RealFrameBuffer.Width && Height == gpSyser->m_RealFrameBuffer.Height && 
		Bpp == gpSyser->m_RealFrameBuffer.Bpp && FrameBuffer == gpSyser->m_RealFrameBuffer.Buffer &&
		Pitch == gpSyser->m_RealFrameBuffer.LineDistance && PixelFormat == gpSyser->m_RealFrameBuffer.PixelFormat)
		return;

	::DbgPrint("Syser : Mode Change %d X %d x %d -> Video Buffer[0x%08X] , Pitch [0x%X]\n",Width,Height,Bpp,FrameBuffer,Pitch);
	if(FrameBuffer)
	{
		int Size = Pitch*Height;
		for(int Off = 0;Off<Size;Off+=MP_SIZE)
		{
			if(MmIsAddressValid((BYTE*)FrameBuffer+Off)==false)
			{
				DbgPrint("***************************************************************************\n");
				DbgPrint("Syser : Invalid FrameBuf [%08X] ,Invalid Address [%08X]\n",FrameBuffer,(BYTE*)FrameBuffer+Off);
				DbgPrint("***************************************************************************\n");
				gpSyser->m_RealFrameBuffer.Buffer = NULL;
				return;
			}
		}
	}
	gpSyser->m_RealFrameBuffer.Width = Width;
	gpSyser->m_RealFrameBuffer.Height = Height;
	gpSyser->m_RealFrameBuffer.Bpp = Bpp;
	gpSyser->m_RealFrameBuffer.Buffer = FrameBuffer;
	gpSyser->m_RealFrameBuffer.LineDistance = Pitch;
	gpSyser->GetFrameBufferDrawHAL(&gpSyser->m_RealFrameBuffer);
	if(gpSyser->m_pRootWnd)
	{
		if(Width < gpSyser->m_MainFrame.m_WindowRect.cx || Height < gpSyser->m_MainFrame.m_WindowRect.cy)
		{
			OUTPUT(WSTR("Syser : Resize %d %d\n"),Width,Height);
			gpSyser->m_MainFrame.Resize(Width,Height);
		}
		else if(Width > gpSyser->m_MainFrame.m_WindowRect.cx || Height > gpSyser->m_MainFrame.m_WindowRect.cy)
		{
			OUTPUT(WSTR("Syser : Resize %d %d\n"),gpSyser->m_OrgWindowWidth,gpSyser->m_OrgWindowHeight);
			gpSyser->m_MainFrame.Resize(gpSyser->m_OrgWindowWidth,gpSyser->m_OrgWindowHeight);
		}
	}
	gpSyser->m_RootPos.x = CENTER_ALGN(gpSyser->m_MainFrame.m_WindowRect.cx,Width);
	gpSyser->m_RootPos.y = CENTER_ALGN(gpSyser->m_MainFrame.m_WindowRect.cy,Height);
	MIN_LIMIT(gpSyser->m_RootPos.x,0);
	MIN_LIMIT(gpSyser->m_RootPos.y,0);
	gpSyser->m_bScrBackup = true;
}

void SyserFrameBufferFlip(void*FrameBuffer)
{
	gpSyser->m_RealFrameBuffer.Buffer = FrameBuffer;
}

void SyserActive()
{
	gpSyser->Active();
}


NTSTATUS CompletionRoutine(IN PDEVICE_OBJECT DeviceObject, IN PIRP Irp, IN PVOID Context)
{
	IoFreeIrp(Irp);
	return STATUS_MORE_PROCESSING_REQUIRED;
}


bool InstallDdrawHook()
{
	ULPOS SyserRootImageBase;
	PEPROCESS Pr;
	ULPOS Address;
	CDbgProcess*pProcess;
	NTSTATUS ntStatus;
	if(gpSysBootDevEx==NULL)
	{
		::DbgPrint("Syser : Fail to attach FrameBuffer , SysBoot isn't actived!\n");
		return true;
	}
	if(gpSysBootDevEx->cbSize == sizeof(SYSER_BOOT_DEVICE_EXTENSION))
	{
			gpSysBootDevEx->pfnFrameModeChange = SyserFrameModeChange;
			gpSysBootDevEx->pfnFrameBufferFlip = SyserFrameBufferFlip;
			gpSysBootDevEx->pfnSyserActive = SyserActive;
			pbSyserDisabled = &gpSysBootDevEx->bDisabled;
			if(gpSysBootDevEx->pCurFrameBuffer)
			{
				SyserFrameModeChange(	gpSysBootDevEx->pCurFrameBuffer->Width,gpSysBootDevEx->pCurFrameBuffer->Height,
										gpSysBootDevEx->pCurFrameBuffer->Bpp,gpSysBootDevEx->pCurFrameBuffer->Buffer,
										gpSysBootDevEx->pCurFrameBuffer->LineDistance,gpSysBootDevEx->pCurFrameBuffer->PixelFormat);
				return true;
			}
			else
			{
				::DbgPrint("Syser : Fail to attach Video FrameBuffer !\n");
				if(gInVMWARE)
				{
					::DbgPrint("*************************************\n");
					::DbgPrint("Syser : Please Install VMWare Tools !\n");
					::DbgPrint("*************************************\n");
				}
				else if(gInVirtualPC)
				{
					::DbgPrint("************************************************************\n");
					::DbgPrint("Syser : Please Install or Update Virtual Machine Additions !\n");
					::DbgPrint("************************************************************\n");
				}
			}
	}
	else
	{
		::DbgPrint("Syser : SyserBoot[0x%X] version isn't same as Syser[0x%X]!\n",gpSysBootDevEx->cbSize,sizeof(SYSER_BOOT_DEVICE_EXTENSION));
	}
	return true;
}

bool RemoveDdrawHook()
{
	if(gpSysBootDevEx)
	{
		gpSysBootDevEx->pfnFrameModeChange = NULL;
		gpSysBootDevEx->pfnFrameBufferFlip = NULL;
		return true;
	}
	return true;
}


