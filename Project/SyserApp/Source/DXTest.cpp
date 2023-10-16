#include "StdAfx.h"
#include "DXTest.h"
#include "SyserApp.h"

CSyserDX::CSyserDX()
{
	m_pDD4=NULL;
	m_pDD=NULL;
	m_pFrameSurfacer=NULL;
}


bool CSyserDX::Init()
{
	HRESULT hResult;
	hResult=DirectDrawCreate(NULL, &m_pDD, NULL);
	if(hResult!=DD_OK)
		goto FailExit;
	hResult=m_pDD->QueryInterface(IID_IDirectDraw4,(LPVOID*)&m_pDD4);
	if(hResult!=DD_OK)
	{
		m_pDD->Release();
		goto FailExit;
	}
	m_pDD4->SetCooperativeLevel(NULL,DDSCL_NORMAL);
	return true;
FailExit:
	OUTPUT(WSTR("%<F>SyserLoader : Your video driver doesn't support direct draw!\n"));
	OUTPUT(WSTR("%<F>SyserLoader : Syser could't lock frame buffer!\n"));
	return false;
}

void CSyserDX::LockFrameSurfacer()
{
	HRESULT hResult;
	DDSURFACEDESC2 SurfaceDesc;

	if(m_pDD4==NULL)
		return;

	UnlockFrameSurfacer();

	STZeroMemory(SurfaceDesc);
	SurfaceDesc.dwSize = sizeof(SurfaceDesc);
	SurfaceDesc.dwFlags = DDSD_CAPS;
	SurfaceDesc.ddsCaps.dwCaps = DDSCAPS_PRIMARYSURFACE;
	hResult=m_pDD4->CreateSurface(&SurfaceDesc,&m_pFrameSurfacer,NULL);
	if(hResult!=DD_OK)
	{
		OUTPUT(WSTR("%<F>SyserLoader : Fail to create surface !\n"));
		OUTPUT(WSTR("%<F>SyserLoader : Your video driver doesn't support direct draw!\n"));
		return;
	}

	hResult=m_pFrameSurfacer->Lock(NULL,&SurfaceDesc,DDLOCK_SURFACEMEMORYPTR,NULL);
	if(hResult!=DD_OK)
	{
		m_pFrameSurfacer->Release();
		m_pFrameSurfacer=NULL;
		OUTPUT(WSTR("%<F>SyserLoader : Fail to lock surface !\n"));
		OUTPUT(WSTR("%<F>SyserLoader : Your video driver doesn't support direct draw!\n"));
		return;
	}

	DWORD cbReturn;
	SYSER_CORRECT_VIDEO_PARAM CorrectVideoParam;
	CorrectVideoParam.Pitch= SurfaceDesc.lPitch;
	CorrectVideoParam.Width = SurfaceDesc.dwWidth;
	CorrectVideoParam.Height = SurfaceDesc.dwHeight;
	CorrectVideoParam.Bpp = SurfaceDesc.ddpfPixelFormat.dwRGBBitCount;
	CorrectVideoParam.FrameBuffer = SurfaceDesc.lpSurface;
	CorrectVideoParam.BufferSize = SurfaceDesc.dwHeight * SurfaceDesc.lPitch;
	CorrectVideoParam.PID = GetCurrentProcessId();
	HANDLE hSyser = CreateFile(DRIVER_RING3_NAME,GENERIC_READ,FILE_SHARE_READ|FILE_SHARE_WRITE,NULL,OPEN_EXISTING,0,NULL);
	if(hSyser!=INVALID_HANDLE_VALUE)
	{
		OUTPUT(WSTR("SyserLoader : Notify Syser Kernel Debugger current display mode !\n"));
		DeviceIoControl(hSyser,IOCTL_SYSER_CORRECT_VIDEO_PARAM,&CorrectVideoParam,sizeof(CorrectVideoParam),NULL,0,&cbReturn,NULL);
		CloseHandle(hSyser);
	}

}

void CSyserDX::UnlockFrameSurfacer()
{
	if(m_pFrameSurfacer)
	{
		m_pFrameSurfacer->Unlock(NULL);
		m_pFrameSurfacer->Release();
		m_pFrameSurfacer=NULL;
	}
}

void CSyserDX::Release()
{
	SafeRelease(m_pDD4);
	SafeRelease(m_pDD);
}

