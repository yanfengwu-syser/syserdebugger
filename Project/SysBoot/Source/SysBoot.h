#ifndef _SYSER_BOOT_H_
#define _SYSER_BOOT_H_

typedef void	(*PFN_FrameModeChange)(int Width,int Height,int Bpp,void*FrameBuffer,int Pitch,UINT PixelFormat);
typedef void	(*PFN_FrameBufferFlip)(void*FrameBuffer);
typedef void	(*PFN_SyserActive)();
typedef void	(*PFN_ScrPrint)(int x,int y,PCSTR szMsg,...);

void	SwitchDrawPixel(int Bpp);
void	WindowsModeChange(int Width,int Height,int Bpp,void*FrameBuffer,int Pitch);
void	WindowsFilp(void*FrameBuffer);
void	GetDbgMsgState();

#define SYSER_BOOT_VER		0x00019700

struct SYSER_BOOT_DEVICE_EXTENSION
{
	int						cbSize;
	DWORD					Version;
	SYSER_FRAME_BUFFER*		pCurFrameBuffer;
	PFN_FrameModeChange		pfnFrameModeChange;
	PFN_FrameBufferFlip		pfnFrameBufferFlip;
	PFN_SyserActive			pfnSyserActive;
	PFN_ScrPrint			pfnScrPrint;
	PLOAD_IMAGE_NOTIFY_ROUTINE  pfnLoadImageNotifyRoutine;
	bool					bCanceled;
	bool					bDisabled;
};

typedef TMap<HANDLE,SYSER_FRAME_BUFFER>	CSyserFrameBufferMap;


extern	WCHAR	szDispModuleName[MAX_FN_LEN];
extern	bool	gbDisabled;
extern	bool	gbDbgMsg;
extern	bool	gbFlipDbgMsg;
extern SYSER_BOOT_DEVICE_EXTENSION*gpDevExt;
extern CSyserFrameBufferMap*gpFrameBufferMap;
extern SYSER_FRAME_BUFFER CurentFrameBuffer;

#define SYSER_BOOT_LINK_NAME		WSTR("\\??\\SyserBoot")

#endif
