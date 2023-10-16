#ifndef _VIDEO_DRIVER_H_
#define _VIDEO_DRIVER_H_

bool	InstallDdrawHook();
bool	RemoveDdrawHook();

ULPOS	GetWin32KServiceTable(CPEFile*pPEFile);
void	SyserFrameModeChange(int Width,int Height,int Bpp,void*FrameBuffer,int Pitch,UINT PixelFormat);

extern	SYSER_FRAME_BUFFER	SyserFrameBuffer;
extern	SYSER_FRAME_BUFFER*	pSyserFrameBuffer;

#endif
