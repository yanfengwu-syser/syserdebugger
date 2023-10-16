#include "StdAfx.h"
#include "TouchPad.h"
#include "InputDriver.h"
#include "Mouse.h"
#include "Syser.h"
bool gTouchPad=false;
BYTE gTouchPadMode=0;
bool gbSynapticsTouchPad=false;
bool gbAlpsTouchPad=false;
void TestTouchPad()
{
	bool ReadMouseRet;
	BYTE ResponeBuf[6];
	BYTE ResponeBuf2[6];
	DWORD i =0 ;
	BYTE Value;
	if(gHasPS2Mouse==false)
		return;
	for(i = 0; i < sizeof(ResponeBuf);i++)
		ResponeBuf[i]=0;
	i=0;
	while(ReadMouseRet = SyserReadPort60(&Value,true))
	{
		if(i<6)
			ResponeBuf2[i]=Value;
		i++;
	}
	i = 0;
	if(SendMouseCommand(0xe8)==false)
		return;
	if(SendMouseCommand(0x0)==false)
		return;
	if(SendMouseCommand(0xe8)==false)
		return;
	if(SendMouseCommand(0x0)==false)
		return;
	if(SendMouseCommand(0xe8)==false)
		return;
	if(SendMouseCommand(0x0)==false)
		return;
	if(SendMouseCommand(0xe8)==false)
		return;
	if(SendMouseCommand(0x1)==false)
		return;
	if(SendMouseCommand(0xe9)==false)
		return;
	while(ReadMouseRet = SyserReadPort60(&Value,true))
	{
		if(i<6)
			ResponeBuf[i]=Value;
		i++;
	}
	if(ResponeBuf[1]==0x47)
	{
		gTouchPad=true;
		if(ResponeBuf[2]&0x80)
		{
			dwMousePrePackageSize=6;
		}
		gTouchPadMode=ResponeBuf[2];
	}
	else
	{
		if(SendMouseCommand(0xe8)==false)
			return;
		if(SendMouseCommand(ResponeBuf2[1]&3)==false)
			return;
	}

}



#ifdef __cplusplus
extern "C" {
#endif
	DWORD gPreAbsoluteX=0;
	DWORD gPreAbsoluteY=0;
	DWORD MouseInterruptCount;
	BYTE gbPressure;
	DWORD gTouchPadCount;
	extern ULONGLONG gTSCTickCount;
#ifdef __cplusplus
}; // extern "C"
#endif

void AnalyzerTouchPadPackage()
{
	DWORD AbsoluteX,AbsoluteY,X,Y;
	int XOffset,YOffset;
	DWORD w;
	ULONGLONG TmpTickCount,Interval;
	char TrackPointX,TrackPointY;
	bool bButtonState,bDoubleClick;

	AbsoluteX=(CurrentMouseData.D6.Byte3&0x10)|(CurrentMouseData.D6.Byte1&0xf);
	AbsoluteX<<=8;
	AbsoluteX|=CurrentMouseData.D6.Byte4;
	X = AbsoluteX;
	AbsoluteY=CurrentMouseData.D6.Byte3&0x20;
	AbsoluteY>>=1;
	AbsoluteY=AbsoluteY|((CurrentMouseData.D6.Byte1&0xf0)>>4);
	AbsoluteY<<=8;
	AbsoluteY|=CurrentMouseData.D6.Byte5;
	Y = AbsoluteX;
	if(CurrentMouseData.D6.Byte2)
	{
		if(gbPressure==0)
		{
			gTouchPadCount=0;
			//gpSyser->DbgPrint(0,24,WSTR("[%d] %d %d %d %d"),gTouchPadCount,gPreAbsoluteX,gPreAbsoluteY,AbsoluteX,AbsoluteY);
			gPreAbsoluteX=AbsoluteX;
			gPreAbsoluteY=AbsoluteY;
		}
	}
	else
	{
		if(gbPressure)
		{
			//gpSyser->DbgPrint(0,12,WSTR("[%d] %d %d %d %d"),gTouchPadCount,gPreAbsoluteX,gPreAbsoluteY,AbsoluteX,AbsoluteY);
		}
	}
	gbPressure=CurrentMouseData.D6.Byte2;
	AbsoluteX = (gPreAbsoluteX+AbsoluteX)/2;
	AbsoluteY = (gPreAbsoluteY+AbsoluteY)/2;
#if 0
	gpSyser->DbgPrint(600,0,WSTR("count=[%d] %02x %02x %02x %02x %02x %02x x=%d y=%d"),MouseInterruptCount,CurrentMouseData.D6.Byte0,
		CurrentMouseData.D6.Byte1,
		CurrentMouseData.D6.Byte2,
		CurrentMouseData.D6.Byte3,
		CurrentMouseData.D6.Byte4,
		CurrentMouseData.D6.Byte5,
		AbsoluteX,
		AbsoluteY
		);
#endif
	
	TmpTickCount = SyserGetTSC();
	XOffset=AbsoluteX-gPreAbsoluteX;
	YOffset=AbsoluteY-gPreAbsoluteY;
	YOffset/=6;
	XOffset/=6;

	if(CurrentMouseData.D6.ZPressure!=0||X!=0||Y!=0)
	{
		if(CurrentMouseData.D6.ZPressure==0)
		{
			TrackPointX=CurrentMouseData.D6.Byte4;
			TrackPointY=CurrentMouseData.D6.Byte5;
		}
		if((XOffset||YOffset))
		{
			if(CurrentMouseData.D6.ZPressure>40&&gTouchPadCount>10)
				gpSyser->OnMouseMove(XOffset,-YOffset);
			if(CurrentMouseData.D6.ZPressure==0)
				gpSyser->OnMouseMove(TrackPointX,-TrackPointY);
			if(CurrentMouseData.D6.ZPressure!=0)
			{
				gPreAbsoluteX=AbsoluteX;
				gPreAbsoluteY=AbsoluteY;
			}
		}
	}

	if((PrevMouseData.D3.cFirstData & MOUSE_INTERRUPT_LEFT_PRESS) != (CurrentMouseData.D3.cFirstData & MOUSE_INTERRUPT_LEFT_PRESS))
	{
		bButtonState = CurrentMouseData.D3.cFirstData & MOUSE_INTERRUPT_LEFT_PRESS;
		if(bButtonState)
		{
			if(gLButtonDblClkSecond==false)
			{
				gLButtonDblClkSecond=true;
				gPrevLButtonDownTickCount=TmpTickCount;
			}
			else
			{
				if(CurrentMouseData.D6.Byte2 == 0 ||(XOffset==0&&YOffset==0))
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
			gpSyser->OnKeyEvent(WISP_VK_LBUTTON,CurrentMouseData.D3.cFirstData & MOUSE_INTERRUPT_LEFT_PRESS);
	}
	if((PrevMouseData.D3.cFirstData & MOUSE_INTERRUPT_RIGHT_PRESS) != (CurrentMouseData.D3.cFirstData & MOUSE_INTERRUPT_RIGHT_PRESS))
	{
		bDoubleClick=false;
		bButtonState = (CurrentMouseData.D3.cFirstData & MOUSE_INTERRUPT_RIGHT_PRESS)!=0;
		if(bButtonState)
		{
			if(gRButtonDblClkSecond==false)
			{
				gRButtonDblClkSecond=true;
				gPrevRButtonDownTickCount=TmpTickCount;
			}
			else
			{
				if(XOffset==0&&YOffset==0)
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
			gpSyser->OnKeyEvent(WISP_VK_RBUTTON,(CurrentMouseData.D3.cFirstData & MOUSE_INTERRUPT_RIGHT_PRESS)!=0);
	}
	gTouchPadCount++;
	PrevMouseData=CurrentMouseData;
}
/*
* XXX - this entry is suspicious. First byte has zero lower nibble,
* which is what a normal mouse would report. Also, the value 0x0e
* isn't valid per PS/2 spec.
*/

/*
* ALPS abolute Mode - new format
*
* byte 0:  1    ?    ?    ?    1    ?    ?    ?
* byte 1:  0   x6   x5   x4   x3   x2   x1   x0
* byte 2:  0   x10  x9   x8   x7    ?  fin  ges
* byte 3:  0   y9   y8   y7    1    M    R    L
* byte 4:  0   y6   y5   y4   y3   y2   y1   y0
* byte 5:  0   z6   z5   z4   z3   z2   z1   z0
*
* ?'s can have different meanings on different models,
* such as wheel rotation, extra buttons, stick buttons
* on a dualpoint, etc.
*/
void AlpsAnalyzerTouchPadPackage()
{
	DWORD AbsoluteX,AbsoluteY,X,Y;
	int XOffset,YOffset;
	DWORD w;
	ULONGLONG TmpTickCount,Interval;
	char TrackPointX,TrackPointY;
	bool bButtonState,bDoubleClick;

	AbsoluteX=CurrentMouseData.D6.Byte2&0x78;
	AbsoluteX<<=4;
	AbsoluteX|=CurrentMouseData.D6.Byte1&0x7f;		
	X = AbsoluteX;
	AbsoluteY=CurrentMouseData.D6.Byte3&0x70;
	AbsoluteY<<=3;
	AbsoluteY|=CurrentMouseData.D6.Byte4&0x7f;	
	Y = AbsoluteX;
	if(CurrentMouseData.D6.Byte5)
	{
		if(gbPressure==0)
		{
			gTouchPadCount=0;
			//gpSyser->DbgPrint(0,24,WSTR("[%d] %d %d %d %d"),gTouchPadCount,gPreAbsoluteX,gPreAbsoluteY,AbsoluteX,AbsoluteY);
			gPreAbsoluteX=AbsoluteX;
			gPreAbsoluteY=AbsoluteY;
		}
	}
	else
	{
		if(gbPressure)
		{
			//gpSyser->DbgPrint(0,12,WSTR("[%d] %d %d %d %d"),gTouchPadCount,gPreAbsoluteX,gPreAbsoluteY,AbsoluteX,AbsoluteY);
		}
	}
	gbPressure=CurrentMouseData.D6.Byte5;
	AbsoluteX = (gPreAbsoluteX+AbsoluteX)/2;
	AbsoluteY = (gPreAbsoluteY+AbsoluteY)/2;
#if 0
	gpSyser->DbgPrint(600,0,WSTR("count=[%d] %02x %02x %02x %02x %02x %02x x=%d y=%d"),MouseInterruptCount,CurrentMouseData.D6.Byte0,
		CurrentMouseData.D6.Byte1,
		CurrentMouseData.D6.Byte2,
		CurrentMouseData.D6.Byte3,
		CurrentMouseData.D6.Byte4,
		CurrentMouseData.D6.Byte5,
		AbsoluteX,
		AbsoluteY
		);
#endif
	
	TmpTickCount = SyserGetTSC();
	XOffset=AbsoluteX-gPreAbsoluteX;
	YOffset=AbsoluteY-gPreAbsoluteY;
	/*
	OUTPUT(WSTR("%02x %02x %02x %02x %02x %02x\n"),CurrentMouseData.D6.Byte0,
		CurrentMouseData.D6.Byte1,
		CurrentMouseData.D6.Byte2,
		CurrentMouseData.D6.Byte3,
		CurrentMouseData.D6.Byte4,
		CurrentMouseData.D6.Byte5);
	OUTPUT(WSTR("%d %d [%d][%d] (%d)(%d)\n"),AbsoluteX,AbsoluteY,gPreAbsoluteX,gPreAbsoluteY,XOffset,YOffset);
	*/
	//YOffset/=2;
	//XOffset/=2;
	

	if(CurrentMouseData.D6.Byte5!=0||X!=0||Y!=0)
	{
		if(CurrentMouseData.D6.Byte5==0)
		{
			TrackPointX=CurrentMouseData.D6.Byte4;
			TrackPointY=CurrentMouseData.D6.Byte5;
		}
		if((XOffset||YOffset))
		{
			if(CurrentMouseData.D6.Byte5>40&&gTouchPadCount>10)
				gpSyser->OnMouseMove(XOffset,YOffset);
			if(CurrentMouseData.D6.Byte5==0)
				gpSyser->OnMouseMove(TrackPointX,TrackPointY);
			if(CurrentMouseData.D6.Byte5!=0)
			{
				gPreAbsoluteX=AbsoluteX;
				gPreAbsoluteY=AbsoluteY;
			}
		}
	}

	if((PrevMouseData.D6.Byte3 & MOUSE_INTERRUPT_LEFT_PRESS) != (CurrentMouseData.D6.Byte3 & MOUSE_INTERRUPT_LEFT_PRESS))
	{
		bButtonState = CurrentMouseData.D6.Byte3 & MOUSE_INTERRUPT_LEFT_PRESS;
		/*
		if(bButtonState)
		{
			if(gLButtonDblClkSecond==false)
			{
				gLButtonDblClkSecond=true;
				gPrevLButtonDownTickCount=TmpTickCount;
			}
			else
			{
				if(CurrentMouseData.D6.Byte5 == 0 ||(XOffset==0&&YOffset==0))
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
		*/
			gpSyser->OnKeyEvent(WISP_VK_LBUTTON,CurrentMouseData.D6.Byte3 & MOUSE_INTERRUPT_LEFT_PRESS);
	}
	if((PrevMouseData.D6.Byte3 & MOUSE_INTERRUPT_RIGHT_PRESS) != (CurrentMouseData.D6.Byte3 & MOUSE_INTERRUPT_RIGHT_PRESS))
	{
		bDoubleClick=false;
		bButtonState = (CurrentMouseData.D6.Byte3 & MOUSE_INTERRUPT_RIGHT_PRESS)!=0;
		/*
		if(bButtonState)
		{
			if(gRButtonDblClkSecond==false)
			{
				gRButtonDblClkSecond=true;
				gPrevRButtonDownTickCount=TmpTickCount;
			}
			else
			{
				if(XOffset==0&&YOffset==0)
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
		*/
			gpSyser->OnKeyEvent(WISP_VK_RBUTTON,(CurrentMouseData.D6.Byte3 & MOUSE_INTERRUPT_RIGHT_PRESS)!=0);
	}
	gTouchPadCount++;
	PrevMouseData=CurrentMouseData;
}
