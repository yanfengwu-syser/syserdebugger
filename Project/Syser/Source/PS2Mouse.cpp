#include "stdafx.h"
#include "HardWareInterruptCtrl.h"
#include "Mouse.h"
#include "PS2Mouse.h"
#include "Syser.h"
#include "TouchPad.h"
DWORD gPS2MouseInterruptNum=0;
bool IsAlpsTouchPad()
{
	int i,j=0,n=0;
	bool bOK;

	for(i = 0;i<6;i++)
	{
		if(MouseBeginBuffer[i]&0x80)		
			n++,j=i;
	}
	if(n!=1)
		return false;
	for(i = j,n=0;i<j+18;i++)
	{
		if(((MouseBeginBuffer[i]&0x88) == 0x88) 
			&& ((MouseBeginBuffer[i+3]&0x88)==0x8)
			&& ((MouseBeginBuffer[i+1]&0x80) == 0)
			&& ((MouseBeginBuffer[i+2]&0x80) == 0)
			&& ((MouseBeginBuffer[i+4]&0x80) == 0)
			&& ((MouseBeginBuffer[i+5]&0x80) == 0))
			n++;
	}
	return n==3;
}
bool IsSynapticsTouchPad()
{
	int i,n=0;
	BYTE* p=MouseBeginBuffer;;
	for(i = 0; i < 6;i++)
	{
		if(((p[i]&0xc0)==0x80) 
			&& ((p[i+3]&0xc0)==0xc0)
			&& ((p[i+6]&0xc0)==0x80)
			&& ((p[i+9]&0xc0)==0xc0)
			&& ((p[i+12]&0xc0)==0x80)
			&& ((p[i+15]&0xc0)==0xc0))
		{
			n++;
			break;
		}
	}
	
	return n==1;
}
DWORD CalcMouseBeginIndex()
{
	DWORD i,j,k,n;
	bool bFirst;

	for(i = 0,j = MouseInterruptCount-23; i < dwMousePrePackageSize;j++,i++)
	{
		if(MouseBeginBuffer[j%24]&8)
		{
			bFirst = true;
			for(k = 0,n = j; k < (24 / dwMousePrePackageSize);k++,n+=dwMousePrePackageSize)
			{
				if((MouseBeginBuffer[n%24]&8)==0)
				{
					bFirst = false;
					break;
				}
			}
			if(bFirst)
				break;
		}
	}
	if(i)
		i = dwMousePrePackageSize - i;
	return i;
}
DWORD dwMyMouseCounter = 0;

// __declspec (naked) void Interrupt_0xF9_Mouse_Service()
// {
// 	__asm{
// 		pushfd
// 		cmp cs:gbActive,0
// 		jnz local_2
// 		push eax  
// 		in al,0x64 
// 		test al,1 
// 		pop eax 
// 		jnz local_2
// 		popfd
// 		//push cs:dwInterruptF9Address
// 		ret		
// local_2:
// 		popfd
// 		push cs:MouseInterruptService
// 		ret
// 	}
// }

DWORD dwIC=0;
// BYTE nnByte;
// __declspec (naked) void MouseInterruptService()
// {
// 	__asm{
// 		cmp cs:gbActive,TRUE
// 		jz local_1
// 		mov ss:bIsMouseData,TRUE
// 		ret		
// local_1:	
// 		lea esp,[esp+4]
// 		pushad
// 		pushfd
// 		in al,0x64
// 		and eax,0xff
// 		mov nnByte,al
// 		mov ebx,eax			
// 		in al,0x60 
// 		mov stKeyGlobalVariable.chCurrentMouseData,al
// 	}
// 	PS2MouseOperation();
// 	MouseInterruptCount++;
// 	SetInteruptEOI(0xc);
// 	__asm
// 	{
// 		popfd
// 		popad
// 		iretd
// 	}
// }

#ifdef __cplusplus
extern "C" {
#endif
extern ULONGLONG gTSCTickCount;
#ifdef __cplusplus
}; // extern "C"
#endif

DWORD gPS2ModifyCount=0;
DWORD gPS2OKPackageCount=0;
void PS2MouseOperation()
{
	ULONGLONG TmpTickCount,Interval;
	bool bButtonState,bDoubleClick;
	int i;
	MouseBeginBuffer[MouseInterruptCount%24]=stKeyGlobalVariable.chCurrentMouseData;

	stKeyGlobalVariable.dwMouseDataIndex ++;

	if(dwMousePrePackageSize==6)
	{
		if(stKeyGlobalVariable.dwMouseDataIndex == 1)
			CurrentMouseData.D6.Byte0 = stKeyGlobalVariable.chCurrentMouseData;	
		if(stKeyGlobalVariable.dwMouseDataIndex == 2)		
			CurrentMouseData.D6.Byte1 = stKeyGlobalVariable.chCurrentMouseData;
		if(stKeyGlobalVariable.dwMouseDataIndex == 3)		
			CurrentMouseData.D6.Byte2 = stKeyGlobalVariable.chCurrentMouseData;							
		if(stKeyGlobalVariable.dwMouseDataIndex == 4)		
			CurrentMouseData.D6.Byte3 = stKeyGlobalVariable.chCurrentMouseData;
		if(stKeyGlobalVariable.dwMouseDataIndex == 5)
			CurrentMouseData.D6.Byte4 = stKeyGlobalVariable.chCurrentMouseData;
		if(stKeyGlobalVariable.dwMouseDataIndex == 6)
			CurrentMouseData.D6.Byte5 = stKeyGlobalVariable.chCurrentMouseData;
		if(stKeyGlobalVariable.dwMouseDataIndex == dwMousePrePackageSize)
		{			
			if(gbSynapticsTouchPad==false && gbAlpsTouchPad==false && MouseInterruptCount>23)
			{
				gbAlpsTouchPad = IsAlpsTouchPad();
				//OUTPUT(WSTR("gbAlpsTouchPad=%d\n"),gbAlpsTouchPad);
				if(gbAlpsTouchPad==false)
				{
					gbSynapticsTouchPad=IsSynapticsTouchPad();
					//OUTPUT(WSTR("gbSynapticsTouchPad=%d\n"),gbSynapticsTouchPad);
				}
			}
			if(gbAlpsTouchPad)
			{
				if(MouseInterruptCount>23&&((CurrentMouseData.D6.Byte0&0x88)!=0x88||(CurrentMouseData.D6.Byte3&0x88)!=0x8))
				{
					if((PrevMouseData.D6.Byte1&0x88)==0x88&&(PrevMouseData.D6.Byte4&0x88)==0x8&&(CurrentMouseData.D6.Byte1&0x88)==0x88&&(CurrentMouseData.D6.Byte4&0x88)==0x8)
						stKeyGlobalVariable.dwMouseDataIndex=5;
					else if((PrevMouseData.D6.Byte2&0x88)==0x88&&(PrevMouseData.D6.Byte5&0x88)==0x8&&(CurrentMouseData.D6.Byte2&0x88)==0x88&&(CurrentMouseData.D6.Byte5&0x88)==0x8)
						stKeyGlobalVariable.dwMouseDataIndex=4;
					else if((PrevMouseData.D6.Byte0&0x88)==0x88 && (PrevMouseData.D6.Byte3&0x88)==0x8&&(CurrentMouseData.D6.Byte0&0x88)==0x88&&(CurrentMouseData.D6.Byte3&0x88)==0x8)
						stKeyGlobalVariable.dwMouseDataIndex=3;
					else if((PrevMouseData.D6.Byte1&0x88)==0x88&&(PrevMouseData.D6.Byte4&0x88)==0x8&&(CurrentMouseData.D6.Byte1&0x88)==0x88&&(CurrentMouseData.D6.Byte4&0x88)==0x8)
						stKeyGlobalVariable.dwMouseDataIndex=2;
					else
						stKeyGlobalVariable.dwMouseDataIndex=1;
					CurrentMouseData.D6.Byte0=0x88;
					CurrentMouseData.D6.Byte3=0x8;

					gPS2ModifyCount++;
					if(gPS2ModifyCount>10)
					{
						dwMousePrePackageSize=3;
					}
					gPS2OKPackageCount=0;
				}
			}
			if(gbSynapticsTouchPad)
			{			
				if(MouseInterruptCount>23&&((CurrentMouseData.D6.Byte0&0xc0)!=0x80||(CurrentMouseData.D6.Byte3&0xc0)!=0xc0))
				{
					if((PrevMouseData.D6.Byte1&0xc0)==0x80&&(PrevMouseData.D6.Byte4&0xc0)==0xc0&&(CurrentMouseData.D6.Byte1&0xc0)==0x80&&(CurrentMouseData.D6.Byte4&0xc0)==0xc0)
						stKeyGlobalVariable.dwMouseDataIndex=5;
					else if((PrevMouseData.D6.Byte2&0xc0)==0x80&&(PrevMouseData.D6.Byte5&0xc0)==0xc0&&(CurrentMouseData.D6.Byte2&0xc0)==0x80&&(CurrentMouseData.D6.Byte5&0xc0)==0xc0)
						stKeyGlobalVariable.dwMouseDataIndex=4;
					else if((PrevMouseData.D6.Byte0&0xc0)==0xc0 && (PrevMouseData.D6.Byte3&0xc0)==0x80&&(CurrentMouseData.D6.Byte0&0xc0)==0xc0&&(CurrentMouseData.D6.Byte3&0xc0)==0x80)
						stKeyGlobalVariable.dwMouseDataIndex=3;
					else if((PrevMouseData.D6.Byte1&0xc0)==0xc0&&(PrevMouseData.D6.Byte4&0xc0)==0x80&&(CurrentMouseData.D6.Byte1&0xc0)==0xc0&&(CurrentMouseData.D6.Byte4&0xc0)==0x80)
						stKeyGlobalVariable.dwMouseDataIndex=2;
					else
						stKeyGlobalVariable.dwMouseDataIndex=1;
					CurrentMouseData.D6.Byte0=0x80;
					CurrentMouseData.D6.Byte3|=0xC0;
					
					gPS2ModifyCount++;
					if(gPS2ModifyCount>10)
					{
						dwMousePrePackageSize=3;
					}
					gPS2OKPackageCount=0;
				}
				else
				{	
					gPS2OKPackageCount++;
					if(gPS2OKPackageCount>10&&gPS2ModifyCount>=1)
						gPS2ModifyCount--;
				}
			}
			if(stKeyGlobalVariable.dwMouseDataIndex == dwMousePrePackageSize)
			{		
				if(gbSynapticsTouchPad)
					AnalyzerTouchPadPackage();
				if(gbAlpsTouchPad)
					AlpsAnalyzerTouchPadPackage();
				stKeyGlobalVariable.dwMouseDataIndex = 0;	
			}
		}
	}
	else
	{
		if(stKeyGlobalVariable.dwMouseDataIndex == 1)
			CurrentMouseData.D3.cFirstData = stKeyGlobalVariable.chCurrentMouseData;	
		if(stKeyGlobalVariable.dwMouseDataIndex == 2)		
			CurrentMouseData.D3.cXOffset = stKeyGlobalVariable.chCurrentMouseData;
		if(stKeyGlobalVariable.dwMouseDataIndex == 3)		
			CurrentMouseData.D3.cYOffset = -stKeyGlobalVariable.chCurrentMouseData;							
		if(stKeyGlobalVariable.dwMouseDataIndex == 4)		
			CurrentMouseData.D3.cZOffset = stKeyGlobalVariable.chCurrentMouseData;
		if(stKeyGlobalVariable.dwMouseDataIndex == dwMousePrePackageSize)
		{
			TmpTickCount=SyserGetTSC();
			if((CurrentMouseData.D3.cFirstData&8)==0)
				PrevMouseData.D3.cFirstData=CurrentMouseData.D3.cFirstData;
			stKeyGlobalVariable.dwMouseDataIndex = 0;	
			if(CurrentMouseData.D3.cYOffset != 0 || CurrentMouseData.D3.cXOffset != 0)
			{			
				gpSyser->OnMouseMove(CurrentMouseData.D3.cXOffset,CurrentMouseData.D3.cYOffset);
			}
			if(CurrentMouseData.D3.cZOffset)
			{
				gpSyser->OnMouseWheel(-CurrentMouseData.D3.cZOffset);
			}
			if((PrevMouseData.D3.cFirstData & MOUSE_INTERRUPT_LEFT_PRESS) != (CurrentMouseData.D3.cFirstData & MOUSE_INTERRUPT_LEFT_PRESS))
			{				
				bDoubleClick=false;
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
						if(CurrentMouseData.D3.cYOffset==0&&CurrentMouseData.D3.cXOffset==0)
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
					gpSyser->OnKeyEvent(WISP_VK_LBUTTON,bButtonState);
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
						if(CurrentMouseData.D3.cYOffset==0&&CurrentMouseData.D3.cXOffset==0)
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
			if((PrevMouseData.D3.cFirstData & MOUSE_INTERRUPT_MIDDLE_PRESS) != (CurrentMouseData.D3.cFirstData & MOUSE_INTERRUPT_MIDDLE_PRESS))
			{				
				bDoubleClick=false;
				bButtonState = (CurrentMouseData.D3.cFirstData & MOUSE_INTERRUPT_MIDDLE_PRESS)!=0;
				if(bButtonState)
				{
					if(gMButtonDblClkSecond==false)
					{
						gMButtonDblClkSecond=true;
						gPrevMButtonDownTickCount=TmpTickCount;
					}
					else
					{
						if(CurrentMouseData.D3.cYOffset==0&&CurrentMouseData.D3.cXOffset==0)
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
					gpSyser->OnKeyEvent(WISP_VK_MBUTTON,(CurrentMouseData.D3.cFirstData & MOUSE_INTERRUPT_MIDDLE_PRESS)!=0);
			}

			PrevMouseData.D3.cFirstData = CurrentMouseData.D3.cFirstData;
			PrevMouseData.D3.cXOffset = CurrentMouseData.D3.cXOffset;
			PrevMouseData.D3.cYOffset = CurrentMouseData.D3.cYOffset;
			PrevMouseData.D3.cZOffset = CurrentMouseData.D3.cZOffset;
			
			if((PrevMouseData.D3.cFirstData&8)==0&&MouseInterruptCount>=23)
			{
				stKeyGlobalVariable.dwMouseDataIndex = CalcMouseBeginIndex();
				//OUTPUT(WSTR("[%d]Mouse offset modify %d\n"),dwMousePrePackageSize,stKeyGlobalVariable.dwMouseDataIndex);
				MouseInterruptCount=0;
				gPS2ModifyCount++;
				if(gPS2ModifyCount>=10)
				{
					if(dwMousePrePackageSize==3)
						dwMousePrePackageSize=4;
					else
					dwMousePrePackageSize=6;
					gPS2ModifyCount=0;
				}
				gPS2OKPackageCount=0;
			}
			else
			{
				if((PrevMouseData.D3.cFirstData&8)==0)
				{
					gPS2ModifyCount++;
					gPS2OKPackageCount=0;
				}
				else
				{
					gPS2OKPackageCount++;
					if(gPS2OKPackageCount>10&&gPS2ModifyCount>=1)
						gPS2ModifyCount--;
				}
			}
			
		}
	}
}