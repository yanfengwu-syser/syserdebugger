#include "StdAfx.h"
#include "InputDriver.h"
#include "Syser.h"
#include "Mouse.h"
#include "Keyboard.h"

#ifdef __cplusplus
extern "C" {
#endif

ULONGLONG gPrevMouseTickCount;
ULONGLONG gCurrMouseTickCount;
ULONGLONG gPrevLButtonDownTickCount;
ULONGLONG gPrevRButtonDownTickCount;
ULONGLONG gPrevMButtonDownTickCount;
ULONGLONG gMaxDblClkInterval=400;
bool gLButtonDblClkSecond=false;
bool gRButtonDblClkSecond=false;
bool gMButtonDblClkSecond=false;
bool bIsMouseData = false;
BYTE MouseBeginBuffer[0x24];
DWORD dwMouseBeginBufferIndex = 0;
MouseDataPackage MouseBuffer[0x100];
MouseDataPackage CurrentMouseData;						//当前鼠标移动包的数据
MouseDataPackage PrevMouseData;							//上一个鼠标移动包的数据
MouseDataPackage *pMouseDataPackage = MouseBuffer;
DWORD dwMouseBufferIndex = 0;							//鼠标缓冲区的索引。以鼠标的移动数据包为单位。
DWORD dwMousePrePackageSize = 0;						//鼠标移动数据包的字节数  3  或 4个
DWORD dwMousePackageBeginOffset = 0;					//当调试器被激活是Windows 的鼠标数据包被揭短的偏移，如果是非 0 则在
														//调试器推出是要模拟鼠标输入给 Windows。不至于鼠标在屏幕中乱晃。

extern ULONGLONG gTSCTickCount;

#ifdef __cplusplus
}; // extern "C"
#endif

void TranslateUSBMouse(char*pData,char*pBtStatus)
{
	char cFirstData,cXOffset,cYOffset,cZOffset;
	ULONGLONG TmpTickCount,Interval;
	bool bButtonState,bDoubleClick;
	TmpTickCount=SyserGetTSC();
	cFirstData=pData[0];
	cXOffset=pData[1];
	cYOffset=pData[2];
	cZOffset=pData[3];
	if(cYOffset != 0 || cXOffset != 0)
		gpSyser->OnMouseMove(cXOffset,cYOffset);
	if(cZOffset)
		gpSyser->OnMouseWheel(cZOffset);
	if((*pBtStatus & MOUSE_INTERRUPT_LEFT_PRESS) != (cFirstData & MOUSE_INTERRUPT_LEFT_PRESS))
	{
		bDoubleClick=false;
		bButtonState = cFirstData & MOUSE_INTERRUPT_LEFT_PRESS;
		if(bButtonState)
		{
			if(gLButtonDblClkSecond==false)
			{
				gLButtonDblClkSecond=true;
				gPrevLButtonDownTickCount=TmpTickCount;
			}
			else
			{
				if(cYOffset==0&&cYOffset==0)
				{
					Interval = (TmpTickCount-gPrevLButtonDownTickCount) / gTSCTickCount;
					if(Interval<=gMaxDblClkInterval)
					{
						gpSyser->OnMouseButtonDBClick(WISP_VK_LBUTTON);
						gLButtonDblClkSecond=false;
						bDoubleClick=true;
					}
					else
					{
						gLButtonDblClkSecond=true;
						gPrevLButtonDownTickCount=TmpTickCount;
					}
				}
				else 
				{
					gLButtonDblClkSecond=true;
					gPrevLButtonDownTickCount=TmpTickCount;
				}
			}
		}
		if(!bDoubleClick)
		{
			gpSyser->OnKeyEvent(WISP_VK_LBUTTON,cFirstData & MOUSE_INTERRUPT_LEFT_PRESS);
		}
	}
	if((*pBtStatus & MOUSE_INTERRUPT_RIGHT_PRESS) != (cFirstData & MOUSE_INTERRUPT_RIGHT_PRESS))
	{
		bDoubleClick=false;
		bButtonState = (cFirstData & MOUSE_INTERRUPT_RIGHT_PRESS)!=0;
		if(bButtonState)
		{
			if(gRButtonDblClkSecond==false)
			{
				gRButtonDblClkSecond=true;
				gPrevRButtonDownTickCount=TmpTickCount;
			}
			else
			{
				if(cYOffset==0&&cYOffset==0)
				{
					Interval = (TmpTickCount-gPrevRButtonDownTickCount) / gTSCTickCount;
					if(Interval<=gMaxDblClkInterval)
					{
						gpSyser->OnMouseButtonDBClick(WISP_VK_RBUTTON);
						gRButtonDblClkSecond=false;
						bDoubleClick=true;
					}
					else
					{
						gRButtonDblClkSecond=true;
						gPrevRButtonDownTickCount=TmpTickCount;
					}
				}
				else 
				{
					gRButtonDblClkSecond=true;
					gPrevRButtonDownTickCount=TmpTickCount;
				}
			}
		}
		if(!bDoubleClick)
			gpSyser->OnKeyEvent(WISP_VK_RBUTTON,(cFirstData & MOUSE_INTERRUPT_RIGHT_PRESS)!=0);
	}
	if((*pBtStatus & MOUSE_INTERRUPT_MIDDLE_PRESS) != (cFirstData & MOUSE_INTERRUPT_MIDDLE_PRESS))
	{
		bDoubleClick=false;
		bButtonState = (cFirstData & MOUSE_INTERRUPT_MIDDLE_PRESS)!=0;
		if(bButtonState)
		{
			if(gMButtonDblClkSecond==false)
			{
				gMButtonDblClkSecond=true;
				gPrevMButtonDownTickCount=TmpTickCount;
			}
			else
			{
				if(cYOffset==0&&cYOffset==0)
				{
					Interval = (TmpTickCount-gPrevMButtonDownTickCount) / gTSCTickCount;
					if(Interval<=gMaxDblClkInterval)
					{
						gpSyser->OnMouseButtonDBClick(WISP_VK_MBUTTON);
						gMButtonDblClkSecond=false;
						bDoubleClick=true;
					}
					else
					{
						gMButtonDblClkSecond=true;
						gPrevMButtonDownTickCount=TmpTickCount;
					}
				}
				else 
				{
					gMButtonDblClkSecond=true;
					gPrevMButtonDownTickCount=TmpTickCount;
				}
			}
		}
		if(!bDoubleClick)
			gpSyser->OnKeyEvent(WISP_VK_MBUTTON,(cFirstData & MOUSE_INTERRUPT_MIDDLE_PRESS)!=0);
	}
	*pBtStatus = *pData;	
}